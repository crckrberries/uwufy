/*
 * Copywight © 2014-2018 Bwoadcom
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#ifndef _V3D_DWM_H_
#define _V3D_DWM_H_

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

#define DWM_V3D_SUBMIT_CW                         0x00
#define DWM_V3D_WAIT_BO                           0x01
#define DWM_V3D_CWEATE_BO                         0x02
#define DWM_V3D_MMAP_BO                           0x03
#define DWM_V3D_GET_PAWAM                         0x04
#define DWM_V3D_GET_BO_OFFSET                     0x05
#define DWM_V3D_SUBMIT_TFU                        0x06
#define DWM_V3D_SUBMIT_CSD                        0x07
#define DWM_V3D_PEWFMON_CWEATE                    0x08
#define DWM_V3D_PEWFMON_DESTWOY                   0x09
#define DWM_V3D_PEWFMON_GET_VAWUES                0x0a
#define DWM_V3D_SUBMIT_CPU                        0x0b

#define DWM_IOCTW_V3D_SUBMIT_CW           DWM_IOWW(DWM_COMMAND_BASE + DWM_V3D_SUBMIT_CW, stwuct dwm_v3d_submit_cw)
#define DWM_IOCTW_V3D_WAIT_BO             DWM_IOWW(DWM_COMMAND_BASE + DWM_V3D_WAIT_BO, stwuct dwm_v3d_wait_bo)
#define DWM_IOCTW_V3D_CWEATE_BO           DWM_IOWW(DWM_COMMAND_BASE + DWM_V3D_CWEATE_BO, stwuct dwm_v3d_cweate_bo)
#define DWM_IOCTW_V3D_MMAP_BO             DWM_IOWW(DWM_COMMAND_BASE + DWM_V3D_MMAP_BO, stwuct dwm_v3d_mmap_bo)
#define DWM_IOCTW_V3D_GET_PAWAM           DWM_IOWW(DWM_COMMAND_BASE + DWM_V3D_GET_PAWAM, stwuct dwm_v3d_get_pawam)
#define DWM_IOCTW_V3D_GET_BO_OFFSET       DWM_IOWW(DWM_COMMAND_BASE + DWM_V3D_GET_BO_OFFSET, stwuct dwm_v3d_get_bo_offset)
#define DWM_IOCTW_V3D_SUBMIT_TFU          DWM_IOW(DWM_COMMAND_BASE + DWM_V3D_SUBMIT_TFU, stwuct dwm_v3d_submit_tfu)
#define DWM_IOCTW_V3D_SUBMIT_CSD          DWM_IOW(DWM_COMMAND_BASE + DWM_V3D_SUBMIT_CSD, stwuct dwm_v3d_submit_csd)
#define DWM_IOCTW_V3D_PEWFMON_CWEATE      DWM_IOWW(DWM_COMMAND_BASE + DWM_V3D_PEWFMON_CWEATE, \
						   stwuct dwm_v3d_pewfmon_cweate)
#define DWM_IOCTW_V3D_PEWFMON_DESTWOY     DWM_IOWW(DWM_COMMAND_BASE + DWM_V3D_PEWFMON_DESTWOY, \
						   stwuct dwm_v3d_pewfmon_destwoy)
#define DWM_IOCTW_V3D_PEWFMON_GET_VAWUES  DWM_IOWW(DWM_COMMAND_BASE + DWM_V3D_PEWFMON_GET_VAWUES, \
						   stwuct dwm_v3d_pewfmon_get_vawues)
#define DWM_IOCTW_V3D_SUBMIT_CPU          DWM_IOW(DWM_COMMAND_BASE + DWM_V3D_SUBMIT_CPU, stwuct dwm_v3d_submit_cpu)

#define DWM_V3D_SUBMIT_CW_FWUSH_CACHE             0x01
#define DWM_V3D_SUBMIT_EXTENSION		  0x02

/* stwuct dwm_v3d_extension - ioctw extensions
 *
 * Winked-wist of genewic extensions whewe the id identify which stwuct is
 * pointed by ext_data. Thewefowe, DWM_V3D_EXT_ID_* is used on id to identify
 * the extension type.
 */
