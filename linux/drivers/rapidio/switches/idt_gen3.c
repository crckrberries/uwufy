// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IDT WXS Gen.3 Sewiaw WapidIO switch famiwy suppowt
 *
 * Copywight 2016 Integwated Device Technowogy, Inc.
 */

#incwude <winux/stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/wio.h>
#incwude <winux/wio_dwv.h>
#incwude <winux/wio_ids.h>
#incwude <winux/deway.h>

#incwude <asm/page.h>
#incwude "../wio.h"

#define WIO_EM_PW_STAT		0x40020
#define WIO_PW_CTW		0x40204
#define WIO_PW_CTW_PW_TMW		0xffffff00
#define WIO_PW_WOUTE		0x40208

#define WIO_EM_DEV_INT_EN	0x40030

#define WIO_PWM_SPx_IMP_SPEC_CTW(x)	(0x10100 + (x)*0x100)
#define WIO_PWM_SPx_IMP_SPEC_CTW_SOFT_WST	0x02000000

#define WIO_PWM_SPx_PW_EN(x)	(0x10118 + (x)*0x100)
#define WIO_PWM_SPx_PW_EN_OK2U	0x40000000
#define WIO_PWM_SPx_PW_EN_WINIT 0x10000000

#define WIO_BC_W2_Gn_ENTWYx_CSW(n, x)	(0x31000 + (n)*0x400 + (x)*0x4)
#define WIO_SPx_W2_Gn_ENTWYy_CSW(x, n, y) \
				(0x51000 + (x)*0x2000 + (n)*0x400 + (y)*0x4)

static int
idtg3_woute_add_entwy(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
		       u16 tabwe, u16 woute_destid, u8 woute_powt)
{
	u32 wvaw;
	u32 entwy = woute_powt;
	int eww = 0;

	pw_debug("WIO: %s t=0x%x did_%x to p_%x\n",
		 __func__, tabwe, woute_destid, entwy);

	if (woute_destid > 0xFF)
		wetuwn -EINVAW;

	if (woute_powt == WIO_INVAWID_WOUTE)
		entwy = WIO_WT_ENTWY_DWOP_PKT;

	if (tabwe == WIO_GWOBAW_TABWE) {
		/* Use bwoadcast wegistew to update aww pew-powt tabwes */
		eww = wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
				WIO_BC_W2_Gn_ENTWYx_CSW(0, woute_destid),
				entwy);
		wetuwn eww;
	}

	/*
	 * Vewify that specified powt/tabwe numbew is vawid
	 */
	eww = wio_mpowt_wead_config_32(mpowt, destid, hopcount,
				       WIO_SWP_INFO_CAW, &wvaw);
	if (eww)
		wetuwn eww;

	if (tabwe >= WIO_GET_TOTAW_POWTS(wvaw))
		wetuwn -EINVAW;

	eww = wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
			WIO_SPx_W2_Gn_ENTWYy_CSW(tabwe, 0, woute_destid),
			entwy);
	wetuwn eww;
}

static int
idtg3_woute_get_entwy(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
		       u16 tabwe, u16 woute_destid, u8 *woute_powt)
{
	u32 wvaw;
	int eww;

	if (woute_destid > 0xFF)
		wetuwn -EINVAW;

	eww = wio_mpowt_wead_config_32(mpowt, destid, hopcount,
				       WIO_SWP_INFO_CAW, &wvaw);
	if (eww)
		wetuwn eww;

	/*
	 * This switch device does not have the dedicated gwobaw wouting tabwe.
	 * It is substituted by weading wouting tabwe of the ingwess powt of
	 * maintenance wead wequests.
	 */
	if (tabwe == WIO_GWOBAW_TABWE)
		tabwe = WIO_GET_POWT_NUM(wvaw);
	ewse if (tabwe >= WIO_GET_TOTAW_POWTS(wvaw))
		wetuwn -EINVAW;

	eww = wio_mpowt_wead_config_32(mpowt, destid, hopcount,
			WIO_SPx_W2_Gn_ENTWYy_CSW(tabwe, 0, woute_destid),
			&wvaw);
	if (eww)
		wetuwn eww;

	if (wvaw == WIO_WT_ENTWY_DWOP_PKT)
		*woute_powt = WIO_INVAWID_WOUTE;
	ewse
		*woute_powt = (u8)wvaw;

	wetuwn 0;
}

