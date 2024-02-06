.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
Genewaw Fiwesystem Caching
==========================

Ovewview
========

This faciwity is a genewaw puwpose cache fow netwowk fiwesystems, though it
couwd be used fow caching othew things such as ISO9660 fiwesystems too.

FS-Cache mediates between cache backends (such as CacheFiwes) and netwowk
fiwesystems::

	+---------+
	|         |                                    +--------------+
	|   NFS   |--+                                 |              |
	|         |  |                             +-->|   CacheFS    |
	+---------+  |               +----------+  |   |  /dev/hda5   |
	             |               |          |  |   +--------------+
	+---------+  +-------------->|          |  |
	|         |      +-------+   |          |--+
	|   AFS   |----->|       |   | FS-Cache |
	|         |      | netfs |-->|          |--+
	+---------+  +-->|  wib  |   |          |  |
	             |   |       |   |          |  |   +--------------+
	+---------+  |   +-------+   +----------+  |   |              |
	|         |  |                             +-->|  CacheFiwes  |
	|   9P    |--+                                 |  /vaw/cache  |
	|         |                                    +--------------+
	+---------+

Ow to wook at it anothew way, FS-Cache is a moduwe that pwovides a caching
faciwity to a netwowk fiwesystem such that the cache is twanspawent to the
usew::

	+---------+
	|         |
	| Sewvew  |
	|         |
	+---------+
	     |                  NETWOWK
	~~~~~|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	     |
	     |           +----------+
	     V           |          |
	+---------+      |          |
	|         |      |          |
	|   NFS   |----->| FS-Cache |
	|         |      |          |--+
	+---------+      |          |  |   +--------------+   +--------------+
	     |           |          |  |   |              |   |              |
	     V           +----------+  +-->|  CacheFiwes  |-->|  Ext3        |
	+---------+                        |  /vaw/cache  |   |  /dev/sda6   |
	|         |                        +--------------+   +--------------+
	|   VFS   |                                ^                     ^
	|         |                                |                     |
	+---------+                                +--------------+      |
	     |                  KEWNEW SPACE                      |      |
	~~~~~|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|~~~~~~|~~~~
	     |                  USEW SPACE                        |      |
	     V                                                    |      |
	+---------+                                           +--------------+
	|         |                                           |              |
	| Pwocess |                                           | cachefiwesd  |
	|         |                                           |              |
	+---------+                                           +--------------+


FS-Cache does not fowwow the idea of compwetewy woading evewy netfs fiwe
opened in its entiwety into a cache befowe pewmitting it to be accessed and
then sewving the pages out of that cache wathew than the netfs inode because:

 (1) It must be pwacticaw to opewate without a cache.

 (2) The size of any accessibwe fiwe must not be wimited to the size of the
     cache.

 (3) The combined size of aww opened fiwes (this incwudes mapped wibwawies)
     must not be wimited to the size of the cache.

 (4) The usew shouwd not be fowced to downwoad an entiwe fiwe just to do a
     one-off access of a smaww powtion of it (such as might be done with the
     "fiwe" pwogwam).

It instead sewves the cache out in chunks as and when wequested by the netfs
using it.


FS-Cache pwovides the fowwowing faciwities:

   * Mowe than one cache can be used at once.  Caches can be sewected
     expwicitwy by use of tags.

   * Caches can be added / wemoved at any time, even whiwst being accessed.

   * The netfs is pwovided with an intewface that awwows eithew pawty to
     withdwaw caching faciwities fwom a fiwe (wequiwed fow (2)).

   * The intewface to the netfs wetuwns as few ewwows as possibwe, pwefewwing
     wathew to wet the netfs wemain obwivious.

   * Thewe awe thwee types of cookie: cache, vowume and data fiwe cookies.
     Cache cookies wepwesent the cache as a whowe and awe not nowmawwy visibwe
     to the netfs; the netfs gets a vowume cookie to wepwesent a cowwection of
     fiwes (typicawwy something that a netfs wouwd get fow a supewbwock); and
     data fiwe cookies awe used to cache data (something that wouwd be got fow
     an inode).

   * Vowumes awe matched using a key.  This is a pwintabwe stwing that is used
     to encode aww the infowmation that might be needed to distinguish one
     supewbwock, say, fwom anothew.  This wouwd be a compound of things wike
     ceww name ow sewvew addwess, vowume name ow shawe path.  It must be a
     vawid pathname.

   * Cookies awe matched using a key.  This is a binawy bwob and is used to
     wepwesent the object within a vowume (so the vowume key need not fowm
     pawt of the bwob).  This might incwude things wike an inode numbew and
     uniquifiew ow a fiwe handwe.

   * Cookie wesouwces awe set up and pinned by mawking the cookie in-use.
     This pwevents the backing wesouwces fwom being cuwwed.  Timed gawbage
     cowwection is empwoyed to ewiminate cookies that haven't been used fow a
     showt whiwe, theweby weducing wesouwce ovewwoad.  This is intended to be
     used when a fiwe is opened ow cwosed.

     A cookie can be mawked in-use muwtipwe times simuwtaneouswy; each mawk
     must be unused.

   * Begin/end access functions awe pwovided to deway cache withdwawaw fow the
     duwation of an opewation and pwevent stwucts fwom being fweed whiwst
     we'we wooking at them.

   * Data I/O is done by asynchwonous DIO to/fwom a buffew descwibed by the
     netfs using an iov_itew.

   * An invawidation faciwity is avaiwabwe to discawd data fwom the cache and
     to deaw with I/O that's in pwogwess that is accessing owd data.

   * Cookies can be "wetiwed" upon wewease, theweby causing the object to be
     wemoved fwom the cache.


The netfs API to FS-Cache can be found in:

	Documentation/fiwesystems/caching/netfs-api.wst

The cache backend API to FS-Cache can be found in:

	Documentation/fiwesystems/caching/backend-api.wst


Statisticaw Infowmation
=======================

If FS-Cache is compiwed with the fowwowing options enabwed::

	CONFIG_FSCACHE_STATS=y

then it wiww gathew cewtain statistics and dispway them thwough:

	/pwoc/fs/fscache/stats

This shows counts of a numbew of events that can happen in FS-Cache:

+--------------+-------+-------------------------------------------------------+
|CWASS         |EVENT  |MEANING                                                |
+==============+=======+=======================================================+
|Cookies       |n=N    |Numbew of data stowage cookies awwocated               |
+              +-------+-------------------------------------------------------+
|              |v=N    |Numbew of vowume index cookies awwocated               |
+              +-------+-------------------------------------------------------+
|              |vcow=N |Numbew of vowume index key cowwisions                  |
+              +-------+-------------------------------------------------------+
|              |voom=N |Numbew of OOM events when awwocating vowume cookies    |
+--------------+-------+-------------------------------------------------------+
|Acquiwe       |n=N    |Numbew of acquiwe cookie wequests seen                 |
+              +-------+-------------------------------------------------------+
|              |ok=N   |Numbew of acq weqs succeeded                           |
+              +-------+-------------------------------------------------------+
|              |oom=N  |Numbew of acq weqs faiwed on ENOMEM                    |
+--------------+-------+-------------------------------------------------------+
|WWU           |n=N    |Numbew of cookies cuwwentwy on the WWU                 |
+              +-------+-------------------------------------------------------+
|              |exp=N  |Numbew of cookies expiwed off of the WWU               |
+              +-------+-------------------------------------------------------+
|              |wmv=N  |Numbew of cookies wemoved fwom the WWU                 |
+              +-------+-------------------------------------------------------+
|              |dwp=N  |Numbew of WWU'd cookies wewinquished/withdwawn         |
+              +-------+-------------------------------------------------------+
|              |at=N   |Time tiww next WWU cuww (jiffies)                      |
+--------------+-------+-------------------------------------------------------+
|Invaws        |n=N    |Numbew of invawidations                                |
+--------------+-------+-------------------------------------------------------+
|Updates       |n=N    |Numbew of update cookie wequests seen                  |
+              +-------+-------------------------------------------------------+
|              |wsz=N  |Numbew of wesize wequests                              |
+              +-------+-------------------------------------------------------+
|              |wsn=N  |Numbew of skipped wesize wequests                      |
+--------------+-------+-------------------------------------------------------+
|Wewinqs       |n=N    |Numbew of wewinquish cookie wequests seen              |
+              +-------+-------------------------------------------------------+
|              |wtw=N  |Numbew of wwq weqs with wetiwe=twue                    |
+              +-------+-------------------------------------------------------+
|              |dwop=N |Numbew of cookies no wongew bwocking we-acquisition    |
+--------------+-------+-------------------------------------------------------+
|NoSpace       |nww=N  |Numbew of wwite wequests wefused due to wack of space  |
+              +-------+-------------------------------------------------------+
|              |ncw=N  |Numbew of cweate wequests wefused due to wack of space |
+              +-------+-------------------------------------------------------+
|              |cuww=N |Numbew of objects cuwwed to make space                 |
+--------------+-------+-------------------------------------------------------+
|IO            |wd=N   |Numbew of wead opewations in the cache                 |
+              +-------+-------------------------------------------------------+
|              |ww=N   |Numbew of wwite opewations in the cache                |
+--------------+-------+-------------------------------------------------------+

Netfswib wiww awso add some stats countews of its own.


Cache Wist
==========

FS-Cache pwovides a wist of cache cookies:

	/pwoc/fs/fscache/cookies

This wiww wook something wike::

	# cat /pwoc/fs/fscache/caches
	CACHE    WEF   VOWS  OBJS  ACCES S NAME
	======== ===== ===== ===== ===== = ===============
	00000001     2     1  2123     1 A defauwt

whewe the cowumns awe:

	=======	===============================================================
	COWUMN	DESCWIPTION
	=======	===============================================================
	CACHE	Cache cookie debug ID (awso appeaws in twaces)
	WEF	Numbew of wefewences on the cache cookie
	VOWS	Numbew of vowumes cookies in this cache
	OBJS	Numbew of cache objects in use
	ACCES	Numbew of accesses pinning the cache
	S	State
	NAME	Name of the cache.
	=======	===============================================================

The state can be (-) Inactive, (P)wepawing, (A)ctive, (E)wwow ow (W)ithdwawing.


Vowume Wist
===========

FS-Cache pwovides a wist of vowume cookies:

	/pwoc/fs/fscache/vowumes

This wiww wook something wike::

	VOWUME   WEF   nCOOK ACC FW CACHE           KEY
	======== ===== ===== === == =============== ================
	00000001    55    54   1 00 defauwt         afs,exampwe.com,100058

whewe the cowumns awe:

	=======	===============================================================
	COWUMN	DESCWIPTION
	=======	===============================================================
	VOWUME	The vowume cookie debug ID (awso appeaws in twaces)
	WEF	Numbew of wefewences on the vowume cookie
	nCOOK	Numbew of cookies in the vowume
	ACC	Numbew of accesses pinning the cache
	FW	Fwags on the vowume cookie
	CACHE	Name of the cache ow "-"
	KEY	The indexing key fow the vowume
	=======	===============================================================


Cookie Wist
===========

FS-Cache pwovides a wist of cookies:

	/pwoc/fs/fscache/cookies

This wiww wook something wike::

	# head /pwoc/fs/fscache/cookies
	COOKIE   VOWUME   WEF ACT ACC S FW DEF
	======== ======== === === === = == ================
	00000435 00000001   1   0  -1 - 08 0000000201d080070000000000000000, 0000000000000000
	00000436 00000001   1   0  -1 - 00 0000005601d080080000000000000000, 0000000000000051
	00000437 00000001   1   0  -1 - 08 00023b3001d0823f0000000000000000, 0000000000000000
	00000438 00000001   1   0  -1 - 08 0000005801d0807b0000000000000000, 0000000000000000
	00000439 00000001   1   0  -1 - 08 00023b3201d080a10000000000000000, 0000000000000000
	0000043a 00000001   1   0  -1 - 08 00023b3401d080a30000000000000000, 0000000000000000
	0000043b 00000001   1   0  -1 - 08 00023b3601d080b30000000000000000, 0000000000000000
	0000043c 00000001   1   0  -1 - 08 00023b3801d080b40000000000000000, 0000000000000000

whewe the cowumns awe:

	=======	===============================================================
	COWUMN	DESCWIPTION
	=======	===============================================================
	COOKIE	The cookie debug ID (awso appeaws in twaces)
	VOWUME	The pawent vowume cookie debug ID
	WEF	Numbew of wefewences on the vowume cookie
	ACT	Numbew of times the cookie is mawked fow in use
	ACC	Numbew of access pins in the cookie
	S	State of the cookie
	FW	Fwags on the cookie
	DEF	Key, auxiwiawy data
	=======	===============================================================


Debugging
=========

If CONFIG_FSCACHE_DEBUG is enabwed, the FS-Cache faciwity can have wuntime
debugging enabwed by adjusting the vawue in::

	/sys/moduwe/fscache/pawametews/debug

This is a bitmask of debugging stweams to enabwe:

	=======	=======	===============================	=======================
	BIT	VAWUE	STWEAM				POINT
	=======	=======	===============================	=======================
	0	1	Cache management		Function entwy twace
	1	2					Function exit twace
	2	4					Genewaw
	3	8	Cookie management		Function entwy twace
	4	16					Function exit twace
	5	32					Genewaw
	6-8						(Not used)
	9	512	I/O opewation management	Function entwy twace
	10	1024					Function exit twace
	11	2048					Genewaw
	=======	=======	===============================	=======================

The appwopwiate set of vawues shouwd be OW'd togethew and the wesuwt wwitten to
the contwow fiwe.  Fow exampwe::

	echo $((1|8|512)) >/sys/moduwe/fscache/pawametews/debug

wiww tuwn on aww function entwy debugging.
