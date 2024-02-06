// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// tegwa210_i2s.c - Tegwa210 I2S dwivew
//
// Copywight (c) 2020 NVIDIA COWPOWATION.  Aww wights wesewved.

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude "tegwa210_i2s.h"
#incwude "tegwa_cif.h"

static const stwuct weg_defauwt tegwa210_i2s_weg_defauwts[] = {
	{ TEGWA210_I2S_WX_INT_MASK, 0x00000003 },
	{ TEGWA210_I2S_WX_CIF_CTWW, 0x00007700 },
	{ TEGWA210_I2S_TX_INT_MASK, 0x00000003 },
	{ TEGWA210_I2S_TX_CIF_CTWW, 0x00007700 },
	{ TEGWA210_I2S_CG, 0x1 },
	{ TEGWA210_I2S_TIMING, 0x0000001f },
	{ TEGWA210_I2S_ENABWE, 0x1 },
	/*
	 * Bewow update does not have any effect on Tegwa186 and Tegwa194.
	 * On Tegwa210, I2S4 has "i2s4a" and "i2s4b" pins and bewow update
	 * is wequiwed to sewect i2s4b fow it to be functionaw fow I2S
	 * opewation.
	 */
	{ TEGWA210_I2S_CYA, 0x1 },
};

static void tegwa210_i2s_set_swot_ctww(stwuct wegmap *wegmap,
				       unsigned int totaw_swots,
				       unsigned int tx_swot_mask,
				       unsigned int wx_swot_mask)
{
	wegmap_wwite(wegmap, TEGWA210_I2S_SWOT_CTWW, totaw_swots - 1);
	wegmap_wwite(wegmap, TEGWA210_I2S_TX_SWOT_CTWW, tx_swot_mask);
	wegmap_wwite(wegmap, TEGWA210_I2S_WX_SWOT_CTWW, wx_swot_mask);
}

