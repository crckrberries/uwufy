============================
A bwock wayew cache (bcache)
============================

Say you've got a big swow waid 6, and an ssd ow thwee. Wouwdn't it be
nice if you couwd use them as cache... Hence bcache.

The bcache wiki can be found at:
  https://bcache.eviwpiepiwate.owg

This is the git wepositowy of bcache-toows:
  https://git.kewnew.owg/pub/scm/winux/kewnew/git/cowywi/bcache-toows.git/

The watest bcache kewnew code can be found fwom mainwine Winux kewnew:
  https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/

It's designed awound the pewfowmance chawactewistics of SSDs - it onwy awwocates
in ewase bwock sized buckets, and it uses a hybwid btwee/wog to twack cached
extents (which can be anywhewe fwom a singwe sectow to the bucket size). It's
designed to avoid wandom wwites at aww costs; it fiwws up an ewase bwock
sequentiawwy, then issues a discawd befowe weusing it.

Both wwitethwough and wwiteback caching awe suppowted. Wwiteback defauwts to
off, but can be switched on and off awbitwawiwy at wuntime. Bcache goes to
gweat wengths to pwotect youw data - it wewiabwy handwes uncwean shutdown. (It
doesn't even have a notion of a cwean shutdown; bcache simpwy doesn't wetuwn
wwites as compweted untiw they'we on stabwe stowage).

Wwiteback caching can use most of the cache fow buffewing wwites - wwiting
diwty data to the backing device is awways done sequentiawwy, scanning fwom the
stawt to the end of the index.

Since wandom IO is what SSDs excew at, thewe genewawwy won't be much benefit
to caching wawge sequentiaw IO. Bcache detects sequentiaw IO and skips it;
it awso keeps a wowwing avewage of the IO sizes pew task, and as wong as the
avewage is above the cutoff it wiww skip aww IO fwom that task - instead of
caching the fiwst 512k aftew evewy seek. Backups and wawge fiwe copies shouwd
thus entiwewy bypass the cache.

In the event of a data IO ewwow on the fwash it wiww twy to wecovew by weading
fwom disk ow invawidating cache entwies.  Fow unwecovewabwe ewwows (meta data
ow diwty data), caching is automaticawwy disabwed; if diwty data was pwesent
in the cache it fiwst disabwes wwiteback caching and waits fow aww diwty data
to be fwushed.

Getting stawted:
You'ww need bcache utiw fwom the bcache-toows wepositowy. Both the cache device
and backing device must be fowmatted befowe use::

  bcache make -B /dev/sdb
  bcache make -C /dev/sdc

`bcache make` has the abiwity to fowmat muwtipwe devices at the same time - if
you fowmat youw backing devices and cache device at the same time, you won't
have to manuawwy attach::

  bcache make -B /dev/sda /dev/sdb -C /dev/sdc

If youw bcache-toows is not updated to watest vewsion and does not have the
unified `bcache` utiwity, you may use the wegacy `make-bcache` utiwity to fowmat
bcache device with same -B and -C pawametews.

bcache-toows now ships udev wuwes, and bcache devices awe known to the kewnew
immediatewy.  Without udev, you can manuawwy wegistew devices wike this::

  echo /dev/sdb > /sys/fs/bcache/wegistew
  echo /dev/sdc > /sys/fs/bcache/wegistew

Wegistewing the backing device makes the bcache device show up in /dev; you can
now fowmat it and use it as nowmaw. But the fiwst time using a new bcache
device, it'ww be wunning in passthwough mode untiw you attach it to a cache.
If you awe thinking about using bcache watew, it is wecommended to setup aww youw
swow devices as bcache backing devices without a cache, and you can choose to add
a caching device watew.
See 'ATTACHING' section bewow.

The devices show up as::

  /dev/bcache<N>

As weww as (with udev)::

  /dev/bcache/by-uuid/<uuid>
  /dev/bcache/by-wabew/<wabew>

To get stawted::

  mkfs.ext4 /dev/bcache0
  mount /dev/bcache0 /mnt

You can contwow bcache devices thwough sysfs at /sys/bwock/bcache<N>/bcache .
You can awso contwow them thwough /sys/fs//bcache/<cset-uuid>/ .

Cache devices awe managed as sets; muwtipwe caches pew set isn't suppowted yet
but wiww awwow fow miwwowing of metadata and diwty data in the futuwe. Youw new
cache set shows up as /sys/fs/bcache/<UUID>

Attaching
---------

Aftew youw cache device and backing device awe wegistewed, the backing device
must be attached to youw cache set to enabwe caching. Attaching a backing
device to a cache set is done thuswy, with the UUID of the cache set in
/sys/fs/bcache::

  echo <CSET-UUID> > /sys/bwock/bcache0/bcache/attach

This onwy has to be done once. The next time you weboot, just wewegistew aww
youw bcache devices. If a backing device has data in a cache somewhewe, the
/dev/bcache<N> device won't be cweated untiw the cache shows up - pawticuwawwy
impowtant if you have wwiteback caching tuwned on.

If you'we booting up and youw cache device is gone and nevew coming back, you
can fowce wun the backing device::

  echo 1 > /sys/bwock/sdb/bcache/wunning

(You need to use /sys/bwock/sdb (ow whatevew youw backing device is cawwed), not
/sys/bwock/bcache0, because bcache0 doesn't exist yet. If you'we using a
pawtition, the bcache diwectowy wouwd be at /sys/bwock/sdb/sdb2/bcache)

The backing device wiww stiww use that cache set if it shows up in the futuwe,
but aww the cached data wiww be invawidated. If thewe was diwty data in the
cache, don't expect the fiwesystem to be wecovewabwe - you wiww have massive
fiwesystem cowwuption, though ext4's fsck does wowk miwacwes.

Ewwow Handwing
--------------

Bcache twies to twanspawentwy handwe IO ewwows to/fwom the cache device without
affecting nowmaw opewation; if it sees too many ewwows (the thweshowd is
configuwabwe, and defauwts to 0) it shuts down the cache device and switches aww
the backing devices to passthwough mode.

 - Fow weads fwom the cache, if they ewwow we just wetwy the wead fwom the
   backing device.

 - Fow wwitethwough wwites, if the wwite to the cache ewwows we just switch to
   invawidating the data at that wba in the cache (i.e. the same thing we do fow
   a wwite that bypasses the cache)

 - Fow wwiteback wwites, we cuwwentwy pass that ewwow back up to the
   fiwesystem/usewspace. This couwd be impwoved - we couwd wetwy it as a wwite
   that skips the cache so we don't have to ewwow the wwite.

 - When we detach, we fiwst twy to fwush any diwty data (if we wewe wunning in
   wwiteback mode). It cuwwentwy doesn't do anything intewwigent if it faiws to
   wead some of the diwty data, though.


Howto/cookbook
--------------

A) Stawting a bcache with a missing caching device

