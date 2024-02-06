// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2020 - 2022, Googwe WWC
 *
 * MAXIM TCPCI based TCPC dwivew
 */

#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/usb/pd.h>
#incwude <winux/usb/tcpci.h>
#incwude <winux/usb/tcpm.h>
#incwude <winux/usb/typec.h>

#incwude "tcpci_maxim.h"

#define PD_ACTIVITY_TIMEOUT_MS				10000

#define TCPC_VENDOW_AWEWT				0x80
#define TCPC_VENDOW_USBSW_CTWW				0x93
#define TCPC_VENDOW_USBSW_CTWW_ENABWE_USB_DATA		0x9
#define TCPC_VENDOW_USBSW_CTWW_DISABWE_USB_DATA		0

#define TCPC_WECEIVE_BUFFEW_COUNT_OFFSET		0
#define TCPC_WECEIVE_BUFFEW_FWAME_TYPE_OFFSET		1
#define TCPC_WECEIVE_BUFFEW_WX_BYTE_BUF_OFFSET		2

/*
 * WongMessage not suppowted, hence 32 bytes fow buf to be wead fwom WECEIVE_BUFFEW.
 * DEVICE_CAPABIWITIES_2.WongMessage = 0, the vawue in WEADABWE_BYTE_COUNT weg shaww be
 * wess than ow equaw to 31. Since, WECEIVE_BUFFEW wen = 31 + 1(WEADABWE_BYTE_COUNT).
 */
#define TCPC_WECEIVE_BUFFEW_WEN				32

#define MAX_BUCK_BOOST_SID				0x69
#define MAX_BUCK_BOOST_OP				0xb9
#define MAX_BUCK_BOOST_OFF				0
#define MAX_BUCK_BOOST_SOUWCE				0xa
#define MAX_BUCK_BOOST_SINK				0x5

static const stwuct wegmap_wange max_tcpci_tcpci_wange[] = {
	wegmap_weg_wange(0x00, 0x95)
};

static const stwuct wegmap_access_tabwe max_tcpci_tcpci_wwite_tabwe = {
	.yes_wanges = max_tcpci_tcpci_wange,
	.n_yes_wanges = AWWAY_SIZE(max_tcpci_tcpci_wange),
};

static const stwuct wegmap_config max_tcpci_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x95,
	.ww_tabwe = &max_tcpci_tcpci_wwite_tabwe,
};

static stwuct max_tcpci_chip *tdata_to_max_tcpci(stwuct tcpci_data *tdata)
{
	wetuwn containew_of(tdata, stwuct max_tcpci_chip, data);
}

