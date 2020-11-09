# Rotary Encoder Library for GR-CITRUS

[Japanese README (和文ドキュメント)](README-ja.md)

Rotary encoder positioning library for GR-CITRUS

<br>

## Global objects

| Name |  Phase A input pin | Phase B input pin | Occupied timer resouce |
| ---- | ---- | ---- | ---- |
| Encoder1 |  4 | 19 | TPU1 |
| Encoder2 |  2 |  3 | TPU2 |
| Encoder3 | 11 | 12 | MTU1 |
| Encoder4 | 10 | 13 | MTU2 |

<br>

## Encoder *n* .begin()
Begins positioning of rotary encoder.

## Encoder *n* .clear()
Clears the position count value.

## Encoder *n* .read()
Reads the position count value. The return value is a unsigned 16-bit integer.

<br>

## Notes
This library uses MTUs (Multi function timer pulse units) and TPUs (16-bit timer pulse units). Therefore, it conflicts with PWM output (Servo library and analogWrite) of **other than** pin 1,5,7,8,11. Additionally, it also conflicts with MsTimer2 and WaveMp3p. Timer resouces used by their libraries are shown below.

- PWM output
    - 0: MTU1 (**conflicts with Encoder3**)
    - 1: TPU3
    - 5: TPU4
    - 7: TPU0
    - 8: TPU0
    - 11: MTU3
    - Others: TPU2 (**conflicts with Encoder2**)
- MsTimer2: TPU1 (**conflicts with Encoder1**)
- WaveMp3p: MTU1 (**conflicts with Encoder3**)