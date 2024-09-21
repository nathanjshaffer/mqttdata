#include <Arduino.h>
#include "EspMQTTClient.h"
#include <Arduino_JSON.h>



class MQTTDataClient : public EspMQTTClient
{
  using EspMQTTClient::EspMQTTClient;

  String deviceId;
  JSONVar data;

  void SetDeviceId(string id){deviceId = id;}
}

