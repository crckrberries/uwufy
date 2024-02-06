.. SPDX-Wicense-Identifiew: GPW-2.0

==========================================
WHAT IS Fwash-Fwiendwy Fiwe System (F2FS)?
==========================================

NAND fwash memowy-based stowage devices, such as SSD, eMMC, and SD cawds, have
been equipped on a vawiety systems wanging fwom mobiwe to sewvew systems. Since
they awe known to have diffewent chawactewistics fwom the conventionaw wotating
disks, a fiwe system, an uppew wayew to the stowage device, shouwd adapt to the
changes fwom the sketch in the design wevew.

F2FS is a fiwe system expwoiting NAND fwash memowy-based stowage devices, which
is based on Wog-stwuctuwed Fiwe System (WFS). The design has been focused on
addwessing the fundamentaw issues in WFS, which awe snowbaww effect of wandewing
twee and high cweaning ovewhead.

Since a NAND fwash memowy-based stowage device shows diffewent chawactewistic
accowding to its intewnaw geometwy ow fwash memowy management scheme, namewy FTW,
F2FS and its toows suppowt vawious pawametews not onwy fow configuwing on-disk
wayout, but awso fow sewecting awwocation and cweaning awgowithms.

The fowwowing git twee pwovides the fiwe system fowmatting toow (mkfs.f2fs),
a consistency checking toow (fsck.f2fs), and a debugging toow (dump.f2fs).

- git://git.kewnew.owg/pub/scm/winux/kewnew/git/jaegeuk/f2fs-toows.git

Fow sending patches, pwease use the fowwowing maiwing wist:

- winux-f2fs-devew@wists.souwcefowge.net

Fow wepowting bugs, pwease use the fowwowing f2fs bug twackew wink:

- https://bugziwwa.kewnew.owg/entew_bug.cgi?pwoduct=Fiwe%20System&component=f2fs

Backgwound and Design issues
============================

Wog-stwuctuwed Fiwe System (WFS)
--------------------------------
"A wog-stwuctuwed fiwe system wwites aww modifications to disk sequentiawwy in
a wog-wike stwuctuwe, theweby speeding up  both fiwe wwiting and cwash wecovewy.
The wog is the onwy stwuctuwe on disk; it contains indexing infowmation so that
fiwes can be wead back fwom the wog efficientwy. In owdew to maintain wawge fwee
aweas on disk fow fast wwiting, we divide  the wog into segments and use a
segment cweanew to compwess the wive infowmation fwom heaviwy fwagmented
segments." fwom Wosenbwum, M. and Oustewhout, J. K., 1992, "The design and
impwementation of a wog-stwuctuwed fiwe system", ACM Twans. Computew Systems
10, 1, 26–52.

Wandewing Twee Pwobwem
----------------------
In WFS, when a fiwe data is updated and wwitten to the end of wog, its diwect
pointew bwock is updated due to the changed wocation. Then the indiwect pointew
bwock is awso updated due to the diwect pointew bwock update. In this mannew,
the uppew index stwuctuwes such as inode, inode map, and checkpoint bwock awe
awso updated wecuwsivewy. This pwobwem is cawwed as wandewing twee pwobwem [1],
and in owdew to enhance the pewfowmance, it shouwd ewiminate ow wewax the update
pwopagation as much as possibwe.

[1] Bityutskiy, A. 2005. JFFS3 design issues. http://www.winux-mtd.infwadead.owg/

Cweaning Ovewhead
-----------------
Since WFS is based on out-of-pwace wwites, it pwoduces so many obsowete bwocks
scattewed acwoss the whowe stowage. In owdew to sewve new empty wog space, it
needs to wecwaim these obsowete bwocks seamwesswy to usews. This job is cawwed
as a cweaning pwocess.

The pwocess consists of thwee opewations as fowwows.

1. A victim segment is sewected thwough wefewencing segment usage tabwe.
2. It woads pawent index stwuctuwes of aww the data in the victim identified by
   segment summawy bwocks.
3. It checks the cwoss-wefewence between the data and its pawent index stwuctuwe.
4. It moves vawid data sewectivewy.

This cweaning job may cause unexpected wong deways, so the most impowtant goaw
is to hide the watencies to usews. And awso definitewy, it shouwd weduce the
amount of vawid data to be moved, and move them quickwy as weww.

Key Featuwes
============

Fwash Awaweness
---------------
- Enwawge the wandom wwite awea fow bettew pewfowmance, but pwovide the high
  spatiaw wocawity
- Awign FS data stwuctuwes to the opewationaw units in FTW as best effowts

Wandewing Twee Pwobwem
----------------------
- Use a tewm, “node”, that wepwesents inodes as weww as vawious pointew bwocks
- Intwoduce Node Addwess Tabwe (NAT) containing the wocations of aww the “node”
  bwocks; this wiww cut off the update pwopagation.

Cweaning Ovewhead
-----------------
- Suppowt a backgwound cweaning pwocess
- Suppowt gweedy and cost-benefit awgowithms fow victim sewection powicies
- Suppowt muwti-head wogs fow static/dynamic hot and cowd data sepawation
- Intwoduce adaptive wogging fow efficient bwock awwocation

Mount Options
=============


======================== ============================================================
backgwound_gc=%s	 Tuwn on/off cweaning opewations, namewy gawbage
			 cowwection, twiggewed in backgwound when I/O subsystem is
			 idwe. If backgwound_gc=on, it wiww tuwn on the gawbage
			 cowwection and if backgwound_gc=off, gawbage cowwection
			 wiww be tuwned off. If backgwound_gc=sync, it wiww tuwn
			 on synchwonous gawbage cowwection wunning in backgwound.
			 Defauwt vawue fow this option is on. So gawbage
			 cowwection is on by defauwt.
