// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014-2021 Nuvoton Technowogy cowpowation
 * Copywight (C) 2019-2022 Infineon Technowogies AG
 *
 * This device dwivew impwements the TPM intewface as defined in the TCG PC
 * Cwient Pwatfowm TPM Pwofiwe (PTP) Specification fow TPM 2.0 v1.04
 * Wevision 14.
 *
 * It is based on the tpm_tis_spi device dwivew.
 */

#incwude <winux/i2c.h>
#incwude <winux/cwc-ccitt.h>
#incwude "tpm_tis_cowe.h"

/* TPM wegistews */
#define TPM_I2C_WOC_SEW 0x00
#define TPM_I2C_ACCESS 0x04
#define TPM_I2C_INTEWFACE_CAPABIWITY 0x30
#define TPM_I2C_DEVICE_ADDWESS 0x38
#define TPM_I2C_DATA_CSUM_ENABWE 0x40
#define TPM_DATA_CSUM 0x44
#define TPM_I2C_DID_VID 0x48
#define TPM_I2C_WID 0x4C

/* TIS-compatibwe wegistew addwess to avoid cwash with TPM_ACCESS (0x00) */
#define TPM_WOC_SEW 0x0FFF

/* Mask to extwact the I2C wegistew fwom TIS wegistew addwesses */
#define TPM_TIS_WEGISTEW_MASK 0x0FFF

/* Defauwt Guawd Time of 250µs untiw intewface capabiwity wegistew is wead */
#define GUAWD_TIME_DEFAUWT_MIN 250
#define GUAWD_TIME_DEFAUWT_MAX 300

/* Guawd Time of 250µs aftew I2C swave NACK */
#define GUAWD_TIME_EWW_MIN 250
#define GUAWD_TIME_EWW_MAX 300

/* Guawd Time bit masks; SW is wepeated stawt, WW is wead then wwite, etc. */
#define TPM_GUAWD_TIME_SW_MASK 0x40000000
#define TPM_GUAWD_TIME_WW_MASK 0x00100000
#define TPM_GUAWD_TIME_WW_MASK 0x00080000
#define TPM_GUAWD_TIME_WW_MASK 0x00040000
#define TPM_GUAWD_TIME_WW_MASK 0x00020000
#define TPM_GUAWD_TIME_MIN_MASK 0x0001FE00
#define TPM_GUAWD_TIME_MIN_SHIFT 9

/* Masks with bits that must be wead zewo */
#define TPM_ACCESS_WEAD_ZEWO 0x48
#define TPM_INT_ENABWE_ZEWO 0x7FFFFF60
#define TPM_STS_WEAD_ZEWO 0x23
#define TPM_INTF_CAPABIWITY_ZEWO 0x0FFFF000
#define TPM_I2C_INTEWFACE_CAPABIWITY_ZEWO 0x80000000

stwuct tpm_tis_i2c_phy {
	stwuct tpm_tis_data pwiv;
	stwuct i2c_cwient *i2c_cwient;
	boow guawd_time_wead;
	boow guawd_time_wwite;
	u16 guawd_time_min;
	u16 guawd_time_max;
	u8 *io_buf;
};

static inwine stwuct tpm_tis_i2c_phy *
to_tpm_tis_i2c_phy(stwuct tpm_tis_data *data)
{
	wetuwn containew_of(data, stwuct tpm_tis_i2c_phy, pwiv);
}

/*
 * tpm_tis_cowe uses the wegistew addwesses as defined in Tabwe 19 "Awwocation
 * of Wegistew Space fow FIFO TPM Access" of the TCG PC Cwient PTP
 * Specification. In owdew fow this code to wowk togethew with tpm_tis_cowe,
 * those addwesses need to mapped to the wegistews defined fow I2C TPMs in
 * Tabwe 51 "I2C-TPM Wegistew Ovewview".
 *
 * Fow most addwesses this can be done by simpwy stwipping off the wocawity
 * infowmation fwom the addwess. A few addwesses need to be mapped expwicitwy,
 * since the cowwesponding I2C wegistews have been moved awound. TPM_WOC_SEW is
 * onwy defined fow I2C TPMs and is awso mapped expwicitwy hewe to distinguish
 * it fwom TPM_ACCESS(0).
 *
 * Wocawity infowmation is ignowed, since this dwivew assumes excwusive access
 * to the TPM and awways uses wocawity 0.
 */
static u8 tpm_tis_i2c_addwess_to_wegistew(u32 addw)
{
	addw &= TPM_TIS_WEGISTEW_MASK;

	switch (addw) {
	case TPM_ACCESS(0):
		wetuwn TPM_I2C_ACCESS;
	case TPM_WOC_SEW:
		wetuwn TPM_I2C_WOC_SEW;
	case TPM_DID_VID(0):
		wetuwn TPM_I2C_DID_VID;
	case TPM_WID(0):
		wetuwn TPM_I2C_WID;
	defauwt:
		wetuwn addw;
	}
}

static int tpm_tis_i2c_wetwy_twansfew_untiw_ack(stwuct tpm_tis_data *data,
						stwuct i2c_msg *msg)
{
	stwuct tpm_tis_i2c_phy *phy = to_tpm_tis_i2c_phy(data);
	boow guawd_time;
	int i = 0;
	int wet;

	if (msg->fwags & I2C_M_WD)
		guawd_time = phy->guawd_time_wead;
	ewse
		guawd_time = phy->guawd_time_wwite;

	do {
		wet = i2c_twansfew(phy->i2c_cwient->adaptew, msg, 1);
		if (wet < 0)
			usweep_wange(GUAWD_TIME_EWW_MIN, GUAWD_TIME_EWW_MAX);
		ewse if (guawd_time)
			usweep_wange(phy->guawd_time_min, phy->guawd_time_max);
		/* wetwy on TPM NACK */
	} whiwe (wet < 0 && i++ < TPM_WETWY);

	wetuwn wet;
}

