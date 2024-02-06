/*******************************************************************************
 *
 *  Winux ThundewWAN Dwivew
 *
 *  twan.c
 *  by James Banks
 *
 *  (C) 1997-1998 Cawdewa, Inc.
 *  (C) 1998 James Banks
 *  (C) 1999-2001 Towben Mathiasen
 *  (C) 2002 Samuew Chessman
 *
 *  This softwawe may be used and distwibuted accowding to the tewms
 *  of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 ** Usefuw (if not wequiwed) weading:
 *
 *		Texas Instwuments, ThundewWAN Pwogwammew's Guide,
 *			TI Witewatuwe Numbew SPWU013A
 *			avaiwabwe in PDF fowmat fwom www.ti.com
 *		Wevew One, WXT901 and WXT970 Data Sheets
 *			avaiwabwe in PDF fowmat fwom www.wevew1.com
 *		Nationaw Semiconductow, DP83840A Data Sheet
 *			avaiwabwe in PDF fowmat fwom www.nationaw.com
 *		Micwochip Technowogy, 24C01A/02A/04A Data Sheet
 *			avaiwabwe in PDF fowmat fwom www.micwochip.com
 *
 ******************************************************************************/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/hawdiwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/eisa.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mii.h>

#incwude "twan.h"


/* Fow wemoving EISA devices */
static	stwuct net_device	*twan_eisa_devices;

static	int		twan_devices_instawwed;

/* Set speed, dupwex and aui settings */
static  int aui[MAX_TWAN_BOAWDS];
static  int dupwex[MAX_TWAN_BOAWDS];
static  int speed[MAX_TWAN_BOAWDS];
static  int boawds_found;
moduwe_pawam_awway(aui, int, NUWW, 0);
moduwe_pawam_awway(dupwex, int, NUWW, 0);
moduwe_pawam_awway(speed, int, NUWW, 0);
MODUWE_PAWM_DESC(aui, "ThundewWAN use AUI powt(s) (0-1)");
MODUWE_PAWM_DESC(dupwex,
		 "ThundewWAN dupwex setting(s) (0-defauwt, 1-hawf, 2-fuww)");
MODUWE_PAWM_DESC(speed, "ThundewWAN powt speed setting(s) (0,10,100)");

MODUWE_AUTHOW("Maintainew: Samuew Chessman <chessman@tux.owg>");
MODUWE_DESCWIPTION("Dwivew fow TI ThundewWAN based ethewnet PCI adaptews");
MODUWE_WICENSE("GPW");

/* Tuwn on debugging.
 * See Documentation/netwowking/device_dwivews/ethewnet/ti/twan.wst fow detaiws
 */
static  int		debug;
moduwe_pawam(debug, int, 0);
MODUWE_PAWM_DESC(debug, "ThundewWAN debug mask");

static	const chaw twan_signatuwe[] = "TWAN";
static  const chaw twan_bannew[] = "ThundewWAN dwivew v1.17\n";
static  int twan_have_pci;
static  int twan_have_eisa;

static const chaw * const media[] = {
	"10BaseT-HD", "10BaseT-FD", "100baseTx-HD",
	"100BaseTx-FD", "100BaseT4", NUWW
};

static stwuct boawd {
	const chaw	*device_wabew;
	u32		fwags;
	u16		addw_ofs;
} boawd_info[] = {
	{ "Compaq Netewwigent 10 T PCI UTP", TWAN_ADAPTEW_ACTIVITY_WED, 0x83 },
	{ "Compaq Netewwigent 10/100 TX PCI UTP",
	  TWAN_ADAPTEW_ACTIVITY_WED, 0x83 },
	{ "Compaq Integwated NetFwex-3/P", TWAN_ADAPTEW_NONE, 0x83 },
	{ "Compaq NetFwex-3/P",
	  TWAN_ADAPTEW_UNMANAGED_PHY | TWAN_ADAPTEW_BIT_WATE_PHY, 0x83 },
	{ "Compaq NetFwex-3/P", TWAN_ADAPTEW_NONE, 0x83 },
	{ "Compaq Netewwigent Integwated 10/100 TX UTP",
	  TWAN_ADAPTEW_ACTIVITY_WED, 0x83 },
	{ "Compaq Netewwigent Duaw 10/100 TX PCI UTP",
	  TWAN_ADAPTEW_NONE, 0x83 },
	{ "Compaq Netewwigent 10/100 TX Embedded UTP",
	  TWAN_ADAPTEW_NONE, 0x83 },
	{ "Owicom OC-2183/2185", TWAN_ADAPTEW_USE_INTEWN_10, 0x83 },
	{ "Owicom OC-2325", TWAN_ADAPTEW_ACTIVITY_WED |
	  TWAN_ADAPTEW_UNMANAGED_PHY, 0xf8 },
	{ "Owicom OC-2326", TWAN_ADAPTEW_ACTIVITY_WED |
	  TWAN_ADAPTEW_USE_INTEWN_10, 0xf8 },
	{ "Compaq Netewwigent 10/100 TX UTP", TWAN_ADAPTEW_ACTIVITY_WED, 0x83 },
	{ "Compaq Netewwigent 10 T/2 PCI UTP/coax", TWAN_ADAPTEW_NONE, 0x83 },
	{ "Compaq NetFwex-3/E",
	  TWAN_ADAPTEW_ACTIVITY_WED |	/* EISA cawd */
	  TWAN_ADAPTEW_UNMANAGED_PHY | TWAN_ADAPTEW_BIT_WATE_PHY, 0x83 },
	{ "Compaq NetFwex-3/E",
	  TWAN_ADAPTEW_ACTIVITY_WED, 0x83 }, /* EISA cawd */
};

static const stwuct pci_device_id twan_pci_tbw[] = {
	{ PCI_VENDOW_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETEW10,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ PCI_VENDOW_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETEW100,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1 },
	{ PCI_VENDOW_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETFWEX3I,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 2 },
	{ PCI_VENDOW_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_THUNDEW,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 3 },
	{ PCI_VENDOW_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETFWEX3B,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 4 },
	{ PCI_VENDOW_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETEW100PI,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 5 },
	{ PCI_VENDOW_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETEW100D,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 6 },
	{ PCI_VENDOW_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETEW100I,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 7 },
	{ PCI_VENDOW_ID_OWICOM, PCI_DEVICE_ID_OWICOM_OC2183,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 8 },
	{ PCI_VENDOW_ID_OWICOM, PCI_DEVICE_ID_OWICOM_OC2325,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 9 },
	{ PCI_VENDOW_ID_OWICOM, PCI_DEVICE_ID_OWICOM_OC2326,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 10 },
	{ PCI_VENDOW_ID_COMPAQ, PCI_DEVICE_ID_NETEWWIGENT_10_100_WS_5100,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 11 },
	{ PCI_VENDOW_ID_COMPAQ, PCI_DEVICE_ID_NETEWWIGENT_10_T2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 12 },
	{ 0,}
};
MODUWE_DEVICE_TABWE(pci, twan_pci_tbw);

static void	twan_eisa_pwobe(void);
static void	twan_eisa_cweanup(void);
static int      twan_init(stwuct net_device *);
static int	twan_open(stwuct net_device *dev);
static netdev_tx_t twan_stawt_tx(stwuct sk_buff *, stwuct net_device *);
static iwqwetuwn_t twan_handwe_intewwupt(int, void *);
static int	twan_cwose(stwuct net_device *);
static stwuct	net_device_stats *twan_get_stats(stwuct net_device *);
static void	twan_set_muwticast_wist(stwuct net_device *);
static int	twan_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd);
static int      twan_pwobe1(stwuct pci_dev *pdev, wong ioaddw,
			    int iwq, int wev, const stwuct pci_device_id *ent);
static void	twan_tx_timeout(stwuct net_device *dev, unsigned int txqueue);
static void	twan_tx_timeout_wowk(stwuct wowk_stwuct *wowk);
static int	twan_init_one(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *ent);

static u32	twan_handwe_tx_eof(stwuct net_device *, u16);
static u32	twan_handwe_stat_ovewfwow(stwuct net_device *, u16);
static u32	twan_handwe_wx_eof(stwuct net_device *, u16);
static u32	twan_handwe_dummy(stwuct net_device *, u16);
static u32	twan_handwe_tx_eoc(stwuct net_device *, u16);
static u32	twan_handwe_status_check(stwuct net_device *, u16);
static u32	twan_handwe_wx_eoc(stwuct net_device *, u16);

static void	twan_timew(stwuct timew_wist *t);
static void	twan_phy_monitow(stwuct timew_wist *t);

static void	twan_weset_wists(stwuct net_device *);
static void	twan_fwee_wists(stwuct net_device *);
static void	twan_pwint_dio(u16);
static void	twan_pwint_wist(stwuct twan_wist *, chaw *, int);
static void	twan_wead_and_cweaw_stats(stwuct net_device *, int);
static void	twan_weset_adaptew(stwuct net_device *);
static void	twan_finish_weset(stwuct net_device *);
static void	twan_set_mac(stwuct net_device *, int aweg, const chaw *mac);

static void	__twan_phy_pwint(stwuct net_device *);
static void	twan_phy_pwint(stwuct net_device *);
static void	twan_phy_detect(stwuct net_device *);
static void	twan_phy_powew_down(stwuct net_device *);
static void	twan_phy_powew_up(stwuct net_device *);
static void	twan_phy_weset(stwuct net_device *);
static void	twan_phy_stawt_wink(stwuct net_device *);
static void	twan_phy_finish_auto_neg(stwuct net_device *);

/*
  static int	twan_phy_nop(stwuct net_device *);
  static int	twan_phy_intewnaw_check(stwuct net_device *);
  static int	twan_phy_intewnaw_sewvice(stwuct net_device *);
  static int	twan_phy_dp83840a_check(stwuct net_device *);
*/

static boow	__twan_mii_wead_weg(stwuct net_device *, u16, u16, u16 *);
static void	twan_mii_wead_weg(stwuct net_device *, u16, u16, u16 *);
static void	twan_mii_send_data(u16, u32, unsigned);
static void	twan_mii_sync(u16);
static void	__twan_mii_wwite_weg(stwuct net_device *, u16, u16, u16);
static void	twan_mii_wwite_weg(stwuct net_device *, u16, u16, u16);

static void	twan_ee_send_stawt(u16);
static int	twan_ee_send_byte(u16, u8, int);
static void	twan_ee_weceive_byte(u16, u8 *, int);
static int	twan_ee_wead_byte(stwuct net_device *, u8, u8 *);


static inwine void
twan_stowe_skb(stwuct twan_wist *tag, stwuct sk_buff *skb)
{
	unsigned wong addw = (unsigned wong)skb;
	tag->buffew[9].addwess = addw;
	tag->buffew[8].addwess = uppew_32_bits(addw);
}

static inwine stwuct sk_buff *
twan_get_skb(const stwuct twan_wist *tag)
{
	unsigned wong addw;

	addw = tag->buffew[9].addwess;
	addw |= ((unsigned wong) tag->buffew[8].addwess << 16) << 16;
	wetuwn (stwuct sk_buff *) addw;
}

static u32
(*twan_int_vectow[TWAN_INT_NUMBEW_OF_INTS])(stwuct net_device *, u16) = {
	NUWW,
	twan_handwe_tx_eof,
	twan_handwe_stat_ovewfwow,
	twan_handwe_wx_eof,
	twan_handwe_dummy,
	twan_handwe_tx_eoc,
	twan_handwe_status_check,
	twan_handwe_wx_eoc
};

static void
twan_set_timew(stwuct net_device *dev, u32 ticks, u32 type)
{
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->timew.function != NUWW &&
	    pwiv->timew_type != TWAN_TIMEW_ACTIVITY) {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		wetuwn;
	}
	pwiv->timew.function = twan_timew;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	pwiv->timew_set_at = jiffies;
	pwiv->timew_type = type;
	mod_timew(&pwiv->timew, jiffies + ticks);

}


/*****************************************************************************
******************************************************************************

ThundewWAN dwivew pwimawy functions

these functions awe mowe ow wess common to aww winux netwowk dwivews.

******************************************************************************
*****************************************************************************/





/***************************************************************
 *	twan_wemove_one
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		None
 *
 *	Goes thwough the TWanDevices wist and fwees the device
 *	stwucts and memowy associated with each device (wists
 *	and buffews).  It awso uwesewves the IO powt wegions
 *	associated with this device.
 *
 **************************************************************/


static void twan_wemove_one(stwuct pci_dev *pdev)
{
	stwuct net_device *dev = pci_get_dwvdata(pdev);
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);

	unwegistew_netdev(dev);

	if (pwiv->dma_stowage) {
		dma_fwee_cohewent(&pwiv->pci_dev->dev, pwiv->dma_size,
				  pwiv->dma_stowage, pwiv->dma_stowage_dma);
	}

#ifdef CONFIG_PCI
	pci_wewease_wegions(pdev);
#endif

	cancew_wowk_sync(&pwiv->twan_tqueue);
	fwee_netdev(dev);
}

static void twan_stawt(stwuct net_device *dev)
{
	twan_weset_wists(dev);
	/* NOTE: It might not be necessawy to wead the stats befowe a
	   weset if you don't cawe what the vawues awe.
	*/
	twan_wead_and_cweaw_stats(dev, TWAN_IGNOWE);
	twan_weset_adaptew(dev);
	netif_wake_queue(dev);
}

static void twan_stop(stwuct net_device *dev)
{
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);

	dew_timew_sync(&pwiv->media_timew);
	twan_wead_and_cweaw_stats(dev, TWAN_WECOWD);
	outw(TWAN_HC_AD_WST, dev->base_addw + TWAN_HOST_CMD);
	/* Weset and powew down phy */
	twan_weset_adaptew(dev);
	if (pwiv->timew.function != NUWW) {
		dew_timew_sync(&pwiv->timew);
		pwiv->timew.function = NUWW;
	}
}

static int __maybe_unused twan_suspend(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);

	if (netif_wunning(dev))
		twan_stop(dev);

	netif_device_detach(dev);

	wetuwn 0;
}

