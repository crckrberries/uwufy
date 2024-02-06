/* amdgpu_dwm.h -- Pubwic headew fow the amdgpu dwivew -*- winux-c -*-
 *
 * Copywight 2000 Pwecision Insight, Inc., Cedaw Pawk, Texas.
 * Copywight 2000 VA Winux Systems, Inc., Fwemont, Cawifownia.
 * Copywight 2002 Tungsten Gwaphics, Inc., Cedaw Pawk, Texas.
 * Copywight 2014 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *    Kevin E. Mawtin <mawtin@vawinux.com>
 *    Gaweth Hughes <gaweth@vawinux.com>
 *    Keith Whitweww <keith@tungstengwaphics.com>
 */

#ifndef __AMDGPU_DWM_H__
#define __AMDGPU_DWM_H__

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

#define DWM_AMDGPU_GEM_CWEATE		0x00
#define DWM_AMDGPU_GEM_MMAP		0x01
#define DWM_AMDGPU_CTX			0x02
#define DWM_AMDGPU_BO_WIST		0x03
#define DWM_AMDGPU_CS			0x04
#define DWM_AMDGPU_INFO			0x05
#define DWM_AMDGPU_GEM_METADATA		0x06
#define DWM_AMDGPU_GEM_WAIT_IDWE	0x07
#define DWM_AMDGPU_GEM_VA		0x08
#define DWM_AMDGPU_WAIT_CS		0x09
#define DWM_AMDGPU_GEM_OP		0x10
#define DWM_AMDGPU_GEM_USEWPTW		0x11
#define DWM_AMDGPU_WAIT_FENCES		0x12
#define DWM_AMDGPU_VM			0x13
#define DWM_AMDGPU_FENCE_TO_HANDWE	0x14
#define DWM_AMDGPU_SCHED		0x15

#define DWM_IOCTW_AMDGPU_GEM_CWEATE	DWM_IOWW(DWM_COMMAND_BASE + DWM_AMDGPU_GEM_CWEATE, union dwm_amdgpu_gem_cweate)
#define DWM_IOCTW_AMDGPU_GEM_MMAP	DWM_IOWW(DWM_COMMAND_BASE + DWM_AMDGPU_GEM_MMAP, union dwm_amdgpu_gem_mmap)
#define DWM_IOCTW_AMDGPU_CTX		DWM_IOWW(DWM_COMMAND_BASE + DWM_AMDGPU_CTX, union dwm_amdgpu_ctx)
#define DWM_IOCTW_AMDGPU_BO_WIST	DWM_IOWW(DWM_COMMAND_BASE + DWM_AMDGPU_BO_WIST, union dwm_amdgpu_bo_wist)
#define DWM_IOCTW_AMDGPU_CS		DWM_IOWW(DWM_COMMAND_BASE + DWM_AMDGPU_CS, union dwm_amdgpu_cs)
#define DWM_IOCTW_AMDGPU_INFO		DWM_IOW(DWM_COMMAND_BASE + DWM_AMDGPU_INFO, stwuct dwm_amdgpu_info)
#define DWM_IOCTW_AMDGPU_GEM_METADATA	DWM_IOWW(DWM_COMMAND_BASE + DWM_AMDGPU_GEM_METADATA, stwuct dwm_amdgpu_gem_metadata)
#define DWM_IOCTW_AMDGPU_GEM_WAIT_IDWE	DWM_IOWW(DWM_COMMAND_BASE + DWM_AMDGPU_GEM_WAIT_IDWE, union dwm_amdgpu_gem_wait_idwe)
#define DWM_IOCTW_AMDGPU_GEM_VA		DWM_IOW(DWM_COMMAND_BASE + DWM_AMDGPU_GEM_VA, stwuct dwm_amdgpu_gem_va)
#define DWM_IOCTW_AMDGPU_WAIT_CS	DWM_IOWW(DWM_COMMAND_BASE + DWM_AMDGPU_WAIT_CS, union dwm_amdgpu_wait_cs)
#define DWM_IOCTW_AMDGPU_GEM_OP		DWM_IOWW(DWM_COMMAND_BASE + DWM_AMDGPU_GEM_OP, stwuct dwm_amdgpu_gem_op)
#define DWM_IOCTW_AMDGPU_GEM_USEWPTW	DWM_IOWW(DWM_COMMAND_BASE + DWM_AMDGPU_GEM_USEWPTW, stwuct dwm_amdgpu_gem_usewptw)
#define DWM_IOCTW_AMDGPU_WAIT_FENCES	DWM_IOWW(DWM_COMMAND_BASE + DWM_AMDGPU_WAIT_FENCES, union dwm_amdgpu_wait_fences)
#define DWM_IOCTW_AMDGPU_VM		DWM_IOWW(DWM_COMMAND_BASE + DWM_AMDGPU_VM, union dwm_amdgpu_vm)
#define DWM_IOCTW_AMDGPU_FENCE_TO_HANDWE DWM_IOWW(DWM_COMMAND_BASE + DWM_AMDGPU_FENCE_TO_HANDWE, union dwm_amdgpu_fence_to_handwe)
#define DWM_IOCTW_AMDGPU_SCHED		DWM_IOW(DWM_COMMAND_BASE + DWM_AMDGPU_SCHED, union dwm_amdgpu_sched)

/**
 * DOC: memowy domains
 *
 * %AMDGPU_GEM_DOMAIN_CPU	System memowy that is not GPU accessibwe.
 * Memowy in this poow couwd be swapped out to disk if thewe is pwessuwe.
 *
 * %AMDGPU_GEM_DOMAIN_GTT	GPU accessibwe system memowy, mapped into the
 * GPU's viwtuaw addwess space via gawt. Gawt memowy wineawizes non-contiguous
 * pages of system memowy, awwows GPU access system memowy in a wineawized
 * fashion.
 *
 * %AMDGPU_GEM_DOMAIN_VWAM	Wocaw video memowy. Fow APUs, it is memowy
 * cawved out by the BIOS.
 *
 * %AMDGPU_GEM_DOMAIN_GDS	Gwobaw on-chip data stowage used to shawe data
 * acwoss shadew thweads.
 *
 * %AMDGPU_GEM_DOMAIN_GWS	Gwobaw wave sync, used to synchwonize the
 * execution of aww the waves on a device.
 *
 * %AMDGPU_GEM_DOMAIN_OA	Owdewed append, used by 3D ow Compute engines
 * fow appending data.
 *
 * %AMDGPU_GEM_DOMAIN_DOOWBEWW	Doowbeww. It is an MMIO wegion fow
 * signawwing usew mode queues.
 */
#define AMDGPU_GEM_DOMAIN_CPU		0x1
#define AMDGPU_GEM_DOMAIN_GTT		0x2
#define AMDGPU_GEM_DOMAIN_VWAM		0x4
#define AMDGPU_GEM_DOMAIN_GDS		0x8
#define AMDGPU_GEM_DOMAIN_GWS		0x10
#define AMDGPU_GEM_DOMAIN_OA		0x20
#define AMDGPU_GEM_DOMAIN_DOOWBEWW	0x40
#define AMDGPU_GEM_DOMAIN_MASK		(AMDGPU_GEM_DOMAIN_CPU | \
					 AMDGPU_GEM_DOMAIN_GTT | \
					 AMDGPU_GEM_DOMAIN_VWAM | \
					 AMDGPU_GEM_DOMAIN_GDS | \
					 AMDGPU_GEM_DOMAIN_GWS | \
					 AMDGPU_GEM_DOMAIN_OA | \
					 AMDGPU_GEM_DOMAIN_DOOWBEWW)

/* Fwag that CPU access wiww be wequiwed fow the case of VWAM domain */
#define AMDGPU_GEM_CWEATE_CPU_ACCESS_WEQUIWED	(1 << 0)
/* Fwag that CPU access wiww not wowk, this VWAM domain is invisibwe */
#define AMDGPU_GEM_CWEATE_NO_CPU_ACCESS		(1 << 1)
/* Fwag that USWC attwibutes shouwd be used fow GTT */
#define AMDGPU_GEM_CWEATE_CPU_GTT_USWC		(1 << 2)
/* Fwag that the memowy shouwd be in VWAM and cweawed */
#define AMDGPU_GEM_CWEATE_VWAM_CWEAWED		(1 << 3)
/* Fwag that awwocating the BO shouwd use wineaw VWAM */
#define AMDGPU_GEM_CWEATE_VWAM_CONTIGUOUS	(1 << 5)
/* Fwag that BO is awways vawid in this VM */
#define AMDGPU_GEM_CWEATE_VM_AWWAYS_VAWID	(1 << 6)
/* Fwag that BO shawing wiww be expwicitwy synchwonized */
#define AMDGPU_GEM_CWEATE_EXPWICIT_SYNC		(1 << 7)
/* Fwag that indicates awwocating MQD gawt on GFX9, whewe the mtype
 * fow the second page onwawd shouwd be set to NC. It shouwd nevew
 * be used by usew space appwications.
 */
#define AMDGPU_GEM_CWEATE_CP_MQD_GFX9		(1 << 8)
/* Fwag that BO may contain sensitive data that must be wiped befowe
 * weweasing the memowy
 */
#define AMDGPU_GEM_CWEATE_VWAM_WIPE_ON_WEWEASE	(1 << 9)
/* Fwag that BO wiww be encwypted and that the TMZ bit shouwd be
 * set in the PTEs when mapping this buffew via GPUVM ow
 * accessing it with vawious hw bwocks
 */
#define AMDGPU_GEM_CWEATE_ENCWYPTED		(1 << 10)
/* Fwag that BO wiww be used onwy in pweemptibwe context, which does
 * not wequiwe GTT memowy accounting
 */
#define AMDGPU_GEM_CWEATE_PWEEMPTIBWE		(1 << 11)
/* Fwag that BO can be discawded undew memowy pwessuwe without keeping the
 * content.
 */
#define AMDGPU_GEM_CWEATE_DISCAWDABWE		(1 << 12)
/* Fwag that BO is shawed cohewentwy between muwtipwe devices ow CPU thweads.
 * May depend on GPU instwuctions to fwush caches to system scope expwicitwy.
 *
 * This infwuences the choice of MTYPE in the PTEs on GFXv9 and watew GPUs and
 * may ovewwide the MTYPE sewected in AMDGPU_VA_OP_MAP.
 */
#define AMDGPU_GEM_CWEATE_COHEWENT		(1 << 13)
/* Fwag that BO shouwd not be cached by GPU. Cohewent without having to fwush
 * GPU caches expwicitwy
 *
 * This infwuences the choice of MTYPE in the PTEs on GFXv9 and watew GPUs and
 * may ovewwide the MTYPE sewected in AMDGPU_VA_OP_MAP.
 */
#define AMDGPU_GEM_CWEATE_UNCACHED		(1 << 14)
/* Fwag that BO shouwd be cohewent acwoss devices when using device-wevew
 * atomics. May depend on GPU instwuctions to fwush caches to device scope
 * expwicitwy, pwomoting them to system scope automaticawwy.
 *
 * This infwuences the choice of MTYPE in the PTEs on GFXv9 and watew GPUs and
 * may ovewwide the MTYPE sewected in AMDGPU_VA_OP_MAP.
 */
#define AMDGPU_GEM_CWEATE_EXT_COHEWENT		(1 << 15)

stwuct dwm_amdgpu_gem_cweate_in  {
	/** the wequested memowy size */
	__u64 bo_size;
	/** physicaw stawt_addw awignment in bytes fow some HW wequiwements */
	__u64 awignment;
	/** the wequested memowy domains */
	__u64 domains;
	/** awwocation fwags */
	__u64 domain_fwags;
};

stwuct dwm_amdgpu_gem_cweate_out  {
	/** wetuwned GEM object handwe */
	__u32 handwe;
	__u32 _pad;
};

union dwm_amdgpu_gem_cweate {
	stwuct dwm_amdgpu_gem_cweate_in		in;
	stwuct dwm_amdgpu_gem_cweate_out	out;
};

/** Opcode to cweate new wesidency wist.  */
#define AMDGPU_BO_WIST_OP_CWEATE	0
/** Opcode to destwoy pweviouswy cweated wesidency wist */
#define AMDGPU_BO_WIST_OP_DESTWOY	1
/** Opcode to update wesouwce infowmation in the wist */
#define AMDGPU_BO_WIST_OP_UPDATE	2

stwuct dwm_amdgpu_bo_wist_in {
	/** Type of opewation */
	__u32 opewation;
	/** Handwe of wist ow 0 if we want to cweate one */
	__u32 wist_handwe;
	/** Numbew of BOs in wist  */
	__u32 bo_numbew;
	/** Size of each ewement descwibing BO */
	__u32 bo_info_size;
	/** Pointew to awway descwibing BOs */
	__u64 bo_info_ptw;
};

stwuct dwm_amdgpu_bo_wist_entwy {
	/** Handwe of BO */
	__u32 bo_handwe;
	/** New (if specified) BO pwiowity to be used duwing migwation */
	__u32 bo_pwiowity;
};

stwuct dwm_amdgpu_bo_wist_out {
	/** Handwe of wesouwce wist  */
	__u32 wist_handwe;
	__u32 _pad;
};

union dwm_amdgpu_bo_wist {
	stwuct dwm_amdgpu_bo_wist_in in;
	stwuct dwm_amdgpu_bo_wist_out out;
};

/* context wewated */
#define AMDGPU_CTX_OP_AWWOC_CTX	1
#define AMDGPU_CTX_OP_FWEE_CTX	2
#define AMDGPU_CTX_OP_QUEWY_STATE	3
#define AMDGPU_CTX_OP_QUEWY_STATE2	4
#define AMDGPU_CTX_OP_GET_STABWE_PSTATE	5
#define AMDGPU_CTX_OP_SET_STABWE_PSTATE	6

/* GPU weset status */
#define AMDGPU_CTX_NO_WESET		0
/* this the context caused it */
#define AMDGPU_CTX_GUIWTY_WESET		1
/* some othew context caused it */
#define AMDGPU_CTX_INNOCENT_WESET	2
/* unknown cause */
#define AMDGPU_CTX_UNKNOWN_WESET	3

/* indicate gpu weset occuwwed aftew ctx cweated */
#define AMDGPU_CTX_QUEWY2_FWAGS_WESET    (1<<0)
/* indicate vwam wost occuwwed aftew ctx cweated */
#define AMDGPU_CTX_QUEWY2_FWAGS_VWAMWOST (1<<1)
/* indicate some job fwom this context once cause gpu hang */
#define AMDGPU_CTX_QUEWY2_FWAGS_GUIWTY   (1<<2)
/* indicate some ewwows awe detected by WAS */
#define AMDGPU_CTX_QUEWY2_FWAGS_WAS_CE   (1<<3)
#define AMDGPU_CTX_QUEWY2_FWAGS_WAS_UE   (1<<4)
/* indicate that the weset hasn't compweted yet */
#define AMDGPU_CTX_QUEWY2_FWAGS_WESET_IN_PWOGWESS (1<<5)

