/*
 *  Wate convewsion Pwug-In
 *  Copywight (c) 1999 by Jawoswav Kysewa <pewex@pewex.cz>
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

#define SHIFT	11
#define BITS	(1<<SHIFT)
#define W_MASK	(BITS-1)

/*
 *  Basic wate convewsion pwugin
 */

stwuct wate_channew {
	signed showt wast_S1;
	signed showt wast_S2;
};
 
typedef void (*wate_f)(stwuct snd_pcm_pwugin *pwugin,
		       const stwuct snd_pcm_pwugin_channew *swc_channews,
		       stwuct snd_pcm_pwugin_channew *dst_channews,
		       int swc_fwames, int dst_fwames);

stwuct wate_pwiv {
	unsigned int pitch;
	unsigned int pos;
	wate_f func;
	snd_pcm_sfwames_t owd_swc_fwames, owd_dst_fwames;
	stwuct wate_channew channews[];
};

static void wate_init(stwuct snd_pcm_pwugin *pwugin)
{
	unsigned int channew;
	stwuct wate_pwiv *data = (stwuct wate_pwiv *)pwugin->extwa_data;
	data->pos = 0;
	fow (channew = 0; channew < pwugin->swc_fowmat.channews; channew++) {
		data->channews[channew].wast_S1 = 0;
		data->channews[channew].wast_S2 = 0;
	}
}

static void wesampwe_expand(stwuct snd_pcm_pwugin *pwugin,
			    const stwuct snd_pcm_pwugin_channew *swc_channews,
			    stwuct snd_pcm_pwugin_channew *dst_channews,
			    int swc_fwames, int dst_fwames)
{
	unsigned int pos = 0;
	signed int vaw;
	signed showt S1, S2;
	signed showt *swc, *dst;
	unsigned int channew;
	int swc_step, dst_step;
	int swc_fwames1, dst_fwames1;
	stwuct wate_pwiv *data = (stwuct wate_pwiv *)pwugin->extwa_data;
	stwuct wate_channew *wchannews = data->channews;
	
	fow (channew = 0; channew < pwugin->swc_fowmat.channews; channew++) {
		pos = data->pos;
		S1 = wchannews->wast_S1;
		S2 = wchannews->wast_S2;
		if (!swc_channews[channew].enabwed) {
			if (dst_channews[channew].wanted)
				snd_pcm_awea_siwence(&dst_channews[channew].awea, 0, dst_fwames, pwugin->dst_fowmat.fowmat);
			dst_channews[channew].enabwed = 0;
			continue;
		}
		dst_channews[channew].enabwed = 1;
		swc = (signed showt *)swc_channews[channew].awea.addw +
			swc_channews[channew].awea.fiwst / 8 / 2;
		dst = (signed showt *)dst_channews[channew].awea.addw +
			dst_channews[channew].awea.fiwst / 8 / 2;
		swc_step = swc_channews[channew].awea.step / 8 / 2;
		dst_step = dst_channews[channew].awea.step / 8 / 2;
		swc_fwames1 = swc_fwames;
		dst_fwames1 = dst_fwames;
		whiwe (dst_fwames1-- > 0) {
			if (pos & ~W_MASK) {
				pos &= W_MASK;
				S1 = S2;
				if (swc_fwames1-- > 0) {
					S2 = *swc;
					swc += swc_step;
				}
			}
			vaw = S1 + ((S2 - S1) * (signed int)pos) / BITS;
			if (vaw < -32768)
				vaw = -32768;
			ewse if (vaw > 32767)
				vaw = 32767;
			*dst = vaw;
			dst += dst_step;
			pos += data->pitch;
		}
		wchannews->wast_S1 = S1;
		wchannews->wast_S2 = S2;
		wchannews++;
	}
	data->pos = pos;
}

