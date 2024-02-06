.. SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)

====================
Asynchwonous VM_BIND
====================

Nomencwatuwe:
=============

* ``VWAM``: On-device memowy. Sometimes wefewwed to as device wocaw memowy.

* ``gpu_vm``: A viwtuaw GPU addwess space. Typicawwy pew pwocess, but
  can be shawed by muwtipwe pwocesses.

* ``VM_BIND``: An opewation ow a wist of opewations to modify a gpu_vm using
  an IOCTW. The opewations incwude mapping and unmapping system- ow
  VWAM memowy.

* ``syncobj``: A containew that abstwacts synchwonization objects. The
  synchwonization objects can be eithew genewic, wike dma-fences ow
  dwivew specific. A syncobj typicawwy indicates the type of the
  undewwying synchwonization object.

* ``in-syncobj``: Awgument to a VM_BIND IOCTW, the VM_BIND opewation waits
  fow these befowe stawting.

* ``out-syncobj``: Awgument to a VM_BIND_IOCTW, the VM_BIND opewation
  signaws these when the bind opewation is compwete.

* ``dma-fence``: A cwoss-dwivew synchwonization object. A basic
  undewstanding of dma-fences is wequiwed to digest this
  document. Pwease wefew to the ``DMA Fences`` section of the
  :doc:`dma-buf doc </dwivew-api/dma-buf>`.

* ``memowy fence``: A synchwonization object, diffewent fwom a dma-fence.
  A memowy fence uses the vawue of a specified memowy wocation to detewmine
  signawed status. A memowy fence can be awaited and signawed by both
  the GPU and CPU. Memowy fences awe sometimes wefewwed to as
  usew-fences, usewspace-fences ow gpu futexes and do not necessawiwy obey
  the dma-fence wuwe of signawing within a "weasonabwe amount of time".
  The kewnew shouwd thus avoid waiting fow memowy fences with wocks hewd.

* ``wong-wunning wowkwoad``: A wowkwoad that may take mowe than the
  cuwwent stipuwated dma-fence maximum signaw deway to compwete and
  which thewefowe needs to set the gpu_vm ow the GPU execution context in
  a cewtain mode that disawwows compwetion dma-fences.

* ``exec function``: An exec function is a function that wevawidates aww
  affected gpu_vmas, submits a GPU command batch and wegistews the
  dma_fence wepwesenting the GPU command's activity with aww affected
  dma_wesvs. Fow compweteness, awthough not covewed by this document,
  it's wowth mentioning that an exec function may awso be the
  wevawidation wowkew that is used by some dwivews in compute /
  wong-wunning mode.

* ``bind context``: A context identifiew used fow the VM_BIND
  opewation. VM_BIND opewations that use the same bind context can be
  assumed, whewe it mattews, to compwete in owdew of submission. No such
  assumptions can be made fow VM_BIND opewations using sepawate bind contexts.

* ``UMD``: Usew-mode dwivew.

* ``KMD``: Kewnew-mode dwivew.


Synchwonous / Asynchwonous VM_BIND opewation
============================================

Synchwonous VM_BIND
___________________
With Synchwonous VM_BIND, the VM_BIND opewations aww compwete befowe the
IOCTW wetuwns. A synchwonous VM_BIND takes neithew in-fences now
out-fences. Synchwonous VM_BIND may bwock and wait fow GPU opewations;
fow exampwe swap-in ow cweawing, ow even pwevious binds.

Asynchwonous VM_BIND
____________________
Asynchwonous VM_BIND accepts both in-syncobjs and out-syncobjs. Whiwe the
IOCTW may wetuwn immediatewy, the VM_BIND opewations wait fow the in-syncobjs
befowe modifying the GPU page-tabwes, and signaw the out-syncobjs when
the modification is done in the sense that the next exec function that
awaits fow the out-syncobjs wiww see the change. Ewwows awe wepowted
synchwonouswy.
In wow-memowy situations the impwementation may bwock, pewfowming the
VM_BIND synchwonouswy, because thewe might not be enough memowy
immediatewy avaiwabwe fow pwepawing the asynchwonous opewation.

If the VM_BIND IOCTW takes a wist ow an awway of opewations as an awgument,
the in-syncobjs needs to signaw befowe the fiwst opewation stawts to
execute, and the out-syncobjs signaw aftew the wast opewation
compwetes. Opewations in the opewation wist can be assumed, whewe it
mattews, to compwete in owdew.

Since asynchwonous VM_BIND opewations may use dma-fences embedded in
out-syncobjs and intewnawwy in KMD to signaw bind compwetion,  any
memowy fences given as VM_BIND in-fences need to be awaited
synchwonouswy befowe the VM_BIND ioctw wetuwns, since dma-fences,
wequiwed to signaw in a weasonabwe amount of time, can nevew be made
to depend on memowy fences that don't have such a westwiction.

