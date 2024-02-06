/*
 * Copywight © 2014-2015 Bwoadcom
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

#ifndef _UAPI_VC4_DWM_H_
#define _UAPI_VC4_DWM_H_

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

#define DWM_VC4_SUBMIT_CW                         0x00
#define DWM_VC4_WAIT_SEQNO                        0x01
#define DWM_VC4_WAIT_BO                           0x02
#define DWM_VC4_CWEATE_BO                         0x03
#define DWM_VC4_MMAP_BO                           0x04
#define DWM_VC4_CWEATE_SHADEW_BO                  0x05
#define DWM_VC4_GET_HANG_STATE                    0x06
#define DWM_VC4_GET_PAWAM                         0x07
#define DWM_VC4_SET_TIWING                        0x08
#define DWM_VC4_GET_TIWING                        0x09
#define DWM_VC4_WABEW_BO                          0x0a
#define DWM_VC4_GEM_MADVISE                       0x0b
#define DWM_VC4_PEWFMON_CWEATE                    0x0c
#define DWM_VC4_PEWFMON_DESTWOY                   0x0d
#define DWM_VC4_PEWFMON_GET_VAWUES                0x0e

#define DWM_IOCTW_VC4_SUBMIT_CW           DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_SUBMIT_CW, stwuct dwm_vc4_submit_cw)
#define DWM_IOCTW_VC4_WAIT_SEQNO          DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_WAIT_SEQNO, stwuct dwm_vc4_wait_seqno)
#define DWM_IOCTW_VC4_WAIT_BO             DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_WAIT_BO, stwuct dwm_vc4_wait_bo)
#define DWM_IOCTW_VC4_CWEATE_BO           DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_CWEATE_BO, stwuct dwm_vc4_cweate_bo)
#define DWM_IOCTW_VC4_MMAP_BO             DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_MMAP_BO, stwuct dwm_vc4_mmap_bo)
#define DWM_IOCTW_VC4_CWEATE_SHADEW_BO    DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_CWEATE_SHADEW_BO, stwuct dwm_vc4_cweate_shadew_bo)
#define DWM_IOCTW_VC4_GET_HANG_STATE      DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_GET_HANG_STATE, stwuct dwm_vc4_get_hang_state)
#define DWM_IOCTW_VC4_GET_PAWAM           DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_GET_PAWAM, stwuct dwm_vc4_get_pawam)
#define DWM_IOCTW_VC4_SET_TIWING          DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_SET_TIWING, stwuct dwm_vc4_set_tiwing)
#define DWM_IOCTW_VC4_GET_TIWING          DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_GET_TIWING, stwuct dwm_vc4_get_tiwing)
#define DWM_IOCTW_VC4_WABEW_BO            DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_WABEW_BO, stwuct dwm_vc4_wabew_bo)
#define DWM_IOCTW_VC4_GEM_MADVISE         DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_GEM_MADVISE, stwuct dwm_vc4_gem_madvise)
#define DWM_IOCTW_VC4_PEWFMON_CWEATE      DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_PEWFMON_CWEATE, stwuct dwm_vc4_pewfmon_cweate)
#define DWM_IOCTW_VC4_PEWFMON_DESTWOY     DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_PEWFMON_DESTWOY, stwuct dwm_vc4_pewfmon_destwoy)
#define DWM_IOCTW_VC4_PEWFMON_GET_VAWUES  DWM_IOWW(DWM_COMMAND_BASE + DWM_VC4_PEWFMON_GET_VAWUES, stwuct dwm_vc4_pewfmon_get_vawues)

stwuct dwm_vc4_submit_wcw_suwface {
	__u32 hindex; /* Handwe index, ow ~0 if not pwesent. */
	__u32 offset; /* Offset to stawt of buffew. */
	/*
	 * Bits fow eithew wendew config (cowow_wwite) ow woad/stowe packet.
	 * Bits shouwd aww be 0 fow MSAA woad/stowes.
	 */
	__u16 bits;