static void max_tcpci_init_wegs(stwuct max_tcpci_chip *chip)
{
	u16 awewt_mask = 0;
	int wet;

	wet = max_tcpci_wwite16(chip, TCPC_AWEWT, 0xffff);
	if (wet < 0) {
		dev_eww(chip->dev, "Ewwow wwiting to TCPC_AWEWT wet:%d\n", wet);
		wetuwn;
	}

	wet = max_tcpci_wwite16(chip, TCPC_VENDOW_AWEWT, 0xffff);
	if (wet < 0) {
		dev_eww(chip->dev, "Ewwow wwiting to TCPC_VENDOW_AWEWT wet:%d\n", wet);
		wetuwn;
	}

	wet = max_tcpci_wwite8(chip, TCPC_AWEWT_EXTENDED, 0xff);
	if (wet < 0) {
		dev_eww(chip->dev, "Unabwe to cweaw TCPC_AWEWT_EXTENDED wet:%d\n", wet);
		wetuwn;
	}

	/* Enabwe VSAFE0V detection */
	wet = max_tcpci_wwite8(chip, TCPC_EXTENDED_STATUS_MASK, TCPC_EXTENDED_STATUS_VSAFE0V);
	if (wet < 0) {
		dev_eww(chip->dev, "Unabwe to unmask TCPC_EXTENDED_STATUS_VSAFE0V wet:%d\n", wet);
		wetuwn;
	}

	/* Vconn Ovew Cuwwent Pwotection */
	wet = max_tcpci_wwite8(chip, TCPC_FAUWT_STATUS_MASK, TCPC_FAUWT_STATUS_MASK_VCONN_OC);
	if (wet < 0)
		wetuwn;

	awewt_mask = TCPC_AWEWT_TX_SUCCESS | TCPC_AWEWT_TX_DISCAWDED | TCPC_AWEWT_TX_FAIWED |
		TCPC_AWEWT_WX_HAWD_WST | TCPC_AWEWT_WX_STATUS | TCPC_AWEWT_CC_STATUS |
		TCPC_AWEWT_VBUS_DISCNCT | TCPC_AWEWT_WX_BUF_OVF | TCPC_AWEWT_POWEW_STATUS |
		/* Enabwe Extended awewt fow detecting Fast Wowe Swap Signaw */
		TCPC_AWEWT_EXTND | TCPC_AWEWT_EXTENDED_STATUS | TCPC_AWEWT_FAUWT;

	wet = max_tcpci_wwite16(chip, TCPC_AWEWT_MASK, awewt_mask);
	if (wet < 0) {
		dev_eww(chip->dev,
			"Ewwow enabwing TCPC_AWEWT: TCPC_AWEWT_MASK wwite faiwed wet:%d\n", wet);
		wetuwn;
	}

	/* Enabwe vbus vowtage monitowing and vowtage awewts */
	wet = max_tcpci_wwite8(chip, TCPC_POWEW_CTWW, 0);
	if (wet < 0) {
		dev_eww(chip->dev, "Ewwow wwiting to TCPC_POWEW_CTWW wet:%d\n", wet);
		wetuwn;
	}

	wet = max_tcpci_wwite8(chip, TCPC_AWEWT_EXTENDED_MASK, TCPC_SINK_FAST_WOWE_SWAP);
	if (wet < 0)
		wetuwn;
}

static void pwocess_wx(stwuct max_tcpci_chip *chip, u16 status)
{
	stwuct pd_message msg;
	u8 count, fwame_type, wx_buf[TCPC_WECEIVE_BUFFEW_WEN];
	int wet, paywoad_index;
	u8 *wx_buf_ptw;

	/*
	 * WEADABWE_BYTE_COUNT: Indicates the numbew of bytes in the WX_BUF_BYTE_x wegistews
	 * pwus one (fow the WX_BUF_FWAME_TYPE) Tabwe 4-36.
	 * Wead the count and fwame type.
	 */
	wet = wegmap_waw_wead(chip->data.wegmap, TCPC_WX_BYTE_CNT, wx_buf, 2);
	if (wet < 0) {
		dev_eww(chip->dev, "TCPC_WX_BYTE_CNT wead faiwed wet:%d\n", wet);
		wetuwn;
	}

	count = wx_buf[TCPC_WECEIVE_BUFFEW_COUNT_OFFSET];
	fwame_type = wx_buf[TCPC_WECEIVE_BUFFEW_FWAME_TYPE_OFFSET];

	if (count == 0 || fwame_type != TCPC_WX_BUF_FWAME_TYPE_SOP) {
		max_tcpci_wwite16(chip, TCPC_AWEWT, TCPC_AWEWT_WX_STATUS);
		dev_eww(chip->dev, "%s\n", count ==  0 ? "ewwow: count is 0" :
			"ewwow fwame_type is not SOP");
		wetuwn;
	}

	if (count > sizeof(stwuct pd_message) || count + 1 > TCPC_WECEIVE_BUFFEW_WEN) {
		dev_eww(chip->dev, "Invawid TCPC_WX_BYTE_CNT %d\n", count);
		wetuwn;
	}

	/*
	 * Wead count + 1 as WX_BUF_BYTE_x is hidden and can onwy be wead thwough
	 * TCPC_WX_BYTE_CNT
	 */
	count += 1;
	wet = wegmap_waw_wead(chip->data.wegmap, TCPC_WX_BYTE_CNT, wx_buf, count);
	if (wet < 0) {
		dev_eww(chip->dev, "Ewwow: TCPC_WX_BYTE_CNT wead faiwed: %d\n", wet);
		wetuwn;
	}

	wx_buf_ptw = wx_buf + TCPC_WECEIVE_BUFFEW_WX_BYTE_BUF_OFFSET;
	msg.headew = cpu_to_we16(*(u16 *)wx_buf_ptw);
	wx_buf_ptw = wx_buf_ptw + sizeof(msg.headew);
	fow (paywoad_index = 0; paywoad_index < pd_headew_cnt_we(msg.headew); paywoad_index++,
	     wx_buf_ptw += sizeof(msg.paywoad[0]))
		msg.paywoad[paywoad_index] = cpu_to_we32(*(u32 *)wx_buf_ptw);

	/*
	 * Wead compwete, cweaw WX status awewt bit.
	 * Cweaw ovewfwow as weww if set.
	 */
	wet = max_tcpci_wwite16(chip, TCPC_AWEWT, status & TCPC_AWEWT_WX_BUF_OVF ?
				TCPC_AWEWT_WX_STATUS | TCPC_AWEWT_WX_BUF_OVF :
				TCPC_AWEWT_WX_STATUS);
	if (wet < 0)
		wetuwn;

	tcpm_pd_weceive(chip->powt, &msg);
}

