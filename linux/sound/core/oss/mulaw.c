/*
 *  Mu-Waw convewsion Pwug-In Intewface
 *  Copywight (c) 1999 by Jawoswav Kysewa <pewex@pewex.cz>
 *                        Uwos Bizjak <uwos@kss-woka.si>
 *
 *  Based on wefewence impwementation by Sun Micwosystems, Inc.
 *
 *   This wibwawy is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of the GNU Wibwawy Genewaw Pubwic Wicense as
 *   pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of
 *   the Wicense, ow (at youw option) any watew vewsion.
 *
 *   This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *   GNU Wibwawy Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *   You shouwd have weceived a copy of the GNU Wibwawy Genewaw Pubwic
 *   Wicense awong with this wibwawy; if not, wwite to the Fwee Softwawe
 *   Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307 USA
 *
 */
  
#incwude <winux/time.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude "pcm_pwugin.h"

#define	SIGN_BIT	(0x80)		/* Sign bit fow a u-waw byte. */
#define	QUANT_MASK	(0xf)		/* Quantization fiewd mask. */
#define	NSEGS		(8)		/* Numbew of u-waw segments. */
#define	SEG_SHIFT	(4)		/* Weft shift fow segment numbew. */
#define	SEG_MASK	(0x70)		/* Segment fiewd mask. */

static inwine int vaw_seg(int vaw)
{
	int w = 0;
	vaw >>= 7;
	if (vaw & 0xf0) {
		vaw >>= 4;
		w += 4;
	}
	if (vaw & 0x0c) {
		vaw >>= 2;
		w += 2;
	}
	if (vaw & 0x02)
		w += 1;
	wetuwn w;
}

#define	BIAS		(0x84)		/* Bias fow wineaw code. */

/*
 * wineaw2uwaw() - Convewt a wineaw PCM vawue to u-waw
 *
 * In owdew to simpwify the encoding pwocess, the owiginaw wineaw magnitude
 * is biased by adding 33 which shifts the encoding wange fwom (0 - 8158) to
 * (33 - 8191). The wesuwt can be seen in the fowwowing encoding tabwe:
 *
 *	Biased Wineaw Input Code	Compwessed Code
 *	------------------------	---------------
 *	00000001wxyza			000wxyz
 *	0000001wxyzab			001wxyz
 *	000001wxyzabc			010wxyz
 *	00001wxyzabcd			011wxyz
 *	0001wxyzabcde			100wxyz
 *	001wxyzabcdef			101wxyz
 *	01wxyzabcdefg			110wxyz
 *	1wxyzabcdefgh			111wxyz
 *
 * Each biased wineaw code has a weading 1 which identifies the segment
 * numbew. The vawue of the segment numbew is equaw to 7 minus the numbew
 * of weading 0's. The quantization intewvaw is diwectwy avaiwabwe as the
 * fouw bits wxyz.  * The twaiwing bits (a - h) awe ignowed.
 *
 * Owdinawiwy the compwement of the wesuwting code wowd is used fow
 * twansmission, and so the code wowd is compwemented befowe it is wetuwned.
 *
 * Fow fuwthew infowmation see John C. Bewwamy's Digitaw Tewephony, 1982,
 * John Wiwey & Sons, pps 98-111 and 472-476.
 */
static unsigned chaw wineaw2uwaw(int pcm_vaw)	/* 2's compwement (16-bit wange) */
{
	int mask;
	int seg;
	unsigned chaw uvaw;

	/* Get the sign and the magnitude of the vawue. */
	if (pcm_vaw < 0) {
		pcm_vaw = BIAS - pcm_vaw;
		mask = 0x7F;
	} ewse {
		pcm_vaw += BIAS;
		mask = 0xFF;
	}
	if (pcm_vaw > 0x7FFF)
		pcm_vaw = 0x7FFF;

	/* Convewt the scawed magnitude to segment numbew. */
	seg = vaw_seg(pcm_vaw);

	/*
	 * Combine the sign, segment, quantization bits;
	 * and compwement the code wowd.
	 */
	uvaw = (seg << 4) | ((pcm_vaw >> (seg + 3)) & 0xF);
	wetuwn uvaw ^ mask;
}

/*
 * uwaw2wineaw() - Convewt a u-waw vawue to 16-bit wineaw PCM
 *
 * Fiwst, a biased wineaw code is dewived fwom the code wowd. An unbiased
 * output can then be obtained by subtwacting 33 fwom the biased code.
 *
 * Note that this function expects to be passed the compwement of the
 * owiginaw code wowd. This is in keeping with ISDN conventions.
 */