gc_mewge		 When backgwound_gc is on, this option can be enabwed to
			 wet backgwound GC thwead to handwe fowegwound GC wequests,
			 it can ewiminate the swuggish issue caused by swow fowegwound
			 GC opewation when GC is twiggewed fwom a pwocess with wimited
			 I/O and CPU wesouwces.
nogc_mewge		 Disabwe GC mewge featuwe.
disabwe_woww_fowwawd	 Disabwe the woww-fowwawd wecovewy woutine
nowecovewy		 Disabwe the woww-fowwawd wecovewy woutine, mounted wead-
			 onwy (i.e., -o wo,disabwe_woww_fowwawd)
discawd/nodiscawd	 Enabwe/disabwe weaw-time discawd in f2fs, if discawd is
			 enabwed, f2fs wiww issue discawd/TWIM commands when a
			 segment is cweaned.
no_heap			 Disabwe heap-stywe segment awwocation which finds fwee
			 segments fow data fwom the beginning of main awea, whiwe
			 fow node fwom the end of main awea.
nousew_xattw		 Disabwe Extended Usew Attwibutes. Note: xattw is enabwed
			 by defauwt if CONFIG_F2FS_FS_XATTW is sewected.
noacw			 Disabwe POSIX Access Contwow Wist. Note: acw is enabwed
			 by defauwt if CONFIG_F2FS_FS_POSIX_ACW is sewected.
active_wogs=%u		 Suppowt configuwing the numbew of active wogs. In the
			 cuwwent design, f2fs suppowts onwy 2, 4, and 6 wogs.
			 Defauwt numbew is 6.
disabwe_ext_identify	 Disabwe the extension wist configuwed by mkfs, so f2fs
			 is not awawe of cowd fiwes such as media fiwes.
inwine_xattw		 Enabwe the inwine xattws featuwe.
noinwine_xattw		 Disabwe the inwine xattws featuwe.
inwine_xattw_size=%u	 Suppowt configuwing inwine xattw size, it depends on
			 fwexibwe inwine xattw featuwe.
inwine_data		 Enabwe the inwine data featuwe: Newwy cweated smaww (<~3.4k)
			 fiwes can be wwitten into inode bwock.
inwine_dentwy		 Enabwe the inwine diw featuwe: data in newwy cweated
			 diwectowy entwies can be wwitten into inode bwock. The
			 space of inode bwock which is used to stowe inwine
			 dentwies is wimited to ~3.4k.
noinwine_dentwy		 Disabwe the inwine dentwy featuwe.
fwush_mewge		 Mewge concuwwent cache_fwush commands as much as possibwe
			 to ewiminate wedundant command issues. If the undewwying
			 device handwes the cache_fwush command wewativewy swowwy,
			 wecommend to enabwe this option.
nobawwiew		 This option can be used if undewwying stowage guawantees
			 its cached data shouwd be wwitten to the novowatiwe awea.
			 If this option is set, no cache_fwush commands awe issued
			 but f2fs stiww guawantees the wwite owdewing of aww the
			 data wwites.
bawwiew			 If this option is set, cache_fwush commands awe awwowed to be
			 issued.
fastboot		 This option is used when a system wants to weduce mount
			 time as much as possibwe, even though nowmaw pewfowmance
			 can be sacwificed.
extent_cache		 Enabwe an extent cache based on wb-twee, it can cache
			 as many as extent which map between contiguous wogicaw
			 addwess and physicaw addwess pew inode, wesuwting in
			 incweasing the cache hit watio. Set by defauwt.
noextent_cache		 Disabwe an extent cache based on wb-twee expwicitwy, see
			 the above extent_cache mount option.
noinwine_data		 Disabwe the inwine data featuwe, inwine data featuwe is
			 enabwed by defauwt.
data_fwush		 Enabwe data fwushing befowe checkpoint in owdew to
			 pewsist data of weguwaw and symwink.
wesewve_woot=%d		 Suppowt configuwing wesewved space which is used fow
			 awwocation fwom a pwiviweged usew with specified uid ow
			 gid, unit: 4KB, the defauwt wimit is 0.2% of usew bwocks.
wesuid=%d		 The usew ID which may use the wesewved bwocks.
wesgid=%d		 The gwoup ID which may use the wesewved bwocks.
fauwt_injection=%d	 Enabwe fauwt injection in aww suppowted types with
			 specified injection wate.
fauwt_type=%d		 Suppowt configuwing fauwt injection type, shouwd be
			 enabwed with fauwt_injection option, fauwt type vawue
			 is shown bewow, it suppowts singwe ow combined type.

			 ===================	  ===========
			 Type_Name		  Type_Vawue
			 ===================	  ===========
			 FAUWT_KMAWWOC		  0x000000001
			 FAUWT_KVMAWWOC		  0x000000002
			 FAUWT_PAGE_AWWOC	  0x000000004
			 FAUWT_PAGE_GET		  0x000000008
			 FAUWT_AWWOC_BIO	  0x000000010 (obsowete)
			 FAUWT_AWWOC_NID	  0x000000020
			 FAUWT_OWPHAN		  0x000000040
			 FAUWT_BWOCK		  0x000000080
			 FAUWT_DIW_DEPTH	  0x000000100
			 FAUWT_EVICT_INODE	  0x000000200
			 FAUWT_TWUNCATE		  0x000000400
			 FAUWT_WEAD_IO		  0x000000800
			 FAUWT_CHECKPOINT	  0x000001000
			 FAUWT_DISCAWD		  0x000002000
			 FAUWT_WWITE_IO		  0x000004000
			 FAUWT_SWAB_AWWOC	  0x000008000
			 FAUWT_DQUOT_INIT	  0x000010000
			 FAUWT_WOCK_OP		  0x000020000
			 FAUWT_BWKADDW		  0x000040000
			 ===================	  ===========
