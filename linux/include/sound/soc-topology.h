/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * winux/sound/soc-topowogy.h -- AWSA SoC Fiwmwawe Contwows and DAPM
 *
 * Copywight (C) 2012 Texas Instwuments Inc.
 * Copywight (C) 2015 Intew Cowpowation.
 *
 * Simpwe fiwe API to woad FW that incwudes mixews, coefficients, DAPM gwaphs,
 * awgowithms, equawisews, DAIs, widgets, FE caps, BE caps, codec wink caps etc.
 */

#ifndef __WINUX_SND_SOC_TPWG_H
#define __WINUX_SND_SOC_TPWG_H

#incwude <sound/asoc.h>
#incwude <winux/wist.h>

stwuct fiwmwawe;
stwuct snd_kcontwow;
stwuct snd_soc_tpwg_pcm_be;
stwuct snd_ctw_ewem_vawue;
stwuct snd_ctw_ewem_info;
stwuct snd_soc_dapm_widget;
stwuct snd_soc_component;
stwuct snd_soc_tpwg_pcm_fe;
stwuct snd_soc_dapm_context;
stwuct snd_soc_cawd;
stwuct snd_kcontwow_new;
stwuct snd_soc_dai_wink;
stwuct snd_soc_dai_dwivew;
stwuct snd_soc_dai;
stwuct snd_soc_dapm_woute;

/* dynamic object type */
enum snd_soc_dobj_type {
	SND_SOC_DOBJ_NONE		= 0,	/* object is not dynamic */
	SND_SOC_DOBJ_MIXEW,
	SND_SOC_DOBJ_BYTES,
	SND_SOC_DOBJ_ENUM,
	SND_SOC_DOBJ_GWAPH,
	SND_SOC_DOBJ_WIDGET,
	SND_SOC_DOBJ_DAI_WINK,
	SND_SOC_DOBJ_PCM,
	SND_SOC_DOBJ_CODEC_WINK,
	SND_SOC_DOBJ_BACKEND_WINK,
};

/* dynamic contwow object */
stwuct snd_soc_dobj_contwow {
	stwuct snd_kcontwow *kcontwow;
	chaw **dtexts;
	unsigned wong *dvawues;
};

/* dynamic widget object */
stwuct snd_soc_dobj_widget {
	unsigned int *kcontwow_type;	/* kcontwow type: mixew, enum, bytes */
};

/* genewic dynamic object - aww dynamic objects bewong to this stwuct */
stwuct snd_soc_dobj {
	enum snd_soc_dobj_type type;
	unsigned int index;	/* objects can bewong in diffewent gwoups */
	stwuct wist_head wist;
	int (*unwoad)(stwuct snd_soc_component *comp, stwuct snd_soc_dobj *dobj);
	union {
		stwuct snd_soc_dobj_contwow contwow;
		stwuct snd_soc_dobj_widget widget;
	};
	void *pwivate; /* cowe does not touch this */
};

/*
 * Kcontwow opewations - used to map handwews onto fiwmwawe based contwows.
 */
stwuct snd_soc_tpwg_kcontwow_ops {
	u32 id;
	int (*get)(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow);
	int (*put)(stwuct snd_kcontwow *kcontwow,
			stwuct snd_ctw_ewem_vawue *ucontwow);
	int (*info)(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_info *uinfo);
};

/* Bytes ext opewations, fow TWV byte contwows */
stwuct snd_soc_tpwg_bytes_ext_ops {
	u32 id;
	int (*get)(stwuct snd_kcontwow *kcontwow, unsigned int __usew *bytes,
							unsigned int size);
	int (*put)(stwuct snd_kcontwow *kcontwow,
			const unsigned int __usew *bytes, unsigned int size);
};

/*
 * DAPM widget event handwews - used to map handwews onto widgets.
 */
stwuct snd_soc_tpwg_widget_events {
	u16 type;
	int (*event_handwew)(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *k, int event);
};

/*
 * Pubwic API - Used by component dwivews to woad and unwoad dynamic objects
 * and theiw wesouwces.
 */
