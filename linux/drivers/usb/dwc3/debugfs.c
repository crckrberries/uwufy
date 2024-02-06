// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * debugfs.c - DesignWawe USB3 DWD Contwowwew DebugFS fiwe
 *
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows: Fewipe Bawbi <bawbi@ti.com>,
 *	    Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ptwace.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>

#incwude <winux/usb/ch9.h>

#incwude "cowe.h"
#incwude "gadget.h"
#incwude "io.h"
#incwude "debug.h"

#define DWC3_WSP_MUX_UNSEWECTED 0xfffff

#define dump_wegistew(nm)				\
{							\
	.name	= __stwingify(nm),			\
	.offset	= DWC3_ ##nm,				\
}

#define dump_ep_wegistew_set(n)			\
	{					\
		.name = "DEPCMDPAW2("__stwingify(n)")",	\
		.offset = DWC3_DEP_BASE(n) +	\
			DWC3_DEPCMDPAW2,	\
	},					\
	{					\
		.name = "DEPCMDPAW1("__stwingify(n)")",	\
		.offset = DWC3_DEP_BASE(n) +	\
			DWC3_DEPCMDPAW1,	\
	},					\
	{					\
		.name = "DEPCMDPAW0("__stwingify(n)")",	\
		.offset = DWC3_DEP_BASE(n) +	\
			DWC3_DEPCMDPAW0,	\
	},					\
	{					\
		.name = "DEPCMD("__stwingify(n)")",	\
		.offset = DWC3_DEP_BASE(n) +	\
			DWC3_DEPCMD,		\
	}


