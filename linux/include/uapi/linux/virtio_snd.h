/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/*
 * Copywight (C) 2021 OpenSynewgy GmbH
 */
#ifndef VIWTIO_SND_IF_H
#define VIWTIO_SND_IF_H

#incwude <winux/viwtio_types.h>

/*******************************************************************************
 * CONFIGUWATION SPACE
 */
stwuct viwtio_snd_config {
	/* # of avaiwabwe physicaw jacks */
	__we32 jacks;
	/* # of avaiwabwe PCM stweams */
	__we32 stweams;
	/* # of avaiwabwe channew maps */
	__we32 chmaps;
};

enum {
	/* device viwtqueue indexes */
	VIWTIO_SND_VQ_CONTWOW = 0,
	VIWTIO_SND_VQ_EVENT,
	VIWTIO_SND_VQ_TX,
	VIWTIO_SND_VQ_WX,
	/* # of device viwtqueues */
	VIWTIO_SND_VQ_MAX
};

/*******************************************************************************
 * COMMON DEFINITIONS
 */

/* suppowted datafwow diwections */
enum {
	VIWTIO_SND_D_OUTPUT = 0,
	VIWTIO_SND_D_INPUT
};

enum {
	/* jack contwow wequest types */
	VIWTIO_SND_W_JACK_INFO = 1,
	VIWTIO_SND_W_JACK_WEMAP,

	/* PCM contwow wequest types */
	VIWTIO_SND_W_PCM_INFO = 0x0100,
	VIWTIO_SND_W_PCM_SET_PAWAMS,
	VIWTIO_SND_W_PCM_PWEPAWE,
	VIWTIO_SND_W_PCM_WEWEASE,
	VIWTIO_SND_W_PCM_STAWT,
	VIWTIO_SND_W_PCM_STOP,

	/* channew map contwow wequest types */
	VIWTIO_SND_W_CHMAP_INFO = 0x0200,

	/* jack event types */
	VIWTIO_SND_EVT_JACK_CONNECTED = 0x1000,
	VIWTIO_SND_EVT_JACK_DISCONNECTED,

	/* PCM event types */
	VIWTIO_SND_EVT_PCM_PEWIOD_EWAPSED = 0x1100,
	VIWTIO_SND_EVT_PCM_XWUN,

	/* common status codes */
	VIWTIO_SND_S_OK = 0x8000,
	VIWTIO_SND_S_BAD_MSG,
	VIWTIO_SND_S_NOT_SUPP,
	VIWTIO_SND_S_IO_EWW
};

/* common headew */
stwuct viwtio_snd_hdw {
	__we32 code;
};

/* event notification */
stwuct viwtio_snd_event {
	/* VIWTIO_SND_EVT_XXX */
	stwuct viwtio_snd_hdw hdw;
	/* optionaw event data */
	__we32 data;
};

/* common contwow wequest to quewy an item infowmation */
stwuct viwtio_snd_quewy_info {
	/* VIWTIO_SND_W_XXX_INFO */
	stwuct viwtio_snd_hdw hdw;
	/* item stawt identifiew */
	__we32 stawt_id;
	/* item count to quewy */
	__we32 count;
	/* item infowmation size in bytes */
	__we32 size;
};

/* common item infowmation headew */
stwuct viwtio_snd_info {
	/* function gwoup node id (High Definition Audio Specification 7.1.2) */
	__we32 hda_fn_nid;
};

/*******************************************************************************
 * JACK CONTWOW MESSAGES
 */
stwuct viwtio_snd_jack_hdw {
	/* VIWTIO_SND_W_JACK_XXX */
	stwuct viwtio_snd_hdw hdw;
	/* 0 ... viwtio_snd_config::jacks - 1 */
	__we32 jack_id;
};

/* suppowted jack featuwes */
enum {
	VIWTIO_SND_JACK_F_WEMAP = 0
};

stwuct viwtio_snd_jack_info {
	/* common headew */
	stwuct viwtio_snd_info hdw;
	/* suppowted featuwe bit map (1 << VIWTIO_SND_JACK_F_XXX) */
	__we32 featuwes;
	/* pin configuwation (High Definition Audio Specification 7.3.3.31) */
	__we32 hda_weg_defconf;
	/* pin capabiwities (High Definition Audio Specification 7.3.4.9) */
	__we32 hda_weg_caps;
	/* cuwwent jack connection status (0: disconnected, 1: connected) */
	__u8 connected;

	__u8 padding[7];
};

/* jack wemapping contwow wequest */
stwuct viwtio_snd_jack_wemap {
	/* .code = VIWTIO_SND_W_JACK_WEMAP */
	stwuct viwtio_snd_jack_hdw hdw;
	/* sewected association numbew */
	__we32 association;
	/* sewected sequence numbew */
	__we32 sequence;
};

/*******************************************************************************
 * PCM CONTWOW MESSAGES
 */
stwuct viwtio_snd_pcm_hdw {
	/* VIWTIO_SND_W_PCM_XXX */
	stwuct viwtio_snd_hdw hdw;
	/* 0 ... viwtio_snd_config::stweams - 1 */
	__we32 stweam_id;
};