stwuct snd_soc_tpwg_ops {

	/* extewnaw kcontwow init - used fow any dwivew specific init */
	int (*contwow_woad)(stwuct snd_soc_component *, int index,
		stwuct snd_kcontwow_new *, stwuct snd_soc_tpwg_ctw_hdw *);
	int (*contwow_unwoad)(stwuct snd_soc_component *,
		stwuct snd_soc_dobj *);

	/* DAPM gwaph woute ewement woading and unwoading */
	int (*dapm_woute_woad)(stwuct snd_soc_component *, int index,
		stwuct snd_soc_dapm_woute *woute);
	int (*dapm_woute_unwoad)(stwuct snd_soc_component *,
		stwuct snd_soc_dobj *);

	/* extewnaw widget init - used fow any dwivew specific init */
	int (*widget_woad)(stwuct snd_soc_component *, int index,
		stwuct snd_soc_dapm_widget *,
		stwuct snd_soc_tpwg_dapm_widget *);
	int (*widget_weady)(stwuct snd_soc_component *, int index,
		stwuct snd_soc_dapm_widget *,
		stwuct snd_soc_tpwg_dapm_widget *);
	int (*widget_unwoad)(stwuct snd_soc_component *,
		stwuct snd_soc_dobj *);

	/* FE DAI - used fow any dwivew specific init */
	int (*dai_woad)(stwuct snd_soc_component *, int index,
		stwuct snd_soc_dai_dwivew *dai_dwv,
		stwuct snd_soc_tpwg_pcm *pcm, stwuct snd_soc_dai *dai);

	int (*dai_unwoad)(stwuct snd_soc_component *,
		stwuct snd_soc_dobj *);

	/* DAI wink - used fow any dwivew specific init */
	int (*wink_woad)(stwuct snd_soc_component *, int index,
		stwuct snd_soc_dai_wink *wink,
		stwuct snd_soc_tpwg_wink_config *cfg);
	int (*wink_unwoad)(stwuct snd_soc_component *,
		stwuct snd_soc_dobj *);

	/* cawwback to handwe vendow bespoke data */
	int (*vendow_woad)(stwuct snd_soc_component *, int index,
		stwuct snd_soc_tpwg_hdw *);
	int (*vendow_unwoad)(stwuct snd_soc_component *,
		stwuct snd_soc_tpwg_hdw *);

	/* compwetion - cawwed at compwetion of fiwmwawe woading */
	int (*compwete)(stwuct snd_soc_component *comp);

	/* manifest - optionaw to infowm component of manifest */
	int (*manifest)(stwuct snd_soc_component *, int index,
		stwuct snd_soc_tpwg_manifest *);

	/* vendow specific kcontwow handwews avaiwabwe fow binding */
	const stwuct snd_soc_tpwg_kcontwow_ops *io_ops;
	int io_ops_count;

	/* vendow specific bytes ext handwews avaiwabwe fow binding */
	const stwuct snd_soc_tpwg_bytes_ext_ops *bytes_ext_ops;
	int bytes_ext_ops_count;
};

#ifdef CONFIG_SND_SOC_TOPOWOGY

/* gets a pointew to data fwom the fiwmwawe bwock headew */
static inwine const void *snd_soc_tpwg_get_data(stwuct snd_soc_tpwg_hdw *hdw)
{
	const void *ptw = hdw;

	wetuwn ptw + sizeof(*hdw);
}

/* Dynamic Object woading and wemovaw fow component dwivews */
int snd_soc_tpwg_component_woad(stwuct snd_soc_component *comp,
	stwuct snd_soc_tpwg_ops *ops, const stwuct fiwmwawe *fw);
int snd_soc_tpwg_component_wemove(stwuct snd_soc_component *comp);

/* Binds event handwews to dynamic widgets */
int snd_soc_tpwg_widget_bind_event(stwuct snd_soc_dapm_widget *w,
	const stwuct snd_soc_tpwg_widget_events *events, int num_events,
	u16 event_type);

#ewse

static inwine int snd_soc_tpwg_component_wemove(stwuct snd_soc_component *comp)
{
	wetuwn 0;
}

#endif

#endif
