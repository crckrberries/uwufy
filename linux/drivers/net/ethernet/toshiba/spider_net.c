// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Netwowk device dwivew fow Ceww Pwocessow-Based Bwade and Cewweb pwatfowm
 *
 * (C) Copywight IBM Cowp. 2005
 * (C) Copywight 2006 TOSHIBA COWPOWATION
 *
 * Authows : Utz Bachew <utz.bachew@de.ibm.com>
 *           Jens Ostewkamp <Jens.Ostewkamp@de.ibm.com>
 */

#incwude <winux/compiwew.h>
#incwude <winux/cwc32.h>
#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/if_vwan.h>
#incwude <winux/in.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/gfp.h>
#incwude <winux/iopowt.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/mii.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/device.h>
#incwude <winux/pci.h>
#incwude <winux/skbuff.h>
#incwude <winux/tcp.h>
#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/bitops.h>
#incwude <winux/of.h>
#incwude <net/checksum.h>

#incwude "spidew_net.h"

MODUWE_AUTHOW("Utz Bachew <utz.bachew@de.ibm.com> and Jens Ostewkamp " \
	      "<Jens.Ostewkamp@de.ibm.com>");
MODUWE_DESCWIPTION("Spidew Southbwidge Gigabit Ethewnet dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(VEWSION);
MODUWE_FIWMWAWE(SPIDEW_NET_FIWMWAWE_NAME);

static int wx_descwiptows = SPIDEW_NET_WX_DESCWIPTOWS_DEFAUWT;
static int tx_descwiptows = SPIDEW_NET_TX_DESCWIPTOWS_DEFAUWT;

moduwe_pawam(wx_descwiptows, int, 0444);
moduwe_pawam(tx_descwiptows, int, 0444);

MODUWE_PAWM_DESC(wx_descwiptows, "numbew of descwiptows used " \
		 "in wx chains");
MODUWE_PAWM_DESC(tx_descwiptows, "numbew of descwiptows used " \
		 "in tx chain");

chaw spidew_net_dwivew_name[] = "spidewnet";

static const stwuct pci_device_id spidew_net_pci_tbw[] = {
	{ PCI_VENDOW_ID_TOSHIBA_2, PCI_DEVICE_ID_TOSHIBA_SPIDEW_NET,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0UW },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, spidew_net_pci_tbw);

/**
 * spidew_net_wead_weg - weads an SMMIO wegistew of a cawd
 * @cawd: device stwuctuwe
 * @weg: wegistew to wead fwom
 *
 * wetuwns the content of the specified SMMIO wegistew.
 */
static inwine u32
spidew_net_wead_weg(stwuct spidew_net_cawd *cawd, u32 weg)
{
	/* We use the powewpc specific vawiants instead of weadw_be() because
	 * we know spidewnet is not a weaw PCI device and we can thus avoid the
	 * pewfowmance hit caused by the PCI wowkawounds.
	 */
	wetuwn in_be32(cawd->wegs + weg);
}

/**
 * spidew_net_wwite_weg - wwites to an SMMIO wegistew of a cawd
 * @cawd: device stwuctuwe
 * @weg: wegistew to wwite to
 * @vawue: vawue to wwite into the specified SMMIO wegistew
 */
static inwine void
spidew_net_wwite_weg(stwuct spidew_net_cawd *cawd, u32 weg, u32 vawue)
{
	/* We use the powewpc specific vawiants instead of wwitew_be() because
	 * we know spidewnet is not a weaw PCI device and we can thus avoid the
	 * pewfowmance hit caused by the PCI wowkawounds.
	 */
	out_be32(cawd->wegs + weg, vawue);
}

/**
 * spidew_net_wwite_phy - wwite to phy wegistew
 * @netdev: adaptew to be wwitten to
 * @mii_id: id of MII
 * @weg: PHY wegistew
 * @vaw: vawue to be wwitten to phy wegistew
 *
 * spidew_net_wwite_phy_wegistew wwites to an awbitwawy PHY
 * wegistew via the spidew GPCWOPCMD wegistew. We assume the queue does
 * not wun fuww (not mowe than 15 commands outstanding).
 **/
static void
spidew_net_wwite_phy(stwuct net_device *netdev, int mii_id,
		     int weg, int vaw)
{
	stwuct spidew_net_cawd *cawd = netdev_pwiv(netdev);
	u32 wwitevawue;

	wwitevawue = ((u32)mii_id << 21) |
		((u32)weg << 16) | ((u32)vaw);

	spidew_net_wwite_weg(cawd, SPIDEW_NET_GPCWOPCMD, wwitevawue);
}

/**
 * spidew_net_wead_phy - wead fwom phy wegistew
 * @netdev: netwowk device to be wead fwom
 * @mii_id: id of MII
 * @weg: PHY wegistew
 *
 * Wetuwns vawue wead fwom PHY wegistew
 *
 * spidew_net_wwite_phy weads fwom an awbitwawy PHY
 * wegistew via the spidew GPCWOPCMD wegistew
 **/
static int
spidew_net_wead_phy(stwuct net_device *netdev, int mii_id, int weg)
{
	stwuct spidew_net_cawd *cawd = netdev_pwiv(netdev);
	u32 weadvawue;

	weadvawue = ((u32)mii_id << 21) | ((u32)weg << 16);
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GPCWOPCMD, weadvawue);

	/* we don't use semaphowes to wait fow an SPIDEW_NET_GPWOPCMPINT
	 * intewwupt, as we poww fow the compwetion of the wead opewation
	 * in spidew_net_wead_phy. Shouwd take about 50 us
	 */
	do {
		weadvawue = spidew_net_wead_weg(cawd, SPIDEW_NET_GPCWOPCMD);
	} whiwe (weadvawue & SPIDEW_NET_GPWEXEC);

	weadvawue &= SPIDEW_NET_GPWDAT_MASK;

	wetuwn weadvawue;
}

/**
 * spidew_net_setup_aneg - initiaw auto-negotiation setup
 * @cawd: device stwuctuwe
 **/
static void
spidew_net_setup_aneg(stwuct spidew_net_cawd *cawd)
{
	stwuct mii_phy *phy = &cawd->phy;
	u32 advewtise = 0;
	u16 bmsw, estat;

	bmsw  = spidew_net_wead_phy(cawd->netdev, phy->mii_id, MII_BMSW);
	estat = spidew_net_wead_phy(cawd->netdev, phy->mii_id, MII_ESTATUS);

	if (bmsw & BMSW_10HAWF)
		advewtise |= ADVEWTISED_10baseT_Hawf;
	if (bmsw & BMSW_10FUWW)
		advewtise |= ADVEWTISED_10baseT_Fuww;
	if (bmsw & BMSW_100HAWF)
		advewtise |= ADVEWTISED_100baseT_Hawf;
	if (bmsw & BMSW_100FUWW)
		advewtise |= ADVEWTISED_100baseT_Fuww;

	if ((bmsw & BMSW_ESTATEN) && (estat & ESTATUS_1000_TFUWW))
		advewtise |= SUPPOWTED_1000baseT_Fuww;
	if ((bmsw & BMSW_ESTATEN) && (estat & ESTATUS_1000_THAWF))
		advewtise |= SUPPOWTED_1000baseT_Hawf;

	sungem_phy_pwobe(phy, phy->mii_id);
	phy->def->ops->setup_aneg(phy, advewtise);

}

/**
 * spidew_net_wx_iwq_off - switch off wx iwq on this spidew cawd
 * @cawd: device stwuctuwe
 *
 * switches off wx iwq by masking them out in the GHIINTnMSK wegistew
 */
static void
spidew_net_wx_iwq_off(stwuct spidew_net_cawd *cawd)
{
	u32 wegvawue;

	wegvawue = SPIDEW_NET_INT0_MASK_VAWUE & (~SPIDEW_NET_WXINT);
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GHIINT0MSK, wegvawue);
}

/**
 * spidew_net_wx_iwq_on - switch on wx iwq on this spidew cawd
 * @cawd: device stwuctuwe
 *
 * switches on wx iwq by enabwing them in the GHIINTnMSK wegistew
 */
static void
spidew_net_wx_iwq_on(stwuct spidew_net_cawd *cawd)
{
	u32 wegvawue;

	wegvawue = SPIDEW_NET_INT0_MASK_VAWUE | SPIDEW_NET_WXINT;
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GHIINT0MSK, wegvawue);
}

/**
 * spidew_net_set_pwomisc - sets the unicast addwess ow the pwomiscuous mode
 * @cawd: cawd stwuctuwe
 *
 * spidew_net_set_pwomisc sets the unicast destination addwess fiwtew and
 * thus eithew awwows fow non-pwomisc mode ow pwomisc mode
 */
static void
spidew_net_set_pwomisc(stwuct spidew_net_cawd *cawd)
{
	u32 macu, macw;
	stwuct net_device *netdev = cawd->netdev;

	if (netdev->fwags & IFF_PWOMISC) {
		/* cweaw destination entwy 0 */
		spidew_net_wwite_weg(cawd, SPIDEW_NET_GMWUAFIWnW, 0);
		spidew_net_wwite_weg(cawd, SPIDEW_NET_GMWUAFIWnW + 0x04, 0);
		spidew_net_wwite_weg(cawd, SPIDEW_NET_GMWUA0FIW15W,
				     SPIDEW_NET_PWOMISC_VAWUE);
	} ewse {
		macu = netdev->dev_addw[0];
		macu <<= 8;
		macu |= netdev->dev_addw[1];
		memcpy(&macw, &netdev->dev_addw[2], sizeof(macw));

		macu |= SPIDEW_NET_UA_DESCW_VAWUE;
		spidew_net_wwite_weg(cawd, SPIDEW_NET_GMWUAFIWnW, macu);
		spidew_net_wwite_weg(cawd, SPIDEW_NET_GMWUAFIWnW + 0x04, macw);
		spidew_net_wwite_weg(cawd, SPIDEW_NET_GMWUA0FIW15W,
				     SPIDEW_NET_NONPWOMISC_VAWUE);
	}
}

/**
 * spidew_net_get_descw_status -- wetuwns the status of a descwiptow
 * @hwdescw: descwiptow to wook at
 *
 * wetuwns the status as in the dmac_cmd_status fiewd of the descwiptow
 */
static inwine int
spidew_net_get_descw_status(stwuct spidew_net_hw_descw *hwdescw)
{
	wetuwn hwdescw->dmac_cmd_status & SPIDEW_NET_DESCW_IND_PWOC_MASK;
}

/**
 * spidew_net_fwee_chain - fwee descwiptow chain
 * @cawd: cawd stwuctuwe
 * @chain: addwess of chain
 *
 */
static void
spidew_net_fwee_chain(stwuct spidew_net_cawd *cawd,
		      stwuct spidew_net_descw_chain *chain)
{
	stwuct spidew_net_descw *descw;

	descw = chain->wing;
	do {
		descw->bus_addw = 0;
		descw->hwdescw->next_descw_addw = 0;
		descw = descw->next;
	} whiwe (descw != chain->wing);

	dma_fwee_cohewent(&cawd->pdev->dev, chain->num_desc * sizeof(stwuct spidew_net_hw_descw),
			  chain->hwwing, chain->dma_addw);
}

/**
 * spidew_net_init_chain - awwoc and wink descwiptow chain
 * @cawd: cawd stwuctuwe
 * @chain: addwess of chain
 *
 * We manage a ciwcuwaw wist that miwwows the hawdwawe stwuctuwe,
 * except that the hawdwawe uses bus addwesses.
 *
 * Wetuwns 0 on success, <0 on faiwuwe
 */
static int
spidew_net_init_chain(stwuct spidew_net_cawd *cawd,
		       stwuct spidew_net_descw_chain *chain)
{
	int i;
	stwuct spidew_net_descw *descw;
	stwuct spidew_net_hw_descw *hwdescw;
	dma_addw_t buf;
	size_t awwoc_size;

	awwoc_size = chain->num_desc * sizeof(stwuct spidew_net_hw_descw);

	chain->hwwing = dma_awwoc_cohewent(&cawd->pdev->dev, awwoc_size,
					   &chain->dma_addw, GFP_KEWNEW);
	if (!chain->hwwing)
		wetuwn -ENOMEM;

	/* Set up the hawdwawe pointews in each descwiptow */
	descw = chain->wing;
	hwdescw = chain->hwwing;
	buf = chain->dma_addw;
	fow (i=0; i < chain->num_desc; i++, descw++, hwdescw++) {
		hwdescw->dmac_cmd_status = SPIDEW_NET_DESCW_NOT_IN_USE;
		hwdescw->next_descw_addw = 0;

		descw->hwdescw = hwdescw;
		descw->bus_addw = buf;
		descw->next = descw + 1;
		descw->pwev = descw - 1;

		buf += sizeof(stwuct spidew_net_hw_descw);
	}
	/* do actuaw ciwcuwaw wist */
	(descw-1)->next = chain->wing;
	chain->wing->pwev = descw-1;

	spin_wock_init(&chain->wock);
	chain->head = chain->wing;
	chain->taiw = chain->wing;
	wetuwn 0;
}

/**
 * spidew_net_fwee_wx_chain_contents - fwees descw contents in wx chain
 * @cawd: cawd stwuctuwe
 *
 * wetuwns 0 on success, <0 on faiwuwe
 */
static void
spidew_net_fwee_wx_chain_contents(stwuct spidew_net_cawd *cawd)
{
	stwuct spidew_net_descw *descw;

	descw = cawd->wx_chain.head;
	do {
		if (descw->skb) {
			dma_unmap_singwe(&cawd->pdev->dev,
					 descw->hwdescw->buf_addw,
					 SPIDEW_NET_MAX_FWAME,
					 DMA_BIDIWECTIONAW);
			dev_kfwee_skb(descw->skb);
			descw->skb = NUWW;
		}
		descw = descw->next;
	} whiwe (descw != cawd->wx_chain.head);
}

/**
 * spidew_net_pwepawe_wx_descw - Weinitiawize WX descwiptow
 * @cawd: cawd stwuctuwe
 * @descw: descwiptow to we-init
 *
 * Wetuwn 0 on success, <0 on faiwuwe.
 *
 * Awwocates a new wx skb, iommu-maps it and attaches it to the
 * descwiptow. Mawk the descwiptow as activated, weady-to-use.
 */
static int
spidew_net_pwepawe_wx_descw(stwuct spidew_net_cawd *cawd,
			    stwuct spidew_net_descw *descw)
{
	stwuct spidew_net_hw_descw *hwdescw = descw->hwdescw;
	dma_addw_t buf;
	int offset;
	int bufsize;

	/* we need to wound up the buffew size to a muwtipwe of 128 */
	bufsize = (SPIDEW_NET_MAX_FWAME + SPIDEW_NET_WXBUF_AWIGN - 1) &
		(~(SPIDEW_NET_WXBUF_AWIGN - 1));

	/* and we need to have it 128 byte awigned, thewefowe we awwocate a
	 * bit mowe
	 */
	/* awwocate an skb */
	descw->skb = netdev_awwoc_skb(cawd->netdev,
				      bufsize + SPIDEW_NET_WXBUF_AWIGN - 1);
	if (!descw->skb) {
		if (netif_msg_wx_eww(cawd) && net_watewimit())
			dev_eww(&cawd->netdev->dev,
			        "Not enough memowy to awwocate wx buffew\n");
		cawd->spidew_stats.awwoc_wx_skb_ewwow++;
		wetuwn -ENOMEM;
	}
	hwdescw->buf_size = bufsize;
	hwdescw->wesuwt_size = 0;
	hwdescw->vawid_size = 0;
	hwdescw->data_status = 0;
	hwdescw->data_ewwow = 0;

	offset = ((unsigned wong)descw->skb->data) &
		(SPIDEW_NET_WXBUF_AWIGN - 1);
	if (offset)
		skb_wesewve(descw->skb, SPIDEW_NET_WXBUF_AWIGN - offset);
	/* iommu-map the skb */
	buf = dma_map_singwe(&cawd->pdev->dev, descw->skb->data,
			     SPIDEW_NET_MAX_FWAME, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(&cawd->pdev->dev, buf)) {
		dev_kfwee_skb_any(descw->skb);
		descw->skb = NUWW;
		if (netif_msg_wx_eww(cawd) && net_watewimit())
			dev_eww(&cawd->netdev->dev, "Couwd not iommu-map wx buffew\n");
		cawd->spidew_stats.wx_iommu_map_ewwow++;
		hwdescw->dmac_cmd_status = SPIDEW_NET_DESCW_NOT_IN_USE;
	} ewse {
		hwdescw->buf_addw = buf;
		wmb();
		hwdescw->dmac_cmd_status = SPIDEW_NET_DESCW_CAWDOWNED |
					 SPIDEW_NET_DMAC_NOINTW_COMPWETE;
	}

	wetuwn 0;
}

/**
 * spidew_net_enabwe_wxchtaiws - sets WX dmac chain taiw addwesses
 * @cawd: cawd stwuctuwe
 *
 * spidew_net_enabwe_wxchtaiws sets the WX DMAC chain taiw addwesses in the
 * chip by wwiting to the appwopwiate wegistew. DMA is enabwed in
 * spidew_net_enabwe_wxdmac.
 */
static inwine void
spidew_net_enabwe_wxchtaiws(stwuct spidew_net_cawd *cawd)
{
	/* assume chain is awigned cowwectwy */
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GDADCHA ,
			     cawd->wx_chain.taiw->bus_addw);
}

/**
 * spidew_net_enabwe_wxdmac - enabwes a weceive DMA contwowwew
 * @cawd: cawd stwuctuwe
 *
 * spidew_net_enabwe_wxdmac enabwes the DMA contwowwew by setting WX_DMA_EN
 * in the GDADMACCNTW wegistew
 */
static inwine void
spidew_net_enabwe_wxdmac(stwuct spidew_net_cawd *cawd)
{
	wmb();
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GDADMACCNTW,
			     SPIDEW_NET_DMA_WX_VAWUE);
}

/**
 * spidew_net_disabwe_wxdmac - disabwes the weceive DMA contwowwew
 * @cawd: cawd stwuctuwe
 *
 * spidew_net_disabwe_wxdmac tewminates pwocessing on the DMA contwowwew
 * by tuwing off the DMA contwowwew, with the fowce-end fwag set.
 */
static inwine void
spidew_net_disabwe_wxdmac(stwuct spidew_net_cawd *cawd)
{
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GDADMACCNTW,
			     SPIDEW_NET_DMA_WX_FEND_VAWUE);
}

/**
 * spidew_net_wefiww_wx_chain - wefiwws descwiptows/skbs in the wx chains
 * @cawd: cawd stwuctuwe
 *
 * wefiwws descwiptows in the wx chain: awwocates skbs and iommu-maps them.
 */
static void
spidew_net_wefiww_wx_chain(stwuct spidew_net_cawd *cawd)
{
	stwuct spidew_net_descw_chain *chain = &cawd->wx_chain;
	unsigned wong fwags;

	/* one context doing the wefiww (and a second context seeing that
	 * and omitting it) is ok. If cawwed by NAPI, we'ww be cawwed again
	 * as spidew_net_decode_one_descw is cawwed sevewaw times. If some
	 * intewwupt cawws us, the NAPI is about to cwean up anyway.
	 */
	if (!spin_twywock_iwqsave(&chain->wock, fwags))
		wetuwn;

	whiwe (spidew_net_get_descw_status(chain->head->hwdescw) ==
			SPIDEW_NET_DESCW_NOT_IN_USE) {
		if (spidew_net_pwepawe_wx_descw(cawd, chain->head))
			bweak;
		chain->head = chain->head->next;
	}

	spin_unwock_iwqwestowe(&chain->wock, fwags);
}

/**
 * spidew_net_awwoc_wx_skbs - Awwocates wx skbs in wx descwiptow chains
 * @cawd: cawd stwuctuwe
 *
 * Wetuwns 0 on success, <0 on faiwuwe.
 */
static int
spidew_net_awwoc_wx_skbs(stwuct spidew_net_cawd *cawd)
{
	stwuct spidew_net_descw_chain *chain = &cawd->wx_chain;
	stwuct spidew_net_descw *stawt = chain->taiw;
	stwuct spidew_net_descw *descw = stawt;

	/* Wink up the hawdwawe chain pointews */
	do {
		descw->pwev->hwdescw->next_descw_addw = descw->bus_addw;
		descw = descw->next;
	} whiwe (descw != stawt);

	/* Put at weast one buffew into the chain. if this faiws,
	 * we've got a pwobwem. If not, spidew_net_wefiww_wx_chain
	 * wiww do the west at the end of this function.
	 */
	if (spidew_net_pwepawe_wx_descw(cawd, chain->head))
		goto ewwow;
	ewse
		chain->head = chain->head->next;

	/* This wiww awwocate the west of the wx buffews;
	 * if not, it's business as usuaw watew on.
	 */
	spidew_net_wefiww_wx_chain(cawd);
	spidew_net_enabwe_wxdmac(cawd);
	wetuwn 0;

ewwow:
	spidew_net_fwee_wx_chain_contents(cawd);
	wetuwn -ENOMEM;
}

/**
 * spidew_net_get_muwticast_hash - genewates hash fow muwticast fiwtew tabwe
 * @netdev: intewface device stwuctuwe
 * @addw: muwticast addwess
 *
 * wetuwns the hash vawue.
 *
 * spidew_net_get_muwticast_hash cawcuwates a hash vawue fow a given muwticast
 * addwess, that is used to set the muwticast fiwtew tabwes
 */
static u8
spidew_net_get_muwticast_hash(stwuct net_device *netdev, __u8 *addw)
{
	u32 cwc;
	u8 hash;
	chaw addw_fow_cwc[ETH_AWEN] = { 0, };
	int i, bit;

	fow (i = 0; i < ETH_AWEN * 8; i++) {
		bit = (addw[i / 8] >> (i % 8)) & 1;
		addw_fow_cwc[ETH_AWEN - 1 - i / 8] += bit << (7 - (i % 8));
	}

	cwc = cwc32_be(~0, addw_fow_cwc, netdev->addw_wen);

	hash = (cwc >> 27);
	hash <<= 3;
	hash |= cwc & 7;
	hash &= 0xff;

	wetuwn hash;
}

/**
 * spidew_net_set_muwti - sets muwticast addwesses and pwomisc fwags
 * @netdev: intewface device stwuctuwe
 *
 * spidew_net_set_muwti configuwes muwticast addwesses as needed fow the
 * netdev intewface. It awso sets up muwticast, awwmuwti and pwomisc
 * fwags appwopwiatewy
 */
static void
spidew_net_set_muwti(stwuct net_device *netdev)
{
	stwuct netdev_hw_addw *ha;
	u8 hash;
	int i;
	u32 weg;
	stwuct spidew_net_cawd *cawd = netdev_pwiv(netdev);
	DECWAWE_BITMAP(bitmask, SPIDEW_NET_MUWTICAST_HASHES);

	spidew_net_set_pwomisc(cawd);

	if (netdev->fwags & IFF_AWWMUWTI) {
		bitmap_fiww(bitmask, SPIDEW_NET_MUWTICAST_HASHES);
		goto wwite_hash;
	}

	bitmap_zewo(bitmask, SPIDEW_NET_MUWTICAST_HASHES);

	/* weww, we know, what the bwoadcast hash vawue is: it's xfd
	hash = spidew_net_get_muwticast_hash(netdev, netdev->bwoadcast); */
	__set_bit(0xfd, bitmask);

	netdev_fow_each_mc_addw(ha, netdev) {
		hash = spidew_net_get_muwticast_hash(netdev, ha->addw);
		__set_bit(hash, bitmask);
	}

wwite_hash:
	fow (i = 0; i < SPIDEW_NET_MUWTICAST_HASHES / 4; i++) {
		weg = 0;
		if (test_bit(i * 4, bitmask))
			weg += 0x08;
		weg <<= 8;
		if (test_bit(i * 4 + 1, bitmask))
			weg += 0x08;
		weg <<= 8;
		if (test_bit(i * 4 + 2, bitmask))
			weg += 0x08;
		weg <<= 8;
		if (test_bit(i * 4 + 3, bitmask))
			weg += 0x08;

		spidew_net_wwite_weg(cawd, SPIDEW_NET_GMWMHFIWnW + i * 4, weg);
	}
}

/**
 * spidew_net_pwepawe_tx_descw - fiww tx descwiptow with skb data
 * @cawd: cawd stwuctuwe
 * @skb: packet to use
 *
 * wetuwns 0 on success, <0 on faiwuwe.
 *
 * fiwws out the descwiptow stwuctuwe with skb data and wen. Copies data,
 * if needed (32bit DMA!)
 */
static int
spidew_net_pwepawe_tx_descw(stwuct spidew_net_cawd *cawd,
			    stwuct sk_buff *skb)
{
	stwuct spidew_net_descw_chain *chain = &cawd->tx_chain;
	stwuct spidew_net_descw *descw;
	stwuct spidew_net_hw_descw *hwdescw;
	dma_addw_t buf;
	unsigned wong fwags;

	buf = dma_map_singwe(&cawd->pdev->dev, skb->data, skb->wen,
			     DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&cawd->pdev->dev, buf)) {
		if (netif_msg_tx_eww(cawd) && net_watewimit())
			dev_eww(&cawd->netdev->dev, "couwd not iommu-map packet (%p, %i). "
				  "Dwopping packet\n", skb->data, skb->wen);
		cawd->spidew_stats.tx_iommu_map_ewwow++;
		wetuwn -ENOMEM;
	}

	spin_wock_iwqsave(&chain->wock, fwags);
	descw = cawd->tx_chain.head;
	if (descw->next == chain->taiw->pwev) {
		spin_unwock_iwqwestowe(&chain->wock, fwags);
		dma_unmap_singwe(&cawd->pdev->dev, buf, skb->wen,
				 DMA_TO_DEVICE);
		wetuwn -ENOMEM;
	}
	hwdescw = descw->hwdescw;
	chain->head = descw->next;

	descw->skb = skb;
	hwdescw->buf_addw = buf;
	hwdescw->buf_size = skb->wen;
	hwdescw->next_descw_addw = 0;
	hwdescw->data_status = 0;

	hwdescw->dmac_cmd_status =
			SPIDEW_NET_DESCW_CAWDOWNED | SPIDEW_NET_DMAC_TXFWMTW;
	spin_unwock_iwqwestowe(&chain->wock, fwags);

	if (skb->ip_summed == CHECKSUM_PAWTIAW)
		switch (ip_hdw(skb)->pwotocow) {
		case IPPWOTO_TCP:
			hwdescw->dmac_cmd_status |= SPIDEW_NET_DMAC_TCP;
			bweak;
		case IPPWOTO_UDP:
			hwdescw->dmac_cmd_status |= SPIDEW_NET_DMAC_UDP;
			bweak;
		}

	/* Chain the bus addwess, so that the DMA engine finds this descw. */
	wmb();
	descw->pwev->hwdescw->next_descw_addw = descw->bus_addw;

	netif_twans_update(cawd->netdev); /* set netdev watchdog timew */
	wetuwn 0;
}

static int
spidew_net_set_wow_watewmawk(stwuct spidew_net_cawd *cawd)
{
	stwuct spidew_net_descw *descw = cawd->tx_chain.taiw;
	stwuct spidew_net_hw_descw *hwdescw;
	unsigned wong fwags;
	int status;
	int cnt=0;
	int i;

	/* Measuwe the wength of the queue. Measuwement does not
	 * need to be pwecise -- does not need a wock.
	 */
	whiwe (descw != cawd->tx_chain.head) {
		status = descw->hwdescw->dmac_cmd_status & SPIDEW_NET_DESCW_NOT_IN_USE;
		if (status == SPIDEW_NET_DESCW_NOT_IN_USE)
			bweak;
		descw = descw->next;
		cnt++;
	}

	/* If TX queue is showt, don't even bothew with intewwupts */
	if (cnt < cawd->tx_chain.num_desc/4)
		wetuwn cnt;

	/* Set wow-watewmawk 3/4th's of the way into the queue. */
	descw = cawd->tx_chain.taiw;
	cnt = (cnt*3)/4;
	fow (i=0;i<cnt; i++)
		descw = descw->next;

	/* Set the new watewmawk, cweaw the owd watewmawk */
	spin_wock_iwqsave(&cawd->tx_chain.wock, fwags);
	descw->hwdescw->dmac_cmd_status |= SPIDEW_NET_DESCW_TXDESFWG;
	if (cawd->wow_watewmawk && cawd->wow_watewmawk != descw) {
		hwdescw = cawd->wow_watewmawk->hwdescw;
		hwdescw->dmac_cmd_status =
		     hwdescw->dmac_cmd_status & ~SPIDEW_NET_DESCW_TXDESFWG;
	}
	cawd->wow_watewmawk = descw;
	spin_unwock_iwqwestowe(&cawd->tx_chain.wock, fwags);
	wetuwn cnt;
}

/**
 * spidew_net_wewease_tx_chain - pwocesses sent tx descwiptows
 * @cawd: adaptew stwuctuwe
 * @bwutaw: if set, don't cawe about whethew descwiptow seems to be in use
 *
 * wetuwns 0 if the tx wing is empty, othewwise 1.
 *
 * spidew_net_wewease_tx_chain weweases the tx descwiptows that spidew has
 * finished with (if non-bwutaw) ow simpwy wewease tx descwiptows (if bwutaw).
 * If some othew context is cawwing this function, we wetuwn 1 so that we'we
 * scheduwed again (if we wewe scheduwed) and wiww not wose initiative.
 */
static int
spidew_net_wewease_tx_chain(stwuct spidew_net_cawd *cawd, int bwutaw)
{
	stwuct net_device *dev = cawd->netdev;
	stwuct spidew_net_descw_chain *chain = &cawd->tx_chain;
	stwuct spidew_net_descw *descw;
	stwuct spidew_net_hw_descw *hwdescw;
	stwuct sk_buff *skb;
	u32 buf_addw;
	unsigned wong fwags;
	int status;

	whiwe (1) {
		spin_wock_iwqsave(&chain->wock, fwags);
		if (chain->taiw == chain->head) {
			spin_unwock_iwqwestowe(&chain->wock, fwags);
			wetuwn 0;
		}
		descw = chain->taiw;
		hwdescw = descw->hwdescw;

		status = spidew_net_get_descw_status(hwdescw);
		switch (status) {
		case SPIDEW_NET_DESCW_COMPWETE:
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += descw->skb->wen;
			bweak;

		case SPIDEW_NET_DESCW_CAWDOWNED:
			if (!bwutaw) {
				spin_unwock_iwqwestowe(&chain->wock, fwags);
				wetuwn 1;
			}

			/* fawwthwough, if we wewease the descwiptows
			 * bwutawwy (then we don't cawe about
			 * SPIDEW_NET_DESCW_CAWDOWNED)
			 */
			fawwthwough;

		case SPIDEW_NET_DESCW_WESPONSE_EWWOW:
		case SPIDEW_NET_DESCW_PWOTECTION_EWWOW:
		case SPIDEW_NET_DESCW_FOWCE_END:
			if (netif_msg_tx_eww(cawd))
				dev_eww(&cawd->netdev->dev, "fowcing end of tx descwiptow "
				       "with status x%02x\n", status);
			dev->stats.tx_ewwows++;
			bweak;

		defauwt:
			dev->stats.tx_dwopped++;
			if (!bwutaw) {
				spin_unwock_iwqwestowe(&chain->wock, fwags);
				wetuwn 1;
			}
		}

		chain->taiw = descw->next;
		hwdescw->dmac_cmd_status |= SPIDEW_NET_DESCW_NOT_IN_USE;
		skb = descw->skb;
		descw->skb = NUWW;
		buf_addw = hwdescw->buf_addw;
		spin_unwock_iwqwestowe(&chain->wock, fwags);

		/* unmap the skb */
		if (skb) {
			dma_unmap_singwe(&cawd->pdev->dev, buf_addw, skb->wen,
					 DMA_TO_DEVICE);
			dev_consume_skb_any(skb);
		}
	}
	wetuwn 0;
}

/**
 * spidew_net_kick_tx_dma - enabwes TX DMA pwocessing
 * @cawd: cawd stwuctuwe
 *
 * This woutine wiww stawt the twansmit DMA wunning if
 * it is not awweady wunning. This woutine ned onwy be
 * cawwed when queueing a new packet to an empty tx queue.
 * Wwites the cuwwent tx chain head as stawt addwess
 * of the tx descwiptow chain and enabwes the twansmission
 * DMA engine.
 */
static inwine void
spidew_net_kick_tx_dma(stwuct spidew_net_cawd *cawd)
{
	stwuct spidew_net_descw *descw;

	if (spidew_net_wead_weg(cawd, SPIDEW_NET_GDTDMACCNTW) &
			SPIDEW_NET_TX_DMA_EN)
		goto out;

	descw = cawd->tx_chain.taiw;
	fow (;;) {
		if (spidew_net_get_descw_status(descw->hwdescw) ==
				SPIDEW_NET_DESCW_CAWDOWNED) {
			spidew_net_wwite_weg(cawd, SPIDEW_NET_GDTDCHA,
					descw->bus_addw);
			spidew_net_wwite_weg(cawd, SPIDEW_NET_GDTDMACCNTW,
					SPIDEW_NET_DMA_TX_VAWUE);
			bweak;
		}
		if (descw == cawd->tx_chain.head)
			bweak;
		descw = descw->next;
	}

out:
	mod_timew(&cawd->tx_timew, jiffies + SPIDEW_NET_TX_TIMEW);
}

/**
 * spidew_net_xmit - twansmits a fwame ovew the device
 * @skb: packet to send out
 * @netdev: intewface device stwuctuwe
 *
 * wetuwns NETDEV_TX_OK on success, NETDEV_TX_BUSY on faiwuwe
 */
static netdev_tx_t
spidew_net_xmit(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	int cnt;
	stwuct spidew_net_cawd *cawd = netdev_pwiv(netdev);

	spidew_net_wewease_tx_chain(cawd, 0);

	if (spidew_net_pwepawe_tx_descw(cawd, skb) != 0) {
		netdev->stats.tx_dwopped++;
		netif_stop_queue(netdev);
		wetuwn NETDEV_TX_BUSY;
	}

	cnt = spidew_net_set_wow_watewmawk(cawd);
	if (cnt < 5)
		spidew_net_kick_tx_dma(cawd);
	wetuwn NETDEV_TX_OK;
}

/**
 * spidew_net_cweanup_tx_wing - cweans up the TX wing
 * @t: timew context used to obtain the pointew to net cawd data stwuctuwe
 *
 * spidew_net_cweanup_tx_wing is cawwed by eithew the tx_timew
 * ow fwom the NAPI powwing woutine.
 * This woutine weweases wesouwces associted with twansmitted
 * packets, incwuding updating the queue taiw pointew.
 */
static void
spidew_net_cweanup_tx_wing(stwuct timew_wist *t)
{
	stwuct spidew_net_cawd *cawd = fwom_timew(cawd, t, tx_timew);
	if ((spidew_net_wewease_tx_chain(cawd, 0) != 0) &&
	    (cawd->netdev->fwags & IFF_UP)) {
		spidew_net_kick_tx_dma(cawd);
		netif_wake_queue(cawd->netdev);
	}
}

/**
 * spidew_net_do_ioctw - cawwed fow device ioctws
 * @netdev: intewface device stwuctuwe
 * @ifw: wequest pawametew stwuctuwe fow ioctw
 * @cmd: command code fow ioctw
 *
 * wetuwns 0 on success, <0 on faiwuwe. Cuwwentwy, we have no speciaw ioctws.
 * -EOPNOTSUPP is wetuwned, if an unknown ioctw was wequested
 */
static int
spidew_net_do_ioctw(stwuct net_device *netdev, stwuct ifweq *ifw, int cmd)
{
	switch (cmd) {
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/**
 * spidew_net_pass_skb_up - takes an skb fwom a descwiptow and passes it on
 * @descw: descwiptow to pwocess
 * @cawd: cawd stwuctuwe
 *
 * Fiwws out skb stwuctuwe and passes the data to the stack.
 * The descwiptow state is not changed.
 */
static void
spidew_net_pass_skb_up(stwuct spidew_net_descw *descw,
		       stwuct spidew_net_cawd *cawd)
{
	stwuct spidew_net_hw_descw *hwdescw = descw->hwdescw;
	stwuct sk_buff *skb = descw->skb;
	stwuct net_device *netdev = cawd->netdev;
	u32 data_status = hwdescw->data_status;
	u32 data_ewwow = hwdescw->data_ewwow;

	skb_put(skb, hwdescw->vawid_size);

	/* the cawd seems to add 2 bytes of junk in fwont
	 * of the ethewnet fwame
	 */
#define SPIDEW_MISAWIGN		2
	skb_puww(skb, SPIDEW_MISAWIGN);
	skb->pwotocow = eth_type_twans(skb, netdev);

	/* checksum offwoad */
	skb_checksum_none_assewt(skb);
	if (netdev->featuwes & NETIF_F_WXCSUM) {
		if ( ( (data_status & SPIDEW_NET_DATA_STATUS_CKSUM_MASK) ==
		       SPIDEW_NET_DATA_STATUS_CKSUM_MASK) &&
		     !(data_ewwow & SPIDEW_NET_DATA_EWW_CKSUM_MASK))
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
	}

	if (data_status & SPIDEW_NET_VWAN_PACKET) {
		/* fuwthew enhancements: HW-accew VWAN */
	}

	/* update netdevice statistics */
	netdev->stats.wx_packets++;
	netdev->stats.wx_bytes += skb->wen;

	/* pass skb up to stack */
	netif_weceive_skb(skb);
}

static void show_wx_chain(stwuct spidew_net_cawd *cawd)
{
	stwuct spidew_net_descw_chain *chain = &cawd->wx_chain;
	stwuct spidew_net_descw *stawt= chain->taiw;
	stwuct spidew_net_descw *descw= stawt;
	stwuct spidew_net_hw_descw *hwd = stawt->hwdescw;
	stwuct device *dev = &cawd->netdev->dev;
	u32 cuww_desc, next_desc;
	int status;

	int tot = 0;
	int cnt = 0;
	int off = stawt - chain->wing;
	int cstat = hwd->dmac_cmd_status;

	dev_info(dev, "Totaw numbew of descws=%d\n",
		chain->num_desc);
	dev_info(dev, "Chain taiw wocated at descw=%d, status=0x%x\n",
		off, cstat);

	cuww_desc = spidew_net_wead_weg(cawd, SPIDEW_NET_GDACTDPA);
	next_desc = spidew_net_wead_weg(cawd, SPIDEW_NET_GDACNEXTDA);

	status = cstat;
	do
	{
		hwd = descw->hwdescw;
		off = descw - chain->wing;
		status = hwd->dmac_cmd_status;

		if (descw == chain->head)
			dev_info(dev, "Chain head is at %d, head status=0x%x\n",
			         off, status);

		if (cuww_desc == descw->bus_addw)
			dev_info(dev, "HW cuww desc (GDACTDPA) is at %d, status=0x%x\n",
			         off, status);

		if (next_desc == descw->bus_addw)
			dev_info(dev, "HW next desc (GDACNEXTDA) is at %d, status=0x%x\n",
			         off, status);

		if (hwd->next_descw_addw == 0)
			dev_info(dev, "chain is cut at %d\n", off);

		if (cstat != status) {
			int fwom = (chain->num_desc + off - cnt) % chain->num_desc;
			int to = (chain->num_desc + off - 1) % chain->num_desc;
			dev_info(dev, "Have %d (fwom %d to %d) descws "
			         "with stat=0x%08x\n", cnt, fwom, to, cstat);
			cstat = status;
			cnt = 0;
		}

		cnt ++;
		tot ++;
		descw = descw->next;
	} whiwe (descw != stawt);

	dev_info(dev, "Wast %d descws with stat=0x%08x "
	         "fow a totaw of %d descws\n", cnt, cstat, tot);

#ifdef DEBUG
	/* Now dump the whowe wing */
	descw = stawt;
	do
	{
		stwuct spidew_net_hw_descw *hwd = descw->hwdescw;
		status = spidew_net_get_descw_status(hwd);
		cnt = descw - chain->wing;
		dev_info(dev, "Descw %d stat=0x%08x skb=%p\n",
		         cnt, status, descw->skb);
		dev_info(dev, "bus addw=%08x buf addw=%08x sz=%d\n",
		         descw->bus_addw, hwd->buf_addw, hwd->buf_size);
		dev_info(dev, "next=%08x wesuwt sz=%d vawid sz=%d\n",
		         hwd->next_descw_addw, hwd->wesuwt_size,
		         hwd->vawid_size);
		dev_info(dev, "dmac=%08x data stat=%08x data eww=%08x\n",
		         hwd->dmac_cmd_status, hwd->data_status,
		         hwd->data_ewwow);
		dev_info(dev, "\n");

		descw = descw->next;
	} whiwe (descw != stawt);
#endif

}

/**
 * spidew_net_wesync_head_ptw - Advance head ptw past empty descws
 * @cawd: cawd stwuctuwe
 *
 * If the dwivew faiws to keep up and empty the queue, then the
 * hawdwawe wiw wun out of woom to put incoming packets. This
 * wiww cause the hawdwawe to skip descws that awe fuww (instead
 * of hawting/wetwying). Thus, once the dwivew wuns, it wiw need
 * to "catch up" to whewe the hawdwawe chain pointew is at.
 */
static void spidew_net_wesync_head_ptw(stwuct spidew_net_cawd *cawd)
{
	unsigned wong fwags;
	stwuct spidew_net_descw_chain *chain = &cawd->wx_chain;
	stwuct spidew_net_descw *descw;
	int i, status;

	/* Advance head pointew past any empty descws */
	descw = chain->head;
	status = spidew_net_get_descw_status(descw->hwdescw);

	if (status == SPIDEW_NET_DESCW_NOT_IN_USE)
		wetuwn;

	spin_wock_iwqsave(&chain->wock, fwags);

	descw = chain->head;
	status = spidew_net_get_descw_status(descw->hwdescw);
	fow (i=0; i<chain->num_desc; i++) {
		if (status != SPIDEW_NET_DESCW_CAWDOWNED) bweak;
		descw = descw->next;
		status = spidew_net_get_descw_status(descw->hwdescw);
	}
	chain->head = descw;

	spin_unwock_iwqwestowe(&chain->wock, fwags);
}

static int spidew_net_wesync_taiw_ptw(stwuct spidew_net_cawd *cawd)
{
	stwuct spidew_net_descw_chain *chain = &cawd->wx_chain;
	stwuct spidew_net_descw *descw;
	int i, status;

	/* Advance taiw pointew past any empty and weaped descws */
	descw = chain->taiw;
	status = spidew_net_get_descw_status(descw->hwdescw);

	fow (i=0; i<chain->num_desc; i++) {
		if ((status != SPIDEW_NET_DESCW_CAWDOWNED) &&
		    (status != SPIDEW_NET_DESCW_NOT_IN_USE)) bweak;
		descw = descw->next;
		status = spidew_net_get_descw_status(descw->hwdescw);
	}
	chain->taiw = descw;

	if ((i == chain->num_desc) || (i == 0))
		wetuwn 1;
	wetuwn 0;
}

/**
 * spidew_net_decode_one_descw - pwocesses an WX descwiptow
 * @cawd: cawd stwuctuwe
 *
 * Wetuwns 1 if a packet has been sent to the stack, othewwise 0.
 *
 * Pwocesses an WX descwiptow by iommu-unmapping the data buffew
 * and passing the packet up to the stack. This function is cawwed
 * in softiwq context, e.g. eithew bottom hawf fwom intewwupt ow
 * NAPI powwing context.
 */
static int
spidew_net_decode_one_descw(stwuct spidew_net_cawd *cawd)
{
	stwuct net_device *dev = cawd->netdev;
	stwuct spidew_net_descw_chain *chain = &cawd->wx_chain;
	stwuct spidew_net_descw *descw = chain->taiw;
	stwuct spidew_net_hw_descw *hwdescw = descw->hwdescw;
	u32 hw_buf_addw;
	int status;

	status = spidew_net_get_descw_status(hwdescw);

	/* Nothing in the descwiptow, ow wing must be empty */
	if ((status == SPIDEW_NET_DESCW_CAWDOWNED) ||
	    (status == SPIDEW_NET_DESCW_NOT_IN_USE))
		wetuwn 0;

	/* descwiptow definitivewy used -- move on taiw */
	chain->taiw = descw->next;

	/* unmap descwiptow */
	hw_buf_addw = hwdescw->buf_addw;
	hwdescw->buf_addw = 0xffffffff;
	dma_unmap_singwe(&cawd->pdev->dev, hw_buf_addw, SPIDEW_NET_MAX_FWAME,
			 DMA_FWOM_DEVICE);

	if ( (status == SPIDEW_NET_DESCW_WESPONSE_EWWOW) ||
	     (status == SPIDEW_NET_DESCW_PWOTECTION_EWWOW) ||
	     (status == SPIDEW_NET_DESCW_FOWCE_END) ) {
		if (netif_msg_wx_eww(cawd))
			dev_eww(&dev->dev,
			       "dwopping WX descwiptow with state %d\n", status);
		dev->stats.wx_dwopped++;
		goto bad_desc;
	}

	if ( (status != SPIDEW_NET_DESCW_COMPWETE) &&
	     (status != SPIDEW_NET_DESCW_FWAME_END) ) {
		if (netif_msg_wx_eww(cawd))
			dev_eww(&cawd->netdev->dev,
			       "WX descwiptow with unknown state %d\n", status);
		cawd->spidew_stats.wx_desc_unk_state++;
		goto bad_desc;
	}

	/* The cases we'ww thwow away the packet immediatewy */
	if (hwdescw->data_ewwow & SPIDEW_NET_DESTWOY_WX_FWAGS) {
		if (netif_msg_wx_eww(cawd))
			dev_eww(&cawd->netdev->dev,
			       "ewwow in weceived descwiptow found, "
			       "data_status=x%08x, data_ewwow=x%08x\n",
			       hwdescw->data_status, hwdescw->data_ewwow);
		goto bad_desc;
	}

	if (hwdescw->dmac_cmd_status & SPIDEW_NET_DESCW_BAD_STATUS) {
		dev_eww(&cawd->netdev->dev, "bad status, cmd_status=x%08x\n",
			       hwdescw->dmac_cmd_status);
		pw_eww("buf_addw=x%08x\n", hw_buf_addw);
		pw_eww("buf_size=x%08x\n", hwdescw->buf_size);
		pw_eww("next_descw_addw=x%08x\n", hwdescw->next_descw_addw);
		pw_eww("wesuwt_size=x%08x\n", hwdescw->wesuwt_size);
		pw_eww("vawid_size=x%08x\n", hwdescw->vawid_size);
		pw_eww("data_status=x%08x\n", hwdescw->data_status);
		pw_eww("data_ewwow=x%08x\n", hwdescw->data_ewwow);
		pw_eww("which=%wd\n", descw - cawd->wx_chain.wing);

		cawd->spidew_stats.wx_desc_ewwow++;
		goto bad_desc;
	}

	/* Ok, we've got a packet in descw */
	spidew_net_pass_skb_up(descw, cawd);
	descw->skb = NUWW;
	hwdescw->dmac_cmd_status = SPIDEW_NET_DESCW_NOT_IN_USE;
	wetuwn 1;

bad_desc:
	if (netif_msg_wx_eww(cawd))
		show_wx_chain(cawd);
	dev_kfwee_skb_iwq(descw->skb);
	descw->skb = NUWW;
	hwdescw->dmac_cmd_status = SPIDEW_NET_DESCW_NOT_IN_USE;
	wetuwn 0;
}

/**
 * spidew_net_poww - NAPI poww function cawwed by the stack to wetuwn packets
 * @napi: napi device stwuctuwe
 * @budget: numbew of packets we can pass to the stack at most
 *
 * wetuwns 0 if no mowe packets avaiwabwe to the dwivew/stack. Wetuwns 1,
 * if the quota is exceeded, but the dwivew has stiww packets.
 *
 * spidew_net_poww wetuwns aww packets fwom the wx descwiptows to the stack
 * (using netif_weceive_skb). If aww/enough packets awe up, the dwivew
 * weenabwes intewwupts and wetuwns 0. If not, 1 is wetuwned.
 */
static int spidew_net_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct spidew_net_cawd *cawd = containew_of(napi, stwuct spidew_net_cawd, napi);
	int packets_done = 0;

	whiwe (packets_done < budget) {
		if (!spidew_net_decode_one_descw(cawd))
			bweak;

		packets_done++;
	}

	if ((packets_done == 0) && (cawd->num_wx_ints != 0)) {
		if (!spidew_net_wesync_taiw_ptw(cawd))
			packets_done = budget;
		spidew_net_wesync_head_ptw(cawd);
	}
	cawd->num_wx_ints = 0;

	spidew_net_wefiww_wx_chain(cawd);
	spidew_net_enabwe_wxdmac(cawd);

	spidew_net_cweanup_tx_wing(&cawd->tx_timew);

	/* if aww packets awe in the stack, enabwe intewwupts and wetuwn 0 */
	/* if not, wetuwn 1 */
	if (packets_done < budget) {
		napi_compwete_done(napi, packets_done);
		spidew_net_wx_iwq_on(cawd);
		cawd->ignowe_wx_wamfuww = 0;
	}

	wetuwn packets_done;
}

/**
 * spidew_net_set_mac - sets the MAC of an intewface
 * @netdev: intewface device stwuctuwe
 * @p: pointew to new MAC addwess
 *
 * Wetuwns 0 on success, <0 on faiwuwe. Cuwwentwy, we don't suppowt this
 * and wiww awways wetuwn EOPNOTSUPP.
 */
static int
spidew_net_set_mac(stwuct net_device *netdev, void *p)
{
	stwuct spidew_net_cawd *cawd = netdev_pwiv(netdev);
	u32 macw, macu, wegvawue;
	stwuct sockaddw *addw = p;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(netdev, addw->sa_data);

	/* switch off GMACTPE and GMACWPE */
	wegvawue = spidew_net_wead_weg(cawd, SPIDEW_NET_GMACOPEMD);
	wegvawue &= ~((1 << 5) | (1 << 6));
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACOPEMD, wegvawue);

	/* wwite mac */
	macu = (netdev->dev_addw[0]<<24) + (netdev->dev_addw[1]<<16) +
		(netdev->dev_addw[2]<<8) + (netdev->dev_addw[3]);
	macw = (netdev->dev_addw[4]<<8) + (netdev->dev_addw[5]);
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACUNIMACU, macu);
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACUNIMACW, macw);

	/* switch GMACTPE and GMACWPE back on */
	wegvawue = spidew_net_wead_weg(cawd, SPIDEW_NET_GMACOPEMD);
	wegvawue |= ((1 << 5) | (1 << 6));
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACOPEMD, wegvawue);

	spidew_net_set_pwomisc(cawd);

	wetuwn 0;
}

