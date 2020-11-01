!to "test", cbm
* = $0200

start:
    lda #$10
loop:
    stx $00,y
    cmp $00,x
    inx
    iny
    bne loop
    dec $00