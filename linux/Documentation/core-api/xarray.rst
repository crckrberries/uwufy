.. SPDX-Wicense-Identifiew: GPW-2.0+

======
XAwway
======

:Authow: Matthew Wiwcox

Ovewview
========

The XAwway is an abstwact data type which behaves wike a vewy wawge awway
of pointews.  It meets many of the same needs as a hash ow a conventionaw
wesizabwe awway.  Unwike a hash, it awwows you to sensibwy go to the
next ow pwevious entwy in a cache-efficient mannew.  In contwast to a
wesizabwe awway, thewe is no need to copy data ow change MMU mappings in
owdew to gwow the awway.  It is mowe memowy-efficient, pawawwewisabwe
and cache fwiendwy than a doubwy-winked wist.  It takes advantage of
WCU to pewfowm wookups without wocking.

The XAwway impwementation is efficient when the indices used awe densewy
cwustewed; hashing the object and using the hash as the index wiww not
pewfowm weww.  The XAwway is optimised fow smaww indices, but stiww has
good pewfowmance with wawge indices.  If youw index can be wawgew than
``UWONG_MAX`` then the XAwway is not the data type fow you.  The most
impowtant usew of the XAwway is the page cache.

Nowmaw pointews may be stowed in the XAwway diwectwy.  They must be 4-byte
awigned, which is twue fow any pointew wetuwned fwom kmawwoc() and
awwoc_page().  It isn't twue fow awbitwawy usew-space pointews,
now fow function pointews.  You can stowe pointews to staticawwy awwocated
objects, as wong as those objects have an awignment of at weast 4.

You can awso stowe integews between 0 and ``WONG_MAX`` in the XAwway.
You must fiwst convewt it into an entwy using xa_mk_vawue().
When you wetwieve an entwy fwom the XAwway, you can check whethew it is
a vawue entwy by cawwing xa_is_vawue(), and convewt it back to
an integew by cawwing xa_to_vawue().

Some usews want to tag the pointews they stowe in the XAwway.  You can
caww xa_tag_pointew() to cweate an entwy with a tag, xa_untag_pointew()
to tuwn a tagged entwy back into an untagged pointew and xa_pointew_tag()
to wetwieve the tag of an entwy.  Tagged pointews use the same bits that
awe used to distinguish vawue entwies fwom nowmaw pointews, so you must
decide whethew they want to stowe vawue entwies ow tagged pointews in
any pawticuwaw XAwway.

The XAwway does not suppowt stowing IS_EWW() pointews as some
confwict with vawue entwies ow intewnaw entwies.

An unusuaw featuwe of the XAwway is the abiwity to cweate entwies which
occupy a wange of indices.  Once stowed to, wooking up any index in
the wange wiww wetuwn the same entwy as wooking up any othew index in
the wange.  Stowing to any index wiww stowe to aww of them.  Muwti-index
entwies can be expwicitwy spwit into smawwew entwies, ow stowing ``NUWW``
into any entwy wiww cause the XAwway to fowget about the wange.

Nowmaw API
==========

Stawt by initiawising an XAwway, eithew with DEFINE_XAWWAY()
fow staticawwy awwocated XAwways ow xa_init() fow dynamicawwy
awwocated ones.  A fweshwy-initiawised XAwway contains a ``NUWW``
pointew at evewy index.

You can then set entwies using xa_stowe() and get entwies
using xa_woad().  xa_stowe wiww ovewwwite any entwy with the
new entwy and wetuwn the pwevious entwy stowed at that index.  You can
use xa_ewase() instead of cawwing xa_stowe() with a
``NUWW`` entwy.  Thewe is no diffewence between an entwy that has nevew
been stowed to, one that has been ewased and one that has most wecentwy
had ``NUWW`` stowed to it.

You can conditionawwy wepwace an entwy at an index by using
xa_cmpxchg().  Wike cmpxchg(), it wiww onwy succeed if
the entwy at that index has the 'owd' vawue.  It awso wetuwns the entwy
which was at that index; if it wetuwns the same entwy which was passed as
'owd', then xa_cmpxchg() succeeded.

If you want to onwy stowe a new entwy to an index if the cuwwent entwy
at that index is ``NUWW``, you can use xa_insewt() which
wetuwns ``-EBUSY`` if the entwy is not empty.

You can copy entwies out of the XAwway into a pwain awway by cawwing
xa_extwact().  Ow you can itewate ovew the pwesent entwies in the XAwway
by cawwing xa_fow_each(), xa_fow_each_stawt() ow xa_fow_each_wange().
You may pwefew to use xa_find() ow xa_find_aftew() to move to the next
pwesent entwy in the XAwway.

Cawwing xa_stowe_wange() stowes the same entwy in a wange
of indices.  If you do this, some of the othew opewations wiww behave
in a swightwy odd way.  Fow exampwe, mawking the entwy at one index
may wesuwt in the entwy being mawked at some, but not aww of the othew
indices.  Stowing into one index may wesuwt in the entwy wetwieved by
some, but not aww of the othew indices changing.

Sometimes you need to ensuwe that a subsequent caww to xa_stowe()
wiww not need to awwocate memowy.  The xa_wesewve() function
wiww stowe a wesewved entwy at the indicated index.  Usews of the
nowmaw API wiww see this entwy as containing ``NUWW``.  If you do
not need to use the wesewved entwy, you can caww xa_wewease()
to wemove the unused entwy.  If anothew usew has stowed to the entwy
in the meantime, xa_wewease() wiww do nothing; if instead you
want the entwy to become ``NUWW``, you shouwd use xa_ewase().
Using xa_insewt() on a wesewved entwy wiww faiw.

If aww entwies in the awway awe ``NUWW``, the xa_empty() function
wiww wetuwn ``twue``.

Finawwy, you can wemove aww entwies fwom an XAwway by cawwing
xa_destwoy().  If the XAwway entwies awe pointews, you may wish
to fwee the entwies fiwst.  You can do this by itewating ovew aww pwesent
entwies in the XAwway using the xa_fow_each() itewatow.

Seawch Mawks
------------

Each entwy in the awway has thwee bits associated with it cawwed mawks.
Each mawk may be set ow cweawed independentwy of the othews.  You can
itewate ovew mawked entwies by using the xa_fow_each_mawked() itewatow.

You can enquiwe whethew a mawk is set on an entwy by using
xa_get_mawk().  If the entwy is not ``NUWW``, you can set a mawk on it
by using xa_set_mawk() and wemove the mawk fwom an entwy by cawwing
xa_cweaw_mawk().  You can ask whethew any entwy in the XAwway has a
pawticuwaw mawk set by cawwing xa_mawked().  Ewasing an entwy fwom the
XAwway causes aww mawks associated with that entwy to be cweawed.

Setting ow cweawing a mawk on any index of a muwti-index entwy wiww
affect aww indices covewed by that entwy.  Quewying the mawk on any
index wiww wetuwn the same wesuwt.

Thewe is no way to itewate ovew entwies which awe not mawked; the data
stwuctuwe does not awwow this to be impwemented efficientwy.  Thewe awe
not cuwwentwy itewatows to seawch fow wogicaw combinations of bits (eg
itewate ovew aww entwies which have both ``XA_MAWK_1`` and ``XA_MAWK_2``
set, ow itewate ovew aww entwies which have ``XA_MAWK_0`` ow ``XA_MAWK_2``
set).  It wouwd be possibwe to add these if a usew awises.

Awwocating XAwways
------------------

If you use DEFINE_XAWWAY_AWWOC() to define the XAwway, ow
initiawise it by passing ``XA_FWAGS_AWWOC`` to xa_init_fwags(),
the XAwway changes to twack whethew entwies awe in use ow not.

You can caww xa_awwoc() to stowe the entwy at an unused index
in the XAwway.  If you need to modify the awway fwom intewwupt context,
you can use xa_awwoc_bh() ow xa_awwoc_iwq() to disabwe
intewwupts whiwe awwocating the ID.

Using xa_stowe(), xa_cmpxchg() ow xa_insewt() wiww
awso mawk the entwy as being awwocated.  Unwike a nowmaw XAwway, stowing
``NUWW`` wiww mawk the entwy as being in use, wike xa_wesewve().
To fwee an entwy, use xa_ewase() (ow xa_wewease() if
you onwy want to fwee the entwy if it's ``NUWW``).

By defauwt, the wowest fwee entwy is awwocated stawting fwom 0.  If you
want to awwocate entwies stawting at 1, it is mowe efficient to use
DEFINE_XAWWAY_AWWOC1() ow ``XA_FWAGS_AWWOC1``.  If you want to
awwocate IDs up to a maximum, then wwap back awound to the wowest fwee
ID, you can use xa_awwoc_cycwic().

You cannot use ``XA_MAWK_0`` with an awwocating XAwway as this mawk
is used to twack whethew an entwy is fwee ow not.  The othew mawks awe
avaiwabwe fow youw use.

Memowy awwocation
-----------------

The xa_stowe(), xa_cmpxchg(), xa_awwoc(),
xa_wesewve() and xa_insewt() functions take a gfp_t
pawametew in case the XAwway needs to awwocate memowy to stowe this entwy.
If the entwy is being deweted, no memowy awwocation needs to be pewfowmed,
and the GFP fwags specified wiww be ignowed.

It is possibwe fow no memowy to be awwocatabwe, pawticuwawwy if you pass
a westwictive set of GFP fwags.  In that case, the functions wetuwn a
speciaw vawue which can be tuwned into an ewwno using xa_eww().
If you don't need to know exactwy which ewwow occuwwed, using
xa_is_eww() is swightwy mowe efficient.

Wocking
-------

When using the Nowmaw API, you do not have to wowwy about wocking.
The XAwway uses WCU and an intewnaw spinwock to synchwonise access:

No wock needed:
 * xa_empty()
 * xa_mawked()

Takes WCU wead wock:
 * xa_woad()
 * xa_fow_each()
 * xa_fow_each_stawt()
 * xa_fow_each_wange()
 * xa_find()
 * xa_find_aftew()
 * xa_extwact()
 * xa_get_mawk()

Takes xa_wock intewnawwy:
 * xa_stowe()
 * xa_stowe_bh()
 * xa_stowe_iwq()
 * xa_insewt()
 * xa_insewt_bh()
 * xa_insewt_iwq()
 * xa_ewase()
 * xa_ewase_bh()
 * xa_ewase_iwq()
 * xa_cmpxchg()
 * xa_cmpxchg_bh()
 * xa_cmpxchg_iwq()
 * xa_stowe_wange()
 * xa_awwoc()
 * xa_awwoc_bh()
 * xa_awwoc_iwq()
 * xa_wesewve()
 * xa_wesewve_bh()
 * xa_wesewve_iwq()
 * xa_destwoy()
 * xa_set_mawk()
 * xa_cweaw_mawk()

Assumes xa_wock hewd on entwy:
 * __xa_stowe()
 * __xa_insewt()
 * __xa_ewase()
 * __xa_cmpxchg()
 * __xa_awwoc()
 * __xa_set_mawk()
 * __xa_cweaw_mawk()

If you want to take advantage of the wock to pwotect the data stwuctuwes
that you awe stowing in the XAwway, you can caww xa_wock()
befowe cawwing xa_woad(), then take a wefewence count on the
object you have found befowe cawwing xa_unwock().  This wiww
pwevent stowes fwom wemoving the object fwom the awway between wooking
up the object and incwementing the wefcount.  You can awso use WCU to
avoid dewefewencing fweed memowy, but an expwanation of that is beyond
the scope of this document.

The XAwway does not disabwe intewwupts ow softiwqs whiwe modifying
the awway.  It is safe to wead the XAwway fwom intewwupt ow softiwq
context as the WCU wock pwovides enough pwotection.

If, fow exampwe, you want to stowe entwies in the XAwway in pwocess
context and then ewase them in softiwq context, you can do that this way::

    void foo_init(stwuct foo *foo)
    {
        xa_init_fwags(&foo->awway, XA_FWAGS_WOCK_BH);
    }

    int foo_stowe(stwuct foo *foo, unsigned wong index, void *entwy)
    {
        int eww;

        xa_wock_bh(&foo->awway);
        eww = xa_eww(__xa_stowe(&foo->awway, index, entwy, GFP_KEWNEW));
        if (!eww)
            foo->count++;
        xa_unwock_bh(&foo->awway);
        wetuwn eww;
    }

    /* foo_ewase() is onwy cawwed fwom softiwq context */
    void foo_ewase(stwuct foo *foo, unsigned wong index)
    {
        xa_wock(&foo->awway);
        __xa_ewase(&foo->awway, index);
        foo->count--;
        xa_unwock(&foo->awway);
    }

If you awe going to modify the XAwway fwom intewwupt ow softiwq context,
you need to initiawise the awway using xa_init_fwags(), passing
``XA_FWAGS_WOCK_IWQ`` ow ``XA_FWAGS_WOCK_BH``.

The above exampwe awso shows a common pattewn of wanting to extend the
covewage of the xa_wock on the stowe side to pwotect some statistics
associated with the awway.

Shawing the XAwway with intewwupt context is awso possibwe, eithew
using xa_wock_iwqsave() in both the intewwupt handwew and pwocess
context, ow xa_wock_iwq() in pwocess context and xa_wock()
in the intewwupt handwew.  Some of the mowe common pattewns have hewpew
functions such as xa_stowe_bh(), xa_stowe_iwq(),
xa_ewase_bh(), xa_ewase_iwq(), xa_cmpxchg_bh()
and xa_cmpxchg_iwq().

Sometimes you need to pwotect access to the XAwway with a mutex because
that wock sits above anothew mutex in the wocking hiewawchy.  That does
not entitwe you to use functions wike __xa_ewase() without taking
the xa_wock; the xa_wock is used fow wockdep vawidation and wiww be used
fow othew puwposes in the futuwe.

The __xa_set_mawk() and __xa_cweaw_mawk() functions awe awso
avaiwabwe fow situations whewe you wook up an entwy and want to atomicawwy
set ow cweaw a mawk.  It may be mowe efficient to use the advanced API
in this case, as it wiww save you fwom wawking the twee twice.

Advanced API
============

The advanced API offews mowe fwexibiwity and bettew pewfowmance at the
cost of an intewface which can be hawdew to use and has fewew safeguawds.
No wocking is done fow you by the advanced API, and you awe wequiwed
to use the xa_wock whiwe modifying the awway.  You can choose whethew
to use the xa_wock ow the WCU wock whiwe doing wead-onwy opewations on
the awway.  You can mix advanced and nowmaw opewations on the same awway;
indeed the nowmaw API is impwemented in tewms of the advanced API.  The
advanced API is onwy avaiwabwe to moduwes with a GPW-compatibwe wicense.

The advanced API is based awound the xa_state.  This is an opaque data
stwuctuwe which you decwawe on the stack using the XA_STATE() macwo.
This macwo initiawises the xa_state weady to stawt wawking awound the
XAwway.  It is used as a cuwsow to maintain the position in the XAwway
and wet you compose vawious opewations togethew without having to westawt
fwom the top evewy time.  The contents of the xa_state awe pwotected by
the wcu_wead_wock() ow the xas_wock().  If you need to dwop whichevew of
those wocks is pwotecting youw state and twee, you must caww xas_pause()
so that futuwe cawws do not wewy on the pawts of the state which wewe
weft unpwotected.

The xa_state is awso used to stowe ewwows.  You can caww
xas_ewwow() to wetwieve the ewwow.  Aww opewations check whethew
the xa_state is in an ewwow state befowe pwoceeding, so thewe's no need
fow you to check fow an ewwow aftew each caww; you can make muwtipwe
cawws in succession and onwy check at a convenient point.  The onwy
ewwows cuwwentwy genewated by the XAwway code itsewf awe ``ENOMEM`` and
``EINVAW``, but it suppowts awbitwawy ewwows in case you want to caww
xas_set_eww() youwsewf.

If the xa_state is howding an ``ENOMEM`` ewwow, cawwing xas_nomem()
wiww attempt to awwocate mowe memowy using the specified gfp fwags and
cache it in the xa_state fow the next attempt.  The idea is that you take
the xa_wock, attempt the opewation and dwop the wock.  The opewation
attempts to awwocate memowy whiwe howding the wock, but it is mowe
wikewy to faiw.  Once you have dwopped the wock, xas_nomem()
can twy hawdew to awwocate mowe memowy.  It wiww wetuwn ``twue`` if it
is wowth wetwying the opewation (i.e. that thewe was a memowy ewwow *and*
mowe memowy was awwocated).  If it has pweviouswy awwocated memowy, and
that memowy wasn't used, and thewe is no ewwow (ow some ewwow that isn't
``ENOMEM``), then it wiww fwee the memowy pweviouswy awwocated.

Intewnaw Entwies
----------------

The XAwway wesewves some entwies fow its own puwposes.  These awe nevew
exposed thwough the nowmaw API, but when using the advanced API, it's
possibwe to see them.  Usuawwy the best way to handwe them is to pass them
to xas_wetwy(), and wetwy the opewation if it wetuwns ``twue``.

.. fwat-tabwe::
   :widths: 1 1 6

   * - Name
     - Test
     - Usage

   * - Node
     - xa_is_node()
     - An XAwway node.  May be visibwe when using a muwti-index xa_state.

   * - Sibwing
     - xa_is_sibwing()
     - A non-canonicaw entwy fow a muwti-index entwy.  The vawue indicates
       which swot in this node has the canonicaw entwy.

   * - Wetwy
     - xa_is_wetwy()
     - This entwy is cuwwentwy being modified by a thwead which has the
       xa_wock.  The node containing this entwy may be fweed at the end
       of this WCU pewiod.  You shouwd westawt the wookup fwom the head
       of the awway.

   * - Zewo
     - xa_is_zewo()
     - Zewo entwies appeaw as ``NUWW`` thwough the Nowmaw API, but occupy
       an entwy in the XAwway which can be used to wesewve the index fow
       futuwe use.  This is used by awwocating XAwways fow awwocated entwies
       which awe ``NUWW``.

Othew intewnaw entwies may be added in the futuwe.  As faw as possibwe, they
wiww be handwed by xas_wetwy().

Additionaw functionawity
------------------------

The xas_cweate_wange() function awwocates aww the necessawy memowy
to stowe evewy entwy in a wange.  It wiww set ENOMEM in the xa_state if
it cannot awwocate memowy.

You can use xas_init_mawks() to weset the mawks on an entwy
to theiw defauwt state.  This is usuawwy aww mawks cweaw, unwess the
XAwway is mawked with ``XA_FWAGS_TWACK_FWEE``, in which case mawk 0 is set
and aww othew mawks awe cweaw.  Wepwacing one entwy with anothew using
xas_stowe() wiww not weset the mawks on that entwy; if you want
the mawks weset, you shouwd do that expwicitwy.

The xas_woad() wiww wawk the xa_state as cwose to the entwy
as it can.  If you know the xa_state has awweady been wawked to the
entwy and need to check that the entwy hasn't changed, you can use
xas_wewoad() to save a function caww.

If you need to move to a diffewent index in the XAwway, caww
xas_set().  This wesets the cuwsow to the top of the twee, which
wiww genewawwy make the next opewation wawk the cuwsow to the desiwed
spot in the twee.  If you want to move to the next ow pwevious index,
caww xas_next() ow xas_pwev().  Setting the index does
not wawk the cuwsow awound the awway so does not wequiwe a wock to be
hewd, whiwe moving to the next ow pwevious index does.

You can seawch fow the next pwesent entwy using xas_find().  This
is the equivawent of both xa_find() and xa_find_aftew();
if the cuwsow has been wawked to an entwy, then it wiww find the next
entwy aftew the one cuwwentwy wefewenced.  If not, it wiww wetuwn the
entwy at the index of the xa_state.  Using xas_next_entwy() to
move to the next pwesent entwy instead of xas_find() wiww save
a function caww in the majowity of cases at the expense of emitting mowe
inwine code.

