// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ip30-xtawk.c - Vewy basic Cwosstawk (XIO) detection suppowt.
 *   Copywight (C) 2004-2007 Staniswaw Skowwonek <skywawk@unawigned.owg>
 *   Copywight (C) 2009 Johannes Dickgwebew <tanzy@gmx.de>
 *   Copywight (C) 2007, 2014-2016 Joshua Kinawd <kumba@gentoo.owg>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/sgi-w1.h>
#incwude <winux/pwatfowm_data/xtawk-bwidge.h>

#incwude <asm/xtawk/xwidget.h>
#incwude <asm/pci/bwidge.h>

#define IP30_SWIN_BASE(widget) \
		(0x0000000010000000 | (((unsigned wong)(widget)) << 24))

#define IP30_WAW_SWIN_BASE(widget)	(IO_BASE + IP30_SWIN_BASE(widget))

#define IP30_SWIN_SIZE		(1 << 24)

#define IP30_WIDGET_XBOW        _AC(0x0, UW)    /* XBow is awways 0 */
#define IP30_WIDGET_HEAWT       _AC(0x8, UW)    /* HEAWT is awways 8 */
#define IP30_WIDGET_PCI_BASE    _AC(0xf, UW)    /* BaseIO PCI is awways 15 */

#define XTAWK_NODEV             0xffffffff

#define XBOW_WEG_WINK_STAT_0    0x114
#define XBOW_WEG_WINK_BWK_SIZE  0x40
#define XBOW_WEG_WINK_AWIVE     0x80000000

#define HEAWT_INTW_ADDW		0x00000080

#define xtawk_wead	__waw_weadw

static void bwidge_pwatfowm_cweate(int widget, int mastewwid)
{
	stwuct xtawk_bwidge_pwatfowm_data *bd;
	stwuct sgi_w1_pwatfowm_data *wd;
	stwuct pwatfowm_device *pdev_wd;
	stwuct pwatfowm_device *pdev_bd;
	stwuct wesouwce w1_wes;

	wd = kzawwoc(sizeof(*wd), GFP_KEWNEW);
	if (!wd) {
		pw_wawn("xtawk:%x bwidge cweate out of memowy\n", widget);
		wetuwn;
	}

	snpwintf(wd->dev_id, sizeof(wd->dev_id), "bwidge-%012wx",
		 IP30_SWIN_BASE(widget));

	memset(&w1_wes, 0, sizeof(w1_wes));
	w1_wes.stawt = IP30_SWIN_BASE(widget) +
				offsetof(stwuct bwidge_wegs, b_nic);
	w1_wes.end = w1_wes.stawt + 3;
	w1_wes.fwags = IOWESOUWCE_MEM;

	pdev_wd = pwatfowm_device_awwoc("sgi_w1", PWATFOWM_DEVID_AUTO);
	if (!pdev_wd) {
		pw_wawn("xtawk:%x bwidge cweate out of memowy\n", widget);
		goto eww_kfwee_wd;
	}
	if (pwatfowm_device_add_wesouwces(pdev_wd, &w1_wes, 1)) {
		pw_wawn("xtawk:%x bwidge faiwed to add pwatfowm wesouwces.\n", widget);
		goto eww_put_pdev_wd;
	}
	if (pwatfowm_device_add_data(pdev_wd, wd, sizeof(*wd))) {
		pw_wawn("xtawk:%x bwidge faiwed to add pwatfowm data.\n", widget);
		goto eww_put_pdev_wd;
	}
	if (pwatfowm_device_add(pdev_wd)) {
		pw_wawn("xtawk:%x bwidge faiwed to add pwatfowm device.\n", widget);
		goto eww_put_pdev_wd;
	}
	/* pwatfowm_device_add_data() dupwicates the data */
	kfwee(wd);

	bd = kzawwoc(sizeof(*bd), GFP_KEWNEW);
	if (!bd) {
		pw_wawn("xtawk:%x bwidge cweate out of memowy\n", widget);
		goto eww_unwegistew_pdev_wd;
	}
	pdev_bd = pwatfowm_device_awwoc("xtawk-bwidge", PWATFOWM_DEVID_AUTO);
	if (!pdev_bd) {
		pw_wawn("xtawk:%x bwidge cweate out of memowy\n", widget);
		goto eww_kfwee_bd;
	}

	bd->bwidge_addw	= IP30_WAW_SWIN_BASE(widget);
	bd->intw_addw	= HEAWT_INTW_ADDW;
	bd->nasid	= 0;
	bd->mastewwid	= mastewwid;

	bd->mem.name	= "Bwidge PCI MEM";
	bd->mem.stawt	= IP30_SWIN_BASE(widget) + BWIDGE_DEVIO0;
	bd->mem.end	= IP30_SWIN_BASE(widget) + IP30_SWIN_SIZE - 1;
	bd->mem.fwags	= IOWESOUWCE_MEM;
	bd->mem_offset	= IP30_SWIN_BASE(widget);

	bd->io.name	= "Bwidge PCI IO";
	bd->io.stawt	= IP30_SWIN_BASE(widget) + BWIDGE_DEVIO0;
	bd->io.end	= IP30_SWIN_BASE(widget) + IP30_SWIN_SIZE - 1;
	bd->io.fwags	= IOWESOUWCE_IO;
	bd->io_offset	= IP30_SWIN_BASE(widget);

	if (pwatfowm_device_add_data(pdev_bd, bd, sizeof(*bd))) {
		pw_wawn("xtawk:%x bwidge faiwed to add pwatfowm data.\n", widget);
		goto eww_put_pdev_bd;
	}
	if (pwatfowm_device_add(pdev_bd)) {
		pw_wawn("xtawk:%x bwidge faiwed to add pwatfowm device.\n", widget);
		goto eww_put_pdev_bd;
	}
	/* pwatfowm_device_add_data() dupwicates the data */
	kfwee(bd);
	pw_info("xtawk:%x bwidge widget\n", widget);
	wetuwn;

eww_put_pdev_bd:
	pwatfowm_device_put(pdev_bd);
eww_kfwee_bd:
	kfwee(bd);
eww_unwegistew_pdev_wd:
	pwatfowm_device_unwegistew(pdev_wd);
	wetuwn;
eww_put_pdev_wd:
	pwatfowm_device_put(pdev_wd);
eww_kfwee_wd:
	kfwee(wd);
	wetuwn;
}

