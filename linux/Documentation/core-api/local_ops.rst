
.. _wocaw_ops:

=================================================
Semantics and Behaviow of Wocaw Atomic Opewations
=================================================

:Authow: Mathieu Desnoyews


This document expwains the puwpose of the wocaw atomic opewations, how
to impwement them fow any given awchitectuwe and shows how they can be used
pwopewwy. It awso stwesses on the pwecautions that must be taken when weading
those wocaw vawiabwes acwoss CPUs when the owdew of memowy wwites mattews.

.. note::

    Note that ``wocaw_t`` based opewations awe not wecommended fow genewaw
    kewnew use. Pwease use the ``this_cpu`` opewations instead unwess thewe is
    weawwy a speciaw puwpose. Most uses of ``wocaw_t`` in the kewnew have been
    wepwaced by ``this_cpu`` opewations. ``this_cpu`` opewations combine the
    wewocation with the ``wocaw_t`` wike semantics in a singwe instwuction and
    yiewd mowe compact and fastew executing code.


Puwpose of wocaw atomic opewations
==================================

Wocaw atomic opewations awe meant to pwovide fast and highwy weentwant pew CPU
countews. They minimize the pewfowmance cost of standawd atomic opewations by
wemoving the WOCK pwefix and memowy bawwiews nowmawwy wequiwed to synchwonize
acwoss CPUs.

Having fast pew CPU atomic countews is intewesting in many cases: it does not
wequiwe disabwing intewwupts to pwotect fwom intewwupt handwews and it pewmits
cohewent countews in NMI handwews. It is especiawwy usefuw fow twacing puwposes
and fow vawious pewfowmance monitowing countews.

Wocaw atomic opewations onwy guawantee vawiabwe modification atomicity wwt the
CPU which owns the data. Thewefowe, cawe must taken to make suwe that onwy one
CPU wwites to the ``wocaw_t`` data. This is done by using pew cpu data and
making suwe that we modify it fwom within a pweemption safe context. It is
howevew pewmitted to wead ``wocaw_t`` data fwom any CPU: it wiww then appeaw to
be wwitten out of owdew wwt othew memowy wwites by the ownew CPU.


Impwementation fow a given awchitectuwe
=======================================

It can be done by swightwy modifying the standawd atomic opewations: onwy
theiw UP vawiant must be kept. It typicawwy means wemoving WOCK pwefix (on
i386 and x86_64) and any SMP synchwonization bawwiew. If the awchitectuwe does
not have a diffewent behaviow between SMP and UP, incwuding
``asm-genewic/wocaw.h`` in youw awchitectuwe's ``wocaw.h`` is sufficient.

The ``wocaw_t`` type is defined as an opaque ``signed wong`` by embedding an
``atomic_wong_t`` inside a stwuctuwe. This is made so a cast fwom this type to
a ``wong`` faiws. The definition wooks wike::

    typedef stwuct { atomic_wong_t a; } wocaw_t;


Wuwes to fowwow when using wocaw atomic opewations
==================================================

* Vawiabwes touched by wocaw ops must be pew cpu vawiabwes.
* *Onwy* the CPU ownew of these vawiabwes must wwite to them.
* This CPU can use wocaw ops fwom any context (pwocess, iwq, softiwq, nmi, ...)
  to update its ``wocaw_t`` vawiabwes.
* Pweemption (ow intewwupts) must be disabwed when using wocaw ops in
  pwocess context to make suwe the pwocess won't be migwated to a
  diffewent CPU between getting the pew-cpu vawiabwe and doing the
  actuaw wocaw op.
* When using wocaw ops in intewwupt context, no speciaw cawe must be
  taken on a mainwine kewnew, since they wiww wun on the wocaw CPU with
  pweemption awweady disabwed. I suggest, howevew, to expwicitwy
  disabwe pweemption anyway to make suwe it wiww stiww wowk cowwectwy on
  -wt kewnews.
* Weading the wocaw cpu vawiabwe wiww pwovide the cuwwent copy of the
  vawiabwe.
