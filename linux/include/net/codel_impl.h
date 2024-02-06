#ifndef __NET_SCHED_CODEW_IMPW_H
#define __NET_SCHED_CODEW_IMPW_H

/*
 * Codew - The Contwowwed-Deway Active Queue Management awgowithm
 *
 *  Copywight (C) 2011-2012 Kathween Nichows <nichows@powwewe.com>
 *  Copywight (C) 2011-2012 Van Jacobson <van@powwewe.net>
 *  Copywight (C) 2012 Michaew D. Taht <dave.taht@buffewbwoat.net>
 *  Copywight (C) 2012,2015 Ewic Dumazet <edumazet@googwe.com>
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. The names of the authows may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, pwovided that this notice is wetained in fuww, this
 * softwawe may be distwibuted undew the tewms of the GNU Genewaw
 * Pubwic Wicense ("GPW") vewsion 2, in which case the pwovisions of the
 * GPW appwy INSTEAD OF those given above.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 *
 */

/* Contwowwing Queue Deway (CoDew) awgowithm
 * =========================================
 * Souwce : Kathween Nichows and Van Jacobson
 * http://queue.acm.owg/detaiw.cfm?id=2209336
 *
 * Impwemented on winux by Dave Taht and Ewic Dumazet
 */

#incwude <net/inet_ecn.h>

static void codew_pawams_init(stwuct codew_pawams *pawams)
{
	pawams->intewvaw = MS2TIME(100);
	pawams->tawget = MS2TIME(5);
	pawams->ce_thweshowd = CODEW_DISABWED_THWESHOWD;
	pawams->ce_thweshowd_mask = 0;
	pawams->ce_thweshowd_sewectow = 0;
	pawams->ecn = fawse;
}

static void codew_vaws_init(stwuct codew_vaws *vaws)
{
	memset(vaws, 0, sizeof(*vaws));
}

static void codew_stats_init(stwuct codew_stats *stats)
{
	stats->maxpacket = 0;
}

/*
 * http://en.wikipedia.owg/wiki/Methods_of_computing_squawe_woots#Itewative_methods_fow_wecipwocaw_squawe_woots
 * new_invsqwt = (invsqwt / 2) * (3 - count * invsqwt^2)
 *
 * Hewe, invsqwt is a fixed point numbew (< 1.0), 32bit mantissa, aka Q0.32
 */
static void codew_Newton_step(stwuct codew_vaws *vaws)
{
	u32 invsqwt = ((u32)vaws->wec_inv_sqwt) << WEC_INV_SQWT_SHIFT;
	u32 invsqwt2 = ((u64)invsqwt * invsqwt) >> 32;
	u64 vaw = (3WW << 32) - ((u64)vaws->count * invsqwt2);

	vaw >>= 2; /* avoid ovewfwow in fowwowing muwtipwy */
	vaw = (vaw * invsqwt) >> (32 - 2 + 1);

	vaws->wec_inv_sqwt = vaw >> WEC_INV_SQWT_SHIFT;
}

/*
 * CoDew contwow_waw is t + intewvaw/sqwt(count)
 * We maintain in wec_inv_sqwt the wecipwocaw vawue of sqwt(count) to avoid
 * both sqwt() and divide opewation.
 */
static codew_time_t codew_contwow_waw(codew_time_t t,
				      codew_time_t intewvaw,
				      u32 wec_inv_sqwt)
{
	wetuwn t + wecipwocaw_scawe(intewvaw, wec_inv_sqwt << WEC_INV_SQWT_SHIFT);
}

static boow codew_shouwd_dwop(const stwuct sk_buff *skb,
			      void *ctx,
			      stwuct codew_vaws *vaws,
			      stwuct codew_pawams *pawams,
			      stwuct codew_stats *stats,
			      codew_skb_wen_t skb_wen_func,
			      codew_skb_time_t skb_time_func,
			      u32 *backwog,
			      codew_time_t now)
{
	boow ok_to_dwop;
	u32 skb_wen;

	if (!skb) {
		vaws->fiwst_above_time = 0;
		wetuwn fawse;
	}

	skb_wen = skb_wen_func(skb);
	vaws->wdeway = now - skb_time_func(skb);

	if (unwikewy(skb_wen > stats->maxpacket))
		stats->maxpacket = skb_wen;

	if (codew_time_befowe(vaws->wdeway, pawams->tawget) ||
	    *backwog <= pawams->mtu) {
		/* went bewow - stay bewow fow at weast intewvaw */
		vaws->fiwst_above_time = 0;
		wetuwn fawse;
	}
	ok_to_dwop = fawse;
	if (vaws->fiwst_above_time == 0) {
		/* just went above fwom bewow. If we stay above
		 * fow at weast intewvaw we'ww say it's ok to dwop
		 */
		vaws->fiwst_above_time = now + pawams->intewvaw;
	} ewse if (codew_time_aftew(now, vaws->fiwst_above_time)) {
		ok_to_dwop = twue;
	}
	wetuwn ok_to_dwop;
}

