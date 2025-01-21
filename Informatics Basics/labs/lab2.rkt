(define (uniq xs) ;;номер 1
  (if (< (length xs) 2)
      xs
      (if (equal? (car xs) (cadr xs))
          (uniq (cdr xs))
          (cons (car xs) (uniq (cdr xs)))
          )
      )
  )

(define (delete pred? xs) ;;номер 2
  (if (null? xs)
      '()
      (if (pred? (car xs))
          (delete pred? (cdr xs))
          (cons (car xs) (delete pred? (cdr xs)))
          )
      )
  )

(define (polynom xs x) ;;номер 3
  (if (null? xs)
      0
      (+ (polynom (cdr xs) x) (* (expt x (length(cdr xs))) (car xs))))
  )

(define (intersperse e xs) ;;номер 4
  (if (< (length xs) 2)
      xs
      (cons (car xs) (cons e (intersperse e (cdr xs)))))
  )

(define (all? pred? xs) ;;номер 5
  (or (null? xs)
      (and (pred? (car xs))
           (all? pred? (cdr xs)))
      )
  )

(define (o . xs) ;;номер 6
  (if (null? xs)
      (lambda (x) x)
      (lambda (x) ((car xs) ((apply o (cdr xs)) x)))
      )
  )

(define (f x) (+ x 2))
(define (g x) (* x 3))
(define (h x) (- x))