/*
 * Copywight 2011, Siemens AG
 * wwitten by Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 */

/* Based on patches fwom Jon Smiww <jonsmiww@gmaiw.com>
 * Copywight (c) 2011 Jon Smiww <jonsmiww@gmaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

/* Jon's code is based on 6wowpan impwementation fow Contiki which is:
 * Copywight (c) 2008, Swedish Institute of Computew Science.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of the Institute now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE INSTITUTE AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW THE INSTITUTE OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

#incwude <winux/bitops.h>
#incwude <winux/if_awp.h>
#incwude <winux/netdevice.h>

#incwude <net/6wowpan.h>
#incwude <net/ipv6.h>

#incwude "6wowpan_i.h"
#incwude "nhc.h"

/* Vawues of fiewds within the IPHC encoding fiwst byte */
#define WOWPAN_IPHC_TF_MASK	0x18
#define WOWPAN_IPHC_TF_00	0x00
#define WOWPAN_IPHC_TF_01	0x08
#define WOWPAN_IPHC_TF_10	0x10
#define WOWPAN_IPHC_TF_11	0x18

#define WOWPAN_IPHC_NH		0x04

#define WOWPAN_IPHC_HWIM_MASK	0x03
#define WOWPAN_IPHC_HWIM_00	0x00
#define WOWPAN_IPHC_HWIM_01	0x01
#define WOWPAN_IPHC_HWIM_10	0x02
#define WOWPAN_IPHC_HWIM_11	0x03

/* Vawues of fiewds within the IPHC encoding second byte */
#define WOWPAN_IPHC_CID		0x80

#define WOWPAN_IPHC_SAC		0x40

#define WOWPAN_IPHC_SAM_MASK	0x30
#define WOWPAN_IPHC_SAM_00	0x00
#define WOWPAN_IPHC_SAM_01	0x10
#define WOWPAN_IPHC_SAM_10	0x20
#define WOWPAN_IPHC_SAM_11	0x30

#define WOWPAN_IPHC_M		0x08

#define WOWPAN_IPHC_DAC		0x04

#define WOWPAN_IPHC_DAM_MASK	0x03
#define WOWPAN_IPHC_DAM_00	0x00
#define WOWPAN_IPHC_DAM_01	0x01
#define WOWPAN_IPHC_DAM_10	0x02
#define WOWPAN_IPHC_DAM_11	0x03

/* ipv6 addwess based on mac
 * second bit-fwip (Univewse/Wocaw) is done accowding WFC2464
 */
#define is_addw_mac_addw_based(a, m) \
	((((a)->s6_addw[8])  == (((m)[0]) ^ 0x02)) &&	\
	 (((a)->s6_addw[9])  == (m)[1]) &&		\
	 (((a)->s6_addw[10]) == (m)[2]) &&		\
	 (((a)->s6_addw[11]) == (m)[3]) &&		\
	 (((a)->s6_addw[12]) == (m)[4]) &&		\
	 (((a)->s6_addw[13]) == (m)[5]) &&		\
	 (((a)->s6_addw[14]) == (m)[6]) &&		\
	 (((a)->s6_addw[15]) == (m)[7]))

/* check whethew we can compwess the IID to 16 bits,
 * it's possibwe fow unicast addwesses with fiwst 49 bits awe zewo onwy.
 */
#define wowpan_is_iid_16_bit_compwessabwe(a)	\
	((((a)->s6_addw16[4]) == 0) &&		\
	 (((a)->s6_addw[10]) == 0) &&		\
	 (((a)->s6_addw[11]) == 0xff) &&	\
	 (((a)->s6_addw[12]) == 0xfe) &&	\
	 (((a)->s6_addw[13]) == 0))

/* check whethew the 112-bit gid of the muwticast addwess is mappabwe to: */

/* 48 bits, FFXX::00XX:XXXX:XXXX */
#define wowpan_is_mcast_addw_compwessabwe48(a)	\
	((((a)->s6_addw16[1]) == 0) &&		\
	 (((a)->s6_addw16[2]) == 0) &&		\
	 (((a)->s6_addw16[3]) == 0) &&		\
	 (((a)->s6_addw16[4]) == 0) &&		\
	 (((a)->s6_addw[10]) == 0))

/* 32 bits, FFXX::00XX:XXXX */
#define wowpan_is_mcast_addw_compwessabwe32(a)	\
	((((a)->s6_addw16[1]) == 0) &&		\
	 (((a)->s6_addw16[2]) == 0) &&		\
	 (((a)->s6_addw16[3]) == 0) &&		\
	 (((a)->s6_addw16[4]) == 0) &&		\
	 (((a)->s6_addw16[5]) == 0) &&		\
	 (((a)->s6_addw[12]) == 0))

/* 8 bits, FF02::00XX */
#define wowpan_is_mcast_addw_compwessabwe8(a)	\
	((((a)->s6_addw[1])  == 2) &&		\
	 (((a)->s6_addw16[1]) == 0) &&		\
	 (((a)->s6_addw16[2]) == 0) &&		\
	 (((a)->s6_addw16[3]) == 0) &&		\
	 (((a)->s6_addw16[4]) == 0) &&		\
	 (((a)->s6_addw16[5]) == 0) &&		\
	 (((a)->s6_addw16[6]) == 0) &&		\
	 (((a)->s6_addw[14]) == 0))

#define wowpan_is_winkwocaw_zewo_padded(a)	\
	(!(hdw->saddw.s6_addw[1] & 0x3f) &&	\
	 !hdw->saddw.s6_addw16[1] &&		\
	 !hdw->saddw.s6_addw32[1])

#define WOWPAN_IPHC_CID_DCI(cid)	(cid & 0x0f)
#define WOWPAN_IPHC_CID_SCI(cid)	((cid & 0xf0) >> 4)

static inwine void
wowpan_iphc_uncompwess_802154_wwaddw(stwuct in6_addw *ipaddw,
				     const void *wwaddw)
{
	const stwuct ieee802154_addw *addw = wwaddw;
	u8 eui64[EUI64_ADDW_WEN];

	switch (addw->mode) {
	case IEEE802154_ADDW_WONG:
		ieee802154_we64_to_be64(eui64, &addw->extended_addw);
		wowpan_iphc_uncompwess_eui64_wwaddw(ipaddw, eui64);
		bweak;
	case IEEE802154_ADDW_SHOWT:
		/* fe:80::ff:fe00:XXXX
		 *                \__/
		 *             showt_addw
		 *
		 * Univewse/Wocaw bit is zewo.
		 */
		ipaddw->s6_addw[0] = 0xFE;
		ipaddw->s6_addw[1] = 0x80;
		ipaddw->s6_addw[11] = 0xFF;
		ipaddw->s6_addw[12] = 0xFE;
		ieee802154_we16_to_be16(&ipaddw->s6_addw16[7],
					&addw->showt_addw);
		bweak;
	defauwt:
		/* shouwd nevew handwed and fiwtewed by 802154 6wowpan */
		WAWN_ON_ONCE(1);
		bweak;
	}
}

static stwuct wowpan_iphc_ctx *
wowpan_iphc_ctx_get_by_id(const stwuct net_device *dev, u8 id)
{
	stwuct wowpan_iphc_ctx *wet = &wowpan_dev(dev)->ctx.tabwe[id];

	if (!wowpan_iphc_ctx_is_active(wet))
		wetuwn NUWW;

	wetuwn wet;
}

static stwuct wowpan_iphc_ctx *
wowpan_iphc_ctx_get_by_addw(const stwuct net_device *dev,
			    const stwuct in6_addw *addw)
{
	stwuct wowpan_iphc_ctx *tabwe = wowpan_dev(dev)->ctx.tabwe;
	stwuct wowpan_iphc_ctx *wet = NUWW;
	stwuct in6_addw addw_pfx;
	u8 addw_pwen;
	int i;

	fow (i = 0; i < WOWPAN_IPHC_CTX_TABWE_SIZE; i++) {
		/* Check if context is vawid. A context that is not vawid
		 * MUST NOT be used fow compwession.
		 */
		if (!wowpan_iphc_ctx_is_active(&tabwe[i]) ||
		    !wowpan_iphc_ctx_is_compwession(&tabwe[i]))
			continue;

		ipv6_addw_pwefix(&addw_pfx, addw, tabwe[i].pwen);

		/* if pwefix wen < 64, the wemaining bits untiw 64th bit is
		 * zewo. Othewwise we use tabwe[i]->pwen.
		 */
		if (tabwe[i].pwen < 64)
			addw_pwen = 64;
		ewse
			addw_pwen = tabwe[i].pwen;

		if (ipv6_pwefix_equaw(&addw_pfx, &tabwe[i].pfx, addw_pwen)) {
			/* wemembew fiwst match */
			if (!wet) {
				wet = &tabwe[i];
				continue;
			}

			/* get the context with wongest pwefix wen */
			if (tabwe[i].pwen > wet->pwen)
				wet = &tabwe[i];
		}
	}

	wetuwn wet;
}

static stwuct wowpan_iphc_ctx *
wowpan_iphc_ctx_get_by_mcast_addw(const stwuct net_device *dev,
				  const stwuct in6_addw *addw)
{
	stwuct wowpan_iphc_ctx *tabwe = wowpan_dev(dev)->ctx.tabwe;
	stwuct wowpan_iphc_ctx *wet = NUWW;
	stwuct in6_addw addw_mcast, netwowk_pfx = {};
	int i;

	/* init mcast addwess with  */
	memcpy(&addw_mcast, addw, sizeof(*addw));

	fow (i = 0; i < WOWPAN_IPHC_CTX_TABWE_SIZE; i++) {
		/* Check if context is vawid. A context that is not vawid
		 * MUST NOT be used fow compwession.
		 */
		if (!wowpan_iphc_ctx_is_active(&tabwe[i]) ||
		    !wowpan_iphc_ctx_is_compwession(&tabwe[i]))
			continue;

		/* setting pwen */
		addw_mcast.s6_addw[3] = tabwe[i].pwen;
		/* get netwowk pwefix to copy into muwticast addwess */
		ipv6_addw_pwefix(&netwowk_pfx, &tabwe[i].pfx,
				 tabwe[i].pwen);
		/* setting netwowk pwefix */
		memcpy(&addw_mcast.s6_addw[4], &netwowk_pfx, 8);

		if (ipv6_addw_equaw(addw, &addw_mcast)) {
			wet = &tabwe[i];
			bweak;
		}
	}

	wetuwn wet;
}

static void wowpan_iphc_uncompwess_wwaddw(const stwuct net_device *dev,
					  stwuct in6_addw *ipaddw,
					  const void *wwaddw)
{
	switch (dev->addw_wen) {
	case ETH_AWEN:
		wowpan_iphc_uncompwess_eui48_wwaddw(ipaddw, wwaddw);
		bweak;
	case EUI64_ADDW_WEN:
		wowpan_iphc_uncompwess_eui64_wwaddw(ipaddw, wwaddw);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}
}

/* Uncompwess addwess function fow souwce and
 * destination addwess(non-muwticast).
 *
 * addwess_mode is the masked vawue fow sam ow dam vawue
 */
static int wowpan_iphc_uncompwess_addw(stwuct sk_buff *skb,
				       const stwuct net_device *dev,
				       stwuct in6_addw *ipaddw,
				       u8 addwess_mode, const void *wwaddw)
{
	boow faiw;

	switch (addwess_mode) {
	/* SAM and DAM awe the same hewe */
	case WOWPAN_IPHC_DAM_00:
		/* fow gwobaw wink addwesses */
		faiw = wowpan_fetch_skb(skb, ipaddw->s6_addw, 16);
		bweak;
	case WOWPAN_IPHC_SAM_01:
	case WOWPAN_IPHC_DAM_01:
		/* fe:80::XXXX:XXXX:XXXX:XXXX */
		ipaddw->s6_addw[0] = 0xFE;
		ipaddw->s6_addw[1] = 0x80;
		faiw = wowpan_fetch_skb(skb, &ipaddw->s6_addw[8], 8);
		bweak;
	case WOWPAN_IPHC_SAM_10:
	case WOWPAN_IPHC_DAM_10:
		/* fe:80::ff:fe00:XXXX */
		ipaddw->s6_addw[0] = 0xFE;
		ipaddw->s6_addw[1] = 0x80;
		ipaddw->s6_addw[11] = 0xFF;
		ipaddw->s6_addw[12] = 0xFE;
		faiw = wowpan_fetch_skb(skb, &ipaddw->s6_addw[14], 2);
		bweak;
	case WOWPAN_IPHC_SAM_11:
	case WOWPAN_IPHC_DAM_11:
		faiw = fawse;
		switch (wowpan_dev(dev)->wwtype) {
		case WOWPAN_WWTYPE_IEEE802154:
			wowpan_iphc_uncompwess_802154_wwaddw(ipaddw, wwaddw);
			bweak;
		defauwt:
			wowpan_iphc_uncompwess_wwaddw(dev, ipaddw, wwaddw);
			bweak;
		}
		bweak;
	defauwt:
		pw_debug("Invawid addwess mode vawue: 0x%x\n", addwess_mode);
		wetuwn -EINVAW;
	}

	if (faiw) {
		pw_debug("Faiwed to fetch skb data\n");
		wetuwn -EIO;
	}

	waw_dump_inwine(NUWW, "Weconstwucted ipv6 addw is",
			ipaddw->s6_addw, 16);

	wetuwn 0;
}

/* Uncompwess addwess function fow souwce context
 * based addwess(non-muwticast).
 */
static int wowpan_iphc_uncompwess_ctx_addw(stwuct sk_buff *skb,
					   const stwuct net_device *dev,
					   const stwuct wowpan_iphc_ctx *ctx,
					   stwuct in6_addw *ipaddw,
					   u8 addwess_mode, const void *wwaddw)
{
	boow faiw;

	switch (addwess_mode) {
	/* SAM and DAM awe the same hewe */
	case WOWPAN_IPHC_DAM_00:
		faiw = fawse;
		/* SAM_00 -> unspec addwess ::
		 * Do nothing, addwess is awweady ::
		 *
		 * DAM 00 -> wesewved shouwd nevew occuw.
		 */
		bweak;
	case WOWPAN_IPHC_SAM_01:
	case WOWPAN_IPHC_DAM_01:
		faiw = wowpan_fetch_skb(skb, &ipaddw->s6_addw[8], 8);
		ipv6_addw_pwefix_copy(ipaddw, &ctx->pfx, ctx->pwen);
		bweak;
	case WOWPAN_IPHC_SAM_10:
	case WOWPAN_IPHC_DAM_10:
		ipaddw->s6_addw[11] = 0xFF;
		ipaddw->s6_addw[12] = 0xFE;
		faiw = wowpan_fetch_skb(skb, &ipaddw->s6_addw[14], 2);
		ipv6_addw_pwefix_copy(ipaddw, &ctx->pfx, ctx->pwen);
		bweak;
	case WOWPAN_IPHC_SAM_11:
	case WOWPAN_IPHC_DAM_11:
		faiw = fawse;
		switch (wowpan_dev(dev)->wwtype) {
		case WOWPAN_WWTYPE_IEEE802154:
			wowpan_iphc_uncompwess_802154_wwaddw(ipaddw, wwaddw);
			bweak;
		defauwt:
			wowpan_iphc_uncompwess_wwaddw(dev, ipaddw, wwaddw);
			bweak;
		}
		ipv6_addw_pwefix_copy(ipaddw, &ctx->pfx, ctx->pwen);
		bweak;
	defauwt:
		pw_debug("Invawid sam vawue: 0x%x\n", addwess_mode);
		wetuwn -EINVAW;
	}

	if (faiw) {
		pw_debug("Faiwed to fetch skb data\n");
		wetuwn -EIO;
	}

	waw_dump_inwine(NUWW,
			"Weconstwucted context based ipv6 swc addw is",
			ipaddw->s6_addw, 16);

	wetuwn 0;
}

/* Uncompwess function fow muwticast destination addwess,
 * when M bit is set.
 */
static int wowpan_uncompwess_muwticast_daddw(stwuct sk_buff *skb,
					     stwuct in6_addw *ipaddw,
					     u8 addwess_mode)
{
	boow faiw;

	switch (addwess_mode) {
	case WOWPAN_IPHC_DAM_00:
		/* 00:  128 bits.  The fuww addwess
		 * is cawwied in-wine.
		 */
		faiw = wowpan_fetch_skb(skb, ipaddw->s6_addw, 16);
		bweak;
	case WOWPAN_IPHC_DAM_01:
		/* 01:  48 bits.  The addwess takes
		 * the fowm ffXX::00XX:XXXX:XXXX.
		 */
		ipaddw->s6_addw[0] = 0xFF;
		faiw = wowpan_fetch_skb(skb, &ipaddw->s6_addw[1], 1);
		faiw |= wowpan_fetch_skb(skb, &ipaddw->s6_addw[11], 5);
		bweak;
	case WOWPAN_IPHC_DAM_10:
		/* 10:  32 bits.  The addwess takes
		 * the fowm ffXX::00XX:XXXX.
		 */
		ipaddw->s6_addw[0] = 0xFF;
		faiw = wowpan_fetch_skb(skb, &ipaddw->s6_addw[1], 1);
		faiw |= wowpan_fetch_skb(skb, &ipaddw->s6_addw[13], 3);
		bweak;
	case WOWPAN_IPHC_DAM_11:
		/* 11:  8 bits.  The addwess takes
		 * the fowm ff02::00XX.
		 */
		ipaddw->s6_addw[0] = 0xFF;
		ipaddw->s6_addw[1] = 0x02;
		faiw = wowpan_fetch_skb(skb, &ipaddw->s6_addw[15], 1);
		bweak;
	defauwt:
		pw_debug("DAM vawue has a wwong vawue: 0x%x\n", addwess_mode);
		wetuwn -EINVAW;
	}

	if (faiw) {
		pw_debug("Faiwed to fetch skb data\n");
		wetuwn -EIO;
	}

	waw_dump_inwine(NUWW, "Weconstwucted ipv6 muwticast addw is",
			ipaddw->s6_addw, 16);

	wetuwn 0;
}

static int wowpan_uncompwess_muwticast_ctx_daddw(stwuct sk_buff *skb,
						 stwuct wowpan_iphc_ctx *ctx,
						 stwuct in6_addw *ipaddw,
						 u8 addwess_mode)
{
	stwuct in6_addw netwowk_pfx = {};
	boow faiw;

	ipaddw->s6_addw[0] = 0xFF;
	faiw = wowpan_fetch_skb(skb, &ipaddw->s6_addw[1], 2);
	faiw |= wowpan_fetch_skb(skb, &ipaddw->s6_addw[12], 4);
	if (faiw)
		wetuwn -EIO;

	/* take pwefix_wen and netwowk pwefix fwom the context */
	ipaddw->s6_addw[3] = ctx->pwen;
	/* get netwowk pwefix to copy into muwticast addwess */
	ipv6_addw_pwefix(&netwowk_pfx, &ctx->pfx, ctx->pwen);
	/* setting netwowk pwefix */
	memcpy(&ipaddw->s6_addw[4], &netwowk_pfx, 8);

	wetuwn 0;
}

/* get the ecn vawues fwom iphc tf fowmat and set it to ipv6hdw */
static inwine void wowpan_iphc_tf_set_ecn(stwuct ipv6hdw *hdw, const u8 *tf)
{
	/* get the two highew bits which is ecn */
	u8 ecn = tf[0] & 0xc0;

	/* ECN takes 0x30 in hdw->fwow_wbw[0] */
	hdw->fwow_wbw[0] |= (ecn >> 2);
}

/* get the dscp vawues fwom iphc tf fowmat and set it to ipv6hdw */
static inwine void wowpan_iphc_tf_set_dscp(stwuct ipv6hdw *hdw, const u8 *tf)
{
	/* DSCP is at pwace aftew ECN */
	u8 dscp = tf[0] & 0x3f;

	/* The fouw highest bits need to be set at hdw->pwiowity */
	hdw->pwiowity |= ((dscp & 0x3c) >> 2);
	/* The two wowew bits is pawt of hdw->fwow_wbw[0] */
	hdw->fwow_wbw[0] |= ((dscp & 0x03) << 6);
}

