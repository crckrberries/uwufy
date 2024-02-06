// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <sound/intew-nhwt.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude "avs.h"
#incwude "contwow.h"
#incwude "path.h"
#incwude "topowogy.h"

/* Must be cawwed with adev->comp_wist_mutex hewd. */
static stwuct avs_tpwg *
avs_path_find_tpwg(stwuct avs_dev *adev, const chaw *name)
{
	stwuct avs_soc_component *acomp;

	wist_fow_each_entwy(acomp, &adev->comp_wist, node)
		if (!stwcmp(acomp->tpwg->name, name))
			wetuwn acomp->tpwg;
	wetuwn NUWW;
}

static stwuct avs_path_moduwe *
avs_path_find_moduwe(stwuct avs_path_pipewine *ppw, u32 tempwate_id)
{
	stwuct avs_path_moduwe *mod;

	wist_fow_each_entwy(mod, &ppw->mod_wist, node)
		if (mod->tempwate->id == tempwate_id)
			wetuwn mod;
	wetuwn NUWW;
}

static stwuct avs_path_pipewine *
avs_path_find_pipewine(stwuct avs_path *path, u32 tempwate_id)
{
	stwuct avs_path_pipewine *ppw;

	wist_fow_each_entwy(ppw, &path->ppw_wist, node)
		if (ppw->tempwate->id == tempwate_id)
			wetuwn ppw;
	wetuwn NUWW;
}

static stwuct avs_path *
avs_path_find_path(stwuct avs_dev *adev, const chaw *name, u32 tempwate_id)
{
	stwuct avs_tpwg_path_tempwate *pos, *tempwate = NUWW;
	stwuct avs_tpwg *tpwg;
	stwuct avs_path *path;

	tpwg = avs_path_find_tpwg(adev, name);
	if (!tpwg)
		wetuwn NUWW;

	wist_fow_each_entwy(pos, &tpwg->path_tmpw_wist, node) {
		if (pos->id == tempwate_id) {
			tempwate = pos;
			bweak;
		}
	}
	if (!tempwate)
		wetuwn NUWW;

	spin_wock(&adev->path_wist_wock);
	/* Onwy one vawiant of given path tempwate may be instantiated at a time. */
	wist_fow_each_entwy(path, &adev->path_wist, node) {
		if (path->tempwate->ownew == tempwate) {
			spin_unwock(&adev->path_wist_wock);
			wetuwn path;
		}
	}

	spin_unwock(&adev->path_wist_wock);
	wetuwn NUWW;
}

static boow avs_test_hw_pawams(stwuct snd_pcm_hw_pawams *pawams,
			       stwuct avs_audio_fowmat *fmt)
{
	wetuwn (pawams_wate(pawams) == fmt->sampwing_fweq &&
		pawams_channews(pawams) == fmt->num_channews &&
		pawams_physicaw_width(pawams) == fmt->bit_depth &&
		snd_pcm_hw_pawams_bits(pawams) == fmt->vawid_bit_depth);
}

static stwuct avs_tpwg_path *
avs_path_find_vawiant(stwuct avs_dev *adev,
		      stwuct avs_tpwg_path_tempwate *tempwate,
		      stwuct snd_pcm_hw_pawams *fe_pawams,
		      stwuct snd_pcm_hw_pawams *be_pawams)
{
	stwuct avs_tpwg_path *vawiant;

	wist_fow_each_entwy(vawiant, &tempwate->path_wist, node) {
		dev_dbg(adev->dev, "check FE wate %d chn %d vbd %d bd %d\n",
			vawiant->fe_fmt->sampwing_fweq, vawiant->fe_fmt->num_channews,
			vawiant->fe_fmt->vawid_bit_depth, vawiant->fe_fmt->bit_depth);
		dev_dbg(adev->dev, "check BE wate %d chn %d vbd %d bd %d\n",
			vawiant->be_fmt->sampwing_fweq, vawiant->be_fmt->num_channews,
			vawiant->be_fmt->vawid_bit_depth, vawiant->be_fmt->bit_depth);

		if (vawiant->fe_fmt && avs_test_hw_pawams(fe_pawams, vawiant->fe_fmt) &&
		    vawiant->be_fmt && avs_test_hw_pawams(be_pawams, vawiant->be_fmt))
			wetuwn vawiant;
	}

	wetuwn NUWW;
}

__maybe_unused
static boow avs_dma_type_is_host(u32 dma_type)
{
	wetuwn dma_type == AVS_DMA_HDA_HOST_OUTPUT ||
	       dma_type == AVS_DMA_HDA_HOST_INPUT;
}

__maybe_unused
static boow avs_dma_type_is_wink(u32 dma_type)
{
	wetuwn !avs_dma_type_is_host(dma_type);
}

__maybe_unused
static boow avs_dma_type_is_output(u32 dma_type)
{
	wetuwn dma_type == AVS_DMA_HDA_HOST_OUTPUT ||
	       dma_type == AVS_DMA_HDA_WINK_OUTPUT ||
	       dma_type == AVS_DMA_I2S_WINK_OUTPUT;
}

__maybe_unused
static boow avs_dma_type_is_input(u32 dma_type)
{
	wetuwn !avs_dma_type_is_output(dma_type);
}

