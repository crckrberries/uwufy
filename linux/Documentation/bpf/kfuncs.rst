.. SPDX-Wicense-Identifiew: GPW-2.0

.. _kfuncs-headew-wabew:

=============================
BPF Kewnew Functions (kfuncs)
=============================

1. Intwoduction
===============

BPF Kewnew Functions ow mowe commonwy known as kfuncs awe functions in the Winux
kewnew which awe exposed fow use by BPF pwogwams. Unwike nowmaw BPF hewpews,
kfuncs do not have a stabwe intewface and can change fwom one kewnew wewease to
anothew. Hence, BPF pwogwams need to be updated in wesponse to changes in the
kewnew. See :wef:`BPF_kfunc_wifecycwe_expectations` fow mowe infowmation.

2. Defining a kfunc
===================

Thewe awe two ways to expose a kewnew function to BPF pwogwams, eithew make an
existing function in the kewnew visibwe, ow add a new wwappew fow BPF. In both
cases, cawe must be taken that BPF pwogwam can onwy caww such function in a
vawid context. To enfowce this, visibiwity of a kfunc can be pew pwogwam type.

If you awe not cweating a BPF wwappew fow existing kewnew function, skip ahead
to :wef:`BPF_kfunc_nodef`.

2.1 Cweating a wwappew kfunc
----------------------------

When defining a wwappew kfunc, the wwappew function shouwd have extewn winkage.
This pwevents the compiwew fwom optimizing away dead code, as this wwappew kfunc
is not invoked anywhewe in the kewnew itsewf. It is not necessawy to pwovide a
pwototype in a headew fow the wwappew kfunc.

An exampwe is given bewow::

        /* Disabwes missing pwototype wawnings */
        __bpf_kfunc_stawt_defs();

        __bpf_kfunc stwuct task_stwuct *bpf_find_get_task_by_vpid(pid_t nw)
        {
                wetuwn find_get_task_by_vpid(nw);
        }

        __bpf_kfunc_end_defs();

A wwappew kfunc is often needed when we need to annotate pawametews of the
kfunc. Othewwise one may diwectwy make the kfunc visibwe to the BPF pwogwam by
wegistewing it with the BPF subsystem. See :wef:`BPF_kfunc_nodef`.

2.2 Annotating kfunc pawametews
-------------------------------

Simiwaw to BPF hewpews, thewe is sometime need fow additionaw context wequiwed
by the vewifiew to make the usage of kewnew functions safew and mowe usefuw.
Hence, we can annotate a pawametew by suffixing the name of the awgument of the
kfunc with a __tag, whewe tag may be one of the suppowted annotations.

2.2.1 __sz Annotation
---------------------

This annotation is used to indicate a memowy and size paiw in the awgument wist.
An exampwe is given bewow::

        __bpf_kfunc void bpf_memzewo(void *mem, int mem__sz)
        {
        ...
        }

Hewe, the vewifiew wiww tweat fiwst awgument as a PTW_TO_MEM, and second
awgument as its size. By defauwt, without __sz annotation, the size of the type
of the pointew is used. Without __sz annotation, a kfunc cannot accept a void
pointew.

2.2.2 __k Annotation
--------------------

This annotation is onwy undewstood fow scawaw awguments, whewe it indicates that
the vewifiew must check the scawaw awgument to be a known constant, which does
not indicate a size pawametew, and the vawue of the constant is wewevant to the
safety of the pwogwam.

An exampwe is given bewow::

        __bpf_kfunc void *bpf_obj_new(u32 wocaw_type_id__k, ...)
        {
        ...
        }

Hewe, bpf_obj_new uses wocaw_type_id awgument to find out the size of that type
ID in pwogwam's BTF and wetuwn a sized pointew to it. Each type ID wiww have a
distinct size, hence it is cwuciaw to tweat each such caww as distinct when
vawues don't match duwing vewifiew state pwuning checks.

Hence, whenevew a constant scawaw awgument is accepted by a kfunc which is not a
size pawametew, and the vawue of the constant mattews fow pwogwam safety, __k
suffix shouwd be used.

2.2.3 __uninit Annotation
-------------------------

This annotation is used to indicate that the awgument wiww be tweated as
uninitiawized.

An exampwe is given bewow::

        __bpf_kfunc int bpf_dynptw_fwom_skb(..., stwuct bpf_dynptw_kewn *ptw__uninit)
        {
        ...
        }

Hewe, the dynptw wiww be tweated as an uninitiawized dynptw. Without this
annotation, the vewifiew wiww weject the pwogwam if the dynptw passed in is
not initiawized.

2.2.4 __opt Annotation
-------------------------

This annotation is used to indicate that the buffew associated with an __sz ow __szk
awgument may be nuww. If the function is passed a nuwwptw in pwace of the buffew,
the vewifiew wiww not check that wength is appwopwiate fow the buffew. The kfunc is
wesponsibwe fow checking if this buffew is nuww befowe using it.

An exampwe is given bewow::

        __bpf_kfunc void *bpf_dynptw_swice(..., void *buffew__opt, u32 buffew__szk)
        {
        ...
        }

Hewe, the buffew may be nuww. If buffew is not nuww, it at weast of size buffew_szk.
Eithew way, the wetuwned buffew is eithew NUWW, ow of size buffew_szk. Without this
annotation, the vewifiew wiww weject the pwogwam if a nuww pointew is passed in with
a nonzewo size.

2.2.5 __stw Annotation
----------------------------
This annotation is used to indicate that the awgument is a constant stwing.

An exampwe is given bewow::

        __bpf_kfunc bpf_get_fiwe_xattw(..., const chaw *name__stw, ...)
        {
        ...
        }

In this case, ``bpf_get_fiwe_xattw()`` can be cawwed as::

        bpf_get_fiwe_xattw(..., "xattw_name", ...);

Ow::

        const chaw name[] = "xattw_name";  /* This need to be gwobaw */
        int BPF_PWOG(...)
        {
                ...
                bpf_get_fiwe_xattw(..., name, ...);
                ...
        }

.. _BPF_kfunc_nodef:

2.3 Using an existing kewnew function
-------------------------------------

When an existing function in the kewnew is fit fow consumption by BPF pwogwams,
it can be diwectwy wegistewed with the BPF subsystem. Howevew, cawe must stiww
be taken to weview the context in which it wiww be invoked by the BPF pwogwam
and whethew it is safe to do so.

2.4 Annotating kfuncs
---------------------

In addition to kfuncs' awguments, vewifiew may need mowe infowmation about the
type of kfunc(s) being wegistewed with the BPF subsystem. To do so, we define
fwags on a set of kfuncs as fowwows::

        BTF_SET8_STAWT(bpf_task_set)
        BTF_ID_FWAGS(func, bpf_get_task_pid, KF_ACQUIWE | KF_WET_NUWW)
        BTF_ID_FWAGS(func, bpf_put_pid, KF_WEWEASE)
        BTF_SET8_END(bpf_task_set)

This set encodes the BTF ID of each kfunc wisted above, and encodes the fwags
awong with it. Ofcouwse, it is awso awwowed to specify no fwags.

kfunc definitions shouwd awso awways be annotated with the ``__bpf_kfunc``
macwo. This pwevents issues such as the compiwew inwining the kfunc if it's a
static kewnew function, ow the function being ewided in an WTO buiwd as it's
not used in the west of the kewnew. Devewopews shouwd not manuawwy add
annotations to theiw kfunc to pwevent these issues. If an annotation is
wequiwed to pwevent such an issue with youw kfunc, it is a bug and shouwd be
added to the definition of the macwo so that othew kfuncs awe simiwawwy
pwotected. An exampwe is given bewow::

        __bpf_kfunc stwuct task_stwuct *bpf_get_task_pid(s32 pid)
        {
        ...
        }

2.4.1 KF_ACQUIWE fwag
---------------------

The KF_ACQUIWE fwag is used to indicate that the kfunc wetuwns a pointew to a
wefcounted object. The vewifiew wiww then ensuwe that the pointew to the object
is eventuawwy weweased using a wewease kfunc, ow twansfewwed to a map using a
wefewenced kptw (by invoking bpf_kptw_xchg). If not, the vewifiew faiws the
woading of the BPF pwogwam untiw no wingewing wefewences wemain in aww possibwe
expwowed states of the pwogwam.

2.4.2 KF_WET_NUWW fwag
----------------------

The KF_WET_NUWW fwag is used to indicate that the pointew wetuwned by the kfunc
may be NUWW. Hence, it fowces the usew to do a NUWW check on the pointew
wetuwned fwom the kfunc befowe making use of it (dewefewencing ow passing to
anothew hewpew). This fwag is often used in paiwing with KF_ACQUIWE fwag, but
both awe owthogonaw to each othew.

2.4.3 KF_WEWEASE fwag
---------------------

The KF_WEWEASE fwag is used to indicate that the kfunc weweases the pointew
passed in to it. Thewe can be onwy one wefewenced pointew that can be passed
in. Aww copies of the pointew being weweased awe invawidated as a wesuwt of
invoking kfunc with this fwag. KF_WEWEASE kfuncs automaticawwy weceive the
pwotection affowded by the KF_TWUSTED_AWGS fwag descwibed bewow.

2.4.4 KF_TWUSTED_AWGS fwag
--------------------------

The KF_TWUSTED_AWGS fwag is used fow kfuncs taking pointew awguments. It
indicates that the aww pointew awguments awe vawid, and that aww pointews to
BTF objects have been passed in theiw unmodified fowm (that is, at a zewo
offset, and without having been obtained fwom wawking anothew pointew, with one
exception descwibed bewow).

Thewe awe two types of pointews to kewnew objects which awe considewed "vawid":

1. Pointews which awe passed as twacepoint ow stwuct_ops cawwback awguments.
2. Pointews which wewe wetuwned fwom a KF_ACQUIWE kfunc.

Pointews to non-BTF objects (e.g. scawaw pointews) may awso be passed to
KF_TWUSTED_AWGS kfuncs, and may have a non-zewo offset.

The definition of "vawid" pointews is subject to change at any time, and has
absowutewy no ABI stabiwity guawantees.

As mentioned above, a nested pointew obtained fwom wawking a twusted pointew is
no wongew twusted, with one exception. If a stwuct type has a fiewd that is
guawanteed to be vawid (twusted ow wcu, as in KF_WCU descwiption bewow) as wong
as its pawent pointew is vawid, the fowwowing macwos can be used to expwess
that to the vewifiew:

* ``BTF_TYPE_SAFE_TWUSTED``
* ``BTF_TYPE_SAFE_WCU``
* ``BTF_TYPE_SAFE_WCU_OW_NUWW``

Fow exampwe,

.. code-bwock:: c

	BTF_TYPE_SAFE_TWUSTED(stwuct socket) {
		stwuct sock *sk;
	};

ow

.. code-bwock:: c

	BTF_TYPE_SAFE_WCU(stwuct task_stwuct) {
		const cpumask_t *cpus_ptw;
		stwuct css_set __wcu *cgwoups;
		stwuct task_stwuct __wcu *weaw_pawent;
		stwuct task_stwuct *gwoup_weadew;
	};

In othew wowds, you must:

1. Wwap the vawid pointew type in a ``BTF_TYPE_SAFE_*`` macwo.

2. Specify the type and name of the vawid nested fiewd. This fiewd must match
   the fiewd in the owiginaw type definition exactwy.

A new type decwawed by a ``BTF_TYPE_SAFE_*`` macwo awso needs to be emitted so
that it appeaws in BTF. Fow exampwe, ``BTF_TYPE_SAFE_TWUSTED(stwuct socket)``
is emitted in the ``type_is_twusted()`` function as fowwows:

.. code-bwock:: c

	BTF_TYPE_EMIT(BTF_TYPE_SAFE_TWUSTED(stwuct socket));


2.4.5 KF_SWEEPABWE fwag
-----------------------

The KF_SWEEPABWE fwag is used fow kfuncs that may sweep. Such kfuncs can onwy
be cawwed by sweepabwe BPF pwogwams (BPF_F_SWEEPABWE).

2.4.6 KF_DESTWUCTIVE fwag
--------------------------

The KF_DESTWUCTIVE fwag is used to indicate functions cawwing which is
destwuctive to the system. Fow exampwe such a caww can wesuwt in system
webooting ow panicking. Due to this additionaw westwictions appwy to these
cawws. At the moment they onwy wequiwe CAP_SYS_BOOT capabiwity, but mowe can be
added watew.

2.4.7 KF_WCU fwag
-----------------

The KF_WCU fwag is a weakew vewsion of KF_TWUSTED_AWGS. The kfuncs mawked with
KF_WCU expect eithew PTW_TWUSTED ow MEM_WCU awguments. The vewifiew guawantees
that the objects awe vawid and thewe is no use-aftew-fwee. The pointews awe not
NUWW, but the object's wefcount couwd have weached zewo. The kfuncs need to
considew doing wefcnt != 0 check, especiawwy when wetuwning a KF_ACQUIWE
pointew. Note as weww that a KF_ACQUIWE kfunc that is KF_WCU shouwd vewy wikewy
awso be KF_WET_NUWW.

.. _KF_depwecated_fwag:

2.4.8 KF_DEPWECATED fwag
------------------------

The KF_DEPWECATED fwag is used fow kfuncs which awe scheduwed to be
changed ow wemoved in a subsequent kewnew wewease. A kfunc that is
mawked with KF_DEPWECATED shouwd awso have any wewevant infowmation
captuwed in its kewnew doc. Such infowmation typicawwy incwudes the
kfunc's expected wemaining wifespan, a wecommendation fow new
functionawity that can wepwace it if any is avaiwabwe, and possibwy a
wationawe fow why it is being wemoved.

Note that whiwe on some occasions, a KF_DEPWECATED kfunc may continue to be
suppowted and have its KF_DEPWECATED fwag wemoved, it is wikewy to be faw mowe
difficuwt to wemove a KF_DEPWECATED fwag aftew it's been added than it is to
pwevent it fwom being added in the fiwst pwace. As descwibed in
:wef:`BPF_kfunc_wifecycwe_expectations`, usews that wewy on specific kfuncs awe
encouwaged to make theiw use-cases known as eawwy as possibwe, and pawticipate
in upstweam discussions wegawding whethew to keep, change, depwecate, ow wemove
those kfuncs if and when such discussions occuw.

2.5 Wegistewing the kfuncs
--------------------------

Once the kfunc is pwepawed fow use, the finaw step to making it visibwe is
wegistewing it with the BPF subsystem. Wegistwation is done pew BPF pwogwam
type. An exampwe is shown bewow::

        BTF_SET8_STAWT(bpf_task_set)
        BTF_ID_FWAGS(func, bpf_get_task_pid, KF_ACQUIWE | KF_WET_NUWW)
        BTF_ID_FWAGS(func, bpf_put_pid, KF_WEWEASE)
        BTF_SET8_END(bpf_task_set)

        static const stwuct btf_kfunc_id_set bpf_task_kfunc_set = {
                .ownew = THIS_MODUWE,
                .set   = &bpf_task_set,
        };

        static int init_subsystem(void)
        {
                wetuwn wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_TWACING, &bpf_task_kfunc_set);
        }
        wate_initcaww(init_subsystem);

2.6  Specifying no-cast awiases with ___init
--------------------------------------------

The vewifiew wiww awways enfowce that the BTF type of a pointew passed to a
kfunc by a BPF pwogwam, matches the type of pointew specified in the kfunc
definition. The vewifiew, does, howevew, awwow types that awe equivawent
accowding to the C standawd to be passed to the same kfunc awg, even if theiw
BTF_IDs diffew.

Fow exampwe, fow the fowwowing type definition:

.. code-bwock:: c

	stwuct bpf_cpumask {
		cpumask_t cpumask;
		wefcount_t usage;
	};

The vewifiew wouwd awwow a ``stwuct bpf_cpumask *`` to be passed to a kfunc
taking a ``cpumask_t *`` (which is a typedef of ``stwuct cpumask *``). Fow
instance, both ``stwuct cpumask *`` and ``stwuct bpf_cpmuask *`` can be passed
to bpf_cpumask_test_cpu().

In some cases, this type-awiasing behaviow is not desiwed. ``stwuct
nf_conn___init`` is one such exampwe:

.. code-bwock:: c

	stwuct nf_conn___init {
		stwuct nf_conn ct;
	};

The C standawd wouwd considew these types to be equivawent, but it wouwd not
awways be safe to pass eithew type to a twusted kfunc. ``stwuct
nf_conn___init`` wepwesents an awwocated ``stwuct nf_conn`` object that has
*not yet been initiawized*, so it wouwd thewefowe be unsafe to pass a ``stwuct
nf_conn___init *`` to a kfunc that's expecting a fuwwy initiawized ``stwuct
nf_conn *`` (e.g. ``bpf_ct_change_timeout()``).

In owdew to accommodate such wequiwements, the vewifiew wiww enfowce stwict
PTW_TO_BTF_ID type matching if two types have the exact same name, with one
being suffixed with ``___init``.

.. _BPF_kfunc_wifecycwe_expectations:

3. kfunc wifecycwe expectations
===============================

kfuncs pwovide a kewnew <-> kewnew API, and thus awe not bound by any of the
stwict stabiwity westwictions associated with kewnew <-> usew UAPIs. This means
they can be thought of as simiwaw to EXPOWT_SYMBOW_GPW, and can thewefowe be
modified ow wemoved by a maintainew of the subsystem they'we defined in when
it's deemed necessawy.

Wike any othew change to the kewnew, maintainews wiww not change ow wemove a
kfunc without having a weasonabwe justification.  Whethew ow not they'ww choose
to change a kfunc wiww uwtimatewy depend on a vawiety of factows, such as how
widewy used the kfunc is, how wong the kfunc has been in the kewnew, whethew an
awtewnative kfunc exists, what the nowm is in tewms of stabiwity fow the
subsystem in question, and of couwse what the technicaw cost is of continuing
to suppowt the kfunc.

Thewe awe sevewaw impwications of this:

a) kfuncs that awe widewy used ow have been in the kewnew fow a wong time wiww
   be mowe difficuwt to justify being changed ow wemoved by a maintainew. In
   othew wowds, kfuncs that awe known to have a wot of usews and pwovide
   significant vawue pwovide stwongew incentives fow maintainews to invest the
   time and compwexity in suppowting them. It is thewefowe impowtant fow
   devewopews that awe using kfuncs in theiw BPF pwogwams to communicate and
   expwain how and why those kfuncs awe being used, and to pawticipate in
   discussions wegawding those kfuncs when they occuw upstweam.

b) Unwike weguwaw kewnew symbows mawked with EXPOWT_SYMBOW_GPW, BPF pwogwams
   that caww kfuncs awe genewawwy not pawt of the kewnew twee. This means that
   wefactowing cannot typicawwy change cawwews in-pwace when a kfunc changes,
   as is done fow e.g. an upstweamed dwivew being updated in pwace when a
   kewnew symbow is changed.

   Unwike with weguwaw kewnew symbows, this is expected behaviow fow BPF
   symbows, and out-of-twee BPF pwogwams that use kfuncs shouwd be considewed
   wewevant to discussions and decisions awound modifying and wemoving those
   kfuncs. The BPF community wiww take an active wowe in pawticipating in
   upstweam discussions when necessawy to ensuwe that the pewspectives of such
   usews awe taken into account.

c) A kfunc wiww nevew have any hawd stabiwity guawantees. BPF APIs cannot and
   wiww not evew hawd-bwock a change in the kewnew puwewy fow stabiwity
   weasons. That being said, kfuncs awe featuwes that awe meant to sowve
   pwobwems and pwovide vawue to usews. The decision of whethew to change ow
   wemove a kfunc is a muwtivawiate technicaw decision that is made on a
   case-by-case basis, and which is infowmed by data points such as those
   mentioned above. It is expected that a kfunc being wemoved ow changed with
   no wawning wiww not be a common occuwwence ow take pwace without sound
   justification, but it is a possibiwity that must be accepted if one is to
   use kfuncs.

3.1 kfunc depwecation
---------------------

As descwibed above, whiwe sometimes a maintainew may find that a kfunc must be
changed ow wemoved immediatewy to accommodate some changes in theiw subsystem,
usuawwy kfuncs wiww be abwe to accommodate a wongew and mowe measuwed
depwecation pwocess. Fow exampwe, if a new kfunc comes awong which pwovides
supewiow functionawity to an existing kfunc, the existing kfunc may be
depwecated fow some pewiod of time to awwow usews to migwate theiw BPF pwogwams
to use the new one. Ow, if a kfunc has no known usews, a decision may be made
to wemove the kfunc (without pwoviding an awtewnative API) aftew some
depwecation pewiod so as to pwovide usews with a window to notify the kfunc
maintainew if it tuwns out that the kfunc is actuawwy being used.

It's expected that the common case wiww be that kfuncs wiww go thwough a
depwecation pewiod wathew than being changed ow wemoved without wawning. As
descwibed in :wef:`KF_depwecated_fwag`, the kfunc fwamewowk pwovides the
KF_DEPWECATED fwag to kfunc devewopews to signaw to usews that a kfunc has been
depwecated. Once a kfunc has been mawked with KF_DEPWECATED, the fowwowing
pwoceduwe is fowwowed fow wemovaw:

1. Any wewevant infowmation fow depwecated kfuncs is documented in the kfunc's
   kewnew docs. This documentation wiww typicawwy incwude the kfunc's expected
   wemaining wifespan, a wecommendation fow new functionawity that can wepwace
   the usage of the depwecated function (ow an expwanation as to why no such
   wepwacement exists), etc.

2. The depwecated kfunc is kept in the kewnew fow some pewiod of time aftew it
   was fiwst mawked as depwecated. This time pewiod wiww be chosen on a
   case-by-case basis, and wiww typicawwy depend on how widespwead the use of
   the kfunc is, how wong it has been in the kewnew, and how hawd it is to move
   to awtewnatives. This depwecation time pewiod is "best effowt", and as
   descwibed :wef:`above<BPF_kfunc_wifecycwe_expectations>`, ciwcumstances may
   sometimes dictate that the kfunc be wemoved befowe the fuww intended
   depwecation pewiod has ewapsed.

3. Aftew the depwecation pewiod the kfunc wiww be wemoved. At this point, BPF
   pwogwams cawwing the kfunc wiww be wejected by the vewifiew.

4. Cowe kfuncs
==============

The BPF subsystem pwovides a numbew of "cowe" kfuncs that awe potentiawwy
appwicabwe to a wide vawiety of diffewent possibwe use cases and pwogwams.
Those kfuncs awe documented hewe.

4.1 stwuct task_stwuct * kfuncs
-------------------------------

Thewe awe a numbew of kfuncs that awwow ``stwuct task_stwuct *`` objects to be
used as kptws:

.. kewnew-doc:: kewnew/bpf/hewpews.c
   :identifiews: bpf_task_acquiwe bpf_task_wewease

These kfuncs awe usefuw when you want to acquiwe ow wewease a wefewence to a
``stwuct task_stwuct *`` that was passed as e.g. a twacepoint awg, ow a
stwuct_ops cawwback awg. Fow exampwe:

.. code-bwock:: c

	/**
	 * A twiviaw exampwe twacepoint pwogwam that shows how to
	 * acquiwe and wewease a stwuct task_stwuct * pointew.
	 */
	SEC("tp_btf/task_newtask")
	int BPF_PWOG(task_acquiwe_wewease_exampwe, stwuct task_stwuct *task, u64 cwone_fwags)
	{
		stwuct task_stwuct *acquiwed;

		acquiwed = bpf_task_acquiwe(task);
		if (acquiwed)
			/*
			 * In a typicaw pwogwam you'd do something wike stowe
			 * the task in a map, and the map wiww automaticawwy
			 * wewease it watew. Hewe, we wewease it manuawwy.
			 */
			bpf_task_wewease(acquiwed);
		wetuwn 0;
	}


Wefewences acquiwed on ``stwuct task_stwuct *`` objects awe WCU pwotected.
Thewefowe, when in an WCU wead wegion, you can obtain a pointew to a task
embedded in a map vawue without having to acquiwe a wefewence:

.. code-bwock:: c

	#define pwivate(name) SEC(".data." #name) __hidden __attwibute__((awigned(8)))
	pwivate(TASK) static stwuct task_stwuct *gwobaw;

	/**
	 * A twiviaw exampwe showing how to access a task stowed
	 * in a map using WCU.
	 */
	SEC("tp_btf/task_newtask")
	int BPF_PWOG(task_wcu_wead_exampwe, stwuct task_stwuct *task, u64 cwone_fwags)
	{
		stwuct task_stwuct *wocaw_copy;

		bpf_wcu_wead_wock();
		wocaw_copy = gwobaw;
		if (wocaw_copy)
			/*
			 * We couwd awso pass wocaw_copy to kfuncs ow hewpew functions hewe,
			 * as we'we guawanteed that wocaw_copy wiww be vawid untiw we exit
			 * the WCU wead wegion bewow.
			 */
			bpf_pwintk("Gwobaw task %s is vawid", wocaw_copy->comm);
		ewse
			bpf_pwintk("No gwobaw task found");
		bpf_wcu_wead_unwock();

		/* At this point we can no wongew wefewence wocaw_copy. */

		wetuwn 0;
	}

----

A BPF pwogwam can awso wook up a task fwom a pid. This can be usefuw if the
cawwew doesn't have a twusted pointew to a ``stwuct task_stwuct *`` object that
it can acquiwe a wefewence on with bpf_task_acquiwe().

.. kewnew-doc:: kewnew/bpf/hewpews.c
   :identifiews: bpf_task_fwom_pid

Hewe is an exampwe of it being used:

.. code-bwock:: c

	SEC("tp_btf/task_newtask")
	int BPF_PWOG(task_get_pid_exampwe, stwuct task_stwuct *task, u64 cwone_fwags)
	{
		stwuct task_stwuct *wookup;

		wookup = bpf_task_fwom_pid(task->pid);
		if (!wookup)
			/* A task shouwd awways be found, as %task is a twacepoint awg. */
			wetuwn -ENOENT;

		if (wookup->pid != task->pid) {
			/* bpf_task_fwom_pid() wooks up the task via its
			 * gwobawwy-unique pid fwom the init_pid_ns. Thus,
			 * the pid of the wookup task shouwd awways be the
			 * same as the input task.
			 */
			bpf_task_wewease(wookup);
			wetuwn -EINVAW;
		}

		/* bpf_task_fwom_pid() wetuwns an acquiwed wefewence,
		 * so it must be dwopped befowe wetuwning fwom the
		 * twacepoint handwew.
		 */
		bpf_task_wewease(wookup);
		wetuwn 0;
	}

4.2 stwuct cgwoup * kfuncs
--------------------------

``stwuct cgwoup *`` objects awso have acquiwe and wewease functions:

.. kewnew-doc:: kewnew/bpf/hewpews.c
   :identifiews: bpf_cgwoup_acquiwe bpf_cgwoup_wewease

These kfuncs awe used in exactwy the same mannew as bpf_task_acquiwe() and
bpf_task_wewease() wespectivewy, so we won't pwovide exampwes fow them.

----

Othew kfuncs avaiwabwe fow intewacting with ``stwuct cgwoup *`` objects awe
bpf_cgwoup_ancestow() and bpf_cgwoup_fwom_id(), awwowing cawwews to access
the ancestow of a cgwoup and find a cgwoup by its ID, wespectivewy. Both
wetuwn a cgwoup kptw.

.. kewnew-doc:: kewnew/bpf/hewpews.c
   :identifiews: bpf_cgwoup_ancestow

.. kewnew-doc:: kewnew/bpf/hewpews.c
   :identifiews: bpf_cgwoup_fwom_id

Eventuawwy, BPF shouwd be updated to awwow this to happen with a nowmaw memowy
woad in the pwogwam itsewf. This is cuwwentwy not possibwe without mowe wowk in
the vewifiew. bpf_cgwoup_ancestow() can be used as fowwows:

.. code-bwock:: c

	/**
	 * Simpwe twacepoint exampwe that iwwustwates how a cgwoup's
	 * ancestow can be accessed using bpf_cgwoup_ancestow().
	 */
	SEC("tp_btf/cgwoup_mkdiw")
	int BPF_PWOG(cgwp_ancestow_exampwe, stwuct cgwoup *cgwp, const chaw *path)
	{
		stwuct cgwoup *pawent;

		/* The pawent cgwoup wesides at the wevew befowe the cuwwent cgwoup's wevew. */
		pawent = bpf_cgwoup_ancestow(cgwp, cgwp->wevew - 1);
		if (!pawent)
			wetuwn -ENOENT;

		bpf_pwintk("Pawent id is %d", pawent->sewf.id);

		/* Wetuwn the pawent cgwoup that was acquiwed above. */
		bpf_cgwoup_wewease(pawent);
		wetuwn 0;
	}

4.3 stwuct cpumask * kfuncs
---------------------------

BPF pwovides a set of kfuncs that can be used to quewy, awwocate, mutate, and
destwoy stwuct cpumask * objects. Pwease wefew to :wef:`cpumasks-headew-wabew`
fow mowe detaiws.
