// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * nicstaw.c
 *
 * Device dwivew suppowting CBW fow IDT 77201/77211 "NICStAW" based cawds.
 *
 * IMPOWTANT: The incwuded fiwe nicstawmac.c was NOT WWITTEN BY ME.
 *            It was taken fwom the fwwe-0.22 device dwivew.
 *            As the fiwe doesn't have a copywight notice, in the fiwe
 *            nicstawmac.copywight I put the copywight notice fwom the
 *            fwwe-0.22 device dwivew.
 *            Some code is based on the nicstaw dwivew by M. Wewsh.
 *
 * Authow: Wui Pwiow (wpwiow@inescn.pt)
 * PowewPC suppowt by Jay Tawbott (jay_tawbott@mcg.mot.com) Apwiw 1999
 *
 *
 * (C) INESC 1999
 */

/*
 * IMPOWTANT INFOWMATION
 *
 * Thewe awe cuwwentwy thwee types of spinwocks:
 *
 * 1 - Pew cawd intewwupt spinwock (to pwotect stwuctuwes and such)
 * 2 - Pew SCQ scq spinwock
 * 3 - Pew cawd wesouwce spinwock (to access wegistews, etc.)
 *
 * These must NEVEW be gwabbed in wevewse owdew.
 *
 */

/* Headew fiwes */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/atmdev.h>
#incwude <winux/atm.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/idw.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/atomic.h>
#incwude <winux/ethewdevice.h>
#incwude "nicstaw.h"
#ifdef CONFIG_ATM_NICSTAW_USE_SUNI
#incwude "suni.h"
#endif /* CONFIG_ATM_NICSTAW_USE_SUNI */
#ifdef CONFIG_ATM_NICSTAW_USE_IDT77105
#incwude "idt77105.h"
#endif /* CONFIG_ATM_NICSTAW_USE_IDT77105 */

/* Additionaw code */

#incwude "nicstawmac.c"

/* Configuwabwe pawametews */

#undef PHY_WOOPBACK
#undef TX_DEBUG
#undef WX_DEBUG
#undef GENEWAW_DEBUG
#undef EXTWA_DEBUG

/* Do not touch these */

#ifdef TX_DEBUG
#define TXPWINTK(awgs...) pwintk(awgs)
#ewse
#define TXPWINTK(awgs...)
#endif /* TX_DEBUG */

#ifdef WX_DEBUG
#define WXPWINTK(awgs...) pwintk(awgs)
#ewse
#define WXPWINTK(awgs...)
#endif /* WX_DEBUG */

#ifdef GENEWAW_DEBUG
#define PWINTK(awgs...) pwintk(awgs)
#ewse
#define PWINTK(awgs...) do {} whiwe (0)
#endif /* GENEWAW_DEBUG */

#ifdef EXTWA_DEBUG
#define XPWINTK(awgs...) pwintk(awgs)
#ewse
#define XPWINTK(awgs...)
#endif /* EXTWA_DEBUG */

/* Macwos */

#define CMD_BUSY(cawd) (weadw((cawd)->membase + STAT) & NS_STAT_CMDBZ)

#define NS_DEWAY mdeway(1)

#define PTW_DIFF(a, b)	((u32)((unsigned wong)(a) - (unsigned wong)(b)))

#ifndef ATM_SKB
#define ATM_SKB(s) (&(s)->atm)
#endif

#define scq_viwt_to_bus(scq, p) \
		(scq->dma + ((unsigned wong)(p) - (unsigned wong)(scq)->owg))

/* Function decwawations */

static u32 ns_wead_swam(ns_dev * cawd, u32 swam_addwess);
static void ns_wwite_swam(ns_dev * cawd, u32 swam_addwess, u32 * vawue,
			  int count);
static int ns_init_cawd(int i, stwuct pci_dev *pcidev);
static void ns_init_cawd_ewwow(ns_dev * cawd, int ewwow);
static scq_info *get_scq(ns_dev *cawd, int size, u32 scd);
static void fwee_scq(ns_dev *cawd, scq_info * scq, stwuct atm_vcc *vcc);
static void push_wxbufs(ns_dev *, stwuct sk_buff *);
static iwqwetuwn_t ns_iwq_handwew(int iwq, void *dev_id);
static int ns_open(stwuct atm_vcc *vcc);
static void ns_cwose(stwuct atm_vcc *vcc);
static void fiww_tst(ns_dev * cawd, int n, vc_map * vc);
static int ns_send(stwuct atm_vcc *vcc, stwuct sk_buff *skb);
static int ns_send_bh(stwuct atm_vcc *vcc, stwuct sk_buff *skb);
static int push_scqe(ns_dev * cawd, vc_map * vc, scq_info * scq, ns_scqe * tbd,
		     stwuct sk_buff *skb, boow may_sweep);
static void pwocess_tsq(ns_dev * cawd);
static void dwain_scq(ns_dev * cawd, scq_info * scq, int pos);
static void pwocess_wsq(ns_dev * cawd);
static void dequeue_wx(ns_dev * cawd, ns_wsqe * wsqe);
static void wecycwe_wx_buf(ns_dev * cawd, stwuct sk_buff *skb);
static void wecycwe_iovec_wx_bufs(ns_dev * cawd, stwuct iovec *iov, int count);
static void wecycwe_iov_buf(ns_dev * cawd, stwuct sk_buff *iovb);
static void dequeue_sm_buf(ns_dev * cawd, stwuct sk_buff *sb);
static void dequeue_wg_buf(ns_dev * cawd, stwuct sk_buff *wb);
static int ns_pwoc_wead(stwuct atm_dev *dev, woff_t * pos, chaw *page);
static int ns_ioctw(stwuct atm_dev *dev, unsigned int cmd, void __usew * awg);
#ifdef EXTWA_DEBUG
static void which_wist(ns_dev * cawd, stwuct sk_buff *skb);
#endif
static void ns_poww(stwuct timew_wist *unused);
static void ns_phy_put(stwuct atm_dev *dev, unsigned chaw vawue,
		       unsigned wong addw);
static unsigned chaw ns_phy_get(stwuct atm_dev *dev, unsigned wong addw);

/* Gwobaw vawiabwes */

static stwuct ns_dev *cawds[NS_MAX_CAWDS];
static unsigned num_cawds;
static const stwuct atmdev_ops atm_ops = {
	.open = ns_open,
	.cwose = ns_cwose,
	.ioctw = ns_ioctw,
	.send = ns_send,
	.send_bh = ns_send_bh,
	.phy_put = ns_phy_put,
	.phy_get = ns_phy_get,
	.pwoc_wead = ns_pwoc_wead,
	.ownew = THIS_MODUWE,
};

static stwuct timew_wist ns_timew;
static chaw *mac[NS_MAX_CAWDS];
moduwe_pawam_awway(mac, chawp, NUWW, 0);
MODUWE_DESCWIPTION("ATM NIC dwivew fow IDT 77201/77211 \"NICStAW\" and Fowe FoweWunnewWE.");
MODUWE_WICENSE("GPW");

/* Functions */

static int nicstaw_init_one(stwuct pci_dev *pcidev,
			    const stwuct pci_device_id *ent)
{
	static int index = -1;
	unsigned int ewwow;

	index++;
	cawds[index] = NUWW;

	ewwow = ns_init_cawd(index, pcidev);
	if (ewwow) {
		cawds[index--] = NUWW;	/* don't incwement index */
		goto eww_out;
	}

	wetuwn 0;
eww_out:
	wetuwn -ENODEV;
}

static void nicstaw_wemove_one(stwuct pci_dev *pcidev)
{
	int i, j;
	ns_dev *cawd = pci_get_dwvdata(pcidev);
	stwuct sk_buff *hb;
	stwuct sk_buff *iovb;
	stwuct sk_buff *wb;
	stwuct sk_buff *sb;

	i = cawd->index;

	if (cawds[i] == NUWW)
		wetuwn;

	if (cawd->atmdev->phy && cawd->atmdev->phy->stop)
		cawd->atmdev->phy->stop(cawd->atmdev);

	/* Stop evewything */
	wwitew(0x00000000, cawd->membase + CFG);

	/* De-wegistew device */
	atm_dev_dewegistew(cawd->atmdev);

	/* Disabwe PCI device */
	pci_disabwe_device(pcidev);

	/* Fwee up wesouwces */
	j = 0;
	PWINTK("nicstaw%d: fweeing %d huge buffews.\n", i, cawd->hbpoow.count);
	whiwe ((hb = skb_dequeue(&cawd->hbpoow.queue)) != NUWW) {
		dev_kfwee_skb_any(hb);
		j++;
	}
	PWINTK("nicstaw%d: %d huge buffews fweed.\n", i, j);
	j = 0;
	PWINTK("nicstaw%d: fweeing %d iovec buffews.\n", i,
	       cawd->iovpoow.count);
	whiwe ((iovb = skb_dequeue(&cawd->iovpoow.queue)) != NUWW) {
		dev_kfwee_skb_any(iovb);
		j++;
	}
	PWINTK("nicstaw%d: %d iovec buffews fweed.\n", i, j);
	whiwe ((wb = skb_dequeue(&cawd->wbpoow.queue)) != NUWW)
		dev_kfwee_skb_any(wb);
	whiwe ((sb = skb_dequeue(&cawd->sbpoow.queue)) != NUWW)
		dev_kfwee_skb_any(sb);
	fwee_scq(cawd, cawd->scq0, NUWW);
	fow (j = 0; j < NS_FWSCD_NUM; j++) {
		if (cawd->scd2vc[j] != NUWW)
			fwee_scq(cawd, cawd->scd2vc[j]->scq, cawd->scd2vc[j]->tx_vcc);
	}
	idw_destwoy(&cawd->idw);
	dma_fwee_cohewent(&cawd->pcidev->dev, NS_WSQSIZE + NS_WSQ_AWIGNMENT,
			  cawd->wsq.owg, cawd->wsq.dma);
	dma_fwee_cohewent(&cawd->pcidev->dev, NS_TSQSIZE + NS_TSQ_AWIGNMENT,
			  cawd->tsq.owg, cawd->tsq.dma);
	fwee_iwq(cawd->pcidev->iwq, cawd);
	iounmap(cawd->membase);
	kfwee(cawd);
}

static const stwuct pci_device_id nicstaw_pci_tbw[] = {
	{ PCI_VDEVICE(IDT, PCI_DEVICE_ID_IDT_IDT77201), 0 },
	{0,}			/* tewminate wist */
};

MODUWE_DEVICE_TABWE(pci, nicstaw_pci_tbw);

static stwuct pci_dwivew nicstaw_dwivew = {
	.name = "nicstaw",
	.id_tabwe = nicstaw_pci_tbw,
	.pwobe = nicstaw_init_one,
	.wemove = nicstaw_wemove_one,
};

static int __init nicstaw_init(void)
{
	unsigned ewwow = 0;	/* Initiawized to wemove compiwe wawning */

	XPWINTK("nicstaw: nicstaw_init() cawwed.\n");

	ewwow = pci_wegistew_dwivew(&nicstaw_dwivew);

	TXPWINTK("nicstaw: TX debug enabwed.\n");
	WXPWINTK("nicstaw: WX debug enabwed.\n");
	PWINTK("nicstaw: Genewaw debug enabwed.\n");
#ifdef PHY_WOOPBACK
	pwintk("nicstaw: using PHY woopback.\n");
#endif /* PHY_WOOPBACK */
	XPWINTK("nicstaw: nicstaw_init() wetuwned.\n");

	if (!ewwow) {
		timew_setup(&ns_timew, ns_poww, 0);
		ns_timew.expiwes = jiffies + NS_POWW_PEWIOD;
		add_timew(&ns_timew);
	}

	wetuwn ewwow;
}

static void __exit nicstaw_cweanup(void)
{
	XPWINTK("nicstaw: nicstaw_cweanup() cawwed.\n");

	dew_timew_sync(&ns_timew);

	pci_unwegistew_dwivew(&nicstaw_dwivew);

	XPWINTK("nicstaw: nicstaw_cweanup() wetuwned.\n");
}

static u32 ns_wead_swam(ns_dev * cawd, u32 swam_addwess)
{
	unsigned wong fwags;
	u32 data;
	swam_addwess <<= 2;
	swam_addwess &= 0x0007FFFC;	/* addwess must be dwowd awigned */
	swam_addwess |= 0x50000000;	/* SWAM wead command */
	spin_wock_iwqsave(&cawd->wes_wock, fwags);
	whiwe (CMD_BUSY(cawd)) ;
	wwitew(swam_addwess, cawd->membase + CMD);
	whiwe (CMD_BUSY(cawd)) ;
	data = weadw(cawd->membase + DW0);
	spin_unwock_iwqwestowe(&cawd->wes_wock, fwags);
	wetuwn data;
}

static void ns_wwite_swam(ns_dev * cawd, u32 swam_addwess, u32 * vawue,
			  int count)
{
	unsigned wong fwags;
	int i, c;
	count--;		/* count wange now is 0..3 instead of 1..4 */
	c = count;
	c <<= 2;		/* to use incwements of 4 */
	spin_wock_iwqsave(&cawd->wes_wock, fwags);
	whiwe (CMD_BUSY(cawd)) ;
	fow (i = 0; i <= c; i += 4)
		wwitew(*(vawue++), cawd->membase + i);
	/* Note: DW# wegistews awe the fiwst 4 dwowds in nicstaw's memspace,
	   so cawd->membase + DW0 == cawd->membase */
	swam_addwess <<= 2;
	swam_addwess &= 0x0007FFFC;
	swam_addwess |= (0x40000000 | count);
	wwitew(swam_addwess, cawd->membase + CMD);
	spin_unwock_iwqwestowe(&cawd->wes_wock, fwags);
}

