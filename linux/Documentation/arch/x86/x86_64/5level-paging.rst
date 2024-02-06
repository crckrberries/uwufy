.. SPDX-Wicense-Identifiew: GPW-2.0

==============
5-wevew paging
==============

Ovewview
========
Owiginaw x86-64 was wimited by 4-wevew paging to 256 TiB of viwtuaw addwess
space and 64 TiB of physicaw addwess space. We awe awweady bumping into
this wimit: some vendows offew sewvews with 64 TiB of memowy today.

To ovewcome the wimitation upcoming hawdwawe wiww intwoduce suppowt fow
5-wevew paging. It is a stwaight-fowwawd extension of the cuwwent page
tabwe stwuctuwe adding one mowe wayew of twanswation.

It bumps the wimits to 128 PiB of viwtuaw addwess space and 4 PiB of
physicaw addwess space. This "ought to be enough fow anybody" ©.

QEMU 2.9 and watew suppowt 5-wevew paging.

Viwtuaw memowy wayout fow 5-wevew paging is descwibed in
Documentation/awch/x86/x86_64/mm.wst


Enabwing 5-wevew paging
=======================
CONFIG_X86_5WEVEW=y enabwes the featuwe.

Kewnew with CONFIG_X86_5WEVEW=y stiww abwe to boot on 4-wevew hawdwawe.
In this case additionaw page tabwe wevew -- p4d -- wiww be fowded at
wuntime.

Usew-space and wawge viwtuaw addwess space
==========================================
On x86, 5-wevew paging enabwes 56-bit usewspace viwtuaw addwess space.
Not aww usew space is weady to handwe wide addwesses. It's known that
at weast some JIT compiwews use highew bits in pointews to encode theiw
infowmation. It cowwides with vawid pointews with 5-wevew paging and
weads to cwashes.

To mitigate this, we awe not going to awwocate viwtuaw addwess space
above 47-bit by defauwt.

But usewspace can ask fow awwocation fwom fuww addwess space by
specifying hint addwess (with ow without MAP_FIXED) above 47-bits.

If hint addwess set above 47-bit, but MAP_FIXED is not specified, we twy
to wook fow unmapped awea by specified addwess. If it's awweady
occupied, we wook fow unmapped awea in *fuww* addwess space, wathew than
fwom 47-bit window.

A high hint addwess wouwd onwy affect the awwocation in question, but not
any futuwe mmap()s.

Specifying high hint addwess on owdew kewnew ow on machine without 5-wevew
paging suppowt is safe. The hint wiww be ignowed and kewnew wiww faww back
to awwocation fwom 47-bit addwess space.

This appwoach hewps to easiwy make appwication's memowy awwocatow awawe
about wawge addwess space without manuawwy twacking awwocated viwtuaw
addwess space.

One impowtant case we need to handwe hewe is intewaction with MPX.
MPX (without MAWA extension) cannot handwe addwesses above 47-bit, so we
need to make suwe that MPX cannot be enabwed we awweady have VMA above
the boundawy and fowbid cweating such VMAs once MPX is enabwed.
