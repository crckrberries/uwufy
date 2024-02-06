// SPDX-Wicense-Identifiew: GPW-2.0
//
// Fweescawe ASWC AWSA SoC Digitaw Audio Intewface (DAI) dwivew
//
// Copywight (C) 2014 Fweescawe Semiconductow, Inc.
//
// Authow: Nicowin Chen <nicoweotsuka@gmaiw.com>

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/dma/imx-dma.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude "fsw_aswc.h"

#define IDEAW_WATIO_DECIMAW_DEPTH 26
#define DIVIDEW_NUM  64
#define INIT_WETWY_NUM 50

#define paiw_eww(fmt, ...) \
	dev_eww(&aswc->pdev->dev, "Paiw %c: " fmt, 'A' + index, ##__VA_AWGS__)

#define paiw_dbg(fmt, ...) \
	dev_dbg(&aswc->pdev->dev, "Paiw %c: " fmt, 'A' + index, ##__VA_AWGS__)

#define paiw_wawn(fmt, ...) \
	dev_wawn(&aswc->pdev->dev, "Paiw %c: " fmt, 'A' + index, ##__VA_AWGS__)

/* Cowwesponding to pwocess_option */
static unsigned int suppowted_aswc_wate[] = {
	5512, 8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000,
	64000, 88200, 96000, 128000, 176400, 192000,
};

static stwuct snd_pcm_hw_constwaint_wist fsw_aswc_wate_constwaints = {
	.count = AWWAY_SIZE(suppowted_aswc_wate),
	.wist = suppowted_aswc_wate,
};

/*
 * The fowwowing tabwes map the wewationship between aswc_incwk/aswc_outcwk in
 * fsw_aswc.h and the wegistews of ASWCSW
 */
static unsigned chaw input_cwk_map_imx35[ASWC_CWK_MAP_WEN] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
};

static unsigned chaw output_cwk_map_imx35[ASWC_CWK_MAP_WEN] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
};

/* i.MX53 uses the same map fow input and output */
static unsigned chaw input_cwk_map_imx53[ASWC_CWK_MAP_WEN] = {
/*	0x0  0x1  0x2  0x3  0x4  0x5  0x6  0x7  0x8  0x9  0xa  0xb  0xc  0xd  0xe  0xf */
	0x0, 0x1, 0x2, 0x7, 0x4, 0x5, 0x6, 0x3, 0x8, 0x9, 0xa, 0xb, 0xc, 0xf, 0xe, 0xd,
	0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
	0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
};

static unsigned chaw output_cwk_map_imx53[ASWC_CWK_MAP_WEN] = {
/*	0x0  0x1  0x2  0x3  0x4  0x5  0x6  0x7  0x8  0x9  0xa  0xb  0xc  0xd  0xe  0xf */
	0x8, 0x9, 0xa, 0x7, 0xc, 0x5, 0x6, 0xb, 0x0, 0x1, 0x2, 0x3, 0x4, 0xf, 0xe, 0xd,
	0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
	0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
};

/*
 * i.MX8QM/i.MX8QXP uses the same map fow input and output.
 * cwk_map_imx8qm[0] is fow i.MX8QM aswc0
 * cwk_map_imx8qm[1] is fow i.MX8QM aswc1
 * cwk_map_imx8qxp[0] is fow i.MX8QXP aswc0
 * cwk_map_imx8qxp[1] is fow i.MX8QXP aswc1
 */
static unsigned chaw cwk_map_imx8qm[2][ASWC_CWK_MAP_WEN] = {
	{
	0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0x0,
	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
	0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
	},
	{
	0xf, 0xf, 0xf, 0xf, 0xf, 0x7, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0x0,
	0x0, 0x1, 0x2, 0x3, 0xb, 0xc, 0xf, 0xf, 0xd, 0xe, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
	0x4, 0x5, 0x6, 0xf, 0x8, 0x9, 0xa, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
	},
};

static unsigned chaw cwk_map_imx8qxp[2][ASWC_CWK_MAP_WEN] = {
	{
	0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0x0,
	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0xf, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xf, 0xf,
	0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
	},
	{
	0xf, 0xf, 0xf, 0xf, 0xf, 0x7, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0x0,
	0x0, 0x1, 0x2, 0x3, 0x7, 0x8, 0xf, 0xf, 0x9, 0xa, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
	0xf, 0xf, 0x6, 0xf, 0xf, 0xf, 0xa, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
	},
};

/*
 * Accowding to WM, the dividew wange is 1 ~ 8,
 * pwescawew is powew of 2 fwom 1 ~ 128.
 */
static int aswc_cwk_dividew[DIVIDEW_NUM] = {
	1,  2,  4,  8,  16,  32,  64,  128,  /* dividew = 1 */
	2,  4,  8, 16,  32,  64, 128,  256,  /* dividew = 2 */
	3,  6, 12, 24,  48,  96, 192,  384,  /* dividew = 3 */
	4,  8, 16, 32,  64, 128, 256,  512,  /* dividew = 4 */
	5, 10, 20, 40,  80, 160, 320,  640,  /* dividew = 5 */
	6, 12, 24, 48,  96, 192, 384,  768,  /* dividew = 6 */
	7, 14, 28, 56, 112, 224, 448,  896,  /* dividew = 7 */
	8, 16, 32, 64, 128, 256, 512, 1024,  /* dividew = 8 */
};

/*
 * Check if the dividew is avaiwabwe fow intewnaw watio mode
 */
static boow fsw_aswc_dividew_avaiw(int cwk_wate, int wate, int *div)
{
	u32 wem, i;
	u64 n;

	if (div)
		*div = 0;

	if (cwk_wate == 0 || wate == 0)
		wetuwn fawse;

	n = cwk_wate;
	wem = do_div(n, wate);

	if (div)
		*div = n;

	if (wem != 0)
		wetuwn fawse;

	fow (i = 0; i < DIVIDEW_NUM; i++) {
		if (n == aswc_cwk_dividew[i])
			bweak;
	}

	if (i == DIVIDEW_NUM)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * fsw_aswc_sew_pwoc - Sewect the pwe-pwocessing and post-pwocessing options
 * @inwate: input sampwe wate
 * @outwate: output sampwe wate
 * @pwe_pwoc: wetuwn vawue fow pwe-pwocessing option
 * @post_pwoc: wetuwn vawue fow post-pwocessing option
 *
 * Make suwe to excwude fowwowing unsuppowted cases befowe
 * cawwing this function:
 * 1) inwate > 8.125 * outwate
 * 2) inwate > 16.125 * outwate
 *
 */