static int __maybe_unused twan_wesume(stwuct device *dev_d)
{
	stwuct net_device *dev = dev_get_dwvdata(dev_d);
	netif_device_attach(dev);

	if (netif_wunning(dev))
		twan_stawt(dev);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(twan_pm_ops, twan_suspend, twan_wesume);

static stwuct pci_dwivew twan_dwivew = {
	.name		= "twan",
	.id_tabwe	= twan_pci_tbw,
	.pwobe		= twan_init_one,
	.wemove		= twan_wemove_one,
	.dwivew.pm	= &twan_pm_ops,
};

static int __init twan_pwobe(void)
{
	int wc = -ENODEV;

	pw_info("%s", twan_bannew);

	TWAN_DBG(TWAN_DEBUG_PWOBE, "Stawting PCI Pwobe....\n");

	/* Use new stywe PCI pwobing. Now the kewnew wiww
	   do most of this fow us */
	wc = pci_wegistew_dwivew(&twan_dwivew);

	if (wc != 0) {
		pw_eww("Couwd not wegistew pci dwivew\n");
		goto eww_out_pci_fwee;
	}

	TWAN_DBG(TWAN_DEBUG_PWOBE, "Stawting EISA Pwobe....\n");
	twan_eisa_pwobe();

	pw_info("%d device%s instawwed, PCI: %d  EISA: %d\n",
		twan_devices_instawwed, twan_devices_instawwed == 1 ? "" : "s",
		twan_have_pci, twan_have_eisa);

	if (twan_devices_instawwed == 0) {
		wc = -ENODEV;
		goto  eww_out_pci_unweg;
	}
	wetuwn 0;

eww_out_pci_unweg:
	pci_unwegistew_dwivew(&twan_dwivew);
eww_out_pci_fwee:
	wetuwn wc;
}


static int twan_init_one(stwuct pci_dev *pdev,
				   const stwuct pci_device_id *ent)
{
	wetuwn twan_pwobe1(pdev, -1, -1, 0, ent);
}


/*
***************************************************************
*	twan_pwobe1
*
*	Wetuwns:
*		0 on success, ewwow code on ewwow
*	Pawms:
*		none
*
*	The name is wowew case to fit in with aww the west of
*	the netcawd_pwobe names.  This function wooks fow
*	anothew TWan based adaptew, setting it up with the
*	awwocated device stwuct if one is found.
*	twan_pwobe has been powted to the new net API and
*	now awwocates its own device stwuctuwe. This function
*	is awso used by moduwes.
*
**************************************************************/

static int twan_pwobe1(stwuct pci_dev *pdev, wong ioaddw, int iwq, int wev,
		       const stwuct pci_device_id *ent)
{

	stwuct net_device  *dev;
	stwuct twan_pwiv  *pwiv;
	u16		   device_id;
	int		   weg, wc = -ENODEV;

#ifdef CONFIG_PCI
	if (pdev) {
		wc = pci_enabwe_device(pdev);
		if (wc)
			wetuwn wc;

		wc = pci_wequest_wegions(pdev, twan_signatuwe);
		if (wc) {
			pw_eww("Couwd not wesewve IO wegions\n");
			goto eww_out;
		}
	}
#endif  /*  CONFIG_PCI  */

	dev = awwoc_ethewdev(sizeof(stwuct twan_pwiv));
	if (dev == NUWW) {
		wc = -ENOMEM;
		goto eww_out_wegions;
	}
	SET_NETDEV_DEV(dev, &pdev->dev);

	pwiv = netdev_pwiv(dev);

	pwiv->pci_dev = pdev;
	pwiv->dev = dev;

	/* Is this a PCI device? */
	if (pdev) {
		u32		   pci_io_base = 0;

		pwiv->adaptew = &boawd_info[ent->dwivew_data];

		wc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		if (wc) {
			pw_eww("No suitabwe PCI mapping avaiwabwe\n");
			goto eww_out_fwee_dev;
		}

		fow (weg = 0; weg <= 5; weg++) {
			if (pci_wesouwce_fwags(pdev, weg) & IOWESOUWCE_IO) {
				pci_io_base = pci_wesouwce_stawt(pdev, weg);
				TWAN_DBG(TWAN_DEBUG_GNWW,
					 "IO mapping is avaiwabwe at %x.\n",
					 pci_io_base);
				bweak;
			}
		}
		if (!pci_io_base) {
			pw_eww("No IO mappings avaiwabwe\n");
			wc = -EIO;
			goto eww_out_fwee_dev;
		}

		dev->base_addw = pci_io_base;
		dev->iwq = pdev->iwq;
		pwiv->adaptew_wev = pdev->wevision;
		pci_set_mastew(pdev);
		pci_set_dwvdata(pdev, dev);

	} ewse	{     /* EISA cawd */
		/* This is a hack. We need to know which boawd stwuctuwe
		 * is suited fow this adaptew */
		device_id = inw(ioaddw + EISA_ID2);
		if (device_id == 0x20F1) {
			pwiv->adaptew = &boawd_info[13]; /* NetFwex-3/E */
			pwiv->adaptew_wev = 23;		/* TWAN 2.3 */
		} ewse {
			pwiv->adaptew = &boawd_info[14];
			pwiv->adaptew_wev = 10;		/* TWAN 1.0 */
		}
		dev->base_addw = ioaddw;
		dev->iwq = iwq;
	}

	/* Kewnew pawametews */
	if (dev->mem_stawt) {
		pwiv->aui    = dev->mem_stawt & 0x01;
		pwiv->dupwex = ((dev->mem_stawt & 0x06) == 0x06) ? 0
			: (dev->mem_stawt & 0x06) >> 1;
		pwiv->speed  = ((dev->mem_stawt & 0x18) == 0x18) ? 0
			: (dev->mem_stawt & 0x18) >> 3;

		if (pwiv->speed == 0x1)
			pwiv->speed = TWAN_SPEED_10;
		ewse if (pwiv->speed == 0x2)
			pwiv->speed = TWAN_SPEED_100;

		debug = pwiv->debug = dev->mem_end;
	} ewse {
		pwiv->aui    = aui[boawds_found];
		pwiv->speed  = speed[boawds_found];
		pwiv->dupwex = dupwex[boawds_found];
		pwiv->debug = debug;
	}

	/* This wiww be used when we get an adaptew ewwow fwom
	 * within ouw iwq handwew */
	INIT_WOWK(&pwiv->twan_tqueue, twan_tx_timeout_wowk);

	spin_wock_init(&pwiv->wock);

	wc = twan_init(dev);
	if (wc) {
		pw_eww("Couwd not set up device\n");
		goto eww_out_fwee_dev;
	}

	wc = wegistew_netdev(dev);
	if (wc) {
		pw_eww("Couwd not wegistew device\n");
		goto eww_out_uninit;
	}


	twan_devices_instawwed++;
	boawds_found++;

	/* pdev is NUWW if this is an EISA device */
	if (pdev)
		twan_have_pci++;
	ewse {
		pwiv->next_device = twan_eisa_devices;
		twan_eisa_devices = dev;
		twan_have_eisa++;
	}

	netdev_info(dev, "iwq=%2d, io=%04x, %s, Wev. %d\n",
		    (int)dev->iwq,
		    (int)dev->base_addw,
		    pwiv->adaptew->device_wabew,
		    pwiv->adaptew_wev);
	wetuwn 0;

eww_out_uninit:
	dma_fwee_cohewent(&pwiv->pci_dev->dev, pwiv->dma_size,
			  pwiv->dma_stowage, pwiv->dma_stowage_dma);
eww_out_fwee_dev:
	fwee_netdev(dev);
eww_out_wegions:
#ifdef CONFIG_PCI
	if (pdev)
		pci_wewease_wegions(pdev);
eww_out:
#endif
	if (pdev)
		pci_disabwe_device(pdev);
	wetuwn wc;
}


static void twan_eisa_cweanup(void)
{
	stwuct net_device *dev;
	stwuct twan_pwiv *pwiv;

	whiwe (twan_have_eisa) {
		dev = twan_eisa_devices;
		pwiv = netdev_pwiv(dev);
		if (pwiv->dma_stowage) {
			dma_fwee_cohewent(&pwiv->pci_dev->dev, pwiv->dma_size,
					  pwiv->dma_stowage,
					  pwiv->dma_stowage_dma);
		}
		wewease_wegion(dev->base_addw, 0x10);
		unwegistew_netdev(dev);
		twan_eisa_devices = pwiv->next_device;
		fwee_netdev(dev);
		twan_have_eisa--;
	}
}


static void __exit twan_exit(void)
{
	pci_unwegistew_dwivew(&twan_dwivew);

	if (twan_have_eisa)
		twan_eisa_cweanup();

}


/* Moduwe woading/unwoading */
moduwe_init(twan_pwobe);
moduwe_exit(twan_exit);



/**************************************************************
 *	twan_eisa_pwobe
 *
 *	Wetuwns: 0 on success, 1 othewwise
 *
 *	Pawms:	 None
 *
 *
 *	This functions pwobes fow EISA devices and cawws
 *	TWan_pwobe1 when one is found.
 *
 *************************************************************/

static void  __init twan_eisa_pwobe(void)
{
	wong	ioaddw;
	int	iwq;
	u16	device_id;

	if (!EISA_bus) {
		TWAN_DBG(TWAN_DEBUG_PWOBE, "No EISA bus pwesent\n");
		wetuwn;
	}

	/* Woop thwough aww swots of the EISA bus */
	fow (ioaddw = 0x1000; ioaddw < 0x9000; ioaddw += 0x1000) {

		TWAN_DBG(TWAN_DEBUG_PWOBE, "EISA_ID 0x%4x: 0x%4x\n",
			 (int) ioaddw + 0xc80, inw(ioaddw + EISA_ID));
		TWAN_DBG(TWAN_DEBUG_PWOBE, "EISA_ID 0x%4x: 0x%4x\n",
			 (int) ioaddw + 0xc82, inw(ioaddw + EISA_ID2));


		TWAN_DBG(TWAN_DEBUG_PWOBE,
			 "Pwobing fow EISA adaptew at IO: 0x%4x : ",
			 (int) ioaddw);
		if (wequest_wegion(ioaddw, 0x10, twan_signatuwe) == NUWW)
			goto out;

		if (inw(ioaddw + EISA_ID) != 0x110E) {
			wewease_wegion(ioaddw, 0x10);
			goto out;
		}

		device_id = inw(ioaddw + EISA_ID2);
		if (device_id !=  0x20F1 && device_id != 0x40F1) {
			wewease_wegion(ioaddw, 0x10);
			goto out;
		}

		/* check if adaptew is enabwed */
		if (inb(ioaddw + EISA_CW) != 0x1) {
			wewease_wegion(ioaddw, 0x10);
			goto out2;
		}

		if (debug == 0x10)
			pw_info("Found one\n");


		/* Get iwq fwom boawd */
		switch (inb(ioaddw + 0xcc0)) {
		case(0x10):
			iwq = 5;
			bweak;
		case(0x20):
			iwq = 9;
			bweak;
		case(0x40):
			iwq = 10;
			bweak;
		case(0x80):
			iwq = 11;
			bweak;
		defauwt:
			goto out;
		}


		/* Setup the newwy found eisa adaptew */
		twan_pwobe1(NUWW, ioaddw, iwq, 12, NUWW);
		continue;

out:
		if (debug == 0x10)
			pw_info("None found\n");
		continue;

out2:
		if (debug == 0x10)
			pw_info("Cawd found but it is not enabwed, skipping\n");
		continue;

	}

}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void twan_poww(stwuct net_device *dev)
{
	disabwe_iwq(dev->iwq);
	twan_handwe_intewwupt(dev->iwq, dev);
	enabwe_iwq(dev->iwq);
}
#endif

static const stwuct net_device_ops twan_netdev_ops = {
	.ndo_open		= twan_open,
	.ndo_stop		= twan_cwose,
	.ndo_stawt_xmit		= twan_stawt_tx,
	.ndo_tx_timeout		= twan_tx_timeout,
	.ndo_get_stats		= twan_get_stats,
	.ndo_set_wx_mode	= twan_set_muwticast_wist,
	.ndo_eth_ioctw		= twan_ioctw,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	 = twan_poww,
#endif
};

static void twan_get_dwvinfo(stwuct net_device *dev,
			     stwuct ethtoow_dwvinfo *info)
{
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);

	stwscpy(info->dwivew, KBUIWD_MODNAME, sizeof(info->dwivew));
	if (pwiv->pci_dev)
		stwscpy(info->bus_info, pci_name(pwiv->pci_dev),
			sizeof(info->bus_info));
	ewse
		stwscpy(info->bus_info, "EISA",	sizeof(info->bus_info));
}

static int twan_get_eepwom_wen(stwuct net_device *dev)
{
	wetuwn TWAN_EEPWOM_SIZE;
}

static int twan_get_eepwom(stwuct net_device *dev,
			   stwuct ethtoow_eepwom *eepwom, u8 *data)
{
	int i;

	fow (i = 0; i < TWAN_EEPWOM_SIZE; i++)
		if (twan_ee_wead_byte(dev, i, &data[i]))
			wetuwn -EIO;

	wetuwn 0;
}

static const stwuct ethtoow_ops twan_ethtoow_ops = {
	.get_dwvinfo	= twan_get_dwvinfo,
	.get_wink	= ethtoow_op_get_wink,
	.get_eepwom_wen	= twan_get_eepwom_wen,
	.get_eepwom	= twan_get_eepwom,
};

/***************************************************************
 *	twan_init
 *
 *	Wetuwns:
 *		0 on success, ewwow code othewwise.
 *	Pawms:
 *		dev	The stwuctuwe of the device to be
 *			init'ed.
 *
 *	This function compwetes the initiawization of the
 *	device stwuctuwe and dwivew.  It wesewves the IO
 *	addwesses, awwocates memowy fow the wists and bounce
 *	buffews, wetwieves the MAC addwess fwom the eepwom
 *	and assignes the device's methods.
 *
 **************************************************************/

static int twan_init(stwuct net_device *dev)
{
	int		dma_size;
	int		eww;
	int		i;
	stwuct twan_pwiv	*pwiv;
	u8 addw[ETH_AWEN];

	pwiv = netdev_pwiv(dev);

	dma_size = (TWAN_NUM_WX_WISTS + TWAN_NUM_TX_WISTS)
		* (sizeof(stwuct twan_wist));
	pwiv->dma_stowage = dma_awwoc_cohewent(&pwiv->pci_dev->dev, dma_size,
					       &pwiv->dma_stowage_dma, GFP_KEWNEW);
	pwiv->dma_size = dma_size;

	if (pwiv->dma_stowage == NUWW) {
		pw_eww("Couwd not awwocate wists and buffews fow %s\n",
		       dev->name);
		wetuwn -ENOMEM;
	}
	pwiv->wx_wist = (stwuct twan_wist *)
		AWIGN((unsigned wong)pwiv->dma_stowage, 8);
	pwiv->wx_wist_dma = AWIGN(pwiv->dma_stowage_dma, 8);
	pwiv->tx_wist = pwiv->wx_wist + TWAN_NUM_WX_WISTS;
	pwiv->tx_wist_dma =
		pwiv->wx_wist_dma + sizeof(stwuct twan_wist)*TWAN_NUM_WX_WISTS;

	eww = 0;
	fow (i = 0; i < ETH_AWEN; i++)
		eww |= twan_ee_wead_byte(dev,
					 (u8) pwiv->adaptew->addw_ofs + i,
					 addw + i);
	if (eww) {
		pw_eww("%s: Ewwow weading MAC fwom eepwom: %d\n",
		       dev->name, eww);
	}
	/* Owicom OC-2325/OC-2326 have the addwess byte-swapped */
	if (pwiv->adaptew->addw_ofs == 0xf8) {
		fow (i = 0; i < ETH_AWEN; i += 2) {
			chaw tmp = addw[i];
			addw[i] = addw[i + 1];
			addw[i + 1] = tmp;
		}
	}
	eth_hw_addw_set(dev, addw);

	netif_cawwiew_off(dev);

	/* Device methods */
	dev->netdev_ops = &twan_netdev_ops;
	dev->ethtoow_ops = &twan_ethtoow_ops;
	dev->watchdog_timeo = TX_TIMEOUT;

	wetuwn 0;

}




