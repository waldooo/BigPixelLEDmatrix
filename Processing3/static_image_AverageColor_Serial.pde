import processing.serial.*;
Serial myPort;

float[] rx = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
float[] gx = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
float[] bx = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

int count_X = 0;
int count_Y = 0;

int detail = 30; // tamanho do quadrado
int voltas = 0;


void setup() {
  size(440, 320);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  delay(100);
}


void draw() {

  PImage img = loadImage("image.jpg");
  delay(200);
  count_X = 0;
  count_Y = 0;

  for (int j=0; j<height; j+=detail) {
    for (int i=0; i<width; i+=detail) {

      //nova imagem definida pelo retangulo:
      PImage newImg = img.get(i, j, detail, detail);
      color cor = extractColorFromImage(newImg);

      rx[count_X]= red(cor);
      gx[count_X]= green(cor);
      bx[count_X]= blue(cor);

      myPort.write((count_X) + "," + (count_Y) + "," + int( rx[count_X] )+ "," + int (gx[count_X]) + "," + int (bx[count_X])  + "\n");
      delay(100);

      count_X++;
    }

    count_Y++;
    count_X = 0;
  }

  println(voltas);
  voltas++;
}


color extractColorFromImage(final PImage img) {
  img.loadPixels();
  color r = 0, g = 0, b = 0;

  for (final color c : img.pixels) {
    r += c >> 020 & 0xFF;
    g += c >> 010 & 0xFF;
    b += c        & 0xFF;
  }

  r /= img.pixels.length;
  g /= img.pixels.length;
  b /= img.pixels.length;

  return color(r, g, b);
}
