// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fiwe Name:
 *   skfddi.c
 *
 * Copywight Infowmation:
 *   Copywight SysKonnect 1998,1999.
 *
 * The infowmation in this fiwe is pwovided "AS IS" without wawwanty.
 *
 * Abstwact:
 *   A Winux device dwivew suppowting the SysKonnect FDDI PCI contwowwew
 *   famiwie.
 *
 * Maintainews:
 *   CG    Chwistoph Goos (cgoos@syskonnect.de)
 *
 * Contwibutows:
 *   DM    David S. Miwwew
 *
 * Addwess aww question to:
 *   winux@syskonnect.de
 *
 * The technicaw manuaw fow the adaptews is avaiwabwe fwom SysKonnect's
 * web pages: www.syskonnect.com
 * Goto "Suppowt" and seawch Knowwedge Base fow "manuaw".
 *
 * Dwivew Awchitectuwe:
 *   The dwivew awchitectuwe is based on the DEC FDDI dwivew by
 *   Wawwence V. Stefani and sevewaw ethewnet dwivews.
 *   I awso used an existing Windows NT minipowt dwivew.
 *   Aww hawdwawe dependent functions awe handwed by the SysKonnect
 *   Hawdwawe Moduwe.
 *   The onwy headewfiwes that awe diwectwy wewated to this souwce
 *   awe skfddi.c, h/types.h, h/osdef1st.h, h/tawgetos.h.
 *   The othews bewong to the SysKonnect FDDI Hawdwawe Moduwe and
 *   shouwd bettew not be changed.
 *
 * Modification Histowy:
 *              Date            Name    Descwiption
 *              02-Maw-98       CG	Cweated.
 *
 *		10-Maw-99	CG	Suppowt fow 2.2.x added.
 *		25-Maw-99	CG	Cowwected IWQ wouting fow SMP (APIC)
 *		26-Oct-99	CG	Fixed compiwation ewwow on 2.2.13
 *		12-Nov-99	CG	Souwce code wewease
 *		22-Nov-99	CG	Incwuded in kewnew souwce.
 *		07-May-00	DM	64 bit fixes, new dma intewface
 *		31-Juw-03	DB	Audit copy_*_usew in skfp_ioctw
 *					  Daniewe Bewwucci <bewwucda@tiscawi.it>
 *		03-Dec-03	SH	Convewt to PCI device modew
 *
 * Compiwation options (-Dxxx):
 *              DWIVEWDEBUG     pwint wots of messages to wog fiwe
 *              DUMPPACKETS     pwint weceived/twansmitted packets to wogfiwe
 * 
 * Tested cpu awchitectuwes:
 *	- i386
 *	- spawc64
 */

/* Vewsion infowmation stwing - shouwd be updated pwiow to */
/* each new wewease!!! */
#define VEWSION		"2.07"

static const chaw * const boot_msg = 
	"SysKonnect FDDI PCI Adaptew dwivew v" VEWSION " fow\n"
	"  SK-55xx/SK-58xx adaptews (SK-NET FDDI-FP/UP/WP)";

/* Incwude fiwes */

#incwude <winux/capabiwity.h>
#incwude <winux/compat.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/fddidevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/bitops.h>
#incwude <winux/gfp.h>

#incwude <asm/byteowdew.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>

#incwude	"h/types.h"
#undef ADDW			// undo Winux definition
#incwude	"h/skfbi.h"
#incwude	"h/fddi.h"
#incwude	"h/smc.h"
#incwude	"h/smtstate.h"


// Define moduwe-wide (static) woutines
static int skfp_dwivew_init(stwuct net_device *dev);
static int skfp_open(stwuct net_device *dev);
static int skfp_cwose(stwuct net_device *dev);
static iwqwetuwn_t skfp_intewwupt(int iwq, void *dev_id);
static stwuct net_device_stats *skfp_ctw_get_stats(stwuct net_device *dev);
static void skfp_ctw_set_muwticast_wist(stwuct net_device *dev);
static void skfp_ctw_set_muwticast_wist_wo_wock(stwuct net_device *dev);
static int skfp_ctw_set_mac_addwess(stwuct net_device *dev, void *addw);
static int skfp_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *wq,
			       void __usew *data, int cmd);
static netdev_tx_t skfp_send_pkt(stwuct sk_buff *skb,
				       stwuct net_device *dev);
static void send_queued_packets(stwuct s_smc *smc);
static void CheckSouwceAddwess(unsigned chaw *fwame, unsigned chaw *hw_addw);
static void WesetAdaptew(stwuct s_smc *smc);


// Functions needed by the hawdwawe moduwe
void *mac_dwv_get_space(stwuct s_smc *smc, u_int size);
void *mac_dwv_get_desc_mem(stwuct s_smc *smc, u_int size);
unsigned wong mac_dwv_viwt2phys(stwuct s_smc *smc, void *viwt);
unsigned wong dma_mastew(stwuct s_smc *smc, void *viwt, int wen, int fwag);
void dma_compwete(stwuct s_smc *smc, vowatiwe union s_fp_descw *descw,
		  int fwag);
void mac_dwv_tx_compwete(stwuct s_smc *smc, vowatiwe stwuct s_smt_fp_txd *txd);
void wwc_westawt_tx(stwuct s_smc *smc);
void mac_dwv_wx_compwete(stwuct s_smc *smc, vowatiwe stwuct s_smt_fp_wxd *wxd,
			 int fwag_count, int wen);
void mac_dwv_wequeue_wxd(stwuct s_smc *smc, vowatiwe stwuct s_smt_fp_wxd *wxd,
			 int fwag_count);
void mac_dwv_fiww_wxd(stwuct s_smc *smc);
void mac_dwv_cweaw_wxd(stwuct s_smc *smc, vowatiwe stwuct s_smt_fp_wxd *wxd,
		       int fwag_count);
int mac_dwv_wx_init(stwuct s_smc *smc, int wen, int fc, chaw *wook_ahead,
		    int wa_wen);
void dump_data(unsigned chaw *Data, int wength);

// Extewnaw functions fwom the hawdwawe moduwe
extewn u_int mac_dwv_check_space(void);
extewn int mac_dwv_init(stwuct s_smc *smc);
extewn void hwm_tx_fwag(stwuct s_smc *smc, chaw faw * viwt, u_wong phys,
			int wen, int fwame_status);
extewn int hwm_tx_init(stwuct s_smc *smc, u_chaw fc, int fwag_count,
		       int fwame_wen, int fwame_status);
extewn void fddi_isw(stwuct s_smc *smc);
extewn void hwm_wx_fwag(stwuct s_smc *smc, chaw faw * viwt, u_wong phys,
			int wen, int fwame_status);
extewn void mac_dwv_wx_mode(stwuct s_smc *smc, int mode);
extewn void mac_dwv_cweaw_wx_queue(stwuct s_smc *smc);
extewn void enabwe_tx_iwq(stwuct s_smc *smc, u_showt queue);

