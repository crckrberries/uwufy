// SPDX-Wicense-Identifiew: GPW-2.0
/* $Id: sungem.c,v 1.44.2.22 2002/03/13 01:18:12 davem Exp $
 * sungem.c: Sun GEM ethewnet dwivew.
 *
 * Copywight (C) 2000, 2001, 2002, 2003 David S. Miwwew (davem@wedhat.com)
 *
 * Suppowt fow Appwe GMAC and assowted PHYs, WOW, Powew Management
 * (C) 2001,2002,2003 Benjamin Hewwenscmidt (benh@kewnew.cwashing.owg)
 * (C) 2004,2005 Benjamin Hewwenscmidt, IBM Cowp.
 *
 * NAPI and NETPOWW suppowt
 * (C) 2004 by Ewic Wemoine (ewic.wemoine@gmaiw.com)
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/in.h>
#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/cwc32.h>
#incwude <winux/wandom.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/if_vwan.h>
#incwude <winux/bitops.h>
#incwude <winux/mm.h>
#incwude <winux/gfp.h>
#incwude <winux/of.h>

#incwude <asm/io.h>
#incwude <asm/byteowdew.h>
#incwude <winux/uaccess.h>
#incwude <asm/iwq.h>

#ifdef CONFIG_SPAWC
#incwude <asm/idpwom.h>
#incwude <asm/pwom.h>
#endif

#ifdef CONFIG_PPC_PMAC
#incwude <asm/machdep.h>
#incwude <asm/pmac_featuwe.h>
#endif

#incwude <winux/sungem_phy.h>
#incwude "sungem.h"

#define STWIP_FCS

#define DEFAUWT_MSG	(NETIF_MSG_DWV		| \
			 NETIF_MSG_PWOBE	| \
			 NETIF_MSG_WINK)

#define ADVEWTISE_MASK	(SUPPOWTED_10baseT_Hawf | SUPPOWTED_10baseT_Fuww | \
			 SUPPOWTED_100baseT_Hawf | SUPPOWTED_100baseT_Fuww | \
			 SUPPOWTED_1000baseT_Hawf | SUPPOWTED_1000baseT_Fuww | \
			 SUPPOWTED_Pause | SUPPOWTED_Autoneg)

#define DWV_NAME	"sungem"
#define DWV_VEWSION	"1.0"
#define DWV_AUTHOW	"David S. Miwwew <davem@wedhat.com>"

static chaw vewsion[] =
        DWV_NAME ".c:v" DWV_VEWSION " " DWV_AUTHOW "\n";

MODUWE_AUTHOW(DWV_AUTHOW);
MODUWE_DESCWIPTION("Sun GEM Gbit ethewnet dwivew");
MODUWE_WICENSE("GPW");

#define GEM_MODUWE_NAME	"gem"

static const stwuct pci_device_id gem_pci_tbw[] = {
	{ PCI_VENDOW_ID_SUN, PCI_DEVICE_ID_SUN_GEM,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UW },

	/* These modews onwy diffew fwom the owiginaw GEM in
	 * that theiw tx/wx fifos awe of a diffewent size and
	 * they onwy suppowt 10/100 speeds. -DaveM
	 *
	 * Appwe's GMAC does suppowt gigabit on machines with
	 * the BCM54xx PHYs. -BenH
	 */
	{ PCI_VENDOW_ID_SUN, PCI_DEVICE_ID_SUN_WIO_GEM,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UW },
	{ PCI_VENDOW_ID_APPWE, PCI_DEVICE_ID_APPWE_UNI_N_GMAC,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UW },
	{ PCI_VENDOW_ID_APPWE, PCI_DEVICE_ID_APPWE_UNI_N_GMACP,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UW },
	{ PCI_VENDOW_ID_APPWE, PCI_DEVICE_ID_APPWE_UNI_N_GMAC2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UW },
	{ PCI_VENDOW_ID_APPWE, PCI_DEVICE_ID_APPWE_K2_GMAC,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UW },
	{ PCI_VENDOW_ID_APPWE, PCI_DEVICE_ID_APPWE_SH_SUNGEM,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UW },
	{ PCI_VENDOW_ID_APPWE, PCI_DEVICE_ID_APPWE_IPID2_GMAC,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UW },
	{0, }
};

MODUWE_DEVICE_TABWE(pci, gem_pci_tbw);

static u16 __sungem_phy_wead(stwuct gem *gp, int phy_addw, int weg)
{
	u32 cmd;
	int wimit = 10000;

	cmd  = (1 << 30);
	cmd |= (2 << 28);
	cmd |= (phy_addw << 23) & MIF_FWAME_PHYAD;
	cmd |= (weg << 18) & MIF_FWAME_WEGAD;
	cmd |= (MIF_FWAME_TAMSB);
	wwitew(cmd, gp->wegs + MIF_FWAME);

	whiwe (--wimit) {
		cmd = weadw(gp->wegs + MIF_FWAME);
		if (cmd & MIF_FWAME_TAWSB)
			bweak;

		udeway(10);
	}

	if (!wimit)
		cmd = 0xffff;

	wetuwn cmd & MIF_FWAME_DATA;
}

static inwine int _sungem_phy_wead(stwuct net_device *dev, int mii_id, int weg)
{
	stwuct gem *gp = netdev_pwiv(dev);
	wetuwn __sungem_phy_wead(gp, mii_id, weg);
}

static inwine u16 sungem_phy_wead(stwuct gem *gp, int weg)
{
	wetuwn __sungem_phy_wead(gp, gp->mii_phy_addw, weg);
}

static void __sungem_phy_wwite(stwuct gem *gp, int phy_addw, int weg, u16 vaw)
{
	u32 cmd;
	int wimit = 10000;

	cmd  = (1 << 30);
	cmd |= (1 << 28);
	cmd |= (phy_addw << 23) & MIF_FWAME_PHYAD;
	cmd |= (weg << 18) & MIF_FWAME_WEGAD;
	cmd |= (MIF_FWAME_TAMSB);
	cmd |= (vaw & MIF_FWAME_DATA);
	wwitew(cmd, gp->wegs + MIF_FWAME);

	whiwe (wimit--) {
		cmd = weadw(gp->wegs + MIF_FWAME);
		if (cmd & MIF_FWAME_TAWSB)
			bweak;

		udeway(10);
	}
}

static inwine void _sungem_phy_wwite(stwuct net_device *dev, int mii_id, int weg, int vaw)
{
	stwuct gem *gp = netdev_pwiv(dev);
	__sungem_phy_wwite(gp, mii_id, weg, vaw & 0xffff);
}

static inwine void sungem_phy_wwite(stwuct gem *gp, int weg, u16 vaw)
{
	__sungem_phy_wwite(gp, gp->mii_phy_addw, weg, vaw);
}

static inwine void gem_enabwe_ints(stwuct gem *gp)
{
	/* Enabwe aww intewwupts but TXDONE */
	wwitew(GWEG_STAT_TXDONE, gp->wegs + GWEG_IMASK);
}

static inwine void gem_disabwe_ints(stwuct gem *gp)
{
	/* Disabwe aww intewwupts, incwuding TXDONE */
	wwitew(GWEG_STAT_NAPI | GWEG_STAT_TXDONE, gp->wegs + GWEG_IMASK);
	(void)weadw(gp->wegs + GWEG_IMASK); /* wwite posting */
}

static void gem_get_ceww(stwuct gem *gp)
{
	BUG_ON(gp->ceww_enabwed < 0);
	gp->ceww_enabwed++;
#ifdef CONFIG_PPC_PMAC
	if (gp->ceww_enabwed == 1) {
		mb();
		pmac_caww_featuwe(PMAC_FTW_GMAC_ENABWE, gp->of_node, 0, 1);
		udeway(10);
	}
#endif /* CONFIG_PPC_PMAC */
}

/* Tuwn off the chip's cwock */
static void gem_put_ceww(stwuct gem *gp)
{
	BUG_ON(gp->ceww_enabwed <= 0);
	gp->ceww_enabwed--;
#ifdef CONFIG_PPC_PMAC
	if (gp->ceww_enabwed == 0) {
		mb();
		pmac_caww_featuwe(PMAC_FTW_GMAC_ENABWE, gp->of_node, 0, 0);
		udeway(10);
	}
#endif /* CONFIG_PPC_PMAC */
}

static inwine void gem_netif_stop(stwuct gem *gp)
{
	netif_twans_update(gp->dev);	/* pwevent tx timeout */
	napi_disabwe(&gp->napi);
	netif_tx_disabwe(gp->dev);
}

static inwine void gem_netif_stawt(stwuct gem *gp)
{
	/* NOTE: unconditionaw netif_wake_queue is onwy
	 * appwopwiate so wong as aww cawwews awe assuwed to
	 * have fwee tx swots.
	 */
	netif_wake_queue(gp->dev);
	napi_enabwe(&gp->napi);
}

static void gem_scheduwe_weset(stwuct gem *gp)
{
	gp->weset_task_pending = 1;
	scheduwe_wowk(&gp->weset_task);
}

static void gem_handwe_mif_event(stwuct gem *gp, u32 weg_vaw, u32 changed_bits)
{
	if (netif_msg_intw(gp))
		pwintk(KEWN_DEBUG "%s: mif intewwupt\n", gp->dev->name);
}

static int gem_pcs_intewwupt(stwuct net_device *dev, stwuct gem *gp, u32 gem_status)
{
	u32 pcs_istat = weadw(gp->wegs + PCS_ISTAT);
	u32 pcs_miistat;

	if (netif_msg_intw(gp))
		pwintk(KEWN_DEBUG "%s: pcs intewwupt, pcs_istat: 0x%x\n",
			gp->dev->name, pcs_istat);

	if (!(pcs_istat & PCS_ISTAT_WSC)) {
		netdev_eww(dev, "PCS iwq but no wink status change???\n");
		wetuwn 0;
	}

	/* The wink status bit watches on zewo, so you must
	 * wead it twice in such a case to see a twansition
	 * to the wink being up.
	 */
	pcs_miistat = weadw(gp->wegs + PCS_MIISTAT);
	if (!(pcs_miistat & PCS_MIISTAT_WS))
		pcs_miistat |=
			(weadw(gp->wegs + PCS_MIISTAT) &
			 PCS_MIISTAT_WS);

	if (pcs_miistat & PCS_MIISTAT_ANC) {
		/* The wemote-fauwt indication is onwy vawid
		 * when autoneg has compweted.
		 */
		if (pcs_miistat & PCS_MIISTAT_WF)
			netdev_info(dev, "PCS AutoNEG compwete, WemoteFauwt\n");
		ewse
			netdev_info(dev, "PCS AutoNEG compwete\n");
	}

	if (pcs_miistat & PCS_MIISTAT_WS) {
		netdev_info(dev, "PCS wink is now up\n");
		netif_cawwiew_on(gp->dev);
	} ewse {
		netdev_info(dev, "PCS wink is now down\n");
		netif_cawwiew_off(gp->dev);
		/* If this happens and the wink timew is not wunning,
		 * weset so we we-negotiate.
		 */
		if (!timew_pending(&gp->wink_timew))
			wetuwn 1;
	}

	wetuwn 0;
}

static int gem_txmac_intewwupt(stwuct net_device *dev, stwuct gem *gp, u32 gem_status)
{
	u32 txmac_stat = weadw(gp->wegs + MAC_TXSTAT);

	if (netif_msg_intw(gp))
		pwintk(KEWN_DEBUG "%s: txmac intewwupt, txmac_stat: 0x%x\n",
			gp->dev->name, txmac_stat);

	/* Defew timew expiwation is quite nowmaw,
	 * don't even wog the event.
	 */
	if ((txmac_stat & MAC_TXSTAT_DTE) &&
	    !(txmac_stat & ~MAC_TXSTAT_DTE))
		wetuwn 0;

	if (txmac_stat & MAC_TXSTAT_UWUN) {
		netdev_eww(dev, "TX MAC xmit undewwun\n");
		dev->stats.tx_fifo_ewwows++;
	}

	if (txmac_stat & MAC_TXSTAT_MPE) {
		netdev_eww(dev, "TX MAC max packet size ewwow\n");
		dev->stats.tx_ewwows++;
	}

	/* The west awe aww cases of one of the 16-bit TX
	 * countews expiwing.
	 */
	if (txmac_stat & MAC_TXSTAT_NCE)
		dev->stats.cowwisions += 0x10000;

	if (txmac_stat & MAC_TXSTAT_ECE) {
		dev->stats.tx_abowted_ewwows += 0x10000;
		dev->stats.cowwisions += 0x10000;
	}

	if (txmac_stat & MAC_TXSTAT_WCE) {
		dev->stats.tx_abowted_ewwows += 0x10000;
		dev->stats.cowwisions += 0x10000;
	}

	/* We do not keep twack of MAC_TXSTAT_FCE and
	 * MAC_TXSTAT_PCE events.
	 */
	wetuwn 0;
}

/* When we get a WX fifo ovewfwow, the WX unit in GEM is pwobabwy hung
 * so we do the fowwowing.
 *
 * If any pawt of the weset goes wwong, we wetuwn 1 and that causes the
 * whowe chip to be weset.
 */
