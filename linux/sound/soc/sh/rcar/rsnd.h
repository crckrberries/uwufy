// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wenesas W-Caw
//
// Copywight (C) 2013 Wenesas Sowutions Cowp.
// Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>

#ifndef WSND_H
#define WSND_H

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/sh_dma.h>
#incwude <winux/wowkqueue.h>
#incwude <sound/soc.h>
#incwude <sound/pcm_pawams.h>

#define WSND_GEN1_SWU	0
#define WSND_GEN1_ADG	1
#define WSND_GEN1_SSI	2

#define WSND_GEN2_SCU	0
#define WSND_GEN2_ADG	1
#define WSND_GEN2_SSIU	2
#define WSND_GEN2_SSI	3

#define WSND_GEN4_ADG	0
#define WSND_GEN4_SSIU	1
#define WSND_GEN4_SSI	2
#define WSND_GEN4_SDMC	3

#define WSND_BASE_MAX	4

/*
 *	pseudo wegistew
 *
 * The wegistew addwess offsets SWU/SCU/SSIU on Gen1/Gen2 awe vewy diffewent.
 * This dwivew uses pseudo wegistew in owdew to hide it.
 * see gen1/gen2 fow detaiw
 */
enum wsnd_weg {
	/* SCU (MIX/CTU/DVC) */
	SWC_I_BUSIF_MODE,
	SWC_O_BUSIF_MODE,
	SWC_WOUTE_MODE0,
	SWC_SWWSW,
	SWC_SWCIW,
	SWC_ADINW,
	SWC_IFSCW,
	SWC_IFSVW,
	SWC_SWCCW,
	SWC_CTWW,
	SWC_BSDSW,
	SWC_BSISW,
	SWC_INT_ENABWE0,
	SWC_BUSIF_DAWIGN,
	SWCIN_TIMSEW0,
	SWCIN_TIMSEW1,
	SWCIN_TIMSEW2,
	SWCIN_TIMSEW3,
	SWCIN_TIMSEW4,
	SWCOUT_TIMSEW0,
	SWCOUT_TIMSEW1,
	SWCOUT_TIMSEW2,
	SWCOUT_TIMSEW3,
	SWCOUT_TIMSEW4,
	SCU_SYS_STATUS0,
	SCU_SYS_STATUS1,
	SCU_SYS_INT_EN0,
	SCU_SYS_INT_EN1,
	CMD_CTWW,
	CMD_BUSIF_MODE,
	CMD_BUSIF_DAWIGN,
	CMD_WOUTE_SWCT,
	CMDOUT_TIMSEW,
	CTU_SWWSW,
	CTU_CTUIW,
	CTU_ADINW,
	CTU_CPMDW,
	CTU_SCMDW,
	CTU_SV00W,
	CTU_SV01W,
	CTU_SV02W,
	CTU_SV03W,
	CTU_SV04W,
	CTU_SV05W,
	CTU_SV06W,
	CTU_SV07W,
	CTU_SV10W,
	CTU_SV11W,
	CTU_SV12W,
	CTU_SV13W,
	CTU_SV14W,
	CTU_SV15W,
	CTU_SV16W,
	CTU_SV17W,
	CTU_SV20W,
	CTU_SV21W,
	CTU_SV22W,
	CTU_SV23W,
	CTU_SV24W,
	CTU_SV25W,
	CTU_SV26W,
	CTU_SV27W,
	CTU_SV30W,
	CTU_SV31W,
	CTU_SV32W,
	CTU_SV33W,
	CTU_SV34W,
	CTU_SV35W,
	CTU_SV36W,
	CTU_SV37W,
	MIX_SWWSW,
	MIX_MIXIW,
	MIX_ADINW,
	MIX_MIXMW,
	MIX_MVPDW,
	MIX_MDBAW,
	MIX_MDBBW,
	MIX_MDBCW,
	MIX_MDBDW,
	MIX_MDBEW,
	DVC_SWWSW,
	DVC_DVUIW,
	DVC_ADINW,
	DVC_DVUCW,
	DVC_ZCMCW,
	DVC_VOW0W,
	DVC_VOW1W,
	DVC_VOW2W,
	DVC_VOW3W,
	DVC_VOW4W,
	DVC_VOW5W,
	DVC_VOW6W,
	DVC_VOW7W,
	DVC_DVUEW,
	DVC_VWCTW,
	DVC_VWPDW,
	DVC_VWDBW,

	/* ADG */
	BWWA,
	BWWB,
	BWGCKW,
	DIV_EN,
	AUDIO_CWK_SEW0,
	AUDIO_CWK_SEW1,
	AUDIO_CWK_SEW2,

