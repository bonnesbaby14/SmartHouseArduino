#include <MsTimer2.h>

#include <DHT.h>
//claseeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee/////////////////////////////////////////////////////////////////////
class Habitacion {


  public:
    int pinT, pinM, pinL, pinV, pinP;
    String nombre;
    float valorT, valorM, valorL, valorV, valorP;




    Habitacion() {}
    Habitacion(String _nombre, int _pinT, int _pinM, int _pinV, int _pinP, int _pinL ) {
      pinT = _pinT;
      pinM = _pinM;
      pinV = _pinV;
      pinL = _pinL;

      pinP = _pinP;
      nombre = _nombre;
      valorT = 0.0;
      valorM = 0.0;
      valorL = 0.0;
      valorV = 0.0;
      valorP = 0.0;

      pinMode(pinT, INPUT);
      pinMode(pinM, INPUT);
      pinMode(pinL, INPUT);
      pinMode(pinV, INPUT);
      pinMode(pinP, INPUT);




    }
    float Habitacion::getTemperatura() {
#define DHTPIN  pinT
      DHT dht(DHTPIN, DHT11);
      dht.begin();

      return   dht.readTemperature();
    }



};////////////////////////////////////////fin de la clase

//variables universales para todo el programa
int contadorHabitaciones;
Habitacion habitaciones[30];
int flatThread;

void fun() {

}




void setup() {
  contadorHabitaciones = 0;
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(200);
  getConf();
  flatThread=0;


 // MsTimer2::set(220, fun);
//  MsTimer2::start();


}

void loop() {
  // put your main code here, to run repeatedly:
  ///



 

  
 long timee = micros();
  if (flatThread == 0) {
     flatThread = 1;
       Serial.println("comparacion para el 1");
  Serial.print(micros());
    Serial.print("<");
      Serial.println(timee + 200000);
  Serial.println("......................................");
    while (micros() < timee + 200000) {
     
      Serial.print(micros());
  Serial.print("==");
  Serial.println(timee + 200000);


      Serial.println("1");

    }

  }
 timee = micros();
  if (flatThread == 1) {
    flatThread = 2;

  Serial.println("comparacion para el 2");
  Serial.print(micros());
    Serial.print("<");
      Serial.println(timee + 200000);
  Serial.println("......................................");

    while (micros() < timee + 200000) {
      Serial.println("2");
    }
    
  }

  
  timee = micros();
  if (flatThread == 2) {
    flatThread = 0;
  Serial.println("comparacion para el 3");
  Serial.print(micros());
    Serial.print("<");
      Serial.println(timee + 200000);
  Serial.println("......................................");
    while (micros() < timee + 200000) {
      Serial.println("3");
    }
  }
  

  

}







//Metodoooooooooooooooooooooooooood//////////////////////////////////////////////////////////////////////////////////
void getConf() {
  Serial.print("S");
  while (!Serial.available());
  String confi = Serial.readString();

  char str[1024];
  confi.toCharArray(str, 1024);
  const char s[2] = "/";
  char *token;

  /* get the first token */
  token = strtok(str, s);

  /* walk through other tokens */
  int x = 0;
  String aux[200];
  while ( token != NULL ) {
    aux[x] = String(token);
    aux[x] = String(token);
    x++;
    token = strtok(NULL, s);
  }
  ///
  int y = 0;
  while (aux[y] != NULL) {
    char str2[500];
    aux[y].toCharArray(str2, 500);
    const char s2[2] = "-";
    char *token2;
    token2 = strtok(str2, s2);

    String z[6];
    int p = 0;
    while ( token2 != NULL ) {
      z[p] = String(token2);



      token2 = strtok(NULL, s2);
      p++;

    }

    habitaciones[y] = Habitacion(String(z[0]), String(z[1]).toInt(), String(z[2]).toInt(), String(z[3]).toInt(), String(z[4]).toInt(), String(z[5]).toInt());
    contadorHabitaciones++;






    ////////////////


    y++;
  }

}
