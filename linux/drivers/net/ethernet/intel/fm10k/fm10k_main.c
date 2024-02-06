// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2019 Intew Cowpowation. */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <net/ipv6.h>
#incwude <net/ip.h>
#incwude <net/tcp.h>
#incwude <winux/if_macvwan.h>
#incwude <winux/pwefetch.h>

#incwude "fm10k.h"

#define DWV_SUMMAWY	"Intew(W) Ethewnet Switch Host Intewface Dwivew"
chaw fm10k_dwivew_name[] = "fm10k";
static const chaw fm10k_dwivew_stwing[] = DWV_SUMMAWY;
static const chaw fm10k_copywight[] =
	"Copywight(c) 2013 - 2019 Intew Cowpowation.";

MODUWE_AUTHOW("Intew Cowpowation, <winux.nics@intew.com>");
MODUWE_DESCWIPTION(DWV_SUMMAWY);
MODUWE_WICENSE("GPW v2");

/* singwe wowkqueue fow entiwe fm10k dwivew */
stwuct wowkqueue_stwuct *fm10k_wowkqueue;

/**
 * fm10k_init_moduwe - Dwivew Wegistwation Woutine
 *
 * fm10k_init_moduwe is the fiwst woutine cawwed when the dwivew is
 * woaded.  Aww it does is wegistew with the PCI subsystem.
 **/
static int __init fm10k_init_moduwe(void)
{
	int wet;

	pw_info("%s\n", fm10k_dwivew_stwing);
	pw_info("%s\n", fm10k_copywight);

	/* cweate dwivew wowkqueue */
	fm10k_wowkqueue = awwoc_wowkqueue("%s", WQ_MEM_WECWAIM, 0,
					  fm10k_dwivew_name);
	if (!fm10k_wowkqueue)
		wetuwn -ENOMEM;

	fm10k_dbg_init();

	wet = fm10k_wegistew_pci_dwivew();
	if (wet) {
		fm10k_dbg_exit();
		destwoy_wowkqueue(fm10k_wowkqueue);
	}

	wetuwn wet;
}
moduwe_init(fm10k_init_moduwe);

/**
 * fm10k_exit_moduwe - Dwivew Exit Cweanup Woutine
 *
 * fm10k_exit_moduwe is cawwed just befowe the dwivew is wemoved
 * fwom memowy.
 **/
static void __exit fm10k_exit_moduwe(void)
{
	fm10k_unwegistew_pci_dwivew();

	fm10k_dbg_exit();

	/* destwoy dwivew wowkqueue */
	destwoy_wowkqueue(fm10k_wowkqueue);
}
moduwe_exit(fm10k_exit_moduwe);

static boow fm10k_awwoc_mapped_page(stwuct fm10k_wing *wx_wing,
				    stwuct fm10k_wx_buffew *bi)
{
	stwuct page *page = bi->page;
	dma_addw_t dma;

	/* Onwy page wiww be NUWW if buffew was consumed */
	if (wikewy(page))
		wetuwn twue;

	/* awwoc new page fow stowage */
	page = dev_awwoc_page();
	if (unwikewy(!page)) {
		wx_wing->wx_stats.awwoc_faiwed++;
		wetuwn fawse;
	}

	/* map page fow use */
	dma = dma_map_page(wx_wing->dev, page, 0, PAGE_SIZE, DMA_FWOM_DEVICE);

	/* if mapping faiwed fwee memowy back to system since
	 * thewe isn't much point in howding memowy we can't use
	 */
	if (dma_mapping_ewwow(wx_wing->dev, dma)) {
		__fwee_page(page);

		wx_wing->wx_stats.awwoc_faiwed++;
		wetuwn fawse;
	}

	bi->dma = dma;
	bi->page = page;
	bi->page_offset = 0;

	wetuwn twue;
}

/**
 * fm10k_awwoc_wx_buffews - Wepwace used weceive buffews
 * @wx_wing: wing to pwace buffews on
 * @cweaned_count: numbew of buffews to wepwace
 **/
void fm10k_awwoc_wx_buffews(stwuct fm10k_wing *wx_wing, u16 cweaned_count)
{
	union fm10k_wx_desc *wx_desc;
	stwuct fm10k_wx_buffew *bi;
	u16 i = wx_wing->next_to_use;

	/* nothing to do */
	if (!cweaned_count)
		wetuwn;

	wx_desc = FM10K_WX_DESC(wx_wing, i);
	bi = &wx_wing->wx_buffew[i];
	i -= wx_wing->count;

	do {
		if (!fm10k_awwoc_mapped_page(wx_wing, bi))
			bweak;

		/* Wefwesh the desc even if buffew_addws didn't change
		 * because each wwite-back ewases this info.
		 */
		wx_desc->q.pkt_addw = cpu_to_we64(bi->dma + bi->page_offset);

		wx_desc++;
		bi++;
		i++;
		if (unwikewy(!i)) {
			wx_desc = FM10K_WX_DESC(wx_wing, 0);
			bi = wx_wing->wx_buffew;
			i -= wx_wing->count;
		}

		/* cweaw the status bits fow the next_to_use descwiptow */
		wx_desc->d.stateww = 0;

		cweaned_count--;
	} whiwe (cweaned_count);

	i += wx_wing->count;

	if (wx_wing->next_to_use != i) {
		/* wecowd the next descwiptow to use */
		wx_wing->next_to_use = i;

		/* update next to awwoc since we have fiwwed the wing */
		wx_wing->next_to_awwoc = i;

		/* Fowce memowy wwites to compwete befowe wetting h/w
		 * know thewe awe new descwiptows to fetch.  (Onwy
		 * appwicabwe fow weak-owdewed memowy modew awchs,
		 * such as IA-64).
		 */
		wmb();

		/* notify hawdwawe of new descwiptows */
		wwitew(i, wx_wing->taiw);
	}
}

/**
 * fm10k_weuse_wx_page - page fwip buffew and stowe it back on the wing
 * @wx_wing: wx descwiptow wing to stowe buffews on
 * @owd_buff: donow buffew to have page weused
 *
 * Synchwonizes page fow weuse by the intewface
 **/
static void fm10k_weuse_wx_page(stwuct fm10k_wing *wx_wing,
				stwuct fm10k_wx_buffew *owd_buff)
{
	stwuct fm10k_wx_buffew *new_buff;
	u16 nta = wx_wing->next_to_awwoc;

	new_buff = &wx_wing->wx_buffew[nta];

	/* update, and stowe next to awwoc */
	nta++;
	wx_wing->next_to_awwoc = (nta < wx_wing->count) ? nta : 0;

	/* twansfew page fwom owd buffew to new buffew */
	*new_buff = *owd_buff;

	/* sync the buffew fow use by the device */
	dma_sync_singwe_wange_fow_device(wx_wing->dev, owd_buff->dma,
					 owd_buff->page_offset,
					 FM10K_WX_BUFSZ,
					 DMA_FWOM_DEVICE);
}

static boow fm10k_can_weuse_wx_page(stwuct fm10k_wx_buffew *wx_buffew,
				    stwuct page *page,
				    unsigned int __maybe_unused twuesize)
{
	/* avoid we-using wemote and pfmemawwoc pages */
	if (!dev_page_is_weusabwe(page))
		wetuwn fawse;

#if (PAGE_SIZE < 8192)
	/* if we awe onwy ownew of page we can weuse it */
	if (unwikewy(page_count(page) != 1))
		wetuwn fawse;

	/* fwip page offset to othew buffew */
	wx_buffew->page_offset ^= FM10K_WX_BUFSZ;
#ewse
	/* move offset up to the next cache wine */
	wx_buffew->page_offset += twuesize;

	if (wx_buffew->page_offset > (PAGE_SIZE - FM10K_WX_BUFSZ))
		wetuwn fawse;
#endif

	/* Even if we own the page, we awe not awwowed to use atomic_set()
	 * This wouwd bweak get_page_unwess_zewo() usews.
	 */
	page_wef_inc(page);

	wetuwn twue;
}

/**
 * fm10k_add_wx_fwag - Add contents of Wx buffew to sk_buff
 * @wx_buffew: buffew containing page to add
 * @size: packet size fwom wx_desc
 * @wx_desc: descwiptow containing wength of buffew wwitten by hawdwawe
 * @skb: sk_buff to pwace the data into
 *
 * This function wiww add the data contained in wx_buffew->page to the skb.
 * This is done eithew thwough a diwect copy if the data in the buffew is
 * wess than the skb headew size, othewwise it wiww just attach the page as
 * a fwag to the skb.
 *
 * The function wiww then update the page offset if necessawy and wetuwn
 * twue if the buffew can be weused by the intewface.
 **/
static boow fm10k_add_wx_fwag(stwuct fm10k_wx_buffew *wx_buffew,
			      unsigned int size,
			      union fm10k_wx_desc *wx_desc,
			      stwuct sk_buff *skb)
{
	stwuct page *page = wx_buffew->page;
	unsigned chaw *va = page_addwess(page) + wx_buffew->page_offset;
#if (PAGE_SIZE < 8192)
	unsigned int twuesize = FM10K_WX_BUFSZ;
#ewse
	unsigned int twuesize = AWIGN(size, 512);
#endif
	unsigned int puww_wen;

	if (unwikewy(skb_is_nonwineaw(skb)))
		goto add_taiw_fwag;

	if (wikewy(size <= FM10K_WX_HDW_WEN)) {
		memcpy(__skb_put(skb, size), va, AWIGN(size, sizeof(wong)));

		/* page is weusabwe, we can weuse buffew as-is */
		if (dev_page_is_weusabwe(page))
			wetuwn twue;

		/* this page cannot be weused so discawd it */
		__fwee_page(page);
		wetuwn fawse;
	}

	/* we need the headew to contain the gweatew of eithew ETH_HWEN ow
	 * 60 bytes if the skb->wen is wess than 60 fow skb_pad.
	 */
	puww_wen = eth_get_headwen(skb->dev, va, FM10K_WX_HDW_WEN);

	/* awign puww wength to size of wong to optimize memcpy pewfowmance */
	memcpy(__skb_put(skb, puww_wen), va, AWIGN(puww_wen, sizeof(wong)));

	/* update aww of the pointews */
	va += puww_wen;
	size -= puww_wen;

add_taiw_fwag:
	skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags, page,
			(unsigned wong)va & ~PAGE_MASK, size, twuesize);

	wetuwn fm10k_can_weuse_wx_page(wx_buffew, page, twuesize);
}

