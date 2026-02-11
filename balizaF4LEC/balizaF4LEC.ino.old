//////////////////////////////////////////////////
// PROGRAMA DE BALIZA, CACERÍAS DE ZORRO, ETC  //
// EA7HG, 2025 Software libre                   //
// MODIFICACION F4LEC SIMULACION +WPM+debug		//
//////////////////////////////////////////////////

// PIN USADOS
// 2 = relé ENCENDIDO
// 7 = PTT OUT  
// 9 = Salida TONO A TRAVES DE CONDENSADOR 10NF
// 10 = tiempo de apagado 1 CON PUESTA A MASA
// 11 = tiempo de apagado 2 CON PUESTA A MASA
// 12 = tiempo de apagado 3 CON PUESTA A MASA
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
#define Encendido 2
#define PTT 7
#define Salida 9

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
  
  //Envio Mensaje , recorre el mensaje a enviar por la baliza
	for (int i = 0; i < mensaje.length(); i++) {
		playCW ( getCwCode ( mensaje[i] ) );
	}
  
  // Desactiva relé del PTT
  digitalWrite(PTT, LOW);
  // espera 500 ms (1/2 segundo)
  delay(500);
  // Apaga transceptor o emisor
  digitalWrite(Encendido, LOW);
  // Inicia nuevamente el temporizador de espera
  tiempo_inicial = millis();
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

//Play sonido CW ,del simbolo 
void playCW (String cw){
	Serial.print("(" +cw+ ") ");
	//Recorre el equivalente CW , puntos , rayas y espacios del CW
	for (int index=0;index<cw.length();index++){

		//ESTE CODIGO ES PARA MODO REAL NO PROBADO PERO DEBE SER ALGO ASI

		/*
		if (cw.charAt(index) =='.'){tone(Salida, frecuencia);delay(punto); noTone(Salida); delay(punto * 3)}//punto .
		else if (cw.charAt(index) =='-'){tone(Salida, frecuencia);delay(punto * 3); noTone(Salida); delay(punto / 2)}//raya _
		else { delay(punto); }//Espacio	entre elementos punto raya
		delay( (punto * 2) );			
		*/
		
		//ESTE CODIGO FUNCIONA EN MODO SIMULACION CON UN BUZZER SIMULADO 
		if (cw.charAt(index) =='.'){tone(Salida, frecuencia,punto);delay( (punto) + 10); }//punto .
		else if (cw.charAt(index) =='-'){tone(Salida, frecuencia,punto * 3);delay( (punto * 3) + 10);}//raya _
		else { delay(punto); }//Espacio	entre elementos punto raya
		delay( (punto * 2) );		
	}
	delay (punto*2);
}

//Calcula el tiempo de un punto en funcion de los WPM seleccionados
unsigned int calcularTimingCW(int wpm) {
  return (unsigned int)(1320.0 / wpm);
}
