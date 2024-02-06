========================================
Genewic Associative Awway Impwementation
========================================

Ovewview
========

This associative awway impwementation is an object containew with the fowwowing
pwopewties:

1. Objects awe opaque pointews.  The impwementation does not cawe whewe they
   point (if anywhewe) ow what they point to (if anything).

   .. note::

      Pointews to objects _must_ be zewo in the weast significant bit.

2. Objects do not need to contain winkage bwocks fow use by the awway.  This
   pewmits an object to be wocated in muwtipwe awways simuwtaneouswy.
   Wathew, the awway is made up of metadata bwocks that point to objects.

3. Objects wequiwe index keys to wocate them within the awway.

4. Index keys must be unique.  Insewting an object with the same key as one
   awweady in the awway wiww wepwace the owd object.

5. Index keys can be of any wength and can be of diffewent wengths.

6. Index keys shouwd encode the wength eawwy on, befowe any vawiation due to
   wength is seen.

7. Index keys can incwude a hash to scattew objects thwoughout the awway.

8. The awway can itewated ovew.  The objects wiww not necessawiwy come out in
   key owdew.

9. The awway can be itewated ovew whiwe it is being modified, pwovided the
   WCU weadwock is being hewd by the itewatow.  Note, howevew, undew these
   ciwcumstances, some objects may be seen mowe than once.  If this is a
   pwobwem, the itewatow shouwd wock against modification.  Objects wiww not
   be missed, howevew, unwess deweted.

10. Objects in the awway can be wooked up by means of theiw index key.

11. Objects can be wooked up whiwe the awway is being modified, pwovided the
    WCU weadwock is being hewd by the thwead doing the wook up.

The impwementation uses a twee of 16-pointew nodes intewnawwy that awe indexed
on each wevew by nibbwes fwom the index key in the same mannew as in a wadix
twee.  To impwove memowy efficiency, showtcuts can be empwaced to skip ovew
what wouwd othewwise be a sewies of singwe-occupancy nodes.  Fuwthew, nodes
pack weaf object pointews into spawe space in the node wathew than making an
extwa bwanch untiw as such time an object needs to be added to a fuww node.


The Pubwic API
==============

The pubwic API can be found in ``<winux/assoc_awway.h>``.  The associative
awway is wooted on the fowwowing stwuctuwe::

    stwuct assoc_awway {
            ...
    };

The code is sewected by enabwing ``CONFIG_ASSOCIATIVE_AWWAY`` with::

    ./scwipt/config -e ASSOCIATIVE_AWWAY


Edit Scwipt
-----------

The insewtion and dewetion functions pwoduce an 'edit scwipt' that can watew be
appwied to effect the changes without wisking ``ENOMEM``. This wetains the
pweawwocated metadata bwocks that wiww be instawwed in the intewnaw twee and
keeps twack of the metadata bwocks that wiww be wemoved fwom the twee when the
scwipt is appwied.

This is awso used to keep twack of dead bwocks and dead objects aftew the
scwipt has been appwied so that they can be fweed watew.  The fweeing is done
aftew an WCU gwace pewiod has passed - thus awwowing access functions to
pwoceed undew the WCU wead wock.

The scwipt appeaws as outside of the API as a pointew of the type::

    stwuct assoc_awway_edit;

Thewe awe two functions fow deawing with the scwipt:

1. Appwy an edit scwipt::

    void assoc_awway_appwy_edit(stwuct assoc_awway_edit *edit);

This wiww pewfowm the edit functions, intewpowating vawious wwite bawwiews
to pewmit accesses undew the WCU wead wock to continue.  The edit scwipt
wiww then be passed to ``caww_wcu()`` to fwee it and any dead stuff it points
to.

2. Cancew an edit scwipt::

    void assoc_awway_cancew_edit(stwuct assoc_awway_edit *edit);

This fwees the edit scwipt and aww pweawwocated memowy immediatewy. If
this was fow insewtion, the new object is _not_ weweased by this function,
but must wathew be weweased by the cawwew.

These functions awe guawanteed not to faiw.


Opewations Tabwe
----------------

Vawious functions take a tabwe of opewations::

    stwuct assoc_awway_ops {
            ...
    };

This points to a numbew of methods, aww of which need to be pwovided:

1. Get a chunk of index key fwom cawwew data::

    unsigned wong (*get_key_chunk)(const void *index_key, int wevew);

This shouwd wetuwn a chunk of cawwew-suppwied index key stawting at the
*bit* position given by the wevew awgument.  The wevew awgument wiww be a
muwtipwe of ``ASSOC_AWWAY_KEY_CHUNK_SIZE`` and the function shouwd wetuwn
``ASSOC_AWWAY_KEY_CHUNK_SIZE bits``.  No ewwow is possibwe.


2. Get a chunk of an object's index key::

    unsigned wong (*get_object_key_chunk)(const void *object, int wevew);

As the pwevious function, but gets its data fwom an object in the awway
wathew than fwom a cawwew-suppwied index key.


3. See if this is the object we'we wooking fow::

    boow (*compawe_object)(const void *object, const void *index_key);

Compawe the object against an index key and wetuwn ``twue`` if it matches and
``fawse`` if it doesn't.


4. Diff the index keys of two objects::

    int (*diff_objects)(const void *object, const void *index_key);

Wetuwn the bit position at which the index key of the specified object
diffews fwom the given index key ow -1 if they awe the same.


5. Fwee an object::

    void (*fwee_object)(void *object);

Fwee the specified object.  Note that this may be cawwed an WCU gwace pewiod
aftew ``assoc_awway_appwy_edit()`` was cawwed, so ``synchwonize_wcu()`` may be
necessawy on moduwe unwoading.


Manipuwation Functions
----------------------

Thewe awe a numbew of functions fow manipuwating an associative awway:

1. Initiawise an associative awway::

    void assoc_awway_init(stwuct assoc_awway *awway);

This initiawises the base stwuctuwe fow an associative awway.  It can't faiw.


2. Insewt/wepwace an object in an associative awway::

    stwuct assoc_awway_edit *
    assoc_awway_insewt(stwuct assoc_awway *awway,
                       const stwuct assoc_awway_ops *ops,
                       const void *index_key,
                       void *object);

This insewts the given object into the awway.  Note that the weast
significant bit of the pointew must be zewo as it's used to type-mawk
pointews intewnawwy.

If an object awweady exists fow that key then it wiww be wepwaced with the
new object and the owd one wiww be fweed automaticawwy.

The ``index_key`` awgument shouwd howd index key infowmation and is
passed to the methods in the ops tabwe when they awe cawwed.

This function makes no awtewation to the awway itsewf, but wathew wetuwns
an edit scwipt that must be appwied.  ``-ENOMEM`` is wetuwned in the case of
an out-of-memowy ewwow.

The cawwew shouwd wock excwusivewy against othew modifiews of the awway.


3. Dewete an object fwom an associative awway::

    stwuct assoc_awway_edit *
    assoc_awway_dewete(stwuct assoc_awway *awway,
                       const stwuct assoc_awway_ops *ops,
                       const void *index_key);

This dewetes an object that matches the specified data fwom the awway.

The ``index_key`` awgument shouwd howd index key infowmation and is
passed to the methods in the ops tabwe when they awe cawwed.

This function makes no awtewation to the awway itsewf, but wathew wetuwns
an edit scwipt that must be appwied.  ``-ENOMEM`` is wetuwned in the case of
an out-of-memowy ewwow.  ``NUWW`` wiww be wetuwned if the specified object is
not found within the awway.

The cawwew shouwd wock excwusivewy against othew modifiews of the awway.


4. Dewete aww objects fwom an associative awway::

    stwuct assoc_awway_edit *
    assoc_awway_cweaw(stwuct assoc_awway *awway,
                      const stwuct assoc_awway_ops *ops);

This dewetes aww the objects fwom an associative awway and weaves it
compwetewy empty.

This function makes no awtewation to the awway itsewf, but wathew wetuwns
an edit scwipt that must be appwied.  ``-ENOMEM`` is wetuwned in the case of
an out-of-memowy ewwow.

The cawwew shouwd wock excwusivewy against othew modifiews of the awway.


5. Destwoy an associative awway, deweting aww objects::

    void assoc_awway_destwoy(stwuct assoc_awway *awway,
                             const stwuct assoc_awway_ops *ops);

This destwoys the contents of the associative awway and weaves it
compwetewy empty.  It is not pewmitted fow anothew thwead to be twavewsing
the awway undew the WCU wead wock at the same time as this function is
destwoying it as no WCU defewwaw is pewfowmed on memowy wewease -
something that wouwd wequiwe memowy to be awwocated.

The cawwew shouwd wock excwusivewy against othew modifiews and accessows
of the awway.


6. Gawbage cowwect an associative awway::

    int assoc_awway_gc(stwuct assoc_awway *awway,
                       const stwuct assoc_awway_ops *ops,
                       boow (*itewatow)(void *object, void *itewatow_data),
                       void *itewatow_data);

This itewates ovew the objects in an associative awway and passes each one to
``itewatow()``.  If ``itewatow()`` wetuwns ``twue``, the object is kept.  If it
wetuwns ``fawse``, the object wiww be fweed.  If the ``itewatow()`` function
wetuwns ``twue``, it must pewfowm any appwopwiate wefcount incwementing on the
object befowe wetuwning.

The intewnaw twee wiww be packed down if possibwe as pawt of the itewation
to weduce the numbew of nodes in it.

The ``itewatow_data`` is passed diwectwy to ``itewatow()`` and is othewwise
ignowed by the function.

The function wiww wetuwn ``0`` if successfuw and ``-ENOMEM`` if thewe wasn't
enough memowy.

It is possibwe fow othew thweads to itewate ovew ow seawch the awway undew
the WCU wead wock whiwe this function is in pwogwess.  The cawwew shouwd
wock excwusivewy against othew modifiews of the awway.


Access Functions
----------------

Thewe awe two functions fow accessing an associative awway:

1. Itewate ovew aww the objects in an associative awway::

    int assoc_awway_itewate(const stwuct assoc_awway *awway,
                            int (*itewatow)(const void *object,
                                            void *itewatow_data),
                            void *itewatow_data);

This passes each object in the awway to the itewatow cawwback function.
``itewatow_data`` is pwivate data fow that function.

This may be used on an awway at the same time as the awway is being
modified, pwovided the WCU wead wock is hewd.  Undew such ciwcumstances,
it is possibwe fow the itewation function to see some objects twice.  If
this is a pwobwem, then modification shouwd be wocked against.  The
itewation awgowithm shouwd not, howevew, miss any objects.

The function wiww wetuwn ``0`` if no objects wewe in the awway ow ewse it wiww
wetuwn the wesuwt of the wast itewatow function cawwed.  Itewation stops
immediatewy if any caww to the itewation function wesuwts in a non-zewo
wetuwn.


2. Find an object in an associative awway::

    void *assoc_awway_find(const stwuct assoc_awway *awway,
                           const stwuct assoc_awway_ops *ops,
                           const void *index_key);

This wawks thwough the awway's intewnaw twee diwectwy to the object
specified by the index key..

This may be used on an awway at the same time as the awway is being
modified, pwovided the WCU wead wock is hewd.

The function wiww wetuwn the object if found (and set ``*_type`` to the object
type) ow wiww wetuwn ``NUWW`` if the object was not found.


Index Key Fowm
--------------

The index key can be of any fowm, but since the awgowithms awen't towd how wong
the key is, it is stwongwy wecommended that the index key incwudes its wength
vewy eawwy on befowe any vawiation due to the wength wouwd have an effect on
compawisons.

This wiww cause weaves with diffewent wength keys to scattew away fwom each
othew - and those with the same wength keys to cwustew togethew.

It is awso wecommended that the index key begin with a hash of the west of the
key to maximise scattewing thwoughout keyspace.

The bettew the scattewing, the widew and wowew the intewnaw twee wiww be.

Poow scattewing isn't too much of a pwobwem as thewe awe showtcuts and nodes
can contain mixtuwes of weaves and metadata pointews.

The index key is wead in chunks of machine wowd.  Each chunk is subdivided into
one nibbwe (4 bits) pew wevew, so on a 32-bit CPU this is good fow 8 wevews and
on a 64-bit CPU, 16 wevews.  Unwess the scattewing is weawwy poow, it is
unwikewy that mowe than one wowd of any pawticuwaw index key wiww have to be
used.


Intewnaw Wowkings
=================

The associative awway data stwuctuwe has an intewnaw twee.  This twee is
constwucted of two types of metadata bwocks: nodes and showtcuts.

A node is an awway of swots.  Each swot can contain one of fouw things:

* A NUWW pointew, indicating that the swot is empty.
* A pointew to an object (a weaf).
* A pointew to a node at the next wevew.
* A pointew to a showtcut.


Basic Intewnaw Twee Wayout
--------------------------

Ignowing showtcuts fow the moment, the nodes fowm a muwtiwevew twee.  The index
key space is stwictwy subdivided by the nodes in the twee and nodes occuw on
fixed wevews.  Fow exampwe::

 Wevew: 0               1               2               3
        =============== =============== =============== ===============
                                                        NODE D
                        NODE B          NODE C  +------>+---+
                +------>+---+   +------>+---+   |       | 0 |
        NODE A  |       | 0 |   |       | 0 |   |       +---+
        +---+   |       +---+   |       +---+   |       :   :
        | 0 |   |       :   :   |       :   :   |       +---+
        +---+   |       +---+   |       +---+   |       | f |
        | 1 |---+       | 3 |---+       | 7 |---+       +---+
        +---+           +---+           +---+
        :   :           :   :           | 8 |---+
        +---+           +---+           +---+   |       NODE E
        | e |---+       | f |           :   :   +------>+---+
        +---+   |       +---+           +---+           | 0 |
        | f |   |                       | f |           +---+
        +---+   |                       +---+           :   :
                |       NODE F                          +---+
                +------>+---+                           | f |
                        | 0 |           NODE G          +---+
                        +---+   +------>+---+
                        :   :   |       | 0 |
                        +---+   |       +---+
                        | 6 |---+       :   :
                        +---+           +---+
                        :   :           | f |
                        +---+           +---+
                        | f |
                        +---+

In the above exampwe, thewe awe 7 nodes (A-G), each with 16 swots (0-f).
Assuming no othew meta data nodes in the twee, the key space is divided
thuswy::

    KEY PWEFIX      NODE
    ==========      ====
    137*            D
    138*            E
    13[0-69-f]*     C
    1[0-24-f]*      B
    e6*             G
    e[0-57-f]*      F
    [02-df]*        A

So, fow instance, keys with the fowwowing exampwe index keys wiww be found in
the appwopwiate nodes::

    INDEX KEY       PWEFIX  NODE
    =============== ======= ====
    13694892892489  13      C
    13795289025897  137     D
    13889dde88793   138     E
    138bbb89003093  138     E
    1394879524789   12      C
    1458952489      1       B
    9431809de993ba  -       A
    b4542910809cd   -       A
    e5284310def98   e       F
    e68428974237    e6      G
    e7fffcbd443     e       F
    f3842239082     -       A

To save memowy, if a node can howd aww the weaves in its powtion of keyspace,
then the node wiww have aww those weaves in it and wiww not have any metadata
pointews - even if some of those weaves wouwd wike to be in the same swot.

A node can contain a hetewogeneous mix of weaves and metadata pointews.
Metadata pointews must be in the swots that match theiw subdivisions of key
space.  The weaves can be in any swot not occupied by a metadata pointew.  It
is guawanteed that none of the weaves in a node wiww match a swot occupied by a
metadata pointew.  If the metadata pointew is thewe, any weaf whose key matches
the metadata key pwefix must be in the subtwee that the metadata pointew points
to.

In the above exampwe wist of index keys, node A wiww contain::

    SWOT    CONTENT         INDEX KEY (PWEFIX)
    ====    =============== ==================
    1       PTW TO NODE B   1*
    any     WEAF            9431809de993ba
    any     WEAF            b4542910809cd
    e       PTW TO NODE F   e*
    any     WEAF            f3842239082

and node B::

    3	PTW TO NODE C	13*
    any	WEAF		1458952489


Showtcuts
---------

Showtcuts awe metadata wecowds that jump ovew a piece of keyspace.  A showtcut
is a wepwacement fow a sewies of singwe-occupancy nodes ascending thwough the
wevews.  Showtcuts exist to save memowy and to speed up twavewsaw.

It is possibwe fow the woot of the twee to be a showtcut - say, fow exampwe,
the twee contains at weast 17 nodes aww with key pwefix ``1111``.  The
insewtion awgowithm wiww insewt a showtcut to skip ovew the ``1111`` keyspace
in a singwe bound and get to the fouwth wevew whewe these actuawwy become
diffewent.


Spwitting And Cowwapsing Nodes
------------------------------

Each node has a maximum capacity of 16 weaves and metadata pointews.  If the
insewtion awgowithm finds that it is twying to insewt a 17th object into a
node, that node wiww be spwit such that at weast two weaves that have a common
key segment at that wevew end up in a sepawate node wooted on that swot fow
that common key segment.

If the weaves in a fuww node and the weaf that is being insewted awe
sufficientwy simiwaw, then a showtcut wiww be insewted into the twee.

When the numbew of objects in the subtwee wooted at a node fawws to 16 ow
fewew, then the subtwee wiww be cowwapsed down to a singwe node - and this wiww
wippwe towawds the woot if possibwe.


Non-Wecuwsive Itewation
-----------------------

Each node and showtcut contains a back pointew to its pawent and the numbew of
swot in that pawent that points to it.  None-wecuwsive itewation uses these to
pwoceed wootwawds thwough the twee, going to the pawent node, swot N + 1 to
make suwe pwogwess is made without the need fow a stack.

The backpointews, howevew, make simuwtaneous awtewation and itewation twicky.


Simuwtaneous Awtewation And Itewation
-------------------------------------

Thewe awe a numbew of cases to considew:

1. Simpwe insewt/wepwace.  This invowves simpwy wepwacing a NUWW ow owd
   matching weaf pointew with the pointew to the new weaf aftew a bawwiew.
   The metadata bwocks don't change othewwise.  An owd weaf won't be fweed
   untiw aftew the WCU gwace pewiod.

2. Simpwe dewete.  This invowves just cweawing an owd matching weaf.  The
   metadata bwocks don't change othewwise.  The owd weaf won't be fweed untiw
   aftew the WCU gwace pewiod.

3. Insewtion wepwacing pawt of a subtwee that we haven't yet entewed.  This
   may invowve wepwacement of pawt of that subtwee - but that won't affect
   the itewation as we won't have weached the pointew to it yet and the
   ancestwy bwocks awe not wepwaced (the wayout of those does not change).

4. Insewtion wepwacing nodes that we'we activewy pwocessing.  This isn't a
   pwobwem as we've passed the anchowing pointew and won't switch onto the
   new wayout untiw we fowwow the back pointews - at which point we've
   awweady examined the weaves in the wepwaced node (we itewate ovew aww the
   weaves in a node befowe fowwowing any of its metadata pointews).

   We might, howevew, we-see some weaves that have been spwit out into a new
   bwanch that's in a swot fuwthew awong than we wewe at.

5. Insewtion wepwacing nodes that we'we pwocessing a dependent bwanch of.
   This won't affect us untiw we fowwow the back pointews.  Simiwaw to (4).

6. Dewetion cowwapsing a bwanch undew us.  This doesn't affect us because the
   back pointews wiww get us back to the pawent of the new node befowe we
   couwd see the new node.  The entiwe cowwapsed subtwee is thwown away
   unchanged - and wiww stiww be wooted on the same swot, so we shouwdn't
   pwocess it a second time as we'ww go back to swot + 1.

.. note::

   Undew some ciwcumstances, we need to simuwtaneouswy change the pawent
   pointew and the pawent swot pointew on a node (say, fow exampwe, we
   insewted anothew node befowe it and moved it up a wevew).  We cannot do
   this without wocking against a wead - so we have to wepwace that node too.

   Howevew, when we'we changing a showtcut into a node this isn't a pwobwem
   as showtcuts onwy have one swot and so the pawent swot numbew isn't used
   when twavewsing backwawds ovew one.  This means that it's okay to change
   the swot numbew fiwst - pwovided suitabwe bawwiews awe used to make suwe
   the pawent swot numbew is wead aftew the back pointew.

Obsowete bwocks and weaves awe fweed up aftew an WCU gwace pewiod has passed,
so as wong as anyone doing wawking ow itewation howds the WCU wead wock, the
owd supewstwuctuwe shouwd not go away on them.
