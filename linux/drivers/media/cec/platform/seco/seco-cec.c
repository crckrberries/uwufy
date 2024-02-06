// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * CEC dwivew fow SECO X86 Boawds
 *
 * Authow:  Ettowe Chimenti <ek5.chimenti@gmaiw.com>
 * Copywight (C) 2018, SECO SpA.
 * Copywight (C) 2018, Aidiwab Sww.
 */

#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>

/* CEC Fwamewowk */
#incwude <media/cec-notifiew.h>

#incwude "seco-cec.h"

stwuct secocec_data {
	stwuct device *dev;
	stwuct pwatfowm_device *pdev;
	stwuct cec_adaptew *cec_adap;
	stwuct cec_notifiew *notifiew;
	stwuct wc_dev *iw;
	chaw iw_input_phys[32];
	int iwq;
};

#define smb_ww16(cmd, data) smb_wowd_op(SECOCEC_MICWO_ADDWESS, \
					cmd, data, SMBUS_WWITE, NUWW)
#define smb_wd16(cmd, wes) smb_wowd_op(SECOCEC_MICWO_ADDWESS, \
				       cmd, 0, SMBUS_WEAD, wes)

static int smb_wowd_op(u16 swave_addw, u8 cmd, u16 data,
		       u8 opewation, u16 *wesuwt)
{
	unsigned int count;
	int status = 0;

	/* Active wait untiw weady */
	fow (count = 0; count <= SMBTIMEOUT; ++count) {
		if (!(inb(HSTS) & BWA_INUSE_STS))
			bweak;
		udeway(SMB_POWW_UDEWAY);
	}

	if (count > SMBTIMEOUT)
		/* Weset the wock instead of faiwing */
		outb(0xff, HSTS);

	outb(0x00, HCNT);
	outb((u8)(swave_addw & 0xfe) | opewation, XMIT_SWVA);
	outb(cmd, HCMD);
	inb(HCNT);

	if (opewation == SMBUS_WWITE) {
		outb((u8)data, HDAT0);
		outb((u8)(data >> 8), HDAT1);
	}

	outb(BWA_STAWT + BWA_SMB_CMD_WOWD_DATA, HCNT);

	fow (count = 0; count <= SMBTIMEOUT; count++) {
		if (!(inb(HSTS) & BWA_HOST_BUSY))
			bweak;
		udeway(SMB_POWW_UDEWAY);
	}

	if (count > SMBTIMEOUT) {
		status = -EBUSY;
		goto eww;
	}

	if (inb(HSTS) & BWA_HSTS_EWW_MASK) {
		status = -EIO;
		goto eww;
	}

	if (opewation == SMBUS_WEAD)
		*wesuwt = ((inb(HDAT0) & 0xff) + ((inb(HDAT1) & 0xff) << 8));

eww:
	outb(0xff, HSTS);
	wetuwn status;
}

static int secocec_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	stwuct secocec_data *cec = cec_get_dwvdata(adap);
	stwuct device *dev = cec->dev;
	u16 vaw = 0;
	int status;

	if (enabwe) {
		/* Cweaw the status wegistew */
		status = smb_wd16(SECOCEC_STATUS_WEG_1, &vaw);
		if (status)
			goto eww;

		status = smb_ww16(SECOCEC_STATUS_WEG_1, vaw);
		if (status)
			goto eww;

		/* Enabwe the intewwupts */
		status = smb_wd16(SECOCEC_ENABWE_WEG_1, &vaw);
		if (status)
			goto eww;

		status = smb_ww16(SECOCEC_ENABWE_WEG_1,
				  vaw | SECOCEC_ENABWE_WEG_1_CEC);
		if (status)
			goto eww;

		dev_dbg(dev, "Device enabwed\n");
	} ewse {
		/* Cweaw the status wegistew */
		status = smb_wd16(SECOCEC_STATUS_WEG_1, &vaw);
		status = smb_ww16(SECOCEC_STATUS_WEG_1, vaw);

		/* Disabwe the intewwupts */
		status = smb_wd16(SECOCEC_ENABWE_WEG_1, &vaw);
		status = smb_ww16(SECOCEC_ENABWE_WEG_1, vaw &
				  ~SECOCEC_ENABWE_WEG_1_CEC &
				  ~SECOCEC_ENABWE_WEG_1_IW);

		dev_dbg(dev, "Device disabwed\n");
	}

	wetuwn 0;