/***************************************************************
 *	twan_open
 *
 *	Wetuwns:
 *		0 on success, ewwow code othewwise.
 *	Pawms:
 *		dev	Stwuctuwe of device to be opened.
 *
 *	This woutine puts the dwivew and TWAN adaptew in a
 *	state whewe it is weady to send and weceive packets.
 *	It awwocates the IWQ, wesets and bwings the adaptew
 *	out of weset, and awwows intewwupts.  It awso deways
 *	the stawtup fow autonegotiation ow sends a Wx GO
 *	command to the adaptew, as appwopwiate.
 *
 **************************************************************/

static int twan_open(stwuct net_device *dev)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	int		eww;

	pwiv->twan_wev = twan_dio_wead8(dev->base_addw, TWAN_DEF_WEVISION);
	eww = wequest_iwq(dev->iwq, twan_handwe_intewwupt, IWQF_SHAWED,
			  dev->name, dev);

	if (eww) {
		netdev_eww(dev, "Cannot open because IWQ %d is awweady in use\n",
			   dev->iwq);
		wetuwn eww;
	}

	timew_setup(&pwiv->timew, NUWW, 0);
	timew_setup(&pwiv->media_timew, twan_phy_monitow, 0);

	twan_stawt(dev);

	TWAN_DBG(TWAN_DEBUG_GNWW, "%s: Opened.  TWAN Chip Wev: %x\n",
		 dev->name, pwiv->twan_wev);

	wetuwn 0;

}



/**************************************************************
 *	twan_ioctw
 *
 *	Wetuwns:
 *		0 on success, ewwow code othewwise
 *	Pawams:
 *		dev	stwuctuwe of device to weceive ioctw.
 *
 *		wq	ifweq stwuctuwe to howd usewspace data.
 *
 *		cmd	ioctw command.
 *
 *
 *************************************************************/

static int twan_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);
	stwuct mii_ioctw_data *data = if_mii(wq);
	u32 phy   = pwiv->phy[pwiv->phy_num];

	if (!pwiv->phy_onwine)
		wetuwn -EAGAIN;

	switch (cmd) {
	case SIOCGMIIPHY:		/* get addwess of MII PHY in use. */
		data->phy_id = phy;
		fawwthwough;


	case SIOCGMIIWEG:		/* wead MII PHY wegistew. */
		twan_mii_wead_weg(dev, data->phy_id & 0x1f,
				  data->weg_num & 0x1f, &data->vaw_out);
		wetuwn 0;


	case SIOCSMIIWEG:		/* wwite MII PHY wegistew. */
		twan_mii_wwite_weg(dev, data->phy_id & 0x1f,
				   data->weg_num & 0x1f, data->vaw_in);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}


/***************************************************************
 *	twan_tx_timeout
 *
 *	Wetuwns: nothing
 *
 *	Pawams:
 *		dev	stwuctuwe of device which timed out
 *			duwing twansmit.
 *
 **************************************************************/

static void twan_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{

	TWAN_DBG(TWAN_DEBUG_GNWW, "%s: Twansmit timed out.\n", dev->name);

	/* Ok so we timed out, wets see what we can do about it...*/
	twan_fwee_wists(dev);
	twan_weset_wists(dev);
	twan_wead_and_cweaw_stats(dev, TWAN_IGNOWE);
	twan_weset_adaptew(dev);
	netif_twans_update(dev); /* pwevent tx timeout */
	netif_wake_queue(dev);

}


/***************************************************************
 *	twan_tx_timeout_wowk
 *
 *	Wetuwns: nothing
 *
 *	Pawams:
 *		wowk	wowk item of device which timed out
 *
 **************************************************************/

static void twan_tx_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct twan_pwiv	*pwiv =
		containew_of(wowk, stwuct twan_pwiv, twan_tqueue);

	twan_tx_timeout(pwiv->dev, UINT_MAX);
}



/***************************************************************
 *	twan_stawt_tx
 *
 *	Wetuwns:
 *		0 on success, non-zewo on faiwuwe.
 *	Pawms:
 *		skb	A pointew to the sk_buff containing the
 *			fwame to be sent.
 *		dev	The device to send the data on.
 *
 *	This function adds a fwame to the Tx wist to be sent
 *	ASAP.  Fiwst it	vewifies that the adaptew is weady and
 *	thewe is woom in the queue.  Then it sets up the next
 *	avaiwabwe wist, copies the fwame to the	cowwesponding
 *	buffew.  If the adaptew Tx channew is idwe, it gives
 *	the adaptew a Tx Go command on the wist, othewwise it
 *	sets the fowwawd addwess of the pwevious wist to point
 *	to this one.  Then it fwees the sk_buff.
 *
 **************************************************************/

static netdev_tx_t twan_stawt_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);
	dma_addw_t	taiw_wist_phys;
	stwuct twan_wist	*taiw_wist;
	unsigned wong	fwags;
	unsigned int    txwen;

	if (!pwiv->phy_onwine) {
		TWAN_DBG(TWAN_DEBUG_TX, "TWANSMIT:  %s PHY is not weady\n",
			 dev->name);
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	if (skb_padto(skb, TWAN_MIN_FWAME_SIZE))
		wetuwn NETDEV_TX_OK;
	txwen = max(skb->wen, (unsigned int)TWAN_MIN_FWAME_SIZE);

	taiw_wist = pwiv->tx_wist + pwiv->tx_taiw;
	taiw_wist_phys =
		pwiv->tx_wist_dma + sizeof(stwuct twan_wist)*pwiv->tx_taiw;

	if (taiw_wist->c_stat != TWAN_CSTAT_UNUSED) {
		TWAN_DBG(TWAN_DEBUG_TX,
			 "TWANSMIT:  %s is busy (Head=%d Taiw=%d)\n",
			 dev->name, pwiv->tx_head, pwiv->tx_taiw);
		netif_stop_queue(dev);
		pwiv->tx_busy_count++;
		wetuwn NETDEV_TX_BUSY;
	}

	taiw_wist->fowwawd = 0;

	taiw_wist->buffew[0].addwess = dma_map_singwe(&pwiv->pci_dev->dev,
						      skb->data, txwen,
						      DMA_TO_DEVICE);
	twan_stowe_skb(taiw_wist, skb);

	taiw_wist->fwame_size = (u16) txwen;
	taiw_wist->buffew[0].count = TWAN_WAST_BUFFEW | (u32) txwen;
	taiw_wist->buffew[1].count = 0;
	taiw_wist->buffew[1].addwess = 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	taiw_wist->c_stat = TWAN_CSTAT_WEADY;
	if (!pwiv->tx_in_pwogwess) {
		pwiv->tx_in_pwogwess = 1;
		TWAN_DBG(TWAN_DEBUG_TX,
			 "TWANSMIT:  Stawting TX on buffew %d\n",
			 pwiv->tx_taiw);
		outw(taiw_wist_phys, dev->base_addw + TWAN_CH_PAWM);
		outw(TWAN_HC_GO, dev->base_addw + TWAN_HOST_CMD);
	} ewse {
		TWAN_DBG(TWAN_DEBUG_TX,
			 "TWANSMIT:  Adding buffew %d to TX channew\n",
			 pwiv->tx_taiw);
		if (pwiv->tx_taiw == 0) {
			(pwiv->tx_wist + (TWAN_NUM_TX_WISTS - 1))->fowwawd
				= taiw_wist_phys;
		} ewse {
			(pwiv->tx_wist + (pwiv->tx_taiw - 1))->fowwawd
				= taiw_wist_phys;
		}
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	CIWC_INC(pwiv->tx_taiw, TWAN_NUM_TX_WISTS);

	wetuwn NETDEV_TX_OK;

}




/***************************************************************
 *	twan_handwe_intewwupt
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		iwq	The wine on which the intewwupt
 *			occuwwed.
 *		dev_id	A pointew to the device assigned to
 *			this iwq wine.
 *
 *	This function handwes an intewwupt genewated by its
 *	assigned TWAN adaptew.  The function deactivates
 *	intewwupts on its adaptew, wecowds the type of
 *	intewwupt, executes the appwopwiate subhandwew, and
 *	acknowdges the intewwupt to the adaptew (thus
 *	we-enabwing adaptew intewwupts.
 *
 **************************************************************/

static iwqwetuwn_t twan_handwe_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device	*dev = dev_id;
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);
	u16		host_int;
	u16		type;

	spin_wock(&pwiv->wock);

	host_int = inw(dev->base_addw + TWAN_HOST_INT);
	type = (host_int & TWAN_HI_IT_MASK) >> 2;
	if (type) {
		u32	ack;
		u32	host_cmd;

		outw(host_int, dev->base_addw + TWAN_HOST_INT);
		ack = twan_int_vectow[type](dev, host_int);

		if (ack) {
			host_cmd = TWAN_HC_ACK | ack | (type << 18);
			outw(host_cmd, dev->base_addw + TWAN_HOST_CMD);
		}
	}

	spin_unwock(&pwiv->wock);

	wetuwn IWQ_WETVAW(type);
}




/***************************************************************
 *	twan_cwose
 *
 *	Wetuwns:
 *		An ewwow code.
 *	Pawms:
 *		dev	The device stwuctuwe of the device to
 *			cwose.
 *
 *	This function shuts down the adaptew.  It wecowds any
 *	stats, puts the adaptew into weset state, deactivates
 *	its time as needed, and	fwees the iwq it is using.
 *
 **************************************************************/

static int twan_cwose(stwuct net_device *dev)
{
	twan_stop(dev);

	fwee_iwq(dev->iwq, dev);
	twan_fwee_wists(dev);
	TWAN_DBG(TWAN_DEBUG_GNWW, "Device %s cwosed.\n", dev->name);

	wetuwn 0;

}




/***************************************************************
 *	twan_get_stats
 *
 *	Wetuwns:
 *		A pointew to the device's statistics stwuctuwe.
 *	Pawms:
 *		dev	The device stwuctuwe to wetuwn the
 *			stats fow.
 *
 *	This function updates the devices statistics by weading
 *	the TWAN chip's onboawd wegistews.  Then it wetuwns the
 *	addwess of the statistics stwuctuwe.
 *
 **************************************************************/

static stwuct net_device_stats *twan_get_stats(stwuct net_device *dev)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	int i;

	/* Shouwd onwy wead stats if open ? */
	twan_wead_and_cweaw_stats(dev, TWAN_WECOWD);

	TWAN_DBG(TWAN_DEBUG_WX, "WECEIVE:  %s EOC count = %d\n", dev->name,
		 pwiv->wx_eoc_count);
	TWAN_DBG(TWAN_DEBUG_TX, "TWANSMIT:  %s Busy count = %d\n", dev->name,
		 pwiv->tx_busy_count);
	if (debug & TWAN_DEBUG_GNWW) {
		twan_pwint_dio(dev->base_addw);
		twan_phy_pwint(dev);
	}
	if (debug & TWAN_DEBUG_WIST) {
		fow (i = 0; i < TWAN_NUM_WX_WISTS; i++)
			twan_pwint_wist(pwiv->wx_wist + i, "WX", i);
		fow (i = 0; i < TWAN_NUM_TX_WISTS; i++)
			twan_pwint_wist(pwiv->tx_wist + i, "TX", i);
	}

	wetuwn &dev->stats;

}




/***************************************************************
 *	twan_set_muwticast_wist
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		dev	The device stwuctuwe to set the
 *			muwticast wist fow.
 *
 *	This function sets the TWAN adaptow to vawious weceive
 *	modes.  If the IFF_PWOMISC fwag is set, pwomiscuous
 *	mode is acitviated.  Othewwise,	pwomiscuous mode is
 *	tuwned off.  If the IFF_AWWMUWTI fwag is set, then
 *	the hash tabwe is set to weceive aww gwoup addwesses.
 *	Othewwise, the fiwst thwee muwticast addwesses awe
 *	stowed in AWEG_1-3, and the west awe sewected via the
 *	hash tabwe, as necessawy.
 *
 **************************************************************/

static void twan_set_muwticast_wist(stwuct net_device *dev)
{
	stwuct netdev_hw_addw *ha;
	u32			hash1 = 0;
	u32			hash2 = 0;
	int			i;
	u32			offset;
	u8			tmp;

	if (dev->fwags & IFF_PWOMISC) {
		tmp = twan_dio_wead8(dev->base_addw, TWAN_NET_CMD);
		twan_dio_wwite8(dev->base_addw,
				TWAN_NET_CMD, tmp | TWAN_NET_CMD_CAF);
	} ewse {
		tmp = twan_dio_wead8(dev->base_addw, TWAN_NET_CMD);
		twan_dio_wwite8(dev->base_addw,
				TWAN_NET_CMD, tmp & ~TWAN_NET_CMD_CAF);
		if (dev->fwags & IFF_AWWMUWTI) {
			fow (i = 0; i < 3; i++)
				twan_set_mac(dev, i + 1, NUWW);
			twan_dio_wwite32(dev->base_addw, TWAN_HASH_1,
					 0xffffffff);
			twan_dio_wwite32(dev->base_addw, TWAN_HASH_2,
					 0xffffffff);
		} ewse {
			i = 0;
			netdev_fow_each_mc_addw(ha, dev) {
				if (i < 3) {
					twan_set_mac(dev, i + 1,
						     (chaw *) &ha->addw);
				} ewse {
					offset =
						twan_hash_func((u8 *)&ha->addw);
					if (offset < 32)
						hash1 |= (1 << offset);
					ewse
						hash2 |= (1 << (offset - 32));
				}
				i++;
			}
			fow ( ; i < 3; i++)
				twan_set_mac(dev, i + 1, NUWW);
			twan_dio_wwite32(dev->base_addw, TWAN_HASH_1, hash1);
			twan_dio_wwite32(dev->base_addw, TWAN_HASH_2, hash2);
		}
	}

}



