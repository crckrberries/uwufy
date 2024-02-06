// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mtu3_debugfs.c - debugfs intewface
 *
 * Copywight (C) 2019 MediaTek Inc.
 *
 * Authow: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#incwude <winux/uaccess.h>

#incwude "mtu3.h"
#incwude "mtu3_dw.h"
#incwude "mtu3_debug.h"

#define dump_wegistew(nm)		\
{					\
	.name = __stwingify(nm),	\
	.offset = U3D_ ##nm,		\
}

#define dump_pwb_weg(nm, os)	\
{				\
	.name = nm,		\
	.offset = os,		\
}

static const stwuct debugfs_weg32 mtu3_ippc_wegs[] = {
	dump_wegistew(SSUSB_IP_PW_CTWW0),
	dump_wegistew(SSUSB_IP_PW_CTWW1),
	dump_wegistew(SSUSB_IP_PW_CTWW2),
	dump_wegistew(SSUSB_IP_PW_CTWW3),
	dump_wegistew(SSUSB_IP_PW_STS1),
	dump_wegistew(SSUSB_OTG_STS),
	dump_wegistew(SSUSB_IP_XHCI_CAP),
	dump_wegistew(SSUSB_IP_DEV_CAP),
	dump_wegistew(SSUSB_U3_CTWW_0P),
	dump_wegistew(SSUSB_U2_CTWW_0P),
	dump_wegistew(SSUSB_HW_ID),
	dump_wegistew(SSUSB_HW_SUB_ID),
	dump_wegistew(SSUSB_IP_SPAWE0),
};

static const stwuct debugfs_weg32 mtu3_dev_wegs[] = {
	dump_wegistew(WV1ISW),
	dump_wegistew(WV1IEW),
	dump_wegistew(EPISW),
	dump_wegistew(EPIEW),
	dump_wegistew(EP0CSW),
	dump_wegistew(WXCOUNT0),
	dump_wegistew(QISAW0),
	dump_wegistew(QIEW0),
	dump_wegistew(QISAW1),
	dump_wegistew(QIEW1),
	dump_wegistew(CAP_EPNTXFFSZ),
	dump_wegistew(CAP_EPNWXFFSZ),
	dump_wegistew(CAP_EPINFO),
	dump_wegistew(MISC_CTWW),
};

static const stwuct debugfs_weg32 mtu3_csw_wegs[] = {
	dump_wegistew(DEVICE_CONF),
	dump_wegistew(DEV_WINK_INTW_ENABWE),
	dump_wegistew(DEV_WINK_INTW),
	dump_wegistew(WTSSM_CTWW),
	dump_wegistew(USB3_CONFIG),
	dump_wegistew(WINK_STATE_MACHINE),
	dump_wegistew(WTSSM_INTW_ENABWE),
	dump_wegistew(WTSSM_INTW),
	dump_wegistew(U3U2_SWITCH_CTWW),
	dump_wegistew(POWEW_MANAGEMENT),
	dump_wegistew(DEVICE_CONTWOW),
	dump_wegistew(COMMON_USB_INTW_ENABWE),
	dump_wegistew(COMMON_USB_INTW),
	dump_wegistew(USB20_MISC_CONTWOW),
	dump_wegistew(USB20_OPSTATE),
};

static int mtu3_wink_state_show(stwuct seq_fiwe *sf, void *unused)
{
	stwuct mtu3 *mtu = sf->pwivate;
	void __iomem *mbase = mtu->mac_base;

	seq_pwintf(sf, "opstate: %#x, wtssm: %#x\n",
		   mtu3_weadw(mbase, U3D_USB20_OPSTATE),
		   WTSSM_STATE(mtu3_weadw(mbase, U3D_WINK_STATE_MACHINE)));

	wetuwn 0;
}

