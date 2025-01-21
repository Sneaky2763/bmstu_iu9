(define (derivative expr)
  (cond ((number? expr) 0)
        
        ((equal? 'x expr) 1)

        ((equal? '(- x) expr) -1)
        
        ((equal? '+ (car expr))
         `(+ ,(derivative (cadr expr)) ,(derivative (caddr expr))))
        
        ((equal? '- (car expr))
         `(- ,(derivative (cadr expr)) ,(derivative (caddr expr))))
        
        ((and (equal? '* (car expr)) (equal? (length expr) 3))
         `(+ (* ,(derivative (cadr expr)) ,(caddr expr))
             (* ,(cadr expr) ,(derivative (caddr expr)))))

        ((and (equal? '* (car expr)) (> (length expr) 3))
         (write "hi"))
         
          

        ((equal? '/ (car expr))
         `(/ (- (* ,(derivative (cadr expr)) ,(caddr expr))
                (* ,(cadr expr) ,(derivative (caddr expr))))
             (expt ,(caddr expr) 2)))
        
        ((and (equal? 'expt (car expr)) (equal? 'x (cadr expr)))
         `(* ,(caddr expr) (expt ,(cadr expr) ,(- (caddr expr) 1))))

        ((and (equal? 'expt (car expr)) (number? (cadr expr)))
         `(* (log ,(cadr expr)) (expt ,(cadr expr) ,(caddr expr))))

        ((and (equal? 'cos (car expr)) (list? (cadr expr)))
         `(* (- (sin ,(cadr expr))) ,(derivative (cadr expr))))
        
        ((equal? 'cos (car expr))
         `(- (sin ,(cadr expr))))

        ((and (equal? 'sin (car expr)) (list? (cadr expr)))
         `(* (cos ,(cadr expr)) ,(derivative (cadr expr))))

        ((equal? 'sin (car expr))
         `(cos ,(cadr expr)))

        ((and (equal? 'exp (car expr)) (list? (cadr expr)))
         `(* ,expr ,(derivative (cadr expr))))
        
        ((equal? 'exp (car expr))
         expr)

        ((and (equal? 'log (car expr)) (equal? 'x (cadr expr)))
         `(/ 1 x))

        ((and (equal? 'log (car expr)) (equal? 'expt (caadr expr)))
         `(/ ,(car (cddadr expr)) x))
        
        (else expr))
  )



(define-syntax test
  (syntax-rules ()
    ((test exp res)
     '(exp res))))

(define (run-test test)
  (write (car test))
  (let ((res (eval (car test) (interaction-environment))))
    (if (equal? res (cadr test))
        (begin (display " ok")
               (display "\n")
               #t)
        (begin
          (display "\n   Returned: ")
          (write res)
          (display "\n")
          #f)
        )
    )
  )

(define (run-tests tests)
  (let ((res #t))
    (define (rec-tests tests res)
      (if (null? tests)
          res
          (begin
            (if (not (run-test (car tests)))
                (set! res #f))
            (rec-tests (cdr tests) res))
          )
      )
    (rec-tests tests res))
  )
  

(define the-tests
  (list (test (derivative '2) #f)
        (test (derivative  'x) #f)
        (test (derivative '(- x)) #f)
        (test (derivative '(* 1 x)) #f)
        (test (derivative '(* -1 x)) #f)
        (test (derivative '(* -4 x)) #f)
        (test (derivative '(* 10 x)) #f)
        (test (derivative '(- (* 2 x) 3)) #f)
        (test (derivative '(expt x 10)) #f)
        (test (derivative '(* 2 (expt x 5))) #f)
        (test (derivative '(expt x -2)) #f)
        (test (derivative '(expt 5 x)) #f)
        (test (derivative '(cos x)) #f)
        (test (derivative '(sin x)) #f)
        (test (derivative '(exp x)) #f)
        (test (derivative '(* 2 (exp x))) #f)
        (test (derivative '(* 2 (exp (* 2 x)))) #f)
        (test (derivative '(log x)) #f)
        (test (derivative '(* 3 (log x))) #f)
        (test (derivative '(+ (expt x 3) (expt x 2))) #f)
        (test (derivative '(/ 3 x)) #f)
        (test (derivative '(/ 3 (* 2 (expt x 2)))) #f)
        (test (derivative '(sin (* 2 x))) #f)
        (test (derivative '(cos (* 2 (expt x 2)))) #f)
        (test (derivative '(sin (log (expt x 2)))) #f)
        (test (derivative '(+ (sin (* 2 x)) (cos (* 2 (expt x 2))))) #f)
        )
  )

(run-tests the-tests)