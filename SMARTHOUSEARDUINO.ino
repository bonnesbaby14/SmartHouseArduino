#include <MyRealTimeClock.h>

#include <Servo.h>
#include <Keypad.h>
#include <DHT.h>

//claseeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee/////////////////////////////////////////////////////////////////////

class Habitacion {


  public:
    int pinT, pinM, pinL, pinV, pinP, id, pinLuz;
    String nombre;
    float valorT, valorM, valorL, valorV, valorP, temperatura, luz;
    Servo servo;


    Habitacion() {}
    Habitacion(String _nombre, int _pinT, int _pinM, int _pinV, int _pinP, int _pinL, int _id , float _temperatura, float _luz, float _pinLuz) {
      id = _id;
      pinT = _pinT;
      pinM = _pinM;
      pinV = _pinV;
      pinL = _pinL;
      pinLuz = _pinLuz;
      temperatura = _temperatura;
      luz = _luz;

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
      pinMode(18, OUTPUT);
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

    float Habitacion::getLuz() {

      float x = analogRead(pinL);
      float d = x * (100.00 / 1024.00);
      return d;
    }


};////////////////////////////////////////////////////////////////////////////////////fin de la clase

//variables universales para todo el programa////////////////////////////


const byte COLUMNAS = 4;
const byte FILAS = 4;
byte pinsFilas[FILAS] = {37, 39, 41, 43};
byte pinsColumnas[COLUMNAS] = {45, 47, 49, 51};

//entrada del reloj  despues entrada y salida, despues habiltadr de entrada y salida
MyRealTimeClock myRTC(12, 13, 11);


String clave1, clave2, clave3, upLight, offLight, horanow;

char teclas [FILAS][COLUMNAS] = {

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'E', '0', 'F', 'D'}

};
int contadorHabitaciones;
Habitacion habitaciones[30];
int flatThread;
int hora = 0, minuto = 0, segundo = 0;
bool access = false;
bool flatfecha = true;
int escalera1 = 10, escalera2 = 9, escalera3 = 8;

int totalPersonas = 0;

int conteoError = 0;





Keypad teclado = Keypad(makeKeymap(teclas), pinsFilas, pinsColumnas, FILAS, COLUMNAS);







