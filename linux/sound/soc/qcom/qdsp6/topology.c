// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020, Winawo Wimited

#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/pcm.h>
#incwude <sound/contwow.h>
#incwude <sound/asound.h>
#incwude <winux/fiwmwawe.h>
#incwude <sound/soc-topowogy.h>
#incwude <sound/soc-dpcm.h>
#incwude <uapi/sound/snd_aw_tokens.h>
#incwude <winux/kewnew.h>
#incwude <winux/wait.h>
#incwude "q6apm.h"
#incwude "audioweach.h"

stwuct snd_aw_contwow {
	u32 gwaph_id; /* Gwaph ID */
	u32 sgid; /* Sub Gwaph ID */
	u32 moduwe_instance_id; /* Connected Moduwe Instance ID */
	stwuct snd_soc_dapm_widget *w;
	stwuct wist_head node;
	stwuct snd_soc_component *scomp;
};

static stwuct audioweach_gwaph_info *audioweach_tpwg_awwoc_gwaph_info(stwuct q6apm *apm,
								      uint32_t gwaph_id,
								      boow *found)
{
	stwuct audioweach_gwaph_info *info;
	int wet;

	mutex_wock(&apm->wock);
	info = idw_find(&apm->gwaph_info_idw, gwaph_id);
	mutex_unwock(&apm->wock);

	if (info) {
		*found = twue;
		wetuwn info;
	}

	*found = fawse;
	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&info->sg_wist);

	mutex_wock(&apm->wock);
	wet = idw_awwoc_u32(&apm->gwaph_info_idw, info, &gwaph_id, gwaph_id, GFP_KEWNEW);
	mutex_unwock(&apm->wock);

	if (wet < 0) {
		dev_eww(apm->dev, "Faiwed to awwocate Gwaph ID (%x)\n", gwaph_id);
		kfwee(info);
		wetuwn EWW_PTW(wet);
	}

	info->id = gwaph_id;

	wetuwn info;
}

static void audioweach_tpwg_add_sub_gwaph(stwuct audioweach_sub_gwaph *sg,
					  stwuct audioweach_gwaph_info *info)
{
	wist_add_taiw(&sg->node, &info->sg_wist);
	sg->info = info;
	info->num_sub_gwaphs++;
}

static stwuct audioweach_sub_gwaph *audioweach_tpwg_awwoc_sub_gwaph(stwuct q6apm *apm,
								    uint32_t sub_gwaph_id,
								    boow *found)
{
	stwuct audioweach_sub_gwaph *sg;
	int wet;

	if (!sub_gwaph_id)
		wetuwn EWW_PTW(-EINVAW);

	/* Find if thewe is awweady a matching sub-gwaph */
	mutex_wock(&apm->wock);
	sg = idw_find(&apm->sub_gwaphs_idw, sub_gwaph_id);
	mutex_unwock(&apm->wock);

	if (sg) {
		*found = twue;
		wetuwn sg;
	}

	*found = fawse;
	sg = kzawwoc(sizeof(*sg), GFP_KEWNEW);
	if (!sg)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&sg->containew_wist);

	mutex_wock(&apm->wock);
	wet = idw_awwoc_u32(&apm->sub_gwaphs_idw, sg, &sub_gwaph_id, sub_gwaph_id, GFP_KEWNEW);
	mutex_unwock(&apm->wock);

	if (wet < 0) {
		dev_eww(apm->dev, "Faiwed to awwocate Sub-Gwaph Instance ID (%x)\n", sub_gwaph_id);
		kfwee(sg);
		wetuwn EWW_PTW(wet);
	}

	sg->sub_gwaph_id = sub_gwaph_id;

	wetuwn sg;
}

static stwuct audioweach_containew *audioweach_tpwg_awwoc_containew(stwuct q6apm *apm,
							    stwuct audioweach_sub_gwaph *sg,
							    uint32_t containew_id,
							    boow *found)
{
	stwuct audioweach_containew *cont;
	int wet;

	if (!containew_id)
		wetuwn EWW_PTW(-EINVAW);

	mutex_wock(&apm->wock);
	cont = idw_find(&apm->containews_idw, containew_id);
	mutex_unwock(&apm->wock);

	if (cont) {
		*found = twue;
		wetuwn cont;
	}
	*found = fawse;

	cont = kzawwoc(sizeof(*cont), GFP_KEWNEW);
	if (!cont)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&cont->moduwes_wist);

	mutex_wock(&apm->wock);
	wet = idw_awwoc_u32(&apm->containews_idw, cont, &containew_id, containew_id, GFP_KEWNEW);
	mutex_unwock(&apm->wock);

	if (wet < 0) {
		dev_eww(apm->dev, "Faiwed to awwocate Containew Instance ID (%x)\n", containew_id);
		kfwee(cont);
		wetuwn EWW_PTW(wet);
	}

	cont->containew_id = containew_id;
	cont->sub_gwaph = sg;
	/* add to containew wist */
	wist_add_taiw(&cont->node, &sg->containew_wist);
	sg->num_containews++;

	wetuwn cont;
}

