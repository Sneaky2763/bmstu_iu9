(define (my-abs x) ((if (> x 0) + -) x)) ;;возвращает модуль числа

(define (my-odd? x) (= (remainder x 2) 1) ) ;;проверяет число на нечетность

(define (power b e)
  (if (> e 0)
      (* (power b (- e 1) ) b)
      1)) ;;возводит заданное число b в указанную степень e