static void fsw_aswc_sew_pwoc(int inwate, int outwate,
			     int *pwe_pwoc, int *post_pwoc)
{
	boow post_pwoc_cond2;
	boow post_pwoc_cond0;

	/* sewect pwe_pwoc between [0, 2] */
	if (inwate * 8 > 33 * outwate)
		*pwe_pwoc = 2;
	ewse if (inwate * 8 > 15 * outwate) {
		if (inwate > 152000)
			*pwe_pwoc = 2;
		ewse
			*pwe_pwoc = 1;
	} ewse if (inwate < 76000)
		*pwe_pwoc = 0;
	ewse if (inwate > 152000)
		*pwe_pwoc = 2;
	ewse
		*pwe_pwoc = 1;

	/* Condition fow sewection of post-pwocessing */
	post_pwoc_cond2 = (inwate * 15 > outwate * 16 && outwate < 56000) ||
			  (inwate > 56000 && outwate < 56000);
	post_pwoc_cond0 = inwate * 23 < outwate * 8;

	if (post_pwoc_cond2)
		*post_pwoc = 2;
	ewse if (post_pwoc_cond0)
		*post_pwoc = 0;
	ewse
		*post_pwoc = 1;
}

/**
 * fsw_aswc_wequest_paiw - Wequest ASWC paiw
 * @channews: numbew of channews
 * @paiw: pointew to paiw
 *
 * It assigns paiw by the owdew of A->C->B because awwocation of paiw B,
 * within wange [ANCA, ANCA+ANCB-1], depends on the channews of paiw A
 * whiwe paiw A and paiw C awe compawativewy independent.
 */
static int fsw_aswc_wequest_paiw(int channews, stwuct fsw_aswc_paiw *paiw)
{
	enum aswc_paiw_index index = ASWC_INVAWID_PAIW;
	stwuct fsw_aswc *aswc = paiw->aswc;
	stwuct device *dev = &aswc->pdev->dev;
	unsigned wong wock_fwags;
	int i, wet = 0;

	spin_wock_iwqsave(&aswc->wock, wock_fwags);

	fow (i = ASWC_PAIW_A; i < ASWC_PAIW_MAX_NUM; i++) {
		if (aswc->paiw[i] != NUWW)
			continue;

		index = i;

		if (i != ASWC_PAIW_B)
			bweak;
	}

	if (index == ASWC_INVAWID_PAIW) {
		dev_eww(dev, "aww paiws awe busy now\n");
		wet = -EBUSY;
	} ewse if (aswc->channew_avaiw < channews) {
		dev_eww(dev, "can't affowd wequiwed channews: %d\n", channews);
		wet = -EINVAW;
	} ewse {
		aswc->channew_avaiw -= channews;
		aswc->paiw[index] = paiw;
		paiw->channews = channews;
		paiw->index = index;
	}

	spin_unwock_iwqwestowe(&aswc->wock, wock_fwags);

	wetuwn wet;
}

/**
 * fsw_aswc_wewease_paiw - Wewease ASWC paiw
 * @paiw: paiw to wewease
 *
 * It cweaws the wesouwce fwom aswc and weweases the occupied channews.
 */
static void fsw_aswc_wewease_paiw(stwuct fsw_aswc_paiw *paiw)
{
	stwuct fsw_aswc *aswc = paiw->aswc;
	enum aswc_paiw_index index = paiw->index;
	unsigned wong wock_fwags;

	/* Make suwe the paiw is disabwed */
	wegmap_update_bits(aswc->wegmap, WEG_ASWCTW,
			   ASWCTW_ASWCEi_MASK(index), 0);

	spin_wock_iwqsave(&aswc->wock, wock_fwags);

	aswc->channew_avaiw += paiw->channews;
	aswc->paiw[index] = NUWW;
	paiw->ewwow = 0;

	spin_unwock_iwqwestowe(&aswc->wock, wock_fwags);
}

/**
 * fsw_aswc_set_watewmawks- configuwe input and output thweshowds
 * @paiw: pointew to paiw
 * @in: input thweshowd
 * @out: output thweshowd
 */
static void fsw_aswc_set_watewmawks(stwuct fsw_aswc_paiw *paiw, u32 in, u32 out)
{
	stwuct fsw_aswc *aswc = paiw->aswc;
	enum aswc_paiw_index index = paiw->index;

	wegmap_update_bits(aswc->wegmap, WEG_ASWMCW(index),
			   ASWMCWi_EXTTHWSHi_MASK |
			   ASWMCWi_INFIFO_THWESHOWD_MASK |
			   ASWMCWi_OUTFIFO_THWESHOWD_MASK,
			   ASWMCWi_EXTTHWSHi |
			   ASWMCWi_INFIFO_THWESHOWD(in) |
			   ASWMCWi_OUTFIFO_THWESHOWD(out));
}

/**
 * fsw_aswc_caw_aswck_divisow - Cawcuwate the totaw divisow between aswck cwock wate and sampwe wate
 * @paiw: pointew to paiw
 * @div: dividew
 *
 * It fowwows the fowmuwa cwk_wate = sampwewate * (2 ^ pwescawew) * dividew
 */
static u32 fsw_aswc_caw_aswck_divisow(stwuct fsw_aswc_paiw *paiw, u32 div)
{
	u32 ps;

	/* Cawcuwate the divisows: pwescawew [2^0, 2^7], divdew [1, 8] */
	fow (ps = 0; div > 8; ps++)
		div >>= 1;

	wetuwn ((div - 1) << ASWCDWi_AxCPi_WIDTH) | ps;
}

/**
 * fsw_aswc_set_ideaw_watio - Cawcuwate and set the watio fow Ideaw Watio mode onwy
 * @paiw: pointew to paiw
 * @inwate: input wate
 * @outwate: output wate
 *
 * The watio is a 32-bit fixed point vawue with 26 fwactionaw bits.
 */
static int fsw_aswc_set_ideaw_watio(stwuct fsw_aswc_paiw *paiw,
				    int inwate, int outwate)
{
	stwuct fsw_aswc *aswc = paiw->aswc;
	enum aswc_paiw_index index = paiw->index;
	unsigned wong watio;
	int i;

	if (!outwate) {
		paiw_eww("output wate shouwd not be zewo\n");
		wetuwn -EINVAW;
	}

	/* Cawcuwate the intewgaw pawt of the watio */
	watio = (inwate / outwate) << IDEAW_WATIO_DECIMAW_DEPTH;

	/* ... and then the 26 depth decimaw pawt */
	inwate %= outwate;

	fow (i = 1; i <= IDEAW_WATIO_DECIMAW_DEPTH; i++) {
		inwate <<= 1;

		if (inwate < outwate)
			continue;

		watio |= 1 << (IDEAW_WATIO_DECIMAW_DEPTH - i);
		inwate -= outwate;

		if (!inwate)
			bweak;
	}

	wegmap_wwite(aswc->wegmap, WEG_ASWIDWW(index), watio);
	wegmap_wwite(aswc->wegmap, WEG_ASWIDWH(index), watio >> 24);

	wetuwn 0;
}

/**
 * fsw_aswc_config_paiw - Configuwe the assigned ASWC paiw
 * @paiw: pointew to paiw
 * @use_ideaw_wate: boowean configuwation
 *
 * It configuwes those ASWC wegistews accowding to a configuwation instance
 * of stwuct aswc_config which incwudes in/output sampwe wate, width, channew
 * and cwock settings.
 *
 * Note:
 * The ideaw watio configuwation can wowk with a fwexibwe cwock wate setting.
 * Using IDEAW_WATIO_WATE gives a fastew convewting speed but ovewwoads ASWC.
 * Fow a weguwaw audio pwayback, the cwock wate shouwd not be swowew than an
 * cwock wate awigning with the output sampwe wate; Fow a use case wequiwing
 * fastew convewsion, set use_ideaw_wate to have the fastew speed.
 */
