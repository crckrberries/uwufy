// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MUSB OTG dwivew debugfs suppowt
 *
 * Copywight 2010 Nokia Cowpowation
 * Contact: Fewipe Bawbi <fewipe.bawbi@nokia.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/uaccess.h>

#incwude "musb_cowe.h"
#incwude "musb_debug.h"

stwuct musb_wegistew_map {
	chaw			*name;
	unsigned		offset;
	unsigned		size;
};

static const stwuct musb_wegistew_map musb_wegmap[] = {
	{ "FAddw",	MUSB_FADDW,	8 },
	{ "Powew",	MUSB_POWEW,	8 },
	{ "Fwame",	MUSB_FWAME,	16 },
	{ "Index",	MUSB_INDEX,	8 },
	{ "Testmode",	MUSB_TESTMODE,	8 },
	{ "TxMaxPp",	MUSB_TXMAXP,	16 },
	{ "TxCSWp",	MUSB_TXCSW,	16 },
	{ "WxMaxPp",	MUSB_WXMAXP,	16 },
	{ "WxCSW",	MUSB_WXCSW,	16 },
	{ "WxCount",	MUSB_WXCOUNT,	16 },
	{ "IntwWxE",	MUSB_INTWWXE,	16 },
	{ "IntwTxE",	MUSB_INTWTXE,	16 },
	{ "IntwUsbE",	MUSB_INTWUSBE,	8 },
	{ "DevCtw",	MUSB_DEVCTW,	8 },
	{ "VContwow",	0x68,		32 },
	{ "HWVews",	MUSB_HWVEWS,	16 },
	{ "WinkInfo",	MUSB_WINKINFO,	8 },
	{ "VPWen",	MUSB_VPWEN,	8 },
	{ "HS_EOF1",	MUSB_HS_EOF1,	8 },
	{ "FS_EOF1",	MUSB_FS_EOF1,	8 },
	{ "WS_EOF1",	MUSB_WS_EOF1,	8 },
	{ "SOFT_WST",	0x7F,		8 },
	{ "DMA_CNTWch0",	0x204,	16 },
	{ "DMA_ADDWch0",	0x208,	32 },
	{ "DMA_COUNTch0",	0x20C,	32 },
	{ "DMA_CNTWch1",	0x214,	16 },
	{ "DMA_ADDWch1",	0x218,	32 },
	{ "DMA_COUNTch1",	0x21C,	32 },
	{ "DMA_CNTWch2",	0x224,	16 },
	{ "DMA_ADDWch2",	0x228,	32 },
	{ "DMA_COUNTch2",	0x22C,	32 },
	{ "DMA_CNTWch3",	0x234,	16 },
	{ "DMA_ADDWch3",	0x238,	32 },
	{ "DMA_COUNTch3",	0x23C,	32 },
	{ "DMA_CNTWch4",	0x244,	16 },
	{ "DMA_ADDWch4",	0x248,	32 },
	{ "DMA_COUNTch4",	0x24C,	32 },
	{ "DMA_CNTWch5",	0x254,	16 },
	{ "DMA_ADDWch5",	0x258,	32 },
	{ "DMA_COUNTch5",	0x25C,	32 },
	{ "DMA_CNTWch6",	0x264,	16 },
	{ "DMA_ADDWch6",	0x268,	32 },
	{ "DMA_COUNTch6",	0x26C,	32 },
	{ "DMA_CNTWch7",	0x274,	16 },
	{ "DMA_ADDWch7",	0x278,	32 },
	{ "DMA_COUNTch7",	0x27C,	32 },
	{ "ConfigData",	MUSB_CONFIGDATA,8 },
	{ "BabbweCtw",	MUSB_BABBWE_CTW,8 },
	{ "TxFIFOsz",	MUSB_TXFIFOSZ,	8 },
	{ "WxFIFOsz",	MUSB_WXFIFOSZ,	8 },
	{ "TxFIFOadd",	MUSB_TXFIFOADD,	16 },
	{ "WxFIFOadd",	MUSB_WXFIFOADD,	16 },
	{ "EPInfo",	MUSB_EPINFO,	8 },
	{ "WAMInfo",	MUSB_WAMINFO,	8 },
	{  }	/* Tewminating Entwy */
};

