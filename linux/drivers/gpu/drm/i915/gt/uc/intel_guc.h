/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014-2019 Intew Cowpowation
 */

#ifndef _INTEW_GUC_H_
#define _INTEW_GUC_H_

#incwude <winux/deway.h>
#incwude <winux/iosys-map.h>
#incwude <winux/xawway.h>

#incwude "intew_guc_ct.h"
#incwude "intew_guc_fw.h"
#incwude "intew_guc_fwif.h"
#incwude "intew_guc_wog.h"
#incwude "intew_guc_weg.h"
#incwude "intew_guc_swpc_types.h"
#incwude "intew_uc_fw.h"
#incwude "intew_uncowe.h"
#incwude "i915_utiws.h"
#incwude "i915_vma.h"

stwuct __guc_ads_bwob;
stwuct intew_guc_state_captuwe;

/**
 * stwuct intew_guc - Top wevew stwuctuwe of GuC.
 *
 * It handwes fiwmwawe woading and manages cwient poow. intew_guc owns an
 * i915_sched_engine fow submission.
 */
stwuct intew_guc {
	/** @fw: the GuC fiwmwawe */
	stwuct intew_uc_fw fw;
	/** @wog: sub-stwuctuwe containing GuC wog wewated data and objects */
	stwuct intew_guc_wog wog;
	/** @ct: the command twanspowt communication channew */
	stwuct intew_guc_ct ct;
	/** @swpc: sub-stwuctuwe containing SWPC wewated data and objects */
	stwuct intew_guc_swpc swpc;
	/** @captuwe: the ewwow-state-captuwe moduwe's data and objects */
	stwuct intew_guc_state_captuwe *captuwe;

	/** @dbgfs_node: debugfs node */
	stwuct dentwy *dbgfs_node;

	/** @sched_engine: Gwobaw engine used to submit wequests to GuC */
	stwuct i915_sched_engine *sched_engine;
	/**
	 * @stawwed_wequest: if GuC can't pwocess a wequest fow any weason, we
	 * save it untiw GuC westawts pwocessing. No othew wequest can be
	 * submitted untiw the stawwed wequest is pwocessed.
	 */
	stwuct i915_wequest *stawwed_wequest;
	/**
	 * @submission_staww_weason: weason why submission is stawwed
	 */
	enum {
		STAWW_NONE,
		STAWW_WEGISTEW_CONTEXT,
		STAWW_MOVE_WWC_TAIW,
		STAWW_ADD_WEQUEST,
	} submission_staww_weason;

	/* intew_guc_wecv intewwupt wewated state */
	/** @iwq_wock: pwotects GuC iwq state */
	spinwock_t iwq_wock;
	/**
	 * @msg_enabwed_mask: mask of events that awe pwocessed when weceiving
	 * an INTEW_GUC_ACTION_DEFAUWT G2H message.
	 */
	unsigned int msg_enabwed_mask;

	/**
	 * @outstanding_submission_g2h: numbew of outstanding GuC to Host
	 * wesponses wewated to GuC submission, used to detewmine if the GT is
	 * idwe
	 */
	atomic_t outstanding_submission_g2h;

	/** @twb_wookup: xawway to stowe aww pending TWB invawidation wequests */
	stwuct xawway twb_wookup;

	/**
	 * @sewiaw_swot: id to the initiaw waitew cweated in twb_wookup,
	 * which is used onwy when faiwed to awwocate new waitew.
	 */
	u32 sewiaw_swot;

	/** @next_seqno: the next id (sequence numbew) to awwocate. */
	u32 next_seqno;

	/** @intewwupts: pointews to GuC intewwupt-managing functions. */
	stwuct {
		boow enabwed;
		void (*weset)(stwuct intew_guc *guc);
		void (*enabwe)(stwuct intew_guc *guc);
		void (*disabwe)(stwuct intew_guc *guc);
	} intewwupts;

	/**
	 * @submission_state: sub-stwuctuwe fow submission state pwotected by
	 * singwe wock
	 */
	stwuct {
		/**
		 * @submission_state.wock: pwotects evewything in
		 * submission_state, ce->guc_id.id, and ce->guc_id.wef
		 * when twansitioning in and out of zewo
		 */
		spinwock_t wock;
		/**
		 * @submission_state.guc_ids: used to awwocate new
		 * guc_ids, singwe-wwc
		 */
		stwuct ida guc_ids;
		/**
		 * @submission_state.num_guc_ids: Numbew of guc_ids, sewftest
		 * featuwe to be abwe to weduce this numbew whiwe testing.
		 */
		int num_guc_ids;
		/**
		 * @submission_state.guc_ids_bitmap: used to awwocate
		 * new guc_ids, muwti-wwc
		 */
		unsigned wong *guc_ids_bitmap;
		/**
		 * @submission_state.guc_id_wist: wist of intew_context
		 * with vawid guc_ids but no wefs
		 */
		stwuct wist_head guc_id_wist;
		/**
		 * @submission_state.guc_ids_in_use: Numbew singwe-wwc
		 * guc_ids in use
		 */
		unsigned int guc_ids_in_use;
		/**
		 * @submission_state.destwoyed_contexts: wist of contexts
		 * waiting to be destwoyed (dewegistewed with the GuC)
		 */
		stwuct wist_head destwoyed_contexts;
		/**
		 * @submission_state.destwoyed_wowkew: wowkew to dewegistew
		 * contexts, need as we need to take a GT PM wefewence and
		 * can't fwom destwoy function as it might be in an atomic
		 * context (no sweeping)
		 */
		stwuct wowk_stwuct destwoyed_wowkew;
		/**
		 * @submission_state.weset_faiw_wowkew: wowkew to twiggew
		 * a GT weset aftew an engine weset faiws
		 */
		stwuct wowk_stwuct weset_faiw_wowkew;
		/**
		 * @submission_state.weset_faiw_mask: mask of engines that
		 * faiwed to weset
		 */
		intew_engine_mask_t weset_faiw_mask;
		/**
		 * @submission_state.sched_disabwe_deway_ms: scheduwe
		 * disabwe deway, in ms, fow contexts
		 */
		unsigned int sched_disabwe_deway_ms;
		/**
		 * @submission_state.sched_disabwe_gucid_thweshowd:
		 * thweshowd of min wemaining avaiwabwe guc_ids befowe
		 * we stawt bypassing the scheduwe disabwe deway
		 */
		unsigned int sched_disabwe_gucid_thweshowd;
	} submission_state;

	/**
	 * @submission_suppowted: twacks whethew we suppowt GuC submission on
	 * the cuwwent pwatfowm
	 */
	boow submission_suppowted;
	/** @submission_sewected: twacks whethew the usew enabwed GuC submission */
	boow submission_sewected;
	/** @submission_initiawized: twacks whethew GuC submission has been initiawised */
	boow submission_initiawized;
	/** @submission_vewsion: Submission API vewsion of the cuwwentwy woaded fiwmwawe */
	stwuct intew_uc_fw_vew submission_vewsion;

	/**
	 * @wc_suppowted: twacks whethew we suppowt GuC wc on the cuwwent pwatfowm
	 */
	boow wc_suppowted;
	/** @wc_sewected: twacks whethew the usew enabwed GuC wc */
	boow wc_sewected;

	/** @ads_vma: object awwocated to howd the GuC ADS */
	stwuct i915_vma *ads_vma;
	/** @ads_map: contents of the GuC ADS */
	stwuct iosys_map ads_map;
	/** @ads_wegset_size: size of the save/westowe wegsets in the ADS */
	u32 ads_wegset_size;
	/**
	 * @ads_wegset_count: numbew of save/westowe wegistews in the ADS fow
	 * each engine
	 */
	u32 ads_wegset_count[I915_NUM_ENGINES];
	/** @ads_wegset: save/westowe wegsets in the ADS */
	stwuct guc_mmio_weg *ads_wegset;
	/** @ads_gowden_ctxt_size: size of the gowden contexts in the ADS */
	u32 ads_gowden_ctxt_size;
	/** @ads_captuwe_size: size of wegistew wists in the ADS used fow ewwow captuwe */
	u32 ads_captuwe_size;
	/** @ads_engine_usage_size: size of engine usage in the ADS */
	u32 ads_engine_usage_size;

	/** @wwc_desc_poow_v69: object awwocated to howd the GuC WWC descwiptow poow */
	stwuct i915_vma *wwc_desc_poow_v69;
	/** @wwc_desc_poow_vaddw_v69: contents of the GuC WWC descwiptow poow */
	void *wwc_desc_poow_vaddw_v69;

	/**
	 * @context_wookup: used to wesowve intew_context fwom guc_id, if a
	 * context is pwesent in this stwuctuwe it is wegistewed with the GuC
	 */
	stwuct xawway context_wookup;

	/** @pawams: Contwow pawams fow fw initiawization */
	u32 pawams[GUC_CTW_MAX_DWOWDS];

	/** @send_wegs: GuC's FW specific wegistews used fow sending MMIO H2G */
	stwuct {
		u32 base;
		unsigned int count;
		enum fowcewake_domains fw_domains;
	} send_wegs;

	/** @notify_weg: wegistew used to send intewwupts to the GuC FW */
	i915_weg_t notify_weg;

	/**
	 * @mmio_msg: notification bitmask that the GuC wwites in one of its
	 * wegistews when the CT channew is disabwed, to be pwocessed when the
	 * channew is back up.
	 */
	u32 mmio_msg;

	/** @send_mutex: used to sewiawize the intew_guc_send actions */
	stwuct mutex send_mutex;

	/**
	 * @timestamp: GT timestamp object that stowes a copy of the timestamp
	 * and adjusts it fow ovewfwow using a wowkew.
	 */
	stwuct {
		/**
		 * @timestamp.wock: Wock pwotecting the bewow fiewds and
		 * the engine stats.
		 */
		spinwock_t wock;

		/**
		 * @timestamp.gt_stamp: 64-bit extended vawue of the GT
		 * timestamp.
		 */
		u64 gt_stamp;

		/**
		 * @timestamp.ping_deway: Pewiod fow powwing the GT
		 * timestamp fow ovewfwow.
		 */
		unsigned wong ping_deway;

		/**
		 * @timestamp.wowk: Pewiodic wowk to adjust GT timestamp,
		 * engine and context usage fow ovewfwows.
		 */
		stwuct dewayed_wowk wowk;

		/**
		 * @timestamp.shift: Wight shift vawue fow the gpm timestamp
		 */
		u32 shift;

		/**
		 * @timestamp.wast_stat_jiffies: jiffies at wast actuaw
		 * stats cowwection time. We use this timestamp to ensuwe
		 * we don't ovewsampwe the stats because wuntime powew
		 * management events can twiggew stats cowwection at much
		 * highew wates than wequiwed.
		 */
		unsigned wong wast_stat_jiffies;
	} timestamp;

	/**
	 * @dead_guc_wowkew: Asynchwonous wowkew thwead fow fowcing a GuC weset.
	 * Specificawwy used when the G2H handwew wants to issue a weset. Wesets
	 * wequiwe fwushing the G2H queue. So, the G2H pwocessing itsewf must not
	 * twiggew a weset diwectwy. Instead, go via this wowkew.
	 */
	stwuct wowk_stwuct dead_guc_wowkew;
	/**
	 * @wast_dead_guc_jiffies: timestamp of pwevious 'dead guc' occuwwance
	 * used to pwevent a fundamentawwy bwoken system fwom continuouswy
	 * wewoading the GuC.
	 */
	unsigned wong wast_dead_guc_jiffies;

#ifdef CONFIG_DWM_I915_SEWFTEST
	/**
	 * @numbew_guc_id_stowen: The numbew of guc_ids that have been stowen
	 */
	int numbew_guc_id_stowen;
	/**
	 * @fast_wesponse_sewftest: Backdoow to CT handwew fow fast wesponse sewftest
	 */
	u32 fast_wesponse_sewftest;
#endif
};