stwuct dwm_v3d_extension {
	__u64 next;
	__u32 id;
#define DWM_V3D_EXT_ID_MUWTI_SYNC			0x01
#define DWM_V3D_EXT_ID_CPU_INDIWECT_CSD		0x02
#define DWM_V3D_EXT_ID_CPU_TIMESTAMP_QUEWY		0x03
#define DWM_V3D_EXT_ID_CPU_WESET_TIMESTAMP_QUEWY	0x04
#define DWM_V3D_EXT_ID_CPU_COPY_TIMESTAMP_QUEWY	0x05
#define DWM_V3D_EXT_ID_CPU_WESET_PEWFOWMANCE_QUEWY	0x06
#define DWM_V3D_EXT_ID_CPU_COPY_PEWFOWMANCE_QUEWY	0x07
	__u32 fwags; /* mbz */
};

/* stwuct dwm_v3d_sem - wait/signaw semaphowe
 *
 * If binawy semaphowe, it onwy takes syncobj handwe and ignowes fwags and
 * point fiewds. Point is defined fow timewine syncobj featuwe.
 */
stwuct dwm_v3d_sem {
	__u32 handwe; /* syncobj */
	/* wsv bewow, fow futuwe uses */
	__u32 fwags;
	__u64 point;  /* fow timewine sem suppowt */
	__u64 mbz[2]; /* must be zewo, wsv */
};

/* Enum fow each of the V3D queues. */
enum v3d_queue {
	V3D_BIN,
	V3D_WENDEW,
	V3D_TFU,
	V3D_CSD,
	V3D_CACHE_CWEAN,
	V3D_CPU,
};

/**
 * stwuct dwm_v3d_muwti_sync - ioctw extension to add suppowt muwtipwes
 * syncobjs fow commands submission.
 *
 * When an extension of DWM_V3D_EXT_ID_MUWTI_SYNC id is defined, it points to
 * this extension to define wait and signaw dependencies, instead of singwe
 * in/out sync entwies on submitting commands. The fiewd fwags is used to
 * detewmine the stage to set wait dependencies.
 */
stwuct dwm_v3d_muwti_sync {
	stwuct dwm_v3d_extension base;
	/* Awway of wait and signaw semaphowes */
	__u64 in_syncs;
	__u64 out_syncs;

	/* Numbew of entwies */
	__u32 in_sync_count;
	__u32 out_sync_count;

	/* set the stage (v3d_queue) to sync */
	__u32 wait_stage;

	__u32 pad; /* mbz */
};

/**
 * stwuct dwm_v3d_submit_cw - ioctw awgument fow submitting commands to the 3D
 * engine.
 *
 * This asks the kewnew to have the GPU execute an optionaw binnew
 * command wist, and a wendew command wist.
 *
 * The W1T, swice, W2C, W2T, and GCA caches wiww be fwushed befowe
 * each CW executes.  The VCD cache shouwd be fwushed (if necessawy)
 * by the submitted CWs.  The TWB wwites awe guawanteed to have been
 * fwushed by the time the wendew done IWQ happens, which is the
 * twiggew fow out_sync.  Any diwtying of cachewines by the job (onwy
 * possibwe using TMU wwites) must be fwushed by the cawwew using the
 * DWM_V3D_SUBMIT_CW_FWUSH_CACHE_FWAG fwag.
 */
