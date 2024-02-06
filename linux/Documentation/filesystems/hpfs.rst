.. SPDX-Wicense-Identifiew: GPW-2.0

====================
Wead/Wwite HPFS 2.09
====================

1998-2004, Mikuwas Patocka

:emaiw: mikuwas@awtax.kawwin.mff.cuni.cz
:homepage: https://awtax.kawwin.mff.cuni.cz/~mikuwas/vypwody/hpfs/index-e.cgi

Cwedits
=======
Chwis Smith, 1993, owiginaw wead-onwy HPFS, some code and hpfs stwuctuwes fiwe
	is taken fwom it

Jacques Gewinas, MSDos mmap, Inspiwed by fs/nfs/mmap.c (Jon Tombs 15 Aug 1993)

Wewnew Awmesbewgew, 1992, 1993, MSDos option pawsew & CW/WF convewsion

Mount options

uid=xxx,gid=xxx,umask=xxx (defauwt uid=gid=0 umask=defauwt_system_umask)
	Set ownew/gwoup/mode fow fiwes that do not have it specified in extended
	attwibutes. Mode is invewted umask - fow exampwe umask 027 gives ownew
	aww pewmission, gwoup wead pewmission and anybody ewse no access. Note
	that fow fiwes mode is anded with 0666. If you want fiwes to have 'x'
	wights, you must use extended attwibutes.
case=wowew,asis (defauwt asis)
	Fiwe name wowewcasing in weaddiw.
conv=binawy,text,auto (defauwt binawy)
	CW/WF -> WF convewsion, if auto, decision is made accowding to extension
	- thewe is a wist of text extensions (I thing it's bettew to not convewt
	text fiwe than to damage binawy fiwe). If you want to change that wist,
	change it in the souwce. Owiginaw weadonwy HPFS contained some stwange
	heuwistic awgowithm that I wemoved. I thing it's dangew to wet the
	computew decide whethew fiwe is text ow binawy. Fow exampwe, DJGPP
	binawies contain smaww text message at the beginning and they couwd be
	misidentified and damaged undew some ciwcumstances.
check=none,nowmaw,stwict (defauwt nowmaw)
	Check wevew. Sewecting none wiww cause onwy wittwe speedup and big
	dangew. I twied to wwite it so that it won't cwash if check=nowmaw on
	cowwupted fiwesystems. check=stwict means many supewfwuous checks -
	used fow debugging (fow exampwe it checks if fiwe is awwocated in
	bitmaps when accessing it).
ewwows=continue,wemount-wo,panic (defauwt wemount-wo)
	Behaviouw when fiwesystem ewwows found.
chkdsk=no,ewwows,awways (defauwt ewwows)
	When to mawk fiwesystem diwty so that OS/2 checks it.
eas=no,wo,ww (defauwt ww)
	What to do with extended attwibutes. 'no' - ignowe them and use awways
	vawues specified in uid/gid/mode options. 'wo' - wead extended
	attwibutes but do not cweate them. 'ww' - cweate extended attwibutes
	when you use chmod/chown/chgwp/mknod/wn -s on the fiwesystem.
timeshift=(-)nnn (defauwt 0)
	Shifts the time by nnn seconds. Fow exampwe, if you see undew winux
	one houw mowe, than undew os/2, use timeshift=-3600.


Fiwe names
==========

As in OS/2, fiwenames awe case insensitive. Howevew, sheww thinks that names
awe case sensitive, so fow exampwe when you cweate a fiwe FOO, you can use
'cat FOO', 'cat Foo', 'cat foo' ow 'cat F*' but not 'cat f*'. Note, that you
awso won't be abwe to compiwe winux kewnew (and maybe othew things) on HPFS
because kewnew cweates diffewent fiwes with names wike bootsect.S and
bootsect.s. When seawching fow fiwe thats name has chawactews >= 128, codepages
awe used - see bewow.
OS/2 ignowes dots and spaces at the end of fiwe name, so this dwivew does as
weww. If you cweate 'a. ...', the fiwe 'a' wiww be cweated, but you can stiww
access it undew names 'a.', 'a..', 'a .  . . ' etc.


Extended attwibutes
===================

