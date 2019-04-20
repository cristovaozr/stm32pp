# ST CubeMX LL Library C++ wrapper

This project is named **stm32pp** because it's a C++ implementation of a STM32 library.

This project serve a few personal goals:
* Improve my C/C++ skills;
* Learn how to integrate better C and C++ in a project;
* Obtain a better insight on how to use C++ on microcontrollers;
* Provide an open-source library written in C++ that is straightforward and useful;
* Mess a little with baremetal development;
* ...

## Tools used in the development

To develop this project I'm using the following tools:
* Archlinux;
* VSCodium. Check it out [here](https://github.com/VSCodium/vscodium)
* GCC/G++ ARM toolchain for Linux;
* GNU make
* newlib;
*  [texane's stlink utilities](https://github.com/texane/stlink);
* WaveShare Open407Z-C Package B development board. Check it out [here](https://www.waveshare.com/product/mcu-tools/stm32/open/open407z-c-package-b.htm|);
* ST CubeMX LL library (files are contained in the source-code *as is*)

## What the project contains

* ST CubeMX LL Library in the `clib` folder;
* C++ library source-code in the `cpp` folder;
* A sample project that is used to test the peripheral development in the `main` folder;
* other stuff

## Building the project

To build the project just type
> `make`

This will output a static linkable library (.a) named `stm32pp.a`. Use this library to link to your own projects!

To build the sample project just type
> `make binary`

and two files should pop-up:
* `main.elf` which is the compiled file with debugging symbols (the symbols were intended for the GNU gdb compiler);
* `main.bin` which is the binary version of the compiled program.

Note that **no library** file is generated this way! Also the library **does not contain** necessary files to create a fully functional firmware! You could use the sample application to do so!

To flash the contents of the file to the microcontroler just type (assuming that you have a st-link hardware)

> `st-flash write main.bin 0x08000000`

## Target architecture

This library and binary files target STM32F407ZE series of microcontrollers. Specifically it targets the before mentioned WaveShare development board.

And before you ask: no, I'll not port these files to other microcontrollers. Please! Feel free to do so!

## Why C++? Why don't you use C as everyone else?

But I **do** use C as everyone else! This is my first project using C++ as default programming language for microcontrollers. As I mentioned I want to get a grasp of how challenging and how amazing coding in C++ for microcontrollers can be.

## Contacting me

I am a brazillian computer engineer and I've specialized in embedded systems development. I've written a few firmwares and high level software. My [LinkedIn profile](https://linkedin.com/in/cristovaozr) contains a few of the projects I've done in the past years. Feel free to visit me there!

You can visit my personal blog. It's been a while that I don't write anything there - life's been busy the last couple of years but this is comming to an end! The address to the blog can be found [here](https://cristovaorufino.wordpress.com/). Content written in english and in portuguese also!