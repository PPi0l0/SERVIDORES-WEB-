#include <WiFi.h>

#define PORT 80
WiFiServer server(PORT);

const uint8_t l [5] = {2,17, 18, 19, 22,};
const char* ssid     = "Fibertel WiFi268 2.4";
const char* password = "01421442852";


int contconexion = 0;

String header;

String estadoSalida = "off";

const int salida = 2;

String pagina = "<!DOCTYPE html>"
"<html>"
"<head>"
"<meta charset='utf-8' />"
"<title>Servidor Web ESP32</title>"
"</head>"
"<body>"
"<center>"
"<table border = 0>" 
"<thead>"
"<tr>"
"<td> <p><a href='/an1'><button style='height:100px;width:200px'>Animacion 1</button></a></p></td> <td> </td>"
"<td><p><a href='/an2'><button style='height:100px;width:200px'>Animacion 2</button></a></p> </td> <td> </td>"
"<td><p><a href='/off'><button style='height:100px;width:200px'>OFF</button></a></p> </td>"
"</tr>"
"</thead>"
"</table>"
"</center>"
"</body>"
"</html>";

void setup() {
  Serial.begin(115200);
  Serial.println("");
  pinMode(l[1],OUTPUT);
  pinMode(l[2],OUTPUT);
  pinMode(l[3],OUTPUT);
  pinMode(l[4],OUTPUT);
  pinMode(l[5],OUTPUT);
  
  pinMode(salida, OUTPUT); 
  digitalWrite(salida, LOW);

  // Conexión WIFI
  WiFi.begin(ssid, password);
  //Cuenta hasta 50 si no se puede conectar lo cancela
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { 
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  if (contconexion <50) {
      //para usar con ip fija
      //IPAddress ip(192,168,1,180); 
      //IPAddress gateway(192,168,1,1); 
      //IPAddress subnet(255,255,255,0); 
      //WiFi.config(ip, gateway, subnet); 
      
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

/*----------------------------LOOP----------------------------------*/

void loop(){
  WiFiClient client = server.available();   // Escucha a los clientes entrantes

  if (client) {                             // Si se conecta un nuevo cliente
    Serial.println("New Client.");          // 
    String currentLine = "";                //
    while (client.connected()) {            // loop mientras el cliente está conectado
      if (client.available()) {             // si hay bytes para leer desde el cliente
        char c = client.read();             // lee un byte
        Serial.write(c);                    // imprime ese byte en el monitor serial
        header += c;
        if (c == '\n') {                    // si el byte es un caracter de salto de linea
          // si la nueva linea está en blanco significa que es el fin del 
          // HTTP request del cliente, entonces respondemos:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // enciende y apaga el GPIO
            if (header.indexOf("GET /an1") >= 0) {
              Serial.println("GPIO an1");
              estadoSalida = "an1";
              digitalWrite(l[0],HIGH);
              digitalWrite(l[1],LOW);
              digitalWrite(l[2],HIGH);
              digitalWrite(l[3],LOW);
              digitalWrite(l[4],HIGH);
            }
              else if (header.indexOf("GET /an2") >= 0) {
              Serial.println("GPIO an2");
              estadoSalida = "an2";
              digitalWrite(l[0],LOW);
              digitalWrite(l[1],HIGH);
              digitalWrite(l[2],LOW);
              digitalWrite(l[3],HIGH);
              digitalWrite(l[4],LOW);
            } else if (header.indexOf("GET /off") >= 0) {
              Serial.println("GPIO off");
              estadoSalida = "off";
              digitalWrite(l[0],LOW);
              digitalWrite(l[1],LOW);
              digitalWrite(l[2],LOW);
              digitalWrite(l[3],LOW);
              digitalWrite(l[4],LOW);    
            }
            
            // Muestra la página web
            client.println(pagina);
            
            // la respuesta HTTP temina con una linea en blanco
            client.println();
            break;
          } else { // si tenemos una nueva linea limpiamos currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // si C es distinto al caracter de retorno de carro
          currentLine += c;      // lo agrega al final de currentLine
        }
      }
    }
    // Limpiamos la variable header
    header = "";
    // Cerramos la conexión
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  
}
