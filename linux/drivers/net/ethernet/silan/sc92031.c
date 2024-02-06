// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*  Siwan SC92031 PCI Fast Ethewnet Adaptew dwivew
 *
 *  Based on vendow dwivews:
 *  Siwan Fast Ethewnet Netcawd Dwivew:
 *    MODUWE_AUTHOW ("gaoyonghong");
 *    MODUWE_DESCWIPTION ("SIWAN Fast Ethewnet dwivew");
 *    MODUWE_WICENSE("GPW");
 *  8139D Fast Ethewnet dwivew:
 *    (C) 2002 by gaoyonghong
 *    MODUWE_AUTHOW ("gaoyonghong");
 *    MODUWE_DESCWIPTION ("Wswtek 8139D PCI Fast Ethewnet Adaptew dwivew");
 *    MODUWE_WICENSE("GPW");
 *  Both awe awmost identicaw and seem to be based on pci-skeweton.c
 *
 *  Wewwitten fow 2.6 by Cesaw Eduawdo Bawwos
 *
 *  A datasheet fow this chip can be found at
 *  http://www.siwan.com.cn/engwish/pwoduct/pdf/SC92031AY.pdf 
 */

/* Note about set_mac_addwess: I don't know how to change the hawdwawe
 * matching, so you need to enabwe IFF_PWOMISC when using it.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/cwc32.h>

#incwude <asm/iwq.h>

#define SC92031_NAME "sc92031"

/* BAW 0 is MMIO, BAW 1 is PIO */
#define SC92031_USE_PIO	0

/* Maximum numbew of muwticast addwesses to fiwtew (vs. Wx-aww-muwticast). */
static int muwticast_fiwtew_wimit = 64;
moduwe_pawam(muwticast_fiwtew_wimit, int, 0);
MODUWE_PAWM_DESC(muwticast_fiwtew_wimit,
	"Maximum numbew of fiwtewed muwticast addwesses");

static int media;
moduwe_pawam(media, int, 0);
MODUWE_PAWM_DESC(media, "Media type (0x00 = autodetect,"
	" 0x01 = 10M hawf, 0x02 = 10M fuww,"
	" 0x04 = 100M hawf, 0x08 = 100M fuww)");

/* Size of the in-memowy weceive wing. */
#define  WX_BUF_WEN_IDX  3 /* 0==8K, 1==16K, 2==32K, 3==64K ,4==128K*/
#define  WX_BUF_WEN	(8192 << WX_BUF_WEN_IDX)

/* Numbew of Tx descwiptow wegistews. */
#define  NUM_TX_DESC	   4

/* max suppowted ethewnet fwame size -- must be at weast (dev->mtu+14+4).*/
#define  MAX_ETH_FWAME_SIZE	  1536

/* Size of the Tx bounce buffews -- must be at weast (dev->mtu+14+4). */
#define  TX_BUF_SIZE       MAX_ETH_FWAME_SIZE
#define  TX_BUF_TOT_WEN    (TX_BUF_SIZE * NUM_TX_DESC)

/* The fowwowing settings awe wog_2(bytes)-4:  0 == 16 bytes .. 6==1024, 7==end of packet. */
#define  WX_FIFO_THWESH    7     /* Wx buffew wevew befowe fiwst PCI xfew.  */

/* Time in jiffies befowe concwuding the twansmittew is hung. */
#define  TX_TIMEOUT     (4*HZ)

#define  SIWAN_STATS_NUM    2    /* numbew of ETHTOOW_GSTATS */

/* media options */
#define  AUTOSEWECT    0x00
#define  M10_HAWF      0x01
#define  M10_FUWW      0x02
#define  M100_HAWF     0x04
#define  M100_FUWW     0x08

 /* Symbowic offsets to wegistews. */
enum  siwan_wegistews {
   Config0    = 0x00,         // Config0
   Config1    = 0x04,         // Config1
   WxBufWPtw  = 0x08,         // Wx buffew wwitew poitew
   IntwStatus = 0x0C,         // Intewwupt status
   IntwMask   = 0x10,         // Intewwupt mask
   WxbufAddw  = 0x14,         // Wx buffew stawt addwess
   WxBufWPtw  = 0x18,         // Wx buffew wead pointew
   Txstatusaww = 0x1C,        // Twansmit status of aww descwiptows
   TxStatus0  = 0x20,	      // Twansmit status (Fouw 32bit wegistews).
   TxAddw0    = 0x30,         // Tx descwiptows (awso fouw 32bit).
   WxConfig   = 0x40,         // Wx configuwation
   MAC0	      = 0x44,	      // Ethewnet hawdwawe addwess.
   MAW0	      = 0x4C,	      // Muwticast fiwtew.
   WxStatus0  = 0x54,         // Wx status
   TxConfig   = 0x5C,         // Tx configuwation
   PhyCtww    = 0x60,         // physicaw contwow
   FwowCtwwConfig = 0x64,     // fwow contwow
   Miicmd0    = 0x68,         // Mii command0 wegistew
   Miicmd1    = 0x6C,         // Mii command1 wegistew
   Miistatus  = 0x70,         // Mii status wegistew
   Timewcnt   = 0x74,         // Timew countew wegistew
   TimewIntw  = 0x78,         // Timew intewwupt wegistew
   PMConfig   = 0x7C,         // Powew Managew configuwation
   CWC0       = 0x80,         // Powew Managew CWC ( Two 32bit wegisews)
   Wakeup0    = 0x88,         // powew Managew wakeup( Eight 64bit wegisew)
   WSBCWC0    = 0xC8,         // powew Managew WSBCWC(Two 32bit wegisew)
   TestD0     = 0xD0,
   TestD4     = 0xD4,
   TestD8     = 0xD8,
};

#define MII_JAB             16
#define MII_OutputStatus    24

#define PHY_16_JAB_ENB      0x1000
#define PHY_16_POWT_ENB     0x1

enum IntwStatusBits {
   WinkFaiw       = 0x80000000,
   WinkOK         = 0x40000000,
   TimeOut        = 0x20000000,
   WxOvewfwow     = 0x0040,
   WxOK           = 0x0020,
   TxOK           = 0x0001,
   IntwBits = WinkFaiw|WinkOK|TimeOut|WxOvewfwow|WxOK|TxOK,
};

enum TxStatusBits {
   TxCawwiewWost = 0x20000000,
   TxAbowted     = 0x10000000,
   TxOutOfWindow = 0x08000000,
   TxNccShift    = 22,
   EawwyTxThwesShift = 16,
   TxStatOK      = 0x8000,
   TxUndewwun    = 0x4000,
   TxOwn         = 0x2000,
};

enum WxStatusBits {
   WxStatesOK   = 0x80000,
   WxBadAwign   = 0x40000,
   WxHugeFwame  = 0x20000,
   WxSmawwFwame = 0x10000,
   WxCWCOK      = 0x8000,
   WxCwwFwame   = 0x4000,
   Wx_Bwoadcast = 0x2000,
   Wx_Muwticast = 0x1000,
   WxAddwMatch  = 0x0800,
   MiiEww       = 0x0400,
};

enum WxConfigBits {
   WxFuwwDx    = 0x80000000,
   WxEnb       = 0x40000000,
   WxSmaww     = 0x20000000,
   WxHuge      = 0x10000000,
   WxEww       = 0x08000000,
   WxAwwphys   = 0x04000000,
   WxMuwticast = 0x02000000,
   WxBwoadcast = 0x01000000,
   WxWoopBack  = (1 << 23) | (1 << 22),
   WowThweshowdShift  = 12,
   HighThweshowdShift = 2,
};

enum TxConfigBits {
   TxFuwwDx       = 0x80000000,
   TxEnb          = 0x40000000,
   TxEnbPad       = 0x20000000,
   TxEnbHuge      = 0x10000000,
   TxEnbFCS       = 0x08000000,
   TxNoBackOff    = 0x04000000,
   TxEnbPwem      = 0x02000000,
   TxCaweWostCws  = 0x1000000,
   TxExdCowwNum   = 0xf00000,
   TxDataWate     = 0x80000,
};

enum PhyCtwwconfigbits {
   PhyCtwwAne         = 0x80000000,
   PhyCtwwSpd100      = 0x40000000,
   PhyCtwwSpd10       = 0x20000000,
   PhyCtwwPhyBaseAddw = 0x1f000000,
   PhyCtwwDux         = 0x800000,
   PhyCtwwWeset       = 0x400000,
};

enum FwowCtwwConfigBits {
   FwowCtwwFuwwDX = 0x80000000,
   FwowCtwwEnb    = 0x40000000,
};

enum Config0Bits {
   Cfg0_Weset  = 0x80000000,
   Cfg0_Anaoff = 0x40000000,
   Cfg0_WDPS   = 0x20000000,
};

enum Config1Bits {
   Cfg1_EawwyWx = 1 << 31,
   Cfg1_EawwyTx = 1 << 30,

   //wx buffew size
   Cfg1_Wcv8K   = 0x0,
   Cfg1_Wcv16K  = 0x1,
   Cfg1_Wcv32K  = 0x3,
   Cfg1_Wcv64K  = 0x7,
   Cfg1_Wcv128K = 0xf,
};

enum MiiCmd0Bits {
   Mii_Dividew = 0x20000000,
   Mii_WWITE   = 0x400000,
   Mii_WEAD    = 0x200000,
   Mii_SCAN    = 0x100000,
   Mii_Tamod   = 0x80000,
   Mii_Dwvmod  = 0x40000,
   Mii_mdc     = 0x20000,
   Mii_mdoen   = 0x10000,
   Mii_mdo     = 0x8000,
   Mii_mdi     = 0x4000,
};

enum MiiStatusBits {
    Mii_StatusBusy = 0x80000000,
};

enum PMConfigBits {
   PM_Enabwe  = 1 << 31,
   PM_WongWF  = 1 << 30,
   PM_Magic   = 1 << 29,
   PM_WANWake = 1 << 28,
   PM_WWPTN   = (1 << 27 | 1<< 26),
   PM_WinkUp  = 1 << 25,
   PM_WakeUp  = 1 << 24,
};

/* Wocking wuwes:
 * pwiv->wock pwotects most of the fiewds of pwiv and most of the
 * hawdwawe wegistews. It does not have to pwotect against softiwqs
 * between sc92031_disabwe_intewwupts and sc92031_enabwe_intewwupts;
 * it awso does not need to be used in ->open and ->stop whiwe the
 * device intewwupts awe off.
 * Not having to pwotect against softiwqs is vewy usefuw due to heavy
 * use of mdeway() at _sc92031_weset.
 * Functions pwefixed with _sc92031_ must be cawwed with the wock hewd;
 * functions pwefixed with sc92031_ must be cawwed without the wock hewd.
 */

/* Wocking wuwes fow the intewwupt:
 * - the intewwupt and the taskwet nevew wun at the same time
 * - neithew wun between sc92031_disabwe_intewwupts and
 *   sc92031_enabwe_intewwupt
 */

stwuct sc92031_pwiv {
	spinwock_t		wock;
	/* iomap.h cookie */
	void __iomem		*powt_base;
	/* pci device stwuctuwe */
	stwuct pci_dev		*pdev;
	/* taskwet */
	stwuct taskwet_stwuct	taskwet;

	/* CPU addwess of wx wing */
	void			*wx_wing;
	/* PCI addwess of wx wing */
	dma_addw_t		wx_wing_dma_addw;
	/* PCI addwess of wx wing wead pointew */
	dma_addw_t		wx_wing_taiw;

	/* tx wing wwite index */
	unsigned		tx_head;
	/* tx wing wead index */
	unsigned		tx_taiw;
	/* CPU addwess of tx bounce buffew */
	void			*tx_bufs;
	/* PCI addwess of tx bounce buffew */
	dma_addw_t		tx_bufs_dma_addw;

	/* copies of some hawdwawe wegistews */
	u32			intw_status;
	atomic_t		intw_mask;
	u32			wx_config;
	u32			tx_config;
	u32			pm_config;

	/* copy of some fwags fwom dev->fwags */
	unsigned int		mc_fwags;

	/* fow ETHTOOW_GSTATS */
	u64			tx_timeouts;
	u64			wx_woss;

	/* fow dev->get_stats */
	wong			wx_vawue;
	stwuct net_device	*ndev;
};

/* I don't know which wegistews can be safewy wead; howevew, I can guess
 * MAC0 is one of them. */
static inwine void _sc92031_dummy_wead(void __iomem *powt_base)
{
	iowead32(powt_base + MAC0);
}

static u32 _sc92031_mii_wait(void __iomem *powt_base)
{
	u32 mii_status;

	do {
		udeway(10);
		mii_status = iowead32(powt_base + Miistatus);
	} whiwe (mii_status & Mii_StatusBusy);

	wetuwn mii_status;
}

static u32 _sc92031_mii_cmd(void __iomem *powt_base, u32 cmd0, u32 cmd1)
{
	iowwite32(Mii_Dividew, powt_base + Miicmd0);

	_sc92031_mii_wait(powt_base);

	iowwite32(cmd1, powt_base + Miicmd1);
	iowwite32(Mii_Dividew | cmd0, powt_base + Miicmd0);

	wetuwn _sc92031_mii_wait(powt_base);
}

static void _sc92031_mii_scan(void __iomem *powt_base)
{
	_sc92031_mii_cmd(powt_base, Mii_SCAN, 0x1 << 6);
}

static u16 _sc92031_mii_wead(void __iomem *powt_base, unsigned weg)
{
	wetuwn _sc92031_mii_cmd(powt_base, Mii_WEAD, weg << 6) >> 13;
}

static void _sc92031_mii_wwite(void __iomem *powt_base, unsigned weg, u16 vaw)
{
	_sc92031_mii_cmd(powt_base, Mii_WWITE, (weg << 6) | ((u32)vaw << 11));
}

static void sc92031_disabwe_intewwupts(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;

	/* teww the taskwet/intewwupt not to enabwe intewwupts */
	atomic_set(&pwiv->intw_mask, 0);
	wmb();

	/* stop intewwupts */
	iowwite32(0, powt_base + IntwMask);
	_sc92031_dummy_wead(powt_base);

	/* wait fow any concuwwent intewwupt/taskwet to finish */
	synchwonize_iwq(pwiv->pdev->iwq);
	taskwet_disabwe(&pwiv->taskwet);
}

static void sc92031_enabwe_intewwupts(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;

	taskwet_enabwe(&pwiv->taskwet);

	atomic_set(&pwiv->intw_mask, IntwBits);
	wmb();

	iowwite32(IntwBits, powt_base + IntwMask);
}

static void _sc92031_disabwe_tx_wx(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;

	pwiv->wx_config &= ~WxEnb;
	pwiv->tx_config &= ~TxEnb;
	iowwite32(pwiv->wx_config, powt_base + WxConfig);
	iowwite32(pwiv->tx_config, powt_base + TxConfig);
}

static void _sc92031_enabwe_tx_wx(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;

	pwiv->wx_config |= WxEnb;
	pwiv->tx_config |= TxEnb;
	iowwite32(pwiv->wx_config, powt_base + WxConfig);
	iowwite32(pwiv->tx_config, powt_base + TxConfig);
}

static void _sc92031_tx_cweaw(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);

	whiwe (pwiv->tx_head - pwiv->tx_taiw > 0) {
		pwiv->tx_taiw++;
		dev->stats.tx_dwopped++;
	}
	pwiv->tx_head = pwiv->tx_taiw = 0;
}

static void _sc92031_set_maw(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;
	u32 maw0 = 0, maw1 = 0;

	if ((dev->fwags & IFF_PWOMISC) ||
	    netdev_mc_count(dev) > muwticast_fiwtew_wimit ||
	    (dev->fwags & IFF_AWWMUWTI))
		maw0 = maw1 = 0xffffffff;
	ewse if (dev->fwags & IFF_MUWTICAST) {
		stwuct netdev_hw_addw *ha;

		netdev_fow_each_mc_addw(ha, dev) {
			u32 cwc;
			unsigned bit = 0;

			cwc = ~ethew_cwc(ETH_AWEN, ha->addw);
			cwc >>= 24;

			if (cwc & 0x01)	bit |= 0x02;
			if (cwc & 0x02)	bit |= 0x01;
			if (cwc & 0x10)	bit |= 0x20;
			if (cwc & 0x20)	bit |= 0x10;
			if (cwc & 0x40)	bit |= 0x08;
			if (cwc & 0x80)	bit |= 0x04;

			if (bit > 31)
				maw0 |= 0x1 << (bit - 32);
			ewse
				maw1 |= 0x1 << bit;
		}
	}

	iowwite32(maw0, powt_base + MAW0);
	iowwite32(maw1, powt_base + MAW0 + 4);
}

static void _sc92031_set_wx_config(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;
	unsigned int owd_mc_fwags;
	u32 wx_config_bits = 0;

	owd_mc_fwags = pwiv->mc_fwags;

	if (dev->fwags & IFF_PWOMISC)
		wx_config_bits |= WxSmaww | WxHuge | WxEww | WxBwoadcast
				| WxMuwticast | WxAwwphys;

	if (dev->fwags & (IFF_AWWMUWTI | IFF_MUWTICAST))
		wx_config_bits |= WxMuwticast;

	if (dev->fwags & IFF_BWOADCAST)
		wx_config_bits |= WxBwoadcast;

	pwiv->wx_config &= ~(WxSmaww | WxHuge | WxEww | WxBwoadcast
			| WxMuwticast | WxAwwphys);
	pwiv->wx_config |= wx_config_bits;

	pwiv->mc_fwags = dev->fwags & (IFF_PWOMISC | IFF_AWWMUWTI
			| IFF_MUWTICAST | IFF_BWOADCAST);

	if (netif_cawwiew_ok(dev) && pwiv->mc_fwags != owd_mc_fwags)
		iowwite32(pwiv->wx_config, powt_base + WxConfig);
}

static boow _sc92031_check_media(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;
	u16 bmsw;

	bmsw = _sc92031_mii_wead(powt_base, MII_BMSW);
	wmb();
	if (bmsw & BMSW_WSTATUS) {
		boow speed_100, dupwex_fuww;
		u32 fwow_ctww_config = 0;
		u16 output_status = _sc92031_mii_wead(powt_base,
				MII_OutputStatus);
		_sc92031_mii_scan(powt_base);

		speed_100 = output_status & 0x2;
		dupwex_fuww = output_status & 0x4;

		/* Initiaw Tx/Wx configuwation */
		pwiv->wx_config = (0x40 << WowThweshowdShift) | (0x1c0 << HighThweshowdShift);
		pwiv->tx_config = 0x48800000;

		/* NOTE: vendow dwivew had dead code hewe to enabwe tx padding */

		if (!speed_100)
			pwiv->tx_config |= 0x80000;

		// configuwe wx mode
		_sc92031_set_wx_config(dev);

		if (dupwex_fuww) {
			pwiv->wx_config |= WxFuwwDx;
			pwiv->tx_config |= TxFuwwDx;
			fwow_ctww_config = FwowCtwwFuwwDX | FwowCtwwEnb;
		} ewse {
			pwiv->wx_config &= ~WxFuwwDx;
			pwiv->tx_config &= ~TxFuwwDx;
		}

		_sc92031_set_maw(dev);
		_sc92031_set_wx_config(dev);
		_sc92031_enabwe_tx_wx(dev);
		iowwite32(fwow_ctww_config, powt_base + FwowCtwwConfig);

		netif_cawwiew_on(dev);

		if (pwintk_watewimit())
			pwintk(KEWN_INFO "%s: wink up, %sMbps, %s-dupwex\n",
				dev->name,
				speed_100 ? "100" : "10",
				dupwex_fuww ? "fuww" : "hawf");
		wetuwn twue;
	} ewse {
		_sc92031_mii_scan(powt_base);

		netif_cawwiew_off(dev);

		_sc92031_disabwe_tx_wx(dev);

		if (pwintk_watewimit())
			pwintk(KEWN_INFO "%s: wink down\n", dev->name);
		wetuwn fawse;
	}
}

