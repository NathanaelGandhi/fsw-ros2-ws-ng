#include <boost/asio.hpp>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class CiTo : public rclcpp::Node
{
public:
CiTo()
: Node("ci_to"), count_(0)
{
    port_ = 50006;
    host_ = "127.0.0.1";
}


void start_tcp_server()
{
    RCLCPP_INFO(this->get_logger(), "Starting tcp server on port %d", port_);

    using tcp = boost::asio::ip::tcp;

    boost::asio::io_service io_service;

    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port_));

    tcp::socket socket(io_service);
    acceptor.accept(socket);

    char data[1024];
    boost::system::error_code error;
    size_t len = socket.read_some(boost::asio::buffer(data), error);

    if (error == boost::asio::error::eof)
    {
        RCLCPP_INFO(this->get_logger(), "Connection closed");
    }
    else if (error)
    {
        throw boost::system::system_error(error);
    }

    std::string message = std::string(data, len);
    RCLCPP_INFO(this->get_logger(), "Received: '%s'", message.c_str());

    std::stringstream ss(message);
    std::string value;
    int a, b, c;
    ss >> a >> b >> c;
    int d = c + 1;
    std::stringstream result;
    result << d;
    message = result.str();
    RCLCPP_INFO(this->get_logger(), "Replying with: '%s'", message.c_str());

    this->send_reply_when_ready(message);
    boost::asio::write(socket, boost::asio::buffer(message));
    socket.close();
    RCLCPP_INFO(this->get_logger(), "Finished tcp server on port %d", port_);
}

void send_reply_when_ready(std::string message)
{
    RCLCPP_INFO(this->get_logger(), "Function not implemented: '%s'", message.c_str());
}

private:
size_t count_;
uint32_t port_;
std::string host_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto ci_to = std::make_shared<CiTo>();
  RCLCPP_INFO(rclcpp::get_logger("main"), "Spinning");
  ci_to->start_tcp_server();
//   rclcpp::spin(ci_to);
  rclcpp::shutdown();
  return 0;
}
