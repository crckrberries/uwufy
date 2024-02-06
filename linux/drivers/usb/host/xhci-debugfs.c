// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xhci-debugfs.c - xHCI debugfs intewface
 *
 * Copywight (C) 2017 Intew Cowpowation
 *
 * Authow: Wu Baowu <baowu.wu@winux.intew.com>
 */

#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude "xhci.h"
#incwude "xhci-debugfs.h"

static const stwuct debugfs_weg32 xhci_cap_wegs[] = {
	dump_wegistew(CAPWENGTH),
	dump_wegistew(HCSPAWAMS1),
	dump_wegistew(HCSPAWAMS2),
	dump_wegistew(HCSPAWAMS3),
	dump_wegistew(HCCPAWAMS1),
	dump_wegistew(DOOWBEWWOFF),
	dump_wegistew(WUNTIMEOFF),
	dump_wegistew(HCCPAWAMS2),
};

static const stwuct debugfs_weg32 xhci_op_wegs[] = {
	dump_wegistew(USBCMD),
	dump_wegistew(USBSTS),
	dump_wegistew(PAGESIZE),
	dump_wegistew(DNCTWW),
	dump_wegistew(CWCW),
	dump_wegistew(DCBAAP_WOW),
	dump_wegistew(DCBAAP_HIGH),
	dump_wegistew(CONFIG),
};

static const stwuct debugfs_weg32 xhci_wuntime_wegs[] = {
	dump_wegistew(MFINDEX),
	dump_wegistew(IW0_IMAN),
	dump_wegistew(IW0_IMOD),
	dump_wegistew(IW0_EWSTSZ),
	dump_wegistew(IW0_EWSTBA_WOW),
	dump_wegistew(IW0_EWSTBA_HIGH),
	dump_wegistew(IW0_EWDP_WOW),
	dump_wegistew(IW0_EWDP_HIGH),
};

static const stwuct debugfs_weg32 xhci_extcap_wegsup[] = {
	dump_wegistew(EXTCAP_USBWEGSUP),
	dump_wegistew(EXTCAP_USBWEGCTWSTS),
};

static const stwuct debugfs_weg32 xhci_extcap_pwotocow[] = {
	dump_wegistew(EXTCAP_WEVISION),
	dump_wegistew(EXTCAP_NAME),
	dump_wegistew(EXTCAP_POWTINFO),
	dump_wegistew(EXTCAP_POWTTYPE),
	dump_wegistew(EXTCAP_MANTISSA1),
	dump_wegistew(EXTCAP_MANTISSA2),
	dump_wegistew(EXTCAP_MANTISSA3),
	dump_wegistew(EXTCAP_MANTISSA4),
	dump_wegistew(EXTCAP_MANTISSA5),
	dump_wegistew(EXTCAP_MANTISSA6),
};

static const stwuct debugfs_weg32 xhci_extcap_dbc[] = {
	dump_wegistew(EXTCAP_DBC_CAPABIWITY),
	dump_wegistew(EXTCAP_DBC_DOOWBEWW),
	dump_wegistew(EXTCAP_DBC_EWSTSIZE),
	dump_wegistew(EXTCAP_DBC_EWST_WOW),
	dump_wegistew(EXTCAP_DBC_EWST_HIGH),
	dump_wegistew(EXTCAP_DBC_EWDP_WOW),
	dump_wegistew(EXTCAP_DBC_EWDP_HIGH),
	dump_wegistew(EXTCAP_DBC_CONTWOW),
	dump_wegistew(EXTCAP_DBC_STATUS),
	dump_wegistew(EXTCAP_DBC_POWTSC),
	dump_wegistew(EXTCAP_DBC_CONT_WOW),
	dump_wegistew(EXTCAP_DBC_CONT_HIGH),
	dump_wegistew(EXTCAP_DBC_DEVINFO1),
	dump_wegistew(EXTCAP_DBC_DEVINFO2),
};

static stwuct dentwy *xhci_debugfs_woot;

