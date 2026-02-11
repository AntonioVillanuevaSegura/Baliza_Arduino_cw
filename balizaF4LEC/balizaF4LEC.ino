//////////////////////////////////////////////////
// PROGRAMA DE BALIZA, CACERÍAS DE ZORRO, ETC  //
// EA7HG, 2025 Software libre                   //
// MODIFICACION F4LEC SIMULACION +WPM+debug		//
//////////////////////////////////////////////////

// PIN USADOS
// 2 = relé ENCENDIDO
// 7 = PTT OUT  
// 9 = SALIDA TONO A TRAVES DE CONDENSADOR 10NF
//////////////////////////////////////////////////

String mensaje = "V V V DE F4LEC ZORRO K";  //Mensaje a enviar por la baliza
int frecuencia =800; //Frecuencia CW 
int WPM = 20;  // Velocidad en palabras por minuto

// Define variable con 30 s. Tiempo por defecto de espera
unsigned long tiempo_disparo = 30;
// Define variable para iniciar tiempos
unsigned long tiempo_inicial = 0;
// Define tiempo del punto en morse. La raya multiplica por 3
unsigned int punto = 167;

// Define los pines para mejor lectura de código
#define ENCENDIDO 2
#define PTT 7
#define SALIDA 9

//Entradas retardo 2^8 posibilidades
#define RETARDO_1 10
#define RETARDO_2 11
#define RETARDO_3 12

//Leds salida auxiliares
#define LED_1 3
#define LED_2 4
#define LED_3 5

//Creamos un diccionario KEY:VALUE donde cada signo  tiene su correspondencia CW

const char* key[] = {
  "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
  "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
  "U", "V", "W", "X", "Y", "Z",
  "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", " "
};

const char* value[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
  "..-", "...-", ".--", "-..-", "-.--", "--..",
  "-----", ".----", "..---", "...--", "....-", ".....", 
  "-....", "--...", "---..", "----.", "-----",
  " "
};

void setup() {

	punto =calcularTimingCW(WPM);
	Serial.begin(9600);  // Debug serie
	Serial.println("Velocidad punto " + String(punto) + " ms");

	// pin 2 configurado para SALIDA
	pinMode(ENCENDIDO, OUTPUT);
	digitalWrite(ENCENDIDO, LOW);

	// pin 7 configurado para SALIDA
	pinMode(PTT, OUTPUT);
	digitalWrite(PTT, LOW);

	// pin 9 configurado para SALIDA tono
	pinMode(SALIDA, OUTPUT);

	//D3 D4 D5 LEDs salidas auxiliares PCB  
	pinMode(LED_1, OUTPUT);
	pinMode(LED_2, OUTPUT);
	pinMode(LED_3, OUTPUT);

	//pin 10,11,12 entrada configura apagado 
	pinMode(RETARDO_1, INPUT_PULLUP);
	pinMode(RETARDO_2, INPUT_PULLUP);
	pinMode(RETARDO_3, INPUT_PULLUP);
	

	/*2³ =8 posibilidades de retardo 
	Switch 10	Switch 11	Switch 12	Bits (1=ON)	tiempo_disparo
	OFF	OFF	OFF	000 = 0	0ms
	ON	OFF	OFF	001 = 1	15ms
	OFF	ON	OFF	010 = 2	30ms
	ON	ON	OFF	011 = 3	45ms
	OFF	OFF	ON	100 = 4	60ms
	ON	OFF	ON	101 = 5	75ms
	OFF	ON	ON	110 = 6	90ms
	ON	ON	ON	111 = 7	105ms	
	*/
	tiempo_disparo = (digitalRead(RETARDO_1)|digitalRead(RETARDO_2)|digitalRead(RETARDO_3))*15;
	Serial.println("Retardo " +String (tiempo_disparo) + " ms");
	Activar_Baliza();
	tiempo_inicial = millis();
}

void loop() {
  // al finalizar tiempo de espera activa la baliza
  if ((millis() - tiempo_inicial) >= (tiempo_disparo * 1000)) {
    Activar_Baliza();
  }
}

void Activar_Baliza() {
	
	led_ON (LED_3);
  // Activa relé ENCENDIDO transceptor o emisor
  digitalWrite(ENCENDIDO, HIGH);
  // Espera 1000 ms (1 segundo) antes de activar el PTT
  delay(1000);
  // Activa relé para activar PTT
  digitalWrite(PTT, HIGH);
  delay(250); // Espera 250ms (1/4 segundo)
  
  //Envio Mensaje , recorre el mensaje a enviar por la baliza
	for (int i = 0; i < mensaje.length(); i++) {
		playCW ( getCwCode ( mensaje[i] ) );
	}
  
  // Desactiva relé del PTT
  digitalWrite(PTT, LOW);
  // espera 500 ms (1/2 segundo)
  delay(500);
  // Apaga transceptor o emisor
  digitalWrite(ENCENDIDO, LOW);
  // Inicia nuevamente el temporizador de espera
  tiempo_inicial = millis();
  led_OFF (LED_3);
}

// obtiene el codigo CW de un signo , p.e A retorna .-
String getCwCode(char caracter) { 
	Serial.print (caracter);//Debug caracter
	if (caracter==' '){return " ";}//Retorna espacio 

	//Recorre la matriz de key creando indices 
	for (int index=0;index<(sizeof(key)/sizeof(key[0]));index++){//Recorre key
		
		if ( key[index][0] ==  toupper(caracter) ){
			return value[index];
		}
	}
	return "";
}

//Funciones auxiliares para activar leds auxiliares
void led_ON(int led){
	digitalWrite(led,HIGH);
}

void led_OFF(int led){
	digitalWrite(led,LOW);
}

//Play sonido CW ,del simbolo 
void playCW (String cw){
	Serial.print("(" +cw+ ") ");
	//Recorre el equivalente CW , puntos , rayas y espacios del CW
	for (int index=0;index<cw.length();index++){

		//ESTE CODIGO ES PARA MODO REAL NO PROBADO PERO DEBE SER ALGO ASI

		/*
		if (cw.charAt(index) =='.'){tone(SALIDA, frecuencia);delay(punto); noTone(SALIDA); delay(punto * 3)}//punto .
		else if (cw.charAt(index) =='-'){tone(SALIDA, frecuencia);delay(punto * 3); noTone(SALIDA); delay(punto / 2)}//raya _
		else { delay(punto); }//Espacio	entre elementos punto raya
		delay( (punto * 2) );			
		*/
		
		//ESTE CODIGO FUNCIONA EN MODO SIMULACION CON UN BUZZER SIMULADO 
		if (cw.charAt(index) =='.'){tone(SALIDA, frecuencia,punto);led_ON (LED_1) ;delay( (punto) + 10); led_OFF (LED_1);}//punto .
		else if (cw.charAt(index) =='-'){tone(SALIDA, frecuencia,punto * 3);led_ON (LED_2);delay( (punto * 3) + 10);led_OFF (LED_2);}//raya _
		else { delay(punto); }//Espacio	entre elementos punto raya
		delay( (punto * 2) );		
	}
	led_OFF (LED_1);
	led_OFF (LED_2);	
	delay (punto*2);
}

//Calcula el tiempo de un punto en funcion de los WPM seleccionados
unsigned int calcularTimingCW(int wpm) {
  return (unsigned int)(1320.0 / wpm);
}
