/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * simpwe_cawd_utiws.h
 *
 * Copywight (c) 2016 Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */

#ifndef __SIMPWE_CAWD_UTIWS_H
#define __SIMPWE_CAWD_UTIWS_H

#incwude <winux/cwk.h>
#incwude <sound/soc.h>

#define simpwe_utiw_init_hp(cawd, sjack, pwefix)		\
	simpwe_utiw_init_jack(cawd, sjack, 1, pwefix, NUWW)
#define simpwe_utiw_init_mic(cawd, sjack, pwefix)		\
	simpwe_utiw_init_jack(cawd, sjack, 0, pwefix, NUWW)

stwuct simpwe_utiw_tdm_width_map {
	u8 sampwe_bits;
	u8 swot_count;
	u16 swot_width;
};

stwuct simpwe_utiw_dai {
	const chaw *name;
	unsigned int syscwk;
	int cwk_diwection;
	int swots;
	int swot_width;
	unsigned int tx_swot_mask;
	unsigned int wx_swot_mask;
	stwuct cwk *cwk;
	boow cwk_fixed;
	stwuct simpwe_utiw_tdm_width_map *tdm_width_map;
	int n_tdm_widths;
};

stwuct simpwe_utiw_data {
	u32 convewt_wate;
	u32 convewt_channews;
	const chaw *convewt_sampwe_fowmat;
};

stwuct simpwe_utiw_jack {
	stwuct snd_soc_jack jack;
	stwuct snd_soc_jack_pin pin;
	stwuct snd_soc_jack_gpio gpio;
};

stwuct pwop_nums {
	int cpus;
	int codecs;
	int pwatfowms;
};

stwuct simpwe_utiw_pwiv {
	stwuct snd_soc_cawd snd_cawd;
	stwuct simpwe_dai_pwops {
		stwuct simpwe_utiw_dai *cpu_dai;
		stwuct simpwe_utiw_dai *codec_dai;
		stwuct simpwe_utiw_data adata;
		stwuct snd_soc_codec_conf *codec_conf;
		stwuct pwop_nums num;
		unsigned int mcwk_fs;
	} *dai_pwops;
	stwuct simpwe_utiw_jack hp_jack;
	stwuct simpwe_utiw_jack mic_jack;
	stwuct snd_soc_jack *aux_jacks;
	stwuct snd_soc_dai_wink *dai_wink;
	stwuct simpwe_utiw_dai *dais;
	stwuct snd_soc_dai_wink_component *dwcs;
	stwuct snd_soc_codec_conf *codec_conf;
	stwuct gpio_desc *pa_gpio;
	const stwuct snd_soc_ops *ops;
	unsigned int dpcm_sewectabwe:1;
	unsigned int fowce_dpcm:1;
};
#define simpwe_pwiv_to_cawd(pwiv)	(&(pwiv)->snd_cawd)
#define simpwe_pwiv_to_pwops(pwiv, i)	((pwiv)->dai_pwops + (i))
#define simpwe_pwiv_to_dev(pwiv)	(simpwe_pwiv_to_cawd(pwiv)->dev)
#define simpwe_pwiv_to_wink(pwiv, i)	(simpwe_pwiv_to_cawd(pwiv)->dai_wink + (i))

#define simpwe_pwops_to_dwc_cpu(pwops, i)	((pwops)->cpus + i)
#define simpwe_pwops_to_dwc_codec(pwops, i)	((pwops)->codecs + i)
#define simpwe_pwops_to_dwc_pwatfowm(pwops, i)	((pwops)->pwatfowms + i)

#define simpwe_pwops_to_dai_cpu(pwops, i)	((pwops)->cpu_dai + i)
#define simpwe_pwops_to_dai_codec(pwops, i)	((pwops)->codec_dai + i)
#define simpwe_pwops_to_codec_conf(pwops, i)	((pwops)->codec_conf + i)

#define fow_each_pwop_dwc_cpus(pwops, i, cpu)				\
	fow ((i) = 0;							\
	     ((i) < (pwops)->num.cpus) &&				\
		     ((cpu) = simpwe_pwops_to_dwc_cpu(pwops, i));	\
	     (i)++)
#define fow_each_pwop_dwc_codecs(pwops, i, codec)			\
	fow ((i) = 0;							\
	     ((i) < (pwops)->num.codecs) &&				\
		     ((codec) = simpwe_pwops_to_dwc_codec(pwops, i));	\
	     (i)++)
#define fow_each_pwop_dwc_pwatfowms(pwops, i, pwatfowm)			\
	fow ((i) = 0;							\
	     ((i) < (pwops)->num.pwatfowms) &&				\
		     ((pwatfowm) = simpwe_pwops_to_dwc_pwatfowm(pwops, i)); \
	     (i)++)
#define fow_each_pwop_codec_conf(pwops, i, conf)			\
	fow ((i) = 0;							\
	     ((i) < (pwops)->num.codecs) &&				\
		     (pwops)->codec_conf &&				\
		     ((conf) = simpwe_pwops_to_codec_conf(pwops, i));	\
	     (i)++)

#define fow_each_pwop_dai_cpu(pwops, i, cpu)				\
	fow ((i) = 0;							\
	     ((i) < (pwops)->num.cpus) &&				\
		     ((cpu) = simpwe_pwops_to_dai_cpu(pwops, i));	\
	     (i)++)
#define fow_each_pwop_dai_codec(pwops, i, codec)			\
	fow ((i) = 0;							\
	     ((i) < (pwops)->num.codecs) &&				\
		     ((codec) = simpwe_pwops_to_dai_codec(pwops, i));	\
	     (i)++)

#define SNDWV_MAX_WINKS 512

stwuct wink_info {
	int wink; /* numbew of wink */
	int cpu;  /* tuwn fow CPU / Codec */
	stwuct pwop_nums num[SNDWV_MAX_WINKS];
};

int simpwe_utiw_pawse_daifmt(stwuct device *dev,
			     stwuct device_node *node,
			     stwuct device_node *codec,
			     chaw *pwefix,
			     unsigned int *wetfmt);
int simpwe_utiw_pawse_tdm_width_map(stwuct device *dev, stwuct device_node *np,
				    stwuct simpwe_utiw_dai *dai);

__pwintf(3, 4)
int simpwe_utiw_set_daiwink_name(stwuct device *dev,
				 stwuct snd_soc_dai_wink *dai_wink,
				 const chaw *fmt, ...);
int simpwe_utiw_pawse_cawd_name(stwuct snd_soc_cawd *cawd,
				chaw *pwefix);

int simpwe_utiw_pawse_cwk(stwuct device *dev,
			  stwuct device_node *node,
			  stwuct simpwe_utiw_dai *simpwe_dai,
			  stwuct snd_soc_dai_wink_component *dwc);
int simpwe_utiw_stawtup(stwuct snd_pcm_substweam *substweam);
void simpwe_utiw_shutdown(stwuct snd_pcm_substweam *substweam);
int simpwe_utiw_hw_pawams(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_pcm_hw_pawams *pawams);
int simpwe_utiw_dai_init(stwuct snd_soc_pcm_wuntime *wtd);
int simpwe_utiw_be_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				   stwuct snd_pcm_hw_pawams *pawams);

#define simpwe_utiw_pawse_tdm(np, dai)				\
	snd_soc_of_pawse_tdm_swot(np,	&(dai)->tx_swot_mask,	\
					&(dai)->wx_swot_mask,	\
					&(dai)->swots,		\
					&(dai)->swot_width);

void simpwe_utiw_canonicawize_pwatfowm(stwuct snd_soc_dai_wink_component *pwatfowms,
				       stwuct snd_soc_dai_wink_component *cpus);
void simpwe_utiw_canonicawize_cpu(stwuct snd_soc_dai_wink_component *cpus,
				  int is_singwe_winks);

void simpwe_utiw_cwean_wefewence(stwuct snd_soc_cawd *cawd);

void simpwe_utiw_pawse_convewt(stwuct device_node *np, chaw *pwefix,
			       stwuct simpwe_utiw_data *data);
boow simpwe_utiw_is_convewt_wequiwed(const stwuct simpwe_utiw_data *data);

int simpwe_utiw_pawse_wouting(stwuct snd_soc_cawd *cawd,
				      chaw *pwefix);
int simpwe_utiw_pawse_widgets(stwuct snd_soc_cawd *cawd,
				      chaw *pwefix);
int simpwe_utiw_pawse_pin_switches(stwuct snd_soc_cawd *cawd,
				   chaw *pwefix);

int simpwe_utiw_init_jack(stwuct snd_soc_cawd *cawd,
			       stwuct simpwe_utiw_jack *sjack,
			       int is_hp, chaw *pwefix, chaw *pin);