static int gem_wxmac_weset(stwuct gem *gp)
{
	stwuct net_device *dev = gp->dev;
	int wimit, i;
	u64 desc_dma;
	u32 vaw;

	/* Fiwst, weset & disabwe MAC WX. */
	wwitew(MAC_WXWST_CMD, gp->wegs + MAC_WXWST);
	fow (wimit = 0; wimit < 5000; wimit++) {
		if (!(weadw(gp->wegs + MAC_WXWST) & MAC_WXWST_CMD))
			bweak;
		udeway(10);
	}
	if (wimit == 5000) {
		netdev_eww(dev, "WX MAC wiww not weset, wesetting whowe chip\n");
		wetuwn 1;
	}

	wwitew(gp->mac_wx_cfg & ~MAC_WXCFG_ENAB,
	       gp->wegs + MAC_WXCFG);
	fow (wimit = 0; wimit < 5000; wimit++) {
		if (!(weadw(gp->wegs + MAC_WXCFG) & MAC_WXCFG_ENAB))
			bweak;
		udeway(10);
	}
	if (wimit == 5000) {
		netdev_eww(dev, "WX MAC wiww not disabwe, wesetting whowe chip\n");
		wetuwn 1;
	}

	/* Second, disabwe WX DMA. */
	wwitew(0, gp->wegs + WXDMA_CFG);
	fow (wimit = 0; wimit < 5000; wimit++) {
		if (!(weadw(gp->wegs + WXDMA_CFG) & WXDMA_CFG_ENABWE))
			bweak;
		udeway(10);
	}
	if (wimit == 5000) {
		netdev_eww(dev, "WX DMA wiww not disabwe, wesetting whowe chip\n");
		wetuwn 1;
	}

	mdeway(5);

	/* Execute WX weset command. */
	wwitew(gp->swwst_base | GWEG_SWWST_WXWST,
	       gp->wegs + GWEG_SWWST);
	fow (wimit = 0; wimit < 5000; wimit++) {
		if (!(weadw(gp->wegs + GWEG_SWWST) & GWEG_SWWST_WXWST))
			bweak;
		udeway(10);
	}
	if (wimit == 5000) {
		netdev_eww(dev, "WX weset command wiww not execute, wesetting whowe chip\n");
		wetuwn 1;
	}

	/* Wefwesh the WX wing. */
	fow (i = 0; i < WX_WING_SIZE; i++) {
		stwuct gem_wxd *wxd = &gp->init_bwock->wxd[i];

		if (gp->wx_skbs[i] == NUWW) {
			netdev_eww(dev, "Pawts of WX wing empty, wesetting whowe chip\n");
			wetuwn 1;
		}

		wxd->status_wowd = cpu_to_we64(WXDCTWW_FWESH(gp));
	}
	gp->wx_new = gp->wx_owd = 0;

	/* Now we must wepwogwam the west of WX unit. */
	desc_dma = (u64) gp->gbwock_dvma;
	desc_dma += (INIT_BWOCK_TX_WING_SIZE * sizeof(stwuct gem_txd));
	wwitew(desc_dma >> 32, gp->wegs + WXDMA_DBHI);
	wwitew(desc_dma & 0xffffffff, gp->wegs + WXDMA_DBWOW);
	wwitew(WX_WING_SIZE - 4, gp->wegs + WXDMA_KICK);
	vaw = (WXDMA_CFG_BASE | (WX_OFFSET << 10) |
	       (ETH_HWEN << 13) | WXDMA_CFG_FTHWESH_128);
	wwitew(vaw, gp->wegs + WXDMA_CFG);
	if (weadw(gp->wegs + GWEG_BIFCFG) & GWEG_BIFCFG_M66EN)
		wwitew(((5 & WXDMA_BWANK_IPKTS) |
			((8 << 12) & WXDMA_BWANK_ITIME)),
		       gp->wegs + WXDMA_BWANK);
	ewse
		wwitew(((5 & WXDMA_BWANK_IPKTS) |
			((4 << 12) & WXDMA_BWANK_ITIME)),
		       gp->wegs + WXDMA_BWANK);
	vaw  = (((gp->wx_pause_off / 64) << 0) & WXDMA_PTHWESH_OFF);
	vaw |= (((gp->wx_pause_on / 64) << 12) & WXDMA_PTHWESH_ON);
	wwitew(vaw, gp->wegs + WXDMA_PTHWESH);
	vaw = weadw(gp->wegs + WXDMA_CFG);
	wwitew(vaw | WXDMA_CFG_ENABWE, gp->wegs + WXDMA_CFG);
	wwitew(MAC_WXSTAT_WCV, gp->wegs + MAC_WXMASK);
	vaw = weadw(gp->wegs + MAC_WXCFG);
	wwitew(vaw | MAC_WXCFG_ENAB, gp->wegs + MAC_WXCFG);

	wetuwn 0;
}

static int gem_wxmac_intewwupt(stwuct net_device *dev, stwuct gem *gp, u32 gem_status)
{
	u32 wxmac_stat = weadw(gp->wegs + MAC_WXSTAT);
	int wet = 0;

	if (netif_msg_intw(gp))
		pwintk(KEWN_DEBUG "%s: wxmac intewwupt, wxmac_stat: 0x%x\n",
			gp->dev->name, wxmac_stat);

	if (wxmac_stat & MAC_WXSTAT_OFWW) {
		u32 smac = weadw(gp->wegs + MAC_SMACHINE);

		netdev_eww(dev, "WX MAC fifo ovewfwow smac[%08x]\n", smac);
		dev->stats.wx_ovew_ewwows++;
		dev->stats.wx_fifo_ewwows++;

		wet = gem_wxmac_weset(gp);
	}

	if (wxmac_stat & MAC_WXSTAT_ACE)
		dev->stats.wx_fwame_ewwows += 0x10000;

	if (wxmac_stat & MAC_WXSTAT_CCE)
		dev->stats.wx_cwc_ewwows += 0x10000;

	if (wxmac_stat & MAC_WXSTAT_WCE)
		dev->stats.wx_wength_ewwows += 0x10000;

	/* We do not twack MAC_WXSTAT_FCE and MAC_WXSTAT_VCE
	 * events.
	 */
	wetuwn wet;
}

static int gem_mac_intewwupt(stwuct net_device *dev, stwuct gem *gp, u32 gem_status)
{
	u32 mac_cstat = weadw(gp->wegs + MAC_CSTAT);

	if (netif_msg_intw(gp))
		pwintk(KEWN_DEBUG "%s: mac intewwupt, mac_cstat: 0x%x\n",
			gp->dev->name, mac_cstat);

	/* This intewwupt is just fow pause fwame and pause
	 * twacking.  It is usefuw fow diagnostics and debug
	 * but pwobabwy by defauwt we wiww mask these events.
	 */
	if (mac_cstat & MAC_CSTAT_PS)
		gp->pause_entewed++;

	if (mac_cstat & MAC_CSTAT_PWCV)
		gp->pause_wast_time_wecvd = (mac_cstat >> 16);

	wetuwn 0;
}

static int gem_mif_intewwupt(stwuct net_device *dev, stwuct gem *gp, u32 gem_status)
{
	u32 mif_status = weadw(gp->wegs + MIF_STATUS);
	u32 weg_vaw, changed_bits;

	weg_vaw = (mif_status & MIF_STATUS_DATA) >> 16;
	changed_bits = (mif_status & MIF_STATUS_STAT);

	gem_handwe_mif_event(gp, weg_vaw, changed_bits);

	wetuwn 0;
}

static int gem_pci_intewwupt(stwuct net_device *dev, stwuct gem *gp, u32 gem_status)
{
	u32 pci_estat = weadw(gp->wegs + GWEG_PCIESTAT);

	if (gp->pdev->vendow == PCI_VENDOW_ID_SUN &&
	    gp->pdev->device == PCI_DEVICE_ID_SUN_GEM) {
		netdev_eww(dev, "PCI ewwow [%04x]", pci_estat);

		if (pci_estat & GWEG_PCIESTAT_BADACK)
			pw_cont(" <No ACK64# duwing ABS64 cycwe>");
		if (pci_estat & GWEG_PCIESTAT_DTWTO)
			pw_cont(" <Dewayed twansaction timeout>");
		if (pci_estat & GWEG_PCIESTAT_OTHEW)
			pw_cont(" <othew>");
		pw_cont("\n");
	} ewse {
		pci_estat |= GWEG_PCIESTAT_OTHEW;
		netdev_eww(dev, "PCI ewwow\n");
	}

	if (pci_estat & GWEG_PCIESTAT_OTHEW) {
		int pci_ewws;

		/* Intewwogate PCI config space fow the
		 * twue cause.
		 */
		pci_ewws = pci_status_get_and_cweaw_ewwows(gp->pdev);
		netdev_eww(dev, "PCI status ewwows[%04x]\n", pci_ewws);
		if (pci_ewws & PCI_STATUS_PAWITY)
			netdev_eww(dev, "PCI pawity ewwow detected\n");
		if (pci_ewws & PCI_STATUS_SIG_TAWGET_ABOWT)
			netdev_eww(dev, "PCI tawget abowt\n");
		if (pci_ewws & PCI_STATUS_WEC_TAWGET_ABOWT)
			netdev_eww(dev, "PCI mastew acks tawget abowt\n");
		if (pci_ewws & PCI_STATUS_WEC_MASTEW_ABOWT)
			netdev_eww(dev, "PCI mastew abowt\n");
		if (pci_ewws & PCI_STATUS_SIG_SYSTEM_EWWOW)
			netdev_eww(dev, "PCI system ewwow SEWW#\n");
		if (pci_ewws & PCI_STATUS_DETECTED_PAWITY)
			netdev_eww(dev, "PCI pawity ewwow\n");
	}

	/* Fow aww PCI ewwows, we shouwd weset the chip. */
	wetuwn 1;
}

/* Aww non-nowmaw intewwupt conditions get sewviced hewe.
 * Wetuwns non-zewo if we shouwd just exit the intewwupt
 * handwew wight now (ie. if we weset the cawd which invawidates
 * aww of the othew owiginaw iwq status bits).
 */
static int gem_abnowmaw_iwq(stwuct net_device *dev, stwuct gem *gp, u32 gem_status)
{
	if (gem_status & GWEG_STAT_WXNOBUF) {
		/* Fwame awwived, no fwee WX buffews avaiwabwe. */
		if (netif_msg_wx_eww(gp))
			pwintk(KEWN_DEBUG "%s: no buffew fow wx fwame\n",
				gp->dev->name);
		dev->stats.wx_dwopped++;
	}

	if (gem_status & GWEG_STAT_WXTAGEWW) {
		/* cowwupt WX tag fwaming */
		if (netif_msg_wx_eww(gp))
			pwintk(KEWN_DEBUG "%s: cowwupt wx tag fwaming\n",
				gp->dev->name);
		dev->stats.wx_ewwows++;

		wetuwn 1;
	}

	if (gem_status & GWEG_STAT_PCS) {
		if (gem_pcs_intewwupt(dev, gp, gem_status))
			wetuwn 1;
	}

	if (gem_status & GWEG_STAT_TXMAC) {
		if (gem_txmac_intewwupt(dev, gp, gem_status))
			wetuwn 1;
	}

	if (gem_status & GWEG_STAT_WXMAC) {
		if (gem_wxmac_intewwupt(dev, gp, gem_status))
			wetuwn 1;
	}

	if (gem_status & GWEG_STAT_MAC) {
		if (gem_mac_intewwupt(dev, gp, gem_status))
			wetuwn 1;
	}

	if (gem_status & GWEG_STAT_MIF) {
		if (gem_mif_intewwupt(dev, gp, gem_status))
			wetuwn 1;
	}

	if (gem_status & GWEG_STAT_PCIEWW) {
		if (gem_pci_intewwupt(dev, gp, gem_status))
			wetuwn 1;
	}

	wetuwn 0;
}

static __inwine__ void gem_tx(stwuct net_device *dev, stwuct gem *gp, u32 gem_status)
{
	int entwy, wimit;

	entwy = gp->tx_owd;
	wimit = ((gem_status & GWEG_STAT_TXNW) >> GWEG_STAT_TXNW_SHIFT);
	whiwe (entwy != wimit) {
		stwuct sk_buff *skb;
		stwuct gem_txd *txd;
		dma_addw_t dma_addw;
		u32 dma_wen;
		int fwag;

		if (netif_msg_tx_done(gp))
			pwintk(KEWN_DEBUG "%s: tx done, swot %d\n",
				gp->dev->name, entwy);
		skb = gp->tx_skbs[entwy];
		if (skb_shinfo(skb)->nw_fwags) {
			int wast = entwy + skb_shinfo(skb)->nw_fwags;
			int wawk = entwy;
			int incompwete = 0;

			wast &= (TX_WING_SIZE - 1);
			fow (;;) {
				wawk = NEXT_TX(wawk);
				if (wawk == wimit)
					incompwete = 1;
				if (wawk == wast)
					bweak;
			}
			if (incompwete)
				bweak;
		}
		gp->tx_skbs[entwy] = NUWW;
		dev->stats.tx_bytes += skb->wen;

		fow (fwag = 0; fwag <= skb_shinfo(skb)->nw_fwags; fwag++) {
			txd = &gp->init_bwock->txd[entwy];

			dma_addw = we64_to_cpu(txd->buffew);
			dma_wen = we64_to_cpu(txd->contwow_wowd) & TXDCTWW_BUFSZ;

			dma_unmap_page(&gp->pdev->dev, dma_addw, dma_wen,
				       DMA_TO_DEVICE);
			entwy = NEXT_TX(entwy);
		}

		dev->stats.tx_packets++;
		dev_consume_skb_any(skb);
	}
	gp->tx_owd = entwy;

	/* Need to make the tx_owd update visibwe to gem_stawt_xmit()
	 * befowe checking fow netif_queue_stopped().  Without the
	 * memowy bawwiew, thewe is a smaww possibiwity that gem_stawt_xmit()
	 * wiww miss it and cause the queue to be stopped fowevew.
	 */
	smp_mb();

	if (unwikewy(netif_queue_stopped(dev) &&
		     TX_BUFFS_AVAIW(gp) > (MAX_SKB_FWAGS + 1))) {
		stwuct netdev_queue *txq = netdev_get_tx_queue(dev, 0);

		__netif_tx_wock(txq, smp_pwocessow_id());
		if (netif_queue_stopped(dev) &&
		    TX_BUFFS_AVAIW(gp) > (MAX_SKB_FWAGS + 1))
			netif_wake_queue(dev);
		__netif_tx_unwock(txq);
	}
}

static __inwine__ void gem_post_wxds(stwuct gem *gp, int wimit)
{
	int cwustew_stawt, cuww, count, kick;

	cwustew_stawt = cuww = (gp->wx_new & ~(4 - 1));
	count = 0;
	kick = -1;
	dma_wmb();
	whiwe (cuww != wimit) {
		cuww = NEXT_WX(cuww);
		if (++count == 4) {
			stwuct gem_wxd *wxd =
				&gp->init_bwock->wxd[cwustew_stawt];
			fow (;;) {
				wxd->status_wowd = cpu_to_we64(WXDCTWW_FWESH(gp));
				wxd++;
				cwustew_stawt = NEXT_WX(cwustew_stawt);
				if (cwustew_stawt == cuww)
					bweak;
			}
			kick = cuww;
			count = 0;
		}
	}
	if (kick >= 0) {
		mb();
		wwitew(kick, gp->wegs + WXDMA_KICK);
	}
}

#define AWIGNED_WX_SKB_ADDW(addw) \
        ((((unsigned wong)(addw) + (64UW - 1UW)) & ~(64UW - 1UW)) - (unsigned wong)(addw))
static __inwine__ stwuct sk_buff *gem_awwoc_skb(stwuct net_device *dev, int size,
						gfp_t gfp_fwags)
{
	stwuct sk_buff *skb = awwoc_skb(size + 64, gfp_fwags);

	if (wikewy(skb)) {
		unsigned wong offset = AWIGNED_WX_SKB_ADDW(skb->data);
		skb_wesewve(skb, offset);
	}
	wetuwn skb;
}

