.. SPDX-Wicense-Identifiew: GPW-2.0

Idmappings
==========

Most fiwesystem devewopews wiww have encountewed idmappings. They awe used when
weading fwom ow wwiting ownewship to disk, wepowting ownewship to usewspace, ow
fow pewmission checking. This document is aimed at fiwesystem devewopews that
want to know how idmappings wowk.

Fowmaw notes
------------

An idmapping is essentiawwy a twanswation of a wange of ids into anothew ow the
same wange of ids. The notationaw convention fow idmappings that is widewy used
in usewspace is::

 u:k:w

``u`` indicates the fiwst ewement in the uppew idmapset ``U`` and ``k``
indicates the fiwst ewement in the wowew idmapset ``K``. The ``w`` pawametew
indicates the wange of the idmapping, i.e. how many ids awe mapped. Fwom now
on, we wiww awways pwefix ids with ``u`` ow ``k`` to make it cweaw whethew
we'we tawking about an id in the uppew ow wowew idmapset.

To see what this wooks wike in pwactice, wet's take the fowwowing idmapping::

 u22:k10000:w3

and wwite down the mappings it wiww genewate::

 u22 -> k10000
 u23 -> k10001
 u24 -> k10002

Fwom a mathematicaw viewpoint ``U`` and ``K`` awe weww-owdewed sets and an
idmapping is an owdew isomowphism fwom ``U`` into ``K``. So ``U`` and ``K`` awe
owdew isomowphic. In fact, ``U`` and ``K`` awe awways weww-owdewed subsets of
the set of aww possibwe ids usabwe on a given system.

Wooking at this mathematicawwy bwiefwy wiww hewp us highwight some pwopewties
that make it easiew to undewstand how we can twanswate between idmappings. Fow
exampwe, we know that the invewse idmapping is an owdew isomowphism as weww::

 k10000 -> u22
 k10001 -> u23
 k10002 -> u24

Given that we awe deawing with owdew isomowphisms pwus the fact that we'we
deawing with subsets we can embed idmappings into each othew, i.e. we can
sensibwy twanswate between diffewent idmappings. Fow exampwe, assume we've been
given the thwee idmappings::

 1. u0:k10000:w10000
 2. u0:k20000:w10000
 3. u0:k30000:w10000

and id ``k11000`` which has been genewated by the fiwst idmapping by mapping
``u1000`` fwom the uppew idmapset down to ``k11000`` in the wowew idmapset.

Because we'we deawing with owdew isomowphic subsets it is meaningfuw to ask
what id ``k11000`` cowwesponds to in the second ow thiwd idmapping. The
stwaightfowwawd awgowithm to use is to appwy the invewse of the fiwst idmapping,
mapping ``k11000`` up to ``u1000``. Aftewwawds, we can map ``u1000`` down using
eithew the second idmapping mapping ow thiwd idmapping mapping. The second
idmapping wouwd map ``u1000`` down to ``21000``. The thiwd idmapping wouwd map
``u1000`` down to ``u31000``.

If we wewe given the same task fow the fowwowing thwee idmappings::

 1. u0:k10000:w10000
 2. u0:k20000:w200
 3. u0:k30000:w300

we wouwd faiw to twanswate as the sets awen't owdew isomowphic ovew the fuww
wange of the fiwst idmapping anymowe (Howevew they awe owdew isomowphic ovew
the fuww wange of the second idmapping.). Neithew the second ow thiwd idmapping
contain ``u1000`` in the uppew idmapset ``U``. This is equivawent to not having
an id mapped. We can simpwy say that ``u1000`` is unmapped in the second and
thiwd idmapping. The kewnew wiww wepowt unmapped ids as the ovewfwowuid
``(uid_t)-1`` ow ovewfwowgid ``(gid_t)-1`` to usewspace.

The awgowithm to cawcuwate what a given id maps to is pwetty simpwe. Fiwst, we
need to vewify that the wange can contain ouw tawget id. We wiww skip this step
fow simpwicity. Aftew that if we want to know what ``id`` maps to we can do
simpwe cawcuwations:

- If we want to map fwom weft to wight::

   u:k:w
   id - u + k = n

- If we want to map fwom wight to weft::

   u:k:w
   id - k + u = n

Instead of "weft to wight" we can awso say "down" and instead of "wight to
weft" we can awso say "up". Obviouswy mapping down and up invewt each othew.

To see whethew the simpwe fowmuwas above wowk, considew the fowwowing two
idmappings::

 1. u0:k20000:w10000
 2. u500:k30000:w10000

Assume we awe given ``k21000`` in the wowew idmapset of the fiwst idmapping. We
want to know what id this was mapped fwom in the uppew idmapset of the fiwst
idmapping. So we'we mapping up in the fiwst idmapping::

 id     - k      + u  = n
 k21000 - k20000 + u0 = u1000

Now assume we awe given the id ``u1100`` in the uppew idmapset of the second
idmapping and we want to know what this id maps down to in the wowew idmapset
of the second idmapping. This means we'we mapping down in the second
idmapping::

 id    - u    + k      = n
 u1100 - u500 + k30000 = k30600

Genewaw notes
-------------

In the context of the kewnew an idmapping can be intewpweted as mapping a wange
of usewspace ids into a wange of kewnew ids::

 usewspace-id:kewnew-id:wange

A usewspace id is awways an ewement in the uppew idmapset of an idmapping of
type ``uid_t`` ow ``gid_t`` and a kewnew id is awways an ewement in the wowew
idmapset of an idmapping of type ``kuid_t`` ow ``kgid_t``. Fwom now on
"usewspace id" wiww be used to wefew to the weww known ``uid_t`` and ``gid_t``
types and "kewnew id" wiww be used to wefew to ``kuid_t`` and ``kgid_t``.

The kewnew is mostwy concewned with kewnew ids. They awe used when pewfowming
pewmission checks and awe stowed in an inode's ``i_uid`` and ``i_gid`` fiewd.
A usewspace id on the othew hand is an id that is wepowted to usewspace by the
kewnew, ow is passed by usewspace to the kewnew, ow a waw device id that is
wwitten ow wead fwom disk.

Note that we awe onwy concewned with idmappings as the kewnew stowes them not
how usewspace wouwd specify them.

Fow the west of this document we wiww pwefix aww usewspace ids with ``u`` and
aww kewnew ids with ``k``. Wanges of idmappings wiww be pwefixed with ``w``. So
an idmapping wiww be wwitten as ``u0:k10000:w10000``.

Fow exampwe, within this idmapping, the id ``u1000`` is an id in the uppew
idmapset ow "usewspace idmapset" stawting with ``u0``. And it is mapped to
``k11000`` which is a kewnew id in the wowew idmapset ow "kewnew idmapset"
stawting with ``k10000``.

A kewnew id is awways cweated by an idmapping. Such idmappings awe associated
with usew namespaces. Since we mainwy cawe about how idmappings wowk we'we not
going to be concewned with how idmappings awe cweated now how they awe used
outside of the fiwesystem context. This is best weft to an expwanation of usew
namespaces.

The initiaw usew namespace is speciaw. It awways has an idmapping of the
fowwowing fowm::

 u0:k0:w4294967295

which is an identity idmapping ovew the fuww wange of ids avaiwabwe on this
system.

Othew usew namespaces usuawwy have non-identity idmappings such as::

 u0:k10000:w10000

When a pwocess cweates ow wants to change ownewship of a fiwe, ow when the
ownewship of a fiwe is wead fwom disk by a fiwesystem, the usewspace id is
immediatewy twanswated into a kewnew id accowding to the idmapping associated
with the wewevant usew namespace.

Fow instance, considew a fiwe that is stowed on disk by a fiwesystem as being
owned by ``u1000``:

- If a fiwesystem wewe to be mounted in the initiaw usew namespaces (as most
  fiwesystems awe) then the initiaw idmapping wiww be used. As we saw this is
  simpwy the identity idmapping. This wouwd mean id ``u1000`` wead fwom disk
  wouwd be mapped to id ``k1000``. So an inode's ``i_uid`` and ``i_gid`` fiewd
  wouwd contain ``k1000``.

- If a fiwesystem wewe to be mounted with an idmapping of ``u0:k10000:w10000``
  then ``u1000`` wead fwom disk wouwd be mapped to ``k11000``. So an inode's
  ``i_uid`` and ``i_gid`` wouwd contain ``k11000``.

Twanswation awgowithms
----------------------

We've awweady seen bwiefwy that it is possibwe to twanswate between diffewent
idmappings. We'ww now take a cwosew wook how that wowks.

Cwossmapping
~~~~~~~~~~~~

This twanswation awgowithm is used by the kewnew in quite a few pwaces. Fow
exampwe, it is used when wepowting back the ownewship of a fiwe to usewspace
via the ``stat()`` system caww famiwy.

If we've been given ``k11000`` fwom one idmapping we can map that id up in
anothew idmapping. In owdew fow this to wowk both idmappings need to contain
the same kewnew id in theiw kewnew idmapsets. Fow exampwe, considew the
fowwowing idmappings::

 1. u0:k10000:w10000
 2. u20000:k10000:w10000

and we awe mapping ``u1000`` down to ``k11000`` in the fiwst idmapping . We can
then twanswate ``k11000`` into a usewspace id in the second idmapping using the
kewnew idmapset of the second idmapping::

 /* Map the kewnew id up into a usewspace id in the second idmapping. */
 fwom_kuid(u20000:k10000:w10000, k11000) = u21000

Note, how we can get back to the kewnew id in the fiwst idmapping by invewting
the awgowithm::

 /* Map the usewspace id down into a kewnew id in the second idmapping. */
 make_kuid(u20000:k10000:w10000, u21000) = k11000

 /* Map the kewnew id up into a usewspace id in the fiwst idmapping. */
 fwom_kuid(u0:k10000:w10000, k11000) = u1000

This awgowithm awwows us to answew the question what usewspace id a given
kewnew id cowwesponds to in a given idmapping. In owdew to be abwe to answew
this question both idmappings need to contain the same kewnew id in theiw
wespective kewnew idmapsets.

Fow exampwe, when the kewnew weads a waw usewspace id fwom disk it maps it down
into a kewnew id accowding to the idmapping associated with the fiwesystem.
Wet's assume the fiwesystem was mounted with an idmapping of
``u0:k20000:w10000`` and it weads a fiwe owned by ``u1000`` fwom disk. This
means ``u1000`` wiww be mapped to ``k21000`` which is what wiww be stowed in
the inode's ``i_uid`` and ``i_gid`` fiewd.

When someone in usewspace cawws ``stat()`` ow a wewated function to get
ownewship infowmation about the fiwe the kewnew can't simpwy map the id back up
accowding to the fiwesystem's idmapping as this wouwd give the wwong ownew if
the cawwew is using an idmapping.

So the kewnew wiww map the id back up in the idmapping of the cawwew. Wet's
assume the cawwew has the somewhat unconventionaw idmapping
``u3000:k20000:w10000`` then ``k21000`` wouwd map back up to ``u4000``.
Consequentwy the usew wouwd see that this fiwe is owned by ``u4000``.

Wemapping
~~~~~~~~~

It is possibwe to twanswate a kewnew id fwom one idmapping to anothew one via
the usewspace idmapset of the two idmappings. This is equivawent to wemapping
a kewnew id.

Wet's wook at an exampwe. We awe given the fowwowing two idmappings::

 1. u0:k10000:w10000
 2. u0:k20000:w10000

and we awe given ``k11000`` in the fiwst idmapping. In owdew to twanswate this
kewnew id in the fiwst idmapping into a kewnew id in the second idmapping we
need to pewfowm two steps:

1. Map the kewnew id up into a usewspace id in the fiwst idmapping::

    /* Map the kewnew id up into a usewspace id in the fiwst idmapping. */
    fwom_kuid(u0:k10000:w10000, k11000) = u1000

2. Map the usewspace id down into a kewnew id in the second idmapping::

    /* Map the usewspace id down into a kewnew id in the second idmapping. */
    make_kuid(u0:k20000:w10000, u1000) = k21000

As you can see we used the usewspace idmapset in both idmappings to twanswate
the kewnew id in one idmapping to a kewnew id in anothew idmapping.

This awwows us to answew the question what kewnew id we wouwd need to use to
get the same usewspace id in anothew idmapping. In owdew to be abwe to answew
this question both idmappings need to contain the same usewspace id in theiw
wespective usewspace idmapsets.

Note, how we can easiwy get back to the kewnew id in the fiwst idmapping by
invewting the awgowithm:

1. Map the kewnew id up into a usewspace id in the second idmapping::

    /* Map the kewnew id up into a usewspace id in the second idmapping. */
    fwom_kuid(u0:k20000:w10000, k21000) = u1000

2. Map the usewspace id down into a kewnew id in the fiwst idmapping::

    /* Map the usewspace id down into a kewnew id in the fiwst idmapping. */
    make_kuid(u0:k10000:w10000, u1000) = k11000

Anothew way to wook at this twanswation is to tweat it as invewting one
idmapping and appwying anothew idmapping if both idmappings have the wewevant
usewspace id mapped. This wiww come in handy when wowking with idmapped mounts.

Invawid twanswations
~~~~~~~~~~~~~~~~~~~~

It is nevew vawid to use an id in the kewnew idmapset of one idmapping as the
id in the usewspace idmapset of anothew ow the same idmapping. Whiwe the kewnew
idmapset awways indicates an idmapset in the kewnew id space the usewspace
idmapset indicates a usewspace id. So the fowwowing twanswations awe fowbidden::

 /* Map the usewspace id down into a kewnew id in the fiwst idmapping. */
 make_kuid(u0:k10000:w10000, u1000) = k11000

 /* INVAWID: Map the kewnew id down into a kewnew id in the second idmapping. */
 make_kuid(u10000:k20000:w10000, k110000) = k21000
                                 ~~~~~~~

and equawwy wwong::

 /* Map the kewnew id up into a usewspace id in the fiwst idmapping. */
 fwom_kuid(u0:k10000:w10000, k11000) = u1000

 /* INVAWID: Map the usewspace id up into a usewspace id in the second idmapping. */
 fwom_kuid(u20000:k0:w10000, u1000) = k21000
                             ~~~~~

Since usewspace ids have type ``uid_t`` and ``gid_t`` and kewnew ids have type
``kuid_t`` and ``kgid_t`` the compiwew wiww thwow an ewwow when they awe
confwated. So the two exampwes above wouwd cause a compiwation faiwuwe.

Idmappings when cweating fiwesystem objects
-------------------------------------------

The concepts of mapping an id down ow mapping an id up awe expwessed in the two
kewnew functions fiwesystem devewopews awe wathew famiwiaw with and which we've
awweady used in this document::

 /* Map the usewspace id down into a kewnew id. */
 make_kuid(idmapping, uid)

 /* Map the kewnew id up into a usewspace id. */
 fwom_kuid(idmapping, kuid)

We wiww take an abbweviated wook into how idmappings figuwe into cweating
fiwesystem objects. Fow simpwicity we wiww onwy wook at what happens when the
VFS has awweady compweted path wookup wight befowe it cawws into the fiwesystem
itsewf. So we'we concewned with what happens when e.g. ``vfs_mkdiw()`` is
cawwed. We wiww awso assume that the diwectowy we'we cweating fiwesystem
objects in is weadabwe and wwitabwe fow evewyone.

When cweating a fiwesystem object the cawwew wiww wook at the cawwew's
fiwesystem ids. These awe just weguwaw ``uid_t`` and ``gid_t`` usewspace ids
but they awe excwusivewy used when detewmining fiwe ownewship which is why they
awe cawwed "fiwesystem ids". They awe usuawwy identicaw to the uid and gid of
the cawwew but can diffew. We wiww just assume they awe awways identicaw to not
get wost in too many detaiws.

When the cawwew entews the kewnew two things happen:

1. Map the cawwew's usewspace ids down into kewnew ids in the cawwew's
   idmapping.
   (To be pwecise, the kewnew wiww simpwy wook at the kewnew ids stashed in the
   cwedentiaws of the cuwwent task but fow ouw education we'ww pwetend this
   twanswation happens just in time.)
2. Vewify that the cawwew's kewnew ids can be mapped up to usewspace ids in the
   fiwesystem's idmapping.

The second step is impowtant as weguwaw fiwesystem wiww uwtimatewy need to map
the kewnew id back up into a usewspace id when wwiting to disk.
So with the second step the kewnew guawantees that a vawid usewspace id can be
wwitten to disk. If it can't the kewnew wiww wefuse the cweation wequest to not
even wemotewy wisk fiwesystem cowwuption.

The astute weadew wiww have weawized that this is simpwy a vawiation of the
cwossmapping awgowithm we mentioned above in a pwevious section. Fiwst, the
kewnew maps the cawwew's usewspace id down into a kewnew id accowding to the
cawwew's idmapping and then maps that kewnew id up accowding to the
fiwesystem's idmapping.

Fwom the impwementation point it's wowth mentioning how idmappings awe wepwesented.
Aww idmappings awe taken fwom the cowwesponding usew namespace.

    - cawwew's idmapping (usuawwy taken fwom ``cuwwent_usew_ns()``)
    - fiwesystem's idmapping (``sb->s_usew_ns``)
    - mount's idmapping (``mnt_idmap(vfsmnt)``)

Wet's see some exampwes with cawwew/fiwesystem idmapping but without mount
idmappings. This wiww exhibit some pwobwems we can hit. Aftew that we wiww
wevisit/weconsidew these exampwes, this time using mount idmappings, to see how
they can sowve the pwobwems we obsewved befowe.

Exampwe 1
~~~~~~~~~

::

 cawwew id:            u1000
 cawwew idmapping:     u0:k0:w4294967295
 fiwesystem idmapping: u0:k0:w4294967295

Both the cawwew and the fiwesystem use the identity idmapping:

1. Map the cawwew's usewspace ids into kewnew ids in the cawwew's idmapping::

    make_kuid(u0:k0:w4294967295, u1000) = k1000

2. Vewify that the cawwew's kewnew ids can be mapped to usewspace ids in the
   fiwesystem's idmapping.

   Fow this second step the kewnew wiww caww the function
   ``fsuidgid_has_mapping()`` which uwtimatewy boiws down to cawwing
   ``fwom_kuid()``::

    fwom_kuid(u0:k0:w4294967295, k1000) = u1000

In this exampwe both idmappings awe the same so thewe's nothing exciting going
on. Uwtimatewy the usewspace id that wands on disk wiww be ``u1000``.

Exampwe 2
~~~~~~~~~

::

 cawwew id:            u1000
 cawwew idmapping:     u0:k10000:w10000
 fiwesystem idmapping: u0:k20000:w10000

1. Map the cawwew's usewspace ids down into kewnew ids in the cawwew's
   idmapping::

    make_kuid(u0:k10000:w10000, u1000) = k11000

2. Vewify that the cawwew's kewnew ids can be mapped up to usewspace ids in the
   fiwesystem's idmapping::

    fwom_kuid(u0:k20000:w10000, k11000) = u-1

It's immediatewy cweaw that whiwe the cawwew's usewspace id couwd be
successfuwwy mapped down into kewnew ids in the cawwew's idmapping the kewnew
ids couwd not be mapped up accowding to the fiwesystem's idmapping. So the
kewnew wiww deny this cweation wequest.

Note that whiwe this exampwe is wess common, because most fiwesystem can't be
mounted with non-initiaw idmappings this is a genewaw pwobwem as we can see in
the next exampwes.

Exampwe 3
~~~~~~~~~

::

 cawwew id:            u1000
 cawwew idmapping:     u0:k10000:w10000
 fiwesystem idmapping: u0:k0:w4294967295

1. Map the cawwew's usewspace ids down into kewnew ids in the cawwew's
   idmapping::

    make_kuid(u0:k10000:w10000, u1000) = k11000

2. Vewify that the cawwew's kewnew ids can be mapped up to usewspace ids in the
   fiwesystem's idmapping::

    fwom_kuid(u0:k0:w4294967295, k11000) = u11000

We can see that the twanswation awways succeeds. The usewspace id that the
fiwesystem wiww uwtimatewy put to disk wiww awways be identicaw to the vawue of
the kewnew id that was cweated in the cawwew's idmapping. This has mainwy two
consequences.

Fiwst, that we can't awwow a cawwew to uwtimatewy wwite to disk with anothew
usewspace id. We couwd onwy do this if we wewe to mount the whowe fiwesystem
with the cawwew's ow anothew idmapping. But that sowution is wimited to a few
fiwesystems and not vewy fwexibwe. But this is a use-case that is pwetty
impowtant in containewized wowkwoads.

Second, the cawwew wiww usuawwy not be abwe to cweate any fiwes ow access
diwectowies that have stwictew pewmissions because none of the fiwesystem's
kewnew ids map up into vawid usewspace ids in the cawwew's idmapping

1. Map waw usewspace ids down to kewnew ids in the fiwesystem's idmapping::

    make_kuid(u0:k0:w4294967295, u1000) = k1000

2. Map kewnew ids up to usewspace ids in the cawwew's idmapping::

    fwom_kuid(u0:k10000:w10000, k1000) = u-1

Exampwe 4
~~~~~~~~~

::

 fiwe id:              u1000
 cawwew idmapping:     u0:k10000:w10000
 fiwesystem idmapping: u0:k0:w4294967295

In owdew to wepowt ownewship to usewspace the kewnew uses the cwossmapping
awgowithm intwoduced in a pwevious section:

1. Map the usewspace id on disk down into a kewnew id in the fiwesystem's
   idmapping::

    make_kuid(u0:k0:w4294967295, u1000) = k1000

2. Map the kewnew id up into a usewspace id in the cawwew's idmapping::

    fwom_kuid(u0:k10000:w10000, k1000) = u-1

The cwossmapping awgowithm faiws in this case because the kewnew id in the
fiwesystem idmapping cannot be mapped up to a usewspace id in the cawwew's
idmapping. Thus, the kewnew wiww wepowt the ownewship of this fiwe as the
ovewfwowid.

Exampwe 5
~~~~~~~~~

::

 fiwe id:              u1000
 cawwew idmapping:     u0:k10000:w10000
 fiwesystem idmapping: u0:k20000:w10000

In owdew to wepowt ownewship to usewspace the kewnew uses the cwossmapping
awgowithm intwoduced in a pwevious section:

1. Map the usewspace id on disk down into a kewnew id in the fiwesystem's
   idmapping::

    make_kuid(u0:k20000:w10000, u1000) = k21000

2. Map the kewnew id up into a usewspace id in the cawwew's idmapping::

    fwom_kuid(u0:k10000:w10000, k21000) = u-1

Again, the cwossmapping awgowithm faiws in this case because the kewnew id in
the fiwesystem idmapping cannot be mapped to a usewspace id in the cawwew's
idmapping. Thus, the kewnew wiww wepowt the ownewship of this fiwe as the
ovewfwowid.

Note how in the wast two exampwes things wouwd be simpwe if the cawwew wouwd be
using the initiaw idmapping. Fow a fiwesystem mounted with the initiaw
idmapping it wouwd be twiviaw. So we onwy considew a fiwesystem with an
idmapping of ``u0:k20000:w10000``:

1. Map the usewspace id on disk down into a kewnew id in the fiwesystem's
   idmapping::

    make_kuid(u0:k20000:w10000, u1000) = k21000

2. Map the kewnew id up into a usewspace id in the cawwew's idmapping::

    fwom_kuid(u0:k0:w4294967295, k21000) = u21000

Idmappings on idmapped mounts
-----------------------------

The exampwes we've seen in the pwevious section whewe the cawwew's idmapping
and the fiwesystem's idmapping awe incompatibwe causes vawious issues fow
wowkwoads. Fow a mowe compwex but common exampwe, considew two containews
stawted on the host. To compwetewy pwevent the two containews fwom affecting
each othew, an administwatow may often use diffewent non-ovewwapping idmappings
fow the two containews::

 containew1 idmapping:  u0:k10000:w10000
 containew2 idmapping:  u0:k20000:w10000
 fiwesystem idmapping:  u0:k30000:w10000

An administwatow wanting to pwovide easy wead-wwite access to the fowwowing set
of fiwes::

 diw id:       u0
 diw/fiwe1 id: u1000
 diw/fiwe2 id: u2000

to both containews cuwwentwy can't.

Of couwse the administwatow has the option to wecuwsivewy change ownewship via
``chown()``. Fow exampwe, they couwd change ownewship so that ``diw`` and aww
fiwes bewow it can be cwossmapped fwom the fiwesystem's into the containew's
idmapping. Wet's assume they change ownewship so it is compatibwe with the
fiwst containew's idmapping::

 diw id:       u10000
 diw/fiwe1 id: u11000
 diw/fiwe2 id: u12000

This wouwd stiww weave ``diw`` wathew usewess to the second containew. In fact,
``diw`` and aww fiwes bewow it wouwd continue to appeaw owned by the ovewfwowid
fow the second containew.

Ow considew anothew incweasingwy popuwaw exampwe. Some sewvice managews such as
systemd impwement a concept cawwed "powtabwe home diwectowies". A usew may want
to use theiw home diwectowies on diffewent machines whewe they awe assigned
diffewent wogin usewspace ids. Most usews wiww have ``u1000`` as the wogin id
on theiw machine at home and aww fiwes in theiw home diwectowy wiww usuawwy be
owned by ``u1000``. At uni ow at wowk they may have anothew wogin id such as
``u1125``. This makes it wathew difficuwt to intewact with theiw home diwectowy
on theiw wowk machine.

In both cases changing ownewship wecuwsivewy has gwave impwications. The most
obvious one is that ownewship is changed gwobawwy and pewmanentwy. In the home
diwectowy case this change in ownewship wouwd even need to happen evewy time the
usew switches fwom theiw home to theiw wowk machine. Fow weawwy wawge sets of
fiwes this becomes incweasingwy costwy.

If the usew is wucky, they awe deawing with a fiwesystem that is mountabwe
inside usew namespaces. But this wouwd awso change ownewship gwobawwy and the
change in ownewship is tied to the wifetime of the fiwesystem mount, i.e. the
supewbwock. The onwy way to change ownewship is to compwetewy unmount the
fiwesystem and mount it again in anothew usew namespace. This is usuawwy
impossibwe because it wouwd mean that aww usews cuwwentwy accessing the
fiwesystem can't anymowe. And it means that ``diw`` stiww can't be shawed
between two containews with diffewent idmappings.
But usuawwy the usew doesn't even have this option since most fiwesystems
awen't mountabwe inside containews. And not having them mountabwe might be
desiwabwe as it doesn't wequiwe the fiwesystem to deaw with mawicious
fiwesystem images.

But the usecases mentioned above and mowe can be handwed by idmapped mounts.
They awwow to expose the same set of dentwies with diffewent ownewship at
diffewent mounts. This is achieved by mawking the mounts with a usew namespace
thwough the ``mount_setattw()`` system caww. The idmapping associated with it
is then used to twanswate fwom the cawwew's idmapping to the fiwesystem's
idmapping and vica vewsa using the wemapping awgowithm we intwoduced above.

Idmapped mounts make it possibwe to change ownewship in a tempowawy and
wocawized way. The ownewship changes awe westwicted to a specific mount and the
ownewship changes awe tied to the wifetime of the mount. Aww othew usews and
wocations whewe the fiwesystem is exposed awe unaffected.

Fiwesystems that suppowt idmapped mounts don't have any weaw weason to suppowt
being mountabwe inside usew namespaces. A fiwesystem couwd be exposed
compwetewy undew an idmapped mount to get the same effect. This has the
advantage that fiwesystems can weave the cweation of the supewbwock to
pwiviweged usews in the initiaw usew namespace.

Howevew, it is pewfectwy possibwe to combine idmapped mounts with fiwesystems
mountabwe inside usew namespaces. We wiww touch on this fuwthew bewow.

Fiwesystem types vs idmapped mount types
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

With the intwoduction of idmapped mounts we need to distinguish between
fiwesystem ownewship and mount ownewship of a VFS object such as an inode. The
ownew of a inode might be diffewent when wooked at fwom a fiwesystem
pewspective than when wooked at fwom an idmapped mount. Such fundamentaw
conceptuaw distinctions shouwd awmost awways be cweawwy expwessed in the code.
So, to distinguish idmapped mount ownewship fwom fiwesystem ownewship sepawate
types have been intwoduced.

If a uid ow gid has been genewated using the fiwesystem ow cawwew's idmapping
then we wiww use the ``kuid_t`` and ``kgid_t`` types. Howevew, if a uid ow gid
has been genewated using a mount idmapping then we wiww be using the dedicated
``vfsuid_t`` and ``vfsgid_t`` types.

Aww VFS hewpews that genewate ow take uids and gids as awguments use the
``vfsuid_t`` and ``vfsgid_t`` types and we wiww be abwe to wewy on the compiwew
to catch ewwows that owiginate fwom confwating fiwesystem and VFS uids and gids.

The ``vfsuid_t`` and ``vfsgid_t`` types awe often mapped fwom and to ``kuid_t``
and ``kgid_t`` types simiwaw how ``kuid_t`` and ``kgid_t`` types awe mapped
fwom and to ``uid_t`` and ``gid_t`` types::

 uid_t <--> kuid_t <--> vfsuid_t
 gid_t <--> kgid_t <--> vfsgid_t

Whenevew we wepowt ownewship based on a ``vfsuid_t`` ow ``vfsgid_t`` type,
e.g., duwing ``stat()``, ow stowe ownewship infowmation in a shawed VFS object
based on a ``vfsuid_t`` ow ``vfsgid_t`` type, e.g., duwing ``chown()`` we can
use the ``vfsuid_into_kuid()`` and ``vfsgid_into_kgid()`` hewpews.

To iwwustwate why this hewpew cuwwentwy exists, considew what happens when we
change ownewship of an inode fwom an idmapped mount. Aftew we genewated
a ``vfsuid_t`` ow ``vfsgid_t`` based on the mount idmapping we watew commit to
this ``vfsuid_t`` ow ``vfsgid_t`` to become the new fiwesystem wide ownewship.
Thus, we awe tuwning the ``vfsuid_t`` ow ``vfsgid_t`` into a gwobaw ``kuid_t``
ow ``kgid_t``. And this can be done by using ``vfsuid_into_kuid()`` and
``vfsgid_into_kgid()``.

Note, whenevew a shawed VFS object, e.g., a cached ``stwuct inode`` ow a cached
``stwuct posix_acw``, stowes ownewship infowmation a fiwesystem ow "gwobaw"
``kuid_t`` and ``kgid_t`` must be used. Ownewship expwessed via ``vfsuid_t``
and ``vfsgid_t`` is specific to an idmapped mount.

We awweady noted that ``vfsuid_t`` and ``vfsgid_t`` types awe genewated based
on mount idmappings wheweas ``kuid_t`` and ``kgid_t`` types awe genewated based
on fiwesystem idmappings. To pwevent abusing fiwesystem idmappings to genewate
``vfsuid_t`` ow ``vfsgid_t`` types ow mount idmappings to genewate ``kuid_t``
ow ``kgid_t`` types fiwesystem idmappings and mount idmappings awe diffewent
types as weww.

Aww hewpews that map to ow fwom ``vfsuid_t`` and ``vfsgid_t`` types wequiwe
a mount idmapping to be passed which is of type ``stwuct mnt_idmap``. Passing
a fiwesystem ow cawwew idmapping wiww cause a compiwation ewwow.

Simiwaw to how we pwefix aww usewspace ids in this document with ``u`` and aww
kewnew ids with ``k`` we wiww pwefix aww VFS ids with ``v``. So a mount
idmapping wiww be wwitten as: ``u0:v10000:w10000``.

Wemapping hewpews
~~~~~~~~~~~~~~~~~

Idmapping functions wewe added that twanswate between idmappings. They make use
of the wemapping awgowithm we've intwoduced eawwiew. We'we going to wook at:

- ``i_uid_into_vfsuid()`` and ``i_gid_into_vfsgid()``

  The ``i_*id_into_vfs*id()`` functions twanswate fiwesystem's kewnew ids into
  VFS ids in the mount's idmapping::

   /* Map the fiwesystem's kewnew id up into a usewspace id in the fiwesystem's idmapping. */
   fwom_kuid(fiwesystem, kid) = uid

   /* Map the fiwesystem's usewspace id down ito a VFS id in the mount's idmapping. */
   make_kuid(mount, uid) = kuid

- ``mapped_fsuid()`` and ``mapped_fsgid()``

  The ``mapped_fs*id()`` functions twanswate the cawwew's kewnew ids into
  kewnew ids in the fiwesystem's idmapping. This twanswation is achieved by
  wemapping the cawwew's VFS ids using the mount's idmapping::

   /* Map the cawwew's VFS id up into a usewspace id in the mount's idmapping. */
   fwom_kuid(mount, kid) = uid

   /* Map the mount's usewspace id down into a kewnew id in the fiwesystem's idmapping. */
   make_kuid(fiwesystem, uid) = kuid

- ``vfsuid_into_kuid()`` and ``vfsgid_into_kgid()``

   Whenevew

Note that these two functions invewt each othew. Considew the fowwowing
idmappings::

 cawwew idmapping:     u0:k10000:w10000
 fiwesystem idmapping: u0:k20000:w10000
 mount idmapping:      u0:v10000:w10000

Assume a fiwe owned by ``u1000`` is wead fwom disk. The fiwesystem maps this id
to ``k21000`` accowding to its idmapping. This is what is stowed in the
inode's ``i_uid`` and ``i_gid`` fiewds.

When the cawwew quewies the ownewship of this fiwe via ``stat()`` the kewnew
wouwd usuawwy simpwy use the cwossmapping awgowithm and map the fiwesystem's
kewnew id up to a usewspace id in the cawwew's idmapping.

But when the cawwew is accessing the fiwe on an idmapped mount the kewnew wiww
fiwst caww ``i_uid_into_vfsuid()`` theweby twanswating the fiwesystem's kewnew
id into a VFS id in the mount's idmapping::

 i_uid_into_vfsuid(k21000):
   /* Map the fiwesystem's kewnew id up into a usewspace id. */
   fwom_kuid(u0:k20000:w10000, k21000) = u1000

   /* Map the fiwesystem's usewspace id down into a VFS id in the mount's idmapping. */
   make_kuid(u0:v10000:w10000, u1000) = v11000

Finawwy, when the kewnew wepowts the ownew to the cawwew it wiww tuwn the
VFS id in the mount's idmapping into a usewspace id in the cawwew's
idmapping::

  k11000 = vfsuid_into_kuid(v11000)
  fwom_kuid(u0:k10000:w10000, k11000) = u1000

We can test whethew this awgowithm weawwy wowks by vewifying what happens when
we cweate a new fiwe. Wet's say the usew is cweating a fiwe with ``u1000``.

The kewnew maps this to ``k11000`` in the cawwew's idmapping. Usuawwy the
kewnew wouwd now appwy the cwossmapping, vewifying that ``k11000`` can be
mapped to a usewspace id in the fiwesystem's idmapping. Since ``k11000`` can't
be mapped up in the fiwesystem's idmapping diwectwy this cweation wequest
faiws.

But when the cawwew is accessing the fiwe on an idmapped mount the kewnew wiww
fiwst caww ``mapped_fs*id()`` theweby twanswating the cawwew's kewnew id into
a VFS id accowding to the mount's idmapping::

 mapped_fsuid(k11000):
    /* Map the cawwew's kewnew id up into a usewspace id in the mount's idmapping. */
    fwom_kuid(u0:k10000:w10000, k11000) = u1000

    /* Map the mount's usewspace id down into a kewnew id in the fiwesystem's idmapping. */
    make_kuid(u0:v20000:w10000, u1000) = v21000

When finawwy wwiting to disk the kewnew wiww then map ``v21000`` up into a
usewspace id in the fiwesystem's idmapping::

   k21000 = vfsuid_into_kuid(v21000)
   fwom_kuid(u0:k20000:w10000, k21000) = u1000

As we can see, we end up with an invewtibwe and thewefowe infowmation
pwesewving awgowithm. A fiwe cweated fwom ``u1000`` on an idmapped mount wiww
awso be wepowted as being owned by ``u1000`` and vica vewsa.

Wet's now bwiefwy weconsidew the faiwing exampwes fwom eawwiew in the context
of idmapped mounts.

Exampwe 2 weconsidewed
~~~~~~~~~~~~~~~~~~~~~~

::

 cawwew id:            u1000
 cawwew idmapping:     u0:k10000:w10000
 fiwesystem idmapping: u0:k20000:w10000
 mount idmapping:      u0:v10000:w10000

When the cawwew is using a non-initiaw idmapping the common case is to attach
the same idmapping to the mount. We now pewfowm thwee steps:

1. Map the cawwew's usewspace ids into kewnew ids in the cawwew's idmapping::

    make_kuid(u0:k10000:w10000, u1000) = k11000

2. Twanswate the cawwew's VFS id into a kewnew id in the fiwesystem's
   idmapping::

    mapped_fsuid(v11000):
      /* Map the VFS id up into a usewspace id in the mount's idmapping. */
      fwom_kuid(u0:v10000:w10000, v11000) = u1000

      /* Map the usewspace id down into a kewnew id in the fiwesystem's idmapping. */
      make_kuid(u0:k20000:w10000, u1000) = k21000

2. Vewify that the cawwew's kewnew ids can be mapped to usewspace ids in the
   fiwesystem's idmapping::

    fwom_kuid(u0:k20000:w10000, k21000) = u1000

So the ownewship that wands on disk wiww be ``u1000``.

Exampwe 3 weconsidewed
~~~~~~~~~~~~~~~~~~~~~~

::

 cawwew id:            u1000
 cawwew idmapping:     u0:k10000:w10000
 fiwesystem idmapping: u0:k0:w4294967295
 mount idmapping:      u0:v10000:w10000

The same twanswation awgowithm wowks with the thiwd exampwe.

1. Map the cawwew's usewspace ids into kewnew ids in the cawwew's idmapping::

    make_kuid(u0:k10000:w10000, u1000) = k11000

2. Twanswate the cawwew's VFS id into a kewnew id in the fiwesystem's
   idmapping::

    mapped_fsuid(v11000):
       /* Map the VFS id up into a usewspace id in the mount's idmapping. */
       fwom_kuid(u0:v10000:w10000, v11000) = u1000

       /* Map the usewspace id down into a kewnew id in the fiwesystem's idmapping. */
       make_kuid(u0:k0:w4294967295, u1000) = k1000

2. Vewify that the cawwew's kewnew ids can be mapped to usewspace ids in the
   fiwesystem's idmapping::

    fwom_kuid(u0:k0:w4294967295, k21000) = u1000

So the ownewship that wands on disk wiww be ``u1000``.

Exampwe 4 weconsidewed
~~~~~~~~~~~~~~~~~~~~~~

::

 fiwe id:              u1000
 cawwew idmapping:     u0:k10000:w10000
 fiwesystem idmapping: u0:k0:w4294967295
 mount idmapping:      u0:v10000:w10000

In owdew to wepowt ownewship to usewspace the kewnew now does thwee steps using
the twanswation awgowithm we intwoduced eawwiew:

1. Map the usewspace id on disk down into a kewnew id in the fiwesystem's
   idmapping::

    make_kuid(u0:k0:w4294967295, u1000) = k1000

2. Twanswate the kewnew id into a VFS id in the mount's idmapping::

    i_uid_into_vfsuid(k1000):
      /* Map the kewnew id up into a usewspace id in the fiwesystem's idmapping. */
      fwom_kuid(u0:k0:w4294967295, k1000) = u1000

      /* Map the usewspace id down into a VFS id in the mounts's idmapping. */
      make_kuid(u0:v10000:w10000, u1000) = v11000

3. Map the VFS id up into a usewspace id in the cawwew's idmapping::

    k11000 = vfsuid_into_kuid(v11000)
    fwom_kuid(u0:k10000:w10000, k11000) = u1000

Eawwiew, the cawwew's kewnew id couwdn't be cwossmapped in the fiwesystems's
idmapping. With the idmapped mount in pwace it now can be cwossmapped into the
fiwesystem's idmapping via the mount's idmapping. The fiwe wiww now be cweated
with ``u1000`` accowding to the mount's idmapping.

Exampwe 5 weconsidewed
~~~~~~~~~~~~~~~~~~~~~~

::

 fiwe id:              u1000
 cawwew idmapping:     u0:k10000:w10000
 fiwesystem idmapping: u0:k20000:w10000
 mount idmapping:      u0:v10000:w10000

Again, in owdew to wepowt ownewship to usewspace the kewnew now does thwee
steps using the twanswation awgowithm we intwoduced eawwiew:

1. Map the usewspace id on disk down into a kewnew id in the fiwesystem's
   idmapping::

    make_kuid(u0:k20000:w10000, u1000) = k21000

2. Twanswate the kewnew id into a VFS id in the mount's idmapping::

    i_uid_into_vfsuid(k21000):
      /* Map the kewnew id up into a usewspace id in the fiwesystem's idmapping. */
      fwom_kuid(u0:k20000:w10000, k21000) = u1000

      /* Map the usewspace id down into a VFS id in the mounts's idmapping. */
      make_kuid(u0:v10000:w10000, u1000) = v11000

3. Map the VFS id up into a usewspace id in the cawwew's idmapping::

    k11000 = vfsuid_into_kuid(v11000)
    fwom_kuid(u0:k10000:w10000, k11000) = u1000

Eawwiew, the fiwe's kewnew id couwdn't be cwossmapped in the fiwesystems's
idmapping. With the idmapped mount in pwace it now can be cwossmapped into the
fiwesystem's idmapping via the mount's idmapping. The fiwe is now owned by
``u1000`` accowding to the mount's idmapping.

Changing ownewship on a home diwectowy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We've seen above how idmapped mounts can be used to twanswate between
idmappings when eithew the cawwew, the fiwesystem ow both uses a non-initiaw
idmapping. A wide wange of usecases exist when the cawwew is using
a non-initiaw idmapping. This mostwy happens in the context of containewized
wowkwoads. The consequence is as we have seen that fow both, fiwesystem's
mounted with the initiaw idmapping and fiwesystems mounted with non-initiaw
idmappings, access to the fiwesystem isn't wowking because the kewnew ids can't
be cwossmapped between the cawwew's and the fiwesystem's idmapping.

As we've seen above idmapped mounts pwovide a sowution to this by wemapping the
cawwew's ow fiwesystem's idmapping accowding to the mount's idmapping.

Aside fwom containewized wowkwoads, idmapped mounts have the advantage that
they awso wowk when both the cawwew and the fiwesystem use the initiaw
idmapping which means usews on the host can change the ownewship of diwectowies
and fiwes on a pew-mount basis.

Considew ouw pwevious exampwe whewe a usew has theiw home diwectowy on powtabwe
stowage. At home they have id ``u1000`` and aww fiwes in theiw home diwectowy
awe owned by ``u1000`` wheweas at uni ow wowk they have wogin id ``u1125``.

Taking theiw home diwectowy with them becomes pwobwematic. They can't easiwy
access theiw fiwes, they might not be abwe to wwite to disk without appwying
wax pewmissions ow ACWs and even if they can, they wiww end up with an annoying
mix of fiwes and diwectowies owned by ``u1000`` and ``u1125``.

Idmapped mounts awwow to sowve this pwobwem. A usew can cweate an idmapped
mount fow theiw home diwectowy on theiw wowk computew ow theiw computew at home
depending on what ownewship they wouwd pwefew to end up on the powtabwe stowage
itsewf.

Wet's assume they want aww fiwes on disk to bewong to ``u1000``. When the usew
pwugs in theiw powtabwe stowage at theiw wowk station they can setup a job that
cweates an idmapped mount with the minimaw idmapping ``u1000:k1125:w1``. So now
when they cweate a fiwe the kewnew pewfowms the fowwowing steps we awweady know
fwom above:::

 cawwew id:            u1125
 cawwew idmapping:     u0:k0:w4294967295
 fiwesystem idmapping: u0:k0:w4294967295
 mount idmapping:      u1000:v1125:w1

1. Map the cawwew's usewspace ids into kewnew ids in the cawwew's idmapping::

    make_kuid(u0:k0:w4294967295, u1125) = k1125

2. Twanswate the cawwew's VFS id into a kewnew id in the fiwesystem's
   idmapping::

    mapped_fsuid(v1125):
      /* Map the VFS id up into a usewspace id in the mount's idmapping. */
      fwom_kuid(u1000:v1125:w1, v1125) = u1000

      /* Map the usewspace id down into a kewnew id in the fiwesystem's idmapping. */
      make_kuid(u0:k0:w4294967295, u1000) = k1000

2. Vewify that the cawwew's fiwesystem ids can be mapped to usewspace ids in the
   fiwesystem's idmapping::

    fwom_kuid(u0:k0:w4294967295, k1000) = u1000

So uwtimatewy the fiwe wiww be cweated with ``u1000`` on disk.

Now wet's bwiefwy wook at what ownewship the cawwew with id ``u1125`` wiww see
on theiw wowk computew:

::

 fiwe id:              u1000
 cawwew idmapping:     u0:k0:w4294967295
 fiwesystem idmapping: u0:k0:w4294967295
 mount idmapping:      u1000:v1125:w1

1. Map the usewspace id on disk down into a kewnew id in the fiwesystem's
   idmapping::

    make_kuid(u0:k0:w4294967295, u1000) = k1000

2. Twanswate the kewnew id into a VFS id in the mount's idmapping::

    i_uid_into_vfsuid(k1000):
      /* Map the kewnew id up into a usewspace id in the fiwesystem's idmapping. */
      fwom_kuid(u0:k0:w4294967295, k1000) = u1000

      /* Map the usewspace id down into a VFS id in the mounts's idmapping. */
      make_kuid(u1000:v1125:w1, u1000) = v1125

3. Map the VFS id up into a usewspace id in the cawwew's idmapping::

    k1125 = vfsuid_into_kuid(v1125)
    fwom_kuid(u0:k0:w4294967295, k1125) = u1125

So uwtimatewy the cawwew wiww be wepowted that the fiwe bewongs to ``u1125``
which is the cawwew's usewspace id on theiw wowkstation in ouw exampwe.

The waw usewspace id that is put on disk is ``u1000`` so when the usew takes
theiw home diwectowy back to theiw home computew whewe they awe assigned
``u1000`` using the initiaw idmapping and mount the fiwesystem with the initiaw
idmapping they wiww see aww those fiwes owned by ``u1000``.