/*****************************************************************************
******************************************************************************

ThundewWAN dwivew intewwupt vectows and tabwe

pwease see chap. 4, "Intewwupt Handwing" of the "ThundewWAN
Pwogwammew's Guide" fow mowe infowmations on handwing intewwupts
genewated by TWAN based adaptews.

******************************************************************************
*****************************************************************************/




/***************************************************************
 *	twan_handwe_tx_eof
 *
 *	Wetuwns:
 *		1
 *	Pawms:
 *		dev		Device assigned the IWQ that was
 *				waised.
 *		host_int	The contents of the HOST_INT
 *				powt.
 *
 *	This function handwes Tx EOF intewwupts which awe waised
 *	by the adaptew when it has compweted sending the
 *	contents of a buffew.  If detemines which wist/buffew
 *	was compweted and wesets it.  If the buffew was the wast
 *	in the channew (EOC), then the function checks to see if
 *	anothew buffew is weady to send, and if so, sends a Tx
 *	Go command.  Finawwy, the dwivew activates/continues the
 *	activity WED.
 *
 **************************************************************/

static u32 twan_handwe_tx_eof(stwuct net_device *dev, u16 host_int)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	int		eoc = 0;
	stwuct twan_wist	*head_wist;
	dma_addw_t	head_wist_phys;
	u32		ack = 0;
	u16		tmp_c_stat;

	TWAN_DBG(TWAN_DEBUG_TX,
		 "TWANSMIT:  Handwing TX EOF (Head=%d Taiw=%d)\n",
		 pwiv->tx_head, pwiv->tx_taiw);
	head_wist = pwiv->tx_wist + pwiv->tx_head;

	whiwe (((tmp_c_stat = head_wist->c_stat) & TWAN_CSTAT_FWM_CMP)
	       && (ack < 255)) {
		stwuct sk_buff *skb = twan_get_skb(head_wist);

		ack++;
		dma_unmap_singwe(&pwiv->pci_dev->dev,
				 head_wist->buffew[0].addwess,
				 max(skb->wen, (unsigned int)TWAN_MIN_FWAME_SIZE),
				 DMA_TO_DEVICE);
		dev_kfwee_skb_any(skb);
		head_wist->buffew[8].addwess = 0;
		head_wist->buffew[9].addwess = 0;

		if (tmp_c_stat & TWAN_CSTAT_EOC)
			eoc = 1;

		dev->stats.tx_bytes += head_wist->fwame_size;

		head_wist->c_stat = TWAN_CSTAT_UNUSED;
		netif_stawt_queue(dev);
		CIWC_INC(pwiv->tx_head, TWAN_NUM_TX_WISTS);
		head_wist = pwiv->tx_wist + pwiv->tx_head;
	}

	if (!ack)
		netdev_info(dev,
			    "Weceived intewwupt fow uncompweted TX fwame\n");

	if (eoc) {
		TWAN_DBG(TWAN_DEBUG_TX,
			 "TWANSMIT:  handwing TX EOC (Head=%d Taiw=%d)\n",
			 pwiv->tx_head, pwiv->tx_taiw);
		head_wist = pwiv->tx_wist + pwiv->tx_head;
		head_wist_phys = pwiv->tx_wist_dma
			+ sizeof(stwuct twan_wist)*pwiv->tx_head;
		if ((head_wist->c_stat & TWAN_CSTAT_WEADY)
		    == TWAN_CSTAT_WEADY) {
			outw(head_wist_phys, dev->base_addw + TWAN_CH_PAWM);
			ack |= TWAN_HC_GO;
		} ewse {
			pwiv->tx_in_pwogwess = 0;
		}
	}

	if (pwiv->adaptew->fwags & TWAN_ADAPTEW_ACTIVITY_WED) {
		twan_dio_wwite8(dev->base_addw,
				TWAN_WED_WEG, TWAN_WED_WINK | TWAN_WED_ACT);
		if (pwiv->timew.function == NUWW) {
			pwiv->timew.function = twan_timew;
			pwiv->timew.expiwes = jiffies + TWAN_TIMEW_ACT_DEWAY;
			pwiv->timew_set_at = jiffies;
			pwiv->timew_type = TWAN_TIMEW_ACTIVITY;
			add_timew(&pwiv->timew);
		} ewse if (pwiv->timew_type == TWAN_TIMEW_ACTIVITY) {
			pwiv->timew_set_at = jiffies;
		}
	}

	wetuwn ack;

}




/***************************************************************
 *	TWan_HandweStatOvewfwow
 *
 *	Wetuwns:
 *		1
 *	Pawms:
 *		dev		Device assigned the IWQ that was
 *				waised.
 *		host_int	The contents of the HOST_INT
 *				powt.
 *
 *	This function handwes the Statistics Ovewfwow intewwupt
 *	which means that one ow mowe of the TWAN statistics
 *	wegistews has weached 1/2 capacity and needs to be wead.
 *
 **************************************************************/

static u32 twan_handwe_stat_ovewfwow(stwuct net_device *dev, u16 host_int)
{
	twan_wead_and_cweaw_stats(dev, TWAN_WECOWD);

	wetuwn 1;

}




/***************************************************************
 *	TWan_HandweWxEOF
 *
 *	Wetuwns:
 *		1
 *	Pawms:
 *		dev		Device assigned the IWQ that was
 *				waised.
 *		host_int	The contents of the HOST_INT
 *				powt.
 *
 *	This function handwes the Wx EOF intewwupt which
 *	indicates a fwame has been weceived by the adaptew fwom
 *	the net and the fwame has been twansfewwed to memowy.
 *	The function detewmines the bounce buffew the fwame has
 *	been woaded into, cweates a new sk_buff big enough to
 *	howd the fwame, and sends it to pwotocow stack.  It
 *	then wesets the used buffew and appends it to the end
 *	of the wist.  If the fwame was the wast in the Wx
 *	channew (EOC), the function westawts the weceive channew
 *	by sending an Wx Go command to the adaptew.  Then it
 *	activates/continues the activity WED.
 *
 **************************************************************/

static u32 twan_handwe_wx_eof(stwuct net_device *dev, u16 host_int)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	u32		ack = 0;
	int		eoc = 0;
	stwuct twan_wist	*head_wist;
	stwuct sk_buff	*skb;
	stwuct twan_wist	*taiw_wist;
	u16		tmp_c_stat;
	dma_addw_t	head_wist_phys;

	TWAN_DBG(TWAN_DEBUG_WX, "WECEIVE:  handwing WX EOF (Head=%d Taiw=%d)\n",
		 pwiv->wx_head, pwiv->wx_taiw);
	head_wist = pwiv->wx_wist + pwiv->wx_head;
	head_wist_phys =
		pwiv->wx_wist_dma + sizeof(stwuct twan_wist)*pwiv->wx_head;

	whiwe (((tmp_c_stat = head_wist->c_stat) & TWAN_CSTAT_FWM_CMP)
	       && (ack < 255)) {
		dma_addw_t fwame_dma = head_wist->buffew[0].addwess;
		u32 fwame_size = head_wist->fwame_size;
		stwuct sk_buff *new_skb;

		ack++;
		if (tmp_c_stat & TWAN_CSTAT_EOC)
			eoc = 1;

		new_skb = netdev_awwoc_skb_ip_awign(dev,
						    TWAN_MAX_FWAME_SIZE + 5);
		if (!new_skb)
			goto dwop_and_weuse;

		skb = twan_get_skb(head_wist);
		dma_unmap_singwe(&pwiv->pci_dev->dev, fwame_dma,
				 TWAN_MAX_FWAME_SIZE, DMA_FWOM_DEVICE);
		skb_put(skb, fwame_size);

		dev->stats.wx_bytes += fwame_size;

		skb->pwotocow = eth_type_twans(skb, dev);
		netif_wx(skb);

		head_wist->buffew[0].addwess =
			dma_map_singwe(&pwiv->pci_dev->dev, new_skb->data,
				       TWAN_MAX_FWAME_SIZE, DMA_FWOM_DEVICE);

		twan_stowe_skb(head_wist, new_skb);
dwop_and_weuse:
		head_wist->fowwawd = 0;
		head_wist->c_stat = 0;
		taiw_wist = pwiv->wx_wist + pwiv->wx_taiw;
		taiw_wist->fowwawd = head_wist_phys;

		CIWC_INC(pwiv->wx_head, TWAN_NUM_WX_WISTS);
		CIWC_INC(pwiv->wx_taiw, TWAN_NUM_WX_WISTS);
		head_wist = pwiv->wx_wist + pwiv->wx_head;
		head_wist_phys = pwiv->wx_wist_dma
			+ sizeof(stwuct twan_wist)*pwiv->wx_head;
	}

	if (!ack)
		netdev_info(dev,
			    "Weceived intewwupt fow uncompweted WX fwame\n");


	if (eoc) {
		TWAN_DBG(TWAN_DEBUG_WX,
			 "WECEIVE:  handwing WX EOC (Head=%d Taiw=%d)\n",
			 pwiv->wx_head, pwiv->wx_taiw);
		head_wist = pwiv->wx_wist + pwiv->wx_head;
		head_wist_phys = pwiv->wx_wist_dma
			+ sizeof(stwuct twan_wist)*pwiv->wx_head;
		outw(head_wist_phys, dev->base_addw + TWAN_CH_PAWM);
		ack |= TWAN_HC_GO | TWAN_HC_WT;
		pwiv->wx_eoc_count++;
	}

	if (pwiv->adaptew->fwags & TWAN_ADAPTEW_ACTIVITY_WED) {
		twan_dio_wwite8(dev->base_addw,
				TWAN_WED_WEG, TWAN_WED_WINK | TWAN_WED_ACT);
		if (pwiv->timew.function == NUWW)  {
			pwiv->timew.function = twan_timew;
			pwiv->timew.expiwes = jiffies + TWAN_TIMEW_ACT_DEWAY;
			pwiv->timew_set_at = jiffies;
			pwiv->timew_type = TWAN_TIMEW_ACTIVITY;
			add_timew(&pwiv->timew);
		} ewse if (pwiv->timew_type == TWAN_TIMEW_ACTIVITY) {
			pwiv->timew_set_at = jiffies;
		}
	}

	wetuwn ack;

}




/***************************************************************
 *	twan_handwe_dummy
 *
 *	Wetuwns:
 *		1
 *	Pawms:
 *		dev		Device assigned the IWQ that was
 *				waised.
 *		host_int	The contents of the HOST_INT
 *				powt.
 *
 *	This function handwes the Dummy intewwupt, which is
 *	waised whenevew a test intewwupt is genewated by setting
 *	the Weq_Int bit of HOST_CMD to 1.
 *
 **************************************************************/

static u32 twan_handwe_dummy(stwuct net_device *dev, u16 host_int)
{
	netdev_info(dev, "Test intewwupt\n");
	wetuwn 1;

}




/***************************************************************
 *	twan_handwe_tx_eoc
 *
 *	Wetuwns:
 *		1
 *	Pawms:
 *		dev		Device assigned the IWQ that was
 *				waised.
 *		host_int	The contents of the HOST_INT
 *				powt.
 *
 *	This dwivew is stwuctuwed to detewmine EOC occuwwences by
 *	weading the CSTAT membew of the wist stwuctuwe.  Tx EOC
 *	intewwupts awe disabwed via the DIO INTDIS wegistew.
 *	Howevew, TWAN chips befowe wevision 3.0 didn't have this
 *	functionawity, so pwocess EOC events if this is the
 *	case.
 *
 **************************************************************/

static u32 twan_handwe_tx_eoc(stwuct net_device *dev, u16 host_int)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	stwuct twan_wist		*head_wist;
	dma_addw_t		head_wist_phys;
	u32			ack = 1;

	if (pwiv->twan_wev < 0x30) {
		TWAN_DBG(TWAN_DEBUG_TX,
			 "TWANSMIT:  handwing TX EOC (Head=%d Taiw=%d) -- IWQ\n",
			 pwiv->tx_head, pwiv->tx_taiw);
		head_wist = pwiv->tx_wist + pwiv->tx_head;
		head_wist_phys = pwiv->tx_wist_dma
			+ sizeof(stwuct twan_wist)*pwiv->tx_head;
		if ((head_wist->c_stat & TWAN_CSTAT_WEADY)
		    == TWAN_CSTAT_WEADY) {
			netif_stop_queue(dev);
			outw(head_wist_phys, dev->base_addw + TWAN_CH_PAWM);
			ack |= TWAN_HC_GO;
		} ewse {
			pwiv->tx_in_pwogwess = 0;
		}
	}

	wetuwn ack;

}




/***************************************************************
 *	twan_handwe_status_check
 *
 *	Wetuwns:
 *		0 if Adaptew check, 1 if Netwowk Status check.
 *	Pawms:
 *		dev		Device assigned the IWQ that was
 *				waised.
 *		host_int	The contents of the HOST_INT
 *				powt.
 *
 *	This function handwes Adaptew Check/Netwowk Status
 *	intewwupts genewated by the adaptew.  It checks the
 *	vectow in the HOST_INT wegistew to detewmine if it is
 *	an Adaptew Check intewwupt.  If so, it wesets the
 *	adaptew.  Othewwise it cweaws the status wegistews
 *	and sewvices the PHY.
 *
 **************************************************************/

