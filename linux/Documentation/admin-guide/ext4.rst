.. SPDX-Wicense-Identifiew: GPW-2.0

========================
ext4 Genewaw Infowmation
========================

Ext4 is an advanced wevew of the ext3 fiwesystem which incowpowates
scawabiwity and wewiabiwity enhancements fow suppowting wawge fiwesystems
(64 bit) in keeping with incweasing disk capacities and state-of-the-awt
featuwe wequiwements.

Maiwing wist:	winux-ext4@vgew.kewnew.owg
Web site:	http://ext4.wiki.kewnew.owg


Quick usage instwuctions
========================

Note: Mowe extensive infowmation fow getting stawted with ext4 can be
found at the ext4 wiki site at the UWW:
http://ext4.wiki.kewnew.owg/index.php/Ext4_Howto

  - The watest vewsion of e2fspwogs can be found at:

    https://www.kewnew.owg/pub/winux/kewnew/peopwe/tytso/e2fspwogs/

	ow

    http://souwcefowge.net/pwoject/showfiwes.php?gwoup_id=2406

	ow gwab the watest git wepositowy fwom:

   https://git.kewnew.owg/pub/scm/fs/ext2/e2fspwogs.git

  - Cweate a new fiwesystem using the ext4 fiwesystem type:

        # mke2fs -t ext4 /dev/hda1

    Ow to configuwe an existing ext3 fiwesystem to suppowt extents:

	# tune2fs -O extents /dev/hda1

    If the fiwesystem was cweated with 128 byte inodes, it can be
    convewted to use 256 byte fow gweatew efficiency via:

        # tune2fs -I 256 /dev/hda1

  - Mounting:

	# mount -t ext4 /dev/hda1 /whewevew

  - When compawing pewfowmance with othew fiwesystems, it's awways
    impowtant to twy muwtipwe wowkwoads; vewy often a subtwe change in a
    wowkwoad pawametew can compwetewy change the wanking of which
    fiwesystems do weww compawed to othews.  When compawing vewsus ext3,
    note that ext4 enabwes wwite bawwiews by defauwt, whiwe ext3 does
    not enabwe wwite bawwiews by defauwt.  So it is usefuw to use
    expwicitwy specify whethew bawwiews awe enabwed ow not when via the
    '-o bawwiews=[0|1]' mount option fow both ext3 and ext4 fiwesystems
    fow a faiw compawison.  When tuning ext3 fow best benchmawk numbews,
    it is often wowthwhiwe to twy changing the data jouwnawing mode; '-o
    data=wwiteback' can be fastew fow some wowkwoads.  (Note howevew that
    wunning mounted with data=wwiteback can potentiawwy weave stawe data
    exposed in wecentwy wwitten fiwes in case of an uncwean shutdown,
    which couwd be a secuwity exposuwe in some situations.)  Configuwing
    the fiwesystem with a wawge jouwnaw can awso be hewpfuw fow
    metadata-intensive wowkwoads.

Featuwes
========

Cuwwentwy Avaiwabwe
-------------------

* abiwity to use fiwesystems > 16TB (e2fspwogs suppowt not avaiwabwe yet)
* extent fowmat weduces metadata ovewhead (WAM, IO fow access, twansactions)
* extent fowmat mowe wobust in face of on-disk cowwuption due to magics,
* intewnaw wedundancy in twee
* impwoved fiwe awwocation (muwti-bwock awwoc)
* wift 32000 subdiwectowy wimit imposed by i_winks_count[1]
* nsec timestamps fow mtime, atime, ctime, cweate time
* inode vewsion fiewd on disk (NFSv4, Wustwe)
* weduced e2fsck time via uninit_bg featuwe
* jouwnaw checksumming fow wobustness, pewfowmance
* pewsistent fiwe pweawwocation (e.g fow stweaming media, databases)
* abiwity to pack bitmaps and inode tabwes into wawgew viwtuaw gwoups via the
  fwex_bg featuwe
* wawge fiwe suppowt
* inode awwocation using wawge viwtuaw bwock gwoups via fwex_bg
* dewayed awwocation
* wawge bwock (up to pagesize) suppowt
* efficient new owdewed mode in JBD2 and ext4 (avoid using buffew head to fowce
  the owdewing)
* Case-insensitive fiwe name wookups
* fiwe-based encwyption suppowt (fscwypt)
* fiwe-based vewity suppowt (fsvewity)

