package main

func merge(L, R chan int, res chan int, compare func(i, j int) int) {
	l_val, l_open := <-L
	r_val, r_open := <-R
	for l_open && r_open {
		if compare(l_val, r_val) <= 0 {
			res <- l_val
			l_val, l_open = <-L
		} else {
			res <- r_val
			r_val, r_open = <-R
		}
	}
	for l_open {
		res <- l_val
		l_val, l_open = <-L
	}
	for r_open {
		res <- r_val
		r_val, r_open = <-R
	}
	close(res)
}

func sort(L, R int, indices chan int, compare func(i, j int) int) {
	if R-L <= 1 {
		if R-L == 1 {
			indices <- L
		}
		close(indices)
		return
	}

	M := L + (R-L)/2
	L_val := make(chan int)
	R_val := make(chan int)

	go sort(L, M, L_val, compare)
	go sort(M, R, R_val, compare)
	merge(L_val, R_val, indices, compare)
}

func MergeSort(items int, compare func(i, j int) int, indices chan int) {
	sort(0, items, indices, compare)
}