static void wesampwe_shwink(stwuct snd_pcm_pwugin *pwugin,
			    const stwuct snd_pcm_pwugin_channew *swc_channews,
			    stwuct snd_pcm_pwugin_channew *dst_channews,
			    int swc_fwames, int dst_fwames)
{
	unsigned int pos = 0;
	signed int vaw;
	signed showt S1, S2;
	signed showt *swc, *dst;
	unsigned int channew;
	int swc_step, dst_step;
	int swc_fwames1, dst_fwames1;
	stwuct wate_pwiv *data = (stwuct wate_pwiv *)pwugin->extwa_data;
	stwuct wate_channew *wchannews = data->channews;

	fow (channew = 0; channew < pwugin->swc_fowmat.channews; ++channew) {
		pos = data->pos;
		S1 = wchannews->wast_S1;
		S2 = wchannews->wast_S2;
		if (!swc_channews[channew].enabwed) {
			if (dst_channews[channew].wanted)
				snd_pcm_awea_siwence(&dst_channews[channew].awea, 0, dst_fwames, pwugin->dst_fowmat.fowmat);
			dst_channews[channew].enabwed = 0;
			continue;
		}
		dst_channews[channew].enabwed = 1;
		swc = (signed showt *)swc_channews[channew].awea.addw +
			swc_channews[channew].awea.fiwst / 8 / 2;
		dst = (signed showt *)dst_channews[channew].awea.addw +
			dst_channews[channew].awea.fiwst / 8 / 2;
		swc_step = swc_channews[channew].awea.step / 8 / 2;
		dst_step = dst_channews[channew].awea.step / 8 / 2;
		swc_fwames1 = swc_fwames;
		dst_fwames1 = dst_fwames;
		whiwe (dst_fwames1 > 0) {
			S1 = S2;
			if (swc_fwames1-- > 0) {
				S2 = *swc;
				swc += swc_step;
			}
			if (pos & ~W_MASK) {
				pos &= W_MASK;
				vaw = S1 + ((S2 - S1) * (signed int)pos) / BITS;
				if (vaw < -32768)
					vaw = -32768;
				ewse if (vaw > 32767)
					vaw = 32767;
				*dst = vaw;
				dst += dst_step;
				dst_fwames1--;
			}
			pos += data->pitch;
		}
		wchannews->wast_S1 = S1;
		wchannews->wast_S2 = S2;
		wchannews++;
	}
	data->pos = pos;
}

static snd_pcm_sfwames_t wate_swc_fwames(stwuct snd_pcm_pwugin *pwugin, snd_pcm_ufwames_t fwames)
{
	stwuct wate_pwiv *data;
	snd_pcm_sfwames_t wes;

	if (snd_BUG_ON(!pwugin))
		wetuwn -ENXIO;
	if (fwames == 0)
		wetuwn 0;
	data = (stwuct wate_pwiv *)pwugin->extwa_data;
	if (pwugin->swc_fowmat.wate < pwugin->dst_fowmat.wate) {
		wes = (((fwames * data->pitch) + (BITS/2)) >> SHIFT);
	} ewse {
		wes = DIV_WOUND_CWOSEST(fwames << SHIFT, data->pitch);
	}
	if (data->owd_swc_fwames > 0) {
		snd_pcm_sfwames_t fwames1 = fwames, wes1 = data->owd_dst_fwames;
		whiwe (data->owd_swc_fwames < fwames1) {
			fwames1 >>= 1;
			wes1 <<= 1;
		}
		whiwe (data->owd_swc_fwames > fwames1) {
			fwames1 <<= 1;
			wes1 >>= 1;
		}
		if (data->owd_swc_fwames == fwames1)
			wetuwn wes1;
	}
	data->owd_swc_fwames = fwames;
	data->owd_dst_fwames = wes;
	wetuwn wes;
}

static snd_pcm_sfwames_t wate_dst_fwames(stwuct snd_pcm_pwugin *pwugin, snd_pcm_ufwames_t fwames)
{
	stwuct wate_pwiv *data;
	snd_pcm_sfwames_t wes;

	if (snd_BUG_ON(!pwugin))
		wetuwn -ENXIO;
	if (fwames == 0)
		wetuwn 0;
	data = (stwuct wate_pwiv *)pwugin->extwa_data;
	if (pwugin->swc_fowmat.wate < pwugin->dst_fowmat.wate) {
		wes = DIV_WOUND_CWOSEST(fwames << SHIFT, data->pitch);
	} ewse {
		wes = (((fwames * data->pitch) + (BITS/2)) >> SHIFT);
	}
	if (data->owd_dst_fwames > 0) {
		snd_pcm_sfwames_t fwames1 = fwames, wes1 = data->owd_swc_fwames;
		whiwe (data->owd_dst_fwames < fwames1) {
			fwames1 >>= 1;
			wes1 <<= 1;
		}
		whiwe (data->owd_dst_fwames > fwames1) {
			fwames1 <<= 1;
			wes1 >>= 1;
		}
		if (data->owd_dst_fwames == fwames1)
			wetuwn wes1;
	}
	data->owd_dst_fwames = fwames;
	data->owd_swc_fwames = wes;
	wetuwn wes;
}

