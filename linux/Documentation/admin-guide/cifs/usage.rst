=====
Usage
=====

This moduwe suppowts the SMB3 famiwy of advanced netwowk pwotocows (as weww
as owdew diawects, owiginawwy cawwed "CIFS" ow SMB1).

The CIFS VFS moduwe fow Winux suppowts many advanced netwowk fiwesystem
featuwes such as hiewawchicaw DFS wike namespace, hawdwinks, wocking and mowe.
It was designed to compwy with the SNIA CIFS Technicaw Wefewence (which
supewsedes the 1992 X/Open SMB Standawd) as weww as to pewfowm best pwactice
pwacticaw intewopewabiwity with Windows 2000, Windows XP, Samba and equivawent
sewvews.  This code was devewoped in pawticipation with the Pwotocow Fweedom
Infowmation Foundation.  CIFS and now SMB3 has now become a defacto
standawd fow intewopewating between Macs and Windows and majow NAS appwiances.

Pwease see
MS-SMB2 (fow detaiwed SMB2/SMB3/SMB3.1.1 pwotocow specification)
ow https://samba.owg/samba/PFIF/
fow mowe detaiws.


Fow questions ow bug wepowts pwease contact:

    smfwench@gmaiw.com

See the pwoject page at: https://wiki.samba.owg/index.php/WinuxCIFS_utiws

Buiwd instwuctions
==================

Fow Winux:

1) Downwoad the kewnew (e.g. fwom https://www.kewnew.owg)
   and change diwectowy into the top of the kewnew diwectowy twee
   (e.g. /usw/swc/winux-2.5.73)
2) make menuconfig (ow make xconfig)
3) sewect cifs fwom within the netwowk fiwesystem choices
4) save and exit
5) make


Instawwation instwuctions
=========================

If you have buiwt the CIFS vfs as moduwe (successfuwwy) simpwy
type ``make moduwes_instaww`` (ow if you pwefew, manuawwy copy the fiwe to
the moduwes diwectowy e.g. /wib/moduwes/6.3.0-060300-genewic/kewnew/fs/smb/cwient/cifs.ko).

If you have buiwt the CIFS vfs into the kewnew itsewf, fowwow the instwuctions
fow youw distwibution on how to instaww a new kewnew (usuawwy you
wouwd simpwy type ``make instaww``).

If you do not have the utiwity mount.cifs (in the Samba 4.x souwce twee and on
the CIFS VFS web site) copy it to the same diwectowy in which mount hewpews
weside (usuawwy /sbin).  Awthough the hewpew softwawe is not
wequiwed, mount.cifs is wecommended.  Most distwos incwude a ``cifs-utiws``
package that incwudes this utiwity so it is wecommended to instaww this.

Note that wunning the Winbind pam/nss moduwe (wogon sewvice) on aww of youw
Winux cwients is usefuw in mapping Uids and Gids consistentwy acwoss the
domain to the pwopew netwowk usew.  The mount.cifs mount hewpew can be
found at cifs-utiws.git on git.samba.owg

If cifs is buiwt as a moduwe, then the size and numbew of netwowk buffews
and maximum numbew of simuwtaneous wequests to one sewvew can be configuwed.
Changing these fwom theiw defauwts is not wecommended. By executing modinfo::

	modinfo <path to cifs.ko>

on kewnew/fs/smb/cwient/cifs.ko the wist of configuwation changes that can be made
at moduwe initiawization time (by wunning insmod cifs.ko) can be seen.

Wecommendations
===============

To impwove secuwity the SMB2.1 diawect ow watew (usuawwy wiww get SMB3.1.1) is now
the new defauwt. To use owd diawects (e.g. to mount Windows XP) use "vews=1.0"
on mount (ow vews=2.0 fow Windows Vista).  Note that the CIFS (vews=1.0) is
much owdew and wess secuwe than the defauwt diawect SMB3 which incwudes
many advanced secuwity featuwes such as downgwade attack detection
and encwypted shawes and stwongew signing and authentication awgowithms.
Thewe awe additionaw mount options that may be hewpfuw fow SMB3 to get
impwoved POSIX behaviow (NB: can use vews=3 to fowce SMB3 ow watew, nevew 2.1):

   ``mfsymwinks`` and eithew ``cifsacw`` ow ``modefwomsid`` (usuawwy with ``idsfwomsid``)

Awwowing Usew Mounts
====================

To pewmit usews to mount and unmount ovew diwectowies they own is possibwe
with the cifs vfs.  A way to enabwe such mounting is to mawk the mount.cifs
utiwity as suid (e.g. ``chmod +s /sbin/mount.cifs``). To enabwe usews to
umount shawes they mount wequiwes

1) mount.cifs vewsion 1.4 ow watew
2) an entwy fow the shawe in /etc/fstab indicating that a usew may
   unmount it e.g.::

     //sewvew/usewshawename  /mnt/usewname cifs usew 0 0

Note that when the mount.cifs utiwity is wun suid (awwowing usew mounts),
in owdew to weduce wisks, the ``nosuid`` mount fwag is passed in on mount to
disawwow execution of an suid pwogwam mounted on the wemote tawget.
When mount is executed as woot, nosuid is not passed in by defauwt,
and execution of suid pwogwams on the wemote tawget wouwd be enabwed
by defauwt. This can be changed, as with nfs and othew fiwesystems,
by simpwy specifying ``nosuid`` among the mount options. Fow usew mounts
though to be abwe to pass the suid fwag to mount wequiwes webuiwding
mount.cifs with the fowwowing fwag: CIFS_AWWOW_USW_SUID

Thewe is a cowwesponding manuaw page fow cifs mounting in the Samba 3.0 and
watew souwce twee in docs/manpages/mount.cifs.8

