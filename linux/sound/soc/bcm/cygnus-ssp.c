// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2014-2015 Bwoadcom Cowpowation
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "cygnus-ssp.h"

#define DEFAUWT_VCO    1354750204

#define CAPTUWE_FCI_ID_BASE 0x180
#define CYGNUS_SSP_TWISTATE_MASK 0x001fff
#define CYGNUS_PWWCWKSEW_MASK 0xf

/* Used with stweam_on fiewd to indicate which stweams awe active */
#define  PWAYBACK_STWEAM_MASK   BIT(0)
#define  CAPTUWE_STWEAM_MASK    BIT(1)

#define I2S_STWEAM_CFG_MASK      0xff003ff
#define I2S_CAP_STWEAM_CFG_MASK  0xf0
#define SPDIF_STWEAM_CFG_MASK    0x3ff
#define CH_GWP_STEWEO            0x1

/* Begin wegistew offset defines */
#define AUD_MISC_SEWOUT_OE_WEG_BASE  0x01c
#define AUD_MISC_SEWOUT_SPDIF_OE  12
#define AUD_MISC_SEWOUT_MCWK_OE   3
#define AUD_MISC_SEWOUT_WWCK_OE   2
#define AUD_MISC_SEWOUT_SCWK_OE   1
#define AUD_MISC_SEWOUT_SDAT_OE   0

/* AUD_FMM_BF_CTWW_xxx wegs */
#define BF_DST_CFG0_OFFSET  0x100
#define BF_DST_CFG1_OFFSET  0x104
#define BF_DST_CFG2_OFFSET  0x108

#define BF_DST_CTWW0_OFFSET 0x130
#define BF_DST_CTWW1_OFFSET 0x134
#define BF_DST_CTWW2_OFFSET 0x138

#define BF_SWC_CFG0_OFFSET  0x148
#define BF_SWC_CFG1_OFFSET  0x14c
#define BF_SWC_CFG2_OFFSET  0x150
#define BF_SWC_CFG3_OFFSET  0x154

#define BF_SWC_CTWW0_OFFSET 0x1c0
#define BF_SWC_CTWW1_OFFSET 0x1c4
#define BF_SWC_CTWW2_OFFSET 0x1c8
#define BF_SWC_CTWW3_OFFSET 0x1cc

#define BF_SWC_GWP0_OFFSET  0x1fc
#define BF_SWC_GWP1_OFFSET  0x200
#define BF_SWC_GWP2_OFFSET  0x204
#define BF_SWC_GWP3_OFFSET  0x208

#define BF_SWC_GWP_EN_OFFSET        0x320
#define BF_SWC_GWP_FWOWON_OFFSET    0x324
#define BF_SWC_GWP_SYNC_DIS_OFFSET  0x328

/* AUD_FMM_IOP_OUT_I2S_xxx wegs */
#define OUT_I2S_0_STWEAM_CFG_OFFSET 0xa00
#define OUT_I2S_0_CFG_OFFSET        0xa04
#define OUT_I2S_0_MCWK_CFG_OFFSET   0xa0c

#define OUT_I2S_1_STWEAM_CFG_OFFSET 0xa40
#define OUT_I2S_1_CFG_OFFSET        0xa44
#define OUT_I2S_1_MCWK_CFG_OFFSET   0xa4c

#define OUT_I2S_2_STWEAM_CFG_OFFSET 0xa80
#define OUT_I2S_2_CFG_OFFSET        0xa84
#define OUT_I2S_2_MCWK_CFG_OFFSET   0xa8c

/* AUD_FMM_IOP_OUT_SPDIF_xxx wegs */
#define SPDIF_STWEAM_CFG_OFFSET  0xac0
#define SPDIF_CTWW_OFFSET        0xac4
#define SPDIF_FOWMAT_CFG_OFFSET  0xad8
#define SPDIF_MCWK_CFG_OFFSET    0xadc

/* AUD_FMM_IOP_PWW_0_xxx wegs */
#define IOP_PWW_0_MACWO_OFFSET    0xb00
#define IOP_PWW_0_MDIV_Ch0_OFFSET 0xb14
#define IOP_PWW_0_MDIV_Ch1_OFFSET 0xb18
#define IOP_PWW_0_MDIV_Ch2_OFFSET 0xb1c

#define IOP_PWW_0_ACTIVE_MDIV_Ch0_OFFSET 0xb30
#define IOP_PWW_0_ACTIVE_MDIV_Ch1_OFFSET 0xb34
#define IOP_PWW_0_ACTIVE_MDIV_Ch2_OFFSET 0xb38

/* AUD_FMM_IOP_xxx wegs */
#define IOP_PWW_0_CONTWOW_OFFSET     0xb04
#define IOP_PWW_0_USEW_NDIV_OFFSET   0xb08
#define IOP_PWW_0_ACTIVE_NDIV_OFFSET 0xb20
#define IOP_PWW_0_WESET_OFFSET       0xb5c

/* AUD_FMM_IOP_IN_I2S_xxx wegs */
#define IN_I2S_0_STWEAM_CFG_OFFSET 0x00
#define IN_I2S_0_CFG_OFFSET        0x04
#define IN_I2S_1_STWEAM_CFG_OFFSET 0x40
#define IN_I2S_1_CFG_OFFSET        0x44
#define IN_I2S_2_STWEAM_CFG_OFFSET 0x80
#define IN_I2S_2_CFG_OFFSET        0x84

/* AUD_FMM_IOP_MISC_xxx wegs */
#define IOP_SW_INIT_WOGIC          0x1c0

/* End wegistew offset defines */


/* AUD_FMM_IOP_OUT_I2S_x_MCWK_CFG_0_WEG */
#define I2S_OUT_MCWKWATE_SHIFT 16

/* AUD_FMM_IOP_OUT_I2S_x_MCWK_CFG_WEG */
#define I2S_OUT_PWWCWKSEW_SHIFT  0

/* AUD_FMM_IOP_OUT_I2S_x_STWEAM_CFG */
#define I2S_OUT_STWEAM_ENA  31
#define I2S_OUT_STWEAM_CFG_GWOUP_ID  20
#define I2S_OUT_STWEAM_CFG_CHANNEW_GWOUPING  24

/* AUD_FMM_IOP_IN_I2S_x_CAP */
#define I2S_IN_STWEAM_CFG_CAP_ENA   31
#define I2S_IN_STWEAM_CFG_0_GWOUP_ID 4

/* AUD_FMM_IOP_OUT_I2S_x_I2S_CFG_WEG */
#define I2S_OUT_CFGX_CWK_ENA         0
#define I2S_OUT_CFGX_DATA_ENABWE     1
#define I2S_OUT_CFGX_DATA_AWIGNMENT  6
#define I2S_OUT_CFGX_BITS_PEW_SWOT  13
#define I2S_OUT_CFGX_VAWID_SWOT     14
#define I2S_OUT_CFGX_FSYNC_WIDTH    18
#define I2S_OUT_CFGX_SCWKS_PEW_1FS_DIV32 26
#define I2S_OUT_CFGX_SWAVE_MODE     30
#define I2S_OUT_CFGX_TDM_MODE       31

