#include <SPI.h>
#include <SD.h>
#include <DS3231.h>
#include <Wire.h>


int SDKarte=6;                                              // Das Wort "SDKarte" steht jetzt für den Wert 6.
int LED=4;                                                  // Das Wort „LED“ steht jetzt für den Wert 4.
int Lautsprecher=5;                                         // Das Wort „Lautsprecher“ steht jetzt für den Wert 5.
int Bewegungsmelder=7;                                      // Das Wort „Bewegungsmelder“ steht jetzt für den Wert 7.
int Bewegungsstatus=0;                                      // Das Wort „Bewegungsstatus“ steht jetzt zunächst für den Wert 0. Später wird unter dieser Variable gespeichert, ob eine Bewegung erkannt wird oder nicht.
int AusKnopf=2;                                             // Das Wort „Aus-Knopf“ steht jetzt für den Wert 2.
int Knopfstatus=0;                                          // Das Wort „Knopfstatus“ steht jetzt zunächst für den Wert 0. Später wird unter dieser Variable gespeichert, ob der Aus-Knopf gedrückt ist oder nicht.


File Textdatei;                                             // An dieser Stelle wird die Variable "Textdatei" als File deklariert.

DS3231 RTC;

bool Century=false;
bool h12;
bool PM;


void setup()                                                // Start des Setups.
{
Serial.begin(9600);

pinMode(SDKarte, OUTPUT);                                   // Pin 4 (Pin "SDKarte") ist ein Ausgang.
pinMode(LED, OUTPUT);                                       // Pin 4 (Pin "LED") ist ein Ausgang.
pinMode(Lautsprecher,OUTPUT);                               // Pin 5 (Pin "Lautsprecher") ist ein Ausgang.
pinMode(Bewegungsmelder, INPUT);                            // Pin 7 (Pin "Bewegungsmelder") ist ein Eingang.
pinMode(AusKnopf, INPUT);                                   // Pin 2 (Pin "AusKnopf") ist ein Eingang.

Serial.println("Initialisiere SD-Karte");   

if (!SD.begin(SDKarte))                                     // Wenn die SD-Karte nicht gefunden werden kann, ...
{                                     
Serial.println("Initialisierung fehlgeschlagen!");          // ... soll eine Fehlermeldung ausgegeben werden. ...
return;
}

Serial.println("Initialisierung abgeschlossen");            // ... ansonsten soll die Meldung "Initialisierung abgeschlossen." ausgegeben werden.

Wire.begin();

}


void loop()                                                 // Start des Hauptprogramms.
{
Bewegungsstatus=digitalRead(Bewegungsmelder);               // Hier wird der Pin7 ausgelesen. Das Ergebnis wird unter der Variablen „Bewegungsstatus“ mit dem Wert „HIGH“ für 5Volt oder „LOW“ für 0Volt gespeichert.

if (Bewegungsstatus == HIGH)                                // Verarbeitung: Wenn eine Bewegung detektiert wird (Das Spannungssignal ist hoch)
{
digitalWrite(LED, HIGH);                                    // Schalte die LED an.
digitalWrite(Lautsprecher, HIGH);                           // Schalte den Lautsprecher an.

Serial.print(RTC.getYear(), DEC);
Serial.print('.');
Serial.print(RTC.getMonth(Century), DEC);
Serial.print('.');
Serial.print(RTC.getDate(), DEC);
Serial.print(' ');
Serial.print(RTC.getHour(h12, PM), DEC);
Serial.print(':');
Serial.print(RTC.getMinute(), DEC);
Serial.print(':');
Serial.println(RTC.getSecond(), DEC);

Textdatei = SD.open("AlarmProtokoll.txt", FILE_WRITE);        // An dieser Stelle wird die Textdatei erstellt.

if (Textdatei)                                                // Wenn die Textdatei ("AlarmProtokoll.txt") gefunden wurde....
{                                        
Textdatei.print(RTC.getYear(), DEC);
Textdatei.print('.');
Textdatei.print(RTC.getMonth(Century), DEC);
Textdatei.print('.');
Textdatei.print(RTC.getDate(), DEC);
Textdatei.print(' ');
Textdatei.print(RTC.getHour(h12, PM), DEC);
Textdatei.print(':');
Textdatei.print(RTC.getMinute(), DEC);
Textdatei.print(':');
Textdatei.println(RTC.getSecond(), DEC);          
Textdatei.close();                                            // Anschließend wird die Textdatei wieder geschlossen. 
} 

else 
{                                                             // Wenn keine Textdatei gefunden werden kann ...
Serial.println("Textdatei konnte nicht ausgelesen werden");   // ... erscheint eine Fehlermeldung im seriellen Monitor.
}

}

Knopfstatus=digitalRead(AusKnopf);                            // Hier wird der Pin2 ausgelesen. Das Ergebnis wird unter der Variable „Knopfstatus“ mit dem Wert „HIGH“ für 5Volt oder „LOW“ für 0Volt gespeichert.

if (Knopfstatus == HIGH)                                      // Verarbeitung: Wenn der Aus-Knopf gedrückt ist (Das Spannungssignal ist hoch)
{ 
digitalWrite(LED, LOW);                                       // Schalte die LED aus.
digitalWrite(Lautsprecher, LOW);                              // Schalte den Lautsprecher aus.
}

}
