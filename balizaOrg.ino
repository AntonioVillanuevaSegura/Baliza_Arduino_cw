//////////////////////////////////////////////////
// PROGRAMA DE BALIZA, CACERÍAS DE ZORRO, ETC  //
// EA7HG, 2025 Software libre                   //
//////////////////////////////////////////////////

// PIN USADOS
// 2 = relé ENCENDIDO
// 7 = PTT OUT  
// 9 = Salida TONO A TRAVES DE CONDENSADOR 10NF
// 10 = tiempo de apagado 1 CON PUESTA A MASA
// 11 = tiempo de apagado 2 CON PUESTA A MASA
// 12 = tiempo de apagado 3 CON PUESTA A MASA
//////////////////////////////////////////////////

// Define variable con 30 s. Tiempo por defecto de espera
unsigned long tiempo_disparo = 30;
// Define variable para iniciar tiempos
unsigned long tiempo_inicial = 0;
// Define tiempo del punto en morse. La raya multiplica por 3
unsigned int punto = 167;

// Define los pines para mejor lectura de código
#define Encendido 2
#define PTT 7
#define Salida 9

void setup() {
  // pin 2 configurado para salida
  pinMode(Encendido, OUTPUT);
  digitalWrite(Encendido, LOW);
  
  // pin 7 configurado para salida
  pinMode(PTT, OUTPUT);
  digitalWrite(PTT, LOW);
  
  // pin 9 configurado para salida tono
  pinMode(Salida, OUTPUT);
  
  //pin 10 configurado como entrada para tiempo de apagado 1
  pinMode(10, INPUT_PULLUP);
  //pin 11 configurado como entrada para tiempo de apagado 2
  pinMode(11, INPUT_PULLUP);
  //pin 12 configurado como entrada para tiempo de apagado 3
  pinMode(12, INPUT_PULLUP);
  
  // Si pin 10 se pone a tierra (GND) -> tiempo 45 segundos
  if (digitalRead(10) == LOW) tiempo_disparo = 45;
  // Si pin 11 se pone a tierra (GND) -> tiempo 60 segundos  
  if (digitalRead(11) == LOW) tiempo_disparo = 60;
  // Si pin 12 se pone a tierra (GND) -> tiempo 90 segundos
  if (digitalRead(12) == LOW) tiempo_disparo = 90;
  
  // Emite por primera vez el mensaje de la baliza
  Activar_Baliza();
  // se inicia el tiempo de espera
  tiempo_inicial = millis();
}

void loop() {
  // al finalizar tiempo de espera activa la baliza
  if ((millis() - tiempo_inicial) >= (tiempo_disparo * 1000)) {
    Activar_Baliza();
  }
}

void Activar_Baliza() {
  // Activa relé encendido transceptor o emisor
  digitalWrite(Encendido, HIGH);
  // Espera 1000 ms (1 segundo) antes de activar el PTT
  delay(1000);
  // Activa relé para activar PTT
  digitalWrite(PTT, HIGH);
  delay(250); // Espera 250ms (1/4 segundo)
  
  // Emite 3 V seguidas (V = ...-)
  for (int ab = 0; ab < 3; ab++) {
    Caracter(9);
  }
  // tiempo para espacio en blanco
  delay(punto * 3);
  
  // Emite DEEA7URJRZORROK
  Caracter(11); // D
  Caracter(4);  // E
  delay(punto * 3);
  Caracter(4);  // E
  Caracter(5);  // A
  Caracter(6);  // 7
  Caracter(7);  // U
  Caracter(3);  // R
  Caracter(8);  // J
  delay(1000);
  Caracter(1);  // Z
  Caracter(2);  // O
  Caracter(3);  // R
  Caracter(3);  // R
  Caracter(2);  // O
  Caracter(10); // K
  
  // Desactiva relé del PTT
  digitalWrite(PTT, LOW);
  // espera 500 ms (1/2 segundo)
  delay(500);
  // Apaga transceptor o emisor
  digitalWrite(Encendido, LOW);
  // Inicia nuevamente el temporizador de espera
  tiempo_inicial = millis();
}

void Caracter(int num) { // Genera tono de letra o número
  if (num == 1) { // Letra Z --**
    tone(Salida, 800); delay(punto * 3); noTone(Salida); delay(punto / 2);
    tone(Salida, 800); delay(punto * 3); noTone(Salida); delay(punto / 2);
    tone(Salida, 800); delay(punto); noTone(Salida); delay(punto / 2);
    tone(Salida, 800); delay(punto); noTone(Salida); delay(punto * 3);
  }
  if (num == 2) { // Letra O ***
    for (int ab = 0; ab < 3; ab++) {
      tone(Salida, 800); delay(punto * 3); noTone(Salida); delay(punto / 2);
    }
    delay(punto * 3);
  }
  if (num == 3) { // Letra R *.-.
    tone(Salida, 800); delay(punto); noTone(Salida); delay(punto / 2);
    tone(Salida, 800); delay(punto * 3); noTone(Salida); delay(punto / 2);
    tone(Salida, 800); delay(punto); noTone(Salida); delay(punto * 3);
  }
  if (num == 4) { // Letra E *
    tone(Salida, 800); delay(punto); noTone(Salida); delay(punto * 3);
  }
  if (num == 5) { // Letra A *-
    tone(Salida, 800); delay(punto); noTone(Salida); delay(punto / 2);
    tone(Salida, 800); delay(punto * 3); noTone(Salida); delay(punto * 3);
  }
  if (num == 6) { // Número 7 **---
    for (int ab = 0; ab < 2; ab++) {
      tone(Salida, 800); delay(punto * 3); noTone(Salida); delay(punto / 2);
    }
    for (int ab = 0; ab < 3; ab++) {
      tone(Salida, 800); delay(punto); noTone(Salida); delay(punto / 2);
    }
    delay(punto * 3);
  }
  if (num == 7) { // Letra U **-
    for (int ab = 0; ab < 2; ab++) {
      tone(Salida, 800); delay(punto); noTone(Salida); delay(punto / 2);
    }
    tone(Salida, 800); delay(punto * 3); noTone(Salida); delay(punto * 3);
  }
  if (num == 8) { // Letra J *---
    tone(Salida, 800); delay(punto); noTone(Salida); delay(punto / 2);
    for (int ab = 0; ab < 3; ab++) {
      tone(Salida, 800); delay(punto * 3); noTone(Salida); delay(punto / 2);
    }
    delay(punto * 3);
  }
  if (num == 9) { // Letra V ...-
    for (int ab = 0; ab < 3; ab++) {
      tone(Salida, 800); delay(punto); noTone(Salida); delay(punto / 2);
    }
    tone(Salida, 800); delay(punto * 3); noTone(Salida); delay(punto * 3);
  }
  if (num == 10) { // Letra K -.- 
    tone(Salida, 800); delay(punto * 3); noTone(Salida); delay(punto / 2);
    tone(Salida, 800); delay(punto); noTone(Salida); delay(punto / 2);
    tone(Salida, 800); delay(punto * 3); noTone(Salida); delay(punto * 3);
  }
  if (num == 11) { // Letra D -..
    tone(Salida, 800); delay(punto * 3); noTone(Salida); delay(punto / 2);
    for (int ab = 0; ab < 2; ab++) {
      tone(Salida, 800); delay(punto); noTone(Salida); delay(punto / 2);
    }
    delay(punto * 3);
  }
}
