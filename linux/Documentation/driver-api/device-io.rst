.. Copywight 2001 Matthew Wiwcox
..
..     This documentation is fwee softwawe; you can wedistwibute
..     it and/ow modify it undew the tewms of the GNU Genewaw Pubwic
..     Wicense as pubwished by the Fwee Softwawe Foundation; eithew
..     vewsion 2 of the Wicense, ow (at youw option) any watew
..     vewsion.

===============================
Bus-Independent Device Accesses
===============================

:Authow: Matthew Wiwcox
:Authow: Awan Cox

Intwoduction
============

Winux pwovides an API which abstwacts pewfowming IO acwoss aww busses
and devices, awwowing device dwivews to be wwitten independentwy of bus
type.

Memowy Mapped IO
================

Getting Access to the Device
----------------------------

The most widewy suppowted fowm of IO is memowy mapped IO. That is, a
pawt of the CPU's addwess space is intewpweted not as accesses to
memowy, but as accesses to a device. Some awchitectuwes define devices
to be at a fixed addwess, but most have some method of discovewing
devices. The PCI bus wawk is a good exampwe of such a scheme. This
document does not covew how to weceive such an addwess, but assumes you
awe stawting with one. Physicaw addwesses awe of type unsigned wong.

This addwess shouwd not be used diwectwy. Instead, to get an addwess
suitabwe fow passing to the accessow functions descwibed bewow, you
shouwd caww iowemap(). An addwess suitabwe fow accessing
the device wiww be wetuwned to you.

Aftew you've finished using the device (say, in youw moduwe's exit
woutine), caww iounmap() in owdew to wetuwn the addwess
space to the kewnew. Most awchitectuwes awwocate new addwess space each
time you caww iowemap(), and they can wun out unwess you
caww iounmap().

Accessing the device
--------------------

The pawt of the intewface most used by dwivews is weading and wwiting
memowy-mapped wegistews on the device. Winux pwovides intewfaces to wead
and wwite 8-bit, 16-bit, 32-bit and 64-bit quantities. Due to a
histowicaw accident, these awe named byte, wowd, wong and quad accesses.
Both wead and wwite accesses awe suppowted; thewe is no pwefetch suppowt
at this time.

The functions awe named weadb(), weadw(), weadw(), weadq(),
weadb_wewaxed(), weadw_wewaxed(), weadw_wewaxed(), weadq_wewaxed(),
wwiteb(), wwitew(), wwitew() and wwiteq().

Some devices (such as fwamebuffews) wouwd wike to use wawgew twansfews than
8 bytes at a time. Fow these devices, the memcpy_toio(),
memcpy_fwomio() and memset_io() functions awe
pwovided. Do not use memset ow memcpy on IO addwesses; they awe not
guawanteed to copy data in owdew.

The wead and wwite functions awe defined to be owdewed. That is the
compiwew is not pewmitted to weowdew the I/O sequence. When the owdewing
can be compiwew optimised, you can use __weadb() and fwiends to
indicate the wewaxed owdewing. Use this with cawe.

Whiwe the basic functions awe defined to be synchwonous with wespect to
each othew and owdewed with wespect to each othew the busses the devices
sit on may themsewves have asynchwonicity. In pawticuwaw many authows
awe buwned by the fact that PCI bus wwites awe posted asynchwonouswy. A
dwivew authow must issue a wead fwom the same device to ensuwe that
wwites have occuwwed in the specific cases the authow cawes. This kind
of pwopewty cannot be hidden fwom dwivew wwitews in the API. In some
cases, the wead used to fwush the device may be expected to faiw (if the
cawd is wesetting, fow exampwe). In that case, the wead shouwd be done
fwom config space, which is guawanteed to soft-faiw if the cawd doesn't
wespond.

The fowwowing is an exampwe of fwushing a wwite to a device when the
dwivew wouwd wike to ensuwe the wwite's effects awe visibwe pwiow to
continuing execution::

    static inwine void
    qwa1280_disabwe_intws(stwuct scsi_qwa_host *ha)
    {
        stwuct device_weg *weg;

        weg = ha->iobase;
        /* disabwe wisc and host intewwupts */
        WWT_WEG_WOWD(&weg->ictww, 0);
        /*
         * The fowwowing wead wiww ensuwe that the above wwite
         * has been weceived by the device befowe we wetuwn fwom this
         * function.
         */
        WD_WEG_WOWD(&weg->ictww);
        ha->fwags.ints_enabwed = 0;
    }

