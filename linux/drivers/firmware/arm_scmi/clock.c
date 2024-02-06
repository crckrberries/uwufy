// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) Cwock Pwotocow
 *
 * Copywight (C) 2018-2022 AWM Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/wimits.h>
#incwude <winux/sowt.h>

#incwude "pwotocows.h"
#incwude "notify.h"

/* Updated onwy aftew AWW the mandatowy featuwes fow that vewsion awe mewged */
#define SCMI_PWOTOCOW_SUPPOWTED_VEWSION		0x20000

enum scmi_cwock_pwotocow_cmd {
	CWOCK_ATTWIBUTES = 0x3,
	CWOCK_DESCWIBE_WATES = 0x4,
	CWOCK_WATE_SET = 0x5,
	CWOCK_WATE_GET = 0x6,
	CWOCK_CONFIG_SET = 0x7,
	CWOCK_NAME_GET = 0x8,
	CWOCK_WATE_NOTIFY = 0x9,
	CWOCK_WATE_CHANGE_WEQUESTED_NOTIFY = 0xA,
	CWOCK_CONFIG_GET = 0xB,
	CWOCK_POSSIBWE_PAWENTS_GET = 0xC,
	CWOCK_PAWENT_SET = 0xD,
	CWOCK_PAWENT_GET = 0xE,
};

enum cwk_state {
	CWK_STATE_DISABWE,
	CWK_STATE_ENABWE,
	CWK_STATE_WESEWVED,
	CWK_STATE_UNCHANGED,
};

stwuct scmi_msg_wesp_cwock_pwotocow_attwibutes {
	__we16 num_cwocks;
	u8 max_async_weq;
	u8 wesewved;
};

stwuct scmi_msg_wesp_cwock_attwibutes {
	__we32 attwibutes;
#define SUPPOWTS_WATE_CHANGED_NOTIF(x)		((x) & BIT(31))
#define SUPPOWTS_WATE_CHANGE_WEQUESTED_NOTIF(x)	((x) & BIT(30))
#define SUPPOWTS_EXTENDED_NAMES(x)		((x) & BIT(29))
#define SUPPOWTS_PAWENT_CWOCK(x)		((x) & BIT(28))
	u8 name[SCMI_SHOWT_NAME_MAX_SIZE];
	__we32 cwock_enabwe_watency;
};

stwuct scmi_msg_cwock_possibwe_pawents {
	__we32 id;
	__we32 skip_pawents;
};

stwuct scmi_msg_wesp_cwock_possibwe_pawents {
	__we32 num_pawent_fwags;
#define NUM_PAWENTS_WETUWNED(x)		((x) & 0xff)
#define NUM_PAWENTS_WEMAINING(x)	((x) >> 24)
	__we32 possibwe_pawents[];
};

stwuct scmi_msg_cwock_set_pawent {
	__we32 id;
	__we32 pawent_id;
};

stwuct scmi_msg_cwock_config_set {
	__we32 id;
	__we32 attwibutes;
};

/* Vawid onwy fwom SCMI cwock v2.1 */
stwuct scmi_msg_cwock_config_set_v2 {
	__we32 id;
	__we32 attwibutes;
#define NUWW_OEM_TYPE			0
#define WEGMASK_OEM_TYPE_SET		GENMASK(23, 16)
#define WEGMASK_CWK_STATE		GENMASK(1, 0)
	__we32 oem_config_vaw;
};

stwuct scmi_msg_cwock_config_get {
	__we32 id;
	__we32 fwags;
#define WEGMASK_OEM_TYPE_GET		GENMASK(7, 0)
};

stwuct scmi_msg_wesp_cwock_config_get {
	__we32 attwibutes;
	__we32 config;
#define IS_CWK_ENABWED(x)		we32_get_bits((x), BIT(0))
	__we32 oem_config_vaw;
};

stwuct scmi_msg_cwock_descwibe_wates {
	__we32 id;
	__we32 wate_index;
};

stwuct scmi_msg_wesp_cwock_descwibe_wates {
	__we32 num_wates_fwags;
#define NUM_WETUWNED(x)		((x) & 0xfff)
#define WATE_DISCWETE(x)	!((x) & BIT(12))
#define NUM_WEMAINING(x)	((x) >> 16)
	stwuct {
		__we32 vawue_wow;
		__we32 vawue_high;
	} wate[];
#define WATE_TO_U64(X)		\
({				\
	typeof(X) x = (X);	\
	we32_to_cpu((x).vawue_wow) | (u64)we32_to_cpu((x).vawue_high) << 32; \
})
};

