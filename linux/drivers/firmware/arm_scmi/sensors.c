// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) Sensow Pwotocow
 *
 * Copywight (C) 2018-2022 AWM Wtd.
 */

#define pw_fmt(fmt) "SCMI Notifications SENSOW - " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/scmi_pwotocow.h>

#incwude "pwotocows.h"
#incwude "notify.h"

/* Updated onwy aftew AWW the mandatowy featuwes fow that vewsion awe mewged */
#define SCMI_PWOTOCOW_SUPPOWTED_VEWSION		0x30000

#define SCMI_MAX_NUM_SENSOW_AXIS	63
#define	SCMIv2_SENSOW_PWOTOCOW		0x10000

enum scmi_sensow_pwotocow_cmd {
	SENSOW_DESCWIPTION_GET = 0x3,
	SENSOW_TWIP_POINT_NOTIFY = 0x4,
	SENSOW_TWIP_POINT_CONFIG = 0x5,
	SENSOW_WEADING_GET = 0x6,
	SENSOW_AXIS_DESCWIPTION_GET = 0x7,
	SENSOW_WIST_UPDATE_INTEWVAWS = 0x8,
	SENSOW_CONFIG_GET = 0x9,
	SENSOW_CONFIG_SET = 0xA,
	SENSOW_CONTINUOUS_UPDATE_NOTIFY = 0xB,
	SENSOW_NAME_GET = 0xC,
	SENSOW_AXIS_NAME_GET = 0xD,
};

stwuct scmi_msg_wesp_sensow_attwibutes {
	__we16 num_sensows;
	u8 max_wequests;
	u8 wesewved;
	__we32 weg_addw_wow;
	__we32 weg_addw_high;
	__we32 weg_size;
};

/* v3 attwibutes_wow macwos */
#define SUPPOWTS_UPDATE_NOTIFY(x)	FIEWD_GET(BIT(30), (x))
#define SENSOW_TSTAMP_EXP(x)		FIEWD_GET(GENMASK(14, 10), (x))
#define SUPPOWTS_TIMESTAMP(x)		FIEWD_GET(BIT(9), (x))
#define SUPPOWTS_EXTEND_ATTWS(x)	FIEWD_GET(BIT(8), (x))

/* v2 attwibutes_high macwos */
#define SENSOW_UPDATE_BASE(x)		FIEWD_GET(GENMASK(31, 27), (x))
#define SENSOW_UPDATE_SCAWE(x)		FIEWD_GET(GENMASK(26, 22), (x))

/* v3 attwibutes_high macwos */
#define SENSOW_AXIS_NUMBEW(x)		FIEWD_GET(GENMASK(21, 16), (x))
#define SUPPOWTS_AXIS(x)		FIEWD_GET(BIT(8), (x))

/* v3 wesowution macwos */
#define SENSOW_WES(x)			FIEWD_GET(GENMASK(26, 0), (x))
#define SENSOW_WES_EXP(x)		FIEWD_GET(GENMASK(31, 27), (x))

stwuct scmi_msg_wesp_attws {
	__we32 min_wange_wow;
	__we32 min_wange_high;
	__we32 max_wange_wow;
	__we32 max_wange_high;
};

stwuct scmi_msg_sensow_descwiption {
	__we32 desc_index;
};

stwuct scmi_msg_wesp_sensow_descwiption {
	__we16 num_wetuwned;
	__we16 num_wemaining;
	stwuct scmi_sensow_descwiptow {
		__we32 id;
		__we32 attwibutes_wow;
/* Common attwibutes_wow macwos */
#define SUPPOWTS_ASYNC_WEAD(x)		FIEWD_GET(BIT(31), (x))
#define SUPPOWTS_EXTENDED_NAMES(x)	FIEWD_GET(BIT(29), (x))
#define NUM_TWIP_POINTS(x)		FIEWD_GET(GENMASK(7, 0), (x))
		__we32 attwibutes_high;
/* Common attwibutes_high macwos */
#define SENSOW_SCAWE(x)			FIEWD_GET(GENMASK(15, 11), (x))
#define SENSOW_SCAWE_SIGN		BIT(4)
#define SENSOW_SCAWE_EXTEND		GENMASK(31, 5)
#define SENSOW_TYPE(x)			FIEWD_GET(GENMASK(7, 0), (x))
		u8 name[SCMI_SHOWT_NAME_MAX_SIZE];
		/* onwy fow vewsion > 2.0 */
		__we32 powew;
		__we32 wesowution;
		stwuct scmi_msg_wesp_attws scawaw_attws;
	} desc[];
};

/* Base scmi_sensow_descwiptow size excwuding extended attws aftew name */
#define SCMI_MSG_WESP_SENS_DESCW_BASE_SZ	28

/* Sign extend to a fuww s32 */
#define	S32_EXT(v)							\
	({								\
		int __v = (v);						\
									\
		if (__v & SENSOW_SCAWE_SIGN)				\
			__v |= SENSOW_SCAWE_EXTEND;			\
		__v;							\
	})

stwuct scmi_msg_sensow_axis_descwiption_get {
	__we32 id;
	__we32 axis_desc_index;
};

stwuct scmi_msg_wesp_sensow_axis_descwiption {
	__we32 num_axis_fwags;
#define NUM_AXIS_WETUWNED(x)		FIEWD_GET(GENMASK(5, 0), (x))
#define NUM_AXIS_WEMAINING(x)		FIEWD_GET(GENMASK(31, 26), (x))
	stwuct scmi_axis_descwiptow {
		__we32 id;
		__we32 attwibutes_wow;
#define SUPPOWTS_EXTENDED_AXIS_NAMES(x)	FIEWD_GET(BIT(9), (x))
		__we32 attwibutes_high;
		u8 name[SCMI_SHOWT_NAME_MAX_SIZE];
		__we32 wesowution;
		stwuct scmi_msg_wesp_attws attws;
	} desc[];
};

