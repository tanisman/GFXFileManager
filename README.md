# GFXFileManager

An example replacement for the Joymax File Manager used in Silkroad Online.

## What?

This code will allow you to load all game-related files directly from your harddisk instead of the pk2-container. This will simplify your development process.

![a cool screenshot](https://github.com/florian0/GFXFileManager/blob/master/doc/screenshot.png)

Simply compile the code using *Visual Studio 2010*. Other versions, especially newer, may not work properly (Feel free to test and report your results).
Place the compiled `GFXFileManager.dll` inside your Silkroad Folder.

### Work in progress!

The implementation is far from complete and has been tested just barely. At the current state of development, the game will start just fine. Creating or deleting files, handling directories, browsing archives, is currently not possible.


## Customize

This code also allows you to create your own container-format. Study the code and implement all required functions for your container.

The code will automatically output every function call. This is useful for debugging but will slow everything a lot, so use with care.
Some messages are configureable. Simply change the first lines of `CWFileManager.cpp`:
```
// Show debug messages on file-open and file-close (slow)
#define DEBUG_PRINT_FILES 0

// Show debug-messages on file-read and file-write (very slow!)
#define DEBUG_PRINT_IO 0

// Show debug-messages on unknown methods
#define DEBUG_PRINT_UNKNOWN 0

// Show a messagen when opening failed
#define DEBUG_PRINT_NOTFOUND 0
```
You really should consider creating custom filters for filenames.

## Troubleshooting & Support

Feel free to report all bugs and problems you encounter. This is a work in progress and any contribution is welcome.




