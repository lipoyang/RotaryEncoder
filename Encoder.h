#include <stdint.h>

// rotary encoder class (phase count by timer pulse unit)
class HardwareEncoder
{
private:
    const int m_id;
public:
    HardwareEncoder(int id) : m_id(id) {};
    void begin();
    void clear();
    uint16_t read();
};

// global instance
extern HardwareEncoder Encoder1; // pin  4(A) and 19(B)
extern HardwareEncoder Encoder2; // pin  2(A) and  3(B)
extern HardwareEncoder Encoder3; // pin 11(A) and 12(B)
extern HardwareEncoder Encoder4; // pin 10(A) and 13(B)