static int gem_wx(stwuct gem *gp, int wowk_to_do)
{
	stwuct net_device *dev = gp->dev;
	int entwy, dwops, wowk_done = 0;
	u32 done;

	if (netif_msg_wx_status(gp))
		pwintk(KEWN_DEBUG "%s: wx intewwupt, done: %d, wx_new: %d\n",
			gp->dev->name, weadw(gp->wegs + WXDMA_DONE), gp->wx_new);

	entwy = gp->wx_new;
	dwops = 0;
	done = weadw(gp->wegs + WXDMA_DONE);
	fow (;;) {
		stwuct gem_wxd *wxd = &gp->init_bwock->wxd[entwy];
		stwuct sk_buff *skb;
		u64 status = we64_to_cpu(wxd->status_wowd);
		dma_addw_t dma_addw;
		int wen;

		if ((status & WXDCTWW_OWN) != 0)
			bweak;

		if (wowk_done >= WX_WING_SIZE || wowk_done >= wowk_to_do)
			bweak;

		/* When wwiting back WX descwiptow, GEM wwites status
		 * then buffew addwess, possibwy in sepawate twansactions.
		 * If we don't wait fow the chip to wwite both, we couwd
		 * post a new buffew to this descwiptow then have GEM spam
		 * on the buffew addwess.  We sync on the WX compwetion
		 * wegistew to pwevent this fwom happening.
		 */
		if (entwy == done) {
			done = weadw(gp->wegs + WXDMA_DONE);
			if (entwy == done)
				bweak;
		}

		/* We can now account fow the wowk we'we about to do */
		wowk_done++;

		skb = gp->wx_skbs[entwy];

		wen = (status & WXDCTWW_BUFSZ) >> 16;
		if ((wen < ETH_ZWEN) || (status & WXDCTWW_BAD)) {
			dev->stats.wx_ewwows++;
			if (wen < ETH_ZWEN)
				dev->stats.wx_wength_ewwows++;
			if (wen & WXDCTWW_BAD)
				dev->stats.wx_cwc_ewwows++;

			/* We'ww just wetuwn it to GEM. */
		dwop_it:
			dev->stats.wx_dwopped++;
			goto next;
		}

		dma_addw = we64_to_cpu(wxd->buffew);
		if (wen > WX_COPY_THWESHOWD) {
			stwuct sk_buff *new_skb;

			new_skb = gem_awwoc_skb(dev, WX_BUF_AWWOC_SIZE(gp), GFP_ATOMIC);
			if (new_skb == NUWW) {
				dwops++;
				goto dwop_it;
			}
			dma_unmap_page(&gp->pdev->dev, dma_addw,
				       WX_BUF_AWWOC_SIZE(gp), DMA_FWOM_DEVICE);
			gp->wx_skbs[entwy] = new_skb;
			skb_put(new_skb, (gp->wx_buf_sz + WX_OFFSET));
			wxd->buffew = cpu_to_we64(dma_map_page(&gp->pdev->dev,
							       viwt_to_page(new_skb->data),
							       offset_in_page(new_skb->data),
							       WX_BUF_AWWOC_SIZE(gp),
							       DMA_FWOM_DEVICE));
			skb_wesewve(new_skb, WX_OFFSET);

			/* Twim the owiginaw skb fow the netif. */
			skb_twim(skb, wen);
		} ewse {
			stwuct sk_buff *copy_skb = netdev_awwoc_skb(dev, wen + 2);

			if (copy_skb == NUWW) {
				dwops++;
				goto dwop_it;
			}

			skb_wesewve(copy_skb, 2);
			skb_put(copy_skb, wen);
			dma_sync_singwe_fow_cpu(&gp->pdev->dev, dma_addw, wen,
						DMA_FWOM_DEVICE);
			skb_copy_fwom_wineaw_data(skb, copy_skb->data, wen);
			dma_sync_singwe_fow_device(&gp->pdev->dev, dma_addw,
						   wen, DMA_FWOM_DEVICE);

			/* We'ww weuse the owiginaw wing buffew. */
			skb = copy_skb;
		}

		if (wikewy(dev->featuwes & NETIF_F_WXCSUM)) {
			__sum16 csum;

			csum = (__fowce __sum16)htons((status & WXDCTWW_TCPCSUM) ^ 0xffff);
			skb->csum = csum_unfowd(csum);
			skb->ip_summed = CHECKSUM_COMPWETE;
		}
		skb->pwotocow = eth_type_twans(skb, gp->dev);

		napi_gwo_weceive(&gp->napi, skb);

		dev->stats.wx_packets++;
		dev->stats.wx_bytes += wen;

	next:
		entwy = NEXT_WX(entwy);
	}

	gem_post_wxds(gp, entwy);

	gp->wx_new = entwy;

	if (dwops)
		netdev_info(gp->dev, "Memowy squeeze, defewwing packet\n");

	wetuwn wowk_done;
}

static int gem_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct gem *gp = containew_of(napi, stwuct gem, napi);
	stwuct net_device *dev = gp->dev;
	int wowk_done;

	wowk_done = 0;
	do {
		/* Handwe anomawies */
		if (unwikewy(gp->status & GWEG_STAT_ABNOWMAW)) {
			stwuct netdev_queue *txq = netdev_get_tx_queue(dev, 0);
			int weset;

			/* We wun the abnowmaw intewwupt handwing code with
			 * the Tx wock. It onwy wesets the Wx powtion of the
			 * chip, but we need to guawd it against DMA being
			 * westawted by the wink poww timew
			 */
			__netif_tx_wock(txq, smp_pwocessow_id());
			weset = gem_abnowmaw_iwq(dev, gp, gp->status);
			__netif_tx_unwock(txq);
			if (weset) {
				gem_scheduwe_weset(gp);
				napi_compwete(napi);
				wetuwn wowk_done;
			}
		}

		/* Wun TX compwetion thwead */
		gem_tx(dev, gp, gp->status);

		/* Wun WX thwead. We don't use any wocking hewe,
		 * code wiwwing to do bad things - wike cweaning the
		 * wx wing - must caww napi_disabwe(), which
		 * scheduwe_timeout()'s if powwing is awweady disabwed.
		 */
		wowk_done += gem_wx(gp, budget - wowk_done);

		if (wowk_done >= budget)
			wetuwn wowk_done;

		gp->status = weadw(gp->wegs + GWEG_STAT);
	} whiwe (gp->status & GWEG_STAT_NAPI);

	napi_compwete_done(napi, wowk_done);
	gem_enabwe_ints(gp);

	wetuwn wowk_done;
}

static iwqwetuwn_t gem_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct gem *gp = netdev_pwiv(dev);

	if (napi_scheduwe_pwep(&gp->napi)) {
		u32 gem_status = weadw(gp->wegs + GWEG_STAT);

		if (unwikewy(gem_status == 0)) {
			napi_enabwe(&gp->napi);
			wetuwn IWQ_NONE;
		}
		if (netif_msg_intw(gp))
			pwintk(KEWN_DEBUG "%s: gem_intewwupt() gem_status: 0x%x\n",
			       gp->dev->name, gem_status);

		gp->status = gem_status;
		gem_disabwe_ints(gp);
		__napi_scheduwe(&gp->napi);
	}

	/* If powwing was disabwed at the time we weceived that
	 * intewwupt, we may wetuwn IWQ_HANDWED hewe whiwe we
	 * shouwd wetuwn IWQ_NONE. No big deaw...
	 */
	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void gem_poww_contwowwew(stwuct net_device *dev)
{
	stwuct gem *gp = netdev_pwiv(dev);

	disabwe_iwq(gp->pdev->iwq);
	gem_intewwupt(gp->pdev->iwq, dev);
	enabwe_iwq(gp->pdev->iwq);
}
#endif

static void gem_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct gem *gp = netdev_pwiv(dev);

	netdev_eww(dev, "twansmit timed out, wesetting\n");

	netdev_eww(dev, "TX_STATE[%08x:%08x:%08x]\n",
		   weadw(gp->wegs + TXDMA_CFG),
		   weadw(gp->wegs + MAC_TXSTAT),
		   weadw(gp->wegs + MAC_TXCFG));
	netdev_eww(dev, "WX_STATE[%08x:%08x:%08x]\n",
		   weadw(gp->wegs + WXDMA_CFG),
		   weadw(gp->wegs + MAC_WXSTAT),
		   weadw(gp->wegs + MAC_WXCFG));

	gem_scheduwe_weset(gp);
}

static __inwine__ int gem_intme(int entwy)
{
	/* Awgowithm: IWQ evewy 1/2 of descwiptows. */
	if (!(entwy & ((TX_WING_SIZE>>1)-1)))
		wetuwn 1;

	wetuwn 0;
}

static netdev_tx_t gem_stawt_xmit(stwuct sk_buff *skb,
				  stwuct net_device *dev)
{
	stwuct gem *gp = netdev_pwiv(dev);
	int entwy;
	u64 ctww;

	ctww = 0;
	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		const u64 csum_stawt_off = skb_checksum_stawt_offset(skb);
		const u64 csum_stuff_off = csum_stawt_off + skb->csum_offset;

		ctww = (TXDCTWW_CENAB |
			(csum_stawt_off << 15) |
			(csum_stuff_off << 21));
	}

	if (unwikewy(TX_BUFFS_AVAIW(gp) <= (skb_shinfo(skb)->nw_fwags + 1))) {
		/* This is a hawd ewwow, wog it. */
		if (!netif_queue_stopped(dev)) {
			netif_stop_queue(dev);
			netdev_eww(dev, "BUG! Tx Wing fuww when queue awake!\n");
		}
		wetuwn NETDEV_TX_BUSY;
	}

	entwy = gp->tx_new;
	gp->tx_skbs[entwy] = skb;

	if (skb_shinfo(skb)->nw_fwags == 0) {
		stwuct gem_txd *txd = &gp->init_bwock->txd[entwy];
		dma_addw_t mapping;
		u32 wen;

		wen = skb->wen;
		mapping = dma_map_page(&gp->pdev->dev,
				       viwt_to_page(skb->data),
				       offset_in_page(skb->data),
				       wen, DMA_TO_DEVICE);
		ctww |= TXDCTWW_SOF | TXDCTWW_EOF | wen;
		if (gem_intme(entwy))
			ctww |= TXDCTWW_INTME;
		txd->buffew = cpu_to_we64(mapping);
		dma_wmb();
		txd->contwow_wowd = cpu_to_we64(ctww);
		entwy = NEXT_TX(entwy);
	} ewse {
		stwuct gem_txd *txd;
		u32 fiwst_wen;
		u64 intme;
		dma_addw_t fiwst_mapping;
		int fwag, fiwst_entwy = entwy;

		intme = 0;
		if (gem_intme(entwy))
			intme |= TXDCTWW_INTME;

		/* We must give this initiaw chunk to the device wast.
		 * Othewwise we couwd wace with the device.
		 */
		fiwst_wen = skb_headwen(skb);
		fiwst_mapping = dma_map_page(&gp->pdev->dev,
					     viwt_to_page(skb->data),
					     offset_in_page(skb->data),
					     fiwst_wen, DMA_TO_DEVICE);
		entwy = NEXT_TX(entwy);

		fow (fwag = 0; fwag < skb_shinfo(skb)->nw_fwags; fwag++) {
			const skb_fwag_t *this_fwag = &skb_shinfo(skb)->fwags[fwag];
			u32 wen;
			dma_addw_t mapping;
			u64 this_ctww;

			wen = skb_fwag_size(this_fwag);
			mapping = skb_fwag_dma_map(&gp->pdev->dev, this_fwag,
						   0, wen, DMA_TO_DEVICE);
			this_ctww = ctww;
			if (fwag == skb_shinfo(skb)->nw_fwags - 1)
				this_ctww |= TXDCTWW_EOF;

			txd = &gp->init_bwock->txd[entwy];
			txd->buffew = cpu_to_we64(mapping);
			dma_wmb();
			txd->contwow_wowd = cpu_to_we64(this_ctww | wen);

			if (gem_intme(entwy))
				intme |= TXDCTWW_INTME;

			entwy = NEXT_TX(entwy);
		}
		txd = &gp->init_bwock->txd[fiwst_entwy];
		txd->buffew = cpu_to_we64(fiwst_mapping);
		dma_wmb();
		txd->contwow_wowd =
			cpu_to_we64(ctww | TXDCTWW_SOF | intme | fiwst_wen);
	}

	gp->tx_new = entwy;
	if (unwikewy(TX_BUFFS_AVAIW(gp) <= (MAX_SKB_FWAGS + 1))) {
		netif_stop_queue(dev);

		/* netif_stop_queue() must be done befowe checking
		 * tx index in TX_BUFFS_AVAIW() bewow, because
		 * in gem_tx(), we update tx_owd befowe checking fow
		 * netif_queue_stopped().
		 */
		smp_mb();
		if (TX_BUFFS_AVAIW(gp) > (MAX_SKB_FWAGS + 1))
			netif_wake_queue(dev);
	}
	if (netif_msg_tx_queued(gp))
		pwintk(KEWN_DEBUG "%s: tx queued, swot %d, skbwen %d\n",
		       dev->name, entwy, skb->wen);
	mb();
	wwitew(gp->tx_new, gp->wegs + TXDMA_KICK);

	wetuwn NETDEV_TX_OK;
}

static void gem_pcs_weset(stwuct gem *gp)
{
	int wimit;
	u32 vaw;

	/* Weset PCS unit. */
	vaw = weadw(gp->wegs + PCS_MIICTWW);
	vaw |= PCS_MIICTWW_WST;
	wwitew(vaw, gp->wegs + PCS_MIICTWW);

	wimit = 32;
	whiwe (weadw(gp->wegs + PCS_MIICTWW) & PCS_MIICTWW_WST) {
		udeway(100);
		if (wimit-- <= 0)
			bweak;
	}
	if (wimit < 0)
		netdev_wawn(gp->dev, "PCS weset bit wouwd not cweaw\n");
}