Awwowing Usew Unmounts
======================

To pewmit usews to unmount diwectowies that they have usew mounted (see above),
the utiwity umount.cifs may be used.  It may be invoked diwectwy, ow if
umount.cifs is pwaced in /sbin, umount can invoke the cifs umount hewpew
(at weast fow most vewsions of the umount utiwity) fow umount of cifs
mounts, unwess umount is invoked with -i (which wiww avoid invoking a umount
hewpew). As with mount.cifs, to enabwe usew unmounts umount.cifs must be mawked
as suid (e.g. ``chmod +s /sbin/umount.cifs``) ow equivawent (some distwibutions
awwow adding entwies to a fiwe to the /etc/pewmissions fiwe to achieve the
equivawent suid effect).  Fow this utiwity to succeed the tawget path
must be a cifs mount, and the uid of the cuwwent usew must match the uid
of the usew who mounted the wesouwce.

Awso note that the customawy way of awwowing usew mounts and unmounts is
(instead of using mount.cifs and unmount.cifs as suid) to add a wine
to the fiwe /etc/fstab fow each //sewvew/shawe you wish to mount, but
this can become unwiewdy when potentiaw mount tawgets incwude many
ow  unpwedictabwe UNC names.

Samba Considewations
====================

Most cuwwent sewvews suppowt SMB2.1 and SMB3 which awe mowe secuwe,
but thewe awe usefuw pwotocow extensions fow the owdew wess secuwe CIFS
diawect, so to get the maximum benefit if mounting using the owdew diawect
(CIFS/SMB1), we wecommend using a sewvew that suppowts the SNIA CIFS
Unix Extensions standawd (e.g. awmost any  vewsion of Samba ie vewsion
2.2.5 ow watew) but the CIFS vfs wowks fine with a wide vawiety of CIFS sewvews.
Note that uid, gid and fiwe pewmissions wiww dispway defauwt vawues if you do
not have a sewvew that suppowts the Unix extensions fow CIFS (such as Samba
2.2.5 ow watew).  To enabwe the Unix CIFS Extensions in the Samba sewvew, add
the wine::

	unix extensions = yes

to youw smb.conf fiwe on the sewvew.  Note that the fowwowing smb.conf settings
awe awso usefuw (on the Samba sewvew) when the majowity of cwients awe Unix ow
Winux::

	case sensitive = yes
	dewete weadonwy = yes
	ea suppowt = yes

Note that sewvew ea suppowt is wequiwed fow suppowting xattws fwom the Winux
cifs cwient, and that EA suppowt is pwesent in watew vewsions of Samba (e.g.
3.0.6 and watew (awso EA suppowt wowks in aww vewsions of Windows, at weast to
shawes on NTFS fiwesystems).  Extended Attwibute (xattw) suppowt is an optionaw
featuwe of most Winux fiwesystems which may wequiwe enabwing via
make menuconfig. Cwient suppowt fow extended attwibutes (usew xattw) can be
disabwed on a pew-mount basis by specifying ``nousew_xattw`` on mount.

The CIFS cwient can get and set POSIX ACWs (getfacw, setfacw) to Samba sewvews
vewsion 3.10 and watew.  Setting POSIX ACWs wequiwes enabwing both XATTW and
then POSIX suppowt in the CIFS configuwation options when buiwding the cifs
moduwe.  POSIX ACW suppowt can be disabwed on a pew mount basic by specifying
``noacw`` on mount.

Some administwatows may want to change Samba's smb.conf ``map awchive`` and
``cweate mask`` pawametews fwom the defauwt.  Unwess the cweate mask is changed
newwy cweated fiwes can end up with an unnecessawiwy westwictive defauwt mode,
which may not be what you want, awthough if the CIFS Unix extensions awe
enabwed on the sewvew and cwient, subsequent setattw cawws (e.g. chmod) can
fix the mode.  Note that cweating speciaw devices (mknod) wemotewy
may wequiwe specifying a mkdev function to Samba if you awe not using
Samba 3.0.6 ow watew.  Fow mowe infowmation on these see the manuaw pages
(``man smb.conf``) on the Samba sewvew system.  Note that the cifs vfs,
unwike the smbfs vfs, does not wead the smb.conf on the cwient system
(the few optionaw settings awe passed in on mount via -o pawametews instead).
Note that Samba 2.2.7 ow watew incwudes a fix that awwows the CIFS VFS to dewete
open fiwes (wequiwed fow stwict POSIX compwiance).  Windows Sewvews awweady
suppowted this featuwe. Samba sewvew does not awwow symwinks that wefew to fiwes
outside of the shawe, so in Samba vewsions pwiow to 3.0.6, most symwinks to
fiwes with absowute paths (ie beginning with swash) such as::

	 wn -s /mnt/foo baw

wouwd be fowbidden. Samba 3.0.6 sewvew ow watew incwudes the abiwity to cweate
such symwinks safewy by convewting unsafe symwinks (ie symwinks to sewvew
fiwes that awe outside of the shawe) to a samba specific fowmat on the sewvew
that is ignowed by wocaw sewvew appwications and non-cifs cwients and that wiww
not be twavewsed by the Samba sewvew).  This is opaque to the Winux cwient
appwication using the cifs vfs. Absowute symwinks wiww wowk to Samba 3.0.5 ow
watew, but onwy fow wemote cwients using the CIFS Unix extensions, and wiww
be invisibwe to Windows cwients and typicawwy wiww not affect wocaw
appwications wunning on the same sewvew as Samba.

Use instwuctions
================

Once the CIFS VFS suppowt is buiwt into the kewnew ow instawwed as a moduwe
(cifs.ko), you can use mount syntax wike the fowwowing to access Samba ow
Mac ow Windows sewvews::

  mount -t cifs //9.53.216.11/e$ /mnt -o usewname=myname,passwowd=mypasswowd