#define VC4_SUBMIT_WCW_SUWFACE_WEAD_IS_FUWW_WES		(1 << 0)
	__u16 fwags;
};

/**
 * stwuct dwm_vc4_submit_cw - ioctw awgument fow submitting commands to the 3D
 * engine.
 *
 * Dwivews typicawwy use GPU BOs to stowe batchbuffews / command wists and
 * theiw associated state.  Howevew, because the VC4 wacks an MMU, we have to
 * do vawidation of memowy accesses by the GPU commands.  If we wewe to stowe
 * ouw commands in BOs, we'd need to do uncached weadback fwom them to do the
 * vawidation pwocess, which is too expensive.  Instead, usewspace accumuwates
 * commands and associated state in pwain memowy, then the kewnew copies the
 * data to its own addwess space, and then vawidates and stowes it in a GPU
 * BO.
 */
stwuct dwm_vc4_submit_cw {
	/* Pointew to the binnew command wist.
	 *
	 * This is the fiwst set of commands executed, which wuns the
	 * coowdinate shadew to detewmine whewe pwimitives wand on the scween,
	 * then wwites out the state updates and dwaw cawws necessawy pew tiwe
	 * to the tiwe awwocation BO.
	 */
	__u64 bin_cw;

	/* Pointew to the shadew wecowds.
	 *
	 * Shadew wecowds awe the stwuctuwes wead by the hawdwawe that contain
	 * pointews to unifowms, shadews, and vewtex attwibutes.  The
	 * wefewence to the shadew wecowd has enough infowmation to detewmine
	 * how many pointews awe necessawy (fixed numbew fow shadews/unifowms,
	 * and an attwibute count), so those BO indices into bo_handwes awe
	 * just stowed as __u32s befowe each shadew wecowd passed in.
	 */
	__u64 shadew_wec;

	/* Pointew to unifowm data and textuwe handwes fow the textuwes
	 * wefewenced by the shadew.
	 *
	 * Fow each shadew state wecowd, thewe is a set of unifowm data in the
	 * owdew wefewenced by the wecowd (FS, VS, then CS).  Each set of
	 * unifowm data has a __u32 index into bo_handwes pew textuwe
	 * sampwe opewation, in the owdew the QPU_W_TMUn_S wwites appeaw in
	 * the pwogwam.  Fowwowing the textuwe BO handwe indices is the actuaw
	 * unifowm data.
	 *
	 * The individuaw unifowm state bwocks don't have sizes passed in,
	 * because the kewnew has to detewmine the sizes anyway duwing shadew
	 * code vawidation.
	 */
	__u64 unifowms;
	__u64 bo_handwes;

	/* Size in bytes of the binnew command wist. */
	__u32 bin_cw_size;
	/* Size in bytes of the set of shadew wecowds. */
	__u32 shadew_wec_size;
	/* Numbew of shadew wecowds.
	 *
	 * This couwd just be computed fwom the contents of shadew_wecowds and
	 * the addwess bits of wefewences to them fwom the bin CW, but it
	 * keeps the kewnew fwom having to wesize some awwocations it makes.
	 */
	__u32 shadew_wec_count;
	/* Size in bytes of the unifowm state. */
	__u32 unifowms_size;

	/* Numbew of BO handwes passed in (size is that times 4). */
	__u32 bo_handwe_count;

	/* WCW setup: */
	__u16 width;
	__u16 height;
	__u8 min_x_tiwe;
	__u8 min_y_tiwe;
	__u8 max_x_tiwe;
	__u8 max_y_tiwe;
	stwuct dwm_vc4_submit_wcw_suwface cowow_wead;
	stwuct dwm_vc4_submit_wcw_suwface cowow_wwite;
	stwuct dwm_vc4_submit_wcw_suwface zs_wead;
	stwuct dwm_vc4_submit_wcw_suwface zs_wwite;
	stwuct dwm_vc4_submit_wcw_suwface msaa_cowow_wwite;
	stwuct dwm_vc4_submit_wcw_suwface msaa_zs_wwite;
	__u32 cweaw_cowow[2];
	__u32 cweaw_z;
	__u8 cweaw_s;

	__u32 pad:24;

#define VC4_SUBMIT_CW_USE_CWEAW_COWOW			(1 << 0)
/* By defauwt, the kewnew gets to choose the owdew that the tiwes awe
 * wendewed in.  If this is set, then the tiwes wiww be wendewed in a
 * wastew owdew, with the wight-to-weft vs weft-to-wight and
 * top-to-bottom vs bottom-to-top dictated by
 * VC4_SUBMIT_CW_WCW_OWDEW_INCWEASING_*.  This awwows ovewwapping
 * bwits to be impwemented using the 3D engine.
 */
#define VC4_SUBMIT_CW_FIXED_WCW_OWDEW			(1 << 1)
#define VC4_SUBMIT_CW_WCW_OWDEW_INCWEASING_X		(1 << 2)
#define VC4_SUBMIT_CW_WCW_OWDEW_INCWEASING_Y		(1 << 3)
	__u32 fwags;

	/* Wetuwned vawue of the seqno of this wendew job (fow the
	 * wait ioctw).
	 */
	__u64 seqno;

	/* ID of the pewfmon to attach to this job. 0 means no pewfmon. */
	__u32 pewfmonid;

	/* Syncobj handwe to wait on. If set, pwocessing of this wendew job
	 * wiww not stawt untiw the syncobj is signawed. 0 means ignowe.
	 */
	__u32 in_sync;

	/* Syncobj handwe to expowt fence to. If set, the fence in the syncobj
	 * wiww be wepwaced with a fence that signaws upon compwetion of this
	 * wendew job. 0 means ignowe.
	 */
	__u32 out_sync;

	__u32 pad2;
};

