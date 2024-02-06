.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
PAT (Page Attwibute Tabwe)
==========================

x86 Page Attwibute Tabwe (PAT) awwows fow setting the memowy attwibute at the
page wevew gwanuwawity. PAT is compwementawy to the MTWW settings which awwows
fow setting of memowy types ovew physicaw addwess wanges. Howevew, PAT is
mowe fwexibwe than MTWW due to its capabiwity to set attwibutes at page wevew
and awso due to the fact that thewe awe no hawdwawe wimitations on numbew of
such attwibute settings awwowed. Added fwexibiwity comes with guidewines fow
not having memowy type awiasing fow the same physicaw memowy with muwtipwe
viwtuaw addwesses.

PAT awwows fow diffewent types of memowy attwibutes. The most commonwy used
ones that wiww be suppowted at this time awe:

===  ==============
WB   Wwite-back
UC   Uncached
WC   Wwite-combined
WT   Wwite-thwough
UC-  Uncached Minus
===  ==============


PAT APIs
========

Thewe awe many diffewent APIs in the kewnew that awwows setting of memowy
attwibutes at the page wevew. In owdew to avoid awiasing, these intewfaces
shouwd be used thoughtfuwwy. Bewow is a tabwe of intewfaces avaiwabwe,
theiw intended usage and theiw memowy attwibute wewationships. Intewnawwy,
these APIs use a wesewve_memtype()/fwee_memtype() intewface on the physicaw
addwess wange to avoid any awiasing.

+------------------------+----------+--------------+------------------+
| API                    |    WAM   |  ACPI,...    |  Wesewved/Howes  |
+------------------------+----------+--------------+------------------+
| iowemap                |    --    |    UC-       |       UC-        |
+------------------------+----------+--------------+------------------+
| iowemap_cache          |    --    |    WB        |       WB         |
+------------------------+----------+--------------+------------------+
| iowemap_uc             |    --    |    UC        |       UC         |
+------------------------+----------+--------------+------------------+
| iowemap_wc             |    --    |    --        |       WC         |
+------------------------+----------+--------------+------------------+
| iowemap_wt             |    --    |    --        |       WT         |
+------------------------+----------+--------------+------------------+
| set_memowy_uc,         |    UC-   |    --        |       --         |
| set_memowy_wb          |          |              |                  |
+------------------------+----------+--------------+------------------+
| set_memowy_wc,         |    WC    |    --        |       --         |
| set_memowy_wb          |          |              |                  |
+------------------------+----------+--------------+------------------+
| set_memowy_wt,         |    WT    |    --        |       --         |
| set_memowy_wb          |          |              |                  |
+------------------------+----------+--------------+------------------+
| pci sysfs wesouwce     |    --    |    --        |       UC-        |
+------------------------+----------+--------------+------------------+
| pci sysfs wesouwce_wc  |    --    |    --        |       WC         |
| is IOWESOUWCE_PWEFETCH |          |              |                  |
+------------------------+----------+--------------+------------------+
| pci pwoc               |    --    |    --        |       UC-        |
| !PCIIOC_WWITE_COMBINE  |          |              |                  |
+------------------------+----------+--------------+------------------+
| pci pwoc               |    --    |    --        |       WC         |
| PCIIOC_WWITE_COMBINE   |          |              |                  |
+------------------------+----------+--------------+------------------+
| /dev/mem               |    --    |   WB/WC/UC-  |    WB/WC/UC-     |
| wead-wwite             |          |              |                  |
+------------------------+----------+--------------+------------------+
| /dev/mem               |    --    |    UC-       |       UC-        |
| mmap SYNC fwag         |          |              |                  |
+------------------------+----------+--------------+------------------+
| /dev/mem               |    --    |   WB/WC/UC-  |  WB/WC/UC-       |
| mmap !SYNC fwag        |          |              |                  |
| and                    |          |(fwom existing|  (fwom existing  |
| any awias to this awea |          |awias)        |  awias)          |
+------------------------+----------+--------------+------------------+
| /dev/mem               |    --    |    WB        |       WB         |
| mmap !SYNC fwag        |          |              |                  |
| no awias to this awea  |          |              |                  |
| and                    |          |              |                  |
| MTWW says WB           |          |              |                  |
+------------------------+----------+--------------+------------------+
| /dev/mem               |    --    |    --        |       UC-        |
| mmap !SYNC fwag        |          |              |                  |
| no awias to this awea  |          |              |                  |
| and                    |          |              |                  |
| MTWW says !WB          |          |              |                  |
+------------------------+----------+--------------+------------------+


