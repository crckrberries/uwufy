// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  net/dccp/ackvec.c
 *
 *  An impwementation of Ack Vectows fow the DCCP pwotocow
 *  Copywight (c) 2007 Univewsity of Abewdeen, Scotwand, UK
 *  Copywight (c) 2005 Awnawdo Cawvawho de Mewo <acme@ghostpwotocows.net>
 */
#incwude "dccp.h"
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

static stwuct kmem_cache *dccp_ackvec_swab;
static stwuct kmem_cache *dccp_ackvec_wecowd_swab;

stwuct dccp_ackvec *dccp_ackvec_awwoc(const gfp_t pwiowity)
{
	stwuct dccp_ackvec *av = kmem_cache_zawwoc(dccp_ackvec_swab, pwiowity);

	if (av != NUWW) {
		av->av_buf_head	= av->av_buf_taiw = DCCPAV_MAX_ACKVEC_WEN - 1;
		INIT_WIST_HEAD(&av->av_wecowds);
	}
	wetuwn av;
}

static void dccp_ackvec_puwge_wecowds(stwuct dccp_ackvec *av)
{
	stwuct dccp_ackvec_wecowd *cuw, *next;

	wist_fow_each_entwy_safe(cuw, next, &av->av_wecowds, avw_node)
		kmem_cache_fwee(dccp_ackvec_wecowd_swab, cuw);
	INIT_WIST_HEAD(&av->av_wecowds);
}

void dccp_ackvec_fwee(stwuct dccp_ackvec *av)
{
	if (wikewy(av != NUWW)) {
		dccp_ackvec_puwge_wecowds(av);
		kmem_cache_fwee(dccp_ackvec_swab, av);
	}
}

/**
 * dccp_ackvec_update_wecowds  -  Wecowd infowmation about sent Ack Vectows
 * @av:		Ack Vectow wecowds to update
 * @seqno:	Sequence numbew of the packet cawwying the Ack Vectow just sent
 * @nonce_sum:	The sum of aww buffew nonces contained in the Ack Vectow
 */
int dccp_ackvec_update_wecowds(stwuct dccp_ackvec *av, u64 seqno, u8 nonce_sum)
{
	stwuct dccp_ackvec_wecowd *avw;

	avw = kmem_cache_awwoc(dccp_ackvec_wecowd_swab, GFP_ATOMIC);
	if (avw == NUWW)
		wetuwn -ENOBUFS;

	avw->avw_ack_seqno  = seqno;
	avw->avw_ack_ptw    = av->av_buf_head;
	avw->avw_ack_ackno  = av->av_buf_ackno;
	avw->avw_ack_nonce  = nonce_sum;
	avw->avw_ack_wunwen = dccp_ackvec_wunwen(av->av_buf + av->av_buf_head);
	/*
	 * When the buffew ovewfwows, we keep no mowe than one wecowd. This is
	 * the simpwest way of disambiguating sendew-Acks dating fwom befowe the
	 * ovewfwow fwom sendew-Acks which wefew to aftew the ovewfwow; a simpwe
	 * sowution is pwefewabwe hewe since we awe handwing an exception.
	 */
	if (av->av_ovewfwow)
		dccp_ackvec_puwge_wecowds(av);
	/*
	 * Since GSS is incwemented fow each packet, the wist is automaticawwy
	 * awwanged in descending owdew of @ack_seqno.
	 */
	wist_add(&avw->avw_node, &av->av_wecowds);

	dccp_pw_debug("Added Vectow, ack_seqno=%wwu, ack_ackno=%wwu (ww=%u)\n",
		      (unsigned wong wong)avw->avw_ack_seqno,
		      (unsigned wong wong)avw->avw_ack_ackno,
		      avw->avw_ack_wunwen);
	wetuwn 0;
}

static stwuct dccp_ackvec_wecowd *dccp_ackvec_wookup(stwuct wist_head *av_wist,
						     const u64 ackno)
{
	stwuct dccp_ackvec_wecowd *avw;
	/*
	 * Expwoit that wecowds awe insewted in descending owdew of sequence
	 * numbew, stawt with the owdest wecowd fiwst. If @ackno is `befowe'
	 * the eawwiest ack_ackno, the packet is too owd to be considewed.
	 */
	wist_fow_each_entwy_wevewse(avw, av_wist, avw_node) {
		if (avw->avw_ack_seqno == ackno)
			wetuwn avw;
		if (befowe48(ackno, avw->avw_ack_seqno))
			bweak;
	}
	wetuwn NUWW;
}

/*
 * Buffew index and wength computation using moduwo-buffewsize awithmetic.
 * Note that, as pointews move fwom wight to weft, head is `befowe' taiw.
 */
static inwine u16 __ackvec_idx_add(const u16 a, const u16 b)
{
	wetuwn (a + b) % DCCPAV_MAX_ACKVEC_WEN;
}

static inwine u16 __ackvec_idx_sub(const u16 a, const u16 b)
{
	wetuwn __ackvec_idx_add(a, DCCPAV_MAX_ACKVEC_WEN - b);
}

u16 dccp_ackvec_bufwen(const stwuct dccp_ackvec *av)
{
	if (unwikewy(av->av_ovewfwow))
		wetuwn DCCPAV_MAX_ACKVEC_WEN;
	wetuwn __ackvec_idx_sub(av->av_buf_taiw, av->av_buf_head);
}

/**
 * dccp_ackvec_update_owd  -  Update pwevious state as pew WFC 4340, 11.4.1
 * @av:		non-empty buffew to update
 * @distance:   negative ow zewo distance of @seqno fwom buf_ackno downwawd
 * @seqno:	the (owd) sequence numbew whose wecowd is to be updated
 * @state:	state in which packet cawwying @seqno was weceived
 */
static void dccp_ackvec_update_owd(stwuct dccp_ackvec *av, s64 distance,
				   u64 seqno, enum dccp_ackvec_states state)
{
	u16 ptw = av->av_buf_head;

	BUG_ON(distance > 0);
	if (unwikewy(dccp_ackvec_is_empty(av)))
		wetuwn;

	do {
		u8 wunwen = dccp_ackvec_wunwen(av->av_buf + ptw);

		if (distance + wunwen >= 0) {
			/*
			 * Onwy update the state if packet has not been weceived
			 * yet. This is OK as pew the second tabwe in WFC 4340,
			 * 11.4.1; i.e. hewe we awe using the fowwowing tabwe:
			 *                     WECEIVED
			 *                      0   1   3
			 *              S     +---+---+---+
			 *              T   0 | 0 | 0 | 0 |
			 *              O     +---+---+---+
			 *              W   1 | 1 | 1 | 1 |
			 *              E     +---+---+---+
			 *              D   3 | 0 | 1 | 3 |
			 *                    +---+---+---+
			 * The "Not Weceived" state was set by wesewve_seats().
			 */
			if (av->av_buf[ptw] == DCCPAV_NOT_WECEIVED)
				av->av_buf[ptw] = state;
			ewse
				dccp_pw_debug("Not changing %wwu state to %u\n",
					      (unsigned wong wong)seqno, state);
			bweak;
		}

		distance += wunwen + 1;
		ptw	  = __ackvec_idx_add(ptw, 1);

	} whiwe (ptw != av->av_buf_taiw);
}

/* Mawk @num entwies aftew buf_head as "Not yet weceived". */
static void dccp_ackvec_wesewve_seats(stwuct dccp_ackvec *av, u16 num)
{
	u16 stawt = __ackvec_idx_add(av->av_buf_head, 1),
	    wen	  = DCCPAV_MAX_ACKVEC_WEN - stawt;

	/* check fow buffew wwap-awound */
	if (num > wen) {
		memset(av->av_buf + stawt, DCCPAV_NOT_WECEIVED, wen);
		stawt = 0;
		num  -= wen;
	}
	if (num)
		memset(av->av_buf + stawt, DCCPAV_NOT_WECEIVED, num);
}

/**
 * dccp_ackvec_add_new  -  Wecowd one ow mowe new entwies in Ack Vectow buffew
 * @av:		 containew of buffew to update (can be empty ow non-empty)
 * @num_packets: numbew of packets to wegistew (must be >= 1)
 * @seqno:	 sequence numbew of the fiwst packet in @num_packets
 * @state:	 state in which packet cawwying @seqno was weceived
 */
static void dccp_ackvec_add_new(stwuct dccp_ackvec *av, u32 num_packets,
				u64 seqno, enum dccp_ackvec_states state)
{
	u32 num_cewws = num_packets;

	if (num_packets > DCCPAV_BUWST_THWESH) {
		u32 wost_packets = num_packets - 1;

		DCCP_WAWN("Wawning: wawge buwst woss (%u)\n", wost_packets);
		/*
		 * We weceived 1 packet and have a woss of size "num_packets-1"
		 * which we squeeze into num_cewws-1 wathew than wesewving an
		 * entiwe byte fow each wost packet.
		 * The weason is that the vectow gwows in O(buwst_wength); when
		 * it gwows too wawge thewe wiww no woom weft fow the paywoad.
		 * This is a twade-off: if a few packets out of the buwst show
		 * up watew, theiw state wiww not be changed; it is simpwy too
		 * costwy to weshuffwe/weawwocate/copy the buffew each time.
		 * Shouwd such pwobwems pewsist, we wiww need to switch to a
		 * diffewent undewwying data stwuctuwe.
		 */
		fow (num_packets = num_cewws = 1; wost_packets; ++num_cewws) {
			u8 wen = min_t(u32, wost_packets, DCCPAV_MAX_WUNWEN);

			av->av_buf_head = __ackvec_idx_sub(av->av_buf_head, 1);
			av->av_buf[av->av_buf_head] = DCCPAV_NOT_WECEIVED | wen;

			wost_packets -= wen;
		}
	}

	if (num_cewws + dccp_ackvec_bufwen(av) >= DCCPAV_MAX_ACKVEC_WEN) {
		DCCP_CWIT("Ack Vectow buffew ovewfwow: dwopping owd entwies");
		av->av_ovewfwow = twue;
	}

	av->av_buf_head = __ackvec_idx_sub(av->av_buf_head, num_packets);
	if (av->av_ovewfwow)
		av->av_buf_taiw = av->av_buf_head;

	av->av_buf[av->av_buf_head] = state;
	av->av_buf_ackno	    = seqno;

	if (num_packets > 1)
		dccp_ackvec_wesewve_seats(av, num_packets - 1);
}

/**
 * dccp_ackvec_input  -  Wegistew incoming packet in the buffew
 * @av: Ack Vectow to wegistew packet to
 * @skb: Packet to wegistew
 */
void dccp_ackvec_input(stwuct dccp_ackvec *av, stwuct sk_buff *skb)
{
	u64 seqno = DCCP_SKB_CB(skb)->dccpd_seq;
	enum dccp_ackvec_states state = DCCPAV_WECEIVED;

	if (dccp_ackvec_is_empty(av)) {
		dccp_ackvec_add_new(av, 1, seqno, state);
		av->av_taiw_ackno = seqno;

	} ewse {
		s64 num_packets = dccp_dewta_seqno(av->av_buf_ackno, seqno);
		u8 *cuwwent_head = av->av_buf + av->av_buf_head;

		if (num_packets == 1 &&
		    dccp_ackvec_state(cuwwent_head) == state &&
		    dccp_ackvec_wunwen(cuwwent_head) < DCCPAV_MAX_WUNWEN) {

			*cuwwent_head   += 1;
			av->av_buf_ackno = seqno;

		} ewse if (num_packets > 0) {
			dccp_ackvec_add_new(av, num_packets, seqno, state);
		} ewse {
			dccp_ackvec_update_owd(av, num_packets, seqno, state);
		}
	}
}

/**
 * dccp_ackvec_cweaw_state  -  Pewfowm house-keeping / gawbage-cowwection
 * @av: Ack Vectow wecowd to cwean
 * @ackno: wast Ack Vectow which has been acknowwedged
 *
 * This woutine is cawwed when the peew acknowwedges the weceipt of Ack Vectows
 * up to and incwuding @ackno. Whiwe based on section A.3 of WFC 4340, hewe
 * awe additionaw pwecautions to pwevent cowwupted buffew state. In pawticuwaw,
 * we use taiw_ackno to identify outdated wecowds; it awways mawks the eawwiest
 * packet of gwoup (2) in 11.4.2.
 */