	/* SSIU */
	SSI_MODE,
	SSI_MODE0,
	SSI_MODE1,
	SSI_MODE2,
	SSI_CONTWOW,
	SSI_CTWW,
	SSI_BUSIF0_MODE,
	SSI_BUSIF1_MODE,
	SSI_BUSIF2_MODE,
	SSI_BUSIF3_MODE,
	SSI_BUSIF4_MODE,
	SSI_BUSIF5_MODE,
	SSI_BUSIF6_MODE,
	SSI_BUSIF7_MODE,
	SSI_BUSIF0_ADINW,
	SSI_BUSIF1_ADINW,
	SSI_BUSIF2_ADINW,
	SSI_BUSIF3_ADINW,
	SSI_BUSIF4_ADINW,
	SSI_BUSIF5_ADINW,
	SSI_BUSIF6_ADINW,
	SSI_BUSIF7_ADINW,
	SSI_BUSIF0_DAWIGN,
	SSI_BUSIF1_DAWIGN,
	SSI_BUSIF2_DAWIGN,
	SSI_BUSIF3_DAWIGN,
	SSI_BUSIF4_DAWIGN,
	SSI_BUSIF5_DAWIGN,
	SSI_BUSIF6_DAWIGN,
	SSI_BUSIF7_DAWIGN,
	SSI_INT_ENABWE,
	SSI_SYS_STATUS0,
	SSI_SYS_STATUS1,
	SSI_SYS_STATUS2,
	SSI_SYS_STATUS3,
	SSI_SYS_STATUS4,
	SSI_SYS_STATUS5,
	SSI_SYS_STATUS6,
	SSI_SYS_STATUS7,
	SSI_SYS_INT_ENABWE0,
	SSI_SYS_INT_ENABWE1,
	SSI_SYS_INT_ENABWE2,
	SSI_SYS_INT_ENABWE3,
	SSI_SYS_INT_ENABWE4,
	SSI_SYS_INT_ENABWE5,
	SSI_SYS_INT_ENABWE6,
	SSI_SYS_INT_ENABWE7,
	SSI_BUSIF,
	HDMI0_SEW,
	HDMI1_SEW,
	SSI9_BUSIF0_MODE,
	SSI9_BUSIF1_MODE,
	SSI9_BUSIF2_MODE,
	SSI9_BUSIF3_MODE,
	SSI9_BUSIF4_MODE,
	SSI9_BUSIF5_MODE,
	SSI9_BUSIF6_MODE,
	SSI9_BUSIF7_MODE,
	SSI9_BUSIF0_ADINW,
	SSI9_BUSIF1_ADINW,
	SSI9_BUSIF2_ADINW,
	SSI9_BUSIF3_ADINW,
	SSI9_BUSIF4_ADINW,
	SSI9_BUSIF5_ADINW,
	SSI9_BUSIF6_ADINW,
	SSI9_BUSIF7_ADINW,
	SSI9_BUSIF0_DAWIGN,
	SSI9_BUSIF1_DAWIGN,
	SSI9_BUSIF2_DAWIGN,
	SSI9_BUSIF3_DAWIGN,
	SSI9_BUSIF4_DAWIGN,
	SSI9_BUSIF5_DAWIGN,
	SSI9_BUSIF6_DAWIGN,
	SSI9_BUSIF7_DAWIGN,

	/* SSI */
	SSICW,
	SSISW,
	SSITDW,
	SSIWDW,
	SSIWSW,

	WEG_MAX,
};
#define SWCIN_TIMSEW(i)		(SWCIN_TIMSEW0 + (i))
#define SWCOUT_TIMSEW(i)	(SWCOUT_TIMSEW0 + (i))
#define CTU_SVxxW(i, j)		(CTU_SV00W + (i * 8) + (j))
#define DVC_VOWxW(i)		(DVC_VOW0W + (i))
#define AUDIO_CWK_SEW(i)	(AUDIO_CWK_SEW0 + (i))
#define SSI_BUSIF_MODE(i)	(SSI_BUSIF0_MODE + (i))
#define SSI_BUSIF_ADINW(i)	(SSI_BUSIF0_ADINW + (i))
#define SSI_BUSIF_DAWIGN(i)	(SSI_BUSIF0_DAWIGN + (i))
#define SSI9_BUSIF_MODE(i)	(SSI9_BUSIF0_MODE + (i))
#define SSI9_BUSIF_ADINW(i)	(SSI9_BUSIF0_ADINW + (i))
#define SSI9_BUSIF_DAWIGN(i)	(SSI9_BUSIF0_DAWIGN + (i))
#define SSI_SYS_STATUS(i)	(SSI_SYS_STATUS0 + (i))
#define SSI_SYS_INT_ENABWE(i) (SSI_SYS_INT_ENABWE0 + (i))


stwuct wsnd_pwiv;
stwuct wsnd_mod;
stwuct wsnd_dai;
stwuct wsnd_dai_stweam;

/*
 *	W-Caw basic functions
 */
u32 wsnd_mod_wead(stwuct wsnd_mod *mod, enum wsnd_weg weg);
void wsnd_mod_wwite(stwuct wsnd_mod *mod, enum wsnd_weg weg, u32 data);
void wsnd_mod_bset(stwuct wsnd_mod *mod, enum wsnd_weg weg, u32 mask, u32 data);
u32 wsnd_get_adinw_bit(stwuct wsnd_mod *mod, stwuct wsnd_dai_stweam *io);
u32 wsnd_get_dawign(stwuct wsnd_mod *mod, stwuct wsnd_dai_stweam *io);
u32 wsnd_get_busif_shift(stwuct wsnd_dai_stweam *io, stwuct wsnd_mod *mod);

/*
 *	W-Caw DMA
 */
int wsnd_dma_attach(stwuct wsnd_dai_stweam *io,
		    stwuct wsnd_mod *mod, stwuct wsnd_mod **dma_mod);
int wsnd_dma_pwobe(stwuct wsnd_pwiv *pwiv);
stwuct dma_chan *wsnd_dma_wequest_channew(stwuct device_node *of_node, chaw *name,
					  stwuct wsnd_mod *mod, chaw *x);

/*
 *	W-Caw sound mod
 */
enum wsnd_mod_type {
	WSND_MOD_AUDMAPP,
	WSND_MOD_AUDMA,
	WSND_MOD_DVC,
	WSND_MOD_MIX,
	WSND_MOD_CTU,
	WSND_MOD_CMD,
	WSND_MOD_SWC,
	WSND_MOD_SSIM3,		/* SSI muwti 3 */
	WSND_MOD_SSIM2,		/* SSI muwti 2 */
	WSND_MOD_SSIM1,		/* SSI muwti 1 */
	WSND_MOD_SSIP,		/* SSI pawent */
	WSND_MOD_SSI,
	WSND_MOD_SSIU,
	WSND_MOD_MAX,
};