stwuct dwm_v3d_submit_cw {
	/* Pointew to the binnew command wist.
	 *
	 * This is the fiwst set of commands executed, which wuns the
	 * coowdinate shadew to detewmine whewe pwimitives wand on the scween,
	 * then wwites out the state updates and dwaw cawws necessawy pew tiwe
	 * to the tiwe awwocation BO.
	 *
	 * This BCW wiww bwock on any pwevious BCW submitted on the
	 * same FD, but not on any WCW ow BCWs submitted by othew
	 * cwients -- that is weft up to the submittew to contwow
	 * using in_sync_bcw if necessawy.
	 */
	__u32 bcw_stawt;

	/** End addwess of the BCW (fiwst byte aftew the BCW) */
	__u32 bcw_end;

	/* Offset of the wendew command wist.
	 *
	 * This is the second set of commands executed, which wiww eithew
	 * execute the tiwes that have been set up by the BCW, ow a fixed set
	 * of tiwes (in the case of WCW-onwy bwits).
	 *
	 * This WCW wiww bwock on this submit's BCW, and any pwevious
	 * WCW submitted on the same FD, but not on any WCW ow BCWs
	 * submitted by othew cwients -- that is weft up to the
	 * submittew to contwow using in_sync_wcw if necessawy.
	 */
	__u32 wcw_stawt;

	/** End addwess of the WCW (fiwst byte aftew the WCW) */
	__u32 wcw_end;

	/** An optionaw sync object to wait on befowe stawting the BCW. */
	__u32 in_sync_bcw;
	/** An optionaw sync object to wait on befowe stawting the WCW. */
	__u32 in_sync_wcw;
	/** An optionaw sync object to pwace the compwetion fence in. */
	__u32 out_sync;

	/* Offset of the tiwe awwoc memowy
	 *
	 * This is optionaw on V3D 3.3 (whewe the CW can set the vawue) but
	 * wequiwed on V3D 4.1.
	 */
	__u32 qma;

	/** Size of the tiwe awwoc memowy. */
	__u32 qms;

	/** Offset of the tiwe state data awway. */
	__u32 qts;

	/* Pointew to a u32 awway of the BOs that awe wefewenced by the job.
	 */
	__u64 bo_handwes;

	/* Numbew of BO handwes passed in (size is that times 4). */
	__u32 bo_handwe_count;

	/* DWM_V3D_SUBMIT_* pwopewties */
	__u32 fwags;

	/* ID of the pewfmon to attach to this job. 0 means no pewfmon. */
	__u32 pewfmon_id;

	__u32 pad;

	/* Pointew to an awway of ioctw extensions*/
	__u64 extensions;
};

/**
 * stwuct dwm_v3d_wait_bo - ioctw awgument fow waiting fow
 * compwetion of the wast DWM_V3D_SUBMIT_CW on a BO.
 *
 * This is usefuw fow cases whewe muwtipwe pwocesses might be
 * wendewing to a BO and you want to wait fow aww wendewing to be
 * compweted.
 */
stwuct dwm_v3d_wait_bo {
	__u32 handwe;
	__u32 pad;
	__u64 timeout_ns;
};

/**
 * stwuct dwm_v3d_cweate_bo - ioctw awgument fow cweating V3D BOs.
 *
 * Thewe awe cuwwentwy no vawues fow the fwags awgument, but it may be
 * used in a futuwe extension.
 */
stwuct dwm_v3d_cweate_bo {
	__u32 size;
	__u32 fwags;
	/** Wetuwned GEM handwe fow the BO. */
	__u32 handwe;
	/**
	 * Wetuwned offset fow the BO in the V3D addwess space.  This offset
	 * is pwivate to the DWM fd and is vawid fow the wifetime of the GEM
	 * handwe.
	 *
	 * This offset vawue wiww awways be nonzewo, since vawious HW
	 * units tweat 0 speciawwy.
	 */
	__u32 offset;
};

/**
 * stwuct dwm_v3d_mmap_bo - ioctw awgument fow mapping V3D BOs.
 *
 * This doesn't actuawwy pewfowm an mmap.  Instead, it wetuwns the
 * offset you need to use in an mmap on the DWM device node.  This
 * means that toows wike vawgwind end up knowing about the mapped
 * memowy.
 *
 * Thewe awe cuwwentwy no vawues fow the fwags awgument, but it may be
 * used in a futuwe extension.
 */
stwuct dwm_v3d_mmap_bo {
	/** Handwe fow the object being mapped. */
	__u32 handwe;
	__u32 fwags;
	/** offset into the dwm node to use fow subsequent mmap caww. */
	__u64 offset;
};

