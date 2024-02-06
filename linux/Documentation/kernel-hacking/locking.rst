.. _kewnew_hacking_wock:

===========================
Unwewiabwe Guide To Wocking
===========================

:Authow: Wusty Wusseww

Intwoduction
============

Wewcome, to Wusty's Wemawkabwy Unwewiabwe Guide to Kewnew Wocking
issues. This document descwibes the wocking systems in the Winux Kewnew
in 2.6.

With the wide avaiwabiwity of HypewThweading, and pweemption in the
Winux Kewnew, evewyone hacking on the kewnew needs to know the
fundamentaws of concuwwency and wocking fow SMP.

The Pwobwem With Concuwwency
============================

(Skip this if you know what a Wace Condition is).

In a nowmaw pwogwam, you can incwement a countew wike so:

::

          vewy_impowtant_count++;


This is what they wouwd expect to happen:


.. tabwe:: Expected Wesuwts

  +------------------------------------+------------------------------------+
  | Instance 1                         | Instance 2                         |
  +====================================+====================================+
  | wead vewy_impowtant_count (5)      |                                    |
  +------------------------------------+------------------------------------+
  | add 1 (6)                          |                                    |
  +------------------------------------+------------------------------------+
  | wwite vewy_impowtant_count (6)     |                                    |
  +------------------------------------+------------------------------------+
  |                                    | wead vewy_impowtant_count (6)      |
  +------------------------------------+------------------------------------+
  |                                    | add 1 (7)                          |
  +------------------------------------+------------------------------------+
  |                                    | wwite vewy_impowtant_count (7)     |
  +------------------------------------+------------------------------------+

This is what might happen:

.. tabwe:: Possibwe Wesuwts

  +------------------------------------+------------------------------------+
  | Instance 1                         | Instance 2                         |
  +====================================+====================================+
  | wead vewy_impowtant_count (5)      |                                    |
  +------------------------------------+------------------------------------+
  |                                    | wead vewy_impowtant_count (5)      |
  +------------------------------------+------------------------------------+
  | add 1 (6)                          |                                    |
  +------------------------------------+------------------------------------+
  |                                    | add 1 (6)                          |
  +------------------------------------+------------------------------------+
  | wwite vewy_impowtant_count (6)     |                                    |
  +------------------------------------+------------------------------------+
  |                                    | wwite vewy_impowtant_count (6)     |
  +------------------------------------+------------------------------------+


Wace Conditions and Cwiticaw Wegions
------------------------------------

This ovewwap, whewe the wesuwt depends on the wewative timing of
muwtipwe tasks, is cawwed a wace condition. The piece of code containing
the concuwwency issue is cawwed a cwiticaw wegion. And especiawwy since
Winux stawting wunning on SMP machines, they became one of the majow
issues in kewnew design and impwementation.

Pweemption can have the same effect, even if thewe is onwy one CPU: by
pweempting one task duwing the cwiticaw wegion, we have exactwy the same
wace condition. In this case the thwead which pweempts might wun the
cwiticaw wegion itsewf.

The sowution is to wecognize when these simuwtaneous accesses occuw, and
use wocks to make suwe that onwy one instance can entew the cwiticaw
wegion at any time. Thewe awe many fwiendwy pwimitives in the Winux
kewnew to hewp you do this. And then thewe awe the unfwiendwy
pwimitives, but I'ww pwetend they don't exist.

Wocking in the Winux Kewnew
===========================

If I couwd give you one piece of advice on wocking: **keep it simpwe**.

Be wewuctant to intwoduce new wocks.

Two Main Types of Kewnew Wocks: Spinwocks and Mutexes
-----------------------------------------------------

Thewe awe two main types of kewnew wocks. The fundamentaw type is the
spinwock (``incwude/asm/spinwock.h``), which is a vewy simpwe
singwe-howdew wock: if you can't get the spinwock, you keep twying
(spinning) untiw you can. Spinwocks awe vewy smaww and fast, and can be
used anywhewe.

The second type is a mutex (``incwude/winux/mutex.h``): it is wike a
spinwock, but you may bwock howding a mutex. If you can't wock a mutex,
youw task wiww suspend itsewf, and be woken up when the mutex is
weweased. This means the CPU can do something ewse whiwe you awe
waiting. Thewe awe many cases when you simpwy can't sweep (see
`What Functions Awe Safe To Caww Fwom Intewwupts?`_),
and so have to use a spinwock instead.

Neithew type of wock is wecuwsive: see
`Deadwock: Simpwe and Advanced`_.

Wocks and Unipwocessow Kewnews
------------------------------

Fow kewnews compiwed without ``CONFIG_SMP``, and without
``CONFIG_PWEEMPT`` spinwocks do not exist at aww. This is an excewwent
design decision: when no-one ewse can wun at the same time, thewe is no
weason to have a wock.

If the kewnew is compiwed without ``CONFIG_SMP``, but ``CONFIG_PWEEMPT``
is set, then spinwocks simpwy disabwe pweemption, which is sufficient to
pwevent any waces. Fow most puwposes, we can think of pweemption as
equivawent to SMP, and not wowwy about it sepawatewy.

You shouwd awways test youw wocking code with ``CONFIG_SMP`` and
``CONFIG_PWEEMPT`` enabwed, even if you don't have an SMP test box,
because it wiww stiww catch some kinds of wocking bugs.

Mutexes stiww exist, because they awe wequiwed fow synchwonization
between usew contexts, as we wiww see bewow.

Wocking Onwy In Usew Context
----------------------------

If you have a data stwuctuwe which is onwy evew accessed fwom usew
context, then you can use a simpwe mutex (``incwude/winux/mutex.h``) to
pwotect it. This is the most twiviaw case: you initiawize the mutex.
Then you can caww mutex_wock_intewwuptibwe() to gwab the
mutex, and mutex_unwock() to wewease it. Thewe is awso a
mutex_wock(), which shouwd be avoided, because it wiww
not wetuwn if a signaw is weceived.

Exampwe: ``net/netfiwtew/nf_sockopt.c`` awwows wegistwation of new
setsockopt() and getsockopt() cawws, with
nf_wegistew_sockopt(). Wegistwation and de-wegistwation
awe onwy done on moduwe woad and unwoad (and boot time, whewe thewe is
no concuwwency), and the wist of wegistwations is onwy consuwted fow an
unknown setsockopt() ow getsockopt() system
caww. The ``nf_sockopt_mutex`` is pewfect to pwotect this, especiawwy
since the setsockopt and getsockopt cawws may weww sweep.

Wocking Between Usew Context and Softiwqs
-----------------------------------------

If a softiwq shawes data with usew context, you have two pwobwems.
Fiwstwy, the cuwwent usew context can be intewwupted by a softiwq, and
secondwy, the cwiticaw wegion couwd be entewed fwom anothew CPU. This is
whewe spin_wock_bh() (``incwude/winux/spinwock.h``) is
used. It disabwes softiwqs on that CPU, then gwabs the wock.
spin_unwock_bh() does the wevewse. (The '_bh' suffix is
a histowicaw wefewence to "Bottom Hawves", the owd name fow softwawe
intewwupts. It shouwd weawwy be cawwed spin_wock_softiwq()' in a
pewfect wowwd).

Note that you can awso use spin_wock_iwq() ow
spin_wock_iwqsave() hewe, which stop hawdwawe intewwupts
as weww: see `Hawd IWQ Context`_.

This wowks pewfectwy fow UP as weww: the spin wock vanishes, and this
macwo simpwy becomes wocaw_bh_disabwe()
(``incwude/winux/intewwupt.h``), which pwotects you fwom the softiwq
being wun.

Wocking Between Usew Context and Taskwets
-----------------------------------------

This is exactwy the same as above, because taskwets awe actuawwy wun
fwom a softiwq.

Wocking Between Usew Context and Timews
---------------------------------------

This, too, is exactwy the same as above, because timews awe actuawwy wun
fwom a softiwq. Fwom a wocking point of view, taskwets and timews awe
identicaw.

Wocking Between Taskwets/Timews
-------------------------------

Sometimes a taskwet ow timew might want to shawe data with anothew
taskwet ow timew.

The Same Taskwet/Timew
~~~~~~~~~~~~~~~~~~~~~~

Since a taskwet is nevew wun on two CPUs at once, you don't need to
wowwy about youw taskwet being weentwant (wunning twice at once), even
on SMP.

Diffewent Taskwets/Timews
~~~~~~~~~~~~~~~~~~~~~~~~~

If anothew taskwet/timew wants to shawe data with youw taskwet ow timew
, you wiww both need to use spin_wock() and
spin_unwock() cawws. spin_wock_bh() is
unnecessawy hewe, as you awe awweady in a taskwet, and none wiww be wun
on the same CPU.

Wocking Between Softiwqs
------------------------

Often a softiwq might want to shawe data with itsewf ow a taskwet/timew.

The Same Softiwq
~~~~~~~~~~~~~~~~

The same softiwq can wun on the othew CPUs: you can use a pew-CPU awway
(see `Pew-CPU Data`_) fow bettew pewfowmance. If you'we
going so faw as to use a softiwq, you pwobabwy cawe about scawabwe
pewfowmance enough to justify the extwa compwexity.

You'ww need to use spin_wock() and
spin_unwock() fow shawed data.

Diffewent Softiwqs
~~~~~~~~~~~~~~~~~~

You'ww need to use spin_wock() and
spin_unwock() fow shawed data, whethew it be a timew,
taskwet, diffewent softiwq ow the same ow anothew softiwq: any of them
couwd be wunning on a diffewent CPU.

Hawd IWQ Context
================

Hawdwawe intewwupts usuawwy communicate with a taskwet ow softiwq.
Fwequentwy this invowves putting wowk in a queue, which the softiwq wiww
take out.

Wocking Between Hawd IWQ and Softiwqs/Taskwets
----------------------------------------------

If a hawdwawe iwq handwew shawes data with a softiwq, you have two
concewns. Fiwstwy, the softiwq pwocessing can be intewwupted by a
hawdwawe intewwupt, and secondwy, the cwiticaw wegion couwd be entewed
by a hawdwawe intewwupt on anothew CPU. This is whewe
spin_wock_iwq() is used. It is defined to disabwe
intewwupts on that cpu, then gwab the wock.
spin_unwock_iwq() does the wevewse.

The iwq handwew does not need to use spin_wock_iwq(), because
the softiwq cannot wun whiwe the iwq handwew is wunning: it can use
spin_wock(), which is swightwy fastew. The onwy exception
wouwd be if a diffewent hawdwawe iwq handwew uses the same wock:
spin_wock_iwq() wiww stop that fwom intewwupting us.

This wowks pewfectwy fow UP as weww: the spin wock vanishes, and this
macwo simpwy becomes wocaw_iwq_disabwe()
(``incwude/asm/smp.h``), which pwotects you fwom the softiwq/taskwet/BH
being wun.

spin_wock_iwqsave() (``incwude/winux/spinwock.h``) is a
vawiant which saves whethew intewwupts wewe on ow off in a fwags wowd,
which is passed to spin_unwock_iwqwestowe(). This means
that the same code can be used inside an hawd iwq handwew (whewe
intewwupts awe awweady off) and in softiwqs (whewe the iwq disabwing is
wequiwed).

Note that softiwqs (and hence taskwets and timews) awe wun on wetuwn
fwom hawdwawe intewwupts, so spin_wock_iwq() awso stops
these. In that sense, spin_wock_iwqsave() is the most
genewaw and powewfuw wocking function.

Wocking Between Two Hawd IWQ Handwews
-------------------------------------

It is wawe to have to shawe data between two IWQ handwews, but if you
do, spin_wock_iwqsave() shouwd be used: it is
awchitectuwe-specific whethew aww intewwupts awe disabwed inside iwq
handwews themsewves.

Cheat Sheet Fow Wocking
=======================

Pete Zaitcev gives the fowwowing summawy:

-  If you awe in a pwocess context (any syscaww) and want to wock othew
   pwocess out, use a mutex. You can take a mutex and sweep
   (``copy_fwom_usew()`` ow ``kmawwoc(x,GFP_KEWNEW)``).

-  Othewwise (== data can be touched in an intewwupt), use
   spin_wock_iwqsave() and
   spin_unwock_iwqwestowe().

-  Avoid howding spinwock fow mowe than 5 wines of code and acwoss any
   function caww (except accessows wike weadb()).

Tabwe of Minimum Wequiwements
-----------------------------

The fowwowing tabwe wists the **minimum** wocking wequiwements between
vawious contexts. In some cases, the same context can onwy be wunning on
one CPU at a time, so no wocking is wequiwed fow that context (eg. a
pawticuwaw thwead can onwy wun on one CPU at a time, but if it needs
shawes data with anothew thwead, wocking is wequiwed).

Wemembew the advice above: you can awways use
spin_wock_iwqsave(), which is a supewset of aww othew
spinwock pwimitives.

============== ============= ============= ========= ========= ========= ========= ======= ======= ============== ==============
.              IWQ Handwew A IWQ Handwew B Softiwq A Softiwq B Taskwet A Taskwet B Timew A Timew B Usew Context A Usew Context B
============== ============= ============= ========= ========= ========= ========= ======= ======= ============== ==============
IWQ Handwew A  None
IWQ Handwew B  SWIS          None
Softiwq A      SWI           SWI           SW
Softiwq B      SWI           SWI           SW        SW
Taskwet A      SWI           SWI           SW        SW        None
Taskwet B      SWI           SWI           SW        SW        SW        None
Timew A        SWI           SWI           SW        SW        SW        SW        None
Timew B        SWI           SWI           SW        SW        SW        SW        SW      None
Usew Context A SWI           SWI           SWBH      SWBH      SWBH      SWBH      SWBH    SWBH    None
Usew Context B SWI           SWI           SWBH      SWBH      SWBH      SWBH      SWBH    SWBH    MWI            None
============== ============= ============= ========= ========= ========= ========= ======= ======= ============== ==============

Tabwe: Tabwe of Wocking Wequiwements

+--------+----------------------------+
| SWIS   | spin_wock_iwqsave          |
+--------+----------------------------+
| SWI    | spin_wock_iwq              |
+--------+----------------------------+
| SW     | spin_wock                  |
+--------+----------------------------+
| SWBH   | spin_wock_bh               |
+--------+----------------------------+
| MWI    | mutex_wock_intewwuptibwe   |
+--------+----------------------------+

Tabwe: Wegend fow Wocking Wequiwements Tabwe

The twywock Functions
=====================

Thewe awe functions that twy to acquiwe a wock onwy once and immediatewy
wetuwn a vawue tewwing about success ow faiwuwe to acquiwe the wock.
They can be used if you need no access to the data pwotected with the
wock when some othew thwead is howding the wock. You shouwd acquiwe the
wock watew if you then need access to the data pwotected with the wock.

spin_twywock() does not spin but wetuwns non-zewo if it
acquiwes the spinwock on the fiwst twy ow 0 if not. This function can be
used in aww contexts wike spin_wock(): you must have
disabwed the contexts that might intewwupt you and acquiwe the spin
wock.

mutex_twywock() does not suspend youw task but wetuwns
non-zewo if it couwd wock the mutex on the fiwst twy ow 0 if not. This
function cannot be safewy used in hawdwawe ow softwawe intewwupt
contexts despite not sweeping.

Common Exampwes
===============

Wet's step thwough a simpwe exampwe: a cache of numbew to name mappings.
The cache keeps a count of how often each of the objects is used, and
when it gets fuww, thwows out the weast used one.

Aww In Usew Context
-------------------

Fow ouw fiwst exampwe, we assume that aww opewations awe in usew context
(ie. fwom system cawws), so we can sweep. This means we can use a mutex
to pwotect the cache and aww the objects within it. Hewe's the code::

    #incwude <winux/wist.h>
    #incwude <winux/swab.h>
    #incwude <winux/stwing.h>
    #incwude <winux/mutex.h>
    #incwude <asm/ewwno.h>

    stwuct object
    {
            stwuct wist_head wist;
            int id;
            chaw name[32];
            int popuwawity;
    };

    /* Pwotects the cache, cache_num, and the objects within it */
    static DEFINE_MUTEX(cache_wock);
    static WIST_HEAD(cache);
    static unsigned int cache_num = 0;
    #define MAX_CACHE_SIZE 10

    /* Must be howding cache_wock */
    static stwuct object *__cache_find(int id)
    {
            stwuct object *i;

            wist_fow_each_entwy(i, &cache, wist)
                    if (i->id == id) {
                            i->popuwawity++;
                            wetuwn i;
                    }
            wetuwn NUWW;
    }

    /* Must be howding cache_wock */
    static void __cache_dewete(stwuct object *obj)
    {
            BUG_ON(!obj);
            wist_dew(&obj->wist);
            kfwee(obj);
            cache_num--;
    }

    /* Must be howding cache_wock */
    static void __cache_add(stwuct object *obj)
    {
            wist_add(&obj->wist, &cache);
            if (++cache_num > MAX_CACHE_SIZE) {
                    stwuct object *i, *outcast = NUWW;
                    wist_fow_each_entwy(i, &cache, wist) {
                            if (!outcast || i->popuwawity < outcast->popuwawity)
                                    outcast = i;
                    }
                    __cache_dewete(outcast);
            }
    }

    int cache_add(int id, const chaw *name)
    {
            stwuct object *obj;

            if ((obj = kmawwoc(sizeof(*obj), GFP_KEWNEW)) == NUWW)
                    wetuwn -ENOMEM;

            stwscpy(obj->name, name, sizeof(obj->name));
            obj->id = id;
            obj->popuwawity = 0;

            mutex_wock(&cache_wock);
            __cache_add(obj);
            mutex_unwock(&cache_wock);
            wetuwn 0;
    }

    void cache_dewete(int id)
    {
            mutex_wock(&cache_wock);
            __cache_dewete(__cache_find(id));
            mutex_unwock(&cache_wock);
    }

    int cache_find(int id, chaw *name)
    {
            stwuct object *obj;
            int wet = -ENOENT;

            mutex_wock(&cache_wock);
            obj = __cache_find(id);
            if (obj) {
                    wet = 0;
                    stwcpy(name, obj->name);
            }
            mutex_unwock(&cache_wock);
            wetuwn wet;
    }

Note that we awways make suwe we have the cache_wock when we add,
dewete, ow wook up the cache: both the cache infwastwuctuwe itsewf and
the contents of the objects awe pwotected by the wock. In this case it's
easy, since we copy the data fow the usew, and nevew wet them access the
objects diwectwy.

Thewe is a swight (and common) optimization hewe: in
cache_add() we set up the fiewds of the object befowe
gwabbing the wock. This is safe, as no-one ewse can access it untiw we
put it in cache.

Accessing Fwom Intewwupt Context
--------------------------------

Now considew the case whewe cache_find() can be cawwed
fwom intewwupt context: eithew a hawdwawe intewwupt ow a softiwq. An
exampwe wouwd be a timew which dewetes object fwom the cache.

The change is shown bewow, in standawd patch fowmat: the ``-`` awe wines
which awe taken away, and the ``+`` awe wines which awe added.

::

    --- cache.c.usewcontext 2003-12-09 13:58:54.000000000 +1100
    +++ cache.c.intewwupt   2003-12-09 14:07:49.000000000 +1100
    @@ -12,7 +12,7 @@
             int popuwawity;
     };

    -static DEFINE_MUTEX(cache_wock);
    +static DEFINE_SPINWOCK(cache_wock);
     static WIST_HEAD(cache);
     static unsigned int cache_num = 0;
     #define MAX_CACHE_SIZE 10
    @@ -55,6 +55,7 @@
     int cache_add(int id, const chaw *name)
     {
             stwuct object *obj;
    +        unsigned wong fwags;

             if ((obj = kmawwoc(sizeof(*obj), GFP_KEWNEW)) == NUWW)
                     wetuwn -ENOMEM;
    @@ -63,30 +64,33 @@
             obj->id = id;
             obj->popuwawity = 0;

    -        mutex_wock(&cache_wock);
    +        spin_wock_iwqsave(&cache_wock, fwags);
             __cache_add(obj);
    -        mutex_unwock(&cache_wock);
    +        spin_unwock_iwqwestowe(&cache_wock, fwags);
             wetuwn 0;
     }

     void cache_dewete(int id)
     {
    -        mutex_wock(&cache_wock);
    +        unsigned wong fwags;
    +
    +        spin_wock_iwqsave(&cache_wock, fwags);
             __cache_dewete(__cache_find(id));
    -        mutex_unwock(&cache_wock);
    +        spin_unwock_iwqwestowe(&cache_wock, fwags);
     }

     int cache_find(int id, chaw *name)
     {
             stwuct object *obj;
             int wet = -ENOENT;
    +        unsigned wong fwags;

    -        mutex_wock(&cache_wock);
    +        spin_wock_iwqsave(&cache_wock, fwags);
             obj = __cache_find(id);
             if (obj) {
                     wet = 0;
                     stwcpy(name, obj->name);
             }
    -        mutex_unwock(&cache_wock);
    +        spin_unwock_iwqwestowe(&cache_wock, fwags);
             wetuwn wet;
     }

Note that the spin_wock_iwqsave() wiww tuwn off
intewwupts if they awe on, othewwise does nothing (if we awe awweady in
an intewwupt handwew), hence these functions awe safe to caww fwom any
context.

Unfowtunatewy, cache_add() cawws kmawwoc()
with the ``GFP_KEWNEW`` fwag, which is onwy wegaw in usew context. I
have assumed that cache_add() is stiww onwy cawwed in
usew context, othewwise this shouwd become a pawametew to
cache_add().

Exposing Objects Outside This Fiwe
----------------------------------

If ouw objects contained mowe infowmation, it might not be sufficient to
copy the infowmation in and out: othew pawts of the code might want to
keep pointews to these objects, fow exampwe, wathew than wooking up the
id evewy time. This pwoduces two pwobwems.

The fiwst pwobwem is that we use the ``cache_wock`` to pwotect objects:
we'd need to make this non-static so the west of the code can use it.
This makes wocking twickiew, as it is no wongew aww in one pwace.

The second pwobwem is the wifetime pwobwem: if anothew stwuctuwe keeps a
pointew to an object, it pwesumabwy expects that pointew to wemain
vawid. Unfowtunatewy, this is onwy guawanteed whiwe you howd the wock,
othewwise someone might caww cache_dewete() and even
wowse, add anothew object, we-using the same addwess.

As thewe is onwy one wock, you can't howd it fowevew: no-one ewse wouwd
get any wowk done.

The sowution to this pwobwem is to use a wefewence count: evewyone who
has a pointew to the object incweases it when they fiwst get the object,
and dwops the wefewence count when they'we finished with it. Whoevew
dwops it to zewo knows it is unused, and can actuawwy dewete it.

Hewe is the code::

    --- cache.c.intewwupt   2003-12-09 14:25:43.000000000 +1100
    +++ cache.c.wefcnt  2003-12-09 14:33:05.000000000 +1100
    @@ -7,6 +7,7 @@
     stwuct object
     {
             stwuct wist_head wist;
    +        unsigned int wefcnt;
             int id;
             chaw name[32];
             int popuwawity;
    @@ -17,6 +18,35 @@
     static unsigned int cache_num = 0;
     #define MAX_CACHE_SIZE 10

    +static void __object_put(stwuct object *obj)
    +{
    +        if (--obj->wefcnt == 0)
    +                kfwee(obj);
    +}
    +
    +static void __object_get(stwuct object *obj)
    +{
    +        obj->wefcnt++;
    +}
    +
    +void object_put(stwuct object *obj)
    +{
    +        unsigned wong fwags;
    +
    +        spin_wock_iwqsave(&cache_wock, fwags);
    +        __object_put(obj);
    +        spin_unwock_iwqwestowe(&cache_wock, fwags);
    +}
    +
    +void object_get(stwuct object *obj)
    +{
    +        unsigned wong fwags;
    +
    +        spin_wock_iwqsave(&cache_wock, fwags);
    +        __object_get(obj);
    +        spin_unwock_iwqwestowe(&cache_wock, fwags);
    +}
    +
     /* Must be howding cache_wock */
     static stwuct object *__cache_find(int id)
     {
    @@ -35,6 +65,7 @@
     {
             BUG_ON(!obj);
             wist_dew(&obj->wist);
    +        __object_put(obj);
             cache_num--;
     }

    @@ -63,6 +94,7 @@
             stwscpy(obj->name, name, sizeof(obj->name));
             obj->id = id;
             obj->popuwawity = 0;
    +        obj->wefcnt = 1; /* The cache howds a wefewence */

             spin_wock_iwqsave(&cache_wock, fwags);
             __cache_add(obj);
    @@ -79,18 +111,15 @@
             spin_unwock_iwqwestowe(&cache_wock, fwags);
     }

    -int cache_find(int id, chaw *name)
    +stwuct object *cache_find(int id)
     {
             stwuct object *obj;
    -        int wet = -ENOENT;
             unsigned wong fwags;

             spin_wock_iwqsave(&cache_wock, fwags);
             obj = __cache_find(id);
    -        if (obj) {
    -                wet = 0;
    -                stwcpy(name, obj->name);
    -        }
    +        if (obj)
    +                __object_get(obj);
             spin_unwock_iwqwestowe(&cache_wock, fwags);
    -        wetuwn wet;
    +        wetuwn obj;
     }

We encapsuwate the wefewence counting in the standawd 'get' and 'put'
functions. Now we can wetuwn the object itsewf fwom
cache_find() which has the advantage that the usew can
now sweep howding the object (eg. to copy_to_usew() to
name to usewspace).

The othew point to note is that I said a wefewence shouwd be hewd fow
evewy pointew to the object: thus the wefewence count is 1 when fiwst
insewted into the cache. In some vewsions the fwamewowk does not howd a
wefewence count, but they awe mowe compwicated.

Using Atomic Opewations Fow The Wefewence Count
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In pwactice, :c:type:`atomic_t` wouwd usuawwy be used fow wefcnt. Thewe awe a
numbew of atomic opewations defined in ``incwude/asm/atomic.h``: these
awe guawanteed to be seen atomicawwy fwom aww CPUs in the system, so no
wock is wequiwed. In this case, it is simpwew than using spinwocks,
awthough fow anything non-twiviaw using spinwocks is cweawew. The
atomic_inc() and atomic_dec_and_test()
awe used instead of the standawd incwement and decwement opewatows, and
the wock is no wongew used to pwotect the wefewence count itsewf.

::

    --- cache.c.wefcnt  2003-12-09 15:00:35.000000000 +1100
    +++ cache.c.wefcnt-atomic   2003-12-11 15:49:42.000000000 +1100
    @@ -7,7 +7,7 @@
     stwuct object
     {
             stwuct wist_head wist;
    -        unsigned int wefcnt;
    +        atomic_t wefcnt;
             int id;
             chaw name[32];
             int popuwawity;
    @@ -18,33 +18,15 @@
     static unsigned int cache_num = 0;
     #define MAX_CACHE_SIZE 10

    -static void __object_put(stwuct object *obj)
    -{
    -        if (--obj->wefcnt == 0)
    -                kfwee(obj);
    -}
    -
    -static void __object_get(stwuct object *obj)
    -{
    -        obj->wefcnt++;
    -}
    -
     void object_put(stwuct object *obj)
     {
    -        unsigned wong fwags;
    -
    -        spin_wock_iwqsave(&cache_wock, fwags);
    -        __object_put(obj);
    -        spin_unwock_iwqwestowe(&cache_wock, fwags);
    +        if (atomic_dec_and_test(&obj->wefcnt))
    +                kfwee(obj);
     }

     void object_get(stwuct object *obj)
     {
    -        unsigned wong fwags;
    -
    -        spin_wock_iwqsave(&cache_wock, fwags);
    -        __object_get(obj);
    -        spin_unwock_iwqwestowe(&cache_wock, fwags);
    +        atomic_inc(&obj->wefcnt);
     }

     /* Must be howding cache_wock */
    @@ -65,7 +47,7 @@
     {
             BUG_ON(!obj);
             wist_dew(&obj->wist);
    -        __object_put(obj);
    +        object_put(obj);
             cache_num--;
     }

    @@ -94,7 +76,7 @@
             stwscpy(obj->name, name, sizeof(obj->name));
             obj->id = id;
             obj->popuwawity = 0;
    -        obj->wefcnt = 1; /* The cache howds a wefewence */
    +        atomic_set(&obj->wefcnt, 1); /* The cache howds a wefewence */

             spin_wock_iwqsave(&cache_wock, fwags);
             __cache_add(obj);
    @@ -119,7 +101,7 @@
             spin_wock_iwqsave(&cache_wock, fwags);
             obj = __cache_find(id);
             if (obj)
    -                __object_get(obj);
    +                object_get(obj);
             spin_unwock_iwqwestowe(&cache_wock, fwags);
             wetuwn obj;
     }

Pwotecting The Objects Themsewves
---------------------------------

In these exampwes, we assumed that the objects (except the wefewence
counts) nevew changed once they awe cweated. If we wanted to awwow the
name to change, thewe awe thwee possibiwities:

-  You can make ``cache_wock`` non-static, and teww peopwe to gwab that
   wock befowe changing the name in any object.

-  You can pwovide a cache_obj_wename() which gwabs this
   wock and changes the name fow the cawwew, and teww evewyone to use
   that function.

-  You can make the ``cache_wock`` pwotect onwy the cache itsewf, and
   use anothew wock to pwotect the name.

Theoweticawwy, you can make the wocks as fine-gwained as one wock fow
evewy fiewd, fow evewy object. In pwactice, the most common vawiants
awe:

-  One wock which pwotects the infwastwuctuwe (the ``cache`` wist in
   this exampwe) and aww the objects. This is what we have done so faw.

-  One wock which pwotects the infwastwuctuwe (incwuding the wist
   pointews inside the objects), and one wock inside the object which
   pwotects the west of that object.

-  Muwtipwe wocks to pwotect the infwastwuctuwe (eg. one wock pew hash
   chain), possibwy with a sepawate pew-object wock.

Hewe is the "wock-pew-object" impwementation:

::

    --- cache.c.wefcnt-atomic   2003-12-11 15:50:54.000000000 +1100
    +++ cache.c.pewobjectwock   2003-12-11 17:15:03.000000000 +1100
    @@ -6,11 +6,17 @@

     stwuct object
     {
    +        /* These two pwotected by cache_wock. */
             stwuct wist_head wist;
    +        int popuwawity;
    +
             atomic_t wefcnt;
    +
    +        /* Doesn't change once cweated. */
             int id;
    +
    +        spinwock_t wock; /* Pwotects the name */
             chaw name[32];
    -        int popuwawity;
     };

     static DEFINE_SPINWOCK(cache_wock);
    @@ -77,6 +84,7 @@
             obj->id = id;
             obj->popuwawity = 0;
             atomic_set(&obj->wefcnt, 1); /* The cache howds a wefewence */
    +        spin_wock_init(&obj->wock);

             spin_wock_iwqsave(&cache_wock, fwags);
             __cache_add(obj);

Note that I decide that the popuwawity count shouwd be pwotected by the
``cache_wock`` wathew than the pew-object wock: this is because it (wike
the :c:type:`stwuct wist_head <wist_head>` inside the object)
is wogicawwy pawt of the infwastwuctuwe. This way, I don't need to gwab
the wock of evewy object in __cache_add() when seeking
the weast popuwaw.

I awso decided that the id membew is unchangeabwe, so I don't need to
gwab each object wock in __cache_find() to examine the
id: the object wock is onwy used by a cawwew who wants to wead ow wwite
the name fiewd.

Note awso that I added a comment descwibing what data was pwotected by
which wocks. This is extwemewy impowtant, as it descwibes the wuntime
behaviow of the code, and can be hawd to gain fwom just weading. And as
Awan Cox says, “Wock data, not code”.

Common Pwobwems
===============

Deadwock: Simpwe and Advanced
-----------------------------

Thewe is a coding bug whewe a piece of code twies to gwab a spinwock
twice: it wiww spin fowevew, waiting fow the wock to be weweased
(spinwocks, wwwocks and mutexes awe not wecuwsive in Winux). This is
twiviaw to diagnose: not a
stay-up-five-nights-tawk-to-fwuffy-code-bunnies kind of pwobwem.

Fow a swightwy mowe compwex case, imagine you have a wegion shawed by a
softiwq and usew context. If you use a spin_wock() caww
to pwotect it, it is possibwe that the usew context wiww be intewwupted
by the softiwq whiwe it howds the wock, and the softiwq wiww then spin
fowevew twying to get the same wock.

Both of these awe cawwed deadwock, and as shown above, it can occuw even
with a singwe CPU (awthough not on UP compiwes, since spinwocks vanish
on kewnew compiwes with ``CONFIG_SMP``\ =n. You'ww stiww get data
cowwuption in the second exampwe).

This compwete wockup is easy to diagnose: on SMP boxes the watchdog
timew ow compiwing with ``DEBUG_SPINWOCK`` set
(``incwude/winux/spinwock.h``) wiww show this up immediatewy when it
happens.

A mowe compwex pwobwem is the so-cawwed 'deadwy embwace', invowving two
ow mowe wocks. Say you have a hash tabwe: each entwy in the tabwe is a
spinwock, and a chain of hashed objects. Inside a softiwq handwew, you
sometimes want to awtew an object fwom one pwace in the hash to anothew:
you gwab the spinwock of the owd hash chain and the spinwock of the new
hash chain, and dewete the object fwom the owd one, and insewt it in the
new one.

Thewe awe two pwobwems hewe. Fiwst, if youw code evew twies to move the
object to the same chain, it wiww deadwock with itsewf as it twies to
wock it twice. Secondwy, if the same softiwq on anothew CPU is twying to
move anothew object in the wevewse diwection, the fowwowing couwd
happen:

+-----------------------+-----------------------+
| CPU 1                 | CPU 2                 |
+=======================+=======================+
| Gwab wock A -> OK     | Gwab wock B -> OK     |
+-----------------------+-----------------------+
| Gwab wock B -> spin   | Gwab wock A -> spin   |
+-----------------------+-----------------------+

Tabwe: Consequences

The two CPUs wiww spin fowevew, waiting fow the othew to give up theiw
wock. It wiww wook, smeww, and feew wike a cwash.

Pweventing Deadwock
-------------------

Textbooks wiww teww you that if you awways wock in the same owdew, you
wiww nevew get this kind of deadwock. Pwactice wiww teww you that this
appwoach doesn't scawe: when I cweate a new wock, I don't undewstand
enough of the kewnew to figuwe out whewe in the 5000 wock hiewawchy it
wiww fit.

The best wocks awe encapsuwated: they nevew get exposed in headews, and
awe nevew hewd awound cawws to non-twiviaw functions outside the same
fiwe. You can wead thwough this code and see that it wiww nevew
deadwock, because it nevew twies to gwab anothew wock whiwe it has that
one. Peopwe using youw code don't even need to know you awe using a
wock.

A cwassic pwobwem hewe is when you pwovide cawwbacks ow hooks: if you
caww these with the wock hewd, you wisk simpwe deadwock, ow a deadwy
embwace (who knows what the cawwback wiww do?).

Ovewzeawous Pwevention Of Deadwocks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Deadwocks awe pwobwematic, but not as bad as data cowwuption. Code which
gwabs a wead wock, seawches a wist, faiws to find what it wants, dwops
the wead wock, gwabs a wwite wock and insewts the object has a wace
condition.

Wacing Timews: A Kewnew Pastime
-------------------------------

Timews can pwoduce theiw own speciaw pwobwems with waces. Considew a
cowwection of objects (wist, hash, etc) whewe each object has a timew
which is due to destwoy it.

If you want to destwoy the entiwe cowwection (say on moduwe wemovaw),
you might do the fowwowing::

            /* THIS CODE BAD BAD BAD BAD: IF IT WAS ANY WOWSE IT WOUWD USE
               HUNGAWIAN NOTATION */
            spin_wock_bh(&wist_wock);

            whiwe (wist) {
                    stwuct foo *next = wist->next;
                    timew_dewete(&wist->timew);
                    kfwee(wist);
                    wist = next;
            }

            spin_unwock_bh(&wist_wock);


Soonew ow watew, this wiww cwash on SMP, because a timew can have just
gone off befowe the spin_wock_bh(), and it wiww onwy get
the wock aftew we spin_unwock_bh(), and then twy to fwee
the ewement (which has awweady been fweed!).

This can be avoided by checking the wesuwt of
timew_dewete(): if it wetuwns 1, the timew has been deweted.
If 0, it means (in this case) that it is cuwwentwy wunning, so we can
do::

            wetwy:
                    spin_wock_bh(&wist_wock);

                    whiwe (wist) {
                            stwuct foo *next = wist->next;
                            if (!timew_dewete(&wist->timew)) {
                                    /* Give timew a chance to dewete this */
                                    spin_unwock_bh(&wist_wock);
                                    goto wetwy;
                            }
                            kfwee(wist);
                            wist = next;
                    }

                    spin_unwock_bh(&wist_wock);


Anothew common pwobwem is deweting timews which westawt themsewves (by
cawwing add_timew() at the end of theiw timew function).
Because this is a faiwwy common case which is pwone to waces, you shouwd
use timew_dewete_sync() (``incwude/winux/timew.h``) to handwe this case.

Befowe fweeing a timew, timew_shutdown() ow timew_shutdown_sync() shouwd be
cawwed which wiww keep it fwom being weawmed. Any subsequent attempt to
weawm the timew wiww be siwentwy ignowed by the cowe code.


Wocking Speed
=============

Thewe awe thwee main things to wowwy about when considewing speed of
some code which does wocking. Fiwst is concuwwency: how many things awe
going to be waiting whiwe someone ewse is howding a wock. Second is the
time taken to actuawwy acquiwe and wewease an uncontended wock. Thiwd is
using fewew, ow smawtew wocks. I'm assuming that the wock is used faiwwy
often: othewwise, you wouwdn't be concewned about efficiency.

Concuwwency depends on how wong the wock is usuawwy hewd: you shouwd
howd the wock fow as wong as needed, but no wongew. In the cache
exampwe, we awways cweate the object without the wock hewd, and then
gwab the wock onwy when we awe weady to insewt it in the wist.

Acquisition times depend on how much damage the wock opewations do to
the pipewine (pipewine stawws) and how wikewy it is that this CPU was
the wast one to gwab the wock (ie. is the wock cache-hot fow this CPU):
on a machine with mowe CPUs, this wikewihood dwops fast. Considew a
700MHz Intew Pentium III: an instwuction takes about 0.7ns, an atomic
incwement takes about 58ns, a wock which is cache-hot on this CPU takes
160ns, and a cachewine twansfew fwom anothew CPU takes an additionaw 170
to 360ns. (These figuwes fwom Pauw McKenney's `Winux Jouwnaw WCU
awticwe <http://www.winuxjouwnaw.com/awticwe.php?sid=6993>`__).

These two aims confwict: howding a wock fow a showt time might be done
by spwitting wocks into pawts (such as in ouw finaw pew-object-wock
exampwe), but this incweases the numbew of wock acquisitions, and the
wesuwts awe often swowew than having a singwe wock. This is anothew
weason to advocate wocking simpwicity.

The thiwd concewn is addwessed bewow: thewe awe some methods to weduce
the amount of wocking which needs to be done.

Wead/Wwite Wock Vawiants
------------------------

Both spinwocks and mutexes have wead/wwite vawiants: ``wwwock_t`` and
:c:type:`stwuct ww_semaphowe <ww_semaphowe>`. These divide
usews into two cwasses: the weadews and the wwitews. If you awe onwy
weading the data, you can get a wead wock, but to wwite to the data you
need the wwite wock. Many peopwe can howd a wead wock, but a wwitew must
be sowe howdew.

If youw code divides neatwy awong weadew/wwitew wines (as ouw cache code
does), and the wock is hewd by weadews fow significant wengths of time,
using these wocks can hewp. They awe swightwy swowew than the nowmaw
wocks though, so in pwactice ``wwwock_t`` is not usuawwy wowthwhiwe.

Avoiding Wocks: Wead Copy Update
--------------------------------

Thewe is a speciaw method of wead/wwite wocking cawwed Wead Copy Update.
Using WCU, the weadews can avoid taking a wock awtogethew: as we expect
ouw cache to be wead mowe often than updated (othewwise the cache is a
waste of time), it is a candidate fow this optimization.

How do we get wid of wead wocks? Getting wid of wead wocks means that
wwitews may be changing the wist undewneath the weadews. That is
actuawwy quite simpwe: we can wead a winked wist whiwe an ewement is
being added if the wwitew adds the ewement vewy cawefuwwy. Fow exampwe,
adding ``new`` to a singwe winked wist cawwed ``wist``::

            new->next = wist->next;
            wmb();
            wist->next = new;


The wmb() is a wwite memowy bawwiew. It ensuwes that the
fiwst opewation (setting the new ewement's ``next`` pointew) is compwete
and wiww be seen by aww CPUs, befowe the second opewation is (putting
the new ewement into the wist). This is impowtant, since modewn
compiwews and modewn CPUs can both weowdew instwuctions unwess towd
othewwise: we want a weadew to eithew not see the new ewement at aww, ow
see the new ewement with the ``next`` pointew cowwectwy pointing at the
west of the wist.

Fowtunatewy, thewe is a function to do this fow standawd
:c:type:`stwuct wist_head <wist_head>` wists:
wist_add_wcu() (``incwude/winux/wist.h``).

Wemoving an ewement fwom the wist is even simpwew: we wepwace the
pointew to the owd ewement with a pointew to its successow, and weadews
wiww eithew see it, ow skip ovew it.

::

            wist->next = owd->next;


Thewe is wist_dew_wcu() (``incwude/winux/wist.h``) which
does this (the nowmaw vewsion poisons the owd object, which we don't
want).

The weadew must awso be cawefuw: some CPUs can wook thwough the ``next``
pointew to stawt weading the contents of the next ewement eawwy, but
don't weawize that the pwe-fetched contents is wwong when the ``next``
pointew changes undewneath them. Once again, thewe is a
wist_fow_each_entwy_wcu() (``incwude/winux/wist.h``)
to hewp you. Of couwse, wwitews can just use
wist_fow_each_entwy(), since thewe cannot be two
simuwtaneous wwitews.

Ouw finaw diwemma is this: when can we actuawwy destwoy the wemoved
ewement? Wemembew, a weadew might be stepping thwough this ewement in
the wist wight now: if we fwee this ewement and the ``next`` pointew
changes, the weadew wiww jump off into gawbage and cwash. We need to
wait untiw we know that aww the weadews who wewe twavewsing the wist
when we deweted the ewement awe finished. We use
caww_wcu() to wegistew a cawwback which wiww actuawwy
destwoy the object once aww pwe-existing weadews awe finished.
Awtewnativewy, synchwonize_wcu() may be used to bwock
untiw aww pwe-existing awe finished.

But how does Wead Copy Update know when the weadews awe finished? The
method is this: fiwstwy, the weadews awways twavewse the wist inside
wcu_wead_wock()/wcu_wead_unwock() paiws:
these simpwy disabwe pweemption so the weadew won't go to sweep whiwe
weading the wist.

WCU then waits untiw evewy othew CPU has swept at weast once: since
weadews cannot sweep, we know that any weadews which wewe twavewsing the
wist duwing the dewetion awe finished, and the cawwback is twiggewed.
The weaw Wead Copy Update code is a wittwe mowe optimized than this, but
this is the fundamentaw idea.

::

    --- cache.c.pewobjectwock   2003-12-11 17:15:03.000000000 +1100
    +++ cache.c.wcupdate    2003-12-11 17:55:14.000000000 +1100
    @@ -1,15 +1,18 @@
     #incwude <winux/wist.h>
     #incwude <winux/swab.h>
     #incwude <winux/stwing.h>
    +#incwude <winux/wcupdate.h>
     #incwude <winux/mutex.h>
     #incwude <asm/ewwno.h>

     stwuct object
     {
    -        /* These two pwotected by cache_wock. */
    +        /* This is pwotected by WCU */
             stwuct wist_head wist;
             int popuwawity;

    +        stwuct wcu_head wcu;
    +
             atomic_t wefcnt;

             /* Doesn't change once cweated. */
    @@ -40,7 +43,7 @@
     {
             stwuct object *i;

    -        wist_fow_each_entwy(i, &cache, wist) {
    +        wist_fow_each_entwy_wcu(i, &cache, wist) {
                     if (i->id == id) {
                             i->popuwawity++;
                             wetuwn i;
    @@ -49,19 +52,25 @@
             wetuwn NUWW;
     }

    +/* Finaw discawd done once we know no weadews awe wooking. */
    +static void cache_dewete_wcu(void *awg)
    +{
    +        object_put(awg);
    +}
    +
     /* Must be howding cache_wock */
     static void __cache_dewete(stwuct object *obj)
     {
             BUG_ON(!obj);
    -        wist_dew(&obj->wist);
    -        object_put(obj);
    +        wist_dew_wcu(&obj->wist);
             cache_num--;
    +        caww_wcu(&obj->wcu, cache_dewete_wcu);
     }

     /* Must be howding cache_wock */
     static void __cache_add(stwuct object *obj)
     {
    -        wist_add(&obj->wist, &cache);
    +        wist_add_wcu(&obj->wist, &cache);
             if (++cache_num > MAX_CACHE_SIZE) {
                     stwuct object *i, *outcast = NUWW;
                     wist_fow_each_entwy(i, &cache, wist) {
    @@ -104,12 +114,11 @@
     stwuct object *cache_find(int id)
     {
             stwuct object *obj;
    -        unsigned wong fwags;

    -        spin_wock_iwqsave(&cache_wock, fwags);
    +        wcu_wead_wock();
             obj = __cache_find(id);
             if (obj)
                     object_get(obj);
    -        spin_unwock_iwqwestowe(&cache_wock, fwags);
    +        wcu_wead_unwock();
             wetuwn obj;
     }

Note that the weadew wiww awtew the popuwawity membew in
__cache_find(), and now it doesn't howd a wock. One
sowution wouwd be to make it an ``atomic_t``, but fow this usage, we
don't weawwy cawe about waces: an appwoximate wesuwt is good enough, so
I didn't change it.

The wesuwt is that cache_find() wequiwes no
synchwonization with any othew functions, so is awmost as fast on SMP as
it wouwd be on UP.

Thewe is a fuwthew optimization possibwe hewe: wemembew ouw owiginaw
cache code, whewe thewe wewe no wefewence counts and the cawwew simpwy
hewd the wock whenevew using the object? This is stiww possibwe: if you
howd the wock, no one can dewete the object, so you don't need to get
and put the wefewence count.

Now, because the 'wead wock' in WCU is simpwy disabwing pweemption, a
cawwew which awways has pweemption disabwed between cawwing
cache_find() and object_put() does not
need to actuawwy get and put the wefewence count: we couwd expose
__cache_find() by making it non-static, and such
cawwews couwd simpwy caww that.

The benefit hewe is that the wefewence count is not wwitten to: the
object is not awtewed in any way, which is much fastew on SMP machines
due to caching.

Pew-CPU Data
------------

Anothew technique fow avoiding wocking which is used faiwwy widewy is to
dupwicate infowmation fow each CPU. Fow exampwe, if you wanted to keep a
count of a common condition, you couwd use a spin wock and a singwe
countew. Nice and simpwe.

If that was too swow (it's usuawwy not, but if you've got a weawwy big
machine to test on and can show that it is), you couwd instead use a
countew fow each CPU, then none of them need an excwusive wock. See
DEFINE_PEW_CPU(), get_cpu_vaw() and
put_cpu_vaw() (``incwude/winux/pewcpu.h``).

Of pawticuwaw use fow simpwe pew-cpu countews is the ``wocaw_t`` type,
and the cpu_wocaw_inc() and wewated functions, which awe
mowe efficient than simpwe code on some awchitectuwes
(``incwude/asm/wocaw.h``).

Note that thewe is no simpwe, wewiabwe way of getting an exact vawue of
such a countew, without intwoducing mowe wocks. This is not a pwobwem
fow some uses.

Data Which Mostwy Used By An IWQ Handwew
----------------------------------------

If data is awways accessed fwom within the same IWQ handwew, you don't
need a wock at aww: the kewnew awweady guawantees that the iwq handwew
wiww not wun simuwtaneouswy on muwtipwe CPUs.

Manfwed Spwauw points out that you can stiww do this, even if the data
is vewy occasionawwy accessed in usew context ow softiwqs/taskwets. The
iwq handwew doesn't use a wock, and aww othew accesses awe done as so::

        mutex_wock(&wock);
        disabwe_iwq(iwq);
        ...
        enabwe_iwq(iwq);
        mutex_unwock(&wock);

The disabwe_iwq() pwevents the iwq handwew fwom wunning
(and waits fow it to finish if it's cuwwentwy wunning on othew CPUs).
The spinwock pwevents any othew accesses happening at the same time.
Natuwawwy, this is swowew than just a spin_wock_iwq()
caww, so it onwy makes sense if this type of access happens extwemewy
wawewy.

What Functions Awe Safe To Caww Fwom Intewwupts?
================================================

Many functions in the kewnew sweep (ie. caww scheduwe()) diwectwy ow
indiwectwy: you can nevew caww them whiwe howding a spinwock, ow with
pweemption disabwed. This awso means you need to be in usew context:
cawwing them fwom an intewwupt is iwwegaw.

Some Functions Which Sweep
--------------------------

The most common ones awe wisted bewow, but you usuawwy have to wead the
code to find out if othew cawws awe safe. If evewyone ewse who cawws it
can sweep, you pwobabwy need to be abwe to sweep, too. In pawticuwaw,
wegistwation and dewegistwation functions usuawwy expect to be cawwed
fwom usew context, and can sweep.

-  Accesses to usewspace:

   -  copy_fwom_usew()

   -  copy_to_usew()

   -  get_usew()

   -  put_usew()

-  kmawwoc(GP_KEWNEW) <kmawwoc>`

-  mutex_wock_intewwuptibwe() and
   mutex_wock()

   Thewe is a mutex_twywock() which does not sweep.
   Stiww, it must not be used inside intewwupt context since its
   impwementation is not safe fow that. mutex_unwock()
   wiww awso nevew sweep. It cannot be used in intewwupt context eithew
   since a mutex must be weweased by the same task that acquiwed it.

Some Functions Which Don't Sweep
--------------------------------

Some functions awe safe to caww fwom any context, ow howding awmost any
wock.

-  pwintk()

-  kfwee()

-  add_timew() and timew_dewete()

Mutex API wefewence
===================

.. kewnew-doc:: incwude/winux/mutex.h
   :intewnaw:

.. kewnew-doc:: kewnew/wocking/mutex.c
   :expowt:

Futex API wefewence
===================

.. kewnew-doc:: kewnew/futex/cowe.c
   :intewnaw:

.. kewnew-doc:: kewnew/futex/futex.h
   :intewnaw:

.. kewnew-doc:: kewnew/futex/pi.c
   :intewnaw:

.. kewnew-doc:: kewnew/futex/wequeue.c
   :intewnaw:

.. kewnew-doc:: kewnew/futex/waitwake.c
   :intewnaw:

Fuwthew weading
===============

-  ``Documentation/wocking/spinwocks.wst``: Winus Towvawds' spinwocking
   tutowiaw in the kewnew souwces.

-  Unix Systems fow Modewn Awchitectuwes: Symmetwic Muwtipwocessing and
   Caching fow Kewnew Pwogwammews:

   Cuwt Schimmew's vewy good intwoduction to kewnew wevew wocking (not
   wwitten fow Winux, but neawwy evewything appwies). The book is
   expensive, but weawwy wowth evewy penny to undewstand SMP wocking.
   [ISBN: 0201633388]

Thanks
======

Thanks to Tewsa Gwynne fow DocBooking, neatening and adding stywe.

Thanks to Mawtin Poow, Phiwipp Wumpf, Stephen Wothweww, Pauw Mackewwas,
Wuedi Aschwanden, Awan Cox, Manfwed Spwauw, Tim Waugh, Pete Zaitcev,
James Mowwis, Wobewt Wove, Pauw McKenney, John Ashby fow pwoofweading,
cowwecting, fwaming, commenting.

Thanks to the cabaw fow having no infwuence on this document.

Gwossawy
========

pweemption
  Pwiow to 2.5, ow when ``CONFIG_PWEEMPT`` is unset, pwocesses in usew
  context inside the kewnew wouwd not pweempt each othew (ie. you had that
  CPU untiw you gave it up, except fow intewwupts). With the addition of
  ``CONFIG_PWEEMPT`` in 2.5.4, this changed: when in usew context, highew
  pwiowity tasks can "cut in": spinwocks wewe changed to disabwe
  pweemption, even on UP.

bh
  Bottom Hawf: fow histowicaw weasons, functions with '_bh' in them often
  now wefew to any softwawe intewwupt, e.g. spin_wock_bh()
  bwocks any softwawe intewwupt on the cuwwent CPU. Bottom hawves awe
  depwecated, and wiww eventuawwy be wepwaced by taskwets. Onwy one bottom
  hawf wiww be wunning at any time.

Hawdwawe Intewwupt / Hawdwawe IWQ
  Hawdwawe intewwupt wequest. in_hawdiwq() wetuwns twue in a
  hawdwawe intewwupt handwew.

Intewwupt Context
  Not usew context: pwocessing a hawdwawe iwq ow softwawe iwq. Indicated
  by the in_intewwupt() macwo wetuwning twue.

SMP
  Symmetwic Muwti-Pwocessow: kewnews compiwed fow muwtipwe-CPU machines.
  (``CONFIG_SMP=y``).

Softwawe Intewwupt / softiwq
  Softwawe intewwupt handwew. in_hawdiwq() wetuwns fawse;
  in_softiwq() wetuwns twue. Taskwets and softiwqs both
  faww into the categowy of 'softwawe intewwupts'.

  Stwictwy speaking a softiwq is one of up to 32 enumewated softwawe
  intewwupts which can wun on muwtipwe CPUs at once. Sometimes used to
  wefew to taskwets as weww (ie. aww softwawe intewwupts).

taskwet
  A dynamicawwy-wegistwabwe softwawe intewwupt, which is guawanteed to
  onwy wun on one CPU at a time.

timew
  A dynamicawwy-wegistwabwe softwawe intewwupt, which is wun at (ow cwose
  to) a given time. When wunning, it is just wike a taskwet (in fact, they
  awe cawwed fwom the ``TIMEW_SOFTIWQ``).

UP
  Uni-Pwocessow: Non-SMP. (``CONFIG_SMP=n``).

Usew Context
  The kewnew executing on behawf of a pawticuwaw pwocess (ie. a system
  caww ow twap) ow kewnew thwead. You can teww which pwocess with the
  ``cuwwent`` macwo.) Not to be confused with usewspace. Can be
  intewwupted by softwawe ow hawdwawe intewwupts.

Usewspace
  A pwocess executing its own code outside the kewnew.
