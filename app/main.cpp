
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <yaml-cpp/yaml.h>
#include <jwt-cpp/jwt.h>
#include <jwt-cpp/traits/kazuho-picojson/defaults.h>
#include <crow.h>

class Config {
public:
    std::string addr;
    std::string secret;

    static Config LoadConfig(const std::string& path) {
        YAML::Node config = YAML::LoadFile(path);
        return {config["addr"].as<std::string>(), config["secret"].as<std::string>()};
    }
};

class Handler {
public:
    virtual void handle(const crow::request& req, crow::response& res) = 0;
};

class HomeHandler : public Handler {
public:
    void handle(const crow::request& req, crow::response& res) override {
        std::cout << "Home endpoint accessed" << std::endl;
        res.write("Welcome to the C++ HTTP Service!");
        res.end();
    }
};

class HealthHandler : public Handler {
public:
    void handle(const crow::request& req, crow::response& res) override {
        std::cout << "Health check accessed" << std::endl;
        res.write("OK");
        res.end();
    }
};

class Middleware {
public:
    virtual void protect(const crow::request& req, crow::response& res, std::function<void()> next) = 0;
};

class JWTMiddleware : public Middleware {
private:
    std::string secret;
public:
    explicit JWTMiddleware(std::string secretKey) : secret(std::move(secretKey)) {}

    void protect(const crow::request& req, crow::response& res, std::function<void()> next) override {
        auto auth_header = req.get_header_value("Authorization");
        if (auth_header.find("Bearer ") != 0) {
            std::cout << "Unauthorized access attempt" << std::endl;
            res.code = 401;
            res.end("Unauthorized");
            return;
        }

        std::string token = auth_header.substr(7);
        try {
            auto decoded = jwt::decode<jwt::traits::kazuho_picojson>(token);
            auto verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{secret});
            verifier.verify(decoded);
            std::cout << "Valid JWT token received" << std::endl;
            next();
        } catch (const std::exception& e) {
            std::cout << "Invalid JWT token: " << e.what() << std::endl;
            res.code = 401;
            res.end("Unauthorized");
        }
    }
};

class HTTPServer {
private:
    Config config;
    crow::SimpleApp app;
    std::map<std::string, Handler*> handlers;
    Middleware* authMiddleware;

public:
    explicit HTTPServer(const Config& cfg) : config(cfg) {
        handlers["/"] = new HomeHandler();
        handlers["/health"] = new HealthHandler();
        authMiddleware = new JWTMiddleware(config.secret);

        CROW_ROUTE(app, "/").methods(crow::HTTPMethod::GET)
            ([this](const crow::request& req, crow::response& res) {
                authMiddleware->protect(req, res, [this, &req, &res]() {
                    handlers["/"]->handle(req, res);
                });
            });

        CROW_ROUTE(app, "/health").methods(crow::HTTPMethod::GET)
            ([this](const crow::request& req, crow::response& res) {
                handlers["/health"]->handle(req, res);
            });
    }

    void Start() {
        std::cout << "Starting server at " << config.addr << std::endl;
        app.port(std::stoi(config.addr.substr(config.addr.find(":") + 1))).multithreaded().run();
    }
};

int main() {
    Config config = Config::LoadConfig("config.yaml");
    HTTPServer server(config);
    server.Start();
    return 0;
}
