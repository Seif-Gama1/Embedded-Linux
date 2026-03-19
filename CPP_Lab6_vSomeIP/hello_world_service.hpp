#include <vsomeip/vsomeip.hpp>
#include "GPIO.h" // Include your header


#define LOG_INF(...) fprintf(stdout, __VA_ARGS__), fprintf(stdout, "\n")
#define LOG_ERR(...) fprintf(stderr, __VA_ARGS__), fprintf(stderr, "\n")

// --- Service IDs (Must match Client JSON) ---
static vsomeip::service_t service_id = 0x1111;
static vsomeip::instance_t service_instance_id = 0x2222;
static vsomeip::method_t service_method_id = 0x3333;

class hello_world_service {
public:
    hello_world_service() : 
        rtm_(vsomeip::runtime::get()),
        app_(rtm_->create_application()),
        led(538) // Initialize your specific pin here
    {
        led.setDirection("out");
    }

    bool init() {
        if (!app_->init()) return false;

        app_->register_message_handler(service_id, service_instance_id, service_method_id,
            std::bind(&hello_world_service::on_message, this, std::placeholders::_1));
        
        app_->offer_service(service_id, service_instance_id);
        return true;
    }

    void start() { app_->start(); }
    void stop() {
        app_->stop();
        LOG_INF("Service stopped.");
    }
    void on_message(const std::shared_ptr<vsomeip::message> &_request) {
        // 1. Get data from payload (expecting 1 byte: 0 or 1)
        std::shared_ptr<vsomeip::payload> its_payload = _request->get_payload();
        vsomeip::byte_t led_command = its_payload->get_data()[0];

        // 2. Control the Hardware
        if (led_command == 1) {
            led.setValue(1);
            LOG_INF("LED Turned ON");
        } else {
            led.setValue(0);
            LOG_INF("LED Turned OFF");
        }

        // 3. Send Response back to PC
        std::shared_ptr<vsomeip::message> its_response = rtm_->create_response(_request);
        std::shared_ptr<vsomeip::payload> its_response_payload = rtm_->create_payload();
        
        std::string msg = (led_command == 1) ? "ACK: ON" : "ACK: OFF";
        std::vector<vsomeip::byte_t> its_payload_data(msg.begin(), msg.end());
        
        its_response_payload->set_data(its_payload_data);
        its_response->set_payload(its_response_payload);
        app_->send(its_response);
    }

private:
    std::shared_ptr<vsomeip::runtime> rtm_;
    std::shared_ptr<vsomeip::application> app_;
    Gpio led; // Your GPIO object
};