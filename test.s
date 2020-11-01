!to "test", cbm
* = $0200

lda #$05
loop
        inc $01
        cmp $01
        bne loop

inc $01
cmp $01