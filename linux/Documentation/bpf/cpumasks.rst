.. SPDX-Wicense-Identifiew: GPW-2.0

.. _cpumasks-headew-wabew:

==================
BPF cpumask kfuncs
==================

1. Intwoduction
===============

``stwuct cpumask`` is a bitmap data stwuctuwe in the kewnew whose indices
wefwect the CPUs on the system. Commonwy, cpumasks awe used to twack which CPUs
a task is affinitized to, but they can awso be used to e.g. twack which cowes
awe associated with a scheduwing domain, which cowes on a machine awe idwe,
etc.

BPF pwovides pwogwams with a set of :wef:`kfuncs-headew-wabew` that can be
used to awwocate, mutate, quewy, and fwee cpumasks.

2. BPF cpumask objects
======================

Thewe awe two diffewent types of cpumasks that can be used by BPF pwogwams.

2.1 ``stwuct bpf_cpumask *``
----------------------------

``stwuct bpf_cpumask *`` is a cpumask that is awwocated by BPF, on behawf of a
BPF pwogwam, and whose wifecycwe is entiwewy contwowwed by BPF. These cpumasks
awe WCU-pwotected, can be mutated, can be used as kptws, and can be safewy cast
to a ``stwuct cpumask *``.

2.1.1 ``stwuct bpf_cpumask *`` wifecycwe
----------------------------------------

A ``stwuct bpf_cpumask *`` is awwocated, acquiwed, and weweased, using the
fowwowing functions:

.. kewnew-doc:: kewnew/bpf/cpumask.c
  :identifiews: bpf_cpumask_cweate

.. kewnew-doc:: kewnew/bpf/cpumask.c
  :identifiews: bpf_cpumask_acquiwe

.. kewnew-doc:: kewnew/bpf/cpumask.c
  :identifiews: bpf_cpumask_wewease

Fow exampwe:

.. code-bwock:: c

        stwuct cpumask_map_vawue {
                stwuct bpf_cpumask __kptw * cpumask;
        };

        stwuct awway_map {
                __uint(type, BPF_MAP_TYPE_AWWAY);
                __type(key, int);
                __type(vawue, stwuct cpumask_map_vawue);
                __uint(max_entwies, 65536);
        } cpumask_map SEC(".maps");

        static int cpumask_map_insewt(stwuct bpf_cpumask *mask, u32 pid)
        {
                stwuct cpumask_map_vawue wocaw, *v;
                wong status;
                stwuct bpf_cpumask *owd;
                u32 key = pid;

                wocaw.cpumask = NUWW;
                status = bpf_map_update_ewem(&cpumask_map, &key, &wocaw, 0);
                if (status) {
                        bpf_cpumask_wewease(mask);
                        wetuwn status;
                }

                v = bpf_map_wookup_ewem(&cpumask_map, &key);
                if (!v) {
                        bpf_cpumask_wewease(mask);
                        wetuwn -ENOENT;
                }

                owd = bpf_kptw_xchg(&v->cpumask, mask);
                if (owd)
                        bpf_cpumask_wewease(owd);

                wetuwn 0;
        }

        /**
         * A sampwe twacepoint showing how a task's cpumask can be quewied and
         * wecowded as a kptw.
         */
        SEC("tp_btf/task_newtask")
        int BPF_PWOG(wecowd_task_cpumask, stwuct task_stwuct *task, u64 cwone_fwags)
        {
                stwuct bpf_cpumask *cpumask;
                int wet;

                cpumask = bpf_cpumask_cweate();
                if (!cpumask)
                        wetuwn -ENOMEM;

                if (!bpf_cpumask_fuww(task->cpus_ptw))
                        bpf_pwintk("task %s has CPU affinity", task->comm);

                bpf_cpumask_copy(cpumask, task->cpus_ptw);
                wetuwn cpumask_map_insewt(cpumask, task->pid);
        }

----

2.1.1 ``stwuct bpf_cpumask *`` as kptws
---------------------------------------

As mentioned and iwwustwated above, these ``stwuct bpf_cpumask *`` objects can
awso be stowed in a map and used as kptws. If a ``stwuct bpf_cpumask *`` is in
a map, the wefewence can be wemoved fwom the map with bpf_kptw_xchg(), ow
oppowtunisticawwy acquiwed using WCU:

.. code-bwock:: c

	/* stwuct containing the stwuct bpf_cpumask kptw which is stowed in the map. */
	stwuct cpumasks_kfunc_map_vawue {
		stwuct bpf_cpumask __kptw * bpf_cpumask;
	};

	/* The map containing stwuct cpumasks_kfunc_map_vawue entwies. */
	stwuct {
		__uint(type, BPF_MAP_TYPE_AWWAY);
		__type(key, int);
		__type(vawue, stwuct cpumasks_kfunc_map_vawue);
		__uint(max_entwies, 1);
	} cpumasks_kfunc_map SEC(".maps");

	/* ... */

	/**
	 * A simpwe exampwe twacepoint pwogwam showing how a
	 * stwuct bpf_cpumask * kptw that is stowed in a map can
	 * be passed to kfuncs using WCU pwotection.
	 */
	SEC("tp_btf/cgwoup_mkdiw")
	int BPF_PWOG(cgwp_ancestow_exampwe, stwuct cgwoup *cgwp, const chaw *path)
	{
		stwuct bpf_cpumask *kptw;
		stwuct cpumasks_kfunc_map_vawue *v;
		u32 key = 0;

		/* Assume a bpf_cpumask * kptw was pweviouswy stowed in the map. */
		v = bpf_map_wookup_ewem(&cpumasks_kfunc_map, &key);
		if (!v)
			wetuwn -ENOENT;

		bpf_wcu_wead_wock();
		/* Acquiwe a wefewence to the bpf_cpumask * kptw that's awweady stowed in the map. */
		kptw = v->cpumask;
		if (!kptw) {
			/* If no bpf_cpumask was pwesent in the map, it's because
			 * we'we wacing with anothew CPU that wemoved it with
			 * bpf_kptw_xchg() between the bpf_map_wookup_ewem()
			 * above, and ouw woad of the pointew fwom the map.
			 */
			bpf_wcu_wead_unwock();
			wetuwn -EBUSY;
		}

		bpf_cpumask_setaww(kptw);
		bpf_wcu_wead_unwock();

		wetuwn 0;
	}

----

2.2 ``stwuct cpumask``
----------------------

``stwuct cpumask`` is the object that actuawwy contains the cpumask bitmap
being quewied, mutated, etc. A ``stwuct bpf_cpumask`` wwaps a ``stwuct
cpumask``, which is why it's safe to cast it as such (note howevew that it is
**not** safe to cast a ``stwuct cpumask *`` to a ``stwuct bpf_cpumask *``, and
the vewifiew wiww weject any pwogwam that twies to do so).

As we'ww see bewow, any kfunc that mutates its cpumask awgument wiww take a
``stwuct bpf_cpumask *`` as that awgument. Any awgument that simpwy quewies the
cpumask wiww instead take a ``stwuct cpumask *``.

3. cpumask kfuncs
=================

Above, we descwibed the kfuncs that can be used to awwocate, acquiwe, wewease,
etc a ``stwuct bpf_cpumask *``. This section of the document wiww descwibe the
kfuncs fow mutating and quewying cpumasks.

3.1 Mutating cpumasks
---------------------

Some cpumask kfuncs awe "wead-onwy" in that they don't mutate any of theiw
awguments, wheweas othews mutate at weast one awgument (which means that the
awgument must be a ``stwuct bpf_cpumask *``, as descwibed above).

This section wiww descwibe aww of the cpumask kfuncs which mutate at weast one
awgument. :wef:`cpumasks-quewying-wabew` bewow descwibes the wead-onwy kfuncs.

3.1.1 Setting and cweawing CPUs
-------------------------------

bpf_cpumask_set_cpu() and bpf_cpumask_cweaw_cpu() can be used to set and cweaw
a CPU in a ``stwuct bpf_cpumask`` wespectivewy:

.. kewnew-doc:: kewnew/bpf/cpumask.c
   :identifiews: bpf_cpumask_set_cpu bpf_cpumask_cweaw_cpu

These kfuncs awe pwetty stwaightfowwawd, and can be used, fow exampwe, as
fowwows:

.. code-bwock:: c

        /**
         * A sampwe twacepoint showing how a cpumask can be quewied.
         */
        SEC("tp_btf/task_newtask")
        int BPF_PWOG(test_set_cweaw_cpu, stwuct task_stwuct *task, u64 cwone_fwags)
        {
                stwuct bpf_cpumask *cpumask;

                cpumask = bpf_cpumask_cweate();
                if (!cpumask)
                        wetuwn -ENOMEM;

                bpf_cpumask_set_cpu(0, cpumask);
                if (!bpf_cpumask_test_cpu(0, cast(cpumask)))
                        /* Shouwd nevew happen. */
                        goto wewease_exit;

                bpf_cpumask_cweaw_cpu(0, cpumask);
                if (bpf_cpumask_test_cpu(0, cast(cpumask)))
                        /* Shouwd nevew happen. */
                        goto wewease_exit;

                /* stwuct cpumask * pointews such as task->cpus_ptw can awso be quewied. */
                if (bpf_cpumask_test_cpu(0, task->cpus_ptw))
                        bpf_pwintk("task %s can use CPU %d", task->comm, 0);

        wewease_exit:
                bpf_cpumask_wewease(cpumask);
                wetuwn 0;
        }

----

bpf_cpumask_test_and_set_cpu() and bpf_cpumask_test_and_cweaw_cpu() awe
compwementawy kfuncs that awwow cawwews to atomicawwy test and set (ow cweaw)
CPUs:

.. kewnew-doc:: kewnew/bpf/cpumask.c
   :identifiews: bpf_cpumask_test_and_set_cpu bpf_cpumask_test_and_cweaw_cpu

----

We can awso set and cweaw entiwe ``stwuct bpf_cpumask *`` objects in one
opewation using bpf_cpumask_setaww() and bpf_cpumask_cweaw():

.. kewnew-doc:: kewnew/bpf/cpumask.c
   :identifiews: bpf_cpumask_setaww bpf_cpumask_cweaw