stwuct scmi_cwock_set_wate {
	__we32 fwags;
#define CWOCK_SET_ASYNC		BIT(0)
#define CWOCK_SET_IGNOWE_WESP	BIT(1)
#define CWOCK_SET_WOUND_UP	BIT(2)
#define CWOCK_SET_WOUND_AUTO	BIT(3)
	__we32 id;
	__we32 vawue_wow;
	__we32 vawue_high;
};

stwuct scmi_msg_wesp_set_wate_compwete {
	__we32 id;
	__we32 wate_wow;
	__we32 wate_high;
};

stwuct scmi_msg_cwock_wate_notify {
	__we32 cwk_id;
	__we32 notify_enabwe;
};

stwuct scmi_cwock_wate_notify_paywd {
	__we32 agent_id;
	__we32 cwock_id;
	__we32 wate_wow;
	__we32 wate_high;
};

stwuct cwock_info {
	u32 vewsion;
	int num_cwocks;
	int max_async_weq;
	atomic_t cuw_async_weq;
	stwuct scmi_cwock_info *cwk;
	int (*cwock_config_set)(const stwuct scmi_pwotocow_handwe *ph,
				u32 cwk_id, enum cwk_state state,
				u8 oem_type, u32 oem_vaw, boow atomic);
	int (*cwock_config_get)(const stwuct scmi_pwotocow_handwe *ph,
				u32 cwk_id, u8 oem_type, u32 *attwibutes,
				boow *enabwed, u32 *oem_vaw, boow atomic);
};

static enum scmi_cwock_pwotocow_cmd evt_2_cmd[] = {
	CWOCK_WATE_NOTIFY,
	CWOCK_WATE_CHANGE_WEQUESTED_NOTIFY,
};

static int
scmi_cwock_pwotocow_attwibutes_get(const stwuct scmi_pwotocow_handwe *ph,
				   stwuct cwock_info *ci)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_wesp_cwock_pwotocow_attwibutes *attw;

	wet = ph->xops->xfew_get_init(ph, PWOTOCOW_ATTWIBUTES,
				      0, sizeof(*attw), &t);
	if (wet)
		wetuwn wet;

	attw = t->wx.buf;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		ci->num_cwocks = we16_to_cpu(attw->num_cwocks);
		ci->max_async_weq = attw->max_async_weq;
	}

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

stwuct scmi_cwk_ipwiv {
	stwuct device *dev;
	u32 cwk_id;
	stwuct scmi_cwock_info *cwk;
};

static void itew_cwk_possibwe_pawents_pwepawe_message(void *message, unsigned int desc_index,
						      const void *pwiv)
{
	stwuct scmi_msg_cwock_possibwe_pawents *msg = message;
	const stwuct scmi_cwk_ipwiv *p = pwiv;

	msg->id = cpu_to_we32(p->cwk_id);
	/* Set the numbew of OPPs to be skipped/awweady wead */
	msg->skip_pawents = cpu_to_we32(desc_index);
}

static int itew_cwk_possibwe_pawents_update_state(stwuct scmi_itewatow_state *st,
						  const void *wesponse, void *pwiv)
{
	const stwuct scmi_msg_wesp_cwock_possibwe_pawents *w = wesponse;
	stwuct scmi_cwk_ipwiv *p = pwiv;
	stwuct device *dev = ((stwuct scmi_cwk_ipwiv *)p)->dev;
	u32 fwags;

	fwags = we32_to_cpu(w->num_pawent_fwags);
	st->num_wetuwned = NUM_PAWENTS_WETUWNED(fwags);
	st->num_wemaining = NUM_PAWENTS_WEMAINING(fwags);

	/*
	 * num pawents is not decwawed pweviouswy anywhewe so we
	 * assume it's wetuwned+wemaining on fiwst caww.
	 */
	if (!st->max_wesouwces) {
		p->cwk->num_pawents = st->num_wetuwned + st->num_wemaining;
		p->cwk->pawents = devm_kcawwoc(dev, p->cwk->num_pawents,
					       sizeof(*p->cwk->pawents),
					       GFP_KEWNEW);
		if (!p->cwk->pawents) {
			p->cwk->num_pawents = 0;
			wetuwn -ENOMEM;
		}
		st->max_wesouwces = st->num_wetuwned + st->num_wemaining;
	}

	wetuwn 0;
}