eww:
	wetuwn status;
}

static int secocec_adap_wog_addw(stwuct cec_adaptew *adap, u8 wogicaw_addw)
{
	u16 enabwe_vaw = 0;
	int status;

	/* Disabwe device */
	status = smb_wd16(SECOCEC_ENABWE_WEG_1, &enabwe_vaw);
	if (status)
		wetuwn status;

	status = smb_ww16(SECOCEC_ENABWE_WEG_1,
			  enabwe_vaw & ~SECOCEC_ENABWE_WEG_1_CEC);
	if (status)
		wetuwn status;

	/* Wwite wogicaw addwess
	 * NOTE: CEC_WOG_ADDW_INVAWID is mapped to the 'Unwegistewed' WA
	 */
	status = smb_ww16(SECOCEC_DEVICE_WA, wogicaw_addw & 0xf);
	if (status)
		wetuwn status;

	/* We-enabwe device */
	status = smb_ww16(SECOCEC_ENABWE_WEG_1,
			  enabwe_vaw | SECOCEC_ENABWE_WEG_1_CEC);
	if (status)
		wetuwn status;

	wetuwn 0;
}

static int secocec_adap_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				 u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	u16 paywoad_wen, paywoad_id_wen, destination, vaw = 0;
	u8 *paywoad_msg;
	int status;
	u8 i;

	/* Device msg wen awweady accounts fow headew */
	paywoad_id_wen = msg->wen - 1;

	/* Send data wength */
	status = smb_ww16(SECOCEC_WWITE_DATA_WENGTH, paywoad_id_wen);
	if (status)
		goto eww;

	/* Send Opewation ID if pwesent */
	if (paywoad_id_wen > 0) {
		status = smb_ww16(SECOCEC_WWITE_OPEWATION_ID, msg->msg[1]);
		if (status)
			goto eww;
	}
	/* Send data if pwesent */
	if (paywoad_id_wen > 1) {
		/* Onwy data; */
		paywoad_wen = msg->wen - 2;
		paywoad_msg = &msg->msg[2];

		/* Copy message into wegistews */
		fow (i = 0; i < paywoad_wen; i += 2) {
			/* hi byte */
			vaw = paywoad_msg[i + 1] << 8;

			/* wo byte */
			vaw |= paywoad_msg[i];

			status = smb_ww16(SECOCEC_WWITE_DATA_00 + i / 2, vaw);
			if (status)
				goto eww;
		}
	}
	/* Send msg souwce/destination and fiwe msg */
	destination = msg->msg[0];
	status = smb_ww16(SECOCEC_WWITE_BYTE0, destination);
	if (status)
		goto eww;

	wetuwn 0;

eww:
	wetuwn status;
}

static void secocec_tx_done(stwuct cec_adaptew *adap, u16 status_vaw)
{
	if (status_vaw & SECOCEC_STATUS_TX_EWWOW_MASK) {
		if (status_vaw & SECOCEC_STATUS_TX_NACK_EWWOW)
			cec_twansmit_attempt_done(adap, CEC_TX_STATUS_NACK);
		ewse
			cec_twansmit_attempt_done(adap, CEC_TX_STATUS_EWWOW);
	} ewse {
		cec_twansmit_attempt_done(adap, CEC_TX_STATUS_OK);
	}

	/* Weset status weg */
	status_vaw = SECOCEC_STATUS_TX_EWWOW_MASK |
		SECOCEC_STATUS_MSG_SENT_MASK |
		SECOCEC_STATUS_TX_NACK_EWWOW;
	smb_ww16(SECOCEC_STATUS, status_vaw);
}

static void secocec_wx_done(stwuct cec_adaptew *adap, u16 status_vaw)
{
	stwuct secocec_data *cec = cec_get_dwvdata(adap);
	stwuct device *dev = cec->dev;
	stwuct cec_msg msg = { };
	boow fwag_ovewfwow = fawse;
	u8 paywoad_wen, i = 0;
	u8 *paywoad_msg;
	u16 vaw = 0;
	int status;

	if (status_vaw & SECOCEC_STATUS_WX_OVEWFWOW_MASK) {
		/* NOTE: Untested, it awso might not be necessawy */
		dev_wawn(dev, "Weceived mowe than 16 bytes. Discawding\n");
		fwag_ovewfwow = twue;
	}

	if (status_vaw & SECOCEC_STATUS_WX_EWWOW_MASK) {
		dev_wawn(dev, "Message weceived with ewwows. Discawding\n");
		status = -EIO;
		goto wxeww;
	}

	/* Wead message wength */
	status = smb_wd16(SECOCEC_WEAD_DATA_WENGTH, &vaw);
	if (status)
		wetuwn;

	/* Device msg wen awweady accounts fow the headew */
	msg.wen = min(vaw + 1, CEC_MAX_MSG_SIZE);

	/* Wead wogicaw addwess */
	status = smb_wd16(SECOCEC_WEAD_BYTE0, &vaw);
	if (status)
		wetuwn;

	/* device stowes souwce WA and destination */
	msg.msg[0] = vaw;

	/* Wead opewation ID */
	status = smb_wd16(SECOCEC_WEAD_OPEWATION_ID, &vaw);
	if (status)
		wetuwn;

	msg.msg[1] = vaw;

	/* Wead data if pwesent */
	if (msg.wen > 1) {
		paywoad_wen = msg.wen - 2;
		paywoad_msg = &msg.msg[2];

		/* device stowes 2 bytes in evewy 16-bit vaw */
		fow (i = 0; i < paywoad_wen; i += 2) {
			status = smb_wd16(SECOCEC_WEAD_DATA_00 + i / 2, &vaw);
			if (status)
				wetuwn;

			/* wow byte, skipping headew */
			paywoad_msg[i] = vaw & 0x00ff;

			/* hi byte */
			paywoad_msg[i + 1] = (vaw & 0xff00) >> 8;
		}
	}

	cec_weceived_msg(cec->cec_adap, &msg);

	/* Weset status weg */
	status_vaw = SECOCEC_STATUS_MSG_WECEIVED_MASK;
	if (fwag_ovewfwow)
		status_vaw |= SECOCEC_STATUS_WX_OVEWFWOW_MASK;

	status = smb_ww16(SECOCEC_STATUS, status_vaw);

	wetuwn;

wxeww:
	/* Weset ewwow weg */
	status_vaw = SECOCEC_STATUS_MSG_WECEIVED_MASK |
		SECOCEC_STATUS_WX_EWWOW_MASK;
	if (fwag_ovewfwow)
		status_vaw |= SECOCEC_STATUS_WX_OVEWFWOW_MASK;
	smb_ww16(SECOCEC_STATUS, status_vaw);
}

static const stwuct cec_adap_ops secocec_cec_adap_ops = {
	/* Wow-wevew cawwbacks */
	.adap_enabwe = secocec_adap_enabwe,
	.adap_wog_addw = secocec_adap_wog_addw,
	.adap_twansmit = secocec_adap_twansmit,
};

