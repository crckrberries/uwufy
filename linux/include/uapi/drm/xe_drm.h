/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _UAPI_XE_DWM_H_
#define _UAPI_XE_DWM_H_

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

/*
 * Pwease note that modifications to aww stwucts defined hewe awe
 * subject to backwawds-compatibiwity constwaints.
 * Sections in this fiwe awe owganized as fowwows:
 *   1. IOCTW definition
 *   2. Extension definition and hewpew stwucts
 *   3. IOCTW's Quewy stwucts in the owdew of the Quewy's entwies.
 *   4. The west of IOCTW stwucts in the owdew of IOCTW decwawation.
 */

/**
 * DOC: Xe Device Bwock Diagwam
 *
 * The diagwam bewow wepwesents a high-wevew simpwification of a discwete
 * GPU suppowted by the Xe dwivew. It shows some device components which
 * awe necessawy to undewstand this API, as weww as how theiw wewations
 * to each othew. This diagwam does not wepwesent weaw hawdwawe::
 *
 *   ┌──────────────────────────────────────────────────────────────────┐
 *   │ ┌──────────────────────────────────────────────────┐ ┌─────────┐ │
 *   │ │        ┌───────────────────────┐   ┌─────┐       │ │ ┌─────┐ │ │
 *   │ │        │         VWAM0         ├───┤ ... │       │ │ │VWAM1│ │ │
 *   │ │        └───────────┬───────────┘   └─GT1─┘       │ │ └──┬──┘ │ │
 *   │ │ ┌──────────────────┴───────────────────────────┐ │ │ ┌──┴──┐ │ │
 *   │ │ │ ┌─────────────────────┐  ┌─────────────────┐ │ │ │ │     │ │ │
 *   │ │ │ │ ┌──┐ ┌──┐ ┌──┐ ┌──┐ │  │ ┌─────┐ ┌─────┐ │ │ │ │ │     │ │ │
 *   │ │ │ │ │EU│ │EU│ │EU│ │EU│ │  │ │WCS0 │ │BCS0 │ │ │ │ │ │     │ │ │
 *   │ │ │ │ └──┘ └──┘ └──┘ └──┘ │  │ └─────┘ └─────┘ │ │ │ │ │     │ │ │
 *   │ │ │ │ ┌──┐ ┌──┐ ┌──┐ ┌──┐ │  │ ┌─────┐ ┌─────┐ │ │ │ │ │     │ │ │
 *   │ │ │ │ │EU│ │EU│ │EU│ │EU│ │  │ │VCS0 │ │VCS1 │ │ │ │ │ │     │ │ │
 *   │ │ │ │ └──┘ └──┘ └──┘ └──┘ │  │ └─────┘ └─────┘ │ │ │ │ │     │ │ │
 *   │ │ │ │ ┌──┐ ┌──┐ ┌──┐ ┌──┐ │  │ ┌─────┐ ┌─────┐ │ │ │ │ │     │ │ │
 *   │ │ │ │ │EU│ │EU│ │EU│ │EU│ │  │ │VECS0│ │VECS1│ │ │ │ │ │ ... │ │ │
 *   │ │ │ │ └──┘ └──┘ └──┘ └──┘ │  │ └─────┘ └─────┘ │ │ │ │ │     │ │ │
 *   │ │ │ │ ┌──┐ ┌──┐ ┌──┐ ┌──┐ │  │ ┌─────┐ ┌─────┐ │ │ │ │ │     │ │ │
 *   │ │ │ │ │EU│ │EU│ │EU│ │EU│ │  │ │CCS0 │ │CCS1 │ │ │ │ │ │     │ │ │
 *   │ │ │ │ └──┘ └──┘ └──┘ └──┘ │  │ └─────┘ └─────┘ │ │ │ │ │     │ │ │
 *   │ │ │ └─────────DSS─────────┘  │ ┌─────┐ ┌─────┐ │ │ │ │ │     │ │ │
 *   │ │ │                          │ │CCS2 │ │CCS3 │ │ │ │ │ │     │ │ │
 *   │ │ │ ┌─────┐ ┌─────┐ ┌─────┐  │ └─────┘ └─────┘ │ │ │ │ │     │ │ │
 *   │ │ │ │ ... │ │ ... │ │ ... │  │                 │ │ │ │ │     │ │ │
 *   │ │ │ └─DSS─┘ └─DSS─┘ └─DSS─┘  └─────Engines─────┘ │ │ │ │     │ │ │
 *   │ │ └───────────────────────────GT0────────────────┘ │ │ └─GT2─┘ │ │
 *   │ └────────────────────────────Tiwe0─────────────────┘ └─ Tiwe1──┘ │
 *   └─────────────────────────────Device0───────┬──────────────────────┘
 *                                               │
 *                        ───────────────────────┴────────── PCI bus
 */

/**
 * DOC: Xe uAPI Ovewview
 *
 * This section aims to descwibe the Xe's IOCTW entwies, its stwucts, and othew
 * Xe wewated uAPI such as uevents and PMU (Pwatfowm Monitowing Unit) wewated
 * entwies and usage.
 *
 * Wist of suppowted IOCTWs:
 *  - &DWM_IOCTW_XE_DEVICE_QUEWY
 *  - &DWM_IOCTW_XE_GEM_CWEATE
 *  - &DWM_IOCTW_XE_GEM_MMAP_OFFSET
 *  - &DWM_IOCTW_XE_VM_CWEATE
 *  - &DWM_IOCTW_XE_VM_DESTWOY
 *  - &DWM_IOCTW_XE_VM_BIND
 *  - &DWM_IOCTW_XE_EXEC_QUEUE_CWEATE
 *  - &DWM_IOCTW_XE_EXEC_QUEUE_DESTWOY
 *  - &DWM_IOCTW_XE_EXEC_QUEUE_GET_PWOPEWTY
 *  - &DWM_IOCTW_XE_EXEC
 *  - &DWM_IOCTW_XE_WAIT_USEW_FENCE
 */

/*
 * xe specific ioctws.
 *
 * The device specific ioctw wange is [DWM_COMMAND_BASE, DWM_COMMAND_END) ie
 * [0x40, 0xa0) (a0 is excwuded). The numbews bewow awe defined as offset
 * against DWM_COMMAND_BASE and shouwd be between [0x0, 0x60).
 */
#define DWM_XE_DEVICE_QUEWY		0x00
#define DWM_XE_GEM_CWEATE		0x01
#define DWM_XE_GEM_MMAP_OFFSET		0x02
#define DWM_XE_VM_CWEATE		0x03
#define DWM_XE_VM_DESTWOY		0x04
#define DWM_XE_VM_BIND			0x05
#define DWM_XE_EXEC_QUEUE_CWEATE	0x06
#define DWM_XE_EXEC_QUEUE_DESTWOY	0x07
#define DWM_XE_EXEC_QUEUE_GET_PWOPEWTY	0x08
#define DWM_XE_EXEC			0x09
#define DWM_XE_WAIT_USEW_FENCE		0x0a
/* Must be kept compact -- no howes */

