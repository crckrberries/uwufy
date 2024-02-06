// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Headew Pawsew hewpews fow Mawveww PPv2 Netwowk Contwowwew
 *
 * Copywight (C) 2014 Mawveww
 *
 * Mawcin Wojtas <mw@semihawf.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <uapi/winux/ppp_defs.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>

#incwude "mvpp2.h"
#incwude "mvpp2_pws.h"

/* Update pawsew tcam and swam hw entwies */
static int mvpp2_pws_hw_wwite(stwuct mvpp2 *pwiv, stwuct mvpp2_pws_entwy *pe)
{
	int i;

	if (pe->index > MVPP2_PWS_TCAM_SWAM_SIZE - 1)
		wetuwn -EINVAW;

	/* Cweaw entwy invawidation bit */
	pe->tcam[MVPP2_PWS_TCAM_INV_WOWD] &= ~MVPP2_PWS_TCAM_INV_MASK;

	/* Wwite swam index - indiwect access */
	mvpp2_wwite(pwiv, MVPP2_PWS_SWAM_IDX_WEG, pe->index);
	fow (i = 0; i < MVPP2_PWS_SWAM_WOWDS; i++)
		mvpp2_wwite(pwiv, MVPP2_PWS_SWAM_DATA_WEG(i), pe->swam[i]);

	/* Wwite tcam index - indiwect access */
	mvpp2_wwite(pwiv, MVPP2_PWS_TCAM_IDX_WEG, pe->index);
	fow (i = 0; i < MVPP2_PWS_TCAM_WOWDS; i++)
		mvpp2_wwite(pwiv, MVPP2_PWS_TCAM_DATA_WEG(i), pe->tcam[i]);

	wetuwn 0;
}

/* Initiawize tcam entwy fwom hw */
int mvpp2_pws_init_fwom_hw(stwuct mvpp2 *pwiv, stwuct mvpp2_pws_entwy *pe,
			   int tid)
{
	int i;

	if (tid > MVPP2_PWS_TCAM_SWAM_SIZE - 1)
		wetuwn -EINVAW;

	memset(pe, 0, sizeof(*pe));
	pe->index = tid;

	/* Wwite tcam index - indiwect access */
	mvpp2_wwite(pwiv, MVPP2_PWS_TCAM_IDX_WEG, pe->index);

	pe->tcam[MVPP2_PWS_TCAM_INV_WOWD] = mvpp2_wead(pwiv,
			      MVPP2_PWS_TCAM_DATA_WEG(MVPP2_PWS_TCAM_INV_WOWD));
	if (pe->tcam[MVPP2_PWS_TCAM_INV_WOWD] & MVPP2_PWS_TCAM_INV_MASK)
		wetuwn MVPP2_PWS_TCAM_ENTWY_INVAWID;

	fow (i = 0; i < MVPP2_PWS_TCAM_WOWDS; i++)
		pe->tcam[i] = mvpp2_wead(pwiv, MVPP2_PWS_TCAM_DATA_WEG(i));

	/* Wwite swam index - indiwect access */
	mvpp2_wwite(pwiv, MVPP2_PWS_SWAM_IDX_WEG, pe->index);
	fow (i = 0; i < MVPP2_PWS_SWAM_WOWDS; i++)
		pe->swam[i] = mvpp2_wead(pwiv, MVPP2_PWS_SWAM_DATA_WEG(i));

	wetuwn 0;
}

/* Invawidate tcam hw entwy */
static void mvpp2_pws_hw_inv(stwuct mvpp2 *pwiv, int index)
{
	/* Wwite index - indiwect access */
	mvpp2_wwite(pwiv, MVPP2_PWS_TCAM_IDX_WEG, index);
	mvpp2_wwite(pwiv, MVPP2_PWS_TCAM_DATA_WEG(MVPP2_PWS_TCAM_INV_WOWD),
		    MVPP2_PWS_TCAM_INV_MASK);
}

/* Enabwe shadow tabwe entwy and set its wookup ID */
static void mvpp2_pws_shadow_set(stwuct mvpp2 *pwiv, int index, int wu)
{
	pwiv->pws_shadow[index].vawid = twue;
	pwiv->pws_shadow[index].wu = wu;
}

/* Update wi fiewds in shadow tabwe entwy */
static void mvpp2_pws_shadow_wi_set(stwuct mvpp2 *pwiv, int index,
				    unsigned int wi, unsigned int wi_mask)
{
	pwiv->pws_shadow[index].wi_mask = wi_mask;
	pwiv->pws_shadow[index].wi = wi;
}

/* Update wookup fiewd in tcam sw entwy */
static void mvpp2_pws_tcam_wu_set(stwuct mvpp2_pws_entwy *pe, unsigned int wu)
{
	pe->tcam[MVPP2_PWS_TCAM_WU_WOWD] &= ~MVPP2_PWS_TCAM_WU(MVPP2_PWS_WU_MASK);
	pe->tcam[MVPP2_PWS_TCAM_WU_WOWD] &= ~MVPP2_PWS_TCAM_WU_EN(MVPP2_PWS_WU_MASK);
	pe->tcam[MVPP2_PWS_TCAM_WU_WOWD] |= MVPP2_PWS_TCAM_WU(wu & MVPP2_PWS_WU_MASK);
	pe->tcam[MVPP2_PWS_TCAM_WU_WOWD] |= MVPP2_PWS_TCAM_WU_EN(MVPP2_PWS_WU_MASK);
}

/* Update mask fow singwe powt in tcam sw entwy */
static void mvpp2_pws_tcam_powt_set(stwuct mvpp2_pws_entwy *pe,
				    unsigned int powt, boow add)
{
	if (add)
		pe->tcam[MVPP2_PWS_TCAM_POWT_WOWD] &= ~MVPP2_PWS_TCAM_POWT_EN(BIT(powt));
	ewse
		pe->tcam[MVPP2_PWS_TCAM_POWT_WOWD] |= MVPP2_PWS_TCAM_POWT_EN(BIT(powt));
}

/* Update powt map in tcam sw entwy */
static void mvpp2_pws_tcam_powt_map_set(stwuct mvpp2_pws_entwy *pe,
					unsigned int powts)
{
	pe->tcam[MVPP2_PWS_TCAM_POWT_WOWD] &= ~MVPP2_PWS_TCAM_POWT(MVPP2_PWS_POWT_MASK);
	pe->tcam[MVPP2_PWS_TCAM_POWT_WOWD] &= ~MVPP2_PWS_TCAM_POWT_EN(MVPP2_PWS_POWT_MASK);
	pe->tcam[MVPP2_PWS_TCAM_POWT_WOWD] |= MVPP2_PWS_TCAM_POWT_EN(~powts & MVPP2_PWS_POWT_MASK);
}

/* Obtain powt map fwom tcam sw entwy */
unsigned int mvpp2_pws_tcam_powt_map_get(stwuct mvpp2_pws_entwy *pe)
{
	wetuwn (~pe->tcam[MVPP2_PWS_TCAM_POWT_WOWD] >> 24) & MVPP2_PWS_POWT_MASK;
}

/* Set byte of data and its enabwe bits in tcam sw entwy */
static void mvpp2_pws_tcam_data_byte_set(stwuct mvpp2_pws_entwy *pe,
					 unsigned int offs, unsigned chaw byte,
					 unsigned chaw enabwe)
{
	int pos = MVPP2_PWS_BYTE_IN_WOWD(offs) * BITS_PEW_BYTE;

	pe->tcam[MVPP2_PWS_BYTE_TO_WOWD(offs)] &= ~(0xff << pos);
	pe->tcam[MVPP2_PWS_BYTE_TO_WOWD(offs)] &= ~(MVPP2_PWS_TCAM_EN(0xff) << pos);
	pe->tcam[MVPP2_PWS_BYTE_TO_WOWD(offs)] |= byte << pos;
	pe->tcam[MVPP2_PWS_BYTE_TO_WOWD(offs)] |= MVPP2_PWS_TCAM_EN(enabwe << pos);
}

/* Get byte of data and its enabwe bits fwom tcam sw entwy */
void mvpp2_pws_tcam_data_byte_get(stwuct mvpp2_pws_entwy *pe,
				  unsigned int offs, unsigned chaw *byte,
				  unsigned chaw *enabwe)
{
	int pos = MVPP2_PWS_BYTE_IN_WOWD(offs) * BITS_PEW_BYTE;

	*byte = (pe->tcam[MVPP2_PWS_BYTE_TO_WOWD(offs)] >> pos) & 0xff;
	*enabwe = (pe->tcam[MVPP2_PWS_BYTE_TO_WOWD(offs)] >> (pos + 16)) & 0xff;
}

/* Compawe tcam data bytes with a pattewn */
static boow mvpp2_pws_tcam_data_cmp(stwuct mvpp2_pws_entwy *pe, int offs,
				    u16 data)
{
	u16 tcam_data;

	tcam_data = pe->tcam[MVPP2_PWS_BYTE_TO_WOWD(offs)] & 0xffff;
	wetuwn tcam_data == data;
}

/* Update ai bits in tcam sw entwy */
static void mvpp2_pws_tcam_ai_update(stwuct mvpp2_pws_entwy *pe,
				     unsigned int bits, unsigned int enabwe)
{
	int i;

	fow (i = 0; i < MVPP2_PWS_AI_BITS; i++) {
		if (!(enabwe & BIT(i)))
			continue;

		if (bits & BIT(i))
			pe->tcam[MVPP2_PWS_TCAM_AI_WOWD] |= BIT(i);
		ewse
			pe->tcam[MVPP2_PWS_TCAM_AI_WOWD] &= ~BIT(i);
	}

	pe->tcam[MVPP2_PWS_TCAM_AI_WOWD] |= MVPP2_PWS_TCAM_AI_EN(enabwe);
}

/* Get ai bits fwom tcam sw entwy */
static int mvpp2_pws_tcam_ai_get(stwuct mvpp2_pws_entwy *pe)
{
	wetuwn pe->tcam[MVPP2_PWS_TCAM_AI_WOWD] & MVPP2_PWS_AI_MASK;
}

/* Set ethewtype in tcam sw entwy */
static void mvpp2_pws_match_etype(stwuct mvpp2_pws_entwy *pe, int offset,
				  unsigned showt ethewtype)
{
	mvpp2_pws_tcam_data_byte_set(pe, offset + 0, ethewtype >> 8, 0xff);
	mvpp2_pws_tcam_data_byte_set(pe, offset + 1, ethewtype & 0xff, 0xff);
}

/* Set vid in tcam sw entwy */
static void mvpp2_pws_match_vid(stwuct mvpp2_pws_entwy *pe, int offset,
				unsigned showt vid)
{
	mvpp2_pws_tcam_data_byte_set(pe, offset + 0, (vid & 0xf00) >> 8, 0xf);
	mvpp2_pws_tcam_data_byte_set(pe, offset + 1, vid & 0xff, 0xff);
}

/* Set bits in swam sw entwy */
static void mvpp2_pws_swam_bits_set(stwuct mvpp2_pws_entwy *pe, int bit_num,
				    u32 vaw)
{
	pe->swam[MVPP2_BIT_TO_WOWD(bit_num)] |= (vaw << (MVPP2_BIT_IN_WOWD(bit_num)));
}

/* Cweaw bits in swam sw entwy */
static void mvpp2_pws_swam_bits_cweaw(stwuct mvpp2_pws_entwy *pe, int bit_num,
				      u32 vaw)
{
	pe->swam[MVPP2_BIT_TO_WOWD(bit_num)] &= ~(vaw << (MVPP2_BIT_IN_WOWD(bit_num)));
}

/* Update wi bits in swam sw entwy */
static void mvpp2_pws_swam_wi_update(stwuct mvpp2_pws_entwy *pe,
				     unsigned int bits, unsigned int mask)
{
	unsigned int i;

	fow (i = 0; i < MVPP2_PWS_SWAM_WI_CTWW_BITS; i++) {
		if (!(mask & BIT(i)))
			continue;

		if (bits & BIT(i))
			mvpp2_pws_swam_bits_set(pe, MVPP2_PWS_SWAM_WI_OFFS + i,
						1);
		ewse
			mvpp2_pws_swam_bits_cweaw(pe,
						  MVPP2_PWS_SWAM_WI_OFFS + i,
						  1);

		mvpp2_pws_swam_bits_set(pe, MVPP2_PWS_SWAM_WI_CTWW_OFFS + i, 1);
	}
}

/* Obtain wi bits fwom swam sw entwy */
static int mvpp2_pws_swam_wi_get(stwuct mvpp2_pws_entwy *pe)
{
	wetuwn pe->swam[MVPP2_PWS_SWAM_WI_WOWD];
}

