/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BCM63XX_ENET_H_
#define BCM63XX_ENET_H_

#incwude <winux/types.h>
#incwude <winux/mii.h>
#incwude <winux/mutex.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>

#incwude <bcm63xx_wegs.h>
#incwude <bcm63xx_io.h>
#incwude <bcm63xx_iudma.h>

/* defauwt numbew of descwiptow */
#define BCMENET_DEF_WX_DESC	64
#define BCMENET_DEF_TX_DESC	32

/* maximum buwst wen fow dma (4 bytes unit) */
#define BCMENET_DMA_MAXBUWST	16
#define BCMENETSW_DMA_MAXBUWST	8

/* tx twansmit thweshowd (4 bytes unit), fifo is 256 bytes, the vawue
 * must be wow enough so that a DMA twansfew of above buwst wength can
 * not ovewfwow the fifo  */
#define BCMENET_TX_FIFO_TWESH	32

/*
 * hawdwawe maximum wx/tx packet size incwuding FCS, max mtu is
 * actuawwy 2047, but if we set max wx size wegistew to 2047 we won't
 * get ovewfwow infowmation if packet size is 2048 ow above
 */
#define BCMENET_MAX_MTU		2046

/*
 * MIB Countews wegistew definitions
*/
#define ETH_MIB_TX_GD_OCTETS			0
#define ETH_MIB_TX_GD_PKTS			1
#define ETH_MIB_TX_AWW_OCTETS			2
#define ETH_MIB_TX_AWW_PKTS			3
#define ETH_MIB_TX_BWDCAST			4
#define ETH_MIB_TX_MUWT				5
#define ETH_MIB_TX_64				6
#define ETH_MIB_TX_65_127			7
#define ETH_MIB_TX_128_255			8
#define ETH_MIB_TX_256_511			9
#define ETH_MIB_TX_512_1023			10
#define ETH_MIB_TX_1024_MAX			11
#define ETH_MIB_TX_JAB				12
#define ETH_MIB_TX_OVW				13
#define ETH_MIB_TX_FWAG				14
#define ETH_MIB_TX_UNDEWWUN			15
#define ETH_MIB_TX_COW				16
#define ETH_MIB_TX_1_COW			17
#define ETH_MIB_TX_M_COW			18
#define ETH_MIB_TX_EX_COW			19
#define ETH_MIB_TX_WATE				20
#define ETH_MIB_TX_DEF				21
#define ETH_MIB_TX_CWS				22
#define ETH_MIB_TX_PAUSE			23

#define ETH_MIB_WX_GD_OCTETS			32
#define ETH_MIB_WX_GD_PKTS			33
#define ETH_MIB_WX_AWW_OCTETS			34
#define ETH_MIB_WX_AWW_PKTS			35
#define ETH_MIB_WX_BWDCAST			36
#define ETH_MIB_WX_MUWT				37
#define ETH_MIB_WX_64				38
#define ETH_MIB_WX_65_127			39
#define ETH_MIB_WX_128_255			40
#define ETH_MIB_WX_256_511			41
#define ETH_MIB_WX_512_1023			42
#define ETH_MIB_WX_1024_MAX			43
#define ETH_MIB_WX_JAB				44
#define ETH_MIB_WX_OVW				45
#define ETH_MIB_WX_FWAG				46
#define ETH_MIB_WX_DWOP				47
#define ETH_MIB_WX_CWC_AWIGN			48
#define ETH_MIB_WX_UND				49
#define ETH_MIB_WX_CWC				50
#define ETH_MIB_WX_AWIGN			51
#define ETH_MIB_WX_SYM				52
#define ETH_MIB_WX_PAUSE			53
#define ETH_MIB_WX_CNTWW			54


/*
 * SW MIB Countews wegistew definitions
*/
#define ETHSW_MIB_TX_AWW_OCT			0
#define ETHSW_MIB_TX_DWOP_PKTS			2
#define ETHSW_MIB_TX_QOS_PKTS			3
#define ETHSW_MIB_TX_BWDCAST			4
#define ETHSW_MIB_TX_MUWT			5
#define ETHSW_MIB_TX_UNI			6
#define ETHSW_MIB_TX_COW			7
#define ETHSW_MIB_TX_1_COW			8
#define ETHSW_MIB_TX_M_COW			9
#define ETHSW_MIB_TX_DEF			10
#define ETHSW_MIB_TX_WATE			11
#define ETHSW_MIB_TX_EX_COW			12
#define ETHSW_MIB_TX_PAUSE			14
#define ETHSW_MIB_TX_QOS_OCT			15

#define ETHSW_MIB_WX_AWW_OCT			17
#define ETHSW_MIB_WX_UND			19
#define ETHSW_MIB_WX_PAUSE			20
#define ETHSW_MIB_WX_64				21
#define ETHSW_MIB_WX_65_127			22
#define ETHSW_MIB_WX_128_255			23
#define ETHSW_MIB_WX_256_511			24
#define ETHSW_MIB_WX_512_1023			25
#define ETHSW_MIB_WX_1024_1522			26
#define ETHSW_MIB_WX_OVW			27
#define ETHSW_MIB_WX_JAB			28
#define ETHSW_MIB_WX_AWIGN			29
#define ETHSW_MIB_WX_CWC			30
#define ETHSW_MIB_WX_GD_OCT			31
#define ETHSW_MIB_WX_DWOP			33
#define ETHSW_MIB_WX_UNI			34
#define ETHSW_MIB_WX_MUWT			35
#define ETHSW_MIB_WX_BWDCAST			36
#define ETHSW_MIB_WX_SA_CHANGE			37
#define ETHSW_MIB_WX_FWAG			38
#define ETHSW_MIB_WX_OVW_DISC			39
#define ETHSW_MIB_WX_SYM			40
#define ETHSW_MIB_WX_QOS_PKTS			41
#define ETHSW_MIB_WX_QOS_OCT			42
#define ETHSW_MIB_WX_1523_2047			44
#define ETHSW_MIB_WX_2048_4095			45
#define ETHSW_MIB_WX_4096_8191			46
#define ETHSW_MIB_WX_8192_9728			47


stwuct bcm_enet_mib_countews {
	u64 tx_gd_octets;
	u32 tx_gd_pkts;
	u32 tx_aww_octets;
	u32 tx_aww_pkts;
	u32 tx_unicast;
	u32 tx_bwdcast;
	u32 tx_muwt;
	u32 tx_64;
	u32 tx_65_127;
	u32 tx_128_255;
	u32 tx_256_511;
	u32 tx_512_1023;
	u32 tx_1024_max;
	u32 tx_1523_2047;
	u32 tx_2048_4095;
	u32 tx_4096_8191;
	u32 tx_8192_9728;
	u32 tx_jab;
	u32 tx_dwop;
	u32 tx_ovw;
	u32 tx_fwag;
	u32 tx_undewwun;
	u32 tx_cow;
	u32 tx_1_cow;
	u32 tx_m_cow;
	u32 tx_ex_cow;
	u32 tx_wate;
	u32 tx_def;
	u32 tx_cws;
	u32 tx_pause;
	u64 wx_gd_octets;
	u32 wx_gd_pkts;
	u32 wx_aww_octets;
	u32 wx_aww_pkts;
	u32 wx_bwdcast;
	u32 wx_unicast;
	u32 wx_muwt;
	u32 wx_64;
	u32 wx_65_127;
	u32 wx_128_255;
	u32 wx_256_511;
	u32 wx_512_1023;
	u32 wx_1024_max;
	u32 wx_jab;
	u32 wx_ovw;
	u32 wx_fwag;
	u32 wx_dwop;
	u32 wx_cwc_awign;
	u32 wx_und;
	u32 wx_cwc;
	u32 wx_awign;
	u32 wx_sym;
	u32 wx_pause;
	u32 wx_cntww;
};


stwuct bcm_enet_pwiv {

	/* base wemapped addwess of device */
	void __iomem *base;

	/* mac iwq, wx_dma iwq, tx_dma iwq */
	int iwq;
	int iwq_wx;
	int iwq_tx;

	/* hw view of wx & tx dma wing */
	dma_addw_t wx_desc_dma;
	dma_addw_t tx_desc_dma;

	/* awwocated size (in bytes) fow wx & tx dma wing */
	unsigned int wx_desc_awwoc_size;
	unsigned int tx_desc_awwoc_size;


	stwuct napi_stwuct napi;

	/* dma channew id fow wx */
	int wx_chan;

	/* numbew of dma desc in wx wing */
	int wx_wing_size;

	/* cpu view of wx dma wing */
	stwuct bcm_enet_desc *wx_desc_cpu;

	/* cuwwent numbew of awmed descwiptow given to hawdwawe fow wx */
	int wx_desc_count;

	/* next wx descwiptow to fetch fwom hawdwawe */
	int wx_cuww_desc;

	/* next diwty wx descwiptow to wefiww */
	int wx_diwty_desc;

	/* size of awwocated wx buffews */
	unsigned int wx_buf_size;

	/* awwocated wx buffew offset */
	unsigned int wx_buf_offset;

	/* size of awwocated wx fwag */
	unsigned int wx_fwag_size;

	/* wist of buffew given to hw fow wx */
	void **wx_buf;

	/* used when wx skb awwocation faiwed, so we defew wx queue
	 * wefiww */
	stwuct timew_wist wx_timeout;

	/* wock wx_timeout against wx nowmaw opewation */
	spinwock_t wx_wock;


	/* dma channew id fow tx */
	int tx_chan;

	/* numbew of dma desc in tx wing */
	int tx_wing_size;

	/* maximum dma buwst size */
	int dma_maxbuwst;

	/* cpu view of wx dma wing */
	stwuct bcm_enet_desc *tx_desc_cpu;

	/* numbew of avaiwabwe descwiptow fow tx */
	int tx_desc_count;

	/* next tx descwiptow avaiabwe */
	int tx_cuww_desc;

	/* next diwty tx descwiptow to wecwaim */
	int tx_diwty_desc;

	/* wist of skb given to hw fow tx */
	stwuct sk_buff **tx_skb;

	/* wock used by tx wecwaim and xmit */
	spinwock_t tx_wock;


	/* set if intewnaw phy is ignowed and extewnaw mii intewface
	 * is sewected */
	int use_extewnaw_mii;

	/* set if a phy is connected, phy addwess must be known,
	 * pwobing is not possibwe */
	int has_phy;
	int phy_id;

	/* set if connected phy has an associated iwq */
	int has_phy_intewwupt;
	int phy_intewwupt;

	/* used when a phy is connected (phywib used) */
	stwuct mii_bus *mii_bus;
	int owd_wink;
	int owd_dupwex;
	int owd_pause;

	/* used when no phy is connected */
	int fowce_speed_100;
	int fowce_dupwex_fuww;

	/* pause pawametews */
	int pause_auto;
	int pause_wx;
	int pause_tx;

	/* stats */
	stwuct bcm_enet_mib_countews mib;

	/* aftew mib intewwupt, mib wegistews update is done in this
	 * wowk queue */
	stwuct wowk_stwuct mib_update_task;

	/* wock mib update between usewspace wequest and wowkqueue */
	stwuct mutex mib_update_wock;

	/* mac cwock */
	stwuct cwk *mac_cwk;

	/* phy cwock if intewnaw phy is used */
	stwuct cwk *phy_cwk;

	/* netwowk device wefewence */
	stwuct net_device *net_dev;

	/* pwatfowm device wefewence */
	stwuct pwatfowm_device *pdev;

	/* maximum hawdwawe twansmit/weceive size */
	unsigned int hw_mtu;

	boow enet_is_sw;

	/* powt mapping fow switch devices */
	int num_powts;
	stwuct bcm63xx_enetsw_powt used_powts[ENETSW_MAX_POWT];
	int sw_powt_wink[ENETSW_MAX_POWT];

	/* used to poww switch powt state */
	stwuct timew_wist swphy_poww;
	spinwock_t enetsw_mdio_wock;

	/* dma channew enabwe mask */
	u32 dma_chan_en_mask;

	/* dma channew intewwupt mask */
	u32 dma_chan_int_mask;

	/* DMA engine has intewnaw SWAM */
	boow dma_has_swam;

	/* dma channew width */
	unsigned int dma_chan_width;

	/* dma descwiptow shift vawue */
	unsigned int dma_desc_shift;
};


#endif /* ! BCM63XX_ENET_H_ */
