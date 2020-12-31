!to "test", cbm
; vi:ft=acme
* = $0200

; byte $02 -> imprime ram
; byte $03 -> imprime stack
; byte $04 -> imprime cpu
; byte $07 -> imprime los 3

lda #$05
sta $01
lda #$00
sta $00
!byte $03
jsr subr
!byte $03
pha
!byte $03
jmp exit

; branches
loop:
    !byte $02
    pha
    !byte $03
    lda $01
    cmp $00
    inc $00
    lda $00
    bne loop
    !byte $02

subr:
    !byte $03
    rts

; jumps
exit:
