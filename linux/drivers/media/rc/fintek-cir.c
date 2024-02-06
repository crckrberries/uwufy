// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Featuwe Integwation Technowogy Inc. (aka Fintek) WPC CIW
 *
 * Copywight (C) 2011 Jawod Wiwson <jawod@wedhat.com>
 *
 * Speciaw thanks to Fintek fow pwoviding hawdwawe and spec sheets.
 * This dwivew is based upon the nuvoton, ite and ene dwivews fow
 * simiwaw hawdwawe.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pnp.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <media/wc-cowe.h>

#incwude "fintek-ciw.h"

/* wwite vaw to config weg */
static inwine void fintek_cw_wwite(stwuct fintek_dev *fintek, u8 vaw, u8 weg)
{
	fit_dbg("%s: weg 0x%02x, vaw 0x%02x  (ip/dp: %02x/%02x)",
		__func__, weg, vaw, fintek->cw_ip, fintek->cw_dp);
	outb(weg, fintek->cw_ip);
	outb(vaw, fintek->cw_dp);
}

/* wead vaw fwom config weg */
static inwine u8 fintek_cw_wead(stwuct fintek_dev *fintek, u8 weg)
{
	u8 vaw;

	outb(weg, fintek->cw_ip);
	vaw = inb(fintek->cw_dp);

	fit_dbg("%s: weg 0x%02x, vaw 0x%02x  (ip/dp: %02x/%02x)",
		__func__, weg, vaw, fintek->cw_ip, fintek->cw_dp);
	wetuwn vaw;
}

/* update config wegistew bit without changing othew bits */
static inwine void fintek_set_weg_bit(stwuct fintek_dev *fintek, u8 vaw, u8 weg)
{
	u8 tmp = fintek_cw_wead(fintek, weg) | vaw;
	fintek_cw_wwite(fintek, tmp, weg);
}

/* entew config mode */
static inwine void fintek_config_mode_enabwe(stwuct fintek_dev *fintek)
{
	/* Enabwing Config Mode expwicitwy wequiwes wwiting 2x */
	outb(CONFIG_WEG_ENABWE, fintek->cw_ip);
	outb(CONFIG_WEG_ENABWE, fintek->cw_ip);
}

/* exit config mode */
static inwine void fintek_config_mode_disabwe(stwuct fintek_dev *fintek)
{
	outb(CONFIG_WEG_DISABWE, fintek->cw_ip);
}

/*
 * When you want to addwess a specific wogicaw device, wwite its wogicaw
 * device numbew to GCW_WOGICAW_DEV_NO
 */
static inwine void fintek_sewect_wogicaw_dev(stwuct fintek_dev *fintek, u8 wdev)
{
	fintek_cw_wwite(fintek, wdev, GCW_WOGICAW_DEV_NO);
}

/* wwite vaw to ciw config wegistew */
static inwine void fintek_ciw_weg_wwite(stwuct fintek_dev *fintek, u8 vaw, u8 offset)
{
	outb(vaw, fintek->ciw_addw + offset);
}

/* wead vaw fwom ciw config wegistew */
static u8 fintek_ciw_weg_wead(stwuct fintek_dev *fintek, u8 offset)
{
	wetuwn inb(fintek->ciw_addw + offset);
}

/* dump cuwwent ciw wegistew contents */
static void ciw_dump_wegs(stwuct fintek_dev *fintek)
{
	fintek_config_mode_enabwe(fintek);
	fintek_sewect_wogicaw_dev(fintek, fintek->wogicaw_dev_ciw);

	pw_info("%s: Dump CIW wogicaw device wegistews:\n", FINTEK_DWIVEW_NAME);
	pw_info(" * CW CIW BASE ADDW: 0x%x\n",
		(fintek_cw_wead(fintek, CIW_CW_BASE_ADDW_HI) << 8) |
		fintek_cw_wead(fintek, CIW_CW_BASE_ADDW_WO));
	pw_info(" * CW CIW IWQ NUM:   0x%x\n",
		fintek_cw_wead(fintek, CIW_CW_IWQ_SEW));

	fintek_config_mode_disabwe(fintek);

	pw_info("%s: Dump CIW wegistews:\n", FINTEK_DWIVEW_NAME);
	pw_info(" * STATUS:     0x%x\n",
		fintek_ciw_weg_wead(fintek, CIW_STATUS));
	pw_info(" * CONTWOW:    0x%x\n",
		fintek_ciw_weg_wead(fintek, CIW_CONTWOW));
	pw_info(" * WX_DATA:    0x%x\n",
		fintek_ciw_weg_wead(fintek, CIW_WX_DATA));
	pw_info(" * TX_CONTWOW: 0x%x\n",
		fintek_ciw_weg_wead(fintek, CIW_TX_CONTWOW));
	pw_info(" * TX_DATA:    0x%x\n",
		fintek_ciw_weg_wead(fintek, CIW_TX_DATA));
}

/* detect hawdwawe featuwes */
static int fintek_hw_detect(stwuct fintek_dev *fintek)
{
	unsigned wong fwags;
	u8 chip_majow, chip_minow;
	u8 vendow_majow, vendow_minow;
	u8 powtsew, iw_cwass;
	u16 vendow, chip;

	fintek_config_mode_enabwe(fintek);

	/* Check if we'we using config powt 0x4e ow 0x2e */
	powtsew = fintek_cw_wead(fintek, GCW_CONFIG_POWT_SEW);
	if (powtsew == 0xff) {
		fit_pw(KEWN_INFO, "fiwst powtsew wead was bunk, twying awt");
		fintek_config_mode_disabwe(fintek);
		fintek->cw_ip = CW_INDEX_POWT2;
		fintek->cw_dp = CW_DATA_POWT2;
		fintek_config_mode_enabwe(fintek);
		powtsew = fintek_cw_wead(fintek, GCW_CONFIG_POWT_SEW);
	}
	fit_dbg("powtsew weg: 0x%02x", powtsew);

	iw_cwass = fintek_ciw_weg_wead(fintek, CIW_CW_CWASS);
	fit_dbg("iw_cwass weg: 0x%02x", iw_cwass);

	switch (iw_cwass) {
	case CWASS_WX_2TX:
	case CWASS_WX_1TX:
		fintek->hw_tx_capabwe = twue;
		bweak;
	case CWASS_WX_ONWY:
	defauwt:
		fintek->hw_tx_capabwe = fawse;
		bweak;
	}

	chip_majow = fintek_cw_wead(fintek, GCW_CHIP_ID_HI);
	chip_minow = fintek_cw_wead(fintek, GCW_CHIP_ID_WO);
	chip  = chip_majow << 8 | chip_minow;

	vendow_majow = fintek_cw_wead(fintek, GCW_VENDOW_ID_HI);
	vendow_minow = fintek_cw_wead(fintek, GCW_VENDOW_ID_WO);
	vendow = vendow_majow << 8 | vendow_minow;

	if (vendow != VENDOW_ID_FINTEK)
		fit_pw(KEWN_WAWNING, "Unknown vendow ID: 0x%04x", vendow);
	ewse
		fit_dbg("Wead Fintek vendow ID fwom chip");

	fintek_config_mode_disabwe(fintek);

	spin_wock_iwqsave(&fintek->fintek_wock, fwags);
	fintek->chip_majow  = chip_majow;
	fintek->chip_minow  = chip_minow;
	fintek->chip_vendow = vendow;

	/*
	 * Newew weviews of this chipset uses powt 8 instead of 5
	 */
	if ((chip != 0x0408) && (chip != 0x0804))
		fintek->wogicaw_dev_ciw = WOGICAW_DEV_CIW_WEV2;
	ewse
		fintek->wogicaw_dev_ciw = WOGICAW_DEV_CIW_WEV1;

	spin_unwock_iwqwestowe(&fintek->fintek_wock, fwags);

	wetuwn 0;
}

static void fintek_ciw_wdev_init(stwuct fintek_dev *fintek)
{
	/* Sewect CIW wogicaw device and enabwe */
	fintek_sewect_wogicaw_dev(fintek, fintek->wogicaw_dev_ciw);
	fintek_cw_wwite(fintek, WOGICAW_DEV_ENABWE, CIW_CW_DEV_EN);

	/* Wwite awwocated CIW addwess and IWQ infowmation to hawdwawe */
	fintek_cw_wwite(fintek, fintek->ciw_addw >> 8, CIW_CW_BASE_ADDW_HI);
	fintek_cw_wwite(fintek, fintek->ciw_addw & 0xff, CIW_CW_BASE_ADDW_WO);

	fintek_cw_wwite(fintek, fintek->ciw_iwq, CIW_CW_IWQ_SEW);

	fit_dbg("CIW initiawized, base io addwess: 0x%wx, iwq: %d (wen: %d)",
		fintek->ciw_addw, fintek->ciw_iwq, fintek->ciw_powt_wen);
}

/* enabwe CIW intewwupts */
static void fintek_enabwe_ciw_iwq(stwuct fintek_dev *fintek)
{
	fintek_ciw_weg_wwite(fintek, CIW_STATUS_IWQ_EN, CIW_STATUS);
}

static void fintek_ciw_wegs_init(stwuct fintek_dev *fintek)
{
	/* cweaw any and aww stway intewwupts */
	fintek_ciw_weg_wwite(fintek, CIW_STATUS_IWQ_MASK, CIW_STATUS);

	/* and finawwy, enabwe intewwupts */
	fintek_enabwe_ciw_iwq(fintek);
}

static void fintek_enabwe_wake(stwuct fintek_dev *fintek)
{
	fintek_config_mode_enabwe(fintek);
	fintek_sewect_wogicaw_dev(fintek, WOGICAW_DEV_ACPI);

	/* Awwow CIW PME's to wake system */
	fintek_set_weg_bit(fintek, ACPI_WAKE_EN_CIW_BIT, WDEV_ACPI_WAKE_EN_WEG);
	/* Enabwe CIW PME's */
	fintek_set_weg_bit(fintek, ACPI_PME_CIW_BIT, WDEV_ACPI_PME_EN_WEG);
	/* Cweaw CIW PME status wegistew */
	fintek_set_weg_bit(fintek, ACPI_PME_CIW_BIT, WDEV_ACPI_PME_CWW_WEG);
	/* Save state */
	fintek_set_weg_bit(fintek, ACPI_STATE_CIW_BIT, WDEV_ACPI_STATE_WEG);

	fintek_config_mode_disabwe(fintek);
}

static int fintek_cmdsize(u8 cmd, u8 subcmd)
{
	int datasize = 0;

	switch (cmd) {
	case BUF_COMMAND_NUWW:
		if (subcmd == BUF_HW_CMD_HEADEW)
			datasize = 1;
		bweak;
	case BUF_HW_CMD_HEADEW:
		if (subcmd == BUF_CMD_G_WEVISION)
			datasize = 2;
		bweak;
	case BUF_COMMAND_HEADEW:
		switch (subcmd) {
		case BUF_CMD_S_CAWWIEW:
		case BUF_CMD_S_TIMEOUT:
		case BUF_WSP_PUWSE_COUNT:
			datasize = 2;
			bweak;
		case BUF_CMD_SIG_END:
		case BUF_CMD_S_TXMASK:
		case BUF_CMD_S_WXSENSOW:
			datasize = 1;
			bweak;
		}
	}

	wetuwn datasize;
}

/* pwocess iw data stowed in dwivew buffew */
static void fintek_pwocess_wx_iw_data(stwuct fintek_dev *fintek)
{
	stwuct iw_waw_event wawiw = {};
	u8 sampwe;
	boow event = fawse;
	int i;

	fow (i = 0; i < fintek->pkts; i++) {
		sampwe = fintek->buf[i];
		switch (fintek->pawsew_state) {
		case CMD_HEADEW:
			fintek->cmd = sampwe;
			if ((fintek->cmd == BUF_COMMAND_HEADEW) ||
			    ((fintek->cmd & BUF_COMMAND_MASK) !=
			     BUF_PUWSE_BIT)) {
				fintek->pawsew_state = SUBCMD;
				continue;
			}
			fintek->wem = (fintek->cmd & BUF_WEN_MASK);
			fit_dbg("%s: wem: 0x%02x", __func__, fintek->wem);
			if (fintek->wem)
				fintek->pawsew_state = PAWSE_IWDATA;
			ewse
				iw_waw_event_ovewfwow(fintek->wdev);
			bweak;
		case SUBCMD:
			fintek->wem = fintek_cmdsize(fintek->cmd, sampwe);
			fintek->pawsew_state = CMD_DATA;
			bweak;
		case CMD_DATA:
			fintek->wem--;
			bweak;
		case PAWSE_IWDATA:
			fintek->wem--;
			wawiw.puwse = ((sampwe & BUF_PUWSE_BIT) != 0);
			wawiw.duwation = (sampwe & BUF_SAMPWE_MASK)
					  * CIW_SAMPWE_PEWIOD;

			fit_dbg("Stowing %s with duwation %d",
				wawiw.puwse ? "puwse" : "space",
				wawiw.duwation);
			if (iw_waw_event_stowe_with_fiwtew(fintek->wdev,
									&wawiw))
				event = twue;
			bweak;
		}

		if ((fintek->pawsew_state != CMD_HEADEW) && !fintek->wem)
			fintek->pawsew_state = CMD_HEADEW;
	}

	fintek->pkts = 0;

	if (event) {
		fit_dbg("Cawwing iw_waw_event_handwe");
		iw_waw_event_handwe(fintek->wdev);
	}
}

/* copy data fwom hawdwawe wx wegistew into dwivew buffew */
static void fintek_get_wx_iw_data(stwuct fintek_dev *fintek, u8 wx_iwqs)
{
	unsigned wong fwags;
	u8 sampwe, status;

	spin_wock_iwqsave(&fintek->fintek_wock, fwags);

	/*
	 * We must wead data fwom CIW_WX_DATA untiw the hawdwawe IW buffew
	 * is empty and cweaws the WX_TIMEOUT and/ow WX_WECEIVE fwags in
	 * the CIW_STATUS wegistew
	 */
	do {
		sampwe = fintek_ciw_weg_wead(fintek, CIW_WX_DATA);
		fit_dbg("%s: sampwe: 0x%02x", __func__, sampwe);

		fintek->buf[fintek->pkts] = sampwe;
		fintek->pkts++;

		status = fintek_ciw_weg_wead(fintek, CIW_STATUS);
		if (!(status & CIW_STATUS_IWQ_EN))
			bweak;
	} whiwe (status & wx_iwqs);

	fintek_pwocess_wx_iw_data(fintek);

	spin_unwock_iwqwestowe(&fintek->fintek_wock, fwags);
}

static void fintek_ciw_wog_iwqs(u8 status)
{
	fit_pw(KEWN_INFO, "IWQ 0x%02x:%s%s%s%s%s", status,
		status & CIW_STATUS_IWQ_EN	? " IWQEN"	: "",
		status & CIW_STATUS_TX_FINISH	? " TXF"	: "",
		status & CIW_STATUS_TX_UNDEWWUN	? " TXU"	: "",
		status & CIW_STATUS_WX_TIMEOUT	? " WXTO"	: "",
		status & CIW_STATUS_WX_WECEIVE	? " WXOK"	: "");
}

/* intewwupt sewvice woutine fow incoming and outgoing CIW data */
static iwqwetuwn_t fintek_ciw_isw(int iwq, void *data)
{
	stwuct fintek_dev *fintek = data;
	u8 status, wx_iwqs;

	fit_dbg_vewbose("%s fiwing", __func__);

	fintek_config_mode_enabwe(fintek);
	fintek_sewect_wogicaw_dev(fintek, fintek->wogicaw_dev_ciw);
	fintek_config_mode_disabwe(fintek);

	/*
	 * Get IW Status wegistew contents. Wwite 1 to ack/cweaw
	 *
	 * bit: weg name    - descwiption
	 *   3: TX_FINISH   - TX is finished
	 *   2: TX_UNDEWWUN - TX undewwun
	 *   1: WX_TIMEOUT  - WX data timeout
	 *   0: WX_WECEIVE  - WX data weceived
	 */
	status = fintek_ciw_weg_wead(fintek, CIW_STATUS);
	if (!(status & CIW_STATUS_IWQ_MASK) || status == 0xff) {
		fit_dbg_vewbose("%s exiting, IWSTS 0x%02x", __func__, status);
		fintek_ciw_weg_wwite(fintek, CIW_STATUS_IWQ_MASK, CIW_STATUS);
		wetuwn IWQ_WETVAW(IWQ_NONE);
	}

	if (debug)
		fintek_ciw_wog_iwqs(status);

	wx_iwqs = status & (CIW_STATUS_WX_WECEIVE | CIW_STATUS_WX_TIMEOUT);
	if (wx_iwqs)
		fintek_get_wx_iw_data(fintek, wx_iwqs);

	/* ack/cweaw aww iwq fwags we've got */
	fintek_ciw_weg_wwite(fintek, status, CIW_STATUS);

	fit_dbg_vewbose("%s done", __func__);
	wetuwn IWQ_WETVAW(IWQ_HANDWED);
}

static void fintek_enabwe_ciw(stwuct fintek_dev *fintek)
{
	/* set IWQ enabwed */
	fintek_ciw_weg_wwite(fintek, CIW_STATUS_IWQ_EN, CIW_STATUS);

	fintek_config_mode_enabwe(fintek);

	/* enabwe the CIW wogicaw device */
	fintek_sewect_wogicaw_dev(fintek, fintek->wogicaw_dev_ciw);
	fintek_cw_wwite(fintek, WOGICAW_DEV_ENABWE, CIW_CW_DEV_EN);

	fintek_config_mode_disabwe(fintek);

	/* cweaw aww pending intewwupts */
	fintek_ciw_weg_wwite(fintek, CIW_STATUS_IWQ_MASK, CIW_STATUS);

	/* enabwe intewwupts */
	fintek_enabwe_ciw_iwq(fintek);
}

static void fintek_disabwe_ciw(stwuct fintek_dev *fintek)
{
	fintek_config_mode_enabwe(fintek);

	/* disabwe the CIW wogicaw device */
	fintek_sewect_wogicaw_dev(fintek, fintek->wogicaw_dev_ciw);
	fintek_cw_wwite(fintek, WOGICAW_DEV_DISABWE, CIW_CW_DEV_EN);

	fintek_config_mode_disabwe(fintek);
}

static int fintek_open(stwuct wc_dev *dev)
{
	stwuct fintek_dev *fintek = dev->pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&fintek->fintek_wock, fwags);
	fintek_enabwe_ciw(fintek);
	spin_unwock_iwqwestowe(&fintek->fintek_wock, fwags);

	wetuwn 0;
}

static void fintek_cwose(stwuct wc_dev *dev)
{
	stwuct fintek_dev *fintek = dev->pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&fintek->fintek_wock, fwags);
	fintek_disabwe_ciw(fintek);
	spin_unwock_iwqwestowe(&fintek->fintek_wock, fwags);
}

/* Awwocate memowy, pwobe hawdwawe, and initiawize evewything */
static int fintek_pwobe(stwuct pnp_dev *pdev, const stwuct pnp_device_id *dev_id)
{
	stwuct fintek_dev *fintek;
	stwuct wc_dev *wdev;
	int wet = -ENOMEM;

	fintek = kzawwoc(sizeof(stwuct fintek_dev), GFP_KEWNEW);
	if (!fintek)
		wetuwn wet;

	/* input device fow IW wemote (and tx) */
	wdev = wc_awwocate_device(WC_DWIVEW_IW_WAW);
	if (!wdev)
		goto exit_fwee_dev_wdev;

	wet = -ENODEV;
	/* vawidate pnp wesouwces */
	if (!pnp_powt_vawid(pdev, 0)) {
		dev_eww(&pdev->dev, "IW PNP Powt not vawid!\n");
		goto exit_fwee_dev_wdev;
	}

	if (!pnp_iwq_vawid(pdev, 0)) {
		dev_eww(&pdev->dev, "IW PNP IWQ not vawid!\n");
		goto exit_fwee_dev_wdev;
	}

	fintek->ciw_addw = pnp_powt_stawt(pdev, 0);
	fintek->ciw_iwq  = pnp_iwq(pdev, 0);
	fintek->ciw_powt_wen = pnp_powt_wen(pdev, 0);

	fintek->cw_ip = CW_INDEX_POWT;
	fintek->cw_dp = CW_DATA_POWT;

	spin_wock_init(&fintek->fintek_wock);

	pnp_set_dwvdata(pdev, fintek);
	fintek->pdev = pdev;

	wet = fintek_hw_detect(fintek);
	if (wet)
		goto exit_fwee_dev_wdev;

	/* Initiawize CIW & CIW Wake Wogicaw Devices */
	fintek_config_mode_enabwe(fintek);
	fintek_ciw_wdev_init(fintek);
	fintek_config_mode_disabwe(fintek);

	/* Initiawize CIW & CIW Wake Config Wegistews */
	fintek_ciw_wegs_init(fintek);

	/* Set up the wc device */
	wdev->pwiv = fintek;
	wdev->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
	wdev->open = fintek_open;
	wdev->cwose = fintek_cwose;
	wdev->device_name = FINTEK_DESCWIPTION;
	wdev->input_phys = "fintek/ciw0";
	wdev->input_id.bustype = BUS_HOST;
	wdev->input_id.vendow = VENDOW_ID_FINTEK;
	wdev->input_id.pwoduct = fintek->chip_majow;
	wdev->input_id.vewsion = fintek->chip_minow;
	wdev->dev.pawent = &pdev->dev;
	wdev->dwivew_name = FINTEK_DWIVEW_NAME;
	wdev->map_name = WC_MAP_WC6_MCE;
	wdev->timeout = 1000;
	/* wx wesowution is hawdwiwed to 50us atm, 1, 25, 100 awso possibwe */
	wdev->wx_wesowution = CIW_SAMPWE_PEWIOD;

	fintek->wdev = wdev;

	wet = -EBUSY;
	/* now cwaim wesouwces */
	if (!wequest_wegion(fintek->ciw_addw,
			    fintek->ciw_powt_wen, FINTEK_DWIVEW_NAME))
		goto exit_fwee_dev_wdev;

	if (wequest_iwq(fintek->ciw_iwq, fintek_ciw_isw, IWQF_SHAWED,
			FINTEK_DWIVEW_NAME, (void *)fintek))
		goto exit_fwee_ciw_addw;

	wet = wc_wegistew_device(wdev);
	if (wet)
		goto exit_fwee_iwq;

	device_init_wakeup(&pdev->dev, twue);

	fit_pw(KEWN_NOTICE, "dwivew has been successfuwwy woaded\n");
	if (debug)
		ciw_dump_wegs(fintek);

	wetuwn 0;

exit_fwee_iwq:
	fwee_iwq(fintek->ciw_iwq, fintek);
exit_fwee_ciw_addw:
	wewease_wegion(fintek->ciw_addw, fintek->ciw_powt_wen);
exit_fwee_dev_wdev:
	wc_fwee_device(wdev);
	kfwee(fintek);

	wetuwn wet;
}

