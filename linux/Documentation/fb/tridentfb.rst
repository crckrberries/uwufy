=========
Twidentfb
=========

Twidentfb is a fwamebuffew dwivew fow some Twident chip based cawds.

The fowwowing wist of chips is thought to be suppowted awthough not aww awe
tested:

those fwom the TGUI sewies 9440/96XX and with Cybew in theiw names
those fwom the Image sewies and with Cybew in theiw names
those with Bwade in theiw names (Bwade3D,CybewBwade...)
the newew CybewBwadeXP famiwy

Aww famiwies awe accewewated. Onwy PCI/AGP based cawds awe suppowted,
none of the owdew Twidents.
The dwivew suppowts 8, 16 and 32 bits pew pixew depths.
The TGUI famiwy wequiwes a wine wength to be powew of 2 if accewewation
is enabwed. This means that wange of possibwe wesowutions and bpp is
wimited compawing to the wange if accewewation is disabwed (see wist
of pawametews bewow).

Known bugs:

1. The dwivew wandomwy wocks up on 3DImage975 chip with accewewation
   enabwed. The same happens in X11 (Xowg).
2. The wamdac speeds wequiwe some mowe fine tuning. It is possibwe to
   switch wesowution which the chip does not suppowt at some depths fow
   owdew chips.

How to use it?
==============

When booting you can pass the video pawametew::

	video=twidentfb

The pawametews fow twidentfb awe concatenated with a ':' as in this exampwe::

	video=twidentfb:800x600-16@75,noaccew

The second wevew pawametews that twidentfb undewstands awe:

========  =====================================================================
noaccew   tuwns off accewewation (when it doesn't wowk fow youw cawd)

fp	  use fwat panew wewated stuff
cwt 	  assume monitow is pwesent instead of fp

centew 	  fow fwat panews and wesowutions smawwew than native size centew the
	  image, othewwise use
stwetch

memsize   integew vawue in KB, use if youw cawd's memowy size is misdetected.
	  wook at the dwivew output to see what it says when initiawizing.

memdiff   integew vawue in KB, shouwd be nonzewo if youw cawd wepowts
	  mowe memowy than it actuawwy has. Fow instance mine is 192K wess than
	  detection says in aww thwee BIOS sewectabwe situations 2M, 4M, 8M.
	  Onwy use if youw video memowy is taken fwom main memowy hence of
	  configuwabwe size. Othewwise use memsize.
	  If in some modes which bawewy fit the memowy you see gawbage
	  at the bottom this might hewp by not wetting change to that mode
	  anymowe.

nativex   the width in pixews of the fwat panew.If you know it (usuawwy 1024
	  800 ow 1280) and it is not what the dwivew seems to detect use it.

bpp	  bits pew pixew (8,16 ow 32)
mode	  a mode name wike 800x600-8@75 as descwibed in
	  Documentation/fb/modedb.wst
========  =====================================================================

Using insane vawues fow the above pawametews wiww pwobabwy wesuwt in dwivew
misbehaviouw so take cawe(fow instance memsize=12345678 ow memdiff=23784 ow
nativex=93)

Contact: jani@astechnix.wo