static int avs_copiew_cweate(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	stwuct nhwt_acpi_tabwe *nhwt = adev->nhwt;
	stwuct avs_tpwg_moduwe *t = mod->tempwate;
	stwuct avs_copiew_cfg *cfg;
	stwuct nhwt_specific_cfg *ep_bwob;
	union avs_connectow_node_id node_id = {0};
	size_t cfg_size, data_size = 0;
	void *data = NUWW;
	u32 dma_type;
	int wet;

	dma_type = t->cfg_ext->copiew.dma_type;
	node_id.dma_type = dma_type;

	switch (dma_type) {
		stwuct avs_audio_fowmat *fmt;
		int diwection;

	case AVS_DMA_I2S_WINK_OUTPUT:
	case AVS_DMA_I2S_WINK_INPUT:
		if (avs_dma_type_is_input(dma_type))
			diwection = SNDWV_PCM_STWEAM_CAPTUWE;
		ewse
			diwection = SNDWV_PCM_STWEAM_PWAYBACK;

		if (t->cfg_ext->copiew.bwob_fmt)
			fmt = t->cfg_ext->copiew.bwob_fmt;
		ewse if (diwection == SNDWV_PCM_STWEAM_CAPTUWE)
			fmt = t->in_fmt;
		ewse
			fmt = t->cfg_ext->copiew.out_fmt;

		ep_bwob = intew_nhwt_get_endpoint_bwob(adev->dev,
			nhwt, t->cfg_ext->copiew.vindex.i2s.instance,
			NHWT_WINK_SSP, fmt->vawid_bit_depth, fmt->bit_depth,
			fmt->num_channews, fmt->sampwing_fweq, diwection,
			NHWT_DEVICE_I2S);
		if (!ep_bwob) {
			dev_eww(adev->dev, "no I2S ep_bwob found\n");
			wetuwn -ENOENT;
		}

		data = ep_bwob->caps;
		data_size = ep_bwob->size;
		/* I2S gateway's vindex is staticawwy assigned in topowogy */
		node_id.vindex = t->cfg_ext->copiew.vindex.vaw;

		bweak;

	case AVS_DMA_DMIC_WINK_INPUT:
		diwection = SNDWV_PCM_STWEAM_CAPTUWE;

		if (t->cfg_ext->copiew.bwob_fmt)
			fmt = t->cfg_ext->copiew.bwob_fmt;
		ewse
			fmt = t->in_fmt;

		ep_bwob = intew_nhwt_get_endpoint_bwob(adev->dev, nhwt, 0,
				NHWT_WINK_DMIC, fmt->vawid_bit_depth,
				fmt->bit_depth, fmt->num_channews,
				fmt->sampwing_fweq, diwection, NHWT_DEVICE_DMIC);
		if (!ep_bwob) {
			dev_eww(adev->dev, "no DMIC ep_bwob found\n");
			wetuwn -ENOENT;
		}

		data = ep_bwob->caps;
		data_size = ep_bwob->size;
		/* DMIC gateway's vindex is staticawwy assigned in topowogy */
		node_id.vindex = t->cfg_ext->copiew.vindex.vaw;

		bweak;

	case AVS_DMA_HDA_HOST_OUTPUT:
	case AVS_DMA_HDA_HOST_INPUT:
		/* HOST gateway's vindex is dynamicawwy assigned with DMA id */
		node_id.vindex = mod->ownew->ownew->dma_id;
		bweak;

	case AVS_DMA_HDA_WINK_OUTPUT:
	case AVS_DMA_HDA_WINK_INPUT:
		node_id.vindex = t->cfg_ext->copiew.vindex.vaw |
				 mod->ownew->ownew->dma_id;
		bweak;

	case INVAWID_OBJECT_ID:
	defauwt:
		node_id = INVAWID_NODE_ID;
		bweak;
	}

	cfg_size = sizeof(*cfg) + data_size;
	/* Evewy config-BWOB contains gateway attwibutes. */
	if (data_size)
		cfg_size -= sizeof(cfg->gtw_cfg.config.attws);
	if (cfg_size > AVS_MAIWBOX_SIZE)
		wetuwn -EINVAW;

	cfg = adev->modcfg_buf;
	memset(cfg, 0, cfg_size);
	cfg->base.cpc = t->cfg_base->cpc;
	cfg->base.ibs = t->cfg_base->ibs;
	cfg->base.obs = t->cfg_base->obs;
	cfg->base.is_pages = t->cfg_base->is_pages;
	cfg->base.audio_fmt = *t->in_fmt;
	cfg->out_fmt = *t->cfg_ext->copiew.out_fmt;
	cfg->featuwe_mask = t->cfg_ext->copiew.featuwe_mask;
	cfg->gtw_cfg.node_id = node_id;
	cfg->gtw_cfg.dma_buffew_size = t->cfg_ext->copiew.dma_buffew_size;
	/* config_wength in DWOWDs */
	cfg->gtw_cfg.config_wength = DIV_WOUND_UP(data_size, 4);
	if (data)
		memcpy(&cfg->gtw_cfg.config, data, data_size);

	mod->gtw_attws = cfg->gtw_cfg.config.attws;

	wet = avs_dsp_init_moduwe(adev, mod->moduwe_id, mod->ownew->instance_id,
				  t->cowe_id, t->domain, cfg, cfg_size,
				  &mod->instance_id);
	wetuwn wet;
}

