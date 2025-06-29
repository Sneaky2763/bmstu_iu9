package main

import "fmt"

func min(a int, b int) int {
	if a < b {
		return a
	}
	return b
}

func max(a int, b int) int {
	if a > b {
		return a
	}
	return b
}

//а вот в go 1.21 и выше min и max встроены :)

func add(a, b []int32, p int) []int32 {
	var (
		ans      []int32
		leftover = int32(0)
		digit    int32
	)

	for i := 0; i < min(len(a), len(b)); i++ {
		val := a[i] + b[i] + leftover
		if val >= int32(p) {
			digit = (a[i] + b[i] + leftover) % int32(p)
			leftover = 1
		} else {
			digit = a[i] + b[i] + leftover
			leftover = 0
		}
		ans = append(ans, digit)
	}

	for i := min(len(a), len(b)); i < max(len(a), len(b)); i++ {
		if len(a) > len(b) {
			ans = append(ans, (a[i]+leftover)%int32(p))
			if a[i]+leftover >= int32(p) {
				leftover = 1
			} else {
				leftover = 0
			}
		} else {
			ans = append(ans, (b[i]+leftover)%int32(p))
			if b[i]+leftover >= int32(p) {
				leftover = 1
			} else {
				leftover = 0
			}
		}
	}

	if leftover == 1 {
		ans = append(ans, 1)
	}

	return ans
}

func main() {
	x := []int32{1, 1, 2, 0, 2, 2}
	y := []int32{1, 2, 1, 2}
	fmt.Println(add(x, y, 3))
}