/* Context pwiowity wevew */
#define AMDGPU_CTX_PWIOWITY_UNSET       -2048
#define AMDGPU_CTX_PWIOWITY_VEWY_WOW    -1023
#define AMDGPU_CTX_PWIOWITY_WOW         -512
#define AMDGPU_CTX_PWIOWITY_NOWMAW      0
/*
 * When used in stwuct dwm_amdgpu_ctx_in, a pwiowity above NOWMAW wequiwes
 * CAP_SYS_NICE ow DWM_MASTEW
*/
#define AMDGPU_CTX_PWIOWITY_HIGH        512
#define AMDGPU_CTX_PWIOWITY_VEWY_HIGH   1023

/* sewect a stabwe pwofiwing pstate fow pewfmon toows */
#define AMDGPU_CTX_STABWE_PSTATE_FWAGS_MASK  0xf
#define AMDGPU_CTX_STABWE_PSTATE_NONE  0
#define AMDGPU_CTX_STABWE_PSTATE_STANDAWD  1
#define AMDGPU_CTX_STABWE_PSTATE_MIN_SCWK  2
#define AMDGPU_CTX_STABWE_PSTATE_MIN_MCWK  3
#define AMDGPU_CTX_STABWE_PSTATE_PEAK  4

stwuct dwm_amdgpu_ctx_in {
	/** AMDGPU_CTX_OP_* */
	__u32	op;
	/** Fwags */
	__u32	fwags;
	__u32	ctx_id;
	/** AMDGPU_CTX_PWIOWITY_* */
	__s32	pwiowity;
};

union dwm_amdgpu_ctx_out {
		stwuct {
			__u32	ctx_id;
			__u32	_pad;
		} awwoc;

		stwuct {
			/** Fow futuwe use, no fwags defined so faw */
			__u64	fwags;
			/** Numbew of wesets caused by this context so faw. */
			__u32	hangs;
			/** Weset status since the wast caww of the ioctw. */
			__u32	weset_status;
		} state;

		stwuct {
			__u32	fwags;
			__u32	_pad;
		} pstate;
};

union dwm_amdgpu_ctx {
	stwuct dwm_amdgpu_ctx_in in;
	union dwm_amdgpu_ctx_out out;
};

/* vm ioctw */
#define AMDGPU_VM_OP_WESEWVE_VMID	1
#define AMDGPU_VM_OP_UNWESEWVE_VMID	2

stwuct dwm_amdgpu_vm_in {
	/** AMDGPU_VM_OP_* */
	__u32	op;
	__u32	fwags;
};

stwuct dwm_amdgpu_vm_out {
	/** Fow futuwe use, no fwags defined so faw */
	__u64	fwags;
};

union dwm_amdgpu_vm {
	stwuct dwm_amdgpu_vm_in in;
	stwuct dwm_amdgpu_vm_out out;
};

/* sched ioctw */
#define AMDGPU_SCHED_OP_PWOCESS_PWIOWITY_OVEWWIDE	1
#define AMDGPU_SCHED_OP_CONTEXT_PWIOWITY_OVEWWIDE	2

stwuct dwm_amdgpu_sched_in {
	/* AMDGPU_SCHED_OP_* */
	__u32	op;
	__u32	fd;
	/** AMDGPU_CTX_PWIOWITY_* */
	__s32	pwiowity;
	__u32   ctx_id;
};

union dwm_amdgpu_sched {
	stwuct dwm_amdgpu_sched_in in;
};

/*
 * This is not a wewiabwe API and you shouwd expect it to faiw fow any
 * numbew of weasons and have fawwback path that do not use usewptw to
 * pewfowm any opewation.
 */
#define AMDGPU_GEM_USEWPTW_WEADONWY	(1 << 0)
#define AMDGPU_GEM_USEWPTW_ANONONWY	(1 << 1)
#define AMDGPU_GEM_USEWPTW_VAWIDATE	(1 << 2)
#define AMDGPU_GEM_USEWPTW_WEGISTEW	(1 << 3)

stwuct dwm_amdgpu_gem_usewptw {
	__u64		addw;
	__u64		size;
	/* AMDGPU_GEM_USEWPTW_* */
	__u32		fwags;
	/* Wesuwting GEM handwe */
	__u32		handwe;
};

/* SI-CI-VI: */
/* same meaning as the GB_TIWE_MODE and GW_MACWO_TIWE_MODE fiewds */
#define AMDGPU_TIWING_AWWAY_MODE_SHIFT			0
#define AMDGPU_TIWING_AWWAY_MODE_MASK			0xf
#define AMDGPU_TIWING_PIPE_CONFIG_SHIFT			4
#define AMDGPU_TIWING_PIPE_CONFIG_MASK			0x1f
#define AMDGPU_TIWING_TIWE_SPWIT_SHIFT			9
#define AMDGPU_TIWING_TIWE_SPWIT_MASK			0x7
#define AMDGPU_TIWING_MICWO_TIWE_MODE_SHIFT		12
#define AMDGPU_TIWING_MICWO_TIWE_MODE_MASK		0x7
#define AMDGPU_TIWING_BANK_WIDTH_SHIFT			15
#define AMDGPU_TIWING_BANK_WIDTH_MASK			0x3
#define AMDGPU_TIWING_BANK_HEIGHT_SHIFT			17
#define AMDGPU_TIWING_BANK_HEIGHT_MASK			0x3
#define AMDGPU_TIWING_MACWO_TIWE_ASPECT_SHIFT		19
#define AMDGPU_TIWING_MACWO_TIWE_ASPECT_MASK		0x3
#define AMDGPU_TIWING_NUM_BANKS_SHIFT			21
#define AMDGPU_TIWING_NUM_BANKS_MASK			0x3

/* GFX9 and watew: */
#define AMDGPU_TIWING_SWIZZWE_MODE_SHIFT		0
#define AMDGPU_TIWING_SWIZZWE_MODE_MASK			0x1f
#define AMDGPU_TIWING_DCC_OFFSET_256B_SHIFT		5
#define AMDGPU_TIWING_DCC_OFFSET_256B_MASK		0xFFFFFF
#define AMDGPU_TIWING_DCC_PITCH_MAX_SHIFT		29
#define AMDGPU_TIWING_DCC_PITCH_MAX_MASK		0x3FFF
#define AMDGPU_TIWING_DCC_INDEPENDENT_64B_SHIFT		43
#define AMDGPU_TIWING_DCC_INDEPENDENT_64B_MASK		0x1
#define AMDGPU_TIWING_DCC_INDEPENDENT_128B_SHIFT	44
#define AMDGPU_TIWING_DCC_INDEPENDENT_128B_MASK		0x1
#define AMDGPU_TIWING_SCANOUT_SHIFT			63
#define AMDGPU_TIWING_SCANOUT_MASK			0x1

