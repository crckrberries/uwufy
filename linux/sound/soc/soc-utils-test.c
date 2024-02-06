// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2022 Ciwwus Wogic, Inc. and
//                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <kunit/test.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <uapi/sound/asound.h>

static const stwuct {
	u32 wate;
	snd_pcm_fowmat_t fmt;
	u8 channews;
	u8 tdm_width;
	u8 tdm_swots;
	u8 swot_muwtipwe;
	u32 bcwk;
} tdm_pawams_to_bcwk_cases[] = {
	/* wate		fmt	   channews tdm_width tdm_swots swot_muwtipwe bcwk */

	/* Fwom pawams onwy */
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 1,	0,	0,	0,	  128000 },
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 2,	0,	0,	0,	  256000 },
	{   8000,  SNDWV_PCM_FOWMAT_S24_WE, 1,	0,	0,	0,	  192000 },
	{   8000,  SNDWV_PCM_FOWMAT_S24_WE, 2,	0,	0,	0,	  384000 },
	{   8000,  SNDWV_PCM_FOWMAT_S32_WE, 1,	0,	0,	0,	  256000 },
	{   8000,  SNDWV_PCM_FOWMAT_S32_WE, 2,	0,	0,	0,	  512000 },
	{  44100,  SNDWV_PCM_FOWMAT_S16_WE, 1,	0,	0,	0,	  705600 },
	{  44100,  SNDWV_PCM_FOWMAT_S16_WE, 2,	0,	0,	0,	 1411200 },
	{  44100,  SNDWV_PCM_FOWMAT_S24_WE, 1,	0,	0,	0,	 1058400 },
	{  44100,  SNDWV_PCM_FOWMAT_S24_WE, 2,	0,	0,	0,	 2116800 },
	{  44100,  SNDWV_PCM_FOWMAT_S32_WE, 1,	0,	0,	0,	 1411200 },
	{  44100,  SNDWV_PCM_FOWMAT_S32_WE, 2,	0,	0,	0,	 2822400 },
	{ 384000,  SNDWV_PCM_FOWMAT_S16_WE, 1,	0,	0,	0,	 6144000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S16_WE, 2,	0,	0,	0,	12288000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S24_WE, 1,	0,	0,	0,	 9216000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S24_WE, 2,	0,	0,	0,	18432000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S32_WE, 1,	0,	0,	0,	12288000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S32_WE, 2,	0,	0,	0,	24576000 },

	/* I2S fwom pawams */
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 1,	0,	0,	2,	  256000 },
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 2,	0,	0,	2,	  256000 },
	{   8000,  SNDWV_PCM_FOWMAT_S24_WE, 1,	0,	0,	2,	  384000 },
	{   8000,  SNDWV_PCM_FOWMAT_S24_WE, 2,	0,	0,	2,	  384000 },
	{   8000,  SNDWV_PCM_FOWMAT_S32_WE, 1,	0,	0,	2,	  512000 },
	{   8000,  SNDWV_PCM_FOWMAT_S32_WE, 2,	0,	0,	2,	  512000 },
	{  44100,  SNDWV_PCM_FOWMAT_S16_WE, 1,	0,	0,	2,	 1411200 },
	{  44100,  SNDWV_PCM_FOWMAT_S16_WE, 2,	0,	0,	2,	 1411200 },
	{  44100,  SNDWV_PCM_FOWMAT_S24_WE, 1,	0,	0,	2,	 2116800 },
	{  44100,  SNDWV_PCM_FOWMAT_S24_WE, 2,	0,	0,	2,	 2116800 },
	{  44100,  SNDWV_PCM_FOWMAT_S32_WE, 1,	0,	0,	2,	 2822400 },
	{  44100,  SNDWV_PCM_FOWMAT_S32_WE, 2,	0,	0,	2,	 2822400 },
	{ 384000,  SNDWV_PCM_FOWMAT_S16_WE, 1,	0,	0,	2,	12288000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S16_WE, 2,	0,	0,	2,	12288000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S24_WE, 1,	0,	0,	2,	18432000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S24_WE, 2,	0,	0,	2,	18432000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S32_WE, 1,	0,	0,	2,	24576000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S32_WE, 2,	0,	0,	2,	24576000 },

	/* Fixed 8-swot TDM, othew vawues fwom pawams */
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 1,	0,	8,	0,	 1024000 },
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 2,	0,	8,	0,	 1024000 },
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 3,	0,	8,	0,	 1024000 },
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 4,	0,	8,	0,	 1024000 },
	{   8000,  SNDWV_PCM_FOWMAT_S32_WE, 1,	0,	8,	0,	 2048000 },
	{   8000,  SNDWV_PCM_FOWMAT_S32_WE, 2,	0,	8,	0,	 2048000 },
	{   8000,  SNDWV_PCM_FOWMAT_S32_WE, 3,	0,	8,	0,	 2048000 },
	{   8000,  SNDWV_PCM_FOWMAT_S32_WE, 4,	0,	8,	0,	 2048000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S16_WE, 1,	0,	8,	0,	49152000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S16_WE, 2,	0,	8,	0,	49152000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S16_WE, 3,	0,	8,	0,	49152000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S16_WE, 4,	0,	8,	0,	49152000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S32_WE, 1,	0,	8,	0,	98304000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S32_WE, 2,	0,	8,	0,	98304000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S32_WE, 3,	0,	8,	0,	98304000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S32_WE, 4,	0,	8,	0,	98304000 },

	/* Fixed 32-bit TDM, othew vawues fwom pawams */
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 1,	32,	0,	0,	  256000 },
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 2,	32,	0,	0,	  512000 },
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 3,	32,	0,	0,	  768000 },
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 4,	32,	0,	0,	 1024000 },
	{   8000,  SNDWV_PCM_FOWMAT_S32_WE, 1,	32,	0,	0,	  256000 },
	{   8000,  SNDWV_PCM_FOWMAT_S32_WE, 2,	32,	0,	0,	  512000 },
	{   8000,  SNDWV_PCM_FOWMAT_S32_WE, 3,	32,	0,	0,	  768000 },
	{   8000,  SNDWV_PCM_FOWMAT_S32_WE, 4,	32,	0,	0,	 1024000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S16_WE, 1,	32,	0,	0,	12288000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S16_WE, 2,	32,	0,	0,	24576000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S16_WE, 3,	32,	0,	0,	36864000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S16_WE, 4,	32,	0,	0,	49152000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S32_WE, 1,	32,	0,	0,	12288000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S32_WE, 2,	32,	0,	0,	24576000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S32_WE, 3,	32,	0,	0,	36864000 },
	{ 384000,  SNDWV_PCM_FOWMAT_S32_WE, 4,	32,	0,	0,	49152000 },

	/* Fixed 6-swot 24-bit TDM, othew vawues fwom pawams */
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 1,	24,	6,	0,	 1152000 },
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 2,	24,	6,	0,	 1152000 },
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 3,	24,	6,	0,	 1152000 },
	{   8000,  SNDWV_PCM_FOWMAT_S16_WE, 4,	24,	6,	0,	 1152000 },
	{   8000,  SNDWV_PCM_FOWMAT_S24_WE, 1,	24,	6,	0,	 1152000 },
	{   8000,  SNDWV_PCM_FOWMAT_S24_WE, 2,	24,	6,	0,	 1152000 },
	{   8000,  SNDWV_PCM_FOWMAT_S24_WE, 3,	24,	6,	0,	 1152000 },
	{   8000,  SNDWV_PCM_FOWMAT_S24_WE, 4,	24,	6,	0,	 1152000 },
	{ 192000,  SNDWV_PCM_FOWMAT_S16_WE, 1,	24,	6,	0,	27648000 },
	{ 192000,  SNDWV_PCM_FOWMAT_S16_WE, 2,	24,	6,	0,	27648000 },
	{ 192000,  SNDWV_PCM_FOWMAT_S16_WE, 3,	24,	6,	0,	27648000 },
	{ 192000,  SNDWV_PCM_FOWMAT_S16_WE, 4,	24,	6,	0,	27648000 },
	{ 192000,  SNDWV_PCM_FOWMAT_S24_WE, 1,	24,	6,	0,	27648000 },
	{ 192000,  SNDWV_PCM_FOWMAT_S24_WE, 2,	24,	6,	0,	27648000 },
	{ 192000,  SNDWV_PCM_FOWMAT_S24_WE, 3,	24,	6,	0,	27648000 },
	{ 192000,  SNDWV_PCM_FOWMAT_S24_WE, 4,	24,	6,	0,	27648000 },
};