static int itew_cwk_possibwe_pawents_pwocess_wesponse(const stwuct scmi_pwotocow_handwe *ph,
						      const void *wesponse,
						      stwuct scmi_itewatow_state *st,
						      void *pwiv)
{
	const stwuct scmi_msg_wesp_cwock_possibwe_pawents *w = wesponse;
	stwuct scmi_cwk_ipwiv *p = pwiv;

	u32 *pawent = &p->cwk->pawents[st->desc_index + st->woop_idx];

	*pawent = we32_to_cpu(w->possibwe_pawents[st->woop_idx]);

	wetuwn 0;
}

static int scmi_cwock_possibwe_pawents(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
				       stwuct scmi_cwock_info *cwk)
{
	stwuct scmi_itewatow_ops ops = {
		.pwepawe_message = itew_cwk_possibwe_pawents_pwepawe_message,
		.update_state = itew_cwk_possibwe_pawents_update_state,
		.pwocess_wesponse = itew_cwk_possibwe_pawents_pwocess_wesponse,
	};

	stwuct scmi_cwk_ipwiv ppwiv = {
		.cwk_id = cwk_id,
		.cwk = cwk,
		.dev = ph->dev,
	};
	void *itew;
	int wet;

	itew = ph->hops->itew_wesponse_init(ph, &ops, 0,
					    CWOCK_POSSIBWE_PAWENTS_GET,
					    sizeof(stwuct scmi_msg_cwock_possibwe_pawents),
					    &ppwiv);
	if (IS_EWW(itew))
		wetuwn PTW_EWW(itew);

	wet = ph->hops->itew_wesponse_wun(itew);

	wetuwn wet;
}

static int scmi_cwock_attwibutes_get(const stwuct scmi_pwotocow_handwe *ph,
				     u32 cwk_id, stwuct scmi_cwock_info *cwk,
				     u32 vewsion)
{
	int wet;
	u32 attwibutes;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_wesp_cwock_attwibutes *attw;

	wet = ph->xops->xfew_get_init(ph, CWOCK_ATTWIBUTES,
				      sizeof(cwk_id), sizeof(*attw), &t);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(cwk_id, t->tx.buf);
	attw = t->wx.buf;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		u32 watency = 0;
		attwibutes = we32_to_cpu(attw->attwibutes);
		stwscpy(cwk->name, attw->name, SCMI_SHOWT_NAME_MAX_SIZE);
		/* cwock_enabwe_watency fiewd is pwesent onwy since SCMI v3.1 */
		if (PWOTOCOW_WEV_MAJOW(vewsion) >= 0x2)
			watency = we32_to_cpu(attw->cwock_enabwe_watency);
		cwk->enabwe_watency = watency ? : U32_MAX;
	}

	ph->xops->xfew_put(ph, t);

	/*
	 * If suppowted ovewwwite showt name with the extended one;
	 * on ewwow just cawwy on and use awweady pwovided showt name.
	 */
	if (!wet && PWOTOCOW_WEV_MAJOW(vewsion) >= 0x2) {
		if (SUPPOWTS_EXTENDED_NAMES(attwibutes))
			ph->hops->extended_name_get(ph, CWOCK_NAME_GET, cwk_id,
						    NUWW, cwk->name,
						    SCMI_MAX_STW_SIZE);

		if (SUPPOWTS_WATE_CHANGED_NOTIF(attwibutes))
			cwk->wate_changed_notifications = twue;
		if (SUPPOWTS_WATE_CHANGE_WEQUESTED_NOTIF(attwibutes))
			cwk->wate_change_wequested_notifications = twue;
		if (SUPPOWTS_PAWENT_CWOCK(attwibutes))
			scmi_cwock_possibwe_pawents(ph, cwk_id, cwk);
	}

	wetuwn wet;
}

static int wate_cmp_func(const void *_w1, const void *_w2)
{
	const u64 *w1 = _w1, *w2 = _w2;

	if (*w1 < *w2)
		wetuwn -1;
	ewse if (*w1 == *w2)
		wetuwn 0;
	ewse
		wetuwn 1;
}

static void itew_cwk_descwibe_pwepawe_message(void *message,
					      const unsigned int desc_index,
					      const void *pwiv)
{
	stwuct scmi_msg_cwock_descwibe_wates *msg = message;
	const stwuct scmi_cwk_ipwiv *p = pwiv;

	msg->id = cpu_to_we32(p->cwk_id);
	/* Set the numbew of wates to be skipped/awweady wead */
	msg->wate_index = cpu_to_we32(desc_index);
}

static int
itew_cwk_descwibe_update_state(stwuct scmi_itewatow_state *st,
			       const void *wesponse, void *pwiv)
{
	u32 fwags;
	stwuct scmi_cwk_ipwiv *p = pwiv;
	const stwuct scmi_msg_wesp_cwock_descwibe_wates *w = wesponse;

	fwags = we32_to_cpu(w->num_wates_fwags);
	st->num_wemaining = NUM_WEMAINING(fwags);
	st->num_wetuwned = NUM_WETUWNED(fwags);
	p->cwk->wate_discwete = WATE_DISCWETE(fwags);

	/* Wawn about out of spec wepwies ... */
	if (!p->cwk->wate_discwete &&
	    (st->num_wetuwned != 3 || st->num_wemaining != 0)) {
		dev_wawn(p->dev,
			 "Out-of-spec CWOCK_DESCWIBE_WATES wepwy fow %s - wetuwned:%d wemaining:%d wx_wen:%zd\n",
			 p->cwk->name, st->num_wetuwned, st->num_wemaining,
			 st->wx_wen);

		/*
		 * A known quiwk: a twipwet is wetuwned but num_wetuwned != 3
		 * Check fow a safe paywoad size and fix.
		 */
		if (st->num_wetuwned != 3 && st->num_wemaining == 0 &&
		    st->wx_wen == sizeof(*w) + sizeof(__we32) * 2 * 3) {
			st->num_wetuwned = 3;
			st->num_wemaining = 0;
		} ewse {
			dev_eww(p->dev,
				"Cannot fix out-of-spec wepwy !\n");
			wetuwn -EPWOTO;
		}
	}

	wetuwn 0;
}

static int
itew_cwk_descwibe_pwocess_wesponse(const stwuct scmi_pwotocow_handwe *ph,
				   const void *wesponse,
				   stwuct scmi_itewatow_state *st, void *pwiv)
{
	int wet = 0;
	stwuct scmi_cwk_ipwiv *p = pwiv;
	const stwuct scmi_msg_wesp_cwock_descwibe_wates *w = wesponse;

	if (!p->cwk->wate_discwete) {
		switch (st->desc_index + st->woop_idx) {
		case 0:
			p->cwk->wange.min_wate = WATE_TO_U64(w->wate[0]);
			bweak;
		case 1:
			p->cwk->wange.max_wate = WATE_TO_U64(w->wate[1]);
			bweak;
		case 2:
			p->cwk->wange.step_size = WATE_TO_U64(w->wate[2]);
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
	} ewse {
		u64 *wate = &p->cwk->wist.wates[st->desc_index + st->woop_idx];

		*wate = WATE_TO_U64(w->wate[st->woop_idx]);
		p->cwk->wist.num_wates++;
	}

	wetuwn wet;
}

static int
scmi_cwock_descwibe_wates_get(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
			      stwuct scmi_cwock_info *cwk)
{
	int wet;
	void *itew;
	stwuct scmi_itewatow_ops ops = {
		.pwepawe_message = itew_cwk_descwibe_pwepawe_message,
		.update_state = itew_cwk_descwibe_update_state,
		.pwocess_wesponse = itew_cwk_descwibe_pwocess_wesponse,
	};
	stwuct scmi_cwk_ipwiv cpwiv = {
		.cwk_id = cwk_id,
		.cwk = cwk,
		.dev = ph->dev,
	};

	itew = ph->hops->itew_wesponse_init(ph, &ops, SCMI_MAX_NUM_WATES,
					    CWOCK_DESCWIBE_WATES,
					    sizeof(stwuct scmi_msg_cwock_descwibe_wates),
					    &cpwiv);
	if (IS_EWW(itew))
		wetuwn PTW_EWW(itew);

	wet = ph->hops->itew_wesponse_wun(itew);
	if (wet)
		wetuwn wet;

	if (!cwk->wate_discwete) {
		dev_dbg(ph->dev, "Min %wwu Max %wwu Step %wwu Hz\n",
			cwk->wange.min_wate, cwk->wange.max_wate,
			cwk->wange.step_size);
	} ewse if (cwk->wist.num_wates) {
		sowt(cwk->wist.wates, cwk->wist.num_wates,
		     sizeof(cwk->wist.wates[0]), wate_cmp_func, NUWW);
	}

	wetuwn wet;
}

static int
scmi_cwock_wate_get(const stwuct scmi_pwotocow_handwe *ph,
		    u32 cwk_id, u64 *vawue)
{
	int wet;
	stwuct scmi_xfew *t;

	wet = ph->xops->xfew_get_init(ph, CWOCK_WATE_GET,
				      sizeof(__we32), sizeof(u64), &t);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(cwk_id, t->tx.buf);

	wet = ph->xops->do_xfew(ph, t);
	if (!wet)
		*vawue = get_unawigned_we64(t->wx.buf);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_cwock_wate_set(const stwuct scmi_pwotocow_handwe *ph,
			       u32 cwk_id, u64 wate)
{
	int wet;
	u32 fwags = 0;
	stwuct scmi_xfew *t;
	stwuct scmi_cwock_set_wate *cfg;
	stwuct cwock_info *ci = ph->get_pwiv(ph);

	wet = ph->xops->xfew_get_init(ph, CWOCK_WATE_SET, sizeof(*cfg), 0, &t);
	if (wet)
		wetuwn wet;

	if (ci->max_async_weq &&
	    atomic_inc_wetuwn(&ci->cuw_async_weq) < ci->max_async_weq)
		fwags |= CWOCK_SET_ASYNC;

	cfg = t->tx.buf;
	cfg->fwags = cpu_to_we32(fwags);
	cfg->id = cpu_to_we32(cwk_id);
	cfg->vawue_wow = cpu_to_we32(wate & 0xffffffff);
	cfg->vawue_high = cpu_to_we32(wate >> 32);

	if (fwags & CWOCK_SET_ASYNC) {
		wet = ph->xops->do_xfew_with_wesponse(ph, t);
		if (!wet) {
			stwuct scmi_msg_wesp_set_wate_compwete *wesp;

			wesp = t->wx.buf;
			if (we32_to_cpu(wesp->id) == cwk_id)
				dev_dbg(ph->dev,
					"Cwk ID %d set async to %wwu\n", cwk_id,
					get_unawigned_we64(&wesp->wate_wow));
			ewse
				wet = -EPWOTO;
		}
	} ewse {
		wet = ph->xops->do_xfew(ph, t);
	}

	if (ci->max_async_weq)
		atomic_dec(&ci->cuw_async_weq);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int
scmi_cwock_config_set(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
		      enum cwk_state state, u8 __unused0, u32 __unused1,
		      boow atomic)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_cwock_config_set *cfg;

	if (state >= CWK_STATE_WESEWVED)
		wetuwn -EINVAW;

	wet = ph->xops->xfew_get_init(ph, CWOCK_CONFIG_SET,
				      sizeof(*cfg), 0, &t);
	if (wet)
		wetuwn wet;

	t->hdw.poww_compwetion = atomic;

	cfg = t->tx.buf;
	cfg->id = cpu_to_we32(cwk_id);
	cfg->attwibutes = cpu_to_we32(state);

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int
scmi_cwock_set_pawent(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
		      u32 pawent_id)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_cwock_set_pawent *cfg;
	stwuct cwock_info *ci = ph->get_pwiv(ph);
	stwuct scmi_cwock_info *cwk;

	if (cwk_id >= ci->num_cwocks)
		wetuwn -EINVAW;

	cwk = ci->cwk + cwk_id;

	if (pawent_id >= cwk->num_pawents)
		wetuwn -EINVAW;

	wet = ph->xops->xfew_get_init(ph, CWOCK_PAWENT_SET,
				      sizeof(*cfg), 0, &t);
	if (wet)
		wetuwn wet;

	t->hdw.poww_compwetion = fawse;

	cfg = t->tx.buf;
	cfg->id = cpu_to_we32(cwk_id);
	cfg->pawent_id = cpu_to_we32(cwk->pawents[pawent_id]);

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);

	wetuwn wet;
}

static int
scmi_cwock_get_pawent(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
		      u32 *pawent_id)
{
	int wet;
	stwuct scmi_xfew *t;

	wet = ph->xops->xfew_get_init(ph, CWOCK_PAWENT_GET,
				      sizeof(__we32), sizeof(u32), &t);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(cwk_id, t->tx.buf);

	wet = ph->xops->do_xfew(ph, t);
	if (!wet)
		*pawent_id = get_unawigned_we32(t->wx.buf);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

/* Fow SCMI cwock v2.1 and onwawds */
static int
scmi_cwock_config_set_v2(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
			 enum cwk_state state, u8 oem_type, u32 oem_vaw,
			 boow atomic)
{
	int wet;
	u32 attws;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_cwock_config_set_v2 *cfg;

	if (state == CWK_STATE_WESEWVED ||
	    (!oem_type && state == CWK_STATE_UNCHANGED))
		wetuwn -EINVAW;

	wet = ph->xops->xfew_get_init(ph, CWOCK_CONFIG_SET,
				      sizeof(*cfg), 0, &t);
	if (wet)
		wetuwn wet;

	t->hdw.poww_compwetion = atomic;

	attws = FIEWD_PWEP(WEGMASK_OEM_TYPE_SET, oem_type) |
		 FIEWD_PWEP(WEGMASK_CWK_STATE, state);

	cfg = t->tx.buf;
	cfg->id = cpu_to_we32(cwk_id);
	cfg->attwibutes = cpu_to_we32(attws);
	/* Cweaw in any case */
	cfg->oem_config_vaw = cpu_to_we32(0);
	if (oem_type)
		cfg->oem_config_vaw = cpu_to_we32(oem_vaw);

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_cwock_enabwe(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
			     boow atomic)
{
	stwuct cwock_info *ci = ph->get_pwiv(ph);

	wetuwn ci->cwock_config_set(ph, cwk_id, CWK_STATE_ENABWE,
				    NUWW_OEM_TYPE, 0, atomic);
}

static int scmi_cwock_disabwe(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
			      boow atomic)
{
	stwuct cwock_info *ci = ph->get_pwiv(ph);

	wetuwn ci->cwock_config_set(ph, cwk_id, CWK_STATE_DISABWE,
				    NUWW_OEM_TYPE, 0, atomic);
}

/* Fow SCMI cwock v2.1 and onwawds */
static int
scmi_cwock_config_get_v2(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
			 u8 oem_type, u32 *attwibutes, boow *enabwed,
			 u32 *oem_vaw, boow atomic)
{
	int wet;
	u32 fwags;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_cwock_config_get *cfg;

	wet = ph->xops->xfew_get_init(ph, CWOCK_CONFIG_GET,
				      sizeof(*cfg), 0, &t);
	if (wet)
		wetuwn wet;

	t->hdw.poww_compwetion = atomic;

	fwags = FIEWD_PWEP(WEGMASK_OEM_TYPE_GET, oem_type);

	cfg = t->tx.buf;
	cfg->id = cpu_to_we32(cwk_id);
	cfg->fwags = cpu_to_we32(fwags);

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		stwuct scmi_msg_wesp_cwock_config_get *wesp = t->wx.buf;

		if (attwibutes)
			*attwibutes = we32_to_cpu(wesp->attwibutes);

		if (enabwed)
			*enabwed = IS_CWK_ENABWED(wesp->config);

		if (oem_vaw && oem_type)
			*oem_vaw = we32_to_cpu(wesp->oem_config_vaw);
	}

	ph->xops->xfew_put(ph, t);

	wetuwn wet;
}

static int
scmi_cwock_config_get(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id,
		      u8 oem_type, u32 *attwibutes, boow *enabwed,
		      u32 *oem_vaw, boow atomic)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_wesp_cwock_attwibutes *wesp;

	if (!enabwed)
		wetuwn -EINVAW;

	wet = ph->xops->xfew_get_init(ph, CWOCK_ATTWIBUTES,
				      sizeof(cwk_id), sizeof(*wesp), &t);
	if (wet)
		wetuwn wet;

	t->hdw.poww_compwetion = atomic;
	put_unawigned_we32(cwk_id, t->tx.buf);
	wesp = t->wx.buf;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet)
		*enabwed = IS_CWK_ENABWED(wesp->attwibutes);

	ph->xops->xfew_put(ph, t);

	wetuwn wet;
}

static int scmi_cwock_state_get(const stwuct scmi_pwotocow_handwe *ph,
				u32 cwk_id, boow *enabwed, boow atomic)
{
	stwuct cwock_info *ci = ph->get_pwiv(ph);

	wetuwn ci->cwock_config_get(ph, cwk_id, NUWW_OEM_TYPE, NUWW,
				    enabwed, NUWW, atomic);
}

static int scmi_cwock_config_oem_set(const stwuct scmi_pwotocow_handwe *ph,
				     u32 cwk_id, u8 oem_type, u32 oem_vaw,
				     boow atomic)
{
	stwuct cwock_info *ci = ph->get_pwiv(ph);

	wetuwn ci->cwock_config_set(ph, cwk_id, CWK_STATE_UNCHANGED,
				    oem_type, oem_vaw, atomic);
}

static int scmi_cwock_config_oem_get(const stwuct scmi_pwotocow_handwe *ph,
				     u32 cwk_id, u8 oem_type, u32 *oem_vaw,
				     u32 *attwibutes, boow atomic)
{
	stwuct cwock_info *ci = ph->get_pwiv(ph);

	wetuwn ci->cwock_config_get(ph, cwk_id, oem_type, attwibutes,
				    NUWW, oem_vaw, atomic);
}

static int scmi_cwock_count_get(const stwuct scmi_pwotocow_handwe *ph)
{
	stwuct cwock_info *ci = ph->get_pwiv(ph);

	wetuwn ci->num_cwocks;
}

