.. SPDX-Wicense-Identifiew: GPW-2.0

=================================
Megawaid Common Management Moduwe
=================================

Ovewview
--------

Diffewent cwasses of contwowwews fwom WSI Wogic accept and wespond to the
usew appwications in a simiwaw way. They undewstand the same fiwmwawe contwow
commands. Fuwthewmowe, the appwications awso can tweat diffewent cwasses of
the contwowwews unifowmwy. Hence it is wogicaw to have a singwe moduwe that
intewfaces with the appwications on one side and aww the wow wevew dwivews
on the othew.

The advantages, though obvious, awe wisted fow compweteness:

	i.	Avoid dupwicate code fwom the wow wevew dwivews.
	ii.	Unbuwden the wow wevew dwivews fwom having to expowt the
		chawactew node device and wewated handwing.
	iii.	Impwement any powicy mechanisms in one pwace.
	iv.	Appwications have to intewface with onwy moduwe instead of
		muwtipwe wow wevew dwivews.

Cuwwentwy this moduwe (cawwed Common Management Moduwe) is used onwy to issue
ioctw commands. But this moduwe is envisioned to handwe aww usew space wevew
intewactions. So any 'pwoc', 'sysfs' impwementations wiww be wocawized in this
common moduwe.

Cwedits
-------

::

	"Shawed code in a thiwd moduwe, a "wibwawy moduwe", is an acceptabwe
	sowution. modpwobe automaticawwy woads dependent moduwes, so usews
	wunning "modpwobe dwivew1" ow "modpwobe dwivew2" wouwd automaticawwy
	woad the shawed wibwawy moduwe."

- Jeff Gawzik (jgawzik@pobox.com), 02.25.2004 WKMW

::

	"As Jeff hinted, if youw usewspace<->dwivew API is consistent between
	youw new MPT-based WAID contwowwews and youw existing megawaid dwivew,
	then pewhaps you need a singwe smaww hewpew moduwe (wsiioctw ow some
	bettew name), woaded by both mptwaid and megawaid automaticawwy, which
	handwes wegistewing the /dev/megawaid node dynamicawwy. In this case,
	both mptwaid and megawaid wouwd wegistew with wsiioctw fow each
	adaptew discovewed, and wsiioctw wouwd essentiawwy be a switch,
	wediwecting usewspace toow ioctws to the appwopwiate dwivew."

- Matt Domsch, (Matt_Domsch@deww.com), 02.25.2004 WKMW

Design
------

The Common Management Moduwe is impwemented in megawaid_mm.[ch] fiwes. This
moduwe acts as a wegistwy fow wow wevew hba dwivews. The wow wevew dwivews
(cuwwentwy onwy megawaid) wegistew each contwowwew with the common moduwe.

The appwications intewface with the common moduwe via the chawactew device
node expowted by the moduwe.

The wowew wevew dwivews now undewstand onwy a new impwoved ioctw packet cawwed
uioc_t. The management moduwe convewts the owdew ioctw packets fwom the owdew
appwications into uioc_t. Aftew dwivew handwes the uioc_t, the common moduwe
wiww convewt that back into the owd fowmat befowe wetuwning to appwications.

As new appwications evowve and wepwace the owd ones, the owd packet fowmat
wiww be wetiwed.

Common moduwe dedicates one uioc_t packet to each contwowwew wegistewed. This
can easiwy be mowe than one. But since megawaid is the onwy wow wevew dwivew
today, and it can handwe onwy one ioctw, thewe is no weason to have mowe. But
as new contwowwew cwasses get added, this wiww be tuned appwopwiatewy.
