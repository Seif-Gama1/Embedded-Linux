// Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <vsomeip/vsomeip.hpp>

#if defined ANDROID || defined __ANDROID__
#include "android/log.h"
#define LOG_TAG "hello_world_client"
#define LOG_INF(...) fprintf(stdout, __VA_ARGS__), fprintf(stdout, "\n"), (void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, ##__VA_ARGS__)
#define LOG_ERR(...) fprintf(stderr, __VA_ARGS__), fprintf(stderr, "\n"), (void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, ##__VA_ARGS__)
#else
#include <cstdio>
#include <atomic>
#define LOG_INF(...) fprintf(stdout, __VA_ARGS__), fprintf(stdout, "\n")
#define LOG_ERR(...) fprintf(stderr, __VA_ARGS__), fprintf(stderr, "\n")
#endif

static vsomeip::service_t service_id = 0x1111;
static vsomeip::instance_t service_instance_id = 0x2222;
static vsomeip::method_t service_method_id = 0x3333;

class hello_world_client {
public:
    bool is_available() const {
        return is_service_available;
    }
    // Get the vSomeIP runtime and
    // create a application via the runtime, we could pass the application name
    // here otherwise the name supplied via the VSOMEIP_APPLICATION_NAME
    // environment variable is useds
    hello_world_client() :
                    rtm_(vsomeip::runtime::get()),
                    app_(rtm_->create_application())
    {
    }

    bool init(){
        // init the application
        if (!app_->init()) {
            LOG_ERR ("Couldn't initialize application");
            return false;
        }

        // register a state handler to get called back after registration at the
        // runtime was successful
        app_->register_state_handler(
                std::bind(&hello_world_client::on_state_cbk, this,
                        std::placeholders::_1));

        // register a callback for responses from the service
        // app_->register_message_handler(vsomeip::ANY_SERVICE,
        //         service_instance_id, vsomeip::ANY_METHOD,
        //         std::bind(&hello_world_client::on_message_cbk, this,
        //                 std::placeholders::_1));

        app_->register_message_handler(
                    service_id,           // Specific Service 0x1111
                    service_instance_id,  // Specific Instance 0x2222
                    service_method_id,    // Specific Method 0x3333
                    std::bind(&hello_world_client::on_message_cbk, this,
                            std::placeholders::_1));

        // register a callback which is called as soon as the service is available
        app_->register_availability_handler(service_id, service_instance_id,
                std::bind(&hello_world_client::on_availability_cbk, this,
                        std::placeholders::_1, std::placeholders::_2,
                        std::placeholders::_3));
        return true;
    }

    void start()
    {
        // start the application and wait for the on_event callback to be called
        // this method only returns when app_->stop() is called
        app_->start();
    }

    void on_state_cbk(vsomeip::state_type_e _state)
    {
        if(_state == vsomeip::state_type_e::ST_REGISTERED)
        {
            // we are registered at the runtime now we can request the service
            // and wait for the on_availability callback to be called
            app_->request_service(service_id, service_instance_id);
        }
    }

    /* this is the client invoking the service, after the server already offered it */
    void on_availability_cbk(vsomeip::service_t _service, 
                            vsomeip::instance_t _instance, bool _is_available) {
        if(service_id == _service && service_instance_id == _instance) {
            is_service_available = _is_available; // Store state
            if (_is_available) {
                LOG_INF("Service is ready! Waiting for Caps Lock...");
            } else {
                LOG_INF("Service lost.");
            }
        }
    }

    void send_led_event(bool led_state) {
        // 1. Create the request object
        std::shared_ptr<vsomeip::message> rq = vsomeip::runtime::get()->create_request();
        
        // 2. Set the destination (The Pi Service)
        rq->set_service(service_id);
        rq->set_instance(service_instance_id);
        rq->set_method(service_method_id);

        // 3. Create the payload (0 for OFF, 1 for ON)
        std::shared_ptr<vsomeip::payload> pl = vsomeip::runtime::get()->create_payload();
        std::vector<vsomeip::byte_t> data;
        data.push_back(led_state ? 1 : 0); 
        
        pl->set_data(data);
        rq->set_payload(pl);

        // 4. Actually push it to the network
        app_->send(rq);
        
        LOG_INF("Client sent LED state: %s", led_state ? "ON" : "OFF");
    }

    /* this is the function invoked when the server sends response to client */
    void on_message_cbk(const std::shared_ptr<vsomeip::message> &_response) {
        // Keep the checks to ensure the message is for us
        if(service_id == _response->get_service() && 
        vsomeip::return_code_e::E_OK == _response->get_return_code()) {
            
            std::shared_ptr<vsomeip::payload> pl = _response->get_payload();
            // Print the response from the Pi (e.g., "LED ON ACK")
            LOG_INF("Pi Confirmation: %s", reinterpret_cast<const char*>(pl->get_data()));
            
            // REMOVED: stop(); <-- This keeps the client alive indefinitely
        }
    }

    void stop()
    {
        // unregister the state handler
        app_->unregister_state_handler();
        // unregister the message handler
        app_->unregister_message_handler(vsomeip::ANY_SERVICE,
                service_instance_id, vsomeip::ANY_METHOD);
        // alternatively unregister all registered handlers at once
        app_->clear_all_handler();
        // release the service
        app_->release_service(service_id, service_instance_id);
        // shutdown the application
        app_->stop();
    }

private:
    std::shared_ptr<vsomeip::runtime> rtm_;
    std::shared_ptr<vsomeip::application> app_;
    std::atomic<bool> is_service_available{false};
};