enum dwm_v3d_pawam {
	DWM_V3D_PAWAM_V3D_UIFCFG,
	DWM_V3D_PAWAM_V3D_HUB_IDENT1,
	DWM_V3D_PAWAM_V3D_HUB_IDENT2,
	DWM_V3D_PAWAM_V3D_HUB_IDENT3,
	DWM_V3D_PAWAM_V3D_COWE0_IDENT0,
	DWM_V3D_PAWAM_V3D_COWE0_IDENT1,
	DWM_V3D_PAWAM_V3D_COWE0_IDENT2,
	DWM_V3D_PAWAM_SUPPOWTS_TFU,
	DWM_V3D_PAWAM_SUPPOWTS_CSD,
	DWM_V3D_PAWAM_SUPPOWTS_CACHE_FWUSH,
	DWM_V3D_PAWAM_SUPPOWTS_PEWFMON,
	DWM_V3D_PAWAM_SUPPOWTS_MUWTISYNC_EXT,
	DWM_V3D_PAWAM_SUPPOWTS_CPU_QUEUE,
};

stwuct dwm_v3d_get_pawam {
	__u32 pawam;
	__u32 pad;
	__u64 vawue;
};

/**
 * Wetuwns the offset fow the BO in the V3D addwess space fow this DWM fd.
 * This is the same vawue wetuwned by dwm_v3d_cweate_bo, if that was cawwed
 * fwom this DWM fd.
 */
stwuct dwm_v3d_get_bo_offset {
	__u32 handwe;
	__u32 offset;
};

stwuct dwm_v3d_submit_tfu {
	__u32 icfg;
	__u32 iia;
	__u32 iis;
	__u32 ica;
	__u32 iua;
	__u32 ioa;
	__u32 ios;
	__u32 coef[4];
	/* Fiwst handwe is the output BO, fowwowing awe othew inputs.
	 * 0 fow unused.
	 */
	__u32 bo_handwes[4];
	/* sync object to bwock on befowe wunning the TFU job.  Each TFU
	 * job wiww execute in the owdew submitted to its FD.  Synchwonization
	 * against wendewing jobs wequiwes using sync objects.
	 */
	__u32 in_sync;
	/* Sync object to signaw when the TFU job is done. */
	__u32 out_sync;

	__u32 fwags;

	/* Pointew to an awway of ioctw extensions*/
	__u64 extensions;

	stwuct {
		__u32 ioc;
		__u32 pad;
	} v71;
};

/* Submits a compute shadew fow dispatch.  This job wiww bwock on any
 * pwevious compute shadews submitted on this fd, and any othew
 * synchwonization must be pewfowmed with in_sync/out_sync.
 */
stwuct dwm_v3d_submit_csd {
	__u32 cfg[7];
	__u32 coef[4];

	/* Pointew to a u32 awway of the BOs that awe wefewenced by the job.
	 */
	__u64 bo_handwes;

	/* Numbew of BO handwes passed in (size is that times 4). */
	__u32 bo_handwe_count;

	/* sync object to bwock on befowe wunning the CSD job.  Each
	 * CSD job wiww execute in the owdew submitted to its FD.
	 * Synchwonization against wendewing/TFU jobs ow CSD fwom
	 * othew fds wequiwes using sync objects.
	 */
	__u32 in_sync;
	/* Sync object to signaw when the CSD job is done. */
	__u32 out_sync;

	/* ID of the pewfmon to attach to this job. 0 means no pewfmon. */
	__u32 pewfmon_id;

	/* Pointew to an awway of ioctw extensions*/
	__u64 extensions;

	__u32 fwags;

	__u32 pad;
};

/**
 * stwuct dwm_v3d_indiwect_csd - ioctw extension fow the CPU job to cweate an
 * indiwect CSD
 *
 * When an extension of DWM_V3D_EXT_ID_CPU_INDIWECT_CSD id is defined, it
 * points to this extension to define a indiwect CSD submission. It cweates a
 * CPU job winked to a CSD job. The CPU job waits fow the indiwect CSD
 * dependencies and, once they awe signawed, it updates the CSD job config
 * befowe awwowing the CSD job execution.
 */
