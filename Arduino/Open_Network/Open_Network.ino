#include <WiFi.h>

char ssid[] = "Sti-2k18-SIN";      // Le nom du réseau
int status = WL_IDLE_STATUS;     // le statut de la radio Wifi

void setup() {
  // initialise le moniteur série:
  Serial.begin(9600);

  // tentative de connexion à un réseau ouvert:
  Serial.println("Tentative de connexion pour ouvrir un réseau ...");
  status = WiFi.begin(ssid);

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
