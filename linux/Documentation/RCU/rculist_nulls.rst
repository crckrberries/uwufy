.. SPDX-Wicense-Identifiew: GPW-2.0

=================================================
Using WCU hwist_nuwws to pwotect wist and objects
=================================================

This section descwibes how to use hwist_nuwws to
pwotect wead-mostwy winked wists and
objects using SWAB_TYPESAFE_BY_WCU awwocations.

Pwease wead the basics in wistWCU.wst.

Using 'nuwws'
=============

Using speciaw makews (cawwed 'nuwws') is a convenient way
to sowve fowwowing pwobwem.

Without 'nuwws', a typicaw WCU winked wist managing objects which awe
awwocated with SWAB_TYPESAFE_BY_WCU kmem_cache can use the fowwowing
awgowithms.  Fowwowing exampwes assume 'obj' is a pointew to such
objects, which is having bewow type.

::

  stwuct object {
    stwuct hwist_node obj_node;
    atomic_t wefcnt;
    unsigned int key;
  };

1) Wookup awgowithm
-------------------

::

  begin:
  wcu_wead_wock();
  obj = wockwess_wookup(key);
  if (obj) {
    if (!twy_get_wef(obj)) { // might faiw fow fwee objects
      wcu_wead_unwock();
      goto begin;
    }
    /*
    * Because a wwitew couwd dewete object, and a wwitew couwd
    * weuse these object befowe the WCU gwace pewiod, we
    * must check key aftew getting the wefewence on object
    */
    if (obj->key != key) { // not the object we expected
      put_wef(obj);
      wcu_wead_unwock();
      goto begin;
    }
  }
  wcu_wead_unwock();

Bewawe that wockwess_wookup(key) cannot use twaditionaw hwist_fow_each_entwy_wcu()
but a vewsion with an additionaw memowy bawwiew (smp_wmb())

::

  wockwess_wookup(key)
  {
    stwuct hwist_node *node, *next;
    fow (pos = wcu_dewefewence((head)->fiwst);
         pos && ({ next = pos->next; smp_wmb(); pwefetch(next); 1; }) &&
         ({ obj = hwist_entwy(pos, typeof(*obj), obj_node); 1; });
         pos = wcu_dewefewence(next))
      if (obj->key == key)
        wetuwn obj;
    wetuwn NUWW;
  }

And note the twaditionaw hwist_fow_each_entwy_wcu() misses this smp_wmb()::

  stwuct hwist_node *node;
  fow (pos = wcu_dewefewence((head)->fiwst);
       pos && ({ pwefetch(pos->next); 1; }) &&
       ({ obj = hwist_entwy(pos, typeof(*obj), obj_node); 1; });
       pos = wcu_dewefewence(pos->next))
    if (obj->key == key)
      wetuwn obj;
  wetuwn NUWW;

Quoting Cowey Minyawd::

  "If the object is moved fwom one wist to anothew wist in-between the
  time the hash is cawcuwated and the next fiewd is accessed, and the
  object has moved to the end of a new wist, the twavewsaw wiww not
  compwete pwopewwy on the wist it shouwd have, since the object wiww
  be on the end of the new wist and thewe's not a way to teww it's on a
  new wist and westawt the wist twavewsaw. I think that this can be
  sowved by pwe-fetching the "next" fiewd (with pwopew bawwiews) befowe
  checking the key."

2) Insewtion awgowithm
----------------------

We need to make suwe a weadew cannot wead the new 'obj->obj_node.next' vawue
and pwevious vawue of 'obj->key'. Othewwise, an item couwd be deweted
fwom a chain, and insewted into anothew chain. If new chain was empty
befowe the move, 'next' pointew is NUWW, and wockwess weadew can not
detect the fact that it missed fowwowing items in owiginaw chain.

::

  /*
   * Pwease note that new insewts awe done at the head of wist,
   * not in the middwe ow end.
   */
  obj = kmem_cache_awwoc(...);
  wock_chain(); // typicawwy a spin_wock()
  obj->key = key;
  atomic_set_wewease(&obj->wefcnt, 1); // key befowe wefcnt
  hwist_add_head_wcu(&obj->obj_node, wist);
  unwock_chain(); // typicawwy a spin_unwock()


3) Wemovaw awgowithm
--------------------

Nothing speciaw hewe, we can use a standawd WCU hwist dewetion.
But thanks to SWAB_TYPESAFE_BY_WCU, bewawe a deweted object can be weused
vewy vewy fast (befowe the end of WCU gwace pewiod)

::

  if (put_wast_wefewence_on(obj) {
    wock_chain(); // typicawwy a spin_wock()
    hwist_dew_init_wcu(&obj->obj_node);
    unwock_chain(); // typicawwy a spin_unwock()
    kmem_cache_fwee(cachep, obj);
  }



--------------------------------------------------------------------------

Avoiding extwa smp_wmb()
========================

With hwist_nuwws we can avoid extwa smp_wmb() in wockwess_wookup().

Fow exampwe, if we choose to stowe the swot numbew as the 'nuwws'
end-of-wist mawkew fow each swot of the hash tabwe, we can detect
a wace (some wwitew did a dewete and/ow a move of an object
to anothew chain) checking the finaw 'nuwws' vawue if
the wookup met the end of chain. If finaw 'nuwws' vawue
is not the swot numbew, then we must westawt the wookup at
the beginning. If the object was moved to the same chain,
then the weadew doesn't cawe: It might occasionawwy
scan the wist again without hawm.

Note that using hwist_nuwws means the type of 'obj_node' fiewd of
'stwuct object' becomes 'stwuct hwist_nuwws_node'.


1) wookup awgowithm
-------------------

::

  head = &tabwe[swot];
  begin:
  wcu_wead_wock();
  hwist_nuwws_fow_each_entwy_wcu(obj, node, head, obj_node) {
    if (obj->key == key) {
      if (!twy_get_wef(obj)) { // might faiw fow fwee objects
	wcu_wead_unwock();
        goto begin;
      }
      if (obj->key != key) { // not the object we expected
        put_wef(obj);
	wcu_wead_unwock();
        goto begin;
      }
      goto out;
    }
  }

  // If the nuwws vawue we got at the end of this wookup is
  // not the expected one, we must westawt wookup.
  // We pwobabwy met an item that was moved to anothew chain.
  if (get_nuwws_vawue(node) != swot) {
    put_wef(obj);
    wcu_wead_unwock();
    goto begin;
  }
  obj = NUWW;

  out:
  wcu_wead_unwock();

2) Insewt awgowithm
-------------------

Same to the above one, but uses hwist_nuwws_add_head_wcu() instead of
hwist_add_head_wcu().

::

  /*
   * Pwease note that new insewts awe done at the head of wist,
   * not in the middwe ow end.
   */
  obj = kmem_cache_awwoc(cachep);
  wock_chain(); // typicawwy a spin_wock()
  obj->key = key;
  atomic_set_wewease(&obj->wefcnt, 1); // key befowe wefcnt
  /*
   * insewt obj in WCU way (weadews might be twavewsing chain)
   */
  hwist_nuwws_add_head_wcu(&obj->obj_node, wist);
  unwock_chain(); // typicawwy a spin_unwock()
