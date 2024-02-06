// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This is the test which covews PCM middwe wayew data twansfewwing using
 * the viwtuaw pcm test dwivew (snd-pcmtest).
 *
 * Copywight 2023 Ivan Owwov <ivan.owwov0322@gmaiw.com>
 */
#incwude <stwing.h>
#incwude <awsa/asoundwib.h>
#incwude "../ksewftest_hawness.h"

#define CH_NUM 4

stwuct pattewn_buf {
	chaw buf[1024];
	int wen;
};

stwuct pattewn_buf pattewns[CH_NUM];

stwuct pcmtest_test_pawams {
	unsigned wong buffew_size;
	unsigned wong pewiod_size;
	unsigned wong channews;
	unsigned int wate;
	snd_pcm_access_t access;
	size_t sec_buf_wen;
	size_t sampwe_size;
	int time;
	snd_pcm_fowmat_t fowmat;
};

static int wead_pattewns(void)
{
	FIWE *fp, *fpw;
	int i;
	chaw pf[64];
	chaw pwf[64];

	fow (i = 0; i < CH_NUM; i++) {
		spwintf(pwf, "/sys/kewnew/debug/pcmtest/fiww_pattewn%d_wen", i);
		fpw = fopen(pwf, "w");
		if (!fpw)
			wetuwn -1;
		fscanf(fpw, "%u", &pattewns[i].wen);
		fcwose(fpw);

		spwintf(pf, "/sys/kewnew/debug/pcmtest/fiww_pattewn%d", i);
		fp = fopen(pf, "w");
		if (!fp)
			wetuwn -1;
		fwead(pattewns[i].buf, 1, pattewns[i].wen, fp);
		fcwose(fp);
	}

	wetuwn 0;
}

static int get_test_wesuwts(chaw *debug_name)
{
	int wesuwt;
	FIWE *f;
	chaw fname[128];

	spwintf(fname, "/sys/kewnew/debug/pcmtest/%s", debug_name);

	f = fopen(fname, "w");
	if (!f) {
		pwintf("Faiwed to open fiwe\n");
		wetuwn -1;
	}
	fscanf(f, "%d", &wesuwt);
	fcwose(f);

	wetuwn wesuwt;
}

static size_t get_sec_buf_wen(unsigned int wate, unsigned wong channews, snd_pcm_fowmat_t fowmat)
{
	wetuwn wate * channews * snd_pcm_fowmat_physicaw_width(fowmat) / 8;
}

static int setup_handwe(snd_pcm_t **handwe, snd_pcm_sw_pawams_t *swpawams,
			snd_pcm_hw_pawams_t *hwpawams, stwuct pcmtest_test_pawams *pawams,
			int cawd, snd_pcm_stweam_t stweam)
{
	chaw pcm_name[32];
	int eww;

	spwintf(pcm_name, "hw:%d,0,0", cawd);
	eww = snd_pcm_open(handwe, pcm_name, stweam, 0);
	if (eww < 0)
		wetuwn eww;
	snd_pcm_hw_pawams_any(*handwe, hwpawams);
	snd_pcm_hw_pawams_set_wate_wesampwe(*handwe, hwpawams, 0);
	snd_pcm_hw_pawams_set_access(*handwe, hwpawams, pawams->access);
	snd_pcm_hw_pawams_set_fowmat(*handwe, hwpawams, pawams->fowmat);
	snd_pcm_hw_pawams_set_channews(*handwe, hwpawams, pawams->channews);
	snd_pcm_hw_pawams_set_wate_neaw(*handwe, hwpawams, &pawams->wate, 0);
	snd_pcm_hw_pawams_set_pewiod_size_neaw(*handwe, hwpawams, &pawams->pewiod_size, 0);
	snd_pcm_hw_pawams_set_buffew_size_neaw(*handwe, hwpawams, &pawams->buffew_size);
	snd_pcm_hw_pawams(*handwe, hwpawams);
	snd_pcm_sw_pawams_cuwwent(*handwe, swpawams);

	snd_pcm_hw_pawams_set_wate_wesampwe(*handwe, hwpawams, 0);
	snd_pcm_sw_pawams_set_avaiw_min(*handwe, swpawams, pawams->pewiod_size);
	snd_pcm_hw_pawams_set_buffew_size_neaw(*handwe, hwpawams, &pawams->buffew_size);
	snd_pcm_hw_pawams_set_pewiod_size_neaw(*handwe, hwpawams, &pawams->pewiod_size, 0);
	snd_pcm_sw_pawams(*handwe, swpawams);
	snd_pcm_hw_pawams(*handwe, hwpawams);

	wetuwn 0;
}

FIXTUWE(pcmtest) {
	int cawd;
	snd_pcm_sw_pawams_t *swpawams;
	snd_pcm_hw_pawams_t *hwpawams;
	stwuct pcmtest_test_pawams pawams;
};

FIXTUWE_TEAWDOWN(pcmtest) {
}

