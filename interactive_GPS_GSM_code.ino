//Insert your sim number in the bottom portion.
#include <SoftwareSerial.h>

SoftwareSerial mySerial(7,8); // RX, TX
char strn[100],strn1[100],strn2[100],coord[50],lati_arr_1[25],lati_arr_2[25],long_arr_1[25],long_arr_2[25];
int j=0,c=0,i=0,l=0,k=0,p=0;
double Db_lati_1,Db_lati_2,Db_long_1,Db_long_2,Db_lati,Db_long;
String str_lati,str_long,coord_string,map_link;
  
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
   while(!Serial){
    
  }
  
  pinMode(13,OUTPUT); // output to trigger digital pin13
  pinMode(11,OUTPUT);//output to trigger digital pin11
 // int CO = analogRead(A1);    // reading the data on analog pin A1 via a sensor.
  int temp = analogRead(A2);  // reading the sensor data on analog pin A2.

while(temp<140)
  {
    //CO = analogRead(A1);    // reading the sensor data on analog pin A1.
    temp = analogRead(A2);  // reading the sensor data on analog pin A2.
    Serial.println(temp);
  }
      digitalWrite(11, 1);  // digital pin 11 will be triggered.
      digitalWrite(13, 1);  // digital pin 13 will be triggered.
      digitalWrite(4,1);    // digital pin 4 will be triggered.
      
      strn[9]='\0';
      delay(10);
  mySerial.println("AT");    // To check the correct interfacing with sim808(gsm module)
  delay(200);
  for(i=0;i<99;i++)strn[i]=0; // initialising the array to avoid any garbage values
   c=0;
  while(!mySerial.available());  // if nothing is available to read on the serial pins then this empty loop will be continuosly executed.
  while(mySerial.available()) {strn[c]=(mySerial.read());if(c<9)c++;}  
  for (i=0;i<20;i++)Serial.print(strn[i]); // strn will be printed on serial monitor.
  Serial.println("");
//The above method to print and store the response of an AT command is helpful in case of any timing 
// problems occuring even after using delay function. 
  
  mySerial.println("AT+CMEE=1"); // This command that will make sure that if an error occurs in the program then a corresponding error No./code
  //should appear,cause of the errror can be find out from AT command manual or just by google search using this error code. 
  delay(200);
  delay(200);
  for(i=0;i<99;i++)strn[i]=0;
    c=0;
  while(!mySerial.available());
  while(mySerial.available()) {strn[c]=(mySerial.read());c++;}
  for (i=0;i<c;i++)Serial.print(strn[i]);

  // Sending the first text message containing only text alert only i.e., without any location.
  mySerial.println("AT+CSCS=\"GSM\"");  // setting for english only message
   delay(200);
  delay(200);
  for(i=0;i<99;i++)strn[i]=0;
    c=0;
  while(!mySerial.available());
  while(mySerial.available()) {strn[c]=(mySerial.read());c++;}
  for (i=0;i<c;i++)Serial.print(strn[i]);
 
  mySerial.println("AT+CMGF=1");     // set the module in text message mode
    delay(200);
  delay(200);
  for(i=0;i<99;i++)strn[i]=0;
    c=0;
  while(!mySerial.available());
  while(mySerial.available()) {strn[c]=(mySerial.read());c++;}
  for (i=0;i<c;i++)Serial.print(strn[i]);
  
  mySerial.println("AT+CMGS=\"8780923758\"");  // to send message at a particular number
    delay(200);
  delay(200);
  for(i=0;i<99;i++)strn[i]=0;
    c=0;
  while(!mySerial.available());
  while(mySerial.available()) {strn[c]=(mySerial.read());c++;}
  for (i=0;i<c;i++)Serial.print(strn[i]);
  
  mySerial.println("ALERT" );  // appending the text message with location
    delay(200);
  delay(200);
  for(i=0;i<99;i++)strn[i]=0;
    c=0;
  while(!mySerial.available());
  while(mySerial.available()) {strn[c]=(mySerial.read());c++;}
  for (i=0;i<c;i++)Serial.print(strn[i]);
  
  mySerial.write(0x1A);     // Final gsm Command which is required for sending the message and  0x1A is the hex code for Ctrl+Z 
    delay(20000);
    digitalWrite(13, 0);
    delay(15000); 
}