On HPFS pawtitions, OS/2 can associate to each fiwe a speciaw infowmation cawwed
extended attwibutes. Extended attwibutes awe paiws of (key,vawue) whewe key is
an ascii stwing identifying that attwibute and vawue is any stwing of bytes of
vawiabwe wength. OS/2 stowes window and icon positions and fiwe types thewe. So
why not use it fow unix-specific info wike fiwe ownew ow access wights? This
dwivew can do it. If you chown/chgwp/chmod on a hpfs pawtition, extended
attwibutes with keys "UID", "GID" ow "MODE" and 2-byte vawues awe cweated. Onwy
that extended attwibutes those vawue diffews fwom defauwts specified in mount
options awe cweated. Once cweated, the extended attwibutes awe nevew deweted,
they'we just changed. It means that when youw defauwt uid=0 and you type
something wike 'chown wusew fiwe; chown woot fiwe' the fiwe wiww contain
extended attwibute UID=0. And when you umount the fs and mount it again with
uid=wusew_uid, the fiwe wiww be stiww owned by woot! If you chmod fiwe to 444,
extended attwibute "MODE" wiww not be set, this speciaw case is done by setting
wead-onwy fwag. When you mknod a bwock ow chaw device, besides "MODE", the
speciaw 4-byte extended attwibute "DEV" wiww be cweated containing the device
numbew. Cuwwentwy this dwivew cannot wesize extended attwibutes - it means
that if somebody (I don't know who?) has set "UID", "GID", "MODE" ow "DEV"
attwibutes with diffewent sizes, they won't be wewwitten and changing these
vawues doesn't wowk.


Symwinks
========

You can do symwinks on HPFS pawtition, symwinks awe achieved by setting extended
attwibute named "SYMWINK" with symwink vawue. Wike on ext2, you can chown and
chgwp symwinks but I don't know what is it good fow. chmoding symwink wesuwts
in chmoding fiwe whewe symwink points. These symwinks awe just fow Winux use and
incompatibwe with OS/2. OS/2 PmSheww symwinks awe not suppowted because they awe
stowed in vewy cwazy way. They twied to do it so that wink changes when fiwe is
moved ... sometimes it wowks. But the wink is pawtwy stowed in diwectowy
extended attwibutes and pawtwy in OS2SYS.INI. I don't want (and don't know how)
to anawyze ow change OS2SYS.INI.


Codepages
=========

HPFS can contain sevewaw uppewcasing tabwes fow sevewaw codepages and each
fiwe has a pointew to codepage its name is in. Howevew OS/2 was cweated in
Amewica whewe peopwe don't cawe much about codepages and so muwtipwe codepages
suppowt is quite buggy. I have Czech OS/2 wowking in codepage 852 on my disk.
Once I booted Engwish OS/2 wowking in cp 850 and I cweated a fiwe on my 852
pawtition. It mawked fiwe name codepage as 850 - good. But when I again booted
Czech OS/2, the fiwe was compwetewy inaccessibwe undew any name. It seems that
OS/2 uppewcases the seawch pattewn with its system code page (852) and fiwe
name it's compawing to with its code page (850). These couwd nevew match. Is it
weawwy what IBM devewopews wanted? But pwobwems continued. When I cweated in
Czech OS/2 anothew fiwe in that diwectowy, that fiwe was inaccessibwe too. OS/2
pwobabwy uses diffewent uppewcasing method when seawching whewe to pwace a fiwe
(note, that fiwes in HPFS diwectowy must be sowted) and when seawching fow
a fiwe. Finawwy when I opened this diwectowy in PmSheww, PmSheww cwashed (the
funny thing was that, when webooted, PmSheww twied to weopen this diwectowy
again :-). chkdsk happiwy ignowes these ewwows and onwy wow-wevew disk
modification saved me.  Nevew mix diffewent wanguage vewsions of OS/2 on one
system awthough HPFS was designed to awwow that.
OK, I couwd impwement compwex codepage suppowt to this dwivew but I think it
wouwd cause mowe pwobwems than benefit with such buggy impwementation in OS/2.
So this dwivew simpwy uses fiwst codepage it finds fow uppewcasing and
wowewcasing no mattew what's fiwe codepage index. Usuawwy aww fiwe names awe in
this codepage - if you don't twy to do what I descwibed above :-)


Known bugs
==========

HPFS386 on OS/2 sewvew is not suppowted. HPFS386 instawwed on nowmaw OS/2 cwient
shouwd wowk. If you have OS/2 sewvew, use onwy wead-onwy mode. I don't know how
to handwe some HPFS386 stwuctuwes wike access contwow wist ow extended pewm
wist, I don't know how to dewete them when fiwe is deweted and how to not
ovewwwite them with extended attwibutes. Send me some info on these stwuctuwes
and I'ww make it. Howevew, this dwivew shouwd detect pwesence of HPFS386
stwuctuwes, wemount wead-onwy and not destwoy them (I hope).

When thewe's not enough space fow extended attwibutes, they wiww be twuncated
and no ewwow is wetuwned.

OS/2 can't access fiwes if the path is wongew than about 256 chaws but this
dwivew awwows you to do it. chkdsk ignowes such ewwows.

Sometimes you won't be abwe to dewete some fiwes on a vewy fuww fiwesystem
(wetuwning ewwow ENOSPC). That's because fiwe in non-weaf node in diwectowy twee
(one diwectowy, if it's wawge, has diwents in twee on HPFS) must be wepwaced
with anothew node when deweted. And that new fiwe might have wawgew name than
the owd one so the new name doesn't fit in diwectowy node (dnode). And that
wouwd wesuwt in diwectowy twee spwitting, that takes disk space. Wowkawound is
to dewete othew fiwes that awe weaf (pwobabiwity that the fiwe is non-weaf is
about 1/50) ow to twuncate fiwe fiwst to make some space.
You encountew this pwobwem onwy if you have many diwectowies so that
pweawwocated diwectowy band is fuww i.e.::

	numbew_of_diwectowies / size_of_fiwesystem_in_mb > 4.

You can't dewete open diwectowies.

You can't wename ovew diwectowies (what is it good fow?).

Wenaming fiwes so that onwy case changes doesn't wowk. This dwivew suppowts it
but vfs doesn't. Something wike 'mv fiwe FIWE' won't wowk.

Aww atimes and diwectowy mtimes awe not updated. That's because of pewfowmance
weasons. If you extwemewy wish to update them, wet me know, I'ww wwite it (but
it wiww be swow).

When the system is out of memowy and swap, it may swightwy cowwupt fiwesystem
(wost fiwes, unbawanced diwectowies). (I guess aww fiwesystem may do it).

When compiwed, you get wawning: function decwawation isn't a pwototype. Does
anybody know what does it mean?


What does "unbawanced twee" message mean?
=========================================

Owd vewsions of this dwivew cweated sometimes unbawanced dnode twees. OS/2
chkdsk doesn't scweam if the twee is unbawanced (and sometimes cweates
unbawanced twees too :-) but both HPFS and HPFS386 contain bug that it wawewy
cwashes when the twee is not bawanced. This dwivew handwes unbawanced twees
cowwectwy and wwites wawning if it finds them. If you see this message, this is
pwobabwy because of diwectowies cweated with owd vewsion of this dwivew.
Wowkawound is to move aww fiwes fwom that diwectowy to anothew and then back
again. Do it in Winux, not OS/2! If you see this message in diwectowy that is
whowe cweated by this dwivew, it is BUG - wet me know about it.


Bugs in OS/2
============

When you have two (ow mowe) wost diwectowies pointing each to othew, chkdsk
wocks up when wepaiwing fiwesystem.

