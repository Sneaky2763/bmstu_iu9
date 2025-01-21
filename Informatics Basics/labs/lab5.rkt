(define (interpret code stack)
  (define (iter code stack words)
    (begin (write code) (write stack) (newline))
    (if(not(null? code))
       (if(number? (car code))
          (iter (cdr code) (cons (car code) stack) words)
          (cond
            ((and (equal? (car code) 'neg))
             (iter (cdr code) (cons (- (car stack)) (cdr stack)) words))
            ((equal? (car code) '-)
             (iter (cdr code) (cons (- (cadr stack) (car stack)) (cddr stack)) words))
            ((equal? (car code) '+)
             (iter (cdr code) (cons (+ (cadr stack) (car stack)) (cddr stack)) words))
            ((equal? (car code) '*)
             (iter (cdr code) (cons (* (cadr stack) (car stack)) (cddr stack)) words))
            ((equal? (car code) '/)
             (iter (cdr code) (cons (/ (cadr stack) (car stack)) (cddr stack)) words))
            ((equal? (car code) 'mod)
             (iter (cdr code) (cons (remainder (cadr stack) (car stack)) (cddr stack)) words))
            ((equal? (car code) '=)
             (cond
               ((equal? (car stack) (cadr stack)) (iter (cdr code) (append '(-1) (cddr stack)) words))
               (else (iter (cdr code) (append '(0) (cddr stack)) words))
               )
             )
            ((equal? (car code) '>)
             (cond
               ((> (cadr stack) (car stack)) (iter (cdr code) (append '(-1) (cddr stack)) words))
               (else (iter (cdr code) (append '(0) (cddr stack)) words))
               ))
            ((equal? (car code) '<)
             (cond
               ((< (cadr stack) (car stack)) (iter (cdr code) (append '(-1) (cddr stack)) words))
               (else (iter (cdr code) (append '(0) (cddr stack)) words))
               )
             )
            ((equal? (car code) 'not)
             (cond
               ((equal? (car stack) '0)
                (iter (cdr code) (append '(-1) (cdr stack)) words))
               (else (iter (cdr code) (append '(0) (cdr stack)) words))
               )
             )
            ((equal? (car code) 'and)
             (cond
               ((or (equal? (car stack) '0) (equal? (cadr stack) '0))
                (iter (cdr code) (append '(0) (cddr stack)) words))
               (else (iter (cdr code) (append '(-1) (cddr stack)) words))
               )
             )
            ((equal? (car code) 'or)
             (cond
               ((and (equal? (car stack) '0) (equal? (cadr stack) '0))
                (iter (cdr code) (append '(0) (cddr stack)) words))
               (else (iter (cdr code) (append '(-1) (cddr stack)) words))
               )
             )
            ((equal? (car code) 'drop)
             (iter (cdr code) (cdr stack) words)
             )
            ((equal? (car code) 'swap)
             (iter (cdr code) (append (list (cadr stack)) (list (car stack)) (cddr stack)) words)
             )
            ((equal? (car code) 'dup)
             (iter (cdr code) (cons (car stack) stack) words)
             )
            ((equal? (car code) 'over)
             (iter (cdr code) (cons (cadr stack) stack) words)
             )
            ((equal? (car code) 'rot)
             (iter (cdr code) (append (list (caddr stack)) (list (cadr stack))
                                      (list (car stack)) (cdddr stack)) words)
             )
            ((equal? (car code) 'depth)
             (iter (cdr code) (cons (length stack) stack) words)
             )
            ((equal? (car code) 'define)
             (let((name-state (cadr code)))
               (define (read-code code code-state)
                 (if(equal? (car code) 'end)
                    (iter (cdr code) stack (append words (list (list name-state code-state))))
                    (read-code (cdr code) (append code-state (list (car code))))
                    ))
               (read-code (cddr code) '())
               )
             )
            ((equal? (car code) 'exit)
             (let ()
               (define (skip code)
                 (if (equal? (car code) 'end)
                     (iter (cdr code) stack words)
                     (skip (cdr code))
                     )
                 )
               (skip code)
               ))
            ((equal? (car code) 'if)
             (if(equal? (car stack) 0)
                (let()
                  (define (skip code)
                    (if(equal? (car code) 'endif)
                       (iter (cdr code) (cdr stack) words)
                       (skip (cdr code))
                       )
                    )
                  (skip code)
                  )
                (let()
                  (define (use-code code use)
                    (if(equal? (car code) 'endif)
                       (iter (append use (cdr code)) (cdr stack) words)
                       (use-code (cdr code) (append use (list (car code))))
                       )
                    )
                  (use-code (cdr code) '())
                  )
                )
             )
            ((equal? (car code) 'while)
             (if (equal? (car code) 0)
                 (let()
                   (define (skip code)
                     (if(equal? (car code) 'wend)
                        (iter (cdr code) (cdr stack) words)
                        (skip (cdr code))
                        )
                     )
                   (skip code)
                   )
                 (let()
                  (define (use-code code use)
                    (if (equal? (car code) 'wend)
                       (iter (append (append use '(wend)) (cdr code)) (cdr stack) words)
                       (use-code (cdr code) (append use (list (car code))))
                       )
                    )
                  (use-code (cdr code) '())
                  )
                 )
             )
             
            ((assoc (car code) words)
             (iter (append (append (cadr (assoc (car code) words)) '(end)) (cdr code)) stack words) 
             )
            ((equal? (car code) 'end)
             (iter (cdr code) stack words))
            )
          )
       stack
       )
    )
  (iter (vector->list code) stack '())
  )

;тестирование
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
        (begin (display " FAIL\n")
               (display "   Expected: ")
               (write (cadr test))
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
  (list (test (interpret #(   define abs
                               dup 0 <
                               if neg endif
                               end
                               9 abs
                               -9 abs      ) (quote ())) (9 9))
        (test (interpret #(   define =0? dup 0 = end
                               define <0? dup 0 < end
                               define signum
                               =0? if exit endif
                               <0? if drop -1 exit endif
                               drop
                               1
                               end
                               0 signum
                               -5 signum
                               10 signum       ) (quote ())) (1 -1 0))
        (test (interpret #(   define -- 1 - end
                               define =0? dup 0 = end
                               define =1? dup 1 = end
                               define factorial
                               =0? if drop 1 exit endif
                               =1? if drop 1 exit endif
                               dup --
                               factorial
                               *
                               end
                               0 factorial
                               1 factorial
                               2 factorial
                               3 factorial
                               4 factorial     ) (quote ())) (24 6 2 1 1))
        (test (interpret #(   define =0? dup 0 = end
                               define =1? dup 1 = end
                               define -- 1 - end
                               define fib
                               =0? if drop 0 exit endif
                               =1? if drop 1 exit endif
                               -- dup
                               -- fib
                               swap fib
                               +
                               end
                               define make-fib
                               dup 0 < if drop exit endif
                               dup fib
                               swap --
                               make-fib
                               end
                               10 make-fib     ) (quote ())) (0 1 1 2 3 5 8 13 21 34 55))
        (test (interpret #(   define =0? dup 0 = end
                               define gcd
                               =0? if drop exit endif
                               swap over mod
                               gcd
                               end
                               90 99 gcd
                               234 8100 gcd    ) '()) (18 9))
        )
  )

;(run-tests the-tests)