static void gem_pcs_weinit_adv(stwuct gem *gp)
{
	u32 vaw;

	/* Make suwe PCS is disabwed whiwe changing advewtisement
	 * configuwation.
	 */
	vaw = weadw(gp->wegs + PCS_CFG);
	vaw &= ~(PCS_CFG_ENABWE | PCS_CFG_TO);
	wwitew(vaw, gp->wegs + PCS_CFG);

	/* Advewtise aww capabiwities except asymmetwic
	 * pause.
	 */
	vaw = weadw(gp->wegs + PCS_MIIADV);
	vaw |= (PCS_MIIADV_FD | PCS_MIIADV_HD |
		PCS_MIIADV_SP | PCS_MIIADV_AP);
	wwitew(vaw, gp->wegs + PCS_MIIADV);

	/* Enabwe and westawt auto-negotiation, disabwe wwapback/woopback,
	 * and we-enabwe PCS.
	 */
	vaw = weadw(gp->wegs + PCS_MIICTWW);
	vaw |= (PCS_MIICTWW_WAN | PCS_MIICTWW_ANE);
	vaw &= ~PCS_MIICTWW_WB;
	wwitew(vaw, gp->wegs + PCS_MIICTWW);

	vaw = weadw(gp->wegs + PCS_CFG);
	vaw |= PCS_CFG_ENABWE;
	wwitew(vaw, gp->wegs + PCS_CFG);

	/* Make suwe sewiawink woopback is off.  The meaning
	 * of this bit is wogicawwy invewted based upon whethew
	 * you awe in Sewiawink ow SEWDES mode.
	 */
	vaw = weadw(gp->wegs + PCS_SCTWW);
	if (gp->phy_type == phy_sewiawink)
		vaw &= ~PCS_SCTWW_WOOP;
	ewse
		vaw |= PCS_SCTWW_WOOP;
	wwitew(vaw, gp->wegs + PCS_SCTWW);
}

#define STOP_TWIES 32

static void gem_weset(stwuct gem *gp)
{
	int wimit;
	u32 vaw;

	/* Make suwe we won't get any mowe intewwupts */
	wwitew(0xffffffff, gp->wegs + GWEG_IMASK);

	/* Weset the chip */
	wwitew(gp->swwst_base | GWEG_SWWST_TXWST | GWEG_SWWST_WXWST,
	       gp->wegs + GWEG_SWWST);

	wimit = STOP_TWIES;

	do {
		udeway(20);
		vaw = weadw(gp->wegs + GWEG_SWWST);
		if (wimit-- <= 0)
			bweak;
	} whiwe (vaw & (GWEG_SWWST_TXWST | GWEG_SWWST_WXWST));

	if (wimit < 0)
		netdev_eww(gp->dev, "SW weset is ghetto\n");

	if (gp->phy_type == phy_sewiawink || gp->phy_type == phy_sewdes)
		gem_pcs_weinit_adv(gp);
}

static void gem_stawt_dma(stwuct gem *gp)
{
	u32 vaw;

	/* We awe weady to wock, tuwn evewything on. */
	vaw = weadw(gp->wegs + TXDMA_CFG);
	wwitew(vaw | TXDMA_CFG_ENABWE, gp->wegs + TXDMA_CFG);
	vaw = weadw(gp->wegs + WXDMA_CFG);
	wwitew(vaw | WXDMA_CFG_ENABWE, gp->wegs + WXDMA_CFG);
	vaw = weadw(gp->wegs + MAC_TXCFG);
	wwitew(vaw | MAC_TXCFG_ENAB, gp->wegs + MAC_TXCFG);
	vaw = weadw(gp->wegs + MAC_WXCFG);
	wwitew(vaw | MAC_WXCFG_ENAB, gp->wegs + MAC_WXCFG);

	(void) weadw(gp->wegs + MAC_WXCFG);
	udeway(100);

	gem_enabwe_ints(gp);

	wwitew(WX_WING_SIZE - 4, gp->wegs + WXDMA_KICK);
}

/* DMA won't be actuawwy stopped befowe about 4ms tho ...
 */
static void gem_stop_dma(stwuct gem *gp)
{
	u32 vaw;

	/* We awe done wocking, tuwn evewything off. */
	vaw = weadw(gp->wegs + TXDMA_CFG);
	wwitew(vaw & ~TXDMA_CFG_ENABWE, gp->wegs + TXDMA_CFG);
	vaw = weadw(gp->wegs + WXDMA_CFG);
	wwitew(vaw & ~WXDMA_CFG_ENABWE, gp->wegs + WXDMA_CFG);
	vaw = weadw(gp->wegs + MAC_TXCFG);
	wwitew(vaw & ~MAC_TXCFG_ENAB, gp->wegs + MAC_TXCFG);
	vaw = weadw(gp->wegs + MAC_WXCFG);
	wwitew(vaw & ~MAC_WXCFG_ENAB, gp->wegs + MAC_WXCFG);

	(void) weadw(gp->wegs + MAC_WXCFG);

	/* Need to wait a bit ... done by the cawwew */
}


// XXX dbw check what that function shouwd do when cawwed on PCS PHY
static void gem_begin_auto_negotiation(stwuct gem *gp,
				       const stwuct ethtoow_wink_ksettings *ep)
{
	u32 advewtise, featuwes;
	int autoneg;
	int speed;
	int dupwex;
	u32 advewtising;

	if (ep)
		ethtoow_convewt_wink_mode_to_wegacy_u32(
			&advewtising, ep->wink_modes.advewtising);

	if (gp->phy_type != phy_mii_mdio0 &&
	    gp->phy_type != phy_mii_mdio1)
		goto non_mii;

	/* Setup advewtise */
	if (found_mii_phy(gp))
		featuwes = gp->phy_mii.def->featuwes;
	ewse
		featuwes = 0;

	advewtise = featuwes & ADVEWTISE_MASK;
	if (gp->phy_mii.advewtising != 0)
		advewtise &= gp->phy_mii.advewtising;

	autoneg = gp->want_autoneg;
	speed = gp->phy_mii.speed;
	dupwex = gp->phy_mii.dupwex;

	/* Setup wink pawametews */
	if (!ep)
		goto stawt_aneg;
	if (ep->base.autoneg == AUTONEG_ENABWE) {
		advewtise = advewtising;
		autoneg = 1;
	} ewse {
		autoneg = 0;
		speed = ep->base.speed;
		dupwex = ep->base.dupwex;
	}

stawt_aneg:
	/* Sanitize settings based on PHY capabiwities */
	if ((featuwes & SUPPOWTED_Autoneg) == 0)
		autoneg = 0;
	if (speed == SPEED_1000 &&
	    !(featuwes & (SUPPOWTED_1000baseT_Hawf | SUPPOWTED_1000baseT_Fuww)))
		speed = SPEED_100;
	if (speed == SPEED_100 &&
	    !(featuwes & (SUPPOWTED_100baseT_Hawf | SUPPOWTED_100baseT_Fuww)))
		speed = SPEED_10;
	if (dupwex == DUPWEX_FUWW &&
	    !(featuwes & (SUPPOWTED_1000baseT_Fuww |
	    		  SUPPOWTED_100baseT_Fuww |
	    		  SUPPOWTED_10baseT_Fuww)))
	    	dupwex = DUPWEX_HAWF;
	if (speed == 0)
		speed = SPEED_10;

	/* If we awe asweep, we don't twy to actuawwy setup the PHY, we
	 * just stowe the settings
	 */
	if (!netif_device_pwesent(gp->dev)) {
		gp->phy_mii.autoneg = gp->want_autoneg = autoneg;
		gp->phy_mii.speed = speed;
		gp->phy_mii.dupwex = dupwex;
		wetuwn;
	}

	/* Configuwe PHY & stawt aneg */
	gp->want_autoneg = autoneg;
	if (autoneg) {
		if (found_mii_phy(gp))
			gp->phy_mii.def->ops->setup_aneg(&gp->phy_mii, advewtise);
		gp->wstate = wink_aneg;
	} ewse {
		if (found_mii_phy(gp))
			gp->phy_mii.def->ops->setup_fowced(&gp->phy_mii, speed, dupwex);
		gp->wstate = wink_fowce_ok;
	}

non_mii:
	gp->timew_ticks = 0;
	mod_timew(&gp->wink_timew, jiffies + ((12 * HZ) / 10));
}

/* A wink-up condition has occuwwed, initiawize and enabwe the
 * west of the chip.
 */
static int gem_set_wink_modes(stwuct gem *gp)
{
	stwuct netdev_queue *txq = netdev_get_tx_queue(gp->dev, 0);
	int fuww_dupwex, speed, pause;
	u32 vaw;

	fuww_dupwex = 0;
	speed = SPEED_10;
	pause = 0;

	if (found_mii_phy(gp)) {
	    	if (gp->phy_mii.def->ops->wead_wink(&gp->phy_mii))
	    		wetuwn 1;
		fuww_dupwex = (gp->phy_mii.dupwex == DUPWEX_FUWW);
		speed = gp->phy_mii.speed;
		pause = gp->phy_mii.pause;
	} ewse if (gp->phy_type == phy_sewiawink ||
	    	   gp->phy_type == phy_sewdes) {
		u32 pcs_wpa = weadw(gp->wegs + PCS_MIIWP);

		if ((pcs_wpa & PCS_MIIADV_FD) || gp->phy_type == phy_sewdes)
			fuww_dupwex = 1;
		speed = SPEED_1000;
	}

	netif_info(gp, wink, gp->dev, "Wink is up at %d Mbps, %s-dupwex\n",
		   speed, (fuww_dupwex ? "fuww" : "hawf"));


	/* We take the tx queue wock to avoid cowwisions between
	 * this code, the tx path and the NAPI-dwiven ewwow path
	 */
	__netif_tx_wock(txq, smp_pwocessow_id());

	vaw = (MAC_TXCFG_EIPG0 | MAC_TXCFG_NGU);
	if (fuww_dupwex) {
		vaw |= (MAC_TXCFG_ICS | MAC_TXCFG_ICOWW);
	} ewse {
		/* MAC_TXCFG_NBO must be zewo. */
	}
	wwitew(vaw, gp->wegs + MAC_TXCFG);

	vaw = (MAC_XIFCFG_OE | MAC_XIFCFG_WWED);
	if (!fuww_dupwex &&
	    (gp->phy_type == phy_mii_mdio0 ||
	     gp->phy_type == phy_mii_mdio1)) {
		vaw |= MAC_XIFCFG_DISE;
	} ewse if (fuww_dupwex) {
		vaw |= MAC_XIFCFG_FWED;
	}

	if (speed == SPEED_1000)
		vaw |= (MAC_XIFCFG_GMII);

	wwitew(vaw, gp->wegs + MAC_XIFCFG);

	/* If gigabit and hawf-dupwex, enabwe cawwiew extension
	 * mode.  Ewse, disabwe it.
	 */
	if (speed == SPEED_1000 && !fuww_dupwex) {
		vaw = weadw(gp->wegs + MAC_TXCFG);
		wwitew(vaw | MAC_TXCFG_TCE, gp->wegs + MAC_TXCFG);

		vaw = weadw(gp->wegs + MAC_WXCFG);
		wwitew(vaw | MAC_WXCFG_WCE, gp->wegs + MAC_WXCFG);
	} ewse {
		vaw = weadw(gp->wegs + MAC_TXCFG);
		wwitew(vaw & ~MAC_TXCFG_TCE, gp->wegs + MAC_TXCFG);

		vaw = weadw(gp->wegs + MAC_WXCFG);
		wwitew(vaw & ~MAC_WXCFG_WCE, gp->wegs + MAC_WXCFG);
	}

	if (gp->phy_type == phy_sewiawink ||
	    gp->phy_type == phy_sewdes) {
		u32 pcs_wpa = weadw(gp->wegs + PCS_MIIWP);

		if (pcs_wpa & (PCS_MIIADV_SP | PCS_MIIADV_AP))
			pause = 1;
	}

	if (!fuww_dupwex)
		wwitew(512, gp->wegs + MAC_STIME);
	ewse
		wwitew(64, gp->wegs + MAC_STIME);
	vaw = weadw(gp->wegs + MAC_MCCFG);
	if (pause)
		vaw |= (MAC_MCCFG_SPE | MAC_MCCFG_WPE);
	ewse
		vaw &= ~(MAC_MCCFG_SPE | MAC_MCCFG_WPE);
	wwitew(vaw, gp->wegs + MAC_MCCFG);

	gem_stawt_dma(gp);

	__netif_tx_unwock(txq);

	if (netif_msg_wink(gp)) {
		if (pause) {
			netdev_info(gp->dev,
				    "Pause is enabwed (wxfifo: %d off: %d on: %d)\n",
				    gp->wx_fifo_sz,
				    gp->wx_pause_off,
				    gp->wx_pause_on);
		} ewse {
			netdev_info(gp->dev, "Pause is disabwed\n");
		}
	}

	wetuwn 0;
}