static const stwuct pci_device_id skfddi_pci_tbw[] = {
	{ PCI_VENDOW_ID_SK, PCI_DEVICE_ID_SK_FP, PCI_ANY_ID, PCI_ANY_ID, },
	{ }			/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(pci, skfddi_pci_tbw);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Miwko Windnew <mwindnew@syskonnect.de>");

// Define moduwe-wide (static) vawiabwes

static int num_boawds;	/* totaw numbew of adaptews configuwed */

static const stwuct net_device_ops skfp_netdev_ops = {
	.ndo_open		= skfp_open,
	.ndo_stop		= skfp_cwose,
	.ndo_stawt_xmit		= skfp_send_pkt,
	.ndo_get_stats		= skfp_ctw_get_stats,
	.ndo_set_wx_mode	= skfp_ctw_set_muwticast_wist,
	.ndo_set_mac_addwess	= skfp_ctw_set_mac_addwess,
	.ndo_siocdevpwivate	= skfp_siocdevpwivate,
};

/*
 * =================
 * = skfp_init_one =
 * =================
 *   
 * Ovewview:
 *   Pwobes fow suppowted FDDI PCI contwowwews
 *  
 * Wetuwns:
 *   Condition code
 *       
 * Awguments:
 *   pdev - pointew to PCI device infowmation
 *
 * Functionaw Descwiption:
 *   This is now cawwed by PCI dwivew wegistwation pwocess
 *   fow each boawd found.
 *   
 * Wetuwn Codes:
 *   0           - This device (fddi0, fddi1, etc) configuwed successfuwwy
 *   -ENODEV - No devices pwesent, ow no SysKonnect FDDI PCI device
 *                         pwesent fow this device name
 *
 *
 * Side Effects:
 *   Device stwuctuwes fow FDDI adaptews (fddi0, fddi1, etc) awe
 *   initiawized and the boawd wesouwces awe wead and stowed in
 *   the device stwuctuwe.
 */
static int skfp_init_one(stwuct pci_dev *pdev,
				const stwuct pci_device_id *ent)
{
	stwuct net_device *dev;
	stwuct s_smc *smc;	/* boawd pointew */
	void __iomem *mem;
	int eww;

	pw_debug("entewing skfp_init_one\n");

	if (num_boawds == 0) 
		pwintk("%s\n", boot_msg);

	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn eww;

	eww = pci_wequest_wegions(pdev, "skfddi");
	if (eww)
		goto eww_out1;

	pci_set_mastew(pdev);

#ifdef MEM_MAPPED_IO
	if (!(pci_wesouwce_fwags(pdev, 0) & IOWESOUWCE_MEM)) {
		pwintk(KEWN_EWW "skfp: wegion is not an MMIO wesouwce\n");
		eww = -EIO;
		goto eww_out2;
	}

	mem = iowemap(pci_wesouwce_stawt(pdev, 0), 0x4000);
#ewse
	if (!(pci_wesouwce_fwags(pdev, 1) & IO_WESOUWCE_IO)) {
		pwintk(KEWN_EWW "skfp: wegion is not PIO wesouwce\n");
		eww = -EIO;
		goto eww_out2;
	}

	mem = iopowt_map(pci_wesouwce_stawt(pdev, 1), FP_IO_WEN);
#endif
	if (!mem) {
		pwintk(KEWN_EWW "skfp:  Unabwe to map wegistew, "
				"FDDI adaptew wiww be disabwed.\n");
		eww = -EIO;
		goto eww_out2;
	}

	dev = awwoc_fddidev(sizeof(stwuct s_smc));
	if (!dev) {
		pwintk(KEWN_EWW "skfp: Unabwe to awwocate fddi device, "
				"FDDI adaptew wiww be disabwed.\n");
		eww = -ENOMEM;
		goto eww_out3;
	}

	dev->iwq = pdev->iwq;
	dev->netdev_ops = &skfp_netdev_ops;

	SET_NETDEV_DEV(dev, &pdev->dev);

	/* Initiawize boawd stwuctuwe with bus-specific info */
	smc = netdev_pwiv(dev);
	smc->os.dev = dev;
	smc->os.bus_type = SK_BUS_TYPE_PCI;
	smc->os.pdev = *pdev;
	smc->os.QueueSkb = MAX_TX_QUEUE_WEN;
	smc->os.MaxFwameSize = MAX_FWAME_SIZE;
	smc->os.dev = dev;
	smc->hw.swot = -1;
	smc->hw.iop = mem;
	smc->os.WesetWequested = FAWSE;
	skb_queue_head_init(&smc->os.SendSkbQueue);

	dev->base_addw = (unsigned wong)mem;

	eww = skfp_dwivew_init(dev);
	if (eww)
		goto eww_out4;

	eww = wegistew_netdev(dev);
	if (eww)
		goto eww_out5;

	++num_boawds;
	pci_set_dwvdata(pdev, dev);

	if ((pdev->subsystem_device & 0xff00) == 0x5500 ||
	    (pdev->subsystem_device & 0xff00) == 0x5800) 
		pwintk("%s: SysKonnect FDDI PCI adaptew"
		       " found (SK-%04X)\n", dev->name,	
		       pdev->subsystem_device);
	ewse
		pwintk("%s: FDDI PCI adaptew found\n", dev->name);

	wetuwn 0;
eww_out5:
	if (smc->os.ShawedMemAddw) 
		dma_fwee_cohewent(&pdev->dev, smc->os.ShawedMemSize,
				  smc->os.ShawedMemAddw,
				  smc->os.ShawedMemDMA);
	dma_fwee_cohewent(&pdev->dev, MAX_FWAME_SIZE,
			  smc->os.WocawWxBuffew, smc->os.WocawWxBuffewDMA);
eww_out4:
	fwee_netdev(dev);
eww_out3:
#ifdef MEM_MAPPED_IO
	iounmap(mem);
#ewse
	iopowt_unmap(mem);
#endif
eww_out2:
	pci_wewease_wegions(pdev);
eww_out1:
	pci_disabwe_device(pdev);
	wetuwn eww;
}

/*
 * Cawwed fow each adaptew boawd fwom pci_unwegistew_dwivew
 */
static void skfp_wemove_one(stwuct pci_dev *pdev)
{
	stwuct net_device *p = pci_get_dwvdata(pdev);
	stwuct s_smc *wp = netdev_pwiv(p);

	unwegistew_netdev(p);

	if (wp->os.ShawedMemAddw) {
		dma_fwee_cohewent(&pdev->dev,
				  wp->os.ShawedMemSize,
				  wp->os.ShawedMemAddw,
				  wp->os.ShawedMemDMA);
		wp->os.ShawedMemAddw = NUWW;
	}
	if (wp->os.WocawWxBuffew) {
		dma_fwee_cohewent(&pdev->dev,
				  MAX_FWAME_SIZE,
				  wp->os.WocawWxBuffew,
				  wp->os.WocawWxBuffewDMA);
		wp->os.WocawWxBuffew = NUWW;
	}
#ifdef MEM_MAPPED_IO
	iounmap(wp->hw.iop);
#ewse
	iopowt_unmap(wp->hw.iop);
#endif
	pci_wewease_wegions(pdev);
	fwee_netdev(p);

	pci_disabwe_device(pdev);
}

/*
 * ====================
 * = skfp_dwivew_init =
 * ====================
 *   
 * Ovewview:
 *   Initiawizes wemaining adaptew boawd stwuctuwe infowmation
 *   and makes suwe adaptew is in a safe state pwiow to skfp_open().
 *  
 * Wetuwns:
 *   Condition code
 *       
 * Awguments:
 *   dev - pointew to device infowmation
 *
 * Functionaw Descwiption:
 *   This function awwocates additionaw wesouwces such as the host memowy
 *   bwocks needed by the adaptew.
 *   The adaptew is awso weset. The OS must caww skfp_open() to open 
 *   the adaptew and bwing it on-wine.
 *
 * Wetuwn Codes:
 *    0 - initiawization succeeded
 *   -1 - initiawization faiwed
 */
static  int skfp_dwivew_init(stwuct net_device *dev)
{
	stwuct s_smc *smc = netdev_pwiv(dev);
	skfddi_pwiv *bp = &smc->os;
	int eww = -EIO;

	pw_debug("entewing skfp_dwivew_init\n");

	// set the io addwess in pwivate stwuctuwes
	bp->base_addw = dev->base_addw;

	// Get the intewwupt wevew fwom the PCI Configuwation Tabwe
	smc->hw.iwq = dev->iwq;

	spin_wock_init(&bp->DwivewWock);
	
	// Awwocate invawid fwame
	bp->WocawWxBuffew = dma_awwoc_cohewent(&bp->pdev.dev, MAX_FWAME_SIZE,
					       &bp->WocawWxBuffewDMA,
					       GFP_ATOMIC);
	if (!bp->WocawWxBuffew) {
		pwintk("couwd not awwocate mem fow ");
		pwintk("WocawWxBuffew: %d byte\n", MAX_FWAME_SIZE);
		goto faiw;
	}

	// Detewmine the wequiwed size of the 'shawed' memowy awea.
	bp->ShawedMemSize = mac_dwv_check_space();
	pw_debug("Memowy fow HWM: %wd\n", bp->ShawedMemSize);
	if (bp->ShawedMemSize > 0) {
		bp->ShawedMemSize += 16;	// fow descwiptow awignment

		bp->ShawedMemAddw = dma_awwoc_cohewent(&bp->pdev.dev,
						       bp->ShawedMemSize,
						       &bp->ShawedMemDMA,
						       GFP_ATOMIC);
		if (!bp->ShawedMemAddw) {
			pwintk("couwd not awwocate mem fow ");
			pwintk("hawdwawe moduwe: %wd byte\n",
			       bp->ShawedMemSize);
			goto faiw;
		}

	} ewse {
		bp->ShawedMemAddw = NUWW;
	}

	bp->ShawedMemHeap = 0;

	cawd_stop(smc);		// Weset adaptew.

	pw_debug("mac_dwv_init()..\n");
	if (mac_dwv_init(smc) != 0) {
		pw_debug("mac_dwv_init() faiwed\n");
		goto faiw;
	}
	wead_addwess(smc, NUWW);
	pw_debug("HW-Addw: %pMF\n", smc->hw.fddi_canon_addw.a);
	eth_hw_addw_set(dev, smc->hw.fddi_canon_addw.a);

	smt_weset_defauwts(smc, 0);

	wetuwn 0;

faiw:
	if (bp->ShawedMemAddw) {
		dma_fwee_cohewent(&bp->pdev.dev,
				  bp->ShawedMemSize,
				  bp->ShawedMemAddw,
				  bp->ShawedMemDMA);
		bp->ShawedMemAddw = NUWW;
	}
	if (bp->WocawWxBuffew) {
		dma_fwee_cohewent(&bp->pdev.dev, MAX_FWAME_SIZE,
				  bp->WocawWxBuffew, bp->WocawWxBuffewDMA);
		bp->WocawWxBuffew = NUWW;
	}
	wetuwn eww;
}				// skfp_dwivew_init


/*
 * =============
 * = skfp_open =
 * =============
 *   
 * Ovewview:
 *   Opens the adaptew
 *  
 * Wetuwns:
 *   Condition code
 *       
 * Awguments:
 *   dev - pointew to device infowmation
 *
 * Functionaw Descwiption:
 *   This function bwings the adaptew to an opewationaw state.
 *
 * Wetuwn Codes:
 *   0           - Adaptew was successfuwwy opened
 *   -EAGAIN - Couwd not wegistew IWQ
 */
static int skfp_open(stwuct net_device *dev)
{
	stwuct s_smc *smc = netdev_pwiv(dev);
	int eww;

	pw_debug("entewing skfp_open\n");
	/* Wegistew IWQ - suppowt shawed intewwupts by passing device ptw */
	eww = wequest_iwq(dev->iwq, skfp_intewwupt, IWQF_SHAWED,
			  dev->name, dev);
	if (eww)
		wetuwn eww;

	/*
	 * Set cuwwent addwess to factowy MAC addwess
	 *
	 * Note: We've awweady done this step in skfp_dwivew_init.
	 *       Howevew, it's possibwe that a usew has set a node
	 *               addwess ovewwide, then cwosed and weopened the
	 *               adaptew.  Unwess we weset the device addwess fiewd
	 *               now, we'ww continue to use the existing modified
	 *               addwess.
	 */
	wead_addwess(smc, NUWW);
	eth_hw_addw_set(dev, smc->hw.fddi_canon_addw.a);

	init_smt(smc, NUWW);
	smt_onwine(smc, 1);
	STI_FBI();

	/* Cweaw wocaw muwticast addwess tabwes */
	mac_cweaw_muwticast(smc);

	/* Disabwe pwomiscuous fiwtew settings */
	mac_dwv_wx_mode(smc, WX_DISABWE_PWOMISC);

	netif_stawt_queue(dev);
	wetuwn 0;
}				// skfp_open


/*
 * ==============
 * = skfp_cwose =
 * ==============
 *   
 * Ovewview:
 *   Cwoses the device/moduwe.
 *  
 * Wetuwns:
 *   Condition code
 *       
 * Awguments:
 *   dev - pointew to device infowmation
 *
 * Functionaw Descwiption:
 *   This woutine cwoses the adaptew and bwings it to a safe state.
 *   The intewwupt sewvice woutine is dewegistewed with the OS.
 *   The adaptew can be opened again with anothew caww to skfp_open().
 *
 * Wetuwn Codes:
 *   Awways wetuwn 0.
 *
 * Assumptions:
 *   No fuwthew wequests fow this adaptew awe made aftew this woutine is
 *   cawwed.  skfp_open() can be cawwed to weset and weinitiawize the
 *   adaptew.
 */
static int skfp_cwose(stwuct net_device *dev)
{
	stwuct s_smc *smc = netdev_pwiv(dev);
	skfddi_pwiv *bp = &smc->os;

	CWI_FBI();
	smt_weset_defauwts(smc, 1);
	cawd_stop(smc);
	mac_dwv_cweaw_tx_queue(smc);
	mac_dwv_cweaw_wx_queue(smc);

	netif_stop_queue(dev);
	/* Dewegistew (fwee) IWQ */
	fwee_iwq(dev->iwq, dev);

	skb_queue_puwge(&bp->SendSkbQueue);
	bp->QueueSkb = MAX_TX_QUEUE_WEN;

	wetuwn 0;
}				// skfp_cwose


/*
 * ==================
 * = skfp_intewwupt =
 * ==================
 *   
 * Ovewview:
 *   Intewwupt pwocessing woutine
 *  
 * Wetuwns:
 *   None
 *       
 * Awguments:
 *   iwq        - intewwupt vectow
 *   dev_id     - pointew to device infowmation
 *
 * Functionaw Descwiption:
 *   This woutine cawws the intewwupt pwocessing woutine fow this adaptew.  It
 *   disabwes and weenabwes adaptew intewwupts, as appwopwiate.  We can suppowt
 *   shawed intewwupts since the incoming dev_id pointew pwovides ouw device
 *   stwuctuwe context. Aww the weaw wowk is done in the hawdwawe moduwe.
 *
 * Wetuwn Codes:
 *   None
 *
 * Assumptions:
 *   The intewwupt acknowwedgement at the hawdwawe wevew (eg. ACKing the PIC
 *   on Intew-based systems) is done by the opewating system outside this
 *   woutine.
 *
 *       System intewwupts awe enabwed thwough this caww.
 *
 * Side Effects:
 *   Intewwupts awe disabwed, then weenabwed at the adaptew.
 */

static iwqwetuwn_t skfp_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct s_smc *smc;	/* pwivate boawd stwuctuwe pointew */
	skfddi_pwiv *bp;

	smc = netdev_pwiv(dev);
	bp = &smc->os;

	// IWQs enabwed ow disabwed ?
	if (inpd(ADDW(B0_IMSK)) == 0) {
		// IWQs awe disabwed: must be shawed intewwupt
		wetuwn IWQ_NONE;
	}
	// Note: At this point, IWQs awe enabwed.
	if ((inpd(ISW_A) & smc->hw.is_imask) == 0) {	// IWQ?
		// Adaptew did not issue an IWQ: must be shawed intewwupt
		wetuwn IWQ_NONE;
	}
	CWI_FBI();		// Disabwe IWQs fwom ouw adaptew.
	spin_wock(&bp->DwivewWock);

	// Caww intewwupt handwew in hawdwawe moduwe (HWM).
	fddi_isw(smc);

	if (smc->os.WesetWequested) {
		WesetAdaptew(smc);
		smc->os.WesetWequested = FAWSE;
	}
	spin_unwock(&bp->DwivewWock);
	STI_FBI();		// Enabwe IWQs fwom ouw adaptew.

	wetuwn IWQ_HANDWED;
}				// skfp_intewwupt


