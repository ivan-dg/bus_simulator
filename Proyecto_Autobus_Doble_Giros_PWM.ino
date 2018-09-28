#include <LiquidCrystal.h>  //Incluye la libreria de la pantalla LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Inicializa la libreria de la pantalla con los pines usados
int s_sub = 0; // Variable para el sensor de subida
int s_baj = 0; // Variable para el sensor de bajada
int npas = 0;  // Variable para el numero de pasajeros
int del = 2000; //Variable para un retraso de 2000 milisegundos (2segundos)
int maxpas = 5;  // Variable para el maximo de pasajeros
int cont = 0;   
const int sen_s =  6;      // the number of the LED pin
const int sen_b =  7;      // the number of the LED pin
const int mot_s =  8;      // the number of the LED pin
const int mot_b =  9;      // the number of the LED pin
const int mot_b2 =  1;      // the number of the LED pin
const int mot_s2 =  0;      // the number of the LED pin
const int led_s =  10;      // the number of the LED pin
const int led_b =  13;      // the number of the LED pin
//int analogPin = 3;   // potentiometer connected to analog pin 3
int val = 130;         // variable to store the read value



void setup() {
  // put your setup code here, to run once:
    lcd.begin(16, 2); //Configura el numero de filas y columnas de la pantalla LCD  
    pinMode(sen_s, INPUT); //Inicializa el puerto 6 como entrada digital
    pinMode(sen_b, INPUT); //Inicializa el puerto 7 como entrada digital
    pinMode(mot_s, OUTPUT); //Inicializa el puerto 8 como salida digital
    pinMode(mot_b, OUTPUT); //Inicializa el puerto 9 como salida digital
    pinMode(led_s, OUTPUT); //Inicializa el puerto 8 como salida digital
    pinMode(led_b, OUTPUT); //Inicializa el puerto 9 como salida digital
    pinMode(mot_s2, OUTPUT); //Inicializa el puerto 9 como salida digital
    pinMode(mot_b2, OUTPUT); //Inicializa el puerto 9 como salida digital
    lcd.setCursor(0, 0); // Situa la posicion donde se escribe el mensaje
    lcd.println("No. de Pasajeros"); //Imprime un mensaje en la pantalla LCD
    lcd.setCursor(0, 1); // Situa la posicion donde se escribe el mensaje
    lcd.print(npas); //Imprime una variable en la pantalla
    delay(200); // Pausa el programa durante un tiempo en milisegundos
}

void loop() {
  // put your main code here, to run repeatedly:
    lcd.setCursor(0, 0); // Situa la posicion donde se escribe el mensaje
    lcd.println("No. de Pasajeros"); //Imprime un mensaje en la pantalla LCD
    lcd.setCursor(0, 1); // Situa la posicion donde se escribe el mensaje
    lcd.print(npas); //Imprime una variable en la pantalla
  if(npas == 0 && cont == 0){ 
    abrir_puerta(mot_s, mot_b, led_s); // Llama a la funcion abrir puerta que abre la puerta de subida de pasajeros cuando se inicia el programa
    cont = 1;
  }
    s_sub = digitalRead(sen_s); //Almacena en la variable s_sub el valor del sensor de subida
    s_baj = digitalRead(sen_b); //Almacena en la variable s_baj el valor del sensor de bajada
    if(s_sub == HIGH) { //Condicion que realiza si el sensor de subida se activa
      npas++; //Contador que almacena el # de pasajeros que suben al bus
      lcd.setCursor(0, 1); // Situa la posicion donde se escribe el mensaje
      lcd.print(npas); //Imprime una variable en la pantalla
      delay(250); // Pausa el programa durante un tiempo en milisegundos
      s_sub = digitalRead(sen_s); //Almacena en la variable s_sub el valor del sensor de subida
      if(npas == maxpas){ //Condicion que realiza si el # de pasajeros es igual al # maximo de pasajeros
        cerrar_puerta(mot_s, mot_b, led_s); //Llama a la funcion cerrar puerta que cierra la puerta subida de pasajeros si el # de pasajeros es igual al # maximo de pasajeros
      }
    }
    else if (s_baj == HIGH && npas>0){  //Condicion que realiza si el sensor de bajada se activa
      abrir_puerta(mot_s2, mot_b2, led_b); // Llama a la funcion abrir puerta que abre la puerta de bajada de pasajeros
      delay(250); // Pausa el programa durante un tiempo en milisegundos  
      cerrar_puerta(mot_s2, mot_b2, led_b); // Llama a la funcion cerrar puerta que cierra la puerta de bajada de pasajeros
      if(npas == maxpas){ //Condicion que realiza si en sensor de bajada se activa y el # de pasajeros es igual al # maximo de pasajeros 
        abrir_puerta(mot_s, mot_b, led_s); // Llama a la funcion abrir puerta que abre la puerta de subida de pasajeros
      }
      npas--; //Contador que almacena el # de pasajeros que bajan del bus
      lcd.setCursor(0, 1); // Situa la posicion donde se escribe el mensaje
      lcd.print(npas); //Imprime una variable en la pantalla
      delay(250); // Pausa el programa durante un tiempo en milisegundos
    }
}

int abrir_puerta(int mots, int motb, int led){
    lcd.clear(); // Borra el todo el contenido de la pantalla LCD
    lcd.setCursor(0, 0); // Situa la posicion donde se escribe el mensaje
    lcd.print("Abriendo puerta"); //Imprime un mensaje en la pantalla LCD
    delay(del); // Pausa el programa durante un tiempo en milisegundos
    analogWrite(motb, 0); // Apaga la salida 
    analogWrite(mots, val); //Genera un pulso PWM en la salida mots que activa al motor con un ciclo util de val=130
    digitalWrite(led, HIGH); // Enciendo la salida que activa el led que muestra si la puerta esta abierta o cerrada
    delay(del);// Pausa el programa durante un tiempo en milisegundos
    analogWrite(mots, 0); // Apaga la salida 
}

int cerrar_puerta(int mots_1, int motb_1, int led_1){
    lcd.clear(); // Borra el todo el contenido de la pantalla LCD
    lcd.setCursor(0, 0); // Situa la posicion donde se escribe el mensaje
    lcd.print("Cerrando puerta"); //Imprime un mensaje en la pantalla LCD
    delay(del); // Pausa el programa durante un tiempo en milisegundos
    analogWrite(mots_1, 0); // Apaga la salida 
    analogWrite(motb_1, val+110);  //Genera un pulso PWM en la salida mots que activa al motor con un ciclo util de val=230    
    delay(del); // Pausa el programa durante un tiempo en milisegundos
    analogWrite(motb_1, 0);   // Apaga la salida   
    digitalWrite(led_1, LOW);  // Apaga la salida que activa el led que muestra si la puerta esta abierta o cerrada
}
