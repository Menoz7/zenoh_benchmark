#include <chrono>
#include <memory>
#include <vector>
#include <random>
#include "rclcpp/rclcpp.hpp"
#include "latency_test_pkg/msg/large_data.hpp"
#include "latency_test_pkg/msg/large_data_ack.hpp"

using namespace std::chrono_literals;

class LargeDataPublisher : public rclcpp::Node
{
public:
    LargeDataPublisher() : Node("large_data_publisher"), current_index_(0), waiting_for_ack_(false)
    {
        // QoS molto robuste per garantire la consegna
        auto qos = rclcpp::QoS(rclcpp::KeepLast(1))
            .reliable()
            .transient_local()  // Mantiene l'ultimo messaggio per late joiners
            .deadline(std::chrono::seconds(30))
            .lifespan(std::chrono::seconds(60));

        publisher_ = this->create_publisher<latency_test_pkg::msg::LargeData>(
            "large_data_topic", qos);

        // Subscriber per ACK
        ack_subscription_ = this->create_subscription<latency_test_pkg::msg::LargeDataAck>(
            "large_data_ack",
            qos,
            std::bind(&LargeDataPublisher::ack_callback, this, std::placeholders::_1));

        sizes_mb_ = {1, 5, 10};

        // Timer per pubblicare ogni 5 secondi
        timer_ = this->create_wall_timer(
            5s, std::bind(&LargeDataPublisher::publish_message, this));

        RCLCPP_INFO(this->get_logger(), "Publisher inizializzato.");
        RCLCPP_INFO(this->get_logger(), "Testando dimensioni: 1MB, 5MB, 10MB");
        RCLCPP_INFO(this->get_logger(), "Attendendo subscriber...");
    }

private:
    void ack_callback(const latency_test_pkg::msg::LargeDataAck::SharedPtr msg)
    {
        if (msg->received && msg->size_mb == sizes_mb_[current_index_]) {
            RCLCPP_INFO(this->get_logger(), 
                "✓ ACK ricevuto per messaggio di %lu MB", msg->size_mb);
            waiting_for_ack_ = false;
            current_index_++;
        }
    }

    void publish_message()
    {
        // Se stiamo ancora aspettando un ACK, non inviare il prossimo
        if (waiting_for_ack_) {
            RCLCPP_WARN(this->get_logger(), "Ancora in attesa di ACK...");
            return;
        }

        if (current_index_ >= sizes_mb_.size()) {
            RCLCPP_INFO(this->get_logger(), "✓ Test completato con successo!");
            rclcpp::shutdown();
            return;
        }

        uint64_t size_mb = sizes_mb_[current_index_];
        size_t size_bytes = size_mb * 1024 * 1024;

        auto message = latency_test_pkg::msg::LargeData();
        message.header.stamp = this->now();
        message.size_mb = size_mb;

        RCLCPP_INFO(this->get_logger(), "Preparazione dati di %lu MB...", size_mb);
        
        message.data.resize(size_bytes);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);
        
        for (size_t i = 0; i < size_bytes; ++i) {
            message.data[i] = static_cast<uint8_t>(dis(gen));
        }

        RCLCPP_INFO(this->get_logger(), 
            ">>> Invio messaggio %zu/%zu di %lu MB (%zu bytes)...", 
            current_index_ + 1, sizes_mb_.size(), size_mb, size_bytes);

        auto start = std::chrono::high_resolution_clock::now();
        publisher_->publish(message);
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        RCLCPP_INFO(this->get_logger(), 
            "Messaggio pubblicato in %ld ms", duration.count());
        RCLCPP_INFO(this->get_logger(), "Attendendo ACK...");
        
        waiting_for_ack_ = true;
    }

    rclcpp::Publisher<latency_test_pkg::msg::LargeData>::SharedPtr publisher_;
    rclcpp::Subscription<latency_test_pkg::msg::LargeDataAck>::SharedPtr ack_subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::vector<uint64_t> sizes_mb_;
    size_t current_index_;
    bool waiting_for_ack_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LargeDataPublisher>());
    rclcpp::shutdown();
    return 0;
}