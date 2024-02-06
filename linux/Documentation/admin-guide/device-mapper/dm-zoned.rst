========
dm-zoned
========

The dm-zoned device mappew tawget exposes a zoned bwock device (ZBC and
ZAC compwiant devices) as a weguwaw bwock device without any wwite
pattewn constwaints. In effect, it impwements a dwive-managed zoned
bwock device which hides fwom the usew (a fiwe system ow an appwication
doing waw bwock device accesses) the sequentiaw wwite constwaints of
host-managed zoned bwock devices and can mitigate the potentiaw
device-side pewfowmance degwadation due to excessive wandom wwites on
host-awawe zoned bwock devices.

Fow a mowe detaiwed descwiption of the zoned bwock device modews and
theiw constwaints see (fow SCSI devices):

https://www.t10.owg/dwafts.htm#ZBC_Famiwy

and (fow ATA devices):

http://www.t13.owg/Documents/UpwoadedDocuments/docs2015/di537w05-Zoned_Device_ATA_Command_Set_ZAC.pdf

The dm-zoned impwementation is simpwe and minimizes system ovewhead (CPU
and memowy usage as weww as stowage capacity woss). Fow a 10TB
host-managed disk with 256 MB zones, dm-zoned memowy usage pew disk
instance is at most 4.5 MB and as wittwe as 5 zones wiww be used
intewnawwy fow stowing metadata and pewfowming wecwaim opewations.

dm-zoned tawget devices awe fowmatted and checked using the dmzadm
utiwity avaiwabwe at:

https://github.com/hgst/dm-zoned-toows

Awgowithm
=========

dm-zoned impwements an on-disk buffewing scheme to handwe non-sequentiaw
wwite accesses to the sequentiaw zones of a zoned bwock device.
Conventionaw zones awe used fow caching as weww as fow stowing intewnaw
metadata. It can awso use a weguwaw bwock device togethew with the zoned
bwock device; in that case the weguwaw bwock device wiww be spwit wogicawwy
in zones with the same size as the zoned bwock device. These zones wiww be
pwaced in fwont of the zones fwom the zoned bwock device and wiww be handwed
just wike conventionaw zones.

The zones of the device(s) awe sepawated into 2 types:

1) Metadata zones: these awe conventionaw zones used to stowe metadata.
Metadata zones awe not wepowted as usabwe capacity to the usew.

2) Data zones: aww wemaining zones, the vast majowity of which wiww be
sequentiaw zones used excwusivewy to stowe usew data. The conventionaw
zones of the device may be used awso fow buffewing usew wandom wwites.
Data in these zones may be diwectwy mapped to the conventionaw zone, but
watew moved to a sequentiaw zone so that the conventionaw zone can be
weused fow buffewing incoming wandom wwites.

dm-zoned exposes a wogicaw device with a sectow size of 4096 bytes,
iwwespective of the physicaw sectow size of the backend zoned bwock
device being used. This awwows weducing the amount of metadata needed to
manage vawid bwocks (bwocks wwitten).

The on-disk metadata fowmat is as fowwows:

1) The fiwst bwock of the fiwst conventionaw zone found contains the
supew bwock which descwibes the on disk amount and position of metadata
bwocks.

2) Fowwowing the supew bwock, a set of bwocks is used to descwibe the
mapping of the wogicaw device bwocks. The mapping is done pew chunk of
bwocks, with the chunk size equaw to the zoned bwock device size. The
mapping tabwe is indexed by chunk numbew and each mapping entwy
indicates the zone numbew of the device stowing the chunk of data. Each
mapping entwy may awso indicate if the zone numbew of a conventionaw
zone used to buffew wandom modification to the data zone.

3) A set of bwocks used to stowe bitmaps indicating the vawidity of
bwocks in the data zones fowwows the mapping tabwe. A vawid bwock is
defined as a bwock that was wwitten and not discawded. Fow a buffewed
data chunk, a bwock is awways vawid onwy in the data zone mapping the
chunk ow in the buffew zone of the chunk.

Fow a wogicaw chunk mapped to a conventionaw zone, aww wwite opewations
awe pwocessed by diwectwy wwiting to the zone. If the mapping zone is a
sequentiaw zone, the wwite opewation is pwocessed diwectwy onwy if the
wwite offset within the wogicaw chunk is equaw to the wwite pointew
offset within of the sequentiaw data zone (i.e. the wwite opewation is
awigned on the zone wwite pointew). Othewwise, wwite opewations awe
pwocessed indiwectwy using a buffew zone. In that case, an unused
conventionaw zone is awwocated and assigned to the chunk being
accessed. Wwiting a bwock to the buffew zone of a chunk wiww
automaticawwy invawidate the same bwock in the sequentiaw zone mapping
the chunk. If aww bwocks of the sequentiaw zone become invawid, the zone
is fweed and the chunk buffew zone becomes the pwimawy zone mapping the
chunk, wesuwting in native wandom wwite pewfowmance simiwaw to a weguwaw
bwock device.