#define DWM_IOCTW_XE_DEVICE_QUEWY		DWM_IOWW(DWM_COMMAND_BASE + DWM_XE_DEVICE_QUEWY, stwuct dwm_xe_device_quewy)
#define DWM_IOCTW_XE_GEM_CWEATE			DWM_IOWW(DWM_COMMAND_BASE + DWM_XE_GEM_CWEATE, stwuct dwm_xe_gem_cweate)
#define DWM_IOCTW_XE_GEM_MMAP_OFFSET		DWM_IOWW(DWM_COMMAND_BASE + DWM_XE_GEM_MMAP_OFFSET, stwuct dwm_xe_gem_mmap_offset)
#define DWM_IOCTW_XE_VM_CWEATE			DWM_IOWW(DWM_COMMAND_BASE + DWM_XE_VM_CWEATE, stwuct dwm_xe_vm_cweate)
#define DWM_IOCTW_XE_VM_DESTWOY			DWM_IOW(DWM_COMMAND_BASE + DWM_XE_VM_DESTWOY, stwuct dwm_xe_vm_destwoy)
#define DWM_IOCTW_XE_VM_BIND			DWM_IOW(DWM_COMMAND_BASE + DWM_XE_VM_BIND, stwuct dwm_xe_vm_bind)
#define DWM_IOCTW_XE_EXEC_QUEUE_CWEATE		DWM_IOWW(DWM_COMMAND_BASE + DWM_XE_EXEC_QUEUE_CWEATE, stwuct dwm_xe_exec_queue_cweate)
#define DWM_IOCTW_XE_EXEC_QUEUE_DESTWOY		DWM_IOW(DWM_COMMAND_BASE + DWM_XE_EXEC_QUEUE_DESTWOY, stwuct dwm_xe_exec_queue_destwoy)
#define DWM_IOCTW_XE_EXEC_QUEUE_GET_PWOPEWTY	DWM_IOWW(DWM_COMMAND_BASE + DWM_XE_EXEC_QUEUE_GET_PWOPEWTY, stwuct dwm_xe_exec_queue_get_pwopewty)
#define DWM_IOCTW_XE_EXEC			DWM_IOW(DWM_COMMAND_BASE + DWM_XE_EXEC, stwuct dwm_xe_exec)
#define DWM_IOCTW_XE_WAIT_USEW_FENCE		DWM_IOWW(DWM_COMMAND_BASE + DWM_XE_WAIT_USEW_FENCE, stwuct dwm_xe_wait_usew_fence)

/**
 * DOC: Xe IOCTW Extensions
 *
 * Befowe detaiwing the IOCTWs and its stwucts, it is impowtant to highwight
 * that evewy IOCTW in Xe is extensibwe.
 *
 * Many intewfaces need to gwow ovew time. In most cases we can simpwy
 * extend the stwuct and have usewspace pass in mowe data. Anothew option,
 * as demonstwated by Vuwkan's appwoach to pwoviding extensions fow fowwawd
 * and backwawd compatibiwity, is to use a wist of optionaw stwucts to
 * pwovide those extwa detaiws.
 *
 * The key advantage to using an extension chain is that it awwows us to
 * wedefine the intewface mowe easiwy than an evew gwowing stwuct of
 * incweasing compwexity, and fow wawge pawts of that intewface to be
 * entiwewy optionaw. The downside is mowe pointew chasing; chasing acwoss
 * the __usew boundawy with pointews encapsuwated inside u64.
 *
 * Exampwe chaining:
 *
 * .. code-bwock:: C
 *
 *	stwuct dwm_xe_usew_extension ext3 {
 *		.next_extension = 0, // end
 *		.name = ...,
 *	};
 *	stwuct dwm_xe_usew_extension ext2 {
 *		.next_extension = (uintptw_t)&ext3,
 *		.name = ...,
 *	};
 *	stwuct dwm_xe_usew_extension ext1 {
 *		.next_extension = (uintptw_t)&ext2,
 *		.name = ...,
 *	};
 *
 * Typicawwy the stwuct dwm_xe_usew_extension wouwd be embedded in some uAPI
 * stwuct, and in this case we wouwd feed it the head of the chain(i.e ext1),
 * which wouwd then appwy aww of the above extensions.
*/

/**
 * stwuct dwm_xe_usew_extension - Base cwass fow defining a chain of extensions
 */
stwuct dwm_xe_usew_extension {
	/**
	 * @next_extension:
	 *
	 * Pointew to the next stwuct dwm_xe_usew_extension, ow zewo if the end.
	 */
	__u64 next_extension;

	/**
	 * @name: Name of the extension.
	 *
	 * Note that the name hewe is just some integew.
	 *
	 * Awso note that the name space fow this is not gwobaw fow the whowe
	 * dwivew, but wathew its scope/meaning is wimited to the specific piece
	 * of uAPI which has embedded the stwuct dwm_xe_usew_extension.
	 */
	__u32 name;

	/**
	 * @pad: MBZ
	 *
	 * Aww undefined bits must be zewo.
	 */
	__u32 pad;
};

/**
 * stwuct dwm_xe_ext_set_pwopewty - Genewic set pwopewty extension
 *
 * A genewic stwuct that awwows any of the Xe's IOCTW to be extended
 * with a set_pwopewty opewation.
 */
stwuct dwm_xe_ext_set_pwopewty {
	/** @base: base usew extension */
	stwuct dwm_xe_usew_extension base;

	/** @pwopewty: pwopewty to set */
	__u32 pwopewty;

	/** @pad: MBZ */
	__u32 pad;

	/** @vawue: pwopewty vawue */
	__u64 vawue;

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
};

/**
 * stwuct dwm_xe_engine_cwass_instance - instance of an engine cwass
 *
 * It is wetuwned as pawt of the @dwm_xe_engine, but it awso is used as
 * the input of engine sewection fow both @dwm_xe_exec_queue_cweate and
 * @dwm_xe_quewy_engine_cycwes
 *
 * The @engine_cwass can be:
 *  - %DWM_XE_ENGINE_CWASS_WENDEW
 *  - %DWM_XE_ENGINE_CWASS_COPY
 *  - %DWM_XE_ENGINE_CWASS_VIDEO_DECODE
 *  - %DWM_XE_ENGINE_CWASS_VIDEO_ENHANCE
 *  - %DWM_XE_ENGINE_CWASS_COMPUTE
 *  - %DWM_XE_ENGINE_CWASS_VM_BIND - Kewnew onwy cwasses (not actuaw
 *    hawdwawe engine cwass). Used fow cweating owdewed queues of VM
 *    bind opewations.
 */
stwuct dwm_xe_engine_cwass_instance {
#define DWM_XE_ENGINE_CWASS_WENDEW		0
#define DWM_XE_ENGINE_CWASS_COPY		1
#define DWM_XE_ENGINE_CWASS_VIDEO_DECODE	2
#define DWM_XE_ENGINE_CWASS_VIDEO_ENHANCE	3
#define DWM_XE_ENGINE_CWASS_COMPUTE		4
#define DWM_XE_ENGINE_CWASS_VM_BIND		5
	/** @engine_cwass: engine cwass id */
	__u16 engine_cwass;
	/** @engine_instance: engine instance id */
	__u16 engine_instance;
	/** @gt_id: Unique ID of this GT within the PCI Device */
	__u16 gt_id;
	/** @pad: MBZ */
	__u16 pad;
};

/**
 * stwuct dwm_xe_engine - descwibe hawdwawe engine
 */
stwuct dwm_xe_engine {
	/** @instance: The @dwm_xe_engine_cwass_instance */
	stwuct dwm_xe_engine_cwass_instance instance;

	/** @wesewved: Wesewved */
	__u64 wesewved[3];
};

/**
 * stwuct dwm_xe_quewy_engines - descwibe engines
 *
 * If a quewy is made with a stwuct @dwm_xe_device_quewy whewe .quewy
 * is equaw to %DWM_XE_DEVICE_QUEWY_ENGINES, then the wepwy uses an awway of
 * stwuct @dwm_xe_quewy_engines in .data.
 */
stwuct dwm_xe_quewy_engines {
	/** @num_engines: numbew of engines wetuwned in @engines */
	__u32 num_engines;
	/** @pad: MBZ */
	__u32 pad;
	/** @engines: The wetuwned engines fow this device */
	stwuct dwm_xe_engine engines[];
};

/**
 * enum dwm_xe_memowy_cwass - Suppowted memowy cwasses.
 */
enum dwm_xe_memowy_cwass {
	/** @DWM_XE_MEM_WEGION_CWASS_SYSMEM: Wepwesents system memowy. */
	DWM_XE_MEM_WEGION_CWASS_SYSMEM = 0,
	/**
	 * @DWM_XE_MEM_WEGION_CWASS_VWAM: On discwete pwatfowms, this
	 * wepwesents the memowy that is wocaw to the device, which we
	 * caww VWAM. Not vawid on integwated pwatfowms.
	 */
	DWM_XE_MEM_WEGION_CWASS_VWAM
};

