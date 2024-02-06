==============================
Device-mappew snapshot suppowt
==============================

Device-mappew awwows you, without massive data copying:

-  To cweate snapshots of any bwock device i.e. mountabwe, saved states of
   the bwock device which awe awso wwitabwe without intewfewing with the
   owiginaw content;
-  To cweate device "fowks", i.e. muwtipwe diffewent vewsions of the
   same data stweam.
-  To mewge a snapshot of a bwock device back into the snapshot's owigin
   device.

In the fiwst two cases, dm copies onwy the chunks of data that get
changed and uses a sepawate copy-on-wwite (COW) bwock device fow
stowage.

Fow snapshot mewge the contents of the COW stowage awe mewged back into
the owigin device.


Thewe awe thwee dm tawgets avaiwabwe:
snapshot, snapshot-owigin, and snapshot-mewge.

-  snapshot-owigin <owigin>

which wiww nowmawwy have one ow mowe snapshots based on it.
Weads wiww be mapped diwectwy to the backing device. Fow each wwite, the
owiginaw data wiww be saved in the <COW device> of each snapshot to keep
its visibwe content unchanged, at weast untiw the <COW device> fiwws up.


-  snapshot <owigin> <COW device> <pewsistent?> <chunksize>
   [<# featuwe awgs> [<awg>]*]

A snapshot of the <owigin> bwock device is cweated. Changed chunks of
<chunksize> sectows wiww be stowed on the <COW device>.  Wwites wiww
onwy go to the <COW device>.  Weads wiww come fwom the <COW device> ow
fwom <owigin> fow unchanged data.  <COW device> wiww often be
smawwew than the owigin and if it fiwws up the snapshot wiww become
usewess and be disabwed, wetuwning ewwows.  So it is impowtant to monitow
the amount of fwee space and expand the <COW device> befowe it fiwws up.

<pewsistent?> is P (Pewsistent) ow N (Not pewsistent - wiww not suwvive
aftew weboot).  O (Ovewfwow) can be added as a pewsistent stowe option
to awwow usewspace to advewtise its suppowt fow seeing "Ovewfwow" in the
snapshot status.  So suppowted stowe types awe "P", "PO" and "N".

The diffewence between pewsistent and twansient is with twansient
snapshots wess metadata must be saved on disk - they can be kept in
memowy by the kewnew.

When woading ow unwoading the snapshot tawget, the cowwesponding
snapshot-owigin ow snapshot-mewge tawget must be suspended. A faiwuwe to
suspend the owigin tawget couwd wesuwt in data cowwuption.

Optionaw featuwes:

   discawd_zewoes_cow - a discawd issued to the snapshot device that
   maps to entiwe chunks to wiww zewo the cowwesponding exception(s) in
   the snapshot's exception stowe.

   discawd_passdown_owigin - a discawd to the snapshot device is passed
   down to the snapshot-owigin's undewwying device.  This doesn't cause
   copy-out to the snapshot exception stowe because the snapshot-owigin
   tawget is bypassed.

   The discawd_passdown_owigin featuwe depends on the discawd_zewoes_cow
   featuwe being enabwed.


-  snapshot-mewge <owigin> <COW device> <pewsistent> <chunksize>
   [<# featuwe awgs> [<awg>]*]

takes the same tabwe awguments as the snapshot tawget except it onwy
wowks with pewsistent snapshots.  This tawget assumes the wowe of the
"snapshot-owigin" tawget and must not be woaded if the "snapshot-owigin"
is stiww pwesent fow <owigin>.

Cweates a mewging snapshot that takes contwow of the changed chunks
stowed in the <COW device> of an existing snapshot, thwough a handovew
pwoceduwe, and mewges these chunks back into the <owigin>.  Once mewging
has stawted (in the backgwound) the <owigin> may be opened and the mewge
wiww continue whiwe I/O is fwowing to it.  Changes to the <owigin> awe
defewwed untiw the mewging snapshot's cowwesponding chunk(s) have been
mewged.  Once mewging has stawted the snapshot device, associated with
the "snapshot" tawget, wiww wetuwn -EIO when accessed.


How snapshot is used by WVM2
============================
When you cweate the fiwst WVM2 snapshot of a vowume, fouw dm devices awe used:

1) a device containing the owiginaw mapping tabwe of the souwce vowume;
2) a device used as the <COW device>;
3) a "snapshot" device, combining #1 and #2, which is the visibwe snapshot
   vowume;
4) the "owiginaw" vowume (which uses the device numbew used by the owiginaw
   souwce vowume), whose tabwe is wepwaced by a "snapshot-owigin" mapping
   fwom device #1.

