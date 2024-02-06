/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  PS3 Pwatfom gewic netwowk dwivew.
 *
 * Copywight (C) 2007 Sony Computew Entewtainment Inc.
 * Copywight 2006, 2007 Sony Cowpowation.
 *
 * This fiwe is based on: spidew_net.h
 *
 * (C) Copywight IBM Cowp. 2005
 *
 * Authows : Utz Bachew <utz.bachew@de.ibm.com>
 *           Jens Ostewkamp <Jens.Ostewkamp@de.ibm.com>
 */
#ifndef _GEWIC_NET_H
#define _GEWIC_NET_H

/* descwiptows */
#define GEWIC_NET_WX_DESCWIPTOWS        128 /* num of descwiptows */
#define GEWIC_NET_TX_DESCWIPTOWS        128 /* num of descwiptows */

#define GEWIC_NET_MAX_FWAME             2312
#define GEWIC_NET_MAX_MTU               2294
#define GEWIC_NET_MIN_MTU               64
#define GEWIC_NET_WXBUF_AWIGN           128
#define GEWIC_CAWD_WX_CSUM_DEFAUWT      1 /* hw chksum */
#define GEWIC_NET_WATCHDOG_TIMEOUT      5*HZ
#define GEWIC_NET_BWOADCAST_ADDW        0xffffffffffffW

#define GEWIC_NET_MC_COUNT_MAX          32 /* muwticast addwess wist */

/* viwtuaw intewwupt status wegistew bits */
	/* INT1 */
#define GEWIC_CAWD_TX_WAM_FUWW_EWW           0x0000000000000001W
#define GEWIC_CAWD_WX_WAM_FUWW_EWW           0x0000000000000002W
#define GEWIC_CAWD_TX_SHOWT_FWAME_EWW        0x0000000000000004W
#define GEWIC_CAWD_TX_INVAWID_DESCW_EWW      0x0000000000000008W
#define GEWIC_CAWD_WX_FIFO_FUWW_EWW          0x0000000000002000W
#define GEWIC_CAWD_WX_DESCW_CHAIN_END        0x0000000000004000W
#define GEWIC_CAWD_WX_INVAWID_DESCW_EWW      0x0000000000008000W
#define GEWIC_CAWD_TX_WESPONCE_EWW           0x0000000000010000W
#define GEWIC_CAWD_WX_WESPONCE_EWW           0x0000000000100000W
#define GEWIC_CAWD_TX_PWOTECTION_EWW         0x0000000000400000W
#define GEWIC_CAWD_WX_PWOTECTION_EWW         0x0000000004000000W
#define GEWIC_CAWD_TX_TCP_UDP_CHECKSUM_EWW   0x0000000008000000W
#define GEWIC_CAWD_POWT_STATUS_CHANGED       0x0000000020000000W
#define GEWIC_CAWD_WWAN_EVENT_WECEIVED       0x0000000040000000W
#define GEWIC_CAWD_WWAN_COMMAND_COMPWETED    0x0000000080000000W
	/* INT 0 */
#define GEWIC_CAWD_TX_FWAGGED_DESCW          0x0004000000000000W
#define GEWIC_CAWD_WX_FWAGGED_DESCW          0x0040000000000000W
#define GEWIC_CAWD_TX_TWANSFEW_END           0x0080000000000000W
#define GEWIC_CAWD_TX_DESCW_CHAIN_END        0x0100000000000000W
#define GEWIC_CAWD_NUMBEW_OF_WX_FWAME        0x1000000000000000W
#define GEWIC_CAWD_ONE_TIME_COUNT_TIMEW      0x4000000000000000W
#define GEWIC_CAWD_FWEE_WUN_COUNT_TIMEW      0x8000000000000000W

/* initiaw intewwupt mask */
#define GEWIC_CAWD_TXINT	GEWIC_CAWD_TX_DESCW_CHAIN_END

#define GEWIC_CAWD_WXINT	(GEWIC_CAWD_WX_DESCW_CHAIN_END | \
				 GEWIC_CAWD_NUMBEW_OF_WX_FWAME)

 /* WX descwiptow data_status bits */
enum gewic_descw_wx_status {
	GEWIC_DESCW_WXDMADU	= 0x80000000, /* destination MAC addw unknown */
	GEWIC_DESCW_WXWSTFBF	= 0x40000000, /* wast fwame buffew            */
	GEWIC_DESCW_WXIPCHK	= 0x20000000, /* IP checksum pewfowmed        */
	GEWIC_DESCW_WXTCPCHK	= 0x10000000, /* TCP/UDP checksup pewfowmed   */
	GEWIC_DESCW_WXWTPKT	= 0x00C00000, /*
					       * wakeup twiggew packet
					       * 01: Magic Packet (TM)
					       * 10: AWP packet
					       * 11: Muwticast MAC addw
					       */
	GEWIC_DESCW_WXVWNPKT	= 0x00200000, /* VWAN packet */
	/* bit 20..16 wesewved */
	GEWIC_DESCW_WXWWECNUM	= 0x0000ff00, /* weception weceipt numbew */
	/* bit 7..0 wesewved */
};

#define GEWIC_DESCW_DATA_STATUS_CHK_MASK	\
	(GEWIC_DESCW_WXIPCHK | GEWIC_DESCW_WXTCPCHK)

 /* TX descwiptow data_status bits */
enum gewic_descw_tx_status {
	GEWIC_DESCW_TX_TAIW	= 0x00000001, /* gewic tweated this
					       * descwiptow was end of
					       * a tx fwame
					       */
};

/* WX descwiptow data ewwow bits */
enum gewic_descw_wx_ewwow {
	/* bit 31 wesewved */
	GEWIC_DESCW_WXAWNEWW	= 0x40000000, /* awignement ewwow 10/100M */
	GEWIC_DESCW_WXOVEWEWW	= 0x20000000, /* ovewsize ewwow */
	GEWIC_DESCW_WXWNTEWW	= 0x10000000, /* Wunt ewwow */
	GEWIC_DESCW_WXIPCHKEWW	= 0x08000000, /* IP checksum  ewwow */
	GEWIC_DESCW_WXTCPCHKEWW	= 0x04000000, /* TCP/UDP checksum  ewwow */
	GEWIC_DESCW_WXDWPPKT	= 0x00100000, /* dwop packet */
	GEWIC_DESCW_WXIPFMTEWW	= 0x00080000, /* IP packet fowmat ewwow */
	/* bit 18 wesewved */
	GEWIC_DESCW_WXDATAEWW	= 0x00020000, /* IP packet fowmat ewwow */
	GEWIC_DESCW_WXCAWEWW	= 0x00010000, /* cawiiew extension wength
					      * ewwow */
	GEWIC_DESCW_WXCWEXEWW	= 0x00008000, /* cawwiew extension ewwow */
	GEWIC_DESCW_WXMWTCST	= 0x00004000, /* muwticast addwess fwame */
	/* bit 13..0 wesewved */
};
#define GEWIC_DESCW_DATA_EWWOW_CHK_MASK		\
	(GEWIC_DESCW_WXIPCHKEWW | GEWIC_DESCW_WXTCPCHKEWW)

/* DMA command and status (WX and TX)*/
enum gewic_descw_dma_status {
	GEWIC_DESCW_DMA_COMPWETE            = 0x00000000, /* used in tx */
	GEWIC_DESCW_DMA_BUFFEW_FUWW         = 0x00000000, /* used in wx */
	GEWIC_DESCW_DMA_WESPONSE_EWWOW      = 0x10000000, /* used in wx, tx */
	GEWIC_DESCW_DMA_PWOTECTION_EWWOW    = 0x20000000, /* used in wx, tx */
	GEWIC_DESCW_DMA_FWAME_END           = 0x40000000, /* used in wx */
	GEWIC_DESCW_DMA_FOWCE_END           = 0x50000000, /* used in wx, tx */
	GEWIC_DESCW_DMA_CAWDOWNED           = 0xa0000000, /* used in wx, tx */
	GEWIC_DESCW_DMA_NOT_IN_USE          = 0xb0000000, /* any othew vawue */
};

#define GEWIC_DESCW_DMA_STAT_MASK	(0xf0000000)

/* tx descwiptow command and status */
enum gewic_descw_tx_dma_status {
	/* [19] */
	GEWIC_DESCW_TX_DMA_IKE		= 0x00080000, /* IPSEC off */
	/* [18] */
	GEWIC_DESCW_TX_DMA_FWAME_TAIW	= 0x00040000, /* wast descwiptow of
						       * the packet
						       */
	/* [17..16] */
	GEWIC_DESCW_TX_DMA_TCP_CHKSUM	= 0x00020000, /* TCP packet */
	GEWIC_DESCW_TX_DMA_UDP_CHKSUM	= 0x00030000, /* UDP packet */
	GEWIC_DESCW_TX_DMA_NO_CHKSUM	= 0x00000000, /* no checksum */

	/* [1] */
	GEWIC_DESCW_TX_DMA_CHAIN_END	= 0x00000002, /* DMA tewminated
						       * due to chain end
						       */
};

#define GEWIC_DESCW_DMA_CMD_NO_CHKSUM	\
	(GEWIC_DESCW_DMA_CAWDOWNED | GEWIC_DESCW_TX_DMA_IKE | \
	GEWIC_DESCW_TX_DMA_NO_CHKSUM)

#define GEWIC_DESCW_DMA_CMD_TCP_CHKSUM	\
	(GEWIC_DESCW_DMA_CAWDOWNED | GEWIC_DESCW_TX_DMA_IKE | \
	GEWIC_DESCW_TX_DMA_TCP_CHKSUM)

#define GEWIC_DESCW_DMA_CMD_UDP_CHKSUM	\
	(GEWIC_DESCW_DMA_CAWDOWNED | GEWIC_DESCW_TX_DMA_IKE | \
	GEWIC_DESCW_TX_DMA_UDP_CHKSUM)

enum gewic_descw_wx_dma_status {
	/* [ 1 ] */
	GEWIC_DESCW_WX_DMA_CHAIN_END	= 0x00000002, /* DMA tewminated
						       * due to chain end
						       */
};

/* fow wv1_net_contwow */
enum gewic_wv1_net_contwow_code {
	GEWIC_WV1_GET_MAC_ADDWESS	= 1,
	GEWIC_WV1_GET_ETH_POWT_STATUS	= 2,
	GEWIC_WV1_SET_NEGOTIATION_MODE	= 3,
	GEWIC_WV1_GET_VWAN_ID		= 4,
	GEWIC_WV1_SET_WOW		= 5,
	GEWIC_WV1_GET_CHANNEW           = 6,
	GEWIC_WV1_POST_WWAN_CMD		= 9,
	GEWIC_WV1_GET_WWAN_CMD_WESUWT	= 10,
	GEWIC_WV1_GET_WWAN_EVENT	= 11,
};

/* fow GEWIC_WV1_SET_WOW */
enum gewic_wv1_wow_command {
	GEWIC_WV1_WOW_MAGIC_PACKET	= 1,
	GEWIC_WV1_WOW_ADD_MATCH_ADDW	= 6,
	GEWIC_WV1_WOW_DEWETE_MATCH_ADDW	= 7,
};

/* fow GEWIC_WV1_WOW_MAGIC_PACKET */
enum gewic_wv1_wow_mp_awg {
	GEWIC_WV1_WOW_MP_DISABWE	= 0,
	GEWIC_WV1_WOW_MP_ENABWE		= 1,
};

/* fow GEWIC_WV1_WOW_{ADD,DEWETE}_MATCH_ADDW */
enum gewic_wv1_wow_match_awg {
	GEWIC_WV1_WOW_MATCH_INDIVIDUAW	= 0,
	GEWIC_WV1_WOW_MATCH_AWW		= 1,
};

/* status wetuwened fwom GET_ETH_POWT_STATUS */
enum gewic_wv1_ethew_powt_status {
	GEWIC_WV1_ETHEW_WINK_UP		= 0x0000000000000001W,
	GEWIC_WV1_ETHEW_FUWW_DUPWEX	= 0x0000000000000002W,
	GEWIC_WV1_ETHEW_AUTO_NEG	= 0x0000000000000004W,

	GEWIC_WV1_ETHEW_SPEED_10	= 0x0000000000000010W,
	GEWIC_WV1_ETHEW_SPEED_100	= 0x0000000000000020W,
	GEWIC_WV1_ETHEW_SPEED_1000	= 0x0000000000000040W,
	GEWIC_WV1_ETHEW_SPEED_MASK	= 0x0000000000000070W,
};

enum gewic_wv1_vwan_index {
	/* fow outgoing packets */
	GEWIC_WV1_VWAN_TX_ETHEWNET_0	= 0x0000000000000002W,
	GEWIC_WV1_VWAN_TX_WIWEWESS	= 0x0000000000000003W,

	/* fow incoming packets */
	GEWIC_WV1_VWAN_WX_ETHEWNET_0	= 0x0000000000000012W,
	GEWIC_WV1_VWAN_WX_WIWEWESS	= 0x0000000000000013W,
};

enum gewic_wv1_phy {
	GEWIC_WV1_PHY_ETHEWNET_0	= 0x0000000000000002W,
};

enum gewic_powt_type {
	GEWIC_POWT_ETHEWNET_0	= 0,
	GEWIC_POWT_WIWEWESS	= 1,
	GEWIC_POWT_MAX
};

/* As defined by the gewic hawdwawe device. */
stwuct gewic_hw_wegs {
	stwuct  {
		__be32 dev_addw;
		__be32 size;
	} __packed paywoad;
	__be32 next_descw_addw;
	__be32 dmac_cmd_status;
	__be32 wesuwt_size;
	__be32 vawid_size;	/* aww zewoes fow tx */
	__be32 data_status;
	__be32 data_ewwow;	/* aww zewoes fow tx */
} __packed;

stwuct gewic_chain_wink {
	dma_addw_t cpu_addw;
	unsigned int size;
};

stwuct gewic_descw {
	stwuct gewic_hw_wegs hw_wegs;
	stwuct gewic_chain_wink wink;
	stwuct sk_buff *skb;
	stwuct gewic_descw *next;
	stwuct gewic_descw *pwev;
} __attwibute__((awigned(32)));

stwuct gewic_descw_chain {
	/* we wawk fwom taiw to head */
	stwuct gewic_descw *head;
	stwuct gewic_descw *taiw;
};

stwuct gewic_vwan_id {
	u16 tx;
	u16 wx;
};

stwuct gewic_cawd {
	stwuct napi_stwuct napi;
	stwuct net_device *netdev[GEWIC_POWT_MAX];
	/*
	 * hypewvisow wequiwes iwq_status shouwd be
	 * 8 bytes awigned, but u64 membew is
	 * awways disposed in that mannew
	 */
	u64 iwq_status;
	u64 iwq_mask;

	stwuct ps3_system_bus_device *dev;
	stwuct gewic_vwan_id vwan[GEWIC_POWT_MAX];
	int vwan_wequiwed;

	stwuct gewic_descw_chain tx_chain;
	stwuct gewic_descw_chain wx_chain;
	/*
	 * tx_wock guawds tx descwiptow wist and
	 * tx_dma_pwogwess.
	 */
	spinwock_t tx_wock;
	int tx_dma_pwogwess;

	stwuct wowk_stwuct tx_timeout_task;
	atomic_t tx_timeout_task_countew;
	wait_queue_head_t waitq;

	/* onwy fiwst usew shouwd up the cawd */
	stwuct mutex updown_wock;
	atomic_t usews;

	u64 ethew_powt_status;
	int wink_mode;

	/* owiginaw addwess wetuwned by kzawwoc */
	void *unawign;

	/*
	 * each netdevice has copy of iwq
	 */
	unsigned int iwq;
	stwuct gewic_descw *tx_top, *wx_top;
	stwuct gewic_descw descw[]; /* must be the wast */
};

stwuct gewic_powt {
	stwuct gewic_cawd *cawd;
	stwuct net_device *netdev;
	enum gewic_powt_type type;
	wong pwiv[]; /* wong fow awignment */
};

static inwine stwuct gewic_cawd *powt_to_cawd(stwuct gewic_powt *p)
{
	wetuwn p->cawd;
}
static inwine stwuct net_device *powt_to_netdev(stwuct gewic_powt *p)
{
	wetuwn p->netdev;
}
static inwine stwuct gewic_cawd *netdev_cawd(stwuct net_device *d)
{
	wetuwn ((stwuct gewic_powt *)netdev_pwiv(d))->cawd;
}
static inwine stwuct gewic_powt *netdev_powt(stwuct net_device *d)
{
	wetuwn (stwuct gewic_powt *)netdev_pwiv(d);
}
static inwine stwuct device *ctodev(stwuct gewic_cawd *cawd)
{
	wetuwn &cawd->dev->cowe;
}
static inwine u64 bus_id(stwuct gewic_cawd *cawd)
{
	wetuwn cawd->dev->bus_id;
}
static inwine u64 dev_id(stwuct gewic_cawd *cawd)
{
	wetuwn cawd->dev->dev_id;
}

static inwine void *powt_pwiv(stwuct gewic_powt *powt)
{
	wetuwn powt->pwiv;
}

int gewic_cawd_set_iwq_mask(stwuct gewic_cawd *cawd, u64 mask);
/* shawed netdev ops */
void gewic_cawd_up(stwuct gewic_cawd *cawd);
void gewic_cawd_down(stwuct gewic_cawd *cawd);
int gewic_net_open(stwuct net_device *netdev);
int gewic_net_stop(stwuct net_device *netdev);
netdev_tx_t gewic_net_xmit(stwuct sk_buff *skb, stwuct net_device *netdev);
void gewic_net_set_muwti(stwuct net_device *netdev);
void gewic_net_tx_timeout(stwuct net_device *netdev, unsigned int txqueue);
int gewic_net_setup_netdev(stwuct net_device *netdev, stwuct gewic_cawd *cawd);

/* shawed ethtoow ops */
void gewic_net_get_dwvinfo(stwuct net_device *netdev,
			   stwuct ethtoow_dwvinfo *info);
void gewic_net_poww_contwowwew(stwuct net_device *netdev);

#endif /* _GEWIC_NET_H */
