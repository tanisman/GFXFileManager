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
Some messages are configureable. Simply change this line of `debug.cpp`:
```
int m_group = DEBUG_FULL;
```
There are several groups available:
```
enum debug_group {
	DEBUG_OFF			= 0,
	DEBUG_OBJECT		= 1,
	DEBUG_CONTAINER		= 2,
	DEBUG_FILE_GEN		= 4,
	DEBUG_FILE			= 8,
	DEBUG_FILE_NOTFOUND	= 16,
	DEBUG_IO			= 32,
	DEBUG_DIRECTORY		= 64,
	DEBUG_DIRECTORY_GEN	= 128,
	DEBUG_SEARCH		= 256,
	DEBUG_UNKNOWN		= 512,
	DEBUG_OTHER			= 1024,
	DEBUG_FULL			= 0xFFFFFFFF
};
```

You can also combine multiple groups like this:
```
int m_group = DEBUG_CONTAINER | DEBUG_FILE_GEN | DEBUG_FILE_NOTFOUND | DEBUG_OTHER;
```

## Troubleshooting & Support

Feel free to report all bugs and problems you encounter. This is a work in progress and any contribution is welcome.




