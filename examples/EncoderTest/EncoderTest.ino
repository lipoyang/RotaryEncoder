#include "Encoder.h"

void setup()
{
    Serial.begin(115200);
    
    Encoder1.begin();
    Encoder2.begin();
    Encoder3.begin();
    Encoder4.begin();
}

void loop()
{
    uint16_t enc1 = Encoder1.read();
    uint16_t enc2 = Encoder2.read();
    uint16_t enc3 = Encoder3.read();
    uint16_t enc4 = Encoder4.read();
    
    Serial.print(enc1);  Serial.print(",  ");
    Serial.print(enc2);  Serial.print(",  ");
    Serial.print(enc3);  Serial.print(",  ");
    Serial.print(enc4);  Serial.print("\n");
    
    delay(500);
}
