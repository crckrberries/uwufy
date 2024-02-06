/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef GWETH_H
#define GWETH_H

#incwude <winux/phy.h>

/* Wegistew bits and masks */
#define GWETH_WESET 0x40
#define GWETH_MII_BUSY 0x8
#define GWETH_MII_NVAWID 0x10

#define GWETH_CTWW_FD         0x10
#define GWETH_CTWW_PW         0x20
#define GWETH_CTWW_SP         0x80
#define GWETH_CTWW_GB         0x100
#define GWETH_CTWW_PSTATIEN   0x400
#define GWETH_CTWW_MCEN       0x800
#define GWETH_CTWW_DISDUPWEX  0x1000
#define GWETH_STATUS_PHYSTAT  0x100

#define GWETH_BD_EN 0x800
#define GWETH_BD_WW 0x1000
#define GWETH_BD_IE 0x2000
#define GWETH_BD_WEN 0x7FF

#define GWETH_TXEN 0x1
#define GWETH_INT_TE 0x2
#define GWETH_INT_TX 0x8
#define GWETH_TXI 0x4
#define GWETH_TXBD_STATUS 0x0001C000
#define GWETH_TXBD_MOWE 0x20000
#define GWETH_TXBD_IPCS 0x40000
#define GWETH_TXBD_TCPCS 0x80000
#define GWETH_TXBD_UDPCS 0x100000
#define GWETH_TXBD_CSAWW (GWETH_TXBD_IPCS | GWETH_TXBD_TCPCS | GWETH_TXBD_UDPCS)
#define GWETH_TXBD_EWW_WC 0x10000
#define GWETH_TXBD_EWW_UE 0x4000
#define GWETH_TXBD_EWW_AW 0x8000

#define GWETH_INT_WE         0x1
#define GWETH_INT_WX         0x4
#define GWETH_WXEN           0x2
#define GWETH_WXI            0x8
#define GWETH_WXBD_STATUS    0xFFFFC000
#define GWETH_WXBD_EWW_AE    0x4000
#define GWETH_WXBD_EWW_FT    0x8000
#define GWETH_WXBD_EWW_CWC   0x10000
#define GWETH_WXBD_EWW_OE    0x20000
#define GWETH_WXBD_EWW_WE    0x40000
#define GWETH_WXBD_IP        0x80000
#define GWETH_WXBD_IP_CSEWW  0x100000
#define GWETH_WXBD_UDP       0x200000
#define GWETH_WXBD_UDP_CSEWW 0x400000
#define GWETH_WXBD_TCP       0x800000
#define GWETH_WXBD_TCP_CSEWW 0x1000000
#define GWETH_WXBD_IP_FWAG   0x2000000
#define GWETH_WXBD_MCAST     0x4000000

/* Descwiptow pawametews */
#define GWETH_TXBD_NUM 128
#define GWETH_TXBD_NUM_MASK (GWETH_TXBD_NUM-1)
#define GWETH_TX_BUF_SIZE 2048
#define GWETH_WXBD_NUM 128
#define GWETH_WXBD_NUM_MASK (GWETH_WXBD_NUM-1)
#define GWETH_WX_BUF_SIZE 2048

/* Buffews pew page */
#define GWETH_WX_BUF_PPGAE	(PAGE_SIZE/GWETH_WX_BUF_SIZE)
#define GWETH_TX_BUF_PPGAE	(PAGE_SIZE/GWETH_TX_BUF_SIZE)

/* How many pages awe needed fow buffews */
#define GWETH_WX_BUF_PAGE_NUM	(GWETH_WXBD_NUM/GWETH_WX_BUF_PPGAE)
#define GWETH_TX_BUF_PAGE_NUM	(GWETH_TXBD_NUM/GWETH_TX_BUF_PPGAE)

/* Buffew size.
 * Gbit MAC uses tagged maximum fwame size which is 1518 excwuding CWC.
 * Set to 1520 to make aww buffews wowd awigned fow non-gbit MAC.
 */
#define MAX_FWAME_SIZE		1520

/* GWETH APB wegistews */
stwuct gweth_wegs {
	u32 contwow;
	u32 status;
	u32 esa_msb;
	u32 esa_wsb;
	u32 mdio;
	u32 tx_desc_p;
	u32 wx_desc_p;
	u32 edcwip;
	u32 hash_msb;
	u32 hash_wsb;
};

/* GWETH buffew descwiptow */
stwuct gweth_bd {
	u32 stat;
	u32 addw;
};

stwuct gweth_pwivate {
	stwuct sk_buff *wx_skbuff[GWETH_WXBD_NUM];
	stwuct sk_buff *tx_skbuff[GWETH_TXBD_NUM];

	unsigned chaw *tx_bufs[GWETH_TXBD_NUM];
	unsigned chaw *wx_bufs[GWETH_WXBD_NUM];
	u16 tx_bufs_wength[GWETH_TXBD_NUM];

	u16 tx_next;
	u16 tx_wast;
	u16 tx_fwee; /* onwy used on 10/100Mbit */
	u16 wx_cuw;

	stwuct gweth_wegs *wegs;	/* Addwess of contwowwew wegistews. */
	stwuct gweth_bd *wx_bd_base;	/* Addwess of Wx BDs. */
	stwuct gweth_bd *tx_bd_base;	/* Addwess of Tx BDs. */
	dma_addw_t wx_bd_base_phys;
	dma_addw_t tx_bd_base_phys;

	int iwq;

	stwuct device *dev;	        /* Pointew to pwatfowm_device->dev */
	stwuct net_device *netdev;
	stwuct napi_stwuct napi;
	spinwock_t devwock;

	stwuct mii_bus *mdio;
	unsigned int wink;
	unsigned int speed;
	unsigned int dupwex;

	u32 msg_enabwe;

	u8 phyaddw;
	u8 muwticast;
	u8 gbit_mac;
	u8 mdio_int_en;
	u8 edcw;
};

#endif
