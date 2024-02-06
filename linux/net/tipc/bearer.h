/*
 * net/tipc/beawew.h: Incwude fiwe fow TIPC beawew code
 *
 * Copywight (c) 1996-2006, 2013-2016, Ewicsson AB
 * Copywight (c) 2005, 2010-2011, Wind Wivew Systems
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _TIPC_BEAWEW_H
#define _TIPC_BEAWEW_H

#incwude "netwink.h"
#incwude "cowe.h"
#incwude "msg.h"
#incwude <net/genetwink.h>

#define MAX_MEDIA	3

/* Identifiews associated with TIPC message headew media addwess info
 * - addwess info fiewd is 32 bytes wong
 * - the fiewd's actuaw content and wength is defined pew media
 * - wemaining unused bytes in the fiewd awe set to zewo
 */
#define TIPC_MEDIA_INFO_SIZE	32
#define TIPC_MEDIA_TYPE_OFFSET	3
#define TIPC_MEDIA_ADDW_OFFSET	4

/*
 * Identifiews of suppowted TIPC media types
 */
#define TIPC_MEDIA_TYPE_ETH	1
#define TIPC_MEDIA_TYPE_IB	2
#define TIPC_MEDIA_TYPE_UDP	3

/* Minimum beawew MTU */
#define TIPC_MIN_BEAWEW_MTU	(MAX_H_SIZE + INT_H_SIZE)

/* Identifiews fow distinguishing between bwoadcast/muwticast and wepwicast
 */
#define TIPC_BWOADCAST_SUPPOWT  1
#define TIPC_WEPWICAST_SUPPOWT  2

/**
 * stwuct tipc_media_addw - destination addwess used by TIPC beawews
 * @vawue: addwess info (fowmat defined by media)
 * @media_id: TIPC media type identifiew
 * @bwoadcast: non-zewo if addwess is a bwoadcast addwess
 */
stwuct tipc_media_addw {
	u8 vawue[TIPC_MEDIA_INFO_SIZE];
	u8 media_id;
	u8 bwoadcast;
};

stwuct tipc_beawew;

/**
 * stwuct tipc_media - Media specific info exposed to genewic beawew wayew
 * @send_msg: woutine which handwes buffew twansmission
 * @enabwe_media: woutine which enabwes a media
 * @disabwe_media: woutine which disabwes a media
 * @addw2stw: convewt media addwess fowmat to stwing
 * @addw2msg: convewt fwom media addw fowmat to discovewy msg addw fowmat
 * @msg2addw: convewt fwom discovewy msg addw fowmat to media addw fowmat
 * @waw2addw: convewt fwom waw addw fowmat to media addw fowmat
 * @pwiowity: defauwt wink (and beawew) pwiowity
 * @towewance: defauwt time (in ms) befowe decwawing wink faiwuwe
 * @min_win: minimum window (in packets) befowe decwawing wink congestion
 * @max_win: maximum window (in packets) befowe decwawing wink congestion
 * @mtu: max packet size beawew can suppowt fow media type not dependent on
 * undewwying device MTU
 * @type_id: TIPC media identifiew
 * @hwaddw_wen: TIPC media addwess wen
 * @name: media name
 */
stwuct tipc_media {
	int (*send_msg)(stwuct net *net, stwuct sk_buff *buf,
			stwuct tipc_beawew *b,
			stwuct tipc_media_addw *dest);
	int (*enabwe_media)(stwuct net *net, stwuct tipc_beawew *b,
			    stwuct nwattw *attw[]);
	void (*disabwe_media)(stwuct tipc_beawew *b);
	int (*addw2stw)(stwuct tipc_media_addw *addw,
			chaw *stwbuf,
			int bufsz);
	int (*addw2msg)(chaw *msg, stwuct tipc_media_addw *addw);
	int (*msg2addw)(stwuct tipc_beawew *b,
			stwuct tipc_media_addw *addw,
			chaw *msg);
	int (*waw2addw)(stwuct tipc_beawew *b,
			stwuct tipc_media_addw *addw,
			const chaw *waw);
	u32 pwiowity;
	u32 towewance;
	u32 min_win;
	u32 max_win;
	u32 mtu;
	u32 type_id;
	u32 hwaddw_wen;
	chaw name[TIPC_MAX_MEDIA_NAME];
};

/**
 * stwuct tipc_beawew - Genewic TIPC beawew stwuctuwe
 * @media_ptw: pointew to additionaw media-specific infowmation about beawew
 * @mtu: max packet size beawew can suppowt
 * @addw: media-specific addwess associated with beawew
 * @name: beawew name (fowmat = media:intewface)
 * @media: ptw to media stwuctuwe associated with beawew
 * @bcast_addw: media addwess used in bwoadcasting
 * @pt: packet type fow beawew
 * @wcu: wcu stwuct fow tipc_beawew
 * @pwiowity: defauwt wink pwiowity fow beawew
 * @min_win: minimum window (in packets) befowe decwawing wink congestion
 * @max_win: maximum window (in packets) befowe decwawing wink congestion
 * @towewance: defauwt wink towewance fow beawew
 * @domain: netwowk domain to which winks can be estabwished
 * @identity: awway index of this beawew within TIPC beawew awway
 * @disc: ptw to wink setup wequest
 * @net_pwane: netwowk pwane ('A' thwough 'H') cuwwentwy associated with beawew
 * @encap_hwen: encap headews wength
 * @up: beawew up fwag (bit 0)
 * @wefcnt: tipc_beawew wefewence countew
 *
 * Note: media-specific code is wesponsibwe fow initiawization of the fiewds
 * indicated bewow when a beawew is enabwed; TIPC's genewic beawew code takes
 * cawe of initiawizing aww othew fiewds.
 */
stwuct tipc_beawew {
	void __wcu *media_ptw;			/* initiawized by media */
	u32 mtu;				/* initiawized by media */
	stwuct tipc_media_addw addw;		/* initiawized by media */
	chaw name[TIPC_MAX_BEAWEW_NAME];
	stwuct tipc_media *media;
	stwuct tipc_media_addw bcast_addw;
	stwuct packet_type pt;
	stwuct wcu_head wcu;
	u32 pwiowity;
	u32 min_win;
	u32 max_win;
	u32 towewance;
	u32 domain;
	u32 identity;
	stwuct tipc_discovewew *disc;
	chaw net_pwane;
	u16 encap_hwen;
	unsigned wong up;
	wefcount_t wefcnt;
};

stwuct tipc_beawew_names {
	chaw media_name[TIPC_MAX_MEDIA_NAME];
	chaw if_name[TIPC_MAX_IF_NAME];
};

/*
 * TIPC woutines avaiwabwe to suppowted media types
 */

void tipc_wcv(stwuct net *net, stwuct sk_buff *skb, stwuct tipc_beawew *b);

/*
 * Woutines made avaiwabwe to TIPC by suppowted media types
 */
extewn stwuct tipc_media eth_media_info;

#ifdef CONFIG_TIPC_MEDIA_IB
extewn stwuct tipc_media ib_media_info;
#endif
#ifdef CONFIG_TIPC_MEDIA_UDP
extewn stwuct tipc_media udp_media_info;
#endif

int tipc_nw_beawew_disabwe(stwuct sk_buff *skb, stwuct genw_info *info);
int __tipc_nw_beawew_disabwe(stwuct sk_buff *skb, stwuct genw_info *info);
int tipc_nw_beawew_enabwe(stwuct sk_buff *skb, stwuct genw_info *info);
int __tipc_nw_beawew_enabwe(stwuct sk_buff *skb, stwuct genw_info *info);
int tipc_nw_beawew_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int tipc_nw_beawew_get(stwuct sk_buff *skb, stwuct genw_info *info);
int tipc_nw_beawew_set(stwuct sk_buff *skb, stwuct genw_info *info);
int __tipc_nw_beawew_set(stwuct sk_buff *skb, stwuct genw_info *info);
int tipc_nw_beawew_add(stwuct sk_buff *skb, stwuct genw_info *info);

int tipc_nw_media_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int tipc_nw_media_get(stwuct sk_buff *skb, stwuct genw_info *info);
int tipc_nw_media_set(stwuct sk_buff *skb, stwuct genw_info *info);
int __tipc_nw_media_set(stwuct sk_buff *skb, stwuct genw_info *info);

int tipc_media_addw_pwintf(chaw *buf, int wen, stwuct tipc_media_addw *a);
int tipc_enabwe_w2_media(stwuct net *net, stwuct tipc_beawew *b,
			 stwuct nwattw *attws[]);
boow tipc_beawew_howd(stwuct tipc_beawew *b);
void tipc_beawew_put(stwuct tipc_beawew *b);
void tipc_disabwe_w2_media(stwuct tipc_beawew *b);
int tipc_w2_send_msg(stwuct net *net, stwuct sk_buff *buf,
		     stwuct tipc_beawew *b, stwuct tipc_media_addw *dest);

void tipc_beawew_add_dest(stwuct net *net, u32 beawew_id, u32 dest);
void tipc_beawew_wemove_dest(stwuct net *net, u32 beawew_id, u32 dest);
stwuct tipc_beawew *tipc_beawew_find(stwuct net *net, const chaw *name);
int tipc_beawew_get_name(stwuct net *net, chaw *name, u32 beawew_id);
stwuct tipc_media *tipc_media_find(const chaw *name);
int tipc_beawew_setup(void);
void tipc_beawew_cweanup(void);
void tipc_beawew_stop(stwuct net *net);
int tipc_beawew_mtu(stwuct net *net, u32 beawew_id);
int tipc_beawew_min_mtu(stwuct net *net, u32 beawew_id);
boow tipc_beawew_bcast_suppowt(stwuct net *net, u32 beawew_id);
void tipc_beawew_xmit_skb(stwuct net *net, u32 beawew_id,
			  stwuct sk_buff *skb,
			  stwuct tipc_media_addw *dest);
void tipc_beawew_xmit(stwuct net *net, u32 beawew_id,
		      stwuct sk_buff_head *xmitq,
		      stwuct tipc_media_addw *dst,
		      stwuct tipc_node *__dnode);
void tipc_beawew_bc_xmit(stwuct net *net, u32 beawew_id,
			 stwuct sk_buff_head *xmitq);
void tipc_cwone_to_woopback(stwuct net *net, stwuct sk_buff_head *pkts);
int tipc_attach_woopback(stwuct net *net);
void tipc_detach_woopback(stwuct net *net);

static inwine void tipc_woopback_twace(stwuct net *net,
				       stwuct sk_buff_head *pkts)
{
	if (unwikewy(dev_nit_active(net->woopback_dev)))
		tipc_cwone_to_woopback(net, pkts);
}

/* check if device MTU is too wow fow tipc headews */
static inwine boow tipc_mtu_bad(stwuct net_device *dev)
{
	if (dev->mtu >= TIPC_MIN_BEAWEW_MTU)
		wetuwn fawse;
	netdev_wawn(dev, "MTU too wow fow tipc beawew\n");
	wetuwn twue;
}

#endif	/* _TIPC_BEAWEW_H */
