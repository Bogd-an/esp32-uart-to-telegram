#include <Arduino.h>
#include <WiFi.h>
#include <HardwareSerial.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Налаштування Wi-Fi
#define WIFI_SSID     "Firelink Shrine"
#define WIFI_PASSWORD "over the moon"

// Налаштування Telegram
#define BOT_TOKEN "7066871593:AAGYf9bp5VPSSoE2D8FbzlQB6N98-mkusxc"
#define CHAT_ID "-4146045456"

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  Serial.println();

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
    digitalWrite(2, !digitalRead(2));
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
  bot.sendMessage(CHAT_ID, "0 online", "");
}

void loop()
{
  // Читання даних з Serial
  if (Serial.available() > 0) {
    digitalWrite(2, 1);
    String message = Serial.readStringUntil('\n'); // читання рядка з Serial до символу нового рядка
    // Відправка отриманого повідомлення у Telegram
    bot.sendMessage(CHAT_ID, message, "");
  }
  digitalWrite(2, 0);
}
// void handleNewMessages(int numNewMessages)
// {
//   for (int i = 0; i < numNewMessages; i++)
//   {
//     bot.sendMessage(bot.messages[i].chat_id, bot.messages[i].text, "");
//   }
// }
// void echoLoop(){
//   if (millis() - bot_lasttime > BOT_MTBS)
//   {
//     int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

//     while (numNewMessages)
//     {
//       Serial.println("got response");
//       handleNewMessages(numNewMessages);
//       numNewMessages = bot.getUpdates(bot.last_message_received + 1);
//     }

//     bot_lasttime = millis();
//   }
// }