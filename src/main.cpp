/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/



/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL2IsG7vOzO"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "Fgu8C7n1h9xx3y_CbkpBHadH6eHB25ar"
#define BLYNK_PRINT Serial

//DEFINE AS VARIÁVEIS QUE REPRESENTAM OS PINOS UTILIZADOS
#define DHTPIN 21
#define DHTTYPE DHT22 
#define LED1 4
#define LED2 5
#define LED3 18
#define LED4 19
#define LED5 22
#define LED6 15
#define LED7 23

#define BUZZER 2

//REALIZA A INCLUSÃO DAS BIBLIOTECAS NECESSÁRIAS
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"


// CONFIGURAÇÕES DA CONEXÃO WI-FI
/*char ssid[] = "NEIVA";
char pass[] = "33991700";*/
/*char ssid[] = "LCI01";
char pass[] = "up3@wz01";*/

char ssid[] = "_Mateus_";
char pass[] = "91469365";

//INICIALIZA A BIBLIOTECA PARA COLETA DE TEMPERATURA E UMIDADE
DHT dht(DHTPIN, DHTTYPE);

//INICIALIZA O TIMER DO BLYNK
BlynkTimer timer;

//DECLARA AS VARIÁVEIS QUE SERÃO UTILIZADAS
float h, t, tbase, incremento;
int status_buzzer;
int status_interface;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V8)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();
  
  // Update state
  digitalWrite(BUZZER, value);

  status_interface = value;
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  //ENVIA PARA O BLYNK AS INFORMAÇÕES DE UMIDADE E TEMPERATURA
  Blynk.virtualWrite(V7, h);
  Blynk.virtualWrite(V6, t);

  Blynk.virtualWrite(V8, status_interface);

  Serial.println(status_interface);  
}

void setup()
{
  //SETA OS PINOS QUE SERÃO UTILIZADOS COMO SAÍDA
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Debug console
  Serial.begin(9600);

  //AUTENTICAÇÃO NO BLYNK
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  //INICIALIZA O DHT (COLETA TEMPERATURA E UMIDADE)
  dht.begin();
  
  //O TBASE DEVE SER A TEMPERATURA AMBIENTE NO MOMENTO DA EXECUÇÃO OU A TEMPERATURA IDEAL EM UM SISTEMA REAL
  tbase = 17;

  //VARIAVEL QUE DEFINE QUAL O INTERVALO DE TEMPERATURA PARA LIGAÇÃO DAS LUZES DO LED
  incremento = 4;  

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);

  t=10;
  status_buzzer = 0;
  status_interface = 0;
  
}

void loop()
{
  //EXECUTA O BLYNK E O TIMER
  Blynk.run();
  timer.run();

  //COLETA TEMPERATURA E UMIDADE
  h = dht.readHumidity();
  t = dht.readTemperature();

  //MOSTRA NO CONSOLE AS INFORMAÇÕES
  Serial.println("Temperatura");  
  Serial.println(t);  
  Serial.println("Umidade");  
  Serial.println(h);

  //ESSA LINHA PODE SER UTILIZADA PARA SIMULAR O SISTEMA SEM A COLETA DE TEMPERATURA
  //t = t + 0.5;

  //CONDIÇÃO PARA LIGAÇÃO DO PRIMEIRO LED
  if (t > (tbase + (incremento*1))){
    digitalWrite(LED1, HIGH);    
  }else{
    digitalWrite(LED1, LOW);
  }

  //CONDIÇÃO PARA LIGAÇÃO DO SEGUNDO LED
  if (t > (tbase + (incremento*2))){
    digitalWrite(LED2, HIGH);    
  }else{
    digitalWrite(LED2, LOW);
  }

  //CONDIÇÃO PARA LIGAÇÃO DO TERCEIRO LED
  if (t > (tbase + (incremento*3))){
    digitalWrite(LED3, HIGH);    
  }else{
    digitalWrite(LED3, LOW);
  }

  //CONDIÇÃO PARA LIGAÇÃO DO QUARTO LED
  if (t > (tbase + (incremento*4))){
    digitalWrite(LED4, HIGH);    
  }else{
    digitalWrite(LED4, LOW);
  }

  //CONDIÇÃO PARA LIGAÇÃO DO QUINTO LED
  if (t > (tbase + (incremento*5))){
    digitalWrite(LED5, HIGH);    
  }else{
    digitalWrite(LED5, LOW);
  }

  //CONDIÇÃO PARA LIGAÇÃO DO SEXTO LED
  if (t > (tbase + (incremento*6))){
    digitalWrite(LED6, HIGH);    
  }else{
    digitalWrite(LED6, LOW);
  }

  //CONDIÇÃO PARA LIGAÇÃO DO SÉTIMO LED
  if (t > (tbase + (incremento*7))){
    digitalWrite(LED7, HIGH);    
  }else{
    digitalWrite(LED7, LOW);
  }

  //CONDIÇÃO PARA DISPARO DO BUZZER (A PARTIR DO SEXTO LED)
  if (t > (tbase + (incremento*6))){

    if (status_buzzer == 0){
      status_interface = 1;
      status_buzzer = 1;
      digitalWrite(BUZZER, HIGH); //LIGAR O BUZZER
      Blynk.logEvent("alerta_temperatura");
    }

    if (status_interface == 0){
      status_buzzer = 1;
      digitalWrite(BUZZER, LOW); //DESLIGAR O BUZZER
    }

    delay(4000); //DELAY PARA DAR O EFEITO DE ALARME INTERMITENTE

  }else{
    status_buzzer = 0;
    digitalWrite(BUZZER, LOW); //DESLIGAR O BUZZER
  }

   delay(1000); //INTERVALO ENTRE UMA COLETA
   

}

