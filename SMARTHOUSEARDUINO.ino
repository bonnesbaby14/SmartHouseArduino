class sensor{
  public:
  int pin;
   String tipo;
   float valor;
  
  };

sensor* temperatura=new sensor[20];
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.setTimeout(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("S");
  while(!Serial.available());
  String confi=Serial.readString();

  
  

}