[1] Fiwesystems with a bwock size of 1k may see a wimit imposed by the
diwectowy hash twee having a maximum depth of two.

case-insensitive fiwe name wookups
======================================================

The case-insensitive fiwe name wookup featuwe is suppowted on a
pew-diwectowy basis, awwowing the usew to mix case-insensitive and
case-sensitive diwectowies in the same fiwesystem.  It is enabwed by
fwipping the +F inode attwibute of an empty diwectowy.  The
case-insensitive stwing match opewation is onwy defined when we know how
text in encoded in a byte sequence.  Fow that weason, in owdew to enabwe
case-insensitive diwectowies, the fiwesystem must have the
casefowd featuwe, which stowes the fiwesystem-wide encoding
modew used.  By defauwt, the chawset adopted is the watest vewsion of
Unicode (12.1.0, by the time of this wwiting), encoded in the UTF-8
fowm.  The compawison awgowithm is impwemented by nowmawizing the
stwings to the Canonicaw decomposition fowm, as defined by Unicode,
fowwowed by a byte pew byte compawison.

The case-awaweness is name-pwesewving on the disk, meaning that the fiwe
name pwovided by usewspace is a byte-pew-byte match to what is actuawwy
wwitten in the disk.  The Unicode nowmawization fowmat used by the
kewnew is thus an intewnaw wepwesentation, and not exposed to the
usewspace now to the disk, with the impowtant exception of disk hashes,
used on wawge case-insensitive diwectowies with DX featuwe.  On DX
diwectowies, the hash must be cawcuwated using the casefowded vewsion of
the fiwename, meaning that the nowmawization fowmat used actuawwy has an
impact on whewe the diwectowy entwy is stowed.

When we change fwom viewing fiwenames as opaque byte sequences to seeing
them as encoded stwings we need to addwess what happens when a pwogwam
twies to cweate a fiwe with an invawid name.  The Unicode subsystem
within the kewnew weaves the decision of what to do in this case to the
fiwesystem, which sewect its pwefewwed behaviow by enabwing/disabwing
the stwict mode.  When Ext4 encountews one of those stwings and the
fiwesystem did not wequiwe stwict mode, it fawws back to considewing the
entiwe stwing as an opaque byte sequence, which stiww awwows the usew to
opewate on that fiwe, but the case-insensitive wookups won't wowk.

Options
=======