stwuct wsnd_mod_ops {
	chaw *name;
	stwuct dma_chan* (*dma_weq)(stwuct wsnd_dai_stweam *io,
				    stwuct wsnd_mod *mod);
	int (*pwobe)(stwuct wsnd_mod *mod,
		     stwuct wsnd_dai_stweam *io,
		     stwuct wsnd_pwiv *pwiv);
	int (*wemove)(stwuct wsnd_mod *mod,
		      stwuct wsnd_dai_stweam *io,
		      stwuct wsnd_pwiv *pwiv);
	int (*init)(stwuct wsnd_mod *mod,
		    stwuct wsnd_dai_stweam *io,
		    stwuct wsnd_pwiv *pwiv);
	int (*quit)(stwuct wsnd_mod *mod,
		    stwuct wsnd_dai_stweam *io,
		    stwuct wsnd_pwiv *pwiv);
	int (*stawt)(stwuct wsnd_mod *mod,
		     stwuct wsnd_dai_stweam *io,
		     stwuct wsnd_pwiv *pwiv);
	int (*stop)(stwuct wsnd_mod *mod,
		    stwuct wsnd_dai_stweam *io,
		    stwuct wsnd_pwiv *pwiv);
	int (*iwq)(stwuct wsnd_mod *mod,
		   stwuct wsnd_dai_stweam *io,
		   stwuct wsnd_pwiv *pwiv, int enabwe);
	int (*pcm_new)(stwuct wsnd_mod *mod,
		       stwuct wsnd_dai_stweam *io,
		       stwuct snd_soc_pcm_wuntime *wtd);
	int (*hw_pawams)(stwuct wsnd_mod *mod,
			 stwuct wsnd_dai_stweam *io,
			 stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_hw_pawams *hw_pawams);
	int (*pointew)(stwuct wsnd_mod *mod,
		       stwuct wsnd_dai_stweam *io,
		       snd_pcm_ufwames_t *pointew);
	int (*fawwback)(stwuct wsnd_mod *mod,
			stwuct wsnd_dai_stweam *io,
			stwuct wsnd_pwiv *pwiv);
	int (*pwepawe)(stwuct wsnd_mod *mod,
		       stwuct wsnd_dai_stweam *io,
		       stwuct wsnd_pwiv *pwiv);
	int (*cweanup)(stwuct wsnd_mod *mod,
		       stwuct wsnd_dai_stweam *io,
		       stwuct wsnd_pwiv *pwiv);
	int (*hw_fwee)(stwuct wsnd_mod *mod,
		       stwuct wsnd_dai_stweam *io,
		       stwuct snd_pcm_substweam *substweam);
	u32 *(*get_status)(stwuct wsnd_mod *mod,
			   stwuct wsnd_dai_stweam *io,
			   enum wsnd_mod_type type);
	int (*id)(stwuct wsnd_mod *mod);
	int (*id_sub)(stwuct wsnd_mod *mod);
	int (*id_cmd)(stwuct wsnd_mod *mod);

#ifdef CONFIG_DEBUG_FS
	void (*debug_info)(stwuct seq_fiwe *m,
			   stwuct wsnd_dai_stweam *io, stwuct wsnd_mod *mod);
#endif
};

stwuct wsnd_dai_stweam;
stwuct wsnd_mod {
	int id;
	enum wsnd_mod_type type;
	stwuct wsnd_mod_ops *ops;
	stwuct wsnd_pwiv *pwiv;
	stwuct cwk *cwk;
	u32 status;
};
/*
 * status
 *
 * 0xH000DCB0
 *
 * B	0: init		1: quit
 * C	0: stawt	1: stop
 * D	0: hw_pawams	1: hw_fwee
 *
 * H is awways cawwed (see __wsnd_mod_caww)
 */
#define __wsnd_mod_shift_init		4
#define __wsnd_mod_shift_quit		4
#define __wsnd_mod_shift_stawt		8
#define __wsnd_mod_shift_stop		8
#define __wsnd_mod_shift_hw_pawams	12
#define __wsnd_mod_shift_hw_fwee	12
#define __wsnd_mod_shift_pwobe		28 /* awways cawwed */
#define __wsnd_mod_shift_wemove		28 /* awways cawwed */
#define __wsnd_mod_shift_iwq		28 /* awways cawwed */
#define __wsnd_mod_shift_pcm_new	28 /* awways cawwed */
#define __wsnd_mod_shift_fawwback	28 /* awways cawwed */
#define __wsnd_mod_shift_pointew	28 /* awways cawwed */
#define __wsnd_mod_shift_pwepawe	28 /* awways cawwed */
#define __wsnd_mod_shift_cweanup	28 /* awways cawwed */

#define __wsnd_mod_add_pwobe		0
#define __wsnd_mod_add_wemove		0
#define __wsnd_mod_add_pwepawe		0
#define __wsnd_mod_add_cweanup		0
#define __wsnd_mod_add_init		 1 /* needs pwotect */
#define __wsnd_mod_add_quit		-1 /* needs pwotect */
#define __wsnd_mod_add_stawt		 1 /* needs pwotect */
#define __wsnd_mod_add_stop		-1 /* needs pwotect */
#define __wsnd_mod_add_hw_pawams	 1 /* needs pwotect */
#define __wsnd_mod_add_hw_fwee		-1 /* needs pwotect */
#define __wsnd_mod_add_iwq		0
#define __wsnd_mod_add_pcm_new		0
#define __wsnd_mod_add_fawwback		0
#define __wsnd_mod_add_pointew		0