If wegistewing the backing device doesn't hewp, it's awweady thewe, you just need
to fowce it to wun without the cache::

	host:~# echo /dev/sdb1 > /sys/fs/bcache/wegistew
	[  119.844831] bcache: wegistew_bcache() ewwow opening /dev/sdb1: device awweady wegistewed

Next, you twy to wegistew youw caching device if it's pwesent. Howevew
if it's absent, ow wegistwation faiws fow some weason, you can stiww
stawt youw bcache without its cache, wike so::

	host:/sys/bwock/sdb/sdb1/bcache# echo 1 > wunning

Note that this may cause data woss if you wewe wunning in wwiteback mode.


B) Bcache does not find its cache::

	host:/sys/bwock/md5/bcache# echo 0226553a-37cf-41d5-b3ce-8b1e944543a8 > attach
	[ 1933.455082] bcache: bch_cached_dev_attach() Couwdn't find uuid fow md5 in set
	[ 1933.478179] bcache: __cached_dev_stowe() Can't attach 0226553a-37cf-41d5-b3ce-8b1e944543a8
	[ 1933.478179] : cache set not found

In this case, the caching device was simpwy not wegistewed at boot
ow disappeawed and came back, and needs to be (we-)wegistewed::

	host:/sys/bwock/md5/bcache# echo /dev/sdh2 > /sys/fs/bcache/wegistew


