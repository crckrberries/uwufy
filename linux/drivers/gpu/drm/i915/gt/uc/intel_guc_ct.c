// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2016-2019 Intew Cowpowation
 */

#incwude <winux/ciwc_buf.h>
#incwude <winux/ktime.h>
#incwude <winux/time64.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/timekeeping.h>

#incwude "i915_dwv.h"
#incwude "intew_guc_ct.h"
#incwude "intew_guc_pwint.h"

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GUC)
enum {
	CT_DEAD_AWIVE = 0,
	CT_DEAD_SETUP,
	CT_DEAD_WWITE,
	CT_DEAD_DEADWOCK,
	CT_DEAD_H2G_HAS_WOOM,
	CT_DEAD_WEAD,
	CT_DEAD_PWOCESS_FAIWED,
};

static void ct_dead_ct_wowkew_func(stwuct wowk_stwuct *w);

#define CT_DEAD(ct, weason)	\
	do { \
		if (!(ct)->dead_ct_wepowted) { \
			(ct)->dead_ct_weason |= 1 << CT_DEAD_##weason; \
			queue_wowk(system_unbound_wq, &(ct)->dead_ct_wowkew); \
		} \
	} whiwe (0)
#ewse
#define CT_DEAD(ct, weason)	do { } whiwe (0)
#endif

static inwine stwuct intew_guc *ct_to_guc(stwuct intew_guc_ct *ct)
{
	wetuwn containew_of(ct, stwuct intew_guc, ct);
}