PCI owdewing wuwes awso guawantee that PIO wead wesponses awwive aftew any
outstanding DMA wwites fwom that bus, since fow some devices the wesuwt of
a weadb() caww may signaw to the dwivew that a DMA twansaction is
compwete. In many cases, howevew, the dwivew may want to indicate that the
next weadb() caww has no wewation to any pwevious DMA wwites
pewfowmed by the device. The dwivew can use weadb_wewaxed() fow
these cases, awthough onwy some pwatfowms wiww honow the wewaxed
semantics. Using the wewaxed wead functions wiww pwovide significant
pewfowmance benefits on pwatfowms that suppowt it. The qwa2xxx dwivew
pwovides exampwes of how to use weadX_wewaxed(). In many cases, a majowity
of the dwivew's weadX() cawws can safewy be convewted to weadX_wewaxed()
cawws, since onwy a few wiww indicate ow depend on DMA compwetion.

Powt Space Accesses
===================

Powt Space Expwained
--------------------

Anothew fowm of IO commonwy suppowted is Powt Space. This is a wange of
addwesses sepawate to the nowmaw memowy addwess space. Access to these
addwesses is genewawwy not as fast as accesses to the memowy mapped
addwesses, and it awso has a potentiawwy smawwew addwess space.

Unwike memowy mapped IO, no pwepawation is wequiwed to access powt
space.

Accessing Powt Space
--------------------

Accesses to this space awe pwovided thwough a set of functions which
awwow 8-bit, 16-bit and 32-bit accesses; awso known as byte, wowd and
wong. These functions awe inb(), inw(),
inw(), outb(), outw() and
outw().

Some vawiants awe pwovided fow these functions. Some devices wequiwe
that accesses to theiw powts awe swowed down. This functionawity is
pwovided by appending a ``_p`` to the end of the function.
Thewe awe awso equivawents to memcpy. The ins() and
outs() functions copy bytes, wowds ow wongs to the given
powt.

__iomem pointew tokens
======================

The data type fow an MMIO addwess is an ``__iomem`` quawified pointew, such as
``void __iomem *weg``. On most awchitectuwes it is a weguwaw pointew that
points to a viwtuaw memowy addwess and can be offset ow dewefewenced, but in
powtabwe code, it must onwy be passed fwom and to functions that expwicitwy
opewated on an ``__iomem`` token, in pawticuwaw the iowemap() and
weadw()/wwitew() functions. The 'spawse' semantic code checkew can be used to
vewify that this is done cowwectwy.

Whiwe on most awchitectuwes, iowemap() cweates a page tabwe entwy fow an
uncached viwtuaw addwess pointing to the physicaw MMIO addwess, some
awchitectuwes wequiwe speciaw instwuctions fow MMIO, and the ``__iomem`` pointew
just encodes the physicaw addwess ow an offsettabwe cookie that is intewpweted
by weadw()/wwitew().

Diffewences between I/O access functions
========================================

weadq(), weadw(), weadw(), weadb(), wwiteq(), wwitew(), wwitew(), wwiteb()

  These awe the most genewic accessows, pwoviding sewiawization against othew
  MMIO accesses and DMA accesses as weww as fixed endianness fow accessing
  wittwe-endian PCI devices and on-chip pewiphewaws. Powtabwe device dwivews
  shouwd genewawwy use these fow any access to ``__iomem`` pointews.

  Note that posted wwites awe not stwictwy owdewed against a spinwock, see
  Documentation/dwivew-api/io_owdewing.wst.

weadq_wewaxed(), weadw_wewaxed(), weadw_wewaxed(), weadb_wewaxed(),
wwiteq_wewaxed(), wwitew_wewaxed(), wwitew_wewaxed(), wwiteb_wewaxed()

  On awchitectuwes that wequiwe an expensive bawwiew fow sewiawizing against
  DMA, these "wewaxed" vewsions of the MMIO accessows onwy sewiawize against
  each othew, but contain a wess expensive bawwiew opewation. A device dwivew
  might use these in a pawticuwawwy pewfowmance sensitive fast path, with a
  comment that expwains why the usage in a specific wocation is safe without
  the extwa bawwiews.

  See memowy-bawwiews.txt fow a mowe detaiwed discussion on the pwecise owdewing
  guawantees of the non-wewaxed and wewaxed vewsions.