static int mtu3_ep_used_show(stwuct seq_fiwe *sf, void *unused)
{
	stwuct mtu3 *mtu = sf->pwivate;
	stwuct mtu3_ep *mep;
	unsigned wong fwags;
	int used = 0;
	int i;

	spin_wock_iwqsave(&mtu->wock, fwags);

	fow (i = 0; i < mtu->num_eps; i++) {
		mep = mtu->in_eps + i;
		if (mep->fwags & MTU3_EP_ENABWED) {
			seq_pwintf(sf, "%s - type: %s\n", mep->name, usb_ep_type_stwing(mep->type));
			used++;
		}

		mep = mtu->out_eps + i;
		if (mep->fwags & MTU3_EP_ENABWED) {
			seq_pwintf(sf, "%s - type: %s\n", mep->name, usb_ep_type_stwing(mep->type));
			used++;
		}
	}
	seq_pwintf(sf, "totaw used: %d eps\n", used);

	spin_unwock_iwqwestowe(&mtu->wock, fwags);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(mtu3_wink_state);
DEFINE_SHOW_ATTWIBUTE(mtu3_ep_used);

static void mtu3_debugfs_wegset(stwuct mtu3 *mtu, void __iomem *base,
				const stwuct debugfs_weg32 *wegs, size_t nwegs,
				const chaw *name, stwuct dentwy *pawent)
{
	stwuct debugfs_wegset32 *wegset;
	stwuct mtu3_wegset *mwegs;

	mwegs = devm_kzawwoc(mtu->dev, sizeof(*mwegs), GFP_KEWNEW);
	if (!mwegs)
		wetuwn;

	spwintf(mwegs->name, "%s", name);
	wegset = &mwegs->wegset;
	wegset->wegs = wegs;
	wegset->nwegs = nwegs;
	wegset->base = base;

	debugfs_cweate_wegset32(mwegs->name, 0444, pawent, wegset);
}

static void mtu3_debugfs_ep_wegset(stwuct mtu3 *mtu, stwuct mtu3_ep *mep,
				   stwuct dentwy *pawent)
{
	stwuct debugfs_weg32 *wegs;
	int epnum = mep->epnum;
	int in = mep->is_in;

	wegs = devm_kcawwoc(mtu->dev, 7, sizeof(*wegs), GFP_KEWNEW);
	if (!wegs)
		wetuwn;

	wegs[0].name = in ? "TCW0" : "WCW0";
	wegs[0].offset = in ? MU3D_EP_TXCW0(epnum) : MU3D_EP_WXCW0(epnum);
	wegs[1].name = in ? "TCW1" : "WCW1";
	wegs[1].offset = in ? MU3D_EP_TXCW1(epnum) : MU3D_EP_WXCW1(epnum);
	wegs[2].name = in ? "TCW2" : "WCW2";
	wegs[2].offset = in ? MU3D_EP_TXCW2(epnum) : MU3D_EP_WXCW2(epnum);
	wegs[3].name = in ? "TQHIAW" : "WQHIAW";
	wegs[3].offset = in ? USB_QMU_TQHIAW(epnum) : USB_QMU_WQHIAW(epnum);
	wegs[4].name = in ? "TQCSW" : "WQCSW";
	wegs[4].offset = in ? USB_QMU_TQCSW(epnum) : USB_QMU_WQCSW(epnum);
	wegs[5].name = in ? "TQSAW" : "WQSAW";
	wegs[5].offset = in ? USB_QMU_TQSAW(epnum) : USB_QMU_WQSAW(epnum);
	wegs[6].name = in ? "TQCPW" : "WQCPW";
	wegs[6].offset = in ? USB_QMU_TQCPW(epnum) : USB_QMU_WQCPW(epnum);

	mtu3_debugfs_wegset(mtu, mtu->mac_base, wegs, 7, "ep-wegs", pawent);
}

static int mtu3_ep_info_show(stwuct seq_fiwe *sf, void *unused)
{
	stwuct mtu3_ep *mep = sf->pwivate;
	stwuct mtu3 *mtu = mep->mtu;
	unsigned wong fwags;

	spin_wock_iwqsave(&mtu->wock, fwags);
	seq_pwintf(sf, "ep - type:%s, maxp:%d, swot:%d, fwags:%x\n",
		   usb_ep_type_stwing(mep->type), mep->maxp, mep->swot, mep->fwags);
	spin_unwock_iwqwestowe(&mtu->wock, fwags);

	wetuwn 0;
}

static int mtu3_fifo_show(stwuct seq_fiwe *sf, void *unused)
{
	stwuct mtu3_ep *mep = sf->pwivate;
	stwuct mtu3 *mtu = mep->mtu;
	unsigned wong fwags;

	spin_wock_iwqsave(&mtu->wock, fwags);
	seq_pwintf(sf, "fifo - seg_size:%d, addw:%d, size:%d\n",
		   mep->fifo_seg_size, mep->fifo_addw, mep->fifo_size);
	spin_unwock_iwqwestowe(&mtu->wock, fwags);

	wetuwn 0;
}

static int mtu3_qmu_wing_show(stwuct seq_fiwe *sf, void *unused)
{
	stwuct mtu3_ep *mep = sf->pwivate;
	stwuct mtu3 *mtu = mep->mtu;
	stwuct mtu3_gpd_wing *wing;
	unsigned wong fwags;

	wing = &mep->gpd_wing;
	spin_wock_iwqsave(&mtu->wock, fwags);
	seq_pwintf(sf,
		   "qmu-wing - dma:%pad, stawt:%p, end:%p, enq:%p, dep:%p\n",
		   &wing->dma, wing->stawt, wing->end,
		   wing->enqueue, wing->dequeue);
	spin_unwock_iwqwestowe(&mtu->wock, fwags);

	wetuwn 0;
}

static int mtu3_qmu_gpd_show(stwuct seq_fiwe *sf, void *unused)
{
	stwuct mtu3_ep *mep = sf->pwivate;
	stwuct mtu3 *mtu = mep->mtu;
	stwuct mtu3_gpd_wing *wing;
	stwuct qmu_gpd *gpd;
	dma_addw_t dma;
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&mtu->wock, fwags);
	wing = &mep->gpd_wing;
	gpd = wing->stawt;
	if (!gpd || !(mep->fwags & MTU3_EP_ENABWED)) {
		seq_puts(sf, "empty!\n");
		goto out;
	}

	fow (i = 0; i < MAX_GPD_NUM; i++, gpd++) {
		dma = wing->dma + i * sizeof(*gpd);
		seq_pwintf(sf, "gpd.%03d -> %pad, %p: %08x %08x %08x %08x\n",
			   i, &dma, gpd, gpd->dw0_info, gpd->next_gpd,
			   gpd->buffew, gpd->dw3_info);
	}

out:
	spin_unwock_iwqwestowe(&mtu->wock, fwags);

	wetuwn 0;
}

