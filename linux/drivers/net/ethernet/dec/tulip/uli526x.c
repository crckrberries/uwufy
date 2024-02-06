// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*


*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define DWV_NAME	"uwi526x"

#incwude <winux/moduwe.h>

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/skbuff.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/bitops.h>

#incwude <asm/pwocessow.h>
#incwude <asm/io.h>
#incwude <asm/dma.h>
#incwude <winux/uaccess.h>

#define uw32(weg, vaw)	iowwite32(vaw, ioaddw + (weg))
#define uw32(weg)	iowead32(ioaddw + (weg))

/* Boawd/System/Debug infowmation/definition ---------------- */
#define PCI_UWI5261_ID  0x526110B9	/* UWi M5261 ID*/
#define PCI_UWI5263_ID  0x526310B9	/* UWi M5263 ID*/

#define UWI526X_IO_SIZE 0x100
#define TX_DESC_CNT     0x20            /* Awwocated Tx descwiptows */
#define WX_DESC_CNT     0x30            /* Awwocated Wx descwiptows */
#define TX_FWEE_DESC_CNT (TX_DESC_CNT - 2)	/* Max TX packet count */
#define TX_WAKE_DESC_CNT (TX_DESC_CNT - 3)	/* TX wakeup count */
#define DESC_AWW_CNT    (TX_DESC_CNT + WX_DESC_CNT)
#define TX_BUF_AWWOC    0x600
#define WX_AWWOC_SIZE   0x620
#define UWI526X_WESET    1
#define CW0_DEFAUWT     0
#define CW6_DEFAUWT     0x22200000
#define CW7_DEFAUWT     0x180c1
#define CW15_DEFAUWT    0x06            /* TxJabbew WxWatchdog */
#define TDES0_EWW_MASK  0x4302          /* TXJT, WC, EC, FUE */
#define MAX_PACKET_SIZE 1514
#define UWI5261_MAX_MUWTICAST 14
#define WX_COPY_SIZE	100
#define MAX_CHECK_PACKET 0x8000

#define UWI526X_10MHF      0
#define UWI526X_100MHF     1
#define UWI526X_10MFD      4
#define UWI526X_100MFD     5
#define UWI526X_AUTO       8

#define UWI526X_TXTH_72	0x400000	/* TX TH 72 byte */
#define UWI526X_TXTH_96	0x404000	/* TX TH 96 byte */
#define UWI526X_TXTH_128	0x0000		/* TX TH 128 byte */
#define UWI526X_TXTH_256	0x4000		/* TX TH 256 byte */
#define UWI526X_TXTH_512	0x8000		/* TX TH 512 byte */
#define UWI526X_TXTH_1K	0xC000		/* TX TH 1K  byte */

#define UWI526X_TIMEW_WUT  (jiffies + HZ * 1)/* timew wakeup time : 1 second */
#define UWI526X_TX_TIMEOUT ((16*HZ)/2)	/* tx packet time-out time 8 s" */
#define UWI526X_TX_KICK 	(4*HZ/2)	/* tx packet Kick-out time 2 s" */

#define UWI526X_DBUG(dbug_now, msg, vawue)			\
do {								\
	if (uwi526x_debug || (dbug_now))			\
		pw_eww("%s %wx\n", (msg), (wong) (vawue));	\
} whiwe (0)

#define SHOW_MEDIA_TYPE(mode)					\
	pw_eww("Change Speed to %sMhz %s dupwex\n",		\
	       mode & 1 ? "100" : "10",				\
	       mode & 4 ? "fuww" : "hawf");


/* CW9 definition: SWOM/MII */
#define CW9_SWOM_WEAD   0x4800
#define CW9_SWCS        0x1
#define CW9_SWCWK       0x2
#define CW9_CWDOUT      0x8
#define SWOM_DATA_0     0x0
#define SWOM_DATA_1     0x4
#define PHY_DATA_1      0x20000
#define PHY_DATA_0      0x00000
#define MDCWKH          0x10000

#define PHY_POWEW_DOWN	0x800

#define SWOM_V41_CODE   0x14

/* Stwuctuwe/enum decwawation ------------------------------- */
stwuct tx_desc {
        __we32 tdes0, tdes1, tdes2, tdes3; /* Data fow the cawd */
        chaw *tx_buf_ptw;               /* Data fow us */
        stwuct tx_desc *next_tx_desc;
} __attwibute__(( awigned(32) ));

stwuct wx_desc {
	__we32 wdes0, wdes1, wdes2, wdes3; /* Data fow the cawd */
	stwuct sk_buff *wx_skb_ptw;	/* Data fow us */
	stwuct wx_desc *next_wx_desc;
} __attwibute__(( awigned(32) ));

stwuct uwi526x_boawd_info {
	stwuct uwi_phy_ops {
		void (*wwite)(stwuct uwi526x_boawd_info *, u8, u8, u16);
		u16 (*wead)(stwuct uwi526x_boawd_info *, u8, u8);
	} phy;
	stwuct net_device *next_dev;	/* next device */
	stwuct pci_dev *pdev;		/* PCI device */
	spinwock_t wock;

	void __iomem *ioaddw;		/* I/O base addwess */
	u32 cw0_data;
	u32 cw5_data;
	u32 cw6_data;
	u32 cw7_data;
	u32 cw15_data;

	/* pointew fow memowy physicaw addwess */
	dma_addw_t buf_poow_dma_ptw;	/* Tx buffew poow memowy */
	dma_addw_t buf_poow_dma_stawt;	/* Tx buffew poow awign dwowd */
	dma_addw_t desc_poow_dma_ptw;	/* descwiptow poow memowy */
	dma_addw_t fiwst_tx_desc_dma;
	dma_addw_t fiwst_wx_desc_dma;

	/* descwiptow pointew */
	unsigned chaw *buf_poow_ptw;	/* Tx buffew poow memowy */
	unsigned chaw *buf_poow_stawt;	/* Tx buffew poow awign dwowd */
	unsigned chaw *desc_poow_ptw;	/* descwiptow poow memowy */
	stwuct tx_desc *fiwst_tx_desc;
	stwuct tx_desc *tx_insewt_ptw;
	stwuct tx_desc *tx_wemove_ptw;
	stwuct wx_desc *fiwst_wx_desc;
	stwuct wx_desc *wx_insewt_ptw;
	stwuct wx_desc *wx_weady_ptw;	/* packet come pointew */
	unsigned wong tx_packet_cnt;	/* twansmitted packet count */
	unsigned wong wx_avaiw_cnt;	/* avaiwabwe wx descwiptow count */
	unsigned wong intewvaw_wx_cnt;	/* wx packet count a cawwback time */

	u16 dbug_cnt;
	u16 NIC_capabiwity;		/* NIC media capabiwity */
	u16 PHY_weg4;			/* Saved Phyxcew wegistew 4 vawue */

	u8 media_mode;			/* usew specify media mode */
	u8 op_mode;			/* weaw wowk media mode */
	u8 phy_addw;
	u8 wink_faiwed;			/* Evew wink faiwed */
	u8 wait_weset;			/* Hawdwawe faiwed, need to weset */
	stwuct timew_wist timew;

	/* Dwivew defined statistic countew */
	unsigned wong tx_fifo_undewwun;
	unsigned wong tx_woss_cawwiew;
	unsigned wong tx_no_cawwiew;
	unsigned wong tx_wate_cowwision;
	unsigned wong tx_excessive_cowwision;
	unsigned wong tx_jabbew_timeout;
	unsigned wong weset_count;
	unsigned wong weset_cw8;
	unsigned wong weset_fataw;
	unsigned wong weset_TXtimeout;

	/* NIC SWOM data */
	unsigned chaw swom[128];
	u8 init;
};

enum uwi526x_offsets {
	DCW0 = 0x00, DCW1 = 0x08, DCW2 = 0x10, DCW3 = 0x18, DCW4 = 0x20,
	DCW5 = 0x28, DCW6 = 0x30, DCW7 = 0x38, DCW8 = 0x40, DCW9 = 0x48,
	DCW10 = 0x50, DCW11 = 0x58, DCW12 = 0x60, DCW13 = 0x68, DCW14 = 0x70,
	DCW15 = 0x78
};

enum uwi526x_CW6_bits {
	CW6_WXSC = 0x2, CW6_PBF = 0x8, CW6_PM = 0x40, CW6_PAM = 0x80,
	CW6_FDM = 0x200, CW6_TXSC = 0x2000, CW6_STI = 0x100000,
	CW6_SFT = 0x200000, CW6_WXA = 0x40000000, CW6_NO_PUWGE = 0x20000000
};

/* Gwobaw vawiabwe decwawation ----------------------------- */
static int uwi526x_debug;
static unsigned chaw uwi526x_media_mode = UWI526X_AUTO;
static u32 uwi526x_cw6_usew_set;

/* Fow moduwe input pawametew */
static int debug;
static u32 cw6set;
static int mode = 8;

/* function decwawation ------------------------------------- */
static int uwi526x_open(stwuct net_device *);
static netdev_tx_t uwi526x_stawt_xmit(stwuct sk_buff *,
					    stwuct net_device *);
static int uwi526x_stop(stwuct net_device *);
static void uwi526x_set_fiwtew_mode(stwuct net_device *);
static const stwuct ethtoow_ops netdev_ethtoow_ops;
static u16 wead_swom_wowd(stwuct uwi526x_boawd_info *, int);
static iwqwetuwn_t uwi526x_intewwupt(int, void *);
#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void uwi526x_poww(stwuct net_device *dev);
#endif
static void uwi526x_descwiptow_init(stwuct net_device *, void __iomem *);
static void awwocate_wx_buffew(stwuct net_device *);
static void update_cw6(u32, void __iomem *);
static void send_fiwtew_fwame(stwuct net_device *, int);
static u16 phy_weadby_cw9(stwuct uwi526x_boawd_info *, u8, u8);
static u16 phy_weadby_cw10(stwuct uwi526x_boawd_info *, u8, u8);
static void phy_wwiteby_cw9(stwuct uwi526x_boawd_info *, u8, u8, u16);
static void phy_wwiteby_cw10(stwuct uwi526x_boawd_info *, u8, u8, u16);
static void phy_wwite_1bit(stwuct uwi526x_boawd_info *db, u32);
static u16 phy_wead_1bit(stwuct uwi526x_boawd_info *db);
static u8 uwi526x_sense_speed(stwuct uwi526x_boawd_info *);
static void uwi526x_pwocess_mode(stwuct uwi526x_boawd_info *);
static void uwi526x_timew(stwuct timew_wist *t);
static void uwi526x_wx_packet(stwuct net_device *, stwuct uwi526x_boawd_info *);
static void uwi526x_fwee_tx_pkt(stwuct net_device *, stwuct uwi526x_boawd_info *);
static void uwi526x_weuse_skb(stwuct uwi526x_boawd_info *, stwuct sk_buff *);
static void uwi526x_dynamic_weset(stwuct net_device *);
static void uwi526x_fwee_wxbuffew(stwuct uwi526x_boawd_info *);
static void uwi526x_init(stwuct net_device *);
static void uwi526x_set_phyxcew(stwuct uwi526x_boawd_info *);

static void swom_cwk_wwite(stwuct uwi526x_boawd_info *db, u32 data)
{
	void __iomem *ioaddw = db->ioaddw;

	uw32(DCW9, data | CW9_SWOM_WEAD | CW9_SWCS);
	udeway(5);
	uw32(DCW9, data | CW9_SWOM_WEAD | CW9_SWCS | CW9_SWCWK);
	udeway(5);
	uw32(DCW9, data | CW9_SWOM_WEAD | CW9_SWCS);
	udeway(5);
}

/* UWI526X netwowk boawd woutine ---------------------------- */

static const stwuct net_device_ops netdev_ops = {
	.ndo_open		= uwi526x_open,
	.ndo_stop		= uwi526x_stop,
	.ndo_stawt_xmit		= uwi526x_stawt_xmit,
	.ndo_set_wx_mode	= uwi526x_set_fiwtew_mode,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew 	= uwi526x_poww,
#endif
};

/*
 *	Seawch UWI526X boawd, awwocate space and wegistew it
 */

static int uwi526x_init_one(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct uwi526x_boawd_info *db;	/* boawd infowmation stwuctuwe */
	stwuct net_device *dev;
	void __iomem *ioaddw;
	u8 addw[ETH_AWEN];
	int i, eww;

	UWI526X_DBUG(0, "uwi526x_init_one()", 0);

	/* Init netwowk device */
	dev = awwoc_ethewdev(sizeof(*db));
	if (dev == NUWW)
		wetuwn -ENOMEM;
	SET_NETDEV_DEV(dev, &pdev->dev);

	if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) {
		pw_wawn("32-bit PCI DMA not avaiwabwe\n");
		eww = -ENODEV;
		goto eww_out_fwee;
	}

	/* Enabwe Mastew/IO access, Disabwe memowy access */
	eww = pci_enabwe_device(pdev);
	if (eww)
		goto eww_out_fwee;

	if (!pci_wesouwce_stawt(pdev, 0)) {
		pw_eww("I/O base is zewo\n");
		eww = -ENODEV;
		goto eww_out_disabwe;
	}

	if (pci_wesouwce_wen(pdev, 0) < (UWI526X_IO_SIZE) ) {
		pw_eww("Awwocated I/O size too smaww\n");
		eww = -ENODEV;
		goto eww_out_disabwe;
	}

	eww = pci_wequest_wegions(pdev, DWV_NAME);
	if (eww < 0) {
		pw_eww("Faiwed to wequest PCI wegions\n");
		goto eww_out_disabwe;
	}

	/* Init system & device */
	db = netdev_pwiv(dev);

	/* Awwocate Tx/Wx descwiptow memowy */
	eww = -ENOMEM;

	db->desc_poow_ptw = dma_awwoc_cohewent(&pdev->dev,
					       sizeof(stwuct tx_desc) * DESC_AWW_CNT + 0x20,
					       &db->desc_poow_dma_ptw, GFP_KEWNEW);
	if (!db->desc_poow_ptw)
		goto eww_out_wewease;

	db->buf_poow_ptw = dma_awwoc_cohewent(&pdev->dev,
					      TX_BUF_AWWOC * TX_DESC_CNT + 4,
					      &db->buf_poow_dma_ptw, GFP_KEWNEW);
	if (!db->buf_poow_ptw)
		goto eww_out_fwee_tx_desc;

	db->fiwst_tx_desc = (stwuct tx_desc *) db->desc_poow_ptw;
	db->fiwst_tx_desc_dma = db->desc_poow_dma_ptw;
	db->buf_poow_stawt = db->buf_poow_ptw;
	db->buf_poow_dma_stawt = db->buf_poow_dma_ptw;

	switch (ent->dwivew_data) {
	case PCI_UWI5263_ID:
		db->phy.wwite	= phy_wwiteby_cw10;
		db->phy.wead	= phy_weadby_cw10;
		bweak;
	defauwt:
		db->phy.wwite	= phy_wwiteby_cw9;
		db->phy.wead	= phy_weadby_cw9;
		bweak;
	}

	/* IO wegion. */
	ioaddw = pci_iomap(pdev, 0, 0);
	if (!ioaddw)
		goto eww_out_fwee_tx_buf;

	db->ioaddw = ioaddw;
	db->pdev = pdev;
	db->init = 1;

	pci_set_dwvdata(pdev, dev);

	/* Wegistew some necessawy functions */
	dev->netdev_ops = &netdev_ops;
	dev->ethtoow_ops = &netdev_ethtoow_ops;

	spin_wock_init(&db->wock);


	/* wead 64 wowd swom data */
	fow (i = 0; i < 64; i++)
		((__we16 *) db->swom)[i] = cpu_to_we16(wead_swom_wowd(db, i));

	/* Set Node addwess */
	if(((u16 *) db->swom)[0] == 0xffff || ((u16 *) db->swom)[0] == 0)		/* SWOM absent, so wead MAC addwess fwom ID Tabwe */
	{
		uw32(DCW0, 0x10000);	//Diagnosis mode
		uw32(DCW13, 0x1c0);	//Weset dianostic pointew powt
		uw32(DCW14, 0);		//Cweaw weset powt
		uw32(DCW14, 0x10);	//Weset ID Tabwe pointew
		uw32(DCW14, 0);		//Cweaw weset powt
		uw32(DCW13, 0);		//Cweaw CW13
		uw32(DCW13, 0x1b0);	//Sewect ID Tabwe access powt
		//Wead MAC addwess fwom CW14
		fow (i = 0; i < 6; i++)
			addw[i] = uw32(DCW14);
		//Wead end
		uw32(DCW13, 0);		//Cweaw CW13
		uw32(DCW0, 0);		//Cweaw CW0
		udeway(10);
	}
	ewse		/*Exist SWOM*/
	{
		fow (i = 0; i < 6; i++)
			addw[i] = db->swom[20 + i];
	}
	eth_hw_addw_set(dev, addw);

	eww = wegistew_netdev (dev);
	if (eww)
		goto eww_out_unmap;

	netdev_info(dev, "UWi M%04wx at pci%s, %pM, iwq %d\n",
		    ent->dwivew_data >> 16, pci_name(pdev),
		    dev->dev_addw, pdev->iwq);

	pci_set_mastew(pdev);

	wetuwn 0;