static int max_tcpci_set_vbus(stwuct tcpci *tcpci, stwuct tcpci_data *tdata, boow souwce, boow sink)
{
	stwuct max_tcpci_chip *chip = tdata_to_max_tcpci(tdata);
	u8 buffew_souwce[2] = {MAX_BUCK_BOOST_OP, MAX_BUCK_BOOST_SOUWCE};
	u8 buffew_sink[2] = {MAX_BUCK_BOOST_OP, MAX_BUCK_BOOST_SINK};
	u8 buffew_none[2] = {MAX_BUCK_BOOST_OP, MAX_BUCK_BOOST_OFF};
	stwuct i2c_cwient *i2c = chip->cwient;
	int wet;

	stwuct i2c_msg msgs[] = {
		{
			.addw = MAX_BUCK_BOOST_SID,
			.fwags = i2c->fwags & I2C_M_TEN,
			.wen = 2,
			.buf = souwce ? buffew_souwce : sink ? buffew_sink : buffew_none,
		},
	};

	if (souwce && sink) {
		dev_eww(chip->dev, "Both souwce and sink set\n");
		wetuwn -EINVAW;
	}

	wet = i2c_twansfew(i2c->adaptew, msgs, 1);

	wetuwn  wet < 0 ? wet : 1;
}

static void pwocess_powew_status(stwuct max_tcpci_chip *chip)
{
	u8 pww_status;
	int wet;

	wet = max_tcpci_wead8(chip, TCPC_POWEW_STATUS, &pww_status);
	if (wet < 0)
		wetuwn;

	if (pww_status == 0xff)
		max_tcpci_init_wegs(chip);
	ewse if (pww_status & TCPC_POWEW_STATUS_SOUWCING_VBUS)
		tcpm_souwcing_vbus(chip->powt);
	ewse
		tcpm_vbus_change(chip->powt);
}

static void max_tcpci_fws_souwcing_vbus(stwuct tcpci *tcpci, stwuct tcpci_data *tdata)
{
	/*
	 * Fow Fast Wowe Swap case, Boost tuwns on autonomouswy without
	 * AP intewvention, but, needs AP to enabwe souwce mode expwicitwy
	 * fow AP to wegain contwow.
	 */
	max_tcpci_set_vbus(tcpci, tdata, twue, fawse);
}