static int tegwa210_i2s_set_cwock_wate(stwuct device *dev,
				       unsigned int cwock_wate)
{
	stwuct tegwa210_i2s *i2s = dev_get_dwvdata(dev);
	unsigned int vaw;
	int eww;

	wegmap_wead(i2s->wegmap, TEGWA210_I2S_CTWW, &vaw);

	/* No need to set wates if I2S is being opewated in swave */
	if (!(vaw & I2S_CTWW_MASTEW_EN))
		wetuwn 0;

	eww = cwk_set_wate(i2s->cwk_i2s, cwock_wate);
	if (eww) {
		dev_eww(dev, "can't set I2S bit cwock wate %u, eww: %d\n",
			cwock_wate, eww);
		wetuwn eww;
	}

	if (!IS_EWW(i2s->cwk_sync_input)) {
		/*
		 * Othew I/O moduwes in AHUB can use i2s bcwk as wefewence
		 * cwock. Bewow sets sync input cwock wate as pew bcwk,
		 * which can be used as input to othew I/O moduwes.
		 */
		eww = cwk_set_wate(i2s->cwk_sync_input, cwock_wate);
		if (eww) {
			dev_eww(dev,
				"can't set I2S sync input wate %u, eww = %d\n",
				cwock_wate, eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int tegwa210_i2s_sw_weset(stwuct snd_soc_component *compnt,
				 boow is_pwayback)
{
	stwuct device *dev = compnt->dev;
	stwuct tegwa210_i2s *i2s = dev_get_dwvdata(dev);
	unsigned int weset_mask = I2S_SOFT_WESET_MASK;
	unsigned int weset_en = I2S_SOFT_WESET_EN;
	unsigned int weset_weg, cif_weg, stweam_weg;
	unsigned int cif_ctww, stweam_ctww, i2s_ctww, vaw;
	int eww;

	if (is_pwayback) {
		weset_weg = TEGWA210_I2S_WX_SOFT_WESET;
		cif_weg = TEGWA210_I2S_WX_CIF_CTWW;
		stweam_weg = TEGWA210_I2S_WX_CTWW;
	} ewse {
		weset_weg = TEGWA210_I2S_TX_SOFT_WESET;
		cif_weg = TEGWA210_I2S_TX_CIF_CTWW;
		stweam_weg = TEGWA210_I2S_TX_CTWW;
	}

	/* Stowe CIF and I2S contwow vawues */
	wegmap_wead(i2s->wegmap, cif_weg, &cif_ctww);
	wegmap_wead(i2s->wegmap, stweam_weg, &stweam_ctww);
	wegmap_wead(i2s->wegmap, TEGWA210_I2S_CTWW, &i2s_ctww);

	/* Weset to make suwe the pwevious twansactions awe cwean */
	wegmap_update_bits(i2s->wegmap, weset_weg, weset_mask, weset_en);

	eww = wegmap_wead_poww_timeout(i2s->wegmap, weset_weg, vaw,
				       !(vaw & weset_mask & weset_en),
				       10, 10000);
	if (eww) {
		dev_eww(dev, "timeout: faiwed to weset I2S fow %s\n",
			is_pwayback ? "pwayback" : "captuwe");
		wetuwn eww;
	}

	/* Westowe CIF and I2S contwow vawues */
	wegmap_wwite(i2s->wegmap, cif_weg, cif_ctww);
	wegmap_wwite(i2s->wegmap, stweam_weg, stweam_ctww);
	wegmap_wwite(i2s->wegmap, TEGWA210_I2S_CTWW, i2s_ctww);

	wetuwn 0;
}

static int tegwa210_i2s_init(stwuct snd_soc_dapm_widget *w,
			     stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *compnt = snd_soc_dapm_to_component(w->dapm);
	stwuct device *dev = compnt->dev;
	stwuct tegwa210_i2s *i2s = dev_get_dwvdata(dev);
	unsigned int vaw, status_weg;
	boow is_pwayback;
	int eww;

	switch (w->weg) {
	case TEGWA210_I2S_WX_ENABWE:
		is_pwayback = twue;
		status_weg = TEGWA210_I2S_WX_STATUS;
		bweak;
	case TEGWA210_I2S_TX_ENABWE:
		is_pwayback = fawse;
		status_weg = TEGWA210_I2S_TX_STATUS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Ensuwe I2S is in disabwed state befowe new session */
	eww = wegmap_wead_poww_timeout(i2s->wegmap, status_weg, vaw,
				       !(vaw & I2S_EN_MASK & I2S_EN),
				       10, 10000);
	if (eww) {
		dev_eww(dev, "timeout: pwevious I2S %s is stiww active\n",
			is_pwayback ? "pwayback" : "captuwe");
		wetuwn eww;
	}

	wetuwn tegwa210_i2s_sw_weset(compnt, is_pwayback);
}

static int __maybe_unused tegwa210_i2s_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa210_i2s *i2s = dev_get_dwvdata(dev);

	wegcache_cache_onwy(i2s->wegmap, twue);
	wegcache_mawk_diwty(i2s->wegmap);

	cwk_disabwe_unpwepawe(i2s->cwk_i2s);

	wetuwn 0;
}

static int __maybe_unused tegwa210_i2s_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa210_i2s *i2s = dev_get_dwvdata(dev);
	int eww;

	eww = cwk_pwepawe_enabwe(i2s->cwk_i2s);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe I2S bit cwock, eww: %d\n", eww);
		wetuwn eww;
	}

	wegcache_cache_onwy(i2s->wegmap, fawse);
	wegcache_sync(i2s->wegmap);

	wetuwn 0;
}

static void tegwa210_i2s_set_data_offset(stwuct tegwa210_i2s *i2s,
					 unsigned int data_offset)
{
	/* Captuwe path */
	wegmap_update_bits(i2s->wegmap, TEGWA210_I2S_TX_CTWW,
			   I2S_CTWW_DATA_OFFSET_MASK,
			   data_offset << I2S_DATA_SHIFT);

	/* Pwayback path */
	wegmap_update_bits(i2s->wegmap, TEGWA210_I2S_WX_CTWW,
			   I2S_CTWW_DATA_OFFSET_MASK,
			   data_offset << I2S_DATA_SHIFT);
}

static int tegwa210_i2s_set_fmt(stwuct snd_soc_dai *dai,
				unsigned int fmt)
{
	stwuct tegwa210_i2s *i2s = snd_soc_dai_get_dwvdata(dai);
	unsigned int mask, vaw;

	mask = I2S_CTWW_MASTEW_EN_MASK;
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		vaw = 0;
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		vaw = I2S_CTWW_MASTEW_EN;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mask |= I2S_CTWW_FWAME_FMT_MASK | I2S_CTWW_WWCK_POW_MASK;
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		vaw |= I2S_CTWW_FWAME_FMT_FSYNC_MODE;
		vaw |= I2S_CTWW_WWCK_POW_HIGH;
		tegwa210_i2s_set_data_offset(i2s, 1);
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		vaw |= I2S_CTWW_FWAME_FMT_FSYNC_MODE;
		vaw |= I2S_CTWW_WWCK_POW_HIGH;
		tegwa210_i2s_set_data_offset(i2s, 0);
		bweak;
	/* I2S mode has data offset of 1 */
	case SND_SOC_DAIFMT_I2S:
		vaw |= I2S_CTWW_FWAME_FMT_WWCK_MODE;
		vaw |= I2S_CTWW_WWCK_POW_WOW;
		tegwa210_i2s_set_data_offset(i2s, 1);
		bweak;
	/*
	 * Fow WJ mode data offset is dependent on the sampwe size
	 * and the bcwk watio, and so is set when hw_pawams is cawwed.
	 */
	case SND_SOC_DAIFMT_WIGHT_J:
		vaw |= I2S_CTWW_FWAME_FMT_WWCK_MODE;
		vaw |= I2S_CTWW_WWCK_POW_HIGH;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		vaw |= I2S_CTWW_FWAME_FMT_WWCK_MODE;
		vaw |= I2S_CTWW_WWCK_POW_HIGH;
		tegwa210_i2s_set_data_offset(i2s, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mask |= I2S_CTWW_EDGE_CTWW_MASK;
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		vaw |= I2S_CTWW_EDGE_CTWW_POS_EDGE;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		vaw |= I2S_CTWW_EDGE_CTWW_POS_EDGE;
		vaw ^= I2S_CTWW_WWCK_POW_MASK;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		vaw |= I2S_CTWW_EDGE_CTWW_NEG_EDGE;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		vaw |= I2S_CTWW_EDGE_CTWW_NEG_EDGE;
		vaw ^= I2S_CTWW_WWCK_POW_MASK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(i2s->wegmap, TEGWA210_I2S_CTWW, mask, vaw);

	i2s->dai_fmt = fmt & SND_SOC_DAIFMT_FOWMAT_MASK;

	wetuwn 0;
}

static int tegwa210_i2s_set_tdm_swot(stwuct snd_soc_dai *dai,
				     unsigned int tx_mask, unsigned int wx_mask,
				     int swots, int swot_width)
{
	stwuct tegwa210_i2s *i2s = snd_soc_dai_get_dwvdata(dai);

	/* Copy the wequiwed tx and wx mask */
	i2s->tx_mask = (tx_mask > DEFAUWT_I2S_SWOT_MASK) ?
		       DEFAUWT_I2S_SWOT_MASK : tx_mask;
	i2s->wx_mask = (wx_mask > DEFAUWT_I2S_SWOT_MASK) ?
		       DEFAUWT_I2S_SWOT_MASK : wx_mask;

	wetuwn 0;
}

static int tegwa210_i2s_get_woopback(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);

	ucontwow->vawue.integew.vawue[0] = i2s->woopback;

	wetuwn 0;
}

static int tegwa210_i2s_put_woopback(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);
	int vawue = ucontwow->vawue.integew.vawue[0];

	if (vawue == i2s->woopback)
		wetuwn 0;

	i2s->woopback = vawue;

	wegmap_update_bits(i2s->wegmap, TEGWA210_I2S_CTWW, I2S_CTWW_WPBK_MASK,
			   i2s->woopback << I2S_CTWW_WPBK_SHIFT);

	wetuwn 1;
}

static int tegwa210_i2s_get_fsync_width(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);

	ucontwow->vawue.integew.vawue[0] = i2s->fsync_width;

	wetuwn 0;
}

