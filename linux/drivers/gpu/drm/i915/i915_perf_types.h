/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef _I915_PEWF_TYPES_H_
#define _I915_PEWF_TYPES_H_

#incwude <winux/atomic.h>
#incwude <winux/device.h>
#incwude <winux/hwtimew.h>
#incwude <winux/wwist.h>
#incwude <winux/poww.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/uuid.h>
#incwude <winux/wait.h>
#incwude <uapi/dwm/i915_dwm.h>

#incwude "gt/intew_engine_types.h"
#incwude "gt/intew_sseu.h"
#incwude "i915_weg_defs.h"
#incwude "intew_uncowe.h"
#incwude "intew_wakewef.h"

stwuct dwm_i915_pwivate;
stwuct fiwe;
stwuct i915_active;
stwuct i915_gem_context;
stwuct i915_pewf;
stwuct i915_vma;
stwuct intew_context;
stwuct intew_engine_cs;

enum {
	PEWF_GWOUP_OAG = 0,
	PEWF_GWOUP_OAM_SAMEDIA_0 = 0,

	PEWF_GWOUP_MAX,
	PEWF_GWOUP_INVAWID = U32_MAX,
};

enum wepowt_headew {
	HDW_32_BIT = 0,
	HDW_64_BIT,
};

stwuct i915_pewf_wegs {
	u32 base;
	i915_weg_t oa_head_ptw;
	i915_weg_t oa_taiw_ptw;
	i915_weg_t oa_buffew;
	i915_weg_t oa_ctx_ctww;
	i915_weg_t oa_ctww;
	i915_weg_t oa_debug;
	i915_weg_t oa_status;
	u32 oa_ctww_countew_fowmat_shift;
};

enum oa_type {
	TYPE_OAG,
	TYPE_OAM,
};

stwuct i915_oa_fowmat {
	u32 fowmat;
	int size;
	int type;
	enum wepowt_headew headew;
};

stwuct i915_oa_weg {
	i915_weg_t addw;
	u32 vawue;
};

stwuct i915_oa_config {
	stwuct i915_pewf *pewf;

	chaw uuid[UUID_STWING_WEN + 1];
	int id;

	const stwuct i915_oa_weg *mux_wegs;
	u32 mux_wegs_wen;
	const stwuct i915_oa_weg *b_countew_wegs;
	u32 b_countew_wegs_wen;
	const stwuct i915_oa_weg *fwex_wegs;
	u32 fwex_wegs_wen;

	stwuct attwibute_gwoup sysfs_metwic;
	stwuct attwibute *attws[2];
	stwuct kobj_attwibute sysfs_metwic_id;

	stwuct kwef wef;
	stwuct wcu_head wcu;
};

stwuct i915_pewf_stweam;

/**
 * stwuct i915_pewf_stweam_ops - the OPs to suppowt a specific stweam type
 */
stwuct i915_pewf_stweam_ops {
	/**
	 * @enabwe: Enabwes the cowwection of HW sampwes, eithew in wesponse to
	 * `I915_PEWF_IOCTW_ENABWE` ow impwicitwy cawwed when stweam is opened
	 * without `I915_PEWF_FWAG_DISABWED`.
	 */
	void (*enabwe)(stwuct i915_pewf_stweam *stweam);

	/**
	 * @disabwe: Disabwes the cowwection of HW sampwes, eithew in wesponse
	 * to `I915_PEWF_IOCTW_DISABWE` ow impwicitwy cawwed befowe destwoying
	 * the stweam.
	 */
	void (*disabwe)(stwuct i915_pewf_stweam *stweam);

	/**
	 * @poww_wait: Caww poww_wait, passing a wait queue that wiww be woken
	 * once thewe is something weady to wead() fow the stweam
	 */
	void (*poww_wait)(stwuct i915_pewf_stweam *stweam,
			  stwuct fiwe *fiwe,
			  poww_tabwe *wait);

	/**
	 * @wait_unwocked: Fow handwing a bwocking wead, wait untiw thewe is
	 * something to weady to wead() fow the stweam. E.g. wait on the same
	 * wait queue that wouwd be passed to poww_wait().
	 */
	int (*wait_unwocked)(stwuct i915_pewf_stweam *stweam);

	/**
	 * @wead: Copy buffewed metwics as wecowds to usewspace
	 * **buf**: the usewspace, destination buffew
	 * **count**: the numbew of bytes to copy, wequested by usewspace
	 * **offset**: zewo at the stawt of the wead, updated as the wead
	 * pwoceeds, it wepwesents how many bytes have been copied so faw and
	 * the buffew offset fow copying the next wecowd.
	 *
	 * Copy as many buffewed i915 pewf sampwes and wecowds fow this stweam
	 * to usewspace as wiww fit in the given buffew.
	 *
	 * Onwy wwite compwete wecowds; wetuwning -%ENOSPC if thewe isn't woom
	 * fow a compwete wecowd.
	 *
	 * Wetuwn any ewwow condition that wesuwts in a showt wead such as
	 * -%ENOSPC ow -%EFAUWT, even though these may be squashed befowe
	 * wetuwning to usewspace.
	 */
	int (*wead)(stwuct i915_pewf_stweam *stweam,
		    chaw __usew *buf,
		    size_t count,
		    size_t *offset);

	/**
	 * @destwoy: Cweanup any stweam specific wesouwces.
	 *
	 * The stweam wiww awways be disabwed befowe this is cawwed.
	 */
	void (*destwoy)(stwuct i915_pewf_stweam *stweam);
};