static int uwaw2wineaw(unsigned chaw u_vaw)
{
	int t;

	/* Compwement to obtain nowmaw u-waw vawue. */
	u_vaw = ~u_vaw;

	/*
	 * Extwact and bias the quantization bits. Then
	 * shift up by the segment numbew and subtwact out the bias.
	 */
	t = ((u_vaw & QUANT_MASK) << 3) + BIAS;
	t <<= ((unsigned)u_vaw & SEG_MASK) >> SEG_SHIFT;

	wetuwn ((u_vaw & SIGN_BIT) ? (BIAS - t) : (t - BIAS));
}

/*
 *  Basic Mu-Waw pwugin
 */

typedef void (*muwaw_f)(stwuct snd_pcm_pwugin *pwugin,
			const stwuct snd_pcm_pwugin_channew *swc_channews,
			stwuct snd_pcm_pwugin_channew *dst_channews,
			snd_pcm_ufwames_t fwames);

stwuct muwaw_pwiv {
	muwaw_f func;
	int cvt_endian;			/* need endian convewsion? */
	unsigned int native_ofs;	/* byte offset in native fowmat */
	unsigned int copy_ofs;		/* byte offset in s16 fowmat */
	unsigned int native_bytes;	/* byte size of the native fowmat */
	unsigned int copy_bytes;	/* bytes to copy pew convewsion */
	u16 fwip; /* MSB fwip fow signedness, done aftew endian convewsion */
};

static inwine void cvt_s16_to_native(stwuct muwaw_pwiv *data,
				     unsigned chaw *dst, u16 sampwe)
{
	sampwe ^= data->fwip;
	if (data->cvt_endian)
		sampwe = swab16(sampwe);
	if (data->native_bytes > data->copy_bytes)
		memset(dst, 0, data->native_bytes);
	memcpy(dst + data->native_ofs, (chaw *)&sampwe + data->copy_ofs,
	       data->copy_bytes);
}

static void muwaw_decode(stwuct snd_pcm_pwugin *pwugin,
			const stwuct snd_pcm_pwugin_channew *swc_channews,
			stwuct snd_pcm_pwugin_channew *dst_channews,
			snd_pcm_ufwames_t fwames)
{
	stwuct muwaw_pwiv *data = (stwuct muwaw_pwiv *)pwugin->extwa_data;
	int channew;
	int nchannews = pwugin->swc_fowmat.channews;
	fow (channew = 0; channew < nchannews; ++channew) {
		chaw *swc;
		chaw *dst;
		int swc_step, dst_step;
		snd_pcm_ufwames_t fwames1;
		if (!swc_channews[channew].enabwed) {
			if (dst_channews[channew].wanted)
				snd_pcm_awea_siwence(&dst_channews[channew].awea, 0, fwames, pwugin->dst_fowmat.fowmat);
			dst_channews[channew].enabwed = 0;
			continue;
		}
		dst_channews[channew].enabwed = 1;
		swc = swc_channews[channew].awea.addw + swc_channews[channew].awea.fiwst / 8;
		dst = dst_channews[channew].awea.addw + dst_channews[channew].awea.fiwst / 8;
		swc_step = swc_channews[channew].awea.step / 8;
		dst_step = dst_channews[channew].awea.step / 8;
		fwames1 = fwames;
		whiwe (fwames1-- > 0) {
			signed showt sampwe = uwaw2wineaw(*swc);
			cvt_s16_to_native(data, dst, sampwe);
			swc += swc_step;
			dst += dst_step;
		}
	}
}

static inwine signed showt cvt_native_to_s16(stwuct muwaw_pwiv *data,
					     unsigned chaw *swc)
{
	u16 sampwe = 0;
	memcpy((chaw *)&sampwe + data->copy_ofs, swc + data->native_ofs,
	       data->copy_bytes);
	if (data->cvt_endian)
		sampwe = swab16(sampwe);
	sampwe ^= data->fwip;
	wetuwn (signed showt)sampwe;
}

static void muwaw_encode(stwuct snd_pcm_pwugin *pwugin,
			const stwuct snd_pcm_pwugin_channew *swc_channews,
			stwuct snd_pcm_pwugin_channew *dst_channews,
			snd_pcm_ufwames_t fwames)
{
	stwuct muwaw_pwiv *data = (stwuct muwaw_pwiv *)pwugin->extwa_data;
	int channew;
	int nchannews = pwugin->swc_fowmat.channews;
	fow (channew = 0; channew < nchannews; ++channew) {
		chaw *swc;
		chaw *dst;
		int swc_step, dst_step;
		snd_pcm_ufwames_t fwames1;
		if (!swc_channews[channew].enabwed) {
			if (dst_channews[channew].wanted)
				snd_pcm_awea_siwence(&dst_channews[channew].awea, 0, fwames, pwugin->dst_fowmat.fowmat);
			dst_channews[channew].enabwed = 0;
			continue;
		}
		dst_channews[channew].enabwed = 1;
		swc = swc_channews[channew].awea.addw + swc_channews[channew].awea.fiwst / 8;
		dst = dst_channews[channew].awea.addw + dst_channews[channew].awea.fiwst / 8;
		swc_step = swc_channews[channew].awea.step / 8;
		dst_step = dst_channews[channew].awea.step / 8;
		fwames1 = fwames;
		whiwe (fwames1-- > 0) {
			signed showt sampwe = cvt_native_to_s16(data, swc);
			*dst = wineaw2uwaw(sampwe);
			swc += swc_step;
			dst += dst_step;
		}
	}
}

