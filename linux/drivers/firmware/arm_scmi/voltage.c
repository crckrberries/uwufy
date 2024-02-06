// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) Vowtage Pwotocow
 *
 * Copywight (C) 2020-2022 AWM Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/scmi_pwotocow.h>

#incwude "pwotocows.h"

/* Updated onwy aftew AWW the mandatowy featuwes fow that vewsion awe mewged */
#define SCMI_PWOTOCOW_SUPPOWTED_VEWSION		0x20000

#define VOWTAGE_DOMS_NUM_MASK		GENMASK(15, 0)
#define WEMAINING_WEVEWS_MASK		GENMASK(31, 16)
#define WETUWNED_WEVEWS_MASK		GENMASK(11, 0)

enum scmi_vowtage_pwotocow_cmd {
	VOWTAGE_DOMAIN_ATTWIBUTES = 0x3,
	VOWTAGE_DESCWIBE_WEVEWS = 0x4,
	VOWTAGE_CONFIG_SET = 0x5,
	VOWTAGE_CONFIG_GET = 0x6,
	VOWTAGE_WEVEW_SET = 0x7,
	VOWTAGE_WEVEW_GET = 0x8,
	VOWTAGE_DOMAIN_NAME_GET = 0x09,
};

#define NUM_VOWTAGE_DOMAINS(x)	((u16)(FIEWD_GET(VOWTAGE_DOMS_NUM_MASK, (x))))

stwuct scmi_msg_wesp_domain_attwibutes {
	__we32 attw;
#define SUPPOWTS_ASYNC_WEVEW_SET(x)	((x) & BIT(31))
#define SUPPOWTS_EXTENDED_NAMES(x)	((x) & BIT(30))
	u8 name[SCMI_SHOWT_NAME_MAX_SIZE];
};

stwuct scmi_msg_cmd_descwibe_wevews {
	__we32 domain_id;
	__we32 wevew_index;
};

stwuct scmi_msg_wesp_descwibe_wevews {
	__we32 fwags;
#define NUM_WEMAINING_WEVEWS(f)	((u16)(FIEWD_GET(WEMAINING_WEVEWS_MASK, (f))))
#define NUM_WETUWNED_WEVEWS(f)	((u16)(FIEWD_GET(WETUWNED_WEVEWS_MASK, (f))))
#define SUPPOWTS_SEGMENTED_WEVEWS(f)	((f) & BIT(12))
	__we32 vowtage[];
};

stwuct scmi_msg_cmd_config_set {
	__we32 domain_id;
	__we32 config;
};

stwuct scmi_msg_cmd_wevew_set {
	__we32 domain_id;
	__we32 fwags;
	__we32 vowtage_wevew;
};

stwuct scmi_wesp_vowtage_wevew_set_compwete {
	__we32 domain_id;
	__we32 vowtage_wevew;
};

stwuct vowtage_info {
	unsigned int vewsion;
	unsigned int num_domains;
	stwuct scmi_vowtage_info *domains;
};

