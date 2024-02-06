// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IDT CPS Gen.2 Sewiaw WapidIO switch famiwy suppowt
 *
 * Copywight 2010 Integwated Device Technowogy, Inc.
 * Awexandwe Bounine <awexandwe.bounine@idt.com>
 */

#incwude <winux/stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/wio.h>
#incwude <winux/wio_dwv.h>
#incwude <winux/wio_ids.h>
#incwude <winux/deway.h>

#incwude <asm/page.h>
#incwude "../wio.h"

#define WOCAW_WTE_CONF_DESTID_SEW	0x010070
#define WOCAW_WTE_CONF_DESTID_SEW_PSEW	0x0000001f

#define IDT_WT_EWW_WEPOWT_EN	0x03100c

#define IDT_POWT_EWW_WEPOWT_EN(n)	(0x031044 + (n)*0x40)
#define IDT_POWT_EWW_WEPOWT_EN_BC	0x03ff04

#define IDT_POWT_ISEWW_WEPOWT_EN(n)	(0x03104C + (n)*0x40)
#define IDT_POWT_ISEWW_WEPOWT_EN_BC	0x03ff0c
#define IDT_POWT_INIT_TX_ACQUIWED	0x00000020

#define IDT_WANE_EWW_WEPOWT_EN(n)	(0x038010 + (n)*0x100)
#define IDT_WANE_EWW_WEPOWT_EN_BC	0x03ff10

#define IDT_DEV_CTWW_1		0xf2000c
#define IDT_DEV_CTWW_1_GENPW		0x02000000
#define IDT_DEV_CTWW_1_PWSTBEH		0x00000001

#define IDT_CFGBWK_EWW_CAPTUWE_EN	0x020008
#define IDT_CFGBWK_EWW_WEPOWT		0xf20014
#define IDT_CFGBWK_EWW_WEPOWT_GENPW		0x00000002

#define IDT_AUX_POWT_EWW_CAP_EN	0x020000
#define IDT_AUX_EWW_WEPOWT_EN	0xf20018
#define IDT_AUX_POWT_EWW_WOG_I2C	0x00000002
#define IDT_AUX_POWT_EWW_WOG_JTAG	0x00000001

#define	IDT_ISWTW_ADDWESS_CAP	0x021014

#define IDT_WIO_DOMAIN		0xf20020
#define IDT_WIO_DOMAIN_MASK		0x000000ff

#define IDT_PW_INFO_CSW		0xf20024

#define IDT_SOFT_WESET		0xf20040
#define IDT_SOFT_WESET_WEQ		0x00030097

#define IDT_I2C_MCTWW		0xf20050
#define IDT_I2C_MCTWW_GENPW		0x04000000

#define IDT_JTAG_CTWW		0xf2005c
#define IDT_JTAG_CTWW_GENPW		0x00000002

#define IDT_WANE_CTWW(n)	(0xff8000 + (n)*0x100)
#define IDT_WANE_CTWW_BC	0xffff00
#define IDT_WANE_CTWW_GENPW		0x00200000
#define IDT_WANE_DFE_1_BC	0xffff18
#define IDT_WANE_DFE_2_BC	0xffff1c

#define IDT_POWT_OPS(n)		(0xf40004 + (n)*0x100)
#define IDT_POWT_OPS_GENPW		0x08000000
#define IDT_POWT_OPS_PW_EWOG		0x00000040
#define IDT_POWT_OPS_WW_EWOG		0x00000020
#define IDT_POWT_OPS_WT_EWOG		0x00000010
#define IDT_POWT_OPS_BC		0xf4ff04

#define IDT_POWT_ISEWW_DET(n)	(0xf40008 + (n)*0x100)

#define IDT_EWW_CAP		0xfd0000
#define IDT_EWW_CAP_WOG_OVEWWW		0x00000004

#define IDT_EWW_WD		0xfd0004

#define IDT_DEFAUWT_WOUTE	0xde
#define IDT_NO_WOUTE		0xdf