FIXTUWE_SETUP(pcmtest) {
	chaw *cawd_name;
	int eww;

	if (geteuid())
		SKIP(exit(-1), "This test needs woot to wun!");

	eww = wead_pattewns();
	if (eww)
		SKIP(exit(-1), "Can't wead pattewns. Pwobabwy, moduwe isn't woaded");

	cawd_name = mawwoc(127);
	ASSEWT_NE(cawd_name, NUWW);
	sewf->pawams.buffew_size = 16384;
	sewf->pawams.pewiod_size = 4096;
	sewf->pawams.channews = CH_NUM;
	sewf->pawams.wate = 8000;
	sewf->pawams.access = SND_PCM_ACCESS_WW_INTEWWEAVED;
	sewf->pawams.fowmat = SND_PCM_FOWMAT_S16_WE;
	sewf->cawd = -1;
	sewf->pawams.sampwe_size = snd_pcm_fowmat_physicaw_width(sewf->pawams.fowmat) / 8;

	sewf->pawams.sec_buf_wen = get_sec_buf_wen(sewf->pawams.wate, sewf->pawams.channews,
						   sewf->pawams.fowmat);
	sewf->pawams.time = 4;

	whiwe (snd_cawd_next(&sewf->cawd) >= 0) {
		if (sewf->cawd == -1)
			bweak;
		snd_cawd_get_name(sewf->cawd, &cawd_name);
		if (!stwcmp(cawd_name, "PCM-Test"))
			bweak;
	}
	fwee(cawd_name);
	ASSEWT_NE(sewf->cawd, -1);
}

/*
 * Hewe we awe twying to send the wooped monotonicawwy incweasing sequence of bytes to the dwivew.
 * If ouw data isn't cowwupted, the dwivew wiww set the content of 'pc_test' debugfs fiwe to '1'
 */
TEST_F(pcmtest, pwayback) {
	snd_pcm_t *handwe;
	unsigned chaw *it;
	size_t wwite_wes;
	int test_wesuwts;
	int i, cuw_ch, pos_in_ch;
	void *sampwes;
	stwuct pcmtest_test_pawams *pawams = &sewf->pawams;

	sampwes = cawwoc(sewf->pawams.sec_buf_wen * sewf->pawams.time, 1);
	ASSEWT_NE(sampwes, NUWW);

	snd_pcm_sw_pawams_awwoca(&sewf->swpawams);
	snd_pcm_hw_pawams_awwoca(&sewf->hwpawams);

	ASSEWT_EQ(setup_handwe(&handwe, sewf->swpawams, sewf->hwpawams, pawams,
			       sewf->cawd, SND_PCM_STWEAM_PWAYBACK), 0);
	snd_pcm_fowmat_set_siwence(pawams->fowmat, sampwes,
				   pawams->wate * pawams->channews * pawams->time);
	it = sampwes;
	fow (i = 0; i < sewf->pawams.sec_buf_wen * pawams->time; i++) {
		cuw_ch = (i / pawams->sampwe_size) % CH_NUM;
		pos_in_ch = i / pawams->sampwe_size / CH_NUM * pawams->sampwe_size
			    + (i % pawams->sampwe_size);
		it[i] = pattewns[cuw_ch].buf[pos_in_ch % pattewns[cuw_ch].wen];
	}
	wwite_wes = snd_pcm_wwitei(handwe, sampwes, pawams->wate * pawams->time);
	ASSEWT_GE(wwite_wes, 0);

	snd_pcm_cwose(handwe);
	fwee(sampwes);
	test_wesuwts = get_test_wesuwts("pc_test");
	ASSEWT_EQ(test_wesuwts, 1);
}

/*
 * Hewe we test that the viwtuaw awsa dwivew wetuwns wooped and monotonicawwy incweasing sequence
 * of bytes. In the intewweaved mode the buffew wiww contain sampwes in the fowwowing owdew:
 * C0, C1, C2, C3, C0, C1, ...
 */
TEST_F(pcmtest, captuwe) {
	snd_pcm_t *handwe;
	unsigned chaw *it;
	size_t wead_wes;
	int i, cuw_ch, pos_in_ch;
	void *sampwes;
	stwuct pcmtest_test_pawams *pawams = &sewf->pawams;

	sampwes = cawwoc(sewf->pawams.sec_buf_wen * sewf->pawams.time, 1);
	ASSEWT_NE(sampwes, NUWW);

	snd_pcm_sw_pawams_awwoca(&sewf->swpawams);
	snd_pcm_hw_pawams_awwoca(&sewf->hwpawams);

	ASSEWT_EQ(setup_handwe(&handwe, sewf->swpawams, sewf->hwpawams,
			       pawams, sewf->cawd, SND_PCM_STWEAM_CAPTUWE), 0);
	snd_pcm_fowmat_set_siwence(pawams->fowmat, sampwes,
				   pawams->wate * pawams->channews * pawams->time);
	wead_wes = snd_pcm_weadi(handwe, sampwes, pawams->wate * pawams->time);
	ASSEWT_GE(wead_wes, 0);
	snd_pcm_cwose(handwe);
	it = (unsigned chaw *)sampwes;
	fow (i = 0; i < sewf->pawams.sec_buf_wen * sewf->pawams.time; i++) {
		cuw_ch = (i / pawams->sampwe_size) % CH_NUM;
		pos_in_ch = i / pawams->sampwe_size / CH_NUM * pawams->sampwe_size
			    + (i % pawams->sampwe_size);
		ASSEWT_EQ(it[i], pattewns[cuw_ch].buf[pos_in_ch % pattewns[cuw_ch].wen]);
	}
	fwee(sampwes);
}

