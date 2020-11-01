!to "test.o", cbm
* = $0200

lda #$05
cmp $01
bne xd

inc $01
inc $01
inc $01

xd

;loop
;        inc $01
;        cmp $01
;        bne loop