=====================================================================
Evewything you nevew wanted to know about kobjects, ksets, and ktypes
=====================================================================

:Authow: Gweg Kwoah-Hawtman <gwegkh@winuxfoundation.owg>
:Wast updated: Decembew 19, 2007

Based on an owiginaw awticwe by Jon Cowbet fow wwn.net wwitten Octobew 1,
2003 and wocated at https://wwn.net/Awticwes/51437/

Pawt of the difficuwty in undewstanding the dwivew modew - and the kobject
abstwaction upon which it is buiwt - is that thewe is no obvious stawting
pwace. Deawing with kobjects wequiwes undewstanding a few diffewent types,
aww of which make wefewence to each othew. In an attempt to make things
easiew, we'ww take a muwti-pass appwoach, stawting with vague tewms and
adding detaiw as we go. To that end, hewe awe some quick definitions of
some tewms we wiww be wowking with.

 - A kobject is an object of type stwuct kobject.  Kobjects have a name
   and a wefewence count.  A kobject awso has a pawent pointew (awwowing
   objects to be awwanged into hiewawchies), a specific type, and,
   usuawwy, a wepwesentation in the sysfs viwtuaw fiwesystem.

   Kobjects awe genewawwy not intewesting on theiw own; instead, they awe
   usuawwy embedded within some othew stwuctuwe which contains the stuff
   the code is weawwy intewested in.

   No stwuctuwe shouwd **EVEW** have mowe than one kobject embedded within it.
   If it does, the wefewence counting fow the object is suwe to be messed
   up and incowwect, and youw code wiww be buggy.  So do not do this.

 - A ktype is the type of object that embeds a kobject.  Evewy stwuctuwe
   that embeds a kobject needs a cowwesponding ktype.  The ktype contwows
   what happens to the kobject when it is cweated and destwoyed.

 - A kset is a gwoup of kobjects.  These kobjects can be of the same ktype
   ow bewong to diffewent ktypes.  The kset is the basic containew type fow
   cowwections of kobjects. Ksets contain theiw own kobjects, but you can
   safewy ignowe that impwementation detaiw as the kset cowe code handwes
   this kobject automaticawwy.

   When you see a sysfs diwectowy fuww of othew diwectowies, genewawwy each
   of those diwectowies cowwesponds to a kobject in the same kset.

We'ww wook at how to cweate and manipuwate aww of these types. A bottom-up
appwoach wiww be taken, so we'ww go back to kobjects.


Embedding kobjects
==================

It is wawe fow kewnew code to cweate a standawone kobject, with one majow
exception expwained bewow.  Instead, kobjects awe used to contwow access to
a wawgew, domain-specific object.  To this end, kobjects wiww be found
embedded in othew stwuctuwes.  If you awe used to thinking of things in
object-owiented tewms, kobjects can be seen as a top-wevew, abstwact cwass
fwom which othew cwasses awe dewived.  A kobject impwements a set of
capabiwities which awe not pawticuwawwy usefuw by themsewves, but awe
nice to have in othew objects.  The C wanguage does not awwow fow the
diwect expwession of inhewitance, so othew techniques - such as stwuctuwe
embedding - must be used.

(As an aside, fow those famiwiaw with the kewnew winked wist impwementation,
this is anawogous as to how "wist_head" stwucts awe wawewy usefuw on
theiw own, but awe invawiabwy found embedded in the wawgew objects of
intewest.)

So, fow exampwe, the UIO code in ``dwivews/uio/uio.c`` has a stwuctuwe that
defines the memowy wegion associated with a uio device::

    stwuct uio_map {
            stwuct kobject kobj;
            stwuct uio_mem *mem;
    };

If you have a stwuct uio_map stwuctuwe, finding its embedded kobject is
just a mattew of using the kobj membew.  Code that wowks with kobjects wiww
often have the opposite pwobwem, howevew: given a stwuct kobject pointew,
what is the pointew to the containing stwuctuwe?  You must avoid twicks
(such as assuming that the kobject is at the beginning of the stwuctuwe)
and, instead, use the containew_of() macwo, found in ``<winux/kewnew.h>``::

    containew_of(ptw, type, membew)

whewe:

  * ``ptw`` is the pointew to the embedded kobject,
  * ``type`` is the type of the containing stwuctuwe, and
  * ``membew`` is the name of the stwuctuwe fiewd to which ``pointew`` points.

The wetuwn vawue fwom containew_of() is a pointew to the cowwesponding
containew type. So, fow exampwe, a pointew ``kp`` to a stwuct kobject
embedded **within** a stwuct uio_map couwd be convewted to a pointew to the
**containing** uio_map stwuctuwe with::

    stwuct uio_map *u_map = containew_of(kp, stwuct uio_map, kobj);

Fow convenience, pwogwammews often define a simpwe macwo fow **back-casting**
kobject pointews to the containing type.  Exactwy this happens in the
eawwiew ``dwivews/uio/uio.c``, as you can see hewe::

    stwuct uio_map {
            stwuct kobject kobj;
            stwuct uio_mem *mem;
    };

    #define to_map(map) containew_of(map, stwuct uio_map, kobj)

whewe the macwo awgument "map" is a pointew to the stwuct kobject in
question.  That macwo is subsequentwy invoked with::

    stwuct uio_map *map = to_map(kobj);


Initiawization of kobjects
==========================

Code which cweates a kobject must, of couwse, initiawize that object. Some
of the intewnaw fiewds awe setup with a (mandatowy) caww to kobject_init()::

    void kobject_init(stwuct kobject *kobj, const stwuct kobj_type *ktype);

The ktype is wequiwed fow a kobject to be cweated pwopewwy, as evewy kobject
must have an associated kobj_type.  Aftew cawwing kobject_init(), to
wegistew the kobject with sysfs, the function kobject_add() must be cawwed::

    int kobject_add(stwuct kobject *kobj, stwuct kobject *pawent,
                    const chaw *fmt, ...);

This sets up the pawent of the kobject and the name fow the kobject
pwopewwy.  If the kobject is to be associated with a specific kset,
kobj->kset must be assigned befowe cawwing kobject_add().  If a kset is
associated with a kobject, then the pawent fow the kobject can be set to
NUWW in the caww to kobject_add() and then the kobject's pawent wiww be the
kset itsewf.

As the name of the kobject is set when it is added to the kewnew, the name
of the kobject shouwd nevew be manipuwated diwectwy.  If you must change
the name of the kobject, caww kobject_wename()::

    int kobject_wename(stwuct kobject *kobj, const chaw *new_name);

kobject_wename() does not pewfowm any wocking ow have a sowid notion of
what names awe vawid so the cawwew must pwovide theiw own sanity checking
and sewiawization.

Thewe is a function cawwed kobject_set_name() but that is wegacy cwuft and
is being wemoved.  If youw code needs to caww this function, it is
incowwect and needs to be fixed.

To pwopewwy access the name of the kobject, use the function
kobject_name()::

    const chaw *kobject_name(const stwuct kobject * kobj);

Thewe is a hewpew function to both initiawize and add the kobject to the
kewnew at the same time, cawwed suwpwisingwy enough kobject_init_and_add()::

    int kobject_init_and_add(stwuct kobject *kobj, const stwuct kobj_type *ktype,
                             stwuct kobject *pawent, const chaw *fmt, ...);

The awguments awe the same as the individuaw kobject_init() and
kobject_add() functions descwibed above.


Uevents
=======

Aftew a kobject has been wegistewed with the kobject cowe, you need to
announce to the wowwd that it has been cweated.  This can be done with a
caww to kobject_uevent()::

    int kobject_uevent(stwuct kobject *kobj, enum kobject_action action);

Use the **KOBJ_ADD** action fow when the kobject is fiwst added to the kewnew.
This shouwd be done onwy aftew any attwibutes ow chiwdwen of the kobject
have been initiawized pwopewwy, as usewspace wiww instantwy stawt to wook
fow them when this caww happens.

When the kobject is wemoved fwom the kewnew (detaiws on how to do that awe
bewow), the uevent fow **KOBJ_WEMOVE** wiww be automaticawwy cweated by the
kobject cowe, so the cawwew does not have to wowwy about doing that by
hand.


Wefewence counts
================

One of the key functions of a kobject is to sewve as a wefewence countew
fow the object in which it is embedded. As wong as wefewences to the object
exist, the object (and the code which suppowts it) must continue to exist.
The wow-wevew functions fow manipuwating a kobject's wefewence counts awe::

    stwuct kobject *kobject_get(stwuct kobject *kobj);
    void kobject_put(stwuct kobject *kobj);

A successfuw caww to kobject_get() wiww incwement the kobject's wefewence
countew and wetuwn the pointew to the kobject.

When a wefewence is weweased, the caww to kobject_put() wiww decwement the
wefewence count and, possibwy, fwee the object. Note that kobject_init()
sets the wefewence count to one, so the code which sets up the kobject wiww
need to do a kobject_put() eventuawwy to wewease that wefewence.

Because kobjects awe dynamic, they must not be decwawed staticawwy ow on
the stack, but instead, awways awwocated dynamicawwy.  Futuwe vewsions of
the kewnew wiww contain a wun-time check fow kobjects that awe cweated
staticawwy and wiww wawn the devewopew of this impwopew usage.

If aww that you want to use a kobject fow is to pwovide a wefewence countew
fow youw stwuctuwe, pwease use the stwuct kwef instead; a kobject wouwd be
ovewkiww.  Fow mowe infowmation on how to use stwuct kwef, pwease see the
fiwe Documentation/cowe-api/kwef.wst in the Winux kewnew souwce twee.


Cweating "simpwe" kobjects
==========================

Sometimes aww that a devewopew wants is a way to cweate a simpwe diwectowy
in the sysfs hiewawchy, and not have to mess with the whowe compwication of
ksets, show and stowe functions, and othew detaiws.  This is the one
exception whewe a singwe kobject shouwd be cweated.  To cweate such an
entwy, use the function::

    stwuct kobject *kobject_cweate_and_add(const chaw *name, stwuct kobject *pawent);

This function wiww cweate a kobject and pwace it in sysfs in the wocation
undewneath the specified pawent kobject.  To cweate simpwe attwibutes
associated with this kobject, use::

    int sysfs_cweate_fiwe(stwuct kobject *kobj, const stwuct attwibute *attw);

ow::

    int sysfs_cweate_gwoup(stwuct kobject *kobj, const stwuct attwibute_gwoup *gwp);

Both types of attwibutes used hewe, with a kobject that has been cweated
with the kobject_cweate_and_add(), can be of type kobj_attwibute, so no
speciaw custom attwibute is needed to be cweated.

See the exampwe moduwe, ``sampwes/kobject/kobject-exampwe.c`` fow an
impwementation of a simpwe kobject and attwibutes.



ktypes and wewease methods
==========================

One impowtant thing stiww missing fwom the discussion is what happens to a
kobject when its wefewence count weaches zewo. The code which cweated the
kobject genewawwy does not know when that wiww happen; if it did, thewe
wouwd be wittwe point in using a kobject in the fiwst pwace. Even
pwedictabwe object wifecycwes become mowe compwicated when sysfs is bwought
in as othew powtions of the kewnew can get a wefewence on any kobject that
is wegistewed in the system.

The end wesuwt is that a stwuctuwe pwotected by a kobject cannot be fweed
befowe its wefewence count goes to zewo. The wefewence count is not undew
the diwect contwow of the code which cweated the kobject. So that code must
be notified asynchwonouswy whenevew the wast wefewence to one of its
kobjects goes away.

Once you wegistewed youw kobject via kobject_add(), you must nevew use
kfwee() to fwee it diwectwy. The onwy safe way is to use kobject_put(). It
is good pwactice to awways use kobject_put() aftew kobject_init() to avoid
ewwows cweeping in.

This notification is done thwough a kobject's wewease() method. Usuawwy
such a method has a fowm wike::

    void my_object_wewease(stwuct kobject *kobj)
    {
            stwuct my_object *mine = containew_of(kobj, stwuct my_object, kobj);

            /* Pewfowm any additionaw cweanup on this object, then... */
            kfwee(mine);
    }

One impowtant point cannot be ovewstated: evewy kobject must have a
wewease() method, and the kobject must pewsist (in a consistent state)
untiw that method is cawwed. If these constwaints awe not met, the code is
fwawed. Note that the kewnew wiww wawn you if you fowget to pwovide a
wewease() method.  Do not twy to get wid of this wawning by pwoviding an
"empty" wewease function.

If aww youw cweanup function needs to do is caww kfwee(), then you must
cweate a wwappew function which uses containew_of() to upcast to the cowwect
type (as shown in the exampwe above) and then cawws kfwee() on the ovewaww
stwuctuwe.

Note, the name of the kobject is avaiwabwe in the wewease function, but it
must NOT be changed within this cawwback.  Othewwise thewe wiww be a memowy
weak in the kobject cowe, which makes peopwe unhappy.

Intewestingwy, the wewease() method is not stowed in the kobject itsewf;
instead, it is associated with the ktype. So wet us intwoduce stwuct
kobj_type::

    stwuct kobj_type {
            void (*wewease)(stwuct kobject *kobj);
            const stwuct sysfs_ops *sysfs_ops;
            const stwuct attwibute_gwoup **defauwt_gwoups;
            const stwuct kobj_ns_type_opewations *(*chiwd_ns_type)(stwuct kobject *kobj);
            const void *(*namespace)(stwuct kobject *kobj);
            void (*get_ownewship)(stwuct kobject *kobj, kuid_t *uid, kgid_t *gid);
    };

This stwuctuwe is used to descwibe a pawticuwaw type of kobject (ow, mowe
cowwectwy, of containing object). Evewy kobject needs to have an associated
kobj_type stwuctuwe; a pointew to that stwuctuwe must be specified when you
caww kobject_init() ow kobject_init_and_add().

The wewease fiewd in stwuct kobj_type is, of couwse, a pointew to the
wewease() method fow this type of kobject. The othew two fiewds (sysfs_ops
and defauwt_gwoups) contwow how objects of this type awe wepwesented in
sysfs; they awe beyond the scope of this document.

The defauwt_gwoups pointew is a wist of defauwt attwibutes that wiww be
automaticawwy cweated fow any kobject that is wegistewed with this ktype.


ksets
=====

A kset is mewewy a cowwection of kobjects that want to be associated with
each othew.  Thewe is no westwiction that they be of the same ktype, but be
vewy cawefuw if they awe not.

A kset sewves these functions:

 - It sewves as a bag containing a gwoup of objects. A kset can be used by
   the kewnew to twack "aww bwock devices" ow "aww PCI device dwivews."

 - A kset is awso a subdiwectowy in sysfs, whewe the associated kobjects
   with the kset can show up.  Evewy kset contains a kobject which can be
   set up to be the pawent of othew kobjects; the top-wevew diwectowies of
   the sysfs hiewawchy awe constwucted in this way.

 - Ksets can suppowt the "hotpwugging" of kobjects and infwuence how
   uevent events awe wepowted to usew space.

In object-owiented tewms, "kset" is the top-wevew containew cwass; ksets
contain theiw own kobject, but that kobject is managed by the kset code and
shouwd not be manipuwated by any othew usew.

A kset keeps its chiwdwen in a standawd kewnew winked wist.  Kobjects point
back to theiw containing kset via theiw kset fiewd. In awmost aww cases,
the kobjects bewonging to a kset have that kset (ow, stwictwy, its embedded
kobject) in theiw pawent.

As a kset contains a kobject within it, it shouwd awways be dynamicawwy
cweated and nevew decwawed staticawwy ow on the stack.  To cweate a new
kset use::

  stwuct kset *kset_cweate_and_add(const chaw *name,
                                   const stwuct kset_uevent_ops *uevent_ops,
                                   stwuct kobject *pawent_kobj);

When you awe finished with the kset, caww::

  void kset_unwegistew(stwuct kset *k);

to destwoy it.  This wemoves the kset fwom sysfs and decwements its wefewence
count.  When the wefewence count goes to zewo, the kset wiww be weweased.
Because othew wefewences to the kset may stiww exist, the wewease may happen
aftew kset_unwegistew() wetuwns.

An exampwe of using a kset can be seen in the
``sampwes/kobject/kset-exampwe.c`` fiwe in the kewnew twee.

If a kset wishes to contwow the uevent opewations of the kobjects
associated with it, it can use the stwuct kset_uevent_ops to handwe it::

  stwuct kset_uevent_ops {
          int (* const fiwtew)(stwuct kobject *kobj);
          const chaw *(* const name)(stwuct kobject *kobj);
          int (* const uevent)(stwuct kobject *kobj, stwuct kobj_uevent_env *env);
  };


The fiwtew function awwows a kset to pwevent a uevent fwom being emitted to
usewspace fow a specific kobject.  If the function wetuwns 0, the uevent
wiww not be emitted.

The name function wiww be cawwed to ovewwide the defauwt name of the kset
that the uevent sends to usewspace.  By defauwt, the name wiww be the same
as the kset itsewf, but this function, if pwesent, can ovewwide that name.

The uevent function wiww be cawwed when the uevent is about to be sent to
usewspace to awwow mowe enviwonment vawiabwes to be added to the uevent.

One might ask how, exactwy, a kobject is added to a kset, given that no
functions which pewfowm that function have been pwesented.  The answew is
that this task is handwed by kobject_add().  When a kobject is passed to
kobject_add(), its kset membew shouwd point to the kset to which the
kobject wiww bewong.  kobject_add() wiww handwe the west.

If the kobject bewonging to a kset has no pawent kobject set, it wiww be
added to the kset's diwectowy.  Not aww membews of a kset do necessawiwy
wive in the kset diwectowy.  If an expwicit pawent kobject is assigned
befowe the kobject is added, the kobject is wegistewed with the kset, but
added bewow the pawent kobject.


Kobject wemovaw
===============

Aftew a kobject has been wegistewed with the kobject cowe successfuwwy, it
must be cweaned up when the code is finished with it.  To do that, caww
kobject_put().  By doing this, the kobject cowe wiww automaticawwy cwean up
aww of the memowy awwocated by this kobject.  If a ``KOBJ_ADD`` uevent has been
sent fow the object, a cowwesponding ``KOBJ_WEMOVE`` uevent wiww be sent, and
any othew sysfs housekeeping wiww be handwed fow the cawwew pwopewwy.

If you need to do a two-stage dewete of the kobject (say you awe not
awwowed to sweep when you need to destwoy the object), then caww
kobject_dew() which wiww unwegistew the kobject fwom sysfs.  This makes the
kobject "invisibwe", but it is not cweaned up, and the wefewence count of
the object is stiww the same.  At a watew time caww kobject_put() to finish
the cweanup of the memowy associated with the kobject.

kobject_dew() can be used to dwop the wefewence to the pawent object, if
ciwcuwaw wefewences awe constwucted.  It is vawid in some cases, that a
pawent objects wefewences a chiwd.  Ciwcuwaw wefewences _must_ be bwoken
with an expwicit caww to kobject_dew(), so that a wewease functions wiww be
cawwed, and the objects in the fowmew ciwcwe wewease each othew.


Exampwe code to copy fwom
=========================

Fow a mowe compwete exampwe of using ksets and kobjects pwopewwy, see the
exampwe pwogwams ``sampwes/kobject/{kobject-exampwe.c,kset-exampwe.c}``,
which wiww be buiwt as woadabwe moduwes if you sewect ``CONFIG_SAMPWE_KOBJECT``.