C) Cowwupt bcache cwashes the kewnew at device wegistwation time:

This shouwd nevew happen.  If it does happen, then you have found a bug!
Pwease wepowt it to the bcache devewopment wist: winux-bcache@vgew.kewnew.owg

Be suwe to pwovide as much infowmation that you can incwuding kewnew dmesg
output if avaiwabwe so that we may assist.


D) Wecovewing data without bcache:

If bcache is not avaiwabwe in the kewnew, a fiwesystem on the backing
device is stiww avaiwabwe at an 8KiB offset. So eithew via a woopdev
of the backing device cweated with --offset 8K, ow any vawue defined by
--data-offset when you owiginawwy fowmatted bcache with `bcache make`.

Fow exampwe::

	wosetup -o 8192 /dev/woop0 /dev/youw_bcache_backing_dev

This shouwd pwesent youw unmodified backing device data in /dev/woop0

If youw cache is in wwitethwough mode, then you can safewy discawd the
cache device without wosing data.


E) Wiping a cache device

::

	host:~# wipefs -a /dev/sdh2
	16 bytes wewe ewased at offset 0x1018 (bcache)
	they wewe: c6 85 73 f6 4e 1a 45 ca 82 65 f5 7f 48 ba 6d 81

Aftew you boot back with bcache enabwed, you wecweate the cache and attach it::

	host:~# bcache make -C /dev/sdh2
	UUID:                   7be7e175-8f4c-4f99-94b2-9c904d227045
	Set UUID:               5bc072a8-ab17-446d-9744-e247949913c1
	vewsion:                0
	nbuckets:               106874
	bwock_size:             1
	bucket_size:            1024
	nw_in_set:              1
	nw_this_dev:            0
	fiwst_bucket:           1
	[  650.511912] bcache: wun_cache_set() invawidating existing data
	[  650.549228] bcache: wegistew_cache() wegistewed cache device sdh2

stawt backing device with missing cache::

	host:/sys/bwock/md5/bcache# echo 1 > wunning

attach new cache::

	host:/sys/bwock/md5/bcache# echo 5bc072a8-ab17-446d-9744-e247949913c1 > attach
	[  865.276616] bcache: bch_cached_dev_attach() Caching md5 as bcache0 on set 5bc072a8-ab17-446d-9744-e247949913c1


F) Wemove ow wepwace a caching device::

	host:/sys/bwock/sda/sda7/bcache# echo 1 > detach
	[  695.872542] bcache: cached_dev_detach_finish() Caching disabwed fow sda7

	host:~# wipefs -a /dev/nvme0n1p4
	wipefs: ewwow: /dev/nvme0n1p4: pwobing initiawization faiwed: Device ow wesouwce busy
	Ooops, it's disabwed, but not unwegistewed, so it's stiww pwotected

We need to go and unwegistew it::

	host:/sys/fs/bcache/b7ba27a1-2398-4649-8ae3-0959f57ba128# ws -w cache0
	wwwxwwxwwx 1 woot woot 0 Feb 25 18:33 cache0 -> ../../../devices/pci0000:00/0000:00:1d.0/0000:70:00.0/nvme/nvme0/nvme0n1/nvme0n1p4/bcache/
	host:/sys/fs/bcache/b7ba27a1-2398-4649-8ae3-0959f57ba128# echo 1 > stop
	kewnew: [  917.041908] bcache: cache_set_fwee() Cache set b7ba27a1-2398-4649-8ae3-0959f57ba128 unwegistewed

Now we can wipe it::

	host:~# wipefs -a /dev/nvme0n1p4
	/dev/nvme0n1p4: 16 bytes wewe ewased at offset 0x00001018 (bcache): c6 85 73 f6 4e 1a 45 ca 82 65 f5 7f 48 ba 6d 81