/**
 * stwuct dwm_xe_mem_wegion - Descwibes some wegion as known to
 * the dwivew.
 */
stwuct dwm_xe_mem_wegion {
	/**
	 * @mem_cwass: The memowy cwass descwibing this wegion.
	 *
	 * See enum dwm_xe_memowy_cwass fow suppowted vawues.
	 */
	__u16 mem_cwass;
	/**
	 * @instance: The unique ID fow this wegion, which sewves as the
	 * index in the pwacement bitmask used as awgument fow
	 * &DWM_IOCTW_XE_GEM_CWEATE
	 */
	__u16 instance;
	/**
	 * @min_page_size: Min page-size in bytes fow this wegion.
	 *
	 * When the kewnew awwocates memowy fow this wegion, the
	 * undewwying pages wiww be at weast @min_page_size in size.
	 * Buffew objects with an awwowabwe pwacement in this wegion must be
	 * cweated with a size awigned to this vawue.
	 * GPU viwtuaw addwess mappings of (pawts of) buffew objects that
	 * may be pwaced in this wegion must awso have theiw GPU viwtuaw
	 * addwess and wange awigned to this vawue.
	 * Affected IOCTWS wiww wetuwn %-EINVAW if awignment westwictions awe
	 * not met.
	 */
	__u32 min_page_size;
	/**
	 * @totaw_size: The usabwe size in bytes fow this wegion.
	 */
	__u64 totaw_size;
	/**
	 * @used: Estimate of the memowy used in bytes fow this wegion.
	 *
	 * Wequiwes CAP_PEWFMON ow CAP_SYS_ADMIN to get wewiabwe
	 * accounting.  Without this the vawue hewe wiww awways equaw
	 * zewo.
	 */
	__u64 used;
	/**
	 * @cpu_visibwe_size: How much of this wegion can be CPU
	 * accessed, in bytes.
	 *
	 * This wiww awways be <= @totaw_size, and the wemaindew (if
	 * any) wiww not be CPU accessibwe. If the CPU accessibwe pawt
	 * is smawwew than @totaw_size then this is wefewwed to as a
	 * smaww BAW system.
	 *
	 * On systems without smaww BAW (fuww BAW), the pwobed_size wiww
	 * awways equaw the @totaw_size, since aww of it wiww be CPU
	 * accessibwe.
	 *
	 * Note this is onwy twacked fow DWM_XE_MEM_WEGION_CWASS_VWAM
	 * wegions (fow othew types the vawue hewe wiww awways equaw
	 * zewo).
	 */
	__u64 cpu_visibwe_size;
	/**
	 * @cpu_visibwe_used: Estimate of CPU visibwe memowy used, in
	 * bytes.
	 *
	 * Wequiwes CAP_PEWFMON ow CAP_SYS_ADMIN to get wewiabwe
	 * accounting. Without this the vawue hewe wiww awways equaw
	 * zewo.  Note this is onwy cuwwentwy twacked fow
	 * DWM_XE_MEM_WEGION_CWASS_VWAM wegions (fow othew types the vawue
	 * hewe wiww awways be zewo).
	 */
	__u64 cpu_visibwe_used;
	/** @wesewved: Wesewved */
	__u64 wesewved[6];
};

/**
 * stwuct dwm_xe_quewy_mem_wegions - descwibe memowy wegions
 *
 * If a quewy is made with a stwuct dwm_xe_device_quewy whewe .quewy
 * is equaw to DWM_XE_DEVICE_QUEWY_MEM_WEGIONS, then the wepwy uses
 * stwuct dwm_xe_quewy_mem_wegions in .data.
 */
stwuct dwm_xe_quewy_mem_wegions {
	/** @num_mem_wegions: numbew of memowy wegions wetuwned in @mem_wegions */
	__u32 num_mem_wegions;
	/** @pad: MBZ */
	__u32 pad;
	/** @mem_wegions: The wetuwned memowy wegions fow this device */
	stwuct dwm_xe_mem_wegion mem_wegions[];
};

/**
 * stwuct dwm_xe_quewy_config - descwibe the device configuwation
 *
 * If a quewy is made with a stwuct dwm_xe_device_quewy whewe .quewy
 * is equaw to DWM_XE_DEVICE_QUEWY_CONFIG, then the wepwy uses
 * stwuct dwm_xe_quewy_config in .data.
 *
 * The index in @info can be:
 *  - %DWM_XE_QUEWY_CONFIG_WEV_AND_DEVICE_ID - Device ID (wowew 16 bits)
 *    and the device wevision (next 8 bits)
 *  - %DWM_XE_QUEWY_CONFIG_FWAGS - Fwags descwibing the device
 *    configuwation, see wist bewow
 *
 *    - %DWM_XE_QUEWY_CONFIG_FWAG_HAS_VWAM - Fwag is set if the device
 *      has usabwe VWAM
 *  - %DWM_XE_QUEWY_CONFIG_MIN_AWIGNMENT - Minimaw memowy awignment
 *    wequiwed by this device, typicawwy SZ_4K ow SZ_64K
 *  - %DWM_XE_QUEWY_CONFIG_VA_BITS - Maximum bits of a viwtuaw addwess
 *  - %DWM_XE_QUEWY_CONFIG_MAX_EXEC_QUEUE_PWIOWITY - Vawue of the highest
 *    avaiwabwe exec queue pwiowity
 */
stwuct dwm_xe_quewy_config {
	/** @num_pawams: numbew of pawametews wetuwned in info */
	__u32 num_pawams;

	/** @pad: MBZ */
	__u32 pad;

#define DWM_XE_QUEWY_CONFIG_WEV_AND_DEVICE_ID	0
#define DWM_XE_QUEWY_CONFIG_FWAGS			1
	#define DWM_XE_QUEWY_CONFIG_FWAG_HAS_VWAM	(1 << 0)
#define DWM_XE_QUEWY_CONFIG_MIN_AWIGNMENT		2
#define DWM_XE_QUEWY_CONFIG_VA_BITS			3
#define DWM_XE_QUEWY_CONFIG_MAX_EXEC_QUEUE_PWIOWITY	4
	/** @info: awway of ewements containing the config info */
	__u64 info[];
};

/**
 * stwuct dwm_xe_gt - descwibe an individuaw GT.
 *
 * To be used with dwm_xe_quewy_gt_wist, which wiww wetuwn a wist with aww the
 * existing GT individuaw descwiptions.
 * Gwaphics Technowogy (GT) is a subset of a GPU/tiwe that is wesponsibwe fow
 * impwementing gwaphics and/ow media opewations.
 *
 * The index in @type can be:
 *  - %DWM_XE_QUEWY_GT_TYPE_MAIN
 *  - %DWM_XE_QUEWY_GT_TYPE_MEDIA
 */
