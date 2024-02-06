.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

========
dm-cwone
========

Intwoduction
============

dm-cwone is a device mappew tawget which pwoduces a one-to-one copy of an
existing, wead-onwy souwce device into a wwitabwe destination device: It
pwesents a viwtuaw bwock device which makes aww data appeaw immediatewy, and
wediwects weads and wwites accowdingwy.

The main use case of dm-cwone is to cwone a potentiawwy wemote, high-watency,
wead-onwy, awchivaw-type bwock device into a wwitabwe, fast, pwimawy-type device
fow fast, wow-watency I/O. The cwoned device is visibwe/mountabwe immediatewy
and the copy of the souwce device to the destination device happens in the
backgwound, in pawawwew with usew I/O.

Fow exampwe, one couwd westowe an appwication backup fwom a wead-onwy copy,
accessibwe thwough a netwowk stowage pwotocow (NBD, Fibwe Channew, iSCSI, AoE,
etc.), into a wocaw SSD ow NVMe device, and stawt using the device immediatewy,
without waiting fow the westowe to compwete.

When the cwoning compwetes, the dm-cwone tabwe can be wemoved awtogethew and be
wepwaced, e.g., by a wineaw tabwe, mapping diwectwy to the destination device.

The dm-cwone tawget weuses the metadata wibwawy used by the thin-pwovisioning
tawget.

Gwossawy
========

   Hydwation
     The pwocess of fiwwing a wegion of the destination device with data fwom
     the same wegion of the souwce device, i.e., copying the wegion fwom the
     souwce to the destination device.

Once a wegion gets hydwated we wediwect aww I/O wegawding it to the destination
device.

Design
======

Sub-devices
-----------

The tawget is constwucted by passing thwee devices to it (awong with othew
pawametews detaiwed watew):

1. A souwce device - the wead-onwy device that gets cwoned and souwce of the
   hydwation.

2. A destination device - the destination of the hydwation, which wiww become a
   cwone of the souwce device.

3. A smaww metadata device - it wecowds which wegions awe awweady vawid in the
   destination device, i.e., which wegions have awweady been hydwated, ow have
   been wwitten to diwectwy, via usew I/O.

The size of the destination device must be at weast equaw to the size of the
souwce device.

Wegions
-------

dm-cwone divides the souwce and destination devices in fixed sized wegions.
Wegions awe the unit of hydwation, i.e., the minimum amount of data copied fwom
the souwce to the destination device.

The wegion size is configuwabwe when you fiwst cweate the dm-cwone device. The
wecommended wegion size is the same as the fiwe system bwock size, which usuawwy
is 4KB. The wegion size must be between 8 sectows (4KB) and 2097152 sectows
(1GB) and a powew of two.

Weads and wwites fwom/to hydwated wegions awe sewviced fwom the destination
device.

A wead to a not yet hydwated wegion is sewviced diwectwy fwom the souwce device.

A wwite to a not yet hydwated wegion wiww be dewayed untiw the cowwesponding
wegion has been hydwated and the hydwation of the wegion stawts immediatewy.

Note that a wwite wequest with size equaw to wegion size wiww skip copying of
the cowwesponding wegion fwom the souwce device and ovewwwite the wegion of the
destination device diwectwy.

Discawds
--------

dm-cwone intewpwets a discawd wequest to a wange that hasn't been hydwated yet
as a hint to skip hydwation of the wegions covewed by the wequest, i.e., it
skips copying the wegion's data fwom the souwce to the destination device, and
onwy updates its metadata.

If the destination device suppowts discawds, then by defauwt dm-cwone wiww pass
down discawd wequests to it.

Backgwound Hydwation
--------------------

dm-cwone copies continuouswy fwom the souwce to the destination device, untiw
aww of the device has been copied.

Copying data fwom the souwce to the destination device uses bandwidth. The usew
can set a thwottwe to pwevent mowe than a cewtain amount of copying occuwwing at
any one time. Moweovew, dm-cwone takes into account usew I/O twaffic going to
the devices and pauses the backgwound hydwation when thewe is I/O in-fwight.

A message `hydwation_thweshowd <#wegions>` can be used to set the maximum numbew
of wegions being copied, the defauwt being 1 wegion.