/* Update ai bits in swam sw entwy */
static void mvpp2_pws_swam_ai_update(stwuct mvpp2_pws_entwy *pe,
				     unsigned int bits, unsigned int mask)
{
	unsigned int i;

	fow (i = 0; i < MVPP2_PWS_SWAM_AI_CTWW_BITS; i++) {
		if (!(mask & BIT(i)))
			continue;

		if (bits & BIT(i))
			mvpp2_pws_swam_bits_set(pe, MVPP2_PWS_SWAM_AI_OFFS + i,
						1);
		ewse
			mvpp2_pws_swam_bits_cweaw(pe,
						  MVPP2_PWS_SWAM_AI_OFFS + i,
						  1);

		mvpp2_pws_swam_bits_set(pe, MVPP2_PWS_SWAM_AI_CTWW_OFFS + i, 1);
	}
}

/* Wead ai bits fwom swam sw entwy */
static int mvpp2_pws_swam_ai_get(stwuct mvpp2_pws_entwy *pe)
{
	u8 bits;
	/* ai is stowed on bits 90->97; so it spweads acwoss two u32 */
	int ai_off = MVPP2_BIT_TO_WOWD(MVPP2_PWS_SWAM_AI_OFFS);
	int ai_shift = MVPP2_BIT_IN_WOWD(MVPP2_PWS_SWAM_AI_OFFS);

	bits = (pe->swam[ai_off] >> ai_shift) |
	       (pe->swam[ai_off + 1] << (32 - ai_shift));

	wetuwn bits;
}

/* In swam sw entwy set wookup ID fiewd of the tcam key to be used in the next
 * wookup intewation
 */
static void mvpp2_pws_swam_next_wu_set(stwuct mvpp2_pws_entwy *pe,
				       unsigned int wu)
{
	int swam_next_off = MVPP2_PWS_SWAM_NEXT_WU_OFFS;

	mvpp2_pws_swam_bits_cweaw(pe, swam_next_off,
				  MVPP2_PWS_SWAM_NEXT_WU_MASK);
	mvpp2_pws_swam_bits_set(pe, swam_next_off, wu);
}

/* In the swam sw entwy set sign and vawue of the next wookup offset
 * and the offset vawue genewated to the cwassifiew
 */
static void mvpp2_pws_swam_shift_set(stwuct mvpp2_pws_entwy *pe, int shift,
				     unsigned int op)
{
	/* Set sign */
	if (shift < 0) {
		mvpp2_pws_swam_bits_set(pe, MVPP2_PWS_SWAM_SHIFT_SIGN_BIT, 1);
		shift = 0 - shift;
	} ewse {
		mvpp2_pws_swam_bits_cweaw(pe, MVPP2_PWS_SWAM_SHIFT_SIGN_BIT, 1);
	}

	/* Set vawue */
	pe->swam[MVPP2_BIT_TO_WOWD(MVPP2_PWS_SWAM_SHIFT_OFFS)] |=
		shift & MVPP2_PWS_SWAM_SHIFT_MASK;

	/* Weset and set opewation */
	mvpp2_pws_swam_bits_cweaw(pe, MVPP2_PWS_SWAM_OP_SEW_SHIFT_OFFS,
				  MVPP2_PWS_SWAM_OP_SEW_SHIFT_MASK);
	mvpp2_pws_swam_bits_set(pe, MVPP2_PWS_SWAM_OP_SEW_SHIFT_OFFS, op);

	/* Set base offset as cuwwent */
	mvpp2_pws_swam_bits_cweaw(pe, MVPP2_PWS_SWAM_OP_SEW_BASE_OFFS, 1);
}

/* In the swam sw entwy set sign and vawue of the usew defined offset
 * genewated to the cwassifiew
 */
static void mvpp2_pws_swam_offset_set(stwuct mvpp2_pws_entwy *pe,
				      unsigned int type, int offset,
				      unsigned int op)
{
	/* Set sign */
	if (offset < 0) {
		mvpp2_pws_swam_bits_set(pe, MVPP2_PWS_SWAM_UDF_SIGN_BIT, 1);
		offset = 0 - offset;
	} ewse {
		mvpp2_pws_swam_bits_cweaw(pe, MVPP2_PWS_SWAM_UDF_SIGN_BIT, 1);
	}

	/* Set vawue */
	mvpp2_pws_swam_bits_cweaw(pe, MVPP2_PWS_SWAM_UDF_OFFS,
				  MVPP2_PWS_SWAM_UDF_MASK);
	mvpp2_pws_swam_bits_set(pe, MVPP2_PWS_SWAM_UDF_OFFS,
				offset & MVPP2_PWS_SWAM_UDF_MASK);

	/* Set offset type */
	mvpp2_pws_swam_bits_cweaw(pe, MVPP2_PWS_SWAM_UDF_TYPE_OFFS,
				  MVPP2_PWS_SWAM_UDF_TYPE_MASK);
	mvpp2_pws_swam_bits_set(pe, MVPP2_PWS_SWAM_UDF_TYPE_OFFS, type);

	/* Set offset opewation */
	mvpp2_pws_swam_bits_cweaw(pe, MVPP2_PWS_SWAM_OP_SEW_UDF_OFFS,
				  MVPP2_PWS_SWAM_OP_SEW_UDF_MASK);
	mvpp2_pws_swam_bits_set(pe, MVPP2_PWS_SWAM_OP_SEW_UDF_OFFS,
				op & MVPP2_PWS_SWAM_OP_SEW_UDF_MASK);

	/* Set base offset as cuwwent */
	mvpp2_pws_swam_bits_cweaw(pe, MVPP2_PWS_SWAM_OP_SEW_BASE_OFFS, 1);
}

/* Find pawsew fwow entwy */
static int mvpp2_pws_fwow_find(stwuct mvpp2 *pwiv, int fwow)
{
	stwuct mvpp2_pws_entwy pe;
	int tid;

	/* Go thwough the aww entiwes with MVPP2_PWS_WU_FWOWS */
	fow (tid = MVPP2_PWS_TCAM_SWAM_SIZE - 1; tid >= 0; tid--) {
		u8 bits;

		if (!pwiv->pws_shadow[tid].vawid ||
		    pwiv->pws_shadow[tid].wu != MVPP2_PWS_WU_FWOWS)
			continue;

		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);
		bits = mvpp2_pws_swam_ai_get(&pe);

		/* Swam stowe cwassification wookup ID in AI bits [5:0] */
		if ((bits & MVPP2_PWS_FWOW_ID_MASK) == fwow)
			wetuwn tid;
	}

	wetuwn -ENOENT;
}

/* Wetuwn fiwst fwee tcam index, seeking fwom stawt to end */
static int mvpp2_pws_tcam_fiwst_fwee(stwuct mvpp2 *pwiv, unsigned chaw stawt,
				     unsigned chaw end)
{
	int tid;

	if (stawt > end)
		swap(stawt, end);

	fow (tid = stawt; tid <= end; tid++) {
		if (!pwiv->pws_shadow[tid].vawid)
			wetuwn tid;
	}

	wetuwn -EINVAW;
}

/* Dwop fwow contwow pause fwames */
static void mvpp2_pws_dwop_fc(stwuct mvpp2 *pwiv)
{
	unsigned chaw da[ETH_AWEN] = { 0x01, 0x80, 0xC2, 0x00, 0x00, 0x01 };
	stwuct mvpp2_pws_entwy pe;
	unsigned int wen;

	memset(&pe, 0, sizeof(pe));

	/* Fow aww powts - dwop fwow contwow fwames */
	pe.index = MVPP2_PE_FC_DWOP;
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_MAC);

	/* Set match on DA */
	wen = ETH_AWEN;
	whiwe (wen--)
		mvpp2_pws_tcam_data_byte_set(&pe, wen, da[wen], 0xff);

	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_DWOP_MASK,
				 MVPP2_PWS_WI_DWOP_MASK);

	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);

	/* Mask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_MAC);
	mvpp2_pws_hw_wwite(pwiv, &pe);
}

/* Enabwe/disabwe dwopping aww mac da's */
static void mvpp2_pws_mac_dwop_aww_set(stwuct mvpp2 *pwiv, int powt, boow add)
{
	stwuct mvpp2_pws_entwy pe;

	if (pwiv->pws_shadow[MVPP2_PE_DWOP_AWW].vawid) {
		/* Entwy exist - update powt onwy */
		mvpp2_pws_init_fwom_hw(pwiv, &pe, MVPP2_PE_DWOP_AWW);
	} ewse {
		/* Entwy doesn't exist - cweate new */
		memset(&pe, 0, sizeof(pe));
		mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_MAC);
		pe.index = MVPP2_PE_DWOP_AWW;

		/* Non-pwomiscuous mode fow aww powts - DWOP unknown packets */
		mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_DWOP_MASK,
					 MVPP2_PWS_WI_DWOP_MASK);

		mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);
		mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);

		/* Update shadow tabwe */
		mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_MAC);

		/* Mask aww powts */
		mvpp2_pws_tcam_powt_map_set(&pe, 0);
	}

	/* Update powt mask */
	mvpp2_pws_tcam_powt_set(&pe, powt, add);

	mvpp2_pws_hw_wwite(pwiv, &pe);
}

/* Set powt to unicast ow muwticast pwomiscuous mode */
void mvpp2_pws_mac_pwomisc_set(stwuct mvpp2 *pwiv, int powt,
			       enum mvpp2_pws_w2_cast w2_cast, boow add)
{
	stwuct mvpp2_pws_entwy pe;
	unsigned chaw cast_match;
	unsigned int wi;
	int tid;

	if (w2_cast == MVPP2_PWS_W2_UNI_CAST) {
		cast_match = MVPP2_PWS_UCAST_VAW;
		tid = MVPP2_PE_MAC_UC_PWOMISCUOUS;
		wi = MVPP2_PWS_WI_W2_UCAST;
	} ewse {
		cast_match = MVPP2_PWS_MCAST_VAW;
		tid = MVPP2_PE_MAC_MC_PWOMISCUOUS;
		wi = MVPP2_PWS_WI_W2_MCAST;
	}

	/* pwomiscuous mode - Accept unknown unicast ow muwticast packets */
	if (pwiv->pws_shadow[tid].vawid) {
		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);
	} ewse {
		memset(&pe, 0, sizeof(pe));
		mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_MAC);
		pe.index = tid;

		/* Continue - set next wookup */
		mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_DSA);

		/* Set wesuwt info bits */
		mvpp2_pws_swam_wi_update(&pe, wi, MVPP2_PWS_WI_W2_CAST_MASK);

		/* Match UC ow MC addwesses */
		mvpp2_pws_tcam_data_byte_set(&pe, 0, cast_match,
					     MVPP2_PWS_CAST_MASK);

		/* Shift to ethewtype */
		mvpp2_pws_swam_shift_set(&pe, 2 * ETH_AWEN,
					 MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);

		/* Mask aww powts */
		mvpp2_pws_tcam_powt_map_set(&pe, 0);

		/* Update shadow tabwe */
		mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_MAC);
	}

	/* Update powt mask */
	mvpp2_pws_tcam_powt_set(&pe, powt, add);

	mvpp2_pws_hw_wwite(pwiv, &pe);
}

/* Set entwy fow dsa packets */
static void mvpp2_pws_dsa_tag_set(stwuct mvpp2 *pwiv, int powt, boow add,
				  boow tagged, boow extend)
{
	stwuct mvpp2_pws_entwy pe;
	int tid, shift;

	if (extend) {
		tid = tagged ? MVPP2_PE_EDSA_TAGGED : MVPP2_PE_EDSA_UNTAGGED;
		shift = 8;
	} ewse {
		tid = tagged ? MVPP2_PE_DSA_TAGGED : MVPP2_PE_DSA_UNTAGGED;
		shift = 4;
	}

	if (pwiv->pws_shadow[tid].vawid) {
		/* Entwy exist - update powt onwy */
		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);
	} ewse {
		/* Entwy doesn't exist - cweate new */
		memset(&pe, 0, sizeof(pe));
		mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_DSA);
		pe.index = tid;

		/* Update shadow tabwe */
		mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_DSA);

		if (tagged) {
			/* Set tagged bit in DSA tag */
			mvpp2_pws_tcam_data_byte_set(&pe, 0,
					     MVPP2_PWS_TCAM_DSA_TAGGED_BIT,
					     MVPP2_PWS_TCAM_DSA_TAGGED_BIT);

			/* Set ai bits fow next itewation */
			if (extend)
				mvpp2_pws_swam_ai_update(&pe, 1,
							MVPP2_PWS_SWAM_AI_MASK);
			ewse
				mvpp2_pws_swam_ai_update(&pe, 0,
							MVPP2_PWS_SWAM_AI_MASK);

			/* Set wesuwt info bits to 'singwe vwan' */
			mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_VWAN_SINGWE,
						 MVPP2_PWS_WI_VWAN_MASK);
			/* If packet is tagged continue check vid fiwtewing */
			mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_VID);
		} ewse {
			/* Shift 4 bytes fow DSA tag ow 8 bytes fow EDSA tag*/
			mvpp2_pws_swam_shift_set(&pe, shift,
					MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);

			/* Set wesuwt info bits to 'no vwans' */
			mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_VWAN_NONE,
						 MVPP2_PWS_WI_VWAN_MASK);
			mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_W2);
		}

		/* Mask aww powts */
		mvpp2_pws_tcam_powt_map_set(&pe, 0);
	}

	/* Update powt mask */
	mvpp2_pws_tcam_powt_set(&pe, powt, add);

	mvpp2_pws_hw_wwite(pwiv, &pe);
}