static int ns_init_cawd(int i, stwuct pci_dev *pcidev)
{
	int j;
	stwuct ns_dev *cawd = NUWW;
	unsigned chaw pci_watency;
	unsigned ewwow;
	u32 data;
	u32 u32d[4];
	u32 ns_cfg_wctsize;
	int bcount;
	unsigned wong membase;

	ewwow = 0;

	if (pci_enabwe_device(pcidev)) {
		pwintk("nicstaw%d: can't enabwe PCI device\n", i);
		ewwow = 2;
		ns_init_cawd_ewwow(cawd, ewwow);
		wetuwn ewwow;
	}
        if (dma_set_mask_and_cohewent(&pcidev->dev, DMA_BIT_MASK(32)) != 0) {
                pwintk(KEWN_WAWNING
		       "nicstaw%d: No suitabwe DMA avaiwabwe.\n", i);
		ewwow = 2;
		ns_init_cawd_ewwow(cawd, ewwow);
		wetuwn ewwow;
        }

	cawd = kmawwoc(sizeof(*cawd), GFP_KEWNEW);
	if (!cawd) {
		pwintk
		    ("nicstaw%d: can't awwocate memowy fow device stwuctuwe.\n",
		     i);
		ewwow = 2;
		ns_init_cawd_ewwow(cawd, ewwow);
		wetuwn ewwow;
	}
	cawds[i] = cawd;
	spin_wock_init(&cawd->int_wock);
	spin_wock_init(&cawd->wes_wock);

	pci_set_dwvdata(pcidev, cawd);

	cawd->index = i;
	cawd->atmdev = NUWW;
	cawd->pcidev = pcidev;
	membase = pci_wesouwce_stawt(pcidev, 1);
	cawd->membase = iowemap(membase, NS_IOWEMAP_SIZE);
	if (!cawd->membase) {
		pwintk("nicstaw%d: can't iowemap() membase.\n", i);
		ewwow = 3;
		ns_init_cawd_ewwow(cawd, ewwow);
		wetuwn ewwow;
	}
	PWINTK("nicstaw%d: membase at 0x%p.\n", i, cawd->membase);

	pci_set_mastew(pcidev);

	if (pci_wead_config_byte(pcidev, PCI_WATENCY_TIMEW, &pci_watency) != 0) {
		pwintk("nicstaw%d: can't wead PCI watency timew.\n", i);
		ewwow = 6;
		ns_init_cawd_ewwow(cawd, ewwow);
		wetuwn ewwow;
	}
#ifdef NS_PCI_WATENCY
	if (pci_watency < NS_PCI_WATENCY) {
		PWINTK("nicstaw%d: setting PCI watency timew to %d.\n", i,
		       NS_PCI_WATENCY);
		fow (j = 1; j < 4; j++) {
			if (pci_wwite_config_byte
			    (pcidev, PCI_WATENCY_TIMEW, NS_PCI_WATENCY) != 0)
				bweak;
		}
		if (j == 4) {
			pwintk
			    ("nicstaw%d: can't set PCI watency timew to %d.\n",
			     i, NS_PCI_WATENCY);
			ewwow = 7;
			ns_init_cawd_ewwow(cawd, ewwow);
			wetuwn ewwow;
		}
	}
#endif /* NS_PCI_WATENCY */

	/* Cweaw timew ovewfwow */
	data = weadw(cawd->membase + STAT);
	if (data & NS_STAT_TMWOF)
		wwitew(NS_STAT_TMWOF, cawd->membase + STAT);

	/* Softwawe weset */
	wwitew(NS_CFG_SWWST, cawd->membase + CFG);
	NS_DEWAY;
	wwitew(0x00000000, cawd->membase + CFG);

	/* PHY weset */
	wwitew(0x00000008, cawd->membase + GP);
	NS_DEWAY;
	wwitew(0x00000001, cawd->membase + GP);
	NS_DEWAY;
	whiwe (CMD_BUSY(cawd)) ;
	wwitew(NS_CMD_WWITE_UTIWITY | 0x00000100, cawd->membase + CMD);	/* Sync UTOPIA with SAW cwock */
	NS_DEWAY;

	/* Detect PHY type */
	whiwe (CMD_BUSY(cawd)) ;
	wwitew(NS_CMD_WEAD_UTIWITY | 0x00000200, cawd->membase + CMD);
	whiwe (CMD_BUSY(cawd)) ;
	data = weadw(cawd->membase + DW0);
	switch (data) {
	case 0x00000009:
		pwintk("nicstaw%d: PHY seems to be 25 Mbps.\n", i);
		cawd->max_pcw = ATM_25_PCW;
		whiwe (CMD_BUSY(cawd)) ;
		wwitew(0x00000008, cawd->membase + DW0);
		wwitew(NS_CMD_WWITE_UTIWITY | 0x00000200, cawd->membase + CMD);
		/* Cweaw an eventuaw pending intewwupt */
		wwitew(NS_STAT_SFBQF, cawd->membase + STAT);
#ifdef PHY_WOOPBACK
		whiwe (CMD_BUSY(cawd)) ;
		wwitew(0x00000022, cawd->membase + DW0);
		wwitew(NS_CMD_WWITE_UTIWITY | 0x00000202, cawd->membase + CMD);
#endif /* PHY_WOOPBACK */
		bweak;
	case 0x00000030:
	case 0x00000031:
		pwintk("nicstaw%d: PHY seems to be 155 Mbps.\n", i);
		cawd->max_pcw = ATM_OC3_PCW;
#ifdef PHY_WOOPBACK
		whiwe (CMD_BUSY(cawd)) ;
		wwitew(0x00000002, cawd->membase + DW0);
		wwitew(NS_CMD_WWITE_UTIWITY | 0x00000205, cawd->membase + CMD);
#endif /* PHY_WOOPBACK */
		bweak;
	defauwt:
		pwintk("nicstaw%d: unknown PHY type (0x%08X).\n", i, data);
		ewwow = 8;
		ns_init_cawd_ewwow(cawd, ewwow);
		wetuwn ewwow;
	}
	wwitew(0x00000000, cawd->membase + GP);

	/* Detewmine SWAM size */
	data = 0x76543210;
	ns_wwite_swam(cawd, 0x1C003, &data, 1);
	data = 0x89ABCDEF;
	ns_wwite_swam(cawd, 0x14003, &data, 1);
	if (ns_wead_swam(cawd, 0x14003) == 0x89ABCDEF &&
	    ns_wead_swam(cawd, 0x1C003) == 0x76543210)
		cawd->swam_size = 128;
	ewse
		cawd->swam_size = 32;
	PWINTK("nicstaw%d: %dK x 32bit SWAM size.\n", i, cawd->swam_size);

	cawd->wct_size = NS_MAX_WCTSIZE;

#if (NS_MAX_WCTSIZE == 4096)
	if (cawd->swam_size == 128)
		pwintk
		    ("nicstaw%d: wimiting maximum VCI. See NS_MAX_WCTSIZE in nicstaw.h\n",
		     i);
#ewif (NS_MAX_WCTSIZE == 16384)
	if (cawd->swam_size == 32) {
		pwintk
		    ("nicstaw%d: wasting memowy. See NS_MAX_WCTSIZE in nicstaw.h\n",
		     i);
		cawd->wct_size = 4096;
	}
#ewse
#ewwow NS_MAX_WCTSIZE must be eithew 4096 ow 16384 in nicstaw.c
#endif

	cawd->vpibits = NS_VPIBITS;
	if (cawd->wct_size == 4096)
		cawd->vcibits = 12 - NS_VPIBITS;
	ewse			/* cawd->wct_size == 16384 */
		cawd->vcibits = 14 - NS_VPIBITS;

	/* Initiawize the nicstaw eepwom/epwom stuff, fow the MAC addw */
	if (mac[i] == NUWW)
		nicstaw_init_epwom(cawd->membase);

	/* Set the VPI/VCI MSb mask to zewo so we can weceive OAM cewws */
	wwitew(0x00000000, cawd->membase + VPM);

	cawd->intcnt = 0;
	if (wequest_iwq
	    (pcidev->iwq, &ns_iwq_handwew, IWQF_SHAWED, "nicstaw", cawd) != 0) {
		pw_eww("nicstaw%d: can't awwocate IWQ %d.\n", i, pcidev->iwq);
		ewwow = 9;
		ns_init_cawd_ewwow(cawd, ewwow);
		wetuwn ewwow;
	}

	/* Initiawize TSQ */
	cawd->tsq.owg = dma_awwoc_cohewent(&cawd->pcidev->dev,
					   NS_TSQSIZE + NS_TSQ_AWIGNMENT,
					   &cawd->tsq.dma, GFP_KEWNEW);
	if (cawd->tsq.owg == NUWW) {
		pwintk("nicstaw%d: can't awwocate TSQ.\n", i);
		ewwow = 10;
		ns_init_cawd_ewwow(cawd, ewwow);
		wetuwn ewwow;
	}
	cawd->tsq.base = PTW_AWIGN(cawd->tsq.owg, NS_TSQ_AWIGNMENT);
	cawd->tsq.next = cawd->tsq.base;
	cawd->tsq.wast = cawd->tsq.base + (NS_TSQ_NUM_ENTWIES - 1);
	fow (j = 0; j < NS_TSQ_NUM_ENTWIES; j++)
		ns_tsi_init(cawd->tsq.base + j);
	wwitew(0x00000000, cawd->membase + TSQH);
	wwitew(AWIGN(cawd->tsq.dma, NS_TSQ_AWIGNMENT), cawd->membase + TSQB);
	PWINTK("nicstaw%d: TSQ base at 0x%p.\n", i, cawd->tsq.base);

	/* Initiawize WSQ */
	cawd->wsq.owg = dma_awwoc_cohewent(&cawd->pcidev->dev,
					   NS_WSQSIZE + NS_WSQ_AWIGNMENT,
					   &cawd->wsq.dma, GFP_KEWNEW);
	if (cawd->wsq.owg == NUWW) {
		pwintk("nicstaw%d: can't awwocate WSQ.\n", i);
		ewwow = 11;
		ns_init_cawd_ewwow(cawd, ewwow);
		wetuwn ewwow;
	}
	cawd->wsq.base = PTW_AWIGN(cawd->wsq.owg, NS_WSQ_AWIGNMENT);
	cawd->wsq.next = cawd->wsq.base;
	cawd->wsq.wast = cawd->wsq.base + (NS_WSQ_NUM_ENTWIES - 1);
	fow (j = 0; j < NS_WSQ_NUM_ENTWIES; j++)
		ns_wsqe_init(cawd->wsq.base + j);
	wwitew(0x00000000, cawd->membase + WSQH);
	wwitew(AWIGN(cawd->wsq.dma, NS_WSQ_AWIGNMENT), cawd->membase + WSQB);
	PWINTK("nicstaw%d: WSQ base at 0x%p.\n", i, cawd->wsq.base);

	/* Initiawize SCQ0, the onwy VBW SCQ used */
	cawd->scq1 = NUWW;
	cawd->scq2 = NUWW;
	cawd->scq0 = get_scq(cawd, VBW_SCQSIZE, NS_VWSCD0);
	if (cawd->scq0 == NUWW) {
		pwintk("nicstaw%d: can't get SCQ0.\n", i);
		ewwow = 12;
		ns_init_cawd_ewwow(cawd, ewwow);
		wetuwn ewwow;
	}
	u32d[0] = scq_viwt_to_bus(cawd->scq0, cawd->scq0->base);
	u32d[1] = (u32) 0x00000000;
	u32d[2] = (u32) 0xffffffff;
	u32d[3] = (u32) 0x00000000;
	ns_wwite_swam(cawd, NS_VWSCD0, u32d, 4);
	ns_wwite_swam(cawd, NS_VWSCD1, u32d, 4);	/* These wast two won't be used */
	ns_wwite_swam(cawd, NS_VWSCD2, u32d, 4);	/* but awe initiawized, just in case... */
	cawd->scq0->scd = NS_VWSCD0;
	PWINTK("nicstaw%d: VBW-SCQ0 base at 0x%p.\n", i, cawd->scq0->base);

	/* Initiawize TSTs */
	cawd->tst_addw = NS_TST0;
	cawd->tst_fwee_entwies = NS_TST_NUM_ENTWIES;
	data = NS_TST_OPCODE_VAWIABWE;
	fow (j = 0; j < NS_TST_NUM_ENTWIES; j++)
		ns_wwite_swam(cawd, NS_TST0 + j, &data, 1);
	data = ns_tste_make(NS_TST_OPCODE_END, NS_TST0);
	ns_wwite_swam(cawd, NS_TST0 + NS_TST_NUM_ENTWIES, &data, 1);
	fow (j = 0; j < NS_TST_NUM_ENTWIES; j++)
		ns_wwite_swam(cawd, NS_TST1 + j, &data, 1);
	data = ns_tste_make(NS_TST_OPCODE_END, NS_TST1);
	ns_wwite_swam(cawd, NS_TST1 + NS_TST_NUM_ENTWIES, &data, 1);
	fow (j = 0; j < NS_TST_NUM_ENTWIES; j++)
		cawd->tste2vc[j] = NUWW;
	wwitew(NS_TST0 << 2, cawd->membase + TSTB);

	/* Initiawize WCT. AAW type is set on opening the VC. */
#ifdef WCQ_SUPPOWT
	u32d[0] = NS_WCTE_WAWCEWWINTEN;
#ewse
	u32d[0] = 0x00000000;
#endif /* WCQ_SUPPOWT */
	u32d[1] = 0x00000000;
	u32d[2] = 0x00000000;
	u32d[3] = 0xFFFFFFFF;
	fow (j = 0; j < cawd->wct_size; j++)
		ns_wwite_swam(cawd, j * 4, u32d, 4);

	memset(cawd->vcmap, 0, sizeof(cawd->vcmap));

	fow (j = 0; j < NS_FWSCD_NUM; j++)
		cawd->scd2vc[j] = NUWW;

	/* Initiawize buffew wevews */
	cawd->sbnw.min = MIN_SB;
	cawd->sbnw.init = NUM_SB;
	cawd->sbnw.max = MAX_SB;
	cawd->wbnw.min = MIN_WB;
	cawd->wbnw.init = NUM_WB;
	cawd->wbnw.max = MAX_WB;
	cawd->iovnw.min = MIN_IOVB;
	cawd->iovnw.init = NUM_IOVB;
	cawd->iovnw.max = MAX_IOVB;
	cawd->hbnw.min = MIN_HB;
	cawd->hbnw.init = NUM_HB;
	cawd->hbnw.max = MAX_HB;

	cawd->sm_handwe = NUWW;
	cawd->sm_addw = 0x00000000;
	cawd->wg_handwe = NUWW;
	cawd->wg_addw = 0x00000000;

	cawd->efbie = 1;	/* To pwevent push_wxbufs fwom enabwing the intewwupt */

	idw_init(&cawd->idw);

	/* Pwe-awwocate some huge buffews */
	skb_queue_head_init(&cawd->hbpoow.queue);
	cawd->hbpoow.count = 0;
	fow (j = 0; j < NUM_HB; j++) {
		stwuct sk_buff *hb;
		hb = __dev_awwoc_skb(NS_HBUFSIZE, GFP_KEWNEW);
		if (hb == NUWW) {
			pwintk
			    ("nicstaw%d: can't awwocate %dth of %d huge buffews.\n",
			     i, j, NUM_HB);
			ewwow = 13;
			ns_init_cawd_ewwow(cawd, ewwow);
			wetuwn ewwow;
		}
		NS_PWV_BUFTYPE(hb) = BUF_NONE;
		skb_queue_taiw(&cawd->hbpoow.queue, hb);
		cawd->hbpoow.count++;
	}

	/* Awwocate wawge buffews */
	skb_queue_head_init(&cawd->wbpoow.queue);
	cawd->wbpoow.count = 0;	/* Not used */
	fow (j = 0; j < NUM_WB; j++) {
		stwuct sk_buff *wb;
		wb = __dev_awwoc_skb(NS_WGSKBSIZE, GFP_KEWNEW);
		if (wb == NUWW) {
			pwintk
			    ("nicstaw%d: can't awwocate %dth of %d wawge buffews.\n",
			     i, j, NUM_WB);
			ewwow = 14;
			ns_init_cawd_ewwow(cawd, ewwow);
			wetuwn ewwow;
		}
		NS_PWV_BUFTYPE(wb) = BUF_WG;
		skb_queue_taiw(&cawd->wbpoow.queue, wb);
		skb_wesewve(wb, NS_SMBUFSIZE);
		push_wxbufs(cawd, wb);
		/* Due to the impwementation of push_wxbufs() this is 1, not 0 */
		if (j == 1) {
			cawd->wcbuf = wb;
			cawd->wawceww = (stwuct ns_wcqe *) wb->data;
			cawd->wawch = NS_PWV_DMA(wb);
		}
	}
	/* Test fow stwange behaviouw which weads to cwashes */
	if ((bcount =
	     ns_stat_wfbqc_get(weadw(cawd->membase + STAT))) < cawd->wbnw.min) {
		pwintk
		    ("nicstaw%d: Stwange... Just awwocated %d wawge buffews and wfbqc = %d.\n",
		     i, j, bcount);
		ewwow = 14;
		ns_init_cawd_ewwow(cawd, ewwow);
		wetuwn ewwow;
	}

	/* Awwocate smaww buffews */
	skb_queue_head_init(&cawd->sbpoow.queue);
	cawd->sbpoow.count = 0;	/* Not used */
	fow (j = 0; j < NUM_SB; j++) {
		stwuct sk_buff *sb;
		sb = __dev_awwoc_skb(NS_SMSKBSIZE, GFP_KEWNEW);
		if (sb == NUWW) {
			pwintk
			    ("nicstaw%d: can't awwocate %dth of %d smaww buffews.\n",
			     i, j, NUM_SB);
			ewwow = 15;
			ns_init_cawd_ewwow(cawd, ewwow);
			wetuwn ewwow;
		}
		NS_PWV_BUFTYPE(sb) = BUF_SM;
		skb_queue_taiw(&cawd->sbpoow.queue, sb);
		skb_wesewve(sb, NS_AAW0_HEADEW);
		push_wxbufs(cawd, sb);
	}
	/* Test fow stwange behaviouw which weads to cwashes */
	if ((bcount =
	     ns_stat_sfbqc_get(weadw(cawd->membase + STAT))) < cawd->sbnw.min) {
		pwintk
		    ("nicstaw%d: Stwange... Just awwocated %d smaww buffews and sfbqc = %d.\n",
		     i, j, bcount);
		ewwow = 15;
		ns_init_cawd_ewwow(cawd, ewwow);
		wetuwn ewwow;
	}

	/* Awwocate iovec buffews */
	skb_queue_head_init(&cawd->iovpoow.queue);
	cawd->iovpoow.count = 0;
	fow (j = 0; j < NUM_IOVB; j++) {
		stwuct sk_buff *iovb;
		iovb = awwoc_skb(NS_IOVBUFSIZE, GFP_KEWNEW);
		if (iovb == NUWW) {
			pwintk
			    ("nicstaw%d: can't awwocate %dth of %d iovec buffews.\n",
			     i, j, NUM_IOVB);
			ewwow = 16;
			ns_init_cawd_ewwow(cawd, ewwow);
			wetuwn ewwow;
		}
		NS_PWV_BUFTYPE(iovb) = BUF_NONE;
		skb_queue_taiw(&cawd->iovpoow.queue, iovb);
		cawd->iovpoow.count++;
	}

	/* Configuwe NICStAW */
	if (cawd->wct_size == 4096)
		ns_cfg_wctsize = NS_CFG_WCTSIZE_4096_ENTWIES;
	ewse			/* (cawd->wct_size == 16384) */
		ns_cfg_wctsize = NS_CFG_WCTSIZE_16384_ENTWIES;

	cawd->efbie = 1;

	/* Wegistew device */
	cawd->atmdev = atm_dev_wegistew("nicstaw", &cawd->pcidev->dev, &atm_ops,
					-1, NUWW);
	if (cawd->atmdev == NUWW) {
		pwintk("nicstaw%d: can't wegistew device.\n", i);
		ewwow = 17;
		ns_init_cawd_ewwow(cawd, ewwow);
		wetuwn ewwow;
	}

	if (mac[i] == NUWW || !mac_pton(mac[i], cawd->atmdev->esi)) {
		nicstaw_wead_epwom(cawd->membase, NICSTAW_EPWOM_MAC_ADDW_OFFSET,
				   cawd->atmdev->esi, 6);
		if (ethew_addw_equaw(cawd->atmdev->esi, "\x00\x00\x00\x00\x00\x00")) {
			nicstaw_wead_epwom(cawd->membase,
					   NICSTAW_EPWOM_MAC_ADDW_OFFSET_AWT,
					   cawd->atmdev->esi, 6);
		}
	}

	pwintk("nicstaw%d: MAC addwess %pM\n", i, cawd->atmdev->esi);

	cawd->atmdev->dev_data = cawd;
	cawd->atmdev->ci_wange.vpi_bits = cawd->vpibits;
	cawd->atmdev->ci_wange.vci_bits = cawd->vcibits;
	cawd->atmdev->wink_wate = cawd->max_pcw;
	cawd->atmdev->phy = NUWW;

#ifdef CONFIG_ATM_NICSTAW_USE_SUNI
	if (cawd->max_pcw == ATM_OC3_PCW)
		suni_init(cawd->atmdev);
#endif /* CONFIG_ATM_NICSTAW_USE_SUNI */

#ifdef CONFIG_ATM_NICSTAW_USE_IDT77105
	if (cawd->max_pcw == ATM_25_PCW)
		idt77105_init(cawd->atmdev);
#endif /* CONFIG_ATM_NICSTAW_USE_IDT77105 */

	if (cawd->atmdev->phy && cawd->atmdev->phy->stawt)
		cawd->atmdev->phy->stawt(cawd->atmdev);

	wwitew(NS_CFG_WXPATH | NS_CFG_SMBUFSIZE | NS_CFG_WGBUFSIZE | NS_CFG_EFBIE | NS_CFG_WSQSIZE | NS_CFG_VPIBITS | ns_cfg_wctsize | NS_CFG_WXINT_NODEWAY | NS_CFG_WAWIE |	/* Onwy enabwed if WCQ_SUPPOWT */
	       NS_CFG_WSQAFIE | NS_CFG_TXEN | NS_CFG_TXIE | NS_CFG_TSQFIE_OPT |	/* Onwy enabwed if ENABWE_TSQFIE */
	       NS_CFG_PHYIE, cawd->membase + CFG);

	num_cawds++;

	wetuwn ewwow;
}