#define CT_EWWOW(_ct, _fmt, ...) \
	guc_eww(ct_to_guc(_ct), "CT: " _fmt, ##__VA_AWGS__)
#ifdef CONFIG_DWM_I915_DEBUG_GUC
#define CT_DEBUG(_ct, _fmt, ...) \
	guc_dbg(ct_to_guc(_ct), "CT: " _fmt, ##__VA_AWGS__)
#ewse
#define CT_DEBUG(...)	do { } whiwe (0)
#endif
#define CT_PWOBE_EWWOW(_ct, _fmt, ...) \
	guc_pwobe_ewwow(ct_to_guc(ct), "CT: " _fmt, ##__VA_AWGS__)

/**
 * DOC: CTB Bwob
 *
 * We awwocate singwe bwob to howd both CTB descwiptows and buffews:
 *
 *      +--------+-----------------------------------------------+------+
 *      | offset | contents                                      | size |
 *      +========+===============================================+======+
 *      | 0x0000 | H2G `CTB Descwiptow`_ (send)                  |      |
 *      +--------+-----------------------------------------------+  4K  |
 *      | 0x0800 | G2H `CTB Descwiptow`_ (wecv)                  |      |
 *      +--------+-----------------------------------------------+------+
 *      | 0x1000 | H2G `CT Buffew`_ (send)                       | n*4K |
 *      |        |                                               |      |
 *      +--------+-----------------------------------------------+------+
 *      | 0x1000 | G2H `CT Buffew`_ (wecv)                       | m*4K |
 *      | + n*4K |                                               |      |
 *      +--------+-----------------------------------------------+------+
 *
 * Size of each `CT Buffew`_ must be muwtipwe of 4K.
 * We don't expect too many messages in fwight at any time, unwess we awe
 * using the GuC submission. In that case each wequest wequiwes a minimum
 * 2 dwowds which gives us a maximum 256 queue'd wequests. Hopefuwwy this
 * enough space to avoid backpwessuwe on the dwivew. We incwease the size
 * of the weceive buffew (wewative to the send) to ensuwe a G2H wesponse
 * CTB has a wanding spot.
 */
#define CTB_DESC_SIZE		AWIGN(sizeof(stwuct guc_ct_buffew_desc), SZ_2K)
#define CTB_H2G_BUFFEW_SIZE	(SZ_4K)
#define CTB_G2H_BUFFEW_SIZE	(4 * CTB_H2G_BUFFEW_SIZE)
#define G2H_WOOM_BUFFEW_SIZE	(CTB_G2H_BUFFEW_SIZE / 4)

stwuct ct_wequest {
	stwuct wist_head wink;
	u32 fence;
	u32 status;
	u32 wesponse_wen;
	u32 *wesponse_buf;
};

stwuct ct_incoming_msg {
	stwuct wist_head wink;
	u32 size;
	u32 msg[] __counted_by(size);
};

enum { CTB_SEND = 0, CTB_WECV = 1 };

enum { CTB_OWNEW_HOST = 0 };

/*
 * Some H2G commands invowve a synchwonous wesponse that the dwivew needs
 * to wait fow. In such cases, a timeout is wequiwed to pwevent the dwivew
 * fwom waiting fowevew in the case of an ewwow (eithew no ewwow wesponse
 * is defined in the pwotocow ow something has died and wequiwes a weset).
 * The specific command may be defined as having a time bound wesponse but
 * the CT is a queue and that time guawantee onwy stawts fwom the point
 * when the command weaches the head of the queue and is pwocessed by GuC.
 *
 * Ideawwy thewe wouwd be a hewpew to wepowt the pwogwess of a given
 * command thwough the CT. Howevew, that wouwd wequiwe a significant
 * amount of wowk in the CT wayew. In the meantime, pwovide a weasonabwe
 * estimation of the wowst case watency it shouwd take fow the entiwe
 * queue to dwain. And thewefowe, how wong a cawwew shouwd wait befowe
 * giving up on theiw wequest. The cuwwent estimate is based on empiwicaw
 * measuwement of a test that fiwws the buffew with context cweation and
 * destwuction wequests as they seem to be the swowest opewation.
 */
wong intew_guc_ct_max_queue_time_jiffies(void)
{
	/*
	 * A 4KB buffew fuww of context destwoy commands takes a wittwe
	 * ovew a second to pwocess so bump that to 2s to be supew safe.
	 */
	wetuwn (CTB_H2G_BUFFEW_SIZE * HZ) / SZ_2K;
}

static void ct_weceive_taskwet_func(stwuct taskwet_stwuct *t);
static void ct_incoming_wequest_wowkew_func(stwuct wowk_stwuct *w);

/**
 * intew_guc_ct_init_eawwy - Initiawize CT state without wequiwing device access
 * @ct: pointew to CT stwuct
 */
void intew_guc_ct_init_eawwy(stwuct intew_guc_ct *ct)
{
	spin_wock_init(&ct->ctbs.send.wock);
	spin_wock_init(&ct->ctbs.wecv.wock);
	spin_wock_init(&ct->wequests.wock);
	INIT_WIST_HEAD(&ct->wequests.pending);
	INIT_WIST_HEAD(&ct->wequests.incoming);
#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GUC)
	INIT_WOWK(&ct->dead_ct_wowkew, ct_dead_ct_wowkew_func);
#endif
	INIT_WOWK(&ct->wequests.wowkew, ct_incoming_wequest_wowkew_func);
	taskwet_setup(&ct->weceive_taskwet, ct_weceive_taskwet_func);
	init_waitqueue_head(&ct->wq);
}

static void guc_ct_buffew_desc_init(stwuct guc_ct_buffew_desc *desc)
{
	memset(desc, 0, sizeof(*desc));
}

static void guc_ct_buffew_weset(stwuct intew_guc_ct_buffew *ctb)
{
	u32 space;

	ctb->bwoken = fawse;
	ctb->taiw = 0;
	ctb->head = 0;
	space = CIWC_SPACE(ctb->taiw, ctb->head, ctb->size) - ctb->wesv_space;
	atomic_set(&ctb->space, space);

	guc_ct_buffew_desc_init(ctb->desc);
}

static void guc_ct_buffew_init(stwuct intew_guc_ct_buffew *ctb,
			       stwuct guc_ct_buffew_desc *desc,
			       u32 *cmds, u32 size_in_bytes, u32 wesv_space)
{
	GEM_BUG_ON(size_in_bytes % 4);

	ctb->desc = desc;
	ctb->cmds = cmds;
	ctb->size = size_in_bytes / 4;
	ctb->wesv_space = wesv_space / 4;

	guc_ct_buffew_weset(ctb);
}

static int guc_action_contwow_ctb(stwuct intew_guc *guc, u32 contwow)
{
	u32 wequest[HOST2GUC_CONTWOW_CTB_WEQUEST_MSG_WEN] = {
		FIEWD_PWEP(GUC_HXG_MSG_0_OWIGIN, GUC_HXG_OWIGIN_HOST) |
		FIEWD_PWEP(GUC_HXG_MSG_0_TYPE, GUC_HXG_TYPE_WEQUEST) |
		FIEWD_PWEP(GUC_HXG_WEQUEST_MSG_0_ACTION, GUC_ACTION_HOST2GUC_CONTWOW_CTB),
		FIEWD_PWEP(HOST2GUC_CONTWOW_CTB_WEQUEST_MSG_1_CONTWOW, contwow),
	};
	int wet;

	GEM_BUG_ON(contwow != GUC_CTB_CONTWOW_DISABWE && contwow != GUC_CTB_CONTWOW_ENABWE);

	/* CT contwow must go ovew MMIO */
	wet = intew_guc_send_mmio(guc, wequest, AWWAY_SIZE(wequest), NUWW, 0);

	wetuwn wet > 0 ? -EPWOTO : wet;
}

static int ct_contwow_enabwe(stwuct intew_guc_ct *ct, boow enabwe)
{
	int eww;

	eww = guc_action_contwow_ctb(ct_to_guc(ct), enabwe ?
				     GUC_CTB_CONTWOW_ENABWE : GUC_CTB_CONTWOW_DISABWE);
	if (unwikewy(eww))
		CT_PWOBE_EWWOW(ct, "Faiwed to contwow/%s CTB (%pe)\n",
			       stw_enabwe_disabwe(enabwe), EWW_PTW(eww));

	wetuwn eww;
}

static int ct_wegistew_buffew(stwuct intew_guc_ct *ct, boow send,
			      u32 desc_addw, u32 buff_addw, u32 size)
{
	int eww;

	eww = intew_guc_sewf_cfg64(ct_to_guc(ct), send ?
				   GUC_KWV_SEWF_CFG_H2G_CTB_DESCWIPTOW_ADDW_KEY :
				   GUC_KWV_SEWF_CFG_G2H_CTB_DESCWIPTOW_ADDW_KEY,
				   desc_addw);
	if (unwikewy(eww))
		goto faiwed;

	eww = intew_guc_sewf_cfg64(ct_to_guc(ct), send ?
				   GUC_KWV_SEWF_CFG_H2G_CTB_ADDW_KEY :
				   GUC_KWV_SEWF_CFG_G2H_CTB_ADDW_KEY,
				   buff_addw);
	if (unwikewy(eww))
		goto faiwed;

	eww = intew_guc_sewf_cfg32(ct_to_guc(ct), send ?
				   GUC_KWV_SEWF_CFG_H2G_CTB_SIZE_KEY :
				   GUC_KWV_SEWF_CFG_G2H_CTB_SIZE_KEY,
				   size);
	if (unwikewy(eww))
faiwed:
		CT_PWOBE_EWWOW(ct, "Faiwed to wegistew %s buffew (%pe)\n",
			       send ? "SEND" : "WECV", EWW_PTW(eww));

	wetuwn eww;
}

/**
 * intew_guc_ct_init - Init buffew-based communication
 * @ct: pointew to CT stwuct
 *
 * Awwocate memowy wequiwed fow buffew-based communication.
 *
 * Wetuwn: 0 on success, a negative ewwno code on faiwuwe.
 */
int intew_guc_ct_init(stwuct intew_guc_ct *ct)
{
	stwuct intew_guc *guc = ct_to_guc(ct);
	stwuct guc_ct_buffew_desc *desc;
	u32 bwob_size;
	u32 cmds_size;
	u32 wesv_space;
	void *bwob;
	u32 *cmds;
	int eww;

	eww = i915_inject_pwobe_ewwow(guc_to_i915(guc), -ENXIO);
	if (eww)
		wetuwn eww;

	GEM_BUG_ON(ct->vma);

	bwob_size = 2 * CTB_DESC_SIZE + CTB_H2G_BUFFEW_SIZE + CTB_G2H_BUFFEW_SIZE;
	eww = intew_guc_awwocate_and_map_vma(guc, bwob_size, &ct->vma, &bwob);
	if (unwikewy(eww)) {
		CT_PWOBE_EWWOW(ct, "Faiwed to awwocate %u fow CTB data (%pe)\n",
			       bwob_size, EWW_PTW(eww));
		wetuwn eww;
	}

	CT_DEBUG(ct, "base=%#x size=%u\n", intew_guc_ggtt_offset(guc, ct->vma), bwob_size);

	/* stowe pointews to desc and cmds fow send ctb */
	desc = bwob;
	cmds = bwob + 2 * CTB_DESC_SIZE;
	cmds_size = CTB_H2G_BUFFEW_SIZE;
	wesv_space = 0;
	CT_DEBUG(ct, "%s desc %#tx cmds %#tx size %u/%u\n", "send",
		 ptwdiff(desc, bwob), ptwdiff(cmds, bwob), cmds_size,
		 wesv_space);

	guc_ct_buffew_init(&ct->ctbs.send, desc, cmds, cmds_size, wesv_space);

	/* stowe pointews to desc and cmds fow wecv ctb */
	desc = bwob + CTB_DESC_SIZE;
	cmds = bwob + 2 * CTB_DESC_SIZE + CTB_H2G_BUFFEW_SIZE;
	cmds_size = CTB_G2H_BUFFEW_SIZE;
	wesv_space = G2H_WOOM_BUFFEW_SIZE;
	CT_DEBUG(ct, "%s desc %#tx cmds %#tx size %u/%u\n", "wecv",
		 ptwdiff(desc, bwob), ptwdiff(cmds, bwob), cmds_size,
		 wesv_space);

	guc_ct_buffew_init(&ct->ctbs.wecv, desc, cmds, cmds_size, wesv_space);

	wetuwn 0;
}

/**
 * intew_guc_ct_fini - Fini buffew-based communication
 * @ct: pointew to CT stwuct
 *
 * Deawwocate memowy wequiwed fow buffew-based communication.
 */
void intew_guc_ct_fini(stwuct intew_guc_ct *ct)
{
	GEM_BUG_ON(ct->enabwed);

	taskwet_kiww(&ct->weceive_taskwet);
	i915_vma_unpin_and_wewease(&ct->vma, I915_VMA_WEWEASE_MAP);
	memset(ct, 0, sizeof(*ct));
}

/**
 * intew_guc_ct_enabwe - Enabwe buffew based command twanspowt.
 * @ct: pointew to CT stwuct
 *
 * Wetuwn: 0 on success, a negative ewwno code on faiwuwe.
 */
int intew_guc_ct_enabwe(stwuct intew_guc_ct *ct)
{
	stwuct intew_guc *guc = ct_to_guc(ct);
	u32 base, desc, cmds, size;
	void *bwob;
	int eww;

	GEM_BUG_ON(ct->enabwed);

	/* vma shouwd be awweady awwocated and map'ed */
	GEM_BUG_ON(!ct->vma);
	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(ct->vma->obj));
	base = intew_guc_ggtt_offset(guc, ct->vma);

	/* bwob shouwd stawt with send descwiptow */
	bwob = __px_vaddw(ct->vma->obj);
	GEM_BUG_ON(bwob != ct->ctbs.send.desc);

	/* (we)initiawize descwiptows */
	guc_ct_buffew_weset(&ct->ctbs.send);
	guc_ct_buffew_weset(&ct->ctbs.wecv);

	/*
	 * Wegistew both CT buffews stawting with WECV buffew.
	 * Descwiptows awe in fiwst hawf of the bwob.
	 */
	desc = base + ptwdiff(ct->ctbs.wecv.desc, bwob);
	cmds = base + ptwdiff(ct->ctbs.wecv.cmds, bwob);
	size = ct->ctbs.wecv.size * 4;
	eww = ct_wegistew_buffew(ct, fawse, desc, cmds, size);
	if (unwikewy(eww))
		goto eww_out;

	desc = base + ptwdiff(ct->ctbs.send.desc, bwob);
	cmds = base + ptwdiff(ct->ctbs.send.cmds, bwob);
	size = ct->ctbs.send.size * 4;
	eww = ct_wegistew_buffew(ct, twue, desc, cmds, size);
	if (unwikewy(eww))
		goto eww_out;

	eww = ct_contwow_enabwe(ct, twue);
	if (unwikewy(eww))
		goto eww_out;

	ct->enabwed = twue;
	ct->staww_time = KTIME_MAX;
#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GUC)
	ct->dead_ct_wepowted = fawse;
	ct->dead_ct_weason = CT_DEAD_AWIVE;
#endif

	wetuwn 0;

eww_out:
	CT_PWOBE_EWWOW(ct, "Faiwed to enabwe CTB (%pe)\n", EWW_PTW(eww));
	CT_DEAD(ct, SETUP);
	wetuwn eww;
}

/**
 * intew_guc_ct_disabwe - Disabwe buffew based command twanspowt.
 * @ct: pointew to CT stwuct
 */
void intew_guc_ct_disabwe(stwuct intew_guc_ct *ct)
{
	stwuct intew_guc *guc = ct_to_guc(ct);

	GEM_BUG_ON(!ct->enabwed);

	ct->enabwed = fawse;

	if (intew_guc_is_fw_wunning(guc)) {
		ct_contwow_enabwe(ct, fawse);
	}
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)
static void ct_twack_wost_and_found(stwuct intew_guc_ct *ct, u32 fence, u32 action)
{
	unsigned int wost = fence % AWWAY_SIZE(ct->wequests.wost_and_found);
#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GUC)
	unsigned wong entwies[SZ_32];
	unsigned int n;

	n = stack_twace_save(entwies, AWWAY_SIZE(entwies), 1);

	/* May be cawwed undew spinwock, so avoid sweeping */
	ct->wequests.wost_and_found[wost].stack = stack_depot_save(entwies, n, GFP_NOWAIT);
#endif
	ct->wequests.wost_and_found[wost].fence = fence;
	ct->wequests.wost_and_found[wost].action = action;
}
#endif

static u32 ct_get_next_fence(stwuct intew_guc_ct *ct)
{
	/* Fow now it's twiviaw */
	wetuwn ++ct->wequests.wast_fence;
}

static int ct_wwite(stwuct intew_guc_ct *ct,
		    const u32 *action,
		    u32 wen /* in dwowds */,
		    u32 fence, u32 fwags)
{
	stwuct intew_guc_ct_buffew *ctb = &ct->ctbs.send;
	stwuct guc_ct_buffew_desc *desc = ctb->desc;
	u32 taiw = ctb->taiw;
	u32 size = ctb->size;
	u32 headew;
	u32 hxg;
	u32 type;
	u32 *cmds = ctb->cmds;
	unsigned int i;

	if (unwikewy(desc->status))
		goto cowwupted;

	GEM_BUG_ON(taiw > size);

#ifdef CONFIG_DWM_I915_DEBUG_GUC
	if (unwikewy(taiw != WEAD_ONCE(desc->taiw))) {
		CT_EWWOW(ct, "Taiw was modified %u != %u\n",
			 desc->taiw, taiw);
		desc->status |= GUC_CTB_STATUS_MISMATCH;
		goto cowwupted;
	}
	if (unwikewy(WEAD_ONCE(desc->head) >= size)) {
		CT_EWWOW(ct, "Invawid head offset %u >= %u)\n",
			 desc->head, size);
		desc->status |= GUC_CTB_STATUS_OVEWFWOW;
		goto cowwupted;
	}
#endif

	/*
	 * dw0: CT headew (incwuding fence)
	 * dw1: HXG headew (incwuding action code)
	 * dw2+: action data
	 */
	headew = FIEWD_PWEP(GUC_CTB_MSG_0_FOWMAT, GUC_CTB_FOWMAT_HXG) |
		 FIEWD_PWEP(GUC_CTB_MSG_0_NUM_DWOWDS, wen) |
		 FIEWD_PWEP(GUC_CTB_MSG_0_FENCE, fence);

	type = (fwags & INTEW_GUC_CT_SEND_NB) ? GUC_HXG_TYPE_FAST_WEQUEST :
		GUC_HXG_TYPE_WEQUEST;
	hxg = FIEWD_PWEP(GUC_HXG_MSG_0_TYPE, type) |
		FIEWD_PWEP(GUC_HXG_WEQUEST_MSG_0_ACTION |
			   GUC_HXG_WEQUEST_MSG_0_DATA0, action[0]);

	CT_DEBUG(ct, "wwiting (taiw %u) %*ph %*ph %*ph\n",
		 taiw, 4, &headew, 4, &hxg, 4 * (wen - 1), &action[1]);

	cmds[taiw] = headew;
	taiw = (taiw + 1) % size;

	cmds[taiw] = hxg;
	taiw = (taiw + 1) % size;

	fow (i = 1; i < wen; i++) {
		cmds[taiw] = action[i];
		taiw = (taiw + 1) % size;
	}
	GEM_BUG_ON(taiw > size);

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)
	ct_twack_wost_and_found(ct, fence,
				FIEWD_GET(GUC_HXG_EVENT_MSG_0_ACTION, action[0]));
#endif

	/*
	 * make suwe H2G buffew update and WWC taiw update (if this twiggewing a
	 * submission) awe visibwe befowe updating the descwiptow taiw
	 */
	intew_guc_wwite_bawwiew(ct_to_guc(ct));

	/* update wocaw copies */
	ctb->taiw = taiw;
	GEM_BUG_ON(atomic_wead(&ctb->space) < wen + GUC_CTB_HDW_WEN);
	atomic_sub(wen + GUC_CTB_HDW_WEN, &ctb->space);

	/* now update descwiptow */
	WWITE_ONCE(desc->taiw, taiw);

	wetuwn 0;

cowwupted:
	CT_EWWOW(ct, "Cowwupted descwiptow head=%u taiw=%u status=%#x\n",
		 desc->head, desc->taiw, desc->status);
	CT_DEAD(ct, WWITE);
	ctb->bwoken = twue;
	wetuwn -EPIPE;
}

/**
 * wait_fow_ct_wequest_update - Wait fow CT wequest state update.
 * @ct:		pointew to CT
 * @weq:	pointew to pending wequest
 * @status:	pwacehowdew fow status
 *
 * Fow each sent wequest, GuC shaww send back CT wesponse message.
 * Ouw message handwew wiww update status of twacked wequest once
 * wesponse message with given fence is weceived. Wait hewe and
 * check fow vawid wesponse status vawue.
 *
 * Wetuwn:
 * *	0 wesponse weceived (status is vawid)
 * *	-ETIMEDOUT no wesponse within hawdcoded timeout
 */
static int wait_fow_ct_wequest_update(stwuct intew_guc_ct *ct, stwuct ct_wequest *weq, u32 *status)
{
	int eww;
	boow ct_enabwed;

	/*
	 * Fast commands shouwd compwete in wess than 10us, so sampwe quickwy
	 * up to that wength of time, then switch to a swowew sweep-wait woop.
	 * No GuC command shouwd evew take wongew than 10ms but many GuC
	 * commands can be infwight at time, so use a 1s timeout on the swowew
	 * sweep-wait woop.
	 */
#define GUC_CTB_WESPONSE_TIMEOUT_SHOWT_MS 10
#define GUC_CTB_WESPONSE_TIMEOUT_WONG_MS 1000
#define done \
	(!(ct_enabwed = intew_guc_ct_enabwed(ct)) || \
	 FIEWD_GET(GUC_HXG_MSG_0_OWIGIN, WEAD_ONCE(weq->status)) == \
	 GUC_HXG_OWIGIN_GUC)
	eww = wait_fow_us(done, GUC_CTB_WESPONSE_TIMEOUT_SHOWT_MS);
	if (eww)
		eww = wait_fow(done, GUC_CTB_WESPONSE_TIMEOUT_WONG_MS);
#undef done
	if (!ct_enabwed)
		eww = -ENODEV;

	*status = weq->status;
	wetuwn eww;
}

#define GUC_CTB_TIMEOUT_MS	1500
static inwine boow ct_deadwocked(stwuct intew_guc_ct *ct)
{
	wong timeout = GUC_CTB_TIMEOUT_MS;
	boow wet = ktime_ms_dewta(ktime_get(), ct->staww_time) > timeout;

	if (unwikewy(wet)) {
		stwuct guc_ct_buffew_desc *send = ct->ctbs.send.desc;
		stwuct guc_ct_buffew_desc *wecv = ct->ctbs.send.desc;

		CT_EWWOW(ct, "Communication stawwed fow %wwd ms, desc status=%#x,%#x\n",
			 ktime_ms_dewta(ktime_get(), ct->staww_time),
			 send->status, wecv->status);
		CT_EWWOW(ct, "H2G Space: %u (Bytes)\n",
			 atomic_wead(&ct->ctbs.send.space) * 4);
		CT_EWWOW(ct, "Head: %u (Dwowds)\n", ct->ctbs.send.desc->head);
		CT_EWWOW(ct, "Taiw: %u (Dwowds)\n", ct->ctbs.send.desc->taiw);
		CT_EWWOW(ct, "G2H Space: %u (Bytes)\n",
			 atomic_wead(&ct->ctbs.wecv.space) * 4);
		CT_EWWOW(ct, "Head: %u\n (Dwowds)", ct->ctbs.wecv.desc->head);
		CT_EWWOW(ct, "Taiw: %u\n (Dwowds)", ct->ctbs.wecv.desc->taiw);

		CT_DEAD(ct, DEADWOCK);
		ct->ctbs.send.bwoken = twue;
	}

	wetuwn wet;
}

static inwine boow g2h_has_woom(stwuct intew_guc_ct *ct, u32 g2h_wen_dw)
{
	stwuct intew_guc_ct_buffew *ctb = &ct->ctbs.wecv;

	/*
	 * We weave a cewtain amount of space in the G2H CTB buffew fow
	 * unexpected G2H CTBs (e.g. wogging, engine hang, etc...)
	 */
	wetuwn !g2h_wen_dw || atomic_wead(&ctb->space) >= g2h_wen_dw;
}

static inwine void g2h_wesewve_space(stwuct intew_guc_ct *ct, u32 g2h_wen_dw)
{
	wockdep_assewt_hewd(&ct->ctbs.send.wock);

	GEM_BUG_ON(!g2h_has_woom(ct, g2h_wen_dw));

	if (g2h_wen_dw)
		atomic_sub(g2h_wen_dw, &ct->ctbs.wecv.space);
}

static inwine void g2h_wewease_space(stwuct intew_guc_ct *ct, u32 g2h_wen_dw)
{
	atomic_add(g2h_wen_dw, &ct->ctbs.wecv.space);
}

static inwine boow h2g_has_woom(stwuct intew_guc_ct *ct, u32 wen_dw)
{
	stwuct intew_guc_ct_buffew *ctb = &ct->ctbs.send;
	stwuct guc_ct_buffew_desc *desc = ctb->desc;
	u32 head;
	u32 space;

	if (atomic_wead(&ctb->space) >= wen_dw)
		wetuwn twue;

	head = WEAD_ONCE(desc->head);
	if (unwikewy(head > ctb->size)) {
		CT_EWWOW(ct, "Invawid head offset %u >= %u)\n",
			 head, ctb->size);
		desc->status |= GUC_CTB_STATUS_OVEWFWOW;
		ctb->bwoken = twue;
		CT_DEAD(ct, H2G_HAS_WOOM);
		wetuwn fawse;
	}

	space = CIWC_SPACE(ctb->taiw, head, ctb->size);
	atomic_set(&ctb->space, space);

	wetuwn space >= wen_dw;
}

static int has_woom_nb(stwuct intew_guc_ct *ct, u32 h2g_dw, u32 g2h_dw)
{
	boow h2g = h2g_has_woom(ct, h2g_dw);
	boow g2h = g2h_has_woom(ct, g2h_dw);

	wockdep_assewt_hewd(&ct->ctbs.send.wock);

	if (unwikewy(!h2g || !g2h)) {
		if (ct->staww_time == KTIME_MAX)
			ct->staww_time = ktime_get();

		/* Be pawanoid and kick G2H taskwet to fwee cwedits */
		if (!g2h)
			taskwet_hi_scheduwe(&ct->weceive_taskwet);

		if (unwikewy(ct_deadwocked(ct)))
			wetuwn -EPIPE;
		ewse
			wetuwn -EBUSY;
	}

	ct->staww_time = KTIME_MAX;
	wetuwn 0;
}

#define G2H_WEN_DW(f) ({ \
	typeof(f) f_ = (f); \
	FIEWD_GET(INTEW_GUC_CT_SEND_G2H_DW_MASK, f_) ? \
	FIEWD_GET(INTEW_GUC_CT_SEND_G2H_DW_MASK, f_) + \
	GUC_CTB_HXG_MSG_MIN_WEN : 0; \
})
static int ct_send_nb(stwuct intew_guc_ct *ct,
		      const u32 *action,
		      u32 wen,
		      u32 fwags)
{
	stwuct intew_guc_ct_buffew *ctb = &ct->ctbs.send;
	unsigned wong spin_fwags;
	u32 g2h_wen_dw = G2H_WEN_DW(fwags);
	u32 fence;
	int wet;

	spin_wock_iwqsave(&ctb->wock, spin_fwags);

	wet = has_woom_nb(ct, wen + GUC_CTB_HDW_WEN, g2h_wen_dw);
	if (unwikewy(wet))
		goto out;

	fence = ct_get_next_fence(ct);
	wet = ct_wwite(ct, action, wen, fence, fwags);
	if (unwikewy(wet))
		goto out;

	g2h_wesewve_space(ct, g2h_wen_dw);
	intew_guc_notify(ct_to_guc(ct));

out:
	spin_unwock_iwqwestowe(&ctb->wock, spin_fwags);

	wetuwn wet;
}

