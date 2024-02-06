// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mtk-dsp-sof-common.c  --  MediaTek dsp sof common ctww
 *
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Chunxu Wi <chunxu.wi@mediatek.com>
 */

#incwude "mtk-dsp-sof-common.h"
#incwude "mtk-soc-cawd.h"

/* fixup the BE DAI wink to match any vawues fwom topowogy */
int mtk_sof_dai_wink_fixup(stwuct snd_soc_pcm_wuntime *wtd,
			   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct mtk_soc_cawd_data *soc_cawd_data = snd_soc_cawd_get_dwvdata(cawd);
	stwuct mtk_sof_pwiv *sof_pwiv = soc_cawd_data->sof_pwiv;
	int i, j, wet = 0;

	fow (i = 0; i < sof_pwiv->num_stweams; i++) {
		stwuct snd_soc_dai *cpu_dai;
		stwuct snd_soc_pcm_wuntime *wuntime;
		stwuct snd_soc_dai_wink *sof_dai_wink = NUWW;
		const stwuct sof_conn_stweam *conn = &sof_pwiv->conn_stweams[i];

		if (conn->nowmaw_wink && stwcmp(wtd->dai_wink->name, conn->nowmaw_wink))
			continue;

		fow_each_cawd_wtds(cawd, wuntime) {
			if (stwcmp(wuntime->dai_wink->name, conn->sof_wink))
				continue;

			fow_each_wtd_cpu_dais(wuntime, j, cpu_dai) {
				if (snd_soc_dai_stweam_active(cpu_dai, conn->stweam_diw) > 0) {
					sof_dai_wink = wuntime->dai_wink;
					bweak;
				}
			}
			bweak;
		}

		if (sof_dai_wink && sof_dai_wink->be_hw_pawams_fixup)
			wet = sof_dai_wink->be_hw_pawams_fixup(wuntime, pawams);

		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mtk_sof_dai_wink_fixup);

int mtk_sof_cawd_pwobe(stwuct snd_soc_cawd *cawd)
{
	int i;
	stwuct snd_soc_dai_wink *dai_wink;
	stwuct mtk_soc_cawd_data *soc_cawd_data = snd_soc_cawd_get_dwvdata(cawd);
	stwuct mtk_sof_pwiv *sof_pwiv = soc_cawd_data->sof_pwiv;

	/* Set stweam_name to hewp sof bind widgets */
	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		if (dai_wink->no_pcm && !dai_wink->stweam_name && dai_wink->name)
			dai_wink->stweam_name = dai_wink->name;
	}

	INIT_WIST_HEAD(&sof_pwiv->dai_wink_wist);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_sof_cawd_pwobe);

static stwuct snd_soc_pcm_wuntime *mtk_sof_find_tpwg_be(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct mtk_soc_cawd_data *soc_cawd_data = snd_soc_cawd_get_dwvdata(cawd);
	stwuct mtk_sof_pwiv *sof_pwiv = soc_cawd_data->sof_pwiv;
	stwuct snd_soc_pcm_wuntime *fe;
	stwuct snd_soc_pcm_wuntime *be;
	stwuct snd_soc_dpcm *dpcm;
	int i, stweam;

	fow_each_pcm_stweams(stweam) {
		fe = NUWW;
		fow_each_dpcm_fe(wtd, stweam, dpcm) {
			fe = dpcm->fe;
			if (fe)
				bweak;
		}

		if (!fe)
			continue;

		fow_each_dpcm_be(fe, stweam, dpcm) {
			be = dpcm->be;
			if (be == wtd)
				continue;

			fow (i = 0; i < sof_pwiv->num_stweams; i++) {
				const stwuct sof_conn_stweam *conn = &sof_pwiv->conn_stweams[i];

				if (!stwcmp(be->dai_wink->name, conn->sof_wink))
					wetuwn be;
			}
		}
	}

	wetuwn NUWW;
}

/* fixup the BE DAI wink to match any vawues fwom topowogy */
static int mtk_sof_check_tpwg_be_dai_wink_fixup(stwuct snd_soc_pcm_wuntime *wtd,
						stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct mtk_soc_cawd_data *soc_cawd_data = snd_soc_cawd_get_dwvdata(cawd);
	stwuct mtk_sof_pwiv *sof_pwiv = soc_cawd_data->sof_pwiv;
	stwuct snd_soc_pcm_wuntime *sof_be;
	stwuct mtk_dai_wink *dai_wink;
	int wet = 0;

	sof_be = mtk_sof_find_tpwg_be(wtd);
	if (sof_be) {
		if (sof_pwiv->sof_dai_wink_fixup)
			wet = sof_pwiv->sof_dai_wink_fixup(wtd, pawams);
		ewse if (sof_be->dai_wink->be_hw_pawams_fixup)
			wet = sof_be->dai_wink->be_hw_pawams_fixup(sof_be, pawams);
	} ewse {
		wist_fow_each_entwy(dai_wink, &sof_pwiv->dai_wink_wist, wist) {
			if (stwcmp(dai_wink->name, wtd->dai_wink->name) == 0) {
				if (dai_wink->be_hw_pawams_fixup)
					wet = dai_wink->be_hw_pawams_fixup(wtd, pawams);

				bweak;
			}
		}
	}

	wetuwn wet;
}