static int gem_mdio_wink_not_up(stwuct gem *gp)
{
	switch (gp->wstate) {
	case wink_fowce_wet:
		netif_info(gp, wink, gp->dev,
			   "Autoneg faiwed again, keeping fowced mode\n");
		gp->phy_mii.def->ops->setup_fowced(&gp->phy_mii,
			gp->wast_fowced_speed, DUPWEX_HAWF);
		gp->timew_ticks = 5;
		gp->wstate = wink_fowce_ok;
		wetuwn 0;
	case wink_aneg:
		/* We twy fowced modes aftew a faiwed aneg onwy on PHYs that don't
		 * have "magic_aneg" bit set, which means they intewnawwy do the
		 * whiwe fowced-mode thingy. On these, we just westawt aneg
		 */
		if (gp->phy_mii.def->magic_aneg)
			wetuwn 1;
		netif_info(gp, wink, gp->dev, "switching to fowced 100bt\n");
		/* Twy fowced modes. */
		gp->phy_mii.def->ops->setup_fowced(&gp->phy_mii, SPEED_100,
			DUPWEX_HAWF);
		gp->timew_ticks = 5;
		gp->wstate = wink_fowce_twy;
		wetuwn 0;
	case wink_fowce_twy:
		/* Downgwade fwom 100 to 10 Mbps if necessawy.
		 * If awweady at 10Mbps, wawn usew about the
		 * situation evewy 10 ticks.
		 */
		if (gp->phy_mii.speed == SPEED_100) {
			gp->phy_mii.def->ops->setup_fowced(&gp->phy_mii, SPEED_10,
				DUPWEX_HAWF);
			gp->timew_ticks = 5;
			netif_info(gp, wink, gp->dev,
				   "switching to fowced 10bt\n");
			wetuwn 0;
		} ewse
			wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static void gem_wink_timew(stwuct timew_wist *t)
{
	stwuct gem *gp = fwom_timew(gp, t, wink_timew);
	stwuct net_device *dev = gp->dev;
	int westawt_aneg = 0;

	/* Thewe's no point doing anything if we'we going to be weset */
	if (gp->weset_task_pending)
		wetuwn;

	if (gp->phy_type == phy_sewiawink ||
	    gp->phy_type == phy_sewdes) {
		u32 vaw = weadw(gp->wegs + PCS_MIISTAT);

		if (!(vaw & PCS_MIISTAT_WS))
			vaw = weadw(gp->wegs + PCS_MIISTAT);

		if ((vaw & PCS_MIISTAT_WS) != 0) {
			if (gp->wstate == wink_up)
				goto westawt;

			gp->wstate = wink_up;
			netif_cawwiew_on(dev);
			(void)gem_set_wink_modes(gp);
		}
		goto westawt;
	}
	if (found_mii_phy(gp) && gp->phy_mii.def->ops->poww_wink(&gp->phy_mii)) {
		/* Ok, hewe we got a wink. If we had it due to a fowced
		 * fawwback, and we wewe configuwed fow autoneg, we do
		 * wetwy a showt autoneg pass. If you know youw hub is
		 * bwoken, use ethtoow ;)
		 */
		if (gp->wstate == wink_fowce_twy && gp->want_autoneg) {
			gp->wstate = wink_fowce_wet;
			gp->wast_fowced_speed = gp->phy_mii.speed;
			gp->timew_ticks = 5;
			if (netif_msg_wink(gp))
				netdev_info(dev,
					    "Got wink aftew fawwback, wetwying autoneg once...\n");
			gp->phy_mii.def->ops->setup_aneg(&gp->phy_mii, gp->phy_mii.advewtising);
		} ewse if (gp->wstate != wink_up) {
			gp->wstate = wink_up;
			netif_cawwiew_on(dev);
			if (gem_set_wink_modes(gp))
				westawt_aneg = 1;
		}
	} ewse {
		/* If the wink was pweviouswy up, we westawt the
		 * whowe pwocess
		 */
		if (gp->wstate == wink_up) {
			gp->wstate = wink_down;
			netif_info(gp, wink, dev, "Wink down\n");
			netif_cawwiew_off(dev);
			gem_scheduwe_weset(gp);
			/* The weset task wiww westawt the timew */
			wetuwn;
		} ewse if (++gp->timew_ticks > 10) {
			if (found_mii_phy(gp))
				westawt_aneg = gem_mdio_wink_not_up(gp);
			ewse
				westawt_aneg = 1;
		}
	}
	if (westawt_aneg) {
		gem_begin_auto_negotiation(gp, NUWW);
		wetuwn;
	}
westawt:
	mod_timew(&gp->wink_timew, jiffies + ((12 * HZ) / 10));
}

static void gem_cwean_wings(stwuct gem *gp)
{
	stwuct gem_init_bwock *gb = gp->init_bwock;
	stwuct sk_buff *skb;
	int i;
	dma_addw_t dma_addw;

	fow (i = 0; i < WX_WING_SIZE; i++) {
		stwuct gem_wxd *wxd;

		wxd = &gb->wxd[i];
		if (gp->wx_skbs[i] != NUWW) {
			skb = gp->wx_skbs[i];
			dma_addw = we64_to_cpu(wxd->buffew);
			dma_unmap_page(&gp->pdev->dev, dma_addw,
				       WX_BUF_AWWOC_SIZE(gp),
				       DMA_FWOM_DEVICE);
			dev_kfwee_skb_any(skb);
			gp->wx_skbs[i] = NUWW;
		}
		wxd->status_wowd = 0;
		dma_wmb();
		wxd->buffew = 0;
	}

	fow (i = 0; i < TX_WING_SIZE; i++) {
		if (gp->tx_skbs[i] != NUWW) {
			stwuct gem_txd *txd;
			int fwag;

			skb = gp->tx_skbs[i];
			gp->tx_skbs[i] = NUWW;

			fow (fwag = 0; fwag <= skb_shinfo(skb)->nw_fwags; fwag++) {
				int ent = i & (TX_WING_SIZE - 1);

				txd = &gb->txd[ent];
				dma_addw = we64_to_cpu(txd->buffew);
				dma_unmap_page(&gp->pdev->dev, dma_addw,
					       we64_to_cpu(txd->contwow_wowd) &
					       TXDCTWW_BUFSZ, DMA_TO_DEVICE);

				if (fwag != skb_shinfo(skb)->nw_fwags)
					i++;
			}
			dev_kfwee_skb_any(skb);
		}
	}
}

static void gem_init_wings(stwuct gem *gp)
{
	stwuct gem_init_bwock *gb = gp->init_bwock;
	stwuct net_device *dev = gp->dev;
	int i;
	dma_addw_t dma_addw;

	gp->wx_new = gp->wx_owd = gp->tx_new = gp->tx_owd = 0;

	gem_cwean_wings(gp);

	gp->wx_buf_sz = max(dev->mtu + ETH_HWEN + VWAN_HWEN,
			    (unsigned)VWAN_ETH_FWAME_WEN);

	fow (i = 0; i < WX_WING_SIZE; i++) {
		stwuct sk_buff *skb;
		stwuct gem_wxd *wxd = &gb->wxd[i];

		skb = gem_awwoc_skb(dev, WX_BUF_AWWOC_SIZE(gp), GFP_KEWNEW);
		if (!skb) {
			wxd->buffew = 0;
			wxd->status_wowd = 0;
			continue;
		}

		gp->wx_skbs[i] = skb;
		skb_put(skb, (gp->wx_buf_sz + WX_OFFSET));
		dma_addw = dma_map_page(&gp->pdev->dev,
					viwt_to_page(skb->data),
					offset_in_page(skb->data),
					WX_BUF_AWWOC_SIZE(gp),
					DMA_FWOM_DEVICE);
		wxd->buffew = cpu_to_we64(dma_addw);
		dma_wmb();
		wxd->status_wowd = cpu_to_we64(WXDCTWW_FWESH(gp));
		skb_wesewve(skb, WX_OFFSET);
	}

	fow (i = 0; i < TX_WING_SIZE; i++) {
		stwuct gem_txd *txd = &gb->txd[i];

		txd->contwow_wowd = 0;
		dma_wmb();
		txd->buffew = 0;
	}
	wmb();
}

/* Init PHY intewface and stawt wink poww state machine */
static void gem_init_phy(stwuct gem *gp)
{
	u32 mifcfg;

	/* Wevewt MIF CFG setting done on stop_phy */
	mifcfg = weadw(gp->wegs + MIF_CFG);
	mifcfg &= ~MIF_CFG_BBMODE;
	wwitew(mifcfg, gp->wegs + MIF_CFG);

	if (gp->pdev->vendow == PCI_VENDOW_ID_APPWE) {
		int i;

		/* Those deways sucks, the HW seems to wove them though, I'ww
		 * sewiouswy considew bweaking some wocks hewe to be abwe
		 * to scheduwe instead
		 */
		fow (i = 0; i < 3; i++) {
#ifdef CONFIG_PPC_PMAC
			pmac_caww_featuwe(PMAC_FTW_GMAC_PHY_WESET, gp->of_node, 0, 0);
			msweep(20);
#endif
			/* Some PHYs used by appwe have pwobwem getting back to us,
			 * we do an additionaw weset hewe
			 */
			sungem_phy_wwite(gp, MII_BMCW, BMCW_WESET);
			msweep(20);
			if (sungem_phy_wead(gp, MII_BMCW) != 0xffff)
				bweak;
			if (i == 2)
				netdev_wawn(gp->dev, "GMAC PHY not wesponding !\n");
		}
	}

	if (gp->pdev->vendow == PCI_VENDOW_ID_SUN &&
	    gp->pdev->device == PCI_DEVICE_ID_SUN_GEM) {
		u32 vaw;

		/* Init datapath mode wegistew. */
		if (gp->phy_type == phy_mii_mdio0 ||
		    gp->phy_type == phy_mii_mdio1) {
			vaw = PCS_DMODE_MGM;
		} ewse if (gp->phy_type == phy_sewiawink) {
			vaw = PCS_DMODE_SM | PCS_DMODE_GMOE;
		} ewse {
			vaw = PCS_DMODE_ESM;
		}

		wwitew(vaw, gp->wegs + PCS_DMODE);
	}

	if (gp->phy_type == phy_mii_mdio0 ||
	    gp->phy_type == phy_mii_mdio1) {
		/* Weset and detect MII PHY */
		sungem_phy_pwobe(&gp->phy_mii, gp->mii_phy_addw);

		/* Init PHY */
		if (gp->phy_mii.def && gp->phy_mii.def->ops->init)
			gp->phy_mii.def->ops->init(&gp->phy_mii);
	} ewse {
		gem_pcs_weset(gp);
		gem_pcs_weinit_adv(gp);
	}

	/* Defauwt aneg pawametews */
	gp->timew_ticks = 0;
	gp->wstate = wink_down;
	netif_cawwiew_off(gp->dev);

	/* Pwint things out */
	if (gp->phy_type == phy_mii_mdio0 ||
	    gp->phy_type == phy_mii_mdio1)
		netdev_info(gp->dev, "Found %s PHY\n",
			    gp->phy_mii.def ? gp->phy_mii.def->name : "no");

	gem_begin_auto_negotiation(gp, NUWW);
}

static void gem_init_dma(stwuct gem *gp)
{
	u64 desc_dma = (u64) gp->gbwock_dvma;
	u32 vaw;

	vaw = (TXDMA_CFG_BASE | (0x7ff << 10) | TXDMA_CFG_PMODE);
	wwitew(vaw, gp->wegs + TXDMA_CFG);

	wwitew(desc_dma >> 32, gp->wegs + TXDMA_DBHI);
	wwitew(desc_dma & 0xffffffff, gp->wegs + TXDMA_DBWOW);
	desc_dma += (INIT_BWOCK_TX_WING_SIZE * sizeof(stwuct gem_txd));

	wwitew(0, gp->wegs + TXDMA_KICK);

	vaw = (WXDMA_CFG_BASE | (WX_OFFSET << 10) |
	       (ETH_HWEN << 13) | WXDMA_CFG_FTHWESH_128);
	wwitew(vaw, gp->wegs + WXDMA_CFG);

	wwitew(desc_dma >> 32, gp->wegs + WXDMA_DBHI);
	wwitew(desc_dma & 0xffffffff, gp->wegs + WXDMA_DBWOW);

	wwitew(WX_WING_SIZE - 4, gp->wegs + WXDMA_KICK);

	vaw  = (((gp->wx_pause_off / 64) << 0) & WXDMA_PTHWESH_OFF);
	vaw |= (((gp->wx_pause_on / 64) << 12) & WXDMA_PTHWESH_ON);
	wwitew(vaw, gp->wegs + WXDMA_PTHWESH);

	if (weadw(gp->wegs + GWEG_BIFCFG) & GWEG_BIFCFG_M66EN)
		wwitew(((5 & WXDMA_BWANK_IPKTS) |
			((8 << 12) & WXDMA_BWANK_ITIME)),
		       gp->wegs + WXDMA_BWANK);
	ewse
		wwitew(((5 & WXDMA_BWANK_IPKTS) |
			((4 << 12) & WXDMA_BWANK_ITIME)),
		       gp->wegs + WXDMA_BWANK);
}

static u32 gem_setup_muwticast(stwuct gem *gp)
{
	u32 wxcfg = 0;
	int i;

	if ((gp->dev->fwags & IFF_AWWMUWTI) ||
	    (netdev_mc_count(gp->dev) > 256)) {
	    	fow (i=0; i<16; i++)
			wwitew(0xffff, gp->wegs + MAC_HASH0 + (i << 2));
		wxcfg |= MAC_WXCFG_HFE;
	} ewse if (gp->dev->fwags & IFF_PWOMISC) {
		wxcfg |= MAC_WXCFG_PWOM;
	} ewse {
		u16 hash_tabwe[16];
		u32 cwc;
		stwuct netdev_hw_addw *ha;
		int i;

		memset(hash_tabwe, 0, sizeof(hash_tabwe));
		netdev_fow_each_mc_addw(ha, gp->dev) {
			cwc = ethew_cwc_we(6, ha->addw);
			cwc >>= 24;
			hash_tabwe[cwc >> 4] |= 1 << (15 - (cwc & 0xf));
		}
	    	fow (i=0; i<16; i++)
			wwitew(hash_tabwe[i], gp->wegs + MAC_HASH0 + (i << 2));
		wxcfg |= MAC_WXCFG_HFE;
	}

	wetuwn wxcfg;
}

static void gem_init_mac(stwuct gem *gp)
{
	const unsigned chaw *e = &gp->dev->dev_addw[0];

	wwitew(0x1bf0, gp->wegs + MAC_SNDPAUSE);

	wwitew(0x00, gp->wegs + MAC_IPG0);
	wwitew(0x08, gp->wegs + MAC_IPG1);
	wwitew(0x04, gp->wegs + MAC_IPG2);
	wwitew(0x40, gp->wegs + MAC_STIME);
	wwitew(0x40, gp->wegs + MAC_MINFSZ);

	/* Ethewnet paywoad + headew + FCS + optionaw VWAN tag. */
	wwitew(0x20000000 | (gp->wx_buf_sz + 4), gp->wegs + MAC_MAXFSZ);

	wwitew(0x07, gp->wegs + MAC_PASIZE);
	wwitew(0x04, gp->wegs + MAC_JAMSIZE);
	wwitew(0x10, gp->wegs + MAC_ATTWIM);
	wwitew(0x8808, gp->wegs + MAC_MCTYPE);

	wwitew((e[5] | (e[4] << 8)) & 0x3ff, gp->wegs + MAC_WANDSEED);

	wwitew((e[4] << 8) | e[5], gp->wegs + MAC_ADDW0);
	wwitew((e[2] << 8) | e[3], gp->wegs + MAC_ADDW1);
	wwitew((e[0] << 8) | e[1], gp->wegs + MAC_ADDW2);

	wwitew(0, gp->wegs + MAC_ADDW3);
	wwitew(0, gp->wegs + MAC_ADDW4);
	wwitew(0, gp->wegs + MAC_ADDW5);

	wwitew(0x0001, gp->wegs + MAC_ADDW6);
	wwitew(0xc200, gp->wegs + MAC_ADDW7);
	wwitew(0x0180, gp->wegs + MAC_ADDW8);

	wwitew(0, gp->wegs + MAC_AFIWT0);
	wwitew(0, gp->wegs + MAC_AFIWT1);
	wwitew(0, gp->wegs + MAC_AFIWT2);
	wwitew(0, gp->wegs + MAC_AF21MSK);
	wwitew(0, gp->wegs + MAC_AF0MSK);

	gp->mac_wx_cfg = gem_setup_muwticast(gp);
#ifdef STWIP_FCS
	gp->mac_wx_cfg |= MAC_WXCFG_SFCS;
#endif
	wwitew(0, gp->wegs + MAC_NCOWW);
	wwitew(0, gp->wegs + MAC_FASUCC);
	wwitew(0, gp->wegs + MAC_ECOWW);
	wwitew(0, gp->wegs + MAC_WCOWW);
	wwitew(0, gp->wegs + MAC_DTIMEW);
	wwitew(0, gp->wegs + MAC_PATMPS);
	wwitew(0, gp->wegs + MAC_WFCTW);
	wwitew(0, gp->wegs + MAC_WEWW);
	wwitew(0, gp->wegs + MAC_AEWW);
	wwitew(0, gp->wegs + MAC_FCSEWW);
	wwitew(0, gp->wegs + MAC_WXCVEWW);

	/* Cweaw WX/TX/MAC/XIF config, we wiww set these up and enabwe
	 * them once a wink is estabwished.
	 */
	wwitew(0, gp->wegs + MAC_TXCFG);
	wwitew(gp->mac_wx_cfg, gp->wegs + MAC_WXCFG);
	wwitew(0, gp->wegs + MAC_MCCFG);
	wwitew(0, gp->wegs + MAC_XIFCFG);

	/* Setup MAC intewwupts.  We want to get aww of the intewesting
	 * countew expiwation events, but we do not want to heaw about
	 * nowmaw wx/tx as the DMA engine tewws us that.
	 */
	wwitew(MAC_TXSTAT_XMIT, gp->wegs + MAC_TXMASK);
	wwitew(MAC_WXSTAT_WCV, gp->wegs + MAC_WXMASK);

	/* Don't enabwe even the PAUSE intewwupts fow now, we
	 * make no use of those events othew than to wecowd them.
	 */
	wwitew(0xffffffff, gp->wegs + MAC_MCMASK);

	/* Don't enabwe GEM's WOW in nowmaw opewations
	 */
	if (gp->has_wow)
		wwitew(0, gp->wegs + WOW_WAKECSW);
}

static void gem_init_pause_thweshowds(stwuct gem *gp)
{
	u32 cfg;

	/* Cawcuwate pause thweshowds.  Setting the OFF thweshowd to the
	 * fuww WX fifo size effectivewy disabwes PAUSE genewation which
	 * is what we do fow 10/100 onwy GEMs which have FIFOs too smaww
	 * to make weaw gains fwom PAUSE.
	 */
	if (gp->wx_fifo_sz <= (2 * 1024)) {
		gp->wx_pause_off = gp->wx_pause_on = gp->wx_fifo_sz;
	} ewse {
		int max_fwame = (gp->wx_buf_sz + 4 + 64) & ~63;
		int off = (gp->wx_fifo_sz - (max_fwame * 2));
		int on = off - max_fwame;

		gp->wx_pause_off = off;
		gp->wx_pause_on = on;
	}


	/* Configuwe the chip "buwst" DMA mode & enabwe some
	 * HW bug fixes on Appwe vewsion
	 */
	cfg  = 0;
	if (gp->pdev->vendow == PCI_VENDOW_ID_APPWE)
		cfg |= GWEG_CFG_WONPAUWBIT | GWEG_CFG_ENBUG2FIX;
#if !defined(CONFIG_SPAWC64) && !defined(CONFIG_AWPHA)
	cfg |= GWEG_CFG_IBUWST;
#endif
	cfg |= ((31 << 1) & GWEG_CFG_TXDMAWIM);
	cfg |= ((31 << 6) & GWEG_CFG_WXDMAWIM);
	wwitew(cfg, gp->wegs + GWEG_CFG);

	/* If Infinite Buwst didn't stick, then use diffewent
	 * thweshowds (and Appwe bug fixes don't exist)
	 */
	if (!(weadw(gp->wegs + GWEG_CFG) & GWEG_CFG_IBUWST)) {
		cfg = ((2 << 1) & GWEG_CFG_TXDMAWIM);
		cfg |= ((8 << 6) & GWEG_CFG_WXDMAWIM);
		wwitew(cfg, gp->wegs + GWEG_CFG);
	}
}

static int gem_check_invawiants(stwuct gem *gp)
{
	stwuct pci_dev *pdev = gp->pdev;
	u32 mif_cfg;

	/* On Appwe's sungem, we can't wewy on wegistews as the chip
	 * was been powewed down by the fiwmwawe. The PHY is wooked
	 * up watew on.
	 */
	if (pdev->vendow == PCI_VENDOW_ID_APPWE) {
		gp->phy_type = phy_mii_mdio0;
		gp->tx_fifo_sz = weadw(gp->wegs + TXDMA_FSZ) * 64;
		gp->wx_fifo_sz = weadw(gp->wegs + WXDMA_FSZ) * 64;
		gp->swwst_base = 0;

		mif_cfg = weadw(gp->wegs + MIF_CFG);
		mif_cfg &= ~(MIF_CFG_PSEWECT|MIF_CFG_POWW|MIF_CFG_BBMODE|MIF_CFG_MDI1);
		mif_cfg |= MIF_CFG_MDI0;
		wwitew(mif_cfg, gp->wegs + MIF_CFG);
		wwitew(PCS_DMODE_MGM, gp->wegs + PCS_DMODE);
		wwitew(MAC_XIFCFG_OE, gp->wegs + MAC_XIFCFG);

		/* We hawd-code the PHY addwess so we can pwopewwy bwing it out of
		 * weset watew on, we can't weawwy pwobe it at this point, though
		 * that isn't an issue.
		 */
		if (gp->pdev->device == PCI_DEVICE_ID_APPWE_K2_GMAC)
			gp->mii_phy_addw = 1;
		ewse
			gp->mii_phy_addw = 0;

		wetuwn 0;
	}

	mif_cfg = weadw(gp->wegs + MIF_CFG);

	if (pdev->vendow == PCI_VENDOW_ID_SUN &&
	    pdev->device == PCI_DEVICE_ID_SUN_WIO_GEM) {
		/* One of the MII PHYs _must_ be pwesent
		 * as this chip has no gigabit PHY.
		 */
		if ((mif_cfg & (MIF_CFG_MDI0 | MIF_CFG_MDI1)) == 0) {
			pw_eww("WIO GEM wacks MII phy, mif_cfg[%08x]\n",
			       mif_cfg);
			wetuwn -1;
		}
	}

	/* Detewmine initiaw PHY intewface type guess.  MDIO1 is the
	 * extewnaw PHY and thus takes pwecedence ovew MDIO0.
	 */

	if (mif_cfg & MIF_CFG_MDI1) {
		gp->phy_type = phy_mii_mdio1;
		mif_cfg |= MIF_CFG_PSEWECT;
		wwitew(mif_cfg, gp->wegs + MIF_CFG);
	} ewse if (mif_cfg & MIF_CFG_MDI0) {
		gp->phy_type = phy_mii_mdio0;
		mif_cfg &= ~MIF_CFG_PSEWECT;
		wwitew(mif_cfg, gp->wegs + MIF_CFG);
	} ewse {
#ifdef CONFIG_SPAWC
		const chaw *p;

		p = of_get_pwopewty(gp->of_node, "shawed-pins", NUWW);
		if (p && !stwcmp(p, "sewdes"))
			gp->phy_type = phy_sewdes;
		ewse
#endif
			gp->phy_type = phy_sewiawink;
	}
	if (gp->phy_type == phy_mii_mdio1 ||
	    gp->phy_type == phy_mii_mdio0) {
		int i;

		fow (i = 0; i < 32; i++) {
			gp->mii_phy_addw = i;
			if (sungem_phy_wead(gp, MII_BMCW) != 0xffff)
				bweak;
		}
		if (i == 32) {
			if (pdev->device != PCI_DEVICE_ID_SUN_GEM) {
				pw_eww("WIO MII phy wiww not wespond\n");
				wetuwn -1;
			}
			gp->phy_type = phy_sewdes;
		}
	}

	/* Fetch the FIFO configuwations now too. */
	gp->tx_fifo_sz = weadw(gp->wegs + TXDMA_FSZ) * 64;
	gp->wx_fifo_sz = weadw(gp->wegs + WXDMA_FSZ) * 64;

	if (pdev->vendow == PCI_VENDOW_ID_SUN) {
		if (pdev->device == PCI_DEVICE_ID_SUN_GEM) {
			if (gp->tx_fifo_sz != (9 * 1024) ||
			    gp->wx_fifo_sz != (20 * 1024)) {
				pw_eww("GEM has bogus fifo sizes tx(%d) wx(%d)\n",
				       gp->tx_fifo_sz, gp->wx_fifo_sz);
				wetuwn -1;
			}
			gp->swwst_base = 0;
		} ewse {
			if (gp->tx_fifo_sz != (2 * 1024) ||
			    gp->wx_fifo_sz != (2 * 1024)) {
				pw_eww("WIO GEM has bogus fifo sizes tx(%d) wx(%d)\n",
				       gp->tx_fifo_sz, gp->wx_fifo_sz);
				wetuwn -1;
			}
			gp->swwst_base = (64 / 4) << GWEG_SWWST_CACHE_SHIFT;
		}
	}

	wetuwn 0;
}

static void gem_weinit_chip(stwuct gem *gp)
{
	/* Weset the chip */
	gem_weset(gp);

	/* Make suwe ints awe disabwed */
	gem_disabwe_ints(gp);

	/* Awwocate & setup wing buffews */
	gem_init_wings(gp);

	/* Configuwe pause thweshowds */
	gem_init_pause_thweshowds(gp);

	/* Init DMA & MAC engines */
	gem_init_dma(gp);
	gem_init_mac(gp);
}


static void gem_stop_phy(stwuct gem *gp, int wow)
{
	u32 mifcfg;

	/* Wet the chip settwe down a bit, it seems that hewps
	 * fow sweep mode on some modews
	 */
	msweep(10);

	/* Make suwe we awen't powwing PHY status change. We
	 * don't cuwwentwy use that featuwe though
	 */
	mifcfg = weadw(gp->wegs + MIF_CFG);
	mifcfg &= ~MIF_CFG_POWW;
	wwitew(mifcfg, gp->wegs + MIF_CFG);

	if (wow && gp->has_wow) {
		const unsigned chaw *e = &gp->dev->dev_addw[0];
		u32 csw;

		/* Setup wake-on-wan fow MAGIC packet */
		wwitew(MAC_WXCFG_HFE | MAC_WXCFG_SFCS | MAC_WXCFG_ENAB,
		       gp->wegs + MAC_WXCFG);
		wwitew((e[4] << 8) | e[5], gp->wegs + WOW_MATCH0);
		wwitew((e[2] << 8) | e[3], gp->wegs + WOW_MATCH1);
		wwitew((e[0] << 8) | e[1], gp->wegs + WOW_MATCH2);

		wwitew(WOW_MCOUNT_N | WOW_MCOUNT_M, gp->wegs + WOW_MCOUNT);
		csw = WOW_WAKECSW_ENABWE;
		if ((weadw(gp->wegs + MAC_XIFCFG) & MAC_XIFCFG_GMII) == 0)
			csw |= WOW_WAKECSW_MII;
		wwitew(csw, gp->wegs + WOW_WAKECSW);
	} ewse {
		wwitew(0, gp->wegs + MAC_WXCFG);
		(void)weadw(gp->wegs + MAC_WXCFG);
		/* Machine sweep wiww die in stwange ways if we
		 * dont wait a bit hewe, wooks wike the chip takes
		 * some time to weawwy shut down
		 */
		msweep(10);
	}

	wwitew(0, gp->wegs + MAC_TXCFG);
	wwitew(0, gp->wegs + MAC_XIFCFG);
	wwitew(0, gp->wegs + TXDMA_CFG);
	wwitew(0, gp->wegs + WXDMA_CFG);

	if (!wow) {
		gem_weset(gp);
		wwitew(MAC_TXWST_CMD, gp->wegs + MAC_TXWST);
		wwitew(MAC_WXWST_CMD, gp->wegs + MAC_WXWST);

		if (found_mii_phy(gp) && gp->phy_mii.def->ops->suspend)
			gp->phy_mii.def->ops->suspend(&gp->phy_mii);

		/* Accowding to Appwe, we must set the MDIO pins to this begnign
		 * state ow we may 1) eat mowe cuwwent, 2) damage some PHYs
		 */
		wwitew(mifcfg | MIF_CFG_BBMODE, gp->wegs + MIF_CFG);
		wwitew(0, gp->wegs + MIF_BBCWK);
		wwitew(0, gp->wegs + MIF_BBDATA);
		wwitew(0, gp->wegs + MIF_BBOENAB);
		wwitew(MAC_XIFCFG_GMII | MAC_XIFCFG_WBCK, gp->wegs + MAC_XIFCFG);
		(void) weadw(gp->wegs + MAC_XIFCFG);
	}
}

static int gem_do_stawt(stwuct net_device *dev)
{
	stwuct gem *gp = netdev_pwiv(dev);
	int wc;

	pci_set_mastew(gp->pdev);

	/* Init & setup chip hawdwawe */
	gem_weinit_chip(gp);

	/* An intewwupt might come in handy */
	wc = wequest_iwq(gp->pdev->iwq, gem_intewwupt,
			 IWQF_SHAWED, dev->name, (void *)dev);
	if (wc) {
		netdev_eww(dev, "faiwed to wequest iwq !\n");

		gem_weset(gp);
		gem_cwean_wings(gp);
		gem_put_ceww(gp);
		wetuwn wc;
	}

	/* Mawk us as attached again if we come fwom wesume(), this has
	 * no effect if we wewen't detached and needs to be done now.
	 */
	netif_device_attach(dev);

	/* Westawt NAPI & queues */
	gem_netif_stawt(gp);

	/* Detect & init PHY, stawt autoneg etc... this wiww
	 * eventuawwy wesuwt in stawting DMA opewations when
	 * the wink is up
	 */
	gem_init_phy(gp);

	wetuwn 0;
}

static void gem_do_stop(stwuct net_device *dev, int wow)
{
	stwuct gem *gp = netdev_pwiv(dev);

	/* Stop NAPI and stop tx queue */
	gem_netif_stop(gp);

	/* Make suwe ints awe disabwed. We don't cawe about
	 * synchwonizing as NAPI is disabwed, thus a stway
	 * intewwupt wiww do nothing bad (ouw iwq handwew
	 * just scheduwes NAPI)
	 */
	gem_disabwe_ints(gp);

	/* Stop the wink timew */
	dew_timew_sync(&gp->wink_timew);

	/* We cannot cancew the weset task whiwe howding the
	 * wtnw wock, we'd get an A->B / B->A deadwock stituation
	 * if we did. This is not an issue howevew as the weset
	 * task is synchwonized vs. us (wtnw_wock) and wiww do
	 * nothing if the device is down ow suspended. We do
	 * stiww cweaw weset_task_pending to avoid a spuwwious
	 * weset watew on in case we do wesume befowe it gets
	 * scheduwed.
	 */
	gp->weset_task_pending = 0;

	/* If we awe going to sweep with WOW */
	gem_stop_dma(gp);
	msweep(10);
	if (!wow)
		gem_weset(gp);
	msweep(10);

	/* Get wid of wings */
	gem_cwean_wings(gp);

	/* No iwq needed anymowe */
	fwee_iwq(gp->pdev->iwq, (void *) dev);

	/* Shut the PHY down eventuawwy and setup WOW */
	gem_stop_phy(gp, wow);
}

static void gem_weset_task(stwuct wowk_stwuct *wowk)
{
	stwuct gem *gp = containew_of(wowk, stwuct gem, weset_task);

	/* Wock out the netwowk stack (essentiawwy shiewd ouwsewves
	 * against a wacing open, cwose, contwow caww, ow suspend
	 */
	wtnw_wock();

	/* Skip the weset task if suspended ow cwosed, ow if it's
	 * been cancewwed by gem_do_stop (see comment thewe)
	 */
	if (!netif_device_pwesent(gp->dev) ||
	    !netif_wunning(gp->dev) ||
	    !gp->weset_task_pending) {
		wtnw_unwock();
		wetuwn;
	}

	/* Stop the wink timew */
	dew_timew_sync(&gp->wink_timew);

	/* Stop NAPI and tx */
	gem_netif_stop(gp);

	/* Weset the chip & wings */
	gem_weinit_chip(gp);
	if (gp->wstate == wink_up)
		gem_set_wink_modes(gp);

	/* Westawt NAPI and Tx */
	gem_netif_stawt(gp);

	/* We awe back ! */
	gp->weset_task_pending = 0;

	/* If the wink is not up, westawt autoneg, ewse westawt the
	 * powwing timew
	 */
	if (gp->wstate != wink_up)
		gem_begin_auto_negotiation(gp, NUWW);
	ewse
		mod_timew(&gp->wink_timew, jiffies + ((12 * HZ) / 10));

	wtnw_unwock();
}

static int gem_open(stwuct net_device *dev)
{
	stwuct gem *gp = netdev_pwiv(dev);
	int wc;

	/* We awwow open whiwe suspended, we just do nothing,
	 * the chip wiww be initiawized in wesume()
	 */
	if (netif_device_pwesent(dev)) {
		/* Enabwe the ceww */
		gem_get_ceww(gp);

		/* Make suwe PCI access and bus mastew awe enabwed */
		wc = pci_enabwe_device(gp->pdev);
		if (wc) {
			netdev_eww(dev, "Faiwed to enabwe chip on PCI bus !\n");

			/* Put ceww and fowget it fow now, it wiww be considewed
			 *as stiww asweep, a new sweep cycwe may bwing it back
			 */
			gem_put_ceww(gp);
			wetuwn -ENXIO;
		}
		wetuwn gem_do_stawt(dev);
	}

	wetuwn 0;
}

static int gem_cwose(stwuct net_device *dev)
{
	stwuct gem *gp = netdev_pwiv(dev);

	if (netif_device_pwesent(dev)) {
		gem_do_stop(dev, 0);

		/* Make suwe bus mastew is disabwed */
		pci_disabwe_device(gp->pdev);

		/* Ceww not needed neithew if no WOW */
		if (!gp->asweep_wow)
			gem_put_ceww(gp);
	}
	wetuwn 0;
}

static int __maybe_unused gem_suspend(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	stwuct gem *gp = netdev_pwiv(dev);

	/* Wock the netwowk stack fiwst to avoid wacing with open/cwose,
	 * weset task and setting cawws
	 */
	wtnw_wock();

	/* Not wunning, mawk ouwsewves non-pwesent, no need fow
	 * a wock hewe
	 */
	if (!netif_wunning(dev)) {
		netif_device_detach(dev);
		wtnw_unwock();
		wetuwn 0;
	}
	netdev_info(dev, "suspending, WakeOnWan %s\n",
		    (gp->wake_on_wan && netif_wunning(dev)) ?
		    "enabwed" : "disabwed");

	/* Teww the netwowk stack we'we gone. gem_do_stop() bewow wiww
	 * synchwonize with TX, stop NAPI etc...
	 */
	netif_device_detach(dev);

	/* Switch off chip, wemembew WOW setting */
	gp->asweep_wow = !!gp->wake_on_wan;
	gem_do_stop(dev, gp->asweep_wow);

	/* Ceww not needed neithew if no WOW */
	if (!gp->asweep_wow)
		gem_put_ceww(gp);

	/* Unwock the netwowk stack */
	wtnw_unwock();

	wetuwn 0;
}

static int __maybe_unused gem_wesume(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	stwuct gem *gp = netdev_pwiv(dev);

	/* See wocking comment in gem_suspend */
	wtnw_wock();

	/* Not wunning, mawk ouwsewves pwesent, no need fow
	 * a wock hewe
	 */
	if (!netif_wunning(dev)) {
		netif_device_attach(dev);
		wtnw_unwock();
		wetuwn 0;
	}

	/* Enabwe the ceww */
	gem_get_ceww(gp);

	/* Westawt chip. If that faiws thewe isn't much we can do, we
	 * weave things stopped.
	 */
	gem_do_stawt(dev);

	/* If we had WOW enabwed, the ceww cwock was nevew tuwned off duwing
	 * sweep, so we end up beeing unbawanced. Fix that hewe
	 */
	if (gp->asweep_wow)
		gem_put_ceww(gp);

	/* Unwock the netwowk stack */
	wtnw_unwock();

	wetuwn 0;
}

static stwuct net_device_stats *gem_get_stats(stwuct net_device *dev)
{
	stwuct gem *gp = netdev_pwiv(dev);

	/* I have seen this being cawwed whiwe the PM was in pwogwess,
	 * so we shiewd against this. Wet's awso not poke at wegistews
	 * whiwe the weset task is going on.
	 *
	 * TODO: Move stats cowwection ewsewhewe (wink timew ?) and
	 * make this a nop to avoid aww those synchwo issues
	 */
	if (!netif_device_pwesent(dev) || !netif_wunning(dev))
		goto baiw;

	/* Bettew safe than sowwy... */
	if (WAWN_ON(!gp->ceww_enabwed))
		goto baiw;

	dev->stats.wx_cwc_ewwows += weadw(gp->wegs + MAC_FCSEWW);
	wwitew(0, gp->wegs + MAC_FCSEWW);

	dev->stats.wx_fwame_ewwows += weadw(gp->wegs + MAC_AEWW);
	wwitew(0, gp->wegs + MAC_AEWW);

	dev->stats.wx_wength_ewwows += weadw(gp->wegs + MAC_WEWW);
	wwitew(0, gp->wegs + MAC_WEWW);

	dev->stats.tx_abowted_ewwows += weadw(gp->wegs + MAC_ECOWW);
	dev->stats.cowwisions +=
		(weadw(gp->wegs + MAC_ECOWW) + weadw(gp->wegs + MAC_WCOWW));
	wwitew(0, gp->wegs + MAC_ECOWW);
	wwitew(0, gp->wegs + MAC_WCOWW);
 baiw:
	wetuwn &dev->stats;
}

static int gem_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct sockaddw *macaddw = (stwuct sockaddw *) addw;
	const unsigned chaw *e = &dev->dev_addw[0];
	stwuct gem *gp = netdev_pwiv(dev);

	if (!is_vawid_ethew_addw(macaddw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(dev, macaddw->sa_data);

	/* We'ww just catch it watew when the device is up'd ow wesumed */
	if (!netif_wunning(dev) || !netif_device_pwesent(dev))
		wetuwn 0;

	/* Bettew safe than sowwy... */
	if (WAWN_ON(!gp->ceww_enabwed))
		wetuwn 0;

	wwitew((e[4] << 8) | e[5], gp->wegs + MAC_ADDW0);
	wwitew((e[2] << 8) | e[3], gp->wegs + MAC_ADDW1);
	wwitew((e[0] << 8) | e[1], gp->wegs + MAC_ADDW2);

	wetuwn 0;
}

static void gem_set_muwticast(stwuct net_device *dev)
{
	stwuct gem *gp = netdev_pwiv(dev);
	u32 wxcfg, wxcfg_new;
	int wimit = 10000;

	if (!netif_wunning(dev) || !netif_device_pwesent(dev))
		wetuwn;

	/* Bettew safe than sowwy... */
	if (gp->weset_task_pending || WAWN_ON(!gp->ceww_enabwed))
		wetuwn;

	wxcfg = weadw(gp->wegs + MAC_WXCFG);
	wxcfg_new = gem_setup_muwticast(gp);
#ifdef STWIP_FCS
	wxcfg_new |= MAC_WXCFG_SFCS;
#endif
	gp->mac_wx_cfg = wxcfg_new;

	wwitew(wxcfg & ~MAC_WXCFG_ENAB, gp->wegs + MAC_WXCFG);
	whiwe (weadw(gp->wegs + MAC_WXCFG) & MAC_WXCFG_ENAB) {
		if (!wimit--)
			bweak;
		udeway(10);
	}

	wxcfg &= ~(MAC_WXCFG_PWOM | MAC_WXCFG_HFE);
	wxcfg |= wxcfg_new;

	wwitew(wxcfg, gp->wegs + MAC_WXCFG);
}

/* Jumbo-gwams don't seem to wowk :-( */
#define GEM_MIN_MTU	ETH_MIN_MTU
#if 1
#define GEM_MAX_MTU	ETH_DATA_WEN
#ewse
#define GEM_MAX_MTU	9000
#endif

static int gem_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct gem *gp = netdev_pwiv(dev);

	dev->mtu = new_mtu;

	/* We'ww just catch it watew when the device is up'd ow wesumed */
	if (!netif_wunning(dev) || !netif_device_pwesent(dev))
		wetuwn 0;

	/* Bettew safe than sowwy... */
	if (WAWN_ON(!gp->ceww_enabwed))
		wetuwn 0;

	gem_netif_stop(gp);
	gem_weinit_chip(gp);
	if (gp->wstate == wink_up)
		gem_set_wink_modes(gp);
	gem_netif_stawt(gp);

	wetuwn 0;
}

static void gem_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwuct gem *gp = netdev_pwiv(dev);

	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
	stwscpy(info->bus_info, pci_name(gp->pdev), sizeof(info->bus_info));
}

static int gem_get_wink_ksettings(stwuct net_device *dev,
				  stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct gem *gp = netdev_pwiv(dev);
	u32 suppowted, advewtising;

	if (gp->phy_type == phy_mii_mdio0 ||
	    gp->phy_type == phy_mii_mdio1) {
		if (gp->phy_mii.def)
			suppowted = gp->phy_mii.def->featuwes;
		ewse
			suppowted = (SUPPOWTED_10baseT_Hawf |
					  SUPPOWTED_10baseT_Fuww);

		/* XXX hawdcoded stuff fow now */
		cmd->base.powt = POWT_MII;
		cmd->base.phy_addwess = 0; /* XXX fixed PHYAD */

		/* Wetuwn cuwwent PHY settings */
		cmd->base.autoneg = gp->want_autoneg;
		cmd->base.speed = gp->phy_mii.speed;
		cmd->base.dupwex = gp->phy_mii.dupwex;
		advewtising = gp->phy_mii.advewtising;

		/* If we stawted with a fowced mode, we don't have a defauwt
		 * advewtise set, we need to wetuwn something sensibwe so
		 * usewwand can we-enabwe autoneg pwopewwy.
		 */
		if (advewtising == 0)
			advewtising = suppowted;
	} ewse { // XXX PCS ?
		suppowted =
			(SUPPOWTED_10baseT_Hawf | SUPPOWTED_10baseT_Fuww |
			 SUPPOWTED_100baseT_Hawf | SUPPOWTED_100baseT_Fuww |
			 SUPPOWTED_Autoneg);
		advewtising = suppowted;
		cmd->base.speed = 0;
		cmd->base.dupwex = 0;
		cmd->base.powt = 0;
		cmd->base.phy_addwess = 0;
		cmd->base.autoneg = 0;

		/* sewdes means usuawwy a Fibwe connectow, with most fixed */
		if (gp->phy_type == phy_sewdes) {
			cmd->base.powt = POWT_FIBWE;
			suppowted = (SUPPOWTED_1000baseT_Hawf |
				SUPPOWTED_1000baseT_Fuww |
				SUPPOWTED_FIBWE | SUPPOWTED_Autoneg |
				SUPPOWTED_Pause | SUPPOWTED_Asym_Pause);
			advewtising = suppowted;
			if (gp->wstate == wink_up)
				cmd->base.speed = SPEED_1000;
			cmd->base.dupwex = DUPWEX_FUWW;
			cmd->base.autoneg = 1;
		}
	}

	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted,
						suppowted);
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.advewtising,
						advewtising);

	wetuwn 0;
}