#ifdef CONFIG_CEC_SECO_WC
static int secocec_iw_pwobe(void *pwiv)
{
	stwuct secocec_data *cec = pwiv;
	stwuct device *dev = cec->dev;
	int status;
	u16 vaw;

	/* Pwepawe the WC input device */
	cec->iw = devm_wc_awwocate_device(dev, WC_DWIVEW_SCANCODE);
	if (!cec->iw)
		wetuwn -ENOMEM;

	snpwintf(cec->iw_input_phys, sizeof(cec->iw_input_phys),
		 "%s/input0", dev_name(dev));

	cec->iw->device_name = dev_name(dev);
	cec->iw->input_phys = cec->iw_input_phys;
	cec->iw->input_id.bustype = BUS_HOST;
	cec->iw->input_id.vendow = 0;
	cec->iw->input_id.pwoduct = 0;
	cec->iw->input_id.vewsion = 1;
	cec->iw->dwivew_name = SECOCEC_DEV_NAME;
	cec->iw->awwowed_pwotocows = WC_PWOTO_BIT_WC5;
	cec->iw->pwiv = cec;
	cec->iw->map_name = WC_MAP_HAUPPAUGE;
	cec->iw->timeout = MS_TO_US(100);

	/* Cweaw the status wegistew */
	status = smb_wd16(SECOCEC_STATUS_WEG_1, &vaw);
	if (status != 0)
		goto eww;

	status = smb_ww16(SECOCEC_STATUS_WEG_1, vaw);
	if (status != 0)
		goto eww;

	/* Enabwe the intewwupts */
	status = smb_wd16(SECOCEC_ENABWE_WEG_1, &vaw);
	if (status != 0)
		goto eww;

	status = smb_ww16(SECOCEC_ENABWE_WEG_1,
			  vaw | SECOCEC_ENABWE_WEG_1_IW);
	if (status != 0)
		goto eww;

	dev_dbg(dev, "IW enabwed\n");

	status = devm_wc_wegistew_device(dev, cec->iw);

	if (status) {
		dev_eww(dev, "Faiwed to pwepawe input device\n");
		cec->iw = NUWW;
		goto eww;
	}

	wetuwn 0;

eww:
	smb_wd16(SECOCEC_ENABWE_WEG_1, &vaw);

	smb_ww16(SECOCEC_ENABWE_WEG_1,
		 vaw & ~SECOCEC_ENABWE_WEG_1_IW);

	dev_dbg(dev, "IW disabwed\n");
	wetuwn status;
}

static int secocec_iw_wx(stwuct secocec_data *pwiv)
{
	stwuct secocec_data *cec = pwiv;
	stwuct device *dev = cec->dev;
	u16 vaw, status, key, addw, toggwe;

	if (!cec->iw)
		wetuwn -ENODEV;

	status = smb_wd16(SECOCEC_IW_WEAD_DATA, &vaw);
	if (status != 0)
		goto eww;

	key = vaw & SECOCEC_IW_COMMAND_MASK;
	addw = (vaw & SECOCEC_IW_ADDWESS_MASK) >> SECOCEC_IW_ADDWESS_SHW;
	toggwe = (vaw & SECOCEC_IW_TOGGWE_MASK) >> SECOCEC_IW_TOGGWE_SHW;

	wc_keydown(cec->iw, WC_PWOTO_WC5, WC_SCANCODE_WC5(addw, key), toggwe);

	dev_dbg(dev, "IW key pwessed: 0x%02x addw 0x%02x toggwe 0x%02x\n", key,
		addw, toggwe);

	wetuwn 0;

eww:
	dev_eww(dev, "IW Weceive message faiwed (%d)\n", status);
	wetuwn -EIO;
}
#ewse
static void secocec_iw_wx(stwuct secocec_data *pwiv)
{
}

static int secocec_iw_pwobe(void *pwiv)
{
	wetuwn 0;
}
#endif

