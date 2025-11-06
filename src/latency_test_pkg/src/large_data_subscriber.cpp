#include <chrono>
#include <memory>
#include <vector>
#include <iomanip>
#include "rclcpp/rclcpp.hpp"
#include "latency_test_pkg/msg/large_data.hpp"
#include "latency_test_pkg/msg/large_data_ack.hpp"

struct LatencyResult {
    uint64_t size_mb;
    double latency_seconds;
    size_t bytes_received;
    std::chrono::system_clock::time_point receive_time;
};

class LargeDataSubscriber : public rclcpp::Node
{
public:
    LargeDataSubscriber() : Node("large_data_subscriber")
    {
        // QoS molto robuste per garantire la ricezione
        auto qos = rclcpp::QoS(rclcpp::KeepLast(1))
            .reliable()
            .transient_local()
            .deadline(std::chrono::seconds(30))
            .lifespan(std::chrono::seconds(60));

        subscription_ = this->create_subscription<latency_test_pkg::msg::LargeData>(
            "large_data_topic", 
            qos,
            std::bind(&LargeDataSubscriber::listener_callback, this, std::placeholders::_1));

        // Publisher per ACK
        ack_publisher_ = this->create_publisher<latency_test_pkg::msg::LargeDataAck>(
            "large_data_ack", qos);

        RCLCPP_INFO(this->get_logger(), "Subscriber inizializzato.");
        RCLCPP_INFO(this->get_logger(), "In attesa di messaggi...");
    }

    ~LargeDataSubscriber()
    {
        print_results();
    }

private:
    void listener_callback(const latency_test_pkg::msg::LargeData::SharedPtr msg)
    {
        auto receive_time = this->now();
        auto send_time = rclcpp::Time(msg->header.stamp);
        
        double latency = (receive_time - send_time).seconds();
        
        RCLCPP_INFO(this->get_logger(), "\n========================================");
        RCLCPP_INFO(this->get_logger(), 
            "✓ Ricevuto messaggio di %lu MB", msg->size_mb);
        RCLCPP_INFO(this->get_logger(), 
            "Dimensione dati: %zu bytes", msg->data.size());
        RCLCPP_INFO(this->get_logger(), 
            "Latenza: %.6f secondi (%.2f ms)", 
            latency, latency * 1000.0);
        
        if (latency > 0) {
            RCLCPP_INFO(this->get_logger(), 
                "Throughput: %.2f MB/s", 
                msg->size_mb / latency);
        }
        
        RCLCPP_INFO(this->get_logger(), "========================================");

        // Invia ACK
        auto ack_msg = latency_test_pkg::msg::LargeDataAck();
        ack_msg.size_mb = msg->size_mb;
        ack_msg.received = true;
        ack_publisher_->publish(ack_msg);
        
        RCLCPP_INFO(this->get_logger(), ">>> ACK inviato per %lu MB\n", msg->size_mb);

        // Salva risultati
        LatencyResult result;
        result.size_mb = msg->size_mb;
        result.latency_seconds = latency;
        result.bytes_received = msg->data.size();
        result.receive_time = std::chrono::system_clock::now();
        
        results_.push_back(result);
    }

    void print_results()
    {
        if (results_.empty()) {
            RCLCPP_WARN(this->get_logger(), "Nessun messaggio ricevuto");
            return;
        }

        RCLCPP_INFO(this->get_logger(), "\n\n");
        RCLCPP_INFO(this->get_logger(), "====================================================");
        RCLCPP_INFO(this->get_logger(), "              RIEPILOGO RISULTATI TEST              ");
        RCLCPP_INFO(this->get_logger(), "====================================================");
        
        for (const auto& result : results_) {
            RCLCPP_INFO(this->get_logger(), 
                "Dimensione: %2lu MB | Latenza: %8.6f s (%7.2f ms) | Throughput: %6.2f MB/s",
                result.size_mb,
                result.latency_seconds,
                result.latency_seconds * 1000.0,
                result.size_mb / result.latency_seconds);
        }
        
        RCLCPP_INFO(this->get_logger(), "====================================================");
        
        double total_latency = 0.0;
        for (const auto& result : results_) {
            total_latency += result.latency_seconds;
        }
        double avg_latency = total_latency / results_.size();
        
        RCLCPP_INFO(this->get_logger(), 
            "Latenza media: %.6f secondi (%.2f ms)", 
            avg_latency, avg_latency * 1000.0);
        RCLCPP_INFO(this->get_logger(), 
            "✓ Messaggi ricevuti con successo: %zu/3", results_.size());
        RCLCPP_INFO(this->get_logger(), "====================================================\n");
    }

    rclcpp::Subscription<latency_test_pkg::msg::LargeData>::SharedPtr subscription_;
    rclcpp::Publisher<latency_test_pkg::msg::LargeDataAck>::SharedPtr ack_publisher_;
    std::vector<LatencyResult> results_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LargeDataSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}