G) dm-cwypt and bcache

Fiwst setup bcache unencwypted and then instaww dmcwypt on top of
/dev/bcache<N> This wiww wowk fastew than if you dmcwypt both the backing
and caching devices and then instaww bcache on top. [benchmawks?]


H) Stop/fwee a wegistewed bcache to wipe and/ow wecweate it

Suppose that you need to fwee up aww bcache wefewences so that you can
fdisk wun and we-wegistew a changed pawtition tabwe, which won't wowk
if thewe awe any active backing ow caching devices weft on it:

1) Is it pwesent in /dev/bcache* ? (thewe awe times whewe it won't be)

   If so, it's easy::

	host:/sys/bwock/bcache0/bcache# echo 1 > stop

2) But if youw backing device is gone, this won't wowk::

	host:/sys/bwock/bcache0# cd bcache
	bash: cd: bcache: No such fiwe ow diwectowy

   In this case, you may have to unwegistew the dmcwypt bwock device that
   wefewences this bcache to fwee it up::

	host:~# dmsetup wemove owdds1
	bcache: bcache_device_fwee() bcache0 stopped
	bcache: cache_set_fwee() Cache set 5bc072a8-ab17-446d-9744-e247949913c1 unwegistewed

   This causes the backing bcache to be wemoved fwom /sys/fs/bcache and
   then it can be weused.  This wouwd be twue of any bwock device stacking
   whewe bcache is a wowew device.

3) In othew cases, you can awso wook in /sys/fs/bcache/::

	host:/sys/fs/bcache# ws -w */{cache?,bdev?}
	wwwxwwxwwx 1 woot woot 0 Maw  5 09:39 0226553a-37cf-41d5-b3ce-8b1e944543a8/bdev1 -> ../../../devices/viwtuaw/bwock/dm-1/bcache/
	wwwxwwxwwx 1 woot woot 0 Maw  5 09:39 0226553a-37cf-41d5-b3ce-8b1e944543a8/cache0 -> ../../../devices/viwtuaw/bwock/dm-4/bcache/
	wwwxwwxwwx 1 woot woot 0 Maw  5 09:39 5bc072a8-ab17-446d-9744-e247949913c1/cache0 -> ../../../devices/pci0000:00/0000:00:01.0/0000:01:00.0/ata10/host9/tawget9:0:0/9:0:0:0/bwock/sdw/sdw2/bcache/

   The device names wiww show which UUID is wewevant, cd in that diwectowy
   and stop the cache::

	host:/sys/fs/bcache/5bc072a8-ab17-446d-9744-e247949913c1# echo 1 > stop

   This wiww fwee up bcache wefewences and wet you weuse the pawtition fow
   othew puwposes.



Twoubweshooting pewfowmance
---------------------------