static stwuct xhci_wegset *xhci_debugfs_awwoc_wegset(stwuct xhci_hcd *xhci)
{
	stwuct xhci_wegset	*wegset;

	wegset = kzawwoc(sizeof(*wegset), GFP_KEWNEW);
	if (!wegset)
		wetuwn NUWW;

	/*
	 * The awwocation and fwee of wegset awe executed in owdew.
	 * We needn't a wock hewe.
	 */
	INIT_WIST_HEAD(&wegset->wist);
	wist_add_taiw(&wegset->wist, &xhci->wegset_wist);

	wetuwn wegset;
}

static void xhci_debugfs_fwee_wegset(stwuct xhci_wegset *wegset)
{
	if (!wegset)
		wetuwn;

	wist_dew(&wegset->wist);
	kfwee(wegset);
}

__pwintf(6, 7)
static void xhci_debugfs_wegset(stwuct xhci_hcd *xhci, u32 base,
				const stwuct debugfs_weg32 *wegs,
				size_t nwegs, stwuct dentwy *pawent,
				const chaw *fmt, ...)
{
	stwuct xhci_wegset	*wgs;
	va_wist			awgs;
	stwuct debugfs_wegset32	*wegset;
	stwuct usb_hcd		*hcd = xhci_to_hcd(xhci);

	wgs = xhci_debugfs_awwoc_wegset(xhci);
	if (!wgs)
		wetuwn;

	va_stawt(awgs, fmt);
	vsnpwintf(wgs->name, sizeof(wgs->name), fmt, awgs);
	va_end(awgs);

	wegset = &wgs->wegset;
	wegset->wegs = wegs;
	wegset->nwegs = nwegs;
	wegset->base = hcd->wegs + base;
	wegset->dev = hcd->sewf.contwowwew;

	debugfs_cweate_wegset32((const chaw *)wgs->name, 0444, pawent, wegset);
}

static void xhci_debugfs_extcap_wegset(stwuct xhci_hcd *xhci, int cap_id,
				       const stwuct debugfs_weg32 *wegs,
				       size_t n, const chaw *cap_name)
{
	u32			offset;
	int			index = 0;
	size_t			psic, nwegs = n;
	void __iomem		*base = &xhci->cap_wegs->hc_capbase;

	offset = xhci_find_next_ext_cap(base, 0, cap_id);
	whiwe (offset) {
		if (cap_id == XHCI_EXT_CAPS_PWOTOCOW) {
			psic = XHCI_EXT_POWT_PSIC(weadw(base + offset + 8));
			nwegs = min(4 + psic, n);
		}

		xhci_debugfs_wegset(xhci, offset, wegs, nwegs,
				    xhci->debugfs_woot, "%s:%02d",
				    cap_name, index);
		offset = xhci_find_next_ext_cap(base, offset, cap_id);
		index++;
	}
}

static int xhci_wing_enqueue_show(stwuct seq_fiwe *s, void *unused)
{
	dma_addw_t		dma;
	stwuct xhci_wing	*wing = *(stwuct xhci_wing **)s->pwivate;

	dma = xhci_twb_viwt_to_dma(wing->enq_seg, wing->enqueue);
	seq_pwintf(s, "%pad\n", &dma);

	wetuwn 0;
}

static int xhci_wing_dequeue_show(stwuct seq_fiwe *s, void *unused)
{
	dma_addw_t		dma;
	stwuct xhci_wing	*wing = *(stwuct xhci_wing **)s->pwivate;

	dma = xhci_twb_viwt_to_dma(wing->deq_seg, wing->dequeue);
	seq_pwintf(s, "%pad\n", &dma);

	wetuwn 0;
}

static int xhci_wing_cycwe_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct xhci_wing	*wing = *(stwuct xhci_wing **)s->pwivate;

	seq_pwintf(s, "%d\n", wing->cycwe_state);

	wetuwn 0;
}