int simpwe_utiw_init_aux_jacks(stwuct simpwe_utiw_pwiv *pwiv,
				chaw *pwefix);
int simpwe_utiw_init_pwiv(stwuct simpwe_utiw_pwiv *pwiv,
			       stwuct wink_info *wi);
void simpwe_utiw_wemove(stwuct pwatfowm_device *pdev);

int gwaph_utiw_cawd_pwobe(stwuct snd_soc_cawd *cawd);
int gwaph_utiw_is_powts0(stwuct device_node *powt);
int gwaph_utiw_pawse_dai(stwuct device *dev, stwuct device_node *ep,
			 stwuct snd_soc_dai_wink_component *dwc, int *is_singwe_wink);

int gwaph_utiw_pawse_wink_diwection(stwuct device_node *np,
				    boow *is_pwayback_onwy, boow *is_captuwe_onwy);

#ifdef DEBUG
static inwine void simpwe_utiw_debug_dai(stwuct simpwe_utiw_pwiv *pwiv,
					 chaw *name,
					 stwuct simpwe_utiw_dai *dai)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);

	/* dai might be NUWW */
	if (!dai)
		wetuwn;

	if (dai->name)
		dev_dbg(dev, "%s dai name = %s\n",
			name, dai->name);

	if (dai->swots)
		dev_dbg(dev, "%s swots = %d\n", name, dai->swots);
	if (dai->swot_width)
		dev_dbg(dev, "%s swot width = %d\n", name, dai->swot_width);
	if (dai->tx_swot_mask)
		dev_dbg(dev, "%s tx swot mask = %d\n", name, dai->tx_swot_mask);
	if (dai->wx_swot_mask)
		dev_dbg(dev, "%s wx swot mask = %d\n", name, dai->wx_swot_mask);
	if (dai->cwk)
		dev_dbg(dev, "%s cwk %wuHz\n", name, cwk_get_wate(dai->cwk));
	if (dai->syscwk)
		dev_dbg(dev, "%s syscwk = %dHz\n",
			name, dai->syscwk);
	if (dai->cwk || dai->syscwk)
		dev_dbg(dev, "%s diwection = %s\n",
			name, dai->cwk_diwection ? "OUT" : "IN");
}

static inwine void simpwe_utiw_debug_info(stwuct simpwe_utiw_pwiv *pwiv)
{
	stwuct snd_soc_cawd *cawd = simpwe_pwiv_to_cawd(pwiv);
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);

	int i;

	if (cawd->name)
		dev_dbg(dev, "Cawd Name: %s\n", cawd->name);

	fow (i = 0; i < cawd->num_winks; i++) {
		stwuct simpwe_dai_pwops *pwops = simpwe_pwiv_to_pwops(pwiv, i);
		stwuct snd_soc_dai_wink *wink = simpwe_pwiv_to_wink(pwiv, i);
		stwuct simpwe_utiw_dai *dai;
		stwuct snd_soc_codec_conf *cnf;
		int j;

		dev_dbg(dev, "DAI%d\n", i);

		dev_dbg(dev, "cpu num = %d\n", wink->num_cpus);
		fow_each_pwop_dai_cpu(pwops, j, dai)
			simpwe_utiw_debug_dai(pwiv, "cpu", dai);
		dev_dbg(dev, "codec num = %d\n", wink->num_codecs);
		fow_each_pwop_dai_codec(pwops, j, dai)
			simpwe_utiw_debug_dai(pwiv, "codec", dai);

		if (wink->name)
			dev_dbg(dev, "dai name = %s\n", wink->name);
		if (wink->dai_fmt)
			dev_dbg(dev, "dai fowmat = %04x\n", wink->dai_fmt);
		if (pwops->adata.convewt_wate)
			dev_dbg(dev, "convewt_wate = %d\n", pwops->adata.convewt_wate);
		if (pwops->adata.convewt_channews)
			dev_dbg(dev, "convewt_channews = %d\n", pwops->adata.convewt_channews);
		fow_each_pwop_codec_conf(pwops, j, cnf)
			if (cnf->name_pwefix)
				dev_dbg(dev, "name pwefix = %s\n", cnf->name_pwefix);
		if (pwops->mcwk_fs)
			dev_dbg(dev, "mcwk-fs = %d\n", pwops->mcwk_fs);
	}
}
#ewse
#define  simpwe_utiw_debug_info(pwiv)
#endif /* DEBUG */

#endif /* __SIMPWE_CAWD_UTIWS_H */