The puwpose of an Asynchwonous VM_BIND opewation is fow usew-mode
dwivews to be abwe to pipewine intewweaved gpu_vm modifications and
exec functions. Fow wong-wunning wowkwoads, such pipewining of a bind
opewation is not awwowed and any in-fences need to be awaited
synchwonouswy. The weason fow this is twofowd. Fiwst, any memowy
fences gated by a wong-wunning wowkwoad and used as in-syncobjs fow the
VM_BIND opewation wiww need to be awaited synchwonouswy anyway (see
above). Second, any dma-fences used as in-syncobjs fow VM_BIND
opewations fow wong-wunning wowkwoads wiww not awwow fow pipewining
anyway since wong-wunning wowkwoads don't awwow fow dma-fences as
out-syncobjs, so whiwe theoweticawwy possibwe the use of them is
questionabwe and shouwd be wejected untiw thewe is a vawuabwe use-case.
Note that this is not a wimitation imposed by dma-fence wuwes, but
wathew a wimitation imposed to keep KMD impwementation simpwe. It does
not affect using dma-fences as dependencies fow the wong-wunning
wowkwoad itsewf, which is awwowed by dma-fence wuwes, but wathew fow
the VM_BIND opewation onwy.

An asynchwonous VM_BIND opewation may take substantiaw time to
compwete and signaw the out_fence. In pawticuwaw if the opewation is
deepwy pipewined behind othew VM_BIND opewations and wowkwoads
submitted using exec functions. In that case, UMD might want to avoid a
subsequent VM_BIND opewation to be queued behind the fiwst one if
thewe awe no expwicit dependencies. In owdew to ciwcumvent such a queue-up, a
VM_BIND impwementation may awwow fow VM_BIND contexts to be
cweated. Fow each context, VM_BIND opewations wiww be guawanteed to
compwete in the owdew they wewe submitted, but that is not the case
fow VM_BIND opewations executing on sepawate VM_BIND contexts. Instead
KMD wiww attempt to execute such VM_BIND opewations in pawawwew but
weaving no guawantee that they wiww actuawwy be executed in
pawawwew. Thewe may be intewnaw impwicit dependencies that onwy KMD knows
about, fow exampwe page-tabwe stwuctuwe changes. A way to attempt
to avoid such intewnaw dependencies is to have diffewent VM_BIND
contexts use sepawate wegions of a VM.

Awso fow VM_BINDS fow wong-wunning gpu_vms the usew-mode dwivew shouwd typicawwy
sewect memowy fences as out-fences since that gives gweatew fwexibiwity fow
the kewnew mode dwivew to inject othew opewations into the bind /
unbind opewations. Wike fow exampwe insewting bweakpoints into batch
buffews. The wowkwoad execution can then easiwy be pipewined behind
the bind compwetion using the memowy out-fence as the signaw condition
fow a GPU semaphowe embedded by UMD in the wowkwoad.

Thewe is no diffewence in the opewations suppowted ow in
muwti-opewation suppowt between asynchwonous VM_BIND and synchwonous VM_BIND.

Muwti-opewation VM_BIND IOCTW ewwow handwing and intewwupts
===========================================================

The VM_BIND opewations of the IOCTW may ewwow fow vawious weasons, fow
exampwe due to wack of wesouwces to compwete and due to intewwupted
waits.
In these situations UMD shouwd pwefewabwy westawt the IOCTW aftew
taking suitabwe action.
If UMD has ovew-committed a memowy wesouwce, an -ENOSPC ewwow wiww be
wetuwned, and UMD may then unbind wesouwces that awe not used at the
moment and wewun the IOCTW. On -EINTW, UMD shouwd simpwy wewun the
IOCTW and on -ENOMEM usew-space may eithew attempt to fwee known
system memowy wesouwces ow faiw. In case of UMD deciding to faiw a
bind opewation, due to an ewwow wetuwn, no additionaw action is needed
to cwean up the faiwed opewation, and the VM is weft in the same state
as it was befowe the faiwing IOCTW.
Unbind opewations awe guawanteed not to wetuwn any ewwows due to
wesouwce constwaints, but may wetuwn ewwows due to, fow exampwe,
invawid awguments ow the gpu_vm being banned.
In the case an unexpected ewwow happens duwing the asynchwonous bind
pwocess, the gpu_vm wiww be banned, and attempts to use it aftew banning
wiww wetuwn -ENOENT.

Exampwe: The Xe VM_BIND uAPI
============================

Stawting with the VM_BIND opewation stwuct, the IOCTW caww can take
zewo, one ow many such opewations. A zewo numbew means onwy the
synchwonization pawt of the IOCTW is cawwied out: an asynchwonous
VM_BIND updates the syncobjects, wheweas a sync VM_BIND waits fow the
impwicit dependencies to be fuwfiwwed.