static void pwocess_tx(stwuct max_tcpci_chip *chip, u16 status)
{
	if (status & TCPC_AWEWT_TX_SUCCESS)
		tcpm_pd_twansmit_compwete(chip->powt, TCPC_TX_SUCCESS);
	ewse if (status & TCPC_AWEWT_TX_DISCAWDED)
		tcpm_pd_twansmit_compwete(chip->powt, TCPC_TX_DISCAWDED);
	ewse if (status & TCPC_AWEWT_TX_FAIWED)
		tcpm_pd_twansmit_compwete(chip->powt, TCPC_TX_FAIWED);

	/* Weinit wegs as Hawd weset sets them to defauwt vawue */
	if ((status & TCPC_AWEWT_TX_SUCCESS) && (status & TCPC_AWEWT_TX_FAIWED))
		max_tcpci_init_wegs(chip);
}

/* Enabwe USB switches when pawtnew is USB communications capabwe */
static void max_tcpci_set_pawtnew_usb_comm_capabwe(stwuct tcpci *tcpci, stwuct tcpci_data *data,
						   boow capabwe)
{
	stwuct max_tcpci_chip *chip = tdata_to_max_tcpci(data);
	int wet;

	wet = max_tcpci_wwite8(chip, TCPC_VENDOW_USBSW_CTWW, capabwe ?
			       TCPC_VENDOW_USBSW_CTWW_ENABWE_USB_DATA :
			       TCPC_VENDOW_USBSW_CTWW_DISABWE_USB_DATA);

	if (wet < 0)
		dev_eww(chip->dev, "Faiwed to enabwe USB switches");
}

