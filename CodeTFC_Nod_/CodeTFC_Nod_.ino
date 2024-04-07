

//librairies nécéssaires

#include <WiFi.h>
#include <FirebaseESP32.h>

//Parametres de connection de la carte
#define FIREBASE_HOST "gestioneaudb-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "NDS1Dv3zV5ryBZtqazRrgKFPEL9YtyBnNIzDKuuc"
#define WIFI_SSID "Sam"
#define WIFI_PASSWORD "3265samm"


//Definition de l' objet  FirebaseESP32 data 
FirebaseData firebaseData;

FirebaseJson json;

void printResult(FirebaseData &data);
//Création des variables des capteurs
  const int pinTrig = 5;
  const int pinEcho = 18;
  long temps;
  double hauteurTotReservoir = 2.3; //en décimetre
  //double hauteurVideMin = 0.25;
  double hauteurVide; // en décimetre
  double SectionMoyen = 5.12; //en décimetre carré
  double VolumeEau;
  double TauxRamp;
  double hautVideCor;
  //double CapaciteRese = hauteurTotReservoir*SectionMoyen; //en litres 
  double CapaciteRese = 11.2; //en litres 

 const int Relais = 4;
 int Etat = 0;
void setup()
{
  
  Serial.begin(115200);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");


  String path = "/Test";

  Serial.println("------------------------------------");
  Serial.println("Set double test...");

  for (uint8_t i = 0; i < 10; i++)
  {
    //Also can use Firebase.set instead of Firebase.setDouble
    if (Firebase.setDouble(firebaseData, path + "/Double/Data" + (i + 1), ((i + 1) * 10) + 0.123456789))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.print("VALUE: ");
      printResult(firebaseData);
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }

  Serial.println("------------------------------------");
  Serial.println("Get double test...");

  for (uint8_t i = 0; i < 10; i++)
  {
    //Also can use Firebase.get instead of Firebase.setInt
    if (Firebase.getInt(firebaseData, path + "/Double/Data" + (i + 1)))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.print("VALUE: ");
      printResult(firebaseData);
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }

  Serial.println("------------------------------------");
  Serial.println("Push integer test...");

  for (uint8_t i = 0; i < 5; i++)
  {
    //Also can use Firebase.push instead of Firebase.pushInt
    if (Firebase.pushInt(firebaseData, path + "/Push/Int", (i + 1)))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }

  Serial.println("------------------------------------");
  Serial.println("Push JSON test...");

  for (uint8_t i = 5; i < 10; i++)
  {

    json.clear().add("Data" + String(i + 1), i + 1);

    //Also can use Firebase.push instead of Firebase.pushJSON
    //Json string is not support in v 2.6.0 and later, only FirebaseJson object is supported.
    if (Firebase.pushJSON(firebaseData, path + "/Push/Int", json))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  }

  Serial.println("------------------------------------");
  Serial.println("Update test...");

  for (uint8_t i = 0; i < 5; i++)
  {

    json.set("Data" + String(i + 1), i + 5.5);

    if (Firebase.updateNode(firebaseData, path + "/float", json))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      //No ETag available
      Serial.print("VALUE: ");
      printResult(firebaseData);
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
 
  
  }
  //initialisation des pins du capteur
  pinMode(pinTrig,OUTPUT);
  pinMode(pinEcho,INPUT);
  pinMode(Relais, OUTPUT);
}



