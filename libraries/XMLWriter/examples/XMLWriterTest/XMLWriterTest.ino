//
//    FILE: XMLWriterTest.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
// PURPOSE: make a simple XML generating lib
//    DATE: 2013-11-06
//     URL:
//
// Released to the public domain
//

#include <XMLWriter.h>

XMLWriter XML(&Serial);

char buffer[24];

void setup()
{
  Serial.begin(115200);

  XML.header();
  XML.comment("XMLWriterTest.ino\nThis is a demo of a simple XML lib for Arduino", true);

  XML.tagOpen("Arduino", "42");

  XML.tagOpen("Ports");
  AnalogPorts("before");
  DigitalPorts();
  AnalogPorts("after");
  XML.tagClose();

  Weather();
  Weather2();
  DataTypes();

  XML.tagClose();
}

void Weather2()
{
  XML.comment("The weather in South Africa");
  for (int i=0; i<10; i++)
  {
    XML.tagStart("Weather");
    XML.tagField("Date", "20131106");
    XML.tagField("Time", "1:42");
    XML.tagField("Temp", "23.4");
    XML.tagField("Humi", "50%");
    XML.tagField("Rain", "10mm");
    XML.tagField("Sun", "40");
    XML.tagEnd();
  }
}

void Weather()
{
  XML.comment("The weather in Nebraska");
  XML.tagOpen("Weather");
  XML.writeNode("Date", "20131106");
  XML.writeNode("Time", "11:42");
  XML.writeNode("Temp", "23.4");
  XML.writeNode("Humi", "50%");
  XML.writeNode("Rain", "10mm");
  XML.writeNode("Sun", "40");
  XML.tagClose();
}

void AnalogPorts(const char* name)
{
  XML.comment("The analog ports are multiplexed");
  XML.tagOpen("Analog", name);
  XML.writeNode("Analog0", itoa(analogRead(A0), buffer, 10));
  XML.writeNode("Analog1", analogRead(A1));
  XML.writeNode("Analog2", (5.0*analogRead(A2))/1023);  // default nr decimals = 2
  XML.writeNode("Analog3", (5.0*analogRead(A2))/1023, 3);
  XML.tagClose();
}

void DigitalPorts()
{
  XML.comment("The digital ports are not multiplexed");
  XML.tagOpen("Digital");
  XML.writeNode("D1", itoa(digitalRead(1), buffer, 10));
  XML.writeNode("D13", digitalRead(13));
  XML.tagClose();
}

void DataTypes()
{
  XML.comment("Testing dataTypes I");
  XML.tagOpen("Datatypes");
  XML.writeNode("Bool", 1 == 1);
  XML.writeNode("Bool", 1 == 0);
  XML.writeNode("BIN", 42, BIN);
  XML.writeNode("DEC", 42, DEC);
  XML.writeNode("HEX", 42, HEX);
  XML.writeNode("OCT", 42, OCT);
  XML.tagClose();
  
  XML.comment("Testing dataTypes II");
  for (int i=0; i<3; i++)
  {
    XML.tagStart("dataTypes");
    XML.tagField("Bool", 1 == 1);
    XML.tagField("Bool", 1 == 0);
    int x = analogRead(A0);
    XML.tagField("BIN", x, BIN);
    XML.tagField("DEC", x, DEC);
    XML.tagField("HEX", x, HEX);
    XML.tagField("OCT", x, OCT);
    XML.tagEnd();
  }
}

void loop()
{
}