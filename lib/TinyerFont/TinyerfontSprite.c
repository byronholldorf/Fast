
#ifndef TINYERFONT_SPRITE_H
#define TINYERFONT_SPRITE_H

#include <avr/io.h>
#include <avr/pgmspace.h>

const unsigned char PROGMEM TINYERFONT_SPRITE[] =
{
  // #32 & #33 - Symbol ' ' (space) & Symbol '!'.
  0b10110000, // → ! ▓░▓▓   ░░░░
  0b00000000, // →   ░░░░   ░░░░   
  0b00000000, // →   ░░░░   ░░░░
  0b00000000, // →   ░░░░   ░░░░

  // #34 & #35 - Symbol '"' & Symbol '#'.
  0b10100001, // → # ▓░▓░ " ░░░▓
  0b01110000, // →   ░▓▓▓   ░░░░
  0b11100001, // →   ▓▓▓░   ░░░▓
  0b01010000, // →   ░▓░▓   ░░░░

  // #36 & #37 - Symbol '$' & Symbol '%'.
  0b10010110, // → % ▓░░▓ $ ░▓▓░
  0b01001111, // →   ░▓░░   ▓▓▓▓
  0b00100110, // →   ░░▓░   ░▓▓░
  0b10010000, // →   ▓░░▓   ░░░░

  // #38 & #39 - Symbol '&' & Symbol '''.
  0b00001111, // → ' ░░░░ & ▓▓▓▓
  0b00011101, // →   ░░░▓   ▓▓░▓
  0b00000111, // →   ░░░░   ░▓▓▓
  0b00001100, // →   ░░░░   ▓▓░░

  // #40 & #41 - Symbol '(' & Symbol ')'.
  0b00000000, // → ) ░░░░ ( ░░░░
  0b10010110, // →   ▓░░▓   ░▓▓░
  0b01101001, // →   ░▓▓░   ▓░░▓
  0b00000000, // →   ░░░░   ░░░░

  // #42 & #43 - Symbol '*' & Symbol '+'.
  0b01001010, // → + ░▓░░ * ▓░▓░
  0b11100100, // →   ▓▓▓░   ░▓░░
  0b01001010, // →   ░▓░░   ▓░▓░
  0b00000000, // →   ░░░░   ░░░░

  // #44 & #45 - Symbol ',' & Symbol '-'.
  0b01001000, // → - ░▓░░ , ▓░░░
  0b01000100, // →   ░▓░░   ░▓░░
  0b01000000, // →   ░▓░░   ░░░░
  0b00000000, // →   ░░░░   ░░░░

  // #46 & #47 - Symbol '.' & Symbol '/'.
  0b10001000, // → / ▓░░░   ▓░░░
  0b01100000, // →   ░▓▓░   ░░░░
  0b00010000, // →   ░░░▓   ░░░░
  0b00000000, // →   ░░░░   ░░░░

  // #48 & #49 - Number '0' & Number '1'.
  0b10011111, // → 1 ▓░░▓ 0 ▓▓▓▓
  0b11111001, // →   ▓▓▓▓   ▓░░▓
  0b10001111, // →   ▓░░░   ▓▓▓▓
  0b00000000, // →   ░░░░   ░░░░

  // #50 & #51 - Number '2' & Number '3'.
  0b10011101, // → 3 ▓░░▓ 2 ▓▓░▓
  0b10111011, // →   ▓░▓▓   ▓░▓▓
  0b11111010, // →   ▓▓▓▓   ▓░▓░
  0b00000000, // →   ░░░░   ░░░░

  // #52 & #53 - Number '4' & Number '5'.
  0b10110111, // → 5 ▓░▓▓ 4 ░▓▓▓
  0b10110100, // →   ▓░▓▓   ░▓░░
  0b11011111, // →   ▓▓░▓   ▓▓▓▓
  0b00000000, // →   ░░░░   ░░░░

  // #54 & #55 - Number '6' & Number '7'.
  0b00011111, // → 7 ░░░▓ 6 ▓▓▓▓
  0b00011010, // →   ░░░▓   ▓░▓░
  0b11111110, // →   ▓▓▓▓   ▓▓▓░
  0b00000000, // →   ░░░░   ░░░░

  // #56 & #57 - Number '8' & Number '9'.
  0b01111111, // → 9 ░▓▓▓ 8 ▓▓▓▓
  0b01011011, // →   ░▓░▓   ▓░▓▓
  0b11111111, // →   ▓▓▓▓   ▓▓▓▓
  0b00000000, // →   ░░░░   ░░░░

  // #58 & #59 - Symbol ':' & Symbol ';'.
  0b10001010, // → ; ▓░░░ : ▓░▓░
  0b01010000, // →   ░▓░▓   ░░░░
  0b00000000, // →   ░░░░   ░░░░
  0b00000000, // →   ░░░░   ░░░░

  // #60 & #61 - Symbol '<' & Symbol '='.
  0b10100000, // → = ▓░▓░ < ░░░░
  0b10100100, // →   ▓░▓░   ░▓░░
  0b10101010, // →   ▓░▓░   ▓░▓░
  0b00000000, // →   ░░░░   ░░░░

  // #62 & #63 - Symbol '>' & Symbol '?'.
  0b00010000, // → ? ░░░▓ > ░░░░
  0b10111010, // →   ▓░▓▓   ▓░▓░
  0b00110100, // →   ░░▓▓   ░▓░░
  0b00000000, // →   ░░░░   ░░░░

  // #64 & #65 - Symbol '@' & Letter 'A'.
  0b11111110, // → A ▓▓▓░ @ ▓▓▓▓
  0b01011001, // →   ░▓░▓   ▓░░▓
  0b01010011, // →   ░▓░▓   ░░▓▓
  0b11110010, // →   ▓▓▓░   ░░▓▓

  // #66 & #67 - Letter 'B' & Letter 'C'.
  0b11111111, // → C ▓▓▓▓ B ▓▓▓▓
  0b10011011, // →   ▓░░▓   ▓░▓▓
  0b10011011, // →   ▓░░▓   ▓░▓▓
  0b10011110, // →   ▓░░▓   ▓▓▓░

  // #68 & #69 - Letter 'D' & Letter 'E'.
  0b11111111, // → E ▓▓▓▓ D ▓▓▓▓
  0b10111001, // →   ▓░▓▓   ▓░░▓
  0b10111001, // →   ▓░▓▓   ▓░░▓
  0b10010110, // →   ▓░░▓   ░▓▓░

  // #70 & #71 - Letter 'F' & Letter 'G'.
  0b11111111, // → G ▓▓▓▓ F ▓▓▓▓
  0b10010101, // →   ▓░░▓   ░▓░▓
  0b10010101, // →   ▓░░▓   ░▓░▓
  0b11010001, // →   ▓▓░▓   ░░░▓

  // #72 & #73 - Letter 'H' & Letter 'I'.
  0b10011111, // → I ▓░░▓ H ▓▓▓▓
  0b11110100, // →   ▓▓▓▓   ░▓░░
  0b10010100, // →   ▓░░▓   ░▓░░
  0b00001111, // →   ░░░░   ▓▓▓▓

  // #74 & #75 - Letter 'J' & Letter 'K'.
  0b11111100, // → K ▓▓▓▓ J ▓▓░░
  0b00101001, // →   ░░▓░   ▓░░▓
  0b01011111, // →   ░▓░▓   ▓▓▓▓
  0b10010000, // →   ▓░░▓   ░░░░

  // #76 & #77 - Letter 'L' & Letter 'M'.
  0b11111111, // → M ▓▓▓▓ L ▓▓▓▓
  0b00011000, // →   ░░░▓   ▓░░░
  0b00111000, // →   ░░▓▓   ▓░░░
  0b11110000, // →   ▓▓▓▓   ░░░░

  // #78 & #79 - Letter 'N' & Letter 'O'.
  0b11111111, // → O ▓▓▓▓ N ▓▓▓▓
  0b10010010, // →   ▓░░▓   ░░▓░
  0b10010100, // →   ▓░░▓   ░▓░░
  0b11111111, // →   ▓▓▓▓   ▓▓▓▓

  // #80 & #81 - Letter 'P' & Letter 'Q'.
  0b11111111, // → Q ▓▓▓▓ P ▓▓▓▓
  0b10010101, // →   ▓░░▓   ░▓░▓
  0b11010101, // →   ▓▓░▓   ░▓░▓
  0b11110111, // →   ▓▓▓▓   ░▓▓▓

  // #82 & #83 - Letter 'R' & Letter 'S'.
  0b10111111, // → S ▓░▓▓ R ▓▓▓▓
  0b10110101, // →   ▓░▓▓   ░▓░▓
  0b11011101, // →   ▓▓░▓   ▓▓░▓
  0b11010111, // →   ▓▓░▓   ░▓▓▓

  // #84 & #85 - Letter 'T' & Letter 'U'.
  0b11110001, // → U ▓▓▓▓ T ░░░▓
  0b10001111, // →   ▓░░░   ▓▓▓▓
  0b10000001, // →   ▓░░░   ░░░▓
  0b11110001, // →   ▓▓▓▓   ░░░▓

  // #86 & #87 - Letter 'V' & Letter 'W'.
  0b11110111, // → W ▓▓▓▓ V ░▓▓▓
  0b10001000, // →   ▓░░░   ▓░░░
  0b11001000, // →   ▓▓░░   ▓░░░
  0b11110111, // →   ▓▓▓▓   ░▓▓▓

  // #88 & #89 - Letter 'X' & Letter 'Y'.
  0b01111001, // → Y ░▓▓▓ X ▓░░▓
  0b11000110, // →   ▓▓░░   ░▓▓░
  0b01000110, // →   ░▓░░   ░▓▓░
  0b01111001, // →   ░▓▓▓   ▓░░▓

  // #90 & #91 - Letter 'Z' & Symbol '['.
  0b00001001, // → [ ░░░░ Z ▓░░▓
  0b11111101, // →   ▓▓▓▓   ▓▓░▓
  0b10011011, // →   ▓░░▓   ▓░▓▓
  0b00001001, // →   ░░░░   ▓░░▓

  // #92 & #93 - Symbol '\' & Symbol ']'.
  0b00000001, // → ] ░░░░ \ ░░░▓
  0b10010110, // →   ▓░░▓   ░▓▓░
  0b11111000, // →   ▓▓▓▓   ▓░░░
  0b00000000, // →   ░░░░   ░░░░

  // #94 & #95 - Symbol '^' & Symbol '_'.
  0b10000010, // → _ ▓░░░ ^ ░░▓░
  0b10000001, // →   ▓░░░   ░░░▓
  0b10000010, // →   ▓░░░   ░░▓░
  0b10000000, // →   ▓░░░   ░░░░

  // #96 & #97 - Symbol '`' & Letter 'a'.
  0b00100001, // → a ░░▓░ ` ░░░▓
  0b01010010, // →   ░▓░▓   ░░▓░
  0b01110000, // →   ░▓▓▓   ░░░░
  0b00000000, // →   ░░░░   ░░░░

  // #98 & #99 - Letter 'b' & Letter 'c'.
  0b01100111, // → c ░▓▓░ b ░▓▓▓
  0b01010110, // →   ░▓░▓   ░▓▓░
  0b01010110, // →   ░▓░▓   ░▓▓░
  0b00000000, // →   ░░░░   ░░░░

  // #100 & #101 - Letter 'd' & Letter 'e'.
  0b01110110, // → e ░▓▓▓ d ░▓▓░
  0b01110110, // →   ░▓▓▓   ░▓▓░
  0b00110111, // →   ░░▓▓   ░▓▓▓
  0b00000000, // →   ░░░░   ░░░░

  // #102 & #103 - Letter 'f' & Letter 'g'.
  0b10100010, // → g ▓░▓░ f ░░▓░
  0b10110111, // →   ▓░▓▓   ░▓▓▓
  0b01110001, // →   ░▓▓▓   ░░░▓
  0b00000000, // →   ░░░░   ░░░░

  // #104 & #105 - Letter 'h' & Letter 'i'.
  0b01110111, // → i ░▓▓▓ h ░▓▓▓
  0b00000010, // →   ░░░░   ░░▓░
  0b00000110, // →   ░░░░   ░▓▓░
  0b00000000, // →   ░░░░   ░░░░

  // #106 & #107 - Letter 'j' & Letter 'k'.
  0b01111000, // → k ░▓▓▓ j ▓░░░
  0b00100111, // →   ░░▓░   ░▓▓▓
  0b01010000, // →   ░▓░▓   ░░░░
  0b00000000, // →   ░░░░   ░░░░

  // #108 & #109 - Letter 'l' & Letter 'm'.
  0b01110111, // → m ░▓▓▓ l ░▓▓▓
  0b00110100, // →   ░░▓▓   ░▓░░
  0b01110000, // →   ░▓▓▓   ░░░░
  0b00000000, // →   ░░░░   ░░░░

  // #110 & #111 - Letter 'n' & Letter 'o'.
  0b01110111, // → o ░▓▓▓ n ░▓▓▓
  0b01010001, // →   ░▓░▓   ░░░▓
  0b01110110, // →   ░▓▓▓   ░▓▓░
  0b00000000, // →   ░░░░   ░░░░

  // #112 & #113 - Letter 'p' & Letter 'q'.
  0b01111111, // → q ░▓▓▓ p ▓▓▓▓
  0b01010101, // →   ░▓░▓   ░▓░▓
  0b11110111, // →   ▓▓▓▓   ░▓▓▓
  0b00000000, // →   ░░░░   ░░░░

  // #114 & #115 - Letter 'r' & Letter 's'.
  0b01000111, // → s ░▓░░ r ░▓▓▓
  0b01110001, // →   ░▓▓▓   ░░░▓
  0b00010000, // →   ░░░▓   ░░░░
  0b00000000, // →   ░░░░   ░░░░

  // #116 & #117 - Letter 't' & Letter 'u'.
  0b00110001, // → u ░░▓▓ t ░░░▓
  0b01000111, // →   ░▓░░   ░▓▓▓
  0b01110001, // →   ░▓▓▓   ░░░▓
  0b00000000, // →   ░░░░   ░░░░

  // #118 & #119 - Letter 'v' & Letter 'w'.
  0b01110011, // → w ░▓▓▓ v ░░▓▓
  0b01100100, // →   ░▓▓░   ░▓░░
  0b01110011, // →   ░▓▓▓   ░░▓▓
  0b00000000, // →   ░░░░   ░░░░

  // #120 & #121 - Letter 'x' & Letter 'y'.
  0b00010101, // → y ░░░▓ x ░▓░▓
  0b10100010, // →   ▓░▓░   ░░▓░
  0b01110101, // →   ░▓▓▓   ░▓░▓
  0b00000000, // →   ░░░░   ░░░░

  // #122 & #123 - Letter 'z' & Symbol '{'.
  0b01100001, // → { ░▓▓░ z ░░░▓
  0b01100111, // →   ░▓▓░   ░▓▓▓
  0b10010100, // →   ▓░░▓   ░▓░░
  0b00000000, // →   ░░░░   ░░░░

  // #124 & #125 - Symbol '|' & Symbol '}'.
  0b00001111, // → } ░░░░ | ▓▓▓▓
  0b10010000, // →   ▓░░▓   ░░░░
  0b01100000, // →   ░▓▓░   ░░░░
  0b01100000, // →   ░▓▓░   ░░░░

  // #126 & #127 - Symbol '~' & Symbol '■'.
  0b11110100, // → ■ ▓▓▓▓ ~ ░▓░░
  0b11110010, // →   ▓▓▓▓   ░░▓░
  0b11110100, // →   ▓▓▓▓   ░▓░░
  0b11110010, // →   ▓▓▓▓   ░░▓░
};

#endif