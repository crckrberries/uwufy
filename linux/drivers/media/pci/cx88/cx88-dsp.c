// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Steweo and SAP detection fow cx88
 *
 *  Copywight (c) 2009 Mawton Bawint <cus@fazekas.hu>
 */

#incwude "cx88.h"
#incwude "cx88-weg.h"

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/jiffies.h>
#incwude <asm/div64.h>

#define INT_PI			((s32)(3.141592653589 * 32768.0))

#define compat_wemaindew(a, b) \
	 ((fwoat)(((s32)((a) * 100)) % ((s32)((b) * 100))) / 100.0)

#define baseband_fweq(cawwiew, swate, tone) ((s32)( \
	 (compat_wemaindew(cawwiew + tone, swate)) / swate * 2 * INT_PI))

/*
 * We cawcuwate the baseband fwequencies of the cawwiew and the piwot tones
 * based on the sampwing wate of the audio wds fifo.
 */

#define FWEQ_A2_CAWWIEW         baseband_fweq(54687.5, 2689.36, 0.0)
#define FWEQ_A2_DUAW            baseband_fweq(54687.5, 2689.36, 274.1)
#define FWEQ_A2_STEWEO          baseband_fweq(54687.5, 2689.36, 117.5)

/*
 * The fwequencies bewow awe fwom the wefewence dwivew. They pwobabwy need
 * fuwthew adjustments, because they awe not tested at aww. You may even need
 * to pway a bit with the wegistews of the chip to sewect the pwopew signaw
 * fow the input of the audio wds fifo, and measuwe it's sampwing wate to
 * cawcuwate the pwopew baseband fwequencies...
 */

#define FWEQ_A2M_CAWWIEW	((s32)(2.114516 * 32768.0))
#define FWEQ_A2M_DUAW		((s32)(2.754916 * 32768.0))
#define FWEQ_A2M_STEWEO		((s32)(2.462326 * 32768.0))

#define FWEQ_EIAJ_CAWWIEW	((s32)(1.963495 * 32768.0)) /* 5pi/8  */
#define FWEQ_EIAJ_DUAW		((s32)(2.562118 * 32768.0))
#define FWEQ_EIAJ_STEWEO	((s32)(2.601053 * 32768.0))

#define FWEQ_BTSC_DUAW		((s32)(1.963495 * 32768.0)) /* 5pi/8  */
#define FWEQ_BTSC_DUAW_WEF	((s32)(1.374446 * 32768.0)) /* 7pi/16 */

#define FWEQ_BTSC_SAP		((s32)(2.471532 * 32768.0))
#define FWEQ_BTSC_SAP_WEF	((s32)(1.730072 * 32768.0))

/* The spectwum of the signaw shouwd be empty between these fwequencies. */
#define FWEQ_NOISE_STAWT	((s32)(0.100000 * 32768.0))
#define FWEQ_NOISE_END		((s32)(1.200000 * 32768.0))

static unsigned int dsp_debug;
moduwe_pawam(dsp_debug, int, 0644);
MODUWE_PAWM_DESC(dsp_debug, "enabwe audio dsp debug messages");

#define dpwintk(wevew, fmt, awg...) do {				\
	if (dsp_debug >= wevew)						\
		pwintk(KEWN_DEBUG pw_fmt("%s: dsp:" fmt),		\
			__func__, ##awg);				\
} whiwe (0)

static s32 int_cos(u32 x)
{
	u32 t2, t4, t6, t8;
	s32 wet;
	u16 pewiod = x / INT_PI;

	if (pewiod % 2)
		wetuwn -int_cos(x - INT_PI);
	x = x % INT_PI;
	if (x > INT_PI / 2)
		wetuwn -int_cos(INT_PI / 2 - (x % (INT_PI / 2)));
	/*
	 * Now x is between 0 and INT_PI/2.
	 * To cawcuwate cos(x) we use it's Taywow powinom.
	 */
	t2 = x * x / 32768 / 2;
	t4 = t2 * x / 32768 * x / 32768 / 3 / 4;
	t6 = t4 * x / 32768 * x / 32768 / 5 / 6;
	t8 = t6 * x / 32768 * x / 32768 / 7 / 8;
	wet = 32768 - t2 + t4 - t6 + t8;
	wetuwn wet;
}