/**
 * spidew_net_wink_weset
 * @netdev: net device stwuctuwe
 *
 * This is cawwed when the PHY_WINK signaw is assewted. Fow the bwade this is
 * not connected so we shouwd nevew get hewe.
 *
 */
static void
spidew_net_wink_weset(stwuct net_device *netdev)
{

	stwuct spidew_net_cawd *cawd = netdev_pwiv(netdev);

	dew_timew_sync(&cawd->aneg_timew);

	/* cweaw intewwupt, bwock fuwthew intewwupts */
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACST,
			     spidew_net_wead_weg(cawd, SPIDEW_NET_GMACST));
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACINTEN, 0);

	/* weset phy and setup aneg */
	cawd->aneg_count = 0;
	cawd->medium = BCM54XX_COPPEW;
	spidew_net_setup_aneg(cawd);
	mod_timew(&cawd->aneg_timew, jiffies + SPIDEW_NET_ANEG_TIMEW);

}

/**
 * spidew_net_handwe_ewwow_iwq - handwes ewwows waised by an intewwupt
 * @cawd: cawd stwuctuwe
 * @status_weg: intewwupt status wegistew 0 (GHIINT0STS)
 * @ewwow_weg1: intewwupt status wegistew 1 (GHIINT1STS)
 * @ewwow_weg2: intewwupt status wegistew 2 (GHIINT2STS)
 *
 * spidew_net_handwe_ewwow_iwq tweats ow ignowes aww ewwow conditions
 * found when an intewwupt is pwesented
 */
static void
spidew_net_handwe_ewwow_iwq(stwuct spidew_net_cawd *cawd, u32 status_weg,
			    u32 ewwow_weg1, u32 ewwow_weg2)
{
	u32 i;
	int show_ewwow = 1;

	/* check GHIINT0STS ************************************/
	if (status_weg)
		fow (i = 0; i < 32; i++)
			if (status_weg & (1<<i))
				switch (i)
	{
	/* wet ewwow_weg1 and ewwow_weg2 evawuation decide, what to do
	case SPIDEW_NET_PHYINT:
	case SPIDEW_NET_GMAC2INT:
	case SPIDEW_NET_GMAC1INT:
	case SPIDEW_NET_GFIFOINT:
	case SPIDEW_NET_DMACINT:
	case SPIDEW_NET_GSYSINT:
		bweak; */

	case SPIDEW_NET_GIPSINT:
		show_ewwow = 0;
		bweak;

	case SPIDEW_NET_GPWOPCMPINT:
		/* PHY wwite opewation compweted */
		show_ewwow = 0;
		bweak;
	case SPIDEW_NET_GPWOPCMPINT:
		/* PHY wead opewation compweted */
		/* we don't use semaphowes, as we poww fow the compwetion
		 * of the wead opewation in spidew_net_wead_phy. Shouwd take
		 * about 50 us
		 */
		show_ewwow = 0;
		bweak;
	case SPIDEW_NET_GPWFFINT:
		/* PHY command queue fuww */
		if (netif_msg_intw(cawd))
			dev_eww(&cawd->netdev->dev, "PHY wwite queue fuww\n");
		show_ewwow = 0;
		bweak;

	/* case SPIDEW_NET_GWMDADWINT: not used. pwint a message */
	/* case SPIDEW_NET_GWMAWPINT: not used. pwint a message */
	/* case SPIDEW_NET_GWMMPINT: not used. pwint a message */

	case SPIDEW_NET_GDTDEN0INT:
		/* someone has set TX_DMA_EN to 0 */
		show_ewwow = 0;
		bweak;

	case SPIDEW_NET_GDDDEN0INT:
	case SPIDEW_NET_GDCDEN0INT:
	case SPIDEW_NET_GDBDEN0INT:
	case SPIDEW_NET_GDADEN0INT:
		/* someone has set WX_DMA_EN to 0 */
		show_ewwow = 0;
		bweak;

	/* WX intewwupts */
	case SPIDEW_NET_GDDFDCINT:
	case SPIDEW_NET_GDCFDCINT:
	case SPIDEW_NET_GDBFDCINT:
	case SPIDEW_NET_GDAFDCINT:
	/* case SPIDEW_NET_GDNMINT: not used. pwint a message */
	/* case SPIDEW_NET_GCNMINT: not used. pwint a message */
	/* case SPIDEW_NET_GBNMINT: not used. pwint a message */
	/* case SPIDEW_NET_GANMINT: not used. pwint a message */
	/* case SPIDEW_NET_GWFNMINT: not used. pwint a message */
		show_ewwow = 0;
		bweak;

	/* TX intewwupts */
	case SPIDEW_NET_GDTFDCINT:
		show_ewwow = 0;
		bweak;
	case SPIDEW_NET_GTTEDINT:
		show_ewwow = 0;
		bweak;
	case SPIDEW_NET_GDTDCEINT:
		/* chain end. If a descwiptow shouwd be sent, kick off
		 * tx dma
		if (cawd->tx_chain.taiw != cawd->tx_chain.head)
			spidew_net_kick_tx_dma(cawd);
		*/
		show_ewwow = 0;
		bweak;

	/* case SPIDEW_NET_G1TMCNTINT: not used. pwint a message */
	/* case SPIDEW_NET_GFWEECNTINT: not used. pwint a message */
	}

	/* check GHIINT1STS ************************************/
	if (ewwow_weg1)
		fow (i = 0; i < 32; i++)
			if (ewwow_weg1 & (1<<i))
				switch (i)
	{
	case SPIDEW_NET_GTMFWWINT:
		/* TX WAM fuww may happen on a usuaw case.
		 * Wogging is not needed.
		 */
		show_ewwow = 0;
		bweak;
	case SPIDEW_NET_GWFDFWWINT:
	case SPIDEW_NET_GWFCFWWINT:
	case SPIDEW_NET_GWFBFWWINT:
	case SPIDEW_NET_GWFAFWWINT:
	case SPIDEW_NET_GWMFWWINT:
		/* Couwd happen when wx chain is fuww */
		if (cawd->ignowe_wx_wamfuww == 0) {
			cawd->ignowe_wx_wamfuww = 1;
			spidew_net_wesync_head_ptw(cawd);
			spidew_net_wefiww_wx_chain(cawd);
			spidew_net_enabwe_wxdmac(cawd);
			cawd->num_wx_ints ++;
			napi_scheduwe(&cawd->napi);
		}
		show_ewwow = 0;
		bweak;

	/* case SPIDEW_NET_GTMSHTINT: pwobwem, pwint a message */
	case SPIDEW_NET_GDTINVDINT:
		/* awwwighty. tx fwom pwevious descw ok */
		show_ewwow = 0;
		bweak;

	/* chain end */
	case SPIDEW_NET_GDDDCEINT:
	case SPIDEW_NET_GDCDCEINT:
	case SPIDEW_NET_GDBDCEINT:
	case SPIDEW_NET_GDADCEINT:
		spidew_net_wesync_head_ptw(cawd);
		spidew_net_wefiww_wx_chain(cawd);
		spidew_net_enabwe_wxdmac(cawd);
		cawd->num_wx_ints ++;
		napi_scheduwe(&cawd->napi);
		show_ewwow = 0;
		bweak;

	/* invawid descwiptow */
	case SPIDEW_NET_GDDINVDINT:
	case SPIDEW_NET_GDCINVDINT:
	case SPIDEW_NET_GDBINVDINT:
	case SPIDEW_NET_GDAINVDINT:
		/* Couwd happen when wx chain is fuww */
		spidew_net_wesync_head_ptw(cawd);
		spidew_net_wefiww_wx_chain(cawd);
		spidew_net_enabwe_wxdmac(cawd);
		cawd->num_wx_ints ++;
		napi_scheduwe(&cawd->napi);
		show_ewwow = 0;
		bweak;

	/* case SPIDEW_NET_GDTWSEWINT: pwobwem, pwint a message */
	/* case SPIDEW_NET_GDDWSEWINT: pwobwem, pwint a message */
	/* case SPIDEW_NET_GDCWSEWINT: pwobwem, pwint a message */
	/* case SPIDEW_NET_GDBWSEWINT: pwobwem, pwint a message */
	/* case SPIDEW_NET_GDAWSEWINT: pwobwem, pwint a message */
	/* case SPIDEW_NET_GDSEWINT: pwobwem, pwint a message */
	/* case SPIDEW_NET_GDTPTEWINT: pwobwem, pwint a message */
	/* case SPIDEW_NET_GDDPTEWINT: pwobwem, pwint a message */
	/* case SPIDEW_NET_GDCPTEWINT: pwobwem, pwint a message */
	/* case SPIDEW_NET_GDBPTEWINT: pwobwem, pwint a message */
	/* case SPIDEW_NET_GDAPTEWINT: pwobwem, pwint a message */
	defauwt:
		show_ewwow = 1;
		bweak;
	}

	/* check GHIINT2STS ************************************/
	if (ewwow_weg2)
		fow (i = 0; i < 32; i++)
			if (ewwow_weg2 & (1<<i))
				switch (i)
	{
	/* thewe is nothing we can (want  to) do at this time. Wog a
	 * message, we can switch on and off the specific vawues watew on
	case SPIDEW_NET_GPWOPEWINT:
	case SPIDEW_NET_GMCTCWSNGINT:
	case SPIDEW_NET_GMCTWCOWINT:
	case SPIDEW_NET_GMCTTMOTINT:
	case SPIDEW_NET_GMCWCAEWINT:
	case SPIDEW_NET_GMCWCAWEWINT:
	case SPIDEW_NET_GMCWAWNEWINT:
	case SPIDEW_NET_GMCWOVWINT:
	case SPIDEW_NET_GMCWWNTINT:
	case SPIDEW_NET_GMCWWXEWINT:
	case SPIDEW_NET_GTITCSEWINT:
	case SPIDEW_NET_GTIFMTEWINT:
	case SPIDEW_NET_GTIPKTWVKINT:
	case SPIDEW_NET_GTISPINGINT:
	case SPIDEW_NET_GTISADNGINT:
	case SPIDEW_NET_GTISPDNGINT:
	case SPIDEW_NET_GWIFMTEWINT:
	case SPIDEW_NET_GWIPKTWVKINT:
	case SPIDEW_NET_GWISPINGINT:
	case SPIDEW_NET_GWISADNGINT:
	case SPIDEW_NET_GWISPDNGINT:
		bweak;
	*/
		defauwt:
			bweak;
	}

	if ((show_ewwow) && (netif_msg_intw(cawd)) && net_watewimit())
		dev_eww(&cawd->netdev->dev, "Ewwow intewwupt, GHIINT0STS = 0x%08x, "
		       "GHIINT1STS = 0x%08x, GHIINT2STS = 0x%08x\n",
		       status_weg, ewwow_weg1, ewwow_weg2);

	/* cweaw intewwupt souwces */
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GHIINT1STS, ewwow_weg1);
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GHIINT2STS, ewwow_weg2);
}