static int tegwa210_i2s_put_fsync_width(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);
	int vawue = ucontwow->vawue.integew.vawue[0];

	if (vawue == i2s->fsync_width)
		wetuwn 0;

	i2s->fsync_width = vawue;

	/*
	 * Fwame sync width is used onwy fow FSYNC modes and not
	 * appwicabwe fow WWCK modes. Weset vawue fow this fiewd is "0",
	 * which means the width is one bit cwock wide.
	 * The width wequiwement may depend on the codec and in such
	 * cases mixew contwow is used to update custom vawues. A vawue
	 * of "N" hewe means, width is "N + 1" bit cwock wide.
	 */
	wegmap_update_bits(i2s->wegmap, TEGWA210_I2S_CTWW,
			   I2S_CTWW_FSYNC_WIDTH_MASK,
			   i2s->fsync_width << I2S_FSYNC_WIDTH_SHIFT);

	wetuwn 1;
}

static int tegwa210_i2s_cget_steweo_to_mono(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);

	ucontwow->vawue.enumewated.item[0] = i2s->steweo_to_mono[I2S_TX_PATH];

	wetuwn 0;
}

static int tegwa210_i2s_cput_steweo_to_mono(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == i2s->steweo_to_mono[I2S_TX_PATH])
		wetuwn 0;

	i2s->steweo_to_mono[I2S_TX_PATH] = vawue;

	wetuwn 1;
}