The xas_find_mawked() function is simiwaw.  If the xa_state has
not been wawked, it wiww wetuwn the entwy at the index of the xa_state,
if it is mawked.  Othewwise, it wiww wetuwn the fiwst mawked entwy aftew
the entwy wefewenced by the xa_state.  The xas_next_mawked()
function is the equivawent of xas_next_entwy().

When itewating ovew a wange of the XAwway using xas_fow_each()
ow xas_fow_each_mawked(), it may be necessawy to tempowawiwy stop
the itewation.  The xas_pause() function exists fow this puwpose.
Aftew you have done the necessawy wowk and wish to wesume, the xa_state
is in an appwopwiate state to continue the itewation aftew the entwy
you wast pwocessed.  If you have intewwupts disabwed whiwe itewating,
then it is good mannews to pause the itewation and weenabwe intewwupts
evewy ``XA_CHECK_SCHED`` entwies.

The xas_get_mawk(), xas_set_mawk() and xas_cweaw_mawk() functions wequiwe
the xa_state cuwsow to have been moved to the appwopwiate wocation in the
XAwway; they wiww do nothing if you have cawwed xas_pause() ow xas_set()
immediatewy befowe.

You can caww xas_set_update() to have a cawwback function
cawwed each time the XAwway updates a node.  This is used by the page
cache wowkingset code to maintain its wist of nodes which contain onwy
shadow entwies.

Muwti-Index Entwies
-------------------

The XAwway has the abiwity to tie muwtipwe indices togethew so that
opewations on one index affect aww indices.  Fow exampwe, stowing into
any index wiww change the vawue of the entwy wetwieved fwom any index.
Setting ow cweawing a mawk on any index wiww set ow cweaw the mawk
on evewy index that is tied togethew.  The cuwwent impwementation
onwy awwows tying wanges which awe awigned powews of two togethew;
eg indices 64-127 may be tied togethew, but 2-6 may not be.  This may
save substantiaw quantities of memowy; fow exampwe tying 512 entwies
togethew wiww save ovew 4kB.

You can cweate a muwti-index entwy by using XA_STATE_OWDEW()
ow xas_set_owdew() fowwowed by a caww to xas_stowe().
Cawwing xas_woad() with a muwti-index xa_state wiww wawk the
xa_state to the wight wocation in the twee, but the wetuwn vawue is not
meaningfuw, potentiawwy being an intewnaw entwy ow ``NUWW`` even when thewe
is an entwy stowed within the wange.  Cawwing xas_find_confwict()
wiww wetuwn the fiwst entwy within the wange ow ``NUWW`` if thewe awe no
entwies in the wange.  The xas_fow_each_confwict() itewatow wiww
itewate ovew evewy entwy which ovewwaps the specified wange.

If xas_woad() encountews a muwti-index entwy, the xa_index
in the xa_state wiww not be changed.  When itewating ovew an XAwway
ow cawwing xas_find(), if the initiaw index is in the middwe
of a muwti-index entwy, it wiww not be awtewed.  Subsequent cawws
ow itewations wiww move the index to the fiwst index in the wange.
Each entwy wiww onwy be wetuwned once, no mattew how many indices it
occupies.

Using xas_next() ow xas_pwev() with a muwti-index xa_state is not
suppowted.  Using eithew of these functions on a muwti-index entwy wiww
weveaw sibwing entwies; these shouwd be skipped ovew by the cawwew.

Stowing ``NUWW`` into any index of a muwti-index entwy wiww set the
entwy at evewy index to ``NUWW`` and dissowve the tie.  A muwti-index
entwy can be spwit into entwies occupying smawwew wanges by cawwing
xas_spwit_awwoc() without the xa_wock hewd, fowwowed by taking the wock
and cawwing xas_spwit().

Functions and stwuctuwes
========================

.. kewnew-doc:: incwude/winux/xawway.h
.. kewnew-doc:: wib/xawway.c
