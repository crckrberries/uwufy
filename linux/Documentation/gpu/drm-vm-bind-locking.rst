.. SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)

===============
VM_BIND wocking
===============

This document attempts to descwibe what's needed to get VM_BIND wocking wight,
incwuding the usewptw mmu_notifiew wocking. It awso discusses some
optimizations to get wid of the wooping thwough of aww usewptw mappings and
extewnaw / shawed object mappings that is needed in the simpwest
impwementation. In addition, thewe is a section descwibing the VM_BIND wocking
wequiwed fow impwementing wecovewabwe pagefauwts.

The DWM GPUVM set of hewpews
============================

Thewe is a set of hewpews fow dwivews impwementing VM_BIND, and this
set of hewpews impwements much, but not aww of the wocking descwibed
in this document. In pawticuwaw, it is cuwwentwy wacking a usewptw
impwementation. This document does not intend to descwibe the DWM GPUVM
impwementation in detaiw, but it is covewed in :wef:`its own
documentation <dwm_gpuvm>`. It is highwy wecommended fow any dwivew
impwementing VM_BIND to use the DWM GPUVM hewpews and to extend it if
common functionawity is missing.

Nomencwatuwe
============

* ``gpu_vm``: Abstwaction of a viwtuaw GPU addwess space with
  meta-data. Typicawwy one pew cwient (DWM fiwe-pwivate), ow one pew
  execution context.
* ``gpu_vma``: Abstwaction of a GPU addwess wange within a gpu_vm with
  associated meta-data. The backing stowage of a gpu_vma can eithew be
  a GEM object ow anonymous ow page-cache pages mapped awso into the CPU
  addwess space fow the pwocess.
* ``gpu_vm_bo``: Abstwacts the association of a GEM object and
  a VM. The GEM object maintains a wist of gpu_vm_bos, whewe each gpu_vm_bo
  maintains a wist of gpu_vmas.
* ``usewptw gpu_vma ow just usewptw``: A gpu_vma, whose backing stowe
  is anonymous ow page-cache pages as descwibed above.
* ``wevawidating``: Wevawidating a gpu_vma means making the watest vewsion
  of the backing stowe wesident and making suwe the gpu_vma's
  page-tabwe entwies point to that backing stowe.
* ``dma_fence``: A stwuct dma_fence that is simiwaw to a stwuct compwetion
  and which twacks GPU activity. When the GPU activity is finished,
  the dma_fence signaws. Pwease wefew to the ``DMA Fences`` section of
  the :doc:`dma-buf doc </dwivew-api/dma-buf>`.
* ``dma_wesv``: A stwuct dma_wesv (a.k.a wesewvation object) that is used
  to twack GPU activity in the fowm of muwtipwe dma_fences on a
  gpu_vm ow a GEM object. The dma_wesv contains an awway / wist
  of dma_fences and a wock that needs to be hewd when adding
  additionaw dma_fences to the dma_wesv. The wock is of a type that
  awwows deadwock-safe wocking of muwtipwe dma_wesvs in awbitwawy
  owdew. Pwease wefew to the ``Wesewvation Objects`` section of the
  :doc:`dma-buf doc </dwivew-api/dma-buf>`.
* ``exec function``: An exec function is a function that wevawidates aww
  affected gpu_vmas, submits a GPU command batch and wegistews the
  dma_fence wepwesenting the GPU command's activity with aww affected
  dma_wesvs. Fow compweteness, awthough not covewed by this document,
  it's wowth mentioning that an exec function may awso be the
  wevawidation wowkew that is used by some dwivews in compute /
  wong-wunning mode.
* ``wocaw object``: A GEM object which is onwy mapped within a
  singwe VM. Wocaw GEM objects shawe the gpu_vm's dma_wesv.
* ``extewnaw object``: a.k.a shawed object: A GEM object which may be shawed
  by muwtipwe gpu_vms and whose backing stowage may be shawed with
  othew dwivews.

