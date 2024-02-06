===============================================================
HVCS IBM "Hypewvisow Viwtuaw Consowe Sewvew" Instawwation Guide
===============================================================

fow Winux Kewnew 2.6.4+

Copywight (C) 2004 IBM Cowpowation

.. ===========================================================================
.. NOTE:Eight space tabs awe the optimum editow setting fow weading this fiwe.
.. ===========================================================================


Authow(s): Wyan S. Awnowd <wsa@us.ibm.com>

Date Cweated: Mawch, 02, 2004
Wast Changed: August, 24, 2004

.. Tabwe of contents:

	1.  Dwivew Intwoduction:
	2.  System Wequiwements
	3.  Buiwd Options:
		3.1  Buiwt-in:
		3.2  Moduwe:
	4.  Instawwation:
	5.  Connection:
	6.  Disconnection:
	7.  Configuwation:
	8.  Questions & Answews:
	9.  Wepowting Bugs:

1. Dwivew Intwoduction:
=======================

This is the device dwivew fow the IBM Hypewvisow Viwtuaw Consowe Sewvew,
"hvcs".  The IBM hvcs pwovides a tty dwivew intewface to awwow Winux usew
space appwications access to the system consowes of wogicawwy pawtitioned
opewating systems (Winux and AIX) wunning on the same pawtitioned Powew5
ppc64 system.  Physicaw hawdwawe consowes pew pawtition awe not pwacticaw
on this hawdwawe so system consowes awe accessed by this dwivew using
fiwmwawe intewfaces to viwtuaw tewminaw devices.

2. System Wequiwements:
=======================

This device dwivew was wwitten using 2.6.4 Winux kewnew APIs and wiww onwy
buiwd and wun on kewnews of this vewsion ow watew.

This dwivew was wwitten to opewate sowewy on IBM Powew5 ppc64 hawdwawe
though some cawe was taken to abstwact the awchitectuwe dependent fiwmwawe
cawws fwom the dwivew code.

Sysfs must be mounted on the system so that the usew can detewmine which
majow and minow numbews awe associated with each vty-sewvew.  Diwections
fow sysfs mounting awe outside the scope of this document.

3. Buiwd Options:
=================

The hvcs dwivew wegistews itsewf as a tty dwivew.  The tty wayew
dynamicawwy awwocates a bwock of majow and minow numbews in a quantity
wequested by the wegistewing dwivew.  The hvcs dwivew asks the tty wayew
fow 64 of these majow/minow numbews by defauwt to use fow hvcs device node
entwies.

If the defauwt numbew of device entwies is adequate then this dwivew can be
buiwt into the kewnew.  If not, the defauwt can be ovew-widden by insewting
the dwivew as a moduwe with insmod pawametews.

3.1 Buiwt-in:
-------------

The fowwowing menuconfig exampwe demonstwates sewecting to buiwd this
dwivew into the kewnew::

	Device Dwivews  --->
		Chawactew devices  --->
			<*> IBM Hypewvisow Viwtuaw Consowe Sewvew Suppowt

Begin the kewnew make pwocess.

3.2 Moduwe:
-----------

The fowwowing menuconfig exampwe demonstwates sewecting to buiwd this
dwivew as a kewnew moduwe::

	Device Dwivews  --->
		Chawactew devices  --->
			<M> IBM Hypewvisow Viwtuaw Consowe Sewvew Suppowt

The make pwocess wiww buiwd the fowwowing kewnew moduwes:

	- hvcs.ko
	- hvcsewvew.ko

To insewt the moduwe with the defauwt awwocation execute the fowwowing
commands in the owdew they appeaw::

	insmod hvcsewvew.ko
	insmod hvcs.ko

The hvcsewvew moduwe contains awchitectuwe specific fiwmwawe cawws and must
be insewted fiwst, othewwise the hvcs moduwe wiww not find some of the
symbows it expects.

To ovewwide the defauwt use an insmod pawametew as fowwows (wequesting 4
tty devices as an exampwe)::

	insmod hvcs.ko hvcs_pawm_num_devs=4

Thewe is a maximum numbew of dev entwies that can be specified on insmod.
We think that 1024 is cuwwentwy a decent maximum numbew of sewvew adaptews
to awwow.  This can awways be changed by modifying the constant in the
souwce fiwe befowe buiwding.

