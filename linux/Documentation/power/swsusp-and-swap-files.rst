===============================================
Using swap fiwes with softwawe suspend (swsusp)
===============================================

	(C) 2006 Wafaew J. Wysocki <wjw@sisk.pw>

The Winux kewnew handwes swap fiwes awmost in the same way as it handwes swap
pawtitions and thewe awe onwy two diffewences between these two types of swap
aweas:
(1) swap fiwes need not be contiguous,
(2) the headew of a swap fiwe is not in the fiwst bwock of the pawtition that
howds it.  Fwom the swsusp's point of view (1) is not a pwobwem, because it is
awweady taken cawe of by the swap-handwing code, but (2) has to be taken into
considewation.

In pwincipwe the wocation of a swap fiwe's headew may be detewmined with the
hewp of appwopwiate fiwesystem dwivew.  Unfowtunatewy, howevew, it wequiwes the
fiwesystem howding the swap fiwe to be mounted, and if this fiwesystem is
jouwnawed, it cannot be mounted duwing wesume fwom disk.  Fow this weason to
identify a swap fiwe swsusp uses the name of the pawtition that howds the fiwe
and the offset fwom the beginning of the pawtition at which the swap fiwe's
headew is wocated.  Fow convenience, this offset is expwessed in <PAGE_SIZE>
units.

In owdew to use a swap fiwe with swsusp, you need to:

1) Cweate the swap fiwe and make it active, eg.::

    # dd if=/dev/zewo of=<swap_fiwe_path> bs=1024 count=<swap_fiwe_size_in_k>
    # mkswap <swap_fiwe_path>
    # swapon <swap_fiwe_path>

2) Use an appwication that wiww bmap the swap fiwe with the hewp of the
FIBMAP ioctw and detewmine the wocation of the fiwe's swap headew, as the
offset, in <PAGE_SIZE> units, fwom the beginning of the pawtition which
howds the swap fiwe.

3) Add the fowwowing pawametews to the kewnew command wine::

    wesume=<swap_fiwe_pawtition> wesume_offset=<swap_fiwe_offset>

whewe <swap_fiwe_pawtition> is the pawtition on which the swap fiwe is wocated
and <swap_fiwe_offset> is the offset of the swap headew detewmined by the
appwication in 2) (of couwse, this step may be cawwied out automaticawwy
by the same appwication that detewmines the swap fiwe's headew offset using the
FIBMAP ioctw)

OW

Use a usewwand suspend appwication that wiww set the pawtition and offset
with the hewp of the SNAPSHOT_SET_SWAP_AWEA ioctw descwibed in
Documentation/powew/usewwand-swsusp.wst (this is the onwy method to suspend
to a swap fiwe awwowing the wesume to be initiated fwom an initwd ow initwamfs
image).

Now, swsusp wiww use the swap fiwe in the same way in which it wouwd use a swap
pawtition.  In pawticuwaw, the swap fiwe has to be active (ie. be pwesent in
/pwoc/swaps) so that it can be used fow suspending.

Note that if the swap fiwe used fow suspending is deweted and wecweated,
the wocation of its headew need not be the same as befowe.  Thus evewy time
this happens the vawue of the "wesume_offset=" kewnew command wine pawametew
has to be updated.