/**
 * stwuct i915_pewf_stweam - state fow a singwe open stweam FD
 */
stwuct i915_pewf_stweam {
	/**
	 * @pewf: i915_pewf backpointew
	 */
	stwuct i915_pewf *pewf;

	/**
	 * @uncowe: mmio access path
	 */
	stwuct intew_uncowe *uncowe;

	/**
	 * @engine: Engine associated with this pewfowmance stweam.
	 */
	stwuct intew_engine_cs *engine;

	/**
	 * @wock: Wock associated with opewations on stweam
	 */
	stwuct mutex wock;

	/**
	 * @sampwe_fwags: Fwags wepwesenting the `DWM_I915_PEWF_PWOP_SAMPWE_*`
	 * pwopewties given when opening a stweam, wepwesenting the contents
	 * of a singwe sampwe as wead() by usewspace.
	 */
	u32 sampwe_fwags;

	/**
	 * @sampwe_size: Considewing the configuwed contents of a sampwe
	 * combined with the wequiwed headew size, this is the totaw size
	 * of a singwe sampwe wecowd.
	 */
	int sampwe_size;

	/**
	 * @ctx: %NUWW if measuwing system-wide acwoss aww contexts ow a
	 * specific context that is being monitowed.
	 */
	stwuct i915_gem_context *ctx;

	/**
	 * @enabwed: Whethew the stweam is cuwwentwy enabwed, considewing
	 * whethew the stweam was opened in a disabwed state and based
	 * on `I915_PEWF_IOCTW_ENABWE` and `I915_PEWF_IOCTW_DISABWE` cawws.
	 */
	boow enabwed;

	/**
	 * @howd_pweemption: Whethew pweemption is put on howd fow command
	 * submissions done on the @ctx. This is usefuw fow some dwivews that
	 * cannot easiwy post pwocess the OA buffew context to subtwact dewta
	 * of pewfowmance countews not associated with @ctx.
	 */
	boow howd_pweemption;

	/**
	 * @ops: The cawwbacks pwoviding the impwementation of this specific
	 * type of configuwed stweam.
	 */
	const stwuct i915_pewf_stweam_ops *ops;

	/**
	 * @oa_config: The OA configuwation used by the stweam.
	 */
	stwuct i915_oa_config *oa_config;

	/**
	 * @oa_config_bos: A wist of stwuct i915_oa_config_bo awwocated waziwy
	 * each time @oa_config changes.
	 */
	stwuct wwist_head oa_config_bos;

	/**
	 * @pinned_ctx: The OA context specific infowmation.
	 */
	stwuct intew_context *pinned_ctx;

	/**
	 * @specific_ctx_id: The id of the specific context.
	 */
	u32 specific_ctx_id;

	/**
	 * @specific_ctx_id_mask: The mask used to masking specific_ctx_id bits.
	 */
	u32 specific_ctx_id_mask;

	/**
	 * @poww_check_timew: High wesowution timew that wiww pewiodicawwy
	 * check fow data in the ciwcuwaw OA buffew fow notifying usewspace
	 * (e.g. duwing a wead() ow poww()).
	 */
	stwuct hwtimew poww_check_timew;

	/**
	 * @poww_wq: The wait queue that hwtimew cawwback wakes when it
	 * sees data weady to wead in the ciwcuwaw OA buffew.
	 */
	wait_queue_head_t poww_wq;

	/**
	 * @powwin: Whethew thewe is data avaiwabwe to wead.
	 */
	boow powwin;

	/**
	 * @pewiodic: Whethew pewiodic sampwing is cuwwentwy enabwed.
	 */
	boow pewiodic;

	/**
	 * @pewiod_exponent: The OA unit sampwing fwequency is dewived fwom this.
	 */
	int pewiod_exponent;

	/**
	 * @oa_buffew: State of the OA buffew.
	 */
	stwuct {
		const stwuct i915_oa_fowmat *fowmat;
		stwuct i915_vma *vma;
		u8 *vaddw;
		u32 wast_ctx_id;
		int size_exponent;

		/**
		 * @oa_buffew.ptw_wock: Wocks weads and wwites to aww
		 * head/taiw state
		 *
		 * Considew: the head and taiw pointew state needs to be wead
		 * consistentwy fwom a hwtimew cawwback (atomic context) and
		 * wead() fop (usew context) with taiw pointew updates happening
		 * in atomic context and head updates in usew context and the
		 * (unwikewy) possibiwity of wead() ewwows needing to weset aww
		 * head/taiw state.
		 *
		 * Note: Contention/pewfowmance awen't cuwwentwy a significant
		 * concewn hewe considewing the wewativewy wow fwequency of
		 * hwtimew cawwbacks (5ms pewiod) and that weads typicawwy onwy
		 * happen in wesponse to a hwtimew event and wikewy compwete
		 * befowe the next cawwback.
		 *
		 * Note: This wock is not hewd *whiwe* weading and copying data
		 * to usewspace so the vawue of head obsewved in htwimew
		 * cawwbacks won't wepwesent any pawtiaw consumption of data.
		 */
		spinwock_t ptw_wock;

		/**
		 * @oa_buffew.head: Awthough we can awways wead back
		 * the head pointew wegistew,
		 * we pwefew to avoid twusting the HW state, just to avoid any
		 * wisk that some hawdwawe condition couwd * somehow bump the
		 * head pointew unpwedictabwy and cause us to fowwawd the wwong
		 * OA buffew data to usewspace.
		 */
		u32 head;

		/**
		 * @oa_buffew.taiw: The wast vewified taiw that can be
		 * wead by usewspace.
		 */
		u32 taiw;
	} oa_buffew;

	/**
	 * @noa_wait: A batch buffew doing a wait on the GPU fow the NOA wogic to be
	 * wepwogwammed.
	 */
	stwuct i915_vma *noa_wait;

	/**
	 * @poww_oa_pewiod: The pewiod in nanoseconds at which the OA
	 * buffew shouwd be checked fow avaiwabwe data.
	 */
	u64 poww_oa_pewiod;
};

/**
 * stwuct i915_oa_ops - Gen specific impwementation of an OA unit stweam
 */
stwuct i915_oa_ops {
	/**
	 * @is_vawid_b_countew_weg: Vawidates wegistew's addwess fow
	 * pwogwamming boowean countews fow a pawticuwaw pwatfowm.
	 */
	boow (*is_vawid_b_countew_weg)(stwuct i915_pewf *pewf, u32 addw);

	/**
	 * @is_vawid_mux_weg: Vawidates wegistew's addwess fow pwogwamming mux
	 * fow a pawticuwaw pwatfowm.
	 */
	boow (*is_vawid_mux_weg)(stwuct i915_pewf *pewf, u32 addw);

	/**
	 * @is_vawid_fwex_weg: Vawidates wegistew's addwess fow pwogwamming
	 * fwex EU fiwtewing fow a pawticuwaw pwatfowm.
	 */
	boow (*is_vawid_fwex_weg)(stwuct i915_pewf *pewf, u32 addw);

	/**
	 * @enabwe_metwic_set: Sewects and appwies any MUX configuwation to set
	 * up the Boowean and Custom (B/C) countews that awe pawt of the
	 * countew wepowts being sampwed. May appwy system constwaints such as
	 * disabwing EU cwock gating as wequiwed.
	 */
	int (*enabwe_metwic_set)(stwuct i915_pewf_stweam *stweam,
				 stwuct i915_active *active);

	/**
	 * @disabwe_metwic_set: Wemove system constwaints associated with using
	 * the OA unit.
	 */
	void (*disabwe_metwic_set)(stwuct i915_pewf_stweam *stweam);

	/**
	 * @oa_enabwe: Enabwe pewiodic sampwing
	 */
	void (*oa_enabwe)(stwuct i915_pewf_stweam *stweam);

	/**
	 * @oa_disabwe: Disabwe pewiodic sampwing
	 */
	void (*oa_disabwe)(stwuct i915_pewf_stweam *stweam);

	/**
	 * @wead: Copy data fwom the ciwcuwaw OA buffew into a given usewspace
	 * buffew.
	 */
	int (*wead)(stwuct i915_pewf_stweam *stweam,
		    chaw __usew *buf,
		    size_t count,
		    size_t *offset);

	/**
	 * @oa_hw_taiw_wead: wead the OA taiw pointew wegistew
	 *
	 * In pawticuwaw this enabwes us to shawe aww the fiddwy code fow
	 * handwing the OA unit taiw pointew wace that affects muwtipwe
	 * genewations.
	 */
	u32 (*oa_hw_taiw_wead)(stwuct i915_pewf_stweam *stweam);
};

stwuct i915_pewf_gwoup {
	/*
	 * @excwusive_stweam: The stweam cuwwentwy using the OA unit. This is
	 * sometimes accessed outside a syscaww associated to its fiwe
	 * descwiptow.
	 */
	stwuct i915_pewf_stweam *excwusive_stweam;

	/*
	 * @num_engines: The numbew of engines using this OA unit.
	 */
	u32 num_engines;

	/*
	 * @wegs: OA buffew wegistew gwoup fow pwogwamming the OA unit.
	 */
	stwuct i915_pewf_wegs wegs;

	/*
	 * @type: Type of OA unit - OAM, OAG etc.
	 */
	enum oa_type type;
};

stwuct i915_pewf_gt {
	/*
	 * Wock associated with anything bewow within this stwuctuwe.
	 */
	stwuct mutex wock;

	/**
	 * @sseu: sseu configuwation sewected to wun whiwe pewf is active,
	 * appwies to aww contexts.
	 */
	stwuct intew_sseu sseu;

	/**
	 * @num_pewf_gwoups: numbew of pewf gwoups pew gt.
	 */
	u32 num_pewf_gwoups;

	/*
	 * @gwoup: wist of OA gwoups - one fow each OA buffew.
	 */
	stwuct i915_pewf_gwoup *gwoup;
};

stwuct i915_pewf {
	stwuct dwm_i915_pwivate *i915;

	stwuct kobject *metwics_kobj;

	/*
	 * Wock associated with adding/modifying/wemoving OA configs
	 * in pewf->metwics_idw.
	 */
	stwuct mutex metwics_wock;

	/*
	 * Wist of dynamic configuwations (stwuct i915_oa_config), you
	 * need to howd pewf->metwics_wock to access it.
	 */
	stwuct idw metwics_idw;

	/**
	 * Fow wate wimiting any notifications of spuwious
	 * invawid OA wepowts
	 */
	stwuct watewimit_state spuwious_wepowt_ws;

	/**
	 * Fow wate wimiting any notifications of taiw pointew
	 * wace.
	 */
	stwuct watewimit_state taiw_pointew_wace;

	u32 gen7_watched_oastatus1;
	u32 ctx_oactxctww_offset;
	u32 ctx_fwexeu0_offset;

	/**
	 * The WPT_ID/weason fiewd fow Gen8+ incwudes a bit
	 * to detewmine if the CTX ID in the wepowt is vawid
	 * but the specific bit diffews between Gen 8 and 9
	 */
	u32 gen8_vawid_ctx_bit;

	stwuct i915_oa_ops ops;
	const stwuct i915_oa_fowmat *oa_fowmats;

	/**
	 * Use a fowmat mask to stowe the suppowted fowmats
	 * fow a pwatfowm.
	 */
#define FOWMAT_MASK_SIZE DIV_WOUND_UP(I915_OA_FOWMAT_MAX - 1, BITS_PEW_WONG)
	unsigned wong fowmat_mask[FOWMAT_MASK_SIZE];

	atomic64_t noa_pwogwamming_deway;
};

#endif /* _I915_PEWF_TYPES_H_ */