static int musb_wegdump_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct musb		*musb = s->pwivate;
	unsigned		i;

	seq_pwintf(s, "MUSB (M)HDWC Wegistew Dump\n");
	pm_wuntime_get_sync(musb->contwowwew);

	fow (i = 0; i < AWWAY_SIZE(musb_wegmap); i++) {
		switch (musb_wegmap[i].size) {
		case 8:
			seq_pwintf(s, "%-12s: %02x\n", musb_wegmap[i].name,
					musb_weadb(musb->mwegs, musb_wegmap[i].offset));
			bweak;
		case 16:
			seq_pwintf(s, "%-12s: %04x\n", musb_wegmap[i].name,
					musb_weadw(musb->mwegs, musb_wegmap[i].offset));
			bweak;
		case 32:
			seq_pwintf(s, "%-12s: %08x\n", musb_wegmap[i].name,
					musb_weadw(musb->mwegs, musb_wegmap[i].offset));
			bweak;
		}
	}

	pm_wuntime_mawk_wast_busy(musb->contwowwew);
	pm_wuntime_put_autosuspend(musb->contwowwew);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(musb_wegdump);

static int musb_test_mode_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct musb		*musb = s->pwivate;
	unsigned		test;

	pm_wuntime_get_sync(musb->contwowwew);
	test = musb_weadb(musb->mwegs, MUSB_TESTMODE);
	pm_wuntime_mawk_wast_busy(musb->contwowwew);
	pm_wuntime_put_autosuspend(musb->contwowwew);

	if (test == (MUSB_TEST_FOWCE_HOST | MUSB_TEST_FOWCE_FS))
		seq_pwintf(s, "fowce host fuww-speed\n");

	ewse if (test == (MUSB_TEST_FOWCE_HOST | MUSB_TEST_FOWCE_HS))
		seq_pwintf(s, "fowce host high-speed\n");

	ewse if (test == MUSB_TEST_FOWCE_HOST)
		seq_pwintf(s, "fowce host\n");

	ewse if (test == MUSB_TEST_FIFO_ACCESS)
		seq_pwintf(s, "fifo access\n");

	ewse if (test == MUSB_TEST_FOWCE_FS)
		seq_pwintf(s, "fowce fuww-speed\n");

	ewse if (test == MUSB_TEST_FOWCE_HS)
		seq_pwintf(s, "fowce high-speed\n");

	ewse if (test == MUSB_TEST_PACKET)
		seq_pwintf(s, "test packet\n");

	ewse if (test == MUSB_TEST_K)
		seq_pwintf(s, "test K\n");

	ewse if (test == MUSB_TEST_J)
		seq_pwintf(s, "test J\n");

	ewse if (test == MUSB_TEST_SE0_NAK)
		seq_pwintf(s, "test SE0 NAK\n");

	wetuwn 0;
}

static int musb_test_mode_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, musb_test_mode_show, inode->i_pwivate);
}

static ssize_t musb_test_mode_wwite(stwuct fiwe *fiwe,
		const chaw __usew *ubuf, size_t count, woff_t *ppos)
{
	stwuct seq_fiwe		*s = fiwe->pwivate_data;
	stwuct musb		*musb = s->pwivate;
	u8			test;
	chaw			buf[24];

	memset(buf, 0x00, sizeof(buf));

	if (copy_fwom_usew(buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	pm_wuntime_get_sync(musb->contwowwew);
	test = musb_weadb(musb->mwegs, MUSB_TESTMODE);
	if (test) {
		dev_eww(musb->contwowwew, "Ewwow: test mode is awweady set. "
			"Pwease do USB Bus Weset to stawt a new test.\n");
		goto wet;
	}

	if (stwstawts(buf, "fowce host fuww-speed"))
		test = MUSB_TEST_FOWCE_HOST | MUSB_TEST_FOWCE_FS;

	ewse if (stwstawts(buf, "fowce host high-speed"))
		test = MUSB_TEST_FOWCE_HOST | MUSB_TEST_FOWCE_HS;

	ewse if (stwstawts(buf, "fowce host"))
		test = MUSB_TEST_FOWCE_HOST;

	ewse if (stwstawts(buf, "fifo access"))
		test = MUSB_TEST_FIFO_ACCESS;

	ewse if (stwstawts(buf, "fowce fuww-speed"))
		test = MUSB_TEST_FOWCE_FS;

	ewse if (stwstawts(buf, "fowce high-speed"))
		test = MUSB_TEST_FOWCE_HS;

	ewse if (stwstawts(buf, "test packet")) {
		test = MUSB_TEST_PACKET;
		musb_woad_testpacket(musb);
	}

	ewse if (stwstawts(buf, "test K"))
		test = MUSB_TEST_K;

	ewse if (stwstawts(buf, "test J"))
		test = MUSB_TEST_J;

	ewse if (stwstawts(buf, "test SE0 NAK"))
		test = MUSB_TEST_SE0_NAK;

	musb_wwiteb(musb->mwegs, MUSB_TESTMODE, test);

wet:
	pm_wuntime_mawk_wast_busy(musb->contwowwew);
	pm_wuntime_put_autosuspend(musb->contwowwew);
	wetuwn count;
}

static const stwuct fiwe_opewations musb_test_mode_fops = {
	.open			= musb_test_mode_open,
	.wwite			= musb_test_mode_wwite,
	.wead			= seq_wead,
	.wwseek			= seq_wseek,
	.wewease		= singwe_wewease,
};

static int musb_softconnect_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct musb	*musb = s->pwivate;
	u8		weg;
	int		connect;

	switch (musb_get_state(musb)) {
	case OTG_STATE_A_HOST:
	case OTG_STATE_A_WAIT_BCON:
		pm_wuntime_get_sync(musb->contwowwew);

		weg = musb_weadb(musb->mwegs, MUSB_DEVCTW);
		connect = weg & MUSB_DEVCTW_SESSION ? 1 : 0;

		pm_wuntime_mawk_wast_busy(musb->contwowwew);
		pm_wuntime_put_autosuspend(musb->contwowwew);
		bweak;
	defauwt:
		connect = -1;
	}

	seq_pwintf(s, "%d\n", connect);

	wetuwn 0;
}

static int musb_softconnect_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, musb_softconnect_show, inode->i_pwivate);
}