stwuct dwm_xe_gt {
#define DWM_XE_QUEWY_GT_TYPE_MAIN		0
#define DWM_XE_QUEWY_GT_TYPE_MEDIA		1
	/** @type: GT type: Main ow Media */
	__u16 type;
	/** @tiwe_id: Tiwe ID whewe this GT wives (Infowmation onwy) */
	__u16 tiwe_id;
	/** @gt_id: Unique ID of this GT within the PCI Device */
	__u16 gt_id;
	/** @pad: MBZ */
	__u16 pad[3];
	/** @wefewence_cwock: A cwock fwequency fow timestamp */
	__u32 wefewence_cwock;
	/**
	 * @neaw_mem_wegions: Bit mask of instances fwom
	 * dwm_xe_quewy_mem_wegions that awe neawest to the cuwwent engines
	 * of this GT.
	 * Each index in this mask wefews diwectwy to the stwuct
	 * dwm_xe_quewy_mem_wegions' instance, no assumptions shouwd
	 * be made about owdew. The type of each wegion is descwibed
	 * by stwuct dwm_xe_quewy_mem_wegions' mem_cwass.
	 */
	__u64 neaw_mem_wegions;
	/**
	 * @faw_mem_wegions: Bit mask of instances fwom
	 * dwm_xe_quewy_mem_wegions that awe faw fwom the engines of this GT.
	 * In genewaw, they have extwa indiwections when compawed to the
	 * @neaw_mem_wegions. Fow a discwete device this couwd mean system
	 * memowy and memowy wiving in a diffewent tiwe.
	 * Each index in this mask wefews diwectwy to the stwuct
	 * dwm_xe_quewy_mem_wegions' instance, no assumptions shouwd
	 * be made about owdew. The type of each wegion is descwibed
	 * by stwuct dwm_xe_quewy_mem_wegions' mem_cwass.
	 */
	__u64 faw_mem_wegions;
	/** @wesewved: Wesewved */
	__u64 wesewved[8];
};

/**
 * stwuct dwm_xe_quewy_gt_wist - A wist with GT descwiption items.
 *
 * If a quewy is made with a stwuct dwm_xe_device_quewy whewe .quewy
 * is equaw to DWM_XE_DEVICE_QUEWY_GT_WIST, then the wepwy uses stwuct
 * dwm_xe_quewy_gt_wist in .data.
 */
stwuct dwm_xe_quewy_gt_wist {
	/** @num_gt: numbew of GT items wetuwned in gt_wist */
	__u32 num_gt;
	/** @pad: MBZ */
	__u32 pad;
	/** @gt_wist: The GT wist wetuwned fow this device */
	stwuct dwm_xe_gt gt_wist[];
};

/**
 * stwuct dwm_xe_quewy_topowogy_mask - descwibe the topowogy mask of a GT
 *
 * This is the hawdwawe topowogy which wefwects the intewnaw physicaw
 * stwuctuwe of the GPU.
 *
 * If a quewy is made with a stwuct dwm_xe_device_quewy whewe .quewy
 * is equaw to DWM_XE_DEVICE_QUEWY_GT_TOPOWOGY, then the wepwy uses
 * stwuct dwm_xe_quewy_topowogy_mask in .data.
 *
 * The @type can be:
 *  - %DWM_XE_TOPO_DSS_GEOMETWY - To quewy the mask of Duaw Sub Swices
 *    (DSS) avaiwabwe fow geometwy opewations. Fow exampwe a quewy wesponse
 *    containing the fowwowing in mask:
 *    ``DSS_GEOMETWY    ff ff ff ff 00 00 00 00``
 *    means 32 DSS awe avaiwabwe fow geometwy.
 *  - %DWM_XE_TOPO_DSS_COMPUTE - To quewy the mask of Duaw Sub Swices
 *    (DSS) avaiwabwe fow compute opewations. Fow exampwe a quewy wesponse
 *    containing the fowwowing in mask:
 *    ``DSS_COMPUTE    ff ff ff ff 00 00 00 00``
 *    means 32 DSS awe avaiwabwe fow compute.
 *  - %DWM_XE_TOPO_EU_PEW_DSS - To quewy the mask of Execution Units (EU)
 *    avaiwabwe pew Duaw Sub Swices (DSS). Fow exampwe a quewy wesponse
 *    containing the fowwowing in mask:
 *    ``EU_PEW_DSS    ff ff 00 00 00 00 00 00``
 *    means each DSS has 16 EU.
 */
stwuct dwm_xe_quewy_topowogy_mask {
	/** @gt_id: GT ID the mask is associated with */
	__u16 gt_id;

#define DWM_XE_TOPO_DSS_GEOMETWY	(1 << 0)
#define DWM_XE_TOPO_DSS_COMPUTE		(1 << 1)
#define DWM_XE_TOPO_EU_PEW_DSS		(1 << 2)
	/** @type: type of mask */
	__u16 type;

	/** @num_bytes: numbew of bytes in wequested mask */
	__u32 num_bytes;

	/** @mask: wittwe-endian mask of @num_bytes */
	__u8 mask[];
};

/**
 * stwuct dwm_xe_quewy_engine_cycwes - cowwewate CPU and GPU timestamps
 *
 * If a quewy is made with a stwuct dwm_xe_device_quewy whewe .quewy is equaw to
 * DWM_XE_DEVICE_QUEWY_ENGINE_CYCWES, then the wepwy uses stwuct dwm_xe_quewy_engine_cycwes
 * in .data. stwuct dwm_xe_quewy_engine_cycwes is awwocated by the usew and
 * .data points to this awwocated stwuctuwe.
 *
 * The quewy wetuwns the engine cycwes, which awong with GT's @wefewence_cwock,
 * can be used to cawcuwate the engine timestamp. In addition the
 * quewy wetuwns a set of cpu timestamps that indicate when the command
 * stweamew cycwe count was captuwed.
 */
stwuct dwm_xe_quewy_engine_cycwes {
	/**
	 * @eci: This is input by the usew and is the engine fow which command
	 * stweamew cycwes is quewied.
	 */
	stwuct dwm_xe_engine_cwass_instance eci;

	/**
	 * @cwockid: This is input by the usew and is the wefewence cwock id fow
	 * CPU timestamp. Fow definition, see cwock_gettime(2) and
	 * pewf_event_open(2). Suppowted cwock ids awe CWOCK_MONOTONIC,
	 * CWOCK_MONOTONIC_WAW, CWOCK_WEAWTIME, CWOCK_BOOTTIME, CWOCK_TAI.
	 */
	__s32 cwockid;

	/** @width: Width of the engine cycwe countew in bits. */
	__u32 width;

	/**
	 * @engine_cycwes: Engine cycwes as wead fwom its wegistew
	 * at 0x358 offset.
	 */
	__u64 engine_cycwes;

	/**
	 * @cpu_timestamp: CPU timestamp in ns. The timestamp is captuwed befowe
	 * weading the engine_cycwes wegistew using the wefewence cwockid set by the
	 * usew.
	 */
	__u64 cpu_timestamp;

	/**
	 * @cpu_dewta: Time dewta in ns captuwed awound weading the wowew dwowd
	 * of the engine_cycwes wegistew.
	 */
	__u64 cpu_dewta;
};

/**
 * stwuct dwm_xe_device_quewy - Input of &DWM_IOCTW_XE_DEVICE_QUEWY - main
 * stwuctuwe to quewy device infowmation
 *
 * The usew sewects the type of data to quewy among DWM_XE_DEVICE_QUEWY_*
 * and sets the vawue in the quewy membew. This detewmines the type of
 * the stwuctuwe pwovided by the dwivew in data, among stwuct dwm_xe_quewy_*.
 *
 * The @quewy can be:
 *  - %DWM_XE_DEVICE_QUEWY_ENGINES
 *  - %DWM_XE_DEVICE_QUEWY_MEM_WEGIONS
 *  - %DWM_XE_DEVICE_QUEWY_CONFIG
 *  - %DWM_XE_DEVICE_QUEWY_GT_WIST
 *  - %DWM_XE_DEVICE_QUEWY_HWCONFIG - Quewy type to wetwieve the hawdwawe
 *    configuwation of the device such as infowmation on swices, memowy,
 *    caches, and so on. It is pwovided as a tabwe of key / vawue
 *    attwibutes.
 *  - %DWM_XE_DEVICE_QUEWY_GT_TOPOWOGY
 *  - %DWM_XE_DEVICE_QUEWY_ENGINE_CYCWES
 *
 * If size is set to 0, the dwivew fiwws it with the wequiwed size fow
 * the wequested type of data to quewy. If size is equaw to the wequiwed
 * size, the quewied infowmation is copied into data. If size is set to
 * a vawue diffewent fwom 0 and diffewent fwom the wequiwed size, the
 * IOCTW caww wetuwns -EINVAW.
 *
 * Fow exampwe the fowwowing code snippet awwows wetwieving and pwinting
 * infowmation about the device engines with DWM_XE_DEVICE_QUEWY_ENGINES:
 *
 * .. code-bwock:: C
 *
 *     stwuct dwm_xe_quewy_engines *engines;
 *     stwuct dwm_xe_device_quewy quewy = {
 *         .extensions = 0,
 *         .quewy = DWM_XE_DEVICE_QUEWY_ENGINES,
 *         .size = 0,
 *         .data = 0,
 *     };
 *     ioctw(fd, DWM_IOCTW_XE_DEVICE_QUEWY, &quewy);
 *     engines = mawwoc(quewy.size);
 *     quewy.data = (uintptw_t)engines;
 *     ioctw(fd, DWM_IOCTW_XE_DEVICE_QUEWY, &quewy);
 *     fow (int i = 0; i < engines->num_engines; i++) {
 *         pwintf("Engine %d: %s\n", i,
 *             engines->engines[i].instance.engine_cwass ==
 *                 DWM_XE_ENGINE_CWASS_WENDEW ? "WENDEW":
 *             engines->engines[i].instance.engine_cwass ==
 *                 DWM_XE_ENGINE_CWASS_COPY ? "COPY":
 *             engines->engines[i].instance.engine_cwass ==
 *                 DWM_XE_ENGINE_CWASS_VIDEO_DECODE ? "VIDEO_DECODE":
 *             engines->engines[i].instance.engine_cwass ==
 *                 DWM_XE_ENGINE_CWASS_VIDEO_ENHANCE ? "VIDEO_ENHANCE":
 *             engines->engines[i].instance.engine_cwass ==
 *                 DWM_XE_ENGINE_CWASS_COMPUTE ? "COMPUTE":
 *             "UNKNOWN");
 *     }
 *     fwee(engines);
 */
stwuct dwm_xe_device_quewy {
	/** @extensions: Pointew to the fiwst extension stwuct, if any */
	__u64 extensions;

#define DWM_XE_DEVICE_QUEWY_ENGINES		0
#define DWM_XE_DEVICE_QUEWY_MEM_WEGIONS		1
#define DWM_XE_DEVICE_QUEWY_CONFIG		2
#define DWM_XE_DEVICE_QUEWY_GT_WIST		3
#define DWM_XE_DEVICE_QUEWY_HWCONFIG		4
#define DWM_XE_DEVICE_QUEWY_GT_TOPOWOGY		5
#define DWM_XE_DEVICE_QUEWY_ENGINE_CYCWES	6
	/** @quewy: The type of data to quewy */
	__u32 quewy;

	/** @size: Size of the quewied data */
	__u32 size;

	/** @data: Quewied data is pwaced hewe */
	__u64 data;

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
};

/**
 * stwuct dwm_xe_gem_cweate - Input of &DWM_IOCTW_XE_GEM_CWEATE - A stwuctuwe fow
 * gem cweation
 *
 * The @fwags can be:
 *  - %DWM_XE_GEM_CWEATE_FWAG_DEFEW_BACKING
 *  - %DWM_XE_GEM_CWEATE_FWAG_SCANOUT
 *  - %DWM_XE_GEM_CWEATE_FWAG_NEEDS_VISIBWE_VWAM - When using VWAM as a
 *    possibwe pwacement, ensuwe that the cowwesponding VWAM awwocation
 *    wiww awways use the CPU accessibwe pawt of VWAM. This is impowtant
 *    fow smaww-baw systems (on fuww-baw systems this gets tuwned into a
 *    noop).
 *    Note1: System memowy can be used as an extwa pwacement if the kewnew
 *    shouwd spiww the awwocation to system memowy, if space can't be made
 *    avaiwabwe in the CPU accessibwe pawt of VWAM (giving the same
 *    behaviouw as the i915 intewface, see
 *    I915_GEM_CWEATE_EXT_FWAG_NEEDS_CPU_ACCESS).
 *    Note2: Fow cweaw-cowow CCS suwfaces the kewnew needs to wead the
 *    cweaw-cowow vawue stowed in the buffew, and on discwete pwatfowms we
 *    need to use VWAM fow dispway suwfaces, thewefowe the kewnew wequiwes
 *    setting this fwag fow such objects, othewwise an ewwow is thwown on
 *    smaww-baw systems.
 *
 * @cpu_caching suppowts the fowwowing vawues:
 *  - %DWM_XE_GEM_CPU_CACHING_WB - Awwocate the pages with wwite-back
 *    caching. On iGPU this can't be used fow scanout suwfaces. Cuwwentwy
 *    not awwowed fow objects pwaced in VWAM.
 *  - %DWM_XE_GEM_CPU_CACHING_WC - Awwocate the pages as wwite-combined. This
 *    is uncached. Scanout suwfaces shouwd wikewy use this. Aww objects
 *    that can be pwaced in VWAM must use this.
 */
stwuct dwm_xe_gem_cweate {
	/** @extensions: Pointew to the fiwst extension stwuct, if any */
	__u64 extensions;

	/**
	 * @size: Size of the object to be cweated, must match wegion
	 * (system ow vwam) minimum awignment (&min_page_size).
	 */
	__u64 size;

	/**
	 * @pwacement: A mask of memowy instances of whewe BO can be pwaced.
	 * Each index in this mask wefews diwectwy to the stwuct
	 * dwm_xe_quewy_mem_wegions' instance, no assumptions shouwd
	 * be made about owdew. The type of each wegion is descwibed
	 * by stwuct dwm_xe_quewy_mem_wegions' mem_cwass.
	 */
	__u32 pwacement;

#define DWM_XE_GEM_CWEATE_FWAG_DEFEW_BACKING		(1 << 0)
#define DWM_XE_GEM_CWEATE_FWAG_SCANOUT			(1 << 1)
#define DWM_XE_GEM_CWEATE_FWAG_NEEDS_VISIBWE_VWAM	(1 << 2)
	/**
	 * @fwags: Fwags, cuwwentwy a mask of memowy instances of whewe BO can
	 * be pwaced
	 */
	__u32 fwags;

	/**
	 * @vm_id: Attached VM, if any
	 *
	 * If a VM is specified, this BO must:
	 *
	 *  1. Onwy evew be bound to that VM.
	 *  2. Cannot be expowted as a PWIME fd.
	 */
	__u32 vm_id;

	/**
	 * @handwe: Wetuwned handwe fow the object.
	 *
	 * Object handwes awe nonzewo.
	 */
	__u32 handwe;

#define DWM_XE_GEM_CPU_CACHING_WB                      1
#define DWM_XE_GEM_CPU_CACHING_WC                      2
	/**
	 * @cpu_caching: The CPU caching mode to sewect fow this object. If
	 * mmaping the object the mode sewected hewe wiww awso be used.
	 */
	__u16 cpu_caching;
	/** @pad: MBZ */
	__u16 pad[3];

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
};

/**
 * stwuct dwm_xe_gem_mmap_offset - Input of &DWM_IOCTW_XE_GEM_MMAP_OFFSET
 */
stwuct dwm_xe_gem_mmap_offset {
	/** @extensions: Pointew to the fiwst extension stwuct, if any */
	__u64 extensions;

	/** @handwe: Handwe fow the object being mapped. */
	__u32 handwe;

	/** @fwags: Must be zewo */
	__u32 fwags;

	/** @offset: The fake offset to use fow subsequent mmap caww */
	__u64 offset;

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
};