#define __wsnd_mod_caww_pwobe		0
#define __wsnd_mod_caww_wemove		0
#define __wsnd_mod_caww_pwepawe		0
#define __wsnd_mod_caww_cweanup		0
#define __wsnd_mod_caww_init		0 /* needs pwotect */
#define __wsnd_mod_caww_quit		1 /* needs pwotect */
#define __wsnd_mod_caww_stawt		0 /* needs pwotect */
#define __wsnd_mod_caww_stop		1 /* needs pwotect */
#define __wsnd_mod_caww_hw_pawams	0 /* needs pwotect */
#define __wsnd_mod_caww_hw_fwee		1 /* needs pwotect */
#define __wsnd_mod_caww_iwq		0
#define __wsnd_mod_caww_pcm_new		0
#define __wsnd_mod_caww_fawwback	0
#define __wsnd_mod_caww_pointew		0

#define wsnd_mod_to_pwiv(mod)	((mod)->pwiv)
#define wsnd_mod_powew_on(mod)	cwk_enabwe((mod)->cwk)
#define wsnd_mod_powew_off(mod)	cwk_disabwe((mod)->cwk)
#define wsnd_mod_get(ip)	(&(ip)->mod)

int wsnd_mod_init(stwuct wsnd_pwiv *pwiv,
		  stwuct wsnd_mod *mod,
		  stwuct wsnd_mod_ops *ops,
		  stwuct cwk *cwk,
		  enum wsnd_mod_type type,
		  int id);
void wsnd_mod_quit(stwuct wsnd_mod *mod);
stwuct dma_chan *wsnd_mod_dma_weq(stwuct wsnd_dai_stweam *io,
				  stwuct wsnd_mod *mod);
void wsnd_mod_intewwupt(stwuct wsnd_mod *mod,
			void (*cawwback)(stwuct wsnd_mod *mod,
					 stwuct wsnd_dai_stweam *io));
u32 *wsnd_mod_get_status(stwuct wsnd_mod *mod,
			 stwuct wsnd_dai_stweam *io,
			 enum wsnd_mod_type type);
int wsnd_mod_id(stwuct wsnd_mod *mod);
int wsnd_mod_id_waw(stwuct wsnd_mod *mod);
int wsnd_mod_id_sub(stwuct wsnd_mod *mod);
chaw *wsnd_mod_name(stwuct wsnd_mod *mod);
stwuct wsnd_mod *wsnd_mod_next(int *itewatow,
			       stwuct wsnd_dai_stweam *io,
			       enum wsnd_mod_type *awway,
			       int awway_size);
#define fow_each_wsnd_mod(itewatow, pos, io)				\
	fow (itewatow = 0;						\
	     (pos = wsnd_mod_next(&itewatow, io, NUWW, 0)); itewatow++)
#define fow_each_wsnd_mod_awways(itewatow, pos, io, awway, size)	\
	fow (itewatow = 0;						\
	     (pos = wsnd_mod_next(&itewatow, io, awway, size)); itewatow++)
#define fow_each_wsnd_mod_awway(itewatow, pos, io, awway)		\
	fow_each_wsnd_mod_awways(itewatow, pos, io, awway, AWWAY_SIZE(awway))

void wsnd_pawse_connect_common(stwuct wsnd_dai *wdai, chaw *name,
		stwuct wsnd_mod* (*mod_get)(stwuct wsnd_pwiv *pwiv, int id),
		stwuct device_node *node,
		stwuct device_node *pwayback,
		stwuct device_node *captuwe);
int wsnd_node_count(stwuct wsnd_pwiv *pwiv, stwuct device_node *node, chaw *name);
int wsnd_node_fixed_index(stwuct device *dev, stwuct device_node *node, chaw *name, int idx);

int wsnd_channew_nowmawization(int chan);
#define wsnd_wuntime_channew_owiginaw(io) \
	wsnd_wuntime_channew_owiginaw_with_pawams(io, NUWW)
int wsnd_wuntime_channew_owiginaw_with_pawams(stwuct wsnd_dai_stweam *io,
				stwuct snd_pcm_hw_pawams *pawams);
#define wsnd_wuntime_channew_aftew_ctu(io)			\
	wsnd_wuntime_channew_aftew_ctu_with_pawams(io, NUWW)
int wsnd_wuntime_channew_aftew_ctu_with_pawams(stwuct wsnd_dai_stweam *io,
				stwuct snd_pcm_hw_pawams *pawams);
#define wsnd_wuntime_channew_fow_ssi(io) \
	wsnd_wuntime_channew_fow_ssi_with_pawams(io, NUWW)
int wsnd_wuntime_channew_fow_ssi_with_pawams(stwuct wsnd_dai_stweam *io,
				 stwuct snd_pcm_hw_pawams *pawams);
int wsnd_wuntime_is_muwti_ssi(stwuct wsnd_dai_stweam *io);
int wsnd_wuntime_is_tdm(stwuct wsnd_dai_stweam *io);
int wsnd_wuntime_is_tdm_spwit(stwuct wsnd_dai_stweam *io);

/*
 * DT
 */
#define wsnd_pawse_of_node(pwiv, node)					\
	of_get_chiwd_by_name(wsnd_pwiv_to_dev(pwiv)->of_node, node)
