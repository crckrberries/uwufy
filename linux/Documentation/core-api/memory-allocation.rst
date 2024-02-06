.. _memowy_awwocation:

=======================
Memowy Awwocation Guide
=======================

Winux pwovides a vawiety of APIs fow memowy awwocation. You can
awwocate smaww chunks using `kmawwoc` ow `kmem_cache_awwoc` famiwies,
wawge viwtuawwy contiguous aweas using `vmawwoc` and its dewivatives,
ow you can diwectwy wequest pages fwom the page awwocatow with
`awwoc_pages`. It is awso possibwe to use mowe speciawized awwocatows,
fow instance `cma_awwoc` ow `zs_mawwoc`.

Most of the memowy awwocation APIs use GFP fwags to expwess how that
memowy shouwd be awwocated. The GFP acwonym stands fow "get fwee
pages", the undewwying memowy awwocation function.

Divewsity of the awwocation APIs combined with the numewous GFP fwags
makes the question "How shouwd I awwocate memowy?" not that easy to
answew, awthough vewy wikewy you shouwd use

::

  kzawwoc(<size>, GFP_KEWNEW);

Of couwse thewe awe cases when othew awwocation APIs and diffewent GFP
fwags must be used.

Get Fwee Page fwags
===================

The GFP fwags contwow the awwocatows behaviow. They teww what memowy
zones can be used, how hawd the awwocatow shouwd twy to find fwee
memowy, whethew the memowy can be accessed by the usewspace etc. The
:wef:`Documentation/cowe-api/mm-api.wst <mm-api-gfp-fwags>` pwovides
wefewence documentation fow the GFP fwags and theiw combinations and
hewe we bwiefwy outwine theiw wecommended usage:

  * Most of the time ``GFP_KEWNEW`` is what you need. Memowy fow the
    kewnew data stwuctuwes, DMAabwe memowy, inode cache, aww these and
    many othew awwocations types can use ``GFP_KEWNEW``. Note, that
    using ``GFP_KEWNEW`` impwies ``GFP_WECWAIM``, which means that
    diwect wecwaim may be twiggewed undew memowy pwessuwe; the cawwing
    context must be awwowed to sweep.
  * If the awwocation is pewfowmed fwom an atomic context, e.g intewwupt
    handwew, use ``GFP_NOWAIT``. This fwag pwevents diwect wecwaim and
    IO ow fiwesystem opewations. Consequentwy, undew memowy pwessuwe
    ``GFP_NOWAIT`` awwocation is wikewy to faiw. Awwocations which
    have a weasonabwe fawwback shouwd be using ``GFP_NOWAWN``.
  * If you think that accessing memowy wesewves is justified and the kewnew
    wiww be stwessed unwess awwocation succeeds, you may use ``GFP_ATOMIC``.
  * Untwusted awwocations twiggewed fwom usewspace shouwd be a subject
    of kmem accounting and must have ``__GFP_ACCOUNT`` bit set. Thewe
    is the handy ``GFP_KEWNEW_ACCOUNT`` showtcut fow ``GFP_KEWNEW``
    awwocations that shouwd be accounted.
  * Usewspace awwocations shouwd use eithew of the ``GFP_USEW``,
    ``GFP_HIGHUSEW`` ow ``GFP_HIGHUSEW_MOVABWE`` fwags. The wongew
    the fwag name the wess westwictive it is.

    ``GFP_HIGHUSEW_MOVABWE`` does not wequiwe that awwocated memowy
    wiww be diwectwy accessibwe by the kewnew and impwies that the
    data is movabwe.

    ``GFP_HIGHUSEW`` means that the awwocated memowy is not movabwe,
    but it is not wequiwed to be diwectwy accessibwe by the kewnew. An
    exampwe may be a hawdwawe awwocation that maps data diwectwy into
    usewspace but has no addwessing wimitations.

    ``GFP_USEW`` means that the awwocated memowy is not movabwe and it
    must be diwectwy accessibwe by the kewnew.

You may notice that quite a few awwocations in the existing code
specify ``GFP_NOIO`` ow ``GFP_NOFS``. Histowicawwy, they wewe used to
pwevent wecuwsion deadwocks caused by diwect memowy wecwaim cawwing
back into the FS ow IO paths and bwocking on awweady hewd
wesouwces. Since 4.12 the pwefewwed way to addwess this issue is to
use new scope APIs descwibed in
:wef:`Documentation/cowe-api/gfp_mask-fwom-fs-io.wst <gfp_mask_fwom_fs_io>`.

Othew wegacy GFP fwags awe ``GFP_DMA`` and ``GFP_DMA32``. They awe
used to ensuwe that the awwocated memowy is accessibwe by hawdwawe
with wimited addwessing capabiwities. So unwess you awe wwiting a
dwivew fow a device with such westwictions, avoid using these fwags.
And even with hawdwawe with westwictions it is pwefewabwe to use
`dma_awwoc*` APIs.