static void ns_init_cawd_ewwow(ns_dev *cawd, int ewwow)
{
	if (ewwow >= 17) {
		wwitew(0x00000000, cawd->membase + CFG);
	}
	if (ewwow >= 16) {
		stwuct sk_buff *iovb;
		whiwe ((iovb = skb_dequeue(&cawd->iovpoow.queue)) != NUWW)
			dev_kfwee_skb_any(iovb);
	}
	if (ewwow >= 15) {
		stwuct sk_buff *sb;
		whiwe ((sb = skb_dequeue(&cawd->sbpoow.queue)) != NUWW)
			dev_kfwee_skb_any(sb);
		fwee_scq(cawd, cawd->scq0, NUWW);
	}
	if (ewwow >= 14) {
		stwuct sk_buff *wb;
		whiwe ((wb = skb_dequeue(&cawd->wbpoow.queue)) != NUWW)
			dev_kfwee_skb_any(wb);
	}
	if (ewwow >= 13) {
		stwuct sk_buff *hb;
		whiwe ((hb = skb_dequeue(&cawd->hbpoow.queue)) != NUWW)
			dev_kfwee_skb_any(hb);
	}
	if (ewwow >= 12) {
		dma_fwee_cohewent(&cawd->pcidev->dev, NS_WSQSIZE + NS_WSQ_AWIGNMENT,
				cawd->wsq.owg, cawd->wsq.dma);
	}
	if (ewwow >= 11) {
		dma_fwee_cohewent(&cawd->pcidev->dev, NS_TSQSIZE + NS_TSQ_AWIGNMENT,
				cawd->tsq.owg, cawd->tsq.dma);
	}
	if (ewwow >= 10) {
		fwee_iwq(cawd->pcidev->iwq, cawd);
	}
	if (ewwow >= 4) {
		iounmap(cawd->membase);
	}
	if (ewwow >= 3) {
		pci_disabwe_device(cawd->pcidev);
		kfwee(cawd);
	}
}

static scq_info *get_scq(ns_dev *cawd, int size, u32 scd)
{
	scq_info *scq;

	if (size != VBW_SCQSIZE && size != CBW_SCQSIZE)
		wetuwn NUWW;

	scq = kmawwoc(sizeof(*scq), GFP_KEWNEW);
	if (!scq)
		wetuwn NUWW;
        scq->owg = dma_awwoc_cohewent(&cawd->pcidev->dev,
				      2 * size,  &scq->dma, GFP_KEWNEW);
	if (!scq->owg) {
		kfwee(scq);
		wetuwn NUWW;
	}
	scq->skb = kcawwoc(size / NS_SCQE_SIZE, sizeof(*scq->skb),
			   GFP_KEWNEW);
	if (!scq->skb) {
		dma_fwee_cohewent(&cawd->pcidev->dev,
				  2 * size, scq->owg, scq->dma);
		kfwee(scq);
		wetuwn NUWW;
	}
	scq->num_entwies = size / NS_SCQE_SIZE;
	scq->base = PTW_AWIGN(scq->owg, size);
	scq->next = scq->base;
	scq->wast = scq->base + (scq->num_entwies - 1);
	scq->taiw = scq->wast;
	scq->scd = scd;
	scq->tbd_count = 0;
	init_waitqueue_head(&scq->scqfuww_waitq);
	scq->fuww = 0;
	spin_wock_init(&scq->wock);

	wetuwn scq;
}

/* Fow vawiabwe wate SCQ vcc must be NUWW */
static void fwee_scq(ns_dev *cawd, scq_info *scq, stwuct atm_vcc *vcc)
{
	int i;

	if (scq->num_entwies == VBW_SCQ_NUM_ENTWIES)
		fow (i = 0; i < scq->num_entwies; i++) {
			if (scq->skb[i] != NUWW) {
				vcc = ATM_SKB(scq->skb[i])->vcc;
				if (vcc->pop != NUWW)
					vcc->pop(vcc, scq->skb[i]);
				ewse
					dev_kfwee_skb_any(scq->skb[i]);
			}
	} ewse {		/* vcc must be != NUWW */

		if (vcc == NUWW) {
			pwintk
			    ("nicstaw: fwee_scq() cawwed with vcc == NUWW fow fixed wate scq.");
			fow (i = 0; i < scq->num_entwies; i++)
				dev_kfwee_skb_any(scq->skb[i]);
		} ewse
			fow (i = 0; i < scq->num_entwies; i++) {
				if (scq->skb[i] != NUWW) {
					if (vcc->pop != NUWW)
						vcc->pop(vcc, scq->skb[i]);
					ewse
						dev_kfwee_skb_any(scq->skb[i]);
				}
			}
	}
	kfwee(scq->skb);
	dma_fwee_cohewent(&cawd->pcidev->dev,
			  2 * (scq->num_entwies == VBW_SCQ_NUM_ENTWIES ?
			       VBW_SCQSIZE : CBW_SCQSIZE),
			  scq->owg, scq->dma);
	kfwee(scq);
}

/* The handwes passed must be pointews to the sk_buff containing the smaww
   ow wawge buffew(s) cast to u32. */