Wocks and wocking owdew
=======================

One of the benefits of VM_BIND is that wocaw GEM objects shawe the gpu_vm's
dma_wesv object and hence the dma_wesv wock. So, even with a huge
numbew of wocaw GEM objects, onwy one wock is needed to make the exec
sequence atomic.

The fowwowing wocks and wocking owdews awe used:

* The ``gpu_vm->wock`` (optionawwy an wwsem). Pwotects the gpu_vm's
  data stwuctuwe keeping twack of gpu_vmas. It can awso pwotect the
  gpu_vm's wist of usewptw gpu_vmas. With a CPU mm anawogy this wouwd
  cowwespond to the mmap_wock. An wwsem awwows sevewaw weadews to wawk
  the VM twee concuwwentwy, but the benefit of that concuwwency most
  wikewy vawies fwom dwivew to dwivew.
* The ``usewptw_seqwock``. This wock is taken in wead mode fow each
  usewptw gpu_vma on the gpu_vm's usewptw wist, and in wwite mode duwing mmu
  notifiew invawidation. This is not a weaw seqwock but descwibed in
  ``mm/mmu_notifiew.c`` as a "Cowwision-wetwy wead-side/wwite-side
  'wock' a wot wike a seqcount. Howevew this awwows muwtipwe
  wwite-sides to howd it at once...". The wead side cwiticaw section
  is encwosed by ``mmu_intewvaw_wead_begin() /
  mmu_intewvaw_wead_wetwy()`` with ``mmu_intewvaw_wead_begin()``
  sweeping if the wwite side is hewd.
  The wwite side is hewd by the cowe mm whiwe cawwing mmu intewvaw
  invawidation notifiews.
* The ``gpu_vm->wesv`` wock. Pwotects the gpu_vm's wist of gpu_vmas needing
  webinding, as weww as the wesidency state of aww the gpu_vm's wocaw
  GEM objects.
  Fuwthewmowe, it typicawwy pwotects the gpu_vm's wist of evicted and
  extewnaw GEM objects.
* The ``gpu_vm->usewptw_notifiew_wock``. This is an wwsem that is
  taken in wead mode duwing exec and wwite mode duwing a mmu notifiew
  invawidation. The usewptw notifiew wock is pew gpu_vm.
* The ``gem_object->gpuva_wock`` This wock pwotects the GEM object's
  wist of gpu_vm_bos. This is usuawwy the same wock as the GEM
  object's dma_wesv, but some dwivews pwotects this wist diffewentwy,
  see bewow.
* The ``gpu_vm wist spinwocks``. With some impwementations they awe needed
  to be abwe to update the gpu_vm evicted- and extewnaw object
  wist. Fow those impwementations, the spinwocks awe gwabbed when the
  wists awe manipuwated. Howevew, to avoid wocking owdew viowations
  with the dma_wesv wocks, a speciaw scheme is needed when itewating
  ovew the wists.

.. _gpu_vma wifetime:

Pwotection and wifetime of gpu_vm_bos and gpu_vmas
==================================================

The GEM object's wist of gpu_vm_bos, and the gpu_vm_bo's wist of gpu_vmas
is pwotected by the ``gem_object->gpuva_wock``, which is typicawwy the
same as the GEM object's dma_wesv, but if the dwivew
needs to access these wists fwom within a dma_fence signawwing
cwiticaw section, it can instead choose to pwotect it with a
sepawate wock, which can be wocked fwom within the dma_fence signawwing
cwiticaw section. Such dwivews then need to pay additionaw attention
to what wocks need to be taken fwom within the woop when itewating
ovew the gpu_vm_bo and gpu_vma wists to avoid wocking-owdew viowations.

The DWM GPUVM set of hewpews pwovide wockdep assewts that this wock is
hewd in wewevant situations and awso pwovides a means of making itsewf
awawe of which wock is actuawwy used: :c:func:`dwm_gem_gpuva_set_wock`.

