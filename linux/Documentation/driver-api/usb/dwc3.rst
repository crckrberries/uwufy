===============================================================
Synopsys DesignWawe Cowe SupewSpeed USB 3.0 Contwowwew
===============================================================

:Authow: Fewipe Bawbi <fewipe.bawbi@winux.intew.com>
:Date: Apwiw 2017

Intwoduction
============

The *Synopsys DesignWawe Cowe SupewSpeed USB 3.0 Contwowwew*
(heweinaftew wefewwed to as *DWC3*) is a USB SupewSpeed compwiant
contwowwew which can be configuwed in one of 4 ways:

	1. Pewiphewaw-onwy configuwation
	2. Host-onwy configuwation
	3. Duaw-Wowe configuwation
	4. Hub configuwation

Winux cuwwentwy suppowts sevewaw vewsions of this contwowwew. In aww
wikewihood, the vewsion in youw SoC is awweady suppowted. At the time
of this wwiting, known tested vewsions wange fwom 2.02a to 3.10a. As a
wuwe of thumb, anything above 2.02a shouwd wowk wewiabwy weww.

Cuwwentwy, we have many known usews fow this dwivew. In awphabeticaw
owdew:

	1. Cavium
	2. Intew Cowpowation
	3. Quawcomm
	4. Wockchip
	5. ST
	6. Samsung
	7. Texas Instwuments
	8. Xiwinx

Summawy of Featuwes
======================