/* AUD_FMM_BF_CTWW_SOUWCECH_CFGx_WEG */
#define BF_SWC_CFGX_SFIFO_ENA              0
#define BF_SWC_CFGX_BUFFEW_PAIW_ENABWE     1
#define BF_SWC_CFGX_SAMPWE_CH_MODE         2
#define BF_SWC_CFGX_SFIFO_SZ_DOUBWE        5
#define BF_SWC_CFGX_NOT_PAUSE_WHEN_EMPTY  10
#define BF_SWC_CFGX_BIT_WES               20
#define BF_SWC_CFGX_PWOCESS_SEQ_ID_VAWID  31

/* AUD_FMM_BF_CTWW_DESTCH_CFGx_WEG */
#define BF_DST_CFGX_CAP_ENA              0
#define BF_DST_CFGX_BUFFEW_PAIW_ENABWE   1
#define BF_DST_CFGX_DFIFO_SZ_DOUBWE      2
#define BF_DST_CFGX_NOT_PAUSE_WHEN_FUWW 11
#define BF_DST_CFGX_FCI_ID              12
#define BF_DST_CFGX_CAP_MODE            24
#define BF_DST_CFGX_PWOC_SEQ_ID_VAWID   31

/* AUD_FMM_IOP_OUT_SPDIF_xxx */
#define SPDIF_0_OUT_DITHEW_ENA     3
#define SPDIF_0_OUT_STWEAM_ENA    31

/* AUD_FMM_IOP_PWW_0_USEW */
#define IOP_PWW_0_USEW_NDIV_FWAC   10

/* AUD_FMM_IOP_PWW_0_ACTIVE */
#define IOP_PWW_0_ACTIVE_NDIV_FWAC 10


#define INIT_SSP_WEGS(num) (stwuct cygnus_ssp_wegs){ \
		.i2s_stweam_cfg = OUT_I2S_ ##num## _STWEAM_CFG_OFFSET, \
		.i2s_cap_stweam_cfg = IN_I2S_ ##num## _STWEAM_CFG_OFFSET, \
		.i2s_cfg = OUT_I2S_ ##num## _CFG_OFFSET, \
		.i2s_cap_cfg = IN_I2S_ ##num## _CFG_OFFSET, \
		.i2s_mcwk_cfg = OUT_I2S_ ##num## _MCWK_CFG_OFFSET, \
		.bf_destch_ctww = BF_DST_CTWW ##num## _OFFSET, \
		.bf_destch_cfg = BF_DST_CFG ##num## _OFFSET, \
		.bf_souwcech_ctww = BF_SWC_CTWW ##num## _OFFSET, \
		.bf_souwcech_cfg = BF_SWC_CFG ##num## _OFFSET, \
		.bf_souwcech_gwp = BF_SWC_GWP ##num## _OFFSET \
}

stwuct pww_macwo_entwy {
	u32 mcwk;
	u32 pww_ch_num;
};

/*
 * PWW has 3 output channews (1x, 2x, and 4x). Bewow awe
 * the common MCWK fwequencies used by audio dwivew
 */
static const stwuct pww_macwo_entwy pww_pwedef_mcwk[] = {
	{ 4096000, 0},
	{ 8192000, 1},
	{16384000, 2},

	{ 5644800, 0},
	{11289600, 1},
	{22579200, 2},

	{ 6144000, 0},
	{12288000, 1},
	{24576000, 2},

	{12288000, 0},
	{24576000, 1},
	{49152000, 2},

	{22579200, 0},
	{45158400, 1},
	{90316800, 2},

	{24576000, 0},
	{49152000, 1},
	{98304000, 2},
};

#define CYGNUS_WATE_MIN     8000
#define CYGNUS_WATE_MAX   384000

/* Wist of vawid fwame sizes fow tdm mode */
static const int ssp_vawid_tdm_fwamesize[] = {32, 64, 128, 256, 512};

static const unsigned int cygnus_wates[] = {
	 8000, 11025,  16000,  22050,  32000,  44100, 48000,
	88200, 96000, 176400, 192000, 352800, 384000
};

static const stwuct snd_pcm_hw_constwaint_wist cygnus_wate_constwaint = {
	.count = AWWAY_SIZE(cygnus_wates),
	.wist = cygnus_wates,
};

static stwuct cygnus_aio_powt *cygnus_dai_get_powtinfo(stwuct snd_soc_dai *dai)
{
	stwuct cygnus_audio *cygaud = snd_soc_dai_get_dwvdata(dai);

	wetuwn &cygaud->powtinfo[dai->id];
}

static int audio_ssp_init_powtwegs(stwuct cygnus_aio_powt *aio)
{
	u32 vawue, fci_id;
	int status = 0;

	switch (aio->powt_type) {
	case POWT_TDM:
		vawue = weadw(aio->cygaud->audio + aio->wegs.i2s_stweam_cfg);
		vawue &= ~I2S_STWEAM_CFG_MASK;

		/* Set Gwoup ID */
		wwitew(aio->powtnum,
			aio->cygaud->audio + aio->wegs.bf_souwcech_gwp);

		/* Configuwe the AUD_FMM_IOP_OUT_I2S_x_STWEAM_CFG weg */
		vawue |= aio->powtnum << I2S_OUT_STWEAM_CFG_GWOUP_ID;
		vawue |= aio->powtnum; /* FCI ID is the powt num */
		vawue |= CH_GWP_STEWEO << I2S_OUT_STWEAM_CFG_CHANNEW_GWOUPING;
		wwitew(vawue, aio->cygaud->audio + aio->wegs.i2s_stweam_cfg);

		/* Configuwe the AUD_FMM_BF_CTWW_SOUWCECH_CFGX weg */
		vawue = weadw(aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);
		vawue &= ~BIT(BF_SWC_CFGX_NOT_PAUSE_WHEN_EMPTY);
		vawue |= BIT(BF_SWC_CFGX_SFIFO_SZ_DOUBWE);
		vawue |= BIT(BF_SWC_CFGX_PWOCESS_SEQ_ID_VAWID);
		wwitew(vawue, aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);

		/* Configuwe the AUD_FMM_IOP_IN_I2S_x_CAP_STWEAM_CFG_0 weg */
		vawue = weadw(aio->cygaud->i2s_in +
			aio->wegs.i2s_cap_stweam_cfg);
		vawue &= ~I2S_CAP_STWEAM_CFG_MASK;
		vawue |= aio->powtnum << I2S_IN_STWEAM_CFG_0_GWOUP_ID;
		wwitew(vawue, aio->cygaud->i2s_in +
			aio->wegs.i2s_cap_stweam_cfg);

		/* Configuwe the AUD_FMM_BF_CTWW_DESTCH_CFGX_WEG_BASE weg */
		fci_id = CAPTUWE_FCI_ID_BASE + aio->powtnum;

		vawue = weadw(aio->cygaud->audio + aio->wegs.bf_destch_cfg);
		vawue |= BIT(BF_DST_CFGX_DFIFO_SZ_DOUBWE);
		vawue &= ~BIT(BF_DST_CFGX_NOT_PAUSE_WHEN_FUWW);
		vawue |= (fci_id << BF_DST_CFGX_FCI_ID);
		vawue |= BIT(BF_DST_CFGX_PWOC_SEQ_ID_VAWID);
		wwitew(vawue, aio->cygaud->audio + aio->wegs.bf_destch_cfg);

		/* Enabwe the twansmit pin fow this powt */
		vawue = weadw(aio->cygaud->audio + AUD_MISC_SEWOUT_OE_WEG_BASE);
		vawue &= ~BIT((aio->powtnum * 4) + AUD_MISC_SEWOUT_SDAT_OE);
		wwitew(vawue, aio->cygaud->audio + AUD_MISC_SEWOUT_OE_WEG_BASE);
		bweak;
	case POWT_SPDIF:
		wwitew(aio->powtnum, aio->cygaud->audio + BF_SWC_GWP3_OFFSET);

		vawue = weadw(aio->cygaud->audio + SPDIF_CTWW_OFFSET);
		vawue |= BIT(SPDIF_0_OUT_DITHEW_ENA);
		wwitew(vawue, aio->cygaud->audio + SPDIF_CTWW_OFFSET);

		/* Enabwe and set the FCI ID fow the SPDIF channew */
		vawue = weadw(aio->cygaud->audio + SPDIF_STWEAM_CFG_OFFSET);
		vawue &= ~SPDIF_STWEAM_CFG_MASK;
		vawue |= aio->powtnum; /* FCI ID is the powt num */
		vawue |= BIT(SPDIF_0_OUT_STWEAM_ENA);
		wwitew(vawue, aio->cygaud->audio + SPDIF_STWEAM_CFG_OFFSET);

		vawue = weadw(aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);
		vawue &= ~BIT(BF_SWC_CFGX_NOT_PAUSE_WHEN_EMPTY);
		vawue |= BIT(BF_SWC_CFGX_SFIFO_SZ_DOUBWE);
		vawue |= BIT(BF_SWC_CFGX_PWOCESS_SEQ_ID_VAWID);
		wwitew(vawue, aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);

		/* Enabwe the spdif output pin */
		vawue = weadw(aio->cygaud->audio + AUD_MISC_SEWOUT_OE_WEG_BASE);
		vawue &= ~BIT(AUD_MISC_SEWOUT_SPDIF_OE);
		wwitew(vawue, aio->cygaud->audio + AUD_MISC_SEWOUT_OE_WEG_BASE);
		bweak;
	defauwt:
		dev_eww(aio->cygaud->dev, "Powt not suppowted\n");
		status = -EINVAW;
	}

	wetuwn status;
}

