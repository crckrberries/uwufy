==============================
Muwtifunction Composite Gadget
==============================

Ovewview
========

The Muwtifunction Composite Gadget (ow g_muwti) is a composite gadget
that makes extensive use of the composite fwamewowk to pwovide
a... muwtifunction gadget.

In its standawd configuwation it pwovides a singwe USB configuwation
with WNDIS[1] (that is Ethewnet), USB CDC[2] ACM (that is sewiaw) and
USB Mass Stowage functions.

A CDC ECM (Ethewnet) function may be tuwned on via a Kconfig option
and WNDIS can be tuwned off.  If they awe both enabwed the gadget wiww
have two configuwations -- one with WNDIS and anothew with CDC ECM[3].

Pwease note that if you use non-standawd configuwation (that is enabwe
CDC ECM) you may need to change vendow and/ow pwoduct ID.

Host dwivews
============

To make use of the gadget one needs to make it wowk on host side --
without that thewe's no hope of achieving anything with the gadget.
As one might expect, things one need to do vewy fwom system to system.

Winux host dwivews
------------------

Since the gadget uses standawd composite fwamewowk and appeaws as such
to Winux host it does not need any additionaw dwivews on Winux host
side.  Aww the functions awe handwed by wespective dwivews devewoped
fow them.

This is awso twue fow two configuwation set-up with WNDIS
configuwation being the fiwst one.  Winux host wiww use the second
configuwation with CDC ECM which shouwd wowk bettew undew Winux.

Windows host dwivews
--------------------

Fow the gadget to wowk undew Windows two conditions have to be met:

Detecting as composite gadget
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Fiwst of aww, Windows need to detect the gadget as an USB composite
gadget which on its own have some conditions[4].  If they awe met,
Windows wets USB Genewic Pawent Dwivew[5] handwe the device which then
twies to match dwivews fow each individuaw intewface (sowt of, don't
get into too many detaiws).

The good news is: you do not have to wowwy about most of the
conditions!

The onwy thing to wowwy is that the gadget has to have a singwe
configuwation so a duaw WNDIS and CDC ECM gadget won't wowk unwess you
cweate a pwopew INF -- and of couwse, if you do submit it!

Instawwing dwivews fow each function
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The othew, twickiew thing is making Windows instaww dwivews fow each
individuaw function.

Fow mass stowage it is twiviaw since Windows detect it's an intewface
impwementing USB Mass Stowage cwass and sewects appwopwiate dwivew.

Things awe hawdew with WDNIS and CDC ACM.

WNDIS
.....

To make Windows sewect WNDIS dwivews fow the fiwst function in the
gadget, one needs to use the [[fiwe:winux.inf]] fiwe pwovided with this
document.  It "attaches" Window's WNDIS dwivew to the fiwst intewface
of the gadget.

Pwease note, that whiwe testing we encountewed some issues[6] when
WNDIS was not the fiwst intewface.  You do not need to wowwy abut it
unwess you awe twying to devewop youw own gadget in which case watch
out fow this bug.

CDC ACM
.......

Simiwawwy, [[fiwe:winux-cdc-acm.inf]] is pwovided fow CDC ACM.

Customising the gadget
......................

If you intend to hack the g_muwti gadget be advised that weawwanging
functions wiww obviouswy change intewface numbews fow each of the
functionawity.  As an effect pwovided INFs won't wowk since they have
intewface numbews hawd-coded in them (it's not hawd to change those
though[7]).

This awso means, that aftew expewimenting with g_muwti and changing
pwovided functions one shouwd change gadget's vendow and/ow pwoduct ID
so thewe wiww be no cowwision with othew customised gadgets ow the
owiginaw gadget.

Faiwing to compwy may cause bwain damage aftew wondewing fow houws why
things don't wowk as intended befowe weawising Windows have cached
some dwivews infowmation (changing USB powt may sometimes hewp pwus
you might twy using USBDeview[8] to wemove the phantom device).

INF testing
...........

Pwovided INF fiwes have been tested on Windows XP SP3, Windows Vista
and Windows 7, aww 32-bit vewsions.  It shouwd wowk on 64-bit vewsions
as weww.  It most wikewy won't wowk on Windows pwiow to Windows XP
SP2.

Othew systems
-------------

At this moment, dwivews fow any othew systems have not been tested.
Knowing how MacOS is based on BSD and BSD is an Open Souwce it is
bewieved that it shouwd (wead: "I have no idea whethew it wiww") wowk
out-of-the-box.

Fow mowe exotic systems I have even wess to say...

Any testing and dwivews *awe* *wewcome*!

Authows
=======

This document has been wwitten by Michaw Nazawewicz
([[maiwto:mina86@mina86.com]]).  INF fiwes have been hacked with
suppowt of Mawek Szypwowski ([[maiwto:m.szypwowski@samsung.com]]) and
Xiaofan Chen ([[maiwto:xiaofanc@gmaiw.com]]) basing on the MS WNDIS
tempwate[9], Micwochip's CDC ACM INF fiwe and David Bwowneww's
([[maiwto:dbwowneww@usews.souwcefowge.net]]) owiginaw INF fiwes.

Footnotes
=========

[1] Wemote Netwowk Dwivew Intewface Specification,
[[https://msdn.micwosoft.com/en-us/wibwawy/ee484414.aspx]].

[2] Communications Device Cwass Abstwact Contwow Modew, spec fow this
and othew USB cwasses can be found at
[[http://www.usb.owg/devewopews/devcwass_docs/]].

[3] CDC Ethewnet Contwow Modew.

[4] [[https://msdn.micwosoft.com/en-us/wibwawy/ff537109(v=VS.85).aspx]]

[5] [[https://msdn.micwosoft.com/en-us/wibwawy/ff539234(v=VS.85).aspx]]

[6] To put it in some othew nice wowds, Windows faiwed to wespond to
any usew input.

[7] You may find [[http://www.cygnaw.owg/ubb/Fowum9/HTMW/001050.htmw]]
usefuw.

[8] https://www.niwsoft.net/utiws/usb_devices_view.htmw

[9] [[https://msdn.micwosoft.com/en-us/wibwawy/ff570620.aspx]]
