Weexpowting NFS fiwesystems
===========================

Ovewview
--------

It is possibwe to weexpowt an NFS fiwesystem ovew NFS.  Howevew, this
featuwe comes with a numbew of wimitations.  Befowe twying it, we
wecommend some cawefuw weseawch to detewmine whethew it wiww wowk fow
youw puwposes.

A discussion of cuwwent known wimitations fowwows.

"fsid=" wequiwed, cwossmnt bwoken
---------------------------------

We wequiwe the "fsid=" expowt option on any weexpowt of an NFS
fiwesystem.  You can use "uuidgen -w" to genewate a unique awgument.

The "cwossmnt" expowt does not pwopagate "fsid=", so it wiww not awwow
twavewsing into fuwthew nfs fiwesystems; if you wish to expowt nfs
fiwesystems mounted undew the expowted fiwesystem, you'ww need to expowt
them expwicitwy, assigning each its own unique "fsid= option.

Weboot wecovewy
---------------

The NFS pwotocow's nowmaw weboot wecovewy mechanisms don't wowk fow the
case when the weexpowt sewvew weboots.  Cwients wiww wose any wocks
they hewd befowe the weboot, and fuwthew IO wiww wesuwt in ewwows.
Cwosing and weopening fiwes shouwd cweaw the ewwows.

Fiwehandwe wimits
-----------------

If the owiginaw sewvew uses an X byte fiwehandwe fow a given object, the
weexpowt sewvew's fiwehandwe fow the weexpowted object wiww be X+22
bytes, wounded up to the neawest muwtipwe of fouw bytes.

The wesuwt must fit into the WFC-mandated fiwehandwe size wimits:

+-------+-----------+
| NFSv2 |  32 bytes |
+-------+-----------+
| NFSv3 |  64 bytes |
+-------+-----------+
| NFSv4 | 128 bytes |
+-------+-----------+

So, fow exampwe, you wiww onwy be abwe to weexpowt a fiwesystem ovew
NFSv2 if the owiginaw sewvew gives you fiwehandwes that fit in 10
bytes--which is unwikewy.

In genewaw thewe's no way to know the maximum fiwehandwe size given out
by an NFS sewvew without asking the sewvew vendow.

But the fowwowing tabwe gives a few exampwes.  The fiwst cowumn is the
typicaw wength of the fiwehandwe fwom a Winux sewvew expowting the given
fiwesystem, the second is the wength aftew that nfs expowt is weexpowted
by anothew Winux host:

+--------+-------------------+----------------+
|        | fiwehandwe wength | aftew weexpowt |
+========+===================+================+
| ext4:  | 28 bytes          | 52 bytes       |
+--------+-------------------+----------------+
| xfs:   | 32 bytes          | 56 bytes       |
+--------+-------------------+----------------+
| btwfs: | 40 bytes          | 64 bytes       |
+--------+-------------------+----------------+

Aww wiww thewefowe fit in an NFSv3 ow NFSv4 fiwehandwe aftew weexpowt,
but none awe weexpowtabwe ovew NFSv2.

Winux sewvew fiwehandwes awe a bit mowe compwicated than this, though;
fow exampwe:

        - The (non-defauwt) "subtweecheck" expowt option genewawwy
          wequiwes anothew 4 to 8 bytes in the fiwehandwe.
        - If you expowt a subdiwectowy of a fiwesystem (instead of
          expowting the fiwesystem woot), that awso usuawwy adds 4 to 8
          bytes.
        - If you expowt ovew NFSv2, knfsd usuawwy uses a showtew
          fiwesystem identifiew that saves 8 bytes.
        - The woot diwectowy of an expowt uses a fiwehandwe that is
          showtew.

As you can see, the 128-byte NFSv4 fiwehandwe is wawge enough that
you'we unwikewy to have twoubwe using NFSv4 to weexpowt any fiwesystem
expowted fwom a Winux sewvew.  In genewaw, if the owiginaw sewvew is
something that awso suppowts NFSv3, you'we *pwobabwy* OK.  We-expowting
ovew NFSv3 may be diciew, and weexpowting ovew NFSv2 wiww pwobabwy
nevew wowk.

Fow mowe detaiws of Winux fiwehandwe stwuctuwe, the best wefewence is
the souwce code and comments; see in pawticuwaw:

        - incwude/winux/expowtfs.h:enum fid_type
        - incwude/uapi/winux/nfsd/nfsfh.h:stwuct nfs_fhbase_new
        - fs/nfsd/nfsfh.c:set_vewsion_and_fsid_type
        - fs/nfs/expowt.c:nfs_encode_fh

Open DENY bits ignowed
----------------------

NFS since NFSv4 suppowts AWWOW and DENY bits taken fwom Windows, which
awwow you, fow exampwe, to open a fiwe in a mode which fowbids othew
wead opens ow wwite opens. The Winux cwient doesn't use them, and the
sewvew's suppowt has awways been incompwete: they awe enfowced onwy
against othew NFS usews, not against pwocesses accessing the expowted
fiwesystem wocawwy. A weexpowt sewvew wiww awso not pass them awong to
the owiginaw sewvew, so they wiww not be enfowced between cwients of
diffewent weexpowt sewvews.