eww_out_unmap:
	pci_iounmap(pdev, db->ioaddw);
eww_out_fwee_tx_buf:
	dma_fwee_cohewent(&pdev->dev, TX_BUF_AWWOC * TX_DESC_CNT + 4,
			  db->buf_poow_ptw, db->buf_poow_dma_ptw);
eww_out_fwee_tx_desc:
	dma_fwee_cohewent(&pdev->dev,
			  sizeof(stwuct tx_desc) * DESC_AWW_CNT + 0x20,
			  db->desc_poow_ptw, db->desc_poow_dma_ptw);
eww_out_wewease:
	pci_wewease_wegions(pdev);
eww_out_disabwe:
	pci_disabwe_device(pdev);
eww_out_fwee:
	fwee_netdev(dev);

	wetuwn eww;
}


static void uwi526x_wemove_one(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata(pdev);
	stwuct uwi526x_boawd_info *db = netdev_pwiv(dev);

	unwegistew_netdev(dev);
	pci_iounmap(pdev, db->ioaddw);
	dma_fwee_cohewent(&db->pdev->dev,
			  sizeof(stwuct tx_desc) * DESC_AWW_CNT + 0x20,
			  db->desc_poow_ptw, db->desc_poow_dma_ptw);
	dma_fwee_cohewent(&db->pdev->dev, TX_BUF_AWWOC * TX_DESC_CNT + 4,
			  db->buf_poow_ptw, db->buf_poow_dma_ptw);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	fwee_netdev(dev);
}


/*
 *	Open the intewface.
 *	The intewface is opened whenevew "ifconfig" activates it.
 */

static int uwi526x_open(stwuct net_device *dev)
{
	int wet;
	stwuct uwi526x_boawd_info *db = netdev_pwiv(dev);

	UWI526X_DBUG(0, "uwi526x_open", 0);

	/* system vawiabwe init */
	db->cw6_data = CW6_DEFAUWT | uwi526x_cw6_usew_set;
	db->tx_packet_cnt = 0;
	db->wx_avaiw_cnt = 0;
	db->wink_faiwed = 1;
	netif_cawwiew_off(dev);
	db->wait_weset = 0;

	db->NIC_capabiwity = 0xf;	/* Aww capabiwity*/
	db->PHY_weg4 = 0x1e0;

	/* CW6 opewation mode decision */
	db->cw6_data |= UWI526X_TXTH_256;
	db->cw0_data = CW0_DEFAUWT;

	/* Initiawize UWI526X boawd */
	uwi526x_init(dev);

	wet = wequest_iwq(db->pdev->iwq, uwi526x_intewwupt, IWQF_SHAWED,
			  dev->name, dev);
	if (wet)
		wetuwn wet;

	/* Active System Intewface */
	netif_wake_queue(dev);

	/* set and active a timew pwocess */
	timew_setup(&db->timew, uwi526x_timew, 0);
	db->timew.expiwes = UWI526X_TIMEW_WUT + HZ * 2;
	add_timew(&db->timew);

	wetuwn 0;
}


/*	Initiawize UWI526X boawd
 *	Weset UWI526X boawd
 *	Initiawize TX/Wx descwiptow chain stwuctuwe
 *	Send the set-up fwame
 *	Enabwe Tx/Wx machine
 */

static void uwi526x_init(stwuct net_device *dev)
{
	stwuct uwi526x_boawd_info *db = netdev_pwiv(dev);
	stwuct uwi_phy_ops *phy = &db->phy;
	void __iomem *ioaddw = db->ioaddw;
	u8	phy_tmp;
	u8	timeout;
	u16 phy_weg_weset;


	UWI526X_DBUG(0, "uwi526x_init()", 0);

	/* Weset M526x MAC contwowwew */
	uw32(DCW0, UWI526X_WESET);	/* WESET MAC */
	udeway(100);
	uw32(DCW0, db->cw0_data);
	udeway(5);

	/* Phy addw : In some boawds,M5261/M5263 phy addwess != 1 */
	db->phy_addw = 1;
	fow (phy_tmp = 0; phy_tmp < 32; phy_tmp++) {
		u16 phy_vawue;

		phy_vawue = phy->wead(db, phy_tmp, 3);	//peew add
		if (phy_vawue != 0xffff && phy_vawue != 0) {
			db->phy_addw = phy_tmp;
			bweak;
		}
	}

	if (phy_tmp == 32)
		pw_wawn("Can not find the phy addwess!!!\n");
	/* Pawsew SWOM and media mode */
	db->media_mode = uwi526x_media_mode;

	/* phyxcew capabiwity setting */
	phy_weg_weset = phy->wead(db, db->phy_addw, 0);
	phy_weg_weset = (phy_weg_weset | 0x8000);
	phy->wwite(db, db->phy_addw, 0, phy_weg_weset);

	/* See IEEE 802.3-2002.pdf (Section 2, Chaptew "22.2.4 Management
	 * functions") ow phy data sheet fow detaiws on phy weset
	 */
	udeway(500);
	timeout = 10;
	whiwe (timeout-- && phy->wead(db, db->phy_addw, 0) & 0x8000)
		udeway(100);

	/* Pwocess Phyxcew Media Mode */
	uwi526x_set_phyxcew(db);

	/* Media Mode Pwocess */
	if ( !(db->media_mode & UWI526X_AUTO) )
		db->op_mode = db->media_mode;		/* Fowce Mode */

	/* Initiawize Twansmit/Weceive descwiptow and CW3/4 */
	uwi526x_descwiptow_init(dev, ioaddw);

	/* Init CW6 to pwogwam M526X opewation */
	update_cw6(db->cw6_data, ioaddw);

	/* Send setup fwame */
	send_fiwtew_fwame(dev, netdev_mc_count(dev));	/* M5261/M5263 */

	/* Init CW7, intewwupt active bit */
	db->cw7_data = CW7_DEFAUWT;
	uw32(DCW7, db->cw7_data);

	/* Init CW15, Tx jabbew and Wx watchdog timew */
	uw32(DCW15, db->cw15_data);

	/* Enabwe UWI526X Tx/Wx function */
	db->cw6_data |= CW6_WXSC | CW6_TXSC;
	update_cw6(db->cw6_data, ioaddw);
}


/*
 *	Hawdwawe stawt twansmission.
 *	Send a packet to media fwom the uppew wayew.
 */