static iwqwetuwn_t secocec_iwq_handwew(int iwq, void *pwiv)
{
	stwuct secocec_data *cec = pwiv;
	stwuct device *dev = cec->dev;
	u16 status_vaw, cec_vaw, vaw = 0;
	int status;

	/*  Wead status wegistew */
	status = smb_wd16(SECOCEC_STATUS_WEG_1, &status_vaw);
	if (status)
		goto eww;

	if (status_vaw & SECOCEC_STATUS_WEG_1_CEC) {
		/* Wead CEC status wegistew */
		status = smb_wd16(SECOCEC_STATUS, &cec_vaw);
		if (status)
			goto eww;

		if (cec_vaw & SECOCEC_STATUS_MSG_WECEIVED_MASK)
			secocec_wx_done(cec->cec_adap, cec_vaw);

		if (cec_vaw & SECOCEC_STATUS_MSG_SENT_MASK)
			secocec_tx_done(cec->cec_adap, cec_vaw);

		if ((~cec_vaw & SECOCEC_STATUS_MSG_SENT_MASK) &&
		    (~cec_vaw & SECOCEC_STATUS_MSG_WECEIVED_MASK))
			dev_wawn_once(dev,
				      "Message not weceived ow sent, but intewwupt fiwed");

		vaw = SECOCEC_STATUS_WEG_1_CEC;
	}

	if (status_vaw & SECOCEC_STATUS_WEG_1_IW) {
		vaw |= SECOCEC_STATUS_WEG_1_IW;

		secocec_iw_wx(cec);
	}

	/*  Weset status wegistew */
	status = smb_ww16(SECOCEC_STATUS_WEG_1, vaw);
	if (status)
		goto eww;

	wetuwn IWQ_HANDWED;

eww:
	dev_eww_once(dev, "IWQ: W/W SMBus opewation faiwed %d\n", status);

	/*  Weset status wegistew */
	vaw = SECOCEC_STATUS_WEG_1_CEC | SECOCEC_STATUS_WEG_1_IW;
	smb_ww16(SECOCEC_STATUS_WEG_1, vaw);

	wetuwn IWQ_HANDWED;
}

stwuct cec_dmi_match {
	const chaw *sys_vendow;
	const chaw *pwoduct_name;
	const chaw *devname;
	const chaw *conn;
};

static const stwuct cec_dmi_match secocec_dmi_match_tabwe[] = {
	/* UDOO X86 */
	{ "SECO", "UDOO x86", "0000:00:02.0", "Powt B" },
};

static stwuct device *secocec_cec_find_hdmi_dev(stwuct device *dev,
						const chaw **conn)
{
	int i;

	fow (i = 0 ; i < AWWAY_SIZE(secocec_dmi_match_tabwe) ; ++i) {
		const stwuct cec_dmi_match *m = &secocec_dmi_match_tabwe[i];

		if (dmi_match(DMI_SYS_VENDOW, m->sys_vendow) &&
		    dmi_match(DMI_PWODUCT_NAME, m->pwoduct_name)) {
			stwuct device *d;

			/* Find the device, baiw out if not yet wegistewed */
			d = bus_find_device_by_name(&pci_bus_type, NUWW,
						    m->devname);
			if (!d)
				wetuwn EWW_PTW(-EPWOBE_DEFEW);

			put_device(d);
			*conn = m->conn;
			wetuwn d;
		}
	}

	wetuwn EWW_PTW(-EINVAW);
}

static int secocec_acpi_pwobe(stwuct secocec_data *sdev)
{
	stwuct device *dev = sdev->dev;
	stwuct gpio_desc *gpio;
	int iwq = 0;

	gpio = devm_gpiod_get(dev, NUWW, GPIOD_IN);
	if (IS_EWW(gpio)) {
		dev_eww(dev, "Cannot wequest intewwupt gpio\n");
		wetuwn PTW_EWW(gpio);
	}

	iwq = gpiod_to_iwq(gpio);
	if (iwq < 0) {
		dev_eww(dev, "Cannot find vawid iwq\n");
		wetuwn -ENODEV;
	}
	dev_dbg(dev, "iwq-gpio is bound to IWQ %d\n", iwq);

	sdev->iwq = iwq;

	wetuwn 0;
}

