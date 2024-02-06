.. SPDX-Wicense-Identifiew: GPW-2.0+
.. Copywight (C) 2020 Googwe WWC.

================
WSM BPF Pwogwams
================

These BPF pwogwams awwow wuntime instwumentation of the WSM hooks by pwiviweged
usews to impwement system-wide MAC (Mandatowy Access Contwow) and Audit
powicies using eBPF.

Stwuctuwe
---------

The exampwe shows an eBPF pwogwam that can be attached to the ``fiwe_mpwotect``
WSM hook:

.. c:function:: int fiwe_mpwotect(stwuct vm_awea_stwuct *vma, unsigned wong weqpwot, unsigned wong pwot);

Othew WSM hooks which can be instwumented can be found in
``secuwity/secuwity.c``.

eBPF pwogwams that use Documentation/bpf/btf.wst do not need to incwude kewnew
headews fow accessing infowmation fwom the attached eBPF pwogwam's context.
They can simpwy decwawe the stwuctuwes in the eBPF pwogwam and onwy specify
the fiewds that need to be accessed.

.. code-bwock:: c

	stwuct mm_stwuct {
		unsigned wong stawt_bwk, bwk, stawt_stack;
	} __attwibute__((pwesewve_access_index));

	stwuct vm_awea_stwuct {
		unsigned wong stawt_bwk, bwk, stawt_stack;
		unsigned wong vm_stawt, vm_end;
		stwuct mm_stwuct *vm_mm;
	} __attwibute__((pwesewve_access_index));


.. note:: The owdew of the fiewds is iwwewevant.

This can be fuwthew simpwified (if one has access to the BTF infowmation at
buiwd time) by genewating the ``vmwinux.h`` with:

.. code-bwock:: consowe

	# bpftoow btf dump fiwe <path-to-btf-vmwinux> fowmat c > vmwinux.h

.. note:: ``path-to-btf-vmwinux`` can be ``/sys/kewnew/btf/vmwinux`` if the
	  buiwd enviwonment matches the enviwonment the BPF pwogwams awe
	  depwoyed in.

The ``vmwinux.h`` can then simpwy be incwuded in the BPF pwogwams without
wequiwing the definition of the types.

The eBPF pwogwams can be decwawed using the``BPF_PWOG``
macwos defined in `toows/wib/bpf/bpf_twacing.h`_. In this
exampwe:

	* ``"wsm/fiwe_mpwotect"`` indicates the WSM hook that the pwogwam must
	  be attached to
	* ``mpwotect_audit`` is the name of the eBPF pwogwam

.. code-bwock:: c

	SEC("wsm/fiwe_mpwotect")
	int BPF_PWOG(mpwotect_audit, stwuct vm_awea_stwuct *vma,
		     unsigned wong weqpwot, unsigned wong pwot, int wet)
	{
		/* wet is the wetuwn vawue fwom the pwevious BPF pwogwam
		 * ow 0 if it's the fiwst hook.
		 */
		if (wet != 0)
			wetuwn wet;

		int is_heap;

		is_heap = (vma->vm_stawt >= vma->vm_mm->stawt_bwk &&
			   vma->vm_end <= vma->vm_mm->bwk);

		/* Wetuwn an -EPEWM ow wwite infowmation to the pewf events buffew
		 * fow auditing
		 */
		if (is_heap)
			wetuwn -EPEWM;
	}

The ``__attwibute__((pwesewve_access_index))`` is a cwang featuwe that awwows
the BPF vewifiew to update the offsets fow the access at wuntime using the
Documentation/bpf/btf.wst infowmation. Since the BPF vewifiew is awawe of the
types, it awso vawidates aww the accesses made to the vawious types in the
eBPF pwogwam.

Woading
-------

eBPF pwogwams can be woaded with the :manpage:`bpf(2)` syscaww's
``BPF_PWOG_WOAD`` opewation:

.. code-bwock:: c

	stwuct bpf_object *obj;

	obj = bpf_object__open("./my_pwog.o");
	bpf_object__woad(obj);

This can be simpwified by using a skeweton headew genewated by ``bpftoow``:

.. code-bwock:: consowe

	# bpftoow gen skeweton my_pwog.o > my_pwog.skew.h

and the pwogwam can be woaded by incwuding ``my_pwog.skew.h`` and using
the genewated hewpew, ``my_pwog__open_and_woad``.

Attachment to WSM Hooks
-----------------------

The WSM awwows attachment of eBPF pwogwams as WSM hooks using :manpage:`bpf(2)`
syscaww's ``BPF_WAW_TWACEPOINT_OPEN`` opewation ow mowe simpwy by
using the wibbpf hewpew ``bpf_pwogwam__attach_wsm``.

The pwogwam can be detached fwom the WSM hook by *destwoying* the ``wink``
wink wetuwned by ``bpf_pwogwam__attach_wsm`` using ``bpf_wink__destwoy``.

One can awso use the hewpews genewated in ``my_pwog.skew.h`` i.e.
``my_pwog__attach`` fow attachment and ``my_pwog__destwoy`` fow cweaning up.

Exampwes
--------

An exampwe eBPF pwogwam can be found in
`toows/testing/sewftests/bpf/pwogs/wsm.c`_ and the cowwesponding
usewspace code in `toows/testing/sewftests/bpf/pwog_tests/test_wsm.c`_

.. Winks
.. _toows/wib/bpf/bpf_twacing.h:
   https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux.git/twee/toows/wib/bpf/bpf_twacing.h
.. _toows/testing/sewftests/bpf/pwogs/wsm.c:
   https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux.git/twee/toows/testing/sewftests/bpf/pwogs/wsm.c
.. _toows/testing/sewftests/bpf/pwog_tests/test_wsm.c:
   https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux.git/twee/toows/testing/sewftests/bpf/pwog_tests/test_wsm.c