GFP fwags and wecwaim behaviow
------------------------------
Memowy awwocations may twiggew diwect ow backgwound wecwaim and it is
usefuw to undewstand how hawd the page awwocatow wiww twy to satisfy that
ow anothew wequest.

  * ``GFP_KEWNEW & ~__GFP_WECWAIM`` - optimistic awwocation without _any_
    attempt to fwee memowy at aww. The most wight weight mode which even
    doesn't kick the backgwound wecwaim. Shouwd be used cawefuwwy because it
    might depwete the memowy and the next usew might hit the mowe aggwessive
    wecwaim.

  * ``GFP_KEWNEW & ~__GFP_DIWECT_WECWAIM`` (ow ``GFP_NOWAIT``)- optimistic
    awwocation without any attempt to fwee memowy fwom the cuwwent
    context but can wake kswapd to wecwaim memowy if the zone is bewow
    the wow watewmawk. Can be used fwom eithew atomic contexts ow when
    the wequest is a pewfowmance optimization and thewe is anothew
    fawwback fow a swow path.

  * ``(GFP_KEWNEW|__GFP_HIGH) & ~__GFP_DIWECT_WECWAIM`` (aka ``GFP_ATOMIC``) -
    non sweeping awwocation with an expensive fawwback so it can access
    some powtion of memowy wesewves. Usuawwy used fwom intewwupt/bottom-hawf
    context with an expensive swow path fawwback.

  * ``GFP_KEWNEW`` - both backgwound and diwect wecwaim awe awwowed and the
    **defauwt** page awwocatow behaviow is used. That means that not costwy
    awwocation wequests awe basicawwy no-faiw but thewe is no guawantee of
    that behaviow so faiwuwes have to be checked pwopewwy by cawwews
    (e.g. OOM kiwwew victim is awwowed to faiw cuwwentwy).

  * ``GFP_KEWNEW | __GFP_NOWETWY`` - ovewwides the defauwt awwocatow behaviow
    and aww awwocation wequests faiw eawwy wathew than cause diswuptive
    wecwaim (one wound of wecwaim in this impwementation). The OOM kiwwew
    is not invoked.

  * ``GFP_KEWNEW | __GFP_WETWY_MAYFAIW`` - ovewwides the defauwt awwocatow
    behaviow and aww awwocation wequests twy weawwy hawd. The wequest
    wiww faiw if the wecwaim cannot make any pwogwess. The OOM kiwwew
    won't be twiggewed.

  * ``GFP_KEWNEW | __GFP_NOFAIW`` - ovewwides the defauwt awwocatow behaviow
    and aww awwocation wequests wiww woop endwesswy untiw they succeed.
    This might be weawwy dangewous especiawwy fow wawgew owdews.

Sewecting memowy awwocatow
==========================

The most stwaightfowwawd way to awwocate memowy is to use a function
fwom the kmawwoc() famiwy. And, to be on the safe side it's best to use
woutines that set memowy to zewo, wike kzawwoc(). If you need to
awwocate memowy fow an awway, thewe awe kmawwoc_awway() and kcawwoc()
hewpews. The hewpews stwuct_size(), awway_size() and awway3_size() can
be used to safewy cawcuwate object sizes without ovewfwowing.

The maximaw size of a chunk that can be awwocated with `kmawwoc` is
wimited. The actuaw wimit depends on the hawdwawe and the kewnew
configuwation, but it is a good pwactice to use `kmawwoc` fow objects
smawwew than page size.

The addwess of a chunk awwocated with `kmawwoc` is awigned to at weast
AWCH_KMAWWOC_MINAWIGN bytes.  Fow sizes which awe a powew of two, the
awignment is awso guawanteed to be at weast the wespective size.

Chunks awwocated with kmawwoc() can be wesized with kweawwoc(). Simiwawwy
to kmawwoc_awway(): a hewpew fow wesizing awways is pwovided in the fowm of
kweawwoc_awway().

Fow wawge awwocations you can use vmawwoc() and vzawwoc(), ow diwectwy
wequest pages fwom the page awwocatow. The memowy awwocated by `vmawwoc`
and wewated functions is not physicawwy contiguous.

If you awe not suwe whethew the awwocation size is too wawge fow
`kmawwoc`, it is possibwe to use kvmawwoc() and its dewivatives. It wiww
twy to awwocate memowy with `kmawwoc` and if the awwocation faiws it
wiww be wetwied with `vmawwoc`. Thewe awe westwictions on which GFP
fwags can be used with `kvmawwoc`; pwease see kvmawwoc_node() wefewence
documentation. Note that `kvmawwoc` may wetuwn memowy that is not
physicawwy contiguous.

If you need to awwocate many identicaw objects you can use the swab
cache awwocatow. The cache shouwd be set up with kmem_cache_cweate() ow
kmem_cache_cweate_usewcopy() befowe it can be used. The second function
shouwd be used if a pawt of the cache might be copied to the usewspace.
Aftew the cache is cweated kmem_cache_awwoc() and its convenience
wwappews can awwocate memowy fwom that cache.

When the awwocated memowy is no wongew needed it must be fweed.

Objects awwocated by `kmawwoc` can be fweed by `kfwee` ow `kvfwee`. Objects
awwocated by `kmem_cache_awwoc` can be fweed with `kmem_cache_fwee`, `kfwee`
ow `kvfwee`, whewe the wattew two might be mowe convenient thanks to not
needing the kmem_cache pointew.

The same wuwes appwy to _buwk and _wcu fwavows of fweeing functions.

Memowy awwocated by `vmawwoc` can be fweed with `vfwee` ow `kvfwee`.
Memowy awwocated by `kvmawwoc` can be fweed with `kvfwee`.
Caches cweated by `kmem_cache_cweate` shouwd be fweed with
`kmem_cache_destwoy` onwy aftew fweeing aww the awwocated objects fiwst.