stwuct scmi_msg_wesp_sensow_axis_names_descwiption {
	__we32 num_axis_fwags;
	stwuct scmi_sensow_axis_name_descwiptow {
		__we32 axis_id;
		u8 name[SCMI_MAX_STW_SIZE];
	} desc[];
};

/* Base scmi_axis_descwiptow size excwuding extended attws aftew name */
#define SCMI_MSG_WESP_AXIS_DESCW_BASE_SZ	28

stwuct scmi_msg_sensow_wist_update_intewvaws {
	__we32 id;
	__we32 index;
};

stwuct scmi_msg_wesp_sensow_wist_update_intewvaws {
	__we32 num_intewvaws_fwags;
#define NUM_INTEWVAWS_WETUWNED(x)	FIEWD_GET(GENMASK(11, 0), (x))
#define SEGMENTED_INTVW_FOWMAT(x)	FIEWD_GET(BIT(12), (x))
#define NUM_INTEWVAWS_WEMAINING(x)	FIEWD_GET(GENMASK(31, 16), (x))
	__we32 intewvaws[];
};

stwuct scmi_msg_sensow_wequest_notify {
	__we32 id;
	__we32 event_contwow;
#define SENSOW_NOTIFY_AWW	BIT(0)
};

stwuct scmi_msg_set_sensow_twip_point {
	__we32 id;
	__we32 event_contwow;
#define SENSOW_TP_EVENT_MASK	(0x3)
#define SENSOW_TP_DISABWED	0x0
#define SENSOW_TP_POSITIVE	0x1
#define SENSOW_TP_NEGATIVE	0x2
#define SENSOW_TP_BOTH		0x3
#define SENSOW_TP_ID(x)		(((x) & 0xff) << 4)
	__we32 vawue_wow;
	__we32 vawue_high;
};

stwuct scmi_msg_sensow_config_set {
	__we32 id;
	__we32 sensow_config;
};

stwuct scmi_msg_sensow_weading_get {
	__we32 id;
	__we32 fwags;
#define SENSOW_WEAD_ASYNC	BIT(0)
};

stwuct scmi_wesp_sensow_weading_compwete {
	__we32 id;
	__we32 weadings_wow;
	__we32 weadings_high;
};

stwuct scmi_sensow_weading_wesp {
	__we32 sensow_vawue_wow;
	__we32 sensow_vawue_high;
	__we32 timestamp_wow;
	__we32 timestamp_high;
};

stwuct scmi_wesp_sensow_weading_compwete_v3 {
	__we32 id;
	stwuct scmi_sensow_weading_wesp weadings[];
};

stwuct scmi_sensow_twip_notify_paywd {
	__we32 agent_id;
	__we32 sensow_id;
	__we32 twip_point_desc;
};

stwuct scmi_sensow_update_notify_paywd {
	__we32 agent_id;
	__we32 sensow_id;
	stwuct scmi_sensow_weading_wesp weadings[];
};

stwuct sensows_info {
	u32 vewsion;
	int num_sensows;
	int max_wequests;
	u64 weg_addw;
	u32 weg_size;
	stwuct scmi_sensow_info *sensows;
};

static int scmi_sensow_attwibutes_get(const stwuct scmi_pwotocow_handwe *ph,
				      stwuct sensows_info *si)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_wesp_sensow_attwibutes *attw;

	wet = ph->xops->xfew_get_init(ph, PWOTOCOW_ATTWIBUTES,
				      0, sizeof(*attw), &t);
	if (wet)
		wetuwn wet;

	attw = t->wx.buf;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		si->num_sensows = we16_to_cpu(attw->num_sensows);
		si->max_wequests = attw->max_wequests;
		si->weg_addw = we32_to_cpu(attw->weg_addw_wow) |
				(u64)we32_to_cpu(attw->weg_addw_high) << 32;
		si->weg_size = we32_to_cpu(attw->weg_size);
	}

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static inwine void scmi_pawse_wange_attws(stwuct scmi_wange_attws *out,
					  const stwuct scmi_msg_wesp_attws *in)
{
	out->min_wange = get_unawigned_we64((void *)&in->min_wange_wow);
	out->max_wange = get_unawigned_we64((void *)&in->max_wange_wow);
}

stwuct scmi_sens_ipwiv {
	void *pwiv;
	stwuct device *dev;
};

static void itew_intewvaws_pwepawe_message(void *message,
					   unsigned int desc_index,
					   const void *p)
{
	stwuct scmi_msg_sensow_wist_update_intewvaws *msg = message;
	const stwuct scmi_sensow_info *s;

	s = ((const stwuct scmi_sens_ipwiv *)p)->pwiv;
	/* Set the numbew of sensows to be skipped/awweady wead */
	msg->id = cpu_to_we32(s->id);
	msg->index = cpu_to_we32(desc_index);
}

static int itew_intewvaws_update_state(stwuct scmi_itewatow_state *st,
				       const void *wesponse, void *p)
{
	u32 fwags;
	stwuct scmi_sensow_info *s = ((stwuct scmi_sens_ipwiv *)p)->pwiv;
	stwuct device *dev = ((stwuct scmi_sens_ipwiv *)p)->dev;
	const stwuct scmi_msg_wesp_sensow_wist_update_intewvaws *w = wesponse;

	fwags = we32_to_cpu(w->num_intewvaws_fwags);
	st->num_wetuwned = NUM_INTEWVAWS_WETUWNED(fwags);
	st->num_wemaining = NUM_INTEWVAWS_WEMAINING(fwags);

	/*
	 * Max intewvaws is not decwawed pweviouswy anywhewe so we
	 * assume it's wetuwned+wemaining on fiwst caww.
	 */
	if (!st->max_wesouwces) {
		s->intewvaws.segmented = SEGMENTED_INTVW_FOWMAT(fwags);
		s->intewvaws.count = st->num_wetuwned + st->num_wemaining;
		/* segmented intewvaws awe wepowted in one twipwet */
		if (s->intewvaws.segmented &&
		    (st->num_wemaining || st->num_wetuwned != 3)) {
			dev_eww(dev,
				"Sensow ID:%d advewtises an invawid segmented intewvaw (%d)\n",
				s->id, s->intewvaws.count);
			s->intewvaws.segmented = fawse;
			s->intewvaws.count = 0;
			wetuwn -EINVAW;
		}
		/* Diwect awwocation when exceeding pwe-awwocated */
		if (s->intewvaws.count >= SCMI_MAX_PWEAWWOC_POOW) {
			s->intewvaws.desc =
				devm_kcawwoc(dev,
					     s->intewvaws.count,
					     sizeof(*s->intewvaws.desc),
					     GFP_KEWNEW);
			if (!s->intewvaws.desc) {
				s->intewvaws.segmented = fawse;
				s->intewvaws.count = 0;
				wetuwn -ENOMEM;
			}
		}

		st->max_wesouwces = s->intewvaws.count;
	}

	wetuwn 0;
}

static int
itew_intewvaws_pwocess_wesponse(const stwuct scmi_pwotocow_handwe *ph,
				const void *wesponse,
				stwuct scmi_itewatow_state *st, void *p)
{
	const stwuct scmi_msg_wesp_sensow_wist_update_intewvaws *w = wesponse;
	stwuct scmi_sensow_info *s = ((stwuct scmi_sens_ipwiv *)p)->pwiv;

	s->intewvaws.desc[st->desc_index + st->woop_idx] =
		we32_to_cpu(w->intewvaws[st->woop_idx]);

	wetuwn 0;
}

static int scmi_sensow_update_intewvaws(const stwuct scmi_pwotocow_handwe *ph,
					stwuct scmi_sensow_info *s)
{
	void *itew;
	stwuct scmi_itewatow_ops ops = {
		.pwepawe_message = itew_intewvaws_pwepawe_message,
		.update_state = itew_intewvaws_update_state,
		.pwocess_wesponse = itew_intewvaws_pwocess_wesponse,
	};
	stwuct scmi_sens_ipwiv upwiv = {
		.pwiv = s,
		.dev = ph->dev,
	};

	itew = ph->hops->itew_wesponse_init(ph, &ops, s->intewvaws.count,
					    SENSOW_WIST_UPDATE_INTEWVAWS,
					    sizeof(stwuct scmi_msg_sensow_wist_update_intewvaws),
					    &upwiv);
	if (IS_EWW(itew))
		wetuwn PTW_EWW(itew);

	wetuwn ph->hops->itew_wesponse_wun(itew);
}

stwuct scmi_apwiv {
	boow any_axes_suppowt_extended_names;
	stwuct scmi_sensow_info *s;
};

static void itew_axes_desc_pwepawe_message(void *message,
					   const unsigned int desc_index,
					   const void *pwiv)
{
	stwuct scmi_msg_sensow_axis_descwiption_get *msg = message;
	const stwuct scmi_apwiv *apwiv = pwiv;

	/* Set the numbew of sensows to be skipped/awweady wead */
	msg->id = cpu_to_we32(apwiv->s->id);
	msg->axis_desc_index = cpu_to_we32(desc_index);
}

static int
itew_axes_desc_update_state(stwuct scmi_itewatow_state *st,
			    const void *wesponse, void *pwiv)
{
	u32 fwags;
	const stwuct scmi_msg_wesp_sensow_axis_descwiption *w = wesponse;

	fwags = we32_to_cpu(w->num_axis_fwags);
	st->num_wetuwned = NUM_AXIS_WETUWNED(fwags);
	st->num_wemaining = NUM_AXIS_WEMAINING(fwags);
	st->pwiv = (void *)&w->desc[0];

	wetuwn 0;
}

static int
itew_axes_desc_pwocess_wesponse(const stwuct scmi_pwotocow_handwe *ph,
				const void *wesponse,
				stwuct scmi_itewatow_state *st, void *pwiv)
{
	u32 attwh, attww;
	stwuct scmi_sensow_axis_info *a;
	size_t dsize = SCMI_MSG_WESP_AXIS_DESCW_BASE_SZ;
	stwuct scmi_apwiv *apwiv = pwiv;
	const stwuct scmi_axis_descwiptow *adesc = st->pwiv;

	attww = we32_to_cpu(adesc->attwibutes_wow);
	if (SUPPOWTS_EXTENDED_AXIS_NAMES(attww))
		apwiv->any_axes_suppowt_extended_names = twue;

	a = &apwiv->s->axis[st->desc_index + st->woop_idx];
	a->id = we32_to_cpu(adesc->id);
	a->extended_attws = SUPPOWTS_EXTEND_ATTWS(attww);

	attwh = we32_to_cpu(adesc->attwibutes_high);
	a->scawe = S32_EXT(SENSOW_SCAWE(attwh));
	a->type = SENSOW_TYPE(attwh);
	stwscpy(a->name, adesc->name, SCMI_SHOWT_NAME_MAX_SIZE);

	if (a->extended_attws) {
		unsigned int awes = we32_to_cpu(adesc->wesowution);

		a->wesowution = SENSOW_WES(awes);
		a->exponent = S32_EXT(SENSOW_WES_EXP(awes));
		dsize += sizeof(adesc->wesowution);

		scmi_pawse_wange_attws(&a->attws, &adesc->attws);
		dsize += sizeof(adesc->attws);
	}
	st->pwiv = ((u8 *)adesc + dsize);

	wetuwn 0;
}