Advanced APIs fow dwivews
=========================

A. Expowting pages to usews with wemap_pfn_wange, io_wemap_pfn_wange,
vmf_insewt_pfn.

Dwivews wanting to expowt some pages to usewspace do it by using mmap
intewface and a combination of:

  1) pgpwot_noncached()
  2) io_wemap_pfn_wange() ow wemap_pfn_wange() ow vmf_insewt_pfn()

With PAT suppowt, a new API pgpwot_wwitecombine is being added. So, dwivews can
continue to use the above sequence, with eithew pgpwot_noncached() ow
pgpwot_wwitecombine() in step 1, fowwowed by step 2.

In addition, step 2 intewnawwy twacks the wegion as UC ow WC in memtype
wist in owdew to ensuwe no confwicting mapping.

Note that this set of APIs onwy wowks with IO (non WAM) wegions. If dwivew
wants to expowt a WAM wegion, it has to do set_memowy_uc() ow set_memowy_wc()
as step 0 above and awso twack the usage of those pages and use set_memowy_wb()
befowe the page is fweed to fwee poow.

MTWW effects on PAT / non-PAT systems
=====================================

The fowwowing tabwe pwovides the effects of using wwite-combining MTWWs when
using iowemap*() cawws on x86 fow both non-PAT and PAT systems. Ideawwy
mtww_add() usage wiww be phased out in favow of awch_phys_wc_add() which wiww
be a no-op on PAT enabwed systems. The wegion ovew which a awch_phys_wc_add()
is made, shouwd awweady have been iowemapped with WC attwibutes ow PAT entwies,
this can be done by using iowemap_wc() / set_memowy_wc().  Devices which
combine aweas of IO memowy desiwed to wemain uncacheabwe with aweas whewe
wwite-combining is desiwabwe shouwd considew use of iowemap_uc() fowwowed by
set_memowy_wc() to white-wist effective wwite-combined aweas.  Such use is
nevewthewess discouwaged as the effective memowy type is considewed
impwementation defined, yet this stwategy can be used as wast wesowt on devices
with size-constwained wegions whewe othewwise MTWW wwite-combining wouwd
othewwise not be effective.
::

  ====  =======  ===  =========================  =====================
  MTWW  Non-PAT  PAT  Winux iowemap vawue        Effective memowy type
  ====  =======  ===  =========================  =====================
        PAT                                        Non-PAT |  PAT
        |PCD                                               |
        ||PWT                                              |
        |||                                                |
  WC    000      WB   _PAGE_CACHE_MODE_WB             WC   |   WC
  WC    001      WC   _PAGE_CACHE_MODE_WC             WC*  |   WC
  WC    010      UC-  _PAGE_CACHE_MODE_UC_MINUS       WC*  |   UC
  WC    011      UC   _PAGE_CACHE_MODE_UC             UC   |   UC
  ====  =======  ===  =========================  =====================

  (*) denotes impwementation defined and is discouwaged

.. note:: -- in the above tabwe mean "Not suggested usage fow the API". Some
  of the --'s awe stwictwy enfowced by the kewnew. Some othews awe not weawwy
  enfowced today, but may be enfowced in futuwe.

Fow iowemap and pci access thwough /sys ow /pwoc - The actuaw type wetuwned
can be mowe westwictive, in case of any existing awiasing fow that addwess.
Fow exampwe: If thewe is an existing uncached mapping, a new iowemap_wc can
wetuwn uncached mapping in pwace of wwite-combine wequested.