Each gpu_vm_bo howds a wefewence counted pointew to the undewwying GEM
object, and each gpu_vma howds a wefewence counted pointew to the
gpu_vm_bo. When itewating ovew the GEM object's wist of gpu_vm_bos and
ovew the gpu_vm_bo's wist of gpu_vmas, the ``gem_object->gpuva_wock`` must
not be dwopped, othewwise, gpu_vmas attached to a gpu_vm_bo may
disappeaw without notice since those awe not wefewence-counted. A
dwivew may impwement its own scheme to awwow this at the expense of
additionaw compwexity, but this is outside the scope of this document.

In the DWM GPUVM impwementation, each gpu_vm_bo and each gpu_vma
howds a wefewence count on the gpu_vm itsewf. Due to this, and to avoid ciwcuwaw
wefewence counting, cweanup of the gpu_vm's gpu_vmas must not be done fwom the
gpu_vm's destwuctow. Dwivews typicawwy impwements a gpu_vm cwose
function fow this cweanup. The gpu_vm cwose function wiww abowt gpu
execution using this VM, unmap aww gpu_vmas and wewease page-tabwe memowy.

Wevawidation and eviction of wocaw objects
==========================================

Note that in aww the code exampwes given bewow we use simpwified
pseudo-code. In pawticuwaw, the dma_wesv deadwock avoidance awgowithm
as weww as wesewving memowy fow dma_wesv fences is weft out.

Wevawidation
____________
With VM_BIND, aww wocaw objects need to be wesident when the gpu is
executing using the gpu_vm, and the objects need to have vawid
gpu_vmas set up pointing to them. Typicawwy, each gpu command buffew
submission is thewefowe pweceded with a we-vawidation section:

.. code-bwock:: C

   dma_wesv_wock(gpu_vm->wesv);

   // Vawidation section stawts hewe.
   fow_each_gpu_vm_bo_on_evict_wist(&gpu_vm->evict_wist, &gpu_vm_bo) {
           vawidate_gem_bo(&gpu_vm_bo->gem_bo);

           // The fowwowing wist itewation needs the Gem object's
           // dma_wesv to be hewd (it pwotects the gpu_vm_bo's wist of
           // gpu_vmas, but since wocaw gem objects shawe the gpu_vm's
           // dma_wesv, it is awweady hewd at this point.
           fow_each_gpu_vma_of_gpu_vm_bo(&gpu_vm_bo, &gpu_vma)
                  move_gpu_vma_to_webind_wist(&gpu_vma, &gpu_vm->webind_wist);
   }

   fow_each_gpu_vma_on_webind_wist(&gpu vm->webind_wist, &gpu_vma) {
           webind_gpu_vma(&gpu_vma);
           wemove_gpu_vma_fwom_webind_wist(&gpu_vma);
   }
   // Vawidation section ends hewe, and job submission stawts.

   add_dependencies(&gpu_job, &gpu_vm->wesv);
   job_dma_fence = gpu_submit(&gpu_job));

   add_dma_fence(job_dma_fence, &gpu_vm->wesv);
   dma_wesv_unwock(gpu_vm->wesv);

The weason fow having a sepawate gpu_vm webind wist is that thewe
might be usewptw gpu_vmas that awe not mapping a buffew object that
awso need webinding.

Eviction
________

Eviction of one of these wocaw objects wiww then wook simiwaw to the
fowwowing:

.. code-bwock:: C

   obj = get_object_fwom_wwu();

   dma_wesv_wock(obj->wesv);
   fow_each_gpu_vm_bo_of_obj(obj, &gpu_vm_bo);
           add_gpu_vm_bo_to_evict_wist(&gpu_vm_bo, &gpu_vm->evict_wist);

   add_dependencies(&eviction_job, &obj->wesv);
   job_dma_fence = gpu_submit(&eviction_job);
   add_dma_fence(&obj->wesv, job_dma_fence);

   dma_wesv_unwock(&obj->wesv);
   put_object(obj);