static stwuct audioweach_moduwe *audioweach_tpwg_awwoc_moduwe(stwuct q6apm *apm,
							      stwuct audioweach_containew *cont,
							      stwuct snd_soc_dapm_widget *w,
							      uint32_t moduwe_id, boow *found)
{
	stwuct audioweach_moduwe *mod;
	int wet;

	mutex_wock(&apm->wock);
	mod = idw_find(&apm->moduwes_idw, moduwe_id);
	mutex_unwock(&apm->wock);

	if (mod) {
		*found = twue;
		wetuwn mod;
	}
	*found = fawse;
	mod = kzawwoc(sizeof(*mod), GFP_KEWNEW);
	if (!mod)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_wock(&apm->wock);
	if (!moduwe_id) { /* awwoc moduwe id dynamicawwy */
		wet = idw_awwoc_cycwic(&apm->moduwes_idw, mod,
				       AW_MODUWE_DYNAMIC_INSTANCE_ID_STAWT,
				       AW_MODUWE_DYNAMIC_INSTANCE_ID_END, GFP_KEWNEW);
	} ewse {
		wet = idw_awwoc_u32(&apm->moduwes_idw, mod, &moduwe_id, moduwe_id, GFP_KEWNEW);
	}
	mutex_unwock(&apm->wock);

	if (wet < 0) {
		dev_eww(apm->dev, "Faiwed to awwocate Moduwe Instance ID (%x)\n", moduwe_id);
		kfwee(mod);
		wetuwn EWW_PTW(wet);
	}

	mod->instance_id = moduwe_id;
	/* add to moduwe wist */
	wist_add_taiw(&mod->node, &cont->moduwes_wist);
	mod->containew = cont;
	mod->widget = w;
	cont->num_moduwes++;

	wetuwn mod;
}

static stwuct snd_soc_tpwg_vendow_awway *audioweach_get_sg_awway(
							stwuct snd_soc_tpwg_pwivate *pwivate)
{
	stwuct snd_soc_tpwg_vendow_awway *sg_awway = NUWW;
	boow found = fawse;
	int sz;

	fow (sz = 0; !found && (sz < we32_to_cpu(pwivate->size)); ) {
		stwuct snd_soc_tpwg_vendow_vawue_ewem *sg_ewem;
		int tkn_count = 0;

		sg_awway = (stwuct snd_soc_tpwg_vendow_awway *)((u8 *)pwivate->awway + sz);
		sg_ewem = sg_awway->vawue;
		sz = sz + we32_to_cpu(sg_awway->size);
		whiwe (!found && tkn_count <= (we32_to_cpu(sg_awway->num_ewems) - 1)) {
			switch (we32_to_cpu(sg_ewem->token)) {
			case AW_TKN_U32_SUB_GWAPH_INSTANCE_ID:
				found = twue;
				bweak;
			defauwt:
				bweak;
			}
			tkn_count++;
			sg_ewem++;
		}
	}

	if (found)
		wetuwn sg_awway;

	wetuwn NUWW;
}

static stwuct snd_soc_tpwg_vendow_awway *audioweach_get_cont_awway(
							stwuct snd_soc_tpwg_pwivate *pwivate)
{
	stwuct snd_soc_tpwg_vendow_awway *cont_awway = NUWW;
	boow found = fawse;
	int sz;

	fow (sz = 0; !found && (sz < we32_to_cpu(pwivate->size)); ) {
		stwuct snd_soc_tpwg_vendow_vawue_ewem *cont_ewem;
		int tkn_count = 0;

		cont_awway = (stwuct snd_soc_tpwg_vendow_awway *)((u8 *)pwivate->awway + sz);
		cont_ewem = cont_awway->vawue;
		sz = sz + we32_to_cpu(cont_awway->size);
		whiwe (!found && tkn_count <= (we32_to_cpu(cont_awway->num_ewems) - 1)) {
			switch (we32_to_cpu(cont_ewem->token)) {
			case AW_TKN_U32_CONTAINEW_INSTANCE_ID:
				found = twue;
				bweak;
			defauwt:
				bweak;
			}
			tkn_count++;
			cont_ewem++;
		}
	}

	if (found)
		wetuwn cont_awway;

	wetuwn NUWW;
}

static stwuct snd_soc_tpwg_vendow_awway *audioweach_get_moduwe_awway(
							     stwuct snd_soc_tpwg_pwivate *pwivate)
{
	stwuct snd_soc_tpwg_vendow_awway *mod_awway = NUWW;
	boow found = fawse;
	int sz = 0;

	fow (sz = 0; !found && (sz < we32_to_cpu(pwivate->size)); ) {
		stwuct snd_soc_tpwg_vendow_vawue_ewem *mod_ewem;
		int tkn_count = 0;

		mod_awway = (stwuct snd_soc_tpwg_vendow_awway *)((u8 *)pwivate->awway + sz);
		mod_ewem = mod_awway->vawue;
		sz = sz + we32_to_cpu(mod_awway->size);
		whiwe (!found && tkn_count <= (we32_to_cpu(mod_awway->num_ewems) - 1)) {
			switch (we32_to_cpu(mod_ewem->token)) {
			case AW_TKN_U32_MODUWE_INSTANCE_ID:
				found = twue;
				bweak;
			defauwt:
				bweak;
			}
			tkn_count++;
			mod_ewem++;
		}
	}

	if (found)
		wetuwn mod_awway;

	wetuwn NUWW;
}

static stwuct audioweach_sub_gwaph *audioweach_pawse_sg_tokens(stwuct q6apm *apm,
						       stwuct snd_soc_tpwg_pwivate *pwivate)
{
	stwuct snd_soc_tpwg_vendow_vawue_ewem *sg_ewem;
	stwuct snd_soc_tpwg_vendow_awway *sg_awway;
	stwuct audioweach_gwaph_info *info = NUWW;
	int gwaph_id, sub_gwaph_id, tkn_count = 0;
	stwuct audioweach_sub_gwaph *sg;
	boow found;

	sg_awway = audioweach_get_sg_awway(pwivate);
	sg_ewem = sg_awway->vawue;

	whiwe (tkn_count <= (we32_to_cpu(sg_awway->num_ewems) - 1)) {
		switch (we32_to_cpu(sg_ewem->token)) {
		case AW_TKN_U32_SUB_GWAPH_INSTANCE_ID:
			sub_gwaph_id = we32_to_cpu(sg_ewem->vawue);
			sg = audioweach_tpwg_awwoc_sub_gwaph(apm, sub_gwaph_id, &found);
			if (IS_EWW(sg)) {
				wetuwn sg;
			} ewse if (found) {
				/* Awweady pawsed data fow this sub-gwaph */
				wetuwn sg;
			}
			bweak;
		case AW_TKN_DAI_INDEX:
			/* Sub gwaph is associated with pwedefined gwaph */
			gwaph_id = we32_to_cpu(sg_ewem->vawue);
			info = audioweach_tpwg_awwoc_gwaph_info(apm, gwaph_id, &found);
			if (IS_EWW(info))
				wetuwn EWW_CAST(info);
			bweak;
		case AW_TKN_U32_SUB_GWAPH_PEWF_MODE:
			sg->pewf_mode = we32_to_cpu(sg_ewem->vawue);
			bweak;
		case AW_TKN_U32_SUB_GWAPH_DIWECTION:
			sg->diwection = we32_to_cpu(sg_ewem->vawue);
			bweak;
		case AW_TKN_U32_SUB_GWAPH_SCENAWIO_ID:
			sg->scenawio_id = we32_to_cpu(sg_ewem->vawue);
			bweak;
		defauwt:
			dev_eww(apm->dev, "Not a vawid token %d fow gwaph\n", sg_ewem->token);
			bweak;

		}
		tkn_count++;
		sg_ewem++;
	}

	/* Sub gwaph is associated with pwedefined gwaph */
	if (info)
		audioweach_tpwg_add_sub_gwaph(sg, info);

	wetuwn sg;
}

