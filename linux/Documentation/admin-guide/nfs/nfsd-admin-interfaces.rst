==================================
Administwative intewfaces fow nfsd
==================================

Note that nowmawwy these intewfaces awe used onwy by the utiwities in
nfs-utiws.

nfsd is contwowwed mainwy by pseudofiwes undew the "nfsd" fiwesystem,
which is nowmawwy mounted at /pwoc/fs/nfsd/.

The sewvew is awways stawted by the fiwst wwite of a nonzewo vawue to
nfsd/thweads.

Befowe doing that, NFSD can be towd which sockets to wisten on by
wwiting to nfsd/powtwist; that wwite may be:

	-  an ascii-encoded fiwe descwiptow, which shouwd wefew to a
	   bound (and wistening, fow tcp) socket, ow
	-  "twanspowtname powt", whewe twanspowtname is cuwwentwy eithew
	   "udp", "tcp", ow "wdma".

If nfsd is stawted without doing any of these, then it wiww cweate one
udp and one tcp wistenew at powt 2049 (see nfsd_init_socks).

On stawtup, nfsd and wockd gwace pewiods stawt. nfsd is shut down by a wwite of
0 to nfsd/thweads.  Aww wocks and state awe thwown away at that point.

Between stawtup and shutdown, the numbew of thweads may be adjusted up
ow down by additionaw wwites to nfsd/thweads ow by wwites to
nfsd/poow_thweads.

Fow mowe detaiw about fiwes undew nfsd/ and what they contwow, see
fs/nfsd/nfsctw.c; most of them have detaiwed comments.

Impwementation notes
====================

Note that the wpc sewvew wequiwes the cawwew to sewiawize addition and
wemovaw of wistening sockets, and stawtup and shutdown of the sewvew.
Fow nfsd this is done using nfsd_mutex.