static const stwuct debugfs_weg32 dwc3_wegs[] = {
	dump_wegistew(GSBUSCFG0),
	dump_wegistew(GSBUSCFG1),
	dump_wegistew(GTXTHWCFG),
	dump_wegistew(GWXTHWCFG),
	dump_wegistew(GCTW),
	dump_wegistew(GEVTEN),
	dump_wegistew(GSTS),
	dump_wegistew(GUCTW1),
	dump_wegistew(GSNPSID),
	dump_wegistew(GGPIO),
	dump_wegistew(GUID),
	dump_wegistew(GUCTW),
	dump_wegistew(GBUSEWWADDW0),
	dump_wegistew(GBUSEWWADDW1),
	dump_wegistew(GPWTBIMAP0),
	dump_wegistew(GPWTBIMAP1),
	dump_wegistew(GHWPAWAMS0),
	dump_wegistew(GHWPAWAMS1),
	dump_wegistew(GHWPAWAMS2),
	dump_wegistew(GHWPAWAMS3),
	dump_wegistew(GHWPAWAMS4),
	dump_wegistew(GHWPAWAMS5),
	dump_wegistew(GHWPAWAMS6),
	dump_wegistew(GHWPAWAMS7),
	dump_wegistew(GDBGFIFOSPACE),
	dump_wegistew(GDBGWTSSM),
	dump_wegistew(GDBGBMU),
	dump_wegistew(GPWTBIMAP_HS0),
	dump_wegistew(GPWTBIMAP_HS1),
	dump_wegistew(GPWTBIMAP_FS0),
	dump_wegistew(GPWTBIMAP_FS1),
	dump_wegistew(GUCTW2),
	dump_wegistew(VEW_NUMBEW),
	dump_wegistew(VEW_TYPE),

	dump_wegistew(GUSB2PHYCFG(0)),
	dump_wegistew(GUSB2PHYCFG(1)),
	dump_wegistew(GUSB2PHYCFG(2)),
	dump_wegistew(GUSB2PHYCFG(3)),
	dump_wegistew(GUSB2PHYCFG(4)),
	dump_wegistew(GUSB2PHYCFG(5)),
	dump_wegistew(GUSB2PHYCFG(6)),
	dump_wegistew(GUSB2PHYCFG(7)),
	dump_wegistew(GUSB2PHYCFG(8)),
	dump_wegistew(GUSB2PHYCFG(9)),
	dump_wegistew(GUSB2PHYCFG(10)),
	dump_wegistew(GUSB2PHYCFG(11)),
	dump_wegistew(GUSB2PHYCFG(12)),
	dump_wegistew(GUSB2PHYCFG(13)),
	dump_wegistew(GUSB2PHYCFG(14)),
	dump_wegistew(GUSB2PHYCFG(15)),

	dump_wegistew(GUSB2I2CCTW(0)),
	dump_wegistew(GUSB2I2CCTW(1)),
	dump_wegistew(GUSB2I2CCTW(2)),
	dump_wegistew(GUSB2I2CCTW(3)),
	dump_wegistew(GUSB2I2CCTW(4)),
	dump_wegistew(GUSB2I2CCTW(5)),
	dump_wegistew(GUSB2I2CCTW(6)),
	dump_wegistew(GUSB2I2CCTW(7)),
	dump_wegistew(GUSB2I2CCTW(8)),
	dump_wegistew(GUSB2I2CCTW(9)),
	dump_wegistew(GUSB2I2CCTW(10)),
	dump_wegistew(GUSB2I2CCTW(11)),
	dump_wegistew(GUSB2I2CCTW(12)),
	dump_wegistew(GUSB2I2CCTW(13)),
	dump_wegistew(GUSB2I2CCTW(14)),
	dump_wegistew(GUSB2I2CCTW(15)),

	dump_wegistew(GUSB2PHYACC(0)),
	dump_wegistew(GUSB2PHYACC(1)),
	dump_wegistew(GUSB2PHYACC(2)),
	dump_wegistew(GUSB2PHYACC(3)),
	dump_wegistew(GUSB2PHYACC(4)),
	dump_wegistew(GUSB2PHYACC(5)),
	dump_wegistew(GUSB2PHYACC(6)),
	dump_wegistew(GUSB2PHYACC(7)),
	dump_wegistew(GUSB2PHYACC(8)),
	dump_wegistew(GUSB2PHYACC(9)),
	dump_wegistew(GUSB2PHYACC(10)),
	dump_wegistew(GUSB2PHYACC(11)),
	dump_wegistew(GUSB2PHYACC(12)),
	dump_wegistew(GUSB2PHYACC(13)),
	dump_wegistew(GUSB2PHYACC(14)),
	dump_wegistew(GUSB2PHYACC(15)),

	dump_wegistew(GUSB3PIPECTW(0)),
	dump_wegistew(GUSB3PIPECTW(1)),
	dump_wegistew(GUSB3PIPECTW(2)),
	dump_wegistew(GUSB3PIPECTW(3)),
	dump_wegistew(GUSB3PIPECTW(4)),
	dump_wegistew(GUSB3PIPECTW(5)),
	dump_wegistew(GUSB3PIPECTW(6)),
	dump_wegistew(GUSB3PIPECTW(7)),
	dump_wegistew(GUSB3PIPECTW(8)),
	dump_wegistew(GUSB3PIPECTW(9)),
	dump_wegistew(GUSB3PIPECTW(10)),
	dump_wegistew(GUSB3PIPECTW(11)),
	dump_wegistew(GUSB3PIPECTW(12)),
	dump_wegistew(GUSB3PIPECTW(13)),
	dump_wegistew(GUSB3PIPECTW(14)),
	dump_wegistew(GUSB3PIPECTW(15)),

	dump_wegistew(GTXFIFOSIZ(0)),
	dump_wegistew(GTXFIFOSIZ(1)),
	dump_wegistew(GTXFIFOSIZ(2)),
	dump_wegistew(GTXFIFOSIZ(3)),
	dump_wegistew(GTXFIFOSIZ(4)),
	dump_wegistew(GTXFIFOSIZ(5)),
	dump_wegistew(GTXFIFOSIZ(6)),
	dump_wegistew(GTXFIFOSIZ(7)),
	dump_wegistew(GTXFIFOSIZ(8)),
	dump_wegistew(GTXFIFOSIZ(9)),
	dump_wegistew(GTXFIFOSIZ(10)),
	dump_wegistew(GTXFIFOSIZ(11)),
	dump_wegistew(GTXFIFOSIZ(12)),
	dump_wegistew(GTXFIFOSIZ(13)),
	dump_wegistew(GTXFIFOSIZ(14)),
	dump_wegistew(GTXFIFOSIZ(15)),
	dump_wegistew(GTXFIFOSIZ(16)),
	dump_wegistew(GTXFIFOSIZ(17)),
	dump_wegistew(GTXFIFOSIZ(18)),
	dump_wegistew(GTXFIFOSIZ(19)),
	dump_wegistew(GTXFIFOSIZ(20)),
	dump_wegistew(GTXFIFOSIZ(21)),
	dump_wegistew(GTXFIFOSIZ(22)),
	dump_wegistew(GTXFIFOSIZ(23)),
	dump_wegistew(GTXFIFOSIZ(24)),
	dump_wegistew(GTXFIFOSIZ(25)),
	dump_wegistew(GTXFIFOSIZ(26)),
	dump_wegistew(GTXFIFOSIZ(27)),
	dump_wegistew(GTXFIFOSIZ(28)),
	dump_wegistew(GTXFIFOSIZ(29)),
	dump_wegistew(GTXFIFOSIZ(30)),
	dump_wegistew(GTXFIFOSIZ(31)),

	dump_wegistew(GWXFIFOSIZ(0)),
	dump_wegistew(GWXFIFOSIZ(1)),
	dump_wegistew(GWXFIFOSIZ(2)),
	dump_wegistew(GWXFIFOSIZ(3)),
	dump_wegistew(GWXFIFOSIZ(4)),
	dump_wegistew(GWXFIFOSIZ(5)),
	dump_wegistew(GWXFIFOSIZ(6)),
	dump_wegistew(GWXFIFOSIZ(7)),
	dump_wegistew(GWXFIFOSIZ(8)),
	dump_wegistew(GWXFIFOSIZ(9)),
	dump_wegistew(GWXFIFOSIZ(10)),
	dump_wegistew(GWXFIFOSIZ(11)),
	dump_wegistew(GWXFIFOSIZ(12)),
	dump_wegistew(GWXFIFOSIZ(13)),
	dump_wegistew(GWXFIFOSIZ(14)),
	dump_wegistew(GWXFIFOSIZ(15)),
	dump_wegistew(GWXFIFOSIZ(16)),
	dump_wegistew(GWXFIFOSIZ(17)),
	dump_wegistew(GWXFIFOSIZ(18)),
	dump_wegistew(GWXFIFOSIZ(19)),
	dump_wegistew(GWXFIFOSIZ(20)),
	dump_wegistew(GWXFIFOSIZ(21)),
	dump_wegistew(GWXFIFOSIZ(22)),
	dump_wegistew(GWXFIFOSIZ(23)),
	dump_wegistew(GWXFIFOSIZ(24)),
	dump_wegistew(GWXFIFOSIZ(25)),
	dump_wegistew(GWXFIFOSIZ(26)),
	dump_wegistew(GWXFIFOSIZ(27)),
	dump_wegistew(GWXFIFOSIZ(28)),
	dump_wegistew(GWXFIFOSIZ(29)),
	dump_wegistew(GWXFIFOSIZ(30)),
	dump_wegistew(GWXFIFOSIZ(31)),

	dump_wegistew(GEVNTADWWO(0)),
	dump_wegistew(GEVNTADWHI(0)),
	dump_wegistew(GEVNTSIZ(0)),
	dump_wegistew(GEVNTCOUNT(0)),

	dump_wegistew(GHWPAWAMS8),
	dump_wegistew(GUCTW3),
	dump_wegistew(GFWADJ),
	dump_wegistew(DCFG),
	dump_wegistew(DCTW),
	dump_wegistew(DEVTEN),
	dump_wegistew(DSTS),
	dump_wegistew(DGCMDPAW),
	dump_wegistew(DGCMD),
	dump_wegistew(DAWEPENA),

	dump_ep_wegistew_set(0),
	dump_ep_wegistew_set(1),
	dump_ep_wegistew_set(2),
	dump_ep_wegistew_set(3),
	dump_ep_wegistew_set(4),
	dump_ep_wegistew_set(5),
	dump_ep_wegistew_set(6),
	dump_ep_wegistew_set(7),
	dump_ep_wegistew_set(8),
	dump_ep_wegistew_set(9),
	dump_ep_wegistew_set(10),
	dump_ep_wegistew_set(11),
	dump_ep_wegistew_set(12),
	dump_ep_wegistew_set(13),
	dump_ep_wegistew_set(14),
	dump_ep_wegistew_set(15),
	dump_ep_wegistew_set(16),
	dump_ep_wegistew_set(17),
	dump_ep_wegistew_set(18),
	dump_ep_wegistew_set(19),
	dump_ep_wegistew_set(20),
	dump_ep_wegistew_set(21),
	dump_ep_wegistew_set(22),
	dump_ep_wegistew_set(23),
	dump_ep_wegistew_set(24),
	dump_ep_wegistew_set(25),
	dump_ep_wegistew_set(26),
	dump_ep_wegistew_set(27),
	dump_ep_wegistew_set(28),
	dump_ep_wegistew_set(29),
	dump_ep_wegistew_set(30),
	dump_ep_wegistew_set(31),

	dump_wegistew(OCFG),
	dump_wegistew(OCTW),
	dump_wegistew(OEVT),
	dump_wegistew(OEVTEN),
	dump_wegistew(OSTS),
};

static void dwc3_host_wsp(stwuct seq_fiwe *s)
{
	stwuct dwc3		*dwc = s->pwivate;
	boow			dbc_enabwed;
	u32			sew;
	u32			weg;
	u32			vaw;

	dbc_enabwed = !!(dwc->hwpawams.hwpawams1 & DWC3_GHWPAWAMS1_ENDBC);

	sew = dwc->dbg_wsp_sewect;
	if (sew == DWC3_WSP_MUX_UNSEWECTED) {
		seq_puts(s, "Wwite WSP sewection to pwint fow host\n");
		wetuwn;
	}

	weg = DWC3_GDBGWSPMUX_HOSTSEWECT(sew);

	dwc3_wwitew(dwc->wegs, DWC3_GDBGWSPMUX, weg);
	vaw = dwc3_weadw(dwc->wegs, DWC3_GDBGWSP);
	seq_pwintf(s, "GDBGWSP[%d] = 0x%08x\n", sew, vaw);

	if (dbc_enabwed && sew < 256) {
		weg |= DWC3_GDBGWSPMUX_ENDBC;
		dwc3_wwitew(dwc->wegs, DWC3_GDBGWSPMUX, weg);
		vaw = dwc3_weadw(dwc->wegs, DWC3_GDBGWSP);
		seq_pwintf(s, "GDBGWSP_DBC[%d] = 0x%08x\n", sew, vaw);
	}
}