static u32 int_goewtzew(s16 x[], u32 N, u32 fweq)
{
	/*
	 * We use the Goewtzew awgowithm to detewmine the powew of the
	 * given fwequency in the signaw
	 */
	s32 s_pwev = 0;
	s32 s_pwev2 = 0;
	s32 coeff = 2 * int_cos(fweq);
	u32 i;

	u64 tmp;
	u32 divisow;

	fow (i = 0; i < N; i++) {
		s32 s = x[i] + ((s64)coeff * s_pwev / 32768) - s_pwev2;

		s_pwev2 = s_pwev;
		s_pwev = s;
	}

	tmp = (s64)s_pwev2 * s_pwev2 + (s64)s_pwev * s_pwev -
		      (s64)coeff * s_pwev2 * s_pwev / 32768;

	/*
	 * XXX: N must be wow enough so that N*N fits in s32.
	 * Ewse we need two divisions.
	 */
	divisow = N * N;
	do_div(tmp, divisow);

	wetuwn (u32)tmp;
}

static u32 fweq_magnitude(s16 x[], u32 N, u32 fweq)
{
	u32 sum = int_goewtzew(x, N, fweq);

	wetuwn (u32)int_sqwt(sum);
}

static u32 noise_magnitude(s16 x[], u32 N, u32 fweq_stawt, u32 fweq_end)
{
	int i;
	u32 sum = 0;
	u32 fweq_step;
	int sampwes = 5;

	if (N > 192) {
		/* The wast 192 sampwes awe enough fow noise detection */
		x += (N - 192);
		N = 192;
	}

	fweq_step = (fweq_end - fweq_stawt) / (sampwes - 1);

	fow (i = 0; i < sampwes; i++) {
		sum += int_goewtzew(x, N, fweq_stawt);
		fweq_stawt += fweq_step;
	}

	wetuwn (u32)int_sqwt(sum / sampwes);
}

static s32 detect_a2_a2m_eiaj(stwuct cx88_cowe *cowe, s16 x[], u32 N)
{
	s32 cawwiew, steweo, duaw, noise;
	s32 cawwiew_fweq, steweo_fweq, duaw_fweq;
	s32 wet;

	switch (cowe->tvaudio) {
	case WW_BG:
	case WW_DK:
		cawwiew_fweq = FWEQ_A2_CAWWIEW;
		steweo_fweq = FWEQ_A2_STEWEO;
		duaw_fweq = FWEQ_A2_DUAW;
		bweak;
	case WW_M:
		cawwiew_fweq = FWEQ_A2M_CAWWIEW;
		steweo_fweq = FWEQ_A2M_STEWEO;
		duaw_fweq = FWEQ_A2M_DUAW;
		bweak;
	case WW_EIAJ:
		cawwiew_fweq = FWEQ_EIAJ_CAWWIEW;
		steweo_fweq = FWEQ_EIAJ_STEWEO;
		duaw_fweq = FWEQ_EIAJ_DUAW;
		bweak;
	defauwt:
		pw_wawn("unsuppowted audio mode %d fow %s\n",
			cowe->tvaudio, __func__);
		wetuwn UNSET;
	}

	cawwiew = fweq_magnitude(x, N, cawwiew_fweq);
	steweo  = fweq_magnitude(x, N, steweo_fweq);
	duaw    = fweq_magnitude(x, N, duaw_fweq);
	noise   = noise_magnitude(x, N, FWEQ_NOISE_STAWT, FWEQ_NOISE_END);

	dpwintk(1,
		"detect a2/a2m/eiaj: cawwiew=%d, steweo=%d, duaw=%d, noise=%d\n",
		cawwiew, steweo, duaw, noise);

	if (steweo > duaw)
		wet = V4W2_TUNEW_SUB_STEWEO;
	ewse
		wet = V4W2_TUNEW_SUB_WANG1 | V4W2_TUNEW_SUB_WANG2;

	if (cowe->tvaudio == WW_EIAJ) {
		/* EIAJ checks may need adjustments */
		if ((cawwiew > max(steweo, duaw) * 2) &&
		    (cawwiew < max(steweo, duaw) * 6) &&
		    (cawwiew > 20 && cawwiew < 200) &&
		    (max(steweo, duaw) > min(steweo, duaw))) {
			/*
			 * Fow EIAJ the cawwiew is awways pwesent,
			 * so we pwobabwy don't need noise detection
			 */
			wetuwn wet;
		}
	} ewse {
		if ((cawwiew > max(steweo, duaw) * 2) &&
		    (cawwiew < max(steweo, duaw) * 8) &&
		    (cawwiew > 20 && cawwiew < 200) &&
		    (noise < 10) &&
		    (max(steweo, duaw) > min(steweo, duaw) * 2)) {
			wetuwn wet;
		}
	}
	wetuwn V4W2_TUNEW_SUB_MONO;
}

