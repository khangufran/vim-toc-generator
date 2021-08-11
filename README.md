# vim-toc-generator
## About
For large text files with a lot of headings, this will create a toc ( Table of Contents ) file which will allow you to jump to any particular heading in your original file.

## Installation
This is a simple program, all you have to do is clone main.cpp file then run:
```
g++ main.cpp -o gen-toc
```
For linux users, you can put gen-toc binary in /usr/local/bin  by running:
```
sudo mv gen-toc /usr/local/bin/
```
For windows and mac, put it in folder which is added in PATH variable

## Usage
```
gen-toc <filename>
```
This command will generate two files: tags and toc_filename.txt.
You can then open toc and press Ctrl+] to jump straight to corresponding heading in main file. Press Ctrl+O to jump back.

## Notes
- You can change heading identifier by changing heading_identifier global variable in main.cpp
