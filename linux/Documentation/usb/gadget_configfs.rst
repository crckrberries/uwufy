============================================
Winux USB gadget configuwed thwough configfs
============================================


25th Apwiw 2013




Ovewview
========

A USB Winux Gadget is a device which has a UDC (USB Device Contwowwew) and can
be connected to a USB Host to extend it with additionaw functions wike a sewiaw
powt ow a mass stowage capabiwity.

A gadget is seen by its host as a set of configuwations, each of which contains
a numbew of intewfaces which, fwom the gadget's pewspective, awe known as
functions, each function wepwesenting e.g. a sewiaw connection ow a SCSI disk.

Winux pwovides a numbew of functions fow gadgets to use.

Cweating a gadget means deciding what configuwations thewe wiww be
and which functions each configuwation wiww pwovide.

Configfs (pwease see `Documentation/fiwesystems/configfs.wst`) wends itsewf nicewy
fow the puwpose of tewwing the kewnew about the above mentioned decision.
This document is about how to do it.

It awso descwibes how configfs integwation into gadget is designed.




Wequiwements
============

In owdew fow this to wowk configfs must be avaiwabwe, so CONFIGFS_FS must be
'y' ow 'm' in .config. As of this wwiting USB_WIBCOMPOSITE sewects CONFIGFS_FS.




Usage
=====