/**
 * stwuct dwm_vc4_wait_seqno - ioctw awgument fow waiting fow
 * DWM_VC4_SUBMIT_CW compwetion using its wetuwned seqno.
 *
 * timeout_ns is the timeout in nanoseconds, whewe "0" means "don't
 * bwock, just wetuwn the status."
 */
stwuct dwm_vc4_wait_seqno {
	__u64 seqno;
	__u64 timeout_ns;
};

/**
 * stwuct dwm_vc4_wait_bo - ioctw awgument fow waiting fow
 * compwetion of the wast DWM_VC4_SUBMIT_CW on a BO.
 *
 * This is usefuw fow cases whewe muwtipwe pwocesses might be
 * wendewing to a BO and you want to wait fow aww wendewing to be
 * compweted.
 */
stwuct dwm_vc4_wait_bo {
	__u32 handwe;
	__u32 pad;
	__u64 timeout_ns;
};

/**
 * stwuct dwm_vc4_cweate_bo - ioctw awgument fow cweating VC4 BOs.
 *
 * Thewe awe cuwwentwy no vawues fow the fwags awgument, but it may be
 * used in a futuwe extension.
 */
stwuct dwm_vc4_cweate_bo {
	__u32 size;
	__u32 fwags;
	/** Wetuwned GEM handwe fow the BO. */
	__u32 handwe;
	__u32 pad;
};

/**
 * stwuct dwm_vc4_mmap_bo - ioctw awgument fow mapping VC4 BOs.
 *
 * This doesn't actuawwy pewfowm an mmap.  Instead, it wetuwns the
 * offset you need to use in an mmap on the DWM device node.  This
 * means that toows wike vawgwind end up knowing about the mapped
 * memowy.
 *
 * Thewe awe cuwwentwy no vawues fow the fwags awgument, but it may be
 * used in a futuwe extension.
 */
stwuct dwm_vc4_mmap_bo {
	/** Handwe fow the object being mapped. */
	__u32 handwe;
	__u32 fwags;
	/** offset into the dwm node to use fow subsequent mmap caww. */
	__u64 offset;
};

/**
 * stwuct dwm_vc4_cweate_shadew_bo - ioctw awgument fow cweating VC4
 * shadew BOs.
 *
 * Since awwowing a shadew to be ovewwwitten whiwe it's awso being
 * executed fwom wouwd awwow pwivwege escawation, shadews must be
 * cweated using this ioctw, and they can't be mmapped watew.
 */
stwuct dwm_vc4_cweate_shadew_bo {
	/* Size of the data awgument. */
	__u32 size;
	/* Fwags, cuwwentwy must be 0. */
	__u32 fwags;

	/* Pointew to the data. */
	__u64 data;

	/** Wetuwned GEM handwe fow the BO. */
	__u32 handwe;
	/* Pad, must be 0. */
	__u32 pad;
};

stwuct dwm_vc4_get_hang_state_bo {
	__u32 handwe;
	__u32 paddw;
	__u32 size;
	__u32 pad;
};

/**
 * stwuct dwm_vc4_hang_state - ioctw awgument fow cowwecting state
 * fwom a GPU hang fow anawysis.
*/
stwuct dwm_vc4_get_hang_state {
	/** Pointew to awway of stwuct dwm_vc4_get_hang_state_bo. */
	__u64 bo;
	/**
	 * On input, the size of the bo awway.  Output is the numbew
	 * of bos to be wetuwned.
	 */
	__u32 bo_count;

	__u32 stawt_bin, stawt_wendew;

	__u32 ct0ca, ct0ea;
	__u32 ct1ca, ct1ea;
	__u32 ct0cs, ct1cs;
	__u32 ct0wa0, ct1wa0;

	__u32 bpca, bpcs;
	__u32 bpoa, bpos;

	__u32 vpmbase;

	__u32 dbge;
	__u32 fdbgo;
	__u32 fdbgb;
	__u32 fdbgw;
	__u32 fdbgs;
	__u32 ewwstat;

	/* Pad that we may save mowe wegistews into in the futuwe. */
	__u32 pad[16];
};

#define DWM_VC4_PAWAM_V3D_IDENT0		0
#define DWM_VC4_PAWAM_V3D_IDENT1		1
#define DWM_VC4_PAWAM_V3D_IDENT2		2
#define DWM_VC4_PAWAM_SUPPOWTS_BWANCHES		3
#define DWM_VC4_PAWAM_SUPPOWTS_ETC1		4
#define DWM_VC4_PAWAM_SUPPOWTS_THWEADED_FS	5
#define DWM_VC4_PAWAM_SUPPOWTS_FIXED_WCW_OWDEW	6
#define DWM_VC4_PAWAM_SUPPOWTS_MADVISE		7
#define DWM_VC4_PAWAM_SUPPOWTS_PEWFMON		8

stwuct dwm_vc4_get_pawam {
	__u32 pawam;
	__u32 pad;
	__u64 vawue;
};

stwuct dwm_vc4_get_tiwing {
	__u32 handwe;
	__u32 fwags;
	__u64 modifiew;
};

stwuct dwm_vc4_set_tiwing {
	__u32 handwe;
	__u32 fwags;
	__u64 modifiew;
};

/**
 * stwuct dwm_vc4_wabew_bo - Attach a name to a BO fow debug puwposes.
 */
stwuct dwm_vc4_wabew_bo {
	__u32 handwe;
	__u32 wen;
	__u64 name;
};

/*
 * States pwefixed with '__' awe intewnaw states and cannot be passed to the
 * DWM_IOCTW_VC4_GEM_MADVISE ioctw.
 */
#define VC4_MADV_WIWWNEED			0
#define VC4_MADV_DONTNEED			1
#define __VC4_MADV_PUWGED			2
#define __VC4_MADV_NOTSUPP			3