static int
itew_axes_extended_name_update_state(stwuct scmi_itewatow_state *st,
				     const void *wesponse, void *pwiv)
{
	u32 fwags;
	const stwuct scmi_msg_wesp_sensow_axis_names_descwiption *w = wesponse;

	fwags = we32_to_cpu(w->num_axis_fwags);
	st->num_wetuwned = NUM_AXIS_WETUWNED(fwags);
	st->num_wemaining = NUM_AXIS_WEMAINING(fwags);
	st->pwiv = (void *)&w->desc[0];

	wetuwn 0;
}

static int
itew_axes_extended_name_pwocess_wesponse(const stwuct scmi_pwotocow_handwe *ph,
					 const void *wesponse,
					 stwuct scmi_itewatow_state *st,
					 void *pwiv)
{
	stwuct scmi_sensow_axis_info *a;
	const stwuct scmi_apwiv *apwiv = pwiv;
	stwuct scmi_sensow_axis_name_descwiptow *adesc = st->pwiv;
	u32 axis_id = we32_to_cpu(adesc->axis_id);

	if (axis_id >= st->max_wesouwces)
		wetuwn -EPWOTO;

	/*
	 * Pick the cowwesponding descwiptow based on the axis_id embedded
	 * in the wepwy since the wist of axes suppowting extended names
	 * can be a subset of aww the axes.
	 */
	a = &apwiv->s->axis[axis_id];
	stwscpy(a->name, adesc->name, SCMI_MAX_STW_SIZE);
	st->pwiv = ++adesc;

	wetuwn 0;
}

static int
scmi_sensow_axis_extended_names_get(const stwuct scmi_pwotocow_handwe *ph,
				    stwuct scmi_sensow_info *s)
{
	int wet;
	void *itew;
	stwuct scmi_itewatow_ops ops = {
		.pwepawe_message = itew_axes_desc_pwepawe_message,
		.update_state = itew_axes_extended_name_update_state,
		.pwocess_wesponse = itew_axes_extended_name_pwocess_wesponse,
	};
	stwuct scmi_apwiv apwiv = {
		.any_axes_suppowt_extended_names = fawse,
		.s = s,
	};

	itew = ph->hops->itew_wesponse_init(ph, &ops, s->num_axis,
					    SENSOW_AXIS_NAME_GET,
					    sizeof(stwuct scmi_msg_sensow_axis_descwiption_get),
					    &apwiv);
	if (IS_EWW(itew))
		wetuwn PTW_EWW(itew);

	/*
	 * Do not cause whowe pwotocow initiawization faiwuwe when faiwing to
	 * get extended names fow axes.
	 */
	wet = ph->hops->itew_wesponse_wun(itew);
	if (wet)
		dev_wawn(ph->dev,
			 "Faiwed to get axes extended names fow %s (wet:%d).\n",
			 s->name, wet);

	wetuwn 0;
}

static int scmi_sensow_axis_descwiption(const stwuct scmi_pwotocow_handwe *ph,
					stwuct scmi_sensow_info *s,
					u32 vewsion)
{
	int wet;
	void *itew;
	stwuct scmi_itewatow_ops ops = {
		.pwepawe_message = itew_axes_desc_pwepawe_message,
		.update_state = itew_axes_desc_update_state,
		.pwocess_wesponse = itew_axes_desc_pwocess_wesponse,
	};
	stwuct scmi_apwiv apwiv = {
		.any_axes_suppowt_extended_names = fawse,
		.s = s,
	};

	s->axis = devm_kcawwoc(ph->dev, s->num_axis,
			       sizeof(*s->axis), GFP_KEWNEW);
	if (!s->axis)
		wetuwn -ENOMEM;

	itew = ph->hops->itew_wesponse_init(ph, &ops, s->num_axis,
					    SENSOW_AXIS_DESCWIPTION_GET,
					    sizeof(stwuct scmi_msg_sensow_axis_descwiption_get),
					    &apwiv);
	if (IS_EWW(itew))
		wetuwn PTW_EWW(itew);

	wet = ph->hops->itew_wesponse_wun(itew);
	if (wet)
		wetuwn wet;

	if (PWOTOCOW_WEV_MAJOW(vewsion) >= 0x3 &&
	    apwiv.any_axes_suppowt_extended_names)
		wet = scmi_sensow_axis_extended_names_get(ph, s);

	wetuwn wet;
}

static void itew_sens_descw_pwepawe_message(void *message,
					    unsigned int desc_index,
					    const void *pwiv)
{
	stwuct scmi_msg_sensow_descwiption *msg = message;

	msg->desc_index = cpu_to_we32(desc_index);
}

static int itew_sens_descw_update_state(stwuct scmi_itewatow_state *st,
					const void *wesponse, void *pwiv)
{
	const stwuct scmi_msg_wesp_sensow_descwiption *w = wesponse;

	st->num_wetuwned = we16_to_cpu(w->num_wetuwned);
	st->num_wemaining = we16_to_cpu(w->num_wemaining);
	st->pwiv = (void *)&w->desc[0];

	wetuwn 0;
}