void loop() {
  if (mySerial.available()) { //if there is some data available on pin 7 or 8 then it'll show on serial monitor.
    Serial.write(mySerial.read());
  }
    if (Serial.available()) { // allows to write AT commands during execution of programme or in case of any error.
    mySerial.write(Serial.read());
  }
//Serial.print(temp);
//Serial.print('\t');
//Serial.println(CO);

  for(i=0;i<26;i++){lati_arr_1[i]=0;}
  for(i=0;i<26;i++){lati_arr_2[i]=0;}
  for(i=0;i<26;i++){long_arr_1[i]=0;}
  for(i=0;i<26;i++){long_arr_2[i]=0;}

while(l<1)
{ l++;
   c=0;
  delay(2000);
  mySerial.println("AT+CGPSPWR=1");  // AT command for powering on gps
  delay(200);
  for(i=0;i<99;i++)strn[i]=0;
    c=0;
  while(!mySerial.available());
  while(mySerial.available()) {strn[c]=(mySerial.read());c++;}
  for (i=0;i<c;i++)Serial.print(strn[i]);

  
  mySerial.println("AT+CGPSRST=1"); // AT command for resetting GPS 
  delay(200);
  delay(200);
  for(i=0;i<99;i++)strn[i]=0;
    c=0;
  while(!mySerial.available());
  while(mySerial.available()) {strn[c]=(mySerial.read());c++;}
  for (i=0;i<c;i++)Serial.print(strn[i]);
}
while(j<1)
{ j++;
while(strn2[39]!= '3')
   {mySerial.println("AT+CGPSSTATUS?"); // AT command for checking status of gps
  delay(500);
  delay(200);
  for(i=0;i<99;i++)strn2[i]=0;
    c=0;
  while(!mySerial.available());
  while(mySerial.available()) {strn2[c]=(mySerial.read());c++;}
 // for (i=0;i<c;i++)Serial.print(strn2[i]);
  Serial.println(strn2[39]); 
  }
  Serial.println(strn2);

}
 

   while(k<1)
    {
      k++;
       mySerial.println("AT+CGPSINF=0"); // AT command for getting the current location
  delay(200);
  for(i=0;i<99;i++)strn[i]=0;
    c=0;
  while(!mySerial.available());
  while(mySerial.available()) {strn[c]=(mySerial.read());Serial.print(strn[c]);c++;}
  Serial.print("\n ");
  for (i=27;i<50;i++)
  {Serial.print(strn[i]);
   coord[i-27]=strn[i] ; // Here a character array named coord containing the coordinates (latitude,longitude) in degree and minutes format is formed.
   }
    Serial.print("\n ");

     for(i=0;i<23;i++)
  { if(i<2) { lati_arr_1[i]=coord[i];}
    else if (i>=2 && i<=10) {lati_arr_2[i-2]=coord[i];}
    else if (i>=12 && i<=13) {long_arr_1[i-12]=coord[i];}
    else if (i>=14 && i<=22) {long_arr_2[i-14]=coord[i];}
  }

  // In the above for loop we separated out degree and minute part of latitude and longitude from the 
  //coordinates character array 'coord' in 4 different character arrays respectively.

    delay(1000);

  String lati_1(lati_arr_1);
  String lati_2(lati_arr_2);
  String long_1(long_arr_1);
  String long_2(long_arr_2); // Here we have converted above 4 character arrays into 4 strings , So that we can directly use
  // function to convert these strings into Doubles.
  //********* String to Double conversion is required,So that we can perform mathematical operation to convert the format of coordinates
  //from degrees and minutes to decimal format which is the required to format in google map location accessing.


  Db_lati_1=lati_1.toDouble();  // here we converted the string lati_1 to double
  Db_lati_2=((lati_2.toDouble())/60);
  Db_lati=Db_lati_1 + Db_lati_2;   // here we have obtained the latitude in the decimal format with double as it's data type.
  
  
str_lati=String(Db_lati,6); // Here we have converted the decimal latitude in string('str_lati') , So that we can include it in our 'text' message.

  Db_long_1=long_1.toDouble();
  Db_long_2=((long_2.toDouble())/60);
  Db_long=Db_long_1 + Db_long_2; // here we have obtained the longitude in the decimal format with double as it's data type.


 str_long=String(Db_long,6);  // converted it in a string named 'str_long'.

String coord_string = str_lati + ',' + str_long ;     // making a string named as 'coord_string' by concatenating latitude and longitide strings in decimal format with
// a comma in between
String d = "https://www.google.com/maps/place/";
String map_link = d + coord_string ;   // Here we have made a link to access the location on google map.
Serial.println(map_link);
delay(200);

// Sending the Second message including text alert , coordinates and google maps link.
    while(p<1)
    { p++;
  mySerial.println("AT+CSCS=\"GSM\"");  // setting for english only message
   delay(200);
  delay(200);
  for(i=0;i<99;i++)strn[i]=0;
    c=0;
  while(!mySerial.available());
  while(mySerial.available()) {strn[c]=(mySerial.read());c++;}
  for (i=0;i<c;i++)Serial.print(strn[i]);
  mySerial.println("AT+CMGF=1");     // set the module in text message mode
   delay(200);
  delay(200);
  for(i=0;i<99;i++)strn[i]=0;
    c=0;
  while(!mySerial.available());
  while(mySerial.available()) {strn[c]=(mySerial.read());c++;}
  for (i=0;i<c;i++)Serial.print(strn[i]);
  mySerial.println("AT+CMGS=\"Type the sim number\"");  // to send message at a particular number
  delay(200);
  delay(200);
  for(i=0;i<99;i++)strn[i]=0;
    c=0;
  while(!mySerial.available());
  while(mySerial.available()) {strn[c]=(mySerial.read());c++;}
  for (i=0;i<c;i++)Serial.print(strn[i]);
  mySerial.println("LOCATION IS " + coord_string+ "\n" + map_link);  // appending the text message with location
   delay(200);
  delay(200);
  for(i=0;i<99;i++)strn[i]=0;
    c=0;
  while(!mySerial.available());
  while(mySerial.available()) {strn[c]=(mySerial.read());c++;}
  for (i=0;i<c;i++)Serial.print(strn[i]);
  mySerial.write(0x1A);
    }
    

}

}
  
  

