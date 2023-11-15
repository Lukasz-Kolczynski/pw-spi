;  .data 1
;x:4
;v=?
;rwynik:0
;  .code 10

;petla:
    ;CPA x   ;A=4
    ;STO v   ;v=4
 loop   ;DEC x   ;x=3
    BRZ koniec
    ;CPA v   ;A=4
    ;MUL x   ;A=4*3
    ;STO v   ;v=4*3
    BRA loop

;HLT