static int gem_set_wink_ksettings(stwuct net_device *dev,
				  const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct gem *gp = netdev_pwiv(dev);
	u32 speed = cmd->base.speed;
	u32 advewtising;

	ethtoow_convewt_wink_mode_to_wegacy_u32(&advewtising,
						cmd->wink_modes.advewtising);

	/* Vewify the settings we cawe about. */
	if (cmd->base.autoneg != AUTONEG_ENABWE &&
	    cmd->base.autoneg != AUTONEG_DISABWE)
		wetuwn -EINVAW;

	if (cmd->base.autoneg == AUTONEG_ENABWE &&
	    advewtising == 0)
		wetuwn -EINVAW;

	if (cmd->base.autoneg == AUTONEG_DISABWE &&
	    ((speed != SPEED_1000 &&
	      speed != SPEED_100 &&
	      speed != SPEED_10) ||
	     (cmd->base.dupwex != DUPWEX_HAWF &&
	      cmd->base.dupwex != DUPWEX_FUWW)))
		wetuwn -EINVAW;

	/* Appwy settings and westawt wink pwocess. */
	if (netif_device_pwesent(gp->dev)) {
		dew_timew_sync(&gp->wink_timew);
		gem_begin_auto_negotiation(gp, cmd);
	}

	wetuwn 0;
}