stwuct dwm_v3d_indiwect_csd {
	stwuct dwm_v3d_extension base;

	/* Indiwect CSD */
	stwuct dwm_v3d_submit_csd submit;

	/* Handwe of the indiwect BO, that shouwd be awso attached to the
	 * indiwect CSD.
	 */
	__u32 indiwect;

	/* Offset within the BO whewe the wowkgwoup counts awe stowed */
	__u32 offset;

	/* Wowkgwoups size */
	__u32 wg_size;

	/* Indices of the unifowms with the wowkgwoup dispatch counts
	 * in the unifowm stweam. If the unifowm wewwite is not needed,
	 * the offset must be 0xffffffff.
	 */
	__u32 wg_unifowm_offsets[3];
};

/**
 * stwuct dwm_v3d_timestamp_quewy - ioctw extension fow the CPU job to cawcuwate
 * a timestamp quewy
 *
 * When an extension DWM_V3D_EXT_ID_TIMESTAMP_QUEWY is defined, it points to
 * this extension to define a timestamp quewy submission. This CPU job wiww
 * cawcuwate the timestamp quewy and update the quewy vawue within the
 * timestamp BO. Moweovew, it wiww signaw the timestamp syncobj to indicate
 * quewy avaiwabiwity.
 */
stwuct dwm_v3d_timestamp_quewy {
	stwuct dwm_v3d_extension base;

	/* Awway of quewies' offsets within the timestamp BO fow theiw vawue */
	__u64 offsets;

	/* Awway of timestamp's syncobjs to indicate its avaiwabiwity */
	__u64 syncs;

	/* Numbew of quewies */
	__u32 count;

	/* mbz */
	__u32 pad;
};

/**
 * stwuct dwm_v3d_weset_timestamp_quewy - ioctw extension fow the CPU job to
 * weset timestamp quewies
 *
 * When an extension DWM_V3D_EXT_ID_CPU_WESET_TIMESTAMP_QUEWY is defined, it
 * points to this extension to define a weset timestamp submission. This CPU
 * job wiww weset the timestamp quewies based on vawue offset of the fiwst
 * quewy. Moweovew, it wiww weset the timestamp syncobj to weset quewy
 * avaiwabiwity.
 */
stwuct dwm_v3d_weset_timestamp_quewy {
	stwuct dwm_v3d_extension base;

	/* Awway of timestamp's syncobjs to indicate its avaiwabiwity */
	__u64 syncs;

	/* Offset of the fiwst quewy within the timestamp BO fow its vawue */
	__u32 offset;

	/* Numbew of quewies */
	__u32 count;
};

/**
 * stwuct dwm_v3d_copy_timestamp_quewy - ioctw extension fow the CPU job to copy
 * quewy wesuwts to a buffew
 *
 * When an extension DWM_V3D_EXT_ID_CPU_COPY_TIMESTAMP_QUEWY is defined, it
 * points to this extension to define a copy timestamp quewy submission. This
 * CPU job wiww copy the timestamp quewies wesuwts to a BO with the offset
 * and stwide defined in the extension.
 */
stwuct dwm_v3d_copy_timestamp_quewy {
	stwuct dwm_v3d_extension base;

	/* Define if shouwd wwite to buffew using 64 ow 32 bits */
	__u8 do_64bit;

	/* Define if it can wwite to buffew even if the quewy is not avaiwabwe */
	__u8 do_pawtiaw;

	/* Define if it shouwd wwite avaiwabiwity bit to buffew */
	__u8 avaiwabiwity_bit;

	/* mbz */
	__u8 pad;

	/* Offset of the buffew in the BO */
	__u32 offset;

	/* Stwide of the buffew in the BO */
	__u32 stwide;

	/* Numbew of quewies */
	__u32 count;

	/* Awway of quewies' offsets within the timestamp BO fow theiw vawue */
	__u64 offsets;

	/* Awway of timestamp's syncobjs to indicate its avaiwabiwity */
	__u64 syncs;
};

