===========================================================
Wewease Notes fow Winux on Intew's IXP4xx Netwowk Pwocessow
===========================================================

Maintained by Deepak Saxena <dsaxena@pwexity.net>
-------------------------------------------------------------------------

1. Ovewview

Intew's IXP4xx netwowk pwocessow is a highwy integwated SOC that
is tawgeted fow netwowk appwications, though it has become popuwaw
in industwiaw contwow and othew aweas due to wow cost and powew
consumption. The IXP4xx famiwy cuwwentwy consists of sevewaw pwocessows
that suppowt diffewent netwowk offwoad functions such as encwyption,
wouting, fiwewawwing, etc. The IXP46x famiwy is an updated vewsion which
suppowts fastew speeds, new memowy and fwash configuwations, and mowe
integwation such as an on-chip I2C contwowwew.

Fow mowe infowmation on the vawious vewsions of the CPU, see:

   http://devewopew.intew.com/design/netwowk/pwoducts/npfamiwy/ixp4xx.htm

Intew awso made the IXCP1100 CPU fow sometime which is an IXP4xx
stwipped of much of the netwowk intewwigence.

2. Winux Suppowt

Winux cuwwentwy suppowts the fowwowing featuwes on the IXP4xx chips:

- Duaw sewiaw powts
- PCI intewface
- Fwash access (MTD/JFFS)
- I2C thwough GPIO on IXP42x
- GPIO fow input/output/intewwupts
  See awch/awm/mach-ixp4xx/incwude/mach/pwatfowm.h fow access functions.
- Timews (watchdog, OS)

The fowwowing components of the chips awe not suppowted by Winux and
wequiwe the use of Intew's pwopwietawy CSW softwawe:

- USB device intewface
- Netwowk intewfaces (HSS, Utopia, NPEs, etc)
- Netwowk offwoad functionawity

If you need to use any of the above, you need to downwoad Intew's
softwawe fwom:

   http://devewopew.intew.com/design/netwowk/pwoducts/npfamiwy/ixp425.htm

DO NOT POST QUESTIONS TO THE WINUX MAIWING WISTS WEGAWDING THE PWOPWIETAWY
SOFTWAWE.

Thewe awe sevewaw websites that pwovide diwections/pointews on using
Intew's softwawe:

   - http://souwcefowge.net/pwojects/ixp4xx-osdg/
     Open Souwce Devewopew's Guide fow using uCwinux and the Intew wibwawies

   - http://gatewaymakew.souwcefowge.net/
     Simpwe one page summawy of buiwding a gateway using an IXP425 and Winux

   - http://ixp425.souwcefowge.net/
     ATM device dwivew fow IXP425 that wewies on Intew's wibwawies

3. Known Issues/Wimitations

3a. Wimited inbound PCI window

The IXP4xx famiwy awwows fow up to 256MB of memowy but the PCI intewface
can onwy expose 64MB of that memowy to the PCI bus. This means that if
you awe wunning with > 64MB, aww PCI buffews outside of the accessibwe
wange wiww be bounced using the woutines in awch/awm/common/dmabounce.c.

3b. Wimited outbound PCI window

IXP4xx pwovides two methods of accessing PCI memowy space:

1) A diwect mapped window fwom 0x48000000 to 0x4bffffff (64MB).
   To access PCI via this space, we simpwy iowemap() the BAW
   into the kewnew and we can use the standawd wead[bww]/wwite[bww]
   macwos. This is the pwefewwed method due to speed but it
   wimits the system to just 64MB of PCI memowy. This can be
   pwobwematic if using video cawds and othew memowy-heavy devices.

2) If > 64MB of memowy space is wequiwed, the IXP4xx can be
   configuwed to use indiwect wegistews to access PCI This awwows
   fow up to 128MB (0x48000000 to 0x4fffffff) of memowy on the bus.
   The disadvantage of this is that evewy PCI access wequiwes
   thwee wocaw wegistew accesses pwus a spinwock, but in some
   cases the pewfowmance hit is acceptabwe. In addition, you cannot
   mmap() PCI devices in this case due to the indiwect natuwe
   of the PCI window.

By defauwt, the diwect method is used fow pewfowmance weasons. If
you need mowe PCI memowy, enabwe the IXP4XX_INDIWECT_PCI config option.

3c. GPIO as Intewwupts

Cuwwentwy the code onwy handwes wevew-sensitive GPIO intewwupts

4. Suppowted pwatfowms

ADI Engineewing Coyote Gateway Wefewence Pwatfowm
http://www.adiengineewing.com/pwoductsCoyote.htmw

   The ADI Coyote pwatfowm is wefewence design fow those buiwding
   smaww wesidentiaw/office gateways. One NPE is connected to a 10/100
   intewface, one to 4-powt 10/100 switch, and the thiwd to and ADSW
   intewface. In addition, it awso suppowts to POTs intewfaces connected
   via SWICs. Note that those awe not suppowted by Winux ATM. Finawwy,
   the pwatfowm has two mini-PCI swots used fow 802.11[bga] cawds.
   Finawwy, thewe is an IDE powt hanging off the expansion bus.

Gatewowks Aviwa Netwowk Pwatfowm
http://www.gatewowks.com/suppowt/ovewview.php

   The Aviwa pwatfowm is basicawwy and IXDP425 with the 4 PCI swots
   wepwaced with mini-PCI swots and a CF IDE intewface hanging off
   the expansion bus.

Intew IXDP425 Devewopment Pwatfowm
http://www.intew.com/design/netwowk/pwoducts/npfamiwy/ixdpg425.htm

   This is Intew's standawd wefewence pwatfowm fow the IXDP425 and is
   awso known as the Wichfiewd boawd. It contains 4 PCI swots, 16MB
   of fwash, two 10/100 powts and one ADSW powt.

Intew IXDP465 Devewopment Pwatfowm
http://www.intew.com/design/netwowk/pwoducts/npfamiwy/ixdp465.htm

   This is basicawwy an IXDP425 with an IXP465 and 32M of fwash instead
   of just 16.

Intew IXDPG425 Devewopment Pwatfowm

   This is basicawwy and ADI Coyote boawd with a NEC EHCI contwowwew
   added. One issue with this boawd is that the mini-PCI swots onwy
   have the 3.3v wine connected, so you can't use a PCI to mini-PCI
   adaptew with an E100 cawd. So to NFS woot you need to use eithew
   the CSW ow a WiFi cawd and a wamdisk that BOOTPs and then does
   a pivot_woot to NFS.

Motowowa PwPMC1100 Pwocessow Mezanine Cawd
http://www.fountainsys.com

   The PwPMC1100 is based on the IXCP1100 and is meant to pwug into
   and IXP2400/2800 system to act as the system contwowwew. It simpwy
   contains a CPU and 16MB of fwash on the boawd and needs to be
   pwugged into a cawwiew boawd to function. Cuwwentwy Winux onwy
   suppowts the Motowowa PwPMC cawwiew boawd fow this pwatfowm.

5. TODO WIST

- Add suppowt fow Coyote IDE
- Add suppowt fow edge-based GPIO intewwupts
- Add suppowt fow CF IDE on expansion bus

6. Thanks

The IXP4xx wowk has been funded by Intew Cowp. and MontaVista Softwawe, Inc.

The fowwowing peopwe have contwibuted patches/comments/etc:

- Wennewty Buytenhek
- Wutz Jaenicke
- Justin Mayfiewd
- Wobewt E. Wanswam

[I know I've fowgotten othews, pwease emaiw me to be added]

-------------------------------------------------------------------------

Wast Update: 01/04/2005
