#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// PIN on has connectat el cable de dades (DIN)
#define PIN 2 

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

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40); // Compte amb el consum! 40 és un bon valor per USB.
  matrix.setTextColor(colors[0]);
}

int x = matrix.width();
int pass = 0;

void loop() {
  matrix.fillScreen(0);    // Esborra la pantalla
  matrix.setCursor(x, 0);
  matrix.print(F("VA DEVELOPERS!!"));

  // Moviment del text cap a l'esquerra
  if(--x < -90) { // El número -90 depèn de la llargada del text
    x = matrix.width();
    if(++pass >= 4) pass = 0;
    matrix.setTextColor(colors[pass]); // Canvia el color en cada volta
  }
  
  matrix.show();
  delay(100); // Velocitat del desplaçament
}
