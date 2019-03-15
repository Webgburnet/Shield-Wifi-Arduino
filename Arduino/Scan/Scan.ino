#include <SPI.h>
#include <WiFi.h>

void setup() {
// initialise le port série et attend que le port s'ouvre:
  Serial.begin(9600);
  while(!Serial) ;

// tentative de connexion en utilisant le cryptage WEP:
  Serial.println("Initisation Wifi...");
  printMacAddress();

// recherche les réseaux existants:
  Serial.println("Analyse des réseaux disponibles ...");
  listNetworks();
}

void loop() {
  delay(10000);
  // scan for existing networks:
  Serial.println("Analyse des réseaux disponibles ...");
  listNetworks();
}

void printMacAddress() {
// l'adresse MAC du Shield Wifi
  byte mac[6];                    

// affiche adresse MAC:
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
}

void listNetworks() {
// recherche les réseaux proches :
  Serial.println("** Analyses Réseaux **");
  byte numSsid = WiFi.scanNetworks();

// affiche la liste des réseaux vus :
  Serial.print("nombre de réseaux disponibles : ");
  Serial.println(numSsid);

// affiche le numéro et le nom du réseau pour chaque réseau trouvé :
  for (int thisNet = 0; thisNet<numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
    Serial.println(WiFi.encryptionType(thisNet));
  }
}