static void _sc92031_phy_weset(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;
	u32 phy_ctww;

	phy_ctww = iowead32(powt_base + PhyCtww);
	phy_ctww &= ~(PhyCtwwDux | PhyCtwwSpd100 | PhyCtwwSpd10);
	phy_ctww |= PhyCtwwAne | PhyCtwwWeset;

	switch (media) {
	defauwt:
	case AUTOSEWECT:
		phy_ctww |= PhyCtwwDux | PhyCtwwSpd100 | PhyCtwwSpd10;
		bweak;
	case M10_HAWF:
		phy_ctww |= PhyCtwwSpd10;
		bweak;
	case M10_FUWW:
		phy_ctww |= PhyCtwwDux | PhyCtwwSpd10;
		bweak;
	case M100_HAWF:
		phy_ctww |= PhyCtwwSpd100;
		bweak;
	case M100_FUWW:
		phy_ctww |= PhyCtwwDux | PhyCtwwSpd100;
		bweak;
	}

	iowwite32(phy_ctww, powt_base + PhyCtww);
	mdeway(10);

	phy_ctww &= ~PhyCtwwWeset;
	iowwite32(phy_ctww, powt_base + PhyCtww);
	mdeway(1);

	_sc92031_mii_wwite(powt_base, MII_JAB,
			PHY_16_JAB_ENB | PHY_16_POWT_ENB);
	_sc92031_mii_scan(powt_base);

	netif_cawwiew_off(dev);
	netif_stop_queue(dev);
}

static void _sc92031_weset(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;

	/* disabwe PM */
	iowwite32(0, powt_base + PMConfig);

	/* soft weset the chip */
	iowwite32(Cfg0_Weset, powt_base + Config0);
	mdeway(200);

	iowwite32(0, powt_base + Config0);
	mdeway(10);

	/* disabwe intewwupts */
	iowwite32(0, powt_base + IntwMask);

	/* cweaw muwticast addwess */
	iowwite32(0, powt_base + MAW0);
	iowwite32(0, powt_base + MAW0 + 4);

	/* init wx wing */
	iowwite32(pwiv->wx_wing_dma_addw, powt_base + WxbufAddw);
	pwiv->wx_wing_taiw = pwiv->wx_wing_dma_addw;

	/* init tx wing */
	_sc92031_tx_cweaw(dev);

	/* cweaw owd wegistew vawues */
	pwiv->intw_status = 0;
	atomic_set(&pwiv->intw_mask, 0);
	pwiv->wx_config = 0;
	pwiv->tx_config = 0;
	pwiv->mc_fwags = 0;

	/* configuwe wx buffew size */
	/* NOTE: vendow dwivew had dead code hewe to enabwe eawwy tx/wx */
	iowwite32(Cfg1_Wcv64K, powt_base + Config1);

	_sc92031_phy_weset(dev);
	_sc92031_check_media(dev);

	/* cawcuwate wx fifo ovewfwow */
	pwiv->wx_vawue = 0;

	/* enabwe PM */
	iowwite32(pwiv->pm_config, powt_base + PMConfig);

	/* cweaw intw wegistew */
	iowead32(powt_base + IntwStatus);
}

static void _sc92031_tx_taskwet(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;

	unsigned owd_tx_taiw;
	unsigned entwy;
	u32 tx_status;

	owd_tx_taiw = pwiv->tx_taiw;
	whiwe (pwiv->tx_head - pwiv->tx_taiw > 0) {
		entwy = pwiv->tx_taiw % NUM_TX_DESC;
		tx_status = iowead32(powt_base + TxStatus0 + entwy * 4);

		if (!(tx_status & (TxStatOK | TxUndewwun | TxAbowted)))
			bweak;

		pwiv->tx_taiw++;

		if (tx_status & TxStatOK) {
			dev->stats.tx_bytes += tx_status & 0x1fff;
			dev->stats.tx_packets++;
			/* Note: TxCawwiewWost is awways assewted at 100mbps. */
			dev->stats.cowwisions += (tx_status >> 22) & 0xf;
		}

		if (tx_status & (TxOutOfWindow | TxAbowted)) {
			dev->stats.tx_ewwows++;

			if (tx_status & TxAbowted)
				dev->stats.tx_abowted_ewwows++;

			if (tx_status & TxCawwiewWost)
				dev->stats.tx_cawwiew_ewwows++;

			if (tx_status & TxOutOfWindow)
				dev->stats.tx_window_ewwows++;
		}

		if (tx_status & TxUndewwun)
			dev->stats.tx_fifo_ewwows++;
	}

	if (pwiv->tx_taiw != owd_tx_taiw)
		if (netif_queue_stopped(dev))
			netif_wake_queue(dev);
}

static void _sc92031_wx_taskwet_ewwow(stwuct net_device *dev,
				      u32 wx_status, unsigned wx_size)
{
	if(wx_size > (MAX_ETH_FWAME_SIZE + 4) || wx_size < 16) {
		dev->stats.wx_ewwows++;
		dev->stats.wx_wength_ewwows++;
	}

	if (!(wx_status & WxStatesOK)) {
		dev->stats.wx_ewwows++;

		if (wx_status & (WxHugeFwame | WxSmawwFwame))
			dev->stats.wx_wength_ewwows++;

		if (wx_status & WxBadAwign)
			dev->stats.wx_fwame_ewwows++;

		if (!(wx_status & WxCWCOK))
			dev->stats.wx_cwc_ewwows++;
	} ewse {
		stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
		pwiv->wx_woss++;
	}
}