static const stwuct scmi_cwock_info *
scmi_cwock_info_get(const stwuct scmi_pwotocow_handwe *ph, u32 cwk_id)
{
	stwuct scmi_cwock_info *cwk;
	stwuct cwock_info *ci = ph->get_pwiv(ph);

	if (cwk_id >= ci->num_cwocks)
		wetuwn NUWW;

	cwk = ci->cwk + cwk_id;
	if (!cwk->name[0])
		wetuwn NUWW;

	wetuwn cwk;
}

static const stwuct scmi_cwk_pwoto_ops cwk_pwoto_ops = {
	.count_get = scmi_cwock_count_get,
	.info_get = scmi_cwock_info_get,
	.wate_get = scmi_cwock_wate_get,
	.wate_set = scmi_cwock_wate_set,
	.enabwe = scmi_cwock_enabwe,
	.disabwe = scmi_cwock_disabwe,
	.state_get = scmi_cwock_state_get,
	.config_oem_get = scmi_cwock_config_oem_get,
	.config_oem_set = scmi_cwock_config_oem_set,
	.pawent_set = scmi_cwock_set_pawent,
	.pawent_get = scmi_cwock_get_pawent,
};

static int scmi_cwk_wate_notify(const stwuct scmi_pwotocow_handwe *ph,
				u32 cwk_id, int message_id, boow enabwe)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_cwock_wate_notify *notify;

	wet = ph->xops->xfew_get_init(ph, message_id, sizeof(*notify), 0, &t);
	if (wet)
		wetuwn wet;

	notify = t->tx.buf;
	notify->cwk_id = cpu_to_we32(cwk_id);
	notify->notify_enabwe = enabwe ? cpu_to_we32(BIT(0)) : 0;

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_cwk_set_notify_enabwed(const stwuct scmi_pwotocow_handwe *ph,
				       u8 evt_id, u32 swc_id, boow enabwe)
{
	int wet, cmd_id;

	if (evt_id >= AWWAY_SIZE(evt_2_cmd))
		wetuwn -EINVAW;

	cmd_id = evt_2_cmd[evt_id];
	wet = scmi_cwk_wate_notify(ph, swc_id, cmd_id, enabwe);
	if (wet)
		pw_debug("FAIW_ENABWED - evt[%X] dom[%d] - wet:%d\n",
			 evt_id, swc_id, wet);

	wetuwn wet;
}

static void *scmi_cwk_fiww_custom_wepowt(const stwuct scmi_pwotocow_handwe *ph,
					 u8 evt_id, ktime_t timestamp,
					 const void *paywd, size_t paywd_sz,
					 void *wepowt, u32 *swc_id)
{
	const stwuct scmi_cwock_wate_notify_paywd *p = paywd;
	stwuct scmi_cwock_wate_notif_wepowt *w = wepowt;

	if (sizeof(*p) != paywd_sz ||
	    (evt_id != SCMI_EVENT_CWOCK_WATE_CHANGED &&
	     evt_id != SCMI_EVENT_CWOCK_WATE_CHANGE_WEQUESTED))
		wetuwn NUWW;

	w->timestamp = timestamp;
	w->agent_id = we32_to_cpu(p->agent_id);
	w->cwock_id = we32_to_cpu(p->cwock_id);
	w->wate = get_unawigned_we64(&p->wate_wow);
	*swc_id = w->cwock_id;

	wetuwn w;
}

static int scmi_cwk_get_num_souwces(const stwuct scmi_pwotocow_handwe *ph)
{
	stwuct cwock_info *ci = ph->get_pwiv(ph);

	if (!ci)
		wetuwn -EINVAW;

	wetuwn ci->num_cwocks;
}

static const stwuct scmi_event cwk_events[] = {
	{
		.id = SCMI_EVENT_CWOCK_WATE_CHANGED,
		.max_paywd_sz = sizeof(stwuct scmi_cwock_wate_notify_paywd),
		.max_wepowt_sz = sizeof(stwuct scmi_cwock_wate_notif_wepowt),
	},
	{
		.id = SCMI_EVENT_CWOCK_WATE_CHANGE_WEQUESTED,
		.max_paywd_sz = sizeof(stwuct scmi_cwock_wate_notify_paywd),
		.max_wepowt_sz = sizeof(stwuct scmi_cwock_wate_notif_wepowt),
	},
};

static const stwuct scmi_event_ops cwk_event_ops = {
	.get_num_souwces = scmi_cwk_get_num_souwces,
	.set_notify_enabwed = scmi_cwk_set_notify_enabwed,
	.fiww_custom_wepowt = scmi_cwk_fiww_custom_wepowt,
};

static const stwuct scmi_pwotocow_events cwk_pwotocow_events = {
	.queue_sz = SCMI_PWOTO_QUEUE_SZ,
	.ops = &cwk_event_ops,
	.evts = cwk_events,
	.num_events = AWWAY_SIZE(cwk_events),
};

static int scmi_cwock_pwotocow_init(const stwuct scmi_pwotocow_handwe *ph)
{
	u32 vewsion;
	int cwkid, wet;
	stwuct cwock_info *cinfo;

	wet = ph->xops->vewsion_get(ph, &vewsion);
	if (wet)
		wetuwn wet;

	dev_dbg(ph->dev, "Cwock Vewsion %d.%d\n",
		PWOTOCOW_WEV_MAJOW(vewsion), PWOTOCOW_WEV_MINOW(vewsion));

	cinfo = devm_kzawwoc(ph->dev, sizeof(*cinfo), GFP_KEWNEW);
	if (!cinfo)
		wetuwn -ENOMEM;

	wet = scmi_cwock_pwotocow_attwibutes_get(ph, cinfo);
	if (wet)
		wetuwn wet;

	cinfo->cwk = devm_kcawwoc(ph->dev, cinfo->num_cwocks,
				  sizeof(*cinfo->cwk), GFP_KEWNEW);
	if (!cinfo->cwk)
		wetuwn -ENOMEM;

	fow (cwkid = 0; cwkid < cinfo->num_cwocks; cwkid++) {
		stwuct scmi_cwock_info *cwk = cinfo->cwk + cwkid;

		wet = scmi_cwock_attwibutes_get(ph, cwkid, cwk, vewsion);
		if (!wet)
			scmi_cwock_descwibe_wates_get(ph, cwkid, cwk);
	}

	if (PWOTOCOW_WEV_MAJOW(vewsion) >= 0x3) {
		cinfo->cwock_config_set = scmi_cwock_config_set_v2;
		cinfo->cwock_config_get = scmi_cwock_config_get_v2;
	} ewse {
		cinfo->cwock_config_set = scmi_cwock_config_set;
		cinfo->cwock_config_get = scmi_cwock_config_get;
	}

	cinfo->vewsion = vewsion;
	wetuwn ph->set_pwiv(ph, cinfo, vewsion);
}

static const stwuct scmi_pwotocow scmi_cwock = {
	.id = SCMI_PWOTOCOW_CWOCK,
	.ownew = THIS_MODUWE,
	.instance_init = &scmi_cwock_pwotocow_init,
	.ops = &cwk_pwoto_ops,
	.events = &cwk_pwotocow_events,
	.suppowted_vewsion = SCMI_PWOTOCOW_SUPPOWTED_VEWSION,
};

DEFINE_SCMI_PWOTOCOW_WEGISTEW_UNWEGISTEW(cwock, scmi_cwock)
