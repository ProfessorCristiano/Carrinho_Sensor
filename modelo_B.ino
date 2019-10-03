/// Inclompleto///


////////////////////////////NOTAS////////////////////////////////
// O Modelo B utiliza ponte L298N
// Para não fazer pontes de ligações com a alimentação e o terra
// E para deixar as ligações do sensor de distância e servo motor mais "Bonitinhos" na placa, e fáceis dos alunos reproduzirem 
// eu optei por deixar as portas digitais configuradas de forma a se portarem como portas de alimentação 5V e GND
// Isso irá aparecer na parte do setup e estará devidamente comentada
//
/////////////////////////////////////////////////////////

#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A1                 // Pino do Sensor Trigger
#define ECHO_PIN A0                 // Pino do Sensor Echo
#define MAX_DISTANCE 200            // Distância Máxima de colisão em cm
#define MAX_SPEED 190               // Define Velocidade Máxima do Motor. Váximo possível 255
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);     // Criação do objeto sonar

AF_DCMotor motor1(1, MOTOR12_1KHZ);                  // Configura motor utilizado pelo Shield
AF_DCMotor motor2(2, MOTOR12_1KHZ);                  // Configura motor utilizado pelo Shield

Servo myservo;                                       // instancia classe Servo como instância myservo

boolean VaParaFrente=false;
int distancia = 100;                                 // cria variável para guardar a distância (cm)
int speedSet = 0;                                    // cria variável para guardar o incremento de velocidade

int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;


void setup() {
  
  // configurar as portas de alimentação do sensor e servo motor //
   pinMode(7, OUTPUT);       // porta de vcc do sensor de proximidade
   digitalWrite(7, HIGH)     // valor alto é equivalente a 5v
   pinMode(4, OUTPUT);       // porta de GND do sensor de proximidade
   digitalWrite(4, LOW)      // valor baixo é equivalente a GND 
  //
  pinMode(13, OUTPUT);       // porta de vcc do servo motor
  digitalWrite(13, HIGH)     // valor alto é equivalente a 5v   
  // Fim da gambiarra /////////////
    
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);   

  myservo.attach(12);                                // configura a instância myservo na porta 12
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
 int distanciaR = 0;                                //cria variável para guardar a distância à direita
 int distanciaL =  0;                               //cria variável para guardar a distância à esquerda
 delay(40);
 
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
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  } 
  
void moveForward() // Função para andar para frente
{ 

 if(!VaParaFrente)
  {
    VaParaFrente=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);      
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // inicia o movimento devagar pois os motores DC tem dificuldade de fazer um arranque bruto, também ajuda a economizar bateria
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
   }
  }
}

void moveBackward() // Função para andar para trás
{
    VaParaFrente=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // inicia o movimento devagar pois os motores DC tem dificuldade de fazer um arranque bruto, também ajuda a economizar bateria
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
  }
}  

void turnRight()// Função para virar a direita
{
  motor1.run(FORWARD);
  motor2.run(BACKWARD);     
  delay(300);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);      
} 
 
void turnLeft() // Função para virar a esquerda
{
  motor1.run(BACKWARD);     
  motor2.run(FORWARD);     
  delay(300);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
}  
