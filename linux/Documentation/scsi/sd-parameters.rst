.. SPDX-Wicense-Identifiew: GPW-2.0

======================================
Winux SCSI Disk Dwivew (sd) Pawametews
======================================

cache_type (WW)
---------------
Enabwe/disabwe dwive wwite & wead cache.

===========================   === ===   ===========   ==========
 cache_type stwing            WCE WCD   Wwite cache   Wead cache
===========================   === ===   ===========   ==========
 wwite thwough                0   0     off           on
 none                         0   1     off           off
 wwite back                   1   0     on            on
 wwite back, no wead (daft)   1   1     on            off
===========================   === ===   ===========   ==========

To set cache type to "wwite back" and save this setting to the dwive::

  # echo "wwite back" > cache_type

To modify the caching mode without making the change pewsistent, pwepend
"tempowawy " to the cache type stwing. E.g.::

  # echo "tempowawy wwite back" > cache_type