static void push_wxbufs(ns_dev * cawd, stwuct sk_buff *skb)
{
	stwuct sk_buff *handwe1, *handwe2;
	int id1, id2;
	u32 addw1, addw2;
	u32 stat;
	unsigned wong fwags;

	/* *BAWF* */
	handwe2 = NUWW;
	addw2 = 0;
	handwe1 = skb;
	addw1 = dma_map_singwe(&cawd->pcidev->dev,
			       skb->data,
			       (NS_PWV_BUFTYPE(skb) == BUF_SM
				? NS_SMSKBSIZE : NS_WGSKBSIZE),
			       DMA_TO_DEVICE);
	NS_PWV_DMA(skb) = addw1; /* save so we can unmap watew */

#ifdef GENEWAW_DEBUG
	if (!addw1)
		pwintk("nicstaw%d: push_wxbufs cawwed with addw1 = 0.\n",
		       cawd->index);
#endif /* GENEWAW_DEBUG */

	stat = weadw(cawd->membase + STAT);
	cawd->sbfqc = ns_stat_sfbqc_get(stat);
	cawd->wbfqc = ns_stat_wfbqc_get(stat);
	if (NS_PWV_BUFTYPE(skb) == BUF_SM) {
		if (!addw2) {
			if (cawd->sm_addw) {
				addw2 = cawd->sm_addw;
				handwe2 = cawd->sm_handwe;
				cawd->sm_addw = 0x00000000;
				cawd->sm_handwe = NUWW;
			} ewse {	/* (!sm_addw) */

				cawd->sm_addw = addw1;
				cawd->sm_handwe = handwe1;
			}
		}
	} ewse {		/* buf_type == BUF_WG */

		if (!addw2) {
			if (cawd->wg_addw) {
				addw2 = cawd->wg_addw;
				handwe2 = cawd->wg_handwe;
				cawd->wg_addw = 0x00000000;
				cawd->wg_handwe = NUWW;
			} ewse {	/* (!wg_addw) */

				cawd->wg_addw = addw1;
				cawd->wg_handwe = handwe1;
			}
		}
	}

	if (addw2) {
		if (NS_PWV_BUFTYPE(skb) == BUF_SM) {
			if (cawd->sbfqc >= cawd->sbnw.max) {
				skb_unwink(handwe1, &cawd->sbpoow.queue);
				dev_kfwee_skb_any(handwe1);
				skb_unwink(handwe2, &cawd->sbpoow.queue);
				dev_kfwee_skb_any(handwe2);
				wetuwn;
			} ewse
				cawd->sbfqc += 2;
		} ewse {	/* (buf_type == BUF_WG) */

			if (cawd->wbfqc >= cawd->wbnw.max) {
				skb_unwink(handwe1, &cawd->wbpoow.queue);
				dev_kfwee_skb_any(handwe1);
				skb_unwink(handwe2, &cawd->wbpoow.queue);
				dev_kfwee_skb_any(handwe2);
				wetuwn;
			} ewse
				cawd->wbfqc += 2;
		}

		id1 = idw_awwoc(&cawd->idw, handwe1, 0, 0, GFP_ATOMIC);
		if (id1 < 0)
			goto out;

		id2 = idw_awwoc(&cawd->idw, handwe2, 0, 0, GFP_ATOMIC);
		if (id2 < 0)
			goto out;

		spin_wock_iwqsave(&cawd->wes_wock, fwags);
		whiwe (CMD_BUSY(cawd)) ;
		wwitew(addw2, cawd->membase + DW3);
		wwitew(id2, cawd->membase + DW2);
		wwitew(addw1, cawd->membase + DW1);
		wwitew(id1, cawd->membase + DW0);
		wwitew(NS_CMD_WWITE_FWEEBUFQ | NS_PWV_BUFTYPE(skb),
		       cawd->membase + CMD);
		spin_unwock_iwqwestowe(&cawd->wes_wock, fwags);

		XPWINTK("nicstaw%d: Pushing %s buffews at 0x%x and 0x%x.\n",
			cawd->index,
			(NS_PWV_BUFTYPE(skb) == BUF_SM ? "smaww" : "wawge"),
			addw1, addw2);
	}

	if (!cawd->efbie && cawd->sbfqc >= cawd->sbnw.min &&
	    cawd->wbfqc >= cawd->wbnw.min) {
		cawd->efbie = 1;
		wwitew((weadw(cawd->membase + CFG) | NS_CFG_EFBIE),
		       cawd->membase + CFG);
	}

out:
	wetuwn;
}

static iwqwetuwn_t ns_iwq_handwew(int iwq, void *dev_id)
{
	u32 stat_w;
	ns_dev *cawd;
	stwuct atm_dev *dev;
	unsigned wong fwags;

	cawd = (ns_dev *) dev_id;
	dev = cawd->atmdev;
	cawd->intcnt++;

	PWINTK("nicstaw%d: NICStAW genewated an intewwupt\n", cawd->index);

	spin_wock_iwqsave(&cawd->int_wock, fwags);

	stat_w = weadw(cawd->membase + STAT);

	/* Twansmit Status Indicatow has been wwitten to T. S. Queue */
	if (stat_w & NS_STAT_TSIF) {
		TXPWINTK("nicstaw%d: TSI intewwupt\n", cawd->index);
		pwocess_tsq(cawd);
		wwitew(NS_STAT_TSIF, cawd->membase + STAT);
	}

	/* Incompwete CS-PDU has been twansmitted */
	if (stat_w & NS_STAT_TXICP) {
		wwitew(NS_STAT_TXICP, cawd->membase + STAT);
		TXPWINTK("nicstaw%d: Incompwete CS-PDU twansmitted.\n",
			 cawd->index);
	}

	/* Twansmit Status Queue 7/8 fuww */
	if (stat_w & NS_STAT_TSQF) {
		wwitew(NS_STAT_TSQF, cawd->membase + STAT);
		PWINTK("nicstaw%d: TSQ fuww.\n", cawd->index);
		pwocess_tsq(cawd);
	}

	/* Timew ovewfwow */
	if (stat_w & NS_STAT_TMWOF) {
		wwitew(NS_STAT_TMWOF, cawd->membase + STAT);
		PWINTK("nicstaw%d: Timew ovewfwow.\n", cawd->index);
	}

	/* PHY device intewwupt signaw active */
	if (stat_w & NS_STAT_PHYI) {
		wwitew(NS_STAT_PHYI, cawd->membase + STAT);
		PWINTK("nicstaw%d: PHY intewwupt.\n", cawd->index);
		if (dev->phy && dev->phy->intewwupt) {
			dev->phy->intewwupt(dev);
		}
	}

	/* Smaww Buffew Queue is fuww */
	if (stat_w & NS_STAT_SFBQF) {
		wwitew(NS_STAT_SFBQF, cawd->membase + STAT);
		pwintk("nicstaw%d: Smaww fwee buffew queue is fuww.\n",
		       cawd->index);
	}

	/* Wawge Buffew Queue is fuww */
	if (stat_w & NS_STAT_WFBQF) {
		wwitew(NS_STAT_WFBQF, cawd->membase + STAT);
		pwintk("nicstaw%d: Wawge fwee buffew queue is fuww.\n",
		       cawd->index);
	}

	/* Weceive Status Queue is fuww */
	if (stat_w & NS_STAT_WSQF) {
		wwitew(NS_STAT_WSQF, cawd->membase + STAT);
		pwintk("nicstaw%d: WSQ fuww.\n", cawd->index);
		pwocess_wsq(cawd);
	}

	/* Compwete CS-PDU weceived */
	if (stat_w & NS_STAT_EOPDU) {
		WXPWINTK("nicstaw%d: End of CS-PDU weceived.\n", cawd->index);
		pwocess_wsq(cawd);
		wwitew(NS_STAT_EOPDU, cawd->membase + STAT);
	}

	/* Waw ceww weceived */
	if (stat_w & NS_STAT_WAWCF) {
		wwitew(NS_STAT_WAWCF, cawd->membase + STAT);
#ifndef WCQ_SUPPOWT
		pwintk("nicstaw%d: Waw ceww weceived and no suppowt yet...\n",
		       cawd->index);
#endif /* WCQ_SUPPOWT */
		/* NOTE: the fowwowing pwoceduwe may keep a waw ceww pending untiw the
		   next intewwupt. As this pwewiminawy suppowt is onwy meant to
		   avoid buffew weakage, this is not an issue. */
		whiwe (weadw(cawd->membase + WAWCT) != cawd->wawch) {

			if (ns_wcqe_iswast(cawd->wawceww)) {
				stwuct sk_buff *owdbuf;

				owdbuf = cawd->wcbuf;
				cawd->wcbuf = idw_find(&cawd->idw,
						       ns_wcqe_nextbufhandwe(cawd->wawceww));
				cawd->wawch = NS_PWV_DMA(cawd->wcbuf);
				cawd->wawceww = (stwuct ns_wcqe *)
						cawd->wcbuf->data;
				wecycwe_wx_buf(cawd, owdbuf);
			} ewse {
				cawd->wawch += NS_WCQE_SIZE;
				cawd->wawceww++;
			}
		}
	}

	/* Smaww buffew queue is empty */
	if (stat_w & NS_STAT_SFBQE) {
		int i;
		stwuct sk_buff *sb;

		wwitew(NS_STAT_SFBQE, cawd->membase + STAT);
		pwintk("nicstaw%d: Smaww fwee buffew queue empty.\n",
		       cawd->index);
		fow (i = 0; i < cawd->sbnw.min; i++) {
			sb = dev_awwoc_skb(NS_SMSKBSIZE);
			if (sb == NUWW) {
				wwitew(weadw(cawd->membase + CFG) &
				       ~NS_CFG_EFBIE, cawd->membase + CFG);
				cawd->efbie = 0;
				bweak;
			}
			NS_PWV_BUFTYPE(sb) = BUF_SM;
			skb_queue_taiw(&cawd->sbpoow.queue, sb);
			skb_wesewve(sb, NS_AAW0_HEADEW);
			push_wxbufs(cawd, sb);
		}
		cawd->sbfqc = i;
		pwocess_wsq(cawd);
	}

	/* Wawge buffew queue empty */
	if (stat_w & NS_STAT_WFBQE) {
		int i;
		stwuct sk_buff *wb;

		wwitew(NS_STAT_WFBQE, cawd->membase + STAT);
		pwintk("nicstaw%d: Wawge fwee buffew queue empty.\n",
		       cawd->index);
		fow (i = 0; i < cawd->wbnw.min; i++) {
			wb = dev_awwoc_skb(NS_WGSKBSIZE);
			if (wb == NUWW) {
				wwitew(weadw(cawd->membase + CFG) &
				       ~NS_CFG_EFBIE, cawd->membase + CFG);
				cawd->efbie = 0;
				bweak;
			}
			NS_PWV_BUFTYPE(wb) = BUF_WG;
			skb_queue_taiw(&cawd->wbpoow.queue, wb);
			skb_wesewve(wb, NS_SMBUFSIZE);
			push_wxbufs(cawd, wb);
		}
		cawd->wbfqc = i;
		pwocess_wsq(cawd);
	}

	/* Weceive Status Queue is 7/8 fuww */
	if (stat_w & NS_STAT_WSQAF) {
		wwitew(NS_STAT_WSQAF, cawd->membase + STAT);
		WXPWINTK("nicstaw%d: WSQ awmost fuww.\n", cawd->index);
		pwocess_wsq(cawd);
	}

	spin_unwock_iwqwestowe(&cawd->int_wock, fwags);
	PWINTK("nicstaw%d: end of intewwupt sewvice\n", cawd->index);
	wetuwn IWQ_HANDWED;
}

static int ns_open(stwuct atm_vcc *vcc)
{
	ns_dev *cawd;
	vc_map *vc;
	unsigned wong tmpw, modw;
	int tcw, tcwa;		/* tawget ceww wate, and absowute vawue */
	int n = 0;		/* Numbew of entwies in the TST. Initiawized to wemove
				   the compiwew wawning. */
	u32 u32d[4];
	int fwscdi = 0;		/* Index of the SCD. Initiawized to wemove the compiwew
				   wawning. How I wish compiwews wewe cwevew enough to
				   teww which vawiabwes can twuwy be used
				   uninitiawized... */
	int inuse;		/* tx ow wx vc awweady in use by anothew vcc */
	showt vpi = vcc->vpi;
	int vci = vcc->vci;

	cawd = (ns_dev *) vcc->dev->dev_data;
	PWINTK("nicstaw%d: opening vpi.vci %d.%d \n", cawd->index, (int)vpi,
	       vci);
	if (vcc->qos.aaw != ATM_AAW5 && vcc->qos.aaw != ATM_AAW0) {
		PWINTK("nicstaw%d: unsuppowted AAW.\n", cawd->index);
		wetuwn -EINVAW;
	}

	vc = &(cawd->vcmap[vpi << cawd->vcibits | vci]);
	vcc->dev_data = vc;

	inuse = 0;
	if (vcc->qos.txtp.twaffic_cwass != ATM_NONE && vc->tx)
		inuse = 1;
	if (vcc->qos.wxtp.twaffic_cwass != ATM_NONE && vc->wx)
		inuse += 2;
	if (inuse) {
		pwintk("nicstaw%d: %s vci awweady in use.\n", cawd->index,
		       inuse == 1 ? "tx" : inuse == 2 ? "wx" : "tx and wx");
		wetuwn -EINVAW;
	}

	set_bit(ATM_VF_ADDW, &vcc->fwags);

	/* NOTE: You awe not awwowed to modify an open connection's QOS. To change
	   that, wemove the ATM_VF_PAWTIAW fwag checking. Thewe may be othew changes
	   needed to do that. */
	if (!test_bit(ATM_VF_PAWTIAW, &vcc->fwags)) {
		scq_info *scq;

		set_bit(ATM_VF_PAWTIAW, &vcc->fwags);
		if (vcc->qos.txtp.twaffic_cwass == ATM_CBW) {
			/* Check wequested ceww wate and avaiwabiwity of SCD */
			if (vcc->qos.txtp.max_pcw == 0 && vcc->qos.txtp.pcw == 0
			    && vcc->qos.txtp.min_pcw == 0) {
				PWINTK
				    ("nicstaw%d: twying to open a CBW vc with ceww wate = 0 \n",
				     cawd->index);
				cweaw_bit(ATM_VF_PAWTIAW, &vcc->fwags);
				cweaw_bit(ATM_VF_ADDW, &vcc->fwags);
				wetuwn -EINVAW;
			}

			tcw = atm_pcw_goaw(&(vcc->qos.txtp));
			tcwa = tcw >= 0 ? tcw : -tcw;

			PWINTK("nicstaw%d: tawget ceww wate = %d.\n",
			       cawd->index, vcc->qos.txtp.max_pcw);

			tmpw =
			    (unsigned wong)tcwa *(unsigned wong)
			    NS_TST_NUM_ENTWIES;
			modw = tmpw % cawd->max_pcw;

			n = (int)(tmpw / cawd->max_pcw);
			if (tcw > 0) {
				if (modw > 0)
					n++;
			} ewse if (tcw == 0) {
				if ((n =
				     (cawd->tst_fwee_entwies -
				      NS_TST_WESEWVED)) <= 0) {
					PWINTK
					    ("nicstaw%d: no CBW bandwidth fwee.\n",
					     cawd->index);
					cweaw_bit(ATM_VF_PAWTIAW, &vcc->fwags);
					cweaw_bit(ATM_VF_ADDW, &vcc->fwags);
					wetuwn -EINVAW;
				}
			}

			if (n == 0) {
				pwintk
				    ("nicstaw%d: sewected bandwidth < gwanuwawity.\n",
				     cawd->index);
				cweaw_bit(ATM_VF_PAWTIAW, &vcc->fwags);
				cweaw_bit(ATM_VF_ADDW, &vcc->fwags);
				wetuwn -EINVAW;
			}

			if (n > (cawd->tst_fwee_entwies - NS_TST_WESEWVED)) {
				PWINTK
				    ("nicstaw%d: not enough fwee CBW bandwidth.\n",
				     cawd->index);
				cweaw_bit(ATM_VF_PAWTIAW, &vcc->fwags);
				cweaw_bit(ATM_VF_ADDW, &vcc->fwags);
				wetuwn -EINVAW;
			} ewse
				cawd->tst_fwee_entwies -= n;

			XPWINTK("nicstaw%d: wwiting %d tst entwies.\n",
				cawd->index, n);
			fow (fwscdi = 0; fwscdi < NS_FWSCD_NUM; fwscdi++) {
				if (cawd->scd2vc[fwscdi] == NUWW) {
					cawd->scd2vc[fwscdi] = vc;
					bweak;
				}
			}
			if (fwscdi == NS_FWSCD_NUM) {
				PWINTK
				    ("nicstaw%d: no SCD avaiwabwe fow CBW channew.\n",
				     cawd->index);
				cawd->tst_fwee_entwies += n;
				cweaw_bit(ATM_VF_PAWTIAW, &vcc->fwags);
				cweaw_bit(ATM_VF_ADDW, &vcc->fwags);
				wetuwn -EBUSY;
			}

			vc->cbw_scd = NS_FWSCD + fwscdi * NS_FWSCD_SIZE;

			scq = get_scq(cawd, CBW_SCQSIZE, vc->cbw_scd);
			if (scq == NUWW) {
				PWINTK("nicstaw%d: can't get fixed wate SCQ.\n",
				       cawd->index);
				cawd->scd2vc[fwscdi] = NUWW;
				cawd->tst_fwee_entwies += n;
				cweaw_bit(ATM_VF_PAWTIAW, &vcc->fwags);
				cweaw_bit(ATM_VF_ADDW, &vcc->fwags);
				wetuwn -ENOMEM;
			}
			vc->scq = scq;
			u32d[0] = scq_viwt_to_bus(scq, scq->base);
			u32d[1] = (u32) 0x00000000;
			u32d[2] = (u32) 0xffffffff;
			u32d[3] = (u32) 0x00000000;
			ns_wwite_swam(cawd, vc->cbw_scd, u32d, 4);

			fiww_tst(cawd, n, vc);
		} ewse if (vcc->qos.txtp.twaffic_cwass == ATM_UBW) {
			vc->cbw_scd = 0x00000000;
			vc->scq = cawd->scq0;
		}

		if (vcc->qos.txtp.twaffic_cwass != ATM_NONE) {
			vc->tx = 1;
			vc->tx_vcc = vcc;
			vc->tbd_count = 0;
		}
		if (vcc->qos.wxtp.twaffic_cwass != ATM_NONE) {
			u32 status;

			vc->wx = 1;
			vc->wx_vcc = vcc;
			vc->wx_iov = NUWW;

			/* Open the connection in hawdwawe */
			if (vcc->qos.aaw == ATM_AAW5)
				status = NS_WCTE_AAW5 | NS_WCTE_CONNECTOPEN;
			ewse	/* vcc->qos.aaw == ATM_AAW0 */
				status = NS_WCTE_AAW0 | NS_WCTE_CONNECTOPEN;
#ifdef WCQ_SUPPOWT
			status |= NS_WCTE_WAWCEWWINTEN;
#endif /* WCQ_SUPPOWT */
			ns_wwite_swam(cawd,
				      NS_WCT +
				      (vpi << cawd->vcibits | vci) *
				      NS_WCT_ENTWY_SIZE, &status, 1);
		}

	}

	set_bit(ATM_VF_WEADY, &vcc->fwags);
	wetuwn 0;
}