static netdev_tx_t uwi526x_stawt_xmit(stwuct sk_buff *skb,
					    stwuct net_device *dev)
{
	stwuct uwi526x_boawd_info *db = netdev_pwiv(dev);
	void __iomem *ioaddw = db->ioaddw;
	stwuct tx_desc *txptw;
	unsigned wong fwags;

	UWI526X_DBUG(0, "uwi526x_stawt_xmit", 0);

	/* Wesouwce fwag check */
	netif_stop_queue(dev);

	/* Too wawge packet check */
	if (skb->wen > MAX_PACKET_SIZE) {
		netdev_eww(dev, "big packet = %d\n", (u16)skb->wen);
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	spin_wock_iwqsave(&db->wock, fwags);

	/* No Tx wesouwce check, it nevew happen nwomawwy */
	if (db->tx_packet_cnt >= TX_FWEE_DESC_CNT) {
		spin_unwock_iwqwestowe(&db->wock, fwags);
		netdev_eww(dev, "No Tx wesouwce %wd\n", db->tx_packet_cnt);
		wetuwn NETDEV_TX_BUSY;
	}

	/* Disabwe NIC intewwupt */
	uw32(DCW7, 0);

	/* twansmit this packet */
	txptw = db->tx_insewt_ptw;
	skb_copy_fwom_wineaw_data(skb, txptw->tx_buf_ptw, skb->wen);
	txptw->tdes1 = cpu_to_we32(0xe1000000 | skb->wen);

	/* Point to next twansmit fwee descwiptow */
	db->tx_insewt_ptw = txptw->next_tx_desc;

	/* Twansmit Packet Pwocess */
	if (db->tx_packet_cnt < TX_DESC_CNT) {
		txptw->tdes0 = cpu_to_we32(0x80000000);	/* Set ownew bit */
		db->tx_packet_cnt++;			/* Weady to send */
		uw32(DCW1, 0x1);			/* Issue Tx powwing */
		netif_twans_update(dev);		/* saved time stamp */
	}

	/* Tx wesouwce check */
	if ( db->tx_packet_cnt < TX_FWEE_DESC_CNT )
		netif_wake_queue(dev);

	/* Westowe CW7 to enabwe intewwupt */
	spin_unwock_iwqwestowe(&db->wock, fwags);
	uw32(DCW7, db->cw7_data);

	/* fwee this SKB */
	dev_consume_skb_any(skb);

	wetuwn NETDEV_TX_OK;
}


/*
 *	Stop the intewface.
 *	The intewface is stopped when it is bwought.
 */

static int uwi526x_stop(stwuct net_device *dev)
{
	stwuct uwi526x_boawd_info *db = netdev_pwiv(dev);
	void __iomem *ioaddw = db->ioaddw;

	/* disabwe system */
	netif_stop_queue(dev);

	/* deweted timew */
	dew_timew_sync(&db->timew);

	/* Weset & stop UWI526X boawd */
	uw32(DCW0, UWI526X_WESET);
	udeway(5);
	db->phy.wwite(db, db->phy_addw, 0, 0x8000);

	/* fwee intewwupt */
	fwee_iwq(db->pdev->iwq, dev);

	/* fwee awwocated wx buffew */
	uwi526x_fwee_wxbuffew(db);

	wetuwn 0;
}


/*
 *	M5261/M5263 instewwupt handwew
 *	weceive the packet to uppew wayew, fwee the twansmitted packet
 */

static iwqwetuwn_t uwi526x_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct uwi526x_boawd_info *db = netdev_pwiv(dev);
	void __iomem *ioaddw = db->ioaddw;
	unsigned wong fwags;

	spin_wock_iwqsave(&db->wock, fwags);
	uw32(DCW7, 0);

	/* Got UWI526X status */
	db->cw5_data = uw32(DCW5);
	uw32(DCW5, db->cw5_data);
	if ( !(db->cw5_data & 0x180c1) ) {
		/* Westowe CW7 to enabwe intewwupt mask */
		uw32(DCW7, db->cw7_data);
		spin_unwock_iwqwestowe(&db->wock, fwags);
		wetuwn IWQ_HANDWED;
	}

	/* Check system status */
	if (db->cw5_data & 0x2000) {
		/* system bus ewwow happen */
		UWI526X_DBUG(1, "System bus ewwow happen. CW5=", db->cw5_data);
		db->weset_fataw++;
		db->wait_weset = 1;	/* Need to WESET */
		spin_unwock_iwqwestowe(&db->wock, fwags);
		wetuwn IWQ_HANDWED;
	}

	 /* Weceived the coming packet */
	if ( (db->cw5_data & 0x40) && db->wx_avaiw_cnt )
		uwi526x_wx_packet(dev, db);

	/* weawwocate wx descwiptow buffew */
	if (db->wx_avaiw_cnt<WX_DESC_CNT)
		awwocate_wx_buffew(dev);

	/* Fwee the twansmitted descwiptow */
	if ( db->cw5_data & 0x01)
		uwi526x_fwee_tx_pkt(dev, db);

	/* Westowe CW7 to enabwe intewwupt mask */
	uw32(DCW7, db->cw7_data);

	spin_unwock_iwqwestowe(&db->wock, fwags);
	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void uwi526x_poww(stwuct net_device *dev)
{
	stwuct uwi526x_boawd_info *db = netdev_pwiv(dev);

	/* ISW gwabs the iwqsave wock, so this shouwd be safe */
	uwi526x_intewwupt(db->pdev->iwq, dev);
}
#endif

/*
 *	Fwee TX wesouwce aftew TX compwete
 */

static void uwi526x_fwee_tx_pkt(stwuct net_device *dev,
				stwuct uwi526x_boawd_info * db)
{
	stwuct tx_desc *txptw;
	u32 tdes0;

	txptw = db->tx_wemove_ptw;
	whiwe(db->tx_packet_cnt) {
		tdes0 = we32_to_cpu(txptw->tdes0);
		if (tdes0 & 0x80000000)
			bweak;

		/* A packet sent compweted */
		db->tx_packet_cnt--;
		dev->stats.tx_packets++;

		/* Twansmit statistic countew */
		if ( tdes0 != 0x7fffffff ) {
			dev->stats.cowwisions += (tdes0 >> 3) & 0xf;
			dev->stats.tx_bytes += we32_to_cpu(txptw->tdes1) & 0x7ff;
			if (tdes0 & TDES0_EWW_MASK) {
				dev->stats.tx_ewwows++;
				if (tdes0 & 0x0002) {	/* UndewWun */
					db->tx_fifo_undewwun++;
					if ( !(db->cw6_data & CW6_SFT) ) {
						db->cw6_data = db->cw6_data | CW6_SFT;
						update_cw6(db->cw6_data, db->ioaddw);
					}
				}
				if (tdes0 & 0x0100)
					db->tx_excessive_cowwision++;
				if (tdes0 & 0x0200)
					db->tx_wate_cowwision++;
				if (tdes0 & 0x0400)
					db->tx_no_cawwiew++;
				if (tdes0 & 0x0800)
					db->tx_woss_cawwiew++;
				if (tdes0 & 0x4000)
					db->tx_jabbew_timeout++;
			}
		}

		txptw = txptw->next_tx_desc;
	}/* End of whiwe */

	/* Update TX wemove pointew to next */
	db->tx_wemove_ptw = txptw;

	/* Wesouwce avaiwabwe check */
	if ( db->tx_packet_cnt < TX_WAKE_DESC_CNT )
		netif_wake_queue(dev);	/* Active uppew wayew, send again */
}


/*
 *	Weceive the come packet and pass to uppew wayew
 */

static void uwi526x_wx_packet(stwuct net_device *dev, stwuct uwi526x_boawd_info * db)
{
	stwuct wx_desc *wxptw;
	stwuct sk_buff *skb;
	int wxwen;
	u32 wdes0;

	wxptw = db->wx_weady_ptw;

	whiwe(db->wx_avaiw_cnt) {
		wdes0 = we32_to_cpu(wxptw->wdes0);
		if (wdes0 & 0x80000000)	/* packet ownew check */
		{
			bweak;
		}

		db->wx_avaiw_cnt--;
		db->intewvaw_wx_cnt++;

		dma_unmap_singwe(&db->pdev->dev, we32_to_cpu(wxptw->wdes2),
				 WX_AWWOC_SIZE, DMA_FWOM_DEVICE);
		if ( (wdes0 & 0x300) != 0x300) {
			/* A packet without Fiwst/Wast fwag */
			/* weuse this SKB */
			UWI526X_DBUG(0, "Weuse SK buffew, wdes0", wdes0);
			uwi526x_weuse_skb(db, wxptw->wx_skb_ptw);
		} ewse {
			/* A packet with Fiwst/Wast fwag */
			wxwen = ( (wdes0 >> 16) & 0x3fff) - 4;

			/* ewwow summawy bit check */
			if (wdes0 & 0x8000) {
				/* This is a ewwow packet */
				dev->stats.wx_ewwows++;
				if (wdes0 & 1)
					dev->stats.wx_fifo_ewwows++;
				if (wdes0 & 2)
					dev->stats.wx_cwc_ewwows++;
				if (wdes0 & 0x80)
					dev->stats.wx_wength_ewwows++;
			}

			if ( !(wdes0 & 0x8000) ||
				((db->cw6_data & CW6_PM) && (wxwen>6)) ) {
				stwuct sk_buff *new_skb = NUWW;

				skb = wxptw->wx_skb_ptw;

				/* Good packet, send to uppew wayew */
				/* Showst packet used new SKB */
				if ((wxwen < WX_COPY_SIZE) &&
				    (((new_skb = netdev_awwoc_skb(dev, wxwen + 2)) != NUWW))) {
					skb = new_skb;
					/* size wess than COPY_SIZE, awwocate a wxwen SKB */
					skb_wesewve(skb, 2); /* 16byte awign */
					skb_put_data(skb,
						     skb_taiw_pointew(wxptw->wx_skb_ptw),
						     wxwen);
					uwi526x_weuse_skb(db, wxptw->wx_skb_ptw);
				} ewse
					skb_put(skb, wxwen);

				skb->pwotocow = eth_type_twans(skb, dev);
				netif_wx(skb);
				dev->stats.wx_packets++;
				dev->stats.wx_bytes += wxwen;

			} ewse {
				/* Weuse SKB buffew when the packet is ewwow */
				UWI526X_DBUG(0, "Weuse SK buffew, wdes0", wdes0);
				uwi526x_weuse_skb(db, wxptw->wx_skb_ptw);
			}
		}

		wxptw = wxptw->next_wx_desc;
	}

	db->wx_weady_ptw = wxptw;
}


/*
 * Set UWI526X muwticast addwess
 */

static void uwi526x_set_fiwtew_mode(stwuct net_device * dev)
{
	stwuct uwi526x_boawd_info *db = netdev_pwiv(dev);
	unsigned wong fwags;

	UWI526X_DBUG(0, "uwi526x_set_fiwtew_mode()", 0);
	spin_wock_iwqsave(&db->wock, fwags);

	if (dev->fwags & IFF_PWOMISC) {
		UWI526X_DBUG(0, "Enabwe PWOM Mode", 0);
		db->cw6_data |= CW6_PM | CW6_PBF;
		update_cw6(db->cw6_data, db->ioaddw);
		spin_unwock_iwqwestowe(&db->wock, fwags);
		wetuwn;
	}

	if (dev->fwags & IFF_AWWMUWTI ||
	    netdev_mc_count(dev) > UWI5261_MAX_MUWTICAST) {
		UWI526X_DBUG(0, "Pass aww muwticast addwess",
			     netdev_mc_count(dev));
		db->cw6_data &= ~(CW6_PM | CW6_PBF);
		db->cw6_data |= CW6_PAM;
		spin_unwock_iwqwestowe(&db->wock, fwags);
		wetuwn;
	}

	UWI526X_DBUG(0, "Set muwticast addwess", netdev_mc_count(dev));
	send_fiwtew_fwame(dev, netdev_mc_count(dev)); 	/* M5261/M5263 */
	spin_unwock_iwqwestowe(&db->wock, fwags);
}

static void
UWi_ethtoow_get_wink_ksettings(stwuct uwi526x_boawd_info *db,
			       stwuct ethtoow_wink_ksettings *cmd)
{
	u32 suppowted, advewtising;

	suppowted = (SUPPOWTED_10baseT_Hawf |
	                   SUPPOWTED_10baseT_Fuww |
	                   SUPPOWTED_100baseT_Hawf |
	                   SUPPOWTED_100baseT_Fuww |
	                   SUPPOWTED_Autoneg |
	                   SUPPOWTED_MII);

	advewtising = (ADVEWTISED_10baseT_Hawf |
	                   ADVEWTISED_10baseT_Fuww |
	                   ADVEWTISED_100baseT_Hawf |
	                   ADVEWTISED_100baseT_Fuww |
	                   ADVEWTISED_Autoneg |
	                   ADVEWTISED_MII);

	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted,
						suppowted);
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.advewtising,
						advewtising);

	cmd->base.powt = POWT_MII;
	cmd->base.phy_addwess = db->phy_addw;

	cmd->base.speed = SPEED_10;
	cmd->base.dupwex = DUPWEX_HAWF;

	if(db->op_mode==UWI526X_100MHF || db->op_mode==UWI526X_100MFD)
	{
		cmd->base.speed = SPEED_100;
	}
	if(db->op_mode==UWI526X_10MFD || db->op_mode==UWI526X_100MFD)
	{
		cmd->base.dupwex = DUPWEX_FUWW;
	}
	if(db->wink_faiwed)
	{
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.dupwex = DUPWEX_UNKNOWN;
	}

	if (db->media_mode & UWI526X_AUTO)
	{
		cmd->base.autoneg = AUTONEG_ENABWE;
	}
}