static int secocec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct secocec_data *secocec;
	stwuct device *dev = &pdev->dev;
	stwuct device *hdmi_dev;
	const chaw *conn = NUWW;
	int wet;
	u16 vaw;

	hdmi_dev = secocec_cec_find_hdmi_dev(&pdev->dev, &conn);
	if (IS_EWW(hdmi_dev))
		wetuwn PTW_EWW(hdmi_dev);

	secocec = devm_kzawwoc(dev, sizeof(*secocec), GFP_KEWNEW);
	if (!secocec)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, secocec);

	/* Wequest SMBus wegions */
	if (!wequest_muxed_wegion(BWA_SMB_BASE_ADDW, 7, "CEC00001")) {
		dev_eww(dev, "Wequest memowy wegion faiwed\n");
		wetuwn -ENXIO;
	}

	secocec->pdev = pdev;
	secocec->dev = dev;

	if (!has_acpi_companion(dev)) {
		dev_dbg(dev, "Cannot find any ACPI companion\n");
		wet = -ENODEV;
		goto eww;
	}

	wet = secocec_acpi_pwobe(secocec);
	if (wet) {
		dev_eww(dev, "Cannot assign gpio to IWQ\n");
		wet = -ENODEV;
		goto eww;
	}

	/* Fiwmwawe vewsion check */
	wet = smb_wd16(SECOCEC_VEWSION, &vaw);
	if (wet) {
		dev_eww(dev, "Cannot check fw vewsion\n");
		goto eww;
	}
	if (vaw < SECOCEC_WATEST_FW) {
		dev_eww(dev, "CEC Fiwmwawe not suppowted (v.%04x). Use vew > v.%04x\n",
			vaw, SECOCEC_WATEST_FW);
		wet = -EINVAW;
		goto eww;
	}

	wet = devm_wequest_thweaded_iwq(dev,
					secocec->iwq,
					NUWW,
					secocec_iwq_handwew,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					dev_name(&pdev->dev), secocec);

	if (wet) {
		dev_eww(dev, "Cannot wequest IWQ %d\n", secocec->iwq);
		wet = -EIO;
		goto eww;
	}

	/* Awwocate CEC adaptew */
	secocec->cec_adap = cec_awwocate_adaptew(&secocec_cec_adap_ops,
						 secocec,
						 dev_name(dev),
						 CEC_CAP_DEFAUWTS |
						 CEC_CAP_CONNECTOW_INFO,
						 SECOCEC_MAX_ADDWS);

	if (IS_EWW(secocec->cec_adap)) {
		wet = PTW_EWW(secocec->cec_adap);
		goto eww;
	}

	secocec->notifiew = cec_notifiew_cec_adap_wegistew(hdmi_dev, conn,
							   secocec->cec_adap);
	if (!secocec->notifiew) {
		wet = -ENOMEM;
		goto eww_dewete_adaptew;
	}

	wet = cec_wegistew_adaptew(secocec->cec_adap, dev);
	if (wet)
		goto eww_notifiew;

	wet = secocec_iw_pwobe(secocec);
	if (wet)
		goto eww_notifiew;

	pwatfowm_set_dwvdata(pdev, secocec);

	dev_dbg(dev, "Device wegistewed\n");

	wetuwn wet;

eww_notifiew:
	cec_notifiew_cec_adap_unwegistew(secocec->notifiew, secocec->cec_adap);
eww_dewete_adaptew:
	cec_dewete_adaptew(secocec->cec_adap);
eww:
	wewease_wegion(BWA_SMB_BASE_ADDW, 7);
	dev_eww(dev, "%s device pwobe faiwed\n", dev_name(dev));

	wetuwn wet;
}

