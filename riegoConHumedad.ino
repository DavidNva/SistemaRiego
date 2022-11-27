int bomba = 8;
int  humedad;
int ledRojo = 13;
int ledAzul = 12;
int ledAmarillo = 11;

int estado = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(bomba,OUTPUT);  
  pinMode(A0, INPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAzul, OUTPUT);
}

void loop()
{
   humedad = (100 - map(analogRead(A0),0,1023,0,100)); // Con esto conseguimos el porcentage de humedad en tantos por cien (el 1.45 puede variar segun el sensor de humedad).
  if(Serial.available()>0)
    {
    estado = Serial.read();
    }
    switch(estado){
      case 'B':
      digitalWrite(bomba, HIGH);
      digitalWrite(ledRojo,LOW);//
      digitalWrite(ledAzul,LOW);//
      break;
      case 'A':
      digitalWrite(bomba, LOW);
      digitalWrite(ledRojo,LOW);//
      digitalWrite(ledAzul,LOW);//
      break;
      case 'C':
            Serial.print(humedad);Serial.println (" %");
        if(humedad < 20){
             Serial.println("Tierra seca, encendiendo bomba automatica");
            digitalWrite(bomba, LOW);
            digitalWrite(ledRojo,HIGH);
            digitalWrite(ledAzul,LOW);
          }
        if(humedad > 20){
            
            Serial.println("Tierra humeda, apagando bomba automaticamente");
             digitalWrite(bomba, HIGH);
             digitalWrite(ledRojo,LOW);
            digitalWrite(ledAzul,HIGH);
          }
        delay(1000);
      break;
      case 'D':
      digitalWrite(bomba, HIGH);//Lo apaga y vuelve a leer el estado
      //estado = Serial.read();
      digitalWrite(ledRojo,LOW);//
      digitalWrite(ledAzul,LOW);//
      break;
      }


  // Monitorizar los parametros.
  
  
  
  
}

