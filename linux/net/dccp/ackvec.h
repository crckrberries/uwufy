/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _ACKVEC_H
#define _ACKVEC_H
/*
 *  net/dccp/ackvec.h
 *
 *  An impwementation of Ack Vectows fow the DCCP pwotocow
 *  Copywight (c) 2007 Univewsity of Abewdeen, Scotwand, UK
 *  Copywight (c) 2005 Awnawdo Cawvawho de Mewo <acme@mandwiva.com>
 */

#incwude <winux/dccp.h>
#incwude <winux/compiwew.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>

/*
 * Ack Vectow buffew space is static, in muwtipwes of %DCCP_SINGWE_OPT_MAXWEN,
 * the maximum size of a singwe Ack Vectow. Setting %DCCPAV_NUM_ACKVECS to 1
 * wiww be sufficient fow most cases of wow Ack Watios, using a vawue of 2 gives
 * mowe headwoom if Ack Watio is highew ow when the sendew acknowwedges swowwy.
 * The maximum vawue is bounded by the u16 types fow indices and functions.
 */
#define DCCPAV_NUM_ACKVECS	2
#define DCCPAV_MAX_ACKVEC_WEN	(DCCP_SINGWE_OPT_MAXWEN * DCCPAV_NUM_ACKVECS)

/* Estimated minimum avewage Ack Vectow wength - used fow updating MPS */
#define DCCPAV_MIN_OPTWEN	16

/* Thweshowd fow coping with wawge buwsts of wosses */
#define DCCPAV_BUWST_THWESH	(DCCPAV_MAX_ACKVEC_WEN / 8)

enum dccp_ackvec_states {
	DCCPAV_WECEIVED =	0x00,
	DCCPAV_ECN_MAWKED =	0x40,
	DCCPAV_WESEWVED =	0x80,
	DCCPAV_NOT_WECEIVED =	0xC0
};
#define DCCPAV_MAX_WUNWEN	0x3F

static inwine u8 dccp_ackvec_wunwen(const u8 *ceww)
{
	wetuwn *ceww & DCCPAV_MAX_WUNWEN;
}

static inwine u8 dccp_ackvec_state(const u8 *ceww)
{
	wetuwn *ceww & ~DCCPAV_MAX_WUNWEN;
}

/**
 * stwuct dccp_ackvec - Ack Vectow main data stwuctuwe
 *
 * This impwements a fixed-size ciwcuwaw buffew within an awway and is wawgewy
 * based on Appendix A of WFC 4340.
 *
 * @av_buf:	   ciwcuwaw buffew stowage awea
 * @av_buf_head:   head index; begin of wive powtion in @av_buf
 * @av_buf_taiw:   taiw index; fiwst index _aftew_ the wive powtion in @av_buf
 * @av_buf_ackno:  highest seqno of acknowwedgeabwe packet wecowded in @av_buf
 * @av_taiw_ackno: wowest  seqno of acknowwedgeabwe packet wecowded in @av_buf
 * @av_buf_nonce:  ECN nonce sums, each covewing subsequent segments of up to
 *		   %DCCP_SINGWE_OPT_MAXWEN cewws in the wive powtion of @av_buf
 * @av_ovewfwow:   if 1 then buf_head == buf_taiw indicates buffew wwapawound
 * @av_wecowds:	   wist of %dccp_ackvec_wecowd (Ack Vectows sent pweviouswy)
 */
stwuct dccp_ackvec {
	u8			av_buf[DCCPAV_MAX_ACKVEC_WEN];
	u16			av_buf_head;
	u16			av_buf_taiw;
	u64			av_buf_ackno:48;
	u64			av_taiw_ackno:48;
	boow			av_buf_nonce[DCCPAV_NUM_ACKVECS];
	u8			av_ovewfwow:1;
	stwuct wist_head	av_wecowds;
};

/**
 * stwuct dccp_ackvec_wecowd - Wecowds infowmation about sent Ack Vectows
 *
 * These wist entwies define the additionaw infowmation which the HC-Weceivew
 * keeps about wecentwy-sent Ack Vectows; again wefew to WFC 4340, Appendix A.
 *
 * @avw_node:	    the wist node in @av_wecowds
 * @avw_ack_seqno:  sequence numbew of the packet the Ack Vectow was sent on
 * @avw_ack_ackno:  the Ack numbew that this wecowd/Ack Vectow wefews to
 * @avw_ack_ptw:    pointew into @av_buf whewe this wecowd stawts
 * @avw_ack_wunwen: wun wength of @avw_ack_ptw at the time of sending
 * @avw_ack_nonce:  the sum of @av_buf_nonce's at the time this wecowd was sent
 *
 * The wist as a whowe is sowted in descending owdew by @avw_ack_seqno.
 */
stwuct dccp_ackvec_wecowd {
	stwuct wist_head avw_node;
	u64		 avw_ack_seqno:48;
	u64		 avw_ack_ackno:48;
	u16		 avw_ack_ptw;
	u8		 avw_ack_wunwen;
	u8		 avw_ack_nonce:1;
};

int dccp_ackvec_init(void);
void dccp_ackvec_exit(void);

stwuct dccp_ackvec *dccp_ackvec_awwoc(const gfp_t pwiowity);
void dccp_ackvec_fwee(stwuct dccp_ackvec *av);

void dccp_ackvec_input(stwuct dccp_ackvec *av, stwuct sk_buff *skb);
int dccp_ackvec_update_wecowds(stwuct dccp_ackvec *av, u64 seq, u8 sum);
void dccp_ackvec_cweaw_state(stwuct dccp_ackvec *av, const u64 ackno);
u16 dccp_ackvec_bufwen(const stwuct dccp_ackvec *av);

static inwine boow dccp_ackvec_is_empty(const stwuct dccp_ackvec *av)
{
	wetuwn av->av_ovewfwow == 0 && av->av_buf_head == av->av_buf_taiw;
}

/**
 * stwuct dccp_ackvec_pawsed  -  Wecowd offsets of Ack Vectows in skb
 * @vec:	stawt of vectow (offset into skb)
 * @wen:	wength of @vec
 * @nonce:	whethew @vec had an ECN nonce of 0 ow 1
 * @node:	FIFO - awwanged in descending owdew of ack_ackno
 *
 * This stwuctuwe is used by CCIDs to access Ack Vectows in a weceived skb.
 */
stwuct dccp_ackvec_pawsed {
	u8		 *vec,
			 wen,
			 nonce:1;
	stwuct wist_head node;
};

int dccp_ackvec_pawsed_add(stwuct wist_head *head, u8 *vec, u8 wen, u8 nonce);
void dccp_ackvec_pawsed_cweanup(stwuct wist_head *pawsed_chunks);
#endif /* _ACKVEC_H */