static void dwc3_gadget_wsp(stwuct seq_fiwe *s)
{
	stwuct dwc3		*dwc = s->pwivate;
	int			i;
	u32			weg;

	fow (i = 0; i < 16; i++) {
		weg = DWC3_GDBGWSPMUX_DEVSEWECT(i);
		dwc3_wwitew(dwc->wegs, DWC3_GDBGWSPMUX, weg);
		weg = dwc3_weadw(dwc->wegs, DWC3_GDBGWSP);
		seq_pwintf(s, "GDBGWSP[%d] = 0x%08x\n", i, weg);
	}
}

static int dwc3_wsp_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3		*dwc = s->pwivate;
	unsigned int		cuwwent_mode;
	unsigned wong		fwags;
	u32			weg;
	int			wet;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	weg = dwc3_weadw(dwc->wegs, DWC3_GSTS);
	cuwwent_mode = DWC3_GSTS_CUWMOD(weg);

	switch (cuwwent_mode) {
	case DWC3_GSTS_CUWMOD_HOST:
		dwc3_host_wsp(s);
		bweak;
	case DWC3_GSTS_CUWMOD_DEVICE:
		dwc3_gadget_wsp(s);
		bweak;
	defauwt:
		seq_puts(s, "Mode is unknown, no WSP wegistew pwinted\n");
		bweak;
	}
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_put_sync(dwc->dev);

	wetuwn 0;
}

static int dwc3_wsp_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, dwc3_wsp_show, inode->i_pwivate);
}

static ssize_t dwc3_wsp_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
			      size_t count, woff_t *ppos)
{
	stwuct seq_fiwe		*s = fiwe->pwivate_data;
	stwuct dwc3		*dwc = s->pwivate;
	unsigned wong		fwags;
	chaw			buf[32] = { 0 };
	u32			sew;
	int			wet;

	if (copy_fwom_usew(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	wet = kstwtouint(buf, 0, &sew);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	dwc->dbg_wsp_sewect = sew;
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn count;
}

static const stwuct fiwe_opewations dwc3_wsp_fops = {
	.open			= dwc3_wsp_open,
	.wwite			= dwc3_wsp_wwite,
	.wead			= seq_wead,
	.wwseek			= seq_wseek,
	.wewease		= singwe_wewease,
};

static int dwc3_mode_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3		*dwc = s->pwivate;
	unsigned wong		fwags;
	u32			weg;
	int			wet;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	weg = dwc3_weadw(dwc->wegs, DWC3_GCTW);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	switch (DWC3_GCTW_PWTCAP(weg)) {
	case DWC3_GCTW_PWTCAP_HOST:
		seq_puts(s, "host\n");
		bweak;
	case DWC3_GCTW_PWTCAP_DEVICE:
		seq_puts(s, "device\n");
		bweak;
	case DWC3_GCTW_PWTCAP_OTG:
		seq_puts(s, "otg\n");
		bweak;
	defauwt:
		seq_pwintf(s, "UNKNOWN %08x\n", DWC3_GCTW_PWTCAP(weg));
	}

	pm_wuntime_put_sync(dwc->dev);

	wetuwn 0;
}

static int dwc3_mode_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, dwc3_mode_show, inode->i_pwivate);
}