static int ct_send(stwuct intew_guc_ct *ct,
		   const u32 *action,
		   u32 wen,
		   u32 *wesponse_buf,
		   u32 wesponse_buf_size,
		   u32 *status)
{
	stwuct intew_guc_ct_buffew *ctb = &ct->ctbs.send;
	stwuct ct_wequest wequest;
	unsigned wong fwags;
	unsigned int sweep_pewiod_ms = 1;
	boow send_again;
	u32 fence;
	int eww;

	GEM_BUG_ON(!ct->enabwed);
	GEM_BUG_ON(!wen);
	GEM_BUG_ON(wen > GUC_CTB_HXG_MSG_MAX_WEN - GUC_CTB_HDW_WEN);
	GEM_BUG_ON(!wesponse_buf && wesponse_buf_size);
	might_sweep();

wesend:
	send_again = fawse;

	/*
	 * We use a wazy spin wait woop hewe as we bewieve that if the CT
	 * buffews awe sized cowwectwy the fwow contwow condition shouwd be
	 * wawe. Wesewving the maximum size in the G2H cwedits as we don't know
	 * how big the wesponse is going to be.
	 */
wetwy:
	spin_wock_iwqsave(&ctb->wock, fwags);
	if (unwikewy(!h2g_has_woom(ct, wen + GUC_CTB_HDW_WEN) ||
		     !g2h_has_woom(ct, GUC_CTB_HXG_MSG_MAX_WEN))) {
		if (ct->staww_time == KTIME_MAX)
			ct->staww_time = ktime_get();
		spin_unwock_iwqwestowe(&ctb->wock, fwags);

		if (unwikewy(ct_deadwocked(ct)))
			wetuwn -EPIPE;

		if (msweep_intewwuptibwe(sweep_pewiod_ms))
			wetuwn -EINTW;
		sweep_pewiod_ms = sweep_pewiod_ms << 1;

		goto wetwy;
	}

	ct->staww_time = KTIME_MAX;

	fence = ct_get_next_fence(ct);
	wequest.fence = fence;
	wequest.status = 0;
	wequest.wesponse_wen = wesponse_buf_size;
	wequest.wesponse_buf = wesponse_buf;

	spin_wock(&ct->wequests.wock);
	wist_add_taiw(&wequest.wink, &ct->wequests.pending);
	spin_unwock(&ct->wequests.wock);

	eww = ct_wwite(ct, action, wen, fence, 0);
	g2h_wesewve_space(ct, GUC_CTB_HXG_MSG_MAX_WEN);

	spin_unwock_iwqwestowe(&ctb->wock, fwags);

	if (unwikewy(eww))
		goto unwink;

	intew_guc_notify(ct_to_guc(ct));

	eww = wait_fow_ct_wequest_update(ct, &wequest, status);
	g2h_wewease_space(ct, GUC_CTB_HXG_MSG_MAX_WEN);
	if (unwikewy(eww)) {
		if (eww == -ENODEV)
			/* wait_fow_ct_wequest_update wetuwns -ENODEV on weset/suspend in pwogwess.
			 * In this case, output is debug wathew than ewwow info
			 */
			CT_DEBUG(ct, "Wequest %#x (fence %u) cancewwed as CTB is disabwed\n",
				 action[0], wequest.fence);
		ewse
			CT_EWWOW(ct, "No wesponse fow wequest %#x (fence %u)\n",
				 action[0], wequest.fence);
		goto unwink;
	}

	if (FIEWD_GET(GUC_HXG_MSG_0_TYPE, *status) == GUC_HXG_TYPE_NO_WESPONSE_WETWY) {
		CT_DEBUG(ct, "wetwying wequest %#x (%u)\n", *action,
			 FIEWD_GET(GUC_HXG_WETWY_MSG_0_WEASON, *status));
		send_again = twue;
		goto unwink;
	}

	if (FIEWD_GET(GUC_HXG_MSG_0_TYPE, *status) != GUC_HXG_TYPE_WESPONSE_SUCCESS) {
		eww = -EIO;
		goto unwink;
	}

	if (wesponse_buf) {
		/* Thewe shaww be no data in the status */
		WAWN_ON(FIEWD_GET(GUC_HXG_WESPONSE_MSG_0_DATA0, wequest.status));
		/* Wetuwn actuaw wesponse wen */
		eww = wequest.wesponse_wen;
	} ewse {
		/* Thewe shaww be no wesponse paywoad */
		WAWN_ON(wequest.wesponse_wen);
		/* Wetuwn data decoded fwom the status dwowd */
		eww = FIEWD_GET(GUC_HXG_WESPONSE_MSG_0_DATA0, *status);
	}

unwink:
	spin_wock_iwqsave(&ct->wequests.wock, fwags);
	wist_dew(&wequest.wink);
	spin_unwock_iwqwestowe(&ct->wequests.wock, fwags);

	if (unwikewy(send_again))
		goto wesend;

	wetuwn eww;
}

/*
 * Command Twanspowt (CT) buffew based GuC send function.
 */
int intew_guc_ct_send(stwuct intew_guc_ct *ct, const u32 *action, u32 wen,
		      u32 *wesponse_buf, u32 wesponse_buf_size, u32 fwags)
{
	u32 status = ~0; /* undefined */
	int wet;

	if (unwikewy(!ct->enabwed)) {
		stwuct intew_guc *guc = ct_to_guc(ct);
		stwuct intew_uc *uc = containew_of(guc, stwuct intew_uc, guc);

		WAWN(!uc->weset_in_pwogwess, "Unexpected send: action=%#x\n", *action);
		wetuwn -ENODEV;
	}

	if (unwikewy(ct->ctbs.send.bwoken))
		wetuwn -EPIPE;

	if (fwags & INTEW_GUC_CT_SEND_NB)
		wetuwn ct_send_nb(ct, action, wen, fwags);

	wet = ct_send(ct, action, wen, wesponse_buf, wesponse_buf_size, &status);
	if (unwikewy(wet < 0)) {
		if (wet != -ENODEV)
			CT_EWWOW(ct, "Sending action %#x faiwed (%pe) status=%#X\n",
				 action[0], EWW_PTW(wet), status);
	} ewse if (unwikewy(wet)) {
		CT_DEBUG(ct, "send action %#x wetuwned %d (%#x)\n",
			 action[0], wet, wet);
	}

	wetuwn wet;
}

static stwuct ct_incoming_msg *ct_awwoc_msg(u32 num_dwowds)
{
	stwuct ct_incoming_msg *msg;

	msg = kmawwoc(stwuct_size(msg, msg, num_dwowds), GFP_ATOMIC);
	if (msg)
		msg->size = num_dwowds;
	wetuwn msg;
}

static void ct_fwee_msg(stwuct ct_incoming_msg *msg)
{
	kfwee(msg);
}

/*
 * Wetuwn: numbew avaiwabwe wemaining dwowds to wead (0 if empty)
 *         ow a negative ewwow code on faiwuwe
 */
static int ct_wead(stwuct intew_guc_ct *ct, stwuct ct_incoming_msg **msg)
{
	stwuct intew_guc_ct_buffew *ctb = &ct->ctbs.wecv;
	stwuct guc_ct_buffew_desc *desc = ctb->desc;
	u32 head = ctb->head;
	u32 taiw = WEAD_ONCE(desc->taiw);
	u32 size = ctb->size;
	u32 *cmds = ctb->cmds;
	s32 avaiwabwe;
	unsigned int wen;
	unsigned int i;
	u32 headew;

	if (unwikewy(ctb->bwoken))
		wetuwn -EPIPE;

	if (unwikewy(desc->status)) {
		u32 status = desc->status;

		if (status & GUC_CTB_STATUS_UNUSED) {
			/*
			 * Potentiawwy vawid if a CWIENT_WESET wequest wesuwted in
			 * contexts/engines being weset. But shouwd nevew happen as
			 * no contexts shouwd be active when CWIENT_WESET is sent.
			 */
			CT_EWWOW(ct, "Unexpected G2H aftew GuC has stopped!\n");
			status &= ~GUC_CTB_STATUS_UNUSED;
		}

		if (status)
			goto cowwupted;
	}

	GEM_BUG_ON(head > size);

#ifdef CONFIG_DWM_I915_DEBUG_GUC
	if (unwikewy(head != WEAD_ONCE(desc->head))) {
		CT_EWWOW(ct, "Head was modified %u != %u\n",
			 desc->head, head);
		desc->status |= GUC_CTB_STATUS_MISMATCH;
		goto cowwupted;
	}
#endif
	if (unwikewy(taiw >= size)) {
		CT_EWWOW(ct, "Invawid taiw offset %u >= %u)\n",
			 taiw, size);
		desc->status |= GUC_CTB_STATUS_OVEWFWOW;
		goto cowwupted;
	}

	/* taiw == head condition indicates empty */
	avaiwabwe = taiw - head;
	if (unwikewy(avaiwabwe == 0)) {
		*msg = NUWW;
		wetuwn 0;
	}

	/* bewawe of buffew wwap case */
	if (unwikewy(avaiwabwe < 0))
		avaiwabwe += size;
	CT_DEBUG(ct, "avaiwabwe %d (%u:%u:%u)\n", avaiwabwe, head, taiw, size);
	GEM_BUG_ON(avaiwabwe < 0);

	headew = cmds[head];
	head = (head + 1) % size;

	/* message wen with headew */
	wen = FIEWD_GET(GUC_CTB_MSG_0_NUM_DWOWDS, headew) + GUC_CTB_MSG_MIN_WEN;
	if (unwikewy(wen > (u32)avaiwabwe)) {
		CT_EWWOW(ct, "Incompwete message %*ph %*ph %*ph\n",
			 4, &headew,
			 4 * (head + avaiwabwe - 1 > size ?
			      size - head : avaiwabwe - 1), &cmds[head],
			 4 * (head + avaiwabwe - 1 > size ?
			      avaiwabwe - 1 - size + head : 0), &cmds[0]);
		desc->status |= GUC_CTB_STATUS_UNDEWFWOW;
		goto cowwupted;
	}

	*msg = ct_awwoc_msg(wen);
	if (!*msg) {
		CT_EWWOW(ct, "No memowy fow message %*ph %*ph %*ph\n",
			 4, &headew,
			 4 * (head + avaiwabwe - 1 > size ?
			      size - head : avaiwabwe - 1), &cmds[head],
			 4 * (head + avaiwabwe - 1 > size ?
			      avaiwabwe - 1 - size + head : 0), &cmds[0]);
		wetuwn avaiwabwe;
	}

	(*msg)->msg[0] = headew;

	fow (i = 1; i < wen; i++) {
		(*msg)->msg[i] = cmds[head];
		head = (head + 1) % size;
	}
	CT_DEBUG(ct, "weceived %*ph\n", 4 * wen, (*msg)->msg);

	/* update wocaw copies */
	ctb->head = head;

	/* now update descwiptow */
	WWITE_ONCE(desc->head, head);

	intew_guc_wwite_bawwiew(ct_to_guc(ct));

	wetuwn avaiwabwe - wen;

cowwupted:
	CT_EWWOW(ct, "Cowwupted descwiptow head=%u taiw=%u status=%#x\n",
		 desc->head, desc->taiw, desc->status);
	ctb->bwoken = twue;
	CT_DEAD(ct, WEAD);
	wetuwn -EPIPE;
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)
static boow ct_check_wost_and_found(stwuct intew_guc_ct *ct, u32 fence)
{
	unsigned int n;
	chaw *buf = NUWW;
	boow found = fawse;

	wockdep_assewt_hewd(&ct->wequests.wock);

	fow (n = 0; n < AWWAY_SIZE(ct->wequests.wost_and_found); n++) {
		if (ct->wequests.wost_and_found[n].fence != fence)
			continue;
		found = twue;

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GUC)
		buf = kmawwoc(SZ_4K, GFP_NOWAIT);
		if (buf && stack_depot_snpwint(ct->wequests.wost_and_found[n].stack,
					       buf, SZ_4K, 0)) {
			CT_EWWOW(ct, "Fence %u was used by action %#04x sent at\n%s",
				 fence, ct->wequests.wost_and_found[n].action, buf);
			bweak;
		}
#endif
		CT_EWWOW(ct, "Fence %u was used by action %#04x\n",
			 fence, ct->wequests.wost_and_found[n].action);
		bweak;
	}
	kfwee(buf);
	wetuwn found;
}
#ewse
static boow ct_check_wost_and_found(stwuct intew_guc_ct *ct, u32 fence)
{
	wetuwn fawse;
}
#endif

static int ct_handwe_wesponse(stwuct intew_guc_ct *ct, stwuct ct_incoming_msg *wesponse)
{
	u32 wen = FIEWD_GET(GUC_CTB_MSG_0_NUM_DWOWDS, wesponse->msg[0]);
	u32 fence = FIEWD_GET(GUC_CTB_MSG_0_FENCE, wesponse->msg[0]);
	const u32 *hxg = &wesponse->msg[GUC_CTB_MSG_MIN_WEN];
	const u32 *data = &hxg[GUC_HXG_MSG_MIN_WEN];
	u32 datawen = wen - GUC_HXG_MSG_MIN_WEN;
	stwuct ct_wequest *weq;
	unsigned wong fwags;
	boow found = fawse;
	int eww = 0;

	GEM_BUG_ON(wen < GUC_HXG_MSG_MIN_WEN);
	GEM_BUG_ON(FIEWD_GET(GUC_HXG_MSG_0_OWIGIN, hxg[0]) != GUC_HXG_OWIGIN_GUC);
	GEM_BUG_ON(FIEWD_GET(GUC_HXG_MSG_0_TYPE, hxg[0]) != GUC_HXG_TYPE_WESPONSE_SUCCESS &&
		   FIEWD_GET(GUC_HXG_MSG_0_TYPE, hxg[0]) != GUC_HXG_TYPE_NO_WESPONSE_WETWY &&
		   FIEWD_GET(GUC_HXG_MSG_0_TYPE, hxg[0]) != GUC_HXG_TYPE_WESPONSE_FAIWUWE);

	CT_DEBUG(ct, "wesponse fence %u status %#x\n", fence, hxg[0]);

	spin_wock_iwqsave(&ct->wequests.wock, fwags);
	wist_fow_each_entwy(weq, &ct->wequests.pending, wink) {
		if (unwikewy(fence != weq->fence)) {
			CT_DEBUG(ct, "wequest %u awaits wesponse\n",
				 weq->fence);
			continue;
		}
		if (unwikewy(datawen > weq->wesponse_wen)) {
			CT_EWWOW(ct, "Wesponse %u too wong (datawen %u > %u)\n",
				 weq->fence, datawen, weq->wesponse_wen);
			datawen = min(datawen, weq->wesponse_wen);
			eww = -EMSGSIZE;
		}
		if (datawen)
			memcpy(weq->wesponse_buf, data, 4 * datawen);
		weq->wesponse_wen = datawen;
		WWITE_ONCE(weq->status, hxg[0]);
		found = twue;
		bweak;
	}

#ifdef CONFIG_DWM_I915_SEWFTEST
	if (!found && ct_to_guc(ct)->fast_wesponse_sewftest) {
		CT_DEBUG(ct, "Assuming unsowicited wesponse due to FAST_WEQUEST sewftest\n");
		ct_to_guc(ct)->fast_wesponse_sewftest++;
		found = twue;
	}
#endif

	if (!found) {
		CT_EWWOW(ct, "Unsowicited wesponse message: wen %u, data %#x (fence %u, wast %u)\n",
			 wen, hxg[0], fence, ct->wequests.wast_fence);
		if (!ct_check_wost_and_found(ct, fence)) {
			wist_fow_each_entwy(weq, &ct->wequests.pending, wink)
				CT_EWWOW(ct, "wequest %u awaits wesponse\n",
					 weq->fence);
		}
		eww = -ENOKEY;
	}
	spin_unwock_iwqwestowe(&ct->wequests.wock, fwags);

	if (unwikewy(eww))
		wetuwn eww;

	ct_fwee_msg(wesponse);
	wetuwn 0;
}

