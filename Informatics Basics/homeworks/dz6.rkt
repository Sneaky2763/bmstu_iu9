(define (list-trim-right lst)
  (define (list-analyze res all lst)
    (if (null? lst)
        res
        (if (not (char-whitespace? (car lst)))
            (list-analyze (append all (cons (car lst) '())) (append all (cons (car lst) '())) (cdr lst))
            (list-analyze res (append all (cons (car lst) '())) (cdr lst))
            )
        )
    )
  (list-analyze '() '() lst)
  )

;номер 1
;<tokens> ::= <whitespace> <token> <tokens_tail>
;<tokens_tail> ::= <tokens> | <empty>
;<whitespace> ::= " " <whitespace> | <empty>
;<token> ::=  <bracket> | <operator> | <var> | <num>
;<bracket> ::= "(" | ")"
;<operator> "+" | "-" | "/" | "*" | "^"
;<var> ::= <letter> <var_tail>
;<var_tail> ::= <letter> <var_tail> | <empty>
;<num> ::= <digit> <num_tail>
;<num_tail> ::= <num_symbol> <num_tail> | <empty>
;<letter> ::= "a" | "b" | ... | "z"
;<num_symbol> ::= "." | "e" | "-" | <digit>
;<digit> ::= "0" | "1" | ... | "9"

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

(define (tokenize str)
  (define stream
    (make-stream (list-trim-right (string->list str)) (integer->char 0)))
  (call-with-current-continuation
   (lambda (error)
     (let* ((res (tokens stream error)))
       (and (equal? (peek stream) (integer->char 0))
            res))))
  )

;<tokens> ::= <whitespace> <token> <tokens_tail>
(define (tokens stream error)
  (whitespace stream error)
  (if (not (null? (car stream)))
      (cons (token stream error) (tokens_tail stream error))
      '()
      )
  )

;<tokens_tail> ::= <tokens> | <empty>
(define (tokens_tail stream error)
  (if (not (equal? (peek stream) (integer->char 0)))
      (tokens stream error)
      '()
      )
  )

;<whitespace> ::= " " <whitespace> | <empty>
(define (whitespace stream error)
  (if (char-whitespace? (peek stream))
      (begin
        (next stream)
        (whitespace stream error))
      #t)
  )

;<token> ::=  <bracket> | <operator> | <var> | <num>
(define (token stream error)
  (cond ((member (peek stream) '(#\( #\)))
         (string (next stream)))
        ((member (peek stream) '(#\+ #\- #\* #\/ #\^))
         (string->symbol (string (next stream))))
        ((char-alphabetic? (peek stream))
         (var stream error))
        ((char-numeric? (peek stream))
         (num stream error))
        (else (error #f)))
  )

(define (upper->lower ch)
  (if (and (char-alphabetic? ch)(char<? ch #\a))
      (integer->char (+ (char->integer ch) 32))
      ch)
  )

;<var> ::= <letter> <var-tail>
(define (var stream error)
  (if (char-alphabetic? (peek stream))
      (string->symbol
       (list->string (cons (upper->lower (next stream))
                           (var_tail stream error))))
      (error #f))
  )

;<var_tail> ::= <letter> <var_tail> | <empty>
(define (var_tail stream error)
  (if (char-alphabetic? (peek stream))
      (cons (upper->lower (next stream))
            (var_tail stream error))
      '())
  )

;<num> ::= <digit> <num-tail>
(define (num stream error)
  (if (char-numeric? (peek stream))
      (let ((res(string->number (list->string (cons (next stream)
                                                    (num_tail stream error))))))
        (if (number? res)
            res
            (error #f)))
      (error #f))
  )

;<num-tail> ::= <num_symbol> <num_tail> | <empty>
(define (num_tail stream error)
  (if (and (char-alphabetic? (peek stream)) (not (equal? (peek stream) #\e)))
      (error #f))
  (if (or (char-numeric? (peek stream)) (member (peek stream) '(#\e #\. #\-)))
      (cons (next stream)
            (num_tail stream error))
      '())
  )