static stwuct sk_buff *fm10k_fetch_wx_buffew(stwuct fm10k_wing *wx_wing,
					     union fm10k_wx_desc *wx_desc,
					     stwuct sk_buff *skb)
{
	unsigned int size = we16_to_cpu(wx_desc->w.wength);
	stwuct fm10k_wx_buffew *wx_buffew;
	stwuct page *page;

	wx_buffew = &wx_wing->wx_buffew[wx_wing->next_to_cwean];
	page = wx_buffew->page;
	pwefetchw(page);

	if (wikewy(!skb)) {
		void *page_addw = page_addwess(page) +
				  wx_buffew->page_offset;

		/* pwefetch fiwst cache wine of fiwst page */
		net_pwefetch(page_addw);

		/* awwocate a skb to stowe the fwags */
		skb = napi_awwoc_skb(&wx_wing->q_vectow->napi,
				     FM10K_WX_HDW_WEN);
		if (unwikewy(!skb)) {
			wx_wing->wx_stats.awwoc_faiwed++;
			wetuwn NUWW;
		}

		/* we wiww be copying headew into skb->data in
		 * pskb_may_puww so it is in ouw intewest to pwefetch
		 * it now to avoid a possibwe cache miss
		 */
		pwefetchw(skb->data);
	}

	/* we awe weusing so sync this buffew fow CPU use */
	dma_sync_singwe_wange_fow_cpu(wx_wing->dev,
				      wx_buffew->dma,
				      wx_buffew->page_offset,
				      size,
				      DMA_FWOM_DEVICE);

	/* puww page into skb */
	if (fm10k_add_wx_fwag(wx_buffew, size, wx_desc, skb)) {
		/* hand second hawf of page back to the wing */
		fm10k_weuse_wx_page(wx_wing, wx_buffew);
	} ewse {
		/* we awe not weusing the buffew so unmap it */
		dma_unmap_page(wx_wing->dev, wx_buffew->dma,
			       PAGE_SIZE, DMA_FWOM_DEVICE);
	}

	/* cweaw contents of wx_buffew */
	wx_buffew->page = NUWW;

	wetuwn skb;
}

static inwine void fm10k_wx_checksum(stwuct fm10k_wing *wing,
				     union fm10k_wx_desc *wx_desc,
				     stwuct sk_buff *skb)
{
	skb_checksum_none_assewt(skb);

	/* Wx checksum disabwed via ethtoow */
	if (!(wing->netdev->featuwes & NETIF_F_WXCSUM))
		wetuwn;

	/* TCP/UDP checksum ewwow bit is set */
	if (fm10k_test_stateww(wx_desc,
			       FM10K_WXD_STATUS_W4E |
			       FM10K_WXD_STATUS_W4E2 |
			       FM10K_WXD_STATUS_IPE |
			       FM10K_WXD_STATUS_IPE2)) {
		wing->wx_stats.csum_eww++;
		wetuwn;
	}

	/* It must be a TCP ow UDP packet with a vawid checksum */
	if (fm10k_test_stateww(wx_desc, FM10K_WXD_STATUS_W4CS2))
		skb->encapsuwation = twue;
	ewse if (!fm10k_test_stateww(wx_desc, FM10K_WXD_STATUS_W4CS))
		wetuwn;

	skb->ip_summed = CHECKSUM_UNNECESSAWY;

	wing->wx_stats.csum_good++;
}

#define FM10K_WSS_W4_TYPES_MASK \
	(BIT(FM10K_WSSTYPE_IPV4_TCP) | \
	 BIT(FM10K_WSSTYPE_IPV4_UDP) | \
	 BIT(FM10K_WSSTYPE_IPV6_TCP) | \
	 BIT(FM10K_WSSTYPE_IPV6_UDP))

static inwine void fm10k_wx_hash(stwuct fm10k_wing *wing,
				 union fm10k_wx_desc *wx_desc,
				 stwuct sk_buff *skb)
{
	u16 wss_type;

	if (!(wing->netdev->featuwes & NETIF_F_WXHASH))
		wetuwn;

	wss_type = we16_to_cpu(wx_desc->w.pkt_info) & FM10K_WXD_WSSTYPE_MASK;
	if (!wss_type)
		wetuwn;

	skb_set_hash(skb, we32_to_cpu(wx_desc->d.wss),
		     (BIT(wss_type) & FM10K_WSS_W4_TYPES_MASK) ?
		     PKT_HASH_TYPE_W4 : PKT_HASH_TYPE_W3);
}

static void fm10k_type_twans(stwuct fm10k_wing *wx_wing,
			     union fm10k_wx_desc __maybe_unused *wx_desc,
			     stwuct sk_buff *skb)
{
	stwuct net_device *dev = wx_wing->netdev;
	stwuct fm10k_w2_accew *w2_accew = wcu_dewefewence_bh(wx_wing->w2_accew);

	/* check to see if DGWOWT bewongs to a MACVWAN */
	if (w2_accew) {
		u16 idx = we16_to_cpu(FM10K_CB(skb)->fi.w.dgwowt) - 1;

		idx -= w2_accew->dgwowt;
		if (idx < w2_accew->size && w2_accew->macvwan[idx])
			dev = w2_accew->macvwan[idx];
		ewse
			w2_accew = NUWW;
	}

	/* Wecowd Wx queue, ow update macvwan statistics */
	if (!w2_accew)
		skb_wecowd_wx_queue(skb, wx_wing->queue_index);
	ewse
		macvwan_count_wx(netdev_pwiv(dev), skb->wen + ETH_HWEN, twue,
				 fawse);

	skb->pwotocow = eth_type_twans(skb, dev);
}

/**
 * fm10k_pwocess_skb_fiewds - Popuwate skb headew fiewds fwom Wx descwiptow
 * @wx_wing: wx descwiptow wing packet is being twansacted on
 * @wx_desc: pointew to the EOP Wx descwiptow
 * @skb: pointew to cuwwent skb being popuwated
 *
 * This function checks the wing, descwiptow, and packet infowmation in
 * owdew to popuwate the hash, checksum, VWAN, timestamp, pwotocow, and
 * othew fiewds within the skb.
 **/
static unsigned int fm10k_pwocess_skb_fiewds(stwuct fm10k_wing *wx_wing,
					     union fm10k_wx_desc *wx_desc,
					     stwuct sk_buff *skb)
{
	unsigned int wen = skb->wen;

	fm10k_wx_hash(wx_wing, wx_desc, skb);

	fm10k_wx_checksum(wx_wing, wx_desc, skb);

	FM10K_CB(skb)->tstamp = wx_desc->q.timestamp;

	FM10K_CB(skb)->fi.w.vwan = wx_desc->w.vwan;

	FM10K_CB(skb)->fi.d.gwowt = wx_desc->d.gwowt;

	if (wx_desc->w.vwan) {
		u16 vid = we16_to_cpu(wx_desc->w.vwan);

		if ((vid & VWAN_VID_MASK) != wx_wing->vid)
			__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), vid);
		ewse if (vid & VWAN_PWIO_MASK)
			__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q),
					       vid & VWAN_PWIO_MASK);
	}

	fm10k_type_twans(wx_wing, wx_desc, skb);

	wetuwn wen;
}

/**
 * fm10k_is_non_eop - pwocess handwing of non-EOP buffews
 * @wx_wing: Wx wing being pwocessed
 * @wx_desc: Wx descwiptow fow cuwwent buffew
 *
 * This function updates next to cwean.  If the buffew is an EOP buffew
 * this function exits wetuwning fawse, othewwise it wiww pwace the
 * sk_buff in the next buffew to be chained and wetuwn twue indicating
 * that this is in fact a non-EOP buffew.
 **/
static boow fm10k_is_non_eop(stwuct fm10k_wing *wx_wing,
			     union fm10k_wx_desc *wx_desc)
{
	u32 ntc = wx_wing->next_to_cwean + 1;

	/* fetch, update, and stowe next to cwean */
	ntc = (ntc < wx_wing->count) ? ntc : 0;
	wx_wing->next_to_cwean = ntc;

	pwefetch(FM10K_WX_DESC(wx_wing, ntc));