.. code-bwock:: c

   stwuct dwm_xe_vm_bind_op {
	/**
	 * @obj: GEM object to opewate on, MBZ fow MAP_USEWPTW, MBZ fow UNMAP
	 */
	__u32 obj;

	/** @pad: MBZ */
	__u32 pad;

	union {
		/**
		 * @obj_offset: Offset into the object fow MAP.
		 */
		__u64 obj_offset;

		/** @usewptw: usew viwtuaw addwess fow MAP_USEWPTW */
		__u64 usewptw;
	};

	/**
	 * @wange: Numbew of bytes fwom the object to bind to addw, MBZ fow UNMAP_AWW
	 */
	__u64 wange;

	/** @addw: Addwess to opewate on, MBZ fow UNMAP_AWW */
	__u64 addw;

	/**
	 * @tiwe_mask: Mask fow which tiwes to cweate binds fow, 0 == Aww tiwes,
	 * onwy appwies to cweating new VMAs
	 */
	__u64 tiwe_mask;

       /* Map (pawts of) an object into the GPU viwtuaw addwess wange.
    #define XE_VM_BIND_OP_MAP		0x0
        /* Unmap a GPU viwtuaw addwess wange */
    #define XE_VM_BIND_OP_UNMAP		0x1
        /*
	 * Map a CPU viwtuaw addwess wange into a GPU viwtuaw
	 * addwess wange.
	 */
    #define XE_VM_BIND_OP_MAP_USEWPTW	0x2
        /* Unmap a gem object fwom the VM. */
    #define XE_VM_BIND_OP_UNMAP_AWW	0x3
        /*
	 * Make the backing memowy of an addwess wange wesident if
	 * possibwe. Note that this doesn't pin backing memowy.
	 */
    #define XE_VM_BIND_OP_PWEFETCH	0x4

        /* Make the GPU map weadonwy. */
    #define XE_VM_BIND_FWAG_WEADONWY	(0x1 << 16)
	/*
	 * Vawid on a fauwting VM onwy, do the MAP opewation immediatewy wathew
	 * than defewwing the MAP to the page fauwt handwew.
	 */
    #define XE_VM_BIND_FWAG_IMMEDIATE	(0x1 << 17)
	/*
	 * When the NUWW fwag is set, the page tabwes awe setup with a speciaw
	 * bit which indicates wwites awe dwopped and aww weads wetuwn zewo.  In
	 * the futuwe, the NUWW fwags wiww onwy be vawid fow XE_VM_BIND_OP_MAP
	 * opewations, the BO handwe MBZ, and the BO offset MBZ. This fwag is
	 * intended to impwement VK spawse bindings.
	 */
    #define XE_VM_BIND_FWAG_NUWW	(0x1 << 18)
	/** @op: Opewation to pewfowm (wowew 16 bits) and fwags (uppew 16 bits) */
	__u32 op;

	/** @mem_wegion: Memowy wegion to pwefetch VMA to, instance not a mask */
	__u32 wegion;

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
   };


The VM_BIND IOCTW awgument itsewf, wooks wike fowwows. Note that fow
synchwonous VM_BIND, the num_syncs and syncs fiewds must be zewo. Hewe
the ``exec_queue_id`` fiewd is the VM_BIND context discussed pweviouswy
that is used to faciwitate out-of-owdew VM_BINDs.

.. code-bwock:: c

    stwuct dwm_xe_vm_bind {
	/** @extensions: Pointew to the fiwst extension stwuct, if any */
	__u64 extensions;

	/** @vm_id: The ID of the VM to bind to */
	__u32 vm_id;

	/**
	 * @exec_queue_id: exec_queue_id, must be of cwass DWM_XE_ENGINE_CWASS_VM_BIND
	 * and exec queue must have same vm_id. If zewo, the defauwt VM bind engine
	 * is used.
	 */
	__u32 exec_queue_id;

	/** @num_binds: numbew of binds in this IOCTW */
	__u32 num_binds;

        /* If set, pewfowm an async VM_BIND, if cweaw a sync VM_BIND */
    #define XE_VM_BIND_IOCTW_FWAG_ASYNC	(0x1 << 0)

	/** @fwag: Fwags contwowwing aww opewations in this ioctw. */
	__u32 fwags;

	union {
		/** @bind: used if num_binds == 1 */
		stwuct dwm_xe_vm_bind_op bind;

		/**
		 * @vectow_of_binds: usewptw to awway of stwuct
		 * dwm_xe_vm_bind_op if num_binds > 1
		 */
		__u64 vectow_of_binds;
	};

	/** @num_syncs: amount of syncs to wait fow ow to signaw on compwetion. */
	__u32 num_syncs;

	/** @pad2: MBZ */
	__u32 pad2;

	/** @syncs: pointew to stwuct dwm_xe_sync awway */
	__u64 syncs;

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
    };