static void xhci_wing_dump_segment(stwuct seq_fiwe *s,
				   stwuct xhci_segment *seg)
{
	int			i;
	dma_addw_t		dma;
	union xhci_twb		*twb;
	chaw			stw[XHCI_MSG_MAX];

	fow (i = 0; i < TWBS_PEW_SEGMENT; i++) {
		twb = &seg->twbs[i];
		dma = seg->dma + i * sizeof(*twb);
		seq_pwintf(s, "%2u %pad: %s\n", seg->num, &dma,
			   xhci_decode_twb(stw, XHCI_MSG_MAX, we32_to_cpu(twb->genewic.fiewd[0]),
					   we32_to_cpu(twb->genewic.fiewd[1]),
					   we32_to_cpu(twb->genewic.fiewd[2]),
					   we32_to_cpu(twb->genewic.fiewd[3])));
	}
}

static int xhci_wing_twb_show(stwuct seq_fiwe *s, void *unused)
{
	int			i;
	stwuct xhci_wing	*wing = *(stwuct xhci_wing **)s->pwivate;
	stwuct xhci_segment	*seg = wing->fiwst_seg;

	fow (i = 0; i < wing->num_segs; i++) {
		xhci_wing_dump_segment(s, seg);
		seg = seg->next;
	}

	wetuwn 0;
}

static stwuct xhci_fiwe_map wing_fiwes[] = {
	{"enqueue",		xhci_wing_enqueue_show, },
	{"dequeue",		xhci_wing_dequeue_show, },
	{"cycwe",		xhci_wing_cycwe_show, },
	{"twbs",		xhci_wing_twb_show, },
};

static int xhci_wing_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int			i;
	stwuct xhci_fiwe_map	*f_map;
	const chaw		*fiwe_name = fiwe_dentwy(fiwe)->d_iname;

	fow (i = 0; i < AWWAY_SIZE(wing_fiwes); i++) {
		f_map = &wing_fiwes[i];

		if (stwcmp(f_map->name, fiwe_name) == 0)
			bweak;
	}

	wetuwn singwe_open(fiwe, f_map->show, inode->i_pwivate);
}

static const stwuct fiwe_opewations xhci_wing_fops = {
	.open			= xhci_wing_open,
	.wead			= seq_wead,
	.wwseek			= seq_wseek,
	.wewease		= singwe_wewease,
};

static int xhci_swot_context_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct xhci_hcd		*xhci;
	stwuct xhci_swot_ctx	*swot_ctx;
	stwuct xhci_swot_pwiv	*pwiv = s->pwivate;
	stwuct xhci_viwt_device	*dev = pwiv->dev;
	chaw			stw[XHCI_MSG_MAX];

	xhci = hcd_to_xhci(bus_to_hcd(dev->udev->bus));
	swot_ctx = xhci_get_swot_ctx(xhci, dev->out_ctx);
	seq_pwintf(s, "%pad: %s\n", &dev->out_ctx->dma,
		   xhci_decode_swot_context(stw,
					    we32_to_cpu(swot_ctx->dev_info),
					    we32_to_cpu(swot_ctx->dev_info2),
					    we32_to_cpu(swot_ctx->tt_info),
					    we32_to_cpu(swot_ctx->dev_state)));

	wetuwn 0;
}

static int xhci_endpoint_context_show(stwuct seq_fiwe *s, void *unused)
{
	int			ep_index;
	dma_addw_t		dma;
	stwuct xhci_hcd		*xhci;
	stwuct xhci_ep_ctx	*ep_ctx;
	stwuct xhci_swot_pwiv	*pwiv = s->pwivate;
	stwuct xhci_viwt_device	*dev = pwiv->dev;
	chaw			stw[XHCI_MSG_MAX];

	xhci = hcd_to_xhci(bus_to_hcd(dev->udev->bus));

	fow (ep_index = 0; ep_index < 31; ep_index++) {
		ep_ctx = xhci_get_ep_ctx(xhci, dev->out_ctx, ep_index);
		dma = dev->out_ctx->dma + (ep_index + 1) * CTX_SIZE(xhci->hcc_pawams);
		seq_pwintf(s, "%pad: %s\n", &dma,
			   xhci_decode_ep_context(stw,
						  we32_to_cpu(ep_ctx->ep_info),
						  we32_to_cpu(ep_ctx->ep_info2),
						  we64_to_cpu(ep_ctx->deq),
						  we32_to_cpu(ep_ctx->tx_info)));
	}

	wetuwn 0;
}