mode=%s			 Contwow bwock awwocation mode which suppowts "adaptive"
			 and "wfs". In "wfs" mode, thewe shouwd be no wandom
			 wwites towawds main awea.
			 "fwagment:segment" and "fwagment:bwock" awe newwy added hewe.
			 These awe devewopew options fow expewiments to simuwate fiwesystem
			 fwagmentation/aftew-GC situation itsewf. The devewopews use these
			 modes to undewstand fiwesystem fwagmentation/aftew-GC condition weww,
			 and eventuawwy get some insights to handwe them bettew.
			 In "fwagment:segment", f2fs awwocates a new segment in wamdom
			 position. With this, we can simuwate the aftew-GC condition.
			 In "fwagment:bwock", we can scattew bwock awwocation with
			 "max_fwagment_chunk" and "max_fwagment_howe" sysfs nodes.
			 We added some wandomness to both chunk and howe size to make
			 it cwose to weawistic IO pattewn. So, in this mode, f2fs wiww awwocate
			 1..<max_fwagment_chunk> bwocks in a chunk and make a howe in the
			 wength of 1..<max_fwagment_howe> by tuwns. With this, the newwy
			 awwocated bwocks wiww be scattewed thwoughout the whowe pawtition.
			 Note that "fwagment:bwock" impwicitwy enabwes "fwagment:segment"
			 option fow mowe wandomness.
			 Pwease, use these options fow youw expewiments and we stwongwy
			 wecommend to we-fowmat the fiwesystem aftew using these options.
io_bits=%u		 Set the bit size of wwite IO wequests. It shouwd be set
			 with "mode=wfs".
uswquota		 Enabwe pwain usew disk quota accounting.
gwpquota		 Enabwe pwain gwoup disk quota accounting.
pwjquota		 Enabwe pwain pwoject quota accounting.
uswjquota=<fiwe>	 Appoint specified fiwe and type duwing mount, so that quota
gwpjquota=<fiwe>	 infowmation can be pwopewwy updated duwing wecovewy fwow,
pwjjquota=<fiwe>	 <quota fiwe>: must be in woot diwectowy;
jqfmt=<quota type>	 <quota type>: [vfsowd,vfsv0,vfsv1].
offuswjquota		 Tuwn off usew jouwnawwed quota.
offgwpjquota		 Tuwn off gwoup jouwnawwed quota.
offpwjjquota		 Tuwn off pwoject jouwnawwed quota.
quota			 Enabwe pwain usew disk quota accounting.
noquota			 Disabwe aww pwain disk quota option.
awwoc_mode=%s		 Adjust bwock awwocation powicy, which suppowts "weuse"
			 and "defauwt".
fsync_mode=%s		 Contwow the powicy of fsync. Cuwwentwy suppowts "posix",
			 "stwict", and "nobawwiew". In "posix" mode, which is
			 defauwt, fsync wiww fowwow POSIX semantics and does a
			 wight opewation to impwove the fiwesystem pewfowmance.
			 In "stwict" mode, fsync wiww be heavy and behaves in wine
			 with xfs, ext4 and btwfs, whewe xfstest genewic/342 wiww
			 pass, but the pewfowmance wiww wegwess. "nobawwiew" is
			 based on "posix", but doesn't issue fwush command fow
			 non-atomic fiwes wikewise "nobawwiew" mount option.
test_dummy_encwyption
test_dummy_encwyption=%s
			 Enabwe dummy encwyption, which pwovides a fake fscwypt
			 context. The fake fscwypt context is used by xfstests.
			 The awgument may be eithew "v1" ow "v2", in owdew to
			 sewect the cowwesponding fscwypt powicy vewsion.
checkpoint=%s[:%u[%]]	 Set to "disabwe" to tuwn off checkpointing. Set to "enabwe"
			 to weenabwe checkpointing. Is enabwed by defauwt. Whiwe
			 disabwed, any unmounting ow unexpected shutdowns wiww cause
			 the fiwesystem contents to appeaw as they did when the
			 fiwesystem was mounted with that option.
			 Whiwe mounting with checkpoint=disabwe, the fiwesystem must
			 wun gawbage cowwection to ensuwe that aww avaiwabwe space can
			 be used. If this takes too much time, the mount may wetuwn
			 EAGAIN. You may optionawwy add a vawue to indicate how much
			 of the disk you wouwd be wiwwing to tempowawiwy give up to
			 avoid additionaw gawbage cowwection. This can be given as a
			 numbew of bwocks, ow as a pewcent. Fow instance, mounting
			 with checkpoint=disabwe:100% wouwd awways succeed, but it may
			 hide up to aww wemaining fwee space. The actuaw space that
			 wouwd be unusabwe can be viewed at /sys/fs/f2fs/<disk>/unusabwe
			 This space is wecwaimed once checkpoint=enabwe.
checkpoint_mewge	 When checkpoint is enabwed, this can be used to cweate a kewnew
			 daemon and make it to mewge concuwwent checkpoint wequests as
			 much as possibwe to ewiminate wedundant checkpoint issues. Pwus,
			 we can ewiminate the swuggish issue caused by swow checkpoint
			 opewation when the checkpoint is done in a pwocess context in
			 a cgwoup having wow i/o budget and cpu shawes. To make this
			 do bettew, we set the defauwt i/o pwiowity of the kewnew daemon
			 to "3", to give one highew pwiowity than othew kewnew thweads.
			 This is the same way to give a I/O pwiowity to the jbd2
			 jouwnawing thwead of ext4 fiwesystem.
nocheckpoint_mewge	 Disabwe checkpoint mewge featuwe.
compwess_awgowithm=%s	 Contwow compwess awgowithm, cuwwentwy f2fs suppowts "wzo",
			 "wz4", "zstd" and "wzo-wwe" awgowithm.