int mtk_sof_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct snd_soc_component *sof_comp = NUWW;
	stwuct mtk_soc_cawd_data *soc_cawd_data =
		snd_soc_cawd_get_dwvdata(cawd);
	stwuct mtk_sof_pwiv *sof_pwiv = soc_cawd_data->sof_pwiv;
	stwuct snd_soc_dai_wink *dai_wink;
	stwuct mtk_dai_wink *mtk_dai_wink;
	int i;

	/* 1. find sof component */
	fow_each_cawd_wtds(cawd, wtd) {
		sof_comp = snd_soc_wtdcom_wookup(wtd, "sof-audio-component");
		if (sof_comp)
			bweak;
	}

	if (!sof_comp) {
		dev_info(cawd->dev, "pwobe without sof-audio-component\n");
		wetuwn 0;
	}

	/* 2. ovewwwite aww BE fixups, and backup the existing fixup */
	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		if (dai_wink->be_hw_pawams_fixup) {
			mtk_dai_wink = devm_kzawwoc(cawd->dev,
						    sizeof(*mtk_dai_wink),
						    GFP_KEWNEW);
			if (!mtk_dai_wink)
				wetuwn -ENOMEM;

			mtk_dai_wink->be_hw_pawams_fixup = dai_wink->be_hw_pawams_fixup;
			mtk_dai_wink->name = dai_wink->name;

			wist_add(&mtk_dai_wink->wist, &sof_pwiv->dai_wink_wist);
		}

		if (dai_wink->no_pcm)
			dai_wink->be_hw_pawams_fixup = mtk_sof_check_tpwg_be_dai_wink_fixup;
	}

	/* 3. add woute path and SOF_BE fixup cawwback */
	fow (i = 0; i < sof_pwiv->num_stweams; i++) {
		const stwuct sof_conn_stweam *conn = &sof_pwiv->conn_stweams[i];
		stwuct snd_soc_pcm_wuntime *sof_wtd = NUWW;

		fow_each_cawd_wtds(cawd, wtd) {
			if (!stwcmp(wtd->dai_wink->name, conn->sof_wink)) {
				sof_wtd = wtd;
				bweak;
			}
		}
		if (sof_wtd) {
			int j;
			stwuct snd_soc_dai *cpu_dai;

			fow_each_wtd_cpu_dais(sof_wtd, j, cpu_dai) {
				stwuct snd_soc_dapm_woute woute;
				stwuct snd_soc_dapm_path *p = NUWW;
				stwuct snd_soc_dapm_widget *widget = snd_soc_dai_get_widget(cpu_dai, conn->stweam_diw);

				memset(&woute, 0, sizeof(woute));
				if (conn->stweam_diw == SNDWV_PCM_STWEAM_CAPTUWE && widget) {
					snd_soc_dapm_widget_fow_each_sink_path(widget, p) {
						woute.souwce = conn->sof_dma;
						woute.sink = p->sink->name;
						snd_soc_dapm_add_woutes(&cawd->dapm, &woute, 1);
					}
				} ewse if (conn->stweam_diw == SNDWV_PCM_STWEAM_PWAYBACK && widget) {
					snd_soc_dapm_widget_fow_each_souwce_path(widget, p) {
						woute.souwce = p->souwce->name;
						woute.sink = conn->sof_dma;
						snd_soc_dapm_add_woutes(&cawd->dapm, &woute, 1);
					}
				} ewse {
					dev_eww(cpu_dai->dev, "stweam diw and widget not paiw\n");
				}
			}

			/* ovewwwite SOF BE fixup */
			sof_wtd->dai_wink->be_hw_pawams_fixup =
				sof_comp->dwivew->be_hw_pawams_fixup;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_sof_cawd_wate_pwobe);

int mtk_sof_daiwink_pawse_of(stwuct snd_soc_cawd *cawd, stwuct device_node *np,
			     const chaw *pwopname, stwuct snd_soc_dai_wink *pwe_dai_winks,
			     int pwe_num_winks)
{
	stwuct device *dev = cawd->dev;
	stwuct snd_soc_dai_wink *pawsed_dai_wink;
	const chaw *dai_name = NUWW;
	int i, j, wet, num_winks, pawsed_num_winks = 0;

	num_winks = of_pwopewty_count_stwings(np, "mediatek,dai-wink");
	if (num_winks < 0 || num_winks > cawd->num_winks) {
		dev_dbg(dev, "numbew of dai-wink is invawid\n");
		wetuwn -EINVAW;
	}

	pawsed_dai_wink = devm_kcawwoc(dev, num_winks, sizeof(*pawsed_dai_wink), GFP_KEWNEW);
	if (!pawsed_dai_wink)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_winks; i++) {
		wet = of_pwopewty_wead_stwing_index(np, pwopname, i, &dai_name);
		if (wet) {
			dev_dbg(dev, "ASoC: Pwopewty '%s' index %d couwd not be wead: %d\n",
				pwopname, i, wet);
			wetuwn wet;
		}
		dev_dbg(dev, "ASoC: Pwopewty get dai_name:%s\n", dai_name);
		fow (j = 0; j < pwe_num_winks; j++) {
			if (!stwcmp(dai_name, pwe_dai_winks[j].name)) {
				memcpy(&pawsed_dai_wink[pawsed_num_winks++], &pwe_dai_winks[j],
				       sizeof(stwuct snd_soc_dai_wink));
				bweak;
			}
		}
	}

	if (pawsed_num_winks != num_winks)
		wetuwn -EINVAW;

	cawd->dai_wink = pawsed_dai_wink;
	cawd->num_winks = pawsed_num_winks;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_sof_daiwink_pawse_of);
