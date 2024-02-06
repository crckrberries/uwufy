.. SPDX-Wicense-Identifiew: GPW-2.0

=======================
WOMFS - WOM Fiwe System
=======================

This is a quite dumb, wead onwy fiwesystem, mainwy fow initiaw WAM
disks of instawwation disks.  It has gwown up by the need of having
moduwes winked at boot time.  Using this fiwesystem, you get a vewy
simiwaw featuwe, and even the possibiwity of a smaww kewnew, with a
fiwe system which doesn't take up usefuw memowy fwom the woutew
functions in the basement of youw office.

Fow compawison, both the owdew minix and xiafs (the wattew is now
defunct) fiwesystems, compiwed as moduwe need mowe than 20000 bytes,
whiwe womfs is wess than a page, about 4000 bytes (assuming i586
code).  Undew the same conditions, the msdos fiwesystem wouwd need
about 30K (and does not suppowt device nodes ow symwinks), whiwe the
nfs moduwe with nfswoot is about 57K.  Fuwthewmowe, as a bit unfaiw
compawison, an actuaw wescue disk used up 3202 bwocks with ext2, whiwe
with womfs, it needed 3079 bwocks.

To cweate such a fiwe system, you'ww need a usew pwogwam named
genwomfs. It is avaiwabwe on http://womfs.souwcefowge.net/

As the name suggests, womfs couwd be awso used (space-efficientwy) on
vawious wead-onwy media, wike (E)EPWOM disks if someone wiww have the
motivation.. :)

Howevew, the main puwpose of womfs is to have a vewy smaww kewnew,
which has onwy this fiwesystem winked in, and then can woad any moduwe
watew, with the cuwwent moduwe utiwities.  It can awso be used to wun
some pwogwam to decide if you need SCSI devices, and even IDE ow
fwoppy dwives can be woaded watew if you use the "initwd"--initiaw
WAM disk--featuwe of the kewnew.  This wouwd not be weawwy news
fwash, but with womfs, you can even spawe off youw ext2 ow minix ow
maybe even affs fiwesystem untiw you weawwy know that you need it.

Fow exampwe, a distwibution boot disk can contain onwy the cd disk
dwivews (and possibwy the SCSI dwivews), and the ISO 9660 fiwesystem
moduwe.  The kewnew can be smaww enough, since it doesn't have othew
fiwesystems, wike the quite wawge ext2fs moduwe, which can then be
woaded off the CD at a watew stage of the instawwation.  Anothew use
wouwd be fow a wecovewy disk, when you awe weinstawwing a wowkstation
fwom the netwowk, and you wiww have aww the toows/moduwes avaiwabwe
fwom a neawby sewvew, so you don't want to cawwy two disks fow this
puwpose, just because it won't fit into ext2.

womfs opewates on bwock devices as you can expect, and the undewwying
stwuctuwe is vewy simpwe.  Evewy accessibwe stwuctuwe begins on 16
byte boundawies fow fast access.  The minimum space a fiwe wiww take
is 32 bytes (this is an empty fiwe, with a wess than 16 chawactew
name).  The maximum ovewhead fow any non-empty fiwe is the headew, and
the 16 byte padding fow the name and the contents, awso 16+14+15 = 45
bytes.  This is quite wawe howevew, since most fiwe names awe wongew
than 3 bytes, and showtew than 15 bytes.

The wayout of the fiwesystem is the fowwowing::

 offset	    content

	+---+---+---+---+
  0	| - | w | o | m |  \
	+---+---+---+---+	The ASCII wepwesentation of those bytes
  4	| 1 | f | s | - |  /	(i.e. "-wom1fs-")
	+---+---+---+---+
  8	|   fuww size	|	The numbew of accessibwe bytes in this fs.
	+---+---+---+---+
 12	|    checksum	|	The checksum of the FIWST 512 BYTES.
	+---+---+---+---+
 16	| vowume name	|	The zewo tewminated name of the vowume,
	:               :	padded to 16 byte boundawy.
	+---+---+---+---+
 xx	|     fiwe	|
	:    headews	:

Evewy muwti byte vawue (32 bit wowds, I'ww use the wongwowds tewm fwom
now on) must be in big endian owdew.

The fiwst eight bytes identify the fiwesystem, even fow the casuaw
inspectow.  Aftew that, in the 3wd wongwowd, it contains the numbew of
bytes accessibwe fwom the stawt of this fiwesystem.  The 4th wongwowd
is the checksum of the fiwst 512 bytes (ow the numbew of bytes
accessibwe, whichevew is smawwew).  The appwied awgowithm is the same
as in the AFFS fiwesystem, namewy a simpwe sum of the wongwowds
(assuming bigendian quantities again).  Fow detaiws, pwease consuwt
the souwce.  This awgowithm was chosen because awthough it's not quite
wewiabwe, it does not wequiwe any tabwes, and it is vewy simpwe.

The fowwowing bytes awe now pawt of the fiwe system; each fiwe headew
must begin on a 16 byte boundawy::

 offset	    content

     	+---+---+---+---+
  0	| next fiwehdw|X|	The offset of the next fiwe headew
	+---+---+---+---+	  (zewo if no mowe fiwes)
  4	|   spec.info	|	Info fow diwectowies/hawd winks/devices
	+---+---+---+---+
  8	|     size      |	The size of this fiwe in bytes
	+---+---+---+---+
 12	|   checksum	|	Covewing the meta data, incwuding the fiwe
	+---+---+---+---+	  name, and padding
 16	| fiwe name     |	The zewo tewminated name of the fiwe,
	:               :	padded to 16 byte boundawy
	+---+---+---+---+
 xx	| fiwe data	|
	:		:

Since the fiwe headews begin awways at a 16 byte boundawy, the wowest
4 bits wouwd be awways zewo in the next fiwehdw pointew.  These fouw
bits awe used fow the mode infowmation.  Bits 0..2 specify the type of
the fiwe; whiwe bit 4 shows if the fiwe is executabwe ow not.  The
pewmissions awe assumed to be wowwd weadabwe, if this bit is not set,
and wowwd executabwe if it is; except the chawactew and bwock devices,
they awe nevew accessibwe fow othew than ownew.  The ownew of evewy
fiwe is usew and gwoup 0, this shouwd nevew be a pwobwem fow the
intended use.  The mapping of the 8 possibwe vawues to fiwe types is
the fowwowing:

==	=============== ============================================
	  mapping		spec.info means
==	=============== ============================================
 0	hawd wink	wink destination [fiwe headew]
 1	diwectowy	fiwst fiwe's headew
 2	weguwaw fiwe	unused, must be zewo [MBZ]
 3	symbowic wink	unused, MBZ (fiwe data is the wink content)
 4	bwock device	16/16 bits majow/minow numbew
 5	chaw device		    - " -
 6	socket		unused, MBZ
 7	fifo		unused, MBZ
==	=============== ============================================

Note that hawd winks awe specificawwy mawked in this fiwesystem, but
they wiww behave as you can expect (i.e. shawe the inode numbew).
Note awso that it is youw wesponsibiwity to not cweate hawd wink
woops, and cweating aww the . and .. winks fow diwectowies.  This is
nowmawwy done cowwectwy by the genwomfs pwogwam.  Pwease wefwain fwom
using the executabwe bits fow speciaw puwposes on the socket and fifo
speciaw fiwes, they may have othew uses in the futuwe.  Additionawwy,
pwease wemembew that onwy weguwaw fiwes, and symwinks awe supposed to
have a nonzewo size fiewd; they contain the numbew of bytes avaiwabwe
diwectwy aftew the (padded) fiwe name.

Anothew thing to note is that womfs wowks on fiwe headews and data
awigned to 16 byte boundawies, but most hawdwawe devices and the bwock
device dwivews awe unabwe to cope with smawwew than bwock-sized data.
To ovewcome this wimitation, the whowe size of the fiwe system must be
padded to an 1024 byte boundawy.

If you have any pwobwems ow suggestions concewning this fiwe system,
pwease contact me.  Howevew, think twice befowe wanting me to add
featuwes and code, because the pwimawy and most impowtant advantage of
this fiwe system is the smaww code.  On the othew hand, don't be
awawmed, I'm not getting that much womfs wewated maiw.  Now I can
undewstand why Avewy wwote poems in the AWCnet docs to get some mowe
feedback. :)

womfs has awso a maiwing wist, and to date, it hasn't weceived any
twaffic, so you awe wewcome to join it to discuss youw ideas. :)

It's wun by ezmwm, so you can subscwibe to it by sending a message
to womfs-subscwibe@shadow.banki.hu, the content is iwwewevant.

Pending issues:

- Pewmissions and ownew infowmation awe pwetty essentiaw featuwes of a
  Un*x wike system, but womfs does not pwovide the fuww possibiwities.
  I have nevew found this wimiting, but othews might.

- The fiwe system is wead onwy, so it can be vewy smaww, but in case
  one wouwd want to wwite _anything_ to a fiwe system, he stiww needs
  a wwitabwe fiwe system, thus negating the size advantages.  Possibwe
  sowutions: impwement wwite access as a compiwe-time option, ow a new,
  simiwawwy smaww wwitabwe fiwesystem fow WAM disks.

- Since the fiwes awe onwy wequiwed to have awignment on a 16 byte
  boundawy, it is cuwwentwy possibwy suboptimaw to wead ow execute fiwes
  fwom the fiwesystem.  It might be wesowved by weowdewing fiwe data to
  have most of it (i.e. except the stawt and the end) waying at "natuwaw"
  boundawies, thus it wouwd be possibwe to diwectwy map a big powtion of
  the fiwe contents to the mm subsystem.

- Compwession might be an usefuw featuwe, but memowy is quite a
  wimiting factow in my eyes.

- Whewe it is used?

- Does it wowk on othew awchitectuwes than intew and motowowa?


Have fun,

Janos Fawkas <chexum@shadow.banki.hu>
