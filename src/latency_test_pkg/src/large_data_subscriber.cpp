#include <chrono>
#include <memory>
#include <vector>
#include <iomanip>
#include "rclcpp/rclcpp.hpp"
#include "latency_test_pkg/msg/large_data.hpp"

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
        // Configura QoS per messaggi grandi con affidabilità garantita
        auto qos = rclcpp::QoS(rclcpp::KeepLast(10))
            .reliable()
            .durability_volatile();

        subscription_ = this->create_subscription<latency_test_pkg::msg::LargeData>(
            "large_data_topic", 
            qos,
            std::bind(&LargeDataSubscriber::listener_callback, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "Subscriber inizializzato. In attesa di messaggi...");
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
        
        // Calcola latenza in secondi
        double latency = (receive_time - send_time).seconds();
        
        RCLCPP_INFO(this->get_logger(), 
            "========================================");
        RCLCPP_INFO(this->get_logger(), 
            "Ricevuto messaggio di %lu MB", msg->size_mb);
        RCLCPP_INFO(this->get_logger(), 
            "Dimensione dati: %zu bytes", msg->data.size());
        RCLCPP_INFO(this->get_logger(), 
            "Latenza: %.6f secondi (%.2f ms)", 
            latency, latency * 1000.0);
        RCLCPP_INFO(this->get_logger(), 
            "Throughput: %.2f MB/s", 
            msg->size_mb / latency);
        RCLCPP_INFO(this->get_logger(), 
            "========================================\n");

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
            RCLCPP_INFO(this->get_logger(), "Nessun messaggio ricevuto");
            return;
        }

        RCLCPP_INFO(this->get_logger(), "\n");
        RCLCPP_INFO(this->get_logger(), "================================================");
        RCLCPP_INFO(this->get_logger(), "           RIEPILOGO RISULTATI TEST             ");
        RCLCPP_INFO(this->get_logger(), "================================================");
        
        for (const auto& result : results_) {
            RCLCPP_INFO(this->get_logger(), 
                "Dimensione: %2lu MB | Latenza: %8.6f s (%7.2f ms) | Throughput: %6.2f MB/s",
                result.size_mb,
                result.latency_seconds,
                result.latency_seconds * 1000.0,
                result.size_mb / result.latency_seconds);
        }
        
        RCLCPP_INFO(this->get_logger(), "================================================");
        
        // Calcola statistiche
        double total_latency = 0.0;
        for (const auto& result : results_) {
            total_latency += result.latency_seconds;
        }
        double avg_latency = total_latency / results_.size();
        
        RCLCPP_INFO(this->get_logger(), 
            "Latenza media: %.6f secondi (%.2f ms)", 
            avg_latency, avg_latency * 1000.0);
        RCLCPP_INFO(this->get_logger(), 
            "Messaggi ricevuti: %zu/%zu", results_.size(), size_t(3));
        RCLCPP_INFO(this->get_logger(), "================================================\n");
    }

    rclcpp::Subscription<latency_test_pkg::msg::LargeData>::SharedPtr subscription_;
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