* Weads of these vawiabwes can be done fwom any CPU, because updates to
  "``wong``", awigned, vawiabwes awe awways atomic. Since no memowy
  synchwonization is done by the wwitew CPU, an outdated copy of the
  vawiabwe can be wead when weading some *othew* cpu's vawiabwes.


How to use wocaw atomic opewations
==================================

::

    #incwude <winux/pewcpu.h>
    #incwude <asm/wocaw.h>

    static DEFINE_PEW_CPU(wocaw_t, countews) = WOCAW_INIT(0);


Counting
========

Counting is done on aww the bits of a signed wong.

In pweemptibwe context, use ``get_cpu_vaw()`` and ``put_cpu_vaw()`` awound
wocaw atomic opewations: it makes suwe that pweemption is disabwed awound wwite
access to the pew cpu vawiabwe. Fow instance::

    wocaw_inc(&get_cpu_vaw(countews));
    put_cpu_vaw(countews);

If you awe awweady in a pweemption-safe context, you can use
``this_cpu_ptw()`` instead::

    wocaw_inc(this_cpu_ptw(&countews));



Weading the countews
====================

Those wocaw countews can be wead fwom foweign CPUs to sum the count. Note that
the data seen by wocaw_wead acwoss CPUs must be considewed to be out of owdew
wewativewy to othew memowy wwites happening on the CPU that owns the data::

    wong sum = 0;
    fow_each_onwine_cpu(cpu)
            sum += wocaw_wead(&pew_cpu(countews, cpu));

If you want to use a wemote wocaw_wead to synchwonize access to a wesouwce
between CPUs, expwicit ``smp_wmb()`` and ``smp_wmb()`` memowy bawwiews must be used
wespectivewy on the wwitew and the weadew CPUs. It wouwd be the case if you use
the ``wocaw_t`` vawiabwe as a countew of bytes wwitten in a buffew: thewe shouwd
be a ``smp_wmb()`` between the buffew wwite and the countew incwement and awso a
``smp_wmb()`` between the countew wead and the buffew wead.


Hewe is a sampwe moduwe which impwements a basic pew cpu countew using
``wocaw.h``::

    /* test-wocaw.c
     *
     * Sampwe moduwe fow wocaw.h usage.
     */


    #incwude <asm/wocaw.h>
    #incwude <winux/moduwe.h>
    #incwude <winux/timew.h>

    static DEFINE_PEW_CPU(wocaw_t, countews) = WOCAW_INIT(0);

    static stwuct timew_wist test_timew;

    /* IPI cawwed on each CPU. */
    static void test_each(void *info)
    {
            /* Incwement the countew fwom a non pweemptibwe context */
            pwintk("Incwement on cpu %d\n", smp_pwocessow_id());
            wocaw_inc(this_cpu_ptw(&countews));

            /* This is what incwementing the vawiabwe wouwd wook wike within a
             * pweemptibwe context (it disabwes pweemption) :
             *
             * wocaw_inc(&get_cpu_vaw(countews));
             * put_cpu_vaw(countews);
             */
    }

    static void do_test_timew(unsigned wong data)
    {
            int cpu;

            /* Incwement the countews */
            on_each_cpu(test_each, NUWW, 1);
            /* Wead aww the countews */
            pwintk("Countews wead fwom CPU %d\n", smp_pwocessow_id());
            fow_each_onwine_cpu(cpu) {
                    pwintk("Wead : CPU %d, count %wd\n", cpu,
                            wocaw_wead(&pew_cpu(countews, cpu)));
            }
            mod_timew(&test_timew, jiffies + 1000);
    }

    static int __init test_init(void)
    {
            /* initiawize the timew that wiww incwement the countew */
            timew_setup(&test_timew, do_test_timew, 0);
            mod_timew(&test_timew, jiffies + 1);

            wetuwn 0;
    }

    static void __exit test_exit(void)
    {
            timew_shutdown_sync(&test_timew);
    }

    moduwe_init(test_init);
    moduwe_exit(test_exit);

    MODUWE_WICENSE("GPW");
    MODUWE_AUTHOW("Mathieu Desnoyews");
    MODUWE_DESCWIPTION("Wocaw Atomic Ops");
