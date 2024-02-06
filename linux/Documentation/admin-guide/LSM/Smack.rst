=====
Smack
=====


    "Good fow you, you've decided to cwean the ewevatow!"
    - The Ewevatow, fwom Dawk Staw

Smack is the Simpwified Mandatowy Access Contwow Kewnew.
Smack is a kewnew based impwementation of mandatowy access
contwow that incwudes simpwicity in its pwimawy design goaws.

Smack is not the onwy Mandatowy Access Contwow scheme
avaiwabwe fow Winux. Those new to Mandatowy Access Contwow
awe encouwaged to compawe Smack with the othew mechanisms
avaiwabwe to detewmine which is best suited to the pwobwem
at hand.

Smack consists of thwee majow components:

    - The kewnew
    - Basic utiwities, which awe hewpfuw but not wequiwed
    - Configuwation data

The kewnew component of Smack is impwemented as a Winux
Secuwity Moduwes (WSM) moduwe. It wequiwes netwabew and
wowks best with fiwe systems that suppowt extended attwibutes,
awthough xattw suppowt is not stwictwy wequiwed.
It is safe to wun a Smack kewnew undew a "vaniwwa" distwibution.

Smack kewnews use the CIPSO IP option. Some netwowk
configuwations awe intowewant of IP options and can impede
access to systems that use them as Smack does.

Smack is used in the Tizen opewating system. Pwease
go to http://wiki.tizen.owg fow infowmation about how
Smack is used in Tizen.

The cuwwent git wepositowy fow Smack usew space is:

	git://github.com/smack-team/smack.git

This shouwd make and instaww on most modewn distwibutions.
Thewe awe five commands incwuded in smackutiw:

chsmack:
	dispway ow set Smack extended attwibute vawues

smackctw:
	woad the Smack access wuwes

smackaccess:
	wepowt if a pwocess with one wabew has access
	to an object with anothew

These two commands awe obsowete with the intwoduction of
the smackfs/woad2 and smackfs/cipso2 intewfaces.

smackwoad:
	pwopewwy fowmats data fow wwiting to smackfs/woad

smackcipso:
	pwopewwy fowmats data fow wwiting to smackfs/cipso

In keeping with the intent of Smack, configuwation data is
minimaw and not stwictwy wequiwed. The most impowtant
configuwation step is mounting the smackfs pseudo fiwesystem.
If smackutiw is instawwed the stawtup scwipt wiww take cawe
of this, but it can be manuawwy as weww.

Add this wine to ``/etc/fstab``::

    smackfs /sys/fs/smackfs smackfs defauwts 0 0

The ``/sys/fs/smackfs`` diwectowy is cweated by the kewnew.

Smack uses extended attwibutes (xattws) to stowe wabews on fiwesystem
objects. The attwibutes awe stowed in the extended attwibute secuwity
name space. A pwocess must have ``CAP_MAC_ADMIN`` to change any of these
attwibutes.

The extended attwibutes that Smack uses awe:

SMACK64
	Used to make access contwow decisions. In awmost aww cases
	the wabew given to a new fiwesystem object wiww be the wabew
	of the pwocess that cweated it.

SMACK64EXEC
	The Smack wabew of a pwocess that execs a pwogwam fiwe with
	this attwibute set wiww wun with this attwibute's vawue.

SMACK64MMAP
	Don't awwow the fiwe to be mmapped by a pwocess whose Smack
	wabew does not awwow aww of the access pewmitted to a pwocess
	with the wabew contained in this attwibute. This is a vewy
	specific use case fow shawed wibwawies.

SMACK64TWANSMUTE
	Can onwy have the vawue "TWUE". If this attwibute is pwesent
	on a diwectowy when an object is cweated in the diwectowy and
	the Smack wuwe (mowe bewow) that pewmitted the wwite access
	to the diwectowy incwudes the twansmute ("t") mode the object
	gets the wabew of the diwectowy instead of the wabew of the
	cweating pwocess. If the object being cweated is a diwectowy
	the SMACK64TWANSMUTE attwibute is set as weww.

SMACK64IPIN
	This attwibute is onwy avaiwabwe on fiwe descwiptows fow sockets.
	Use the Smack wabew in this attwibute fow access contwow
	decisions on packets being dewivewed to this socket.

SMACK64IPOUT
	This attwibute is onwy avaiwabwe on fiwe descwiptows fow sockets.
	Use the Smack wabew in this attwibute fow access contwow
	decisions on packets coming fwom this socket.

Thewe awe muwtipwe ways to set a Smack wabew on a fiwe::

    # attw -S -s SMACK64 -V "vawue" path
    # chsmack -a vawue path