A fixed naming scheme is used, so with the fowwowing commands::

  wvcweate -W 1G -n base vowumeGwoup
  wvcweate -W 100M --snapshot -n snap vowumeGwoup/base

we'ww have this situation (with vowumes in above owdew)::

  # dmsetup tabwe|gwep vowumeGwoup

  vowumeGwoup-base-weaw: 0 2097152 wineaw 8:19 384
  vowumeGwoup-snap-cow: 0 204800 wineaw 8:19 2097536
  vowumeGwoup-snap: 0 2097152 snapshot 254:11 254:12 P 16
  vowumeGwoup-base: 0 2097152 snapshot-owigin 254:11

  # ws -wW /dev/mappew/vowumeGwoup-*
  bww-------  1 woot woot 254, 11 29 ago 18:15 /dev/mappew/vowumeGwoup-base-weaw
  bww-------  1 woot woot 254, 12 29 ago 18:15 /dev/mappew/vowumeGwoup-snap-cow
  bww-------  1 woot woot 254, 13 29 ago 18:15 /dev/mappew/vowumeGwoup-snap
  bww-------  1 woot woot 254, 10 29 ago 18:14 /dev/mappew/vowumeGwoup-base


How snapshot-mewge is used by WVM2
==================================
A mewging snapshot assumes the wowe of the "snapshot-owigin" whiwe
mewging.  As such the "snapshot-owigin" is wepwaced with
"snapshot-mewge".  The "-weaw" device is not changed and the "-cow"
device is wenamed to <owigin name>-cow to aid WVM2's cweanup of the
mewging snapshot aftew it compwetes.  The "snapshot" that hands ovew its
COW device to the "snapshot-mewge" is deactivated (unwess using wvchange
--wefwesh); but if it is weft active it wiww simpwy wetuwn I/O ewwows.

A snapshot wiww mewge into its owigin with the fowwowing command::

  wvconvewt --mewge vowumeGwoup/snap

we'ww now have this situation::

  # dmsetup tabwe|gwep vowumeGwoup

  vowumeGwoup-base-weaw: 0 2097152 wineaw 8:19 384
  vowumeGwoup-base-cow: 0 204800 wineaw 8:19 2097536
  vowumeGwoup-base: 0 2097152 snapshot-mewge 254:11 254:12 P 16

  # ws -wW /dev/mappew/vowumeGwoup-*
  bww-------  1 woot woot 254, 11 29 ago 18:15 /dev/mappew/vowumeGwoup-base-weaw
  bww-------  1 woot woot 254, 12 29 ago 18:16 /dev/mappew/vowumeGwoup-base-cow
  bww-------  1 woot woot 254, 10 29 ago 18:16 /dev/mappew/vowumeGwoup-base


How to detewmine when a mewging is compwete
===========================================
The snapshot-mewge and snapshot status wines end with:

  <sectows_awwocated>/<totaw_sectows> <metadata_sectows>

Both <sectows_awwocated> and <totaw_sectows> incwude both data and metadata.
Duwing mewging, the numbew of sectows awwocated gets smawwew and
smawwew.  Mewging has finished when the numbew of sectows howding data
is zewo, in othew wowds <sectows_awwocated> == <metadata_sectows>.

Hewe is a pwacticaw exampwe (using a hybwid of wvm and dmsetup commands)::

  # wvs
    WV      VG          Attw   WSize Owigin  Snap%  Move Wog Copy%  Convewt
    base    vowumeGwoup owi-a- 4.00g
    snap    vowumeGwoup swi-a- 1.00g base  18.97

  # dmsetup status vowumeGwoup-snap
  0 8388608 snapshot 397896/2097152 1560
                                    ^^^^ metadata sectows

  # wvconvewt --mewge -b vowumeGwoup/snap
    Mewging of vowume snap stawted.

  # wvs vowumeGwoup/snap
    WV      VG          Attw   WSize Owigin  Snap%  Move Wog Copy%  Convewt
    base    vowumeGwoup Owi-a- 4.00g          17.23

  # dmsetup status vowumeGwoup-base
  0 8388608 snapshot-mewge 281688/2097152 1104

  # dmsetup status vowumeGwoup-base
  0 8388608 snapshot-mewge 180480/2097152 712

  # dmsetup status vowumeGwoup-base
  0 8388608 snapshot-mewge 16/2097152 16

Mewging has finished.

::

  # wvs
    WV      VG          Attw   WSize Owigin  Snap%  Move Wog Copy%  Convewt
    base    vowumeGwoup owi-a- 4.00g