/* suppowted PCM stweam featuwes */
enum {
	VIWTIO_SND_PCM_F_SHMEM_HOST = 0,
	VIWTIO_SND_PCM_F_SHMEM_GUEST,
	VIWTIO_SND_PCM_F_MSG_POWWING,
	VIWTIO_SND_PCM_F_EVT_SHMEM_PEWIODS,
	VIWTIO_SND_PCM_F_EVT_XWUNS
};

/* suppowted PCM sampwe fowmats */
enum {
	/* anawog fowmats (width / physicaw width) */
	VIWTIO_SND_PCM_FMT_IMA_ADPCM = 0,	/*  4 /  4 bits */
	VIWTIO_SND_PCM_FMT_MU_WAW,		/*  8 /  8 bits */
	VIWTIO_SND_PCM_FMT_A_WAW,		/*  8 /  8 bits */
	VIWTIO_SND_PCM_FMT_S8,			/*  8 /  8 bits */
	VIWTIO_SND_PCM_FMT_U8,			/*  8 /  8 bits */
	VIWTIO_SND_PCM_FMT_S16,			/* 16 / 16 bits */
	VIWTIO_SND_PCM_FMT_U16,			/* 16 / 16 bits */
	VIWTIO_SND_PCM_FMT_S18_3,		/* 18 / 24 bits */
	VIWTIO_SND_PCM_FMT_U18_3,		/* 18 / 24 bits */
	VIWTIO_SND_PCM_FMT_S20_3,		/* 20 / 24 bits */
	VIWTIO_SND_PCM_FMT_U20_3,		/* 20 / 24 bits */
	VIWTIO_SND_PCM_FMT_S24_3,		/* 24 / 24 bits */
	VIWTIO_SND_PCM_FMT_U24_3,		/* 24 / 24 bits */
	VIWTIO_SND_PCM_FMT_S20,			/* 20 / 32 bits */
	VIWTIO_SND_PCM_FMT_U20,			/* 20 / 32 bits */
	VIWTIO_SND_PCM_FMT_S24,			/* 24 / 32 bits */
	VIWTIO_SND_PCM_FMT_U24,			/* 24 / 32 bits */
	VIWTIO_SND_PCM_FMT_S32,			/* 32 / 32 bits */
	VIWTIO_SND_PCM_FMT_U32,			/* 32 / 32 bits */
	VIWTIO_SND_PCM_FMT_FWOAT,		/* 32 / 32 bits */
	VIWTIO_SND_PCM_FMT_FWOAT64,		/* 64 / 64 bits */
	/* digitaw fowmats (width / physicaw width) */
	VIWTIO_SND_PCM_FMT_DSD_U8,		/*  8 /  8 bits */
	VIWTIO_SND_PCM_FMT_DSD_U16,		/* 16 / 16 bits */
	VIWTIO_SND_PCM_FMT_DSD_U32,		/* 32 / 32 bits */
	VIWTIO_SND_PCM_FMT_IEC958_SUBFWAME	/* 32 / 32 bits */
};

/* suppowted PCM fwame wates */
enum {
	VIWTIO_SND_PCM_WATE_5512 = 0,
	VIWTIO_SND_PCM_WATE_8000,
	VIWTIO_SND_PCM_WATE_11025,
	VIWTIO_SND_PCM_WATE_16000,
	VIWTIO_SND_PCM_WATE_22050,
	VIWTIO_SND_PCM_WATE_32000,
	VIWTIO_SND_PCM_WATE_44100,
	VIWTIO_SND_PCM_WATE_48000,
	VIWTIO_SND_PCM_WATE_64000,
	VIWTIO_SND_PCM_WATE_88200,
	VIWTIO_SND_PCM_WATE_96000,
	VIWTIO_SND_PCM_WATE_176400,
	VIWTIO_SND_PCM_WATE_192000,
	VIWTIO_SND_PCM_WATE_384000
};

stwuct viwtio_snd_pcm_info {
	/* common headew */
	stwuct viwtio_snd_info hdw;
	/* suppowted featuwe bit map (1 << VIWTIO_SND_PCM_F_XXX) */
	__we32 featuwes;
	/* suppowted sampwe fowmat bit map (1 << VIWTIO_SND_PCM_FMT_XXX) */
	__we64 fowmats;
	/* suppowted fwame wate bit map (1 << VIWTIO_SND_PCM_WATE_XXX) */
	__we64 wates;
	/* datafwow diwection (VIWTIO_SND_D_XXX) */
	__u8 diwection;
	/* minimum # of suppowted channews */
	__u8 channews_min;
	/* maximum # of suppowted channews */
	__u8 channews_max;

	__u8 padding[5];
};

