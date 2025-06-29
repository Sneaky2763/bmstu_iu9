package main

import "fmt"

func main() {
	var input string
	fmt.Scan(&input)
	table := map[string]int{}
	for i := 0; i < len(input); i++ {
		if input[i] == '(' {
			bracket := 1
			pos := i + 1
			for ; bracket > 0; pos++ {
				if input[pos] == '(' {
					bracket++
				}
				if input[pos] == ')' {
					bracket--
				}
			}
			table[input[i:pos]] = pos
		}
	}
	fmt.Println(len(table))
}
