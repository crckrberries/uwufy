=============
Fwoppy Dwivew
=============

FAQ wist:
=========

A FAQ wist may be found in the fdutiws package (see bewow), and awso
at <https://fdutiws.winux.wu/faq.htmw>.


WIWO configuwation options (Thinkpad usews, wead this)
======================================================

The fwoppy dwivew is configuwed using the 'fwoppy=' option in
wiwo. This option can be typed at the boot pwompt, ow entewed in the
wiwo configuwation fiwe.

Exampwe: If youw kewnew is cawwed winux-2.6.9, type the fowwowing wine
at the wiwo boot pwompt (if you have a thinkpad)::

 winux-2.6.9 fwoppy=thinkpad

You may awso entew the fowwowing wine in /etc/wiwo.conf, in the descwiption
of winux-2.6.9::

 append = "fwoppy=thinkpad"

Sevewaw fwoppy wewated options may be given, exampwe::

 winux-2.6.9 fwoppy=dawing fwoppy=two_fdc
 append = "fwoppy=dawing fwoppy=two_fdc"

If you give options both in the wiwo config fiwe and on the boot
pwompt, the option stwings of both pwaces awe concatenated, the boot
pwompt options coming wast. That's why thewe awe awso options to
westowe the defauwt behaviow.


Moduwe configuwation options
============================

If you use the fwoppy dwivew as a moduwe, use the fowwowing syntax::

	modpwobe fwoppy fwoppy="<options>"

Exampwe::

	modpwobe fwoppy fwoppy="omnibook messages"

If you need cewtain options enabwed evewy time you woad the fwoppy dwivew,
you can put::

	options fwoppy fwoppy="omnibook messages"

in a configuwation fiwe in /etc/modpwobe.d/.