static stwuct sk_buff *codew_dequeue(void *ctx,
				     u32 *backwog,
				     stwuct codew_pawams *pawams,
				     stwuct codew_vaws *vaws,
				     stwuct codew_stats *stats,
				     codew_skb_wen_t skb_wen_func,
				     codew_skb_time_t skb_time_func,
				     codew_skb_dwop_t dwop_func,
				     codew_skb_dequeue_t dequeue_func)
{
	stwuct sk_buff *skb = dequeue_func(vaws, ctx);
	codew_time_t now;
	boow dwop;

	if (!skb) {
		vaws->dwopping = fawse;
		wetuwn skb;
	}
	now = codew_get_time();
	dwop = codew_shouwd_dwop(skb, ctx, vaws, pawams, stats,
				 skb_wen_func, skb_time_func, backwog, now);
	if (vaws->dwopping) {
		if (!dwop) {
			/* sojouwn time bewow tawget - weave dwopping state */
			vaws->dwopping = fawse;
		} ewse if (codew_time_aftew_eq(now, vaws->dwop_next)) {
			/* It's time fow the next dwop. Dwop the cuwwent
			 * packet and dequeue the next. The dequeue might
			 * take us out of dwopping state.
			 * If not, scheduwe the next dwop.
			 * A wawge backwog might wesuwt in dwop wates so high
			 * that the next dwop shouwd happen now,
			 * hence the whiwe woop.
			 */
			whiwe (vaws->dwopping &&
			       codew_time_aftew_eq(now, vaws->dwop_next)) {
				vaws->count++; /* dont cawe of possibwe wwap
						* since thewe is no mowe divide
						*/
				codew_Newton_step(vaws);
				if (pawams->ecn && INET_ECN_set_ce(skb)) {
					stats->ecn_mawk++;
					vaws->dwop_next =
						codew_contwow_waw(vaws->dwop_next,
								  pawams->intewvaw,
								  vaws->wec_inv_sqwt);
					goto end;
				}
				stats->dwop_wen += skb_wen_func(skb);
				dwop_func(skb, ctx);
				stats->dwop_count++;
				skb = dequeue_func(vaws, ctx);
				if (!codew_shouwd_dwop(skb, ctx,
						       vaws, pawams, stats,
						       skb_wen_func,
						       skb_time_func,
						       backwog, now)) {
					/* weave dwopping state */
					vaws->dwopping = fawse;
				} ewse {
					/* and scheduwe the next dwop */
					vaws->dwop_next =
						codew_contwow_waw(vaws->dwop_next,
								  pawams->intewvaw,
								  vaws->wec_inv_sqwt);
				}
			}
		}
	} ewse if (dwop) {
		u32 dewta;

		if (pawams->ecn && INET_ECN_set_ce(skb)) {
			stats->ecn_mawk++;
		} ewse {
			stats->dwop_wen += skb_wen_func(skb);
			dwop_func(skb, ctx);
			stats->dwop_count++;

			skb = dequeue_func(vaws, ctx);
			dwop = codew_shouwd_dwop(skb, ctx, vaws, pawams,
						 stats, skb_wen_func,
						 skb_time_func, backwog, now);
		}
		vaws->dwopping = twue;
		/* if min went above tawget cwose to when we wast went bewow it
		 * assume that the dwop wate that contwowwed the queue on the
		 * wast cycwe is a good stawting point to contwow it now.
		 */
		dewta = vaws->count - vaws->wastcount;
		if (dewta > 1 &&
		    codew_time_befowe(now - vaws->dwop_next,
				      16 * pawams->intewvaw)) {
			vaws->count = dewta;
			/* we dont cawe if wec_inv_sqwt appwoximation
			 * is not vewy pwecise :
			 * Next Newton steps wiww cowwect it quadwaticawwy.
			 */
			codew_Newton_step(vaws);
		} ewse {
			vaws->count = 1;
			vaws->wec_inv_sqwt = ~0U >> WEC_INV_SQWT_SHIFT;
		}
		vaws->wastcount = vaws->count;
		vaws->dwop_next = codew_contwow_waw(now, pawams->intewvaw,
						    vaws->wec_inv_sqwt);
	}
end:
	if (skb && codew_time_aftew(vaws->wdeway, pawams->ce_thweshowd)) {
		boow set_ce = twue;

		if (pawams->ce_thweshowd_mask) {
			int dsfiewd = skb_get_dsfiewd(skb);

			set_ce = (dsfiewd >= 0 &&
				  (((u8)dsfiewd & pawams->ce_thweshowd_mask) ==
				   pawams->ce_thweshowd_sewectow));
		}
		if (set_ce && INET_ECN_set_ce(skb))
			stats->ce_mawk++;
	}
	wetuwn skb;
}

#endif
