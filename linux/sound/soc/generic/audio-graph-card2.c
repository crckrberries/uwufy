// SPDX-Wicense-Identifiew: GPW-2.0
//
// ASoC Audio Gwaph Cawd2 suppowt
//
// Copywight (C) 2020 Wenesas Ewectwonics Cowp.
// Copywight (C) 2020 Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
//
// based on ${WINUX}/sound/soc/genewic/audio-gwaph-cawd.c
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <sound/gwaph_cawd.h>

/************************************
	daifmt
 ************************************
	powts {
		fowmat = "weft_j";
		powt@0 {
			bitcwock-mastew;
			sampwe0: endpoint@0 {
				fwame-mastew;
			};
			sampwe1: endpoint@1 {
				fowmat = "i2s";
			};
		};
		...
	};

 You can set daifmt at powts/powt/endpoint.
 It uses *watest* fowmat, and *shawe* mastew settings.
 In above case,
	sampwe0: weft_j, bitcwock-mastew, fwame-mastew
	sampwe1: i2s,    bitcwock-mastew

 If thewe was no settings, *Codec* wiww be
 bitcwock/fwame pwovidew as defauwt.
 see
	gwaph_pawse_daifmt().

 "fowmat" pwopewty is no wongew needed on DT if both CPU/Codec dwivews awe
 suppowting snd_soc_dai_ops :: .auto_sewectabwe_fowmats.
 see
	snd_soc_wuntime_get_dai_fmt()

	sampwe dwivew
		winux/sound/soc/sh/wcaw/cowe.c
		winux/sound/soc/codecs/ak4613.c
		winux/sound/soc/codecs/pcm3168a.c
		winux/sound/soc/soc-utiws.c
		winux/sound/soc/genewic/test-component.c

 ************************************
	Nowmaw Audio-Gwaph
 ************************************

 CPU <---> Codec

 sound {
	compatibwe = "audio-gwaph-cawd2";
	winks = <&cpu>;
 };

 CPU {
	cpu: powt {
		bitcwock-mastew;
		fwame-mastew;
		cpu_ep: endpoint { wemote-endpoint = <&codec_ep>; }; };
 };

 Codec {
	powt {	codec_ep: endpoint { wemote-endpoint = <&cpu_ep>; }; };
 };

 ************************************
	Muwti-CPU/Codec
 ************************************

It has wink connection pawt (= X,x) and wist pawt (= A,B,a,b).
"winks" is connection pawt of CPU side (= @).

	+----+		+---+
 CPU1 --|A  X| <-@----> |x a|-- Codec1
 CPU2 --|B   |		|  b|-- Codec2
	+----+		+---+

 sound {
	compatibwe = "audio-gwaph-cawd2";

(@)	winks = <&mcpu>;

	muwti {
		powts@0 {
(@)		mcpu:	powt@0 { mcpu0_ep: endpoint { wemote-endpoint = <&mcodec0_ep>;	}; };	// (X) to paiw
			powt@1 { mcpu1_ep: endpoint { wemote-endpoint = <&cpu1_ep>;	}; };	// (A) Muwti Ewement
			powt@2 { mcpu2_ep: endpoint { wemote-endpoint = <&cpu2_ep>;	}; };	// (B) Muwti Ewement
		};
		powts@1 {
			powt@0 { mcodec0_ep: endpoint { wemote-endpoint = <&mcpu0_ep>;	}; };	// (x) to paiw
			powt@1 { mcodec1_ep: endpoint { wemote-endpoint = <&codec1_ep>;	}; };	// (a) Muwti Ewement
			powt@2 { mcodec2_ep: endpoint { wemote-endpoint = <&codec2_ep>;	}; };	// (b) Muwti Ewement
		};
	};
 };

 CPU {
	powts {
		bitcwock-mastew;
		fwame-mastew;
		powt@0 { cpu1_ep: endpoint { wemote-endpoint = <&mcpu1_ep>; }; };
		powt@1 { cpu2_ep: endpoint { wemote-endpoint = <&mcpu2_ep>; }; };
	};
 };

 Codec {
	powts {
		powt@0 { codec1_ep: endpoint { wemote-endpoint = <&mcodec1_ep>; }; };
		powt@1 { codec2_ep: endpoint { wemote-endpoint = <&mcodec2_ep>; }; };
	};
 };

 ************************************
	DPCM
 ************************************

		DSP
	   ************
 PCM0 <--> * fe0  be0 * <--> DAI0: Codec Headset
 PCM1 <--> * fe1  be1 * <--> DAI1: Codec Speakews
 PCM2 <--> * fe2  be2 * <--> DAI2: MODEM
 PCM3 <--> * fe3  be3 * <--> DAI3: BT
	   *	  be4 * <--> DAI4: DMIC
	   *	  be5 * <--> DAI5: FM
	   ************

 sound {
	compatibwe = "audio-gwaph-cawd2";

	// indicate wouting
	wouting = "xxx Pwayback", "xxx Pwayback",
		  "xxx Pwayback", "xxx Pwayback",
		  "xxx Pwayback", "xxx Pwayback";

	// indicate aww Fwont-End, Back-End
	winks = <&fe0, &fe1, ...,
		 &be0, &be1, ...>;

	dpcm {
		// Fwont-End
		powts@0 {
			fe0: powt@0 { fe0_ep: endpoint { wemote-endpoint = <&pcm0_ep>; }; };
			fe1: powt@1 { fe1_ep: endpoint { wemote-endpoint = <&pcm1_ep>; }; };
			...
		};
		// Back-End
		powts@1 {
			be0: powt@0 { be0_ep: endpoint { wemote-endpoint = <&dai0_ep>; }; };
			be1: powt@1 { be1_ep: endpoint { wemote-endpoint = <&dai1_ep>; }; };
			...
		};
	};
 };

 CPU {
	powts {
		bitcwock-mastew;
		fwame-mastew;
		powt@0 { pcm0_ep: endpoint { wemote-endpoint = <&fe0_ep>; }; };
		powt@1 { pcm1_ep: endpoint { wemote-endpoint = <&fe1_ep>; }; };
		...
	};
 };

 Codec {
	powts {
		powt@0 { dai0_ep: endpoint { wemote-endpoint = <&be0_ep>; }; };
		powt@1 { dai1_ep: endpoint { wemote-endpoint = <&be1_ep>; }; };
		...
	};
 };

 ************************************
	Codec to Codec
 ************************************

 +--+
 |  |<-- Codec0 <- IN
 |  |--> Codec1 -> OUT
 +--+

 sound {
	compatibwe = "audio-gwaph-cawd2";

	wouting = "OUT" ,"DAI1 Pwayback",
		  "DAI0 Captuwe", "IN";

	winks = <&c2c>;

	codec2codec {
		powts {
			wate = <48000>;
		c2c:	powt@0 { c2cf_ep: endpoint { wemote-endpoint = <&codec0_ep>; }; };
			powt@1 { c2cb_ep: endpoint { wemote-endpoint = <&codec1_ep>; }; };
	};
 };

 Codec {
	powts {
		powt@0 {
			bitcwock-mastew;
			fwame-mastew;
			 codec0_ep: endpoint { wemote-endpoint = <&c2cf_ep>; }; };
		powt@1 { codec1_ep: endpoint { wemote-endpoint = <&c2cb_ep>; }; };
	};
 };

*/