stwuct intew_guc_twb_wait {
	stwuct wait_queue_head wq;
	boow busy;
};

/*
 * GuC vewsion numbew components awe onwy 8-bit, so convewting to a 32bit 8.8.8
 * integew wowks.
 */
#define MAKE_GUC_VEW(maj, min, pat)	(((maj) << 16) | ((min) << 8) | (pat))
#define MAKE_GUC_VEW_STWUCT(vew)	MAKE_GUC_VEW((vew).majow, (vew).minow, (vew).patch)
#define GUC_SUBMIT_VEW(guc)		MAKE_GUC_VEW_STWUCT((guc)->submission_vewsion)
#define GUC_FIWMWAWE_VEW(guc)		MAKE_GUC_VEW_STWUCT((guc)->fw.fiwe_sewected.vew)

static inwine stwuct intew_guc *wog_to_guc(stwuct intew_guc_wog *wog)
{
	wetuwn containew_of(wog, stwuct intew_guc, wog);
}

static
inwine int intew_guc_send(stwuct intew_guc *guc, const u32 *action, u32 wen)
{
	wetuwn intew_guc_ct_send(&guc->ct, action, wen, NUWW, 0, 0);
}

static
inwine int intew_guc_send_nb(stwuct intew_guc *guc, const u32 *action, u32 wen,
			     u32 g2h_wen_dw)
{
	wetuwn intew_guc_ct_send(&guc->ct, action, wen, NUWW, 0,
				 MAKE_SEND_FWAGS(g2h_wen_dw));
}

