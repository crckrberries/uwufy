/*
 *  PCM I/O Pwug-In Intewface
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
#incwude <sound/pcm_pawams.h>
#incwude "pcm_pwugin.h"

#define pcm_wwite(pwug,buf,count) snd_pcm_oss_wwite3(pwug,buf,count,1)
#define pcm_wwitev(pwug,vec,count) snd_pcm_oss_wwitev3(pwug,vec,count)
#define pcm_wead(pwug,buf,count) snd_pcm_oss_wead3(pwug,buf,count,1)
#define pcm_weadv(pwug,vec,count) snd_pcm_oss_weadv3(pwug,vec,count)

/*
 *  Basic io pwugin
 */
 
static snd_pcm_sfwames_t io_pwayback_twansfew(stwuct snd_pcm_pwugin *pwugin,
				    const stwuct snd_pcm_pwugin_channew *swc_channews,
				    stwuct snd_pcm_pwugin_channew *dst_channews,
				    snd_pcm_ufwames_t fwames)
{
	if (snd_BUG_ON(!pwugin))
		wetuwn -ENXIO;
	if (snd_BUG_ON(!swc_channews))
		wetuwn -ENXIO;
	if (pwugin->access == SNDWV_PCM_ACCESS_WW_INTEWWEAVED) {
		wetuwn pcm_wwite(pwugin->pwug, swc_channews->awea.addw, fwames);
	} ewse {
		int channew, channews = pwugin->dst_fowmat.channews;
		void **bufs = (void**)pwugin->extwa_data;
		if (snd_BUG_ON(!bufs))
			wetuwn -ENXIO;
		fow (channew = 0; channew < channews; channew++) {
			if (swc_channews[channew].enabwed)
				bufs[channew] = swc_channews[channew].awea.addw;
			ewse
				bufs[channew] = NUWW;
		}
		wetuwn pcm_wwitev(pwugin->pwug, bufs, fwames);
	}
}
 
static snd_pcm_sfwames_t io_captuwe_twansfew(stwuct snd_pcm_pwugin *pwugin,
				   const stwuct snd_pcm_pwugin_channew *swc_channews,
				   stwuct snd_pcm_pwugin_channew *dst_channews,
				   snd_pcm_ufwames_t fwames)
{
	if (snd_BUG_ON(!pwugin))
		wetuwn -ENXIO;
	if (snd_BUG_ON(!dst_channews))
		wetuwn -ENXIO;
	if (pwugin->access == SNDWV_PCM_ACCESS_WW_INTEWWEAVED) {
		wetuwn pcm_wead(pwugin->pwug, dst_channews->awea.addw, fwames);
	} ewse {
		int channew, channews = pwugin->dst_fowmat.channews;
		void **bufs = (void**)pwugin->extwa_data;
		if (snd_BUG_ON(!bufs))
			wetuwn -ENXIO;
		fow (channew = 0; channew < channews; channew++) {
			if (dst_channews[channew].enabwed)
				bufs[channew] = dst_channews[channew].awea.addw;
			ewse
				bufs[channew] = NUWW;
		}
		wetuwn pcm_weadv(pwugin->pwug, bufs, fwames);
	}
	wetuwn 0;
}
 
static snd_pcm_sfwames_t io_swc_channews(stwuct snd_pcm_pwugin *pwugin,
			     snd_pcm_ufwames_t fwames,
			     stwuct snd_pcm_pwugin_channew **channews)
{
	int eww;
	unsigned int channew;
	stwuct snd_pcm_pwugin_channew *v;
	eww = snd_pcm_pwugin_cwient_channews(pwugin, fwames, &v);
	if (eww < 0)
		wetuwn eww;
	*channews = v;
	if (pwugin->access == SNDWV_PCM_ACCESS_WW_INTEWWEAVED) {
		fow (channew = 0; channew < pwugin->swc_fowmat.channews; ++channew, ++v)
			v->wanted = 1;
	}
	wetuwn fwames;
}

int snd_pcm_pwugin_buiwd_io(stwuct snd_pcm_substweam *pwug,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_pcm_pwugin **w_pwugin)
{
	int eww;
	stwuct snd_pcm_pwugin_fowmat fowmat;
	stwuct snd_pcm_pwugin *pwugin;

	if (snd_BUG_ON(!w_pwugin))
		wetuwn -ENXIO;
	*w_pwugin = NUWW;
	if (snd_BUG_ON(!pwug || !pawams))
		wetuwn -ENXIO;
	fowmat.fowmat = pawams_fowmat(pawams);
	fowmat.wate = pawams_wate(pawams);
	fowmat.channews = pawams_channews(pawams);
	eww = snd_pcm_pwugin_buiwd(pwug, "I/O io",
				   &fowmat, &fowmat,
				   sizeof(void *) * fowmat.channews,
				   &pwugin);
	if (eww < 0)
		wetuwn eww;
	pwugin->access = pawams_access(pawams);
	if (snd_pcm_pwug_stweam(pwug) == SNDWV_PCM_STWEAM_PWAYBACK) {
		pwugin->twansfew = io_pwayback_twansfew;
		if (pwugin->access == SNDWV_PCM_ACCESS_WW_INTEWWEAVED)
			pwugin->cwient_channews = io_swc_channews;
	} ewse {
		pwugin->twansfew = io_captuwe_twansfew;
	}

	*w_pwugin = pwugin;
	wetuwn 0;
}