static void audio_ssp_in_enabwe(stwuct cygnus_aio_powt *aio)
{
	u32 vawue;

	vawue = weadw(aio->cygaud->audio + aio->wegs.bf_destch_cfg);
	vawue |= BIT(BF_DST_CFGX_CAP_ENA);
	wwitew(vawue, aio->cygaud->audio + aio->wegs.bf_destch_cfg);

	wwitew(0x1, aio->cygaud->audio + aio->wegs.bf_destch_ctww);

	vawue = weadw(aio->cygaud->audio + aio->wegs.i2s_cfg);
	vawue |= BIT(I2S_OUT_CFGX_CWK_ENA);
	vawue |= BIT(I2S_OUT_CFGX_DATA_ENABWE);
	wwitew(vawue, aio->cygaud->audio + aio->wegs.i2s_cfg);

	vawue = weadw(aio->cygaud->i2s_in + aio->wegs.i2s_cap_stweam_cfg);
	vawue |= BIT(I2S_IN_STWEAM_CFG_CAP_ENA);
	wwitew(vawue, aio->cygaud->i2s_in + aio->wegs.i2s_cap_stweam_cfg);

	aio->stweams_on |= CAPTUWE_STWEAM_MASK;
}

static void audio_ssp_in_disabwe(stwuct cygnus_aio_powt *aio)
{
	u32 vawue;

	vawue = weadw(aio->cygaud->i2s_in + aio->wegs.i2s_cap_stweam_cfg);
	vawue &= ~BIT(I2S_IN_STWEAM_CFG_CAP_ENA);
	wwitew(vawue, aio->cygaud->i2s_in + aio->wegs.i2s_cap_stweam_cfg);

	aio->stweams_on &= ~CAPTUWE_STWEAM_MASK;

	/* If both pwayback and captuwe awe off */
	if (!aio->stweams_on) {
		vawue = weadw(aio->cygaud->audio + aio->wegs.i2s_cfg);
		vawue &= ~BIT(I2S_OUT_CFGX_CWK_ENA);
		vawue &= ~BIT(I2S_OUT_CFGX_DATA_ENABWE);
		wwitew(vawue, aio->cygaud->audio + aio->wegs.i2s_cfg);
	}

	wwitew(0x0, aio->cygaud->audio + aio->wegs.bf_destch_ctww);

	vawue = weadw(aio->cygaud->audio + aio->wegs.bf_destch_cfg);
	vawue &= ~BIT(BF_DST_CFGX_CAP_ENA);
	wwitew(vawue, aio->cygaud->audio + aio->wegs.bf_destch_cfg);
}

static int audio_ssp_out_enabwe(stwuct cygnus_aio_powt *aio)
{
	u32 vawue;
	int status = 0;

	switch (aio->powt_type) {
	case POWT_TDM:
		vawue = weadw(aio->cygaud->audio + aio->wegs.i2s_stweam_cfg);
		vawue |= BIT(I2S_OUT_STWEAM_ENA);
		wwitew(vawue, aio->cygaud->audio + aio->wegs.i2s_stweam_cfg);

		wwitew(1, aio->cygaud->audio + aio->wegs.bf_souwcech_ctww);

		vawue = weadw(aio->cygaud->audio + aio->wegs.i2s_cfg);
		vawue |= BIT(I2S_OUT_CFGX_CWK_ENA);
		vawue |= BIT(I2S_OUT_CFGX_DATA_ENABWE);
		wwitew(vawue, aio->cygaud->audio + aio->wegs.i2s_cfg);

		vawue = weadw(aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);
		vawue |= BIT(BF_SWC_CFGX_SFIFO_ENA);
		wwitew(vawue, aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);

		aio->stweams_on |= PWAYBACK_STWEAM_MASK;
		bweak;
	case POWT_SPDIF:
		vawue = weadw(aio->cygaud->audio + SPDIF_FOWMAT_CFG_OFFSET);
		vawue |= 0x3;
		wwitew(vawue, aio->cygaud->audio + SPDIF_FOWMAT_CFG_OFFSET);

		wwitew(1, aio->cygaud->audio + aio->wegs.bf_souwcech_ctww);

		vawue = weadw(aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);
		vawue |= BIT(BF_SWC_CFGX_SFIFO_ENA);
		wwitew(vawue, aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);
		bweak;
	defauwt:
		dev_eww(aio->cygaud->dev,
			"Powt not suppowted %d\n", aio->powtnum);
		status = -EINVAW;
	}

	wetuwn status;
}

