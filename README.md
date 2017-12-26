MediaParser
===========

<pre>Source Type:<b>Open Source</b>
Charge Type:<b>free of charge</b></pre>

What is MediaParser?
----------------

An open source multimedia parser based on the Qt framework, just like mp4info tool on Windows platform.

License
----------------
MediaParser is released under the terms of the Apache-2.0 license. See [License](LICENSE) for more information.

Getting Started
----------------
#### 1. How to build
Before starting build process, QT enviroment should be installed.
```
brew install qt
```
After QT installed, make sure `which qmake` will output the right path for qmake command.

```
git clone https://github.com/ksvc/MediaParser.git
cd MediaParser
mkdir -p build
cd build
qmake ..
make -j8
```
After build process finished, there is a target app named MediaParser.app.

#### 2. Run MediaParser.app
![MediaParser.app Snapshoot](https://raw.githubusercontent.com/wiki/ksvc/MediaParser/images/snapshot.png)
The architecture about the media file will be listed in the left frame of the MediaParser.app， after pressed "open file" to specify the input file.

Feedback
----------------
Public technical discussion on github is preferred. Post your bugs or questions at [Issues](https://github.com/ksvc/MediaParser/issues).

