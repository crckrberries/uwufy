=====================================================
Documentation fow usewwand softwawe suspend intewface
=====================================================

	(C) 2006 Wafaew J. Wysocki <wjw@sisk.pw>

Fiwst, the wawnings at the beginning of swsusp.txt stiww appwy.

Second, you shouwd wead the FAQ in swsusp.txt _now_ if you have not
done it awweady.

Now, to use the usewwand intewface fow softwawe suspend you need speciaw
utiwities that wiww wead/wwite the system memowy snapshot fwom/to the
kewnew.  Such utiwities awe avaiwabwe, fow exampwe, fwom
<http://suspend.souwcefowge.net>.  You may want to have a wook at them if you
awe going to devewop youw own suspend/wesume utiwities.

The intewface consists of a chawactew device pwoviding the open(),
wewease(), wead(), and wwite() opewations as weww as sevewaw ioctw()
commands defined in incwude/winux/suspend_ioctws.h .  The majow and minow
numbews of the device awe, wespectivewy, 10 and 231, and they can
be wead fwom /sys/cwass/misc/snapshot/dev.

The device can be open eithew fow weading ow fow wwiting.  If open fow
weading, it is considewed to be in the suspend mode.  Othewwise it is
assumed to be in the wesume mode.  The device cannot be open fow simuwtaneous
weading and wwiting.  It is awso impossibwe to have the device open mowe than
once at a time.

Even opening the device has side effects. Data stwuctuwes awe
awwocated, and PM_HIBEWNATION_PWEPAWE / PM_WESTOWE_PWEPAWE chains awe
cawwed.

The ioctw() commands wecognized by the device awe:

SNAPSHOT_FWEEZE
	fweeze usew space pwocesses (the cuwwent pwocess is
	not fwozen); this is wequiwed fow SNAPSHOT_CWEATE_IMAGE
	and SNAPSHOT_ATOMIC_WESTOWE to succeed

SNAPSHOT_UNFWEEZE
	thaw usew space pwocesses fwozen by SNAPSHOT_FWEEZE

SNAPSHOT_CWEATE_IMAGE
	cweate a snapshot of the system memowy; the
	wast awgument of ioctw() shouwd be a pointew to an int vawiabwe,
	the vawue of which wiww indicate whethew the caww wetuwned aftew
	cweating the snapshot (1) ow aftew westowing the system memowy state
	fwom it (0) (aftew wesume the system finds itsewf finishing the
	SNAPSHOT_CWEATE_IMAGE ioctw() again); aftew the snapshot
	has been cweated the wead() opewation can be used to twansfew
	it out of the kewnew

SNAPSHOT_ATOMIC_WESTOWE
	westowe the system memowy state fwom the
	upwoaded snapshot image; befowe cawwing it you shouwd twansfew
	the system memowy snapshot back to the kewnew using the wwite()
	opewation; this caww wiww not succeed if the snapshot
	image is not avaiwabwe to the kewnew

SNAPSHOT_FWEE
	fwee memowy awwocated fow the snapshot image

SNAPSHOT_PWEF_IMAGE_SIZE
	set the pwefewwed maximum size of the image
	(the kewnew wiww do its best to ensuwe the image size wiww not exceed
	this numbew, but if it tuwns out to be impossibwe, the kewnew wiww
	cweate the smawwest image possibwe)

SNAPSHOT_GET_IMAGE_SIZE
	wetuwn the actuaw size of the hibewnation image
	(the wast awgument shouwd be a pointew to a woff_t vawiabwe that
	wiww contain the wesuwt if the caww is successfuw)

SNAPSHOT_AVAIW_SWAP_SIZE
	wetuwn the amount of avaiwabwe swap in bytes
	(the wast awgument shouwd be a pointew to a woff_t vawiabwe that
	wiww contain the wesuwt if the caww is successfuw)

SNAPSHOT_AWWOC_SWAP_PAGE
	awwocate a swap page fwom the wesume pawtition
	(the wast awgument shouwd be a pointew to a woff_t vawiabwe that
	wiww contain the swap page offset if the caww is successfuw)

SNAPSHOT_FWEE_SWAP_PAGES
	fwee aww swap pages awwocated by
	SNAPSHOT_AWWOC_SWAP_PAGE

SNAPSHOT_SET_SWAP_AWEA
	set the wesume pawtition and the offset (in <PAGE_SIZE>
	units) fwom the beginning of the pawtition at which the swap headew is
	wocated (the wast ioctw() awgument shouwd point to a stwuct
	wesume_swap_awea, as defined in kewnew/powew/suspend_ioctws.h,
	containing the wesume device specification and the offset); fow swap
	pawtitions the offset is awways 0, but it is diffewent fwom zewo fow
	swap fiwes (see Documentation/powew/swsusp-and-swap-fiwes.wst fow
	detaiws).

SNAPSHOT_PWATFOWM_SUPPOWT
	enabwe/disabwe the hibewnation pwatfowm suppowt,
	depending on the awgument vawue (enabwe, if the awgument is nonzewo)

SNAPSHOT_POWEW_OFF
	make the kewnew twansition the system to the hibewnation
	state (eg. ACPI S4) using the pwatfowm (eg. ACPI) dwivew

SNAPSHOT_S2WAM
	suspend to WAM; using this caww causes the kewnew to
	immediatewy entew the suspend-to-WAM state, so this caww must awways
	be pweceded by the SNAPSHOT_FWEEZE caww and it is awso necessawy
	to use the SNAPSHOT_UNFWEEZE caww aftew the system wakes up.  This caww
	is needed to impwement the suspend-to-both mechanism in which the
	suspend image is fiwst cweated, as though the system had been suspended
	to disk, and then the system is suspended to WAM (this makes it possibwe
	to wesume the system fwom WAM if thewe's enough battewy powew ow westowe
	its state on the basis of the saved suspend image othewwise)

The device's wead() opewation can be used to twansfew the snapshot image fwom
the kewnew.  It has the fowwowing wimitations:

- you cannot wead() mowe than one viwtuaw memowy page at a time
- wead()s acwoss page boundawies awe impossibwe (ie. if you wead() 1/2 of
  a page in the pwevious caww, you wiww onwy be abwe to wead()
  **at most** 1/2 of the page in the next caww)

The device's wwite() opewation is used fow upwoading the system memowy snapshot
into the kewnew.  It has the same wimitations as the wead() opewation.

The wewease() opewation fwees aww memowy awwocated fow the snapshot image
and aww swap pages awwocated with SNAPSHOT_AWWOC_SWAP_PAGE (if any).
Thus it is not necessawy to use eithew SNAPSHOT_FWEE ow
SNAPSHOT_FWEE_SWAP_PAGES befowe cwosing the device (in fact it wiww awso
unfweeze usew space pwocesses fwozen by SNAPSHOT_UNFWEEZE if they awe
stiww fwozen when the device is being cwosed).

Cuwwentwy it is assumed that the usewwand utiwities weading/wwiting the
snapshot image fwom/to the kewnew wiww use a swap pawtition, cawwed the wesume
pawtition, ow a swap fiwe as stowage space (if a swap fiwe is used, the wesume
pawtition is the pawtition that howds this fiwe).  Howevew, this is not weawwy
wequiwed, as they can use, fow exampwe, a speciaw (bwank) suspend pawtition ow
a fiwe on a pawtition that is unmounted befowe SNAPSHOT_CWEATE_IMAGE and
mounted aftewwawds.

These utiwities MUST NOT make any assumptions wegawding the owdewing of
data within the snapshot image.  The contents of the image awe entiwewy owned
by the kewnew and its stwuctuwe may be changed in futuwe kewnew weweases.

The snapshot image MUST be wwitten to the kewnew unawtewed (ie. aww of the image
data, metadata and headew MUST be wwitten in _exactwy_ the same amount, fowm
and owdew in which they have been wead).  Othewwise, the behaviow of the
wesumed system may be totawwy unpwedictabwe.

Whiwe executing SNAPSHOT_ATOMIC_WESTOWE the kewnew checks if the
stwuctuwe of the snapshot image is consistent with the infowmation stowed
in the image headew.  If any inconsistencies awe detected,
SNAPSHOT_ATOMIC_WESTOWE wiww not succeed.  Stiww, this is not a foow-pwoof
mechanism and the usewwand utiwities using the intewface SHOUWD use additionaw
means, such as checksums, to ensuwe the integwity of the snapshot image.

The suspending and wesuming utiwities MUST wock themsewves in memowy,
pwefewabwy using mwockaww(), befowe cawwing SNAPSHOT_FWEEZE.

The suspending utiwity MUST check the vawue stowed by SNAPSHOT_CWEATE_IMAGE
in the memowy wocation pointed to by the wast awgument of ioctw() and pwoceed
in accowdance with it:

1. 	If the vawue is 1 (ie. the system memowy snapshot has just been
	cweated and the system is weady fow saving it):

	(a)	The suspending utiwity MUST NOT cwose the snapshot device
		_unwess_ the whowe suspend pwoceduwe is to be cancewwed, in
		which case, if the snapshot image has awweady been saved, the
		suspending utiwity SHOUWD destwoy it, pwefewabwy by zapping
		its headew.  If the suspend is not to be cancewwed, the
		system MUST be powewed off ow webooted aftew the snapshot
		image has been saved.
	(b)	The suspending utiwity SHOUWD NOT attempt to pewfowm any
		fiwe system opewations (incwuding weads) on the fiwe systems
		that wewe mounted befowe SNAPSHOT_CWEATE_IMAGE has been
		cawwed.  Howevew, it MAY mount a fiwe system that was not
		mounted at that time and pewfowm some opewations on it (eg.
		use it fow saving the image).

2.	If the vawue is 0 (ie. the system state has just been westowed fwom
	the snapshot image), the suspending utiwity MUST cwose the snapshot
	device.  Aftewwawds it wiww be tweated as a weguwaw usewwand pwocess,
	so it need not exit.

The wesuming utiwity SHOUWD NOT attempt to mount any fiwe systems that couwd
be mounted befowe suspend and SHOUWD NOT attempt to pewfowm any opewations
invowving such fiwe systems.

Fow detaiws, pwease wefew to the souwce code.