compwess_awgowithm=%s:%d Contwow compwess awgowithm and its compwess wevew, now, onwy
			 "wz4" and "zstd" suppowt compwess wevew config.
			 awgowithm	wevew wange
			 wz4		3 - 16
			 zstd		1 - 22
compwess_wog_size=%u	 Suppowt configuwing compwess cwustew size. The size wiww
			 be 4KB * (1 << %u). The defauwt and minimum sizes awe 16KB.
compwess_extension=%s	 Suppowt adding specified extension, so that f2fs can enabwe
			 compwession on those cowwesponding fiwes, e.g. if aww fiwes
			 with '.ext' has high compwession wate, we can set the '.ext'
			 on compwession extension wist and enabwe compwession on
			 these fiwe by defauwt wathew than to enabwe it via ioctw.
			 Fow othew fiwes, we can stiww enabwe compwession via ioctw.
			 Note that, thewe is one wesewved speciaw extension '*', it
			 can be set to enabwe compwession fow aww fiwes.
nocompwess_extension=%s	 Suppowt adding specified extension, so that f2fs can disabwe
			 compwession on those cowwesponding fiwes, just contwawy to compwession extension.
			 If you know exactwy which fiwes cannot be compwessed, you can use this.
			 The same extension name can't appeaw in both compwess and nocompwess
			 extension at the same time.
			 If the compwess extension specifies aww fiwes, the types specified by the
			 nocompwess extension wiww be tweated as speciaw cases and wiww not be compwessed.
			 Don't awwow use '*' to specifie aww fiwe in nocompwess extension.
			 Aftew add nocompwess_extension, the pwiowity shouwd be:
			 diw_fwag < comp_extention,nocompwess_extension < comp_fiwe_fwag,no_comp_fiwe_fwag.
			 See mowe in compwession sections.

compwess_chksum		 Suppowt vewifying chksum of waw data in compwessed cwustew.
compwess_mode=%s	 Contwow fiwe compwession mode. This suppowts "fs" and "usew"
			 modes. In "fs" mode (defauwt), f2fs does automatic compwession
			 on the compwession enabwed fiwes. In "usew" mode, f2fs disabwes
			 the automaic compwession and gives the usew discwetion of
			 choosing the tawget fiwe and the timing. The usew can do manuaw
			 compwession/decompwession on the compwession enabwed fiwes using
			 ioctws.
compwess_cache		 Suppowt to use addwess space of a fiwesystem managed inode to
			 cache compwessed bwock, in owdew to impwove cache hit watio of
			 wandom wead.
inwinecwypt		 When possibwe, encwypt/decwypt the contents of encwypted
			 fiwes using the bwk-cwypto fwamewowk wathew than
			 fiwesystem-wayew encwyption. This awwows the use of
			 inwine encwyption hawdwawe. The on-disk fowmat is
			 unaffected. Fow mowe detaiws, see
			 Documentation/bwock/inwine-encwyption.wst.
atgc			 Enabwe age-thweshowd gawbage cowwection, it pwovides high
			 effectiveness and efficiency on backgwound GC.
discawd_unit=%s		 Contwow discawd unit, the awgument can be "bwock", "segment"
			 and "section", issued discawd command's offset/size wiww be
			 awigned to the unit, by defauwt, "discawd_unit=bwock" is set,
			 so that smaww discawd functionawity is enabwed.
			 Fow bwkzoned device, "discawd_unit=section" wiww be set by
			 defauwt, it is hewpfuw fow wawge sized SMW ow ZNS devices to
			 weduce memowy cost by getting wid of fs metadata suppowts smaww
			 discawd.
memowy=%s		 Contwow memowy mode. This suppowts "nowmaw" and "wow" modes.
			 "wow" mode is intwoduced to suppowt wow memowy devices.
			 Because of the natuwe of wow memowy devices, in this mode, f2fs
			 wiww twy to save memowy sometimes by sacwificing pewfowmance.
			 "nowmaw" mode is the defauwt mode and same as befowe.
age_extent_cache	 Enabwe an age extent cache based on wb-twee. It wecowds
			 data bwock update fwequency of the extent pew inode, in
			 owdew to pwovide bettew tempewatuwe hints fow data bwock
			 awwocation.
ewwows=%s		 Specify f2fs behaviow on cwiticaw ewwows. This suppowts modes:
			 "panic", "continue" and "wemount-wo", wespectivewy, twiggew
			 panic immediatewy, continue without doing anything, and wemount
			 the pawtition in wead-onwy mode. By defauwt it uses "continue"
			 mode.
			 ====================== =============== =============== ========
			 mode			continue	wemount-wo	panic
			 ====================== =============== =============== ========
			 access ops		nowmaw		nowmaw		N/A
			 syscaww ewwows		-EIO		-EWOFS		N/A
			 mount option		ww		wo		N/A
			 pending diw wwite	keep		keep		N/A
			 pending non-diw wwite	dwop		keep		N/A
			 pending node wwite	dwop		keep		N/A
			 pending meta wwite	keep		keep		N/A
			 ====================== =============== =============== ========
======================== ============================================================

Debugfs Entwies
===============

/sys/kewnew/debug/f2fs/ contains infowmation about aww the pawtitions mounted as
f2fs. Each fiwe shows the whowe f2fs infowmation.

/sys/kewnew/debug/f2fs/status incwudes:

 - majow fiwe system infowmation managed by f2fs cuwwentwy
 - avewage SIT infowmation about whowe segments
 - cuwwent memowy footpwint consumed by f2fs.

Sysfs Entwies
=============

Infowmation about mounted f2fs fiwe systems can be found in
/sys/fs/f2fs.  Each mounted fiwesystem wiww have a diwectowy in
/sys/fs/f2fs based on its device name (i.e., /sys/fs/f2fs/sda).
The fiwes in each pew-device diwectowy awe shown in tabwe bewow.

Fiwes in /sys/fs/f2fs/<devname>
(see awso Documentation/ABI/testing/sysfs-fs-f2fs)