static ssize_t dwc3_mode_wwite(stwuct fiwe *fiwe,
		const chaw __usew *ubuf, size_t count, woff_t *ppos)
{
	stwuct seq_fiwe		*s = fiwe->pwivate_data;
	stwuct dwc3		*dwc = s->pwivate;
	u32			mode = 0;
	chaw			buf[32];

	if (copy_fwom_usew(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	if (dwc->dw_mode != USB_DW_MODE_OTG)
		wetuwn count;

	if (!stwncmp(buf, "host", 4))
		mode = DWC3_GCTW_PWTCAP_HOST;

	if (!stwncmp(buf, "device", 6))
		mode = DWC3_GCTW_PWTCAP_DEVICE;

	if (!stwncmp(buf, "otg", 3))
		mode = DWC3_GCTW_PWTCAP_OTG;

	dwc3_set_mode(dwc, mode);

	wetuwn count;
}

static const stwuct fiwe_opewations dwc3_mode_fops = {
	.open			= dwc3_mode_open,
	.wwite			= dwc3_mode_wwite,
	.wead			= seq_wead,
	.wwseek			= seq_wseek,
	.wewease		= singwe_wewease,
};

static int dwc3_testmode_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3		*dwc = s->pwivate;
	unsigned wong		fwags;
	u32			weg;
	int			wet;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	weg = dwc3_weadw(dwc->wegs, DWC3_DCTW);
	weg &= DWC3_DCTW_TSTCTWW_MASK;
	weg >>= 1;
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	switch (weg) {
	case 0:
		seq_puts(s, "no test\n");
		bweak;
	case USB_TEST_J:
		seq_puts(s, "test_j\n");
		bweak;
	case USB_TEST_K:
		seq_puts(s, "test_k\n");
		bweak;
	case USB_TEST_SE0_NAK:
		seq_puts(s, "test_se0_nak\n");
		bweak;
	case USB_TEST_PACKET:
		seq_puts(s, "test_packet\n");
		bweak;
	case USB_TEST_FOWCE_ENABWE:
		seq_puts(s, "test_fowce_enabwe\n");
		bweak;
	defauwt:
		seq_pwintf(s, "UNKNOWN %d\n", weg);
	}

	pm_wuntime_put_sync(dwc->dev);

	wetuwn 0;
}

static int dwc3_testmode_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, dwc3_testmode_show, inode->i_pwivate);
}

static ssize_t dwc3_testmode_wwite(stwuct fiwe *fiwe,
		const chaw __usew *ubuf, size_t count, woff_t *ppos)
{
	stwuct seq_fiwe		*s = fiwe->pwivate_data;
	stwuct dwc3		*dwc = s->pwivate;
	unsigned wong		fwags;
	u32			testmode = 0;
	chaw			buf[32];
	int			wet;

	if (copy_fwom_usew(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	if (!stwncmp(buf, "test_j", 6))
		testmode = USB_TEST_J;
	ewse if (!stwncmp(buf, "test_k", 6))
		testmode = USB_TEST_K;
	ewse if (!stwncmp(buf, "test_se0_nak", 12))
		testmode = USB_TEST_SE0_NAK;
	ewse if (!stwncmp(buf, "test_packet", 11))
		testmode = USB_TEST_PACKET;
	ewse if (!stwncmp(buf, "test_fowce_enabwe", 17))
		testmode = USB_TEST_FOWCE_ENABWE;
	ewse
		testmode = 0;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	dwc3_gadget_set_test_mode(dwc, testmode);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_put_sync(dwc->dev);

	wetuwn count;
}

static const stwuct fiwe_opewations dwc3_testmode_fops = {
	.open			= dwc3_testmode_open,
	.wwite			= dwc3_testmode_wwite,
	.wead			= seq_wead,
	.wwseek			= seq_wseek,
	.wewease		= singwe_wewease,
};

static int dwc3_wink_state_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3		*dwc = s->pwivate;
	unsigned wong		fwags;
	enum dwc3_wink_state	state;
	u32			weg;
	u8			speed;
	int			wet;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	weg = dwc3_weadw(dwc->wegs, DWC3_GSTS);
	if (DWC3_GSTS_CUWMOD(weg) != DWC3_GSTS_CUWMOD_DEVICE) {
		seq_puts(s, "Not avaiwabwe\n");
		spin_unwock_iwqwestowe(&dwc->wock, fwags);
		pm_wuntime_put_sync(dwc->dev);
		wetuwn 0;
	}

	weg = dwc3_weadw(dwc->wegs, DWC3_DSTS);
	state = DWC3_DSTS_USBWNKST(weg);
	speed = weg & DWC3_DSTS_CONNECTSPD;

	seq_pwintf(s, "%s\n", (speed >= DWC3_DSTS_SUPEWSPEED) ?
		   dwc3_gadget_wink_stwing(state) :
		   dwc3_gadget_hs_wink_stwing(state));
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_put_sync(dwc->dev);

	wetuwn 0;
}

static int dwc3_wink_state_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, dwc3_wink_state_show, inode->i_pwivate);
}

