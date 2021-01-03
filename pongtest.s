* = $0600

vectordirX = $20
vectordirY = $21

ballposX = $8
ballposY = $18

player1posX = $9
player1posY = $19

IAposX = $0a
IAposY = $1a

ASCII_w =    $77
ASCII_s =    $73

crashUpborder = $01
crashDownborder = $02
crashRightborder = $04
crashLeftborder = $08

border = $fd

init:
lda #$02 ; ypos
sta ballposY ; ball
lda #$01 ; ypos
sta player1posY ; plr1
lda #$1e ; ypos
sta IAposY ; plr2
;lda #$1f ; xpos
;sta IAposX ; plr2
lda #$04
sta IAposX ; plr2
sta ballposX ; ball
sta player1posX ; plr1
lsr
lda #$01
sta vectordirX ; xdir (ball)
lda #$01
sta vectordirY ; ydir (ball)

mainloop:
!byte $03
jsr checkcollisions
jsr readkeys
jsr getmovesball



jmp mainloop

getmovesball:
jsr getmoveX
jsr getmoveY
rts

getmoveX:
lda vectordirX
cmp #$01
beq movup
cmp #$02
beq movdown
rts
getmoveY:
lda vectordirY
cmp #$01
beq movright
cmp #$02
beq movleft
rts
movup:
  lda ballposY
  sec
  sbc #$20
  sta ballposY
  bcc upup
  rts
upup:
  dec ballposX
  rts
movright:
  inc  ballposY
  rts
movdown:
  lda ballposY
  clc
  adc #$20
  sta ballposY
  bcs downdown
  rts
downdown:
  inc ballposX
  rts
movleft:
  dec ballposY
  rts

readkeys:
lda $ff
cmp #ASCII_w
beq movPlayerup
cmp #ASCII_s
beq movPlayerdown
rts

movPlayerup:
  lda IAposY
  sec
  sbc #$20
  sta IAposY
  bcc playerupup
  lda #$00
  sta $ff
  rts
playerupup:
  dec IAposX
  lda #$00
  sta $ff
  rts

movPlayerdown:
  lda IAposY
  clc
  adc #$20
  sta IAposY
  bcs playerdowndown
  lda #$00
  sta $ff
  rts
playerdowndown:
  inc IAposX
  lda #$00
  sta $ff
  rts

checkcollisions:
jsr checkbordercollitions
;jsr checkplayercollision
;jsr checkcomputercollision
rts
checkbordercollitions:
lda border
cmp #crashUpborder
beq UpborderTouch
cmp #crashDownborder
beq DownborderTouch
cmp #crashRightborder
beq gameOver
cmp #crashLeftborder
beq gameOver
rts

UpborderTouch:
lda #$02
sta vectordirX
rts
DownborderTouch:
lda #$01
sta vectordirX
rts

gameOver:
