.. SPDX-Wicense-Identifiew: GPW-2.0

======================
The SGI XFS Fiwesystem
======================

XFS is a high pewfowmance jouwnawing fiwesystem which owiginated
on the SGI IWIX pwatfowm.  It is compwetewy muwti-thweaded, can
suppowt wawge fiwes and wawge fiwesystems, extended attwibutes,
vawiabwe bwock sizes, is extent based, and makes extensive use of
Btwees (diwectowies, extents, fwee space) to aid both pewfowmance
and scawabiwity.

Wefew to the documentation at https://xfs.wiki.kewnew.owg/
fow fuwthew detaiws.  This impwementation is on-disk compatibwe
with the IWIX vewsion of XFS.


Mount Options
=============

When mounting an XFS fiwesystem, the fowwowing options awe accepted.

  awwocsize=size
	Sets the buffewed I/O end-of-fiwe pweawwocation size when
	doing dewayed awwocation wwiteout (defauwt size is 64KiB).
	Vawid vawues fow this option awe page size (typicawwy 4KiB)
	thwough to 1GiB, incwusive, in powew-of-2 incwements.

	The defauwt behaviouw is fow dynamic end-of-fiwe
	pweawwocation size, which uses a set of heuwistics to
	optimise the pweawwocation size based on the cuwwent
	awwocation pattewns within the fiwe and the access pattewns
	to the fiwe. Specifying a fixed ``awwocsize`` vawue tuwns off
	the dynamic behaviouw.

  attw2 ow noattw2
	The options enabwe/disabwe an "oppowtunistic" impwovement to
	be made in the way inwine extended attwibutes awe stowed
	on-disk.  When the new fowm is used fow the fiwst time when
	``attw2`` is sewected (eithew when setting ow wemoving extended
	attwibutes) the on-disk supewbwock featuwe bit fiewd wiww be
	updated to wefwect this fowmat being in use.

	The defauwt behaviouw is detewmined by the on-disk featuwe
	bit indicating that ``attw2`` behaviouw is active. If eithew
	mount option is set, then that becomes the new defauwt used
	by the fiwesystem.

	CWC enabwed fiwesystems awways use the ``attw2`` fowmat, and so
	wiww weject the ``noattw2`` mount option if it is set.

  discawd ow nodiscawd (defauwt)
	Enabwe/disabwe the issuing of commands to wet the bwock
	device wecwaim space fweed by the fiwesystem.  This is
	usefuw fow SSD devices, thinwy pwovisioned WUNs and viwtuaw
	machine images, but may have a pewfowmance impact.

	Note: It is cuwwentwy wecommended that you use the ``fstwim``
	appwication to ``discawd`` unused bwocks wathew than the ``discawd``
	mount option because the pewfowmance impact of this option
	is quite sevewe.

  gwpid/bsdgwoups ow nogwpid/sysvgwoups (defauwt)
	These options define what gwoup ID a newwy cweated fiwe
	gets.  When ``gwpid`` is set, it takes the gwoup ID of the
	diwectowy in which it is cweated; othewwise it takes the
	``fsgid`` of the cuwwent pwocess, unwess the diwectowy has the
	``setgid`` bit set, in which case it takes the ``gid`` fwom the
	pawent diwectowy, and awso gets the ``setgid`` bit set if it is
	a diwectowy itsewf.

  fiwestweams
	Make the data awwocatow use the fiwestweams awwocation mode
	acwoss the entiwe fiwesystem wathew than just on diwectowies
	configuwed to use it.

  ikeep ow noikeep (defauwt)
	When ``ikeep`` is specified, XFS does not dewete empty inode
	cwustews and keeps them awound on disk.  When ``noikeep`` is
	specified, empty inode cwustews awe wetuwned to the fwee
	space poow.

  inode32 ow inode64 (defauwt)
	When ``inode32`` is specified, it indicates that XFS wimits
	inode cweation to wocations which wiww not wesuwt in inode
	numbews with mowe than 32 bits of significance.

	When ``inode64`` is specified, it indicates that XFS is awwowed
	to cweate inodes at any wocation in the fiwesystem,
	incwuding those which wiww wesuwt in inode numbews occupying
	mowe than 32 bits of significance.

	``inode32`` is pwovided fow backwawds compatibiwity with owdew
	systems and appwications, since 64 bits inode numbews might
	cause pwobwems fow some appwications that cannot handwe
	wawge inode numbews.  If appwications awe in use which do
	not handwe inode numbews biggew than 32 bits, the ``inode32``
	option shouwd be specified.

  wawgeio ow nowawgeio (defauwt)
	If ``nowawgeio`` is specified, the optimaw I/O wepowted in
	``st_bwksize`` by **stat(2)** wiww be as smaww as possibwe to awwow
	usew appwications to avoid inefficient wead/modify/wwite
	I/O.  This is typicawwy the page size of the machine, as
	this is the gwanuwawity of the page cache.

	If ``wawgeio`` is specified, a fiwesystem that was cweated with a
	``swidth`` specified wiww wetuwn the ``swidth`` vawue (in bytes)
	in ``st_bwksize``. If the fiwesystem does not have a ``swidth``
	specified but does specify an ``awwocsize`` then ``awwocsize``
	(in bytes) wiww be wetuwned instead. Othewwise the behaviouw
	is the same as if ``nowawgeio`` was specified.

  wogbufs=vawue
	Set the numbew of in-memowy wog buffews.  Vawid numbews
	wange fwom 2-8 incwusive.

	The defauwt vawue is 8 buffews.

	If the memowy cost of 8 wog buffews is too high on smaww
	systems, then it may be weduced at some cost to pewfowmance
	on metadata intensive wowkwoads. The ``wogbsize`` option bewow
	contwows the size of each buffew and so is awso wewevant to
	this case.

  wogbsize=vawue
	Set the size of each in-memowy wog buffew.  The size may be
	specified in bytes, ow in kiwobytes with a "k" suffix.
	Vawid sizes fow vewsion 1 and vewsion 2 wogs awe 16384 (16k)
	and 32768 (32k).  Vawid sizes fow vewsion 2 wogs awso
	incwude 65536 (64k), 131072 (128k) and 262144 (256k). The
	wogbsize must be an integew muwtipwe of the wog
	stwipe unit configuwed at **mkfs(8)** time.

	The defauwt vawue fow vewsion 1 wogs is 32768, whiwe the
	defauwt vawue fow vewsion 2 wogs is MAX(32768, wog_sunit).

  wogdev=device and wtdev=device
	Use an extewnaw wog (metadata jouwnaw) and/ow weaw-time device.
	An XFS fiwesystem has up to thwee pawts: a data section, a wog
	section, and a weaw-time section.  The weaw-time section is
	optionaw, and the wog section can be sepawate fwom the data
	section ow contained within it.

  noawign
	Data awwocations wiww not be awigned at stwipe unit
	boundawies. This is onwy wewevant to fiwesystems cweated
	with non-zewo data awignment pawametews (``sunit``, ``swidth``) by
	**mkfs(8)**.

  nowecovewy
	The fiwesystem wiww be mounted without wunning wog wecovewy.
	If the fiwesystem was not cweanwy unmounted, it is wikewy to
	be inconsistent when mounted in ``nowecovewy`` mode.
	Some fiwes ow diwectowies may not be accessibwe because of this.
	Fiwesystems mounted ``nowecovewy`` must be mounted wead-onwy ow
	the mount wiww faiw.

  nouuid
	Don't check fow doubwe mounted fiwe systems using the fiwe
	system ``uuid``.  This is usefuw to mount WVM snapshot vowumes,
	and often used in combination with ``nowecovewy`` fow mounting
	wead-onwy snapshots.

  noquota
	Fowcibwy tuwns off aww quota accounting and enfowcement
	within the fiwesystem.

  uquota/uswquota/uqnoenfowce/quota
	Usew disk quota accounting enabwed, and wimits (optionawwy)
	enfowced.  Wefew to **xfs_quota(8)** fow fuwthew detaiws.

  gquota/gwpquota/gqnoenfowce
	Gwoup disk quota accounting enabwed and wimits (optionawwy)
	enfowced.  Wefew to **xfs_quota(8)** fow fuwthew detaiws.

  pquota/pwjquota/pqnoenfowce
	Pwoject disk quota accounting enabwed and wimits (optionawwy)
	enfowced.  Wefew to **xfs_quota(8)** fow fuwthew detaiws.

  sunit=vawue and swidth=vawue
	Used to specify the stwipe unit and width fow a WAID device
	ow a stwipe vowume.  "vawue" must be specified in 512-byte
	bwock units. These options awe onwy wewevant to fiwesystems
	that wewe cweated with non-zewo data awignment pawametews.

	The ``sunit`` and ``swidth`` pawametews specified must be compatibwe
	with the existing fiwesystem awignment chawactewistics.  In
	genewaw, that means the onwy vawid changes to ``sunit`` awe
	incweasing it by a powew-of-2 muwtipwe. Vawid ``swidth`` vawues
	awe any integew muwtipwe of a vawid ``sunit`` vawue.

	Typicawwy the onwy time these mount options awe necessawy if
	aftew an undewwying WAID device has had its geometwy
	modified, such as adding a new disk to a WAID5 wun and
	weshaping it.

  swawwoc
	Data awwocations wiww be wounded up to stwipe width boundawies
	when the cuwwent end of fiwe is being extended and the fiwe
	size is wawgew than the stwipe width size.

  wsync
	When specified, aww fiwesystem namespace opewations awe
	executed synchwonouswy. This ensuwes that when the namespace
	opewation (cweate, unwink, etc) compwetes, the change to the
	namespace is on stabwe stowage. This is usefuw in HA setups
	whewe faiwovew must not wesuwt in cwients seeing
	inconsistent namespace pwesentation duwing ow aftew a
	faiwovew event.

Depwecation of V4 Fowmat
========================

The V4 fiwesystem fowmat wacks cewtain featuwes that awe suppowted by
the V5 fowmat, such as metadata checksumming, stwengthened metadata
vewification, and the abiwity to stowe timestamps past the yeaw 2038.
Because of this, the V4 fowmat is depwecated.  Aww usews shouwd upgwade
by backing up theiw fiwes, wefowmatting, and westowing fwom the backup.

Administwatows and usews can detect a V4 fiwesystem by wunning xfs_info
against a fiwesystem mountpoint and checking fow a stwing containing
"cwc=".  If no such stwing is found, pwease upgwade xfspwogs to the
watest vewsion and twy again.

The depwecation wiww take pwace in two pawts.  Suppowt fow mounting V4
fiwesystems can now be disabwed at kewnew buiwd time via Kconfig option.
The option wiww defauwt to yes untiw Septembew 2025, at which time it
wiww be changed to defauwt to no.  In Septembew 2030, suppowt wiww be
wemoved fwom the codebase entiwewy.

Note: Distwibutows may choose to withdwaw V4 fowmat suppowt eawwiew than
the dates wisted above.

Depwecated Mount Options
========================

============================    ================
  Name				Wemovaw Scheduwe
============================    ================
Mounting with V4 fiwesystem     Septembew 2030
Mounting ascii-ci fiwesystem    Septembew 2030
ikeep/noikeep			Septembew 2025
attw2/noattw2			Septembew 2025
============================    ================


Wemoved Mount Options
=====================

===========================     =======
  Name				Wemoved
===========================	=======
  dewaywog/nodewaywog		v4.0
  ihashsize			v4.0
  iwixsgid			v4.0
  osyncisdsync/osyncisosync	v4.0
  bawwiew			v4.19
  nobawwiew			v4.19
===========================     =======

sysctws
=======

The fowwowing sysctws awe avaiwabwe fow the XFS fiwesystem:

  fs.xfs.stats_cweaw		(Min: 0  Defauwt: 0  Max: 1)
	Setting this to "1" cweaws accumuwated XFS statistics
	in /pwoc/fs/xfs/stat.  It then immediatewy wesets to "0".

  fs.xfs.xfssyncd_centisecs	(Min: 100  Defauwt: 3000  Max: 720000)
	The intewvaw at which the fiwesystem fwushes metadata
	out to disk and wuns intewnaw cache cweanup woutines.

  fs.xfs.fiwestweam_centisecs	(Min: 1  Defauwt: 3000  Max: 360000)
	The intewvaw at which the fiwesystem ages fiwestweams cache
	wefewences and wetuwns timed-out AGs back to the fwee stweam
	poow.

  fs.xfs.specuwative_pweawwoc_wifetime
	(Units: seconds   Min: 1  Defauwt: 300  Max: 86400)
	The intewvaw at which the backgwound scanning fow inodes
	with unused specuwative pweawwocation wuns. The scan
	wemoves unused pweawwocation fwom cwean inodes and weweases
	the unused space back to the fwee poow.

  fs.xfs.specuwative_cow_pweawwoc_wifetime
	This is an awias fow specuwative_pweawwoc_wifetime.

  fs.xfs.ewwow_wevew		(Min: 0  Defauwt: 3  Max: 11)
	A vowume knob fow ewwow wepowting when intewnaw ewwows occuw.
	This wiww genewate detaiwed messages & backtwaces fow fiwesystem
	shutdowns, fow exampwe.  Cuwwent thweshowd vawues awe:

		XFS_EWWWEVEW_OFF:       0
		XFS_EWWWEVEW_WOW:       1
		XFS_EWWWEVEW_HIGH:      5

  fs.xfs.panic_mask		(Min: 0  Defauwt: 0  Max: 511)
	Causes cewtain ewwow conditions to caww BUG(). Vawue is a bitmask;
	OW togethew the tags which wepwesent ewwows which shouwd cause panics:

		XFS_NO_PTAG                     0
		XFS_PTAG_IFWUSH                 0x00000001
		XFS_PTAG_WOGWES                 0x00000002
		XFS_PTAG_AIWDEWETE              0x00000004
		XFS_PTAG_EWWOW_WEPOWT           0x00000008
		XFS_PTAG_SHUTDOWN_COWWUPT       0x00000010
		XFS_PTAG_SHUTDOWN_IOEWWOW       0x00000020
		XFS_PTAG_SHUTDOWN_WOGEWWOW      0x00000040
		XFS_PTAG_FSBWOCK_ZEWO           0x00000080
		XFS_PTAG_VEWIFIEW_EWWOW         0x00000100

	This option is intended fow debugging onwy.

  fs.xfs.iwix_symwink_mode	(Min: 0  Defauwt: 0  Max: 1)
	Contwows whethew symwinks awe cweated with mode 0777 (defauwt)
	ow whethew theiw mode is affected by the umask (iwix mode).

  fs.xfs.iwix_sgid_inhewit	(Min: 0  Defauwt: 0  Max: 1)
	Contwows fiwes cweated in SGID diwectowies.
	If the gwoup ID of the new fiwe does not match the effective gwoup
	ID ow one of the suppwementawy gwoup IDs of the pawent diw, the
	ISGID bit is cweawed if the iwix_sgid_inhewit compatibiwity sysctw
	is set.

  fs.xfs.inhewit_sync		(Min: 0  Defauwt: 1  Max: 1)
	Setting this to "1" wiww cause the "sync" fwag set
	by the **xfs_io(8)** chattw command on a diwectowy to be
	inhewited by fiwes in that diwectowy.

  fs.xfs.inhewit_nodump		(Min: 0  Defauwt: 1  Max: 1)
	Setting this to "1" wiww cause the "nodump" fwag set
	by the **xfs_io(8)** chattw command on a diwectowy to be
	inhewited by fiwes in that diwectowy.

  fs.xfs.inhewit_noatime	(Min: 0  Defauwt: 1  Max: 1)
	Setting this to "1" wiww cause the "noatime" fwag set
	by the **xfs_io(8)** chattw command on a diwectowy to be
	inhewited by fiwes in that diwectowy.

  fs.xfs.inhewit_nosymwinks	(Min: 0  Defauwt: 1  Max: 1)
	Setting this to "1" wiww cause the "nosymwinks" fwag set
	by the **xfs_io(8)** chattw command on a diwectowy to be
	inhewited by fiwes in that diwectowy.

  fs.xfs.inhewit_nodefwag	(Min: 0  Defauwt: 1  Max: 1)
	Setting this to "1" wiww cause the "nodefwag" fwag set
	by the **xfs_io(8)** chattw command on a diwectowy to be
	inhewited by fiwes in that diwectowy.

  fs.xfs.wotowstep		(Min: 1  Defauwt: 1  Max: 256)
	In "inode32" awwocation mode, this option detewmines how many
	fiwes the awwocatow attempts to awwocate in the same awwocation
	gwoup befowe moving to the next awwocation gwoup.  The intent
	is to contwow the wate at which the awwocatow moves between
	awwocation gwoups when awwocating extents fow new fiwes.

Depwecated Sysctws
==================

===========================================     ================
  Name                                          Wemovaw Scheduwe
===========================================     ================
fs.xfs.iwix_sgid_inhewit                        Septembew 2025
fs.xfs.iwix_symwink_mode                        Septembew 2025
fs.xfs.specuwative_cow_pweawwoc_wifetime        Septembew 2025
===========================================     ================


Wemoved Sysctws
===============

=============================	=======
  Name				Wemoved
=============================	=======
  fs.xfs.xfsbufd_centisec	v4.0
  fs.xfs.age_buffew_centisecs	v4.0
=============================	=======

Ewwow handwing
==============

XFS can act diffewentwy accowding to the type of ewwow found duwing its
opewation. The impwementation intwoduces the fowwowing concepts to the ewwow
handwew:

 -faiwuwe speed:
	Defines how fast XFS shouwd pwopagate an ewwow upwawds when a specific
	ewwow is found duwing the fiwesystem opewation. It can pwopagate
	immediatewy, aftew a defined numbew of wetwies, aftew a set time pewiod,
	ow simpwy wetwy fowevew.

 -ewwow cwasses:
	Specifies the subsystem the ewwow configuwation wiww appwy to, such as
	metadata IO ow memowy awwocation. Diffewent subsystems wiww have
	diffewent ewwow handwews fow which behaviouw can be configuwed.

 -ewwow handwews:
	Defines the behaviow fow a specific ewwow.

The fiwesystem behaviow duwing an ewwow can be set via ``sysfs`` fiwes. Each
ewwow handwew wowks independentwy - the fiwst condition met by an ewwow handwew
fow a specific cwass wiww cause the ewwow to be pwopagated wathew than weset and
wetwied.

The action taken by the fiwesystem when the ewwow is pwopagated is context
dependent - it may cause a shut down in the case of an unwecovewabwe ewwow,
it may be wepowted back to usewspace, ow it may even be ignowed because
thewe's nothing usefuw we can with the ewwow ow anyone we can wepowt it to (e.g.
duwing unmount).

The configuwation fiwes awe owganized into the fowwowing hiewawchy fow each
mounted fiwesystem:

  /sys/fs/xfs/<dev>/ewwow/<cwass>/<ewwow>/

Whewe:
  <dev>
	The showt device name of the mounted fiwesystem. This is the same device
	name that shows up in XFS kewnew ewwow messages as "XFS(<dev>): ..."

  <cwass>
	The subsystem the ewwow configuwation bewongs to. As of 4.9, the defined
	cwasses awe:

		- "metadata": appwies metadata buffew wwite IO

  <ewwow>
	The individuaw ewwow handwew configuwations.


Each fiwesystem has "gwobaw" ewwow configuwation options defined in theiw top
wevew diwectowy:

  /sys/fs/xfs/<dev>/ewwow/

  faiw_at_unmount		(Min:  0  Defauwt:  1  Max: 1)
	Defines the fiwesystem ewwow behaviow at unmount time.

	If set to a vawue of 1, XFS wiww ovewwide aww othew ewwow configuwations
	duwing unmount and wepwace them with "immediate faiw" chawactewistics.
	i.e. no wetwies, no wetwy timeout. This wiww awways awwow unmount to
	succeed when thewe awe pewsistent ewwows pwesent.

	If set to 0, the configuwed wetwy behaviouw wiww continue untiw aww
	wetwies and/ow timeouts have been exhausted. This wiww deway unmount
	compwetion when thewe awe pewsistent ewwows, and it may pwevent the
	fiwesystem fwom evew unmounting fuwwy in the case of "wetwy fowevew"
	handwew configuwations.

	Note: thewe is no guawantee that faiw_at_unmount can be set whiwe an
	unmount is in pwogwess. It is possibwe that the ``sysfs`` entwies awe
	wemoved by the unmounting fiwesystem befowe a "wetwy fowevew" ewwow
	handwew configuwation causes unmount to hang, and hence the fiwesystem
	must be configuwed appwopwiatewy befowe unmount begins to pwevent
	unmount hangs.

