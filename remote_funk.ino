#include <C:\Users\Mario\Desktop\DLN Projekt\remote_funk\ESP8266TelegramBOT.h>
#define BOT_TOKEN "AAH3dr3OGQ7665wkoMN25LiPOjKQ5nliyGY"

uint32_t lastTime;
TelegramBOT bot(BOT_TOKEN, "ESP8266_electricity_bot", "ESP8266_electricity_bot");

char ssid[] = "Vodafone-C0A4";
char pwd[] = "7777111177771111";

int codes_A[] = {};
int codes_B[] = {};
int codes_C[] = {};

void setup() {
  Serial.begin(115200);

  connect2Wifi();
  bot.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void connect2Wifi(){
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nWiFi connected.");
}

void checkMessages(){
  uint32_t now = millis();
  if(now - lastTime < 1000){
    Serial.println("update..");
    bot.getUpdates(bot.message[0][1]);
    int numNewMessages = bot.message[0][0].toInt();
    for(int i = 0; i < numNewMessages; i++){
      String chatId = bot.message[i][4];
      String message = bot.message[i][5];
      handleMessage(message, chatId);
    }
  }
  lastTime = now;
}

void handleMessage(String message, String chatId){
  if(message.equalsIgnoreCase("/start")){
    sendMessage(handleStartCommand(), chatId);
  }else{
    Serial.print("Msg: " + message);
  }
}

String handleStartCommand(){
  String response = "Available commands:";
  response += "A_on, A_off\n\r";
  response += "B_on, B_off\n\r";
  response += "C_on, C_off\n\r";
  response += "All_on, All_off";

  return response;
}

void sendMessage(String message, String chatId){
  Serial.println("Sending message...");
  Serial.print(chatId);
  Serial.print("----");
  Serial.println(message);
  bot.sendMessage(chatId, message, "");
}