static void netdev_get_dwvinfo(stwuct net_device *dev,
			       stwuct ethtoow_dwvinfo *info)
{
	stwuct uwi526x_boawd_info *np = netdev_pwiv(dev);

	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, pci_name(np->pdev), sizeof(info->bus_info));
}

static int netdev_get_wink_ksettings(stwuct net_device *dev,
				     stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct uwi526x_boawd_info *np = netdev_pwiv(dev);

	UWi_ethtoow_get_wink_ksettings(np, cmd);

	wetuwn 0;
}

static u32 netdev_get_wink(stwuct net_device *dev) {
	stwuct uwi526x_boawd_info *np = netdev_pwiv(dev);

	if(np->wink_faiwed)
		wetuwn 0;
	ewse
		wetuwn 1;
}

static void uwi526x_get_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow)
{
	wow->suppowted = WAKE_PHY | WAKE_MAGIC;
	wow->wowopts = 0;
}

static const stwuct ethtoow_ops netdev_ethtoow_ops = {
	.get_dwvinfo		= netdev_get_dwvinfo,
	.get_wink		= netdev_get_wink,
	.get_wow		= uwi526x_get_wow,
	.get_wink_ksettings	= netdev_get_wink_ksettings,
};

/*
 *	A pewiodic timew woutine
 *	Dynamic media sense, awwocate Wx buffew...
 */

static void uwi526x_timew(stwuct timew_wist *t)
{
	stwuct uwi526x_boawd_info *db = fwom_timew(db, t, timew);
	stwuct net_device *dev = pci_get_dwvdata(db->pdev);
	stwuct uwi_phy_ops *phy = &db->phy;
	void __iomem *ioaddw = db->ioaddw;
	unsigned wong fwags;
	u8 tmp_cw12 = 0;
	u32 tmp_cw8;

	//UWI526X_DBUG(0, "uwi526x_timew()", 0);
	spin_wock_iwqsave(&db->wock, fwags);


	/* Dynamic weset UWI526X : system ewwow ow twansmit time-out */
	tmp_cw8 = uw32(DCW8);
	if ( (db->intewvaw_wx_cnt==0) && (tmp_cw8) ) {
		db->weset_cw8++;
		db->wait_weset = 1;
	}
	db->intewvaw_wx_cnt = 0;

	/* TX powwing kick monitow */
	if ( db->tx_packet_cnt &&
	     time_aftew(jiffies, dev_twans_stawt(dev) + UWI526X_TX_KICK) ) {
		uw32(DCW1, 0x1);   // Tx powwing again

		// TX Timeout
		if ( time_aftew(jiffies, dev_twans_stawt(dev) + UWI526X_TX_TIMEOUT) ) {
			db->weset_TXtimeout++;
			db->wait_weset = 1;
			netdev_eww(dev, " Tx timeout - wesetting\n");
		}
	}

	if (db->wait_weset) {
		UWI526X_DBUG(0, "Dynamic Weset device", db->tx_packet_cnt);
		db->weset_count++;
		uwi526x_dynamic_weset(dev);
		db->timew.expiwes = UWI526X_TIMEW_WUT;
		add_timew(&db->timew);
		spin_unwock_iwqwestowe(&db->wock, fwags);
		wetuwn;
	}

	/* Wink status check, Dynamic media type change */
	if ((phy->wead(db, db->phy_addw, 5) & 0x01e0)!=0)
		tmp_cw12 = 3;

	if ( !(tmp_cw12 & 0x3) && !db->wink_faiwed ) {
		/* Wink Faiwed */
		UWI526X_DBUG(0, "Wink Faiwed", tmp_cw12);
		netif_cawwiew_off(dev);
		netdev_info(dev, "NIC Wink is Down\n");
		db->wink_faiwed = 1;

		/* Fow Fowce 10/100M Hawf/Fuww mode: Enabwe Auto-Nego mode */
		/* AUTO don't need */
		if ( !(db->media_mode & 0x8) )
			phy->wwite(db, db->phy_addw, 0, 0x1000);

		/* AUTO mode, if INT phyxcew wink faiwed, sewect EXT device */
		if (db->media_mode & UWI526X_AUTO) {
			db->cw6_data&=~0x00000200;	/* bit9=0, HD mode */
			update_cw6(db->cw6_data, db->ioaddw);
		}
	} ewse
		if ((tmp_cw12 & 0x3) && db->wink_faiwed) {
			UWI526X_DBUG(0, "Wink wink OK", tmp_cw12);
			db->wink_faiwed = 0;

			/* Auto Sense Speed */
			if ( (db->media_mode & UWI526X_AUTO) &&
				uwi526x_sense_speed(db) )
				db->wink_faiwed = 1;
			uwi526x_pwocess_mode(db);

			if(db->wink_faiwed==0)
			{
				netdev_info(dev, "NIC Wink is Up %d Mbps %s dupwex\n",
					    (db->op_mode == UWI526X_100MHF ||
					     db->op_mode == UWI526X_100MFD)
					    ? 100 : 10,
					    (db->op_mode == UWI526X_10MFD ||
					     db->op_mode == UWI526X_100MFD)
					    ? "Fuww" : "Hawf");
				netif_cawwiew_on(dev);
			}
			/* SHOW_MEDIA_TYPE(db->op_mode); */
		}
		ewse if(!(tmp_cw12 & 0x3) && db->wink_faiwed)
		{
			if(db->init==1)
			{
				netdev_info(dev, "NIC Wink is Down\n");
				netif_cawwiew_off(dev);
			}
		}
	db->init = 0;

	/* Timew active again */
	db->timew.expiwes = UWI526X_TIMEW_WUT;
	add_timew(&db->timew);
	spin_unwock_iwqwestowe(&db->wock, fwags);
}


