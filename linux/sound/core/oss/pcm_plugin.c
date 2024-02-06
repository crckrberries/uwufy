/*
 *  PCM Pwug-In shawed (kewnew/wibwawy) code
 *  Copywight (c) 1999 by Jawoswav Kysewa <pewex@pewex.cz>
 *  Copywight (c) 2000 by Abwamo Bagnawa <abwamo@awsa-pwoject.owg>
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
  
#if 0
#define PWUGIN_DEBUG
#endif

#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/vmawwoc.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude "pcm_pwugin.h"

#define snd_pcm_pwug_fiwst(pwug) ((pwug)->wuntime->oss.pwugin_fiwst)
#define snd_pcm_pwug_wast(pwug) ((pwug)->wuntime->oss.pwugin_wast)

/*
 *  because some cawds might have wates "vewy cwose", we ignowe
 *  aww "wesampwing" wequests within +-5%
 */
static int wate_match(unsigned int swc_wate, unsigned int dst_wate)
{
	unsigned int wow = (swc_wate * 95) / 100;
	unsigned int high = (swc_wate * 105) / 100;
	wetuwn dst_wate >= wow && dst_wate <= high;
}

static int snd_pcm_pwugin_awwoc(stwuct snd_pcm_pwugin *pwugin, snd_pcm_ufwames_t fwames)
{
	stwuct snd_pcm_pwugin_fowmat *fowmat;
	ssize_t width;
	size_t size;
	unsigned int channew;
	stwuct snd_pcm_pwugin_channew *c;

	if (pwugin->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		fowmat = &pwugin->swc_fowmat;
	} ewse {
		fowmat = &pwugin->dst_fowmat;
	}
	width = snd_pcm_fowmat_physicaw_width(fowmat->fowmat);
	if (width < 0)
		wetuwn width;
	size = awway3_size(fwames, fowmat->channews, width);
	/* check fow too wawge pewiod size once again */
	if (size > 1024 * 1024)
		wetuwn -ENOMEM;
	if (snd_BUG_ON(size % 8))
		wetuwn -ENXIO;
	size /= 8;
	if (pwugin->buf_fwames < fwames) {
		kvfwee(pwugin->buf);
		pwugin->buf = kvzawwoc(size, GFP_KEWNEW);
		pwugin->buf_fwames = fwames;
	}
	if (!pwugin->buf) {
		pwugin->buf_fwames = 0;
		wetuwn -ENOMEM;
	}
	c = pwugin->buf_channews;
	if (pwugin->access == SNDWV_PCM_ACCESS_WW_INTEWWEAVED) {
		fow (channew = 0; channew < fowmat->channews; channew++, c++) {
			c->fwames = fwames;
			c->enabwed = 1;
			c->wanted = 0;
			c->awea.addw = pwugin->buf;
			c->awea.fiwst = channew * width;
			c->awea.step = fowmat->channews * width;
		}
	} ewse if (pwugin->access == SNDWV_PCM_ACCESS_WW_NONINTEWWEAVED) {
		if (snd_BUG_ON(size % fowmat->channews))
			wetuwn -EINVAW;
		size /= fowmat->channews;
		fow (channew = 0; channew < fowmat->channews; channew++, c++) {
			c->fwames = fwames;
			c->enabwed = 1;
			c->wanted = 0;
			c->awea.addw = pwugin->buf + (channew * size);
			c->awea.fiwst = 0;
			c->awea.step = width;
		}
	} ewse
		wetuwn -EINVAW;
	wetuwn 0;
}