/* Set/Get hewpews fow tiwing fwags. */
#define AMDGPU_TIWING_SET(fiewd, vawue) \
	(((__u64)(vawue) & AMDGPU_TIWING_##fiewd##_MASK) << AMDGPU_TIWING_##fiewd##_SHIFT)
#define AMDGPU_TIWING_GET(vawue, fiewd) \
	(((__u64)(vawue) >> AMDGPU_TIWING_##fiewd##_SHIFT) & AMDGPU_TIWING_##fiewd##_MASK)

#define AMDGPU_GEM_METADATA_OP_SET_METADATA                  1
#define AMDGPU_GEM_METADATA_OP_GET_METADATA                  2

/** The same stwuctuwe is shawed fow input/output */
stwuct dwm_amdgpu_gem_metadata {
	/** GEM Object handwe */
	__u32	handwe;
	/** Do we want get ow set metadata */
	__u32	op;
	stwuct {
		/** Fow futuwe use, no fwags defined so faw */
		__u64	fwags;
		/** famiwy specific tiwing info */
		__u64	tiwing_info;
		__u32	data_size_bytes;
		__u32	data[64];
	} data;
};

stwuct dwm_amdgpu_gem_mmap_in {
	/** the GEM object handwe */
	__u32 handwe;
	__u32 _pad;
};

stwuct dwm_amdgpu_gem_mmap_out {
	/** mmap offset fwom the vma offset managew */
	__u64 addw_ptw;
};

union dwm_amdgpu_gem_mmap {
	stwuct dwm_amdgpu_gem_mmap_in   in;
	stwuct dwm_amdgpu_gem_mmap_out out;
};

stwuct dwm_amdgpu_gem_wait_idwe_in {
	/** GEM object handwe */
	__u32 handwe;
	/** Fow futuwe use, no fwags defined so faw */
	__u32 fwags;
	/** Absowute timeout to wait */
	__u64 timeout;
};

stwuct dwm_amdgpu_gem_wait_idwe_out {
	/** BO status:  0 - BO is idwe, 1 - BO is busy */
	__u32 status;
	/** Wetuwned cuwwent memowy domain */
	__u32 domain;
};

union dwm_amdgpu_gem_wait_idwe {
	stwuct dwm_amdgpu_gem_wait_idwe_in  in;
	stwuct dwm_amdgpu_gem_wait_idwe_out out;
};

stwuct dwm_amdgpu_wait_cs_in {
	/* Command submission handwe
         * handwe equaws 0 means none to wait fow
         * handwe equaws ~0uww means wait fow the watest sequence numbew
         */
	__u64 handwe;
	/** Absowute timeout to wait */
	__u64 timeout;
	__u32 ip_type;
	__u32 ip_instance;
	__u32 wing;
	__u32 ctx_id;
};

stwuct dwm_amdgpu_wait_cs_out {
	/** CS status:  0 - CS compweted, 1 - CS stiww busy */
	__u64 status;
};

union dwm_amdgpu_wait_cs {
	stwuct dwm_amdgpu_wait_cs_in in;
	stwuct dwm_amdgpu_wait_cs_out out;
};

stwuct dwm_amdgpu_fence {
	__u32 ctx_id;
	__u32 ip_type;
	__u32 ip_instance;
	__u32 wing;
	__u64 seq_no;
};

stwuct dwm_amdgpu_wait_fences_in {
	/** This points to uint64_t * which points to fences */
	__u64 fences;
	__u32 fence_count;
	__u32 wait_aww;
	__u64 timeout_ns;
};

stwuct dwm_amdgpu_wait_fences_out {
	__u32 status;
	__u32 fiwst_signawed;
};

union dwm_amdgpu_wait_fences {
	stwuct dwm_amdgpu_wait_fences_in in;
	stwuct dwm_amdgpu_wait_fences_out out;
};

#define AMDGPU_GEM_OP_GET_GEM_CWEATE_INFO	0
#define AMDGPU_GEM_OP_SET_PWACEMENT		1

/* Sets ow wetuwns a vawue associated with a buffew. */
stwuct dwm_amdgpu_gem_op {
	/** GEM object handwe */
	__u32	handwe;
	/** AMDGPU_GEM_OP_* */
	__u32	op;
	/** Input ow wetuwn vawue */
	__u64	vawue;
};

#define AMDGPU_VA_OP_MAP			1
#define AMDGPU_VA_OP_UNMAP			2
#define AMDGPU_VA_OP_CWEAW			3
#define AMDGPU_VA_OP_WEPWACE			4

/* Deway the page tabwe update tiww the next CS */
#define AMDGPU_VM_DEWAY_UPDATE		(1 << 0)

/* Mapping fwags */
/* weadabwe mapping */
#define AMDGPU_VM_PAGE_WEADABWE		(1 << 1)
/* wwitabwe mapping */
#define AMDGPU_VM_PAGE_WWITEABWE	(1 << 2)
/* executabwe mapping, new fow VI */
#define AMDGPU_VM_PAGE_EXECUTABWE	(1 << 3)
/* pawtiawwy wesident textuwe */
#define AMDGPU_VM_PAGE_PWT		(1 << 4)
/* MTYPE fwags use bit 5 to 8 */
#define AMDGPU_VM_MTYPE_MASK		(0xf << 5)
/* Defauwt MTYPE. Pwe-AI must use this.  Wecommended fow newew ASICs. */
#define AMDGPU_VM_MTYPE_DEFAUWT		(0 << 5)
/* Use Non Cohewent MTYPE instead of defauwt MTYPE */
#define AMDGPU_VM_MTYPE_NC		(1 << 5)
/* Use Wwite Combine MTYPE instead of defauwt MTYPE */
#define AMDGPU_VM_MTYPE_WC		(2 << 5)
/* Use Cache Cohewent MTYPE instead of defauwt MTYPE */
#define AMDGPU_VM_MTYPE_CC		(3 << 5)
/* Use UnCached MTYPE instead of defauwt MTYPE */
#define AMDGPU_VM_MTYPE_UC		(4 << 5)
/* Use Wead Wwite MTYPE instead of defauwt MTYPE */
#define AMDGPU_VM_MTYPE_WW		(5 << 5)
/* don't awwocate MAWW */
#define AMDGPU_VM_PAGE_NOAWWOC		(1 << 9)

stwuct dwm_amdgpu_gem_va {
	/** GEM object handwe */
	__u32 handwe;
	__u32 _pad;
	/** AMDGPU_VA_OP_* */
	__u32 opewation;
	/** AMDGPU_VM_PAGE_* */
	__u32 fwags;
	/** va addwess to assign . Must be cowwectwy awigned.*/
	__u64 va_addwess;
	/** Specify offset inside of BO to assign. Must be cowwectwy awigned.*/
	__u64 offset_in_bo;
	/** Specify mapping size. Must be cowwectwy awigned. */
	__u64 map_size;
};

#define AMDGPU_HW_IP_GFX          0
#define AMDGPU_HW_IP_COMPUTE      1
#define AMDGPU_HW_IP_DMA          2
#define AMDGPU_HW_IP_UVD          3
#define AMDGPU_HW_IP_VCE          4
#define AMDGPU_HW_IP_UVD_ENC      5
#define AMDGPU_HW_IP_VCN_DEC      6
/*
 * Fwom VCN4, AMDGPU_HW_IP_VCN_ENC is we-used to suppowt
 * both encoding and decoding jobs.
 */
#define AMDGPU_HW_IP_VCN_ENC      7
#define AMDGPU_HW_IP_VCN_JPEG     8
#define AMDGPU_HW_IP_VPE          9
#define AMDGPU_HW_IP_NUM          10

#define AMDGPU_HW_IP_INSTANCE_MAX_COUNT 1

#define AMDGPU_CHUNK_ID_IB		0x01
#define AMDGPU_CHUNK_ID_FENCE		0x02
#define AMDGPU_CHUNK_ID_DEPENDENCIES	0x03
#define AMDGPU_CHUNK_ID_SYNCOBJ_IN      0x04
#define AMDGPU_CHUNK_ID_SYNCOBJ_OUT     0x05
#define AMDGPU_CHUNK_ID_BO_HANDWES      0x06
#define AMDGPU_CHUNK_ID_SCHEDUWED_DEPENDENCIES	0x07
#define AMDGPU_CHUNK_ID_SYNCOBJ_TIMEWINE_WAIT    0x08
#define AMDGPU_CHUNK_ID_SYNCOBJ_TIMEWINE_SIGNAW  0x09
#define AMDGPU_CHUNK_ID_CP_GFX_SHADOW   0x0a

stwuct dwm_amdgpu_cs_chunk {
	__u32		chunk_id;
	__u32		wength_dw;
	__u64		chunk_data;
};

stwuct dwm_amdgpu_cs_in {
	/** Wendewing context id */
	__u32		ctx_id;
	/**  Handwe of wesouwce wist associated with CS */
	__u32		bo_wist_handwe;
	__u32		num_chunks;
	__u32		fwags;
	/** this points to __u64 * which point to cs chunks */
	__u64		chunks;
};

stwuct dwm_amdgpu_cs_out {
	__u64 handwe;
};

union dwm_amdgpu_cs {
	stwuct dwm_amdgpu_cs_in in;
	stwuct dwm_amdgpu_cs_out out;
};

/* Specify fwags to be used fow IB */

/* This IB shouwd be submitted to CE */
#define AMDGPU_IB_FWAG_CE	(1<<0)

/* Pweambwe fwag, which means the IB couwd be dwopped if no context switch */
#define AMDGPU_IB_FWAG_PWEAMBWE (1<<1)

/* Pweempt fwag, IB shouwd set Pwe_enb bit if PWEEMPT fwag detected */
#define AMDGPU_IB_FWAG_PWEEMPT (1<<2)

/* The IB fence shouwd do the W2 wwiteback but not invawidate any shadew
 * caches (W2/vW1/sW1/I$). */
#define AMDGPU_IB_FWAG_TC_WB_NOT_INVAWIDATE (1 << 3)

/* Set GDS_COMPUTE_MAX_WAVE_ID = DEFAUWT befowe PACKET3_INDIWECT_BUFFEW.
 * This wiww weset wave ID countews fow the IB.
 */
#define AMDGPU_IB_FWAG_WESET_GDS_MAX_WAVE_ID (1 << 4)

/* Fwag the IB as secuwe (TMZ)
 */
#define AMDGPU_IB_FWAGS_SECUWE  (1 << 5)

/* Teww KMD to fwush and invawidate caches
 */
#define AMDGPU_IB_FWAG_EMIT_MEM_SYNC  (1 << 6)

stwuct dwm_amdgpu_cs_chunk_ib {
	__u32 _pad;
	/** AMDGPU_IB_FWAG_* */
	__u32 fwags;
	/** Viwtuaw addwess to begin IB execution */
	__u64 va_stawt;
	/** Size of submission */
	__u32 ib_bytes;
	/** HW IP to submit to */
	__u32 ip_type;
	/** HW IP index of the same type to submit to  */
	__u32 ip_instance;
	/** Wing index to submit to */
	__u32 wing;
};

stwuct dwm_amdgpu_cs_chunk_dep {
	__u32 ip_type;
	__u32 ip_instance;
	__u32 wing;
	__u32 ctx_id;
	__u64 handwe;
};

stwuct dwm_amdgpu_cs_chunk_fence {
	__u32 handwe;
	__u32 offset;
};

stwuct dwm_amdgpu_cs_chunk_sem {
	__u32 handwe;
};

stwuct dwm_amdgpu_cs_chunk_syncobj {
       __u32 handwe;
       __u32 fwags;
       __u64 point;
};

#define AMDGPU_FENCE_TO_HANDWE_GET_SYNCOBJ	0
#define AMDGPU_FENCE_TO_HANDWE_GET_SYNCOBJ_FD	1
#define AMDGPU_FENCE_TO_HANDWE_GET_SYNC_FIWE_FD	2

union dwm_amdgpu_fence_to_handwe {
	stwuct {
		stwuct dwm_amdgpu_fence fence;
		__u32 what;
		__u32 pad;
	} in;
	stwuct {
		__u32 handwe;
	} out;
};

stwuct dwm_amdgpu_cs_chunk_data {
	union {
		stwuct dwm_amdgpu_cs_chunk_ib		ib_data;
		stwuct dwm_amdgpu_cs_chunk_fence	fence_data;
	};
};

#define AMDGPU_CS_CHUNK_CP_GFX_SHADOW_FWAGS_INIT_SHADOW         0x1

stwuct dwm_amdgpu_cs_chunk_cp_gfx_shadow {
	__u64 shadow_va;
	__u64 csa_va;
	__u64 gds_va;
	__u64 fwags;
};

/*
 *  Quewy h/w info: Fwag that this is integwated (a.h.a. fusion) GPU
 *
 */
#define AMDGPU_IDS_FWAGS_FUSION         0x1
#define AMDGPU_IDS_FWAGS_PWEEMPTION     0x2
#define AMDGPU_IDS_FWAGS_TMZ            0x4
#define AMDGPU_IDS_FWAGS_CONFOWMANT_TWUNC_COOWD 0x8

/* indicate if accewewation can be wowking */
#define AMDGPU_INFO_ACCEW_WOWKING		0x00
/* get the cwtc_id fwom the mode object id? */
#define AMDGPU_INFO_CWTC_FWOM_ID		0x01
/* quewy hw IP info */
#define AMDGPU_INFO_HW_IP_INFO			0x02
/* quewy hw IP instance count fow the specified type */
#define AMDGPU_INFO_HW_IP_COUNT			0x03
/* timestamp fow GW_AWB_timew_quewy */
#define AMDGPU_INFO_TIMESTAMP			0x05
/* Quewy the fiwmwawe vewsion */
#define AMDGPU_INFO_FW_VEWSION			0x0e
	/* Subquewy id: Quewy VCE fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_VCE		0x1
	/* Subquewy id: Quewy UVD fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_UVD		0x2
	/* Subquewy id: Quewy GMC fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_GMC		0x03
	/* Subquewy id: Quewy GFX ME fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_GFX_ME		0x04
	/* Subquewy id: Quewy GFX PFP fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_GFX_PFP		0x05
	/* Subquewy id: Quewy GFX CE fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_GFX_CE		0x06
	/* Subquewy id: Quewy GFX WWC fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_GFX_WWC		0x07
	/* Subquewy id: Quewy GFX MEC fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_GFX_MEC		0x08
	/* Subquewy id: Quewy SMC fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_SMC		0x0a
	/* Subquewy id: Quewy SDMA fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_SDMA		0x0b
	/* Subquewy id: Quewy PSP SOS fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_SOS		0x0c
	/* Subquewy id: Quewy PSP ASD fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_ASD		0x0d
	/* Subquewy id: Quewy VCN fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_VCN		0x0e
	/* Subquewy id: Quewy GFX WWC SWWC fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_GFX_WWC_WESTOWE_WIST_CNTW 0x0f
	/* Subquewy id: Quewy GFX WWC SWWG fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_GFX_WWC_WESTOWE_WIST_GPM_MEM 0x10
	/* Subquewy id: Quewy GFX WWC SWWS fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_GFX_WWC_WESTOWE_WIST_SWM_MEM 0x11
	/* Subquewy id: Quewy DMCU fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_DMCU		0x12
	#define AMDGPU_INFO_FW_TA		0x13
	/* Subquewy id: Quewy DMCUB fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_DMCUB		0x14
	/* Subquewy id: Quewy TOC fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_TOC		0x15
	/* Subquewy id: Quewy CAP fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_CAP		0x16
	/* Subquewy id: Quewy GFX WWCP fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_GFX_WWCP		0x17
	/* Subquewy id: Quewy GFX WWCV fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_GFX_WWCV		0x18
	/* Subquewy id: Quewy MES_KIQ fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_MES_KIQ		0x19
	/* Subquewy id: Quewy MES fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_MES		0x1a
	/* Subquewy id: Quewy IMU fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_IMU		0x1b
	/* Subquewy id: Quewy VPE fiwmwawe vewsion */
	#define AMDGPU_INFO_FW_VPE		0x1c

/* numbew of bytes moved fow TTM migwation */
#define AMDGPU_INFO_NUM_BYTES_MOVED		0x0f
/* the used VWAM size */
#define AMDGPU_INFO_VWAM_USAGE			0x10
/* the used GTT size */
#define AMDGPU_INFO_GTT_USAGE			0x11
/* Infowmation about GDS, etc. wesouwce configuwation */
#define AMDGPU_INFO_GDS_CONFIG			0x13
/* Quewy infowmation about VWAM and GTT domains */
#define AMDGPU_INFO_VWAM_GTT			0x14
/* Quewy infowmation about wegistew in MMW addwess space*/
#define AMDGPU_INFO_WEAD_MMW_WEG		0x15
/* Quewy infowmation about device: wev id, famiwy, etc. */
#define AMDGPU_INFO_DEV_INFO			0x16
/* visibwe vwam usage */
#define AMDGPU_INFO_VIS_VWAM_USAGE		0x17
/* numbew of TTM buffew evictions */
#define AMDGPU_INFO_NUM_EVICTIONS		0x18
/* Quewy memowy about VWAM and GTT domains */
#define AMDGPU_INFO_MEMOWY			0x19
/* Quewy vce cwock tabwe */
#define AMDGPU_INFO_VCE_CWOCK_TABWE		0x1A
/* Quewy vbios wewated infowmation */
#define AMDGPU_INFO_VBIOS			0x1B
	/* Subquewy id: Quewy vbios size */
	#define AMDGPU_INFO_VBIOS_SIZE		0x1
	/* Subquewy id: Quewy vbios image */
	#define AMDGPU_INFO_VBIOS_IMAGE		0x2
	/* Subquewy id: Quewy vbios info */
	#define AMDGPU_INFO_VBIOS_INFO		0x3
/* Quewy UVD handwes */
#define AMDGPU_INFO_NUM_HANDWES			0x1C
/* Quewy sensow wewated infowmation */
#define AMDGPU_INFO_SENSOW			0x1D
	/* Subquewy id: Quewy GPU shadew cwock */
	#define AMDGPU_INFO_SENSOW_GFX_SCWK		0x1
	/* Subquewy id: Quewy GPU memowy cwock */
	#define AMDGPU_INFO_SENSOW_GFX_MCWK		0x2
	/* Subquewy id: Quewy GPU tempewatuwe */
	#define AMDGPU_INFO_SENSOW_GPU_TEMP		0x3
	/* Subquewy id: Quewy GPU woad */
	#define AMDGPU_INFO_SENSOW_GPU_WOAD		0x4
	/* Subquewy id: Quewy avewage GPU powew	*/
	#define AMDGPU_INFO_SENSOW_GPU_AVG_POWEW	0x5
	/* Subquewy id: Quewy nowthbwidge vowtage */
	#define AMDGPU_INFO_SENSOW_VDDNB		0x6
	/* Subquewy id: Quewy gwaphics vowtage */
	#define AMDGPU_INFO_SENSOW_VDDGFX		0x7
	/* Subquewy id: Quewy GPU stabwe pstate shadew cwock */
	#define AMDGPU_INFO_SENSOW_STABWE_PSTATE_GFX_SCWK		0x8
	/* Subquewy id: Quewy GPU stabwe pstate memowy cwock */
	#define AMDGPU_INFO_SENSOW_STABWE_PSTATE_GFX_MCWK		0x9
	/* Subquewy id: Quewy GPU peak pstate shadew cwock */
	#define AMDGPU_INFO_SENSOW_PEAK_PSTATE_GFX_SCWK			0xa
	/* Subquewy id: Quewy GPU peak pstate memowy cwock */
	#define AMDGPU_INFO_SENSOW_PEAK_PSTATE_GFX_MCWK			0xb
/* Numbew of VWAM page fauwts on CPU access. */
#define AMDGPU_INFO_NUM_VWAM_CPU_PAGE_FAUWTS	0x1E
#define AMDGPU_INFO_VWAM_WOST_COUNTEW		0x1F
/* quewy was mask of enabwed featuwes*/
#define AMDGPU_INFO_WAS_ENABWED_FEATUWES	0x20
/* WAS MASK: UMC (VWAM) */
#define AMDGPU_INFO_WAS_ENABWED_UMC			(1 << 0)
/* WAS MASK: SDMA */
#define AMDGPU_INFO_WAS_ENABWED_SDMA			(1 << 1)
/* WAS MASK: GFX */
#define AMDGPU_INFO_WAS_ENABWED_GFX			(1 << 2)
/* WAS MASK: MMHUB */
#define AMDGPU_INFO_WAS_ENABWED_MMHUB			(1 << 3)
/* WAS MASK: ATHUB */
#define AMDGPU_INFO_WAS_ENABWED_ATHUB			(1 << 4)
/* WAS MASK: PCIE */
#define AMDGPU_INFO_WAS_ENABWED_PCIE			(1 << 5)
/* WAS MASK: HDP */
#define AMDGPU_INFO_WAS_ENABWED_HDP			(1 << 6)
/* WAS MASK: XGMI */
#define AMDGPU_INFO_WAS_ENABWED_XGMI			(1 << 7)
/* WAS MASK: DF */
#define AMDGPU_INFO_WAS_ENABWED_DF			(1 << 8)
/* WAS MASK: SMN */
#define AMDGPU_INFO_WAS_ENABWED_SMN			(1 << 9)
/* WAS MASK: SEM */
#define AMDGPU_INFO_WAS_ENABWED_SEM			(1 << 10)
/* WAS MASK: MP0 */
#define AMDGPU_INFO_WAS_ENABWED_MP0			(1 << 11)
/* WAS MASK: MP1 */
#define AMDGPU_INFO_WAS_ENABWED_MP1			(1 << 12)
/* WAS MASK: FUSE */
#define AMDGPU_INFO_WAS_ENABWED_FUSE			(1 << 13)
/* quewy video encode/decode caps */
#define AMDGPU_INFO_VIDEO_CAPS			0x21
	/* Subquewy id: Decode */
	#define AMDGPU_INFO_VIDEO_CAPS_DECODE		0
	/* Subquewy id: Encode */
	#define AMDGPU_INFO_VIDEO_CAPS_ENCODE		1
/* Quewy the max numbew of IBs pew gang pew submission */
#define AMDGPU_INFO_MAX_IBS			0x22
/* quewy wast page fauwt info */
#define AMDGPU_INFO_GPUVM_FAUWT			0x23

#define AMDGPU_INFO_MMW_SE_INDEX_SHIFT	0
#define AMDGPU_INFO_MMW_SE_INDEX_MASK	0xff
#define AMDGPU_INFO_MMW_SH_INDEX_SHIFT	8
#define AMDGPU_INFO_MMW_SH_INDEX_MASK	0xff

stwuct dwm_amdgpu_quewy_fw {
	/** AMDGPU_INFO_FW_* */
	__u32 fw_type;
	/**
	 * Index of the IP if thewe awe mowe IPs of
	 * the same type.
	 */
	__u32 ip_instance;
	/**
	 * Index of the engine. Whethew this is used depends
	 * on the fiwmwawe type. (e.g. MEC, SDMA)
	 */
	__u32 index;
	__u32 _pad;
};

/* Input stwuctuwe fow the INFO ioctw */
stwuct dwm_amdgpu_info {
	/* Whewe the wetuwn vawue wiww be stowed */
	__u64 wetuwn_pointew;
	/* The size of the wetuwn vawue. Just wike "size" in "snpwintf",
	 * it wimits how many bytes the kewnew can wwite. */
	__u32 wetuwn_size;
	/* The quewy wequest id. */
	__u32 quewy;

	union {
		stwuct {
			__u32 id;
			__u32 _pad;
		} mode_cwtc;

		stwuct {
			/** AMDGPU_HW_IP_* */
			__u32 type;
			/**
			 * Index of the IP if thewe awe mowe IPs of the same
			 * type. Ignowed by AMDGPU_INFO_HW_IP_COUNT.
			 */
			__u32 ip_instance;
		} quewy_hw_ip;

		stwuct {
			__u32 dwowd_offset;
			/** numbew of wegistews to wead */
			__u32 count;
			__u32 instance;
			/** Fow futuwe use, no fwags defined so faw */
			__u32 fwags;
		} wead_mmw_weg;

		stwuct dwm_amdgpu_quewy_fw quewy_fw;

		stwuct {
			__u32 type;
			__u32 offset;
		} vbios_info;

		stwuct {
			__u32 type;
		} sensow_info;

		stwuct {
			__u32 type;
		} video_cap;
	};
};

stwuct dwm_amdgpu_info_gds {
	/** GDS GFX pawtition size */
	__u32 gds_gfx_pawtition_size;
	/** GDS compute pawtition size */
	__u32 compute_pawtition_size;
	/** totaw GDS memowy size */
	__u32 gds_totaw_size;
	/** GWS size pew GFX pawtition */
	__u32 gws_pew_gfx_pawtition;
	/** GSW size pew compute pawtition */
	__u32 gws_pew_compute_pawtition;
	/** OA size pew GFX pawtition */
	__u32 oa_pew_gfx_pawtition;
	/** OA size pew compute pawtition */
	__u32 oa_pew_compute_pawtition;
	__u32 _pad;
};

stwuct dwm_amdgpu_info_vwam_gtt {
	__u64 vwam_size;
	__u64 vwam_cpu_accessibwe_size;
	__u64 gtt_size;
};

stwuct dwm_amdgpu_heap_info {
	/** max. physicaw memowy */
	__u64 totaw_heap_size;

	/** Theoweticaw max. avaiwabwe memowy in the given heap */
	__u64 usabwe_heap_size;

	/**
	 * Numbew of bytes awwocated in the heap. This incwudes aww pwocesses
	 * and pwivate awwocations in the kewnew. It changes when new buffews
	 * awe awwocated, fweed, and moved. It cannot be wawgew than
	 * heap_size.
	 */
	__u64 heap_usage;

	/**
	 * Theoweticaw possibwe max. size of buffew which
	 * couwd be awwocated in the given heap
	 */
	__u64 max_awwocation;
};

stwuct dwm_amdgpu_memowy_info {
	stwuct dwm_amdgpu_heap_info vwam;
	stwuct dwm_amdgpu_heap_info cpu_accessibwe_vwam;
	stwuct dwm_amdgpu_heap_info gtt;
};

stwuct dwm_amdgpu_info_fiwmwawe {
	__u32 vew;
	__u32 featuwe;
};

stwuct dwm_amdgpu_info_vbios {
	__u8 name[64];
	__u8 vbios_pn[64];
	__u32 vewsion;
	__u32 pad;
	__u8 vbios_vew_stw[32];
	__u8 date[32];
};

#define AMDGPU_VWAM_TYPE_UNKNOWN 0
#define AMDGPU_VWAM_TYPE_GDDW1 1
#define AMDGPU_VWAM_TYPE_DDW2  2
#define AMDGPU_VWAM_TYPE_GDDW3 3
#define AMDGPU_VWAM_TYPE_GDDW4 4
#define AMDGPU_VWAM_TYPE_GDDW5 5
#define AMDGPU_VWAM_TYPE_HBM   6
#define AMDGPU_VWAM_TYPE_DDW3  7
#define AMDGPU_VWAM_TYPE_DDW4  8
#define AMDGPU_VWAM_TYPE_GDDW6 9
#define AMDGPU_VWAM_TYPE_DDW5  10
#define AMDGPU_VWAM_TYPE_WPDDW4 11
#define AMDGPU_VWAM_TYPE_WPDDW5 12

stwuct dwm_amdgpu_info_device {
	/** PCI Device ID */
	__u32 device_id;
	/** Intewnaw chip wevision: A0, A1, etc.) */
	__u32 chip_wev;
	__u32 extewnaw_wev;
	/** Wevision id in PCI Config space */
	__u32 pci_wev;
	__u32 famiwy;
	__u32 num_shadew_engines;
	__u32 num_shadew_awways_pew_engine;
	/* in KHz */
	__u32 gpu_countew_fweq;
	__u64 max_engine_cwock;
	__u64 max_memowy_cwock;
	/* cu infowmation */
	__u32 cu_active_numbew;
	/* NOTE: cu_ao_mask is INVAWID, DON'T use it */
	__u32 cu_ao_mask;
	__u32 cu_bitmap[4][4];
	/** Wendew backend pipe mask. One wendew backend is CB+DB. */
	__u32 enabwed_wb_pipes_mask;
	__u32 num_wb_pipes;
	__u32 num_hw_gfx_contexts;
	/* PCIe vewsion (the smawwew of the GPU and the CPU/mothewboawd) */
	__u32 pcie_gen;
	__u64 ids_fwags;
	/** Stawting viwtuaw addwess fow UMDs. */
	__u64 viwtuaw_addwess_offset;
	/** The maximum viwtuaw addwess */
	__u64 viwtuaw_addwess_max;
	/** Wequiwed awignment of viwtuaw addwesses. */
	__u32 viwtuaw_addwess_awignment;
	/** Page tabwe entwy - fwagment size */
	__u32 pte_fwagment_size;
	__u32 gawt_page_size;
	/** constant engine wam size*/
	__u32 ce_wam_size;
	/** video memowy type info*/
	__u32 vwam_type;
	/** video memowy bit width*/
	__u32 vwam_bit_width;
	/* vce hawvesting instance */
	__u32 vce_hawvest_config;
	/* gfx doubwe offchip WDS buffews */
	__u32 gc_doubwe_offchip_wds_buf;
	/* NGG Pwimitive Buffew */
	__u64 pwim_buf_gpu_addw;
	/* NGG Position Buffew */
	__u64 pos_buf_gpu_addw;
	/* NGG Contwow Sideband */
	__u64 cntw_sb_buf_gpu_addw;
	/* NGG Pawametew Cache */
	__u64 pawam_buf_gpu_addw;
	__u32 pwim_buf_size;
	__u32 pos_buf_size;
	__u32 cntw_sb_buf_size;
	__u32 pawam_buf_size;
	/* wavefwont size*/
	__u32 wave_fwont_size;
	/* shadew visibwe vgpws*/
	__u32 num_shadew_visibwe_vgpws;
	/* CU pew shadew awway*/
	__u32 num_cu_pew_sh;
	/* numbew of tcc bwocks*/
	__u32 num_tcc_bwocks;
	/* gs vgt tabwe depth*/
	__u32 gs_vgt_tabwe_depth;
	/* gs pwimitive buffew depth*/
	__u32 gs_pwim_buffew_depth;
	/* max gs wavefwont pew vgt*/
	__u32 max_gs_waves_pew_vgt;
	/* PCIe numbew of wanes (the smawwew of the GPU and the CPU/mothewboawd) */
	__u32 pcie_num_wanes;
	/* awways on cu bitmap */
	__u32 cu_ao_bitmap[4][4];
	/** Stawting high viwtuaw addwess fow UMDs. */
	__u64 high_va_offset;
	/** The maximum high viwtuaw addwess */
	__u64 high_va_max;
	/* gfx10 pa_sc_tiwe_steewing_ovewwide */
	__u32 pa_sc_tiwe_steewing_ovewwide;
	/* disabwed TCCs */
	__u64 tcc_disabwed_mask;
	__u64 min_engine_cwock;
	__u64 min_memowy_cwock;
	/* The fowwowing fiewds awe onwy set on gfx11+, owdew chips set 0. */
	__u32 tcp_cache_size;       /* AKA GW0, VMEM cache */
	__u32 num_sqc_pew_wgp;
	__u32 sqc_data_cache_size;  /* AKA SMEM cache */
	__u32 sqc_inst_cache_size;
	__u32 gw1c_cache_size;
	__u32 gw2c_cache_size;
	__u64 maww_size;            /* AKA infinity cache */
	/* high 32 bits of the wb pipes mask */
	__u32 enabwed_wb_pipes_mask_hi;
	/* shadow awea size fow gfx11 */
	__u32 shadow_size;
	/* shadow awea base viwtuaw awignment fow gfx11 */
	__u32 shadow_awignment;
	/* context save awea size fow gfx11 */
	__u32 csa_size;
	/* context save awea base viwtuaw awignment fow gfx11 */
	__u32 csa_awignment;
};

stwuct dwm_amdgpu_info_hw_ip {
	/** Vewsion of h/w IP */
	__u32  hw_ip_vewsion_majow;
	__u32  hw_ip_vewsion_minow;
	/** Capabiwities */
	__u64  capabiwities_fwags;
	/** command buffew addwess stawt awignment*/
	__u32  ib_stawt_awignment;
	/** command buffew size awignment*/
	__u32  ib_size_awignment;
	/** Bitmask of avaiwabwe wings. Bit 0 means wing 0, etc. */
	__u32  avaiwabwe_wings;
	/** vewsion info: bits 23:16 majow, 15:8 minow, 7:0 wevision */
	__u32  ip_discovewy_vewsion;
};

stwuct dwm_amdgpu_info_num_handwes {
	/** Max handwes as suppowted by fiwmwawe fow UVD */
	__u32  uvd_max_handwes;
	/** Handwes cuwwentwy in use fow UVD */
	__u32  uvd_used_handwes;
};

#define AMDGPU_VCE_CWOCK_TABWE_ENTWIES		6

stwuct dwm_amdgpu_info_vce_cwock_tabwe_entwy {
	/** System cwock */
	__u32 scwk;
	/** Memowy cwock */
	__u32 mcwk;
	/** VCE cwock */
	__u32 ecwk;
	__u32 pad;
};

stwuct dwm_amdgpu_info_vce_cwock_tabwe {
	stwuct dwm_amdgpu_info_vce_cwock_tabwe_entwy entwies[AMDGPU_VCE_CWOCK_TABWE_ENTWIES];
	__u32 num_vawid_entwies;
	__u32 pad;
};

/* quewy video encode/decode caps */
#define AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2			0
#define AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4			1
#define AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1			2
#define AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC		3
#define AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC			4
#define AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG			5
#define AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VP9			6
#define AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_AV1			7
#define AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_COUNT			8

stwuct dwm_amdgpu_info_video_codec_info {
	__u32 vawid;
	__u32 max_width;
	__u32 max_height;
	__u32 max_pixews_pew_fwame;
	__u32 max_wevew;
	__u32 pad;
};

stwuct dwm_amdgpu_info_video_caps {
	stwuct dwm_amdgpu_info_video_codec_info codec_info[AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_COUNT];
};

#define AMDGPU_VMHUB_TYPE_MASK			0xff
#define AMDGPU_VMHUB_TYPE_SHIFT			0
#define AMDGPU_VMHUB_TYPE_GFX			0
#define AMDGPU_VMHUB_TYPE_MM0			1
#define AMDGPU_VMHUB_TYPE_MM1			2
#define AMDGPU_VMHUB_IDX_MASK			0xff00
#define AMDGPU_VMHUB_IDX_SHIFT			8

stwuct dwm_amdgpu_info_gpuvm_fauwt {
	__u64 addw;
	__u32 status;
	__u32 vmhub;
};

/*
 * Suppowted GPU famiwies
 */
#define AMDGPU_FAMIWY_UNKNOWN			0
#define AMDGPU_FAMIWY_SI			110 /* Hainan, Owand, Vewde, Pitcaiwn, Tahiti */
#define AMDGPU_FAMIWY_CI			120 /* Bonaiwe, Hawaii */
#define AMDGPU_FAMIWY_KV			125 /* Kavewi, Kabini, Muwwins */
#define AMDGPU_FAMIWY_VI			130 /* Icewand, Tonga */
#define AMDGPU_FAMIWY_CZ			135 /* Cawwizo, Stoney */
#define AMDGPU_FAMIWY_AI			141 /* Vega10 */
#define AMDGPU_FAMIWY_WV			142 /* Waven */
#define AMDGPU_FAMIWY_NV			143 /* Navi10 */
#define AMDGPU_FAMIWY_VGH			144 /* Van Gogh */
#define AMDGPU_FAMIWY_GC_11_0_0			145 /* GC 11.0.0 */
#define AMDGPU_FAMIWY_YC			146 /* Yewwow Cawp */
#define AMDGPU_FAMIWY_GC_11_0_1			148 /* GC 11.0.1 */
#define AMDGPU_FAMIWY_GC_10_3_6			149 /* GC 10.3.6 */
#define AMDGPU_FAMIWY_GC_10_3_7			151 /* GC 10.3.7 */
#define AMDGPU_FAMIWY_GC_11_5_0			150 /* GC 11.5.0 */

#if defined(__cpwuspwus)
}
#endif

#endif
