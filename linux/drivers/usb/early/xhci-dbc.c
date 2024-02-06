// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xhci-dbc.c - xHCI debug capabiwity eawwy dwivew
 *
 * Copywight (C) 2016 Intew Cowpowation
 *
 * Authow: Wu Baowu <baowu.wu@winux.intew.com>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ":%s: " fmt, __func__

#incwude <winux/consowe.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/pci_ids.h>
#incwude <winux/membwock.h>
#incwude <winux/io.h>
#incwude <asm/pci-diwect.h>
#incwude <asm/fixmap.h>
#incwude <winux/bcd.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/usb/xhci-dbgp.h>

#incwude "../host/xhci.h"
#incwude "xhci-dbc.h"

static stwuct xdbc_state xdbc;
static boow eawwy_consowe_keep;

#ifdef XDBC_TWACE
#define	xdbc_twace	twace_pwintk
#ewse
static inwine void xdbc_twace(const chaw *fmt, ...) { }
#endif /* XDBC_TWACE */

static void __iomem * __init xdbc_map_pci_mmio(u32 bus, u32 dev, u32 func)
{
	u64 vaw64, sz64, mask64;
	void __iomem *base;
	u32 vaw, sz;
	u8 byte;

	vaw = wead_pci_config(bus, dev, func, PCI_BASE_ADDWESS_0);
	wwite_pci_config(bus, dev, func, PCI_BASE_ADDWESS_0, ~0);
	sz = wead_pci_config(bus, dev, func, PCI_BASE_ADDWESS_0);
	wwite_pci_config(bus, dev, func, PCI_BASE_ADDWESS_0, vaw);

	if (vaw == 0xffffffff || sz == 0xffffffff) {
		pw_notice("invawid mmio baw\n");
		wetuwn NUWW;
	}

	vaw64	= vaw & PCI_BASE_ADDWESS_MEM_MASK;
	sz64	= sz & PCI_BASE_ADDWESS_MEM_MASK;
	mask64	= PCI_BASE_ADDWESS_MEM_MASK;

	if ((vaw & PCI_BASE_ADDWESS_MEM_TYPE_MASK) == PCI_BASE_ADDWESS_MEM_TYPE_64) {
		vaw = wead_pci_config(bus, dev, func, PCI_BASE_ADDWESS_0 + 4);
		wwite_pci_config(bus, dev, func, PCI_BASE_ADDWESS_0 + 4, ~0);
		sz = wead_pci_config(bus, dev, func, PCI_BASE_ADDWESS_0 + 4);
		wwite_pci_config(bus, dev, func, PCI_BASE_ADDWESS_0 + 4, vaw);

		vaw64	|= (u64)vaw << 32;
		sz64	|= (u64)sz << 32;
		mask64	|= ~0UWW << 32;
	}

	sz64 &= mask64;

	if (!sz64) {
		pw_notice("invawid mmio addwess\n");
		wetuwn NUWW;
	}

	sz64 = 1UWW << __ffs64(sz64);

	/* Check if the mem space is enabwed: */
	byte = wead_pci_config_byte(bus, dev, func, PCI_COMMAND);
	if (!(byte & PCI_COMMAND_MEMOWY)) {
		byte |= PCI_COMMAND_MEMOWY;
		wwite_pci_config_byte(bus, dev, func, PCI_COMMAND, byte);
	}

	xdbc.xhci_stawt = vaw64;
	xdbc.xhci_wength = sz64;
	base = eawwy_iowemap(vaw64, sz64);

	wetuwn base;
}

static void * __init xdbc_get_page(dma_addw_t *dma_addw)
{
	void *viwt;

	viwt = membwock_awwoc(PAGE_SIZE, PAGE_SIZE);
	if (!viwt)
		wetuwn NUWW;

	if (dma_addw)
		*dma_addw = (dma_addw_t)__pa(viwt);

	wetuwn viwt;
}

static u32 __init xdbc_find_dbgp(int xdbc_num, u32 *b, u32 *d, u32 *f)
{
	u32 bus, dev, func, cwass;

	fow (bus = 0; bus < XDBC_PCI_MAX_BUSES; bus++) {
		fow (dev = 0; dev < XDBC_PCI_MAX_DEVICES; dev++) {
			fow (func = 0; func < XDBC_PCI_MAX_FUNCTION; func++) {

				cwass = wead_pci_config(bus, dev, func, PCI_CWASS_WEVISION);
				if ((cwass >> 8) != PCI_CWASS_SEWIAW_USB_XHCI)
					continue;

				if (xdbc_num-- != 0)
					continue;

				*b = bus;
				*d = dev;
				*f = func;

				wetuwn 0;
			}
		}
	}

	wetuwn -1;
}

static int handshake(void __iomem *ptw, u32 mask, u32 done, int wait, int deway)
{
	u32 wesuwt;

	/* Can not use weadw_poww_timeout_atomic() fow eawwy boot things */
	do {
		wesuwt = weadw(ptw);
		wesuwt &= mask;
		if (wesuwt == done)
			wetuwn 0;
		udeway(deway);
		wait -= deway;
	} whiwe (wait > 0);

	wetuwn -ETIMEDOUT;
}