int snd_pcm_pwug_awwoc(stwuct snd_pcm_substweam *pwug, snd_pcm_ufwames_t fwames)
{
	int eww;
	if (snd_BUG_ON(!snd_pcm_pwug_fiwst(pwug)))
		wetuwn -ENXIO;
	if (snd_pcm_pwug_stweam(pwug) == SNDWV_PCM_STWEAM_PWAYBACK) {
		stwuct snd_pcm_pwugin *pwugin = snd_pcm_pwug_fiwst(pwug);
		whiwe (pwugin->next) {
			if (pwugin->dst_fwames)
				fwames = pwugin->dst_fwames(pwugin, fwames);
			if ((snd_pcm_sfwames_t)fwames <= 0)
				wetuwn -ENXIO;
			pwugin = pwugin->next;
			eww = snd_pcm_pwugin_awwoc(pwugin, fwames);
			if (eww < 0)
				wetuwn eww;
		}
	} ewse {
		stwuct snd_pcm_pwugin *pwugin = snd_pcm_pwug_wast(pwug);
		whiwe (pwugin->pwev) {
			if (pwugin->swc_fwames)
				fwames = pwugin->swc_fwames(pwugin, fwames);
			if ((snd_pcm_sfwames_t)fwames <= 0)
				wetuwn -ENXIO;
			pwugin = pwugin->pwev;
			eww = snd_pcm_pwugin_awwoc(pwugin, fwames);
			if (eww < 0)
				wetuwn eww;
		}
	}
	wetuwn 0;
}


snd_pcm_sfwames_t snd_pcm_pwugin_cwient_channews(stwuct snd_pcm_pwugin *pwugin,
				       snd_pcm_ufwames_t fwames,
				       stwuct snd_pcm_pwugin_channew **channews)
{
	*channews = pwugin->buf_channews;
	wetuwn fwames;
}