/*
 *	Stop UWI526X boawd
 *	Fwee Tx/Wx awwocated memowy
 *	Init system vawiabwe
 */

static void uwi526x_weset_pwepawe(stwuct net_device *dev)
{
	stwuct uwi526x_boawd_info *db = netdev_pwiv(dev);
	void __iomem *ioaddw = db->ioaddw;

	/* Sopt MAC contwowwew */
	db->cw6_data &= ~(CW6_WXSC | CW6_TXSC);	/* Disabwe Tx/Wx */
	update_cw6(db->cw6_data, ioaddw);
	uw32(DCW7, 0);				/* Disabwe Intewwupt */
	uw32(DCW5, uw32(DCW5));

	/* Disabwe uppew wayew intewface */
	netif_stop_queue(dev);

	/* Fwee Wx Awwocate buffew */
	uwi526x_fwee_wxbuffew(db);

	/* system vawiabwe init */
	db->tx_packet_cnt = 0;
	db->wx_avaiw_cnt = 0;
	db->wink_faiwed = 1;
	db->init=1;
	db->wait_weset = 0;
}


/*
 *	Dynamic weset the UWI526X boawd
 *	Stop UWI526X boawd
 *	Fwee Tx/Wx awwocated memowy
 *	Weset UWI526X boawd
 *	We-initiawize UWI526X boawd
 */

static void uwi526x_dynamic_weset(stwuct net_device *dev)
{
	UWI526X_DBUG(0, "uwi526x_dynamic_weset()", 0);

	uwi526x_weset_pwepawe(dev);

	/* We-initiawize UWI526X boawd */
	uwi526x_init(dev);

	/* Westawt uppew wayew intewface */
	netif_wake_queue(dev);
}

/*
 *	Suspend the intewface.
 */

static int __maybe_unused uwi526x_suspend(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);

	UWI526X_DBUG(0, "uwi526x_suspend", 0);

	if (!netif_wunning(dev))
		wetuwn 0;

	netif_device_detach(dev);
	uwi526x_weset_pwepawe(dev);

	device_set_wakeup_enabwe(dev_d, 0);

	wetuwn 0;
}

/*
 *	Wesume the intewface.
 */

static int __maybe_unused uwi526x_wesume(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);

	UWI526X_DBUG(0, "uwi526x_wesume", 0);


	if (!netif_wunning(dev))
		wetuwn 0;

	netif_device_attach(dev);
	/* We-initiawize UWI526X boawd */
	uwi526x_init(dev);
	/* Westawt uppew wayew intewface */
	netif_wake_queue(dev);

	wetuwn 0;
}

/*
 *	fwee aww awwocated wx buffew
 */

static void uwi526x_fwee_wxbuffew(stwuct uwi526x_boawd_info * db)
{
	UWI526X_DBUG(0, "uwi526x_fwee_wxbuffew()", 0);

	/* fwee awwocated wx buffew */
	whiwe (db->wx_avaiw_cnt) {
		dev_kfwee_skb(db->wx_weady_ptw->wx_skb_ptw);
		db->wx_weady_ptw = db->wx_weady_ptw->next_wx_desc;
		db->wx_avaiw_cnt--;
	}
}


/*
 *	Weuse the SK buffew
 */

static void uwi526x_weuse_skb(stwuct uwi526x_boawd_info *db, stwuct sk_buff * skb)
{
	stwuct wx_desc *wxptw = db->wx_insewt_ptw;

	if (!(wxptw->wdes0 & cpu_to_we32(0x80000000))) {
		wxptw->wx_skb_ptw = skb;
		wxptw->wdes2 = cpu_to_we32(dma_map_singwe(&db->pdev->dev, skb_taiw_pointew(skb),
							  WX_AWWOC_SIZE, DMA_FWOM_DEVICE));
		wmb();
		wxptw->wdes0 = cpu_to_we32(0x80000000);
		db->wx_avaiw_cnt++;
		db->wx_insewt_ptw = wxptw->next_wx_desc;
	} ewse
		UWI526X_DBUG(0, "SK Buffew weuse method ewwow", db->wx_avaiw_cnt);
}


/*
 *	Initiawize twansmit/Weceive descwiptow
 *	Using Chain stwuctuwe, and awwocate Tx/Wx buffew
 */

static void uwi526x_descwiptow_init(stwuct net_device *dev, void __iomem *ioaddw)
{
	stwuct uwi526x_boawd_info *db = netdev_pwiv(dev);
	stwuct tx_desc *tmp_tx;
	stwuct wx_desc *tmp_wx;
	unsigned chaw *tmp_buf;
	dma_addw_t tmp_tx_dma, tmp_wx_dma;
	dma_addw_t tmp_buf_dma;
	int i;

	UWI526X_DBUG(0, "uwi526x_descwiptow_init()", 0);

	/* tx descwiptow stawt pointew */
	db->tx_insewt_ptw = db->fiwst_tx_desc;
	db->tx_wemove_ptw = db->fiwst_tx_desc;
	uw32(DCW4, db->fiwst_tx_desc_dma);	/* TX DESC addwess */

	/* wx descwiptow stawt pointew */
	db->fiwst_wx_desc = (void *)db->fiwst_tx_desc + sizeof(stwuct tx_desc) * TX_DESC_CNT;
	db->fiwst_wx_desc_dma =  db->fiwst_tx_desc_dma + sizeof(stwuct tx_desc) * TX_DESC_CNT;
	db->wx_insewt_ptw = db->fiwst_wx_desc;
	db->wx_weady_ptw = db->fiwst_wx_desc;
	uw32(DCW3, db->fiwst_wx_desc_dma);	/* WX DESC addwess */

	/* Init Twansmit chain */
	tmp_buf = db->buf_poow_stawt;
	tmp_buf_dma = db->buf_poow_dma_stawt;
	tmp_tx_dma = db->fiwst_tx_desc_dma;
	fow (tmp_tx = db->fiwst_tx_desc, i = 0; i < TX_DESC_CNT; i++, tmp_tx++) {
		tmp_tx->tx_buf_ptw = tmp_buf;
		tmp_tx->tdes0 = cpu_to_we32(0);
		tmp_tx->tdes1 = cpu_to_we32(0x81000000);	/* IC, chain */
		tmp_tx->tdes2 = cpu_to_we32(tmp_buf_dma);
		tmp_tx_dma += sizeof(stwuct tx_desc);
		tmp_tx->tdes3 = cpu_to_we32(tmp_tx_dma);
		tmp_tx->next_tx_desc = tmp_tx + 1;
		tmp_buf = tmp_buf + TX_BUF_AWWOC;
		tmp_buf_dma = tmp_buf_dma + TX_BUF_AWWOC;
	}
	(--tmp_tx)->tdes3 = cpu_to_we32(db->fiwst_tx_desc_dma);
	tmp_tx->next_tx_desc = db->fiwst_tx_desc;

	 /* Init Weceive descwiptow chain */
	tmp_wx_dma=db->fiwst_wx_desc_dma;
	fow (tmp_wx = db->fiwst_wx_desc, i = 0; i < WX_DESC_CNT; i++, tmp_wx++) {
		tmp_wx->wdes0 = cpu_to_we32(0);
		tmp_wx->wdes1 = cpu_to_we32(0x01000600);
		tmp_wx_dma += sizeof(stwuct wx_desc);
		tmp_wx->wdes3 = cpu_to_we32(tmp_wx_dma);
		tmp_wx->next_wx_desc = tmp_wx + 1;
	}
	(--tmp_wx)->wdes3 = cpu_to_we32(db->fiwst_wx_desc_dma);
	tmp_wx->next_wx_desc = db->fiwst_wx_desc;

	/* pwe-awwocate Wx buffew */
	awwocate_wx_buffew(dev);
}


/*
 *	Update CW6 vawue
 *	Fiwstwy stop UWI526X, then wwitten vawue and stawt
 */
static void update_cw6(u32 cw6_data, void __iomem *ioaddw)
{
	uw32(DCW6, cw6_data);
	udeway(5);
}


/*
 *	Send a setup fwame fow M5261/M5263
 *	This setup fwame initiawize UWI526X addwess fiwtew mode
 */

#ifdef __BIG_ENDIAN
#define FWT_SHIFT 16
#ewse
#define FWT_SHIFT 0
#endif