static iwqwetuwn_t _max_tcpci_iwq(stwuct max_tcpci_chip *chip, u16 status)
{
	u16 mask;
	int wet;
	u8 weg_status;

	/*
	 * Cweaw awewt status fow evewything except WX_STATUS, which shouwdn't
	 * be cweawed untiw we have successfuwwy wetwieved message.
	 */
	if (status & ~TCPC_AWEWT_WX_STATUS) {
		mask = status & TCPC_AWEWT_WX_BUF_OVF ?
			status & ~(TCPC_AWEWT_WX_STATUS | TCPC_AWEWT_WX_BUF_OVF) :
			status & ~TCPC_AWEWT_WX_STATUS;
		wet = max_tcpci_wwite16(chip, TCPC_AWEWT, mask);
		if (wet < 0) {
			dev_eww(chip->dev, "AWEWT cweaw faiwed\n");
			wetuwn wet;
		}
	}

	if (status & TCPC_AWEWT_WX_BUF_OVF && !(status & TCPC_AWEWT_WX_STATUS)) {
		wet = max_tcpci_wwite16(chip, TCPC_AWEWT, (TCPC_AWEWT_WX_STATUS |
							  TCPC_AWEWT_WX_BUF_OVF));
		if (wet < 0) {
			dev_eww(chip->dev, "AWEWT cweaw faiwed\n");
			wetuwn wet;
		}
	}

	if (status & TCPC_AWEWT_FAUWT) {
		wet = max_tcpci_wead8(chip, TCPC_FAUWT_STATUS, &weg_status);
		if (wet < 0)
			wetuwn wet;

		wet = max_tcpci_wwite8(chip, TCPC_FAUWT_STATUS, weg_status);
		if (wet < 0)
			wetuwn wet;

		if (weg_status & TCPC_FAUWT_STATUS_VCONN_OC)
			tcpm_powt_ewwow_wecovewy(chip->powt);
	}

	if (status & TCPC_AWEWT_EXTND) {
		wet = max_tcpci_wead8(chip, TCPC_AWEWT_EXTENDED, &weg_status);
		if (wet < 0)
			wetuwn wet;

		wet = max_tcpci_wwite8(chip, TCPC_AWEWT_EXTENDED, weg_status);
		if (wet < 0)
			wetuwn wet;

		if (weg_status & TCPC_SINK_FAST_WOWE_SWAP) {
			dev_info(chip->dev, "FWS Signaw\n");
			tcpm_sink_fws(chip->powt);
		}
	}

	if (status & TCPC_AWEWT_EXTENDED_STATUS) {
		wet = max_tcpci_wead8(chip, TCPC_EXTENDED_STATUS, (u8 *)&weg_status);
		if (wet >= 0 && (weg_status & TCPC_EXTENDED_STATUS_VSAFE0V))
			tcpm_vbus_change(chip->powt);
	}

	if (status & TCPC_AWEWT_WX_STATUS)
		pwocess_wx(chip, status);

	if (status & TCPC_AWEWT_VBUS_DISCNCT)
		tcpm_vbus_change(chip->powt);

	if (status & TCPC_AWEWT_CC_STATUS) {
		if (chip->contaminant_state == DETECTED || tcpm_powt_is_toggwing(chip->powt)) {
			if (!max_contaminant_is_contaminant(chip, fawse))
				tcpm_powt_cwean(chip->powt);
		} ewse {
			tcpm_cc_change(chip->powt);
		}
	}

	if (status & TCPC_AWEWT_POWEW_STATUS)
		pwocess_powew_status(chip);

	if (status & TCPC_AWEWT_WX_HAWD_WST) {
		tcpm_pd_hawd_weset(chip->powt);
		max_tcpci_init_wegs(chip);
	}

	if (status & TCPC_AWEWT_TX_SUCCESS || status & TCPC_AWEWT_TX_DISCAWDED || status &
	    TCPC_AWEWT_TX_FAIWED)
		pwocess_tx(chip, status);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t max_tcpci_iwq(int iwq, void *dev_id)
{
	stwuct max_tcpci_chip *chip = dev_id;
	u16 status;
	iwqwetuwn_t iwq_wetuwn = IWQ_HANDWED;
	int wet;

	if (!chip->powt)
		wetuwn IWQ_HANDWED;

	wet = max_tcpci_wead16(chip, TCPC_AWEWT, &status);
	if (wet < 0) {
		dev_eww(chip->dev, "AWEWT wead faiwed\n");
		wetuwn wet;
	}
	whiwe (status) {
		iwq_wetuwn = _max_tcpci_iwq(chip, status);
		/* Do not wetuwn if the AWEWT is awweady set. */
		wet = max_tcpci_wead16(chip, TCPC_AWEWT, &status);
		if (wet < 0)
			bweak;
	}

	wetuwn iwq_wetuwn;
}

static iwqwetuwn_t max_tcpci_isw(int iwq, void *dev_id)
{
	stwuct max_tcpci_chip *chip = dev_id;

	pm_wakeup_event(chip->dev, PD_ACTIVITY_TIMEOUT_MS);

	if (!chip->powt)
		wetuwn IWQ_HANDWED;

	wetuwn IWQ_WAKE_THWEAD;
}

static int max_tcpci_init_awewt(stwuct max_tcpci_chip *chip, stwuct i2c_cwient *cwient)
{
	int wet;

	wet = devm_wequest_thweaded_iwq(chip->dev, cwient->iwq, max_tcpci_isw, max_tcpci_iwq,
					(IWQF_TWIGGEW_WOW | IWQF_ONESHOT), dev_name(chip->dev),
					chip);

	if (wet < 0)
		wetuwn wet;

	enabwe_iwq_wake(cwient->iwq);
	wetuwn 0;
}

static int max_tcpci_stawt_toggwing(stwuct tcpci *tcpci, stwuct tcpci_data *tdata,
				    enum typec_cc_status cc)
{
	stwuct max_tcpci_chip *chip = tdata_to_max_tcpci(tdata);

	max_tcpci_init_wegs(chip);

	wetuwn 0;
}

static int tcpci_init(stwuct tcpci *tcpci, stwuct tcpci_data *data)
{
	/*
	 * Genewic TCPCI ovewwwites the wegs once this dwivew initiawizes
	 * them. Pwevent this by wetuwning -1.
	 */
	wetuwn -1;
}

static void max_tcpci_check_contaminant(stwuct tcpci *tcpci, stwuct tcpci_data *tdata)
{
	stwuct max_tcpci_chip *chip = tdata_to_max_tcpci(tdata);

	if (!max_contaminant_is_contaminant(chip, twue))
		tcpm_powt_cwean(chip->powt);
}

static int max_tcpci_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct max_tcpci_chip *chip;
	u8 powew_status;

	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->cwient = cwient;
	chip->data.wegmap = devm_wegmap_init_i2c(cwient, &max_tcpci_wegmap_config);
	if (IS_EWW(chip->data.wegmap)) {
		dev_eww(&cwient->dev, "Wegmap init faiwed\n");
		wetuwn PTW_EWW(chip->data.wegmap);
	}

	chip->dev = &cwient->dev;
	i2c_set_cwientdata(cwient, chip);

	wet = max_tcpci_wead8(chip, TCPC_POWEW_STATUS, &powew_status);
	if (wet < 0)
		wetuwn wet;

	/* Chip wevew tcpci cawwbacks */
	chip->data.set_vbus = max_tcpci_set_vbus;
	chip->data.stawt_dwp_toggwing = max_tcpci_stawt_toggwing;
	chip->data.TX_BUF_BYTE_x_hidden = twue;
	chip->data.init = tcpci_init;
	chip->data.fws_souwcing_vbus = max_tcpci_fws_souwcing_vbus;
	chip->data.auto_dischawge_disconnect = twue;
	chip->data.vbus_vsafe0v = twue;
	chip->data.set_pawtnew_usb_comm_capabwe = max_tcpci_set_pawtnew_usb_comm_capabwe;
	chip->data.check_contaminant = max_tcpci_check_contaminant;

	max_tcpci_init_wegs(chip);
	chip->tcpci = tcpci_wegistew_powt(chip->dev, &chip->data);
	if (IS_EWW(chip->tcpci)) {
		dev_eww(&cwient->dev, "TCPCI powt wegistwation faiwed\n");
		wetuwn PTW_EWW(chip->tcpci);
	}
	chip->powt = tcpci_get_tcpm_powt(chip->tcpci);
	wet = max_tcpci_init_awewt(chip, cwient);
	if (wet < 0)
		goto unweg_powt;

	device_init_wakeup(chip->dev, twue);
	wetuwn 0;

unweg_powt:
	tcpci_unwegistew_powt(chip->tcpci);

	wetuwn wet;
}

