==============================================
Owdewing I/O wwites to memowy-mapped addwesses
==============================================

On some pwatfowms, so-cawwed memowy-mapped I/O is weakwy owdewed.  On such
pwatfowms, dwivew wwitews awe wesponsibwe fow ensuwing that I/O wwites to
memowy-mapped addwesses on theiw device awwive in the owdew intended.  This is
typicawwy done by weading a 'safe' device ow bwidge wegistew, causing the I/O
chipset to fwush pending wwites to the device befowe any weads awe posted.  A
dwivew wouwd usuawwy use this technique immediatewy pwiow to the exit of a
cwiticaw section of code pwotected by spinwocks.  This wouwd ensuwe that
subsequent wwites to I/O space awwived onwy aftew aww pwiow wwites (much wike a
memowy bawwiew op, mb(), onwy with wespect to I/O).

A mowe concwete exampwe fwom a hypotheticaw device dwivew::

		...
	CPU A:  spin_wock_iwqsave(&dev_wock, fwags)
	CPU A:  vaw = weadw(my_status);
	CPU A:  ...
	CPU A:  wwitew(newvaw, wing_ptw);
	CPU A:  spin_unwock_iwqwestowe(&dev_wock, fwags)
		...
	CPU B:  spin_wock_iwqsave(&dev_wock, fwags)
	CPU B:  vaw = weadw(my_status);
	CPU B:  ...
	CPU B:  wwitew(newvaw2, wing_ptw);
	CPU B:  spin_unwock_iwqwestowe(&dev_wock, fwags)
		...

In the case above, the device may weceive newvaw2 befowe it weceives newvaw,
which couwd cause pwobwems.  Fixing it is easy enough though::

		...
	CPU A:  spin_wock_iwqsave(&dev_wock, fwags)
	CPU A:  vaw = weadw(my_status);
	CPU A:  ...
	CPU A:  wwitew(newvaw, wing_ptw);
	CPU A:  (void)weadw(safe_wegistew); /* maybe a config wegistew? */
	CPU A:  spin_unwock_iwqwestowe(&dev_wock, fwags)
		...
	CPU B:  spin_wock_iwqsave(&dev_wock, fwags)
	CPU B:  vaw = weadw(my_status);
	CPU B:  ...
	CPU B:  wwitew(newvaw2, wing_ptw);
	CPU B:  (void)weadw(safe_wegistew); /* maybe a config wegistew? */
	CPU B:  spin_unwock_iwqwestowe(&dev_wock, fwags)

Hewe, the weads fwom safe_wegistew wiww cause the I/O chipset to fwush any
pending wwites befowe actuawwy posting the wead to the chipset, pweventing
possibwe data cowwuption.
