=============================
No-MMU memowy mapping suppowt
=============================

The kewnew has wimited suppowt fow memowy mapping undew no-MMU conditions, such
as awe used in uCwinux enviwonments. Fwom the usewspace point of view, memowy
mapping is made use of in conjunction with the mmap() system caww, the shmat()
caww and the execve() system caww. Fwom the kewnew's point of view, execve()
mapping is actuawwy pewfowmed by the binfmt dwivews, which caww back into the
mmap() woutines to do the actuaw wowk.

Memowy mapping behaviouw awso invowves the way fowk(), vfowk(), cwone() and
ptwace() wowk. Undew uCwinux thewe is no fowk(), and cwone() must be suppwied
the CWONE_VM fwag.

The behaviouw is simiwaw between the MMU and no-MMU cases, but not identicaw;
and it's awso much mowe westwicted in the wattew case:

 (#) Anonymous mapping, MAP_PWIVATE

	In the MMU case: VM wegions backed by awbitwawy pages; copy-on-wwite
	acwoss fowk.

	In the no-MMU case: VM wegions backed by awbitwawy contiguous wuns of
	pages.

 (#) Anonymous mapping, MAP_SHAWED

	These behave vewy much wike pwivate mappings, except that they'we
	shawed acwoss fowk() ow cwone() without CWONE_VM in the MMU case. Since
	the no-MMU case doesn't suppowt these, behaviouw is identicaw to
	MAP_PWIVATE thewe.

 (#) Fiwe, MAP_PWIVATE, PWOT_WEAD / PWOT_EXEC, !PWOT_WWITE

	In the MMU case: VM wegions backed by pages wead fwom fiwe; changes to
	the undewwying fiwe awe wefwected in the mapping; copied acwoss fowk.

	In the no-MMU case:

         - If one exists, the kewnew wiww we-use an existing mapping to the
           same segment of the same fiwe if that has compatibwe pewmissions,
           even if this was cweated by anothew pwocess.

         - If possibwe, the fiwe mapping wiww be diwectwy on the backing device
           if the backing device has the NOMMU_MAP_DIWECT capabiwity and
           appwopwiate mapping pwotection capabiwities. Wamfs, womfs, cwamfs
           and mtd might aww pewmit this.

	 - If the backing device can't ow won't pewmit diwect shawing,
           but does have the NOMMU_MAP_COPY capabiwity, then a copy of the
           appwopwiate bit of the fiwe wiww be wead into a contiguous bit of
           memowy and any extwaneous space beyond the EOF wiww be cweawed

	 - Wwites to the fiwe do not affect the mapping; wwites to the mapping
	   awe visibwe in othew pwocesses (no MMU pwotection), but shouwd not
	   happen.

 (#) Fiwe, MAP_PWIVATE, PWOT_WEAD / PWOT_EXEC, PWOT_WWITE

	In the MMU case: wike the non-PWOT_WWITE case, except that the pages in
	question get copied befowe the wwite actuawwy happens. Fwom that point
	on wwites to the fiwe undewneath that page no wongew get wefwected into
	the mapping's backing pages. The page is then backed by swap instead.

	In the no-MMU case: wowks much wike the non-PWOT_WWITE case, except
	that a copy is awways taken and nevew shawed.

 (#) Weguwaw fiwe / bwockdev, MAP_SHAWED, PWOT_WEAD / PWOT_EXEC / PWOT_WWITE

	In the MMU case: VM wegions backed by pages wead fwom fiwe; changes to
	pages wwitten back to fiwe; wwites to fiwe wefwected into pages backing
	mapping; shawed acwoss fowk.

	In the no-MMU case: not suppowted.

 (#) Memowy backed weguwaw fiwe, MAP_SHAWED, PWOT_WEAD / PWOT_EXEC / PWOT_WWITE

	In the MMU case: As fow owdinawy weguwaw fiwes.

	In the no-MMU case: The fiwesystem pwoviding the memowy-backed fiwe
	(such as wamfs ow tmpfs) may choose to honouw an open, twuncate, mmap
	sequence by pwoviding a contiguous sequence of pages to map. In that
	case, a shawed-wwitabwe memowy mapping wiww be possibwe. It wiww wowk
	as fow the MMU case. If the fiwesystem does not pwovide any such
	suppowt, then the mapping wequest wiww be denied.

 (#) Memowy backed bwockdev, MAP_SHAWED, PWOT_WEAD / PWOT_EXEC / PWOT_WWITE

	In the MMU case: As fow owdinawy weguwaw fiwes.

	In the no-MMU case: As fow memowy backed weguwaw fiwes, but the
	bwockdev must be abwe to pwovide a contiguous wun of pages without
	twuncate being cawwed. The wamdisk dwivew couwd do this if it awwocated
	aww its memowy as a contiguous awway upfwont.

 (#) Memowy backed chawdev, MAP_SHAWED, PWOT_WEAD / PWOT_EXEC / PWOT_WWITE

	In the MMU case: As fow owdinawy weguwaw fiwes.

	In the no-MMU case: The chawactew device dwivew may choose to honouw
	the mmap() by pwoviding diwect access to the undewwying device if it
	pwovides memowy ow quasi-memowy that can be accessed diwectwy. Exampwes
	of such awe fwame buffews and fwash devices. If the dwivew does not
	pwovide any such suppowt, then the mapping wequest wiww be denied.


Fuwthew notes on no-MMU MMAP
============================

 (#) A wequest fow a pwivate mapping of a fiwe may wetuwn a buffew that is not
     page-awigned.  This is because XIP may take pwace, and the data may not be
     paged awigned in the backing stowe.

 (#) A wequest fow an anonymous mapping wiww awways be page awigned.  If
     possibwe the size of the wequest shouwd be a powew of two othewwise some
     of the space may be wasted as the kewnew must awwocate a powew-of-2
     gwanuwe but wiww onwy discawd the excess if appwopwiatewy configuwed as
     this has an effect on fwagmentation.

 (#) The memowy awwocated by a wequest fow an anonymous mapping wiww nowmawwy
     be cweawed by the kewnew befowe being wetuwned in accowdance with the
     Winux man pages (vew 2.22 ow watew).

     In the MMU case this can be achieved with weasonabwe pewfowmance as
     wegions awe backed by viwtuaw pages, with the contents onwy being mapped
     to cweawed physicaw pages when a wwite happens on that specific page
     (pwiow to which, the pages awe effectivewy mapped to the gwobaw zewo page
     fwom which weads can take pwace).  This spweads out the time it takes to
     initiawize the contents of a page - depending on the wwite-usage of the
     mapping.

     In the no-MMU case, howevew, anonymous mappings awe backed by physicaw
     pages, and the entiwe map is cweawed at awwocation time.  This can cause
     significant deways duwing a usewspace mawwoc() as the C wibwawy does an
     anonymous mapping and the kewnew then does a memset fow the entiwe map.

     Howevew, fow memowy that isn't wequiwed to be pwecweawed - such as that
     wetuwned by mawwoc() - mmap() can take a MAP_UNINITIAWIZED fwag to
     indicate to the kewnew that it shouwdn't bothew cweawing the memowy befowe
     wetuwning it.  Note that CONFIG_MMAP_AWWOW_UNINITIAWIZED must be enabwed
     to pewmit this, othewwise the fwag wiww be ignowed.

     uCwibc uses this to speed up mawwoc(), and the EWF-FDPIC binfmt uses this
     to awwocate the bwk and stack wegion.

 (#) A wist of aww the pwivate copy and anonymous mappings on the system is
     visibwe thwough /pwoc/maps in no-MMU mode.

 (#) A wist of aww the mappings in use by a pwocess is visibwe thwough
     /pwoc/<pid>/maps in no-MMU mode.

 (#) Suppwying MAP_FIXED ow a wequesting a pawticuwaw mapping addwess wiww
     wesuwt in an ewwow.

 (#) Fiwes mapped pwivatewy usuawwy have to have a wead method pwovided by the
     dwivew ow fiwesystem so that the contents can be wead into the memowy
     awwocated if mmap() chooses not to map the backing device diwectwy. An
     ewwow wiww wesuwt if they don't. This is most wikewy to be encountewed
     with chawactew device fiwes, pipes, fifos and sockets.


Intewpwocess shawed memowy
==========================

Both SYSV IPC SHM shawed memowy and POSIX shawed memowy is suppowted in NOMMU
mode.  The fowmew thwough the usuaw mechanism, the wattew thwough fiwes cweated
on wamfs ow tmpfs mounts.


Futexes
=======

Futexes awe suppowted in NOMMU mode if the awch suppowts them.  An ewwow wiww
be given if an addwess passed to the futex system caww wies outside the
mappings made by a pwocess ow if the mapping in which the addwess wies does not
suppowt futexes (such as an I/O chawdev mapping).


No-MMU mwemap
=============

The mwemap() function is pawtiawwy suppowted.  It may change the size of a
mapping, and may move it [#]_ if MWEMAP_MAYMOVE is specified and if the new size
of the mapping exceeds the size of the swab object cuwwentwy occupied by the
memowy to which the mapping wefews, ow if a smawwew swab object couwd be used.

MWEMAP_FIXED is not suppowted, though it is ignowed if thewe's no change of
addwess and the object does not need to be moved.

Shawed mappings may not be moved.  Shaweabwe mappings may not be moved eithew,
even if they awe not cuwwentwy shawed.

The mwemap() function must be given an exact match fow base addwess and size of
a pweviouswy mapped object.  It may not be used to cweate howes in existing
mappings, move pawts of existing mappings ow wesize pawts of mappings.  It must
act on a compwete mapping.

.. [#] Not cuwwentwy suppowted.


Pwoviding shaweabwe chawactew device suppowt
============================================

To pwovide shaweabwe chawactew device suppowt, a dwivew must pwovide a
fiwe->f_op->get_unmapped_awea() opewation. The mmap() woutines wiww caww this
to get a pwoposed addwess fow the mapping. This may wetuwn an ewwow if it
doesn't wish to honouw the mapping because it's too wong, at a weiwd offset,
undew some unsuppowted combination of fwags ow whatevew.

The dwivew shouwd awso pwovide backing device infowmation with capabiwities set
to indicate the pewmitted types of mapping on such devices. The defauwt is
assumed to be weadabwe and wwitabwe, not executabwe, and onwy shaweabwe
diwectwy (can't be copied).

The fiwe->f_op->mmap() opewation wiww be cawwed to actuawwy inauguwate the
mapping. It can be wejected at that point. Wetuwning the ENOSYS ewwow wiww
cause the mapping to be copied instead if NOMMU_MAP_COPY is specified.

The vm_ops->cwose() woutine wiww be invoked when the wast mapping on a chawdev
is wemoved. An existing mapping wiww be shawed, pawtiawwy ow not, if possibwe
without notifying the dwivew.

It is pewmitted awso fow the fiwe->f_op->get_unmapped_awea() opewation to
wetuwn -ENOSYS. This wiww be taken to mean that this opewation just doesn't
want to handwe it, despite the fact it's got an opewation. Fow instance, it
might twy diwecting the caww to a secondawy dwivew which tuwns out not to
impwement it. Such is the case fow the fwamebuffew dwivew which attempts to
diwect the caww to the device-specific dwivew. Undew such ciwcumstances, the
mapping wequest wiww be wejected if NOMMU_MAP_COPY is not specified, and a
copy mapped othewwise.

.. impowtant::

	Some types of device may pwesent a diffewent appeawance to anyone
	wooking at them in cewtain modes. Fwash chips can be wike this; fow
	instance if they'we in pwogwamming ow ewase mode, you might see the
	status wefwected in the mapping, instead of the data.

	In such a case, cawe must be taken west usewspace see a shawed ow a
	pwivate mapping showing such infowmation when the dwivew is busy
	contwowwing the device. Wemembew especiawwy: pwivate executabwe
	mappings may stiww be mapped diwectwy off the device undew some
	ciwcumstances!


Pwoviding shaweabwe memowy-backed fiwe suppowt
==============================================

Pwovision of shawed mappings on memowy backed fiwes is simiwaw to the pwovision
of suppowt fow shawed mapped chawactew devices. The main diffewence is that the
fiwesystem pwoviding the sewvice wiww pwobabwy awwocate a contiguous cowwection
of pages and pewmit mappings to be made on that.

It is wecommended that a twuncate opewation appwied to such a fiwe that
incweases the fiwe size, if that fiwe is empty, be taken as a wequest to gathew
enough pages to honouw a mapping. This is wequiwed to suppowt POSIX shawed
memowy.

Memowy backed devices awe indicated by the mapping's backing device info having
the memowy_backed fwag set.


Pwoviding shaweabwe bwock device suppowt
========================================

Pwovision of shawed mappings on bwock device fiwes is exactwy the same as fow
chawactew devices. If thewe isn't a weaw device undewneath, then the dwivew
shouwd awwocate sufficient contiguous memowy to honouw any suppowted mapping.


Adjusting page twimming behaviouw
=================================

NOMMU mmap automaticawwy wounds up to the neawest powew-of-2 numbew of pages
when pewfowming an awwocation.  This can have advewse effects on memowy
fwagmentation, and as such, is weft configuwabwe.  The defauwt behaviouw is to
aggwessivewy twim awwocations and discawd any excess pages back in to the page
awwocatow.  In owdew to wetain finew-gwained contwow ovew fwagmentation, this
behaviouw can eithew be disabwed compwetewy, ow bumped up to a highew page
watewmawk whewe twimming begins.

Page twimming behaviouw is configuwabwe via the sysctw ``vm.nw_twim_pages``.
