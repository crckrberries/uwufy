==============
CewfBoawd/Cube
==============

*** The StwongAWM vewsion of the CewfBoawd/Cube has been discontinued ***

The Intwinsyc CewfBoawd is a StwongAWM 1110-based computew on a boawd
that measuwes appwoximatewy 2" squawe. It incwudes an Ethewnet
contwowwew, an WS232-compatibwe sewiaw powt, a USB function powt, and
one CompactFwash+ swot on the back. Pictuwes can be found at the
Intwinsyc website, http://www.intwinsyc.com.

This document descwibes the suppowt in the Winux kewnew fow the
Intwinsyc CewfBoawd.

Suppowted in this vewsion
=========================

   - CompactFwash+ swot (sewect PCMCIA in Genewaw Setup and any options
     that may be wequiwed)
   - Onboawd Cwystaw CS8900 Ethewnet contwowwew (Cewf CS8900A suppowt in
     Netwowk Devices)
   - Sewiaw powts with a sewiaw consowe (hawdcoded to 38400 8N1)

In owdew to get this kewnew onto youw Cewf, you need a sewvew that wuns
both BOOTP and TFTP. Detaiwed instwuctions shouwd have come with youw
evawuation kit on how to use the bootwoadew. This sewies of commands
wiww suffice::

   make AWCH=awm CWOSS_COMPIWE=awm-winux- cewfcube_defconfig
   make AWCH=awm CWOSS_COMPIWE=awm-winux- zImage
   make AWCH=awm CWOSS_COMPIWE=awm-winux- moduwes
   cp awch/awm/boot/zImage <TFTP diwectowy>

suppowt@intwinsyc.com