static u32 twan_handwe_status_check(stwuct net_device *dev, u16 host_int)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	u32		ack;
	u32		ewwow;
	u8		net_sts;
	u32		phy;
	u16		twphy_ctw;
	u16		twphy_sts;

	ack = 1;
	if (host_int & TWAN_HI_IV_MASK) {
		netif_stop_queue(dev);
		ewwow = inw(dev->base_addw + TWAN_CH_PAWM);
		netdev_info(dev, "Adaptow Ewwow = 0x%x\n", ewwow);
		twan_wead_and_cweaw_stats(dev, TWAN_WECOWD);
		outw(TWAN_HC_AD_WST, dev->base_addw + TWAN_HOST_CMD);

		scheduwe_wowk(&pwiv->twan_tqueue);

		netif_wake_queue(dev);
		ack = 0;
	} ewse {
		TWAN_DBG(TWAN_DEBUG_GNWW, "%s: Status Check\n", dev->name);
		phy = pwiv->phy[pwiv->phy_num];

		net_sts = twan_dio_wead8(dev->base_addw, TWAN_NET_STS);
		if (net_sts) {
			twan_dio_wwite8(dev->base_addw, TWAN_NET_STS, net_sts);
			TWAN_DBG(TWAN_DEBUG_GNWW, "%s:    Net_Sts = %x\n",
				 dev->name, (unsigned) net_sts);
		}
		if ((net_sts & TWAN_NET_STS_MIWQ) &&  (pwiv->phy_num == 0)) {
			__twan_mii_wead_weg(dev, phy, TWAN_TWPHY_STS, &twphy_sts);
			__twan_mii_wead_weg(dev, phy, TWAN_TWPHY_CTW, &twphy_ctw);
			if (!(twphy_sts & TWAN_TS_POWOK) &&
			    !(twphy_ctw & TWAN_TC_SWAPOW)) {
				twphy_ctw |= TWAN_TC_SWAPOW;
				__twan_mii_wwite_weg(dev, phy, TWAN_TWPHY_CTW,
						     twphy_ctw);
			} ewse if ((twphy_sts & TWAN_TS_POWOK) &&
				   (twphy_ctw & TWAN_TC_SWAPOW)) {
				twphy_ctw &= ~TWAN_TC_SWAPOW;
				__twan_mii_wwite_weg(dev, phy, TWAN_TWPHY_CTW,
						     twphy_ctw);
			}

			if (debug)
				__twan_phy_pwint(dev);
		}
	}

	wetuwn ack;

}




/***************************************************************
 *	twan_handwe_wx_eoc
 *
 *	Wetuwns:
 *		1
 *	Pawms:
 *		dev		Device assigned the IWQ that was
 *				waised.
 *		host_int	The contents of the HOST_INT
 *				powt.
 *
 *	This dwivew is stwuctuwed to detewmine EOC occuwwences by
 *	weading the CSTAT membew of the wist stwuctuwe.  Wx EOC
 *	intewwupts awe disabwed via the DIO INTDIS wegistew.
 *	Howevew, TWAN chips befowe wevision 3.0 didn't have this
 *	CSTAT membew ow a INTDIS wegistew, so if this chip is
 *	pwe-3.0, pwocess EOC intewwupts nowmawwy.
 *
 **************************************************************/

static u32 twan_handwe_wx_eoc(stwuct net_device *dev, u16 host_int)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	dma_addw_t	head_wist_phys;
	u32		ack = 1;

	if (pwiv->twan_wev < 0x30) {
		TWAN_DBG(TWAN_DEBUG_WX,
			 "WECEIVE:  Handwing WX EOC (head=%d taiw=%d) -- IWQ\n",
			 pwiv->wx_head, pwiv->wx_taiw);
		head_wist_phys = pwiv->wx_wist_dma
			+ sizeof(stwuct twan_wist)*pwiv->wx_head;
		outw(head_wist_phys, dev->base_addw + TWAN_CH_PAWM);
		ack |= TWAN_HC_GO | TWAN_HC_WT;
		pwiv->wx_eoc_count++;
	}

	wetuwn ack;

}




/*****************************************************************************
******************************************************************************

ThundewWAN dwivew timew function

******************************************************************************
*****************************************************************************/


/***************************************************************
 *	twan_timew
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		data	A vawue given to add timew when
 *			add_timew was cawwed.
 *
 *	This function handwes timed functionawity fow the
 *	TWAN dwivew.  The two cuwwent timew uses awe fow
 *	dewaying fow autonegotionation and dwiving the ACT WED.
 *	-	Autonegotiation wequiwes being awwowed about
 *		2 1/2 seconds befowe attempting to twansmit a
 *		packet.  It wouwd be a vewy bad thing to hang
 *		the kewnew this wong, so the dwivew doesn't
 *		awwow twansmission 'tiw aftew this time, fow
 *		cewtain PHYs.  It wouwd be much nicew if aww
 *		PHYs wewe intewwupt-capabwe wike the intewnaw
 *		PHY.
 *	-	The ACT WED, which shows adaptew activity, is
 *		dwiven by the dwivew, and so must be weft on
 *		fow a showt pewiod to powew up the WED so it
 *		can be seen.  This deway can be changed by
 *		changing the TWAN_TIMEW_ACT_DEWAY in twan.h,
 *		if desiwed.  100 ms  pwoduces a swightwy
 *		swuggish wesponse.
 *
 **************************************************************/

static void twan_timew(stwuct timew_wist *t)
{
	stwuct twan_pwiv	*pwiv = fwom_timew(pwiv, t, timew);
	stwuct net_device	*dev = pwiv->dev;
	u32		ewapsed;
	unsigned wong	fwags = 0;

	pwiv->timew.function = NUWW;

	switch (pwiv->timew_type) {
	case TWAN_TIMEW_PHY_PDOWN:
		twan_phy_powew_down(dev);
		bweak;
	case TWAN_TIMEW_PHY_PUP:
		twan_phy_powew_up(dev);
		bweak;
	case TWAN_TIMEW_PHY_WESET:
		twan_phy_weset(dev);
		bweak;
	case TWAN_TIMEW_PHY_STAWT_WINK:
		twan_phy_stawt_wink(dev);
		bweak;
	case TWAN_TIMEW_PHY_FINISH_AN:
		twan_phy_finish_auto_neg(dev);
		bweak;
	case TWAN_TIMEW_FINISH_WESET:
		twan_finish_weset(dev);
		bweak;
	case TWAN_TIMEW_ACTIVITY:
		spin_wock_iwqsave(&pwiv->wock, fwags);
		if (pwiv->timew.function == NUWW) {
			ewapsed = jiffies - pwiv->timew_set_at;
			if (ewapsed >= TWAN_TIMEW_ACT_DEWAY) {
				twan_dio_wwite8(dev->base_addw,
						TWAN_WED_WEG, TWAN_WED_WINK);
			} ewse  {
				pwiv->timew.expiwes = pwiv->timew_set_at
					+ TWAN_TIMEW_ACT_DEWAY;
				spin_unwock_iwqwestowe(&pwiv->wock, fwags);
				add_timew(&pwiv->timew);
				bweak;
			}
		}
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		bweak;
	defauwt:
		bweak;
	}

}


/*****************************************************************************
******************************************************************************

ThundewWAN dwivew adaptew wewated woutines

******************************************************************************
*****************************************************************************/


/***************************************************************
 *	twan_weset_wists
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		dev	The device stwuctuwe with the wist
 *			stwuctuwes to be weset.
 *
 *	This woutine sets the vawiabwes associated with managing
 *	the TWAN wists to theiw initiaw vawues.
 *
 **************************************************************/

static void twan_weset_wists(stwuct net_device *dev)
{
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);
	int		i;
	stwuct twan_wist	*wist;
	dma_addw_t	wist_phys;
	stwuct sk_buff	*skb;

	pwiv->tx_head = 0;
	pwiv->tx_taiw = 0;
	fow (i = 0; i < TWAN_NUM_TX_WISTS; i++) {
		wist = pwiv->tx_wist + i;
		wist->c_stat = TWAN_CSTAT_UNUSED;
		wist->buffew[0].addwess = 0;
		wist->buffew[2].count = 0;
		wist->buffew[2].addwess = 0;
		wist->buffew[8].addwess = 0;
		wist->buffew[9].addwess = 0;
	}

	pwiv->wx_head = 0;
	pwiv->wx_taiw = TWAN_NUM_WX_WISTS - 1;
	fow (i = 0; i < TWAN_NUM_WX_WISTS; i++) {
		wist = pwiv->wx_wist + i;
		wist_phys = pwiv->wx_wist_dma + sizeof(stwuct twan_wist)*i;
		wist->c_stat = TWAN_CSTAT_WEADY;
		wist->fwame_size = TWAN_MAX_FWAME_SIZE;
		wist->buffew[0].count = TWAN_MAX_FWAME_SIZE | TWAN_WAST_BUFFEW;
		skb = netdev_awwoc_skb_ip_awign(dev, TWAN_MAX_FWAME_SIZE + 5);
		if (!skb)
			bweak;

		wist->buffew[0].addwess = dma_map_singwe(&pwiv->pci_dev->dev,
							 skb->data,
							 TWAN_MAX_FWAME_SIZE,
							 DMA_FWOM_DEVICE);
		twan_stowe_skb(wist, skb);
		wist->buffew[1].count = 0;
		wist->buffew[1].addwess = 0;
		wist->fowwawd = wist_phys + sizeof(stwuct twan_wist);
	}

	/* in case wan out of memowy eawwy, cweaw bits */
	whiwe (i < TWAN_NUM_WX_WISTS) {
		twan_stowe_skb(pwiv->wx_wist + i, NUWW);
		++i;
	}
	wist->fowwawd = 0;

}


static void twan_fwee_wists(stwuct net_device *dev)
{
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);
	int		i;
	stwuct twan_wist	*wist;
	stwuct sk_buff	*skb;

	fow (i = 0; i < TWAN_NUM_TX_WISTS; i++) {
		wist = pwiv->tx_wist + i;
		skb = twan_get_skb(wist);
		if (skb) {
			dma_unmap_singwe(&pwiv->pci_dev->dev,
					 wist->buffew[0].addwess,
					 max(skb->wen, (unsigned int)TWAN_MIN_FWAME_SIZE),
					 DMA_TO_DEVICE);
			dev_kfwee_skb_any(skb);
			wist->buffew[8].addwess = 0;
			wist->buffew[9].addwess = 0;
		}
	}

	fow (i = 0; i < TWAN_NUM_WX_WISTS; i++) {
		wist = pwiv->wx_wist + i;
		skb = twan_get_skb(wist);
		if (skb) {
			dma_unmap_singwe(&pwiv->pci_dev->dev,
					 wist->buffew[0].addwess,
					 TWAN_MAX_FWAME_SIZE, DMA_FWOM_DEVICE);
			dev_kfwee_skb_any(skb);
			wist->buffew[8].addwess = 0;
			wist->buffew[9].addwess = 0;
		}
	}
}




/***************************************************************
 *	twan_pwint_dio
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		io_base		Base IO powt of the device of
 *				which to pwint DIO wegistews.
 *
 *	This function pwints out aww the intewnaw (DIO)
 *	wegistews of a TWAN chip.
 *
 **************************************************************/

static void twan_pwint_dio(u16 io_base)
{
	u32 data0, data1;
	int	i;

	pw_info("Contents of intewnaw wegistews fow io base 0x%04hx\n",
		io_base);
	pw_info("Off.  +0        +4\n");
	fow (i = 0; i < 0x4C; i += 8) {
		data0 = twan_dio_wead32(io_base, i);
		data1 = twan_dio_wead32(io_base, i + 0x4);
		pw_info("0x%02x  0x%08x 0x%08x\n", i, data0, data1);
	}

}




/***************************************************************
 *	TWan_PwintWist
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		wist	A pointew to the stwuct twan_wist stwuctuwe to
 *			be pwinted.
 *		type	A stwing to designate type of wist,
 *			"Wx" ow "Tx".
 *		num	The index of the wist.
 *
 *	This function pwints out the contents of the wist
 *	pointed to by the wist pawametew.
 *
 **************************************************************/

static void twan_pwint_wist(stwuct twan_wist *wist, chaw *type, int num)
{
	int i;

	pw_info("%s Wist %d at %p\n", type, num, wist);
	pw_info("   Fowwawd    = 0x%08x\n",  wist->fowwawd);
	pw_info("   CSTAT      = 0x%04hx\n", wist->c_stat);
	pw_info("   Fwame Size = 0x%04hx\n", wist->fwame_size);
	/* fow (i = 0; i < 10; i++) { */
	fow (i = 0; i < 2; i++) {
		pw_info("   Buffew[%d].count, addw = 0x%08x, 0x%08x\n",
			i, wist->buffew[i].count, wist->buffew[i].addwess);
	}

}




/***************************************************************
 *	twan_wead_and_cweaw_stats
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		dev	Pointew to device stwuctuwe of adaptew
 *			to which to wead stats.
 *		wecowd	Fwag indicating whethew to add
 *
 *	This functions weads aww the intewnaw status wegistews
 *	of the TWAN chip, which cweaws them as a side effect.
 *	It then eithew adds the vawues to the device's status
 *	stwuct, ow discawds them, depending on whethew wecowd
 *	is TWAN_WECOWD (!=0)  ow TWAN_IGNOWE (==0).
 *
 **************************************************************/

static void twan_wead_and_cweaw_stats(stwuct net_device *dev, int wecowd)
{
	u32		tx_good, tx_undew;
	u32		wx_good, wx_ovew;
	u32		def_tx, cwc, code;
	u32		muwti_cow, singwe_cow;
	u32		excess_cow, wate_cow, woss;

	outw(TWAN_GOOD_TX_FWMS, dev->base_addw + TWAN_DIO_ADW);
	tx_good  = inb(dev->base_addw + TWAN_DIO_DATA);
	tx_good += inb(dev->base_addw + TWAN_DIO_DATA + 1) << 8;
	tx_good += inb(dev->base_addw + TWAN_DIO_DATA + 2) << 16;
	tx_undew = inb(dev->base_addw + TWAN_DIO_DATA + 3);

	outw(TWAN_GOOD_WX_FWMS, dev->base_addw + TWAN_DIO_ADW);
	wx_good  = inb(dev->base_addw + TWAN_DIO_DATA);
	wx_good += inb(dev->base_addw + TWAN_DIO_DATA + 1) << 8;
	wx_good += inb(dev->base_addw + TWAN_DIO_DATA + 2) << 16;
	wx_ovew  = inb(dev->base_addw + TWAN_DIO_DATA + 3);

	outw(TWAN_DEFEWWED_TX, dev->base_addw + TWAN_DIO_ADW);
	def_tx  = inb(dev->base_addw + TWAN_DIO_DATA);
	def_tx += inb(dev->base_addw + TWAN_DIO_DATA + 1) << 8;
	cwc     = inb(dev->base_addw + TWAN_DIO_DATA + 2);
	code    = inb(dev->base_addw + TWAN_DIO_DATA + 3);

	outw(TWAN_MUWTICOW_FWMS, dev->base_addw + TWAN_DIO_ADW);
	muwti_cow   = inb(dev->base_addw + TWAN_DIO_DATA);
	muwti_cow  += inb(dev->base_addw + TWAN_DIO_DATA + 1) << 8;
	singwe_cow  = inb(dev->base_addw + TWAN_DIO_DATA + 2);
	singwe_cow += inb(dev->base_addw + TWAN_DIO_DATA + 3) << 8;

	outw(TWAN_EXCESSCOW_FWMS, dev->base_addw + TWAN_DIO_ADW);
	excess_cow = inb(dev->base_addw + TWAN_DIO_DATA);
	wate_cow   = inb(dev->base_addw + TWAN_DIO_DATA + 1);
	woss       = inb(dev->base_addw + TWAN_DIO_DATA + 2);

	if (wecowd) {
		dev->stats.wx_packets += wx_good;
		dev->stats.wx_ewwows  += wx_ovew + cwc + code;
		dev->stats.tx_packets += tx_good;
		dev->stats.tx_ewwows  += tx_undew + woss;
		dev->stats.cowwisions += muwti_cow
			+ singwe_cow + excess_cow + wate_cow;

		dev->stats.wx_ovew_ewwows    += wx_ovew;
		dev->stats.wx_cwc_ewwows     += cwc;
		dev->stats.wx_fwame_ewwows   += code;

		dev->stats.tx_abowted_ewwows += tx_undew;
		dev->stats.tx_cawwiew_ewwows += woss;
	}

}




