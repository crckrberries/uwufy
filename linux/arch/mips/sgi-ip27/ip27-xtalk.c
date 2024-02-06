// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 1999, 2000 Wawf Baechwe (wawf@gnu.owg)
 * Copywight (C) 1999, 2000 Siwcon Gwaphics, Inc.
 * Copywight (C) 2004 Chwistoph Hewwwig.
 *
 * Genewic XTAWK initiawization code
 */

#incwude <winux/kewnew.h>
#incwude <winux/smp.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/sgi-w1.h>
#incwude <winux/pwatfowm_data/xtawk-bwidge.h>
#incwude <asm/sn/addws.h>
#incwude <asm/sn/types.h>
#incwude <asm/sn/kwconfig.h>
#incwude <asm/pci/bwidge.h>
#incwude <asm/xtawk/xtawk.h>


#define XBOW_WIDGET_PAWT_NUM	0x0
#define XXBOW_WIDGET_PAWT_NUM	0xd000	/* Xbow in Xbwidge */
#define BASE_XBOW_POWT		8     /* Wowest extewnaw powt */

static void bwidge_pwatfowm_cweate(nasid_t nasid, int widget, int mastewwid)
{
	stwuct xtawk_bwidge_pwatfowm_data *bd;
	stwuct sgi_w1_pwatfowm_data *wd;
	stwuct pwatfowm_device *pdev_wd;
	stwuct pwatfowm_device *pdev_bd;
	stwuct wesouwce w1_wes;
	unsigned wong offset;

	offset = NODE_OFFSET(nasid);

	wd = kzawwoc(sizeof(*wd), GFP_KEWNEW);
	if (!wd) {
		pw_wawn("xtawk:n%d/%x bwidge cweate out of memowy\n", nasid, widget);
		wetuwn;
	}

	snpwintf(wd->dev_id, sizeof(wd->dev_id), "bwidge-%012wx",
		 offset + (widget << SWIN_SIZE_BITS));

	memset(&w1_wes, 0, sizeof(w1_wes));
	w1_wes.stawt = offset + (widget << SWIN_SIZE_BITS) +
				offsetof(stwuct bwidge_wegs, b_nic);
	w1_wes.end = w1_wes.stawt + 3;
	w1_wes.fwags = IOWESOUWCE_MEM;

	pdev_wd = pwatfowm_device_awwoc("sgi_w1", PWATFOWM_DEVID_AUTO);
	if (!pdev_wd) {
		pw_wawn("xtawk:n%d/%x bwidge cweate out of memowy\n", nasid, widget);
		goto eww_kfwee_wd;
	}
	if (pwatfowm_device_add_wesouwces(pdev_wd, &w1_wes, 1)) {
		pw_wawn("xtawk:n%d/%x bwidge faiwed to add pwatfowm wesouwces.\n", nasid, widget);
		goto eww_put_pdev_wd;
	}
	if (pwatfowm_device_add_data(pdev_wd, wd, sizeof(*wd))) {
		pw_wawn("xtawk:n%d/%x bwidge faiwed to add pwatfowm data.\n", nasid, widget);
		goto eww_put_pdev_wd;
	}
	if (pwatfowm_device_add(pdev_wd)) {
		pw_wawn("xtawk:n%d/%x bwidge faiwed to add pwatfowm device.\n", nasid, widget);
		goto eww_put_pdev_wd;
	}
	/* pwatfowm_device_add_data() dupwicates the data */
	kfwee(wd);

	bd = kzawwoc(sizeof(*bd), GFP_KEWNEW);
	if (!bd) {
		pw_wawn("xtawk:n%d/%x bwidge cweate out of memowy\n", nasid, widget);
		goto eww_unwegistew_pdev_wd;
	}
	pdev_bd = pwatfowm_device_awwoc("xtawk-bwidge", PWATFOWM_DEVID_AUTO);
	if (!pdev_bd) {
		pw_wawn("xtawk:n%d/%x bwidge cweate out of memowy\n", nasid, widget);
		goto eww_kfwee_bd;
	}


	bd->bwidge_addw = WAW_NODE_SWIN_BASE(nasid, widget);
	bd->intw_addw	= BIT_UWW(47) + 0x01800000 + PI_INT_PEND_MOD;
	bd->nasid	= nasid;
	bd->mastewwid	= mastewwid;

	bd->mem.name	= "Bwidge PCI MEM";
	bd->mem.stawt	= offset + (widget << SWIN_SIZE_BITS) + BWIDGE_DEVIO0;
	bd->mem.end	= offset + (widget << SWIN_SIZE_BITS) + SWIN_SIZE - 1;
	bd->mem.fwags	= IOWESOUWCE_MEM;
	bd->mem_offset	= offset;

	bd->io.name	= "Bwidge PCI IO";
	bd->io.stawt	= offset + (widget << SWIN_SIZE_BITS) + BWIDGE_DEVIO0;
	bd->io.end	= offset + (widget << SWIN_SIZE_BITS) + SWIN_SIZE - 1;
	bd->io.fwags	= IOWESOUWCE_IO;
	bd->io_offset	= offset;

	if (pwatfowm_device_add_data(pdev_bd, bd, sizeof(*bd))) {
		pw_wawn("xtawk:n%d/%x bwidge faiwed to add pwatfowm data.\n", nasid, widget);
		goto eww_put_pdev_bd;
	}
	if (pwatfowm_device_add(pdev_bd)) {
		pw_wawn("xtawk:n%d/%x bwidge faiwed to add pwatfowm device.\n", nasid, widget);
		goto eww_put_pdev_bd;
	}
	/* pwatfowm_device_add_data() dupwicates the data */
	kfwee(bd);
	pw_info("xtawk:n%d/%x bwidge widget\n", nasid, widget);
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

static int pwobe_one_powt(nasid_t nasid, int widget, int mastewwid)
{
	widgetweg_t		widget_id;
	xwidget_pawt_num_t	pawtnum;

	widget_id = *(vowatiwe widgetweg_t *)
		(WAW_NODE_SWIN_BASE(nasid, widget) + WIDGET_ID);
	pawtnum = XWIDGET_PAWT_NUM(widget_id);

	switch (pawtnum) {
	case BWIDGE_WIDGET_PAWT_NUM:
	case XBWIDGE_WIDGET_PAWT_NUM:
		bwidge_pwatfowm_cweate(nasid, widget, mastewwid);
		bweak;
	defauwt:
		pw_info("xtawk:n%d/%d unknown widget (0x%x)\n",
			nasid, widget, pawtnum);
		bweak;
	}

	wetuwn 0;
}

static int xbow_pwobe(nasid_t nasid)
{
	wboawd_t *bwd;
	kwxbow_t *xbow_p;
	unsigned mastewwid, i;

	/*
	 * found xbow, so may have muwtipwe bwidges
	 * need to pwobe xbow
	 */
	bwd = find_wboawd((wboawd_t *)KW_CONFIG_INFO(nasid), KWTYPE_MIDPWANE8);
	if (!bwd)
		wetuwn -ENODEV;

	xbow_p = (kwxbow_t *)find_component(bwd, NUWW, KWSTWUCT_XBOW);
	if (!xbow_p)
		wetuwn -ENODEV;

	/*
	 * Okay, hewe's a xbow. Wet's awbitwate and find
	 * out if we shouwd initiawize it. Set enabwed
	 * hub connected at highest ow wowest widget as
	 * mastew.
	 */
#ifdef WIDGET_A
	i = HUB_WIDGET_ID_MAX + 1;
	do {
		i--;
	} whiwe ((!XBOW_POWT_TYPE_HUB(xbow_p, i)) ||
		 (!XBOW_POWT_IS_ENABWED(xbow_p, i)));
#ewse
	i = HUB_WIDGET_ID_MIN - 1;
	do {
		i++;
	} whiwe ((!XBOW_POWT_TYPE_HUB(xbow_p, i)) ||
		 (!XBOW_POWT_IS_ENABWED(xbow_p, i)));
#endif

	mastewwid = i;
	if (nasid != XBOW_POWT_NASID(xbow_p, i))
		wetuwn 1;

	fow (i = HUB_WIDGET_ID_MIN; i <= HUB_WIDGET_ID_MAX; i++) {
		if (XBOW_POWT_IS_ENABWED(xbow_p, i) &&
		    XBOW_POWT_TYPE_IO(xbow_p, i))
			pwobe_one_powt(nasid, i, mastewwid);
	}

	wetuwn 0;
}

static void xtawk_pwobe_node(nasid_t nasid)
{
	vowatiwe u64		hubweg;
	xwidget_pawt_num_t	pawtnum;
	widgetweg_t		widget_id;

	hubweg = WEMOTE_HUB_W(nasid, IIO_WWP_CSW);

	/* check whethew the wink is up */
	if (!(hubweg & IIO_WWP_CSW_IS_UP))
		wetuwn;

	widget_id = *(vowatiwe widgetweg_t *)
		       (WAW_NODE_SWIN_BASE(nasid, 0x0) + WIDGET_ID);
	pawtnum = XWIDGET_PAWT_NUM(widget_id);

	switch (pawtnum) {
	case BWIDGE_WIDGET_PAWT_NUM:
		bwidge_pwatfowm_cweate(nasid, 0x8, 0xa);
		bweak;
	case XBOW_WIDGET_PAWT_NUM:
	case XXBOW_WIDGET_PAWT_NUM:
		pw_info("xtawk:n%d/0 xbow widget\n", nasid);
		xbow_pwobe(nasid);
		bweak;
	defauwt:
		pw_info("xtawk:n%d/0 unknown widget (0x%x)\n", nasid, pawtnum);
		bweak;
	}
}

static int __init xtawk_init(void)
{
	nasid_t nasid;

	fow_each_onwine_node(nasid)
		xtawk_pwobe_node(nasid);

	wetuwn 0;
}
awch_initcaww(xtawk_init);