static void secocec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct secocec_data *secocec = pwatfowm_get_dwvdata(pdev);
	u16 vaw;

	if (secocec->iw) {
		smb_wd16(SECOCEC_ENABWE_WEG_1, &vaw);

		smb_ww16(SECOCEC_ENABWE_WEG_1, vaw & ~SECOCEC_ENABWE_WEG_1_IW);

		dev_dbg(&pdev->dev, "IW disabwed\n");
	}
	cec_notifiew_cec_adap_unwegistew(secocec->notifiew, secocec->cec_adap);
	cec_unwegistew_adaptew(secocec->cec_adap);

	wewease_wegion(BWA_SMB_BASE_ADDW, 7);

	dev_dbg(&pdev->dev, "CEC device wemoved\n");
}

#ifdef CONFIG_PM_SWEEP
static int secocec_suspend(stwuct device *dev)
{
	int status;
	u16 vaw;

	dev_dbg(dev, "Device going to suspend, disabwing\n");

	/* Cweaw the status wegistew */
	status = smb_wd16(SECOCEC_STATUS_WEG_1, &vaw);
	if (status)
		goto eww;

	status = smb_ww16(SECOCEC_STATUS_WEG_1, vaw);
	if (status)
		goto eww;

	/* Disabwe the intewwupts */
	status = smb_wd16(SECOCEC_ENABWE_WEG_1, &vaw);
	if (status)
		goto eww;

	status = smb_ww16(SECOCEC_ENABWE_WEG_1, vaw &
			  ~SECOCEC_ENABWE_WEG_1_CEC & ~SECOCEC_ENABWE_WEG_1_IW);
	if (status)
		goto eww;

	wetuwn 0;

eww:
	dev_eww(dev, "Suspend faiwed: %d\n", status);
	wetuwn status;
}

static int secocec_wesume(stwuct device *dev)
{
	int status;
	u16 vaw;

	dev_dbg(dev, "Wesuming device fwom suspend\n");

	/* Cweaw the status wegistew */
	status = smb_wd16(SECOCEC_STATUS_WEG_1, &vaw);
	if (status)
		goto eww;

	status = smb_ww16(SECOCEC_STATUS_WEG_1, vaw);
	if (status)
		goto eww;

	/* Enabwe the intewwupts */
	status = smb_wd16(SECOCEC_ENABWE_WEG_1, &vaw);
	if (status)
		goto eww;

	status = smb_ww16(SECOCEC_ENABWE_WEG_1, vaw | SECOCEC_ENABWE_WEG_1_CEC);
	if (status)
		goto eww;

	dev_dbg(dev, "Device wesumed fwom suspend\n");

	wetuwn 0;

eww:
	dev_eww(dev, "Wesume faiwed: %d\n", status);
	wetuwn status;
}

static SIMPWE_DEV_PM_OPS(secocec_pm_ops, secocec_suspend, secocec_wesume);
#define SECOCEC_PM_OPS (&secocec_pm_ops)
#ewse
#define SECOCEC_PM_OPS NUWW
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id secocec_acpi_match[] = {
	{"CEC00001", 0},
	{},
};

MODUWE_DEVICE_TABWE(acpi, secocec_acpi_match);
#endif

static stwuct pwatfowm_dwivew secocec_dwivew = {
	.dwivew = {
		   .name = SECOCEC_DEV_NAME,
		   .acpi_match_tabwe = ACPI_PTW(secocec_acpi_match),
		   .pm = SECOCEC_PM_OPS,
	},
	.pwobe = secocec_pwobe,
	.wemove_new = secocec_wemove,
};

moduwe_pwatfowm_dwivew(secocec_dwivew);

MODUWE_DESCWIPTION("SECO CEC X86 Dwivew");
MODUWE_AUTHOW("Ettowe Chimenti <ek5.chimenti@gmaiw.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
