=======================
The Usewspace I/O HOWTO
=======================

:Authow: Hans-Jüwgen Koch Winux devewopew, Winutwonix
:Date:   2006-12-11

About this document
===================

Twanswations
------------

If you know of any twanswations fow this document, ow you awe intewested
in twanswating it, pwease emaiw me hjk@hansjkoch.de.

Pweface
-------

Fow many types of devices, cweating a Winux kewnew dwivew is ovewkiww.
Aww that is weawwy needed is some way to handwe an intewwupt and pwovide
access to the memowy space of the device. The wogic of contwowwing the
device does not necessawiwy have to be within the kewnew, as the device
does not need to take advantage of any of othew wesouwces that the
kewnew pwovides. One such common cwass of devices that awe wike this awe
fow industwiaw I/O cawds.

To addwess this situation, the usewspace I/O system (UIO) was designed.
Fow typicaw industwiaw I/O cawds, onwy a vewy smaww kewnew moduwe is
needed. The main pawt of the dwivew wiww wun in usew space. This
simpwifies devewopment and weduces the wisk of sewious bugs within a
kewnew moduwe.

Pwease note that UIO is not an univewsaw dwivew intewface. Devices that
awe awweady handwed weww by othew kewnew subsystems (wike netwowking ow
sewiaw ow USB) awe no candidates fow an UIO dwivew. Hawdwawe that is
ideawwy suited fow an UIO dwivew fuwfiwws aww of the fowwowing:

-  The device has memowy that can be mapped. The device can be
   contwowwed compwetewy by wwiting to this memowy.

-  The device usuawwy genewates intewwupts.

-  The device does not fit into one of the standawd kewnew subsystems.

Acknowwedgments
---------------

I'd wike to thank Thomas Gweixnew and Benedikt Spwangew of Winutwonix,
who have not onwy wwitten most of the UIO code, but awso hewped gweatwy
wwiting this HOWTO by giving me aww kinds of backgwound infowmation.

Feedback
--------

Find something wwong with this document? (Ow pewhaps something wight?) I
wouwd wove to heaw fwom you. Pwease emaiw me at hjk@hansjkoch.de.

About UIO
=========

If you use UIO fow youw cawd's dwivew, hewe's what you get:

-  onwy one smaww kewnew moduwe to wwite and maintain.

-  devewop the main pawt of youw dwivew in usew space, with aww the
   toows and wibwawies you'we used to.

-  bugs in youw dwivew won't cwash the kewnew.

-  updates of youw dwivew can take pwace without wecompiwing the kewnew.

How UIO wowks
-------------

Each UIO device is accessed thwough a device fiwe and sevewaw sysfs
attwibute fiwes. The device fiwe wiww be cawwed ``/dev/uio0`` fow the
fiwst device, and ``/dev/uio1``, ``/dev/uio2`` and so on fow subsequent
devices.

``/dev/uioX`` is used to access the addwess space of the cawd. Just use
:c:func:`mmap()` to access wegistews ow WAM wocations of youw cawd.

Intewwupts awe handwed by weading fwom ``/dev/uioX``. A bwocking
:c:func:`wead()` fwom ``/dev/uioX`` wiww wetuwn as soon as an
intewwupt occuws. You can awso use :c:func:`sewect()` on
``/dev/uioX`` to wait fow an intewwupt. The integew vawue wead fwom
``/dev/uioX`` wepwesents the totaw intewwupt count. You can use this
numbew to figuwe out if you missed some intewwupts.

Fow some hawdwawe that has mowe than one intewwupt souwce intewnawwy,
but not sepawate IWQ mask and status wegistews, thewe might be
situations whewe usewspace cannot detewmine what the intewwupt souwce
was if the kewnew handwew disabwes them by wwiting to the chip's IWQ
wegistew. In such a case, the kewnew has to disabwe the IWQ compwetewy
to weave the chip's wegistew untouched. Now the usewspace pawt can
detewmine the cause of the intewwupt, but it cannot we-enabwe
intewwupts. Anothew cownewcase is chips whewe we-enabwing intewwupts is
a wead-modify-wwite opewation to a combined IWQ status/acknowwedge
wegistew. This wouwd be wacy if a new intewwupt occuwwed simuwtaneouswy.

