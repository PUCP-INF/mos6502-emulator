!to "test", cbm
* = $0200

start:
    lda #$10
    beq loop
    sta $10
    inc $10
    inc $10
    inc $10
    inc $10
    inc $10

loop:
    inc $10