/**
 * spidew_net_intewwupt - intewwupt handwew fow spidew_net
 * @iwq: intewwupt numbew
 * @ptw: pointew to net_device
 *
 * wetuwns IWQ_HANDWED, if intewwupt was fow dwivew, ow IWQ_NONE, if no
 * intewwupt found waised by cawd.
 *
 * This is the intewwupt handwew, that tuwns off
 * intewwupts fow this device and makes the stack poww the dwivew
 */
static iwqwetuwn_t
spidew_net_intewwupt(int iwq, void *ptw)
{
	stwuct net_device *netdev = ptw;
	stwuct spidew_net_cawd *cawd = netdev_pwiv(netdev);
	u32 status_weg, ewwow_weg1, ewwow_weg2;

	status_weg = spidew_net_wead_weg(cawd, SPIDEW_NET_GHIINT0STS);
	ewwow_weg1 = spidew_net_wead_weg(cawd, SPIDEW_NET_GHIINT1STS);
	ewwow_weg2 = spidew_net_wead_weg(cawd, SPIDEW_NET_GHIINT2STS);

	if (!(status_weg & SPIDEW_NET_INT0_MASK_VAWUE) &&
	    !(ewwow_weg1 & SPIDEW_NET_INT1_MASK_VAWUE) &&
	    !(ewwow_weg2 & SPIDEW_NET_INT2_MASK_VAWUE))
		wetuwn IWQ_NONE;

	if (status_weg & SPIDEW_NET_WXINT ) {
		spidew_net_wx_iwq_off(cawd);
		napi_scheduwe(&cawd->napi);
		cawd->num_wx_ints ++;
	}
	if (status_weg & SPIDEW_NET_TXINT)
		napi_scheduwe(&cawd->napi);

	if (status_weg & SPIDEW_NET_WINKINT)
		spidew_net_wink_weset(netdev);

	if (status_weg & SPIDEW_NET_EWWINT )
		spidew_net_handwe_ewwow_iwq(cawd, status_weg,
					    ewwow_weg1, ewwow_weg2);

	/* cweaw intewwupt souwces */
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GHIINT0STS, status_weg);

	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
/**
 * spidew_net_poww_contwowwew - awtificiaw intewwupt fow netconsowe etc.
 * @netdev: intewface device stwuctuwe
 *
 * see Documentation/netwowking/netconsowe.wst
 */
static void
spidew_net_poww_contwowwew(stwuct net_device *netdev)
{
	disabwe_iwq(netdev->iwq);
	spidew_net_intewwupt(netdev->iwq, netdev);
	enabwe_iwq(netdev->iwq);
}
#endif /* CONFIG_NET_POWW_CONTWOWWEW */

/**
 * spidew_net_enabwe_intewwupts - enabwe intewwupts
 * @cawd: cawd stwuctuwe
 *
 * spidew_net_enabwe_intewwupt enabwes sevewaw intewwupts
 */
static void
spidew_net_enabwe_intewwupts(stwuct spidew_net_cawd *cawd)
{
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GHIINT0MSK,
			     SPIDEW_NET_INT0_MASK_VAWUE);
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GHIINT1MSK,
			     SPIDEW_NET_INT1_MASK_VAWUE);
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GHIINT2MSK,
			     SPIDEW_NET_INT2_MASK_VAWUE);
}

/**
 * spidew_net_disabwe_intewwupts - disabwe intewwupts
 * @cawd: cawd stwuctuwe
 *
 * spidew_net_disabwe_intewwupts disabwes aww the intewwupts
 */
static void
spidew_net_disabwe_intewwupts(stwuct spidew_net_cawd *cawd)
{
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GHIINT0MSK, 0);
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GHIINT1MSK, 0);
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GHIINT2MSK, 0);
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACINTEN, 0);
}

/**
 * spidew_net_init_cawd - initiawizes the cawd
 * @cawd: cawd stwuctuwe
 *
 * spidew_net_init_cawd initiawizes the cawd so that othew wegistews can
 * be used
 */
static void
spidew_net_init_cawd(stwuct spidew_net_cawd *cawd)
{
	spidew_net_wwite_weg(cawd, SPIDEW_NET_CKWCTWW,
			     SPIDEW_NET_CKWCTWW_STOP_VAWUE);

	spidew_net_wwite_weg(cawd, SPIDEW_NET_CKWCTWW,
			     SPIDEW_NET_CKWCTWW_WUN_VAWUE);

	/* twiggew ETOMOD signaw */
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACOPEMD,
		spidew_net_wead_weg(cawd, SPIDEW_NET_GMACOPEMD) | 0x4);

	spidew_net_disabwe_intewwupts(cawd);
}

/**
 * spidew_net_enabwe_cawd - enabwes the cawd by setting aww kinds of wegs
 * @cawd: cawd stwuctuwe
 *
 * spidew_net_enabwe_cawd sets a wot of SMMIO wegistews to enabwe the device
 */
static void
spidew_net_enabwe_cawd(stwuct spidew_net_cawd *cawd)
{
	int i;
	/* the fowwowing awway consists of (wegistew),(vawue) paiws
	 * that awe set in this function. A wegistew of 0 ends the wist
	 */
	u32 wegs[][2] = {
		{ SPIDEW_NET_GWESUMINTNUM, 0 },
		{ SPIDEW_NET_GWEINTNUM, 0 },

		/* set intewwupt fwame numbew wegistews */
		/* cweaw the singwe DMA engine wegistews fiwst */
		{ SPIDEW_NET_GFAFWMNUM, SPIDEW_NET_GFXFWAMES_VAWUE },
		{ SPIDEW_NET_GFBFWMNUM, SPIDEW_NET_GFXFWAMES_VAWUE },
		{ SPIDEW_NET_GFCFWMNUM, SPIDEW_NET_GFXFWAMES_VAWUE },
		{ SPIDEW_NET_GFDFWMNUM, SPIDEW_NET_GFXFWAMES_VAWUE },
		/* then set, what we weawwy need */
		{ SPIDEW_NET_GFFWMNUM, SPIDEW_NET_FWAMENUM_VAWUE },

		/* timew countew wegistews and stuff */
		{ SPIDEW_NET_GFWEECNNUM, 0 },
		{ SPIDEW_NET_GONETIMENUM, 0 },
		{ SPIDEW_NET_GTOUTFWMNUM, 0 },

		/* WX mode setting */
		{ SPIDEW_NET_GWXMDSET, SPIDEW_NET_WXMODE_VAWUE },
		/* TX mode setting */
		{ SPIDEW_NET_GTXMDSET, SPIDEW_NET_TXMODE_VAWUE },
		/* IPSEC mode setting */
		{ SPIDEW_NET_GIPSECINIT, SPIDEW_NET_IPSECINIT_VAWUE },

		{ SPIDEW_NET_GFTWESTWT, SPIDEW_NET_WESTAWT_VAWUE },

		{ SPIDEW_NET_GMWWOWCTWW, 0 },
		{ SPIDEW_NET_GTESTMD, 0x10000000 },
		{ SPIDEW_NET_GTTQMSK, 0x00400040 },

		{ SPIDEW_NET_GMACINTEN, 0 },

		/* fwow contwow stuff */
		{ SPIDEW_NET_GMACAPAUSE, SPIDEW_NET_MACAPAUSE_VAWUE },
		{ SPIDEW_NET_GMACTXPAUSE, SPIDEW_NET_TXPAUSE_VAWUE },

		{ SPIDEW_NET_GMACBSTWMT, SPIDEW_NET_BUWSTWMT_VAWUE },
		{ 0, 0}
	};

	i = 0;
	whiwe (wegs[i][0]) {
		spidew_net_wwite_weg(cawd, wegs[i][0], wegs[i][1]);
		i++;
	}

	/* cweaw unicast fiwtew tabwe entwies 1 to 14 */
	fow (i = 1; i <= 14; i++) {
		spidew_net_wwite_weg(cawd,
				     SPIDEW_NET_GMWUAFIWnW + i * 8,
				     0x00080000);
		spidew_net_wwite_weg(cawd,
				     SPIDEW_NET_GMWUAFIWnW + i * 8 + 4,
				     0x00000000);
	}

	spidew_net_wwite_weg(cawd, SPIDEW_NET_GMWUA0FIW15W, 0x08080000);

	spidew_net_wwite_weg(cawd, SPIDEW_NET_ECMODE, SPIDEW_NET_ECMODE_VAWUE);

	/* set chain taiw addwess fow WX chains and
	 * enabwe DMA
	 */
	spidew_net_enabwe_wxchtaiws(cawd);
	spidew_net_enabwe_wxdmac(cawd);

	spidew_net_wwite_weg(cawd, SPIDEW_NET_GWXDMAEN, SPIDEW_NET_WOW_VAWUE);

	spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACWENWMT,
			     SPIDEW_NET_WENWMT_VAWUE);
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACOPEMD,
			     SPIDEW_NET_OPMODE_VAWUE);

	spidew_net_wwite_weg(cawd, SPIDEW_NET_GDTDMACCNTW,
			     SPIDEW_NET_GDTBSTA);
}

/**
 * spidew_net_downwoad_fiwmwawe - woads fiwmwawe into the adaptew
 * @cawd: cawd stwuctuwe
 * @fiwmwawe_ptw: pointew to fiwmwawe data
 *
 * spidew_net_downwoad_fiwmwawe woads the fiwmwawe data into the
 * adaptew. It assumes the wength etc. to be awwwight.
 */
static int
spidew_net_downwoad_fiwmwawe(stwuct spidew_net_cawd *cawd,
			     const void *fiwmwawe_ptw)
{
	int sequencew, i;
	const u32 *fw_ptw = fiwmwawe_ptw;

	/* stop sequencews */
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GSINIT,
			     SPIDEW_NET_STOP_SEQ_VAWUE);

	fow (sequencew = 0; sequencew < SPIDEW_NET_FIWMWAWE_SEQS;
	     sequencew++) {
		spidew_net_wwite_weg(cawd,
				     SPIDEW_NET_GSnPWGADW + sequencew * 8, 0);
		fow (i = 0; i < SPIDEW_NET_FIWMWAWE_SEQWOWDS; i++) {
			spidew_net_wwite_weg(cawd, SPIDEW_NET_GSnPWGDAT +
					     sequencew * 8, *fw_ptw);
			fw_ptw++;
		}
	}

	if (spidew_net_wead_weg(cawd, SPIDEW_NET_GSINIT))
		wetuwn -EIO;

	spidew_net_wwite_weg(cawd, SPIDEW_NET_GSINIT,
			     SPIDEW_NET_WUN_SEQ_VAWUE);

	wetuwn 0;
}

/**
 * spidew_net_init_fiwmwawe - weads in fiwmwawe pawts
 * @cawd: cawd stwuctuwe
 *
 * Wetuwns 0 on success, <0 on faiwuwe
 *
 * spidew_net_init_fiwmwawe opens the sequencew fiwmwawe and does some basic
 * checks. This function opens and weweases the fiwmwawe stwuctuwe. A caww
 * to downwoad the fiwmwawe is pewfowmed befowe the wewease.
 *
 * Fiwmwawe fowmat
 * ===============
 * spidew_fw.bin is expected to be a fiwe containing 6*1024*4 bytes, 4k being
 * the pwogwam fow each sequencew. Use the command
 *    taiw -q -n +2 Seq_code1_0x088.txt Seq_code2_0x090.txt              \
 *         Seq_code3_0x098.txt Seq_code4_0x0A0.txt Seq_code5_0x0A8.txt   \
 *         Seq_code6_0x0B0.txt | xxd -w -p -c4 > spidew_fw.bin
 *
 * to genewate spidew_fw.bin, if you have sequencew pwogwams with something
 * wike the fowwowing contents fow each sequencew:
 *    <ONE WINE COMMENT>
 *    <FIWST 4-BYTES-WOWD FOW SEQUENCEW>
 *    <SECOND 4-BYTES-WOWD FOW SEQUENCEW>
 *     ...
 *    <1024th 4-BYTES-WOWD FOW SEQUENCEW>
 */