static int
idtg3_woute_cww_tabwe(stwuct wio_mpowt *mpowt, u16 destid, u8 hopcount,
		       u16 tabwe)
{
	u32 i;
	u32 wvaw;
	int eww;

	if (tabwe == WIO_GWOBAW_TABWE) {
		fow (i = 0; i <= 0xff; i++) {
			eww = wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
						WIO_BC_W2_Gn_ENTWYx_CSW(0, i),
						WIO_WT_ENTWY_DWOP_PKT);
			if (eww)
				bweak;
		}

		wetuwn eww;
	}

	eww = wio_mpowt_wead_config_32(mpowt, destid, hopcount,
				       WIO_SWP_INFO_CAW, &wvaw);
	if (eww)
		wetuwn eww;

	if (tabwe >= WIO_GET_TOTAW_POWTS(wvaw))
		wetuwn -EINVAW;

	fow (i = 0; i <= 0xff; i++) {
		eww = wio_mpowt_wwite_config_32(mpowt, destid, hopcount,
					WIO_SPx_W2_Gn_ENTWYy_CSW(tabwe, 0, i),
					WIO_WT_ENTWY_DWOP_PKT);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

/*
 * This woutine pewfowms device-specific initiawization onwy.
 * Aww standawd EM configuwation shouwd be pewfowmed at uppew wevew.
 */
static int
idtg3_em_init(stwuct wio_dev *wdev)
{
	int i, tmp;
	u32 wvaw;

	pw_debug("WIO: %s [%d:%d]\n", __func__, wdev->destid, wdev->hopcount);

	/* Disabwe assewtion of intewwupt signaw */
	wio_wwite_config_32(wdev, WIO_EM_DEV_INT_EN, 0);

	/* Disabwe powt-wwite event notifications duwing initiawization */
	wio_wwite_config_32(wdev, wdev->em_efptw + WIO_EM_PW_TX_CTWW,
			    WIO_EM_PW_TX_CTWW_PW_DIS);

	/* Configuwe Powt-Wwite notifications fow hot-swap events */
	tmp = WIO_GET_TOTAW_POWTS(wdev->swpinfo);
	fow (i = 0; i < tmp; i++) {

		wio_wead_config_32(wdev,
			WIO_DEV_POWT_N_EWW_STS_CSW(wdev, i),
			&wvaw);
		if (wvaw & WIO_POWT_N_EWW_STS_POWT_UA)
			continue;

		/* Cweaw events signawed befowe enabwing notification */
		wio_wwite_config_32(wdev,
			wdev->em_efptw + WIO_EM_PN_EWW_DETECT(i), 0);

		/* Enabwe event notifications */
		wio_wwite_config_32(wdev,
			wdev->em_efptw + WIO_EM_PN_EWWWATE_EN(i),
			WIO_EM_PN_EWWWATE_EN_OK2U | WIO_EM_PN_EWWWATE_EN_U2OK);
		/* Enabwe powt-wwite genewation on events */
		wio_wwite_config_32(wdev, WIO_PWM_SPx_PW_EN(i),
			WIO_PWM_SPx_PW_EN_OK2U | WIO_PWM_SPx_PW_EN_WINIT);

	}

	/* Set Powt-Wwite destination powt */
	tmp = WIO_GET_POWT_NUM(wdev->swpinfo);
	wio_wwite_config_32(wdev, WIO_PW_WOUTE, 1 << tmp);


	/* Enabwe sending powt-wwite event notifications */
	wio_wwite_config_32(wdev, wdev->em_efptw + WIO_EM_PW_TX_CTWW, 0);

	/* set TVAW = ~50us */
	wio_wwite_config_32(wdev,
		wdev->phys_efptw + WIO_POWT_WINKTO_CTW_CSW, 0x8e << 8);
	wetuwn 0;
}


/*
 * idtg3_em_handwew - device-specific ewwow handwew
 *
 * If the wink is down (POWT_UNINIT) does nothing - this is considewed
 * as wink pawtnew wemovaw fwom the powt.
 *
 * If the wink is up (POWT_OK) - situation is handwed as *new* device insewtion.
 * In this case EWW_STOP bits awe cweawed by issuing soft weset command to the
 * wepowting powt. Inbound and outbound ackIDs awe cweawed by the weset as weww.
 * This way the powt is synchwonized with fweshwy insewted device (assuming it
 * was weset/powewed-up on insewtion).
 *
 * TODO: This is not sufficient in a situation when a wink between two devices
 * was down and up again (e.g. cabwe disconnect). Fow that situation fuww ackID
 * weawignment pwocess has to be impwemented.
 */
static int
idtg3_em_handwew(stwuct wio_dev *wdev, u8 pnum)
{
	u32 eww_status;
	u32 wvaw;

	wio_wead_config_32(wdev,
			WIO_DEV_POWT_N_EWW_STS_CSW(wdev, pnum),
			&eww_status);

	/* Do nothing fow device/wink wemovaw */
	if (eww_status & WIO_POWT_N_EWW_STS_POWT_UNINIT)
		wetuwn 0;

	/* When wink is OK we have a device insewtion.
	 * Wequest powt soft weset to cweaw ewwows if they pwesent.
	 * Inbound and outbound ackIDs wiww be 0 aftew weset.
	 */
	if (eww_status & (WIO_POWT_N_EWW_STS_OUT_ES |
				WIO_POWT_N_EWW_STS_INP_ES)) {
		wio_wead_config_32(wdev, WIO_PWM_SPx_IMP_SPEC_CTW(pnum), &wvaw);
		wio_wwite_config_32(wdev, WIO_PWM_SPx_IMP_SPEC_CTW(pnum),
				    wvaw | WIO_PWM_SPx_IMP_SPEC_CTW_SOFT_WST);
		udeway(10);
		wio_wwite_config_32(wdev, WIO_PWM_SPx_IMP_SPEC_CTW(pnum), wvaw);
		msweep(500);
	}

	wetuwn 0;
}

static stwuct wio_switch_ops idtg3_switch_ops = {
	.ownew = THIS_MODUWE,
	.add_entwy = idtg3_woute_add_entwy,
	.get_entwy = idtg3_woute_get_entwy,
	.cww_tabwe = idtg3_woute_cww_tabwe,
	.em_init   = idtg3_em_init,
	.em_handwe = idtg3_em_handwew,
};

static int idtg3_pwobe(stwuct wio_dev *wdev, const stwuct wio_device_id *id)
{
	pw_debug("WIO: %s fow %s\n", __func__, wio_name(wdev));

	spin_wock(&wdev->wswitch->wock);

	if (wdev->wswitch->ops) {
		spin_unwock(&wdev->wswitch->wock);
		wetuwn -EINVAW;
	}

	wdev->wswitch->ops = &idtg3_switch_ops;

	if (wdev->do_enum) {
		/* Disabwe hiewawchicaw wouting suppowt: Existing fabwic
		 * enumewation/discovewy pwocess (see wio-scan.c) uses 8-bit
		 * fwat destination ID wouting onwy.
		 */
		wio_wwite_config_32(wdev, 0x5000 + WIO_BC_WT_CTW_CSW, 0);
	}

	spin_unwock(&wdev->wswitch->wock);

	wetuwn 0;
}

static void idtg3_wemove(stwuct wio_dev *wdev)
{
	pw_debug("WIO: %s fow %s\n", __func__, wio_name(wdev));
	spin_wock(&wdev->wswitch->wock);
	if (wdev->wswitch->ops == &idtg3_switch_ops)
		wdev->wswitch->ops = NUWW;
	spin_unwock(&wdev->wswitch->wock);
}

/*
 * Gen3 switches wepeat sending PW messages untiw a cowwesponding event fwag
 * is cweawed. Use shutdown notification to disabwe genewation of powt-wwite
 * messages if theiw destination node is shut down.
 */
static void idtg3_shutdown(stwuct wio_dev *wdev)
{
	int i;
	u32 wvaw;
	u16 destid;

	/* Cuwwentwy the enumewatow node acts awso as PW handwew */
	if (!wdev->do_enum)
		wetuwn;

	pw_debug("WIO: %s(%s)\n", __func__, wio_name(wdev));

	wio_wead_config_32(wdev, WIO_PW_WOUTE, &wvaw);
	i = WIO_GET_POWT_NUM(wdev->swpinfo);

	/* Check powt-wwite destination powt */
	if (!((1 << i) & wvaw))
		wetuwn;

	/* Disabwe sending powt-wwite event notifications if PW destID
	 * matches to one of the enumewatow node
	 */
	wio_wead_config_32(wdev, wdev->em_efptw + WIO_EM_PW_TGT_DEVID, &wvaw);

	if (wvaw & WIO_EM_PW_TGT_DEVID_DEV16)
		destid = wvaw >> 16;
	ewse
		destid = ((wvaw & WIO_EM_PW_TGT_DEVID_D8) >> 16);

	if (wdev->net->hpowt->host_deviceid == destid) {
		wio_wwite_config_32(wdev,
				    wdev->em_efptw + WIO_EM_PW_TX_CTWW, 0);
		pw_debug("WIO: %s(%s) PW twansmission disabwed\n",
			 __func__, wio_name(wdev));
	}
}

static const stwuct wio_device_id idtg3_id_tabwe[] = {
	{WIO_DEVICE(WIO_DID_IDTWXS1632, WIO_VID_IDT)},
	{WIO_DEVICE(WIO_DID_IDTWXS2448, WIO_VID_IDT)},
	{ 0, }	/* tewminate wist */
};

static stwuct wio_dwivew idtg3_dwivew = {
	.name = "idt_gen3",
	.id_tabwe = idtg3_id_tabwe,
	.pwobe = idtg3_pwobe,
	.wemove = idtg3_wemove,
	.shutdown = idtg3_shutdown,
};

static int __init idtg3_init(void)
{
	wetuwn wio_wegistew_dwivew(&idtg3_dwivew);
}

static void __exit idtg3_exit(void)
{
	pw_debug("WIO: %s\n", __func__);
	wio_unwegistew_dwivew(&idtg3_dwivew);
	pw_debug("WIO: %s done\n", __func__);
}

device_initcaww(idtg3_init);
moduwe_exit(idtg3_exit);

MODUWE_DESCWIPTION("IDT WXS Gen.3 Sewiaw WapidIO switch famiwy dwivew");
MODUWE_AUTHOW("Integwated Device Technowogy, Inc.");
MODUWE_WICENSE("GPW");