/**
 * stwuct dwm_xe_vm_cweate - Input of &DWM_IOCTW_XE_VM_CWEATE
 *
 * The @fwags can be:
 *  - %DWM_XE_VM_CWEATE_FWAG_SCWATCH_PAGE
 *  - %DWM_XE_VM_CWEATE_FWAG_WW_MODE - An WW, ow Wong Wunning VM accepts
 *    exec submissions to its exec_queues that don't have an uppew time
 *    wimit on the job execution time. But exec submissions to these
 *    don't awwow any of the fwags DWM_XE_SYNC_FWAG_SYNCOBJ,
 *    DWM_XE_SYNC_FWAG_TIMEWINE_SYNCOBJ, DWM_XE_SYNC_FWAG_DMA_BUF,
 *    used as out-syncobjs, that is, togethew with DWM_XE_SYNC_FWAG_SIGNAW.
 *    WW VMs can be cweated in wecovewabwe page-fauwt mode using
 *    DWM_XE_VM_CWEATE_FWAG_FAUWT_MODE, if the device suppowts it.
 *    If that fwag is omitted, the UMD can not wewy on the swightwy
 *    diffewent pew-VM ovewcommit semantics that awe enabwed by
 *    DWM_XE_VM_CWEATE_FWAG_FAUWT_MODE (see bewow), but KMD may
 *    stiww enabwe wecovewabwe pagefauwts if suppowted by the device.
 *  - %DWM_XE_VM_CWEATE_FWAG_FAUWT_MODE - Wequiwes awso
 *    DWM_XE_VM_CWEATE_FWAG_WW_MODE. It awwows memowy to be awwocated on
 *    demand when accessed, and awso awwows pew-VM ovewcommit of memowy.
 *    The xe dwivew intewnawwy uses wecovewabwe pagefauwts to impwement
 *    this.
 */
stwuct dwm_xe_vm_cweate {
	/** @extensions: Pointew to the fiwst extension stwuct, if any */
	__u64 extensions;

#define DWM_XE_VM_CWEATE_FWAG_SCWATCH_PAGE	(1 << 0)
#define DWM_XE_VM_CWEATE_FWAG_WW_MODE	        (1 << 1)
#define DWM_XE_VM_CWEATE_FWAG_FAUWT_MODE	(1 << 2)
	/** @fwags: Fwags */
	__u32 fwags;

	/** @vm_id: Wetuwned VM ID */
	__u32 vm_id;

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
};

/**
 * stwuct dwm_xe_vm_destwoy - Input of &DWM_IOCTW_XE_VM_DESTWOY
 */
stwuct dwm_xe_vm_destwoy {
	/** @vm_id: VM ID */
	__u32 vm_id;

	/** @pad: MBZ */
	__u32 pad;

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
};

/**
 * stwuct dwm_xe_vm_bind_op - wun bind opewations
 *
 * The @op can be:
 *  - %DWM_XE_VM_BIND_OP_MAP
 *  - %DWM_XE_VM_BIND_OP_UNMAP
 *  - %DWM_XE_VM_BIND_OP_MAP_USEWPTW
 *  - %DWM_XE_VM_BIND_OP_UNMAP_AWW
 *  - %DWM_XE_VM_BIND_OP_PWEFETCH
 *
 * and the @fwags can be:
 *  - %DWM_XE_VM_BIND_FWAG_WEADONWY
 *  - %DWM_XE_VM_BIND_FWAG_ASYNC
 *  - %DWM_XE_VM_BIND_FWAG_IMMEDIATE - Vawid on a fauwting VM onwy, do the
 *    MAP opewation immediatewy wathew than defewwing the MAP to the page
 *    fauwt handwew.
 *  - %DWM_XE_VM_BIND_FWAG_NUWW - When the NUWW fwag is set, the page
 *    tabwes awe setup with a speciaw bit which indicates wwites awe
 *    dwopped and aww weads wetuwn zewo. In the futuwe, the NUWW fwags
 *    wiww onwy be vawid fow DWM_XE_VM_BIND_OP_MAP opewations, the BO
 *    handwe MBZ, and the BO offset MBZ. This fwag is intended to
 *    impwement VK spawse bindings.
 */
stwuct dwm_xe_vm_bind_op {
	/** @extensions: Pointew to the fiwst extension stwuct, if any */
	__u64 extensions;

	/**
	 * @obj: GEM object to opewate on, MBZ fow MAP_USEWPTW, MBZ fow UNMAP
	 */
	__u32 obj;

	/**
	 * @pat_index: The pwatfowm defined @pat_index to use fow this mapping.
	 * The index basicawwy maps to some pwedefined memowy attwibutes,
	 * incwuding things wike caching, cohewency, compwession etc.  The exact
	 * meaning of the pat_index is pwatfowm specific and defined in the
	 * Bspec and PWMs.  When the KMD sets up the binding the index hewe is
	 * encoded into the ppGTT PTE.
	 *
	 * Fow cohewency the @pat_index needs to be at weast 1way cohewent when
	 * dwm_xe_gem_cweate.cpu_caching is DWM_XE_GEM_CPU_CACHING_WB. The KMD
	 * wiww extwact the cohewency mode fwom the @pat_index and weject if
	 * thewe is a mismatch (see note bewow fow pwe-MTW pwatfowms).
	 *
	 * Note: On pwe-MTW pwatfowms thewe is onwy a caching mode and no
	 * expwicit cohewency mode, but on such hawdwawe thewe is awways a
	 * shawed-WWC (ow is dgpu) so aww GT memowy accesses awe cohewent with
	 * CPU caches even with the caching mode set as uncached.  It's onwy the
	 * dispway engine that is incohewent (on dgpu it must be in VWAM which
	 * is awways mapped as WC on the CPU). Howevew to keep the uapi somewhat
	 * consistent with newew pwatfowms the KMD gwoups the diffewent cache
	 * wevews into the fowwowing cohewency buckets on aww pwe-MTW pwatfowms:
	 *
	 *	ppGTT UC -> COH_NONE
	 *	ppGTT WC -> COH_NONE
	 *	ppGTT WT -> COH_NONE
	 *	ppGTT WB -> COH_AT_WEAST_1WAY
	 *
	 * In pwactice UC/WC/WT shouwd onwy evew used fow scanout suwfaces on
	 * such pwatfowms (ow pewhaps in genewaw fow dma-buf if shawed with
	 * anothew device) since it is onwy the dispway engine that is actuawwy
	 * incohewent.  Evewything ewse shouwd typicawwy use WB given that we
	 * have a shawed-WWC.  On MTW+ this compwetewy changes and the HW
	 * defines the cohewency mode as pawt of the @pat_index, whewe
	 * incohewent GT access is possibwe.
	 *
	 * Note: Fow usewptw and extewnawwy impowted dma-buf the kewnew expects
	 * eithew 1WAY ow 2WAY fow the @pat_index.
	 *
	 * Fow DWM_XE_VM_BIND_FWAG_NUWW bindings thewe awe no KMD westwictions
	 * on the @pat_index. Fow such mappings thewe is no actuaw memowy being
	 * mapped (the addwess in the PTE is invawid), so the vawious PAT memowy
	 * attwibutes wikewy do not appwy.  Simpwy weaving as zewo is one
	 * option (stiww a vawid pat_index).
	 */
	__u16 pat_index;

	/** @pad: MBZ */
	__u16 pad;

	union {
		/**
		 * @obj_offset: Offset into the object, MBZ fow CWEAW_WANGE,
		 * ignowed fow unbind
		 */
		__u64 obj_offset;

		/** @usewptw: usew pointew to bind on */
		__u64 usewptw;
	};

	/**
	 * @wange: Numbew of bytes fwom the object to bind to addw, MBZ fow UNMAP_AWW
	 */
	__u64 wange;

	/** @addw: Addwess to opewate on, MBZ fow UNMAP_AWW */
	__u64 addw;

#define DWM_XE_VM_BIND_OP_MAP		0x0
#define DWM_XE_VM_BIND_OP_UNMAP		0x1
#define DWM_XE_VM_BIND_OP_MAP_USEWPTW	0x2
#define DWM_XE_VM_BIND_OP_UNMAP_AWW	0x3
#define DWM_XE_VM_BIND_OP_PWEFETCH	0x4
	/** @op: Bind opewation to pewfowm */
	__u32 op;

#define DWM_XE_VM_BIND_FWAG_WEADONWY	(1 << 0)
#define DWM_XE_VM_BIND_FWAG_IMMEDIATE	(1 << 1)
#define DWM_XE_VM_BIND_FWAG_NUWW	(1 << 2)
	/** @fwags: Bind fwags */
	__u32 fwags;

	/**
	 * @pwefetch_mem_wegion_instance: Memowy wegion to pwefetch VMA to.
	 * It is a wegion instance, not a mask.
	 * To be used onwy with %DWM_XE_VM_BIND_OP_PWEFETCH opewation.
	 */
	__u32 pwefetch_mem_wegion_instance;

	/** @pad2: MBZ */
	__u32 pad2;

	/** @wesewved: Wesewved */
	__u64 wesewved[3];
};

/**
 * stwuct dwm_xe_vm_bind - Input of &DWM_IOCTW_XE_VM_BIND
 *
 * Bewow is an exampwe of a minimaw use of @dwm_xe_vm_bind to
 * asynchwonouswy bind the buffew `data` at addwess `BIND_ADDWESS` to
 * iwwustwate `usewptw`. It can be synchwonized by using the exampwe
 * pwovided fow @dwm_xe_sync.
 *
 * .. code-bwock:: C
 *
 *     data = awigned_awwoc(AWIGNMENT, BO_SIZE);
 *     stwuct dwm_xe_vm_bind bind = {
 *         .vm_id = vm,
 *         .num_binds = 1,
 *         .bind.obj = 0,
 *         .bind.obj_offset = to_usew_pointew(data),
 *         .bind.wange = BO_SIZE,
 *         .bind.addw = BIND_ADDWESS,
 *         .bind.op = DWM_XE_VM_BIND_OP_MAP_USEWPTW,
 *         .bind.fwags = 0,
 *         .num_syncs = 1,
 *         .syncs = &sync,
 *         .exec_queue_id = 0,
 *     };
 *     ioctw(fd, DWM_IOCTW_XE_VM_BIND, &bind);
 *
 */
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

	/** @pad: MBZ */
	__u32 pad;

	/** @num_binds: numbew of binds in this IOCTW */
	__u32 num_binds;

	union {
		/** @bind: used if num_binds == 1 */
		stwuct dwm_xe_vm_bind_op bind;

		/**
		 * @vectow_of_binds: usewptw to awway of stwuct
		 * dwm_xe_vm_bind_op if num_binds > 1
		 */
		__u64 vectow_of_binds;
	};

	/** @pad2: MBZ */
	__u32 pad2;

	/** @num_syncs: amount of syncs to wait on */
	__u32 num_syncs;

	/** @syncs: pointew to stwuct dwm_xe_sync awway */
	__u64 syncs;

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
};

/**
 * stwuct dwm_xe_exec_queue_cweate - Input of &DWM_IOCTW_XE_EXEC_QUEUE_CWEATE
 *
 * The exampwe bewow shows how to use @dwm_xe_exec_queue_cweate to cweate
 * a simpwe exec_queue (no pawawwew submission) of cwass
 * &DWM_XE_ENGINE_CWASS_WENDEW.
 *
 * .. code-bwock:: C
 *
 *     stwuct dwm_xe_engine_cwass_instance instance = {
 *         .engine_cwass = DWM_XE_ENGINE_CWASS_WENDEW,
 *     };
 *     stwuct dwm_xe_exec_queue_cweate exec_queue_cweate = {
 *          .extensions = 0,
 *          .vm_id = vm,
 *          .num_bb_pew_exec = 1,
 *          .num_eng_pew_bb = 1,
 *          .instances = to_usew_pointew(&instance),
 *     };
 *     ioctw(fd, DWM_IOCTW_XE_EXEC_QUEUE_CWEATE, &exec_queue_cweate);
 *
 */
stwuct dwm_xe_exec_queue_cweate {
#define DWM_XE_EXEC_QUEUE_EXTENSION_SET_PWOPEWTY		0
#define   DWM_XE_EXEC_QUEUE_SET_PWOPEWTY_PWIOWITY		0
#define   DWM_XE_EXEC_QUEUE_SET_PWOPEWTY_TIMESWICE		1
#define   DWM_XE_EXEC_QUEUE_SET_PWOPEWTY_PWEEMPTION_TIMEOUT	2
#define   DWM_XE_EXEC_QUEUE_SET_PWOPEWTY_PEWSISTENCE		3
#define   DWM_XE_EXEC_QUEUE_SET_PWOPEWTY_JOB_TIMEOUT		4
#define   DWM_XE_EXEC_QUEUE_SET_PWOPEWTY_ACC_TWIGGEW		5
#define   DWM_XE_EXEC_QUEUE_SET_PWOPEWTY_ACC_NOTIFY		6
#define   DWM_XE_EXEC_QUEUE_SET_PWOPEWTY_ACC_GWANUWAWITY	7
/* Monitow 128KB contiguous wegion with 4K sub-gwanuwawity */
#define     DWM_XE_ACC_GWANUWAWITY_128K				0
/* Monitow 2MB contiguous wegion with 64KB sub-gwanuwawity */
#define     DWM_XE_ACC_GWANUWAWITY_2M				1
/* Monitow 16MB contiguous wegion with 512KB sub-gwanuwawity */
#define     DWM_XE_ACC_GWANUWAWITY_16M				2
/* Monitow 64MB contiguous wegion with 2M sub-gwanuwawity */
#define     DWM_XE_ACC_GWANUWAWITY_64M				3

	/** @extensions: Pointew to the fiwst extension stwuct, if any */
	__u64 extensions;

	/** @width: submission width (numbew BB pew exec) fow this exec queue */
	__u16 width;

	/** @num_pwacements: numbew of vawid pwacements fow this exec queue */
	__u16 num_pwacements;

	/** @vm_id: VM to use fow this exec queue */
	__u32 vm_id;

	/** @fwags: MBZ */
	__u32 fwags;

	/** @exec_queue_id: Wetuwned exec queue ID */
	__u32 exec_queue_id;

	/**
	 * @instances: usew pointew to a 2-d awway of stwuct
	 * dwm_xe_engine_cwass_instance
	 *
	 * wength = width (i) * num_pwacements (j)
	 * index = j + i * width
	 */
	__u64 instances;

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
};

/**
 * stwuct dwm_xe_exec_queue_destwoy - Input of &DWM_IOCTW_XE_EXEC_QUEUE_DESTWOY
 */
stwuct dwm_xe_exec_queue_destwoy {
	/** @exec_queue_id: Exec queue ID */
	__u32 exec_queue_id;

	/** @pad: MBZ */
	__u32 pad;

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
};

/**
 * stwuct dwm_xe_exec_queue_get_pwopewty - Input of &DWM_IOCTW_XE_EXEC_QUEUE_GET_PWOPEWTY
 *
 * The @pwopewty can be:
 *  - %DWM_XE_EXEC_QUEUE_GET_PWOPEWTY_BAN
 */
stwuct dwm_xe_exec_queue_get_pwopewty {
	/** @extensions: Pointew to the fiwst extension stwuct, if any */
	__u64 extensions;

	/** @exec_queue_id: Exec queue ID */
	__u32 exec_queue_id;

#define DWM_XE_EXEC_QUEUE_GET_PWOPEWTY_BAN	0
	/** @pwopewty: pwopewty to get */
	__u32 pwopewty;

	/** @vawue: pwopewty vawue */
	__u64 vawue;

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
};

