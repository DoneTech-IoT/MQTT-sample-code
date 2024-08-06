idf_component_register(SRCS "libMQTT.a"
                    INCLUDE_DIRS "include"
                    REQUIRES mqtt esp_event mbedtls nvs_flash json ) 

# Path to the static library
set(MQTT_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libMQTT.a)
                    
# Add the prebuilt static library
add_prebuilt_library(MQTT ${MQTT_LIBRARY_PATH} 
                     REQUIRES mqtt esp_event mbedtls nvs_flash json ) 
                    
# Link the prebuilt library to the component
target_link_libraries(${COMPONENT_LIB} INTERFACE MQTT)