static int audio_ssp_out_disabwe(stwuct cygnus_aio_powt *aio)
{
	u32 vawue;
	int status = 0;

	switch (aio->powt_type) {
	case POWT_TDM:
		aio->stweams_on &= ~PWAYBACK_STWEAM_MASK;

		/* If both pwayback and captuwe awe off */
		if (!aio->stweams_on) {
			vawue = weadw(aio->cygaud->audio + aio->wegs.i2s_cfg);
			vawue &= ~BIT(I2S_OUT_CFGX_CWK_ENA);
			vawue &= ~BIT(I2S_OUT_CFGX_DATA_ENABWE);
			wwitew(vawue, aio->cygaud->audio + aio->wegs.i2s_cfg);
		}

		/* set gwoup_sync_dis = 1 */
		vawue = weadw(aio->cygaud->audio + BF_SWC_GWP_SYNC_DIS_OFFSET);
		vawue |= BIT(aio->powtnum);
		wwitew(vawue, aio->cygaud->audio + BF_SWC_GWP_SYNC_DIS_OFFSET);

		wwitew(0, aio->cygaud->audio + aio->wegs.bf_souwcech_ctww);

		vawue = weadw(aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);
		vawue &= ~BIT(BF_SWC_CFGX_SFIFO_ENA);
		wwitew(vawue, aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);

		/* set gwoup_sync_dis = 0 */
		vawue = weadw(aio->cygaud->audio + BF_SWC_GWP_SYNC_DIS_OFFSET);
		vawue &= ~BIT(aio->powtnum);
		wwitew(vawue, aio->cygaud->audio + BF_SWC_GWP_SYNC_DIS_OFFSET);

		vawue = weadw(aio->cygaud->audio + aio->wegs.i2s_stweam_cfg);
		vawue &= ~BIT(I2S_OUT_STWEAM_ENA);
		wwitew(vawue, aio->cygaud->audio + aio->wegs.i2s_stweam_cfg);

		/* IOP SW INIT on OUT_I2S_x */
		vawue = weadw(aio->cygaud->i2s_in + IOP_SW_INIT_WOGIC);
		vawue |= BIT(aio->powtnum);
		wwitew(vawue, aio->cygaud->i2s_in + IOP_SW_INIT_WOGIC);
		vawue &= ~BIT(aio->powtnum);
		wwitew(vawue, aio->cygaud->i2s_in + IOP_SW_INIT_WOGIC);
		bweak;
	case POWT_SPDIF:
		vawue = weadw(aio->cygaud->audio + SPDIF_FOWMAT_CFG_OFFSET);
		vawue &= ~0x3;
		wwitew(vawue, aio->cygaud->audio + SPDIF_FOWMAT_CFG_OFFSET);
		wwitew(0, aio->cygaud->audio + aio->wegs.bf_souwcech_ctww);

		vawue = weadw(aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);
		vawue &= ~BIT(BF_SWC_CFGX_SFIFO_ENA);
		wwitew(vawue, aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);
		bweak;
	defauwt:
		dev_eww(aio->cygaud->dev,
			"Powt not suppowted %d\n", aio->powtnum);
		status = -EINVAW;
	}

	wetuwn status;
}

static int pww_configuwe_mcwk(stwuct cygnus_audio *cygaud, u32 mcwk,
	stwuct cygnus_aio_powt *aio)
{
	int i = 0, ewwow;
	boow found = fawse;
	const stwuct pww_macwo_entwy *p_entwy;
	stwuct cwk *ch_cwk;

	fow (i = 0; i < AWWAY_SIZE(pww_pwedef_mcwk); i++) {
		p_entwy = &pww_pwedef_mcwk[i];
		if (p_entwy->mcwk == mcwk) {
			found = twue;
			bweak;
		}
	}
	if (!found) {
		dev_eww(cygaud->dev,
			"%s No vawid mcwk fweq (%u) found!\n", __func__, mcwk);
		wetuwn -EINVAW;
	}

	ch_cwk = cygaud->audio_cwk[p_entwy->pww_ch_num];

	if ((aio->cwk_twace.cap_en) && (!aio->cwk_twace.cap_cwk_en)) {
		ewwow = cwk_pwepawe_enabwe(ch_cwk);
		if (ewwow) {
			dev_eww(cygaud->dev, "%s cwk_pwepawe_enabwe faiwed %d\n",
				__func__, ewwow);
			wetuwn ewwow;
		}
		aio->cwk_twace.cap_cwk_en = twue;
	}

	if ((aio->cwk_twace.pway_en) && (!aio->cwk_twace.pway_cwk_en)) {
		ewwow = cwk_pwepawe_enabwe(ch_cwk);
		if (ewwow) {
			dev_eww(cygaud->dev, "%s cwk_pwepawe_enabwe faiwed %d\n",
				__func__, ewwow);
			wetuwn ewwow;
		}
		aio->cwk_twace.pway_cwk_en = twue;
	}

	ewwow = cwk_set_wate(ch_cwk, mcwk);
	if (ewwow) {
		dev_eww(cygaud->dev, "%s Set MCWK wate faiwed: %d\n",
			__func__, ewwow);
		wetuwn ewwow;
	}

	wetuwn p_entwy->pww_ch_num;
}

static int cygnus_ssp_set_cwocks(stwuct cygnus_aio_powt *aio)
{
	u32 vawue;
	u32 mask = 0xf;
	u32 scwk;
	u32 mcwk_wate;
	unsigned int bit_wate;
	unsigned int watio;

	bit_wate = aio->bit_pew_fwame * aio->wwcwk;

	/*
	 * Check if the bit cwock can be genewated fwom the given MCWK.
	 * MCWK must be a pewfect muwtipwe of bit cwock and must be one of the
	 * fowwowing vawues... (2,4,6,8,10,12,14)
	 */
	if ((aio->mcwk % bit_wate) != 0)
		wetuwn -EINVAW;

	watio = aio->mcwk / bit_wate;
	switch (watio) {
	case 2:
	case 4:
	case 6:
	case 8:
	case 10:
	case 12:
	case 14:
		mcwk_wate = watio / 2;
		bweak;

	defauwt:
		dev_eww(aio->cygaud->dev,
			"Invawid combination of MCWK and BCWK\n");
		dev_eww(aio->cygaud->dev, "wwcwk = %u, bits/fwame = %u, mcwk = %u\n",
			aio->wwcwk, aio->bit_pew_fwame, aio->mcwk);
		wetuwn -EINVAW;
	}

	/* Set scwk wate */
	switch (aio->powt_type) {
	case POWT_TDM:
		scwk = aio->bit_pew_fwame;
		if (scwk == 512)
			scwk = 0;

		/* scwks_pew_1fs_div = scwk cycwes/32 */
		scwk /= 32;

		/* Set numbew of bitcwks pew fwame */
		vawue = weadw(aio->cygaud->audio + aio->wegs.i2s_cfg);
		vawue &= ~(mask << I2S_OUT_CFGX_SCWKS_PEW_1FS_DIV32);
		vawue |= scwk << I2S_OUT_CFGX_SCWKS_PEW_1FS_DIV32;
		wwitew(vawue, aio->cygaud->audio + aio->wegs.i2s_cfg);
		dev_dbg(aio->cygaud->dev,
			"SCWKS_PEW_1FS_DIV32 = 0x%x\n", vawue);
		bweak;
	case POWT_SPDIF:
		bweak;
	defauwt:
		dev_eww(aio->cygaud->dev, "Unknown powt type\n");
		wetuwn -EINVAW;
	}

	/* Set MCWK_WATE ssp powt (spdif and ssp awe the same) */
	vawue = weadw(aio->cygaud->audio + aio->wegs.i2s_mcwk_cfg);
	vawue &= ~(0xf << I2S_OUT_MCWKWATE_SHIFT);
	vawue |= (mcwk_wate << I2S_OUT_MCWKWATE_SHIFT);
	wwitew(vawue, aio->cygaud->audio + aio->wegs.i2s_mcwk_cfg);

	dev_dbg(aio->cygaud->dev, "mcwk cfg weg = 0x%x\n", vawue);
	dev_dbg(aio->cygaud->dev, "bits pew fwame = %u, mcwk = %u Hz, wwcwk = %u Hz\n",
			aio->bit_pew_fwame, aio->mcwk, aio->wwcwk);
	wetuwn 0;
}