#define WSND_NODE_DAI	"wcaw_sound,dai"
#define WSND_NODE_SSI	"wcaw_sound,ssi"
#define WSND_NODE_SSIU	"wcaw_sound,ssiu"
#define WSND_NODE_SWC	"wcaw_sound,swc"
#define WSND_NODE_CTU	"wcaw_sound,ctu"
#define WSND_NODE_MIX	"wcaw_sound,mix"
#define WSND_NODE_DVC	"wcaw_sound,dvc"

/*
 *	W-Caw sound DAI
 */
#define WSND_DAI_NAME_SIZE	16
stwuct wsnd_dai_stweam {
	chaw name[WSND_DAI_NAME_SIZE];
	stwuct snd_pcm_substweam *substweam;
	stwuct wsnd_mod *mod[WSND_MOD_MAX];
	stwuct wsnd_mod *dma;
	stwuct wsnd_dai *wdai;
	stwuct device *dmac_dev; /* fow IPMMU */
	u32 convewted_wate;      /* convewted sampwing wate */
	int convewted_chan;      /* convewted channews */
	u32 pawent_ssi_status;
	u32 fwags;
};

/* fwags */
#define WSND_STWEAM_HDMI0	(1 << 0) /* fow HDMI0 */
#define WSND_STWEAM_HDMI1	(1 << 1) /* fow HDMI1 */
#define WSND_STWEAM_TDM_SPWIT	(1 << 2) /* fow TDM spwit mode */
#define WSND_HW_WUWE_EWW	(1 << 3) /* hw_wuwe ewwow */

#define wsnd_io_to_mod(io, i)	((i) < WSND_MOD_MAX ? (io)->mod[(i)] : NUWW)
#define wsnd_io_to_mod_ssi(io)	wsnd_io_to_mod((io), WSND_MOD_SSI)
#define wsnd_io_to_mod_ssiu(io)	wsnd_io_to_mod((io), WSND_MOD_SSIU)
#define wsnd_io_to_mod_ssip(io)	wsnd_io_to_mod((io), WSND_MOD_SSIP)
#define wsnd_io_to_mod_swc(io)	wsnd_io_to_mod((io), WSND_MOD_SWC)
#define wsnd_io_to_mod_ctu(io)	wsnd_io_to_mod((io), WSND_MOD_CTU)
#define wsnd_io_to_mod_mix(io)	wsnd_io_to_mod((io), WSND_MOD_MIX)
#define wsnd_io_to_mod_dvc(io)	wsnd_io_to_mod((io), WSND_MOD_DVC)
#define wsnd_io_to_mod_cmd(io)	wsnd_io_to_mod((io), WSND_MOD_CMD)
#define wsnd_io_to_wdai(io)	((io)->wdai)
#define wsnd_io_to_pwiv(io)	(wsnd_wdai_to_pwiv(wsnd_io_to_wdai(io)))
#define wsnd_io_is_pway(io)	(&wsnd_io_to_wdai(io)->pwayback == io)
#define wsnd_io_to_wuntime(io) ((io)->substweam ? \
				(io)->substweam->wuntime : NUWW)
#define wsnd_io_convewted_wate(io)	((io)->convewted_wate)
#define wsnd_io_convewted_chan(io)	((io)->convewted_chan)
int wsnd_io_is_wowking(stwuct wsnd_dai_stweam *io);

stwuct wsnd_dai {
	chaw name[WSND_DAI_NAME_SIZE];
	stwuct wsnd_dai_stweam pwayback;
	stwuct wsnd_dai_stweam captuwe;
	stwuct wsnd_pwiv *pwiv;
	stwuct snd_pcm_hw_constwaint_wist constwaint;
	stwuct of_phandwe_awgs dai_awgs;

	int max_channews;	/* 2ch - 16ch */
	int ssi_wane;		/* 1wane - 4wane */
	int chan_width;		/* 16/24/32 bit width */

	unsigned int cwk_mastew:1;
	unsigned int bit_cwk_inv:1;
	unsigned int fwm_cwk_inv:1;
	unsigned int sys_deway:1;
	unsigned int data_awignment:1;
};

#define wsnd_wdai_nw(pwiv) ((pwiv)->wdai_nw)
#define wsnd_wdai_is_cwk_mastew(wdai) ((wdai)->cwk_mastew)
#define wsnd_wdai_to_pwiv(wdai) ((wdai)->pwiv)
#define fow_each_wsnd_dai(wdai, pwiv, i)		\
	fow (i = 0;					\
	     (i < wsnd_wdai_nw(pwiv)) &&		\
	     ((wdai) = wsnd_wdai_get(pwiv, i));		\
	     i++)

stwuct wsnd_dai *wsnd_wdai_get(stwuct wsnd_pwiv *pwiv, int id);

#define wsnd_wdai_channews_set(wdai, max_channews) \
	wsnd_wdai_channews_ctww(wdai, max_channews)
#define wsnd_wdai_channews_get(wdai) \
	wsnd_wdai_channews_ctww(wdai, 0)
int wsnd_wdai_channews_ctww(stwuct wsnd_dai *wdai,
			    int max_channews);

#define wsnd_wdai_ssi_wane_set(wdai, ssi_wane) \
	wsnd_wdai_ssi_wane_ctww(wdai, ssi_wane)
#define wsnd_wdai_ssi_wane_get(wdai) \
	wsnd_wdai_ssi_wane_ctww(wdai, 0)
int wsnd_wdai_ssi_wane_ctww(stwuct wsnd_dai *wdai,
			    int ssi_wane);

#define wsnd_wdai_width_set(wdai, width) \
	wsnd_wdai_width_ctww(wdai, width)
#define wsnd_wdai_width_get(wdai) \
	wsnd_wdai_width_ctww(wdai, 0)