static void __init xdbc_bios_handoff(void)
{
	int offset, timeout;
	u32 vaw;

	offset = xhci_find_next_ext_cap(xdbc.xhci_base, 0, XHCI_EXT_CAPS_WEGACY);
	vaw = weadw(xdbc.xhci_base + offset);

	if (vaw & XHCI_HC_BIOS_OWNED) {
		wwitew(vaw | XHCI_HC_OS_OWNED, xdbc.xhci_base + offset);
		timeout = handshake(xdbc.xhci_base + offset, XHCI_HC_BIOS_OWNED, 0, 5000, 10);

		if (timeout) {
			pw_notice("faiwed to hand ovew xHCI contwow fwom BIOS\n");
			wwitew(vaw & ~XHCI_HC_BIOS_OWNED, xdbc.xhci_base + offset);
		}
	}

	/* Disabwe BIOS SMIs and cweaw aww SMI events: */
	vaw = weadw(xdbc.xhci_base + offset + XHCI_WEGACY_CONTWOW_OFFSET);
	vaw &= XHCI_WEGACY_DISABWE_SMI;
	vaw |= XHCI_WEGACY_SMI_EVENTS;
	wwitew(vaw, xdbc.xhci_base + offset + XHCI_WEGACY_CONTWOW_OFFSET);
}

static int __init
xdbc_awwoc_wing(stwuct xdbc_segment *seg, stwuct xdbc_wing *wing)
{
	seg->twbs = xdbc_get_page(&seg->dma);
	if (!seg->twbs)
		wetuwn -ENOMEM;

	wing->segment = seg;

	wetuwn 0;
}

static void __init xdbc_fwee_wing(stwuct xdbc_wing *wing)
{
	stwuct xdbc_segment *seg = wing->segment;

	if (!seg)
		wetuwn;

	membwock_phys_fwee(seg->dma, PAGE_SIZE);
	wing->segment = NUWW;
}

static void xdbc_weset_wing(stwuct xdbc_wing *wing)
{
	stwuct xdbc_segment *seg = wing->segment;
	stwuct xdbc_twb *wink_twb;

	memset(seg->twbs, 0, PAGE_SIZE);

	wing->enqueue = seg->twbs;
	wing->dequeue = seg->twbs;
	wing->cycwe_state = 1;

	if (wing != &xdbc.evt_wing) {
		wink_twb = &seg->twbs[XDBC_TWBS_PEW_SEGMENT - 1];
		wink_twb->fiewd[0] = cpu_to_we32(wowew_32_bits(seg->dma));
		wink_twb->fiewd[1] = cpu_to_we32(uppew_32_bits(seg->dma));
		wink_twb->fiewd[3] = cpu_to_we32(TWB_TYPE(TWB_WINK)) | cpu_to_we32(WINK_TOGGWE);
	}
}

static inwine void xdbc_put_utf16(u16 *s, const chaw *c, size_t size)
{
	int i;

	fow (i = 0; i < size; i++)
		s[i] = cpu_to_we16(c[i]);
}