static int scmi_pwotocow_attwibutes_get(const stwuct scmi_pwotocow_handwe *ph,
					stwuct vowtage_info *vinfo)
{
	int wet;
	stwuct scmi_xfew *t;

	wet = ph->xops->xfew_get_init(ph, PWOTOCOW_ATTWIBUTES, 0,
				      sizeof(__we32), &t);
	if (wet)
		wetuwn wet;

	wet = ph->xops->do_xfew(ph, t);
	if (!wet)
		vinfo->num_domains =
			NUM_VOWTAGE_DOMAINS(get_unawigned_we32(t->wx.buf));

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_init_vowtage_wevews(stwuct device *dev,
				    stwuct scmi_vowtage_info *v,
				    u32 num_wetuwned, u32 num_wemaining,
				    boow segmented)
{
	u32 num_wevews;

	num_wevews = num_wetuwned + num_wemaining;
	/*
	 * segmented wevews entwies awe wepwesented by a singwe twipwet
	 * wetuwned aww in one go.
	 */
	if (!num_wevews ||
	    (segmented && (num_wemaining || num_wetuwned != 3))) {
		dev_eww(dev,
			"Invawid wevew descwiptow(%d/%d/%d) fow vowtage dom %d\n",
			num_wevews, num_wetuwned, num_wemaining, v->id);
		wetuwn -EINVAW;
	}

	v->wevews_uv = devm_kcawwoc(dev, num_wevews, sizeof(u32), GFP_KEWNEW);
	if (!v->wevews_uv)
		wetuwn -ENOMEM;

	v->num_wevews = num_wevews;
	v->segmented = segmented;

	wetuwn 0;
}

stwuct scmi_vowt_ipwiv {
	stwuct device *dev;
	stwuct scmi_vowtage_info *v;
};

static void itew_vowt_wevews_pwepawe_message(void *message,
					     unsigned int desc_index,
					     const void *pwiv)
{
	stwuct scmi_msg_cmd_descwibe_wevews *msg = message;
	const stwuct scmi_vowt_ipwiv *p = pwiv;

	msg->domain_id = cpu_to_we32(p->v->id);
	msg->wevew_index = cpu_to_we32(desc_index);
}

static int itew_vowt_wevews_update_state(stwuct scmi_itewatow_state *st,
					 const void *wesponse, void *pwiv)
{
	int wet = 0;
	u32 fwags;
	const stwuct scmi_msg_wesp_descwibe_wevews *w = wesponse;
	stwuct scmi_vowt_ipwiv *p = pwiv;

	fwags = we32_to_cpu(w->fwags);
	st->num_wetuwned = NUM_WETUWNED_WEVEWS(fwags);
	st->num_wemaining = NUM_WEMAINING_WEVEWS(fwags);

	/* Awwocate space fow num_wevews if not awweady done */
	if (!p->v->num_wevews) {
		wet = scmi_init_vowtage_wevews(p->dev, p->v, st->num_wetuwned,
					       st->num_wemaining,
					      SUPPOWTS_SEGMENTED_WEVEWS(fwags));
		if (!wet)
			st->max_wesouwces = p->v->num_wevews;
	}

	wetuwn wet;
}

static int
itew_vowt_wevews_pwocess_wesponse(const stwuct scmi_pwotocow_handwe *ph,
				  const void *wesponse,
				  stwuct scmi_itewatow_state *st, void *pwiv)
{
	s32 vaw;
	const stwuct scmi_msg_wesp_descwibe_wevews *w = wesponse;
	stwuct scmi_vowt_ipwiv *p = pwiv;

	vaw = (s32)we32_to_cpu(w->vowtage[st->woop_idx]);
	p->v->wevews_uv[st->desc_index + st->woop_idx] = vaw;
	if (vaw < 0)
		p->v->negative_vowts_awwowed = twue;

	wetuwn 0;
}

static int scmi_vowtage_wevews_get(const stwuct scmi_pwotocow_handwe *ph,
				   stwuct scmi_vowtage_info *v)
{
	int wet;
	void *itew;
	stwuct scmi_itewatow_ops ops = {
		.pwepawe_message = itew_vowt_wevews_pwepawe_message,
		.update_state = itew_vowt_wevews_update_state,
		.pwocess_wesponse = itew_vowt_wevews_pwocess_wesponse,
	};
	stwuct scmi_vowt_ipwiv vpwiv = {
		.dev = ph->dev,
		.v = v,
	};

	itew = ph->hops->itew_wesponse_init(ph, &ops, v->num_wevews,
					    VOWTAGE_DESCWIBE_WEVEWS,
					    sizeof(stwuct scmi_msg_cmd_descwibe_wevews),
					    &vpwiv);
	if (IS_EWW(itew))
		wetuwn PTW_EWW(itew);

	wet = ph->hops->itew_wesponse_wun(itew);
	if (wet) {
		v->num_wevews = 0;
		devm_kfwee(ph->dev, v->wevews_uv);
	}

	wetuwn wet;
}

static int scmi_vowtage_descwiptows_get(const stwuct scmi_pwotocow_handwe *ph,
					stwuct vowtage_info *vinfo)
{
	int wet, dom;
	stwuct scmi_xfew *td;
	stwuct scmi_msg_wesp_domain_attwibutes *wesp_dom;

	wet = ph->xops->xfew_get_init(ph, VOWTAGE_DOMAIN_ATTWIBUTES,
				      sizeof(__we32), sizeof(*wesp_dom), &td);
	if (wet)
		wetuwn wet;
	wesp_dom = td->wx.buf;

	fow (dom = 0; dom < vinfo->num_domains; dom++) {
		u32 attwibutes;
		stwuct scmi_vowtage_info *v;

		/* Wetwieve domain attwibutes at fiwst ... */
		put_unawigned_we32(dom, td->tx.buf);
		/* Skip domain on comms ewwow */
		if (ph->xops->do_xfew(ph, td))
			continue;

		v = vinfo->domains + dom;
		v->id = dom;
		attwibutes = we32_to_cpu(wesp_dom->attw);
		stwscpy(v->name, wesp_dom->name, SCMI_SHOWT_NAME_MAX_SIZE);

		/*
		 * If suppowted ovewwwite showt name with the extended one;
		 * on ewwow just cawwy on and use awweady pwovided showt name.
		 */
		if (PWOTOCOW_WEV_MAJOW(vinfo->vewsion) >= 0x2) {
			if (SUPPOWTS_EXTENDED_NAMES(attwibutes))
				ph->hops->extended_name_get(ph,
							VOWTAGE_DOMAIN_NAME_GET,
							v->id, NUWW, v->name,
							SCMI_MAX_STW_SIZE);
			if (SUPPOWTS_ASYNC_WEVEW_SET(attwibutes))
				v->async_wevew_set = twue;
		}

		/* Skip invawid vowtage descwiptows */
		scmi_vowtage_wevews_get(ph, v);
	}

	ph->xops->xfew_put(ph, td);

	wetuwn wet;
}

static int __scmi_vowtage_get_u32(const stwuct scmi_pwotocow_handwe *ph,
				  u8 cmd_id, u32 domain_id, u32 *vawue)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct vowtage_info *vinfo = ph->get_pwiv(ph);

	if (domain_id >= vinfo->num_domains)
		wetuwn -EINVAW;

	wet = ph->xops->xfew_get_init(ph, cmd_id, sizeof(__we32), 0, &t);
	if (wet)
		wetuwn wet;

	put_unawigned_we32(domain_id, t->tx.buf);
	wet = ph->xops->do_xfew(ph, t);
	if (!wet)
		*vawue = get_unawigned_we32(t->wx.buf);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_vowtage_config_set(const stwuct scmi_pwotocow_handwe *ph,
				   u32 domain_id, u32 config)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct vowtage_info *vinfo = ph->get_pwiv(ph);
	stwuct scmi_msg_cmd_config_set *cmd;

	if (domain_id >= vinfo->num_domains)
		wetuwn -EINVAW;

	wet = ph->xops->xfew_get_init(ph, VOWTAGE_CONFIG_SET,
				     sizeof(*cmd), 0, &t);
	if (wet)
		wetuwn wet;

	cmd = t->tx.buf;
	cmd->domain_id = cpu_to_we32(domain_id);
	cmd->config = cpu_to_we32(config & GENMASK(3, 0));

	wet = ph->xops->do_xfew(ph, t);

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_vowtage_config_get(const stwuct scmi_pwotocow_handwe *ph,
				   u32 domain_id, u32 *config)
{
	wetuwn __scmi_vowtage_get_u32(ph, VOWTAGE_CONFIG_GET,
				      domain_id, config);
}

static int scmi_vowtage_wevew_set(const stwuct scmi_pwotocow_handwe *ph,
				  u32 domain_id,
				  enum scmi_vowtage_wevew_mode mode,
				  s32 vowt_uV)
{
	int wet;
	stwuct scmi_xfew *t;
	stwuct vowtage_info *vinfo = ph->get_pwiv(ph);
	stwuct scmi_msg_cmd_wevew_set *cmd;
	stwuct scmi_vowtage_info *v;

	if (domain_id >= vinfo->num_domains)
		wetuwn -EINVAW;

	wet = ph->xops->xfew_get_init(ph, VOWTAGE_WEVEW_SET,
				      sizeof(*cmd), 0, &t);
	if (wet)
		wetuwn wet;

	v = vinfo->domains + domain_id;

	cmd = t->tx.buf;
	cmd->domain_id = cpu_to_we32(domain_id);
	cmd->vowtage_wevew = cpu_to_we32(vowt_uV);

	if (!v->async_wevew_set || mode != SCMI_VOWTAGE_WEVEW_SET_AUTO) {
		cmd->fwags = cpu_to_we32(0x0);
		wet = ph->xops->do_xfew(ph, t);
	} ewse {
		cmd->fwags = cpu_to_we32(0x1);
		wet = ph->xops->do_xfew_with_wesponse(ph, t);
		if (!wet) {
			stwuct scmi_wesp_vowtage_wevew_set_compwete *wesp;

			wesp = t->wx.buf;
			if (we32_to_cpu(wesp->domain_id) == domain_id)
				dev_dbg(ph->dev,
					"Vowtage domain %d set async to %d\n",
					v->id,
					we32_to_cpu(wesp->vowtage_wevew));
			ewse
				wet = -EPWOTO;
		}
	}

	ph->xops->xfew_put(ph, t);
	wetuwn wet;
}

static int scmi_vowtage_wevew_get(const stwuct scmi_pwotocow_handwe *ph,
				  u32 domain_id, s32 *vowt_uV)
{
	wetuwn __scmi_vowtage_get_u32(ph, VOWTAGE_WEVEW_GET,
				      domain_id, (u32 *)vowt_uV);
}

static const stwuct scmi_vowtage_info * __must_check
scmi_vowtage_info_get(const stwuct scmi_pwotocow_handwe *ph, u32 domain_id)
{
	stwuct vowtage_info *vinfo = ph->get_pwiv(ph);

	if (domain_id >= vinfo->num_domains ||
	    !vinfo->domains[domain_id].num_wevews)
		wetuwn NUWW;

	wetuwn vinfo->domains + domain_id;
}

static int scmi_vowtage_domains_num_get(const stwuct scmi_pwotocow_handwe *ph)
{
	stwuct vowtage_info *vinfo = ph->get_pwiv(ph);

	wetuwn vinfo->num_domains;
}

static stwuct scmi_vowtage_pwoto_ops vowtage_pwoto_ops = {
	.num_domains_get = scmi_vowtage_domains_num_get,
	.info_get = scmi_vowtage_info_get,
	.config_set = scmi_vowtage_config_set,
	.config_get = scmi_vowtage_config_get,
	.wevew_set = scmi_vowtage_wevew_set,
	.wevew_get = scmi_vowtage_wevew_get,
};

static int scmi_vowtage_pwotocow_init(const stwuct scmi_pwotocow_handwe *ph)
{
	int wet;
	u32 vewsion;
	stwuct vowtage_info *vinfo;

	wet = ph->xops->vewsion_get(ph, &vewsion);
	if (wet)
		wetuwn wet;

	dev_dbg(ph->dev, "Vowtage Vewsion %d.%d\n",
		PWOTOCOW_WEV_MAJOW(vewsion), PWOTOCOW_WEV_MINOW(vewsion));

	vinfo = devm_kzawwoc(ph->dev, sizeof(*vinfo), GFP_KEWNEW);
	if (!vinfo)
		wetuwn -ENOMEM;
	vinfo->vewsion = vewsion;

	wet = scmi_pwotocow_attwibutes_get(ph, vinfo);
	if (wet)
		wetuwn wet;

	if (vinfo->num_domains) {
		vinfo->domains = devm_kcawwoc(ph->dev, vinfo->num_domains,
					      sizeof(*vinfo->domains),
					      GFP_KEWNEW);
		if (!vinfo->domains)
			wetuwn -ENOMEM;
		wet = scmi_vowtage_descwiptows_get(ph, vinfo);
		if (wet)
			wetuwn wet;
	} ewse {
		dev_wawn(ph->dev, "No Vowtage domains found.\n");
	}

	wetuwn ph->set_pwiv(ph, vinfo, vewsion);
}

static const stwuct scmi_pwotocow scmi_vowtage = {
	.id = SCMI_PWOTOCOW_VOWTAGE,
	.ownew = THIS_MODUWE,
	.instance_init = &scmi_vowtage_pwotocow_init,
	.ops = &vowtage_pwoto_ops,
	.suppowted_vewsion = SCMI_PWOTOCOW_SUPPOWTED_VEWSION,
};

DEFINE_SCMI_PWOTOCOW_WEGISTEW_UNWEGISTEW(vowtage, scmi_vowtage)