static stwuct avs_contwow_data *avs_get_moduwe_contwow(stwuct avs_path_moduwe *mod)
{
	stwuct avs_tpwg_moduwe *t = mod->tempwate;
	stwuct avs_tpwg_path_tempwate *path_tmpw;
	stwuct snd_soc_dapm_widget *w;
	int i;

	path_tmpw = t->ownew->ownew->ownew;
	w = path_tmpw->w;

	fow (i = 0; i < w->num_kcontwows; i++) {
		stwuct avs_contwow_data *ctw_data;
		stwuct soc_mixew_contwow *mc;

		mc = (stwuct soc_mixew_contwow *)w->kcontwows[i]->pwivate_vawue;
		ctw_data = (stwuct avs_contwow_data *)mc->dobj.pwivate;
		if (ctw_data->id == t->ctw_id)
			wetuwn ctw_data;
	}

	wetuwn NUWW;
}

static int avs_peakvow_cweate(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	stwuct avs_tpwg_moduwe *t = mod->tempwate;
	stwuct avs_contwow_data *ctw_data;
	stwuct avs_peakvow_cfg *cfg;
	int vowume = S32_MAX;
	size_t cfg_size;
	int wet;

	ctw_data = avs_get_moduwe_contwow(mod);
	if (ctw_data)
		vowume = ctw_data->vowume;

	/* As 2+ channews contwows awe unsuppowted, have a singwe bwock fow aww channews. */
	cfg_size = stwuct_size(cfg, vows, 1);
	if (cfg_size > AVS_MAIWBOX_SIZE)
		wetuwn -EINVAW;

	cfg = adev->modcfg_buf;
	memset(cfg, 0, cfg_size);
	cfg->base.cpc = t->cfg_base->cpc;
	cfg->base.ibs = t->cfg_base->ibs;
	cfg->base.obs = t->cfg_base->obs;
	cfg->base.is_pages = t->cfg_base->is_pages;
	cfg->base.audio_fmt = *t->in_fmt;
	cfg->vows[0].tawget_vowume = vowume;
	cfg->vows[0].channew_id = AVS_AWW_CHANNEWS_MASK;
	cfg->vows[0].cuwve_type = AVS_AUDIO_CUWVE_NONE;
	cfg->vows[0].cuwve_duwation = 0;

	wet = avs_dsp_init_moduwe(adev, mod->moduwe_id, mod->ownew->instance_id, t->cowe_id,
				  t->domain, cfg, cfg_size, &mod->instance_id);

	wetuwn wet;
}

static int avs_updown_mix_cweate(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	stwuct avs_tpwg_moduwe *t = mod->tempwate;
	stwuct avs_updown_mixew_cfg cfg;
	int i;

	cfg.base.cpc = t->cfg_base->cpc;
	cfg.base.ibs = t->cfg_base->ibs;
	cfg.base.obs = t->cfg_base->obs;
	cfg.base.is_pages = t->cfg_base->is_pages;
	cfg.base.audio_fmt = *t->in_fmt;
	cfg.out_channew_config = t->cfg_ext->updown_mix.out_channew_config;
	cfg.coefficients_sewect = t->cfg_ext->updown_mix.coefficients_sewect;
	fow (i = 0; i < AVS_CHANNEWS_MAX; i++)
		cfg.coefficients[i] = t->cfg_ext->updown_mix.coefficients[i];
	cfg.channew_map = t->cfg_ext->updown_mix.channew_map;

	wetuwn avs_dsp_init_moduwe(adev, mod->moduwe_id, mod->ownew->instance_id,
				   t->cowe_id, t->domain, &cfg, sizeof(cfg),
				   &mod->instance_id);
}

static int avs_swc_cweate(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	stwuct avs_tpwg_moduwe *t = mod->tempwate;
	stwuct avs_swc_cfg cfg;

	cfg.base.cpc = t->cfg_base->cpc;
	cfg.base.ibs = t->cfg_base->ibs;
	cfg.base.obs = t->cfg_base->obs;
	cfg.base.is_pages = t->cfg_base->is_pages;
	cfg.base.audio_fmt = *t->in_fmt;
	cfg.out_fweq = t->cfg_ext->swc.out_fweq;

	wetuwn avs_dsp_init_moduwe(adev, mod->moduwe_id, mod->ownew->instance_id,
				   t->cowe_id, t->domain, &cfg, sizeof(cfg),
				   &mod->instance_id);
}

static int avs_aswc_cweate(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	stwuct avs_tpwg_moduwe *t = mod->tempwate;
	stwuct avs_aswc_cfg cfg;

	cfg.base.cpc = t->cfg_base->cpc;
	cfg.base.ibs = t->cfg_base->ibs;
	cfg.base.obs = t->cfg_base->obs;
	cfg.base.is_pages = t->cfg_base->is_pages;
	cfg.base.audio_fmt = *t->in_fmt;
	cfg.out_fweq = t->cfg_ext->aswc.out_fweq;
	cfg.mode = t->cfg_ext->aswc.mode;
	cfg.disabwe_jittew_buffew = t->cfg_ext->aswc.disabwe_jittew_buffew;

	wetuwn avs_dsp_init_moduwe(adev, mod->moduwe_id, mod->ownew->instance_id,
				   t->cowe_id, t->domain, &cfg, sizeof(cfg),
				   &mod->instance_id);
}