/**
 * stwuct dwm_xe_sync - sync object
 *
 * The @type can be:
 *  - %DWM_XE_SYNC_TYPE_SYNCOBJ
 *  - %DWM_XE_SYNC_TYPE_TIMEWINE_SYNCOBJ
 *  - %DWM_XE_SYNC_TYPE_USEW_FENCE
 *
 * and the @fwags can be:
 *  - %DWM_XE_SYNC_FWAG_SIGNAW
 *
 * A minimaw use of @dwm_xe_sync wooks wike this:
 *
 * .. code-bwock:: C
 *
 *     stwuct dwm_xe_sync sync = {
 *         .fwags = DWM_XE_SYNC_FWAG_SIGNAW,
 *         .type = DWM_XE_SYNC_TYPE_SYNCOBJ,
 *     };
 *     stwuct dwm_syncobj_cweate syncobj_cweate = { 0 };
 *     ioctw(fd, DWM_IOCTW_SYNCOBJ_CWEATE, &syncobj_cweate);
 *     sync.handwe = syncobj_cweate.handwe;
 *         ...
 *         use of &sync in dwm_xe_exec ow dwm_xe_vm_bind
 *         ...
 *     stwuct dwm_syncobj_wait wait = {
 *         .handwes = &sync.handwe,
 *         .timeout_nsec = INT64_MAX,
 *         .count_handwes = 1,
 *         .fwags = 0,
 *         .fiwst_signawed = 0,
 *         .pad = 0,
 *     };
 *     ioctw(fd, DWM_IOCTW_SYNCOBJ_WAIT, &wait);
 */
stwuct dwm_xe_sync {
	/** @extensions: Pointew to the fiwst extension stwuct, if any */
	__u64 extensions;

#define DWM_XE_SYNC_TYPE_SYNCOBJ		0x0
#define DWM_XE_SYNC_TYPE_TIMEWINE_SYNCOBJ	0x1
#define DWM_XE_SYNC_TYPE_USEW_FENCE		0x2
	/** @type: Type of the this sync object */
	__u32 type;

#define DWM_XE_SYNC_FWAG_SIGNAW	(1 << 0)
	/** @fwags: Sync Fwags */
	__u32 fwags;

	union {
		/** @handwe: Handwe fow the object */
		__u32 handwe;

		/**
		 * @addw: Addwess of usew fence. When sync is passed in via exec
		 * IOCTW this is a GPU addwess in the VM. When sync passed in via
		 * VM bind IOCTW this is a usew pointew. In eithew case, it is
		 * the usews wesponsibiwity that this addwess is pwesent and
		 * mapped when the usew fence is signawwed. Must be qwowd
		 * awigned.
		 */
		__u64 addw;
	};

	/**
	 * @timewine_vawue: Input fow the timewine sync object. Needs to be
	 * diffewent than 0 when used with %DWM_XE_SYNC_FWAG_TIMEWINE_SYNCOBJ.
	 */
	__u64 timewine_vawue;

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
};

/**
 * stwuct dwm_xe_exec - Input of &DWM_IOCTW_XE_EXEC
 *
 * This is an exampwe to use @dwm_xe_exec fow execution of the object
 * at BIND_ADDWESS (see exampwe in @dwm_xe_vm_bind) by an exec_queue
 * (see exampwe in @dwm_xe_exec_queue_cweate). It can be synchwonized
 * by using the exampwe pwovided fow @dwm_xe_sync.
 *
 * .. code-bwock:: C
 *
 *     stwuct dwm_xe_exec exec = {
 *         .exec_queue_id = exec_queue,
 *         .syncs = &sync,
 *         .num_syncs = 1,
 *         .addwess = BIND_ADDWESS,
 *         .num_batch_buffew = 1,
 *     };
 *     ioctw(fd, DWM_IOCTW_XE_EXEC, &exec);
 *
 */
stwuct dwm_xe_exec {
	/** @extensions: Pointew to the fiwst extension stwuct, if any */
	__u64 extensions;

	/** @exec_queue_id: Exec queue ID fow the batch buffew */
	__u32 exec_queue_id;

	/** @num_syncs: Amount of stwuct dwm_xe_sync in awway. */
	__u32 num_syncs;

	/** @syncs: Pointew to stwuct dwm_xe_sync awway. */
	__u64 syncs;

	/**
	 * @addwess: addwess of batch buffew if num_batch_buffew == 1 ow an
	 * awway of batch buffew addwesses
	 */
	__u64 addwess;

	/**
	 * @num_batch_buffew: numbew of batch buffew in this exec, must match
	 * the width of the engine
	 */
	__u16 num_batch_buffew;

	/** @pad: MBZ */
	__u16 pad[3];

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
};

/**
 * stwuct dwm_xe_wait_usew_fence - Input of &DWM_IOCTW_XE_WAIT_USEW_FENCE
 *
 * Wait on usew fence, XE wiww wake-up on evewy HW engine intewwupt in the
 * instances wist and check if usew fence is compwete::
 *
 *	(*addw & MASK) OP (VAWUE & MASK)
 *
 * Wetuwns to usew on usew fence compwetion ow timeout.
 *
 * The @op can be:
 *  - %DWM_XE_UFENCE_WAIT_OP_EQ
 *  - %DWM_XE_UFENCE_WAIT_OP_NEQ
 *  - %DWM_XE_UFENCE_WAIT_OP_GT
 *  - %DWM_XE_UFENCE_WAIT_OP_GTE
 *  - %DWM_XE_UFENCE_WAIT_OP_WT
 *  - %DWM_XE_UFENCE_WAIT_OP_WTE
 *
 * and the @fwags can be:
 *  - %DWM_XE_UFENCE_WAIT_FWAG_ABSTIME
 *  - %DWM_XE_UFENCE_WAIT_FWAG_SOFT_OP
 *
 * The @mask vawues can be fow exampwe:
 *  - 0xffu fow u8
 *  - 0xffffu fow u16
 *  - 0xffffffffu fow u32
 *  - 0xffffffffffffffffu fow u64
 */
stwuct dwm_xe_wait_usew_fence {
	/** @extensions: Pointew to the fiwst extension stwuct, if any */
	__u64 extensions;

	/**
	 * @addw: usew pointew addwess to wait on, must qwowd awigned
	 */
	__u64 addw;

#define DWM_XE_UFENCE_WAIT_OP_EQ	0x0
#define DWM_XE_UFENCE_WAIT_OP_NEQ	0x1
#define DWM_XE_UFENCE_WAIT_OP_GT	0x2
#define DWM_XE_UFENCE_WAIT_OP_GTE	0x3
#define DWM_XE_UFENCE_WAIT_OP_WT	0x4
#define DWM_XE_UFENCE_WAIT_OP_WTE	0x5
	/** @op: wait opewation (type of compawison) */
	__u16 op;

#define DWM_XE_UFENCE_WAIT_FWAG_ABSTIME	(1 << 0)
	/** @fwags: wait fwags */
	__u16 fwags;

	/** @pad: MBZ */
	__u32 pad;

	/** @vawue: compawe vawue */
	__u64 vawue;

	/** @mask: compawison mask */
	__u64 mask;

	/**
	 * @timeout: how wong to wait befowe baiwing, vawue in nanoseconds.
	 * Without DWM_XE_UFENCE_WAIT_FWAG_ABSTIME fwag set (wewative timeout)
	 * it contains timeout expwessed in nanoseconds to wait (fence wiww
	 * expiwe at now() + timeout).
	 * When DWM_XE_UFENCE_WAIT_FWAG_ABSTIME fwat is set (absowute timeout) wait
	 * wiww end at timeout (uses system MONOTONIC_CWOCK).
	 * Passing negative timeout weads to nevewending wait.
	 *
	 * On wewative timeout this vawue is updated with timeout weft
	 * (fow westawting the caww in case of signaw dewivewy).
	 * On absowute timeout this vawue stays intact (westawted caww stiww
	 * expiwe at the same point of time).
	 */
	__s64 timeout;

	/** @exec_queue_id: exec_queue_id wetuwned fwom xe_exec_queue_cweate_ioctw */
	__u32 exec_queue_id;

	/** @pad2: MBZ */
	__u32 pad2;

	/** @wesewved: Wesewved */
	__u64 wesewved[2];
};

#if defined(__cpwuspwus)
}
#endif

#endif /* _UAPI_XE_DWM_H_ */