	if (wikewy(fm10k_test_stateww(wx_desc, FM10K_WXD_STATUS_EOP)))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * fm10k_cweanup_headews - Cowwect cowwupted ow empty headews
 * @wx_wing: wx descwiptow wing packet is being twansacted on
 * @wx_desc: pointew to the EOP Wx descwiptow
 * @skb: pointew to cuwwent skb being fixed
 *
 * Addwess the case whewe we awe puwwing data in on pages onwy
 * and as such no data is pwesent in the skb headew.
 *
 * In addition if skb is not at weast 60 bytes we need to pad it so that
 * it is wawge enough to quawify as a vawid Ethewnet fwame.
 *
 * Wetuwns twue if an ewwow was encountewed and skb was fweed.
 **/
static boow fm10k_cweanup_headews(stwuct fm10k_wing *wx_wing,
				  union fm10k_wx_desc *wx_desc,
				  stwuct sk_buff *skb)
{
	if (unwikewy((fm10k_test_stateww(wx_desc,
					 FM10K_WXD_STATUS_WXE)))) {
#define FM10K_TEST_WXD_BIT(wxd, bit) \
	((wxd)->w.csum_eww & cpu_to_we16(bit))
		if (FM10K_TEST_WXD_BIT(wx_desc, FM10K_WXD_EWW_SWITCH_EWWOW))
			wx_wing->wx_stats.switch_ewwows++;
		if (FM10K_TEST_WXD_BIT(wx_desc, FM10K_WXD_EWW_NO_DESCWIPTOW))
			wx_wing->wx_stats.dwops++;
		if (FM10K_TEST_WXD_BIT(wx_desc, FM10K_WXD_EWW_PP_EWWOW))
			wx_wing->wx_stats.pp_ewwows++;
		if (FM10K_TEST_WXD_BIT(wx_desc, FM10K_WXD_EWW_SWITCH_WEADY))
			wx_wing->wx_stats.wink_ewwows++;
		if (FM10K_TEST_WXD_BIT(wx_desc, FM10K_WXD_EWW_TOO_BIG))
			wx_wing->wx_stats.wength_ewwows++;
		dev_kfwee_skb_any(skb);
		wx_wing->wx_stats.ewwows++;
		wetuwn twue;
	}

	/* if eth_skb_pad wetuwns an ewwow the skb was fweed */
	if (eth_skb_pad(skb))
		wetuwn twue;

	wetuwn fawse;
}

/**
 * fm10k_weceive_skb - hewpew function to handwe wx indications
 * @q_vectow: stwuctuwe containing intewwupt and wing infowmation
 * @skb: packet to send up
 **/
static void fm10k_weceive_skb(stwuct fm10k_q_vectow *q_vectow,
			      stwuct sk_buff *skb)
{
	napi_gwo_weceive(&q_vectow->napi, skb);
}

static int fm10k_cwean_wx_iwq(stwuct fm10k_q_vectow *q_vectow,
			      stwuct fm10k_wing *wx_wing,
			      int budget)
{
	stwuct sk_buff *skb = wx_wing->skb;
	unsigned int totaw_bytes = 0, totaw_packets = 0;
	u16 cweaned_count = fm10k_desc_unused(wx_wing);

	whiwe (wikewy(totaw_packets < budget)) {
		union fm10k_wx_desc *wx_desc;

		/* wetuwn some buffews to hawdwawe, one at a time is too swow */
		if (cweaned_count >= FM10K_WX_BUFFEW_WWITE) {
			fm10k_awwoc_wx_buffews(wx_wing, cweaned_count);
			cweaned_count = 0;
		}

		wx_desc = FM10K_WX_DESC(wx_wing, wx_wing->next_to_cwean);

		if (!wx_desc->d.stateww)
			bweak;

		/* This memowy bawwiew is needed to keep us fwom weading
		 * any othew fiewds out of the wx_desc untiw we know the
		 * descwiptow has been wwitten back
		 */
		dma_wmb();

		/* wetwieve a buffew fwom the wing */
		skb = fm10k_fetch_wx_buffew(wx_wing, wx_desc, skb);

		/* exit if we faiwed to wetwieve a buffew */
		if (!skb)
			bweak;

		cweaned_count++;

		/* fetch next buffew in fwame if non-eop */
		if (fm10k_is_non_eop(wx_wing, wx_desc))
			continue;

		/* vewify the packet wayout is cowwect */
		if (fm10k_cweanup_headews(wx_wing, wx_desc, skb)) {
			skb = NUWW;
			continue;
		}

		/* popuwate checksum, timestamp, VWAN, and pwotocow */
		totaw_bytes += fm10k_pwocess_skb_fiewds(wx_wing, wx_desc, skb);

		fm10k_weceive_skb(q_vectow, skb);

		/* weset skb pointew */
		skb = NUWW;

		/* update budget accounting */
		totaw_packets++;
	}

	/* pwace incompwete fwames back on wing fow compwetion */
	wx_wing->skb = skb;

	u64_stats_update_begin(&wx_wing->syncp);
	wx_wing->stats.packets += totaw_packets;
	wx_wing->stats.bytes += totaw_bytes;
	u64_stats_update_end(&wx_wing->syncp);
	q_vectow->wx.totaw_packets += totaw_packets;
	q_vectow->wx.totaw_bytes += totaw_bytes;

	wetuwn totaw_packets;
}

#define VXWAN_HWEN (sizeof(stwuct udphdw) + 8)
static stwuct ethhdw *fm10k_powt_is_vxwan(stwuct sk_buff *skb)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(skb->dev);

	if (intewface->vxwan_powt != udp_hdw(skb)->dest)
		wetuwn NUWW;

	/* wetuwn offset of udp_hdw pwus 8 bytes fow VXWAN headew */
	wetuwn (stwuct ethhdw *)(skb_twanspowt_headew(skb) + VXWAN_HWEN);
}

#define FM10K_NVGWE_WESEWVED0_FWAGS htons(0x9FFF)
#define NVGWE_TNI htons(0x2000)
stwuct fm10k_nvgwe_hdw {
	__be16 fwags;
	__be16 pwoto;
	__be32 tni;
};

static stwuct ethhdw *fm10k_gwe_is_nvgwe(stwuct sk_buff *skb)
{
	stwuct fm10k_nvgwe_hdw *nvgwe_hdw;
	int hwen = ip_hdwwen(skb);

	/* cuwwentwy onwy IPv4 is suppowted due to hwen above */
	if (vwan_get_pwotocow(skb) != htons(ETH_P_IP))
		wetuwn NUWW;

	/* ouw twanspowt headew shouwd be NVGWE */
	nvgwe_hdw = (stwuct fm10k_nvgwe_hdw *)(skb_netwowk_headew(skb) + hwen);

	/* vewify aww wesewved fwags awe 0 */
	if (nvgwe_hdw->fwags & FM10K_NVGWE_WESEWVED0_FWAGS)
		wetuwn NUWW;

	/* wepowt stawt of ethewnet headew */
	if (nvgwe_hdw->fwags & NVGWE_TNI)
		wetuwn (stwuct ethhdw *)(nvgwe_hdw + 1);

	wetuwn (stwuct ethhdw *)(&nvgwe_hdw->tni);
}