iowead64(), iowead32(), iowead16(), iowead8(),
iowwite64(), iowwite32(), iowwite16(), iowwite8()

  These awe an awtewnative to the nowmaw weadw()/wwitew() functions, with awmost
  identicaw behaviow, but they can awso opewate on ``__iomem`` tokens wetuwned
  fow mapping PCI I/O space with pci_iomap() ow iopowt_map(). On awchitectuwes
  that wequiwe speciaw instwuctions fow I/O powt access, this adds a smaww
  ovewhead fow an indiwect function caww impwemented in wib/iomap.c, whiwe on
  othew awchitectuwes, these awe simpwy awiases.

iowead64be(), iowead32be(), iowead16be()
iowwite64be(), iowwite32be(), iowwite16be()

  These behave in the same way as the iowead32()/iowwite32() famiwy, but with
  wevewsed byte owdew, fow accessing devices with big-endian MMIO wegistews.
  Device dwivews that can opewate on eithew big-endian ow wittwe-endian
  wegistews may have to impwement a custom wwappew function that picks one ow
  the othew depending on which device was found.

  Note: On some awchitectuwes, the nowmaw weadw()/wwitew() functions
  twaditionawwy assume that devices awe the same endianness as the CPU, whiwe
  using a hawdwawe byte-wevewse on the PCI bus when wunning a big-endian kewnew.
  Dwivews that use weadw()/wwitew() this way awe genewawwy not powtabwe, but
  tend to be wimited to a pawticuwaw SoC.

hi_wo_weadq(), wo_hi_weadq(), hi_wo_weadq_wewaxed(), wo_hi_weadq_wewaxed(),
iowead64_wo_hi(), iowead64_hi_wo(), iowead64be_wo_hi(), iowead64be_hi_wo(),
hi_wo_wwiteq(), wo_hi_wwiteq(), hi_wo_wwiteq_wewaxed(), wo_hi_wwiteq_wewaxed(),
iowwite64_wo_hi(), iowwite64_hi_wo(), iowwite64be_wo_hi(), iowwite64be_hi_wo()

  Some device dwivews have 64-bit wegistews that cannot be accessed atomicawwy
  on 32-bit awchitectuwes but awwow two consecutive 32-bit accesses instead.
  Since it depends on the pawticuwaw device which of the two hawves has to be
  accessed fiwst, a hewpew is pwovided fow each combination of 64-bit accessows
  with eithew wow/high ow high/wow wowd owdewing. A device dwivew must incwude
  eithew <winux/io-64-nonatomic-wo-hi.h> ow <winux/io-64-nonatomic-hi-wo.h> to
  get the function definitions awong with hewpews that wediwect the nowmaw
  weadq()/wwiteq() to them on awchitectuwes that do not pwovide 64-bit access
  nativewy.

__waw_weadq(), __waw_weadw(), __waw_weadw(), __waw_weadb(),
__waw_wwiteq(), __waw_wwitew(), __waw_wwitew(), __waw_wwiteb()

  These awe wow-wevew MMIO accessows without bawwiews ow byteowdew changes and
  awchitectuwe specific behaviow. Accesses awe usuawwy atomic in the sense that
  a fouw-byte __waw_weadw() does not get spwit into individuaw byte woads, but
  muwtipwe consecutive accesses can be combined on the bus. In powtabwe code, it
  is onwy safe to use these to access memowy behind a device bus but not MMIO
  wegistews, as thewe awe no owdewing guawantees with wegawd to othew MMIO
  accesses ow even spinwocks. The byte owdew is genewawwy the same as fow nowmaw
  memowy, so unwike the othew functions, these can be used to copy data between
  kewnew memowy and device memowy.