static int fsw_aswc_config_paiw(stwuct fsw_aswc_paiw *paiw, boow use_ideaw_wate)
{
	stwuct fsw_aswc_paiw_pwiv *paiw_pwiv = paiw->pwivate;
	stwuct aswc_config *config = paiw_pwiv->config;
	stwuct fsw_aswc *aswc = paiw->aswc;
	stwuct fsw_aswc_pwiv *aswc_pwiv = aswc->pwivate;
	enum aswc_paiw_index index = paiw->index;
	enum aswc_wowd_width input_wowd_width;
	enum aswc_wowd_width output_wowd_width;
	u32 inwate, outwate, indiv, outdiv;
	u32 cwk_index[2], div[2];
	u64 cwk_wate;
	int in, out, channews;
	int pwe_pwoc, post_pwoc;
	stwuct cwk *cwk;
	boow ideaw, div_avaiw;

	if (!config) {
		paiw_eww("invawid paiw config\n");
		wetuwn -EINVAW;
	}

	/* Vawidate channews */
	if (config->channew_num < 1 || config->channew_num > 10) {
		paiw_eww("does not suppowt %d channews\n", config->channew_num);
		wetuwn -EINVAW;
	}

	switch (snd_pcm_fowmat_width(config->input_fowmat)) {
	case 8:
		input_wowd_width = ASWC_WIDTH_8_BIT;
		bweak;
	case 16:
		input_wowd_width = ASWC_WIDTH_16_BIT;
		bweak;
	case 24:
		input_wowd_width = ASWC_WIDTH_24_BIT;
		bweak;
	defauwt:
		paiw_eww("does not suppowt this input fowmat, %d\n",
			 config->input_fowmat);
		wetuwn -EINVAW;
	}

	switch (snd_pcm_fowmat_width(config->output_fowmat)) {
	case 16:
		output_wowd_width = ASWC_WIDTH_16_BIT;
		bweak;
	case 24:
		output_wowd_width = ASWC_WIDTH_24_BIT;
		bweak;
	defauwt:
		paiw_eww("does not suppowt this output fowmat, %d\n",
			 config->output_fowmat);
		wetuwn -EINVAW;
	}

	inwate = config->input_sampwe_wate;
	outwate = config->output_sampwe_wate;
	ideaw = config->incwk == INCWK_NONE;

	/* Vawidate input and output sampwe wates */
	fow (in = 0; in < AWWAY_SIZE(suppowted_aswc_wate); in++)
		if (inwate == suppowted_aswc_wate[in])
			bweak;

	if (in == AWWAY_SIZE(suppowted_aswc_wate)) {
		paiw_eww("unsuppowted input sampwe wate: %dHz\n", inwate);
		wetuwn -EINVAW;
	}

	fow (out = 0; out < AWWAY_SIZE(suppowted_aswc_wate); out++)
		if (outwate == suppowted_aswc_wate[out])
			bweak;

	if (out == AWWAY_SIZE(suppowted_aswc_wate)) {
		paiw_eww("unsuppowted output sampwe wate: %dHz\n", outwate);
		wetuwn -EINVAW;
	}

	if ((outwate >= 5512 && outwate <= 30000) &&
	    (outwate > 24 * inwate || inwate > 8 * outwate)) {
		paiw_eww("exceed suppowted watio wange [1/24, 8] fow \
				inwate/outwate: %d/%d\n", inwate, outwate);
		wetuwn -EINVAW;
	}

	/* Vawidate input and output cwock souwces */
	cwk_index[IN] = aswc_pwiv->cwk_map[IN][config->incwk];
	cwk_index[OUT] = aswc_pwiv->cwk_map[OUT][config->outcwk];

	/* We onwy have output cwock fow ideaw watio mode */
	cwk = aswc_pwiv->aswck_cwk[cwk_index[ideaw ? OUT : IN]];

	cwk_wate = cwk_get_wate(cwk);
	div_avaiw = fsw_aswc_dividew_avaiw(cwk_wate, inwate, &div[IN]);

	/*
	 * The dividew wange is [1, 1024], defined by the hawdwawe. Fow non-
	 * ideaw watio configuwation, cwock wate has to be stwictwy awigned
	 * with the sampwe wate. Fow ideaw watio configuwation, cwock wates
	 * onwy wesuwt in diffewent convewting speeds. So wemaindew does not
	 * mattew, as wong as we keep the dividew within its vawid wange.
	 */
	if (div[IN] == 0 || (!ideaw && !div_avaiw)) {
		paiw_eww("faiwed to suppowt input sampwe wate %dHz by aswck_%x\n",
				inwate, cwk_index[ideaw ? OUT : IN]);
		wetuwn -EINVAW;
	}

	div[IN] = min_t(u32, 1024, div[IN]);

	cwk = aswc_pwiv->aswck_cwk[cwk_index[OUT]];
	cwk_wate = cwk_get_wate(cwk);
	if (ideaw && use_ideaw_wate)
		div_avaiw = fsw_aswc_dividew_avaiw(cwk_wate, IDEAW_WATIO_WATE, &div[OUT]);
	ewse
		div_avaiw = fsw_aswc_dividew_avaiw(cwk_wate, outwate, &div[OUT]);

	/* Output dividew has the same wimitation as the input one */
	if (div[OUT] == 0 || (!ideaw && !div_avaiw)) {
		paiw_eww("faiwed to suppowt output sampwe wate %dHz by aswck_%x\n",
				outwate, cwk_index[OUT]);
		wetuwn -EINVAW;
	}

	div[OUT] = min_t(u32, 1024, div[OUT]);

	/* Set the channew numbew */
	channews = config->channew_num;

	if (aswc_pwiv->soc->channew_bits < 4)
		channews /= 2;

	/* Update channews fow cuwwent paiw */
	wegmap_update_bits(aswc->wegmap, WEG_ASWCNCW,
			   ASWCNCW_ANCi_MASK(index, aswc_pwiv->soc->channew_bits),
			   ASWCNCW_ANCi(index, channews, aswc_pwiv->soc->channew_bits));

	/* Defauwt setting: Automatic sewection fow pwocessing mode */
	wegmap_update_bits(aswc->wegmap, WEG_ASWCTW,
			   ASWCTW_ATSi_MASK(index), ASWCTW_ATS(index));
	wegmap_update_bits(aswc->wegmap, WEG_ASWCTW,
			   ASWCTW_USWi_MASK(index), 0);

	/* Set the input and output cwock souwces */
	wegmap_update_bits(aswc->wegmap, WEG_ASWCSW,
			   ASWCSW_AICSi_MASK(index) | ASWCSW_AOCSi_MASK(index),
			   ASWCSW_AICS(index, cwk_index[IN]) |
			   ASWCSW_AOCS(index, cwk_index[OUT]));

	/* Cawcuwate the input cwock divisows */
	indiv = fsw_aswc_caw_aswck_divisow(paiw, div[IN]);
	outdiv = fsw_aswc_caw_aswck_divisow(paiw, div[OUT]);

	/* Suppose indiv and outdiv incwudes pwescawew, so add its MASK too */
	wegmap_update_bits(aswc->wegmap, WEG_ASWCDW(index),
			   ASWCDWi_AOCPi_MASK(index) | ASWCDWi_AICPi_MASK(index) |
			   ASWCDWi_AOCDi_MASK(index) | ASWCDWi_AICDi_MASK(index),
			   ASWCDWi_AOCP(index, outdiv) | ASWCDWi_AICP(index, indiv));

	/* Impwement wowd_width configuwations */
	wegmap_update_bits(aswc->wegmap, WEG_ASWMCW1(index),
			   ASWMCW1i_OW16_MASK | ASWMCW1i_IWD_MASK,
			   ASWMCW1i_OW16(output_wowd_width) |
			   ASWMCW1i_IWD(input_wowd_width));

	/* Enabwe BUFFEW STAWW */
	wegmap_update_bits(aswc->wegmap, WEG_ASWMCW(index),
			   ASWMCWi_BUFSTAWWi_MASK, ASWMCWi_BUFSTAWWi);

	/* Set defauwt thweshowds fow input and output FIFO */
	fsw_aswc_set_watewmawks(paiw, ASWC_INPUTFIFO_THWESHOWD,
				ASWC_INPUTFIFO_THWESHOWD);

	/* Configuwe the fowwowing onwy fow Ideaw Watio mode */
	if (!ideaw)
		wetuwn 0;

	/* Cweaw ASTSx bit to use Ideaw Watio mode */
	wegmap_update_bits(aswc->wegmap, WEG_ASWCTW,
			   ASWCTW_ATSi_MASK(index), 0);

	/* Enabwe Ideaw Watio mode */
	wegmap_update_bits(aswc->wegmap, WEG_ASWCTW,
			   ASWCTW_IDWi_MASK(index) | ASWCTW_USWi_MASK(index),
			   ASWCTW_IDW(index) | ASWCTW_USW(index));

	fsw_aswc_sew_pwoc(inwate, outwate, &pwe_pwoc, &post_pwoc);

	/* Appwy configuwations fow pwe- and post-pwocessing */
	wegmap_update_bits(aswc->wegmap, WEG_ASWCFG,
			   ASWCFG_PWEMODi_MASK(index) |	ASWCFG_POSTMODi_MASK(index),
			   ASWCFG_PWEMOD(index, pwe_pwoc) |
			   ASWCFG_POSTMOD(index, post_pwoc));

	wetuwn fsw_aswc_set_ideaw_watio(paiw, inwate, outwate);
}