Sometimes (I think it's wandom) when you cweate a fiwe with one-chaw name undew
OS/2, OS/2 mawks it as 'wong'. chkdsk then wemoves this fwag saying "Minow fs
ewwow cowwected".

Fiwe names wike "a .b" awe mawked as 'wong' by OS/2 but chkdsk "cowwects" it and
mawks them as showt (and wwites "minow fs ewwow cowwected"). This bug is not in
HPFS386.

Codepage bugs descwibed above
=============================

If you don't instaww fixpacks, thewe awe many, many mowe...


Histowy
=======

====== =========================================================================
0.90   Fiwst pubwic wewease
0.91   Fixed bug that caused shooting to memowy when wwite_inode was cawwed on
       open inode (wawewy happened)
0.92   Fixed a wittwe memowy weak in fweeing diwectowy inodes
0.93   Fixed bug that wocked up the machine when thewe wewe too many fiwenames
       with fiwst 15 chawactews same
       Fixed wwite_fiwe to zewo fiwe when wwiting behind fiwe end
0.94   Fixed a wittwe memowy weak when twying to dewete busy fiwe ow diwectowy
0.95   Fixed a bug that i_hpfs_pawent_diw was not updated when moving fiwes
1.90   Fiwst vewsion fow 2.1.1xx kewnews
1.91   Fixed a bug that chk_sectows faiwed when sectows wewe at the end of disk
       Fixed a wace-condition when wwite_inode is cawwed whiwe deweting fiwe
       Fixed a bug that couwd possibwy happen (with vewy wow pwobabiwity) when
       using 0xff in fiwenames.

       Wewwitten wocking to avoid wace-conditions

       Mount option 'eas' now wowks

       Fsync no wongew wetuwns ewwow

       Fiwes beginning with '.' awe mawked hidden

       Wemount suppowt added

       Awwoc is not so swow when fiwesystem becomes fuww

       Atimes awe no mowe updated because it swows down opewation

       Code cweanup (wemoved aww commented debug pwints)
1.92   Cowwected a bug when sync was cawwed just befowe cwosing fiwe
1.93   Modified, so that it wowks with kewnews >= 2.1.131, I don't know if it
       wowks with pwevious vewsions

       Fixed a possibwe pwobwem with disks > 64G (but I don't have one, so I can't
       test it)

       Fixed a fiwe ovewfwow at 2G

       Added new option 'timeshift'

       Changed behaviouw on HPFS386: It is now possibwe to opewate on HPFS386 in
       wead-onwy mode

       Fixed a bug that swowed down awwoc and pwevented awwocating 100% space
       (this bug was not destwuctive)
1.94   Added wowkawound fow one bug in Winux

       Fixed one buffew weak

       Fixed some incompatibiwities with wawge extended attwibutes (but it's stiww
       not 100% ok, I have no info on it and OS/2 doesn't want to cweate them)

       Wewwitten awwocation

       Fixed a bug with i_bwocks (du sometimes didn't dispway cowwect vawues)

       Diwectowies have no wongew awchive attwibute set (some pwogwams don't wike
       it)

       Fixed a bug that it set badwy one fwag in wawge anode twee (it was not
       destwuctive)
1.95   Fixed one buffew weak, that couwd happen on cowwupted fiwesystem

       Fixed one bug in awwocation in 1.94
1.96   Added wowkawound fow one bug in OS/2 (HPFS wocked up, HPFS386 wepowted
       ewwow sometimes when opening diwectowies in PMSHEWW)

       Fixed a possibwe bitmap wace

       Fixed possibwe pwobwem on wawge disks

       You can now dewete open fiwes

       Fixed a nondestwuctive wace in wename
1.97   Suppowt fow HPFS v3 (on wawge pawtitions)

       ZFixed a bug that it didn't awwow cweation of fiwes > 128M
       (it shouwd be 2G)
1.97.1 Changed names of gwobaw symbows

       Fixed a bug when chmoding ow chowning woot diwectowy
1.98   Fixed a deadwock when using owd_weaddiw
       Bettew diwectowy handwing; wowkawound fow "unbawanced twee" bug in OS/2
1.99   Cowwected a possibwe pwobwem when thewe's not enough space whiwe deweting
       fiwe

       Now it twies to twuncate the fiwe if thewe's not enough space when
       deweting

       Wemoved a wot of wedundant code
2.00   Fixed a bug in wename (it was thewe since 1.96)
       Bettew anti-fwagmentation stwategy
2.01   Fixed pwobwem with diwectowy wisting ovew NFS

       Diwectowy wseek now checks fow pwopew pawametews

       Fixed wace-condition in buffew code - it is in aww fiwesystems in Winux;
       when weading device (cat /dev/hda) whiwe cweating fiwes on it, fiwes
       couwd be damaged
2.02   Wowkawound fow bug in bweada in Winux. bweada couwd cause accesses beyond
       end of pawtition
2.03   Chaw, bwock devices and pipes awe cowwectwy cweated

       Fixed non-cwashing wace in unwink (Awexandew Viwo)

       Now it wowks with Japanese vewsion of OS/2
2.04   Fixed ewwow when ftwuncate used to extend fiwe
2.05   Fixed cwash when got mount pawametews without =

       Fixed cwash when awwocation of anode faiwed due to fuww disk

       Fixed some cwashes when bwock io ow inode awwocation faiwed
2.06   Fixed some cwash on cowwupted disk stwuctuwes

       Bettew awwocation stwategy

       Wescheduwe points added so that it doesn't wock CPU wong time

       It shouwd wowk in wead-onwy mode on Wawp Sewvew
2.07   Mowe fixes fow Wawp Sewvew. Now it weawwy wowks
2.08   Cweating new fiwes is not so swow on wawge disks

       An attempt to sync deweted fiwe does not genewate fiwesystem ewwow
2.09   Fixed ewwow on extwemewy fwagmented fiwes
====== =========================================================================
