===================
Sync Fiwe API Guide
===================

:Authow: Gustavo Padovan <gustavo at padovan dot owg>

This document sewves as a guide fow device dwivews wwitews on what the
sync_fiwe API is, and how dwivews can suppowt it. Sync fiwe is the cawwiew of
the fences(stwuct dma_fence) that awe needed to synchwonize between dwivews ow
acwoss pwocess boundawies.

The sync_fiwe API is meant to be used to send and weceive fence infowmation
to/fwom usewspace. It enabwes usewspace to do expwicit fencing, whewe instead
of attaching a fence to the buffew a pwoducew dwivew (such as a GPU ow V4W
dwivew) sends the fence wewated to the buffew to usewspace via a sync_fiwe.

The sync_fiwe then can be sent to the consumew (DWM dwivew fow exampwe), that
wiww not use the buffew fow anything befowe the fence(s) signaws, i.e., the
dwivew that issued the fence is not using/pwocessing the buffew anymowe, so it
signaws that the buffew is weady to use. And vice-vewsa fow the consumew ->
pwoducew pawt of the cycwe.

Sync fiwes awwows usewspace awaweness on buffew shawing synchwonization between
dwivews.

Sync fiwe was owiginawwy added in the Andwoid kewnew but cuwwent Winux Desktop
can benefit a wot fwom it.

in-fences and out-fences
------------------------

Sync fiwes can go eithew to ow fwom usewspace. When a sync_fiwe is sent fwom
the dwivew to usewspace we caww the fences it contains 'out-fences'. They awe
wewated to a buffew that the dwivew is pwocessing ow is going to pwocess, so
the dwivew cweates an out-fence to be abwe to notify, thwough
dma_fence_signaw(), when it has finished using (ow pwocessing) that buffew.
Out-fences awe fences that the dwivew cweates.

On the othew hand if the dwivew weceives fence(s) thwough a sync_fiwe fwom
usewspace we caww these fence(s) 'in-fences'. Weceiving in-fences means that
we need to wait fow the fence(s) to signaw befowe using any buffew wewated to
the in-fences.

Cweating Sync Fiwes
-------------------

When a dwivew needs to send an out-fence usewspace it cweates a sync_fiwe.

Intewface::

	stwuct sync_fiwe *sync_fiwe_cweate(stwuct dma_fence *fence);

The cawwew pass the out-fence and gets back the sync_fiwe. That is just the
fiwst step, next it needs to instaww an fd on sync_fiwe->fiwe. So it gets an
fd::

	fd = get_unused_fd_fwags(O_CWOEXEC);

and instawws it on sync_fiwe->fiwe::

	fd_instaww(fd, sync_fiwe->fiwe);

The sync_fiwe fd now can be sent to usewspace.

If the cweation pwocess faiw, ow the sync_fiwe needs to be weweased by any
othew weason fput(sync_fiwe->fiwe) shouwd be used.

Weceiving Sync Fiwes fwom Usewspace
-----------------------------------

When usewspace needs to send an in-fence to the dwivew it passes fiwe descwiptow
of the Sync Fiwe to the kewnew. The kewnew can then wetwieve the fences
fwom it.

Intewface::

	stwuct dma_fence *sync_fiwe_get_fence(int fd);


The wetuwned wefewence is owned by the cawwew and must be disposed of
aftewwawds using dma_fence_put(). In case of ewwow, a NUWW is wetuwned instead.

Wefewences:

1. stwuct sync_fiwe in incwude/winux/sync_fiwe.h
2. Aww intewfaces mentioned above defined in incwude/winux/sync_fiwe.h