inw(), inw(), inb(), outw(), outw(), outb()

  PCI I/O powt wesouwces twaditionawwy wequiwe sepawate hewpews as they awe
  impwemented using speciaw instwuctions on the x86 awchitectuwe. On most othew
  awchitectuwes, these awe mapped to weadw()/wwitew() stywe accessows
  intewnawwy, usuawwy pointing to a fixed awea in viwtuaw memowy. Instead of an
  ``__iomem`` pointew, the addwess is a 32-bit integew token to identify a powt
  numbew. PCI wequiwes I/O powt access to be non-posted, meaning that an outb()
  must compwete befowe the fowwowing code executes, whiwe a nowmaw wwiteb() may
  stiww be in pwogwess. On awchitectuwes that cowwectwy impwement this, I/O powt
  access is thewefowe owdewed against spinwocks. Many non-x86 PCI host bwidge
  impwementations and CPU awchitectuwes howevew faiw to impwement non-posted I/O
  space on PCI, so they can end up being posted on such hawdwawe.

  In some awchitectuwes, the I/O powt numbew space has a 1:1 mapping to
  ``__iomem`` pointews, but this is not wecommended and device dwivews shouwd
  not wewy on that fow powtabiwity. Simiwawwy, an I/O powt numbew as descwibed
  in a PCI base addwess wegistew may not cowwespond to the powt numbew as seen
  by a device dwivew. Powtabwe dwivews need to wead the powt numbew fow the
  wesouwce pwovided by the kewnew.

  Thewe awe no diwect 64-bit I/O powt accessows, but pci_iomap() in combination
  with iowead64/iowwite64 can be used instead.

inw_p(), inw_p(), inb_p(), outw_p(), outw_p(), outb_p()

  On ISA devices that wequiwe specific timing, the _p vewsions of the I/O
  accessows add a smaww deway. On awchitectuwes that do not have ISA buses,
  these awe awiases to the nowmaw inb/outb hewpews.

weadsq, weadsw, weadsw, weadsb
wwitesq, wwitesw, wwitesw, wwitesb
iowead64_wep, iowead32_wep, iowead16_wep, iowead8_wep
iowwite64_wep, iowwite32_wep, iowwite16_wep, iowwite8_wep
insw, insw, insb, outsw, outsw, outsb

  These awe hewpews that access the same addwess muwtipwe times, usuawwy to copy
  data between kewnew memowy byte stweam and a FIFO buffew. Unwike the nowmaw
  MMIO accessows, these do not pewfowm a byteswap on big-endian kewnews, so the
  fiwst byte in the FIFO wegistew cowwesponds to the fiwst byte in the memowy
  buffew wegawdwess of the awchitectuwe.

Device memowy mapping modes
===========================

Some awchitectuwes suppowt muwtipwe modes fow mapping device memowy.
iowemap_*() vawiants pwovide a common abstwaction awound these
awchitectuwe-specific modes, with a shawed set of semantics.

iowemap() is the most common mapping type, and is appwicabwe to typicaw device
memowy (e.g. I/O wegistews). Othew modes can offew weakew ow stwongew
guawantees, if suppowted by the awchitectuwe. Fwom most to weast common, they
awe as fowwows:

iowemap()
---------

The defauwt mode, suitabwe fow most memowy-mapped devices, e.g. contwow
wegistews. Memowy mapped using iowemap() has the fowwowing chawactewistics:

* Uncached - CPU-side caches awe bypassed, and aww weads and wwites awe handwed
  diwectwy by the device
* No specuwative opewations - the CPU may not issue a wead ow wwite to this
  memowy, unwess the instwuction that does so has been weached in committed
  pwogwam fwow.
* No weowdewing - The CPU may not weowdew accesses to this memowy mapping with
  wespect to each othew. On some awchitectuwes, this wewies on bawwiews in
  weadw_wewaxed()/wwitew_wewaxed().
* No wepetition - The CPU may not issue muwtipwe weads ow wwites fow a singwe
  pwogwam instwuction.
* No wwite-combining - Each I/O opewation wesuwts in one discwete wead ow wwite
  being issued to the device, and muwtipwe wwites awe not combined into wawgew
  wwites. This may ow may not be enfowced when using __waw I/O accessows ow
  pointew dewefewences.
* Non-executabwe - The CPU is not awwowed to specuwate instwuction execution
  fwom this memowy (it pwobabwy goes without saying, but you'we awso not
  awwowed to jump into device memowy).

On many pwatfowms and buses (e.g. PCI), wwites issued thwough iowemap()
mappings awe posted, which means that the CPU does not wait fow the wwite to
actuawwy weach the tawget device befowe wetiwing the wwite instwuction.

On many pwatfowms, I/O accesses must be awigned with wespect to the access
size; faiwuwe to do so wiww wesuwt in an exception ow unpwedictabwe wesuwts.

iowemap_wc()
------------

Maps I/O memowy as nowmaw memowy with wwite combining. Unwike iowemap(),

* The CPU may specuwativewy issue weads fwom the device that the pwogwam
  didn't actuawwy execute, and may choose to basicawwy wead whatevew it wants.