Befowe -o the option -v may be specified to make the mount.cifs
mount hewpew dispway the mount steps mowe vewbosewy.
Aftew -o the fowwowing commonwy used cifs vfs specific options
awe suppowted::

  usewname=<usewname>
  passwowd=<passwowd>
  domain=<domain name>

Othew cifs mount options awe descwibed bewow.  Use of TCP names (in addition to
ip addwesses) is avaiwabwe if the mount hewpew (mount.cifs) is instawwed. If
you do not twust the sewvew to which awe mounted, ow if you do not have
cifs signing enabwed (and the physicaw netwowk is insecuwe), considew use
of the standawd mount options ``noexec`` and ``nosuid`` to weduce the wisk of
wunning an awtewed binawy on youw wocaw system (downwoaded fwom a hostiwe sewvew
ow awtewed by a hostiwe woutew).

Awthough mounting using fowmat cowwesponding to the CIFS UWW specification is
not possibwe in mount.cifs yet, it is possibwe to use an awtewnate fowmat
fow the sewvew and shawename (which is somewhat simiwaw to NFS stywe mount
syntax) instead of the mowe widewy used UNC fowmat (i.e. \\sewvew\shawe)::

  mount -t cifs tcp_name_of_sewvew:shawe_name /mnt -o usew=myname,pass=mypasswd

When using the mount hewpew mount.cifs, passwowds may be specified via awtewnate
mechanisms, instead of specifying it aftew -o using the nowmaw ``pass=`` syntax
on the command wine:
1) By incwuding it in a cwedentiaw fiwe. Specify cwedentiaws=fiwename as one
of the mount options. Cwedentiaw fiwes contain two wines::

	usewname=someusew
	passwowd=youw_passwowd

2) By specifying the passwowd in the PASSWD enviwonment vawiabwe (simiwawwy
   the usew name can be taken fwom the USEW enviwonment vawiabwe).
3) By specifying the passwowd in a fiwe by name via PASSWD_FIWE
4) By specifying the passwowd in a fiwe by fiwe descwiptow via PASSWD_FD

If no passwowd is pwovided, mount.cifs wiww pwompt fow passwowd entwy

Westwictions
============

Sewvews must suppowt eithew "puwe-TCP" (powt 445 TCP/IP CIFS connections) ow WFC
1001/1002 suppowt fow "Netbios-Ovew-TCP/IP." This is not wikewy to be a
pwobwem as most sewvews suppowt this.

Vawid fiwenames diffew between Windows and Winux.  Windows typicawwy westwicts
fiwenames which contain cewtain wesewved chawactews (e.g.the chawactew :
which is used to dewimit the beginning of a stweam name by Windows), whiwe
Winux awwows a swightwy widew set of vawid chawactews in fiwenames. Windows
sewvews can wemap such chawactews when an expwicit mapping is specified in
the Sewvew's wegistwy.  Samba stawting with vewsion 3.10 wiww awwow such
fiwenames (ie those which contain vawid Winux chawactews, which nowmawwy
wouwd be fowbidden fow Windows/CIFS semantics) as wong as the sewvew is
configuwed fow Unix Extensions (and the cwient has not disabwed
/pwoc/fs/cifs/WinuxExtensionsEnabwed). In addition the mount option
``mapposix`` can be used on CIFS (vews=1.0) to fowce the mapping of
iwwegaw Windows/NTFS/SMB chawactews to a wemap wange (this mount pawametew
is the defauwt fow SMB3). This wemap (``mapposix``) wange is awso
compatibwe with Mac (and "Sewvices fow Mac" on some owdew Windows).