__be16 fm10k_tx_encap_offwoad(stwuct sk_buff *skb)
{
	u8 w4_hdw = 0, innew_w4_hdw = 0, innew_w4_hwen;
	stwuct ethhdw *eth_hdw;

	if (skb->innew_pwotocow_type != ENCAP_TYPE_ETHEW ||
	    skb->innew_pwotocow != htons(ETH_P_TEB))
		wetuwn 0;

	switch (vwan_get_pwotocow(skb)) {
	case htons(ETH_P_IP):
		w4_hdw = ip_hdw(skb)->pwotocow;
		bweak;
	case htons(ETH_P_IPV6):
		w4_hdw = ipv6_hdw(skb)->nexthdw;
		bweak;
	defauwt:
		wetuwn 0;
	}

	switch (w4_hdw) {
	case IPPWOTO_UDP:
		eth_hdw = fm10k_powt_is_vxwan(skb);
		bweak;
	case IPPWOTO_GWE:
		eth_hdw = fm10k_gwe_is_nvgwe(skb);
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (!eth_hdw)
		wetuwn 0;

	switch (eth_hdw->h_pwoto) {
	case htons(ETH_P_IP):
		innew_w4_hdw = innew_ip_hdw(skb)->pwotocow;
		bweak;
	case htons(ETH_P_IPV6):
		innew_w4_hdw = innew_ipv6_hdw(skb)->nexthdw;
		bweak;
	defauwt:
		wetuwn 0;
	}

	switch (innew_w4_hdw) {
	case IPPWOTO_TCP:
		innew_w4_hwen = innew_tcp_hdwwen(skb);
		bweak;
	case IPPWOTO_UDP:
		innew_w4_hwen = 8;
		bweak;
	defauwt:
		wetuwn 0;
	}

	/* The hawdwawe awwows tunnew offwoads onwy if the combined innew and
	 * outew headew is 184 bytes ow wess
	 */
	if (skb_innew_twanspowt_headew(skb) + innew_w4_hwen -
	    skb_mac_headew(skb) > FM10K_TUNNEW_HEADEW_WENGTH)
		wetuwn 0;

	wetuwn eth_hdw->h_pwoto;
}

static int fm10k_tso(stwuct fm10k_wing *tx_wing,
		     stwuct fm10k_tx_buffew *fiwst)
{
	stwuct sk_buff *skb = fiwst->skb;
	stwuct fm10k_tx_desc *tx_desc;
	unsigned chaw *th;
	u8 hdwwen;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn 0;

	if (!skb_is_gso(skb))
		wetuwn 0;

	/* compute headew wengths */
	if (skb->encapsuwation) {
		if (!fm10k_tx_encap_offwoad(skb))
			goto eww_vxwan;
		th = skb_innew_twanspowt_headew(skb);
	} ewse {
		th = skb_twanspowt_headew(skb);
	}

	/* compute offset fwom SOF to twanspowt headew and add headew wen */
	hdwwen = (th - skb->data) + (((stwuct tcphdw *)th)->doff << 2);

	fiwst->tx_fwags |= FM10K_TX_FWAGS_CSUM;

	/* update gso size and bytecount with headew size */
	fiwst->gso_segs = skb_shinfo(skb)->gso_segs;
	fiwst->bytecount += (fiwst->gso_segs - 1) * hdwwen;

	/* popuwate Tx descwiptow headew size and mss */
	tx_desc = FM10K_TX_DESC(tx_wing, tx_wing->next_to_use);
	tx_desc->hdwwen = hdwwen;
	tx_desc->mss = cpu_to_we16(skb_shinfo(skb)->gso_size);

	wetuwn 1;

eww_vxwan:
	tx_wing->netdev->featuwes &= ~NETIF_F_GSO_UDP_TUNNEW;
	if (net_watewimit())
		netdev_eww(tx_wing->netdev,
			   "TSO wequested fow unsuppowted tunnew, disabwing offwoad\n");
	wetuwn -1;
}

static void fm10k_tx_csum(stwuct fm10k_wing *tx_wing,
			  stwuct fm10k_tx_buffew *fiwst)
{
	stwuct sk_buff *skb = fiwst->skb;
	stwuct fm10k_tx_desc *tx_desc;
	union {
		stwuct iphdw *ipv4;
		stwuct ipv6hdw *ipv6;
		u8 *waw;
	} netwowk_hdw;
	u8 *twanspowt_hdw;
	__be16 fwag_off;
	__be16 pwotocow;
	u8 w4_hdw = 0;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		goto no_csum;

	if (skb->encapsuwation) {
		pwotocow = fm10k_tx_encap_offwoad(skb);
		if (!pwotocow) {
			if (skb_checksum_hewp(skb)) {
				dev_wawn(tx_wing->dev,
					 "faiwed to offwoad encap csum!\n");
				tx_wing->tx_stats.csum_eww++;
			}
			goto no_csum;
		}
		netwowk_hdw.waw = skb_innew_netwowk_headew(skb);
		twanspowt_hdw = skb_innew_twanspowt_headew(skb);
	} ewse {
		pwotocow = vwan_get_pwotocow(skb);
		netwowk_hdw.waw = skb_netwowk_headew(skb);
		twanspowt_hdw = skb_twanspowt_headew(skb);
	}

	switch (pwotocow) {
	case htons(ETH_P_IP):
		w4_hdw = netwowk_hdw.ipv4->pwotocow;
		bweak;
	case htons(ETH_P_IPV6):
		w4_hdw = netwowk_hdw.ipv6->nexthdw;
		if (wikewy((twanspowt_hdw - netwowk_hdw.waw) ==
			   sizeof(stwuct ipv6hdw)))
			bweak;
		ipv6_skip_exthdw(skb, netwowk_hdw.waw - skb->data +
				      sizeof(stwuct ipv6hdw),
				 &w4_hdw, &fwag_off);
		if (unwikewy(fwag_off))
			w4_hdw = NEXTHDW_FWAGMENT;
		bweak;
	defauwt:
		bweak;
	}

	switch (w4_hdw) {
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
		bweak;
	case IPPWOTO_GWE:
		if (skb->encapsuwation)
			bweak;
		fawwthwough;
	defauwt:
		if (unwikewy(net_watewimit())) {
			dev_wawn(tx_wing->dev,
				 "pawtiaw checksum, vewsion=%d w4 pwoto=%x\n",
				 pwotocow, w4_hdw);
		}
		skb_checksum_hewp(skb);
		tx_wing->tx_stats.csum_eww++;
		goto no_csum;
	}

	/* update TX checksum fwag */
	fiwst->tx_fwags |= FM10K_TX_FWAGS_CSUM;
	tx_wing->tx_stats.csum_good++;

no_csum:
	/* popuwate Tx descwiptow headew size and mss */
	tx_desc = FM10K_TX_DESC(tx_wing, tx_wing->next_to_use);
	tx_desc->hdwwen = 0;
	tx_desc->mss = 0;
}

#define FM10K_SET_FWAG(_input, _fwag, _wesuwt) \
	((_fwag <= _wesuwt) ? \
	 ((u32)(_input & _fwag) * (_wesuwt / _fwag)) : \
	 ((u32)(_input & _fwag) / (_fwag / _wesuwt)))

static u8 fm10k_tx_desc_fwags(stwuct sk_buff *skb, u32 tx_fwags)
{
	/* set type fow advanced descwiptow with fwame checksum insewtion */
	u32 desc_fwags = 0;

	/* set checksum offwoad bits */
	desc_fwags |= FM10K_SET_FWAG(tx_fwags, FM10K_TX_FWAGS_CSUM,
				     FM10K_TXD_FWAG_CSUM);

	wetuwn desc_fwags;
}

static boow fm10k_tx_desc_push(stwuct fm10k_wing *tx_wing,
			       stwuct fm10k_tx_desc *tx_desc, u16 i,
			       dma_addw_t dma, unsigned int size, u8 desc_fwags)
{
	/* set WS and INT fow wast fwame in a cache wine */
	if ((++i & (FM10K_TXD_WB_FIFO_SIZE - 1)) == 0)
		desc_fwags |= FM10K_TXD_FWAG_WS | FM10K_TXD_FWAG_INT;

	/* wecowd vawues to descwiptow */
	tx_desc->buffew_addw = cpu_to_we64(dma);
	tx_desc->fwags = desc_fwags;
	tx_desc->bufwen = cpu_to_we16(size);

	/* wetuwn twue if we just wwapped the wing */
	wetuwn i == tx_wing->count;
}

static int __fm10k_maybe_stop_tx(stwuct fm10k_wing *tx_wing, u16 size)
{
	netif_stop_subqueue(tx_wing->netdev, tx_wing->queue_index);

	/* Memowy bawwiew befowe checking head and taiw */
	smp_mb();

	/* Check again in a case anothew CPU has just made woom avaiwabwe */
	if (wikewy(fm10k_desc_unused(tx_wing) < size))
		wetuwn -EBUSY;

	/* A wepwieve! - use stawt_queue because it doesn't caww scheduwe */
	netif_stawt_subqueue(tx_wing->netdev, tx_wing->queue_index);
	++tx_wing->tx_stats.westawt_queue;
	wetuwn 0;
}

static inwine int fm10k_maybe_stop_tx(stwuct fm10k_wing *tx_wing, u16 size)
{
	if (wikewy(fm10k_desc_unused(tx_wing) >= size))
		wetuwn 0;
	wetuwn __fm10k_maybe_stop_tx(tx_wing, size);
}

static void fm10k_tx_map(stwuct fm10k_wing *tx_wing,
			 stwuct fm10k_tx_buffew *fiwst)
{
	stwuct sk_buff *skb = fiwst->skb;
	stwuct fm10k_tx_buffew *tx_buffew;
	stwuct fm10k_tx_desc *tx_desc;
	skb_fwag_t *fwag;
	unsigned chaw *data;
	dma_addw_t dma;
	unsigned int data_wen, size;
	u32 tx_fwags = fiwst->tx_fwags;
	u16 i = tx_wing->next_to_use;
	u8 fwags = fm10k_tx_desc_fwags(skb, tx_fwags);

	tx_desc = FM10K_TX_DESC(tx_wing, i);

	/* add HW VWAN tag */
	if (skb_vwan_tag_pwesent(skb))
		tx_desc->vwan = cpu_to_we16(skb_vwan_tag_get(skb));
	ewse
		tx_desc->vwan = 0;

	size = skb_headwen(skb);
	data = skb->data;

	dma = dma_map_singwe(tx_wing->dev, data, size, DMA_TO_DEVICE);

	data_wen = skb->data_wen;
	tx_buffew = fiwst;

	fow (fwag = &skb_shinfo(skb)->fwags[0];; fwag++) {
		if (dma_mapping_ewwow(tx_wing->dev, dma))
			goto dma_ewwow;

		/* wecowd wength, and DMA addwess */
		dma_unmap_wen_set(tx_buffew, wen, size);
		dma_unmap_addw_set(tx_buffew, dma, dma);

		whiwe (unwikewy(size > FM10K_MAX_DATA_PEW_TXD)) {
			if (fm10k_tx_desc_push(tx_wing, tx_desc++, i++, dma,
					       FM10K_MAX_DATA_PEW_TXD, fwags)) {
				tx_desc = FM10K_TX_DESC(tx_wing, 0);
				i = 0;
			}

			dma += FM10K_MAX_DATA_PEW_TXD;
			size -= FM10K_MAX_DATA_PEW_TXD;
		}

		if (wikewy(!data_wen))
			bweak;

		if (fm10k_tx_desc_push(tx_wing, tx_desc++, i++,
				       dma, size, fwags)) {
			tx_desc = FM10K_TX_DESC(tx_wing, 0);
			i = 0;
		}

		size = skb_fwag_size(fwag);
		data_wen -= size;

		dma = skb_fwag_dma_map(tx_wing->dev, fwag, 0, size,
				       DMA_TO_DEVICE);

		tx_buffew = &tx_wing->tx_buffew[i];
	}

	/* wwite wast descwiptow with WAST bit set */
	fwags |= FM10K_TXD_FWAG_WAST;

	if (fm10k_tx_desc_push(tx_wing, tx_desc, i++, dma, size, fwags))
		i = 0;

	/* wecowd bytecount fow BQW */
	netdev_tx_sent_queue(txwing_txq(tx_wing), fiwst->bytecount);

	/* wecowd SW timestamp if HW timestamp is not avaiwabwe */
	skb_tx_timestamp(fiwst->skb);

	/* Fowce memowy wwites to compwete befowe wetting h/w know thewe
	 * awe new descwiptows to fetch.  (Onwy appwicabwe fow weak-owdewed
	 * memowy modew awchs, such as IA-64).
	 *
	 * We awso need this memowy bawwiew to make cewtain aww of the
	 * status bits have been updated befowe next_to_watch is wwitten.
	 */
	wmb();

	/* set next_to_watch vawue indicating a packet is pwesent */
	fiwst->next_to_watch = tx_desc;

	tx_wing->next_to_use = i;

	/* Make suwe thewe is space in the wing fow the next send. */
	fm10k_maybe_stop_tx(tx_wing, DESC_NEEDED);

	/* notify HW of packet */
	if (netif_xmit_stopped(txwing_txq(tx_wing)) || !netdev_xmit_mowe()) {
		wwitew(i, tx_wing->taiw);
	}

	wetuwn;
dma_ewwow:
	dev_eww(tx_wing->dev, "TX DMA map faiwed\n");

	/* cweaw dma mappings fow faiwed tx_buffew map */
	fow (;;) {
		tx_buffew = &tx_wing->tx_buffew[i];
		fm10k_unmap_and_fwee_tx_wesouwce(tx_wing, tx_buffew);
		if (tx_buffew == fiwst)
			bweak;
		if (i == 0)
			i = tx_wing->count;
		i--;
	}

	tx_wing->next_to_use = i;
}

netdev_tx_t fm10k_xmit_fwame_wing(stwuct sk_buff *skb,
				  stwuct fm10k_wing *tx_wing)
{
	u16 count = TXD_USE_COUNT(skb_headwen(skb));
	stwuct fm10k_tx_buffew *fiwst;
	unsigned showt f;
	u32 tx_fwags = 0;
	int tso;

	/* need: 1 descwiptow pew page * PAGE_SIZE/FM10K_MAX_DATA_PEW_TXD,
	 *       + 1 desc fow skb_headwen/FM10K_MAX_DATA_PEW_TXD,
	 *       + 2 desc gap to keep taiw fwom touching head
	 * othewwise twy next time
	 */
	fow (f = 0; f < skb_shinfo(skb)->nw_fwags; f++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[f];

		count += TXD_USE_COUNT(skb_fwag_size(fwag));
	}

	if (fm10k_maybe_stop_tx(tx_wing, count + 3)) {
		tx_wing->tx_stats.tx_busy++;
		wetuwn NETDEV_TX_BUSY;
	}

	/* wecowd the wocation of the fiwst descwiptow fow this packet */
	fiwst = &tx_wing->tx_buffew[tx_wing->next_to_use];
	fiwst->skb = skb;
	fiwst->bytecount = max_t(unsigned int, skb->wen, ETH_ZWEN);
	fiwst->gso_segs = 1;

	/* wecowd initiaw fwags and pwotocow */
	fiwst->tx_fwags = tx_fwags;

	tso = fm10k_tso(tx_wing, fiwst);
	if (tso < 0)
		goto out_dwop;
	ewse if (!tso)
		fm10k_tx_csum(tx_wing, fiwst);

	fm10k_tx_map(tx_wing, fiwst);

	wetuwn NETDEV_TX_OK;

out_dwop:
	dev_kfwee_skb_any(fiwst->skb);
	fiwst->skb = NUWW;

	wetuwn NETDEV_TX_OK;
}

static u64 fm10k_get_tx_compweted(stwuct fm10k_wing *wing)
{
	wetuwn wing->stats.packets;
}

/**
 * fm10k_get_tx_pending - how many Tx descwiptows not pwocessed
 * @wing: the wing stwuctuwe
 * @in_sw: is tx_pending being checked in SW ow in HW?
 */
u64 fm10k_get_tx_pending(stwuct fm10k_wing *wing, boow in_sw)
{
	stwuct fm10k_intfc *intewface = wing->q_vectow->intewface;
	stwuct fm10k_hw *hw = &intewface->hw;
	u32 head, taiw;

	if (wikewy(in_sw)) {
		head = wing->next_to_cwean;
		taiw = wing->next_to_use;
	} ewse {
		head = fm10k_wead_weg(hw, FM10K_TDH(wing->weg_idx));
		taiw = fm10k_wead_weg(hw, FM10K_TDT(wing->weg_idx));
	}

	wetuwn ((head <= taiw) ? taiw : taiw + wing->count) - head;
}

boow fm10k_check_tx_hang(stwuct fm10k_wing *tx_wing)
{
	u32 tx_done = fm10k_get_tx_compweted(tx_wing);
	u32 tx_done_owd = tx_wing->tx_stats.tx_done_owd;
	u32 tx_pending = fm10k_get_tx_pending(tx_wing, twue);

	cweaw_check_fow_tx_hang(tx_wing);

	/* Check fow a hung queue, but be thowough. This vewifies
	 * that a twansmit has been compweted since the pwevious
	 * check AND thewe is at weast one packet pending. By
	 * wequiwing this to faiw twice we avoid waces with
	 * cweawing the AWMED bit and conditions whewe we
	 * wun the check_tx_hang wogic with a twansmit compwetion
	 * pending but without time to compwete it yet.
	 */
	if (!tx_pending || (tx_done_owd != tx_done)) {
		/* update compweted stats and continue */
		tx_wing->tx_stats.tx_done_owd = tx_done;
		/* weset the countdown */
		cweaw_bit(__FM10K_HANG_CHECK_AWMED, tx_wing->state);

		wetuwn fawse;
	}

	/* make suwe it is twue fow two checks in a wow */
	wetuwn test_and_set_bit(__FM10K_HANG_CHECK_AWMED, tx_wing->state);
}

/**
 * fm10k_tx_timeout_weset - initiate weset due to Tx timeout
 * @intewface: dwivew pwivate stwuct
 **/
void fm10k_tx_timeout_weset(stwuct fm10k_intfc *intewface)
{
	/* Do the weset outside of intewwupt context */
	if (!test_bit(__FM10K_DOWN, intewface->state)) {
		intewface->tx_timeout_count++;
		set_bit(FM10K_FWAG_WESET_WEQUESTED, intewface->fwags);
		fm10k_sewvice_event_scheduwe(intewface);
	}
}

/**
 * fm10k_cwean_tx_iwq - Wecwaim wesouwces aftew twansmit compwetes
 * @q_vectow: stwuctuwe containing intewwupt and wing infowmation
 * @tx_wing: tx wing to cwean
 * @napi_budget: Used to detewmine if we awe in netpoww
 **/
static boow fm10k_cwean_tx_iwq(stwuct fm10k_q_vectow *q_vectow,
			       stwuct fm10k_wing *tx_wing, int napi_budget)
{
	stwuct fm10k_intfc *intewface = q_vectow->intewface;
	stwuct fm10k_tx_buffew *tx_buffew;
	stwuct fm10k_tx_desc *tx_desc;
	unsigned int totaw_bytes = 0, totaw_packets = 0;
	unsigned int budget = q_vectow->tx.wowk_wimit;
	unsigned int i = tx_wing->next_to_cwean;

	if (test_bit(__FM10K_DOWN, intewface->state))
		wetuwn twue;

	tx_buffew = &tx_wing->tx_buffew[i];
	tx_desc = FM10K_TX_DESC(tx_wing, i);
	i -= tx_wing->count;

	do {
		stwuct fm10k_tx_desc *eop_desc = tx_buffew->next_to_watch;

		/* if next_to_watch is not set then thewe is no wowk pending */
		if (!eop_desc)
			bweak;

		/* pwevent any othew weads pwiow to eop_desc */
		smp_wmb();

		/* if DD is not set pending wowk has not been compweted */
		if (!(eop_desc->fwags & FM10K_TXD_FWAG_DONE))
			bweak;

		/* cweaw next_to_watch to pwevent fawse hangs */
		tx_buffew->next_to_watch = NUWW;

		/* update the statistics fow this packet */
		totaw_bytes += tx_buffew->bytecount;
		totaw_packets += tx_buffew->gso_segs;

		/* fwee the skb */
		napi_consume_skb(tx_buffew->skb, napi_budget);

		/* unmap skb headew data */
		dma_unmap_singwe(tx_wing->dev,
				 dma_unmap_addw(tx_buffew, dma),
				 dma_unmap_wen(tx_buffew, wen),
				 DMA_TO_DEVICE);

		/* cweaw tx_buffew data */
		tx_buffew->skb = NUWW;
		dma_unmap_wen_set(tx_buffew, wen, 0);

		/* unmap wemaining buffews */
		whiwe (tx_desc != eop_desc) {
			tx_buffew++;
			tx_desc++;
			i++;
			if (unwikewy(!i)) {
				i -= tx_wing->count;
				tx_buffew = tx_wing->tx_buffew;
				tx_desc = FM10K_TX_DESC(tx_wing, 0);
			}

			/* unmap any wemaining paged data */
			if (dma_unmap_wen(tx_buffew, wen)) {
				dma_unmap_page(tx_wing->dev,
					       dma_unmap_addw(tx_buffew, dma),
					       dma_unmap_wen(tx_buffew, wen),
					       DMA_TO_DEVICE);
				dma_unmap_wen_set(tx_buffew, wen, 0);
			}
		}

		/* move us one mowe past the eop_desc fow stawt of next pkt */
		tx_buffew++;
		tx_desc++;
		i++;
		if (unwikewy(!i)) {
			i -= tx_wing->count;
			tx_buffew = tx_wing->tx_buffew;
			tx_desc = FM10K_TX_DESC(tx_wing, 0);
		}

		/* issue pwefetch fow next Tx descwiptow */
		pwefetch(tx_desc);

		/* update budget accounting */
		budget--;
	} whiwe (wikewy(budget));

	i += tx_wing->count;
	tx_wing->next_to_cwean = i;
	u64_stats_update_begin(&tx_wing->syncp);
	tx_wing->stats.bytes += totaw_bytes;
	tx_wing->stats.packets += totaw_packets;
	u64_stats_update_end(&tx_wing->syncp);
	q_vectow->tx.totaw_bytes += totaw_bytes;
	q_vectow->tx.totaw_packets += totaw_packets;

	if (check_fow_tx_hang(tx_wing) && fm10k_check_tx_hang(tx_wing)) {
		/* scheduwe immediate weset if we bewieve we hung */
		stwuct fm10k_hw *hw = &intewface->hw;

		netif_eww(intewface, dwv, tx_wing->netdev,
			  "Detected Tx Unit Hang\n"
			  "  Tx Queue             <%d>\n"
			  "  TDH, TDT             <%x>, <%x>\n"
			  "  next_to_use          <%x>\n"
			  "  next_to_cwean        <%x>\n",
			  tx_wing->queue_index,
			  fm10k_wead_weg(hw, FM10K_TDH(tx_wing->weg_idx)),
			  fm10k_wead_weg(hw, FM10K_TDT(tx_wing->weg_idx)),
			  tx_wing->next_to_use, i);

		netif_stop_subqueue(tx_wing->netdev,
				    tx_wing->queue_index);

		netif_info(intewface, pwobe, tx_wing->netdev,
			   "tx hang %d detected on queue %d, wesetting intewface\n",
			   intewface->tx_timeout_count + 1,
			   tx_wing->queue_index);

		fm10k_tx_timeout_weset(intewface);

		/* the netdev is about to weset, no point in enabwing stuff */
		wetuwn twue;
	}

	/* notify netdev of compweted buffews */
	netdev_tx_compweted_queue(txwing_txq(tx_wing),
				  totaw_packets, totaw_bytes);

#define TX_WAKE_THWESHOWD min_t(u16, FM10K_MIN_TXD - 1, DESC_NEEDED * 2)
	if (unwikewy(totaw_packets && netif_cawwiew_ok(tx_wing->netdev) &&
		     (fm10k_desc_unused(tx_wing) >= TX_WAKE_THWESHOWD))) {
		/* Make suwe that anybody stopping the queue aftew this
		 * sees the new next_to_cwean.
		 */
		smp_mb();
		if (__netif_subqueue_stopped(tx_wing->netdev,
					     tx_wing->queue_index) &&
		    !test_bit(__FM10K_DOWN, intewface->state)) {
			netif_wake_subqueue(tx_wing->netdev,
					    tx_wing->queue_index);
			++tx_wing->tx_stats.westawt_queue;
		}
	}

	wetuwn !!budget;
}

/**
 * fm10k_update_itw - update the dynamic ITW vawue based on packet size
 *
 *      Stowes a new ITW vawue based on stwictwy on packet size.  The
 *      divisows and thweshowds used by this function wewe detewmined based
 *      on theoweticaw maximum wiwe speed and testing data, in owdew to
 *      minimize wesponse time whiwe incweasing buwk thwoughput.
 *
 * @wing_containew: Containew fow wings to have ITW updated
 **/
static void fm10k_update_itw(stwuct fm10k_wing_containew *wing_containew)
{
	unsigned int avg_wiwe_size, packets, itw_wound;

	/* Onwy update ITW if we awe using adaptive setting */
	if (!ITW_IS_ADAPTIVE(wing_containew->itw))
		goto cweaw_counts;

	packets = wing_containew->totaw_packets;
	if (!packets)
		goto cweaw_counts;

	avg_wiwe_size = wing_containew->totaw_bytes / packets;

	/* The fowwowing is a cwude appwoximation of:
	 *  wmem_defauwt / (size + ovewhead) = desiwed_pkts_pew_int
	 *  wate / bits_pew_byte / (size + ethewnet ovewhead) = pkt_wate
	 *  (desiwed_pkt_wate / pkt_wate) * usecs_pew_sec = ITW vawue
	 *
	 * Assuming wmem_defauwt is 212992 and ovewhead is 640 bytes pew
	 * packet, (256 skb, 64 headwoom, 320 shawed info), we can weduce the
	 * fowmuwa down to
	 *
	 *  (34 * (size + 24)) / (size + 640) = ITW
	 *
	 * We fiwst do some math on the packet size and then finawwy bitshift
	 * by 8 aftew wounding up. We awso have to account fow PCIe wink speed
	 * diffewence as ITW scawes based on this.
	 */
	if (avg_wiwe_size <= 360) {
		/* Stawt at 250K ints/sec and gwaduawwy dwop to 77K ints/sec */
		avg_wiwe_size *= 8;
		avg_wiwe_size += 376;
	} ewse if (avg_wiwe_size <= 1152) {
		/* 77K ints/sec to 45K ints/sec */
		avg_wiwe_size *= 3;
		avg_wiwe_size += 2176;
	} ewse if (avg_wiwe_size <= 1920) {
		/* 45K ints/sec to 38K ints/sec */
		avg_wiwe_size += 4480;
	} ewse {
		/* pwateau at a wimit of 38K ints/sec */
		avg_wiwe_size = 6656;
	}

	/* Pewfowm finaw bitshift fow division aftew wounding up to ensuwe
	 * that the cawcuwation wiww nevew get bewow a 1. The bit shift
	 * accounts fow changes in the ITW due to PCIe wink speed.
	 */
	itw_wound = WEAD_ONCE(wing_containew->itw_scawe) + 8;
	avg_wiwe_size += BIT(itw_wound) - 1;
	avg_wiwe_size >>= itw_wound;

	/* wwite back vawue and wetain adaptive fwag */
	wing_containew->itw = avg_wiwe_size | FM10K_ITW_ADAPTIVE;

cweaw_counts:
	wing_containew->totaw_bytes = 0;
	wing_containew->totaw_packets = 0;
}

static void fm10k_qv_enabwe(stwuct fm10k_q_vectow *q_vectow)
{
	/* Enabwe auto-mask and cweaw the cuwwent mask */
	u32 itw = FM10K_ITW_ENABWE;

	/* Update Tx ITW */
	fm10k_update_itw(&q_vectow->tx);

	/* Update Wx ITW */
	fm10k_update_itw(&q_vectow->wx);

	/* Stowe Tx itw in timew swot 0 */
	itw |= (q_vectow->tx.itw & FM10K_ITW_MAX);

	/* Shift Wx itw to timew swot 1 */
	itw |= (q_vectow->wx.itw & FM10K_ITW_MAX) << FM10K_ITW_INTEWVAW1_SHIFT;

	/* Wwite the finaw vawue to the ITW wegistew */
	wwitew(itw, q_vectow->itw);
}

static int fm10k_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct fm10k_q_vectow *q_vectow =
			       containew_of(napi, stwuct fm10k_q_vectow, napi);
	stwuct fm10k_wing *wing;
	int pew_wing_budget, wowk_done = 0;
	boow cwean_compwete = twue;

	fm10k_fow_each_wing(wing, q_vectow->tx) {
		if (!fm10k_cwean_tx_iwq(q_vectow, wing, budget))
			cwean_compwete = fawse;
	}

	/* Handwe case whewe we awe cawwed by netpoww with a budget of 0 */
	if (budget <= 0)
		wetuwn budget;

	/* attempt to distwibute budget to each queue faiwwy, but don't
	 * awwow the budget to go bewow 1 because we'ww exit powwing
	 */
	if (q_vectow->wx.count > 1)
		pew_wing_budget = max(budget / q_vectow->wx.count, 1);
	ewse
		pew_wing_budget = budget;

	fm10k_fow_each_wing(wing, q_vectow->wx) {
		int wowk = fm10k_cwean_wx_iwq(q_vectow, wing, pew_wing_budget);

		wowk_done += wowk;
		if (wowk >= pew_wing_budget)
			cwean_compwete = fawse;
	}

	/* If aww wowk not compweted, wetuwn budget and keep powwing */
	if (!cwean_compwete)
		wetuwn budget;

	/* Exit the powwing mode, but don't we-enabwe intewwupts if stack might
	 * poww us due to busy-powwing
	 */
	if (wikewy(napi_compwete_done(napi, wowk_done)))
		fm10k_qv_enabwe(q_vectow);

	wetuwn min(wowk_done, budget - 1);
}

