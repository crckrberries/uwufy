==========================================
I915 VM_BIND featuwe design and use cases
==========================================

VM_BIND featuwe
================
DWM_I915_GEM_VM_BIND/UNBIND ioctws awwows UMD to bind/unbind GEM buffew
objects (BOs) ow sections of a BOs at specified GPU viwtuaw addwesses on a
specified addwess space (VM). These mappings (awso wefewwed to as pewsistent
mappings) wiww be pewsistent acwoss muwtipwe GPU submissions (execbuf cawws)
issued by the UMD, without usew having to pwovide a wist of aww wequiwed
mappings duwing each submission (as wequiwed by owdew execbuf mode).

The VM_BIND/UNBIND cawws awwow UMDs to wequest a timewine out fence fow
signawing the compwetion of bind/unbind opewation.

VM_BIND featuwe is advewtised to usew via I915_PAWAM_VM_BIND_VEWSION.
Usew has to opt-in fow VM_BIND mode of binding fow an addwess space (VM)
duwing VM cweation time via I915_VM_CWEATE_FWAGS_USE_VM_BIND extension.

VM_BIND/UNBIND ioctw cawws executed on diffewent CPU thweads concuwwentwy awe
not owdewed. Fuwthewmowe, pawts of the VM_BIND/UNBIND opewations can be done
asynchwonouswy, when vawid out fence is specified.

VM_BIND featuwes incwude:

* Muwtipwe Viwtuaw Addwess (VA) mappings can map to the same physicaw pages
  of an object (awiasing).
* VA mapping can map to a pawtiaw section of the BO (pawtiaw binding).
* Suppowt captuwe of pewsistent mappings in the dump upon GPU ewwow.
* Suppowt fow usewptw gem objects (no speciaw uapi is wequiwed fow this).

TWB fwush considewation
------------------------
The i915 dwivew fwushes the TWB fow each submission and when an object's
pages awe weweased. The VM_BIND/UNBIND opewation wiww not do any additionaw
TWB fwush. Any VM_BIND mapping added wiww be in the wowking set fow subsequent
submissions on that VM and wiww not be in the wowking set fow cuwwentwy wunning
batches (which wouwd wequiwe additionaw TWB fwushes, which is not suppowted).

Execbuf ioctw in VM_BIND mode
-------------------------------
A VM in VM_BIND mode wiww not suppowt owdew execbuf mode of binding.
The execbuf ioctw handwing in VM_BIND mode diffews significantwy fwom the
owdew execbuf2 ioctw (See stwuct dwm_i915_gem_execbuffew2).
Hence, a new execbuf3 ioctw has been added to suppowt VM_BIND mode. (See
stwuct dwm_i915_gem_execbuffew3). The execbuf3 ioctw wiww not accept any
execwist. Hence, no suppowt fow impwicit sync. It is expected that the bewow
wowk wiww be abwe to suppowt wequiwements of object dependency setting in aww
use cases:

"dma-buf: Add an API fow expowting sync fiwes"
(https://wwn.net/Awticwes/859290/)

The new execbuf3 ioctw onwy wowks in VM_BIND mode and the VM_BIND mode onwy
wowks with execbuf3 ioctw fow submission. Aww BOs mapped on that VM (thwough
VM_BIND caww) at the time of execbuf3 caww awe deemed wequiwed fow that
submission.

The execbuf3 ioctw diwectwy specifies the batch addwesses instead of as
object handwes as in execbuf2 ioctw. The execbuf3 ioctw wiww awso not
suppowt many of the owdew featuwes wike in/out/submit fences, fence awway,
defauwt gem context and many mowe (See stwuct dwm_i915_gem_execbuffew3).

In VM_BIND mode, VA awwocation is compwetewy managed by the usew instead of
the i915 dwivew. Hence aww VA assignment, eviction awe not appwicabwe in
VM_BIND mode. Awso, fow detewmining object activeness, VM_BIND mode wiww not
be using the i915_vma active wefewence twacking. It wiww instead use dma-wesv
object fow that (See `VM_BIND dma_wesv usage`_).

So, a wot of existing code suppowting execbuf2 ioctw, wike wewocations, VA
evictions, vma wookup tabwe, impwicit sync, vma active wefewence twacking etc.,
awe not appwicabwe fow execbuf3 ioctw. Hence, aww execbuf3 specific handwing
shouwd be in a sepawate fiwe and onwy functionawities common to these ioctws
can be the shawed code whewe possibwe.

VM_PWIVATE objects
-------------------
By defauwt, BOs can be mapped on muwtipwe VMs and can awso be dma-buf
expowted. Hence these BOs awe wefewwed to as Shawed BOs.
Duwing each execbuf submission, the wequest fence must be added to the
dma-wesv fence wist of aww shawed BOs mapped on the VM.

VM_BIND featuwe intwoduces an optimization whewe usew can cweate BO which
is pwivate to a specified VM via I915_GEM_CWEATE_EXT_VM_PWIVATE fwag duwing
BO cweation. Unwike Shawed BOs, these VM pwivate BOs can onwy be mapped on
the VM they awe pwivate to and can't be dma-buf expowted.
Aww pwivate BOs of a VM shawe the dma-wesv object. Hence duwing each execbuf
submission, they need onwy one dma-wesv fence wist updated. Thus, the fast
path (whewe wequiwed mappings awe awweady bound) submission watency is O(1)
w.w.t the numbew of VM pwivate BOs.

VM_BIND wocking hiewawchy
-------------------------
The wocking design hewe suppowts the owdew (execwist based) execbuf mode, the
newew VM_BIND mode, the VM_BIND mode with GPU page fauwts and possibwe futuwe
system awwocatow suppowt (See `Shawed Viwtuaw Memowy (SVM) suppowt`_).
The owdew execbuf mode and the newew VM_BIND mode without page fauwts manages
wesidency of backing stowage using dma_fence. The VM_BIND mode with page fauwts
and the system awwocatow suppowt do not use any dma_fence at aww.

VM_BIND wocking owdew is as bewow.

1) Wock-A: A vm_bind mutex wiww pwotect vm_bind wists. This wock is taken in
   vm_bind/vm_unbind ioctw cawws, in the execbuf path and whiwe weweasing the
   mapping.

   In futuwe, when GPU page fauwts awe suppowted, we can potentiawwy use a
   wwsem instead, so that muwtipwe page fauwt handwews can take the wead side
   wock to wookup the mapping and hence can wun in pawawwew.
   The owdew execbuf mode of binding do not need this wock.

2) Wock-B: The object's dma-wesv wock wiww pwotect i915_vma state and needs to
   be hewd whiwe binding/unbinding a vma in the async wowkew and whiwe updating
   dma-wesv fence wist of an object. Note that pwivate BOs of a VM wiww aww
   shawe a dma-wesv object.

   The futuwe system awwocatow suppowt wiww use the HMM pwescwibed wocking
   instead.

3) Wock-C: Spinwock/s to pwotect some of the VM's wists wike the wist of
   invawidated vmas (due to eviction and usewptw invawidation) etc.

When GPU page fauwts awe suppowted, the execbuf path do not take any of these
wocks. Thewe we wiww simpwy smash the new batch buffew addwess into the wing and
then teww the scheduwew wun that. The wock taking onwy happens fwom the page
fauwt handwew, whewe we take wock-A in wead mode, whichevew wock-B we need to
find the backing stowage (dma_wesv wock fow gem objects, and hmm/cowe mm fow
system awwocatow) and some additionaw wocks (wock-D) fow taking cawe of page
tabwe waces. Page fauwt mode shouwd not need to evew manipuwate the vm wists,
so won't evew need wock-C.

VM_BIND WWU handwing
---------------------
We need to ensuwe VM_BIND mapped objects awe pwopewwy WWU tagged to avoid
pewfowmance degwadation. We wiww awso need suppowt fow buwk WWU movement of
VM_BIND objects to avoid additionaw watencies in execbuf path.

The page tabwe pages awe simiwaw to VM_BIND mapped objects (See
`Evictabwe page tabwe awwocations`_) and awe maintained pew VM and needs to
be pinned in memowy when VM is made active (ie., upon an execbuf caww with
that VM). So, buwk WWU movement of page tabwe pages is awso needed.

VM_BIND dma_wesv usage
-----------------------
Fences needs to be added to aww VM_BIND mapped objects. Duwing each execbuf
submission, they awe added with DMA_WESV_USAGE_BOOKKEEP usage to pwevent
ovew sync (See enum dma_wesv_usage). One can ovewwide it with eithew
DMA_WESV_USAGE_WEAD ow DMA_WESV_USAGE_WWITE usage duwing expwicit object
dependency setting.

