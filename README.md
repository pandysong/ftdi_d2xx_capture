# What is it

This is the sample code to read UART data using any baud rate that FTDI
supports and save them to a binary file.

# How to use

```
Usage: ./largeread port baudrate save_to
```

port is an zero-based integer on multi-port device
baudrate: could be set to any supported
save_to: the file to save to

# dependencies

The code is changed from FTDI sample code largeread with minor changes, refer
to the official site for more examples.

# On Mac

Need to install D2XX driver and unload the official apple FTDI driver which has
limited baud rate support.

# How to build

```
cd Largeread
make
```