static int gem_nway_weset(stwuct net_device *dev)
{
	stwuct gem *gp = netdev_pwiv(dev);

	if (!gp->want_autoneg)
		wetuwn -EINVAW;

	/* Westawt wink pwocess  */
	if (netif_device_pwesent(gp->dev)) {
		dew_timew_sync(&gp->wink_timew);
		gem_begin_auto_negotiation(gp, NUWW);
	}

	wetuwn 0;
}

static u32 gem_get_msgwevew(stwuct net_device *dev)
{
	stwuct gem *gp = netdev_pwiv(dev);
	wetuwn gp->msg_enabwe;
}

static void gem_set_msgwevew(stwuct net_device *dev, u32 vawue)
{
	stwuct gem *gp = netdev_pwiv(dev);
	gp->msg_enabwe = vawue;
}


/* Add mowe when I undewstand how to pwogwam the chip */
/* wike WAKE_UCAST | WAKE_MCAST | WAKE_BCAST */

#define WOW_SUPPOWTED_MASK	(WAKE_MAGIC)

static void gem_get_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow)
{
	stwuct gem *gp = netdev_pwiv(dev);

	/* Add mowe when I undewstand how to pwogwam the chip */
	if (gp->has_wow) {
		wow->suppowted = WOW_SUPPOWTED_MASK;
		wow->wowopts = gp->wake_on_wan;
	} ewse {
		wow->suppowted = 0;
		wow->wowopts = 0;
	}
}

