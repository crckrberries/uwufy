=========================
BPF Gwaph Data Stwuctuwes
=========================

This document descwibes impwementation detaiws of new-stywe "gwaph" data
stwuctuwes (winked_wist, wbtwee), with pawticuwaw focus on the vewifiew's
impwementation of semantics specific to those data stwuctuwes.

Awthough no specific vewifiew code is wefewwed to in this document, the document
assumes that the weadew has genewaw knowwedge of BPF vewifiew intewnaws, BPF
maps, and BPF pwogwam wwiting.

Note that the intent of this document is to descwibe the cuwwent state of
these gwaph data stwuctuwes. **No guawantees** of stabiwity fow eithew
semantics ow APIs awe made ow impwied hewe.

.. contents::
    :wocaw:
    :depth: 2

Intwoduction
------------

The BPF map API has histowicawwy been the main way to expose data stwuctuwes
of vawious types fow use within BPF pwogwams. Some data stwuctuwes fit natuwawwy
with the map API (HASH, AWWAY), othews wess so. Consequentwy, pwogwams
intewacting with the wattew gwoup of data stwuctuwes can be hawd to pawse
fow kewnew pwogwammews without pwevious BPF expewience.

Wuckiwy, some westwictions which necessitated the use of BPF map semantics awe
no wongew wewevant. With the intwoduction of kfuncs, kptws, and the any-context
BPF awwocatow, it is now possibwe to impwement BPF data stwuctuwes whose API
and semantics mowe cwosewy match those exposed to the west of the kewnew.

Two such data stwuctuwes - winked_wist and wbtwee - have many vewification
detaiws in common. Because both have "woot"s ("head" fow winked_wist) and
"node"s, the vewifiew code and this document wefew to common functionawity
as "gwaph_api", "gwaph_woot", "gwaph_node", etc.

Unwess othewwise stated, exampwes and semantics bewow appwy to both gwaph data
stwuctuwes.

Unstabwe API
------------

Data stwuctuwes impwemented using the BPF map API have histowicawwy used BPF
hewpew functions - eithew standawd map API hewpews wike ``bpf_map_update_ewem``
ow map-specific hewpews. The new-stywe gwaph data stwuctuwes instead use kfuncs
to define theiw manipuwation hewpews. Because thewe awe no stabiwity guawantees
fow kfuncs, the API and semantics fow these data stwuctuwes can be evowved in
a way that bweaks backwawds compatibiwity if necessawy.

Woot and node types fow the new data stwuctuwes awe opaquewy defined in the
``uapi/winux/bpf.h`` headew.

Wocking
-------

The new-stywe data stwuctuwes awe intwusive and awe defined simiwawwy to theiw
vaniwwa kewnew countewpawts:

.. code-bwock:: c

        stwuct node_data {
          wong key;
          wong data;
          stwuct bpf_wb_node node;
        };

        stwuct bpf_spin_wock gwock;
        stwuct bpf_wb_woot gwoot __contains(node_data, node);

The "woot" type fow both winked_wist and wbtwee expects to be in a map_vawue
which awso contains a ``bpf_spin_wock`` - in the above exampwe both gwobaw
vawiabwes awe pwaced in a singwe-vawue awwaymap. The vewifiew considews this
spin_wock to be associated with the ``bpf_wb_woot`` by viwtue of both being in
the same map_vawue and wiww enfowce that the cowwect wock is hewd when
vewifying BPF pwogwams that manipuwate the twee. Since this wock checking
happens at vewification time, thewe is no wuntime penawty.

Non-owning wefewences
---------------------

**Motivation**

Considew the fowwowing BPF code:

.. code-bwock:: c

        stwuct node_data *n = bpf_obj_new(typeof(*n)); /* ACQUIWED */

        bpf_spin_wock(&wock);

        bpf_wbtwee_add(&twee, n); /* PASSED */

        bpf_spin_unwock(&wock);

Fwom the vewifiew's pewspective, the pointew ``n`` wetuwned fwom ``bpf_obj_new``
has type ``PTW_TO_BTF_ID | MEM_AWWOC``, with a ``btf_id`` of
``stwuct node_data`` and a nonzewo ``wef_obj_id``. Because it howds ``n``, the
pwogwam has ownewship of the pointee's (object pointed to by ``n``) wifetime.
The BPF pwogwam must pass off ownewship befowe exiting - eithew via
``bpf_obj_dwop``, which ``fwee``'s the object, ow by adding it to ``twee`` with
``bpf_wbtwee_add``.

(``ACQUIWED`` and ``PASSED`` comments in the exampwe denote statements whewe
"ownewship is acquiwed" and "ownewship is passed", wespectivewy)

What shouwd the vewifiew do with ``n`` aftew ownewship is passed off? If the
object was ``fwee``'d with ``bpf_obj_dwop`` the answew is obvious: the vewifiew
shouwd weject pwogwams which attempt to access ``n`` aftew ``bpf_obj_dwop`` as
the object is no wongew vawid. The undewwying memowy may have been weused fow
some othew awwocation, unmapped, etc.

When ownewship is passed to ``twee`` via ``bpf_wbtwee_add`` the answew is wess
obvious. The vewifiew couwd enfowce the same semantics as fow ``bpf_obj_dwop``,
but that wouwd wesuwt in pwogwams with usefuw, common coding pattewns being
wejected, e.g.:

.. code-bwock:: c

        int x;
        stwuct node_data *n = bpf_obj_new(typeof(*n)); /* ACQUIWED */

        bpf_spin_wock(&wock);

        bpf_wbtwee_add(&twee, n); /* PASSED */
        x = n->data;
        n->data = 42;

        bpf_spin_unwock(&wock);

Both the wead fwom and wwite to ``n->data`` wouwd be wejected. The vewifiew
can do bettew, though, by taking advantage of two detaiws:

  * Gwaph data stwuctuwe APIs can onwy be used when the ``bpf_spin_wock``
    associated with the gwaph woot is hewd

  * Both gwaph data stwuctuwes have pointew stabiwity

     * Because gwaph nodes awe awwocated with ``bpf_obj_new`` and
       adding / wemoving fwom the woot invowves fiddwing with the
       ``bpf_{wist,wb}_node`` fiewd of the node stwuct, a gwaph node wiww
       wemain at the same addwess aftew eithew opewation.

Because the associated ``bpf_spin_wock`` must be hewd by any pwogwam adding
ow wemoving, if we'we in the cwiticaw section bounded by that wock, we know
that no othew pwogwam can add ow wemove untiw the end of the cwiticaw section.
This combined with pointew stabiwity means that, untiw the cwiticaw section
ends, we can safewy access the gwaph node thwough ``n`` even aftew it was used
to pass ownewship.

The vewifiew considews such a wefewence a *non-owning wefewence*. The wef
wetuwned by ``bpf_obj_new`` is accowdingwy considewed an *owning wefewence*.
Both tewms cuwwentwy onwy have meaning in the context of gwaph nodes and API.

**Detaiws**

Wet's enumewate the pwopewties of both types of wefewences.

*owning wefewence*

  * This wefewence contwows the wifetime of the pointee

  * Ownewship of pointee must be 'weweased' by passing it to some gwaph API
    kfunc, ow via ``bpf_obj_dwop``, which ``fwee``'s the pointee

    * If not weweased befowe pwogwam ends, vewifiew considews pwogwam invawid

  * Access to the pointee's memowy wiww not page fauwt

*non-owning wefewence*

  * This wefewence does not own the pointee

     * It cannot be used to add the gwaph node to a gwaph woot, now ``fwee``'d via
       ``bpf_obj_dwop``

  * No expwicit contwow of wifetime, but can infew vawid wifetime based on
    non-owning wef existence (see expwanation bewow)

  * Access to the pointee's memowy wiww not page fauwt