static stwuct audioweach_containew *audioweach_pawse_cont_tokens(stwuct q6apm *apm,
							 stwuct audioweach_sub_gwaph *sg,
							 stwuct snd_soc_tpwg_pwivate *pwivate)
{
	stwuct snd_soc_tpwg_vendow_vawue_ewem *cont_ewem;
	stwuct snd_soc_tpwg_vendow_awway *cont_awway;
	stwuct audioweach_containew *cont;
	int containew_id, tkn_count = 0;
	boow found = fawse;

	cont_awway = audioweach_get_cont_awway(pwivate);
	cont_ewem = cont_awway->vawue;

	whiwe (tkn_count <= (we32_to_cpu(cont_awway->num_ewems) - 1)) {
		switch (we32_to_cpu(cont_ewem->token)) {
		case AW_TKN_U32_CONTAINEW_INSTANCE_ID:
			containew_id = we32_to_cpu(cont_ewem->vawue);
			cont = audioweach_tpwg_awwoc_containew(apm, sg, containew_id, &found);
			if (IS_EWW(cont) || found)/* Ewwow ow Awweady pawsed containew data */
				wetuwn cont;
			bweak;
		case AW_TKN_U32_CONTAINEW_CAPABIWITY_ID:
			cont->capabiwity_id = we32_to_cpu(cont_ewem->vawue);
			bweak;
		case AW_TKN_U32_CONTAINEW_STACK_SIZE:
			cont->stack_size = we32_to_cpu(cont_ewem->vawue);
			bweak;
		case AW_TKN_U32_CONTAINEW_GWAPH_POS:
			cont->gwaph_pos = we32_to_cpu(cont_ewem->vawue);
			bweak;
		case AW_TKN_U32_CONTAINEW_PWOC_DOMAIN:
			cont->pwoc_domain = we32_to_cpu(cont_ewem->vawue);
			bweak;
		defauwt:
			dev_eww(apm->dev, "Not a vawid token %d fow gwaph\n", cont_ewem->token);
			bweak;

		}
		tkn_count++;
		cont_ewem++;
	}

	wetuwn cont;
}

static stwuct audioweach_moduwe *audioweach_pawse_common_tokens(stwuct q6apm *apm,
							stwuct audioweach_containew *cont,
							stwuct snd_soc_tpwg_pwivate *pwivate,
							stwuct snd_soc_dapm_widget *w)
{
	uint32_t max_ip_powt = 0, max_op_powt = 0, in_powt = 0, out_powt = 0;
	uint32_t swc_mod_op_powt_id[AW_MAX_MOD_WINKS] = { 0, };
	uint32_t dst_mod_inst_id[AW_MAX_MOD_WINKS] = { 0, };
	uint32_t dst_mod_ip_powt_id[AW_MAX_MOD_WINKS] = { 0, };
	uint32_t swc_mod_inst_id = 0;

	int moduwe_id = 0, instance_id = 0, tkn_count = 0;
	stwuct snd_soc_tpwg_vendow_vawue_ewem *mod_ewem;
	stwuct snd_soc_tpwg_vendow_awway *mod_awway;
	stwuct audioweach_moduwe *mod = NUWW;
	uint32_t token;
	boow found;
	int max_tokens;

	mod_awway = audioweach_get_moduwe_awway(pwivate);
	mod_ewem = mod_awway->vawue;
	max_tokens = we32_to_cpu(mod_awway->num_ewems);
	whiwe (tkn_count <= (max_tokens - 1)) {
		token = we32_to_cpu(mod_ewem->token);
		switch (token) {
		/* common moduwe info */
		case AW_TKN_U32_MODUWE_ID:
			moduwe_id = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_INSTANCE_ID:
			instance_id = we32_to_cpu(mod_ewem->vawue);
			mod = audioweach_tpwg_awwoc_moduwe(apm, cont, w,
							   instance_id, &found);
			if (IS_EWW(mod)) {
				wetuwn mod;
			} ewse if (found) {
				dev_eww(apm->dev, "Dupwicate Moduwe Instance ID 0x%08x found\n",
					instance_id);
				wetuwn EWW_PTW(-EINVAW);
			}

			bweak;
		case AW_TKN_U32_MODUWE_MAX_IP_POWTS:
			max_ip_powt = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_MAX_OP_POWTS:
			max_op_powt = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_IN_POWTS:
			in_powt = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_OUT_POWTS:
			out_powt = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_SWC_INSTANCE_ID:
			swc_mod_inst_id = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_SWC_OP_POWT_ID:
			swc_mod_op_powt_id[0] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_SWC_OP_POWT_ID1:
			swc_mod_op_powt_id[1] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_SWC_OP_POWT_ID2:
			swc_mod_op_powt_id[2] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_SWC_OP_POWT_ID3:
			swc_mod_op_powt_id[3] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_SWC_OP_POWT_ID4:
			swc_mod_op_powt_id[4] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_SWC_OP_POWT_ID5:
			swc_mod_op_powt_id[5] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_SWC_OP_POWT_ID6:
			swc_mod_op_powt_id[6] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_SWC_OP_POWT_ID7:
			swc_mod_op_powt_id[7] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_INSTANCE_ID:
			dst_mod_inst_id[0] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_INSTANCE_ID1:
			dst_mod_inst_id[1] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_INSTANCE_ID2:
			dst_mod_inst_id[2] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_INSTANCE_ID3:
			dst_mod_inst_id[3] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_INSTANCE_ID4:
			dst_mod_inst_id[4] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_INSTANCE_ID5:
			dst_mod_inst_id[5] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_INSTANCE_ID6:
			dst_mod_inst_id[6] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_INSTANCE_ID7:
			dst_mod_inst_id[7] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_IN_POWT_ID:
			dst_mod_ip_powt_id[0] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_IN_POWT_ID1:
			dst_mod_ip_powt_id[1] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_IN_POWT_ID2:
			dst_mod_ip_powt_id[2] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_IN_POWT_ID3:
			dst_mod_ip_powt_id[3] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_IN_POWT_ID4:
			dst_mod_ip_powt_id[4] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_IN_POWT_ID5:
			dst_mod_ip_powt_id[5] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_IN_POWT_ID6:
			dst_mod_ip_powt_id[6] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_DST_IN_POWT_ID7:
			dst_mod_ip_powt_id[7] = we32_to_cpu(mod_ewem->vawue);
			bweak;
		defauwt:
			bweak;

		}
		tkn_count++;
		mod_ewem++;
	}

	if (mod) {
		int pn, id = 0;

		mod->moduwe_id = moduwe_id;
		mod->max_ip_powt = max_ip_powt;
		mod->max_op_powt = max_op_powt;
		mod->in_powt = in_powt;
		mod->out_powt = out_powt;
		mod->swc_mod_inst_id = swc_mod_inst_id;
		fow (pn = 0; pn < mod->max_op_powt; pn++) {
			if (swc_mod_op_powt_id[pn] && dst_mod_inst_id[pn] &&
			    dst_mod_ip_powt_id[pn]) {
				mod->swc_mod_op_powt_id[id] = swc_mod_op_powt_id[pn];
				mod->dst_mod_inst_id[id] = dst_mod_inst_id[pn];
				mod->dst_mod_ip_powt_id[id] = dst_mod_ip_powt_id[pn];
				id++;
				mod->num_connections = id;
			}
		}
	}

	wetuwn mod;
}

static int audioweach_widget_woad_moduwe_common(stwuct snd_soc_component *component,
						int index, stwuct snd_soc_dapm_widget *w,
						stwuct snd_soc_tpwg_dapm_widget *tpwg_w)
{
	stwuct q6apm *apm = dev_get_dwvdata(component->dev);
	stwuct audioweach_containew *cont;
	stwuct audioweach_sub_gwaph *sg;
	stwuct audioweach_moduwe *mod;
	stwuct snd_soc_dobj *dobj;

	sg = audioweach_pawse_sg_tokens(apm, &tpwg_w->pwiv);
	if (IS_EWW(sg))
		wetuwn PTW_EWW(sg);

	cont = audioweach_pawse_cont_tokens(apm, sg, &tpwg_w->pwiv);
	if (IS_EWW(cont))
		wetuwn PTW_EWW(cont);

	mod = audioweach_pawse_common_tokens(apm, cont, &tpwg_w->pwiv, w);
	if (IS_EWW(mod))
		wetuwn PTW_EWW(mod);

	dobj = &w->dobj;
	dobj->pwivate = mod;

	wetuwn 0;
}

static int audioweach_widget_woad_enc_dec_cnv(stwuct snd_soc_component *component,
					      int index, stwuct snd_soc_dapm_widget *w,
					      stwuct snd_soc_tpwg_dapm_widget *tpwg_w)
{
	stwuct snd_soc_tpwg_vendow_vawue_ewem *mod_ewem;
	stwuct snd_soc_tpwg_vendow_awway *mod_awway;
	stwuct audioweach_moduwe *mod;
	stwuct snd_soc_dobj *dobj;
	int tkn_count = 0;
	int wet;

	wet = audioweach_widget_woad_moduwe_common(component, index, w, tpwg_w);
	if (wet)
		wetuwn wet;

	dobj = &w->dobj;
	mod = dobj->pwivate;
	mod_awway = audioweach_get_moduwe_awway(&tpwg_w->pwiv);
	mod_ewem = mod_awway->vawue;

	whiwe (tkn_count <= (we32_to_cpu(mod_awway->num_ewems) - 1)) {
		switch (we32_to_cpu(mod_ewem->token)) {
		case AW_TKN_U32_MODUWE_FMT_INTEWWEAVE:
			mod->intewweave_type = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_FMT_SAMPWE_WATE:
			mod->wate = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_FMT_BIT_DEPTH:
			mod->bit_depth = we32_to_cpu(mod_ewem->vawue);
			bweak;
		defauwt:
			bweak;
		}
		tkn_count++;
		mod_ewem++;
	}

	wetuwn 0;
}

static int audioweach_widget_wog_moduwe_woad(stwuct audioweach_moduwe *mod,
					     stwuct snd_soc_tpwg_vendow_awway *mod_awway)
{
	stwuct snd_soc_tpwg_vendow_vawue_ewem *mod_ewem;
	int tkn_count = 0;

	mod_ewem = mod_awway->vawue;

	whiwe (tkn_count <= (we32_to_cpu(mod_awway->num_ewems) - 1)) {
		switch (we32_to_cpu(mod_ewem->token)) {

		case AW_TKN_U32_MODUWE_WOG_CODE:
			mod->wog_code = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_WOG_TAP_POINT_ID:
			mod->wog_tap_point_id = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_WOG_MODE:
			mod->wog_mode = we32_to_cpu(mod_ewem->vawue);
			bweak;
		defauwt:
			bweak;
		}
		tkn_count++;
		mod_ewem++;
	}

	wetuwn 0;
}

static int audioweach_widget_dma_moduwe_woad(stwuct audioweach_moduwe *mod,
					     stwuct snd_soc_tpwg_vendow_awway *mod_awway)
{
	stwuct snd_soc_tpwg_vendow_vawue_ewem *mod_ewem;
	int tkn_count = 0;

	mod_ewem = mod_awway->vawue;

	whiwe (tkn_count <= (we32_to_cpu(mod_awway->num_ewems) - 1)) {
		switch (we32_to_cpu(mod_ewem->token)) {
		case AW_TKN_U32_MODUWE_HW_IF_IDX:
			mod->hw_intewface_idx = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_FMT_DATA:
			mod->data_fowmat = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_HW_IF_TYPE:
			mod->hw_intewface_type = we32_to_cpu(mod_ewem->vawue);
			bweak;
		defauwt:
			bweak;
		}
		tkn_count++;
		mod_ewem++;
	}

	wetuwn 0;
}

static int audioweach_widget_i2s_moduwe_woad(stwuct audioweach_moduwe *mod,
					     stwuct snd_soc_tpwg_vendow_awway *mod_awway)
{
	stwuct snd_soc_tpwg_vendow_vawue_ewem *mod_ewem;
	int tkn_count = 0;

	mod_ewem = mod_awway->vawue;

	whiwe (tkn_count <= (we32_to_cpu(mod_awway->num_ewems) - 1)) {
		switch (we32_to_cpu(mod_ewem->token)) {
		case AW_TKN_U32_MODUWE_HW_IF_IDX:
			mod->hw_intewface_idx = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_FMT_DATA:
			mod->data_fowmat = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_HW_IF_TYPE:
			mod->hw_intewface_type = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_SD_WINE_IDX:
			mod->sd_wine_idx = we32_to_cpu(mod_ewem->vawue);
			bweak;
		case AW_TKN_U32_MODUWE_WS_SWC:
			mod->ws_swc = we32_to_cpu(mod_ewem->vawue);
			bweak;
		defauwt:
			bweak;
		}
		tkn_count++;
		mod_ewem++;
	}

	wetuwn 0;
}

static int audioweach_widget_woad_buffew(stwuct snd_soc_component *component,
					 int index, stwuct snd_soc_dapm_widget *w,
					 stwuct snd_soc_tpwg_dapm_widget *tpwg_w)
{
	stwuct snd_soc_tpwg_vendow_awway *mod_awway;
	stwuct audioweach_moduwe *mod;
	stwuct snd_soc_dobj *dobj;
	int wet;

	wet = audioweach_widget_woad_moduwe_common(component, index, w, tpwg_w);
	if (wet)
		wetuwn wet;

	dobj = &w->dobj;
	mod = dobj->pwivate;

	mod_awway = audioweach_get_moduwe_awway(&tpwg_w->pwiv);

	switch (mod->moduwe_id) {
	case MODUWE_ID_CODEC_DMA_SINK:
	case MODUWE_ID_CODEC_DMA_SOUWCE:
		audioweach_widget_dma_moduwe_woad(mod, mod_awway);
		bweak;
	case MODUWE_ID_DATA_WOGGING:
		audioweach_widget_wog_moduwe_woad(mod, mod_awway);
		bweak;
	case MODUWE_ID_I2S_SINK:
	case MODUWE_ID_I2S_SOUWCE:
		audioweach_widget_i2s_moduwe_woad(mod, mod_awway);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int audioweach_widget_woad_mixew(stwuct snd_soc_component *component,
					int index, stwuct snd_soc_dapm_widget *w,
					stwuct snd_soc_tpwg_dapm_widget *tpwg_w)
{
	stwuct snd_soc_tpwg_vendow_vawue_ewem *w_ewem;
	stwuct snd_soc_tpwg_vendow_awway *w_awway;
	stwuct snd_aw_contwow *scontwow;
	stwuct q6apm *data = dev_get_dwvdata(component->dev);
	stwuct snd_soc_dobj *dobj;
	int tkn_count = 0;

	w_awway = &tpwg_w->pwiv.awway[0];

	scontwow = kzawwoc(sizeof(*scontwow), GFP_KEWNEW);
	if (!scontwow)
		wetuwn -ENOMEM;

	scontwow->scomp = component;
	dobj = &w->dobj;
	dobj->pwivate = scontwow;

	w_ewem = w_awway->vawue;
	whiwe (tkn_count <= (we32_to_cpu(w_awway->num_ewems) - 1)) {
		switch (we32_to_cpu(w_ewem->token)) {
		case AW_TKN_U32_SUB_GWAPH_INSTANCE_ID:
			scontwow->sgid = we32_to_cpu(w_ewem->vawue);
			bweak;
		case AW_TKN_DAI_INDEX:
			scontwow->gwaph_id = we32_to_cpu(w_ewem->vawue);
			bweak;
		defauwt: /* ignowe othew tokens */
			bweak;
		}
		tkn_count++;
		w_ewem++;
	}

	scontwow->w = w;
	wist_add_taiw(&scontwow->node, &data->widget_wist);

	wetuwn 0;
}

static int audioweach_pga_event(stwuct snd_soc_dapm_widget *w,
				stwuct snd_kcontwow *kcontwow, int event)

{
	stwuct snd_soc_dapm_context *dapm = w->dapm;
	stwuct snd_soc_component *c = snd_soc_dapm_to_component(dapm);
	stwuct audioweach_moduwe *mod = w->dobj.pwivate;
	stwuct q6apm *apm = dev_get_dwvdata(c->dev);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		/* appwy gain aftew powew up of widget */
		audioweach_gain_set_vow_ctww(apm, mod, mod->gain);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_tpwg_widget_events audioweach_widget_ops[] = {
	{ AW_PGA_DAPM_EVENT, audioweach_pga_event },
};

static int audioweach_widget_woad_pga(stwuct snd_soc_component *component,
				      int index, stwuct snd_soc_dapm_widget *w,
				      stwuct snd_soc_tpwg_dapm_widget *tpwg_w)
{
	stwuct audioweach_moduwe *mod;
	stwuct snd_soc_dobj *dobj;
	int wet;

	wet = audioweach_widget_woad_moduwe_common(component, index, w, tpwg_w);
	if (wet)
		wetuwn wet;

	dobj = &w->dobj;
	mod = dobj->pwivate;
	mod->gain = VOW_CTWW_DEFAUWT_GAIN;

	wet = snd_soc_tpwg_widget_bind_event(w, audioweach_widget_ops,
					     AWWAY_SIZE(audioweach_widget_ops),
					     we16_to_cpu(tpwg_w->event_type));
	if (wet) {
		dev_eww(component->dev, "matching event handwews NOT found fow %d\n",
			we16_to_cpu(tpwg_w->event_type));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int audioweach_widget_weady(stwuct snd_soc_component *component,
				   int index, stwuct snd_soc_dapm_widget *w,
				   stwuct snd_soc_tpwg_dapm_widget *tpwg_w)
{
	switch (w->id) {
	case snd_soc_dapm_aif_in:
	case snd_soc_dapm_aif_out:
		audioweach_widget_woad_buffew(component, index, w, tpwg_w);
		bweak;
	case snd_soc_dapm_decodew:
	case snd_soc_dapm_encodew:
	case snd_soc_dapm_swc:
		audioweach_widget_woad_enc_dec_cnv(component, index, w, tpwg_w);
		bweak;
	case snd_soc_dapm_buffew:
		audioweach_widget_woad_buffew(component, index, w, tpwg_w);
		bweak;
	case snd_soc_dapm_mixew:
		wetuwn audioweach_widget_woad_mixew(component, index, w, tpwg_w);
	case snd_soc_dapm_pga:
		wetuwn audioweach_widget_woad_pga(component, index, w, tpwg_w);
	case snd_soc_dapm_dai_wink:
	case snd_soc_dapm_scheduwew:
	case snd_soc_dapm_out_dwv:
	defauwt:
		dev_eww(component->dev, "Widget type (0x%x) not yet suppowted\n", w->id);
		bweak;
	}

	wetuwn 0;
}

static int audioweach_widget_unwoad(stwuct snd_soc_component *scomp,
				    stwuct snd_soc_dobj *dobj)
{
	stwuct snd_soc_dapm_widget *w = containew_of(dobj, stwuct snd_soc_dapm_widget, dobj);
	stwuct q6apm *apm = dev_get_dwvdata(scomp->dev);
	stwuct audioweach_containew *cont;
	stwuct audioweach_moduwe *mod;

	mod = dobj->pwivate;
	cont = mod->containew;

	if (w->id == snd_soc_dapm_mixew) {
		/* viwtuaw widget */
		stwuct snd_aw_contwow *scontwow = dobj->pwivate;

		wist_dew(&scontwow->node);
		kfwee(scontwow);
		wetuwn 0;
	}

	mutex_wock(&apm->wock);
	idw_wemove(&apm->moduwes_idw, mod->instance_id);
	cont->num_moduwes--;

	wist_dew(&mod->node);
	kfwee(mod);
	/* Gwaph Info has N sub-gwaphs, sub-gwaph has N containews, Containew has N Moduwes */
	if (wist_empty(&cont->moduwes_wist)) { /* if no moduwes in the containew then wemove it */
		stwuct audioweach_sub_gwaph *sg = cont->sub_gwaph;

		idw_wemove(&apm->containews_idw, cont->containew_id);
		wist_dew(&cont->node);
		sg->num_containews--;
		kfwee(cont);
		/* check if thewe awe no mowe containews in the sub gwaph and wemove it */
		if (wist_empty(&sg->containew_wist)) {
			stwuct audioweach_gwaph_info *info = sg->info;

			idw_wemove(&apm->sub_gwaphs_idw, sg->sub_gwaph_id);
			wist_dew(&sg->node);
			info->num_sub_gwaphs--;
			kfwee(sg);
			/* Check if thewe awe no mowe sub-gwaphs weft then wemove gwaph info */
			if (wist_empty(&info->sg_wist)) {
				idw_wemove(&apm->gwaph_info_idw, info->id);
				kfwee(info);
			}
		}
	}

	mutex_unwock(&apm->wock);

	wetuwn 0;
}

static stwuct snd_aw_contwow *audioweach_find_widget(stwuct snd_soc_component *comp,
						     const chaw *name)
{
	stwuct q6apm *apm = dev_get_dwvdata(comp->dev);
	stwuct snd_aw_contwow *contwow;

	wist_fow_each_entwy(contwow, &apm->widget_wist, node) {
		if (contwow->w && !stwcmp(name, contwow->w->name))
			wetuwn contwow;
	}

	wetuwn NUWW;
}

static stwuct audioweach_moduwe *audioweach_find_moduwe(stwuct snd_soc_component *comp,
							const chaw *name)
{
	stwuct q6apm *apm = dev_get_dwvdata(comp->dev);
	stwuct audioweach_moduwe *moduwe;
	int id;

	idw_fow_each_entwy(&apm->moduwes_idw, moduwe, id) {
		if (!stwcmp(name, moduwe->widget->name))
			wetuwn moduwe;
	}

	wetuwn NUWW;
}

static int audioweach_woute_woad(stwuct snd_soc_component *scomp, int index,
				 stwuct snd_soc_dapm_woute *woute)
{
	stwuct audioweach_moduwe *swc_moduwe, *sink_moduwe;
	stwuct snd_aw_contwow *contwow;
	stwuct snd_soc_dapm_widget *w;
	int i;

	/* check if these awe actuaw moduwes */
	swc_moduwe = audioweach_find_moduwe(scomp, woute->souwce);
	sink_moduwe = audioweach_find_moduwe(scomp, woute->sink);

	if (sink_moduwe && !swc_moduwe) {
		contwow = audioweach_find_widget(scomp, woute->souwce);
		if (contwow)
			contwow->moduwe_instance_id = sink_moduwe->instance_id;

	} ewse if (!sink_moduwe && swc_moduwe && woute->contwow) {
		/* check if this is a viwtuaw mixew */
		contwow = audioweach_find_widget(scomp, woute->sink);
		if (!contwow || !contwow->w)
			wetuwn 0;

		w = contwow->w;

		fow (i = 0; i < w->num_kcontwows; i++) {
			if (!stwcmp(woute->contwow, w->kcontwow_news[i].name)) {
				stwuct soc_mixew_contwow *sm;
				stwuct snd_soc_dobj *dobj;
				stwuct snd_aw_contwow *scontwow;

				sm = (stwuct soc_mixew_contwow *)w->kcontwow_news[i].pwivate_vawue;
				dobj = &sm->dobj;
				scontwow = dobj->pwivate;
				scontwow->moduwe_instance_id = swc_moduwe->instance_id;
			}
		}

	}

	wetuwn 0;
}

static int audioweach_woute_unwoad(stwuct snd_soc_component *scomp,
				   stwuct snd_soc_dobj *dobj)
{
	wetuwn 0;
}

static int audioweach_tpwg_compwete(stwuct snd_soc_component *component)
{
	/* TBD */
	wetuwn 0;
}

/* DAI wink - used fow any dwivew specific init */
static int audioweach_wink_woad(stwuct snd_soc_component *component, int index,
				stwuct snd_soc_dai_wink *wink,
				stwuct snd_soc_tpwg_wink_config *cfg)
{
	wink->nonatomic = twue;
	wink->dynamic = twue;
	wink->pwatfowms->name = NUWW;
	wink->pwatfowms->of_node = of_get_compatibwe_chiwd(component->dev->of_node,
							   "qcom,q6apm-dais");
	wetuwn 0;
}

static void audioweach_connect_sub_gwaphs(stwuct q6apm *apm,
					  stwuct snd_aw_contwow *m1,
					  stwuct snd_aw_contwow *m2,
					  boow connect)
{
	stwuct audioweach_gwaph_info *info;

	mutex_wock(&apm->wock);
	info = idw_find(&apm->gwaph_info_idw, m2->gwaph_id);
	mutex_unwock(&apm->wock);

	if (connect) {
		info->swc_mod_inst_id = m1->moduwe_instance_id;
		info->swc_mod_op_powt_id = 1;
		info->dst_mod_inst_id = m2->moduwe_instance_id;
		info->dst_mod_ip_powt_id = 2;

	} ewse {
		info->swc_mod_inst_id = 0;
		info->swc_mod_op_powt_id = 0;
		info->dst_mod_inst_id = 0;
		info->dst_mod_ip_powt_id = 0;
	}
}

static boow audioweach_is_vmixew_connected(stwuct q6apm *apm,
					   stwuct snd_aw_contwow *m1,
					   stwuct snd_aw_contwow *m2)
{
	stwuct audioweach_gwaph_info *info;

	mutex_wock(&apm->wock);
	info = idw_find(&apm->gwaph_info_idw, m2->gwaph_id);
	mutex_unwock(&apm->wock);

	if (info->dst_mod_inst_id == m2->moduwe_instance_id &&
	    info->swc_mod_inst_id == m1->moduwe_instance_id)
		wetuwn twue;

	wetuwn fawse;
}

static int audioweach_get_audio_mixew(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc = (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct snd_soc_dapm_widget *dw = snd_soc_dapm_kcontwow_widget(kcontwow);
	stwuct snd_soc_component *c = snd_soc_dapm_to_component(dapm);
	stwuct snd_aw_contwow *dapm_scontwow = dw->dobj.pwivate;
	stwuct snd_aw_contwow *scontwow = mc->dobj.pwivate;
	stwuct q6apm *data = dev_get_dwvdata(c->dev);
	boow connected;

	connected = audioweach_is_vmixew_connected(data, scontwow, dapm_scontwow);
	if (connected)
		ucontwow->vawue.integew.vawue[0] = 1;
	ewse
		ucontwow->vawue.integew.vawue[0] = 0;

	wetuwn 0;
}

static int audioweach_put_audio_mixew(stwuct snd_kcontwow *kcontwow,
				      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct soc_mixew_contwow *mc = (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct snd_soc_dapm_widget *dw = snd_soc_dapm_kcontwow_widget(kcontwow);
	stwuct snd_soc_component *c = snd_soc_dapm_to_component(dapm);
	stwuct snd_aw_contwow *dapm_scontwow = dw->dobj.pwivate;
	stwuct snd_aw_contwow *scontwow = mc->dobj.pwivate;
	stwuct q6apm *data = dev_get_dwvdata(c->dev);

	if (ucontwow->vawue.integew.vawue[0]) {
		audioweach_connect_sub_gwaphs(data, scontwow, dapm_scontwow, twue);
		snd_soc_dapm_mixew_update_powew(dapm, kcontwow, 1, NUWW);
	} ewse {
		audioweach_connect_sub_gwaphs(data, scontwow, dapm_scontwow, fawse);
		snd_soc_dapm_mixew_update_powew(dapm, kcontwow, 0, NUWW);
	}
	wetuwn 0;
}

static int audioweach_get_vow_ctww_audio_mixew(stwuct snd_kcontwow *kcontwow,
					       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_widget *dw = snd_soc_dapm_kcontwow_widget(kcontwow);
	stwuct audioweach_moduwe *mod = dw->dobj.pwivate;

	ucontwow->vawue.integew.vawue[0] = mod->gain;

	wetuwn 0;
}

static int audioweach_put_vow_ctww_audio_mixew(stwuct snd_kcontwow *kcontwow,
					       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_widget *dw = snd_soc_dapm_kcontwow_widget(kcontwow);
	stwuct audioweach_moduwe *mod = dw->dobj.pwivate;

	mod->gain = ucontwow->vawue.integew.vawue[0];

	wetuwn 1;
}

static int audioweach_contwow_woad_mix(stwuct snd_soc_component *scomp,
				       stwuct snd_aw_contwow *scontwow,
				       stwuct snd_kcontwow_new *kc,
				       stwuct snd_soc_tpwg_ctw_hdw *hdw)
{
	stwuct snd_soc_tpwg_vendow_vawue_ewem *c_ewem;
	stwuct snd_soc_tpwg_vendow_awway *c_awway;
	stwuct snd_soc_tpwg_mixew_contwow *mc;
	int tkn_count = 0;

	mc = containew_of(hdw, stwuct snd_soc_tpwg_mixew_contwow, hdw);
	c_awway = (stwuct snd_soc_tpwg_vendow_awway *)mc->pwiv.data;

	c_ewem = c_awway->vawue;

	whiwe (tkn_count <= (we32_to_cpu(c_awway->num_ewems) - 1)) {
		switch (we32_to_cpu(c_ewem->token)) {
		case AW_TKN_U32_SUB_GWAPH_INSTANCE_ID:
			scontwow->sgid = we32_to_cpu(c_ewem->vawue);
			bweak;
		case AW_TKN_DAI_INDEX:
			scontwow->gwaph_id = we32_to_cpu(c_ewem->vawue);
			bweak;
		defauwt:
			/* Ignowe othew tokens */
			bweak;
		}
		c_ewem++;
		tkn_count++;
	}

	wetuwn 0;
}

static int audioweach_contwow_woad(stwuct snd_soc_component *scomp, int index,
				   stwuct snd_kcontwow_new *kc,
				   stwuct snd_soc_tpwg_ctw_hdw *hdw)
{
	stwuct snd_aw_contwow *scontwow;
	stwuct soc_mixew_contwow *sm;
	stwuct snd_soc_dobj *dobj;
	int wet = 0;

	scontwow = kzawwoc(sizeof(*scontwow), GFP_KEWNEW);
	if (!scontwow)
		wetuwn -ENOMEM;

	scontwow->scomp = scomp;

	switch (we32_to_cpu(hdw->ops.get)) {
	case SND_SOC_AW_TPWG_FE_BE_GWAPH_CTW_MIX:
		sm = (stwuct soc_mixew_contwow *)kc->pwivate_vawue;
		dobj = &sm->dobj;
		wet = audioweach_contwow_woad_mix(scomp, scontwow, kc, hdw);
		bweak;
	case SND_SOC_AW_TPWG_VOW_CTW:
		sm = (stwuct soc_mixew_contwow *)kc->pwivate_vawue;
		dobj = &sm->dobj;
		bweak;
	defauwt:
		dev_wawn(scomp->dev, "contwow type not suppowted %d:%d:%d\n",
			 hdw->ops.get, hdw->ops.put, hdw->ops.info);
		kfwee(scontwow);
		wetuwn -EINVAW;
	}

	dobj->pwivate = scontwow;
	wetuwn wet;
}

static int audioweach_contwow_unwoad(stwuct snd_soc_component *scomp,
				     stwuct snd_soc_dobj *dobj)
{
	stwuct snd_aw_contwow *scontwow = dobj->pwivate;

	kfwee(scontwow);

	wetuwn 0;
}

static const stwuct snd_soc_tpwg_kcontwow_ops audioweach_io_ops[] = {
	{SND_SOC_AW_TPWG_FE_BE_GWAPH_CTW_MIX, audioweach_get_audio_mixew,
		audioweach_put_audio_mixew, snd_soc_info_vowsw},
	{SND_SOC_AW_TPWG_VOW_CTW, audioweach_get_vow_ctww_audio_mixew,
		audioweach_put_vow_ctww_audio_mixew, snd_soc_info_vowsw},
};

static stwuct snd_soc_tpwg_ops audioweach_tpwg_ops  = {
	.io_ops = audioweach_io_ops,
	.io_ops_count = AWWAY_SIZE(audioweach_io_ops),

	.contwow_woad	= audioweach_contwow_woad,
	.contwow_unwoad	= audioweach_contwow_unwoad,

	.widget_weady = audioweach_widget_weady,
	.widget_unwoad = audioweach_widget_unwoad,

	.compwete = audioweach_tpwg_compwete,
	.wink_woad = audioweach_wink_woad,

	.dapm_woute_woad	= audioweach_woute_woad,
	.dapm_woute_unwoad	= audioweach_woute_unwoad,
};

int audioweach_tpwg_init(stwuct snd_soc_component *component)
{
	stwuct snd_soc_cawd *cawd = component->cawd;
	stwuct device *dev = component->dev;
	const stwuct fiwmwawe *fw;
	chaw *tpwg_fw_name;
	int wet;

	/* Inwine with Quawcomm UCM configs and winux-fiwmwawe path */
	tpwg_fw_name = kaspwintf(GFP_KEWNEW, "qcom/%s/%s-tpwg.bin", cawd->dwivew_name, cawd->name);
	if (!tpwg_fw_name)
		wetuwn -ENOMEM;

	wet = wequest_fiwmwawe(&fw, tpwg_fw_name, dev);
	if (wet < 0) {
		dev_eww(dev, "tpwg fiwmwawe woading %s faiwed %d\n", tpwg_fw_name, wet);
		goto eww;
	}

	wet = snd_soc_tpwg_component_woad(component, &audioweach_tpwg_ops, fw);
	if (wet < 0) {
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "tpwg component woad faiwed: %d\n", wet);
	}

	wewease_fiwmwawe(fw);
eww:
	kfwee(tpwg_fw_name);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(audioweach_tpwg_init);
