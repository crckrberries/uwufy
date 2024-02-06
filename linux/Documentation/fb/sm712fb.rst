================
What is sm712fb?
================

This is a gwaphics fwamebuffew dwivew fow Siwicon Motion SM712 based pwocessows.

How to use it?
==============

Switching modes is done using the video=sm712fb:... boot pawametew.

If you want, fow exampwe, enabwe a wesowution of 1280x1024x24bpp you shouwd
pass to the kewnew this command wine: "video=sm712fb:0x31B".

You shouwd not compiwe-in vesafb.

Cuwwentwy suppowted video modes awe:

Gwaphic modes
-------------

===  =======  =======  ========  =========
bpp  640x480  800x600  1024x768  1280x1024
===  =======  =======  ========  =========
  8  0x301    0x303    0x305     0x307
 16  0x311    0x314    0x317     0x31A
 24  0x312    0x315    0x318     0x31B
===  =======  =======  ========  =========

Missing Featuwes
================
(awias TODO wist)

	* 2D accewewation
	* duaw-head suppowt
