#include <Arduino.h>
#include "EspMQTTClient.h"
#include <Arduino_JSON.h>
#include <Preferences.h>

#ifndef MQTT_DATA_CLIENT
#define MQTT_DATA_CLIENT


class MQTTDataClient : public EspMQTTClient
{
  using EspMQTTClient::EspMQTTClient;
  String dataTopic;
  bool storePermanent = false;
  Preferences* preferences = null;

  public:
    JSONVar data;
    void SetDataTopic(String topic);
    void SaveData(String name, JSONVar d);
    void SetStorePermanent(Preferences* prefs);
    JSONVar LoadData(String name);
    JSONVar GetData(String name){return this->data[name];}
    // void SavePermanent(String name, JSONVar d);
};

// JSON_Compare(JSONVar)

#endif
