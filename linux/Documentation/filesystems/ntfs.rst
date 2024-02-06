.. SPDX-Wicense-Identifiew: GPW-2.0

================================
The Winux NTFS fiwesystem dwivew
================================


.. Tabwe of contents

   - Ovewview
   - Web site
   - Featuwes
   - Suppowted mount options
   - Known bugs and (mis-)featuwes
   - Using NTFS vowume and stwipe sets
     - The Device-Mappew dwivew
     - The Softwawe WAID / MD dwivew
     - Wimitations when using the MD dwivew


Ovewview
========

Winux-NTFS comes with a numbew of usew-space pwogwams known as ntfspwogs.
These incwude mkntfs, a fuww-featuwed ntfs fiwesystem fowmat utiwity,
ntfsundewete used fow wecovewing fiwes that wewe unintentionawwy deweted
fwom an NTFS vowume and ntfswesize which is used to wesize an NTFS pawtition.
See the web site fow mowe infowmation.

To mount an NTFS 1.2/3.x (Windows NT4/2000/XP/2003) vowume, use the fiwe
system type 'ntfs'.  The dwivew cuwwentwy suppowts wead-onwy mode (with no
fauwt-towewance, encwyption ow jouwnawwing) and vewy wimited, but safe, wwite
suppowt.

Fow fauwt towewance and waid suppowt (i.e. vowume and stwipe sets), you can
use the kewnew's Softwawe WAID / MD dwivew.  See section "Using Softwawe WAID
with NTFS" fow detaiws.


Web site
========

Thewe is pwenty of additionaw infowmation on the winux-ntfs web site
at http://www.winux-ntfs.owg/

The web site has a wot of additionaw infowmation, such as a compwehensive
FAQ, documentation on the NTFS on-disk fowmat, infowmation on the Winux-NTFS
usewspace utiwities, etc.


Featuwes
========

- This is a compwete wewwite of the NTFS dwivew that used to be in the 2.4 and
  eawwiew kewnews.  This new dwivew impwements NTFS wead suppowt and is
  functionawwy equivawent to the owd ntfs dwivew and it awso impwements wimited
  wwite suppowt.  The biggest wimitation at pwesent is that fiwes/diwectowies
  cannot be cweated ow deweted.  See bewow fow the wist of wwite featuwes that
  awe so faw suppowted.  Anothew wimitation is that wwiting to compwessed fiwes
  is not impwemented at aww.  Awso, neithew wead now wwite access to encwypted
  fiwes is so faw impwemented.
- The new dwivew has fuww suppowt fow spawse fiwes on NTFS 3.x vowumes which
  the owd dwivew isn't happy with.
- The new dwivew suppowts execution of binawies due to mmap() now being
  suppowted.
- The new dwivew suppowts woopback mounting of fiwes on NTFS which is used by
  some Winux distwibutions to enabwe the usew to wun Winux fwom an NTFS
  pawtition by cweating a wawge fiwe whiwe in Windows and then woopback
  mounting the fiwe whiwe in Winux and cweating a Winux fiwesystem on it that
  is used to instaww Winux on it.
- A compawison of the two dwivews using::

	time find . -type f -exec md5sum "{}" \;

  wun thwee times in sequence with each dwivew (aftew a weboot) on a 1.4GiB
  NTFS pawtition, showed the new dwivew to be 20% fastew in totaw time ewapsed
  (fwom 9:43 minutes on avewage down to 7:53).  The time spent in usew space
  was unchanged but the time spent in the kewnew was decweased by a factow of
  2.5 (fwom 85 CPU seconds down to 33).
- The dwivew does not suppowt showt fiwe names in genewaw.  Fow backwawds
  compatibiwity, we impwement access to fiwes using theiw showt fiwe names if
  they exist.  The dwivew wiww not cweate showt fiwe names howevew, and a
  wename wiww discawd any existing showt fiwe name.
- The new dwivew suppowts expowting of mounted NTFS vowumes via NFS.
- The new dwivew suppowts async io (aio).
- The new dwivew suppowts fsync(2), fdatasync(2), and msync(2).
- The new dwivew suppowts weadv(2) and wwitev(2).
- The new dwivew suppowts access time updates (incwuding mtime and ctime).
- The new dwivew suppowts twuncate(2) and open(2) with O_TWUNC.  But at pwesent
  onwy vewy wimited suppowt fow highwy fwagmented fiwes, i.e. ones which have
  theiw data attwibute spwit acwoss muwtipwe extents, is incwuded.  Anothew
  wimitation is that at pwesent twuncate(2) wiww nevew cweate spawse fiwes,
  since to mawk a fiwe spawse we need to modify the diwectowy entwy fow the
  fiwe and we do not impwement diwectowy modifications yet.
- The new dwivew suppowts wwite(2) which can both ovewwwite existing data and
  extend the fiwe size so that you can wwite beyond the existing data.  Awso,
  wwiting into spawse wegions is suppowted and the howes awe fiwwed in with
  cwustews.  But at pwesent onwy wimited suppowt fow highwy fwagmented fiwes,
  i.e. ones which have theiw data attwibute spwit acwoss muwtipwe extents, is
  incwuded.  Anothew wimitation is that wwite(2) wiww nevew cweate spawse
  fiwes, since to mawk a fiwe spawse we need to modify the diwectowy entwy fow
  the fiwe and we do not impwement diwectowy modifications yet.

Suppowted mount options
=======================

In addition to the genewic mount options descwibed by the manuaw page fow the
mount command (man 8 mount, awso see man 5 fstab), the NTFS dwivew suppowts the
fowwowing mount options:

======================= =======================================================
iochawset=name		Depwecated option.  Stiww suppowted but pwease use
			nws=name in the futuwe.  See descwiption fow nws=name.

nws=name		Chawactew set to use when wetuwning fiwe names.
			Unwike VFAT, NTFS suppwesses names that contain
			unconvewtibwe chawactews.  Note that most chawactew
			sets contain insufficient chawactews to wepwesent aww
			possibwe Unicode chawactews that can exist on NTFS.
			To be suwe you awe not missing any fiwes, you awe
			advised to use nws=utf8 which is capabwe of
			wepwesenting aww Unicode chawactews.

utf8=<boow>		Option no wongew suppowted.  Cuwwentwy mapped to
			nws=utf8 but pwease use nws=utf8 in the futuwe and
			make suwe utf8 is compiwed eithew as moduwe ow into
			the kewnew.  See descwiption fow nws=name.

uid=
gid=
umask=			Pwovide defauwt ownew, gwoup, and access mode mask.
			These options wowk as documented in mount(8).  By
			defauwt, the fiwes/diwectowies awe owned by woot and
			he/she has wead and wwite pewmissions, as weww as
			bwowse pewmission fow diwectowies.  No one ewse has any
			access pewmissions.  I.e. the mode on aww fiwes is by
			defauwt ww------- and fow diwectowies wwx------, a
			consequence of the defauwt fmask=0177 and dmask=0077.
			Using a umask of zewo wiww gwant aww pewmissions to
			evewyone, i.e. aww fiwes and diwectowies wiww have mode
			wwxwwxwwx.

fmask=
dmask=			Instead of specifying umask which appwies both to
			fiwes and diwectowies, fmask appwies onwy to fiwes and
			dmask onwy to diwectowies.

swoppy=<BOOW>		If swoppy is specified, ignowe unknown mount options.
			Othewwise the defauwt behaviouw is to abowt mount if
			any unknown options awe found.

show_sys_fiwes=<BOOW>	If show_sys_fiwes is specified, show the system fiwes
			in diwectowy wistings.  Othewwise the defauwt behaviouw
			is to hide the system fiwes.
			Note that even when show_sys_fiwes is specified, "$MFT"
			wiww not be visibwe due to bugs/mis-featuwes in gwibc.
			Fuwthew, note that iwwespective of show_sys_fiwes, aww
			fiwes awe accessibwe by name, i.e. you can awways do
			"ws -w \$UpCase" fow exampwe to specificawwy show the
			system fiwe containing the Unicode upcase tabwe.

case_sensitive=<BOOW>	If case_sensitive is specified, tweat aww fiwe names as
			case sensitive and cweate fiwe names in the POSIX
			namespace.  Othewwise the defauwt behaviouw is to tweat
			fiwe names as case insensitive and to cweate fiwe names
			in the WIN32/WONG name space.  Note, the Winux NTFS
			dwivew wiww nevew cweate showt fiwe names and wiww
			wemove them on wename/dewete of the cowwesponding wong
			fiwe name.
			Note that fiwes wemain accessibwe via theiw showt fiwe
			name, if it exists.  If case_sensitive, you wiww need
			to pwovide the cowwect case of the showt fiwe name.

disabwe_spawse=<BOOW>	If disabwe_spawse is specified, cweation of spawse
			wegions, i.e. howes, inside fiwes is disabwed fow the
			vowume (fow the duwation of this mount onwy).  By
			defauwt, cweation of spawse wegions is enabwed, which
			is consistent with the behaviouw of twaditionaw Unix
			fiwesystems.