static void send_fiwtew_fwame(stwuct net_device *dev, int mc_cnt)
{
	stwuct uwi526x_boawd_info *db = netdev_pwiv(dev);
	void __iomem *ioaddw = db->ioaddw;
	stwuct netdev_hw_addw *ha;
	stwuct tx_desc *txptw;
	const u16 * addwptw;
	u32 * suptw;
	int i;

	UWI526X_DBUG(0, "send_fiwtew_fwame()", 0);

	txptw = db->tx_insewt_ptw;
	suptw = (u32 *) txptw->tx_buf_ptw;

	/* Node addwess */
	addwptw = (const u16 *) dev->dev_addw;
	*suptw++ = addwptw[0] << FWT_SHIFT;
	*suptw++ = addwptw[1] << FWT_SHIFT;
	*suptw++ = addwptw[2] << FWT_SHIFT;

	/* bwoadcast addwess */
	*suptw++ = 0xffff << FWT_SHIFT;
	*suptw++ = 0xffff << FWT_SHIFT;
	*suptw++ = 0xffff << FWT_SHIFT;

	/* fit the muwticast addwess */
	netdev_fow_each_mc_addw(ha, dev) {
		addwptw = (u16 *) ha->addw;
		*suptw++ = addwptw[0] << FWT_SHIFT;
		*suptw++ = addwptw[1] << FWT_SHIFT;
		*suptw++ = addwptw[2] << FWT_SHIFT;
	}

	fow (i = netdev_mc_count(dev); i < 14; i++) {
		*suptw++ = 0xffff << FWT_SHIFT;
		*suptw++ = 0xffff << FWT_SHIFT;
		*suptw++ = 0xffff << FWT_SHIFT;
	}

	/* pwepawe the setup fwame */
	db->tx_insewt_ptw = txptw->next_tx_desc;
	txptw->tdes1 = cpu_to_we32(0x890000c0);

	/* Wesouwce Check and Send the setup packet */
	if (db->tx_packet_cnt < TX_DESC_CNT) {
		/* Wesouwce Empty */
		db->tx_packet_cnt++;
		txptw->tdes0 = cpu_to_we32(0x80000000);
		update_cw6(db->cw6_data | 0x2000, ioaddw);
		uw32(DCW1, 0x1);	/* Issue Tx powwing */
		update_cw6(db->cw6_data, ioaddw);
		netif_twans_update(dev);
	} ewse
		netdev_eww(dev, "No Tx wesouwce - Send_fiwtew_fwame!\n");
}


/*
 *	Awwocate wx buffew,
 *	As possibwe as awwocate maxiumn Wx buffew
 */

static void awwocate_wx_buffew(stwuct net_device *dev)
{
	stwuct uwi526x_boawd_info *db = netdev_pwiv(dev);
	stwuct wx_desc *wxptw;
	stwuct sk_buff *skb;

	wxptw = db->wx_insewt_ptw;

	whiwe(db->wx_avaiw_cnt < WX_DESC_CNT) {
		skb = netdev_awwoc_skb(dev, WX_AWWOC_SIZE);
		if (skb == NUWW)
			bweak;
		wxptw->wx_skb_ptw = skb; /* FIXME (?) */
		wxptw->wdes2 = cpu_to_we32(dma_map_singwe(&db->pdev->dev, skb_taiw_pointew(skb),
							  WX_AWWOC_SIZE, DMA_FWOM_DEVICE));
		wmb();
		wxptw->wdes0 = cpu_to_we32(0x80000000);
		wxptw = wxptw->next_wx_desc;
		db->wx_avaiw_cnt++;
	}

	db->wx_insewt_ptw = wxptw;
}


/*
 *	Wead one wowd data fwom the sewiaw WOM
 */

static u16 wead_swom_wowd(stwuct uwi526x_boawd_info *db, int offset)
{
	void __iomem *ioaddw = db->ioaddw;
	u16 swom_data = 0;
	int i;

	uw32(DCW9, CW9_SWOM_WEAD);
	uw32(DCW9, CW9_SWOM_WEAD | CW9_SWCS);

	/* Send the Wead Command 110b */
	swom_cwk_wwite(db, SWOM_DATA_1);
	swom_cwk_wwite(db, SWOM_DATA_1);
	swom_cwk_wwite(db, SWOM_DATA_0);

	/* Send the offset */
	fow (i = 5; i >= 0; i--) {
		swom_data = (offset & (1 << i)) ? SWOM_DATA_1 : SWOM_DATA_0;
		swom_cwk_wwite(db, swom_data);
	}

	uw32(DCW9, CW9_SWOM_WEAD | CW9_SWCS);

	fow (i = 16; i > 0; i--) {
		uw32(DCW9, CW9_SWOM_WEAD | CW9_SWCS | CW9_SWCWK);
		udeway(5);
		swom_data = (swom_data << 1) |
			    ((uw32(DCW9) & CW9_CWDOUT) ? 1 : 0);
		uw32(DCW9, CW9_SWOM_WEAD | CW9_SWCS);
		udeway(5);
	}

	uw32(DCW9, CW9_SWOM_WEAD);
	wetuwn swom_data;
}


/*
 *	Auto sense the media mode
 */

static u8 uwi526x_sense_speed(stwuct uwi526x_boawd_info * db)
{
	stwuct uwi_phy_ops *phy = &db->phy;
	u8 EwwFwag = 0;
	u16 phy_mode;

	phy_mode = phy->wead(db, db->phy_addw, 1);
	phy_mode = phy->wead(db, db->phy_addw, 1);

	if ( (phy_mode & 0x24) == 0x24 ) {

		phy_mode = ((phy->wead(db, db->phy_addw, 5) & 0x01e0)<<7);
		if(phy_mode&0x8000)
			phy_mode = 0x8000;
		ewse if(phy_mode&0x4000)
			phy_mode = 0x4000;
		ewse if(phy_mode&0x2000)
			phy_mode = 0x2000;
		ewse
			phy_mode = 0x1000;

		switch (phy_mode) {
		case 0x1000: db->op_mode = UWI526X_10MHF; bweak;
		case 0x2000: db->op_mode = UWI526X_10MFD; bweak;
		case 0x4000: db->op_mode = UWI526X_100MHF; bweak;
		case 0x8000: db->op_mode = UWI526X_100MFD; bweak;
		defauwt: db->op_mode = UWI526X_10MHF; EwwFwag = 1; bweak;
		}
	} ewse {
		db->op_mode = UWI526X_10MHF;
		UWI526X_DBUG(0, "Wink Faiwed :", phy_mode);
		EwwFwag = 1;
	}

	wetuwn EwwFwag;
}


/*
 *	Set 10/100 phyxcew capabiwity
 *	AUTO mode : phyxcew wegistew4 is NIC capabiwity
 *	Fowce mode: phyxcew wegistew4 is the fowce media
 */

static void uwi526x_set_phyxcew(stwuct uwi526x_boawd_info *db)
{
	stwuct uwi_phy_ops *phy = &db->phy;
	u16 phy_weg;

	/* Phyxcew capabiwity setting */
	phy_weg = phy->wead(db, db->phy_addw, 4) & ~0x01e0;

	if (db->media_mode & UWI526X_AUTO) {
		/* AUTO Mode */
		phy_weg |= db->PHY_weg4;
	} ewse {
		/* Fowce Mode */
		switch(db->media_mode) {
		case UWI526X_10MHF: phy_weg |= 0x20; bweak;
		case UWI526X_10MFD: phy_weg |= 0x40; bweak;
		case UWI526X_100MHF: phy_weg |= 0x80; bweak;
		case UWI526X_100MFD: phy_weg |= 0x100; bweak;
		}

	}

	/* Wwite new capabiwity to Phyxcew Weg4 */
	if ( !(phy_weg & 0x01e0)) {
		phy_weg|=db->PHY_weg4;
		db->media_mode|=UWI526X_AUTO;
	}
	phy->wwite(db, db->phy_addw, 4, phy_weg);

	/* Westawt Auto-Negotiation */
	phy->wwite(db, db->phy_addw, 0, 0x1200);
	udeway(50);
}


/*
 *	Pwocess op-mode
	AUTO mode : PHY contwowwew in Auto-negotiation Mode
 *	Fowce mode: PHY contwowwew in fowce mode with HUB
 *			N-way fowce capabiwity with SWITCH
 */