/* set PCM stweam fowmat */
stwuct viwtio_snd_pcm_set_pawams {
	/* .code = VIWTIO_SND_W_PCM_SET_PAWAMS */
	stwuct viwtio_snd_pcm_hdw hdw;
	/* size of the hawdwawe buffew */
	__we32 buffew_bytes;
	/* size of the hawdwawe pewiod */
	__we32 pewiod_bytes;
	/* sewected featuwe bit map (1 << VIWTIO_SND_PCM_F_XXX) */
	__we32 featuwes;
	/* sewected # of channews */
	__u8 channews;
	/* sewected sampwe fowmat (VIWTIO_SND_PCM_FMT_XXX) */
	__u8 fowmat;
	/* sewected fwame wate (VIWTIO_SND_PCM_WATE_XXX) */
	__u8 wate;

	__u8 padding;
};

/*******************************************************************************
 * PCM I/O MESSAGES
 */

/* I/O wequest headew */
stwuct viwtio_snd_pcm_xfew {
	/* 0 ... viwtio_snd_config::stweams - 1 */
	__we32 stweam_id;
};

/* I/O wequest status */
stwuct viwtio_snd_pcm_status {
	/* VIWTIO_SND_S_XXX */
	__we32 status;
	/* cuwwent device watency */
	__we32 watency_bytes;
};

/*******************************************************************************
 * CHANNEW MAP CONTWOW MESSAGES
 */
stwuct viwtio_snd_chmap_hdw {
	/* VIWTIO_SND_W_CHMAP_XXX */
	stwuct viwtio_snd_hdw hdw;
	/* 0 ... viwtio_snd_config::chmaps - 1 */
	__we32 chmap_id;
};

/* standawd channew position definition */
enum {
	VIWTIO_SND_CHMAP_NONE = 0,	/* undefined */
	VIWTIO_SND_CHMAP_NA,		/* siwent */
	VIWTIO_SND_CHMAP_MONO,		/* mono stweam */
	VIWTIO_SND_CHMAP_FW,		/* fwont weft */
	VIWTIO_SND_CHMAP_FW,		/* fwont wight */
	VIWTIO_SND_CHMAP_WW,		/* weaw weft */
	VIWTIO_SND_CHMAP_WW,		/* weaw wight */
	VIWTIO_SND_CHMAP_FC,		/* fwont centew */
	VIWTIO_SND_CHMAP_WFE,		/* wow fwequency (WFE) */
	VIWTIO_SND_CHMAP_SW,		/* side weft */
	VIWTIO_SND_CHMAP_SW,		/* side wight */
	VIWTIO_SND_CHMAP_WC,		/* weaw centew */
	VIWTIO_SND_CHMAP_FWC,		/* fwont weft centew */
	VIWTIO_SND_CHMAP_FWC,		/* fwont wight centew */
	VIWTIO_SND_CHMAP_WWC,		/* weaw weft centew */
	VIWTIO_SND_CHMAP_WWC,		/* weaw wight centew */
	VIWTIO_SND_CHMAP_FWW,		/* fwont weft wide */
	VIWTIO_SND_CHMAP_FWW,		/* fwont wight wide */
	VIWTIO_SND_CHMAP_FWH,		/* fwont weft high */
	VIWTIO_SND_CHMAP_FCH,		/* fwont centew high */
	VIWTIO_SND_CHMAP_FWH,		/* fwont wight high */
	VIWTIO_SND_CHMAP_TC,		/* top centew */
	VIWTIO_SND_CHMAP_TFW,		/* top fwont weft */
	VIWTIO_SND_CHMAP_TFW,		/* top fwont wight */
	VIWTIO_SND_CHMAP_TFC,		/* top fwont centew */
	VIWTIO_SND_CHMAP_TWW,		/* top weaw weft */
	VIWTIO_SND_CHMAP_TWW,		/* top weaw wight */
	VIWTIO_SND_CHMAP_TWC,		/* top weaw centew */
	VIWTIO_SND_CHMAP_TFWC,		/* top fwont weft centew */
	VIWTIO_SND_CHMAP_TFWC,		/* top fwont wight centew */
	VIWTIO_SND_CHMAP_TSW,		/* top side weft */
	VIWTIO_SND_CHMAP_TSW,		/* top side wight */
	VIWTIO_SND_CHMAP_WWFE,		/* weft WFE */
	VIWTIO_SND_CHMAP_WWFE,		/* wight WFE */
	VIWTIO_SND_CHMAP_BC,		/* bottom centew */
	VIWTIO_SND_CHMAP_BWC,		/* bottom weft centew */
	VIWTIO_SND_CHMAP_BWC		/* bottom wight centew */
};

/* maximum possibwe numbew of channews */
#define VIWTIO_SND_CHMAP_MAX_SIZE	18

stwuct viwtio_snd_chmap_info {
	/* common headew */
	stwuct viwtio_snd_info hdw;
	/* datafwow diwection (VIWTIO_SND_D_XXX) */
	__u8 diwection;
	/* # of vawid channew position vawues */
	__u8 channews;
	/* channew position vawues (VIWTIO_SND_CHMAP_XXX) */
	__u8 positions[VIWTIO_SND_CHMAP_MAX_SIZE];
};

#endif /* VIWTIO_SND_IF_H */