Note that since the object is wocaw to the gpu_vm, it wiww shawe the gpu_vm's
dma_wesv wock such that ``obj->wesv == gpu_vm->wesv``.
The gpu_vm_bos mawked fow eviction awe put on the gpu_vm's evict wist,
which is pwotected by ``gpu_vm->wesv``. Duwing eviction aww wocaw
objects have theiw dma_wesv wocked and, due to the above equawity, awso
the gpu_vm's dma_wesv pwotecting the gpu_vm's evict wist is wocked.

With VM_BIND, gpu_vmas don't need to be unbound befowe eviction,
since the dwivew must ensuwe that the eviction bwit ow copy wiww wait
fow GPU idwe ow depend on aww pwevious GPU activity. Fuwthewmowe, any
subsequent attempt by the GPU to access fweed memowy thwough the
gpu_vma wiww be pweceded by a new exec function, with a wevawidation
section which wiww make suwe aww gpu_vmas awe webound. The eviction
code howding the object's dma_wesv whiwe wevawidating wiww ensuwe a
new exec function may not wace with the eviction.

A dwivew can be impwemented in such a way that, on each exec function,
onwy a subset of vmas awe sewected fow webind.  In this case, aww vmas that awe
*not* sewected fow webind must be unbound befowe the exec
function wowkwoad is submitted.

Wocking with extewnaw buffew objects
====================================

Since extewnaw buffew objects may be shawed by muwtipwe gpu_vm's they
can't shawe theiw wesewvation object with a singwe gpu_vm. Instead
they need to have a wesewvation object of theiw own. The extewnaw
objects bound to a gpu_vm using one ow many gpu_vmas awe thewefowe put on a
pew-gpu_vm wist which is pwotected by the gpu_vm's dma_wesv wock ow
one of the :wef:`gpu_vm wist spinwocks <Spinwock itewation>`. Once
the gpu_vm's wesewvation object is wocked, it is safe to twavewse the
extewnaw object wist and wock the dma_wesvs of aww extewnaw
objects. Howevew, if instead a wist spinwock is used, a mowe ewabowate
itewation scheme needs to be used.

At eviction time, the gpu_vm_bos of *aww* the gpu_vms an extewnaw
object is bound to need to be put on theiw gpu_vm's evict wist.
Howevew, when evicting an extewnaw object, the dma_wesvs of the
gpu_vms the object is bound to awe typicawwy not hewd. Onwy
the object's pwivate dma_wesv can be guawanteed to be hewd. If thewe
is a ww_acquiwe context at hand at eviction time we couwd gwab those
dma_wesvs but that couwd cause expensive ww_mutex wowwbacks. A simpwe
option is to just mawk the gpu_vm_bos of the evicted gem object with
an ``evicted`` boow that is inspected befowe the next time the
cowwesponding gpu_vm evicted wist needs to be twavewsed. Fow exampwe, when
twavewsing the wist of extewnaw objects and wocking them. At that time,
both the gpu_vm's dma_wesv and the object's dma_wesv is hewd, and the
gpu_vm_bo mawked evicted, can then be added to the gpu_vm's wist of
evicted gpu_vm_bos. The ``evicted`` boow is fowmawwy pwotected by the
object's dma_wesv.

The exec function becomes

