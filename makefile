# ##### BEGIN LICENSE BLOCK #####
# Version: MIT/X11 License
# 
# Copyright (c) 2013 Diego Casorran
# 
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
# 
# Contributor(s):
#   Diego Casorran <dcasorran@gmail.com> (Original Author)
# 
# ##### END LICENSE BLOCK #####

ARCH    =  mingw32
PROGRAM =  NppSkeleton
TARGET  =  $(PROGRAM).dll
CC      =  $(ARCH)-gcc
CXX     =  $(ARCH)-g++
WINDRES =  windres -O coff
RM      =  rm -f
CFLAGS  =  -O2 -mtune=i686 -DBUILD_DLL -W -Wall -gstabs -mwindows
LIBS    =  -lws2_32 -lz -lm -Wl,-Map,$@.map,--cref -static-libgcc
LDFLAGS =  -Wl,--out-implib,$(TARGET) -shared -lshlwapi $(CFLAGS)
OBJDIR  =  .objs

IMAGEMAGICK = C:\Portable\ImageMagick
IMC = $(IMAGEMAGICK)\convert.exe

INSTALL_PATH = "C:\\Program Files\\Notepad++\\plugins\\"

OBJS	= \
	$(OBJDIR)/main.res \
	$(OBJDIR)/main.o

all:	$(OBJDIR) $(TARGET)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: %.c
	@echo Compiling $@
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.cpp
	@echo Compiling $@
	@$(CXX) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	@echo Linking $@
	$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)

$(OBJDIR)/%.res: %.rc %.ico %.h
	$(WINDRES) -o $@ $<

%.ico: %.png
	@echo Creating $@
	@$(IMC) $< -resize 128x128 -transparent white _128.png
	@$(IMC) _128.png -resize 16x16 _16.png
	@$(IMC) _128.png -resize 32x32 _32.png
	@$(IMC) _128.png -resize 48x48 _48.png
	@$(IMC) _16.png _32.png _48.png _128.png -quality 100 $@
	@$(RM) ./_*.png

install: $(OBJDIR) $(TARGET)
	@echo Installing $(TARGET)...
	@cp $(TARGET) $(INSTALL_PATH)

clean:
	$(RM) -r $(OBJDIR)
	$(RM) ./*.ico
	$(RM) ./*.dll
	$(RM) ./*.map