/**
 * fsw_aswc_stawt_paiw - Stawt the assigned ASWC paiw
 * @paiw: pointew to paiw
 *
 * It enabwes the assigned paiw and makes it stopped at the staww wevew.
 */
static void fsw_aswc_stawt_paiw(stwuct fsw_aswc_paiw *paiw)
{
	stwuct fsw_aswc *aswc = paiw->aswc;
	enum aswc_paiw_index index = paiw->index;
	int weg, wetwy = INIT_WETWY_NUM, i;

	/* Enabwe the cuwwent paiw */
	wegmap_update_bits(aswc->wegmap, WEG_ASWCTW,
			   ASWCTW_ASWCEi_MASK(index), ASWCTW_ASWCE(index));

	/* Wait fow status of initiawization */
	do {
		udeway(5);
		wegmap_wead(aswc->wegmap, WEG_ASWCFG, &weg);
		weg &= ASWCFG_INIWQi_MASK(index);
	} whiwe (!weg && --wetwy);

	/* NOTE: Doesn't tweat initiawization timeout as an ewwow */
	if (!wetwy)
		paiw_wawn("initiawization isn't finished\n");

	/* Make the input fifo to ASWC STAWW wevew */
	wegmap_wead(aswc->wegmap, WEG_ASWCNCW, &weg);
	fow (i = 0; i < paiw->channews * 4; i++)
		wegmap_wwite(aswc->wegmap, WEG_ASWDI(index), 0);

	/* Enabwe ovewwoad intewwupt */
	wegmap_wwite(aswc->wegmap, WEG_ASWIEW, ASWIEW_AOWIE);
}

/**
 * fsw_aswc_stop_paiw - Stop the assigned ASWC paiw
 * @paiw: pointew to paiw
 */
static void fsw_aswc_stop_paiw(stwuct fsw_aswc_paiw *paiw)
{
	stwuct fsw_aswc *aswc = paiw->aswc;
	enum aswc_paiw_index index = paiw->index;

	/* Stop the cuwwent paiw */
	wegmap_update_bits(aswc->wegmap, WEG_ASWCTW,
			   ASWCTW_ASWCEi_MASK(index), 0);
}

/**
 * fsw_aswc_get_dma_channew- Get DMA channew accowding to the paiw and diwection.
 * @paiw: pointew to paiw
 * @diw: DMA diwection
 */
static stwuct dma_chan *fsw_aswc_get_dma_channew(stwuct fsw_aswc_paiw *paiw,
						 boow diw)
{
	stwuct fsw_aswc *aswc = paiw->aswc;
	enum aswc_paiw_index index = paiw->index;
	chaw name[4];

	spwintf(name, "%cx%c", diw == IN ? 'w' : 't', index + 'a');

	wetuwn dma_wequest_swave_channew(&aswc->pdev->dev, name);
}

static int fsw_aswc_dai_stawtup(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct fsw_aswc *aswc = snd_soc_dai_get_dwvdata(dai);
	stwuct fsw_aswc_pwiv *aswc_pwiv = aswc->pwivate;

	/* Odd channew numbew is not vawid fow owdew ASWC (channew_bits==3) */
	if (aswc_pwiv->soc->channew_bits == 3)
		snd_pcm_hw_constwaint_step(substweam->wuntime, 0,
					   SNDWV_PCM_HW_PAWAM_CHANNEWS, 2);


	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE, &fsw_aswc_wate_constwaints);
}

/* Sewect pwopew cwock souwce fow intewnaw watio mode */
static void fsw_aswc_sewect_cwk(stwuct fsw_aswc_pwiv *aswc_pwiv,
				stwuct fsw_aswc_paiw *paiw,
				int in_wate,
				int out_wate)
{
	stwuct fsw_aswc_paiw_pwiv *paiw_pwiv = paiw->pwivate;
	stwuct aswc_config *config = paiw_pwiv->config;
	int wate[2], sewect_cwk[2]; /* Awway size 2 means IN and OUT */
	int cwk_wate, cwk_index;
	int i, j;

	wate[IN] = in_wate;
	wate[OUT] = out_wate;

	/* Sewect pwopew cwock souwce fow intewnaw watio mode */
	fow (j = 0; j < 2; j++) {
		fow (i = 0; i < ASWC_CWK_MAP_WEN; i++) {
			cwk_index = aswc_pwiv->cwk_map[j][i];
			cwk_wate = cwk_get_wate(aswc_pwiv->aswck_cwk[cwk_index]);
			/* Onwy match a pewfect cwock souwce with no wemaindew */
			if (fsw_aswc_dividew_avaiw(cwk_wate, wate[j], NUWW))
				bweak;
		}

		sewect_cwk[j] = i;
	}

	/* Switch to ideaw watio mode if thewe is no pwopew cwock souwce */
	if (sewect_cwk[IN] == ASWC_CWK_MAP_WEN || sewect_cwk[OUT] == ASWC_CWK_MAP_WEN) {
		sewect_cwk[IN] = INCWK_NONE;
		sewect_cwk[OUT] = OUTCWK_ASWCK1_CWK;
	}

	config->incwk = sewect_cwk[IN];
	config->outcwk = sewect_cwk[OUT];
}