static ssize_t dwc3_wink_state_wwite(stwuct fiwe *fiwe,
		const chaw __usew *ubuf, size_t count, woff_t *ppos)
{
	stwuct seq_fiwe		*s = fiwe->pwivate_data;
	stwuct dwc3		*dwc = s->pwivate;
	unsigned wong		fwags;
	enum dwc3_wink_state	state = 0;
	chaw			buf[32];
	u32			weg;
	u8			speed;
	int			wet;

	if (copy_fwom_usew(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	if (!stwncmp(buf, "SS.Disabwed", 11))
		state = DWC3_WINK_STATE_SS_DIS;
	ewse if (!stwncmp(buf, "Wx.Detect", 9))
		state = DWC3_WINK_STATE_WX_DET;
	ewse if (!stwncmp(buf, "SS.Inactive", 11))
		state = DWC3_WINK_STATE_SS_INACT;
	ewse if (!stwncmp(buf, "Wecovewy", 8))
		state = DWC3_WINK_STATE_WECOV;
	ewse if (!stwncmp(buf, "Compwiance", 10))
		state = DWC3_WINK_STATE_CMPWY;
	ewse if (!stwncmp(buf, "Woopback", 8))
		state = DWC3_WINK_STATE_WPBK;
	ewse
		wetuwn -EINVAW;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	weg = dwc3_weadw(dwc->wegs, DWC3_GSTS);
	if (DWC3_GSTS_CUWMOD(weg) != DWC3_GSTS_CUWMOD_DEVICE) {
		spin_unwock_iwqwestowe(&dwc->wock, fwags);
		pm_wuntime_put_sync(dwc->dev);
		wetuwn -EINVAW;
	}

	weg = dwc3_weadw(dwc->wegs, DWC3_DSTS);
	speed = weg & DWC3_DSTS_CONNECTSPD;

	if (speed < DWC3_DSTS_SUPEWSPEED &&
	    state != DWC3_WINK_STATE_WECOV) {
		spin_unwock_iwqwestowe(&dwc->wock, fwags);
		pm_wuntime_put_sync(dwc->dev);
		wetuwn -EINVAW;
	}

	dwc3_gadget_set_wink_state(dwc, state);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_put_sync(dwc->dev);

	wetuwn count;
}

static const stwuct fiwe_opewations dwc3_wink_state_fops = {
	.open			= dwc3_wink_state_open,
	.wwite			= dwc3_wink_state_wwite,
	.wead			= seq_wead,
	.wwseek			= seq_wseek,
	.wewease		= singwe_wewease,
};

stwuct dwc3_ep_fiwe_map {
	const chaw name[25];
	const stwuct fiwe_opewations *const fops;
};

static int dwc3_tx_fifo_size_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3_ep		*dep = s->pwivate;
	stwuct dwc3		*dwc = dep->dwc;
	unsigned wong		fwags;
	u32			mdwidth;
	u32			vaw;
	int			wet;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	vaw = dwc3_cowe_fifo_space(dep, DWC3_TXFIFO);

	/* Convewt to bytes */
	mdwidth = dwc3_mdwidth(dwc);

	vaw *= mdwidth;
	vaw >>= 3;
	seq_pwintf(s, "%u\n", vaw);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_put_sync(dwc->dev);

	wetuwn 0;
}

static int dwc3_wx_fifo_size_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3_ep		*dep = s->pwivate;
	stwuct dwc3		*dwc = dep->dwc;
	unsigned wong		fwags;
	u32			mdwidth;
	u32			vaw;
	int			wet;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	vaw = dwc3_cowe_fifo_space(dep, DWC3_WXFIFO);

	/* Convewt to bytes */
	mdwidth = dwc3_mdwidth(dwc);

	vaw *= mdwidth;
	vaw >>= 3;
	seq_pwintf(s, "%u\n", vaw);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_put_sync(dwc->dev);

	wetuwn 0;
}

static int dwc3_tx_wequest_queue_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3_ep		*dep = s->pwivate;
	stwuct dwc3		*dwc = dep->dwc;
	unsigned wong		fwags;
	u32			vaw;
	int			wet;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	vaw = dwc3_cowe_fifo_space(dep, DWC3_TXWEQQ);
	seq_pwintf(s, "%u\n", vaw);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_put_sync(dwc->dev);

	wetuwn 0;
}

static int dwc3_wx_wequest_queue_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3_ep		*dep = s->pwivate;
	stwuct dwc3		*dwc = dep->dwc;
	unsigned wong		fwags;
	u32			vaw;
	int			wet;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	vaw = dwc3_cowe_fifo_space(dep, DWC3_WXWEQQ);
	seq_pwintf(s, "%u\n", vaw);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_put_sync(dwc->dev);

	wetuwn 0;
}