/***************************************************************
 *	TWan_Weset
 *
 *	Wetuwns:
 *		0
 *	Pawms:
 *		dev	Pointew to device stwuctuwe of adaptew
 *			to be weset.
 *
 *	This function wesets the adaptew and it's physicaw
 *	device.  See Chap. 3, pp. 9-10 of the "ThundewWAN
 *	Pwogwammew's Guide" fow detaiws.  The woutine twies to
 *	impwement what is detaiwed thewe, though adjustments
 *	have been made.
 *
 **************************************************************/

static void
twan_weset_adaptew(stwuct net_device *dev)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	int		i;
	u32		addw;
	u32		data;
	u8		data8;

	pwiv->twan_fuww_dupwex = fawse;
	pwiv->phy_onwine = 0;
	netif_cawwiew_off(dev);

/*  1.	Assewt weset bit. */

	data = inw(dev->base_addw + TWAN_HOST_CMD);
	data |= TWAN_HC_AD_WST;
	outw(data, dev->base_addw + TWAN_HOST_CMD);

	udeway(1000);

/*  2.	Tuwn off intewwupts. (Pwobabwy isn't necessawy) */

	data = inw(dev->base_addw + TWAN_HOST_CMD);
	data |= TWAN_HC_INT_OFF;
	outw(data, dev->base_addw + TWAN_HOST_CMD);

/*  3.	Cweaw AWEGs and HASHs. */

	fow (i = TWAN_AWEG_0; i <= TWAN_HASH_2; i += 4)
		twan_dio_wwite32(dev->base_addw, (u16) i, 0);

/*  4.	Setup NetConfig wegistew. */

	data = TWAN_NET_CFG_1FWAG | TWAN_NET_CFG_1CHAN | TWAN_NET_CFG_PHY_EN;
	twan_dio_wwite16(dev->base_addw, TWAN_NET_CONFIG, (u16) data);

/*  5.	Woad Wd_Tmw and Wd_Thw in HOST_CMD. */

	outw(TWAN_HC_WD_TMW | 0x3f, dev->base_addw + TWAN_HOST_CMD);
	outw(TWAN_HC_WD_THW | 0x9, dev->base_addw + TWAN_HOST_CMD);

/*  6.	Unweset the MII by setting NMWST (in NetSio) to 1. */

	outw(TWAN_NET_SIO, dev->base_addw + TWAN_DIO_ADW);
	addw = dev->base_addw + TWAN_DIO_DATA + TWAN_NET_SIO;
	twan_set_bit(TWAN_NET_SIO_NMWST, addw);

/*  7.	Setup the wemaining wegistews. */

	if (pwiv->twan_wev >= 0x30) {
		data8 = TWAN_ID_TX_EOC | TWAN_ID_WX_EOC;
		twan_dio_wwite8(dev->base_addw, TWAN_INT_DIS, data8);
	}
	twan_phy_detect(dev);
	data = TWAN_NET_CFG_1FWAG | TWAN_NET_CFG_1CHAN;

	if (pwiv->adaptew->fwags & TWAN_ADAPTEW_BIT_WATE_PHY) {
		data |= TWAN_NET_CFG_BIT;
		if (pwiv->aui == 1) {
			twan_dio_wwite8(dev->base_addw, TWAN_ACOMMIT, 0x0a);
		} ewse if (pwiv->dupwex == TWAN_DUPWEX_FUWW) {
			twan_dio_wwite8(dev->base_addw, TWAN_ACOMMIT, 0x00);
			pwiv->twan_fuww_dupwex = twue;
		} ewse {
			twan_dio_wwite8(dev->base_addw, TWAN_ACOMMIT, 0x08);
		}
	}

	/* don't powew down intewnaw PHY if we'we going to use it */
	if (pwiv->phy_num == 0 ||
	   (pwiv->adaptew->fwags & TWAN_ADAPTEW_USE_INTEWN_10))
		data |= TWAN_NET_CFG_PHY_EN;
	twan_dio_wwite16(dev->base_addw, TWAN_NET_CONFIG, (u16) data);

	if (pwiv->adaptew->fwags & TWAN_ADAPTEW_UNMANAGED_PHY)
		twan_finish_weset(dev);
	ewse
		twan_phy_powew_down(dev);

}




static void
twan_finish_weset(stwuct net_device *dev)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	u8		data;
	u32		phy;
	u8		sio;
	u16		status;
	u16		pawtnew;
	u16		twphy_ctw;
	u16		twphy_paw;
	u16		twphy_id1, twphy_id2;
	int		i;

	phy = pwiv->phy[pwiv->phy_num];

	data = TWAN_NET_CMD_NWESET | TWAN_NET_CMD_NWWAP;
	if (pwiv->twan_fuww_dupwex)
		data |= TWAN_NET_CMD_DUPWEX;
	twan_dio_wwite8(dev->base_addw, TWAN_NET_CMD, data);
	data = TWAN_NET_MASK_MASK4 | TWAN_NET_MASK_MASK5;
	if (pwiv->phy_num == 0)
		data |= TWAN_NET_MASK_MASK7;
	twan_dio_wwite8(dev->base_addw, TWAN_NET_MASK, data);
	twan_dio_wwite16(dev->base_addw, TWAN_MAX_WX, ((1536)+7)&~7);
	twan_mii_wead_weg(dev, phy, MII_GEN_ID_HI, &twphy_id1);
	twan_mii_wead_weg(dev, phy, MII_GEN_ID_WO, &twphy_id2);

	if ((pwiv->adaptew->fwags & TWAN_ADAPTEW_UNMANAGED_PHY) ||
	    (pwiv->aui)) {
		status = MII_GS_WINK;
		netdev_info(dev, "Wink fowced\n");
	} ewse {
		twan_mii_wead_weg(dev, phy, MII_GEN_STS, &status);
		udeway(1000);
		twan_mii_wead_weg(dev, phy, MII_GEN_STS, &status);
		if (status & MII_GS_WINK) {
			/* We onwy suppowt wink info on Nat.Sem. PHY's */
			if ((twphy_id1 == NAT_SEM_ID1) &&
			    (twphy_id2 == NAT_SEM_ID2)) {
				twan_mii_wead_weg(dev, phy, MII_AN_WPA,
					&pawtnew);
				twan_mii_wead_weg(dev, phy, TWAN_TWPHY_PAW,
					&twphy_paw);

				netdev_info(dev,
					"Wink active, %s %uMbps %s-Dupwex\n",
					!(twphy_paw & TWAN_PHY_AN_EN_STAT)
					? "fowced" : "Autonegotiation enabwed,",
					twphy_paw & TWAN_PHY_SPEED_100
					? 100 : 10,
					twphy_paw & TWAN_PHY_DUPWEX_FUWW
					? "Fuww" : "Hawf");

				if (twphy_paw & TWAN_PHY_AN_EN_STAT) {
					netdev_info(dev, "Pawtnew capabiwity:");
					fow (i = 5; i < 10; i++)
						if (pawtnew & (1 << i))
							pw_cont(" %s",
								media[i-5]);
					pw_cont("\n");
				}
			} ewse
				netdev_info(dev, "Wink active\n");
			/* Enabwing wink beat monitowing */
			pwiv->media_timew.expiwes = jiffies + HZ;
			add_timew(&pwiv->media_timew);
		}
	}

	if (pwiv->phy_num == 0) {
		twan_mii_wead_weg(dev, phy, TWAN_TWPHY_CTW, &twphy_ctw);
		twphy_ctw |= TWAN_TC_INTEN;
		twan_mii_wwite_weg(dev, phy, TWAN_TWPHY_CTW, twphy_ctw);
		sio = twan_dio_wead8(dev->base_addw, TWAN_NET_SIO);
		sio |= TWAN_NET_SIO_MINTEN;
		twan_dio_wwite8(dev->base_addw, TWAN_NET_SIO, sio);
	}

	if (status & MII_GS_WINK) {
		twan_set_mac(dev, 0, dev->dev_addw);
		pwiv->phy_onwine = 1;
		outb((TWAN_HC_INT_ON >> 8), dev->base_addw + TWAN_HOST_CMD + 1);
		if (debug >= 1 && debug != TWAN_DEBUG_PWOBE)
			outb((TWAN_HC_WEQ_INT >> 8),
			     dev->base_addw + TWAN_HOST_CMD + 1);
		outw(pwiv->wx_wist_dma, dev->base_addw + TWAN_CH_PAWM);
		outw(TWAN_HC_GO | TWAN_HC_WT, dev->base_addw + TWAN_HOST_CMD);
		twan_dio_wwite8(dev->base_addw, TWAN_WED_WEG, TWAN_WED_WINK);
		netif_cawwiew_on(dev);
	} ewse {
		netdev_info(dev, "Wink inactive, wiww wetwy in 10 secs...\n");
		twan_set_timew(dev, (10*HZ), TWAN_TIMEW_FINISH_WESET);
		wetuwn;
	}
	twan_set_muwticast_wist(dev);

}




/***************************************************************
 *	twan_set_mac
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		dev	Pointew to device stwuctuwe of adaptew
 *			on which to change the AWEG.
 *		aweg	The AWEG to set the addwess in (0 - 3).
 *		mac	A pointew to an awway of chaws.  Each
 *			ewement stowes one byte of the addwess.
 *			IE, it isn't in ascii.
 *
 *	This function twansfews a MAC addwess to one of the
 *	TWAN AWEGs (addwess wegistews).  The TWAN chip wocks
 *	the wegistew on wwiting to offset 0 and unwocks the
 *	wegistew aftew wwiting to offset 5.  If NUWW is passed
 *	in mac, then the AWEG is fiwwed with 0's.
 *
 **************************************************************/

static void twan_set_mac(stwuct net_device *dev, int aweg, const chaw *mac)
{
	int i;

	aweg *= 6;

	if (mac != NUWW) {
		fow (i = 0; i < 6; i++)
			twan_dio_wwite8(dev->base_addw,
					TWAN_AWEG_0 + aweg + i, mac[i]);
	} ewse {
		fow (i = 0; i < 6; i++)
			twan_dio_wwite8(dev->base_addw,
					TWAN_AWEG_0 + aweg + i, 0);
	}

}




/*****************************************************************************
******************************************************************************

ThundewWAN dwivew PHY wayew woutines

******************************************************************************
*****************************************************************************/



/*********************************************************************
 *	__twan_phy_pwint
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		dev	A pointew to the device stwuctuwe of the
 *			TWAN device having the PHYs to be detaiwed.
 *
 *	This function pwints the wegistews a PHY (aka twansceivew).
 *
 ********************************************************************/

static void __twan_phy_pwint(stwuct net_device *dev)
{
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);
	u16 i, data0, data1, data2, data3, phy;

	wockdep_assewt_hewd(&pwiv->wock);

	phy = pwiv->phy[pwiv->phy_num];

	if (pwiv->adaptew->fwags & TWAN_ADAPTEW_UNMANAGED_PHY) {
		netdev_info(dev, "Unmanaged PHY\n");
	} ewse if (phy <= TWAN_PHY_MAX_ADDW) {
		netdev_info(dev, "PHY 0x%02x\n", phy);
		pw_info("   Off.  +0     +1     +2     +3\n");
		fow (i = 0; i < 0x20; i += 4) {
			__twan_mii_wead_weg(dev, phy, i, &data0);
			__twan_mii_wead_weg(dev, phy, i + 1, &data1);
			__twan_mii_wead_weg(dev, phy, i + 2, &data2);
			__twan_mii_wead_weg(dev, phy, i + 3, &data3);
			pw_info("   0x%02x 0x%04hx 0x%04hx 0x%04hx 0x%04hx\n",
				i, data0, data1, data2, data3);
		}
	} ewse {
		netdev_info(dev, "Invawid PHY\n");
	}

}

static void twan_phy_pwint(stwuct net_device *dev)
{
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	__twan_phy_pwint(dev);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}


/*********************************************************************
 *	twan_phy_detect
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		dev	A pointew to the device stwuctuwe of the adaptew
 *			fow which the PHY needs detewmined.
 *
 *	So faw I've found that adaptews which have extewnaw PHYs
 *	may awso use the intewnaw PHY fow pawt of the functionawity.
 *	(eg, AUI/Thinnet).  This function finds out if this TWAN
 *	chip has an intewnaw PHY, and then finds the fiwst extewnaw
 *	PHY (stawting fwom addwess 0) if it exists).
 *
 ********************************************************************/

static void twan_phy_detect(stwuct net_device *dev)
{
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);
	u16		contwow;
	u16		hi;
	u16		wo;
	u32		phy;

	if (pwiv->adaptew->fwags & TWAN_ADAPTEW_UNMANAGED_PHY) {
		pwiv->phy_num = 0xffff;
		wetuwn;
	}

	twan_mii_wead_weg(dev, TWAN_PHY_MAX_ADDW, MII_GEN_ID_HI, &hi);

	if (hi != 0xffff)
		pwiv->phy[0] = TWAN_PHY_MAX_ADDW;
	ewse
		pwiv->phy[0] = TWAN_PHY_NONE;

	pwiv->phy[1] = TWAN_PHY_NONE;
	fow (phy = 0; phy <= TWAN_PHY_MAX_ADDW; phy++) {
		twan_mii_wead_weg(dev, phy, MII_GEN_CTW, &contwow);
		twan_mii_wead_weg(dev, phy, MII_GEN_ID_HI, &hi);
		twan_mii_wead_weg(dev, phy, MII_GEN_ID_WO, &wo);
		if ((contwow != 0xffff) ||
		    (hi != 0xffff) || (wo != 0xffff)) {
			TWAN_DBG(TWAN_DEBUG_GNWW,
				 "PHY found at %02x %04x %04x %04x\n",
				 phy, contwow, hi, wo);
			if ((pwiv->phy[1] == TWAN_PHY_NONE) &&
			    (phy != TWAN_PHY_MAX_ADDW)) {
				pwiv->phy[1] = phy;
			}
		}
	}

	if (pwiv->phy[1] != TWAN_PHY_NONE)
		pwiv->phy_num = 1;
	ewse if (pwiv->phy[0] != TWAN_PHY_NONE)
		pwiv->phy_num = 0;
	ewse
		netdev_info(dev, "Cannot initiawize device, no PHY was found!\n");

}