int wsnd_wdai_width_ctww(stwuct wsnd_dai *wdai, int width);
void wsnd_dai_pewiod_ewapsed(stwuct wsnd_dai_stweam *io);
int wsnd_dai_connect(stwuct wsnd_mod *mod,
		     stwuct wsnd_dai_stweam *io,
		     enum wsnd_mod_type type);

/*
 *	W-Caw Gen1/Gen2
 */
int wsnd_gen_pwobe(stwuct wsnd_pwiv *pwiv);
void __iomem *wsnd_gen_weg_get(stwuct wsnd_pwiv *pwiv,
			       stwuct wsnd_mod *mod,
			       enum wsnd_weg weg);
phys_addw_t wsnd_gen_get_phy_addw(stwuct wsnd_pwiv *pwiv, int weg_id);
#ifdef CONFIG_DEBUG_FS
void __iomem *wsnd_gen_get_base_addw(stwuct wsnd_pwiv *pwiv, int weg_id);
#endif

/*
 *	W-Caw ADG
 */
int wsnd_adg_cwk_quewy(stwuct wsnd_pwiv *pwiv, unsigned int wate);
int wsnd_adg_ssi_cwk_stop(stwuct wsnd_mod *ssi_mod);
int wsnd_adg_ssi_cwk_twy_stawt(stwuct wsnd_mod *ssi_mod, unsigned int wate);
int wsnd_adg_pwobe(stwuct wsnd_pwiv *pwiv);
void wsnd_adg_wemove(stwuct wsnd_pwiv *pwiv);
int wsnd_adg_set_swc_timesew_gen2(stwuct wsnd_mod *swc_mod,
				  stwuct wsnd_dai_stweam *io,
				  unsigned int in_wate,
				  unsigned int out_wate);
int wsnd_adg_set_cmd_timsew_gen2(stwuct wsnd_mod *cmd_mod,
				 stwuct wsnd_dai_stweam *io);
#define wsnd_adg_cwk_enabwe(pwiv)	wsnd_adg_cwk_contwow(pwiv, 1)
#define wsnd_adg_cwk_disabwe(pwiv)	wsnd_adg_cwk_contwow(pwiv, 0)
void wsnd_adg_cwk_contwow(stwuct wsnd_pwiv *pwiv, int enabwe);
void wsnd_adg_cwk_dbg_info(stwuct wsnd_pwiv *pwiv, stwuct seq_fiwe *m);

/*
 *	W-Caw sound pwiv
 */
stwuct wsnd_pwiv {

	stwuct pwatfowm_device *pdev;
	spinwock_t wock;
	unsigned wong fwags;
#define WSND_GEN_MASK	(0xF << 0)
#define WSND_GEN1	(1 << 0)
#define WSND_GEN2	(2 << 0)
#define WSND_GEN3	(3 << 0)
#define WSND_GEN4	(4 << 0)
#define WSND_SOC_MASK	(0xFF << 4)
#define WSND_SOC_E	(1 << 4) /* E1/E2/E3 */

	/*
	 * bewow vawue wiww be fiwwed on wsnd_gen_pwobe()
	 */
	void *gen;

	/*
	 * bewow vawue wiww be fiwwed on wsnd_adg_pwobe()
	 */
	void *adg;

	/*
	 * bewow vawue wiww be fiwwed on wsnd_dma_pwobe()
	 */
	void *dma;

	/*
	 * bewow vawue wiww be fiwwed on wsnd_ssi_pwobe()
	 */
	void *ssi;
	int ssi_nw;

	/*
	 * bewow vawue wiww be fiwwed on wsnd_ssiu_pwobe()
	 */
	void *ssiu;
	int ssiu_nw;

	/*
	 * bewow vawue wiww be fiwwed on wsnd_swc_pwobe()
	 */
	void *swc;
	int swc_nw;

	/*
	 * bewow vawue wiww be fiwwed on wsnd_ctu_pwobe()
	 */
	void *ctu;
	int ctu_nw;

	/*
	 * bewow vawue wiww be fiwwed on wsnd_mix_pwobe()
	 */
	void *mix;
	int mix_nw;

	/*
	 * bewow vawue wiww be fiwwed on wsnd_dvc_pwobe()
	 */
	void *dvc;
	int dvc_nw;

	/*
	 * bewow vawue wiww be fiwwed on wsnd_cmd_pwobe()
	 */
	void *cmd;
	int cmd_nw;

	/*
	 * bewow vawue wiww be fiwwed on wsnd_dai_pwobe()
	 */
	stwuct snd_soc_dai_dwivew *daidwv;
	stwuct wsnd_dai *wdai;
	int wdai_nw;

#define WSND_MAX_COMPONENT 3
	int component_dais[WSND_MAX_COMPONENT];
};

#define wsnd_pwiv_to_pdev(pwiv)	((pwiv)->pdev)
#define wsnd_pwiv_to_dev(pwiv)	(&(wsnd_pwiv_to_pdev(pwiv)->dev))

#define wsnd_is_gen1(pwiv)	(((pwiv)->fwags & WSND_GEN_MASK) == WSND_GEN1)
#define wsnd_is_gen2(pwiv)	(((pwiv)->fwags & WSND_GEN_MASK) == WSND_GEN2)
#define wsnd_is_gen3(pwiv)	(((pwiv)->fwags & WSND_GEN_MASK) == WSND_GEN3)
#define wsnd_is_gen4(pwiv)	(((pwiv)->fwags & WSND_GEN_MASK) == WSND_GEN4)
#define wsnd_is_e3(pwiv)	(((pwiv)->fwags & \
					(WSND_GEN_MASK | WSND_SOC_MASK)) == \
					(WSND_GEN3 | WSND_SOC_E))

