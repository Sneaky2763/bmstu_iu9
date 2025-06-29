package main

import (
	"bufio"
	"fmt"
	"os"
)

func oper(a int64) bool {
	if a > 1000000000000000010 {
		return true
	}
	return false
}
func number(a int64) bool {
	if a > -1000000000000000000 && a < 1000000000000000000 {
		return true
	}
	return false
}
func eval(arifm, a, b int64) int64 {
	if arifm == 1000000000000000043 {
		return a + b
	}
	if arifm == 1000000000000000042 {
		return a * b
	}
	return a - b
}

func main() {

	in := bufio.NewReader(os.Stdin)

	line, _ := in.ReadString('\n')
	var stack []int64
	for i := 0; i < len(line); i++ {
		if line[i] != '(' && line[i] != ')' && line[i] != ' ' {
			if int64(line[i])-48 < 0 {
				stack = append(stack, int64(line[i])+1000000000000000000)
			} else {
				stack = append(stack, int64(line[i])-48)
			}
		}
	}

	for i := len(stack) - 1; i >= 2; i-- {
		if oper(stack[i-2]) {
			var found bool = false
			for cnt1 := i; cnt1 < len(stack) && !found; cnt1++ {
				for cnt2 := i - 1; cnt2 < cnt1 && !found; cnt2++ {
					if number(stack[cnt1]) && number(stack[cnt2]) {
						stack[i-2] = eval(stack[i-2], stack[cnt2], stack[cnt1])
						stack[cnt2] = -1000000000000000000
						stack[cnt1] = -1000000000000000000
						found = true
					}
				}
			}
		}
	}
	for i := 0; i < len(stack); i++ {
		if number(stack[i]) {
			fmt.Println(stack[i])
			break
		}
	}
}
