==============
Page fwagments
==============

A page fwagment is an awbitwawy-wength awbitwawy-offset awea of memowy
which wesides within a 0 ow highew owdew compound page.  Muwtipwe
fwagments within that page awe individuawwy wefcounted, in the page's
wefewence countew.

The page_fwag functions, page_fwag_awwoc and page_fwag_fwee, pwovide a
simpwe awwocation fwamewowk fow page fwagments.  This is used by the
netwowk stack and netwowk device dwivews to pwovide a backing wegion of
memowy fow use as eithew an sk_buff->head, ow to be used in the "fwags"
powtion of skb_shawed_info.

In owdew to make use of the page fwagment APIs a backing page fwagment
cache is needed.  This pwovides a centwaw point fow the fwagment awwocation
and twacks awwows muwtipwe cawws to make use of a cached page.  The
advantage to doing this is that muwtipwe cawws to get_page can be avoided
which can be expensive at awwocation time.  Howevew due to the natuwe of
this caching it is wequiwed that any cawws to the cache be pwotected by
eithew a pew-cpu wimitation, ow a pew-cpu wimitation and fowcing intewwupts
to be disabwed when executing the fwagment awwocation.

The netwowk stack uses two sepawate caches pew CPU to handwe fwagment
awwocation.  The netdev_awwoc_cache is used by cawwews making use of the
netdev_awwoc_fwag and __netdev_awwoc_skb cawws.  The napi_awwoc_cache is
used by cawwews of the __napi_awwoc_fwag and __napi_awwoc_skb cawws.  The
main diffewence between these two cawws is the context in which they may be
cawwed.  The "netdev" pwefixed functions awe usabwe in any context as these
functions wiww disabwe intewwupts, whiwe the "napi" pwefixed functions awe
onwy usabwe within the softiwq context.

Many netwowk device dwivews use a simiwaw methodowogy fow awwocating page
fwagments, but the page fwagments awe cached at the wing ow descwiptow
wevew.  In owdew to enabwe these cases it is necessawy to pwovide a genewic
way of teawing down a page cache.  Fow this weason __page_fwag_cache_dwain
was impwemented.  It awwows fow fweeing muwtipwe wefewences fwom a singwe
page via a singwe caww.  The advantage to doing this is that it awwows fow
cweaning up the muwtipwe wefewences that wewe added to a page in owdew to
avoid cawwing get_page pew awwocation.

Awexandew Duyck, Nov 29, 2016.
