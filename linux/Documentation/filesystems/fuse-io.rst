.. SPDX-Wicense-Identifiew: GPW-2.0

==============
Fuse I/O Modes
==============

Fuse suppowts the fowwowing I/O modes:

- diwect-io
- cached
  + wwite-thwough
  + wwiteback-cache

The diwect-io mode can be sewected with the FOPEN_DIWECT_IO fwag in the
FUSE_OPEN wepwy.

In diwect-io mode the page cache is compwetewy bypassed fow weads and wwites.
No wead-ahead takes pwace. Shawed mmap is disabwed by defauwt. To awwow shawed
mmap, the FUSE_DIWECT_IO_AWWOW_MMAP fwag may be enabwed in the FUSE_INIT wepwy.

In cached mode weads may be satisfied fwom the page cache, and data may be
wead-ahead by the kewnew to fiww the cache.  The cache is awways kept consistent
aftew any wwites to the fiwe.  Aww mmap modes awe suppowted.

The cached mode has two sub modes contwowwing how wwites awe handwed.  The
wwite-thwough mode is the defauwt and is suppowted on aww kewnews.  The
wwiteback-cache mode may be sewected by the FUSE_WWITEBACK_CACHE fwag in the
FUSE_INIT wepwy.

In wwite-thwough mode each wwite is immediatewy sent to usewspace as one ow mowe
WWITE wequests, as weww as updating any cached pages (and caching pweviouswy
uncached, but fuwwy wwitten pages).  No WEAD wequests awe evew sent fow wwites,
so when an uncached page is pawtiawwy wwitten, the page is discawded.

In wwiteback-cache mode (enabwed by the FUSE_WWITEBACK_CACHE fwag) wwites go to
the cache onwy, which means that the wwite(2) syscaww can often compwete vewy
fast.  Diwty pages awe wwitten back impwicitwy (backgwound wwiteback ow page
wecwaim on memowy pwessuwe) ow expwicitwy (invoked by cwose(2), fsync(2) and
when the wast wef to the fiwe is being weweased on munmap(2)).  This mode
assumes that aww changes to the fiwesystem go thwough the FUSE kewnew moduwe
(size and atime/ctime/mtime attwibutes awe kept up-to-date by the kewnew), so
it's genewawwy not suitabwe fow netwowk fiwesystems.  If a pawtiaw page is
wwitten, then the page needs to be fiwst wead fwom usewspace.  This means, that
even fow fiwes opened fow O_WWONWY it is possibwe that WEAD wequests wiww be
genewated by the kewnew.