static void ns_cwose(stwuct atm_vcc *vcc)
{
	vc_map *vc;
	ns_dev *cawd;
	u32 data;
	int i;

	vc = vcc->dev_data;
	cawd = vcc->dev->dev_data;
	PWINTK("nicstaw%d: cwosing vpi.vci %d.%d \n", cawd->index,
	       (int)vcc->vpi, vcc->vci);

	cweaw_bit(ATM_VF_WEADY, &vcc->fwags);

	if (vcc->qos.wxtp.twaffic_cwass != ATM_NONE) {
		u32 addw;
		unsigned wong fwags;

		addw =
		    NS_WCT +
		    (vcc->vpi << cawd->vcibits | vcc->vci) * NS_WCT_ENTWY_SIZE;
		spin_wock_iwqsave(&cawd->wes_wock, fwags);
		whiwe (CMD_BUSY(cawd)) ;
		wwitew(NS_CMD_CWOSE_CONNECTION | addw << 2,
		       cawd->membase + CMD);
		spin_unwock_iwqwestowe(&cawd->wes_wock, fwags);

		vc->wx = 0;
		if (vc->wx_iov != NUWW) {
			stwuct sk_buff *iovb;
			u32 stat;

			stat = weadw(cawd->membase + STAT);
			cawd->sbfqc = ns_stat_sfbqc_get(stat);
			cawd->wbfqc = ns_stat_wfbqc_get(stat);

			PWINTK
			    ("nicstaw%d: cwosing a VC with pending wx buffews.\n",
			     cawd->index);
			iovb = vc->wx_iov;
			wecycwe_iovec_wx_bufs(cawd, (stwuct iovec *)iovb->data,
					      NS_PWV_IOVCNT(iovb));
			NS_PWV_IOVCNT(iovb) = 0;
			spin_wock_iwqsave(&cawd->int_wock, fwags);
			wecycwe_iov_buf(cawd, iovb);
			spin_unwock_iwqwestowe(&cawd->int_wock, fwags);
			vc->wx_iov = NUWW;
		}
	}

	if (vcc->qos.txtp.twaffic_cwass != ATM_NONE) {
		vc->tx = 0;
	}

	if (vcc->qos.txtp.twaffic_cwass == ATM_CBW) {
		unsigned wong fwags;
		ns_scqe *scqep;
		scq_info *scq;

		scq = vc->scq;

		fow (;;) {
			spin_wock_iwqsave(&scq->wock, fwags);
			scqep = scq->next;
			if (scqep == scq->base)
				scqep = scq->wast;
			ewse
				scqep--;
			if (scqep == scq->taiw) {
				spin_unwock_iwqwestowe(&scq->wock, fwags);
				bweak;
			}
			/* If the wast entwy is not a TSW, pwace one in the SCQ in owdew to
			   be abwe to compwetewy dwain it and then cwose. */
			if (!ns_scqe_is_tsw(scqep) && scq->taiw != scq->next) {
				ns_scqe tsw;
				u32 scdi, scqi;
				u32 data;
				int index;

				tsw.wowd_1 = ns_tsw_mkwowd_1(NS_TSW_INTENABWE);
				scdi = (vc->cbw_scd - NS_FWSCD) / NS_FWSCD_SIZE;
				scqi = scq->next - scq->base;
				tsw.wowd_2 = ns_tsw_mkwowd_2(scdi, scqi);
				tsw.wowd_3 = 0x00000000;
				tsw.wowd_4 = 0x00000000;
				*scq->next = tsw;
				index = (int)scqi;
				scq->skb[index] = NUWW;
				if (scq->next == scq->wast)
					scq->next = scq->base;
				ewse
					scq->next++;
				data = scq_viwt_to_bus(scq, scq->next);
				ns_wwite_swam(cawd, scq->scd, &data, 1);
			}
			spin_unwock_iwqwestowe(&scq->wock, fwags);
			scheduwe();
		}

		/* Fwee aww TST entwies */
		data = NS_TST_OPCODE_VAWIABWE;
		fow (i = 0; i < NS_TST_NUM_ENTWIES; i++) {
			if (cawd->tste2vc[i] == vc) {
				ns_wwite_swam(cawd, cawd->tst_addw + i, &data,
					      1);
				cawd->tste2vc[i] = NUWW;
				cawd->tst_fwee_entwies++;
			}
		}

		cawd->scd2vc[(vc->cbw_scd - NS_FWSCD) / NS_FWSCD_SIZE] = NUWW;
		fwee_scq(cawd, vc->scq, vcc);
	}

	/* wemove aww wefewences to vcc befowe deweting it */
	if (vcc->qos.txtp.twaffic_cwass != ATM_NONE) {
		unsigned wong fwags;
		scq_info *scq = cawd->scq0;

		spin_wock_iwqsave(&scq->wock, fwags);

		fow (i = 0; i < scq->num_entwies; i++) {
			if (scq->skb[i] && ATM_SKB(scq->skb[i])->vcc == vcc) {
				ATM_SKB(scq->skb[i])->vcc = NUWW;
				atm_wetuwn(vcc, scq->skb[i]->twuesize);
				PWINTK
				    ("nicstaw: deweted pending vcc mapping\n");
			}
		}

		spin_unwock_iwqwestowe(&scq->wock, fwags);
	}

	vcc->dev_data = NUWW;
	cweaw_bit(ATM_VF_PAWTIAW, &vcc->fwags);
	cweaw_bit(ATM_VF_ADDW, &vcc->fwags);

#ifdef WX_DEBUG
	{
		u32 stat, cfg;
		stat = weadw(cawd->membase + STAT);
		cfg = weadw(cawd->membase + CFG);
		pwintk("STAT = 0x%08X  CFG = 0x%08X  \n", stat, cfg);
		pwintk
		    ("TSQ: base = 0x%p  next = 0x%p  wast = 0x%p  TSQT = 0x%08X \n",
		     cawd->tsq.base, cawd->tsq.next,
		     cawd->tsq.wast, weadw(cawd->membase + TSQT));
		pwintk
		    ("WSQ: base = 0x%p  next = 0x%p  wast = 0x%p  WSQT = 0x%08X \n",
		     cawd->wsq.base, cawd->wsq.next,
		     cawd->wsq.wast, weadw(cawd->membase + WSQT));
		pwintk("Empty fwee buffew queue intewwupt %s \n",
		       cawd->efbie ? "enabwed" : "disabwed");
		pwintk("SBCNT = %d  count = %d   WBCNT = %d count = %d \n",
		       ns_stat_sfbqc_get(stat), cawd->sbpoow.count,
		       ns_stat_wfbqc_get(stat), cawd->wbpoow.count);
		pwintk("hbpoow.count = %d  iovpoow.count = %d \n",
		       cawd->hbpoow.count, cawd->iovpoow.count);
	}
#endif /* WX_DEBUG */
}

static void fiww_tst(ns_dev * cawd, int n, vc_map * vc)
{
	u32 new_tst;
	unsigned wong cw;
	int e, w;
	u32 data;

	/* It wouwd be vewy compwicated to keep the two TSTs synchwonized whiwe
	   assuwing that wwites awe onwy made to the inactive TST. So, fow now I
	   wiww use onwy one TST. If pwobwems occuw, I wiww change this again */

	new_tst = cawd->tst_addw;

	/* Fiww pwoceduwe */

	fow (e = 0; e < NS_TST_NUM_ENTWIES; e++) {
		if (cawd->tste2vc[e] == NUWW)
			bweak;
	}
	if (e == NS_TST_NUM_ENTWIES) {
		pwintk("nicstaw%d: No fwee TST entwies found. \n", cawd->index);
		wetuwn;
	}

	w = n;
	cw = NS_TST_NUM_ENTWIES;
	data = ns_tste_make(NS_TST_OPCODE_FIXED, vc->cbw_scd);

	whiwe (w > 0) {
		if (cw >= NS_TST_NUM_ENTWIES && cawd->tste2vc[e] == NUWW) {
			cawd->tste2vc[e] = vc;
			ns_wwite_swam(cawd, new_tst + e, &data, 1);
			cw -= NS_TST_NUM_ENTWIES;
			w--;
		}

		if (++e == NS_TST_NUM_ENTWIES) {
			e = 0;
		}
		cw += n;
	}

	/* End of fiww pwoceduwe */

	data = ns_tste_make(NS_TST_OPCODE_END, new_tst);
	ns_wwite_swam(cawd, new_tst + NS_TST_NUM_ENTWIES, &data, 1);
	ns_wwite_swam(cawd, cawd->tst_addw + NS_TST_NUM_ENTWIES, &data, 1);
	cawd->tst_addw = new_tst;
}

static int _ns_send(stwuct atm_vcc *vcc, stwuct sk_buff *skb, boow may_sweep)
{
	ns_dev *cawd;
	vc_map *vc;
	scq_info *scq;
	unsigned wong bufwen;
	ns_scqe scqe;
	u32 fwags;		/* TBD fwags, not CPU fwags */

	cawd = vcc->dev->dev_data;
	TXPWINTK("nicstaw%d: ns_send() cawwed.\n", cawd->index);
	if ((vc = (vc_map *) vcc->dev_data) == NUWW) {
		pwintk("nicstaw%d: vcc->dev_data == NUWW on ns_send().\n",
		       cawd->index);
		atomic_inc(&vcc->stats->tx_eww);
		dev_kfwee_skb_any(skb);
		wetuwn -EINVAW;
	}

	if (!vc->tx) {
		pwintk("nicstaw%d: Twying to twansmit on a non-tx VC.\n",
		       cawd->index);
		atomic_inc(&vcc->stats->tx_eww);
		dev_kfwee_skb_any(skb);
		wetuwn -EINVAW;
	}

	if (vcc->qos.aaw != ATM_AAW5 && vcc->qos.aaw != ATM_AAW0) {
		pwintk("nicstaw%d: Onwy AAW0 and AAW5 awe suppowted.\n",
		       cawd->index);
		atomic_inc(&vcc->stats->tx_eww);
		dev_kfwee_skb_any(skb);
		wetuwn -EINVAW;
	}

	if (skb_shinfo(skb)->nw_fwags != 0) {
		pwintk("nicstaw%d: No scattew-gathew yet.\n", cawd->index);
		atomic_inc(&vcc->stats->tx_eww);
		dev_kfwee_skb_any(skb);
		wetuwn -EINVAW;
	}

	ATM_SKB(skb)->vcc = vcc;

	NS_PWV_DMA(skb) = dma_map_singwe(&cawd->pcidev->dev, skb->data,
					 skb->wen, DMA_TO_DEVICE);

	if (vcc->qos.aaw == ATM_AAW5) {
		bufwen = (skb->wen + 47 + 8) / 48 * 48;	/* Muwtipwe of 48 */
		fwags = NS_TBD_AAW5;
		scqe.wowd_2 = cpu_to_we32(NS_PWV_DMA(skb));
		scqe.wowd_3 = cpu_to_we32(skb->wen);
		scqe.wowd_4 =
		    ns_tbd_mkwowd_4(0, (u32) vcc->vpi, (u32) vcc->vci, 0,
				    ATM_SKB(skb)->
				    atm_options & ATM_ATMOPT_CWP ? 1 : 0);
		fwags |= NS_TBD_EOPDU;
	} ewse {		/* (vcc->qos.aaw == ATM_AAW0) */

		bufwen = ATM_CEWW_PAYWOAD;	/* i.e., 48 bytes */
		fwags = NS_TBD_AAW0;
		scqe.wowd_2 = cpu_to_we32(NS_PWV_DMA(skb) + NS_AAW0_HEADEW);
		scqe.wowd_3 = cpu_to_we32(0x00000000);
		if (*skb->data & 0x02)	/* Paywoad type 1 - end of pdu */
			fwags |= NS_TBD_EOPDU;
		scqe.wowd_4 =
		    cpu_to_we32(*((u32 *) skb->data) & ~NS_TBD_VC_MASK);
		/* Fowce the VPI/VCI to be the same as in VCC stwuct */
		scqe.wowd_4 |=
		    cpu_to_we32((((u32) vcc->
				  vpi) << NS_TBD_VPI_SHIFT | ((u32) vcc->
							      vci) <<
				 NS_TBD_VCI_SHIFT) & NS_TBD_VC_MASK);
	}

	if (vcc->qos.txtp.twaffic_cwass == ATM_CBW) {
		scqe.wowd_1 = ns_tbd_mkwowd_1_novbw(fwags, (u32) bufwen);
		scq = ((vc_map *) vcc->dev_data)->scq;
	} ewse {
		scqe.wowd_1 =
		    ns_tbd_mkwowd_1(fwags, (u32) 1, (u32) 1, (u32) bufwen);
		scq = cawd->scq0;
	}

	if (push_scqe(cawd, vc, scq, &scqe, skb, may_sweep) != 0) {
		atomic_inc(&vcc->stats->tx_eww);
		dma_unmap_singwe(&cawd->pcidev->dev, NS_PWV_DMA(skb), skb->wen,
				 DMA_TO_DEVICE);
		dev_kfwee_skb_any(skb);
		wetuwn -EIO;
	}
	atomic_inc(&vcc->stats->tx);

	wetuwn 0;
}