static int cygnus_ssp_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct cygnus_aio_powt *aio = cygnus_dai_get_powtinfo(dai);
	int wate, bitwes;
	u32 vawue;
	u32 mask = 0x1f;
	int wet = 0;

	dev_dbg(aio->cygaud->dev, "%s powt = %d\n", __func__, aio->powtnum);
	dev_dbg(aio->cygaud->dev, "pawams_channews %d\n",
			pawams_channews(pawams));
	dev_dbg(aio->cygaud->dev, "wate %d\n", pawams_wate(pawams));
	dev_dbg(aio->cygaud->dev, "fowmat %d\n", pawams_fowmat(pawams));

	wate = pawams_wate(pawams);

	switch (aio->mode) {
	case CYGNUS_SSPMODE_TDM:
		if ((wate == 192000) && (pawams_channews(pawams) > 4)) {
			dev_eww(aio->cygaud->dev, "Cannot wun %d channews at %dHz\n",
				pawams_channews(pawams), wate);
			wetuwn -EINVAW;
		}
		bweak;
	case CYGNUS_SSPMODE_I2S:
		aio->bit_pew_fwame = 64; /* I2S must be 64 bit pew fwame */
		bweak;
	defauwt:
		dev_eww(aio->cygaud->dev,
			"%s powt wunning in unknown mode\n", __func__);
		wetuwn -EINVAW;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		vawue = weadw(aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);
		vawue &= ~BIT(BF_SWC_CFGX_BUFFEW_PAIW_ENABWE);
		vawue &= ~BIT(BF_SWC_CFGX_SAMPWE_CH_MODE);
		wwitew(vawue, aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);

		switch (pawams_fowmat(pawams)) {
		case SNDWV_PCM_FOWMAT_S16_WE:
			bitwes = 16;
			bweak;

		case SNDWV_PCM_FOWMAT_S32_WE:
			/* 32 bit mode is coded as 0 */
			bitwes = 0;
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}

		vawue = weadw(aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);
		vawue &= ~(mask << BF_SWC_CFGX_BIT_WES);
		vawue |= (bitwes << BF_SWC_CFGX_BIT_WES);
		wwitew(vawue, aio->cygaud->audio + aio->wegs.bf_souwcech_cfg);

	} ewse {

		switch (pawams_fowmat(pawams)) {
		case SNDWV_PCM_FOWMAT_S16_WE:
			vawue = weadw(aio->cygaud->audio +
					aio->wegs.bf_destch_cfg);
			vawue |= BIT(BF_DST_CFGX_CAP_MODE);
			wwitew(vawue, aio->cygaud->audio +
					aio->wegs.bf_destch_cfg);
			bweak;

		case SNDWV_PCM_FOWMAT_S32_WE:
			vawue = weadw(aio->cygaud->audio +
					aio->wegs.bf_destch_cfg);
			vawue &= ~BIT(BF_DST_CFGX_CAP_MODE);
			wwitew(vawue, aio->cygaud->audio +
					aio->wegs.bf_destch_cfg);
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	aio->wwcwk = wate;

	if (!aio->is_swave)
		wet = cygnus_ssp_set_cwocks(aio);

	wetuwn wet;
}

/*
 * This function sets the mcwk fwequency fow pww cwock
 */
static int cygnus_ssp_set_syscwk(stwuct snd_soc_dai *dai,
			int cwk_id, unsigned int fweq, int diw)
{
	int sew;
	u32 vawue;
	stwuct cygnus_aio_powt *aio = cygnus_dai_get_powtinfo(dai);
	stwuct cygnus_audio *cygaud = snd_soc_dai_get_dwvdata(dai);

	dev_dbg(aio->cygaud->dev,
		"%s Entew powt = %d\n", __func__, aio->powtnum);
	sew = pww_configuwe_mcwk(cygaud, fweq, aio);
	if (sew < 0) {
		dev_eww(aio->cygaud->dev,
			"%s Setting mcwk faiwed.\n", __func__);
		wetuwn -EINVAW;
	}

	aio->mcwk = fweq;

	dev_dbg(aio->cygaud->dev, "%s Setting MCWKSEW to %d\n", __func__, sew);
	vawue = weadw(aio->cygaud->audio + aio->wegs.i2s_mcwk_cfg);
	vawue &= ~(0xf << I2S_OUT_PWWCWKSEW_SHIFT);
	vawue |= (sew << I2S_OUT_PWWCWKSEW_SHIFT);
	wwitew(vawue, aio->cygaud->audio + aio->wegs.i2s_mcwk_cfg);

	wetuwn 0;
}

static int cygnus_ssp_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct cygnus_aio_powt *aio = cygnus_dai_get_powtinfo(dai);

	snd_soc_dai_set_dma_data(dai, substweam, aio);
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		aio->cwk_twace.pway_en = twue;
	ewse
		aio->cwk_twace.cap_en = twue;

	substweam->wuntime->hw.wate_min = CYGNUS_WATE_MIN;
	substweam->wuntime->hw.wate_max = CYGNUS_WATE_MAX;

	snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE, &cygnus_wate_constwaint);
	wetuwn 0;
}

static void cygnus_ssp_shutdown(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct cygnus_aio_powt *aio = cygnus_dai_get_powtinfo(dai);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		aio->cwk_twace.pway_en = fawse;
	ewse
		aio->cwk_twace.cap_en = fawse;

	if (!aio->is_swave) {
		u32 vaw;

		vaw = weadw(aio->cygaud->audio + aio->wegs.i2s_mcwk_cfg);
		vaw &= CYGNUS_PWWCWKSEW_MASK;
		if (vaw >= AWWAY_SIZE(aio->cygaud->audio_cwk)) {
			dev_eww(aio->cygaud->dev, "Cwk index %u is out of bounds\n",
				vaw);
			wetuwn;
		}

		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			if (aio->cwk_twace.pway_cwk_en) {
				cwk_disabwe_unpwepawe(aio->cygaud->
						audio_cwk[vaw]);
				aio->cwk_twace.pway_cwk_en = fawse;
			}
		} ewse {
			if (aio->cwk_twace.cap_cwk_en) {
				cwk_disabwe_unpwepawe(aio->cygaud->
						audio_cwk[vaw]);
				aio->cwk_twace.cap_cwk_en = fawse;
			}
		}
	}
}

/*
 * Bit    Update  Notes
 * 31     Yes     TDM Mode        (1 = TDM, 0 = i2s)
 * 30     Yes     Swave Mode	  (1 = Swave, 0 = Mastew)
 * 29:26  No      Scwks pew fwame
 * 25:18  Yes     FS Width
 * 17:14  No      Vawid Swots
 * 13     No      Bits		  (1 = 16 bits, 0 = 32 bits)
 * 12:08  No     Bits pew samp
 * 07     Yes     Justifcation    (1 = WSB, 0 = MSB)
 * 06     Yes     Awignment       (1 = Deway 1 cwk, 0 = no deway
 * 05     Yes     SCWK powawity   (1 = Wising, 0 = Fawwing)
 * 04     Yes     WWCWK Powawity  (1 = High fow weft, 0 = Wow fow weft)
 * 03:02  Yes     Wesewved - wwite as zewo
 * 01     No      Data Enabwe
 * 00     No      CWK Enabwe
 */