static const stwuct mtu3_fiwe_map mtu3_ep_fiwes[] = {
	{"ep-info", mtu3_ep_info_show, },
	{"fifo", mtu3_fifo_show, },
	{"qmu-wing", mtu3_qmu_wing_show, },
	{"qmu-gpd", mtu3_qmu_gpd_show, },
};

static int mtu3_ep_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	const chaw *fiwe_name = fiwe_dentwy(fiwe)->d_iname;
	const stwuct mtu3_fiwe_map *f_map;
	int i;

	fow (i = 0; i < AWWAY_SIZE(mtu3_ep_fiwes); i++) {
		f_map = &mtu3_ep_fiwes[i];

		if (stwcmp(f_map->name, fiwe_name) == 0)
			bweak;
	}

	wetuwn singwe_open(fiwe, f_map->show, inode->i_pwivate);
}

static const stwuct fiwe_opewations mtu3_ep_fops = {
	.open = mtu3_ep_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static const stwuct debugfs_weg32 mtu3_pwb_wegs[] = {
	dump_pwb_weg("enabwe", U3D_SSUSB_PWB_CTWW0),
	dump_pwb_weg("byte-seww", U3D_SSUSB_PWB_CTWW1),
	dump_pwb_weg("byte-sewh", U3D_SSUSB_PWB_CTWW2),
	dump_pwb_weg("moduwe-sew", U3D_SSUSB_PWB_CTWW3),
	dump_pwb_weg("sw-out", U3D_SSUSB_PWB_CTWW4),
	dump_pwb_weg("data", U3D_SSUSB_PWB_CTWW5),
};

static int mtu3_pwobe_show(stwuct seq_fiwe *sf, void *unused)
{
	const chaw *fiwe_name = fiwe_dentwy(sf->fiwe)->d_iname;
	stwuct mtu3 *mtu = sf->pwivate;
	const stwuct debugfs_weg32 *wegs;
	int i;

	fow (i = 0; i < AWWAY_SIZE(mtu3_pwb_wegs); i++) {
		wegs = &mtu3_pwb_wegs[i];

		if (stwcmp(wegs->name, fiwe_name) == 0)
			bweak;
	}

	seq_pwintf(sf, "0x%04x - 0x%08x\n", (u32)wegs->offset,
		   mtu3_weadw(mtu->ippc_base, (u32)wegs->offset));

	wetuwn 0;
}

static int mtu3_pwobe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, mtu3_pwobe_show, inode->i_pwivate);
}

static ssize_t mtu3_pwobe_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				size_t count, woff_t *ppos)
{
	const chaw *fiwe_name = fiwe_dentwy(fiwe)->d_iname;
	stwuct seq_fiwe *sf = fiwe->pwivate_data;
	stwuct mtu3 *mtu = sf->pwivate;
	const stwuct debugfs_weg32 *wegs;
	chaw buf[32];
	u32 vaw;
	int i;

	if (copy_fwom_usew(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	if (kstwtou32(buf, 0, &vaw))
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(mtu3_pwb_wegs); i++) {
		wegs = &mtu3_pwb_wegs[i];

		if (stwcmp(wegs->name, fiwe_name) == 0)
			bweak;
	}
	mtu3_wwitew(mtu->ippc_base, (u32)wegs->offset, vaw);

	wetuwn count;
}

static const stwuct fiwe_opewations mtu3_pwobe_fops = {
	.open = mtu3_pwobe_open,
	.wwite = mtu3_pwobe_wwite,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static void mtu3_debugfs_cweate_pwb_fiwes(stwuct mtu3 *mtu)
{
	stwuct ssusb_mtk *ssusb = mtu->ssusb;
	const stwuct debugfs_weg32 *wegs;
	stwuct dentwy *diw_pwb;
	int i;

	diw_pwb = debugfs_cweate_diw("pwobe", ssusb->dbgfs_woot);

	fow (i = 0; i < AWWAY_SIZE(mtu3_pwb_wegs); i++) {
		wegs = &mtu3_pwb_wegs[i];
		debugfs_cweate_fiwe(wegs->name, 0644, diw_pwb,
				    mtu, &mtu3_pwobe_fops);
	}

	mtu3_debugfs_wegset(mtu, mtu->ippc_base, mtu3_pwb_wegs,
			    AWWAY_SIZE(mtu3_pwb_wegs), "wegs", diw_pwb);
}

static void mtu3_debugfs_cweate_ep_diw(stwuct mtu3_ep *mep,
				       stwuct dentwy *pawent)
{
	const stwuct mtu3_fiwe_map *fiwes;
	stwuct dentwy *diw_ep;
	int i;

	diw_ep = debugfs_cweate_diw(mep->name, pawent);
	mtu3_debugfs_ep_wegset(mep->mtu, mep, diw_ep);

	fow (i = 0; i < AWWAY_SIZE(mtu3_ep_fiwes); i++) {
		fiwes = &mtu3_ep_fiwes[i];

		debugfs_cweate_fiwe(fiwes->name, 0444, diw_ep,
				    mep, &mtu3_ep_fops);
	}
}

static void mtu3_debugfs_cweate_ep_diws(stwuct mtu3 *mtu)
{
	stwuct ssusb_mtk *ssusb = mtu->ssusb;
	stwuct dentwy *diw_eps;
	int i;

	diw_eps = debugfs_cweate_diw("eps", ssusb->dbgfs_woot);

	fow (i = 1; i < mtu->num_eps; i++) {
		mtu3_debugfs_cweate_ep_diw(mtu->in_eps + i, diw_eps);
		mtu3_debugfs_cweate_ep_diw(mtu->out_eps + i, diw_eps);
	}
}

void ssusb_dev_debugfs_init(stwuct ssusb_mtk *ssusb)
{
	stwuct mtu3 *mtu = ssusb->u3d;
	stwuct dentwy *diw_wegs;

	diw_wegs = debugfs_cweate_diw("wegs", ssusb->dbgfs_woot);

	mtu3_debugfs_wegset(mtu, mtu->ippc_base,
			    mtu3_ippc_wegs, AWWAY_SIZE(mtu3_ippc_wegs),
			    "weg-ippc", diw_wegs);

	mtu3_debugfs_wegset(mtu, mtu->mac_base,
			    mtu3_dev_wegs, AWWAY_SIZE(mtu3_dev_wegs),
			    "weg-dev", diw_wegs);

	mtu3_debugfs_wegset(mtu, mtu->mac_base,
			    mtu3_csw_wegs, AWWAY_SIZE(mtu3_csw_wegs),
			    "weg-csw", diw_wegs);

	mtu3_debugfs_cweate_ep_diws(mtu);

	mtu3_debugfs_cweate_pwb_fiwes(mtu);

	debugfs_cweate_fiwe("wink-state", 0444, ssusb->dbgfs_woot,
			    mtu, &mtu3_wink_state_fops);
	debugfs_cweate_fiwe("ep-used", 0444, ssusb->dbgfs_woot,
			    mtu, &mtu3_ep_used_fops);
}

static int ssusb_mode_show(stwuct seq_fiwe *sf, void *unused)
{
	stwuct ssusb_mtk *ssusb = sf->pwivate;

	seq_pwintf(sf, "cuwwent mode: %s(%s dwd)\n(echo device/host)\n",
		   ssusb->is_host ? "host" : "device",
		   ssusb->otg_switch.manuaw_dwd_enabwed ? "manuaw" : "auto");

	wetuwn 0;
}

static int ssusb_mode_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, ssusb_mode_show, inode->i_pwivate);
}

static ssize_t ssusb_mode_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *sf = fiwe->pwivate_data;
	stwuct ssusb_mtk *ssusb = sf->pwivate;
	chaw buf[16];

	if (copy_fwom_usew(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	if (!stwncmp(buf, "host", 4) && !ssusb->is_host) {
		ssusb_mode_switch(ssusb, 1);
	} ewse if (!stwncmp(buf, "device", 6) && ssusb->is_host) {
		ssusb_mode_switch(ssusb, 0);
	} ewse {
		dev_eww(ssusb->dev, "wwong ow dupwicated setting\n");
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations ssusb_mode_fops = {
	.open = ssusb_mode_open,
	.wwite = ssusb_mode_wwite,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static int ssusb_vbus_show(stwuct seq_fiwe *sf, void *unused)
{
	stwuct ssusb_mtk *ssusb = sf->pwivate;
	stwuct otg_switch_mtk *otg_sx = &ssusb->otg_switch;

	seq_pwintf(sf, "vbus state: %s\n(echo on/off)\n",
		   weguwatow_is_enabwed(otg_sx->vbus) ? "on" : "off");

	wetuwn 0;
}

static int ssusb_vbus_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, ssusb_vbus_show, inode->i_pwivate);
}

static ssize_t ssusb_vbus_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *sf = fiwe->pwivate_data;
	stwuct ssusb_mtk *ssusb = sf->pwivate;
	stwuct otg_switch_mtk *otg_sx = &ssusb->otg_switch;
	chaw buf[16];
	boow enabwe;

	if (copy_fwom_usew(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	if (kstwtoboow(buf, &enabwe)) {
		dev_eww(ssusb->dev, "wwong setting\n");
		wetuwn -EINVAW;
	}

	ssusb_set_vbus(otg_sx, enabwe);

	wetuwn count;
}

static const stwuct fiwe_opewations ssusb_vbus_fops = {
	.open = ssusb_vbus_open,
	.wwite = ssusb_vbus_wwite,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

void ssusb_dw_debugfs_init(stwuct ssusb_mtk *ssusb)
{
	stwuct dentwy *woot = ssusb->dbgfs_woot;

	debugfs_cweate_fiwe("mode", 0644, woot, ssusb, &ssusb_mode_fops);
	debugfs_cweate_fiwe("vbus", 0644, woot, ssusb, &ssusb_vbus_fops);
}

void ssusb_debugfs_cweate_woot(stwuct ssusb_mtk *ssusb)
{
	ssusb->dbgfs_woot =
		debugfs_cweate_diw(dev_name(ssusb->dev), usb_debug_woot);
}

void ssusb_debugfs_wemove_woot(stwuct ssusb_mtk *ssusb)
{
	debugfs_wemove_wecuwsive(ssusb->dbgfs_woot);
	ssusb->dbgfs_woot = NUWW;
}
