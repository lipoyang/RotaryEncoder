#include "Encoder.h"
#include "rx63n/iodefine.h"

// cf. RX63N Group, RX631 Group User’s Manual: Hardware
//     MTU2a / Phase Counting Mode
//     TPUa  / Phase Counting Mode

#define ID_Encoder1  1 // TPU1 : pin 4(PC2/TCLKA) and 19(P15/TCLKB)
#define ID_Encoder2  2 // TPU2 : pin 2(PC0/TCLKC) and  3(PC1/TCLKD)
#define ID_Encoder3  3 // MTU1 : pin 11(PC6/MTCLKA) and 12(PC7/MTCLKB)
#define ID_Encoder4  4 // MTU2 : pin 10(PC4/MTCLKC) and 13(PC5/MTCLKD)

// initialize phase counting
void HardwareEncoder::begin()
{
    switch(m_id){
    // TPU1 : pin 4(PC2/TCLKA) and 19(P15/TCLKB)
    case ID_Encoder1:
        // (!!!) disable TPU1 interrupt! (TPU1 is also used for MsTimer2)
        IEN(TPU1,TGI1A) = 0x0;
        IR (TPU1,TGI1A) = 0x0;
        // set pin function of PC2
        MPC.PC2PFS.BIT.PSEL = 0x03; // pin function (TCLKA)
        PORTC.PDR.BIT.B2 = 0;       // port direction (input)
        PORTC.PMR.BIT.B2 = 1;       // port mode (peripheral)
        // set pin function of P15
        MPC.P15PFS.BIT.PSEL = 0x04; // pin function (TCLKB)
        PORT1.PDR.BIT.B5 = 0;       // port direction (input)
        PORT1.PMR.BIT.B5 = 1;       // port mode (peripheral)
        // set TPU1
        MSTP(TPU1) = 0;             // awake TPU from module stop
        TPUA.TSTR.BIT.CST1 = 0;     // stop TPU1 count
        TPU1.TMDR.BIT.MD = 4;       // phase counting mode 1
        TPU1.TCNT = 0;              // clear count
        TPUA.TSTR.BIT.CST1 = 1;     // start TPU1 count
        break;
        
    // TPU2 : pin 2(PC0/TCLKC) and  3(PC1/TCLKD)
    case ID_Encoder2:
        // (!!!) disable TPU2 interrupt! (TPU2 is also used for software PWM)
        IEN(TPU2, TGI2A) = 0x0;
        IR (TPU2, TGI2A) = 0x0;
        // set pin function of PC0
        MPC.PC0PFS.BIT.PSEL = 0x03; // pin function (TCLKC)
        PORTC.PDR.BIT.B0 = 0;       // port direction (input)
        PORTC.PMR.BIT.B0 = 1;       // port mode (peripheral)
        // set pin function of PC1
        MPC.PC1PFS.BIT.PSEL = 0x03; // pin function (TCLKD)
        PORTC.PDR.BIT.B1 = 0;       // port direction (input)
        PORTC.PMR.BIT.B1 = 1;       // port mode (peripheral)
        // set TPU2
        MSTP(TPU2) = 0;             // awake TPU from module stop
        TPUA.TSTR.BIT.CST2 = 0;     // stop TPU2 count
        TPU2.TCR.BYTE = 0x0;        // (!!!) TCNT clearing disabled (TPU2 is also used for software PWM)
        TPU2.TMDR.BIT.MD = 4;       // phase counting mode 1
        TPU2.TCNT = 0;              // clear count
        TPUA.TSTR.BIT.CST2 = 1;     // start TPU2 count
        break;
    
    // MTU1 : pin 11(PC6/MTCLKA) and 12(PC7/MTCLKB)
    case ID_Encoder3:
        // (!!!) disable MTU1 interrupt! (MTU1 is also used for WavMp3p)
        IEN(MTU1, TGIA1) = 0x0;
        IR (MTU1, TGIA1) = 0x0;
        // set pin function of PC6
        MPC.PC6PFS.BIT.PSEL = 0x02; // pin function (MTCLKA)
        PORTC.PDR.BIT.B6 = 0;       // port direction (input)
        PORTC.PMR.BIT.B6 = 1;       // port mode (peripheral)
        // set pin function of PC7
        MPC.PC7PFS.BIT.PSEL = 0x02; // pin function (MTCLKB)
        PORTC.PDR.BIT.B7 = 0;       // port direction (input)
        PORTC.PMR.BIT.B7 = 1;       // port mode (peripheral)
        // set MTU1
        MSTP(MTU1) = 0;             // awake MTU from module stop
        MTU.TSTR.BIT.CST1 = 0;      // stop MTU1 count
        MTU1.TMDR.BIT.MD = 4;       // phase counting mode 1
        MTU1.TCNT = 0;              // clear count
        MTU.TSTR.BIT.CST1 = 1;      // start MTU1 count
        break;
        
    // MTU2 : pin 10(PC4/MTCLKC) and 13(PC5/MTCLKD)
    case ID_Encoder4:
        // set pin function of PC4
        MPC.PC4PFS.BIT.PSEL = 0x02; // pin function (MTCLKC)
        PORTC.PDR.BIT.B4 = 0;       // port direction (input)
        PORTC.PMR.BIT.B4 = 1;       // port mode (peripheral)
        // set pin function of PC5
        MPC.PC5PFS.BIT.PSEL = 0x02; // pin function (MTCLKD)
        PORTC.PDR.BIT.B5 = 0;       // port direction (input)
        PORTC.PMR.BIT.B5 = 1;       // port mode (peripheral)
        // set MTU2
        MSTP(MTU2) = 0;             // awake MTU from module stop
        MTU.TSTR.BIT.CST2 = 0;      // stop MTU2 count
        MTU2.TMDR.BIT.MD = 4;       // phase counting mode 1
        MTU2.TCNT = 0;              // clear count
        MTU.TSTR.BIT.CST2 = 1;      // start MTU2 count
        break;
    }
}

// clear count value
void HardwareEncoder::clear()
{
    switch(m_id){
    case ID_Encoder1:
        TPU1.TCNT = 0;
        break;
    case ID_Encoder2:
        TPU2.TCNT = 0;
        break;
    case ID_Encoder3:
        MTU1.TCNT = 0;
        break;
    case ID_Encoder4:
        MTU2.TCNT = 0;
        break;
    }
}

// get count value
uint16_t  HardwareEncoder::read()
{
    uint16_t count = 0;
    
    switch(m_id){
    case ID_Encoder1:
        count = TPU1.TCNT;
        break;
    case ID_Encoder2:
        count = TPU2.TCNT;
        break;
    case ID_Encoder3:
        count = MTU1.TCNT;
        break;
    case ID_Encoder4:
        count = MTU2.TCNT;
        break;
    }
    
    return count;
}

// global instance
HardwareEncoder Encoder1 (ID_Encoder1); // pin  4(A) and 19(B)
HardwareEncoder Encoder2 (ID_Encoder2); // pin  2(A) and  3(B)
HardwareEncoder Encoder3 (ID_Encoder3); // pin 11(A) and 12(B)
HardwareEncoder Encoder4 (ID_Encoder4); // pin 10(A) and 13(B)

