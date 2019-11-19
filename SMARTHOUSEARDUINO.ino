class sensor {
  public:
    int pin;
    String tipo;
    float valor;

};

sensor* temperatura = new sensor[20];
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
    Serial.println(aux[y]);

 char str2[500];
  aux[y].toCharArray(str2, 500);
  const char s2[2] = "-";
  char *token2;
token2=strtok(str2,s2);


 while ( token2 != NULL ) {

    Serial.println(token2);
  



    token2 = strtok(NULL, s2);

  }


  
    ////////////////


    y++;
  }


///


}