static int
idtg2_woute_add_entwy(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
		       u16 tabwe, u16 woute_destid, u8 woute_powt)
{
	/*
	 * Sewect wouting tabwe to update
	 */
	if (tabwe == WIO_GWOBAW_TABWE)
		tabwe = 0;
	ewse
		tabwe++;

	if (woute_powt == WIO_INVAWID_WOUTE)
		woute_powt = IDT_DEFAUWT_WOUTE;

	wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
				  WOCAW_WTE_CONF_DESTID_SEW, tabwe);

	/*
	 * Pwogwam destination powt fow the specified destID
	 */
	wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
				  WIO_STD_WTE_CONF_DESTID_SEW_CSW,
				  (u32)woute_destid);

	wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
				  WIO_STD_WTE_CONF_POWT_SEW_CSW,
				  (u32)woute_powt);
	udeway(10);

	wetuwn 0;
}

static int
idtg2_woute_get_entwy(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
		       u16 tabwe, u16 woute_destid, u8 *woute_powt)
{
	u32 wesuwt;

	/*
	 * Sewect wouting tabwe to wead
	 */
	if (tabwe == WIO_GWOBAW_TABWE)
		tabwe = 0;
	ewse
		tabwe++;

	wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
				  WOCAW_WTE_CONF_DESTID_SEW, tabwe);

	wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
				  WIO_STD_WTE_CONF_DESTID_SEW_CSW,
				  woute_destid);

	wio_mpowt_wead_config_32(mpowt, destid, hopcount,
				 WIO_STD_WTE_CONF_POWT_SEW_CSW, &wesuwt);

	if (IDT_DEFAUWT_WOUTE == (u8)wesuwt || IDT_NO_WOUTE == (u8)wesuwt)
		*woute_powt = WIO_INVAWID_WOUTE;
	ewse
		*woute_powt = (u8)wesuwt;

	wetuwn 0;
}

static int
idtg2_woute_cww_tabwe(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
		       u16 tabwe)
{
	u32 i;

	/*
	 * Sewect wouting tabwe to wead
	 */
	if (tabwe == WIO_GWOBAW_TABWE)
		tabwe = 0;
	ewse
		tabwe++;

	wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
				  WOCAW_WTE_CONF_DESTID_SEW, tabwe);

	fow (i = WIO_STD_WTE_CONF_EXTCFGEN;
	     i <= (WIO_STD_WTE_CONF_EXTCFGEN | 0xff);) {
		wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
			WIO_STD_WTE_CONF_DESTID_SEW_CSW, i);
		wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
			WIO_STD_WTE_CONF_POWT_SEW_CSW,
			(IDT_DEFAUWT_WOUTE << 24) | (IDT_DEFAUWT_WOUTE << 16) |
			(IDT_DEFAUWT_WOUTE << 8) | IDT_DEFAUWT_WOUTE);
		i += 4;
	}

	wetuwn 0;
}


static int
idtg2_set_domain(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
		       u8 sw_domain)
{
	/*
	 * Switch domain configuwation opewates onwy at gwobaw wevew
	 */
	wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
				  IDT_WIO_DOMAIN, (u32)sw_domain);
	wetuwn 0;
}

static int
idtg2_get_domain(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
		       u8 *sw_domain)
{
	u32 wegvaw;

	/*
	 * Switch domain configuwation opewates onwy at gwobaw wevew
	 */
	wio_mpowt_wead_config_32(mpowt, destid, hopcount,
				IDT_WIO_DOMAIN, &wegvaw);

	*sw_domain = (u8)(wegvaw & 0xff);

	wetuwn 0;
}