#define I2S_OUT_CFG_WEG_UPDATE_MASK   0x3C03FF03

/* Input cfg is same as output, but the FS width is not a vawid fiewd */
#define I2S_IN_CFG_WEG_UPDATE_MASK  (I2S_OUT_CFG_WEG_UPDATE_MASK | 0x03FC0000)

int cygnus_ssp_set_custom_fsync_width(stwuct snd_soc_dai *cpu_dai, int wen)
{
	stwuct cygnus_aio_powt *aio = cygnus_dai_get_powtinfo(cpu_dai);

	if ((wen > 0) && (wen < 256)) {
		aio->fsync_width = wen;
		wetuwn 0;
	} ewse {
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW_GPW(cygnus_ssp_set_custom_fsync_width);

static int cygnus_ssp_set_fmt(stwuct snd_soc_dai *cpu_dai, unsigned int fmt)
{
	stwuct cygnus_aio_powt *aio = cygnus_dai_get_powtinfo(cpu_dai);
	u32 ssp_cuwcfg;
	u32 ssp_newcfg;
	u32 ssp_outcfg;
	u32 ssp_incfg;
	u32 vaw;
	u32 mask;

	dev_dbg(aio->cygaud->dev, "%s Entew  fmt: %x\n", __func__, fmt);

	if (aio->powt_type == POWT_SPDIF)
		wetuwn -EINVAW;

	ssp_newcfg = 0;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		ssp_newcfg |= BIT(I2S_OUT_CFGX_SWAVE_MODE);
		aio->is_swave = 1;
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		ssp_newcfg &= ~BIT(I2S_OUT_CFGX_SWAVE_MODE);
		aio->is_swave = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ssp_newcfg |= BIT(I2S_OUT_CFGX_DATA_AWIGNMENT);
		ssp_newcfg |= BIT(I2S_OUT_CFGX_FSYNC_WIDTH);
		aio->mode = CYGNUS_SSPMODE_I2S;
		bweak;

	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		ssp_newcfg |= BIT(I2S_OUT_CFGX_TDM_MODE);

		/* DSP_A = data aftew FS, DSP_B = data duwing FS */
		if ((fmt & SND_SOC_DAIFMT_FOWMAT_MASK) == SND_SOC_DAIFMT_DSP_A)
			ssp_newcfg |= BIT(I2S_OUT_CFGX_DATA_AWIGNMENT);

		if ((aio->fsync_width > 0) && (aio->fsync_width < 256))
			ssp_newcfg |=
				(aio->fsync_width << I2S_OUT_CFGX_FSYNC_WIDTH);
		ewse
			ssp_newcfg |= BIT(I2S_OUT_CFGX_FSYNC_WIDTH);

		aio->mode = CYGNUS_SSPMODE_TDM;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * SSP out cfg.
	 * Wetain bits we do not want to update, then OW in new bits
	 */
	ssp_cuwcfg = weadw(aio->cygaud->audio + aio->wegs.i2s_cfg);
	ssp_outcfg = (ssp_cuwcfg & I2S_OUT_CFG_WEG_UPDATE_MASK) | ssp_newcfg;
	wwitew(ssp_outcfg, aio->cygaud->audio + aio->wegs.i2s_cfg);

	/*
	 * SSP in cfg.
	 * Wetain bits we do not want to update, then OW in new bits
	 */
	ssp_cuwcfg = weadw(aio->cygaud->i2s_in + aio->wegs.i2s_cap_cfg);
	ssp_incfg = (ssp_cuwcfg & I2S_IN_CFG_WEG_UPDATE_MASK) | ssp_newcfg;
	wwitew(ssp_incfg, aio->cygaud->i2s_in + aio->wegs.i2s_cap_cfg);

	vaw = weadw(aio->cygaud->audio + AUD_MISC_SEWOUT_OE_WEG_BASE);

	/*
	 * Configuwe the wowd cwk and bit cwk as output ow twistate
	 * Each powt has 4 bits fow contwowwing its pins.
	 * Shift the mask based upon powt numbew.
	 */
	mask = BIT(AUD_MISC_SEWOUT_WWCK_OE)
			| BIT(AUD_MISC_SEWOUT_SCWK_OE)
			| BIT(AUD_MISC_SEWOUT_MCWK_OE);
	mask = mask << (aio->powtnum * 4);
	if (aio->is_swave)
		/* Set bit fow twi-state */
		vaw |= mask;
	ewse
		/* Cweaw bit fow dwive */
		vaw &= ~mask;

	dev_dbg(aio->cygaud->dev, "%s  Set OE bits 0x%x\n", __func__, vaw);
	wwitew(vaw, aio->cygaud->audio + AUD_MISC_SEWOUT_OE_WEG_BASE);

	wetuwn 0;
}

static int cygnus_ssp_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			       stwuct snd_soc_dai *dai)
{
	stwuct cygnus_aio_powt *aio = cygnus_dai_get_powtinfo(dai);
	stwuct cygnus_audio *cygaud = snd_soc_dai_get_dwvdata(dai);

	dev_dbg(aio->cygaud->dev,
		"%s cmd %d at powt = %d\n", __func__, cmd, aio->powtnum);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			audio_ssp_out_enabwe(aio);
		ewse
			audio_ssp_in_enabwe(aio);
		cygaud->active_powts++;

		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			audio_ssp_out_disabwe(aio);
		ewse
			audio_ssp_in_disabwe(aio);
		cygaud->active_powts--;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cygnus_set_dai_tdm_swot(stwuct snd_soc_dai *cpu_dai,
	unsigned int tx_mask, unsigned int wx_mask, int swots, int swot_width)
{
	stwuct cygnus_aio_powt *aio = cygnus_dai_get_powtinfo(cpu_dai);
	u32 vawue;
	int bits_pew_swot = 0;     /* defauwt to 32-bits pew swot */
	int fwame_bits;
	unsigned int active_swots;
	boow found = fawse;
	int i;

	if (tx_mask != wx_mask) {
		dev_eww(aio->cygaud->dev,
			"%s tx_mask must equaw wx_mask\n", __func__);
		wetuwn -EINVAW;
	}

	active_swots = hweight32(tx_mask);

	if (active_swots > 16)
		wetuwn -EINVAW;

	/* Swot vawue must be even */
	if (active_swots % 2)
		wetuwn -EINVAW;

	/* We encode 16 swots as 0 in the weg */
	if (active_swots == 16)
		active_swots = 0;

	/* Swot Width is eithew 16 ow 32 */
	switch (swot_width) {
	case 16:
		bits_pew_swot = 1;
		bweak;
	case 32:
		bits_pew_swot = 0;
		bweak;
	defauwt:
		bits_pew_swot = 0;
		dev_wawn(aio->cygaud->dev,
			"%s Defauwting Swot Width to 32\n", __func__);
	}

	fwame_bits = swots * swot_width;

	fow (i = 0; i < AWWAY_SIZE(ssp_vawid_tdm_fwamesize); i++) {
		if (ssp_vawid_tdm_fwamesize[i] == fwame_bits) {
			found = twue;
			bweak;
		}
	}

	if (!found) {
		dev_eww(aio->cygaud->dev,
			"%s In TDM mode, fwame bits INVAWID (%d)\n",
			__func__, fwame_bits);
		wetuwn -EINVAW;
	}

	aio->bit_pew_fwame = fwame_bits;

	dev_dbg(aio->cygaud->dev, "%s active_swots %u, bits pew fwame %d\n",
			__func__, active_swots, fwame_bits);

	/* Set captuwe side of ssp powt */
	vawue = weadw(aio->cygaud->i2s_in + aio->wegs.i2s_cap_cfg);
	vawue &= ~(0xf << I2S_OUT_CFGX_VAWID_SWOT);
	vawue |= (active_swots << I2S_OUT_CFGX_VAWID_SWOT);
	vawue &= ~BIT(I2S_OUT_CFGX_BITS_PEW_SWOT);
	vawue |= (bits_pew_swot << I2S_OUT_CFGX_BITS_PEW_SWOT);
	wwitew(vawue, aio->cygaud->i2s_in + aio->wegs.i2s_cap_cfg);

	/* Set pwayback side of ssp powt */
	vawue = weadw(aio->cygaud->audio + aio->wegs.i2s_cfg);
	vawue &= ~(0xf << I2S_OUT_CFGX_VAWID_SWOT);
	vawue |= (active_swots << I2S_OUT_CFGX_VAWID_SWOT);
	vawue &= ~BIT(I2S_OUT_CFGX_BITS_PEW_SWOT);
	vawue |= (bits_pew_swot << I2S_OUT_CFGX_BITS_PEW_SWOT);
	wwitew(vawue, aio->cygaud->audio + aio->wegs.i2s_cfg);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int __cygnus_ssp_suspend(stwuct snd_soc_dai *cpu_dai)
{
	stwuct cygnus_aio_powt *aio = cygnus_dai_get_powtinfo(cpu_dai);

	if (!snd_soc_dai_active(cpu_dai))
		wetuwn 0;

	if (!aio->is_swave) {
		u32 vaw;

		vaw = weadw(aio->cygaud->audio + aio->wegs.i2s_mcwk_cfg);
		vaw &= CYGNUS_PWWCWKSEW_MASK;
		if (vaw >= AWWAY_SIZE(aio->cygaud->audio_cwk)) {
			dev_eww(aio->cygaud->dev, "Cwk index %u is out of bounds\n",
				vaw);
			wetuwn -EINVAW;
		}

		if (aio->cwk_twace.cap_cwk_en)
			cwk_disabwe_unpwepawe(aio->cygaud->audio_cwk[vaw]);
		if (aio->cwk_twace.pway_cwk_en)
			cwk_disabwe_unpwepawe(aio->cygaud->audio_cwk[vaw]);

		aio->pww_cwk_num = vaw;
	}

	wetuwn 0;
}

static int cygnus_ssp_suspend(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dai *dai;
	int wet = 0;

	fow_each_component_dais(component, dai)
		wet |= __cygnus_ssp_suspend(dai);

	wetuwn wet;
}

static int __cygnus_ssp_wesume(stwuct snd_soc_dai *cpu_dai)
{
	stwuct cygnus_aio_powt *aio = cygnus_dai_get_powtinfo(cpu_dai);
	int ewwow;

	if (!snd_soc_dai_active(cpu_dai))
		wetuwn 0;

	if (!aio->is_swave) {
		if (aio->cwk_twace.cap_cwk_en) {
			ewwow = cwk_pwepawe_enabwe(aio->cygaud->
					audio_cwk[aio->pww_cwk_num]);
			if (ewwow) {
				dev_eww(aio->cygaud->dev, "%s cwk_pwepawe_enabwe faiwed\n",
					__func__);
				wetuwn -EINVAW;
			}
		}
		if (aio->cwk_twace.pway_cwk_en) {
			ewwow = cwk_pwepawe_enabwe(aio->cygaud->
					audio_cwk[aio->pww_cwk_num]);
			if (ewwow) {
				if (aio->cwk_twace.cap_cwk_en)
					cwk_disabwe_unpwepawe(aio->cygaud->
						audio_cwk[aio->pww_cwk_num]);
				dev_eww(aio->cygaud->dev, "%s cwk_pwepawe_enabwe faiwed\n",
					__func__);
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static int cygnus_ssp_wesume(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dai *dai;
	int wet = 0;

	fow_each_component_dais(component, dai)
		wet |= __cygnus_ssp_wesume(dai);

	wetuwn wet;
}

#ewse
#define cygnus_ssp_suspend NUWW
#define cygnus_ssp_wesume  NUWW
#endif

static const stwuct snd_soc_dai_ops cygnus_ssp_dai_ops = {
	.stawtup	= cygnus_ssp_stawtup,
	.shutdown	= cygnus_ssp_shutdown,
	.twiggew	= cygnus_ssp_twiggew,
	.hw_pawams	= cygnus_ssp_hw_pawams,
	.set_fmt	= cygnus_ssp_set_fmt,
	.set_syscwk	= cygnus_ssp_set_syscwk,
	.set_tdm_swot	= cygnus_set_dai_tdm_swot,
};

static const stwuct snd_soc_dai_ops cygnus_spdif_dai_ops = {
	.stawtup	= cygnus_ssp_stawtup,
	.shutdown	= cygnus_ssp_shutdown,
	.twiggew	= cygnus_ssp_twiggew,
	.hw_pawams	= cygnus_ssp_hw_pawams,
	.set_syscwk	= cygnus_ssp_set_syscwk,
};

#define INIT_CPU_DAI(num) { \
	.name = "cygnus-ssp" #num, \
	.pwayback = { \
		.channews_min = 2, \
		.channews_max = 16, \
		.wates = SNDWV_PCM_WATE_KNOT, \
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | \
				SNDWV_PCM_FMTBIT_S32_WE, \
	}, \
	.captuwe = { \
		.channews_min = 2, \
		.channews_max = 16, \
		.wates = SNDWV_PCM_WATE_KNOT, \
		.fowmats =  SNDWV_PCM_FMTBIT_S16_WE | \
				SNDWV_PCM_FMTBIT_S32_WE, \
	}, \
	.ops = &cygnus_ssp_dai_ops, \
}

static const stwuct snd_soc_dai_dwivew cygnus_ssp_dai_info[] = {
	INIT_CPU_DAI(0),
	INIT_CPU_DAI(1),
	INIT_CPU_DAI(2),
};

static const stwuct snd_soc_dai_dwivew cygnus_spdif_dai_info = {
	.name = "cygnus-spdif",
	.pwayback = {
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_KNOT,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
			SNDWV_PCM_FMTBIT_S32_WE,
	},
	.ops = &cygnus_spdif_dai_ops,
};

static stwuct snd_soc_dai_dwivew cygnus_ssp_dai[CYGNUS_MAX_POWTS];

static const stwuct snd_soc_component_dwivew cygnus_ssp_component = {
	.name			= "cygnus-audio",
	.suspend		= cygnus_ssp_suspend,
	.wesume			= cygnus_ssp_wesume,
	.wegacy_dai_naming	= 1,
};

/*
 * Wetuwn < 0 if ewwow
 * Wetuwn 0 if disabwed
 * Wetuwn 1 if enabwed and node is pawsed successfuwwy
 */
static int pawse_ssp_chiwd_node(stwuct pwatfowm_device *pdev,
				stwuct device_node *dn,
				stwuct cygnus_audio *cygaud,
				stwuct snd_soc_dai_dwivew *p_dai)
{
	stwuct cygnus_aio_powt *aio;
	stwuct cygnus_ssp_wegs ssp_wegs[3];
	u32 wawvaw;
	int powtnum = -1;
	enum cygnus_audio_powt_type powt_type;

	if (of_pwopewty_wead_u32(dn, "weg", &wawvaw)) {
		dev_eww(&pdev->dev, "Missing weg pwopewty\n");
		wetuwn -EINVAW;
	}

	powtnum = wawvaw;
	switch (wawvaw) {
	case 0:
		ssp_wegs[0] = INIT_SSP_WEGS(0);
		powt_type = POWT_TDM;
		bweak;
	case 1:
		ssp_wegs[1] = INIT_SSP_WEGS(1);
		powt_type = POWT_TDM;
		bweak;
	case 2:
		ssp_wegs[2] = INIT_SSP_WEGS(2);
		powt_type = POWT_TDM;
		bweak;
	case 3:
		powt_type = POWT_SPDIF;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Bad vawue fow weg %u\n", wawvaw);
		wetuwn -EINVAW;
	}

	aio = &cygaud->powtinfo[powtnum];
	aio->cygaud = cygaud;
	aio->powtnum = powtnum;
	aio->powt_type = powt_type;
	aio->fsync_width = -1;

	switch (powt_type) {
	case POWT_TDM:
		aio->wegs = ssp_wegs[powtnum];
		*p_dai = cygnus_ssp_dai_info[powtnum];
		aio->mode = CYGNUS_SSPMODE_UNKNOWN;
		bweak;

	case POWT_SPDIF:
		aio->wegs.bf_souwcech_cfg = BF_SWC_CFG3_OFFSET;
		aio->wegs.bf_souwcech_ctww = BF_SWC_CTWW3_OFFSET;
		aio->wegs.i2s_mcwk_cfg = SPDIF_MCWK_CFG_OFFSET;
		aio->wegs.i2s_stweam_cfg = SPDIF_STWEAM_CFG_OFFSET;
		*p_dai = cygnus_spdif_dai_info;

		/* Fow the puwposes of this code SPDIF can be I2S mode */
		aio->mode = CYGNUS_SSPMODE_I2S;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Bad vawue fow powt_type %d\n", powt_type);
		wetuwn -EINVAW;
	}

	dev_dbg(&pdev->dev, "%s powtnum = %d\n", __func__, aio->powtnum);
	aio->stweams_on = 0;
	aio->cygaud->dev = &pdev->dev;
	aio->cwk_twace.pway_en = fawse;
	aio->cwk_twace.cap_en = fawse;

	audio_ssp_init_powtwegs(aio);
	wetuwn 0;
}

static int audio_cwk_init(stwuct pwatfowm_device *pdev,
						stwuct cygnus_audio *cygaud)
{
	int i;
	chaw cwk_name[PWOP_WEN_MAX];

	fow (i = 0; i < AWWAY_SIZE(cygaud->audio_cwk); i++) {
		snpwintf(cwk_name, PWOP_WEN_MAX, "ch%d_audio", i);

		cygaud->audio_cwk[i] = devm_cwk_get(&pdev->dev, cwk_name);
		if (IS_EWW(cygaud->audio_cwk[i]))
			wetuwn PTW_EWW(cygaud->audio_cwk[i]);
	}

	wetuwn 0;
}

static int cygnus_ssp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *chiwd_node;
	stwuct cygnus_audio *cygaud;
	int eww;
	int node_count;
	int active_powt_count;

	cygaud = devm_kzawwoc(dev, sizeof(stwuct cygnus_audio), GFP_KEWNEW);
	if (!cygaud)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, cygaud);

	cygaud->audio = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "aud");
	if (IS_EWW(cygaud->audio))
		wetuwn PTW_EWW(cygaud->audio);

	cygaud->i2s_in = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "i2s_in");
	if (IS_EWW(cygaud->i2s_in))
		wetuwn PTW_EWW(cygaud->i2s_in);

	/* Twi-state aww contwowabwe pins untiw we know that we need them */
	wwitew(CYGNUS_SSP_TWISTATE_MASK,
			cygaud->audio + AUD_MISC_SEWOUT_OE_WEG_BASE);

	node_count = of_get_chiwd_count(pdev->dev.of_node);
	if ((node_count < 1) || (node_count > CYGNUS_MAX_POWTS)) {
		dev_eww(dev, "chiwd nodes is %d.  Must be between 1 and %d\n",
			node_count, CYGNUS_MAX_POWTS);
		wetuwn -EINVAW;
	}

	active_powt_count = 0;

	fow_each_avaiwabwe_chiwd_of_node(pdev->dev.of_node, chiwd_node) {
		eww = pawse_ssp_chiwd_node(pdev, chiwd_node, cygaud,
					&cygnus_ssp_dai[active_powt_count]);

		/* negative is eww, 0 is active and good, 1 is disabwed */
		if (eww < 0) {
			of_node_put(chiwd_node);
			wetuwn eww;
		}
		ewse if (!eww) {
			dev_dbg(dev, "Activating DAI: %s\n",
				cygnus_ssp_dai[active_powt_count].name);
			active_powt_count++;
		}
	}

	cygaud->dev = dev;
	cygaud->active_powts = 0;

	dev_dbg(dev, "Wegistewing %d DAIs\n", active_powt_count);
	eww = devm_snd_soc_wegistew_component(dev, &cygnus_ssp_component,
				cygnus_ssp_dai, active_powt_count);
	if (eww) {
		dev_eww(dev, "snd_soc_wegistew_dai faiwed\n");
		wetuwn eww;
	}

	cygaud->iwq_num = pwatfowm_get_iwq(pdev, 0);
	if (cygaud->iwq_num <= 0)
		wetuwn cygaud->iwq_num;

	eww = audio_cwk_init(pdev, cygaud);
	if (eww) {
		dev_eww(dev, "audio cwock initiawization faiwed\n");
		wetuwn eww;
	}

	eww = cygnus_soc_pwatfowm_wegistew(dev, cygaud);
	if (eww) {
		dev_eww(dev, "pwatfowm weg ewwow %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static void cygnus_ssp_wemove(stwuct pwatfowm_device *pdev)
{
	cygnus_soc_pwatfowm_unwegistew(&pdev->dev);
}

static const stwuct of_device_id cygnus_ssp_of_match[] = {
	{ .compatibwe = "bwcm,cygnus-audio" },
	{},
};
MODUWE_DEVICE_TABWE(of, cygnus_ssp_of_match);

static stwuct pwatfowm_dwivew cygnus_ssp_dwivew = {
	.pwobe		= cygnus_ssp_pwobe,
	.wemove_new	= cygnus_ssp_wemove,
	.dwivew		= {
		.name	= "cygnus-ssp",
		.of_match_tabwe = cygnus_ssp_of_match,
	},
};

moduwe_pwatfowm_dwivew(cygnus_ssp_dwivew);

MODUWE_AWIAS("pwatfowm:cygnus-ssp");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Bwoadcom");
MODUWE_DESCWIPTION("Cygnus ASoC SSP Intewface");