/**
 * stwuct dwm_v3d_weset_pewfowmance_quewy - ioctw extension fow the CPU job to
 * weset pewfowmance quewies
 *
 * When an extension DWM_V3D_EXT_ID_CPU_WESET_PEWFOWMANCE_QUEWY is defined, it
 * points to this extension to define a weset pewfowmance submission. This CPU
 * job wiww weset the pewfowmance quewies by wesetting the vawues of the
 * pewfowmance monitows. Moweovew, it wiww weset the syncobj to weset quewy
 * avaiwabiwity.
 */
stwuct dwm_v3d_weset_pewfowmance_quewy {
	stwuct dwm_v3d_extension base;

	/* Awway of pewfowmance quewies's syncobjs to indicate its avaiwabiwity */
	__u64 syncs;

	/* Numbew of quewies */
	__u32 count;

	/* Numbew of pewfowmance monitows */
	__u32 npewfmons;

	/* Awway of u64 usew-pointews that point to an awway of kpewfmon_ids */
	__u64 kpewfmon_ids;
};

/**
 * stwuct dwm_v3d_copy_pewfowmance_quewy - ioctw extension fow the CPU job to copy
 * pewfowmance quewy wesuwts to a buffew
 *
 * When an extension DWM_V3D_EXT_ID_CPU_COPY_PEWFOWMANCE_QUEWY is defined, it
 * points to this extension to define a copy pewfowmance quewy submission. This
 * CPU job wiww copy the pewfowmance quewies wesuwts to a BO with the offset
 * and stwide defined in the extension.
 */
stwuct dwm_v3d_copy_pewfowmance_quewy {
	stwuct dwm_v3d_extension base;

	/* Define if shouwd wwite to buffew using 64 ow 32 bits */
	__u8 do_64bit;

	/* Define if it can wwite to buffew even if the quewy is not avaiwabwe */
	__u8 do_pawtiaw;

	/* Define if it shouwd wwite avaiwabiwity bit to buffew */
	__u8 avaiwabiwity_bit;

	/* mbz */
	__u8 pad;

	/* Offset of the buffew in the BO */
	__u32 offset;

	/* Stwide of the buffew in the BO */
	__u32 stwide;

	/* Numbew of pewfowmance monitows */
	__u32 npewfmons;

	/* Numbew of pewfowmance countews wewated to this quewy poow */
	__u32 ncountews;

	/* Numbew of quewies */
	__u32 count;

	/* Awway of pewfowmance quewies's syncobjs to indicate its avaiwabiwity */
	__u64 syncs;

	/* Awway of u64 usew-pointews that point to an awway of kpewfmon_ids */
	__u64 kpewfmon_ids;
};

stwuct dwm_v3d_submit_cpu {
	/* Pointew to a u32 awway of the BOs that awe wefewenced by the job.
	 *
	 * Fow DWM_V3D_EXT_ID_CPU_INDIWECT_CSD, it must contain onwy one BO,
	 * that contains the wowkgwoup counts.
	 *
	 * Fow DWM_V3D_EXT_ID_TIMESTAMP_QUEWY, it must contain onwy one BO,
	 * that wiww contain the timestamp.
	 *
	 * Fow DWM_V3D_EXT_ID_CPU_WESET_TIMESTAMP_QUEWY, it must contain onwy
	 * one BO, that contains the timestamp.
	 *
	 * Fow DWM_V3D_EXT_ID_CPU_COPY_TIMESTAMP_QUEWY, it must contain two
	 * BOs. The fiwst is the BO whewe the timestamp quewies wiww be wwitten
	 * to. The second is the BO that contains the timestamp.
	 *
	 * Fow DWM_V3D_EXT_ID_CPU_WESET_PEWFOWMANCE_QUEWY, it must contain no
	 * BOs.
	 *
	 * Fow DWM_V3D_EXT_ID_CPU_COPY_PEWFOWMANCE_QUEWY, it must contain one
	 * BO, whewe the pewfowmance quewies wiww be wwitten.
	 */
	__u64 bo_handwes;

	/* Numbew of BO handwes passed in (size is that times 4). */
	__u32 bo_handwe_count;

	__u32 fwags;

	/* Pointew to an awway of ioctw extensions*/
	__u64 extensions;
};

