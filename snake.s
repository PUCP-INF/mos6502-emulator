!to "snake", cbm
* = $0600
;Para mover la serpiente mover las teclas A, W, S y D
appleL =        $00
appleH =        $01
snakeHeadL =    $10
snakeHeadH =    $11
snakeBodyStart= $12
snakeDirection= $02
snakeLength =   $03

;Direcciones
movingUp =     1
movingRight =  2
movingDown =   4
movingLeft =   8

; valores ASCII de las teclas para manejar la serpiente
ASCII_w =    $77
ASCII_a =    $61
ASCII_s =    $73
ASCII_d =    $64


sysRandom  = $fe
sysLastKey = $ff


  jsr init
  jsr loop

init:
  jsr initSnake
  jsr generateApplePosition
  rts


initSnake:
  lda #movingRight  ;posicion inicial
  sta snakeDirection

  lda #4  ;longitud de inicio(2 segmentos)
  sta snakeLength

  lda #$11
  sta snakeHeadL

  lda #$10
  sta snakeBodyStart

  lda #$0f
  sta $14 ; segmento de cuerpo 1

  lda #$04
  sta snakeHeadH
  sta $13 ; segmento de cuerpo 1
  sta $15 ; segmento de cuerpo 2
  rts


generateApplePosition:
  ;cargamos un byte random en $00
  lda sysRandom
  sta appleL

  ;cargamos un nuevo byte random de  2 a 5 en $01
  lda sysRandom
  and #$03 ;enmascaramos los 2 bytes menos significativos
  clc
  adc #2
  sta appleH
  rts


loop:
  jsr readKeys
  jsr checkCollision
  jsr updateSnake
  !byte $03     ; actualizar pantalla
  jmp loop


readKeys:
  lda sysLastKey
  cmp #ASCII_w
  beq upKey
  cmp #ASCII_d
  beq rightKey
  cmp #ASCII_s
  beq downKey
  cmp #ASCII_a
  beq leftKey
  rts
upKey:
  lda #movingDown
  bit snakeDirection
  bne illegalMove

  lda #movingUp
  sta snakeDirection
  rts
rightKey:
  lda #movingLeft
  bit snakeDirection
  bne illegalMove

  lda #movingRight
  sta snakeDirection
  rts
downKey:
  lda #movingUp
  bit snakeDirection
  bne illegalMove

  lda #movingDown
  sta snakeDirection
  rts
leftKey:
  lda #movingRight
  bit snakeDirection
  bne illegalMove

  lda #movingLeft
  sta snakeDirection
  rts
illegalMove:
  rts


checkCollision:
  jsr checkAppleCollision
  jsr checkSnakeCollision
  rts


checkAppleCollision:
  lda appleL
  cmp snakeHeadL
  bne doneCheckingAppleCollision
  lda appleH
  cmp snakeHeadH
  bne doneCheckingAppleCollision

  ;comer manzanita
  inc snakeLength
  inc snakeLength ;incrementar tamanhio de la serpiente
  !byte $04
  jsr generateApplePosition
doneCheckingAppleCollision:
  rts

checkSnakeCollision:
  ldx #2 ;
snakeCollisionLoop:
  lda snakeHeadL,x
  cmp snakeHeadL
  bne continueCollisionLoop

maybeCollided:
  lda snakeHeadH,x
  cmp snakeHeadH
  beq didCollide

continueCollisionLoop:
  inx
  inx
  cpx snakeLength
  beq didntCollide
  jmp snakeCollisionLoop

didCollide:
  jmp gameOver
didntCollide:
  rts

updateSnake:
  ldx snakeLength
  dex
  txa
  nop
  nop
updateloop:
  lda snakeHeadL,x
  sta snakeBodyStart,x
  dex
  bpl updateloop

  lda snakeDirection
  lsr
  bcs up
  lsr
  bcs right
  lsr
  bcs down
  lsr
  bcs left
up:
  lda snakeHeadL
  sec
  sbc #$20
  sta snakeHeadL
  bcc upup
  rts
upup:
  dec snakeHeadH
  lda #$1
  cmp snakeHeadH
  beq collision
  rts
right:
  inc snakeHeadL
  lda #$1f
  bit snakeHeadL
  beq collision
  rts
down:
  lda snakeHeadL
  clc
  adc #$20
  sta snakeHeadL
  bcs downdown
  rts
downdown:
  inc snakeHeadH
  lda #$6
  cmp snakeHeadH
  beq collision
  rts
left:
  dec snakeHeadL
  lda snakeHeadL
  and #$1f
  cmp #$1f
  beq collision
  rts
collision:
  jmp gameOver


drawApple:
  ldy #0
  lda sysRandom
  sta (appleL),y
  rts


drawSnake:
  ldx snakeLength
  lda #0
  sta (snakeHeadL,x) ; eliminamos el final de la cola de la serpiente

  ldx #0
  lda #1
  sta (snakeHeadL,x) ; pintamos la cabeza de la serpiente
  rts


gameOver: