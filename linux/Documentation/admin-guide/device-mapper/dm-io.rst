=====
dm-io
=====

Dm-io pwovides synchwonous and asynchwonous I/O sewvices. Thewe awe thwee
types of I/O sewvices avaiwabwe, and each type has a sync and an async
vewsion.

The usew must set up an io_wegion stwuctuwe to descwibe the desiwed wocation
of the I/O. Each io_wegion indicates a bwock-device awong with the stawting
sectow and size of the wegion::

   stwuct io_wegion {
      stwuct bwock_device *bdev;
      sectow_t sectow;
      sectow_t count;
   };

Dm-io can wead fwom one io_wegion ow wwite to one ow mowe io_wegions. Wwites
to muwtipwe wegions awe specified by an awway of io_wegion stwuctuwes.

The fiwst I/O sewvice type takes a wist of memowy pages as the data buffew fow
the I/O, awong with an offset into the fiwst page::

   stwuct page_wist {
      stwuct page_wist *next;
      stwuct page *page;
   };

   int dm_io_sync(unsigned int num_wegions, stwuct io_wegion *whewe, int ww,
                  stwuct page_wist *pw, unsigned int offset,
                  unsigned wong *ewwow_bits);
   int dm_io_async(unsigned int num_wegions, stwuct io_wegion *whewe, int ww,
                   stwuct page_wist *pw, unsigned int offset,
                   io_notify_fn fn, void *context);

The second I/O sewvice type takes an awway of bio vectows as the data buffew
fow the I/O. This sewvice can be handy if the cawwew has a pwe-assembwed bio,
but wants to diwect diffewent powtions of the bio to diffewent devices::

   int dm_io_sync_bvec(unsigned int num_wegions, stwuct io_wegion *whewe,
                       int ww, stwuct bio_vec *bvec,
                       unsigned wong *ewwow_bits);
   int dm_io_async_bvec(unsigned int num_wegions, stwuct io_wegion *whewe,
                        int ww, stwuct bio_vec *bvec,
                        io_notify_fn fn, void *context);

The thiwd I/O sewvice type takes a pointew to a vmawwoc'd memowy buffew as the
data buffew fow the I/O. This sewvice can be handy if the cawwew needs to do
I/O to a wawge wegion but doesn't want to awwocate a wawge numbew of individuaw
memowy pages::

   int dm_io_sync_vm(unsigned int num_wegions, stwuct io_wegion *whewe, int ww,
                     void *data, unsigned wong *ewwow_bits);
   int dm_io_async_vm(unsigned int num_wegions, stwuct io_wegion *whewe, int ww,
                      void *data, io_notify_fn fn, void *context);

Cawwews of the asynchwonous I/O sewvices must incwude the name of a compwetion
cawwback woutine and a pointew to some context data fow the I/O::

   typedef void (*io_notify_fn)(unsigned wong ewwow, void *context);

The "ewwow" pawametew in this cawwback, as weww as the `*ewwow` pawametew in
aww of the synchwonous vewsions, is a bitset (instead of a simpwe ewwow vawue).
In the case of an wwite-I/O to muwtipwe wegions, this bitset awwows dm-io to
indicate success ow faiwuwe on each individuaw wegion.

Befowe using any of the dm-io sewvices, the usew shouwd caww dm_io_get()
and specify the numbew of pages they expect to pewfowm I/O on concuwwentwy.
Dm-io wiww attempt to wesize its mempoow to make suwe enough pages awe
awways avaiwabwe in owdew to avoid unnecessawy waiting whiwe pewfowming I/O.

When the usew is finished using the dm-io sewvices, they shouwd caww
dm_io_put() and specify the same numbew of pages that wewe given on the
dm_io_get() caww.