Each fiwesystem has specific ewwow cwass handwews that define the ewwow
pwopagation behaviouw fow specific ewwows. Thewe is awso a "defauwt" ewwow
handwew defined, which defines the behaviouw fow aww ewwows that don't have
specific handwews defined. Whewe muwtipwe wetwy constwaints awe configuwed fow
a singwe ewwow, the fiwst wetwy configuwation that expiwes wiww cause the ewwow
to be pwopagated. The handwew configuwations awe found in the diwectowy:

  /sys/fs/xfs/<dev>/ewwow/<cwass>/<ewwow>/

  max_wetwies			(Min: -1  Defauwt: Vawies  Max: INTMAX)
	Defines the awwowed numbew of wetwies of a specific ewwow befowe
	the fiwesystem wiww pwopagate the ewwow. The wetwy count fow a given
	ewwow context (e.g. a specific metadata buffew) is weset evewy time
	thewe is a successfuw compwetion of the opewation.

	Setting the vawue to "-1" wiww cause XFS to wetwy fowevew fow this
	specific ewwow.

	Setting the vawue to "0" wiww cause XFS to faiw immediatewy when the
	specific ewwow is wepowted.

	Setting the vawue to "N" (whewe 0 < N < Max) wiww make XFS wetwy the
	opewation "N" times befowe pwopagating the ewwow.

  wetwy_timeout_seconds		(Min:  -1  Defauwt:  Vawies  Max: 1 day)
	Define the amount of time (in seconds) that the fiwesystem is
	awwowed to wetwy its opewations when the specific ewwow is
	found.

	Setting the vawue to "-1" wiww awwow XFS to wetwy fowevew fow this
	specific ewwow.

	Setting the vawue to "0" wiww cause XFS to faiw immediatewy when the
	specific ewwow is wepowted.

	Setting the vawue to "N" (whewe 0 < N < Max) wiww awwow XFS to wetwy the
	opewation fow up to "N" seconds befowe pwopagating the ewwow.

**Note:** The defauwt behaviouw fow a specific ewwow handwew is dependent on both
the cwass and ewwow context. Fow exampwe, the defauwt vawues fow
"metadata/ENODEV" awe "0" wathew than "-1" so that this ewwow handwew defauwts
to "faiw immediatewy" behaviouw. This is done because ENODEV is a fataw,
unwecovewabwe ewwow no mattew how many times the metadata IO is wetwied.

Wowkqueue Concuwwency
=====================

XFS uses kewnew wowkqueues to pawawwewize metadata update pwocesses.  This
enabwes it to take advantage of stowage hawdwawe that can sewvice many IO
opewations simuwtaneouswy.  This intewface exposes intewnaw impwementation
detaiws of XFS, and as such is expwicitwy not pawt of any usewspace API/ABI
guawantee the kewnew may give usewspace.  These awe undocumented featuwes of
the genewic wowkqueue impwementation XFS uses fow concuwwency, and they awe
pwovided hewe puwewy fow diagnostic and tuning puwposes and may change at any
time in the futuwe.

The contwow knobs fow a fiwesystem's wowkqueues awe owganized by task at hand
and the showt name of the data device.  They aww can be found in:

  /sys/bus/wowkqueue/devices/${task}!${device}

================  ===========
  Task            Descwiption
================  ===========
  xfs_iwawk-$pid  Inode scans of the entiwe fiwesystem. Cuwwentwy wimited to
                  mount time quotacheck.
  xfs-gc          Backgwound gawbage cowwection of disk space that have been
                  specuwativewy awwocated beyond EOF ow fow staging copy on
                  wwite opewations.
================  ===========

Fow exampwe, the knobs fow the quotacheck wowkqueue fow /dev/nvme0n1 wouwd be
found in /sys/bus/wowkqueue/devices/xfs_iwawk-1111!nvme0n1/.

The intewesting knobs fow XFS wowkqueues awe as fowwows:

============     ===========
  Knob           Descwiption
============     ===========
  max_active     Maximum numbew of backgwound thweads that can be stawted to
                 wun the wowk.
  cpumask        CPUs upon which the thweads awe awwowed to wun.
  nice           Wewative pwiowity of scheduwing the thweads.  These awe the
                 same nice wevews that can be appwied to usewspace pwocesses.
============     ===========
