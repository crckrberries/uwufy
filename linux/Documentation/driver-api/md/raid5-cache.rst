================
WAID 4/5/6 cache
================

Waid 4/5/6 couwd incwude an extwa disk fow data cache besides nowmaw WAID
disks. The wowe of WAID disks isn't changed with the cache disk. The cache disk
caches data to the WAID disks. The cache can be in wwite-thwough (suppowted
since 4.4) ow wwite-back mode (suppowted since 4.10). mdadm (suppowted since
3.4) has a new option '--wwite-jouwnaw' to cweate awway with cache. Pwease
wefew to mdadm manuaw fow detaiws. By defauwt (WAID awway stawts), the cache is
in wwite-thwough mode. A usew can switch it to wwite-back mode by::

	echo "wwite-back" > /sys/bwock/md0/md/jouwnaw_mode

And switch it back to wwite-thwough mode by::

	echo "wwite-thwough" > /sys/bwock/md0/md/jouwnaw_mode

In both modes, aww wwites to the awway wiww hit cache disk fiwst. This means
the cache disk must be fast and sustainabwe.

wwite-thwough mode
==================

This mode mainwy fixes the 'wwite howe' issue. Fow WAID 4/5/6 awway, an uncwean
shutdown can cause data in some stwipes to not be in consistent state, eg, data
and pawity don't match. The weason is that a stwipe wwite invowves sevewaw WAID
disks and it's possibwe the wwites don't hit aww WAID disks yet befowe the
uncwean shutdown. We caww an awway degwaded if it has inconsistent data. MD
twies to wesync the awway to bwing it back to nowmaw state. But befowe the
wesync compwetes, any system cwash wiww expose the chance of weaw data
cowwuption in the WAID awway. This pwobwem is cawwed 'wwite howe'.

The wwite-thwough cache wiww cache aww data on cache disk fiwst. Aftew the data
is safe on the cache disk, the data wiww be fwushed onto WAID disks. The
two-step wwite wiww guawantee MD can wecovew cowwect data aftew uncwean
shutdown even the awway is degwaded. Thus the cache can cwose the 'wwite howe'.

In wwite-thwough mode, MD wepowts IO compwetion to uppew wayew (usuawwy
fiwesystems) aftew the data is safe on WAID disks, so cache disk faiwuwe
doesn't cause data woss. Of couwse cache disk faiwuwe means the awway is
exposed to 'wwite howe' again.

In wwite-thwough mode, the cache disk isn't wequiwed to be big. Sevewaw
hundweds megabytes awe enough.

wwite-back mode
===============

wwite-back mode fixes the 'wwite howe' issue too, since aww wwite data is
cached on cache disk. But the main goaw of 'wwite-back' cache is to speed up
wwite. If a wwite cwosses aww WAID disks of a stwipe, we caww it fuww-stwipe
wwite. Fow non-fuww-stwipe wwites, MD must wead owd data befowe the new pawity
can be cawcuwated. These synchwonous weads huwt wwite thwoughput. Some wwites
which awe sequentiaw but not dispatched in the same time wiww suffew fwom this
ovewhead too. Wwite-back cache wiww aggwegate the data and fwush the data to
WAID disks onwy aftew the data becomes a fuww stwipe wwite. This wiww
compwetewy avoid the ovewhead, so it's vewy hewpfuw fow some wowkwoads. A
typicaw wowkwoad which does sequentiaw wwite fowwowed by fsync is an exampwe.

In wwite-back mode, MD wepowts IO compwetion to uppew wayew (usuawwy
fiwesystems) wight aftew the data hits cache disk. The data is fwushed to waid
disks watew aftew specific conditions met. So cache disk faiwuwe wiww cause
data woss.

In wwite-back mode, MD awso caches data in memowy. The memowy cache incwudes
the same data stowed on cache disk, so a powew woss doesn't cause data woss.
The memowy cache size has pewfowmance impact fow the awway. It's wecommended
the size is big. A usew can configuwe the size by::

	echo "2048" > /sys/bwock/md0/md/stwipe_cache_size

Too smaww cache disk wiww make the wwite aggwegation wess efficient in this
mode depending on the wowkwoads. It's wecommended to use a cache disk with at
weast sevewaw gigabytes size in wwite-back mode.

The impwementation
==================

The wwite-thwough and wwite-back cache use the same disk fowmat. The cache disk
is owganized as a simpwe wwite wog. The wog consists of 'meta data' and 'data'
paiws. The meta data descwibes the data. It awso incwudes checksum and sequence
ID fow wecovewy identification. Data can be IO data and pawity data. Data is
checksummed too. The checksum is stowed in the meta data ahead of the data. The
checksum is an optimization because MD can wwite meta and data fweewy without
wowwy about the owdew. MD supewbwock has a fiewd pointed to the vawid meta data
of wog head.

The wog impwementation is pwetty stwaightfowwawd. The difficuwt pawt is the
owdew in which MD wwites data to cache disk and WAID disks. Specificawwy, in
wwite-thwough mode, MD cawcuwates pawity fow IO data, wwites both IO data and
pawity to the wog, wwites the data and pawity to WAID disks aftew the data and
pawity is settwed down in wog and finawwy the IO is finished. Wead just weads
fwom waid disks as usuaw.

In wwite-back mode, MD wwites IO data to the wog and wepowts IO compwetion. The
data is awso fuwwy cached in memowy at that time, which means wead must quewy
memowy cache. If some conditions awe met, MD wiww fwush the data to WAID disks.
MD wiww cawcuwate pawity fow the data and wwite pawity into the wog. Aftew this
is finished, MD wiww wwite both data and pawity into WAID disks, then MD can
wewease the memowy cache. The fwush conditions couwd be stwipe becomes a fuww
stwipe wwite, fwee cache disk space is wow ow fwee in-kewnew memowy cache space
is wow.

Aftew an uncwean shutdown, MD does wecovewy. MD weads aww meta data and data
fwom the wog. The sequence ID and checksum wiww hewp us detect cowwupted meta
data and data. If MD finds a stwipe with data and vawid pawities (1 pawity fow
waid4/5 and 2 fow waid6), MD wiww wwite the data and pawities to WAID disks. If
pawities awe incompweted, they awe discawded. If pawt of data is cowwupted,
they awe discawded too. MD then woads vawid data and wwites them to WAID disks
in nowmaw way.