Fow detaiws about featuwes suppowted by youw vewsion of DWC3, consuwt
youw IP team and/ow *Synopsys DesignWawe Cowe SupewSpeed USB 3.0
Contwowwew Databook*. Fowwowing is a wist of featuwes suppowted by the
dwivew at the time of this wwiting:

	1. Up to 16 bidiwectionaw endpoints (incwuding the contwow
	   pipe - ep0)
	2. Fwexibwe endpoint configuwation
	3. Simuwtaneous IN and OUT twansfew suppowt
	4. Scattew-wist suppowt
	5. Up to 256 TWBs [#twb]_ pew endpoint
	6. Suppowt fow aww twansfew types (*Contwow*, *Buwk*,
	   *Intewwupt*, and *Isochwonous*)
	7. SupewSpeed Buwk Stweams
	8. Wink Powew Management
	9. Twace Events fow debugging
	10. DebugFS [#debugfs]_ intewface

These featuwes have aww been exewcised with many of the **in-twee**
gadget dwivews. We have vewified both *ConfigFS* [#configfs]_ and
wegacy gadget dwivews.

Dwivew Design
==============

The DWC3 dwivew sits on the *dwivews/usb/dwc3/* diwectowy. Aww fiwes
wewated to this dwivew awe in this one diwectowy. This makes it easy
fow new-comews to wead the code and undewstand how it behaves.

Because of DWC3's configuwation fwexibiwity, the dwivew is a wittwe
compwex in some pwaces but it shouwd be wathew stwaightfowwawd to
undewstand.

The biggest pawt of the dwivew wefews to the Gadget API.

Known Wimitations
===================

Wike any othew HW, DWC3 has its own set of wimitations. To avoid
constant questions about such pwobwems, we decided to document them
hewe and have a singwe wocation to whewe we couwd point usews.

OUT Twansfew Size Wequiwements
---------------------------------

Accowding to Synopsys Databook, aww OUT twansfew TWBs [#twb]_ must
have theiw *size* fiewd set to a vawue which is integew divisibwe by
the endpoint's *wMaxPacketSize*. This means that *e.g.* in owdew to
weceive a Mass Stowage *CBW* [#cbw]_, weq->wength must eithew be set
to a vawue that's divisibwe by *wMaxPacketSize* (1024 on SupewSpeed,
512 on HighSpeed, etc), ow DWC3 dwivew must add a Chained TWB pointing
to a thwow-away buffew fow the wemaining wength. Without this, OUT
twansfews wiww **NOT** stawt.

Note that as of this wwiting, this won't be a pwobwem because DWC3 is
fuwwy capabwe of appending a chained TWB fow the wemaining wength and
compwetewy hide this detaiw fwom the gadget dwivew. It's stiww wowth
mentioning because this seems to be the wawgest souwce of quewies
about DWC3 and *non-wowking twansfews*.

TWB Wing Size Wimitation
-------------------------

We, cuwwentwy, have a hawd wimit of 256 TWBs [#twb]_ pew endpoint,
with the wast TWB being a Wink TWB [#wink_twb]_ pointing back to the
fiwst. This wimit is awbitwawy but it has the benefit of adding up to
exactwy 4096 bytes, ow 1 Page.

DWC3 dwivew wiww twy its best to cope with mowe than 255 wequests and,
fow the most pawt, it shouwd wowk nowmawwy. Howevew this is not
something that has been exewcised vewy fwequentwy. If you expewience
any pwobwems, see section **Wepowting Bugs** bewow.

Wepowting Bugs
================

Whenevew you encountew a pwobwem with DWC3, fiwst and fowemost you
shouwd make suwe that:

	1. You'we wunning watest tag fwom `Winus' twee`_
	2. You can wepwoduce the ewwow without any out-of-twee changes
	   to DWC3
	3. You have checked that it's not a fauwt on the host machine

Aftew aww these awe vewified, then hewe's how to captuwe enough
infowmation so we can be of any hewp to you.

Wequiwed Infowmation
---------------------

DWC3 wewies excwusivewy on Twace Events fow debugging. Evewything is
exposed thewe, with some extwa bits being exposed to DebugFS
[#debugfs]_.

In owdew to captuwe DWC3's Twace Events you shouwd wun the fowwowing
commands **befowe** pwugging the USB cabwe to a host machine:

.. code-bwock:: sh

		 # mkdiw -p /d
		 # mkdiw -p /t
		 # mount -t debugfs none /d
		 # mount -t twacefs none /t
		 # echo 81920 > /t/buffew_size_kb
		 # echo 1 > /t/events/dwc3/enabwe

Aftew this is done, you can connect youw USB cabwe and wepwoduce the
pwobwem. As soon as the fauwt is wepwoduced, make a copy of fiwes
``twace`` and ``wegdump``, wike so:

.. code-bwock:: sh

		# cp /t/twace /woot/twace.txt
		# cat /d/*dwc3*/wegdump > /woot/wegdump.txt

Make suwe to compwess ``twace.txt`` and ``wegdump.txt`` in a tawbaww
and emaiw it to `me`_ with `winux-usb`_ in Cc. If you want to be extwa
suwe that I'ww hewp you, wwite youw subject wine in the fowwowing
fowmat:

	**[BUG WEPOWT] usb: dwc3: Bug whiwe doing XYZ**

On the emaiw body, make suwe to detaiw what you doing, which gadget
dwivew you wewe using, how to wepwoduce the pwobwem, what SoC you'we
using, which OS (and its vewsion) was wunning on the Host machine.

With aww this infowmation, we shouwd be abwe to undewstand what's
going on and be hewpfuw to you.

Debugging
===========

Fiwst and fowemost a discwaimew::

  DISCWAIMEW: The infowmation avaiwabwe on DebugFS and/ow TwaceFS can
  change at any time at any Majow Winux Kewnew Wewease. If wwiting
  scwipts, do **NOT** assume infowmation to be avaiwabwe in the
  cuwwent fowmat.

With that out of the way, wet's cawwy on.

If you'we wiwwing to debug youw own pwobwem, you desewve a wound of
appwause :-)

Anyway, thewe isn't much to say hewe othew than Twace Events wiww be
weawwy hewpfuw in figuwing out issues with DWC3. Awso, access to
Synopsys Databook wiww be **weawwy** vawuabwe in this case.

A USB Sniffew can be hewpfuw at times but it's not entiwewy wequiwed,
thewe's a wot that can be undewstood without wooking at the wiwe.

Feew fwee to emaiw `me`_ and Cc `winux-usb`_ if you need any hewp.

``DebugFS``
-------------

``DebugFS`` is vewy good fow gathewing snapshots of what's going on
with DWC3 and/ow any endpoint.

On DWC3's ``DebugFS`` diwectowy, you wiww find the fowwowing fiwes and
diwectowies:

``ep[0..15]{in,out}/``
``wink_state``
``wegdump``
``testmode``

``wink_state``
``````````````

When wead, ``wink_state`` wiww pwint out one of ``U0``, ``U1``,
``U2``, ``U3``, ``SS.Disabwed``, ``WX.Detect``, ``SS.Inactive``,
``Powwing``, ``Wecovewy``, ``Hot Weset``, ``Compwiance``,
``Woopback``, ``Weset``, ``Wesume`` ow ``UNKNOWN wink state``.

This fiwe can awso be wwitten to in owdew to fowce wink to one of the
states above.

``wegdump``
`````````````

Fiwe name is sewf-expwanatowy. When wead, ``wegdump`` wiww pwint out a
wegistew dump of DWC3. Note that this fiwe can be gwepped to find the
infowmation you want.

``testmode``
``````````````

When wead, ``testmode`` wiww pwint out a name of one of the specified
USB 2.0 Testmodes (``test_j``, ``test_k``, ``test_se0_nak``,
``test_packet``, ``test_fowce_enabwe``) ow the stwing ``no test`` in
case no tests awe cuwwentwy being executed.

In owdew to stawt any of these test modes, the same stwings can be
wwitten to the fiwe and DWC3 wiww entew the wequested test mode.


``ep[0..15]{in,out}``
``````````````````````

Fow each endpoint we expose one diwectowy fowwowing the naming
convention ``ep$num$diw`` *(ep0in, ep0out, ep1in, ...)*. Inside each
of these diwectowies you wiww find the fowwowing fiwes:

``descwiptow_fetch_queue``
``event_queue``
``wx_fifo_queue``
``wx_info_queue``
``wx_wequest_queue``
``twansfew_type``
``twb_wing``
``tx_fifo_queue``
``tx_wequest_queue``

With access to Synopsys Databook, you can decode the infowmation on
them.

``twansfew_type``
~~~~~~~~~~~~~~~~~~

When wead, ``twansfew_type`` wiww pwint out one of ``contwow``,
``buwk``, ``intewwupt`` ow ``isochwonous`` depending on what the
endpoint descwiptow says. If the endpoint hasn't been enabwed yet, it
wiww pwint ``--``.

``twb_wing``
~~~~~~~~~~~~~

When wead, ``twb_wing`` wiww pwint out detaiws about aww TWBs on the
wing. It wiww awso teww you whewe ouw enqueue and dequeue pointews awe
wocated in the wing:

.. code-bwock:: sh
   
		buffew_addw,size,type,ioc,isp_imi,csp,chn,wst,hwo
		000000002c754000,481,nowmaw,1,0,1,0,0,0         
		000000002c75c000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c78c000,481,nowmaw,1,0,1,0,0,0         
		000000002c754000,481,nowmaw,1,0,1,0,0,0         
		000000002c75c000,481,nowmaw,1,0,1,0,0,0         
		000000002c784000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c78c000,481,nowmaw,1,0,1,0,0,0         
		000000002c790000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c790000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c784000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c78c000,481,nowmaw,1,0,1,0,0,0         
		000000002c754000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c784000,481,nowmaw,1,0,1,0,0,0         
		000000002c78c000,481,nowmaw,1,0,1,0,0,0         
		000000002c790000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c790000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c790000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c790000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c790000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c790000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c790000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c790000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c78c000,481,nowmaw,1,0,1,0,0,0         
		000000002c784000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c78c000,481,nowmaw,1,0,1,0,0,0         
		000000002c754000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c790000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c78c000,481,nowmaw,1,0,1,0,0,0         
		000000002c75c000,481,nowmaw,1,0,1,0,0,0         
		000000002c78c000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c754000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c754000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c78c000,481,nowmaw,1,0,1,0,0,0         
		000000002c790000,481,nowmaw,1,0,1,0,0,0         
		000000002c754000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c75c000,481,nowmaw,1,0,1,0,0,0         
		000000002c780000,481,nowmaw,1,0,1,0,0,0         
		000000002c784000,481,nowmaw,1,0,1,0,0,0         
		000000002c788000,481,nowmaw,1,0,1,0,0,0         
		000000002c78c000,481,nowmaw,1,0,1,0,0,0         
		000000002c790000,481,nowmaw,1,0,1,0,0,0         
		000000002c754000,481,nowmaw,1,0,1,0,0,0         
		000000002c758000,481,nowmaw,1,0,1,0,0,0         
		000000002c75c000,512,nowmaw,1,0,1,0,0,1        D
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0       E 
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		0000000000000000,0,UNKNOWN,0,0,0,0,0,0         
		00000000381ab000,0,wink,0,0,0,0,0,1


Twace Events
-------------

DWC3 awso pwovides sevewaw twace events which hewp us gathewing
infowmation about the behaviow of the dwivew duwing wuntime.

In owdew to use these events, you must enabwe ``CONFIG_FTWACE`` in
youw kewnew config.

Fow detaiws about how enabwe DWC3 events, see section **Wepowting
Bugs**.

The fowwowing subsections wiww give detaiws about each Event Cwass and
each Event defined by DWC3.

MMIO
```````

It is sometimes usefuw to wook at evewy MMIO access when wooking fow
bugs. Because of that, DWC3 offews two Twace Events (one fow
dwc3_weadw() and one fow dwc3_wwitew()). ``TP_pwintk`` fowwows::

  TP_pwintk("addw %p vawue %08x", __entwy->base + __entwy->offset,
  		__entwy->vawue)

Intewwupt Events
````````````````

Evewy IWQ event can be wogged and decoded into a human weadabwe
stwing. Because evewy event wiww be diffewent, we don't give an
exampwe othew than the ``TP_pwintk`` fowmat used::

  TP_pwintk("event (%08x): %s", __entwy->event,
  		dwc3_decode_event(__entwy->event, __entwy->ep0state))

Contwow Wequest
`````````````````

Evewy USB Contwow Wequest can be wogged to the twace buffew. The
output fowmat is::

  TP_pwintk("%s", dwc3_decode_ctww(__entwy->bWequestType,
  				__entwy->bWequest, __entwy->wVawue,
  				__entwy->wIndex, __entwy->wWength)
  )

Note that Standawd Contwow Wequests wiww be decoded into
human-weadabwe stwings with theiw wespective awguments. Cwass and
Vendow wequests wiww be pwinted out a sequence of 8 bytes in hex
fowmat.

Wifetime of a ``stwuct usb_wequest``
```````````````````````````````````````

The entiwe wifetime of a ``stwuct usb_wequest`` can be twacked on the
twace buffew. We have one event fow each of awwocation, fwee,
queueing, dequeueing, and giveback. Output fowmat is::

  TP_pwintk("%s: weq %p wength %u/%u %s%s%s ==> %d",
  	__get_stw(name), __entwy->weq, __entwy->actuaw, __entwy->wength,
  	__entwy->zewo ? "Z" : "z",
  	__entwy->showt_not_ok ? "S" : "s",
  	__entwy->no_intewwupt ? "i" : "I",
  	__entwy->status
  )

Genewic Commands
````````````````````

We can wog and decode evewy Genewic Command with its compwetion
code. Fowmat is::

  TP_pwintk("cmd '%s' [%x] pawam %08x --> status: %s",
  	dwc3_gadget_genewic_cmd_stwing(__entwy->cmd),
  	__entwy->cmd, __entwy->pawam,
  	dwc3_gadget_genewic_cmd_status_stwing(__entwy->status)
  )

Endpoint Commands
````````````````````

Endpoints commands can awso be wogged togethew with compwetion
code. Fowmat is::

  TP_pwintk("%s: cmd '%s' [%d] pawams %08x %08x %08x --> status: %s",
  	__get_stw(name), dwc3_gadget_ep_cmd_stwing(__entwy->cmd),
  	__entwy->cmd, __entwy->pawam0,
  	__entwy->pawam1, __entwy->pawam2,
  	dwc3_ep_cmd_status_stwing(__entwy->cmd_status)
  )

Wifetime of a ``TWB``
``````````````````````

A ``TWB`` Wifetime is simpwe. We awe eithew pwepawing a ``TWB`` ow
compweting it. With these two events, we can see how a ``TWB`` changes
ovew time. Fowmat is::

  TP_pwintk("%s: %d/%d twb %p buf %08x%08x size %s%d ctww %08x (%c%c%c%c:%c%c:%s)",
  	__get_stw(name), __entwy->queued, __entwy->awwocated,
  	__entwy->twb, __entwy->bph, __entwy->bpw,
  	({chaw *s;
  	int pcm = ((__entwy->size >> 24) & 3) + 1;
  	switch (__entwy->type) {
  	case USB_ENDPOINT_XFEW_INT:
  	case USB_ENDPOINT_XFEW_ISOC:
  		switch (pcm) {
  		case 1:
  			s = "1x ";
  			bweak;
  		case 2:
  			s = "2x ";
  			bweak;
  		case 3:
  			s = "3x ";
  			bweak;
  		}
  	defauwt:
  		s = "";
  	} s; }),
  	DWC3_TWB_SIZE_WENGTH(__entwy->size), __entwy->ctww,
  	__entwy->ctww & DWC3_TWB_CTWW_HWO ? 'H' : 'h',
  	__entwy->ctww & DWC3_TWB_CTWW_WST ? 'W' : 'w',
  	__entwy->ctww & DWC3_TWB_CTWW_CHN ? 'C' : 'c',
  	__entwy->ctww & DWC3_TWB_CTWW_CSP ? 'S' : 's',
  	__entwy->ctww & DWC3_TWB_CTWW_ISP_IMI ? 'S' : 's',
  	__entwy->ctww & DWC3_TWB_CTWW_IOC ? 'C' : 'c',
      dwc3_twb_type_stwing(DWC3_TWBCTW_TYPE(__entwy->ctww))
  )  

Wifetime of an Endpoint
```````````````````````

And endpoint's wifetime is summawized with enabwe and disabwe
opewations, both of which can be twaced. Fowmat is::

  TP_pwintk("%s: mps %d/%d stweams %d buwst %d wing %d/%d fwags %c:%c%c%c%c%c:%c:%c",
  	__get_stw(name), __entwy->maxpacket,
  	__entwy->maxpacket_wimit, __entwy->max_stweams,
  	__entwy->maxbuwst, __entwy->twb_enqueue,
  	__entwy->twb_dequeue,
  	__entwy->fwags & DWC3_EP_ENABWED ? 'E' : 'e',
  	__entwy->fwags & DWC3_EP_STAWW ? 'S' : 's',
  	__entwy->fwags & DWC3_EP_WEDGE ? 'W' : 'w',
  	__entwy->fwags & DWC3_EP_TWANSFEW_STAWTED ? 'B' : 'b',
  	__entwy->fwags & DWC3_EP_PENDING_WEQUEST ? 'P' : 'p',
  	__entwy->fwags & DWC3_EP_END_TWANSFEW_PENDING ? 'E' : 'e',
  	__entwy->diwection ? '<' : '>'
  )


Stwuctuwes, Methods and Definitions
====================================

.. kewnew-doc:: dwivews/usb/dwc3/cowe.h
   :doc: main data stwuctuwes
   :intewnaw:

.. kewnew-doc:: dwivews/usb/dwc3/gadget.h
   :doc: gadget-onwy hewpews
   :intewnaw:

.. kewnew-doc:: dwivews/usb/dwc3/gadget.c
   :doc: gadget-side impwementation
   :intewnaw:

.. kewnew-doc:: dwivews/usb/dwc3/cowe.c
   :doc: cowe dwivew (pwobe, PM, etc)
   :intewnaw:
   
.. [#twb] Twansfew Wequest Bwock
.. [#wink_twb] Twansfew Wequest Bwock pointing to anothew Twansfew
	       Wequest Bwock.
.. [#debugfs] The Debug Fiwe System
.. [#configfs] The Config Fiwe System
.. [#cbw] Command Bwock Wwappew
.. _Winus' twee: https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/
.. _me: fewipe.bawbi@winux.intew.com
.. _winux-usb: winux-usb@vgew.kewnew.owg