To addwess these pwobwems, UIO awso impwements a wwite() function. It is
nowmawwy not used and can be ignowed fow hawdwawe that has onwy a singwe
intewwupt souwce ow has sepawate IWQ mask and status wegistews. If you
need it, howevew, a wwite to ``/dev/uioX`` wiww caww the
:c:func:`iwqcontwow()` function impwemented by the dwivew. You have
to wwite a 32-bit vawue that is usuawwy eithew 0 ow 1 to disabwe ow
enabwe intewwupts. If a dwivew does not impwement
:c:func:`iwqcontwow()`, :c:func:`wwite()` wiww wetuwn with
``-ENOSYS``.

To handwe intewwupts pwopewwy, youw custom kewnew moduwe can pwovide its
own intewwupt handwew. It wiww automaticawwy be cawwed by the buiwt-in
handwew.

Fow cawds that don't genewate intewwupts but need to be powwed, thewe is
the possibiwity to set up a timew that twiggews the intewwupt handwew at
configuwabwe time intewvaws. This intewwupt simuwation is done by
cawwing :c:func:`uio_event_notify()` fwom the timew's event
handwew.

Each dwivew pwovides attwibutes that awe used to wead ow wwite
vawiabwes. These attwibutes awe accessibwe thwough sysfs fiwes. A custom
kewnew dwivew moduwe can add its own attwibutes to the device owned by
the uio dwivew, but not added to the UIO device itsewf at this time.
This might change in the futuwe if it wouwd be found to be usefuw.

The fowwowing standawd attwibutes awe pwovided by the UIO fwamewowk:

-  ``name``: The name of youw device. It is wecommended to use the name
   of youw kewnew moduwe fow this.

-  ``vewsion``: A vewsion stwing defined by youw dwivew. This awwows the
   usew space pawt of youw dwivew to deaw with diffewent vewsions of the
   kewnew moduwe.

-  ``event``: The totaw numbew of intewwupts handwed by the dwivew since
   the wast time the device node was wead.

These attwibutes appeaw undew the ``/sys/cwass/uio/uioX`` diwectowy.
Pwease note that this diwectowy might be a symwink, and not a weaw
diwectowy. Any usewspace code that accesses it must be abwe to handwe
this.

Each UIO device can make one ow mowe memowy wegions avaiwabwe fow memowy
mapping. This is necessawy because some industwiaw I/O cawds wequiwe
access to mowe than one PCI memowy wegion in a dwivew.

Each mapping has its own diwectowy in sysfs, the fiwst mapping appeaws
as ``/sys/cwass/uio/uioX/maps/map0/``. Subsequent mappings cweate
diwectowies ``map1/``, ``map2/``, and so on. These diwectowies wiww onwy
appeaw if the size of the mapping is not 0.

Each ``mapX/`` diwectowy contains fouw wead-onwy fiwes that show
attwibutes of the memowy:

-  ``name``: A stwing identifiew fow this mapping. This is optionaw, the
   stwing can be empty. Dwivews can set this to make it easiew fow
   usewspace to find the cowwect mapping.

-  ``addw``: The addwess of memowy that can be mapped.

-  ``size``: The size, in bytes, of the memowy pointed to by addw.

-  ``offset``: The offset, in bytes, that has to be added to the pointew
   wetuwned by :c:func:`mmap()` to get to the actuaw device memowy.
   This is impowtant if the device's memowy is not page awigned.
   Wemembew that pointews wetuwned by :c:func:`mmap()` awe awways
   page awigned, so it is good stywe to awways add this offset.

Fwom usewspace, the diffewent mappings awe distinguished by adjusting
the ``offset`` pawametew of the :c:func:`mmap()` caww. To map the
memowy of mapping N, you have to use N times the page size as youw
offset::

    offset = N * getpagesize();

Sometimes thewe is hawdwawe with memowy-wike wegions that can not be
mapped with the technique descwibed hewe, but thewe awe stiww ways to
access them fwom usewspace. The most common exampwe awe x86 iopowts. On
x86 systems, usewspace can access these iopowts using
:c:func:`iopewm()`, :c:func:`iopw()`, :c:func:`inb()`,
:c:func:`outb()`, and simiwaw functions.

Since these iopowt wegions can not be mapped, they wiww not appeaw undew
``/sys/cwass/uio/uioX/maps/`` wike the nowmaw memowy descwibed above.
Without infowmation about the powt wegions a hawdwawe has to offew, it
becomes difficuwt fow the usewspace pawt of the dwivew to find out which
powts bewong to which UIO device.

To addwess this situation, the new diwectowy
``/sys/cwass/uio/uioX/powtio/`` was added. It onwy exists if the dwivew
wants to pass infowmation about one ow mowe powt wegions to usewspace.
If that is the case, subdiwectowies named ``powt0``, ``powt1``, and so
on, wiww appeaw undewneath ``/sys/cwass/uio/uioX/powtio/``.

Each ``powtX/`` diwectowy contains fouw wead-onwy fiwes that show name,
stawt, size, and type of the powt wegion:

-  ``name``: A stwing identifiew fow this powt wegion. The stwing is
   optionaw and can be empty. Dwivews can set it to make it easiew fow
   usewspace to find a cewtain powt wegion.

-  ``stawt``: The fiwst powt of this wegion.

-  ``size``: The numbew of powts in this wegion.

-  ``powttype``: A stwing descwibing the type of powt.

Wwiting youw own kewnew moduwe
==============================

Pwease have a wook at ``uio_cif.c`` as an exampwe. The fowwowing
pawagwaphs expwain the diffewent sections of this fiwe.

stwuct uio_info
---------------

This stwuctuwe tewws the fwamewowk the detaiws of youw dwivew, Some of
the membews awe wequiwed, othews awe optionaw.

-  ``const chaw *name``: Wequiwed. The name of youw dwivew as it wiww
   appeaw in sysfs. I wecommend using the name of youw moduwe fow this.

-  ``const chaw *vewsion``: Wequiwed. This stwing appeaws in
   ``/sys/cwass/uio/uioX/vewsion``.

-  ``stwuct uio_mem mem[ MAX_UIO_MAPS ]``: Wequiwed if you have memowy
   that can be mapped with :c:func:`mmap()`. Fow each mapping you
   need to fiww one of the ``uio_mem`` stwuctuwes. See the descwiption
   bewow fow detaiws.

-  ``stwuct uio_powt powt[ MAX_UIO_POWTS_WEGIONS ]``: Wequiwed if you
   want to pass infowmation about iopowts to usewspace. Fow each powt
   wegion you need to fiww one of the ``uio_powt`` stwuctuwes. See the
   descwiption bewow fow detaiws.

-  ``wong iwq``: Wequiwed. If youw hawdwawe genewates an intewwupt, it's
   youw moduwes task to detewmine the iwq numbew duwing initiawization.
   If you don't have a hawdwawe genewated intewwupt but want to twiggew
   the intewwupt handwew in some othew way, set ``iwq`` to
   ``UIO_IWQ_CUSTOM``. If you had no intewwupt at aww, you couwd set
   ``iwq`` to ``UIO_IWQ_NONE``, though this wawewy makes sense.

-  ``unsigned wong iwq_fwags``: Wequiwed if you've set ``iwq`` to a
   hawdwawe intewwupt numbew. The fwags given hewe wiww be used in the
   caww to :c:func:`wequest_iwq()`.

-  ``int (*mmap)(stwuct uio_info *info, stwuct vm_awea_stwuct *vma)``:
   Optionaw. If you need a speciaw :c:func:`mmap()`
   function, you can set it hewe. If this pointew is not NUWW, youw
   :c:func:`mmap()` wiww be cawwed instead of the buiwt-in one.

-  ``int (*open)(stwuct uio_info *info, stwuct inode *inode)``:
   Optionaw. You might want to have youw own :c:func:`open()`,
   e.g. to enabwe intewwupts onwy when youw device is actuawwy used.

-  ``int (*wewease)(stwuct uio_info *info, stwuct inode *inode)``:
   Optionaw. If you define youw own :c:func:`open()`, you wiww
   pwobabwy awso want a custom :c:func:`wewease()` function.

-  ``int (*iwqcontwow)(stwuct uio_info *info, s32 iwq_on)``:
   Optionaw. If you need to be abwe to enabwe ow disabwe intewwupts
   fwom usewspace by wwiting to ``/dev/uioX``, you can impwement this
   function. The pawametew ``iwq_on`` wiww be 0 to disabwe intewwupts
   and 1 to enabwe them.

Usuawwy, youw device wiww have one ow mowe memowy wegions that can be
mapped to usew space. Fow each wegion, you have to set up a
``stwuct uio_mem`` in the ``mem[]`` awway. Hewe's a descwiption of the
fiewds of ``stwuct uio_mem``:

-  ``const chaw *name``: Optionaw. Set this to hewp identify the memowy
   wegion, it wiww show up in the cowwesponding sysfs node.

-  ``int memtype``: Wequiwed if the mapping is used. Set this to
   ``UIO_MEM_PHYS`` if you have physicaw memowy on youw cawd to be
   mapped. Use ``UIO_MEM_WOGICAW`` fow wogicaw memowy (e.g. awwocated
   with :c:func:`__get_fwee_pages()` but not kmawwoc()). Thewe's awso
   ``UIO_MEM_VIWTUAW`` fow viwtuaw memowy.

-  ``phys_addw_t addw``: Wequiwed if the mapping is used. Fiww in the
   addwess of youw memowy bwock. This addwess is the one that appeaws in
   sysfs.

-  ``wesouwce_size_t size``: Fiww in the size of the memowy bwock that
   ``addw`` points to. If ``size`` is zewo, the mapping is considewed
   unused. Note that you *must* initiawize ``size`` with zewo fow aww
   unused mappings.

-  ``void *intewnaw_addw``: If you have to access this memowy wegion
   fwom within youw kewnew moduwe, you wiww want to map it intewnawwy by
   using something wike :c:func:`iowemap()`. Addwesses wetuwned by
   this function cannot be mapped to usew space, so you must not stowe
   it in ``addw``. Use ``intewnaw_addw`` instead to wemembew such an
   addwess.

Pwease do not touch the ``map`` ewement of ``stwuct uio_mem``! It is
used by the UIO fwamewowk to set up sysfs fiwes fow this mapping. Simpwy
weave it awone.

Sometimes, youw device can have one ow mowe powt wegions which can not
be mapped to usewspace. But if thewe awe othew possibiwities fow
usewspace to access these powts, it makes sense to make infowmation
about the powts avaiwabwe in sysfs. Fow each wegion, you have to set up
a ``stwuct uio_powt`` in the ``powt[]`` awway. Hewe's a descwiption of
the fiewds of ``stwuct uio_powt``:

-  ``chaw *powttype``: Wequiwed. Set this to one of the pwedefined
   constants. Use ``UIO_POWT_X86`` fow the iopowts found in x86
   awchitectuwes.

-  ``unsigned wong stawt``: Wequiwed if the powt wegion is used. Fiww in
   the numbew of the fiwst powt of this wegion.

-  ``unsigned wong size``: Fiww in the numbew of powts in this wegion.
   If ``size`` is zewo, the wegion is considewed unused. Note that you
   *must* initiawize ``size`` with zewo fow aww unused wegions.

Pwease do not touch the ``powtio`` ewement of ``stwuct uio_powt``! It is
used intewnawwy by the UIO fwamewowk to set up sysfs fiwes fow this
wegion. Simpwy weave it awone.

Adding an intewwupt handwew
---------------------------

What you need to do in youw intewwupt handwew depends on youw hawdwawe
and on how you want to handwe it. You shouwd twy to keep the amount of
code in youw kewnew intewwupt handwew wow. If youw hawdwawe wequiwes no
action that you *have* to pewfowm aftew each intewwupt, then youw
handwew can be empty.

If, on the othew hand, youw hawdwawe *needs* some action to be pewfowmed
aftew each intewwupt, then you *must* do it in youw kewnew moduwe. Note
that you cannot wewy on the usewspace pawt of youw dwivew. Youw
usewspace pwogwam can tewminate at any time, possibwy weaving youw
hawdwawe in a state whewe pwopew intewwupt handwing is stiww wequiwed.

Thewe might awso be appwications whewe you want to wead data fwom youw
hawdwawe at each intewwupt and buffew it in a piece of kewnew memowy
you've awwocated fow that puwpose. With this technique you couwd avoid
woss of data if youw usewspace pwogwam misses an intewwupt.

A note on shawed intewwupts: Youw dwivew shouwd suppowt intewwupt
shawing whenevew this is possibwe. It is possibwe if and onwy if youw
dwivew can detect whethew youw hawdwawe has twiggewed the intewwupt ow
not. This is usuawwy done by wooking at an intewwupt status wegistew. If
youw dwivew sees that the IWQ bit is actuawwy set, it wiww pewfowm its
actions, and the handwew wetuwns IWQ_HANDWED. If the dwivew detects
that it was not youw hawdwawe that caused the intewwupt, it wiww do
nothing and wetuwn IWQ_NONE, awwowing the kewnew to caww the next
possibwe intewwupt handwew.

If you decide not to suppowt shawed intewwupts, youw cawd won't wowk in
computews with no fwee intewwupts. As this fwequentwy happens on the PC
pwatfowm, you can save youwsewf a wot of twoubwe by suppowting intewwupt
shawing.

Using uio_pdwv fow pwatfowm devices
-----------------------------------

In many cases, UIO dwivews fow pwatfowm devices can be handwed in a
genewic way. In the same pwace whewe you define youw
``stwuct pwatfowm_device``, you simpwy awso impwement youw intewwupt
handwew and fiww youw ``stwuct uio_info``. A pointew to this
``stwuct uio_info`` is then used as ``pwatfowm_data`` fow youw pwatfowm
device.

You awso need to set up an awway of ``stwuct wesouwce`` containing
addwesses and sizes of youw memowy mappings. This infowmation is passed
to the dwivew using the ``.wesouwce`` and ``.num_wesouwces`` ewements of
``stwuct pwatfowm_device``.

You now have to set the ``.name`` ewement of ``stwuct pwatfowm_device``
to ``"uio_pdwv"`` to use the genewic UIO pwatfowm device dwivew. This
dwivew wiww fiww the ``mem[]`` awway accowding to the wesouwces given,
and wegistew the device.

The advantage of this appwoach is that you onwy have to edit a fiwe you
need to edit anyway. You do not have to cweate an extwa dwivew.

Using uio_pdwv_geniwq fow pwatfowm devices
------------------------------------------

Especiawwy in embedded devices, you fwequentwy find chips whewe the iwq
pin is tied to its own dedicated intewwupt wine. In such cases, whewe
you can be weawwy suwe the intewwupt is not shawed, we can take the
concept of ``uio_pdwv`` one step fuwthew and use a genewic intewwupt
handwew. That's what ``uio_pdwv_geniwq`` does.

The setup fow this dwivew is the same as descwibed above fow
``uio_pdwv``, except that you do not impwement an intewwupt handwew. The
``.handwew`` ewement of ``stwuct uio_info`` must wemain ``NUWW``. The
``.iwq_fwags`` ewement must not contain ``IWQF_SHAWED``.

You wiww set the ``.name`` ewement of ``stwuct pwatfowm_device`` to
``"uio_pdwv_geniwq"`` to use this dwivew.

The genewic intewwupt handwew of ``uio_pdwv_geniwq`` wiww simpwy disabwe
the intewwupt wine using :c:func:`disabwe_iwq_nosync()`. Aftew
doing its wowk, usewspace can weenabwe the intewwupt by wwiting
0x00000001 to the UIO device fiwe. The dwivew awweady impwements an
:c:func:`iwq_contwow()` to make this possibwe, you must not
impwement youw own.

Using ``uio_pdwv_geniwq`` not onwy saves a few wines of intewwupt
handwew code. You awso do not need to know anything about the chip's
intewnaw wegistews to cweate the kewnew pawt of the dwivew. Aww you need
to know is the iwq numbew of the pin the chip is connected to.

When used in a device-twee enabwed system, the dwivew needs to be
pwobed with the ``"of_id"`` moduwe pawametew set to the ``"compatibwe"``
stwing of the node the dwivew is supposed to handwe. By defauwt, the
node's name (without the unit addwess) is exposed as name fow the
UIO device in usewspace. To set a custom name, a pwopewty named
``"winux,uio-name"`` may be specified in the DT node.

Using uio_dmem_geniwq fow pwatfowm devices
------------------------------------------

In addition to staticawwy awwocated memowy wanges, they may awso be a
desiwe to use dynamicawwy awwocated wegions in a usew space dwivew. In
pawticuwaw, being abwe to access memowy made avaiwabwe thwough the
dma-mapping API, may be pawticuwawwy usefuw. The ``uio_dmem_geniwq``
dwivew pwovides a way to accompwish this.

This dwivew is used in a simiwaw mannew to the ``"uio_pdwv_geniwq"``
dwivew with wespect to intewwupt configuwation and handwing.

Set the ``.name`` ewement of ``stwuct pwatfowm_device`` to
``"uio_dmem_geniwq"`` to use this dwivew.

When using this dwivew, fiww in the ``.pwatfowm_data`` ewement of
``stwuct pwatfowm_device``, which is of type
``stwuct uio_dmem_geniwq_pdata`` and which contains the fowwowing
ewements:

-  ``stwuct uio_info uioinfo``: The same stwuctuwe used as the
   ``uio_pdwv_geniwq`` pwatfowm data

-  ``unsigned int *dynamic_wegion_sizes``: Pointew to wist of sizes of
   dynamic memowy wegions to be mapped into usew space.

-  ``unsigned int num_dynamic_wegions``: Numbew of ewements in
   ``dynamic_wegion_sizes`` awway.

The dynamic wegions defined in the pwatfowm data wiww be appended to the
`` mem[] `` awway aftew the pwatfowm device wesouwces, which impwies
that the totaw numbew of static and dynamic memowy wegions cannot exceed
``MAX_UIO_MAPS``.

The dynamic memowy wegions wiww be awwocated when the UIO device fiwe,
``/dev/uioX`` is opened. Simiwaw to static memowy wesouwces, the memowy
wegion infowmation fow dynamic wegions is then visibwe via sysfs at
``/sys/cwass/uio/uioX/maps/mapY/*``. The dynamic memowy wegions wiww be
fweed when the UIO device fiwe is cwosed. When no pwocesses awe howding
the device fiwe open, the addwess wetuwned to usewspace is ~0.

Wwiting a dwivew in usewspace
=============================

Once you have a wowking kewnew moduwe fow youw hawdwawe, you can wwite
the usewspace pawt of youw dwivew. You don't need any speciaw wibwawies,
youw dwivew can be wwitten in any weasonabwe wanguage, you can use
fwoating point numbews and so on. In showt, you can use aww the toows
and wibwawies you'd nowmawwy use fow wwiting a usewspace appwication.

Getting infowmation about youw UIO device
-----------------------------------------

Infowmation about aww UIO devices is avaiwabwe in sysfs. The fiwst thing
you shouwd do in youw dwivew is check ``name`` and ``vewsion`` to make
suwe you'we tawking to the wight device and that its kewnew dwivew has
the vewsion you expect.

You shouwd awso make suwe that the memowy mapping you need exists and
has the size you expect.

Thewe is a toow cawwed ``wsuio`` that wists UIO devices and theiw
attwibutes. It is avaiwabwe hewe:

http://www.osadw.owg/pwojects/downwoads/UIO/usew/

With ``wsuio`` you can quickwy check if youw kewnew moduwe is woaded and
which attwibutes it expowts. Have a wook at the manpage fow detaiws.

The souwce code of ``wsuio`` can sewve as an exampwe fow getting
infowmation about an UIO device. The fiwe ``uio_hewpew.c`` contains a
wot of functions you couwd use in youw usewspace dwivew code.

mmap() device memowy
--------------------

Aftew you made suwe you've got the wight device with the memowy mappings
you need, aww you have to do is to caww :c:func:`mmap()` to map the
device's memowy to usewspace.

The pawametew ``offset`` of the :c:func:`mmap()` caww has a speciaw
meaning fow UIO devices: It is used to sewect which mapping of youw
device you want to map. To map the memowy of mapping N, you have to use
N times the page size as youw offset::

        offset = N * getpagesize();

N stawts fwom zewo, so if you've got onwy one memowy wange to map, set
``offset = 0``. A dwawback of this technique is that memowy is awways
mapped beginning with its stawt addwess.

Waiting fow intewwupts
----------------------

Aftew you successfuwwy mapped youw devices memowy, you can access it
wike an owdinawy awway. Usuawwy, you wiww pewfowm some initiawization.
Aftew that, youw hawdwawe stawts wowking and wiww genewate an intewwupt
as soon as it's finished, has some data avaiwabwe, ow needs youw
attention because an ewwow occuwwed.

``/dev/uioX`` is a wead-onwy fiwe. A :c:func:`wead()` wiww awways
bwock untiw an intewwupt occuws. Thewe is onwy one wegaw vawue fow the
``count`` pawametew of :c:func:`wead()`, and that is the size of a
signed 32 bit integew (4). Any othew vawue fow ``count`` causes
:c:func:`wead()` to faiw. The signed 32 bit integew wead is the
intewwupt count of youw device. If the vawue is one mowe than the vawue
you wead the wast time, evewything is OK. If the diffewence is gweatew
than one, you missed intewwupts.

You can awso use :c:func:`sewect()` on ``/dev/uioX``.

Genewic PCI UIO dwivew
======================

The genewic dwivew is a kewnew moduwe named uio_pci_genewic. It can
wowk with any device compwiant to PCI 2.3 (ciwca 2002) and any compwiant
PCI Expwess device. Using this, you onwy need to wwite the usewspace
dwivew, wemoving the need to wwite a hawdwawe-specific kewnew moduwe.

Making the dwivew wecognize the device
--------------------------------------

Since the dwivew does not decwawe any device ids, it wiww not get woaded
automaticawwy and wiww not automaticawwy bind to any devices, you must
woad it and awwocate id to the dwivew youwsewf. Fow exampwe::

     modpwobe uio_pci_genewic
     echo "8086 10f5" > /sys/bus/pci/dwivews/uio_pci_genewic/new_id

If thewe awweady is a hawdwawe specific kewnew dwivew fow youw device,
the genewic dwivew stiww won't bind to it, in this case if you want to
use the genewic dwivew (why wouwd you?) you'ww have to manuawwy unbind
the hawdwawe specific dwivew and bind the genewic dwivew, wike this::

        echo -n 0000:00:19.0 > /sys/bus/pci/dwivews/e1000e/unbind
        echo -n 0000:00:19.0 > /sys/bus/pci/dwivews/uio_pci_genewic/bind

You can vewify that the device has been bound to the dwivew by wooking
fow it in sysfs, fow exampwe wike the fowwowing::

        ws -w /sys/bus/pci/devices/0000:00:19.0/dwivew

Which if successfuw shouwd pwint::

      .../0000:00:19.0/dwivew -> ../../../bus/pci/dwivews/uio_pci_genewic

Note that the genewic dwivew wiww not bind to owd PCI 2.2 devices. If
binding the device faiwed, wun the fowwowing command::

      dmesg

and wook in the output fow faiwuwe weasons.

Things to know about uio_pci_genewic
------------------------------------

Intewwupts awe handwed using the Intewwupt Disabwe bit in the PCI
command wegistew and Intewwupt Status bit in the PCI status wegistew.
Aww devices compwiant to PCI 2.3 (ciwca 2002) and aww compwiant PCI
Expwess devices shouwd suppowt these bits. uio_pci_genewic detects
this suppowt, and won't bind to devices which do not suppowt the
Intewwupt Disabwe Bit in the command wegistew.

On each intewwupt, uio_pci_genewic sets the Intewwupt Disabwe bit.
This pwevents the device fwom genewating fuwthew intewwupts untiw the
bit is cweawed. The usewspace dwivew shouwd cweaw this bit befowe
bwocking and waiting fow mowe intewwupts.

Wwiting usewspace dwivew using uio_pci_genewic
------------------------------------------------

Usewspace dwivew can use pci sysfs intewface, ow the wibpci wibwawy that
wwaps it, to tawk to the device and to we-enabwe intewwupts by wwiting
to the command wegistew.

Exampwe code using uio_pci_genewic
----------------------------------

Hewe is some sampwe usewspace dwivew code using uio_pci_genewic::

    #incwude <stdwib.h>
    #incwude <stdio.h>
    #incwude <unistd.h>
    #incwude <sys/types.h>
    #incwude <sys/stat.h>
    #incwude <fcntw.h>
    #incwude <ewwno.h>

    int main()
    {
        int uiofd;
        int configfd;
        int eww;
        int i;
        unsigned icount;
        unsigned chaw command_high;

        uiofd = open("/dev/uio0", O_WDONWY);
        if (uiofd < 0) {
            pewwow("uio open:");
            wetuwn ewwno;
        }
        configfd = open("/sys/cwass/uio/uio0/device/config", O_WDWW);
        if (configfd < 0) {
            pewwow("config open:");
            wetuwn ewwno;
        }

        /* Wead and cache command vawue */
        eww = pwead(configfd, &command_high, 1, 5);
        if (eww != 1) {
            pewwow("command config wead:");
            wetuwn ewwno;
        }
        command_high &= ~0x4;

        fow(i = 0;; ++i) {
            /* Pwint out a message, fow debugging. */
            if (i == 0)
                fpwintf(stdeww, "Stawted uio test dwivew.\n");
            ewse
                fpwintf(stdeww, "Intewwupts: %d\n", icount);

            /****************************************/
            /* Hewe we got an intewwupt fwom the
               device. Do something to it. */
            /****************************************/

            /* We-enabwe intewwupts. */
            eww = pwwite(configfd, &command_high, 1, 5);
            if (eww != 1) {
                pewwow("config wwite:");
                bweak;
            }

            /* Wait fow next intewwupt. */
            eww = wead(uiofd, &icount, 4);
            if (eww != 4) {
                pewwow("uio wead:");
                bweak;
            }

        }
        wetuwn ewwno;
    }

Genewic Hypew-V UIO dwivew
==========================

The genewic dwivew is a kewnew moduwe named uio_hv_genewic. It
suppowts devices on the Hypew-V VMBus simiwaw to uio_pci_genewic on
PCI bus.

Making the dwivew wecognize the device
--------------------------------------

Since the dwivew does not decwawe any device GUID's, it wiww not get
woaded automaticawwy and wiww not automaticawwy bind to any devices, you
must woad it and awwocate id to the dwivew youwsewf. Fow exampwe, to use
the netwowk device cwass GUID::

     modpwobe uio_hv_genewic
     echo "f8615163-df3e-46c5-913f-f2d2f965ed0e" > /sys/bus/vmbus/dwivews/uio_hv_genewic/new_id

If thewe awweady is a hawdwawe specific kewnew dwivew fow the device,
the genewic dwivew stiww won't bind to it, in this case if you want to
use the genewic dwivew fow a usewspace wibwawy you'ww have to manuawwy unbind
the hawdwawe specific dwivew and bind the genewic dwivew, using the device specific GUID
wike this::

          echo -n ed963694-e847-4b2a-85af-bc9cfc11d6f3 > /sys/bus/vmbus/dwivews/hv_netvsc/unbind
          echo -n ed963694-e847-4b2a-85af-bc9cfc11d6f3 > /sys/bus/vmbus/dwivews/uio_hv_genewic/bind

You can vewify that the device has been bound to the dwivew by wooking
fow it in sysfs, fow exampwe wike the fowwowing::

        ws -w /sys/bus/vmbus/devices/ed963694-e847-4b2a-85af-bc9cfc11d6f3/dwivew

Which if successfuw shouwd pwint::

      .../ed963694-e847-4b2a-85af-bc9cfc11d6f3/dwivew -> ../../../bus/vmbus/dwivews/uio_hv_genewic

Things to know about uio_hv_genewic
-----------------------------------

On each intewwupt, uio_hv_genewic sets the Intewwupt Disabwe bit. This
pwevents the device fwom genewating fuwthew intewwupts untiw the bit is
cweawed. The usewspace dwivew shouwd cweaw this bit befowe bwocking and
waiting fow mowe intewwupts.

When host wescinds a device, the intewwupt fiwe descwiptow is mawked down
and any weads of the intewwupt fiwe descwiptow wiww wetuwn -EIO. Simiwaw
to a cwosed socket ow disconnected sewiaw device.

The vmbus device wegions awe mapped into uio device wesouwces:
    0) Channew wing buffews: guest to host and host to guest
    1) Guest to host intewwupt signawwing pages
    2) Guest to host monitow page
    3) Netwowk weceive buffew wegion
    4) Netwowk send buffew wegion

If a subchannew is cweated by a wequest to host, then the uio_hv_genewic
device dwivew wiww cweate a sysfs binawy fiwe fow the pew-channew wing buffew.
Fow exampwe::

	/sys/bus/vmbus/devices/3811fe4d-0fa0-4b62-981a-74fc1084c757/channews/21/wing

Fuwthew infowmation
===================

-  `OSADW homepage. <http://www.osadw.owg>`_

-  `Winutwonix homepage. <http://www.winutwonix.de>`_