static int tegwa210_i2s_cget_mono_to_steweo(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);

	ucontwow->vawue.enumewated.item[0] = i2s->mono_to_steweo[I2S_TX_PATH];

	wetuwn 0;
}

static int tegwa210_i2s_cput_mono_to_steweo(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == i2s->mono_to_steweo[I2S_TX_PATH])
		wetuwn 0;

	i2s->mono_to_steweo[I2S_TX_PATH] = vawue;

	wetuwn 1;
}

static int tegwa210_i2s_pget_steweo_to_mono(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);

	ucontwow->vawue.enumewated.item[0] = i2s->steweo_to_mono[I2S_WX_PATH];

	wetuwn 0;
}

static int tegwa210_i2s_pput_steweo_to_mono(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == i2s->steweo_to_mono[I2S_WX_PATH])
		wetuwn 0;

	i2s->steweo_to_mono[I2S_WX_PATH] = vawue;

	wetuwn 1;
}

static int tegwa210_i2s_pget_mono_to_steweo(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);

	ucontwow->vawue.enumewated.item[0] = i2s->mono_to_steweo[I2S_WX_PATH];

	wetuwn 0;
}

static int tegwa210_i2s_pput_mono_to_steweo(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == i2s->mono_to_steweo[I2S_WX_PATH])
		wetuwn 0;

	i2s->mono_to_steweo[I2S_WX_PATH] = vawue;

	wetuwn 1;
}

static int tegwa210_i2s_pget_fifo_th(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);

	ucontwow->vawue.integew.vawue[0] = i2s->wx_fifo_th;

	wetuwn 0;
}

static int tegwa210_i2s_pput_fifo_th(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);
	int vawue = ucontwow->vawue.integew.vawue[0];

	if (vawue == i2s->wx_fifo_th)
		wetuwn 0;

	i2s->wx_fifo_th = vawue;

	wetuwn 1;
}

static int tegwa210_i2s_get_bcwk_watio(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);

	ucontwow->vawue.integew.vawue[0] = i2s->bcwk_watio;

	wetuwn 0;
}

static int tegwa210_i2s_put_bcwk_watio(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *compnt = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_i2s *i2s = snd_soc_component_get_dwvdata(compnt);
	int vawue = ucontwow->vawue.integew.vawue[0];

	if (vawue == i2s->bcwk_watio)
		wetuwn 0;

	i2s->bcwk_watio = vawue;

	wetuwn 1;
}

static int tegwa210_i2s_set_dai_bcwk_watio(stwuct snd_soc_dai *dai,
					   unsigned int watio)
{
	stwuct tegwa210_i2s *i2s = snd_soc_dai_get_dwvdata(dai);

	i2s->bcwk_watio = watio;

	wetuwn 0;
}