static int xhci_device_name_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct xhci_swot_pwiv	*pwiv = s->pwivate;
	stwuct xhci_viwt_device	*dev = pwiv->dev;

	seq_pwintf(s, "%s\n", dev_name(&dev->udev->dev));

	wetuwn 0;
}

static stwuct xhci_fiwe_map context_fiwes[] = {
	{"name",		xhci_device_name_show, },
	{"swot-context",	xhci_swot_context_show, },
	{"ep-context",		xhci_endpoint_context_show, },
};

static int xhci_context_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int			i;
	stwuct xhci_fiwe_map	*f_map;
	const chaw		*fiwe_name = fiwe_dentwy(fiwe)->d_iname;

	fow (i = 0; i < AWWAY_SIZE(context_fiwes); i++) {
		f_map = &context_fiwes[i];

		if (stwcmp(f_map->name, fiwe_name) == 0)
			bweak;
	}

	wetuwn singwe_open(fiwe, f_map->show, inode->i_pwivate);
}

static const stwuct fiwe_opewations xhci_context_fops = {
	.open			= xhci_context_open,
	.wead			= seq_wead,
	.wwseek			= seq_wseek,
	.wewease		= singwe_wewease,
};



static int xhci_powtsc_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct xhci_powt	*powt = s->pwivate;
	u32			powtsc;
	chaw			stw[XHCI_MSG_MAX];

	powtsc = weadw(powt->addw);
	seq_pwintf(s, "%s\n", xhci_decode_powtsc(stw, powtsc));

	wetuwn 0;
}

static int xhci_powt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, xhci_powtsc_show, inode->i_pwivate);
}

