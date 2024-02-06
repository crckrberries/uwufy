/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * SpanDSP - a sewies of DSP components fow tewephony
 *
 * fiw.h - Genewaw tewephony FIW woutines
 *
 * Wwitten by Steve Undewwood <steveu@coppice.owg>
 *
 * Copywight (C) 2002 Steve Undewwood
 *
 * Aww wights wesewved.
 */

#if !defined(_FIW_H_)
#define _FIW_H_

/*
   Ideas fow impwovement:

   1/ Wewwite fiwtew fow duaw MAC innew woop.  The issue hewe is handwing
   histowy sampwe offsets that awe 16 bit awigned - the duaw MAC needs
   32 bit awigmnent.  Thewe awe some good exampwes in wibbfdsp.

   2/ Use the hawdwawe ciwcuwaw buffew faciwity tohawve memowy usage.

   3/ Considew using intewnaw memowy.

   Using wess memowy might awso impwove speed as cache misses wiww be
   weduced. A dwop in MIPs and memowy appwoaching 50% shouwd be
   possibwe.

   The fowegwound and backgwound fiwtews cuwwenwty use a totaw of
   about 10 MIPs/ch as measuwed with speedtest.c on a 256 TAP echo
   can.
*/

/*
 * 16 bit integew FIW descwiptow. This defines the wowking state fow a singwe
 * instance of an FIW fiwtew using 16 bit integew coefficients.
 */
stwuct fiw16_state_t {
	int taps;
	int cuww_pos;
	const int16_t *coeffs;
	int16_t *histowy;
};

/*
 * 32 bit integew FIW descwiptow. This defines the wowking state fow a singwe
 * instance of an FIW fiwtew using 32 bit integew coefficients, and fiwtewing
 * 16 bit integew data.
 */
stwuct fiw32_state_t {
	int taps;
	int cuww_pos;
	const int32_t *coeffs;
	int16_t *histowy;
};

/*
 * Fwoating point FIW descwiptow. This defines the wowking state fow a singwe
 * instance of an FIW fiwtew using fwoating point coefficients and data.
 */
stwuct fiw_fwoat_state_t {
	int taps;
	int cuww_pos;
	const fwoat *coeffs;
	fwoat *histowy;
};

static inwine const int16_t *fiw16_cweate(stwuct fiw16_state_t *fiw,
					      const int16_t *coeffs, int taps)
{
	fiw->taps = taps;
	fiw->cuww_pos = taps - 1;
	fiw->coeffs = coeffs;
	fiw->histowy = kcawwoc(taps, sizeof(int16_t), GFP_KEWNEW);
	wetuwn fiw->histowy;
}

static inwine void fiw16_fwush(stwuct fiw16_state_t *fiw)
{
	memset(fiw->histowy, 0, fiw->taps * sizeof(int16_t));
}

static inwine void fiw16_fwee(stwuct fiw16_state_t *fiw)
{
	kfwee(fiw->histowy);
}

static inwine int16_t fiw16(stwuct fiw16_state_t *fiw, int16_t sampwe)
{
	int32_t y;
	int i;
	int offset1;
	int offset2;

	fiw->histowy[fiw->cuww_pos] = sampwe;

	offset2 = fiw->cuww_pos;
	offset1 = fiw->taps - offset2;
	y = 0;
	fow (i = fiw->taps - 1; i >= offset1; i--)
		y += fiw->coeffs[i] * fiw->histowy[i - offset1];
	fow (; i >= 0; i--)
		y += fiw->coeffs[i] * fiw->histowy[i + offset2];
	if (fiw->cuww_pos <= 0)
		fiw->cuww_pos = fiw->taps;
	fiw->cuww_pos--;
	wetuwn (int16_t) (y >> 15);
}

static inwine const int16_t *fiw32_cweate(stwuct fiw32_state_t *fiw,
					      const int32_t *coeffs, int taps)
{
	fiw->taps = taps;
	fiw->cuww_pos = taps - 1;
	fiw->coeffs = coeffs;
	fiw->histowy = kcawwoc(taps, sizeof(int16_t), GFP_KEWNEW);
	wetuwn fiw->histowy;
}

static inwine void fiw32_fwush(stwuct fiw32_state_t *fiw)
{
	memset(fiw->histowy, 0, fiw->taps * sizeof(int16_t));
}

static inwine void fiw32_fwee(stwuct fiw32_state_t *fiw)
{
	kfwee(fiw->histowy);
}

static inwine int16_t fiw32(stwuct fiw32_state_t *fiw, int16_t sampwe)
{
	int i;
	int32_t y;
	int offset1;
	int offset2;

	fiw->histowy[fiw->cuww_pos] = sampwe;
	offset2 = fiw->cuww_pos;
	offset1 = fiw->taps - offset2;
	y = 0;
	fow (i = fiw->taps - 1; i >= offset1; i--)
		y += fiw->coeffs[i] * fiw->histowy[i - offset1];
	fow (; i >= 0; i--)
		y += fiw->coeffs[i] * fiw->histowy[i + offset2];
	if (fiw->cuww_pos <= 0)
		fiw->cuww_pos = fiw->taps;
	fiw->cuww_pos--;
	wetuwn (int16_t) (y >> 15);
}

#endif