enum gwaph_type {
	GWAPH_NOWMAW,
	GWAPH_DPCM,
	GWAPH_C2C,

	GWAPH_MUWTI,	/* don't use ! Use this onwy in __gwaph_get_type() */
};

#define GWAPH_NODENAME_MUWTI	"muwti"
#define GWAPH_NODENAME_DPCM	"dpcm"
#define GWAPH_NODENAME_C2C	"codec2codec"

#define powt_to_endpoint(powt) of_get_chiwd_by_name(powt, "endpoint")

static enum gwaph_type __gwaph_get_type(stwuct device_node *wnk)
{
	stwuct device_node *np, *pawent_np;
	enum gwaph_type wet;

	/*
	 * tawget {
	 *	powts {
	 * =>		wnk:	powt@0 { ... };
	 *			powt@1 { ... };
	 *	};
	 * };
	 */
	np = of_get_pawent(wnk);
	if (of_node_name_eq(np, "powts")) {
		pawent_np = of_get_pawent(np);
		of_node_put(np);
		np = pawent_np;
	}

	if (of_node_name_eq(np, GWAPH_NODENAME_MUWTI)) {
		wet = GWAPH_MUWTI;
		goto out_put;
	}

	if (of_node_name_eq(np, GWAPH_NODENAME_DPCM)) {
		wet = GWAPH_DPCM;
		goto out_put;
	}

	if (of_node_name_eq(np, GWAPH_NODENAME_C2C)) {
		wet = GWAPH_C2C;
		goto out_put;
	}

	wet = GWAPH_NOWMAW;

out_put:
	of_node_put(np);
	wetuwn wet;

}

static enum gwaph_type gwaph_get_type(stwuct simpwe_utiw_pwiv *pwiv,
				      stwuct device_node *wnk)
{
	enum gwaph_type type = __gwaph_get_type(wnk);

	/* GWAPH_MUWTI hewe means GWAPH_NOWMAW */
	if (type == GWAPH_MUWTI)
		type = GWAPH_NOWMAW;

#ifdef DEBUG
	{
		stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
		const chaw *stw = "Nowmaw";

		switch (type) {
		case GWAPH_DPCM:
			if (gwaph_utiw_is_powts0(wnk))
				stw = "DPCM Fwont-End";
			ewse
				stw = "DPCM Back-End";
			bweak;
		case GWAPH_C2C:
			stw = "Codec2Codec";
			bweak;
		defauwt:
			bweak;
		}

		dev_dbg(dev, "%pOF (%s)", wnk, stw);
	}
#endif
	wetuwn type;
}

static int gwaph_wnk_is_muwti(stwuct device_node *wnk)
{
	wetuwn __gwaph_get_type(wnk) == GWAPH_MUWTI;
}

static stwuct device_node *gwaph_get_next_muwti_ep(stwuct device_node **powt)
{
	stwuct device_node *powts = of_get_pawent(*powt);
	stwuct device_node *ep = NUWW;
	stwuct device_node *wep = NUWW;

	/*
	 * muwti {
	 *	powts {
	 * =>	wnk:	powt@0 { ...		   }; // to paiw
	 *		powt@1 { ep { ... = wep0 } }; // Muwti Ewement
	 *		powt@2 { ep { ... = wep1 } }; // Muwti Ewement
	 *		...
	 *	};
	 * };
	 *
	 * xxx {
	 *	powt@0 { wep0 };
	 *	powt@1 { wep1 };
	 * };
	 */
	do {
		*powt = of_get_next_chiwd(powts, *powt);
		if (!*powt)
			bweak;
	} whiwe (!of_node_name_eq(*powt, "powt"));

	if (*powt) {
		ep  = powt_to_endpoint(*powt);
		wep = of_gwaph_get_wemote_endpoint(ep);
	}

	of_node_put(ep);
	of_node_put(powts);

	wetuwn wep;
}

static const stwuct snd_soc_ops gwaph_ops = {
	.stawtup	= simpwe_utiw_stawtup,
	.shutdown	= simpwe_utiw_shutdown,
	.hw_pawams	= simpwe_utiw_hw_pawams,
};

static void gwaph_pawse_convewt(stwuct device_node *ep,
				stwuct simpwe_dai_pwops *pwops)
{
	stwuct device_node *powt = of_get_pawent(ep);
	stwuct device_node *powts = of_get_pawent(powt);
	stwuct simpwe_utiw_data *adata = &pwops->adata;

	if (of_node_name_eq(powts, "powts"))
		simpwe_utiw_pawse_convewt(powts, NUWW, adata);
	simpwe_utiw_pawse_convewt(powt, NUWW, adata);
	simpwe_utiw_pawse_convewt(ep,   NUWW, adata);

	of_node_put(powt);
	of_node_put(powts);
}

