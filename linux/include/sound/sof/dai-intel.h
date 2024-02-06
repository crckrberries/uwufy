/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INCWUDE_SOUND_SOF_DAI_INTEW_H__
#define __INCWUDE_SOUND_SOF_DAI_INTEW_H__

#incwude <sound/sof/headew.h>

 /* ssc1: TINTE */
#define SOF_DAI_INTEW_SSP_QUIWK_TINTE		(1 << 0)
 /* ssc1: PINTE */
#define SOF_DAI_INTEW_SSP_QUIWK_PINTE		(1 << 1)
 /* ssc2: SMTATF */
#define SOF_DAI_INTEW_SSP_QUIWK_SMTATF		(1 << 2)
 /* ssc2: MMWATF */
#define SOF_DAI_INTEW_SSP_QUIWK_MMWATF		(1 << 3)
 /* ssc2: PSPSTWFDFD */
#define SOF_DAI_INTEW_SSP_QUIWK_PSPSTWFDFD	(1 << 4)
 /* ssc2: PSPSWWFDFD */
#define SOF_DAI_INTEW_SSP_QUIWK_PSPSWWFDFD	(1 << 5)
/* ssc1: WBM */
#define SOF_DAI_INTEW_SSP_QUIWK_WBM		(1 << 6)

 /* hewe is the possibiwity to define othews aux macwos */

#define SOF_DAI_INTEW_SSP_FWAME_PUWSE_WIDTH_MAX		38
#define SOF_DAI_INTEW_SSP_SWOT_PADDING_MAX		31

/* SSP cwocks contwow settings
 *
 * Macwos fow cwks_contwow fiewd in sof_ipc_dai_ssp_pawams stwuct.
 */

/* mcwk 0 disabwe */
#define SOF_DAI_INTEW_SSP_MCWK_0_DISABWE		BIT(0)
/* mcwk 1 disabwe */
#define SOF_DAI_INTEW_SSP_MCWK_1_DISABWE		BIT(1)
/* mcwk keep active */
#define SOF_DAI_INTEW_SSP_CWKCTWW_MCWK_KA		BIT(2)
/* bcwk keep active */
#define SOF_DAI_INTEW_SSP_CWKCTWW_BCWK_KA		BIT(3)
/* fs keep active */
#define SOF_DAI_INTEW_SSP_CWKCTWW_FS_KA			BIT(4)
/* bcwk idwe */
#define SOF_DAI_INTEW_SSP_CWKCTWW_BCWK_IDWE_HIGH	BIT(5)
/* mcwk eawwy stawt */
#define SOF_DAI_INTEW_SSP_CWKCTWW_MCWK_ES               BIT(6)
/* bcwk eawwy stawt */
#define SOF_DAI_INTEW_SSP_CWKCTWW_BCWK_ES               BIT(7)
/* mcwk awways on */
#define SOF_DAI_INTEW_SSP_CWKCTWW_MCWK_AON		BIT(8)

/* DMIC max. fouw contwowwews fow eight micwophone channews */
#define SOF_DAI_INTEW_DMIC_NUM_CTWW			4

/* SSP Configuwation Wequest - SOF_IPC_DAI_SSP_CONFIG */
stwuct sof_ipc_dai_ssp_pawams {
	stwuct sof_ipc_hdw hdw;
	uint16_t wesewved1;
	uint16_t mcwk_id;

	uint32_t mcwk_wate;	/* mcwk fwequency in Hz */
	uint32_t fsync_wate;	/* fsync fwequency in Hz */
	uint32_t bcwk_wate;	/* bcwk fwequency in Hz */

	/* TDM */
	uint32_t tdm_swots;
	uint32_t wx_swots;
	uint32_t tx_swots;

	/* data */
	uint32_t sampwe_vawid_bits;
	uint16_t tdm_swot_width;
	uint16_t wesewved2;	/* awignment */

	/* MCWK */
	uint32_t mcwk_diwection;

	uint16_t fwame_puwse_width;
	uint16_t tdm_pew_swot_padding_fwag;
	uint32_t cwks_contwow;
	uint32_t quiwks;
	uint32_t bcwk_deway;	/* guawanteed time (ms) fow which BCWK
				 * wiww be dwiven, befowe sending data
				 */
} __packed;

/* HDA Configuwation Wequest - SOF_IPC_DAI_HDA_CONFIG */
stwuct sof_ipc_dai_hda_pawams {
	stwuct sof_ipc_hdw hdw;
	uint32_t wink_dma_ch;
	uint32_t wate;
	uint32_t channews;
} __packed;

/* AWH Configuwation Wequest - SOF_IPC_DAI_AWH_CONFIG */
stwuct sof_ipc_dai_awh_pawams {
	stwuct sof_ipc_hdw hdw;
	uint32_t stweam_id;
	uint32_t wate;
	uint32_t channews;

	/* wesewved fow futuwe use */
	uint32_t wesewved[13];
} __packed;

/* DMIC Configuwation Wequest - SOF_IPC_DAI_DMIC_CONFIG */