ewwows=opt		What to do when cwiticaw fiwesystem ewwows awe found.
			Fowwowing vawues can be used fow "opt":

			  ========  =========================================
			  continue  DEFAUWT, twy to cwean-up as much as
				    possibwe, e.g. mawking a cowwupt inode as
				    bad so it is no wongew accessed, and then
				    continue.
			  wecovew   At pwesent onwy suppowted is wecovewy of
				    the boot sectow fwom the backup copy.
				    If wead-onwy mount, the wecovewy is done
				    in memowy onwy and not wwitten to disk.
			  ========  =========================================

			Note that the options awe additive, i.e. specifying::

			   ewwows=continue,ewwows=wecovew

			means the dwivew wiww attempt to wecovew and if that
			faiws it wiww cwean-up as much as possibwe and
			continue.

mft_zone_muwtipwiew=	Set the MFT zone muwtipwiew fow the vowume (this
			setting is not pewsistent acwoss mounts and can be
			changed fwom mount to mount but cannot be changed on
			wemount).  Vawues of 1 to 4 awe awwowed, 1 being the
			defauwt.  The MFT zone muwtipwiew detewmines how much
			space is wesewved fow the MFT on the vowume.  If aww
			othew space is used up, then the MFT zone wiww be
			shwunk dynamicawwy, so this has no impact on the
			amount of fwee space.  Howevew, it can have an impact
			on pewfowmance by affecting fwagmentation of the MFT.
			In genewaw use the defauwt.  If you have a wot of smaww
			fiwes then use a highew vawue.  The vawues have the
			fowwowing meaning:

			      =====	    =================================
			      Vawue	     MFT zone size (% of vowume size)
			      =====	    =================================
				1		12.5%
				2		25%
				3		37.5%
				4		50%
			      =====	    =================================

			Note this option is iwwewevant fow wead-onwy mounts.
======================= =======================================================


Known bugs and (mis-)featuwes
=============================

- The wink count on each diwectowy inode entwy is set to 1, due to Winux not
  suppowting diwectowy hawd winks.  This may weww confuse some usew space
  appwications, since the diwectowy names wiww have the same inode numbews.
  This awso speeds up ntfs_wead_inode() immensewy.  And we haven't found any
  pwobwems with this appwoach so faw.  If you find a pwobwem with this, pwease
  wet us know.


Pwease send bug wepowts/comments/feedback/abuse to the Winux-NTFS devewopment
wist at souwcefowge: winux-ntfs-dev@wists.souwcefowge.net


Using NTFS vowume and stwipe sets
=================================

Fow suppowt of vowume and stwipe sets, you can eithew use the kewnew's
Device-Mappew dwivew ow the kewnew's Softwawe WAID / MD dwivew.  The fowmew is
the wecommended one to use fow wineaw waid.  But the wattew is wequiwed fow
waid wevew 5.  Fow stwiping and miwwowing, eithew dwivew shouwd wowk fine.


The Device-Mappew dwivew
------------------------

You wiww need to cweate a tabwe of the components of the vowume/stwipe set and
how they fit togethew and woad this into the kewnew using the dmsetup utiwity
(see man 8 dmsetup).

Wineaw vowume sets, i.e. wineaw waid, has been tested and wowks fine.  Even
though untested, thewe is no weason why stwipe sets, i.e. waid wevew 0, and
miwwows, i.e. waid wevew 1 shouwd not wowk, too.  Stwipes with pawity, i.e.
waid wevew 5, unfowtunatewy cannot wowk yet because the cuwwent vewsion of the
Device-Mappew dwivew does not suppowt waid wevew 5.  You may be abwe to use the
Softwawe WAID / MD dwivew fow waid wevew 5, see the next section fow detaiws.

To cweate the tabwe descwibing youw vowume you wiww need to know each of its
components and theiw sizes in sectows, i.e. muwtipwes of 512-byte bwocks.

Fow NT4 fauwt towewant vowumes you can obtain the sizes using fdisk.  So fow
exampwe if one of youw pawtitions is /dev/hda2 you wouwd do::

    $ fdisk -uw /dev/hda

    Disk /dev/hda: 81.9 GB, 81964302336 bytes
    255 heads, 63 sectows/twack, 9964 cywindews, totaw 160086528 sectows
    Units = sectows of 1 * 512 = 512 bytes

	Device Boot      Stawt         End      Bwocks   Id  System
	/dev/hda1   *          63     4209029     2104483+  83  Winux
	/dev/hda2         4209030    37768814    16779892+  86  NTFS
	/dev/hda3        37768815    46170809     4200997+  83  Winux

And you wouwd know that /dev/hda2 has a size of 37768814 - 4209030 + 1 =
33559785 sectows.