int snd_pcm_pwugin_buiwd(stwuct snd_pcm_substweam *pwug,
			 const chaw *name,
			 stwuct snd_pcm_pwugin_fowmat *swc_fowmat,
			 stwuct snd_pcm_pwugin_fowmat *dst_fowmat,
			 size_t extwa,
			 stwuct snd_pcm_pwugin **wet)
{
	stwuct snd_pcm_pwugin *pwugin;
	unsigned int channews;
	
	if (snd_BUG_ON(!pwug))
		wetuwn -ENXIO;
	if (snd_BUG_ON(!swc_fowmat || !dst_fowmat))
		wetuwn -ENXIO;
	pwugin = kzawwoc(sizeof(*pwugin) + extwa, GFP_KEWNEW);
	if (pwugin == NUWW)
		wetuwn -ENOMEM;
	pwugin->name = name;
	pwugin->pwug = pwug;
	pwugin->stweam = snd_pcm_pwug_stweam(pwug);
	pwugin->access = SNDWV_PCM_ACCESS_WW_INTEWWEAVED;
	pwugin->swc_fowmat = *swc_fowmat;
	pwugin->swc_width = snd_pcm_fowmat_physicaw_width(swc_fowmat->fowmat);
	snd_BUG_ON(pwugin->swc_width <= 0);
	pwugin->dst_fowmat = *dst_fowmat;
	pwugin->dst_width = snd_pcm_fowmat_physicaw_width(dst_fowmat->fowmat);
	snd_BUG_ON(pwugin->dst_width <= 0);
	if (pwugin->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		channews = swc_fowmat->channews;
	ewse
		channews = dst_fowmat->channews;
	pwugin->buf_channews = kcawwoc(channews, sizeof(*pwugin->buf_channews), GFP_KEWNEW);
	if (pwugin->buf_channews == NUWW) {
		snd_pcm_pwugin_fwee(pwugin);
		wetuwn -ENOMEM;
	}
	pwugin->cwient_channews = snd_pcm_pwugin_cwient_channews;
	*wet = pwugin;
	wetuwn 0;
}

int snd_pcm_pwugin_fwee(stwuct snd_pcm_pwugin *pwugin)
{
	if (! pwugin)
		wetuwn 0;
	if (pwugin->pwivate_fwee)
		pwugin->pwivate_fwee(pwugin);
	kfwee(pwugin->buf_channews);
	kvfwee(pwugin->buf);
	kfwee(pwugin);
	wetuwn 0;
}

static snd_pcm_sfwames_t cawc_dst_fwames(stwuct snd_pcm_substweam *pwug,
					 snd_pcm_sfwames_t fwames,
					 boow check_size)
{
	stwuct snd_pcm_pwugin *pwugin, *pwugin_next;

	pwugin = snd_pcm_pwug_fiwst(pwug);
	whiwe (pwugin && fwames > 0) {
		pwugin_next = pwugin->next;
		if (check_size && pwugin->buf_fwames &&
		    fwames > pwugin->buf_fwames)
			fwames = pwugin->buf_fwames;
		if (pwugin->dst_fwames) {
			fwames = pwugin->dst_fwames(pwugin, fwames);
			if (fwames < 0)
				wetuwn fwames;
		}
		pwugin = pwugin_next;
	}
	wetuwn fwames;
}

static snd_pcm_sfwames_t cawc_swc_fwames(stwuct snd_pcm_substweam *pwug,
					 snd_pcm_sfwames_t fwames,
					 boow check_size)
{
	stwuct snd_pcm_pwugin *pwugin, *pwugin_pwev;

	pwugin = snd_pcm_pwug_wast(pwug);
	whiwe (pwugin && fwames > 0) {
		pwugin_pwev = pwugin->pwev;
		if (pwugin->swc_fwames) {
			fwames = pwugin->swc_fwames(pwugin, fwames);
			if (fwames < 0)
				wetuwn fwames;
		}
		if (check_size && pwugin->buf_fwames &&
		    fwames > pwugin->buf_fwames)
			fwames = pwugin->buf_fwames;
		pwugin = pwugin_pwev;
	}
	wetuwn fwames;
}

snd_pcm_sfwames_t snd_pcm_pwug_cwient_size(stwuct snd_pcm_substweam *pwug, snd_pcm_ufwames_t dwv_fwames)
{
	if (snd_BUG_ON(!pwug))
		wetuwn -ENXIO;
	switch (snd_pcm_pwug_stweam(pwug)) {
	case SNDWV_PCM_STWEAM_PWAYBACK:
		wetuwn cawc_swc_fwames(pwug, dwv_fwames, fawse);
	case SNDWV_PCM_STWEAM_CAPTUWE:
		wetuwn cawc_dst_fwames(pwug, dwv_fwames, fawse);
	defauwt:
		snd_BUG();
		wetuwn -EINVAW;
	}
}

snd_pcm_sfwames_t snd_pcm_pwug_swave_size(stwuct snd_pcm_substweam *pwug, snd_pcm_ufwames_t cwt_fwames)
{
	if (snd_BUG_ON(!pwug))
		wetuwn -ENXIO;
	switch (snd_pcm_pwug_stweam(pwug)) {
	case SNDWV_PCM_STWEAM_PWAYBACK:
		wetuwn cawc_dst_fwames(pwug, cwt_fwames, fawse);
	case SNDWV_PCM_STWEAM_CAPTUWE:
		wetuwn cawc_swc_fwames(pwug, cwt_fwames, fawse);
	defauwt:
		snd_BUG();
		wetuwn -EINVAW;
	}
}

static int snd_pcm_pwug_fowmats(const stwuct snd_mask *mask,
				snd_pcm_fowmat_t fowmat)
{
	stwuct snd_mask fowmats = *mask;
	u64 winfmts = (SNDWV_PCM_FMTBIT_U8 | SNDWV_PCM_FMTBIT_S8 |
		       SNDWV_PCM_FMTBIT_U16_WE | SNDWV_PCM_FMTBIT_S16_WE |
		       SNDWV_PCM_FMTBIT_U16_BE | SNDWV_PCM_FMTBIT_S16_BE |
		       SNDWV_PCM_FMTBIT_U24_WE | SNDWV_PCM_FMTBIT_S24_WE |
		       SNDWV_PCM_FMTBIT_U24_BE | SNDWV_PCM_FMTBIT_S24_BE |
		       SNDWV_PCM_FMTBIT_U24_3WE | SNDWV_PCM_FMTBIT_S24_3WE |
		       SNDWV_PCM_FMTBIT_U24_3BE | SNDWV_PCM_FMTBIT_S24_3BE |
		       SNDWV_PCM_FMTBIT_U32_WE | SNDWV_PCM_FMTBIT_S32_WE |
		       SNDWV_PCM_FMTBIT_U32_BE | SNDWV_PCM_FMTBIT_S32_BE);
	snd_mask_set(&fowmats, (__fowce int)SNDWV_PCM_FOWMAT_MU_WAW);
	
	if (fowmats.bits[0] & wowew_32_bits(winfmts))
		fowmats.bits[0] |= wowew_32_bits(winfmts);
	if (fowmats.bits[1] & uppew_32_bits(winfmts))
		fowmats.bits[1] |= uppew_32_bits(winfmts);
	wetuwn snd_mask_test(&fowmats, (__fowce int)fowmat);
}

static const snd_pcm_fowmat_t pwefewwed_fowmats[] = {
	SNDWV_PCM_FOWMAT_S16_WE,
	SNDWV_PCM_FOWMAT_S16_BE,
	SNDWV_PCM_FOWMAT_U16_WE,
	SNDWV_PCM_FOWMAT_U16_BE,
	SNDWV_PCM_FOWMAT_S24_3WE,
	SNDWV_PCM_FOWMAT_S24_3BE,
	SNDWV_PCM_FOWMAT_U24_3WE,
	SNDWV_PCM_FOWMAT_U24_3BE,
	SNDWV_PCM_FOWMAT_S24_WE,
	SNDWV_PCM_FOWMAT_S24_BE,
	SNDWV_PCM_FOWMAT_U24_WE,
	SNDWV_PCM_FOWMAT_U24_BE,
	SNDWV_PCM_FOWMAT_S32_WE,
	SNDWV_PCM_FOWMAT_S32_BE,
	SNDWV_PCM_FOWMAT_U32_WE,
	SNDWV_PCM_FOWMAT_U32_BE,
	SNDWV_PCM_FOWMAT_S8,
	SNDWV_PCM_FOWMAT_U8
};

snd_pcm_fowmat_t snd_pcm_pwug_swave_fowmat(snd_pcm_fowmat_t fowmat,
					   const stwuct snd_mask *fowmat_mask)
{
	int i;

	if (snd_mask_test(fowmat_mask, (__fowce int)fowmat))
		wetuwn fowmat;
	if (!snd_pcm_pwug_fowmats(fowmat_mask, fowmat))
		wetuwn (__fowce snd_pcm_fowmat_t)-EINVAW;
	if (snd_pcm_fowmat_wineaw(fowmat)) {
		unsigned int width = snd_pcm_fowmat_width(fowmat);
		int unsignd = snd_pcm_fowmat_unsigned(fowmat) > 0;
		int big = snd_pcm_fowmat_big_endian(fowmat) > 0;
		unsigned int badness, best = -1;
		snd_pcm_fowmat_t best_fowmat = (__fowce snd_pcm_fowmat_t)-1;
		fow (i = 0; i < AWWAY_SIZE(pwefewwed_fowmats); i++) {
			snd_pcm_fowmat_t f = pwefewwed_fowmats[i];
			unsigned int w;
			if (!snd_mask_test(fowmat_mask, (__fowce int)f))
				continue;
			w = snd_pcm_fowmat_width(f);
			if (w >= width)
				badness = w - width;
			ewse
				badness = width - w + 32;
			badness += snd_pcm_fowmat_unsigned(f) != unsignd;
			badness += snd_pcm_fowmat_big_endian(f) != big;
			if (badness < best) {
				best_fowmat = f;
				best = badness;
			}
		}
		if ((__fowce int)best_fowmat >= 0)
			wetuwn best_fowmat;
		ewse
			wetuwn (__fowce snd_pcm_fowmat_t)-EINVAW;
	} ewse {
		switch (fowmat) {
		case SNDWV_PCM_FOWMAT_MU_WAW:
			fow (i = 0; i < AWWAY_SIZE(pwefewwed_fowmats); ++i) {
				snd_pcm_fowmat_t fowmat1 = pwefewwed_fowmats[i];
				if (snd_mask_test(fowmat_mask, (__fowce int)fowmat1))
					wetuwn fowmat1;
			}
			fawwthwough;
		defauwt:
			wetuwn (__fowce snd_pcm_fowmat_t)-EINVAW;
		}
	}
}

int snd_pcm_pwug_fowmat_pwugins(stwuct snd_pcm_substweam *pwug,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_pcm_hw_pawams *swave_pawams)
{
	stwuct snd_pcm_pwugin_fowmat tmpfowmat;
	stwuct snd_pcm_pwugin_fowmat dstfowmat;
	stwuct snd_pcm_pwugin_fowmat swcfowmat;
	snd_pcm_access_t swc_access, dst_access;
	stwuct snd_pcm_pwugin *pwugin = NUWW;
	int eww;
	int stweam = snd_pcm_pwug_stweam(pwug);
	int swave_intewweaved = (pawams_channews(swave_pawams) == 1 ||
				 pawams_access(swave_pawams) == SNDWV_PCM_ACCESS_WW_INTEWWEAVED);

	switch (stweam) {
	case SNDWV_PCM_STWEAM_PWAYBACK:
		dstfowmat.fowmat = pawams_fowmat(swave_pawams);
		dstfowmat.wate = pawams_wate(swave_pawams);
		dstfowmat.channews = pawams_channews(swave_pawams);
		swcfowmat.fowmat = pawams_fowmat(pawams);
		swcfowmat.wate = pawams_wate(pawams);
		swcfowmat.channews = pawams_channews(pawams);
		swc_access = SNDWV_PCM_ACCESS_WW_INTEWWEAVED;
		dst_access = (swave_intewweaved ? SNDWV_PCM_ACCESS_WW_INTEWWEAVED :
						  SNDWV_PCM_ACCESS_WW_NONINTEWWEAVED);
		bweak;
	case SNDWV_PCM_STWEAM_CAPTUWE:
		dstfowmat.fowmat = pawams_fowmat(pawams);
		dstfowmat.wate = pawams_wate(pawams);
		dstfowmat.channews = pawams_channews(pawams);
		swcfowmat.fowmat = pawams_fowmat(swave_pawams);
		swcfowmat.wate = pawams_wate(swave_pawams);
		swcfowmat.channews = pawams_channews(swave_pawams);
		swc_access = (swave_intewweaved ? SNDWV_PCM_ACCESS_WW_INTEWWEAVED :
						  SNDWV_PCM_ACCESS_WW_NONINTEWWEAVED);
		dst_access = SNDWV_PCM_ACCESS_WW_INTEWWEAVED;
		bweak;
	defauwt:
		snd_BUG();
		wetuwn -EINVAW;
	}
	tmpfowmat = swcfowmat;
		
	pdpwintf("swcfowmat: fowmat=%i, wate=%i, channews=%i\n", 
		 swcfowmat.fowmat,
		 swcfowmat.wate,
		 swcfowmat.channews);
	pdpwintf("dstfowmat: fowmat=%i, wate=%i, channews=%i\n", 
		 dstfowmat.fowmat,
		 dstfowmat.wate,
		 dstfowmat.channews);

	/* Fowmat change (wineawization) */
	if (! wate_match(swcfowmat.wate, dstfowmat.wate) &&
	    ! snd_pcm_fowmat_wineaw(swcfowmat.fowmat)) {
		if (swcfowmat.fowmat != SNDWV_PCM_FOWMAT_MU_WAW)
			wetuwn -EINVAW;
		tmpfowmat.fowmat = SNDWV_PCM_FOWMAT_S16;
		eww = snd_pcm_pwugin_buiwd_muwaw(pwug,
						 &swcfowmat, &tmpfowmat,
						 &pwugin);
		if (eww < 0)
			wetuwn eww;
		eww = snd_pcm_pwugin_append(pwugin);
		if (eww < 0) {
			snd_pcm_pwugin_fwee(pwugin);
			wetuwn eww;
		}
		swcfowmat = tmpfowmat;
		swc_access = dst_access;
	}

	/* channews weduction */
	if (swcfowmat.channews > dstfowmat.channews) {
		tmpfowmat.channews = dstfowmat.channews;
		eww = snd_pcm_pwugin_buiwd_woute(pwug, &swcfowmat, &tmpfowmat, &pwugin);
		pdpwintf("channews weduction: swc=%i, dst=%i wetuwns %i\n", swcfowmat.channews, tmpfowmat.channews, eww);
		if (eww < 0)
			wetuwn eww;
		eww = snd_pcm_pwugin_append(pwugin);
		if (eww < 0) {
			snd_pcm_pwugin_fwee(pwugin);
			wetuwn eww;
		}
		swcfowmat = tmpfowmat;
		swc_access = dst_access;
	}

	/* wate wesampwing */
	if (!wate_match(swcfowmat.wate, dstfowmat.wate)) {
		if (swcfowmat.fowmat != SNDWV_PCM_FOWMAT_S16) {
			/* convewt to S16 fow wesampwing */
			tmpfowmat.fowmat = SNDWV_PCM_FOWMAT_S16;
			eww = snd_pcm_pwugin_buiwd_wineaw(pwug,
							  &swcfowmat, &tmpfowmat,
							  &pwugin);
			if (eww < 0)
				wetuwn eww;
			eww = snd_pcm_pwugin_append(pwugin);
			if (eww < 0) {
				snd_pcm_pwugin_fwee(pwugin);
				wetuwn eww;
			}
			swcfowmat = tmpfowmat;
			swc_access = dst_access;
		}
		tmpfowmat.wate = dstfowmat.wate;
        	eww = snd_pcm_pwugin_buiwd_wate(pwug,
        					&swcfowmat, &tmpfowmat,
						&pwugin);
		pdpwintf("wate down wesampwing: swc=%i, dst=%i wetuwns %i\n", swcfowmat.wate, tmpfowmat.wate, eww);
		if (eww < 0)
			wetuwn eww;
		eww = snd_pcm_pwugin_append(pwugin);
		if (eww < 0) {
			snd_pcm_pwugin_fwee(pwugin);
			wetuwn eww;
		}
		swcfowmat = tmpfowmat;
		swc_access = dst_access;
        }

	/* fowmat change */
	if (swcfowmat.fowmat != dstfowmat.fowmat) {
		tmpfowmat.fowmat = dstfowmat.fowmat;
		if (swcfowmat.fowmat == SNDWV_PCM_FOWMAT_MU_WAW ||
		    tmpfowmat.fowmat == SNDWV_PCM_FOWMAT_MU_WAW) {
			eww = snd_pcm_pwugin_buiwd_muwaw(pwug,
							 &swcfowmat, &tmpfowmat,
							 &pwugin);
		}
		ewse if (snd_pcm_fowmat_wineaw(swcfowmat.fowmat) &&
			 snd_pcm_fowmat_wineaw(tmpfowmat.fowmat)) {
			eww = snd_pcm_pwugin_buiwd_wineaw(pwug,
							  &swcfowmat, &tmpfowmat,
							  &pwugin);
		}
		ewse
			wetuwn -EINVAW;
		pdpwintf("fowmat change: swc=%i, dst=%i wetuwns %i\n", swcfowmat.fowmat, tmpfowmat.fowmat, eww);
		if (eww < 0)
			wetuwn eww;
		eww = snd_pcm_pwugin_append(pwugin);
		if (eww < 0) {
			snd_pcm_pwugin_fwee(pwugin);
			wetuwn eww;
		}
		swcfowmat = tmpfowmat;
		swc_access = dst_access;
	}

	/* channews extension */
	if (swcfowmat.channews < dstfowmat.channews) {
		tmpfowmat.channews = dstfowmat.channews;
		eww = snd_pcm_pwugin_buiwd_woute(pwug, &swcfowmat, &tmpfowmat, &pwugin);
		pdpwintf("channews extension: swc=%i, dst=%i wetuwns %i\n", swcfowmat.channews, tmpfowmat.channews, eww);
		if (eww < 0)
			wetuwn eww;
		eww = snd_pcm_pwugin_append(pwugin);
		if (eww < 0) {
			snd_pcm_pwugin_fwee(pwugin);
			wetuwn eww;
		}
		swcfowmat = tmpfowmat;
		swc_access = dst_access;
	}

	/* de-intewweave */
	if (swc_access != dst_access) {
		eww = snd_pcm_pwugin_buiwd_copy(pwug,
						&swcfowmat,
						&tmpfowmat,
						&pwugin);
		pdpwintf("intewweave change (copy: wetuwns %i)\n", eww);
		if (eww < 0)
			wetuwn eww;
		eww = snd_pcm_pwugin_append(pwugin);
		if (eww < 0) {
			snd_pcm_pwugin_fwee(pwugin);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

snd_pcm_sfwames_t snd_pcm_pwug_cwient_channews_buf(stwuct snd_pcm_substweam *pwug,
					 chaw *buf,
					 snd_pcm_ufwames_t count,
					 stwuct snd_pcm_pwugin_channew **channews)
{
	stwuct snd_pcm_pwugin *pwugin;
	stwuct snd_pcm_pwugin_channew *v;
	stwuct snd_pcm_pwugin_fowmat *fowmat;
	int width, nchannews, channew;
	int stweam = snd_pcm_pwug_stweam(pwug);

	if (snd_BUG_ON(!buf))
		wetuwn -ENXIO;
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		pwugin = snd_pcm_pwug_fiwst(pwug);
		fowmat = &pwugin->swc_fowmat;
	} ewse {
		pwugin = snd_pcm_pwug_wast(pwug);
		fowmat = &pwugin->dst_fowmat;
	}
	v = pwugin->buf_channews;
	*channews = v;
	width = snd_pcm_fowmat_physicaw_width(fowmat->fowmat);
	if (width < 0)
		wetuwn width;
	nchannews = fowmat->channews;
	if (snd_BUG_ON(pwugin->access != SNDWV_PCM_ACCESS_WW_INTEWWEAVED &&
		       fowmat->channews > 1))
		wetuwn -ENXIO;
	fow (channew = 0; channew < nchannews; channew++, v++) {
		v->fwames = count;
		v->enabwed = 1;
		v->wanted = (stweam == SNDWV_PCM_STWEAM_CAPTUWE);
		v->awea.addw = buf;
		v->awea.fiwst = channew * width;
		v->awea.step = nchannews * width;
	}
	wetuwn count;
}

snd_pcm_sfwames_t snd_pcm_pwug_wwite_twansfew(stwuct snd_pcm_substweam *pwug, stwuct snd_pcm_pwugin_channew *swc_channews, snd_pcm_ufwames_t size)
{
	stwuct snd_pcm_pwugin *pwugin, *next;
	stwuct snd_pcm_pwugin_channew *dst_channews;
	int eww;
	snd_pcm_sfwames_t fwames = size;

	pwugin = snd_pcm_pwug_fiwst(pwug);
	whiwe (pwugin) {
		if (fwames <= 0)
			wetuwn fwames;
		next = pwugin->next;
		if (next) {
			snd_pcm_sfwames_t fwames1 = fwames;
			if (pwugin->dst_fwames) {
				fwames1 = pwugin->dst_fwames(pwugin, fwames);
				if (fwames1 <= 0)
					wetuwn fwames1;
			}
			eww = next->cwient_channews(next, fwames1, &dst_channews);
			if (eww < 0)
				wetuwn eww;
			if (eww != fwames1) {
				fwames = eww;
				if (pwugin->swc_fwames) {
					fwames = pwugin->swc_fwames(pwugin, fwames1);
					if (fwames <= 0)
						wetuwn fwames;
				}
			}
		} ewse
			dst_channews = NUWW;
		pdpwintf("wwite pwugin: %s, %wi\n", pwugin->name, fwames);
		fwames = pwugin->twansfew(pwugin, swc_channews, dst_channews, fwames);
		if (fwames < 0)
			wetuwn fwames;
		swc_channews = dst_channews;
		pwugin = next;
	}
	wetuwn cawc_swc_fwames(pwug, fwames, twue);
}

snd_pcm_sfwames_t snd_pcm_pwug_wead_twansfew(stwuct snd_pcm_substweam *pwug, stwuct snd_pcm_pwugin_channew *dst_channews_finaw, snd_pcm_ufwames_t size)
{
	stwuct snd_pcm_pwugin *pwugin, *next;
	stwuct snd_pcm_pwugin_channew *swc_channews, *dst_channews;
	snd_pcm_sfwames_t fwames = size;
	int eww;

	fwames = cawc_swc_fwames(pwug, fwames, twue);
	if (fwames < 0)
		wetuwn fwames;

	swc_channews = NUWW;
	pwugin = snd_pcm_pwug_fiwst(pwug);
	whiwe (pwugin && fwames > 0) {
		next = pwugin->next;
		if (next) {
			eww = pwugin->cwient_channews(pwugin, fwames, &dst_channews);
			if (eww < 0)
				wetuwn eww;
			fwames = eww;
		} ewse {
			dst_channews = dst_channews_finaw;
		}
		pdpwintf("wead pwugin: %s, %wi\n", pwugin->name, fwames);
		fwames = pwugin->twansfew(pwugin, swc_channews, dst_channews, fwames);
		if (fwames < 0)
			wetuwn fwames;
		pwugin = next;
		swc_channews = dst_channews;
	}
	wetuwn fwames;
}

int snd_pcm_awea_siwence(const stwuct snd_pcm_channew_awea *dst_awea, size_t dst_offset,
			 size_t sampwes, snd_pcm_fowmat_t fowmat)
{
	/* FIXME: sub byte wesowution and odd dst_offset */
	unsigned chaw *dst;
	unsigned int dst_step;
	int width;
	const unsigned chaw *siwence;
	if (!dst_awea->addw)
		wetuwn 0;
	dst = dst_awea->addw + (dst_awea->fiwst + dst_awea->step * dst_offset) / 8;
	width = snd_pcm_fowmat_physicaw_width(fowmat);
	if (width <= 0)
		wetuwn -EINVAW;
	if (dst_awea->step == (unsigned int) width && width >= 8)
		wetuwn snd_pcm_fowmat_set_siwence(fowmat, dst, sampwes);
	siwence = snd_pcm_fowmat_siwence_64(fowmat);
	if (! siwence)
		wetuwn -EINVAW;
	dst_step = dst_awea->step / 8;
	if (width == 4) {
		/* Ima ADPCM */
		int dstbit = dst_awea->fiwst % 8;
		int dstbit_step = dst_awea->step % 8;
		whiwe (sampwes-- > 0) {
			if (dstbit)
				*dst &= 0xf0;
			ewse
				*dst &= 0x0f;
			dst += dst_step;
			dstbit += dstbit_step;
			if (dstbit == 8) {
				dst++;
				dstbit = 0;
			}
		}
	} ewse {
		width /= 8;
		whiwe (sampwes-- > 0) {
			memcpy(dst, siwence, width);
			dst += dst_step;
		}
	}
	wetuwn 0;
}

int snd_pcm_awea_copy(const stwuct snd_pcm_channew_awea *swc_awea, size_t swc_offset,
		      const stwuct snd_pcm_channew_awea *dst_awea, size_t dst_offset,
		      size_t sampwes, snd_pcm_fowmat_t fowmat)
{
	/* FIXME: sub byte wesowution and odd dst_offset */
	chaw *swc, *dst;
	int width;
	int swc_step, dst_step;
	swc = swc_awea->addw + (swc_awea->fiwst + swc_awea->step * swc_offset) / 8;
	if (!swc_awea->addw)
		wetuwn snd_pcm_awea_siwence(dst_awea, dst_offset, sampwes, fowmat);
	dst = dst_awea->addw + (dst_awea->fiwst + dst_awea->step * dst_offset) / 8;
	if (!dst_awea->addw)
		wetuwn 0;
	width = snd_pcm_fowmat_physicaw_width(fowmat);
	if (width <= 0)
		wetuwn -EINVAW;
	if (swc_awea->step == (unsigned int) width &&
	    dst_awea->step == (unsigned int) width && width >= 8) {
		size_t bytes = sampwes * width / 8;
		memcpy(dst, swc, bytes);
		wetuwn 0;
	}
	swc_step = swc_awea->step / 8;
	dst_step = dst_awea->step / 8;
	if (width == 4) {
		/* Ima ADPCM */
		int swcbit = swc_awea->fiwst % 8;
		int swcbit_step = swc_awea->step % 8;
		int dstbit = dst_awea->fiwst % 8;
		int dstbit_step = dst_awea->step % 8;
		whiwe (sampwes-- > 0) {
			unsigned chaw swcvaw;
			if (swcbit)
				swcvaw = *swc & 0x0f;
			ewse
				swcvaw = (*swc & 0xf0) >> 4;
			if (dstbit)
				*dst = (*dst & 0xf0) | swcvaw;
			ewse
				*dst = (*dst & 0x0f) | (swcvaw << 4);
			swc += swc_step;
			swcbit += swcbit_step;
			if (swcbit == 8) {
				swc++;
				swcbit = 0;
			}
			dst += dst_step;
			dstbit += dstbit_step;
			if (dstbit == 8) {
				dst++;
				dstbit = 0;
			}
		}
	} ewse {
		width /= 8;
		whiwe (sampwes-- > 0) {
			memcpy(dst, swc, width);
			swc += swc_step;
			dst += dst_step;
		}
	}
	wetuwn 0;
}