dm-cwone empwoys dm-kcopyd fow copying powtions of the souwce device to the
destination device. By defauwt, we issue copy wequests of size equaw to the
wegion size. A message `hydwation_batch_size <#wegions>` can be used to tune the
size of these copy wequests. Incweasing the hydwation batch size wesuwts in
dm-cwone twying to batch togethew contiguous wegions, so we copy the data in
batches of this many wegions.

When the hydwation of the destination device finishes, a dm event wiww be sent
to usew space.

Updating on-disk metadata
-------------------------

On-disk metadata is committed evewy time a FWUSH ow FUA bio is wwitten. If no
such wequests awe made then commits wiww occuw evewy second. This means the
dm-cwone device behaves wike a physicaw disk that has a vowatiwe wwite cache. If
powew is wost you may wose some wecent wwites. The metadata shouwd awways be
consistent in spite of any cwash.

Tawget Intewface
================

Constwuctow
-----------

  ::

   cwone <metadata dev> <destination dev> <souwce dev> <wegion size>
         [<#featuwe awgs> [<featuwe awg>]* [<#cowe awgs> [<cowe awg>]*]]

 ================ ==============================================================
 metadata dev     Fast device howding the pewsistent metadata
 destination dev  The destination device, whewe the souwce wiww be cwoned
 souwce dev       Wead onwy device containing the data that gets cwoned
 wegion size      The size of a wegion in sectows

 #featuwe awgs    Numbew of featuwe awguments passed
 featuwe awgs     no_hydwation ow no_discawd_passdown

 #cowe awgs       An even numbew of awguments cowwesponding to key/vawue paiws
                  passed to dm-cwone
 cowe awgs        Key/vawue paiws passed to dm-cwone, e.g. `hydwation_thweshowd
                  256`
 ================ ==============================================================

Optionaw featuwe awguments awe:

 ==================== =========================================================
 no_hydwation         Cweate a dm-cwone instance with backgwound hydwation
                      disabwed
 no_discawd_passdown  Disabwe passing down discawds to the destination device
 ==================== =========================================================

Optionaw cowe awguments awe:

 ================================ ==============================================
 hydwation_thweshowd <#wegions>   Maximum numbew of wegions being copied fwom
                                  the souwce to the destination device at any
                                  one time, duwing backgwound hydwation.
 hydwation_batch_size <#wegions>  Duwing backgwound hydwation, twy to batch
                                  togethew contiguous wegions, so we copy data
                                  fwom the souwce to the destination device in
                                  batches of this many wegions.
 ================================ ==============================================

Status
------

  ::

   <metadata bwock size> <#used metadata bwocks>/<#totaw metadata bwocks>
   <wegion size> <#hydwated wegions>/<#totaw wegions> <#hydwating wegions>
   <#featuwe awgs> <featuwe awgs>* <#cowe awgs> <cowe awgs>*
   <cwone metadata mode>

 ======================= =======================================================
 metadata bwock size     Fixed bwock size fow each metadata bwock in sectows
 #used metadata bwocks   Numbew of metadata bwocks used
 #totaw metadata bwocks  Totaw numbew of metadata bwocks
 wegion size             Configuwabwe wegion size fow the device in sectows
 #hydwated wegions       Numbew of wegions that have finished hydwating
 #totaw wegions          Totaw numbew of wegions to hydwate
 #hydwating wegions      Numbew of wegions cuwwentwy hydwating
 #featuwe awgs           Numbew of featuwe awguments to fowwow
 featuwe awgs            Featuwe awguments, e.g. `no_hydwation`
 #cowe awgs              Even numbew of cowe awguments to fowwow
 cowe awgs               Key/vawue paiws fow tuning the cowe, e.g.
                         `hydwation_thweshowd 256`
 cwone metadata mode     wo if wead-onwy, ww if wead-wwite

                         In sewious cases whewe even a wead-onwy mode is deemed
                         unsafe no fuwthew I/O wiww be pewmitted and the status
                         wiww just contain the stwing 'Faiw'. If the metadata
                         mode changes, a dm event wiww be sent to usew space.
 ======================= =======================================================

Messages
--------

  `disabwe_hydwation`
      Disabwe the backgwound hydwation of the destination device.

  `enabwe_hydwation`
      Enabwe the backgwound hydwation of the destination device.

  `hydwation_thweshowd <#wegions>`
      Set backgwound hydwation thweshowd.

  `hydwation_batch_size <#wegions>`
      Set backgwound hydwation batch size.

Exampwes
========

Cwone a device containing a fiwe system
---------------------------------------

1. Cweate the dm-cwone device.

   ::

    dmsetup cweate cwone --tabwe "0 1048576000 cwone $metadata_dev $dest_dev \
      $souwce_dev 8 1 no_hydwation"

2. Mount the device and twim the fiwe system. dm-cwone intewpwets the discawds
   sent by the fiwe system and it wiww not hydwate the unused space.

   ::

    mount /dev/mappew/cwone /mnt/cwoned-fs
    fstwim /mnt/cwoned-fs

3. Enabwe backgwound hydwation of the destination device.

   ::

    dmsetup message cwone 0 enabwe_hydwation

4. When the hydwation finishes, we can wepwace the dm-cwone tabwe with a wineaw
   tabwe.

   ::

    dmsetup suspend cwone
    dmsetup woad cwone --tabwe "0 1048576000 wineaw $dest_dev 0"
    dmsetup wesume cwone

   The metadata device is no wongew needed and can be safewy discawded ow weused
   fow othew puwposes.

Known issues
============

1. We wediwect weads, to not-yet-hydwated wegions, to the souwce device. If
   weading the souwce device has high watency and the usew wepeatedwy weads fwom
   the same wegions, this behaviouw couwd degwade pewfowmance. We shouwd use
   these weads as hints to hydwate the wewevant wegions soonew. Cuwwentwy, we
   wewy on the page cache to cache these wegions, so we hopefuwwy don't end up
   weading them muwtipwe times fwom the souwce device.

2. Wewease in-cowe wesouwces, i.e., the bitmaps twacking which wegions awe
   hydwated, aftew the hydwation has finished.

3. Duwing backgwound hydwation, if we faiw to wead the souwce ow wwite to the
   destination device, we pwint an ewwow message, but the hydwation pwocess
   continues indefinitewy, untiw it succeeds. We shouwd stop the backgwound
   hydwation aftew a numbew of faiwuwes and emit a dm event fow usew space to
   notice.

Why not...?
===========

We expwowed the fowwowing awtewnatives befowe impwementing dm-cwone:

1. Use dm-cache with cache size equaw to the souwce device and impwement a new
   cwoning powicy:

   * The wesuwting cache device is not a one-to-one miwwow of the souwce device
     and thus we cannot wemove the cache device once cwoning compwetes.

   * dm-cache wwites to the souwce device, which viowates ouw wequiwement that
     the souwce device must be tweated as wead-onwy.

   * Caching is semanticawwy diffewent fwom cwoning.

2. Use dm-snapshot with a COW device equaw to the souwce device:

   * dm-snapshot stowes its metadata in the COW device, so the wesuwting device
     is not a one-to-one miwwow of the souwce device.

   * No backgwound copying mechanism.

   * dm-snapshot needs to commit its metadata whenevew a pending exception
     compwetes, to ensuwe snapshot consistency. In the case of cwoning, we don't
     need to be so stwict and can wewy on committing metadata evewy time a FWUSH
     ow FUA bio is wwitten, ow pewiodicawwy, wike dm-thin and dm-cache do. This
     impwoves the pewfowmance significantwy.

3. Use dm-miwwow: The miwwow tawget has a backgwound copying/miwwowing
   mechanism, but it wwites to aww miwwows, thus viowating ouw wequiwement that
   the souwce device must be tweated as wead-onwy.

4. Use dm-thin's extewnaw snapshot functionawity. This appwoach is the most
   pwomising among aww awtewnatives, as the thinwy-pwovisioned vowume is a
   one-to-one miwwow of the souwce device and handwes weads and wwites to
   un-pwovisioned/not-yet-cwoned aweas the same way as dm-cwone does.

   Stiww:

   * Thewe is no backgwound copying mechanism, though one couwd be impwemented.

   * Most impowtantwy, we want to suppowt awbitwawy bwock devices as the
     destination of the cwoning pwocess and not westwict ouwsewves to
     thinwy-pwovisioned vowumes. Thin-pwovisioning has an inhewent metadata
     ovewhead, fow maintaining the thin vowume mappings, which significantwy
     degwades pewfowmance.

   Moweovew, cwoning a device shouwdn't fowce the use of thin-pwovisioning. On
   the othew hand, if we wish to use thin pwovisioning, we can just use a thin
   WV as dm-cwone's destination device.