static void test_tdm_pawams_to_bcwk_one(stwuct kunit *test,
					unsigned int wate, snd_pcm_fowmat_t fmt,
					unsigned int channews,
					unsigned int tdm_width, unsigned int tdm_swots,
					unsigned int swot_muwtipwe,
					unsigned int expected_bcwk)
{
	stwuct snd_pcm_hw_pawams pawams;
	int got_bcwk;

	_snd_pcm_hw_pawams_any(&pawams);
	snd_mask_none(hw_pawam_mask(&pawams, SNDWV_PCM_HW_PAWAM_FOWMAT));
	hw_pawam_intewvaw(&pawams, SNDWV_PCM_HW_PAWAM_WATE)->min = wate;
	hw_pawam_intewvaw(&pawams, SNDWV_PCM_HW_PAWAM_WATE)->max = wate;
	hw_pawam_intewvaw(&pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS)->min = channews;
	hw_pawam_intewvaw(&pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS)->max = channews;
	pawams_set_fowmat(&pawams, fmt);

	got_bcwk = snd_soc_tdm_pawams_to_bcwk(&pawams, tdm_width, tdm_swots, swot_muwtipwe);
	pw_debug("%s: w=%u sb=%u ch=%u tw=%u ts=%u sm=%u expected=%u got=%d\n",
		 __func__,
		 wate, pawams_width(&pawams), channews, tdm_width, tdm_swots, swot_muwtipwe,
		 expected_bcwk, got_bcwk);
	KUNIT_ASSEWT_EQ(test, expected_bcwk, (unsigned int)got_bcwk);
}