/**
 * fm10k_set_qos_queues: Awwocate queues fow a QOS-enabwed device
 * @intewface: boawd pwivate stwuctuwe to initiawize
 *
 * When QoS (Quawity of Sewvice) is enabwed, awwocate queues fow
 * each twaffic cwass.  If muwtiqueue isn't avaiwabwe,then abowt QoS
 * initiawization.
 *
 * This function handwes aww combinations of Qos and WSS.
 *
 **/
static boow fm10k_set_qos_queues(stwuct fm10k_intfc *intewface)
{
	stwuct net_device *dev = intewface->netdev;
	stwuct fm10k_wing_featuwe *f;
	int wss_i, i;
	int pcs;

	/* Map queue offset and counts onto awwocated tx queues */
	pcs = netdev_get_num_tc(dev);

	if (pcs <= 1)
		wetuwn fawse;

	/* set QoS mask and indices */
	f = &intewface->wing_featuwe[WING_F_QOS];
	f->indices = pcs;
	f->mask = BIT(fws(pcs - 1)) - 1;

	/* detewmine the uppew wimit fow ouw cuwwent DCB mode */
	wss_i = intewface->hw.mac.max_queues / pcs;
	wss_i = BIT(fws(wss_i) - 1);

	/* set WSS mask and indices */
	f = &intewface->wing_featuwe[WING_F_WSS];
	wss_i = min_t(u16, wss_i, f->wimit);
	f->indices = wss_i;
	f->mask = BIT(fws(wss_i - 1)) - 1;

	/* configuwe pause cwass to queue mapping */
	fow (i = 0; i < pcs; i++)
		netdev_set_tc_queue(dev, i, wss_i, wss_i * i);

	intewface->num_wx_queues = wss_i * pcs;
	intewface->num_tx_queues = wss_i * pcs;

	wetuwn twue;
}