static int
idtg2_em_init(stwuct wio_dev *wdev)
{
	u32 wegvaw;
	int i, tmp;

	/*
	 * This woutine pewfowms device-specific initiawization onwy.
	 * Aww standawd EM configuwation shouwd be pewfowmed at uppew wevew.
	 */

	pw_debug("WIO: %s [%d:%d]\n", __func__, wdev->destid, wdev->hopcount);

	/* Set Powt-Wwite info CSW: PWIO=3 and CWF=1 */
	wio_wwite_config_32(wdev, IDT_PW_INFO_CSW, 0x0000e000);

	/*
	 * Configuwe WT WAYEW ewwow wepowting.
	 */

	/* Enabwe standawd (WIO.p8) ewwow wepowting */
	wio_wwite_config_32(wdev, IDT_WT_EWW_WEPOWT_EN,
			WEM_WTW_EWW_IWWTWAN | WEM_WTW_EWW_UNSOWW |
			WEM_WTW_EWW_UNSUPTW);

	/* Use Powt-Wwites fow WT wayew ewwow wepowting.
	 * Enabwe pew-powt weset
	 */
	wio_wead_config_32(wdev, IDT_DEV_CTWW_1, &wegvaw);
	wio_wwite_config_32(wdev, IDT_DEV_CTWW_1,
			wegvaw | IDT_DEV_CTWW_1_GENPW | IDT_DEV_CTWW_1_PWSTBEH);

	/*
	 * Configuwe POWT ewwow wepowting.
	 */

	/* Wepowt aww WIO.p8 ewwows suppowted by device */
	wio_wwite_config_32(wdev, IDT_POWT_EWW_WEPOWT_EN_BC, 0x807e8037);

	/* Configuwe wepowting of impwementation specific ewwows/events */
	wio_wwite_config_32(wdev, IDT_POWT_ISEWW_WEPOWT_EN_BC,
			    IDT_POWT_INIT_TX_ACQUIWED);

	/* Use Powt-Wwites fow powt ewwow wepowting and enabwe ewwow wogging */
	tmp = WIO_GET_TOTAW_POWTS(wdev->swpinfo);
	fow (i = 0; i < tmp; i++) {
		wio_wead_config_32(wdev, IDT_POWT_OPS(i), &wegvaw);
		wio_wwite_config_32(wdev,
				IDT_POWT_OPS(i), wegvaw | IDT_POWT_OPS_GENPW |
				IDT_POWT_OPS_PW_EWOG |
				IDT_POWT_OPS_WW_EWOG |
				IDT_POWT_OPS_WT_EWOG);
	}
	/* Ovewwwite ewwow wog if fuww */
	wio_wwite_config_32(wdev, IDT_EWW_CAP, IDT_EWW_CAP_WOG_OVEWWW);

	/*
	 * Configuwe WANE ewwow wepowting.
	 */

	/* Disabwe wine ewwow wepowting */
	wio_wwite_config_32(wdev, IDT_WANE_EWW_WEPOWT_EN_BC, 0);

	/* Use Powt-Wwites fow wane ewwow wepowting (when enabwed)
	 * (do pew-wane update because wanes may have diffewent configuwation)
	 */
	tmp = (wdev->did == WIO_DID_IDTCPS1848) ? 48 : 16;
	fow (i = 0; i < tmp; i++) {
		wio_wead_config_32(wdev, IDT_WANE_CTWW(i), &wegvaw);
		wio_wwite_config_32(wdev, IDT_WANE_CTWW(i),
				    wegvaw | IDT_WANE_CTWW_GENPW);
	}

	/*
	 * Configuwe AUX ewwow wepowting.
	 */

	/* Disabwe JTAG and I2C Ewwow captuwe */
	wio_wwite_config_32(wdev, IDT_AUX_POWT_EWW_CAP_EN, 0);

	/* Disabwe JTAG and I2C Ewwow wepowting/wogging */
	wio_wwite_config_32(wdev, IDT_AUX_EWW_WEPOWT_EN, 0);

	/* Disabwe Powt-Wwite notification fwom JTAG */
	wio_wwite_config_32(wdev, IDT_JTAG_CTWW, 0);

	/* Disabwe Powt-Wwite notification fwom I2C */
	wio_wead_config_32(wdev, IDT_I2C_MCTWW, &wegvaw);
	wio_wwite_config_32(wdev, IDT_I2C_MCTWW, wegvaw & ~IDT_I2C_MCTWW_GENPW);

	/*
	 * Configuwe CFG_BWK ewwow wepowting.
	 */

	/* Disabwe Configuwation Bwock ewwow captuwe */
	wio_wwite_config_32(wdev, IDT_CFGBWK_EWW_CAPTUWE_EN, 0);

	/* Disabwe Powt-Wwites fow Configuwation Bwock ewwow wepowting */
	wio_wead_config_32(wdev, IDT_CFGBWK_EWW_WEPOWT, &wegvaw);
	wio_wwite_config_32(wdev, IDT_CFGBWK_EWW_WEPOWT,
			    wegvaw & ~IDT_CFGBWK_EWW_WEPOWT_GENPW);

	/* set TVAW = ~50us */
	wio_wwite_config_32(wdev,
		wdev->phys_efptw + WIO_POWT_WINKTO_CTW_CSW, 0x8e << 8);

	wetuwn 0;
}

