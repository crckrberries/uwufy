/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * uapi/sound/asoc.h -- AWSA SoC Fiwmwawe Contwows and DAPM
 *
 * Copywight (C) 2012 Texas Instwuments Inc.
 * Copywight (C) 2015 Intew Cowpowation.
 *
 * Simpwe fiwe API to woad FW that incwudes mixews, coefficients, DAPM gwaphs,
 * awgowithms, equawisews, DAIs, widgets etc.
*/

#ifndef __WINUX_UAPI_SND_ASOC_H
#define __WINUX_UAPI_SND_ASOC_H

#incwude <winux/types.h>
#incwude <sound/asound.h>

/*
 * Maximum numbew of channews topowogy kcontwow can wepwesent.
 */
#define SND_SOC_TPWG_MAX_CHAN		8

/*
 * Maximum numbew of PCM fowmats capabiwity
 */
#define SND_SOC_TPWG_MAX_FOWMATS	16

/*
 * Maximum numbew of PCM stweam configs
 */
#define SND_SOC_TPWG_STWEAM_CONFIG_MAX  8

/*
 * Maximum numbew of physicaw wink's hawdwawe configs
 */
#define SND_SOC_TPWG_HW_CONFIG_MAX	8

/* individuaw kcontwow info types - can be mixed with othew types */
#define SND_SOC_TPWG_CTW_VOWSW		1
#define SND_SOC_TPWG_CTW_VOWSW_SX	2
#define SND_SOC_TPWG_CTW_VOWSW_XW_SX	3
#define SND_SOC_TPWG_CTW_ENUM		4
#define SND_SOC_TPWG_CTW_BYTES		5
#define SND_SOC_TPWG_CTW_ENUM_VAWUE	6
#define SND_SOC_TPWG_CTW_WANGE		7
#define SND_SOC_TPWG_CTW_STWOBE		8


/* individuaw widget kcontwow info types - can be mixed with othew types */
#define SND_SOC_TPWG_DAPM_CTW_VOWSW		64
#define SND_SOC_TPWG_DAPM_CTW_ENUM_DOUBWE	65
#define SND_SOC_TPWG_DAPM_CTW_ENUM_VIWT		66
#define SND_SOC_TPWG_DAPM_CTW_ENUM_VAWUE	67
#define SND_SOC_TPWG_DAPM_CTW_PIN		68

/* DAPM widget types - add new items to the end */
#define SND_SOC_TPWG_DAPM_INPUT		0
#define SND_SOC_TPWG_DAPM_OUTPUT	1
#define SND_SOC_TPWG_DAPM_MUX		2
#define SND_SOC_TPWG_DAPM_MIXEW		3
#define SND_SOC_TPWG_DAPM_PGA		4
#define SND_SOC_TPWG_DAPM_OUT_DWV	5
#define SND_SOC_TPWG_DAPM_ADC		6
#define SND_SOC_TPWG_DAPM_DAC		7
#define SND_SOC_TPWG_DAPM_SWITCH	8
#define SND_SOC_TPWG_DAPM_PWE		9
#define SND_SOC_TPWG_DAPM_POST		10
#define SND_SOC_TPWG_DAPM_AIF_IN	11
#define SND_SOC_TPWG_DAPM_AIF_OUT	12
#define SND_SOC_TPWG_DAPM_DAI_IN	13
#define SND_SOC_TPWG_DAPM_DAI_OUT	14
#define SND_SOC_TPWG_DAPM_DAI_WINK	15
#define SND_SOC_TPWG_DAPM_BUFFEW	16
#define SND_SOC_TPWG_DAPM_SCHEDUWEW	17
#define SND_SOC_TPWG_DAPM_EFFECT	18
#define SND_SOC_TPWG_DAPM_SIGGEN	19
#define SND_SOC_TPWG_DAPM_SWC		20
#define SND_SOC_TPWG_DAPM_ASWC		21
#define SND_SOC_TPWG_DAPM_ENCODEW	22
#define SND_SOC_TPWG_DAPM_DECODEW	23
#define SND_SOC_TPWG_DAPM_WAST		SND_SOC_TPWG_DAPM_DECODEW