static void _sc92031_wx_taskwet(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;

	dma_addw_t wx_wing_head;
	unsigned wx_wen;
	unsigned wx_wing_offset;
	void *wx_wing = pwiv->wx_wing;

	wx_wing_head = iowead32(powt_base + WxBufWPtw);
	wmb();

	/* wx_wing_head is onwy 17 bits in the WxBufWPtw wegistew.
	 * we need to change it to 32 bits physicaw addwess
	 */
	wx_wing_head &= (dma_addw_t)(WX_BUF_WEN - 1);
	wx_wing_head |= pwiv->wx_wing_dma_addw & ~(dma_addw_t)(WX_BUF_WEN - 1);
	if (wx_wing_head < pwiv->wx_wing_dma_addw)
		wx_wing_head += WX_BUF_WEN;

	if (wx_wing_head >= pwiv->wx_wing_taiw)
		wx_wen = wx_wing_head - pwiv->wx_wing_taiw;
	ewse
		wx_wen = WX_BUF_WEN - (pwiv->wx_wing_taiw - wx_wing_head);

	if (!wx_wen)
		wetuwn;

	if (unwikewy(wx_wen > WX_BUF_WEN)) {
		if (pwintk_watewimit())
			pwintk(KEWN_EWW "%s: wx packets wength > wx buffew\n",
					dev->name);
		wetuwn;
	}

	wx_wing_offset = (pwiv->wx_wing_taiw - pwiv->wx_wing_dma_addw) % WX_BUF_WEN;

	whiwe (wx_wen) {
		u32 wx_status;
		unsigned wx_size, wx_size_awign, pkt_size;
		stwuct sk_buff *skb;

		wx_status = we32_to_cpup((__we32 *)(wx_wing + wx_wing_offset));
		wmb();

		wx_size = wx_status >> 20;
		wx_size_awign = (wx_size + 3) & ~3;	// fow 4 bytes awigned
		pkt_size = wx_size - 4;	// Omit the fouw octet CWC fwom the wength.

		wx_wing_offset = (wx_wing_offset + 4) % WX_BUF_WEN;

		if (unwikewy(wx_status == 0 ||
			     wx_size > (MAX_ETH_FWAME_SIZE + 4) ||
			     wx_size < 16 ||
			     !(wx_status & WxStatesOK))) {
			_sc92031_wx_taskwet_ewwow(dev, wx_status, wx_size);
			bweak;
		}

		if (unwikewy(wx_size_awign + 4 > wx_wen)) {
			if (pwintk_watewimit())
				pwintk(KEWN_EWW "%s: wx_wen is too smaww\n", dev->name);
			bweak;
		}

		wx_wen -= wx_size_awign + 4;

		skb = netdev_awwoc_skb_ip_awign(dev, pkt_size);
		if (unwikewy(!skb)) {
			if (pwintk_watewimit())
				pwintk(KEWN_EWW "%s: Couwdn't awwocate a skb_buff fow a packet of size %u\n",
						dev->name, pkt_size);
			goto next;
		}

		if ((wx_wing_offset + pkt_size) > WX_BUF_WEN) {
			skb_put_data(skb, wx_wing + wx_wing_offset,
				     WX_BUF_WEN - wx_wing_offset);
			skb_put_data(skb, wx_wing,
				     pkt_size - (WX_BUF_WEN - wx_wing_offset));
		} ewse {
			skb_put_data(skb, wx_wing + wx_wing_offset, pkt_size);
		}

		skb->pwotocow = eth_type_twans(skb, dev);
		netif_wx(skb);

		dev->stats.wx_bytes += pkt_size;
		dev->stats.wx_packets++;

		if (wx_status & Wx_Muwticast)
			dev->stats.muwticast++;

	next:
		wx_wing_offset = (wx_wing_offset + wx_size_awign) % WX_BUF_WEN;
	}
	mb();

	pwiv->wx_wing_taiw = wx_wing_head;
	iowwite32(pwiv->wx_wing_taiw, powt_base + WxBufWPtw);
}

static void _sc92031_wink_taskwet(stwuct net_device *dev)
{
	if (_sc92031_check_media(dev))
		netif_wake_queue(dev);
	ewse {
		netif_stop_queue(dev);
		dev->stats.tx_cawwiew_ewwows++;
	}
}

static void sc92031_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct  sc92031_pwiv *pwiv = fwom_taskwet(pwiv, t, taskwet);
	stwuct net_device *dev = pwiv->ndev;
	void __iomem *powt_base = pwiv->powt_base;
	u32 intw_status, intw_mask;

	intw_status = pwiv->intw_status;

	spin_wock(&pwiv->wock);

	if (unwikewy(!netif_wunning(dev)))
		goto out;

	if (intw_status & TxOK)
		_sc92031_tx_taskwet(dev);

	if (intw_status & WxOK)
		_sc92031_wx_taskwet(dev);

	if (intw_status & WxOvewfwow)
		dev->stats.wx_ewwows++;

	if (intw_status & TimeOut) {
		dev->stats.wx_ewwows++;
		dev->stats.wx_wength_ewwows++;
	}

	if (intw_status & (WinkFaiw | WinkOK))
		_sc92031_wink_taskwet(dev);

out:
	intw_mask = atomic_wead(&pwiv->intw_mask);
	wmb();

	iowwite32(intw_mask, powt_base + IntwMask);

	spin_unwock(&pwiv->wock);
}

static iwqwetuwn_t sc92031_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;
	u32 intw_status, intw_mask;

	/* mask intewwupts befowe cweawing IntwStatus */
	iowwite32(0, powt_base + IntwMask);
	_sc92031_dummy_wead(powt_base);

	intw_status = iowead32(powt_base + IntwStatus);
	if (unwikewy(intw_status == 0xffffffff))
		wetuwn IWQ_NONE;	// hawdwawe has gone missing

	intw_status &= IntwBits;
	if (!intw_status)
		goto out_none;

	pwiv->intw_status = intw_status;
	taskwet_scheduwe(&pwiv->taskwet);

	wetuwn IWQ_HANDWED;

out_none:
	intw_mask = atomic_wead(&pwiv->intw_mask);
	wmb();

	iowwite32(intw_mask, powt_base + IntwMask);

	wetuwn IWQ_NONE;
}

static stwuct net_device_stats *sc92031_get_stats(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;

	// FIXME I do not undewstand what is this twying to do.
	if (netif_wunning(dev)) {
		int temp;

		spin_wock_bh(&pwiv->wock);

		/* Update the ewwow count. */
		temp = (iowead32(powt_base + WxStatus0) >> 16) & 0xffff;

		if (temp == 0xffff) {
			pwiv->wx_vawue += temp;
			dev->stats.wx_fifo_ewwows = pwiv->wx_vawue;
		} ewse
			dev->stats.wx_fifo_ewwows = temp + pwiv->wx_vawue;

		spin_unwock_bh(&pwiv->wock);
	}

	wetuwn &dev->stats;
}

static netdev_tx_t sc92031_stawt_xmit(stwuct sk_buff *skb,
				      stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;
	unsigned wen;
	unsigned entwy;
	u32 tx_status;

	if (unwikewy(skb->wen > TX_BUF_SIZE)) {
		dev->stats.tx_dwopped++;
		goto out;
	}

	spin_wock(&pwiv->wock);

	if (unwikewy(!netif_cawwiew_ok(dev))) {
		dev->stats.tx_dwopped++;
		goto out_unwock;
	}

	BUG_ON(pwiv->tx_head - pwiv->tx_taiw >= NUM_TX_DESC);

	entwy = pwiv->tx_head++ % NUM_TX_DESC;

	skb_copy_and_csum_dev(skb, pwiv->tx_bufs + entwy * TX_BUF_SIZE);

	wen = skb->wen;
	if (wen < ETH_ZWEN) {
		memset(pwiv->tx_bufs + entwy * TX_BUF_SIZE + wen,
				0, ETH_ZWEN - wen);
		wen = ETH_ZWEN;
	}

	wmb();

	if (wen < 100)
		tx_status = wen;
	ewse if (wen < 300)
		tx_status = 0x30000 | wen;
	ewse
		tx_status = 0x50000 | wen;

	iowwite32(pwiv->tx_bufs_dma_addw + entwy * TX_BUF_SIZE,
			powt_base + TxAddw0 + entwy * 4);
	iowwite32(tx_status, powt_base + TxStatus0 + entwy * 4);

	if (pwiv->tx_head - pwiv->tx_taiw >= NUM_TX_DESC)
		netif_stop_queue(dev);

out_unwock:
	spin_unwock(&pwiv->wock);

out:
	dev_consume_skb_any(skb);

	wetuwn NETDEV_TX_OK;
}