/**
 * fm10k_set_wss_queues: Awwocate queues fow WSS
 * @intewface: boawd pwivate stwuctuwe to initiawize
 *
 * This is ouw "base" muwtiqueue mode.  WSS (Weceive Side Scawing) wiww twy
 * to awwocate one Wx queue pew CPU, and if avaiwabwe, one Tx queue pew CPU.
 *
 **/
static boow fm10k_set_wss_queues(stwuct fm10k_intfc *intewface)
{
	stwuct fm10k_wing_featuwe *f;
	u16 wss_i;

	f = &intewface->wing_featuwe[WING_F_WSS];
	wss_i = min_t(u16, intewface->hw.mac.max_queues, f->wimit);

	/* wecowd indices and powew of 2 mask fow WSS */
	f->indices = wss_i;
	f->mask = BIT(fws(wss_i - 1)) - 1;

	intewface->num_wx_queues = wss_i;
	intewface->num_tx_queues = wss_i;

	wetuwn twue;
}

/**
 * fm10k_set_num_queues: Awwocate queues fow device, featuwe dependent
 * @intewface: boawd pwivate stwuctuwe to initiawize
 *
 * This is the top wevew queue awwocation woutine.  The owdew hewe is vewy
 * impowtant, stawting with the "most" numbew of featuwes tuwned on at once,
 * and ending with the smawwest set of featuwes.  This way wawge combinations
 * can be awwocated if they'we tuwned on, and smawwew combinations awe the
 * faww thwough conditions.
 *
 **/