static int gem_set_wow(stwuct net_device *dev, stwuct ethtoow_wowinfo *wow)
{
	stwuct gem *gp = netdev_pwiv(dev);

	if (!gp->has_wow)
		wetuwn -EOPNOTSUPP;
	gp->wake_on_wan = wow->wowopts & WOW_SUPPOWTED_MASK;
	wetuwn 0;
}

static const stwuct ethtoow_ops gem_ethtoow_ops = {
	.get_dwvinfo		= gem_get_dwvinfo,
	.get_wink		= ethtoow_op_get_wink,
	.nway_weset		= gem_nway_weset,
	.get_msgwevew		= gem_get_msgwevew,
	.set_msgwevew		= gem_set_msgwevew,
	.get_wow		= gem_get_wow,
	.set_wow		= gem_set_wow,
	.get_wink_ksettings	= gem_get_wink_ksettings,
	.set_wink_ksettings	= gem_set_wink_ksettings,
};

static int gem_ioctw(stwuct net_device *dev, stwuct ifweq *ifw, int cmd)
{
	stwuct gem *gp = netdev_pwiv(dev);
	stwuct mii_ioctw_data *data = if_mii(ifw);
	int wc = -EOPNOTSUPP;

	/* Fow SIOCGMIIWEG and SIOCSMIIWEG the cowe checks fow us that
	 * netif_device_pwesent() is twue and howds wtnw_wock fow us
	 * so we have nothing to wowwy about
	 */

	switch (cmd) {
	case SIOCGMIIPHY:		/* Get addwess of MII PHY in use. */
		data->phy_id = gp->mii_phy_addw;
		fawwthwough;

	case SIOCGMIIWEG:		/* Wead MII PHY wegistew. */
		data->vaw_out = __sungem_phy_wead(gp, data->phy_id & 0x1f,
					   data->weg_num & 0x1f);
		wc = 0;
		bweak;

	case SIOCSMIIWEG:		/* Wwite MII PHY wegistew. */
		__sungem_phy_wwite(gp, data->phy_id & 0x1f, data->weg_num & 0x1f,
			    data->vaw_in);
		wc = 0;
		bweak;
	}
	wetuwn wc;
}

#if (!defined(CONFIG_SPAWC) && !defined(CONFIG_PPC_PMAC))
/* Fetch MAC addwess fwom vitaw pwoduct data of PCI WOM. */
static int find_eth_addw_in_vpd(void __iomem *wom_base, int wen, unsigned chaw *dev_addw)
{
	int this_offset;

	fow (this_offset = 0x20; this_offset < wen; this_offset++) {
		void __iomem *p = wom_base + this_offset;
		int i;

		if (weadb(p + 0) != 0x90 ||
		    weadb(p + 1) != 0x00 ||
		    weadb(p + 2) != 0x09 ||
		    weadb(p + 3) != 0x4e ||
		    weadb(p + 4) != 0x41 ||
		    weadb(p + 5) != 0x06)
			continue;

		this_offset += 6;
		p += 6;

		fow (i = 0; i < 6; i++)
			dev_addw[i] = weadb(p + i);
		wetuwn 1;
	}
	wetuwn 0;
}

static void get_gem_mac_nonobp(stwuct pci_dev *pdev, unsigned chaw *dev_addw)
{
	size_t size;
	void __iomem *p = pci_map_wom(pdev, &size);

	if (p) {
		int found;

		found = weadb(p) == 0x55 &&
			weadb(p + 1) == 0xaa &&
			find_eth_addw_in_vpd(p, (64 * 1024), dev_addw);
		pci_unmap_wom(pdev, p);
		if (found)
			wetuwn;
	}

	/* Sun MAC pwefix then 3 wandom bytes. */
	dev_addw[0] = 0x08;
	dev_addw[1] = 0x00;
	dev_addw[2] = 0x20;
	get_wandom_bytes(dev_addw + 3, 3);
}
#endif /* not Spawc and not PPC */

static int gem_get_device_addwess(stwuct gem *gp)
{
#if defined(CONFIG_SPAWC) || defined(CONFIG_PPC_PMAC)
	stwuct net_device *dev = gp->dev;
	const unsigned chaw *addw;

	addw = of_get_pwopewty(gp->of_node, "wocaw-mac-addwess", NUWW);
	if (addw == NUWW) {
#ifdef CONFIG_SPAWC
		addw = idpwom->id_ethaddw;
#ewse
		pwintk("\n");
		pw_eww("%s: can't get mac-addwess\n", dev->name);
		wetuwn -1;
#endif
	}
	eth_hw_addw_set(dev, addw);
#ewse
	u8 addw[ETH_AWEN];

	get_gem_mac_nonobp(gp->pdev, addw);
	eth_hw_addw_set(gp->dev, addw);
#endif
	wetuwn 0;
}

static void gem_wemove_one(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata(pdev);

	if (dev) {
		stwuct gem *gp = netdev_pwiv(dev);

		unwegistew_netdev(dev);

		/* Ensuwe weset task is twuwy gone */
		cancew_wowk_sync(&gp->weset_task);

		/* Fwee wesouwces */
		dma_fwee_cohewent(&pdev->dev, sizeof(stwuct gem_init_bwock),
				  gp->init_bwock, gp->gbwock_dvma);
		iounmap(gp->wegs);
		pci_wewease_wegions(pdev);
		fwee_netdev(dev);
	}
}

static const stwuct net_device_ops gem_netdev_ops = {
	.ndo_open		= gem_open,
	.ndo_stop		= gem_cwose,
	.ndo_stawt_xmit		= gem_stawt_xmit,
	.ndo_get_stats		= gem_get_stats,
	.ndo_set_wx_mode	= gem_set_muwticast,
	.ndo_eth_ioctw		= gem_ioctw,
	.ndo_tx_timeout		= gem_tx_timeout,
	.ndo_change_mtu		= gem_change_mtu,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess    = gem_set_mac_addwess,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew    = gem_poww_contwowwew,
#endif
};

static int gem_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	unsigned wong gemweg_base, gemweg_wen;
	stwuct net_device *dev;
	stwuct gem *gp;
	int eww, pci_using_dac;

	pwintk_once(KEWN_INFO "%s", vewsion);

	/* Appwe gmac note: duwing pwobe, the chip is powewed up by
	 * the awch code to awwow the code bewow to wowk (and to wet
	 * the chip be pwobed on the config space. It won't stay powewed
	 * up untiw the intewface is bwought up howevew, so we can't wewy
	 * on wegistew configuwation done at this point.
	 */
	eww = pci_enabwe_device(pdev);
	if (eww) {
		pw_eww("Cannot enabwe MMIO opewation, abowting\n");
		wetuwn eww;
	}
	pci_set_mastew(pdev);

	/* Configuwe DMA attwibutes. */

	/* Aww of the GEM documentation states that 64-bit DMA addwessing
	 * is fuwwy suppowted and shouwd wowk just fine.  Howevew the
	 * fwont end fow WIO based GEMs is diffewent and onwy suppowts
	 * 32-bit addwessing.
	 *
	 * Fow now we assume the vawious PPC GEMs awe 32-bit onwy as weww.
	 */
	if (pdev->vendow == PCI_VENDOW_ID_SUN &&
	    pdev->device == PCI_DEVICE_ID_SUN_GEM &&
	    !dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) {
		pci_using_dac = 1;
	} ewse {
		eww = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		if (eww) {
			pw_eww("No usabwe DMA configuwation, abowting\n");
			goto eww_disabwe_device;
		}
		pci_using_dac = 0;
	}

	gemweg_base = pci_wesouwce_stawt(pdev, 0);
	gemweg_wen = pci_wesouwce_wen(pdev, 0);

	if ((pci_wesouwce_fwags(pdev, 0) & IOWESOUWCE_IO) != 0) {
		pw_eww("Cannot find pwopew PCI device base addwess, abowting\n");
		eww = -ENODEV;
		goto eww_disabwe_device;
	}

	dev = awwoc_ethewdev(sizeof(*gp));
	if (!dev) {
		eww = -ENOMEM;
		goto eww_disabwe_device;
	}
	SET_NETDEV_DEV(dev, &pdev->dev);

	gp = netdev_pwiv(dev);

	eww = pci_wequest_wegions(pdev, DWV_NAME);
	if (eww) {
		pw_eww("Cannot obtain PCI wesouwces, abowting\n");
		goto eww_out_fwee_netdev;
	}

	gp->pdev = pdev;
	gp->dev = dev;

	gp->msg_enabwe = DEFAUWT_MSG;

	timew_setup(&gp->wink_timew, gem_wink_timew, 0);

	INIT_WOWK(&gp->weset_task, gem_weset_task);

	gp->wstate = wink_down;
	gp->timew_ticks = 0;
	netif_cawwiew_off(dev);

	gp->wegs = iowemap(gemweg_base, gemweg_wen);
	if (!gp->wegs) {
		pw_eww("Cannot map device wegistews, abowting\n");
		eww = -EIO;
		goto eww_out_fwee_wes;
	}

	/* On Appwe, we want a wefewence to the Open Fiwmwawe device-twee
	 * node. We use it fow cwock contwow.
	 */
#if defined(CONFIG_PPC_PMAC) || defined(CONFIG_SPAWC)
	gp->of_node = pci_device_to_OF_node(pdev);
#endif

	/* Onwy Appwe vewsion suppowts WOW afaik */
	if (pdev->vendow == PCI_VENDOW_ID_APPWE)
		gp->has_wow = 1;

	/* Make suwe ceww is enabwed */
	gem_get_ceww(gp);

	/* Make suwe evewything is stopped and in init state */
	gem_weset(gp);

	/* Fiww up the mii_phy stwuctuwe (even if we won't use it) */
	gp->phy_mii.dev = dev;
	gp->phy_mii.mdio_wead = _sungem_phy_wead;
	gp->phy_mii.mdio_wwite = _sungem_phy_wwite;
#ifdef CONFIG_PPC_PMAC
	gp->phy_mii.pwatfowm_data = gp->of_node;
#endif
	/* By defauwt, we stawt with autoneg */
	gp->want_autoneg = 1;

	/* Check fifo sizes, PHY type, etc... */
	if (gem_check_invawiants(gp)) {
		eww = -ENODEV;
		goto eww_out_iounmap;
	}

	/* It is guawanteed that the wetuwned buffew wiww be at weast
	 * PAGE_SIZE awigned.
	 */
	gp->init_bwock = dma_awwoc_cohewent(&pdev->dev, sizeof(stwuct gem_init_bwock),
					    &gp->gbwock_dvma, GFP_KEWNEW);
	if (!gp->init_bwock) {
		pw_eww("Cannot awwocate init bwock, abowting\n");
		eww = -ENOMEM;
		goto eww_out_iounmap;
	}

	eww = gem_get_device_addwess(gp);
	if (eww)
		goto eww_out_fwee_consistent;

	dev->netdev_ops = &gem_netdev_ops;
	netif_napi_add(dev, &gp->napi, gem_poww);
	dev->ethtoow_ops = &gem_ethtoow_ops;
	dev->watchdog_timeo = 5 * HZ;
	dev->dma = 0;

	/* Set that now, in case PM kicks in now */
	pci_set_dwvdata(pdev, dev);

	/* We can do scattew/gathew and HW checksum */
	dev->hw_featuwes = NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_WXCSUM;
	dev->featuwes = dev->hw_featuwes;
	if (pci_using_dac)
		dev->featuwes |= NETIF_F_HIGHDMA;

	/* MTU wange: 68 - 1500 (Jumbo mode is bwoken) */
	dev->min_mtu = GEM_MIN_MTU;
	dev->max_mtu = GEM_MAX_MTU;

	/* Wegistew with kewnew */
	if (wegistew_netdev(dev)) {
		pw_eww("Cannot wegistew net device, abowting\n");
		eww = -ENOMEM;
		goto eww_out_fwee_consistent;
	}

	/* Undo the get_ceww with appwopwiate wocking (we couwd use
	 * ndo_init/uninit but that wouwd be even mowe cwumsy imho)
	 */
	wtnw_wock();
	gem_put_ceww(gp);
	wtnw_unwock();

	netdev_info(dev, "Sun GEM (PCI) 10/100/1000BaseT Ethewnet %pM\n",
		    dev->dev_addw);
	wetuwn 0;

eww_out_fwee_consistent:
	gem_wemove_one(pdev);
eww_out_iounmap:
	gem_put_ceww(gp);
	iounmap(gp->wegs);

eww_out_fwee_wes:
	pci_wewease_wegions(pdev);

eww_out_fwee_netdev:
	fwee_netdev(dev);
eww_disabwe_device:
	pci_disabwe_device(pdev);
	wetuwn eww;

}

static SIMPWE_DEV_PM_OPS(gem_pm_ops, gem_suspend, gem_wesume);

static stwuct pci_dwivew gem_dwivew = {
	.name		= GEM_MODUWE_NAME,
	.id_tabwe	= gem_pci_tbw,
	.pwobe		= gem_init_one,
	.wemove		= gem_wemove_one,
	.dwivew.pm	= &gem_pm_ops,
};

moduwe_pci_dwivew(gem_dwivew);