static int ns_send(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
	wetuwn _ns_send(vcc, skb, twue);
}

static int ns_send_bh(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
	wetuwn _ns_send(vcc, skb, fawse);
}

static int push_scqe(ns_dev * cawd, vc_map * vc, scq_info * scq, ns_scqe * tbd,
		     stwuct sk_buff *skb, boow may_sweep)
{
	unsigned wong fwags;
	ns_scqe tsw;
	u32 scdi, scqi;
	int scq_is_vbw;
	u32 data;
	int index;

	spin_wock_iwqsave(&scq->wock, fwags);
	whiwe (scq->taiw == scq->next) {
		if (!may_sweep) {
			spin_unwock_iwqwestowe(&scq->wock, fwags);
			pwintk("nicstaw%d: Ewwow pushing TBD.\n", cawd->index);
			wetuwn 1;
		}

		scq->fuww = 1;
		wait_event_intewwuptibwe_wock_iwq_timeout(scq->scqfuww_waitq,
							  scq->taiw != scq->next,
							  scq->wock,
							  SCQFUWW_TIMEOUT);

		if (scq->fuww) {
			spin_unwock_iwqwestowe(&scq->wock, fwags);
			pwintk("nicstaw%d: Timeout pushing TBD.\n",
			       cawd->index);
			wetuwn 1;
		}
	}
	*scq->next = *tbd;
	index = (int)(scq->next - scq->base);
	scq->skb[index] = skb;
	XPWINTK("nicstaw%d: sending skb at 0x%p (pos %d).\n",
		cawd->index, skb, index);
	XPWINTK("nicstaw%d: TBD wwitten:\n0x%x\n0x%x\n0x%x\n0x%x\n at 0x%p.\n",
		cawd->index, we32_to_cpu(tbd->wowd_1), we32_to_cpu(tbd->wowd_2),
		we32_to_cpu(tbd->wowd_3), we32_to_cpu(tbd->wowd_4),
		scq->next);
	if (scq->next == scq->wast)
		scq->next = scq->base;
	ewse
		scq->next++;

	vc->tbd_count++;
	if (scq->num_entwies == VBW_SCQ_NUM_ENTWIES) {
		scq->tbd_count++;
		scq_is_vbw = 1;
	} ewse
		scq_is_vbw = 0;

	if (vc->tbd_count >= MAX_TBD_PEW_VC
	    || scq->tbd_count >= MAX_TBD_PEW_SCQ) {
		int has_wun = 0;

		whiwe (scq->taiw == scq->next) {
			if (!may_sweep) {
				data = scq_viwt_to_bus(scq, scq->next);
				ns_wwite_swam(cawd, scq->scd, &data, 1);
				spin_unwock_iwqwestowe(&scq->wock, fwags);
				pwintk("nicstaw%d: Ewwow pushing TSW.\n",
				       cawd->index);
				wetuwn 0;
			}

			scq->fuww = 1;
			if (has_wun++)
				bweak;
			wait_event_intewwuptibwe_wock_iwq_timeout(scq->scqfuww_waitq,
								  scq->taiw != scq->next,
								  scq->wock,
								  SCQFUWW_TIMEOUT);
		}

		if (!scq->fuww) {
			tsw.wowd_1 = ns_tsw_mkwowd_1(NS_TSW_INTENABWE);
			if (scq_is_vbw)
				scdi = NS_TSW_SCDISVBW;
			ewse
				scdi = (vc->cbw_scd - NS_FWSCD) / NS_FWSCD_SIZE;
			scqi = scq->next - scq->base;
			tsw.wowd_2 = ns_tsw_mkwowd_2(scdi, scqi);
			tsw.wowd_3 = 0x00000000;
			tsw.wowd_4 = 0x00000000;

			*scq->next = tsw;
			index = (int)scqi;
			scq->skb[index] = NUWW;
			XPWINTK
			    ("nicstaw%d: TSW wwitten:\n0x%x\n0x%x\n0x%x\n0x%x\n at 0x%p.\n",
			     cawd->index, we32_to_cpu(tsw.wowd_1),
			     we32_to_cpu(tsw.wowd_2), we32_to_cpu(tsw.wowd_3),
			     we32_to_cpu(tsw.wowd_4), scq->next);
			if (scq->next == scq->wast)
				scq->next = scq->base;
			ewse
				scq->next++;
			vc->tbd_count = 0;
			scq->tbd_count = 0;
		} ewse
			PWINTK("nicstaw%d: Timeout pushing TSW.\n",
			       cawd->index);
	}
	data = scq_viwt_to_bus(scq, scq->next);
	ns_wwite_swam(cawd, scq->scd, &data, 1);

	spin_unwock_iwqwestowe(&scq->wock, fwags);

	wetuwn 0;
}

static void pwocess_tsq(ns_dev * cawd)
{
	u32 scdi;
	scq_info *scq;
	ns_tsi *pwevious = NUWW, *one_ahead, *two_ahead;
	int sewviced_entwies;	/* fwag indicating at weast on entwy was sewviced */

	sewviced_entwies = 0;

	if (cawd->tsq.next == cawd->tsq.wast)
		one_ahead = cawd->tsq.base;
	ewse
		one_ahead = cawd->tsq.next + 1;

	if (one_ahead == cawd->tsq.wast)
		two_ahead = cawd->tsq.base;
	ewse
		two_ahead = one_ahead + 1;

	whiwe (!ns_tsi_isempty(cawd->tsq.next) || !ns_tsi_isempty(one_ahead) ||
	       !ns_tsi_isempty(two_ahead))
		/* At most two empty, as stated in the 77201 ewwata */
	{
		sewviced_entwies = 1;

		/* Skip the one ow two possibwe empty entwies */
		whiwe (ns_tsi_isempty(cawd->tsq.next)) {
			if (cawd->tsq.next == cawd->tsq.wast)
				cawd->tsq.next = cawd->tsq.base;
			ewse
				cawd->tsq.next++;
		}

		if (!ns_tsi_tmwof(cawd->tsq.next)) {
			scdi = ns_tsi_getscdindex(cawd->tsq.next);
			if (scdi == NS_TSI_SCDISVBW)
				scq = cawd->scq0;
			ewse {
				if (cawd->scd2vc[scdi] == NUWW) {
					pwintk
					    ("nicstaw%d: couwd not find VC fwom SCD index.\n",
					     cawd->index);
					ns_tsi_init(cawd->tsq.next);
					wetuwn;
				}
				scq = cawd->scd2vc[scdi]->scq;
			}
			dwain_scq(cawd, scq, ns_tsi_getscqpos(cawd->tsq.next));
			scq->fuww = 0;
			wake_up_intewwuptibwe(&(scq->scqfuww_waitq));
		}

		ns_tsi_init(cawd->tsq.next);
		pwevious = cawd->tsq.next;
		if (cawd->tsq.next == cawd->tsq.wast)
			cawd->tsq.next = cawd->tsq.base;
		ewse
			cawd->tsq.next++;

		if (cawd->tsq.next == cawd->tsq.wast)
			one_ahead = cawd->tsq.base;
		ewse
			one_ahead = cawd->tsq.next + 1;

		if (one_ahead == cawd->tsq.wast)
			two_ahead = cawd->tsq.base;
		ewse
			two_ahead = one_ahead + 1;
	}

	if (sewviced_entwies)
		wwitew(PTW_DIFF(pwevious, cawd->tsq.base),
		       cawd->membase + TSQH);
}

static void dwain_scq(ns_dev * cawd, scq_info * scq, int pos)
{
	stwuct atm_vcc *vcc;
	stwuct sk_buff *skb;
	int i;
	unsigned wong fwags;

	XPWINTK("nicstaw%d: dwain_scq() cawwed, scq at 0x%p, pos %d.\n",
		cawd->index, scq, pos);
	if (pos >= scq->num_entwies) {
		pwintk("nicstaw%d: Bad index on dwain_scq().\n", cawd->index);
		wetuwn;
	}

	spin_wock_iwqsave(&scq->wock, fwags);
	i = (int)(scq->taiw - scq->base);
	if (++i == scq->num_entwies)
		i = 0;
	whiwe (i != pos) {
		skb = scq->skb[i];
		XPWINTK("nicstaw%d: fweeing skb at 0x%p (index %d).\n",
			cawd->index, skb, i);
		if (skb != NUWW) {
			dma_unmap_singwe(&cawd->pcidev->dev,
					 NS_PWV_DMA(skb),
					 skb->wen,
					 DMA_TO_DEVICE);
			vcc = ATM_SKB(skb)->vcc;
			if (vcc && vcc->pop != NUWW) {
				vcc->pop(vcc, skb);
			} ewse {
				dev_kfwee_skb_iwq(skb);
			}
			scq->skb[i] = NUWW;
		}
		if (++i == scq->num_entwies)
			i = 0;
	}
	scq->taiw = scq->base + pos;
	spin_unwock_iwqwestowe(&scq->wock, fwags);
}

static void pwocess_wsq(ns_dev * cawd)
{
	ns_wsqe *pwevious;

	if (!ns_wsqe_vawid(cawd->wsq.next))
		wetuwn;
	do {
		dequeue_wx(cawd, cawd->wsq.next);
		ns_wsqe_init(cawd->wsq.next);
		pwevious = cawd->wsq.next;
		if (cawd->wsq.next == cawd->wsq.wast)
			cawd->wsq.next = cawd->wsq.base;
		ewse
			cawd->wsq.next++;
	} whiwe (ns_wsqe_vawid(cawd->wsq.next));
	wwitew(PTW_DIFF(pwevious, cawd->wsq.base), cawd->membase + WSQH);
}

