#include "dht.h"

int humidityPin = A4;
int lightPin = A5;

int enginePin_IN2 = 13;
int enginePin_IN1 = 12;
int engineEnablePin = 11;

bool persiana_abaixada = false;
dht DHT;

void print_state(){
  if (persiana_abaixada){
      Serial.println("A persiana esta abaixada");
    } else {
      Serial.println("A persiana esta recolhida"); 
    }
 }

void pararMotor(){
  digitalWrite(engineEnablePin, LOW);
}

void ligarMotor(){
  digitalWrite(engineEnablePin, HIGH);
}
void virarPraUmLado(){
  ligarMotor();
	digitalWrite(enginePin_IN2, HIGH);
	digitalWrite(enginePin_IN1, LOW);
  delay(30000);
  persiana_abaixada = true;
  pararMotor();
}
void virarProOutroLado(){
	ligarMotor();
	digitalWrite(enginePin_IN2, LOW);
	digitalWrite(enginePin_IN1, HIGH);
  delay(20000);
  persiana_abaixada = false;
  pararMotor();
}

void setup()
{
  pinMode(enginePin_IN2, OUTPUT);
  pinMode(enginePin_IN1, OUTPUT);
  pinMode(engineEnablePin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int lightInput = analogRead(lightPin);
  //int humidityInput = analogRead(humidityPin);
  DHT.read11(humidityPin);
  Serial.print("Luz: ");
  Serial.println(lightInput);
  Serial.print("Humidade: ");
  Serial.println(DHT.humidity);
  Serial.println("----------------");
  print_state();
  
  if (lightInput < 600 || DHT.humidity > 70){
    if (!persiana_abaixada){
      virarPraUmLado();  
    }
  }else if (persiana_abaixada){
    virarProOutroLado();
  }
  delay(100);
}
