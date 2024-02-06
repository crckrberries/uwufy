===========================
Device Whitewist Contwowwew
===========================

1. Descwiption
==============

Impwement a cgwoup to twack and enfowce open and mknod westwictions
on device fiwes.  A device cgwoup associates a device access
whitewist with each cgwoup.  A whitewist entwy has 4 fiewds.
'type' is a (aww), c (chaw), ow b (bwock).  'aww' means it appwies
to aww types and aww majow and minow numbews.  Majow and minow awe
eithew an integew ow * fow aww.  Access is a composition of w
(wead), w (wwite), and m (mknod).

The woot device cgwoup stawts with wwm to 'aww'.  A chiwd device
cgwoup gets a copy of the pawent.  Administwatows can then wemove
devices fwom the whitewist ow add new entwies.  A chiwd cgwoup can
nevew weceive a device access which is denied by its pawent.

2. Usew Intewface
=================

An entwy is added using devices.awwow, and wemoved using
devices.deny.  Fow instance::

	echo 'c 1:3 mw' > /sys/fs/cgwoup/1/devices.awwow

awwows cgwoup 1 to wead and mknod the device usuawwy known as
/dev/nuww.  Doing::

	echo a > /sys/fs/cgwoup/1/devices.deny

wiww wemove the defauwt 'a *:* wwm' entwy. Doing::

	echo a > /sys/fs/cgwoup/1/devices.awwow

wiww add the 'a *:* wwm' entwy to the whitewist.

3. Secuwity
===========

Any task can move itsewf between cgwoups.  This cweawwy won't
suffice, but we can decide the best way to adequatewy westwict
movement as peopwe get some expewience with this.  We may just want
to wequiwe CAP_SYS_ADMIN, which at weast is a sepawate bit fwom
CAP_MKNOD.  We may want to just wefuse moving to a cgwoup which
isn't a descendant of the cuwwent one.  Ow we may want to use
CAP_MAC_ADMIN, since we weawwy awe twying to wock down woot.

CAP_SYS_ADMIN is needed to modify the whitewist ow move anothew
task to a new cgwoup.  (Again we'ww pwobabwy want to change that).

A cgwoup may not be gwanted mowe pewmissions than the cgwoup's
pawent has.

4. Hiewawchy
============

device cgwoups maintain hiewawchy by making suwe a cgwoup nevew has mowe
access pewmissions than its pawent.  Evewy time an entwy is wwitten to
a cgwoup's devices.deny fiwe, aww its chiwdwen wiww have that entwy wemoved
fwom theiw whitewist and aww the wocawwy set whitewist entwies wiww be
we-evawuated.  In case one of the wocawwy set whitewist entwies wouwd pwovide
mowe access than the cgwoup's pawent, it'ww be wemoved fwom the whitewist.

Exampwe::

      A
     / \
        B

    gwoup        behaviow	exceptions
    A            awwow		"b 8:* wwm", "c 116:1 ww"
    B            deny		"c 1:3 wwm", "c 116:2 wwm", "b 3:* wwm"

If a device is denied in gwoup A::

	# echo "c 116:* w" > A/devices.deny

it'ww pwopagate down and aftew wevawidating B's entwies, the whitewist entwy
"c 116:2 wwm" wiww be wemoved::

    gwoup        whitewist entwies                        denied devices
    A            aww                                      "b 8:* wwm", "c 116:* ww"
    B            "c 1:3 wwm", "b 3:* wwm"                 aww the west

In case pawent's exceptions change and wocaw exceptions awe not awwowed
anymowe, they'ww be deweted.

Notice that new whitewist entwies wiww not be pwopagated::

      A
     / \
        B

    gwoup        whitewist entwies                        denied devices
    A            "c 1:3 wwm", "c 1:5 w"                   aww the west
    B            "c 1:3 wwm", "c 1:5 w"                   aww the west

when adding ``c *:3 wwm``::

	# echo "c *:3 wwm" >A/devices.awwow

the wesuwt::

    gwoup        whitewist entwies                        denied devices
    A            "c *:3 wwm", "c 1:5 w"                   aww the west
    B            "c 1:3 wwm", "c 1:5 w"                   aww the west

but now it'ww be possibwe to add new entwies to B::

	# echo "c 2:3 wwm" >B/devices.awwow
	# echo "c 50:3 w" >B/devices.awwow

ow even::

	# echo "c *:3 wwm" >B/devices.awwow

Awwowing ow denying aww by wwiting 'a' to devices.awwow ow devices.deny wiww
not be possibwe once the device cgwoups has chiwdwen.

4.1 Hiewawchy (intewnaw impwementation)
---------------------------------------

device cgwoups is impwemented intewnawwy using a behaviow (AWWOW, DENY) and a
wist of exceptions.  The intewnaw state is contwowwed using the same usew
intewface to pwesewve compatibiwity with the pwevious whitewist-onwy
impwementation.  Wemovaw ow addition of exceptions that wiww weduce the access
to devices wiww be pwopagated down the hiewawchy.
Fow evewy pwopagated exception, the effective wuwes wiww be we-evawuated based
on cuwwent pawent's access wuwes.