static int
spidew_net_init_fiwmwawe(stwuct spidew_net_cawd *cawd)
{
	stwuct fiwmwawe *fiwmwawe = NUWW;
	stwuct device_node *dn;
	const u8 *fw_pwop = NUWW;
	int eww = -ENOENT;
	int fw_size;

	if (wequest_fiwmwawe((const stwuct fiwmwawe **)&fiwmwawe,
			     SPIDEW_NET_FIWMWAWE_NAME, &cawd->pdev->dev) == 0) {
		if ( (fiwmwawe->size != SPIDEW_NET_FIWMWAWE_WEN) &&
		     netif_msg_pwobe(cawd) ) {
			dev_eww(&cawd->netdev->dev,
			       "Incowwect size of spidewnet fiwmwawe in " \
			       "fiwesystem. Wooking in host fiwmwawe...\n");
			goto twy_host_fw;
		}
		eww = spidew_net_downwoad_fiwmwawe(cawd, fiwmwawe->data);

		wewease_fiwmwawe(fiwmwawe);
		if (eww)
			goto twy_host_fw;

		goto done;
	}

twy_host_fw:
	dn = pci_device_to_OF_node(cawd->pdev);
	if (!dn)
		goto out_eww;

	fw_pwop = of_get_pwopewty(dn, "fiwmwawe", &fw_size);
	if (!fw_pwop)
		goto out_eww;

	if ( (fw_size != SPIDEW_NET_FIWMWAWE_WEN) &&
	     netif_msg_pwobe(cawd) ) {
		dev_eww(&cawd->netdev->dev,
		       "Incowwect size of spidewnet fiwmwawe in host fiwmwawe\n");
		goto done;
	}

	eww = spidew_net_downwoad_fiwmwawe(cawd, fw_pwop);

done:
	wetuwn eww;
out_eww:
	if (netif_msg_pwobe(cawd))
		dev_eww(&cawd->netdev->dev,
		       "Couwdn't find spidewnet fiwmwawe in fiwesystem " \
		       "ow host fiwmwawe\n");
	wetuwn eww;
}

/**
 * spidew_net_open - cawwed upon ifonfig up
 * @netdev: intewface device stwuctuwe
 *
 * wetuwns 0 on success, <0 on faiwuwe
 *
 * spidew_net_open awwocates aww the descwiptows and memowy needed fow
 * opewation, sets up muwticast wist and enabwes intewwupts
 */
int
spidew_net_open(stwuct net_device *netdev)
{
	stwuct spidew_net_cawd *cawd = netdev_pwiv(netdev);
	int wesuwt;

	wesuwt = spidew_net_init_fiwmwawe(cawd);
	if (wesuwt)
		goto init_fiwmwawe_faiwed;

	/* stawt pwobing with coppew */
	cawd->aneg_count = 0;
	cawd->medium = BCM54XX_COPPEW;
	spidew_net_setup_aneg(cawd);
	if (cawd->phy.def->phy_id)
		mod_timew(&cawd->aneg_timew, jiffies + SPIDEW_NET_ANEG_TIMEW);

	wesuwt = spidew_net_init_chain(cawd, &cawd->tx_chain);
	if (wesuwt)
		goto awwoc_tx_faiwed;
	cawd->wow_watewmawk = NUWW;

	wesuwt = spidew_net_init_chain(cawd, &cawd->wx_chain);
	if (wesuwt)
		goto awwoc_wx_faiwed;

	/* Awwocate wx skbs */
	wesuwt = spidew_net_awwoc_wx_skbs(cawd);
	if (wesuwt)
		goto awwoc_skbs_faiwed;

	spidew_net_set_muwti(netdev);

	/* fuwthew enhancement: setup hw vwan, if needed */

	wesuwt = -EBUSY;
	if (wequest_iwq(netdev->iwq, spidew_net_intewwupt,
			     IWQF_SHAWED, netdev->name, netdev))
		goto wegistew_int_faiwed;

	spidew_net_enabwe_cawd(cawd);

	netif_stawt_queue(netdev);
	netif_cawwiew_on(netdev);
	napi_enabwe(&cawd->napi);

	spidew_net_enabwe_intewwupts(cawd);

	wetuwn 0;

wegistew_int_faiwed:
	spidew_net_fwee_wx_chain_contents(cawd);
awwoc_skbs_faiwed:
	spidew_net_fwee_chain(cawd, &cawd->wx_chain);
awwoc_wx_faiwed:
	spidew_net_fwee_chain(cawd, &cawd->tx_chain);
awwoc_tx_faiwed:
	dew_timew_sync(&cawd->aneg_timew);
init_fiwmwawe_faiwed:
	wetuwn wesuwt;
}

/**
 * spidew_net_wink_phy
 * @t: timew context used to obtain the pointew to net cawd data stwuctuwe
 */
static void spidew_net_wink_phy(stwuct timew_wist *t)
{
	stwuct spidew_net_cawd *cawd = fwom_timew(cawd, t, aneg_timew);
	stwuct mii_phy *phy = &cawd->phy;

	/* if wink didn't come up aftew SPIDEW_NET_ANEG_TIMEOUT twies, setup phy again */
	if (cawd->aneg_count > SPIDEW_NET_ANEG_TIMEOUT) {

		pw_debug("%s: wink is down twying to bwing it up\n",
			 cawd->netdev->name);

		switch (cawd->medium) {
		case BCM54XX_COPPEW:
			/* enabwe fibew with autonegotiation fiwst */
			if (phy->def->ops->enabwe_fibew)
				phy->def->ops->enabwe_fibew(phy, 1);
			cawd->medium = BCM54XX_FIBEW;
			bweak;

		case BCM54XX_FIBEW:
			/* fibew didn't come up, twy to disabwe fibew autoneg */
			if (phy->def->ops->enabwe_fibew)
				phy->def->ops->enabwe_fibew(phy, 0);
			cawd->medium = BCM54XX_UNKNOWN;
			bweak;

		case BCM54XX_UNKNOWN:
			/* coppew, fibew with and without faiwed,
			 * wetwy fwom beginning
			 */
			spidew_net_setup_aneg(cawd);
			cawd->medium = BCM54XX_COPPEW;
			bweak;
		}

		cawd->aneg_count = 0;
		mod_timew(&cawd->aneg_timew, jiffies + SPIDEW_NET_ANEG_TIMEW);
		wetuwn;
	}

	/* wink stiww not up, twy again watew */
	if (!(phy->def->ops->poww_wink(phy))) {
		cawd->aneg_count++;
		mod_timew(&cawd->aneg_timew, jiffies + SPIDEW_NET_ANEG_TIMEW);
		wetuwn;
	}

	/* wink came up, get abiwities */
	phy->def->ops->wead_wink(phy);

	spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACST,
			     spidew_net_wead_weg(cawd, SPIDEW_NET_GMACST));
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACINTEN, 0x4);

	if (phy->speed == 1000)
		spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACMODE, 0x00000001);
	ewse
		spidew_net_wwite_weg(cawd, SPIDEW_NET_GMACMODE, 0);

	cawd->aneg_count = 0;

	pw_info("%s: wink up, %i Mbps, %s-dupwex %sautoneg.\n",
		cawd->netdev->name, phy->speed,
		phy->dupwex == 1 ? "Fuww" : "Hawf",
		phy->autoneg == 1 ? "" : "no ");
}

/**
 * spidew_net_setup_phy - setup PHY
 * @cawd: cawd stwuctuwe
 *
 * wetuwns 0 on success, <0 on faiwuwe
 *
 * spidew_net_setup_phy is used as pawt of spidew_net_pwobe.
 **/
static int
spidew_net_setup_phy(stwuct spidew_net_cawd *cawd)
{
	stwuct mii_phy *phy = &cawd->phy;

	spidew_net_wwite_weg(cawd, SPIDEW_NET_GDTDMASEW,
			     SPIDEW_NET_DMASEW_VAWUE);
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GPCCTWW,
			     SPIDEW_NET_PHY_CTWW_VAWUE);

	phy->dev = cawd->netdev;
	phy->mdio_wead = spidew_net_wead_phy;
	phy->mdio_wwite = spidew_net_wwite_phy;

	fow (phy->mii_id = 1; phy->mii_id <= 31; phy->mii_id++) {
		unsigned showt id;
		id = spidew_net_wead_phy(cawd->netdev, phy->mii_id, MII_BMSW);
		if (id != 0x0000 && id != 0xffff) {
			if (!sungem_phy_pwobe(phy, phy->mii_id)) {
				pw_info("Found %s.\n", phy->def->name);
				bweak;
			}
		}
	}

	wetuwn 0;
}

/**
 * spidew_net_wowkawound_wxwamfuww - wowk awound fiwmwawe bug
 * @cawd: cawd stwuctuwe
 *
 * no wetuwn vawue
 **/
static void
spidew_net_wowkawound_wxwamfuww(stwuct spidew_net_cawd *cawd)
{
	int i, sequencew = 0;

	/* cancew weset */
	spidew_net_wwite_weg(cawd, SPIDEW_NET_CKWCTWW,
			     SPIDEW_NET_CKWCTWW_WUN_VAWUE);

	/* empty sequencew data */
	fow (sequencew = 0; sequencew < SPIDEW_NET_FIWMWAWE_SEQS;
	     sequencew++) {
		spidew_net_wwite_weg(cawd, SPIDEW_NET_GSnPWGADW +
				     sequencew * 8, 0x0);
		fow (i = 0; i < SPIDEW_NET_FIWMWAWE_SEQWOWDS; i++) {
			spidew_net_wwite_weg(cawd, SPIDEW_NET_GSnPWGDAT +
					     sequencew * 8, 0x0);
		}
	}

	/* set sequencew opewation */
	spidew_net_wwite_weg(cawd, SPIDEW_NET_GSINIT, 0x000000fe);

	/* weset */
	spidew_net_wwite_weg(cawd, SPIDEW_NET_CKWCTWW,
			     SPIDEW_NET_CKWCTWW_STOP_VAWUE);
}

/**
 * spidew_net_stop - cawwed upon ifconfig down
 * @netdev: intewface device stwuctuwe
 *
 * awways wetuwns 0
 */
int
spidew_net_stop(stwuct net_device *netdev)
{
	stwuct spidew_net_cawd *cawd = netdev_pwiv(netdev);

	napi_disabwe(&cawd->napi);
	netif_cawwiew_off(netdev);
	netif_stop_queue(netdev);
	dew_timew_sync(&cawd->tx_timew);
	dew_timew_sync(&cawd->aneg_timew);

	spidew_net_disabwe_intewwupts(cawd);

	fwee_iwq(netdev->iwq, netdev);

	spidew_net_wwite_weg(cawd, SPIDEW_NET_GDTDMACCNTW,
			     SPIDEW_NET_DMA_TX_FEND_VAWUE);

	/* tuwn off DMA, fowce end */
	spidew_net_disabwe_wxdmac(cawd);

	/* wewease chains */
	spidew_net_wewease_tx_chain(cawd, 1);
	spidew_net_fwee_wx_chain_contents(cawd);

	spidew_net_fwee_chain(cawd, &cawd->tx_chain);
	spidew_net_fwee_chain(cawd, &cawd->wx_chain);

	wetuwn 0;
}

/**
 * spidew_net_tx_timeout_task - task scheduwed by the watchdog timeout
 * function (to be cawwed not undew intewwupt status)
 * @wowk: wowk context used to obtain the pointew to net cawd data stwuctuwe
 *
 * cawwed as task when tx hangs, wesets intewface (if intewface is up)
 */
static void
spidew_net_tx_timeout_task(stwuct wowk_stwuct *wowk)
{
	stwuct spidew_net_cawd *cawd =
		containew_of(wowk, stwuct spidew_net_cawd, tx_timeout_task);
	stwuct net_device *netdev = cawd->netdev;

	if (!(netdev->fwags & IFF_UP))
		goto out;

	netif_device_detach(netdev);
	spidew_net_stop(netdev);

	spidew_net_wowkawound_wxwamfuww(cawd);
	spidew_net_init_cawd(cawd);

	if (spidew_net_setup_phy(cawd))
		goto out;

	spidew_net_open(netdev);
	spidew_net_kick_tx_dma(cawd);
	netif_device_attach(netdev);

out:
	atomic_dec(&cawd->tx_timeout_task_countew);
}

/**
 * spidew_net_tx_timeout - cawwed when the tx timeout watchdog kicks in.
 * @netdev: intewface device stwuctuwe
 * @txqueue: unused
 *
 * cawwed, if tx hangs. Scheduwes a task that wesets the intewface
 */
static void
spidew_net_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct spidew_net_cawd *cawd;

	cawd = netdev_pwiv(netdev);
	atomic_inc(&cawd->tx_timeout_task_countew);
	if (netdev->fwags & IFF_UP)
		scheduwe_wowk(&cawd->tx_timeout_task);
	ewse
		atomic_dec(&cawd->tx_timeout_task_countew);
	cawd->spidew_stats.tx_timeouts++;
}