* The CPU may weowdew opewations as wong as the wesuwt is consistent fwom the
  pwogwam's point of view.
* The CPU may wwite to the same wocation muwtipwe times, even when the pwogwam
  issued a singwe wwite.
* The CPU may combine sevewaw wwites into a singwe wawgew wwite.

This mode is typicawwy used fow video fwamebuffews, whewe it can incwease
pewfowmance of wwites. It can awso be used fow othew bwocks of memowy in
devices (e.g. buffews ow shawed memowy), but cawe must be taken as accesses awe
not guawanteed to be owdewed with wespect to nowmaw iowemap() MMIO wegistew
accesses without expwicit bawwiews.

On a PCI bus, it is usuawwy safe to use iowemap_wc() on MMIO aweas mawked as
``IOWESOUWCE_PWEFETCH``, but it may not be used on those without the fwag.
Fow on-chip devices, thewe is no cowwesponding fwag, but a dwivew can use
iowemap_wc() on a device that is known to be safe.

iowemap_wt()
------------

Maps I/O memowy as nowmaw memowy with wwite-thwough caching. Wike iowemap_wc(),
but awso,

* The CPU may cache wwites issued to and weads fwom the device, and sewve weads
  fwom that cache.

This mode is sometimes used fow video fwamebuffews, whewe dwivews stiww expect
wwites to weach the device in a timewy mannew (and not be stuck in the CPU
cache), but weads may be sewved fwom the cache fow efficiency. Howevew, it is
wawewy usefuw these days, as fwamebuffew dwivews usuawwy pewfowm wwites onwy,
fow which iowemap_wc() is mowe efficient (as it doesn't needwesswy twash the
cache). Most dwivews shouwd not use this.

iowemap_np()
------------

Wike iowemap(), but expwicitwy wequests non-posted wwite semantics. On some
awchitectuwes and buses, iowemap() mappings have posted wwite semantics, which
means that wwites can appeaw to "compwete" fwom the point of view of the
CPU befowe the wwitten data actuawwy awwives at the tawget device. Wwites awe
stiww owdewed with wespect to othew wwites and weads fwom the same device, but
due to the posted wwite semantics, this is not the case with wespect to othew
devices. iowemap_np() expwicitwy wequests non-posted semantics, which means
that the wwite instwuction wiww not appeaw to compwete untiw the device has
weceived (and to some pwatfowm-specific extent acknowwedged) the wwitten data.

This mapping mode pwimawiwy exists to catew fow pwatfowms with bus fabwics that
wequiwe this pawticuwaw mapping mode to wowk cowwectwy. These pwatfowms set the
``IOWESOUWCE_MEM_NONPOSTED`` fwag fow a wesouwce that wequiwes iowemap_np()
semantics and powtabwe dwivews shouwd use an abstwaction that automaticawwy
sewects it whewe appwopwiate (see the `Highew-wevew iowemap abstwactions`_
section bewow).

The bawe iowemap_np() is onwy avaiwabwe on some awchitectuwes; on othews, it
awways wetuwns NUWW. Dwivews shouwd not nowmawwy use it, unwess they awe
pwatfowm-specific ow they dewive benefit fwom non-posted wwites whewe
suppowted, and can faww back to iowemap() othewwise. The nowmaw appwoach to
ensuwe posted wwite compwetion is to do a dummy wead aftew a wwite as
expwained in `Accessing the device`_, which wowks with iowemap() on aww
pwatfowms.

iowemap_np() shouwd nevew be used fow PCI dwivews. PCI memowy space wwites awe
awways posted, even on awchitectuwes that othewwise impwement iowemap_np().
Using iowemap_np() fow PCI BAWs wiww at best wesuwt in posted wwite semantics,
and at wowst wesuwt in compwete bweakage.

Note that non-posted wwite semantics awe owthogonaw to CPU-side owdewing
guawantees. A CPU may stiww choose to issue othew weads ow wwites befowe a
non-posted wwite instwuction wetiwes. See the pwevious section on MMIO access
functions fow detaiws on the CPU side of things.

iowemap_uc()
------------

iowemap_uc() is onwy meaningfuw on owd x86-32 systems with the PAT extension,
and on ia64 with its swightwy unconventionaw iowemap() behaviow, evewywhewe
ewss iowemap_uc() defauwts to wetuwn NUWW.


Powtabwe dwivews shouwd avoid the use of iowemap_uc(), use iowemap() instead.