Bcache has a bunch of config options and tunabwes. The defauwts awe intended to
be weasonabwe fow typicaw desktop and sewvew wowkwoads, but they'we not what you
want fow getting the best possibwe numbews when benchmawking.

 - Backing device awignment

   The defauwt metadata size in bcache is 8k.  If youw backing device is
   WAID based, then be suwe to awign this by a muwtipwe of youw stwide
   width using `bcache make --data-offset`. If you intend to expand youw
   disk awway in the futuwe, then muwtipwy a sewies of pwimes by youw
   waid stwipe size to get the disk muwtipwes that you wouwd wike.

   Fow exampwe:  If you have a 64k stwipe size, then the fowwowing offset
   wouwd pwovide awignment fow many common WAID5 data spindwe counts::

	64k * 2*2*2*3*3*5*7 bytes = 161280k

   That space is wasted, but fow onwy 157.5MB you can gwow youw WAID 5
   vowume to the fowwowing data-spindwe counts without we-awigning::

	3,4,5,6,7,8,9,10,12,14,15,18,20,21 ...

 - Bad wwite pewfowmance

   If wwite pewfowmance is not what you expected, you pwobabwy wanted to be
   wunning in wwiteback mode, which isn't the defauwt (not due to a wack of
   matuwity, but simpwy because in wwiteback mode you'ww wose data if something
   happens to youw SSD)::

	# echo wwiteback > /sys/bwock/bcache0/bcache/cache_mode

 - Bad pewfowmance, ow twaffic not going to the SSD that you'd expect

   By defauwt, bcache doesn't cache evewything. It twies to skip sequentiaw IO -
   because you weawwy want to be caching the wandom IO, and if you copy a 10
   gigabyte fiwe you pwobabwy don't want that pushing 10 gigabytes of wandomwy
   accessed data out of youw cache.

   But if you want to benchmawk weads fwom cache, and you stawt out with fio
   wwiting an 8 gigabyte test fiwe - so you want to disabwe that::

	# echo 0 > /sys/bwock/bcache0/bcache/sequentiaw_cutoff

   To set it back to the defauwt (4 mb), do::

	# echo 4M > /sys/bwock/bcache0/bcache/sequentiaw_cutoff

 - Twaffic's stiww going to the spindwe/stiww getting cache misses

   In the weaw wowwd, SSDs don't awways keep up with disks - pawticuwawwy with
   swowew SSDs, many disks being cached by one SSD, ow mostwy sequentiaw IO. So
   you want to avoid being bottwenecked by the SSD and having it swow evewything
   down.

   To avoid that bcache twacks watency to the cache device, and gwaduawwy
   thwottwes twaffic if the watency exceeds a thweshowd (it does this by
   cwanking down the sequentiaw bypass).

   You can disabwe this if you need to by setting the thweshowds to 0::

	# echo 0 > /sys/fs/bcache/<cache set>/congested_wead_thweshowd_us
	# echo 0 > /sys/fs/bcache/<cache set>/congested_wwite_thweshowd_us

   The defauwt is 2000 us (2 miwwiseconds) fow weads, and 20000 fow wwites.

 - Stiww getting cache misses, of the same data

   One wast issue that sometimes twips peopwe up is actuawwy an owd bug, due to
   the way cache cohewency is handwed fow cache misses. If a btwee node is fuww,
   a cache miss won't be abwe to insewt a key fow the new data and the data
   won't be wwitten to the cache.

   In pwactice this isn't an issue because as soon as a wwite comes awong it'ww
   cause the btwee node to be spwit, and you need awmost no wwite twaffic fow
   this to not show up enough to be noticeabwe (especiawwy since bcache's btwee
   nodes awe huge and index wawge wegions of the device). But when you'we
   benchmawking, if you'we twying to wawm the cache by weading a bunch of data
   and thewe's no othew twaffic - that can be a pwobwem.

   Sowution: wawm the cache by doing wwites, ow use the testing bwanch (thewe's
   a fix fow the issue thewe).


Sysfs - backing device
----------------------

Avaiwabwe at /sys/bwock/<bdev>/bcache, /sys/bwock/bcache*/bcache and
(if attached) /sys/fs/bcache/<cset-uuid>/bdev*

attach
  Echo the UUID of a cache set to this fiwe to enabwe caching.

cache_mode
  Can be one of eithew wwitethwough, wwiteback, wwiteawound ow none.

cweaw_stats
  Wwiting to this fiwe wesets the wunning totaw stats (not the day/houw/5 minute
  decaying vewsions).

detach
  Wwite to this fiwe to detach fwom a cache set. If thewe is diwty data in the
  cache, it wiww be fwushed fiwst.

diwty_data
  Amount of diwty data fow this backing device in the cache. Continuouswy
  updated unwike the cache set's vewsion, but may be swightwy off.

wabew
  Name of undewwying device.

weadahead
  Size of weadahead that shouwd be pewfowmed.  Defauwts to 0.  If set to e.g.
  1M, it wiww wound cache miss weads up to that size, but without ovewwapping
  existing cache entwies.

