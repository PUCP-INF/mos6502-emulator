!to "snake", cbm
* = $aa00
;  ___           _        __ ___  __ ___
; / __|_ _  __ _| |_____ / /| __|/  \_  )
; \__ \ ' \/ _` | / / -_) _ \__ \ () / /
; |___/_||_\__,_|_\_\___\___/___/\__/___|

; Change direction: W A S D

appleL =        $00 ; screen location of apple, low byte
appleH =        $01 ; screen location of apple, high byte
snakeHeadL =    $10 ; screen location of snake head, low byte
snakeHeadH =    $11 ; screen location of snake head, high byte
snakeBodyStart= $12 ; start of snake body byte pairs
snakeDirection= $02 ; direction (possible values are below)
snakeLength =   $03 ; snake length, in bytes

; Directions (each using a separate bit)
movingUp =     1
movingRight =  2
movingDown =   4
movingLeft =   8

; ASCII values of keys controlling the snake
ASCII_w =    $77
ASCII_a =    $61
ASCII_s =    $73
ASCII_d =    $64

; System variables
sysRandom  = $fe
sysLastKey = $ff


  jsr init
  jsr loop

init:
  jsr initSnake ;funciona bien
  jsr generateApplePosition ;funciona bien
  rts


initSnake:
;carga en snakeDirection el valor de movingRight ( 0x0200= 2)
  lda #movingRight  ;start direction
  sta snakeDirection
;carga en snakeLength el valor de 4 ( 0x0300= 4)
  lda #4  ;start length (2 segments)
  sta snakeLength
;carga en snakeHeadL el valor de 11 ( 0x1000= 11)
  lda #$11
  sta snakeHeadL
;carga en snakeBodyStart el valor de 10 ( 0x1200= 10)
  lda #$10
  sta snakeBodyStart

  lda #$0f
  sta $14 ; body segment 1

;carga en snakeHeadH el valor de 04 ( 0x1000= 4)
  lda #$04
  sta snakeHeadH

  sta $13 ; body segment 1
  sta $15 ; body segment 2
  rts


generateApplePosition:
  ;load a new random byte into $00
  lda sysRandom
  sta appleL

  ;load a new random number from 2 to 5 into $01
  lda sysRandom
  and #$03 ;mask out lowest 2 bits
  clc
  adc #2
  sta appleH
  rts


loop:
  jsr readKeys
  ;lda snakeHeadL
  ;sbc #$01
  ;sta snakeHeadL
  ;dec snakeHeadH

  ;jsr checkCollision
  jsr updateSnake
  ;jsr drawApple
  ;jsr drawSnake
  ;jsr spinWheels
  jmp loop


readKeys:
  lda sysLastKey
  cmp #ASCII_a
  beq leftKey
  cmp #ASCII_w ;terrible error de concepto
  beq upKey ;terrible error de concepto
  cmp #ASCII_d
  beq rightKey
  cmp #ASCII_s
  beq downKey
  rts
upKey:
  ;lda #movingDown
  ;bit snakeDirection
  ;bne illegalMove

  lda #movingUp
  sta snakeDirection
  rts
rightKey:
  ;lda #movingLeft
  ;bit snakeDirection
  ;bne illegalMove

  lda #movingRight
  sta snakeDirection
  rts
downKey:
  ;lda #movingUp
  ;bit snakeDirection
  ;bne illegalMove

  lda #movingDown
  sta snakeDirection
  rts
leftKey:
  ;lda #movingRight
  ;bit snakeDirection
  ;bne illegalMove

  lda #movingLeft
  sta snakeDirection
  rts
illegalMove:
  rts


checkCollision:
  ;jsr checkAppleCollision
  ;jsr checkSnakeCollision
  rts


checkAppleCollision:
  lda appleL
  cmp snakeHeadL
  bne doneCheckingAppleCollision
  lda appleH
  cmp snakeHeadH
  bne doneCheckingAppleCollision

  ;eat apple
  inc snakeLength
  inc snakeLength ;increase length
  jsr generateApplePosition
doneCheckingAppleCollision:
  rts


checkSnakeCollision:
  ldx #2 ;start with second segment
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
  cpx snakeLength          ;got to last section with no collision
  beq didntCollide
  jmp snakeCollisionLoop

didCollide:
  jmp gameOver
didntCollide:
  rts

updateSnake:
  ;ldx snakeLength
  ;dex
  ;txa
updateloop:
  ;lda snakeHeadL,x
  ;sta snakeBodyStart,x
  ;dex
  ;bpl updateloop

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
  lda #$6
  nop
  ;cmp snakeHeadH
  ;beq collision
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
  ;jmp gameOver


drawApple:
  ldy #0
  lda sysRandom
  sta (appleL),y
  rts


drawSnake:
  ldx snakeLength
  lda #0
  sta (snakeHeadL,x) ; erase end of tail

  ldx #0
  lda #1
  sta (snakeHeadL,x) ; paint head
  rts


spinWheels:
  ldx #0
spinloop:
  nop
  nop
  dex
  bne spinloop
  rts


gameOver: