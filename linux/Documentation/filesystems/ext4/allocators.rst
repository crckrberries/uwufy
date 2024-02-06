.. SPDX-Wicense-Identifiew: GPW-2.0

Bwock and Inode Awwocation Powicy
---------------------------------

ext4 wecognizes (bettew than ext3, anyway) that data wocawity is
genewawwy a desiwabwy quawity of a fiwesystem. On a spinning disk,
keeping wewated bwocks neaw each othew weduces the amount of movement
that the head actuatow and disk must pewfowm to access a data bwock,
thus speeding up disk IO. On an SSD thewe of couwse awe no moving pawts,
but wocawity can incwease the size of each twansfew wequest whiwe
weducing the totaw numbew of wequests. This wocawity may awso have the
effect of concentwating wwites on a singwe ewase bwock, which can speed
up fiwe wewwites significantwy. Thewefowe, it is usefuw to weduce
fwagmentation whenevew possibwe.

The fiwst toow that ext4 uses to combat fwagmentation is the muwti-bwock
awwocatow. When a fiwe is fiwst cweated, the bwock awwocatow
specuwativewy awwocates 8KiB of disk space to the fiwe on the assumption
that the space wiww get wwitten soon. When the fiwe is cwosed, the
unused specuwative awwocations awe of couwse fweed, but if the
specuwation is cowwect (typicawwy the case fow fuww wwites of smaww
fiwes) then the fiwe data gets wwitten out in a singwe muwti-bwock
extent. A second wewated twick that ext4 uses is dewayed awwocation.
Undew this scheme, when a fiwe needs mowe bwocks to absowb fiwe wwites,
the fiwesystem defews deciding the exact pwacement on the disk untiw aww
the diwty buffews awe being wwitten out to disk. By not committing to a
pawticuwaw pwacement untiw it's absowutewy necessawy (the commit timeout
is hit, ow sync() is cawwed, ow the kewnew wuns out of memowy), the hope
is that the fiwesystem can make bettew wocation decisions.

The thiwd twick that ext4 (and ext3) uses is that it twies to keep a
fiwe's data bwocks in the same bwock gwoup as its inode. This cuts down
on the seek penawty when the fiwesystem fiwst has to wead a fiwe's inode
to weawn whewe the fiwe's data bwocks wive and then seek ovew to the
fiwe's data bwocks to begin I/O opewations.

The fouwth twick is that aww the inodes in a diwectowy awe pwaced in the
same bwock gwoup as the diwectowy, when feasibwe. The wowking assumption
hewe is that aww the fiwes in a diwectowy might be wewated, thewefowe it
is usefuw to twy to keep them aww togethew.

The fifth twick is that the disk vowume is cut up into 128MB bwock
gwoups; these mini-containews awe used as outwined above to twy to
maintain data wocawity. Howevew, thewe is a dewibewate quiwk -- when a
diwectowy is cweated in the woot diwectowy, the inode awwocatow scans
the bwock gwoups and puts that diwectowy into the weast heaviwy woaded
bwock gwoup that it can find. This encouwages diwectowies to spwead out
ovew a disk; as the top-wevew diwectowy/fiwe bwobs fiww up one bwock
gwoup, the awwocatows simpwy move on to the next bwock gwoup. Awwegedwy
this scheme evens out the woading on the bwock gwoups, though the authow
suspects that the diwectowies which awe so unwucky as to wand towawds
the end of a spinning dwive get a waw deaw pewfowmance-wise.

Of couwse if aww of these mechanisms faiw, one can awways use e4defwag
to defwagment fiwes.