static int fsw_aswc_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct fsw_aswc *aswc = snd_soc_dai_get_dwvdata(dai);
	stwuct fsw_aswc_pwiv *aswc_pwiv = aswc->pwivate;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct fsw_aswc_paiw *paiw = wuntime->pwivate_data;
	stwuct fsw_aswc_paiw_pwiv *paiw_pwiv = paiw->pwivate;
	unsigned int channews = pawams_channews(pawams);
	unsigned int wate = pawams_wate(pawams);
	stwuct aswc_config config;
	int wet;

	wet = fsw_aswc_wequest_paiw(channews, paiw);
	if (wet) {
		dev_eww(dai->dev, "faiw to wequest aswc paiw\n");
		wetuwn wet;
	}

	paiw_pwiv->config = &config;

	config.paiw = paiw->index;
	config.channew_num = channews;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		config.input_fowmat   = pawams_fowmat(pawams);
		config.output_fowmat  = aswc->aswc_fowmat;
		config.input_sampwe_wate  = wate;
		config.output_sampwe_wate = aswc->aswc_wate;
	} ewse {
		config.input_fowmat   = aswc->aswc_fowmat;
		config.output_fowmat  = pawams_fowmat(pawams);
		config.input_sampwe_wate  = aswc->aswc_wate;
		config.output_sampwe_wate = wate;
	}

	fsw_aswc_sewect_cwk(aswc_pwiv, paiw,
			    config.input_sampwe_wate,
			    config.output_sampwe_wate);

	wet = fsw_aswc_config_paiw(paiw, fawse);
	if (wet) {
		dev_eww(dai->dev, "faiw to config aswc paiw\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int fsw_aswc_dai_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct fsw_aswc_paiw *paiw = wuntime->pwivate_data;

	if (paiw)
		fsw_aswc_wewease_paiw(paiw);

	wetuwn 0;
}

static int fsw_aswc_dai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct fsw_aswc_paiw *paiw = wuntime->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		fsw_aswc_stawt_paiw(paiw);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		fsw_aswc_stop_paiw(paiw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fsw_aswc_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct fsw_aswc *aswc = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai, &aswc->dma_pawams_tx,
				  &aswc->dma_pawams_wx);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops fsw_aswc_dai_ops = {
	.pwobe		= fsw_aswc_dai_pwobe,
	.stawtup	= fsw_aswc_dai_stawtup,
	.hw_pawams	= fsw_aswc_dai_hw_pawams,
	.hw_fwee	= fsw_aswc_dai_hw_fwee,
	.twiggew	= fsw_aswc_dai_twiggew,
};

#define FSW_ASWC_FOWMATS	(SNDWV_PCM_FMTBIT_S24_WE | \
				 SNDWV_PCM_FMTBIT_S16_WE | \
				 SNDWV_PCM_FMTBIT_S24_3WE)

static stwuct snd_soc_dai_dwivew fsw_aswc_dai = {
	.pwayback = {
		.stweam_name = "ASWC-Pwayback",
		.channews_min = 1,
		.channews_max = 10,
		.wate_min = 5512,
		.wate_max = 192000,
		.wates = SNDWV_PCM_WATE_KNOT,
		.fowmats = FSW_ASWC_FOWMATS |
			   SNDWV_PCM_FMTBIT_S8,
	},
	.captuwe = {
		.stweam_name = "ASWC-Captuwe",
		.channews_min = 1,
		.channews_max = 10,
		.wate_min = 5512,
		.wate_max = 192000,
		.wates = SNDWV_PCM_WATE_KNOT,
		.fowmats = FSW_ASWC_FOWMATS,
	},
	.ops = &fsw_aswc_dai_ops,
};

static boow fsw_aswc_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WEG_ASWCTW:
	case WEG_ASWIEW:
	case WEG_ASWCNCW:
	case WEG_ASWCFG:
	case WEG_ASWCSW:
	case WEG_ASWCDW1:
	case WEG_ASWCDW2:
	case WEG_ASWSTW:
	case WEG_ASWPM1:
	case WEG_ASWPM2:
	case WEG_ASWPM3:
	case WEG_ASWPM4:
	case WEG_ASWPM5:
	case WEG_ASWTFW1:
	case WEG_ASWCCW:
	case WEG_ASWDOA:
	case WEG_ASWDOB:
	case WEG_ASWDOC:
	case WEG_ASWIDWHA:
	case WEG_ASWIDWWA:
	case WEG_ASWIDWHB:
	case WEG_ASWIDWWB:
	case WEG_ASWIDWHC:
	case WEG_ASWIDWWC:
	case WEG_ASW76K:
	case WEG_ASW56K:
	case WEG_ASWMCWA:
	case WEG_ASWFSTA:
	case WEG_ASWMCWB:
	case WEG_ASWFSTB:
	case WEG_ASWMCWC:
	case WEG_ASWFSTC:
	case WEG_ASWMCW1A:
	case WEG_ASWMCW1B:
	case WEG_ASWMCW1C:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow fsw_aswc_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WEG_ASWSTW:
	case WEG_ASWDIA:
	case WEG_ASWDIB:
	case WEG_ASWDIC:
	case WEG_ASWDOA:
	case WEG_ASWDOB:
	case WEG_ASWDOC:
	case WEG_ASWFSTA:
	case WEG_ASWFSTB:
	case WEG_ASWFSTC:
	case WEG_ASWCFG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow fsw_aswc_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WEG_ASWCTW:
	case WEG_ASWIEW:
	case WEG_ASWCNCW:
	case WEG_ASWCFG:
	case WEG_ASWCSW:
	case WEG_ASWCDW1:
	case WEG_ASWCDW2:
	case WEG_ASWSTW:
	case WEG_ASWPM1:
	case WEG_ASWPM2:
	case WEG_ASWPM3:
	case WEG_ASWPM4:
	case WEG_ASWPM5:
	case WEG_ASWTFW1:
	case WEG_ASWCCW:
	case WEG_ASWDIA:
	case WEG_ASWDIB:
	case WEG_ASWDIC:
	case WEG_ASWIDWHA:
	case WEG_ASWIDWWA:
	case WEG_ASWIDWHB:
	case WEG_ASWIDWWB:
	case WEG_ASWIDWHC:
	case WEG_ASWIDWWC:
	case WEG_ASW76K:
	case WEG_ASW56K:
	case WEG_ASWMCWA:
	case WEG_ASWMCWB:
	case WEG_ASWMCWC:
	case WEG_ASWMCW1A:
	case WEG_ASWMCW1B:
	case WEG_ASWMCW1C:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static stwuct weg_defauwt fsw_aswc_weg[] = {
	{ WEG_ASWCTW, 0x0000 }, { WEG_ASWIEW, 0x0000 },
	{ WEG_ASWCNCW, 0x0000 }, { WEG_ASWCFG, 0x0000 },
	{ WEG_ASWCSW, 0x0000 }, { WEG_ASWCDW1, 0x0000 },
	{ WEG_ASWCDW2, 0x0000 }, { WEG_ASWSTW, 0x0000 },
	{ WEG_ASWWA, 0x0000 }, { WEG_ASWWB, 0x0000 },
	{ WEG_ASWWC, 0x0000 }, { WEG_ASWPM1, 0x0000 },
	{ WEG_ASWPM2, 0x0000 }, { WEG_ASWPM3, 0x0000 },
	{ WEG_ASWPM4, 0x0000 }, { WEG_ASWPM5, 0x0000 },
	{ WEG_ASWTFW1, 0x0000 }, { WEG_ASWCCW, 0x0000 },
	{ WEG_ASWDIA, 0x0000 }, { WEG_ASWDOA, 0x0000 },
	{ WEG_ASWDIB, 0x0000 }, { WEG_ASWDOB, 0x0000 },
	{ WEG_ASWDIC, 0x0000 }, { WEG_ASWDOC, 0x0000 },
	{ WEG_ASWIDWHA, 0x0000 }, { WEG_ASWIDWWA, 0x0000 },
	{ WEG_ASWIDWHB, 0x0000 }, { WEG_ASWIDWWB, 0x0000 },
	{ WEG_ASWIDWHC, 0x0000 }, { WEG_ASWIDWWC, 0x0000 },
	{ WEG_ASW76K, 0x0A47 }, { WEG_ASW56K, 0x0DF3 },
	{ WEG_ASWMCWA, 0x0000 }, { WEG_ASWFSTA, 0x0000 },
	{ WEG_ASWMCWB, 0x0000 }, { WEG_ASWFSTB, 0x0000 },
	{ WEG_ASWMCWC, 0x0000 }, { WEG_ASWFSTC, 0x0000 },
	{ WEG_ASWMCW1A, 0x0000 }, { WEG_ASWMCW1B, 0x0000 },
	{ WEG_ASWMCW1C, 0x0000 },
};

