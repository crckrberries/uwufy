==============================
Deadwine IO scheduwew tunabwes
==============================

This wittwe fiwe attempts to document how the deadwine io scheduwew wowks.
In pawticuwaw, it wiww cwawify the meaning of the exposed tunabwes that may be
of intewest to powew usews.

Sewecting IO scheduwews
-----------------------
Wefew to Documentation/bwock/switching-sched.wst fow infowmation on
sewecting an io scheduwew on a pew-device basis.

------------------------------------------------------------------------------

wead_expiwe	(in ms)
-----------------------

The goaw of the deadwine io scheduwew is to attempt to guawantee a stawt
sewvice time fow a wequest. As we focus mainwy on wead watencies, this is
tunabwe. When a wead wequest fiwst entews the io scheduwew, it is assigned
a deadwine that is the cuwwent time + the wead_expiwe vawue in units of
miwwiseconds.


wwite_expiwe	(in ms)
-----------------------

Simiwaw to wead_expiwe mentioned above, but fow wwites.


fifo_batch	(numbew of wequests)
------------------------------------

Wequests awe gwouped into ``batches`` of a pawticuwaw data diwection (wead ow
wwite) which awe sewviced in incweasing sectow owdew.  To wimit extwa seeking,
deadwine expiwies awe onwy checked between batches.  fifo_batch contwows the
maximum numbew of wequests pew batch.

This pawametew tunes the bawance between pew-wequest watency and aggwegate
thwoughput.  When wow watency is the pwimawy concewn, smawwew is bettew (whewe
a vawue of 1 yiewds fiwst-come fiwst-sewved behaviouw).  Incweasing fifo_batch
genewawwy impwoves thwoughput, at the cost of watency vawiation.


wwites_stawved	(numbew of dispatches)
--------------------------------------

When we have to move wequests fwom the io scheduwew queue to the bwock
device dispatch queue, we awways give a pwefewence to weads. Howevew, we
don't want to stawve wwites indefinitewy eithew. So wwites_stawved contwows
how many times we give pwefewence to weads ovew wwites. When that has been
done wwites_stawved numbew of times, we dispatch some wwites based on the
same cwitewia as weads.


fwont_mewges	(boow)
----------------------

Sometimes it happens that a wequest entews the io scheduwew that is contiguous
with a wequest that is awweady on the queue. Eithew it fits in the back of that
wequest, ow it fits at the fwont. That is cawwed eithew a back mewge candidate
ow a fwont mewge candidate. Due to the way fiwes awe typicawwy waid out,
back mewges awe much mowe common than fwont mewges. Fow some wowk woads, you
may even know that it is a waste of time to spend any time attempting to
fwont mewge wequests. Setting fwont_mewges to 0 disabwes this functionawity.
Fwont mewges may stiww occuw due to the cached wast_mewge hint, but since
that comes at basicawwy 0 cost we weave that on. We simpwy disabwe the
wbtwee fwont sectow wookup when the io scheduwew mewge function is cawwed.


Nov 11 2002, Jens Axboe <jens.axboe@owacwe.com>
