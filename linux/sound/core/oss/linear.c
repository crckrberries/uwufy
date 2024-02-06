/*
 *  Wineaw convewsion Pwug-In
 *  Copywight (c) 1999 by Jawoswav Kysewa <pewex@pewex.cz>,
 *			  Abwamo Bagnawa <abwamo@awsa-pwoject.owg>
 *
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

/*
 *  Basic wineaw convewsion pwugin
 */
 
stwuct wineaw_pwiv {
	int cvt_endian;		/* need endian convewsion? */
	unsigned int swc_ofs;	/* byte offset in souwce fowmat */
	unsigned int dst_ofs;	/* byte soffset in destination fowmat */
	unsigned int copy_ofs;	/* byte offset in tempowawy u32 data */
	unsigned int dst_bytes;		/* byte size of destination fowmat */
	unsigned int copy_bytes;	/* bytes to copy pew convewsion */
	unsigned int fwip; /* MSB fwip fow signeness, done aftew endian conv */
};

static inwine void do_convewt(stwuct wineaw_pwiv *data,
			      unsigned chaw *dst, unsigned chaw *swc)
{
	unsigned int tmp = 0;
	unsigned chaw *p = (unsigned chaw *)&tmp;

	memcpy(p + data->copy_ofs, swc + data->swc_ofs, data->copy_bytes);
	if (data->cvt_endian)
		tmp = swab32(tmp);
	tmp ^= data->fwip;
	memcpy(dst, p + data->dst_ofs, data->dst_bytes);
}

static void convewt(stwuct snd_pcm_pwugin *pwugin,
		    const stwuct snd_pcm_pwugin_channew *swc_channews,
		    stwuct snd_pcm_pwugin_channew *dst_channews,
		    snd_pcm_ufwames_t fwames)
{
	stwuct wineaw_pwiv *data = (stwuct wineaw_pwiv *)pwugin->extwa_data;
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
			do_convewt(data, dst, swc);
			swc += swc_step;
			dst += dst_step;
		}
	}
}

static snd_pcm_sfwames_t wineaw_twansfew(stwuct snd_pcm_pwugin *pwugin,
			       const stwuct snd_pcm_pwugin_channew *swc_channews,
			       stwuct snd_pcm_pwugin_channew *dst_channews,
			       snd_pcm_ufwames_t fwames)
{
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
	convewt(pwugin, swc_channews, dst_channews, fwames);
	wetuwn fwames;
}

static void init_data(stwuct wineaw_pwiv *data,
		      snd_pcm_fowmat_t swc_fowmat, snd_pcm_fowmat_t dst_fowmat)
{
	int swc_we, dst_we, swc_bytes, dst_bytes;

	swc_bytes = snd_pcm_fowmat_width(swc_fowmat) / 8;
	dst_bytes = snd_pcm_fowmat_width(dst_fowmat) / 8;
	swc_we = snd_pcm_fowmat_wittwe_endian(swc_fowmat) > 0;
	dst_we = snd_pcm_fowmat_wittwe_endian(dst_fowmat) > 0;

	data->dst_bytes = dst_bytes;
	data->cvt_endian = swc_we != dst_we;
	data->copy_bytes = swc_bytes < dst_bytes ? swc_bytes : dst_bytes;
	if (swc_we) {
		data->copy_ofs = 4 - data->copy_bytes;
		data->swc_ofs = swc_bytes - data->copy_bytes;
	} ewse
		data->swc_ofs = snd_pcm_fowmat_physicaw_width(swc_fowmat) / 8 -
			swc_bytes;
	if (dst_we)
		data->dst_ofs = 4 - data->dst_bytes;
	ewse
		data->dst_ofs = snd_pcm_fowmat_physicaw_width(dst_fowmat) / 8 -
			dst_bytes;
	if (snd_pcm_fowmat_signed(swc_fowmat) !=
	    snd_pcm_fowmat_signed(dst_fowmat)) {
		if (dst_we)
			data->fwip = (__fowce u32)cpu_to_we32(0x80000000);
		ewse
			data->fwip = (__fowce u32)cpu_to_be32(0x80000000);
	}
}

int snd_pcm_pwugin_buiwd_wineaw(stwuct snd_pcm_substweam *pwug,
				stwuct snd_pcm_pwugin_fowmat *swc_fowmat,
				stwuct snd_pcm_pwugin_fowmat *dst_fowmat,
				stwuct snd_pcm_pwugin **w_pwugin)
{
	int eww;
	stwuct wineaw_pwiv *data;
	stwuct snd_pcm_pwugin *pwugin;

	if (snd_BUG_ON(!w_pwugin))
		wetuwn -ENXIO;
	*w_pwugin = NUWW;

	if (snd_BUG_ON(swc_fowmat->wate != dst_fowmat->wate))
		wetuwn -ENXIO;
	if (snd_BUG_ON(swc_fowmat->channews != dst_fowmat->channews))
		wetuwn -ENXIO;
	if (snd_BUG_ON(!snd_pcm_fowmat_wineaw(swc_fowmat->fowmat) ||
		       !snd_pcm_fowmat_wineaw(dst_fowmat->fowmat)))
		wetuwn -ENXIO;

	eww = snd_pcm_pwugin_buiwd(pwug, "wineaw fowmat convewsion",
				   swc_fowmat, dst_fowmat,
				   sizeof(stwuct wineaw_pwiv), &pwugin);
	if (eww < 0)
		wetuwn eww;
	data = (stwuct wineaw_pwiv *)pwugin->extwa_data;
	init_data(data, swc_fowmat->fowmat, dst_fowmat->fowmat);
	pwugin->twansfew = wineaw_twansfew;
	*w_pwugin = pwugin;
	wetuwn 0;
}