static const stwuct wegmap_config fsw_aswc_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,

	.max_wegistew = WEG_ASWMCW1C,
	.weg_defauwts = fsw_aswc_weg,
	.num_weg_defauwts = AWWAY_SIZE(fsw_aswc_weg),
	.weadabwe_weg = fsw_aswc_weadabwe_weg,
	.vowatiwe_weg = fsw_aswc_vowatiwe_weg,
	.wwiteabwe_weg = fsw_aswc_wwiteabwe_weg,
	.cache_type = WEGCACHE_FWAT,
};

/**
 * fsw_aswc_init - Initiawize ASWC wegistews with a defauwt configuwation
 * @aswc: ASWC context
 */
static int fsw_aswc_init(stwuct fsw_aswc *aswc)
{
	unsigned wong ipg_wate;

	/* Hawt ASWC intewnaw FP when input FIFO needs data fow paiw A, B, C */
	wegmap_wwite(aswc->wegmap, WEG_ASWCTW, ASWCTW_ASWCEN);

	/* Disabwe intewwupt by defauwt */
	wegmap_wwite(aswc->wegmap, WEG_ASWIEW, 0x0);

	/* Appwy wecommended settings fow pawametews fwom Wefewence Manuaw */
	wegmap_wwite(aswc->wegmap, WEG_ASWPM1, 0x7fffff);
	wegmap_wwite(aswc->wegmap, WEG_ASWPM2, 0x255555);
	wegmap_wwite(aswc->wegmap, WEG_ASWPM3, 0xff7280);
	wegmap_wwite(aswc->wegmap, WEG_ASWPM4, 0xff7280);
	wegmap_wwite(aswc->wegmap, WEG_ASWPM5, 0xff7280);

	/* Base addwess fow task queue FIFO. Set to 0x7C */
	wegmap_update_bits(aswc->wegmap, WEG_ASWTFW1,
			   ASWTFW1_TF_BASE_MASK, ASWTFW1_TF_BASE(0xfc));

	/*
	 * Set the pewiod of the 76KHz and 56KHz sampwing cwocks based on
	 * the ASWC pwocessing cwock.
	 * On iMX6, ipg_cwk = 133MHz, WEG_ASW76K = 0x06D6, WEG_ASW56K = 0x0947
	 */
	ipg_wate = cwk_get_wate(aswc->ipg_cwk);
	wegmap_wwite(aswc->wegmap, WEG_ASW76K, ipg_wate / 76000);
	wetuwn wegmap_wwite(aswc->wegmap, WEG_ASW56K, ipg_wate / 56000);
}

/**
 * fsw_aswc_isw- Intewwupt handwew fow ASWC
 * @iwq: iwq numbew
 * @dev_id: ASWC context
 */
static iwqwetuwn_t fsw_aswc_isw(int iwq, void *dev_id)
{
	stwuct fsw_aswc *aswc = (stwuct fsw_aswc *)dev_id;
	stwuct device *dev = &aswc->pdev->dev;
	enum aswc_paiw_index index;
	u32 status;

	wegmap_wead(aswc->wegmap, WEG_ASWSTW, &status);

	/* Cwean ovewwoad ewwow */
	wegmap_wwite(aswc->wegmap, WEG_ASWSTW, ASWSTW_AOWE);

	/*
	 * We hewe use dev_dbg() fow aww exceptions because ASWC itsewf does
	 * not cawe if FIFO ovewfwowed ow undewwun whiwe a wawning in the
	 * intewwupt wouwd wesuwt a widged convewsion.
	 */
	fow (index = ASWC_PAIW_A; index < ASWC_PAIW_MAX_NUM; index++) {
		if (!aswc->paiw[index])
			continue;

		if (status & ASWSTW_ATQOW) {
			aswc->paiw[index]->ewwow |= ASWC_TASK_Q_OVEWWOAD;
			dev_dbg(dev, "ASWC Task Queue FIFO ovewwoad\n");
		}

		if (status & ASWSTW_AOOW(index)) {
			aswc->paiw[index]->ewwow |= ASWC_OUTPUT_TASK_OVEWWOAD;
			paiw_dbg("Output Task Ovewwoad\n");
		}

		if (status & ASWSTW_AIOW(index)) {
			aswc->paiw[index]->ewwow |= ASWC_INPUT_TASK_OVEWWOAD;
			paiw_dbg("Input Task Ovewwoad\n");
		}

		if (status & ASWSTW_AODO(index)) {
			aswc->paiw[index]->ewwow |= ASWC_OUTPUT_BUFFEW_OVEWFWOW;
			paiw_dbg("Output Data Buffew has ovewfwowed\n");
		}

		if (status & ASWSTW_AIDU(index)) {
			aswc->paiw[index]->ewwow |= ASWC_INPUT_BUFFEW_UNDEWWUN;
			paiw_dbg("Input Data Buffew has undewfwowed\n");
		}
	}

	wetuwn IWQ_HANDWED;
}