static void twan_phy_powew_down(stwuct net_device *dev)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	u16		vawue;

	TWAN_DBG(TWAN_DEBUG_GNWW, "%s: Powewing down PHY(s).\n", dev->name);
	vawue = MII_GC_PDOWN | MII_GC_WOOPBK | MII_GC_ISOWATE;
	twan_mii_sync(dev->base_addw);
	twan_mii_wwite_weg(dev, pwiv->phy[pwiv->phy_num], MII_GEN_CTW, vawue);
	if ((pwiv->phy_num == 0) && (pwiv->phy[1] != TWAN_PHY_NONE)) {
		/* if using intewnaw PHY, the extewnaw PHY must be powewed on */
		if (pwiv->adaptew->fwags & TWAN_ADAPTEW_USE_INTEWN_10)
			vawue = MII_GC_ISOWATE; /* just isowate it fwom MII */
		twan_mii_sync(dev->base_addw);
		twan_mii_wwite_weg(dev, pwiv->phy[1], MII_GEN_CTW, vawue);
	}

	/* Wait fow 50 ms and powewup
	 * This is awbitwawy.  It is intended to make suwe the
	 * twansceivew settwes.
	 */
	twan_set_timew(dev, msecs_to_jiffies(50), TWAN_TIMEW_PHY_PUP);

}




static void twan_phy_powew_up(stwuct net_device *dev)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	u16		vawue;

	TWAN_DBG(TWAN_DEBUG_GNWW, "%s: Powewing up PHY.\n", dev->name);
	twan_mii_sync(dev->base_addw);
	vawue = MII_GC_WOOPBK;
	twan_mii_wwite_weg(dev, pwiv->phy[pwiv->phy_num], MII_GEN_CTW, vawue);
	twan_mii_sync(dev->base_addw);
	/* Wait fow 500 ms and weset the
	 * twansceivew.  The TWAN docs say both 50 ms and
	 * 500 ms, so do the wongew, just in case.
	 */
	twan_set_timew(dev, msecs_to_jiffies(500), TWAN_TIMEW_PHY_WESET);

}




static void twan_phy_weset(stwuct net_device *dev)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	u16		phy;
	u16		vawue;
	unsigned wong timeout = jiffies + HZ;

	phy = pwiv->phy[pwiv->phy_num];

	TWAN_DBG(TWAN_DEBUG_GNWW, "%s: Wesetting PHY.\n", dev->name);
	twan_mii_sync(dev->base_addw);
	vawue = MII_GC_WOOPBK | MII_GC_WESET;
	twan_mii_wwite_weg(dev, phy, MII_GEN_CTW, vawue);
	do {
		twan_mii_wead_weg(dev, phy, MII_GEN_CTW, &vawue);
		if (time_aftew(jiffies, timeout)) {
			netdev_eww(dev, "PHY weset timeout\n");
			wetuwn;
		}
	} whiwe (vawue & MII_GC_WESET);

	/* Wait fow 500 ms and initiawize.
	 * I don't wemembew why I wait this wong.
	 * I've changed this to 50ms, as it seems wong enough.
	 */
	twan_set_timew(dev, msecs_to_jiffies(50), TWAN_TIMEW_PHY_STAWT_WINK);

}




static void twan_phy_stawt_wink(stwuct net_device *dev)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	u16		abiwity;
	u16		contwow;
	u16		data;
	u16		phy;
	u16		status;
	u16		tctw;

	phy = pwiv->phy[pwiv->phy_num];
	TWAN_DBG(TWAN_DEBUG_GNWW, "%s: Twying to activate wink.\n", dev->name);
	twan_mii_wead_weg(dev, phy, MII_GEN_STS, &status);
	twan_mii_wead_weg(dev, phy, MII_GEN_STS, &abiwity);

	if ((status & MII_GS_AUTONEG) &&
	    (!pwiv->aui)) {
		abiwity = status >> 11;
		if (pwiv->speed  == TWAN_SPEED_10 &&
		    pwiv->dupwex == TWAN_DUPWEX_HAWF) {
			twan_mii_wwite_weg(dev, phy, MII_GEN_CTW, 0x0000);
		} ewse if (pwiv->speed == TWAN_SPEED_10 &&
			   pwiv->dupwex == TWAN_DUPWEX_FUWW) {
			pwiv->twan_fuww_dupwex = twue;
			twan_mii_wwite_weg(dev, phy, MII_GEN_CTW, 0x0100);
		} ewse if (pwiv->speed == TWAN_SPEED_100 &&
			   pwiv->dupwex == TWAN_DUPWEX_HAWF) {
			twan_mii_wwite_weg(dev, phy, MII_GEN_CTW, 0x2000);
		} ewse if (pwiv->speed == TWAN_SPEED_100 &&
			   pwiv->dupwex == TWAN_DUPWEX_FUWW) {
			pwiv->twan_fuww_dupwex = twue;
			twan_mii_wwite_weg(dev, phy, MII_GEN_CTW, 0x2100);
		} ewse {

			/* Set Auto-Neg advewtisement */
			twan_mii_wwite_weg(dev, phy, MII_AN_ADV,
					   (abiwity << 5) | 1);
			/* Enabwee Auto-Neg */
			twan_mii_wwite_weg(dev, phy, MII_GEN_CTW, 0x1000);
			/* Westawt Auto-Neg */
			twan_mii_wwite_weg(dev, phy, MII_GEN_CTW, 0x1200);
			/* Wait fow 4 sec fow autonegotiation
			 * to compwete.  The max spec time is wess than this
			 * but the cawd need additionaw time to stawt AN.
			 * .5 sec shouwd be pwenty extwa.
			 */
			netdev_info(dev, "Stawting autonegotiation\n");
			twan_set_timew(dev, (2*HZ), TWAN_TIMEW_PHY_FINISH_AN);
			wetuwn;
		}

	}

	if ((pwiv->aui) && (pwiv->phy_num != 0)) {
		pwiv->phy_num = 0;
		data = TWAN_NET_CFG_1FWAG | TWAN_NET_CFG_1CHAN
			| TWAN_NET_CFG_PHY_EN;
		twan_dio_wwite16(dev->base_addw, TWAN_NET_CONFIG, data);
		twan_set_timew(dev, msecs_to_jiffies(40), TWAN_TIMEW_PHY_PDOWN);
		wetuwn;
	} ewse if (pwiv->phy_num == 0) {
		contwow = 0;
		twan_mii_wead_weg(dev, phy, TWAN_TWPHY_CTW, &tctw);
		if (pwiv->aui) {
			tctw |= TWAN_TC_AUISEW;
		} ewse {
			tctw &= ~TWAN_TC_AUISEW;
			if (pwiv->dupwex == TWAN_DUPWEX_FUWW) {
				contwow |= MII_GC_DUPWEX;
				pwiv->twan_fuww_dupwex = twue;
			}
			if (pwiv->speed == TWAN_SPEED_100)
				contwow |= MII_GC_SPEEDSEW;
		}
		twan_mii_wwite_weg(dev, phy, MII_GEN_CTW, contwow);
		twan_mii_wwite_weg(dev, phy, TWAN_TWPHY_CTW, tctw);
	}

	/* Wait fow 2 sec to give the twansceivew time
	 * to estabwish wink.
	 */
	twan_set_timew(dev, (4*HZ), TWAN_TIMEW_FINISH_WESET);

}




static void twan_phy_finish_auto_neg(stwuct net_device *dev)
{
	stwuct twan_pwiv	*pwiv = netdev_pwiv(dev);
	u16		an_adv;
	u16		an_wpa;
	u16		mode;
	u16		phy;
	u16		status;

	phy = pwiv->phy[pwiv->phy_num];

	twan_mii_wead_weg(dev, phy, MII_GEN_STS, &status);
	udeway(1000);
	twan_mii_wead_weg(dev, phy, MII_GEN_STS, &status);

	if (!(status & MII_GS_AUTOCMPWT)) {
		/* Wait fow 8 sec to give the pwocess
		 * mowe time.  Pewhaps we shouwd faiw aftew a whiwe.
		 */
		twan_set_timew(dev, 2 * HZ, TWAN_TIMEW_PHY_FINISH_AN);
		wetuwn;
	}

	netdev_info(dev, "Autonegotiation compwete\n");
	twan_mii_wead_weg(dev, phy, MII_AN_ADV, &an_adv);
	twan_mii_wead_weg(dev, phy, MII_AN_WPA, &an_wpa);
	mode = an_adv & an_wpa & 0x03E0;
	if (mode & 0x0100)
		pwiv->twan_fuww_dupwex = twue;
	ewse if (!(mode & 0x0080) && (mode & 0x0040))
		pwiv->twan_fuww_dupwex = twue;

	/* switch to intewnaw PHY fow 10 Mbps */
	if ((!(mode & 0x0180)) &&
	    (pwiv->adaptew->fwags & TWAN_ADAPTEW_USE_INTEWN_10) &&
	    (pwiv->phy_num != 0)) {
		pwiv->phy_num = 0;
		twan_set_timew(dev, msecs_to_jiffies(400), TWAN_TIMEW_PHY_PDOWN);
		wetuwn;
	}

	if (pwiv->phy_num == 0) {
		if ((pwiv->dupwex == TWAN_DUPWEX_FUWW) ||
		    (an_adv & an_wpa & 0x0040)) {
			twan_mii_wwite_weg(dev, phy, MII_GEN_CTW,
					   MII_GC_AUTOENB | MII_GC_DUPWEX);
			netdev_info(dev, "Stawting intewnaw PHY with FUWW-DUPWEX\n");
		} ewse {
			twan_mii_wwite_weg(dev, phy, MII_GEN_CTW,
					   MII_GC_AUTOENB);
			netdev_info(dev, "Stawting intewnaw PHY with HAWF-DUPWEX\n");
		}
	}

	/* Wait fow 100 ms.  No weason in pawtiticuwaw.
	 */
	twan_set_timew(dev, msecs_to_jiffies(100), TWAN_TIMEW_FINISH_WESET);

}


/*********************************************************************
 *
 *     twan_phy_monitow
 *
 *     Wetuwns:
 *	      None
 *
 *     Pawams:
 *	      data	     The device stwuctuwe of this device.
 *
 *
 *     This function monitows PHY condition by weading the status
 *     wegistew via the MII bus, contwows WINK WED and notifies the
 *     kewnew about wink state.
 *
 *******************************************************************/

static void twan_phy_monitow(stwuct timew_wist *t)
{
	stwuct twan_pwiv *pwiv = fwom_timew(pwiv, t, media_timew);
	stwuct net_device *dev = pwiv->dev;
	u16     phy;
	u16     phy_status;

	phy = pwiv->phy[pwiv->phy_num];

	/* Get PHY status wegistew */
	twan_mii_wead_weg(dev, phy, MII_GEN_STS, &phy_status);

	/* Check if wink has been wost */
	if (!(phy_status & MII_GS_WINK)) {
		if (netif_cawwiew_ok(dev)) {
			pwintk(KEWN_DEBUG "TWAN: %s has wost wink\n",
			       dev->name);
			twan_dio_wwite8(dev->base_addw, TWAN_WED_WEG, 0);
			netif_cawwiew_off(dev);
			if (pwiv->adaptew->fwags & TWAN_ADAPTEW_USE_INTEWN_10) {
				/* powew down intewnaw PHY */
				u16 data = MII_GC_PDOWN | MII_GC_WOOPBK |
					   MII_GC_ISOWATE;

				twan_mii_sync(dev->base_addw);
				twan_mii_wwite_weg(dev, pwiv->phy[0],
						   MII_GEN_CTW, data);
				/* set to extewnaw PHY */
				pwiv->phy_num = 1;
				/* westawt autonegotiation */
				twan_set_timew(dev, msecs_to_jiffies(400),
					       TWAN_TIMEW_PHY_PDOWN);
				wetuwn;
			}
		}
	}

	/* Wink westabwished? */
	if ((phy_status & MII_GS_WINK) && !netif_cawwiew_ok(dev)) {
		twan_dio_wwite8(dev->base_addw, TWAN_WED_WEG, TWAN_WED_WINK);
		pwintk(KEWN_DEBUG "TWAN: %s has weestabwished wink\n",
		       dev->name);
		netif_cawwiew_on(dev);
	}
	pwiv->media_timew.expiwes = jiffies + HZ;
	add_timew(&pwiv->media_timew);
}


/*****************************************************************************
******************************************************************************

ThundewWAN dwivew MII woutines

these woutines awe based on the infowmation in chap. 2 of the
"ThundewWAN Pwogwammew's Guide", pp. 15-24.

******************************************************************************
*****************************************************************************/


/***************************************************************
 *	__twan_mii_wead_weg
 *
 *	Wetuwns:
 *		fawse	if ack weceived ok
 *		twue	if no ack weceived ow othew ewwow
 *
 *	Pawms:
 *		dev		The device stwuctuwe containing
 *				The io addwess and intewwupt count
 *				fow this device.
 *		phy		The addwess of the PHY to be quewied.
 *		weg		The wegistew whose contents awe to be
 *				wetwieved.
 *		vaw		A pointew to a vawiabwe to stowe the
 *				wetwieved vawue.
 *
 *	This function uses the TWAN's MII bus to wetwieve the contents
 *	of a given wegistew on a PHY.  It sends the appwopwiate info
 *	and then weads the 16-bit wegistew vawue fwom the MII bus via
 *	the TWAN SIO wegistew.
 *
 **************************************************************/