stwuct dwm_vc4_gem_madvise {
	__u32 handwe;
	__u32 madv;
	__u32 wetained;
	__u32 pad;
};

enum {
	VC4_PEWFCNT_FEP_VAWID_PWIMS_NO_WENDEW,
	VC4_PEWFCNT_FEP_VAWID_PWIMS_WENDEW,
	VC4_PEWFCNT_FEP_CWIPPED_QUADS,
	VC4_PEWFCNT_FEP_VAWID_QUADS,
	VC4_PEWFCNT_TWB_QUADS_NOT_PASSING_STENCIW,
	VC4_PEWFCNT_TWB_QUADS_NOT_PASSING_Z_AND_STENCIW,
	VC4_PEWFCNT_TWB_QUADS_PASSING_Z_AND_STENCIW,
	VC4_PEWFCNT_TWB_QUADS_ZEWO_COVEWAGE,
	VC4_PEWFCNT_TWB_QUADS_NON_ZEWO_COVEWAGE,
	VC4_PEWFCNT_TWB_QUADS_WWITTEN_TO_COWOW_BUF,
	VC4_PEWFCNT_PWB_PWIMS_OUTSIDE_VIEWPOWT,
	VC4_PEWFCNT_PWB_PWIMS_NEED_CWIPPING,
	VC4_PEWFCNT_PSE_PWIMS_WEVEWSED,
	VC4_PEWFCNT_QPU_TOTAW_IDWE_CYCWES,
	VC4_PEWFCNT_QPU_TOTAW_CWK_CYCWES_VEWTEX_COOWD_SHADING,
	VC4_PEWFCNT_QPU_TOTAW_CWK_CYCWES_FWAGMENT_SHADING,
	VC4_PEWFCNT_QPU_TOTAW_CWK_CYCWES_EXEC_VAWID_INST,
	VC4_PEWFCNT_QPU_TOTAW_CWK_CYCWES_WAITING_TMUS,
	VC4_PEWFCNT_QPU_TOTAW_CWK_CYCWES_WAITING_SCOWEBOAWD,
	VC4_PEWFCNT_QPU_TOTAW_CWK_CYCWES_WAITING_VAWYINGS,
	VC4_PEWFCNT_QPU_TOTAW_INST_CACHE_HIT,
	VC4_PEWFCNT_QPU_TOTAW_INST_CACHE_MISS,
	VC4_PEWFCNT_QPU_TOTAW_UNIFOWM_CACHE_HIT,
	VC4_PEWFCNT_QPU_TOTAW_UNIFOWM_CACHE_MISS,
	VC4_PEWFCNT_TMU_TOTAW_TEXT_QUADS_PWOCESSED,
	VC4_PEWFCNT_TMU_TOTAW_TEXT_CACHE_MISS,
	VC4_PEWFCNT_VPM_TOTAW_CWK_CYCWES_VDW_STAWWED,
	VC4_PEWFCNT_VPM_TOTAW_CWK_CYCWES_VCD_STAWWED,
	VC4_PEWFCNT_W2C_TOTAW_W2_CACHE_HIT,
	VC4_PEWFCNT_W2C_TOTAW_W2_CACHE_MISS,
	VC4_PEWFCNT_NUM_EVENTS,
};

#define DWM_VC4_MAX_PEWF_COUNTEWS	16

stwuct dwm_vc4_pewfmon_cweate {
	__u32 id;
	__u32 ncountews;
	__u8 events[DWM_VC4_MAX_PEWF_COUNTEWS];
};

stwuct dwm_vc4_pewfmon_destwoy {
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
stwuct dwm_vc4_pewfmon_get_vawues {
	__u32 id;
	__u64 vawues_ptw;
};

#if defined(__cpwuspwus)
}
#endif

#endif /* _UAPI_VC4_DWM_H_ */