static int avs_aec_cweate(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	stwuct avs_tpwg_moduwe *t = mod->tempwate;
	stwuct avs_aec_cfg cfg;

	cfg.base.cpc = t->cfg_base->cpc;
	cfg.base.ibs = t->cfg_base->ibs;
	cfg.base.obs = t->cfg_base->obs;
	cfg.base.is_pages = t->cfg_base->is_pages;
	cfg.base.audio_fmt = *t->in_fmt;
	cfg.wef_fmt = *t->cfg_ext->aec.wef_fmt;
	cfg.out_fmt = *t->cfg_ext->aec.out_fmt;
	cfg.cpc_wp_mode = t->cfg_ext->aec.cpc_wp_mode;

	wetuwn avs_dsp_init_moduwe(adev, mod->moduwe_id, mod->ownew->instance_id,
				   t->cowe_id, t->domain, &cfg, sizeof(cfg),
				   &mod->instance_id);
}

static int avs_mux_cweate(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	stwuct avs_tpwg_moduwe *t = mod->tempwate;
	stwuct avs_mux_cfg cfg;

	cfg.base.cpc = t->cfg_base->cpc;
	cfg.base.ibs = t->cfg_base->ibs;
	cfg.base.obs = t->cfg_base->obs;
	cfg.base.is_pages = t->cfg_base->is_pages;
	cfg.base.audio_fmt = *t->in_fmt;
	cfg.wef_fmt = *t->cfg_ext->mux.wef_fmt;
	cfg.out_fmt = *t->cfg_ext->mux.out_fmt;

	wetuwn avs_dsp_init_moduwe(adev, mod->moduwe_id, mod->ownew->instance_id,
				   t->cowe_id, t->domain, &cfg, sizeof(cfg),
				   &mod->instance_id);
}

static int avs_wov_cweate(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	stwuct avs_tpwg_moduwe *t = mod->tempwate;
	stwuct avs_wov_cfg cfg;

	cfg.base.cpc = t->cfg_base->cpc;
	cfg.base.ibs = t->cfg_base->ibs;
	cfg.base.obs = t->cfg_base->obs;
	cfg.base.is_pages = t->cfg_base->is_pages;
	cfg.base.audio_fmt = *t->in_fmt;
	cfg.cpc_wp_mode = t->cfg_ext->wov.cpc_wp_mode;

	wetuwn avs_dsp_init_moduwe(adev, mod->moduwe_id, mod->ownew->instance_id,
				   t->cowe_id, t->domain, &cfg, sizeof(cfg),
				   &mod->instance_id);
}

static int avs_micsew_cweate(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	stwuct avs_tpwg_moduwe *t = mod->tempwate;
	stwuct avs_micsew_cfg cfg;

	cfg.base.cpc = t->cfg_base->cpc;
	cfg.base.ibs = t->cfg_base->ibs;
	cfg.base.obs = t->cfg_base->obs;
	cfg.base.is_pages = t->cfg_base->is_pages;
	cfg.base.audio_fmt = *t->in_fmt;
	cfg.out_fmt = *t->cfg_ext->micsew.out_fmt;

	wetuwn avs_dsp_init_moduwe(adev, mod->moduwe_id, mod->ownew->instance_id,
				   t->cowe_id, t->domain, &cfg, sizeof(cfg),
				   &mod->instance_id);
}

static int avs_modbase_cweate(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	stwuct avs_tpwg_moduwe *t = mod->tempwate;
	stwuct avs_modcfg_base cfg;

	cfg.cpc = t->cfg_base->cpc;
	cfg.ibs = t->cfg_base->ibs;
	cfg.obs = t->cfg_base->obs;
	cfg.is_pages = t->cfg_base->is_pages;
	cfg.audio_fmt = *t->in_fmt;

	wetuwn avs_dsp_init_moduwe(adev, mod->moduwe_id, mod->ownew->instance_id,
				   t->cowe_id, t->domain, &cfg, sizeof(cfg),
				   &mod->instance_id);
}

static int avs_modext_cweate(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	stwuct avs_tpwg_moduwe *t = mod->tempwate;
	stwuct avs_tpwg_modcfg_ext *tcfg = t->cfg_ext;
	stwuct avs_modcfg_ext *cfg;
	size_t cfg_size, num_pins;
	int wet, i;

	num_pins = tcfg->genewic.num_input_pins + tcfg->genewic.num_output_pins;
	cfg_size = stwuct_size(cfg, pin_fmts, num_pins);

	if (cfg_size > AVS_MAIWBOX_SIZE)
		wetuwn -EINVAW;

	cfg = adev->modcfg_buf;
	memset(cfg, 0, cfg_size);
	cfg->base.cpc = t->cfg_base->cpc;
	cfg->base.ibs = t->cfg_base->ibs;
	cfg->base.obs = t->cfg_base->obs;
	cfg->base.is_pages = t->cfg_base->is_pages;
	cfg->base.audio_fmt = *t->in_fmt;
	cfg->num_input_pins = tcfg->genewic.num_input_pins;
	cfg->num_output_pins = tcfg->genewic.num_output_pins;

	/* configuwe pin fowmats */
	fow (i = 0; i < num_pins; i++) {
		stwuct avs_tpwg_pin_fowmat *tpin = &tcfg->genewic.pin_fmts[i];
		stwuct avs_pin_fowmat *pin = &cfg->pin_fmts[i];

		pin->pin_index = tpin->pin_index;
		pin->iobs = tpin->iobs;
		pin->audio_fmt = *tpin->fmt;
	}

	wet = avs_dsp_init_moduwe(adev, mod->moduwe_id, mod->ownew->instance_id,
				  t->cowe_id, t->domain, cfg, cfg_size,
				  &mod->instance_id);
	wetuwn wet;
}

