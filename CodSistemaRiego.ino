int Luz = 3;
int  humedad;


int estado = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(Luz,OUTPUT);  
  pinMode(A0, INPUT);
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
      digitalWrite(Luz, HIGH);
      break;
      case 'A':
      digitalWrite(Luz, LOW);
      break;
      case 'C':
            Serial.print(humedad);Serial.println (" %");
        if(humedad < 20){
             Serial.println("Encendiendo bomba automatica");
            digitalWrite(Luz, LOW);
          }
        if(humedad > 20){
            
            Serial.println("Apagando bomba automaticamente");
             digitalWrite(Luz, HIGH);
          }
        delay(1000);
      break;
      case 'D':
      digitalWrite(Luz, LOW);//Lo apaga y vuelve a leer el estado
      estado = Serial.read();
      break;
      }

  
}