void setup() {

  pinMode(escalera1, INPUT);
  pinMode(escalera2, INPUT);
  pinMode(escalera3, INPUT);

  //luces de escalera
  pinMode(52, OUTPUT);
  pinMode(50, OUTPUT);
  pinMode(48, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(34, OUTPUT);


  //esto es para luces de exterior
  pinMode(2, OUTPUT);

  //pines para el contador de personas
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  //pines para el pir y la alarma
  pinMode(6, OUTPUT);
  pinMode(5, INPUT);



  
  contadorHabitaciones = 0;
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(200);
  getConf();
  flatThread = 0;
  obtenerPass();




}










void loop() {
  // put your main code here, to run repeatedly:
  ///

if(totalPersonas==0){

  if(digitalRead(5)==HIGH){
    delay(50);
    if(digitalRead(5)==HIGH){

digitalWrite(6,HIGH);
String serie="";
char tecla;
     while (true) {
        digitalWrite(17, HIGH);
        delay(800);
        serie = "";
        tecla = NO_KEY;
        while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
          tecla = teclado.getKey();
        }
        serie = serie + String(tecla);
        tecla = NO_KEY;
        while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
          tecla = teclado.getKey();
        }
        serie = serie + String(tecla);
        tecla = NO_KEY;
        while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
          tecla = teclado.getKey();
        }
        serie = serie + String(tecla);
        tecla = NO_KEY;
        while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
          tecla = teclado.getKey();
        }
        serie = serie + String(tecla);
        tecla = NO_KEY;

        while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
          tecla = teclado.getKey();
        }


        serie = serie + String(tecla);
        tecla = NO_KEY;

        if (desencriptar(serie, clave1)) {
          digitalWrite(18, HIGH);
          digitalWrite(17, LOW);
          delay(800);
          digitalWrite(17, LOW);
          digitalWrite(18, LOW);
          digitalWrite(6,LOW);
          break;
        }
      }



    
    }
    }
  }


  getClave();
  lucesTime();
  long timee = micros();

  if (flatThread == 0) {
    //hilo uno para enviar datos de senores
    flatThread = 1;
    String data = "";
    while (micros() < timee + 200000) {
      getClave();
      data = "";

      for (int y = 0; y < contadorHabitaciones; y++) {
        data += "/" + String(habitaciones[y].getLuz()) + "-" + String(habitaciones[y].getTemperatura()) + "-" + String(habitaciones[y].valorM) + "-" + String(habitaciones[y].valorV) + "-" + String(habitaciones[y].valorP) + "-" + String(habitaciones[y].getLuz()) + "-" + String(habitaciones[y].id)+ "-" + String(totalPersonas);

      }



    }

    Serial.print("A");
    delay(10);
    Serial.print(data);
  }




  getClave();
  lucesTime();
  timee = micros();
  if (flatThread == 1) {
    //hilo para checar temperatura
    flatThread = 2;


    while (micros() < timee + 200000) {

      getClave();
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




  getClave();
  lucesTime();
  timee = micros();
  if (flatThread == 2) {
    //leer para el conteo de personas
    flatThread = 3;

    while (micros() < timee + 200000) {

      if (digitalRead(3) == LOW) {


        delay(300);

        totalPersonas++;



      }

      if (digitalRead(4) == LOW) {

        delay(300);

        totalPersonas--;
        if (totalPersonas < 0) {
          totalPersonas = 0;
        }



      }

    }
  }
  getClave();
  lucesTime();
  timee = micros();
  if (flatThread == 3) {
    //leer escaleras
    flatThread = 4;

    while (micros() < timee + 200000) {
      if (digitalRead(escalera1) == LOW) {
        digitalWrite(34, HIGH);
        digitalWrite(36, HIGH);
        digitalWrite(38, HIGH);
        digitalWrite(40, HIGH);
        delay(1400);
        digitalWrite(34, LOW);
        digitalWrite(36, LOW);
        digitalWrite(38, LOW);
        digitalWrite(40, LOW);
      }
      if (digitalRead(escalera2) == LOW) {
        digitalWrite(40, HIGH);
        digitalWrite(42, HIGH);
        digitalWrite(44, HIGH);
        digitalWrite(46, HIGH);
        delay(1400);
        digitalWrite(40, LOW);
        digitalWrite(42, LOW);
        digitalWrite(44, LOW);
        digitalWrite(46, LOW);
      }

      if (digitalRead(escalera3) == LOW) {
        digitalWrite(46, HIGH);
        digitalWrite(48, HIGH);
        digitalWrite(50, HIGH);
        digitalWrite(52, HIGH);
        delay(1400);
        digitalWrite(46, LOW);
        digitalWrite(48, LOW);
        digitalWrite(50, LOW);
        digitalWrite(52, LOW);
      }



    }
  }

  getClave();
  lucesTime();
  timee = micros();
  if (flatThread == 4) {
    //ver la luz
    flatThread = 0;

    while (micros() < timee + 200000) {

      for (int x = 0; x < contadorHabitaciones; x++) {

        float d = habitaciones[x].getLuz();

        if (d < 50) {
          digitalWrite(habitaciones[x].pinLuz, HIGH);

        } else {
          digitalWrite(habitaciones[x].pinLuz, LOW);

        }


      }


    }
  }







}//loop





//////////////////////////////////////////////////////////////////////
// FUNCIONES                                                        //
//                                                                  //
//////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////
// FUNCION PARA DEESCRAGAR CONFIGURACION (HABITACIONES)             //
//////////////////////////////////////////////////////////////////////
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

    String z[10];
    int p = 0;
    while ( token2 != NULL ) {
      z[p] = String(token2);



      token2 = strtok(NULL, s2);
      p++;

    }

    habitaciones[y] = Habitacion(String(z[0]), String(z[1]).toInt(), String(z[2]).toInt(), String(z[3]).toInt(), String(z[4]).toInt(), String(z[5]).toInt(), String(z[6]).toInt(), String(z[7]).toInt(), String(z[8]).toInt(), String(z[9]).toInt());
    contadorHabitaciones++;






    ////////////////


    y++;
  }



}