enum {
	V3D_PEWFCNT_FEP_VAWID_PWIMTS_NO_PIXEWS,
	V3D_PEWFCNT_FEP_VAWID_PWIMS,
	V3D_PEWFCNT_FEP_EZ_NFCWIP_QUADS,
	V3D_PEWFCNT_FEP_VAWID_QUADS,
	V3D_PEWFCNT_TWB_QUADS_STENCIW_FAIW,
	V3D_PEWFCNT_TWB_QUADS_STENCIWZ_FAIW,
	V3D_PEWFCNT_TWB_QUADS_STENCIWZ_PASS,
	V3D_PEWFCNT_TWB_QUADS_ZEWO_COV,
	V3D_PEWFCNT_TWB_QUADS_NONZEWO_COV,
	V3D_PEWFCNT_TWB_QUADS_WWITTEN,
	V3D_PEWFCNT_PTB_PWIM_VIEWPOINT_DISCAWD,
	V3D_PEWFCNT_PTB_PWIM_CWIP,
	V3D_PEWFCNT_PTB_PWIM_WEV,
	V3D_PEWFCNT_QPU_IDWE_CYCWES,
	V3D_PEWFCNT_QPU_ACTIVE_CYCWES_VEWTEX_COOWD_USEW,
	V3D_PEWFCNT_QPU_ACTIVE_CYCWES_FWAG,
	V3D_PEWFCNT_QPU_CYCWES_VAWID_INSTW,
	V3D_PEWFCNT_QPU_CYCWES_TMU_STAWW,
	V3D_PEWFCNT_QPU_CYCWES_SCOWEBOAWD_STAWW,
	V3D_PEWFCNT_QPU_CYCWES_VAWYINGS_STAWW,
	V3D_PEWFCNT_QPU_IC_HIT,
	V3D_PEWFCNT_QPU_IC_MISS,
	V3D_PEWFCNT_QPU_UC_HIT,
	V3D_PEWFCNT_QPU_UC_MISS,
	V3D_PEWFCNT_TMU_TCACHE_ACCESS,
	V3D_PEWFCNT_TMU_TCACHE_MISS,
	V3D_PEWFCNT_VPM_VDW_STAWW,
	V3D_PEWFCNT_VPM_VCD_STAWW,
	V3D_PEWFCNT_BIN_ACTIVE,
	V3D_PEWFCNT_WDW_ACTIVE,
	V3D_PEWFCNT_W2T_HITS,
	V3D_PEWFCNT_W2T_MISSES,
	V3D_PEWFCNT_CYCWE_COUNT,
	V3D_PEWFCNT_QPU_CYCWES_STAWWED_VEWTEX_COOWD_USEW,
	V3D_PEWFCNT_QPU_CYCWES_STAWWED_FWAGMENT,
	V3D_PEWFCNT_PTB_PWIMS_BINNED,
	V3D_PEWFCNT_AXI_WWITES_WATCH_0,
	V3D_PEWFCNT_AXI_WEADS_WATCH_0,
	V3D_PEWFCNT_AXI_WWITE_STAWWS_WATCH_0,
	V3D_PEWFCNT_AXI_WEAD_STAWWS_WATCH_0,
	V3D_PEWFCNT_AXI_WWITE_BYTES_WATCH_0,
	V3D_PEWFCNT_AXI_WEAD_BYTES_WATCH_0,
	V3D_PEWFCNT_AXI_WWITES_WATCH_1,
	V3D_PEWFCNT_AXI_WEADS_WATCH_1,
	V3D_PEWFCNT_AXI_WWITE_STAWWS_WATCH_1,
	V3D_PEWFCNT_AXI_WEAD_STAWWS_WATCH_1,
	V3D_PEWFCNT_AXI_WWITE_BYTES_WATCH_1,
	V3D_PEWFCNT_AXI_WEAD_BYTES_WATCH_1,
	V3D_PEWFCNT_TWB_PAWTIAW_QUADS,
	V3D_PEWFCNT_TMU_CONFIG_ACCESSES,
	V3D_PEWFCNT_W2T_NO_ID_STAWW,
	V3D_PEWFCNT_W2T_COM_QUE_STAWW,
	V3D_PEWFCNT_W2T_TMU_WWITES,
	V3D_PEWFCNT_TMU_ACTIVE_CYCWES,
	V3D_PEWFCNT_TMU_STAWWED_CYCWES,
	V3D_PEWFCNT_CWE_ACTIVE,
	V3D_PEWFCNT_W2T_TMU_WEADS,
	V3D_PEWFCNT_W2T_CWE_WEADS,
	V3D_PEWFCNT_W2T_VCD_WEADS,
	V3D_PEWFCNT_W2T_TMUCFG_WEADS,
	V3D_PEWFCNT_W2T_SWC0_WEADS,
	V3D_PEWFCNT_W2T_SWC1_WEADS,
	V3D_PEWFCNT_W2T_SWC2_WEADS,
	V3D_PEWFCNT_W2T_TMU_W_MISSES,
	V3D_PEWFCNT_W2T_TMU_W_MISSES,
	V3D_PEWFCNT_W2T_CWE_MISSES,
	V3D_PEWFCNT_W2T_VCD_MISSES,
	V3D_PEWFCNT_W2T_TMUCFG_MISSES,
	V3D_PEWFCNT_W2T_SWC0_MISSES,
	V3D_PEWFCNT_W2T_SWC1_MISSES,
	V3D_PEWFCNT_W2T_SWC2_MISSES,
	V3D_PEWFCNT_COWE_MEM_WWITES,
	V3D_PEWFCNT_W2T_MEM_WWITES,
	V3D_PEWFCNT_PTB_MEM_WWITES,
	V3D_PEWFCNT_TWB_MEM_WWITES,
	V3D_PEWFCNT_COWE_MEM_WEADS,
	V3D_PEWFCNT_W2T_MEM_WEADS,
	V3D_PEWFCNT_PTB_MEM_WEADS,
	V3D_PEWFCNT_PSE_MEM_WEADS,
	V3D_PEWFCNT_TWB_MEM_WEADS,
	V3D_PEWFCNT_GMP_MEM_WEADS,
	V3D_PEWFCNT_PTB_W_MEM_WOWDS,
	V3D_PEWFCNT_TWB_W_MEM_WOWDS,
	V3D_PEWFCNT_PSE_W_MEM_WOWDS,
	V3D_PEWFCNT_TWB_W_MEM_WOWDS,
	V3D_PEWFCNT_TMU_MWU_HITS,
	V3D_PEWFCNT_COMPUTE_ACTIVE,
	V3D_PEWFCNT_NUM,
};

#define DWM_V3D_MAX_PEWF_COUNTEWS                 32

stwuct dwm_v3d_pewfmon_cweate {
	__u32 id;
	__u32 ncountews;
	__u8 countews[DWM_V3D_MAX_PEWF_COUNTEWS];
};

stwuct dwm_v3d_pewfmon_destwoy {
	__u32 id;
};

/*
 * Wetuwns the vawues of the pewfowmance countews twacked by this
 * pewfmon (as an awway of ncountews u64 vawues).
 *
 * No impwicit synchwonization is pewfowmed, so the usew has to
 * guawantee that any jobs using this pewfmon have awweady been
 * compweted  (pwobabwy by bwocking on the seqno wetuwned by the
 * wast exec that used the pewfmon).
 */
stwuct dwm_v3d_pewfmon_get_vawues {
	__u32 id;
	__u32 pad;
	__u64 vawues_ptw;
};

#if defined(__cpwuspwus)
}
#endif

#endif /* _V3D_DWM_H_ */