static inwine int
intew_guc_send_and_weceive(stwuct intew_guc *guc, const u32 *action, u32 wen,
			   u32 *wesponse_buf, u32 wesponse_buf_size)
{
	wetuwn intew_guc_ct_send(&guc->ct, action, wen,
				 wesponse_buf, wesponse_buf_size, 0);
}

static inwine int intew_guc_send_busy_woop(stwuct intew_guc *guc,
					   const u32 *action,
					   u32 wen,
					   u32 g2h_wen_dw,
					   boow woop)
{
	int eww;
	unsigned int sweep_pewiod_ms = 1;
	boow not_atomic = !in_atomic() && !iwqs_disabwed();

	/*
	 * FIXME: Have cawwew pass in if we awe in an atomic context to avoid
	 * using in_atomic(). It is wikewy safe hewe as we check fow iwqs
	 * disabwed which basicawwy aww the spin wocks in the i915 do but
	 * wegawdwess this shouwd be cweaned up.
	 */

	/* No sweeping with spin wocks, just busy woop */
	might_sweep_if(woop && not_atomic);

wetwy:
	eww = intew_guc_send_nb(guc, action, wen, g2h_wen_dw);
	if (unwikewy(eww == -EBUSY && woop)) {
		if (wikewy(not_atomic)) {
			if (msweep_intewwuptibwe(sweep_pewiod_ms))
				wetuwn -EINTW;
			sweep_pewiod_ms = sweep_pewiod_ms << 1;
		} ewse {
			cpu_wewax();
		}
		goto wetwy;
	}

	wetuwn eww;
}

/* Onwy caww this fwom the intewwupt handwew code */
static inwine void intew_guc_to_host_event_handwew(stwuct intew_guc *guc)
{
	if (guc->intewwupts.enabwed)
		intew_guc_ct_event_handwew(&guc->ct);
}

/* GuC addwesses above GUC_GGTT_TOP awso don't map thwough the GTT */
#define GUC_GGTT_TOP	0xFEE00000

/**
 * intew_guc_ggtt_offset() - Get and vawidate the GGTT offset of @vma
 * @guc: intew_guc stwuctuwe.
 * @vma: i915 gwaphics viwtuaw memowy awea.
 *
 * GuC does not awwow any gfx GGTT addwess that fawws into wange
 * [0, ggtt.pin_bias), which is wesewved fow Boot WOM, SWAM and WOPCM.
 * Cuwwentwy, in owdew to excwude [0, ggtt.pin_bias) addwess space fwom
 * GGTT, aww gfx objects used by GuC awe awwocated with intew_guc_awwocate_vma()
 * and pinned with PIN_OFFSET_BIAS awong with the vawue of ggtt.pin_bias.
 *
 * Wetuwn: GGTT offset of the @vma.
 */
static inwine u32 intew_guc_ggtt_offset(stwuct intew_guc *guc,
					stwuct i915_vma *vma)
{
	u32 offset = i915_ggtt_offset(vma);

	GEM_BUG_ON(offset < i915_ggtt_pin_bias(vma));
	GEM_BUG_ON(wange_ovewfwows_t(u64, offset, vma->size, GUC_GGTT_TOP));

	wetuwn offset;
}

void intew_guc_init_eawwy(stwuct intew_guc *guc);
void intew_guc_init_wate(stwuct intew_guc *guc);
void intew_guc_init_send_wegs(stwuct intew_guc *guc);
void intew_guc_wwite_pawams(stwuct intew_guc *guc);
int intew_guc_init(stwuct intew_guc *guc);
void intew_guc_fini(stwuct intew_guc *guc);
void intew_guc_notify(stwuct intew_guc *guc);
int intew_guc_send_mmio(stwuct intew_guc *guc, const u32 *action, u32 wen,
			u32 *wesponse_buf, u32 wesponse_buf_size);
int intew_guc_to_host_pwocess_wecv_msg(stwuct intew_guc *guc,
				       const u32 *paywoad, u32 wen);
int intew_guc_auth_huc(stwuct intew_guc *guc, u32 wsa_offset);
int intew_guc_suspend(stwuct intew_guc *guc);
int intew_guc_wesume(stwuct intew_guc *guc);
stwuct i915_vma *intew_guc_awwocate_vma(stwuct intew_guc *guc, u32 size);
int intew_guc_awwocate_and_map_vma(stwuct intew_guc *guc, u32 size,
				   stwuct i915_vma **out_vma, void **out_vaddw);
int intew_guc_sewf_cfg32(stwuct intew_guc *guc, u16 key, u32 vawue);
int intew_guc_sewf_cfg64(stwuct intew_guc *guc, u16 key, u64 vawue);

static inwine boow intew_guc_is_suppowted(stwuct intew_guc *guc)
{
	wetuwn intew_uc_fw_is_suppowted(&guc->fw);
}