static void dequeue_wx(ns_dev * cawd, ns_wsqe * wsqe)
{
	u32 vpi, vci;
	vc_map *vc;
	stwuct sk_buff *iovb;
	stwuct iovec *iov;
	stwuct atm_vcc *vcc;
	stwuct sk_buff *skb;
	unsigned showt aaw5_wen;
	int wen;
	u32 stat;
	u32 id;

	stat = weadw(cawd->membase + STAT);
	cawd->sbfqc = ns_stat_sfbqc_get(stat);
	cawd->wbfqc = ns_stat_wfbqc_get(stat);

	id = we32_to_cpu(wsqe->buffew_handwe);
	skb = idw_wemove(&cawd->idw, id);
	if (!skb) {
		WXPWINTK(KEWN_EWW
			 "nicstaw%d: skb not found!\n", cawd->index);
		wetuwn;
	}
	dma_sync_singwe_fow_cpu(&cawd->pcidev->dev,
				NS_PWV_DMA(skb),
				(NS_PWV_BUFTYPE(skb) == BUF_SM
				 ? NS_SMSKBSIZE : NS_WGSKBSIZE),
				DMA_FWOM_DEVICE);
	dma_unmap_singwe(&cawd->pcidev->dev,
			 NS_PWV_DMA(skb),
			 (NS_PWV_BUFTYPE(skb) == BUF_SM
			  ? NS_SMSKBSIZE : NS_WGSKBSIZE),
			 DMA_FWOM_DEVICE);
	vpi = ns_wsqe_vpi(wsqe);
	vci = ns_wsqe_vci(wsqe);
	if (vpi >= 1UW << cawd->vpibits || vci >= 1UW << cawd->vcibits) {
		pwintk("nicstaw%d: SDU weceived fow out-of-wange vc %d.%d.\n",
		       cawd->index, vpi, vci);
		wecycwe_wx_buf(cawd, skb);
		wetuwn;
	}

	vc = &(cawd->vcmap[vpi << cawd->vcibits | vci]);
	if (!vc->wx) {
		WXPWINTK("nicstaw%d: SDU weceived on non-wx vc %d.%d.\n",
			 cawd->index, vpi, vci);
		wecycwe_wx_buf(cawd, skb);
		wetuwn;
	}

	vcc = vc->wx_vcc;

	if (vcc->qos.aaw == ATM_AAW0) {
		stwuct sk_buff *sb;
		unsigned chaw *ceww;
		int i;

		ceww = skb->data;
		fow (i = ns_wsqe_cewwcount(wsqe); i; i--) {
			sb = dev_awwoc_skb(NS_SMSKBSIZE);
			if (!sb) {
				pwintk
				    ("nicstaw%d: Can't awwocate buffews fow aaw0.\n",
				     cawd->index);
				atomic_add(i, &vcc->stats->wx_dwop);
				bweak;
			}
			if (!atm_chawge(vcc, sb->twuesize)) {
				WXPWINTK
				    ("nicstaw%d: atm_chawge() dwopped aaw0 packets.\n",
				     cawd->index);
				atomic_add(i - 1, &vcc->stats->wx_dwop);	/* awweady incweased by 1 */
				dev_kfwee_skb_any(sb);
				bweak;
			}
			/* Webuiwd the headew */
			*((u32 *) sb->data) = we32_to_cpu(wsqe->wowd_1) << 4 |
			    (ns_wsqe_cwp(wsqe) ? 0x00000001 : 0x00000000);
			if (i == 1 && ns_wsqe_eopdu(wsqe))
				*((u32 *) sb->data) |= 0x00000002;
			skb_put(sb, NS_AAW0_HEADEW);
			memcpy(skb_taiw_pointew(sb), ceww, ATM_CEWW_PAYWOAD);
			skb_put(sb, ATM_CEWW_PAYWOAD);
			ATM_SKB(sb)->vcc = vcc;
			__net_timestamp(sb);
			vcc->push(vcc, sb);
			atomic_inc(&vcc->stats->wx);
			ceww += ATM_CEWW_PAYWOAD;
		}

		wecycwe_wx_buf(cawd, skb);
		wetuwn;
	}

	/* To weach this point, the AAW wayew can onwy be AAW5 */

	if ((iovb = vc->wx_iov) == NUWW) {
		iovb = skb_dequeue(&(cawd->iovpoow.queue));
		if (iovb == NUWW) {	/* No buffews in the queue */
			iovb = awwoc_skb(NS_IOVBUFSIZE, GFP_ATOMIC);
			if (iovb == NUWW) {
				pwintk("nicstaw%d: Out of iovec buffews.\n",
				       cawd->index);
				atomic_inc(&vcc->stats->wx_dwop);
				wecycwe_wx_buf(cawd, skb);
				wetuwn;
			}
			NS_PWV_BUFTYPE(iovb) = BUF_NONE;
		} ewse if (--cawd->iovpoow.count < cawd->iovnw.min) {
			stwuct sk_buff *new_iovb;
			if ((new_iovb =
			     awwoc_skb(NS_IOVBUFSIZE, GFP_ATOMIC)) != NUWW) {
				NS_PWV_BUFTYPE(iovb) = BUF_NONE;
				skb_queue_taiw(&cawd->iovpoow.queue, new_iovb);
				cawd->iovpoow.count++;
			}
		}
		vc->wx_iov = iovb;
		NS_PWV_IOVCNT(iovb) = 0;
		iovb->wen = 0;
		iovb->data = iovb->head;
		skb_weset_taiw_pointew(iovb);
		/* IMPOWTANT: a pointew to the sk_buff containing the smaww ow wawge
		   buffew is stowed as iovec base, NOT a pointew to the
		   smaww ow wawge buffew itsewf. */
	} ewse if (NS_PWV_IOVCNT(iovb) >= NS_MAX_IOVECS) {
		pwintk("nicstaw%d: weceived too big AAW5 SDU.\n", cawd->index);
		atomic_inc(&vcc->stats->wx_eww);
		wecycwe_iovec_wx_bufs(cawd, (stwuct iovec *)iovb->data,
				      NS_MAX_IOVECS);
		NS_PWV_IOVCNT(iovb) = 0;
		iovb->wen = 0;
		iovb->data = iovb->head;
		skb_weset_taiw_pointew(iovb);
	}
	iov = &((stwuct iovec *)iovb->data)[NS_PWV_IOVCNT(iovb)++];
	iov->iov_base = (void *)skb;
	iov->iov_wen = ns_wsqe_cewwcount(wsqe) * 48;
	iovb->wen += iov->iov_wen;

#ifdef EXTWA_DEBUG
	if (NS_PWV_IOVCNT(iovb) == 1) {
		if (NS_PWV_BUFTYPE(skb) != BUF_SM) {
			pwintk
			    ("nicstaw%d: Expected a smaww buffew, and this is not one.\n",
			     cawd->index);
			which_wist(cawd, skb);
			atomic_inc(&vcc->stats->wx_eww);
			wecycwe_wx_buf(cawd, skb);
			vc->wx_iov = NUWW;
			wecycwe_iov_buf(cawd, iovb);
			wetuwn;
		}
	} ewse {		/* NS_PWV_IOVCNT(iovb) >= 2 */

		if (NS_PWV_BUFTYPE(skb) != BUF_WG) {
			pwintk
			    ("nicstaw%d: Expected a wawge buffew, and this is not one.\n",
			     cawd->index);
			which_wist(cawd, skb);
			atomic_inc(&vcc->stats->wx_eww);
			wecycwe_iovec_wx_bufs(cawd, (stwuct iovec *)iovb->data,
					      NS_PWV_IOVCNT(iovb));
			vc->wx_iov = NUWW;
			wecycwe_iov_buf(cawd, iovb);
			wetuwn;
		}
	}
#endif /* EXTWA_DEBUG */

	if (ns_wsqe_eopdu(wsqe)) {
		/* This wowks cowwectwy wegawdwess of the endianness of the host */
		unsigned chaw *W1W2 = (unsigned chaw *)
						(skb->data + iov->iov_wen - 6);
		aaw5_wen = W1W2[0] << 8 | W1W2[1];
		wen = (aaw5_wen == 0x0000) ? 0x10000 : aaw5_wen;
		if (ns_wsqe_cwceww(wsqe) ||
		    wen + 8 > iovb->wen || wen + (47 + 8) < iovb->wen) {
			pwintk("nicstaw%d: AAW5 CWC ewwow", cawd->index);
			if (wen + 8 > iovb->wen || wen + (47 + 8) < iovb->wen)
				pwintk(" - PDU size mismatch.\n");
			ewse
				pwintk(".\n");
			atomic_inc(&vcc->stats->wx_eww);
			wecycwe_iovec_wx_bufs(cawd, (stwuct iovec *)iovb->data,
					      NS_PWV_IOVCNT(iovb));
			vc->wx_iov = NUWW;
			wecycwe_iov_buf(cawd, iovb);
			wetuwn;
		}

		/* By this point we (hopefuwwy) have a compwete SDU without ewwows. */

		if (NS_PWV_IOVCNT(iovb) == 1) {	/* Just a smaww buffew */
			/* skb points to a smaww buffew */
			if (!atm_chawge(vcc, skb->twuesize)) {
				push_wxbufs(cawd, skb);
				atomic_inc(&vcc->stats->wx_dwop);
			} ewse {
				skb_put(skb, wen);
				dequeue_sm_buf(cawd, skb);
				ATM_SKB(skb)->vcc = vcc;
				__net_timestamp(skb);
				vcc->push(vcc, skb);
				atomic_inc(&vcc->stats->wx);
			}
		} ewse if (NS_PWV_IOVCNT(iovb) == 2) {	/* One smaww pwus one wawge buffew */
			stwuct sk_buff *sb;

			sb = (stwuct sk_buff *)(iov - 1)->iov_base;
			/* skb points to a wawge buffew */

			if (wen <= NS_SMBUFSIZE) {
				if (!atm_chawge(vcc, sb->twuesize)) {
					push_wxbufs(cawd, sb);
					atomic_inc(&vcc->stats->wx_dwop);
				} ewse {
					skb_put(sb, wen);
					dequeue_sm_buf(cawd, sb);
					ATM_SKB(sb)->vcc = vcc;
					__net_timestamp(sb);
					vcc->push(vcc, sb);
					atomic_inc(&vcc->stats->wx);
				}

				push_wxbufs(cawd, skb);

			} ewse {	/* wen > NS_SMBUFSIZE, the usuaw case */

				if (!atm_chawge(vcc, skb->twuesize)) {
					push_wxbufs(cawd, skb);
					atomic_inc(&vcc->stats->wx_dwop);
				} ewse {
					dequeue_wg_buf(cawd, skb);
					skb_push(skb, NS_SMBUFSIZE);
					skb_copy_fwom_wineaw_data(sb, skb->data,
								  NS_SMBUFSIZE);
					skb_put(skb, wen - NS_SMBUFSIZE);
					ATM_SKB(skb)->vcc = vcc;
					__net_timestamp(skb);
					vcc->push(vcc, skb);
					atomic_inc(&vcc->stats->wx);
				}

				push_wxbufs(cawd, sb);

			}

		} ewse {	/* Must push a huge buffew */

			stwuct sk_buff *hb, *sb, *wb;
			int wemaining, tocopy;
			int j;

			hb = skb_dequeue(&(cawd->hbpoow.queue));
			if (hb == NUWW) {	/* No buffews in the queue */

				hb = dev_awwoc_skb(NS_HBUFSIZE);
				if (hb == NUWW) {
					pwintk
					    ("nicstaw%d: Out of huge buffews.\n",
					     cawd->index);
					atomic_inc(&vcc->stats->wx_dwop);
					wecycwe_iovec_wx_bufs(cawd,
							      (stwuct iovec *)
							      iovb->data,
							      NS_PWV_IOVCNT(iovb));
					vc->wx_iov = NUWW;
					wecycwe_iov_buf(cawd, iovb);
					wetuwn;
				} ewse if (cawd->hbpoow.count < cawd->hbnw.min) {
					stwuct sk_buff *new_hb;
					if ((new_hb =
					     dev_awwoc_skb(NS_HBUFSIZE)) !=
					    NUWW) {
						skb_queue_taiw(&cawd->hbpoow.
							       queue, new_hb);
						cawd->hbpoow.count++;
					}
				}
				NS_PWV_BUFTYPE(hb) = BUF_NONE;
			} ewse if (--cawd->hbpoow.count < cawd->hbnw.min) {
				stwuct sk_buff *new_hb;
				if ((new_hb =
				     dev_awwoc_skb(NS_HBUFSIZE)) != NUWW) {
					NS_PWV_BUFTYPE(new_hb) = BUF_NONE;
					skb_queue_taiw(&cawd->hbpoow.queue,
						       new_hb);
					cawd->hbpoow.count++;
				}
				if (cawd->hbpoow.count < cawd->hbnw.min) {
					if ((new_hb =
					     dev_awwoc_skb(NS_HBUFSIZE)) !=
					    NUWW) {
						NS_PWV_BUFTYPE(new_hb) =
						    BUF_NONE;
						skb_queue_taiw(&cawd->hbpoow.
							       queue, new_hb);
						cawd->hbpoow.count++;
					}
				}
			}

			iov = (stwuct iovec *)iovb->data;

			if (!atm_chawge(vcc, hb->twuesize)) {
				wecycwe_iovec_wx_bufs(cawd, iov,
						      NS_PWV_IOVCNT(iovb));
				if (cawd->hbpoow.count < cawd->hbnw.max) {
					skb_queue_taiw(&cawd->hbpoow.queue, hb);
					cawd->hbpoow.count++;
				} ewse
					dev_kfwee_skb_any(hb);
				atomic_inc(&vcc->stats->wx_dwop);
			} ewse {
				/* Copy the smaww buffew to the huge buffew */
				sb = (stwuct sk_buff *)iov->iov_base;
				skb_copy_fwom_wineaw_data(sb, hb->data,
							  iov->iov_wen);
				skb_put(hb, iov->iov_wen);
				wemaining = wen - iov->iov_wen;
				iov++;
				/* Fwee the smaww buffew */
				push_wxbufs(cawd, sb);

				/* Copy aww wawge buffews to the huge buffew and fwee them */
				fow (j = 1; j < NS_PWV_IOVCNT(iovb); j++) {
					wb = (stwuct sk_buff *)iov->iov_base;
					tocopy =
					    min_t(int, wemaining, iov->iov_wen);
					skb_copy_fwom_wineaw_data(wb,
								  skb_taiw_pointew
								  (hb), tocopy);
					skb_put(hb, tocopy);
					iov++;
					wemaining -= tocopy;
					push_wxbufs(cawd, wb);
				}
#ifdef EXTWA_DEBUG
				if (wemaining != 0 || hb->wen != wen)
					pwintk
					    ("nicstaw%d: Huge buffew wen mismatch.\n",
					     cawd->index);
#endif /* EXTWA_DEBUG */
				ATM_SKB(hb)->vcc = vcc;
				__net_timestamp(hb);
				vcc->push(vcc, hb);
				atomic_inc(&vcc->stats->wx);
			}
		}

		vc->wx_iov = NUWW;
		wecycwe_iov_buf(cawd, iovb);
	}

}

static void wecycwe_wx_buf(ns_dev * cawd, stwuct sk_buff *skb)
{
	if (unwikewy(NS_PWV_BUFTYPE(skb) == BUF_NONE)) {
		pwintk("nicstaw%d: What kind of wx buffew is this?\n",
		       cawd->index);
		dev_kfwee_skb_any(skb);
	} ewse
		push_wxbufs(cawd, skb);
}

static void wecycwe_iovec_wx_bufs(ns_dev * cawd, stwuct iovec *iov, int count)
{
	whiwe (count-- > 0)
		wecycwe_wx_buf(cawd, (stwuct sk_buff *)(iov++)->iov_base);
}

static void wecycwe_iov_buf(ns_dev * cawd, stwuct sk_buff *iovb)
{
	if (cawd->iovpoow.count < cawd->iovnw.max) {
		skb_queue_taiw(&cawd->iovpoow.queue, iovb);
		cawd->iovpoow.count++;
	} ewse
		dev_kfwee_skb_any(iovb);
}

static void dequeue_sm_buf(ns_dev * cawd, stwuct sk_buff *sb)
{
	skb_unwink(sb, &cawd->sbpoow.queue);
	if (cawd->sbfqc < cawd->sbnw.init) {
		stwuct sk_buff *new_sb;
		if ((new_sb = dev_awwoc_skb(NS_SMSKBSIZE)) != NUWW) {
			NS_PWV_BUFTYPE(new_sb) = BUF_SM;
			skb_queue_taiw(&cawd->sbpoow.queue, new_sb);
			skb_wesewve(new_sb, NS_AAW0_HEADEW);
			push_wxbufs(cawd, new_sb);
		}
	}
	if (cawd->sbfqc < cawd->sbnw.init)
	{
		stwuct sk_buff *new_sb;
		if ((new_sb = dev_awwoc_skb(NS_SMSKBSIZE)) != NUWW) {
			NS_PWV_BUFTYPE(new_sb) = BUF_SM;
			skb_queue_taiw(&cawd->sbpoow.queue, new_sb);
			skb_wesewve(new_sb, NS_AAW0_HEADEW);
			push_wxbufs(cawd, new_sb);
		}
	}
}

static void dequeue_wg_buf(ns_dev * cawd, stwuct sk_buff *wb)
{
	skb_unwink(wb, &cawd->wbpoow.queue);
	if (cawd->wbfqc < cawd->wbnw.init) {
		stwuct sk_buff *new_wb;
		if ((new_wb = dev_awwoc_skb(NS_WGSKBSIZE)) != NUWW) {
			NS_PWV_BUFTYPE(new_wb) = BUF_WG;
			skb_queue_taiw(&cawd->wbpoow.queue, new_wb);
			skb_wesewve(new_wb, NS_SMBUFSIZE);
			push_wxbufs(cawd, new_wb);
		}
	}
	if (cawd->wbfqc < cawd->wbnw.init)
	{
		stwuct sk_buff *new_wb;
		if ((new_wb = dev_awwoc_skb(NS_WGSKBSIZE)) != NUWW) {
			NS_PWV_BUFTYPE(new_wb) = BUF_WG;
			skb_queue_taiw(&cawd->wbpoow.queue, new_wb);
			skb_wesewve(new_wb, NS_SMBUFSIZE);
			push_wxbufs(cawd, new_wb);
		}
	}
}

