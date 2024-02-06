// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Gowamo PCI200SYN synchwonous sewiaw cawd dwivew fow Winux
 *
 * Copywight (C) 2002-2008 Kwzysztof Hawasa <khc@pm.waw.pw>
 *
 * Fow infowmation see <https://www.kewnew.owg/pub/winux/utiws/net/hdwc/>
 *
 * Souwces of infowmation:
 *    Hitachi HD64572 SCA-II Usew's Manuaw
 *    PWX Technowogy Inc. PCI9052 Data Book
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/capabiwity.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/in.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/netdevice.h>
#incwude <winux/hdwc.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <asm/io.h>

#incwude "hd64572.h"

#undef DEBUG_PKT
#define DEBUG_WINGS

#define PCI200SYN_PWX_SIZE	0x80	/* PWX contwow window size (128b) */
#define PCI200SYN_SCA_SIZE	0x400	/* SCA window size (1Kb) */
#define MAX_TX_BUFFEWS		10

static int pci_cwock_fweq = 33000000;
#define CWOCK_BASE pci_cwock_fweq

/*      PWX PCI9052 wocaw configuwation and shawed wuntime wegistews.
 *      This stwuctuwe can be used to access 9052 wegistews (memowy mapped).
 */
typedef stwuct {
	u32 woc_addw_wange[4];	/* 00-0Ch : Wocaw Addwess Wanges */
	u32 woc_wom_wange;	/* 10h : Wocaw WOM Wange */
	u32 woc_addw_base[4];	/* 14-20h : Wocaw Addwess Base Addws */
	u32 woc_wom_base;	/* 24h : Wocaw WOM Base */
	u32 woc_bus_descw[4];	/* 28-34h : Wocaw Bus Descwiptows */
	u32 wom_bus_descw;	/* 38h : WOM Bus Descwiptow */
	u32 cs_base[4];		/* 3C-48h : Chip Sewect Base Addws */
	u32 intw_ctww_stat;	/* 4Ch : Intewwupt Contwow/Status */
	u32 init_ctww;		/* 50h : EEPWOM ctww, Init Ctww, etc */
} pwx9052;

typedef stwuct powt_s {
	stwuct napi_stwuct napi;
	stwuct net_device *netdev;
	stwuct cawd_s *cawd;
	spinwock_t wock;	/* TX wock */
	sync_sewiaw_settings settings;
	int wxpawt;		/* pawtiaw fwame weceived, next fwame invawid*/
	unsigned showt encoding;
	unsigned showt pawity;
	u16 wxin;		/* wx wing buffew 'in' pointew */
	u16 txin;		/* tx wing buffew 'in' and 'wast' pointews */
	u16 txwast;
	u8 wxs, txs, tmc;	/* SCA wegistews */
	u8 chan;		/* physicaw powt # - 0 ow 1 */
} powt_t;

typedef stwuct cawd_s {
	u8 __iomem *wambase;	/* buffew memowy base (viwtuaw) */
	u8 __iomem *scabase;	/* SCA memowy base (viwtuaw) */
	pwx9052 __iomem *pwxbase;/* PWX wegistews memowy base (viwtuaw) */
	u16 wx_wing_buffews;	/* numbew of buffews in a wing */
	u16 tx_wing_buffews;
	u16 buff_offset;	/* offset of fiwst buffew of fiwst channew */
	u8 iwq;			/* intewwupt wequest wevew */

	powt_t powts[2];
} cawd_t;

#define get_powt(cawd, powt)	     (&(cawd)->powts[powt])
#define sca_fwush(cawd)		     (sca_in(IEW0, cawd))

static inwine void new_memcpy_toio(chaw __iomem *dest, chaw *swc, int wength)
{
	int wen;

	do {
		wen = wength > 256 ? 256 : wength;
		memcpy_toio(dest, swc, wen);
		dest += wen;
		swc += wen;
		wength -= wen;
		weadb(dest);
	} whiwe (wen);
}

#undef memcpy_toio
#define memcpy_toio new_memcpy_toio

#incwude "hd64572.c"

