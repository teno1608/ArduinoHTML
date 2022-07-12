/*
Build by fairy-elab: 19-02-2021
*/

#include <WiFi.h>

const char *ssid = "AcePoi19216841";
const char *password = "0987654321";

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");
  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");
}

void loop()
{

  WiFiClient client = server.available();
  Serial.println(server.available());
  Serial.println(client);

  if (client)
  {                                // if you get a client,
    Serial.println("New Client."); // print a message out the serial port
    String currentLine = "";       // make a String to hold incoming data from the client

    while (client.connected()) // loop while the client's connected
    {
      if (client.available()) // if there's bytes to read from the client,
      {
        char c = client.read(); // read a byte, then
        Serial.write(c);
        if (c == '\n') // if the byte is a newline character
        {
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            Serial.println("end reading");
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            //break;
            client.stop();
            Serial.println("Client Disconnected.");
          }
          else
          { // if you got a newline, then clear currentLine:
            currentLine = "";
            Serial.println("end line");
          }
        }
        else if (c != '\r')
        {
          currentLine += c; // add it to the end of the currentLine
        }
      }
    }
  }

  delay(1000);
}