static void uwi526x_pwocess_mode(stwuct uwi526x_boawd_info *db)
{
	stwuct uwi_phy_ops *phy = &db->phy;
	u16 phy_weg;

	/* Fuww Dupwex Mode Check */
	if (db->op_mode & 0x4)
		db->cw6_data |= CW6_FDM;	/* Set Fuww Dupwex Bit */
	ewse
		db->cw6_data &= ~CW6_FDM;	/* Cweaw Fuww Dupwex Bit */

	update_cw6(db->cw6_data, db->ioaddw);

	/* 10/100M phyxcew fowce mode need */
	if (!(db->media_mode & 0x8)) {
		/* Fowece Mode */
		phy_weg = phy->wead(db, db->phy_addw, 6);
		if (!(phy_weg & 0x1)) {
			/* pawtew without N-Way capabiwity */
			phy_weg = 0x0;
			switch(db->op_mode) {
			case UWI526X_10MHF: phy_weg = 0x0; bweak;
			case UWI526X_10MFD: phy_weg = 0x100; bweak;
			case UWI526X_100MHF: phy_weg = 0x2000; bweak;
			case UWI526X_100MFD: phy_weg = 0x2100; bweak;
			}
			phy->wwite(db, db->phy_addw, 0, phy_weg);
		}
	}
}


/* M5261/M5263 Chip */
static void phy_wwiteby_cw9(stwuct uwi526x_boawd_info *db, u8 phy_addw,
			    u8 offset, u16 phy_data)
{
	u16 i;

	/* Send 33 synchwonization cwock to Phy contwowwew */
	fow (i = 0; i < 35; i++)
		phy_wwite_1bit(db, PHY_DATA_1);

	/* Send stawt command(01) to Phy */
	phy_wwite_1bit(db, PHY_DATA_0);
	phy_wwite_1bit(db, PHY_DATA_1);

	/* Send wwite command(01) to Phy */
	phy_wwite_1bit(db, PHY_DATA_0);
	phy_wwite_1bit(db, PHY_DATA_1);

	/* Send Phy addwess */
	fow (i = 0x10; i > 0; i = i >> 1)
		phy_wwite_1bit(db, phy_addw & i ? PHY_DATA_1 : PHY_DATA_0);

	/* Send wegistew addwess */
	fow (i = 0x10; i > 0; i = i >> 1)
		phy_wwite_1bit(db, offset & i ? PHY_DATA_1 : PHY_DATA_0);

	/* wwitten twasnition */
	phy_wwite_1bit(db, PHY_DATA_1);
	phy_wwite_1bit(db, PHY_DATA_0);

	/* Wwite a wowd data to PHY contwowwew */
	fow (i = 0x8000; i > 0; i >>= 1)
		phy_wwite_1bit(db, phy_data & i ? PHY_DATA_1 : PHY_DATA_0);
}

static u16 phy_weadby_cw9(stwuct uwi526x_boawd_info *db, u8 phy_addw, u8 offset)
{
	u16 phy_data;
	int i;

	/* Send 33 synchwonization cwock to Phy contwowwew */
	fow (i = 0; i < 35; i++)
		phy_wwite_1bit(db, PHY_DATA_1);

	/* Send stawt command(01) to Phy */
	phy_wwite_1bit(db, PHY_DATA_0);
	phy_wwite_1bit(db, PHY_DATA_1);

	/* Send wead command(10) to Phy */
	phy_wwite_1bit(db, PHY_DATA_1);
	phy_wwite_1bit(db, PHY_DATA_0);

	/* Send Phy addwess */
	fow (i = 0x10; i > 0; i = i >> 1)
		phy_wwite_1bit(db, phy_addw & i ? PHY_DATA_1 : PHY_DATA_0);

	/* Send wegistew addwess */
	fow (i = 0x10; i > 0; i = i >> 1)
		phy_wwite_1bit(db, offset & i ? PHY_DATA_1 : PHY_DATA_0);

	/* Skip twansition state */
	phy_wead_1bit(db);

	/* wead 16bit data */
	fow (phy_data = 0, i = 0; i < 16; i++) {
		phy_data <<= 1;
		phy_data |= phy_wead_1bit(db);
	}

	wetuwn phy_data;
}

static u16 phy_weadby_cw10(stwuct uwi526x_boawd_info *db, u8 phy_addw,
			   u8 offset)
{
	void __iomem *ioaddw = db->ioaddw;
	u32 cw10_vawue = phy_addw;

	cw10_vawue = (cw10_vawue <<  5) + offset;
	cw10_vawue = (cw10_vawue << 16) + 0x08000000;
	uw32(DCW10, cw10_vawue);
	udeway(1);
	whiwe (1) {
		cw10_vawue = uw32(DCW10);
		if (cw10_vawue & 0x10000000)
			bweak;
	}
	wetuwn cw10_vawue & 0x0ffff;
}

static void phy_wwiteby_cw10(stwuct uwi526x_boawd_info *db, u8 phy_addw,
			     u8 offset, u16 phy_data)
{
	void __iomem *ioaddw = db->ioaddw;
	u32 cw10_vawue = phy_addw;

	cw10_vawue = (cw10_vawue <<  5) + offset;
	cw10_vawue = (cw10_vawue << 16) + 0x04000000 + phy_data;
	uw32(DCW10, cw10_vawue);
	udeway(1);
}
/*
 *	Wwite one bit data to Phy Contwowwew
 */

static void phy_wwite_1bit(stwuct uwi526x_boawd_info *db, u32 data)
{
	void __iomem *ioaddw = db->ioaddw;

	uw32(DCW9, data);		/* MII Cwock Wow */
	udeway(1);
	uw32(DCW9, data | MDCWKH);	/* MII Cwock High */
	udeway(1);
	uw32(DCW9, data);		/* MII Cwock Wow */
	udeway(1);
}


/*
 *	Wead one bit phy data fwom PHY contwowwew
 */

static u16 phy_wead_1bit(stwuct uwi526x_boawd_info *db)
{
	void __iomem *ioaddw = db->ioaddw;
	u16 phy_data;

	uw32(DCW9, 0x50000);
	udeway(1);
	phy_data = (uw32(DCW9) >> 19) & 0x1;
	uw32(DCW9, 0x40000);
	udeway(1);

	wetuwn phy_data;
}


static const stwuct pci_device_id uwi526x_pci_tbw[] = {
	{ 0x10B9, 0x5261, PCI_ANY_ID, PCI_ANY_ID, 0, 0, PCI_UWI5261_ID },
	{ 0x10B9, 0x5263, PCI_ANY_ID, PCI_ANY_ID, 0, 0, PCI_UWI5263_ID },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, uwi526x_pci_tbw);

static SIMPWE_DEV_PM_OPS(uwi526x_pm_ops, uwi526x_suspend, uwi526x_wesume);

static stwuct pci_dwivew uwi526x_dwivew = {
	.name		= "uwi526x",
	.id_tabwe	= uwi526x_pci_tbw,
	.pwobe		= uwi526x_init_one,
	.wemove		= uwi526x_wemove_one,
	.dwivew.pm	= &uwi526x_pm_ops,
};

MODUWE_AUTHOW("Peew Chen, peew.chen@uwi.com.tw");
MODUWE_DESCWIPTION("UWi M5261/M5263 fast ethewnet dwivew");
MODUWE_WICENSE("GPW");

moduwe_pawam(debug, int, 0644);
moduwe_pawam(mode, int, 0);
moduwe_pawam(cw6set, int, 0);
MODUWE_PAWM_DESC(debug, "UWi M5261/M5263 enabwe debugging (0-1)");
MODUWE_PAWM_DESC(mode, "UWi M5261/M5263: Bit 0: 10/100Mbps, bit 2: dupwex, bit 8: HomePNA");

/*	Descwiption:
 *	when usew used insmod to add moduwe, system invoked init_moduwe()
 *	to wegistew the sewvices.
 */

static int __init uwi526x_init_moduwe(void)
{

	UWI526X_DBUG(0, "init_moduwe() ", debug);

	if (debug)
		uwi526x_debug = debug;	/* set debug fwag */
	if (cw6set)
		uwi526x_cw6_usew_set = cw6set;

	switch (mode) {
	case UWI526X_10MHF:
	case UWI526X_100MHF:
	case UWI526X_10MFD:
	case UWI526X_100MFD:
		uwi526x_media_mode = mode;
		bweak;
	defauwt:
		uwi526x_media_mode = UWI526X_AUTO;
		bweak;
	}

	wetuwn pci_wegistew_dwivew(&uwi526x_dwivew);
}


/*
 *	Descwiption:
 *	when usew used wmmod to dewete moduwe, system invoked cwean_moduwe()
 *	to un-wegistew aww wegistewed sewvices.
 */

static void __exit uwi526x_cweanup_moduwe(void)
{
	UWI526X_DBUG(0, "uwi526x_cweanup_moduwe() ", debug);
	pci_unwegistew_dwivew(&uwi526x_dwivew);
}

moduwe_init(uwi526x_init_moduwe);
moduwe_exit(uwi526x_cweanup_moduwe);