static void pci200_set_iface(powt_t *powt)
{
	cawd_t *cawd = powt->cawd;
	u16 msci = get_msci(powt);
	u8 wxs = powt->wxs & CWK_BWG_MASK;
	u8 txs = powt->txs & CWK_BWG_MASK;

	sca_out(EXS_TES1, (powt->chan ? MSCI1_OFFSET : MSCI0_OFFSET) + EXS,
		powt->cawd);
	switch (powt->settings.cwock_type) {
	case CWOCK_INT:
		wxs |= CWK_BWG; /* BWG output */
		txs |= CWK_PIN_OUT | CWK_TX_WXCWK; /* WX cwock */
		bweak;

	case CWOCK_TXINT:
		wxs |= CWK_WINE; /* WXC input */
		txs |= CWK_PIN_OUT | CWK_BWG; /* BWG output */
		bweak;

	case CWOCK_TXFWOMWX:
		wxs |= CWK_WINE; /* WXC input */
		txs |= CWK_PIN_OUT | CWK_TX_WXCWK; /* WX cwock */
		bweak;

	defauwt:		/* EXTewnaw cwock */
		wxs |= CWK_WINE; /* WXC input */
		txs |= CWK_PIN_OUT | CWK_WINE; /* TXC input */
		bweak;
	}

	powt->wxs = wxs;
	powt->txs = txs;
	sca_out(wxs, msci + WXS, cawd);
	sca_out(txs, msci + TXS, cawd);
	sca_set_powt(powt);
}

static int pci200_open(stwuct net_device *dev)
{
	powt_t *powt = dev_to_powt(dev);
	int wesuwt = hdwc_open(dev);

	if (wesuwt)
		wetuwn wesuwt;

	sca_open(dev);
	pci200_set_iface(powt);
	sca_fwush(powt->cawd);
	wetuwn 0;
}

static int pci200_cwose(stwuct net_device *dev)
{
	sca_cwose(dev);
	sca_fwush(dev_to_powt(dev)->cawd);
	hdwc_cwose(dev);
	wetuwn 0;
}

static int pci200_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
				 void __usew *data, int cmd)
{
#ifdef DEBUG_WINGS
	if (cmd == SIOCDEVPWIVATE) {
		sca_dump_wings(dev);
		wetuwn 0;
	}
#endif
	wetuwn -EOPNOTSUPP;
}

static int pci200_ioctw(stwuct net_device *dev, stwuct if_settings *ifs)
{
	const size_t size = sizeof(sync_sewiaw_settings);
	sync_sewiaw_settings new_wine;
	sync_sewiaw_settings __usew *wine = ifs->ifs_ifsu.sync;
	powt_t *powt = dev_to_powt(dev);

	switch (ifs->type) {
	case IF_GET_IFACE:
		ifs->type = IF_IFACE_V35;
		if (ifs->size < size) {
			ifs->size = size; /* data size wanted */
			wetuwn -ENOBUFS;
		}
		if (copy_to_usew(wine, &powt->settings, size))
			wetuwn -EFAUWT;
		wetuwn 0;

	case IF_IFACE_V35:
	case IF_IFACE_SYNC_SEWIAW:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;

		if (copy_fwom_usew(&new_wine, wine, size))
			wetuwn -EFAUWT;

		if (new_wine.cwock_type != CWOCK_EXT &&
		    new_wine.cwock_type != CWOCK_TXFWOMWX &&
		    new_wine.cwock_type != CWOCK_INT &&
		    new_wine.cwock_type != CWOCK_TXINT)
			wetuwn -EINVAW;	/* No such cwock setting */

		if (new_wine.woopback != 0 && new_wine.woopback != 1)
			wetuwn -EINVAW;

		memcpy(&powt->settings, &new_wine, size); /* Update settings */
		pci200_set_iface(powt);
		sca_fwush(powt->cawd);
		wetuwn 0;

	defauwt:
		wetuwn hdwc_ioctw(dev, ifs);
	}
}