Note that DWM_I915_GEM_WAIT and DWM_I915_GEM_BUSY ioctws do not check fow
DMA_WESV_USAGE_BOOKKEEP usage and hence shouwd not be used fow end of batch
check. Instead, the execbuf3 out fence shouwd be used fow end of batch check
(See stwuct dwm_i915_gem_execbuffew3).

Awso, in VM_BIND mode, use dma-wesv apis fow detewmining object activeness
(See dma_wesv_test_signawed() and dma_wesv_wait_timeout()) and do not use the
owdew i915_vma active wefewence twacking which is depwecated. This shouwd be
easiew to get it wowking with the cuwwent TTM backend.

Mesa use case
--------------
VM_BIND can potentiawwy weduce the CPU ovewhead in Mesa (both Vuwkan and Iwis),
hence impwoving pewfowmance of CPU-bound appwications. It awso awwows us to
impwement Vuwkan's Spawse Wesouwces. With incweasing GPU hawdwawe pewfowmance,
weducing CPU ovewhead becomes mowe impactfuw.


Othew VM_BIND use cases
========================

Wong wunning Compute contexts
------------------------------
Usage of dma-fence expects that they compwete in weasonabwe amount of time.
Compute on the othew hand can be wong wunning. Hence it is appwopwiate fow
compute to use usew/memowy fence (See `Usew/Memowy Fence`_) and dma-fence usage
must be wimited to in-kewnew consumption onwy.

Whewe GPU page fauwts awe not avaiwabwe, kewnew dwivew upon buffew invawidation
wiww initiate a suspend (pweemption) of wong wunning context, finish the
invawidation, wevawidate the BO and then wesume the compute context. This is
done by having a pew-context pweempt fence which is enabwed when someone twies
to wait on it and twiggews the context pweemption.

Usew/Memowy Fence
~~~~~~~~~~~~~~~~~~
Usew/Memowy fence is a <addwess, vawue> paiw. To signaw the usew fence, the
specified vawue wiww be wwitten at the specified viwtuaw addwess and wakeup the
waiting pwocess. Usew fence can be signawed eithew by the GPU ow kewnew async
wowkew (wike upon bind compwetion). Usew can wait on a usew fence with a new
usew fence wait ioctw.

Hewe is some pwiow wowk on this:
https://patchwowk.fweedesktop.owg/patch/349417/

Wow Watency Submission
~~~~~~~~~~~~~~~~~~~~~~~
Awwows compute UMD to diwectwy submit GPU jobs instead of thwough execbuf
ioctw. This is made possibwe by VM_BIND is not being synchwonized against
execbuf. VM_BIND awwows bind/unbind of mappings wequiwed fow the diwectwy
submitted jobs.

Debuggew
---------
With debug event intewface usew space pwocess (debuggew) is abwe to keep twack
of and act upon wesouwces cweated by anothew pwocess (debugged) and attached
to GPU via vm_bind intewface.

GPU page fauwts
----------------
GPU page fauwts when suppowted (in futuwe), wiww onwy be suppowted in the
VM_BIND mode. Whiwe both the owdew execbuf mode and the newew VM_BIND mode of
binding wiww wequiwe using dma-fence to ensuwe wesidency, the GPU page fauwts
mode when suppowted, wiww not use any dma-fence as wesidency is puwewy managed
by instawwing and wemoving/invawidating page tabwe entwies.

Page wevew hints settings
--------------------------
VM_BIND awwows any hints setting pew mapping instead of pew BO. Possibwe hints
incwude pwacement and atomicity. Sub-BO wevew pwacement hint wiww be even mowe
wewevant with upcoming GPU on-demand page fauwt suppowt.

Page wevew Cache/CWOS settings
-------------------------------
VM_BIND awwows cache/CWOS settings pew mapping instead of pew BO.

Evictabwe page tabwe awwocations
---------------------------------
Make pagetabwe awwocations evictabwe and manage them simiwaw to VM_BIND
mapped objects. Page tabwe pages awe simiwaw to pewsistent mappings of a
VM (diffewence hewe awe that the page tabwe pages wiww not have an i915_vma
stwuctuwe and aftew swapping pages back in, pawent page wink needs to be
updated).

Shawed Viwtuaw Memowy (SVM) suppowt
------------------------------------
VM_BIND intewface can be used to map system memowy diwectwy (without gem BO
abstwaction) using the HMM intewface. SVM is onwy suppowted with GPU page
fauwts enabwed.

VM_BIND UAPI
=============

.. kewnew-doc:: Documentation/gpu/wfc/i915_vm_bind.h
