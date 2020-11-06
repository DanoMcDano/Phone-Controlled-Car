#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial   
 
//Variables utilizadas internamente por el programa. 
int enco, encoMap, gate, j, i; 
String comando=""; 
char x; 
bool state, laststate; 
int izqA = 5; 
int izqB = 6; 
int derA = 9; 
int derB = 10; 
int encoderA = 2; 
int encoderALast = LOW;
int encoderPos = 0;
int n= LOW;
int a=0;
int estado=1;

 
void setup()
 {   
  Serial.begin(9600);    // Inicializamos  el puerto serie     
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);  
  pinMode(encoderA,INPUT); 
 }   

void loop() 
{   
 gate=0;   
 comando="";   
 laststate=LOW; 
 
 do   
  {     
   if(Serial.available()>0)   //Si el arduino detecta un envío de señal     
    {       
     x=Serial.read();       // Se almacena la señal recibida y se agrega al string de comandos       
     delay(10);       
     Serial.print(x);       
     comando.concat(x);     
    }     
    
   if(x=='S'||x=='s')       
    {         
     gate=1;           //cuando se envíe la señal de start ("S"), se sale de la recepción de datos.       
    }   
   }
 while(gate!=1);  
  
 for(j=0; j<comando.length(); j++) //Ciclo que asegura leer cada una de las instrucciones almacenadas.   
  {     
   switch(comando.charAt(j))     //Se pasa el string por cada uno de sus caracteres con la funcion char at y el indice j.     
    {       
         
     case 'a': 
      do{
      n = digitalRead(encoderA);
      if ((a>=0)&& (a<=100))
      {
         digitalWrite(derB, LOW);     
         digitalWrite(izqB, LOW); 
         digitalWrite(derA, HIGH);  
         digitalWrite(izqA, HIGH); 
        
      if ((encoderALast == LOW) && (n == HIGH)) {
          encoderPos++;
          a=encoderPos*0.52359877559*(8/2);
          Serial.println (encoderPos); 
          Serial.println(encoderPos*30);
          Serial.println((encoderPos*0.52359877559)*(8/2));     
      }
          encoderALast = n;

      }
      else 
      {
          digitalWrite(derB, LOW);     
          digitalWrite(izqB, LOW); 
          digitalWrite(derA, LOW);    
          digitalWrite(izqA, LOW);
          estado=0;
          
      }
      }while(estado!=0);
     if (encoderPos!=40 && a!=0)
     {
           a=0;
     encoderPos=0;
     
     }
      delay(2000);
      estado=1;
      break; 
               
     case 'r':
     i=0; 
     do{
     digitalWrite(derA,LOW);             
     digitalWrite(izqA,LOW);   
     digitalWrite(derB,HIGH);     
     digitalWrite(izqB,HIGH);     
     i++;   
     Serial.println(i);
     delay(2000);
     }while (i==10);
     break;   
           
     case 'd': 
     digitalWrite(derA,LOW);  
     digitalWrite(izqB,LOW);       
     digitalWrite(izqA,HIGH);       
     digitalWrite(derB,HIGH);  
     delay(1000);           
     break;   
        
     case 'i':       
     digitalWrite(derB,LOW);       
     digitalWrite(izqA,LOW);            
     digitalWrite(derA,HIGH);  
     digitalWrite(izqB,HIGH); 
     delay(1000);            
     break;   
         
     case 'p':       
     digitalWrite(derB,LOW);       
     digitalWrite(izqA,LOW);       
     digitalWrite(derA,LOW);       
     digitalWrite(izqB,LOW); 
     delay(1000);       
     break;
        
     
    }   
  }    
}
