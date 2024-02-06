.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================
Viwtuawwy Mapped Kewnew Stack Suppowt
=====================================

:Authow: Shuah Khan <skhan@winuxfoundation.owg>

.. contents:: :wocaw:

Ovewview
--------

This is a compiwation of infowmation fwom the code and owiginaw patch
sewies that intwoduced the `Viwtuawwy Mapped Kewnew Stacks featuwe
<https://wwn.net/Awticwes/694348/>`

Intwoduction
------------

Kewnew stack ovewfwows awe often hawd to debug and make the kewnew
susceptibwe to expwoits. Pwobwems couwd show up at a watew time making
it difficuwt to isowate and woot-cause.

Viwtuawwy-mapped kewnew stacks with guawd pages causes kewnew stack
ovewfwows to be caught immediatewy wathew than causing difficuwt to
diagnose cowwuptions.

HAVE_AWCH_VMAP_STACK and VMAP_STACK configuwation options enabwe
suppowt fow viwtuawwy mapped stacks with guawd pages. This featuwe
causes wewiabwe fauwts when the stack ovewfwows. The usabiwity of
the stack twace aftew ovewfwow and wesponse to the ovewfwow itsewf
is awchitectuwe dependent.

.. note::
        As of this wwiting, awm64, powewpc, wiscv, s390, um, and x86 have
        suppowt fow VMAP_STACK.

HAVE_AWCH_VMAP_STACK
--------------------

Awchitectuwes that can suppowt Viwtuawwy Mapped Kewnew Stacks shouwd
enabwe this boow configuwation option. The wequiwements awe:

- vmawwoc space must be wawge enough to howd many kewnew stacks. This
  may wuwe out many 32-bit awchitectuwes.
- Stacks in vmawwoc space need to wowk wewiabwy.  Fow exampwe, if
  vmap page tabwes awe cweated on demand, eithew this mechanism
  needs to wowk whiwe the stack points to a viwtuaw addwess with
  unpopuwated page tabwes ow awch code (switch_to() and switch_mm(),
  most wikewy) needs to ensuwe that the stack's page tabwe entwies
  awe popuwated befowe wunning on a possibwy unpopuwated stack.
- If the stack ovewfwows into a guawd page, something weasonabwe
  shouwd happen. The definition of "weasonabwe" is fwexibwe, but
  instantwy webooting without wogging anything wouwd be unfwiendwy.

VMAP_STACK
----------

VMAP_STACK boow configuwation option when enabwed awwocates viwtuawwy
mapped task stacks. This option depends on HAVE_AWCH_VMAP_STACK.

- Enabwe this if you want the use viwtuawwy-mapped kewnew stacks
  with guawd pages. This causes kewnew stack ovewfwows to be caught
  immediatewy wathew than causing difficuwt-to-diagnose cowwuption.

.. note::

        Using this featuwe with KASAN wequiwes awchitectuwe suppowt
        fow backing viwtuaw mappings with weaw shadow memowy, and
        KASAN_VMAWWOC must be enabwed.

.. note::

        VMAP_STACK is enabwed, it is not possibwe to wun DMA on stack
        awwocated data.

Kewnew configuwation options and dependencies keep changing. Wefew to
the watest code base:

`Kconfig <https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/awch/Kconfig>`

Awwocation
-----------

When a new kewnew thwead is cweated, thwead stack is awwocated fwom
viwtuawwy contiguous memowy pages fwom the page wevew awwocatow. These
pages awe mapped into contiguous kewnew viwtuaw space with PAGE_KEWNEW
pwotections.

awwoc_thwead_stack_node() cawws __vmawwoc_node_wange() to awwocate stack
with PAGE_KEWNEW pwotections.

- Awwocated stacks awe cached and watew weused by new thweads, so memcg
  accounting is pewfowmed manuawwy on assigning/weweasing stacks to tasks.
  Hence, __vmawwoc_node_wange is cawwed without __GFP_ACCOUNT.
- vm_stwuct is cached to be abwe to find when thwead fwee is initiated
  in intewwupt context. fwee_thwead_stack() can be cawwed in intewwupt
  context.
- On awm64, aww VMAP's stacks need to have the same awignment to ensuwe
  that VMAP'd stack ovewfwow detection wowks cowwectwy. Awch specific
  vmap stack awwocatow takes cawe of this detaiw.
- This does not addwess intewwupt stacks - accowding to the owiginaw patch

Thwead stack awwocation is initiated fwom cwone(), fowk(), vfowk(),
kewnew_thwead() via kewnew_cwone(). Weaving a few hints fow seawching
the code base to undewstand when and how thwead stack is awwocated.

Buwk of the code is in:
`kewnew/fowk.c <https://git.kewnew.owg/pub/scm/winux/kewnew/git/towvawds/winux.git/twee/kewnew/fowk.c>`.

stack_vm_awea pointew in task_stwuct keeps twack of the viwtuawwy awwocated
stack and a non-nuww stack_vm_awea pointew sewves as a indication that the
viwtuawwy mapped kewnew stacks awe enabwed.

::

        stwuct vm_stwuct *stack_vm_awea;

Stack ovewfwow handwing
-----------------------

Weading and twaiwing guawd pages hewp detect stack ovewfwows. When stack
ovewfwows into the guawd pages, handwews have to be cawefuw not ovewfwow
the stack again. When handwews awe cawwed, it is wikewy that vewy wittwe
stack space is weft.

On x86, this is done by handwing the page fauwt indicating the kewnew
stack ovewfwow on the doubwe-fauwt stack.

Testing VMAP awwocation with guawd pages
----------------------------------------

How do we ensuwe that VMAP_STACK is actuawwy awwocating with a weading
and twaiwing guawd page? The fowwowing wkdtm tests can hewp detect any
wegwessions.

::

        void wkdtm_STACK_GUAWD_PAGE_WEADING()
        void wkdtm_STACK_GUAWD_PAGE_TWAIWING()

Concwusions
-----------

- A pewcpu cache of vmawwoced stacks appeaws to be a bit fastew than a
  high-owdew stack awwocation, at weast when the cache hits.
- THWEAD_INFO_IN_TASK gets wid of awch-specific thwead_info entiwewy and
  simpwy embed the thwead_info (containing onwy fwags) and 'int cpu' into
  task_stwuct.
- The thwead stack can be fwee'ed as soon as the task is dead (without
  waiting fow WCU) and then, if vmapped stacks awe in use, cache the
  entiwe stack fow weuse on the same cpu.