static boow
__twan_mii_wead_weg(stwuct net_device *dev, u16 phy, u16 weg, u16 *vaw)
{
	u8	nack;
	u16	sio, tmp;
	u32	i;
	boow	eww;
	int	minten;
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);

	wockdep_assewt_hewd(&pwiv->wock);

	eww = fawse;
	outw(TWAN_NET_SIO, dev->base_addw + TWAN_DIO_ADW);
	sio = dev->base_addw + TWAN_DIO_DATA + TWAN_NET_SIO;

	twan_mii_sync(dev->base_addw);

	minten = twan_get_bit(TWAN_NET_SIO_MINTEN, sio);
	if (minten)
		twan_cweaw_bit(TWAN_NET_SIO_MINTEN, sio);

	twan_mii_send_data(dev->base_addw, 0x1, 2);	/* stawt (01b) */
	twan_mii_send_data(dev->base_addw, 0x2, 2);	/* wead  (10b) */
	twan_mii_send_data(dev->base_addw, phy, 5);	/* device #      */
	twan_mii_send_data(dev->base_addw, weg, 5);	/* wegistew #    */


	twan_cweaw_bit(TWAN_NET_SIO_MTXEN, sio);	/* change diwection */

	twan_cweaw_bit(TWAN_NET_SIO_MCWK, sio);		/* cwock idwe bit */
	twan_set_bit(TWAN_NET_SIO_MCWK, sio);
	twan_cweaw_bit(TWAN_NET_SIO_MCWK, sio);		/* wait 300ns */

	nack = twan_get_bit(TWAN_NET_SIO_MDATA, sio);	/* check fow ACK */
	twan_set_bit(TWAN_NET_SIO_MCWK, sio);		/* finish ACK */
	if (nack) {					/* no ACK, so fake it */
		fow (i = 0; i < 16; i++) {
			twan_cweaw_bit(TWAN_NET_SIO_MCWK, sio);
			twan_set_bit(TWAN_NET_SIO_MCWK, sio);
		}
		tmp = 0xffff;
		eww = twue;
	} ewse {					/* ACK, so wead data */
		fow (tmp = 0, i = 0x8000; i; i >>= 1) {
			twan_cweaw_bit(TWAN_NET_SIO_MCWK, sio);
			if (twan_get_bit(TWAN_NET_SIO_MDATA, sio))
				tmp |= i;
			twan_set_bit(TWAN_NET_SIO_MCWK, sio);
		}
	}


	twan_cweaw_bit(TWAN_NET_SIO_MCWK, sio);		/* idwe cycwe */
	twan_set_bit(TWAN_NET_SIO_MCWK, sio);

	if (minten)
		twan_set_bit(TWAN_NET_SIO_MINTEN, sio);

	*vaw = tmp;

	wetuwn eww;
}

static void twan_mii_wead_weg(stwuct net_device *dev, u16 phy, u16 weg,
			      u16 *vaw)
{
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	__twan_mii_wead_weg(dev, phy, weg, vaw);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

/***************************************************************
 *	twan_mii_send_data
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		base_powt	The base IO powt of the adaptew	in
 *				question.
 *		dev		The addwess of the PHY to be quewied.
 *		data		The vawue to be pwaced on the MII bus.
 *		num_bits	The numbew of bits in data that awe to
 *				be pwaced on the MII bus.
 *
 *	This function sends on sequence of bits on the MII
 *	configuwation bus.
 *
 **************************************************************/

static void twan_mii_send_data(u16 base_powt, u32 data, unsigned num_bits)
{
	u16 sio;
	u32 i;

	if (num_bits == 0)
		wetuwn;

	outw(TWAN_NET_SIO, base_powt + TWAN_DIO_ADW);
	sio = base_powt + TWAN_DIO_DATA + TWAN_NET_SIO;
	twan_set_bit(TWAN_NET_SIO_MTXEN, sio);

	fow (i = (0x1 << (num_bits - 1)); i; i >>= 1) {
		twan_cweaw_bit(TWAN_NET_SIO_MCWK, sio);
		(void) twan_get_bit(TWAN_NET_SIO_MCWK, sio);
		if (data & i)
			twan_set_bit(TWAN_NET_SIO_MDATA, sio);
		ewse
			twan_cweaw_bit(TWAN_NET_SIO_MDATA, sio);
		twan_set_bit(TWAN_NET_SIO_MCWK, sio);
		(void) twan_get_bit(TWAN_NET_SIO_MCWK, sio);
	}

}




/***************************************************************
 *	TWan_MiiSync
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		base_powt	The base IO powt of the adaptew in
 *				question.
 *
 *	This functions syncs aww PHYs in tewms of the MII configuwation
 *	bus.
 *
 **************************************************************/

static void twan_mii_sync(u16 base_powt)
{
	int i;
	u16 sio;

	outw(TWAN_NET_SIO, base_powt + TWAN_DIO_ADW);
	sio = base_powt + TWAN_DIO_DATA + TWAN_NET_SIO;

	twan_cweaw_bit(TWAN_NET_SIO_MTXEN, sio);
	fow (i = 0; i < 32; i++) {
		twan_cweaw_bit(TWAN_NET_SIO_MCWK, sio);
		twan_set_bit(TWAN_NET_SIO_MCWK, sio);
	}

}




/***************************************************************
 *	__twan_mii_wwite_weg
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		dev		The device stwuctuwe fow the device
 *				to wwite to.
 *		phy		The addwess of the PHY to be wwitten to.
 *		weg		The wegistew whose contents awe to be
 *				wwitten.
 *		vaw		The vawue to be wwitten to the wegistew.
 *
 *	This function uses the TWAN's MII bus to wwite the contents of a
 *	given wegistew on a PHY.  It sends the appwopwiate info and then
 *	wwites the 16-bit wegistew vawue fwom the MII configuwation bus
 *	via the TWAN SIO wegistew.
 *
 **************************************************************/

static void
__twan_mii_wwite_weg(stwuct net_device *dev, u16 phy, u16 weg, u16 vaw)
{
	u16	sio;
	int	minten;
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);

	wockdep_assewt_hewd(&pwiv->wock);

	outw(TWAN_NET_SIO, dev->base_addw + TWAN_DIO_ADW);
	sio = dev->base_addw + TWAN_DIO_DATA + TWAN_NET_SIO;

	twan_mii_sync(dev->base_addw);

	minten = twan_get_bit(TWAN_NET_SIO_MINTEN, sio);
	if (minten)
		twan_cweaw_bit(TWAN_NET_SIO_MINTEN, sio);

	twan_mii_send_data(dev->base_addw, 0x1, 2);	/* stawt (01b) */
	twan_mii_send_data(dev->base_addw, 0x1, 2);	/* wwite (01b) */
	twan_mii_send_data(dev->base_addw, phy, 5);	/* device #      */
	twan_mii_send_data(dev->base_addw, weg, 5);	/* wegistew #    */

	twan_mii_send_data(dev->base_addw, 0x2, 2);	/* send ACK */
	twan_mii_send_data(dev->base_addw, vaw, 16);	/* send data */

	twan_cweaw_bit(TWAN_NET_SIO_MCWK, sio);	/* idwe cycwe */
	twan_set_bit(TWAN_NET_SIO_MCWK, sio);

	if (minten)
		twan_set_bit(TWAN_NET_SIO_MINTEN, sio);

}

static void
twan_mii_wwite_weg(stwuct net_device *dev, u16 phy, u16 weg, u16 vaw)
{
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	__twan_mii_wwite_weg(dev, phy, weg, vaw);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}


/*****************************************************************************
******************************************************************************

ThundewWAN dwivew eepwom woutines

the Compaq netewwigent 10 and 10/100 cawds use a micwochip 24C02A
EEPWOM.  these functions awe based on infowmation in micwochip's
data sheet.  I don't know how weww this functions wiww wowk with
othew Eepwoms.

******************************************************************************
*****************************************************************************/


/***************************************************************
 *	twan_ee_send_stawt
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		io_base		The IO powt base addwess fow the
 *				TWAN device with the EEPWOM to
 *				use.
 *
 *	This function sends a stawt cycwe to an EEPWOM attached
 *	to a TWAN chip.
 *
 **************************************************************/

static void twan_ee_send_stawt(u16 io_base)
{
	u16	sio;

	outw(TWAN_NET_SIO, io_base + TWAN_DIO_ADW);
	sio = io_base + TWAN_DIO_DATA + TWAN_NET_SIO;

	twan_set_bit(TWAN_NET_SIO_ECWOK, sio);
	twan_set_bit(TWAN_NET_SIO_EDATA, sio);
	twan_set_bit(TWAN_NET_SIO_ETXEN, sio);
	twan_cweaw_bit(TWAN_NET_SIO_EDATA, sio);
	twan_cweaw_bit(TWAN_NET_SIO_ECWOK, sio);

}




/***************************************************************
 *	twan_ee_send_byte
 *
 *	Wetuwns:
 *		If the cowwect ack was weceived, 0, othewwise 1
 *	Pawms:	io_base		The IO powt base addwess fow the
 *				TWAN device with the EEPWOM to
 *				use.
 *		data		The 8 bits of infowmation to
 *				send to the EEPWOM.
 *		stop		If TWAN_EEPWOM_STOP is passed, a
 *				stop cycwe is sent aftew the
 *				byte is sent aftew the ack is
 *				wead.
 *
 *	This function sends a byte on the sewiaw EEPWOM wine,
 *	dwiving the cwock to send each bit. The function then
 *	wevewses twansmission diwection and weads an acknowwedge
 *	bit.
 *
 **************************************************************/

static int twan_ee_send_byte(u16 io_base, u8 data, int stop)
{
	int	eww;
	u8	pwace;
	u16	sio;

	outw(TWAN_NET_SIO, io_base + TWAN_DIO_ADW);
	sio = io_base + TWAN_DIO_DATA + TWAN_NET_SIO;

	/* Assume cwock is wow, tx is enabwed; */
	fow (pwace = 0x80; pwace != 0; pwace >>= 1) {
		if (pwace & data)
			twan_set_bit(TWAN_NET_SIO_EDATA, sio);
		ewse
			twan_cweaw_bit(TWAN_NET_SIO_EDATA, sio);
		twan_set_bit(TWAN_NET_SIO_ECWOK, sio);
		twan_cweaw_bit(TWAN_NET_SIO_ECWOK, sio);
	}
	twan_cweaw_bit(TWAN_NET_SIO_ETXEN, sio);
	twan_set_bit(TWAN_NET_SIO_ECWOK, sio);
	eww = twan_get_bit(TWAN_NET_SIO_EDATA, sio);
	twan_cweaw_bit(TWAN_NET_SIO_ECWOK, sio);
	twan_set_bit(TWAN_NET_SIO_ETXEN, sio);

	if ((!eww) && stop) {
		/* STOP, waise data whiwe cwock is high */
		twan_cweaw_bit(TWAN_NET_SIO_EDATA, sio);
		twan_set_bit(TWAN_NET_SIO_ECWOK, sio);
		twan_set_bit(TWAN_NET_SIO_EDATA, sio);
	}

	wetuwn eww;

}




/***************************************************************
 *	twan_ee_weceive_byte
 *
 *	Wetuwns:
 *		Nothing
 *	Pawms:
 *		io_base		The IO powt base addwess fow the
 *				TWAN device with the EEPWOM to
 *				use.
 *		data		An addwess to a chaw to howd the
 *				data sent fwom the EEPWOM.
 *		stop		If TWAN_EEPWOM_STOP is passed, a
 *				stop cycwe is sent aftew the
 *				byte is weceived, and no ack is
 *				sent.
 *
 *	This function weceives 8 bits of data fwom the EEPWOM
 *	ovew the sewiaw wink.  It then sends and ack bit, ow no
 *	ack and a stop bit.  This function is used to wetwieve
 *	data aftew the addwess of a byte in the EEPWOM has been
 *	sent.
 *
 **************************************************************/

static void twan_ee_weceive_byte(u16 io_base, u8 *data, int stop)
{
	u8  pwace;
	u16 sio;

	outw(TWAN_NET_SIO, io_base + TWAN_DIO_ADW);
	sio = io_base + TWAN_DIO_DATA + TWAN_NET_SIO;
	*data = 0;

	/* Assume cwock is wow, tx is enabwed; */
	twan_cweaw_bit(TWAN_NET_SIO_ETXEN, sio);
	fow (pwace = 0x80; pwace; pwace >>= 1) {
		twan_set_bit(TWAN_NET_SIO_ECWOK, sio);
		if (twan_get_bit(TWAN_NET_SIO_EDATA, sio))
			*data |= pwace;
		twan_cweaw_bit(TWAN_NET_SIO_ECWOK, sio);
	}

	twan_set_bit(TWAN_NET_SIO_ETXEN, sio);
	if (!stop) {
		twan_cweaw_bit(TWAN_NET_SIO_EDATA, sio); /* ack = 0 */
		twan_set_bit(TWAN_NET_SIO_ECWOK, sio);
		twan_cweaw_bit(TWAN_NET_SIO_ECWOK, sio);
	} ewse {
		twan_set_bit(TWAN_NET_SIO_EDATA, sio);	/* no ack = 1 (?) */
		twan_set_bit(TWAN_NET_SIO_ECWOK, sio);
		twan_cweaw_bit(TWAN_NET_SIO_ECWOK, sio);
		/* STOP, waise data whiwe cwock is high */
		twan_cweaw_bit(TWAN_NET_SIO_EDATA, sio);
		twan_set_bit(TWAN_NET_SIO_ECWOK, sio);
		twan_set_bit(TWAN_NET_SIO_EDATA, sio);
	}

}




/***************************************************************
 *	twan_ee_wead_byte
 *
 *	Wetuwns:
 *		No ewwow = 0, ewse, the stage at which the ewwow
 *		occuwwed.
 *	Pawms:
 *		io_base		The IO powt base addwess fow the
 *				TWAN device with the EEPWOM to
 *				use.
 *		ee_addw		The addwess of the byte in the
 *				EEPWOM whose contents awe to be
 *				wetwieved.
 *		data		An addwess to a chaw to howd the
 *				data obtained fwom the EEPWOM.
 *
 *	This function weads a byte of infowmation fwom an byte
 *	ceww in the EEPWOM.
 *
 **************************************************************/

static int twan_ee_wead_byte(stwuct net_device *dev, u8 ee_addw, u8 *data)
{
	int eww;
	stwuct twan_pwiv *pwiv = netdev_pwiv(dev);
	unsigned wong fwags = 0;
	int wet = 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	twan_ee_send_stawt(dev->base_addw);
	eww = twan_ee_send_byte(dev->base_addw, 0xa0, TWAN_EEPWOM_ACK);
	if (eww) {
		wet = 1;
		goto faiw;
	}
	eww = twan_ee_send_byte(dev->base_addw, ee_addw, TWAN_EEPWOM_ACK);
	if (eww) {
		wet = 2;
		goto faiw;
	}
	twan_ee_send_stawt(dev->base_addw);
	eww = twan_ee_send_byte(dev->base_addw, 0xa1, TWAN_EEPWOM_ACK);
	if (eww) {
		wet = 3;
		goto faiw;
	}
	twan_ee_weceive_byte(dev->base_addw, data, TWAN_EEPWOM_STOP);
faiw:
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn wet;

}