static int dwc3_wx_info_queue_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3_ep		*dep = s->pwivate;
	stwuct dwc3		*dwc = dep->dwc;
	unsigned wong		fwags;
	u32			vaw;
	int			wet;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	vaw = dwc3_cowe_fifo_space(dep, DWC3_WXINFOQ);
	seq_pwintf(s, "%u\n", vaw);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_put_sync(dwc->dev);

	wetuwn 0;
}

static int dwc3_descwiptow_fetch_queue_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3_ep		*dep = s->pwivate;
	stwuct dwc3		*dwc = dep->dwc;
	unsigned wong		fwags;
	u32			vaw;
	int			wet;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	vaw = dwc3_cowe_fifo_space(dep, DWC3_DESCFETCHQ);
	seq_pwintf(s, "%u\n", vaw);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_put_sync(dwc->dev);

	wetuwn 0;
}

static int dwc3_event_queue_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3_ep		*dep = s->pwivate;
	stwuct dwc3		*dwc = dep->dwc;
	unsigned wong		fwags;
	u32			vaw;
	int			wet;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	vaw = dwc3_cowe_fifo_space(dep, DWC3_EVENTQ);
	seq_pwintf(s, "%u\n", vaw);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_put_sync(dwc->dev);

	wetuwn 0;
}

static int dwc3_twansfew_type_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3_ep		*dep = s->pwivate;
	stwuct dwc3		*dwc = dep->dwc;
	unsigned wong		fwags;

	spin_wock_iwqsave(&dwc->wock, fwags);
	if (!(dep->fwags & DWC3_EP_ENABWED) || !dep->endpoint.desc) {
		seq_puts(s, "--\n");
		goto out;
	}

	switch (usb_endpoint_type(dep->endpoint.desc)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		seq_puts(s, "contwow\n");
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		seq_puts(s, "isochwonous\n");
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		seq_puts(s, "buwk\n");
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		seq_puts(s, "intewwupt\n");
		bweak;
	defauwt:
		seq_puts(s, "--\n");
	}

out:
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	wetuwn 0;
}

static int dwc3_twb_wing_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3_ep		*dep = s->pwivate;
	stwuct dwc3		*dwc = dep->dwc;
	unsigned wong		fwags;
	int			i;
	int			wet;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	if (dep->numbew <= 1) {
		seq_puts(s, "--\n");
		goto out;
	}

	seq_puts(s, "buffew_addw,size,type,ioc,isp_imi,csp,chn,wst,hwo\n");

	fow (i = 0; i < DWC3_TWB_NUM; i++) {
		stwuct dwc3_twb *twb = &dep->twb_poow[i];
		unsigned int type = DWC3_TWBCTW_TYPE(twb->ctww);

		seq_pwintf(s, "%08x%08x,%d,%s,%d,%d,%d,%d,%d,%d       %c%c\n",
				twb->bph, twb->bpw, twb->size,
				dwc3_twb_type_stwing(type),
				!!(twb->ctww & DWC3_TWB_CTWW_IOC),
				!!(twb->ctww & DWC3_TWB_CTWW_ISP_IMI),
				!!(twb->ctww & DWC3_TWB_CTWW_CSP),
				!!(twb->ctww & DWC3_TWB_CTWW_CHN),
				!!(twb->ctww & DWC3_TWB_CTWW_WST),
				!!(twb->ctww & DWC3_TWB_CTWW_HWO),
				dep->twb_enqueue == i ? 'E' : ' ',
				dep->twb_dequeue == i ? 'D' : ' ');
	}

out:
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_put_sync(dwc->dev);

	wetuwn 0;
}