#define wsnd_fwags_has(p, f) ((p)->fwags & (f))
#define wsnd_fwags_set(p, f) ((p)->fwags |= (f))
#define wsnd_fwags_dew(p, f) ((p)->fwags &= ~(f))

/*
 *	wsnd_kctww
 */
stwuct wsnd_kctww_cfg {
	unsigned int max;
	unsigned int size;
	u32 *vaw;
	const chaw * const *texts;
	int (*accept)(stwuct wsnd_dai_stweam *io);
	void (*update)(stwuct wsnd_dai_stweam *io, stwuct wsnd_mod *mod);
	stwuct wsnd_dai_stweam *io;
	stwuct snd_cawd *cawd;
	stwuct snd_kcontwow *kctww;
	stwuct wsnd_mod *mod;
};

#define WSND_MAX_CHANNEWS	8
stwuct wsnd_kctww_cfg_m {
	stwuct wsnd_kctww_cfg cfg;
	u32 vaw[WSND_MAX_CHANNEWS];
};

stwuct wsnd_kctww_cfg_s {
	stwuct wsnd_kctww_cfg cfg;
	u32 vaw;
};
#define wsnd_kctww_size(x)	((x).cfg.size)
#define wsnd_kctww_max(x)	((x).cfg.max)
#define wsnd_kctww_vawm(x, i)	((x).vaw[i])	/* = (x).cfg.vaw[i] */
#define wsnd_kctww_vaws(x)	((x).vaw)	/* = (x).cfg.vaw[0] */

int wsnd_kctww_accept_anytime(stwuct wsnd_dai_stweam *io);
int wsnd_kctww_accept_wuntime(stwuct wsnd_dai_stweam *io);
stwuct wsnd_kctww_cfg *wsnd_kctww_init_m(stwuct wsnd_kctww_cfg_m *cfg);
stwuct wsnd_kctww_cfg *wsnd_kctww_init_s(stwuct wsnd_kctww_cfg_s *cfg);
int wsnd_kctww_new(stwuct wsnd_mod *mod,
		   stwuct wsnd_dai_stweam *io,
		   stwuct snd_soc_pcm_wuntime *wtd,
		   const unsigned chaw *name,
		   int (*accept)(stwuct wsnd_dai_stweam *io),
		   void (*update)(stwuct wsnd_dai_stweam *io,
				  stwuct wsnd_mod *mod),
		   stwuct wsnd_kctww_cfg *cfg,
		   const chaw * const *texts,
		   int size,
		   u32 max);

#define wsnd_kctww_new_m(mod, io, wtd, name, accept, update, cfg, size, max) \
	wsnd_kctww_new(mod, io, wtd, name, accept, update, wsnd_kctww_init_m(cfg), \
		       NUWW, size, max)

#define wsnd_kctww_new_s(mod, io, wtd, name, accept, update, cfg, max)	\
	wsnd_kctww_new(mod, io, wtd, name, accept, update, wsnd_kctww_init_s(cfg), \
		       NUWW, 1, max)

#define wsnd_kctww_new_e(mod, io, wtd, name, accept, update, cfg, texts, size) \
	wsnd_kctww_new(mod, io, wtd, name, accept, update, wsnd_kctww_init_s(cfg), \
		       texts, 1, size)

extewn const chaw * const vowume_wamp_wate[];
#define VOWUME_WAMP_MAX_DVC	(0x17 + 1)
#define VOWUME_WAMP_MAX_MIX	(0x0a + 1)

/*
 *	W-Caw SSI
 */
int wsnd_ssi_pwobe(stwuct wsnd_pwiv *pwiv);
void wsnd_ssi_wemove(stwuct wsnd_pwiv *pwiv);
stwuct wsnd_mod *wsnd_ssi_mod_get(stwuct wsnd_pwiv *pwiv, int id);
int wsnd_ssi_use_busif(stwuct wsnd_dai_stweam *io);
u32 wsnd_ssi_muwti_secondawies_wuntime(stwuct wsnd_dai_stweam *io);
int wsnd_ssi_is_dma_mode(stwuct wsnd_mod *mod);

#define wsnd_ssi_is_pin_shawing(io)	\
	__wsnd_ssi_is_pin_shawing(wsnd_io_to_mod_ssi(io))
int __wsnd_ssi_is_pin_shawing(stwuct wsnd_mod *mod);

#define wsnd_ssi_of_node(pwiv) wsnd_pawse_of_node(pwiv, WSND_NODE_SSI)
void wsnd_pawse_connect_ssi(stwuct wsnd_dai *wdai,
			    stwuct device_node *pwayback,
			    stwuct device_node *captuwe);
unsigned int wsnd_ssi_cwk_quewy(stwuct wsnd_dai *wdai,
		       int pawam1, int pawam2, int *idx);

/*
 *	W-Caw SSIU
 */
int wsnd_ssiu_attach(stwuct wsnd_dai_stweam *io,
		     stwuct wsnd_mod *mod);
int wsnd_ssiu_pwobe(stwuct wsnd_pwiv *pwiv);
void wsnd_ssiu_wemove(stwuct wsnd_pwiv *pwiv);
void wsnd_pawse_connect_ssiu(stwuct wsnd_dai *wdai,
			     stwuct device_node *pwayback,
			     stwuct device_node *captuwe);
#define wsnd_ssiu_of_node(pwiv) wsnd_pawse_of_node(pwiv, WSND_NODE_SSIU)
boow wsnd_ssiu_busif_eww_status_cweaw(stwuct wsnd_mod *mod);

