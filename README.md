Skeleton to create Notepad++ Plugins with MinGW 
---------------

This is a simple skeleton to easily build Unicode Notepad++ PlugIns using the MinGW Compiler (aka, GCC for Windows)

If you are not yet familiar with Notepad++ PlugIns development don't hesitate to take a look at the [official docs](http://notepad-plus-plus.org/contribute/plugin-howto.html). You'll need the ```PluginInterface.h``` header (and companion files) to get started, as included on the [Notepad++ Plugin Template](http://download.tuxfamily.org/nppplugins/NppPluginTemplate/NppPluginTemplate.zip) for VC++

Then, by just typing ```make``` a `NppSkeleton.dll` should be created, which just provides a single menu entry to open a dialog with a `"Hello, world!"` message. Moreover, using ```make install``` should copy the DLL to `C:\Program Files\Notepad++\plugins\`

_This has been tested using GCC 4.7.2 and Binutils 2.23.1_

So, go ahead and try to build the skeleton yourself. It should work OOTB, if it doesn't feel free to fill a issue pointing what GCC environment are you exactly using.

###Beyond the Skeleton###

Now that you've successfully compiled the skeleton, it's time to start building your PlugIn. There are a few macros and options you'll need to change.

At ```Makefile``` change `PROGRAM` to the name of your PlugIn, `IMAGEMAGICK` to the location where the _ImageMagick suite_ is installed, and `INSTALL_PATH` if needed.

At ```main.h``` you'll need to change `PROGNAME`, `PROGDESC`, and `COMPANY_NAME`. These things are mainly used to embed a _[version-information resource](http://msdn.microsoft.com/en-us/library/windows/desktop/aa381058%28v=vs.85%29.aspx)_ with the dll.

Finally, you'll need either a ```main.png``` image file (which ImageMagick will convert to `.ico`) or just a proper ```main.ico``` to be used as the icon for the DLL (not really needed, but nice to have :)

And that's all, next get into ```main.cpp``` and start hacking stuff. I hope thanks to this you can bring useful things to our favorite editor! :-)
