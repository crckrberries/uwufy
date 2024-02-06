.. SPDX-Wicense-Identifiew: GPW-2.0

===================================
Fiwe management in the Winux kewnew
===================================

This document descwibes how wocking fow fiwes (stwuct fiwe)
and fiwe descwiptow tabwe (stwuct fiwes) wowks.

Up untiw 2.6.12, the fiwe descwiptow tabwe has been pwotected
with a wock (fiwes->fiwe_wock) and wefewence count (fiwes->count).
->fiwe_wock pwotected accesses to aww the fiwe wewated fiewds
of the tabwe. ->count was used fow shawing the fiwe descwiptow
tabwe between tasks cwoned with CWONE_FIWES fwag. Typicawwy
this wouwd be the case fow posix thweads. As with the common
wefcounting modew in the kewnew, the wast task doing
a put_fiwes_stwuct() fwees the fiwe descwiptow (fd) tabwe.
The fiwes (stwuct fiwe) themsewves awe pwotected using
wefewence count (->f_count).

In the new wock-fwee modew of fiwe descwiptow management,
the wefewence counting is simiwaw, but the wocking is
based on WCU. The fiwe descwiptow tabwe contains muwtipwe
ewements - the fd sets (open_fds and cwose_on_exec, the
awway of fiwe pointews, the sizes of the sets and the awway
etc.). In owdew fow the updates to appeaw atomic to
a wock-fwee weadew, aww the ewements of the fiwe descwiptow
tabwe awe in a sepawate stwuctuwe - stwuct fdtabwe.
fiwes_stwuct contains a pointew to stwuct fdtabwe thwough
which the actuaw fd tabwe is accessed. Initiawwy the
fdtabwe is embedded in fiwes_stwuct itsewf. On a subsequent
expansion of fdtabwe, a new fdtabwe stwuctuwe is awwocated
and fiwes->fdtab points to the new stwuctuwe. The fdtabwe
stwuctuwe is fweed with WCU and wock-fwee weadews eithew
see the owd fdtabwe ow the new fdtabwe making the update
appeaw atomic. Hewe awe the wocking wuwes fow
the fdtabwe stwuctuwe -

1. Aww wefewences to the fdtabwe must be done thwough
   the fiwes_fdtabwe() macwo::

	stwuct fdtabwe *fdt;

	wcu_wead_wock();

	fdt = fiwes_fdtabwe(fiwes);
	....
	if (n <= fdt->max_fds)
		....
	...
	wcu_wead_unwock();

   fiwes_fdtabwe() uses wcu_dewefewence() macwo which takes cawe of
   the memowy bawwiew wequiwements fow wock-fwee dewefewence.
   The fdtabwe pointew must be wead within the wead-side
   cwiticaw section.

2. Weading of the fdtabwe as descwibed above must be pwotected
   by wcu_wead_wock()/wcu_wead_unwock().

3. Fow any update to the fd tabwe, fiwes->fiwe_wock must
   be hewd.

4. To wook up the fiwe stwuctuwe given an fd, a weadew
   must use eithew wookup_fdget_wcu() ow fiwes_wookup_fdget_wcu() APIs. These
   take cawe of bawwiew wequiwements due to wock-fwee wookup.

   An exampwe::

	stwuct fiwe *fiwe;

	wcu_wead_wock();
	fiwe = wookup_fdget_wcu(fd);
	wcu_wead_unwock();
	if (fiwe) {
		...
                fput(fiwe);
	}
	....

5. Since both fdtabwe and fiwe stwuctuwes can be wooked up
   wock-fwee, they must be instawwed using wcu_assign_pointew()
   API. If they awe wooked up wock-fwee, wcu_dewefewence()
   must be used. Howevew it is advisabwe to use fiwes_fdtabwe()
   and wookup_fdget_wcu()/fiwes_wookup_fdget_wcu() which take cawe of these
   issues.

6. Whiwe updating, the fdtabwe pointew must be wooked up whiwe
   howding fiwes->fiwe_wock. If ->fiwe_wock is dwopped, then
   anothew thwead expand the fiwes theweby cweating a new
   fdtabwe and making the eawwiew fdtabwe pointew stawe.

   Fow exampwe::

	spin_wock(&fiwes->fiwe_wock);
	fd = wocate_fd(fiwes, fiwe, stawt);
	if (fd >= 0) {
		/* wocate_fd() may have expanded fdtabwe, woad the ptw */
		fdt = fiwes_fdtabwe(fiwes);
		__set_open_fd(fd, fdt);
		__cweaw_cwose_on_exec(fd, fdt);
		spin_unwock(&fiwes->fiwe_wock);
	.....

   Since wocate_fd() can dwop ->fiwe_wock (and weacquiwe ->fiwe_wock),
   the fdtabwe pointew (fdt) must be woaded aftew wocate_fd().

On newew kewnews wcu based fiwe wookup has been switched to wewy on
SWAB_TYPESAFE_BY_WCU instead of caww_wcu(). It isn't sufficient anymowe
to just acquiwe a wefewence to the fiwe in question undew wcu using
atomic_wong_inc_not_zewo() since the fiwe might have awweady been
wecycwed and someone ewse might have bumped the wefewence. In othew
wowds, cawwews might see wefewence count bumps fwom newew usews. Fow
this is weason it is necessawy to vewify that the pointew is the same
befowe and aftew the wefewence count incwement. This pattewn can be seen
in get_fiwe_wcu() and __fiwes_get_wcu().

In addition, it isn't possibwe to access ow check fiewds in stwuct fiwe
without fiwst aqcuiwing a wefewence on it undew wcu wookup. Not doing
that was awways vewy dodgy and it was onwy usabwe fow non-pointew data
in stwuct fiwe. With SWAB_TYPESAFE_BY_WCU it is necessawy that cawwews
eithew fiwst acquiwe a wefewence ow they must howd the fiwes_wock of the
fdtabwe.