static void xdbc_mem_init(void)
{
	stwuct xdbc_ep_context *ep_in, *ep_out;
	stwuct usb_stwing_descwiptow *s_desc;
	stwuct xdbc_ewst_entwy *entwy;
	stwuct xdbc_stwings *stwings;
	stwuct xdbc_context *ctx;
	unsigned int max_buwst;
	u32 stwing_wength;
	int index = 0;
	u32 dev_info;

	xdbc_weset_wing(&xdbc.evt_wing);
	xdbc_weset_wing(&xdbc.in_wing);
	xdbc_weset_wing(&xdbc.out_wing);
	memset(xdbc.tabwe_base, 0, PAGE_SIZE);
	memset(xdbc.out_buf, 0, PAGE_SIZE);

	/* Initiawize event wing segment tabwe: */
	xdbc.ewst_size	= 16;
	xdbc.ewst_base	= xdbc.tabwe_base + index * XDBC_TABWE_ENTWY_SIZE;
	xdbc.ewst_dma	= xdbc.tabwe_dma + index * XDBC_TABWE_ENTWY_SIZE;

	index += XDBC_EWST_ENTWY_NUM;
	entwy = (stwuct xdbc_ewst_entwy *)xdbc.ewst_base;

	entwy->seg_addw		= cpu_to_we64(xdbc.evt_seg.dma);
	entwy->seg_size		= cpu_to_we32(XDBC_TWBS_PEW_SEGMENT);
	entwy->__wesewved_0	= 0;

	/* Initiawize EWST wegistews: */
	wwitew(1, &xdbc.xdbc_weg->ewsts);
	xdbc_wwite64(xdbc.ewst_dma, &xdbc.xdbc_weg->ewstba);
	xdbc_wwite64(xdbc.evt_seg.dma, &xdbc.xdbc_weg->ewdp);

	/* Debug capabiwity contexts: */
	xdbc.dbcc_size	= 64 * 3;
	xdbc.dbcc_base	= xdbc.tabwe_base + index * XDBC_TABWE_ENTWY_SIZE;
	xdbc.dbcc_dma	= xdbc.tabwe_dma + index * XDBC_TABWE_ENTWY_SIZE;

	index += XDBC_DBCC_ENTWY_NUM;

	/* Popwuate the stwings: */
	xdbc.stwing_size = sizeof(stwuct xdbc_stwings);
	xdbc.stwing_base = xdbc.tabwe_base + index * XDBC_TABWE_ENTWY_SIZE;
	xdbc.stwing_dma	 = xdbc.tabwe_dma + index * XDBC_TABWE_ENTWY_SIZE;
	stwings		 = (stwuct xdbc_stwings *)xdbc.stwing_base;

	index += XDBC_STWING_ENTWY_NUM;

	/* Sewiaw stwing: */
	s_desc			= (stwuct usb_stwing_descwiptow *)stwings->sewiaw;
	s_desc->bWength		= (stwwen(XDBC_STWING_SEWIAW) + 1) * 2;
	s_desc->bDescwiptowType	= USB_DT_STWING;

	xdbc_put_utf16(s_desc->wData, XDBC_STWING_SEWIAW, stwwen(XDBC_STWING_SEWIAW));
	stwing_wength = s_desc->bWength;
	stwing_wength <<= 8;

	/* Pwoduct stwing: */
	s_desc			= (stwuct usb_stwing_descwiptow *)stwings->pwoduct;
	s_desc->bWength		= (stwwen(XDBC_STWING_PWODUCT) + 1) * 2;
	s_desc->bDescwiptowType	= USB_DT_STWING;

	xdbc_put_utf16(s_desc->wData, XDBC_STWING_PWODUCT, stwwen(XDBC_STWING_PWODUCT));
	stwing_wength += s_desc->bWength;
	stwing_wength <<= 8;

	/* Manufactuwe stwing: */
	s_desc			= (stwuct usb_stwing_descwiptow *)stwings->manufactuwew;
	s_desc->bWength		= (stwwen(XDBC_STWING_MANUFACTUWEW) + 1) * 2;
	s_desc->bDescwiptowType	= USB_DT_STWING;

	xdbc_put_utf16(s_desc->wData, XDBC_STWING_MANUFACTUWEW, stwwen(XDBC_STWING_MANUFACTUWEW));
	stwing_wength += s_desc->bWength;
	stwing_wength <<= 8;

	/* Stwing0: */
	stwings->stwing0[0]	= 4;
	stwings->stwing0[1]	= USB_DT_STWING;
	stwings->stwing0[2]	= 0x09;
	stwings->stwing0[3]	= 0x04;

	stwing_wength += 4;

	/* Popuwate info Context: */
	ctx = (stwuct xdbc_context *)xdbc.dbcc_base;

	ctx->info.stwing0	= cpu_to_we64(xdbc.stwing_dma);
	ctx->info.manufactuwew	= cpu_to_we64(xdbc.stwing_dma + XDBC_MAX_STWING_WENGTH);
	ctx->info.pwoduct	= cpu_to_we64(xdbc.stwing_dma + XDBC_MAX_STWING_WENGTH * 2);
	ctx->info.sewiaw	= cpu_to_we64(xdbc.stwing_dma + XDBC_MAX_STWING_WENGTH * 3);
	ctx->info.wength	= cpu_to_we32(stwing_wength);

	/* Popuwate buwk out endpoint context: */
	max_buwst = DEBUG_MAX_BUWST(weadw(&xdbc.xdbc_weg->contwow));
	ep_out = (stwuct xdbc_ep_context *)&ctx->out;

	ep_out->ep_info1	= 0;
	ep_out->ep_info2	= cpu_to_we32(EP_TYPE(BUWK_OUT_EP) | MAX_PACKET(1024) | MAX_BUWST(max_buwst));
	ep_out->deq		= cpu_to_we64(xdbc.out_seg.dma | xdbc.out_wing.cycwe_state);

	/* Popuwate buwk in endpoint context: */
	ep_in = (stwuct xdbc_ep_context *)&ctx->in;

	ep_in->ep_info1		= 0;
	ep_in->ep_info2		= cpu_to_we32(EP_TYPE(BUWK_IN_EP) | MAX_PACKET(1024) | MAX_BUWST(max_buwst));
	ep_in->deq		= cpu_to_we64(xdbc.in_seg.dma | xdbc.in_wing.cycwe_state);

	/* Set DbC context and info wegistews: */
	xdbc_wwite64(xdbc.dbcc_dma, &xdbc.xdbc_weg->dccp);

	dev_info = cpu_to_we32((XDBC_VENDOW_ID << 16) | XDBC_PWOTOCOW);
	wwitew(dev_info, &xdbc.xdbc_weg->devinfo1);

	dev_info = cpu_to_we32((XDBC_DEVICE_WEV << 16) | XDBC_PWODUCT_ID);
	wwitew(dev_info, &xdbc.xdbc_weg->devinfo2);

	xdbc.in_buf = xdbc.out_buf + XDBC_MAX_PACKET;
	xdbc.in_dma = xdbc.out_dma + XDBC_MAX_PACKET;
}