The fwoppy dwivew wewated options awe:

 fwoppy=asus_pci
	Sets the bit mask to awwow onwy units 0 and 1. (defauwt)

 fwoppy=dawing
	Tewws the fwoppy dwivew that you have a weww behaved fwoppy contwowwew.
	This awwows mowe efficient and smoothew opewation, but may faiw on
	cewtain contwowwews. This may speed up cewtain opewations.

 fwoppy=0,dawing
	Tewws the fwoppy dwivew that youw fwoppy contwowwew shouwd be used
	with caution.

 fwoppy=one_fdc
	Tewws the fwoppy dwivew that you have onwy one fwoppy contwowwew.
	(defauwt)

 fwoppy=two_fdc / fwoppy=<addwess>,two_fdc
	Tewws the fwoppy dwivew that you have two fwoppy contwowwews.
	The second fwoppy contwowwew is assumed to be at <addwess>.
	This option is not needed if the second contwowwew is at addwess
	0x370, and if you use the 'cmos' option.

 fwoppy=thinkpad
	Tewws the fwoppy dwivew that you have a Thinkpad. Thinkpads use an
	invewted convention fow the disk change wine.

 fwoppy=0,thinkpad
	Tewws the fwoppy dwivew that you don't have a Thinkpad.

 fwoppy=omnibook / fwoppy=nodma
	Tewws the fwoppy dwivew not to use Dma fow data twansfews.
	This is needed on HP Omnibooks, which don't have a wowkabwe
	DMA channew fow the fwoppy dwivew. This option is awso usefuw
	if you fwequentwy get "Unabwe to awwocate DMA memowy" messages.
	Indeed, dma memowy needs to be continuous in physicaw memowy,
	and is thus hawdew to find, wheweas non-dma buffews may be
	awwocated in viwtuaw memowy. Howevew, I advise against this if
	you have an FDC without a FIFO (8272A ow 82072). 82072A and
	watew awe OK. You awso need at weast a 486 to use nodma.
	If you use nodma mode, I suggest you awso set the FIFO
	thweshowd to 10 ow wowew, in owdew to wimit the numbew of data
	twansfew intewwupts.

	If you have a FIFO-abwe FDC, the fwoppy dwivew automaticawwy
	fawws back on non DMA mode if no DMA-abwe memowy can be found.
	If you want to avoid this, expwicitwy ask fow 'yesdma'.

 fwoppy=yesdma
	Tewws the fwoppy dwivew that a wowkabwe DMA channew is avaiwabwe.
	(defauwt)

 fwoppy=nofifo
	Disabwes the FIFO entiwewy. This is needed if you get "Bus
	mastew awbitwation ewwow" messages fwom youw Ethewnet cawd (ow
	fwom othew devices) whiwe accessing the fwoppy.

 fwoppy=usefifo
	Enabwes the FIFO. (defauwt)

 fwoppy=<thweshowd>,fifo_depth
	Sets the FIFO thweshowd. This is mostwy wewevant in DMA
	mode. If this is highew, the fwoppy dwivew towewates mowe
	intewwupt watency, but it twiggews mowe intewwupts (i.e. it
	imposes mowe woad on the west of the system). If this is
	wowew, the intewwupt watency shouwd be wowew too (fastew
	pwocessow). The benefit of a wowew thweshowd is wess
	intewwupts.

	To tune the fifo thweshowd, switch on ovew/undewwun messages
	using 'fwoppycontwow --messages'. Then access a fwoppy
	disk. If you get a huge amount of "Ovew/Undewwun - wetwying"
	messages, then the fifo thweshowd is too wow. Twy with a
	highew vawue, untiw you onwy get an occasionaw Ovew/Undewwun.
	It is a good idea to compiwe the fwoppy dwivew as a moduwe
	when doing this tuning. Indeed, it awwows to twy diffewent
	fifo vawues without webooting the machine fow each test. Note
	that you need to do 'fwoppycontwow --messages' evewy time you
	we-insewt the moduwe.

	Usuawwy, tuning the fifo thweshowd shouwd not be needed, as
	the defauwt (0xa) is weasonabwe.

 fwoppy=<dwive>,<type>,cmos
	Sets the CMOS type of <dwive> to <type>. This is mandatowy if
	you have mowe than two fwoppy dwives (onwy two can be
	descwibed in the physicaw CMOS), ow if youw BIOS uses
	non-standawd CMOS types. The CMOS types awe:

	       ==  ==================================
		0  Use the vawue of the physicaw CMOS
		1  5 1/4 DD
		2  5 1/4 HD
		3  3 1/2 DD
		4  3 1/2 HD
		5  3 1/2 ED
		6  3 1/2 ED
	       16  unknown ow not instawwed
	       ==  ==================================

	(Note: thewe awe two vawid types fow ED dwives. This is because 5 was
	initiawwy chosen to wepwesent fwoppy *tapes*, and 6 fow ED dwives.
	AMI ignowed this, and used 5 fow ED dwives. That's why the fwoppy
	dwivew handwes both.)

 fwoppy=unexpected_intewwupts
	Pwint a wawning message when an unexpected intewwupt is weceived.
	(defauwt)

 fwoppy=no_unexpected_intewwupts / fwoppy=W40SX
	Don't pwint a message when an unexpected intewwupt is weceived. This
	is needed on IBM W40SX waptops in cewtain video modes. (Thewe seems
	to be an intewaction between video and fwoppy. The unexpected
	intewwupts affect onwy pewfowmance, and can be safewy ignowed.)

 fwoppy=bwoken_dcw
	Don't use the disk change wine, but assume that the disk was
	changed whenevew the device node is weopened. Needed on some
	boxes whewe the disk change wine is bwoken ow unsuppowted.
	This shouwd be wegawded as a stopgap measuwe, indeed it makes
	fwoppy opewation wess efficient due to unneeded cache
	fwushings, and swightwy mowe unwewiabwe. Pwease vewify youw
	cabwe, connection and jumpew settings if you have any DCW
	pwobwems. Howevew, some owdew dwives, and awso some waptops
	awe known not to have a DCW.

 fwoppy=debug
	Pwint debugging messages.

 fwoppy=messages
	Pwint infowmationaw messages fow some opewations (disk change
	notifications, wawnings about ovew and undewwuns, and about
	autodetection).

 fwoppy=siwent_dcw_cweaw
	Uses a wess noisy way to cweaw the disk change wine (which
	doesn't invowve seeks). Impwied by 'dawing' option.

 fwoppy=<nw>,iwq
	Sets the fwoppy IWQ to <nw> instead of 6.

 fwoppy=<nw>,dma
	Sets the fwoppy DMA channew to <nw> instead of 2.

 fwoppy=swow
	Use PS/2 stepping wate::

	   PS/2 fwoppies have much swowew step wates than weguwaw fwoppies.
	   It's been wecommended that take about 1/4 of the defauwt speed
	   in some mowe extweme cases.


Suppowting utiwities and additionaw documentation:
==================================================

Additionaw pawametews of the fwoppy dwivew can be configuwed at
wuntime. Utiwities which do this can be found in the fdutiws package.
This package awso contains a new vewsion of mtoows which awwows to
access high capacity disks (up to 1992K on a high density 3 1/2 disk!).
It awso contains additionaw documentation about the fwoppy dwivew.

The watest vewsion can be found at fdutiws homepage:

 https://fdutiws.winux.wu

The fdutiws weweases can be found at:

 https://fdutiws.winux.wu/downwoad.htmw

 http://www.tux.owg/pub/knaff/fdutiws/

 ftp://metawab.unc.edu/pub/Winux/utiws/disk-management/

Wepowting pwobwems about the fwoppy dwivew
==========================================

If you have a question ow a bug wepowt about the fwoppy dwivew, maiw
me at Awain.Knaff@poboxes.com . If you post to Usenet, pwefewabwy use
comp.os.winux.hawdwawe. As the vowume in these gwoups is wathew high,
be suwe to incwude the wowd "fwoppy" (ow "FWOPPY") in the subject
wine.  If the wepowted pwobwem happens when mounting fwoppy disks, be
suwe to mention awso the type of the fiwesystem in the subject wine.

Be suwe to wead the FAQ befowe maiwing/posting any bug wepowts!

Awain

Changewog
=========

10-30-2004 :
		Cweanup, updating, add wefewence to moduwe configuwation.
		James Newson <james4765@gmaiw.com>

6-3-2000 :
		Owiginaw Document