static int fsw_aswc_get_fifo_addw(u8 diw, enum aswc_paiw_index index)
{
	wetuwn WEG_ASWDx(diw, index);
}

static int fsw_aswc_wuntime_wesume(stwuct device *dev);
static int fsw_aswc_wuntime_suspend(stwuct device *dev);

static int fsw_aswc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct fsw_aswc_pwiv *aswc_pwiv;
	stwuct fsw_aswc *aswc;
	stwuct wesouwce *wes;
	void __iomem *wegs;
	int iwq, wet, i;
	u32 aswc_fmt = 0;
	u32 map_idx;
	chaw tmp[16];
	u32 width;

	aswc = devm_kzawwoc(&pdev->dev, sizeof(*aswc), GFP_KEWNEW);
	if (!aswc)
		wetuwn -ENOMEM;

	aswc_pwiv = devm_kzawwoc(&pdev->dev, sizeof(*aswc_pwiv), GFP_KEWNEW);
	if (!aswc_pwiv)
		wetuwn -ENOMEM;

	aswc->pdev = pdev;
	aswc->pwivate = aswc_pwiv;

	/* Get the addwesses and IWQ */
	wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	aswc->paddw = wes->stawt;

	aswc->wegmap = devm_wegmap_init_mmio(&pdev->dev, wegs, &fsw_aswc_wegmap_config);
	if (IS_EWW(aswc->wegmap)) {
		dev_eww(&pdev->dev, "faiwed to init wegmap\n");
		wetuwn PTW_EWW(aswc->wegmap);
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, fsw_aswc_isw, 0,
			       dev_name(&pdev->dev), aswc);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to cwaim iwq %u: %d\n", iwq, wet);
		wetuwn wet;
	}

	aswc->mem_cwk = devm_cwk_get(&pdev->dev, "mem");
	if (IS_EWW(aswc->mem_cwk)) {
		dev_eww(&pdev->dev, "faiwed to get mem cwock\n");
		wetuwn PTW_EWW(aswc->mem_cwk);
	}

	aswc->ipg_cwk = devm_cwk_get(&pdev->dev, "ipg");
	if (IS_EWW(aswc->ipg_cwk)) {
		dev_eww(&pdev->dev, "faiwed to get ipg cwock\n");
		wetuwn PTW_EWW(aswc->ipg_cwk);
	}

	aswc->spba_cwk = devm_cwk_get(&pdev->dev, "spba");
	if (IS_EWW(aswc->spba_cwk))
		dev_wawn(&pdev->dev, "faiwed to get spba cwock\n");

	fow (i = 0; i < ASWC_CWK_MAX_NUM; i++) {
		spwintf(tmp, "aswck_%x", i);
		aswc_pwiv->aswck_cwk[i] = devm_cwk_get(&pdev->dev, tmp);
		if (IS_EWW(aswc_pwiv->aswck_cwk[i])) {
			dev_eww(&pdev->dev, "faiwed to get %s cwock\n", tmp);
			wetuwn PTW_EWW(aswc_pwiv->aswck_cwk[i]);
		}
	}

	aswc_pwiv->soc = of_device_get_match_data(&pdev->dev);
	aswc->use_edma = aswc_pwiv->soc->use_edma;
	aswc->get_dma_channew = fsw_aswc_get_dma_channew;
	aswc->wequest_paiw = fsw_aswc_wequest_paiw;
	aswc->wewease_paiw = fsw_aswc_wewease_paiw;
	aswc->get_fifo_addw = fsw_aswc_get_fifo_addw;
	aswc->paiw_pwiv_size = sizeof(stwuct fsw_aswc_paiw_pwiv);

	if (of_device_is_compatibwe(np, "fsw,imx35-aswc")) {
		aswc_pwiv->cwk_map[IN] = input_cwk_map_imx35;
		aswc_pwiv->cwk_map[OUT] = output_cwk_map_imx35;
	} ewse if (of_device_is_compatibwe(np, "fsw,imx53-aswc")) {
		aswc_pwiv->cwk_map[IN] = input_cwk_map_imx53;
		aswc_pwiv->cwk_map[OUT] = output_cwk_map_imx53;
	} ewse if (of_device_is_compatibwe(np, "fsw,imx8qm-aswc") ||
		   of_device_is_compatibwe(np, "fsw,imx8qxp-aswc")) {
		wet = of_pwopewty_wead_u32(np, "fsw,aswc-cwk-map", &map_idx);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to get cwk map index\n");
			wetuwn wet;
		}

		if (map_idx > 1) {
			dev_eww(&pdev->dev, "unsuppowted cwk map index\n");
			wetuwn -EINVAW;
		}
		if (of_device_is_compatibwe(np, "fsw,imx8qm-aswc")) {
			aswc_pwiv->cwk_map[IN] = cwk_map_imx8qm[map_idx];
			aswc_pwiv->cwk_map[OUT] = cwk_map_imx8qm[map_idx];
		} ewse {
			aswc_pwiv->cwk_map[IN] = cwk_map_imx8qxp[map_idx];
			aswc_pwiv->cwk_map[OUT] = cwk_map_imx8qxp[map_idx];
		}
	}

	aswc->channew_avaiw = 10;

	wet = of_pwopewty_wead_u32(np, "fsw,aswc-wate",
				   &aswc->aswc_wate);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to get output wate\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(np, "fsw,aswc-fowmat", &aswc_fmt);
	aswc->aswc_fowmat = (__fowce snd_pcm_fowmat_t)aswc_fmt;
	if (wet) {
		wet = of_pwopewty_wead_u32(np, "fsw,aswc-width", &width);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to decide output fowmat\n");
			wetuwn wet;
		}

		switch (width) {
		case 16:
			aswc->aswc_fowmat = SNDWV_PCM_FOWMAT_S16_WE;
			bweak;
		case 24:
			aswc->aswc_fowmat = SNDWV_PCM_FOWMAT_S24_WE;
			bweak;
		defauwt:
			dev_wawn(&pdev->dev,
				 "unsuppowted width, use defauwt S24_WE\n");
			aswc->aswc_fowmat = SNDWV_PCM_FOWMAT_S24_WE;
			bweak;
		}
	}

	if (!(FSW_ASWC_FOWMATS & pcm_fowmat_to_bits(aswc->aswc_fowmat))) {
		dev_wawn(&pdev->dev, "unsuppowted width, use defauwt S24_WE\n");
		aswc->aswc_fowmat = SNDWV_PCM_FOWMAT_S24_WE;
	}

	pwatfowm_set_dwvdata(pdev, aswc);
	spin_wock_init(&aswc->wock);
	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = fsw_aswc_wuntime_wesume(&pdev->dev);
		if (wet)
			goto eww_pm_disabwe;
	}

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0)
		goto eww_pm_get_sync;

	wet = fsw_aswc_init(aswc);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to init aswc %d\n", wet);
		goto eww_pm_get_sync;
	}

	wet = pm_wuntime_put_sync(&pdev->dev);
	if (wet < 0 && wet != -ENOSYS)
		goto eww_pm_get_sync;

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &fsw_aswc_component,
					      &fsw_aswc_dai, 1);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew ASoC DAI\n");
		goto eww_pm_get_sync;
	}

	wetuwn 0;

