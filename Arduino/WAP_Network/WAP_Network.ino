#include <WiFi.h>

char ssid[] = "Sti-2k18-SIN";      // Le nom du réseau wifi
char pass[] = "Sti-2k18-Sin";        // Mot de passe du réseau wifi
int status = WL_IDLE_STATUS;     // le statut de la radio Wifi
IPAddress ip_shield;

void setup() {
  // initialise le moniteur série:
  Serial.begin(9600);

  // tentative de connexion à un réseau ouvert:
  Serial.println("Tentative de connexion pour ouvrir un réseau ...");
  status = WiFi.begin(ssid, pass);
  ip_shield = WiFi.localIP();
  //WiFi.config(ip_shield);
  // si vous n'êtes pas connecté, arrêtez-vous ici:
  if ( status != WL_CONNECTED) {
    Serial.println("Impossible d'obtenir une connexion wifi ! ");
    while(true);
  }
  // si vous êtes connecté:
  else {
      Serial.print("Adresse IP : ");
      Serial.println(WiFi.localIP());
      Serial.println("Connecté au réseau");
  }
}

void loop() {
  // Ne rien faire
}