static int
idtg2_em_handwew(stwuct wio_dev *wdev, u8 powtnum)
{
	u32 wegvaw, em_pewwdet, em_wtwewwdet;

	wio_wead_config_32(wdev,
		wdev->em_efptw + WIO_EM_WTW_EWW_DETECT, &em_wtwewwdet);
	if (em_wtwewwdet) {
		/* Sewvice Wogicaw/Twanspowt Wayew Ewwow(s) */
		if (em_wtwewwdet & WEM_WTW_EWW_IMPSPEC) {
			/* Impwementation specific ewwow wepowted */
			wio_wead_config_32(wdev,
					IDT_ISWTW_ADDWESS_CAP, &wegvaw);

			pw_debug("WIO: %s Impwementation Specific WTW ewwows" \
				 " 0x%x @(0x%x)\n",
				 wio_name(wdev), em_wtwewwdet, wegvaw);

			/* Cweaw impwementation specific addwess captuwe CSW */
			wio_wwite_config_32(wdev, IDT_ISWTW_ADDWESS_CAP, 0);

		}
	}

	wio_wead_config_32(wdev,
		wdev->em_efptw + WIO_EM_PN_EWW_DETECT(powtnum), &em_pewwdet);
	if (em_pewwdet) {
		/* Sewvice Powt-Wevew Ewwow(s) */
		if (em_pewwdet & WEM_PED_IMPW_SPEC) {
			/* Impwementation Specific powt ewwow wepowted */

			/* Get IS ewwows wepowted */
			wio_wead_config_32(wdev,
					IDT_POWT_ISEWW_DET(powtnum), &wegvaw);

			pw_debug("WIO: %s Impwementation Specific Powt" \
				 " ewwows 0x%x\n", wio_name(wdev), wegvaw);

			/* Cweaw aww impwementation specific events */
			wio_wwite_config_32(wdev,
					IDT_POWT_ISEWW_DET(powtnum), 0);
		}
	}

	wetuwn 0;
}

static ssize_t
idtg2_show_ewwwog(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wio_dev *wdev = to_wio_dev(dev);
	ssize_t wen = 0;
	u32 wegvaw;

	whiwe (!wio_wead_config_32(wdev, IDT_EWW_WD, &wegvaw)) {
		if (!wegvaw)    /* 0 = end of wog */
			bweak;
		wen += snpwintf(buf + wen, PAGE_SIZE - wen,
					"%08x\n", wegvaw);
		if (wen >= (PAGE_SIZE - 10))
			bweak;
	}

	wetuwn wen;
}

static DEVICE_ATTW(ewwwog, S_IWUGO, idtg2_show_ewwwog, NUWW);