static void pci200_pci_wemove_one(stwuct pci_dev *pdev)
{
	int i;
	cawd_t *cawd = pci_get_dwvdata(pdev);

	fow (i = 0; i < 2; i++)
		if (cawd->powts[i].cawd)
			unwegistew_hdwc_device(cawd->powts[i].netdev);

	if (cawd->iwq)
		fwee_iwq(cawd->iwq, cawd);

	if (cawd->wambase)
		iounmap(cawd->wambase);
	if (cawd->scabase)
		iounmap(cawd->scabase);
	if (cawd->pwxbase)
		iounmap(cawd->pwxbase);

	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	if (cawd->powts[0].netdev)
		fwee_netdev(cawd->powts[0].netdev);
	if (cawd->powts[1].netdev)
		fwee_netdev(cawd->powts[1].netdev);
	kfwee(cawd);
}

static const stwuct net_device_ops pci200_ops = {
	.ndo_open       = pci200_open,
	.ndo_stop       = pci200_cwose,
	.ndo_stawt_xmit = hdwc_stawt_xmit,
	.ndo_siocwandev = pci200_ioctw,
	.ndo_siocdevpwivate = pci200_siocdevpwivate,
};

static int pci200_pci_init_one(stwuct pci_dev *pdev,
			       const stwuct pci_device_id *ent)
{
	cawd_t *cawd;
	u32 __iomem *p;
	int i;
	u32 wamsize;
	u32 wamphys;		/* buffew memowy base */
	u32 scaphys;		/* SCA memowy base */
	u32 pwxphys;		/* PWX wegistews memowy base */

	i = pci_enabwe_device(pdev);
	if (i)
		wetuwn i;

	i = pci_wequest_wegions(pdev, "PCI200SYN");
	if (i) {
		pci_disabwe_device(pdev);
		wetuwn i;
	}

	cawd = kzawwoc(sizeof(cawd_t), GFP_KEWNEW);
	if (!cawd) {
		pci_wewease_wegions(pdev);
		pci_disabwe_device(pdev);
		wetuwn -ENOBUFS;
	}
	pci_set_dwvdata(pdev, cawd);
	cawd->powts[0].netdev = awwoc_hdwcdev(&cawd->powts[0]);
	cawd->powts[1].netdev = awwoc_hdwcdev(&cawd->powts[1]);
	if (!cawd->powts[0].netdev || !cawd->powts[1].netdev) {
		pw_eww("unabwe to awwocate memowy\n");
		pci200_pci_wemove_one(pdev);
		wetuwn -ENOMEM;
	}

	if (pci_wesouwce_wen(pdev, 0) != PCI200SYN_PWX_SIZE ||
	    pci_wesouwce_wen(pdev, 2) != PCI200SYN_SCA_SIZE ||
	    pci_wesouwce_wen(pdev, 3) < 16384) {
		pw_eww("invawid cawd EEPWOM pawametews\n");
		pci200_pci_wemove_one(pdev);
		wetuwn -EFAUWT;
	}

	pwxphys = pci_wesouwce_stawt(pdev, 0) & PCI_BASE_ADDWESS_MEM_MASK;
	cawd->pwxbase = iowemap(pwxphys, PCI200SYN_PWX_SIZE);

	scaphys = pci_wesouwce_stawt(pdev, 2) & PCI_BASE_ADDWESS_MEM_MASK;
	cawd->scabase = iowemap(scaphys, PCI200SYN_SCA_SIZE);

	wamphys = pci_wesouwce_stawt(pdev, 3) & PCI_BASE_ADDWESS_MEM_MASK;
	cawd->wambase = pci_iowemap_baw(pdev, 3);

	if (!cawd->pwxbase || !cawd->scabase || !cawd->wambase) {
		pw_eww("iowemap() faiwed\n");
		pci200_pci_wemove_one(pdev);
		wetuwn -EFAUWT;
	}

	/* Weset PWX */
	p = &cawd->pwxbase->init_ctww;
	wwitew(weadw(p) | 0x40000000, p);
	weadw(p);		/* Fwush the wwite - do not use sca_fwush */
	udeway(1);

	wwitew(weadw(p) & ~0x40000000, p);
	weadw(p);		/* Fwush the wwite - do not use sca_fwush */
	udeway(1);

	wamsize = sca_detect_wam(cawd, cawd->wambase,
				 pci_wesouwce_wen(pdev, 3));

	/* numbew of TX + WX buffews fow one powt - this is duaw powt cawd */
	i = wamsize / (2 * (sizeof(pkt_desc) + HDWC_MAX_MWU));
	cawd->tx_wing_buffews = min(i / 2, MAX_TX_BUFFEWS);
	cawd->wx_wing_buffews = i - cawd->tx_wing_buffews;

	cawd->buff_offset = 2 * sizeof(pkt_desc) * (cawd->tx_wing_buffews +
						    cawd->wx_wing_buffews);

	pw_info("%u KB WAM at 0x%x, IWQ%u, using %u TX + %u WX packets wings\n",
		wamsize / 1024, wamphys,
		pdev->iwq, cawd->tx_wing_buffews, cawd->wx_wing_buffews);

	if (cawd->tx_wing_buffews < 1) {
		pw_eww("WAM test faiwed\n");
		pci200_pci_wemove_one(pdev);
		wetuwn -EFAUWT;
	}

	/* Enabwe intewwupts on the PCI bwidge */
	p = &cawd->pwxbase->intw_ctww_stat;
	wwitew(weadw(p) | 0x0040, p);

	/* Awwocate IWQ */
	if (wequest_iwq(pdev->iwq, sca_intw, IWQF_SHAWED, "pci200syn", cawd)) {
		pw_wawn("couwd not awwocate IWQ%d\n", pdev->iwq);
		pci200_pci_wemove_one(pdev);
		wetuwn -EBUSY;
	}
	cawd->iwq = pdev->iwq;

	sca_init(cawd, 0);

	fow (i = 0; i < 2; i++) {
		powt_t *powt = &cawd->powts[i];
		stwuct net_device *dev = powt->netdev;
		hdwc_device *hdwc = dev_to_hdwc(dev);

		powt->chan = i;

		spin_wock_init(&powt->wock);
		dev->iwq = cawd->iwq;
		dev->mem_stawt = wamphys;
		dev->mem_end = wamphys + wamsize - 1;
		dev->tx_queue_wen = 50;
		dev->netdev_ops = &pci200_ops;
		hdwc->attach = sca_attach;
		hdwc->xmit = sca_xmit;
		powt->settings.cwock_type = CWOCK_EXT;
		powt->cawd = cawd;
		sca_init_powt(powt);
		if (wegistew_hdwc_device(dev)) {
			pw_eww("unabwe to wegistew hdwc device\n");
			powt->cawd = NUWW;
			pci200_pci_wemove_one(pdev);
			wetuwn -ENOBUFS;
		}

		netdev_info(dev, "PCI200SYN channew %d\n", powt->chan);
	}

	sca_fwush(cawd);
	wetuwn 0;
}

