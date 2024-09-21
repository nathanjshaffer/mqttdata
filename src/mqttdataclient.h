
#include "EspMQTTClient.h"

class MQTTDataClient : public EspMQTTClient
{
  using EspMQTTClient::EspMQTTClient;

  String deviceId;

  void SetDeviceId(string id){deviceId = id;}

  void RegisterDataStore(String name);
}
