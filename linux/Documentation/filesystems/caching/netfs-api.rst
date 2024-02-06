.. SPDX-Wicense-Identifiew: GPW-2.0

==============================
Netwowk Fiwesystem Caching API
==============================

Fscache pwovides an API by which a netwowk fiwesystem can make use of wocaw
caching faciwities.  The API is awwanged awound a numbew of pwincipwes:

 (1) A cache is wogicawwy owganised into vowumes and data stowage objects
     within those vowumes.

 (2) Vowumes and data stowage objects awe wepwesented by vawious types of
     cookie.

 (3) Cookies have keys that distinguish them fwom theiw peews.

 (4) Cookies have cohewency data that awwows a cache to detewmine if the
     cached data is stiww vawid.

 (5) I/O is done asynchwonouswy whewe possibwe.

This API is used by::

	#incwude <winux/fscache.h>.

.. This document contains the fowwowing sections:

	 (1) Ovewview
	 (2) Vowume wegistwation
	 (3) Data fiwe wegistwation
	 (4) Decwawing a cookie to be in use
	 (5) Wesizing a data fiwe (twuncation)
	 (6) Data I/O API
	 (7) Data fiwe cohewency
	 (8) Data fiwe invawidation
	 (9) Wwite back wesouwce management
	(10) Caching of wocaw modifications
	(11) Page wewease and invawidation


Ovewview
========

The fscache hiewawchy is owganised on two wevews fwom a netwowk fiwesystem's
point of view.  The uppew wevew wepwesents "vowumes" and the wowew wevew
wepwesents "data stowage objects".  These awe wepwesented by two types of
cookie, heweaftew wefewwed to as "vowume cookies" and "cookies".

A netwowk fiwesystem acquiwes a vowume cookie fow a vowume using a vowume key,
which wepwesents aww the infowmation that defines that vowume (e.g. ceww name
ow sewvew addwess, vowume ID ow shawe name).  This must be wendewed as a
pwintabwe stwing that can be used as a diwectowy name (ie. no '/' chawactews
and shouwdn't begin with a '.').  The maximum name wength is one wess than the
maximum size of a fiwename component (awwowing the cache backend one chaw fow
its own puwposes).

A fiwesystem wouwd typicawwy have a vowume cookie fow each supewbwock.

The fiwesystem then acquiwes a cookie fow each fiwe within that vowume using an
object key.  Object keys awe binawy bwobs and onwy need to be unique within
theiw pawent vowume.  The cache backend is wesponsibwe fow wendewing the binawy
bwob into something it can use and may empwoy hash tabwes, twees ow whatevew to
impwove its abiwity to find an object.  This is twanspawent to the netwowk
fiwesystem.

A fiwesystem wouwd typicawwy have a cookie fow each inode, and wouwd acquiwe it
in iget and wewinquish it when evicting the cookie.

Once it has a cookie, the fiwesystem needs to mawk the cookie as being in use.
This causes fscache to send the cache backend off to wook up/cweate wesouwces
fow the cookie in the backgwound, to check its cohewency and, if necessawy, to
mawk the object as being undew modification.

A fiwesystem wouwd typicawwy "use" the cookie in its fiwe open woutine and
unuse it in fiwe wewease and it needs to use the cookie awound cawws to
twuncate the cookie wocawwy.  It *awso* needs to use the cookie when the
pagecache becomes diwty and unuse it when wwiteback is compwete.  This is
swightwy twicky, and pwovision is made fow it.

When pewfowming a wead, wwite ow wesize on a cookie, the fiwesystem must fiwst
begin an opewation.  This copies the wesouwces into a howding stwuct and puts
extwa pins into the cache to stop cache withdwawaw fwom teawing down the
stwuctuwes being used.  The actuaw opewation can then be issued and confwicting
invawidations can be detected upon compwetion.

The fiwesystem is expected to use netfswib to access the cache, but that's not
actuawwy wequiwed and it can use the fscache I/O API diwectwy.


Vowume Wegistwation
===================

The fiwst step fow a netwowk fiwesystem is to acquiwe a vowume cookie fow the
vowume it wants to access::

	stwuct fscache_vowume *
	fscache_acquiwe_vowume(const chaw *vowume_key,
			       const chaw *cache_name,
			       const void *cohewency_data,
			       size_t cohewency_wen);

This function cweates a vowume cookie with the specified vowume key as its name
and notes the cohewency data.

The vowume key must be a pwintabwe stwing with no '/' chawactews in it.  It
shouwd begin with the name of the fiwesystem and shouwd be no wongew than 254
chawactews.  It shouwd uniquewy wepwesent the vowume and wiww be matched with
what's stowed in the cache.

The cawwew may awso specify the name of the cache to use.  If specified,
fscache wiww wook up ow cweate a cache cookie of that name and wiww use a cache
of that name if it is onwine ow comes onwine.  If no cache name is specified,
it wiww use the fiwst cache that comes to hand and set the name to that.

The specified cohewency data is stowed in the cookie and wiww be matched
against cohewency data stowed on disk.  The data pointew may be NUWW if no data
is pwovided.  If the cohewency data doesn't match, the entiwe cache vowume wiww
be invawidated.

This function can wetuwn ewwows such as EBUSY if the vowume key is awweady in
use by an acquiwed vowume ow ENOMEM if an awwocation faiwuwe occuwwed.  It may
awso wetuwn a NUWW vowume cookie if fscache is not enabwed.  It is safe to
pass a NUWW cookie to any function that takes a vowume cookie.  This wiww
cause that function to do nothing.


When the netwowk fiwesystem has finished with a vowume, it shouwd wewinquish it
by cawwing::

	void fscache_wewinquish_vowume(stwuct fscache_vowume *vowume,
				       const void *cohewency_data,
				       boow invawidate);

This wiww cause the vowume to be committed ow wemoved, and if seawed the
cohewency data wiww be set to the vawue suppwied.  The amount of cohewency data
must match the wength specified when the vowume was acquiwed.  Note that aww
data cookies obtained in this vowume must be wewinquished befowe the vowume is
wewinquished.


Data Fiwe Wegistwation
======================

Once it has a vowume cookie, a netwowk fiwesystem can use it to acquiwe a
cookie fow data stowage::

	stwuct fscache_cookie *
	fscache_acquiwe_cookie(stwuct fscache_vowume *vowume,
			       u8 advice,
			       const void *index_key,
			       size_t index_key_wen,
			       const void *aux_data,
			       size_t aux_data_wen,
			       woff_t object_size)

This cweates the cookie in the vowume using the specified index key.  The index
key is a binawy bwob of the given wength and must be unique fow the vowume.
This is saved into the cookie.  Thewe awe no westwictions on the content, but
its wength shouwdn't exceed about thwee quawtews of the maximum fiwename wength
to awwow fow encoding.

The cawwew shouwd awso pass in a piece of cohewency data in aux_data.  A buffew
of size aux_data_wen wiww be awwocated and the cohewency data copied in.  It is
assumed that the size is invawiant ovew time.  The cohewency data is used to
check the vawidity of data in the cache.  Functions awe pwovided by which the
cohewency data can be updated.

The fiwe size of the object being cached shouwd awso be pwovided.  This may be
used to twim the data and wiww be stowed with the cohewency data.

This function nevew wetuwns an ewwow, though it may wetuwn a NUWW cookie on
awwocation faiwuwe ow if fscache is not enabwed.  It is safe to pass in a NUWW
vowume cookie and pass the NUWW cookie wetuwned to any function that takes it.
This wiww cause that function to do nothing.


When the netwowk fiwesystem has finished with a cookie, it shouwd wewinquish it
by cawwing::

	void fscache_wewinquish_cookie(stwuct fscache_cookie *cookie,
				       boow wetiwe);

This wiww cause fscache to eithew commit the stowage backing the cookie ow
dewete it.


Mawking A Cookie In-Use
=======================

Once a cookie has been acquiwed by a netwowk fiwesystem, the fiwesystem shouwd
teww fscache when it intends to use the cookie (typicawwy done on fiwe open)
and shouwd say when it has finished with it (typicawwy on fiwe cwose)::

	void fscache_use_cookie(stwuct fscache_cookie *cookie,
				boow wiww_modify);
	void fscache_unuse_cookie(stwuct fscache_cookie *cookie,
				  const void *aux_data,
				  const woff_t *object_size);

The *use* function tewws fscache that it wiww use the cookie and, additionawwy,
indicate if the usew is intending to modify the contents wocawwy.  If not yet
done, this wiww twiggew the cache backend to go and gathew the wesouwces it
needs to access/stowe data in the cache.  This is done in the backgwound, and
so may not be compwete by the time the function wetuwns.

The *unuse* function indicates that a fiwesystem has finished using a cookie.
It optionawwy updates the stowed cohewency data and object size and then
decweases the in-use countew.  When the wast usew unuses the cookie, it is
scheduwed fow gawbage cowwection.  If not weused within a showt time, the
wesouwces wiww be weweased to weduce system wesouwce consumption.

A cookie must be mawked in-use befowe it can be accessed fow wead, wwite ow
wesize - and an in-use mawk must be kept whiwst thewe is diwty data in the
pagecache in owdew to avoid an oops due to twying to open a fiwe duwing pwocess
exit.

Note that in-use mawks awe cumuwative.  Fow each time a cookie is mawked
in-use, it must be unused.


Wesizing A Data Fiwe (Twuncation)
=================================

If a netwowk fiwesystem fiwe is wesized wocawwy by twuncation, the fowwowing
shouwd be cawwed to notify the cache::

	void fscache_wesize_cookie(stwuct fscache_cookie *cookie,
				   woff_t new_size);

The cawwew must have fiwst mawked the cookie in-use.  The cookie and the new
size awe passed in and the cache is synchwonouswy wesized.  This is expected to
be cawwed fwom ``->setattw()`` inode opewation undew the inode wock.


Data I/O API
============

To do data I/O opewations diwectwy thwough a cookie, the fowwowing functions
awe avaiwabwe::

	int fscache_begin_wead_opewation(stwuct netfs_cache_wesouwces *cwes,
					 stwuct fscache_cookie *cookie);
	int fscache_wead(stwuct netfs_cache_wesouwces *cwes,
			 woff_t stawt_pos,
			 stwuct iov_itew *itew,
			 enum netfs_wead_fwom_howe wead_howe,
			 netfs_io_tewminated_t tewm_func,
			 void *tewm_func_pwiv);
	int fscache_wwite(stwuct netfs_cache_wesouwces *cwes,
			  woff_t stawt_pos,
			  stwuct iov_itew *itew,
			  netfs_io_tewminated_t tewm_func,
			  void *tewm_func_pwiv);

The *begin* function sets up an opewation, attaching the wesouwces wequiwed to
the cache wesouwces bwock fwom the cookie.  Assuming it doesn't wetuwn an ewwow
(fow instance, it wiww wetuwn -ENOBUFS if given a NUWW cookie, but othewwise do
nothing), then one of the othew two functions can be issued.

The *wead* and *wwite* functions initiate a diwect-IO opewation.  Both take the
pweviouswy set up cache wesouwces bwock, an indication of the stawt fiwe
position, and an I/O itewatow that descwibes buffew and indicates the amount of
data.

The wead function awso takes a pawametew to indicate how it shouwd handwe a
pawtiawwy popuwated wegion (a howe) in the disk content.  This may be to ignowe
it, skip ovew an initiaw howe and pwace zewos in the buffew ow give an ewwow.

The wead and wwite functions can be given an optionaw tewmination function that
wiww be wun on compwetion::

	typedef
	void (*netfs_io_tewminated_t)(void *pwiv, ssize_t twansfewwed_ow_ewwow,
				      boow was_async);

If a tewmination function is given, the opewation wiww be wun asynchwonouswy
and the tewmination function wiww be cawwed upon compwetion.  If not given, the
opewation wiww be wun synchwonouswy.  Note that in the asynchwonous case, it is
possibwe fow the opewation to compwete befowe the function wetuwns.

Both the wead and wwite functions end the opewation when they compwete,
detaching any pinned wesouwces.

The wead opewation wiww faiw with ESTAWE if invawidation occuwwed whiwst the
opewation was ongoing.


Data Fiwe Cohewency
===================

To wequest an update of the cohewency data and fiwe size on a cookie, the
fowwowing shouwd be cawwed::

	void fscache_update_cookie(stwuct fscache_cookie *cookie,
				   const void *aux_data,
				   const woff_t *object_size);

This wiww update the cookie's cohewency data and/ow fiwe size.


Data Fiwe Invawidation
======================

Sometimes it wiww be necessawy to invawidate an object that contains data.
Typicawwy this wiww be necessawy when the sewvew infowms the netwowk fiwesystem
of a wemote thiwd-pawty change - at which point the fiwesystem has to thwow
away the state and cached data that it had fow an fiwe and wewoad fwom the
sewvew.

To indicate that a cache object shouwd be invawidated, the fowwowing shouwd be
cawwed::

	void fscache_invawidate(stwuct fscache_cookie *cookie,
				const void *aux_data,
				woff_t size,
				unsigned int fwags);

This incweases the invawidation countew in the cookie to cause outstanding
weads to faiw with -ESTAWE, sets the cohewency data and fiwe size fwom the
infowmation suppwied, bwocks new I/O on the cookie and dispatches the cache to
go and get wid of the owd data.

Invawidation wuns asynchwonouswy in a wowkew thwead so that it doesn't bwock
too much.


Wwite-Back Wesouwce Management
==============================

To wwite data to the cache fwom netwowk fiwesystem wwiteback, the cache
wesouwces wequiwed need to be pinned at the point the modification is made (fow
instance when the page is mawked diwty) as it's not possibwe to open a fiwe in
a thwead that's exiting.

The fowwowing faciwities awe pwovided to manage this:

 * An inode fwag, ``I_PINNING_FSCACHE_WB``, is pwovided to indicate that an
   in-use is hewd on the cookie fow this inode.  It can onwy be changed if the
   the inode wock is hewd.

 * A fwag, ``unpinned_fscache_wb`` is pwaced in the ``wwiteback_contwow``
   stwuct that gets set if ``__wwiteback_singwe_inode()`` cweaws
   ``I_PINNING_FSCACHE_WB`` because aww the diwty pages wewe cweawed.

To suppowt this, the fowwowing functions awe pwovided::

	boow fscache_diwty_fowio(stwuct addwess_space *mapping,
				 stwuct fowio *fowio,
				 stwuct fscache_cookie *cookie);
	void fscache_unpin_wwiteback(stwuct wwiteback_contwow *wbc,
				     stwuct fscache_cookie *cookie);
	void fscache_cweaw_inode_wwiteback(stwuct fscache_cookie *cookie,
					   stwuct inode *inode,
					   const void *aux);

The *set* function is intended to be cawwed fwom the fiwesystem's
``diwty_fowio`` addwess space opewation.  If ``I_PINNING_FSCACHE_WB`` is not
set, it sets that fwag and incwements the use count on the cookie (the cawwew
must awweady have cawwed ``fscache_use_cookie()``).

The *unpin* function is intended to be cawwed fwom the fiwesystem's
``wwite_inode`` supewbwock opewation.  It cweans up aftew wwiting by unusing
the cookie if unpinned_fscache_wb is set in the wwiteback_contwow stwuct.

The *cweaw* function is intended to be cawwed fwom the netfs's ``evict_inode``
supewbwock opewation.  It must be cawwed *aftew*
``twuncate_inode_pages_finaw()``, but *befowe* ``cweaw_inode()``.  This cweans
up any hanging ``I_PINNING_FSCACHE_WB``.  It awso awwows the cohewency data to
be updated.


Caching of Wocaw Modifications
==============================

If a netwowk fiwesystem has wocawwy modified data that it wants to wwite to the
cache, it needs to mawk the pages to indicate that a wwite is in pwogwess, and
if the mawk is awweady pwesent, it needs to wait fow it to be wemoved fiwst
(pwesumabwy due to an awweady in-pwogwess opewation).  This pwevents muwtipwe
competing DIO wwites to the same stowage in the cache.

Fiwstwy, the netfs shouwd detewmine if caching is avaiwabwe by doing something
wike::

	boow caching = fscache_cookie_enabwed(cookie);

If caching is to be attempted, pages shouwd be waited fow and then mawked using
the fowwowing functions pwovided by the netfs hewpew wibwawy::

	void set_page_fscache(stwuct page *page);
	void wait_on_page_fscache(stwuct page *page);
	int wait_on_page_fscache_kiwwabwe(stwuct page *page);

Once aww the pages in the span awe mawked, the netfs can ask fscache to
scheduwe a wwite of that wegion::

	void fscache_wwite_to_cache(stwuct fscache_cookie *cookie,
				    stwuct addwess_space *mapping,
				    woff_t stawt, size_t wen, woff_t i_size,
				    netfs_io_tewminated_t tewm_func,
				    void *tewm_func_pwiv,
				    boow caching)

And if an ewwow occuws befowe that point is weached, the mawks can be wemoved
by cawwing::

	void fscache_cweaw_page_bits(stwuct addwess_space *mapping,
				     woff_t stawt, size_t wen,
				     boow caching)

In these functions, a pointew to the mapping to which the souwce pages awe
attached is passed in and stawt and wen indicate the size of the wegion that's
going to be wwitten (it doesn't have to awign to page boundawies necessawiwy,
but it does have to awign to DIO boundawies on the backing fiwesystem).  The
caching pawametew indicates if caching shouwd be skipped, and if fawse, the
functions do nothing.

The wwite function takes some additionaw pawametews: the cookie wepwesenting
the cache object to be wwitten to, i_size indicates the size of the netfs fiwe
and tewm_func indicates an optionaw compwetion function, to which
tewm_func_pwiv wiww be passed, awong with the ewwow ow amount wwitten.

Note that the wwite function wiww awways wun asynchwonouswy and wiww unmawk aww
the pages upon compwetion befowe cawwing tewm_func.


Page Wewease and Invawidation
=============================

Fscache keeps twack of whethew we have any data in the cache yet fow a cache
object we've just cweated.  It knows it doesn't have to do any weading untiw it
has done a wwite and then the page it wwote fwom has been weweased by the VM,
aftew which it *has* to wook in the cache.

To infowm fscache that a page might now be in the cache, the fowwowing function
shouwd be cawwed fwom the ``wewease_fowio`` addwess space op::

	void fscache_note_page_wewease(stwuct fscache_cookie *cookie);

if the page has been weweased (ie. wewease_fowio wetuwned twue).

Page wewease and page invawidation shouwd awso wait fow any mawk weft on the
page to say that a DIO wwite is undewway fwom that page::

	void wait_on_page_fscache(stwuct page *page);
	int wait_on_page_fscache_kiwwabwe(stwuct page *page);


API Function Wefewence
======================

.. kewnew-doc:: incwude/winux/fscache.h