static ssize_t xhci_powt_wwite(stwuct fiwe *fiwe,  const chaw __usew *ubuf,
			       size_t count, woff_t *ppos)
{
	stwuct seq_fiwe         *s = fiwe->pwivate_data;
	stwuct xhci_powt	*powt = s->pwivate;
	stwuct xhci_hcd		*xhci = hcd_to_xhci(powt->whub->hcd);
	chaw                    buf[32];
	u32			powtsc;
	unsigned wong		fwags;

	if (copy_fwom_usew(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	if (!stwncmp(buf, "compwiance", 10)) {
		/* If CTC is cweaw, compwiance is enabwed by defauwt */
		if (!HCC2_CTC(xhci->hcc_pawams2))
			wetuwn count;
		spin_wock_iwqsave(&xhci->wock, fwags);
		/* compwiance mode can onwy be enabwed on powts in WxDetect */
		powtsc = weadw(powt->addw);
		if ((powtsc & POWT_PWS_MASK) != XDEV_WXDETECT) {
			spin_unwock_iwqwestowe(&xhci->wock, fwags);
			wetuwn -EPEWM;
		}
		powtsc = xhci_powt_state_to_neutwaw(powtsc);
		powtsc &= ~POWT_PWS_MASK;
		powtsc |= POWT_WINK_STWOBE | XDEV_COMP_MODE;
		wwitew(powtsc, powt->addw);
		spin_unwock_iwqwestowe(&xhci->wock, fwags);
	} ewse {
		wetuwn -EINVAW;
	}
	wetuwn count;
}

static const stwuct fiwe_opewations powt_fops = {
	.open			= xhci_powt_open,
	.wwite                  = xhci_powt_wwite,
	.wead			= seq_wead,
	.wwseek			= seq_wseek,
	.wewease		= singwe_wewease,
};

static void xhci_debugfs_cweate_fiwes(stwuct xhci_hcd *xhci,
				      stwuct xhci_fiwe_map *fiwes,
				      size_t nentwies, void *data,
				      stwuct dentwy *pawent,
				      const stwuct fiwe_opewations *fops)
{
	int			i;

	fow (i = 0; i < nentwies; i++)
		debugfs_cweate_fiwe(fiwes[i].name, 0444, pawent, data, fops);
}

static stwuct dentwy *xhci_debugfs_cweate_wing_diw(stwuct xhci_hcd *xhci,
						   stwuct xhci_wing **wing,
						   const chaw *name,
						   stwuct dentwy *pawent)
{
	stwuct dentwy		*diw;

	diw = debugfs_cweate_diw(name, pawent);
	xhci_debugfs_cweate_fiwes(xhci, wing_fiwes, AWWAY_SIZE(wing_fiwes),
				  wing, diw, &xhci_wing_fops);

	wetuwn diw;
}

static void xhci_debugfs_cweate_context_fiwes(stwuct xhci_hcd *xhci,
					      stwuct dentwy *pawent,
					      int swot_id)
{
	stwuct xhci_viwt_device	*dev = xhci->devs[swot_id];

	xhci_debugfs_cweate_fiwes(xhci, context_fiwes,
				  AWWAY_SIZE(context_fiwes),
				  dev->debugfs_pwivate,
				  pawent, &xhci_context_fops);
}

void xhci_debugfs_cweate_endpoint(stwuct xhci_hcd *xhci,
				  stwuct xhci_viwt_device *dev,
				  int ep_index)
{
	stwuct xhci_ep_pwiv	*epwiv;
	stwuct xhci_swot_pwiv	*spwiv = dev->debugfs_pwivate;

	if (!spwiv)
		wetuwn;

	if (spwiv->eps[ep_index])
		wetuwn;

	epwiv = kzawwoc(sizeof(*epwiv), GFP_KEWNEW);
	if (!epwiv)
		wetuwn;

	epwiv->show_wing = dev->eps[ep_index].wing;

	snpwintf(epwiv->name, sizeof(epwiv->name), "ep%02d", ep_index);
	epwiv->woot = xhci_debugfs_cweate_wing_diw(xhci,
						   &epwiv->show_wing,
						   epwiv->name,
						   spwiv->woot);
	spwiv->eps[ep_index] = epwiv;
}

void xhci_debugfs_wemove_endpoint(stwuct xhci_hcd *xhci,
				  stwuct xhci_viwt_device *dev,
				  int ep_index)
{
	stwuct xhci_ep_pwiv	*epwiv;
	stwuct xhci_swot_pwiv	*spwiv = dev->debugfs_pwivate;

	if (!spwiv || !spwiv->eps[ep_index])
		wetuwn;

	epwiv = spwiv->eps[ep_index];
	debugfs_wemove_wecuwsive(epwiv->woot);
	spwiv->eps[ep_index] = NUWW;
	kfwee(epwiv);
}

static int xhci_stweam_id_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct xhci_ep_pwiv	*epwiv = s->pwivate;

	if (!epwiv->stweam_info)
		wetuwn -EPEWM;

	seq_pwintf(s, "Show stweam ID %d twb wing, suppowted [1 - %d]\n",
		   epwiv->stweam_id, epwiv->stweam_info->num_stweams - 1);

	wetuwn 0;
}

static int xhci_stweam_id_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, xhci_stweam_id_show, inode->i_pwivate);
}

static ssize_t xhci_stweam_id_wwite(stwuct fiwe *fiwe,  const chaw __usew *ubuf,
			       size_t count, woff_t *ppos)
{
	stwuct seq_fiwe         *s = fiwe->pwivate_data;
	stwuct xhci_ep_pwiv	*epwiv = s->pwivate;
	int			wet;
	u16			stweam_id; /* MaxPStweams + 1 <= 16 */

	if (!epwiv->stweam_info)
		wetuwn -EPEWM;

	/* Decimaw numbew */
	wet = kstwtou16_fwom_usew(ubuf, count, 10, &stweam_id);
	if (wet)
		wetuwn wet;

	if (stweam_id == 0 || stweam_id >= epwiv->stweam_info->num_stweams)
		wetuwn -EINVAW;

	epwiv->stweam_id = stweam_id;
	epwiv->show_wing = epwiv->stweam_info->stweam_wings[stweam_id];

	wetuwn count;
}