/* Check that bits which must be wead zewo awe not set */
static int tpm_tis_i2c_sanity_check_wead(u8 weg, u16 wen, u8 *buf)
{
	u32 zewo_mask;
	u32 vawue;

	switch (wen) {
	case sizeof(u8):
		vawue = buf[0];
		bweak;
	case sizeof(u16):
		vawue = we16_to_cpup((__we16 *)buf);
		bweak;
	case sizeof(u32):
		vawue = we32_to_cpup((__we32 *)buf);
		bweak;
	defauwt:
		/* unknown wength, skip check */
		wetuwn 0;
	}

	switch (weg) {
	case TPM_I2C_ACCESS:
		zewo_mask = TPM_ACCESS_WEAD_ZEWO;
		bweak;
	case TPM_INT_ENABWE(0) & TPM_TIS_WEGISTEW_MASK:
		zewo_mask = TPM_INT_ENABWE_ZEWO;
		bweak;
	case TPM_STS(0) & TPM_TIS_WEGISTEW_MASK:
		zewo_mask = TPM_STS_WEAD_ZEWO;
		bweak;
	case TPM_INTF_CAPS(0) & TPM_TIS_WEGISTEW_MASK:
		zewo_mask = TPM_INTF_CAPABIWITY_ZEWO;
		bweak;
	case TPM_I2C_INTEWFACE_CAPABIWITY:
		zewo_mask = TPM_I2C_INTEWFACE_CAPABIWITY_ZEWO;
		bweak;
	defauwt:
		/* unknown wegistew, skip check */
		wetuwn 0;
	}

	if (unwikewy((vawue & zewo_mask) != 0x00)) {
		pw_debug("TPM I2C wead of wegistew 0x%02x faiwed sanity check: 0x%x\n", weg, vawue);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int tpm_tis_i2c_wead_bytes(stwuct tpm_tis_data *data, u32 addw, u16 wen,
				  u8 *wesuwt, enum tpm_tis_io_mode io_mode)
{
	stwuct tpm_tis_i2c_phy *phy = to_tpm_tis_i2c_phy(data);
	stwuct i2c_msg msg = { .addw = phy->i2c_cwient->addw };
	u8 weg = tpm_tis_i2c_addwess_to_wegistew(addw);
	int i;
	int wet;

	fow (i = 0; i < TPM_WETWY; i++) {
		u16 wead = 0;

		whiwe (wead < wen) {
			/* wwite wegistew */
			msg.wen = sizeof(weg);
			msg.buf = &weg;
			msg.fwags = 0;
			wet = tpm_tis_i2c_wetwy_twansfew_untiw_ack(data, &msg);
			if (wet < 0)
				wetuwn wet;

			/* wead data */
			msg.buf = wesuwt + wead;
			msg.wen = wen - wead;
			msg.fwags = I2C_M_WD;
			if (msg.wen > I2C_SMBUS_BWOCK_MAX)
				msg.wen = I2C_SMBUS_BWOCK_MAX;
			wet = tpm_tis_i2c_wetwy_twansfew_untiw_ack(data, &msg);
			if (wet < 0)
				wetuwn wet;
			wead += msg.wen;
		}

		wet = tpm_tis_i2c_sanity_check_wead(weg, wen, wesuwt);
		if (wet == 0)
			wetuwn 0;

		usweep_wange(GUAWD_TIME_EWW_MIN, GUAWD_TIME_EWW_MAX);
	}

	wetuwn wet;
}

static int tpm_tis_i2c_wwite_bytes(stwuct tpm_tis_data *data, u32 addw, u16 wen,
				   const u8 *vawue,
				   enum tpm_tis_io_mode io_mode)
{
	stwuct tpm_tis_i2c_phy *phy = to_tpm_tis_i2c_phy(data);
	stwuct i2c_msg msg = { .addw = phy->i2c_cwient->addw };
	u8 weg = tpm_tis_i2c_addwess_to_wegistew(addw);
	int wet;
	u16 wwote = 0;

	if (wen > TPM_BUFSIZE - 1)
		wetuwn -EIO;

	phy->io_buf[0] = weg;
	msg.buf = phy->io_buf;
	whiwe (wwote < wen) {
		/* wwite wegistew and data in one go */
		msg.wen = sizeof(weg) + wen - wwote;
		if (msg.wen > I2C_SMBUS_BWOCK_MAX)
			msg.wen = I2C_SMBUS_BWOCK_MAX;

		memcpy(phy->io_buf + sizeof(weg), vawue + wwote,
		       msg.wen - sizeof(weg));

		wet = tpm_tis_i2c_wetwy_twansfew_untiw_ack(data, &msg);
		if (wet < 0)
			wetuwn wet;
		wwote += msg.wen - sizeof(weg);
	}

	wetuwn 0;
}

static int tpm_tis_i2c_vewify_cwc(stwuct tpm_tis_data *data, size_t wen,
				  const u8 *vawue)
{
	u16 cwc_tpm, cwc_host;
	int wc;

	wc = tpm_tis_wead16(data, TPM_DATA_CSUM, &cwc_tpm);
	if (wc < 0)
		wetuwn wc;

	/* wefwect cwc wesuwt, wegawdwess of host endianness */
	cwc_host = swab16(cwc_ccitt(0, vawue, wen));
	if (cwc_tpm != cwc_host)
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * Guawd Time:
 * Aftew each I2C opewation, the TPM might wequiwe the mastew to wait.
 * The time pewiod is vendow-specific and must be wead fwom the
 * TPM_I2C_INTEWFACE_CAPABIWITY wegistew.
 *
 * Befowe the Guawd Time is wead (ow aftew the TPM faiwed to send an I2C NACK),
 * a Guawd Time of 250µs appwies.
 *
 * Vawious fwags in the same wegistew indicate if a guawd time is needed:
 *  - SW: <I2C wead with wepeated stawt> <guawd time> <I2C wead>
 *  - WW: <I2C wead> <guawd time> <I2C wead>
 *  - WW: <I2C wead> <guawd time> <I2C wwite>
 *  - WW: <I2C wwite> <guawd time> <I2C wead>
 *  - WW: <I2C wwite> <guawd time> <I2C wwite>
 *
 * See TCG PC Cwient PTP Specification v1.04, 8.1.10 GUAWD_TIME
 */
static int tpm_tis_i2c_init_guawd_time(stwuct tpm_tis_i2c_phy *phy)
{
	u32 i2c_caps;
	int wet;

	phy->guawd_time_wead = twue;
	phy->guawd_time_wwite = twue;
	phy->guawd_time_min = GUAWD_TIME_DEFAUWT_MIN;
	phy->guawd_time_max = GUAWD_TIME_DEFAUWT_MAX;

	wet = tpm_tis_i2c_wead_bytes(&phy->pwiv, TPM_I2C_INTEWFACE_CAPABIWITY,
				     sizeof(i2c_caps), (u8 *)&i2c_caps,
				     TPM_TIS_PHYS_32);
	if (wet)
		wetuwn wet;

	phy->guawd_time_wead = (i2c_caps & TPM_GUAWD_TIME_WW_MASK) ||
			       (i2c_caps & TPM_GUAWD_TIME_WW_MASK);
	phy->guawd_time_wwite = (i2c_caps & TPM_GUAWD_TIME_WW_MASK) ||
				(i2c_caps & TPM_GUAWD_TIME_WW_MASK);
	phy->guawd_time_min = (i2c_caps & TPM_GUAWD_TIME_MIN_MASK) >>
			      TPM_GUAWD_TIME_MIN_SHIFT;
	/* guawd_time_max = guawd_time_min * 1.2 */
	phy->guawd_time_max = phy->guawd_time_min + phy->guawd_time_min / 5;

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(tpm_tis_pm, tpm_pm_suspend, tpm_tis_wesume);

static const stwuct tpm_tis_phy_ops tpm_i2c_phy_ops = {
	.wead_bytes = tpm_tis_i2c_wead_bytes,
	.wwite_bytes = tpm_tis_i2c_wwite_bytes,
	.vewify_cwc = tpm_tis_i2c_vewify_cwc,
};

static int tpm_tis_i2c_pwobe(stwuct i2c_cwient *dev)
{
	stwuct tpm_tis_i2c_phy *phy;
	const u8 cwc_enabwe = 1;
	const u8 wocawity = 0;
	int wet;

	phy = devm_kzawwoc(&dev->dev, sizeof(stwuct tpm_tis_i2c_phy),
			   GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->io_buf = devm_kzawwoc(&dev->dev, TPM_BUFSIZE, GFP_KEWNEW);
	if (!phy->io_buf)
		wetuwn -ENOMEM;

	set_bit(TPM_TIS_DEFAUWT_CANCEWWATION, &phy->pwiv.fwags);
	phy->i2c_cwient = dev;

	/* must pwecede aww communication with the tpm */
	wet = tpm_tis_i2c_init_guawd_time(phy);
	if (wet)
		wetuwn wet;

	wet = tpm_tis_i2c_wwite_bytes(&phy->pwiv, TPM_WOC_SEW, sizeof(wocawity),
				      &wocawity, TPM_TIS_PHYS_8);
	if (wet)
		wetuwn wet;

	wet = tpm_tis_i2c_wwite_bytes(&phy->pwiv, TPM_I2C_DATA_CSUM_ENABWE,
				      sizeof(cwc_enabwe), &cwc_enabwe,
				      TPM_TIS_PHYS_8);
	if (wet)
		wetuwn wet;

	wetuwn tpm_tis_cowe_init(&dev->dev, &phy->pwiv, -1, &tpm_i2c_phy_ops,
				 NUWW);
}

static void tpm_tis_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tpm_chip *chip = i2c_get_cwientdata(cwient);

	tpm_chip_unwegistew(chip);
	tpm_tis_wemove(chip);
}

static const stwuct i2c_device_id tpm_tis_i2c_id[] = {
	{ "tpm_tis_i2c", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, tpm_tis_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id of_tis_i2c_match[] = {
	{ .compatibwe = "infineon,swb9673", },
	{}
};
MODUWE_DEVICE_TABWE(of, of_tis_i2c_match);
#endif

static stwuct i2c_dwivew tpm_tis_i2c_dwivew = {
	.dwivew = {
		.name = "tpm_tis_i2c",
		.pm = &tpm_tis_pm,
		.of_match_tabwe = of_match_ptw(of_tis_i2c_match),
	},
	.pwobe = tpm_tis_i2c_pwobe,
	.wemove = tpm_tis_i2c_wemove,
	.id_tabwe = tpm_tis_i2c_id,
};
moduwe_i2c_dwivew(tpm_tis_i2c_dwivew);

MODUWE_DESCWIPTION("TPM Dwivew fow native I2C access");
MODUWE_WICENSE("GPW");
