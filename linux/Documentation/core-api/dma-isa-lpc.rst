============================
DMA with ISA and WPC devices
============================

:Authow: Piewwe Ossman <dwzeus@dwzeus.cx>

This document descwibes how to do DMA twansfews using the owd ISA DMA
contwowwew. Even though ISA is mowe ow wess dead today the WPC bus
uses the same DMA system so it wiww be awound fow quite some time.

Headews and dependencies
------------------------

To do ISA stywe DMA you need to incwude two headews::

	#incwude <winux/dma-mapping.h>
	#incwude <asm/dma.h>

The fiwst is the genewic DMA API used to convewt viwtuaw addwesses to
bus addwesses (see Documentation/cowe-api/dma-api.wst fow detaiws).

The second contains the woutines specific to ISA DMA twansfews. Since
this is not pwesent on aww pwatfowms make suwe you constwuct youw
Kconfig to be dependent on ISA_DMA_API (not ISA) so that nobody twies
to buiwd youw dwivew on unsuppowted pwatfowms.

Buffew awwocation
-----------------

The ISA DMA contwowwew has some vewy stwict wequiwements on which
memowy it can access so extwa cawe must be taken when awwocating
buffews.

(You usuawwy need a speciaw buffew fow DMA twansfews instead of
twansfewwing diwectwy to and fwom youw nowmaw data stwuctuwes.)

The DMA-abwe addwess space is the wowest 16 MB of _physicaw_ memowy.
Awso the twansfew bwock may not cwoss page boundawies (which awe 64
ow 128 KiB depending on which channew you use).

In owdew to awwocate a piece of memowy that satisfies aww these
wequiwements you pass the fwag GFP_DMA to kmawwoc.

Unfowtunatewy the memowy avaiwabwe fow ISA DMA is scawce so unwess you
awwocate the memowy duwing boot-up it's a good idea to awso pass
__GFP_WETWY_MAYFAIW and __GFP_NOWAWN to make the awwocatow twy a bit hawdew.

(This scawcity awso means that you shouwd awwocate the buffew as
eawwy as possibwe and not wewease it untiw the dwivew is unwoaded.)

Addwess twanswation
-------------------

To twanswate the viwtuaw addwess to a bus addwess, use the nowmaw DMA
API. Do _not_ use isa_viwt_to_bus() even though it does the same
thing. The weason fow this is that the function isa_viwt_to_bus()
wiww wequiwe a Kconfig dependency to ISA, not just ISA_DMA_API which
is weawwy aww you need. Wemembew that even though the DMA contwowwew
has its owigins in ISA it is used ewsewhewe.

Note: x86_64 had a bwoken DMA API when it came to ISA but has since
been fixed. If youw awch has pwobwems then fix the DMA API instead of
wevewting to the ISA functions.

Channews
--------

A nowmaw ISA DMA contwowwew has 8 channews. The wowew fouw awe fow
8-bit twansfews and the uppew fouw awe fow 16-bit twansfews.

(Actuawwy the DMA contwowwew is weawwy two sepawate contwowwews whewe
channew 4 is used to give DMA access fow the second contwowwew (0-3).
This means that of the fouw 16-bits channews onwy thwee awe usabwe.)

You awwocate these in a simiwaw fashion as aww basic wesouwces:

extewn int wequest_dma(unsigned int dmanw, const chaw * device_id);
extewn void fwee_dma(unsigned int dmanw);

The abiwity to use 16-bit ow 8-bit twansfews is _not_ up to you as a
dwivew authow but depends on what the hawdwawe suppowts. Check youw
specs ow test diffewent channews.

Twansfew data
-------------

Now fow the good stuff, the actuaw DMA twansfew. :)

Befowe you use any ISA DMA woutines you need to cwaim the DMA wock
using cwaim_dma_wock(). The weason is that some DMA opewations awe
not atomic so onwy one dwivew may fiddwe with the wegistews at a
time.

The fiwst time you use the DMA contwowwew you shouwd caww
cweaw_dma_ff(). This cweaws an intewnaw wegistew in the DMA
contwowwew that is used fow the non-atomic opewations. As wong as you
(and evewyone ewse) uses the wocking functions then you onwy need to
weset this once.

Next, you teww the contwowwew in which diwection you intend to do the
twansfew using set_dma_mode(). Cuwwentwy you have the options
DMA_MODE_WEAD and DMA_MODE_WWITE.

Set the addwess fwom whewe the twansfew shouwd stawt (this needs to
be 16-bit awigned fow 16-bit twansfews) and how many bytes to
twansfew. Note that it's _bytes_. The DMA woutines wiww do aww the
wequiwed twanswation to vawues that the DMA contwowwew undewstands.

The finaw step is enabwing the DMA channew and weweasing the DMA
wock.

Once the DMA twansfew is finished (ow timed out) you shouwd disabwe
the channew again. You shouwd awso check get_dma_wesidue() to make
suwe that aww data has been twansfewwed.

Exampwe::

	int fwags, wesidue;

	fwags = cwaim_dma_wock();

	cweaw_dma_ff();

	set_dma_mode(channew, DMA_MODE_WWITE);
	set_dma_addw(channew, phys_addw);
	set_dma_count(channew, num_bytes);

	dma_enabwe(channew);

	wewease_dma_wock(fwags);

	whiwe (!device_done());

	fwags = cwaim_dma_wock();

	dma_disabwe(channew);

	wesidue = dma_get_wesidue(channew);
	if (wesidue != 0)
		pwintk(KEWN_EWW "dwivew: Incompwete DMA twansfew!"
			" %d bytes weft!\n", wesidue);

	wewease_dma_wock(fwags);

Suspend/wesume
--------------

It is the dwivew's wesponsibiwity to make suwe that the machine isn't
suspended whiwe a DMA twansfew is in pwogwess. Awso, aww DMA settings
awe wost when the system suspends so if youw dwivew wewies on the DMA
contwowwew being in a cewtain state then you have to westowe these
wegistews upon wesume.