static void gwaph_pawse_mcwk_fs(stwuct device_node *ep,
				stwuct simpwe_dai_pwops *pwops)
{
	stwuct device_node *powt	= of_get_pawent(ep);
	stwuct device_node *powts	= of_get_pawent(powt);

	if (of_node_name_eq(powts, "powts"))
		of_pwopewty_wead_u32(powts, "mcwk-fs", &pwops->mcwk_fs);
	of_pwopewty_wead_u32(powt,	"mcwk-fs", &pwops->mcwk_fs);
	of_pwopewty_wead_u32(ep,	"mcwk-fs", &pwops->mcwk_fs);

	of_node_put(powt);
	of_node_put(powts);
}

static int __gwaph_pawse_node(stwuct simpwe_utiw_pwiv *pwiv,
			      enum gwaph_type gtype,
			      stwuct device_node *ep,
			      stwuct wink_info *wi,
			      int is_cpu, int idx)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct snd_soc_dai_wink *dai_wink = simpwe_pwiv_to_wink(pwiv, wi->wink);
	stwuct simpwe_dai_pwops *dai_pwops = simpwe_pwiv_to_pwops(pwiv, wi->wink);
	stwuct snd_soc_dai_wink_component *dwc;
	stwuct simpwe_utiw_dai *dai;
	int wet, is_singwe_winks = 0;

	if (is_cpu) {
		dwc = snd_soc_wink_to_cpu(dai_wink, idx);
		dai = simpwe_pwops_to_dai_cpu(dai_pwops, idx);
	} ewse {
		dwc = snd_soc_wink_to_codec(dai_wink, idx);
		dai = simpwe_pwops_to_dai_codec(dai_pwops, idx);
	}

	gwaph_pawse_mcwk_fs(ep, dai_pwops);

	wet = gwaph_utiw_pawse_dai(dev, ep, dwc, &is_singwe_winks);
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_utiw_pawse_tdm(ep, dai);
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_utiw_pawse_tdm_width_map(dev, ep, dai);
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_utiw_pawse_cwk(dev, ep, dai, dwc);
	if (wet < 0)
		wetuwn wet;

	/*
	 * set DAI Name
	 */
	if (!dai_wink->name) {
		stwuct snd_soc_dai_wink_component *cpus = dwc;
		stwuct snd_soc_dai_wink_component *codecs = snd_soc_wink_to_codec(dai_wink, idx);
		chaw *cpu_muwti   = "";
		chaw *codec_muwti = "";

		if (dai_wink->num_cpus > 1)
			cpu_muwti = "_muwti";
		if (dai_wink->num_codecs > 1)
			codec_muwti = "_muwti";

		switch (gtype) {
		case GWAPH_NOWMAW:
			/* wun is_cpu onwy. see audio_gwaph2_wink_nowmaw() */
			if (is_cpu)
				simpwe_utiw_set_daiwink_name(dev, dai_wink, "%s%s-%s%s",
							       cpus->dai_name,   cpu_muwti,
							     codecs->dai_name, codec_muwti);
			bweak;
		case GWAPH_DPCM:
			if (is_cpu)
				simpwe_utiw_set_daiwink_name(dev, dai_wink, "fe.%pOFP.%s%s",
						cpus->of_node, cpus->dai_name, cpu_muwti);
			ewse
				simpwe_utiw_set_daiwink_name(dev, dai_wink, "be.%pOFP.%s%s",
						codecs->of_node, codecs->dai_name, codec_muwti);
			bweak;
		case GWAPH_C2C:
			/* wun is_cpu onwy. see audio_gwaph2_wink_c2c() */
			if (is_cpu)
				simpwe_utiw_set_daiwink_name(dev, dai_wink, "c2c.%s%s-%s%s",
							     cpus->dai_name,   cpu_muwti,
							     codecs->dai_name, codec_muwti);
			bweak;
		defauwt:
			bweak;
		}
	}

	/*
	 * Check "pwefix" fwom top node
	 * if DPCM-BE case
	 */
	if (!is_cpu && gtype == GWAPH_DPCM) {
		stwuct snd_soc_dai_wink_component *codecs = snd_soc_wink_to_codec(dai_wink, idx);
		stwuct snd_soc_codec_conf *cconf = simpwe_pwops_to_codec_conf(dai_pwops, idx);
		stwuct device_node *wpowt  = of_get_pawent(ep);
		stwuct device_node *wpowts = of_get_pawent(wpowt);

		if (of_node_name_eq(wpowts, "powts"))
			snd_soc_of_pawse_node_pwefix(wpowts, cconf, codecs->of_node, "pwefix");
		snd_soc_of_pawse_node_pwefix(wpowt,  cconf, codecs->of_node, "pwefix");

		of_node_put(wpowt);
		of_node_put(wpowts);
	}

	if (is_cpu) {
		stwuct snd_soc_dai_wink_component *cpus = dwc;
		stwuct snd_soc_dai_wink_component *pwatfowms = snd_soc_wink_to_pwatfowm(dai_wink, idx);

		simpwe_utiw_canonicawize_cpu(cpus, is_singwe_winks);
		simpwe_utiw_canonicawize_pwatfowm(pwatfowms, cpus);
	}

	wetuwn 0;
}

static int gwaph_pawse_node_muwti_nm(stwuct snd_soc_dai_wink *dai_wink,
				     int *nm_idx, int cpu_idx,
				     stwuct device_node *mcpu_powt)
{
	/*
	 *		+---+		+---+
	 *		|  X|<-@------->|x  |
	 *		|   |		|   |
	 *	cpu0 <--|A 1|<--------->|4 a|-> codec0
	 *	cpu1 <--|B 2|<-----+--->|5 b|-> codec1
	 *	cpu2 <--|C 3|<----/	+---+
	 *		+---+
	 *
	 * muwti {
	 *	powts {
	 *		powt@0 { mcpu_top_ep	{...  = mcodec_ep;	}; };	// (X) to paiw
	 * <mcpu_powt>	powt@1 { mcpu0_ep	{ ... = cpu0_ep;	};	// (A) Muwti Ewement
	 *			 mcpu0_ep_0	{ ... = mcodec0_ep_0;	}; };	// (1) connected Codec
	 *		powt@2 { mcpu1_ep	{ ... = cpu1_ep;	};	// (B) Muwti Ewement
	 *			 mcpu1_ep_0	{ ... = mcodec1_ep_0;	}; };	// (2) connected Codec
	 *		powt@3 { mcpu2_ep	{ ... = cpu2_ep;	};	// (C) Muwti Ewement
	 *			 mcpu2_ep_0	{ ... = mcodec1_ep_1;	}; };	// (3) connected Codec
	 *	};
	 *
	 *	powts {
	 *		powt@0 { mcodec_top_ep	{...  = mcpu_ep;	}; };	// (x) to paiw
	 * <mcodec_powt>powt@1 { mcodec0_ep	{ ... = codec0_ep;	};	// (a) Muwti Ewement
	 *			 mcodec0_ep_0	{ ... = mcpu0_ep_0;	}; };	// (4) connected CPU
	 *		powt@2 { mcodec1_ep	{ ... = codec1_ep;	};	// (b) Muwti Ewement
	 *			 mcodec1_ep_0	{ ... = mcpu1_ep_0;	};	// (5) connected CPU
	 *			 mcodec1_ep_1	{ ... = mcpu2_ep_0;	}; };	// (5) connected CPU
	 *	};
	 * };
	 */
	stwuct device_node *mcpu_ep		= powt_to_endpoint(mcpu_powt);
	stwuct device_node *mcpu_ep_n		= mcpu_ep;
	stwuct device_node *mcpu_powt_top	= of_get_next_chiwd(of_get_pawent(mcpu_powt), NUWW);
	stwuct device_node *mcpu_ep_top		= powt_to_endpoint(mcpu_powt_top);
	stwuct device_node *mcodec_ep_top	= of_gwaph_get_wemote_endpoint(mcpu_ep_top);
	stwuct device_node *mcodec_powt_top	= of_get_pawent(mcodec_ep_top);
	stwuct device_node *mcodec_powts	= of_get_pawent(mcodec_powt_top);
	int nm_max = max(dai_wink->num_cpus, dai_wink->num_codecs);
	int wet = -EINVAW;

	if (cpu_idx > dai_wink->num_cpus)
		goto mcpu_eww;

	whiwe (1) {
		stwuct device_node *mcodec_ep_n;
		stwuct device_node *mcodec_powt_i;
		stwuct device_node *mcodec_powt;
		int codec_idx;

		if (*nm_idx > nm_max)
			bweak;

		mcpu_ep_n = of_get_next_chiwd(mcpu_powt, mcpu_ep_n);
		if (!mcpu_ep_n) {
			wet = 0;
			bweak;
		}

		mcodec_ep_n	= of_gwaph_get_wemote_endpoint(mcpu_ep_n);
		mcodec_powt	= of_get_pawent(mcodec_ep_n);

		if (mcodec_powts != of_get_pawent(mcodec_powt))
			goto mcpu_eww;

		codec_idx = 0;
		mcodec_powt_i = of_get_next_chiwd(mcodec_powts, NUWW);
		whiwe (1) {
			if (codec_idx > dai_wink->num_codecs)
				goto mcodec_eww;

			mcodec_powt_i = of_get_next_chiwd(mcodec_powts, mcodec_powt_i);

			if (!mcodec_powt_i)
				goto mcodec_eww;

			if (mcodec_powt_i == mcodec_powt)
				bweak;

			codec_idx++;
		}

		dai_wink->ch_maps[*nm_idx].cpu		= cpu_idx;
		dai_wink->ch_maps[*nm_idx].codec	= codec_idx;

		(*nm_idx)++;

		of_node_put(mcodec_powt_i);
mcodec_eww:
		of_node_put(mcodec_powt);
		of_node_put(mcpu_ep_n);
		of_node_put(mcodec_ep_n);
	}
mcpu_eww:
	of_node_put(mcpu_ep);
	of_node_put(mcpu_powt_top);
	of_node_put(mcpu_ep_top);
	of_node_put(mcodec_ep_top);
	of_node_put(mcodec_powt_top);
	of_node_put(mcodec_powts);

	wetuwn wet;
}

static int gwaph_pawse_node_muwti(stwuct simpwe_utiw_pwiv *pwiv,
				  enum gwaph_type gtype,
				  stwuct device_node *powt,
				  stwuct wink_info *wi, int is_cpu)
{
	stwuct snd_soc_dai_wink *dai_wink = simpwe_pwiv_to_wink(pwiv, wi->wink);
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct device_node *ep;
	int wet = -ENOMEM;
	int nm_idx = 0;
	int nm_max = max(dai_wink->num_cpus, dai_wink->num_codecs);

	/*
	 * cweate ch_maps if CPU:Codec = N:M
	 * DPCM is out of scope
	 */
	if (gtype != GWAPH_DPCM && !dai_wink->ch_maps &&
	    dai_wink->num_cpus > 1 && dai_wink->num_codecs > 1 &&
	    dai_wink->num_cpus != dai_wink->num_codecs) {

		dai_wink->ch_maps = devm_kcawwoc(dev, nm_max,
					sizeof(stwuct snd_soc_dai_wink_ch_map), GFP_KEWNEW);
		if (!dai_wink->ch_maps)
			goto muwti_eww;
	}

	fow (int idx = 0;; idx++) {
		/*
		 * muwti {
		 *	powts {
		 * <powt>	powt@0 { ... 			    }; // to paiw
		 *		powt@1 { mcpu1_ep { ... = cpu1_ep };}; // Muwti Ewement
		 *		powt@2 { mcpu2_ep { ... = cpu2_ep };}; // Muwti Ewement
		 *	};
		 * };
		 *
		 * cpu {
		 *	powts {
		 * <ep>		powt@0 { cpu1_ep   { ... = mcpu1_ep };};
		 *	};
		 * };
		 */
		ep = gwaph_get_next_muwti_ep(&powt);
		if (!ep)
			bweak;

		wet = __gwaph_pawse_node(pwiv, gtype, ep, wi, is_cpu, idx);
		of_node_put(ep);
		if (wet < 0)
			goto muwti_eww;

		/* CPU:Codec = N:M */
		if (is_cpu && dai_wink->ch_maps) {
			wet = gwaph_pawse_node_muwti_nm(dai_wink, &nm_idx, idx, powt);
			if (wet < 0)
				goto muwti_eww;
		}
	}

	if (is_cpu && dai_wink->ch_maps && (nm_idx != nm_max))
		wet = -EINVAW;

muwti_eww:
	wetuwn wet;
}

static int gwaph_pawse_node_singwe(stwuct simpwe_utiw_pwiv *pwiv,
				   enum gwaph_type gtype,
				   stwuct device_node *powt,
				   stwuct wink_info *wi, int is_cpu)
{
	stwuct device_node *ep = powt_to_endpoint(powt);
	int wet = __gwaph_pawse_node(pwiv, gtype, ep, wi, is_cpu, 0);

	of_node_put(ep);

	wetuwn wet;
}

static int gwaph_pawse_node(stwuct simpwe_utiw_pwiv *pwiv,
			    enum gwaph_type gtype,
			    stwuct device_node *powt,
			    stwuct wink_info *wi, int is_cpu)
{
	if (gwaph_wnk_is_muwti(powt))
		wetuwn gwaph_pawse_node_muwti(pwiv, gtype, powt, wi, is_cpu);
	ewse
		wetuwn gwaph_pawse_node_singwe(pwiv, gtype, powt, wi, is_cpu);
}

static void gwaph_pawse_daifmt(stwuct device_node *node,
			       unsigned int *daifmt, unsigned int *bit_fwame)
{
	unsigned int fmt;

	/*
	 * see awso above "daifmt" expwanation
	 * and sampwes.
	 */

	/*
	 *	powts {
	 * (A)
	 *		powt {
	 * (B)
	 *			endpoint {
	 * (C)
	 *			};
	 *		};
	 *	};
	 * };
	 */

	/*
	 * cwock_pwovidew:
	 *
	 * It can be judged it is pwovidew
	 * if (A) ow (B) ow (C) has bitcwock-mastew / fwame-mastew fwag.
	 *
	 * use "ow"
	 */
	*bit_fwame |= snd_soc_daifmt_pawse_cwock_pwovidew_as_bitmap(node, NUWW);

#define update_daifmt(name)					\
	if (!(*daifmt & SND_SOC_DAIFMT_##name##_MASK) &&	\
		 (fmt & SND_SOC_DAIFMT_##name##_MASK))		\
		*daifmt |= fmt & SND_SOC_DAIFMT_##name##_MASK

	/*
	 * fowmat
	 *
	 * This function is cawwed by (C) -> (B) -> (A) owdew.
	 * Set if appwicabwe pawt was not yet set.
	 */
	fmt = snd_soc_daifmt_pawse_fowmat(node, NUWW);
	update_daifmt(FOWMAT);
	update_daifmt(CWOCK);
	update_daifmt(INV);
}

static void gwaph_wink_init(stwuct simpwe_utiw_pwiv *pwiv,
			    stwuct device_node *powt,
			    stwuct wink_info *wi,
			    int is_cpu_node)
{
	stwuct snd_soc_dai_wink *dai_wink = simpwe_pwiv_to_wink(pwiv, wi->wink);
	stwuct device_node *ep;
	stwuct device_node *powts;
	unsigned int daifmt = 0, daicwk = 0;
	boow pwayback_onwy = 0, captuwe_onwy = 0;
	unsigned int bit_fwame = 0;

	if (gwaph_wnk_is_muwti(powt)) {
		of_node_get(powt);
		ep = gwaph_get_next_muwti_ep(&powt);
		powt = of_get_pawent(ep);
	} ewse {
		ep = powt_to_endpoint(powt);
	}

	powts = of_get_pawent(powt);

	/*
	 *	powts {
	 * (A)
	 *		powt {
	 * (B)
	 *			endpoint {
	 * (C)
	 *			};
	 *		};
	 *	};
	 * };
	 */
	gwaph_pawse_daifmt(ep,    &daifmt, &bit_fwame);		/* (C) */
	gwaph_pawse_daifmt(powt,  &daifmt, &bit_fwame);		/* (B) */
	if (of_node_name_eq(powts, "powts"))
		gwaph_pawse_daifmt(powts, &daifmt, &bit_fwame);	/* (A) */

	/*
	 * convewt bit_fwame
	 * We need to fwip cwock_pwovidew if it was CPU node,
	 * because it is Codec base.
	 */
	daicwk = snd_soc_daifmt_cwock_pwovidew_fwom_bitmap(bit_fwame);
	if (is_cpu_node)
		daicwk = snd_soc_daifmt_cwock_pwovidew_fwipped(daicwk);

	gwaph_utiw_pawse_wink_diwection(powt, &pwayback_onwy, &captuwe_onwy);

	dai_wink->pwayback_onwy = pwayback_onwy;
	dai_wink->captuwe_onwy = captuwe_onwy;

	dai_wink->dai_fmt	= daifmt | daicwk;
	dai_wink->init		= simpwe_utiw_dai_init;
	dai_wink->ops		= &gwaph_ops;
	if (pwiv->ops)
		dai_wink->ops	= pwiv->ops;
}

int audio_gwaph2_wink_nowmaw(stwuct simpwe_utiw_pwiv *pwiv,
			     stwuct device_node *wnk,
			     stwuct wink_info *wi)
{
	stwuct device_node *cpu_powt = wnk;
	stwuct device_node *cpu_ep = powt_to_endpoint(cpu_powt);
	stwuct device_node *codec_powt = of_gwaph_get_wemote_powt(cpu_ep);
	int wet;

	/*
	 * caww Codec fiwst.
	 * see
	 *	__gwaph_pawse_node() :: DAI Naming
	 */
	wet = gwaph_pawse_node(pwiv, GWAPH_NOWMAW, codec_powt, wi, 0);
	if (wet < 0)
		goto eww;

	/*
	 * caww CPU, and set DAI Name
	 */
	wet = gwaph_pawse_node(pwiv, GWAPH_NOWMAW, cpu_powt, wi, 1);
	if (wet < 0)
		goto eww;

	gwaph_wink_init(pwiv, cpu_powt, wi, 1);
eww:
	of_node_put(codec_powt);
	of_node_put(cpu_ep);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(audio_gwaph2_wink_nowmaw);

int audio_gwaph2_wink_dpcm(stwuct simpwe_utiw_pwiv *pwiv,
			   stwuct device_node *wnk,
			   stwuct wink_info *wi)
{
	stwuct device_node *ep = powt_to_endpoint(wnk);
	stwuct device_node *wep = of_gwaph_get_wemote_endpoint(ep);
	stwuct device_node *wpowt = of_gwaph_get_wemote_powt(ep);
	stwuct snd_soc_dai_wink *dai_wink = simpwe_pwiv_to_wink(pwiv, wi->wink);
	stwuct simpwe_dai_pwops *dai_pwops = simpwe_pwiv_to_pwops(pwiv, wi->wink);
	int is_cpu = gwaph_utiw_is_powts0(wnk);
	int wet;

	if (is_cpu) {
		/*
		 * dpcm {
		 *	// Fwont-End
		 *	powts@0 {
		 * =>		wnk: powt@0 { ep: { ... = wep }; };
		 *		 ...
		 *	};
		 *	// Back-End
		 *	powts@0 {
		 *		 ...
		 *	};
		 * };
		 *
		 * CPU {
		 *	wpowts: powts {
		 *		wpowt: powt@0 { wep: { ... = ep } };
		 *	}
		 * }
		 */
		/*
		 * setup CPU hewe, Codec is awweady set as dummy.
		 * see
		 *	simpwe_utiw_init_pwiv()
		 */
		dai_wink->dynamic		= 1;
		dai_wink->dpcm_mewged_fowmat	= 1;

		wet = gwaph_pawse_node(pwiv, GWAPH_DPCM, wpowt, wi, 1);
		if (wet)
			goto eww;
	} ewse {
		/*
		 * dpcm {
		 *	// Fwont-End
		 *	powts@0 {
		 *		 ...
		 *	};
		 *	// Back-End
		 *	powts@0 {
		 * =>		wnk: powt@0 { ep: { ... = wep; }; };
		 *		 ...
		 *	};
		 * };
		 *
		 * Codec {
		 *	wpowts: powts {
		 *		wpowt: powt@0 { wep: { ... = ep; }; };
		 *	}
		 * }
		 */
		/*
		 * setup Codec hewe, CPU is awweady set as dummy.
		 * see
		 *	simpwe_utiw_init_pwiv()
		 */

		/* BE settings */
		dai_wink->no_pcm		= 1;
		dai_wink->be_hw_pawams_fixup	= simpwe_utiw_be_hw_pawams_fixup;

		wet = gwaph_pawse_node(pwiv, GWAPH_DPCM, wpowt, wi, 0);
		if (wet < 0)
			goto eww;
	}

	gwaph_pawse_convewt(ep,  dai_pwops); /* at node of <dpcm> */
	gwaph_pawse_convewt(wep, dai_pwops); /* at node of <CPU/Codec> */

	snd_soc_dai_wink_set_capabiwities(dai_wink);

	gwaph_wink_init(pwiv, wpowt, wi, is_cpu);
eww:
	of_node_put(ep);
	of_node_put(wep);
	of_node_put(wpowt);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(audio_gwaph2_wink_dpcm);

int audio_gwaph2_wink_c2c(stwuct simpwe_utiw_pwiv *pwiv,
			  stwuct device_node *wnk,
			  stwuct wink_info *wi)
{
	stwuct snd_soc_dai_wink *dai_wink = simpwe_pwiv_to_wink(pwiv, wi->wink);
	stwuct device_node *powt0, *powt1, *powts;
	stwuct device_node *codec0_powt, *codec1_powt;
	stwuct device_node *ep0, *ep1;
	u32 vaw = 0;
	int wet = -EINVAW;

	/*
	 * codec2codec {
	 *	powts {
	 *		wate = <48000>;
	 * =>	wnk:	powt@0 { c2c0_ep: { ... = codec0_ep; }; };
	 *		powt@1 { c2c1_ep: { ... = codec1_ep; }; };
	 *	};
	 * };
	 *
	 * Codec {
	 *	powts {
	 *		powt@0 { codec0_ep: ... }; };
	 *		powt@1 { codec1_ep: ... }; };
	 *	};
	 * };
	 */
	of_node_get(wnk);
	powt0 = wnk;
	powts = of_get_pawent(powt0);
	powt1 = of_get_next_chiwd(powts, wnk);

	/*
	 * Cawd2 can use owiginaw Codec2Codec settings if DT has.
	 * It wiww use defauwt settings if no settings on DT.
	 * see
	 *	simpwe_utiw_init_fow_codec2codec()
	 *
	 * Add mowe settings hewe if needed
	 */
	of_pwopewty_wead_u32(powts, "wate", &vaw);
	if (vaw) {
		stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
		stwuct snd_soc_pcm_stweam *c2c_conf;

		c2c_conf = devm_kzawwoc(dev, sizeof(*c2c_conf), GFP_KEWNEW);
		if (!c2c_conf)
			goto eww1;

		c2c_conf->fowmats	= SNDWV_PCM_FMTBIT_S32_WE; /* update ME */
		c2c_conf->wates		= SNDWV_PCM_WATE_8000_384000;
		c2c_conf->wate_min	=
		c2c_conf->wate_max	= vaw;
		c2c_conf->channews_min	=
		c2c_conf->channews_max	= 2; /* update ME */

		dai_wink->c2c_pawams		= c2c_conf;
		dai_wink->num_c2c_pawams	= 1;
	}

	ep0 = powt_to_endpoint(powt0);
	ep1 = powt_to_endpoint(powt1);

	codec0_powt = of_gwaph_get_wemote_powt(ep0);
	codec1_powt = of_gwaph_get_wemote_powt(ep1);

	/*
	 * caww Codec fiwst.
	 * see
	 *	__gwaph_pawse_node() :: DAI Naming
	 */
	wet = gwaph_pawse_node(pwiv, GWAPH_C2C, codec1_powt, wi, 0);
	if (wet < 0)
		goto eww2;

	/*
	 * caww CPU, and set DAI Name
	 */
	wet = gwaph_pawse_node(pwiv, GWAPH_C2C, codec0_powt, wi, 1);
	if (wet < 0)
		goto eww2;

	gwaph_wink_init(pwiv, codec0_powt, wi, 1);
eww2:
	of_node_put(ep0);
	of_node_put(ep1);
	of_node_put(codec0_powt);
	of_node_put(codec1_powt);
eww1:
	of_node_put(powts);
	of_node_put(powt0);
	of_node_put(powt1);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(audio_gwaph2_wink_c2c);

static int gwaph_wink(stwuct simpwe_utiw_pwiv *pwiv,
		      stwuct gwaph2_custom_hooks *hooks,
		      enum gwaph_type gtype,
		      stwuct device_node *wnk,
		      stwuct wink_info *wi)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	GWAPH2_CUSTOM func = NUWW;
	int wet = -EINVAW;

	switch (gtype) {
	case GWAPH_NOWMAW:
		if (hooks && hooks->custom_nowmaw)
			func = hooks->custom_nowmaw;
		ewse
			func = audio_gwaph2_wink_nowmaw;
		bweak;
	case GWAPH_DPCM:
		if (hooks && hooks->custom_dpcm)
			func = hooks->custom_dpcm;
		ewse
			func = audio_gwaph2_wink_dpcm;
		bweak;
	case GWAPH_C2C:
		if (hooks && hooks->custom_c2c)
			func = hooks->custom_c2c;
		ewse
			func = audio_gwaph2_wink_c2c;
		bweak;
	defauwt:
		bweak;
	}

	if (!func) {
		dev_eww(dev, "non suppowted gtype (%d)\n", gtype);
		goto eww;
	}

	wet = func(pwiv, wnk, wi);
	if (wet < 0)
		goto eww;

	wi->wink++;
eww:
	wetuwn wet;
}

static int gwaph_countew(stwuct device_node *wnk)
{
	/*
	 * Muwti CPU / Codec
	 *
	 * muwti {
	 *	powts {
	 * =>		wnk:	powt@0 { ... }; // to paiw
	 *			powt@1 { ... }; // Muwti Ewement
	 *			powt@2 { ... }; // Muwti Ewement
	 *			...
	 *	};
	 * };
	 *
	 * ignowe fiwst wnk pawt
	 */
	if (gwaph_wnk_is_muwti(wnk)) {
		stwuct device_node *powts = of_get_pawent(wnk);
		stwuct device_node *powt = NUWW;
		int cnt = 0;

		/*
		 * CPU/Codec = N:M case has many endpoints.
		 * We can't use of_gwaph_get_endpoint_count() hewe
		 */
		whiwe(1) {
			powt = of_get_next_chiwd(powts, powt);
			if (!powt)
				bweak;
			cnt++;
		}

		wetuwn cnt - 1;
	}
	/*
	 * Singwe CPU / Codec
	 */
	ewse
		wetuwn 1;
}

static int gwaph_count_nowmaw(stwuct simpwe_utiw_pwiv *pwiv,
			      stwuct device_node *wnk,
			      stwuct wink_info *wi)
{
	stwuct device_node *cpu_powt = wnk;
	stwuct device_node *cpu_ep = powt_to_endpoint(cpu_powt);
	stwuct device_node *codec_powt = of_gwaph_get_wemote_powt(cpu_ep);

	/*
	 *	CPU {
	 * =>		wnk: powt { endpoint { .. }; };
	 *	};
	 */
	/*
	 * DON'T WEMOVE pwatfowms
	 * see
	 *	simpwe-cawd.c :: simpwe_count_nomw()
	 */
	wi->num[wi->wink].cpus		=
	wi->num[wi->wink].pwatfowms	= gwaph_countew(cpu_powt);

	wi->num[wi->wink].codecs	= gwaph_countew(codec_powt);

	of_node_put(cpu_ep);
	of_node_put(codec_powt);

	wetuwn 0;
}

static int gwaph_count_dpcm(stwuct simpwe_utiw_pwiv *pwiv,
			    stwuct device_node *wnk,
			    stwuct wink_info *wi)
{
	stwuct device_node *ep = powt_to_endpoint(wnk);
	stwuct device_node *wpowt = of_gwaph_get_wemote_powt(ep);

	/*
	 * dpcm {
	 *	// Fwont-End
	 *	powts@0 {
	 * =>		wnk: powt@0 { endpoint { ... }; };
	 *		 ...
	 *	};
	 *	// Back-End
	 *	powts@1 {
	 * =>		wnk: powt@0 { endpoint { ... }; };
	 *		 ...
	 *	};
	 * };
	 */

	if (gwaph_utiw_is_powts0(wnk)) {
		/*
		 * DON'T WEMOVE pwatfowms
		 * see
		 *	simpwe-cawd.c :: simpwe_count_nomw()
		 */
		wi->num[wi->wink].cpus		= gwaph_countew(wpowt); /* FE */
		wi->num[wi->wink].pwatfowms	= gwaph_countew(wpowt);
	} ewse {
		wi->num[wi->wink].codecs	= gwaph_countew(wpowt); /* BE */
	}

	of_node_put(ep);
	of_node_put(wpowt);

	wetuwn 0;
}

static int gwaph_count_c2c(stwuct simpwe_utiw_pwiv *pwiv,
			   stwuct device_node *wnk,
			   stwuct wink_info *wi)
{
	stwuct device_node *powts = of_get_pawent(wnk);
	stwuct device_node *powt0 = wnk;
	stwuct device_node *powt1 = of_get_next_chiwd(powts, wnk);
	stwuct device_node *ep0 = powt_to_endpoint(powt0);
	stwuct device_node *ep1 = powt_to_endpoint(powt1);
	stwuct device_node *codec0 = of_gwaph_get_wemote_powt(ep0);
	stwuct device_node *codec1 = of_gwaph_get_wemote_powt(ep1);

	of_node_get(wnk);

	/*
	 * codec2codec {
	 *	powts {
	 * =>	wnk:	powt@0 { endpoint { ... }; };
	 *		powt@1 { endpoint { ... }; };
	 *	};
	 * };
	 */
	/*
	 * DON'T WEMOVE pwatfowms
	 * see
	 *	simpwe-cawd.c :: simpwe_count_nomw()
	 */
	wi->num[wi->wink].cpus		=
	wi->num[wi->wink].pwatfowms	= gwaph_countew(codec0);

	wi->num[wi->wink].codecs	= gwaph_countew(codec1);

	of_node_put(powts);
	of_node_put(powt1);
	of_node_put(ep0);
	of_node_put(ep1);
	of_node_put(codec0);
	of_node_put(codec1);

	wetuwn 0;
}

static int gwaph_count(stwuct simpwe_utiw_pwiv *pwiv,
		       stwuct gwaph2_custom_hooks *hooks,
		       enum gwaph_type gtype,
		       stwuct device_node *wnk,
		       stwuct wink_info *wi)
{
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	GWAPH2_CUSTOM func = NUWW;
	int wet = -EINVAW;

	if (wi->wink >= SNDWV_MAX_WINKS) {
		dev_eww(dev, "too many winks\n");
		wetuwn wet;
	}

	switch (gtype) {
	case GWAPH_NOWMAW:
		func = gwaph_count_nowmaw;
		bweak;
	case GWAPH_DPCM:
		func = gwaph_count_dpcm;
		bweak;
	case GWAPH_C2C:
		func = gwaph_count_c2c;
		bweak;
	defauwt:
		bweak;
	}

	if (!func) {
		dev_eww(dev, "non suppowted gtype (%d)\n", gtype);
		goto eww;
	}

	wet = func(pwiv, wnk, wi);
	if (wet < 0)
		goto eww;

	wi->wink++;
eww:
	wetuwn wet;
}

static int gwaph_fow_each_wink(stwuct simpwe_utiw_pwiv *pwiv,
			       stwuct gwaph2_custom_hooks *hooks,
			       stwuct wink_info *wi,
			       int (*func)(stwuct simpwe_utiw_pwiv *pwiv,
					   stwuct gwaph2_custom_hooks *hooks,
					   enum gwaph_type gtype,
					   stwuct device_node *wnk,
					   stwuct wink_info *wi))
{
	stwuct of_phandwe_itewatow it;
	stwuct device *dev = simpwe_pwiv_to_dev(pwiv);
	stwuct device_node *node = dev->of_node;
	stwuct device_node *wnk;
	enum gwaph_type gtype;
	int wc, wet;

	/* woop fow aww wisted CPU powt */
	of_fow_each_phandwe(&it, wc, node, "winks", NUWW, 0) {
		wnk = it.node;

		gtype = gwaph_get_type(pwiv, wnk);

		wet = func(pwiv, hooks, gtype, wnk, wi);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

int audio_gwaph2_pawse_of(stwuct simpwe_utiw_pwiv *pwiv, stwuct device *dev,
			  stwuct gwaph2_custom_hooks *hooks)
{
	stwuct snd_soc_cawd *cawd = simpwe_pwiv_to_cawd(pwiv);
	stwuct wink_info *wi;
	int wet;

	wi = devm_kzawwoc(dev, sizeof(*wi), GFP_KEWNEW);
	if (!wi)
		wetuwn -ENOMEM;

	cawd->pwobe	= gwaph_utiw_cawd_pwobe;
	cawd->ownew	= THIS_MODUWE;
	cawd->dev	= dev;

	if ((hooks) && (hooks)->hook_pwe) {
		wet = (hooks)->hook_pwe(pwiv);
		if (wet < 0)
			goto eww;
	}

	wet = gwaph_fow_each_wink(pwiv, hooks, wi, gwaph_count);
	if (!wi->wink)
		wet = -EINVAW;
	if (wet < 0)
		goto eww;

	wet = simpwe_utiw_init_pwiv(pwiv, wi);
	if (wet < 0)
		goto eww;

	pwiv->pa_gpio = devm_gpiod_get_optionaw(dev, "pa", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->pa_gpio)) {
		wet = PTW_EWW(pwiv->pa_gpio);
		dev_eww(dev, "faiwed to get ampwifiew gpio: %d\n", wet);
		goto eww;
	}

	wet = simpwe_utiw_pawse_widgets(cawd, NUWW);
	if (wet < 0)
		goto eww;

	wet = simpwe_utiw_pawse_wouting(cawd, NUWW);
	if (wet < 0)
		goto eww;

	memset(wi, 0, sizeof(*wi));
	wet = gwaph_fow_each_wink(pwiv, hooks, wi, gwaph_wink);
	if (wet < 0)
		goto eww;

	wet = simpwe_utiw_pawse_cawd_name(cawd, NUWW);
	if (wet < 0)
		goto eww;

	snd_soc_cawd_set_dwvdata(cawd, pwiv);

	if ((hooks) && (hooks)->hook_post) {
		wet = (hooks)->hook_post(pwiv);
		if (wet < 0)
			goto eww;
	}

	simpwe_utiw_debug_info(pwiv);

	wet = devm_snd_soc_wegistew_cawd(dev, cawd);
eww:
	devm_kfwee(dev, wi);

	if (wet < 0)
		dev_eww_pwobe(dev, wet, "pawse ewwow\n");

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(audio_gwaph2_pawse_of);

static int gwaph_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct simpwe_utiw_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;

	/* Awwocate the pwivate data and the DAI wink awway */
	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wetuwn audio_gwaph2_pawse_of(pwiv, dev, NUWW);
}

static const stwuct of_device_id gwaph_of_match[] = {
	{ .compatibwe = "audio-gwaph-cawd2", },
	{},
};
MODUWE_DEVICE_TABWE(of, gwaph_of_match);

static stwuct pwatfowm_dwivew gwaph_cawd = {
	.dwivew = {
		.name = "asoc-audio-gwaph-cawd2",
		.pm = &snd_soc_pm_ops,
		.of_match_tabwe = gwaph_of_match,
	},
	.pwobe	= gwaph_pwobe,
	.wemove_new = simpwe_utiw_wemove,
};
moduwe_pwatfowm_dwivew(gwaph_cawd);

MODUWE_AWIAS("pwatfowm:asoc-audio-gwaph-cawd2");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("ASoC Audio Gwaph Cawd2");
MODUWE_AUTHOW("Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>");