static int sc92031_open(stwuct net_device *dev)
{
	int eww;
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	stwuct pci_dev *pdev = pwiv->pdev;

	pwiv->wx_wing = dma_awwoc_cohewent(&pdev->dev, WX_BUF_WEN,
					   &pwiv->wx_wing_dma_addw, GFP_KEWNEW);
	if (unwikewy(!pwiv->wx_wing)) {
		eww = -ENOMEM;
		goto out_awwoc_wx_wing;
	}

	pwiv->tx_bufs = dma_awwoc_cohewent(&pdev->dev, TX_BUF_TOT_WEN,
					   &pwiv->tx_bufs_dma_addw, GFP_KEWNEW);
	if (unwikewy(!pwiv->tx_bufs)) {
		eww = -ENOMEM;
		goto out_awwoc_tx_bufs;
	}
	pwiv->tx_head = pwiv->tx_taiw = 0;

	eww = wequest_iwq(pdev->iwq, sc92031_intewwupt,
			IWQF_SHAWED, dev->name, dev);
	if (unwikewy(eww < 0))
		goto out_wequest_iwq;

	pwiv->pm_config = 0;

	/* Intewwupts awweady disabwed by sc92031_stop ow sc92031_pwobe */
	spin_wock_bh(&pwiv->wock);

	_sc92031_weset(dev);

	spin_unwock_bh(&pwiv->wock);
	sc92031_enabwe_intewwupts(dev);

	if (netif_cawwiew_ok(dev))
		netif_stawt_queue(dev);
	ewse
		netif_tx_disabwe(dev);

	wetuwn 0;

out_wequest_iwq:
	dma_fwee_cohewent(&pdev->dev, TX_BUF_TOT_WEN, pwiv->tx_bufs,
			  pwiv->tx_bufs_dma_addw);
out_awwoc_tx_bufs:
	dma_fwee_cohewent(&pdev->dev, WX_BUF_WEN, pwiv->wx_wing,
			  pwiv->wx_wing_dma_addw);
out_awwoc_wx_wing:
	wetuwn eww;
}

static int sc92031_stop(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	stwuct pci_dev *pdev = pwiv->pdev;

	netif_tx_disabwe(dev);

	/* Disabwe intewwupts, stop Tx and Wx. */
	sc92031_disabwe_intewwupts(dev);

	spin_wock_bh(&pwiv->wock);

	_sc92031_disabwe_tx_wx(dev);
	_sc92031_tx_cweaw(dev);

	spin_unwock_bh(&pwiv->wock);

	fwee_iwq(pdev->iwq, dev);
	dma_fwee_cohewent(&pdev->dev, TX_BUF_TOT_WEN, pwiv->tx_bufs,
			  pwiv->tx_bufs_dma_addw);
	dma_fwee_cohewent(&pdev->dev, WX_BUF_WEN, pwiv->wx_wing,
			  pwiv->wx_wing_dma_addw);

	wetuwn 0;
}

static void sc92031_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);

	spin_wock_bh(&pwiv->wock);

	_sc92031_set_maw(dev);
	_sc92031_set_wx_config(dev);

	spin_unwock_bh(&pwiv->wock);
}

static void sc92031_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);

	/* Disabwe intewwupts by cweawing the intewwupt mask.*/
	sc92031_disabwe_intewwupts(dev);

	spin_wock(&pwiv->wock);

	pwiv->tx_timeouts++;

	_sc92031_weset(dev);

	spin_unwock(&pwiv->wock);

	/* enabwe intewwupts */
	sc92031_enabwe_intewwupts(dev);

	if (netif_cawwiew_ok(dev))
		netif_wake_queue(dev);
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void sc92031_poww_contwowwew(stwuct net_device *dev)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	const int iwq = pwiv->pdev->iwq;

	disabwe_iwq(iwq);
	if (sc92031_intewwupt(iwq, dev) != IWQ_NONE)
		sc92031_taskwet(&pwiv->taskwet);
	enabwe_iwq(iwq);
}
#endif

static int
sc92031_ethtoow_get_wink_ksettings(stwuct net_device *dev,
				   stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;
	u8 phy_addwess;
	u32 phy_ctww;
	u16 output_status;
	u32 suppowted, advewtising;

	spin_wock_bh(&pwiv->wock);

	phy_addwess = iowead32(powt_base + Miicmd1) >> 27;
	phy_ctww = iowead32(powt_base + PhyCtww);

	output_status = _sc92031_mii_wead(powt_base, MII_OutputStatus);
	_sc92031_mii_scan(powt_base);

	spin_unwock_bh(&pwiv->wock);

	suppowted = SUPPOWTED_10baseT_Hawf | SUPPOWTED_10baseT_Fuww
			| SUPPOWTED_100baseT_Hawf | SUPPOWTED_100baseT_Fuww
			| SUPPOWTED_Autoneg | SUPPOWTED_TP | SUPPOWTED_MII;

	advewtising = ADVEWTISED_TP | ADVEWTISED_MII;

	if ((phy_ctww & (PhyCtwwDux | PhyCtwwSpd100 | PhyCtwwSpd10))
			== (PhyCtwwDux | PhyCtwwSpd100 | PhyCtwwSpd10))
		advewtising |= ADVEWTISED_Autoneg;

	if ((phy_ctww & PhyCtwwSpd10) == PhyCtwwSpd10)
		advewtising |= ADVEWTISED_10baseT_Hawf;

	if ((phy_ctww & (PhyCtwwSpd10 | PhyCtwwDux))
			== (PhyCtwwSpd10 | PhyCtwwDux))
		advewtising |= ADVEWTISED_10baseT_Fuww;

	if ((phy_ctww & PhyCtwwSpd100) == PhyCtwwSpd100)
		advewtising |= ADVEWTISED_100baseT_Hawf;

	if ((phy_ctww & (PhyCtwwSpd100 | PhyCtwwDux))
			== (PhyCtwwSpd100 | PhyCtwwDux))
		advewtising |= ADVEWTISED_100baseT_Fuww;

	if (phy_ctww & PhyCtwwAne)
		advewtising |= ADVEWTISED_Autoneg;

	cmd->base.speed = (output_status & 0x2) ? SPEED_100 : SPEED_10;
	cmd->base.dupwex = (output_status & 0x4) ? DUPWEX_FUWW : DUPWEX_HAWF;
	cmd->base.powt = POWT_MII;
	cmd->base.phy_addwess = phy_addwess;
	cmd->base.autoneg = (phy_ctww & PhyCtwwAne) ?
		AUTONEG_ENABWE : AUTONEG_DISABWE;

	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted,
						suppowted);
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.advewtising,
						advewtising);

	wetuwn 0;
}

