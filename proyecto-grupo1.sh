#Para installar el cmake, acme  y librerias
sudo apt install libgc-dev git build-essential wget
wget https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4-Linux-x86_64.tar.gz
untar xf cmake-3.18.4-Linux-x86_64.tar.gz
export PATH=$PATH:$PWD/cmake-3.18.4-Linux-x86_64/bin/
wget https://github.com/PUCP-INF/mos6502-emulator/releases/download/0.1/acme_0.96.4-5_amd64.deb
sudo dpkg -i acme_0.96.4-5_amd64.deb
#Para instalar la libreria grafica de allegro
sudo add-apt-repository ppa:allegro/5.2
sudo apt update
sudo apt install liballegro5-dev
sudo apt install liballegro-acodec5-dev liballegro-audio5-dev \
    liballegro-image5-dev liballegro-dialog5-dev liballegro-ttf5-dev \
    liballegro-physfs5-dev
#Para installar la libreria de ncurses
sudo apt-get install libncurses5-dev libncursesw5-dev

#Para compilar el emulador y generar los archivos binarios
git clone https://github.com/PUCP-INF/mos6502-emulator.git
cd mos6502-emulator
mkdir build && cd build
cmake .. && make
acme ../snake.s
acme ../pongtest.s
#Para ejecutar los juegos, en el archivo.c llamado display.c, en la linea 164 y 165 descomentar de acuerdo al juego
#que se quiera correr, aunque solo uno a la vez

#Luego, colocarce en la carpeta cmake-build-debug y abrir en el terminal y ejecutar segun el juego que se quiera
#Para el snake
#./cpu snake
#Para el pongtest
./cpu pongtest