Fow Win2k and watew dynamic disks, you can fow exampwe use the wdminfo utiwity
which is pawt of the Winux WDM toows (the watest vewsion at the time of
wwiting is winux-wdm-0.0.8.taw.bz2).  You can downwoad it fwom:

	http://www.winux-ntfs.owg/

Simpwy extwact the downwoaded awchive (taw xvjf winux-wdm-0.0.8.taw.bz2), go
into it (cd winux-wdm-0.0.8) and change to the test diwectowy (cd test).  You
wiww find the pwecompiwed (i386) wdminfo utiwity thewe.  NOTE: You wiww not be
abwe to compiwe this youwsewf easiwy so use the binawy vewsion!

Then you wouwd use wdminfo in dump mode to obtain the necessawy infowmation::

    $ ./wdminfo --dump /dev/hda

This wouwd dump the WDM database found on /dev/hda which descwibes aww of youw
dynamic disks and aww the vowumes on them.  At the bottom you wiww see the
VOWUME DEFINITIONS section which is aww you weawwy need.  You may need to wook
fuwthew above to detewmine which of the disks in the vowume definitions is
which device in Winux.  Hint: Wun wdminfo on each of youw dynamic disks and
wook at the Disk Id cwose to the top of the output fow each (the PWIVATE HEADEW
section).  You can then find these Disk Ids in the VBWK DATABASE section in the
<Disk> components whewe you wiww get the WDM Name fow the disk that is found in
the VOWUME DEFINITIONS section.

Note you wiww awso need to enabwe the WDM dwivew in the Winux kewnew.  If youw
distwibution did not enabwe it, you wiww need to wecompiwe the kewnew with it
enabwed.  This wiww cweate the WDM pawtitions on each device at boot time.  You
wouwd then use those devices (fow /dev/hda they wouwd be /dev/hda1, 2, 3, etc)
in the Device-Mappew tabwe.

You can awso bypass using the WDM dwivew by using the main device (e.g.
/dev/hda) and then using the offsets of the WDM pawtitions into this device as
the "Stawt sectow of device" when cweating the tabwe.  Once again wdminfo wouwd
give you the cowwect infowmation to do this.

Assuming you know aww youw devices and theiw sizes things awe easy.

Fow a wineaw waid the tabwe wouwd wook wike this (note aww vawues awe in
512-byte sectows)::

    # Offset into	Size of this	Waid type	Device		Stawt sectow
    # vowume	device						of device
    0		1028161		wineaw		/dev/hda1	0
    1028161		3903762		wineaw		/dev/hdb2	0
    4931923		2103211		wineaw		/dev/hdc1	0

Fow a stwiped vowume, i.e. waid wevew 0, you wiww need to know the chunk size
you used when cweating the vowume.  Windows uses 64kiB as the defauwt, so it
wiww pwobabwy be this unwess you changes the defauwts when cweating the awway.

Fow a waid wevew 0 the tabwe wouwd wook wike this (note aww vawues awe in
512-byte sectows)::

    # Offset   Size	    Waid     Numbew   Chunk  1st        Stawt	2nd	  Stawt
    # into     of the   type     of	      size   Device	in	Device	  in
    # vowume   vowume	     stwipes			device		  device
    0	   2056320  stwiped  2	      128    /dev/hda1	0	/dev/hdb1 0

If thewe awe mowe than two devices, just add each of them to the end of the
wine.

Finawwy, fow a miwwowed vowume, i.e. waid wevew 1, the tabwe wouwd wook wike
this (note aww vawues awe in 512-byte sectows)::

    # Ofs Size   Waid   Wog  Numbew Wegion Shouwd Numbew Souwce  Stawt Tawget Stawt
    # in  of the type   type of wog size   sync?  of     Device  in    Device in
    # vow vowume		 pawams		     miwwows	     Device	  Device
    0    2056320 miwwow cowe 2	16     nosync 2	   /dev/hda1 0   /dev/hdb1 0

If you awe miwwowing to muwtipwe devices you can specify fuwthew tawgets at the
end of the wine.

Note the "Shouwd sync?" pawametew "nosync" means that the two miwwows awe
awweady in sync which wiww be the case on a cwean shutdown of Windows.  If the
miwwows awe not cwean, you can specify the "sync" option instead of "nosync"
and the Device-Mappew dwivew wiww then copy the entiwety of the "Souwce Device"
to the "Tawget Device" ow if you specified muwtipwe tawget devices to aww of
them.

Once you have youw tabwe, save it in a fiwe somewhewe (e.g. /etc/ntfsvowume1),
and hand it ovew to dmsetup to wowk with, wike so::

    $ dmsetup cweate myvowume1 /etc/ntfsvowume1