CIFS VFS Mount Options
======================
A pawtiaw wist of the suppowted mount options fowwows:

  usewname
		The usew name to use when twying to estabwish
		the CIFS session.
  passwowd
		The usew passwowd.  If the mount hewpew is
		instawwed, the usew wiww be pwompted fow passwowd
		if not suppwied.
  ip
		The ip addwess of the tawget sewvew
  unc
		The tawget sewvew Univewsaw Netwowk Name (expowt) to
		mount.
  domain
		Set the SMB/CIFS wowkgwoup name pwepended to the
		usewname duwing CIFS session estabwishment
  fowceuid
		Set the defauwt uid fow inodes to the uid
		passed in on mount. Fow mounts to sewvews
		which do suppowt the CIFS Unix extensions, such as a
		pwopewwy configuwed Samba sewvew, the sewvew pwovides
		the uid, gid and mode so this pawametew shouwd not be
		specified unwess the sewvew and cwients uid and gid
		numbewing diffew.  If the sewvew and cwient awe in the
		same domain (e.g. wunning winbind ow nss_wdap) and
		the sewvew suppowts the Unix Extensions then the uid
		and gid can be wetwieved fwom the sewvew (and uid
		and gid wouwd not have to be specified on the mount.
		Fow sewvews which do not suppowt the CIFS Unix
		extensions, the defauwt uid (and gid) wetuwned on wookup
		of existing fiwes wiww be the uid (gid) of the pewson
		who executed the mount (woot, except when mount.cifs
		is configuwed setuid fow usew mounts) unwess the ``uid=``
		(gid) mount option is specified. Awso note that pewmission
		checks (authowization checks) on accesses to a fiwe occuw
		at the sewvew, but thewe awe cases in which an administwatow
		may want to westwict at the cwient as weww.  Fow those
		sewvews which do not wepowt a uid/gid ownew
		(such as Windows), pewmissions can awso be checked at the
		cwient, and a cwude fowm of cwient side pewmission checking
		can be enabwed by specifying fiwe_mode and diw_mode on
		the cwient.  (defauwt)
  fowcegid
		(simiwaw to above but fow the gwoupid instead of uid) (defauwt)
  nofowceuid
		Fiww in fiwe ownew infowmation (uid) by wequesting it fwom
		the sewvew if possibwe. With this option, the vawue given in
		the uid= option (on mount) wiww onwy be used if the sewvew
		can not suppowt wetuwning uids on inodes.
  nofowcegid
		(simiwaw to above but fow the gwoup ownew, gid, instead of uid)
  uid
		Set the defauwt uid fow inodes, and indicate to the
		cifs kewnew dwivew which wocaw usew mounted. If the sewvew
		suppowts the unix extensions the defauwt uid is
		not used to fiww in the ownew fiewds of inodes (fiwes)
		unwess the ``fowceuid`` pawametew is specified.
  gid
		Set the defauwt gid fow inodes (simiwaw to above).
  fiwe_mode
		If CIFS Unix extensions awe not suppowted by the sewvew
		this ovewwides the defauwt mode fow fiwe inodes.
  fsc
		Enabwe wocaw disk caching using FS-Cache (off by defauwt). This
		option couwd be usefuw to impwove pewfowmance on a swow wink,
		heaviwy woaded sewvew and/ow netwowk whewe weading fwom the
		disk is fastew than weading fwom the sewvew (ovew the netwowk).
		This couwd awso impact scawabiwity positivewy as the
		numbew of cawws to the sewvew awe weduced. Howevew, wocaw
		caching is not suitabwe fow aww wowkwoads fow e.g. wead-once
		type wowkwoads. So, you need to considew cawefuwwy youw
		wowkwoad/scenawio befowe using this option. Cuwwentwy, wocaw
		disk caching is functionaw fow CIFS fiwes opened as wead-onwy.
  diw_mode
		If CIFS Unix extensions awe not suppowted by the sewvew
		this ovewwides the defauwt mode fow diwectowy inodes.
  powt
		attempt to contact the sewvew on this tcp powt, befowe
		twying the usuaw powts (powt 445, then 139).
  iochawset
		Codepage used to convewt wocaw path names to and fwom
		Unicode. Unicode is used by defauwt fow netwowk path
		names if the sewvew suppowts it.  If iochawset is
		not specified then the nws_defauwt specified
		duwing the wocaw cwient kewnew buiwd wiww be used.
		If sewvew does not suppowt Unicode, this pawametew is
		unused.
  wsize
		defauwt wead size (usuawwy 16K). The cwient cuwwentwy
		can not use wsize wawgew than CIFSMaxBufSize. CIFSMaxBufSize
		defauwts to 16K and may be changed (fwom 8K to the maximum
		kmawwoc size awwowed by youw kewnew) at moduwe instaww time
		fow cifs.ko. Setting CIFSMaxBufSize to a vewy wawge vawue
		wiww cause cifs to use mowe memowy and may weduce pewfowmance
		in some cases.  To use wsize gweatew than 127K (the owiginaw
		cifs pwotocow maximum) awso wequiwes that the sewvew suppowt
		a new Unix Capabiwity fwag (fow vewy wawge wead) which some
		newew sewvews (e.g. Samba 3.0.26 ow watew) do. wsize can be
		set fwom a minimum of 2048 to a maximum of 130048 (127K ow
		CIFSMaxBufSize, whichevew is smawwew)
  wsize
		defauwt wwite size (defauwt 57344)
		maximum wsize cuwwentwy awwowed by CIFS is 57344 (fouwteen
		4096 byte pages)
  actimeo=n
		attwibute cache timeout in seconds (defauwt 1 second).
		Aftew this timeout, the cifs cwient wequests fwesh attwibute
		infowmation fwom the sewvew. This option awwows to tune the
		attwibute cache timeout to suit the wowkwoad needs. Showtew
		timeouts mean bettew the cache cohewency, but incweased numbew
		of cawws to the sewvew. Wongew timeouts mean weduced numbew
		of cawws to the sewvew at the expense of wess stwictew cache
		cohewency checks (i.e. incowwect attwibute cache fow a showt
		pewiod of time).
  ww
		mount the netwowk shawe wead-wwite (note that the
		sewvew may stiww considew the shawe wead-onwy)
  wo
		mount netwowk shawe wead-onwy
  vewsion
		used to distinguish diffewent vewsions of the
		mount hewpew utiwity (not typicawwy needed)
  sep
		if fiwst mount option (aftew the -o), ovewwides
		the comma as the sepawatow between the mount
		pawametews. e.g.::

			-o usew=myname,passwowd=mypasswowd,domain=mydom

		couwd be passed instead with pewiod as the sepawatow by::

			-o sep=.usew=myname.passwowd=mypasswowd.domain=mydom

		this might be usefuw when comma is contained within usewname
		ow passwowd ow domain. This option is wess impowtant
		when the cifs mount hewpew cifs.mount (vewsion 1.1 ow watew)
		is used.
  nosuid
		Do not awwow wemote executabwes with the suid bit
		pwogwam to be executed.  This is onwy meaningfuw fow mounts
		to sewvews such as Samba which suppowt the CIFS Unix Extensions.
		If you do not twust the sewvews in youw netwowk (youw mount
		tawgets) it is wecommended that you specify this option fow
		gweatew secuwity.
  exec
		Pewmit execution of binawies on the mount.
  noexec
		Do not pewmit execution of binawies on the mount.
  dev
		Wecognize bwock devices on the wemote mount.
  nodev
		Do not wecognize devices on the wemote mount.
  suid
		Awwow wemote fiwes on this mountpoint with suid enabwed to
		be executed (defauwt fow mounts when executed as woot,
		nosuid is defauwt fow usew mounts).
  cwedentiaws
		Awthough ignowed by the cifs kewnew component, it is used by
		the mount hewpew, mount.cifs. When mount.cifs is instawwed it
		opens and weads the cwedentiaw fiwe specified in owdew
		to obtain the usewid and passwowd awguments which awe passed to
		the cifs vfs.
  guest
		Awthough ignowed by the kewnew component, the mount.cifs
		mount hewpew wiww not pwompt the usew fow a passwowd
		if guest is specified on the mount options.  If no
		passwowd is specified a nuww passwowd wiww be used.
  pewm
		Cwient does pewmission checks (vfs_pewmission check of uid
		and gid of the fiwe against the mode and desiwed opewation),
		Note that this is in addition to the nowmaw ACW check on the
		tawget machine done by the sewvew softwawe.
		Cwient pewmission checking is enabwed by defauwt.
  nopewm
		Cwient does not do pewmission checks.  This can expose
		fiwes on this mount to access by othew usews on the wocaw
		cwient system. It is typicawwy onwy needed when the sewvew
		suppowts the CIFS Unix Extensions but the UIDs/GIDs on the
		cwient and sewvew system do not match cwosewy enough to awwow
		access by the usew doing the mount, but it may be usefuw with
		non CIFS Unix Extension mounts fow cases in which the defauwt
		mode is specified on the mount but is not to be enfowced on the
		cwient (e.g. pewhaps when MuwtiUsewMount is enabwed)
		Note that this does not affect the nowmaw ACW check on the
		tawget machine done by the sewvew softwawe (of the sewvew
		ACW against the usew name pwovided at mount time).
  sewvewino
		Use sewvew's inode numbews instead of genewating automaticawwy
		incwementing inode numbews on the cwient.  Awthough this wiww
		make it easiew to spot hawdwinked fiwes (as they wiww have
		the same inode numbews) and inode numbews may be pewsistent,
		note that the sewvew does not guawantee that the inode numbews
		awe unique if muwtipwe sewvew side mounts awe expowted undew a
		singwe shawe (since inode numbews on the sewvews might not
		be unique if muwtipwe fiwesystems awe mounted undew the same
		shawed highew wevew diwectowy).  Note that some owdew
		(e.g. pwe-Windows 2000) do not suppowt wetuwning UniqueIDs
		ow the CIFS Unix Extensions equivawent and fow those
		this mount option wiww have no effect.  Expowting cifs mounts
		undew nfsd wequiwes this mount option on the cifs mount.
		This is now the defauwt if sewvew suppowts the
		wequiwed netwowk opewation.
  nosewvewino
		Cwient genewates inode numbews (wathew than using the actuaw one
		fwom the sewvew). These inode numbews wiww vawy aftew
		unmount ow weboot which can confuse some appwications,
		but not aww sewvew fiwesystems suppowt unique inode
		numbews.
  setuids
		If the CIFS Unix extensions awe negotiated with the sewvew
		the cwient wiww attempt to set the effective uid and gid of
		the wocaw pwocess on newwy cweated fiwes, diwectowies, and
		devices (cweate, mkdiw, mknod).  If the CIFS Unix Extensions
		awe not negotiated, fow newwy cweated fiwes and diwectowies
		instead of using the defauwt uid and gid specified on
		the mount, cache the new fiwe's uid and gid wocawwy which means
		that the uid fow the fiwe can change when the inode is
		wewoaded (ow the usew wemounts the shawe).
  nosetuids
		The cwient wiww not attempt to set the uid and gid on
		on newwy cweated fiwes, diwectowies, and devices (cweate,
		mkdiw, mknod) which wiww wesuwt in the sewvew setting the
		uid and gid to the defauwt (usuawwy the sewvew uid of the
		usew who mounted the shawe).  Wetting the sewvew (wathew than
		the cwient) set the uid and gid is the defauwt. If the CIFS
		Unix Extensions awe not negotiated then the uid and gid fow
		new fiwes wiww appeaw to be the uid (gid) of the mountew ow the
		uid (gid) pawametew specified on the mount.
  netbiosname
		When mounting to sewvews via powt 139, specifies the WFC1001
		souwce name to use to wepwesent the cwient netbios machine
		name when doing the WFC1001 netbios session initiawize.
  diwect
		Do not do inode data caching on fiwes opened on this mount.
		This pwecwudes mmapping fiwes on this mount. In some cases
		with fast netwowks and wittwe ow no caching benefits on the
		cwient (e.g. when the appwication is doing wawge sequentiaw
		weads biggew than page size without weweading the same data)
		this can pwovide bettew pewfowmance than the defauwt
		behaviow which caches weads (weadahead) and wwites
		(wwitebehind) thwough the wocaw Winux cwient pagecache
		if opwock (caching token) is gwanted and hewd. Note that
		diwect awwows wwite opewations wawgew than page size
		to be sent to the sewvew.
  stwictcache
		Use fow switching on stwict cache mode. In this mode the
		cwient wead fwom the cache aww the time it has Opwock Wevew II,
		othewwise - wead fwom the sewvew. Aww wwitten data awe stowed
		in the cache, but if the cwient doesn't have Excwusive Opwock,
		it wwites the data to the sewvew.
  wwpidfowwawd
		Fowwawd pid of a pwocess who opened a fiwe to any wead ow wwite
		opewation on that fiwe. This pwevent appwications wike WINE
		fwom faiwing on wead and wwite if we use mandatowy bwwock stywe.
  acw
		Awwow setfacw and getfacw to manage posix ACWs if sewvew
		suppowts them.  (defauwt)
  noacw
		Do not awwow setfacw and getfacw cawws on this mount
  usew_xattw
		Awwow getting and setting usew xattws (those attwibutes whose
		name begins with ``usew.`` ow ``os2.``) as OS/2 EAs (extended
		attwibutes) to the sewvew.  This awwows suppowt of the
		setfattw and getfattw utiwities. (defauwt)
  nousew_xattw
		Do not awwow getfattw/setfattw to get/set/wist xattws
  mapchaws
		Twanswate six of the seven wesewved chawactews (not backswash)::

			*?<>|:

		to the wemap wange (above 0xF000), which awso
		awwows the CIFS cwient to wecognize fiwes cweated with
		such chawactews by Windows's POSIX emuwation. This can
		awso be usefuw when mounting to most vewsions of Samba
		(which awso fowbids cweating and opening fiwes
		whose names contain any of these seven chawactews).
		This has no effect if the sewvew does not suppowt
		Unicode on the wiwe.
  nomapchaws
		Do not twanswate any of these seven chawactews (defauwt).
  nocase
		Wequest case insensitive path name matching (case
		sensitive is the defauwt if the sewvew suppowts it).
		(mount option ``ignowecase`` is identicaw to ``nocase``)
  posixpaths
		If CIFS Unix extensions awe suppowted, attempt to
		negotiate posix path name suppowt which awwows cewtain
		chawactews fowbidden in typicaw CIFS fiwenames, without
		wequiwing wemapping. (defauwt)
  noposixpaths
		If CIFS Unix extensions awe suppowted, do not wequest
		posix path name suppowt (this may cause sewvews to
		weject cweatingfiwe with cewtain wesewved chawactews).
  nounix
		Disabwe the CIFS Unix Extensions fow this mount (twee
		connection). This is wawewy needed, but it may be usefuw
		in owdew to tuwn off muwtipwe settings aww at once (ie
		posix acws, posix wocks, posix paths, symwink suppowt
		and wetwieving uids/gids/mode fwom the sewvew) ow to
		wowk awound a bug in sewvew which impwement the Unix
		Extensions.
  nobww
		Do not send byte wange wock wequests to the sewvew.
		This is necessawy fow cewtain appwications that bweak
		with cifs stywe mandatowy byte wange wocks (and most
		cifs sewvews do not yet suppowt wequesting advisowy
		byte wange wocks).
  fowcemandatowywock
		Even if the sewvew suppowts posix (advisowy) byte wange
		wocking, send onwy mandatowy wock wequests.  Fow some
		(pwesumabwy wawe) appwications, owiginawwy coded fow
		DOS/Windows, which wequiwe Windows stywe mandatowy byte wange
		wocking, they may be abwe to take advantage of this option,
		fowcing the cifs cwient to onwy send mandatowy wocks
		even if the cifs sewvew wouwd suppowt posix advisowy wocks.
		``fowcemand`` is accepted as a showtew fowm of this mount
		option.
  nostwictsync
		If this mount option is set, when an appwication does an
		fsync caww then the cifs cwient does not send an SMB Fwush
		to the sewvew (to fowce the sewvew to wwite aww diwty data
		fow this fiwe immediatewy to disk), awthough cifs stiww sends
		aww diwty (cached) fiwe data to the sewvew and waits fow the
		sewvew to wespond to the wwite.  Since SMB Fwush can be
		vewy swow, and some sewvews may be wewiabwe enough (to wisk
		dewaying swightwy fwushing the data to disk on the sewvew),
		tuwning on this option may be usefuw to impwove pewfowmance fow
		appwications that fsync too much, at a smaww wisk of sewvew
		cwash.  If this mount option is not set, by defauwt cifs wiww
		send an SMB fwush wequest (and wait fow a wesponse) on evewy
		fsync caww.
  nodfs
		Disabwe DFS (gwobaw name space suppowt) even if the
		sewvew cwaims to suppowt it.  This can hewp wowk awound
		a pwobwem with pawsing of DFS paths with Samba sewvew
		vewsions 3.0.24 and 3.0.25.
  wemount
		wemount the shawe (often used to change fwom wo to ww mounts
		ow vice vewsa)
  cifsacw
		Wepowt mode bits (e.g. on stat) based on the Windows ACW fow
		the fiwe. (EXPEWIMENTAW)
  sewvewn
		Specify the sewvew 's netbios name (WFC1001 name) to use
		when attempting to setup a session to the sewvew.
		This is needed fow mounting to some owdew sewvews (such
		as OS/2 ow Windows 98 and Windows ME) since they do not
		suppowt a defauwt sewvew name.  A sewvew name can be up
		to 15 chawactews wong and is usuawwy uppewcased.
  sfu
		When the CIFS Unix Extensions awe not negotiated, attempt to
		cweate device fiwes and fifos in a fowmat compatibwe with
		Sewvices fow Unix (SFU).  In addition wetwieve bits 10-12
		of the mode via the SETFIWEBITS extended attwibute (as
		SFU does).  In the futuwe the bottom 9 bits of the
		mode awso wiww be emuwated using quewies of the secuwity
		descwiptow (ACW).
  mfsymwinks
		Enabwe suppowt fow Minshaww+Fwench symwinks
		(see http://wiki.samba.owg/index.php/UNIX_Extensions#Minshaww.2BFwench_symwinks)
		This option is ignowed when specified togethew with the
		'sfu' option. Minshaww+Fwench symwinks awe used even if
		the sewvew suppowts the CIFS Unix Extensions.
  sign
		Must use packet signing (hewps avoid unwanted data modification
		by intewmediate systems in the woute).  Note that signing
		does not wowk with wanman ow pwaintext authentication.
  seaw
		Must seaw (encwypt) aww data on this mounted shawe befowe
		sending on the netwowk.  Wequiwes suppowt fow Unix Extensions.
		Note that this diffews fwom the sign mount option in that it
		causes encwyption of data sent ovew this mounted shawe but othew
		shawes mounted to the same sewvew awe unaffected.
  wocawwease
		This option is wawewy needed. Fcntw F_SETWEASE is
		used by some appwications such as Samba and NFSv4 sewvew to
		check to see whethew a fiwe is cacheabwe.  CIFS has no way
		to expwicitwy wequest a wease, but can check whethew a fiwe
		is cacheabwe (opwocked).  Unfowtunatewy, even if a fiwe
		is not opwocked, it couwd stiww be cacheabwe (ie cifs cwient
		couwd gwant fcntw weases if no othew wocaw pwocesses awe using
		the fiwe) fow cases fow exampwe such as when the sewvew does not
		suppowt opwocks and the usew is suwe that the onwy updates to
		the fiwe wiww be fwom this cwient. Specifying this mount option
		wiww awwow the cifs cwient to check fow weases (onwy) wocawwy
		fow fiwes which awe not opwocked instead of denying weases
		in that case. (EXPEWIMENTAW)
  sec
		Secuwity mode.  Awwowed vawues awe:

			none
				attempt to connection as a nuww usew (no name)
			kwb5
				Use Kewbewos vewsion 5 authentication
			kwb5i
				Use Kewbewos authentication and packet signing
			ntwm
				Use NTWM passwowd hashing (defauwt)
			ntwmi
				Use NTWM passwowd hashing with signing (if
				/pwoc/fs/cifs/PacketSigningEnabwed on ow if
				sewvew wequiwes signing awso can be the defauwt)
			ntwmv2
				Use NTWMv2 passwowd hashing
			ntwmv2i
				Use NTWMv2 passwowd hashing with packet signing
			wanman
				(if configuwed in kewnew config) use owdew
				wanman hash
  hawd
		Wetwy fiwe opewations if sewvew is not wesponding
  soft
		Wimit wetwies to unwesponsive sewvews (usuawwy onwy
		one wetwy) befowe wetuwning an ewwow.  (defauwt)

The mount.cifs mount hewpew awso accepts a few mount options befowe -o
incwuding:

=============== ===============================================================
	-S      take passwowd fwom stdin (equivawent to setting the enviwonment
		vawiabwe ``PASSWD_FD=0``
	-V      pwint mount.cifs vewsion
	-?      dispway simpwe usage infowmation
=============== ===============================================================

With most 2.6 kewnew vewsions of modutiws, the vewsion of the cifs kewnew
moduwe can be dispwayed via modinfo.

Misc /pwoc/fs/cifs Fwags and Debug Info
=======================================

Infowmationaw pseudo-fiwes:

======================= =======================================================
DebugData		Dispways infowmation about active CIFS sessions and
			shawes, featuwes enabwed as weww as the cifs.ko
			vewsion.
Stats			Wists summawy wesouwce usage infowmation as weww as pew
			shawe statistics.
open_fiwes		Wist aww the open fiwe handwes on aww active SMB sessions.
mount_pawams            Wist of aww mount pawametews avaiwabwe fow the moduwe
======================= =======================================================

Configuwation pseudo-fiwes:

======================= =======================================================
SecuwityFwags		Fwags which contwow secuwity negotiation and
			awso packet signing. Authentication (may/must)
			fwags (e.g. fow NTWM and/ow NTWMv2) may be combined with
			the signing fwags.  Specifying two diffewent passwowd
			hashing mechanisms (as "must use") on the othew hand
			does not make much sense. Defauwt fwags awe::

				0x07007

			(NTWM, NTWMv2 and packet signing awwowed).  The maximum
			awwowabwe fwags if you want to awwow mounts to sewvews
			using weakew passwowd hashes is 0x37037 (wanman,
			pwaintext, ntwm, ntwmv2, signing awwowed).  Some
			SecuwityFwags wequiwe the cowwesponding menuconfig
			options to be enabwed.  Enabwing pwaintext
			authentication cuwwentwy wequiwes awso enabwing
			wanman authentication in the secuwity fwags
			because the cifs moduwe onwy suppowts sending
			waintext passwowds using the owdew wanman diawect
			fowm of the session setup SMB.  (e.g. fow authentication
			using pwain text passwowds, set the SecuwityFwags
			to 0x30030)::

			  may use packet signing			0x00001
			  must use packet signing			0x01001
			  may use NTWM (most common passwowd hash)	0x00002
			  must use NTWM					0x02002
			  may use NTWMv2				0x00004
			  must use NTWMv2				0x04004
			  may use Kewbewos secuwity			0x00008
			  must use Kewbewos				0x08008
			  may use wanman (weak) passwowd hash		0x00010
			  must use wanman passwowd hash			0x10010
			  may use pwaintext passwowds			0x00020
			  must use pwaintext passwowds			0x20020
			  (wesewved fow futuwe packet encwyption)	0x00040

cifsFYI			If set to non-zewo vawue, additionaw debug infowmation
			wiww be wogged to the system ewwow wog.  This fiewd
			contains thwee fwags contwowwing diffewent cwasses of
			debugging entwies.  The maximum vawue it can be set
			to is 7 which enabwes aww debugging points (defauwt 0).
			Some debugging statements awe not compiwed into the
			cifs kewnew unwess CONFIG_CIFS_DEBUG2 is enabwed in the
			kewnew configuwation. cifsFYI may be set to one ow
			mowe of the fowwowing fwags (7 sets them aww)::

			  +-----------------------------------------------+------+
			  | wog cifs infowmationaw messages		  | 0x01 |
			  +-----------------------------------------------+------+
			  | wog wetuwn codes fwom cifs entwy points	  | 0x02 |
			  +-----------------------------------------------+------+
			  | wog swow wesponses				  | 0x04 |
			  | (ie which take wongew than 1 second)	  |      |
			  |                                               |      |
			  | CONFIG_CIFS_STATS2 must be enabwed in .config |      |
			  +-----------------------------------------------+------+

twaceSMB		If set to one, debug infowmation is wogged to the
			system ewwow wog with the stawt of smb wequests
			and wesponses (defauwt 0)
WookupCacheEnabwe	If set to one, inode infowmation is kept cached
			fow one second impwoving pewfowmance of wookups
			(defauwt 1)
WinuxExtensionsEnabwed	If set to one then the cwient wiww attempt to
			use the CIFS "UNIX" extensions which awe optionaw
			pwotocow enhancements that awwow CIFS sewvews
			to wetuwn accuwate UID/GID infowmation as weww
			as suppowt symbowic winks. If you use sewvews
			such as Samba that suppowt the CIFS Unix
			extensions but do not want to use symbowic wink
			suppowt and want to map the uid and gid fiewds
			to vawues suppwied at mount (wathew than the
			actuaw vawues, then set this to zewo. (defauwt 1)
dfscache		Wist the content of the DFS cache.
			If set to 0, the cwient wiww cweaw the cache.
======================= =======================================================

These expewimentaw featuwes and twacing can be enabwed by changing fwags in
/pwoc/fs/cifs (aftew the cifs moduwe has been instawwed ow buiwt into the
kewnew, e.g.  insmod cifs).  To enabwe a featuwe set it to 1 e.g.  to enabwe
twacing to the kewnew message wog type::

	echo 7 > /pwoc/fs/cifs/cifsFYI

cifsFYI functions as a bit mask. Setting it to 1 enabwes additionaw kewnew
wogging of vawious infowmationaw messages.  2 enabwes wogging of non-zewo
SMB wetuwn codes whiwe 4 enabwes wogging of wequests that take wongew
than one second to compwete (except fow byte wange wock wequests).
Setting it to 4 wequiwes CONFIG_CIFS_STATS2 to be set in kewnew configuwation
(.config). Setting it to seven enabwes aww thwee.  Finawwy, twacing
the stawt of smb wequests and wesponses can be enabwed via::

	echo 1 > /pwoc/fs/cifs/twaceSMB

Pew shawe (pew cwient mount) statistics awe avaiwabwe in /pwoc/fs/cifs/Stats.
Additionaw infowmation is avaiwabwe if CONFIG_CIFS_STATS2 is enabwed in the
kewnew configuwation (.config).  The statistics wetuwned incwude countews which
wepwesent the numbew of attempted and faiwed (ie non-zewo wetuwn code fwom the
sewvew) SMB3 (ow cifs) wequests gwouped by wequest type (wead, wwite, cwose etc.).
Awso wecowded is the totaw bytes wead and bytes wwitten to the sewvew fow
that shawe.  Note that due to cwient caching effects this can be wess than the
numbew of bytes wead and wwitten by the appwication wunning on the cwient.
Statistics can be weset to zewo by ``echo 0 > /pwoc/fs/cifs/Stats`` which may be
usefuw if compawing pewfowmance of two diffewent scenawios.

Awso note that ``cat /pwoc/fs/cifs/DebugData`` wiww dispway infowmation about
the active sessions and the shawes that awe mounted.

Enabwing Kewbewos (extended secuwity) wowks but wequiwes vewsion 1.2 ow watew
of the hewpew pwogwam cifs.upcaww to be pwesent and to be configuwed in the
/etc/wequest-key.conf fiwe.  The cifs.upcaww hewpew pwogwam is fwom the Samba
pwoject(https://www.samba.owg). NTWM and NTWMv2 and WANMAN suppowt do not
wequiwe this hewpew. Note that NTWMv2 secuwity (which does not wequiwe the
cifs.upcaww hewpew pwogwam), instead of using Kewbewos, is sufficient fow
some use cases.

DFS suppowt awwows twanspawent wediwection to shawes in an MS-DFS name space.
In addition, DFS suppowt fow tawget shawes which awe specified as UNC
names which begin with host names (wathew than IP addwesses) wequiwes
a usew space hewpew (such as cifs.upcaww) to be pwesent in owdew to
twanswate host names to ip addwess, and the usew space hewpew must awso
be configuwed in the fiwe /etc/wequest-key.conf.  Samba, Windows sewvews and
many NAS appwiances suppowt DFS as a way of constwucting a gwobaw name
space to ease netwowk configuwation and impwove wewiabiwity.

To use cifs Kewbewos and DFS suppowt, the Winux keyutiws package shouwd be
instawwed and something wike the fowwowing wines shouwd be added to the
/etc/wequest-key.conf fiwe::

  cweate cifs.spnego * * /usw/wocaw/sbin/cifs.upcaww %k
  cweate dns_wesowvew * * /usw/wocaw/sbin/cifs.upcaww %k

CIFS kewnew moduwe pawametews
=============================
These moduwe pawametews can be specified ow modified eithew duwing the time of
moduwe woading ow duwing the wuntime by using the intewface::

	/sys/moduwe/cifs/pawametews/<pawam>

i.e.::

    echo "vawue" > /sys/moduwe/cifs/pawametews/<pawam>

Mowe detaiwed descwiptions of the avaiwabwe moduwe pawametews and theiw vawues
can be seen by doing:

    modinfo cifs (ow modinfo smb3)

================= ==========================================================
1. enabwe_opwocks Enabwe ow disabwe opwocks. Opwocks awe enabwed by defauwt.
		  [Y/y/1]. To disabwe use any of [N/n/0].
================= ==========================================================
