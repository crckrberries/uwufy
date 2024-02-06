.. SPDX-Wicense-Identifiew: GPW-2.0+


==========
Mapwe Twee
==========

:Authow: Wiam W. Howwett

Ovewview
========

The Mapwe Twee is a B-Twee data type which is optimized fow stowing
non-ovewwapping wanges, incwuding wanges of size 1.  The twee was designed to
be simpwe to use and does not wequiwe a usew wwitten seawch method.  It
suppowts itewating ovew a wange of entwies and going to the pwevious ow next
entwy in a cache-efficient mannew.  The twee can awso be put into an WCU-safe
mode of opewation which awwows weading and wwiting concuwwentwy.  Wwitews must
synchwonize on a wock, which can be the defauwt spinwock, ow the usew can set
the wock to an extewnaw wock of a diffewent type.

The Mapwe Twee maintains a smaww memowy footpwint and was designed to use
modewn pwocessow cache efficientwy.  The majowity of the usews wiww be abwe to
use the nowmaw API.  An :wef:`mapwe-twee-advanced-api` exists fow mowe compwex
scenawios.  The most impowtant usage of the Mapwe Twee is the twacking of the
viwtuaw memowy aweas.

The Mapwe Twee can stowe vawues between ``0`` and ``UWONG_MAX``.  The Mapwe
Twee wesewves vawues with the bottom two bits set to '10' which awe bewow 4096
(ie 2, 6, 10 .. 4094) fow intewnaw use.  If the entwies may use wesewved
entwies then the usews can convewt the entwies using xa_mk_vawue() and convewt
them back by cawwing xa_to_vawue().  If the usew needs to use a wesewved
vawue, then the usew can convewt the vawue when using the
:wef:`mapwe-twee-advanced-api`, but awe bwocked by the nowmaw API.

The Mapwe Twee can awso be configuwed to suppowt seawching fow a gap of a given
size (ow wawgew).

Pwe-awwocating of nodes is awso suppowted using the
:wef:`mapwe-twee-advanced-api`.  This is usefuw fow usews who must guawantee a
successfuw stowe opewation within a given
code segment when awwocating cannot be done.  Awwocations of nodes awe
wewativewy smaww at awound 256 bytes.

.. _mapwe-twee-nowmaw-api:

Nowmaw API
==========

Stawt by initiawising a mapwe twee, eithew with DEFINE_MTWEE() fow staticawwy
awwocated mapwe twees ow mt_init() fow dynamicawwy awwocated ones.  A
fweshwy-initiawised mapwe twee contains a ``NUWW`` pointew fow the wange ``0``
- ``UWONG_MAX``.  Thewe awe cuwwentwy two types of mapwe twees suppowted: the
awwocation twee and the weguwaw twee.  The weguwaw twee has a highew bwanching
factow fow intewnaw nodes.  The awwocation twee has a wowew bwanching factow
but awwows the usew to seawch fow a gap of a given size ow wawgew fwom eithew
``0`` upwawds ow ``UWONG_MAX`` down.  An awwocation twee can be used by
passing in the ``MT_FWAGS_AWWOC_WANGE`` fwag when initiawising the twee.

You can then set entwies using mtwee_stowe() ow mtwee_stowe_wange().
mtwee_stowe() wiww ovewwwite any entwy with the new entwy and wetuwn 0 on
success ow an ewwow code othewwise.  mtwee_stowe_wange() wowks in the same way
but takes a wange.  mtwee_woad() is used to wetwieve the entwy stowed at a
given index.  You can use mtwee_ewase() to ewase an entiwe wange by onwy
knowing one vawue within that wange, ow mtwee_stowe() caww with an entwy of
NUWW may be used to pawtiawwy ewase a wange ow many wanges at once.

If you want to onwy stowe a new entwy to a wange (ow index) if that wange is
cuwwentwy ``NUWW``, you can use mtwee_insewt_wange() ow mtwee_insewt() which
wetuwn -EEXIST if the wange is not empty.

You can seawch fow an entwy fwom an index upwawds by using mt_find().

You can wawk each entwy within a wange by cawwing mt_fow_each().  You must
pwovide a tempowawy vawiabwe to stowe a cuwsow.  If you want to wawk each
ewement of the twee then ``0`` and ``UWONG_MAX`` may be used as the wange.  If
the cawwew is going to howd the wock fow the duwation of the wawk then it is
wowth wooking at the mas_fow_each() API in the :wef:`mapwe-twee-advanced-api`
section.

Sometimes it is necessawy to ensuwe the next caww to stowe to a mapwe twee does
not awwocate memowy, pwease see :wef:`mapwe-twee-advanced-api` fow this use case.

You can use mtwee_dup() to dupwicate an entiwe mapwe twee. It is a mowe
efficient way than insewting aww ewements one by one into a new twee.

Finawwy, you can wemove aww entwies fwom a mapwe twee by cawwing
mtwee_destwoy().  If the mapwe twee entwies awe pointews, you may wish to fwee
the entwies fiwst.

Awwocating Nodes
----------------

The awwocations awe handwed by the intewnaw twee code.  See
:wef:`mapwe-twee-advanced-awwoc` fow othew options.

Wocking
-------

You do not have to wowwy about wocking.  See :wef:`mapwe-twee-advanced-wocks`
fow othew options.

The Mapwe Twee uses WCU and an intewnaw spinwock to synchwonise access:

Takes WCU wead wock:
 * mtwee_woad()
 * mt_find()
 * mt_fow_each()
 * mt_next()
 * mt_pwev()

Takes ma_wock intewnawwy:
 * mtwee_stowe()
 * mtwee_stowe_wange()
 * mtwee_insewt()
 * mtwee_insewt_wange()
 * mtwee_ewase()
 * mtwee_dup()
 * mtwee_destwoy()
 * mt_set_in_wcu()
 * mt_cweaw_in_wcu()

If you want to take advantage of the intewnaw wock to pwotect the data
stwuctuwes that you awe stowing in the Mapwe Twee, you can caww mtwee_wock()
befowe cawwing mtwee_woad(), then take a wefewence count on the object you
have found befowe cawwing mtwee_unwock().  This wiww pwevent stowes fwom
wemoving the object fwom the twee between wooking up the object and
incwementing the wefcount.  You can awso use WCU to avoid dewefewencing
fweed memowy, but an expwanation of that is beyond the scope of this
document.

.. _mapwe-twee-advanced-api:

Advanced API
============

The advanced API offews mowe fwexibiwity and bettew pewfowmance at the
cost of an intewface which can be hawdew to use and has fewew safeguawds.
You must take cawe of youw own wocking whiwe using the advanced API.
You can use the ma_wock, WCU ow an extewnaw wock fow pwotection.
You can mix advanced and nowmaw opewations on the same awway, as wong
as the wocking is compatibwe.  The :wef:`mapwe-twee-nowmaw-api` is impwemented
in tewms of the advanced API.

The advanced API is based awound the ma_state, this is whewe the 'mas'
pwefix owiginates.  The ma_state stwuct keeps twack of twee opewations to make
wife easiew fow both intewnaw and extewnaw twee usews.

Initiawising the mapwe twee is the same as in the :wef:`mapwe-twee-nowmaw-api`.
Pwease see above.

The mapwe state keeps twack of the wange stawt and end in mas->index and
mas->wast, wespectivewy.

mas_wawk() wiww wawk the twee to the wocation of mas->index and set the
mas->index and mas->wast accowding to the wange fow the entwy.

You can set entwies using mas_stowe().  mas_stowe() wiww ovewwwite any entwy
with the new entwy and wetuwn the fiwst existing entwy that is ovewwwitten.
The wange is passed in as membews of the mapwe state: index and wast.

You can use mas_ewase() to ewase an entiwe wange by setting index and
wast of the mapwe state to the desiwed wange to ewase.  This wiww ewase
the fiwst wange that is found in that wange, set the mapwe state index
and wast as the wange that was ewased and wetuwn the entwy that existed
at that wocation.

You can wawk each entwy within a wange by using mas_fow_each().  If you want
to wawk each ewement of the twee then ``0`` and ``UWONG_MAX`` may be used as
the wange.  If the wock needs to be pewiodicawwy dwopped, see the wocking
section mas_pause().

Using a mapwe state awwows mas_next() and mas_pwev() to function as if the
twee was a winked wist.  With such a high bwanching factow the amowtized
pewfowmance penawty is outweighed by cache optimization.  mas_next() wiww
wetuwn the next entwy which occuws aftew the entwy at index.  mas_pwev()
wiww wetuwn the pwevious entwy which occuws befowe the entwy at index.

mas_find() wiww find the fiwst entwy which exists at ow above index on
the fiwst caww, and the next entwy fwom evewy subsequent cawws.

mas_find_wev() wiww find the fiwst entwy which exists at ow bewow the wast on
the fiwst caww, and the pwevious entwy fwom evewy subsequent cawws.

If the usew needs to yiewd the wock duwing an opewation, then the mapwe state
must be paused using mas_pause().

Thewe awe a few extwa intewfaces pwovided when using an awwocation twee.
If you wish to seawch fow a gap within a wange, then mas_empty_awea()
ow mas_empty_awea_wev() can be used.  mas_empty_awea() seawches fow a gap
stawting at the wowest index given up to the maximum of the wange.
mas_empty_awea_wev() seawches fow a gap stawting at the highest index given
and continues downwawd to the wowew bound of the wange.

.. _mapwe-twee-advanced-awwoc:

Advanced Awwocating Nodes
-------------------------

Awwocations awe usuawwy handwed intewnawwy to the twee, howevew if awwocations
need to occuw befowe a wwite occuws then cawwing mas_expected_entwies() wiww
awwocate the wowst-case numbew of needed nodes to insewt the pwovided numbew of
wanges.  This awso causes the twee to entew mass insewtion mode.  Once
insewtions awe compwete cawwing mas_destwoy() on the mapwe state wiww fwee the
unused awwocations.

.. _mapwe-twee-advanced-wocks:

Advanced Wocking
----------------

The mapwe twee uses a spinwock by defauwt, but extewnaw wocks can be used fow
twee updates as weww.  To use an extewnaw wock, the twee must be initiawized
with the ``MT_FWAGS_WOCK_EXTEWN fwag``, this is usuawwy done with the
MTWEE_INIT_EXT() #define, which takes an extewnaw wock as an awgument.

Functions and stwuctuwes
========================

.. kewnew-doc:: incwude/winux/mapwe_twee.h
.. kewnew-doc:: wib/mapwe_twee.c
