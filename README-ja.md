# Rotary Encoder Library for GR-CITRUS

[English README (英文ドキュメント)](README.md)

GR-CITRUS用のロータリーエンコーダ測位ライブラリです。

<br>

## グローバルオブジェクト

| 名前 |  A相入力ピン | B相入力ピン | 占有するタイマリソース |
| ---- | ---- | ---- | ---- |
| Encoder1 |  4 | 19 | TPU1 |
| Encoder2 |  2 |  3 | TPU2 |
| Encoder3 | 11 | 12 | MTU1 |
| Encoder4 | 10 | 13 | MTU2 |

<br>

## Encoder *n* .begin()
ロータリーエンコーダ測位を開始します。

## Encoder *n* .clear()
測位カウント値をクリアします。

## Encoder *n* .read()
測位カウント値を取得します。
値は符号なし16ビット整数値です。

<br>

## 注意点
このクラスはMTU(マルチファンクションタイマパルスユニット)およびTPU(16ビットタイマパルスユニット)を使用しています。そのため、ピン1,5,7,8,11**以外**のPWM出力 (ServoライブラリおよびanalogWrite)と競合します。 また、MsTimer2, WaveMp3pとも競合します。これらのライブラリが使用するタイマリソースは下記の通りです。

- PWM出力
    - 0: MTU1 (**Encoder3と競合**)
    - 1: TPU3
    - 5: TPU4
    - 7: TPU0
    - 8: TPU0
    - 11: MTU3
    - それ以外: TPU2 (**Encoder2と競合**)
- MsTimer2: TPU1 (**Encoder1と競合**)
- WaveMp3p: MTU1 (**Encoder3と競合**)