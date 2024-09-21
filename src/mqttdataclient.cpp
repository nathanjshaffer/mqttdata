#include "mqttdataclient.h"


void MQTTDataClient::SetDeviceId(string id){deviceId = id;}
{
  subscribe(codeTopic + "/+/command", [] (const String& topic, const String& message)
  {
    String name = topic.substring(codeTopic.length() + 1, topic.length() - 8);
    Serial.print(name);
    
    JSONVar cmd = JSON.parse(message)
    // JsonDocument doc;
    // 
    // // Deserialize the JSON document
    // DeserializationError error = deserializeJson(doc, message);
    // 
    // // Test if parsing succeeds.
    // if (error) {
    //   Serial.print(F("deserializeJson() failed: "));
    //   Serial.println(error.f_str());
    //   return;
    // }

    if (cmd["cmd"] == "update")
    {
      data[name] = cmd["data"];
    }
  });
}