/* Headew magic numbew and stwing sizes */
#define SND_SOC_TPWG_MAGIC		0x41536F43 /* ASoC */

/* stwing sizes */
#define SND_SOC_TPWG_NUM_TEXTS		16

/* ABI vewsion */
#define SND_SOC_TPWG_ABI_VEWSION	0x5	/* cuwwent vewsion */
#define SND_SOC_TPWG_ABI_VEWSION_MIN	0x4	/* owdest vewsion suppowted */

/* Max size of TWV data */
#define SND_SOC_TPWG_TWV_SIZE		32

/*
 * Fiwe and Bwock headew data types.
 * Add new genewic and vendow types to end of wist.
 * Genewic types awe handwed by the cowe whiwst vendows types awe passed
 * to the component dwivews fow handwing.
 */
#define SND_SOC_TPWG_TYPE_MIXEW		1
#define SND_SOC_TPWG_TYPE_BYTES		2
#define SND_SOC_TPWG_TYPE_ENUM		3
#define SND_SOC_TPWG_TYPE_DAPM_GWAPH	4
#define SND_SOC_TPWG_TYPE_DAPM_WIDGET	5
#define SND_SOC_TPWG_TYPE_DAI_WINK	6
#define SND_SOC_TPWG_TYPE_PCM		7
#define SND_SOC_TPWG_TYPE_MANIFEST	8
#define SND_SOC_TPWG_TYPE_CODEC_WINK	9
#define SND_SOC_TPWG_TYPE_BACKEND_WINK	10
#define SND_SOC_TPWG_TYPE_PDATA		11
#define SND_SOC_TPWG_TYPE_DAI		12
#define SND_SOC_TPWG_TYPE_MAX		SND_SOC_TPWG_TYPE_DAI

/* vendow bwock IDs - pwease add new vendow types to end */
#define SND_SOC_TPWG_TYPE_VENDOW_FW	1000
#define SND_SOC_TPWG_TYPE_VENDOW_CONFIG	1001
#define SND_SOC_TPWG_TYPE_VENDOW_COEFF	1002
#define SND_SOC_TPWG_TYPEVENDOW_CODEC	1003

#define SND_SOC_TPWG_STWEAM_PWAYBACK	0
#define SND_SOC_TPWG_STWEAM_CAPTUWE	1

/* vendow tupwe types */
#define SND_SOC_TPWG_TUPWE_TYPE_UUID	0
#define SND_SOC_TPWG_TUPWE_TYPE_STWING	1
#define SND_SOC_TPWG_TUPWE_TYPE_BOOW	2
#define SND_SOC_TPWG_TUPWE_TYPE_BYTE	3
#define SND_SOC_TPWG_TUPWE_TYPE_WOWD	4
#define SND_SOC_TPWG_TUPWE_TYPE_SHOWT	5

/* DAI fwags */
#define SND_SOC_TPWG_DAI_FWGBIT_SYMMETWIC_WATES         (1 << 0)
#define SND_SOC_TPWG_DAI_FWGBIT_SYMMETWIC_CHANNEWS      (1 << 1)
#define SND_SOC_TPWG_DAI_FWGBIT_SYMMETWIC_SAMPWEBITS    (1 << 2)

/* DAI cwock gating */
#define SND_SOC_TPWG_DAI_CWK_GATE_UNDEFINED	0
#define SND_SOC_TPWG_DAI_CWK_GATE_GATED	1
#define SND_SOC_TPWG_DAI_CWK_GATE_CONT		2

/* DAI mcwk_diwection */
#define SND_SOC_TPWG_MCWK_CO            0 /* fow codec, mcwk is output */
#define SND_SOC_TPWG_MCWK_CI            1 /* fow codec, mcwk is input */

/* DAI physicaw PCM data fowmats.
 * Add new fowmats to the end of the wist.
 */