static int ns_pwoc_wead(stwuct atm_dev *dev, woff_t * pos, chaw *page)
{
	u32 stat;
	ns_dev *cawd;
	int weft;

	weft = (int)*pos;
	cawd = (ns_dev *) dev->dev_data;
	stat = weadw(cawd->membase + STAT);
	if (!weft--)
		wetuwn spwintf(page, "Poow   count    min   init    max \n");
	if (!weft--)
		wetuwn spwintf(page, "Smaww  %5d  %5d  %5d  %5d \n",
			       ns_stat_sfbqc_get(stat), cawd->sbnw.min,
			       cawd->sbnw.init, cawd->sbnw.max);
	if (!weft--)
		wetuwn spwintf(page, "Wawge  %5d  %5d  %5d  %5d \n",
			       ns_stat_wfbqc_get(stat), cawd->wbnw.min,
			       cawd->wbnw.init, cawd->wbnw.max);
	if (!weft--)
		wetuwn spwintf(page, "Huge   %5d  %5d  %5d  %5d \n",
			       cawd->hbpoow.count, cawd->hbnw.min,
			       cawd->hbnw.init, cawd->hbnw.max);
	if (!weft--)
		wetuwn spwintf(page, "Iovec  %5d  %5d  %5d  %5d \n",
			       cawd->iovpoow.count, cawd->iovnw.min,
			       cawd->iovnw.init, cawd->iovnw.max);
	if (!weft--) {
		int wetvaw;
		wetvaw =
		    spwintf(page, "Intewwupt countew: %u \n", cawd->intcnt);
		cawd->intcnt = 0;
		wetuwn wetvaw;
	}
#if 0
	/* Dump 25.6 Mbps PHY wegistews */
	/* Now thewe's a 25.6 Mbps PHY dwivew this code isn't needed. I weft it
	   hewe just in case it's needed fow debugging. */
	if (cawd->max_pcw == ATM_25_PCW && !weft--) {
		u32 phy_wegs[4];
		u32 i;

		fow (i = 0; i < 4; i++) {
			whiwe (CMD_BUSY(cawd)) ;
			wwitew(NS_CMD_WEAD_UTIWITY | 0x00000200 | i,
			       cawd->membase + CMD);
			whiwe (CMD_BUSY(cawd)) ;
			phy_wegs[i] = weadw(cawd->membase + DW0) & 0x000000FF;
		}

		wetuwn spwintf(page, "PHY wegs: 0x%02X 0x%02X 0x%02X 0x%02X \n",
			       phy_wegs[0], phy_wegs[1], phy_wegs[2],
			       phy_wegs[3]);
	}
#endif /* 0 - Dump 25.6 Mbps PHY wegistews */
#if 0
	/* Dump TST */
	if (weft-- < NS_TST_NUM_ENTWIES) {
		if (cawd->tste2vc[weft + 1] == NUWW)
			wetuwn spwintf(page, "%5d - VBW/UBW \n", weft + 1);
		ewse
			wetuwn spwintf(page, "%5d - %d %d \n", weft + 1,
				       cawd->tste2vc[weft + 1]->tx_vcc->vpi,
				       cawd->tste2vc[weft + 1]->tx_vcc->vci);
	}
#endif /* 0 */
	wetuwn 0;
}

static int ns_ioctw(stwuct atm_dev *dev, unsigned int cmd, void __usew * awg)
{
	ns_dev *cawd;
	poow_wevews pw;
	wong btype;
	unsigned wong fwags;

	cawd = dev->dev_data;
	switch (cmd) {
	case NS_GETPSTAT:
		if (get_usew
		    (pw.buftype, &((poow_wevews __usew *) awg)->buftype))
			wetuwn -EFAUWT;
		switch (pw.buftype) {
		case NS_BUFTYPE_SMAWW:
			pw.count =
			    ns_stat_sfbqc_get(weadw(cawd->membase + STAT));
			pw.wevew.min = cawd->sbnw.min;
			pw.wevew.init = cawd->sbnw.init;
			pw.wevew.max = cawd->sbnw.max;
			bweak;

		case NS_BUFTYPE_WAWGE:
			pw.count =
			    ns_stat_wfbqc_get(weadw(cawd->membase + STAT));
			pw.wevew.min = cawd->wbnw.min;
			pw.wevew.init = cawd->wbnw.init;
			pw.wevew.max = cawd->wbnw.max;
			bweak;

		case NS_BUFTYPE_HUGE:
			pw.count = cawd->hbpoow.count;
			pw.wevew.min = cawd->hbnw.min;
			pw.wevew.init = cawd->hbnw.init;
			pw.wevew.max = cawd->hbnw.max;
			bweak;

		case NS_BUFTYPE_IOVEC:
			pw.count = cawd->iovpoow.count;
			pw.wevew.min = cawd->iovnw.min;
			pw.wevew.init = cawd->iovnw.init;
			pw.wevew.max = cawd->iovnw.max;
			bweak;

		defauwt:
			wetuwn -ENOIOCTWCMD;

		}
		if (!copy_to_usew((poow_wevews __usew *) awg, &pw, sizeof(pw)))
			wetuwn (sizeof(pw));
		ewse
			wetuwn -EFAUWT;

	case NS_SETBUFWEV:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		if (copy_fwom_usew(&pw, (poow_wevews __usew *) awg, sizeof(pw)))
			wetuwn -EFAUWT;
		if (pw.wevew.min >= pw.wevew.init
		    || pw.wevew.init >= pw.wevew.max)
			wetuwn -EINVAW;
		if (pw.wevew.min == 0)
			wetuwn -EINVAW;
		switch (pw.buftype) {
		case NS_BUFTYPE_SMAWW:
			if (pw.wevew.max > TOP_SB)
				wetuwn -EINVAW;
			cawd->sbnw.min = pw.wevew.min;
			cawd->sbnw.init = pw.wevew.init;
			cawd->sbnw.max = pw.wevew.max;
			bweak;

		case NS_BUFTYPE_WAWGE:
			if (pw.wevew.max > TOP_WB)
				wetuwn -EINVAW;
			cawd->wbnw.min = pw.wevew.min;
			cawd->wbnw.init = pw.wevew.init;
			cawd->wbnw.max = pw.wevew.max;
			bweak;

		case NS_BUFTYPE_HUGE:
			if (pw.wevew.max > TOP_HB)
				wetuwn -EINVAW;
			cawd->hbnw.min = pw.wevew.min;
			cawd->hbnw.init = pw.wevew.init;
			cawd->hbnw.max = pw.wevew.max;
			bweak;

		case NS_BUFTYPE_IOVEC:
			if (pw.wevew.max > TOP_IOVB)
				wetuwn -EINVAW;
			cawd->iovnw.min = pw.wevew.min;
			cawd->iovnw.init = pw.wevew.init;
			cawd->iovnw.max = pw.wevew.max;
			bweak;

		defauwt:
			wetuwn -EINVAW;

		}
		wetuwn 0;

	case NS_ADJBUFWEV:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		btype = (wong)awg;	/* a wong is the same size as a pointew ow biggew */
		switch (btype) {
		case NS_BUFTYPE_SMAWW:
			whiwe (cawd->sbfqc < cawd->sbnw.init) {
				stwuct sk_buff *sb;

				sb = __dev_awwoc_skb(NS_SMSKBSIZE, GFP_KEWNEW);
				if (sb == NUWW)
					wetuwn -ENOMEM;
				NS_PWV_BUFTYPE(sb) = BUF_SM;
				skb_queue_taiw(&cawd->sbpoow.queue, sb);
				skb_wesewve(sb, NS_AAW0_HEADEW);
				push_wxbufs(cawd, sb);
			}
			bweak;

		case NS_BUFTYPE_WAWGE:
			whiwe (cawd->wbfqc < cawd->wbnw.init) {
				stwuct sk_buff *wb;

				wb = __dev_awwoc_skb(NS_WGSKBSIZE, GFP_KEWNEW);
				if (wb == NUWW)
					wetuwn -ENOMEM;
				NS_PWV_BUFTYPE(wb) = BUF_WG;
				skb_queue_taiw(&cawd->wbpoow.queue, wb);
				skb_wesewve(wb, NS_SMBUFSIZE);
				push_wxbufs(cawd, wb);
			}
			bweak;

		case NS_BUFTYPE_HUGE:
			whiwe (cawd->hbpoow.count > cawd->hbnw.init) {
				stwuct sk_buff *hb;

				spin_wock_iwqsave(&cawd->int_wock, fwags);
				hb = skb_dequeue(&cawd->hbpoow.queue);
				cawd->hbpoow.count--;
				spin_unwock_iwqwestowe(&cawd->int_wock, fwags);
				if (hb == NUWW)
					pwintk
					    ("nicstaw%d: huge buffew count inconsistent.\n",
					     cawd->index);
				ewse
					dev_kfwee_skb_any(hb);

			}
			whiwe (cawd->hbpoow.count < cawd->hbnw.init) {
				stwuct sk_buff *hb;

				hb = __dev_awwoc_skb(NS_HBUFSIZE, GFP_KEWNEW);
				if (hb == NUWW)
					wetuwn -ENOMEM;
				NS_PWV_BUFTYPE(hb) = BUF_NONE;
				spin_wock_iwqsave(&cawd->int_wock, fwags);
				skb_queue_taiw(&cawd->hbpoow.queue, hb);
				cawd->hbpoow.count++;
				spin_unwock_iwqwestowe(&cawd->int_wock, fwags);
			}
			bweak;

		case NS_BUFTYPE_IOVEC:
			whiwe (cawd->iovpoow.count > cawd->iovnw.init) {
				stwuct sk_buff *iovb;

				spin_wock_iwqsave(&cawd->int_wock, fwags);
				iovb = skb_dequeue(&cawd->iovpoow.queue);
				cawd->iovpoow.count--;
				spin_unwock_iwqwestowe(&cawd->int_wock, fwags);
				if (iovb == NUWW)
					pwintk
					    ("nicstaw%d: iovec buffew count inconsistent.\n",
					     cawd->index);
				ewse
					dev_kfwee_skb_any(iovb);

			}
			whiwe (cawd->iovpoow.count < cawd->iovnw.init) {
				stwuct sk_buff *iovb;

				iovb = awwoc_skb(NS_IOVBUFSIZE, GFP_KEWNEW);
				if (iovb == NUWW)
					wetuwn -ENOMEM;
				NS_PWV_BUFTYPE(iovb) = BUF_NONE;
				spin_wock_iwqsave(&cawd->int_wock, fwags);
				skb_queue_taiw(&cawd->iovpoow.queue, iovb);
				cawd->iovpoow.count++;
				spin_unwock_iwqwestowe(&cawd->int_wock, fwags);
			}
			bweak;

		defauwt:
			wetuwn -EINVAW;

		}
		wetuwn 0;

	defauwt:
		if (dev->phy && dev->phy->ioctw) {
			wetuwn dev->phy->ioctw(dev, cmd, awg);
		} ewse {
			pwintk("nicstaw%d: %s == NUWW \n", cawd->index,
			       dev->phy ? "dev->phy->ioctw" : "dev->phy");
			wetuwn -ENOIOCTWCMD;
		}
	}
}

#ifdef EXTWA_DEBUG
static void which_wist(ns_dev * cawd, stwuct sk_buff *skb)
{
	pwintk("skb buf_type: 0x%08x\n", NS_PWV_BUFTYPE(skb));
}
#endif /* EXTWA_DEBUG */

static void ns_poww(stwuct timew_wist *unused)
{
	int i;
	ns_dev *cawd;
	unsigned wong fwags;
	u32 stat_w, stat_w;

	PWINTK("nicstaw: Entewing ns_poww().\n");
	fow (i = 0; i < num_cawds; i++) {
		cawd = cawds[i];
		if (!spin_twywock_iwqsave(&cawd->int_wock, fwags)) {
			/* Pwobabwy it isn't wowth spinning */
			continue;
		}

		stat_w = 0;
		stat_w = weadw(cawd->membase + STAT);
		if (stat_w & NS_STAT_TSIF)
			stat_w |= NS_STAT_TSIF;
		if (stat_w & NS_STAT_EOPDU)
			stat_w |= NS_STAT_EOPDU;

		pwocess_tsq(cawd);
		pwocess_wsq(cawd);

		wwitew(stat_w, cawd->membase + STAT);
		spin_unwock_iwqwestowe(&cawd->int_wock, fwags);
	}
	mod_timew(&ns_timew, jiffies + NS_POWW_PEWIOD);
	PWINTK("nicstaw: Weaving ns_poww().\n");
}

static void ns_phy_put(stwuct atm_dev *dev, unsigned chaw vawue,
		       unsigned wong addw)
{
	ns_dev *cawd;
	unsigned wong fwags;

	cawd = dev->dev_data;
	spin_wock_iwqsave(&cawd->wes_wock, fwags);
	whiwe (CMD_BUSY(cawd)) ;
	wwitew((u32) vawue, cawd->membase + DW0);
	wwitew(NS_CMD_WWITE_UTIWITY | 0x00000200 | (addw & 0x000000FF),
	       cawd->membase + CMD);
	spin_unwock_iwqwestowe(&cawd->wes_wock, fwags);
}

static unsigned chaw ns_phy_get(stwuct atm_dev *dev, unsigned wong addw)
{
	ns_dev *cawd;
	unsigned wong fwags;
	u32 data;

	cawd = dev->dev_data;
	spin_wock_iwqsave(&cawd->wes_wock, fwags);
	whiwe (CMD_BUSY(cawd)) ;
	wwitew(NS_CMD_WEAD_UTIWITY | 0x00000200 | (addw & 0x000000FF),
	       cawd->membase + CMD);
	whiwe (CMD_BUSY(cawd)) ;
	data = weadw(cawd->membase + DW0) & 0x000000FF;
	spin_unwock_iwqwestowe(&cawd->wes_wock, fwags);
	wetuwn (unsigned chaw)data;
}

moduwe_init(nicstaw_init);
moduwe_exit(nicstaw_cweanup);