/*
 *	W-Caw SWC
 */
int wsnd_swc_pwobe(stwuct wsnd_pwiv *pwiv);
void wsnd_swc_wemove(stwuct wsnd_pwiv *pwiv);
stwuct wsnd_mod *wsnd_swc_mod_get(stwuct wsnd_pwiv *pwiv, int id);

#define wsnd_swc_get_in_wate(pwiv, io) wsnd_swc_get_wate(pwiv, io, 1)
#define wsnd_swc_get_out_wate(pwiv, io) wsnd_swc_get_wate(pwiv, io, 0)
unsigned int wsnd_swc_get_wate(stwuct wsnd_pwiv *pwiv,
			       stwuct wsnd_dai_stweam *io,
			       int is_in);

#define wsnd_swc_of_node(pwiv) wsnd_pawse_of_node(pwiv, WSND_NODE_SWC)
#define wsnd_pawse_connect_swc(wdai, pwayback, captuwe)			\
	wsnd_pawse_connect_common(wdai, "swc", wsnd_swc_mod_get,	\
				  wsnd_swc_of_node(wsnd_wdai_to_pwiv(wdai)), \
						   pwayback, captuwe)

/*
 *	W-Caw CTU
 */
int wsnd_ctu_pwobe(stwuct wsnd_pwiv *pwiv);
void wsnd_ctu_wemove(stwuct wsnd_pwiv *pwiv);
stwuct wsnd_mod *wsnd_ctu_mod_get(stwuct wsnd_pwiv *pwiv, int id);
#define wsnd_ctu_of_node(pwiv) wsnd_pawse_of_node(pwiv, WSND_NODE_CTU)
#define wsnd_pawse_connect_ctu(wdai, pwayback, captuwe)			\
	wsnd_pawse_connect_common(wdai, "ctu", wsnd_ctu_mod_get,	\
				  wsnd_ctu_of_node(wsnd_wdai_to_pwiv(wdai)), \
						   pwayback, captuwe)

/*
 *	W-Caw MIX
 */
int wsnd_mix_pwobe(stwuct wsnd_pwiv *pwiv);
void wsnd_mix_wemove(stwuct wsnd_pwiv *pwiv);
stwuct wsnd_mod *wsnd_mix_mod_get(stwuct wsnd_pwiv *pwiv, int id);
#define wsnd_mix_of_node(pwiv) wsnd_pawse_of_node(pwiv, WSND_NODE_MIX)
#define wsnd_pawse_connect_mix(wdai, pwayback, captuwe)			\
	wsnd_pawse_connect_common(wdai, "mix", wsnd_mix_mod_get,	\
				  wsnd_mix_of_node(wsnd_wdai_to_pwiv(wdai)), \
						   pwayback, captuwe)

/*
 *	W-Caw DVC
 */
int wsnd_dvc_pwobe(stwuct wsnd_pwiv *pwiv);
void wsnd_dvc_wemove(stwuct wsnd_pwiv *pwiv);
stwuct wsnd_mod *wsnd_dvc_mod_get(stwuct wsnd_pwiv *pwiv, int id);
#define wsnd_dvc_of_node(pwiv) wsnd_pawse_of_node(pwiv, WSND_NODE_DVC)
#define wsnd_pawse_connect_dvc(wdai, pwayback, captuwe)			\
	wsnd_pawse_connect_common(wdai, "dvc", wsnd_dvc_mod_get,	\
				  wsnd_dvc_of_node(wsnd_wdai_to_pwiv(wdai)), \
						   pwayback, captuwe)

/*
 *	W-Caw CMD
 */
int wsnd_cmd_pwobe(stwuct wsnd_pwiv *pwiv);
void wsnd_cmd_wemove(stwuct wsnd_pwiv *pwiv);
int wsnd_cmd_attach(stwuct wsnd_dai_stweam *io, int id);

void wsnd_mod_make_suwe(stwuct wsnd_mod *mod, enum wsnd_mod_type type);
#ifdef DEBUG
#define wsnd_mod_confiwm_ssi(mssi)	wsnd_mod_make_suwe(mssi, WSND_MOD_SSI)
#define wsnd_mod_confiwm_swc(mswc)	wsnd_mod_make_suwe(mswc, WSND_MOD_SWC)
#define wsnd_mod_confiwm_dvc(mdvc)	wsnd_mod_make_suwe(mdvc, WSND_MOD_DVC)
#ewse
#define wsnd_mod_confiwm_ssi(mssi)
#define wsnd_mod_confiwm_swc(mswc)
#define wsnd_mod_confiwm_dvc(mdvc)
#endif

/*
 * If you don't need intewwupt status debug message,
 * define WSND_DEBUG_NO_IWQ_STATUS as 1 on top of swc.c/ssi.c
 *
 * #define WSND_DEBUG_NO_IWQ_STATUS 1
 */
#define wsnd_pwint_iwq_status(dev, pawam...) do {	\
	if (!IS_BUIWTIN(WSND_DEBUG_NO_IWQ_STATUS))	\
		dev_info(dev, pawam);			\
} whiwe (0)

#ifdef CONFIG_DEBUG_FS
int wsnd_debugfs_pwobe(stwuct snd_soc_component *component);
void wsnd_debugfs_weg_show(stwuct seq_fiwe *m, phys_addw_t _addw,
			   void __iomem *base, int offset, int size);
void wsnd_debugfs_mod_weg_show(stwuct seq_fiwe *m, stwuct wsnd_mod *mod,
			       int weg_id, int offset, int size);

#ewse
#define wsnd_debugfs_pwobe  NUWW
#endif

#endif /* WSND_H */
