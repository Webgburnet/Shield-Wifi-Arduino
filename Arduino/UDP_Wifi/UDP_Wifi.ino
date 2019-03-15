/*
  Chaîne d'envoi et de réception WiFi UDP

 Cette esquisse attend un paquet UDP sur LocalPort à l’aide d’un bouclier WiFi.
 Lorsqu'un paquet est reçu, un paquet d'accusé de réception est envoyé au client sur le port remotePort

 Circuit:
 * Shield Wifi
*/


#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>

int status = WL_IDLE_STATUS;
char ssid[] = "TonWifi"; 				// Nom du réseau wifi
char pass[] = "secretPassword";    		// votre mot de passe réseau wifi(utilisez pour WPA ou comme clé pour WEP)
int keyIndex = 0;            			// votre numéro d'index de clé de réseau (nécessaire uniquement pour WEP)

unsigned int localPort = 2390;      	// port local sur lequel écouter

char packetBuffer[255]; 				// buffer pour contenir le paquet entrant
char  ReplyBuffer[] = "acknowledged";  	// une chaîne à renvoyer

WiFiUDP Udp;

void setup() {
  // Initialise le port série et attend que le port s'ouvre :
  Serial.begin(9600);
  while (!Serial) {
    ; // // attend que le port série se connecte. Nécessaire pour le port USB natif uniquement
  }

  // vérifie la présence du Shield :
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Shield WiFi non present");
    // ne continue pas :
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("S'il vous plaît mettre à jour le firmware.");
  }

  // tentative de connexion au réseau Wifi :
  while (status != WL_CONNECTED) {
    Serial.print("Tentative de connexion au SSID : ");
    Serial.println(ssid);
    // Connexion au réseau WPA / WPA2. Modifiez cette ligne si vous utilisez un réseau ouvert ou WEP
    status = WiFi.begin(ssid);

    // attendez 10 secondes pour la connexion :
    delay(10000);
  }
  Serial.println("Connecté au wifi ! ");
  printWifiStatus();

  Serial.println("\n Démarrage de la connexion au serveur ...");
  // si vous avez une connexion, faites un rapport via serial:
  Udp.begin(localPort);
}

void loop() {

  // s'il y a des données disponibles, lit un paquet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Paquet reçu de taille : ");
    Serial.println(packetSize);
    Serial.print("Adresse IP de  ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", sur le port ");
    Serial.println(Udp.remotePort());

    // lit le paquet dans packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println("Contenu : ");
    Serial.println(packetBuffer);

    // envoie une réponse à l'adresse IP et au port qui nous a envoyé le paquet que nous avons reçu
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
}


void printWifiStatus() {
  // affiche le SSID du réseau auquel vous êtes connecté :
  Serial.print("SSID : ");
  Serial.println(WiFi.SSID());

  // affiche l'adresse IP du Shield WiFi :
  IPAddress ip = WiFi.localIP();
  Serial.print("Addresse IP : ");
  Serial.println(ip);

  // affiche la longeur du signal reçu :
  long rssi = WiFi.RSSI();
  Serial.print("longeur du Signal (RSSI) : ");
  Serial.print(rssi);
  Serial.println(" dBm");
}