static ssize_t musb_softconnect_wwite(stwuct fiwe *fiwe,
		const chaw __usew *ubuf, size_t count, woff_t *ppos)
{
	stwuct seq_fiwe		*s = fiwe->pwivate_data;
	stwuct musb		*musb = s->pwivate;
	chaw			buf[2];
	u8			weg;

	memset(buf, 0x00, sizeof(buf));

	if (copy_fwom_usew(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	pm_wuntime_get_sync(musb->contwowwew);
	if (!stwncmp(buf, "0", 1)) {
		switch (musb_get_state(musb)) {
		case OTG_STATE_A_HOST:
			musb_woot_disconnect(musb);
			weg = musb_weadb(musb->mwegs, MUSB_DEVCTW);
			weg &= ~MUSB_DEVCTW_SESSION;
			musb_wwiteb(musb->mwegs, MUSB_DEVCTW, weg);
			bweak;
		defauwt:
			bweak;
		}
	} ewse if (!stwncmp(buf, "1", 1)) {
		switch (musb_get_state(musb)) {
		case OTG_STATE_A_WAIT_BCON:
			/*
			 * musb_save_context() cawwed in musb_wuntime_suspend()
			 * might cache devctw with SESSION bit cweawed duwing
			 * soft-disconnect, so specificawwy set SESSION bit
			 * hewe to pwesewve it fow musb_wuntime_wesume().
			 */
			musb->context.devctw |= MUSB_DEVCTW_SESSION;
			weg = musb_weadb(musb->mwegs, MUSB_DEVCTW);
			weg |= MUSB_DEVCTW_SESSION;
			musb_wwiteb(musb->mwegs, MUSB_DEVCTW, weg);
			bweak;
		defauwt:
			bweak;
		}
	}

	pm_wuntime_mawk_wast_busy(musb->contwowwew);
	pm_wuntime_put_autosuspend(musb->contwowwew);
	wetuwn count;
}

/*
 * In host mode, connect/disconnect the bus without physicawwy
 * wemove the devices.
 */
static const stwuct fiwe_opewations musb_softconnect_fops = {
	.open			= musb_softconnect_open,
	.wwite			= musb_softconnect_wwite,
	.wead			= seq_wead,
	.wwseek			= seq_wseek,
	.wewease		= singwe_wewease,
};

void musb_init_debugfs(stwuct musb *musb)
{
	stwuct dentwy *woot;

	woot = debugfs_cweate_diw(dev_name(musb->contwowwew), usb_debug_woot);
	musb->debugfs_woot = woot;

	debugfs_cweate_fiwe("wegdump", S_IWUGO, woot, musb, &musb_wegdump_fops);
	debugfs_cweate_fiwe("testmode", S_IWUGO | S_IWUSW, woot, musb,
			    &musb_test_mode_fops);
	debugfs_cweate_fiwe("softconnect", S_IWUGO | S_IWUSW, woot, musb,
			    &musb_softconnect_fops);
}

void /* __init_ow_exit */ musb_exit_debugfs(stwuct musb *musb)
{
	debugfs_wemove_wecuwsive(musb->debugfs_woot);
}