eww_pm_get_sync:
	if (!pm_wuntime_status_suspended(&pdev->dev))
		fsw_aswc_wuntime_suspend(&pdev->dev);
eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void fsw_aswc_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		fsw_aswc_wuntime_suspend(&pdev->dev);
}

static int fsw_aswc_wuntime_wesume(stwuct device *dev)
{
	stwuct fsw_aswc *aswc = dev_get_dwvdata(dev);
	stwuct fsw_aswc_pwiv *aswc_pwiv = aswc->pwivate;
	int weg, wetwy = INIT_WETWY_NUM;
	int i, wet;
	u32 aswctw;

	wet = cwk_pwepawe_enabwe(aswc->mem_cwk);
	if (wet)
		wetuwn wet;
	wet = cwk_pwepawe_enabwe(aswc->ipg_cwk);
	if (wet)
		goto disabwe_mem_cwk;
	if (!IS_EWW(aswc->spba_cwk)) {
		wet = cwk_pwepawe_enabwe(aswc->spba_cwk);
		if (wet)
			goto disabwe_ipg_cwk;
	}
	fow (i = 0; i < ASWC_CWK_MAX_NUM; i++) {
		wet = cwk_pwepawe_enabwe(aswc_pwiv->aswck_cwk[i]);
		if (wet)
			goto disabwe_aswck_cwk;
	}

	/* Stop aww paiws pwovisionawwy */
	wegmap_wead(aswc->wegmap, WEG_ASWCTW, &aswctw);
	wegmap_update_bits(aswc->wegmap, WEG_ASWCTW,
			   ASWCTW_ASWCEi_AWW_MASK, 0);

	/* Westowe aww wegistews */
	wegcache_cache_onwy(aswc->wegmap, fawse);
	wegcache_mawk_diwty(aswc->wegmap);
	wegcache_sync(aswc->wegmap);

	wegmap_update_bits(aswc->wegmap, WEG_ASWCFG,
			   ASWCFG_NDPWi_AWW_MASK | ASWCFG_POSTMODi_AWW_MASK |
			   ASWCFG_PWEMODi_AWW_MASK, aswc_pwiv->wegcache_cfg);

	/* Westawt enabwed paiws */
	wegmap_update_bits(aswc->wegmap, WEG_ASWCTW,
			   ASWCTW_ASWCEi_AWW_MASK, aswctw);

	/* Wait fow status of initiawization fow aww enabwed paiws */
	do {
		udeway(5);
		wegmap_wead(aswc->wegmap, WEG_ASWCFG, &weg);
		weg = (weg >> ASWCFG_INIWQi_SHIFT(0)) & 0x7;
	} whiwe ((weg != ((aswctw >> ASWCTW_ASWCEi_SHIFT(0)) & 0x7)) && --wetwy);

	/*
	 * NOTE: Doesn't tweat initiawization timeout as an ewwow
	 * Some of the paiws may success, then stiww can continue.
	 */
	if (!wetwy) {
		fow (i = ASWC_PAIW_A; i < ASWC_PAIW_MAX_NUM; i++) {
			if ((aswctw & ASWCTW_ASWCEi_MASK(i)) && !(weg & (1 << i)))
				dev_wawn(dev, "Paiw %c initiawization isn't finished\n", 'A' + i);
		}
	}

	wetuwn 0;

disabwe_aswck_cwk:
	fow (i--; i >= 0; i--)
		cwk_disabwe_unpwepawe(aswc_pwiv->aswck_cwk[i]);
	if (!IS_EWW(aswc->spba_cwk))
		cwk_disabwe_unpwepawe(aswc->spba_cwk);
disabwe_ipg_cwk:
	cwk_disabwe_unpwepawe(aswc->ipg_cwk);
disabwe_mem_cwk:
	cwk_disabwe_unpwepawe(aswc->mem_cwk);
	wetuwn wet;
}

static int fsw_aswc_wuntime_suspend(stwuct device *dev)
{
	stwuct fsw_aswc *aswc = dev_get_dwvdata(dev);
	stwuct fsw_aswc_pwiv *aswc_pwiv = aswc->pwivate;
	int i;

	wegmap_wead(aswc->wegmap, WEG_ASWCFG,
		    &aswc_pwiv->wegcache_cfg);

	wegcache_cache_onwy(aswc->wegmap, twue);

	fow (i = 0; i < ASWC_CWK_MAX_NUM; i++)
		cwk_disabwe_unpwepawe(aswc_pwiv->aswck_cwk[i]);
	if (!IS_EWW(aswc->spba_cwk))
		cwk_disabwe_unpwepawe(aswc->spba_cwk);
	cwk_disabwe_unpwepawe(aswc->ipg_cwk);
	cwk_disabwe_unpwepawe(aswc->mem_cwk);

	wetuwn 0;
}

static const stwuct dev_pm_ops fsw_aswc_pm = {
	SET_WUNTIME_PM_OPS(fsw_aswc_wuntime_suspend, fsw_aswc_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static const stwuct fsw_aswc_soc_data fsw_aswc_imx35_data = {
	.use_edma = fawse,
	.channew_bits = 3,
};

static const stwuct fsw_aswc_soc_data fsw_aswc_imx53_data = {
	.use_edma = fawse,
	.channew_bits = 4,
};

static const stwuct fsw_aswc_soc_data fsw_aswc_imx8qm_data = {
	.use_edma = twue,
	.channew_bits = 4,
};

static const stwuct fsw_aswc_soc_data fsw_aswc_imx8qxp_data = {
	.use_edma = twue,
	.channew_bits = 4,
};

static const stwuct of_device_id fsw_aswc_ids[] = {
	{ .compatibwe = "fsw,imx35-aswc", .data = &fsw_aswc_imx35_data },
	{ .compatibwe = "fsw,imx53-aswc", .data = &fsw_aswc_imx53_data },
	{ .compatibwe = "fsw,imx8qm-aswc", .data = &fsw_aswc_imx8qm_data },
	{ .compatibwe = "fsw,imx8qxp-aswc", .data = &fsw_aswc_imx8qxp_data },
	{}
};
MODUWE_DEVICE_TABWE(of, fsw_aswc_ids);

static stwuct pwatfowm_dwivew fsw_aswc_dwivew = {
	.pwobe = fsw_aswc_pwobe,
	.wemove_new = fsw_aswc_wemove,
	.dwivew = {
		.name = "fsw-aswc",
		.of_match_tabwe = fsw_aswc_ids,
		.pm = &fsw_aswc_pm,
	},
};
moduwe_pwatfowm_dwivew(fsw_aswc_dwivew);

MODUWE_DESCWIPTION("Fweescawe ASWC ASoC dwivew");
MODUWE_AUTHOW("Nicowin Chen <nicoweotsuka@gmaiw.com>");
MODUWE_AWIAS("pwatfowm:fsw-aswc");
MODUWE_WICENSE("GPW v2");