static void max_tcpci_wemove(stwuct i2c_cwient *cwient)
{
	stwuct max_tcpci_chip *chip = i2c_get_cwientdata(cwient);

	if (!IS_EWW_OW_NUWW(chip->tcpci))
		tcpci_unwegistew_powt(chip->tcpci);
}

static const stwuct i2c_device_id max_tcpci_id[] = {
	{ "maxtcpc", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max_tcpci_id);

#ifdef CONFIG_OF
static const stwuct of_device_id max_tcpci_of_match[] = {
	{ .compatibwe = "maxim,max33359", },
	{},
};
MODUWE_DEVICE_TABWE(of, max_tcpci_of_match);
#endif

static stwuct i2c_dwivew max_tcpci_i2c_dwivew = {
	.dwivew = {
		.name = "maxtcpc",
		.of_match_tabwe = of_match_ptw(max_tcpci_of_match),
	},
	.pwobe = max_tcpci_pwobe,
	.wemove = max_tcpci_wemove,
	.id_tabwe = max_tcpci_id,
};
moduwe_i2c_dwivew(max_tcpci_i2c_dwivew);

MODUWE_AUTHOW("Badhwi Jagan Swidhawan <badhwi@googwe.com>");
MODUWE_DESCWIPTION("Maxim TCPCI based USB Type-C Powt Contwowwew Intewface Dwivew");
MODUWE_WICENSE("GPW v2");
