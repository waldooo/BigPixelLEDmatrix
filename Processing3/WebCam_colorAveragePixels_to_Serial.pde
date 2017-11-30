import processing.video.*;
Capture webcam;

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

  webcam = new Capture(this, 320, 240);  
  //String[] devices = Capture.list();
  //println(devices);
  webcam.start();
}

void draw() {

  if (webcam.available() == true) {
    webcam.read();
    image(webcam, 0, 0, width, height);
    saveFrame("/data/image.jpg");
  }

  delay(100);

  PImage img = loadImage("image.jpg");
  delay(200);
  count_X = 0;
  count_Y = 0;



  //cria retangulos com a dimensão estipulada:
  for (int j=0; j<height; j+=detail) {
    for (int i=0; i<width; i+=detail) {

      //nova imagem definida pelo retangulo:
      PImage newImg = img.get(i, j, detail, detail);

      //extrai e cria um retangulo preenchido com a cor média medida
      noStroke();
      color cor = extractColorFromImage(newImg);
      fill(cor);
      rect(i, j, detail, detail);

      //rx[count_i][count_i]= cor >> 16 & 0xFF;
      //gx[count_i][count_j]=cor >> 8 & 0xFF;
      //bx[count_i][count_j]=cor & 0xFF;
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