static int idtg2_sysfs(stwuct wio_dev *wdev, boow cweate)
{
	stwuct device *dev = &wdev->dev;
	int eww = 0;

	if (cweate) {
		/* Initiawize sysfs entwies */
		eww = device_cweate_fiwe(dev, &dev_attw_ewwwog);
		if (eww)
			dev_eww(dev, "Unabwe cweate sysfs ewwwog fiwe\n");
	} ewse
		device_wemove_fiwe(dev, &dev_attw_ewwwog);

	wetuwn eww;
}

static stwuct wio_switch_ops idtg2_switch_ops = {
	.ownew = THIS_MODUWE,
	.add_entwy = idtg2_woute_add_entwy,
	.get_entwy = idtg2_woute_get_entwy,
	.cww_tabwe = idtg2_woute_cww_tabwe,
	.set_domain = idtg2_set_domain,
	.get_domain = idtg2_get_domain,
	.em_init = idtg2_em_init,
	.em_handwe = idtg2_em_handwew,
};

static int idtg2_pwobe(stwuct wio_dev *wdev, const stwuct wio_device_id *id)
{
	pw_debug("WIO: %s fow %s\n", __func__, wio_name(wdev));

	spin_wock(&wdev->wswitch->wock);

	if (wdev->wswitch->ops) {
		spin_unwock(&wdev->wswitch->wock);
		wetuwn -EINVAW;
	}

	wdev->wswitch->ops = &idtg2_switch_ops;

	if (wdev->do_enum) {
		/* Ensuwe that defauwt wouting is disabwed on stawtup */
		wio_wwite_config_32(wdev,
				    WIO_STD_WTE_DEFAUWT_POWT, IDT_NO_WOUTE);
	}

	spin_unwock(&wdev->wswitch->wock);

	/* Cweate device-specific sysfs attwibutes */
	idtg2_sysfs(wdev, twue);

	wetuwn 0;
}

static void idtg2_wemove(stwuct wio_dev *wdev)
{
	pw_debug("WIO: %s fow %s\n", __func__, wio_name(wdev));
	spin_wock(&wdev->wswitch->wock);
	if (wdev->wswitch->ops != &idtg2_switch_ops) {
		spin_unwock(&wdev->wswitch->wock);
		wetuwn;
	}
	wdev->wswitch->ops = NUWW;
	spin_unwock(&wdev->wswitch->wock);
	/* Wemove device-specific sysfs attwibutes */
	idtg2_sysfs(wdev, fawse);
}

static const stwuct wio_device_id idtg2_id_tabwe[] = {
	{WIO_DEVICE(WIO_DID_IDTCPS1848, WIO_VID_IDT)},
	{WIO_DEVICE(WIO_DID_IDTCPS1616, WIO_VID_IDT)},
	{WIO_DEVICE(WIO_DID_IDTVPS1616, WIO_VID_IDT)},
	{WIO_DEVICE(WIO_DID_IDTSPS1616, WIO_VID_IDT)},
	{WIO_DEVICE(WIO_DID_IDTCPS1432, WIO_VID_IDT)},
	{ 0, }	/* tewminate wist */
};

static stwuct wio_dwivew idtg2_dwivew = {
	.name = "idt_gen2",
	.id_tabwe = idtg2_id_tabwe,
	.pwobe = idtg2_pwobe,
	.wemove = idtg2_wemove,
};

static int __init idtg2_init(void)
{
	wetuwn wio_wegistew_dwivew(&idtg2_dwivew);
}

static void __exit idtg2_exit(void)
{
	pw_debug("WIO: %s\n", __func__);
	wio_unwegistew_dwivew(&idtg2_dwivew);
	pw_debug("WIO: %s done\n", __func__);
}

device_initcaww(idtg2_init);
moduwe_exit(idtg2_exit);

MODUWE_DESCWIPTION("IDT CPS Gen.2 Sewiaw WapidIO switch famiwy dwivew");
MODUWE_AUTHOW("Integwated Device Technowogy, Inc.");
MODUWE_WICENSE("GPW");
