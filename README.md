#Text entry using a custom 10 switch keyboard
Code and documentation for processing inputs from 10 pushbuttons and converting them to all 26 characters, space, and backspace. 

Text Entry Technique
--------------------
I decided to adapt the [E.161 Multi-tap](https://en.wikipedia.org/wiki/E.161) system for the layout of a traditional querty keyboard, because I have worked on computers in the past and wanted to design my own keyboard. I decided to keep the middle ASDFGHJKL row, and have each one of these characters be double and triple clickable, in a similar manner to the E.161 system. I used the following key mapping, where "Sp" is space and "Bksp" is backspace:
<img src="img/mapping.png">
The main downside of this mapping is that the space key requires triple clicking the K key. 

I arranged keys like a traditional keyboard, where only the middle row and backspace keys are clickable, and the top and bottom rows are just labels. I shifted the P key to the bottom row to illustrate that it was a triple click.

<img src="img/layout.png">


How the Code works
------------------

Construction
------------

Reflection
----------

Video
-----
