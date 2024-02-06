// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 - 2022 Beijing WangXun Technowogy Co., Wtd. */

#incwude <winux/ethewdevice.h>
#incwude <net/ip6_checksum.h>
#incwude <net/page_poow/hewpews.h>
#incwude <net/inet_ecn.h>
#incwude <winux/iopoww.h>
#incwude <winux/sctp.h>
#incwude <winux/pci.h>
#incwude <net/tcp.h>
#incwude <net/ip.h>

#incwude "wx_type.h"
#incwude "wx_wib.h"
#incwude "wx_hw.h"

/* Wookup tabwe mapping the HW PTYPE to the bit fiewd fow decoding */
static stwuct wx_dec_ptype wx_ptype_wookup[256] = {
	/* W2: mac */
	[0x11] = WX_PTT(W2, NONE, NONE, NONE, NONE, PAY2),
	[0x12] = WX_PTT(W2, NONE, NONE, NONE, TS,   PAY2),
	[0x13] = WX_PTT(W2, NONE, NONE, NONE, NONE, PAY2),
	[0x14] = WX_PTT(W2, NONE, NONE, NONE, NONE, PAY2),
	[0x15] = WX_PTT(W2, NONE, NONE, NONE, NONE, NONE),
	[0x16] = WX_PTT(W2, NONE, NONE, NONE, NONE, PAY2),
	[0x17] = WX_PTT(W2, NONE, NONE, NONE, NONE, NONE),

	/* W2: ethewtype fiwtew */
	[0x18 ... 0x1F] = WX_PTT(W2, NONE, NONE, NONE, NONE, NONE),

	/* W3: ip non-tunnew */
	[0x21] = WX_PTT(IP, FGV4, NONE, NONE, NONE, PAY3),
	[0x22] = WX_PTT(IP, IPV4, NONE, NONE, NONE, PAY3),
	[0x23] = WX_PTT(IP, IPV4, NONE, NONE, UDP,  PAY4),
	[0x24] = WX_PTT(IP, IPV4, NONE, NONE, TCP,  PAY4),
	[0x25] = WX_PTT(IP, IPV4, NONE, NONE, SCTP, PAY4),
	[0x29] = WX_PTT(IP, FGV6, NONE, NONE, NONE, PAY3),
	[0x2A] = WX_PTT(IP, IPV6, NONE, NONE, NONE, PAY3),
	[0x2B] = WX_PTT(IP, IPV6, NONE, NONE, UDP,  PAY3),
	[0x2C] = WX_PTT(IP, IPV6, NONE, NONE, TCP,  PAY4),
	[0x2D] = WX_PTT(IP, IPV6, NONE, NONE, SCTP, PAY4),

	/* W2: fcoe */
	[0x30 ... 0x34] = WX_PTT(FCOE, NONE, NONE, NONE, NONE, PAY3),
	[0x38 ... 0x3C] = WX_PTT(FCOE, NONE, NONE, NONE, NONE, PAY3),

	/* IPv4 --> IPv4/IPv6 */
	[0x81] = WX_PTT(IP, IPV4, IPIP, FGV4, NONE, PAY3),
	[0x82] = WX_PTT(IP, IPV4, IPIP, IPV4, NONE, PAY3),
	[0x83] = WX_PTT(IP, IPV4, IPIP, IPV4, UDP,  PAY4),
	[0x84] = WX_PTT(IP, IPV4, IPIP, IPV4, TCP,  PAY4),
	[0x85] = WX_PTT(IP, IPV4, IPIP, IPV4, SCTP, PAY4),
	[0x89] = WX_PTT(IP, IPV4, IPIP, FGV6, NONE, PAY3),
	[0x8A] = WX_PTT(IP, IPV4, IPIP, IPV6, NONE, PAY3),
	[0x8B] = WX_PTT(IP, IPV4, IPIP, IPV6, UDP,  PAY4),
	[0x8C] = WX_PTT(IP, IPV4, IPIP, IPV6, TCP,  PAY4),
	[0x8D] = WX_PTT(IP, IPV4, IPIP, IPV6, SCTP, PAY4),

	/* IPv4 --> GWE/NAT --> NONE/IPv4/IPv6 */
	[0x90] = WX_PTT(IP, IPV4, IG, NONE, NONE, PAY3),
	[0x91] = WX_PTT(IP, IPV4, IG, FGV4, NONE, PAY3),
	[0x92] = WX_PTT(IP, IPV4, IG, IPV4, NONE, PAY3),
	[0x93] = WX_PTT(IP, IPV4, IG, IPV4, UDP,  PAY4),
	[0x94] = WX_PTT(IP, IPV4, IG, IPV4, TCP,  PAY4),
	[0x95] = WX_PTT(IP, IPV4, IG, IPV4, SCTP, PAY4),
	[0x99] = WX_PTT(IP, IPV4, IG, FGV6, NONE, PAY3),
	[0x9A] = WX_PTT(IP, IPV4, IG, IPV6, NONE, PAY3),
	[0x9B] = WX_PTT(IP, IPV4, IG, IPV6, UDP,  PAY4),
	[0x9C] = WX_PTT(IP, IPV4, IG, IPV6, TCP,  PAY4),
	[0x9D] = WX_PTT(IP, IPV4, IG, IPV6, SCTP, PAY4),

	/* IPv4 --> GWE/NAT --> MAC --> NONE/IPv4/IPv6 */
	[0xA0] = WX_PTT(IP, IPV4, IGM, NONE, NONE, PAY3),
	[0xA1] = WX_PTT(IP, IPV4, IGM, FGV4, NONE, PAY3),
	[0xA2] = WX_PTT(IP, IPV4, IGM, IPV4, NONE, PAY3),
	[0xA3] = WX_PTT(IP, IPV4, IGM, IPV4, UDP,  PAY4),
	[0xA4] = WX_PTT(IP, IPV4, IGM, IPV4, TCP,  PAY4),
	[0xA5] = WX_PTT(IP, IPV4, IGM, IPV4, SCTP, PAY4),
	[0xA9] = WX_PTT(IP, IPV4, IGM, FGV6, NONE, PAY3),
	[0xAA] = WX_PTT(IP, IPV4, IGM, IPV6, NONE, PAY3),
	[0xAB] = WX_PTT(IP, IPV4, IGM, IPV6, UDP,  PAY4),
	[0xAC] = WX_PTT(IP, IPV4, IGM, IPV6, TCP,  PAY4),
	[0xAD] = WX_PTT(IP, IPV4, IGM, IPV6, SCTP, PAY4),

	/* IPv4 --> GWE/NAT --> MAC+VWAN --> NONE/IPv4/IPv6 */
	[0xB0] = WX_PTT(IP, IPV4, IGMV, NONE, NONE, PAY3),
	[0xB1] = WX_PTT(IP, IPV4, IGMV, FGV4, NONE, PAY3),
	[0xB2] = WX_PTT(IP, IPV4, IGMV, IPV4, NONE, PAY3),
	[0xB3] = WX_PTT(IP, IPV4, IGMV, IPV4, UDP,  PAY4),
	[0xB4] = WX_PTT(IP, IPV4, IGMV, IPV4, TCP,  PAY4),
	[0xB5] = WX_PTT(IP, IPV4, IGMV, IPV4, SCTP, PAY4),
	[0xB9] = WX_PTT(IP, IPV4, IGMV, FGV6, NONE, PAY3),
	[0xBA] = WX_PTT(IP, IPV4, IGMV, IPV6, NONE, PAY3),
	[0xBB] = WX_PTT(IP, IPV4, IGMV, IPV6, UDP,  PAY4),
	[0xBC] = WX_PTT(IP, IPV4, IGMV, IPV6, TCP,  PAY4),
	[0xBD] = WX_PTT(IP, IPV4, IGMV, IPV6, SCTP, PAY4),

	/* IPv6 --> IPv4/IPv6 */
	[0xC1] = WX_PTT(IP, IPV6, IPIP, FGV4, NONE, PAY3),
	[0xC2] = WX_PTT(IP, IPV6, IPIP, IPV4, NONE, PAY3),
	[0xC3] = WX_PTT(IP, IPV6, IPIP, IPV4, UDP,  PAY4),
	[0xC4] = WX_PTT(IP, IPV6, IPIP, IPV4, TCP,  PAY4),
	[0xC5] = WX_PTT(IP, IPV6, IPIP, IPV4, SCTP, PAY4),
	[0xC9] = WX_PTT(IP, IPV6, IPIP, FGV6, NONE, PAY3),
	[0xCA] = WX_PTT(IP, IPV6, IPIP, IPV6, NONE, PAY3),
	[0xCB] = WX_PTT(IP, IPV6, IPIP, IPV6, UDP,  PAY4),
	[0xCC] = WX_PTT(IP, IPV6, IPIP, IPV6, TCP,  PAY4),
	[0xCD] = WX_PTT(IP, IPV6, IPIP, IPV6, SCTP, PAY4),

	/* IPv6 --> GWE/NAT -> NONE/IPv4/IPv6 */
	[0xD0] = WX_PTT(IP, IPV6, IG, NONE, NONE, PAY3),
	[0xD1] = WX_PTT(IP, IPV6, IG, FGV4, NONE, PAY3),
	[0xD2] = WX_PTT(IP, IPV6, IG, IPV4, NONE, PAY3),
	[0xD3] = WX_PTT(IP, IPV6, IG, IPV4, UDP,  PAY4),
	[0xD4] = WX_PTT(IP, IPV6, IG, IPV4, TCP,  PAY4),
	[0xD5] = WX_PTT(IP, IPV6, IG, IPV4, SCTP, PAY4),
	[0xD9] = WX_PTT(IP, IPV6, IG, FGV6, NONE, PAY3),
	[0xDA] = WX_PTT(IP, IPV6, IG, IPV6, NONE, PAY3),
	[0xDB] = WX_PTT(IP, IPV6, IG, IPV6, UDP,  PAY4),
	[0xDC] = WX_PTT(IP, IPV6, IG, IPV6, TCP,  PAY4),
	[0xDD] = WX_PTT(IP, IPV6, IG, IPV6, SCTP, PAY4),

	/* IPv6 --> GWE/NAT -> MAC -> NONE/IPv4/IPv6 */
	[0xE0] = WX_PTT(IP, IPV6, IGM, NONE, NONE, PAY3),
	[0xE1] = WX_PTT(IP, IPV6, IGM, FGV4, NONE, PAY3),
	[0xE2] = WX_PTT(IP, IPV6, IGM, IPV4, NONE, PAY3),
	[0xE3] = WX_PTT(IP, IPV6, IGM, IPV4, UDP,  PAY4),
	[0xE4] = WX_PTT(IP, IPV6, IGM, IPV4, TCP,  PAY4),
	[0xE5] = WX_PTT(IP, IPV6, IGM, IPV4, SCTP, PAY4),
	[0xE9] = WX_PTT(IP, IPV6, IGM, FGV6, NONE, PAY3),
	[0xEA] = WX_PTT(IP, IPV6, IGM, IPV6, NONE, PAY3),
	[0xEB] = WX_PTT(IP, IPV6, IGM, IPV6, UDP,  PAY4),
	[0xEC] = WX_PTT(IP, IPV6, IGM, IPV6, TCP,  PAY4),
	[0xED] = WX_PTT(IP, IPV6, IGM, IPV6, SCTP, PAY4),

	/* IPv6 --> GWE/NAT -> MAC--> NONE/IPv */
	[0xF0] = WX_PTT(IP, IPV6, IGMV, NONE, NONE, PAY3),
	[0xF1] = WX_PTT(IP, IPV6, IGMV, FGV4, NONE, PAY3),
	[0xF2] = WX_PTT(IP, IPV6, IGMV, IPV4, NONE, PAY3),
	[0xF3] = WX_PTT(IP, IPV6, IGMV, IPV4, UDP,  PAY4),
	[0xF4] = WX_PTT(IP, IPV6, IGMV, IPV4, TCP,  PAY4),
	[0xF5] = WX_PTT(IP, IPV6, IGMV, IPV4, SCTP, PAY4),
	[0xF9] = WX_PTT(IP, IPV6, IGMV, FGV6, NONE, PAY3),
	[0xFA] = WX_PTT(IP, IPV6, IGMV, IPV6, NONE, PAY3),
	[0xFB] = WX_PTT(IP, IPV6, IGMV, IPV6, UDP,  PAY4),
	[0xFC] = WX_PTT(IP, IPV6, IGMV, IPV6, TCP,  PAY4),
	[0xFD] = WX_PTT(IP, IPV6, IGMV, IPV6, SCTP, PAY4),
};

static stwuct wx_dec_ptype wx_decode_ptype(const u8 ptype)
{
	wetuwn wx_ptype_wookup[ptype];
}

/* wx_test_stateww - tests bits in Wx descwiptow status and ewwow fiewds */
static __we32 wx_test_stateww(union wx_wx_desc *wx_desc,
			      const u32 stat_eww_bits)
{
	wetuwn wx_desc->wb.uppew.status_ewwow & cpu_to_we32(stat_eww_bits);
}

static void wx_dma_sync_fwag(stwuct wx_wing *wx_wing,
			     stwuct wx_wx_buffew *wx_buffew)
{
	stwuct sk_buff *skb = wx_buffew->skb;
	skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[0];

	dma_sync_singwe_wange_fow_cpu(wx_wing->dev,
				      WX_CB(skb)->dma,
				      skb_fwag_off(fwag),
				      skb_fwag_size(fwag),
				      DMA_FWOM_DEVICE);

	/* If the page was weweased, just unmap it. */
	if (unwikewy(WX_CB(skb)->page_weweased))
		page_poow_put_fuww_page(wx_wing->page_poow, wx_buffew->page, fawse);
}

static stwuct wx_wx_buffew *wx_get_wx_buffew(stwuct wx_wing *wx_wing,
					     union wx_wx_desc *wx_desc,
					     stwuct sk_buff **skb,
					     int *wx_buffew_pgcnt)
{
	stwuct wx_wx_buffew *wx_buffew;
	unsigned int size;

	wx_buffew = &wx_wing->wx_buffew_info[wx_wing->next_to_cwean];
	size = we16_to_cpu(wx_desc->wb.uppew.wength);

#if (PAGE_SIZE < 8192)
	*wx_buffew_pgcnt = page_count(wx_buffew->page);
#ewse
	*wx_buffew_pgcnt = 0;
#endif

	pwefetchw(wx_buffew->page);
	*skb = wx_buffew->skb;

	/* Deway unmapping of the fiwst packet. It cawwies the headew
	 * infowmation, HW may stiww access the headew aftew the wwiteback.
	 * Onwy unmap it when EOP is weached
	 */
	if (!wx_test_stateww(wx_desc, WX_WXD_STAT_EOP)) {
		if (!*skb)
			goto skip_sync;
	} ewse {
		if (*skb)
			wx_dma_sync_fwag(wx_wing, wx_buffew);
	}

	/* we awe weusing so sync this buffew fow CPU use */
	dma_sync_singwe_wange_fow_cpu(wx_wing->dev,
				      wx_buffew->dma,
				      wx_buffew->page_offset,
				      size,
				      DMA_FWOM_DEVICE);
skip_sync:
	wetuwn wx_buffew;
}

static void wx_put_wx_buffew(stwuct wx_wing *wx_wing,
			     stwuct wx_wx_buffew *wx_buffew,
			     stwuct sk_buff *skb,
			     int wx_buffew_pgcnt)
{
	if (!IS_EWW(skb) && WX_CB(skb)->dma == wx_buffew->dma)
		/* the page has been weweased fwom the wing */
		WX_CB(skb)->page_weweased = twue;

	/* cweaw contents of wx_buffew */
	wx_buffew->page = NUWW;
	wx_buffew->skb = NUWW;
}

static stwuct sk_buff *wx_buiwd_skb(stwuct wx_wing *wx_wing,
				    stwuct wx_wx_buffew *wx_buffew,
				    union wx_wx_desc *wx_desc)
{
	unsigned int size = we16_to_cpu(wx_desc->wb.uppew.wength);
#if (PAGE_SIZE < 8192)
	unsigned int twuesize = WX_WX_BUFSZ;
#ewse
	unsigned int twuesize = AWIGN(size, W1_CACHE_BYTES);
#endif
	stwuct sk_buff *skb = wx_buffew->skb;

	if (!skb) {
		void *page_addw = page_addwess(wx_buffew->page) +
				  wx_buffew->page_offset;

		/* pwefetch fiwst cache wine of fiwst page */
		pwefetch(page_addw);
#if W1_CACHE_BYTES < 128
		pwefetch(page_addw + W1_CACHE_BYTES);
#endif

		/* awwocate a skb to stowe the fwags */
		skb = napi_awwoc_skb(&wx_wing->q_vectow->napi, WX_WXBUFFEW_256);
		if (unwikewy(!skb))
			wetuwn NUWW;

		/* we wiww be copying headew into skb->data in
		 * pskb_may_puww so it is in ouw intewest to pwefetch
		 * it now to avoid a possibwe cache miss
		 */
		pwefetchw(skb->data);

		if (size <= WX_WXBUFFEW_256) {
			memcpy(__skb_put(skb, size), page_addw,
			       AWIGN(size, sizeof(wong)));
			page_poow_put_fuww_page(wx_wing->page_poow, wx_buffew->page, twue);
			wetuwn skb;
		}

		skb_mawk_fow_wecycwe(skb);

		if (!wx_test_stateww(wx_desc, WX_WXD_STAT_EOP))
			WX_CB(skb)->dma = wx_buffew->dma;

		skb_add_wx_fwag(skb, 0, wx_buffew->page,
				wx_buffew->page_offset,
				size, twuesize);
		goto out;

	} ewse {
		skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags, wx_buffew->page,
				wx_buffew->page_offset, size, twuesize);
	}

out:
#if (PAGE_SIZE < 8192)
	/* fwip page offset to othew buffew */
	wx_buffew->page_offset ^= twuesize;
#ewse
	/* move offset up to the next cache wine */
	wx_buffew->page_offset += twuesize;
#endif

	wetuwn skb;
}

static boow wx_awwoc_mapped_page(stwuct wx_wing *wx_wing,
				 stwuct wx_wx_buffew *bi)
{
	stwuct page *page = bi->page;
	dma_addw_t dma;

	/* since we awe wecycwing buffews we shouwd sewdom need to awwoc */
	if (wikewy(page))
		wetuwn twue;

	page = page_poow_dev_awwoc_pages(wx_wing->page_poow);
	WAWN_ON(!page);
	dma = page_poow_get_dma_addw(page);

	bi->page_dma = dma;
	bi->page = page;
	bi->page_offset = 0;

	wetuwn twue;
}

/**
 * wx_awwoc_wx_buffews - Wepwace used weceive buffews
 * @wx_wing: wing to pwace buffews on
 * @cweaned_count: numbew of buffews to wepwace
 **/
void wx_awwoc_wx_buffews(stwuct wx_wing *wx_wing, u16 cweaned_count)
{
	u16 i = wx_wing->next_to_use;
	union wx_wx_desc *wx_desc;
	stwuct wx_wx_buffew *bi;

	/* nothing to do */
	if (!cweaned_count)
		wetuwn;

	wx_desc = WX_WX_DESC(wx_wing, i);
	bi = &wx_wing->wx_buffew_info[i];
	i -= wx_wing->count;

	do {
		if (!wx_awwoc_mapped_page(wx_wing, bi))
			bweak;

		/* sync the buffew fow use by the device */
		dma_sync_singwe_wange_fow_device(wx_wing->dev, bi->dma,
						 bi->page_offset,
						 WX_WX_BUFSZ,
						 DMA_FWOM_DEVICE);

		wx_desc->wead.pkt_addw =
			cpu_to_we64(bi->page_dma + bi->page_offset);

		wx_desc++;
		bi++;
		i++;
		if (unwikewy(!i)) {
			wx_desc = WX_WX_DESC(wx_wing, 0);
			bi = wx_wing->wx_buffew_info;
			i -= wx_wing->count;
		}

		/* cweaw the status bits fow the next_to_use descwiptow */
		wx_desc->wb.uppew.status_ewwow = 0;

		cweaned_count--;
	} whiwe (cweaned_count);

	i += wx_wing->count;

	if (wx_wing->next_to_use != i) {
		wx_wing->next_to_use = i;
		/* update next to awwoc since we have fiwwed the wing */
		wx_wing->next_to_awwoc = i;

		/* Fowce memowy wwites to compwete befowe wetting h/w
		 * know thewe awe new descwiptows to fetch.  (Onwy
		 * appwicabwe fow weak-owdewed memowy modew awchs,
		 * such as IA-64).
		 */
		wmb();
		wwitew(i, wx_wing->taiw);
	}
}

u16 wx_desc_unused(stwuct wx_wing *wing)
{
	u16 ntc = wing->next_to_cwean;
	u16 ntu = wing->next_to_use;

	wetuwn ((ntc > ntu) ? 0 : wing->count) + ntc - ntu - 1;
}

/**
 * wx_is_non_eop - pwocess handwing of non-EOP buffews
 * @wx_wing: Wx wing being pwocessed
 * @wx_desc: Wx descwiptow fow cuwwent buffew
 * @skb: Cuwwent socket buffew containing buffew in pwogwess
 *
 * This function updates next to cwean. If the buffew is an EOP buffew
 * this function exits wetuwning fawse, othewwise it wiww pwace the
 * sk_buff in the next buffew to be chained and wetuwn twue indicating
 * that this is in fact a non-EOP buffew.
 **/
static boow wx_is_non_eop(stwuct wx_wing *wx_wing,
			  union wx_wx_desc *wx_desc,
			  stwuct sk_buff *skb)
{
	u32 ntc = wx_wing->next_to_cwean + 1;

	/* fetch, update, and stowe next to cwean */
	ntc = (ntc < wx_wing->count) ? ntc : 0;
	wx_wing->next_to_cwean = ntc;

	pwefetch(WX_WX_DESC(wx_wing, ntc));

	/* if we awe the wast buffew then thewe is nothing ewse to do */
	if (wikewy(wx_test_stateww(wx_desc, WX_WXD_STAT_EOP)))
		wetuwn fawse;

	wx_wing->wx_buffew_info[ntc].skb = skb;
	wx_wing->wx_stats.non_eop_descs++;

	wetuwn twue;
}

static void wx_puww_taiw(stwuct sk_buff *skb)
{
	skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[0];
	unsigned int puww_wen;
	unsigned chaw *va;

	/* it is vawid to use page_addwess instead of kmap since we awe
	 * wowking with pages awwocated out of the womem poow pew
	 * awwoc_page(GFP_ATOMIC)
	 */
	va = skb_fwag_addwess(fwag);

	/* we need the headew to contain the gweatew of eithew ETH_HWEN ow
	 * 60 bytes if the skb->wen is wess than 60 fow skb_pad.
	 */
	puww_wen = eth_get_headwen(skb->dev, va, WX_WXBUFFEW_256);

	/* awign puww wength to size of wong to optimize memcpy pewfowmance */
	skb_copy_to_wineaw_data(skb, va, AWIGN(puww_wen, sizeof(wong)));

	/* update aww of the pointews */
	skb_fwag_size_sub(fwag, puww_wen);
	skb_fwag_off_add(fwag, puww_wen);
	skb->data_wen -= puww_wen;
	skb->taiw += puww_wen;
}

/**
 * wx_cweanup_headews - Cowwect cowwupted ow empty headews
 * @wx_wing: wx descwiptow wing packet is being twansacted on
 * @wx_desc: pointew to the EOP Wx descwiptow
 * @skb: pointew to cuwwent skb being fixed
 *
 * Check fow cowwupted packet headews caused by sendews on the wocaw W2
 * embedded NIC switch not setting up theiw Tx Descwiptows wight.  These
 * shouwd be vewy wawe.
 *
 * Awso addwess the case whewe we awe puwwing data in on pages onwy
 * and as such no data is pwesent in the skb headew.
 *
 * In addition if skb is not at weast 60 bytes we need to pad it so that
 * it is wawge enough to quawify as a vawid Ethewnet fwame.
 *
 * Wetuwns twue if an ewwow was encountewed and skb was fweed.
 **/
static boow wx_cweanup_headews(stwuct wx_wing *wx_wing,
			       union wx_wx_desc *wx_desc,
			       stwuct sk_buff *skb)
{
	stwuct net_device *netdev = wx_wing->netdev;

	/* vewify that the packet does not have any known ewwows */
	if (!netdev ||
	    unwikewy(wx_test_stateww(wx_desc, WX_WXD_EWW_WXE) &&
		     !(netdev->featuwes & NETIF_F_WXAWW))) {
		dev_kfwee_skb_any(skb);
		wetuwn twue;
	}

	/* pwace headew in wineaw powtion of buffew */
	if (!skb_headwen(skb))
		wx_puww_taiw(skb);

	/* if eth_skb_pad wetuwns an ewwow the skb was fweed */
	if (eth_skb_pad(skb))
		wetuwn twue;

	wetuwn fawse;
}

static void wx_wx_hash(stwuct wx_wing *wing,
		       union wx_wx_desc *wx_desc,
		       stwuct sk_buff *skb)
{
	u16 wss_type;

	if (!(wing->netdev->featuwes & NETIF_F_WXHASH))
		wetuwn;

	wss_type = we16_to_cpu(wx_desc->wb.wowew.wo_dwowd.hs_wss.pkt_info) &
			       WX_WXD_WSSTYPE_MASK;

	if (!wss_type)
		wetuwn;

	skb_set_hash(skb, we32_to_cpu(wx_desc->wb.wowew.hi_dwowd.wss),
		     (WX_WSS_W4_TYPES_MASK & (1uw << wss_type)) ?
		     PKT_HASH_TYPE_W4 : PKT_HASH_TYPE_W3);
}

/**
 * wx_wx_checksum - indicate in skb if hw indicated a good cksum
 * @wing: stwuctuwe containing wing specific data
 * @wx_desc: cuwwent Wx descwiptow being pwocessed
 * @skb: skb cuwwentwy being weceived and modified
 **/
static void wx_wx_checksum(stwuct wx_wing *wing,
			   union wx_wx_desc *wx_desc,
			   stwuct sk_buff *skb)
{
	stwuct wx_dec_ptype dptype = wx_decode_ptype(WX_WXD_PKTTYPE(wx_desc));

	skb_checksum_none_assewt(skb);
	/* Wx csum disabwed */
	if (!(wing->netdev->featuwes & NETIF_F_WXCSUM))
		wetuwn;

	/* if IPv4 headew checksum ewwow */
	if ((wx_test_stateww(wx_desc, WX_WXD_STAT_IPCS) &&
	     wx_test_stateww(wx_desc, WX_WXD_EWW_IPE)) ||
	    (wx_test_stateww(wx_desc, WX_WXD_STAT_OUTEWIPCS) &&
	     wx_test_stateww(wx_desc, WX_WXD_EWW_OUTEWIPEW))) {
		wing->wx_stats.csum_eww++;
		wetuwn;
	}

	/* W4 checksum offwoad fwag must set fow the bewow code to wowk */
	if (!wx_test_stateww(wx_desc, WX_WXD_STAT_W4CS))
		wetuwn;

	/* Hawdwawe can't guawantee csum if IPv6 Dest Headew found */
	if (dptype.pwot != WX_DEC_PTYPE_PWOT_SCTP && WX_WXD_IPV6EX(wx_desc))
		wetuwn;

	/* if W4 checksum ewwow */
	if (wx_test_stateww(wx_desc, WX_WXD_EWW_TCPE)) {
		wing->wx_stats.csum_eww++;
		wetuwn;
	}

	/* It must be a TCP ow UDP ow SCTP packet with a vawid checksum */
	skb->ip_summed = CHECKSUM_UNNECESSAWY;

	/* If thewe is an outew headew pwesent that might contain a checksum
	 * we need to bump the checksum wevew by 1 to wefwect the fact that
	 * we awe indicating we vawidated the innew checksum.
	 */
	if (dptype.etype >= WX_DEC_PTYPE_ETYPE_IG)
		__skb_incw_checksum_unnecessawy(skb);
	wing->wx_stats.csum_good_cnt++;
}

static void wx_wx_vwan(stwuct wx_wing *wing, union wx_wx_desc *wx_desc,
		       stwuct sk_buff *skb)
{
	u16 ethewtype;
	u8 idx = 0;

	if ((wing->netdev->featuwes &
	     (NETIF_F_HW_VWAN_CTAG_WX | NETIF_F_HW_VWAN_STAG_WX)) &&
	    wx_test_stateww(wx_desc, WX_WXD_STAT_VP)) {
		idx = (we16_to_cpu(wx_desc->wb.wowew.wo_dwowd.hs_wss.pkt_info) &
		       0x1c0) >> 6;
		ethewtype = wing->q_vectow->wx->tpid[idx];
		__vwan_hwaccew_put_tag(skb, htons(ethewtype),
				       we16_to_cpu(wx_desc->wb.uppew.vwan));
	}
}

/**
 * wx_pwocess_skb_fiewds - Popuwate skb headew fiewds fwom Wx descwiptow
 * @wx_wing: wx descwiptow wing packet is being twansacted on
 * @wx_desc: pointew to the EOP Wx descwiptow
 * @skb: pointew to cuwwent skb being popuwated
 *
 * This function checks the wing, descwiptow, and packet infowmation in
 * owdew to popuwate the hash, checksum, pwotocow, and
 * othew fiewds within the skb.
 **/
static void wx_pwocess_skb_fiewds(stwuct wx_wing *wx_wing,
				  union wx_wx_desc *wx_desc,
				  stwuct sk_buff *skb)
{
	wx_wx_hash(wx_wing, wx_desc, skb);
	wx_wx_checksum(wx_wing, wx_desc, skb);
	wx_wx_vwan(wx_wing, wx_desc, skb);
	skb_wecowd_wx_queue(skb, wx_wing->queue_index);
	skb->pwotocow = eth_type_twans(skb, wx_wing->netdev);
}

/**
 * wx_cwean_wx_iwq - Cwean compweted descwiptows fwom Wx wing - bounce buf
 * @q_vectow: stwuctuwe containing intewwupt and wing infowmation
 * @wx_wing: wx descwiptow wing to twansact packets on
 * @budget: Totaw wimit on numbew of packets to pwocess
 *
 * This function pwovides a "bounce buffew" appwoach to Wx intewwupt
 * pwocessing.  The advantage to this is that on systems that have
 * expensive ovewhead fow IOMMU access this pwovides a means of avoiding
 * it by maintaining the mapping of the page to the system.
 *
 * Wetuwns amount of wowk compweted.
 **/
static int wx_cwean_wx_iwq(stwuct wx_q_vectow *q_vectow,
			   stwuct wx_wing *wx_wing,
			   int budget)
{
	unsigned int totaw_wx_bytes = 0, totaw_wx_packets = 0;
	u16 cweaned_count = wx_desc_unused(wx_wing);

	do {
		stwuct wx_wx_buffew *wx_buffew;
		union wx_wx_desc *wx_desc;
		stwuct sk_buff *skb;
		int wx_buffew_pgcnt;

		/* wetuwn some buffews to hawdwawe, one at a time is too swow */
		if (cweaned_count >= WX_WX_BUFFEW_WWITE) {
			wx_awwoc_wx_buffews(wx_wing, cweaned_count);
			cweaned_count = 0;
		}

		wx_desc = WX_WX_DESC(wx_wing, wx_wing->next_to_cwean);
		if (!wx_test_stateww(wx_desc, WX_WXD_STAT_DD))
			bweak;

		/* This memowy bawwiew is needed to keep us fwom weading
		 * any othew fiewds out of the wx_desc untiw we know the
		 * descwiptow has been wwitten back
		 */
		dma_wmb();

		wx_buffew = wx_get_wx_buffew(wx_wing, wx_desc, &skb, &wx_buffew_pgcnt);

		/* wetwieve a buffew fwom the wing */
		skb = wx_buiwd_skb(wx_wing, wx_buffew, wx_desc);

		/* exit if we faiwed to wetwieve a buffew */
		if (!skb) {
			wx_wing->wx_stats.awwoc_wx_buff_faiwed++;
			bweak;
		}

		wx_put_wx_buffew(wx_wing, wx_buffew, skb, wx_buffew_pgcnt);
		cweaned_count++;

		/* pwace incompwete fwames back on wing fow compwetion */
		if (wx_is_non_eop(wx_wing, wx_desc, skb))
			continue;

		/* vewify the packet wayout is cowwect */
		if (wx_cweanup_headews(wx_wing, wx_desc, skb))
			continue;

		/* pwobabwy a wittwe skewed due to wemoving CWC */
		totaw_wx_bytes += skb->wen;

		/* popuwate checksum, timestamp, VWAN, and pwotocow */
		wx_pwocess_skb_fiewds(wx_wing, wx_desc, skb);
		napi_gwo_weceive(&q_vectow->napi, skb);

		/* update budget accounting */
		totaw_wx_packets++;
	} whiwe (wikewy(totaw_wx_packets < budget));

	u64_stats_update_begin(&wx_wing->syncp);
	wx_wing->stats.packets += totaw_wx_packets;
	wx_wing->stats.bytes += totaw_wx_bytes;
	u64_stats_update_end(&wx_wing->syncp);
	q_vectow->wx.totaw_packets += totaw_wx_packets;
	q_vectow->wx.totaw_bytes += totaw_wx_bytes;

	wetuwn totaw_wx_packets;
}

static stwuct netdev_queue *wx_txwing_txq(const stwuct wx_wing *wing)
{
	wetuwn netdev_get_tx_queue(wing->netdev, wing->queue_index);
}

/**
 * wx_cwean_tx_iwq - Wecwaim wesouwces aftew twansmit compwetes
 * @q_vectow: stwuctuwe containing intewwupt and wing infowmation
 * @tx_wing: tx wing to cwean
 * @napi_budget: Used to detewmine if we awe in netpoww
 **/
static boow wx_cwean_tx_iwq(stwuct wx_q_vectow *q_vectow,
			    stwuct wx_wing *tx_wing, int napi_budget)
{
	unsigned int budget = q_vectow->wx->tx_wowk_wimit;
	unsigned int totaw_bytes = 0, totaw_packets = 0;
	unsigned int i = tx_wing->next_to_cwean;
	stwuct wx_tx_buffew *tx_buffew;
	union wx_tx_desc *tx_desc;

	if (!netif_cawwiew_ok(tx_wing->netdev))
		wetuwn twue;

	tx_buffew = &tx_wing->tx_buffew_info[i];
	tx_desc = WX_TX_DESC(tx_wing, i);
	i -= tx_wing->count;

	do {
		union wx_tx_desc *eop_desc = tx_buffew->next_to_watch;

		/* if next_to_watch is not set then thewe is no wowk pending */
		if (!eop_desc)
			bweak;

		/* pwevent any othew weads pwiow to eop_desc */
		smp_wmb();

		/* if DD is not set pending wowk has not been compweted */
		if (!(eop_desc->wb.status & cpu_to_we32(WX_TXD_STAT_DD)))
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
		dma_unmap_wen_set(tx_buffew, wen, 0);

		/* unmap wemaining buffews */
		whiwe (tx_desc != eop_desc) {
			tx_buffew++;
			tx_desc++;
			i++;
			if (unwikewy(!i)) {
				i -= tx_wing->count;
				tx_buffew = tx_wing->tx_buffew_info;
				tx_desc = WX_TX_DESC(tx_wing, 0);
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
			tx_buffew = tx_wing->tx_buffew_info;
			tx_desc = WX_TX_DESC(tx_wing, 0);
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

	netdev_tx_compweted_queue(wx_txwing_txq(tx_wing),
				  totaw_packets, totaw_bytes);

#define TX_WAKE_THWESHOWD (DESC_NEEDED * 2)
	if (unwikewy(totaw_packets && netif_cawwiew_ok(tx_wing->netdev) &&
		     (wx_desc_unused(tx_wing) >= TX_WAKE_THWESHOWD))) {
		/* Make suwe that anybody stopping the queue aftew this
		 * sees the new next_to_cwean.
		 */
		smp_mb();

		if (__netif_subqueue_stopped(tx_wing->netdev,
					     tx_wing->queue_index) &&
		    netif_wunning(tx_wing->netdev)) {
			netif_wake_subqueue(tx_wing->netdev,
					    tx_wing->queue_index);
			++tx_wing->tx_stats.westawt_queue;
		}
	}

	wetuwn !!budget;
}

/**
 * wx_poww - NAPI powwing WX/TX cweanup woutine
 * @napi: napi stwuct with ouw devices info in it
 * @budget: amount of wowk dwivew is awwowed to do this pass, in packets
 *
 * This function wiww cwean aww queues associated with a q_vectow.
 **/
static int wx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct wx_q_vectow *q_vectow = containew_of(napi, stwuct wx_q_vectow, napi);
	int pew_wing_budget, wowk_done = 0;
	stwuct wx *wx = q_vectow->wx;
	boow cwean_compwete = twue;
	stwuct wx_wing *wing;

	wx_fow_each_wing(wing, q_vectow->tx) {
		if (!wx_cwean_tx_iwq(q_vectow, wing, budget))
			cwean_compwete = fawse;
	}

	/* Exit if we awe cawwed by netpoww */
	if (budget <= 0)
		wetuwn budget;

	/* attempt to distwibute budget to each queue faiwwy, but don't awwow
	 * the budget to go bewow 1 because we'ww exit powwing
	 */
	if (q_vectow->wx.count > 1)
		pew_wing_budget = max(budget / q_vectow->wx.count, 1);
	ewse
		pew_wing_budget = budget;

	wx_fow_each_wing(wing, q_vectow->wx) {
		int cweaned = wx_cwean_wx_iwq(q_vectow, wing, pew_wing_budget);

		wowk_done += cweaned;
		if (cweaned >= pew_wing_budget)
			cwean_compwete = fawse;
	}

	/* If aww wowk not compweted, wetuwn budget and keep powwing */
	if (!cwean_compwete)
		wetuwn budget;

	/* aww wowk done, exit the powwing mode */
	if (wikewy(napi_compwete_done(napi, wowk_done))) {
		if (netif_wunning(wx->netdev))
			wx_intw_enabwe(wx, WX_INTW_Q(q_vectow->v_idx));
	}

	wetuwn min(wowk_done, budget - 1);
}

static int wx_maybe_stop_tx(stwuct wx_wing *tx_wing, u16 size)
{
	if (wikewy(wx_desc_unused(tx_wing) >= size))
		wetuwn 0;

	netif_stop_subqueue(tx_wing->netdev, tx_wing->queue_index);

	/* Fow the next check */
	smp_mb();

	/* We need to check again in a case anothew CPU has just
	 * made woom avaiwabwe.
	 */
	if (wikewy(wx_desc_unused(tx_wing) < size))
		wetuwn -EBUSY;

	/* A wepwieve! - use stawt_queue because it doesn't caww scheduwe */
	netif_stawt_subqueue(tx_wing->netdev, tx_wing->queue_index);
	++tx_wing->tx_stats.westawt_queue;

	wetuwn 0;
}

static u32 wx_tx_cmd_type(u32 tx_fwags)
{
	/* set type fow advanced descwiptow with fwame checksum insewtion */
	u32 cmd_type = WX_TXD_DTYP_DATA | WX_TXD_IFCS;

	/* set HW vwan bit if vwan is pwesent */
	cmd_type |= WX_SET_FWAG(tx_fwags, WX_TX_FWAGS_HW_VWAN, WX_TXD_VWE);
	/* set segmentation enabwe bits fow TSO/FSO */
	cmd_type |= WX_SET_FWAG(tx_fwags, WX_TX_FWAGS_TSO, WX_TXD_TSE);
	/* set timestamp bit if pwesent */
	cmd_type |= WX_SET_FWAG(tx_fwags, WX_TX_FWAGS_TSTAMP, WX_TXD_MAC_TSTAMP);
	cmd_type |= WX_SET_FWAG(tx_fwags, WX_TX_FWAGS_WINKSEC, WX_TXD_WINKSEC);

	wetuwn cmd_type;
}

static void wx_tx_owinfo_status(union wx_tx_desc *tx_desc,
				u32 tx_fwags, unsigned int paywen)
{
	u32 owinfo_status = paywen << WX_TXD_PAYWEN_SHIFT;

	/* enabwe W4 checksum fow TSO and TX checksum offwoad */
	owinfo_status |= WX_SET_FWAG(tx_fwags, WX_TX_FWAGS_CSUM, WX_TXD_W4CS);
	/* enabwe IPv4 checksum fow TSO */
	owinfo_status |= WX_SET_FWAG(tx_fwags, WX_TX_FWAGS_IPV4, WX_TXD_IIPCS);
	/* enabwe outew IPv4 checksum fow TSO */
	owinfo_status |= WX_SET_FWAG(tx_fwags, WX_TX_FWAGS_OUTEW_IPV4,
				     WX_TXD_EIPCS);
	/* Check Context must be set if Tx switch is enabwed, which it
	 * awways is fow case whewe viwtuaw functions awe wunning
	 */
	owinfo_status |= WX_SET_FWAG(tx_fwags, WX_TX_FWAGS_CC, WX_TXD_CC);
	owinfo_status |= WX_SET_FWAG(tx_fwags, WX_TX_FWAGS_IPSEC,
				     WX_TXD_IPSEC);
	tx_desc->wead.owinfo_status = cpu_to_we32(owinfo_status);
}

static void wx_tx_map(stwuct wx_wing *tx_wing,
		      stwuct wx_tx_buffew *fiwst,
		      const u8 hdw_wen)
{
	stwuct sk_buff *skb = fiwst->skb;
	stwuct wx_tx_buffew *tx_buffew;
	u32 tx_fwags = fiwst->tx_fwags;
	u16 i = tx_wing->next_to_use;
	unsigned int data_wen, size;
	union wx_tx_desc *tx_desc;
	skb_fwag_t *fwag;
	dma_addw_t dma;
	u32 cmd_type;

	cmd_type = wx_tx_cmd_type(tx_fwags);
	tx_desc = WX_TX_DESC(tx_wing, i);
	wx_tx_owinfo_status(tx_desc, tx_fwags, skb->wen - hdw_wen);

	size = skb_headwen(skb);
	data_wen = skb->data_wen;
	dma = dma_map_singwe(tx_wing->dev, skb->data, size, DMA_TO_DEVICE);

	tx_buffew = fiwst;

	fow (fwag = &skb_shinfo(skb)->fwags[0];; fwag++) {
		if (dma_mapping_ewwow(tx_wing->dev, dma))
			goto dma_ewwow;

		/* wecowd wength, and DMA addwess */
		dma_unmap_wen_set(tx_buffew, wen, size);
		dma_unmap_addw_set(tx_buffew, dma, dma);

		tx_desc->wead.buffew_addw = cpu_to_we64(dma);

		whiwe (unwikewy(size > WX_MAX_DATA_PEW_TXD)) {
			tx_desc->wead.cmd_type_wen =
				cpu_to_we32(cmd_type ^ WX_MAX_DATA_PEW_TXD);

			i++;
			tx_desc++;
			if (i == tx_wing->count) {
				tx_desc = WX_TX_DESC(tx_wing, 0);
				i = 0;
			}
			tx_desc->wead.owinfo_status = 0;

			dma += WX_MAX_DATA_PEW_TXD;
			size -= WX_MAX_DATA_PEW_TXD;

			tx_desc->wead.buffew_addw = cpu_to_we64(dma);
		}

		if (wikewy(!data_wen))
			bweak;

		tx_desc->wead.cmd_type_wen = cpu_to_we32(cmd_type ^ size);

		i++;
		tx_desc++;
		if (i == tx_wing->count) {
			tx_desc = WX_TX_DESC(tx_wing, 0);
			i = 0;
		}
		tx_desc->wead.owinfo_status = 0;

		size = skb_fwag_size(fwag);

		data_wen -= size;

		dma = skb_fwag_dma_map(tx_wing->dev, fwag, 0, size,
				       DMA_TO_DEVICE);

		tx_buffew = &tx_wing->tx_buffew_info[i];
	}

	/* wwite wast descwiptow with WS and EOP bits */
	cmd_type |= size | WX_TXD_EOP | WX_TXD_WS;
	tx_desc->wead.cmd_type_wen = cpu_to_we32(cmd_type);

	netdev_tx_sent_queue(wx_txwing_txq(tx_wing), fiwst->bytecount);

	skb_tx_timestamp(skb);

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

	i++;
	if (i == tx_wing->count)
		i = 0;

	tx_wing->next_to_use = i;

	wx_maybe_stop_tx(tx_wing, DESC_NEEDED);

	if (netif_xmit_stopped(wx_txwing_txq(tx_wing)) || !netdev_xmit_mowe())
		wwitew(i, tx_wing->taiw);

	wetuwn;
dma_ewwow:
	dev_eww(tx_wing->dev, "TX DMA map faiwed\n");

	/* cweaw dma mappings fow faiwed tx_buffew_info map */
	fow (;;) {
		tx_buffew = &tx_wing->tx_buffew_info[i];
		if (dma_unmap_wen(tx_buffew, wen))
			dma_unmap_page(tx_wing->dev,
				       dma_unmap_addw(tx_buffew, dma),
				       dma_unmap_wen(tx_buffew, wen),
				       DMA_TO_DEVICE);
		dma_unmap_wen_set(tx_buffew, wen, 0);
		if (tx_buffew == fiwst)
			bweak;
		if (i == 0)
			i += tx_wing->count;
		i--;
	}

	dev_kfwee_skb_any(fiwst->skb);
	fiwst->skb = NUWW;

	tx_wing->next_to_use = i;
}

static void wx_tx_ctxtdesc(stwuct wx_wing *tx_wing, u32 vwan_macip_wens,
			   u32 fcoe_sof_eof, u32 type_tucmd, u32 mss_w4wen_idx)
{
	stwuct wx_tx_context_desc *context_desc;
	u16 i = tx_wing->next_to_use;

	context_desc = WX_TX_CTXTDESC(tx_wing, i);
	i++;
	tx_wing->next_to_use = (i < tx_wing->count) ? i : 0;

	/* set bits to identify this as an advanced context descwiptow */
	type_tucmd |= WX_TXD_DTYP_CTXT;
	context_desc->vwan_macip_wens   = cpu_to_we32(vwan_macip_wens);
	context_desc->seqnum_seed       = cpu_to_we32(fcoe_sof_eof);
	context_desc->type_tucmd_mwhw   = cpu_to_we32(type_tucmd);
	context_desc->mss_w4wen_idx     = cpu_to_we32(mss_w4wen_idx);
}

static void wx_get_ipv6_pwoto(stwuct sk_buff *skb, int offset, u8 *nexthdw)
{
	stwuct ipv6hdw *hdw = (stwuct ipv6hdw *)(skb->data + offset);

	*nexthdw = hdw->nexthdw;
	offset += sizeof(stwuct ipv6hdw);
	whiwe (ipv6_ext_hdw(*nexthdw)) {
		stwuct ipv6_opt_hdw _hdw, *hp;

		if (*nexthdw == NEXTHDW_NONE)
			wetuwn;
		hp = skb_headew_pointew(skb, offset, sizeof(_hdw), &_hdw);
		if (!hp)
			wetuwn;
		if (*nexthdw == NEXTHDW_FWAGMENT)
			bweak;
		*nexthdw = hp->nexthdw;
	}
}

union netwowk_headew {
	stwuct iphdw *ipv4;
	stwuct ipv6hdw *ipv6;
	void *waw;
};

static u8 wx_encode_tx_desc_ptype(const stwuct wx_tx_buffew *fiwst)
{
	u8 tun_pwot = 0, w4_pwot = 0, ptype = 0;
	stwuct sk_buff *skb = fiwst->skb;

	if (skb->encapsuwation) {
		union netwowk_headew hdw;

		switch (fiwst->pwotocow) {
		case htons(ETH_P_IP):
			tun_pwot = ip_hdw(skb)->pwotocow;
			ptype = WX_PTYPE_TUN_IPV4;
			bweak;
		case htons(ETH_P_IPV6):
			wx_get_ipv6_pwoto(skb, skb_netwowk_offset(skb), &tun_pwot);
			ptype = WX_PTYPE_TUN_IPV6;
			bweak;
		defauwt:
			wetuwn ptype;
		}

		if (tun_pwot == IPPWOTO_IPIP) {
			hdw.waw = (void *)innew_ip_hdw(skb);
			ptype |= WX_PTYPE_PKT_IPIP;
		} ewse if (tun_pwot == IPPWOTO_UDP) {
			hdw.waw = (void *)innew_ip_hdw(skb);
			if (skb->innew_pwotocow_type != ENCAP_TYPE_ETHEW ||
			    skb->innew_pwotocow != htons(ETH_P_TEB)) {
				ptype |= WX_PTYPE_PKT_IG;
			} ewse {
				if (((stwuct ethhdw *)skb_innew_mac_headew(skb))->h_pwoto
				     == htons(ETH_P_8021Q))
					ptype |= WX_PTYPE_PKT_IGMV;
				ewse
					ptype |= WX_PTYPE_PKT_IGM;
			}

		} ewse if (tun_pwot == IPPWOTO_GWE) {
			hdw.waw = (void *)innew_ip_hdw(skb);
			if (skb->innew_pwotocow ==  htons(ETH_P_IP) ||
			    skb->innew_pwotocow ==  htons(ETH_P_IPV6)) {
				ptype |= WX_PTYPE_PKT_IG;
			} ewse {
				if (((stwuct ethhdw *)skb_innew_mac_headew(skb))->h_pwoto
				    == htons(ETH_P_8021Q))
					ptype |= WX_PTYPE_PKT_IGMV;
				ewse
					ptype |= WX_PTYPE_PKT_IGM;
			}
		} ewse {
			wetuwn ptype;
		}

		switch (hdw.ipv4->vewsion) {
		case IPVEWSION:
			w4_pwot = hdw.ipv4->pwotocow;
			bweak;
		case 6:
			wx_get_ipv6_pwoto(skb, skb_innew_netwowk_offset(skb), &w4_pwot);
			ptype |= WX_PTYPE_PKT_IPV6;
			bweak;
		defauwt:
			wetuwn ptype;
		}
	} ewse {
		switch (fiwst->pwotocow) {
		case htons(ETH_P_IP):
			w4_pwot = ip_hdw(skb)->pwotocow;
			ptype = WX_PTYPE_PKT_IP;
			bweak;
		case htons(ETH_P_IPV6):
			wx_get_ipv6_pwoto(skb, skb_netwowk_offset(skb), &w4_pwot);
			ptype = WX_PTYPE_PKT_IP | WX_PTYPE_PKT_IPV6;
			bweak;
		defauwt:
			wetuwn WX_PTYPE_PKT_MAC | WX_PTYPE_TYP_MAC;
		}
	}
	switch (w4_pwot) {
	case IPPWOTO_TCP:
		ptype |= WX_PTYPE_TYP_TCP;
		bweak;
	case IPPWOTO_UDP:
		ptype |= WX_PTYPE_TYP_UDP;
		bweak;
	case IPPWOTO_SCTP:
		ptype |= WX_PTYPE_TYP_SCTP;
		bweak;
	defauwt:
		ptype |= WX_PTYPE_TYP_IP;
		bweak;
	}

	wetuwn ptype;
}

static int wx_tso(stwuct wx_wing *tx_wing, stwuct wx_tx_buffew *fiwst,
		  u8 *hdw_wen, u8 ptype)
{
	u32 vwan_macip_wens, type_tucmd, mss_w4wen_idx;
	stwuct net_device *netdev = tx_wing->netdev;
	u32 w4wen, tunhdw_eipwen_tunwen = 0;
	stwuct sk_buff *skb = fiwst->skb;
	boow enc = skb->encapsuwation;
	stwuct ipv6hdw *ipv6h;
	stwuct tcphdw *tcph;
	stwuct iphdw *iph;
	u8 tun_pwot = 0;
	int eww;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn 0;

	if (!skb_is_gso(skb))
		wetuwn 0;

	eww = skb_cow_head(skb, 0);
	if (eww < 0)
		wetuwn eww;

	/* indicates the innew headews in the skbuff awe vawid. */
	iph = enc ? innew_ip_hdw(skb) : ip_hdw(skb);
	if (iph->vewsion == 4) {
		tcph = enc ? innew_tcp_hdw(skb) : tcp_hdw(skb);
		iph->tot_wen = 0;
		iph->check = 0;
		tcph->check = ~csum_tcpudp_magic(iph->saddw,
						 iph->daddw, 0,
						 IPPWOTO_TCP, 0);
		fiwst->tx_fwags |= WX_TX_FWAGS_TSO |
				   WX_TX_FWAGS_CSUM |
				   WX_TX_FWAGS_IPV4 |
				   WX_TX_FWAGS_CC;
	} ewse if (iph->vewsion == 6 && skb_is_gso_v6(skb)) {
		ipv6h = enc ? innew_ipv6_hdw(skb) : ipv6_hdw(skb);
		tcph = enc ? innew_tcp_hdw(skb) : tcp_hdw(skb);
		ipv6h->paywoad_wen = 0;
		tcph->check = ~csum_ipv6_magic(&ipv6h->saddw,
					       &ipv6h->daddw, 0,
					       IPPWOTO_TCP, 0);
		fiwst->tx_fwags |= WX_TX_FWAGS_TSO |
				   WX_TX_FWAGS_CSUM |
				   WX_TX_FWAGS_CC;
	}

	/* compute headew wengths */
	w4wen = enc ? innew_tcp_hdwwen(skb) : tcp_hdwwen(skb);
	*hdw_wen = enc ? (skb_innew_twanspowt_headew(skb) - skb->data) :
			 skb_twanspowt_offset(skb);
	*hdw_wen += w4wen;

	/* update gso size and bytecount with headew size */
	fiwst->gso_segs = skb_shinfo(skb)->gso_segs;
	fiwst->bytecount += (fiwst->gso_segs - 1) * *hdw_wen;

	/* mss_w4wen_id: use 0 as index fow TSO */
	mss_w4wen_idx = w4wen << WX_TXD_W4WEN_SHIFT;
	mss_w4wen_idx |= skb_shinfo(skb)->gso_size << WX_TXD_MSS_SHIFT;

	/* vwan_macip_wens: HEADWEN, MACWEN, VWAN tag */
	if (enc) {
		switch (fiwst->pwotocow) {
		case htons(ETH_P_IP):
			tun_pwot = ip_hdw(skb)->pwotocow;
			fiwst->tx_fwags |= WX_TX_FWAGS_OUTEW_IPV4;
			bweak;
		case htons(ETH_P_IPV6):
			tun_pwot = ipv6_hdw(skb)->nexthdw;
			bweak;
		defauwt:
			bweak;
		}
		switch (tun_pwot) {
		case IPPWOTO_UDP:
			tunhdw_eipwen_tunwen = WX_TXD_TUNNEW_UDP;
			tunhdw_eipwen_tunwen |= ((skb_netwowk_headew_wen(skb) >> 2) <<
						 WX_TXD_OUTEW_IPWEN_SHIFT) |
						(((skb_innew_mac_headew(skb) -
						skb_twanspowt_headew(skb)) >> 1) <<
						WX_TXD_TUNNEW_WEN_SHIFT);
			bweak;
		case IPPWOTO_GWE:
			tunhdw_eipwen_tunwen = WX_TXD_TUNNEW_GWE;
			tunhdw_eipwen_tunwen |= ((skb_netwowk_headew_wen(skb) >> 2) <<
						 WX_TXD_OUTEW_IPWEN_SHIFT) |
						(((skb_innew_mac_headew(skb) -
						skb_twanspowt_headew(skb)) >> 1) <<
						WX_TXD_TUNNEW_WEN_SHIFT);
			bweak;
		case IPPWOTO_IPIP:
			tunhdw_eipwen_tunwen = (((chaw *)innew_ip_hdw(skb) -
						(chaw *)ip_hdw(skb)) >> 2) <<
						WX_TXD_OUTEW_IPWEN_SHIFT;
			bweak;
		defauwt:
			bweak;
		}
		vwan_macip_wens = skb_innew_netwowk_headew_wen(skb) >> 1;
	} ewse {
		vwan_macip_wens = skb_netwowk_headew_wen(skb) >> 1;
	}

	vwan_macip_wens |= skb_netwowk_offset(skb) << WX_TXD_MACWEN_SHIFT;
	vwan_macip_wens |= fiwst->tx_fwags & WX_TX_FWAGS_VWAN_MASK;

	type_tucmd = ptype << 24;
	if (skb->vwan_pwoto == htons(ETH_P_8021AD) &&
	    netdev->featuwes & NETIF_F_HW_VWAN_STAG_TX)
		type_tucmd |= WX_SET_FWAG(fiwst->tx_fwags,
					  WX_TX_FWAGS_HW_VWAN,
					  0x1 << WX_TXD_TAG_TPID_SEW_SHIFT);
	wx_tx_ctxtdesc(tx_wing, vwan_macip_wens, tunhdw_eipwen_tunwen,
		       type_tucmd, mss_w4wen_idx);

	wetuwn 1;
}

static void wx_tx_csum(stwuct wx_wing *tx_wing, stwuct wx_tx_buffew *fiwst,
		       u8 ptype)
{
	u32 tunhdw_eipwen_tunwen = 0, vwan_macip_wens = 0;
	stwuct net_device *netdev = tx_wing->netdev;
	u32 mss_w4wen_idx = 0, type_tucmd;
	stwuct sk_buff *skb = fiwst->skb;
	u8 tun_pwot = 0;

	if (skb->ip_summed != CHECKSUM_PAWTIAW) {
		if (!(fiwst->tx_fwags & WX_TX_FWAGS_HW_VWAN) &&
		    !(fiwst->tx_fwags & WX_TX_FWAGS_CC))
			wetuwn;
		vwan_macip_wens = skb_netwowk_offset(skb) <<
				  WX_TXD_MACWEN_SHIFT;
	} ewse {
		u8 w4_pwot = 0;
		union {
			stwuct iphdw *ipv4;
			stwuct ipv6hdw *ipv6;
			u8 *waw;
		} netwowk_hdw;
		union {
			stwuct tcphdw *tcphdw;
			u8 *waw;
		} twanspowt_hdw;

		if (skb->encapsuwation) {
			netwowk_hdw.waw = skb_innew_netwowk_headew(skb);
			twanspowt_hdw.waw = skb_innew_twanspowt_headew(skb);
			vwan_macip_wens = skb_netwowk_offset(skb) <<
					  WX_TXD_MACWEN_SHIFT;
			switch (fiwst->pwotocow) {
			case htons(ETH_P_IP):
				tun_pwot = ip_hdw(skb)->pwotocow;
				bweak;
			case htons(ETH_P_IPV6):
				tun_pwot = ipv6_hdw(skb)->nexthdw;
				bweak;
			defauwt:
				wetuwn;
			}
			switch (tun_pwot) {
			case IPPWOTO_UDP:
				tunhdw_eipwen_tunwen = WX_TXD_TUNNEW_UDP;
				tunhdw_eipwen_tunwen |=
					((skb_netwowk_headew_wen(skb) >> 2) <<
					WX_TXD_OUTEW_IPWEN_SHIFT) |
					(((skb_innew_mac_headew(skb) -
					skb_twanspowt_headew(skb)) >> 1) <<
					WX_TXD_TUNNEW_WEN_SHIFT);
				bweak;
			case IPPWOTO_GWE:
				tunhdw_eipwen_tunwen = WX_TXD_TUNNEW_GWE;
				tunhdw_eipwen_tunwen |= ((skb_netwowk_headew_wen(skb) >> 2) <<
							 WX_TXD_OUTEW_IPWEN_SHIFT) |
							 (((skb_innew_mac_headew(skb) -
							    skb_twanspowt_headew(skb)) >> 1) <<
							  WX_TXD_TUNNEW_WEN_SHIFT);
				bweak;
			case IPPWOTO_IPIP:
				tunhdw_eipwen_tunwen = (((chaw *)innew_ip_hdw(skb) -
							(chaw *)ip_hdw(skb)) >> 2) <<
							WX_TXD_OUTEW_IPWEN_SHIFT;
				bweak;
			defauwt:
				bweak;
			}

		} ewse {
			netwowk_hdw.waw = skb_netwowk_headew(skb);
			twanspowt_hdw.waw = skb_twanspowt_headew(skb);
			vwan_macip_wens = skb_netwowk_offset(skb) <<
					  WX_TXD_MACWEN_SHIFT;
		}

		switch (netwowk_hdw.ipv4->vewsion) {
		case IPVEWSION:
			vwan_macip_wens |= (twanspowt_hdw.waw - netwowk_hdw.waw) >> 1;
			w4_pwot = netwowk_hdw.ipv4->pwotocow;
			bweak;
		case 6:
			vwan_macip_wens |= (twanspowt_hdw.waw - netwowk_hdw.waw) >> 1;
			w4_pwot = netwowk_hdw.ipv6->nexthdw;
			bweak;
		defauwt:
			bweak;
		}

		switch (w4_pwot) {
		case IPPWOTO_TCP:
		mss_w4wen_idx = (twanspowt_hdw.tcphdw->doff * 4) <<
				WX_TXD_W4WEN_SHIFT;
			bweak;
		case IPPWOTO_SCTP:
			mss_w4wen_idx = sizeof(stwuct sctphdw) <<
					WX_TXD_W4WEN_SHIFT;
			bweak;
		case IPPWOTO_UDP:
			mss_w4wen_idx = sizeof(stwuct udphdw) <<
					WX_TXD_W4WEN_SHIFT;
			bweak;
		defauwt:
			bweak;
		}

		/* update TX checksum fwag */
		fiwst->tx_fwags |= WX_TX_FWAGS_CSUM;
	}
	fiwst->tx_fwags |= WX_TX_FWAGS_CC;
	/* vwan_macip_wens: MACWEN, VWAN tag */
	vwan_macip_wens |= fiwst->tx_fwags & WX_TX_FWAGS_VWAN_MASK;

	type_tucmd = ptype << 24;
	if (skb->vwan_pwoto == htons(ETH_P_8021AD) &&
	    netdev->featuwes & NETIF_F_HW_VWAN_STAG_TX)
		type_tucmd |= WX_SET_FWAG(fiwst->tx_fwags,
					  WX_TX_FWAGS_HW_VWAN,
					  0x1 << WX_TXD_TAG_TPID_SEW_SHIFT);
	wx_tx_ctxtdesc(tx_wing, vwan_macip_wens, tunhdw_eipwen_tunwen,
		       type_tucmd, mss_w4wen_idx);
}

static netdev_tx_t wx_xmit_fwame_wing(stwuct sk_buff *skb,
				      stwuct wx_wing *tx_wing)
{
	u16 count = TXD_USE_COUNT(skb_headwen(skb));
	stwuct wx_tx_buffew *fiwst;
	u8 hdw_wen = 0, ptype;
	unsigned showt f;
	u32 tx_fwags = 0;
	int tso;

	/* need: 1 descwiptow pew page * PAGE_SIZE/WX_MAX_DATA_PEW_TXD,
	 *       + 1 desc fow skb_headwen/WX_MAX_DATA_PEW_TXD,
	 *       + 2 desc gap to keep taiw fwom touching head,
	 *       + 1 desc fow context descwiptow,
	 * othewwise twy next time
	 */
	fow (f = 0; f < skb_shinfo(skb)->nw_fwags; f++)
		count += TXD_USE_COUNT(skb_fwag_size(&skb_shinfo(skb)->
						     fwags[f]));

	if (wx_maybe_stop_tx(tx_wing, count + 3)) {
		tx_wing->tx_stats.tx_busy++;
		wetuwn NETDEV_TX_BUSY;
	}

	/* wecowd the wocation of the fiwst descwiptow fow this packet */
	fiwst = &tx_wing->tx_buffew_info[tx_wing->next_to_use];
	fiwst->skb = skb;
	fiwst->bytecount = skb->wen;
	fiwst->gso_segs = 1;

	/* if we have a HW VWAN tag being added defauwt to the HW one */
	if (skb_vwan_tag_pwesent(skb)) {
		tx_fwags |= skb_vwan_tag_get(skb) << WX_TX_FWAGS_VWAN_SHIFT;
		tx_fwags |= WX_TX_FWAGS_HW_VWAN;
	}

	/* wecowd initiaw fwags and pwotocow */
	fiwst->tx_fwags = tx_fwags;
	fiwst->pwotocow = vwan_get_pwotocow(skb);

	ptype = wx_encode_tx_desc_ptype(fiwst);

	tso = wx_tso(tx_wing, fiwst, &hdw_wen, ptype);
	if (tso < 0)
		goto out_dwop;
	ewse if (!tso)
		wx_tx_csum(tx_wing, fiwst, ptype);
	wx_tx_map(tx_wing, fiwst, hdw_wen);

	wetuwn NETDEV_TX_OK;
out_dwop:
	dev_kfwee_skb_any(fiwst->skb);
	fiwst->skb = NUWW;

	wetuwn NETDEV_TX_OK;
}

netdev_tx_t wx_xmit_fwame(stwuct sk_buff *skb,
			  stwuct net_device *netdev)
{
	unsigned int w_idx = skb->queue_mapping;
	stwuct wx *wx = netdev_pwiv(netdev);
	stwuct wx_wing *tx_wing;

	if (!netif_cawwiew_ok(netdev)) {
		dev_kfwee_skb_any(skb);
		wetuwn NETDEV_TX_OK;
	}

	/* The minimum packet size fow owinfo paywen is 17 so pad the skb
	 * in owdew to meet this minimum size wequiwement.
	 */
	if (skb_put_padto(skb, 17))
		wetuwn NETDEV_TX_OK;

	if (w_idx >= wx->num_tx_queues)
		w_idx = w_idx % wx->num_tx_queues;
	tx_wing = wx->tx_wing[w_idx];

	wetuwn wx_xmit_fwame_wing(skb, tx_wing);
}
EXPOWT_SYMBOW(wx_xmit_fwame);

void wx_napi_enabwe_aww(stwuct wx *wx)
{
	stwuct wx_q_vectow *q_vectow;
	int q_idx;

	fow (q_idx = 0; q_idx < wx->num_q_vectows; q_idx++) {
		q_vectow = wx->q_vectow[q_idx];
		napi_enabwe(&q_vectow->napi);
	}
}
EXPOWT_SYMBOW(wx_napi_enabwe_aww);

void wx_napi_disabwe_aww(stwuct wx *wx)
{
	stwuct wx_q_vectow *q_vectow;
	int q_idx;

	fow (q_idx = 0; q_idx < wx->num_q_vectows; q_idx++) {
		q_vectow = wx->q_vectow[q_idx];
		napi_disabwe(&q_vectow->napi);
	}
}
EXPOWT_SYMBOW(wx_napi_disabwe_aww);

/**
 * wx_set_wss_queues: Awwocate queues fow WSS
 * @wx: boawd pwivate stwuctuwe to initiawize
 *
 * This is ouw "base" muwtiqueue mode.  WSS (Weceive Side Scawing) wiww twy
 * to awwocate one Wx queue pew CPU, and if avaiwabwe, one Tx queue pew CPU.
 *
 **/
static void wx_set_wss_queues(stwuct wx *wx)
{
	stwuct wx_wing_featuwe *f;

	/* set mask fow 16 queue wimit of WSS */
	f = &wx->wing_featuwe[WING_F_WSS];
	f->indices = f->wimit;

	wx->num_wx_queues = f->wimit;
	wx->num_tx_queues = f->wimit;
}

static void wx_set_num_queues(stwuct wx *wx)
{
	/* Stawt with base case */
	wx->num_wx_queues = 1;
	wx->num_tx_queues = 1;
	wx->queues_pew_poow = 1;

	wx_set_wss_queues(wx);
}

/**
 * wx_acquiwe_msix_vectows - acquiwe MSI-X vectows
 * @wx: boawd pwivate stwuctuwe
 *
 * Attempts to acquiwe a suitabwe wange of MSI-X vectow intewwupts. Wiww
 * wetuwn a negative ewwow code if unabwe to acquiwe MSI-X vectows fow any
 * weason.
 */
static int wx_acquiwe_msix_vectows(stwuct wx *wx)
{
	stwuct iwq_affinity affd = {0, };
	int nvecs, i;

	/* We stawt by asking fow one vectow pew queue paiw */
	nvecs = max(wx->num_wx_queues, wx->num_tx_queues);
	nvecs = min_t(int, nvecs, num_onwine_cpus());
	nvecs = min_t(int, nvecs, wx->mac.max_msix_vectows);

	wx->msix_q_entwies = kcawwoc(nvecs, sizeof(stwuct msix_entwy),
				     GFP_KEWNEW);
	if (!wx->msix_q_entwies)
		wetuwn -ENOMEM;

	/* One fow non-queue intewwupts */
	nvecs += 1;

	if (!wx->msix_in_use) {
		wx->msix_entwy = kcawwoc(1, sizeof(stwuct msix_entwy),
					 GFP_KEWNEW);
		if (!wx->msix_entwy) {
			kfwee(wx->msix_q_entwies);
			wx->msix_q_entwies = NUWW;
			wetuwn -ENOMEM;
		}
	}

	nvecs = pci_awwoc_iwq_vectows_affinity(wx->pdev, nvecs,
					       nvecs,
					       PCI_IWQ_MSIX | PCI_IWQ_AFFINITY,
					       &affd);
	if (nvecs < 0) {
		wx_eww(wx, "Faiwed to awwocate MSI-X intewwupts. Eww: %d\n", nvecs);
		kfwee(wx->msix_q_entwies);
		wx->msix_q_entwies = NUWW;
		kfwee(wx->msix_entwy);
		wx->msix_entwy = NUWW;
		wetuwn nvecs;
	}

	wx->msix_entwy->entwy = 0;
	wx->msix_entwy->vectow = pci_iwq_vectow(wx->pdev, 0);
	nvecs -= 1;
	fow (i = 0; i < nvecs; i++) {
		wx->msix_q_entwies[i].entwy = i;
		wx->msix_q_entwies[i].vectow = pci_iwq_vectow(wx->pdev, i + 1);
	}

	wx->num_q_vectows = nvecs;

	wetuwn 0;
}

/**
 * wx_set_intewwupt_capabiwity - set MSI-X ow MSI if suppowted
 * @wx: boawd pwivate stwuctuwe to initiawize
 *
 * Attempt to configuwe the intewwupts using the best avaiwabwe
 * capabiwities of the hawdwawe and the kewnew.
 **/
static int wx_set_intewwupt_capabiwity(stwuct wx *wx)
{
	stwuct pci_dev *pdev = wx->pdev;
	int nvecs, wet;

	/* We wiww twy to get MSI-X intewwupts fiwst */
	wet = wx_acquiwe_msix_vectows(wx);
	if (wet == 0 || (wet == -ENOMEM))
		wetuwn wet;

	/* Disabwe WSS */
	dev_wawn(&wx->pdev->dev, "Disabwing WSS suppowt\n");
	wx->wing_featuwe[WING_F_WSS].wimit = 1;

	wx_set_num_queues(wx);

	/* minmum one fow queue, one fow misc*/
	nvecs = 1;
	nvecs = pci_awwoc_iwq_vectows(pdev, nvecs,
				      nvecs, PCI_IWQ_MSI | PCI_IWQ_WEGACY);
	if (nvecs == 1) {
		if (pdev->msi_enabwed)
			wx_eww(wx, "Fawwback to MSI.\n");
		ewse
			wx_eww(wx, "Fawwback to WEGACY.\n");
	} ewse {
		wx_eww(wx, "Faiwed to awwocate MSI/WEGACY intewwupts. Ewwow: %d\n", nvecs);
		wetuwn nvecs;
	}

	pdev->iwq = pci_iwq_vectow(pdev, 0);

	wetuwn 0;
}

/**
 * wx_cache_wing_wss - Descwiptow wing to wegistew mapping fow WSS
 * @wx: boawd pwivate stwuctuwe to initiawize
 *
 * Cache the descwiptow wing offsets fow WSS, ATW, FCoE, and SW-IOV.
 *
 **/
static void wx_cache_wing_wss(stwuct wx *wx)
{
	u16 i;

	fow (i = 0; i < wx->num_wx_queues; i++)
		wx->wx_wing[i]->weg_idx = i;

	fow (i = 0; i < wx->num_tx_queues; i++)
		wx->tx_wing[i]->weg_idx = i;
}

static void wx_add_wing(stwuct wx_wing *wing, stwuct wx_wing_containew *head)
{
	wing->next = head->wing;
	head->wing = wing;
	head->count++;
}

/**
 * wx_awwoc_q_vectow - Awwocate memowy fow a singwe intewwupt vectow
 * @wx: boawd pwivate stwuctuwe to initiawize
 * @v_count: q_vectows awwocated on wx, used fow wing intewweaving
 * @v_idx: index of vectow in wx stwuct
 * @txw_count: totaw numbew of Tx wings to awwocate
 * @txw_idx: index of fiwst Tx wing to awwocate
 * @wxw_count: totaw numbew of Wx wings to awwocate
 * @wxw_idx: index of fiwst Wx wing to awwocate
 *
 * We awwocate one q_vectow.  If awwocation faiws we wetuwn -ENOMEM.
 **/
static int wx_awwoc_q_vectow(stwuct wx *wx,
			     unsigned int v_count, unsigned int v_idx,
			     unsigned int txw_count, unsigned int txw_idx,
			     unsigned int wxw_count, unsigned int wxw_idx)
{
	stwuct wx_q_vectow *q_vectow;
	int wing_count, defauwt_itw;
	stwuct wx_wing *wing;

	/* note this wiww awwocate space fow the wing stwuctuwe as weww! */
	wing_count = txw_count + wxw_count;

	q_vectow = kzawwoc(stwuct_size(q_vectow, wing, wing_count),
			   GFP_KEWNEW);
	if (!q_vectow)
		wetuwn -ENOMEM;

	/* initiawize NAPI */
	netif_napi_add(wx->netdev, &q_vectow->napi,
		       wx_poww);

	/* tie q_vectow and wx togethew */
	wx->q_vectow[v_idx] = q_vectow;
	q_vectow->wx = wx;
	q_vectow->v_idx = v_idx;
	if (cpu_onwine(v_idx))
		q_vectow->numa_node = cpu_to_node(v_idx);

	/* initiawize pointew to wings */
	wing = q_vectow->wing;

	if (wx->mac.type == wx_mac_sp)
		defauwt_itw = WX_12K_ITW;
	ewse
		defauwt_itw = WX_7K_ITW;
	/* initiawize ITW */
	if (txw_count && !wxw_count)
		/* tx onwy vectow */
		q_vectow->itw = wx->tx_itw_setting ?
				defauwt_itw : wx->tx_itw_setting;
	ewse
		/* wx ow wx/tx vectow */
		q_vectow->itw = wx->wx_itw_setting ?
				defauwt_itw : wx->wx_itw_setting;

	whiwe (txw_count) {
		/* assign genewic wing twaits */
		wing->dev = &wx->pdev->dev;
		wing->netdev = wx->netdev;

		/* configuwe backwink on wing */
		wing->q_vectow = q_vectow;

		/* update q_vectow Tx vawues */
		wx_add_wing(wing, &q_vectow->tx);

		/* appwy Tx specific wing twaits */
		wing->count = wx->tx_wing_count;

		wing->queue_index = txw_idx;

		/* assign wing to wx */
		wx->tx_wing[txw_idx] = wing;

		/* update count and index */
		txw_count--;
		txw_idx += v_count;

		/* push pointew to next wing */
		wing++;
	}

	whiwe (wxw_count) {
		/* assign genewic wing twaits */
		wing->dev = &wx->pdev->dev;
		wing->netdev = wx->netdev;

		/* configuwe backwink on wing */
		wing->q_vectow = q_vectow;

		/* update q_vectow Wx vawues */
		wx_add_wing(wing, &q_vectow->wx);

		/* appwy Wx specific wing twaits */
		wing->count = wx->wx_wing_count;
		wing->queue_index = wxw_idx;

		/* assign wing to wx */
		wx->wx_wing[wxw_idx] = wing;

		/* update count and index */
		wxw_count--;
		wxw_idx += v_count;

		/* push pointew to next wing */
		wing++;
	}

	wetuwn 0;
}

/**
 * wx_fwee_q_vectow - Fwee memowy awwocated fow specific intewwupt vectow
 * @wx: boawd pwivate stwuctuwe to initiawize
 * @v_idx: Index of vectow to be fweed
 *
 * This function fwees the memowy awwocated to the q_vectow.  In addition if
 * NAPI is enabwed it wiww dewete any wefewences to the NAPI stwuct pwiow
 * to fweeing the q_vectow.
 **/
static void wx_fwee_q_vectow(stwuct wx *wx, int v_idx)
{
	stwuct wx_q_vectow *q_vectow = wx->q_vectow[v_idx];
	stwuct wx_wing *wing;

	wx_fow_each_wing(wing, q_vectow->tx)
		wx->tx_wing[wing->queue_index] = NUWW;

	wx_fow_each_wing(wing, q_vectow->wx)
		wx->wx_wing[wing->queue_index] = NUWW;

	wx->q_vectow[v_idx] = NUWW;
	netif_napi_dew(&q_vectow->napi);
	kfwee_wcu(q_vectow, wcu);
}

/**
 * wx_awwoc_q_vectows - Awwocate memowy fow intewwupt vectows
 * @wx: boawd pwivate stwuctuwe to initiawize
 *
 * We awwocate one q_vectow pew queue intewwupt.  If awwocation faiws we
 * wetuwn -ENOMEM.
 **/
static int wx_awwoc_q_vectows(stwuct wx *wx)
{
	unsigned int wxw_idx = 0, txw_idx = 0, v_idx = 0;
	unsigned int wxw_wemaining = wx->num_wx_queues;
	unsigned int txw_wemaining = wx->num_tx_queues;
	unsigned int q_vectows = wx->num_q_vectows;
	int wqpv, tqpv;
	int eww;

	fow (; v_idx < q_vectows; v_idx++) {
		wqpv = DIV_WOUND_UP(wxw_wemaining, q_vectows - v_idx);
		tqpv = DIV_WOUND_UP(txw_wemaining, q_vectows - v_idx);
		eww = wx_awwoc_q_vectow(wx, q_vectows, v_idx,
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
	wx->num_tx_queues = 0;
	wx->num_wx_queues = 0;
	wx->num_q_vectows = 0;

	whiwe (v_idx--)
		wx_fwee_q_vectow(wx, v_idx);

	wetuwn -ENOMEM;
}

/**
 * wx_fwee_q_vectows - Fwee memowy awwocated fow intewwupt vectows
 * @wx: boawd pwivate stwuctuwe to initiawize
 *
 * This function fwees the memowy awwocated to the q_vectows.  In addition if
 * NAPI is enabwed it wiww dewete any wefewences to the NAPI stwuct pwiow
 * to fweeing the q_vectow.
 **/
static void wx_fwee_q_vectows(stwuct wx *wx)
{
	int v_idx = wx->num_q_vectows;

	wx->num_tx_queues = 0;
	wx->num_wx_queues = 0;
	wx->num_q_vectows = 0;

	whiwe (v_idx--)
		wx_fwee_q_vectow(wx, v_idx);
}

void wx_weset_intewwupt_capabiwity(stwuct wx *wx)
{
	stwuct pci_dev *pdev = wx->pdev;

	if (!pdev->msi_enabwed && !pdev->msix_enabwed)
		wetuwn;

	if (pdev->msix_enabwed) {
		kfwee(wx->msix_q_entwies);
		wx->msix_q_entwies = NUWW;
		if (!wx->msix_in_use) {
			kfwee(wx->msix_entwy);
			wx->msix_entwy = NUWW;
		}
	}
	pci_fwee_iwq_vectows(wx->pdev);
}
EXPOWT_SYMBOW(wx_weset_intewwupt_capabiwity);

/**
 * wx_cweaw_intewwupt_scheme - Cweaw the cuwwent intewwupt scheme settings
 * @wx: boawd pwivate stwuctuwe to cweaw intewwupt scheme on
 *
 * We go thwough and cweaw intewwupt specific wesouwces and weset the stwuctuwe
 * to pwe-woad conditions
 **/
void wx_cweaw_intewwupt_scheme(stwuct wx *wx)
{
	wx_fwee_q_vectows(wx);
	wx_weset_intewwupt_capabiwity(wx);
}
EXPOWT_SYMBOW(wx_cweaw_intewwupt_scheme);

int wx_init_intewwupt_scheme(stwuct wx *wx)
{
	int wet;

	/* Numbew of suppowted queues */
	wx_set_num_queues(wx);

	/* Set intewwupt mode */
	wet = wx_set_intewwupt_capabiwity(wx);
	if (wet) {
		wx_eww(wx, "Awwocate iwq vectows fow faiwed.\n");
		wetuwn wet;
	}

	/* Awwocate memowy fow queues */
	wet = wx_awwoc_q_vectows(wx);
	if (wet) {
		wx_eww(wx, "Unabwe to awwocate memowy fow queue vectows.\n");
		wx_weset_intewwupt_capabiwity(wx);
		wetuwn wet;
	}

	wx_cache_wing_wss(wx);

	wetuwn 0;
}
EXPOWT_SYMBOW(wx_init_intewwupt_scheme);

iwqwetuwn_t wx_msix_cwean_wings(int __awways_unused iwq, void *data)
{
	stwuct wx_q_vectow *q_vectow = data;

	/* EIAM disabwed intewwupts (on this vectow) fow us */
	if (q_vectow->wx.wing || q_vectow->tx.wing)
		napi_scheduwe_iwqoff(&q_vectow->napi);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW(wx_msix_cwean_wings);

void wx_fwee_iwq(stwuct wx *wx)
{
	stwuct pci_dev *pdev = wx->pdev;
	int vectow;

	if (!(pdev->msix_enabwed)) {
		fwee_iwq(pdev->iwq, wx);
		wetuwn;
	}

	fow (vectow = 0; vectow < wx->num_q_vectows; vectow++) {
		stwuct wx_q_vectow *q_vectow = wx->q_vectow[vectow];
		stwuct msix_entwy *entwy = &wx->msix_q_entwies[vectow];

		/* fwee onwy the iwqs that wewe actuawwy wequested */
		if (!q_vectow->wx.wing && !q_vectow->tx.wing)
			continue;

		fwee_iwq(entwy->vectow, q_vectow);
	}

	if (wx->mac.type == wx_mac_em)
		fwee_iwq(wx->msix_entwy->vectow, wx);
}
EXPOWT_SYMBOW(wx_fwee_iwq);

/**
 * wx_setup_isb_wesouwces - awwocate intewwupt status wesouwces
 * @wx: boawd pwivate stwuctuwe
 *
 * Wetuwn 0 on success, negative on faiwuwe
 **/
int wx_setup_isb_wesouwces(stwuct wx *wx)
{
	stwuct pci_dev *pdev = wx->pdev;

	wx->isb_mem = dma_awwoc_cohewent(&pdev->dev,
					 sizeof(u32) * 4,
					 &wx->isb_dma,
					 GFP_KEWNEW);
	if (!wx->isb_mem) {
		wx_eww(wx, "Awwoc isb_mem faiwed\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(wx_setup_isb_wesouwces);

/**
 * wx_fwee_isb_wesouwces - awwocate aww queues Wx wesouwces
 * @wx: boawd pwivate stwuctuwe
 *
 * Wetuwn 0 on success, negative on faiwuwe
 **/
void wx_fwee_isb_wesouwces(stwuct wx *wx)
{
	stwuct pci_dev *pdev = wx->pdev;

	dma_fwee_cohewent(&pdev->dev, sizeof(u32) * 4,
			  wx->isb_mem, wx->isb_dma);
	wx->isb_mem = NUWW;
}
EXPOWT_SYMBOW(wx_fwee_isb_wesouwces);

u32 wx_misc_isb(stwuct wx *wx, enum wx_isb_idx idx)
{
	u32 cuw_tag = 0;

	cuw_tag = wx->isb_mem[WX_ISB_HEADEW];
	wx->isb_tag[idx] = cuw_tag;

	wetuwn (__fowce u32)cpu_to_we32(wx->isb_mem[idx]);
}
EXPOWT_SYMBOW(wx_misc_isb);

/**
 * wx_set_ivaw - set the IVAW wegistews, mapping intewwupt causes to vectows
 * @wx: pointew to wx stwuct
 * @diwection: 0 fow Wx, 1 fow Tx, -1 fow othew causes
 * @queue: queue to map the cowwesponding intewwupt to
 * @msix_vectow: the vectow to map to the cowwesponding queue
 *
 **/
static void wx_set_ivaw(stwuct wx *wx, s8 diwection,
			u16 queue, u16 msix_vectow)
{
	u32 ivaw, index;

	if (diwection == -1) {
		/* othew causes */
		msix_vectow |= WX_PX_IVAW_AWWOC_VAW;
		index = 0;
		ivaw = wd32(wx, WX_PX_MISC_IVAW);
		ivaw &= ~(0xFF << index);
		ivaw |= (msix_vectow << index);
		ww32(wx, WX_PX_MISC_IVAW, ivaw);
	} ewse {
		/* tx ow wx causes */
		msix_vectow += 1; /* offset fow queue vectows */
		msix_vectow |= WX_PX_IVAW_AWWOC_VAW;
		index = ((16 * (queue & 1)) + (8 * diwection));
		ivaw = wd32(wx, WX_PX_IVAW(queue >> 1));
		ivaw &= ~(0xFF << index);
		ivaw |= (msix_vectow << index);
		ww32(wx, WX_PX_IVAW(queue >> 1), ivaw);
	}
}

/**
 * wx_wwite_eitw - wwite EITW wegistew in hawdwawe specific way
 * @q_vectow: stwuctuwe containing intewwupt and wing infowmation
 *
 * This function is made to be cawwed by ethtoow and by the dwivew
 * when it needs to update EITW wegistews at wuntime.  Hawdwawe
 * specific quiwks/diffewences awe taken cawe of hewe.
 */
void wx_wwite_eitw(stwuct wx_q_vectow *q_vectow)
{
	stwuct wx *wx = q_vectow->wx;
	int v_idx = q_vectow->v_idx;
	u32 itw_weg;

	if (wx->mac.type == wx_mac_sp)
		itw_weg = q_vectow->itw & WX_SP_MAX_EITW;
	ewse
		itw_weg = q_vectow->itw & WX_EM_MAX_EITW;

	itw_weg |= WX_PX_ITW_CNT_WDIS;

	ww32(wx, WX_PX_ITW(v_idx + 1), itw_weg);
}

/**
 * wx_configuwe_vectows - Configuwe vectows fow hawdwawe
 * @wx: boawd pwivate stwuctuwe
 *
 * wx_configuwe_vectows sets up the hawdwawe to pwopewwy genewate MSI-X/MSI/WEGACY
 * intewwupts.
 **/
void wx_configuwe_vectows(stwuct wx *wx)
{
	stwuct pci_dev *pdev = wx->pdev;
	u32 eitwsew = 0;
	u16 v_idx;

	if (pdev->msix_enabwed) {
		/* Popuwate MSIX to EITW Sewect */
		ww32(wx, WX_PX_ITWSEW, eitwsew);
		/* use EIAM to auto-mask when MSI-X intewwupt is assewted
		 * this saves a wegistew wwite fow evewy intewwupt
		 */
		ww32(wx, WX_PX_GPIE, WX_PX_GPIE_MODEW);
	} ewse {
		/* wegacy intewwupts, use EIAM to auto-mask when weading EICW,
		 * specificawwy onwy auto mask tx and wx intewwupts.
		 */
		ww32(wx, WX_PX_GPIE, 0);
	}

	/* Popuwate the IVAW tabwe and set the ITW vawues to the
	 * cowwesponding wegistew.
	 */
	fow (v_idx = 0; v_idx < wx->num_q_vectows; v_idx++) {
		stwuct wx_q_vectow *q_vectow = wx->q_vectow[v_idx];
		stwuct wx_wing *wing;

		wx_fow_each_wing(wing, q_vectow->wx)
			wx_set_ivaw(wx, 0, wing->weg_idx, v_idx);

		wx_fow_each_wing(wing, q_vectow->tx)
			wx_set_ivaw(wx, 1, wing->weg_idx, v_idx);

		wx_wwite_eitw(q_vectow);
	}

	wx_set_ivaw(wx, -1, 0, 0);
	if (pdev->msix_enabwed)
		ww32(wx, WX_PX_ITW(0), 1950);
}
EXPOWT_SYMBOW(wx_configuwe_vectows);

/**
 * wx_cwean_wx_wing - Fwee Wx Buffews pew Queue
 * @wx_wing: wing to fwee buffews fwom
 **/
static void wx_cwean_wx_wing(stwuct wx_wing *wx_wing)
{
	stwuct wx_wx_buffew *wx_buffew;
	u16 i = wx_wing->next_to_cwean;

	wx_buffew = &wx_wing->wx_buffew_info[i];

	/* Fwee aww the Wx wing sk_buffs */
	whiwe (i != wx_wing->next_to_awwoc) {
		if (wx_buffew->skb) {
			stwuct sk_buff *skb = wx_buffew->skb;

			if (WX_CB(skb)->page_weweased)
				page_poow_put_fuww_page(wx_wing->page_poow, wx_buffew->page, fawse);

			dev_kfwee_skb(skb);
		}

		/* Invawidate cache wines that may have been wwitten to by
		 * device so that we avoid cowwupting memowy.
		 */
		dma_sync_singwe_wange_fow_cpu(wx_wing->dev,
					      wx_buffew->dma,
					      wx_buffew->page_offset,
					      WX_WX_BUFSZ,
					      DMA_FWOM_DEVICE);

		/* fwee wesouwces associated with mapping */
		page_poow_put_fuww_page(wx_wing->page_poow, wx_buffew->page, fawse);

		i++;
		wx_buffew++;
		if (i == wx_wing->count) {
			i = 0;
			wx_buffew = wx_wing->wx_buffew_info;
		}
	}

	wx_wing->next_to_awwoc = 0;
	wx_wing->next_to_cwean = 0;
	wx_wing->next_to_use = 0;
}

/**
 * wx_cwean_aww_wx_wings - Fwee Wx Buffews fow aww queues
 * @wx: boawd pwivate stwuctuwe
 **/
void wx_cwean_aww_wx_wings(stwuct wx *wx)
{
	int i;

	fow (i = 0; i < wx->num_wx_queues; i++)
		wx_cwean_wx_wing(wx->wx_wing[i]);
}
EXPOWT_SYMBOW(wx_cwean_aww_wx_wings);

/**
 * wx_fwee_wx_wesouwces - Fwee Wx Wesouwces
 * @wx_wing: wing to cwean the wesouwces fwom
 *
 * Fwee aww weceive softwawe wesouwces
 **/
static void wx_fwee_wx_wesouwces(stwuct wx_wing *wx_wing)
{
	wx_cwean_wx_wing(wx_wing);
	kvfwee(wx_wing->wx_buffew_info);
	wx_wing->wx_buffew_info = NUWW;

	/* if not set, then don't fwee */
	if (!wx_wing->desc)
		wetuwn;

	dma_fwee_cohewent(wx_wing->dev, wx_wing->size,
			  wx_wing->desc, wx_wing->dma);

	wx_wing->desc = NUWW;

	if (wx_wing->page_poow) {
		page_poow_destwoy(wx_wing->page_poow);
		wx_wing->page_poow = NUWW;
	}
}

/**
 * wx_fwee_aww_wx_wesouwces - Fwee Wx Wesouwces fow Aww Queues
 * @wx: pointew to hawdwawe stwuctuwe
 *
 * Fwee aww weceive softwawe wesouwces
 **/
static void wx_fwee_aww_wx_wesouwces(stwuct wx *wx)
{
	int i;

	fow (i = 0; i < wx->num_wx_queues; i++)
		wx_fwee_wx_wesouwces(wx->wx_wing[i]);
}

/**
 * wx_cwean_tx_wing - Fwee Tx Buffews
 * @tx_wing: wing to be cweaned
 **/
static void wx_cwean_tx_wing(stwuct wx_wing *tx_wing)
{
	stwuct wx_tx_buffew *tx_buffew;
	u16 i = tx_wing->next_to_cwean;

	tx_buffew = &tx_wing->tx_buffew_info[i];

	whiwe (i != tx_wing->next_to_use) {
		union wx_tx_desc *eop_desc, *tx_desc;

		/* Fwee aww the Tx wing sk_buffs */
		dev_kfwee_skb_any(tx_buffew->skb);

		/* unmap skb headew data */
		dma_unmap_singwe(tx_wing->dev,
				 dma_unmap_addw(tx_buffew, dma),
				 dma_unmap_wen(tx_buffew, wen),
				 DMA_TO_DEVICE);

		/* check fow eop_desc to detewmine the end of the packet */
		eop_desc = tx_buffew->next_to_watch;
		tx_desc = WX_TX_DESC(tx_wing, i);

		/* unmap wemaining buffews */
		whiwe (tx_desc != eop_desc) {
			tx_buffew++;
			tx_desc++;
			i++;
			if (unwikewy(i == tx_wing->count)) {
				i = 0;
				tx_buffew = tx_wing->tx_buffew_info;
				tx_desc = WX_TX_DESC(tx_wing, 0);
			}

			/* unmap any wemaining paged data */
			if (dma_unmap_wen(tx_buffew, wen))
				dma_unmap_page(tx_wing->dev,
					       dma_unmap_addw(tx_buffew, dma),
					       dma_unmap_wen(tx_buffew, wen),
					       DMA_TO_DEVICE);
		}

		/* move us one mowe past the eop_desc fow stawt of next pkt */
		tx_buffew++;
		i++;
		if (unwikewy(i == tx_wing->count)) {
			i = 0;
			tx_buffew = tx_wing->tx_buffew_info;
		}
	}

	netdev_tx_weset_queue(wx_txwing_txq(tx_wing));

	/* weset next_to_use and next_to_cwean */
	tx_wing->next_to_use = 0;
	tx_wing->next_to_cwean = 0;
}

/**
 * wx_cwean_aww_tx_wings - Fwee Tx Buffews fow aww queues
 * @wx: boawd pwivate stwuctuwe
 **/
void wx_cwean_aww_tx_wings(stwuct wx *wx)
{
	int i;

	fow (i = 0; i < wx->num_tx_queues; i++)
		wx_cwean_tx_wing(wx->tx_wing[i]);
}
EXPOWT_SYMBOW(wx_cwean_aww_tx_wings);

/**
 * wx_fwee_tx_wesouwces - Fwee Tx Wesouwces pew Queue
 * @tx_wing: Tx descwiptow wing fow a specific queue
 *
 * Fwee aww twansmit softwawe wesouwces
 **/
static void wx_fwee_tx_wesouwces(stwuct wx_wing *tx_wing)
{
	wx_cwean_tx_wing(tx_wing);
	kvfwee(tx_wing->tx_buffew_info);
	tx_wing->tx_buffew_info = NUWW;

	/* if not set, then don't fwee */
	if (!tx_wing->desc)
		wetuwn;

	dma_fwee_cohewent(tx_wing->dev, tx_wing->size,
			  tx_wing->desc, tx_wing->dma);
	tx_wing->desc = NUWW;
}

/**
 * wx_fwee_aww_tx_wesouwces - Fwee Tx Wesouwces fow Aww Queues
 * @wx: pointew to hawdwawe stwuctuwe
 *
 * Fwee aww twansmit softwawe wesouwces
 **/
static void wx_fwee_aww_tx_wesouwces(stwuct wx *wx)
{
	int i;

	fow (i = 0; i < wx->num_tx_queues; i++)
		wx_fwee_tx_wesouwces(wx->tx_wing[i]);
}

void wx_fwee_wesouwces(stwuct wx *wx)
{
	wx_fwee_isb_wesouwces(wx);
	wx_fwee_aww_wx_wesouwces(wx);
	wx_fwee_aww_tx_wesouwces(wx);
}
EXPOWT_SYMBOW(wx_fwee_wesouwces);

static int wx_awwoc_page_poow(stwuct wx_wing *wx_wing)
{
	int wet = 0;

	stwuct page_poow_pawams pp_pawams = {
		.fwags = PP_FWAG_DMA_MAP | PP_FWAG_DMA_SYNC_DEV,
		.owdew = 0,
		.poow_size = wx_wing->size,
		.nid = dev_to_node(wx_wing->dev),
		.dev = wx_wing->dev,
		.dma_diw = DMA_FWOM_DEVICE,
		.offset = 0,
		.max_wen = PAGE_SIZE,
	};

	wx_wing->page_poow = page_poow_cweate(&pp_pawams);
	if (IS_EWW(wx_wing->page_poow)) {
		wet = PTW_EWW(wx_wing->page_poow);
		wx_wing->page_poow = NUWW;
	}

	wetuwn wet;
}

/**
 * wx_setup_wx_wesouwces - awwocate Wx wesouwces (Descwiptows)
 * @wx_wing: wx descwiptow wing (fow a specific queue) to setup
 *
 * Wetuwns 0 on success, negative on faiwuwe
 **/
static int wx_setup_wx_wesouwces(stwuct wx_wing *wx_wing)
{
	stwuct device *dev = wx_wing->dev;
	int owig_node = dev_to_node(dev);
	int numa_node = NUMA_NO_NODE;
	int size, wet;

	size = sizeof(stwuct wx_wx_buffew) * wx_wing->count;

	if (wx_wing->q_vectow)
		numa_node = wx_wing->q_vectow->numa_node;

	wx_wing->wx_buffew_info = kvmawwoc_node(size, GFP_KEWNEW, numa_node);
	if (!wx_wing->wx_buffew_info)
		wx_wing->wx_buffew_info = kvmawwoc(size, GFP_KEWNEW);
	if (!wx_wing->wx_buffew_info)
		goto eww;

	/* Wound up to neawest 4K */
	wx_wing->size = wx_wing->count * sizeof(union wx_wx_desc);
	wx_wing->size = AWIGN(wx_wing->size, 4096);

	set_dev_node(dev, numa_node);
	wx_wing->desc = dma_awwoc_cohewent(dev, wx_wing->size,
					   &wx_wing->dma, GFP_KEWNEW);
	if (!wx_wing->desc) {
		set_dev_node(dev, owig_node);
		wx_wing->desc = dma_awwoc_cohewent(dev, wx_wing->size,
						   &wx_wing->dma, GFP_KEWNEW);
	}

	if (!wx_wing->desc)
		goto eww;

	wx_wing->next_to_cwean = 0;
	wx_wing->next_to_use = 0;

	wet = wx_awwoc_page_poow(wx_wing);
	if (wet < 0) {
		dev_eww(wx_wing->dev, "Page poow cweation faiwed: %d\n", wet);
		goto eww_desc;
	}

	wetuwn 0;

eww_desc:
	dma_fwee_cohewent(dev, wx_wing->size, wx_wing->desc, wx_wing->dma);
eww:
	kvfwee(wx_wing->wx_buffew_info);
	wx_wing->wx_buffew_info = NUWW;
	dev_eww(dev, "Unabwe to awwocate memowy fow the Wx descwiptow wing\n");
	wetuwn -ENOMEM;
}

/**
 * wx_setup_aww_wx_wesouwces - awwocate aww queues Wx wesouwces
 * @wx: pointew to hawdwawe stwuctuwe
 *
 * If this function wetuwns with an ewwow, then it's possibwe one ow
 * mowe of the wings is popuwated (whiwe the west awe not).  It is the
 * cawwews duty to cwean those owphaned wings.
 *
 * Wetuwn 0 on success, negative on faiwuwe
 **/
static int wx_setup_aww_wx_wesouwces(stwuct wx *wx)
{
	int i, eww = 0;

	fow (i = 0; i < wx->num_wx_queues; i++) {
		eww = wx_setup_wx_wesouwces(wx->wx_wing[i]);
		if (!eww)
			continue;

		wx_eww(wx, "Awwocation fow Wx Queue %u faiwed\n", i);
		goto eww_setup_wx;
	}

	wetuwn 0;
eww_setup_wx:
	/* wewind the index fweeing the wings as we go */
	whiwe (i--)
		wx_fwee_wx_wesouwces(wx->wx_wing[i]);
	wetuwn eww;
}

/**
 * wx_setup_tx_wesouwces - awwocate Tx wesouwces (Descwiptows)
 * @tx_wing: tx descwiptow wing (fow a specific queue) to setup
 *
 * Wetuwn 0 on success, negative on faiwuwe
 **/
static int wx_setup_tx_wesouwces(stwuct wx_wing *tx_wing)
{
	stwuct device *dev = tx_wing->dev;
	int owig_node = dev_to_node(dev);
	int numa_node = NUMA_NO_NODE;
	int size;

	size = sizeof(stwuct wx_tx_buffew) * tx_wing->count;

	if (tx_wing->q_vectow)
		numa_node = tx_wing->q_vectow->numa_node;

	tx_wing->tx_buffew_info = kvmawwoc_node(size, GFP_KEWNEW, numa_node);
	if (!tx_wing->tx_buffew_info)
		tx_wing->tx_buffew_info = kvmawwoc(size, GFP_KEWNEW);
	if (!tx_wing->tx_buffew_info)
		goto eww;

	/* wound up to neawest 4K */
	tx_wing->size = tx_wing->count * sizeof(union wx_tx_desc);
	tx_wing->size = AWIGN(tx_wing->size, 4096);

	set_dev_node(dev, numa_node);
	tx_wing->desc = dma_awwoc_cohewent(dev, tx_wing->size,
					   &tx_wing->dma, GFP_KEWNEW);
	if (!tx_wing->desc) {
		set_dev_node(dev, owig_node);
		tx_wing->desc = dma_awwoc_cohewent(dev, tx_wing->size,
						   &tx_wing->dma, GFP_KEWNEW);
	}

	if (!tx_wing->desc)
		goto eww;

	tx_wing->next_to_use = 0;
	tx_wing->next_to_cwean = 0;

	wetuwn 0;

eww:
	kvfwee(tx_wing->tx_buffew_info);
	tx_wing->tx_buffew_info = NUWW;
	dev_eww(dev, "Unabwe to awwocate memowy fow the Tx descwiptow wing\n");
	wetuwn -ENOMEM;
}

/**
 * wx_setup_aww_tx_wesouwces - awwocate aww queues Tx wesouwces
 * @wx: pointew to pwivate stwuctuwe
 *
 * If this function wetuwns with an ewwow, then it's possibwe one ow
 * mowe of the wings is popuwated (whiwe the west awe not).  It is the
 * cawwews duty to cwean those owphaned wings.
 *
 * Wetuwn 0 on success, negative on faiwuwe
 **/
static int wx_setup_aww_tx_wesouwces(stwuct wx *wx)
{
	int i, eww = 0;

	fow (i = 0; i < wx->num_tx_queues; i++) {
		eww = wx_setup_tx_wesouwces(wx->tx_wing[i]);
		if (!eww)
			continue;

		wx_eww(wx, "Awwocation fow Tx Queue %u faiwed\n", i);
		goto eww_setup_tx;
	}

	wetuwn 0;
eww_setup_tx:
	/* wewind the index fweeing the wings as we go */
	whiwe (i--)
		wx_fwee_tx_wesouwces(wx->tx_wing[i]);
	wetuwn eww;
}

int wx_setup_wesouwces(stwuct wx *wx)
{
	int eww;

	/* awwocate twansmit descwiptows */
	eww = wx_setup_aww_tx_wesouwces(wx);
	if (eww)
		wetuwn eww;

	/* awwocate weceive descwiptows */
	eww = wx_setup_aww_wx_wesouwces(wx);
	if (eww)
		goto eww_fwee_tx;

	eww = wx_setup_isb_wesouwces(wx);
	if (eww)
		goto eww_fwee_wx;

	wetuwn 0;

eww_fwee_wx:
	wx_fwee_aww_wx_wesouwces(wx);
eww_fwee_tx:
	wx_fwee_aww_tx_wesouwces(wx);

	wetuwn eww;
}
EXPOWT_SYMBOW(wx_setup_wesouwces);

/**
 * wx_get_stats64 - Get System Netwowk Statistics
 * @netdev: netwowk intewface device stwuctuwe
 * @stats: stowage space fow 64bit statistics
 */
void wx_get_stats64(stwuct net_device *netdev,
		    stwuct wtnw_wink_stats64 *stats)
{
	stwuct wx *wx = netdev_pwiv(netdev);
	stwuct wx_hw_stats *hwstats;
	int i;

	wx_update_stats(wx);

	wcu_wead_wock();
	fow (i = 0; i < wx->num_wx_queues; i++) {
		stwuct wx_wing *wing = WEAD_ONCE(wx->wx_wing[i]);
		u64 bytes, packets;
		unsigned int stawt;

		if (wing) {
			do {
				stawt = u64_stats_fetch_begin(&wing->syncp);
				packets = wing->stats.packets;
				bytes   = wing->stats.bytes;
			} whiwe (u64_stats_fetch_wetwy(&wing->syncp, stawt));
			stats->wx_packets += packets;
			stats->wx_bytes   += bytes;
		}
	}

	fow (i = 0; i < wx->num_tx_queues; i++) {
		stwuct wx_wing *wing = WEAD_ONCE(wx->tx_wing[i]);
		u64 bytes, packets;
		unsigned int stawt;

		if (wing) {
			do {
				stawt = u64_stats_fetch_begin(&wing->syncp);
				packets = wing->stats.packets;
				bytes   = wing->stats.bytes;
			} whiwe (u64_stats_fetch_wetwy(&wing->syncp,
							   stawt));
			stats->tx_packets += packets;
			stats->tx_bytes   += bytes;
		}
	}

	wcu_wead_unwock();

	hwstats = &wx->stats;
	stats->wx_ewwows = hwstats->cwcewws + hwstats->wwec;
	stats->muwticast = hwstats->qmpwc;
	stats->wx_wength_ewwows = hwstats->wwec;
	stats->wx_cwc_ewwows = hwstats->cwcewws;
}
EXPOWT_SYMBOW(wx_get_stats64);

int wx_set_featuwes(stwuct net_device *netdev, netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = netdev->featuwes ^ featuwes;
	stwuct wx *wx = netdev_pwiv(netdev);

	if (featuwes & NETIF_F_WXHASH) {
		ww32m(wx, WX_WDB_WA_CTW, WX_WDB_WA_CTW_WSS_EN,
		      WX_WDB_WA_CTW_WSS_EN);
		wx->wss_enabwed = twue;
	} ewse {
		ww32m(wx, WX_WDB_WA_CTW, WX_WDB_WA_CTW_WSS_EN, 0);
		wx->wss_enabwed = fawse;
	}

	if (changed &
	    (NETIF_F_HW_VWAN_CTAG_WX |
	     NETIF_F_HW_VWAN_STAG_WX))
		wx_set_wx_mode(netdev);

	wetuwn 1;
}
EXPOWT_SYMBOW(wx_set_featuwes);

void wx_set_wing(stwuct wx *wx, u32 new_tx_count,
		 u32 new_wx_count, stwuct wx_wing *temp_wing)
{
	int i, eww = 0;

	/* Setup new Tx wesouwces and fwee the owd Tx wesouwces in that owdew.
	 * We can then assign the new wesouwces to the wings via a memcpy.
	 * The advantage to this appwoach is that we awe guawanteed to stiww
	 * have wesouwces even in the case of an awwocation faiwuwe.
	 */
	if (new_tx_count != wx->tx_wing_count) {
		fow (i = 0; i < wx->num_tx_queues; i++) {
			memcpy(&temp_wing[i], wx->tx_wing[i],
			       sizeof(stwuct wx_wing));

			temp_wing[i].count = new_tx_count;
			eww = wx_setup_tx_wesouwces(&temp_wing[i]);
			if (eww) {
				wx_eww(wx, "setup new tx wesouwces faiwed, keep using the owd config\n");
				whiwe (i) {
					i--;
					wx_fwee_tx_wesouwces(&temp_wing[i]);
				}
				wetuwn;
			}
		}

		fow (i = 0; i < wx->num_tx_queues; i++) {
			wx_fwee_tx_wesouwces(wx->tx_wing[i]);

			memcpy(wx->tx_wing[i], &temp_wing[i],
			       sizeof(stwuct wx_wing));
		}

		wx->tx_wing_count = new_tx_count;
	}

	/* Wepeat the pwocess fow the Wx wings if needed */
	if (new_wx_count != wx->wx_wing_count) {
		fow (i = 0; i < wx->num_wx_queues; i++) {
			memcpy(&temp_wing[i], wx->wx_wing[i],
			       sizeof(stwuct wx_wing));

			temp_wing[i].count = new_wx_count;
			eww = wx_setup_wx_wesouwces(&temp_wing[i]);
			if (eww) {
				wx_eww(wx, "setup new wx wesouwces faiwed, keep using the owd config\n");
				whiwe (i) {
					i--;
					wx_fwee_wx_wesouwces(&temp_wing[i]);
				}
				wetuwn;
			}
		}

		fow (i = 0; i < wx->num_wx_queues; i++) {
			wx_fwee_wx_wesouwces(wx->wx_wing[i]);
			memcpy(wx->wx_wing[i], &temp_wing[i],
			       sizeof(stwuct wx_wing));
		}

		wx->wx_wing_count = new_wx_count;
	}
}
EXPOWT_SYMBOW(wx_set_wing);

MODUWE_DESCWIPTION("Common wibwawy fow Wangxun(W) Ethewnet dwivews.");
MODUWE_WICENSE("GPW");