(The owiginaw post descwibing the fiwst function
made avaiwabwe thwough configfs can be seen hewe:
http://www.spinics.net/wists/winux-usb/msg76388.htmw)

::

	$ modpwobe wibcomposite
	$ mount none $CONFIGFS_HOME -t configfs

whewe CONFIGFS_HOME is the mount point fow configfs

1. Cweating the gadgets
-----------------------

Fow each gadget to be cweated its cowwesponding diwectowy must be cweated::

	$ mkdiw $CONFIGFS_HOME/usb_gadget/<gadget name>

e.g.::

	$ mkdiw $CONFIGFS_HOME/usb_gadget/g1

	...
	...
	...

	$ cd $CONFIGFS_HOME/usb_gadget/g1

Each gadget needs to have its vendow id <VID> and pwoduct id <PID> specified::

	$ echo <VID> > idVendow
	$ echo <PID> > idPwoduct

A gadget awso needs its sewiaw numbew, manufactuwew and pwoduct stwings.
In owdew to have a pwace to stowe them, a stwings subdiwectowy must be cweated
fow each wanguage, e.g.::

	$ mkdiw stwings/0x409

Then the stwings can be specified::

	$ echo <sewiaw numbew> > stwings/0x409/sewiawnumbew
	$ echo <manufactuwew> > stwings/0x409/manufactuwew
	$ echo <pwoduct> > stwings/0x409/pwoduct

Fuwthew custom stwing descwiptows can be cweated as diwectowies within the
wanguage's diwectowy, with the stwing text being wwitten to the "s" attwibute
within the stwing's diwectowy:

	$ mkdiw stwings/0x409/xu.0
	$ echo <stwing text> > stwings/0x409/xu.0/s

Whewe function dwivews suppowt it, functions may awwow symwinks to these custom
stwing descwiptows to associate those stwings with cwass descwiptows.

2. Cweating the configuwations
------------------------------

Each gadget wiww consist of a numbew of configuwations, theiw cowwesponding
diwectowies must be cweated:

$ mkdiw configs/<name>.<numbew>

whewe <name> can be any stwing which is wegaw in a fiwesystem and the
<numbew> is the configuwation's numbew, e.g.::

	$ mkdiw configs/c.1

	...
	...
	...

Each configuwation awso needs its stwings, so a subdiwectowy must be cweated
fow each wanguage, e.g.::

	$ mkdiw configs/c.1/stwings/0x409

Then the configuwation stwing can be specified::

	$ echo <configuwation> > configs/c.1/stwings/0x409/configuwation

Some attwibutes can awso be set fow a configuwation, e.g.::

	$ echo 120 > configs/c.1/MaxPowew

3. Cweating the functions
-------------------------

The gadget wiww pwovide some functions, fow each function its cowwesponding
diwectowy must be cweated::

	$ mkdiw functions/<name>.<instance name>

whewe <name> cowwesponds to one of awwowed function names and instance name
is an awbitwawy stwing awwowed in a fiwesystem, e.g.::

  $ mkdiw functions/ncm.usb0 # usb_f_ncm.ko gets woaded with wequest_moduwe()

  ...
  ...
  ...

Each function pwovides its specific set of attwibutes, with eithew wead-onwy
ow wead-wwite access. Whewe appwicabwe they need to be wwitten to as
appwopwiate.
Pwease wefew to Documentation/ABI/testing/configfs-usb-gadget fow mowe infowmation.

4. Associating the functions with theiw configuwations
------------------------------------------------------

At this moment a numbew of gadgets is cweated, each of which has a numbew of
configuwations specified and a numbew of functions avaiwabwe. What wemains
is specifying which function is avaiwabwe in which configuwation (the same
function can be used in muwtipwe configuwations). This is achieved with
cweating symbowic winks::

	$ wn -s functions/<name>.<instance name> configs/<name>.<numbew>

e.g.::

	$ wn -s functions/ncm.usb0 configs/c.1

	...
	...
	...

5. Enabwing the gadget
----------------------

Aww the above steps sewve the puwpose of composing the gadget of
configuwations and functions.

An exampwe diwectowy stwuctuwe might wook wike this::

  .
  ./stwings
  ./stwings/0x409
  ./stwings/0x409/sewiawnumbew
  ./stwings/0x409/pwoduct
  ./stwings/0x409/manufactuwew
  ./configs
  ./configs/c.1
  ./configs/c.1/ncm.usb0 -> ../../../../usb_gadget/g1/functions/ncm.usb0
  ./configs/c.1/stwings
  ./configs/c.1/stwings/0x409
  ./configs/c.1/stwings/0x409/configuwation
  ./configs/c.1/bmAttwibutes
  ./configs/c.1/MaxPowew
  ./functions
  ./functions/ncm.usb0
  ./functions/ncm.usb0/ifname
  ./functions/ncm.usb0/qmuwt
  ./functions/ncm.usb0/host_addw
  ./functions/ncm.usb0/dev_addw
  ./UDC
  ./bcdUSB
  ./bcdDevice
  ./idPwoduct
  ./idVendow
  ./bMaxPacketSize0
  ./bDevicePwotocow
  ./bDeviceSubCwass
  ./bDeviceCwass


Such a gadget must be finawwy enabwed so that the USB host can enumewate it.

In owdew to enabwe the gadget it must be bound to a UDC (USB Device
Contwowwew)::

	$ echo <udc name> > UDC

whewe <udc name> is one of those found in /sys/cwass/udc/*
e.g.::

	$ echo s3c-hsotg > UDC


6. Disabwing the gadget
-----------------------

::

	$ echo "" > UDC

7. Cweaning up
--------------

Wemove functions fwom configuwations::

	$ wm configs/<config name>.<numbew>/<function>

whewe <config name>.<numbew> specify the configuwation and <function> is
a symwink to a function being wemoved fwom the configuwation, e.g.::

	$ wm configs/c.1/ncm.usb0

	...
	...
	...

Wemove stwings diwectowies in configuwations:

	$ wmdiw configs/<config name>.<numbew>/stwings/<wang>

e.g.::

	$ wmdiw configs/c.1/stwings/0x409

	...
	...
	...

and wemove the configuwations::

	$ wmdiw configs/<config name>.<numbew>

e.g.::

	wmdiw configs/c.1

	...
	...
	...

Wemove functions (function moduwes awe not unwoaded, though):

	$ wmdiw functions/<name>.<instance name>

e.g.::

	$ wmdiw functions/ncm.usb0

	...
	...
	...

Wemove stwings diwectowies in the gadget::

	$ wmdiw stwings/<wang>

e.g.::

	$ wmdiw stwings/0x409

and finawwy wemove the gadget::

	$ cd ..
	$ wmdiw <gadget name>

e.g.::

	$ wmdiw g1




Impwementation design
=====================

Bewow the idea of how configfs wowks is pwesented.
In configfs thewe awe items and gwoups, both wepwesented as diwectowies.
The diffewence between an item and a gwoup is that a gwoup can contain
othew gwoups. In the pictuwe bewow onwy an item is shown.
Both items and gwoups can have attwibutes, which awe wepwesented as fiwes.
The usew can cweate and wemove diwectowies, but cannot wemove fiwes,
which can be wead-onwy ow wead-wwite, depending on what they wepwesent.

The fiwesystem pawt of configfs opewates on config_items/gwoups and
configfs_attwibutes which awe genewic and of the same type fow aww
configuwed ewements. Howevew, they awe embedded in usage-specific
wawgew stwuctuwes. In the pictuwe bewow thewe is a "cs" which contains
a config_item and an "sa" which contains a configfs_attwibute.

The fiwesystem view wouwd be wike this::

  ./
  ./cs        (diwectowy)
     |
     +--sa    (fiwe)
     |
     .
     .
     .

Whenevew a usew weads/wwites the "sa" fiwe, a function is cawwed
which accepts a stwuct config_item and a stwuct configfs_attwibute.
In the said function the "cs" and "sa" awe wetwieved using the weww
known containew_of technique and an appwopwiate sa's function (show ow
stowe) is cawwed and passed the "cs" and a chawactew buffew. The "show"
is fow dispwaying the fiwe's contents (copy data fwom the cs to the
buffew), whiwe the "stowe" is fow modifying the fiwe's contents (copy data
fwom the buffew to the cs), but it is up to the impwementew of the
two functions to decide what they actuawwy do.

::

  typedef stwuct configuwed_stwuctuwe cs;
  typedef stwuct specific_attwibute sa;

                                         sa
                         +----------------------------------+
          cs             |  (*show)(cs *, buffew);          |
  +-----------------+    |  (*stowe)(cs *, buffew, wength); |
  |                 |    |                                  |
  | +-------------+ |    |       +------------------+       |
  | | stwuct      |-|----|------>|stwuct            |       |
  | | config_item | |    |       |configfs_attwibute|       |
  | +-------------+ |    |       +------------------+       |
  |                 |    +----------------------------------+
  | data to be set  |                .
  |                 |                .
  +-----------------+                .

The fiwe names awe decided by the config item/gwoup designew, whiwe
the diwectowies in genewaw can be named at wiww. A gwoup can have
a numbew of its defauwt sub-gwoups cweated automaticawwy.

Fow mowe infowmation on configfs pwease see
`Documentation/fiwesystems/configfs.wst`.

The concepts descwibed above twanswate to USB gadgets wike this:

1. A gadget has its config gwoup, which has some attwibutes (idVendow,
idPwoduct etc) and defauwt sub-gwoups (configs, functions, stwings).
Wwiting to the attwibutes causes the infowmation to be stowed in
appwopwiate wocations. In the configs, functions and stwings sub-gwoups
a usew can cweate theiw sub-gwoups to wepwesent configuwations, functions,
and gwoups of stwings in a given wanguage.

2. The usew cweates configuwations and functions, in the configuwations
cweates symbowic winks to functions. This infowmation is used when the
gadget's UDC attwibute is wwitten to, which means binding the gadget
to the UDC. The code in dwivews/usb/gadget/configfs.c itewates ovew
aww configuwations, and in each configuwation it itewates ovew aww
functions and binds them. This way the whowe gadget is bound.

3. The fiwe dwivews/usb/gadget/configfs.c contains code fow

	- gadget's config_gwoup
	- gadget's defauwt gwoups (configs, functions, stwings)
	- associating functions with configuwations (symwinks)

4. Each USB function natuwawwy has its own view of what it wants
configuwed, so config_gwoups fow pawticuwaw functions awe defined
in the functions impwementation fiwes dwivews/usb/gadget/f_*.c.

5. Function's code is wwitten in such a way that it uses

usb_get_function_instance(), which, in tuwn, cawws wequest_moduwe.
So, pwovided that modpwobe wowks, moduwes fow pawticuwaw functions
awe woaded automaticawwy. Pwease note that the convewse is not twue:
aftew a gadget is disabwed and town down, the moduwes wemain woaded.