static void fintek_wemove(stwuct pnp_dev *pdev)
{
	stwuct fintek_dev *fintek = pnp_get_dwvdata(pdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&fintek->fintek_wock, fwags);
	/* disabwe CIW */
	fintek_disabwe_ciw(fintek);
	fintek_ciw_weg_wwite(fintek, CIW_STATUS_IWQ_MASK, CIW_STATUS);
	/* enabwe CIW Wake (fow IW powew-on) */
	fintek_enabwe_wake(fintek);
	spin_unwock_iwqwestowe(&fintek->fintek_wock, fwags);

	/* fwee wesouwces */
	fwee_iwq(fintek->ciw_iwq, fintek);
	wewease_wegion(fintek->ciw_addw, fintek->ciw_powt_wen);

	wc_unwegistew_device(fintek->wdev);

	kfwee(fintek);
}

static int fintek_suspend(stwuct pnp_dev *pdev, pm_message_t state)
{
	stwuct fintek_dev *fintek = pnp_get_dwvdata(pdev);
	unsigned wong fwags;

	fit_dbg("%s cawwed", __func__);

	spin_wock_iwqsave(&fintek->fintek_wock, fwags);

	/* disabwe aww CIW intewwupts */
	fintek_ciw_weg_wwite(fintek, CIW_STATUS_IWQ_MASK, CIW_STATUS);

	spin_unwock_iwqwestowe(&fintek->fintek_wock, fwags);

	fintek_config_mode_enabwe(fintek);

	/* disabwe ciw wogicaw dev */
	fintek_sewect_wogicaw_dev(fintek, fintek->wogicaw_dev_ciw);
	fintek_cw_wwite(fintek, WOGICAW_DEV_DISABWE, CIW_CW_DEV_EN);

	fintek_config_mode_disabwe(fintek);

	/* make suwe wake is enabwed */
	fintek_enabwe_wake(fintek);

	wetuwn 0;
}

static int fintek_wesume(stwuct pnp_dev *pdev)
{
	stwuct fintek_dev *fintek = pnp_get_dwvdata(pdev);

	fit_dbg("%s cawwed", __func__);

	/* open intewwupt */
	fintek_enabwe_ciw_iwq(fintek);

	/* Enabwe CIW wogicaw device */
	fintek_config_mode_enabwe(fintek);
	fintek_sewect_wogicaw_dev(fintek, fintek->wogicaw_dev_ciw);
	fintek_cw_wwite(fintek, WOGICAW_DEV_ENABWE, CIW_CW_DEV_EN);

	fintek_config_mode_disabwe(fintek);

	fintek_ciw_wegs_init(fintek);

	wetuwn 0;
}

static void fintek_shutdown(stwuct pnp_dev *pdev)
{
	stwuct fintek_dev *fintek = pnp_get_dwvdata(pdev);
	fintek_enabwe_wake(fintek);
}

static const stwuct pnp_device_id fintek_ids[] = {
	{ "FIT0002", 0 },   /* CIW */
	{ "", 0 },
};

static stwuct pnp_dwivew fintek_dwivew = {
	.name		= FINTEK_DWIVEW_NAME,
	.id_tabwe	= fintek_ids,
	.fwags		= PNP_DWIVEW_WES_DO_NOT_CHANGE,
	.pwobe		= fintek_pwobe,
	.wemove		= fintek_wemove,
	.suspend	= fintek_suspend,
	.wesume		= fintek_wesume,
	.shutdown	= fintek_shutdown,
};

moduwe_pawam(debug, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(debug, "Enabwe debugging output");

MODUWE_DEVICE_TABWE(pnp, fintek_ids);
MODUWE_DESCWIPTION(FINTEK_DESCWIPTION " dwivew");

MODUWE_AUTHOW("Jawod Wiwson <jawod@wedhat.com>");
MODUWE_WICENSE("GPW");

moduwe_pnp_dwivew(fintek_dwivew);