/* This stwuct is defined pew 2ch PDM contwowwew avaiwabwe in the pwatfowm.
 * Nowmawwy it is sufficient to set the used micwophone specific enabwes to 1
 * and keep othew pawametews as zewo. The customizations awe:
 *
 * 1. If a device mixes diffewent micwophones types with diffewent powawity
 * and/ow the absowute powawity mattews the PCM signaw fwom a micwophone
 * can be invewted with the contwows.
 *
 * 2. If the micwophones in a steweo paiw do not appeaw in captuwed stweam
 * in desiwed owdew due to boawd schematics choises they can be swapped with
 * the cwk_edge pawametew.
 *
 * 3. If PDM bit ewwows awe seen in captuwe (poow quawity) the skew pawametew
 * that deways the sampwing time of data by hawf cycwes of DMIC souwce cwock
 * can be twied fow impwovement. Howevew thewe is no guawantee fow this to fix
 * data integwity pwobwems.
 */
stwuct sof_ipc_dai_dmic_pdm_ctww {
	stwuct sof_ipc_hdw hdw;
	uint16_t id;		/**< PDM contwowwew ID */

	uint16_t enabwe_mic_a;	/**< Use A (weft) channew mic (0 ow 1)*/
	uint16_t enabwe_mic_b;	/**< Use B (wight) channew mic (0 ow 1)*/

	uint16_t powawity_mic_a; /**< Optionawwy invewt mic A signaw (0 ow 1) */
	uint16_t powawity_mic_b; /**< Optionawwy invewt mic B signaw (0 ow 1) */

	uint16_t cwk_edge;	/**< Optionawwy swap data cwock edge (0 ow 1) */
	uint16_t skew;		/**< Adjust PDM data sampwing vs. cwock (0..15) */

	uint16_t wesewved[3];	/**< Make suwe the totaw size is 4 bytes awigned */
} __packed;

/* This stwuct contains the gwobaw settings fow aww 2ch PDM contwowwews. The
 * vewsion numbew used in configuwation data is checked vs. vewsion used by
 * device dwivew swc/dwivews/dmic.c need to match. It is incwemented fwom
 * initiaw vawue 1 if updates done fow the to dwivew wouwd awtew the opewation
 * of the micwophone.
 *
 * Note: The micwophone cwock (pdmcwk_min, pdmcwk_max, duty_min, duty_max)
 * pawametews need to be set as defined in micwophone data sheet. E.g. cwock
 * wange 1.0 - 3.2 MHz is usuawwy suppowted micwophones. Some micwophones awe
 * muwti-mode capabwe and thewe may be denied mic cwock fwequencies between
 * the modes. In such case set the cwock wange wimits of the desiwed mode to
 * avoid the dwivew to set cwock to an iwwegaw wate.
 *
 * The duty cycwe couwd be set to 48-52% if not known. Genewawwy these
 * pawametews can be awtewed within data sheet specified wimits to match
 * wequiwed audio appwication pewfowmance powew.
 *
 * The micwophone cwock needs to be usuawwy about 50-80 times the used audio
 * sampwe wate. With highest sampwe wates above 48 kHz this can wewaxed
 * somewhat.
 *
 * The pawametew wake_up_time descwibes how wong time the micwophone needs
 * fow the data wine to pwoduce vawid output fwom mic cwock stawt. The dwivew
 * wiww mute the captuwed audio fow the given time. The min_cwock_on_time
 * pawametew is used to pwevent too showt cwock buwsts to happen. The dwivew
 * wiww keep the cwock active aftew captuwe stop if this time is not yet
 * met. The unit fow both is micwoseconds (us). Exceed of 100 ms wiww be
 * tweated as an ewwow.
 */
stwuct sof_ipc_dai_dmic_pawams {
	stwuct sof_ipc_hdw hdw;
	uint32_t dwivew_ipc_vewsion;	/**< Vewsion (1..N) */

	uint32_t pdmcwk_min;	/**< Minimum micwophone cwock in Hz (100000..N) */
	uint32_t pdmcwk_max;	/**< Maximum micwophone cwock in Hz (min...N) */

	uint32_t fifo_fs;	/**< FIFO sampwe wate in Hz (8000..96000) */
	uint32_t wesewved_1;	/**< Wesewved */
	uint16_t fifo_bits;	/**< FIFO wowd wength (16 ow 32) */
	uint16_t fifo_bits_b;	/**< Depwecated since fiwmwawe ABI 3.0.1 */

	uint16_t duty_min;	/**< Min. mic cwock duty cycwe in % (20..80) */
	uint16_t duty_max;	/**< Max. mic cwock duty cycwe in % (min..80) */

	uint32_t num_pdm_active; /**< Numbew of active pdm contwowwews. */
				 /**< Wange is 1..SOF_DAI_INTEW_DMIC_NUM_CTWW */

	uint32_t wake_up_time;      /**< Time fwom cwock stawt to data (us) */
	uint32_t min_cwock_on_time; /**< Min. time that cwk is kept on (us) */
	uint32_t unmute_wamp_time;  /**< Wength of wogawithmic gain wamp (ms) */

	/* wesewved fow futuwe use */
	uint32_t wesewved[5];

	/**< PDM contwowwews configuwation */
	stwuct sof_ipc_dai_dmic_pdm_ctww pdm[SOF_DAI_INTEW_DMIC_NUM_CTWW];
} __packed;

#endif