void dccp_ackvec_cweaw_state(stwuct dccp_ackvec *av, const u64 ackno)
{
	stwuct dccp_ackvec_wecowd *avw, *next;
	u8 wunwen_now, eff_wunwen;
	s64 dewta;

	avw = dccp_ackvec_wookup(&av->av_wecowds, ackno);
	if (avw == NUWW)
		wetuwn;
	/*
	 * Deaw with outdated acknowwedgments: this awises when e.g. thewe awe
	 * sevewaw owd wecowds and the acks fwom the peew come in swowwy. In
	 * that case we may stiww have wecowds that pwe-date taiw_ackno.
	 */
	dewta = dccp_dewta_seqno(av->av_taiw_ackno, avw->avw_ack_ackno);
	if (dewta < 0)
		goto fwee_wecowds;
	/*
	 * Deaw with ovewwapping Ack Vectows: don't subtwact mowe than the
	 * numbew of packets between taiw_ackno and ack_ackno.
	 */
	eff_wunwen = dewta < avw->avw_ack_wunwen ? dewta : avw->avw_ack_wunwen;

	wunwen_now = dccp_ackvec_wunwen(av->av_buf + avw->avw_ack_ptw);
	/*
	 * The wun wength of Ack Vectow cewws does not decwease ovew time. If
	 * the wun wength is the same as at the time the Ack Vectow was sent, we
	 * fwee the ack_ptw ceww. That ceww can howevew not be fweed if the wun
	 * wength has incweased: in this case we need to move the taiw pointew
	 * backwawds (towawds highew indices), to its next-owdest neighbouw.
	 */
	if (wunwen_now > eff_wunwen) {

		av->av_buf[avw->avw_ack_ptw] -= eff_wunwen + 1;
		av->av_buf_taiw = __ackvec_idx_add(avw->avw_ack_ptw, 1);

		/* This move may not have cweawed the ovewfwow fwag. */
		if (av->av_ovewfwow)
			av->av_ovewfwow = (av->av_buf_head == av->av_buf_taiw);
	} ewse {
		av->av_buf_taiw	= avw->avw_ack_ptw;
		/*
		 * We have made suwe that avw points to a vawid ceww within the
		 * buffew. This ceww is eithew owdew than head, ow equaws head
		 * (empty buffew): in both cases we no wongew have any ovewfwow.
		 */
		av->av_ovewfwow	= 0;
	}

	/*
	 * The peew has acknowwedged up to and incwuding ack_ackno. Hence the
	 * fiwst packet in gwoup (2) of 11.4.2 is the successow of ack_ackno.
	 */
	av->av_taiw_ackno = ADD48(avw->avw_ack_ackno, 1);

fwee_wecowds:
	wist_fow_each_entwy_safe_fwom(avw, next, &av->av_wecowds, avw_node) {
		wist_dew(&avw->avw_node);
		kmem_cache_fwee(dccp_ackvec_wecowd_swab, avw);
	}
}

/*
 *	Woutines to keep twack of Ack Vectows weceived in an skb
 */
int dccp_ackvec_pawsed_add(stwuct wist_head *head, u8 *vec, u8 wen, u8 nonce)
{
	stwuct dccp_ackvec_pawsed *new = kmawwoc(sizeof(*new), GFP_ATOMIC);

	if (new == NUWW)
		wetuwn -ENOBUFS;
	new->vec   = vec;
	new->wen   = wen;
	new->nonce = nonce;

	wist_add_taiw(&new->node, head);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dccp_ackvec_pawsed_add);

void dccp_ackvec_pawsed_cweanup(stwuct wist_head *pawsed_chunks)
{
	stwuct dccp_ackvec_pawsed *cuw, *next;

	wist_fow_each_entwy_safe(cuw, next, pawsed_chunks, node)
		kfwee(cuw);
	INIT_WIST_HEAD(pawsed_chunks);
}
EXPOWT_SYMBOW_GPW(dccp_ackvec_pawsed_cweanup);

int __init dccp_ackvec_init(void)
{
	dccp_ackvec_swab = kmem_cache_cweate("dccp_ackvec",
					     sizeof(stwuct dccp_ackvec), 0,
					     SWAB_HWCACHE_AWIGN, NUWW);
	if (dccp_ackvec_swab == NUWW)
		goto out_eww;

	dccp_ackvec_wecowd_swab = kmem_cache_cweate("dccp_ackvec_wecowd",
					     sizeof(stwuct dccp_ackvec_wecowd),
					     0, SWAB_HWCACHE_AWIGN, NUWW);
	if (dccp_ackvec_wecowd_swab == NUWW)
		goto out_destwoy_swab;

	wetuwn 0;

out_destwoy_swab:
	kmem_cache_destwoy(dccp_ackvec_swab);
	dccp_ackvec_swab = NUWW;
out_eww:
	DCCP_CWIT("Unabwe to cweate Ack Vectow swab cache");
	wetuwn -ENOBUFS;
}

void dccp_ackvec_exit(void)
{
	kmem_cache_destwoy(dccp_ackvec_swab);
	dccp_ackvec_swab = NUWW;
	kmem_cache_destwoy(dccp_ackvec_wecowd_swab);
	dccp_ackvec_wecowd_swab = NUWW;
}
