## Rekols Media Player

A simple player for you.

## system environment
- deepin desktop 
- qt5

## Build dependencies
here are two ways to build environmental dependencies：
- use apt-get
- build source code 

### way1: use apt-get 
```
$ sudo apt install qtav-dev libqtavwidgets
```

###  way2: build source code 
If you don't want to use apt-get to install the qtav library, you want to use source code.
- build [FFmpeg](http://www.ffmpeg.org/download.html)
```
$ sudo apt-get install -y yasm 
$ wget https://ffmpeg.org/releases/ffmpeg-4.1.3.tar.bz2
$ tar -jxvf ffmpeg-4.1.3.tar.bz2
$ cd ffmpeg-4.1.3/
$ sudo ./configure --enable-shared --prefix=/usr/local/ffmpeg
$ sudo make && sudo make install 

$ sudo gedit /etc/ld.so.conf
// Add in a new line: /usr/local/ffmpeg

$ sudo ldconfig
```
- build [QtAv](https://github.com/wang-bin/QtAV)
```
$ sudo apt-get install -y libopenal-dev libpulse-dev libva-dev libxv-dev libass-dev libegl1-mesa-dev \
  libavformat-dev libswscale-dev libavfilter-dev libavcodec-dev 

$ wget https://codeload.github.com/wang-bin/QtAV/zip/master
$ unzip master 
```

use `qt quick` to build it, before we need configure `Build Environment`, 
then add the following variables:
- CPATH
- LD_LIBRARY_PATH
- LIBRARY_PATH

<img src="https://raw.githubusercontent.com/JackLovel/qt-demo-projects/master/media-player/img/build_environment_variable.png" width=" 50% "/>

switch to build directory 
```
$ chmod +x sdk_install.sh && ./sdk_install.sh 
```
add `avwidgets` library to own project, open `xx.pro`: 

<img src="https://raw.githubusercontent.com/JackLovel/qt-demo-projects/master/media-player/img/add_qtav_library.png" width=" 50% "/>

## License

Rekols Player is licensed under [GPLv3](LICENSE).