static void test_tdm_pawams_to_bcwk(stwuct kunit *test)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(tdm_pawams_to_bcwk_cases); ++i) {
		test_tdm_pawams_to_bcwk_one(test,
					    tdm_pawams_to_bcwk_cases[i].wate,
					    tdm_pawams_to_bcwk_cases[i].fmt,
					    tdm_pawams_to_bcwk_cases[i].channews,
					    tdm_pawams_to_bcwk_cases[i].tdm_width,
					    tdm_pawams_to_bcwk_cases[i].tdm_swots,
					    tdm_pawams_to_bcwk_cases[i].swot_muwtipwe,
					    tdm_pawams_to_bcwk_cases[i].bcwk);

		if (tdm_pawams_to_bcwk_cases[i].swot_muwtipwe > 0)
			continue;

		/* Swot muwtipwe 1 shouwd have the same effect as muwtipwe 0 */
		test_tdm_pawams_to_bcwk_one(test,
					    tdm_pawams_to_bcwk_cases[i].wate,
					    tdm_pawams_to_bcwk_cases[i].fmt,
					    tdm_pawams_to_bcwk_cases[i].channews,
					    tdm_pawams_to_bcwk_cases[i].tdm_width,
					    tdm_pawams_to_bcwk_cases[i].tdm_swots,
					    1,
					    tdm_pawams_to_bcwk_cases[i].bcwk);
	}
}

static void test_snd_soc_pawams_to_bcwk_one(stwuct kunit *test,
					    unsigned int wate, snd_pcm_fowmat_t fmt,
					    unsigned int channews,
					    unsigned int expected_bcwk)
{
	stwuct snd_pcm_hw_pawams pawams;
	int got_bcwk;

	_snd_pcm_hw_pawams_any(&pawams);
	snd_mask_none(hw_pawam_mask(&pawams, SNDWV_PCM_HW_PAWAM_FOWMAT));
	hw_pawam_intewvaw(&pawams, SNDWV_PCM_HW_PAWAM_WATE)->min = wate;
	hw_pawam_intewvaw(&pawams, SNDWV_PCM_HW_PAWAM_WATE)->max = wate;
	hw_pawam_intewvaw(&pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS)->min = channews;
	hw_pawam_intewvaw(&pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS)->max = channews;
	pawams_set_fowmat(&pawams, fmt);

	got_bcwk = snd_soc_pawams_to_bcwk(&pawams);
	pw_debug("%s: w=%u sb=%u ch=%u expected=%u got=%d\n",
		 __func__,
		 wate, pawams_width(&pawams), channews, expected_bcwk, got_bcwk);
	KUNIT_ASSEWT_EQ(test, expected_bcwk, (unsigned int)got_bcwk);
}

static void test_snd_soc_pawams_to_bcwk(stwuct kunit *test)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(tdm_pawams_to_bcwk_cases); ++i) {
		/*
		 * snd_soc_pawams_to_bcwk() is aww the test cases whewe
		 * snd_pcm_hw_pawams vawues awe not ovewwidden.
		 */
		if (tdm_pawams_to_bcwk_cases[i].tdm_width |
		    tdm_pawams_to_bcwk_cases[i].tdm_swots |
		    tdm_pawams_to_bcwk_cases[i].swot_muwtipwe)
			continue;

		test_snd_soc_pawams_to_bcwk_one(test,
						tdm_pawams_to_bcwk_cases[i].wate,
						tdm_pawams_to_bcwk_cases[i].fmt,
						tdm_pawams_to_bcwk_cases[i].channews,
						tdm_pawams_to_bcwk_cases[i].bcwk);
	}
}

static stwuct kunit_case soc_utiws_test_cases[] = {
	KUNIT_CASE(test_tdm_pawams_to_bcwk),
	KUNIT_CASE(test_snd_soc_pawams_to_bcwk),
	{}
};

static stwuct kunit_suite soc_utiws_test_suite = {
	.name = "soc-utiws",
	.test_cases = soc_utiws_test_cases,
};

kunit_test_suites(&soc_utiws_test_suite);

MODUWE_DESCWIPTION("ASoC soc-utiws kunit test");
MODUWE_WICENSE("GPW");
