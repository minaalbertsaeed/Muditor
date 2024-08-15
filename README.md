<h1 align="center">Muditor (Music Editor)</h1>

> [!CAUTION]
 NOTE: Muditor still under development

## Build from Source
I use the great [GNU make](https://www.gnu.org/software/make/) build system to handle the dependencies and compiling stuff

> [!IMPORTANT]  
> As i use the shared object **build/libmuditor.so** to hot reload the main logic for seamless development without closing the main running program, you need to add the "./build/" directory to the LD_LIBRARY_PATH env variable by 
```bash
#PLEASE read the Makefile
# from the project directory
export LD_LIBRARY_PATH="./build/:$LD_LIBRARY_PATH" 

# then run the program
make run
```

> [!NOTE]
Only Unix-like systems will be supported in the near and far future; Windows will not.


## TODO
- [x] Implementing FFT
- [ ] Apply [X-Macros](https://en.wikipedia.org/wiki/X_macro) in libmuditor 
- [ ] Applying [Hann Function](https://en.wikipedia.org/wiki/Window_function#Hann_and_Hamming_windows) to audio samples 
- [ ] Apply Drag and Drop instead of command line arguments
- [ ] Use Shaders and Textures stuff (I know nothing about yet)
