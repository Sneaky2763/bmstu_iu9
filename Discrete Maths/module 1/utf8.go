package main

import (
	"fmt"
)

func encode(utf32 []rune) []byte {
	var res []byte
	for i := 0; i < len(utf32); i++ {
		switch {
		case utf32[i] < 1<<7:
			res = append(res, byte(utf32[i]))
		case utf32[i] < 1<<12:
			res = append(res,
				(byte(utf32[i]>>6) + 3<<6),
				(byte(utf32[i]) | 3<<6 - 1<<6),
			)
		case utf32[i] < 1<<16:
			res = append(res,
				(byte(utf32[i]>>12) + 14<<4),
				(byte(utf32[i]>>6) | 3<<6 - 1<<6),
				(byte(utf32[i]) | 3<<6 - 1<<6),
			)
		case utf32[i] < 1<<22:
			res = append(res,
				(byte(utf32[i]>>18) + 15<<4),
				(byte(utf32[i]>>12) | 3<<6 - 1<<6),
				(byte(utf32[i]>>6) | 3<<6 - 1<<6),
				(byte(utf32[i]) | 3<<6 - 1<<6),
			)
		}
	}
	return res
}

func decode(utf8 []byte) []rune {
	var res []rune
	for i := 0; i < len(utf8); i++ {
		switch {
		case utf8[i]>>7 == 0:
			res = append(res, rune(utf8[i]))
		case utf8[i]>>5 == 6:
			res = append(res, ((rune(utf8[i])-3<<6)<<6)+
				(rune(utf8[i+1])-1<<7))
			i++
		case utf8[i]>>4 == 14:
			res = append(res, ((rune(utf8[i])-14<<4)<<12)+
				((rune(utf8[i+1])-1<<7)<<6)+
				(rune(utf8[i+2])-1<<7))
			i += 2
		case utf8[i]>>4 == 15:
			res = append(res, ((rune(utf8[i])-15<<4)<<18)+
				((rune(utf8[i+1])-1<<7)<<12)+
				((rune(utf8[i+2])-1<<7)<<6)+
				(rune(utf8[i+3])-1<<7))
			i += 3
		}
	}
	return res
}

func main() {
	input := ([]rune)("😁")
	expected := ([]byte)("😁")
	actual := encode(input)
	fmt.Println(expected, actual)
}*/
