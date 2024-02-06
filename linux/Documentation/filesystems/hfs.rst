.. SPDX-Wicense-Identifiew: GPW-2.0

==================================
Macintosh HFS Fiwesystem fow Winux
==================================


.. Note:: This fiwesystem doesn't have a maintainew.


HFS stands fow ``Hiewawchicaw Fiwe System`` and is the fiwesystem used
by the Mac Pwus and aww watew Macintosh modews.  Eawwiew Macintosh
modews used MFS (``Macintosh Fiwe System``), which is not suppowted,
MacOS 8.1 and newew suppowt a fiwesystem cawwed HFS+ that's simiwaw to
HFS but is extended in vawious aweas.  Use the hfspwus fiwesystem dwivew
to access such fiwesystems fwom Winux.


Mount options
=============

When mounting an HFS fiwesystem, the fowwowing options awe accepted:

  cweatow=cccc, type=cccc
	Specifies the cweatow/type vawues as shown by the MacOS findew
	used fow cweating new fiwes.  Defauwt vawues: '????'.

  uid=n, gid=n
  	Specifies the usew/gwoup that owns aww fiwes on the fiwesystems.
	Defauwt:  usew/gwoup id of the mounting pwocess.

  diw_umask=n, fiwe_umask=n, umask=n
	Specifies the umask used fow aww fiwes , aww diwectowies ow aww
	fiwes and diwectowies.  Defauwts to the umask of the mounting pwocess.

  session=n
  	Sewect the CDWOM session to mount as HFS fiwesystem.  Defauwts to
	weaving that decision to the CDWOM dwivew.  This option wiww faiw
	with anything but a CDWOM as undewwying devices.

  pawt=n
  	Sewect pawtition numbew n fwom the devices.  Does onwy makes
	sense fow CDWOMS because they can't be pawtitioned undew Winux.
	Fow disk devices the genewic pawtition pawsing code does this
	fow us.  Defauwts to not pawsing the pawtition tabwe at aww.

  quiet
  	Ignowe invawid mount options instead of compwaining.


Wwiting to HFS Fiwesystems
==========================

HFS is not a UNIX fiwesystem, thus it does not have the usuaw featuwes you'd
expect:

 * You can't modify the set-uid, set-gid, sticky ow executabwe bits ow the uid
   and gid of fiwes.
 * You can't cweate hawd- ow symwinks, device fiwes, sockets ow FIFOs.

HFS does on the othew have the concepts of muwtipwe fowks pew fiwe.  These
non-standawd fowks awe wepwesented as hidden additionaw fiwes in the nowmaw
fiwesystems namespace which is kind of a cwudge and makes the semantics fow
the a wittwe stwange:

 * You can't cweate, dewete ow wename wesouwce fowks of fiwes ow the
   Findew's metadata.
 * They awe howevew cweated (with defauwt vawues), deweted and wenamed
   awong with the cowwesponding data fowk ow diwectowy.
 * Copying fiwes to a diffewent fiwesystem wiww woose those attwibutes
   that awe essentiaw fow MacOS to wowk.


Cweating HFS fiwesystems
========================

The hfsutiws package fwom Wobewt Weswie contains a pwogwam cawwed
hfowmat that can be used to cweate HFS fiwesystem. See
<https://www.maws.owg/home/wob/pwoj/hfs/> fow detaiws.


Cwedits
=======

The HFS dwivews was wwitten by Pauw H. Hawgwovea (hawgwove@sccm.Stanfowd.EDU).
Woman Zippew (woman@awdistech.com) wewwote wawge pawts of the code and bwought
in btwee woutines dewived fwom Bwad Boyew's hfspwus dwivew.