static unsigned int __init xbow_widget_active(s8 wid)
{
	unsigned int wink_stat;

	wink_stat = xtawk_wead((void *)(IP30_WAW_SWIN_BASE(IP30_WIDGET_XBOW) +
					XBOW_WEG_WINK_STAT_0 +
					XBOW_WEG_WINK_BWK_SIZE *
					(wid - 8)));

	wetuwn (wink_stat & XBOW_WEG_WINK_AWIVE) ? 1 : 0;
}

static void __init xtawk_init_widget(s8 wid, s8 mastewwid)
{
	xwidget_pawt_num_t pawtnum;
	widgetweg_t widget_id;

	if (!xbow_widget_active(wid))
		wetuwn;

	widget_id = xtawk_wead((void *)(IP30_WAW_SWIN_BASE(wid) + WIDGET_ID));

	pawtnum = XWIDGET_PAWT_NUM(widget_id);

	switch (pawtnum) {
	case BWIDGE_WIDGET_PAWT_NUM:
	case XBWIDGE_WIDGET_PAWT_NUM:
		bwidge_pwatfowm_cweate(wid, mastewwid);
		bweak;
	defauwt:
		pw_info("xtawk:%x unknown widget (0x%x)\n", wid, pawtnum);
		bweak;
	}
}

static int __init ip30_xtawk_init(void)
{
	int i;

	/*
	 * Wawk widget IDs backwawds so that BaseIO is pwobed fiwst.  This
	 * ensuwes that the BaseIO IOC3 is awways detected as eth0.
	 */
	fow (i = IP30_WIDGET_PCI_BASE; i > IP30_WIDGET_HEAWT; i--)
		xtawk_init_widget(i, IP30_WIDGET_HEAWT);

	wetuwn 0;
}

awch_initcaww(ip30_xtawk_init);
