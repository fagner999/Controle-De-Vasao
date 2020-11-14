#include <LiquidCrystal.h>
int estadobotao;//f
int botao =A0;//f
float (y);//f
int(t);//f
int (x);//f
float vazao; //Variável para armazenar o valor em L/min
float media = 0; //Variável para fazer a média
int contaPulso; //Variável para a quantidade de pulsos
int i = 0; //Variável para segundos
int Min = 00; //Variável para minutos
float Litros = 0; //Variável para Quantidade de agua
float MiliLitros = 0; //Variavel para Conversão
int rele = 10; //rele na porta digital 10
int ledVermelho=9; //led vermelho
int ledAmarelo = 13; //led Amarelo
int ledVerde = 12; //Led Verde
int sensorFluxo=2;  //sensor de fluxo de agua na porta digital 2
int push=11; //push button para acionamento assincrono
boolean acionamentoExterno = false;  
LiquidCrystal lcd(8, 7, 6, 5, 4, 3); //a ordem e importante
  
 void incpulso ()
{
 contaPulso++; //Incrementa a variável de pulsos
} 
void setup()
{
 pinMode(botao,INPUT);//f
 pinMode(rele, OUTPUT);  //define rele como atuador
 pinMode(sensorFluxo, INPUT); //Define o Sersor de fluxo de agua como entrada
 pinMode(push, INPUT);
 pinMode(ledVerde, OUTPUT);
 pinMode(ledVermelho, OUTPUT);
 pinMode(ledAmarelo, OUTPUT);
 Serial.begin(9600); //inicia a comunicacao pelo monitor serial
 lcd.begin(16, 2); //inicializa o display LCD como 16x2
 lcd.setCursor( 0, 0); //coloca o cursor na primeira coluna e primeira linha
 lcd.print("Sensoriamento de"); //escreve na primeira linha
 lcd.setCursor( 0, 1); //cursor na segunda linha
 lcd.print(" fluxo de Agua "); //escreve na segunda linha
 delay(3000); //aguarda 3 segundos (3000 ms)
 lcd.clear(); //limpa display LCD
 attachInterrupt(0, incpulso, RISING); //Configura o pino 2(Interrupção 0) interrupção
}
  
  
void loop ()
{
 contaPulso = 0;//Zera a variável
 sei(); //Habilita interrupção
 delay (1000); //Aguarda 1 segundo
 cli(); //Desabilita interrupção
  
 vazao = contaPulso / 5.5; //Converte para L/min
 media = media + vazao; //Soma a vazão para o calculo da media
 i++;
 lcd.setCursor(0, 0);
 lcd.print(vazao); //Escreve no display o valor da vazão
 lcd.print(" L/min "); //Escreve L/min
 lcd.setCursor(0, 1);
 lcd.print(Min);
 lcd.print(":"); //Escreve :
 lcd.print(i); //Escreve a contagem i (segundos)
 lcd.print("Min "); //Escreve :
 MiliLitros = vazao / 60;
 Litros = Litros + MiliLitros;
 lcd.print(Litros);
 lcd.print("L ");
 
 estadobotao = digitalRead(botao);//f

 if (estadobotao <=6){
  estadobotao=estadobotao++;
 }else {
    estadobotao = 0;
  
 }//f
  if(estadobotao == 0){
    x=2;//f
    y=1.5;//f
    t=1;//f
  }//f
  if(estadobotao == 1){
    x=4;//f
    y=3.3;//f
    t=2;//f
  }
  if(estadobotao == 2){
     x=6;//f
    y=4.5;//f
    t=3;//f
  }
  if(estadobotao == 3){
     x=8;//f
    y=6.5;//f
    t=4;//f
  }
  if(estadobotao == 4){
     x=10;//f
    y=7.5;//f
    t=5;//f
  }
  if(estadobotao == 5){
    x=12;//f
    y=8.5;//f
    t=6;//f
  }
  if(estadobotao == 6){
     x=14;//f
    y=10.5;//f
    t=7;//f
  }
  

 if( (Litros>0)&&(Litros<t)){
  digitalWrite (ledVerde,HIGH);
  digitalWrite (ledAmarelo,LOW);   
  digitalWrite (ledVermelho,LOW);         
 }
 if ((Litros >t)&&(Litros<y)){
  digitalWrite (ledAmarelo,HIGH);    
  digitalWrite (ledVerde,LOW);   
  digitalWrite (ledVermelho,LOW);     
 }
 if ((Litros>y)&&(Litros<x)){
  digitalWrite (ledAmarelo,LOW);    
  digitalWrite (ledVerde,LOW);   
  digitalWrite (ledVermelho,HIGH);      
 }
 if ((Litros > x) && (acionamentoExterno==false))
 {
  digitalWrite (rele,HIGH);
  digitalWrite (ledVerde,LOW);   
  digitalWrite (ledAmarelo, LOW);
  digitalWrite (ledVermelho,HIGH);     
  delay(1000);
  digitalWrite (ledVermelho,LOW);     
  delay(1000);
  digitalWrite (ledVermelho,HIGH);     
  delay(1000);
  digitalWrite (ledVermelho,LOW);     
  delay(1000);
  digitalWrite (ledVermelho,HIGH);     
  
  Serial.println("Volume atingido");
 }
 
 if(digitalRead(push)==HIGH){
  acionamentoExterno = !acionamentoExterno;   
 }

 if (acionamentoExterno==true){
  digitalWrite (rele,LOW);
  digitalWrite (ledVerde,LOW);   
  digitalWrite (ledAmarelo, LOW);
  digitalWrite (ledVermelho,LOW);     
     
 }
 // Neste conjunto de linhas fizemos a média das leituras obtidas a cada 1 minuto
 if (i == 60)
 {
 Min++;
 lcd.print(Min);
  
 if (Min >= 60)
 {
 Min = 0;
 }
 media = media / 60; //faz a média
 Serial.print("nMedia por minuto = "); //Imprime a frase Media por minuto =
 Serial.print(media); //Imprime o valor da media
 Serial.println(" L/min - "); //Imprime L/min
 media = 0; //Zera a variável media para uma nova contagem
 i = 0; //Zera a variável i para uma nova contagem
 }
  
}
  
//declaracoes das funcoes