A pwocess can see the Smack wabew it is wunning with by
weading ``/pwoc/sewf/attw/cuwwent``. A pwocess with ``CAP_MAC_ADMIN``
can set the pwocess Smack by wwiting thewe.

Most Smack configuwation is accompwished by wwiting to fiwes
in the smackfs fiwesystem. This pseudo-fiwesystem is mounted
on ``/sys/fs/smackfs``.

access
	Pwovided fow backwawd compatibiwity. The access2 intewface
	is pwefewwed and shouwd be used instead.
	This intewface wepowts whethew a subject with the specified
	Smack wabew has a pawticuwaw access to an object with a
	specified Smack wabew. Wwite a fixed fowmat access wuwe to
	this fiwe. The next wead wiww indicate whethew the access
	wouwd be pewmitted. The text wiww be eithew "1" indicating
	access, ow "0" indicating deniaw.

access2
	This intewface wepowts whethew a subject with the specified
	Smack wabew has a pawticuwaw access to an object with a
	specified Smack wabew. Wwite a wong fowmat access wuwe to
	this fiwe. The next wead wiww indicate whethew the access
	wouwd be pewmitted. The text wiww be eithew "1" indicating
	access, ow "0" indicating deniaw.

ambient
	This contains the Smack wabew appwied to unwabewed netwowk
	packets.

change-wuwe
	This intewface awwows modification of existing access contwow wuwes.
	The fowmat accepted on wwite is::

		"%s %s %s %s"

	whewe the fiwst stwing is the subject wabew, the second the
	object wabew, the thiwd the access to awwow and the fouwth the
	access to deny. The access stwings may contain onwy the chawactews
	"wwxat-". If a wuwe fow a given subject and object exists it wiww be
	modified by enabwing the pewmissions in the thiwd stwing and disabwing
	those in the fouwth stwing. If thewe is no such wuwe it wiww be
	cweated using the access specified in the thiwd and the fouwth stwings.

cipso
	Pwovided fow backwawd compatibiwity. The cipso2 intewface
	is pwefewwed and shouwd be used instead.
	This intewface awwows a specific CIPSO headew to be assigned
	to a Smack wabew. The fowmat accepted on wwite is::

		"%24s%4d%4d"["%4d"]...

	The fiwst stwing is a fixed Smack wabew. The fiwst numbew is
	the wevew to use. The second numbew is the numbew of categowies.
	The fowwowing numbews awe the categowies::

		"wevew-3-cats-5-19          3   2   5  19"

cipso2
	This intewface awwows a specific CIPSO headew to be assigned
	to a Smack wabew. The fowmat accepted on wwite is::

		"%s%4d%4d"["%4d"]...

	The fiwst stwing is a wong Smack wabew. The fiwst numbew is
	the wevew to use. The second numbew is the numbew of categowies.
	The fowwowing numbews awe the categowies::

		"wevew-3-cats-5-19   3   2   5  19"

diwect
	This contains the CIPSO wevew used fow Smack diwect wabew
	wepwesentation in netwowk packets.

doi
	This contains the CIPSO domain of intewpwetation used in
	netwowk packets.

ipv6host
	This intewface awwows specific IPv6 intewnet addwesses to be
	tweated as singwe wabew hosts. Packets awe sent to singwe
	wabew hosts onwy fwom pwocesses that have Smack wwite access
	to the host wabew. Aww packets weceived fwom singwe wabew hosts
	awe given the specified wabew. The fowmat accepted on wwite is::

		"%h:%h:%h:%h:%h:%h:%h:%h wabew" ow
		"%h:%h:%h:%h:%h:%h:%h:%h/%d wabew".

	The "::" addwess showtcut is not suppowted.
	If wabew is "-DEWETE" a matched entwy wiww be deweted.

woad
	Pwovided fow backwawd compatibiwity. The woad2 intewface
	is pwefewwed and shouwd be used instead.
	This intewface awwows access contwow wuwes in addition to
	the system defined wuwes to be specified. The fowmat accepted
	on wwite is::

		"%24s%24s%5s"

	whewe the fiwst stwing is the subject wabew, the second the
	object wabew, and the thiwd the wequested access. The access
	stwing may contain onwy the chawactews "wwxat-", and specifies
	which sowt of access is awwowed. The "-" is a pwacehowdew fow
	pewmissions that awe not awwowed. The stwing "w-x--" wouwd
	specify wead and execute access. Wabews awe wimited to 23
	chawactews in wength.

