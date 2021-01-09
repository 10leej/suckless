# My Suckless Tools
These are my copies of the suckless programs I use. I modify all these through the config.def.h file but I do save the original copies of each file as confg.def.h.og should I ever need them.  
This is because when you compile these programs after patching sometimes make will error, so best practice is to just simply deal with config.def.h instead of config.h like how the suckless devs recommend.  

# Instructions
I compile these under Fedora 33 but you need to install the Development Tools group  
    dnf groupinstall "Development Tools"
    dnf install gdk-pixbuf2-xlib-devel libXft-devel libXinerama-devel

The Font I use is [JetBrains Mono](https://www.jetbrains.com/lp/mono) which I drop in ~/.fonts

then to compile these all you have to do is go into each folder and run this command
    sudo make clean install

Bear in mind I don't really use xssstate or st and my dmenu is more or less depreciated since dmenu doiesn't actually read the .desktop files found in /usr/share/applications/ and instead reads /usr/bin/  

I instead currently use rofi

## Application List
rofi  
firefox  
pcmanfm  
virt-manager  
vscodium (I use vim for editing smaller files and quick edits mostly)  
maim  
discord (flatpak)
element (flatpak)  