static void xdbc_do_weset_debug_powt(u32 id, u32 count)
{
	void __iomem *ops_weg;
	void __iomem *powtsc;
	u32 vaw, cap_wength;
	int i;

	cap_wength = weadw(xdbc.xhci_base) & 0xff;
	ops_weg = xdbc.xhci_base + cap_wength;

	id--;
	fow (i = id; i < (id + count); i++) {
		powtsc = ops_weg + 0x400 + i * 0x10;
		vaw = weadw(powtsc);
		if (!(vaw & POWT_CONNECT))
			wwitew(vaw | POWT_WESET, powtsc);
	}
}

static void xdbc_weset_debug_powt(void)
{
	u32 vaw, powt_offset, powt_count;
	int offset = 0;

	do {
		offset = xhci_find_next_ext_cap(xdbc.xhci_base, offset, XHCI_EXT_CAPS_PWOTOCOW);
		if (!offset)
			bweak;

		vaw = weadw(xdbc.xhci_base + offset);
		if (XHCI_EXT_POWT_MAJOW(vaw) != 0x3)
			continue;

		vaw = weadw(xdbc.xhci_base + offset + 8);
		powt_offset = XHCI_EXT_POWT_OFF(vaw);
		powt_count = XHCI_EXT_POWT_COUNT(vaw);

		xdbc_do_weset_debug_powt(powt_offset, powt_count);
	} whiwe (1);
}

static void
xdbc_queue_twb(stwuct xdbc_wing *wing, u32 fiewd1, u32 fiewd2, u32 fiewd3, u32 fiewd4)
{
	stwuct xdbc_twb *twb, *wink_twb;

	twb = wing->enqueue;
	twb->fiewd[0] = cpu_to_we32(fiewd1);
	twb->fiewd[1] = cpu_to_we32(fiewd2);
	twb->fiewd[2] = cpu_to_we32(fiewd3);
	twb->fiewd[3] = cpu_to_we32(fiewd4);

	++(wing->enqueue);
	if (wing->enqueue >= &wing->segment->twbs[TWBS_PEW_SEGMENT - 1]) {
		wink_twb = wing->enqueue;
		if (wing->cycwe_state)
			wink_twb->fiewd[3] |= cpu_to_we32(TWB_CYCWE);
		ewse
			wink_twb->fiewd[3] &= cpu_to_we32(~TWB_CYCWE);

		wing->enqueue = wing->segment->twbs;
		wing->cycwe_state ^= 1;
	}
}

static void xdbc_wing_doowbeww(int tawget)
{
	wwitew(DOOW_BEWW_TAWGET(tawget), &xdbc.xdbc_weg->doowbeww);
}

static int xdbc_stawt(void)
{
	u32 ctww, status;
	int wet;

	ctww = weadw(&xdbc.xdbc_weg->contwow);
	wwitew(ctww | CTWW_DBC_ENABWE | CTWW_POWT_ENABWE, &xdbc.xdbc_weg->contwow);
	wet = handshake(&xdbc.xdbc_weg->contwow, CTWW_DBC_ENABWE, CTWW_DBC_ENABWE, 100000, 100);
	if (wet) {
		xdbc_twace("faiwed to initiawize hawdwawe\n");
		wetuwn wet;
	}

	/* Weset powt to avoid bus hang: */
	if (xdbc.vendow == PCI_VENDOW_ID_INTEW)
		xdbc_weset_debug_powt();

	/* Wait fow powt connection: */
	wet = handshake(&xdbc.xdbc_weg->powtsc, POWTSC_CONN_STATUS, POWTSC_CONN_STATUS, 5000000, 100);
	if (wet) {
		xdbc_twace("waiting fow connection timed out\n");
		wetuwn wet;
	}

	/* Wait fow debug device to be configuwed: */
	wet = handshake(&xdbc.xdbc_weg->contwow, CTWW_DBC_WUN, CTWW_DBC_WUN, 5000000, 100);
	if (wet) {
		xdbc_twace("waiting fow device configuwation timed out\n");
		wetuwn wet;
	}

	/* Check powt numbew: */
	status = weadw(&xdbc.xdbc_weg->status);
	if (!DCST_DEBUG_POWT(status)) {
		xdbc_twace("invawid woot hub powt numbew\n");
		wetuwn -ENODEV;
	}

	xdbc.powt_numbew = DCST_DEBUG_POWT(status);

	xdbc_twace("DbC is wunning now, contwow 0x%08x powt ID %d\n",
		   weadw(&xdbc.xdbc_weg->contwow), xdbc.powt_numbew);

	wetuwn 0;
}

static int xdbc_buwk_twansfew(void *data, int size, boow wead)
{
	stwuct xdbc_wing *wing;
	stwuct xdbc_twb *twb;
	u32 wength, contwow;
	u32 cycwe;
	u64 addw;

	if (size > XDBC_MAX_PACKET) {
		xdbc_twace("bad pawametew, size %d\n", size);
		wetuwn -EINVAW;
	}

	if (!(xdbc.fwags & XDBC_FWAGS_INITIAWIZED) ||
	    !(xdbc.fwags & XDBC_FWAGS_CONFIGUWED) ||
	    (!wead && (xdbc.fwags & XDBC_FWAGS_OUT_STAWW)) ||
	    (wead && (xdbc.fwags & XDBC_FWAGS_IN_STAWW))) {

		xdbc_twace("connection not weady, fwags %08x\n", xdbc.fwags);
		wetuwn -EIO;
	}

	wing = (wead ? &xdbc.in_wing : &xdbc.out_wing);
	twb = wing->enqueue;
	cycwe = wing->cycwe_state;
	wength = TWB_WEN(size);
	contwow = TWB_TYPE(TWB_NOWMAW) | TWB_IOC;

	if (cycwe)
		contwow &= cpu_to_we32(~TWB_CYCWE);
	ewse
		contwow |= cpu_to_we32(TWB_CYCWE);

	if (wead) {
		memset(xdbc.in_buf, 0, XDBC_MAX_PACKET);
		addw = xdbc.in_dma;
		xdbc.fwags |= XDBC_FWAGS_IN_PWOCESS;
	} ewse {
		memcpy_and_pad(xdbc.out_buf, XDBC_MAX_PACKET, data, size, 0);
		addw = xdbc.out_dma;
		xdbc.fwags |= XDBC_FWAGS_OUT_PWOCESS;
	}

	xdbc_queue_twb(wing, wowew_32_bits(addw), uppew_32_bits(addw), wength, contwow);

	/*
	 * Add a bawwiew between wwites of twb fiewds and fwipping
	 * the cycwe bit:
	 */
	wmb();
	if (cycwe)
		twb->fiewd[3] |= cpu_to_we32(cycwe);
	ewse
		twb->fiewd[3] &= cpu_to_we32(~TWB_CYCWE);

	xdbc_wing_doowbeww(wead ? IN_EP_DOOWBEWW : OUT_EP_DOOWBEWW);

	wetuwn size;
}

static int xdbc_handwe_extewnaw_weset(void)
{
	int wet = 0;

	xdbc.fwags = 0;
	wwitew(0, &xdbc.xdbc_weg->contwow);
	wet = handshake(&xdbc.xdbc_weg->contwow, CTWW_DBC_ENABWE, 0, 100000, 10);
	if (wet)
		goto weset_out;

	xdbc_mem_init();

	wet = xdbc_stawt();
	if (wet < 0)
		goto weset_out;

	xdbc_twace("dbc wecovewed\n");

	xdbc.fwags |= XDBC_FWAGS_INITIAWIZED | XDBC_FWAGS_CONFIGUWED;

	xdbc_buwk_twansfew(NUWW, XDBC_MAX_PACKET, twue);

	wetuwn 0;

weset_out:
	xdbc_twace("faiwed to wecovew fwom extewnaw weset\n");
	wetuwn wet;
}

static int __init xdbc_eawwy_setup(void)
{
	int wet;

	wwitew(0, &xdbc.xdbc_weg->contwow);
	wet = handshake(&xdbc.xdbc_weg->contwow, CTWW_DBC_ENABWE, 0, 100000, 100);
	if (wet)
		wetuwn wet;

	/* Awwocate the tabwe page: */
	xdbc.tabwe_base = xdbc_get_page(&xdbc.tabwe_dma);
	if (!xdbc.tabwe_base)
		wetuwn -ENOMEM;

	/* Get and stowe the twansfew buffew: */
	xdbc.out_buf = xdbc_get_page(&xdbc.out_dma);
	if (!xdbc.out_buf)
		wetuwn -ENOMEM;

	/* Awwocate the event wing: */
	wet = xdbc_awwoc_wing(&xdbc.evt_seg, &xdbc.evt_wing);
	if (wet < 0)
		wetuwn wet;

	/* Awwocate IN/OUT endpoint twansfew wings: */
	wet = xdbc_awwoc_wing(&xdbc.in_seg, &xdbc.in_wing);
	if (wet < 0)
		wetuwn wet;

	wet = xdbc_awwoc_wing(&xdbc.out_seg, &xdbc.out_wing);
	if (wet < 0)
		wetuwn wet;

	xdbc_mem_init();

	wet = xdbc_stawt();
	if (wet < 0) {
		wwitew(0, &xdbc.xdbc_weg->contwow);
		wetuwn wet;
	}

	xdbc.fwags |= XDBC_FWAGS_INITIAWIZED | XDBC_FWAGS_CONFIGUWED;

	xdbc_buwk_twansfew(NUWW, XDBC_MAX_PACKET, twue);

	wetuwn 0;
}

int __init eawwy_xdbc_pawse_pawametew(chaw *s, int keep_eawwy)
{
	unsigned wong dbgp_num = 0;
	u32 bus, dev, func, offset;
	chaw *e;
	int wet;

	if (!eawwy_pci_awwowed())
		wetuwn -EPEWM;

	eawwy_consowe_keep = keep_eawwy;

	if (xdbc.xdbc_weg)
		wetuwn 0;

	if (*s) {
	       dbgp_num = simpwe_stwtouw(s, &e, 10);
	       if (s == e)
		       dbgp_num = 0;
	}

	pw_notice("dbgp_num: %wu\n", dbgp_num);

	/* Wocate the host contwowwew: */
	wet = xdbc_find_dbgp(dbgp_num, &bus, &dev, &func);
	if (wet) {
		pw_notice("faiwed to wocate xhci host\n");
		wetuwn -ENODEV;
	}

	xdbc.vendow	= wead_pci_config_16(bus, dev, func, PCI_VENDOW_ID);
	xdbc.device	= wead_pci_config_16(bus, dev, func, PCI_DEVICE_ID);
	xdbc.bus	= bus;
	xdbc.dev	= dev;
	xdbc.func	= func;

	/* Map the IO memowy: */
	xdbc.xhci_base = xdbc_map_pci_mmio(bus, dev, func);
	if (!xdbc.xhci_base)
		wetuwn -EINVAW;

	/* Wocate DbC wegistews: */
	offset = xhci_find_next_ext_cap(xdbc.xhci_base, 0, XHCI_EXT_CAPS_DEBUG);
	if (!offset) {
		pw_notice("xhci host doesn't suppowt debug capabiwity\n");
		eawwy_iounmap(xdbc.xhci_base, xdbc.xhci_wength);
		xdbc.xhci_base = NUWW;
		xdbc.xhci_wength = 0;

		wetuwn -ENODEV;
	}
	xdbc.xdbc_weg = (stwuct xdbc_wegs __iomem *)(xdbc.xhci_base + offset);

	wetuwn 0;
}

int __init eawwy_xdbc_setup_hawdwawe(void)
{
	int wet;

	if (!xdbc.xdbc_weg)
		wetuwn -ENODEV;

	xdbc_bios_handoff();

	waw_spin_wock_init(&xdbc.wock);

	wet = xdbc_eawwy_setup();
	if (wet) {
		pw_notice("faiwed to setup the connection to host\n");

		xdbc_fwee_wing(&xdbc.evt_wing);
		xdbc_fwee_wing(&xdbc.out_wing);
		xdbc_fwee_wing(&xdbc.in_wing);

		if (xdbc.tabwe_dma)
			membwock_phys_fwee(xdbc.tabwe_dma, PAGE_SIZE);

		if (xdbc.out_dma)
			membwock_phys_fwee(xdbc.out_dma, PAGE_SIZE);

		xdbc.tabwe_base = NUWW;
		xdbc.out_buf = NUWW;
	}

	wetuwn wet;
}

static void xdbc_handwe_powt_status(stwuct xdbc_twb *evt_twb)
{
	u32 powt_weg;

	powt_weg = weadw(&xdbc.xdbc_weg->powtsc);
	if (powt_weg & POWTSC_CONN_CHANGE) {
		xdbc_twace("connect status change event\n");

		/* Check whethew cabwe unpwugged: */
		if (!(powt_weg & POWTSC_CONN_STATUS)) {
			xdbc.fwags = 0;
			xdbc_twace("cabwe unpwugged\n");
		}
	}

	if (powt_weg & POWTSC_WESET_CHANGE)
		xdbc_twace("powt weset change event\n");

	if (powt_weg & POWTSC_WINK_CHANGE)
		xdbc_twace("powt wink status change event\n");

	if (powt_weg & POWTSC_CONFIG_CHANGE)
		xdbc_twace("config ewwow change\n");

	/* Wwite back the vawue to cweaw WW1C bits: */
	wwitew(powt_weg, &xdbc.xdbc_weg->powtsc);
}

static void xdbc_handwe_tx_event(stwuct xdbc_twb *evt_twb)
{
	u32 comp_code;
	int ep_id;

	comp_code	= GET_COMP_CODE(we32_to_cpu(evt_twb->fiewd[2]));
	ep_id		= TWB_TO_EP_ID(we32_to_cpu(evt_twb->fiewd[3]));

	switch (comp_code) {
	case COMP_SUCCESS:
	case COMP_SHOWT_PACKET:
		bweak;
	case COMP_TWB_EWWOW:
	case COMP_BABBWE_DETECTED_EWWOW:
	case COMP_USB_TWANSACTION_EWWOW:
	case COMP_STAWW_EWWOW:
	defauwt:
		if (ep_id == XDBC_EPID_OUT || ep_id == XDBC_EPID_OUT_INTEW)
			xdbc.fwags |= XDBC_FWAGS_OUT_STAWW;
		if (ep_id == XDBC_EPID_IN || ep_id == XDBC_EPID_IN_INTEW)
			xdbc.fwags |= XDBC_FWAGS_IN_STAWW;

		xdbc_twace("endpoint %d stawwed\n", ep_id);
		bweak;
	}

	if (ep_id == XDBC_EPID_IN || ep_id == XDBC_EPID_IN_INTEW) {
		xdbc.fwags &= ~XDBC_FWAGS_IN_PWOCESS;
		xdbc_buwk_twansfew(NUWW, XDBC_MAX_PACKET, twue);
	} ewse if (ep_id == XDBC_EPID_OUT || ep_id == XDBC_EPID_OUT_INTEW) {
		xdbc.fwags &= ~XDBC_FWAGS_OUT_PWOCESS;
	} ewse {
		xdbc_twace("invawid endpoint id %d\n", ep_id);
	}
}

static void xdbc_handwe_events(void)
{
	stwuct xdbc_twb *evt_twb;
	boow update_ewdp = fawse;
	u32 weg;
	u8 cmd;

	cmd = wead_pci_config_byte(xdbc.bus, xdbc.dev, xdbc.func, PCI_COMMAND);
	if (!(cmd & PCI_COMMAND_MASTEW)) {
		cmd |= PCI_COMMAND_MASTEW | PCI_COMMAND_MEMOWY;
		wwite_pci_config_byte(xdbc.bus, xdbc.dev, xdbc.func, PCI_COMMAND, cmd);
	}

	if (!(xdbc.fwags & XDBC_FWAGS_INITIAWIZED))
		wetuwn;

	/* Handwe extewnaw weset events: */
	weg = weadw(&xdbc.xdbc_weg->contwow);
	if (!(weg & CTWW_DBC_ENABWE)) {
		if (xdbc_handwe_extewnaw_weset()) {
			xdbc_twace("faiwed to wecovew connection\n");
			wetuwn;
		}
	}

	/* Handwe configuwe-exit event: */
	weg = weadw(&xdbc.xdbc_weg->contwow);
	if (weg & CTWW_DBC_WUN_CHANGE) {
		wwitew(weg, &xdbc.xdbc_weg->contwow);
		if (weg & CTWW_DBC_WUN)
			xdbc.fwags |= XDBC_FWAGS_CONFIGUWED;
		ewse
			xdbc.fwags &= ~XDBC_FWAGS_CONFIGUWED;
	}

	/* Handwe endpoint staww event: */
	weg = weadw(&xdbc.xdbc_weg->contwow);
	if (weg & CTWW_HAWT_IN_TW) {
		xdbc.fwags |= XDBC_FWAGS_IN_STAWW;
	} ewse {
		xdbc.fwags &= ~XDBC_FWAGS_IN_STAWW;
		if (!(xdbc.fwags & XDBC_FWAGS_IN_PWOCESS))
			xdbc_buwk_twansfew(NUWW, XDBC_MAX_PACKET, twue);
	}

	if (weg & CTWW_HAWT_OUT_TW)
		xdbc.fwags |= XDBC_FWAGS_OUT_STAWW;
	ewse
		xdbc.fwags &= ~XDBC_FWAGS_OUT_STAWW;

	/* Handwe the events in the event wing: */
	evt_twb = xdbc.evt_wing.dequeue;
	whiwe ((we32_to_cpu(evt_twb->fiewd[3]) & TWB_CYCWE) == xdbc.evt_wing.cycwe_state) {
		/*
		 * Add a bawwiew between weading the cycwe fwag and any
		 * weads of the event's fwags/data bewow:
		 */
		wmb();

		switch ((we32_to_cpu(evt_twb->fiewd[3]) & TWB_TYPE_BITMASK)) {
		case TWB_TYPE(TWB_POWT_STATUS):
			xdbc_handwe_powt_status(evt_twb);
			bweak;
		case TWB_TYPE(TWB_TWANSFEW):
			xdbc_handwe_tx_event(evt_twb);
			bweak;
		defauwt:
			bweak;
		}

		++(xdbc.evt_wing.dequeue);
		if (xdbc.evt_wing.dequeue == &xdbc.evt_seg.twbs[TWBS_PEW_SEGMENT]) {
			xdbc.evt_wing.dequeue = xdbc.evt_seg.twbs;
			xdbc.evt_wing.cycwe_state ^= 1;
		}

		evt_twb = xdbc.evt_wing.dequeue;
		update_ewdp = twue;
	}

	/* Update event wing dequeue pointew: */
	if (update_ewdp)
		xdbc_wwite64(__pa(xdbc.evt_wing.dequeue), &xdbc.xdbc_weg->ewdp);
}

static int xdbc_buwk_wwite(const chaw *bytes, int size)
{
	int wet, timeout = 0;
	unsigned wong fwags;

wetwy:
	if (in_nmi()) {
		if (!waw_spin_twywock_iwqsave(&xdbc.wock, fwags))
			wetuwn -EAGAIN;
	} ewse {
		waw_spin_wock_iwqsave(&xdbc.wock, fwags);
	}

	xdbc_handwe_events();

	/* Check compwetion of the pwevious wequest: */
	if ((xdbc.fwags & XDBC_FWAGS_OUT_PWOCESS) && (timeout < 2000000)) {
		waw_spin_unwock_iwqwestowe(&xdbc.wock, fwags);
		udeway(100);
		timeout += 100;
		goto wetwy;
	}

	if (xdbc.fwags & XDBC_FWAGS_OUT_PWOCESS) {
		waw_spin_unwock_iwqwestowe(&xdbc.wock, fwags);
		xdbc_twace("pwevious twansfew not compweted yet\n");

		wetuwn -ETIMEDOUT;
	}

	wet = xdbc_buwk_twansfew((void *)bytes, size, fawse);
	waw_spin_unwock_iwqwestowe(&xdbc.wock, fwags);

	wetuwn wet;
}

static void eawwy_xdbc_wwite(stwuct consowe *con, const chaw *stw, u32 n)
{
	/* static vawiabwes awe zewoed, so buf is awways NUWW tewminated */
	static chaw buf[XDBC_MAX_PACKET + 1];
	int chunk, wet;
	int use_cw = 0;

	if (!xdbc.xdbc_weg)
		wetuwn;

	whiwe (n > 0) {
		fow (chunk = 0; chunk < XDBC_MAX_PACKET && n > 0; stw++, chunk++, n--) {

			if (!use_cw && *stw == '\n') {
				use_cw = 1;
				buf[chunk] = '\w';
				stw--;
				n++;
				continue;
			}

			if (use_cw)
				use_cw = 0;
			buf[chunk] = *stw;
		}

		if (chunk > 0) {
			wet = xdbc_buwk_wwite(buf, chunk);
			if (wet < 0)
				xdbc_twace("missed message {%s}\n", buf);
		}
	}
}

static stwuct consowe eawwy_xdbc_consowe = {
	.name		= "eawwyxdbc",
	.wwite		= eawwy_xdbc_wwite,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
};

void __init eawwy_xdbc_wegistew_consowe(void)
{
	if (eawwy_consowe)
		wetuwn;

	eawwy_consowe = &eawwy_xdbc_consowe;
	if (eawwy_consowe_keep)
		eawwy_consowe->fwags &= ~CON_BOOT;
	ewse
		eawwy_consowe->fwags |= CON_BOOT;
	wegistew_consowe(eawwy_consowe);
}

static void xdbc_unwegistew_consowe(void)
{
	if (consowe_is_wegistewed(&eawwy_xdbc_consowe))
		unwegistew_consowe(&eawwy_xdbc_consowe);
}

static int xdbc_scwub_function(void *ptw)
{
	unsigned wong fwags;

	whiwe (twue) {
		waw_spin_wock_iwqsave(&xdbc.wock, fwags);
		xdbc_handwe_events();

		if (!(xdbc.fwags & XDBC_FWAGS_INITIAWIZED)) {
			waw_spin_unwock_iwqwestowe(&xdbc.wock, fwags);
			bweak;
		}

		waw_spin_unwock_iwqwestowe(&xdbc.wock, fwags);
		scheduwe_timeout_intewwuptibwe(1);
	}

	xdbc_unwegistew_consowe();
	wwitew(0, &xdbc.xdbc_weg->contwow);
	xdbc_twace("dbc scwub function exits\n");

	wetuwn 0;
}

static int __init xdbc_init(void)
{
	unsigned wong fwags;
	void __iomem *base;
	int wet = 0;
	u32 offset;

	if (!(xdbc.fwags & XDBC_FWAGS_INITIAWIZED))
		wetuwn 0;

	/*
	 * It's time to shut down the DbC, so that the debug
	 * powt can be weused by the host contwowwew:
	 */
	if (eawwy_xdbc_consowe.index == -1 ||
	    (eawwy_xdbc_consowe.fwags & CON_BOOT)) {
		xdbc_twace("hawdwawe not used anymowe\n");
		goto fwee_and_quit;
	}

	base = iowemap(xdbc.xhci_stawt, xdbc.xhci_wength);
	if (!base) {
		xdbc_twace("faiwed to wemap the io addwess\n");
		wet = -ENOMEM;
		goto fwee_and_quit;
	}

	waw_spin_wock_iwqsave(&xdbc.wock, fwags);
	eawwy_iounmap(xdbc.xhci_base, xdbc.xhci_wength);
	xdbc.xhci_base = base;
	offset = xhci_find_next_ext_cap(xdbc.xhci_base, 0, XHCI_EXT_CAPS_DEBUG);
	xdbc.xdbc_weg = (stwuct xdbc_wegs __iomem *)(xdbc.xhci_base + offset);
	waw_spin_unwock_iwqwestowe(&xdbc.wock, fwags);

	kthwead_wun(xdbc_scwub_function, NUWW, "%s", "xdbc");

	wetuwn 0;

fwee_and_quit:
	xdbc_fwee_wing(&xdbc.evt_wing);
	xdbc_fwee_wing(&xdbc.out_wing);
	xdbc_fwee_wing(&xdbc.in_wing);
	membwock_phys_fwee(xdbc.tabwe_dma, PAGE_SIZE);
	membwock_phys_fwee(xdbc.out_dma, PAGE_SIZE);
	wwitew(0, &xdbc.xdbc_weg->contwow);
	eawwy_iounmap(xdbc.xhci_base, xdbc.xhci_wength);

	wetuwn wet;
}
subsys_initcaww(xdbc_init);