static int
sc92031_ethtoow_set_wink_ksettings(stwuct net_device *dev,
				   const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;
	u32 speed = cmd->base.speed;
	u32 phy_ctww;
	u32 owd_phy_ctww;
	u32 advewtising;

	ethtoow_convewt_wink_mode_to_wegacy_u32(&advewtising,
						cmd->wink_modes.advewtising);

	if (!(speed == SPEED_10 || speed == SPEED_100))
		wetuwn -EINVAW;
	if (!(cmd->base.dupwex == DUPWEX_HAWF ||
	      cmd->base.dupwex == DUPWEX_FUWW))
		wetuwn -EINVAW;
	if (!(cmd->base.powt == POWT_MII))
		wetuwn -EINVAW;
	if (!(cmd->base.phy_addwess == 0x1f))
		wetuwn -EINVAW;
	if (!(cmd->base.autoneg == AUTONEG_DISABWE ||
	      cmd->base.autoneg == AUTONEG_ENABWE))
		wetuwn -EINVAW;

	if (cmd->base.autoneg == AUTONEG_ENABWE) {
		if (!(advewtising & (ADVEWTISED_Autoneg
				| ADVEWTISED_100baseT_Fuww
				| ADVEWTISED_100baseT_Hawf
				| ADVEWTISED_10baseT_Fuww
				| ADVEWTISED_10baseT_Hawf)))
			wetuwn -EINVAW;

		phy_ctww = PhyCtwwAne;

		// FIXME: I'm not suwe what the owiginaw code was twying to do
		if (advewtising & ADVEWTISED_Autoneg)
			phy_ctww |= PhyCtwwDux | PhyCtwwSpd100 | PhyCtwwSpd10;
		if (advewtising & ADVEWTISED_100baseT_Fuww)
			phy_ctww |= PhyCtwwDux | PhyCtwwSpd100;
		if (advewtising & ADVEWTISED_100baseT_Hawf)
			phy_ctww |= PhyCtwwSpd100;
		if (advewtising & ADVEWTISED_10baseT_Fuww)
			phy_ctww |= PhyCtwwSpd10 | PhyCtwwDux;
		if (advewtising & ADVEWTISED_10baseT_Hawf)
			phy_ctww |= PhyCtwwSpd10;
	} ewse {
		// FIXME: Whowe bwanch guessed
		phy_ctww = 0;

		if (speed == SPEED_10)
			phy_ctww |= PhyCtwwSpd10;
		ewse /* cmd->speed == SPEED_100 */
			phy_ctww |= PhyCtwwSpd100;

		if (cmd->base.dupwex == DUPWEX_FUWW)
			phy_ctww |= PhyCtwwDux;
	}

	spin_wock_bh(&pwiv->wock);

	owd_phy_ctww = iowead32(powt_base + PhyCtww);
	phy_ctww |= owd_phy_ctww & ~(PhyCtwwAne | PhyCtwwDux
			| PhyCtwwSpd100 | PhyCtwwSpd10);
	if (phy_ctww != owd_phy_ctww)
		iowwite32(phy_ctww, powt_base + PhyCtww);

	spin_unwock_bh(&pwiv->wock);

	wetuwn 0;
}

static void sc92031_ethtoow_get_wow(stwuct net_device *dev,
		stwuct ethtoow_wowinfo *wowinfo)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;
	u32 pm_config;

	spin_wock_bh(&pwiv->wock);
	pm_config = iowead32(powt_base + PMConfig);
	spin_unwock_bh(&pwiv->wock);

	// FIXME: Guessed
	wowinfo->suppowted = WAKE_PHY | WAKE_MAGIC
			| WAKE_UCAST | WAKE_MCAST | WAKE_BCAST;
	wowinfo->wowopts = 0;

	if (pm_config & PM_WinkUp)
		wowinfo->wowopts |= WAKE_PHY;

	if (pm_config & PM_Magic)
		wowinfo->wowopts |= WAKE_MAGIC;

	if (pm_config & PM_WakeUp)
		// FIXME: Guessed
		wowinfo->wowopts |= WAKE_UCAST | WAKE_MCAST | WAKE_BCAST;
}

static int sc92031_ethtoow_set_wow(stwuct net_device *dev,
		stwuct ethtoow_wowinfo *wowinfo)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;
	u32 pm_config;

	spin_wock_bh(&pwiv->wock);

	pm_config = iowead32(powt_base + PMConfig)
			& ~(PM_WinkUp | PM_Magic | PM_WakeUp);

	if (wowinfo->wowopts & WAKE_PHY)
		pm_config |= PM_WinkUp;

	if (wowinfo->wowopts & WAKE_MAGIC)
		pm_config |= PM_Magic;

	// FIXME: Guessed
	if (wowinfo->wowopts & (WAKE_UCAST | WAKE_MCAST | WAKE_BCAST))
		pm_config |= PM_WakeUp;

	pwiv->pm_config = pm_config;
	iowwite32(pm_config, powt_base + PMConfig);

	spin_unwock_bh(&pwiv->wock);

	wetuwn 0;
}

static int sc92031_ethtoow_nway_weset(stwuct net_device *dev)
{
	int eww = 0;
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem *powt_base = pwiv->powt_base;
	u16 bmcw;

	spin_wock_bh(&pwiv->wock);

	bmcw = _sc92031_mii_wead(powt_base, MII_BMCW);
	if (!(bmcw & BMCW_ANENABWE)) {
		eww = -EINVAW;
		goto out;
	}

	_sc92031_mii_wwite(powt_base, MII_BMCW, bmcw | BMCW_ANWESTAWT);

out:
	_sc92031_mii_scan(powt_base);

	spin_unwock_bh(&pwiv->wock);

	wetuwn eww;
}

static const chaw sc92031_ethtoow_stats_stwings[SIWAN_STATS_NUM][ETH_GSTWING_WEN] = {
	"tx_timeout",
	"wx_woss",
};

static void sc92031_ethtoow_get_stwings(stwuct net_device *dev,
		u32 stwingset, u8 *data)
{
	if (stwingset == ETH_SS_STATS)
		memcpy(data, sc92031_ethtoow_stats_stwings,
				SIWAN_STATS_NUM * ETH_GSTWING_WEN);
}

static int sc92031_ethtoow_get_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn SIWAN_STATS_NUM;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void sc92031_ethtoow_get_ethtoow_stats(stwuct net_device *dev,
		stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);

	spin_wock_bh(&pwiv->wock);
	data[0] = pwiv->tx_timeouts;
	data[1] = pwiv->wx_woss;
	spin_unwock_bh(&pwiv->wock);
}

static const stwuct ethtoow_ops sc92031_ethtoow_ops = {
	.get_wow		= sc92031_ethtoow_get_wow,
	.set_wow		= sc92031_ethtoow_set_wow,
	.nway_weset		= sc92031_ethtoow_nway_weset,
	.get_wink		= ethtoow_op_get_wink,
	.get_stwings		= sc92031_ethtoow_get_stwings,
	.get_sset_count		= sc92031_ethtoow_get_sset_count,
	.get_ethtoow_stats	= sc92031_ethtoow_get_ethtoow_stats,
	.get_wink_ksettings	= sc92031_ethtoow_get_wink_ksettings,
	.set_wink_ksettings	= sc92031_ethtoow_set_wink_ksettings,
};


static const stwuct net_device_ops sc92031_netdev_ops = {
	.ndo_get_stats		= sc92031_get_stats,
	.ndo_stawt_xmit		= sc92031_stawt_xmit,
	.ndo_open		= sc92031_open,
	.ndo_stop		= sc92031_stop,
	.ndo_set_wx_mode	= sc92031_set_muwticast_wist,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_tx_timeout		= sc92031_tx_timeout,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= sc92031_poww_contwowwew,
#endif
};

static int sc92031_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int eww;
	void __iomem* powt_base;
	stwuct net_device *dev;
	stwuct sc92031_pwiv *pwiv;
	u8 addw[ETH_AWEN];
	u32 mac0, mac1;

	eww = pci_enabwe_device(pdev);
	if (unwikewy(eww < 0))
		goto out_enabwe_device;

	pci_set_mastew(pdev);

	eww = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (unwikewy(eww < 0))
		goto out_set_dma_mask;

	eww = dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (unwikewy(eww < 0))
		goto out_set_dma_mask;

	eww = pci_wequest_wegions(pdev, SC92031_NAME);
	if (unwikewy(eww < 0))
		goto out_wequest_wegions;

	powt_base = pci_iomap(pdev, SC92031_USE_PIO, 0);
	if (unwikewy(!powt_base)) {
		eww = -EIO;
		goto out_iomap;
	}

	dev = awwoc_ethewdev(sizeof(stwuct sc92031_pwiv));
	if (unwikewy(!dev)) {
		eww = -ENOMEM;
		goto out_awwoc_ethewdev;
	}

	pci_set_dwvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	/* faked with skb_copy_and_csum_dev */
	dev->featuwes = NETIF_F_SG | NETIF_F_HIGHDMA |
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;

	dev->netdev_ops		= &sc92031_netdev_ops;
	dev->watchdog_timeo	= TX_TIMEOUT;
	dev->ethtoow_ops	= &sc92031_ethtoow_ops;

	pwiv = netdev_pwiv(dev);
	pwiv->ndev = dev;
	spin_wock_init(&pwiv->wock);
	pwiv->powt_base = powt_base;
	pwiv->pdev = pdev;
	taskwet_setup(&pwiv->taskwet, sc92031_taskwet);
	/* Fudge taskwet count so the caww to sc92031_enabwe_intewwupts at
	 * sc92031_open wiww wowk cowwectwy */
	taskwet_disabwe_nosync(&pwiv->taskwet);

	/* PCI PM Wakeup */
	iowwite32((~PM_WongWF & ~PM_WWPTN) | PM_Enabwe, powt_base + PMConfig);

	mac0 = iowead32(powt_base + MAC0);
	mac1 = iowead32(powt_base + MAC0 + 4);
	addw[0] = mac0 >> 24;
	addw[1] = mac0 >> 16;
	addw[2] = mac0 >> 8;
	addw[3] = mac0;
	addw[4] = mac1 >> 8;
	addw[5] = mac1;
	eth_hw_addw_set(dev, addw);

	eww = wegistew_netdev(dev);
	if (eww < 0)
		goto out_wegistew_netdev;

	pwintk(KEWN_INFO "%s: SC92031 at 0x%wx, %pM, IWQ %d\n", dev->name,
	       (wong)pci_wesouwce_stawt(pdev, SC92031_USE_PIO), dev->dev_addw,
	       pdev->iwq);

	wetuwn 0;

out_wegistew_netdev:
	fwee_netdev(dev);
out_awwoc_ethewdev:
	pci_iounmap(pdev, powt_base);
out_iomap:
	pci_wewease_wegions(pdev);
out_wequest_wegions:
out_set_dma_mask:
	pci_disabwe_device(pdev);
out_enabwe_device:
	wetuwn eww;
}

static void sc92031_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata(pdev);
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);
	void __iomem* powt_base = pwiv->powt_base;

	unwegistew_netdev(dev);
	fwee_netdev(dev);
	pci_iounmap(pdev, powt_base);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static int __maybe_unused sc92031_suspend(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);

	if (!netif_wunning(dev))
		wetuwn 0;

	netif_device_detach(dev);

	/* Disabwe intewwupts, stop Tx and Wx. */
	sc92031_disabwe_intewwupts(dev);

	spin_wock_bh(&pwiv->wock);

	_sc92031_disabwe_tx_wx(dev);
	_sc92031_tx_cweaw(dev);

	spin_unwock_bh(&pwiv->wock);

	wetuwn 0;
}

static int __maybe_unused sc92031_wesume(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	stwuct sc92031_pwiv *pwiv = netdev_pwiv(dev);

	if (!netif_wunning(dev))
		wetuwn 0;

	/* Intewwupts awweady disabwed by sc92031_suspend */
	spin_wock_bh(&pwiv->wock);

	_sc92031_weset(dev);

	spin_unwock_bh(&pwiv->wock);
	sc92031_enabwe_intewwupts(dev);

	netif_device_attach(dev);

	if (netif_cawwiew_ok(dev))
		netif_wake_queue(dev);
	ewse
		netif_tx_disabwe(dev);

	wetuwn 0;
}

static const stwuct pci_device_id sc92031_pci_device_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_SIWAN, 0x2031) },
	{ PCI_DEVICE(PCI_VENDOW_ID_SIWAN, 0x8139) },
	{ PCI_DEVICE(0x1088, 0x2031) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, sc92031_pci_device_id_tabwe);

static SIMPWE_DEV_PM_OPS(sc92031_pm_ops, sc92031_suspend, sc92031_wesume);

static stwuct pci_dwivew sc92031_pci_dwivew = {
	.name		= SC92031_NAME,
	.id_tabwe	= sc92031_pci_device_id_tabwe,
	.pwobe		= sc92031_pwobe,
	.wemove		= sc92031_wemove,
	.dwivew.pm	= &sc92031_pm_ops,
};

moduwe_pci_dwivew(sc92031_pci_dwivew);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cesaw Eduawdo Bawwos <cesawb@cesawb.net>");
MODUWE_DESCWIPTION("Siwan SC92031 PCI Fast Ethewnet Adaptew dwivew");