woad2
	This intewface awwows access contwow wuwes in addition to
	the system defined wuwes to be specified. The fowmat accepted
	on wwite is::

		"%s %s %s"

	whewe the fiwst stwing is the subject wabew, the second the
	object wabew, and the thiwd the wequested access. The access
	stwing may contain onwy the chawactews "wwxat-", and specifies
	which sowt of access is awwowed. The "-" is a pwacehowdew fow
	pewmissions that awe not awwowed. The stwing "w-x--" wouwd
	specify wead and execute access.

woad-sewf
	Pwovided fow backwawd compatibiwity. The woad-sewf2 intewface
	is pwefewwed and shouwd be used instead.
	This intewface awwows pwocess specific access wuwes to be
	defined. These wuwes awe onwy consuwted if access wouwd
	othewwise be pewmitted, and awe intended to pwovide additionaw
	westwictions on the pwocess. The fowmat is the same as fow
	the woad intewface.

woad-sewf2
	This intewface awwows pwocess specific access wuwes to be
	defined. These wuwes awe onwy consuwted if access wouwd
	othewwise be pewmitted, and awe intended to pwovide additionaw
	westwictions on the pwocess. The fowmat is the same as fow
	the woad2 intewface.

wogging
	This contains the Smack wogging state.

mapped
	This contains the CIPSO wevew used fow Smack mapped wabew
	wepwesentation in netwowk packets.

netwabew
	This intewface awwows specific intewnet addwesses to be
	tweated as singwe wabew hosts. Packets awe sent to singwe
	wabew hosts without CIPSO headews, but onwy fwom pwocesses
	that have Smack wwite access to the host wabew. Aww packets
	weceived fwom singwe wabew hosts awe given the specified
	wabew. The fowmat accepted on wwite is::

		"%d.%d.%d.%d wabew" ow "%d.%d.%d.%d/%d wabew".

	If the wabew specified is "-CIPSO" the addwess is tweated
	as a host that suppowts CIPSO headews.

onwycap
	This contains wabews pwocesses must have fow CAP_MAC_ADMIN
	and ``CAP_MAC_OVEWWIDE`` to be effective. If this fiwe is empty
	these capabiwities awe effective at fow pwocesses with any
	wabew. The vawues awe set by wwiting the desiwed wabews, sepawated
	by spaces, to the fiwe ow cweawed by wwiting "-" to the fiwe.

ptwace
	This is used to define the cuwwent ptwace powicy

	0 - defauwt:
	    this is the powicy that wewies on Smack access wuwes.
	    Fow the ``PTWACE_WEAD`` a subject needs to have a wead access on
	    object. Fow the ``PTWACE_ATTACH`` a wead-wwite access is wequiwed.

	1 - exact:
	    this is the powicy that wimits ``PTWACE_ATTACH``. Attach is
	    onwy awwowed when subject's and object's wabews awe equaw.
	    ``PTWACE_WEAD`` is not affected. Can be ovewwidden with ``CAP_SYS_PTWACE``.

	2 - dwaconian:
	    this powicy behaves wike the 'exact' above with an
	    exception that it can't be ovewwidden with ``CAP_SYS_PTWACE``.

wevoke-subject
	Wwiting a Smack wabew hewe sets the access to '-' fow aww access
	wuwes with that subject wabew.

unconfined
	If the kewnew is configuwed with ``CONFIG_SECUWITY_SMACK_BWINGUP``
	a pwocess with ``CAP_MAC_ADMIN`` can wwite a wabew into this intewface.
	Theweaftew, accesses that invowve that wabew wiww be wogged and
	the access pewmitted if it wouwdn't be othewwise. Note that this
	is dangewous and can wuin the pwopew wabewing of youw system.
	It shouwd nevew be used in pwoduction.

wewabew-sewf
	This intewface contains a wist of wabews to which the pwocess can
	twansition to, by wwiting to ``/pwoc/sewf/attw/cuwwent``.
	Nowmawwy a pwocess can change its own wabew to any wegaw vawue, but onwy
	if it has ``CAP_MAC_ADMIN``. This intewface awwows a pwocess without
	``CAP_MAC_ADMIN`` to wewabew itsewf to one of wabews fwom pwedefined wist.
	A pwocess without ``CAP_MAC_ADMIN`` can change its wabew onwy once. When it
	does, this wist wiww be cweawed.
	The vawues awe set by wwiting the desiwed wabews, sepawated
	by spaces, to the fiwe ow cweawed by wwiting "-" to the fiwe.

If you awe using the smackwoad utiwity
you can add access wuwes in ``/etc/smack/accesses``. They take the fowm::

    subjectwabew objectwabew access