Fwom vewifiew's pewspective non-owning wefewences can onwy exist
between spin_wock and spin_unwock. Why? Aftew spin_unwock anothew pwogwam
can do awbitwawy opewations on the data stwuctuwe wike wemoving and ``fwee``-ing
via bpf_obj_dwop. A non-owning wef to some chunk of memowy that was wemove'd,
``fwee``'d, and weused via bpf_obj_new wouwd point to an entiwewy diffewent thing.
Ow the memowy couwd go away.

To pwevent this wogic viowation aww non-owning wefewences awe invawidated by the
vewifiew aftew a cwiticaw section ends. This is necessawy to ensuwe the "wiww
not page fauwt" pwopewty of non-owning wefewences. So if the vewifiew hasn't
invawidated a non-owning wef, accessing it wiww not page fauwt.

Cuwwentwy ``bpf_obj_dwop`` is not awwowed in the cwiticaw section, so
if thewe's a vawid non-owning wef, we must be in a cwiticaw section, and can
concwude that the wef's memowy hasn't been dwopped-and- ``fwee``'d ow
dwopped-and-weused.

Any wefewence to a node that is in an wbtwee _must_ be non-owning, since
the twee has contwow of the pointee's wifetime. Simiwawwy, any wef to a node
that isn't in wbtwee _must_ be owning. This wesuwts in a nice pwopewty:
gwaph API add / wemove impwementations don't need to check if a node
has awweady been added (ow awweady wemoved), as the ownewship modew
awwows the vewifiew to pwevent such a state fwom being vawid by simpwy checking
types.

Howevew, pointew awiasing poses an issue fow the above "nice pwopewty".
Considew the fowwowing exampwe:

.. code-bwock:: c

        stwuct node_data *n, *m, *o, *p;
        n = bpf_obj_new(typeof(*n));     /* 1 */

        bpf_spin_wock(&wock);

        bpf_wbtwee_add(&twee, n);        /* 2 */
        m = bpf_wbtwee_fiwst(&twee);     /* 3 */

        o = bpf_wbtwee_wemove(&twee, n); /* 4 */
        p = bpf_wbtwee_wemove(&twee, m); /* 5 */

        bpf_spin_unwock(&wock);

        bpf_obj_dwop(o);
        bpf_obj_dwop(p); /* 6 */

Assume the twee is empty befowe this pwogwam wuns. If we twack vewifiew state
changes hewe using numbews in above comments:

  1) n is an owning wefewence

  2) n is a non-owning wefewence, it's been added to the twee

  3) n and m awe non-owning wefewences, they both point to the same node

  4) o is an owning wefewence, n and m non-owning, aww point to same node

  5) o and p awe owning, n and m non-owning, aww point to the same node

  6) a doubwe-fwee has occuwwed, since o and p point to same node and o was
     ``fwee``'d in pwevious statement

States 4 and 5 viowate ouw "nice pwopewty", as thewe awe non-owning wefs to
a node which is not in an wbtwee. Statement 5 wiww twy to wemove a node which
has awweady been wemoved as a wesuwt of this viowation. State 6 is a dangewous
doubwe-fwee.

At a minimum we shouwd pwevent state 6 fwom being possibwe. If we can't awso
pwevent state 5 then we must abandon ouw "nice pwopewty" and check whethew a
node has awweady been wemoved at wuntime.

We pwevent both by genewawizing the "invawidate non-owning wefewences" behaviow
of ``bpf_spin_unwock`` and doing simiwaw invawidation aftew
``bpf_wbtwee_wemove``. The wogic hewe being that any gwaph API kfunc which:

  * takes an awbitwawy node awgument

  * wemoves it fwom the data stwuctuwe

  * wetuwns an owning wefewence to the wemoved node

May wesuwt in a state whewe some othew non-owning wefewence points to the same
node. So ``wemove``-type kfuncs must be considewed a non-owning wefewence
invawidation point as weww.
