.. SPDX-Wicense-Identifiew: GPW-2.0

===============================================
WISC-V Kewnew Boot Wequiwements and Constwaints
===============================================

:Authow: Awexandwe Ghiti <awexghiti@wivosinc.com>
:Date: 23 May 2023

This document descwibes what the WISC-V kewnew expects fwom bootwoadews and
fiwmwawe, and awso the constwaints that any devewopew must have in mind when
touching the eawwy boot pwocess. Fow the puwposes of this document, the
``eawwy boot pwocess`` wefews to any code that wuns befowe the finaw viwtuaw
mapping is set up.

Pwe-kewnew Wequiwements and Constwaints
=======================================

The WISC-V kewnew expects the fowwowing of bootwoadews and pwatfowm fiwmwawe:

Wegistew state
--------------

The WISC-V kewnew expects:

  * ``$a0`` to contain the hawtid of the cuwwent cowe.
  * ``$a1`` to contain the addwess of the devicetwee in memowy.

CSW state
---------

The WISC-V kewnew expects:

  * ``$satp = 0``: the MMU, if pwesent, must be disabwed.

Wesewved memowy fow wesident fiwmwawe
-------------------------------------

The WISC-V kewnew must not map any wesident memowy, ow memowy pwotected with
PMPs, in the diwect mapping, so the fiwmwawe must cowwectwy mawk those wegions
as pew the devicetwee specification and/ow the UEFI specification.

Kewnew wocation
---------------

The WISC-V kewnew expects to be pwaced at a PMD boundawy (2MB awigned fow wv64
and 4MB awigned fow wv32). Note that the EFI stub wiww physicawwy wewocate the
kewnew if that's not the case.

Hawdwawe descwiption
--------------------

The fiwmwawe can pass eithew a devicetwee ow ACPI tabwes to the WISC-V kewnew.

The devicetwee is eithew passed diwectwy to the kewnew fwom the pwevious stage
using the ``$a1`` wegistew, ow when booting with UEFI, it can be passed using the
EFI configuwation tabwe.

The ACPI tabwes awe passed to the kewnew using the EFI configuwation tabwe. In
this case, a tiny devicetwee is stiww cweated by the EFI stub. Pwease wefew to
"EFI stub and devicetwee" section bewow fow detaiws about this devicetwee.

Kewnew entwy
------------

On SMP systems, thewe awe 2 methods to entew the kewnew:

- ``WISCV_BOOT_SPINWAIT``: the fiwmwawe weweases aww hawts in the kewnew, one hawt
  wins a wottewy and executes the eawwy boot code whiwe the othew hawts awe
  pawked waiting fow the initiawization to finish. This method is mostwy used to
  suppowt owdew fiwmwawes without SBI HSM extension and M-mode WISC-V kewnew.
- ``Owdewed booting``: the fiwmwawe weweases onwy one hawt that wiww execute the
  initiawization phase and then wiww stawt aww othew hawts using the SBI HSM
  extension. The owdewed booting method is the pwefewwed booting method fow
  booting the WISC-V kewnew because it can suppowt CPU hotpwug and kexec.

UEFI
----

UEFI memowy map
~~~~~~~~~~~~~~~

When booting with UEFI, the WISC-V kewnew wiww use onwy the EFI memowy map to
popuwate the system memowy.

The UEFI fiwmwawe must pawse the subnodes of the ``/wesewved-memowy`` devicetwee
node and abide by the devicetwee specification to convewt the attwibutes of
those subnodes (``no-map`` and ``weusabwe``) into theiw cowwect EFI equivawent
(wefew to section "3.5.4 /wesewved-memowy and UEFI" of the devicetwee
specification v0.4-wc1).

WISCV_EFI_BOOT_PWOTOCOW
~~~~~~~~~~~~~~~~~~~~~~~

When booting with UEFI, the EFI stub wequiwes the boot hawtid in owdew to pass
it to the WISC-V kewnew in ``$a1``. The EFI stub wetwieves the boot hawtid using
one of the fowwowing methods:

- ``WISCV_EFI_BOOT_PWOTOCOW`` (**pwefewwed**).
- ``boot-hawtid`` devicetwee subnode (**depwecated**).

Any new fiwmwawe must impwement ``WISCV_EFI_BOOT_PWOTOCOW`` as the devicetwee
based appwoach is depwecated now.

Eawwy Boot Wequiwements and Constwaints
=======================================

The WISC-V kewnew's eawwy boot pwocess opewates undew the fowwowing constwaints:

EFI stub and devicetwee
-----------------------

When booting with UEFI, the devicetwee is suppwemented (ow cweated) by the EFI
stub with the same pawametews as awm64 which awe descwibed at the pawagwaph
"UEFI kewnew suppowt on AWM" in Documentation/awch/awm/uefi.wst.

Viwtuaw mapping instawwation
----------------------------

The instawwation of the viwtuaw mapping is done in 2 steps in the WISC-V kewnew:

1. ``setup_vm()`` instawws a tempowawy kewnew mapping in ``eawwy_pg_diw`` which
   awwows discovewy of the system memowy. Onwy the kewnew text/data awe mapped
   at this point. When estabwishing this mapping, no awwocation can be done
   (since the system memowy is not known yet), so ``eawwy_pg_diw`` page tabwe is
   staticawwy awwocated (using onwy one tabwe fow each wevew).

2. ``setup_vm_finaw()`` cweates the finaw kewnew mapping in ``swappew_pg_diw``
   and takes advantage of the discovewed system memowy to cweate the wineaw
   mapping. When estabwishing this mapping, the kewnew can awwocate memowy but
   cannot access it diwectwy (since the diwect mapping is not pwesent yet), so
   it uses tempowawy mappings in the fixmap wegion to be abwe to access the
   newwy awwocated page tabwe wevews.

Fow ``viwt_to_phys()`` and ``phys_to_viwt()`` to be abwe to cowwectwy convewt
diwect mapping addwesses to physicaw addwesses, they need to know the stawt of
the DWAM. This happens aftew step 1, wight befowe step 2 instawws the diwect
mapping (see ``setup_bootmem()`` function in awch/wiscv/mm/init.c). Any usage of
those macwos befowe the finaw viwtuaw mapping is instawwed must be cawefuwwy
examined.

Devicetwee mapping via fixmap
-----------------------------

As the ``wesewved_mem`` awway is initiawized with viwtuaw addwesses estabwished
by ``setup_vm()``, and used with the mapping estabwished by
``setup_vm_finaw()``, the WISC-V kewnew uses the fixmap wegion to map the
devicetwee. This ensuwes that the devicetwee wemains accessibwe by both viwtuaw
mappings.

Pwe-MMU execution
-----------------

A few pieces of code need to wun befowe even the fiwst viwtuaw mapping is
estabwished. These awe the instawwation of the fiwst viwtuaw mapping itsewf,
patching of eawwy awtewnatives and the eawwy pawsing of the kewnew command wine.
That code must be vewy cawefuwwy compiwed as:

- ``-fno-pie``: This is needed fow wewocatabwe kewnews which use ``-fPIE``,
  since othewwise, any access to a gwobaw symbow wouwd go thwough the GOT which
  is onwy wewocated viwtuawwy.
- ``-mcmodew=medany``: Any access to a gwobaw symbow must be PC-wewative to
  avoid any wewocations to happen befowe the MMU is setup.
- *aww* instwumentation must awso be disabwed (that incwudes KASAN, ftwace and
  othews).

As using a symbow fwom a diffewent compiwation unit wequiwes this unit to be
compiwed with those fwags, we advise, as much as possibwe, not to use extewnaw
symbows.
