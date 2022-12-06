#include <Arduino.h>
// シフトレジスタへの電源供給は3.3Vで行う

void setup() {
    // put your setup code here, to run once:
    pinMode(21, OUTPUT);  // RCK
    pinMode(22, OUTPUT);  // SCK
    pinMode(23, OUTPUT);  // SER
    pinMode(19, OUTPUT);  // RCK_2
    pinMode(18, OUTPUT);  // SCK_2
    pinMode(17, OUTPUT);  // SER_2
}
const int char_cnt = 9;
uint16_t pattern[char_cnt][16] = {
    {
        0,
    },
    {
        0,
    },
    {
        0,
    },
    {0b0000000000000000,
     0b0100011111111000,
     0b0010000100010000,
     0b0010000010100000,
     0b0000001111111100,
     0b0000001001000100,
     0b0000001001000100,
     0b1111001111111100,
     0b0001001001000100,
     0b0001001001000100,
     0b0001001111111100,
     0b0001001001000100,
     0b0001101001000100,
     0b0010101001001100,
     0b0100011000000000,
     0b1000000111111110},
    {0b0010001000010000,
     0b0001000100010000,
     0b0001000100010000,
     0b1111111111111100,
     0b1000000000000100,
     0b1000000000000100,
     0b0011111111100000,
     0b0000000001000000,
     0b0000000110000000,
     0b0000001000000000,
     0b1111111111111100,
     0b0000001000000000,
     0b0000001000000000,
     0b0000001000000000,
     0b0000001000000000,
     0b0000011000000000},
    {0b0001000001000000,
     0b0001000001000000,
     0b0001000001000000,
     0b0001001111111000,
     0b0101100001001000,
     0b0101010001001000,
     0b0101010001001000,
     0b0101000001001000,
     0b1001011111111110,
     0b0001000001000000,
     0b0001000010100000,
     0b0001000010100000,
     0b0001000100010000,
     0b0001000100010000,
     0b0001001000001000,
     0b0001010000000100},
    {0b0000000001000000,
     0b0100000001000000,
     0b0010111111111110,
     0b0010000001000000,
     0b0000000001000000,
     0b0000011111111100,
     0b0000010001000100,
     0b1111010001000100,
     0b0001011111111100,
     0b0001000011100000,
     0b0001000101010000,
     0b0001001001001000,
     0b0001110001000110,
     0b0010100001000000,
     0b0100011000000000,
     0b1000000111111110},
    {
        0,
    },
    {
        0,
    }};
uint16_t display_pat[3][16] = {{
                                   0,
                               },
                               {
                                   0,
                               },
                               {
                                   0,
                               }};
void loop() {
    // put your main code here, to run repeatedly:
    for (int col = 0; col < 16 * (char_cnt - 2); col++) {
        for (int ch = 0; ch < 3; ch++) {
            for (int row = 0; row < 16; row++) {
                display_pat[ch][row] = (pattern[ch + col / 16][row] << (col % 16)) + (pattern[ch + 1 + col / 16][row] >> (16 - (col % 16)));
            }
        }

        for (int cnt = 0; cnt < 12; cnt++) {
            for (int anode = 0; anode < 16; anode++) {
                delayMicroseconds(300);

                digitalWrite(23, LOW);
                for (int i = 0; i < 6; i++) shiftOut(21, 22, LSBFIRST, 0);  // 一度全部0を突っ込むと残像が出ない
                digitalWrite(23, HIGH);

                digitalWrite(19, LOW);
                uint16_t itr = 0b1000000000000000 >> anode;
                shiftOut(17, 18, LSBFIRST, ~itr);
                shiftOut(17, 18, LSBFIRST, (~itr >> 8));
                digitalWrite(19, HIGH);

                digitalWrite(23, LOW);
                for (int i = 0; i < 3; i++) {
                    shiftOut(21, 22, LSBFIRST, display_pat[i][anode] >> 8);
                    shiftOut(21, 22, LSBFIRST, display_pat[i][anode]);
                }
                digitalWrite(23, HIGH);

                // delayMicroseconds(100);
            }
        }
    }
    // digitalWrite(23,LOW); 全点灯
    // shiftOut(21,22,MSBFIRST,0b11111111);
    // shiftOut(21,22,MSBFIRST,0b11111111);
    // digitalWrite(23,HIGH);
}