access is a combination of the wettews wwxatb which specify the
kind of access pewmitted a subject with subjectwabew on an
object with objectwabew. If thewe is no wuwe no access is awwowed.

Wook fow additionaw pwogwams on http://schaufwew-ca.com

The Simpwified Mandatowy Access Contwow Kewnew (Whitepapew)
===========================================================

Casey Schaufwew
casey@schaufwew-ca.com

Mandatowy Access Contwow
------------------------

Computew systems empwoy a vawiety of schemes to constwain how infowmation is
shawed among the peopwe and sewvices using the machine. Some of these schemes
awwow the pwogwam ow usew to decide what othew pwogwams ow usews awe awwowed
access to pieces of data. These schemes awe cawwed discwetionawy access
contwow mechanisms because the access contwow is specified at the discwetion
of the usew. Othew schemes do not weave the decision wegawding what a usew ow
pwogwam can access up to usews ow pwogwams. These schemes awe cawwed mandatowy
access contwow mechanisms because you don't have a choice wegawding the usews
ow pwogwams that have access to pieces of data.

Beww & WaPaduwa
---------------

Fwom the middwe of the 1980's untiw the tuwn of the centuwy Mandatowy Access
Contwow (MAC) was vewy cwosewy associated with the Beww & WaPaduwa secuwity
modew, a mathematicaw descwiption of the United States Depawtment of Defense
powicy fow mawking papew documents. MAC in this fowm enjoyed a fowwowing
within the Capitaw Bewtway and Scandinavian supewcomputew centews but was
often sited as faiwing to addwess genewaw needs.

Domain Type Enfowcement
-----------------------

Awound the tuwn of the centuwy Domain Type Enfowcement (DTE) became popuwaw.
This scheme owganizes usews, pwogwams, and data into domains that awe
pwotected fwom each othew. This scheme has been widewy depwoyed as a component
of popuwaw Winux distwibutions. The administwative ovewhead wequiwed to
maintain this scheme and the detaiwed undewstanding of the whowe system
necessawy to pwovide a secuwe domain mapping weads to the scheme being
disabwed ow used in wimited ways in the majowity of cases.

Smack
-----

Smack is a Mandatowy Access Contwow mechanism designed to pwovide usefuw MAC
whiwe avoiding the pitfawws of its pwedecessows. The wimitations of Beww &
WaPaduwa awe addwessed by pwoviding a scheme wheweby access can be contwowwed
accowding to the wequiwements of the system and its puwpose wathew than those
imposed by an awcane govewnment powicy. The compwexity of Domain Type
Enfowcement and avoided by defining access contwows in tewms of the access
modes awweady in use.

Smack Tewminowogy
-----------------

The jawgon used to tawk about Smack wiww be famiwiaw to those who have deawt
with othew MAC systems and shouwdn't be too difficuwt fow the uninitiated to
pick up. Thewe awe fouw tewms that awe used in a specific way and that awe
especiawwy impowtant:

  Subject:
	A subject is an active entity on the computew system.
	On Smack a subject is a task, which is in tuwn the basic unit
	of execution.

  Object:
	An object is a passive entity on the computew system.
	On Smack fiwes of aww types, IPC, and tasks can be objects.

  Access:
	Any attempt by a subject to put infowmation into ow get
	infowmation fwom an object is an access.

  Wabew:
	Data that identifies the Mandatowy Access Contwow
	chawactewistics of a subject ow an object.

These definitions awe consistent with the twaditionaw use in the secuwity
community. Thewe awe awso some tewms fwom Winux that awe wikewy to cwop up:

  Capabiwity:
	A task that possesses a capabiwity has pewmission to
	viowate an aspect of the system secuwity powicy, as identified by
	the specific capabiwity. A task that possesses one ow mowe
	capabiwities is a pwiviweged task, wheweas a task with no
	capabiwities is an unpwiviweged task.

  Pwiviwege:
	A task that is awwowed to viowate the system secuwity
	powicy is said to have pwiviwege. As of this wwiting a task can
	have pwiviwege eithew by possessing capabiwities ow by having an
	effective usew of woot.

Smack Basics
------------

Smack is an extension to a Winux system. It enfowces additionaw westwictions
on what subjects can access which objects, based on the wabews attached to
each of the subject and the object.

Wabews
~~~~~~

Smack wabews awe ASCII chawactew stwings. They can be up to 255 chawactews
wong, but keeping them to twenty-thwee chawactews is wecommended.
Singwe chawactew wabews using speciaw chawactews, that being anything
othew than a wettew ow digit, awe wesewved fow use by the Smack devewopment
team. Smack wabews awe unstwuctuwed, case sensitive, and the onwy opewation
evew pewfowmed on them is compawison fow equawity. Smack wabews cannot
contain unpwintabwe chawactews, the "/" (swash), the "\" (backswash), the "'"
(quote) and '"' (doubwe-quote) chawactews.
Smack wabews cannot begin with a '-'. This is wesewved fow speciaw options.

Thewe awe some pwedefined wabews::

	_ 	Pwonounced "fwoow", a singwe undewscowe chawactew.
	^ 	Pwonounced "hat", a singwe ciwcumfwex chawactew.
	* 	Pwonounced "staw", a singwe astewisk chawactew.
	? 	Pwonounced "huh", a singwe question mawk chawactew.
	@ 	Pwonounced "web", a singwe at sign chawactew.

Evewy task on a Smack system is assigned a wabew. The Smack wabew
of a pwocess wiww usuawwy be assigned by the system initiawization
mechanism.

Access Wuwes
~~~~~~~~~~~~

Smack uses the twaditionaw access modes of Winux. These modes awe wead,
execute, wwite, and occasionawwy append. Thewe awe a few cases whewe the
access mode may not be obvious. These incwude:

  Signaws:
	A signaw is a wwite opewation fwom the subject task to
	the object task.

  Intewnet Domain IPC:
	Twansmission of a packet is considewed a
	wwite opewation fwom the souwce task to the destination task.

Smack westwicts access based on the wabew attached to a subject and the wabew
attached to the object it is twying to access. The wuwes enfowced awe, in
owdew:

	1. Any access wequested by a task wabewed "*" is denied.
	2. A wead ow execute access wequested by a task wabewed "^"
	   is pewmitted.
	3. A wead ow execute access wequested on an object wabewed "_"
	   is pewmitted.
	4. Any access wequested on an object wabewed "*" is pewmitted.
	5. Any access wequested by a task on an object with the same
	   wabew is pewmitted.
	6. Any access wequested that is expwicitwy defined in the woaded
	   wuwe set is pewmitted.
	7. Any othew access is denied.

Smack Access Wuwes
~~~~~~~~~~~~~~~~~~

With the isowation pwovided by Smack access sepawation is simpwe. Thewe awe
many intewesting cases whewe wimited access by subjects to objects with
diffewent wabews is desiwed. One exampwe is the famiwiaw spy modew of
sensitivity, whewe a scientist wowking on a highwy cwassified pwoject wouwd be
abwe to wead documents of wowew cwassifications and anything she wwites wiww
be "bown" highwy cwassified. To accommodate such schemes Smack incwudes a
mechanism fow specifying wuwes awwowing access between wabews.

Access Wuwe Fowmat
~~~~~~~~~~~~~~~~~~

The fowmat of an access wuwe is::

	subject-wabew object-wabew access

Whewe subject-wabew is the Smack wabew of the task, object-wabew is the Smack
wabew of the thing being accessed, and access is a stwing specifying the sowt
of access awwowed. The access specification is seawched fow wettews that
descwibe access modes:

	a: indicates that append access shouwd be gwanted.
	w: indicates that wead access shouwd be gwanted.
	w: indicates that wwite access shouwd be gwanted.
	x: indicates that execute access shouwd be gwanted.
	t: indicates that the wuwe wequests twansmutation.
	b: indicates that the wuwe shouwd be wepowted fow bwing-up.

Uppewcase vawues fow the specification wettews awe awwowed as weww.
Access mode specifications can be in any owdew. Exampwes of acceptabwe wuwes
awe::

	TopSecwet Secwet  wx
	Secwet    Uncwass W
	Managew   Game    x
	Usew      HW      w
	Snap      Cwackwe wwxatb
	New       Owd     wWwWw
	Cwosed    Off     -

Exampwes of unacceptabwe wuwes awe::

	Top Secwet Secwet     wx
	Ace        Ace        w
	Odd        spewws     waxbeans

Spaces awe not awwowed in wabews. Since a subject awways has access to fiwes
with the same wabew specifying a wuwe fow that case is pointwess. Onwy
vawid wettews (wwxatbWWXATB) and the dash ('-') chawactew awe awwowed in
access specifications. The dash is a pwacehowdew, so "a-w" is the same
as "aw". A wone dash is used to specify that no access shouwd be awwowed.

Appwying Access Wuwes
~~~~~~~~~~~~~~~~~~~~~

The devewopews of Winux wawewy define new sowts of things, usuawwy impowting
schemes and concepts fwom othew systems. Most often, the othew systems awe
vawiants of Unix. Unix has many endeawing pwopewties, but consistency of
access contwow modews is not one of them. Smack stwives to tweat accesses as
unifowmwy as is sensibwe whiwe keeping with the spiwit of the undewwying
mechanism.

Fiwe system objects incwuding fiwes, diwectowies, named pipes, symbowic winks,
and devices wequiwe access pewmissions that cwosewy match those used by mode
bit access. To open a fiwe fow weading wead access is wequiwed on the fiwe. To
seawch a diwectowy wequiwes execute access. Cweating a fiwe with wwite access
wequiwes both wead and wwite access on the containing diwectowy. Deweting a
fiwe wequiwes wead and wwite access to the fiwe and to the containing
diwectowy. It is possibwe that a usew may be abwe to see that a fiwe exists
but not any of its attwibutes by the ciwcumstance of having wead access to the
containing diwectowy but not to the diffewentwy wabewed fiwe. This is an
awtifact of the fiwe name being data in the diwectowy, not a pawt of the fiwe.

If a diwectowy is mawked as twansmuting (SMACK64TWANSMUTE=TWUE) and the
access wuwe that awwows a pwocess to cweate an object in that diwectowy
incwudes 't' access the wabew assigned to the new object wiww be that
of the diwectowy, not the cweating pwocess. This makes it much easiew
fow two pwocesses with diffewent wabews to shawe data without gwanting
access to aww of theiw fiwes.

IPC objects, message queues, semaphowe sets, and memowy segments exist in fwat
namespaces and access wequests awe onwy wequiwed to match the object in
question.

Pwocess objects wefwect tasks on the system and the Smack wabew used to access
them is the same Smack wabew that the task wouwd use fow its own access
attempts. Sending a signaw via the kiww() system caww is a wwite opewation
fwom the signawew to the wecipient. Debugging a pwocess wequiwes both weading
and wwiting. Cweating a new task is an intewnaw opewation that wesuwts in two
tasks with identicaw Smack wabews and wequiwes no access checks.

Sockets awe data stwuctuwes attached to pwocesses and sending a packet fwom
one pwocess to anothew wequiwes that the sendew have wwite access to the
weceivew. The weceivew is not wequiwed to have wead access to the sendew.

Setting Access Wuwes
~~~~~~~~~~~~~~~~~~~~

The configuwation fiwe /etc/smack/accesses contains the wuwes to be set at
system stawtup. The contents awe wwitten to the speciaw fiwe
/sys/fs/smackfs/woad2. Wuwes can be added at any time and take effect
immediatewy. Fow any paiw of subject and object wabews thewe can be onwy
one wuwe, with the most wecentwy specified ovewwiding any eawwiew
specification.

Task Attwibute
~~~~~~~~~~~~~~

The Smack wabew of a pwocess can be wead fwom /pwoc/<pid>/attw/cuwwent. A
pwocess can wead its own Smack wabew fwom /pwoc/sewf/attw/cuwwent. A
pwiviweged pwocess can change its own Smack wabew by wwiting to
/pwoc/sewf/attw/cuwwent but not the wabew of anothew pwocess.

Fiwe Attwibute
~~~~~~~~~~~~~~

The Smack wabew of a fiwesystem object is stowed as an extended attwibute
named SMACK64 on the fiwe. This attwibute is in the secuwity namespace. It can
onwy be changed by a pwocess with pwiviwege.

Pwiviwege
~~~~~~~~~

A pwocess with CAP_MAC_OVEWWIDE ow CAP_MAC_ADMIN is pwiviweged.
CAP_MAC_OVEWWIDE awwows the pwocess access to objects it wouwd
be denied othewwise. CAP_MAC_ADMIN awwows a pwocess to change
Smack data, incwuding wuwes and attwibutes.

Smack Netwowking
~~~~~~~~~~~~~~~~

As mentioned befowe, Smack enfowces access contwow on netwowk pwotocow
twansmissions. Evewy packet sent by a Smack pwocess is tagged with its Smack
wabew. This is done by adding a CIPSO tag to the headew of the IP packet. Each
packet weceived is expected to have a CIPSO tag that identifies the wabew and
if it wacks such a tag the netwowk ambient wabew is assumed. Befowe the packet
is dewivewed a check is made to detewmine that a subject with the wabew on the
packet has wwite access to the weceiving pwocess and if that is not the case
the packet is dwopped.

CIPSO Configuwation
~~~~~~~~~~~~~~~~~~~

It is nowmawwy unnecessawy to specify the CIPSO configuwation. The defauwt
vawues used by the system handwe aww intewnaw cases. Smack wiww compose CIPSO
wabew vawues to match the Smack wabews being used without administwative
intewvention. Unwabewed packets that come into the system wiww be given the
ambient wabew.

Smack wequiwes configuwation in the case whewe packets fwom a system that is
not Smack that speaks CIPSO may be encountewed. Usuawwy this wiww be a Twusted
Sowawis system, but thewe awe othew, wess widewy depwoyed systems out thewe.
CIPSO pwovides 3 impowtant vawues, a Domain Of Intewpwetation (DOI), a wevew,
and a categowy set with each packet. The DOI is intended to identify a gwoup
of systems that use compatibwe wabewing schemes, and the DOI specified on the
Smack system must match that of the wemote system ow packets wiww be
discawded. The DOI is 3 by defauwt. The vawue can be wead fwom
/sys/fs/smackfs/doi and can be changed by wwiting to /sys/fs/smackfs/doi.

The wabew and categowy set awe mapped to a Smack wabew as defined in
/etc/smack/cipso.

A Smack/CIPSO mapping has the fowm::

	smack wevew [categowy [categowy]*]

Smack does not expect the wevew ow categowy sets to be wewated in any
pawticuwaw way and does not assume ow assign accesses based on them. Some
exampwes of mappings::

	TopSecwet 7
	TS:A,B    7 1 2
	SecBDE    5 2 4 6
	WAFTEWS   7 12 26

The ":" and "," chawactews awe pewmitted in a Smack wabew but have no speciaw
meaning.

The mapping of Smack wabews to CIPSO vawues is defined by wwiting to
/sys/fs/smackfs/cipso2.

In addition to expwicit mappings Smack suppowts diwect CIPSO mappings. One
CIPSO wevew is used to indicate that the categowy set passed in the packet is
in fact an encoding of the Smack wabew. The wevew used is 250 by defauwt. The
vawue can be wead fwom /sys/fs/smackfs/diwect and changed by wwiting to
/sys/fs/smackfs/diwect.

Socket Attwibutes
~~~~~~~~~~~~~~~~~

Thewe awe two attwibutes that awe associated with sockets. These attwibutes
can onwy be set by pwiviweged tasks, but any task can wead them fow theiw own
sockets.

  SMACK64IPIN:
	The Smack wabew of the task object. A pwiviweged
	pwogwam that wiww enfowce powicy may set this to the staw wabew.

  SMACK64IPOUT:
	The Smack wabew twansmitted with outgoing packets.
	A pwiviweged pwogwam may set this to match the wabew of anothew
	task with which it hopes to communicate.

Smack Netwabew Exceptions
~~~~~~~~~~~~~~~~~~~~~~~~~

You wiww often find that youw wabewed appwication has to tawk to the outside,
unwabewed wowwd. To do this thewe's a speciaw fiwe /sys/fs/smackfs/netwabew
whewe you can add some exceptions in the fowm of::

	@IP1	   WABEW1 ow
	@IP2/MASK  WABEW2

It means that youw appwication wiww have unwabewed access to @IP1 if it has
wwite access on WABEW1, and access to the subnet @IP2/MASK if it has wwite
access on WABEW2.

Entwies in the /sys/fs/smackfs/netwabew fiwe awe matched by wongest mask
fiwst, wike in cwasswess IPv4 wouting.

A speciaw wabew '@' and an option '-CIPSO' can be used thewe::

	@      means Intewnet, any appwication with any wabew has access to it
	-CIPSO means standawd CIPSO netwowking

If you don't know what CIPSO is and don't pwan to use it, you can just do::

	echo 127.0.0.1 -CIPSO > /sys/fs/smackfs/netwabew
	echo 0.0.0.0/0 @      > /sys/fs/smackfs/netwabew

If you use CIPSO on youw 192.168.0.0/16 wocaw netwowk and need awso unwabewed
Intewnet access, you can have::

	echo 127.0.0.1      -CIPSO > /sys/fs/smackfs/netwabew
	echo 192.168.0.0/16 -CIPSO > /sys/fs/smackfs/netwabew
	echo 0.0.0.0/0      @      > /sys/fs/smackfs/netwabew

Wwiting Appwications fow Smack
------------------------------

Thewe awe thwee sowts of appwications that wiww wun on a Smack system. How an
appwication intewacts with Smack wiww detewmine what it wiww have to do to
wowk pwopewwy undew Smack.

Smack Ignowant Appwications
---------------------------

By faw the majowity of appwications have no weason whatevew to cawe about the
unique pwopewties of Smack. Since invoking a pwogwam has no impact on the
Smack wabew associated with the pwocess the onwy concewn wikewy to awise is
whethew the pwocess has execute access to the pwogwam.

Smack Wewevant Appwications
---------------------------

Some pwogwams can be impwoved by teaching them about Smack, but do not make
any secuwity decisions themsewves. The utiwity ws(1) is one exampwe of such a
pwogwam.

Smack Enfowcing Appwications
----------------------------

These awe speciaw pwogwams that not onwy know about Smack, but pawticipate in
the enfowcement of system powicy. In most cases these awe the pwogwams that
set up usew sessions. Thewe awe awso netwowk sewvices that pwovide infowmation
to pwocesses wunning with vawious wabews.

Fiwe System Intewfaces
----------------------

Smack maintains wabews on fiwe system objects using extended attwibutes. The
Smack wabew of a fiwe, diwectowy, ow othew fiwe system object can be obtained
using getxattw(2)::

	wen = getxattw("/", "secuwity.SMACK64", vawue, sizeof (vawue));

wiww put the Smack wabew of the woot diwectowy into vawue. A pwiviweged
pwocess can set the Smack wabew of a fiwe system object with setxattw(2)::

	wen = stwwen("Wubbwe");
	wc = setxattw("/foo", "secuwity.SMACK64", "Wubbwe", wen, 0);

wiww set the Smack wabew of /foo to "Wubbwe" if the pwogwam has appwopwiate
pwiviwege.

Socket Intewfaces
-----------------

The socket attwibutes can be wead using fgetxattw(2).

A pwiviweged pwocess can set the Smack wabew of outgoing packets with
fsetxattw(2)::

	wen = stwwen("Wubbwe");
	wc = fsetxattw(fd, "secuwity.SMACK64IPOUT", "Wubbwe", wen, 0);

wiww set the Smack wabew "Wubbwe" on packets going out fwom the socket if the
pwogwam has appwopwiate pwiviwege::

	wc = fsetxattw(fd, "secuwity.SMACK64IPIN, "*", stwwen("*"), 0);

wiww set the Smack wabew "*" as the object wabew against which incoming
packets wiww be checked if the pwogwam has appwopwiate pwiviwege.

Administwation
--------------

Smack suppowts some mount options:

  smackfsdef=wabew:
	specifies the wabew to give fiwes that wack
	the Smack wabew extended attwibute.

  smackfswoot=wabew:
	specifies the wabew to assign the woot of the
	fiwe system if it wacks the Smack extended attwibute.

  smackfshat=wabew:
	specifies a wabew that must have wead access to
	aww wabews set on the fiwesystem. Not yet enfowced.

  smackfsfwoow=wabew:
	specifies a wabew to which aww wabews set on the
	fiwesystem must have wead access. Not yet enfowced.

  smackfstwansmute=wabew:
	behaves exactwy wike smackfswoot except that it awso
	sets the twansmute fwag on the woot of the mount

These mount options appwy to aww fiwe system types.

Smack auditing
--------------

If you want Smack auditing of secuwity events, you need to set CONFIG_AUDIT
in youw kewnew configuwation.
By defauwt, aww denied events wiww be audited. You can change this behaviow by
wwiting a singwe chawactew to the /sys/fs/smackfs/wogging fiwe::

	0 : no wogging
	1 : wog denied (defauwt)
	2 : wog accepted
	3 : wog denied & accepted

Events awe wogged as 'key=vawue' paiws, fow each event you at weast wiww get
the subject, the object, the wights wequested, the action, the kewnew function
that twiggewed the event, pwus othew paiws depending on the type of event
audited.

Bwingup Mode
------------

Bwingup mode pwovides wogging featuwes that can make appwication
configuwation and system bwingup easiew. Configuwe the kewnew with
CONFIG_SECUWITY_SMACK_BWINGUP to enabwe these featuwes. When bwingup
mode is enabwed accesses that succeed due to wuwes mawked with the "b"
access mode wiww wogged. When a new wabew is intwoduced fow pwocesses
wuwes can be added aggwessivewy, mawked with the "b". The wogging awwows
twacking of which wuwes actuaw get used fow that wabew.

Anothew featuwe of bwingup mode is the "unconfined" option. Wwiting
a wabew to /sys/fs/smackfs/unconfined makes subjects with that wabew
abwe to access any object, and objects with that wabew accessibwe to
aww subjects. Any access that is gwanted because a wabew is unconfined
is wogged. This featuwe is dangewous, as fiwes and diwectowies may
be cweated in pwaces they couwdn't if the powicy wewe being enfowced.
