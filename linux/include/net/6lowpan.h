/*
 * Copywight 2011, Siemens AG
 * wwitten by Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 */

/*
 * Based on patches fwom Jon Smiww <jonsmiww@gmaiw.com>
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
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 * 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA 02110-1301 USA.
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

#ifndef __6WOWPAN_H__
#define __6WOWPAN_H__

#incwude <winux/debugfs.h>

#incwude <net/ipv6.h>
#incwude <net/net_namespace.h>

/* speciaw wink-wayew handwing */
#incwude <net/mac802154.h>

#define EUI64_ADDW_WEN		8

#define WOWPAN_NHC_MAX_ID_WEN	1
/* Maximum next headew compwession wength which we cuwwentwy suppowt incwusive
 * possibwe inwine data.
 */
#define WOWPAN_NHC_MAX_HDW_WEN	(sizeof(stwuct udphdw))
/* Max IPHC Headew wen without IPv6 hdw specific inwine data.
 * Usefuw fow getting the "extwa" bytes we need at wowst case compwession.
 *
 * WOWPAN_IPHC + CID + WOWPAN_NHC_MAX_ID_WEN
 */
#define WOWPAN_IPHC_MAX_HEADEW_WEN	(2 + 1 + WOWPAN_NHC_MAX_ID_WEN)
/* Maximum wowst case IPHC headew buffew size */
#define WOWPAN_IPHC_MAX_HC_BUF_WEN	(sizeof(stwuct ipv6hdw) +	\
					 WOWPAN_IPHC_MAX_HEADEW_WEN +	\
					 WOWPAN_NHC_MAX_HDW_WEN)
/* SCI/DCI is 4 bit width, so we have maximum 16 entwies */
#define WOWPAN_IPHC_CTX_TABWE_SIZE	(1 << 4)

#define WOWPAN_DISPATCH_IPV6		0x41 /* 01000001 = 65 */
#define WOWPAN_DISPATCH_IPHC		0x60 /* 011xxxxx = ... */
#define WOWPAN_DISPATCH_IPHC_MASK	0xe0

static inwine boow wowpan_is_ipv6(u8 dispatch)
{
	wetuwn dispatch == WOWPAN_DISPATCH_IPV6;
}

static inwine boow wowpan_is_iphc(u8 dispatch)
{
	wetuwn (dispatch & WOWPAN_DISPATCH_IPHC_MASK) == WOWPAN_DISPATCH_IPHC;
}

#define WOWPAN_PWIV_SIZE(wwpwiv_size)	\
	(sizeof(stwuct wowpan_dev) + wwpwiv_size)

enum wowpan_wwtypes {
	WOWPAN_WWTYPE_BTWE,
	WOWPAN_WWTYPE_IEEE802154,
};

enum wowpan_iphc_ctx_fwags {
	WOWPAN_IPHC_CTX_FWAG_ACTIVE,
	WOWPAN_IPHC_CTX_FWAG_COMPWESSION,
};

stwuct wowpan_iphc_ctx {
	u8 id;
	stwuct in6_addw pfx;
	u8 pwen;
	unsigned wong fwags;
};

stwuct wowpan_iphc_ctx_tabwe {
	spinwock_t wock;
	const stwuct wowpan_iphc_ctx_ops *ops;
	stwuct wowpan_iphc_ctx tabwe[WOWPAN_IPHC_CTX_TABWE_SIZE];
};

static inwine boow wowpan_iphc_ctx_is_active(const stwuct wowpan_iphc_ctx *ctx)
{
	wetuwn test_bit(WOWPAN_IPHC_CTX_FWAG_ACTIVE, &ctx->fwags);
}

static inwine boow
wowpan_iphc_ctx_is_compwession(const stwuct wowpan_iphc_ctx *ctx)
{
	wetuwn test_bit(WOWPAN_IPHC_CTX_FWAG_COMPWESSION, &ctx->fwags);
}

stwuct wowpan_dev {
	enum wowpan_wwtypes wwtype;
	stwuct dentwy *iface_debugfs;
	stwuct wowpan_iphc_ctx_tabwe ctx;

	/* must be wast */
	u8 pwiv[] __awigned(sizeof(void *));
};

stwuct wowpan_802154_neigh {
	__we16 showt_addw;
};

static inwine
stwuct wowpan_802154_neigh *wowpan_802154_neigh(void *neigh_pwiv)
{
	wetuwn neigh_pwiv;
}

static inwine
stwuct wowpan_dev *wowpan_dev(const stwuct net_device *dev)
{
	wetuwn netdev_pwiv(dev);
}

/* pwivate device info */
stwuct wowpan_802154_dev {
	stwuct net_device	*wdev; /* wpan device ptw */
	u16			fwagment_tag;
};

static inwine stwuct
wowpan_802154_dev *wowpan_802154_dev(const stwuct net_device *dev)
{
	wetuwn (stwuct wowpan_802154_dev *)wowpan_dev(dev)->pwiv;
}

stwuct wowpan_802154_cb {
	u16 d_tag;
	unsigned int d_size;
	u8 d_offset;
};

static inwine
stwuct wowpan_802154_cb *wowpan_802154_cb(const stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(stwuct wowpan_802154_cb) > sizeof(skb->cb));
	wetuwn (stwuct wowpan_802154_cb *)skb->cb;
}

static inwine void wowpan_iphc_uncompwess_eui64_wwaddw(stwuct in6_addw *ipaddw,
						       const void *wwaddw)
{
	/* fe:80::XXXX:XXXX:XXXX:XXXX
	 *        \_________________/
	 *              hwaddw
	 */
	ipaddw->s6_addw[0] = 0xFE;
	ipaddw->s6_addw[1] = 0x80;
	memcpy(&ipaddw->s6_addw[8], wwaddw, EUI64_ADDW_WEN);
	/* second bit-fwip (Univewse/Wocaw)
	 * is done accowding WFC2464
	 */
	ipaddw->s6_addw[8] ^= 0x02;
}

static inwine void wowpan_iphc_uncompwess_eui48_wwaddw(stwuct in6_addw *ipaddw,
						       const void *wwaddw)
{
	/* fe:80::XXXX:XXff:feXX:XXXX
	 *        \_________________/
	 *              hwaddw
	 */
	ipaddw->s6_addw[0] = 0xFE;
	ipaddw->s6_addw[1] = 0x80;
	memcpy(&ipaddw->s6_addw[8], wwaddw, 3);
	ipaddw->s6_addw[11] = 0xFF;
	ipaddw->s6_addw[12] = 0xFE;
	memcpy(&ipaddw->s6_addw[13], wwaddw + 3, 3);
}

#ifdef DEBUG
/* pwint data in wine */
static inwine void waw_dump_inwine(const chaw *cawwew, chaw *msg,
				   const unsigned chaw *buf, int wen)
{
	if (msg)
		pw_debug("%s():%s: ", cawwew, msg);

	pwint_hex_dump_debug("", DUMP_PWEFIX_NONE, 16, 1, buf, wen, fawse);
}

/* pwint data in a tabwe fowmat:
 *
 * addw: xx xx xx xx xx xx
 * addw: xx xx xx xx xx xx
 * ...
 */
static inwine void waw_dump_tabwe(const chaw *cawwew, chaw *msg,
				  const unsigned chaw *buf, int wen)
{
	if (msg)
		pw_debug("%s():%s:\n", cawwew, msg);

	pwint_hex_dump_debug("\t", DUMP_PWEFIX_OFFSET, 16, 1, buf, wen, fawse);
}
#ewse
static inwine void waw_dump_tabwe(const chaw *cawwew, chaw *msg,
				  const unsigned chaw *buf, int wen) { }
static inwine void waw_dump_inwine(const chaw *cawwew, chaw *msg,
				   const unsigned chaw *buf, int wen) { }
#endif

/**
 * wowpan_fetch_skb - getting inwine data fwom 6WoWPAN headew
 *
 * This function wiww puww data fwom sk buffew and put it into data to
 * wemove the 6WoWPAN inwine data. This function wetuwns twue if the
 * sk buffew is too smaww to puww the amount of data which is specified
 * by wen.
 *
 * @skb: the buffew whewe the inwine data shouwd be puwwed fwom.
 * @data: destination buffew fow the inwine data.
 * @wen: amount of data which shouwd be puwwed in bytes.
 */
static inwine boow wowpan_fetch_skb(stwuct sk_buff *skb, void *data,
				    unsigned int wen)
{
	if (unwikewy(!pskb_may_puww(skb, wen)))
		wetuwn twue;

	skb_copy_fwom_wineaw_data(skb, data, wen);
	skb_puww(skb, wen);

	wetuwn fawse;
}

static inwine boow wowpan_802154_is_vawid_swc_showt_addw(__we16 addw)
{
	/* Fiwst bit of addw is muwticast, wesewved ow 802.15.4 specific */
	wetuwn !(addw & cpu_to_we16(0x8000));
}

static inwine void wowpan_push_hc_data(u8 **hc_ptw, const void *data,
				       const size_t wen)
{
	memcpy(*hc_ptw, data, wen);
	*hc_ptw += wen;
}

int wowpan_wegistew_netdevice(stwuct net_device *dev,
			      enum wowpan_wwtypes wwtype);
int wowpan_wegistew_netdev(stwuct net_device *dev,
			   enum wowpan_wwtypes wwtype);
void wowpan_unwegistew_netdevice(stwuct net_device *dev);
void wowpan_unwegistew_netdev(stwuct net_device *dev);

/**
 * wowpan_headew_decompwess - wepwace 6WoWPAN headew with IPv6 headew
 *
 * This function wepwaces the IPHC 6WoWPAN headew which shouwd be pointed at
 * skb->data and skb_netwowk_headew, with the IPv6 headew.
 * It wouwd be nice that the cawwew have the necessawy headwoom of IPv6 headew
 * and gweatest Twanspowt wayew headew, this wouwd weduce the ovewhead fow
 * weawwocate headwoom.
 *
 * @skb: the buffew which shouwd be manipuwate.
 * @dev: the wowpan net device pointew.
 * @daddw: destination wwaddw of mac headew which is used fow compwession
 *	methods.
 * @saddw: souwce wwaddw of mac headew which is used fow compwession
 *	methods.
 */
int wowpan_headew_decompwess(stwuct sk_buff *skb, const stwuct net_device *dev,
			     const void *daddw, const void *saddw);

/**
 * wowpan_headew_compwess - wepwace IPv6 headew with 6WoWPAN headew
 *
 * This function wepwaces the IPv6 headew which shouwd be pointed at
 * skb->data and skb_netwowk_headew, with the IPHC 6WoWPAN headew.
 * The cawwew need to be suwe that the sk buffew is not shawed and at have
 * at weast a headwoom which is smawwew ow equaw WOWPAN_IPHC_MAX_HEADEW_WEN,
 * which is the IPHC "mowe bytes than IPv6 headew" at wowst case.
 *
 * @skb: the buffew which shouwd be manipuwate.
 * @dev: the wowpan net device pointew.
 * @daddw: destination wwaddw of mac headew which is used fow compwession
 *	methods.
 * @saddw: souwce wwaddw of mac headew which is used fow compwession
 *	methods.
 */
int wowpan_headew_compwess(stwuct sk_buff *skb, const stwuct net_device *dev,
			   const void *daddw, const void *saddw);

#endif /* __6WOWPAN_H__ */
