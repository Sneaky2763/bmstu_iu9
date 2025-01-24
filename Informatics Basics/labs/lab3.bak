(load "trace.scm") ;;номер 1
 
;;(zip '(1 2 3) '(one two three))
(define (zip . xss)
  (if (or (null? xss)
          (null? (trace (car xss))))
      '()
      (cons (map car xss)
            (apply zip (map cdr (trace xss))))))
;;номер 2
(define (signum x)
  (cond
    ((< x 0) -1)
    ((= x 0)  1) ; Ошибка здесь!
    (else     1)))

(define-syntax test
  (syntax-rules ()
    ((test exp res)
     '(exp res))))

(define-syntax run-test
  (syntax-rules ()
    ((run-test test)
     ())))

;;(define-syntax run-tests
;;  (syntax-rules ()
;;    ((run-tests test)
;;     )))

;;(define the-tests
;;  (list (test (signum -2) -1)
;;        (test (signum  0)  0)
;;        (test (signum  2)  1)))

(define the-tests
  (list (test (signum -2) -1)))
(run-tests the-tests)