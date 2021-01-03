!to "pongtest", cbm


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

score = $06

canmove = $30
distance = $03

border = $fd

init:
lda #$02
sta canmove
lda #$02 ; ypos
sta ballposY ; ball
lda #$01 ; ypos
sta player1posY ; plr1
lda #$1e ; ypos
sta IAposY ; plr2
lda #$04
sta IAposX ; plr2
sta ballposX ; ball
sta player1posX ; plr1
lsr
lda #$01
sta vectordirX ; xdir (ball)
lda #$01
sta vectordirY ; ydir (ball)
lda #$1b
sta distance
lda #$00
sta score


mainloop:
!byte $03
jsr checkcollisions
jsr readkeys
jsr getmovesball
jsr playerseeker
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
jsr checkplayercollision
jsr checkcomputercollision
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

checkplayercollision:
lda ballposX
cmp IAposX
beq maycolliteIa  ;IA somos los jugadores crack
rts
maycolliteIa:
lda ballposY
clc
adc #$01
cmp IAposY
beq didcolliteIA
rts
didcolliteIA:
lda #$02
sta vectordirY
lda #$01
sta canmove

rts

checkcomputercollision:
lda ballposX
cmp player1posX
beq maycolliteplayer  ;player es la compu crack
rts
maycolliteplayer:
lda ballposY
sec
sbc #$01
cmp player1posY
beq didcolliteplayer
rts
didcolliteplayer:
lda #$01
sta vectordirY
rts

playerseeker:
lda distance
cmp #$01
beq dontmove
lda canmove
cmp #$01
beq domove
rts
domove:
sec
lda distance
sbc #$01
sta distance
lda ballposX
sta player1posX
lda ballposY
sbc distance
sta player1posY
rts
dontmove:
lda #$1b
sta distance
lda #$02
sta canmove
rts
gameOver:
