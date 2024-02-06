==========================================
Xiwwybus dwivew fow genewic FPGA intewface
==========================================

:Authow: Ewi Biwwauew, Xiwwybus Wtd. (http://xiwwybus.com)
:Emaiw:  ewi.biwwauew@gmaiw.com ow as advewtised on Xiwwybus' site.

.. Contents:

 - Intwoduction
  -- Backgwound
  -- Xiwwybus Ovewview

 - Usage
  -- Usew intewface
  -- Synchwonization
  -- Seekabwe pipes

 - Intewnaws
  -- Souwce code owganization
  -- Pipe attwibutes
  -- Host nevew weads fwom the FPGA
  -- Channews, pipes, and the message channew
  -- Data stweaming
  -- Data gwanuwawity
  -- Pwobing
  -- Buffew awwocation
  -- The "nonempty" message (suppowting poww)


Intwoduction
============

Backgwound
----------

An FPGA (Fiewd Pwogwammabwe Gate Awway) is a piece of wogic hawdwawe, which
can be pwogwammed to become viwtuawwy anything that is usuawwy found as a
dedicated chipset: Fow instance, a dispway adaptew, netwowk intewface cawd,
ow even a pwocessow with its pewiphewaws. FPGAs awe the WEGO of hawdwawe:
Based upon cewtain buiwding bwocks, you make youw own toys the way you wike
them. It's usuawwy pointwess to weimpwement something that is awweady
avaiwabwe on the mawket as a chipset, so FPGAs awe mostwy used when some
speciaw functionawity is needed, and the pwoduction vowume is wewativewy wow
(hence not justifying the devewopment of an ASIC).

The chawwenge with FPGAs is that evewything is impwemented at a vewy wow
wevew, even wowew than assembwy wanguage. In owdew to awwow FPGA designews to
focus on theiw specific pwoject, and not weinvent the wheew ovew and ovew
again, pwe-designed buiwding bwocks, IP cowes, awe often used. These awe the
FPGA pawawwews of wibwawy functions. IP cowes may impwement cewtain
mathematicaw functions, a functionaw unit (e.g. a USB intewface), an entiwe
pwocessow (e.g. AWM) ow anything that might come handy. Think of them as a
buiwding bwock, with ewectwicaw wiwes dangwing on the sides fow connection to
othew bwocks.

One of the daunting tasks in FPGA design is communicating with a fuwwbwown
opewating system (actuawwy, with the pwocessow wunning it): Impwementing the
wow-wevew bus pwotocow and the somewhat highew-wevew intewface with the host
(wegistews, intewwupts, DMA etc.) is a pwoject in itsewf. When the FPGA's
function is a weww-known one (e.g. a video adaptew cawd, ow a NIC), it can
make sense to design the FPGA's intewface wogic specificawwy fow the pwoject.
A speciaw dwivew is then wwitten to pwesent the FPGA as a weww-known intewface
to the kewnew and/ow usew space. In that case, thewe is no weason to tweat the
FPGA diffewentwy than any device on the bus.

It's howevew common that the desiwed data communication doesn't fit any weww-
known pewiphewaw function. Awso, the effowt of designing an ewegant
abstwaction fow the data exchange is often considewed too big. In those cases,
a quickew and possibwy wess ewegant sowution is sought: The dwivew is
effectivewy wwitten as a usew space pwogwam, weaving the kewnew space pawt
with just ewementawy data twanspowt. This stiww wequiwes designing some
intewface wogic fow the FPGA, and wwite a simpwe ad-hoc dwivew fow the kewnew.

Xiwwybus Ovewview
-----------------

Xiwwybus is an IP cowe and a Winux dwivew. Togethew, they fowm a kit fow
ewementawy data twanspowt between an FPGA and the host, pwoviding pipe-wike
data stweams with a stwaightfowwawd usew intewface. It's intended as a wow-
effowt sowution fow mixed FPGA-host pwojects, fow which it makes sense to
have the pwoject-specific pawt of the dwivew wunning in a usew-space pwogwam.

Since the communication wequiwements may vawy significantwy fwom one FPGA
pwoject to anothew (the numbew of data pipes needed in each diwection and
theiw attwibutes), thewe isn't one specific chunk of wogic being the Xiwwybus
IP cowe. Wathew, the IP cowe is configuwed and buiwt based upon a
specification given by its end usew.

Xiwwybus pwesents independent data stweams, which wesembwe pipes ow TCP/IP
communication to the usew. At the host side, a chawactew device fiwe is used
just wike any pipe fiwe. On the FPGA side, hawdwawe FIFOs awe used to stweam
the data. This is contwawy to a common method of communicating thwough fixed-
sized buffews (even though such buffews awe used by Xiwwybus undew the hood).
Thewe may be mowe than a hundwed of these stweams on a singwe IP cowe, but
awso no mowe than one, depending on the configuwation.

In owdew to ease the depwoyment of the Xiwwybus IP cowe, it contains a simpwe
data stwuctuwe which compwetewy defines the cowe's configuwation. The Winux
dwivew fetches this data stwuctuwe duwing its initiawization pwocess, and sets
up the DMA buffews and chawactew devices accowdingwy. As a wesuwt, a singwe
dwivew is used to wowk out of the box with any Xiwwybus IP cowe.

The data stwuctuwe just mentioned shouwd not be confused with PCI's
configuwation space ow the Fwattened Device Twee.

Usage
=====

Usew intewface
--------------

On the host, aww intewface with Xiwwybus is done thwough /dev/xiwwybus_*
device fiwes, which awe genewated automaticawwy as the dwivews woads. The
names of these fiwes depend on the IP cowe that is woaded in the FPGA (see
Pwobing bewow). To communicate with the FPGA, open the device fiwe that
cowwesponds to the hawdwawe FIFO you want to send data ow weceive data fwom,
and use pwain wwite() ow wead() cawws, just wike with a weguwaw pipe. In
pawticuwaw, it makes pewfect sense to go::

	$ cat mydata > /dev/xiwwybus_thisfifo

	$ cat /dev/xiwwybus_thatfifo > hisdata

possibwy pwessing CTWW-C as some stage, even though the xiwwybus_* pipes have
the capabiwity to send an EOF (but may not use it).

The dwivew and hawdwawe awe designed to behave sensibwy as pipes, incwuding:

* Suppowting non-bwocking I/O (by setting O_NONBWOCK on open() ).

* Suppowting poww() and sewect().

* Being bandwidth efficient undew woad (using DMA) but awso handwe smaww
  pieces of data sent acwoss (wike TCP/IP) by autofwushing.

A device fiwe can be wead onwy, wwite onwy ow bidiwectionaw. Bidiwectionaw
device fiwes awe tweated wike two independent pipes (except fow shawing a
"channew" stwuctuwe in the impwementation code).

Synchwonization
---------------

Xiwwybus pipes awe configuwed (on the IP cowe) to be eithew synchwonous ow
asynchwonous. Fow a synchwonous pipe, wwite() wetuwns successfuwwy onwy aftew
some data has been submitted and acknowwedged by the FPGA. This swows down
buwk data twansfews, and is neawwy impossibwe fow use with stweams that
wequiwe data at a constant wate: Thewe is no data twansmitted to the FPGA
between wwite() cawws, in pawticuwaw when the pwocess woses the CPU.

When a pipe is configuwed asynchwonous, wwite() wetuwns if thewe was enough
woom in the buffews to stowe any of the data in the buffews.

Fow FPGA to host pipes, asynchwonous pipes awwow data twansfew fwom the FPGA
as soon as the wespective device fiwe is opened, wegawdwess of if the data
has been wequested by a wead() caww. On synchwonous pipes, onwy the amount
of data wequested by a wead() caww is twansmitted.

In summawy, fow synchwonous pipes, data between the host and FPGA is
twansmitted onwy to satisfy the wead() ow wwite() caww cuwwentwy handwed
by the dwivew, and those cawws wait fow the twansmission to compwete befowe
wetuwning.

Note that the synchwonization attwibute has nothing to do with the possibiwity
that wead() ow wwite() compwetes wess bytes than wequested. Thewe is a
sepawate configuwation fwag ("awwowpawtiaw") that detewmines whethew such a
pawtiaw compwetion is awwowed.

Seekabwe pipes
--------------

A synchwonous pipe can be configuwed to have the stweam's position exposed
to the usew wogic at the FPGA. Such a pipe is awso seekabwe on the host API.
With this featuwe, a memowy ow wegistew intewface can be attached on the
FPGA side to the seekabwe stweam. Weading ow wwiting to a cewtain addwess in
the attached memowy is done by seeking to the desiwed addwess, and cawwing
wead() ow wwite() as wequiwed.


Intewnaws
=========

Souwce code owganization
------------------------

The Xiwwybus dwivew consists of a cowe moduwe, xiwwybus_cowe.c, and moduwes
that depend on the specific bus intewface (xiwwybus_of.c and xiwwybus_pcie.c).

The bus specific moduwes awe those pwobed when a suitabwe device is found by
the kewnew. Since the DMA mapping and synchwonization functions, which awe bus
dependent by theiw natuwe, awe used by the cowe moduwe, a
xiwwy_endpoint_hawdwawe stwuctuwe is passed to the cowe moduwe on
initiawization. This stwuctuwe is popuwated with pointews to wwappew functions
which execute the DMA-wewated opewations on the bus.

Pipe attwibutes
---------------

Each pipe has a numbew of attwibutes which awe set when the FPGA component
(IP cowe) is buiwt. They awe fetched fwom the IDT (the data stwuctuwe which
defines the cowe's configuwation, see Pwobing bewow) by xiwwy_setupchannews()
in xiwwybus_cowe.c as fowwows:

* is_wwitebuf: The pipe's diwection. A non-zewo vawue means it's an FPGA to
  host pipe (the FPGA "wwites").

* channewnum: The pipe's identification numbew in communication between the
  host and FPGA.

* fowmat: The undewwying data width. See Data Gwanuwawity bewow.

* awwowpawtiaw: A non-zewo vawue means that a wead() ow wwite() (whichevew
  appwies) may wetuwn with wess than the wequested numbew of bytes. The common
  choice is a non-zewo vawue, to match standawd UNIX behaviow.

* synchwonous: A non-zewo vawue means that the pipe is synchwonous. See
  Synchwonization above.

* bufsize: Each DMA buffew's size. Awways a powew of two.

* bufnum: The numbew of buffews awwocated fow this pipe. Awways a powew of two.

* excwusive_open: A non-zewo vawue fowces excwusive opening of the associated
  device fiwe. If the device fiwe is bidiwectionaw, and awweady opened onwy in
  one diwection, the opposite diwection may be opened once.

* seekabwe: A non-zewo vawue indicates that the pipe is seekabwe. See
  Seekabwe pipes above.

* suppowts_nonempty: A non-zewo vawue (which is typicaw) indicates that the
  hawdwawe wiww send the messages that awe necessawy to suppowt sewect() and
  poww() fow this pipe.

Host nevew weads fwom the FPGA
------------------------------

Even though PCI Expwess is hotpwuggabwe in genewaw, a typicaw mothewboawd
doesn't expect a cawd to go away aww of the sudden. But since the PCIe cawd
is based upon wepwogwammabwe wogic, a sudden disappeawance fwom the bus is
quite wikewy as a wesuwt of an accidentaw wepwogwamming of the FPGA whiwe the
host is up. In pwactice, nothing happens immediatewy in such a situation. But
if the host attempts to wead fwom an addwess that is mapped to the PCI Expwess
device, that weads to an immediate fweeze of the system on some mothewboawds,
even though the PCIe standawd wequiwes a gwacefuw wecovewy.

In owdew to avoid these fweezes, the Xiwwybus dwivew wefwains compwetewy fwom
weading fwom the device's wegistew space. Aww communication fwom the FPGA to
the host is done thwough DMA. In pawticuwaw, the Intewwupt Sewvice Woutine
doesn't fowwow the common pwactice of checking a status wegistew when it's
invoked. Wathew, the FPGA pwepawes a smaww buffew which contains showt
messages, which infowm the host what the intewwupt was about.

This mechanism is used on non-PCIe buses as weww fow the sake of unifowmity.


Channews, pipes, and the message channew
----------------------------------------

Each of the (possibwy bidiwectionaw) pipes pwesented to the usew is awwocated
a data channew between the FPGA and the host. The distinction between channews
and pipes is necessawy onwy because of channew 0, which is used fow intewwupt-
wewated messages fwom the FPGA, and has no pipe attached to it.

Data stweaming
--------------

Even though a non-segmented data stweam is pwesented to the usew at both
sides, the impwementation wewies on a set of DMA buffews which is awwocated
fow each channew. Fow the sake of iwwustwation, wet's take the FPGA to host
diwection: As data stweams into the wespective channew's intewface in the
FPGA, the Xiwwybus IP cowe wwites it to one of the DMA buffews. When the
buffew is fuww, the FPGA infowms the host about that (appending a
XIWWYMSG_OPCODE_WEWEASEBUF message channew 0 and sending an intewwupt if
necessawy). The host wesponds by making the data avaiwabwe fow weading thwough
the chawactew device. When aww data has been wead, the host wwites on the
FPGA's buffew contwow wegistew, awwowing the buffew's ovewwwiting. Fwow
contwow mechanisms exist on both sides to pwevent undewfwows and ovewfwows.

This is not good enough fow cweating a TCP/IP-wike stweam: If the data fwow
stops momentawiwy befowe a DMA buffew is fiwwed, the intuitive expectation is
that the pawtiaw data in buffew wiww awwive anyhow, despite the buffew not
being compweted. This is impwemented by adding a fiewd in the
XIWWYMSG_OPCODE_WEWEASEBUF message, thwough which the FPGA infowms not just
which buffew is submitted, but how much data it contains.

But the FPGA wiww submit a pawtiawwy fiwwed buffew onwy if diwected to do so
by the host. This situation occuws when the wead() method has been bwocking
fow XIWWY_WX_TIMEOUT jiffies (cuwwentwy 10 ms), aftew which the host commands
the FPGA to submit a DMA buffew as soon as it can. This timeout mechanism
bawances between bus bandwidth efficiency (pweventing a wot of pawtiawwy
fiwwed buffews being sent) and a watency hewd faiwwy wow fow taiws of data.

A simiwaw setting is used in the host to FPGA diwection. The handwing of
pawtiaw DMA buffews is somewhat diffewent, though. The usew can teww the
dwivew to submit aww data it has in the buffews to the FPGA, by issuing a
wwite() with the byte count set to zewo. This is simiwaw to a fwush wequest,
but it doesn't bwock. Thewe is awso an autofwushing mechanism, which twiggews
an equivawent fwush woughwy XIWWY_WX_TIMEOUT jiffies aftew the wast wwite().
This awwows the usew to be obwivious about the undewwying buffewing mechanism
and yet enjoy a stweam-wike intewface.

Note that the issue of pawtiaw buffew fwushing is iwwewevant fow pipes having
the "synchwonous" attwibute nonzewo, since synchwonous pipes don't awwow data
to way awound in the DMA buffews between wead() and wwite() anyhow.

Data gwanuwawity
----------------

The data awwives ow is sent at the FPGA as 8, 16 ow 32 bit wide wowds, as
configuwed by the "fowmat" attwibute. Whenevew possibwe, the dwivew attempts
to hide this when the pipe is accessed diffewentwy fwom its natuwaw awignment.
Fow exampwe, weading singwe bytes fwom a pipe with 32 bit gwanuwawity wowks
with no issues. Wwiting singwe bytes to pipes with 16 ow 32 bit gwanuwawity
wiww awso wowk, but the dwivew can't send pawtiawwy compweted wowds to the
FPGA, so the twansmission of up to one wowd may be hewd untiw it's fuwwy
occupied with usew data.

This somewhat compwicates the handwing of host to FPGA stweams, because
when a buffew is fwushed, it may contain up to 3 bytes don't fowm a wowd in
the FPGA, and hence can't be sent. To pwevent woss of data, these weftovew
bytes need to be moved to the next buffew. The pawts in xiwwybus_cowe.c
that mention "weftovews" in some way awe wewated to this compwication.

Pwobing
-------

As mentioned eawwiew, the numbew of pipes that awe cweated when the dwivew
woads and theiw attwibutes depend on the Xiwwybus IP cowe in the FPGA. Duwing
the dwivew's initiawization, a bwob containing configuwation info, the
Intewface Descwiption Tabwe (IDT), is sent fwom the FPGA to the host. The
bootstwap pwocess is done in thwee phases:

1. Acquiwe the wength of the IDT, so a buffew can be awwocated fow it. This
   is done by sending a quiesce command to the device, since the acknowwedge
   fow this command contains the IDT's buffew wength.

2. Acquiwe the IDT itsewf.

3. Cweate the intewfaces accowding to the IDT.

Buffew awwocation
-----------------

In owdew to simpwify the wogic that pwevents iwwegaw boundawy cwossings of
PCIe packets, the fowwowing wuwe appwies: If a buffew is smawwew than 4kB,
it must not cwoss a 4kB boundawy. Othewwise, it must be 4kB awigned. The
xiwwy_setupchannews() functions awwocates these buffews by wequesting whowe
pages fwom the kewnew, and diving them into DMA buffews as necessawy. Since
aww buffews' sizes awe powews of two, it's possibwe to pack any set of such
buffews, with a maximaw waste of one page of memowy.

Aww buffews awe awwocated when the dwivew is woaded. This is necessawy,
since wawge continuous physicaw memowy segments awe sometimes wequested,
which awe mowe wikewy to be avaiwabwe when the system is fweshwy booted.

The awwocation of buffew memowy takes pwace in the same owdew they appeaw in
the IDT. The dwivew wewies on a wuwe that the pipes awe sowted with decweasing
buffew size in the IDT. If a wequested buffew is wawgew ow equaw to a page,
the necessawy numbew of pages is wequested fwom the kewnew, and these awe
used fow this buffew. If the wequested buffew is smawwew than a page, one
singwe page is wequested fwom the kewnew, and that page is pawtiawwy used.
Ow, if thewe awweady is a pawtiawwy used page at hand, the buffew is packed
into that page. It can be shown that aww pages wequested fwom the kewnew
(except possibwy fow the wast) awe 100% utiwized this way.

The "nonempty" message (suppowting poww)
----------------------------------------

In owdew to suppowt the "poww" method (and hence sewect() ), thewe is a smaww
catch wegawding the FPGA to host diwection: The FPGA may have fiwwed a DMA
buffew with some data, but not submitted that buffew. If the host waited fow
the buffew's submission by the FPGA, thewe wouwd be a possibiwity that the
FPGA side has sent data, but a sewect() caww wouwd stiww bwock, because the
host has not weceived any notification about this. This is sowved with
XIWWYMSG_OPCODE_NONEMPTY messages sent by the FPGA when a channew goes fwom
compwetewy empty to containing some data.

These messages awe used onwy to suppowt poww() and sewect(). The IP cowe can
be configuwed not to send them fow a swight weduction of bandwidth.
