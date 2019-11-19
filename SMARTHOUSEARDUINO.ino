class Habitacion {
  public:
    int pinT, pinM, pinL, pinV, pinP;
    String nombre;
    float valorT, valorM, valorL, valorV, valorP;
    Habitacion() {}
    Habitacion(String _nombre,int _pinT, int _pinM, int _pinV, int _pinP, int _pinL ) {
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

};

Habitacion habitaciones[30];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(200);
}

void loop() {
  // put your main code here, to run repeatedly:
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

    Serial.print("se entro al while con x=");
    Serial.println(x);
    ///////
    Serial.print("del token ");
    Serial.println(token);
    aux[x] = String(token);
    aux[x] = String(token);
    Serial.print("del array ");
    Serial.println(aux[x]);
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

     habitaciones[y]=Habitacion(String(z[0]),String(z[1]).toInt(),String(z[2]).toInt(),String(z[3]).toInt(),String(z[4]).toInt(),String(z[5]).toInt());



     
      
 

    ////////////////


    y++;
  }


  ///

Serial.println("fin del loop");
Serial.println(habitaciones[0].nombre);
Serial.println(habitaciones[1].nombre);
}