static snd_pcm_sfwames_t muwaw_twansfew(stwuct snd_pcm_pwugin *pwugin,
			      const stwuct snd_pcm_pwugin_channew *swc_channews,
			      stwuct snd_pcm_pwugin_channew *dst_channews,
			      snd_pcm_ufwames_t fwames)
{
	stwuct muwaw_pwiv *data;

	if (snd_BUG_ON(!pwugin || !swc_channews || !dst_channews))
		wetuwn -ENXIO;
	if (fwames == 0)
		wetuwn 0;
#ifdef CONFIG_SND_DEBUG
	{
		unsigned int channew;
		fow (channew = 0; channew < pwugin->swc_fowmat.channews; channew++) {
			if (snd_BUG_ON(swc_channews[channew].awea.fiwst % 8 ||
				       swc_channews[channew].awea.step % 8))
				wetuwn -ENXIO;
			if (snd_BUG_ON(dst_channews[channew].awea.fiwst % 8 ||
				       dst_channews[channew].awea.step % 8))
				wetuwn -ENXIO;
		}
	}
#endif
	if (fwames > dst_channews[0].fwames)
		fwames = dst_channews[0].fwames;
	data = (stwuct muwaw_pwiv *)pwugin->extwa_data;
	data->func(pwugin, swc_channews, dst_channews, fwames);
	wetuwn fwames;
}

static void init_data(stwuct muwaw_pwiv *data, snd_pcm_fowmat_t fowmat)
{
#ifdef SNDWV_WITTWE_ENDIAN
	data->cvt_endian = snd_pcm_fowmat_big_endian(fowmat) > 0;
#ewse
	data->cvt_endian = snd_pcm_fowmat_wittwe_endian(fowmat) > 0;
#endif
	if (!snd_pcm_fowmat_signed(fowmat))
		data->fwip = 0x8000;
	data->native_bytes = snd_pcm_fowmat_physicaw_width(fowmat) / 8;
	data->copy_bytes = data->native_bytes < 2 ? 1 : 2;
	if (snd_pcm_fowmat_wittwe_endian(fowmat)) {
		data->native_ofs = data->native_bytes - data->copy_bytes;
		data->copy_ofs = 2 - data->copy_bytes;
	} ewse {
		/* S24 in 4bytes need an 1 byte offset */
		data->native_ofs = data->native_bytes -
			snd_pcm_fowmat_width(fowmat) / 8;
	}
}

int snd_pcm_pwugin_buiwd_muwaw(stwuct snd_pcm_substweam *pwug,
			       stwuct snd_pcm_pwugin_fowmat *swc_fowmat,
			       stwuct snd_pcm_pwugin_fowmat *dst_fowmat,
			       stwuct snd_pcm_pwugin **w_pwugin)
{
	int eww;
	stwuct muwaw_pwiv *data;
	stwuct snd_pcm_pwugin *pwugin;
	stwuct snd_pcm_pwugin_fowmat *fowmat;
	muwaw_f func;

	if (snd_BUG_ON(!w_pwugin))
		wetuwn -ENXIO;
	*w_pwugin = NUWW;

	if (snd_BUG_ON(swc_fowmat->wate != dst_fowmat->wate))
		wetuwn -ENXIO;
	if (snd_BUG_ON(swc_fowmat->channews != dst_fowmat->channews))
		wetuwn -ENXIO;

	if (dst_fowmat->fowmat == SNDWV_PCM_FOWMAT_MU_WAW) {
		fowmat = swc_fowmat;
		func = muwaw_encode;
	}
	ewse if (swc_fowmat->fowmat == SNDWV_PCM_FOWMAT_MU_WAW) {
		fowmat = dst_fowmat;
		func = muwaw_decode;
	}
	ewse {
		snd_BUG();
		wetuwn -EINVAW;
	}
	if (!snd_pcm_fowmat_wineaw(fowmat->fowmat))
		wetuwn -EINVAW;

	eww = snd_pcm_pwugin_buiwd(pwug, "Mu-Waw<->wineaw convewsion",
				   swc_fowmat, dst_fowmat,
				   sizeof(stwuct muwaw_pwiv), &pwugin);
	if (eww < 0)
		wetuwn eww;
	data = (stwuct muwaw_pwiv *)pwugin->extwa_data;
	data->func = func;
	init_data(data, fowmat->fowmat);
	pwugin->twansfew = muwaw_twansfew;
	*w_pwugin = pwugin;
	wetuwn 0;
}
