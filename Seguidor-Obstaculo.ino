/// COMPLETO///
///TESTADO E FUNCIONANDO /// 


////////////////////////////NOTAS////////////////////////////////
// O Modelo B utiliza ponte L298N
//
/////////////////////////////////////////////////////////

#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN 18                 // Pino do Sensor Trigger
#define ECHO_PIN 17                 // Pino do Sensor Echo
#define MAX_DISTANCE 200            // Distância Máxima de colisão em cm


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);     // Criação do objeto sonar

Servo myservo;                                       // instancia classe Servo como instância myservo

boolean VaParaFrente=false;
int distancia = 100;                                 // cria variável para guardar a distância (cm)
int velocidade = 250;                                // Cria variável responsável por controlar a velocidade dos motores

                                                     // cria as variáveis a seguir com os nomes INI das portas de 
                                                     // conexões da ponte para facilitar a conexão e interpretação
                                                     
int INI1 = 10;                                       // cria variável INI1 com valor 10
int INI2 = 9;                                        // cria variável INI2 com valor 9
int INI3 = 5;                                        // cria variável INI3 com valor 5
int INI4 = 6;                                        // cria variável INI4 com valor 6

int MServo = 11;                                     // cria variável para o Servo motor com valor 11

//Definição dos pinos de controle do motor
//#define M1 INI2 // Pino_Velocidade 1º Motor ( 0 a 255)_ Porta ATV_A ponte H;
//#define M2 INI4 //Pino_Velocidade 2º Motor ( 0 a 255) _ Porta ATV_B ponte H;
//#define dir1 INI1 //Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
//#define dir2 INI3 //Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;

//Definição dos pinos dos sensores
#define pin_S1 15                                     // Cria a Variável do Sensor da Direita
#define pin_S2 14                                     // Cria a Variável do Sensor da Esquerda
#define pin_S3 16                                     // Cria a Variável do Sensor do Centro
bool Sensor1 = 0;
bool Sensor2 = 0;
bool Sensor3 = 0;


void setup() {
//Definimos os pinos de controle dos motores como saída
  pinMode(INI1, OUTPUT);
  pinMode(INI2, OUTPUT);
  pinMode(INI3, OUTPUT);
  pinMode(INI4, OUTPUT);

//Definimos a direção inicial do motor como 0, isso fará com que ambos os motores girem para frente
  digitalWrite(INI1, 0);
  digitalWrite(INI2, 0);
  digitalWrite(INI3, 0);
  digitalWrite(INI4, 0);

//Definimos os pinos dos sensores como entrada
  pinMode(pin_S1, INPUT);
  pinMode(pin_S2, INPUT);
  pinMode(pin_S3, INPUT);

//Definimos o Servo moto
  myservo.attach(MServo);                                // configura a instância myservo na porta 12
  myservo.write(90);                                 // posição inicial do servo 90 graus
  delay(2000);                                       // espera dois segundos 
  distancia = readPing();                            // linhas abaixo ele faz 4 leituras seguidas
  delay(100);
  distancia = readPing();
  delay(100);
  distancia = readPing();
  delay(100);
  distancia = readPing();
  delay(100);
}