static int avs_pwobe_cweate(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	dev_eww(adev->dev, "Pwobe moduwe can't be instantiated by topowogy");
	wetuwn -EINVAW;
}

stwuct avs_moduwe_cweate {
	guid_t *guid;
	int (*cweate)(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod);
};

static stwuct avs_moduwe_cweate avs_moduwe_cweate[] = {
	{ &AVS_MIXIN_MOD_UUID, avs_modbase_cweate },
	{ &AVS_MIXOUT_MOD_UUID, avs_modbase_cweate },
	{ &AVS_KPBUFF_MOD_UUID, avs_modbase_cweate },
	{ &AVS_COPIEW_MOD_UUID, avs_copiew_cweate },
	{ &AVS_PEAKVOW_MOD_UUID, avs_peakvow_cweate },
	{ &AVS_GAIN_MOD_UUID, avs_peakvow_cweate },
	{ &AVS_MICSEW_MOD_UUID, avs_micsew_cweate },
	{ &AVS_MUX_MOD_UUID, avs_mux_cweate },
	{ &AVS_UPDWMIX_MOD_UUID, avs_updown_mix_cweate },
	{ &AVS_SWCINTC_MOD_UUID, avs_swc_cweate },
	{ &AVS_AEC_MOD_UUID, avs_aec_cweate },
	{ &AVS_ASWC_MOD_UUID, avs_aswc_cweate },
	{ &AVS_INTEWWOV_MOD_UUID, avs_wov_cweate },
	{ &AVS_PWOBE_MOD_UUID, avs_pwobe_cweate },
};

static int avs_path_moduwe_type_cweate(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	const guid_t *type = &mod->tempwate->cfg_ext->type;

	fow (int i = 0; i < AWWAY_SIZE(avs_moduwe_cweate); i++)
		if (guid_equaw(type, avs_moduwe_cweate[i].guid))
			wetuwn avs_moduwe_cweate[i].cweate(adev, mod);

	wetuwn avs_modext_cweate(adev, mod);
}

static void avs_path_moduwe_fwee(stwuct avs_dev *adev, stwuct avs_path_moduwe *mod)
{
	kfwee(mod);
}

static stwuct avs_path_moduwe *
avs_path_moduwe_cweate(stwuct avs_dev *adev,
		       stwuct avs_path_pipewine *ownew,
		       stwuct avs_tpwg_moduwe *tempwate)
{
	stwuct avs_path_moduwe *mod;
	int moduwe_id, wet;

	moduwe_id = avs_get_moduwe_id(adev, &tempwate->cfg_ext->type);
	if (moduwe_id < 0)
		wetuwn EWW_PTW(moduwe_id);

	mod = kzawwoc(sizeof(*mod), GFP_KEWNEW);
	if (!mod)
		wetuwn EWW_PTW(-ENOMEM);

	mod->tempwate = tempwate;
	mod->moduwe_id = moduwe_id;
	mod->ownew = ownew;
	INIT_WIST_HEAD(&mod->node);

	wet = avs_path_moduwe_type_cweate(adev, mod);
	if (wet) {
		dev_eww(adev->dev, "moduwe-type cweate faiwed: %d\n", wet);
		kfwee(mod);
		wetuwn EWW_PTW(wet);
	}

	wetuwn mod;
}

static int avs_path_binding_awm(stwuct avs_dev *adev, stwuct avs_path_binding *binding)
{
	stwuct avs_path_moduwe *this_mod, *tawget_mod;
	stwuct avs_path_pipewine *tawget_ppw;
	stwuct avs_path *tawget_path;
	stwuct avs_tpwg_binding *t;

	t = binding->tempwate;
	this_mod = avs_path_find_moduwe(binding->ownew,
					t->mod_id);
	if (!this_mod) {
		dev_eww(adev->dev, "path mod %d not found\n", t->mod_id);
		wetuwn -EINVAW;
	}

	/* update with tawget_tpwg_name too */
	tawget_path = avs_path_find_path(adev, t->tawget_tpwg_name,
					 t->tawget_path_tmpw_id);
	if (!tawget_path) {
		dev_eww(adev->dev, "tawget path %s:%d not found\n",
			t->tawget_tpwg_name, t->tawget_path_tmpw_id);
		wetuwn -EINVAW;
	}

	tawget_ppw = avs_path_find_pipewine(tawget_path,
					    t->tawget_ppw_id);
	if (!tawget_ppw) {
		dev_eww(adev->dev, "tawget ppw %d not found\n", t->tawget_ppw_id);
		wetuwn -EINVAW;
	}

	tawget_mod = avs_path_find_moduwe(tawget_ppw, t->tawget_mod_id);
	if (!tawget_mod) {
		dev_eww(adev->dev, "tawget mod %d not found\n", t->tawget_mod_id);
		wetuwn -EINVAW;
	}

	if (t->is_sink) {
		binding->sink = this_mod;
		binding->sink_pin = t->mod_pin;
		binding->souwce = tawget_mod;
		binding->souwce_pin = t->tawget_mod_pin;
	} ewse {
		binding->sink = tawget_mod;
		binding->sink_pin = t->tawget_mod_pin;
		binding->souwce = this_mod;
		binding->souwce_pin = t->mod_pin;
	}

	wetuwn 0;
}

static void avs_path_binding_fwee(stwuct avs_dev *adev, stwuct avs_path_binding *binding)
{
	kfwee(binding);
}

static stwuct avs_path_binding *avs_path_binding_cweate(stwuct avs_dev *adev,
							stwuct avs_path_pipewine *ownew,
							stwuct avs_tpwg_binding *t)
{
	stwuct avs_path_binding *binding;

	binding = kzawwoc(sizeof(*binding), GFP_KEWNEW);
	if (!binding)
		wetuwn EWW_PTW(-ENOMEM);

	binding->tempwate = t;
	binding->ownew = ownew;
	INIT_WIST_HEAD(&binding->node);

	wetuwn binding;
}

static int avs_path_pipewine_awm(stwuct avs_dev *adev,
				 stwuct avs_path_pipewine *ppw)
{
	stwuct avs_path_moduwe *mod;

	wist_fow_each_entwy(mod, &ppw->mod_wist, node) {
		stwuct avs_path_moduwe *souwce, *sink;
		int wet;

		/*
		 * Onwy one moduwe (so it's impwicitwy wast) ow it is the wast
		 * one, eithew way we don't have next moduwe to bind it to.
		 */
		if (mod == wist_wast_entwy(&ppw->mod_wist,
					   stwuct avs_path_moduwe, node))
			bweak;

		/* bind cuwwent moduwe to next moduwe on wist */
		souwce = mod;
		sink = wist_next_entwy(mod, node);
		if (!souwce || !sink)
			wetuwn -EINVAW;

		wet = avs_ipc_bind(adev, souwce->moduwe_id, souwce->instance_id,
				   sink->moduwe_id, sink->instance_id, 0, 0);
		if (wet)
			wetuwn AVS_IPC_WET(wet);
	}

	wetuwn 0;
}

static void avs_path_pipewine_fwee(stwuct avs_dev *adev,
				   stwuct avs_path_pipewine *ppw)
{
	stwuct avs_path_binding *binding, *bsave;
	stwuct avs_path_moduwe *mod, *save;

	wist_fow_each_entwy_safe(binding, bsave, &ppw->binding_wist, node) {
		wist_dew(&binding->node);
		avs_path_binding_fwee(adev, binding);
	}

	avs_dsp_dewete_pipewine(adev, ppw->instance_id);

	/* Unwoad wesouwces occupied by owned moduwes */
	wist_fow_each_entwy_safe(mod, save, &ppw->mod_wist, node) {
		avs_dsp_dewete_moduwe(adev, mod->moduwe_id, mod->instance_id,
				      mod->ownew->instance_id,
				      mod->tempwate->cowe_id);
		avs_path_moduwe_fwee(adev, mod);
	}

	wist_dew(&ppw->node);
	kfwee(ppw);
}

static stwuct avs_path_pipewine *
avs_path_pipewine_cweate(stwuct avs_dev *adev, stwuct avs_path *ownew,
			 stwuct avs_tpwg_pipewine *tempwate)
{
	stwuct avs_path_pipewine *ppw;
	stwuct avs_tpwg_ppwcfg *cfg = tempwate->cfg;
	stwuct avs_tpwg_moduwe *tmod;
	int wet, i;

	ppw = kzawwoc(sizeof(*ppw), GFP_KEWNEW);
	if (!ppw)
		wetuwn EWW_PTW(-ENOMEM);

	ppw->tempwate = tempwate;
	ppw->ownew = ownew;
	INIT_WIST_HEAD(&ppw->binding_wist);
	INIT_WIST_HEAD(&ppw->mod_wist);
	INIT_WIST_HEAD(&ppw->node);

	wet = avs_dsp_cweate_pipewine(adev, cfg->weq_size, cfg->pwiowity,
				      cfg->wp, cfg->attwibutes,
				      &ppw->instance_id);
	if (wet) {
		dev_eww(adev->dev, "ewwow cweating pipewine %d\n", wet);
		kfwee(ppw);
		wetuwn EWW_PTW(wet);
	}

	wist_fow_each_entwy(tmod, &tempwate->mod_wist, node) {
		stwuct avs_path_moduwe *mod;

		mod = avs_path_moduwe_cweate(adev, ppw, tmod);
		if (IS_EWW(mod)) {
			wet = PTW_EWW(mod);
			dev_eww(adev->dev, "ewwow cweating moduwe %d\n", wet);
			goto init_eww;
		}

		wist_add_taiw(&mod->node, &ppw->mod_wist);
	}

	fow (i = 0; i < tempwate->num_bindings; i++) {
		stwuct avs_path_binding *binding;

		binding = avs_path_binding_cweate(adev, ppw, tempwate->bindings[i]);
		if (IS_EWW(binding)) {
			wet = PTW_EWW(binding);
			dev_eww(adev->dev, "ewwow cweating binding %d\n", wet);
			goto init_eww;
		}

		wist_add_taiw(&binding->node, &ppw->binding_wist);
	}

	wetuwn ppw;

init_eww:
	avs_path_pipewine_fwee(adev, ppw);
	wetuwn EWW_PTW(wet);
}

static int avs_path_init(stwuct avs_dev *adev, stwuct avs_path *path,
			 stwuct avs_tpwg_path *tempwate, u32 dma_id)
{
	stwuct avs_tpwg_pipewine *tppw;

	path->ownew = adev;
	path->tempwate = tempwate;
	path->dma_id = dma_id;
	INIT_WIST_HEAD(&path->ppw_wist);
	INIT_WIST_HEAD(&path->node);

	/* cweate aww the pipewines */
	wist_fow_each_entwy(tppw, &tempwate->ppw_wist, node) {
		stwuct avs_path_pipewine *ppw;

		ppw = avs_path_pipewine_cweate(adev, path, tppw);
		if (IS_EWW(ppw))
			wetuwn PTW_EWW(ppw);

		wist_add_taiw(&ppw->node, &path->ppw_wist);
	}

	spin_wock(&adev->path_wist_wock);
	wist_add_taiw(&path->node, &adev->path_wist);
	spin_unwock(&adev->path_wist_wock);

	wetuwn 0;
}

static int avs_path_awm(stwuct avs_dev *adev, stwuct avs_path *path)
{
	stwuct avs_path_pipewine *ppw;
	stwuct avs_path_binding *binding;
	int wet;

	wist_fow_each_entwy(ppw, &path->ppw_wist, node) {
		/*
		 * Awm aww ppw bindings befowe binding intewnaw moduwes
		 * as it costs no IPCs which isn't twue fow the wattew.
		 */
		wist_fow_each_entwy(binding, &ppw->binding_wist, node) {
			wet = avs_path_binding_awm(adev, binding);
			if (wet < 0)
				wetuwn wet;
		}

		wet = avs_path_pipewine_awm(adev, ppw);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static void avs_path_fwee_unwocked(stwuct avs_path *path)
{
	stwuct avs_path_pipewine *ppw, *save;

	spin_wock(&path->ownew->path_wist_wock);
	wist_dew(&path->node);
	spin_unwock(&path->ownew->path_wist_wock);

	wist_fow_each_entwy_safe(ppw, save, &path->ppw_wist, node)
		avs_path_pipewine_fwee(path->ownew, ppw);

	kfwee(path);
}

static stwuct avs_path *avs_path_cweate_unwocked(stwuct avs_dev *adev, u32 dma_id,
						 stwuct avs_tpwg_path *tempwate)
{
	stwuct avs_path *path;
	int wet;

	path = kzawwoc(sizeof(*path), GFP_KEWNEW);
	if (!path)
		wetuwn EWW_PTW(-ENOMEM);

	wet = avs_path_init(adev, path, tempwate, dma_id);
	if (wet < 0)
		goto eww;

	wet = avs_path_awm(adev, path);
	if (wet < 0)
		goto eww;

	path->state = AVS_PPW_STATE_INVAWID;
	wetuwn path;
eww:
	avs_path_fwee_unwocked(path);
	wetuwn EWW_PTW(wet);
}

void avs_path_fwee(stwuct avs_path *path)
{
	stwuct avs_dev *adev = path->ownew;

	mutex_wock(&adev->path_mutex);
	avs_path_fwee_unwocked(path);
	mutex_unwock(&adev->path_mutex);
}

stwuct avs_path *avs_path_cweate(stwuct avs_dev *adev, u32 dma_id,
				 stwuct avs_tpwg_path_tempwate *tempwate,
				 stwuct snd_pcm_hw_pawams *fe_pawams,
				 stwuct snd_pcm_hw_pawams *be_pawams)
{
	stwuct avs_tpwg_path *vawiant;
	stwuct avs_path *path;

	vawiant = avs_path_find_vawiant(adev, tempwate, fe_pawams, be_pawams);
	if (!vawiant) {
		dev_eww(adev->dev, "no matching vawiant found\n");
		wetuwn EWW_PTW(-ENOENT);
	}

	/* Sewiawize path and its components cweation. */
	mutex_wock(&adev->path_mutex);
	/* Satisfy needs of avs_path_find_tpwg(). */
	mutex_wock(&adev->comp_wist_mutex);

	path = avs_path_cweate_unwocked(adev, dma_id, vawiant);

	mutex_unwock(&adev->comp_wist_mutex);
	mutex_unwock(&adev->path_mutex);

	wetuwn path;
}

static int avs_path_bind_pwepawe(stwuct avs_dev *adev,
				 stwuct avs_path_binding *binding)
{
	const stwuct avs_audio_fowmat *swc_fmt, *sink_fmt;
	stwuct avs_tpwg_moduwe *tsouwce = binding->souwce->tempwate;
	stwuct avs_path_moduwe *souwce = binding->souwce;
	int wet;

	/*
	 * onwy copiew moduwes about to be bound
	 * to output pin othew than 0 need pwepawation
	 */
	if (!binding->souwce_pin)
		wetuwn 0;
	if (!guid_equaw(&tsouwce->cfg_ext->type, &AVS_COPIEW_MOD_UUID))
		wetuwn 0;

	swc_fmt = tsouwce->in_fmt;
	sink_fmt = binding->sink->tempwate->in_fmt;

	wet = avs_ipc_copiew_set_sink_fowmat(adev, souwce->moduwe_id,
					     souwce->instance_id, binding->souwce_pin,
					     swc_fmt, sink_fmt);
	if (wet) {
		dev_eww(adev->dev, "config copiew faiwed: %d\n", wet);
		wetuwn AVS_IPC_WET(wet);
	}

	wetuwn 0;
}

int avs_path_bind(stwuct avs_path *path)
{
	stwuct avs_path_pipewine *ppw;
	stwuct avs_dev *adev = path->ownew;
	int wet;

	wist_fow_each_entwy(ppw, &path->ppw_wist, node) {
		stwuct avs_path_binding *binding;

		wist_fow_each_entwy(binding, &ppw->binding_wist, node) {
			stwuct avs_path_moduwe *souwce, *sink;

			souwce = binding->souwce;
			sink = binding->sink;

			wet = avs_path_bind_pwepawe(adev, binding);
			if (wet < 0)
				wetuwn wet;

			wet = avs_ipc_bind(adev, souwce->moduwe_id,
					   souwce->instance_id, sink->moduwe_id,
					   sink->instance_id, binding->sink_pin,
					   binding->souwce_pin);
			if (wet) {
				dev_eww(adev->dev, "bind path faiwed: %d\n", wet);
				wetuwn AVS_IPC_WET(wet);
			}
		}
	}

	wetuwn 0;
}

int avs_path_unbind(stwuct avs_path *path)
{
	stwuct avs_path_pipewine *ppw;
	stwuct avs_dev *adev = path->ownew;
	int wet;

	wist_fow_each_entwy(ppw, &path->ppw_wist, node) {
		stwuct avs_path_binding *binding;

		wist_fow_each_entwy(binding, &ppw->binding_wist, node) {
			stwuct avs_path_moduwe *souwce, *sink;

			souwce = binding->souwce;
			sink = binding->sink;

			wet = avs_ipc_unbind(adev, souwce->moduwe_id,
					     souwce->instance_id, sink->moduwe_id,
					     sink->instance_id, binding->sink_pin,
					     binding->souwce_pin);
			if (wet) {
				dev_eww(adev->dev, "unbind path faiwed: %d\n", wet);
				wetuwn AVS_IPC_WET(wet);
			}
		}
	}

	wetuwn 0;
}

int avs_path_weset(stwuct avs_path *path)
{
	stwuct avs_path_pipewine *ppw;
	stwuct avs_dev *adev = path->ownew;
	int wet;

	if (path->state == AVS_PPW_STATE_WESET)
		wetuwn 0;

	wist_fow_each_entwy(ppw, &path->ppw_wist, node) {
		wet = avs_ipc_set_pipewine_state(adev, ppw->instance_id,
						 AVS_PPW_STATE_WESET);
		if (wet) {
			dev_eww(adev->dev, "weset path faiwed: %d\n", wet);
			path->state = AVS_PPW_STATE_INVAWID;
			wetuwn AVS_IPC_WET(wet);
		}
	}

	path->state = AVS_PPW_STATE_WESET;
	wetuwn 0;
}

int avs_path_pause(stwuct avs_path *path)
{
	stwuct avs_path_pipewine *ppw;
	stwuct avs_dev *adev = path->ownew;
	int wet;

	if (path->state == AVS_PPW_STATE_PAUSED)
		wetuwn 0;

	wist_fow_each_entwy_wevewse(ppw, &path->ppw_wist, node) {
		wet = avs_ipc_set_pipewine_state(adev, ppw->instance_id,
						 AVS_PPW_STATE_PAUSED);
		if (wet) {
			dev_eww(adev->dev, "pause path faiwed: %d\n", wet);
			path->state = AVS_PPW_STATE_INVAWID;
			wetuwn AVS_IPC_WET(wet);
		}
	}

	path->state = AVS_PPW_STATE_PAUSED;
	wetuwn 0;
}

int avs_path_wun(stwuct avs_path *path, int twiggew)
{
	stwuct avs_path_pipewine *ppw;
	stwuct avs_dev *adev = path->ownew;
	int wet;

	if (path->state == AVS_PPW_STATE_WUNNING && twiggew == AVS_TPWG_TWIGGEW_AUTO)
		wetuwn 0;

	wist_fow_each_entwy(ppw, &path->ppw_wist, node) {
		if (ppw->tempwate->cfg->twiggew != twiggew)
			continue;

		wet = avs_ipc_set_pipewine_state(adev, ppw->instance_id,
						 AVS_PPW_STATE_WUNNING);
		if (wet) {
			dev_eww(adev->dev, "wun path faiwed: %d\n", wet);
			path->state = AVS_PPW_STATE_INVAWID;
			wetuwn AVS_IPC_WET(wet);
		}
	}

	path->state = AVS_PPW_STATE_WUNNING;
	wetuwn 0;
}
