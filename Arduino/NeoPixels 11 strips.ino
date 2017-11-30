/*
  Sketch arduino por Waldo Costa
  http://www.waldocosta.com.br
  atualizado em: 2017 nov 11

  Baseado parcialmente no sketch de Tom Igoe disponível em:
  http://www.arduino.cc/en/Tutorial/SerialEvent
*/

#include <Adafruit_NeoPixel.h>

int BRILHO  =  50;  // valor entre 0 e 255
int PIXEL_COUNT = 15;  // numero de pixels em cada LED strip

int indice_i = 0;
int indice_j = 0;     // índices para a matriz das cores

// valores iniciais para vermelho, verde e azul
byte vermelho[11][15] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

byte verde[11][15] = {
  {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
  {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
  {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
  {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
  {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
  {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
  {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
  {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
  {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
  {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
  {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255}
};

byte azul[11][15] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(PIXEL_COUNT, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(PIXEL_COUNT, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(PIXEL_COUNT, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(PIXEL_COUNT, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(PIXEL_COUNT, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(PIXEL_COUNT, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(PIXEL_COUNT, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(PIXEL_COUNT, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip9 = Adafruit_NeoPixel(PIXEL_COUNT, 10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip10 = Adafruit_NeoPixel(PIXEL_COUNT, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip11 = Adafruit_NeoPixel(PIXEL_COUNT, 12, NEO_GRB + NEO_KHZ800);



void setup() {

  // initialize serial:
  Serial.begin(9600);


  strip1.setBrightness(BRILHO);
  strip1.begin();
  strip1.show();
  strip2.setBrightness(BRILHO);
  strip2.begin();
  strip2.show();
  strip3.setBrightness(BRILHO);
  strip3.begin();
  strip3.show();
  strip4.setBrightness(BRILHO);
  strip4.begin();
  strip4.show();
  strip5.setBrightness(BRILHO);
  strip5.begin();
  strip5.show();
  strip6.setBrightness(BRILHO);
  strip6.begin();
  strip6.show();
  strip7.setBrightness(BRILHO);
  strip7.begin();
  strip7.show();
  strip8.setBrightness(BRILHO);
  strip8.begin();
  strip8.show();
  strip9.setBrightness(BRILHO);
  strip9.begin();
  strip9.show();
  strip10.setBrightness(BRILHO);
  strip10.begin();
  strip10.show();
  strip11.setBrightness(BRILHO);
  strip11.begin();
  strip11.show();

}

void loop() {

  while (Serial.available() > 0) {

    indice_j = Serial.parseInt();
    indice_i = Serial.parseInt();
    int red = Serial.parseInt();
    int green = Serial.parseInt();
    int blue = Serial.parseInt();

    if (Serial.read() == '\n') {
      vermelho[indice_i][indice_j] = red;
      verde[indice_i][indice_j]    = green;
      azul[indice_i][indice_j]     = blue;
    }
  }

  for (byte k = 0; k < PIXEL_COUNT; k++) {

    strip1.setPixelColor(k, strip1.Color(vermelho[0][k], verde[0][k], azul[0][k])); //
    strip1.show();

    strip2.setPixelColor(k, strip2.Color(vermelho[1][k], verde[1][k], azul[1][k])); //
    strip2.show();

    strip3.setPixelColor(k, strip3.Color(vermelho[2][k], verde[2][k], azul[2][k])); //
    strip3.show();

    strip4.setPixelColor(k, strip4.Color(vermelho[3][k], verde[3][k], azul[3][k])); //
    strip4.show();

    strip5.setPixelColor(k, strip5.Color(vermelho[4][k], verde[4][k], azul[4][k])); //
    strip5.show();

    strip6.setPixelColor(k, strip6.Color(vermelho[5][k], verde[5][k], azul[5][k])); //
    strip6.show();

    strip7.setPixelColor(k, strip7.Color(vermelho[6][k], verde[6][k], azul[6][k])); //
    strip7.show();

    strip8.setPixelColor(k, strip8.Color(vermelho[7][k], verde[7][k], azul[7][k])); //
    strip8.show();

    strip9.setPixelColor(k, strip9.Color(vermelho[8][k], verde[8][k], azul[8][k])); //
    strip9.show();

    strip10.setPixelColor(k, strip10.Color(vermelho[9][k], verde[9][k], azul[9][k])); //
    strip10.show();

    strip11.setPixelColor(k, strip11.Color(vermelho[10][k], verde[10][k], azul[10][k])); //
    strip11.show();
  }

}//fim do loop



