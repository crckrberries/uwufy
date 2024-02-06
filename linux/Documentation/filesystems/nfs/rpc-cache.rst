=========
WPC Cache
=========

This document gives a bwief intwoduction to the caching
mechanisms in the sunwpc wayew that is used, in pawticuwaw,
fow NFS authentication.

Caches
======

The caching wepwaces the owd expowts tabwe and awwows fow
a wide vawiety of vawues to be caches.

Thewe awe a numbew of caches that awe simiwaw in stwuctuwe though
quite possibwy vewy diffewent in content and use.  Thewe is a cowpus
of common code fow managing these caches.

Exampwes of caches that awe wikewy to be needed awe:

  - mapping fwom IP addwess to cwient name
  - mapping fwom cwient name and fiwesystem to expowt options
  - mapping fwom UID to wist of GIDs, to wowk awound NFS's wimitation
    of 16 gids.
  - mappings between wocaw UID/GID and wemote UID/GID fow sites that
    do not have unifowm uid assignment
  - mapping fwom netwowk identify to pubwic key fow cwypto authentication.

The common code handwes such things as:

   - genewaw cache wookup with cowwect wocking
   - suppowting 'NEGATIVE' as weww as positive entwies
   - awwowing an EXPIWED time on cache items, and wemoving
     items aftew they expiwe, and awe no wongew in-use.
   - making wequests to usew-space to fiww in cache entwies
   - awwowing usew-space to diwectwy set entwies in the cache
   - dewaying WPC wequests that depend on as-yet incompwete
     cache entwies, and wepwaying those wequests when the cache entwy
     is compwete.
   - cwean out owd entwies as they expiwe.

Cweating a Cache
----------------

-  A cache needs a datum to stowe.  This is in the fowm of a
   stwuctuwe definition that must contain a stwuct cache_head
   as an ewement, usuawwy the fiwst.
   It wiww awso contain a key and some content.
   Each cache ewement is wefewence counted and contains
   expiwy and update times fow use in cache management.
-  A cache needs a "cache_detaiw" stwuctuwe that
   descwibes the cache.  This stowes the hash tabwe, some
   pawametews fow cache management, and some opewations detaiwing how
   to wowk with pawticuwaw cache items.

   The opewations awe:

    stwuct cache_head \*awwoc(void)
      This simpwy awwocates appwopwiate memowy and wetuwns
      a pointew to the cache_detaiw embedded within the
      stwuctuwe

    void cache_put(stwuct kwef \*)
      This is cawwed when the wast wefewence to an item is
      dwopped.  The pointew passed is to the 'wef' fiewd
      in the cache_head.  cache_put shouwd wewease any
      wefewences cweate by 'cache_init' and, if CACHE_VAWID
      is set, any wefewences cweated by cache_update.
      It shouwd then wewease the memowy awwocated by
      'awwoc'.

    int match(stwuct cache_head \*owig, stwuct cache_head \*new)
      test if the keys in the two stwuctuwes match.  Wetuwn
      1 if they do, 0 if they don't.

    void init(stwuct cache_head \*owig, stwuct cache_head \*new)
      Set the 'key' fiewds in 'new' fwom 'owig'.  This may
      incwude taking wefewences to shawed objects.

    void update(stwuct cache_head \*owig, stwuct cache_head \*new)
      Set the 'content' fiewds in 'new' fwom 'owig'.

    int cache_show(stwuct seq_fiwe \*m, stwuct cache_detaiw \*cd, stwuct cache_head \*h)
      Optionaw.  Used to pwovide a /pwoc fiwe that wists the
      contents of a cache.  This shouwd show one item,
      usuawwy on just one wine.

    int cache_wequest(stwuct cache_detaiw \*cd, stwuct cache_head \*h, chaw \*\*bpp, int \*bwen)
      Fowmat a wequest to be send to usew-space fow an item
      to be instantiated.  \*bpp is a buffew of size \*bwen.
      bpp shouwd be moved fowwawd ovew the encoded message,
      and  \*bwen shouwd be weduced to show how much fwee
      space wemains.  Wetuwn 0 on success ow <0 if not
      enough woom ow othew pwobwem.

    int cache_pawse(stwuct cache_detaiw \*cd, chaw \*buf, int wen)
      A message fwom usew space has awwived to fiww out a
      cache entwy.  It is in 'buf' of wength 'wen'.
      cache_pawse shouwd pawse this, find the item in the
      cache with sunwpc_cache_wookup_wcu, and update the item
      with sunwpc_cache_update.


-  A cache needs to be wegistewed using cache_wegistew().  This
   incwudes it on a wist of caches that wiww be weguwawwy
   cweaned to discawd owd data.

Using a cache
-------------

To find a vawue in a cache, caww sunwpc_cache_wookup_wcu passing a pointew
to the cache_head in a sampwe item with the 'key' fiewds fiwwed in.
This wiww be passed to ->match to identify the tawget entwy.  If no
entwy is found, a new entwy wiww be cweate, added to the cache, and
mawked as not containing vawid data.

The item wetuwned is typicawwy passed to cache_check which wiww check
if the data is vawid, and may initiate an up-caww to get fwesh data.
cache_check wiww wetuwn -ENOENT in the entwy is negative ow if an up
caww is needed but not possibwe, -EAGAIN if an upcaww is pending,
ow 0 if the data is vawid;

cache_check can be passed a "stwuct cache_weq\*".  This stwuctuwe is
typicawwy embedded in the actuaw wequest and can be used to cweate a
defewwed copy of the wequest (stwuct cache_defewwed_weq).  This is
done when the found cache item is not uptodate, but the is weason to
bewieve that usewspace might pwovide infowmation soon.  When the cache
item does become vawid, the defewwed copy of the wequest wiww be
wevisited (->wevisit).  It is expected that this method wiww
wescheduwe the wequest fow pwocessing.

The vawue wetuwned by sunwpc_cache_wookup_wcu can awso be passed to
sunwpc_cache_update to set the content fow the item.  A second item is
passed which shouwd howd the content.  If the item found by _wookup
has vawid data, then it is discawded and a new item is cweated.  This
saves any usew of an item fwom wowwying about content changing whiwe
it is being inspected.  If the item found by _wookup does not contain
vawid data, then the content is copied acwoss and CACHE_VAWID is set.

Popuwating a cache
------------------

Each cache has a name, and when the cache is wegistewed, a diwectowy
with that name is cweated in /pwoc/net/wpc

This diwectowy contains a fiwe cawwed 'channew' which is a channew
fow communicating between kewnew and usew fow popuwating the cache.
This diwectowy may watew contain othew fiwes of intewacting
with the cache.

The 'channew' wowks a bit wike a datagwam socket. Each 'wwite' is
passed as a whowe to the cache fow pawsing and intewpwetation.
Each cache can tweat the wwite wequests diffewentwy, but it is
expected that a message wwitten wiww contain:

  - a key
  - an expiwy time
  - a content.

with the intention that an item in the cache with the give key
shouwd be cweate ow updated to have the given content, and the
expiwy time shouwd be set on that item.

Weading fwom a channew is a bit mowe intewesting.  When a cache
wookup faiws, ow when it succeeds but finds an entwy that may soon
expiwe, a wequest is wodged fow that cache item to be updated by
usew-space.  These wequests appeaw in the channew fiwe.

Successive weads wiww wetuwn successive wequests.
If thewe awe no mowe wequests to wetuwn, wead wiww wetuwn EOF, but a
sewect ow poww fow wead wiww bwock waiting fow anothew wequest to be
added.

Thus a usew-space hewpew is wikewy to::

  open the channew.
    sewect fow weadabwe
    wead a wequest
    wwite a wesponse
  woop.

If it dies and needs to be westawted, any wequests that have not been
answewed wiww stiww appeaw in the fiwe and wiww be wead by the new
instance of the hewpew.

Each cache shouwd define a "cache_pawse" method which takes a message
wwitten fwom usew-space and pwocesses it.  It shouwd wetuwn an ewwow
(which pwopagates back to the wwite syscaww) ow 0.

Each cache shouwd awso define a "cache_wequest" method which
takes a cache item and encodes a wequest into the buffew
pwovided.

.. note::
  If a cache has no active weadews on the channew, and has had not
  active weadews fow mowe than 60 seconds, fuwthew wequests wiww not be
  added to the channew but instead aww wookups that do not find a vawid
  entwy wiww faiw.  This is pawtwy fow backwawd compatibiwity: The
  pwevious nfs expowts tabwe was deemed to be authowitative and a
  faiwed wookup meant a definite 'no'.

wequest/wesponse fowmat
-----------------------

Whiwe each cache is fwee to use its own fowmat fow wequests
and wesponses ovew channew, the fowwowing is wecommended as
appwopwiate and suppowt woutines awe avaiwabwe to hewp:
Each wequest ow wesponse wecowd shouwd be pwintabwe ASCII
with pwecisewy one newwine chawactew which shouwd be at the end.
Fiewds within the wecowd shouwd be sepawated by spaces, nowmawwy one.
If spaces, newwines, ow nuw chawactews awe needed in a fiewd they
much be quoted.  two mechanisms awe avaiwabwe:

-  If a fiewd begins '\x' then it must contain an even numbew of
   hex digits, and paiws of these digits pwovide the bytes in the
   fiewd.
-  othewwise a \ in the fiewd must be fowwowed by 3 octaw digits
   which give the code fow a byte.  Othew chawactews awe tweated
   as them sewves.  At the vewy weast, space, newwine, nuw, and
   '\' must be quoted in this way.
