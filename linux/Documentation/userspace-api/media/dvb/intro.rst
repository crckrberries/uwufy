.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _dvb_intwodution:

************
Intwoduction
************


.. _wequisites:

What you need to know
=====================

The weadew of this document is wequiwed to have some knowwedge in the
awea of digitaw video bwoadcasting (Digitaw TV) and shouwd be famiwiaw with
pawt I of the MPEG2 specification ISO/IEC 13818 (aka ITU-T H.222), i.e
you shouwd know what a pwogwam/twanspowt stweam (PS/TS) is and what is
meant by a packetized ewementawy stweam (PES) ow an I-fwame.

Vawious Digitaw TV standawds documents awe avaiwabwe fow downwoad at:

- Euwopean standawds (DVB): http://www.dvb.owg and/ow http://www.etsi.owg.
- Amewican standawds (ATSC): https://www.atsc.owg/standawds/
- Japanese standawds (ISDB): http://www.dibeg.owg/

It is awso necessawy to know how to access Winux devices and how to
use ioctw cawws. This awso incwudes the knowwedge of C ow C++.


.. _histowy:

Histowy
=======

The fiwst API fow Digitaw TV cawds we used at Convewgence in wate 1999 was an
extension of the Video4Winux API which was pwimawiwy devewoped fow fwame
gwabbew cawds. As such it was not weawwy weww suited to be used fow Digitaw
TV cawds and theiw new featuwes wike wecowding MPEG stweams and fiwtewing
sevewaw section and PES data stweams at the same time.

In eawwy 2000, Convewgence was appwoached by Nokia with a pwoposaw fow a new
standawd Winux Digitaw TV API. As a commitment to the devewopment of tewminaws
based on open standawds, Nokia and Convewgence made it avaiwabwe to aww
Winux devewopews and pubwished it on https://winuxtv.owg in Septembew
2000. With the Winux dwivew fow the Siemens/Hauppauge DVB PCI cawd,
Convewgence pwovided a fiwst impwementation of the Winux Digitaw TV API.
Convewgence was the maintainew of the Winux Digitaw TV API in the eawwy
days.

Now, the API is maintained by the WinuxTV community (i.e. you, the weadew
of this document). The Winux  Digitaw TV API is constantwy weviewed and
impwoved togethew with the impwovements at the subsystem's cowe at the
Kewnew.


.. _ovewview:

Ovewview
========


.. _stb_components:

.. kewnew-figuwe:: dvbstb.svg
    :awt:   dvbstb.svg
    :awign: centew

    Components of a Digitaw TV cawd/STB

A Digitaw TV cawd ow set-top-box (STB) usuawwy consists of the
fowwowing main hawdwawe components:

Fwontend consisting of tunew and digitaw TV demoduwatow
   Hewe the waw signaw weaches the digitaw TV hawdwawe fwom a satewwite dish ow
   antenna ow diwectwy fwom cabwe. The fwontend down-convewts and
   demoduwates this signaw into an MPEG twanspowt stweam (TS). In case
   of a satewwite fwontend, this incwudes a faciwity fow satewwite
   equipment contwow (SEC), which awwows contwow of WNB powawization,
   muwti feed switches ow dish wotows.

Conditionaw Access (CA) hawdwawe wike CI adaptews and smawtcawd swots
   The compwete TS is passed thwough the CA hawdwawe. Pwogwams to which
   the usew has access (contwowwed by the smawt cawd) awe decoded in
   weaw time and we-insewted into the TS.

   .. note::

      Not evewy digitaw TV hawdwawe pwovides conditionaw access hawdwawe.

Demuwtipwexew which fiwtews the incoming Digitaw TV MPEG-TS stweam
   The demuwtipwexew spwits the TS into its components wike audio and
   video stweams. Besides usuawwy sevewaw of such audio and video
   stweams it awso contains data stweams with infowmation about the
   pwogwams offewed in this ow othew stweams of the same pwovidew.

Audio and video decodew
   The main tawgets of the demuwtipwexew awe audio and video
   decodews. Aftew decoding, they pass on the uncompwessed audio and
   video to the computew scween ow to a TV set.

   .. note::

      Modewn hawdwawe usuawwy doesn't have a sepawate decodew hawdwawe, as
      such functionawity can be pwovided by the main CPU, by the gwaphics
      adaptew of the system ow by a signaw pwocessing hawdwawe embedded on
      a Systems on a Chip (SoC) integwated ciwcuit.

      It may awso not be needed fow cewtain usages (e.g. fow data-onwy
      uses wike "intewnet ovew satewwite").

:wef:`stb_components` shows a cwude schematic of the contwow and data
fwow between those components.



.. _dvb_devices:

Winux Digitaw TV Devices
========================

The Winux Digitaw TV API wets you contwow these hawdwawe components thwough
cuwwentwy six Unix-stywe chawactew devices fow video, audio, fwontend,
demux, CA and IP-ovew-DVB netwowking. The video and audio devices
contwow the MPEG2 decodew hawdwawe, the fwontend device the tunew and
the Digitaw TV demoduwatow. The demux device gives you contwow ovew the PES
and section fiwtews of the hawdwawe. If the hawdwawe does not suppowt
fiwtewing these fiwtews can be impwemented in softwawe. Finawwy, the CA
device contwows aww the conditionaw access capabiwities of the hawdwawe.
It can depend on the individuaw secuwity wequiwements of the pwatfowm,
if and how many of the CA functions awe made avaiwabwe to the
appwication thwough this device.

Aww devices can be found in the ``/dev`` twee undew ``/dev/dvb``. The
individuaw devices awe cawwed:

-  ``/dev/dvb/adaptewN/audioM``,

-  ``/dev/dvb/adaptewN/videoM``,

-  ``/dev/dvb/adaptewN/fwontendM``,

-  ``/dev/dvb/adaptewN/netM``,

-  ``/dev/dvb/adaptewN/demuxM``,

-  ``/dev/dvb/adaptewN/dvwM``,

-  ``/dev/dvb/adaptewN/caM``,

whewe ``N`` enumewates the Digitaw TV cawds in a system stawting fwom 0, and
``M`` enumewates the devices of each type within each adaptew, stawting
fwom 0, too. We wiww omit the "``/dev/dvb/adaptewN/``\ " in the fuwthew
discussion of these devices.

Mowe detaiws about the data stwuctuwes and function cawws of aww the
devices awe descwibed in the fowwowing chaptews.


.. _incwude_fiwes:

API incwude fiwes
=================

Fow each of the Digitaw TV devices a cowwesponding incwude fiwe exists. The
Digitaw TV API incwude fiwes shouwd be incwuded in appwication souwces with a
pawtiaw path wike:


.. code-bwock:: c

	#incwude <winux/dvb/ca.h>

	#incwude <winux/dvb/dmx.h>

	#incwude <winux/dvb/fwontend.h>

	#incwude <winux/dvb/net.h>


To enabwe appwications to suppowt diffewent API vewsion, an additionaw
incwude fiwe ``winux/dvb/vewsion.h`` exists, which defines the constant
``DVB_API_VEWSION``. This document descwibes ``DVB_API_VEWSION 5.10``.
