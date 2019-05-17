//CHIAKI-chan
//2017.05.01


#include <SoftwareSerial.h>
#define BAUD_RATE 57600
SoftwareSerial swSer(14, 14, false, 256);

#include <ArduinoOSC.h>
// WiFi stuff
const char* ssid = "MATHRAX_SUB";
const char* pwd = "remokuma";
const IPAddress ip(192, 168, 1, 201);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

// for ArduinoOSC
OscWiFi osc;
const char* host = "192.168.1.14";
const int recv_port = 10000;
const int send_port = 12000;

void onOscReceived(OscMessage& m)
{
  Serial.print("callback : ");
  Serial.print(m.ip()); Serial.print(" ");
  Serial.print(m.port()); Serial.print(" ");
  Serial.print(m.size()); Serial.print(" ");
  Serial.print(m.address()); Serial.print(" ");
  Serial.print(m.arg<int>(0)); Serial.print(" ");
  Serial.print(m.arg<float>(1)); Serial.print(" ");
  Serial.print(m.arg<String>(2)); Serial.println();
}

void setup() {
  Serial.begin(115200);
  swSer.begin(BAUD_RATE);

  swSer.write(static_cast<uint8_t>(0));
  Serial.println("\nSoftware serial test started");

  for (char ch = ' '; ch <= 'z'; ch++) {
    swSer.write(ch);
  }
  swSer.println("");

  // WiFi stuff
  WiFi.begin(ssid, pwd);
  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("WiFi connected, IP = "); Serial.println(WiFi.localIP());

  // ArduinoOSC
  osc.begin(recv_port);
}


unsigned char datapos;
unsigned char buf[20];

void loop() {
  unsigned char t1, t2, t3, t4, t5;


  while (swSer.available() > 0) {
    unsigned char rcvdata = (swSer.read() & 0xFF);

    if (rcvdata == 255) {
      datapos = 0;
    } else {
      buf[datapos] = rcvdata;
      datapos++;
    }

    yield();
  }
  if (datapos >= 4) {
    t1 = buf[0];
    t2 = buf[1];
    t3 = buf[2];
    t4 = buf[3];
    t5 = buf[4];
    
    Serial.print(t1);
    Serial.print("\t,");
    Serial.print(t2);
    Serial.print("\t,");
    Serial.print(t3);
    Serial.print("\t,");
    Serial.print(t4);
    Serial.print("\t,");
    Serial.print(t5);
    Serial.println("\t,");

    osc.send(host, send_port, "/data", t1, t2, t3, t4, t5);
  }


  osc.parse(); // should be called
}
