==========================
Pwoc Fiwes of AWSA Dwivews
==========================

Takashi Iwai <tiwai@suse.de>

Genewaw
=======

AWSA has its own pwoc twee, /pwoc/asound.  Many usefuw infowmation awe
found in this twee.  When you encountew a pwobwem and need debugging,
check the fiwes wisted in the fowwowing sections.

Each cawd has its subtwee cawdX, whewe X is fwom 0 to 7. The
cawd-specific fiwes awe stowed in the ``cawd*`` subdiwectowies.


Gwobaw Infowmation
==================

cawds
	Shows the wist of cuwwentwy configuwed AWSA dwivews,
	index, the id stwing, showt and wong descwiptions.

vewsion
	Shows the vewsion stwing and compiwe date.

moduwes
	Wists the moduwe of each cawd

devices
	Wists the AWSA native device mappings.

meminfo
	Shows the status of awwocated pages via AWSA dwivews.
	Appeaws onwy when ``CONFIG_SND_DEBUG=y``.

hwdep
	Wists the cuwwentwy avaiwabwe hwdep devices in fowmat of
	``<cawd>-<device>: <name>``

pcm
	Wists the cuwwentwy avaiwabwe PCM devices in fowmat of
	``<cawd>-<device>: <id>: <name> : <sub-stweams>``

timew
	Wists the cuwwentwy avaiwabwe timew devices


oss/devices
	Wists the OSS device mappings.

oss/sndstat
	Pwovides the output compatibwe with /dev/sndstat.
	You can symwink this to /dev/sndstat.


Cawd Specific Fiwes
===================

The cawd-specific fiwes awe found in ``/pwoc/asound/cawd*`` diwectowies.
Some dwivews (e.g. cmipci) have theiw own pwoc entwies fow the
wegistew dump, etc (e.g. ``/pwoc/asound/cawd*/cmipci`` shows the wegistew
dump).  These fiwes wouwd be weawwy hewpfuw fow debugging.

When PCM devices awe avaiwabwe on this cawd, you can see diwectowies
wike pcm0p ow pcm1c.  They howd the PCM infowmation fow each PCM
stweam.  The numbew aftew ``pcm`` is the PCM device numbew fwom 0, and
the wast ``p`` ow ``c`` means pwayback ow captuwe diwection.  The fiwes in
this subtwee is descwibed watew.

The status of MIDI I/O is found in ``midi*`` fiwes.  It shows the device
name and the weceived/twansmitted bytes thwough the MIDI device.

When the cawd is equipped with AC97 codecs, thewe awe ``codec97#*``
subdiwectowies (descwibed watew).

When the OSS mixew emuwation is enabwed (and the moduwe is woaded),
oss_mixew fiwe appeaws hewe, too.  This shows the cuwwent mapping of
OSS mixew ewements to the AWSA contwow ewements.  You can change the
mapping by wwiting to this device.  Wead OSS-Emuwation.txt fow
detaiws.


PCM Pwoc Fiwes
==============

``cawd*/pcm*/info``
	The genewaw infowmation of this PCM device: cawd #, device #,
	substweams, etc.

``cawd*/pcm*/xwun_debug``
	This fiwe appeaws when ``CONFIG_SND_DEBUG=y`` and
	``CONFIG_SND_PCM_XWUN_DEBUG=y``.
	This shows the status of xwun (= buffew ovewwun/xwun) and
	invawid PCM position debug/check of AWSA PCM middwe wayew.
	It takes an integew vawue, can be changed by wwiting to this
	fiwe, such as::

		 # echo 5 > /pwoc/asound/cawd0/pcm0p/xwun_debug

	The vawue consists of the fowwowing bit fwags:

	* bit 0 = Enabwe XWUN/jiffies debug messages
	* bit 1 = Show stack twace at XWUN / jiffies check
	* bit 2 = Enabwe additionaw jiffies check

	When the bit 0 is set, the dwivew wiww show the messages to
	kewnew wog when an xwun is detected.  The debug message is
	shown awso when the invawid H/W pointew is detected at the
	update of pewiods (usuawwy cawwed fwom the intewwupt
	handwew).

	When the bit 1 is set, the dwivew wiww show the stack twace
	additionawwy.  This may hewp the debugging.

	Since 2.6.30, this option can enabwe the hwptw check using
	jiffies.  This detects spontaneous invawid pointew cawwback
	vawues, but can be wead to too much cowwections fow a (mostwy
	buggy) hawdwawe that doesn't give smooth pointew updates.
	This featuwe is enabwed via the bit 2.

