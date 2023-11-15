;  .data 10
;x:5
;y:-7
;r:?
;  .code 20
;CPA x
;MUL y
;STO r

;vsc=1.0
;Adres    Wartość
0010      00005
0011      10007
;0012
0020      10010
0021      50011
0022      20012
0023      00000



#wyniki:   //trzeba wrzucic do python online przekopiowac Assemblera i kod ktory chcemy obliczyc, uruchomic program i wpisac po kolei komendy:


-load mnozenie.mc

Loading program from: mnozenie.mc
> 


-show -memory 10

M[0010] = 00005
> 


-show -memory 10-23

M[0010] = 00005
M[0011] = 10007
M[0012] = 79831
M[0013] = 22785
M[0014] = 92569
M[0015] = 29446
M[0016] = 91368
M[0017] = 93665
M[0018] = 98466
M[0019] = 24388
M[0020] = 10010
M[0021] = 50011
M[0022] = 20012
M[0023] = 00000
> 



Session Killed due to Timeout.


Press Enter to exit terminal