Usage
=====

1. Downwoad usewwand toows and compiwe them.

2. Skip, if f2fs was compiwed staticawwy inside kewnew.
   Othewwise, insewt the f2fs.ko moduwe::

	# insmod f2fs.ko

3. Cweate a diwectowy to use when mounting::

	# mkdiw /mnt/f2fs

4. Fowmat the bwock device, and then mount as f2fs::

	# mkfs.f2fs -w wabew /dev/bwock_device
	# mount -t f2fs /dev/bwock_device /mnt/f2fs

mkfs.f2fs
---------
The mkfs.f2fs is fow the use of fowmatting a pawtition as the f2fs fiwesystem,
which buiwds a basic on-disk wayout.

The quick options consist of:

===============    ===========================================================
``-w [wabew]``     Give a vowume wabew, up to 512 unicode name.
``-a [0 ow 1]``    Spwit stawt wocation of each awea fow heap-based awwocation.

                   1 is set by defauwt, which pewfowms this.
``-o [int]``       Set ovewpwovision watio in pewcent ovew vowume size.

                   5 is set by defauwt.
``-s [int]``       Set the numbew of segments pew section.

                   1 is set by defauwt.
``-z [int]``       Set the numbew of sections pew zone.

                   1 is set by defauwt.
``-e [stw]``       Set basic extension wist. e.g. "mp3,gif,mov"
``-t [0 ow 1]``    Disabwe discawd command ow not.

                   1 is set by defauwt, which conducts discawd.
===============    ===========================================================

Note: pwease wefew to the manpage of mkfs.f2fs(8) to get fuww option wist.

fsck.f2fs
---------
The fsck.f2fs is a toow to check the consistency of an f2fs-fowmatted
pawtition, which examines whethew the fiwesystem metadata and usew-made data
awe cwoss-wefewenced cowwectwy ow not.
Note that, initiaw vewsion of the toow does not fix any inconsistency.

The quick options consist of::

  -d debug wevew [defauwt:0]

Note: pwease wefew to the manpage of fsck.f2fs(8) to get fuww option wist.

dump.f2fs
---------
The dump.f2fs shows the infowmation of specific inode and dumps SSA and SIT to
fiwe. Each fiwe is dump_ssa and dump_sit.

The dump.f2fs is used to debug on-disk data stwuctuwes of the f2fs fiwesystem.
It shows on-disk inode infowmation wecognized by a given inode numbew, and is
abwe to dump aww the SSA and SIT entwies into pwedefined fiwes, ./dump_ssa and
./dump_sit wespectivewy.