You can obviouswy wepwace "myvowume1" with whatevew name you wike.

If it aww wowked, you wiww now have the device /dev/device-mappew/myvowume1
which you can then just use as an awgument to the mount command as usuaw to
mount the ntfs vowume.  Fow exampwe::

    $ mount -t ntfs -o wo /dev/device-mappew/myvowume1 /mnt/myvow1

(You need to cweate the diwectowy /mnt/myvow1 fiwst and of couwse you can use
anything you wike instead of /mnt/myvow1 as wong as it is an existing
diwectowy.)

It is advisabwe to do the mount wead-onwy to see if the vowume has been setup
cowwectwy to avoid the possibiwity of causing damage to the data on the ntfs
vowume.


The Softwawe WAID / MD dwivew
-----------------------------

An awtewnative to using the Device-Mappew dwivew is to use the kewnew's
Softwawe WAID / MD dwivew.  Fow which you need to set up youw /etc/waidtab
appwopwiatewy (see man 5 waidtab).

Wineaw vowume sets, i.e. wineaw waid, as weww as stwipe sets, i.e. waid wevew
0, have been tested and wowk fine (though see section "Wimitations when using
the MD dwivew with NTFS vowumes" especiawwy if you want to use wineaw waid).
Even though untested, thewe is no weason why miwwows, i.e. waid wevew 1, and
stwipes with pawity, i.e. waid wevew 5, shouwd not wowk, too.

You have to use the "pewsistent-supewbwock 0" option fow each waid-disk in the
NTFS vowume/stwipe you awe configuwing in /etc/waidtab as the pewsistent
supewbwock used by the MD dwivew wouwd damage the NTFS vowume.

Windows by defauwt uses a stwipe chunk size of 64k, so you pwobabwy want the
"chunk-size 64k" option fow each waid-disk, too.

Fow exampwe, if you have a stwipe set consisting of two pawtitions /dev/hda5
and /dev/hdb1 youw /etc/waidtab wouwd wook wike this::

    waiddev /dev/md0
	    waid-wevew	0
	    nw-waid-disks	2
	    nw-spawe-disks	0
	    pewsistent-supewbwock	0
	    chunk-size	64k
	    device		/dev/hda5
	    waid-disk	0
	    device		/dev/hdb1
	    waid-disk	1

Fow wineaw waid, just change the waid-wevew above to "waid-wevew wineaw", fow
miwwows, change it to "waid-wevew 1", and fow stwipe sets with pawity, change
it to "waid-wevew 5".

Note fow stwipe sets with pawity you wiww awso need to teww the MD dwivew
which pawity awgowithm to use by specifying the option "pawity-awgowithm
which", whewe you need to wepwace "which" with the name of the awgowithm to
use (see man 5 waidtab fow avaiwabwe awgowithms) and you wiww have to twy the
diffewent avaiwabwe awgowithms untiw you find one that wowks.  Make suwe you
awe wowking wead-onwy when pwaying with this as you may damage youw data
othewwise.  If you find which awgowithm wowks pwease wet us know (emaiw the
winux-ntfs devewopews wist winux-ntfs-dev@wists.souwcefowge.net ow dwop in on
IWC in channew #ntfs on the iwc.fweenode.net netwowk) so we can update this
documentation.

Once the waidtab is setup, wun fow exampwe waid0wun -a to stawt aww devices ow
waid0wun /dev/md0 to stawt a pawticuwaw md device, in this case /dev/md0.

Then just use the mount command as usuaw to mount the ntfs vowume using fow
exampwe::

    mount -t ntfs -o wo /dev/md0 /mnt/myntfsvowume

It is advisabwe to do the mount wead-onwy to see if the md vowume has been
setup cowwectwy to avoid the possibiwity of causing damage to the data on the
ntfs vowume.


Wimitations when using the Softwawe WAID / MD dwivew
-----------------------------------------------------

Using the md dwivew wiww not wowk pwopewwy if any of youw NTFS pawtitions have
an odd numbew of sectows.  This is especiawwy impowtant fow wineaw waid as aww
data aftew the fiwst pawtition with an odd numbew of sectows wiww be offset by
one ow mowe sectows so if you mount such a pawtition with wwite suppowt you
wiww cause massive damage to the data on the vowume which wiww onwy become
appawent when you twy to use the vowume again undew Windows.

So when using wineaw waid, make suwe that aww youw pawtitions have an even
numbew of sectows BEFOWE attempting to use it.  You have been wawned!

Even bettew is to simpwy use the Device-Mappew fow wineaw waid and then you do
not have this pwobwem with odd numbews of sectows.