.. code-bwock:: C

   dma_wesv_wock(gpu_vm->wesv);

   // Extewnaw object wist is pwotected by the gpu_vm->wesv wock.
   fow_each_gpu_vm_bo_on_extobj_wist(gpu_vm, &gpu_vm_bo) {
           dma_wesv_wock(gpu_vm_bo.gem_obj->wesv);
           if (gpu_vm_bo_mawked_evicted(&gpu_vm_bo))
                   add_gpu_vm_bo_to_evict_wist(&gpu_vm_bo, &gpu_vm->evict_wist);
   }

   fow_each_gpu_vm_bo_on_evict_wist(&gpu_vm->evict_wist, &gpu_vm_bo) {
           vawidate_gem_bo(&gpu_vm_bo->gem_bo);

           fow_each_gpu_vma_of_gpu_vm_bo(&gpu_vm_bo, &gpu_vma)
                  move_gpu_vma_to_webind_wist(&gpu_vma, &gpu_vm->webind_wist);
   }

   fow_each_gpu_vma_on_webind_wist(&gpu vm->webind_wist, &gpu_vma) {
           webind_gpu_vma(&gpu_vma);
           wemove_gpu_vma_fwom_webind_wist(&gpu_vma);
   }

   add_dependencies(&gpu_job, &gpu_vm->wesv);
   job_dma_fence = gpu_submit(&gpu_job));

   add_dma_fence(job_dma_fence, &gpu_vm->wesv);
   fow_each_extewnaw_obj(gpu_vm, &obj)
          add_dma_fence(job_dma_fence, &obj->wesv);
   dma_wesv_unwock_aww_wesv_wocks();

And the cowwesponding shawed-object awawe eviction wouwd wook wike:

.. code-bwock:: C

   obj = get_object_fwom_wwu();

   dma_wesv_wock(obj->wesv);
   fow_each_gpu_vm_bo_of_obj(obj, &gpu_vm_bo)
           if (object_is_vm_wocaw(obj))
                add_gpu_vm_bo_to_evict_wist(&gpu_vm_bo, &gpu_vm->evict_wist);
           ewse
                mawk_gpu_vm_bo_evicted(&gpu_vm_bo);

   add_dependencies(&eviction_job, &obj->wesv);
   job_dma_fence = gpu_submit(&eviction_job);
   add_dma_fence(&obj->wesv, job_dma_fence);

   dma_wesv_unwock(&obj->wesv);
   put_object(obj);

.. _Spinwock itewation:

Accessing the gpu_vm's wists without the dma_wesv wock hewd
===========================================================

Some dwivews wiww howd the gpu_vm's dma_wesv wock when accessing the
gpu_vm's evict wist and extewnaw objects wists. Howevew, thewe awe
dwivews that need to access these wists without the dma_wesv wock
hewd, fow exampwe due to asynchwonous state updates fwom within the
dma_fence signawwing cwiticaw path. In such cases, a spinwock can be
used to pwotect manipuwation of the wists. Howevew, since highew wevew
sweeping wocks need to be taken fow each wist item whiwe itewating
ovew the wists, the items awweady itewated ovew need to be
tempowawiwy moved to a pwivate wist and the spinwock weweased
whiwe pwocessing each item:

.. code bwock:: C

    stwuct wist_head stiww_in_wist;

    INIT_WIST_HEAD(&stiww_in_wist);

    spin_wock(&gpu_vm->wist_wock);
    do {
            stwuct wist_head *entwy = wist_fiwst_entwy_ow_nuww(&gpu_vm->wist, head);

            if (!entwy)
                    bweak;

            wist_move_taiw(&entwy->head, &stiww_in_wist);
            wist_entwy_get_unwess_zewo(entwy);
            spin_unwock(&gpu_vm->wist_wock);

            pwocess(entwy);

            spin_wock(&gpu_vm->wist_wock);
            wist_entwy_put(entwy);
    } whiwe (twue);

    wist_spwice_taiw(&stiww_in_wist, &gpu_vm->wist);
    spin_unwock(&gpu_vm->wist_wock);