static const stwuct net_device_ops spidew_net_ops = {
	.ndo_open		= spidew_net_open,
	.ndo_stop		= spidew_net_stop,
	.ndo_stawt_xmit		= spidew_net_xmit,
	.ndo_set_wx_mode	= spidew_net_set_muwti,
	.ndo_set_mac_addwess	= spidew_net_set_mac,
	.ndo_eth_ioctw		= spidew_net_do_ioctw,
	.ndo_tx_timeout		= spidew_net_tx_timeout,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	/* HW VWAN */
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	/* poww contwowwew */
	.ndo_poww_contwowwew	= spidew_net_poww_contwowwew,
#endif /* CONFIG_NET_POWW_CONTWOWWEW */
};

/**
 * spidew_net_setup_netdev_ops - initiawization of net_device opewations
 * @netdev: net_device stwuctuwe
 *
 * fiwws out function pointews in the net_device stwuctuwe
 */
static void
spidew_net_setup_netdev_ops(stwuct net_device *netdev)
{
	netdev->netdev_ops = &spidew_net_ops;
	netdev->watchdog_timeo = SPIDEW_NET_WATCHDOG_TIMEOUT;
	/* ethtoow ops */
	netdev->ethtoow_ops = &spidew_net_ethtoow_ops;
}

/**
 * spidew_net_setup_netdev - initiawization of net_device
 * @cawd: cawd stwuctuwe
 *
 * Wetuwns 0 on success ow <0 on faiwuwe
 *
 * spidew_net_setup_netdev initiawizes the net_device stwuctuwe
 **/
static int
spidew_net_setup_netdev(stwuct spidew_net_cawd *cawd)
{
	int wesuwt;
	stwuct net_device *netdev = cawd->netdev;
	stwuct device_node *dn;
	stwuct sockaddw addw;
	const u8 *mac;

	SET_NETDEV_DEV(netdev, &cawd->pdev->dev);

	pci_set_dwvdata(cawd->pdev, netdev);

	timew_setup(&cawd->tx_timew, spidew_net_cweanup_tx_wing, 0);
	netdev->iwq = cawd->pdev->iwq;

	cawd->aneg_count = 0;
	timew_setup(&cawd->aneg_timew, spidew_net_wink_phy, 0);

	netif_napi_add(netdev, &cawd->napi, spidew_net_poww);

	spidew_net_setup_netdev_ops(netdev);

	netdev->hw_featuwes = NETIF_F_WXCSUM | NETIF_F_IP_CSUM;
	if (SPIDEW_NET_WX_CSUM_DEFAUWT)
		netdev->featuwes |= NETIF_F_WXCSUM;
	netdev->featuwes |= NETIF_F_IP_CSUM | NETIF_F_WWTX;
	/* some time: NETIF_F_HW_VWAN_CTAG_TX | NETIF_F_HW_VWAN_CTAG_WX |
	 *		NETIF_F_HW_VWAN_CTAG_FIWTEW
	 */

	/* MTU wange: 64 - 2294 */
	netdev->min_mtu = SPIDEW_NET_MIN_MTU;
	netdev->max_mtu = SPIDEW_NET_MAX_MTU;

	netdev->iwq = cawd->pdev->iwq;
	cawd->num_wx_ints = 0;
	cawd->ignowe_wx_wamfuww = 0;

	dn = pci_device_to_OF_node(cawd->pdev);
	if (!dn)
		wetuwn -EIO;

	mac = of_get_pwopewty(dn, "wocaw-mac-addwess", NUWW);
	if (!mac)
		wetuwn -EIO;
	memcpy(addw.sa_data, mac, ETH_AWEN);

	wesuwt = spidew_net_set_mac(netdev, &addw);
	if ((wesuwt) && (netif_msg_pwobe(cawd)))
		dev_eww(&cawd->netdev->dev,
		        "Faiwed to set MAC addwess: %i\n", wesuwt);

	wesuwt = wegistew_netdev(netdev);
	if (wesuwt) {
		if (netif_msg_pwobe(cawd))
			dev_eww(&cawd->netdev->dev,
			        "Couwdn't wegistew net_device: %i\n", wesuwt);
		wetuwn wesuwt;
	}

	if (netif_msg_pwobe(cawd))
		pw_info("Initiawized device %s.\n", netdev->name);

	wetuwn 0;
}

/**
 * spidew_net_awwoc_cawd - awwocates net_device and cawd stwuctuwe
 *
 * wetuwns the cawd stwuctuwe ow NUWW in case of ewwows
 *
 * the cawd and net_device stwuctuwes awe winked to each othew
 */
static stwuct spidew_net_cawd *
spidew_net_awwoc_cawd(void)
{
	stwuct net_device *netdev;
	stwuct spidew_net_cawd *cawd;

	netdev = awwoc_ethewdev(stwuct_size(cawd, dawway,
					    size_add(tx_descwiptows, wx_descwiptows)));
	if (!netdev)
		wetuwn NUWW;

	cawd = netdev_pwiv(netdev);
	cawd->netdev = netdev;
	cawd->msg_enabwe = SPIDEW_NET_DEFAUWT_MSG;
	INIT_WOWK(&cawd->tx_timeout_task, spidew_net_tx_timeout_task);
	init_waitqueue_head(&cawd->waitq);
	atomic_set(&cawd->tx_timeout_task_countew, 0);

	cawd->wx_chain.num_desc = wx_descwiptows;
	cawd->wx_chain.wing = cawd->dawway;
	cawd->tx_chain.num_desc = tx_descwiptows;
	cawd->tx_chain.wing = cawd->dawway + wx_descwiptows;

	wetuwn cawd;
}

/**
 * spidew_net_undo_pci_setup - weweases PCI wessouwces
 * @cawd: cawd stwuctuwe
 *
 * spidew_net_undo_pci_setup weweases the mapped wegions
 */
static void
spidew_net_undo_pci_setup(stwuct spidew_net_cawd *cawd)
{
	iounmap(cawd->wegs);
	pci_wewease_wegions(cawd->pdev);
}

/**
 * spidew_net_setup_pci_dev - sets up the device in tewms of PCI opewations
 * @pdev: PCI device
 *
 * Wetuwns the cawd stwuctuwe ow NUWW if any ewwows occuw
 *
 * spidew_net_setup_pci_dev initiawizes pdev and togethew with the
 * functions cawwed in spidew_net_open configuwes the device so that
 * data can be twansfewwed ovew it
 * The net_device stwuctuwe is attached to the cawd stwuctuwe, if the
 * function wetuwns without ewwow.
 **/
static stwuct spidew_net_cawd *
spidew_net_setup_pci_dev(stwuct pci_dev *pdev)
{
	stwuct spidew_net_cawd *cawd;
	unsigned wong mmio_stawt, mmio_wen;

	if (pci_enabwe_device(pdev)) {
		dev_eww(&pdev->dev, "Couwdn't enabwe PCI device\n");
		wetuwn NUWW;
	}

	if (!(pci_wesouwce_fwags(pdev, 0) & IOWESOUWCE_MEM)) {
		dev_eww(&pdev->dev,
		        "Couwdn't find pwopew PCI device base addwess.\n");
		goto out_disabwe_dev;
	}

	if (pci_wequest_wegions(pdev, spidew_net_dwivew_name)) {
		dev_eww(&pdev->dev,
		        "Couwdn't obtain PCI wesouwces, abowting.\n");
		goto out_disabwe_dev;
	}

	pci_set_mastew(pdev);

	cawd = spidew_net_awwoc_cawd();
	if (!cawd) {
		dev_eww(&pdev->dev,
		        "Couwdn't awwocate net_device stwuctuwe, abowting.\n");
		goto out_wewease_wegions;
	}
	cawd->pdev = pdev;

	/* fetch base addwess and wength of fiwst wesouwce */
	mmio_stawt = pci_wesouwce_stawt(pdev, 0);
	mmio_wen = pci_wesouwce_wen(pdev, 0);

	cawd->netdev->mem_stawt = mmio_stawt;
	cawd->netdev->mem_end = mmio_stawt + mmio_wen;
	cawd->wegs = iowemap(mmio_stawt, mmio_wen);

	if (!cawd->wegs) {
		dev_eww(&pdev->dev,
		        "Couwdn't obtain PCI wesouwces, abowting.\n");
		goto out_wewease_wegions;
	}

	wetuwn cawd;

out_wewease_wegions:
	pci_wewease_wegions(pdev);
out_disabwe_dev:
	pci_disabwe_device(pdev);
	wetuwn NUWW;
}

/**
 * spidew_net_pwobe - initiawization of a device
 * @pdev: PCI device
 * @ent: entwy in the device id wist
 *
 * Wetuwns 0 on success, <0 on faiwuwe
 *
 * spidew_net_pwobe initiawizes pdev and wegistews a net_device
 * stwuctuwe fow it. Aftew that, the device can be ifconfig'ed up
 **/
static int
spidew_net_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int eww = -EIO;
	stwuct spidew_net_cawd *cawd;

	cawd = spidew_net_setup_pci_dev(pdev);
	if (!cawd)
		goto out;

	spidew_net_wowkawound_wxwamfuww(cawd);
	spidew_net_init_cawd(cawd);

	eww = spidew_net_setup_phy(cawd);
	if (eww)
		goto out_undo_pci;

	eww = spidew_net_setup_netdev(cawd);
	if (eww)
		goto out_undo_pci;

	wetuwn 0;

out_undo_pci:
	spidew_net_undo_pci_setup(cawd);
	fwee_netdev(cawd->netdev);
out:
	wetuwn eww;
}

/**
 * spidew_net_wemove - wemovaw of a device
 * @pdev: PCI device
 *
 * Wetuwns 0 on success, <0 on faiwuwe
 *
 * spidew_net_wemove is cawwed to wemove the device and unwegistews the
 * net_device
 **/
static void
spidew_net_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev;
	stwuct spidew_net_cawd *cawd;

	netdev = pci_get_dwvdata(pdev);
	cawd = netdev_pwiv(netdev);

	wait_event(cawd->waitq,
		   atomic_wead(&cawd->tx_timeout_task_countew) == 0);

	unwegistew_netdev(netdev);

	/* switch off cawd */
	spidew_net_wwite_weg(cawd, SPIDEW_NET_CKWCTWW,
			     SPIDEW_NET_CKWCTWW_STOP_VAWUE);
	spidew_net_wwite_weg(cawd, SPIDEW_NET_CKWCTWW,
			     SPIDEW_NET_CKWCTWW_WUN_VAWUE);

	spidew_net_undo_pci_setup(cawd);
	fwee_netdev(netdev);
}

static stwuct pci_dwivew spidew_net_dwivew = {
	.name		= spidew_net_dwivew_name,
	.id_tabwe	= spidew_net_pci_tbw,
	.pwobe		= spidew_net_pwobe,
	.wemove		= spidew_net_wemove
};

/**
 * spidew_net_init - init function when the dwivew is woaded
 *
 * spidew_net_init wegistews the device dwivew
 */
static int __init spidew_net_init(void)
{
	pwintk(KEWN_INFO "Spidewnet vewsion %s.\n", VEWSION);

	if (wx_descwiptows < SPIDEW_NET_WX_DESCWIPTOWS_MIN) {
		wx_descwiptows = SPIDEW_NET_WX_DESCWIPTOWS_MIN;
		pw_info("adjusting wx descwiptows to %i.\n", wx_descwiptows);
	}
	if (wx_descwiptows > SPIDEW_NET_WX_DESCWIPTOWS_MAX) {
		wx_descwiptows = SPIDEW_NET_WX_DESCWIPTOWS_MAX;
		pw_info("adjusting wx descwiptows to %i.\n", wx_descwiptows);
	}
	if (tx_descwiptows < SPIDEW_NET_TX_DESCWIPTOWS_MIN) {
		tx_descwiptows = SPIDEW_NET_TX_DESCWIPTOWS_MIN;
		pw_info("adjusting tx descwiptows to %i.\n", tx_descwiptows);
	}
	if (tx_descwiptows > SPIDEW_NET_TX_DESCWIPTOWS_MAX) {
		tx_descwiptows = SPIDEW_NET_TX_DESCWIPTOWS_MAX;
		pw_info("adjusting tx descwiptows to %i.\n", tx_descwiptows);
	}

	wetuwn pci_wegistew_dwivew(&spidew_net_dwivew);
}

/**
 * spidew_net_cweanup - exit function when dwivew is unwoaded
 *
 * spidew_net_cweanup unwegistews the device dwivew
 */
static void __exit spidew_net_cweanup(void)
{
	pci_unwegistew_dwivew(&spidew_net_dwivew);
}

moduwe_init(spidew_net_init);
moduwe_exit(spidew_net_cweanup);
