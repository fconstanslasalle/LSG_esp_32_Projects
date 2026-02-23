#include <FastLED.h>

#define LED_PIN     2          // Pin de datos
#define NUM_LEDS    256        // 8 x 32 = 256 LEDs
#define BRIGHTNESS  50         // Brillo (0-255)
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

// Definimos los rangos de columnas para cada color
// Bloque 1 (0-7): Rojo | Bloque 2 (8-15): Vacío | Bloque 3 (16-23): Amarillo | Bloque 4 (24-31): Verde

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // 1. ROJO
  encenderBloque(0, 7, CRGB::Red);
  FastLED.show();
  delay(5000); // 5 segundos en rojo

  // 2. VERDE
  FastLED.clear();
  encenderBloque(24, 31, CRGB::Green);
  FastLED.show();
  delay(5000); // 5 segundos en verde

  // 3. AMARILLO (Parpadeo antes de cambiar a rojo)
  FastLED.clear();
  for(int i = 0; i < 3; i++) {
    encenderBloque(16, 23, CRGB::Yellow);
    FastLED.show();
    delay(600);
    encenderBloque(16, 23, CRGB::Black);
    FastLED.show();
    delay(400);
  }
}

// Función auxiliar para iluminar secciones de la matriz
void encenderBloque(int colInicio, int colFin, CRGB color) {
  // Cada columna tiene 8 LEDs
  for (int col = colInicio; col <= colFin; col++) {
    for (int fila = 0; fila < 8; fila++) {
      int pixel = (col * 8) + fila; 
      leds[pixel] = color;
    }
  }
}