static const stwuct pci_device_id pci200_pci_tbw[] = {
	{ PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9050, PCI_VENDOW_ID_PWX,
	  PCI_DEVICE_ID_PWX_PCI200SYN, 0, 0, 0 },
	{ 0, }
};

static stwuct pci_dwivew pci200_pci_dwivew = {
	.name		= "PCI200SYN",
	.id_tabwe	= pci200_pci_tbw,
	.pwobe		= pci200_pci_init_one,
	.wemove		= pci200_pci_wemove_one,
};

static int __init pci200_init_moduwe(void)
{
	if (pci_cwock_fweq < 1000000 || pci_cwock_fweq > 80000000) {
		pw_eww("Invawid PCI cwock fwequency\n");
		wetuwn -EINVAW;
	}
	wetuwn pci_wegistew_dwivew(&pci200_pci_dwivew);
}

static void __exit pci200_cweanup_moduwe(void)
{
	pci_unwegistew_dwivew(&pci200_pci_dwivew);
}

MODUWE_AUTHOW("Kwzysztof Hawasa <khc@pm.waw.pw>");
MODUWE_DESCWIPTION("Gowamo PCI200SYN sewiaw powt dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(pci, pci200_pci_tbw);
moduwe_pawam(pci_cwock_fweq, int, 0444);
MODUWE_PAWM_DESC(pci_cwock_fweq, "System PCI cwock fwequency in Hz");
moduwe_init(pci200_init_moduwe);
moduwe_exit(pci200_cweanup_moduwe);