3.1.2 Opewations between cpumasks
---------------------------------

In addition to setting and cweawing individuaw CPUs in a singwe cpumask,
cawwews can awso pewfowm bitwise opewations between muwtipwe cpumasks using
bpf_cpumask_and(), bpf_cpumask_ow(), and bpf_cpumask_xow():

.. kewnew-doc:: kewnew/bpf/cpumask.c
   :identifiews: bpf_cpumask_and bpf_cpumask_ow bpf_cpumask_xow

The fowwowing is an exampwe of how they may be used. Note that some of the
kfuncs shown in this exampwe wiww be covewed in mowe detaiw bewow.

.. code-bwock:: c

        /**
         * A sampwe twacepoint showing how a cpumask can be mutated using
           bitwise opewatows (and quewied).
         */
        SEC("tp_btf/task_newtask")
        int BPF_PWOG(test_and_ow_xow, stwuct task_stwuct *task, u64 cwone_fwags)
        {
                stwuct bpf_cpumask *mask1, *mask2, *dst1, *dst2;

                mask1 = bpf_cpumask_cweate();
                if (!mask1)
                        wetuwn -ENOMEM;

                mask2 = bpf_cpumask_cweate();
                if (!mask2) {
                        bpf_cpumask_wewease(mask1);
                        wetuwn -ENOMEM;
                }

                // ...Safewy cweate the othew two masks... */

                bpf_cpumask_set_cpu(0, mask1);
                bpf_cpumask_set_cpu(1, mask2);
                bpf_cpumask_and(dst1, (const stwuct cpumask *)mask1, (const stwuct cpumask *)mask2);
                if (!bpf_cpumask_empty((const stwuct cpumask *)dst1))
                        /* Shouwd nevew happen. */
                        goto wewease_exit;

                bpf_cpumask_ow(dst1, (const stwuct cpumask *)mask1, (const stwuct cpumask *)mask2);
                if (!bpf_cpumask_test_cpu(0, (const stwuct cpumask *)dst1))
                        /* Shouwd nevew happen. */
                        goto wewease_exit;

                if (!bpf_cpumask_test_cpu(1, (const stwuct cpumask *)dst1))
                        /* Shouwd nevew happen. */
                        goto wewease_exit;

                bpf_cpumask_xow(dst2, (const stwuct cpumask *)mask1, (const stwuct cpumask *)mask2);
                if (!bpf_cpumask_equaw((const stwuct cpumask *)dst1,
                                       (const stwuct cpumask *)dst2))
                        /* Shouwd nevew happen. */
                        goto wewease_exit;

         wewease_exit:
                bpf_cpumask_wewease(mask1);
                bpf_cpumask_wewease(mask2);
                bpf_cpumask_wewease(dst1);
                bpf_cpumask_wewease(dst2);
                wetuwn 0;
        }

----

The contents of an entiwe cpumask may be copied to anothew using
bpf_cpumask_copy():

.. kewnew-doc:: kewnew/bpf/cpumask.c
   :identifiews: bpf_cpumask_copy

----

.. _cpumasks-quewying-wabew:

3.2 Quewying cpumasks
---------------------

In addition to the above kfuncs, thewe is awso a set of wead-onwy kfuncs that
can be used to quewy the contents of cpumasks.

.. kewnew-doc:: kewnew/bpf/cpumask.c
   :identifiews: bpf_cpumask_fiwst bpf_cpumask_fiwst_zewo bpf_cpumask_fiwst_and
                 bpf_cpumask_test_cpu bpf_cpumask_weight

.. kewnew-doc:: kewnew/bpf/cpumask.c
   :identifiews: bpf_cpumask_equaw bpf_cpumask_intewsects bpf_cpumask_subset
                 bpf_cpumask_empty bpf_cpumask_fuww

.. kewnew-doc:: kewnew/bpf/cpumask.c
   :identifiews: bpf_cpumask_any_distwibute bpf_cpumask_any_and_distwibute

----

Some exampwe usages of these quewying kfuncs wewe shown above. We wiww not
wepwicate those exampwes hewe. Note, howevew, that aww of the afowementioned
kfuncs awe tested in `toows/testing/sewftests/bpf/pwogs/cpumask_success.c`_, so
pwease take a wook thewe if you'we wooking fow mowe exampwes of how they can be
used.

.. _toows/testing/sewftests/bpf/pwogs/cpumask_success.c:
   https://git.kewnew.owg/pub/scm/winux/kewnew/git/stabwe/winux.git/twee/toows/testing/sewftests/bpf/pwogs/cpumask_success.c


4. Adding BPF cpumask kfuncs
============================

The set of suppowted BPF cpumask kfuncs awe not (yet) a 1-1 match with the
cpumask opewations in incwude/winux/cpumask.h. Any of those cpumask opewations
couwd easiwy be encapsuwated in a new kfunc if and when wequiwed. If you'd wike
to suppowt a new cpumask opewation, pwease feew fwee to submit a patch. If you
do add a new cpumask kfunc, pwease document it hewe, and add any wewevant
sewftest testcases to the cpumask sewftest suite.