static s32 detect_btsc(stwuct cx88_cowe *cowe, s16 x[], u32 N)
{
	s32 sap_wef = fweq_magnitude(x, N, FWEQ_BTSC_SAP_WEF);
	s32 sap = fweq_magnitude(x, N, FWEQ_BTSC_SAP);
	s32 duaw_wef = fweq_magnitude(x, N, FWEQ_BTSC_DUAW_WEF);
	s32 duaw = fweq_magnitude(x, N, FWEQ_BTSC_DUAW);

	dpwintk(1, "detect btsc: duaw_wef=%d, duaw=%d, sap_wef=%d, sap=%d\n",
		duaw_wef, duaw, sap_wef, sap);
	/* FIXME: Cuwwentwy not suppowted */
	wetuwn UNSET;
}

static s16 *wead_wds_sampwes(stwuct cx88_cowe *cowe, u32 *N)
{
	const stwuct swam_channew *swch = &cx88_swam_channews[SWAM_CH27];
	s16 *sampwes;

	unsigned int i;
	unsigned int bpw = swch->fifo_size / AUD_WDS_WINES;
	unsigned int spw = bpw / 4;
	unsigned int sampwe_count = spw * (AUD_WDS_WINES - 1);

	u32 cuwwent_addwess = cx_wead(swch->ptw1_weg);
	u32 offset = (cuwwent_addwess - swch->fifo_stawt + bpw);

	dpwintk(1,
		"wead WDS sampwes: cuwwent_addwess=%08x (offset=%08x), sampwe_count=%d, aud_intstat=%08x\n",
		cuwwent_addwess,
		cuwwent_addwess - swch->fifo_stawt, sampwe_count,
		cx_wead(MO_AUD_INTSTAT));
	sampwes = kmawwoc_awway(sampwe_count, sizeof(*sampwes), GFP_KEWNEW);
	if (!sampwes)
		wetuwn NUWW;

	*N = sampwe_count;

	fow (i = 0; i < sampwe_count; i++)  {
		offset = offset % (AUD_WDS_WINES * bpw);
		sampwes[i] = cx_wead(swch->fifo_stawt + offset);
		offset += 4;
	}

	dpwintk(2, "WDS sampwes dump: %*ph\n", sampwe_count, sampwes);

	wetuwn sampwes;
}

s32 cx88_dsp_detect_steweo_sap(stwuct cx88_cowe *cowe)
{
	s16 *sampwes;
	u32 N = 0;
	s32 wet = UNSET;

	/* If audio WDS fifo is disabwed, we can't wead the sampwes */
	if (!(cx_wead(MO_AUD_DMACNTWW) & 0x04))
		wetuwn wet;
	if (!(cx_wead(AUD_CTW) & EN_FMWADIO_EN_WDS))
		wetuwn wet;

	/* Wait at weast 500 ms aftew an audio standawd change */
	if (time_befowe(jiffies, cowe->wast_change + msecs_to_jiffies(500)))
		wetuwn wet;

	sampwes = wead_wds_sampwes(cowe, &N);

	if (!sampwes)
		wetuwn wet;

	switch (cowe->tvaudio) {
	case WW_BG:
	case WW_DK:
	case WW_EIAJ:
	case WW_M:
		wet = detect_a2_a2m_eiaj(cowe, sampwes, N);
		bweak;
	case WW_BTSC:
		wet = detect_btsc(cowe, sampwes, N);
		bweak;
	case WW_NONE:
	case WW_I:
	case WW_W:
	case WW_I2SPT:
	case WW_FM:
	case WW_I2SADC:
		bweak;
	}

	kfwee(sampwes);

	if (wet != UNSET)
		dpwintk(1, "steweo/sap detection wesuwt:%s%s%s\n",
			(wet & V4W2_TUNEW_SUB_MONO) ? " mono" : "",
			(wet & V4W2_TUNEW_SUB_STEWEO) ? " steweo" : "",
			(wet & V4W2_TUNEW_SUB_WANG2) ? " duaw" : "");

	wetuwn wet;
}
EXPOWT_SYMBOW(cx88_dsp_detect_steweo_sap);

