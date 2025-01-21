(load "unittesting.rkt")
(load "trace.scm")

;номер 1
;<sequence> ::= <whitespace> <frac> <sequence_tail>
;<sequence_tail> ::= <sequence> | <empty>
;<frac> ::= <signed_num> "/" <num>
;<signed_num> ::= <sign> <num>
;<num> ::= <digit> <num_tail>
;<num_tail> ::= <num> | <empty>
;<sign> ::= "+" | "-" | <empty>
;<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
;<whitespace> ::= " " <whitespace> | <empty>
;<empty> ::=

(define (make-stream items . eos)
  (if (null? eos)
      (make-stream items #f)
      (list items (car eos))))

(define (peek stream)
  (if (null? (car stream))
      (cadr stream)
      (caar stream)))

(define (next stream)
  (let ((n (peek stream)))
    (if (not (null? (car stream)))
        (set-car! stream (cdr (car stream))))
    n))

(define (check-valid str)
  (define stream
    (make-stream (string->list str) (integer->char 0)))
  (call-with-current-continuation
   (lambda (error)
     (and (sequence stream error)
          (equal? (peek stream) (integer->char 0)))))
  )

;valid-frac? и valid-many-fracs?

;<sequence> ::= <whitespace> <frac> <sequence_tail>
(define (sequence stream error)
  (begin (whitespace stream error)
         (frac stream error)
         (sequence_tail stream error))
  )

;<sequence_tail> ::= <sequence> | <empty>
(define (sequence_tail stream error)
  (if (not (equal? (peek stream) (integer->char 0)))
      (sequence stream error)
      #t)
  )

;<frac> ::= <signed_num> "/" <num>
(define (frac stream error)
  (and
   (signed_num stream error)
   (slash stream error)
   (num stream error))
  )

(define (slash stream error)
  (if (equal? (peek stream) #\/)
      (next stream)
      (error #f))
  )

;<signed_num> ::= <sign> <num>
(define (signed_num stream error)
  (and (sign stream error)
       (num stream error))
  )

;<sign> ::= "+" | "-" | <empty>
(define (sign stream error)
  (cond ((equal? (peek stream) #\+) (next stream))
        ((equal? (peek stream) #\-) (next stream))
        ((char-numeric? (peek stream)) (peek stream))
        (else (error #f)))
  )

;<num> ::= <digit> <num_tail>
(define (num stream error)
  (if (char-numeric? (peek stream))
      (begin (next stream)
             (num_tail stream error))
      (error #f))
  )

;<num_tail> ::= <num> | <empty>
(define (num_tail stream error)
  (if (char-numeric? (peek stream))
      (num stream error)
      #t)
  )

;<whitespace> ::= " " <whitespace> | <empty>
(define (whitespace stream error)
  (if (char-whitespace? (peek stream))
      (begin
        (next stream)
        (whitespace stream error))
      #t)
  )

;(define (valid-frac? str)
;  (check-valid str))
;
;(define (valid-many-fracs? str)
;  (check-valid str))


;scan-frac и scan-many-fracs

(define (scan str)
  (define stream
    (make-stream (string->list str) (integer->char 0)))
  (call-with-current-continuation
   (lambda (error)
     (let* ((res (sequence_scan stream error)))
       (and (equal? (peek stream) (integer->char 0))
            res))))
  )

;<sequence> ::= <whitespace> <frac> <sequence_tail>
(define (sequence_scan stream error)
  (whitespace stream error)
  (cons (frac_scan stream error) (sequence_tail_scan stream error))
  )

;<sequence_tail> ::= <sequence> | <empty>
(define (sequence_tail_scan stream error)
  (if (not (equal? (peek stream) (integer->char 0)))
      (sequence_scan stream error)
      '()
      )
  )

;<frac> ::= <signed_num> "/" <num>
(define (frac_scan stream error)
  (let*
      ((numer (signed_num_scan stream error))
       (sl (slash stream error))
       (denom (num_scan stream error 0 0)))
    (/ numer denom))
  )

;<signed_num> ::= <sign> <num>
(define (signed_num_scan stream error)
  (let* ((znak (sign_scan stream error)))
    (num_scan stream error 0 znak))
  )

;<sign> ::= "+" | "-" | <empty>
(define (sign_scan stream error)
  (cond ((equal? (peek stream) #\+) (next stream) 0)
        ((equal? (peek stream) #\-) (next stream) 1)
        ((char-numeric? (peek stream)) 0)
        (else (error #f)))
  )

;<num> ::= <digit> <num_tail>
(define (num_scan stream error res znak)
  (if (char-numeric? (peek stream))
      (let* ((digit (peek stream)))
        (next stream)
        (num_tail_scan stream error (* 10 (+ res (- (char->integer digit) 48))) znak))
      (error #f))
  )

;<num_tail> ::= <num> | <empty>
(define (num_tail_scan stream error res znak)
  (if (char-numeric? (peek stream))
      (num_scan stream error res znak)
      (if (equal? znak 1)
          (- res)
          res)
      )
  )

(define (valid-frac? str)
  (and (list? (scan str))
       (null? (cdr (scan str))))
  )

(define (valid-many-fracs? str)
  (list? (scan str))
  )

(define (scan-frac str)
  (and (list? (scan str))
       (car (scan str)))
  )

(define (scan-many-fracs str)
  (scan str)
  )

(define the-tests
  (list 
   (test (valid-frac? "110/111") #t)
   (test (valid-frac? "-4/3")  #t)
   (test (valid-frac? "+5/10") #t)
   (test (valid-frac? "5.0/10") #f)
   (test (valid-frac? "FF/10") #f)
   (test (valid-many-fracs?
          "\t1/2 1/3\n\n10/8") #t)
   (test (valid-many-fracs?
          "\t1/2 1/3\n\n2/-5") #f)
   (test (valid-many-fracs?
          "+1/2-3/4") #t)
   (test (scan-frac "110/111") 110/111)
   (test (scan-frac "-4/3") -4/3)
   (test (scan-frac "+5/10") 1/2)
   (test (scan-frac "5.0/10") #f)
   (test (scan-frac "FF/10") #f)
   (test (scan-many-fracs
          "\t1/2 1/3\n\n10/8") (1/2 1/3 5/4))
   (test (scan-many-fracs
          "\t1/2 1/3\n\n2/-5") #f)
   (test (scan-many-fracs
          "+1/2-3/4") (1/2 -3/4))))

(run-tests the-tests)


;номер 2
;<Program>  ::= <Articles> <Body> .
;<Articles> ::= <Article> <Articles> | .
;<Article>  ::= define word <Body> end .
;<Body>     ::= if <Body> endif <Body>
;             | while <Body> do <Body> wend <Body>
;             | integer <Body> | word <Body> | .

(define (parse vec)
  (let ((stream (make-stream (vector->list vec) (integer->char 0)))) 
    (call-with-current-continuation
     (lambda (error)
       (let ((result (program stream error)))
       (and (equal? (peek stream) (integer->char 0))
            result))))))

;<Program>  ::= <Articles> <Body> .
(define (program stream error)
  (list (articles stream error)
  (body stream error))
  )

;<Articles> ::= <Article> <Articles> | .
(define (articles stream error)
  (if (equal? (peek stream) 'define)
      (begin (next stream)
      (cons (article stream error) (articles stream error)))
      '())
  )

;<Article>  ::= define word <Body> end .
(define (article stream error)
  (let* ((word (peek stream)))
    (if (and (not (member word '(define end if endif while do wend)))
             (not (integer? word)))
        (begin (next stream)
               (let ((new (list word (body stream error))))
               (if (equal? (next stream) 'end)
                   new
                   (error #f))))
      (error #f)))
  )

;<Body>     ::= if <Body> endif <Body>
;             | while <Body> do <Body> wend <Body>
;             | integer <Body> | word <Body> | .
(define (body stream error)
  (cond ((equal? (peek stream) 'if)
         (next stream)
         (let* ((body1 (body stream error))
                (endif (next stream))
                (body2 (body stream error)))
         (if (equal? endif 'endif)
             (cons (list 'if body1) body2)
             (error #f)))
         )
        ((equal? (peek stream) 'while)
         (next stream)
         (let* ((body1 (body stream error))
                (do (next stream))
                (body2 (body stream error))
                (wend (next stream))
                (body3 (body stream error)))
         (if (and (equal? do 'do) (equal? wend 'wend))
             (cons (list 'while body1 body2) body3)
             (error #f))
           )
         )
        ((integer? (peek stream))
         (cons (next stream) (body stream error)))
        ((and (symbol? (peek stream)) (not (member (peek stream) '(end endif do wend))))
         (cons (next stream) (body stream error))
         )
        (else '()))
  )

(define (valid? vec)
  (list? (parse vec)))

(define the-tests2
  (list
   (test (valid? #(1 2 +)) #t)
   (test (valid? #(define 1 2 end)) #f)
   (test (valid? #(define x if end endif)) #f)
   (test (parse #(1 2 +)) (() (1 2 +)))
   (test (parse #(x dup 0 swap if drop -1 endif))
         (() (x dup 0 swap (if (drop -1)))))
   (test (parse #(define -- 1 - end
          define =0? dup 0 = end
          define =1? dup 1 = end
          define factorial
              =0? if drop 1 exit endif
              =1? if drop 1 exit endif
              1 swap
              while dup 0 > do
                  1 - swap over * swap
              wend
              drop
          end
          0 factorial
          1 factorial
          2 factorial
          3 factorial
          4 factorial ))
   (((-- (1 -))
   (=0? (dup 0 =))
   (=1? (dup 1 =))
   (factorial
    (=0? (if (drop 1 exit)) =1? (if (drop 1 exit))
    1 swap (while (dup 0 >) (1 - swap over * swap)) drop)))
  (0 factorial 1 factorial 2 factorial 3 factorial 4 factorial)))
  (test (parse #(1 2 3 4 5)) (() (1 2 3 4 5)))
  (test (parse #(define =0? dup 0 = end
                define <0? dup 0 < end
                define signum
                    =0? if exit endif
                    <0? if drop -1 exit endif
                    drop
                    1
                end
                 0 signum
                -5 signum
                10 signum))
        (((=0? (dup 0 =)) (<0? (dup 0 <))
        (signum (=0? (if (exit)) <0? (if (drop -1 exit)) drop 1)))
             (0 signum -5 signum 10 signum)))
  (test (parse #(if endif while if endif do wend if endif))
        (() ((if ()) (while ((if ())) ()) (if ())))))
  )

(run-tests the-tests2)