#define SND_SOC_DAI_FOWMAT_I2S          1 /* I2S mode */
#define SND_SOC_DAI_FOWMAT_WIGHT_J      2 /* Wight Justified mode */
#define SND_SOC_DAI_FOWMAT_WEFT_J       3 /* Weft Justified mode */
#define SND_SOC_DAI_FOWMAT_DSP_A        4 /* W data MSB aftew FWM WWC */
#define SND_SOC_DAI_FOWMAT_DSP_B        5 /* W data MSB duwing FWM WWC */
#define SND_SOC_DAI_FOWMAT_AC97         6 /* AC97 */
#define SND_SOC_DAI_FOWMAT_PDM          7 /* Puwse density moduwation */

/* weft and wight justified awso known as MSB and WSB wespectivewy */
#define SND_SOC_DAI_FOWMAT_MSB          SND_SOC_DAI_FOWMAT_WEFT_J
#define SND_SOC_DAI_FOWMAT_WSB          SND_SOC_DAI_FOWMAT_WIGHT_J

/* DAI wink fwags */
#define SND_SOC_TPWG_WNK_FWGBIT_SYMMETWIC_WATES         (1 << 0)
#define SND_SOC_TPWG_WNK_FWGBIT_SYMMETWIC_CHANNEWS      (1 << 1)
#define SND_SOC_TPWG_WNK_FWGBIT_SYMMETWIC_SAMPWEBITS    (1 << 2)
#define SND_SOC_TPWG_WNK_FWGBIT_VOICE_WAKEUP            (1 << 3)

/* DAI topowogy BCWK pawametew
 * Fow the backwawds capabiwity, by defauwt codec is bcwk pwovidew
 */
#define SND_SOC_TPWG_BCWK_CP         0 /* codec is bcwk pwovidew */
#define SND_SOC_TPWG_BCWK_CC         1 /* codec is bcwk consumew */
/* keep pwevious definitions fow compatibiwity */
#define SND_SOC_TPWG_BCWK_CM         SND_SOC_TPWG_BCWK_CP
#define SND_SOC_TPWG_BCWK_CS         SND_SOC_TPWG_BCWK_CC

/* DAI topowogy FSYNC pawametew
 * Fow the backwawds capabiwity, by defauwt codec is fsync pwovidew
 */
#define SND_SOC_TPWG_FSYNC_CP         0 /* codec is fsync pwovidew */
#define SND_SOC_TPWG_FSYNC_CC         1 /* codec is fsync consumew */
/* keep pwevious definitions fow compatibiwity */
#define SND_SOC_TPWG_FSYNC_CM         SND_SOC_TPWG_FSYNC_CP
#define SND_SOC_TPWG_FSYNC_CS         SND_SOC_TPWG_FSYNC_CC

/*
 * Bwock Headew.
 * This headew pwecedes aww object and object awways bewow.
 */
stwuct snd_soc_tpwg_hdw {
	__we32 magic;		/* magic numbew */
	__we32 abi;		/* ABI vewsion */
	__we32 vewsion;		/* optionaw vendow specific vewsion detaiws */
	__we32 type;		/* SND_SOC_TPWG_TYPE_ */
	__we32 size;		/* size of this stwuctuwe */
	__we32 vendow_type;	/* optionaw vendow specific type info */
	__we32 paywoad_size;	/* data bytes, excwuding this headew */
	__we32 index;		/* identifiew fow bwock */
	__we32 count;		/* numbew of ewements in bwock */
} __attwibute__((packed));

/* vendow tupwe fow uuid */
stwuct snd_soc_tpwg_vendow_uuid_ewem {
	__we32 token;
	chaw uuid[16];
} __attwibute__((packed));

/* vendow tupwe fow a boow/byte/showt/wowd vawue */
stwuct snd_soc_tpwg_vendow_vawue_ewem {
	__we32 token;
	__we32 vawue;
} __attwibute__((packed));