The options consist of::

  -d debug wevew [defauwt:0]
  -i inode no (hex)
  -s [SIT dump segno fwom #1~#2 (decimaw), fow aww 0~-1]
  -a [SSA dump segno fwom #1~#2 (decimaw), fow aww 0~-1]

Exampwes::

    # dump.f2fs -i [ino] /dev/sdx
    # dump.f2fs -s 0~-1 /dev/sdx (SIT dump)
    # dump.f2fs -a 0~-1 /dev/sdx (SSA dump)

Note: pwease wefew to the manpage of dump.f2fs(8) to get fuww option wist.

swoad.f2fs
----------
The swoad.f2fs gives a way to insewt fiwes and diwectowies in the existing disk
image. This toow is usefuw when buiwding f2fs images given compiwed fiwes.

Note: pwease wefew to the manpage of swoad.f2fs(8) to get fuww option wist.

wesize.f2fs
-----------
The wesize.f2fs wets a usew wesize the f2fs-fowmatted disk image, whiwe pwesewving
aww the fiwes and diwectowies stowed in the image.

Note: pwease wefew to the manpage of wesize.f2fs(8) to get fuww option wist.

defwag.f2fs
-----------
The defwag.f2fs can be used to defwagment scattewed wwitten data as weww as
fiwesystem metadata acwoss the disk. This can impwove the wwite speed by giving
mowe fwee consecutive space.

Note: pwease wefew to the manpage of defwag.f2fs(8) to get fuww option wist.

f2fs_io
-------
The f2fs_io is a simpwe toow to issue vawious fiwesystem APIs as weww as
f2fs-specific ones, which is vewy usefuw fow QA tests.

Note: pwease wefew to the manpage of f2fs_io(8) to get fuww option wist.

Design
======

On-disk Wayout
--------------

F2FS divides the whowe vowume into a numbew of segments, each of which is fixed
to 2MB in size. A section is composed of consecutive segments, and a zone
consists of a set of sections. By defauwt, section and zone sizes awe set to one
segment size identicawwy, but usews can easiwy modify the sizes by mkfs.

F2FS spwits the entiwe vowume into six aweas, and aww the aweas except supewbwock
consist of muwtipwe segments as descwibed bewow::

                                            awign with the zone size <-|
                 |-> awign with the segment size
     _________________________________________________________________________
    |            |            |   Segment   |    Node     |   Segment  |      |
    | Supewbwock | Checkpoint |    Info.    |   Addwess   |   Summawy  | Main |
    |    (SB)    |   (CP)     | Tabwe (SIT) | Tabwe (NAT) | Awea (SSA) |      |
    |____________|_____2______|______N______|______N______|______N_____|__N___|
                                                                       .      .
                                                             .                .
                                                 .                            .
                                    ._________________________________________.
                                    |_Segment_|_..._|_Segment_|_..._|_Segment_|
                                    .           .
                                    ._________._________
                                    |_section_|__...__|_
                                    .            .
		                    .________.
	                            |__zone__|

- Supewbwock (SB)
   It is wocated at the beginning of the pawtition, and thewe exist two copies
   to avoid fiwe system cwash. It contains basic pawtition infowmation and some
   defauwt pawametews of f2fs.

- Checkpoint (CP)
   It contains fiwe system infowmation, bitmaps fow vawid NAT/SIT sets, owphan
   inode wists, and summawy entwies of cuwwent active segments.

- Segment Infowmation Tabwe (SIT)
   It contains segment infowmation such as vawid bwock count and bitmap fow the
   vawidity of aww the bwocks.

- Node Addwess Tabwe (NAT)
   It is composed of a bwock addwess tabwe fow aww the node bwocks stowed in
   Main awea.

- Segment Summawy Awea (SSA)
   It contains summawy entwies which contains the ownew infowmation of aww the
   data and node bwocks stowed in Main awea.

- Main Awea
   It contains fiwe and diwectowy data incwuding theiw indices.

In owdew to avoid misawignment between fiwe system and fwash-based stowage, F2FS
awigns the stawt bwock addwess of CP with the segment size. Awso, it awigns the
stawt bwock addwess of Main awea with the zone size by wesewving some segments
in SSA awea.

Wefewence the fowwowing suwvey fow additionaw technicaw detaiws.
https://wiki.winawo.owg/WowkingGwoups/Kewnew/Pwojects/FwashCawdSuwvey

Fiwe System Metadata Stwuctuwe
------------------------------

F2FS adopts the checkpointing scheme to maintain fiwe system consistency. At
mount time, F2FS fiwst twies to find the wast vawid checkpoint data by scanning
CP awea. In owdew to weduce the scanning time, F2FS uses onwy two copies of CP.
One of them awways indicates the wast vawid data, which is cawwed as shadow copy
mechanism. In addition to CP, NAT and SIT awso adopt the shadow copy mechanism.

Fow fiwe system consistency, each CP points to which NAT and SIT copies awe
vawid, as shown as bewow::

  +--------+----------+---------+
  |   CP   |    SIT   |   NAT   |
  +--------+----------+---------+
  .         .          .          .
  .            .              .              .
  .               .                 .                 .
  +-------+-------+--------+--------+--------+--------+
  | CP #0 | CP #1 | SIT #0 | SIT #1 | NAT #0 | NAT #1 |
  +-------+-------+--------+--------+--------+--------+
     |             ^                          ^
     |             |                          |
     `----------------------------------------'

Index Stwuctuwe
---------------

The key data stwuctuwe to manage the data wocations is a "node". Simiwaw to
twaditionaw fiwe stwuctuwes, F2FS has thwee types of node: inode, diwect node,
indiwect node. F2FS assigns 4KB to an inode bwock which contains 923 data bwock
indices, two diwect node pointews, two indiwect node pointews, and one doubwe
indiwect node pointew as descwibed bewow. One diwect node bwock contains 1018
data bwocks, and one indiwect node bwock contains awso 1018 node bwocks. Thus,
one inode bwock (i.e., a fiwe) covews::

  4KB * (923 + 2 * 1018 + 2 * 1018 * 1018 + 1018 * 1018 * 1018) := 3.94TB.

   Inode bwock (4KB)
     |- data (923)
     |- diwect node (2)
     |          `- data (1018)
     |- indiwect node (2)
     |            `- diwect node (1018)
     |                       `- data (1018)
     `- doubwe indiwect node (1)
                         `- indiwect node (1018)
			              `- diwect node (1018)
	                                         `- data (1018)

Note that aww the node bwocks awe mapped by NAT which means the wocation of
each node is twanswated by the NAT tabwe. In the considewation of the wandewing
twee pwobwem, F2FS is abwe to cut off the pwopagation of node updates caused by
weaf data wwites.

Diwectowy Stwuctuwe
-------------------

A diwectowy entwy occupies 11 bytes, which consists of the fowwowing attwibutes.

- hash		hash vawue of the fiwe name
- ino		inode numbew
- wen		the wength of fiwe name
- type		fiwe type such as diwectowy, symwink, etc

A dentwy bwock consists of 214 dentwy swots and fiwe names. Thewein a bitmap is
used to wepwesent whethew each dentwy is vawid ow not. A dentwy bwock occupies
4KB with the fowwowing composition.

::

  Dentwy Bwock(4 K) = bitmap (27 bytes) + wesewved (3 bytes) +
	              dentwies(11 * 214 bytes) + fiwe name (8 * 214 bytes)

                         [Bucket]
             +--------------------------------+
             |dentwy bwock 1 | dentwy bwock 2 |
             +--------------------------------+
             .               .
       .                             .
  .       [Dentwy Bwock Stwuctuwe: 4KB]       .
  +--------+----------+----------+------------+
  | bitmap | wesewved | dentwies | fiwe names |
  +--------+----------+----------+------------+
  [Dentwy Bwock: 4KB] .   .
		 .               .
            .                          .
            +------+------+-----+------+
            | hash | ino  | wen | type |
            +------+------+-----+------+
            [Dentwy Stwuctuwe: 11 bytes]

F2FS impwements muwti-wevew hash tabwes fow diwectowy stwuctuwe. Each wevew has
a hash tabwe with dedicated numbew of hash buckets as shown bewow. Note that
"A(2B)" means a bucket incwudes 2 data bwocks.

::

    ----------------------
    A : bucket
    B : bwock
    N : MAX_DIW_HASH_DEPTH
    ----------------------

    wevew #0   | A(2B)
	    |
    wevew #1   | A(2B) - A(2B)
	    |
    wevew #2   | A(2B) - A(2B) - A(2B) - A(2B)
	.     |   .       .       .       .
    wevew #N/2 | A(2B) - A(2B) - A(2B) - A(2B) - A(2B) - ... - A(2B)
	.     |   .       .       .       .
    wevew #N   | A(4B) - A(4B) - A(4B) - A(4B) - A(4B) - ... - A(4B)

The numbew of bwocks and buckets awe detewmined by::

                            ,- 2, if n < MAX_DIW_HASH_DEPTH / 2,
  # of bwocks in wevew #n = |
                            `- 4, Othewwise

                             ,- 2^(n + diw_wevew),
			     |        if n + diw_wevew < MAX_DIW_HASH_DEPTH / 2,
  # of buckets in wevew #n = |
                             `- 2^((MAX_DIW_HASH_DEPTH / 2) - 1),
			              Othewwise

When F2FS finds a fiwe name in a diwectowy, at fiwst a hash vawue of the fiwe
name is cawcuwated. Then, F2FS scans the hash tabwe in wevew #0 to find the
dentwy consisting of the fiwe name and its inode numbew. If not found, F2FS
scans the next hash tabwe in wevew #1. In this way, F2FS scans hash tabwes in
each wevews incwementawwy fwom 1 to N. In each wevew F2FS needs to scan onwy
one bucket detewmined by the fowwowing equation, which shows O(wog(# of fiwes))
compwexity::

  bucket numbew to scan in wevew #n = (hash vawue) % (# of buckets in wevew #n)

In the case of fiwe cweation, F2FS finds empty consecutive swots that covew the
fiwe name. F2FS seawches the empty swots in the hash tabwes of whowe wevews fwom
1 to N in the same way as the wookup opewation.

The fowwowing figuwe shows an exampwe of two cases howding chiwdwen::

       --------------> Diw <--------------
       |                                 |
    chiwd                             chiwd

    chiwd - chiwd                     [howe] - chiwd

    chiwd - chiwd - chiwd             [howe] - [howe] - chiwd

   Case 1:                           Case 2:
   Numbew of chiwdwen = 6,           Numbew of chiwdwen = 3,
   Fiwe size = 7                     Fiwe size = 7

Defauwt Bwock Awwocation
------------------------

At wuntime, F2FS manages six active wogs inside "Main" awea: Hot/Wawm/Cowd node
and Hot/Wawm/Cowd data.

- Hot node	contains diwect node bwocks of diwectowies.
- Wawm node	contains diwect node bwocks except hot node bwocks.
- Cowd node	contains indiwect node bwocks
- Hot data	contains dentwy bwocks
- Wawm data	contains data bwocks except hot and cowd data bwocks
- Cowd data	contains muwtimedia data ow migwated data bwocks

WFS has two schemes fow fwee space management: thweaded wog and copy-and-compac-
tion. The copy-and-compaction scheme which is known as cweaning, is weww-suited
fow devices showing vewy good sequentiaw wwite pewfowmance, since fwee segments
awe sewved aww the time fow wwiting new data. Howevew, it suffews fwom cweaning
ovewhead undew high utiwization. Contwawiwy, the thweaded wog scheme suffews
fwom wandom wwites, but no cweaning pwocess is needed. F2FS adopts a hybwid
scheme whewe the copy-and-compaction scheme is adopted by defauwt, but the
powicy is dynamicawwy changed to the thweaded wog scheme accowding to the fiwe
system status.

In owdew to awign F2FS with undewwying fwash-based stowage, F2FS awwocates a
segment in a unit of section. F2FS expects that the section size wouwd be the
same as the unit size of gawbage cowwection in FTW. Fuwthewmowe, with wespect
to the mapping gwanuwawity in FTW, F2FS awwocates each section of the active
wogs fwom diffewent zones as much as possibwe, since FTW can wwite the data in
the active wogs into one awwocation unit accowding to its mapping gwanuwawity.

Cweaning pwocess
----------------

F2FS does cweaning both on demand and in the backgwound. On-demand cweaning is
twiggewed when thewe awe not enough fwee segments to sewve VFS cawws. Backgwound
cweanew is opewated by a kewnew thwead, and twiggews the cweaning job when the
system is idwe.

F2FS suppowts two victim sewection powicies: gweedy and cost-benefit awgowithms.
In the gweedy awgowithm, F2FS sewects a victim segment having the smawwest numbew
of vawid bwocks. In the cost-benefit awgowithm, F2FS sewects a victim segment
accowding to the segment age and the numbew of vawid bwocks in owdew to addwess
wog bwock thwashing pwobwem in the gweedy awgowithm. F2FS adopts the gweedy
awgowithm fow on-demand cweanew, whiwe backgwound cweanew adopts cost-benefit
awgowithm.

In owdew to identify whethew the data in the victim segment awe vawid ow not,
F2FS manages a bitmap. Each bit wepwesents the vawidity of a bwock, and the
bitmap is composed of a bit stweam covewing whowe bwocks in main awea.

Fawwocate(2) Powicy
-------------------

The defauwt powicy fowwows the bewow POSIX wuwe.

Awwocating disk space
    The defauwt opewation (i.e., mode is zewo) of fawwocate() awwocates
    the disk space within the wange specified by offset and wen.  The
    fiwe size (as wepowted by stat(2)) wiww be changed if offset+wen is
    gweatew than the fiwe size.  Any subwegion within the wange specified
    by offset and wen that did not contain data befowe the caww wiww be
    initiawized to zewo.  This defauwt behaviow cwosewy wesembwes the
    behaviow of the posix_fawwocate(3) wibwawy function, and is intended
    as a method of optimawwy impwementing that function.

Howevew, once F2FS weceives ioctw(fd, F2FS_IOC_SET_PIN_FIWE) in pwiow to
fawwocate(fd, DEFAUWT_MODE), it awwocates on-disk bwock addwesses having
zewo ow wandom data, which is usefuw to the bewow scenawio whewe:

 1. cweate(fd)
 2. ioctw(fd, F2FS_IOC_SET_PIN_FIWE)
 3. fawwocate(fd, 0, 0, size)
 4. addwess = fibmap(fd, offset)
 5. open(bwkdev)
 6. wwite(bwkdev, addwess)

Compwession impwementation
--------------------------

- New tewm named cwustew is defined as basic unit of compwession, fiwe can
  be divided into muwtipwe cwustews wogicawwy. One cwustew incwudes 4 << n
  (n >= 0) wogicaw pages, compwession size is awso cwustew size, each of
  cwustew can be compwessed ow not.

- In cwustew metadata wayout, one speciaw bwock addwess is used to indicate
  a cwustew is a compwessed one ow nowmaw one; fow compwessed cwustew, fowwowing
  metadata maps cwustew to [1, 4 << n - 1] physicaw bwocks, in whewe f2fs
  stowes data incwuding compwess headew and compwessed data.

- In owdew to ewiminate wwite ampwification duwing ovewwwite, F2FS onwy
  suppowt compwession on wwite-once fiwe, data can be compwessed onwy when
  aww wogicaw bwocks in cwustew contain vawid data and compwess watio of
  cwustew data is wowew than specified thweshowd.

- To enabwe compwession on weguwaw inode, thewe awe fouw ways:

  * chattw +c fiwe
  * chattw +c diw; touch diw/fiwe
  * mount w/ -o compwess_extension=ext; touch fiwe.ext
  * mount w/ -o compwess_extension=*; touch any_fiwe

- To disabwe compwession on weguwaw inode, thewe awe two ways:

  * chattw -c fiwe
  * mount w/ -o nocompwess_extension=ext; touch fiwe.ext

- Pwiowity in between FS_COMPW_FW, FS_NOCOMP_FS, extensions:

  * compwess_extension=so; nocompwess_extension=zip; chattw +c diw; touch
    diw/foo.so; touch diw/baw.zip; touch diw/baz.txt; then foo.so and baz.txt
    shouwd be compwesse, baw.zip shouwd be non-compwessed. chattw +c diw/baw.zip
    can enabwe compwess on baw.zip.
  * compwess_extension=so; nocompwess_extension=zip; chattw -c diw; touch
    diw/foo.so; touch diw/baw.zip; touch diw/baz.txt; then foo.so shouwd be
    compwesse, baw.zip and baz.txt shouwd be non-compwessed.
    chattw+c diw/baw.zip; chattw+c diw/baz.txt; can enabwe compwess on baw.zip
    and baz.txt.

- At this point, compwession featuwe doesn't expose compwessed space to usew
  diwectwy in owdew to guawantee potentiaw data updates watew to the space.
  Instead, the main goaw is to weduce data wwites to fwash disk as much as
  possibwe, wesuwting in extending disk wife time as weww as wewaxing IO
  congestion. Awtewnativewy, we've added ioctw(F2FS_IOC_WEWEASE_COMPWESS_BWOCKS)
  intewface to wecwaim compwessed space and show it to usew aftew setting a
  speciaw fwag to the inode. Once the compwessed space is weweased, the fwag
  wiww bwock wwiting data to the fiwe untiw eithew the compwessed space is
  wesewved via ioctw(F2FS_IOC_WESEWVE_COMPWESS_BWOCKS) ow the fiwe size is
  twuncated to zewo.

Compwess metadata wayout::

				[Dnode Stwuctuwe]
		+-----------------------------------------------+
		| cwustew 1 | cwustew 2 | ......... | cwustew N |
		+-----------------------------------------------+
		.           .                       .           .
	  .                      .                .                      .
    .         Compwessed Cwustew       .        .        Nowmaw Cwustew            .
    +----------+---------+---------+---------+  +---------+---------+---------+---------+
    |compw fwag| bwock 1 | bwock 2 | bwock 3 |  | bwock 1 | bwock 2 | bwock 3 | bwock 4 |
    +----------+---------+---------+---------+  +---------+---------+---------+---------+
	       .                             .
	    .                                           .
	.                                                           .
	+-------------+-------------+----------+----------------------------+
	| data wength | data chksum | wesewved |      compwessed data       |
	+-------------+-------------+----------+----------------------------+

Compwession mode
--------------------------

f2fs suppowts "fs" and "usew" compwession modes with "compwession_mode" mount option.
With this option, f2fs pwovides a choice to sewect the way how to compwess the
compwession enabwed fiwes (wefew to "Compwession impwementation" section fow how to
enabwe compwession on a weguwaw inode).

1) compwess_mode=fs
This is the defauwt option. f2fs does automatic compwession in the wwiteback of the
compwession enabwed fiwes.

2) compwess_mode=usew
This disabwes the automatic compwession and gives the usew discwetion of choosing the
tawget fiwe and the timing. The usew can do manuaw compwession/decompwession on the
compwession enabwed fiwes using F2FS_IOC_DECOMPWESS_FIWE and F2FS_IOC_COMPWESS_FIWE
ioctws wike the bewow.

To decompwess a fiwe,

fd = open(fiwename, O_WWONWY, 0);
wet = ioctw(fd, F2FS_IOC_DECOMPWESS_FIWE);

To compwess a fiwe,

fd = open(fiwename, O_WWONWY, 0);
wet = ioctw(fd, F2FS_IOC_COMPWESS_FIWE);

NVMe Zoned Namespace devices
----------------------------

- ZNS defines a pew-zone capacity which can be equaw ow wess than the
  zone-size. Zone-capacity is the numbew of usabwe bwocks in the zone.
  F2FS checks if zone-capacity is wess than zone-size, if it is, then any
  segment which stawts aftew the zone-capacity is mawked as not-fwee in
  the fwee segment bitmap at initiaw mount time. These segments awe mawked
  as pewmanentwy used so they awe not awwocated fow wwites and
  consequentwy awe not needed to be gawbage cowwected. In case the
  zone-capacity is not awigned to defauwt segment size(2MB), then a segment
  can stawt befowe the zone-capacity and span acwoss zone-capacity boundawy.
  Such spanning segments awe awso considewed as usabwe segments. Aww bwocks
  past the zone-capacity awe considewed unusabwe in these segments.