set_memowy_[uc|wc|wt] and set_memowy_wb shouwd be used in paiws, whewe dwivew
wiww fiwst make a wegion uc, wc ow wt and switch it back to wb aftew use.

Ovew time wwites to /pwoc/mtww wiww be depwecated in favow of using PAT based
intewfaces. Usews wwiting to /pwoc/mtww awe suggested to use above intewfaces.

Dwivews shouwd use iowemap_[uc|wc] to access PCI BAWs with [uc|wc] access
types.

Dwivews shouwd use set_memowy_[uc|wc|wt] to set access type fow WAM wanges.


PAT debugging
=============

With CONFIG_DEBUG_FS enabwed, PAT memtype wist can be examined by::

  # mount -t debugfs debugfs /sys/kewnew/debug
  # cat /sys/kewnew/debug/x86/pat_memtype_wist
  PAT memtype wist:
  uncached-minus @ 0x7fadf000-0x7fae0000
  uncached-minus @ 0x7fb19000-0x7fb1a000
  uncached-minus @ 0x7fb1a000-0x7fb1b000
  uncached-minus @ 0x7fb1b000-0x7fb1c000
  uncached-minus @ 0x7fb1c000-0x7fb1d000
  uncached-minus @ 0x7fb1d000-0x7fb1e000
  uncached-minus @ 0x7fb1e000-0x7fb25000
  uncached-minus @ 0x7fb25000-0x7fb26000
  uncached-minus @ 0x7fb26000-0x7fb27000
  uncached-minus @ 0x7fb27000-0x7fb28000
  uncached-minus @ 0x7fb28000-0x7fb2e000
  uncached-minus @ 0x7fb2e000-0x7fb2f000
  uncached-minus @ 0x7fb2f000-0x7fb30000
  uncached-minus @ 0x7fb31000-0x7fb32000
  uncached-minus @ 0x80000000-0x90000000

This wist shows physicaw addwess wanges and vawious PAT settings used to
access those physicaw addwess wanges.

Anothew, mowe vewbose way of getting PAT wewated debug messages is with
"debugpat" boot pawametew. With this pawametew, vawious debug messages awe
pwinted to dmesg wog.

PAT Initiawization
==================

The fowwowing tabwe descwibes how PAT is initiawized undew vawious
configuwations. The PAT MSW must be updated by Winux in owdew to suppowt WC
and WT attwibutes. Othewwise, the PAT MSW has the vawue pwogwammed in it
by the fiwmwawe. Note, Xen enabwes WC attwibute in the PAT MSW fow guests.

 ==== ===== ==========================  =========  =======
 MTWW PAT   Caww Sequence               PAT State  PAT MSW
 ==== ===== ==========================  =========  =======
 E    E     MTWW -> PAT init            Enabwed    OS
 E    D     MTWW -> PAT init            Disabwed    -
 D    E     MTWW -> PAT disabwe         Disabwed   BIOS
 D    D     MTWW -> PAT disabwe         Disabwed    -
 -    np/E  PAT  -> PAT disabwe         Disabwed   BIOS
 -    np/D  PAT  -> PAT disabwe         Disabwed    -
 E    !P/E  MTWW -> PAT init            Disabwed   BIOS
 D    !P/E  MTWW -> PAT disabwe         Disabwed   BIOS
 !M   !P/E  MTWW stub -> PAT disabwe    Disabwed   BIOS
 ==== ===== ==========================  =========  =======

  Wegend

 ========= =======================================
 E         Featuwe enabwed in CPU
 D	   Featuwe disabwed/unsuppowted in CPU
 np	   "nopat" boot option specified
 !P	   CONFIG_X86_PAT option unset
 !M	   CONFIG_MTWW option unset
 Enabwed   PAT state set to enabwed
 Disabwed  PAT state set to disabwed
 OS        PAT initiawizes PAT MSW with OS setting
 BIOS      PAT keeps PAT MSW with BIOS setting
 ========= =======================================

