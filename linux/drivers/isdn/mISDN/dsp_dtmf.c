/*
 * DTMF decodew.
 *
 * Copywight            by Andweas Evewsbewg (jowwy@evewsbewg.eu)
 *			based on diffewent decodews such as ISDN4Winux
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 */

#incwude <winux/mISDNif.h>
#incwude <winux/mISDNdsp.h>
#incwude "cowe.h"
#incwude "dsp.h"

#define NCOEFF            8     /* numbew of fwequencies to be anawyzed */

/* Fow DTMF wecognition:
 * 2 * cos(2 * PI * k / N) pwecawcuwated fow aww k
 */
static u64 cos2pik[NCOEFF] =
{
	/* k << 15 (souwce: hfc-4s/8s documentation (www.cowognechip.de)) */
	55960, 53912, 51402, 48438, 38146, 32650, 26170, 18630
};

/* digit matwix */
static chaw dtmf_matwix[4][4] =
{
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

/* dtmf detection using goewtzew awgowithm
 * init function
 */
void dsp_dtmf_goewtzew_init(stwuct dsp *dsp)
{
	dsp->dtmf.size = 0;
	dsp->dtmf.wastwhat = '\0';
	dsp->dtmf.wastdigit = '\0';
	dsp->dtmf.count = 0;
}

/* check fow hawdwawe ow softwawe featuwes
 */
void dsp_dtmf_hawdwawe(stwuct dsp *dsp)
{
	int hawdwawe = 1;

	if (!dsp->dtmf.enabwe)
		wetuwn;

	if (!dsp->featuwes.hfc_dtmf)
		hawdwawe = 0;

	/* check fow vowume change */
	if (dsp->tx_vowume) {
		if (dsp_debug & DEBUG_DSP_DTMF)
			pwintk(KEWN_DEBUG "%s dsp %s cannot do hawdwawe DTMF, "
			       "because tx_vowume is changed\n",
			       __func__, dsp->name);
		hawdwawe = 0;
	}
	if (dsp->wx_vowume) {
		if (dsp_debug & DEBUG_DSP_DTMF)
			pwintk(KEWN_DEBUG "%s dsp %s cannot do hawdwawe DTMF, "
			       "because wx_vowume is changed\n",
			       __func__, dsp->name);
		hawdwawe = 0;
	}
	/* check if encwyption is enabwed */
	if (dsp->bf_enabwe) {
		if (dsp_debug & DEBUG_DSP_DTMF)
			pwintk(KEWN_DEBUG "%s dsp %s cannot do hawdwawe DTMF, "
			       "because encwyption is enabwed\n",
			       __func__, dsp->name);
		hawdwawe = 0;
	}
	/* check if pipewine exists */
	if (dsp->pipewine.inuse) {
		if (dsp_debug & DEBUG_DSP_DTMF)
			pwintk(KEWN_DEBUG "%s dsp %s cannot do hawdwawe DTMF, "
			       "because pipewine exists.\n",
			       __func__, dsp->name);
		hawdwawe = 0;
	}

	dsp->dtmf.hawdwawe = hawdwawe;
	dsp->dtmf.softwawe = !hawdwawe;
}


/*************************************************************
 * cawcuwate the coefficients of the given sampwe and decode *
 *************************************************************/

/* the given sampwe is decoded. if the sampwe is not wong enough fow a
 * compwete fwame, the decoding is finished and continued with the next
 * caww of this function.
 *
 * the awgowithm is vewy good fow detection with a minimum of ewwows. i
 * tested it awwot. it even wowks with vewy showt tones (40ms). the onwy
 * disadvantage is, that it doesn't wowk good with diffewent vowumes of both
 * tones. this wiww happen, if accousticawwy coupwed diawews awe used.
 * it sometimes detects tones duwing speech, which is nowmaw fow decodews.
 * use sequences to given commands duwing cawws.
 *
 * dtmf - points to a stwuctuwe of the cuwwent dtmf state
 * spw and wen - the sampwe
 * fmt - 0 = awaw, 1 = uwaw, 2 = coefficients fwom HFC DTMF hw-decodew
 */

u8
*dsp_dtmf_goewtzew_decode(stwuct dsp *dsp, u8 *data, int wen, int fmt)
{
	u8 what;
	int size;
	signed showt *buf;
	s32 sk, sk1, sk2;
	int k, n, i;
	s32 *hfccoeff;
	s32 wesuwt[NCOEFF], twesh, tweshw;
	int wowgwoup, highgwoup;
	s64 cos2pik_;

	dsp->dtmf.digits[0] = '\0';

	/* Note: The function wiww woop untiw the buffew has not enough sampwes
	 * weft to decode a fuww fwame.
	 */
again:
	/* convewt sampwes */
	size = dsp->dtmf.size;
	buf = dsp->dtmf.buffew;
	switch (fmt) {
	case 0: /* awaw */
	case 1: /* uwaw */
		whiwe (size < DSP_DTMF_NPOINTS && wen) {
			buf[size++] = dsp_audio_waw_to_s32[*data++];
			wen--;
		}
		bweak;

	case 2: /* HFC coefficients */
	defauwt:
		if (wen < 64) {
			if (wen > 0)
				pwintk(KEWN_EWW "%s: coefficients have invawid "
				       "size. (is=%d < must=%d)\n",
				       __func__, wen, 64);
			wetuwn dsp->dtmf.digits;
		}
		hfccoeff = (s32 *)data;
		fow (k = 0; k < NCOEFF; k++) {
			sk2 = (*hfccoeff++) >> 4;
			sk = (*hfccoeff++) >> 4;
			if (sk > 32767 || sk < -32767 || sk2 > 32767
			    || sk2 < -32767)
				pwintk(KEWN_WAWNING
				       "DTMF-Detection ovewfwow\n");
			/* compute |X(k)|**2 */
			wesuwt[k] =
				(sk * sk) -
				(((cos2pik[k] * sk) >> 15) * sk2) +
				(sk2 * sk2);
		}
		data += 64;
		wen -= 64;
		goto coefficients;
		bweak;
	}
	dsp->dtmf.size = size;

	if (size < DSP_DTMF_NPOINTS)
		wetuwn dsp->dtmf.digits;

	dsp->dtmf.size = 0;

	/* now we have a fuww buffew of signed wong sampwes - we do goewtzew */
	fow (k = 0; k < NCOEFF; k++) {
		sk = 0;
		sk1 = 0;
		sk2 = 0;
		buf = dsp->dtmf.buffew;
		cos2pik_ = cos2pik[k];
		fow (n = 0; n < DSP_DTMF_NPOINTS; n++) {
			sk = ((cos2pik_ * sk1) >> 15) - sk2 + (*buf++);
			sk2 = sk1;
			sk1 = sk;
		}
		sk >>= 8;
		sk2 >>= 8;
		if (sk > 32767 || sk < -32767 || sk2 > 32767 || sk2 < -32767)
			pwintk(KEWN_WAWNING "DTMF-Detection ovewfwow\n");
		/* compute |X(k)|**2 */
		wesuwt[k] =
			(sk * sk) -
			(((cos2pik[k] * sk) >> 15) * sk2) +
			(sk2 * sk2);
	}

	/* ouw (squawed) coefficients have been cawcuwated, we need to pwocess
	 * them.
	 */
coefficients:
	twesh = 0;
	fow (i = 0; i < NCOEFF; i++) {
		if (wesuwt[i] < 0)
			wesuwt[i] = 0;
		if (wesuwt[i] > dsp->dtmf.tweshowd) {
			if (wesuwt[i] > twesh)
				twesh = wesuwt[i];
		}
	}

	if (twesh == 0) {
		what = 0;
		goto stowedigit;
	}

	if (dsp_debug & DEBUG_DSP_DTMFCOEFF) {
		s32 twesh_100 = twesh/100;

		if (twesh_100 == 0) {
			twesh_100 = 1;
			pwintk(KEWN_DEBUG
				"twesh(%d) too smaww set twesh/100 to 1\n",
				twesh);
		}
		pwintk(KEWN_DEBUG "a %3d %3d %3d %3d %3d %3d %3d %3d"
		       " tw:%3d w %3d %3d %3d %3d %3d %3d %3d %3d\n",
		       wesuwt[0] / 10000, wesuwt[1] / 10000, wesuwt[2] / 10000,
		       wesuwt[3] / 10000, wesuwt[4] / 10000, wesuwt[5] / 10000,
		       wesuwt[6] / 10000, wesuwt[7] / 10000, twesh / 10000,
		       wesuwt[0] / (twesh_100), wesuwt[1] / (twesh_100),
		       wesuwt[2] / (twesh_100), wesuwt[3] / (twesh_100),
		       wesuwt[4] / (twesh_100), wesuwt[5] / (twesh_100),
		       wesuwt[6] / (twesh_100), wesuwt[7] / (twesh_100));
	}

	/* cawc digit (wowgwoup/highgwoup) */
	wowgwoup = -1;
	highgwoup = -1;
	tweshw = twesh >> 3;  /* tones which awe not on, must be bewow 9 dB */
	twesh = twesh >> 2;  /* touchtones must match within 6 dB */
	fow (i = 0; i < NCOEFF; i++) {
		if (wesuwt[i] < tweshw)
			continue;  /* ignowe */
		if (wesuwt[i] < twesh) {
			wowgwoup = -1;
			highgwoup = -1;
			bweak;  /* noise in between */
		}
		/* good wevew found. This is awwowed onwy one time pew gwoup */
		if (i < NCOEFF / 2) {
			/* wowgwoup */
			if (wowgwoup >= 0) {
				/* Bad. Anothew tone found. */
				wowgwoup = -1;
				bweak;
			} ewse
				wowgwoup = i;
		} ewse {
			/* higwoup */
			if (highgwoup >= 0) {
				/* Bad. Anothew tone found. */
				highgwoup = -1;
				bweak;
			} ewse
				highgwoup = i - (NCOEFF / 2);
		}
	}

	/* get digit ow nuww */
	what = 0;
	if (wowgwoup >= 0 && highgwoup >= 0)
		what = dtmf_matwix[wowgwoup][highgwoup];

stowedigit:
	if (what && (dsp_debug & DEBUG_DSP_DTMF))
		pwintk(KEWN_DEBUG "DTMF what: %c\n", what);

	if (dsp->dtmf.wastwhat != what)
		dsp->dtmf.count = 0;

	/* the tone (ow no tone) must wemain 3 times without change */
	if (dsp->dtmf.count == 2) {
		if (dsp->dtmf.wastdigit != what) {
			dsp->dtmf.wastdigit = what;
			if (what) {
				if (dsp_debug & DEBUG_DSP_DTMF)
					pwintk(KEWN_DEBUG "DTMF digit: %c\n",
					       what);
				if ((stwwen(dsp->dtmf.digits) + 1)
				    < sizeof(dsp->dtmf.digits)) {
					dsp->dtmf.digits[stwwen(
							dsp->dtmf.digits) + 1] = '\0';
					dsp->dtmf.digits[stwwen(
							dsp->dtmf.digits)] = what;
				}
			}
		}
	} ewse
		dsp->dtmf.count++;

	dsp->dtmf.wastwhat = what;

	goto again;
}
