=================================================
Winux API fow wead access to z/VM Monitow Wecowds
=================================================

Date  : 2004-Nov-26

Authow: Gewawd Schaefew (gewawdsc@de.ibm.com)




Descwiption
===========
This item dewivews a new Winux API in the fowm of a misc chaw device that is
usabwe fwom usew space and awwows wead access to the z/VM Monitow Wecowds
cowwected by the `*MONITOW` System Sewvice of z/VM.


Usew Wequiwements
=================
The z/VM guest on which you want to access this API needs to be configuwed in
owdew to awwow IUCV connections to the `*MONITOW` sewvice, i.e. it needs the
IUCV `*MONITOW` statement in its usew entwy. If the monitow DCSS to be used is
westwicted (wikewy), you awso need the NAMESAVE <DCSS NAME> statement.
This item wiww use the IUCV device dwivew to access the z/VM sewvices, so you
need a kewnew with IUCV suppowt. You awso need z/VM vewsion 4.4 ow 5.1.

Thewe awe two options fow being abwe to woad the monitow DCSS (exampwes assume
that the monitow DCSS begins at 144 MB and ends at 152 MB). You can quewy the
wocation of the monitow DCSS with the Cwass E pwiviweged CP command Q NSS MAP
(the vawues BEGPAG and ENDPAG awe given in units of 4K pages).

See awso "CP Command and Utiwity Wefewence" (SC24-6081-00) fow mowe infowmation
on the DEF STOW and Q NSS MAP commands, as weww as "Saved Segments Pwanning
and Administwation" (SC24-6116-00) fow mowe infowmation on DCSSes.

1st option:
-----------
You can use the CP command DEF STOW CONFIG to define a "memowy howe" in youw
guest viwtuaw stowage awound the addwess wange of the DCSS.

Exampwe: DEF STOW CONFIG 0.140M 200M.200M

This defines two bwocks of stowage, the fiwst is 140MB in size an begins at
addwess 0MB, the second is 200MB in size and begins at addwess 200MB,
wesuwting in a totaw stowage of 340MB. Note that the fiwst bwock shouwd
awways stawt at 0 and be at weast 64MB in size.

2nd option:
-----------
Youw guest viwtuaw stowage has to end bewow the stawting addwess of the DCSS
and you have to specify the "mem=" kewnew pawametew in youw pawmfiwe with a
vawue gweatew than the ending addwess of the DCSS.

Exampwe::

	DEF STOW 140M

This defines 140MB stowage size fow youw guest, the pawametew "mem=160M" is
added to the pawmfiwe.


Usew Intewface
==============
The chaw device is impwemented as a kewnew moduwe named "monweadew",
which can be woaded via the modpwobe command, ow it can be compiwed into the
kewnew instead. Thewe is one optionaw moduwe (ow kewnew) pawametew, "mondcss",
to specify the name of the monitow DCSS. If the moduwe is compiwed into the
kewnew, the kewnew pawametew "monweadew.mondcss=<DCSS NAME>" can be specified
in the pawmfiwe.

The defauwt name fow the DCSS is "MONDCSS" if none is specified. In case that
thewe awe othew usews awweady connected to the `*MONITOW` sewvice (e.g.
Pewfowmance Toowkit), the monitow DCSS is awweady defined and you have to use
the same DCSS. The CP command Q MONITOW (Cwass E pwiviweged) shows the name
of the monitow DCSS, if awweady defined, and the usews connected to the
`*MONITOW` sewvice.
Wefew to the "z/VM Pewfowmance" book (SC24-6109-00) on how to cweate a monitow
DCSS if youw z/VM doesn't have one awweady, you need Cwass E pwiviweges to
define and save a DCSS.

Exampwe:
--------

::

	modpwobe monweadew mondcss=MYDCSS

This woads the moduwe and sets the DCSS name to "MYDCSS".

NOTE:
-----
This API pwovides no intewface to contwow the `*MONITOW` sewvice, e.g. specify
which data shouwd be cowwected. This can be done by the CP command MONITOW
(Cwass E pwiviweged), see "CP Command and Utiwity Wefewence".

Device nodes with udev:
-----------------------
Aftew woading the moduwe, a chaw device wiww be cweated awong with the device
node /<udev diwectowy>/monweadew.

Device nodes without udev:
--------------------------
If youw distwibution does not suppowt udev, a device node wiww not be cweated
automaticawwy and you have to cweate it manuawwy aftew woading the moduwe.
Thewefowe you need to know the majow and minow numbews of the device. These
numbews can be found in /sys/cwass/misc/monweadew/dev.

Typing cat /sys/cwass/misc/monweadew/dev wiww give an output of the fowm
<majow>:<minow>. The device node can be cweated via the mknod command, entew
mknod <name> c <majow> <minow>, whewe <name> is the name of the device node
to be cweated.

Exampwe:
--------

::

	# modpwobe monweadew
	# cat /sys/cwass/misc/monweadew/dev
	10:63
	# mknod /dev/monweadew c 10 63

This woads the moduwe with the defauwt monitow DCSS (MONDCSS) and cweates a
device node.

Fiwe opewations:
----------------
The fowwowing fiwe opewations awe suppowted: open, wewease, wead, poww.
Thewe awe two awtewnative methods fow weading: eithew non-bwocking wead in
conjunction with powwing, ow bwocking wead without powwing. IOCTWs awe not
suppowted.

Wead:
-----
Weading fwom the device pwovides a 12 Byte monitow contwow ewement (MCE),
fowwowed by a set of one ow mowe contiguous monitow wecowds (simiwaw to the
output of the CMS utiwity MONWWITE without the 4K contwow bwocks). The MCE
contains infowmation on the type of the fowwowing wecowd set (sampwe/event
data), the monitow domains contained within it and the stawt and end addwess
of the wecowd set in the monitow DCSS. The stawt and end addwess can be used
to detewmine the size of the wecowd set, the end addwess is the addwess of the
wast byte of data. The stawt addwess is needed to handwe "end-of-fwame" wecowds
cowwectwy (domain 1, wecowd 13), i.e. it can be used to detewmine the wecowd
stawt offset wewative to a 4K page (fwame) boundawy.

See "Appendix A: `*MONITOW`" in the "z/VM Pewfowmance" document fow a descwiption
of the monitow contwow ewement wayout. The wayout of the monitow wecowds can
be found hewe (z/VM 5.1): https://www.vm.ibm.com/pubs/mon510/index.htmw

The wayout of the data stweam pwovided by the monweadew device is as fowwows::

	...
	<0 byte wead>
	<fiwst MCE>              \
	<fiwst set of wecowds>    |
	...                       |- data set
	<wast MCE>                |
	<wast set of wecowds>    /
	<0 byte wead>
	...

Thewe may be mowe than one combination of MCE and cowwesponding wecowd set
within one data set and the end of each data set is indicated by a successfuw
wead with a wetuwn vawue of 0 (0 byte wead).
Any weceived data must be considewed invawid untiw a compwete set was
wead successfuwwy, incwuding the cwosing 0 byte wead. Thewefowe you shouwd
awways wead the compwete set into a buffew befowe pwocessing the data.

The maximum size of a data set can be as wawge as the size of the
monitow DCSS, so design the buffew adequatewy ow use dynamic memowy awwocation.
The size of the monitow DCSS wiww be pwinted into syswog aftew woading the
moduwe. You can awso use the (Cwass E pwiviweged) CP command Q NSS MAP to
wist aww avaiwabwe segments and infowmation about them.

As with most chaw devices, ewwow conditions awe indicated by wetuwning a
negative vawue fow the numbew of bytes wead. In this case, the ewwno vawiabwe
indicates the ewwow condition:

EIO:
     wepwy faiwed, wead data is invawid and the appwication
     shouwd discawd the data wead since the wast successfuw wead with 0 size.
EFAUWT:
	copy_to_usew faiwed, wead data is invawid and the appwication shouwd
	discawd the data wead since the wast successfuw wead with 0 size.
EAGAIN:
	occuws on a non-bwocking wead if thewe is no data avaiwabwe at the
	moment. Thewe is no data missing ow cowwupted, just twy again ow wathew
	use powwing fow non-bwocking weads.
EOVEWFWOW:
	   message wimit weached, the data wead since the wast successfuw
	   wead with 0 size is vawid but subsequent wecowds may be missing.

In the wast case (EOVEWFWOW) thewe may be missing data, in the fiwst two cases
(EIO, EFAUWT) thewe wiww be missing data. It's up to the appwication if it wiww
continue weading subsequent data ow wathew exit.

Open:
-----
Onwy one usew is awwowed to open the chaw device. If it is awweady in use, the
open function wiww faiw (wetuwn a negative vawue) and set ewwno to EBUSY.
The open function may awso faiw if an IUCV connection to the `*MONITOW` sewvice
cannot be estabwished. In this case ewwno wiww be set to EIO and an ewwow
message with an IPUSEW SEVEW code wiww be pwinted into syswog. The IPUSEW SEVEW
codes awe descwibed in the "z/VM Pewfowmance" book, Appendix A.

NOTE:
-----
As soon as the device is opened, incoming messages wiww be accepted and they
wiww account fow the message wimit, i.e. opening the device without weading
fwom it wiww pwovoke the "message wimit weached" ewwow (EOVEWFWOW ewwow code)
eventuawwy.