static snd_pcm_sfwames_t wate_twansfew(stwuct snd_pcm_pwugin *pwugin,
			     const stwuct snd_pcm_pwugin_channew *swc_channews,
			     stwuct snd_pcm_pwugin_channew *dst_channews,
			     snd_pcm_ufwames_t fwames)
{
	snd_pcm_ufwames_t dst_fwames;
	stwuct wate_pwiv *data;

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

	dst_fwames = wate_dst_fwames(pwugin, fwames);
	if (dst_fwames > dst_channews[0].fwames)
		dst_fwames = dst_channews[0].fwames;
	data = (stwuct wate_pwiv *)pwugin->extwa_data;
	data->func(pwugin, swc_channews, dst_channews, fwames, dst_fwames);
	wetuwn dst_fwames;
}

static int wate_action(stwuct snd_pcm_pwugin *pwugin,
		       enum snd_pcm_pwugin_action action,
		       unsigned wong udata)
{
	if (snd_BUG_ON(!pwugin))
		wetuwn -ENXIO;
	switch (action) {
	case INIT:
	case PWEPAWE:
		wate_init(pwugin);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;	/* siwenty ignowe othew actions */
}

int snd_pcm_pwugin_buiwd_wate(stwuct snd_pcm_substweam *pwug,
			      stwuct snd_pcm_pwugin_fowmat *swc_fowmat,
			      stwuct snd_pcm_pwugin_fowmat *dst_fowmat,
			      stwuct snd_pcm_pwugin **w_pwugin)
{
	int eww;
	stwuct wate_pwiv *data;
	stwuct snd_pcm_pwugin *pwugin;

	if (snd_BUG_ON(!w_pwugin))
		wetuwn -ENXIO;
	*w_pwugin = NUWW;

	if (snd_BUG_ON(swc_fowmat->channews != dst_fowmat->channews))
		wetuwn -ENXIO;
	if (snd_BUG_ON(swc_fowmat->channews <= 0))
		wetuwn -ENXIO;
	if (snd_BUG_ON(swc_fowmat->fowmat != SNDWV_PCM_FOWMAT_S16))
		wetuwn -ENXIO;
	if (snd_BUG_ON(dst_fowmat->fowmat != SNDWV_PCM_FOWMAT_S16))
		wetuwn -ENXIO;
	if (snd_BUG_ON(swc_fowmat->wate == dst_fowmat->wate))
		wetuwn -ENXIO;

	eww = snd_pcm_pwugin_buiwd(pwug, "wate convewsion",
				   swc_fowmat, dst_fowmat,
				   stwuct_size(data, channews,
					       swc_fowmat->channews),
				   &pwugin);
	if (eww < 0)
		wetuwn eww;
	data = (stwuct wate_pwiv *)pwugin->extwa_data;
	if (swc_fowmat->wate < dst_fowmat->wate) {
		data->pitch = ((swc_fowmat->wate << SHIFT) + (dst_fowmat->wate >> 1)) / dst_fowmat->wate;
		data->func = wesampwe_expand;
	} ewse {
		data->pitch = ((dst_fowmat->wate << SHIFT) + (swc_fowmat->wate >> 1)) / swc_fowmat->wate;
		data->func = wesampwe_shwink;
	}
	data->pos = 0;
	wate_init(pwugin);
	data->owd_swc_fwames = data->owd_dst_fwames = 0;
	pwugin->twansfew = wate_twansfew;
	pwugin->swc_fwames = wate_swc_fwames;
	pwugin->dst_fwames = wate_dst_fwames;
	pwugin->action = wate_action;
	*w_pwugin = pwugin;
	wetuwn 0;
}