//////////////////////////////////////////////////////////////////////
// FUNCION PARA ENCRIPTAR                                           //
//////////////////////////////////////////////////////////////////////
String encriptar(String k) {
  String aux = "";
  for (int s = 0; s < k.length() - 1; s++) {

    int f = k.charAt(s) + 10;

    aux = aux + char(f);


  }



  return aux;
}

//////////////////////////////////////////////////////////////////////
// FUNCION PARA DESENCRIPTAR                                        //
//////////////////////////////////////////////////////////////////////
bool desencriptar(String a, String b) {
  String aux = "";
  for (int s = 0; s < a.length(); s++) {

    int f = a.charAt(s) + 10;

    aux = aux + char(f);


  }

  if (aux == b) {
    return true;
  } else {
    return false;
  }

}


//////////////////////////////////////////////////////////////////////
// FUNCION PARA OBTENER LA CLAVE DEL TECLADO                        //
//////////////////////////////////////////////////////////////////////

void getClave() {

  String serie = "";

  char tecla = teclado.getKey();
  if (tecla != NO_KEY) {


    tecla = NO_KEY;

    while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
      tecla = teclado.getKey();
    }
    serie = serie + String(tecla);
    tecla = NO_KEY;
    while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
      tecla = teclado.getKey();
    }
    serie = serie + String(tecla);
    tecla = NO_KEY;
    while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
      tecla = teclado.getKey();
    }
    serie = serie + String(tecla);
    tecla = NO_KEY;
    while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
      tecla = teclado.getKey();
    }
    serie = serie + String(tecla);
    tecla = NO_KEY;

    while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
      tecla = teclado.getKey();
    }


    serie = serie + String(tecla);
    tecla = NO_KEY;


    if (desencriptar(serie, clave1)) {
      digitalWrite(18, HIGH);
      conteoError = 0;
    } else if (desencriptar(serie, clave2)) {
      conteoError = 0;
      digitalWrite(18, HIGH);
    } else if (desencriptar(serie, clave3)) {
      conteoError = 0;
      digitalWrite(18, HIGH);
    } else {
      digitalWrite(18, LOW);
      conteoError++;
      while (conteoError > 2) {
        digitalWrite(17, HIGH);
        delay(800);
        serie = "";
        tecla = NO_KEY;
        while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
          tecla = teclado.getKey();
        }
        serie = serie + String(tecla);
        tecla = NO_KEY;
        while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
          tecla = teclado.getKey();
        }
        serie = serie + String(tecla);
        tecla = NO_KEY;
        while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
          tecla = teclado.getKey();
        }
        serie = serie + String(tecla);
        tecla = NO_KEY;
        while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
          tecla = teclado.getKey();
        }
        serie = serie + String(tecla);
        tecla = NO_KEY;

        while (tecla == NO_KEY || tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == 'E' || tecla == 'F') {
          tecla = teclado.getKey();
        }


        serie = serie + String(tecla);
        tecla = NO_KEY;

        if (desencriptar(serie, clave1)) {
          digitalWrite(18, HIGH);
          digitalWrite(17, LOW);
          delay(800);
          digitalWrite(17, LOW);
          digitalWrite(18, LOW);
          conteoError = 0;
        }
      }
    }


  }

}



void lucesTime() {


  myRTC.updateTime();

  String prueba = String(myRTC.minutes);
  prueba += ":";
  if (myRTC.seconds < 10) {
    prueba += "0";
    prueba += String(myRTC.seconds);
  } else {
    prueba += String(myRTC.seconds);
  }

  if (prueba == upLight) {


    digitalWrite(2, HIGH);
  }
  if (prueba == offLight) {

    digitalWrite(2, LOW);
  }


}


void obtenerPass() {
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

    String z[6];
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
    horanow = z[5];
    while (flatfecha) {



      char str3[200];
      horanow.toCharArray(str3, 200);
      const char s3[2] = ":";
      char *token3;
      token3 = strtok(str3, s3);

      String d[2];
      int p2 = 0;
      while ( token3 != NULL ) {
        d[p2] = String(token3);


        token3 = strtok(NULL, s3);
        p2++;

      }
      myRTC.setDS1302Time( d[1].toInt(), d[0].toInt(), 00, 5 , 11, 12, 2019);

      flatfecha = false;
    }









    ////////////////


    y++;
  }


}
