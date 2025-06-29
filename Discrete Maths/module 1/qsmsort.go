package main

import "fmt"

type Task struct {
	low, high int
}

func partition(low, high int,
	less func(i, j int) bool,
	swap func(i, j int)) int {
	i := low - 1
	for j := low; j < high; j++ {
		if less(j, high) {
			i++
			swap(i, j)
		}
	}
	swap(i+1, high)
	return i + 1
}

func qssort(n int,
	less func(i, j int) bool,
	swap func(i, j int)) {

	s := []Task{Task{0, n - 1}}

	for len(s) > 0 {
		low, high := s[len(s)-1].low, s[len(s)-1].high
		s = s[:len(s)-1]

		if low < high {
			q := partition(low, high, less, swap)
			if q-1 > low {
				s = append(s, Task{low, q - 1})
			}
			if q+1 < high {
				s = append(s, Task{q + 1, high})
			}
		}
	}
}

func main() {
	data := []int{413, 443, 475, 450, 407, 315, 324, 386, 317, 397,
		419, 302, 374, 365, 307, 423, 394, 386, 419, 321,
		339, 357, 468, 448, 294, 466, 333, 321, 381, 440,
		432, 349, 455, 370, 454, 457, 430}

	fmt.Println("Массив до сортировки:", data)

	less := func(i, j int) bool {
		return data[i] < data[j]
	}

	swap := func(i, j int) {
		data[i], data[j] = data[j], data[i]
	}

	qssort(len(data), less, swap)

	fmt.Println("Массив после сортировки:", data)
}