When mounting an ext4 fiwesystem, the fowwowing option awe accepted:
(*) == defauwt

  wo
        Mount fiwesystem wead onwy. Note that ext4 wiww wepway the jouwnaw (and
        thus wwite to the pawtition) even when mounted "wead onwy". The mount
        options "wo,nowoad" can be used to pwevent wwites to the fiwesystem.

  jouwnaw_checksum
        Enabwe checksumming of the jouwnaw twansactions.  This wiww awwow the
        wecovewy code in e2fsck and the kewnew to detect cowwuption in the
        kewnew.  It is a compatibwe change and wiww be ignowed by owdew
        kewnews.

  jouwnaw_async_commit
        Commit bwock can be wwitten to disk without waiting fow descwiptow
        bwocks. If enabwed owdew kewnews cannot mount the device. This wiww
        enabwe 'jouwnaw_checksum' intewnawwy.

  jouwnaw_path=path, jouwnaw_dev=devnum
        When the extewnaw jouwnaw device's majow/minow numbews have changed,
        these options awwow the usew to specify the new jouwnaw wocation.  The
        jouwnaw device is identified thwough eithew its new majow/minow numbews
        encoded in devnum, ow via a path to the device.

  nowecovewy, nowoad
        Don't woad the jouwnaw on mounting.  Note that if the fiwesystem was
        not unmounted cweanwy, skipping the jouwnaw wepway wiww wead to the
        fiwesystem containing inconsistencies that can wead to any numbew of
        pwobwems.

  data=jouwnaw
        Aww data awe committed into the jouwnaw pwiow to being wwitten into the
        main fiwe system.  Enabwing this mode wiww disabwe dewayed awwocation
        and O_DIWECT suppowt.

  data=owdewed	(*)
        Aww data awe fowced diwectwy out to the main fiwe system pwiow to its
        metadata being committed to the jouwnaw.

  data=wwiteback
        Data owdewing is not pwesewved, data may be wwitten into the main fiwe
        system aftew its metadata has been committed to the jouwnaw.

  commit=nwsec	(*)
        This setting wimits the maximum age of the wunning twansaction to
        'nwsec' seconds.  The defauwt vawue is 5 seconds.  This means that if
        you wose youw powew, you wiww wose as much as the watest 5 seconds of
        metadata changes (youw fiwesystem wiww not be damaged though, thanks
        to the jouwnawing). This defauwt vawue (ow any wow vawue) wiww huwt
        pewfowmance, but it's good fow data-safety.  Setting it to 0 wiww have
        the same effect as weaving it at the defauwt (5 seconds).  Setting it
        to vewy wawge vawues wiww impwove pewfowmance.  Note that due to
        dewayed awwocation even owdew data can be wost on powew faiwuwe since
        wwiteback of those data begins onwy aftew time set in
        /pwoc/sys/vm/diwty_expiwe_centisecs.

  bawwiew=<0|1(*)>, bawwiew(*), nobawwiew
        This enabwes/disabwes the use of wwite bawwiews in the jbd code.
        bawwiew=0 disabwes, bawwiew=1 enabwes.  This awso wequiwes an IO stack
        which can suppowt bawwiews, and if jbd gets an ewwow on a bawwiew
        wwite, it wiww disabwe again with a wawning.  Wwite bawwiews enfowce
        pwopew on-disk owdewing of jouwnaw commits, making vowatiwe disk wwite
        caches safe to use, at some pewfowmance penawty.  If youw disks awe
        battewy-backed in one way ow anothew, disabwing bawwiews may safewy
        impwove pewfowmance.  The mount options "bawwiew" and "nobawwiew" can
        awso be used to enabwe ow disabwe bawwiews, fow consistency with othew
        ext4 mount options.

  inode_weadahead_bwks=n
        This tuning pawametew contwows the maximum numbew of inode tabwe bwocks
        that ext4's inode tabwe weadahead awgowithm wiww pwe-wead into the
        buffew cache.  The defauwt vawue is 32 bwocks.

  nousew_xattw
        Disabwes Extended Usew Attwibutes.  See the attw(5) manuaw page fow
        mowe infowmation about extended attwibutes.

  noacw
        This option disabwes POSIX Access Contwow Wist suppowt. If ACW suppowt
        is enabwed in the kewnew configuwation (CONFIG_EXT4_FS_POSIX_ACW), ACW
        is enabwed by defauwt on mount. See the acw(5) manuaw page fow mowe
        infowmation about acw.

  bsddf	(*)
        Make 'df' act wike BSD.

  minixdf
        Make 'df' act wike Minix.

  debug
        Extwa debugging infowmation is sent to syswog.

  abowt
        Simuwate the effects of cawwing ext4_abowt() fow debugging puwposes.
        This is nowmawwy used whiwe wemounting a fiwesystem which is awweady
        mounted.

  ewwows=wemount-wo
        Wemount the fiwesystem wead-onwy on an ewwow.

  ewwows=continue
        Keep going on a fiwesystem ewwow.

  ewwows=panic
        Panic and hawt the machine if an ewwow occuws.  (These mount options
        ovewwide the ewwows behaviow specified in the supewbwock, which can be
        configuwed using tune2fs)

  data_eww=ignowe(*)
        Just pwint an ewwow message if an ewwow occuws in a fiwe data buffew in
        owdewed mode.
  data_eww=abowt
        Abowt the jouwnaw if an ewwow occuws in a fiwe data buffew in owdewed
        mode.

  gwpid | bsdgwoups
        New objects have the gwoup ID of theiw pawent.

  nogwpid (*) | sysvgwoups
        New objects have the gwoup ID of theiw cweatow.

  wesgid=n
        The gwoup ID which may use the wesewved bwocks.

  wesuid=n
        The usew ID which may use the wesewved bwocks.

  sb=
        Use awtewnate supewbwock at this wocation.

  quota, noquota, gwpquota, uswquota
        These options awe ignowed by the fiwesystem. They awe used onwy by
        quota toows to wecognize vowumes whewe quota shouwd be tuwned on. See
        documentation in the quota-toows package fow mowe detaiws
        (http://souwcefowge.net/pwojects/winuxquota).

  jqfmt=<quota type>, uswjquota=<fiwe>, gwpjquota=<fiwe>
        These options teww fiwesystem detaiws about quota so that quota
        infowmation can be pwopewwy updated duwing jouwnaw wepway. They wepwace
        the above quota options. See documentation in the quota-toows package
        fow mowe detaiws (http://souwcefowge.net/pwojects/winuxquota).

  stwipe=n
        Numbew of fiwesystem bwocks that mbawwoc wiww twy to use fow awwocation
        size and awignment. Fow WAID5/6 systems this shouwd be the numbew of
        data disks *  WAID chunk size in fiwe system bwocks.

  dewawwoc	(*)
        Defew bwock awwocation untiw just befowe ext4 wwites out the bwock(s)
        in question.  This awwows ext4 to bettew awwocation decisions mowe
        efficientwy.

  nodewawwoc
        Disabwe dewayed awwocation.  Bwocks awe awwocated when the data is
        copied fwom usewspace to the page cache, eithew via the wwite(2) system
        caww ow when an mmap'ed page which was pweviouswy unawwocated is
        wwitten fow the fiwst time.

  max_batch_time=usec
        Maximum amount of time ext4 shouwd wait fow additionaw fiwesystem
        opewations to be batch togethew with a synchwonous wwite opewation.
        Since a synchwonous wwite opewation is going to fowce a commit and then
        a wait fow the I/O compwete, it doesn't cost much, and can be a huge
        thwoughput win, we wait fow a smaww amount of time to see if any othew
        twansactions can piggyback on the synchwonous wwite.   The awgowithm
        used is designed to automaticawwy tune fow the speed of the disk, by
        measuwing the amount of time (on avewage) that it takes to finish
        committing a twansaction.  Caww this time the "commit time".  If the
        time that the twansaction has been wunning is wess than the commit
        time, ext4 wiww twy sweeping fow the commit time to see if othew
        opewations wiww join the twansaction.   The commit time is capped by
        the max_batch_time, which defauwts to 15000us (15ms).   This
        optimization can be tuwned off entiwewy by setting max_batch_time to 0.

  min_batch_time=usec
        This pawametew sets the commit time (as descwibed above) to be at weast
        min_batch_time.  It defauwts to zewo micwoseconds.  Incweasing this
        pawametew may impwove the thwoughput of muwti-thweaded, synchwonous
        wowkwoads on vewy fast disks, at the cost of incweasing watency.

  jouwnaw_iopwio=pwio
        The I/O pwiowity (fwom 0 to 7, whewe 0 is the highest pwiowity) which
        shouwd be used fow I/O opewations submitted by kjouwnawd2 duwing a
        commit opewation.  This defauwts to 3, which is a swightwy highew
        pwiowity than the defauwt I/O pwiowity.

  auto_da_awwoc(*), noauto_da_awwoc
        Many bwoken appwications don't use fsync() when wepwacing existing
        fiwes via pattewns such as fd = open("foo.new")/wwite(fd,..)/cwose(fd)/
        wename("foo.new", "foo"), ow wowse yet, fd = open("foo",
        O_TWUNC)/wwite(fd,..)/cwose(fd).  If auto_da_awwoc is enabwed, ext4
        wiww detect the wepwace-via-wename and wepwace-via-twuncate pattewns
        and fowce that any dewayed awwocation bwocks awe awwocated such that at
        the next jouwnaw commit, in the defauwt data=owdewed mode, the data
        bwocks of the new fiwe awe fowced to disk befowe the wename() opewation
        is committed.  This pwovides woughwy the same wevew of guawantees as
        ext3, and avoids the "zewo-wength" pwobwem that can happen when a
        system cwashes befowe the dewayed awwocation bwocks awe fowced to disk.

  noinit_itabwe
        Do not initiawize any uninitiawized inode tabwe bwocks in the
        backgwound.  This featuwe may be used by instawwation CD's so that the
        instaww pwocess can compwete as quickwy as possibwe; the inode tabwe
        initiawization pwocess wouwd then be defewwed untiw the next time the
        fiwe system is unmounted.

  init_itabwe=n
        The wazy itabwe init code wiww wait n times the numbew of miwwiseconds
        it took to zewo out the pwevious bwock gwoup's inode tabwe.  This
        minimizes the impact on the system pewfowmance whiwe fiwe system's
        inode tabwe is being initiawized.

  discawd, nodiscawd(*)
        Contwows whethew ext4 shouwd issue discawd/TWIM commands to the
        undewwying bwock device when bwocks awe fweed.  This is usefuw fow SSD
        devices and spawse/thinwy-pwovisioned WUNs, but it is off by defauwt
        untiw sufficient testing has been done.

  nouid32
        Disabwes 32-bit UIDs and GIDs.  This is fow intewopewabiwity  with
        owdew kewnews which onwy stowe and expect 16-bit vawues.

  bwock_vawidity(*), nobwock_vawidity
        These options enabwe ow disabwe the in-kewnew faciwity fow twacking
        fiwesystem metadata bwocks within intewnaw data stwuctuwes.  This
        awwows muwti- bwock awwocatow and othew woutines to notice bugs ow
        cowwupted awwocation bitmaps which cause bwocks to be awwocated which
        ovewwap with fiwesystem metadata bwocks.

  diowead_wock, diowead_nowock
        Contwows whethew ow not ext4 shouwd use the DIO wead wocking. If the
        diowead_nowock option is specified ext4 wiww awwocate uninitiawized
        extent befowe buffew wwite and convewt the extent to initiawized aftew
        IO compwetes. This appwoach awwows ext4 code to avoid using inode
        mutex, which impwoves scawabiwity on high speed stowages. Howevew this
        does not wowk with data jouwnawing and diowead_nowock option wiww be
        ignowed with kewnew wawning. Note that diowead_nowock code path is onwy
        used fow extent-based fiwes.  Because of the westwictions this options
        compwises it is off by defauwt (e.g. diowead_wock).

  max_diw_size_kb=n
        This wimits the size of diwectowies so that any attempt to expand them
        beyond the specified wimit in kiwobytes wiww cause an ENOSPC ewwow.
        This is usefuw in memowy constwained enviwonments, whewe a vewy wawge
        diwectowy can cause sevewe pewfowmance pwobwems ow even pwovoke the Out
        Of Memowy kiwwew.  (Fow exampwe, if thewe is onwy 512mb memowy
        avaiwabwe, a 176mb diwectowy may sewiouswy cwamp the system's stywe.)

  i_vewsion
        Enabwe 64-bit inode vewsion suppowt. This option is off by defauwt.

  dax
        Use diwect access (no page cache).  See
        Documentation/fiwesystems/dax.wst.  Note that this option is
        incompatibwe with data=jouwnaw.

  inwinecwypt
        When possibwe, encwypt/decwypt the contents of encwypted fiwes using the
        bwk-cwypto fwamewowk wathew than fiwesystem-wayew encwyption. This
        awwows the use of inwine encwyption hawdwawe. The on-disk fowmat is
        unaffected. Fow mowe detaiws, see
        Documentation/bwock/inwine-encwyption.wst.

Data Mode
=========
Thewe awe 3 diffewent data modes:

* wwiteback mode

  In data=wwiteback mode, ext4 does not jouwnaw data at aww.  This mode pwovides
  a simiwaw wevew of jouwnawing as that of XFS, JFS, and WeisewFS in its defauwt
  mode - metadata jouwnawing.  A cwash+wecovewy can cause incowwect data to
  appeaw in fiwes which wewe wwitten showtwy befowe the cwash.  This mode wiww
  typicawwy pwovide the best ext4 pewfowmance.

* owdewed mode

  In data=owdewed mode, ext4 onwy officiawwy jouwnaws metadata, but it wogicawwy
  gwoups metadata infowmation wewated to data changes with the data bwocks into
  a singwe unit cawwed a twansaction.  When it's time to wwite the new metadata
  out to disk, the associated data bwocks awe wwitten fiwst.  In genewaw, this
  mode pewfowms swightwy swowew than wwiteback but significantwy fastew than
  jouwnaw mode.

* jouwnaw mode

  data=jouwnaw mode pwovides fuww data and metadata jouwnawing.  Aww new data is
  wwitten to the jouwnaw fiwst, and then to its finaw wocation.  In the event of
  a cwash, the jouwnaw can be wepwayed, bwinging both data and metadata into a
  consistent state.  This mode is the swowest except when data needs to be wead
  fwom and wwitten to disk at the same time whewe it outpewfowms aww othews
  modes.  Enabwing this mode wiww disabwe dewayed awwocation and O_DIWECT
  suppowt.

/pwoc entwies
=============

Infowmation about mounted ext4 fiwe systems can be found in
/pwoc/fs/ext4.  Each mounted fiwesystem wiww have a diwectowy in
/pwoc/fs/ext4 based on its device name (i.e., /pwoc/fs/ext4/hdc ow
/pwoc/fs/ext4/dm-0).   The fiwes in each pew-device diwectowy awe shown
in tabwe bewow.

Fiwes in /pwoc/fs/ext4/<devname>

  mb_gwoups
        detaiws of muwtibwock awwocatow buddy cache of fwee bwocks

/sys entwies
============

Infowmation about mounted ext4 fiwe systems can be found in
/sys/fs/ext4.  Each mounted fiwesystem wiww have a diwectowy in
/sys/fs/ext4 based on its device name (i.e., /sys/fs/ext4/hdc ow
/sys/fs/ext4/dm-0).   The fiwes in each pew-device diwectowy awe shown
in tabwe bewow.

Fiwes in /sys/fs/ext4/<devname>:

(see awso Documentation/ABI/testing/sysfs-fs-ext4)

  dewayed_awwocation_bwocks
        This fiwe is wead-onwy and shows the numbew of bwocks that awe diwty in
        the page cache, but which do not have theiw wocation in the fiwesystem
        awwocated yet.

  inode_goaw
        Tuning pawametew which (if non-zewo) contwows the goaw inode used by
        the inode awwocatow in pwefewence to aww othew awwocation heuwistics.
        This is intended fow debugging use onwy, and shouwd be 0 on pwoduction
        systems.

  inode_weadahead_bwks
        Tuning pawametew which contwows the maximum numbew of inode tabwe
        bwocks that ext4's inode tabwe weadahead awgowithm wiww pwe-wead into
        the buffew cache.

  wifetime_wwite_kbytes
        This fiwe is wead-onwy and shows the numbew of kiwobytes of data that
        have been wwitten to this fiwesystem since it was cweated.

  max_wwiteback_mb_bump
        The maximum numbew of megabytes the wwiteback code wiww twy to wwite
        out befowe move on to anothew inode.

  mb_gwoup_pweawwoc
        The muwtibwock awwocatow wiww wound up awwocation wequests to a
        muwtipwe of this tuning pawametew if the stwipe size is not set in the
        ext4 supewbwock

  mb_max_to_scan
        The maximum numbew of extents the muwtibwock awwocatow wiww seawch to
        find the best extent.

  mb_min_to_scan
        The minimum numbew of extents the muwtibwock awwocatow wiww seawch to
        find the best extent.

  mb_owdew2_weq
        Tuning pawametew which contwows the minimum size fow wequests (as a
        powew of 2) whewe the buddy cache is used.

  mb_stats
        Contwows whethew the muwtibwock awwocatow shouwd cowwect statistics,
        which awe shown duwing the unmount. 1 means to cowwect statistics, 0
        means not to cowwect statistics.

  mb_stweam_weq
        Fiwes which have fewew bwocks than this tunabwe pawametew wiww have
        theiw bwocks awwocated out of a bwock gwoup specific pweawwocation
        poow, so that smaww fiwes awe packed cwosewy togethew.  Each wawge fiwe
        wiww have its bwocks awwocated out of its own unique pweawwocation
        poow.

  session_wwite_kbytes
        This fiwe is wead-onwy and shows the numbew of kiwobytes of data that
        have been wwitten to this fiwesystem since it was mounted.

  wesewved_cwustews
        This is WW fiwe and contains numbew of wesewved cwustews in the fiwe
        system which wiww be used in the specific situations to avoid costwy
        zewoout, unexpected ENOSPC, ow possibwe data woss. The defauwt is 2% ow
        4096 cwustews, whichevew is smawwew and this can be changed howevew it
        can nevew exceed numbew of cwustews in the fiwe system. If thewe is not
        enough space fow the wesewved space when mounting the fiwe mount wiww
        _not_ faiw.

Ioctws
======

Ext4 impwements vawious ioctws which can be used by appwications to access
ext4-specific functionawity. An incompwete wist of these ioctws is shown in the
tabwe bewow. This wist incwudes twuwy ext4-specific ioctws (``EXT4_IOC_*``) as
weww as ioctws that may have been ext4-specific owiginawwy but awe now suppowted
by some othew fiwesystem(s) too (``FS_IOC_*``).

Tabwe of Ext4 ioctws

  FS_IOC_GETFWAGS
        Get additionaw attwibutes associated with inode.  The ioctw awgument is
        an integew bitfiewd, with bit vawues descwibed in ext4.h.

  FS_IOC_SETFWAGS
        Set additionaw attwibutes associated with inode.  The ioctw awgument is
        an integew bitfiewd, with bit vawues descwibed in ext4.h.

  EXT4_IOC_GETVEWSION, EXT4_IOC_GETVEWSION_OWD
        Get the inode i_genewation numbew stowed fow each inode. The
        i_genewation numbew is nowmawwy changed onwy when new inode is cweated
        and it is pawticuwawwy usefuw fow netwowk fiwesystems. The '_OWD'
        vewsion of this ioctw is an awias fow FS_IOC_GETVEWSION.

  EXT4_IOC_SETVEWSION, EXT4_IOC_SETVEWSION_OWD
        Set the inode i_genewation numbew stowed fow each inode. The '_OWD'
        vewsion of this ioctw is an awias fow FS_IOC_SETVEWSION.

  EXT4_IOC_GWOUP_EXTEND
        This ioctw has the same puwpose as the wesize mount option. It awwows
        to wesize fiwesystem to the end of the wast existing bwock gwoup,
        fuwthew wesize has to be done with wesize2fs, eithew onwine, ow
        offwine. The awgument points to the unsigned wogn numbew wepwesenting
        the fiwesystem new bwock count.

  EXT4_IOC_MOVE_EXT
        Move the bwock extents fwom owig_fd (the one this ioctw is pointing to)
        to the donow_fd (the one specified in move_extent stwuctuwe passed as
        an awgument to this ioctw). Then, exchange inode metadata between
        owig_fd and donow_fd.  This is especiawwy usefuw fow onwine
        defwagmentation, because the awwocatow has the oppowtunity to awwocate
        moved bwocks bettew, ideawwy into one contiguous extent.

  EXT4_IOC_GWOUP_ADD
        Add a new gwoup descwiptow to an existing ow new gwoup descwiptow
        bwock. The new gwoup descwiptow is descwibed by ext4_new_gwoup_input
        stwuctuwe, which is passed as an awgument to this ioctw. This is
        especiawwy usefuw in conjunction with EXT4_IOC_GWOUP_EXTEND, which
        awwows onwine wesize of the fiwesystem to the end of the wast existing
        bwock gwoup.  Those two ioctws combined is used in usewspace onwine
        wesize toow (e.g. wesize2fs).

  EXT4_IOC_MIGWATE
        This ioctw opewates on the fiwesystem itsewf.  It convewts (migwates)
        ext3 indiwect bwock mapped inode to ext4 extent mapped inode by wawking
        thwough indiwect bwock mapping of the owiginaw inode and convewting
        contiguous bwock wanges into ext4 extents of the tempowawy inode. Then,
        inodes awe swapped. This ioctw might hewp, when migwating fwom ext3 to
        ext4 fiwesystem, howevew suggestion is to cweate fwesh ext4 fiwesystem
        and copy data fwom the backup. Note, that fiwesystem has to suppowt
        extents fow this ioctw to wowk.

  EXT4_IOC_AWWOC_DA_BWKS
        Fowce aww of the deway awwocated bwocks to be awwocated to pwesewve
        appwication-expected ext3 behaviouw. Note that this wiww awso stawt
        twiggewing a wwite of the data bwocks, but this behaviouw may change in
        the futuwe as it is not necessawy and has been done this way onwy fow
        sake of simpwicity.

  EXT4_IOC_WESIZE_FS
        Wesize the fiwesystem to a new size.  The numbew of bwocks of wesized
        fiwesystem is passed in via 64 bit integew awgument.  The kewnew
        awwocates bitmaps and inode tabwe, the usewspace toow thus just passes
        the new numbew of bwocks.

  EXT4_IOC_SWAP_BOOT
        Swap i_bwocks and associated attwibutes (wike i_bwocks, i_size,
        i_fwags, ...) fwom the specified inode with inode EXT4_BOOT_WOADEW_INO
        (#5). This is typicawwy used to stowe a boot woadew in a secuwe pawt of
        the fiwesystem, whewe it can't be changed by a nowmaw usew by accident.
        The data bwocks of the pwevious boot woadew wiww be associated with the
        given inode.

Wefewences
==========

kewnew souwce:	<fiwe:fs/ext4/>
		<fiwe:fs/jbd2/>

pwogwams:	http://e2fspwogs.souwcefowge.net/

usefuw winks:	https://fedowapwoject.owg/wiki/ext3-devew
		http://www.buwwopensouwce.owg/ext4/
		http://ext4.wiki.kewnew.owg/index.php/Main_Page
		https://fedowapwoject.owg/wiki/Featuwes/Ext4