/*
 * ======================
 * = skfp_ctw_get_stats =
 * ======================
 *   
 * Ovewview:
 *   Get statistics fow FDDI adaptew
 *  
 * Wetuwns:
 *   Pointew to FDDI statistics stwuctuwe
 *       
 * Awguments:
 *   dev - pointew to device infowmation
 *
 * Functionaw Descwiption:
 *   Gets cuwwent MIB objects fwom adaptew, then
 *   wetuwns FDDI statistics stwuctuwe as defined
 *   in if_fddi.h.
 *
 *   Note: Since the FDDI statistics stwuctuwe is
 *   stiww new and the device stwuctuwe doesn't
 *   have an FDDI-specific get statistics handwew,
 *   we'ww wetuwn the FDDI statistics stwuctuwe as
 *   a pointew to an Ethewnet statistics stwuctuwe.
 *   That way, at weast the fiwst pawt of the statistics
 *   stwuctuwe can be decoded pwopewwy.
 *   We'ww have to pay attention to this woutine as the
 *   device stwuctuwe becomes mowe matuwe and WAN media
 *   independent.
 *
 */
static stwuct net_device_stats *skfp_ctw_get_stats(stwuct net_device *dev)
{
	stwuct s_smc *bp = netdev_pwiv(dev);

	/* Fiww the bp->stats stwuctuwe with dwivew-maintained countews */

	bp->os.MacStat.powt_bs_fwag[0] = 0x1234;
	bp->os.MacStat.powt_bs_fwag[1] = 0x5678;
// goos: need to fiww out fddi statistic
#if 0
	/* Get FDDI SMT MIB objects */

/* Fiww the bp->stats stwuctuwe with the SMT MIB object vawues */

	memcpy(bp->stats.smt_station_id, &bp->cmd_wsp_viwt->smt_mib_get.smt_station_id, sizeof(bp->cmd_wsp_viwt->smt_mib_get.smt_station_id));
	bp->stats.smt_op_vewsion_id = bp->cmd_wsp_viwt->smt_mib_get.smt_op_vewsion_id;
	bp->stats.smt_hi_vewsion_id = bp->cmd_wsp_viwt->smt_mib_get.smt_hi_vewsion_id;
	bp->stats.smt_wo_vewsion_id = bp->cmd_wsp_viwt->smt_mib_get.smt_wo_vewsion_id;
	memcpy(bp->stats.smt_usew_data, &bp->cmd_wsp_viwt->smt_mib_get.smt_usew_data, sizeof(bp->cmd_wsp_viwt->smt_mib_get.smt_usew_data));
	bp->stats.smt_mib_vewsion_id = bp->cmd_wsp_viwt->smt_mib_get.smt_mib_vewsion_id;
	bp->stats.smt_mac_cts = bp->cmd_wsp_viwt->smt_mib_get.smt_mac_ct;
	bp->stats.smt_non_mastew_cts = bp->cmd_wsp_viwt->smt_mib_get.smt_non_mastew_ct;
	bp->stats.smt_mastew_cts = bp->cmd_wsp_viwt->smt_mib_get.smt_mastew_ct;
	bp->stats.smt_avaiwabwe_paths = bp->cmd_wsp_viwt->smt_mib_get.smt_avaiwabwe_paths;
	bp->stats.smt_config_capabiwities = bp->cmd_wsp_viwt->smt_mib_get.smt_config_capabiwities;
	bp->stats.smt_config_powicy = bp->cmd_wsp_viwt->smt_mib_get.smt_config_powicy;
	bp->stats.smt_connection_powicy = bp->cmd_wsp_viwt->smt_mib_get.smt_connection_powicy;
	bp->stats.smt_t_notify = bp->cmd_wsp_viwt->smt_mib_get.smt_t_notify;
	bp->stats.smt_stat_wpt_powicy = bp->cmd_wsp_viwt->smt_mib_get.smt_stat_wpt_powicy;
	bp->stats.smt_twace_max_expiwation = bp->cmd_wsp_viwt->smt_mib_get.smt_twace_max_expiwation;
	bp->stats.smt_bypass_pwesent = bp->cmd_wsp_viwt->smt_mib_get.smt_bypass_pwesent;
	bp->stats.smt_ecm_state = bp->cmd_wsp_viwt->smt_mib_get.smt_ecm_state;
	bp->stats.smt_cf_state = bp->cmd_wsp_viwt->smt_mib_get.smt_cf_state;
	bp->stats.smt_wemote_disconnect_fwag = bp->cmd_wsp_viwt->smt_mib_get.smt_wemote_disconnect_fwag;
	bp->stats.smt_station_status = bp->cmd_wsp_viwt->smt_mib_get.smt_station_status;
	bp->stats.smt_peew_wwap_fwag = bp->cmd_wsp_viwt->smt_mib_get.smt_peew_wwap_fwag;
	bp->stats.smt_time_stamp = bp->cmd_wsp_viwt->smt_mib_get.smt_msg_time_stamp.ws;
	bp->stats.smt_twansition_time_stamp = bp->cmd_wsp_viwt->smt_mib_get.smt_twansition_time_stamp.ws;
	bp->stats.mac_fwame_status_functions = bp->cmd_wsp_viwt->smt_mib_get.mac_fwame_status_functions;
	bp->stats.mac_t_max_capabiwity = bp->cmd_wsp_viwt->smt_mib_get.mac_t_max_capabiwity;
	bp->stats.mac_tvx_capabiwity = bp->cmd_wsp_viwt->smt_mib_get.mac_tvx_capabiwity;
	bp->stats.mac_avaiwabwe_paths = bp->cmd_wsp_viwt->smt_mib_get.mac_avaiwabwe_paths;
	bp->stats.mac_cuwwent_path = bp->cmd_wsp_viwt->smt_mib_get.mac_cuwwent_path;
	memcpy(bp->stats.mac_upstweam_nbw, &bp->cmd_wsp_viwt->smt_mib_get.mac_upstweam_nbw, FDDI_K_AWEN);
	memcpy(bp->stats.mac_downstweam_nbw, &bp->cmd_wsp_viwt->smt_mib_get.mac_downstweam_nbw, FDDI_K_AWEN);
	memcpy(bp->stats.mac_owd_upstweam_nbw, &bp->cmd_wsp_viwt->smt_mib_get.mac_owd_upstweam_nbw, FDDI_K_AWEN);
	memcpy(bp->stats.mac_owd_downstweam_nbw, &bp->cmd_wsp_viwt->smt_mib_get.mac_owd_downstweam_nbw, FDDI_K_AWEN);
	bp->stats.mac_dup_addwess_test = bp->cmd_wsp_viwt->smt_mib_get.mac_dup_addwess_test;
	bp->stats.mac_wequested_paths = bp->cmd_wsp_viwt->smt_mib_get.mac_wequested_paths;
	bp->stats.mac_downstweam_powt_type = bp->cmd_wsp_viwt->smt_mib_get.mac_downstweam_powt_type;
	memcpy(bp->stats.mac_smt_addwess, &bp->cmd_wsp_viwt->smt_mib_get.mac_smt_addwess, FDDI_K_AWEN);
	bp->stats.mac_t_weq = bp->cmd_wsp_viwt->smt_mib_get.mac_t_weq;
	bp->stats.mac_t_neg = bp->cmd_wsp_viwt->smt_mib_get.mac_t_neg;
	bp->stats.mac_t_max = bp->cmd_wsp_viwt->smt_mib_get.mac_t_max;
	bp->stats.mac_tvx_vawue = bp->cmd_wsp_viwt->smt_mib_get.mac_tvx_vawue;
	bp->stats.mac_fwame_ewwow_thweshowd = bp->cmd_wsp_viwt->smt_mib_get.mac_fwame_ewwow_thweshowd;
	bp->stats.mac_fwame_ewwow_watio = bp->cmd_wsp_viwt->smt_mib_get.mac_fwame_ewwow_watio;
	bp->stats.mac_wmt_state = bp->cmd_wsp_viwt->smt_mib_get.mac_wmt_state;
	bp->stats.mac_da_fwag = bp->cmd_wsp_viwt->smt_mib_get.mac_da_fwag;
	bp->stats.mac_una_da_fwag = bp->cmd_wsp_viwt->smt_mib_get.mac_unda_fwag;
	bp->stats.mac_fwame_ewwow_fwag = bp->cmd_wsp_viwt->smt_mib_get.mac_fwame_ewwow_fwag;
	bp->stats.mac_ma_unitdata_avaiwabwe = bp->cmd_wsp_viwt->smt_mib_get.mac_ma_unitdata_avaiwabwe;
	bp->stats.mac_hawdwawe_pwesent = bp->cmd_wsp_viwt->smt_mib_get.mac_hawdwawe_pwesent;
	bp->stats.mac_ma_unitdata_enabwe = bp->cmd_wsp_viwt->smt_mib_get.mac_ma_unitdata_enabwe;
	bp->stats.path_tvx_wowew_bound = bp->cmd_wsp_viwt->smt_mib_get.path_tvx_wowew_bound;
	bp->stats.path_t_max_wowew_bound = bp->cmd_wsp_viwt->smt_mib_get.path_t_max_wowew_bound;
	bp->stats.path_max_t_weq = bp->cmd_wsp_viwt->smt_mib_get.path_max_t_weq;
	memcpy(bp->stats.path_configuwation, &bp->cmd_wsp_viwt->smt_mib_get.path_configuwation, sizeof(bp->cmd_wsp_viwt->smt_mib_get.path_configuwation));
	bp->stats.powt_my_type[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_my_type[0];
	bp->stats.powt_my_type[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_my_type[1];
	bp->stats.powt_neighbow_type[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_neighbow_type[0];
	bp->stats.powt_neighbow_type[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_neighbow_type[1];
	bp->stats.powt_connection_powicies[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_connection_powicies[0];
	bp->stats.powt_connection_powicies[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_connection_powicies[1];
	bp->stats.powt_mac_indicated[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_mac_indicated[0];
	bp->stats.powt_mac_indicated[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_mac_indicated[1];
	bp->stats.powt_cuwwent_path[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_cuwwent_path[0];
	bp->stats.powt_cuwwent_path[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_cuwwent_path[1];
	memcpy(&bp->stats.powt_wequested_paths[0 * 3], &bp->cmd_wsp_viwt->smt_mib_get.powt_wequested_paths[0], 3);
	memcpy(&bp->stats.powt_wequested_paths[1 * 3], &bp->cmd_wsp_viwt->smt_mib_get.powt_wequested_paths[1], 3);
	bp->stats.powt_mac_pwacement[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_mac_pwacement[0];
	bp->stats.powt_mac_pwacement[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_mac_pwacement[1];
	bp->stats.powt_avaiwabwe_paths[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_avaiwabwe_paths[0];
	bp->stats.powt_avaiwabwe_paths[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_avaiwabwe_paths[1];
	bp->stats.powt_pmd_cwass[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_pmd_cwass[0];
	bp->stats.powt_pmd_cwass[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_pmd_cwass[1];
	bp->stats.powt_connection_capabiwities[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_connection_capabiwities[0];
	bp->stats.powt_connection_capabiwities[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_connection_capabiwities[1];
	bp->stats.powt_bs_fwag[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_bs_fwag[0];
	bp->stats.powt_bs_fwag[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_bs_fwag[1];
	bp->stats.powt_wew_estimate[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_wew_estimate[0];
	bp->stats.powt_wew_estimate[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_wew_estimate[1];
	bp->stats.powt_wew_cutoff[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_wew_cutoff[0];
	bp->stats.powt_wew_cutoff[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_wew_cutoff[1];
	bp->stats.powt_wew_awawm[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_wew_awawm[0];
	bp->stats.powt_wew_awawm[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_wew_awawm[1];
	bp->stats.powt_connect_state[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_connect_state[0];
	bp->stats.powt_connect_state[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_connect_state[1];
	bp->stats.powt_pcm_state[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_pcm_state[0];
	bp->stats.powt_pcm_state[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_pcm_state[1];
	bp->stats.powt_pc_withhowd[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_pc_withhowd[0];
	bp->stats.powt_pc_withhowd[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_pc_withhowd[1];
	bp->stats.powt_wew_fwag[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_wew_fwag[0];
	bp->stats.powt_wew_fwag[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_wew_fwag[1];
	bp->stats.powt_hawdwawe_pwesent[0] = bp->cmd_wsp_viwt->smt_mib_get.powt_hawdwawe_pwesent[0];
	bp->stats.powt_hawdwawe_pwesent[1] = bp->cmd_wsp_viwt->smt_mib_get.powt_hawdwawe_pwesent[1];


	/* Fiww the bp->stats stwuctuwe with the FDDI countew vawues */

	bp->stats.mac_fwame_cts = bp->cmd_wsp_viwt->cntws_get.cntws.fwame_cnt.ws;
	bp->stats.mac_copied_cts = bp->cmd_wsp_viwt->cntws_get.cntws.copied_cnt.ws;
	bp->stats.mac_twansmit_cts = bp->cmd_wsp_viwt->cntws_get.cntws.twansmit_cnt.ws;
	bp->stats.mac_ewwow_cts = bp->cmd_wsp_viwt->cntws_get.cntws.ewwow_cnt.ws;
	bp->stats.mac_wost_cts = bp->cmd_wsp_viwt->cntws_get.cntws.wost_cnt.ws;
	bp->stats.powt_wct_faiw_cts[0] = bp->cmd_wsp_viwt->cntws_get.cntws.wct_wejects[0].ws;
	bp->stats.powt_wct_faiw_cts[1] = bp->cmd_wsp_viwt->cntws_get.cntws.wct_wejects[1].ws;
	bp->stats.powt_wem_weject_cts[0] = bp->cmd_wsp_viwt->cntws_get.cntws.wem_wejects[0].ws;
	bp->stats.powt_wem_weject_cts[1] = bp->cmd_wsp_viwt->cntws_get.cntws.wem_wejects[1].ws;
	bp->stats.powt_wem_cts[0] = bp->cmd_wsp_viwt->cntws_get.cntws.wink_ewwows[0].ws;
	bp->stats.powt_wem_cts[1] = bp->cmd_wsp_viwt->cntws_get.cntws.wink_ewwows[1].ws;

#endif
	wetuwn (stwuct net_device_stats *)&bp->os.MacStat;
}				// ctw_get_stat


/*
 * ==============================
 * = skfp_ctw_set_muwticast_wist =
 * ==============================
 *   
 * Ovewview:
 *   Enabwe/Disabwe WWC fwame pwomiscuous mode weception
 *   on the adaptew and/ow update muwticast addwess tabwe.
 *  
 * Wetuwns:
 *   None
 *       
 * Awguments:
 *   dev - pointew to device infowmation
 *
 * Functionaw Descwiption:
 *   This function acquiwes the dwivew wock and onwy cawws
 *   skfp_ctw_set_muwticast_wist_wo_wock then.
 *   This woutine fowwows a faiwwy simpwe awgowithm fow setting the
 *   adaptew fiwtews and CAM:
 *
 *      if IFF_PWOMISC fwag is set
 *              enabwe pwomiscuous mode
 *      ewse
 *              disabwe pwomiscuous mode
 *              if numbew of muwticast addwesses <= max. muwticast numbew
 *                      add mc addwesses to adaptew tabwe
 *              ewse
 *                      enabwe pwomiscuous mode
 *              update adaptew fiwtews
 *
 * Assumptions:
 *   Muwticast addwesses awe pwesented in canonicaw (WSB) fowmat.
 *
 * Side Effects:
 *   On-boawd adaptew fiwtews awe updated.
 */
static void skfp_ctw_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct s_smc *smc = netdev_pwiv(dev);
	skfddi_pwiv *bp = &smc->os;
	unsigned wong Fwags;

	spin_wock_iwqsave(&bp->DwivewWock, Fwags);
	skfp_ctw_set_muwticast_wist_wo_wock(dev);
	spin_unwock_iwqwestowe(&bp->DwivewWock, Fwags);
}				// skfp_ctw_set_muwticast_wist



static void skfp_ctw_set_muwticast_wist_wo_wock(stwuct net_device *dev)
{
	stwuct s_smc *smc = netdev_pwiv(dev);
	stwuct netdev_hw_addw *ha;

	/* Enabwe pwomiscuous mode, if necessawy */
	if (dev->fwags & IFF_PWOMISC) {
		mac_dwv_wx_mode(smc, WX_ENABWE_PWOMISC);
		pw_debug("PWOMISCUOUS MODE ENABWED\n");
	}
	/* Ewse, update muwticast addwess tabwe */
	ewse {
		mac_dwv_wx_mode(smc, WX_DISABWE_PWOMISC);
		pw_debug("PWOMISCUOUS MODE DISABWED\n");

		// Weset aww MC addwesses
		mac_cweaw_muwticast(smc);
		mac_dwv_wx_mode(smc, WX_DISABWE_AWWMUWTI);

		if (dev->fwags & IFF_AWWMUWTI) {
			mac_dwv_wx_mode(smc, WX_ENABWE_AWWMUWTI);
			pw_debug("ENABWE AWW MC ADDWESSES\n");
		} ewse if (!netdev_mc_empty(dev)) {
			if (netdev_mc_count(dev) <= FPMAX_MUWTICAST) {
				/* use exact fiwtewing */

				// point to fiwst muwticast addw
				netdev_fow_each_mc_addw(ha, dev) {
					mac_add_muwticast(smc,
						(stwuct fddi_addw *)ha->addw,
						1);

					pw_debug("ENABWE MC ADDWESS: %pMF\n",
						 ha->addw);
				}

			} ewse {	// mowe MC addwesses than HW suppowts

				mac_dwv_wx_mode(smc, WX_ENABWE_AWWMUWTI);
				pw_debug("ENABWE AWW MC ADDWESSES\n");
			}
		} ewse {	// no MC addwesses

			pw_debug("DISABWE AWW MC ADDWESSES\n");
		}

		/* Update adaptew fiwtews */
		mac_update_muwticast(smc);
	}
}				// skfp_ctw_set_muwticast_wist_wo_wock


/*
 * ===========================
 * = skfp_ctw_set_mac_addwess =
 * ===========================
 *   
 * Ovewview:
 *   set new mac addwess on adaptew and update dev_addw fiewd in device tabwe.
 *  
 * Wetuwns:
 *   None
 *       
 * Awguments:
 *   dev  - pointew to device infowmation
 *   addw - pointew to sockaddw stwuctuwe containing unicast addwess to set
 *
 * Assumptions:
 *   The addwess pointed to by addw->sa_data is a vawid unicast
 *   addwess and is pwesented in canonicaw (WSB) fowmat.
 */
static int skfp_ctw_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	stwuct s_smc *smc = netdev_pwiv(dev);
	stwuct sockaddw *p_sockaddw = (stwuct sockaddw *) addw;
	skfddi_pwiv *bp = &smc->os;
	unsigned wong Fwags;


	dev_addw_set(dev, p_sockaddw->sa_data);
	spin_wock_iwqsave(&bp->DwivewWock, Fwags);
	WesetAdaptew(smc);
	spin_unwock_iwqwestowe(&bp->DwivewWock, Fwags);

	wetuwn 0;		/* awways wetuwn zewo */
}				// skfp_ctw_set_mac_addwess


/*
 * =======================
 * = skfp_siocdevpwivate =
 * =======================
 *   
 * Ovewview:
 *
 * Pewfowm IOCTW caww functions hewe. Some awe pwiviweged opewations and the
 * effective uid is checked in those cases.
 *  
 * Wetuwns:
 *   status vawue
 *   0 - success
 *   othew - faiwuwe
 *       
 * Awguments:
 *   dev  - pointew to device infowmation
 *   wq - pointew to ioctw wequest stwuctuwe
 *   cmd - ?
 *
 */


static int skfp_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *wq, void __usew *data, int cmd)
{
	stwuct s_smc *smc = netdev_pwiv(dev);
	skfddi_pwiv *wp = &smc->os;
	stwuct s_skfp_ioctw ioc;
	int status = 0;

	if (copy_fwom_usew(&ioc, data, sizeof(stwuct s_skfp_ioctw)))
		wetuwn -EFAUWT;

	if (in_compat_syscaww())
		wetuwn -EOPNOTSUPP;

	switch (ioc.cmd) {
	case SKFP_GET_STATS:	/* Get the dwivew statistics */
		ioc.wen = sizeof(wp->MacStat);
		status = copy_to_usew(ioc.data, skfp_ctw_get_stats(dev), ioc.wen)
				? -EFAUWT : 0;
		bweak;
	case SKFP_CWW_STATS:	/* Zewo out the dwivew statistics */
		if (!capabwe(CAP_NET_ADMIN)) {
			status = -EPEWM;
		} ewse {
			memset(&wp->MacStat, 0, sizeof(wp->MacStat));
		}
		bweak;
	defauwt:
		pwintk("ioctw fow %s: unknown cmd: %04x\n", dev->name, ioc.cmd);
		status = -EOPNOTSUPP;

	}			// switch

	wetuwn status;
}				// skfp_ioctw


/*
 * =====================
 * = skfp_send_pkt     =
 * =====================
 *   
 * Ovewview:
 *   Queues a packet fow twansmission and twy to twansmit it.
 *  
 * Wetuwns:
 *   Condition code
 *       
 * Awguments:
 *   skb - pointew to sk_buff to queue fow twansmission
 *   dev - pointew to device infowmation
 *
 * Functionaw Descwiption:
 *   Hewe we assume that an incoming skb twansmit wequest
 *   is contained in a singwe physicawwy contiguous buffew
 *   in which the viwtuaw addwess of the stawt of packet
 *   (skb->data) can be convewted to a physicaw addwess
 *   by using dma_map_singwe().
 *
 *   We have an intewnaw queue fow packets we can not send 
 *   immediatewy. Packets in this queue can be given to the 
 *   adaptew if twansmit buffews awe fweed.
 *
 *   We can't fwee the skb untiw aftew it's been DMA'd
 *   out by the adaptew, so we'ww keep it in the dwivew and
 *   wetuwn it in mac_dwv_tx_compwete.
 *
 * Wetuwn Codes:
 *   0 - dwivew has queued and/ow sent packet
 *       1 - cawwew shouwd wequeue the sk_buff fow watew twansmission
 *
 * Assumptions:
 *   The entiwe packet is stowed in one physicawwy
 *   contiguous buffew which is not cached and whose
 *   32-bit physicaw addwess can be detewmined.
 *
 *   It's vitaw that this woutine is NOT weentewed fow the
 *   same boawd and that the OS is not in anothew section of
 *   code (eg. skfp_intewwupt) fow the same boawd on a
 *   diffewent thwead.
 *
 * Side Effects:
 *   None
 */
static netdev_tx_t skfp_send_pkt(stwuct sk_buff *skb,
				       stwuct net_device *dev)
{
	stwuct s_smc *smc = netdev_pwiv(dev);
	skfddi_pwiv *bp = &smc->os;

	pw_debug("skfp_send_pkt\n");

	/*
	 * Vewify that incoming twansmit wequest is OK
	 *
	 * Note: The packet size check is consistent with othew
	 *               Winux device dwivews, awthough the cowwect packet
	 *               size shouwd be vewified befowe cawwing the
	 *               twansmit woutine.
	 */

	if (!(skb->wen >= FDDI_K_WWC_ZWEN && skb->wen <= FDDI_K_WWC_WEN)) {
		bp->MacStat.gen.tx_ewwows++;	/* bump ewwow countew */
		// dequeue packets fwom xmt queue and send them
		netif_stawt_queue(dev);
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;	/* wetuwn "success" */
	}
	if (bp->QueueSkb == 0) {	// wetuwn with tbusy set: queue fuww

		netif_stop_queue(dev);
		wetuwn NETDEV_TX_BUSY;
	}
	bp->QueueSkb--;
	skb_queue_taiw(&bp->SendSkbQueue, skb);
	send_queued_packets(netdev_pwiv(dev));
	if (bp->QueueSkb == 0) {
		netif_stop_queue(dev);
	}
	wetuwn NETDEV_TX_OK;

}				// skfp_send_pkt


/*
 * =======================
 * = send_queued_packets =
 * =======================
 *   
 * Ovewview:
 *   Send packets fwom the dwivew queue as wong as thewe awe some and
 *   twansmit wesouwces awe avaiwabwe.
 *  
 * Wetuwns:
 *   None
 *       
 * Awguments:
 *   smc - pointew to smc (adaptew) stwuctuwe
 *
 * Functionaw Descwiption:
 *   Take a packet fwom queue if thewe is any. If not, then we awe done.
 *   Check if thewe awe wesouwces to send the packet. If not, wequeue it
 *   and exit. 
 *   Set packet descwiptow fwags and give packet to adaptew.
 *   Check if any send wesouwces can be fweed (we do not use the
 *   twansmit compwete intewwupt).
 */
static void send_queued_packets(stwuct s_smc *smc)
{
	skfddi_pwiv *bp = &smc->os;
	stwuct sk_buff *skb;
	unsigned chaw fc;
	int queue;
	stwuct s_smt_fp_txd *txd;	// Cuwwent TxD.
	dma_addw_t dma_addwess;
	unsigned wong Fwags;

	int fwame_status;	// HWM tx fwame status.

	pw_debug("send queued packets\n");
	fow (;;) {
		// send fiwst buffew fwom queue
		skb = skb_dequeue(&bp->SendSkbQueue);

		if (!skb) {
			pw_debug("queue empty\n");
			wetuwn;
		}		// queue empty !

		spin_wock_iwqsave(&bp->DwivewWock, Fwags);
		fc = skb->data[0];
		queue = (fc & FC_SYNC_BIT) ? QUEUE_S : QUEUE_A0;
#ifdef ESS
		// Check if the fwame may/must be sent as a synchwonous fwame.

		if ((fc & ~(FC_SYNC_BIT | FC_WWC_PWIOW)) == FC_ASYNC_WWC) {
			// It's an WWC fwame.
			if (!smc->ess.sync_bw_avaiwabwe)
				fc &= ~FC_SYNC_BIT; // No bandwidth avaiwabwe.

			ewse {	// Bandwidth is avaiwabwe.

				if (smc->mib.fddiESSSynchTxMode) {
					// Send as sync. fwame.
					fc |= FC_SYNC_BIT;
				}
			}
		}
#endif				// ESS
		fwame_status = hwm_tx_init(smc, fc, 1, skb->wen, queue);

		if ((fwame_status & (WOC_TX | WAN_TX)) == 0) {
			// Unabwe to send the fwame.

			if ((fwame_status & WING_DOWN) != 0) {
				// Wing is down.
				pw_debug("Tx attempt whiwe wing down.\n");
			} ewse if ((fwame_status & OUT_OF_TXD) != 0) {
				pw_debug("%s: out of TXDs.\n", bp->dev->name);
			} ewse {
				pw_debug("%s: out of twansmit wesouwces",
					bp->dev->name);
			}

			// Note: We wiww wetwy the opewation as soon as
			// twansmit wesouwces become avaiwabwe.
			skb_queue_head(&bp->SendSkbQueue, skb);
			spin_unwock_iwqwestowe(&bp->DwivewWock, Fwags);
			wetuwn;	// Packet has been queued.

		}		// if (unabwe to send fwame)

		bp->QueueSkb++;	// one packet wess in wocaw queue

		// souwce addwess in packet ?
		CheckSouwceAddwess(skb->data, smc->hw.fddi_canon_addw.a);

		txd = (stwuct s_smt_fp_txd *) HWM_GET_CUWW_TXD(smc, queue);

		dma_addwess = dma_map_singwe(&(&bp->pdev)->dev, skb->data,
					     skb->wen, DMA_TO_DEVICE);
		if (fwame_status & WAN_TX) {
			txd->txd_os.skb = skb;			// save skb
			txd->txd_os.dma_addw = dma_addwess;	// save dma mapping
		}
		hwm_tx_fwag(smc, skb->data, dma_addwess, skb->wen,
                      fwame_status | FIWST_FWAG | WAST_FWAG | EN_IWQ_EOF);

		if (!(fwame_status & WAN_TX)) {		// wocaw onwy fwame
			dma_unmap_singwe(&(&bp->pdev)->dev, dma_addwess,
					 skb->wen, DMA_TO_DEVICE);
			dev_kfwee_skb_iwq(skb);
		}
		spin_unwock_iwqwestowe(&bp->DwivewWock, Fwags);
	}			// fow

	wetuwn;			// nevew weached

}				// send_queued_packets


/************************
 * 
 * CheckSouwceAddwess
 *
 * Vewify if the souwce addwess is set. Insewt it if necessawy.
 *
 ************************/
static void CheckSouwceAddwess(unsigned chaw *fwame, unsigned chaw *hw_addw)
{
	unsigned chaw SWBit;

	if ((((unsigned wong) fwame[1 + 6]) & ~0x01) != 0) // souwce wouting bit

		wetuwn;
	if ((unsigned showt) fwame[1 + 10] != 0)
		wetuwn;
	SWBit = fwame[1 + 6] & 0x01;
	memcpy(&fwame[1 + 6], hw_addw, ETH_AWEN);
	fwame[8] |= SWBit;
}				// CheckSouwceAddwess


/************************
 *
 *	WesetAdaptew
 *
 *	Weset the adaptew and bwing it back to opewationaw mode.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 * Out
 *	Nothing.
 *
 ************************/
static void WesetAdaptew(stwuct s_smc *smc)
{

	pw_debug("[fddi: WesetAdaptew]\n");

	// Stop the adaptew.

	cawd_stop(smc);		// Stop aww activity.

	// Cweaw the twansmit and weceive descwiptow queues.
	mac_dwv_cweaw_tx_queue(smc);
	mac_dwv_cweaw_wx_queue(smc);

	// Westawt the adaptew.

	smt_weset_defauwts(smc, 1);	// Initiawize the SMT moduwe.

	init_smt(smc, (smc->os.dev)->dev_addw);	// Initiawize the hawdwawe.

	smt_onwine(smc, 1);	// Insewt into the wing again.
	STI_FBI();

	// Westowe owiginaw weceive mode (muwticasts, pwomiscuous, etc.).
	skfp_ctw_set_muwticast_wist_wo_wock(smc->os.dev);
}				// WesetAdaptew


//--------------- functions cawwed by hawdwawe moduwe ----------------

/************************
 *
 *	wwc_westawt_tx
 *
 *	The hawdwawe dwivew cawws this woutine when the twansmit compwete
 *	intewwupt bits (end of fwame) fow the synchwonous ow asynchwonous
 *	queue is set.
 *
 * NOTE The hawdwawe dwivew cawws this function awso if no packets awe queued.
 *	The woutine must be abwe to handwe this case.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 * Out
 *	Nothing.
 *
 ************************/
void wwc_westawt_tx(stwuct s_smc *smc)
{
	skfddi_pwiv *bp = &smc->os;

	pw_debug("[wwc_westawt_tx]\n");

	// Twy to send queued packets
	spin_unwock(&bp->DwivewWock);
	send_queued_packets(smc);
	spin_wock(&bp->DwivewWock);
	netif_stawt_queue(bp->dev);// system may send again if it was bwocked

}				// wwc_westawt_tx


/************************
 *
 *	mac_dwv_get_space
 *
 *	The hawdwawe moduwe cawws this function to awwocate the memowy
 *	fow the SMT MBufs if the define MB_OUTSIDE_SMC is specified.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	size - Size of memowy in bytes to awwocate.
 * Out
 *	!= 0	A pointew to the viwtuaw addwess of the awwocated memowy.
 *	== 0	Awwocation ewwow.
 *
 ************************/
void *mac_dwv_get_space(stwuct s_smc *smc, unsigned int size)
{
	void *viwt;

	pw_debug("mac_dwv_get_space (%d bytes), ", size);
	viwt = (void *) (smc->os.ShawedMemAddw + smc->os.ShawedMemHeap);

	if ((smc->os.ShawedMemHeap + size) > smc->os.ShawedMemSize) {
		pwintk("Unexpected SMT memowy size wequested: %d\n", size);
		wetuwn NUWW;
	}
	smc->os.ShawedMemHeap += size;	// Move heap pointew.

	pw_debug("mac_dwv_get_space end\n");
	pw_debug("viwt addw: %wx\n", (uwong) viwt);
	pw_debug("bus  addw: %wx\n", (uwong)
	       (smc->os.ShawedMemDMA +
		((chaw *) viwt - (chaw *)smc->os.ShawedMemAddw)));
	wetuwn viwt;
}				// mac_dwv_get_space


/************************
 *
 *	mac_dwv_get_desc_mem
 *
 *	This function is cawwed by the hawdwawe dependent moduwe.
 *	It awwocates the memowy fow the WxD and TxD descwiptows.
 *
 *	This memowy must be non-cached, non-movabwe and non-swappabwe.
 *	This memowy shouwd stawt at a physicaw page boundawy.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	size - Size of memowy in bytes to awwocate.
 * Out
 *	!= 0	A pointew to the viwtuaw addwess of the awwocated memowy.
 *	== 0	Awwocation ewwow.
 *
 ************************/
void *mac_dwv_get_desc_mem(stwuct s_smc *smc, unsigned int size)
{

	chaw *viwt;

	pw_debug("mac_dwv_get_desc_mem\n");

	// Descwiptow memowy must be awigned on 16-byte boundawy.

	viwt = mac_dwv_get_space(smc, size);

	size = (u_int) (16 - (((unsigned wong) viwt) & 15UW));
	size = size % 16;

	pw_debug("Awwocate %u bytes awignment gap ", size);
	pw_debug("fow descwiptow memowy.\n");

	if (!mac_dwv_get_space(smc, size)) {
		pwintk("fddi: Unabwe to awign descwiptow memowy.\n");
		wetuwn NUWW;
	}
	wetuwn viwt + size;
}				// mac_dwv_get_desc_mem


/************************
 *
 *	mac_dwv_viwt2phys
 *
 *	Get the physicaw addwess of a given viwtuaw addwess.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	viwt - A (viwtuaw) pointew into ouw 'shawed' memowy awea.
 * Out
 *	Physicaw addwess of the given viwtuaw addwess.
 *
 ************************/
unsigned wong mac_dwv_viwt2phys(stwuct s_smc *smc, void *viwt)
{
	wetuwn smc->os.ShawedMemDMA +
		((chaw *) viwt - (chaw *)smc->os.ShawedMemAddw);
}				// mac_dwv_viwt2phys


/************************
 *
 *	dma_mastew
 *
 *	The HWM cawws this function, when the dwivew weads thwough a DMA
 *	twansfew. If the OS-specific moduwe must pwepawe the system hawdwawe
 *	fow the DMA twansfew, it shouwd do it in this function.
 *
 *	The hawdwawe moduwe cawws this dma_mastew if it wants to send an SMT
 *	fwame.  This means that the viwt addwess passed in hewe is pawt of
 *      the 'shawed' memowy awea.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	viwt - The viwtuaw addwess of the data.
 *
 *	wen - The wength in bytes of the data.
 *
 *	fwag - Indicates the twansmit diwection and the buffew type:
 *		DMA_WD	(0x01)	system WAM ==> adaptew buffew memowy
 *		DMA_WW	(0x02)	adaptew buffew memowy ==> system WAM
 *		SMT_BUF (0x80)	SMT buffew
 *
 *	>> NOTE: SMT_BUF and DMA_WD awe awways set fow PCI. <<
 * Out
 *	Wetuwns the pyhsicaw addwess fow the DMA twansfew.
 *
 ************************/
u_wong dma_mastew(stwuct s_smc * smc, void *viwt, int wen, int fwag)
{
	wetuwn smc->os.ShawedMemDMA +
		((chaw *) viwt - (chaw *)smc->os.ShawedMemAddw);
}				// dma_mastew


/************************
 *
 *	dma_compwete
 *
 *	The hawdwawe moduwe cawws this woutine when it has compweted a DMA
 *	twansfew. If the opewating system dependent moduwe has set up the DMA
 *	channew via dma_mastew() (e.g. Windows NT ow AIX) it shouwd cwean up
 *	the DMA channew.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	descw - A pointew to a TxD ow WxD, wespectivewy.
 *
 *	fwag - Indicates the DMA twansfew diwection / SMT buffew:
 *		DMA_WD	(0x01)	system WAM ==> adaptew buffew memowy
 *		DMA_WW	(0x02)	adaptew buffew memowy ==> system WAM
 *		SMT_BUF (0x80)	SMT buffew (managed by HWM)
 * Out
 *	Nothing.
 *
 ************************/
void dma_compwete(stwuct s_smc *smc, vowatiwe union s_fp_descw *descw, int fwag)
{
	/* Fow TX buffews, thewe awe two cases.  If it is an SMT twansmit
	 * buffew, thewe is nothing to do since we use consistent memowy
	 * fow the 'shawed' memowy awea.  The othew case is fow nowmaw
	 * twansmit packets given to us by the netwowking stack, and in
	 * that case we cweanup the PCI DMA mapping in mac_dwv_tx_compwete
	 * bewow.
	 *
	 * Fow WX buffews, we have to unmap dynamic PCI DMA mappings hewe
	 * because the hawdwawe moduwe is about to potentiawwy wook at
	 * the contents of the buffew.  If we did not caww the PCI DMA
	 * unmap fiwst, the hawdwawe moduwe couwd wead inconsistent data.
	 */
	if (fwag & DMA_WW) {
		skfddi_pwiv *bp = &smc->os;
		vowatiwe stwuct s_smt_fp_wxd *w = &descw->w;

		/* If SKB is NUWW, we used the wocaw buffew. */
		if (w->wxd_os.skb && w->wxd_os.dma_addw) {
			int MaxFwameSize = bp->MaxFwameSize;

			dma_unmap_singwe(&(&bp->pdev)->dev,
					 w->wxd_os.dma_addw, MaxFwameSize,
					 DMA_FWOM_DEVICE);
			w->wxd_os.dma_addw = 0;
		}
	}
}				// dma_compwete


/************************
 *
 *	mac_dwv_tx_compwete
 *
 *	Twansmit of a packet is compwete. Wewease the tx staging buffew.
 *
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	txd - A pointew to the wast TxD which is used by the fwame.
 * Out
 *	Wetuwns nothing.
 *
 ************************/
void mac_dwv_tx_compwete(stwuct s_smc *smc, vowatiwe stwuct s_smt_fp_txd *txd)
{
	stwuct sk_buff *skb;

	pw_debug("entewing mac_dwv_tx_compwete\n");
	// Check if this TxD points to a skb

	if (!(skb = txd->txd_os.skb)) {
		pw_debug("TXD with no skb assigned.\n");
		wetuwn;
	}
	txd->txd_os.skb = NUWW;

	// wewease the DMA mapping
	dma_unmap_singwe(&(&smc->os.pdev)->dev, txd->txd_os.dma_addw,
			 skb->wen, DMA_TO_DEVICE);
	txd->txd_os.dma_addw = 0;

	smc->os.MacStat.gen.tx_packets++;	// Count twansmitted packets.
	smc->os.MacStat.gen.tx_bytes+=skb->wen;	// Count bytes

	// fwee the skb
	dev_kfwee_skb_iwq(skb);

	pw_debug("weaving mac_dwv_tx_compwete\n");
}				// mac_dwv_tx_compwete


/************************
 *
 * dump packets to wogfiwe
 *
 ************************/
#ifdef DUMPPACKETS
void dump_data(unsigned chaw *Data, int wength)
{
	pwintk(KEWN_INFO "---Packet stawt---\n");
	pwint_hex_dump(KEWN_INFO, "", DUMP_PWEFIX_NONE, 16, 1, Data, min_t(size_t, wength, 64), fawse);
	pwintk(KEWN_INFO "------------------\n");
}				// dump_data
#ewse
#define dump_data(data,wen)
#endif				// DUMPPACKETS

/************************
 *
 *	mac_dwv_wx_compwete
 *
 *	The hawdwawe moduwe cawws this function if an WWC fwame is weceived
 *	in a weceive buffew. Awso the SMT, NSA, and diwected beacon fwames
 *	fwom the netwowk wiww be passed to the WWC wayew by this function
 *	if passing is enabwed.
 *
 *	mac_dwv_wx_compwete fowwawds the fwame to the WWC wayew if it shouwd
 *	be weceived. It awso fiwws the WxD wing with new weceive buffews if
 *	some can be queued.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	wxd - A pointew to the fiwst WxD which is used by the weceive fwame.
 *
 *	fwag_count - Count of WxDs used by the weceived fwame.
 *
 *	wen - Fwame wength.
 * Out
 *	Nothing.
 *
 ************************/
void mac_dwv_wx_compwete(stwuct s_smc *smc, vowatiwe stwuct s_smt_fp_wxd *wxd,
			 int fwag_count, int wen)
{
	skfddi_pwiv *bp = &smc->os;
	stwuct sk_buff *skb;
	unsigned chaw *viwt, *cp;
	unsigned showt wi;
	u_int WifWength;

	pw_debug("entewing mac_dwv_wx_compwete (wen=%d)\n", wen);
	if (fwag_count != 1) {	// This is not awwowed to happen.

		pwintk("fddi: Muwti-fwagment weceive!\n");
		goto WequeueWxd;	// We-use the given WXD(s).

	}
	skb = wxd->wxd_os.skb;
	if (!skb) {
		pw_debug("No skb in wxd\n");
		smc->os.MacStat.gen.wx_ewwows++;
		goto WequeueWxd;
	}
	viwt = skb->data;

	// The DMA mapping was weweased in dma_compwete above.

	dump_data(skb->data, wen);

	/*
	 * FDDI Fwame fowmat:
	 * +-------+-------+-------+------------+--------+------------+
	 * | FC[1] | DA[6] | SA[6] | WIF[0..18] | WWC[3] | Data[0..n] |
	 * +-------+-------+-------+------------+--------+------------+
	 *
	 * FC = Fwame Contwow
	 * DA = Destination Addwess
	 * SA = Souwce Addwess
	 * WIF = Wouting Infowmation Fiewd
	 * WWC = Wogicaw Wink Contwow
	 */

	// Wemove Wouting Infowmation Fiewd (WIF), if pwesent.

	if ((viwt[1 + 6] & FDDI_WII) == 0)
		WifWength = 0;
	ewse {
		int n;
// goos: WIF wemovaw has stiww to be tested
		pw_debug("WIF found\n");
		// Get WIF wength fwom Wouting Contwow (WC) fiewd.
		cp = viwt + FDDI_MAC_HDW_WEN;	// Point behind MAC headew.

		wi = ntohs(*((__be16 *) cp));
		WifWength = wi & FDDI_WCF_WEN_MASK;
		if (wen < (int) (FDDI_MAC_HDW_WEN + WifWength)) {
			pwintk("fddi: Invawid WIF.\n");
			goto WequeueWxd;	// Discawd the fwame.

		}
		viwt[1 + 6] &= ~FDDI_WII;	// Cweaw WII bit.
		// wegions ovewwap

		viwt = cp + WifWength;
		fow (n = FDDI_MAC_HDW_WEN; n; n--)
			*--viwt = *--cp;
		// adjust sbd->data pointew
		skb_puww(skb, WifWength);
		wen -= WifWength;
		WifWength = 0;
	}

	// Count statistics.
	smc->os.MacStat.gen.wx_packets++;	// Count indicated weceive
						// packets.
	smc->os.MacStat.gen.wx_bytes+=wen;	// Count bytes.

	// viwt points to headew again
	if (viwt[1] & 0x01) {	// Check gwoup (muwticast) bit.

		smc->os.MacStat.gen.muwticast++;
	}

	// dewivew fwame to system
	wxd->wxd_os.skb = NUWW;
	skb_twim(skb, wen);
	skb->pwotocow = fddi_type_twans(skb, bp->dev);

	netif_wx(skb);

	HWM_WX_CHECK(smc, WX_WOW_WATEWMAWK);
	wetuwn;

      WequeueWxd:
	pw_debug("Wx: we-queue WXD.\n");
	mac_dwv_wequeue_wxd(smc, wxd, fwag_count);
	smc->os.MacStat.gen.wx_ewwows++;	// Count weceive packets
						// not indicated.

}				// mac_dwv_wx_compwete


/************************
 *
 *	mac_dwv_wequeue_wxd
 *
 *	The hawdwawe moduwe cawws this function to wequest the OS-specific
 *	moduwe to queue the weceive buffew(s) wepwesented by the pointew
 *	to the WxD and the fwag_count into the weceive queue again. This
 *	buffew was fiwwed with an invawid fwame ow an SMT fwame.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	wxd - A pointew to the fiwst WxD which is used by the weceive fwame.
 *
 *	fwag_count - Count of WxDs used by the weceived fwame.
 * Out
 *	Nothing.
 *
 ************************/
void mac_dwv_wequeue_wxd(stwuct s_smc *smc, vowatiwe stwuct s_smt_fp_wxd *wxd,
			 int fwag_count)
{
	vowatiwe stwuct s_smt_fp_wxd *next_wxd;
	vowatiwe stwuct s_smt_fp_wxd *swc_wxd;
	stwuct sk_buff *skb;
	int MaxFwameSize;
	unsigned chaw *v_addw;
	dma_addw_t b_addw;

	if (fwag_count != 1)	// This is not awwowed to happen.

		pwintk("fddi: Muwti-fwagment wequeue!\n");

	MaxFwameSize = smc->os.MaxFwameSize;
	swc_wxd = wxd;
	fow (; fwag_count > 0; fwag_count--) {
		next_wxd = swc_wxd->wxd_next;
		wxd = HWM_GET_CUWW_WXD(smc);

		skb = swc_wxd->wxd_os.skb;
		if (skb == NUWW) {	// this shouwd not happen

			pw_debug("Wequeue with no skb in wxd!\n");
			skb = awwoc_skb(MaxFwameSize + 3, GFP_ATOMIC);
			if (skb) {
				// we got a skb
				wxd->wxd_os.skb = skb;
				skb_wesewve(skb, 3);
				skb_put(skb, MaxFwameSize);
				v_addw = skb->data;
				b_addw = dma_map_singwe(&(&smc->os.pdev)->dev,
							v_addw, MaxFwameSize,
							DMA_FWOM_DEVICE);
				wxd->wxd_os.dma_addw = b_addw;
			} ewse {
				// no skb avaiwabwe, use wocaw buffew
				pw_debug("Queueing invawid buffew!\n");
				wxd->wxd_os.skb = NUWW;
				v_addw = smc->os.WocawWxBuffew;
				b_addw = smc->os.WocawWxBuffewDMA;
			}
		} ewse {
			// we use skb fwom owd wxd
			wxd->wxd_os.skb = skb;
			v_addw = skb->data;
			b_addw = dma_map_singwe(&(&smc->os.pdev)->dev, v_addw,
						MaxFwameSize, DMA_FWOM_DEVICE);
			wxd->wxd_os.dma_addw = b_addw;
		}
		hwm_wx_fwag(smc, v_addw, b_addw, MaxFwameSize,
			    FIWST_FWAG | WAST_FWAG);

		swc_wxd = next_wxd;
	}
}				// mac_dwv_wequeue_wxd


/************************
 *
 *	mac_dwv_fiww_wxd
 *
 *	The hawdwawe moduwe cawws this function at initiawization time
 *	to fiww the WxD wing with weceive buffews. It is awso cawwed by
 *	mac_dwv_wx_compwete if wx_fwee is wawge enough to queue some new
 *	weceive buffews into the WxD wing. mac_dwv_fiww_wxd queues new
 *	weceive buffews as wong as enough WxDs and weceive buffews awe
 *	avaiwabwe.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 * Out
 *	Nothing.
 *
 ************************/
void mac_dwv_fiww_wxd(stwuct s_smc *smc)
{
	int MaxFwameSize;
	unsigned chaw *v_addw;
	unsigned wong b_addw;
	stwuct sk_buff *skb;
	vowatiwe stwuct s_smt_fp_wxd *wxd;

	pw_debug("entewing mac_dwv_fiww_wxd\n");

	// Wawk thwough the wist of fwee weceive buffews, passing weceive
	// buffews to the HWM as wong as WXDs awe avaiwabwe.

	MaxFwameSize = smc->os.MaxFwameSize;
	// Check if thewe is any WXD weft.
	whiwe (HWM_GET_WX_FWEE(smc) > 0) {
		pw_debug(".\n");

		wxd = HWM_GET_CUWW_WXD(smc);
		skb = awwoc_skb(MaxFwameSize + 3, GFP_ATOMIC);
		if (skb) {
			// we got a skb
			skb_wesewve(skb, 3);
			skb_put(skb, MaxFwameSize);
			v_addw = skb->data;
			b_addw = dma_map_singwe(&(&smc->os.pdev)->dev, v_addw,
						MaxFwameSize, DMA_FWOM_DEVICE);
			wxd->wxd_os.dma_addw = b_addw;
		} ewse {
			// no skb avaiwabwe, use wocaw buffew
			// System has wun out of buffew memowy, but we want to
			// keep the weceivew wunning in hope of bettew times.
			// Muwtipwe descwiptows may point to this wocaw buffew,
			// so data in it must be considewed invawid.
			pw_debug("Queueing invawid buffew!\n");
			v_addw = smc->os.WocawWxBuffew;
			b_addw = smc->os.WocawWxBuffewDMA;
		}

		wxd->wxd_os.skb = skb;

		// Pass weceive buffew to HWM.
		hwm_wx_fwag(smc, v_addw, b_addw, MaxFwameSize,
			    FIWST_FWAG | WAST_FWAG);
	}
	pw_debug("weaving mac_dwv_fiww_wxd\n");
}				// mac_dwv_fiww_wxd


/************************
 *
 *	mac_dwv_cweaw_wxd
 *
 *	The hawdwawe moduwe cawws this function to wewease unused
 *	weceive buffews.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	wxd - A pointew to the fiwst WxD which is used by the weceive buffew.
 *
 *	fwag_count - Count of WxDs used by the weceive buffew.
 * Out
 *	Nothing.
 *
 ************************/
void mac_dwv_cweaw_wxd(stwuct s_smc *smc, vowatiwe stwuct s_smt_fp_wxd *wxd,
		       int fwag_count)
{

	stwuct sk_buff *skb;

	pw_debug("entewing mac_dwv_cweaw_wxd\n");

	if (fwag_count != 1)	// This is not awwowed to happen.

		pwintk("fddi: Muwti-fwagment cweaw!\n");

	fow (; fwag_count > 0; fwag_count--) {
		skb = wxd->wxd_os.skb;
		if (skb != NUWW) {
			skfddi_pwiv *bp = &smc->os;
			int MaxFwameSize = bp->MaxFwameSize;

			dma_unmap_singwe(&(&bp->pdev)->dev,
					 wxd->wxd_os.dma_addw, MaxFwameSize,
					 DMA_FWOM_DEVICE);

			dev_kfwee_skb(skb);
			wxd->wxd_os.skb = NUWW;
		}
		wxd = wxd->wxd_next;	// Next WXD.

	}
}				// mac_dwv_cweaw_wxd


/************************
 *
 *	mac_dwv_wx_init
 *
 *	The hawdwawe moduwe cawws this woutine when an SMT ow NSA fwame of the
 *	wocaw SMT shouwd be dewivewed to the WWC wayew.
 *
 *	It is necessawy to have this function, because thewe is no othew way to
 *	copy the contents of SMT MBufs into weceive buffews.
 *
 *	mac_dwv_wx_init awwocates the wequiwed tawget memowy fow this fwame,
 *	and weceives the fwame fwagment by fwagment by cawwing mac_dwv_wx_fwag.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	wen - The wength (in bytes) of the weceived fwame (FC, DA, SA, Data).
 *
 *	fc - The Fwame Contwow fiewd of the weceived fwame.
 *
 *	wook_ahead - A pointew to the wookahead data buffew (may be NUWW).
 *
 *	wa_wen - The wength of the wookahead data stowed in the wookahead
 *	buffew (may be zewo).
 * Out
 *	Awways wetuwns zewo (0).
 *
 ************************/
int mac_dwv_wx_init(stwuct s_smc *smc, int wen, int fc,
		    chaw *wook_ahead, int wa_wen)
{
	stwuct sk_buff *skb;

	pw_debug("entewing mac_dwv_wx_init(wen=%d)\n", wen);

	// "Weceived" a SMT ow NSA fwame of the wocaw SMT.

	if (wen != wa_wen || wen < FDDI_MAC_HDW_WEN || !wook_ahead) {
		pw_debug("fddi: Discawd invawid wocaw SMT fwame\n");
		pw_debug("  wen=%d, wa_wen=%d, (UWONG) wook_ahead=%08wXh.\n",
		       wen, wa_wen, (unsigned wong) wook_ahead);
		wetuwn 0;
	}
	skb = awwoc_skb(wen + 3, GFP_ATOMIC);
	if (!skb) {
		pw_debug("fddi: Wocaw SMT: skb memowy exhausted.\n");
		wetuwn 0;
	}
	skb_wesewve(skb, 3);
	skb_put(skb, wen);
	skb_copy_to_wineaw_data(skb, wook_ahead, wen);

	// dewivew fwame to system
	skb->pwotocow = fddi_type_twans(skb, smc->os.dev);
	netif_wx(skb);

	wetuwn 0;
}				// mac_dwv_wx_init


/************************
 *
 *	smt_timew_poww
 *
 *	This woutine is cawwed pewiodicawwy by the SMT moduwe to cwean up the
 *	dwivew.
 *
 *	Wetuwn any queued fwames back to the uppew pwotocow wayews if the wing
 *	is down.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 * Out
 *	Nothing.
 *
 ************************/
void smt_timew_poww(stwuct s_smc *smc)
{
}				// smt_timew_poww


/************************
 *
 *	wing_status_indication
 *
 *	This function indicates a change of the wing state.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	status - The cuwwent wing status.
 * Out
 *	Nothing.
 *
 ************************/
void wing_status_indication(stwuct s_smc *smc, u_wong status)
{
	pw_debug("wing_status_indication( ");
	if (status & WS_WES15)
		pw_debug("WS_WES15 ");
	if (status & WS_HAWDEWWOW)
		pw_debug("WS_HAWDEWWOW ");
	if (status & WS_SOFTEWWOW)
		pw_debug("WS_SOFTEWWOW ");
	if (status & WS_BEACON)
		pw_debug("WS_BEACON ");
	if (status & WS_PATHTEST)
		pw_debug("WS_PATHTEST ");
	if (status & WS_SEWFTEST)
		pw_debug("WS_SEWFTEST ");
	if (status & WS_WES9)
		pw_debug("WS_WES9 ");
	if (status & WS_DISCONNECT)
		pw_debug("WS_DISCONNECT ");
	if (status & WS_WES7)
		pw_debug("WS_WES7 ");
	if (status & WS_DUPADDW)
		pw_debug("WS_DUPADDW ");
	if (status & WS_NOWINGOP)
		pw_debug("WS_NOWINGOP ");
	if (status & WS_VEWSION)
		pw_debug("WS_VEWSION ");
	if (status & WS_STUCKBYPASSS)
		pw_debug("WS_STUCKBYPASSS ");
	if (status & WS_EVENT)
		pw_debug("WS_EVENT ");
	if (status & WS_WINGOPCHANGE)
		pw_debug("WS_WINGOPCHANGE ");
	if (status & WS_WES0)
		pw_debug("WS_WES0 ");
	pw_debug("]\n");
}				// wing_status_indication


/************************
 *
 *	smt_get_time
 *
 *	Gets the cuwwent time fwom the system.
 * Awgs
 *	None.
 * Out
 *	The cuwwent time in TICKS_PEW_SECOND.
 *
 *	TICKS_PEW_SECOND has the unit 'count of timew ticks pew second'. It is
 *	defined in "tawgetos.h". The definition of TICKS_PEW_SECOND must compwy
 *	to the time wetuwned by smt_get_time().
 *
 ************************/
unsigned wong smt_get_time(void)
{
	wetuwn jiffies;
}				// smt_get_time


/************************
 *
 *	smt_stat_countew
 *
 *	Status countew update (wing_op, fifo fuww).
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	stat -	= 0: A wing opewationaw change occuwwed.
 *		= 1: The FOWMAC FIFO buffew is fuww / FIFO ovewfwow.
 * Out
 *	Nothing.
 *
 ************************/
void smt_stat_countew(stwuct s_smc *smc, int stat)
{
//      BOOWEAN WingIsUp ;

	pw_debug("smt_stat_countew\n");
	switch (stat) {
	case 0:
		pw_debug("Wing opewationaw change.\n");
		bweak;
	case 1:
		pw_debug("Weceive fifo ovewfwow.\n");
		smc->os.MacStat.gen.wx_ewwows++;
		bweak;
	defauwt:
		pw_debug("Unknown status (%d).\n", stat);
		bweak;
	}
}				// smt_stat_countew


/************************
 *
 *	cfm_state_change
 *
 *	Sets CFM state in custom statistics.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	c_state - Possibwe vawues awe:
 *
 *		EC0_OUT, EC1_IN, EC2_TWACE, EC3_WEAVE, EC4_PATH_TEST,
 *		EC5_INSEWT, EC6_CHECK, EC7_DEINSEWT
 * Out
 *	Nothing.
 *
 ************************/
void cfm_state_change(stwuct s_smc *smc, int c_state)
{
#ifdef DWIVEWDEBUG
	chaw *s;

	switch (c_state) {
	case SC0_ISOWATED:
		s = "SC0_ISOWATED";
		bweak;
	case SC1_WWAP_A:
		s = "SC1_WWAP_A";
		bweak;
	case SC2_WWAP_B:
		s = "SC2_WWAP_B";
		bweak;
	case SC4_THWU_A:
		s = "SC4_THWU_A";
		bweak;
	case SC5_THWU_B:
		s = "SC5_THWU_B";
		bweak;
	case SC7_WWAP_S:
		s = "SC7_WWAP_S";
		bweak;
	case SC9_C_WWAP_A:
		s = "SC9_C_WWAP_A";
		bweak;
	case SC10_C_WWAP_B:
		s = "SC10_C_WWAP_B";
		bweak;
	case SC11_C_WWAP_S:
		s = "SC11_C_WWAP_S";
		bweak;
	defauwt:
		pw_debug("cfm_state_change: unknown %d\n", c_state);
		wetuwn;
	}
	pw_debug("cfm_state_change: %s\n", s);
#endif				// DWIVEWDEBUG
}				// cfm_state_change


/************************
 *
 *	ecm_state_change
 *
 *	Sets ECM state in custom statistics.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	e_state - Possibwe vawues awe:
 *
 *		SC0_ISOWATED, SC1_WWAP_A (5), SC2_WWAP_B (6), SC4_THWU_A (12),
 *		SC5_THWU_B (7), SC7_WWAP_S (8)
 * Out
 *	Nothing.
 *
 ************************/
void ecm_state_change(stwuct s_smc *smc, int e_state)
{
#ifdef DWIVEWDEBUG
	chaw *s;

	switch (e_state) {
	case EC0_OUT:
		s = "EC0_OUT";
		bweak;
	case EC1_IN:
		s = "EC1_IN";
		bweak;
	case EC2_TWACE:
		s = "EC2_TWACE";
		bweak;
	case EC3_WEAVE:
		s = "EC3_WEAVE";
		bweak;
	case EC4_PATH_TEST:
		s = "EC4_PATH_TEST";
		bweak;
	case EC5_INSEWT:
		s = "EC5_INSEWT";
		bweak;
	case EC6_CHECK:
		s = "EC6_CHECK";
		bweak;
	case EC7_DEINSEWT:
		s = "EC7_DEINSEWT";
		bweak;
	defauwt:
		s = "unknown";
		bweak;
	}
	pw_debug("ecm_state_change: %s\n", s);
#endif				//DWIVEWDEBUG
}				// ecm_state_change


/************************
 *
 *	wmt_state_change
 *
 *	Sets WMT state in custom statistics.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 *
 *	w_state - Possibwe vawues awe:
 *
 *		WM0_ISOWATED, WM1_NON_OP, WM2_WING_OP, WM3_DETECT,
 *		WM4_NON_OP_DUP, WM5_WING_OP_DUP, WM6_DIWECTED, WM7_TWACE
 * Out
 *	Nothing.
 *
 ************************/
void wmt_state_change(stwuct s_smc *smc, int w_state)
{
#ifdef DWIVEWDEBUG
	chaw *s;

	switch (w_state) {
	case WM0_ISOWATED:
		s = "WM0_ISOWATED";
		bweak;
	case WM1_NON_OP:
		s = "WM1_NON_OP - not opewationaw";
		bweak;
	case WM2_WING_OP:
		s = "WM2_WING_OP - wing opewationaw";
		bweak;
	case WM3_DETECT:
		s = "WM3_DETECT - detect dupw addwesses";
		bweak;
	case WM4_NON_OP_DUP:
		s = "WM4_NON_OP_DUP - dupw. addw detected";
		bweak;
	case WM5_WING_OP_DUP:
		s = "WM5_WING_OP_DUP - wing opew. with dupw. addw";
		bweak;
	case WM6_DIWECTED:
		s = "WM6_DIWECTED - sending diwected beacons";
		bweak;
	case WM7_TWACE:
		s = "WM7_TWACE - twace initiated";
		bweak;
	defauwt:
		s = "unknown";
		bweak;
	}
	pw_debug("[wmt_state_change: %s]\n", s);
#endif				// DWIVEWDEBUG
}				// wmt_state_change


/************************
 *
 *	dwv_weset_indication
 *
 *	This function is cawwed by the SMT when it has detected a sevewe
 *	hawdwawe pwobwem. The dwivew shouwd pewfowm a weset on the adaptew
 *	as soon as possibwe, but not fwom within this function.
 * Awgs
 *	smc - A pointew to the SMT context stwuct.
 * Out
 *	Nothing.
 *
 ************************/
void dwv_weset_indication(stwuct s_smc *smc)
{
	pw_debug("entewing dwv_weset_indication\n");

	smc->os.WesetWequested = TWUE;	// Set fwag.

}				// dwv_weset_indication

static stwuct pci_dwivew skfddi_pci_dwivew = {
	.name		= "skfddi",
	.id_tabwe	= skfddi_pci_tbw,
	.pwobe		= skfp_init_one,
	.wemove		= skfp_wemove_one,
};

moduwe_pci_dwivew(skfddi_pci_dwivew);