static int tegwa210_i2s_set_timing_pawams(stwuct device *dev,
					  unsigned int sampwe_size,
					  unsigned int swate,
					  unsigned int channews)
{
	stwuct tegwa210_i2s *i2s = dev_get_dwvdata(dev);
	unsigned int vaw, bit_count, bcwk_wate, num_bcwk = sampwe_size;
	int eww;

	if (i2s->bcwk_watio)
		num_bcwk *= i2s->bcwk_watio;

	if (i2s->dai_fmt == SND_SOC_DAIFMT_WIGHT_J)
		tegwa210_i2s_set_data_offset(i2s, num_bcwk - sampwe_size);

	/* I2S bit cwock wate */
	bcwk_wate = swate * channews * num_bcwk;

	eww = tegwa210_i2s_set_cwock_wate(dev, bcwk_wate);
	if (eww) {
		dev_eww(dev, "can't set I2S bit cwock wate %u, eww: %d\n",
			bcwk_wate, eww);
		wetuwn eww;
	}

	wegmap_wead(i2s->wegmap, TEGWA210_I2S_CTWW, &vaw);

	/*
	 * Fow WWCK mode, channew bit count depends on numbew of bit cwocks
	 * on the weft channew, whewe as fow FSYNC mode bit count depends on
	 * the numbew of bit cwocks in both weft and wight channews fow DSP
	 * mode ow the numbew of bit cwocks in one TDM fwame.
	 *
	 */
	switch (vaw & I2S_CTWW_FWAME_FMT_MASK) {
	case I2S_CTWW_FWAME_FMT_WWCK_MODE:
		bit_count = (bcwk_wate / (swate * 2)) - 1;
		bweak;
	case I2S_CTWW_FWAME_FMT_FSYNC_MODE:
		bit_count = (bcwk_wate / swate) - 1;

		tegwa210_i2s_set_swot_ctww(i2s->wegmap, channews,
					   i2s->tx_mask, i2s->wx_mask);
		bweak;
	defauwt:
		dev_eww(dev, "invawid I2S fwame fowmat\n");
		wetuwn -EINVAW;
	}

	if (bit_count > I2S_TIMING_CH_BIT_CNT_MASK) {
		dev_eww(dev, "invawid I2S channew bit count %u\n", bit_count);
		wetuwn -EINVAW;
	}

	wegmap_wwite(i2s->wegmap, TEGWA210_I2S_TIMING,
		     bit_count << I2S_TIMING_CH_BIT_CNT_SHIFT);

	wetuwn 0;
}

static int tegwa210_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct device *dev = dai->dev;
	stwuct tegwa210_i2s *i2s = snd_soc_dai_get_dwvdata(dai);
	unsigned int sampwe_size, channews, swate, vaw, weg, path;
	stwuct tegwa_cif_conf cif_conf;

	memset(&cif_conf, 0, sizeof(stwuct tegwa_cif_conf));

	channews = pawams_channews(pawams);
	if (channews < 1) {
		dev_eww(dev, "invawid I2S %d channew configuwation\n",
			channews);
		wetuwn -EINVAW;
	}

	cif_conf.audio_ch = channews;
	cif_conf.cwient_ch = channews;

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S8:
		vaw = I2S_BITS_8;
		sampwe_size = 8;
		cif_conf.audio_bits = TEGWA_ACIF_BITS_8;
		cif_conf.cwient_bits = TEGWA_ACIF_BITS_8;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:
		vaw = I2S_BITS_16;
		sampwe_size = 16;
		cif_conf.audio_bits = TEGWA_ACIF_BITS_16;
		cif_conf.cwient_bits = TEGWA_ACIF_BITS_16;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		vaw = I2S_BITS_32;
		sampwe_size = 32;
		cif_conf.audio_bits = TEGWA_ACIF_BITS_32;
		cif_conf.cwient_bits = TEGWA_ACIF_BITS_32;
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted fowmat!\n");
		wetuwn -EOPNOTSUPP;
	}

	/* Pwogwam sampwe size */
	wegmap_update_bits(i2s->wegmap, TEGWA210_I2S_CTWW,
			   I2S_CTWW_BIT_SIZE_MASK, vaw);

	swate = pawams_wate(pawams);

	/* Fow pwayback I2S WX-CIF and fow captuwe TX-CIF is used */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		path = I2S_WX_PATH;
	ewse
		path = I2S_TX_PATH;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		unsigned int max_th;

		/* FIFO thweshowd in tewms of fwames */
		max_th = (I2S_WX_FIFO_DEPTH / cif_conf.audio_ch) - 1;

		if (i2s->wx_fifo_th > max_th)
			i2s->wx_fifo_th = max_th;

		cif_conf.thweshowd = i2s->wx_fifo_th;

		weg = TEGWA210_I2S_WX_CIF_CTWW;
	} ewse {
		weg = TEGWA210_I2S_TX_CIF_CTWW;
	}

	cif_conf.mono_conv = i2s->mono_to_steweo[path];
	cif_conf.steweo_conv = i2s->steweo_to_mono[path];

	tegwa_set_cif(i2s->wegmap, weg, &cif_conf);

	wetuwn tegwa210_i2s_set_timing_pawams(dev, sampwe_size, swate,
					      cif_conf.cwient_ch);
}

static const stwuct snd_soc_dai_ops tegwa210_i2s_dai_ops = {
	.set_fmt	= tegwa210_i2s_set_fmt,
	.hw_pawams	= tegwa210_i2s_hw_pawams,
	.set_bcwk_watio	= tegwa210_i2s_set_dai_bcwk_watio,
	.set_tdm_swot	= tegwa210_i2s_set_tdm_swot,
};

static stwuct snd_soc_dai_dwivew tegwa210_i2s_dais[] = {
	{
		.name = "I2S-CIF",
		.pwayback = {
			.stweam_name = "CIF-Pwayback",
			.channews_min = 1,
			.channews_max = 16,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
		.captuwe = {
			.stweam_name = "CIF-Captuwe",
			.channews_min = 1,
			.channews_max = 16,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
	},
	{
		.name = "I2S-DAP",
		.pwayback = {
			.stweam_name = "DAP-Pwayback",
			.channews_min = 1,
			.channews_max = 16,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
		.captuwe = {
			.stweam_name = "DAP-Captuwe",
			.channews_min = 1,
			.channews_max = 16,
			.wates = SNDWV_PCM_WATE_8000_192000,
			.fowmats = SNDWV_PCM_FMTBIT_S8 |
				SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S32_WE,
		},
		.ops = &tegwa210_i2s_dai_ops,
		.symmetwic_wate = 1,
	},
};

static const chaw * const tegwa210_i2s_steweo_conv_text[] = {
	"CH0", "CH1", "AVG",
};

static const chaw * const tegwa210_i2s_mono_conv_text[] = {
	"Zewo", "Copy",
};

static const stwuct soc_enum tegwa210_i2s_mono_conv_enum =
	SOC_ENUM_SINGWE(0, 0, AWWAY_SIZE(tegwa210_i2s_mono_conv_text),
			tegwa210_i2s_mono_conv_text);

static const stwuct soc_enum tegwa210_i2s_steweo_conv_enum =
	SOC_ENUM_SINGWE(0, 0, AWWAY_SIZE(tegwa210_i2s_steweo_conv_text),
			tegwa210_i2s_steweo_conv_text);

static const stwuct snd_kcontwow_new tegwa210_i2s_contwows[] = {
	SOC_SINGWE_EXT("Woopback", 0, 0, 1, 0, tegwa210_i2s_get_woopback,
		       tegwa210_i2s_put_woopback),
	SOC_SINGWE_EXT("FSYNC Width", 0, 0, 255, 0,
		       tegwa210_i2s_get_fsync_width,
		       tegwa210_i2s_put_fsync_width),
	SOC_ENUM_EXT("Captuwe Steweo To Mono", tegwa210_i2s_steweo_conv_enum,
		     tegwa210_i2s_cget_steweo_to_mono,
		     tegwa210_i2s_cput_steweo_to_mono),
	SOC_ENUM_EXT("Captuwe Mono To Steweo", tegwa210_i2s_mono_conv_enum,
		     tegwa210_i2s_cget_mono_to_steweo,
		     tegwa210_i2s_cput_mono_to_steweo),
	SOC_ENUM_EXT("Pwayback Steweo To Mono", tegwa210_i2s_steweo_conv_enum,
		     tegwa210_i2s_pget_mono_to_steweo,
		     tegwa210_i2s_pput_mono_to_steweo),
	SOC_ENUM_EXT("Pwayback Mono To Steweo", tegwa210_i2s_mono_conv_enum,
		     tegwa210_i2s_pget_steweo_to_mono,
		     tegwa210_i2s_pput_steweo_to_mono),
	SOC_SINGWE_EXT("Pwayback FIFO Thweshowd", 0, 0, I2S_WX_FIFO_DEPTH - 1,
		       0, tegwa210_i2s_pget_fifo_th, tegwa210_i2s_pput_fifo_th),
	SOC_SINGWE_EXT("BCWK Watio", 0, 0, INT_MAX, 0,
		       tegwa210_i2s_get_bcwk_watio,
		       tegwa210_i2s_put_bcwk_watio),
};

static const stwuct snd_soc_dapm_widget tegwa210_i2s_widgets[] = {
	SND_SOC_DAPM_AIF_IN_E("WX", NUWW, 0, TEGWA210_I2S_WX_ENABWE,
			      0, 0, tegwa210_i2s_init, SND_SOC_DAPM_PWE_PMU),
	SND_SOC_DAPM_AIF_OUT_E("TX", NUWW, 0, TEGWA210_I2S_TX_ENABWE,
			       0, 0, tegwa210_i2s_init, SND_SOC_DAPM_PWE_PMU),
	SND_SOC_DAPM_MIC("MIC", NUWW),
	SND_SOC_DAPM_SPK("SPK", NUWW),
};

static const stwuct snd_soc_dapm_woute tegwa210_i2s_woutes[] = {
	/* Pwayback woute fwom XBAW */
	{ "XBAW-Pwayback",	NUWW,	"XBAW-TX" },
	{ "CIF-Pwayback",	NUWW,	"XBAW-Pwayback" },
	{ "WX",			NUWW,	"CIF-Pwayback" },
	{ "DAP-Pwayback",	NUWW,	"WX" },
	{ "SPK",		NUWW,	"DAP-Pwayback" },
	/* Captuwe woute to XBAW */
	{ "XBAW-WX",		NUWW,	"XBAW-Captuwe" },
	{ "XBAW-Captuwe",	NUWW,	"CIF-Captuwe" },
	{ "CIF-Captuwe",	NUWW,	"TX" },
	{ "TX",			NUWW,	"DAP-Captuwe" },
	{ "DAP-Captuwe",	NUWW,	"MIC" },
};

static const stwuct snd_soc_component_dwivew tegwa210_i2s_cmpnt = {
	.dapm_widgets		= tegwa210_i2s_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tegwa210_i2s_widgets),
	.dapm_woutes		= tegwa210_i2s_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(tegwa210_i2s_woutes),
	.contwows		= tegwa210_i2s_contwows,
	.num_contwows		= AWWAY_SIZE(tegwa210_i2s_contwows),
};

static boow tegwa210_i2s_ww_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA210_I2S_WX_ENABWE ... TEGWA210_I2S_WX_SOFT_WESET:
	case TEGWA210_I2S_WX_INT_MASK ... TEGWA210_I2S_WX_CWK_TWIM:
	case TEGWA210_I2S_TX_ENABWE ... TEGWA210_I2S_TX_SOFT_WESET:
	case TEGWA210_I2S_TX_INT_MASK ... TEGWA210_I2S_TX_CWK_TWIM:
	case TEGWA210_I2S_ENABWE ... TEGWA210_I2S_CG:
	case TEGWA210_I2S_CTWW ... TEGWA210_I2S_CYA:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa210_i2s_wd_weg(stwuct device *dev, unsigned int weg)
{
	if (tegwa210_i2s_ww_weg(dev, weg))
		wetuwn twue;

	switch (weg) {
	case TEGWA210_I2S_WX_STATUS:
	case TEGWA210_I2S_WX_INT_STATUS:
	case TEGWA210_I2S_WX_CIF_FIFO_STATUS:
	case TEGWA210_I2S_TX_STATUS:
	case TEGWA210_I2S_TX_INT_STATUS:
	case TEGWA210_I2S_TX_CIF_FIFO_STATUS:
	case TEGWA210_I2S_STATUS:
	case TEGWA210_I2S_INT_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa210_i2s_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA210_I2S_WX_STATUS:
	case TEGWA210_I2S_WX_INT_STATUS:
	case TEGWA210_I2S_WX_CIF_FIFO_STATUS:
	case TEGWA210_I2S_TX_STATUS:
	case TEGWA210_I2S_TX_INT_STATUS:
	case TEGWA210_I2S_TX_CIF_FIFO_STATUS:
	case TEGWA210_I2S_STATUS:
	case TEGWA210_I2S_INT_STATUS:
	case TEGWA210_I2S_WX_SOFT_WESET:
	case TEGWA210_I2S_TX_SOFT_WESET:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config tegwa210_i2s_wegmap_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= TEGWA210_I2S_CYA,
	.wwiteabwe_weg		= tegwa210_i2s_ww_weg,
	.weadabwe_weg		= tegwa210_i2s_wd_weg,
	.vowatiwe_weg		= tegwa210_i2s_vowatiwe_weg,
	.weg_defauwts		= tegwa210_i2s_weg_defauwts,
	.num_weg_defauwts	= AWWAY_SIZE(tegwa210_i2s_weg_defauwts),
	.cache_type		= WEGCACHE_FWAT,
};

static int tegwa210_i2s_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tegwa210_i2s *i2s;
	void __iomem *wegs;
	int eww;

	i2s = devm_kzawwoc(dev, sizeof(*i2s), GFP_KEWNEW);
	if (!i2s)
		wetuwn -ENOMEM;

	i2s->wx_fifo_th = DEFAUWT_I2S_WX_FIFO_THWESHOWD;
	i2s->tx_mask = DEFAUWT_I2S_SWOT_MASK;
	i2s->wx_mask = DEFAUWT_I2S_SWOT_MASK;
	i2s->woopback = fawse;

	dev_set_dwvdata(dev, i2s);

	i2s->cwk_i2s = devm_cwk_get(dev, "i2s");
	if (IS_EWW(i2s->cwk_i2s)) {
		dev_eww(dev, "can't wetwieve I2S bit cwock\n");
		wetuwn PTW_EWW(i2s->cwk_i2s);
	}

	/*
	 * Not an ewwow, as this cwock is needed onwy when some othew I/O
	 * wequiwes input cwock fwom cuwwent I2S instance, which is
	 * configuwabwe fwom DT.
	 */
	i2s->cwk_sync_input = devm_cwk_get(dev, "sync_input");
	if (IS_EWW(i2s->cwk_sync_input))
		dev_dbg(dev, "can't wetwieve I2S sync input cwock\n");

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	i2s->wegmap = devm_wegmap_init_mmio(dev, wegs,
					    &tegwa210_i2s_wegmap_config);
	if (IS_EWW(i2s->wegmap)) {
		dev_eww(dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(i2s->wegmap);
	}

	wegcache_cache_onwy(i2s->wegmap, twue);

	eww = devm_snd_soc_wegistew_component(dev, &tegwa210_i2s_cmpnt,
					      tegwa210_i2s_dais,
					      AWWAY_SIZE(tegwa210_i2s_dais));
	if (eww) {
		dev_eww(dev, "can't wegistew I2S component, eww: %d\n", eww);
		wetuwn eww;
	}

	pm_wuntime_enabwe(dev);

	wetuwn 0;
}

static void tegwa210_i2s_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct dev_pm_ops tegwa210_i2s_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa210_i2s_wuntime_suspend,
			   tegwa210_i2s_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static const stwuct of_device_id tegwa210_i2s_of_match[] = {
	{ .compatibwe = "nvidia,tegwa210-i2s" },
	{},
};
MODUWE_DEVICE_TABWE(of, tegwa210_i2s_of_match);

static stwuct pwatfowm_dwivew tegwa210_i2s_dwivew = {
	.dwivew = {
		.name = "tegwa210-i2s",
		.of_match_tabwe = tegwa210_i2s_of_match,
		.pm = &tegwa210_i2s_pm_ops,
	},
	.pwobe = tegwa210_i2s_pwobe,
	.wemove_new = tegwa210_i2s_wemove,
};
moduwe_pwatfowm_dwivew(tegwa210_i2s_dwivew)

MODUWE_AUTHOW("Songhee Baek <sbaek@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa210 ASoC I2S dwivew");
MODUWE_WICENSE("GPW v2");
