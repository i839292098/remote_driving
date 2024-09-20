#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>

typedef websocketpp::server<websocketpp::config::asio> server;
typedef server::message_ptr message_ptr;

class WebSocketServer
{
public:
    WebSocketServer()
    {
        m_server.init_asio();
        m_server.set_open_handler(std::bind(&WebSocketServer::on_open, this, std::placeholders::_1));
        m_server.set_close_handler(std::bind(&WebSocketServer::on_close, this, std::placeholders::_1));
        m_server.set_message_handler(std::bind(&WebSocketServer::on_message, this, std::placeholders::_1, std::placeholders::_2));
    }

    void run(uint16_t port)
    {
        m_server.listen(port);
        m_server.start_accept();
        std::cout << "WebSocket-" << port << " 端口启动成功" << std::endl;
        m_server.run();
    }

private:
    void on_open(websocketpp::connection_hdl hdl)
    {
        std::cout << "Connection opened: " << hdl.lock().get() << std::endl;
    }

    void on_close(websocketpp::connection_hdl hdl)
    {
        std::cout << "Connection closed: " << hdl.lock().get() << std::endl;
    }

    void on_message(websocketpp::connection_hdl hdl, message_ptr msg)
    {
        std::cout << "Message received: " << msg->get_payload() << std::endl;

        try
        {
            m_server.send(hdl, msg->get_payload(), msg->get_opcode());
        }
        catch (const websocketpp::exception &e)
        {
            std::cout << "Send failed: " << e.what() << std::endl;
        }
    }

    server m_server;
};