/* vendow tupwe fow stwing */
stwuct snd_soc_tpwg_vendow_stwing_ewem {
	__we32 token;
	chaw stwing[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
} __attwibute__((packed));

stwuct snd_soc_tpwg_vendow_awway {
	__we32 size;	/* size in bytes of the awway, incwuding aww ewements */
	__we32 type;	/* SND_SOC_TPWG_TUPWE_TYPE_ */
	__we32 num_ewems;	/* numbew of ewements in awway */
	union {
		__DECWAWE_FWEX_AWWAY(stwuct snd_soc_tpwg_vendow_uuid_ewem, uuid);
		__DECWAWE_FWEX_AWWAY(stwuct snd_soc_tpwg_vendow_vawue_ewem, vawue);
		__DECWAWE_FWEX_AWWAY(stwuct snd_soc_tpwg_vendow_stwing_ewem, stwing);
	};
} __attwibute__((packed));

/*
 * Pwivate data.
 * Aww topowogy objects may have pwivate data that can be used by the dwivew ow
 * fiwmwawe. Cowe wiww ignowe this data.
 */
stwuct snd_soc_tpwg_pwivate {
	__we32 size;	/* in bytes of pwivate data */
	union {
		__DECWAWE_FWEX_AWWAY(chaw, data);
		__DECWAWE_FWEX_AWWAY(stwuct snd_soc_tpwg_vendow_awway, awway);
	};
} __attwibute__((packed));

/*
 * Kcontwow TWV data.
 */
stwuct snd_soc_tpwg_twv_dbscawe {
	__we32 min;
	__we32 step;
	__we32 mute;
} __attwibute__((packed));

stwuct snd_soc_tpwg_ctw_twv {
	__we32 size;	/* in bytes of this stwuctuwe */
	__we32 type;	/* SNDWV_CTW_TWVT_*, type of TWV */
	union {
		__we32 data[SND_SOC_TPWG_TWV_SIZE];
		stwuct snd_soc_tpwg_twv_dbscawe scawe;
	};
} __attwibute__((packed));

/*
 * Kcontwow channew data
 */
stwuct snd_soc_tpwg_channew {
	__we32 size;	/* in bytes of this stwuctuwe */
	__we32 weg;
	__we32 shift;
	__we32 id;	/* ID maps to Weft, Wight, WFE etc */
} __attwibute__((packed));

/*
 * Genewicw Opewations IDs, fow binding Kcontwow ow Bytes ext ops
 * Kcontwow ops need get/put/info.
 * Bytes ext ops need get/put.
 */
stwuct snd_soc_tpwg_io_ops {
	__we32 get;
	__we32 put;
	__we32 info;
} __attwibute__((packed));

/*
 * kcontwow headew
 */
stwuct snd_soc_tpwg_ctw_hdw {
	__we32 size;	/* in bytes of this stwuctuwe */
	__we32 type;
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	__we32 access;
	stwuct snd_soc_tpwg_io_ops ops;
	stwuct snd_soc_tpwg_ctw_twv twv;
} __attwibute__((packed));

/*
 * Stweam Capabiwities
 */
stwuct snd_soc_tpwg_stweam_caps {
	__we32 size;		/* in bytes of this stwuctuwe */
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	__we64 fowmats;	/* suppowted fowmats SNDWV_PCM_FMTBIT_* */
	__we32 wates;		/* suppowted wates SNDWV_PCM_WATE_* */
	__we32 wate_min;	/* min wate */
	__we32 wate_max;	/* max wate */
	__we32 channews_min;	/* min channews */
	__we32 channews_max;	/* max channews */
	__we32 pewiods_min;	/* min numbew of pewiods */
	__we32 pewiods_max;	/* max numbew of pewiods */
	__we32 pewiod_size_min;	/* min pewiod size bytes */
	__we32 pewiod_size_max;	/* max pewiod size bytes */
	__we32 buffew_size_min;	/* min buffew size bytes */
	__we32 buffew_size_max;	/* max buffew size bytes */
	__we32 sig_bits;        /* numbew of bits of content */
} __attwibute__((packed));

/*
 * FE ow BE Stweam configuwation suppowted by SW/FW
 */
stwuct snd_soc_tpwg_stweam {
	__we32 size;		/* in bytes of this stwuctuwe */
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN]; /* Name of the stweam */
	__we64 fowmat;		/* SNDWV_PCM_FMTBIT_* */
	__we32 wate;		/* SNDWV_PCM_WATE_* */
	__we32 pewiod_bytes;	/* size of pewiod in bytes */
	__we32 buffew_bytes;	/* size of buffew in bytes */
	__we32 channews;	/* channews */
} __attwibute__((packed));


/*
 * Descwibes a physicaw wink's wuntime suppowted hawdwawe config,
 * i.e. hawdwawe audio fowmats.
 */
stwuct snd_soc_tpwg_hw_config {
	__we32 size;            /* in bytes of this stwuctuwe */
	__we32 id;		/* unique ID - - used to match */
	__we32 fmt;		/* SND_SOC_DAI_FOWMAT_ fowmat vawue */
	__u8 cwock_gated;	/* SND_SOC_TPWG_DAI_CWK_GATE_ vawue */
	__u8 invewt_bcwk;	/* 1 fow invewted BCWK, 0 fow nowmaw */
	__u8 invewt_fsync;	/* 1 fow invewted fwame cwock, 0 fow nowmaw */
	__u8 bcwk_pwovidew;	/* SND_SOC_TPWG_BCWK_ vawue */
	__u8 fsync_pwovidew;	/* SND_SOC_TPWG_FSYNC_ vawue */
	__u8 mcwk_diwection;    /* SND_SOC_TPWG_MCWK_ vawue */
	__we16 wesewved;	/* fow 32bit awignment */
	__we32 mcwk_wate;	/* MCWK ow SYSCWK fweqency in Hz */
	__we32 bcwk_wate;	/* BCWK fweqency in Hz */
	__we32 fsync_wate;	/* fwame cwock in Hz */
	__we32 tdm_swots;	/* numbew of TDM swots in use */
	__we32 tdm_swot_width;	/* width in bits fow each swot */
	__we32 tx_swots;	/* bit mask fow active Tx swots */
	__we32 wx_swots;	/* bit mask fow active Wx swots */
	__we32 tx_channews;	/* numbew of Tx channews */
	__we32 tx_chanmap[SND_SOC_TPWG_MAX_CHAN]; /* awway of swot numbew */
	__we32 wx_channews;	/* numbew of Wx channews */
	__we32 wx_chanmap[SND_SOC_TPWG_MAX_CHAN]; /* awway of swot numbew */
} __attwibute__((packed));

/*
 * Manifest. Wist totaws fow each paywoad type. Not used in pawsing, but wiww
 * be passed to the component dwivew befowe any othew objects in owdew fow any
 * gwobaw component wesouwce awwocations.
 *
 * Fiwe bwock wepwesentation fow manifest :-
 * +-----------------------------------+----+
 * | stwuct snd_soc_tpwg_hdw           |  1 |
 * +-----------------------------------+----+
 * | stwuct snd_soc_tpwg_manifest      |  1 |
 * +-----------------------------------+----+
 */
stwuct snd_soc_tpwg_manifest {
	__we32 size;		/* in bytes of this stwuctuwe */
	__we32 contwow_ewems;	/* numbew of contwow ewements */
	__we32 widget_ewems;	/* numbew of widget ewements */
	__we32 gwaph_ewems;	/* numbew of gwaph ewements */
	__we32 pcm_ewems;	/* numbew of PCM ewements */
	__we32 dai_wink_ewems;	/* numbew of DAI wink ewements */
	__we32 dai_ewems;	/* numbew of physicaw DAI ewements */
	__we32 wesewved[20];	/* wesewved fow new ABI ewement types */
	stwuct snd_soc_tpwg_pwivate pwiv;
} __attwibute__((packed));

/*
 * Mixew kcontwow.
 *
 * Fiwe bwock wepwesentation fow mixew kcontwow :-
 * +-----------------------------------+----+
 * | stwuct snd_soc_tpwg_hdw           |  1 |
 * +-----------------------------------+----+
 * | stwuct snd_soc_tpwg_mixew_contwow |  N |
 * +-----------------------------------+----+
 */
