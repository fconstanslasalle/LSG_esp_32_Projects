#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// --- Configuració Wi-Fi ---
const char* ssid = "LSG-CFGS";
const char* password = "CFGS-L@S@lleGr@ci@";
WebServer server(80);
String missatge = "ESPERANT DADES...";


// PIN on has connectat el cable de dades (DIN)
#define PIN 13 

// Configuració de la matriu:
// 8 de llarg, 32 d'ample. Si el text surt del revés o en vertical, 
// haurem d'ajustar els paràmetres de 'NEO_MATRIX_...'
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0),   // Vermell
  matrix.Color(0, 255, 0),   // Verd
  matrix.Color(0, 0, 255),   // Blau
  matrix.Color(255, 255, 0)  // Groc
};

int x;
int pass = 0;

void handleUpdate() {
  if (server.hasArg("msg")) {
    missatge = server.arg("msg");
    missatge.toUpperCase(); // Opcional: tot en majúscules
    x = matrix.width();     // Reinicia la posició del text
    server.send(200, "text/plain", "Missatge rebut!");
  } else {
    server.send(400, "text/plain", "Falta el paràmetre 'msg'");
  }
}

void setup() {
  Serial.begin(115200);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40); // Compte amb el consum! 40 és un bon valor per USB.
  matrix.setTextColor(colors[0]);
  x = matrix.width();
  // Connexió Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnectat! IP:");
  Serial.println(WiFi.localIP()); // IMPORTANT: Mira aquesta IP al monitor sèrie

  server.on("/update", handleUpdate);
  server.begin();
  
}

void loop() {
  server.handleClient(); // Gestiona les peticions PHP

  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(missatge);

  // Calculem la longitud aproximada (cada lletra uns 6 píxels)
  int longitud = missatge.length() * -6;

  if(--x < longitud) {
    x = matrix.width();
    if(++pass >= 4) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  
  matrix.show();
  delay(50); // Una mica més ràpid per millorar la fluïdesa
}