void printResult(FirebaseData &data)
{

  if (data.dataType() == "int")
    Serial.println(data.intData());
  else if (data.dataType() == "float")
    Serial.println(data.floatData(), 5);
  else if (data.dataType() == "double")
    printf("%.9lf\n", data.doubleData());
  else if (data.dataType() == "boolean")
    Serial.println(data.boolData() == 1 ? "true" : "false");
  else if (data.dataType() == "string")
    Serial.println(data.stringData());
  else if (data.dataType() == "json")
  {
    Serial.println();
    FirebaseJson &json = data.jsonObject();
    //Print all object data
    Serial.println("Pretty printed JSON data:");
    String jsonStr;
    json.toString(jsonStr, true);
    Serial.println(jsonStr);
    Serial.println();
    Serial.println("Iterate JSON data:");
    Serial.println();
    size_t len = json.iteratorBegin();
    String key, value = "";
    int type = 0;
    for (size_t i = 0; i < len; i++)
    {
      json.iteratorGet(i, type, key, value);
      Serial.print(i);
      Serial.print(", ");
      Serial.print("Type: ");
      Serial.print(type == FirebaseJson::JSON_OBJECT ? "object" : "array");
      if (type == FirebaseJson::JSON_OBJECT)
      {
        Serial.print(", Key: ");
        Serial.print(key);
      }
      Serial.print(", Value: ");
      Serial.println(value);
    }
    json.iteratorEnd();
  }
  else if (data.dataType() == "array")
  {
    Serial.println();
    //get array data from FirebaseData using FirebaseJsonArray object
    FirebaseJsonArray &arr = data.jsonArray();
    //Print all array values
    Serial.println("Pretty printed Array:");
    String arrStr;
    arr.toString(arrStr, true);
    Serial.println(arrStr);
    Serial.println();
    Serial.println("Iterate array values:");
    Serial.println();
    for (size_t i = 0; i < arr.size(); i++)
    {
      Serial.print(i);
      Serial.print(", Value: ");

      FirebaseJsonData &jsonData = data.jsonData();
      //Get the result data from FirebaseJsonArray object
      arr.get(jsonData, i);
      if (jsonData.typeNum == FirebaseJson::JSON_BOOL)
        Serial.println(jsonData.boolValue ? "true" : "false");
      else if (jsonData.typeNum == FirebaseJson::JSON_INT)
        Serial.println(jsonData.intValue);
      else if (jsonData.typeNum == FirebaseJson::JSON_DOUBLE)
        printf("%.9lf\n", jsonData.doubleValue);
      else if (jsonData.typeNum == FirebaseJson::JSON_STRING ||
               jsonData.typeNum == FirebaseJson::JSON_NULL ||
               jsonData.typeNum == FirebaseJson::JSON_OBJECT ||
               jsonData.typeNum == FirebaseJson::JSON_ARRAY)
        Serial.println(jsonData.stringValue);
    }
  }
} 

void loop()
{
 
  
 digitalWrite(pinTrig, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(pinTrig, HIGH);
delayMicroseconds(10);
digitalWrite(pinTrig, LOW);

  temps = pulseIn(pinEcho,HIGH);
  if(temps > 25000 ){
    Serial.println("Echec de la mesure");
    }
    else {
      temps = temps/2;
      hauteurVide = ( temps*343.4)/100000.0;
      Serial.print(" hauteurVide:");
      Serial.print(hauteurVide);
      Serial.println("dm");
      hautVideCor = hauteurVide-0.51;
      VolumeEau = SectionMoyen*(hauteurTotReservoir-hautVideCor);
      Serial.print(" Volume de l' eau du réservoir");
      Serial.print(VolumeEau);
      Serial.println("Litres");
     TauxRamp = (VolumeEau/CapaciteRese)*100;
     Serial.print(" Taux de remplissage du réservoir");
     Serial.print(TauxRamp);
     Serial.println("%");
    
    }
    
    //tranfert de données vers la base de données
    
delay(10); 
  json.set("/volumeDeau",  VolumeEau );
  json.set("/tauxDeRemplissage", TauxRamp );
  Firebase.updateNode(firebaseData,"/GestionEau/Test2",json);
  delay(100);
  //Commande de l' électrovanne d' alimentation du réservoir
  if(Etat == 0 && TauxRamp >= 100)
  {
    Etat =1;
    }
    if(Etat == 1 && TauxRamp <= 60)
    
  {
    Etat = 0;
    }
    if(Etat == 0)
  {
    digitalWrite(Relais, LOW);
    }
    if(Etat == 1)
  {
    digitalWrite(Relais, HIGH);
    }
  /*
  if(TauxRamp <= 100){
    digitalWrite(Relais, LOW);
     }
    else{ 
      digitalWrite(Relais, HIGH);
      }
      */
     delay(100);
    
}
