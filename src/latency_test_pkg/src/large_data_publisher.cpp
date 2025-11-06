#include <chrono>
#include <memory>
#include <vector>
#include <random>
#include "rclcpp/rclcpp.hpp"
#include "latency_test_pkg/msg/large_data.hpp"

using namespace std::chrono_literals;

class LargeDataPublisher : public rclcpp::Node
{
public:
    LargeDataPublisher() : Node("large_data_publisher"), current_index_(0)
    {
        // Configura QoS per messaggi grandi con affidabilità garantita
        auto qos = rclcpp::QoS(rclcpp::KeepLast(10))
            .reliable()
            .durability_volatile();

        publisher_ = this->create_publisher<latency_test_pkg::msg::LargeData>(
            "large_data_topic", qos);

        // Dimensioni da testare: 1MB, 5MB, 10MB
        sizes_mb_ = {1, 5, 10};

        // Timer per pubblicare ogni 3 secondi
        timer_ = this->create_wall_timer(
            3s, std::bind(&LargeDataPublisher::publish_message, this));

        RCLCPP_INFO(this->get_logger(), "Publisher inizializzato. Testando dimensioni: 1MB, 5MB, 10MB");
    }

private:
    void publish_message()
    {
        if (current_index_ >= sizes_mb_.size()) {
            RCLCPP_INFO(this->get_logger(), "Test completato!");
            rclcpp::shutdown();
            return;
        }

        uint64_t size_mb = sizes_mb_[current_index_];
        size_t size_bytes = size_mb * 1024 * 1024;

        auto message = latency_test_pkg::msg::LargeData();
        message.header.stamp = this->now();
        message.size_mb = size_mb;

        // Genera dati casuali
        message.data.resize(size_bytes);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);
        
        for (size_t i = 0; i < size_bytes; ++i) {
            message.data[i] = static_cast<uint8_t>(dis(gen));
        }

        RCLCPP_INFO(this->get_logger(), 
            "Invio messaggio %zu/%zu di %lu MB (%zu bytes)...", 
            current_index_ + 1, sizes_mb_.size(), size_mb, size_bytes);

        auto start = std::chrono::high_resolution_clock::now();
        publisher_->publish(message);
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        RCLCPP_INFO(this->get_logger(), 
            "Messaggio pubblicato in %ld ms", duration.count());

        current_index_++;
    }

    rclcpp::Publisher<latency_test_pkg::msg::LargeData>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::vector<uint64_t> sizes_mb_;
    size_t current_index_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LargeDataPublisher>());
    rclcpp::shutdown();
    return 0;
}