#include <httpserver.hpp>

using namespace httpserver;

class file_response_resource : public http_resource {
public:
    const std::shared_ptr<http_response> render_GET(const http_request& req) {
        return std::shared_ptr<file_response>(new file_response("test_content", 200, "text/plain"));
    }
};

int main(int argc, char** argv) {
    webserver ws = create_webserver(8080);

    file_response_resource hwr;
    ws.register_resource("/hello", &hwr);
    ws.start(true);

    return 0;
}
