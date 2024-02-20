#include <Wire.h> //INCLUSÃO DE BIBLIOTECA

#include <Adafruit_GFX.h> //INCLUSÃO DE BIBLIOTECA

#include <Adafruit_SSD1306.h> //INCLUSÃO DE BIBLIOTECA


Adafruit_SSD1306 display = Adafruit_SSD1306(); // Código baseado no controlador usado no Oled

//Declaracao do pino conectado ao sensor
const int PINO_SENSOR = A0;

//Declaracao do pino conectado ao relê
const int PINO_RELE = 2;

//Declaracao da variavel que armazena as leituras do sensor
int leitura_sensor;

//Declaracao da variavel auxiliar para o "delay" de 10 segundos
bool pausa = true;

//Declaracao das variaveis que armazenam os valores de calibracao    
const int VALOR_MAXIMO = 470; //Valor com solo seco
const int VALOR_MINIMO = 1000; //Valor com solo umido
//Altere o valor das variaveis acima de acordo com as                                                                                                                                                                                        obtidas atraves do codigo do projeto anterior

//Declaracao das variaveis que armazenam a concentracao maxima e minima desejada
const int CONCENTRACAO_MINIMA = 30; // Solo 70% seco
const int CONCENTRACAO_MAXIMA = 50; // Solo 50% seco
//Altere as variaveis acima com os valores ideais para a sua planta

void setup() { 

  //Define o pino conectado ao sensor como uma entrada do sistema
  pinMode(PINO_SENSOR, INPUT);
  
  //Define o pino conectado ao rele como uma saida do sistema
  pinMode(PINO_RELE, OUTPUT);

  //Inicia o pino conectado ao rele com nivel logico baixo
  digitalWrite(PINO_RELE, LOW);

  Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  
  display.setTextColor(WHITE); //DEFINE A COR DO TEXTO

  display.setTextSize(1); //DEFINE O TAMANHO DA FONTE DO TEXTO
  
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY

}

void loop() {

  Serial.begin(9600);
  Serial.println("Umidade: ");
  Serial.print(leitura_sensor);
  Serial.println("%");
  delay(1000);
  //Realiza a leitura do sensor, a mapeia entre 0 e 100 % e exibe o valor no LCD
  leitura_sensor = analogRead(PINO_SENSOR);
  leitura_sensor = map(leitura_sensor, VALOR_MINIMO, VALOR_MAXIMO, 0, 100);
  
  //Verifica se a leitura esta abaixo da concetracao minima desejada
  if(leitura_sensor > CONCENTRACAO_MINIMA){ //Se sim
    digitalWrite(PINO_RELE, HIGH); //Rele acionadao
    pausa = false; //Configura a variavel "pausa" como falsa
    
    display.setTextSize(1);
    display.setCursor(35,2); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    display.print("% Umidade");
    display.display();

    display.setTextSize(2);
    display.setCursor(49,42);
    display.print(leitura_sensor); //ESCREVE O TEXTO NO DISPLAY
    display.print("%");
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    display.clearDisplay();

  } else if (leitura_sensor < CONCENTRACAO_MAXIMA) { //Caso contrario
    digitalWrite(PINO_RELE, LOW); //O rele se mantem desligado
    pausa = true; //Configura a variavel "pausa" como verdadeira
    
    display.setTextSize(1);
    display.setCursor(35,2); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    display.print("% Umidade");
    display.display();
    
    display.setTextSize(2);
    display.setCursor(49,42);
    display.print(leitura_sensor); //ESCREVE O TEXTO NO DISPLAY
    display.print("%");
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(1000); //INTERVALO DE 1 segundo
    display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
  }
  //Verifica se a variavel "pausa" e verdadeira
  if(pausa){ //Se sim
    delay(1000); //Aguarda 1 segundos para nova leitura
  } 
}