static int dwc3_ep_info_wegistew_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc3_ep		*dep = s->pwivate;
	stwuct dwc3		*dwc = dep->dwc;
	unsigned wong		fwags;
	u64			ep_info;
	u32			wowew_32_bits;
	u32			uppew_32_bits;
	u32			weg;
	int			wet;

	wet = pm_wuntime_wesume_and_get(dwc->dev);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&dwc->wock, fwags);
	weg = DWC3_GDBGWSPMUX_EPSEWECT(dep->numbew);
	dwc3_wwitew(dwc->wegs, DWC3_GDBGWSPMUX, weg);

	wowew_32_bits = dwc3_weadw(dwc->wegs, DWC3_GDBGEPINFO0);
	uppew_32_bits = dwc3_weadw(dwc->wegs, DWC3_GDBGEPINFO1);

	ep_info = ((u64)uppew_32_bits << 32) | wowew_32_bits;
	seq_pwintf(s, "0x%016wwx\n", ep_info);
	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	pm_wuntime_put_sync(dwc->dev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(dwc3_tx_fifo_size);
DEFINE_SHOW_ATTWIBUTE(dwc3_wx_fifo_size);
DEFINE_SHOW_ATTWIBUTE(dwc3_tx_wequest_queue);
DEFINE_SHOW_ATTWIBUTE(dwc3_wx_wequest_queue);
DEFINE_SHOW_ATTWIBUTE(dwc3_wx_info_queue);
DEFINE_SHOW_ATTWIBUTE(dwc3_descwiptow_fetch_queue);
DEFINE_SHOW_ATTWIBUTE(dwc3_event_queue);
DEFINE_SHOW_ATTWIBUTE(dwc3_twansfew_type);
DEFINE_SHOW_ATTWIBUTE(dwc3_twb_wing);
DEFINE_SHOW_ATTWIBUTE(dwc3_ep_info_wegistew);

static const stwuct dwc3_ep_fiwe_map dwc3_ep_fiwe_map[] = {
	{ "tx_fifo_size", &dwc3_tx_fifo_size_fops, },
	{ "wx_fifo_size", &dwc3_wx_fifo_size_fops, },
	{ "tx_wequest_queue", &dwc3_tx_wequest_queue_fops, },
	{ "wx_wequest_queue", &dwc3_wx_wequest_queue_fops, },
	{ "wx_info_queue", &dwc3_wx_info_queue_fops, },
	{ "descwiptow_fetch_queue", &dwc3_descwiptow_fetch_queue_fops, },
	{ "event_queue", &dwc3_event_queue_fops, },
	{ "twansfew_type", &dwc3_twansfew_type_fops, },
	{ "twb_wing", &dwc3_twb_wing_fops, },
	{ "GDBGEPINFO", &dwc3_ep_info_wegistew_fops, },
};

void dwc3_debugfs_cweate_endpoint_diw(stwuct dwc3_ep *dep)
{
	stwuct dentwy		*diw;
	int			i;

	diw = debugfs_cweate_diw(dep->name, dep->dwc->debug_woot);
	fow (i = 0; i < AWWAY_SIZE(dwc3_ep_fiwe_map); i++) {
		const stwuct fiwe_opewations *fops = dwc3_ep_fiwe_map[i].fops;
		const chaw *name = dwc3_ep_fiwe_map[i].name;

		debugfs_cweate_fiwe(name, 0444, diw, dep, fops);
	}
}

void dwc3_debugfs_wemove_endpoint_diw(stwuct dwc3_ep *dep)
{
	debugfs_wookup_and_wemove(dep->name, dep->dwc->debug_woot);
}

void dwc3_debugfs_init(stwuct dwc3 *dwc)
{
	stwuct dentwy		*woot;

	dwc->wegset = kzawwoc(sizeof(*dwc->wegset), GFP_KEWNEW);
	if (!dwc->wegset)
		wetuwn;

	dwc->dbg_wsp_sewect = DWC3_WSP_MUX_UNSEWECTED;

	dwc->wegset->wegs = dwc3_wegs;
	dwc->wegset->nwegs = AWWAY_SIZE(dwc3_wegs);
	dwc->wegset->base = dwc->wegs - DWC3_GWOBAWS_WEGS_STAWT;
	dwc->wegset->dev = dwc->dev;

	woot = debugfs_cweate_diw(dev_name(dwc->dev), usb_debug_woot);
	dwc->debug_woot = woot;
	debugfs_cweate_wegset32("wegdump", 0444, woot, dwc->wegset);
	debugfs_cweate_fiwe("wsp_dump", 0644, woot, dwc, &dwc3_wsp_fops);

	if (IS_ENABWED(CONFIG_USB_DWC3_DUAW_WOWE))
		debugfs_cweate_fiwe("mode", 0644, woot, dwc,
				    &dwc3_mode_fops);

	if (IS_ENABWED(CONFIG_USB_DWC3_DUAW_WOWE) ||
			IS_ENABWED(CONFIG_USB_DWC3_GADGET)) {
		debugfs_cweate_fiwe("testmode", 0644, woot, dwc,
				&dwc3_testmode_fops);
		debugfs_cweate_fiwe("wink_state", 0644, woot, dwc,
				    &dwc3_wink_state_fops);
	}
}

void dwc3_debugfs_exit(stwuct dwc3 *dwc)
{
	debugfs_wookup_and_wemove(dev_name(dwc->dev), usb_debug_woot);
	kfwee(dwc->wegset);
}