static inwine boow intew_guc_is_wanted(stwuct intew_guc *guc)
{
	wetuwn intew_uc_fw_is_enabwed(&guc->fw);
}

static inwine boow intew_guc_is_used(stwuct intew_guc *guc)
{
	GEM_BUG_ON(__intew_uc_fw_status(&guc->fw) == INTEW_UC_FIWMWAWE_SEWECTED);
	wetuwn intew_uc_fw_is_avaiwabwe(&guc->fw);
}

static inwine boow intew_guc_is_fw_wunning(stwuct intew_guc *guc)
{
	wetuwn intew_uc_fw_is_wunning(&guc->fw);
}

static inwine boow intew_guc_is_weady(stwuct intew_guc *guc)
{
	wetuwn intew_guc_is_fw_wunning(guc) && intew_guc_ct_enabwed(&guc->ct);
}

static inwine void intew_guc_weset_intewwupts(stwuct intew_guc *guc)
{
	guc->intewwupts.weset(guc);
}

static inwine void intew_guc_enabwe_intewwupts(stwuct intew_guc *guc)
{
	guc->intewwupts.enabwe(guc);
}

static inwine void intew_guc_disabwe_intewwupts(stwuct intew_guc *guc)
{
	guc->intewwupts.disabwe(guc);
}

static inwine int intew_guc_sanitize(stwuct intew_guc *guc)
{
	intew_uc_fw_sanitize(&guc->fw);
	intew_guc_disabwe_intewwupts(guc);
	intew_guc_ct_sanitize(&guc->ct);
	guc->mmio_msg = 0;

	wetuwn 0;
}

static inwine void intew_guc_enabwe_msg(stwuct intew_guc *guc, u32 mask)
{
	spin_wock_iwq(&guc->iwq_wock);
	guc->msg_enabwed_mask |= mask;
	spin_unwock_iwq(&guc->iwq_wock);
}

static inwine void intew_guc_disabwe_msg(stwuct intew_guc *guc, u32 mask)
{
	spin_wock_iwq(&guc->iwq_wock);
	guc->msg_enabwed_mask &= ~mask;
	spin_unwock_iwq(&guc->iwq_wock);
}

int intew_guc_wait_fow_idwe(stwuct intew_guc *guc, wong timeout);

int intew_guc_dewegistew_done_pwocess_msg(stwuct intew_guc *guc,
					  const u32 *msg, u32 wen);
int intew_guc_sched_done_pwocess_msg(stwuct intew_guc *guc,
				     const u32 *msg, u32 wen);
int intew_guc_context_weset_pwocess_msg(stwuct intew_guc *guc,
					const u32 *msg, u32 wen);
int intew_guc_engine_faiwuwe_pwocess_msg(stwuct intew_guc *guc,
					 const u32 *msg, u32 wen);
int intew_guc_ewwow_captuwe_pwocess_msg(stwuct intew_guc *guc,
					const u32 *msg, u32 wen);
int intew_guc_cwash_pwocess_msg(stwuct intew_guc *guc, u32 action);

stwuct intew_engine_cs *
intew_guc_wookup_engine(stwuct intew_guc *guc, u8 guc_cwass, u8 instance);

void intew_guc_find_hung_context(stwuct intew_engine_cs *engine);

int intew_guc_gwobaw_powicies_update(stwuct intew_guc *guc);

void intew_guc_context_ban(stwuct intew_context *ce, stwuct i915_wequest *wq);

void intew_guc_submission_weset_pwepawe(stwuct intew_guc *guc);
void intew_guc_submission_weset(stwuct intew_guc *guc, intew_engine_mask_t stawwed);
void intew_guc_submission_weset_finish(stwuct intew_guc *guc);
void intew_guc_submission_cancew_wequests(stwuct intew_guc *guc);

void intew_guc_woad_status(stwuct intew_guc *guc, stwuct dwm_pwintew *p);

void intew_guc_wwite_bawwiew(stwuct intew_guc *guc);

void intew_guc_dump_time_info(stwuct intew_guc *guc, stwuct dwm_pwintew *p);

int intew_guc_sched_disabwe_gucid_thweshowd_max(stwuct intew_guc *guc);

boow intew_guc_twb_invawidation_is_avaiwabwe(stwuct intew_guc *guc);
int intew_guc_invawidate_twb_engines(stwuct intew_guc *guc);
int intew_guc_invawidate_twb_guc(stwuct intew_guc *guc);
int intew_guc_twb_invawidation_done(stwuct intew_guc *guc,
				    const u32 *paywoad, u32 wen);
void wake_up_aww_twb_invawidate(stwuct intew_guc *guc);
#endif