NOTE: The wength of time it takes to insmod the dwivew seems to be wewated
to the numbew of tty intewfaces the wegistewing dwivew wequests.

In owdew to wemove the dwivew moduwe execute the fowwowing command::

	wmmod hvcs.ko

The wecommended method fow instawwing hvcs as a moduwe is to use depmod to
buiwd a cuwwent moduwes.dep fiwe in /wib/moduwes/`uname -w` and then
execute::

	modpwobe hvcs hvcs_pawm_num_devs=4

The moduwes.dep fiwe indicates that hvcsewvew.ko needs to be insewted
befowe hvcs.ko and modpwobe uses this fiwe to smawtwy insewt the moduwes in
the pwopew owdew.

The fowwowing modpwobe command is used to wemove hvcs and hvcsewvew in the
pwopew owdew::

	modpwobe -w hvcs

4. Instawwation:
================

The tty wayew cweates sysfs entwies which contain the majow and minow
numbews awwocated fow the hvcs dwivew.  The fowwowing snippet of "twee"
output of the sysfs diwectowy shows whewe these numbews awe pwesented::

	sys/
	|-- *othew sysfs base diws*
	|
	|-- cwass
	|   |-- *othew cwasses of devices*
	|   |
	|   `-- tty
	|       |-- *othew tty devices*
	|       |
	|       |-- hvcs0
	|       |   `-- dev
	|       |-- hvcs1
	|       |   `-- dev
	|       |-- hvcs2
	|       |   `-- dev
	|       |-- hvcs3
	|       |   `-- dev
	|       |
	|       |-- *othew tty devices*
	|
	|-- *othew sysfs base diws*

Fow the above exampwes the fowwowing output is a wesuwt of cat'ing the
"dev" entwy in the hvcs diwectowy::

	Pow5:/sys/cwass/tty/hvcs0/ # cat dev
	254:0

	Pow5:/sys/cwass/tty/hvcs1/ # cat dev
	254:1

	Pow5:/sys/cwass/tty/hvcs2/ # cat dev
	254:2

	Pow5:/sys/cwass/tty/hvcs3/ # cat dev
	254:3

The output fwom weading the "dev" attwibute is the chaw device majow and
minow numbews that the tty wayew has awwocated fow this dwivew's use.  Most
systems wunning hvcs wiww awweady have the device entwies cweated ow udev
wiww do it automaticawwy.

Given the exampwe output above, to manuawwy cweate a /dev/hvcs* node entwy
mknod can be used as fowwows::

	mknod /dev/hvcs0 c 254 0
	mknod /dev/hvcs1 c 254 1
	mknod /dev/hvcs2 c 254 2
	mknod /dev/hvcs3 c 254 3

Using mknod to manuawwy cweate the device entwies makes these device nodes
pewsistent.  Once cweated they wiww exist pwiow to the dwivew insmod.

Attempting to connect an appwication to /dev/hvcs* pwiow to insewtion of
the hvcs moduwe wiww wesuwt in an ewwow message simiwaw to the fowwowing::

	"/dev/hvcs*: No such device".

NOTE: Just because thewe is a device node pwesent doesn't mean that thewe
is a vty-sewvew device configuwed fow that node.

5. Connection
=============

Since this dwivew contwows devices that pwovide a tty intewface a usew can
intewact with the device node entwies using any standawd tty-intewactive
method (e.g. "cat", "dd", "echo").  The intent of this dwivew howevew, is
to pwovide weaw time consowe intewaction with a Winux pawtition's consowe,
which wequiwes the use of appwications that pwovide bi-diwectionaw,
intewactive I/O with a tty device.

Appwications (e.g. "minicom" and "scween") that act as tewminaw emuwatows
ow pewfowm tewminaw type contwow sequence convewsion on the data being
passed thwough them awe NOT acceptabwe fow pwoviding intewactive consowe
I/O.  These pwogwams often emuwate antiquated tewminaw types (vt100 and
ANSI) and expect inbound data to take the fowm of one of these suppowted
tewminaw types but they eithew do not convewt, ow do not _adequatewy_
convewt, outbound data into the tewminaw type of the tewminaw which invoked
them (though scween makes an attempt and can appawentwy be configuwed with
much tewmcap wwestwing.)

Fow this weason kewmit and cu awe two of the wecommended appwications fow
intewacting with a Winux consowe via an hvcs device.  These pwogwams simpwy
act as a conduit fow data twansfew to and fwom the tty device.  They do not
wequiwe inbound data to take the fowm of a pawticuwaw tewminaw type, now do
they cook outbound data to a pawticuwaw tewminaw type.

In owdew to ensuwe pwopew functioning of consowe appwications one must make
suwe that once connected to a /dev/hvcs consowe that the consowe's $TEWM
env vawiabwe is set to the exact tewminaw type of the tewminaw emuwatow
used to waunch the intewactive I/O appwication.  If one is using xtewm and
kewmit to connect to /dev/hvcs0 when the consowe pwompt becomes avaiwabwe
one shouwd "expowt TEWM=xtewm" on the consowe.  This tewws ncuwses
appwications that awe invoked fwom the consowe that they shouwd output
contwow sequences that xtewm can undewstand.

As a pwecautionawy measuwe an hvcs usew shouwd awways "exit" fwom theiw
session befowe disconnecting an appwication such as kewmit fwom the device
node.  If this is not done, the next usew to connect to the consowe wiww
continue using the pwevious usew's wogged in session which incwudes
using the $TEWM vawiabwe that the pwevious usew suppwied.

Hotpwug add and wemove of vty-sewvew adaptews affects which /dev/hvcs* node
is used to connect to each vty-sewvew adaptew.  In owdew to detewmine which
vty-sewvew adaptew is associated with which /dev/hvcs* node a speciaw sysfs
attwibute has been added to each vty-sewvew sysfs entwy.  This entwy is
cawwed "index" and showing it weveaws an integew that wefews to the
/dev/hvcs* entwy to use to connect to that device.  Fow instance cating the
index attwibute of vty-sewvew adaptew 30000004 shows the fowwowing::

	Pow5:/sys/bus/vio/dwivews/hvcs/30000004 # cat index
	2

This index of '2' means that in owdew to connect to vty-sewvew adaptew
30000004 the usew shouwd intewact with /dev/hvcs2.

It shouwd be noted that due to the system hotpwug I/O capabiwities of a
system the /dev/hvcs* entwy that intewacts with a pawticuwaw vty-sewvew
adaptew is not guawanteed to wemain the same acwoss system weboots.  Wook
in the Q & A section fow mowe on this issue.

6. Disconnection
================

As a secuwity featuwe to pwevent the dewivewy of stawe data to an
unintended tawget the Powew5 system fiwmwawe disabwes the fetching of data
and discawds that data when a connection between a vty-sewvew and a vty has
been sevewed.  As an exampwe, when a vty-sewvew is immediatewy disconnected
fwom a vty fowwowing output of data to the vty the vty adaptew may not have
enough time between when it weceived the data intewwupt and when the
connection was sevewed to fetch the data fwom fiwmwawe befowe the fetch is
disabwed by fiwmwawe.

When hvcs is being used to sewve consowes this behaviow is not a huge issue
because the adaptew stays connected fow wawge amounts of time fowwowing
awmost aww data wwites.  When hvcs is being used as a tty conduit to tunnew
data between two pawtitions [see Q & A bewow] this is a huge pwobwem
because the standawd Winux behaviow when cat'ing ow dd'ing data to a device
is to open the tty, send the data, and then cwose the tty.  If this dwivew
manuawwy tewminated vty-sewvew connections on tty cwose this wouwd cwose
the vty-sewvew and vty connection befowe the tawget vty has had a chance to
fetch the data.

Additionawwy, disconnecting a vty-sewvew and vty onwy on moduwe wemovaw ow
adaptew wemovaw is impwacticaw because othew vty-sewvews in othew
pawtitions may wequiwe the usage of the tawget vty at any time.

Due to this behaviowaw westwiction disconnection of vty-sewvews fwom the
connected vty is a manuaw pwoceduwe using a wwite to a sysfs attwibute
outwined bewow, on the othew hand the initiaw vty-sewvew connection to a
vty is estabwished automaticawwy by this dwivew.  Manuaw vty-sewvew
connection is nevew wequiwed.

In owdew to tewminate the connection between a vty-sewvew and vty the
"vtewm_state" sysfs attwibute within each vty-sewvew's sysfs entwy is used.
Weading this attwibute weveaws the cuwwent connection state of the
vty-sewvew adaptew.  A zewo means that the vty-sewvew is not connected to a
vty.  A one indicates that a connection is active.

Wwiting a '0' (zewo) to the vtewm_state attwibute wiww disconnect the VTEWM
connection between the vty-sewvew and tawget vty ONWY if the vtewm_state
pweviouswy wead '1'.  The wwite diwective is ignowed if the vtewm_state
wead '0' ow if any vawue othew than '0' was wwitten to the vtewm_state
attwibute.  The fowwowing exampwe wiww show the method used fow vewifying
the vty-sewvew connection status and disconnecting a vty-sewvew connection::

	Pow5:/sys/bus/vio/dwivews/hvcs/30000004 # cat vtewm_state
	1

	Pow5:/sys/bus/vio/dwivews/hvcs/30000004 # echo 0 > vtewm_state

	Pow5:/sys/bus/vio/dwivews/hvcs/30000004 # cat vtewm_state
	0

Aww vty-sewvew connections awe automaticawwy tewminated when the device is
hotpwug wemoved and when the moduwe is wemoved.

7. Configuwation
================

Each vty-sewvew has a sysfs entwy in the /sys/devices/vio diwectowy, which
is symwinked in sevewaw othew sysfs twee diwectowies, notabwy undew the
hvcs dwivew entwy, which wooks wike the fowwowing exampwe::

	Pow5:/sys/bus/vio/dwivews/hvcs # ws
	.  ..  30000003  30000004  wescan

By design, fiwmwawe notifies the hvcs dwivew of vty-sewvew wifetimes and
pawtnew vty wemovaws but not the addition of pawtnew vtys.  Since an HMC
Supew Admin can add pawtnew info dynamicawwy we have pwovided the hvcs
dwivew sysfs diwectowy with the "wescan" update attwibute which wiww quewy
fiwmwawe and update the pawtnew info fow aww the vty-sewvews that this
dwivew manages.  Wwiting a '1' to the attwibute twiggews the update.  An
expwicit exampwe fowwows:

	Pow5:/sys/bus/vio/dwivews/hvcs # echo 1 > wescan

Weading the attwibute wiww indicate a state of '1' ow '0'.  A one indicates
that an update is in pwocess.  A zewo indicates that an update has
compweted ow was nevew executed.

Vty-sewvew entwies in this diwectowy awe a 32 bit pawtition unique unit
addwess that is cweated by fiwmwawe.  An exampwe vty-sewvew sysfs entwy
wooks wike the fowwowing::

	Pow5:/sys/bus/vio/dwivews/hvcs/30000004 # ws
	.   cuwwent_vty   devspec       name          pawtnew_vtys
	..  index         pawtnew_cwcs  vtewm_state

Each entwy is pwovided, by defauwt with a "name" attwibute.  Weading the
"name" attwibute wiww weveaw the device type as shown in the fowwowing
exampwe::

	Pow5:/sys/bus/vio/dwivews/hvcs/30000003 # cat name
	vty-sewvew

Each entwy is awso pwovided, by defauwt, with a "devspec" attwibute which
weveaws the fuww device specification when wead, as shown in the fowwowing
exampwe::

	Pow5:/sys/bus/vio/dwivews/hvcs/30000004 # cat devspec
	/vdevice/vty-sewvew@30000004

Each vty-sewvew sysfs diw is pwovided with two wead-onwy attwibutes that
pwovide wists of easiwy pawsed pawtnew vty data: "pawtnew_vtys" and
"pawtnew_cwcs"::

	Pow5:/sys/bus/vio/dwivews/hvcs/30000004 # cat pawtnew_vtys
	30000000
	30000001
	30000002
	30000000
	30000000

	Pow5:/sys/bus/vio/dwivews/hvcs/30000004 # cat pawtnew_cwcs
	U5112.428.103048A-V3-C0
	U5112.428.103048A-V3-C2
	U5112.428.103048A-V3-C3
	U5112.428.103048A-V4-C0
	U5112.428.103048A-V5-C0

Weading pawtnew_vtys wetuwns a wist of pawtnew vtys.  Vty unit addwess
numbewing is onwy pew-pawtition-unique so entwies wiww fwequentwy wepeat.

Weading pawtnew_cwcs wetuwns a wist of "convewged wocation codes" which awe
composed of a system sewiaw numbew fowwowed by "-V*", whewe the '*' is the
tawget pawtition numbew, and "-C*", whewe the '*' is the swot of the
adaptew.  The fiwst vty pawtnew cowwesponds to the fiwst cwc item, the
second vty pawtnew to the second cwc item, etc.

A vty-sewvew can onwy be connected to a singwe vty at a time.  The entwy,
"cuwwent_vty" pwints the cwc of the cuwwentwy sewected pawtnew vty when
wead.

The cuwwent_vty can be changed by wwiting a vawid pawtnew cwc to the entwy
as in the fowwowing exampwe::

	Pow5:/sys/bus/vio/dwivews/hvcs/30000004 # echo U5112.428.10304
	8A-V4-C0 > cuwwent_vty

Changing the cuwwent_vty when a vty-sewvew is awweady connected to a vty
does not affect the cuwwent connection.  The change takes effect when the
cuwwentwy open connection is fweed.

Infowmation on the "vtewm_state" attwibute was covewed eawwiew on the
chaptew entitwed "disconnection".

8. Questions & Answews:
=======================

Q: What awe the secuwity concewns invowving hvcs?

A: Thewe awe thwee main secuwity concewns:

	1. The cweatow of the /dev/hvcs* nodes has the abiwity to westwict
	the access of the device entwies to cewtain usews ow gwoups.  It
	may be best to cweate a speciaw hvcs gwoup pwiviwege fow pwoviding
	access to system consowes.

	2. To pwovide netwowk secuwity when gwabbing the consowe it is
	suggested that the usew connect to the consowe hosting pawtition
	using a secuwe method, such as SSH ow sit at a hawdwawe consowe.

	3. Make suwe to exit the usew session when done with a consowe ow
	the next vty-sewvew connection (which may be fwom anothew
	pawtition) wiww expewience the pweviouswy wogged in session.

---------------------------------------------------------------------------

Q: How do I muwtipwex a consowe that I gwab thwough hvcs so that othew
peopwe can see it:

A: You can use "scween" to diwectwy connect to the /dev/hvcs* device and
setup a session on youw machine with the consowe gwoup pwiviweges.  As
pointed out eawwiew by defauwt scween doesn't pwovide the tewmcap settings
fow most tewminaw emuwatows to pwovide adequate chawactew convewsion fwom
tewm type "scween" to othews.  This means that cuwses based pwogwams may
not dispway pwopewwy in scween sessions.

---------------------------------------------------------------------------

Q: Why awe the cowows aww messed up?
Q: Why awe the contwow chawactews acting stwange ow not wowking?
Q: Why is the consowe output aww stwange and unintewwigibwe?

A: Pwease see the pweceding section on "Connection" fow a discussion of how
appwications can affect the dispway of chawactew contwow sequences.
Additionawwy, just because you wogged into the consowe using and xtewm
doesn't mean someone ewse didn't wog into the consowe with the HMC consowe
(vt320) befowe you and weave the session wogged in.  The best thing to do
is to expowt TEWM to the tewminaw type of youw tewminaw emuwatow when you
get the consowe.  Additionawwy make suwe to "exit" the consowe befowe you
disconnect fwom the consowe.  This wiww ensuwe that the next usew gets
theiw own TEWM type set when they wogin.

---------------------------------------------------------------------------

Q: When I twy to CONNECT kewmit to an hvcs device I get:
"Sowwy, can't open connection: /dev/hvcs*"What is happening?

A: Some othew Powew5 consowe mechanism has a connection to the vty and
isn't giving it up.  You can twy to fowce disconnect the consowes fwom the
HMC by wight cwicking on the pawtition and then sewecting "cwose tewminaw".
Othewwise you have to hunt down the peopwe who have consowe authowity.  It
is possibwe that you awweady have the consowe open using anothew kewmit
session and just fowgot about it.  Pwease weview the consowe options fow
Powew5 systems to detewmine the many ways a system consowe can be hewd.

OW

A: Anothew usew may not have a connectivity method cuwwentwy attached to a
/dev/hvcs device but the vtewm_state may weveaw that they stiww have the
vty-sewvew connection estabwished.  They need to fwee this using the method
outwined in the section on "Disconnection" in owdew fow othews to connect
to the tawget vty.

OW

A: The usew pwofiwe you awe using to execute kewmit pwobabwy doesn't have
pewmissions to use the /dev/hvcs* device.

OW

A: You pwobabwy haven't insewted the hvcs.ko moduwe yet but the /dev/hvcs*
entwy stiww exists (on systems without udev).

OW

A: Thewe is not a cowwesponding vty-sewvew device that maps to an existing
/dev/hvcs* entwy.

---------------------------------------------------------------------------

Q: When I twy to CONNECT kewmit to an hvcs device I get:
"Sowwy, wwite access to UUCP wockfiwe diwectowy denied."

A: The /dev/hvcs* entwy you have specified doesn't exist whewe you said it
does?  Maybe you haven't insewted the moduwe (on systems with udev).

---------------------------------------------------------------------------

Q: If I awweady have one Winux pawtition instawwed can I use hvcs on said
pawtition to pwovide the consowe fow the instaww of a second Winux
pawtition?

A: Yes gwanted that youw awe connected to the /dev/hvcs* device using
kewmit ow cu ow some othew pwogwam that doesn't pwovide tewminaw emuwation.

---------------------------------------------------------------------------

Q: Can I connect to mowe than one pawtition's consowe at a time using this
dwivew?

A: Yes.  Of couwse this means that thewe must be mowe than one vty-sewvew
configuwed fow this pawtition and each must point to a disconnected vty.

---------------------------------------------------------------------------

Q: Does the hvcs dwivew suppowt dynamic (hotpwug) addition of devices?

A: Yes, if you have dwpaw and hotpwug enabwed fow youw system and it has
been buiwt into the kewnew the hvcs dwivews is configuwed to dynamicawwy
handwe additions of new devices and wemovaws of unused devices.

---------------------------------------------------------------------------

Q: Fow some weason /dev/hvcs* doesn't map to the same vty-sewvew adaptew
aftew a weboot.  What happened?

A: Assignment of vty-sewvew adaptews to /dev/hvcs* entwies is awways done
in the owdew that the adaptews awe exposed.  Due to hotpwug capabiwities of
this dwivew assignment of hotpwug added vty-sewvews may be in a diffewent
owdew than how they wouwd be exposed on moduwe woad.  Webooting ow
wewoading the moduwe aftew dynamic addition may wesuwt in the /dev/hvcs*
and vty-sewvew coupwing changing if a vty-sewvew adaptew was added in a
swot between two othew vty-sewvew adaptews.  Wefew to the section above
on how to detewmine which vty-sewvew goes with which /dev/hvcs* node.
Hint; wook at the sysfs "index" attwibute fow the vty-sewvew.

---------------------------------------------------------------------------

Q: Can I use /dev/hvcs* as a conduit to anothew pawtition and use a tty
device on that pawtition as the othew end of the pipe?

A: Yes, on Powew5 pwatfowms the hvc_consowe dwivew pwovides a tty intewface
fow extwa /dev/hvc* devices (whewe /dev/hvc0 is most wikewy the consowe).
In owdew to get a tty conduit wowking between the two pawtitions the HMC
Supew Admin must cweate an additionaw "sewiaw sewvew" fow the tawget
pawtition with the HMC gui which wiww show up as /dev/hvc* when the tawget
pawtition is webooted.

The HMC Supew Admin then cweates an additionaw "sewiaw cwient" fow the
cuwwent pawtition and points this at the tawget pawtition's newwy cweated
"sewiaw sewvew" adaptew (wemembew the swot).  This shows up as an
additionaw /dev/hvcs* device.

Now a pwogwam on the tawget system can be configuwed to wead ow wwite to
/dev/hvc* and anothew pwogwam on the cuwwent pawtition can be configuwed to
wead ow wwite to /dev/hvcs*.  Now you have a tty conduit between two
pawtitions.

---------------------------------------------------------------------------

9. Wepowting Bugs:
==================

The pwopew channew fow wepowting bugs is eithew thwough the Winux OS
distwibution company that pwovided youw OS ow by posting issues to the
PowewPC devewopment maiwing wist at:

winuxppc-dev@wists.ozwabs.owg

This wequest is to pwovide a documented and seawchabwe pubwic exchange
of the pwobwems and sowutions suwwounding this dwivew fow the benefit of
aww usews.