void loop() {

//Neste processo armazenamos o valor lido pelo sensor na variável que armazena tais dados.
Sensor1 = digitalRead(pin_S1);
Sensor2 = digitalRead(pin_S2);
Sensor3 = digitalRead(pin_S3);

//Aqui está toda a lógica de comportamento do robô: Para a cor branca atribuímos o valor 0 e, para a cor preta, o valor 1.
if((Sensor1 == 0) && (Sensor2 == 0)){ // Se detectar na extremidade das faixas duas cores brancas
// Ambos motores ligam na mesma velocidade
    analogWrite(INI1, velocidade);
    analogWrite(INI2, 0);
    analogWrite(INI3, velocidade);
    analogWrite(INI4, 0);
}

if((Sensor1 == 1) && (Sensor2 == 0)){ // Se detectar um lado direito preto e o outro esquerdo branco
// O motor direito desliga
// O motor esquerdo fica ligado, fazendo assim o carrinho virar
    analogWrite(INI1, 0);
    analogWrite(INI2, 0);
    analogWrite(INI3, velocidade);
    analogWrite(INI4, 0);

}

if((Sensor1 == 0) && (Sensor2 == 1)){ // Se detectar um lado direito branco e o outro esquerdo preto
//O motor 1 fica ligado
// O motor 2 desliga, fazendo assim o carrinho virar no outro sentido
    analogWrite(INI1, velocidade);
    analogWrite(INI2, 0);
    analogWrite(INI3, 0);
    analogWrite(INI4, 0);
}

 
 int distanciaR = 0;                                //cria variável para guardar a distância à direita
 int distanciaL =  0;                               //cria variável para guardar a distância à esquerda
 //delay(40);
 
 if(distancia<=15)                                  // se distância menor que 15 (cm)
 {
  moveStop();                                       // para de mover
  delay(100);                                       // espera um décimo de segundo (100 ms)
  moveBackward();                                   // anda para trás
  delay(300);                                       // por três décimos de segundo (300 ms)
  moveStop();                                       // para de mover 
  delay(200);                                       // por dois décimos de segundo (200 ms)
  distanciaR = lookRight();                         // distância da direita igual a função lookRigth()
  delay(200);                                       // espera por dois décimos de segundo (200 ms)
  distanciaL = lookLeft();                          // distância da esquerda igual a função lookLeft()
  delay(200);                                       // espera por dois décimos de segundo (200 ms)

  if(distanciaR>=distanciaL)                        // se distância da direita maior que a distência da esquerda
  {
    turnRight();                                    // Vira para Direita
    moveStop();                                     // para de mover
  }else
  {
    turnLeft();                                     // Vira para Esquerda
    moveStop();                                     // para de mover
  }
 }else
 {
  moveForward();                                   // anda para frente
 }
 distancia = readPing();                           // mede a distância
}

int lookRight() // Função Olha para direita
{
    myservo.write(10); 
    delay(500);
    int distancia = readPing();
    delay(100);
    myservo.write(90); 
    return distancia;
}

int lookLeft() // Função Olha para esquerda
{
    myservo.write(160); 
    delay(500);
    int distancia = readPing();
    delay(100);
    myservo.write(90); 
    return distancia;
    delay(100);
}

int readPing()  // Função para fazer a leitura das distâncias
{ 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {  // Função para parar os motores
    analogWrite(INI1, velocidade);
    analogWrite(INI2, velocidade);
    analogWrite(INI3, velocidade);
    analogWrite(INI4, velocidade);
  } 
  
void moveForward() // Função para andar para frente
{ 

 if(!VaParaFrente)
  {
    VaParaFrente=true;
    analogWrite(INI1, velocidade);
    analogWrite(INI2, 0);
    analogWrite(INI3, velocidade);
    analogWrite(INI4, 0);
  }
}

void moveBackward() // Função para andar para trás
{
    VaParaFrente=false;
    analogWrite(INI1, 0);
    analogWrite(INI2, velocidade);
    analogWrite(INI3, 0);
    analogWrite(INI4, velocidade);
}  

void turnRight()// Função para virar a direita
{

    
  analogWrite(INI1, velocidade);
  analogWrite(INI2, 0);
  analogWrite(INI3, 0);
  analogWrite(INI4, velocidade);
  delay(600);
  analogWrite(INI1, velocidade);
  analogWrite(INI2, 0);
  analogWrite(INI3, velocidade);
  analogWrite(INI4, 0); 
} 
 
void turnLeft() // Função para virar a esquerda
{
  analogWrite(INI1, 0);
  analogWrite(INI2, velocidade);
  analogWrite(INI3, velocidade);
  analogWrite(INI4, 0);  
  delay(600);
  analogWrite(INI1, velocidade);
  analogWrite(INI2, 0);
  analogWrite(INI3, velocidade);
  analogWrite(INI4, 0);
}  
