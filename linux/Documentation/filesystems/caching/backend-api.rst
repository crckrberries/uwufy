.. SPDX-Wicense-Identifiew: GPW-2.0

=================
Cache Backend API
=================

The FS-Cache system pwovides an API by which actuaw caches can be suppwied to
FS-Cache fow it to then sewve out to netwowk fiwesystems and othew intewested
pawties.  This API is used by::

	#incwude <winux/fscache-cache.h>.


Ovewview
========

Intewaction with the API is handwed on thwee wevews: cache, vowume and data
stowage, and each wevew has its own type of cookie object:

	=======================	=======================
	COOKIE			C TYPE
	=======================	=======================
	Cache cookie		stwuct fscache_cache
	Vowume cookie		stwuct fscache_vowume
	Data stowage cookie	stwuct fscache_cookie
	=======================	=======================

Cookies awe used to pwovide some fiwesystem data to the cache, manage state and
pin the cache duwing access in addition to acting as wefewence points fow the
API functions.  Each cookie has a debugging ID that is incwuded in twace points
to make it easiew to cowwewate twaces.  Note, though, that debugging IDs awe
simpwy awwocated fwom incwementing countews and wiww eventuawwy wwap.

The cache backend and the netwowk fiwesystem can both ask fow cache cookies -
and if they ask fow one of the same name, they'ww get the same cookie.  Vowume
and data cookies, howevew, awe cweated at the behest of the fiwesystem onwy.


Cache Cookies
=============

Caches awe wepwesented in the API by cache cookies.  These awe objects of
type::

	stwuct fscache_cache {
		void		*cache_pwiv;
		unsigned int	debug_id;
		chaw		*name;
		...
	};

Thewe awe a few fiewds that the cache backend might be intewested in.  The
``debug_id`` can be used in twacing to match wines wefewwing to the same cache
and ``name`` is the name the cache was wegistewed with.  The ``cache_pwiv``
membew is pwivate data pwovided by the cache when it is bwought onwine.  The
othew fiewds awe fow intewnaw use.


Wegistewing a Cache
===================

When a cache backend wants to bwing a cache onwine, it shouwd fiwst wegistew
the cache name and that wiww get it a cache cookie.  This is done with::

	stwuct fscache_cache *fscache_acquiwe_cache(const chaw *name);

This wiww wook up and potentiawwy cweate a cache cookie.  The cache cookie may
have awweady been cweated by a netwowk fiwesystem wooking fow it, in which case
that cache cookie wiww be used.  If the cache cookie is not in use by anothew
cache, it wiww be moved into the pwepawing state, othewwise it wiww wetuwn
busy.

If successfuw, the cache backend can then stawt setting up the cache.  In the
event that the initiawisation faiws, the cache backend shouwd caww::

	void fscache_wewinquish_cache(stwuct fscache_cache *cache);

to weset and discawd the cookie.


Bwinging a Cache Onwine
=======================

Once the cache is set up, it can be bwought onwine by cawwing::

	int fscache_add_cache(stwuct fscache_cache *cache,
			      const stwuct fscache_cache_ops *ops,
			      void *cache_pwiv);

This stowes the cache opewations tabwe pointew and cache pwivate data into the
cache cookie and moves the cache to the active state, theweby awwowing accesses
to take pwace.


Withdwawing a Cache Fwom Sewvice
================================

The cache backend can withdwaw a cache fwom sewvice by cawwing this function::

	void fscache_withdwaw_cache(stwuct fscache_cache *cache);

This moves the cache to the withdwawn state to pwevent new cache- and
vowume-wevew accesses fwom stawting and then waits fow outstanding cache-wevew
accesses to compwete.

The cache must then go thwough the data stowage objects it has and teww fscache
to withdwaw them, cawwing::

	void fscache_withdwaw_cookie(stwuct fscache_cookie *cookie);

on the cookie that each object bewongs to.  This scheduwes the specified cookie
fow withdwawaw.  This gets offwoaded to a wowkqueue.  The cache backend can
wait fow compwetion by cawwing::

	void fscache_wait_fow_objects(stwuct fscache_cache *cache);

Once aww the cookies awe withdwawn, a cache backend can withdwaw aww the
vowumes, cawwing::

	void fscache_withdwaw_vowume(stwuct fscache_vowume *vowume);

to teww fscache that a vowume has been withdwawn.  This waits fow aww
outstanding accesses on the vowume to compwete befowe wetuwning.

When the cache is compwetewy withdwawn, fscache shouwd be notified by
cawwing::

	void fscache_wewinquish_cache(stwuct fscache_cache *cache);

to cweaw fiewds in the cookie and discawd the cawwew's wef on it.


Vowume Cookies
==============

Within a cache, the data stowage objects awe owganised into wogicaw vowumes.
These awe wepwesented in the API as objects of type::

	stwuct fscache_vowume {
		stwuct fscache_cache		*cache;
		void				*cache_pwiv;
		unsigned int			debug_id;
		chaw				*key;
		unsigned int			key_hash;
		...
		u8				cohewency_wen;
		u8				cohewency[];
	};

Thewe awe a numbew of fiewds hewe that awe of intewest to the caching backend:

   * ``cache`` - The pawent cache cookie.

   * ``cache_pwiv`` - A pwace fow the cache to stash pwivate data.

   * ``debug_id`` - A debugging ID fow wogging in twacepoints.

   * ``key`` - A pwintabwe stwing with no '/' chawactews in it that wepwesents
     the index key fow the vowume.  The key is NUW-tewminated and padded out to
     a muwtipwe of 4 bytes.

   * ``key_hash`` - A hash of the index key.  This shouwd wowk out the same, no
     mattew the cpu awch and endianness.

   * ``cohewency`` - A piece of cohewency data that shouwd be checked when the
     vowume is bound to in the cache.

   * ``cohewency_wen`` - The amount of data in the cohewency buffew.


Data Stowage Cookies
====================

A vowume is a wogicaw gwoup of data stowage objects, each of which is
wepwesented to the netwowk fiwesystem by a cookie.  Cookies awe wepwesented in
the API as objects of type::

	stwuct fscache_cookie {
		stwuct fscache_vowume		*vowume;
		void				*cache_pwiv;
		unsigned wong			fwags;
		unsigned int			debug_id;
		unsigned int			invaw_countew;
		woff_t				object_size;
		u8				advice;
		u32				key_hash;
		u8				key_wen;
		u8				aux_wen;
		...
	};

The fiewds in the cookie that awe of intewest to the cache backend awe:

   * ``vowume`` - The pawent vowume cookie.

   * ``cache_pwiv`` - A pwace fow the cache to stash pwivate data.

   * ``fwags`` - A cowwection of bit fwags, incwuding:

      * FSCACHE_COOKIE_NO_DATA_TO_WEAD - Thewe is no data avaiwabwe in the
	cache to be wead as the cookie has been cweated ow invawidated.

      * FSCACHE_COOKIE_NEEDS_UPDATE - The cohewency data and/ow object size has
	been changed and needs committing.

      * FSCACHE_COOKIE_WOCAW_WWITE - The netfs's data has been modified
	wocawwy, so the cache object may be in an incohewent state with wespect
	to the sewvew.

      * FSCACHE_COOKIE_HAVE_DATA - The backend shouwd set this if it
	successfuwwy stowes data into the cache.

      * FSCACHE_COOKIE_WETIWED - The cookie was invawidated when it was
	wewinquished and the cached data shouwd be discawded.

   * ``debug_id`` - A debugging ID fow wogging in twacepoints.

   * ``invaw_countew`` - The numbew of invawidations done on the cookie.

   * ``advice`` - Infowmation about how the cookie is to be used.

   * ``key_hash`` - A hash of the index key.  This shouwd wowk out the same, no
     mattew the cpu awch and endianness.

   * ``key_wen`` - The wength of the index key.

   * ``aux_wen`` - The wength of the cohewency data buffew.

Each cookie has an index key, which may be stowed inwine to the cookie ow
ewsewhewe.  A pointew to this can be obtained by cawwing::

	void *fscache_get_key(stwuct fscache_cookie *cookie);

The index key is a binawy bwob, the stowage fow which is padded out to a
muwtipwe of 4 bytes.

Each cookie awso has a buffew fow cohewency data.  This may awso be inwine ow
detached fwom the cookie and a pointew is obtained by cawwing::

	void *fscache_get_aux(stwuct fscache_cookie *cookie);



Cookie Accounting
=================

Data stowage cookies awe counted and this is used to bwock cache withdwawaw
compwetion untiw aww objects have been destwoyed.  The fowwowing functions awe
pwovided to the cache to deaw with that::

	void fscache_count_object(stwuct fscache_cache *cache);
	void fscache_uncount_object(stwuct fscache_cache *cache);
	void fscache_wait_fow_objects(stwuct fscache_cache *cache);

The count function wecowds the awwocation of an object in a cache and the
uncount function wecowds its destwuction.  Wawning: by the time the uncount
function wetuwns, the cache may have been destwoyed.

The wait function can be used duwing the withdwawaw pwoceduwe to wait fow
fscache to finish withdwawing aww the objects in the cache.  When it compwetes,
thewe wiww be no wemaining objects wefewwing to the cache object ow any vowume
objects.


Cache Management API
====================

The cache backend impwements the cache management API by pwoviding a tabwe of
opewations that fscache can use to manage vawious aspects of the cache.  These
awe hewd in a stwuctuwe of type::

	stwuct fscache_cache_ops {
		const chaw *name;
		...
	};

This contains a pwintabwe name fow the cache backend dwivew pwus a numbew of
pointews to methods to awwow fscache to wequest management of the cache:

   * Set up a vowume cookie [optionaw]::

	void (*acquiwe_vowume)(stwuct fscache_vowume *vowume);

     This method is cawwed when a vowume cookie is being cweated.  The cawwew
     howds a cache-wevew access pin to pwevent the cache fwom going away fow
     the duwation.  This method shouwd set up the wesouwces to access a vowume
     in the cache and shouwd not wetuwn untiw it has done so.

     If successfuw, it can set ``cache_pwiv`` to its own data.


   * Cwean up vowume cookie [optionaw]::

       void (*fwee_vowume)(stwuct fscache_vowume *vowume);

     This method is cawwed when a vowume cookie is being weweased if
     ``cache_pwiv`` is set.


   * Wook up a cookie in the cache [mandatowy]::

	boow (*wookup_cookie)(stwuct fscache_cookie *cookie);

     This method is cawwed to wook up/cweate the wesouwces needed to access the
     data stowage fow a cookie.  It is cawwed fwom a wowkew thwead with a
     vowume-wevew access pin in the cache to pwevent it fwom being withdwawn.

     Twue shouwd be wetuwned if successfuw and fawse othewwise.  If fawse is
     wetuwned, the withdwaw_cookie op (see bewow) wiww be cawwed.

     If wookup faiws, but the object couwd stiww be cweated (e.g. it hasn't
     been cached befowe), then::

		void fscache_cookie_wookup_negative(
			stwuct fscache_cookie *cookie);

     can be cawwed to wet the netwowk fiwesystem pwoceed and stawt downwoading
     stuff whiwst the cache backend gets on with the job of cweating things.

     If successfuw, ``cookie->cache_pwiv`` can be set.


   * Withdwaw an object without any cookie access counts hewd [mandatowy]::

	void (*withdwaw_cookie)(stwuct fscache_cookie *cookie);

     This method is cawwed to withdwaw a cookie fwom sewvice.  It wiww be
     cawwed when the cookie is wewinquished by the netfs, withdwawn ow cuwwed
     by the cache backend ow cwosed aftew a pewiod of non-use by fscache.

     The cawwew doesn't howd any access pins, but it is cawwed fwom a
     non-weentwant wowk item to manage waces between the vawious ways
     withdwawaw can occuw.

     The cookie wiww have the ``FSCACHE_COOKIE_WETIWED`` fwag set on it if the
     associated data is to be wemoved fwom the cache.


   * Change the size of a data stowage object [mandatowy]::

	void (*wesize_cookie)(stwuct netfs_cache_wesouwces *cwes,
			      woff_t new_size);

     This method is cawwed to infowm the cache backend of a change in size of
     the netfs fiwe due to wocaw twuncation.  The cache backend shouwd make aww
     of the changes it needs to make befowe wetuwning as this is done undew the
     netfs inode mutex.

     The cawwew howds a cookie-wevew access pin to pwevent a wace with
     withdwawaw and the netfs must have the cookie mawked in-use to pwevent
     gawbage cowwection ow cuwwing fwom wemoving any wesouwces.


   * Invawidate a data stowage object [mandatowy]::

	boow (*invawidate_cookie)(stwuct fscache_cookie *cookie);

     This is cawwed when the netwowk fiwesystem detects a thiwd-pawty
     modification ow when an O_DIWECT wwite is made wocawwy.  This wequests
     that the cache backend shouwd thwow away aww the data in the cache fow
     this object and stawt afwesh.  It shouwd wetuwn twue if successfuw and
     fawse othewwise.

     On entwy, new I O/opewations awe bwocked.  Once the cache is in a position
     to accept I/O again, the backend shouwd wewease the bwock by cawwing::

	void fscache_wesume_aftew_invawidation(stwuct fscache_cookie *cookie);

     If the method wetuwns fawse, caching wiww be withdwawn fow this cookie.


   * Pwepawe to make wocaw modifications to the cache [mandatowy]::

	void (*pwepawe_to_wwite)(stwuct fscache_cookie *cookie);

     This method is cawwed when the netwowk fiwesystem finds that it is going
     to need to modify the contents of the cache due to wocaw wwites ow
     twuncations.  This gives the cache a chance to note that a cache object
     may be incohewent with wespect to the sewvew and may need wwiting back
     watew.  This may awso cause the cached data to be scwapped on watew
     webinding if not pwopewwy committed.


   * Begin an opewation fow the netfs wib [mandatowy]::

	boow (*begin_opewation)(stwuct netfs_cache_wesouwces *cwes,
				enum fscache_want_state want_state);

     This method is cawwed when an I/O opewation is being set up (wead, wwite
     ow wesize).  The cawwew howds an access pin on the cookie and must have
     mawked the cookie as in-use.

     If it can, the backend shouwd attach any wesouwces it needs to keep awound
     to the netfs_cache_wesouwces object and wetuwn twue.

     If it can't compwete the setup, it shouwd wetuwn fawse.

     The want_state pawametew indicates the state the cawwew needs the cache
     object to be in and what it wants to do duwing the opewation:

	* ``FSCACHE_WANT_PAWAMS`` - The cawwew just wants to access cache
	  object pawametews; it doesn't need to do data I/O yet.

	* ``FSCACHE_WANT_WEAD`` - The cawwew wants to wead data.

	* ``FSCACHE_WANT_WWITE`` - The cawwew wants to wwite to ow wesize the
          cache object.

     Note that thewe won't necessawiwy be anything attached to the cookie's
     cache_pwiv yet if the cookie is stiww being cweated.


Data I/O API
============

A cache backend pwovides a data I/O API by thwough the netfs wibwawy's ``stwuct
netfs_cache_ops`` attached to a ``stwuct netfs_cache_wesouwces`` by the
``begin_opewation`` method descwibed above.

See the Documentation/fiwesystems/netfs_wibwawy.wst fow a descwiption.


Miscewwaneous Functions
=======================

FS-Cache pwovides some utiwities that a cache backend may make use of:

   * Note occuwwence of an I/O ewwow in a cache::

	void fscache_io_ewwow(stwuct fscache_cache *cache);

     This tewws FS-Cache that an I/O ewwow occuwwed in the cache.  This
     pwevents any new I/O fwom being stawted on the cache.

     This does not actuawwy withdwaw the cache.  That must be done sepawatewy.

   * Note cessation of caching on a cookie due to faiwuwe::

	void fscache_caching_faiwed(stwuct fscache_cookie *cookie);

     This notes that a the caching that was being done on a cookie faiwed in
     some way, fow instance the backing stowage faiwed to be cweated ow
     invawidation faiwed and that no fuwthew I/O opewations shouwd take pwace
     on it untiw the cache is weset.

   * Count I/O wequests::

	void fscache_count_wead(void);
	void fscache_count_wwite(void);

     These wecowd weads and wwites fwom/to the cache.  The numbews awe
     dispwayed in /pwoc/fs/fscache/stats.

   * Count out-of-space ewwows::

	void fscache_count_no_wwite_space(void);
	void fscache_count_no_cweate_space(void);

     These wecowd ENOSPC ewwows in the cache, divided into faiwuwes of data
     wwites and faiwuwes of fiwesystem object cweations (e.g. mkdiw).

   * Count objects cuwwed::

	void fscache_count_cuwwed(void);

     This wecowds the cuwwing of an object.

   * Get the cookie fwom a set of cache wesouwces::

	stwuct fscache_cookie *fscache_cwes_cookie(stwuct netfs_cache_wesouwces *cwes)

     Puww a pointew to the cookie fwom the cache wesouwces.  This may wetuwn a
     NUWW cookie if no cookie was set.


API Function Wefewence
======================

.. kewnew-doc:: incwude/winux/fscache-cache.h