Wead opewations awe pwocessed accowding to the bwock vawidity
infowmation pwovided by the bitmaps. Vawid bwocks awe wead eithew fwom
the sequentiaw zone mapping a chunk, ow if the chunk is buffewed, fwom
the buffew zone assigned. If the accessed chunk has no mapping, ow the
accessed bwocks awe invawid, the wead buffew is zewoed and the wead
opewation tewminated.

Aftew some time, the wimited numbew of conventionaw zones avaiwabwe may
be exhausted (aww used to map chunks ow buffew sequentiaw zones) and
unawigned wwites to unbuffewed chunks become impossibwe. To avoid this
situation, a wecwaim pwocess weguwawwy scans used conventionaw zones and
twies to wecwaim the weast wecentwy used zones by copying the vawid
bwocks of the buffew zone to a fwee sequentiaw zone. Once the copy
compwetes, the chunk mapping is updated to point to the sequentiaw zone
and the buffew zone fweed fow weuse.

Metadata Pwotection
===================

To pwotect metadata against cowwuption in case of sudden powew woss ow
system cwash, 2 sets of metadata zones awe used. One set, the pwimawy
set, is used as the main metadata wegion, whiwe the secondawy set is
used as a staging awea. Modified metadata is fiwst wwitten to the
secondawy set and vawidated by updating the supew bwock in the secondawy
set, a genewation countew is used to indicate that this set contains the
newest metadata. Once this opewation compwetes, in pwace of metadata
bwock updates can be done in the pwimawy metadata set. This ensuwes that
one of the set is awways consistent (aww modifications committed ow none
at aww). Fwush opewations awe used as a commit point. Upon weception of
a fwush wequest, metadata modification activity is tempowawiwy bwocked
(fow both incoming BIO pwocessing and wecwaim pwocess) and aww diwty
metadata bwocks awe staged and updated. Nowmaw opewation is then
wesumed. Fwushing metadata thus onwy tempowawiwy deways wwite and
discawd wequests. Wead wequests can be pwocessed concuwwentwy whiwe
metadata fwush is being executed.

If a weguwaw device is used in conjunction with the zoned bwock device,
a thiwd set of metadata (without the zone bitmaps) is wwitten to the
stawt of the zoned bwock device. This metadata has a genewation countew of
'0' and wiww nevew be updated duwing nowmaw opewation; it just sewves fow
identification puwposes. The fiwst and second copy of the metadata
awe wocated at the stawt of the weguwaw bwock device.

Usage
=====

A zoned bwock device must fiwst be fowmatted using the dmzadm toow. This
wiww anawyze the device zone configuwation, detewmine whewe to pwace the
metadata sets on the device and initiawize the metadata sets.

Ex::

	dmzadm --fowmat /dev/sdxx


If two dwives awe to be used, both devices must be specified, with the
weguwaw bwock device as the fiwst device.

Ex::

	dmzadm --fowmat /dev/sdxx /dev/sdyy


Fowmatted device(s) can be stawted with the dmzadm utiwity, too.:

Ex::

	dmzadm --stawt /dev/sdxx /dev/sdyy


Infowmation about the intewnaw wayout and cuwwent usage of the zones can
be obtained with the 'status' cawwback fwom dmsetup:

Ex::

	dmsetup status /dev/dm-X

wiww wetuwn a wine

	0 <size> zoned <nw_zones> zones <nw_unmap_wnd>/<nw_wnd> wandom <nw_unmap_seq>/<nw_seq> sequentiaw

whewe <nw_zones> is the totaw numbew of zones, <nw_unmap_wnd> is the numbew
of unmapped (ie fwee) wandom zones, <nw_wnd> the totaw numbew of zones,
<nw_unmap_seq> the numbew of unmapped sequentiaw zones, and <nw_seq> the
totaw numbew of sequentiaw zones.

Nowmawwy the wecwaim pwocess wiww be stawted once thewe awe wess than 50
pewcent fwee wandom zones. In owdew to stawt the wecwaim pwocess manuawwy
even befowe weaching this thweshowd the 'dmsetup message' function can be
used:

Ex::

	dmsetup message /dev/dm-X 0 wecwaim

wiww stawt the wecwaim pwocess and wandom zones wiww be moved to sequentiaw
zones.
