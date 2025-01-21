;;задача 1
(define call-cc call-with-current-continuation)

(define state 0)
(define (use-assertions)
  (call-cc (lambda (cc) (set! state cc))))

(define-syntax assert
  (syntax-rules ()
    ((assert check)
     (if (not check)
         ((begin (display "FAILED: ")
                 (write 'check)
                 (newline))
          (state))
         )
     )
    )
  )

(use-assertions) ; Инициализация вашего каркаса перед использованием

; Определение процедуры, требующей верификации переданного ей значения:

(define (1/x x)
  (assert (not (zero? x))) ; Утверждение: x ДОЛЖЕН БЫТЬ ≠ 0
  (/ 1 x))

; Применение процедуры с утверждением:

(map 1/x '(1 2 3 4 5)) ; ВЕРНЕТ список значений в программу

(map 1/x '(-2 -1 0 1 2)) ; ВЫВЕДЕТ в консоль сообщение и завершит работу программы

;;задача 2
;первое
(define (analyze-loop input-port output-port) 
  (let ((expr (read input-port)))
    (if (not (eof-object? expr))
        (begin
          (if (and (list? expr)
                   (equal? (car expr) 'define)
                   (list? (cadr expr)))
              (let ((name (caadr expr))
                    (func (append (list 'lambda (cdadr expr)) (cddr expr))))
                (begin (write `(define ,name ,func) output-port)
                       (newline output-port)))
              (begin (write expr output-port)
                     (newline output-port)))
          (analyze-loop input-port output-port))
        )
    )
  )

(define (proc-desugar input-file output-file)
  (with-input-from-file input-file
    (lambda ()
      (with-output-to-file output-file
        (lambda ()
          (analyze-loop (current-input-port) (current-output-port)))))))

;(proc-desugar "test.rkt" "res.rkt")
;второе
(define (analyze-lines input-port)
  (let ((counter 0))
    (define (line-count input-port counter)
      (let ((curr-symb (read-char input-port))
            (next-symb (peek-char input-port)))
        (if (not (eof-object? next-symb))
            (if (and (not (equal? curr-symb #\newline))
                     (equal? next-symb #\newline))
                (line-count input-port (+ 1 counter))
                (line-count input-port counter)
                )
            (if (equal? curr-symb #\newline)
                (write counter)
                (write (+ 1 counter))
                )
            )))
    (line-count input-port counter)
    )
  )

(define (line-counter input-file)
  (with-input-from-file input-file
    (lambda ()
      (analyze-lines (current-input-port)))))

;(line-counter "test.rkt")

;;задача 3
(define trib-memo
  (let ((known-results '((0 0) (1 0) (2 1))))
    (lambda (n)
      (let* ((args n)
             (res (assoc args known-results)))
        (if res
            (cadr res)
            (let ((res (+ (trib-memo (- n 1))
                          (trib-memo (- n 2))
                          (trib-memo (- n 3)))))
              (set! known-results
                    (cons (list args res) known-results))
              res))))))

;;задача 4
(define-syntax lazy-cons
  (syntax-rules ()
    ((lazy-cons a b)
     (cons a (delay b)))))

(define (lazy-car lazy-list)
  (car lazy-list))
(define (lazy-cdr lazy-list)
  (force (cdr lazy-list)))

(define (lazy-head xs k)
  (if (equal? k 0)
      '()
      (cons (car xs) (lazy-head (lazy-cdr xs) (- k 1)))
      )
  )

(define (lazy-ref xs k)
  (if (equal? k 0)
      (if (pair? xs)
          (lazy-car xs)
          xs
          )
      (lazy-ref (lazy-cdr xs) (- k 1)))
  )

(define (lazy-map proc xs)
  (if (null? xs)
      '() 
      (lazy-cons (proc (lazy-car xs)) (lazy-map proc (lazy-cdr xs)))
      )
  )

(define (lazy-zip xs ys)
  (if (or (null? xs) (null? ys))
      '()
      (lazy-cons (list (lazy-car xs) (lazy-car ys)) 
                 (lazy-zip (lazy-cdr xs) (lazy-cdr ys)))))

(define fibonacci 
  (lazy-cons 1 (lazy-cons 1
               (lazy-map (lambda xs (+ (caar xs) (cadar xs)))
               (lazy-zip fibonacci (lazy-cdr fibonacci))))))


;;задание 5
(define-syntax when
  (syntax-rules ()
    ((when cond? . expr)
     (if cond?
         (begin . expr)
         ))))

(define-syntax for
  (syntax-rules (in as)
    ((for x in xs . expr)
     (for-each (lambda (x) (begin . expr)) xs))
    ((for xs as x . expr)
     (for-each (lambda (x) (begin . expr)) xs))))

(define-syntax repeat
  (syntax-rules ()
    ((repeat (expr . exprs) until cond?)
     (letrec ((use (lambda ()
                      (begin
                        (begin expr . exprs)
                        (if (not cond?)
                            (use))))))
       (use)))))