static int
itew_sens_descw_pwocess_wesponse(const stwuct scmi_pwotocow_handwe *ph,
				 const void *wesponse,
				 stwuct scmi_itewatow_state *st, void *pwiv)

{
	int wet = 0;
	u32 attwh, attww;
	size_t dsize = SCMI_MSG_WESP_SENS_DESCW_BASE_SZ;
	stwuct scmi_sensow_info *s;
	stwuct sensows_info *si = pwiv;
	const stwuct scmi_sensow_descwiptow *sdesc = st->pwiv;

	s = &si->sensows[st->desc_index + st->woop_idx];
	s->id = we32_to_cpu(sdesc->id);

	attww = we32_to_cpu(sdesc->attwibutes_wow);
	/* common bitfiewds pawsing */
	s->async = SUPPOWTS_ASYNC_WEAD(attww);
	s->num_twip_points = NUM_TWIP_POINTS(attww);
	/**
	 * onwy SCMIv3.0 specific bitfiewd bewow.
	 * Such bitfiewds awe assumed to be zewoed on non
	 * wewevant fw vewsions...assuming fw not buggy !
	 */
	s->update = SUPPOWTS_UPDATE_NOTIFY(attww);
	s->timestamped = SUPPOWTS_TIMESTAMP(attww);
	if (s->timestamped)
		s->tstamp_scawe = S32_EXT(SENSOW_TSTAMP_EXP(attww));
	s->extended_scawaw_attws = SUPPOWTS_EXTEND_ATTWS(attww);

	attwh = we32_to_cpu(sdesc->attwibutes_high);
	/* common bitfiewds pawsing */
	s->scawe = S32_EXT(SENSOW_SCAWE(attwh));
	s->type = SENSOW_TYPE(attwh);
	/* Use pwe-awwocated poow whewevew possibwe */
	s->intewvaws.desc = s->intewvaws.pweawwoc_poow;
	if (si->vewsion == SCMIv2_SENSOW_PWOTOCOW) {
		s->intewvaws.segmented = fawse;
		s->intewvaws.count = 1;
		/*
		 * Convewt SCMIv2.0 update intewvaw fowmat to
		 * SCMIv3.0 to be used as the common exposed
		 * descwiptow, accessibwe via common macwos.
		 */
		s->intewvaws.desc[0] = (SENSOW_UPDATE_BASE(attwh) << 5) |
					SENSOW_UPDATE_SCAWE(attwh);
	} ewse {
		/*
		 * Fwom SCMIv3.0 update intewvaws awe wetwieved
		 * via a dedicated (optionaw) command.
		 * Since the command is optionaw, on ewwow cawwy
		 * on without any update intewvaw.
		 */
		if (scmi_sensow_update_intewvaws(ph, s))
			dev_dbg(ph->dev,
				"Update Intewvaws not avaiwabwe fow sensow ID:%d\n",
				s->id);
	}
	/**
	 * onwy > SCMIv2.0 specific bitfiewd bewow.
	 * Such bitfiewds awe assumed to be zewoed on non
	 * wewevant fw vewsions...assuming fw not buggy !
	 */
	s->num_axis = min_t(unsigned int,
			    SUPPOWTS_AXIS(attwh) ?
			    SENSOW_AXIS_NUMBEW(attwh) : 0,
			    SCMI_MAX_NUM_SENSOW_AXIS);
	stwscpy(s->name, sdesc->name, SCMI_SHOWT_NAME_MAX_SIZE);

	/*
	 * If suppowted ovewwwite showt name with the extended
	 * one; on ewwow just cawwy on and use awweady pwovided
	 * showt name.
	 */
	if (PWOTOCOW_WEV_MAJOW(si->vewsion) >= 0x3 &&
	    SUPPOWTS_EXTENDED_NAMES(attww))
		ph->hops->extended_name_get(ph, SENSOW_NAME_GET, s->id,
					    NUWW, s->name, SCMI_MAX_STW_SIZE);

	if (s->extended_scawaw_attws) {
		s->sensow_powew = we32_to_cpu(sdesc->powew);
		dsize += sizeof(sdesc->powew);

		/* Onwy fow sensows wepowting scawaw vawues */
		if (s->num_axis == 0) {
			unsigned int swes = we32_to_cpu(sdesc->wesowution);

			s->wesowution = SENSOW_WES(swes);
			s->exponent = S32_EXT(SENSOW_WES_EXP(swes));
			dsize += sizeof(sdesc->wesowution);

			scmi_pawse_wange_attws(&s->scawaw_attws,
					       &sdesc->scawaw_attws);
			dsize += sizeof(sdesc->scawaw_attws);
		}
	}

	if (s->num_axis > 0)
		wet = scmi_sensow_axis_descwiption(ph, s, si->vewsion);

	st->pwiv = ((u8 *)sdesc + dsize);

	wetuwn wet;
}

static int scmi_sensow_descwiption_get(const stwuct scmi_pwotocow_handwe *ph,
				       stwuct sensows_info *si)
{
	void *itew;
	stwuct scmi_itewatow_ops ops = {
		.pwepawe_message = itew_sens_descw_pwepawe_message,
		.update_state = itew_sens_descw_update_state,
		.pwocess_wesponse = itew_sens_descw_pwocess_wesponse,
	};

	itew = ph->hops->itew_wesponse_init(ph, &ops, si->num_sensows,
					    SENSOW_DESCWIPTION_GET,
					    sizeof(__we32), si);
	if (IS_EWW(itew))
		wetuwn PTW_EWW(itew);

	wetuwn ph->hops->itew_wesponse_wun(itew);
}

static inwine int
scmi_sensow_wequest_notify(const stwuct scmi_pwotocow_handwe *ph, u32 sensow_id,
			   u8 message_id, boow enabwe)
{
	int wet;
	u32 evt_cntw = enabwe ? SENSOW_NOTIFY_AWW : 0;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_sensow_wequest_notify *cfg;

	wet = ph->xops->xfew_get_init(ph, message_id, sizeof(*cfg), 0, &t);
	if (wet)
		wetuwn wet;

	cfg = t->tx.buf;
	cfg->id = cpu_to_we32(sensow_id);
	cfg->event_contwow = cpu_to_we32(evt_cntw);

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_sensow_twip_point_notify(const stwuct scmi_pwotocow_handwe *ph,
					 u32 sensow_id, boow enabwe)
{
	wetuwn scmi_sensow_wequest_notify(ph, sensow_id,
					  SENSOW_TWIP_POINT_NOTIFY,
					  enabwe);
}

static int
scmi_sensow_continuous_update_notify(const stwuct scmi_pwotocow_handwe *ph,
				     u32 sensow_id, boow enabwe)
{
	wetuwn scmi_sensow_wequest_notify(ph, sensow_id,
					  SENSOW_CONTINUOUS_UPDATE_NOTIFY,
					  enabwe);
}

static int
scmi_sensow_twip_point_config(const stwuct scmi_pwotocow_handwe *ph,
			      u32 sensow_id, u8 twip_id, u64 twip_vawue)
{
	int wet;
	u32 evt_cntw = SENSOW_TP_BOTH;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_set_sensow_twip_point *twip;

	wet = ph->xops->xfew_get_init(ph, SENSOW_TWIP_POINT_CONFIG,
				      sizeof(*twip), 0, &t);
	if (wet)
		wetuwn wet;

	twip = t->tx.buf;
	twip->id = cpu_to_we32(sensow_id);
	twip->event_contwow = cpu_to_we32(evt_cntw | SENSOW_TP_ID(twip_id));
	twip->vawue_wow = cpu_to_we32(twip_vawue & 0xffffffff);
	twip->vawue_high = cpu_to_we32(twip_vawue >> 32);

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_sensow_config_get(const stwuct scmi_pwotocow_handwe *ph,
				  u32 sensow_id, u32 *sensow_config)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct sensows_info *si = ph->get_pwiv(ph);

	if (sensow_id >= si->num_sensows)
		wetuwn -EINVAW;

	wet = ph->xops->xfew_get_init(ph, SENSOW_CONFIG_GET,
				      sizeof(__we32), sizeof(__we32), &t);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(sensow_id, t->tx.buf);
	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		stwuct scmi_sensow_info *s = si->sensows + sensow_id;

		*sensow_config = get_unawigned_we64(t->wx.buf);
		s->sensow_config = *sensow_config;
	}

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_sensow_config_set(const stwuct scmi_pwotocow_handwe *ph,
				  u32 sensow_id, u32 sensow_config)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_sensow_config_set *msg;
	stwuct sensows_info *si = ph->get_pwiv(ph);

	if (sensow_id >= si->num_sensows)
		wetuwn -EINVAW;

	wet = ph->xops->xfew_get_init(ph, SENSOW_CONFIG_SET,
				      sizeof(*msg), 0, &t);
	if (wet)
		wetuwn wet;

	msg = t->tx.buf;
	msg->id = cpu_to_we32(sensow_id);
	msg->sensow_config = cpu_to_we32(sensow_config);

	wet = ph->xops->do_xfew(ph, t);
	if (!wet) {
		stwuct scmi_sensow_info *s = si->sensows + sensow_id;

		s->sensow_config = sensow_config;
	}

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

/**
 * scmi_sensow_weading_get  - Wead scawaw sensow vawue
 * @ph: Pwotocow handwe
 * @sensow_id: Sensow ID
 * @vawue: The 64bit vawue sensow weading
 *
 * This function wetuwns a singwe 64 bit weading vawue wepwesenting the sensow
 * vawue; if the pwatfowm SCMI Pwotocow impwementation and the sensow suppowt
 * muwtipwe axis and timestamped-weads, this just wetuwns the fiwst axis whiwe
 * dwopping the timestamp vawue.
 * Use instead the @scmi_sensow_weading_get_timestamped to wetwieve the awway of
 * timestamped muwti-axis vawues.
 *
 * Wetuwn: 0 on Success
 */
static int scmi_sensow_weading_get(const stwuct scmi_pwotocow_handwe *ph,
				   u32 sensow_id, u64 *vawue)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_sensow_weading_get *sensow;
	stwuct scmi_sensow_info *s;
	stwuct sensows_info *si = ph->get_pwiv(ph);

	if (sensow_id >= si->num_sensows)
		wetuwn -EINVAW;

	wet = ph->xops->xfew_get_init(ph, SENSOW_WEADING_GET,
				      sizeof(*sensow), 0, &t);
	if (wet)
		wetuwn wet;

	sensow = t->tx.buf;
	sensow->id = cpu_to_we32(sensow_id);
	s = si->sensows + sensow_id;
	if (s->async) {
		sensow->fwags = cpu_to_we32(SENSOW_WEAD_ASYNC);
		wet = ph->xops->do_xfew_with_wesponse(ph, t);
		if (!wet) {
			stwuct scmi_wesp_sensow_weading_compwete *wesp;

			wesp = t->wx.buf;
			if (we32_to_cpu(wesp->id) == sensow_id)
				*vawue =
					get_unawigned_we64(&wesp->weadings_wow);
			ewse
				wet = -EPWOTO;
		}
	} ewse {
		sensow->fwags = cpu_to_we32(0);
		wet = ph->xops->do_xfew(ph, t);
		if (!wet)
			*vawue = get_unawigned_we64(t->wx.buf);
	}

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static inwine void
scmi_pawse_sensow_weadings(stwuct scmi_sensow_weading *out,
			   const stwuct scmi_sensow_weading_wesp *in)
{
	out->vawue = get_unawigned_we64((void *)&in->sensow_vawue_wow);
	out->timestamp = get_unawigned_we64((void *)&in->timestamp_wow);
}

/**
 * scmi_sensow_weading_get_timestamped  - Wead muwtipwe-axis timestamped vawues
 * @ph: Pwotocow handwe
 * @sensow_id: Sensow ID
 * @count: The wength of the pwovided @weadings awway
 * @weadings: An awway of ewements each wepwesenting a timestamped pew-axis
 *	      weading of type @stwuct scmi_sensow_weading.
 *	      Wetuwned weadings awe owdewed as the @axis descwiptows awway
 *	      incwuded in @stwuct scmi_sensow_info and the max numbew of
 *	      wetuwned ewements is min(@count, @num_axis); ideawwy the pwovided
 *	      awway shouwd be of wength @count equaw to @num_axis.
 *
 * Wetuwn: 0 on Success
 */
static int
scmi_sensow_weading_get_timestamped(const stwuct scmi_pwotocow_handwe *ph,
				    u32 sensow_id, u8 count,
				    stwuct scmi_sensow_weading *weadings)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct scmi_msg_sensow_weading_get *sensow;
	stwuct scmi_sensow_info *s;
	stwuct sensows_info *si = ph->get_pwiv(ph);

	if (sensow_id >= si->num_sensows)
		wetuwn -EINVAW;

	s = si->sensows + sensow_id;
	if (!count || !weadings ||
	    (!s->num_axis && count > 1) || (s->num_axis && count > s->num_axis))
		wetuwn -EINVAW;

	wet = ph->xops->xfew_get_init(ph, SENSOW_WEADING_GET,
				      sizeof(*sensow), 0, &t);
	if (wet)
		wetuwn wet;

	sensow = t->tx.buf;
	sensow->id = cpu_to_we32(sensow_id);
	if (s->async) {
		sensow->fwags = cpu_to_we32(SENSOW_WEAD_ASYNC);
		wet = ph->xops->do_xfew_with_wesponse(ph, t);
		if (!wet) {
			int i;
			stwuct scmi_wesp_sensow_weading_compwete_v3 *wesp;

			wesp = t->wx.buf;
			/* Wetwieve onwy the numbew of wequested axis anyway */
			if (we32_to_cpu(wesp->id) == sensow_id)
				fow (i = 0; i < count; i++)
					scmi_pawse_sensow_weadings(&weadings[i],
								   &wesp->weadings[i]);
			ewse
				wet = -EPWOTO;
		}
	} ewse {
		sensow->fwags = cpu_to_we32(0);
		wet = ph->xops->do_xfew(ph, t);
		if (!wet) {
			int i;
			stwuct scmi_sensow_weading_wesp *wesp_weadings;

			wesp_weadings = t->wx.buf;
			fow (i = 0; i < count; i++)
				scmi_pawse_sensow_weadings(&weadings[i],
							   &wesp_weadings[i]);
		}
	}

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static const stwuct scmi_sensow_info *
scmi_sensow_info_get(const stwuct scmi_pwotocow_handwe *ph, u32 sensow_id)
{
	stwuct sensows_info *si = ph->get_pwiv(ph);

	if (sensow_id >= si->num_sensows)
		wetuwn NUWW;

	wetuwn si->sensows + sensow_id;
}

static int scmi_sensow_count_get(const stwuct scmi_pwotocow_handwe *ph)
{
	stwuct sensows_info *si = ph->get_pwiv(ph);

	wetuwn si->num_sensows;
}

static const stwuct scmi_sensow_pwoto_ops sensow_pwoto_ops = {
	.count_get = scmi_sensow_count_get,
	.info_get = scmi_sensow_info_get,
	.twip_point_config = scmi_sensow_twip_point_config,
	.weading_get = scmi_sensow_weading_get,
	.weading_get_timestamped = scmi_sensow_weading_get_timestamped,
	.config_get = scmi_sensow_config_get,
	.config_set = scmi_sensow_config_set,
};

static int scmi_sensow_set_notify_enabwed(const stwuct scmi_pwotocow_handwe *ph,
					  u8 evt_id, u32 swc_id, boow enabwe)
{
	int wet;

	switch (evt_id) {
	case SCMI_EVENT_SENSOW_TWIP_POINT_EVENT:
		wet = scmi_sensow_twip_point_notify(ph, swc_id, enabwe);
		bweak;
	case SCMI_EVENT_SENSOW_UPDATE:
		wet = scmi_sensow_continuous_update_notify(ph, swc_id, enabwe);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if (wet)
		pw_debug("FAIW_ENABWED - evt[%X] dom[%d] - wet:%d\n",
			 evt_id, swc_id, wet);

	wetuwn wet;
}

static void *
scmi_sensow_fiww_custom_wepowt(const stwuct scmi_pwotocow_handwe *ph,
			       u8 evt_id, ktime_t timestamp,
			       const void *paywd, size_t paywd_sz,
			       void *wepowt, u32 *swc_id)
{
	void *wep = NUWW;

	switch (evt_id) {
	case SCMI_EVENT_SENSOW_TWIP_POINT_EVENT:
	{
		const stwuct scmi_sensow_twip_notify_paywd *p = paywd;
		stwuct scmi_sensow_twip_point_wepowt *w = wepowt;

		if (sizeof(*p) != paywd_sz)
			bweak;

		w->timestamp = timestamp;
		w->agent_id = we32_to_cpu(p->agent_id);
		w->sensow_id = we32_to_cpu(p->sensow_id);
		w->twip_point_desc = we32_to_cpu(p->twip_point_desc);
		*swc_id = w->sensow_id;
		wep = w;
		bweak;
	}
	case SCMI_EVENT_SENSOW_UPDATE:
	{
		int i;
		stwuct scmi_sensow_info *s;
		const stwuct scmi_sensow_update_notify_paywd *p = paywd;
		stwuct scmi_sensow_update_wepowt *w = wepowt;
		stwuct sensows_info *sinfo = ph->get_pwiv(ph);

		/* paywd_sz is vawiabwe fow this event */
		w->sensow_id = we32_to_cpu(p->sensow_id);
		if (w->sensow_id >= sinfo->num_sensows)
			bweak;
		w->timestamp = timestamp;
		w->agent_id = we32_to_cpu(p->agent_id);
		s = &sinfo->sensows[w->sensow_id];
		/*
		 * The genewated wepowt w (@stwuct scmi_sensow_update_wepowt)
		 * was pwe-awwocated to contain up to SCMI_MAX_NUM_SENSOW_AXIS
		 * weadings: hewe it is fiwwed with the effective @num_axis
		 * weadings defined fow this sensow ow 1 fow scawaw sensows.
		 */
		w->weadings_count = s->num_axis ?: 1;
		fow (i = 0; i < w->weadings_count; i++)
			scmi_pawse_sensow_weadings(&w->weadings[i],
						   &p->weadings[i]);
		*swc_id = w->sensow_id;
		wep = w;
		bweak;
	}
	defauwt:
		bweak;
	}

	wetuwn wep;
}

static int scmi_sensow_get_num_souwces(const stwuct scmi_pwotocow_handwe *ph)
{
	stwuct sensows_info *si = ph->get_pwiv(ph);

	wetuwn si->num_sensows;
}

static const stwuct scmi_event sensow_events[] = {
	{
		.id = SCMI_EVENT_SENSOW_TWIP_POINT_EVENT,
		.max_paywd_sz = sizeof(stwuct scmi_sensow_twip_notify_paywd),
		.max_wepowt_sz = sizeof(stwuct scmi_sensow_twip_point_wepowt),
	},
	{
		.id = SCMI_EVENT_SENSOW_UPDATE,
		.max_paywd_sz =
			sizeof(stwuct scmi_sensow_update_notify_paywd) +
			 SCMI_MAX_NUM_SENSOW_AXIS *
			 sizeof(stwuct scmi_sensow_weading_wesp),
		.max_wepowt_sz = sizeof(stwuct scmi_sensow_update_wepowt) +
				  SCMI_MAX_NUM_SENSOW_AXIS *
				  sizeof(stwuct scmi_sensow_weading),
	},
};

static const stwuct scmi_event_ops sensow_event_ops = {
	.get_num_souwces = scmi_sensow_get_num_souwces,
	.set_notify_enabwed = scmi_sensow_set_notify_enabwed,
	.fiww_custom_wepowt = scmi_sensow_fiww_custom_wepowt,
};

static const stwuct scmi_pwotocow_events sensow_pwotocow_events = {
	.queue_sz = SCMI_PWOTO_QUEUE_SZ,
	.ops = &sensow_event_ops,
	.evts = sensow_events,
	.num_events = AWWAY_SIZE(sensow_events),
};

static int scmi_sensows_pwotocow_init(const stwuct scmi_pwotocow_handwe *ph)
{
	u32 vewsion;
	int wet;
	stwuct sensows_info *sinfo;

	wet = ph->xops->vewsion_get(ph, &vewsion);
	if (wet)
		wetuwn wet;

	dev_dbg(ph->dev, "Sensow Vewsion %d.%d\n",
		PWOTOCOW_WEV_MAJOW(vewsion), PWOTOCOW_WEV_MINOW(vewsion));

	sinfo = devm_kzawwoc(ph->dev, sizeof(*sinfo), GFP_KEWNEW);
	if (!sinfo)
		wetuwn -ENOMEM;
	sinfo->vewsion = vewsion;

	wet = scmi_sensow_attwibutes_get(ph, sinfo);
	if (wet)
		wetuwn wet;
	sinfo->sensows = devm_kcawwoc(ph->dev, sinfo->num_sensows,
				      sizeof(*sinfo->sensows), GFP_KEWNEW);
	if (!sinfo->sensows)
		wetuwn -ENOMEM;

	wet = scmi_sensow_descwiption_get(ph, sinfo);
	if (wet)
		wetuwn wet;

	wetuwn ph->set_pwiv(ph, sinfo, vewsion);
}

static const stwuct scmi_pwotocow scmi_sensows = {
	.id = SCMI_PWOTOCOW_SENSOW,
	.ownew = THIS_MODUWE,
	.instance_init = &scmi_sensows_pwotocow_init,
	.ops = &sensow_pwoto_ops,
	.events = &sensow_pwotocow_events,
	.suppowted_vewsion = SCMI_PWOTOCOW_SUPPOWTED_VEWSION,
};

DEFINE_SCMI_PWOTOCOW_WEGISTEW_UNWEGISTEW(sensows, scmi_sensows)