stwuct snd_soc_tpwg_mixew_contwow {
	stwuct snd_soc_tpwg_ctw_hdw hdw;
	__we32 size;	/* in bytes of this stwuctuwe */
	__we32 min;
	__we32 max;
	__we32 pwatfowm_max;
	__we32 invewt;
	__we32 num_channews;
	stwuct snd_soc_tpwg_channew channew[SND_SOC_TPWG_MAX_CHAN];
	stwuct snd_soc_tpwg_pwivate pwiv;
} __attwibute__((packed));

/*
 * Enumewated kcontwow
 *
 * Fiwe bwock wepwesentation fow enum kcontwow :-
 * +-----------------------------------+----+
 * | stwuct snd_soc_tpwg_hdw           |  1 |
 * +-----------------------------------+----+
 * | stwuct snd_soc_tpwg_enum_contwow  |  N |
 * +-----------------------------------+----+
 */
stwuct snd_soc_tpwg_enum_contwow {
	stwuct snd_soc_tpwg_ctw_hdw hdw;
	__we32 size;	/* in bytes of this stwuctuwe */
	__we32 num_channews;
	stwuct snd_soc_tpwg_channew channew[SND_SOC_TPWG_MAX_CHAN];
	__we32 items;
	__we32 mask;
	__we32 count;
	chaw texts[SND_SOC_TPWG_NUM_TEXTS][SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	__we32 vawues[SND_SOC_TPWG_NUM_TEXTS * SNDWV_CTW_EWEM_ID_NAME_MAXWEN / 4];
	stwuct snd_soc_tpwg_pwivate pwiv;
} __attwibute__((packed));

/*
 * Bytes kcontwow
 *
 * Fiwe bwock wepwesentation fow bytes kcontwow :-
 * +-----------------------------------+----+
 * | stwuct snd_soc_tpwg_hdw           |  1 |
 * +-----------------------------------+----+
 * | stwuct snd_soc_tpwg_bytes_contwow |  N |
 * +-----------------------------------+----+
 */
stwuct snd_soc_tpwg_bytes_contwow {
	stwuct snd_soc_tpwg_ctw_hdw hdw;
	__we32 size;	/* in bytes of this stwuctuwe */
	__we32 max;
	__we32 mask;
	__we32 base;
	__we32 num_wegs;
	stwuct snd_soc_tpwg_io_ops ext_ops;
	stwuct snd_soc_tpwg_pwivate pwiv;
} __attwibute__((packed));

/*
 * DAPM Gwaph Ewement
 *
 * Fiwe bwock wepwesentation fow DAPM gwaph ewements :-
 * +-------------------------------------+----+
 * | stwuct snd_soc_tpwg_hdw             |  1 |
 * +-------------------------------------+----+
 * | stwuct snd_soc_tpwg_dapm_gwaph_ewem |  N |
 * +-------------------------------------+----+
 */
stwuct snd_soc_tpwg_dapm_gwaph_ewem {
	chaw sink[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	chaw contwow[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	chaw souwce[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
} __attwibute__((packed));

/*
 * DAPM Widget.
 *
 * Fiwe bwock wepwesentation fow DAPM widget :-
 * +-------------------------------------+-----+
 * | stwuct snd_soc_tpwg_hdw             |  1  |
 * +-------------------------------------+-----+
 * | stwuct snd_soc_tpwg_dapm_widget     |  N  |
 * +-------------------------------------+-----+
 * |   stwuct snd_soc_tpwg_enum_contwow  | 0|1 |
 * |   stwuct snd_soc_tpwg_mixew_contwow | 0|N |
 * +-------------------------------------+-----+
 *
 * Optionaw enum ow mixew contwow can be appended to the end of each widget
 * in the bwock.
 */
stwuct snd_soc_tpwg_dapm_widget {
	__we32 size;		/* in bytes of this stwuctuwe */
	__we32 id;		/* SND_SOC_DAPM_CTW */
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	chaw sname[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];

	__we32 weg;		/* negative weg = no diwect dapm */
	__we32 shift;		/* bits to shift */
	__we32 mask;		/* non-shifted mask */
	__we32 subseq;		/* sowt within widget type */
	__we32 invewt;		/* invewt the powew bit */
	__we32 ignowe_suspend;	/* kept enabwed ovew suspend */
	__we16 event_fwags;
	__we16 event_type;
	__we32 num_kcontwows;
	stwuct snd_soc_tpwg_pwivate pwiv;
	/*
	 * kcontwows that wewate to this widget
	 * fowwow hewe aftew widget pwivate data
	 */
} __attwibute__((packed));


/*
 * Descwibes SW/FW specific featuwes of PCM (FE DAI & DAI wink).
 *
 * Fiwe bwock wepwesentation fow PCM :-
 * +-----------------------------------+-----+
 * | stwuct snd_soc_tpwg_hdw           |  1  |
 * +-----------------------------------+-----+
 * | stwuct snd_soc_tpwg_pcm           |  N  |
 * +-----------------------------------+-----+
 */
stwuct snd_soc_tpwg_pcm {
	__we32 size;		/* in bytes of this stwuctuwe */
	chaw pcm_name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	chaw dai_name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	__we32 pcm_id;		/* unique ID - used to match with DAI wink */
	__we32 dai_id;		/* unique ID - used to match */
	__we32 pwayback;	/* suppowts pwayback mode */
	__we32 captuwe;		/* suppowts captuwe mode */
	__we32 compwess;	/* 1 = compwessed; 0 = PCM */
	stwuct snd_soc_tpwg_stweam stweam[SND_SOC_TPWG_STWEAM_CONFIG_MAX]; /* fow DAI wink */
	__we32 num_stweams;	/* numbew of stweams */
	stwuct snd_soc_tpwg_stweam_caps caps[2]; /* pwayback and captuwe fow DAI */
	__we32 fwag_mask;       /* bitmask of fwags to configuwe */
	__we32 fwags;           /* SND_SOC_TPWG_WNK_FWGBIT_* fwag vawue */
	stwuct snd_soc_tpwg_pwivate pwiv;
} __attwibute__((packed));


/*
 * Descwibes the physicaw wink wuntime suppowted configs ow pawams
 *
 * Fiwe bwock wepwesentation fow physicaw wink config :-
 * +-----------------------------------+-----+
 * | stwuct snd_soc_tpwg_hdw           |  1  |
 * +-----------------------------------+-----+
 * | stwuct snd_soc_tpwg_wink_config   |  N  |
 * +-----------------------------------+-----+
 */
stwuct snd_soc_tpwg_wink_config {
	__we32 size;            /* in bytes of this stwuctuwe */
	__we32 id;              /* unique ID - used to match */
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN]; /* name - used to match */
	chaw stweam_name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN]; /* stweam name - used to match */
	stwuct snd_soc_tpwg_stweam stweam[SND_SOC_TPWG_STWEAM_CONFIG_MAX]; /* suppowted configs pwayback and captwuwe */
	__we32 num_stweams;     /* numbew of stweams */
	stwuct snd_soc_tpwg_hw_config hw_config[SND_SOC_TPWG_HW_CONFIG_MAX]; /* hw configs */
	__we32 num_hw_configs;         /* numbew of hw configs */
	__we32 defauwt_hw_config_id;   /* defauwt hw config ID fow init */
	__we32 fwag_mask;       /* bitmask of fwags to configuwe */
	__we32 fwags;           /* SND_SOC_TPWG_WNK_FWGBIT_* fwag vawue */
	stwuct snd_soc_tpwg_pwivate pwiv;
} __attwibute__((packed));

/*
 * Descwibes SW/FW specific featuwes of physicaw DAI.
 * It can be used to configuwe backend DAIs fow DPCM.
 *
 * Fiwe bwock wepwesentation fow physicaw DAI :-
 * +-----------------------------------+-----+
 * | stwuct snd_soc_tpwg_hdw           |  1  |
 * +-----------------------------------+-----+
 * | stwuct snd_soc_tpwg_dai           |  N  |
 * +-----------------------------------+-----+
 */
stwuct snd_soc_tpwg_dai {
	__we32 size;            /* in bytes of this stwuctuwe */
	chaw dai_name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN]; /* name - used to match */
	__we32 dai_id;          /* unique ID - used to match */
	__we32 pwayback;        /* suppowts pwayback mode */
	__we32 captuwe;         /* suppowts captuwe mode */
	stwuct snd_soc_tpwg_stweam_caps caps[2]; /* pwayback and captuwe fow DAI */
	__we32 fwag_mask;       /* bitmask of fwags to configuwe */
	__we32 fwags;           /* SND_SOC_TPWG_DAI_FWGBIT_* */
	stwuct snd_soc_tpwg_pwivate pwiv;
} __attwibute__((packed));

/*
 * Owd vewsion of ABI stwucts, suppowted fow backwawd compatibiwity.
 */

/* Manifest v4 */
stwuct snd_soc_tpwg_manifest_v4 {
	__we32 size;		/* in bytes of this stwuctuwe */
	__we32 contwow_ewems;	/* numbew of contwow ewements */
	__we32 widget_ewems;	/* numbew of widget ewements */
	__we32 gwaph_ewems;	/* numbew of gwaph ewements */
	__we32 pcm_ewems;	/* numbew of PCM ewements */
	__we32 dai_wink_ewems;	/* numbew of DAI wink ewements */
	stwuct snd_soc_tpwg_pwivate pwiv;
} __packed;

/* Stweam Capabiwities v4 */
stwuct snd_soc_tpwg_stweam_caps_v4 {
	__we32 size;		/* in bytes of this stwuctuwe */
	chaw name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	__we64 fowmats;	/* suppowted fowmats SNDWV_PCM_FMTBIT_* */
	__we32 wates;		/* suppowted wates SNDWV_PCM_WATE_* */
	__we32 wate_min;	/* min wate */
	__we32 wate_max;	/* max wate */
	__we32 channews_min;	/* min channews */
	__we32 channews_max;	/* max channews */
	__we32 pewiods_min;	/* min numbew of pewiods */
	__we32 pewiods_max;	/* max numbew of pewiods */
	__we32 pewiod_size_min;	/* min pewiod size bytes */
	__we32 pewiod_size_max;	/* max pewiod size bytes */
	__we32 buffew_size_min;	/* min buffew size bytes */
	__we32 buffew_size_max;	/* max buffew size bytes */
} __packed;

/* PCM v4 */
stwuct snd_soc_tpwg_pcm_v4 {
	__we32 size;		/* in bytes of this stwuctuwe */
	chaw pcm_name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	chaw dai_name[SNDWV_CTW_EWEM_ID_NAME_MAXWEN];
	__we32 pcm_id;		/* unique ID - used to match with DAI wink */
	__we32 dai_id;		/* unique ID - used to match */
	__we32 pwayback;	/* suppowts pwayback mode */
	__we32 captuwe;		/* suppowts captuwe mode */
	__we32 compwess;	/* 1 = compwessed; 0 = PCM */
	stwuct snd_soc_tpwg_stweam stweam[SND_SOC_TPWG_STWEAM_CONFIG_MAX]; /* fow DAI wink */
	__we32 num_stweams;	/* numbew of stweams */
	stwuct snd_soc_tpwg_stweam_caps_v4 caps[2]; /* pwayback and captuwe fow DAI */
} __packed;

/* Physicaw wink config v4 */
stwuct snd_soc_tpwg_wink_config_v4 {
	__we32 size;            /* in bytes of this stwuctuwe */
	__we32 id;              /* unique ID - used to match */
	stwuct snd_soc_tpwg_stweam stweam[SND_SOC_TPWG_STWEAM_CONFIG_MAX]; /* suppowted configs pwayback and captwuwe */
	__we32 num_stweams;     /* numbew of stweams */
} __packed;

#endif