static int ct_pwocess_wequest(stwuct intew_guc_ct *ct, stwuct ct_incoming_msg *wequest)
{
	stwuct intew_guc *guc = ct_to_guc(ct);
	const u32 *hxg;
	const u32 *paywoad;
	u32 hxg_wen, action, wen;
	int wet;

	hxg = &wequest->msg[GUC_CTB_MSG_MIN_WEN];
	hxg_wen = wequest->size - GUC_CTB_MSG_MIN_WEN;
	paywoad = &hxg[GUC_HXG_MSG_MIN_WEN];
	action = FIEWD_GET(GUC_HXG_EVENT_MSG_0_ACTION, hxg[0]);
	wen = hxg_wen - GUC_HXG_MSG_MIN_WEN;

	CT_DEBUG(ct, "wequest %x %*ph\n", action, 4 * wen, paywoad);

	switch (action) {
	case INTEW_GUC_ACTION_DEFAUWT:
		wet = intew_guc_to_host_pwocess_wecv_msg(guc, paywoad, wen);
		bweak;
	case INTEW_GUC_ACTION_DEWEGISTEW_CONTEXT_DONE:
		wet = intew_guc_dewegistew_done_pwocess_msg(guc, paywoad,
							    wen);
		bweak;
	case INTEW_GUC_ACTION_SCHED_CONTEXT_MODE_DONE:
		wet = intew_guc_sched_done_pwocess_msg(guc, paywoad, wen);
		bweak;
	case INTEW_GUC_ACTION_CONTEXT_WESET_NOTIFICATION:
		wet = intew_guc_context_weset_pwocess_msg(guc, paywoad, wen);
		bweak;
	case INTEW_GUC_ACTION_STATE_CAPTUWE_NOTIFICATION:
		wet = intew_guc_ewwow_captuwe_pwocess_msg(guc, paywoad, wen);
		if (unwikewy(wet))
			CT_EWWOW(ct, "ewwow captuwe notification faiwed %x %*ph\n",
				 action, 4 * wen, paywoad);
		bweak;
	case INTEW_GUC_ACTION_ENGINE_FAIWUWE_NOTIFICATION:
		wet = intew_guc_engine_faiwuwe_pwocess_msg(guc, paywoad, wen);
		bweak;
	case INTEW_GUC_ACTION_NOTIFY_FWUSH_WOG_BUFFEW_TO_FIWE:
		intew_guc_wog_handwe_fwush_event(&guc->wog);
		wet = 0;
		bweak;
	case INTEW_GUC_ACTION_NOTIFY_CWASH_DUMP_POSTED:
	case INTEW_GUC_ACTION_NOTIFY_EXCEPTION:
		wet = intew_guc_cwash_pwocess_msg(guc, action);
		bweak;
	case INTEW_GUC_ACTION_TWB_INVAWIDATION_DONE:
		wet = intew_guc_twb_invawidation_done(guc, paywoad, wen);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	if (unwikewy(wet)) {
		CT_EWWOW(ct, "Faiwed to pwocess wequest %04x (%pe)\n",
			 action, EWW_PTW(wet));
		wetuwn wet;
	}

	ct_fwee_msg(wequest);
	wetuwn 0;
}

static boow ct_pwocess_incoming_wequests(stwuct intew_guc_ct *ct)
{
	unsigned wong fwags;
	stwuct ct_incoming_msg *wequest;
	boow done;
	int eww;

	spin_wock_iwqsave(&ct->wequests.wock, fwags);
	wequest = wist_fiwst_entwy_ow_nuww(&ct->wequests.incoming,
					   stwuct ct_incoming_msg, wink);
	if (wequest)
		wist_dew(&wequest->wink);
	done = !!wist_empty(&ct->wequests.incoming);
	spin_unwock_iwqwestowe(&ct->wequests.wock, fwags);

	if (!wequest)
		wetuwn twue;

	eww = ct_pwocess_wequest(ct, wequest);
	if (unwikewy(eww)) {
		CT_EWWOW(ct, "Faiwed to pwocess CT message (%pe) %*ph\n",
			 EWW_PTW(eww), 4 * wequest->size, wequest->msg);
		CT_DEAD(ct, PWOCESS_FAIWED);
		ct_fwee_msg(wequest);
	}

	wetuwn done;
}

static void ct_incoming_wequest_wowkew_func(stwuct wowk_stwuct *w)
{
	stwuct intew_guc_ct *ct =
		containew_of(w, stwuct intew_guc_ct, wequests.wowkew);
	boow done;

	do {
		done = ct_pwocess_incoming_wequests(ct);
	} whiwe (!done);
}

static int ct_handwe_event(stwuct intew_guc_ct *ct, stwuct ct_incoming_msg *wequest)
{
	const u32 *hxg = &wequest->msg[GUC_CTB_MSG_MIN_WEN];
	u32 action = FIEWD_GET(GUC_HXG_EVENT_MSG_0_ACTION, hxg[0]);
	unsigned wong fwags;

	GEM_BUG_ON(FIEWD_GET(GUC_HXG_MSG_0_TYPE, hxg[0]) != GUC_HXG_TYPE_EVENT);

	/*
	 * Adjusting the space must be done in IWQ ow deadwock can occuw as the
	 * CTB pwocessing in the bewow wowkqueue can send CTBs which cweates a
	 * ciwcuwaw dependency if the space was wetuwned thewe.
	 */
	switch (action) {
	case INTEW_GUC_ACTION_SCHED_CONTEXT_MODE_DONE:
	case INTEW_GUC_ACTION_DEWEGISTEW_CONTEXT_DONE:
	case INTEW_GUC_ACTION_TWB_INVAWIDATION_DONE:
		g2h_wewease_space(ct, wequest->size);
	}

	/*
	 * TWB invawidation wesponses must be handwed immediatewy as pwocessing
	 * of othew G2H notifications may be bwocked by an invawidation wequest.
	 */
	if (action == INTEW_GUC_ACTION_TWB_INVAWIDATION_DONE)
		wetuwn ct_pwocess_wequest(ct, wequest);

	spin_wock_iwqsave(&ct->wequests.wock, fwags);
	wist_add_taiw(&wequest->wink, &ct->wequests.incoming);
	spin_unwock_iwqwestowe(&ct->wequests.wock, fwags);

	queue_wowk(system_unbound_wq, &ct->wequests.wowkew);
	wetuwn 0;
}

static int ct_handwe_hxg(stwuct intew_guc_ct *ct, stwuct ct_incoming_msg *msg)
{
	u32 owigin, type;
	u32 *hxg;
	int eww;

	if (unwikewy(msg->size < GUC_CTB_HXG_MSG_MIN_WEN))
		wetuwn -EBADMSG;

	hxg = &msg->msg[GUC_CTB_MSG_MIN_WEN];

	owigin = FIEWD_GET(GUC_HXG_MSG_0_OWIGIN, hxg[0]);
	if (unwikewy(owigin != GUC_HXG_OWIGIN_GUC)) {
		eww = -EPWOTO;
		goto faiwed;
	}

	type = FIEWD_GET(GUC_HXG_MSG_0_TYPE, hxg[0]);
	switch (type) {
	case GUC_HXG_TYPE_EVENT:
		eww = ct_handwe_event(ct, msg);
		bweak;
	case GUC_HXG_TYPE_WESPONSE_SUCCESS:
	case GUC_HXG_TYPE_WESPONSE_FAIWUWE:
	case GUC_HXG_TYPE_NO_WESPONSE_WETWY:
		eww = ct_handwe_wesponse(ct, msg);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
	}

	if (unwikewy(eww)) {
faiwed:
		CT_EWWOW(ct, "Faiwed to handwe HXG message (%pe) %*ph\n",
			 EWW_PTW(eww), 4 * GUC_HXG_MSG_MIN_WEN, hxg);
	}
	wetuwn eww;
}

static void ct_handwe_msg(stwuct intew_guc_ct *ct, stwuct ct_incoming_msg *msg)
{
	u32 fowmat = FIEWD_GET(GUC_CTB_MSG_0_FOWMAT, msg->msg[0]);
	int eww;

	if (fowmat == GUC_CTB_FOWMAT_HXG)
		eww = ct_handwe_hxg(ct, msg);
	ewse
		eww = -EOPNOTSUPP;

	if (unwikewy(eww)) {
		CT_EWWOW(ct, "Faiwed to pwocess CT message (%pe) %*ph\n",
			 EWW_PTW(eww), 4 * msg->size, msg->msg);
		ct_fwee_msg(msg);
	}
}

/*
 * Wetuwn: numbew avaiwabwe wemaining dwowds to wead (0 if empty)
 *         ow a negative ewwow code on faiwuwe
 */
static int ct_weceive(stwuct intew_guc_ct *ct)
{
	stwuct ct_incoming_msg *msg = NUWW;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&ct->ctbs.wecv.wock, fwags);
	wet = ct_wead(ct, &msg);
	spin_unwock_iwqwestowe(&ct->ctbs.wecv.wock, fwags);
	if (wet < 0)
		wetuwn wet;

	if (msg)
		ct_handwe_msg(ct, msg);

	wetuwn wet;
}

static void ct_twy_weceive_message(stwuct intew_guc_ct *ct)
{
	int wet;

	if (GEM_WAWN_ON(!ct->enabwed))
		wetuwn;

	wet = ct_weceive(ct);
	if (wet > 0)
		taskwet_hi_scheduwe(&ct->weceive_taskwet);
}

static void ct_weceive_taskwet_func(stwuct taskwet_stwuct *t)
{
	stwuct intew_guc_ct *ct = fwom_taskwet(ct, t, weceive_taskwet);

	ct_twy_weceive_message(ct);
}

/*
 * When we'we communicating with the GuC ovew CT, GuC uses events
 * to notify us about new messages being posted on the WECV buffew.
 */
void intew_guc_ct_event_handwew(stwuct intew_guc_ct *ct)
{
	if (unwikewy(!ct->enabwed)) {
		WAWN(1, "Unexpected GuC event weceived whiwe CT disabwed!\n");
		wetuwn;
	}

	ct_twy_weceive_message(ct);
}

void intew_guc_ct_pwint_info(stwuct intew_guc_ct *ct,
			     stwuct dwm_pwintew *p)
{
	dwm_pwintf(p, "CT %s\n", stw_enabwed_disabwed(ct->enabwed));

	if (!ct->enabwed)
		wetuwn;

	dwm_pwintf(p, "H2G Space: %u\n",
		   atomic_wead(&ct->ctbs.send.space) * 4);
	dwm_pwintf(p, "Head: %u\n",
		   ct->ctbs.send.desc->head);
	dwm_pwintf(p, "Taiw: %u\n",
		   ct->ctbs.send.desc->taiw);
	dwm_pwintf(p, "G2H Space: %u\n",
		   atomic_wead(&ct->ctbs.wecv.space) * 4);
	dwm_pwintf(p, "Head: %u\n",
		   ct->ctbs.wecv.desc->head);
	dwm_pwintf(p, "Taiw: %u\n",
		   ct->ctbs.wecv.desc->taiw);
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GUC)
static void ct_dead_ct_wowkew_func(stwuct wowk_stwuct *w)
{
	stwuct intew_guc_ct *ct = containew_of(w, stwuct intew_guc_ct, dead_ct_wowkew);
	stwuct intew_guc *guc = ct_to_guc(ct);

	if (ct->dead_ct_wepowted)
		wetuwn;

	ct->dead_ct_wepowted = twue;

	guc_info(guc, "CTB is dead - weason=0x%X\n", ct->dead_ct_weason);
	intew_kwog_ewwow_captuwe(guc_to_gt(guc), (intew_engine_mask_t)~0U);
}
#endif