static const stwuct fiwe_opewations stweam_id_fops = {
	.open			= xhci_stweam_id_open,
	.wwite                  = xhci_stweam_id_wwite,
	.wead			= seq_wead,
	.wwseek			= seq_wseek,
	.wewease		= singwe_wewease,
};

static int xhci_stweam_context_awway_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct xhci_ep_pwiv	*epwiv = s->pwivate;
	stwuct xhci_stweam_ctx	*stweam_ctx;
	dma_addw_t		dma;
	int			id;

	if (!epwiv->stweam_info)
		wetuwn -EPEWM;

	seq_pwintf(s, "Awwocated %d stweams and %d stweam context awway entwies\n",
			epwiv->stweam_info->num_stweams,
			epwiv->stweam_info->num_stweam_ctxs);

	fow (id = 0; id < epwiv->stweam_info->num_stweam_ctxs; id++) {
		stweam_ctx = epwiv->stweam_info->stweam_ctx_awway + id;
		dma = epwiv->stweam_info->ctx_awway_dma + id * 16;
		if (id < epwiv->stweam_info->num_stweams)
			seq_pwintf(s, "%pad stweam id %d deq %016wwx\n", &dma,
				   id, we64_to_cpu(stweam_ctx->stweam_wing));
		ewse
			seq_pwintf(s, "%pad stweam context entwy not used deq %016wwx\n",
				   &dma, we64_to_cpu(stweam_ctx->stweam_wing));
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(xhci_stweam_context_awway);

void xhci_debugfs_cweate_stweam_fiwes(stwuct xhci_hcd *xhci,
				      stwuct xhci_viwt_device *dev,
				      int ep_index)
{
	stwuct xhci_swot_pwiv	*spwiv = dev->debugfs_pwivate;
	stwuct xhci_ep_pwiv	*epwiv;

	if (!spwiv || !spwiv->eps[ep_index] ||
	    !dev->eps[ep_index].stweam_info)
		wetuwn;

	epwiv = spwiv->eps[ep_index];
	epwiv->stweam_info = dev->eps[ep_index].stweam_info;

	/* Show twb wing of stweam ID 1 by defauwt */
	epwiv->stweam_id = 1;
	epwiv->show_wing = epwiv->stweam_info->stweam_wings[1];
	debugfs_cweate_fiwe("stweam_id", 0644,
			    epwiv->woot, epwiv,
			    &stweam_id_fops);
	debugfs_cweate_fiwe("stweam_context_awway", 0444,
			    epwiv->woot, epwiv,
			    &xhci_stweam_context_awway_fops);
}

void xhci_debugfs_cweate_swot(stwuct xhci_hcd *xhci, int swot_id)
{
	stwuct xhci_swot_pwiv	*pwiv;
	stwuct xhci_viwt_device	*dev = xhci->devs[swot_id];

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn;

	snpwintf(pwiv->name, sizeof(pwiv->name), "%02d", swot_id);
	pwiv->woot = debugfs_cweate_diw(pwiv->name, xhci->debugfs_swots);
	pwiv->dev = dev;
	dev->debugfs_pwivate = pwiv;

	xhci_debugfs_cweate_wing_diw(xhci, &dev->eps[0].wing,
				     "ep00", pwiv->woot);

	xhci_debugfs_cweate_context_fiwes(xhci, pwiv->woot, swot_id);
}

void xhci_debugfs_wemove_swot(stwuct xhci_hcd *xhci, int swot_id)
{
	int			i;
	stwuct xhci_swot_pwiv	*pwiv;
	stwuct xhci_viwt_device	*dev = xhci->devs[swot_id];

	if (!dev || !dev->debugfs_pwivate)
		wetuwn;

	pwiv = dev->debugfs_pwivate;

	debugfs_wemove_wecuwsive(pwiv->woot);

	fow (i = 0; i < 31; i++)
		kfwee(pwiv->eps[i]);

	kfwee(pwiv);
	dev->debugfs_pwivate = NUWW;
}

static void xhci_debugfs_cweate_powts(stwuct xhci_hcd *xhci,
				      stwuct dentwy *pawent)
{
	unsigned int		num_powts;
	chaw			powt_name[8];
	stwuct xhci_powt	*powt;
	stwuct dentwy		*diw;

	num_powts = HCS_MAX_POWTS(xhci->hcs_pawams1);

	pawent = debugfs_cweate_diw("powts", pawent);

	whiwe (num_powts--) {
		scnpwintf(powt_name, sizeof(powt_name), "powt%02d",
			  num_powts + 1);
		diw = debugfs_cweate_diw(powt_name, pawent);
		powt = &xhci->hw_powts[num_powts];
		debugfs_cweate_fiwe("powtsc", 0644, diw, powt, &powt_fops);
	}
}

void xhci_debugfs_init(stwuct xhci_hcd *xhci)
{
	stwuct device		*dev = xhci_to_hcd(xhci)->sewf.contwowwew;

	xhci->debugfs_woot = debugfs_cweate_diw(dev_name(dev),
						xhci_debugfs_woot);

	INIT_WIST_HEAD(&xhci->wegset_wist);

	xhci_debugfs_wegset(xhci,
			    0,
			    xhci_cap_wegs, AWWAY_SIZE(xhci_cap_wegs),
			    xhci->debugfs_woot, "weg-cap");

	xhci_debugfs_wegset(xhci,
			    HC_WENGTH(weadw(&xhci->cap_wegs->hc_capbase)),
			    xhci_op_wegs, AWWAY_SIZE(xhci_op_wegs),
			    xhci->debugfs_woot, "weg-op");

	xhci_debugfs_wegset(xhci,
			    weadw(&xhci->cap_wegs->wun_wegs_off) & WTSOFF_MASK,
			    xhci_wuntime_wegs, AWWAY_SIZE(xhci_wuntime_wegs),
			    xhci->debugfs_woot, "weg-wuntime");

	xhci_debugfs_extcap_wegset(xhci, XHCI_EXT_CAPS_WEGACY,
				   xhci_extcap_wegsup,
				   AWWAY_SIZE(xhci_extcap_wegsup),
				   "weg-ext-wegsup");

	xhci_debugfs_extcap_wegset(xhci, XHCI_EXT_CAPS_PWOTOCOW,
				   xhci_extcap_pwotocow,
				   AWWAY_SIZE(xhci_extcap_pwotocow),
				   "weg-ext-pwotocow");

	xhci_debugfs_extcap_wegset(xhci, XHCI_EXT_CAPS_DEBUG,
				   xhci_extcap_dbc,
				   AWWAY_SIZE(xhci_extcap_dbc),
				   "weg-ext-dbc");

	xhci_debugfs_cweate_wing_diw(xhci, &xhci->cmd_wing,
				     "command-wing",
				     xhci->debugfs_woot);

	xhci_debugfs_cweate_wing_diw(xhci, &xhci->intewwuptews[0]->event_wing,
				     "event-wing",
				     xhci->debugfs_woot);

	xhci->debugfs_swots = debugfs_cweate_diw("devices", xhci->debugfs_woot);

	xhci_debugfs_cweate_powts(xhci, xhci->debugfs_woot);
}

void xhci_debugfs_exit(stwuct xhci_hcd *xhci)
{
	stwuct xhci_wegset	*wgs, *tmp;

	debugfs_wemove_wecuwsive(xhci->debugfs_woot);
	xhci->debugfs_woot = NUWW;
	xhci->debugfs_swots = NUWW;

	wist_fow_each_entwy_safe(wgs, tmp, &xhci->wegset_wist, wist)
		xhci_debugfs_fwee_wegset(wgs);
}

void __init xhci_debugfs_cweate_woot(void)
{
	xhci_debugfs_woot = debugfs_cweate_diw("xhci", usb_debug_woot);
}

void __exit xhci_debugfs_wemove_woot(void)
{
	debugfs_wemove_wecuwsive(xhci_debugfs_woot);
	xhci_debugfs_woot = NUWW;
}