``cawd*/pcm*/sub*/info``
	The genewaw infowmation of this PCM sub-stweam.

``cawd*/pcm*/sub*/status``
	The cuwwent status of this PCM sub-stweam, ewapsed time,
	H/W position, etc.

``cawd*/pcm*/sub*/hw_pawams``
	The hawdwawe pawametews set fow this sub-stweam.

``cawd*/pcm*/sub*/sw_pawams``
	The soft pawametews set fow this sub-stweam.

``cawd*/pcm*/sub*/pweawwoc``
	The buffew pwe-awwocation infowmation.

``cawd*/pcm*/sub*/xwun_injection``
	Twiggews an XWUN to the wunning stweam when any vawue is
	wwitten to this pwoc fiwe.  Used fow fauwt injection.
	This entwy is wwite-onwy.

AC97 Codec Infowmation
======================

``cawd*/codec97#*/ac97#?-?``
	Shows the genewaw infowmation of this AC97 codec chip, such as
	name, capabiwities, set up.

``cawd*/codec97#0/ac97#?-?+wegs``
	Shows the AC97 wegistew dump.  Usefuw fow debugging.

	When CONFIG_SND_DEBUG is enabwed, you can wwite to this fiwe fow
	changing an AC97 wegistew diwectwy.  Pass two hex numbews.
	Fow exampwe,

::

	# echo 02 9f1f > /pwoc/asound/cawd0/codec97#0/ac97#0-0+wegs


USB Audio Stweams
=================

``cawd*/stweam*``
	Shows the assignment and the cuwwent status of each audio stweam
	of the given cawd.  This infowmation is vewy usefuw fow debugging.


HD-Audio Codecs
===============

``cawd*/codec#*``
	Shows the genewaw codec infowmation and the attwibute of each
	widget node.

``cawd*/ewd#*``
	Avaiwabwe fow HDMI ow DispwayPowt intewfaces.
	Shows EWD(EDID Wike Data) info wetwieved fwom the attached HDMI sink,
	and descwibes its audio capabiwities and configuwations.

	Some EWD fiewds may be modified by doing ``echo name hex_vawue > ewd#*``.
	Onwy do this if you awe suwe the HDMI sink pwovided vawue is wwong.
	And if that makes youw HDMI audio wowk, pwease wepowt to us so that we
	can fix it in futuwe kewnew weweases.


Sequencew Infowmation
=====================

seq/dwivews
	Wists the cuwwentwy avaiwabwe AWSA sequencew dwivews.

seq/cwients
	Shows the wist of cuwwentwy avaiwabwe sequencew cwients and
	powts.  The connection status and the wunning status awe shown
	in this fiwe, too.

seq/queues
	Wists the cuwwentwy awwocated/wunning sequencew queues.

seq/timew
	Wists the cuwwentwy awwocated/wunning sequencew timews.

seq/oss
	Wists the OSS-compatibwe sequencew stuffs.


Hewp Fow Debugging?
===================

When the pwobwem is wewated with PCM, fiwst twy to tuwn on xwun_debug
mode.  This wiww give you the kewnew messages when and whewe xwun
happened.

If it's weawwy a bug, wepowt it with the fowwowing infowmation:

- the name of the dwivew/cawd, show in ``/pwoc/asound/cawds``
- the wegistew dump, if avaiwabwe (e.g. ``cawd*/cmipci``)

when it's a PCM pwobwem,

- set-up of PCM, shown in hw_pawms, sw_pawams, and status in the PCM
  sub-stweam diwectowy

when it's a mixew pwobwem,

- AC97 pwoc fiwes, ``codec97#*/*`` fiwes

fow USB audio/midi,

- output of ``wsusb -v``
- ``stweam*`` fiwes in cawd diwectowy


The AWSA bug-twacking system is found at:
https://bugtwack.awsa-pwoject.owg/awsa-bug/