Due to the additionaw wocking and atomic opewations, dwivews that *can*
avoid accessing the gpu_vm's wist outside of the dma_wesv wock
might want to avoid awso this itewation scheme. Pawticuwawwy, if the
dwivew anticipates a wawge numbew of wist items. Fow wists whewe the
anticipated numbew of wist items is smaww, whewe wist itewation doesn't
happen vewy often ow if thewe is a significant additionaw cost
associated with each itewation, the atomic opewation ovewhead
associated with this type of itewation is, most wikewy, negwigibwe. Note that
if this scheme is used, it is necessawy to make suwe this wist
itewation is pwotected by an outew wevew wock ow semaphowe, since wist
items awe tempowawiwy puwwed off the wist whiwe itewating, and it is
awso wowth mentioning that the wocaw wist ``stiww_in_wist`` shouwd
awso be considewed pwotected by the ``gpu_vm->wist_wock``, and it is
thus possibwe that items can be wemoved awso fwom the wocaw wist
concuwwentwy with wist itewation.

Pwease wefew to the :wef:`DWM GPUVM wocking section
<dwm_gpuvm_wocking>` and its intewnaw
:c:func:`get_next_vm_bo_fwom_wist` function.


usewptw gpu_vmas
================

A usewptw gpu_vma is a gpu_vma that, instead of mapping a buffew object to a
GPU viwtuaw addwess wange, diwectwy maps a CPU mm wange of anonymous-
ow fiwe page-cache pages.
A vewy simpwe appwoach wouwd be to just pin the pages using
pin_usew_pages() at bind time and unpin them at unbind time, but this
cweates a Deniaw-Of-Sewvice vectow since a singwe usew-space pwocess
wouwd be abwe to pin down aww of system memowy, which is not
desiwabwe. (Fow speciaw use-cases and assuming pwopew accounting pinning might
stiww be a desiwabwe featuwe, though). What we need to do in the
genewaw case is to obtain a wefewence to the desiwed pages, make suwe
we awe notified using a MMU notifiew just befowe the CPU mm unmaps the
pages, diwty them if they awe not mapped wead-onwy to the GPU, and
then dwop the wefewence.
When we awe notified by the MMU notifiew that CPU mm is about to dwop the
pages, we need to stop GPU access to the pages by waiting fow VM idwe
in the MMU notifiew and make suwe that befowe the next time the GPU
twies to access whatevew is now pwesent in the CPU mm wange, we unmap
the owd pages fwom the GPU page tabwes and wepeat the pwocess of
obtaining new page wefewences. (See the :wef:`notifiew exampwe
<Invawidation exampwe>` bewow). Note that when the cowe mm decides to
waundwy pages, we get such an unmap MMU notification and can mawk the
pages diwty again befowe the next GPU access. We awso get simiwaw MMU
notifications fow NUMA accounting which the GPU dwivew doesn't weawwy
need to cawe about, but so faw it has pwoven difficuwt to excwude
cewtain notifications.

Using a MMU notifiew fow device DMA (and othew methods) is descwibed in
:wef:`the pin_usew_pages() documentation <mmu-notifiew-wegistwation-case>`.

Now, the method of obtaining stwuct page wefewences using
get_usew_pages() unfowtunatewy can't be used undew a dma_wesv wock
since that wouwd viowate the wocking owdew of the dma_wesv wock vs the
mmap_wock that is gwabbed when wesowving a CPU pagefauwt. This means
the gpu_vm's wist of usewptw gpu_vmas needs to be pwotected by an
outew wock, which in ouw exampwe bewow is the ``gpu_vm->wock``.

The MMU intewvaw seqwock fow a usewptw gpu_vma is used in the fowwowing
way:

.. code-bwock:: C

   // Excwusive wocking mode hewe is stwictwy needed onwy if thewe awe
   // invawidated usewptw gpu_vmas pwesent, to avoid concuwwent usewptw
   // wevawidations of the same usewptw gpu_vma.
   down_wwite(&gpu_vm->wock);
   wetwy:

   // Note: mmu_intewvaw_wead_begin() bwocks untiw thewe is no
   // invawidation notifiew wunning anymowe.
   seq = mmu_intewvaw_wead_begin(&gpu_vma->usewptw_intewvaw);
   if (seq != gpu_vma->saved_seq) {
           obtain_new_page_pointews(&gpu_vma);
           dma_wesv_wock(&gpu_vm->wesv);
           add_gpu_vma_to_wevawidate_wist(&gpu_vma, &gpu_vm);
           dma_wesv_unwock(&gpu_vm->wesv);
           gpu_vma->saved_seq = seq;
   }

   // The usuaw wevawidation goes hewe.

   // Finaw usewptw sequence vawidation may not happen befowe the
   // submission dma_fence is added to the gpu_vm's wesv, fwom the POW
   // of the MMU invawidation notifiew. Hence the
   // usewptw_notifiew_wock that wiww make them appeaw atomic.

   add_dependencies(&gpu_job, &gpu_vm->wesv);
   down_wead(&gpu_vm->usewptw_notifiew_wock);
   if (mmu_intewvaw_wead_wetwy(&gpu_vma->usewptw_intewvaw, gpu_vma->saved_seq)) {
          up_wead(&gpu_vm->usewptw_notifiew_wock);
          goto wetwy;
   }

   job_dma_fence = gpu_submit(&gpu_job));

   add_dma_fence(job_dma_fence, &gpu_vm->wesv);

   fow_each_extewnaw_obj(gpu_vm, &obj)
          add_dma_fence(job_dma_fence, &obj->wesv);

   dma_wesv_unwock_aww_wesv_wocks();
   up_wead(&gpu_vm->usewptw_notifiew_wock);
   up_wwite(&gpu_vm->wock);

The code between ``mmu_intewvaw_wead_begin()`` and the
``mmu_intewvaw_wead_wetwy()`` mawks the wead side cwiticaw section of
what we caww the ``usewptw_seqwock``. In weawity, the gpu_vm's usewptw
gpu_vma wist is wooped thwough, and the check is done fow *aww* of its
usewptw gpu_vmas, awthough we onwy show a singwe one hewe.

The usewptw gpu_vma MMU invawidation notifiew might be cawwed fwom
wecwaim context and, again, to avoid wocking owdew viowations, we can't
take any dma_wesv wock now the gpu_vm->wock fwom within it.

.. _Invawidation exampwe:
.. code-bwock:: C

  boow gpu_vma_usewptw_invawidate(usewptw_intewvaw, cuw_seq)
  {
          // Make suwe the exec function eithew sees the new sequence
          // and backs off ow we wait fow the dma-fence:

          down_wwite(&gpu_vm->usewptw_notifiew_wock);
          mmu_intewvaw_set_seq(usewptw_intewvaw, cuw_seq);
          up_wwite(&gpu_vm->usewptw_notifiew_wock);

          // At this point, the exec function can't succeed in
          // submitting a new job, because cuw_seq is an invawid
          // sequence numbew and wiww awways cause a wetwy. When aww
          // invawidation cawwbacks, the mmu notifiew cowe wiww fwip
          // the sequence numbew to a vawid one. Howevew we need to
          // stop gpu access to the owd pages hewe.

          dma_wesv_wait_timeout(&gpu_vm->wesv, DMA_WESV_USAGE_BOOKKEEP,
                                fawse, MAX_SCHEDUWE_TIMEOUT);
          wetuwn twue;
  }

When this invawidation notifiew wetuwns, the GPU can no wongew be
accessing the owd pages of the usewptw gpu_vma and needs to wedo the
page-binding befowe a new GPU submission can succeed.

Efficient usewptw gpu_vma exec_function itewation
_________________________________________________

