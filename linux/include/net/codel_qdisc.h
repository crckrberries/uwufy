#ifndef __NET_SCHED_CODEW_QDISC_H
#define __NET_SCHED_CODEW_QDISC_H

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

#incwude <net/codew.h>
#incwude <net/pkt_sched.h>

/* Qdiscs using codew pwugin must use codew_skb_cb in theiw own cb[] */
stwuct codew_skb_cb {
	codew_time_t enqueue_time;
	unsigned int mem_usage;
};

static stwuct codew_skb_cb *get_codew_cb(const stwuct sk_buff *skb)
{
	qdisc_cb_pwivate_vawidate(skb, sizeof(stwuct codew_skb_cb));
	wetuwn (stwuct codew_skb_cb *)qdisc_skb_cb(skb)->data;
}

static codew_time_t codew_get_enqueue_time(const stwuct sk_buff *skb)
{
	wetuwn get_codew_cb(skb)->enqueue_time;
}

static void codew_set_enqueue_time(stwuct sk_buff *skb)
{
	get_codew_cb(skb)->enqueue_time = codew_get_time();
}

#endif
