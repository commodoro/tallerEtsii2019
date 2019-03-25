/****************************************
* Taller Arduino ETSIT (UPCT) 2019      *
* Autor: Mariano Fernández Abadía.      *
* Organizacion: IEEE UPCT SB.           *
* Licencia: (CC BY-ND)                  *
****************************************/

#include <Adafruit_NeoPixel.h>
#include <UniColor.h>

/////////// Constantes ///////////
#define PIN_LEDS 6
#define N_LEDS 8 // Cambiar si hay más LEDS.

/////////// Variables ///////////

Adafruit_NeoPixel lampara = Adafruit_NeoPixel(N_LEDS, PIN_LEDS, NEO_GRB + NEO_KHZ800);
UniColor color; // Donde guardamos el color que queramos que use.
bool on = true; // Indica si la lámpara está encendida o apagada.

void setup() {
  /////////// Configuaración ///////////
  
  // Iniciamos la comunicación con el modulo bluetooth
  // usando el puerto Serie.
  Serial.begin(9600);

  // Configuramos la lámpara.
  lampara.begin();
  lampara.setBrightness(255);

  /////////// Test ///////////
  
  // Para ver que los colores funcionan bien.
  rellenar({255, 0, 0});
  delay(500);
  rellenar({0, 255, 0});
  delay(500);
  rellenar({0, 0, 255});
  delay(500);
  rellenar({0, 0, 0});
}

void loop() {
  char c = 0; // Para guardar el caracter que llega del puerto serie.

  /////////// Lectura del puerto Serie ///////////

  if (Serial.available()) // Si haya algo en el puerto Serie...
  {
    c = Serial.read(); // ...tomamos el carácter que nos ha llegado.
  }

  /////////// Selección de Acción ///////////

  if (c == 'A') color.hex = 0x0000ff; // Si el carácter que nos llega es 'A' el color será Azul.

  if (c == 'V') color.hex = 0x00ff00; // Color Verde.

  if (c == 'R') color.hex = 0xff0000; // Color Rojo.

  // Otro color.

  if (c == 'E') on = true; // Encender.

  if (c == 'e') on = false; // Apagar.

  /////////// Usar Lámpara ///////////
  
  if (on) rellenar(color); // Si está encendida rellena con el color elegido.
  else rellenar ({0, 0, 0}); // Si está apagada no muestra ningún color.
};


void rellenar(UniColor c)
{
  // Esto sirve para que la lámpara muestre el color que le hemos indicado.
  for (int i = 0; i < lampara.numPixels(); i++)
    lampara.setPixelColor(i, lampara.Color(c.red, c.green, c.blue));
  lampara.show();
};
