!to "mult", cbm
* = $0200

; byte $02 -> imprime ram
; byte $03 -> imprime stack
; byte $04 -> imprime cpu
; byte $07 -> imprime los 3

factor1: !by 4 ;declaramos el operando 1, con el valor 4
factor2: !by 3 ;declaramos el operando 2, con el valor 3
;los numeros se guardan en hexadecimal en la memoria
jsr multiplicar ;subrutina de multiplicacion
                ;el resultado estara la direccion $00
jmp exit

multiplicar:
    ;el contador estará en la pila
    lda #$00
sumar:
    cmp factor2
    beq exit
    adc #$01
    pha ; pusheo el contador
    lda $00 ;en $00 se guarda la suma
    adc factor1
    sta $00
    pla ; pop del contador
    jmp sumar
rts

exit:
    lda $00
    !byte $04 ;imprimimos en pantalla los registro del CPU
    !byte $02 ;imprimimos la memoria RAM
    ;fin programa
