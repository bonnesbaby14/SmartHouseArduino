#include <Servo.h>
#include <Keypad.h>
#include <DHT.h>
//claseeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee/////////////////////////////////////////////////////////////////////

class Habitacion {


  public:
    int pinT, pinM, pinL, pinV, pinP, id;
    String nombre;
    float valorT, valorM, valorL, valorV, valorP, temperatura;
    Servo servo;




    Habitacion() {}
    Habitacion(String _nombre, int _pinT, int _pinM, int _pinV, int _pinP, int _pinL, int _id , float _temperatura) {
      id = _id;
      pinT = _pinT;
      pinM = _pinM;
      pinV = _pinV;
      pinL = _pinL;
      temperatura = _temperatura;

      pinP = _pinP;
      nombre = _nombre;
      valorT = 0.0;
      valorM = 1.0;
      valorL = 0.0;
      valorV = 0.0;
      valorP = 0.0;

      pinMode(pinT, INPUT);
      pinMode(pinM, OUTPUT);
      pinMode(pinL, INPUT);
      pinMode(pinV, INPUT);
      pinMode(pinP, INPUT);
      servo.attach(pinM, 544, 3700);
      servo.write(1.0);




    }
    float Habitacion::getTemperatura() {
#define DHTPIN  pinT
      DHT dht(DHTPIN, DHT11);
      dht.begin();
      delay(100);
      float s = dht.readTemperature();
      if (isnan(s)) {
        s = valorT;
      } else {
        valorT = s;
      }
      return s  ;
    }



};////////////////////////////////////////////////////////////////////////////////////fin de la clase

//variables universales para todo el programa////////////////////////////


const byte COLUMNAS = 3;
const byte FILAS = 4;
byte pinsFilas[FILAS] = {39, 41, 43, 45};
byte pinsColumnas[COLUMNAS] = {47, 49, 51};

String clave1, clave2, clave3, upLight, offLight;

char teclas [FILAS][COLUMNAS] = {

  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'E', '0', 'F'}

};
int contadorHabitaciones;
Habitacion habitaciones[30];
int flatThread;
int hora = 0, minuto = 0, segundo = 0;




void setup() {
  contadorHabitaciones = 0;
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(200);
  getConf();
  flatThread = 0;




}

void loop() {
  // put your main code here, to run repeatedly:
  ///






  long timee = micros();

  if (flatThread == 0) {
    //hilo uno para enviar datos de senores
    flatThread = 1;
    String data = "";
    while (micros() < timee + 200000) {
      data = "";

      for (int y = 0; y < contadorHabitaciones; y++) {
        data += "/" + String(habitaciones[y].getTemperatura()) + "-" + String(habitaciones[y].valorM) + "-" + String(habitaciones[y].valorV) + "-" + String(habitaciones[y].valorP) + "-" + String(habitaciones[y].valorL) + "-" + String(habitaciones[y].id);

      }



    }

    Serial.print("A");
    delay(10);
    Serial.print(data);
  }





  timee = micros();
  if (flatThread == 1) {
    //hilo para checar temperatura
    flatThread = 2;


    while (micros() < timee + 200000) {

      for (int x = 0; x < contadorHabitaciones; x++) {

        if (habitaciones[x].valorT < habitaciones[x].temperatura) {
          //la habitacion es menor a la que se requiere
          //se debe cerrar ventanas


          if (1.1 < (habitaciones[x].temperatura - habitaciones[x].valorT) < 3) {
            habitaciones[x].valorM -= (habitaciones[x].valorT * .25);


          } else if (3.1 < (habitaciones[x].temperatura - habitaciones[x].valorT) < 4) {
            habitaciones[x].valorM -= (habitaciones[x].valorT * .50);

          } else if (4.1 < (habitaciones[x].temperatura - habitaciones[x].valorT) < 5) {
            habitaciones[x].valorM -= (habitaciones[x].valorT * .75);

          } else if (5 < (habitaciones[x].temperatura - habitaciones[x].valorT)) {
            habitaciones[x].valorM = 180;
          }
          if ( habitaciones[x].valorM <= 0) {
            habitaciones[x].valorM = 1;
          }

        } else {

          //la temperatra es mayor a la que se requiere
          //se debe abrir ventanas
          if (habitaciones[x].valorM == 0) {
            habitaciones[x].valorM++;
          }


          if (1.1 < (habitaciones[x].valorT - habitaciones[x].temperatura) < 3) {

            habitaciones[x].valorM += (habitaciones[x].valorT * .25);

          } else if (3.1 < (habitaciones[x].valorT - habitaciones[x].temperatura) < 4) {
            habitaciones[x].valorM += (habitaciones[x].valorT * .5);
          } else if (4.1 < (habitaciones[x].valorT - habitaciones[x].temperatura) < 5) {
            habitaciones[x].valorM += (habitaciones[x].valorT * .75);
          } else if (5 < (habitaciones[x].valorT - habitaciones[x].temperatura)) {
            habitaciones[x].valorM = 1;
          }


          if ( habitaciones[x].valorM >= 180) {
            habitaciones[x].valorM = 180;
          }
        }

        habitaciones[x].servo.write(habitaciones[x].valorM);

      }


    }

  }





  timee = micros();
  if (flatThread == 2) {
    //leer configiracion basica de la casa
    flatThread = 0;

    while (micros() < timee + 200000) {

      //////////////////////////////////////
delay(10);
      Serial.print("H");
      
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

        String z[5];
        int p = 0;
        while ( token2 != NULL ) {
          z[p] = String(token2);



          token2 = strtok(NULL, s2);
          p++;

        }


        clave1 = z[0];
        clave2 = z[1];
        clave3 = z[2];
        upLight = z[3];
        offLight = z[4];







        ////////////////


        y++;
      }

      //////////////////////////////////////




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

    String z[8];
    int p = 0;
    while ( token2 != NULL ) {
      z[p] = String(token2);



      token2 = strtok(NULL, s2);
      p++;

    }

    habitaciones[y] = Habitacion(String(z[0]), String(z[1]).toInt(), String(z[2]).toInt(), String(z[3]).toInt(), String(z[4]).toInt(), String(z[5]).toInt(), String(z[6]).toInt(), String(z[7]).toInt());
    contadorHabitaciones++;






    ////////////////


    y++;
  }

}