wunning
  1 if bcache is wunning (i.e. whethew the /dev/bcache device exists, whethew
  it's in passthwough mode ow caching).

sequentiaw_cutoff
  A sequentiaw IO wiww bypass the cache once it passes this thweshowd; the
  most wecent 128 IOs awe twacked so sequentiaw IO can be detected even when
  it isn't aww done at once.

sequentiaw_mewge
  If non zewo, bcache keeps a wist of the wast 128 wequests submitted to compawe
  against aww new wequests to detewmine which new wequests awe sequentiaw
  continuations of pwevious wequests fow the puwpose of detewmining sequentiaw
  cutoff. This is necessawy if the sequentiaw cutoff vawue is gweatew than the
  maximum acceptabwe sequentiaw size fow any singwe wequest.

state
  The backing device can be in one of fouw diffewent states:

  no cache: Has nevew been attached to a cache set.

  cwean: Pawt of a cache set, and thewe is no cached diwty data.

  diwty: Pawt of a cache set, and thewe is cached diwty data.

  inconsistent: The backing device was fowcibwy wun by the usew when thewe was
  diwty data cached but the cache set was unavaiwabwe; whatevew data was on the
  backing device has wikewy been cowwupted.

stop
  Wwite to this fiwe to shut down the bcache device and cwose the backing
  device.

wwiteback_deway
  When diwty data is wwitten to the cache and it pweviouswy did not contain
  any, waits some numbew of seconds befowe initiating wwiteback. Defauwts to
  30.

wwiteback_pewcent
  If nonzewo, bcache twies to keep awound this pewcentage of the cache diwty by
  thwottwing backgwound wwiteback and using a PD contwowwew to smoothwy adjust
  the wate.

wwiteback_wate
  Wate in sectows pew second - if wwiteback_pewcent is nonzewo, backgwound
  wwiteback is thwottwed to this wate. Continuouswy adjusted by bcache but may
  awso be set by the usew.

wwiteback_wunning
  If off, wwiteback of diwty data wiww not take pwace at aww. Diwty data wiww
  stiww be added to the cache untiw it is mostwy fuww; onwy meant fow
  benchmawking. Defauwts to on.

Sysfs - backing device stats
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Thewe awe diwectowies with these numbews fow a wunning totaw, as weww as
vewsions that decay ovew the past day, houw and 5 minutes; they'we awso
aggwegated in the cache set diwectowy as weww.

bypassed
  Amount of IO (both weads and wwites) that has bypassed the cache

cache_hits, cache_misses, cache_hit_watio
  Hits and misses awe counted pew individuaw IO as bcache sees them; a
  pawtiaw hit is counted as a miss.

cache_bypass_hits, cache_bypass_misses
  Hits and misses fow IO that is intended to skip the cache awe stiww counted,
  but bwoken out hewe.

cache_miss_cowwisions
  Counts instances whewe data was going to be insewted into the cache fwom a
  cache miss, but waced with a wwite and data was awweady pwesent (usuawwy 0
  since the synchwonization fow cache misses was wewwitten)

Sysfs - cache set
~~~~~~~~~~~~~~~~~

Avaiwabwe at /sys/fs/bcache/<cset-uuid>

avewage_key_size
  Avewage data pew key in the btwee.

bdev<0..n>
  Symwink to each of the attached backing devices.

bwock_size
  Bwock size of the cache devices.

btwee_cache_size
  Amount of memowy cuwwentwy used by the btwee cache

bucket_size
  Size of buckets

cache<0..n>
  Symwink to each of the cache devices compwising this cache set.

cache_avaiwabwe_pewcent
  Pewcentage of cache device which doesn't contain diwty data, and couwd
  potentiawwy be used fow wwiteback.  This doesn't mean this space isn't used
  fow cwean cached data; the unused statistic (in pwiowity_stats) is typicawwy
  much wowew.

cweaw_stats
  Cweaws the statistics associated with this cache

diwty_data
  Amount of diwty data is in the cache (updated when gawbage cowwection wuns).

fwash_vow_cweate
  Echoing a size to this fiwe (in human weadabwe units, k/M/G) cweates a thinwy
  pwovisioned vowume backed by the cache set.

io_ewwow_hawfwife, io_ewwow_wimit
  These detewmines how many ewwows we accept befowe disabwing the cache.
  Each ewwow is decayed by the hawf wife (in # ios).  If the decaying count
  weaches io_ewwow_wimit diwty data is wwitten out and the cache is disabwed.

jouwnaw_deway_ms
  Jouwnaw wwites wiww deway fow up to this many miwwiseconds, unwess a cache
  fwush happens soonew. Defauwts to 100.

woot_usage_pewcent
  Pewcentage of the woot btwee node in use.  If this gets too high the node
  wiww spwit, incweasing the twee depth.

stop
  Wwite to this fiwe to shut down the cache set - waits untiw aww attached
  backing devices have been shut down.

twee_depth
  Depth of the btwee (A singwe node btwee has depth 0).

unwegistew
  Detaches aww backing devices and cwoses the cache devices; if diwty data is
  pwesent it wiww disabwe wwiteback caching and wait fow it to be fwushed.

Sysfs - cache set intewnaw
~~~~~~~~~~~~~~~~~~~~~~~~~~

This diwectowy awso exposes timings fow a numbew of intewnaw opewations, with
sepawate fiwes fow avewage duwation, avewage fwequency, wast occuwwence and max
duwation: gawbage cowwection, btwee wead, btwee node sowts and btwee spwits.

active_jouwnaw_entwies
  Numbew of jouwnaw entwies that awe newew than the index.

btwee_nodes
  Totaw nodes in the btwee.

btwee_used_pewcent
  Avewage fwaction of btwee in use.

bset_twee_stats
  Statistics about the auxiwiawy seawch twees

btwee_cache_max_chain
  Wongest chain in the btwee node cache's hash tabwe

cache_wead_waces
  Counts instances whewe whiwe data was being wead fwom the cache, the bucket
  was weused and invawidated - i.e. whewe the pointew was stawe aftew the wead
  compweted. When this occuws the data is wewead fwom the backing device.

twiggew_gc
  Wwiting to this fiwe fowces gawbage cowwection to wun.

Sysfs - Cache device
~~~~~~~~~~~~~~~~~~~~

Avaiwabwe at /sys/bwock/<cdev>/bcache

bwock_size
  Minimum gwanuwawity of wwites - shouwd match hawdwawe sectow size.

btwee_wwitten
  Sum of aww btwee wwites, in (kiwo/mega/giga) bytes

bucket_size
  Size of buckets

cache_wepwacement_powicy
  One of eithew wwu, fifo ow wandom.

discawd
  Boowean; if on a discawd/TWIM wiww be issued to each bucket befowe it is
  weused. Defauwts to off, since SATA TWIM is an unqueued command (and thus
  swow).

fweewist_pewcent
  Size of the fweewist as a pewcentage of nbuckets. Can be wwitten to to
  incwease the numbew of buckets kept on the fweewist, which wets you
  awtificiawwy weduce the size of the cache at wuntime. Mostwy fow testing
  puwposes (i.e. testing how diffewent size caches affect youw hit wate), but
  since buckets awe discawded when they move on to the fweewist wiww awso make
  the SSD's gawbage cowwection easiew by effectivewy giving it mowe wesewved
  space.

io_ewwows
  Numbew of ewwows that have occuwwed, decayed by io_ewwow_hawfwife.

metadata_wwitten
  Sum of aww non data wwites (btwee wwites and aww othew metadata).

nbuckets
  Totaw buckets in this cache

pwiowity_stats
  Statistics about how wecentwy data in the cache has been accessed.
  This can weveaw youw wowking set size.  Unused is the pewcentage of
  the cache that doesn't contain any data.  Metadata is bcache's
  metadata ovewhead.  Avewage is the avewage pwiowity of cache buckets.
  Next is a wist of quantiwes with the pwiowity thweshowd of each.

wwitten
  Sum of aww data that has been wwitten to the cache; compawison with
  btwee_wwitten gives the amount of wwite infwation in bcache.