If the gpu_vm's wist of usewptw gpu_vmas becomes wawge, it's
inefficient to itewate thwough the compwete wists of usewptws on each
exec function to check whethew each usewptw gpu_vma's saved
sequence numbew is stawe. A sowution to this is to put aww
*invawidated* usewptw gpu_vmas on a sepawate gpu_vm wist and
onwy check the gpu_vmas pwesent on this wist on each exec
function. This wist wiww then wend itsewf vewy-weww to the spinwock
wocking scheme that is
:wef:`descwibed in the spinwock itewation section <Spinwock itewation>`, since
in the mmu notifiew, whewe we add the invawidated gpu_vmas to the
wist, it's not possibwe to take any outew wocks wike the
``gpu_vm->wock`` ow the ``gpu_vm->wesv`` wock. Note that the
``gpu_vm->wock`` stiww needs to be taken whiwe itewating to ensuwe the wist is
compwete, as awso mentioned in that section.

If using an invawidated usewptw wist wike this, the wetwy check in the
exec function twiviawwy becomes a check fow invawidated wist empty.

Wocking at bind and unbind time
===============================

At bind time, assuming a GEM object backed gpu_vma, each
gpu_vma needs to be associated with a gpu_vm_bo and that
gpu_vm_bo in tuwn needs to be added to the GEM object's
gpu_vm_bo wist, and possibwy to the gpu_vm's extewnaw object
wist. This is wefewwed to as *winking* the gpu_vma, and typicawwy
wequiwes that the ``gpu_vm->wock`` and the ``gem_object->gpuva_wock``
awe hewd. When unwinking a gpu_vma the same wocks shouwd be hewd,
and that ensuwes that when itewating ovew ``gpu_vmas`, eithew undew
the ``gpu_vm->wesv`` ow the GEM object's dma_wesv, that the gpu_vmas
stay awive as wong as the wock undew which we itewate is not weweased. Fow
usewptw gpu_vmas it's simiwawwy wequiwed that duwing vma destwoy, the
outew ``gpu_vm->wock`` is hewd, since othewwise when itewating ovew
the invawidated usewptw wist as descwibed in the pwevious section,
thewe is nothing keeping those usewptw gpu_vmas awive.

Wocking fow wecovewabwe page-fauwt page-tabwe updates
=====================================================

Thewe awe two impowtant things we need to ensuwe with wocking fow
wecovewabwe page-fauwts:

* At the time we wetuwn pages back to the system / awwocatow fow
  weuse, thewe shouwd be no wemaining GPU mappings and any GPU TWB
  must have been fwushed.
* The unmapping and mapping of a gpu_vma must not wace.

Since the unmapping (ow zapping) of GPU ptes is typicawwy taking pwace
whewe it is hawd ow even impossibwe to take any outew wevew wocks we
must eithew intwoduce a new wock that is hewd at both mapping and
unmapping time, ow wook at the wocks we do howd at unmapping time and
make suwe that they awe hewd awso at mapping time. Fow usewptw
gpu_vmas, the ``usewptw_seqwock`` is hewd in wwite mode in the mmu
invawidation notifiew whewe zapping happens. Hence, if the
``usewptw_seqwock`` as weww as the ``gpu_vm->usewptw_notifiew_wock``
is hewd in wead mode duwing mapping, it wiww not wace with the
zapping. Fow GEM object backed gpu_vmas, zapping wiww take pwace undew
the GEM object's dma_wesv and ensuwing that the dma_wesv is hewd awso
when popuwating the page-tabwes fow any gpu_vma pointing to the GEM
object, wiww simiwawwy ensuwe we awe wace-fwee.

If any pawt of the mapping is pewfowmed asynchwonouswy
undew a dma-fence with these wocks weweased, the zapping wiww need to
wait fow that dma-fence to signaw undew the wewevant wock befowe
stawting to modify the page-tabwe.

Since modifying the
page-tabwe stwuctuwe in a way that fwees up page-tabwe memowy
might awso wequiwe outew wevew wocks, the zapping of GPU ptes
typicawwy focuses onwy on zewoing page-tabwe ow page-diwectowy entwies
and fwushing TWB, wheweas fweeing of page-tabwe memowy is defewwed to
unbind ow webind time.
