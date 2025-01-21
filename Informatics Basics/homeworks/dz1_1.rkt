(define (day-of-week day month year)
  (let* ((y (if (< month 3)
                (- year 1)
                year))
         (m (if (< month 3)
                (+ month 12)
                month))
         (den (remainder
               (+ day
                  (quotient (* 13 (+ m 1)) 5)
                  y
                  (quotient y 4)
                  (- (quotient y 100))
                  (quotient y 400)
                  ) 7)))
    (remainder (+ den 6) 7))
  )