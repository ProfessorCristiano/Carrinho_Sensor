/// COMPLETO///
///TESTADO E FUNCIONANDO /// 


////////////////////////////NOTAS////////////////////////////////
// O Modelo B utiliza ponte L298N
// Para não fazer pontes de ligações com a alimentação e o terra
// E para deixar as ligações do sensor de distância e servo motor mais "Bonitinhos" na placa, e fáceis dos alunos reproduzirem 
// eu optei por deixar as portas digitais configuradas de forma a se portarem como portas de alimentação 5V e GND
// Isso irá aparecer na parte do setup e estará devidamente comentada
//
/////////////////////////////////////////////////////////

#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN 5                 // Pino do Sensor Trigger
#define ECHO_PIN 6                 // Pino do Sensor Echo
#define MAX_DISTANCE 200            // Distância Máxima de colisão em cm


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);     // Criação do objeto sonar

Servo myservo;                                       // instancia classe Servo como instância myservo

boolean VaParaFrente=false;
int distancia = 100;                                 // cria variável para guardar a distância (cm)
int speedSet = 0;                                    // cria variável para guardar o incremento de velocidade


                                                     // cria as variáveis a seguir com os nomes INI das portas de 
                                                     // conexões da ponte para facilitar a conexão e interpretação
                                                     //
int INI1 = 8;                                         // cria variável INI1 com valor 8
int INI2 = 9;                                         // cria variável INI2 com valor 9
int INI3 = 10;                                        // cria variável INI3 com valor 10
int INI4 = 11;                                        // cria variável INI4 com valor 11


void setup() {
  
  // configurar as portas de alimentação do sensor e servo motor //
   pinMode(7, OUTPUT);       // porta de vcc do sensor de proximidade
   digitalWrite(7, HIGH);    // valor alto é equivalente a 5v
   pinMode(4, OUTPUT);       // porta de GND do sensor de proximidade
   digitalWrite(4, LOW);     // valor baixo é equivalente a GND 
  //
   pinMode(13, OUTPUT);       // porta de vcc do servo motor
   digitalWrite(13, HIGH);     // valor alto é equivalente a 5v   
  // Fim da gambiarra /////////////
    
 pinMode(INI1, OUTPUT);
 pinMode(INI2, OUTPUT);
 pinMode(INI3, OUTPUT);
 pinMode(INI4, OUTPUT);   

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
  digitalWrite(INI1, LOW);
  digitalWrite(INI2, LOW);
  digitalWrite(INI3, LOW);
  digitalWrite(INI4, LOW);
  } 
  
void moveForward() // Função para andar para frente
{ 

 if(!VaParaFrente)
  {
    VaParaFrente=true;
    digitalWrite(INI1, HIGH);
    digitalWrite(INI2, LOW);
    digitalWrite(INI3, HIGH);
    digitalWrite(INI4, LOW);
  }
}

void moveBackward() // Função para andar para trás
{
    VaParaFrente=false;
    digitalWrite(INI1, LOW);
    digitalWrite(INI2, HIGH);
    digitalWrite(INI3, LOW);
    digitalWrite(INI4, HIGH);
}  

void turnRight()// Função para virar a direita
{
    
  digitalWrite(INI1, HIGH);
  digitalWrite(INI2, LOW);
  digitalWrite(INI3, LOW);
  digitalWrite(INI4, HIGH);
  delay(600);
  digitalWrite(INI1, HIGH);
  digitalWrite(INI2, LOW);
  digitalWrite(INI3, HIGH);
  digitalWrite(INI4, LOW); 
} 
 
void turnLeft() // Função para virar a esquerda
{
  digitalWrite(INI1, LOW);
  digitalWrite(INI2, HIGH);
  digitalWrite(INI3, HIGH);
  digitalWrite(INI4, LOW);  
  delay(600);
  digitalWrite(INI1, HIGH);
  digitalWrite(INI2, LOW);
  digitalWrite(INI3, HIGH);
  digitalWrite(INI4, LOW);
}  
