## Rekols Media Player

A simple player for you.

### Build dependencies

`sudo apt install qt5-default qtav-dev`

### Runtime dependencies

* qt5widgets

* qt5gui

* qt5core

* [libqtavwidgets](https://github.com/wang-bin/QtAV)

`sudo apt install libqt5core5a libqt5gui5 libqt5widgets5 libqtavwidgets`

##  build source code 
if you want use source code build dependencies.
- build `FFmpeg` 
```
$ sudo apt-get install -y yasm 
$ wget https://ffmpeg.org/releases/ffmpeg-4.1.3.tar.bz2
$ tar -jxvf ffmpeg-4.1.3.tar.bz2
$ cd ffmpeg-4.1.3/
$ sudo ./configure --enable-shared --prefix=/usr/local/ffmpeg
$ sudo make && sudo make install 

$ sudo gedit /etc/ld.so.conf

// then put: /usr/local/ffmpeg
$ sudo ldconfig
```
- build [QtAv]()
```
$ sudo apt-get install libopenal-dev libpulse-dev libva-dev libxv-dev libass-dev libegl1-mesa-dev \
  libavformat-dev libswscale-dev libavfilter-dev libavcodec-dev 

$ wget https://codeload.github.com/wang-bin/QtAV/zip/master
$ unzip master && cd QtAV-master
```

## License

Rekols Player is licensed under [GPLv3](LICENSE).