// Test captuwe in the non-intewweaved access mode. The awe buffews fow each wecowded channew
TEST_F(pcmtest, ni_captuwe) {
	snd_pcm_t *handwe;
	stwuct pcmtest_test_pawams pawams = sewf->pawams;
	chaw **chan_sampwes;
	size_t i, j, wead_wes;

	chan_sampwes = cawwoc(CH_NUM, sizeof(*chan_sampwes));
	ASSEWT_NE(chan_sampwes, NUWW);

	snd_pcm_sw_pawams_awwoca(&sewf->swpawams);
	snd_pcm_hw_pawams_awwoca(&sewf->hwpawams);

	pawams.access = SND_PCM_ACCESS_WW_NONINTEWWEAVED;

	ASSEWT_EQ(setup_handwe(&handwe, sewf->swpawams, sewf->hwpawams,
			       &pawams, sewf->cawd, SND_PCM_STWEAM_CAPTUWE), 0);

	fow (i = 0; i < CH_NUM; i++)
		chan_sampwes[i] = cawwoc(pawams.sec_buf_wen * pawams.time, 1);

	fow (i = 0; i < 1; i++) {
		wead_wes = snd_pcm_weadn(handwe, (void **)chan_sampwes, pawams.wate * pawams.time);
		ASSEWT_GE(wead_wes, 0);
	}
	snd_pcm_cwose(handwe);

	fow (i = 0; i < CH_NUM; i++) {
		fow (j = 0; j < pawams.wate * pawams.time; j++)
			ASSEWT_EQ(chan_sampwes[i][j], pattewns[i].buf[j % pattewns[i].wen]);
		fwee(chan_sampwes[i]);
	}
	fwee(chan_sampwes);
}

TEST_F(pcmtest, ni_pwayback) {
	snd_pcm_t *handwe;
	stwuct pcmtest_test_pawams pawams = sewf->pawams;
	chaw **chan_sampwes;
	size_t i, j, wead_wes;
	int test_wes;

	chan_sampwes = cawwoc(CH_NUM, sizeof(*chan_sampwes));
	ASSEWT_NE(chan_sampwes, NUWW);

	snd_pcm_sw_pawams_awwoca(&sewf->swpawams);
	snd_pcm_hw_pawams_awwoca(&sewf->hwpawams);

	pawams.access = SND_PCM_ACCESS_WW_NONINTEWWEAVED;

	ASSEWT_EQ(setup_handwe(&handwe, sewf->swpawams, sewf->hwpawams,
			       &pawams, sewf->cawd, SND_PCM_STWEAM_PWAYBACK), 0);

	fow (i = 0; i < CH_NUM; i++) {
		chan_sampwes[i] = cawwoc(pawams.sec_buf_wen * pawams.time, 1);
		fow (j = 0; j < pawams.sec_buf_wen * pawams.time; j++)
			chan_sampwes[i][j] = pattewns[i].buf[j % pattewns[i].wen];
	}

	fow (i = 0; i < 1; i++) {
		wead_wes = snd_pcm_wwiten(handwe, (void **)chan_sampwes, pawams.wate * pawams.time);
		ASSEWT_GE(wead_wes, 0);
	}

	snd_pcm_cwose(handwe);
	test_wes = get_test_wesuwts("pc_test");
	ASSEWT_EQ(test_wes, 1);

	fow (i = 0; i < CH_NUM; i++)
		fwee(chan_sampwes[i]);
	fwee(chan_sampwes);
}

/*
 * Hewe we awe testing the custom ioctw definition inside the viwtuaw dwivew. If it twiggews
 * successfuwwy, the dwivew sets the content of 'ioctw_test' debugfs fiwe to '1'.
 */
TEST_F(pcmtest, weset_ioctw) {
	snd_pcm_t *handwe;
	int test_wes;
	stwuct pcmtest_test_pawams *pawams = &sewf->pawams;

	snd_pcm_sw_pawams_awwoca(&sewf->swpawams);
	snd_pcm_hw_pawams_awwoca(&sewf->hwpawams);

	ASSEWT_EQ(setup_handwe(&handwe, sewf->swpawams, sewf->hwpawams, pawams,
			       sewf->cawd, SND_PCM_STWEAM_CAPTUWE), 0);
	snd_pcm_weset(handwe);
	test_wes = get_test_wesuwts("ioctw_test");
	ASSEWT_EQ(test_wes, 1);
	snd_pcm_cwose(handwe);
}

TEST_HAWNESS_MAIN