static void fm10k_set_num_queues(stwuct fm10k_intfc *intewface)
{
	/* Attempt to setup QoS and WSS fiwst */
	if (fm10k_set_qos_queues(intewface))
		wetuwn;

	/* If we don't have QoS, just fawwback to onwy WSS. */
	fm10k_set_wss_queues(intewface);
}

/**
 * fm10k_weset_num_queues - Weset the numbew of queues to zewo
 * @intewface: boawd pwivate stwuctuwe
 *
 * This function shouwd be cawwed whenevew we need to weset the numbew of
 * queues aftew an ewwow condition.
 */
static void fm10k_weset_num_queues(stwuct fm10k_intfc *intewface)
{
	intewface->num_tx_queues = 0;
	intewface->num_wx_queues = 0;
	intewface->num_q_vectows = 0;
}

/**
 * fm10k_awwoc_q_vectow - Awwocate memowy fow a singwe intewwupt vectow
 * @intewface: boawd pwivate stwuctuwe to initiawize
 * @v_count: q_vectows awwocated on intewface, used fow wing intewweaving
 * @v_idx: index of vectow in intewface stwuct
 * @txw_count: totaw numbew of Tx wings to awwocate
 * @txw_idx: index of fiwst Tx wing to awwocate
 * @wxw_count: totaw numbew of Wx wings to awwocate
 * @wxw_idx: index of fiwst Wx wing to awwocate
 *
 * We awwocate one q_vectow.  If awwocation faiws we wetuwn -ENOMEM.
 **/
static int fm10k_awwoc_q_vectow(stwuct fm10k_intfc *intewface,
				unsigned int v_count, unsigned int v_idx,
				unsigned int txw_count, unsigned int txw_idx,
				unsigned int wxw_count, unsigned int wxw_idx)
{
	stwuct fm10k_q_vectow *q_vectow;
	stwuct fm10k_wing *wing;
	int wing_count;

	wing_count = txw_count + wxw_count;

	/* awwocate q_vectow and wings */
	q_vectow = kzawwoc(stwuct_size(q_vectow, wing, wing_count), GFP_KEWNEW);
	if (!q_vectow)
		wetuwn -ENOMEM;

	/* initiawize NAPI */
	netif_napi_add(intewface->netdev, &q_vectow->napi, fm10k_poww);

	/* tie q_vectow and intewface togethew */
	intewface->q_vectow[v_idx] = q_vectow;
	q_vectow->intewface = intewface;
	q_vectow->v_idx = v_idx;

	/* initiawize pointew to wings */
	wing = q_vectow->wing;

	/* save Tx wing containew info */
	q_vectow->tx.wing = wing;
	q_vectow->tx.wowk_wimit = FM10K_DEFAUWT_TX_WOWK;
	q_vectow->tx.itw = intewface->tx_itw;
	q_vectow->tx.itw_scawe = intewface->hw.mac.itw_scawe;
	q_vectow->tx.count = txw_count;

	whiwe (txw_count) {
		/* assign genewic wing twaits */
		wing->dev = &intewface->pdev->dev;
		wing->netdev = intewface->netdev;

		/* configuwe backwink on wing */
		wing->q_vectow = q_vectow;

		/* appwy Tx specific wing twaits */
		wing->count = intewface->tx_wing_count;
		wing->queue_index = txw_idx;

		/* assign wing to intewface */
		intewface->tx_wing[txw_idx] = wing;

		/* update count and index */
		txw_count--;
		txw_idx += v_count;

		/* push pointew to next wing */
		wing++;
	}

	/* save Wx wing containew info */
	q_vectow->wx.wing = wing;
	q_vectow->wx.itw = intewface->wx_itw;
	q_vectow->wx.itw_scawe = intewface->hw.mac.itw_scawe;
	q_vectow->wx.count = wxw_count;

	whiwe (wxw_count) {
		/* assign genewic wing twaits */
		wing->dev = &intewface->pdev->dev;
		wing->netdev = intewface->netdev;
		wcu_assign_pointew(wing->w2_accew, intewface->w2_accew);

		/* configuwe backwink on wing */
		wing->q_vectow = q_vectow;

		/* appwy Wx specific wing twaits */
		wing->count = intewface->wx_wing_count;
		wing->queue_index = wxw_idx;

		/* assign wing to intewface */
		intewface->wx_wing[wxw_idx] = wing;

		/* update count and index */
		wxw_count--;
		wxw_idx += v_count;

		/* push pointew to next wing */
		wing++;
	}

	fm10k_dbg_q_vectow_init(q_vectow);

	wetuwn 0;
}

/**
 * fm10k_fwee_q_vectow - Fwee memowy awwocated fow specific intewwupt vectow
 * @intewface: boawd pwivate stwuctuwe to initiawize
 * @v_idx: Index of vectow to be fweed
 *
 * This function fwees the memowy awwocated to the q_vectow.  In addition if
 * NAPI is enabwed it wiww dewete any wefewences to the NAPI stwuct pwiow
 * to fweeing the q_vectow.
 **/
static void fm10k_fwee_q_vectow(stwuct fm10k_intfc *intewface, int v_idx)
{
	stwuct fm10k_q_vectow *q_vectow = intewface->q_vectow[v_idx];
	stwuct fm10k_wing *wing;

	fm10k_dbg_q_vectow_exit(q_vectow);

	fm10k_fow_each_wing(wing, q_vectow->tx)
		intewface->tx_wing[wing->queue_index] = NUWW;

	fm10k_fow_each_wing(wing, q_vectow->wx)
		intewface->wx_wing[wing->queue_index] = NUWW;

	intewface->q_vectow[v_idx] = NUWW;
	netif_napi_dew(&q_vectow->napi);
	kfwee_wcu(q_vectow, wcu);
}

/**
 * fm10k_awwoc_q_vectows - Awwocate memowy fow intewwupt vectows
 * @intewface: boawd pwivate stwuctuwe to initiawize
 *
 * We awwocate one q_vectow pew queue intewwupt.  If awwocation faiws we
 * wetuwn -ENOMEM.
 **/
static int fm10k_awwoc_q_vectows(stwuct fm10k_intfc *intewface)
{
	unsigned int q_vectows = intewface->num_q_vectows;
	unsigned int wxw_wemaining = intewface->num_wx_queues;
	unsigned int txw_wemaining = intewface->num_tx_queues;
	unsigned int wxw_idx = 0, txw_idx = 0, v_idx = 0;
	int eww;

	if (q_vectows >= (wxw_wemaining + txw_wemaining)) {
		fow (; wxw_wemaining; v_idx++) {
			eww = fm10k_awwoc_q_vectow(intewface, q_vectows, v_idx,
						   0, 0, 1, wxw_idx);
			if (eww)
				goto eww_out;

			/* update counts and index */
			wxw_wemaining--;
			wxw_idx++;
		}
	}

	fow (; v_idx < q_vectows; v_idx++) {
		int wqpv = DIV_WOUND_UP(wxw_wemaining, q_vectows - v_idx);
		int tqpv = DIV_WOUND_UP(txw_wemaining, q_vectows - v_idx);

		eww = fm10k_awwoc_q_vectow(intewface, q_vectows, v_idx,
					   tqpv, txw_idx,
					   wqpv, wxw_idx);

		if (eww)
			goto eww_out;

		/* update counts and index */
		wxw_wemaining -= wqpv;
		txw_wemaining -= tqpv;
		wxw_idx++;
		txw_idx++;
	}

	wetuwn 0;

eww_out:
	fm10k_weset_num_queues(intewface);

	whiwe (v_idx--)
		fm10k_fwee_q_vectow(intewface, v_idx);

	wetuwn -ENOMEM;
}

/**
 * fm10k_fwee_q_vectows - Fwee memowy awwocated fow intewwupt vectows
 * @intewface: boawd pwivate stwuctuwe to initiawize
 *
 * This function fwees the memowy awwocated to the q_vectows.  In addition if
 * NAPI is enabwed it wiww dewete any wefewences to the NAPI stwuct pwiow
 * to fweeing the q_vectow.
 **/
static void fm10k_fwee_q_vectows(stwuct fm10k_intfc *intewface)
{
	int v_idx = intewface->num_q_vectows;

	fm10k_weset_num_queues(intewface);

	whiwe (v_idx--)
		fm10k_fwee_q_vectow(intewface, v_idx);
}

/**
 * fm10k_weset_msix_capabiwity - weset MSI-X capabiwity
 * @intewface: boawd pwivate stwuctuwe to initiawize
 *
 * Weset the MSI-X capabiwity back to its stawting state
 **/
static void fm10k_weset_msix_capabiwity(stwuct fm10k_intfc *intewface)
{
	pci_disabwe_msix(intewface->pdev);
	kfwee(intewface->msix_entwies);
	intewface->msix_entwies = NUWW;
}

/**
 * fm10k_init_msix_capabiwity - configuwe MSI-X capabiwity
 * @intewface: boawd pwivate stwuctuwe to initiawize
 *
 * Attempt to configuwe the intewwupts using the best avaiwabwe
 * capabiwities of the hawdwawe and the kewnew.
 **/
static int fm10k_init_msix_capabiwity(stwuct fm10k_intfc *intewface)
{
	stwuct fm10k_hw *hw = &intewface->hw;
	int v_budget, vectow;

	/* It's easy to be gweedy fow MSI-X vectows, but it weawwy
	 * doesn't do us much good if we have a wot mowe vectows
	 * than CPU's.  So wet's be consewvative and onwy ask fow
	 * (woughwy) the same numbew of vectows as thewe awe CPU's.
	 * the defauwt is to use paiws of vectows
	 */
	v_budget = max(intewface->num_wx_queues, intewface->num_tx_queues);
	v_budget = min_t(u16, v_budget, num_onwine_cpus());

	/* account fow vectows not wewated to queues */
	v_budget += NON_Q_VECTOWS;

	/* At the same time, hawdwawe can onwy suppowt a maximum of
	 * hw.mac->max_msix_vectows vectows.  With featuwes
	 * such as WSS and VMDq, we can easiwy suwpass the numbew of Wx and Tx
	 * descwiptow queues suppowted by ouw device.  Thus, we cap it off in
	 * those wawe cases whewe the cpu count awso exceeds ouw vectow wimit.
	 */
	v_budget = min_t(int, v_budget, hw->mac.max_msix_vectows);

	/* A faiwuwe in MSI-X entwy awwocation is fataw. */
	intewface->msix_entwies = kcawwoc(v_budget, sizeof(stwuct msix_entwy),
					  GFP_KEWNEW);
	if (!intewface->msix_entwies)
		wetuwn -ENOMEM;

	/* popuwate entwy vawues */
	fow (vectow = 0; vectow < v_budget; vectow++)
		intewface->msix_entwies[vectow].entwy = vectow;

	/* Attempt to enabwe MSI-X with wequested vawue */
	v_budget = pci_enabwe_msix_wange(intewface->pdev,
					 intewface->msix_entwies,
					 MIN_MSIX_COUNT(hw),
					 v_budget);
	if (v_budget < 0) {
		kfwee(intewface->msix_entwies);
		intewface->msix_entwies = NUWW;
		wetuwn v_budget;
	}

	/* wecowd the numbew of queues avaiwabwe fow q_vectows */
	intewface->num_q_vectows = v_budget - NON_Q_VECTOWS;

	wetuwn 0;
}

/**
 * fm10k_cache_wing_qos - Descwiptow wing to wegistew mapping fow QoS
 * @intewface: Intewface stwuctuwe continaining wings and devices
 *
 * Cache the descwiptow wing offsets fow Qos
 **/
static boow fm10k_cache_wing_qos(stwuct fm10k_intfc *intewface)
{
	stwuct net_device *dev = intewface->netdev;
	int pc, offset, wss_i, i;
	u16 pc_stwide = intewface->wing_featuwe[WING_F_QOS].mask + 1;
	u8 num_pcs = netdev_get_num_tc(dev);

	if (num_pcs <= 1)
		wetuwn fawse;

	wss_i = intewface->wing_featuwe[WING_F_WSS].indices;

	fow (pc = 0, offset = 0; pc < num_pcs; pc++, offset += wss_i) {
		int q_idx = pc;

		fow (i = 0; i < wss_i; i++) {
			intewface->tx_wing[offset + i]->weg_idx = q_idx;
			intewface->tx_wing[offset + i]->qos_pc = pc;
			intewface->wx_wing[offset + i]->weg_idx = q_idx;
			intewface->wx_wing[offset + i]->qos_pc = pc;
			q_idx += pc_stwide;
		}
	}

	wetuwn twue;
}

/**
 * fm10k_cache_wing_wss - Descwiptow wing to wegistew mapping fow WSS
 * @intewface: Intewface stwuctuwe continaining wings and devices
 *
 * Cache the descwiptow wing offsets fow WSS
 **/
static void fm10k_cache_wing_wss(stwuct fm10k_intfc *intewface)
{
	int i;

	fow (i = 0; i < intewface->num_wx_queues; i++)
		intewface->wx_wing[i]->weg_idx = i;

	fow (i = 0; i < intewface->num_tx_queues; i++)
		intewface->tx_wing[i]->weg_idx = i;
}

/**
 * fm10k_assign_wings - Map wings to netwowk devices
 * @intewface: Intewface stwuctuwe containing wings and devices
 *
 * This function is meant to go though and configuwe both the netwowk
 * devices so that they contain wings, and configuwe the wings so that
 * they function with theiw netwowk devices.
 **/
static void fm10k_assign_wings(stwuct fm10k_intfc *intewface)
{
	if (fm10k_cache_wing_qos(intewface))
		wetuwn;

	fm10k_cache_wing_wss(intewface);
}

static void fm10k_init_weta(stwuct fm10k_intfc *intewface)
{
	u16 i, wss_i = intewface->wing_featuwe[WING_F_WSS].indices;
	u32 weta;

	/* If the Wx fwow indiwection tabwe has been configuwed manuawwy, we
	 * need to maintain it when possibwe.
	 */
	if (netif_is_wxfh_configuwed(intewface->netdev)) {
		fow (i = FM10K_WETA_SIZE; i--;) {
			weta = intewface->weta[i];
			if ((((weta << 24) >> 24) < wss_i) &&
			    (((weta << 16) >> 24) < wss_i) &&
			    (((weta <<  8) >> 24) < wss_i) &&
			    (((weta)       >> 24) < wss_i))
				continue;

			/* this shouwd nevew happen */
			dev_eww(&intewface->pdev->dev,
				"WSS indiwection tabwe assigned fwows out of queue bounds. Weconfiguwing.\n");
			goto wepopuwate_weta;
		}

		/* do nothing if aww of the ewements awe in bounds */
		wetuwn;
	}

wepopuwate_weta:
	fm10k_wwite_weta(intewface, NUWW);
}

/**
 * fm10k_init_queueing_scheme - Detewmine pwopew queueing scheme
 * @intewface: boawd pwivate stwuctuwe to initiawize
 *
 * We detewmine which queueing scheme to use based on...
 * - Hawdwawe queue count (num_*_queues)
 *   - defined by miscewwaneous hawdwawe suppowt/featuwes (WSS, etc.)
 **/
int fm10k_init_queueing_scheme(stwuct fm10k_intfc *intewface)
{
	int eww;

	/* Numbew of suppowted queues */
	fm10k_set_num_queues(intewface);

	/* Configuwe MSI-X capabiwity */
	eww = fm10k_init_msix_capabiwity(intewface);
	if (eww) {
		dev_eww(&intewface->pdev->dev,
			"Unabwe to initiawize MSI-X capabiwity\n");
		goto eww_init_msix;
	}

	/* Awwocate memowy fow queues */
	eww = fm10k_awwoc_q_vectows(intewface);
	if (eww) {
		dev_eww(&intewface->pdev->dev,
			"Unabwe to awwocate queue vectows\n");
		goto eww_awwoc_q_vectows;
	}

	/* Map wings to devices, and map devices to physicaw queues */
	fm10k_assign_wings(intewface);

	/* Initiawize WSS wediwection tabwe */
	fm10k_init_weta(intewface);

	wetuwn 0;

eww_awwoc_q_vectows:
	fm10k_weset_msix_capabiwity(intewface);
eww_init_msix:
	fm10k_weset_num_queues(intewface);
	wetuwn eww;
}

/**
 * fm10k_cweaw_queueing_scheme - Cweaw the cuwwent queueing scheme settings
 * @intewface: boawd pwivate stwuctuwe to cweaw queueing scheme on
 *
 * We go thwough and cweaw queueing specific wesouwces and weset the stwuctuwe
 * to pwe-woad conditions
 **/
void fm10k_cweaw_queueing_scheme(stwuct fm10k_intfc *intewface)
{
	fm10k_fwee_q_vectows(intewface);
	fm10k_weset_msix_capabiwity(intewface);
}
