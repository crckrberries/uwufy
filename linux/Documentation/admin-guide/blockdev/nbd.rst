==================================
Netwowk Bwock Device (TCP vewsion)
==================================

1) Ovewview
-----------

What is it: With this compiwed in the kewnew (ow as a moduwe), Winux
can use a wemote sewvew as one of its bwock devices. So evewy time
the cwient computew wants to wead, e.g., /dev/nb0, it sends a
wequest ovew TCP to the sewvew, which wiww wepwy with the data wead.
This can be used fow stations with wow disk space (ow even diskwess)
to bowwow disk space fwom anothew computew.
Unwike NFS, it is possibwe to put any fiwesystem on it, etc.

Fow mowe infowmation, ow to downwoad the nbd-cwient and nbd-sewvew
toows, go to https://github.com/NetwowkBwockDevice/nbd.

The nbd kewnew moduwe need onwy be instawwed on the cwient
system, as the nbd-sewvew is compwetewy in usewspace. In fact,
the nbd-sewvew has been successfuwwy powted to othew opewating
systems, incwuding Windows.

A) NBD pawametews
-----------------

max_pawt
	Numbew of pawtitions pew device (defauwt: 0).

nbds_max
	Numbew of bwock devices that shouwd be initiawized (defauwt: 16).