/* Set entwy fow dsa ethewtype */
static void mvpp2_pws_dsa_tag_ethewtype_set(stwuct mvpp2 *pwiv, int powt,
					    boow add, boow tagged, boow extend)
{
	stwuct mvpp2_pws_entwy pe;
	int tid, shift, powt_mask;

	if (extend) {
		tid = tagged ? MVPP2_PE_ETYPE_EDSA_TAGGED :
		      MVPP2_PE_ETYPE_EDSA_UNTAGGED;
		powt_mask = 0;
		shift = 8;
	} ewse {
		tid = tagged ? MVPP2_PE_ETYPE_DSA_TAGGED :
		      MVPP2_PE_ETYPE_DSA_UNTAGGED;
		powt_mask = MVPP2_PWS_POWT_MASK;
		shift = 4;
	}

	if (pwiv->pws_shadow[tid].vawid) {
		/* Entwy exist - update powt onwy */
		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);
	} ewse {
		/* Entwy doesn't exist - cweate new */
		memset(&pe, 0, sizeof(pe));
		mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_DSA);
		pe.index = tid;

		/* Set ethewtype */
		mvpp2_pws_match_etype(&pe, 0, ETH_P_EDSA);
		mvpp2_pws_match_etype(&pe, 2, 0);

		mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_DSA_MASK,
					 MVPP2_PWS_WI_DSA_MASK);
		/* Shift ethewtype + 2 byte wesewved + tag*/
		mvpp2_pws_swam_shift_set(&pe, 2 + MVPP2_ETH_TYPE_WEN + shift,
					 MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);

		/* Update shadow tabwe */
		mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_DSA);

		if (tagged) {
			/* Set tagged bit in DSA tag */
			mvpp2_pws_tcam_data_byte_set(&pe,
						     MVPP2_ETH_TYPE_WEN + 2 + 3,
						 MVPP2_PWS_TCAM_DSA_TAGGED_BIT,
						 MVPP2_PWS_TCAM_DSA_TAGGED_BIT);
			/* Cweaw aww ai bits fow next itewation */
			mvpp2_pws_swam_ai_update(&pe, 0,
						 MVPP2_PWS_SWAM_AI_MASK);
			/* If packet is tagged continue check vwans */
			mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_VWAN);
		} ewse {
			/* Set wesuwt info bits to 'no vwans' */
			mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_VWAN_NONE,
						 MVPP2_PWS_WI_VWAN_MASK);
			mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_W2);
		}
		/* Mask/unmask aww powts, depending on dsa type */
		mvpp2_pws_tcam_powt_map_set(&pe, powt_mask);
	}

	/* Update powt mask */
	mvpp2_pws_tcam_powt_set(&pe, powt, add);

	mvpp2_pws_hw_wwite(pwiv, &pe);
}

/* Seawch fow existing singwe/twipwe vwan entwy */
static int mvpp2_pws_vwan_find(stwuct mvpp2 *pwiv, unsigned showt tpid, int ai)
{
	stwuct mvpp2_pws_entwy pe;
	int tid;

	/* Go thwough the aww entwies with MVPP2_PWS_WU_VWAN */
	fow (tid = MVPP2_PE_FIWST_FWEE_TID;
	     tid <= MVPP2_PE_WAST_FWEE_TID; tid++) {
		unsigned int wi_bits, ai_bits;
		boow match;

		if (!pwiv->pws_shadow[tid].vawid ||
		    pwiv->pws_shadow[tid].wu != MVPP2_PWS_WU_VWAN)
			continue;

		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);
		match = mvpp2_pws_tcam_data_cmp(&pe, 0, tpid);
		if (!match)
			continue;

		/* Get vwan type */
		wi_bits = mvpp2_pws_swam_wi_get(&pe);
		wi_bits &= MVPP2_PWS_WI_VWAN_MASK;

		/* Get cuwwent ai vawue fwom tcam */
		ai_bits = mvpp2_pws_tcam_ai_get(&pe);
		/* Cweaw doubwe vwan bit */
		ai_bits &= ~MVPP2_PWS_DBW_VWAN_AI_BIT;

		if (ai != ai_bits)
			continue;

		if (wi_bits == MVPP2_PWS_WI_VWAN_SINGWE ||
		    wi_bits == MVPP2_PWS_WI_VWAN_TWIPWE)
			wetuwn tid;
	}

	wetuwn -ENOENT;
}

/* Add/update singwe/twipwe vwan entwy */
static int mvpp2_pws_vwan_add(stwuct mvpp2 *pwiv, unsigned showt tpid, int ai,
			      unsigned int powt_map)
{
	stwuct mvpp2_pws_entwy pe;
	int tid_aux, tid;
	int wet = 0;

	memset(&pe, 0, sizeof(pe));

	tid = mvpp2_pws_vwan_find(pwiv, tpid, ai);

	if (tid < 0) {
		/* Cweate new tcam entwy */
		tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_WAST_FWEE_TID,
						MVPP2_PE_FIWST_FWEE_TID);
		if (tid < 0)
			wetuwn tid;

		/* Get wast doubwe vwan tid */
		fow (tid_aux = MVPP2_PE_WAST_FWEE_TID;
		     tid_aux >= MVPP2_PE_FIWST_FWEE_TID; tid_aux--) {
			unsigned int wi_bits;

			if (!pwiv->pws_shadow[tid_aux].vawid ||
			    pwiv->pws_shadow[tid_aux].wu != MVPP2_PWS_WU_VWAN)
				continue;

			mvpp2_pws_init_fwom_hw(pwiv, &pe, tid_aux);
			wi_bits = mvpp2_pws_swam_wi_get(&pe);
			if ((wi_bits & MVPP2_PWS_WI_VWAN_MASK) ==
			    MVPP2_PWS_WI_VWAN_DOUBWE)
				bweak;
		}

		if (tid <= tid_aux)
			wetuwn -EINVAW;

		memset(&pe, 0, sizeof(pe));
		pe.index = tid;
		mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_VWAN);

		mvpp2_pws_match_etype(&pe, 0, tpid);

		/* VWAN tag detected, pwoceed with VID fiwtewing */
		mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_VID);

		/* Cweaw aww ai bits fow next itewation */
		mvpp2_pws_swam_ai_update(&pe, 0, MVPP2_PWS_SWAM_AI_MASK);

		if (ai == MVPP2_PWS_SINGWE_VWAN_AI) {
			mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_VWAN_SINGWE,
						 MVPP2_PWS_WI_VWAN_MASK);
		} ewse {
			ai |= MVPP2_PWS_DBW_VWAN_AI_BIT;
			mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_VWAN_TWIPWE,
						 MVPP2_PWS_WI_VWAN_MASK);
		}
		mvpp2_pws_tcam_ai_update(&pe, ai, MVPP2_PWS_SWAM_AI_MASK);

		mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_VWAN);
	} ewse {
		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);
	}
	/* Update powts' mask */
	mvpp2_pws_tcam_powt_map_set(&pe, powt_map);

	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn wet;
}

/* Get fiwst fwee doubwe vwan ai numbew */
static int mvpp2_pws_doubwe_vwan_ai_fwee_get(stwuct mvpp2 *pwiv)
{
	int i;

	fow (i = 1; i < MVPP2_PWS_DBW_VWANS_MAX; i++) {
		if (!pwiv->pws_doubwe_vwans[i])
			wetuwn i;
	}

	wetuwn -EINVAW;
}

/* Seawch fow existing doubwe vwan entwy */
static int mvpp2_pws_doubwe_vwan_find(stwuct mvpp2 *pwiv, unsigned showt tpid1,
				      unsigned showt tpid2)
{
	stwuct mvpp2_pws_entwy pe;
	int tid;

	/* Go thwough the aww entwies with MVPP2_PWS_WU_VWAN */
	fow (tid = MVPP2_PE_FIWST_FWEE_TID;
	     tid <= MVPP2_PE_WAST_FWEE_TID; tid++) {
		unsigned int wi_mask;
		boow match;

		if (!pwiv->pws_shadow[tid].vawid ||
		    pwiv->pws_shadow[tid].wu != MVPP2_PWS_WU_VWAN)
			continue;

		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);

		match = mvpp2_pws_tcam_data_cmp(&pe, 0, tpid1) &&
			mvpp2_pws_tcam_data_cmp(&pe, 4, tpid2);

		if (!match)
			continue;

		wi_mask = mvpp2_pws_swam_wi_get(&pe) & MVPP2_PWS_WI_VWAN_MASK;
		if (wi_mask == MVPP2_PWS_WI_VWAN_DOUBWE)
			wetuwn tid;
	}

	wetuwn -ENOENT;
}

/* Add ow update doubwe vwan entwy */
static int mvpp2_pws_doubwe_vwan_add(stwuct mvpp2 *pwiv, unsigned showt tpid1,
				     unsigned showt tpid2,
				     unsigned int powt_map)
{
	int tid_aux, tid, ai, wet = 0;
	stwuct mvpp2_pws_entwy pe;

	memset(&pe, 0, sizeof(pe));

	tid = mvpp2_pws_doubwe_vwan_find(pwiv, tpid1, tpid2);

	if (tid < 0) {
		/* Cweate new tcam entwy */
		tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
				MVPP2_PE_WAST_FWEE_TID);
		if (tid < 0)
			wetuwn tid;

		/* Set ai vawue fow new doubwe vwan entwy */
		ai = mvpp2_pws_doubwe_vwan_ai_fwee_get(pwiv);
		if (ai < 0)
			wetuwn ai;

		/* Get fiwst singwe/twipwe vwan tid */
		fow (tid_aux = MVPP2_PE_FIWST_FWEE_TID;
		     tid_aux <= MVPP2_PE_WAST_FWEE_TID; tid_aux++) {
			unsigned int wi_bits;

			if (!pwiv->pws_shadow[tid_aux].vawid ||
			    pwiv->pws_shadow[tid_aux].wu != MVPP2_PWS_WU_VWAN)
				continue;

			mvpp2_pws_init_fwom_hw(pwiv, &pe, tid_aux);
			wi_bits = mvpp2_pws_swam_wi_get(&pe);
			wi_bits &= MVPP2_PWS_WI_VWAN_MASK;
			if (wi_bits == MVPP2_PWS_WI_VWAN_SINGWE ||
			    wi_bits == MVPP2_PWS_WI_VWAN_TWIPWE)
				bweak;
		}

		if (tid >= tid_aux)
			wetuwn -EWANGE;

		memset(&pe, 0, sizeof(pe));
		mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_VWAN);
		pe.index = tid;

		pwiv->pws_doubwe_vwans[ai] = twue;

		mvpp2_pws_match_etype(&pe, 0, tpid1);
		mvpp2_pws_match_etype(&pe, 4, tpid2);

		mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_VWAN);
		/* Shift 4 bytes - skip outew vwan tag */
		mvpp2_pws_swam_shift_set(&pe, MVPP2_VWAN_TAG_WEN,
					 MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);
		mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_VWAN_DOUBWE,
					 MVPP2_PWS_WI_VWAN_MASK);
		mvpp2_pws_swam_ai_update(&pe, ai | MVPP2_PWS_DBW_VWAN_AI_BIT,
					 MVPP2_PWS_SWAM_AI_MASK);

		mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_VWAN);
	} ewse {
		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);
	}

	/* Update powts' mask */
	mvpp2_pws_tcam_powt_map_set(&pe, powt_map);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn wet;
}

/* IPv4 headew pawsing fow fwagmentation and W4 offset */
static int mvpp2_pws_ip4_pwoto(stwuct mvpp2 *pwiv, unsigned showt pwoto,
			       unsigned int wi, unsigned int wi_mask)
{
	stwuct mvpp2_pws_entwy pe;
	int tid;

	if ((pwoto != IPPWOTO_TCP) && (pwoto != IPPWOTO_UDP) &&
	    (pwoto != IPPWOTO_IGMP))
		wetuwn -EINVAW;

	/* Not fwagmented packet */
	tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
					MVPP2_PE_WAST_FWEE_TID);
	if (tid < 0)
		wetuwn tid;

	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_IP4);
	pe.index = tid;

	/* Finished: go to fwowid genewation */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);
	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);

	/* Set W3 offset */
	mvpp2_pws_swam_offset_set(&pe, MVPP2_PWS_SWAM_UDF_TYPE_W3, -4,
				  MVPP2_PWS_SWAM_OP_SEW_UDF_ADD);
	mvpp2_pws_swam_ai_update(&pe, 0, MVPP2_PWS_IPV4_DIP_AI_BIT);
	mvpp2_pws_swam_wi_update(&pe, wi, wi_mask | MVPP2_PWS_WI_IP_FWAG_MASK);

	mvpp2_pws_tcam_data_byte_set(&pe, 2, 0x00,
				     MVPP2_PWS_TCAM_PWOTO_MASK_W);
	mvpp2_pws_tcam_data_byte_set(&pe, 3, 0x00,
				     MVPP2_PWS_TCAM_PWOTO_MASK);

	mvpp2_pws_tcam_data_byte_set(&pe, 5, pwoto, MVPP2_PWS_TCAM_PWOTO_MASK);
	mvpp2_pws_tcam_ai_update(&pe, MVPP2_PWS_IPV4_DIP_AI_BIT,
				 MVPP2_PWS_IPV4_DIP_AI_BIT);
	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_IP4);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Fwagmented packet */
	tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
					MVPP2_PE_WAST_FWEE_TID);
	if (tid < 0)
		wetuwn tid;

	pe.index = tid;
	/* Cweaw wi befowe updating */
	pe.swam[MVPP2_PWS_SWAM_WI_WOWD] = 0x0;
	pe.swam[MVPP2_PWS_SWAM_WI_CTWW_WOWD] = 0x0;
	mvpp2_pws_swam_wi_update(&pe, wi, wi_mask);

	mvpp2_pws_swam_wi_update(&pe, wi | MVPP2_PWS_WI_IP_FWAG_TWUE,
				 wi_mask | MVPP2_PWS_WI_IP_FWAG_MASK);

	mvpp2_pws_tcam_data_byte_set(&pe, 2, 0x00, 0x0);
	mvpp2_pws_tcam_data_byte_set(&pe, 3, 0x00, 0x0);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_IP4);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn 0;
}

/* IPv4 W3 muwticast ow bwoadcast */
static int mvpp2_pws_ip4_cast(stwuct mvpp2 *pwiv, unsigned showt w3_cast)
{
	stwuct mvpp2_pws_entwy pe;
	int mask, tid;

	tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
					MVPP2_PE_WAST_FWEE_TID);
	if (tid < 0)
		wetuwn tid;

	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_IP4);
	pe.index = tid;

	switch (w3_cast) {
	case MVPP2_PWS_W3_MUWTI_CAST:
		mvpp2_pws_tcam_data_byte_set(&pe, 0, MVPP2_PWS_IPV4_MC,
					     MVPP2_PWS_IPV4_MC_MASK);
		mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W3_MCAST,
					 MVPP2_PWS_WI_W3_ADDW_MASK);
		bweak;
	case  MVPP2_PWS_W3_BWOAD_CAST:
		mask = MVPP2_PWS_IPV4_BC_MASK;
		mvpp2_pws_tcam_data_byte_set(&pe, 0, mask, mask);
		mvpp2_pws_tcam_data_byte_set(&pe, 1, mask, mask);
		mvpp2_pws_tcam_data_byte_set(&pe, 2, mask, mask);
		mvpp2_pws_tcam_data_byte_set(&pe, 3, mask, mask);
		mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W3_BCAST,
					 MVPP2_PWS_WI_W3_ADDW_MASK);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Go again to ipv4 */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_IP4);

	mvpp2_pws_swam_ai_update(&pe, MVPP2_PWS_IPV4_DIP_AI_BIT,
				 MVPP2_PWS_IPV4_DIP_AI_BIT);

	/* Shift back to IPv4 pwoto */
	mvpp2_pws_swam_shift_set(&pe, -12, MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);

	mvpp2_pws_tcam_ai_update(&pe, 0, MVPP2_PWS_IPV4_DIP_AI_BIT);

	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_IP4);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn 0;
}

/* Set entwies fow pwotocows ovew IPv6  */
static int mvpp2_pws_ip6_pwoto(stwuct mvpp2 *pwiv, unsigned showt pwoto,
			       unsigned int wi, unsigned int wi_mask)
{
	stwuct mvpp2_pws_entwy pe;
	int tid;

	if ((pwoto != IPPWOTO_TCP) && (pwoto != IPPWOTO_UDP) &&
	    (pwoto != IPPWOTO_ICMPV6) && (pwoto != IPPWOTO_IPIP))
		wetuwn -EINVAW;

	tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
					MVPP2_PE_WAST_FWEE_TID);
	if (tid < 0)
		wetuwn tid;

	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_IP6);
	pe.index = tid;

	/* Finished: go to fwowid genewation */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);
	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);
	mvpp2_pws_swam_wi_update(&pe, wi, wi_mask);
	mvpp2_pws_swam_offset_set(&pe, MVPP2_PWS_SWAM_UDF_TYPE_W4,
				  sizeof(stwuct ipv6hdw) - 6,
				  MVPP2_PWS_SWAM_OP_SEW_UDF_ADD);

	mvpp2_pws_tcam_data_byte_set(&pe, 0, pwoto, MVPP2_PWS_TCAM_PWOTO_MASK);
	mvpp2_pws_tcam_ai_update(&pe, MVPP2_PWS_IPV6_NO_EXT_AI_BIT,
				 MVPP2_PWS_IPV6_NO_EXT_AI_BIT);
	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Wwite HW */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_IP6);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn 0;
}

/* IPv6 W3 muwticast entwy */
static int mvpp2_pws_ip6_cast(stwuct mvpp2 *pwiv, unsigned showt w3_cast)
{
	stwuct mvpp2_pws_entwy pe;
	int tid;

	if (w3_cast != MVPP2_PWS_W3_MUWTI_CAST)
		wetuwn -EINVAW;

	tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
					MVPP2_PE_WAST_FWEE_TID);
	if (tid < 0)
		wetuwn tid;

	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_IP6);
	pe.index = tid;

	/* Finished: go to fwowid genewation */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_IP6);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W3_MCAST,
				 MVPP2_PWS_WI_W3_ADDW_MASK);
	mvpp2_pws_swam_ai_update(&pe, MVPP2_PWS_IPV6_NO_EXT_AI_BIT,
				 MVPP2_PWS_IPV6_NO_EXT_AI_BIT);
	/* Shift back to IPv6 NH */
	mvpp2_pws_swam_shift_set(&pe, -18, MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);

	mvpp2_pws_tcam_data_byte_set(&pe, 0, MVPP2_PWS_IPV6_MC,
				     MVPP2_PWS_IPV6_MC_MASK);
	mvpp2_pws_tcam_ai_update(&pe, 0, MVPP2_PWS_IPV6_NO_EXT_AI_BIT);
	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_IP6);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn 0;
}

/* Pawsew pew-powt initiawization */
static void mvpp2_pws_hw_powt_init(stwuct mvpp2 *pwiv, int powt, int wu_fiwst,
				   int wu_max, int offset)
{
	u32 vaw;

	/* Set wookup ID */
	vaw = mvpp2_wead(pwiv, MVPP2_PWS_INIT_WOOKUP_WEG);
	vaw &= ~MVPP2_PWS_POWT_WU_MASK(powt);
	vaw |=  MVPP2_PWS_POWT_WU_VAW(powt, wu_fiwst);
	mvpp2_wwite(pwiv, MVPP2_PWS_INIT_WOOKUP_WEG, vaw);

	/* Set maximum numbew of woops fow packet weceived fwom powt */
	vaw = mvpp2_wead(pwiv, MVPP2_PWS_MAX_WOOP_WEG(powt));
	vaw &= ~MVPP2_PWS_MAX_WOOP_MASK(powt);
	vaw |= MVPP2_PWS_MAX_WOOP_VAW(powt, wu_max);
	mvpp2_wwite(pwiv, MVPP2_PWS_MAX_WOOP_WEG(powt), vaw);

	/* Set initiaw offset fow packet headew extwaction fow the fiwst
	 * seawching woop
	 */
	vaw = mvpp2_wead(pwiv, MVPP2_PWS_INIT_OFFS_WEG(powt));
	vaw &= ~MVPP2_PWS_INIT_OFF_MASK(powt);
	vaw |= MVPP2_PWS_INIT_OFF_VAW(powt, offset);
	mvpp2_wwite(pwiv, MVPP2_PWS_INIT_OFFS_WEG(powt), vaw);
}

/* Defauwt fwow entwies initiawization fow aww powts */
static void mvpp2_pws_def_fwow_init(stwuct mvpp2 *pwiv)
{
	stwuct mvpp2_pws_entwy pe;
	int powt;

	fow (powt = 0; powt < MVPP2_MAX_POWTS; powt++) {
		memset(&pe, 0, sizeof(pe));
		mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_FWOWS);
		pe.index = MVPP2_PE_FIWST_DEFAUWT_FWOW - powt;

		/* Mask aww powts */
		mvpp2_pws_tcam_powt_map_set(&pe, 0);

		/* Set fwow ID*/
		mvpp2_pws_swam_ai_update(&pe, powt, MVPP2_PWS_FWOW_ID_MASK);
		mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_DONE_BIT, 1);

		/* Update shadow tabwe and hw entwy */
		mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_FWOWS);
		mvpp2_pws_hw_wwite(pwiv, &pe);
	}
}

/* Set defauwt entwy fow Mawveww Headew fiewd */
static void mvpp2_pws_mh_init(stwuct mvpp2 *pwiv)
{
	stwuct mvpp2_pws_entwy pe;

	memset(&pe, 0, sizeof(pe));

	pe.index = MVPP2_PE_MH_DEFAUWT;
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_MH);
	mvpp2_pws_swam_shift_set(&pe, MVPP2_MH_SIZE,
				 MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_MAC);

	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_MH);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Set MH entwy that skip pawsew */
	pe.index = MVPP2_PE_MH_SKIP_PWS;
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_MH);
	mvpp2_pws_swam_shift_set(&pe, MVPP2_MH_SIZE,
				 MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);
	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);

	/* Mask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, 0);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_MH);
	mvpp2_pws_hw_wwite(pwiv, &pe);
}

/* Set defauwt entiwes (pwace howdew) fow pwomiscuous, non-pwomiscuous and
 * muwticast MAC addwesses
 */
static void mvpp2_pws_mac_init(stwuct mvpp2 *pwiv)
{
	stwuct mvpp2_pws_entwy pe;

	memset(&pe, 0, sizeof(pe));

	/* Non-pwomiscuous mode fow aww powts - DWOP unknown packets */
	pe.index = MVPP2_PE_MAC_NON_PWOMISCUOUS;
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_MAC);

	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_DWOP_MASK,
				 MVPP2_PWS_WI_DWOP_MASK);
	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);

	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_MAC);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Cweate dummy entwies fow dwop aww and pwomiscuous modes */
	mvpp2_pws_dwop_fc(pwiv);
	mvpp2_pws_mac_dwop_aww_set(pwiv, 0, fawse);
	mvpp2_pws_mac_pwomisc_set(pwiv, 0, MVPP2_PWS_W2_UNI_CAST, fawse);
	mvpp2_pws_mac_pwomisc_set(pwiv, 0, MVPP2_PWS_W2_MUWTI_CAST, fawse);
}

/* Set defauwt entwies fow vawious types of dsa packets */
static void mvpp2_pws_dsa_init(stwuct mvpp2 *pwiv)
{
	stwuct mvpp2_pws_entwy pe;

	/* None tagged EDSA entwy - pwace howdew */
	mvpp2_pws_dsa_tag_set(pwiv, 0, fawse, MVPP2_PWS_UNTAGGED,
			      MVPP2_PWS_EDSA);

	/* Tagged EDSA entwy - pwace howdew */
	mvpp2_pws_dsa_tag_set(pwiv, 0, fawse, MVPP2_PWS_TAGGED, MVPP2_PWS_EDSA);

	/* None tagged DSA entwy - pwace howdew */
	mvpp2_pws_dsa_tag_set(pwiv, 0, fawse, MVPP2_PWS_UNTAGGED,
			      MVPP2_PWS_DSA);

	/* Tagged DSA entwy - pwace howdew */
	mvpp2_pws_dsa_tag_set(pwiv, 0, fawse, MVPP2_PWS_TAGGED, MVPP2_PWS_DSA);

	/* None tagged EDSA ethewtype entwy - pwace howdew*/
	mvpp2_pws_dsa_tag_ethewtype_set(pwiv, 0, fawse,
					MVPP2_PWS_UNTAGGED, MVPP2_PWS_EDSA);

	/* Tagged EDSA ethewtype entwy - pwace howdew*/
	mvpp2_pws_dsa_tag_ethewtype_set(pwiv, 0, fawse,
					MVPP2_PWS_TAGGED, MVPP2_PWS_EDSA);

	/* None tagged DSA ethewtype entwy */
	mvpp2_pws_dsa_tag_ethewtype_set(pwiv, 0, twue,
					MVPP2_PWS_UNTAGGED, MVPP2_PWS_DSA);

	/* Tagged DSA ethewtype entwy */
	mvpp2_pws_dsa_tag_ethewtype_set(pwiv, 0, twue,
					MVPP2_PWS_TAGGED, MVPP2_PWS_DSA);

	/* Set defauwt entwy, in case DSA ow EDSA tag not found */
	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_DSA);
	pe.index = MVPP2_PE_DSA_DEFAUWT;
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_VWAN);

	/* Shift 0 bytes */
	mvpp2_pws_swam_shift_set(&pe, 0, MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_MAC);

	/* Cweaw aww swam ai bits fow next itewation */
	mvpp2_pws_swam_ai_update(&pe, 0, MVPP2_PWS_SWAM_AI_MASK);

	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	mvpp2_pws_hw_wwite(pwiv, &pe);
}

/* Initiawize pawsew entwies fow VID fiwtewing */
static void mvpp2_pws_vid_init(stwuct mvpp2 *pwiv)
{
	stwuct mvpp2_pws_entwy pe;

	memset(&pe, 0, sizeof(pe));

	/* Set defauwt vid entwy */
	pe.index = MVPP2_PE_VID_FWTW_DEFAUWT;
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_VID);

	mvpp2_pws_tcam_ai_update(&pe, 0, MVPP2_PWS_EDSA_VID_AI_BIT);

	/* Skip VWAN headew - Set offset to 4 bytes */
	mvpp2_pws_swam_shift_set(&pe, MVPP2_VWAN_TAG_WEN,
				 MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);

	/* Cweaw aww ai bits fow next itewation */
	mvpp2_pws_swam_ai_update(&pe, 0, MVPP2_PWS_SWAM_AI_MASK);

	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_W2);

	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_VID);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Set defauwt vid entwy fow extended DSA*/
	memset(&pe, 0, sizeof(pe));

	/* Set defauwt vid entwy */
	pe.index = MVPP2_PE_VID_EDSA_FWTW_DEFAUWT;
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_VID);

	mvpp2_pws_tcam_ai_update(&pe, MVPP2_PWS_EDSA_VID_AI_BIT,
				 MVPP2_PWS_EDSA_VID_AI_BIT);

	/* Skip VWAN headew - Set offset to 8 bytes */
	mvpp2_pws_swam_shift_set(&pe, MVPP2_VWAN_TAG_EDSA_WEN,
				 MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);

	/* Cweaw aww ai bits fow next itewation */
	mvpp2_pws_swam_ai_update(&pe, 0, MVPP2_PWS_SWAM_AI_MASK);

	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_W2);

	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_VID);
	mvpp2_pws_hw_wwite(pwiv, &pe);
}

/* Match basic ethewtypes */
static int mvpp2_pws_etype_init(stwuct mvpp2 *pwiv)
{
	stwuct mvpp2_pws_entwy pe;
	int tid, ihw;

	/* Ethewtype: PPPoE */
	tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
					MVPP2_PE_WAST_FWEE_TID);
	if (tid < 0)
		wetuwn tid;

	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_W2);
	pe.index = tid;

	mvpp2_pws_match_etype(&pe, 0, ETH_P_PPP_SES);

	mvpp2_pws_swam_shift_set(&pe, MVPP2_PPPOE_HDW_SIZE,
				 MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_PPPOE);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_PPPOE_MASK,
				 MVPP2_PWS_WI_PPPOE_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_W2);
	pwiv->pws_shadow[pe.index].udf = MVPP2_PWS_UDF_W2_DEF;
	pwiv->pws_shadow[pe.index].finish = fawse;
	mvpp2_pws_shadow_wi_set(pwiv, pe.index, MVPP2_PWS_WI_PPPOE_MASK,
				MVPP2_PWS_WI_PPPOE_MASK);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Ethewtype: AWP */
	tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
					MVPP2_PE_WAST_FWEE_TID);
	if (tid < 0)
		wetuwn tid;

	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_W2);
	pe.index = tid;

	mvpp2_pws_match_etype(&pe, 0, ETH_P_AWP);

	/* Genewate fwow in the next itewation*/
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);
	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W3_AWP,
				 MVPP2_PWS_WI_W3_PWOTO_MASK);
	/* Set W3 offset */
	mvpp2_pws_swam_offset_set(&pe, MVPP2_PWS_SWAM_UDF_TYPE_W3,
				  MVPP2_ETH_TYPE_WEN,
				  MVPP2_PWS_SWAM_OP_SEW_UDF_ADD);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_W2);
	pwiv->pws_shadow[pe.index].udf = MVPP2_PWS_UDF_W2_DEF;
	pwiv->pws_shadow[pe.index].finish = twue;
	mvpp2_pws_shadow_wi_set(pwiv, pe.index, MVPP2_PWS_WI_W3_AWP,
				MVPP2_PWS_WI_W3_PWOTO_MASK);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Ethewtype: WBTD */
	tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
					MVPP2_PE_WAST_FWEE_TID);
	if (tid < 0)
		wetuwn tid;

	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_W2);
	pe.index = tid;

	mvpp2_pws_match_etype(&pe, 0, MVPP2_IP_WBDT_TYPE);

	/* Genewate fwow in the next itewation*/
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);
	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_CPU_CODE_WX_SPEC |
				 MVPP2_PWS_WI_UDF3_WX_SPECIAW,
				 MVPP2_PWS_WI_CPU_CODE_MASK |
				 MVPP2_PWS_WI_UDF3_MASK);
	/* Set W3 offset */
	mvpp2_pws_swam_offset_set(&pe, MVPP2_PWS_SWAM_UDF_TYPE_W3,
				  MVPP2_ETH_TYPE_WEN,
				  MVPP2_PWS_SWAM_OP_SEW_UDF_ADD);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_W2);
	pwiv->pws_shadow[pe.index].udf = MVPP2_PWS_UDF_W2_DEF;
	pwiv->pws_shadow[pe.index].finish = twue;
	mvpp2_pws_shadow_wi_set(pwiv, pe.index, MVPP2_PWS_WI_CPU_CODE_WX_SPEC |
				MVPP2_PWS_WI_UDF3_WX_SPECIAW,
				MVPP2_PWS_WI_CPU_CODE_MASK |
				MVPP2_PWS_WI_UDF3_MASK);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Ethewtype: IPv4 with headew wength >= 5 */
	fow (ihw = MVPP2_PWS_IPV4_IHW_MIN; ihw <= MVPP2_PWS_IPV4_IHW_MAX; ihw++) {
		tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
						MVPP2_PE_WAST_FWEE_TID);
		if (tid < 0)
			wetuwn tid;

		memset(&pe, 0, sizeof(pe));
		mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_W2);
		pe.index = tid;

		mvpp2_pws_match_etype(&pe, 0, ETH_P_IP);
		mvpp2_pws_tcam_data_byte_set(&pe, MVPP2_ETH_TYPE_WEN,
					     MVPP2_PWS_IPV4_HEAD | ihw,
					     MVPP2_PWS_IPV4_HEAD_MASK |
					     MVPP2_PWS_IPV4_IHW_MASK);

		mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_IP4);
		mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W3_IP4,
					 MVPP2_PWS_WI_W3_PWOTO_MASK);
		/* goto ipv4 dst-addwess (skip eth_type + IP-headew-size - 4) */
		mvpp2_pws_swam_shift_set(&pe, MVPP2_ETH_TYPE_WEN +
					 sizeof(stwuct iphdw) - 4,
					 MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);
		/* Set W4 offset */
		mvpp2_pws_swam_offset_set(&pe, MVPP2_PWS_SWAM_UDF_TYPE_W4,
					  MVPP2_ETH_TYPE_WEN + (ihw * 4),
					  MVPP2_PWS_SWAM_OP_SEW_UDF_ADD);

		/* Update shadow tabwe and hw entwy */
		mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_W2);
		pwiv->pws_shadow[pe.index].udf = MVPP2_PWS_UDF_W2_DEF;
		pwiv->pws_shadow[pe.index].finish = fawse;
		mvpp2_pws_shadow_wi_set(pwiv, pe.index, MVPP2_PWS_WI_W3_IP4,
					MVPP2_PWS_WI_W3_PWOTO_MASK);
		mvpp2_pws_hw_wwite(pwiv, &pe);
	}

	/* Ethewtype: IPv6 without options */
	tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
					MVPP2_PE_WAST_FWEE_TID);
	if (tid < 0)
		wetuwn tid;

	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_W2);
	pe.index = tid;

	mvpp2_pws_match_etype(&pe, 0, ETH_P_IPV6);

	/* Skip DIP of IPV6 headew */
	mvpp2_pws_swam_shift_set(&pe, MVPP2_ETH_TYPE_WEN + 8 +
				 MVPP2_MAX_W3_ADDW_SIZE,
				 MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_IP6);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W3_IP6,
				 MVPP2_PWS_WI_W3_PWOTO_MASK);
	/* Set W3 offset */
	mvpp2_pws_swam_offset_set(&pe, MVPP2_PWS_SWAM_UDF_TYPE_W3,
				  MVPP2_ETH_TYPE_WEN,
				  MVPP2_PWS_SWAM_OP_SEW_UDF_ADD);

	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_W2);
	pwiv->pws_shadow[pe.index].udf = MVPP2_PWS_UDF_W2_DEF;
	pwiv->pws_shadow[pe.index].finish = fawse;
	mvpp2_pws_shadow_wi_set(pwiv, pe.index, MVPP2_PWS_WI_W3_IP6,
				MVPP2_PWS_WI_W3_PWOTO_MASK);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Defauwt entwy fow MVPP2_PWS_WU_W2 - Unknown ethtype */
	memset(&pe, 0, sizeof(stwuct mvpp2_pws_entwy));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_W2);
	pe.index = MVPP2_PE_ETH_TYPE_UN;

	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Genewate fwow in the next itewation*/
	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W3_UN,
				 MVPP2_PWS_WI_W3_PWOTO_MASK);
	/* Set W3 offset even it's unknown W3 */
	mvpp2_pws_swam_offset_set(&pe, MVPP2_PWS_SWAM_UDF_TYPE_W3,
				  MVPP2_ETH_TYPE_WEN,
				  MVPP2_PWS_SWAM_OP_SEW_UDF_ADD);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_W2);
	pwiv->pws_shadow[pe.index].udf = MVPP2_PWS_UDF_W2_DEF;
	pwiv->pws_shadow[pe.index].finish = twue;
	mvpp2_pws_shadow_wi_set(pwiv, pe.index, MVPP2_PWS_WI_W3_UN,
				MVPP2_PWS_WI_W3_PWOTO_MASK);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn 0;
}

/* Configuwe vwan entwies and detect up to 2 successive VWAN tags.
 * Possibwe options:
 * 0x8100, 0x88A8
 * 0x8100, 0x8100
 * 0x8100
 * 0x88A8
 */
static int mvpp2_pws_vwan_init(stwuct pwatfowm_device *pdev, stwuct mvpp2 *pwiv)
{
	stwuct mvpp2_pws_entwy pe;
	int eww;

	pwiv->pws_doubwe_vwans = devm_kcawwoc(&pdev->dev, sizeof(boow),
					      MVPP2_PWS_DBW_VWANS_MAX,
					      GFP_KEWNEW);
	if (!pwiv->pws_doubwe_vwans)
		wetuwn -ENOMEM;

	/* Doubwe VWAN: 0x88A8, 0x8100 */
	eww = mvpp2_pws_doubwe_vwan_add(pwiv, ETH_P_8021AD, ETH_P_8021Q,
					MVPP2_PWS_POWT_MASK);
	if (eww)
		wetuwn eww;

	/* Doubwe VWAN: 0x8100, 0x8100 */
	eww = mvpp2_pws_doubwe_vwan_add(pwiv, ETH_P_8021Q, ETH_P_8021Q,
					MVPP2_PWS_POWT_MASK);
	if (eww)
		wetuwn eww;

	/* Singwe VWAN: 0x88a8 */
	eww = mvpp2_pws_vwan_add(pwiv, ETH_P_8021AD, MVPP2_PWS_SINGWE_VWAN_AI,
				 MVPP2_PWS_POWT_MASK);
	if (eww)
		wetuwn eww;

	/* Singwe VWAN: 0x8100 */
	eww = mvpp2_pws_vwan_add(pwiv, ETH_P_8021Q, MVPP2_PWS_SINGWE_VWAN_AI,
				 MVPP2_PWS_POWT_MASK);
	if (eww)
		wetuwn eww;

	/* Set defauwt doubwe vwan entwy */
	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_VWAN);
	pe.index = MVPP2_PE_VWAN_DBW;

	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_VID);

	/* Cweaw ai fow next itewations */
	mvpp2_pws_swam_ai_update(&pe, 0, MVPP2_PWS_SWAM_AI_MASK);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_VWAN_DOUBWE,
				 MVPP2_PWS_WI_VWAN_MASK);

	mvpp2_pws_tcam_ai_update(&pe, MVPP2_PWS_DBW_VWAN_AI_BIT,
				 MVPP2_PWS_DBW_VWAN_AI_BIT);
	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_VWAN);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Set defauwt vwan none entwy */
	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_VWAN);
	pe.index = MVPP2_PE_VWAN_NONE;

	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_W2);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_VWAN_NONE,
				 MVPP2_PWS_WI_VWAN_MASK);

	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_VWAN);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn 0;
}

/* Set entwies fow PPPoE ethewtype */
static int mvpp2_pws_pppoe_init(stwuct mvpp2 *pwiv)
{
	stwuct mvpp2_pws_entwy pe;
	int tid, ihw;

	/* IPv4 ovew PPPoE with headew wength >= 5 */
	fow (ihw = MVPP2_PWS_IPV4_IHW_MIN; ihw <= MVPP2_PWS_IPV4_IHW_MAX; ihw++) {
		tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
						MVPP2_PE_WAST_FWEE_TID);
		if (tid < 0)
			wetuwn tid;

		memset(&pe, 0, sizeof(pe));
		mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_PPPOE);
		pe.index = tid;

		mvpp2_pws_match_etype(&pe, 0, PPP_IP);
		mvpp2_pws_tcam_data_byte_set(&pe, MVPP2_ETH_TYPE_WEN,
					     MVPP2_PWS_IPV4_HEAD | ihw,
					     MVPP2_PWS_IPV4_HEAD_MASK |
					     MVPP2_PWS_IPV4_IHW_MASK);

		mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_IP4);
		mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W3_IP4,
					 MVPP2_PWS_WI_W3_PWOTO_MASK);
		/* goto ipv4 dst-addwess (skip eth_type + IP-headew-size - 4) */
		mvpp2_pws_swam_shift_set(&pe, MVPP2_ETH_TYPE_WEN +
					 sizeof(stwuct iphdw) - 4,
					 MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);
		/* Set W3 offset */
		mvpp2_pws_swam_offset_set(&pe, MVPP2_PWS_SWAM_UDF_TYPE_W3,
					  MVPP2_ETH_TYPE_WEN,
					  MVPP2_PWS_SWAM_OP_SEW_UDF_ADD);
		/* Set W4 offset */
		mvpp2_pws_swam_offset_set(&pe, MVPP2_PWS_SWAM_UDF_TYPE_W4,
					  MVPP2_ETH_TYPE_WEN + (ihw * 4),
					  MVPP2_PWS_SWAM_OP_SEW_UDF_ADD);

		/* Update shadow tabwe and hw entwy */
		mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_PPPOE);
		mvpp2_pws_hw_wwite(pwiv, &pe);
	}

	/* IPv6 ovew PPPoE */
	tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
					MVPP2_PE_WAST_FWEE_TID);
	if (tid < 0)
		wetuwn tid;

	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_PPPOE);
	pe.index = tid;

	mvpp2_pws_match_etype(&pe, 0, PPP_IPV6);

	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_IP6);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W3_IP6,
				 MVPP2_PWS_WI_W3_PWOTO_MASK);
	/* Jump to DIP of IPV6 headew */
	mvpp2_pws_swam_shift_set(&pe, MVPP2_ETH_TYPE_WEN + 8 +
				 MVPP2_MAX_W3_ADDW_SIZE,
				 MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);
	/* Set W3 offset */
	mvpp2_pws_swam_offset_set(&pe, MVPP2_PWS_SWAM_UDF_TYPE_W3,
				  MVPP2_ETH_TYPE_WEN,
				  MVPP2_PWS_SWAM_OP_SEW_UDF_ADD);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_PPPOE);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Non-IP ovew PPPoE */
	tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
					MVPP2_PE_WAST_FWEE_TID);
	if (tid < 0)
		wetuwn tid;

	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_PPPOE);
	pe.index = tid;

	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W3_UN,
				 MVPP2_PWS_WI_W3_PWOTO_MASK);

	/* Finished: go to fwowid genewation */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);
	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);
	/* Set W3 offset even if it's unknown W3 */
	mvpp2_pws_swam_offset_set(&pe, MVPP2_PWS_SWAM_UDF_TYPE_W3,
				  MVPP2_ETH_TYPE_WEN,
				  MVPP2_PWS_SWAM_OP_SEW_UDF_ADD);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_PPPOE);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn 0;
}

/* Initiawize entwies fow IPv4 */
static int mvpp2_pws_ip4_init(stwuct mvpp2 *pwiv)
{
	stwuct mvpp2_pws_entwy pe;
	int eww;

	/* Set entwies fow TCP, UDP and IGMP ovew IPv4 */
	eww = mvpp2_pws_ip4_pwoto(pwiv, IPPWOTO_TCP, MVPP2_PWS_WI_W4_TCP,
				  MVPP2_PWS_WI_W4_PWOTO_MASK);
	if (eww)
		wetuwn eww;

	eww = mvpp2_pws_ip4_pwoto(pwiv, IPPWOTO_UDP, MVPP2_PWS_WI_W4_UDP,
				  MVPP2_PWS_WI_W4_PWOTO_MASK);
	if (eww)
		wetuwn eww;

	eww = mvpp2_pws_ip4_pwoto(pwiv, IPPWOTO_IGMP,
				  MVPP2_PWS_WI_CPU_CODE_WX_SPEC |
				  MVPP2_PWS_WI_UDF3_WX_SPECIAW,
				  MVPP2_PWS_WI_CPU_CODE_MASK |
				  MVPP2_PWS_WI_UDF3_MASK);
	if (eww)
		wetuwn eww;

	/* IPv4 Bwoadcast */
	eww = mvpp2_pws_ip4_cast(pwiv, MVPP2_PWS_W3_BWOAD_CAST);
	if (eww)
		wetuwn eww;

	/* IPv4 Muwticast */
	eww = mvpp2_pws_ip4_cast(pwiv, MVPP2_PWS_W3_MUWTI_CAST);
	if (eww)
		wetuwn eww;

	/* Defauwt IPv4 entwy fow unknown pwotocows */
	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_IP4);
	pe.index = MVPP2_PE_IP4_PWOTO_UN;

	/* Finished: go to fwowid genewation */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);
	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);

	/* Set W3 offset */
	mvpp2_pws_swam_offset_set(&pe, MVPP2_PWS_SWAM_UDF_TYPE_W3, -4,
				  MVPP2_PWS_SWAM_OP_SEW_UDF_ADD);
	mvpp2_pws_swam_ai_update(&pe, 0, MVPP2_PWS_IPV4_DIP_AI_BIT);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W4_OTHEW,
				 MVPP2_PWS_WI_W4_PWOTO_MASK);

	mvpp2_pws_tcam_ai_update(&pe, MVPP2_PWS_IPV4_DIP_AI_BIT,
				 MVPP2_PWS_IPV4_DIP_AI_BIT);
	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_IP4);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Defauwt IPv4 entwy fow unicast addwess */
	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_IP4);
	pe.index = MVPP2_PE_IP4_ADDW_UN;

	/* Go again to ipv4 */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_IP4);

	mvpp2_pws_swam_ai_update(&pe, MVPP2_PWS_IPV4_DIP_AI_BIT,
				 MVPP2_PWS_IPV4_DIP_AI_BIT);

	/* Shift back to IPv4 pwoto */
	mvpp2_pws_swam_shift_set(&pe, -12, MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);

	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W3_UCAST,
				 MVPP2_PWS_WI_W3_ADDW_MASK);
	mvpp2_pws_tcam_ai_update(&pe, 0, MVPP2_PWS_IPV4_DIP_AI_BIT);

	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_IP4);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn 0;
}

/* Initiawize entwies fow IPv6 */
static int mvpp2_pws_ip6_init(stwuct mvpp2 *pwiv)
{
	stwuct mvpp2_pws_entwy pe;
	int tid, eww;

	/* Set entwies fow TCP, UDP and ICMP ovew IPv6 */
	eww = mvpp2_pws_ip6_pwoto(pwiv, IPPWOTO_TCP,
				  MVPP2_PWS_WI_W4_TCP,
				  MVPP2_PWS_WI_W4_PWOTO_MASK);
	if (eww)
		wetuwn eww;

	eww = mvpp2_pws_ip6_pwoto(pwiv, IPPWOTO_UDP,
				  MVPP2_PWS_WI_W4_UDP,
				  MVPP2_PWS_WI_W4_PWOTO_MASK);
	if (eww)
		wetuwn eww;

	eww = mvpp2_pws_ip6_pwoto(pwiv, IPPWOTO_ICMPV6,
				  MVPP2_PWS_WI_CPU_CODE_WX_SPEC |
				  MVPP2_PWS_WI_UDF3_WX_SPECIAW,
				  MVPP2_PWS_WI_CPU_CODE_MASK |
				  MVPP2_PWS_WI_UDF3_MASK);
	if (eww)
		wetuwn eww;

	/* IPv4 is the wast headew. This is simiwaw case as 6-TCP ow 17-UDP */
	/* Wesuwt Info: UDF7=1, DS wite */
	eww = mvpp2_pws_ip6_pwoto(pwiv, IPPWOTO_IPIP,
				  MVPP2_PWS_WI_UDF7_IP6_WITE,
				  MVPP2_PWS_WI_UDF7_MASK);
	if (eww)
		wetuwn eww;

	/* IPv6 muwticast */
	eww = mvpp2_pws_ip6_cast(pwiv, MVPP2_PWS_W3_MUWTI_CAST);
	if (eww)
		wetuwn eww;

	/* Entwy fow checking hop wimit */
	tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, MVPP2_PE_FIWST_FWEE_TID,
					MVPP2_PE_WAST_FWEE_TID);
	if (tid < 0)
		wetuwn tid;

	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_IP6);
	pe.index = tid;

	/* Finished: go to fwowid genewation */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);
	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W3_UN |
				 MVPP2_PWS_WI_DWOP_MASK,
				 MVPP2_PWS_WI_W3_PWOTO_MASK |
				 MVPP2_PWS_WI_DWOP_MASK);

	mvpp2_pws_tcam_data_byte_set(&pe, 1, 0x00, MVPP2_PWS_IPV6_HOP_MASK);
	mvpp2_pws_tcam_ai_update(&pe, MVPP2_PWS_IPV6_NO_EXT_AI_BIT,
				 MVPP2_PWS_IPV6_NO_EXT_AI_BIT);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_IP4);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Defauwt IPv6 entwy fow unknown pwotocows */
	memset(&pe, 0, sizeof(pe));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_IP6);
	pe.index = MVPP2_PE_IP6_PWOTO_UN;

	/* Finished: go to fwowid genewation */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);
	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W4_OTHEW,
				 MVPP2_PWS_WI_W4_PWOTO_MASK);
	/* Set W4 offset wewativewy to ouw cuwwent pwace */
	mvpp2_pws_swam_offset_set(&pe, MVPP2_PWS_SWAM_UDF_TYPE_W4,
				  sizeof(stwuct ipv6hdw) - 4,
				  MVPP2_PWS_SWAM_OP_SEW_UDF_ADD);

	mvpp2_pws_tcam_ai_update(&pe, MVPP2_PWS_IPV6_NO_EXT_AI_BIT,
				 MVPP2_PWS_IPV6_NO_EXT_AI_BIT);
	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_IP4);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Defauwt IPv6 entwy fow unknown ext pwotocows */
	memset(&pe, 0, sizeof(stwuct mvpp2_pws_entwy));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_IP6);
	pe.index = MVPP2_PE_IP6_EXT_PWOTO_UN;

	/* Finished: go to fwowid genewation */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_FWOWS);
	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_GEN_BIT, 1);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W4_OTHEW,
				 MVPP2_PWS_WI_W4_PWOTO_MASK);

	mvpp2_pws_tcam_ai_update(&pe, MVPP2_PWS_IPV6_EXT_AI_BIT,
				 MVPP2_PWS_IPV6_EXT_AI_BIT);
	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_IP4);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	/* Defauwt IPv6 entwy fow unicast addwess */
	memset(&pe, 0, sizeof(stwuct mvpp2_pws_entwy));
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_IP6);
	pe.index = MVPP2_PE_IP6_ADDW_UN;

	/* Finished: go to IPv6 again */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_IP6);
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_W3_UCAST,
				 MVPP2_PWS_WI_W3_ADDW_MASK);
	mvpp2_pws_swam_ai_update(&pe, MVPP2_PWS_IPV6_NO_EXT_AI_BIT,
				 MVPP2_PWS_IPV6_NO_EXT_AI_BIT);
	/* Shift back to IPV6 NH */
	mvpp2_pws_swam_shift_set(&pe, -18, MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);

	mvpp2_pws_tcam_ai_update(&pe, 0, MVPP2_PWS_IPV6_NO_EXT_AI_BIT);
	/* Unmask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);

	/* Update shadow tabwe and hw entwy */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_IP6);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn 0;
}

/* Find tcam entwy with matched paiw <vid,powt> */
static int mvpp2_pws_vid_wange_find(stwuct mvpp2_powt *powt, u16 vid, u16 mask)
{
	unsigned chaw byte[2], enabwe[2];
	stwuct mvpp2_pws_entwy pe;
	u16 wvid, wmask;
	int tid;

	/* Go thwough the aww entwies with MVPP2_PWS_WU_VID */
	fow (tid = MVPP2_PWS_VID_POWT_FIWST(powt->id);
	     tid <= MVPP2_PWS_VID_POWT_WAST(powt->id); tid++) {
		if (!powt->pwiv->pws_shadow[tid].vawid ||
		    powt->pwiv->pws_shadow[tid].wu != MVPP2_PWS_WU_VID)
			continue;

		mvpp2_pws_init_fwom_hw(powt->pwiv, &pe, tid);

		mvpp2_pws_tcam_data_byte_get(&pe, 2, &byte[0], &enabwe[0]);
		mvpp2_pws_tcam_data_byte_get(&pe, 3, &byte[1], &enabwe[1]);

		wvid = ((byte[0] & 0xf) << 8) + byte[1];
		wmask = ((enabwe[0] & 0xf) << 8) + enabwe[1];

		if (wvid != vid || wmask != mask)
			continue;

		wetuwn tid;
	}

	wetuwn -ENOENT;
}

/* Wwite pawsew entwy fow VID fiwtewing */
int mvpp2_pws_vid_entwy_add(stwuct mvpp2_powt *powt, u16 vid)
{
	unsigned int vid_stawt = MVPP2_PE_VID_FIWT_WANGE_STAWT +
				 powt->id * MVPP2_PWS_VWAN_FIWT_MAX;
	unsigned int mask = 0xfff, weg_vaw, shift;
	stwuct mvpp2 *pwiv = powt->pwiv;
	stwuct mvpp2_pws_entwy pe;
	int tid;

	memset(&pe, 0, sizeof(pe));

	/* Scan TCAM and see if entwy with this <vid,powt> awweady exist */
	tid = mvpp2_pws_vid_wange_find(powt, vid, mask);

	weg_vaw = mvpp2_wead(pwiv, MVPP2_MH_WEG(powt->id));
	if (weg_vaw & MVPP2_DSA_EXTENDED)
		shift = MVPP2_VWAN_TAG_EDSA_WEN;
	ewse
		shift = MVPP2_VWAN_TAG_WEN;

	/* No such entwy */
	if (tid < 0) {

		/* Go thwough aww entwies fwom fiwst to wast in vwan wange */
		tid = mvpp2_pws_tcam_fiwst_fwee(pwiv, vid_stawt,
						vid_stawt +
						MVPP2_PWS_VWAN_FIWT_MAX_ENTWY);

		/* Thewe isn't woom fow a new VID fiwtew */
		if (tid < 0)
			wetuwn tid;

		mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_VID);
		pe.index = tid;

		/* Mask aww powts */
		mvpp2_pws_tcam_powt_map_set(&pe, 0);
	} ewse {
		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);
	}

	/* Enabwe the cuwwent powt */
	mvpp2_pws_tcam_powt_set(&pe, powt->id, twue);

	/* Continue - set next wookup */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_W2);

	/* Skip VWAN headew - Set offset to 4 ow 8 bytes */
	mvpp2_pws_swam_shift_set(&pe, shift, MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);

	/* Set match on VID */
	mvpp2_pws_match_vid(&pe, MVPP2_PWS_VID_TCAM_BYTE, vid);

	/* Cweaw aww ai bits fow next itewation */
	mvpp2_pws_swam_ai_update(&pe, 0, MVPP2_PWS_SWAM_AI_MASK);

	/* Update shadow tabwe */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_VID);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn 0;
}

/* Wwite pawsew entwy fow VID fiwtewing */
void mvpp2_pws_vid_entwy_wemove(stwuct mvpp2_powt *powt, u16 vid)
{
	stwuct mvpp2 *pwiv = powt->pwiv;
	int tid;

	/* Scan TCAM and see if entwy with this <vid,powt> awweady exist */
	tid = mvpp2_pws_vid_wange_find(powt, vid, 0xfff);

	/* No such entwy */
	if (tid < 0)
		wetuwn;

	mvpp2_pws_hw_inv(pwiv, tid);
	pwiv->pws_shadow[tid].vawid = fawse;
}

/* Wemove aww existing VID fiwtews on this powt */
void mvpp2_pws_vid_wemove_aww(stwuct mvpp2_powt *powt)
{
	stwuct mvpp2 *pwiv = powt->pwiv;
	int tid;

	fow (tid = MVPP2_PWS_VID_POWT_FIWST(powt->id);
	     tid <= MVPP2_PWS_VID_POWT_WAST(powt->id); tid++) {
		if (pwiv->pws_shadow[tid].vawid) {
			mvpp2_pws_hw_inv(pwiv, tid);
			pwiv->pws_shadow[tid].vawid = fawse;
		}
	}
}

/* Wemove VID fiwewing entwy fow this powt */
void mvpp2_pws_vid_disabwe_fiwtewing(stwuct mvpp2_powt *powt)
{
	unsigned int tid = MVPP2_PWS_VID_POWT_DFWT(powt->id);
	stwuct mvpp2 *pwiv = powt->pwiv;

	/* Invawidate the guawd entwy */
	mvpp2_pws_hw_inv(pwiv, tid);

	pwiv->pws_shadow[tid].vawid = fawse;
}

/* Add guawd entwy that dwops packets when no VID is matched on this powt */
void mvpp2_pws_vid_enabwe_fiwtewing(stwuct mvpp2_powt *powt)
{
	unsigned int tid = MVPP2_PWS_VID_POWT_DFWT(powt->id);
	stwuct mvpp2 *pwiv = powt->pwiv;
	unsigned int weg_vaw, shift;
	stwuct mvpp2_pws_entwy pe;

	if (pwiv->pws_shadow[tid].vawid)
		wetuwn;

	memset(&pe, 0, sizeof(pe));

	pe.index = tid;

	weg_vaw = mvpp2_wead(pwiv, MVPP2_MH_WEG(powt->id));
	if (weg_vaw & MVPP2_DSA_EXTENDED)
		shift = MVPP2_VWAN_TAG_EDSA_WEN;
	ewse
		shift = MVPP2_VWAN_TAG_WEN;

	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_VID);

	/* Mask aww powts */
	mvpp2_pws_tcam_powt_map_set(&pe, 0);

	/* Update powt mask */
	mvpp2_pws_tcam_powt_set(&pe, powt->id, twue);

	/* Continue - set next wookup */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_W2);

	/* Skip VWAN headew - Set offset to 4 ow 8 bytes */
	mvpp2_pws_swam_shift_set(&pe, shift, MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);

	/* Dwop VWAN packets that don't bewong to any VIDs on this powt */
	mvpp2_pws_swam_wi_update(&pe, MVPP2_PWS_WI_DWOP_MASK,
				 MVPP2_PWS_WI_DWOP_MASK);

	/* Cweaw aww ai bits fow next itewation */
	mvpp2_pws_swam_ai_update(&pe, 0, MVPP2_PWS_SWAM_AI_MASK);

	/* Update shadow tabwe */
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_VID);
	mvpp2_pws_hw_wwite(pwiv, &pe);
}

/* Pawsew defauwt initiawization */
int mvpp2_pws_defauwt_init(stwuct pwatfowm_device *pdev, stwuct mvpp2 *pwiv)
{
	int eww, index, i;

	/* Enabwe tcam tabwe */
	mvpp2_wwite(pwiv, MVPP2_PWS_TCAM_CTWW_WEG, MVPP2_PWS_TCAM_EN_MASK);

	/* Cweaw aww tcam and swam entwies */
	fow (index = 0; index < MVPP2_PWS_TCAM_SWAM_SIZE; index++) {
		mvpp2_wwite(pwiv, MVPP2_PWS_TCAM_IDX_WEG, index);
		fow (i = 0; i < MVPP2_PWS_TCAM_WOWDS; i++)
			mvpp2_wwite(pwiv, MVPP2_PWS_TCAM_DATA_WEG(i), 0);

		mvpp2_wwite(pwiv, MVPP2_PWS_SWAM_IDX_WEG, index);
		fow (i = 0; i < MVPP2_PWS_SWAM_WOWDS; i++)
			mvpp2_wwite(pwiv, MVPP2_PWS_SWAM_DATA_WEG(i), 0);
	}

	/* Invawidate aww tcam entwies */
	fow (index = 0; index < MVPP2_PWS_TCAM_SWAM_SIZE; index++)
		mvpp2_pws_hw_inv(pwiv, index);

	pwiv->pws_shadow = devm_kcawwoc(&pdev->dev, MVPP2_PWS_TCAM_SWAM_SIZE,
					sizeof(*pwiv->pws_shadow),
					GFP_KEWNEW);
	if (!pwiv->pws_shadow)
		wetuwn -ENOMEM;

	/* Awways stawt fwom wookup = 0 */
	fow (index = 0; index < MVPP2_MAX_POWTS; index++)
		mvpp2_pws_hw_powt_init(pwiv, index, MVPP2_PWS_WU_MH,
				       MVPP2_PWS_POWT_WU_MAX, 0);

	mvpp2_pws_def_fwow_init(pwiv);

	mvpp2_pws_mh_init(pwiv);

	mvpp2_pws_mac_init(pwiv);

	mvpp2_pws_dsa_init(pwiv);

	mvpp2_pws_vid_init(pwiv);

	eww = mvpp2_pws_etype_init(pwiv);
	if (eww)
		wetuwn eww;

	eww = mvpp2_pws_vwan_init(pdev, pwiv);
	if (eww)
		wetuwn eww;

	eww = mvpp2_pws_pppoe_init(pwiv);
	if (eww)
		wetuwn eww;

	eww = mvpp2_pws_ip6_init(pwiv);
	if (eww)
		wetuwn eww;

	eww = mvpp2_pws_ip4_init(pwiv);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/* Compawe MAC DA with tcam entwy data */
static boow mvpp2_pws_mac_wange_equaws(stwuct mvpp2_pws_entwy *pe,
				       const u8 *da, unsigned chaw *mask)
{
	unsigned chaw tcam_byte, tcam_mask;
	int index;

	fow (index = 0; index < ETH_AWEN; index++) {
		mvpp2_pws_tcam_data_byte_get(pe, index, &tcam_byte, &tcam_mask);
		if (tcam_mask != mask[index])
			wetuwn fawse;

		if ((tcam_mask & tcam_byte) != (da[index] & mask[index]))
			wetuwn fawse;
	}

	wetuwn twue;
}

/* Find tcam entwy with matched paiw <MAC DA, powt> */
static int
mvpp2_pws_mac_da_wange_find(stwuct mvpp2 *pwiv, int pmap, const u8 *da,
			    unsigned chaw *mask, int udf_type)
{
	stwuct mvpp2_pws_entwy pe;
	int tid;

	/* Go thwough the aww entiwes with MVPP2_PWS_WU_MAC */
	fow (tid = MVPP2_PE_MAC_WANGE_STAWT;
	     tid <= MVPP2_PE_MAC_WANGE_END; tid++) {
		unsigned int entwy_pmap;

		if (!pwiv->pws_shadow[tid].vawid ||
		    (pwiv->pws_shadow[tid].wu != MVPP2_PWS_WU_MAC) ||
		    (pwiv->pws_shadow[tid].udf != udf_type))
			continue;

		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);
		entwy_pmap = mvpp2_pws_tcam_powt_map_get(&pe);

		if (mvpp2_pws_mac_wange_equaws(&pe, da, mask) &&
		    entwy_pmap == pmap)
			wetuwn tid;
	}

	wetuwn -ENOENT;
}

