package main

import "fmt"

type Frac struct {
	numer, denom int
}

func gcd(a, b int) int {
	if b == 0 {
		return a
	}
	return gcd(b, a%b)
}

func simplify(a Frac) Frac {
	divisor := gcd(a.numer, a.denom)
	a.numer /= divisor
	a.denom /= divisor
	if a.numer > 0 && a.denom < 0 {
		a.numer = -a.numer
		a.denom = -a.denom
	}
	return a
}

func frac_subtr(a Frac, b Frac) Frac {
	targetdenom := gcd(a.denom, b.denom)
	prevdenom := a.denom
	a.numer *= b.denom / targetdenom
	a.denom *= b.denom / targetdenom
	b.numer *= prevdenom / targetdenom

	a.numer -= b.numer
	a = simplify(a)
	return a
}

func gauss(matrix [][]Frac, n int) {
	for i := 0; i < n; i++ {
		if matrix[i][i].numer == 0 {
			for cnt := 1; cnt < n-i; cnt++ {
				if matrix[i+cnt][i].numer != 0 {
					matrix[i], matrix[i+cnt] = matrix[i+cnt], matrix[i]
				}
			}
		}
		if matrix[i][i].numer == 0 {
			fmt.Println("No solution")
			return
		}

		for j := i + 1; j < n; j++ {
			ratio := Frac{matrix[j][i].numer * matrix[i][i].denom,
				matrix[j][i].denom * matrix[i][i].numer}
			for k := 0; k < n+1; k++ {
				subtr := Frac{ratio.numer * matrix[i][k].numer,
					ratio.denom * matrix[i][k].denom}
				matrix[j][k] = frac_subtr(matrix[j][k], subtr)
			}
		}
	}

	var ans [5]Frac
	ans[n-1] = simplify(Frac{matrix[n-1][n].numer * matrix[n-1][n-1].denom,
		matrix[n-1][n].denom * matrix[n-1][n-1].numer})
	for i := n - 2; i >= 0; i-- {
		ans[i] = matrix[i][n]
		for j := i + 1; j < n; j++ {
			subtr := Frac{matrix[i][j].numer * ans[j].numer, matrix[i][j].denom * ans[j].denom}
			ans[i] = frac_subtr(ans[i], subtr)
		}
		ans[i].numer = ans[i].numer * matrix[i][i].denom
		ans[i].denom = ans[i].denom * matrix[i][i].numer
		ans[i] = simplify(ans[i])
	}

	for i := 0; i < n; i++ {
		fmt.Printf("%d/%d\n", ans[i].numer, ans[i].denom)
	}
}

func main() {
	var n int
	fmt.Scan(&n)
	matrix := make([][]Frac, n)
	for i := 0; i < n; i++ {
		matrix[i] = make([]Frac, n+1)
	}
	for i := 0; i < n; i++ {
		for j := 0; j < n+1; j++ {
			fmt.Scan(&matrix[i][j].numer)
			matrix[i][j].denom = 1
		}
	}
	gauss(matrix, n)
}
