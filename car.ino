/*
  Capitulo 20 de Arduino desde cero en Español.
  Programa que utiliza el modulo controlador de motor L298N junto con vehiculo
  tipo rover para realizar un circuito simple en forma de U.

  Autor: bitwiseAr  

*/

#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); 

char DATA = 0;
int IN1 = 2;      // IN1 a pin digital 2
int IN2 = 3;      // IN2 a pin digital 3
int ENA = 5;      // ENA a pin digital 5
int IN3 = 7;      // IN3 a pin digital 7
int IN4 = 8;      // IN4 a pin digital 8
int ENB = 9;      // ENA a pin digital 9
int VELOCIDAD;      // variable para almacenar valor de velocidad

void setup(){
  BT.begin(38400);
  pinMode(IN1, OUTPUT);   // IN1 como salida  
  pinMode(IN2, OUTPUT);   // IN2 como salida
  pinMode(ENA, OUTPUT);   // ENA como salida
  pinMode(IN3, OUTPUT);   // IN3 como salida
  pinMode(IN4, OUTPUT);   // IN4 como salida
  pinMode(ENB, OUTPUT);   // ENB como salida
}

void loop(){
  VELOCIDAD = 100;    // valor de velocidad para PWM de ENA y ENB
  if (BT.available()){
    DATA = BT.read();
    if (DATA == '1'){
      aAvance(VELOCIDAD);  
      bAvance(VELOCIDAD);
      delay(250);  
      }
      else if (DATA == '2')
      {
        Retroceso(VELOCIDAD);
        delay(250);
      }
      else if (DATA == '3'){
        GiroD(VELOCIDAD);
        delay(250);  
      }
      else if (DATA == '4'){
        GiroI(VELOCIDAD);
        delay(250);  
      }
        
        
      detieneAmbos();
    }
  }

void aAvance(int veloc){  // funcion para avance de motor A
  analogWrite(ENA, veloc);  // velocidad mediante PWM en ENA
  digitalWrite(IN1, HIGH); // IN1 a cero logico
  digitalWrite(IN2, LOW);  // IN2 a uno logico
}

void bAvance(int veloc){  // funcion para avance de motor B
  analogWrite(ENB, veloc);  // velocidad mediante PWM en ENB
  digitalWrite(IN3, HIGH); // IN3 a cero logico
  digitalWrite(IN4, LOW);  // IN4 a uno logico
}

void Retroceso(int veloc){
  analogWrite(ENA, veloc);  // velocidad mediante PWM en ENA
  digitalWrite(IN1, LOW); // IN1 a cero logico
  digitalWrite(IN2, HIGH);
  analogWrite(ENB, veloc);  // velocidad mediante PWM en ENB
  digitalWrite(IN3, LOW); // IN3 a cero logico
  digitalWrite(IN4, HIGH);  // IN4 a uno logico
}

void GiroD(int veloc){
  analogWrite(ENA, veloc);  // velocidad mediante PWM en ENA
  digitalWrite(IN1, HIGH); // IN1 a cero logico
  digitalWrite(IN2, LOW);
  analogWrite(ENB, 0);
}

void GiroI(int veloc){
  analogWrite(ENA, 0);  // velocidad mediante PWM en ENA
  
  analogWrite(ENB, veloc);
  digitalWrite(IN3, HIGH); // IN1 a cero logico
  digitalWrite(IN4, LOW);
}

void detieneAmbos(){    // funcion que detiene ambos motores
  analogWrite(ENA, 0);    // deshabilita motor A
  analogWrite(ENB, 0);    // deshabilita motor B
}