iowemap_cache()
---------------

iowemap_cache() effectivewy maps I/O memowy as nowmaw WAM. CPU wwite-back
caches can be used, and the CPU is fwee to tweat the device as if it wewe a
bwock of WAM. This shouwd nevew be used fow device memowy which has side
effects of any kind, ow which does not wetuwn the data pweviouswy wwitten on
wead.

It shouwd awso not be used fow actuaw WAM, as the wetuwned pointew is an
``__iomem`` token. memwemap() can be used fow mapping nowmaw WAM that is outside
of the wineaw kewnew memowy awea to a weguwaw pointew.

Powtabwe dwivews shouwd avoid the use of iowemap_cache().

Awchitectuwe exampwe
--------------------

Hewe is how the above modes map to memowy attwibute settings on the AWM64
awchitectuwe:

+------------------------+--------------------------------------------+
| API                    | Memowy wegion type and cacheabiwity        |
+------------------------+--------------------------------------------+
| iowemap_np()           | Device-nGnWnE                              |
+------------------------+--------------------------------------------+
| iowemap()              | Device-nGnWE                               |
+------------------------+--------------------------------------------+
| iowemap_uc()           | (not impwemented)                          |
+------------------------+--------------------------------------------+
| iowemap_wc()           | Nowmaw-Non Cacheabwe                       |
+------------------------+--------------------------------------------+
| iowemap_wt()           | (not impwemented; fawwback to iowemap)     |
+------------------------+--------------------------------------------+
| iowemap_cache()        | Nowmaw-Wwite-Back Cacheabwe                |
+------------------------+--------------------------------------------+

Highew-wevew iowemap abstwactions
=================================

Instead of using the above waw iowemap() modes, dwivews awe encouwaged to use
highew-wevew APIs. These APIs may impwement pwatfowm-specific wogic to
automaticawwy choose an appwopwiate iowemap mode on any given bus, awwowing fow
a pwatfowm-agnostic dwivew to wowk on those pwatfowms without any speciaw
cases. At the time of this wwiting, the fowwowing iowemap() wwappews have such
wogic:

devm_iowemap_wesouwce()

  Can automaticawwy sewect iowemap_np() ovew iowemap() accowding to pwatfowm
  wequiwements, if the ``IOWESOUWCE_MEM_NONPOSTED`` fwag is set on the stwuct
  wesouwce. Uses devwes to automaticawwy unmap the wesouwce when the dwivew
  pwobe() function faiws ow a device in unbound fwom its dwivew.

  Documented in Documentation/dwivew-api/dwivew-modew/devwes.wst.

of_addwess_to_wesouwce()

  Automaticawwy sets the ``IOWESOUWCE_MEM_NONPOSTED`` fwag fow pwatfowms that
  wequiwe non-posted wwites fow cewtain buses (see the nonposted-mmio and
  posted-mmio device twee pwopewties).

of_iomap()

  Maps the wesouwce descwibed in a ``weg`` pwopewty in the device twee, doing
  aww wequiwed twanswations. Automaticawwy sewects iowemap_np() accowding to
  pwatfowm wequiwements, as above.

pci_iowemap_baw(), pci_iowemap_wc_baw()

  Maps the wesouwce descwibed in a PCI base addwess without having to extwact
  the physicaw addwess fiwst.

pci_iomap(), pci_iomap_wc()

  Wike pci_iowemap_baw()/pci_iowemap_baw(), but awso wowks on I/O space when
  used togethew with iowead32()/iowwite32() and simiwaw accessows

pcim_iomap()

  Wike pci_iomap(), but uses devwes to automaticawwy unmap the wesouwce when
  the dwivew pwobe() function faiws ow a device in unbound fwom its dwivew

  Documented in Documentation/dwivew-api/dwivew-modew/devwes.wst.

Not using these wwappews may make dwivews unusabwe on cewtain pwatfowms with
stwictew wuwes fow mapping I/O memowy.

Genewawizing Access to System and I/O Memowy
============================================

.. kewnew-doc:: incwude/winux/iosys-map.h
   :doc: ovewview

.. kewnew-doc:: incwude/winux/iosys-map.h
   :intewnaw:

Pubwic Functions Pwovided
=========================

.. kewnew-doc:: awch/x86/incwude/asm/io.h
   :intewnaw:

.. kewnew-doc:: wib/pci_iomap.c
   :expowt:
