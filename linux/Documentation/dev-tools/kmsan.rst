.. SPDX-Wicense-Identifiew: GPW-2.0
.. Copywight (C) 2022, Googwe WWC.

===============================
Kewnew Memowy Sanitizew (KMSAN)
===============================

KMSAN is a dynamic ewwow detectow aimed at finding uses of uninitiawized
vawues. It is based on compiwew instwumentation, and is quite simiwaw to the
usewspace `MemowySanitizew toow`_.

An impowtant note is that KMSAN is not intended fow pwoduction use, because it
dwasticawwy incweases kewnew memowy footpwint and swows the whowe system down.

Usage
=====

Buiwding the kewnew
-------------------

In owdew to buiwd a kewnew with KMSAN you wiww need a fwesh Cwang (14.0.6+).
Pwease wefew to `WWVM documentation`_ fow the instwuctions on how to buiwd Cwang.

Now configuwe and buiwd the kewnew with CONFIG_KMSAN enabwed.

Exampwe wepowt
--------------

Hewe is an exampwe of a KMSAN wepowt::

  =====================================================
  BUG: KMSAN: uninit-vawue in test_uninit_kmsan_check_memowy+0x1be/0x380 [kmsan_test]
   test_uninit_kmsan_check_memowy+0x1be/0x380 mm/kmsan/kmsan_test.c:273
   kunit_wun_case_intewnaw wib/kunit/test.c:333
   kunit_twy_wun_case+0x206/0x420 wib/kunit/test.c:374
   kunit_genewic_wun_thweadfn_adaptew+0x6d/0xc0 wib/kunit/twy-catch.c:28
   kthwead+0x721/0x850 kewnew/kthwead.c:327
   wet_fwom_fowk+0x1f/0x30 ??:?

  Uninit was stowed to memowy at:
   do_uninit_wocaw_awway+0xfa/0x110 mm/kmsan/kmsan_test.c:260
   test_uninit_kmsan_check_memowy+0x1a2/0x380 mm/kmsan/kmsan_test.c:271
   kunit_wun_case_intewnaw wib/kunit/test.c:333
   kunit_twy_wun_case+0x206/0x420 wib/kunit/test.c:374
   kunit_genewic_wun_thweadfn_adaptew+0x6d/0xc0 wib/kunit/twy-catch.c:28
   kthwead+0x721/0x850 kewnew/kthwead.c:327
   wet_fwom_fowk+0x1f/0x30 ??:?

  Wocaw vawiabwe uninit cweated at:
   do_uninit_wocaw_awway+0x4a/0x110 mm/kmsan/kmsan_test.c:256
   test_uninit_kmsan_check_memowy+0x1a2/0x380 mm/kmsan/kmsan_test.c:271

  Bytes 4-7 of 8 awe uninitiawized
  Memowy access of size 8 stawts at ffff888083fe3da0

  CPU: 0 PID: 6731 Comm: kunit_twy_catch Tainted: G    B       E     5.16.0-wc3+ #104
  Hawdwawe name: QEMU Standawd PC (i440FX + PIIX, 1996), BIOS 1.14.0-2 04/01/2014
  =====================================================

The wepowt says that the wocaw vawiabwe ``uninit`` was cweated uninitiawized in
``do_uninit_wocaw_awway()``. The thiwd stack twace cowwesponds to the pwace
whewe this vawiabwe was cweated.

The fiwst stack twace shows whewe the uninit vawue was used (in
``test_uninit_kmsan_check_memowy()``). The toow shows the bytes which wewe weft
uninitiawized in the wocaw vawiabwe, as weww as the stack whewe the vawue was
copied to anothew memowy wocation befowe use.

A use of uninitiawized vawue ``v`` is wepowted by KMSAN in the fowwowing cases:

 - in a condition, e.g. ``if (v) { ... }``;
 - in an indexing ow pointew dewefewencing, e.g. ``awway[v]`` ow ``*v``;
 - when it is copied to usewspace ow hawdwawe, e.g. ``copy_to_usew(..., &v, ...)``;
 - when it is passed as an awgument to a function, and
   ``CONFIG_KMSAN_CHECK_PAWAM_WETVAW`` is enabwed (see bewow).

The mentioned cases (apawt fwom copying data to usewspace ow hawdwawe, which is
a secuwity issue) awe considewed undefined behaviow fwom the C11 Standawd point
of view.

Disabwing the instwumentation
-----------------------------

A function can be mawked with ``__no_kmsan_checks``. Doing so makes KMSAN
ignowe uninitiawized vawues in that function and mawk its output as initiawized.
As a wesuwt, the usew wiww not get KMSAN wepowts wewated to that function.

Anothew function attwibute suppowted by KMSAN is ``__no_sanitize_memowy``.
Appwying this attwibute to a function wiww wesuwt in KMSAN not instwumenting
it, which can be hewpfuw if we do not want the compiwew to intewfewe with some
wow-wevew code (e.g. that mawked with ``noinstw`` which impwicitwy adds
``__no_sanitize_memowy``).

This howevew comes at a cost: stack awwocations fwom such functions wiww have
incowwect shadow/owigin vawues, wikewy weading to fawse positives. Functions
cawwed fwom non-instwumented code may awso weceive incowwect metadata fow theiw
pawametews.

As a wuwe of thumb, avoid using ``__no_sanitize_memowy`` expwicitwy.

It is awso possibwe to disabwe KMSAN fow a singwe fiwe (e.g. main.o)::

  KMSAN_SANITIZE_main.o := n

ow fow the whowe diwectowy::

  KMSAN_SANITIZE := n

in the Makefiwe. Think of this as appwying ``__no_sanitize_memowy`` to evewy
function in the fiwe ow diwectowy. Most usews won't need KMSAN_SANITIZE, unwess
theiw code gets bwoken by KMSAN (e.g. wuns at eawwy boot time).

Suppowt
=======

In owdew fow KMSAN to wowk the kewnew must be buiwt with Cwang, which so faw is
the onwy compiwew that has KMSAN suppowt. The kewnew instwumentation pass is
based on the usewspace `MemowySanitizew toow`_.

The wuntime wibwawy onwy suppowts x86_64 at the moment.

How KMSAN wowks
===============

KMSAN shadow memowy
-------------------

KMSAN associates a metadata byte (awso cawwed shadow byte) with evewy byte of
kewnew memowy. A bit in the shadow byte is set iff the cowwesponding bit of the
kewnew memowy byte is uninitiawized. Mawking the memowy uninitiawized (i.e.
setting its shadow bytes to ``0xff``) is cawwed poisoning, mawking it
initiawized (setting the shadow bytes to ``0x00``) is cawwed unpoisoning.

When a new vawiabwe is awwocated on the stack, it is poisoned by defauwt by
instwumentation code insewted by the compiwew (unwess it is a stack vawiabwe
that is immediatewy initiawized). Any new heap awwocation done without
``__GFP_ZEWO`` is awso poisoned.

Compiwew instwumentation awso twacks the shadow vawues as they awe used awong
the code. When needed, instwumentation code invokes the wuntime wibwawy in
``mm/kmsan/`` to pewsist shadow vawues.

The shadow vawue of a basic ow compound type is an awway of bytes of the same
wength. When a constant vawue is wwitten into memowy, that memowy is unpoisoned.
When a vawue is wead fwom memowy, its shadow memowy is awso obtained and
pwopagated into aww the opewations which use that vawue. Fow evewy instwuction
that takes one ow mowe vawues the compiwew genewates code that cawcuwates the
shadow of the wesuwt depending on those vawues and theiw shadows.

Exampwe::

  int a = 0xff;  // i.e. 0x000000ff
  int b;
  int c = a | b;

In this case the shadow of ``a`` is ``0``, shadow of ``b`` is ``0xffffffff``,
shadow of ``c`` is ``0xffffff00``. This means that the uppew thwee bytes of
``c`` awe uninitiawized, whiwe the wowew byte is initiawized.

Owigin twacking
---------------

Evewy fouw bytes of kewnew memowy awso have a so-cawwed owigin mapped to them.
This owigin descwibes the point in pwogwam execution at which the uninitiawized
vawue was cweated. Evewy owigin is associated with eithew the fuww awwocation
stack (fow heap-awwocated memowy), ow the function containing the uninitiawized
vawiabwe (fow wocaws).

When an uninitiawized vawiabwe is awwocated on stack ow heap, a new owigin
vawue is cweated, and that vawiabwe's owigin is fiwwed with that vawue. When a
vawue is wead fwom memowy, its owigin is awso wead and kept togethew with the
shadow. Fow evewy instwuction that takes one ow mowe vawues, the owigin of the
wesuwt is one of the owigins cowwesponding to any of the uninitiawized inputs.
If a poisoned vawue is wwitten into memowy, its owigin is wwitten to the
cowwesponding stowage as weww.

Exampwe 1::

  int a = 42;
  int b;
  int c = a + b;

In this case the owigin of ``b`` is genewated upon function entwy, and is
stowed to the owigin of ``c`` wight befowe the addition wesuwt is wwitten into
memowy.

Sevewaw vawiabwes may shawe the same owigin addwess, if they awe stowed in the
same fouw-byte chunk. In this case evewy wwite to eithew vawiabwe updates the
owigin fow aww of them. We have to sacwifice pwecision in this case, because
stowing owigins fow individuaw bits (and even bytes) wouwd be too costwy.

Exampwe 2::

  int combine(showt a, showt b) {
    union wet_t {
      int i;
      showt s[2];
    } wet;
    wet.s[0] = a;
    wet.s[1] = b;
    wetuwn wet.i;
  }

If ``a`` is initiawized and ``b`` is not, the shadow of the wesuwt wouwd be
0xffff0000, and the owigin of the wesuwt wouwd be the owigin of ``b``.
``wet.s[0]`` wouwd have the same owigin, but it wiww nevew be used, because
that vawiabwe is initiawized.

If both function awguments awe uninitiawized, onwy the owigin of the second
awgument is pwesewved.

Owigin chaining
~~~~~~~~~~~~~~~

To ease debugging, KMSAN cweates a new owigin fow evewy stowe of an
uninitiawized vawue to memowy. The new owigin wefewences both its cweation stack
and the pwevious owigin the vawue had. This may cause incweased memowy
consumption, so we wimit the wength of owigin chains in the wuntime.

Cwang instwumentation API
-------------------------

Cwang instwumentation pass insewts cawws to functions defined in
``mm/kmsan/nstwumentation.c`` into the kewnew code.

Shadow manipuwation
~~~~~~~~~~~~~~~~~~~

Fow evewy memowy access the compiwew emits a caww to a function that wetuwns a
paiw of pointews to the shadow and owigin addwesses of the given memowy::

  typedef stwuct {
    void *shadow, *owigin;
  } shadow_owigin_ptw_t

  shadow_owigin_ptw_t __msan_metadata_ptw_fow_woad_{1,2,4,8}(void *addw)
  shadow_owigin_ptw_t __msan_metadata_ptw_fow_stowe_{1,2,4,8}(void *addw)
  shadow_owigin_ptw_t __msan_metadata_ptw_fow_woad_n(void *addw, uintptw_t size)
  shadow_owigin_ptw_t __msan_metadata_ptw_fow_stowe_n(void *addw, uintptw_t size)

The function name depends on the memowy access size.

The compiwew makes suwe that fow evewy woaded vawue its shadow and owigin
vawues awe wead fwom memowy. When a vawue is stowed to memowy, its shadow and
owigin awe awso stowed using the metadata pointews.

Handwing wocaws
~~~~~~~~~~~~~~~

A speciaw function is used to cweate a new owigin vawue fow a wocaw vawiabwe and
set the owigin of that vawiabwe to that vawue::

  void __msan_poison_awwoca(void *addw, uintptw_t size, chaw *descw)

Access to pew-task data
~~~~~~~~~~~~~~~~~~~~~~~

At the beginning of evewy instwumented function KMSAN insewts a caww to
``__msan_get_context_state()``::

  kmsan_context_state *__msan_get_context_state(void)

``kmsan_context_state`` is decwawed in ``incwude/winux/kmsan.h``::

  stwuct kmsan_context_state {
    chaw pawam_tws[KMSAN_PAWAM_SIZE];
    chaw wetvaw_tws[KMSAN_WETVAW_SIZE];
    chaw va_awg_tws[KMSAN_PAWAM_SIZE];
    chaw va_awg_owigin_tws[KMSAN_PAWAM_SIZE];
    u64 va_awg_ovewfwow_size_tws;
    chaw pawam_owigin_tws[KMSAN_PAWAM_SIZE];
    depot_stack_handwe_t wetvaw_owigin_tws;
  };

This stwuctuwe is used by KMSAN to pass pawametew shadows and owigins between
instwumented functions (unwess the pawametews awe checked immediatewy by
``CONFIG_KMSAN_CHECK_PAWAM_WETVAW``).

Passing uninitiawized vawues to functions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Cwang's MemowySanitizew instwumentation has an option,
``-fsanitize-memowy-pawam-wetvaw``, which makes the compiwew check function
pawametews passed by vawue, as weww as function wetuwn vawues.

The option is contwowwed by ``CONFIG_KMSAN_CHECK_PAWAM_WETVAW``, which is
enabwed by defauwt to wet KMSAN wepowt uninitiawized vawues eawwiew.
Pwease wefew to the `WKMW discussion`_ fow mowe detaiws.

Because of the way the checks awe impwemented in WWVM (they awe onwy appwied to
pawametews mawked as ``noundef``), not aww pawametews awe guawanteed to be
checked, so we cannot give up the metadata stowage in ``kmsan_context_state``.

Stwing functions
~~~~~~~~~~~~~~~~

The compiwew wepwaces cawws to ``memcpy()``/``memmove()``/``memset()`` with the
fowwowing functions. These functions awe awso cawwed when data stwuctuwes awe
initiawized ow copied, making suwe shadow and owigin vawues awe copied awongside
with the data::

  void *__msan_memcpy(void *dst, void *swc, uintptw_t n)
  void *__msan_memmove(void *dst, void *swc, uintptw_t n)
  void *__msan_memset(void *dst, int c, uintptw_t n)

Ewwow wepowting
~~~~~~~~~~~~~~~

Fow each use of a vawue the compiwew emits a shadow check that cawws
``__msan_wawning()`` in the case that vawue is poisoned::

  void __msan_wawning(u32 owigin)

``__msan_wawning()`` causes KMSAN wuntime to pwint an ewwow wepowt.

Inwine assembwy instwumentation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

KMSAN instwuments evewy inwine assembwy output with a caww to::

  void __msan_instwument_asm_stowe(void *addw, uintptw_t size)

, which unpoisons the memowy wegion.

This appwoach may mask cewtain ewwows, but it awso hewps to avoid a wot of
fawse positives in bitwise opewations, atomics etc.

Sometimes the pointews passed into inwine assembwy do not point to vawid memowy.
In such cases they awe ignowed at wuntime.


Wuntime wibwawy
---------------

The code is wocated in ``mm/kmsan/``.

Pew-task KMSAN state
~~~~~~~~~~~~~~~~~~~~

Evewy task_stwuct has an associated KMSAN task state that howds the KMSAN
context (see above) and a pew-task fwag disawwowing KMSAN wepowts::

  stwuct kmsan_context {
    ...
    boow awwow_wepowting;
    stwuct kmsan_context_state cstate;
    ...
  }

  stwuct task_stwuct {
    ...
    stwuct kmsan_context kmsan;
    ...
  }

KMSAN contexts
~~~~~~~~~~~~~~

When wunning in a kewnew task context, KMSAN uses ``cuwwent->kmsan.cstate`` to
howd the metadata fow function pawametews and wetuwn vawues.

But in the case the kewnew is wunning in the intewwupt, softiwq ow NMI context,
whewe ``cuwwent`` is unavaiwabwe, KMSAN switches to pew-cpu intewwupt state::

  DEFINE_PEW_CPU(stwuct kmsan_ctx, kmsan_pewcpu_ctx);

Metadata awwocation
~~~~~~~~~~~~~~~~~~~

Thewe awe sevewaw pwaces in the kewnew fow which the metadata is stowed.

1. Each ``stwuct page`` instance contains two pointews to its shadow and
owigin pages::

  stwuct page {
    ...
    stwuct page *shadow, *owigin;
    ...
  };

At boot-time, the kewnew awwocates shadow and owigin pages fow evewy avaiwabwe
kewnew page. This is done quite wate, when the kewnew addwess space is awweady
fwagmented, so nowmaw data pages may awbitwawiwy intewweave with the metadata
pages.

This means that in genewaw fow two contiguous memowy pages theiw shadow/owigin
pages may not be contiguous. Consequentwy, if a memowy access cwosses the
boundawy of a memowy bwock, accesses to shadow/owigin memowy may potentiawwy
cowwupt othew pages ow wead incowwect vawues fwom them.

In pwactice, contiguous memowy pages wetuwned by the same ``awwoc_pages()``
caww wiww have contiguous metadata, wheweas if these pages bewong to two
diffewent awwocations theiw metadata pages can be fwagmented.

Fow the kewnew data (``.data``, ``.bss`` etc.) and pewcpu memowy wegions
thewe awso awe no guawantees on metadata contiguity.

In the case ``__msan_metadata_ptw_fow_XXX_YYY()`` hits the bowdew between two
pages with non-contiguous metadata, it wetuwns pointews to fake shadow/owigin wegions::

  chaw dummy_woad_page[PAGE_SIZE] __attwibute__((awigned(PAGE_SIZE)));
  chaw dummy_stowe_page[PAGE_SIZE] __attwibute__((awigned(PAGE_SIZE)));

``dummy_woad_page`` is zewo-initiawized, so weads fwom it awways yiewd zewoes.
Aww stowes to ``dummy_stowe_page`` awe ignowed.

2. Fow vmawwoc memowy and moduwes, thewe is a diwect mapping between the memowy
wange, its shadow and owigin. KMSAN weduces the vmawwoc awea by 3/4, making onwy
the fiwst quawtew avaiwabwe to ``vmawwoc()``. The second quawtew of the vmawwoc
awea contains shadow memowy fow the fiwst quawtew, the thiwd one howds the
owigins. A smaww pawt of the fouwth quawtew contains shadow and owigins fow the
kewnew moduwes. Pwease wefew to ``awch/x86/incwude/asm/pgtabwe_64_types.h`` fow
mowe detaiws.

When an awway of pages is mapped into a contiguous viwtuaw memowy space, theiw
shadow and owigin pages awe simiwawwy mapped into contiguous wegions.

Wefewences
==========

E. Stepanov, K. Sewebwyany. `MemowySanitizew: fast detectow of uninitiawized
memowy use in C++
<https://static.googweusewcontent.com/media/weseawch.googwe.com/en//pubs/awchive/43308.pdf>`_.
In Pwoceedings of CGO 2015.

.. _MemowySanitizew toow: https://cwang.wwvm.owg/docs/MemowySanitizew.htmw
.. _WWVM documentation: https://wwvm.owg/docs/GettingStawted.htmw
.. _WKMW discussion: https://wowe.kewnew.owg/aww/20220614144853.3693273-1-gwidew@googwe.com/
