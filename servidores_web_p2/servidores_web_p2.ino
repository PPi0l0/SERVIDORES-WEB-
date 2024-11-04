#include <WiFi.h>
#define PORT 80
WiFiServer server(PORT);

const uint8_t sg1[7] = {26,27,32,33,25,14,12};
const uint8_t sg2[7] = {5,18,23,21,19,4,2};

const char* ssid     = "Fibertel WiFi268 2.4";
const char* password = "01421442852";

const uint8_t dis[10][7] = {
  {0,0,0,0,0,0,0},  //0
  {0,1,1,0,0,0,0},  //1
  {1,1,0,1,1,0,1},  //2
  {1,1,1,1,0,0,1},  //3
  {0,1,1,0,0,1,1},  //4
  {1,0,1,1,0,1,1},  //5
  {1,0,1,1,1,1,1},  //6
  {1,1,1,0,0,0,0},  //7
  {1,1,1,1,1,1,1},  //8
  {1,1,1,0,0,1,1},  //9
};

String estadoSalida = "off";
int aux = 0;
int contconexion=0;
const int salida = 2;

String header;
String pagina = "<!DOCTYPE html>"

"<html>"
"<head>"
"<meta charset='utf-8' />"
"<title> NUMEROS </title>"
"</head>"
"<body>"
"<center>"
"<table border = 0> "
"<tr>"
" <td> <p> <a href='/dece'><button style='height:100px;width:150px'> DECENA </button></a></p></td> "
" <td>  <p>  <a href='/desi'><button style='height:100px;width:150px'> DECIMAL </button></a></p></td> "
"</tr></table>"

"<table border = 0>"
"<tr>"
"    <td>  <p>  <a href='/n7'><button style='height:50px;width:100px'> 7 </button></a></p></td> "
"    <td>  <p>  <a href='/n8'><button style='height:50px;width:100px'> 8 </button></a></p></td>"
"    <td>  <p>  <a href='/n9'><button style='height:50px;width:100px'> 9 </button></a></p></td>"
"</tr>"
"<tr>"
"    <td>  <p>  <a href='/n4'><button style='height:50px;width:100px'> 4 </button></a></p></td> "
"    <td>  <p>  <a href='/n5'><button style='height:50px;width:100px'> 5 </button></a></p></td>"
"    <td>  <p>  <a href='/n6'><button style='height:50px;width:100px'> 6 </button></a></p></td>"
"</tr>"
"<tr>"
"    <td>  <p>  <a href='/n1'><button style='height:50px;width:100px'> 1 </button></a></p></td> "
"    <td>  <p>  <a href='/n2'><button style='height:50px;width:100px'> 2 </button></a></p></td>"
"    <td>  <p>  <a href='/n3'><button style='height:50px;width:100px'> 3 </button></a></p></td>"
"</tr>"

"<tr>"
"    <td>  </td> "
"    <td>  <p>  <a href='/n0'><button style='height:50px;width:100px'> 0 </button></a>  </p> </td>"
"    <td>  </td>"
"</tr>"
"</center>"
"</body>"
"</table>"
"</html>";


void setup() {
  
  Serial.println("");


  
  Serial.begin(115200);
  for(int i = 0; i < 7; i++){
    pinMode(sg1[i], OUTPUT);
    pinMode(sg2[i], OUTPUT);
  }
  
  pinMode(salida, OUTPUT);
  digitalWrite(salida, LOW);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) {
  ++contconexion;
  delay(500);
  Serial.print(".");
  }
  if (contconexion <50) {
    Serial.println("");
    Serial.println("WiFi conectado");
    Serial.println(WiFi.localIP());
    server.begin(); // iniciamos el servidor
  }
  else {
    Serial.println("");
    Serial.println("Error de conexion");
  }
}

void loop(){
  WiFiClient client = server.available();  
  if (client) {                           
  Serial.println("New Client.");        
  String currentLine = "";              
  while (client.connected()) {          
    if (client.available()) {           
      char c = client.read();           
      Serial.write(c);                  
      header += c;
      if (c == '\n') {                  
            if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
          if(header.indexOf("GET/dece")>=0){
            aux = 1;
          } else if(header.indexOf("GET/deci")>=0){
            aux = 0;
          }

          if(aux = 1){
            if(header.indexOf("GET/n9")>=0){
              Serial.println("GPIO n9");
              estadoSalida = "n9";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg1[i],dis[9][i]);
                
              }} else if(header.indexOf("GET/n8")>=0){
              Serial.println("GPIO n8");
              estadoSalida = "n8";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg1[i],dis[8][i]);
                
              }}else if(header.indexOf("GET/n7")>=0){
              Serial.println("GPIO n7");
              estadoSalida = "n7";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg1[i],dis[7][i]);
                
              }}else if(header.indexOf("GET/n6")>=0){
              Serial.println("GPIO n6");
              estadoSalida = "n6";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg1[i],dis[6][i]);
                
              }}else if(header.indexOf("GET/n5")>=0){
              Serial.println("GPIO n5");
              estadoSalida = "n5";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg1[i],dis[5][i]);
                
              }}else if(header.indexOf("GET/n4")>=0){
              Serial.println("GPIO n4");
              estadoSalida = "n4";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg1[i],dis[4][i]);
                
              }}else if(header.indexOf("GET/n3")>=0){
              Serial.println("GPIO n3");
              estadoSalida = "n3";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg1[i],dis[3][i]);
                
              }}else if(header.indexOf("GET/n2")>=0){
              Serial.println("GPIO n2");
              estadoSalida = "n2";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg1[i],dis[2][i]);
                
              }}else if(header.indexOf("GET/n1")>=0){
              Serial.println("GPIO n1");
              estadoSalida = "n1";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg1[i],dis[1][i]);
                
              }}else if(header.indexOf("GET/n0")>=0){
              Serial.println("GPIO n0");
              estadoSalida = "n0";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg1[i],dis[0][i]);
              }}
          } else if( aux = 0){
            if(header.indexOf("GET/n9")>=0){
              Serial.println("GPIO n9");
              estadoSalida = "n9";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg2[i],dis[9][i]);
                
              }} else if(header.indexOf("GET/n8")>=0){
              Serial.println("GPIO n8");
              estadoSalida = "n8";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg2[i],dis[8][i]);
                
              }}else if(header.indexOf("GET/n7")>=0){
              Serial.println("GPIO n7");
              estadoSalida = "n7";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg2[i],dis[7][i]);
                
              }}else if(header.indexOf("GET/n6")>=0){
              Serial.println("GPIO n6");
              estadoSalida = "n6";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg2[i],dis[6][i]);
                
              }}else if(header.indexOf("GET/n5")>=0){
              Serial.println("GPIO n5");
              estadoSalida = "n5";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg2[i],dis[5][i]);
                
              }}else if(header.indexOf("GET/n4")>=0){
              Serial.println("GPIO n4");
              estadoSalida = "n4";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg2[i],dis[4][i]);
                
              }}else if(header.indexOf("GET/n3")>=0){
              Serial.println("GPIO n3");
              estadoSalida = "n3";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg2[i],dis[3][i]);
                
              }}else if(header.indexOf("GET/n2")>=0){
              Serial.println("GPIO n2");
              estadoSalida = "n2";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg2[i],dis[2][i]);
                
              }}else if(header.indexOf("GET/n1")>=0){
              Serial.println("GPIO n1");
              estadoSalida = "n1";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg2[i],dis[1][i]);
                
              }}else if(header.indexOf("GET/n0")>=0){
              Serial.println("GPIO n0");
             
              estadoSalida = "n0";
              for(int i = 0; i < 7; i++){
                digitalWrite(sg2[i],dis[0][i]);
              }}
          }

                      
            // Muestra la página web
            client.println(pagina);
                               
            client.println();
          break;
          } else currentLine = "";
      } else if (c != '\r') { 
            currentLine += c;   
        }
      }
  }
  header = "";
  client.stop();
  Serial.println("Client disconnected.");
  Serial.println("");
  }
}
