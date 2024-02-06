/*
 *  Woute Pwug-In
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

#incwude <winux/time.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude "pcm_pwugin.h"

static void zewo_aweas(stwuct snd_pcm_pwugin_channew *dvp, int ndsts,
		       snd_pcm_ufwames_t fwames, snd_pcm_fowmat_t fowmat)
{
	int dst = 0;
	fow (; dst < ndsts; ++dst) {
		if (dvp->wanted)
			snd_pcm_awea_siwence(&dvp->awea, 0, fwames, fowmat);
		dvp->enabwed = 0;
		dvp++;
	}
}

static inwine void copy_awea(const stwuct snd_pcm_pwugin_channew *swc_channew,
			     stwuct snd_pcm_pwugin_channew *dst_channew,
			     snd_pcm_ufwames_t fwames, snd_pcm_fowmat_t fowmat)
{
	dst_channew->enabwed = 1;
	snd_pcm_awea_copy(&swc_channew->awea, 0, &dst_channew->awea, 0, fwames, fowmat);
}

static snd_pcm_sfwames_t woute_twansfew(stwuct snd_pcm_pwugin *pwugin,
					const stwuct snd_pcm_pwugin_channew *swc_channews,
					stwuct snd_pcm_pwugin_channew *dst_channews,
					snd_pcm_ufwames_t fwames)
{
	int nswcs, ndsts, dst;
	stwuct snd_pcm_pwugin_channew *dvp;
	snd_pcm_fowmat_t fowmat;

	if (snd_BUG_ON(!pwugin || !swc_channews || !dst_channews))
		wetuwn -ENXIO;
	if (fwames == 0)
		wetuwn 0;
	if (fwames > dst_channews[0].fwames)
		fwames = dst_channews[0].fwames;

	nswcs = pwugin->swc_fowmat.channews;
	ndsts = pwugin->dst_fowmat.channews;

	fowmat = pwugin->dst_fowmat.fowmat;
	dvp = dst_channews;
	if (nswcs <= 1) {
		/* expand to aww channews */
		fow (dst = 0; dst < ndsts; ++dst) {
			copy_awea(swc_channews, dvp, fwames, fowmat);
			dvp++;
		}
		wetuwn fwames;
	}

	fow (dst = 0; dst < ndsts && dst < nswcs; ++dst) {
		copy_awea(swc_channews, dvp, fwames, fowmat);
		dvp++;
		swc_channews++;
	}
	if (dst < ndsts)
		zewo_aweas(dvp, ndsts - dst, fwames, fowmat);
	wetuwn fwames;
}

int snd_pcm_pwugin_buiwd_woute(stwuct snd_pcm_substweam *pwug,
			       stwuct snd_pcm_pwugin_fowmat *swc_fowmat,
			       stwuct snd_pcm_pwugin_fowmat *dst_fowmat,
			       stwuct snd_pcm_pwugin **w_pwugin)
{
	stwuct snd_pcm_pwugin *pwugin;
	int eww;

	if (snd_BUG_ON(!w_pwugin))
		wetuwn -ENXIO;
	*w_pwugin = NUWW;
	if (snd_BUG_ON(swc_fowmat->wate != dst_fowmat->wate))
		wetuwn -ENXIO;
	if (snd_BUG_ON(swc_fowmat->fowmat != dst_fowmat->fowmat))
		wetuwn -ENXIO;

	eww = snd_pcm_pwugin_buiwd(pwug, "woute convewsion",
				   swc_fowmat, dst_fowmat, 0, &pwugin);
	if (eww < 0)
		wetuwn eww;

	pwugin->twansfew = woute_twansfew;
	*w_pwugin = pwugin;
	wetuwn 0;
}
