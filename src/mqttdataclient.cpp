#include "PubSubClient.h"
#include "mqttdataclient.h"


void MQTTDataClient::SetDataTopic(String topic)
{
  this->dataTopic = topic;
  // this->data = JSON.parse("{}");
  
  setMaxPacketSize(1028);
  subscribe(this->dataTopic + "/dataclient/update", [this] (const String& topic, const String& message)
  {
    Serial.println(message.length());
    JSONVar cmd = JSON.parse(message);

    if (cmd.hasOwnProperty("name") && cmd.hasOwnProperty("data"))
    {
      String name = cmd["name"];
      this->SaveData(name, cmd["data"]);
    }
  });


  subscribe(this->dataTopic + "/dataclient/get", [this] (const String& topic, const String& message)
  {
    JSONVar cmd = JSON.parse(message);
    if (cmd.hasOwnProperty("name"))
    {
      String name = cmd["name"];
      JSONVar response;
      response["name"] = name;
      response["data"] = LoadData(name);
      publish(this->dataTopic + "/dataclient/data",  JSON.stringify(response));
    }
  });
}

void MQTTDataClient::SetStorePermanent(Preferences* prefs)
{
  storePermanent = true;
  preferences = prefs;
}

void MQTTDataClient::SaveData(String name, JSONVar d)
{
  if (this->data.hasOwnProperty(name))
  {
    if(this->data[name] == d) return;
  }
  this->data[name] = d;
  if(storePermanent && this->preferences != null)
  {
    this->preferences->putString(name.c_str(), JSON.stringify(d));
  }
}

JSONVar MQTTDataClient::LoadData(String name)
{
  if (!this->data.hasOwnProperty(name) && storePermanent && this->preferences != null)
  {
    this->data[name] = JSON.parse(this->preferences->getString(name.c_str()));
  }
  return this->data[name]; 
}