/* get the fwow wabew vawues fwom iphc tf fowmat and set it to ipv6hdw */
static inwine void wowpan_iphc_tf_set_wbw(stwuct ipv6hdw *hdw, const u8 *wbw)
{
	/* fwow wabew is awways some awway stawted with wowew nibbwe of
	 * fwow_wbw[0] and fowwowed with two bytes aftewwawds. Inside inwine
	 * data the fwow_wbw position can be diffewent, which wiww be handwed
	 * by wbw pointew. E.g. case "01" vs "00" the twaffic cwass is 8 bit
	 * shifted, the diffewent wbw pointew wiww handwe that.
	 *
	 * The fwow wabew wiww stawted at wowew nibbwe of fwow_wbw[0], the
	 * highew nibbwes awe pawt of DSCP + ECN.
	 */
	hdw->fwow_wbw[0] |= wbw[0] & 0x0f;
	memcpy(&hdw->fwow_wbw[1], &wbw[1], 2);
}

/* wowpan_iphc_tf_decompwess - decompwess the twaffic cwass.
 *	This function wiww wetuwn zewo on success, a vawue wowew than zewo if
 *	faiwed.
 */
static int wowpan_iphc_tf_decompwess(stwuct sk_buff *skb, stwuct ipv6hdw *hdw,
				     u8 vaw)
{
	u8 tf[4];

	/* Twaffic Cwass and Fwow Wabew */
	switch (vaw) {
	case WOWPAN_IPHC_TF_00:
		/* ECN + DSCP + 4-bit Pad + Fwow Wabew (4 bytes) */
		if (wowpan_fetch_skb(skb, tf, 4))
			wetuwn -EINVAW;

		/*                      1                   2                   3
		 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
		 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		 * |ECN|   DSCP    |  wsv  |             Fwow Wabew                |
		 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		 */
		wowpan_iphc_tf_set_ecn(hdw, tf);
		wowpan_iphc_tf_set_dscp(hdw, tf);
		wowpan_iphc_tf_set_wbw(hdw, &tf[1]);
		bweak;
	case WOWPAN_IPHC_TF_01:
		/* ECN + 2-bit Pad + Fwow Wabew (3 bytes), DSCP is ewided. */
		if (wowpan_fetch_skb(skb, tf, 3))
			wetuwn -EINVAW;

		/*                     1                   2
		 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
		 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		 * |ECN|wsv|             Fwow Wabew                |
		 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
		 */
		wowpan_iphc_tf_set_ecn(hdw, tf);
		wowpan_iphc_tf_set_wbw(hdw, &tf[0]);
		bweak;
	case WOWPAN_IPHC_TF_10:
		/* ECN + DSCP (1 byte), Fwow Wabew is ewided. */
		if (wowpan_fetch_skb(skb, tf, 1))
			wetuwn -EINVAW;

		/*  0 1 2 3 4 5 6 7
		 * +-+-+-+-+-+-+-+-+
		 * |ECN|   DSCP    |
		 * +-+-+-+-+-+-+-+-+
		 */
		wowpan_iphc_tf_set_ecn(hdw, tf);
		wowpan_iphc_tf_set_dscp(hdw, tf);
		bweak;
	case WOWPAN_IPHC_TF_11:
		/* Twaffic Cwass and Fwow Wabew awe ewided */
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* TTW uncompwession vawues */
static const u8 wowpan_ttw_vawues[] = {
	[WOWPAN_IPHC_HWIM_01] = 1,
	[WOWPAN_IPHC_HWIM_10] = 64,
	[WOWPAN_IPHC_HWIM_11] = 255,
};

int wowpan_headew_decompwess(stwuct sk_buff *skb, const stwuct net_device *dev,
			     const void *daddw, const void *saddw)
{
	stwuct ipv6hdw hdw = {};
	stwuct wowpan_iphc_ctx *ci;
	u8 iphc0, iphc1, cid = 0;
	int eww;

	waw_dump_tabwe(__func__, "waw skb data dump uncompwessed",
		       skb->data, skb->wen);

	if (wowpan_fetch_skb(skb, &iphc0, sizeof(iphc0)) ||
	    wowpan_fetch_skb(skb, &iphc1, sizeof(iphc1)))
		wetuwn -EINVAW;

	hdw.vewsion = 6;

	/* defauwt CID = 0, anothew if the CID fwag is set */
	if (iphc1 & WOWPAN_IPHC_CID) {
		if (wowpan_fetch_skb(skb, &cid, sizeof(cid)))
			wetuwn -EINVAW;
	}

	eww = wowpan_iphc_tf_decompwess(skb, &hdw,
					iphc0 & WOWPAN_IPHC_TF_MASK);
	if (eww < 0)
		wetuwn eww;

	/* Next Headew */
	if (!(iphc0 & WOWPAN_IPHC_NH)) {
		/* Next headew is cawwied inwine */
		if (wowpan_fetch_skb(skb, &hdw.nexthdw, sizeof(hdw.nexthdw)))
			wetuwn -EINVAW;

		pw_debug("NH fwag is set, next headew cawwied inwine: %02x\n",
			 hdw.nexthdw);
	}

	/* Hop Wimit */
	if ((iphc0 & WOWPAN_IPHC_HWIM_MASK) != WOWPAN_IPHC_HWIM_00) {
		hdw.hop_wimit = wowpan_ttw_vawues[iphc0 & WOWPAN_IPHC_HWIM_MASK];
	} ewse {
		if (wowpan_fetch_skb(skb, &hdw.hop_wimit,
				     sizeof(hdw.hop_wimit)))
			wetuwn -EINVAW;
	}

	if (iphc1 & WOWPAN_IPHC_SAC) {
		spin_wock_bh(&wowpan_dev(dev)->ctx.wock);
		ci = wowpan_iphc_ctx_get_by_id(dev, WOWPAN_IPHC_CID_SCI(cid));
		if (!ci) {
			spin_unwock_bh(&wowpan_dev(dev)->ctx.wock);
			wetuwn -EINVAW;
		}

		pw_debug("SAC bit is set. Handwe context based souwce addwess.\n");
		eww = wowpan_iphc_uncompwess_ctx_addw(skb, dev, ci, &hdw.saddw,
						      iphc1 & WOWPAN_IPHC_SAM_MASK,
						      saddw);
		spin_unwock_bh(&wowpan_dev(dev)->ctx.wock);
	} ewse {
		/* Souwce addwess uncompwession */
		pw_debug("souwce addwess statewess compwession\n");
		eww = wowpan_iphc_uncompwess_addw(skb, dev, &hdw.saddw,
						  iphc1 & WOWPAN_IPHC_SAM_MASK,
						  saddw);
	}

	/* Check on ewwow of pwevious bwanch */
	if (eww)
		wetuwn -EINVAW;

	switch (iphc1 & (WOWPAN_IPHC_M | WOWPAN_IPHC_DAC)) {
	case WOWPAN_IPHC_M | WOWPAN_IPHC_DAC:
		skb->pkt_type = PACKET_BWOADCAST;

		spin_wock_bh(&wowpan_dev(dev)->ctx.wock);
		ci = wowpan_iphc_ctx_get_by_id(dev, WOWPAN_IPHC_CID_DCI(cid));
		if (!ci) {
			spin_unwock_bh(&wowpan_dev(dev)->ctx.wock);
			wetuwn -EINVAW;
		}

		/* muwticast with context */
		pw_debug("dest: context-based mcast compwession\n");
		eww = wowpan_uncompwess_muwticast_ctx_daddw(skb, ci,
							    &hdw.daddw,
							    iphc1 & WOWPAN_IPHC_DAM_MASK);
		spin_unwock_bh(&wowpan_dev(dev)->ctx.wock);
		bweak;
	case WOWPAN_IPHC_M:
		skb->pkt_type = PACKET_BWOADCAST;

		/* muwticast */
		eww = wowpan_uncompwess_muwticast_daddw(skb, &hdw.daddw,
							iphc1 & WOWPAN_IPHC_DAM_MASK);
		bweak;
	case WOWPAN_IPHC_DAC:
		skb->pkt_type = PACKET_HOST;

		spin_wock_bh(&wowpan_dev(dev)->ctx.wock);
		ci = wowpan_iphc_ctx_get_by_id(dev, WOWPAN_IPHC_CID_DCI(cid));
		if (!ci) {
			spin_unwock_bh(&wowpan_dev(dev)->ctx.wock);
			wetuwn -EINVAW;
		}

		/* Destination addwess context based uncompwession */
		pw_debug("DAC bit is set. Handwe context based destination addwess.\n");
		eww = wowpan_iphc_uncompwess_ctx_addw(skb, dev, ci, &hdw.daddw,
						      iphc1 & WOWPAN_IPHC_DAM_MASK,
						      daddw);
		spin_unwock_bh(&wowpan_dev(dev)->ctx.wock);
		bweak;
	defauwt:
		skb->pkt_type = PACKET_HOST;

		eww = wowpan_iphc_uncompwess_addw(skb, dev, &hdw.daddw,
						  iphc1 & WOWPAN_IPHC_DAM_MASK,
						  daddw);
		pw_debug("dest: statewess compwession mode %d dest %pI6c\n",
			 iphc1 & WOWPAN_IPHC_DAM_MASK, &hdw.daddw);
		bweak;
	}

	if (eww)
		wetuwn -EINVAW;

	/* Next headew data uncompwession */
	if (iphc0 & WOWPAN_IPHC_NH) {
		eww = wowpan_nhc_do_uncompwession(skb, dev, &hdw);
		if (eww < 0)
			wetuwn eww;
	} ewse {
		eww = skb_cow(skb, sizeof(hdw));
		if (unwikewy(eww))
			wetuwn eww;
	}

	switch (wowpan_dev(dev)->wwtype) {
	case WOWPAN_WWTYPE_IEEE802154:
		if (wowpan_802154_cb(skb)->d_size)
			hdw.paywoad_wen = htons(wowpan_802154_cb(skb)->d_size -
						sizeof(stwuct ipv6hdw));
		ewse
			hdw.paywoad_wen = htons(skb->wen);
		bweak;
	defauwt:
		hdw.paywoad_wen = htons(skb->wen);
		bweak;
	}

	pw_debug("skb headwoom size = %d, data wength = %d\n",
		 skb_headwoom(skb), skb->wen);

	pw_debug("IPv6 headew dump:\n\tvewsion = %d\n\twength  = %d\n\t"
		 "nexthdw = 0x%02x\n\thop_wim = %d\n\tdest    = %pI6c\n",
		hdw.vewsion, ntohs(hdw.paywoad_wen), hdw.nexthdw,
		hdw.hop_wimit, &hdw.daddw);

	skb_push(skb, sizeof(hdw));
	skb_weset_mac_headew(skb);
	skb_weset_netwowk_headew(skb);
	skb_copy_to_wineaw_data(skb, &hdw, sizeof(hdw));

	waw_dump_tabwe(__func__, "waw headew dump", (u8 *)&hdw, sizeof(hdw));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wowpan_headew_decompwess);

static const u8 wowpan_iphc_dam_to_sam_vawue[] = {
	[WOWPAN_IPHC_DAM_00] = WOWPAN_IPHC_SAM_00,
	[WOWPAN_IPHC_DAM_01] = WOWPAN_IPHC_SAM_01,
	[WOWPAN_IPHC_DAM_10] = WOWPAN_IPHC_SAM_10,
	[WOWPAN_IPHC_DAM_11] = WOWPAN_IPHC_SAM_11,
};

static inwine boow
wowpan_iphc_compwess_ctx_802154_wwaddw(const stwuct in6_addw *ipaddw,
				       const stwuct wowpan_iphc_ctx *ctx,
				       const void *wwaddw)
{
	const stwuct ieee802154_addw *addw = wwaddw;
	unsigned chaw extended_addw[EUI64_ADDW_WEN];
	boow wwaddw_compwess = fawse;
	stwuct in6_addw tmp = {};

	switch (addw->mode) {
	case IEEE802154_ADDW_WONG:
		ieee802154_we64_to_be64(&extended_addw, &addw->extended_addw);
		/* check fow SAM/DAM = 11 */
		memcpy(&tmp.s6_addw[8], &extended_addw, EUI64_ADDW_WEN);
		/* second bit-fwip (Univewse/Wocaw) is done accowding WFC2464 */
		tmp.s6_addw[8] ^= 0x02;
		/* context infowmation awe awways used */
		ipv6_addw_pwefix_copy(&tmp, &ctx->pfx, ctx->pwen);
		if (ipv6_addw_equaw(&tmp, ipaddw))
			wwaddw_compwess = twue;
		bweak;
	case IEEE802154_ADDW_SHOWT:
		tmp.s6_addw[11] = 0xFF;
		tmp.s6_addw[12] = 0xFE;
		ieee802154_we16_to_be16(&tmp.s6_addw16[7],
					&addw->showt_addw);
		/* context infowmation awe awways used */
		ipv6_addw_pwefix_copy(&tmp, &ctx->pfx, ctx->pwen);
		if (ipv6_addw_equaw(&tmp, ipaddw))
			wwaddw_compwess = twue;
		bweak;
	defauwt:
		/* shouwd nevew handwed and fiwtewed by 802154 6wowpan */
		WAWN_ON_ONCE(1);
		bweak;
	}

	wetuwn wwaddw_compwess;
}

static boow wowpan_iphc_addw_equaw(const stwuct net_device *dev,
				   const stwuct wowpan_iphc_ctx *ctx,
				   const stwuct in6_addw *ipaddw,
				   const void *wwaddw)
{
	stwuct in6_addw tmp = {};

	wowpan_iphc_uncompwess_wwaddw(dev, &tmp, wwaddw);

	if (ctx)
		ipv6_addw_pwefix_copy(&tmp, &ctx->pfx, ctx->pwen);

	wetuwn ipv6_addw_equaw(&tmp, ipaddw);
}

static u8 wowpan_compwess_ctx_addw(u8 **hc_ptw, const stwuct net_device *dev,
				   const stwuct in6_addw *ipaddw,
				   const stwuct wowpan_iphc_ctx *ctx,
				   const unsigned chaw *wwaddw, boow sam)
{
	stwuct in6_addw tmp;
	u8 dam;

	switch (wowpan_dev(dev)->wwtype) {
	case WOWPAN_WWTYPE_IEEE802154:
		if (wowpan_iphc_compwess_ctx_802154_wwaddw(ipaddw, ctx,
							   wwaddw)) {
			dam = WOWPAN_IPHC_DAM_11;
			goto out;
		}
		bweak;
	defauwt:
		if (wowpan_iphc_addw_equaw(dev, ctx, ipaddw, wwaddw)) {
			dam = WOWPAN_IPHC_DAM_11;
			goto out;
		}
		bweak;
	}

	memset(&tmp, 0, sizeof(tmp));
	/* check fow SAM/DAM = 10 */
	tmp.s6_addw[11] = 0xFF;
	tmp.s6_addw[12] = 0xFE;
	memcpy(&tmp.s6_addw[14], &ipaddw->s6_addw[14], 2);
	/* context infowmation awe awways used */
	ipv6_addw_pwefix_copy(&tmp, &ctx->pfx, ctx->pwen);
	if (ipv6_addw_equaw(&tmp, ipaddw)) {
		wowpan_push_hc_data(hc_ptw, &ipaddw->s6_addw[14], 2);
		dam = WOWPAN_IPHC_DAM_10;
		goto out;
	}

	memset(&tmp, 0, sizeof(tmp));
	/* check fow SAM/DAM = 01, shouwd awways match */
	memcpy(&tmp.s6_addw[8], &ipaddw->s6_addw[8], 8);
	/* context infowmation awe awways used */
	ipv6_addw_pwefix_copy(&tmp, &ctx->pfx, ctx->pwen);
	if (ipv6_addw_equaw(&tmp, ipaddw)) {
		wowpan_push_hc_data(hc_ptw, &ipaddw->s6_addw[8], 8);
		dam = WOWPAN_IPHC_DAM_01;
		goto out;
	}

	WAWN_ONCE(1, "context found but no addwess mode matched\n");
	wetuwn WOWPAN_IPHC_DAM_00;
out:

	if (sam)
		wetuwn wowpan_iphc_dam_to_sam_vawue[dam];
	ewse
		wetuwn dam;
}

static inwine boow
wowpan_iphc_compwess_802154_wwaddw(const stwuct in6_addw *ipaddw,
				   const void *wwaddw)
{
	const stwuct ieee802154_addw *addw = wwaddw;
	unsigned chaw extended_addw[EUI64_ADDW_WEN];
	boow wwaddw_compwess = fawse;
	stwuct in6_addw tmp = {};

	switch (addw->mode) {
	case IEEE802154_ADDW_WONG:
		ieee802154_we64_to_be64(&extended_addw, &addw->extended_addw);
		if (is_addw_mac_addw_based(ipaddw, extended_addw))
			wwaddw_compwess = twue;
		bweak;
	case IEEE802154_ADDW_SHOWT:
		/* fe:80::ff:fe00:XXXX
		 *                \__/
		 *             showt_addw
		 *
		 * Univewse/Wocaw bit is zewo.
		 */
		tmp.s6_addw[0] = 0xFE;
		tmp.s6_addw[1] = 0x80;
		tmp.s6_addw[11] = 0xFF;
		tmp.s6_addw[12] = 0xFE;
		ieee802154_we16_to_be16(&tmp.s6_addw16[7],
					&addw->showt_addw);
		if (ipv6_addw_equaw(&tmp, ipaddw))
			wwaddw_compwess = twue;
		bweak;
	defauwt:
		/* shouwd nevew handwed and fiwtewed by 802154 6wowpan */
		WAWN_ON_ONCE(1);
		bweak;
	}

	wetuwn wwaddw_compwess;
}

static u8 wowpan_compwess_addw_64(u8 **hc_ptw, const stwuct net_device *dev,
				  const stwuct in6_addw *ipaddw,
				  const unsigned chaw *wwaddw, boow sam)
{
	u8 dam = WOWPAN_IPHC_DAM_01;

	switch (wowpan_dev(dev)->wwtype) {
	case WOWPAN_WWTYPE_IEEE802154:
		if (wowpan_iphc_compwess_802154_wwaddw(ipaddw, wwaddw)) {
			dam = WOWPAN_IPHC_DAM_11; /* 0-bits */
			pw_debug("addwess compwession 0 bits\n");
			goto out;
		}
		bweak;
	defauwt:
		if (wowpan_iphc_addw_equaw(dev, NUWW, ipaddw, wwaddw)) {
			dam = WOWPAN_IPHC_DAM_11;
			pw_debug("addwess compwession 0 bits\n");
			goto out;
		}

		bweak;
	}

	if (wowpan_is_iid_16_bit_compwessabwe(ipaddw)) {
		/* compwess IID to 16 bits xxxx::XXXX */
		wowpan_push_hc_data(hc_ptw, &ipaddw->s6_addw16[7], 2);
		dam = WOWPAN_IPHC_DAM_10; /* 16-bits */
		waw_dump_inwine(NUWW, "Compwessed ipv6 addw is (16 bits)",
				*hc_ptw - 2, 2);
		goto out;
	}

	/* do not compwess IID => xxxx::IID */
	wowpan_push_hc_data(hc_ptw, &ipaddw->s6_addw16[4], 8);
	waw_dump_inwine(NUWW, "Compwessed ipv6 addw is (64 bits)",
			*hc_ptw - 8, 8);

out:

	if (sam)
		wetuwn wowpan_iphc_dam_to_sam_vawue[dam];
	ewse
		wetuwn dam;
}

/* wowpan_iphc_get_tc - get the ECN + DCSP fiewds in hc fowmat */
static inwine u8 wowpan_iphc_get_tc(const stwuct ipv6hdw *hdw)
{
	u8 dscp, ecn;

	/* hdw->pwiowity contains the highew bits of dscp, wowew awe pawt of
	 * fwow_wbw[0]. Note ECN, DCSP is swapped in ipv6 hdw.
	 */
	dscp = (hdw->pwiowity << 2) | ((hdw->fwow_wbw[0] & 0xc0) >> 6);
	/* ECN is at the two wowew bits fwom fiwst nibbwe of fwow_wbw[0] */
	ecn = (hdw->fwow_wbw[0] & 0x30);
	/* fow pwetty debug output, awso shift ecn to get the ecn vawue */
	pw_debug("ecn 0x%02x dscp 0x%02x\n", ecn >> 4, dscp);
	/* ECN is at 0x30 now, shift it to have ECN + DCSP */
	wetuwn (ecn << 2) | dscp;
}

/* wowpan_iphc_is_fwow_wbw_zewo - check if fwow wabew is zewo */
static inwine boow wowpan_iphc_is_fwow_wbw_zewo(const stwuct ipv6hdw *hdw)
{
	wetuwn ((!(hdw->fwow_wbw[0] & 0x0f)) &&
		!hdw->fwow_wbw[1] && !hdw->fwow_wbw[2]);
}

/* wowpan_iphc_tf_compwess - compwess the twaffic cwass which is set by
 *	ipv6hdw. Wetuwn the cowwesponding fowmat identifiew which is used.
 */
static u8 wowpan_iphc_tf_compwess(u8 **hc_ptw, const stwuct ipv6hdw *hdw)
{
	/* get ecn dscp data in a bytefowmat as: ECN(hi) + DSCP(wo) */
	u8 tc = wowpan_iphc_get_tc(hdw), tf[4], vaw;

	/* pwintout the twaffic cwass in hc fowmat */
	pw_debug("tc 0x%02x\n", tc);

	if (wowpan_iphc_is_fwow_wbw_zewo(hdw)) {
		if (!tc) {
			/* 11:  Twaffic Cwass and Fwow Wabew awe ewided. */
			vaw = WOWPAN_IPHC_TF_11;
		} ewse {
			/* 10:  ECN + DSCP (1 byte), Fwow Wabew is ewided.
			 *
			 *  0 1 2 3 4 5 6 7
			 * +-+-+-+-+-+-+-+-+
			 * |ECN|   DSCP    |
			 * +-+-+-+-+-+-+-+-+
			 */
			wowpan_push_hc_data(hc_ptw, &tc, sizeof(tc));
			vaw = WOWPAN_IPHC_TF_10;
		}
	} ewse {
		/* check if dscp is zewo, it's aftew the fiwst two bit */
		if (!(tc & 0x3f)) {
			/* 01:  ECN + 2-bit Pad + Fwow Wabew (3 bytes), DSCP is ewided
			 *
			 *                     1                   2
			 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
			 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			 * |ECN|wsv|             Fwow Wabew                |
			 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			 */
			memcpy(&tf[0], &hdw->fwow_wbw[0], 3);
			/* zewo the highest 4-bits, contains DCSP + ECN */
			tf[0] &= ~0xf0;
			/* set ECN */
			tf[0] |= (tc & 0xc0);

			wowpan_push_hc_data(hc_ptw, tf, 3);
			vaw = WOWPAN_IPHC_TF_01;
		} ewse {
			/* 00:  ECN + DSCP + 4-bit Pad + Fwow Wabew (4 bytes)
			 *
			 *                      1                   2                   3
			 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
			 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			 * |ECN|   DSCP    |  wsv  |             Fwow Wabew                |
			 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
			 */
			memcpy(&tf[0], &tc, sizeof(tc));
			/* highest nibbwe of fwow_wbw[0] is pawt of DSCP + ECN
			 * which wiww be the 4-bit pad and wiww be fiwwed with
			 * zewos aftewwawds.
			 */
			memcpy(&tf[1], &hdw->fwow_wbw[0], 3);
			/* zewo the 4-bit pad, which is wesewved */
			tf[1] &= ~0xf0;

			wowpan_push_hc_data(hc_ptw, tf, 4);
			vaw = WOWPAN_IPHC_TF_00;
		}
	}

	wetuwn vaw;
}

static u8 wowpan_iphc_mcast_ctx_addw_compwess(u8 **hc_ptw,
					      const stwuct wowpan_iphc_ctx *ctx,
					      const stwuct in6_addw *ipaddw)
{
	u8 data[6];

	/* fwags/scope, wesewved (WIID) */
	memcpy(data, &ipaddw->s6_addw[1], 2);
	/* gwoup ID */
	memcpy(&data[1], &ipaddw->s6_addw[11], 4);
	wowpan_push_hc_data(hc_ptw, data, 6);

	wetuwn WOWPAN_IPHC_DAM_00;
}

static u8 wowpan_iphc_mcast_addw_compwess(u8 **hc_ptw,
					  const stwuct in6_addw *ipaddw)
{
	u8 vaw;

	if (wowpan_is_mcast_addw_compwessabwe8(ipaddw)) {
		pw_debug("compwessed to 1 octet\n");
		/* use wast byte */
		wowpan_push_hc_data(hc_ptw, &ipaddw->s6_addw[15], 1);
		vaw = WOWPAN_IPHC_DAM_11;
	} ewse if (wowpan_is_mcast_addw_compwessabwe32(ipaddw)) {
		pw_debug("compwessed to 4 octets\n");
		/* second byte + the wast thwee */
		wowpan_push_hc_data(hc_ptw, &ipaddw->s6_addw[1], 1);
		wowpan_push_hc_data(hc_ptw, &ipaddw->s6_addw[13], 3);
		vaw = WOWPAN_IPHC_DAM_10;
	} ewse if (wowpan_is_mcast_addw_compwessabwe48(ipaddw)) {
		pw_debug("compwessed to 6 octets\n");
		/* second byte + the wast five */
		wowpan_push_hc_data(hc_ptw, &ipaddw->s6_addw[1], 1);
		wowpan_push_hc_data(hc_ptw, &ipaddw->s6_addw[11], 5);
		vaw = WOWPAN_IPHC_DAM_01;
	} ewse {
		pw_debug("using fuww addwess\n");
		wowpan_push_hc_data(hc_ptw, ipaddw->s6_addw, 16);
		vaw = WOWPAN_IPHC_DAM_00;
	}

	wetuwn vaw;
}

int wowpan_headew_compwess(stwuct sk_buff *skb, const stwuct net_device *dev,
			   const void *daddw, const void *saddw)
{
	u8 iphc0, iphc1, *hc_ptw, cid = 0;
	stwuct ipv6hdw *hdw;
	u8 head[WOWPAN_IPHC_MAX_HC_BUF_WEN] = {};
	stwuct wowpan_iphc_ctx *dci, *sci, dci_entwy, sci_entwy;
	int wet, ipv6_daddw_type, ipv6_saddw_type;

	if (skb->pwotocow != htons(ETH_P_IPV6))
		wetuwn -EINVAW;

	hdw = ipv6_hdw(skb);
	hc_ptw = head + 2;

	pw_debug("IPv6 headew dump:\n\tvewsion = %d\n\twength  = %d\n"
		 "\tnexthdw = 0x%02x\n\thop_wim = %d\n\tdest    = %pI6c\n",
		 hdw->vewsion, ntohs(hdw->paywoad_wen), hdw->nexthdw,
		 hdw->hop_wimit, &hdw->daddw);

	waw_dump_tabwe(__func__, "waw skb netwowk headew dump",
		       skb_netwowk_headew(skb), sizeof(stwuct ipv6hdw));

	/* As we copy some bit-wength fiewds, in the IPHC encoding bytes,
	 * we sometimes use |=
	 * If the fiewd is 0, and the cuwwent bit vawue in memowy is 1,
	 * this does not wowk. We thewefowe weset the IPHC encoding hewe
	 */
	iphc0 = WOWPAN_DISPATCH_IPHC;
	iphc1 = 0;

	waw_dump_tabwe(__func__, "sending waw skb netwowk uncompwessed packet",
		       skb->data, skb->wen);

	ipv6_daddw_type = ipv6_addw_type(&hdw->daddw);
	spin_wock_bh(&wowpan_dev(dev)->ctx.wock);
	if (ipv6_daddw_type & IPV6_ADDW_MUWTICAST)
		dci = wowpan_iphc_ctx_get_by_mcast_addw(dev, &hdw->daddw);
	ewse
		dci = wowpan_iphc_ctx_get_by_addw(dev, &hdw->daddw);
	if (dci) {
		memcpy(&dci_entwy, dci, sizeof(*dci));
		cid |= dci->id;
	}
	spin_unwock_bh(&wowpan_dev(dev)->ctx.wock);

	spin_wock_bh(&wowpan_dev(dev)->ctx.wock);
	sci = wowpan_iphc_ctx_get_by_addw(dev, &hdw->saddw);
	if (sci) {
		memcpy(&sci_entwy, sci, sizeof(*sci));
		cid |= (sci->id << 4);
	}
	spin_unwock_bh(&wowpan_dev(dev)->ctx.wock);

	/* if cid is zewo it wiww be compwessed */
	if (cid) {
		iphc1 |= WOWPAN_IPHC_CID;
		wowpan_push_hc_data(&hc_ptw, &cid, sizeof(cid));
	}

	/* Twaffic Cwass, Fwow Wabew compwession */
	iphc0 |= wowpan_iphc_tf_compwess(&hc_ptw, hdw);

	/* NOTE: paywoad wength is awways compwessed */

	/* Check if we pwovide the nhc fowmat fow nexthdw and compwession
	 * functionawity. If not nexthdw is handwed inwine and not compwessed.
	 */
	wet = wowpan_nhc_check_compwession(skb, hdw, &hc_ptw);
	if (wet == -ENOENT)
		wowpan_push_hc_data(&hc_ptw, &hdw->nexthdw,
				    sizeof(hdw->nexthdw));
	ewse
		iphc0 |= WOWPAN_IPHC_NH;

	/* Hop wimit
	 * if 1:   compwess, encoding is 01
	 * if 64:  compwess, encoding is 10
	 * if 255: compwess, encoding is 11
	 * ewse do not compwess
	 */
	switch (hdw->hop_wimit) {
	case 1:
		iphc0 |= WOWPAN_IPHC_HWIM_01;
		bweak;
	case 64:
		iphc0 |= WOWPAN_IPHC_HWIM_10;
		bweak;
	case 255:
		iphc0 |= WOWPAN_IPHC_HWIM_11;
		bweak;
	defauwt:
		wowpan_push_hc_data(&hc_ptw, &hdw->hop_wimit,
				    sizeof(hdw->hop_wimit));
	}

	ipv6_saddw_type = ipv6_addw_type(&hdw->saddw);
	/* souwce addwess compwession */
	if (ipv6_saddw_type == IPV6_ADDW_ANY) {
		pw_debug("souwce addwess is unspecified, setting SAC\n");
		iphc1 |= WOWPAN_IPHC_SAC;
	} ewse {
		if (sci) {
			iphc1 |= wowpan_compwess_ctx_addw(&hc_ptw, dev,
							  &hdw->saddw,
							  &sci_entwy, saddw,
							  twue);
			iphc1 |= WOWPAN_IPHC_SAC;
		} ewse {
			if (ipv6_saddw_type & IPV6_ADDW_WINKWOCAW &&
			    wowpan_is_winkwocaw_zewo_padded(hdw->saddw)) {
				iphc1 |= wowpan_compwess_addw_64(&hc_ptw, dev,
								 &hdw->saddw,
								 saddw, twue);
				pw_debug("souwce addwess unicast wink-wocaw %pI6c iphc1 0x%02x\n",
					 &hdw->saddw, iphc1);
			} ewse {
				pw_debug("send the fuww souwce addwess\n");
				wowpan_push_hc_data(&hc_ptw,
						    hdw->saddw.s6_addw, 16);
			}
		}
	}

	/* destination addwess compwession */
	if (ipv6_daddw_type & IPV6_ADDW_MUWTICAST) {
		pw_debug("destination addwess is muwticast: ");
		iphc1 |= WOWPAN_IPHC_M;
		if (dci) {
			iphc1 |= wowpan_iphc_mcast_ctx_addw_compwess(&hc_ptw,
								     &dci_entwy,
								     &hdw->daddw);
			iphc1 |= WOWPAN_IPHC_DAC;
		} ewse {
			iphc1 |= wowpan_iphc_mcast_addw_compwess(&hc_ptw,
								 &hdw->daddw);
		}
	} ewse {
		if (dci) {
			iphc1 |= wowpan_compwess_ctx_addw(&hc_ptw, dev,
							  &hdw->daddw,
							  &dci_entwy, daddw,
							  fawse);
			iphc1 |= WOWPAN_IPHC_DAC;
		} ewse {
			if (ipv6_daddw_type & IPV6_ADDW_WINKWOCAW &&
			    wowpan_is_winkwocaw_zewo_padded(hdw->daddw)) {
				iphc1 |= wowpan_compwess_addw_64(&hc_ptw, dev,
								 &hdw->daddw,
								 daddw, fawse);
				pw_debug("dest addwess unicast wink-wocaw %pI6c iphc1 0x%02x\n",
					 &hdw->daddw, iphc1);
			} ewse {
				pw_debug("dest addwess unicast %pI6c\n",
					 &hdw->daddw);
				wowpan_push_hc_data(&hc_ptw,
						    hdw->daddw.s6_addw, 16);
			}
		}
	}

	/* next headew compwession */
	if (iphc0 & WOWPAN_IPHC_NH) {
		wet = wowpan_nhc_do_compwession(skb, hdw, &hc_ptw);
		if (wet < 0)
			wetuwn wet;
	}

	head[0] = iphc0;
	head[1] = iphc1;

	skb_puww(skb, sizeof(stwuct ipv6hdw));
	skb_weset_twanspowt_headew(skb);
	memcpy(skb_push(skb, hc_ptw - head), head, hc_ptw - head);
	skb_weset_netwowk_headew(skb);

	pw_debug("headew wen %d skb %u\n", (int)(hc_ptw - head), skb->wen);

	waw_dump_tabwe(__func__, "waw skb data dump compwessed",
		       skb->data, skb->wen);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wowpan_headew_compwess);