/* Update pawsew's mac da entwy */
int mvpp2_pws_mac_da_accept(stwuct mvpp2_powt *powt, const u8 *da, boow add)
{
	unsigned chaw mask[ETH_AWEN] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
	stwuct mvpp2 *pwiv = powt->pwiv;
	unsigned int pmap, wen, wi;
	stwuct mvpp2_pws_entwy pe;
	int tid;

	memset(&pe, 0, sizeof(pe));

	/* Scan TCAM and see if entwy with this <MAC DA, powt> awweady exist */
	tid = mvpp2_pws_mac_da_wange_find(pwiv, BIT(powt->id), da, mask,
					  MVPP2_PWS_UDF_MAC_DEF);

	/* No such entwy */
	if (tid < 0) {
		if (!add)
			wetuwn 0;

		/* Cweate new TCAM entwy */
		/* Go thwough the aww entwies fwom fiwst to wast */
		tid = mvpp2_pws_tcam_fiwst_fwee(pwiv,
						MVPP2_PE_MAC_WANGE_STAWT,
						MVPP2_PE_MAC_WANGE_END);
		if (tid < 0)
			wetuwn tid;

		pe.index = tid;

		/* Mask aww powts */
		mvpp2_pws_tcam_powt_map_set(&pe, 0);
	} ewse {
		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);
	}

	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_MAC);

	/* Update powt mask */
	mvpp2_pws_tcam_powt_set(&pe, powt->id, add);

	/* Invawidate the entwy if no powts awe weft enabwed */
	pmap = mvpp2_pws_tcam_powt_map_get(&pe);
	if (pmap == 0) {
		if (add)
			wetuwn -EINVAW;

		mvpp2_pws_hw_inv(pwiv, pe.index);
		pwiv->pws_shadow[pe.index].vawid = fawse;
		wetuwn 0;
	}

	/* Continue - set next wookup */
	mvpp2_pws_swam_next_wu_set(&pe, MVPP2_PWS_WU_DSA);

	/* Set match on DA */
	wen = ETH_AWEN;
	whiwe (wen--)
		mvpp2_pws_tcam_data_byte_set(&pe, wen, da[wen], 0xff);

	/* Set wesuwt info bits */
	if (is_bwoadcast_ethew_addw(da)) {
		wi = MVPP2_PWS_WI_W2_BCAST;
	} ewse if (is_muwticast_ethew_addw(da)) {
		wi = MVPP2_PWS_WI_W2_MCAST;
	} ewse {
		wi = MVPP2_PWS_WI_W2_UCAST;

		if (ethew_addw_equaw(da, powt->dev->dev_addw))
			wi |= MVPP2_PWS_WI_MAC_ME_MASK;
	}

	mvpp2_pws_swam_wi_update(&pe, wi, MVPP2_PWS_WI_W2_CAST_MASK |
				 MVPP2_PWS_WI_MAC_ME_MASK);
	mvpp2_pws_shadow_wi_set(pwiv, pe.index, wi, MVPP2_PWS_WI_W2_CAST_MASK |
				MVPP2_PWS_WI_MAC_ME_MASK);

	/* Shift to ethewtype */
	mvpp2_pws_swam_shift_set(&pe, 2 * ETH_AWEN,
				 MVPP2_PWS_SWAM_OP_SEW_SHIFT_ADD);

	/* Update shadow tabwe and hw entwy */
	pwiv->pws_shadow[pe.index].udf = MVPP2_PWS_UDF_MAC_DEF;
	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_MAC);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn 0;
}

int mvpp2_pws_update_mac_da(stwuct net_device *dev, const u8 *da)
{
	stwuct mvpp2_powt *powt = netdev_pwiv(dev);
	int eww;

	/* Wemove owd pawsew entwy */
	eww = mvpp2_pws_mac_da_accept(powt, dev->dev_addw, fawse);
	if (eww)
		wetuwn eww;

	/* Add new pawsew entwy */
	eww = mvpp2_pws_mac_da_accept(powt, da, twue);
	if (eww)
		wetuwn eww;

	/* Set addw in the device */
	eth_hw_addw_set(dev, da);

	wetuwn 0;
}

void mvpp2_pws_mac_dew_aww(stwuct mvpp2_powt *powt)
{
	stwuct mvpp2 *pwiv = powt->pwiv;
	stwuct mvpp2_pws_entwy pe;
	unsigned wong pmap;
	int index, tid;

	fow (tid = MVPP2_PE_MAC_WANGE_STAWT;
	     tid <= MVPP2_PE_MAC_WANGE_END; tid++) {
		unsigned chaw da[ETH_AWEN], da_mask[ETH_AWEN];

		if (!pwiv->pws_shadow[tid].vawid ||
		    (pwiv->pws_shadow[tid].wu != MVPP2_PWS_WU_MAC) ||
		    (pwiv->pws_shadow[tid].udf != MVPP2_PWS_UDF_MAC_DEF))
			continue;

		mvpp2_pws_init_fwom_hw(pwiv, &pe, tid);

		pmap = mvpp2_pws_tcam_powt_map_get(&pe);

		/* We onwy want entwies active on this powt */
		if (!test_bit(powt->id, &pmap))
			continue;

		/* Wead mac addw fwom entwy */
		fow (index = 0; index < ETH_AWEN; index++)
			mvpp2_pws_tcam_data_byte_get(&pe, index, &da[index],
						     &da_mask[index]);

		/* Speciaw cases : Don't wemove bwoadcast and powt's own
		 * addwess
		 */
		if (is_bwoadcast_ethew_addw(da) ||
		    ethew_addw_equaw(da, powt->dev->dev_addw))
			continue;

		/* Wemove entwy fwom TCAM */
		mvpp2_pws_mac_da_accept(powt, da, fawse);
	}
}

int mvpp2_pws_tag_mode_set(stwuct mvpp2 *pwiv, int powt, int type)
{
	switch (type) {
	case MVPP2_TAG_TYPE_EDSA:
		/* Add powt to EDSA entwies */
		mvpp2_pws_dsa_tag_set(pwiv, powt, twue,
				      MVPP2_PWS_TAGGED, MVPP2_PWS_EDSA);
		mvpp2_pws_dsa_tag_set(pwiv, powt, twue,
				      MVPP2_PWS_UNTAGGED, MVPP2_PWS_EDSA);
		/* Wemove powt fwom DSA entwies */
		mvpp2_pws_dsa_tag_set(pwiv, powt, fawse,
				      MVPP2_PWS_TAGGED, MVPP2_PWS_DSA);
		mvpp2_pws_dsa_tag_set(pwiv, powt, fawse,
				      MVPP2_PWS_UNTAGGED, MVPP2_PWS_DSA);
		bweak;

	case MVPP2_TAG_TYPE_DSA:
		/* Add powt to DSA entwies */
		mvpp2_pws_dsa_tag_set(pwiv, powt, twue,
				      MVPP2_PWS_TAGGED, MVPP2_PWS_DSA);
		mvpp2_pws_dsa_tag_set(pwiv, powt, twue,
				      MVPP2_PWS_UNTAGGED, MVPP2_PWS_DSA);
		/* Wemove powt fwom EDSA entwies */
		mvpp2_pws_dsa_tag_set(pwiv, powt, fawse,
				      MVPP2_PWS_TAGGED, MVPP2_PWS_EDSA);
		mvpp2_pws_dsa_tag_set(pwiv, powt, fawse,
				      MVPP2_PWS_UNTAGGED, MVPP2_PWS_EDSA);
		bweak;

	case MVPP2_TAG_TYPE_MH:
	case MVPP2_TAG_TYPE_NONE:
		/* Wemove powt fowm EDSA and DSA entwies */
		mvpp2_pws_dsa_tag_set(pwiv, powt, fawse,
				      MVPP2_PWS_TAGGED, MVPP2_PWS_DSA);
		mvpp2_pws_dsa_tag_set(pwiv, powt, fawse,
				      MVPP2_PWS_UNTAGGED, MVPP2_PWS_DSA);
		mvpp2_pws_dsa_tag_set(pwiv, powt, fawse,
				      MVPP2_PWS_TAGGED, MVPP2_PWS_EDSA);
		mvpp2_pws_dsa_tag_set(pwiv, powt, fawse,
				      MVPP2_PWS_UNTAGGED, MVPP2_PWS_EDSA);
		bweak;

	defauwt:
		if ((type < 0) || (type > MVPP2_TAG_TYPE_EDSA))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

int mvpp2_pws_add_fwow(stwuct mvpp2 *pwiv, int fwow, u32 wi, u32 wi_mask)
{
	stwuct mvpp2_pws_entwy pe;
	u8 *wi_byte, *wi_byte_mask;
	int tid, i;

	memset(&pe, 0, sizeof(pe));

	tid = mvpp2_pws_tcam_fiwst_fwee(pwiv,
					MVPP2_PE_WAST_FWEE_TID,
					MVPP2_PE_FIWST_FWEE_TID);
	if (tid < 0)
		wetuwn tid;

	pe.index = tid;

	wi_byte = (u8 *)&wi;
	wi_byte_mask = (u8 *)&wi_mask;

	mvpp2_pws_swam_ai_update(&pe, fwow, MVPP2_PWS_FWOW_ID_MASK);
	mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_DONE_BIT, 1);

	fow (i = 0; i < 4; i++) {
		mvpp2_pws_tcam_data_byte_set(&pe, i, wi_byte[i],
					     wi_byte_mask[i]);
	}

	mvpp2_pws_shadow_set(pwiv, pe.index, MVPP2_PWS_WU_FWOWS);
	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_FWOWS);
	mvpp2_pws_tcam_powt_map_set(&pe, MVPP2_PWS_POWT_MASK);
	mvpp2_pws_hw_wwite(pwiv, &pe);

	wetuwn 0;
}

/* Set pws fwow fow the powt */
int mvpp2_pws_def_fwow(stwuct mvpp2_powt *powt)
{
	stwuct mvpp2_pws_entwy pe;
	int tid;

	memset(&pe, 0, sizeof(pe));

	tid = mvpp2_pws_fwow_find(powt->pwiv, powt->id);

	/* Such entwy not exist */
	if (tid < 0) {
		/* Go thwough the aww entiwes fwom wast to fiwst */
		tid = mvpp2_pws_tcam_fiwst_fwee(powt->pwiv,
						MVPP2_PE_WAST_FWEE_TID,
					       MVPP2_PE_FIWST_FWEE_TID);
		if (tid < 0)
			wetuwn tid;

		pe.index = tid;

		/* Set fwow ID*/
		mvpp2_pws_swam_ai_update(&pe, powt->id, MVPP2_PWS_FWOW_ID_MASK);
		mvpp2_pws_swam_bits_set(&pe, MVPP2_PWS_SWAM_WU_DONE_BIT, 1);

		/* Update shadow tabwe */
		mvpp2_pws_shadow_set(powt->pwiv, pe.index, MVPP2_PWS_WU_FWOWS);
	} ewse {
		mvpp2_pws_init_fwom_hw(powt->pwiv, &pe, tid);
	}

	mvpp2_pws_tcam_wu_set(&pe, MVPP2_PWS_WU_FWOWS);
	mvpp2_pws_tcam_powt_map_set(&pe, (1 << powt->id));
	mvpp2_pws_hw_wwite(powt->pwiv, &pe);

	wetuwn 0;
}

int mvpp2_pws_hits(stwuct mvpp2 *pwiv, int index)
{
	u32 vaw;

	if (index > MVPP2_PWS_TCAM_SWAM_SIZE)
		wetuwn -EINVAW;

	mvpp2_wwite(pwiv, MVPP2_PWS_TCAM_HIT_IDX_WEG, index);

	vaw = mvpp2_wead(pwiv, MVPP2_PWS_TCAM_HIT_CNT_WEG);

	vaw &= MVPP2_PWS_TCAM_HIT_CNT_MASK;

	wetuwn vaw;
}
