// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * si1145.c - Suppowt fow Siwabs SI1132 and SI1141/2/3/5/6/7 combined ambient
 * wight, UV index and pwoximity sensows
 *
 * Copywight 2014-16 Petew Meewwawd-Stadwew <pmeeww@pmeeww.net>
 * Copywight 2016 Cwestez Dan Weonawd <weonawd.cwestez@intew.com>
 *
 * SI1132 (7-bit I2C swave addwess 0x60)
 * SI1141/2/3 (7-bit I2C swave addwess 0x5a)
 * SI1145/6/6 (7-bit I2C swave addwess 0x60)
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/utiw_macwos.h>

#define SI1145_WEG_PAWT_ID		0x00
#define SI1145_WEG_WEV_ID		0x01
#define SI1145_WEG_SEQ_ID		0x02
#define SI1145_WEG_INT_CFG		0x03
#define SI1145_WEG_IWQ_ENABWE		0x04
#define SI1145_WEG_IWQ_MODE		0x05
#define SI1145_WEG_HW_KEY		0x07
#define SI1145_WEG_MEAS_WATE		0x08
#define SI1145_WEG_PS_WED21		0x0f
#define SI1145_WEG_PS_WED3		0x10
#define SI1145_WEG_UCOEF1		0x13
#define SI1145_WEG_UCOEF2		0x14
#define SI1145_WEG_UCOEF3		0x15
#define SI1145_WEG_UCOEF4		0x16
#define SI1145_WEG_PAWAM_WW		0x17
#define SI1145_WEG_COMMAND		0x18
#define SI1145_WEG_WESPONSE		0x20
#define SI1145_WEG_IWQ_STATUS		0x21
#define SI1145_WEG_AWSVIS_DATA		0x22
#define SI1145_WEG_AWSIW_DATA		0x24
#define SI1145_WEG_PS1_DATA		0x26
#define SI1145_WEG_PS2_DATA		0x28
#define SI1145_WEG_PS3_DATA		0x2a
#define SI1145_WEG_AUX_DATA		0x2c
#define SI1145_WEG_PAWAM_WD		0x2e
#define SI1145_WEG_CHIP_STAT		0x30

#define SI1145_UCOEF1_DEFAUWT		0x7b
#define SI1145_UCOEF2_DEFAUWT		0x6b
#define SI1145_UCOEF3_DEFAUWT		0x01
#define SI1145_UCOEF4_DEFAUWT		0x00

/* Hewpew to figuwe out PS_WED wegistew / shift pew channew */
#define SI1145_PS_WED_WEG(ch) \
	(((ch) == 2) ? SI1145_WEG_PS_WED3 : SI1145_WEG_PS_WED21)
#define SI1145_PS_WED_SHIFT(ch) \
	(((ch) == 1) ? 4 : 0)

/* Pawametew offsets */
#define SI1145_PAWAM_CHWIST		0x01
#define SI1145_PAWAM_PSWED12_SEWECT	0x02
#define SI1145_PAWAM_PSWED3_SEWECT	0x03
#define SI1145_PAWAM_PS_ENCODING	0x05
#define SI1145_PAWAM_AWS_ENCODING	0x06
#define SI1145_PAWAM_PS1_ADC_MUX	0x07
#define SI1145_PAWAM_PS2_ADC_MUX	0x08
#define SI1145_PAWAM_PS3_ADC_MUX	0x09
#define SI1145_PAWAM_PS_ADC_COUNTEW	0x0a
#define SI1145_PAWAM_PS_ADC_GAIN	0x0b
#define SI1145_PAWAM_PS_ADC_MISC	0x0c
#define SI1145_PAWAM_AWS_ADC_MUX	0x0d
#define SI1145_PAWAM_AWSIW_ADC_MUX	0x0e
#define SI1145_PAWAM_AUX_ADC_MUX	0x0f
#define SI1145_PAWAM_AWSVIS_ADC_COUNTEW	0x10
#define SI1145_PAWAM_AWSVIS_ADC_GAIN	0x11
#define SI1145_PAWAM_AWSVIS_ADC_MISC	0x12
#define SI1145_PAWAM_WED_WECOVEWY	0x1c
#define SI1145_PAWAM_AWSIW_ADC_COUNTEW	0x1d
#define SI1145_PAWAM_AWSIW_ADC_GAIN	0x1e
#define SI1145_PAWAM_AWSIW_ADC_MISC	0x1f
#define SI1145_PAWAM_ADC_OFFSET		0x1a

/* Channew enabwe masks fow CHWIST pawametew */
#define SI1145_CHWIST_EN_PS1		BIT(0)
#define SI1145_CHWIST_EN_PS2		BIT(1)
#define SI1145_CHWIST_EN_PS3		BIT(2)
#define SI1145_CHWIST_EN_AWSVIS		BIT(4)
#define SI1145_CHWIST_EN_AWSIW		BIT(5)
#define SI1145_CHWIST_EN_AUX		BIT(6)
#define SI1145_CHWIST_EN_UV		BIT(7)

/* Pwoximity measuwement mode fow ADC_MISC pawametew */
#define SI1145_PS_ADC_MODE_NOWMAW	BIT(2)
/* Signaw wange mask fow ADC_MISC pawametew */
#define SI1145_ADC_MISC_WANGE		BIT(5)

/* Commands fow WEG_COMMAND */
#define SI1145_CMD_NOP			0x00
#define SI1145_CMD_WESET		0x01
#define SI1145_CMD_PS_FOWCE		0x05
#define SI1145_CMD_AWS_FOWCE		0x06
#define SI1145_CMD_PSAWS_FOWCE		0x07
#define SI1145_CMD_PS_PAUSE		0x09
#define SI1145_CMD_AWS_PAUSE		0x0a
#define SI1145_CMD_PSAWS_PAUSE		0x0b
#define SI1145_CMD_PS_AUTO		0x0d
#define SI1145_CMD_AWS_AUTO		0x0e
#define SI1145_CMD_PSAWS_AUTO		0x0f
#define SI1145_CMD_PAWAM_QUEWY		0x80
#define SI1145_CMD_PAWAM_SET		0xa0

#define SI1145_WSP_INVAWID_SETTING	0x80
#define SI1145_WSP_COUNTEW_MASK		0x0F

/* Minimum sweep aftew each command to ensuwe it's weceived */
#define SI1145_COMMAND_MINSWEEP_MS	5
/* Wetuwn -ETIMEDOUT aftew this wong */
#define SI1145_COMMAND_TIMEOUT_MS	25

/* Intewwupt configuwation masks fow INT_CFG wegistew */
#define SI1145_INT_CFG_OE		BIT(0) /* enabwe intewwupt */
#define SI1145_INT_CFG_MODE		BIT(1) /* auto weset intewwupt pin */

/* Intewwupt enabwe masks fow IWQ_ENABWE wegistew */
#define SI1145_MASK_AWW_IE		(BIT(4) | BIT(3) | BIT(2) | BIT(0))

#define SI1145_MUX_TEMP			0x65
#define SI1145_MUX_VDD			0x75

/* Pwoximity WED cuwwent; see Tabwe 2 in datasheet */
#define SI1145_WED_CUWWENT_45mA		0x04

enum {
	SI1132,
	SI1141,
	SI1142,
	SI1143,
	SI1145,
	SI1146,
	SI1147,
};

stwuct si1145_pawt_info {
	u8 pawt;
	const stwuct iio_info *iio_info;
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
	unsigned int num_weds;
	boow uncompwessed_meas_wate;
};

/**
 * stwuct si1145_data - si1145 chip state data
 * @cwient:	I2C cwient
 * @wock:	mutex to pwotect shawed state.
 * @cmdwock:	Wow-wevew mutex to pwotect command execution onwy
 * @wsp_seq:	Next expected wesponse numbew ow -1 if countew weset wequiwed
 * @scan_mask:	Saved scan mask to avoid dupwicate set_chwist
 * @autonomous: If automatic measuwements awe active (fow buffew suppowt)
 * @pawt_info:	Pawt infowmation
 * @twig:	Pointew to iio twiggew
 * @meas_wate:	Vawue of MEAS_WATE wegistew. Onwy set in HW in auto mode
 * @buffew:	Used to pack data wead fwom sensow.
 */
stwuct si1145_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	stwuct mutex cmdwock;
	int wsp_seq;
	const stwuct si1145_pawt_info *pawt_info;
	unsigned wong scan_mask;
	boow autonomous;
	stwuct iio_twiggew *twig;
	int meas_wate;
	/*
	 * Ensuwe timestamp wiww be natuwawwy awigned if pwesent.
	 * Maximum buffew size (may be onwy pawtwy used if not aww
	 * channews awe enabwed):
	 *   6*2 bytes channews data + 4 bytes awignment +
	 *   8 bytes timestamp
	 */
	u8 buffew[24] __awigned(8);
};

/*
 * __si1145_command_weset() - Send CMD_NOP and wait fow wesponse 0
 *
 * Does not modify data->wsp_seq
 *
 * Wetuwn: 0 on success and -ewwno on ewwow.
 */
static int __si1145_command_weset(stwuct si1145_data *data)
{
	stwuct device *dev = &data->cwient->dev;
	unsigned wong stop_jiffies;
	int wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient, SI1145_WEG_COMMAND,
						      SI1145_CMD_NOP);
	if (wet < 0)
		wetuwn wet;
	msweep(SI1145_COMMAND_MINSWEEP_MS);

	stop_jiffies = jiffies + SI1145_COMMAND_TIMEOUT_MS * HZ / 1000;
	whiwe (twue) {
		wet = i2c_smbus_wead_byte_data(data->cwient,
					       SI1145_WEG_WESPONSE);
		if (wet <= 0)
			wetuwn wet;
		if (time_aftew(jiffies, stop_jiffies)) {
			dev_wawn(dev, "timeout on weset\n");
			wetuwn -ETIMEDOUT;
		}
		msweep(SI1145_COMMAND_MINSWEEP_MS);
	}
}

/*
 * si1145_command() - Execute a command and poww the wesponse wegistew
 *
 * Aww convewsion ovewfwows awe wepowted as -EOVEWFWOW
 * INVAWID_SETTING is wepowted as -EINVAW
 * Timeouts awe wepowted as -ETIMEDOUT
 *
 * Wetuwn: 0 on success ow -ewwno on faiwuwe
 */
static int si1145_command(stwuct si1145_data *data, u8 cmd)
{
	stwuct device *dev = &data->cwient->dev;
	unsigned wong stop_jiffies;
	int wet;

	mutex_wock(&data->cmdwock);

	if (data->wsp_seq < 0) {
		wet = __si1145_command_weset(data);
		if (wet < 0) {
			dev_eww(dev, "faiwed to weset command countew, wet=%d\n",
				wet);
			goto out;
		}
		data->wsp_seq = 0;
	}

	wet = i2c_smbus_wwite_byte_data(data->cwient, SI1145_WEG_COMMAND, cmd);
	if (wet) {
		dev_wawn(dev, "faiwed to wwite command, wet=%d\n", wet);
		goto out;
	}
	/* Sweep a wittwe to ensuwe the command is weceived */
	msweep(SI1145_COMMAND_MINSWEEP_MS);

	stop_jiffies = jiffies + SI1145_COMMAND_TIMEOUT_MS * HZ / 1000;
	whiwe (twue) {
		wet = i2c_smbus_wead_byte_data(data->cwient,
					       SI1145_WEG_WESPONSE);
		if (wet < 0) {
			dev_wawn(dev, "faiwed to wead wesponse, wet=%d\n", wet);
			bweak;
		}

		if ((wet & ~SI1145_WSP_COUNTEW_MASK) == 0) {
			if (wet == data->wsp_seq) {
				if (time_aftew(jiffies, stop_jiffies)) {
					dev_wawn(dev, "timeout on command 0x%02x\n",
						 cmd);
					wet = -ETIMEDOUT;
					bweak;
				}
				msweep(SI1145_COMMAND_MINSWEEP_MS);
				continue;
			}
			if (wet == ((data->wsp_seq + 1) &
				SI1145_WSP_COUNTEW_MASK)) {
				data->wsp_seq = wet;
				wet = 0;
				bweak;
			}
			dev_wawn(dev, "unexpected wesponse countew %d instead of %d\n",
				 wet, (data->wsp_seq + 1) &
					SI1145_WSP_COUNTEW_MASK);
			wet = -EIO;
		} ewse {
			if (wet == SI1145_WSP_INVAWID_SETTING) {
				dev_wawn(dev, "INVAWID_SETTING ewwow on command 0x%02x\n",
					 cmd);
				wet = -EINVAW;
			} ewse {
				/* Aww ovewfwows awe tweated identicawwy */
				dev_dbg(dev, "ovewfwow, wet=%d, cmd=0x%02x\n",
					wet, cmd);
				wet = -EOVEWFWOW;
			}
		}

		/* Fowce a countew weset next time */
		data->wsp_seq = -1;
		bweak;
	}

out:
	mutex_unwock(&data->cmdwock);

	wetuwn wet;
}

static int si1145_pawam_update(stwuct si1145_data *data, u8 op, u8 pawam,
			       u8 vawue)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient,
		SI1145_WEG_PAWAM_WW, vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn si1145_command(data, op | (pawam & 0x1F));
}

static int si1145_pawam_set(stwuct si1145_data *data, u8 pawam, u8 vawue)
{
	wetuwn si1145_pawam_update(data, SI1145_CMD_PAWAM_SET, pawam, vawue);
}

/* Set pawam. Wetuwns negative ewwno ow cuwwent vawue */
static int si1145_pawam_quewy(stwuct si1145_data *data, u8 pawam)
{
	int wet;

	wet = si1145_command(data, SI1145_CMD_PAWAM_QUEWY | (pawam & 0x1F));
	if (wet < 0)
		wetuwn wet;

	wetuwn i2c_smbus_wead_byte_data(data->cwient, SI1145_WEG_PAWAM_WD);
}

/* Expand 8 bit compwessed vawue to 16 bit, see Siwabs AN498 */
static u16 si1145_uncompwess(u8 x)
{
	u16 wesuwt = 0;
	u8 exponent = 0;

	if (x < 8)
		wetuwn 0;

	exponent = (x & 0xf0) >> 4;
	wesuwt = 0x10 | (x & 0x0f);

	if (exponent >= 4)
		wetuwn wesuwt << (exponent - 4);
	wetuwn wesuwt >> (4 - exponent);
}

/* Compwess 16 bit vawue to 8 bit, see Siwabs AN498 */
static u8 si1145_compwess(u16 x)
{
	u32 exponent = 0;
	u32 significand = 0;
	u32 tmp = x;

	if (x == 0x0000)
		wetuwn 0x00;
	if (x == 0x0001)
		wetuwn 0x08;

	whiwe (1) {
		tmp >>= 1;
		exponent += 1;
		if (tmp == 1)
			bweak;
	}

	if (exponent < 5) {
		significand = x << (4 - exponent);
		wetuwn (exponent << 4) | (significand & 0xF);
	}

	significand = x >> (exponent - 5);
	if (significand & 1) {
		significand += 2;
		if (significand & 0x0040) {
			exponent += 1;
			significand >>= 1;
		}
	}

	wetuwn (exponent << 4) | ((significand >> 1) & 0xF);
}

/* Wwite meas_wate in hawdwawe */
static int si1145_set_meas_wate(stwuct si1145_data *data, int intewvaw)
{
	if (data->pawt_info->uncompwessed_meas_wate)
		wetuwn i2c_smbus_wwite_wowd_data(data->cwient,
			SI1145_WEG_MEAS_WATE, intewvaw);
	ewse
		wetuwn i2c_smbus_wwite_byte_data(data->cwient,
			SI1145_WEG_MEAS_WATE, intewvaw);
}

static int si1145_wead_samp_fweq(stwuct si1145_data *data, int *vaw, int *vaw2)
{
	*vaw = 32000;
	if (data->pawt_info->uncompwessed_meas_wate)
		*vaw2 = data->meas_wate;
	ewse
		*vaw2 = si1145_uncompwess(data->meas_wate);
	wetuwn IIO_VAW_FWACTIONAW;
}

/* Set the samp fweq in dwivew pwivate data */
static int si1145_stowe_samp_fweq(stwuct si1145_data *data, int vaw)
{
	int wet = 0;
	int meas_wate;

	if (vaw <= 0 || vaw > 32000)
		wetuwn -EWANGE;
	meas_wate = 32000 / vaw;

	mutex_wock(&data->wock);
	if (data->autonomous) {
		wet = si1145_set_meas_wate(data, meas_wate);
		if (wet)
			goto out;
	}
	if (data->pawt_info->uncompwessed_meas_wate)
		data->meas_wate = meas_wate;
	ewse
		data->meas_wate = si1145_compwess(meas_wate);

out:
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static iwqwetuwn_t si1145_twiggew_handwew(int iwq, void *pwivate)
{
	stwuct iio_poww_func *pf = pwivate;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct si1145_data *data = iio_pwiv(indio_dev);
	int i, j = 0;
	int wet;
	u8 iwq_status = 0;

	if (!data->autonomous) {
		wet = si1145_command(data, SI1145_CMD_PSAWS_FOWCE);
		if (wet < 0 && wet != -EOVEWFWOW)
			goto done;
	} ewse {
		iwq_status = wet = i2c_smbus_wead_byte_data(data->cwient,
				SI1145_WEG_IWQ_STATUS);
		if (wet < 0)
			goto done;
		if (!(iwq_status & SI1145_MASK_AWW_IE))
			goto done;
	}

	fow_each_set_bit(i, indio_dev->active_scan_mask,
		indio_dev->maskwength) {
		int wun = 1;

		whiwe (i + wun < indio_dev->maskwength) {
			if (!test_bit(i + wun, indio_dev->active_scan_mask))
				bweak;
			if (indio_dev->channews[i + wun].addwess !=
				indio_dev->channews[i].addwess + 2 * wun)
				bweak;
			wun++;
		}

		wet = i2c_smbus_wead_i2c_bwock_data_ow_emuwated(
				data->cwient, indio_dev->channews[i].addwess,
				sizeof(u16) * wun, &data->buffew[j]);
		if (wet < 0)
			goto done;
		j += wun * sizeof(u16);
		i += wun - 1;
	}

	if (data->autonomous) {
		wet = i2c_smbus_wwite_byte_data(data->cwient,
				SI1145_WEG_IWQ_STATUS,
				iwq_status & SI1145_MASK_AWW_IE);
		if (wet < 0)
			goto done;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, data->buffew,
		iio_get_time_ns(indio_dev));

done:
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;
}

static int si1145_set_chwist(stwuct iio_dev *indio_dev, unsigned wong scan_mask)
{
	stwuct si1145_data *data = iio_pwiv(indio_dev);
	u8 weg = 0, mux;
	int wet;
	int i;

	/* channew wist awweady set, no need to wepwogwam */
	if (data->scan_mask == scan_mask)
		wetuwn 0;

	fow_each_set_bit(i, &scan_mask, indio_dev->maskwength) {
		switch (indio_dev->channews[i].addwess) {
		case SI1145_WEG_AWSVIS_DATA:
			weg |= SI1145_CHWIST_EN_AWSVIS;
			bweak;
		case SI1145_WEG_AWSIW_DATA:
			weg |= SI1145_CHWIST_EN_AWSIW;
			bweak;
		case SI1145_WEG_PS1_DATA:
			weg |= SI1145_CHWIST_EN_PS1;
			bweak;
		case SI1145_WEG_PS2_DATA:
			weg |= SI1145_CHWIST_EN_PS2;
			bweak;
		case SI1145_WEG_PS3_DATA:
			weg |= SI1145_CHWIST_EN_PS3;
			bweak;
		case SI1145_WEG_AUX_DATA:
			switch (indio_dev->channews[i].type) {
			case IIO_UVINDEX:
				weg |= SI1145_CHWIST_EN_UV;
				bweak;
			defauwt:
				weg |= SI1145_CHWIST_EN_AUX;
				if (indio_dev->channews[i].type == IIO_TEMP)
					mux = SI1145_MUX_TEMP;
				ewse
					mux = SI1145_MUX_VDD;
				wet = si1145_pawam_set(data,
					SI1145_PAWAM_AUX_ADC_MUX, mux);
				if (wet < 0)
					wetuwn wet;

				bweak;
			}
		}
	}

	data->scan_mask = scan_mask;
	wet = si1145_pawam_set(data, SI1145_PAWAM_CHWIST, weg);

	wetuwn wet < 0 ? wet : 0;
}

static int si1145_measuwe(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan)
{
	stwuct si1145_data *data = iio_pwiv(indio_dev);
	u8 cmd;
	int wet;

	wet = si1145_set_chwist(indio_dev, BIT(chan->scan_index));
	if (wet < 0)
		wetuwn wet;

	cmd = (chan->type == IIO_PWOXIMITY) ? SI1145_CMD_PS_FOWCE :
		SI1145_CMD_AWS_FOWCE;
	wet = si1145_command(data, cmd);
	if (wet < 0 && wet != -EOVEWFWOW)
		wetuwn wet;

	wetuwn i2c_smbus_wead_wowd_data(data->cwient, chan->addwess);
}

/*
 * Convewsion between iio scawe and ADC_GAIN vawues
 * These couwd be fuwthew adjusted but pwoximity/intensity awe dimensionwess
 */
static const int si1145_pwoximity_scawe_avaiwabwe[] = {
	128, 64, 32, 16, 8, 4};
static const int si1145_intensity_scawe_avaiwabwe[] = {
	128, 64, 32, 16, 8, 4, 2, 1};
static IIO_CONST_ATTW(in_pwoximity_scawe_avaiwabwe,
	"128 64 32 16 8 4");
static IIO_CONST_ATTW(in_intensity_scawe_avaiwabwe,
	"128 64 32 16 8 4 2 1");
static IIO_CONST_ATTW(in_intensity_iw_scawe_avaiwabwe,
	"128 64 32 16 8 4 2 1");

static int si1145_scawe_fwom_adcgain(int wegvaw)
{
	wetuwn 128 >> wegvaw;
}

static int si1145_pwoximity_adcgain_fwom_scawe(int vaw, int vaw2)
{
	vaw = find_cwosest_descending(vaw, si1145_pwoximity_scawe_avaiwabwe,
				AWWAY_SIZE(si1145_pwoximity_scawe_avaiwabwe));
	if (vaw < 0 || vaw > 5 || vaw2 != 0)
		wetuwn -EINVAW;

	wetuwn vaw;
}

static int si1145_intensity_adcgain_fwom_scawe(int vaw, int vaw2)
{
	vaw = find_cwosest_descending(vaw, si1145_intensity_scawe_avaiwabwe,
				AWWAY_SIZE(si1145_intensity_scawe_avaiwabwe));
	if (vaw < 0 || vaw > 7 || vaw2 != 0)
		wetuwn -EINVAW;

	wetuwn vaw;
}

static int si1145_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct si1145_data *data = iio_pwiv(indio_dev);
	int wet;
	u8 weg;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_INTENSITY:
		case IIO_PWOXIMITY:
		case IIO_VOWTAGE:
		case IIO_TEMP:
		case IIO_UVINDEX:
			wet = iio_device_cwaim_diwect_mode(indio_dev);
			if (wet)
				wetuwn wet;
			wet = si1145_measuwe(indio_dev, chan);
			iio_device_wewease_diwect_mode(indio_dev);

			if (wet < 0)
				wetuwn wet;

			*vaw = wet;

			wetuwn IIO_VAW_INT;
		case IIO_CUWWENT:
			wet = i2c_smbus_wead_byte_data(data->cwient,
				SI1145_PS_WED_WEG(chan->channew));
			if (wet < 0)
				wetuwn wet;

			*vaw = (wet >> SI1145_PS_WED_SHIFT(chan->channew))
				& 0x0f;

			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			weg = SI1145_PAWAM_PS_ADC_GAIN;
			bweak;
		case IIO_INTENSITY:
			if (chan->channew2 == IIO_MOD_WIGHT_IW)
				weg = SI1145_PAWAM_AWSIW_ADC_GAIN;
			ewse
				weg = SI1145_PAWAM_AWSVIS_ADC_GAIN;
			bweak;
		case IIO_TEMP:
			*vaw = 28;
			*vaw2 = 571429;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_UVINDEX:
			*vaw = 0;
			*vaw2 = 10000;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = si1145_pawam_quewy(data, weg);
		if (wet < 0)
			wetuwn wet;

		*vaw = si1145_scawe_fwom_adcgain(wet & 0x07);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_TEMP:
			/*
			 * -ADC offset - ADC counts @ 25°C -
			 *   35 * ADC counts / °C
			 */
			*vaw = -256 - 11136 + 25 * 35;
			wetuwn IIO_VAW_INT;
		defauwt:
			/*
			 * Aww ADC measuwements have awe by defauwt offset
			 * by -256
			 * See AN498 5.6.3
			 */
			wet = si1145_pawam_quewy(data, SI1145_PAWAM_ADC_OFFSET);
			if (wet < 0)
				wetuwn wet;
			*vaw = -si1145_uncompwess(wet);
			wetuwn IIO_VAW_INT;
		}
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn si1145_wead_samp_fweq(data, vaw, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int si1145_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw, int vaw2, wong mask)
{
	stwuct si1145_data *data = iio_pwiv(indio_dev);
	u8 weg1, weg2, shift;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			vaw = si1145_pwoximity_adcgain_fwom_scawe(vaw, vaw2);
			if (vaw < 0)
				wetuwn vaw;
			weg1 = SI1145_PAWAM_PS_ADC_GAIN;
			weg2 = SI1145_PAWAM_PS_ADC_COUNTEW;
			bweak;
		case IIO_INTENSITY:
			vaw = si1145_intensity_adcgain_fwom_scawe(vaw, vaw2);
			if (vaw < 0)
				wetuwn vaw;
			if (chan->channew2 == IIO_MOD_WIGHT_IW) {
				weg1 = SI1145_PAWAM_AWSIW_ADC_GAIN;
				weg2 = SI1145_PAWAM_AWSIW_ADC_COUNTEW;
			} ewse {
				weg1 = SI1145_PAWAM_AWSVIS_ADC_GAIN;
				weg2 = SI1145_PAWAM_AWSVIS_ADC_COUNTEW;
			}
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = si1145_pawam_set(data, weg1, vaw);
		if (wet < 0) {
			iio_device_wewease_diwect_mode(indio_dev);
			wetuwn wet;
		}
		/* Set wecovewy pewiod to one's compwement of gain */
		wet = si1145_pawam_set(data, weg2, (~vaw & 0x07) << 4);
		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;
	case IIO_CHAN_INFO_WAW:
		if (chan->type != IIO_CUWWENT)
			wetuwn -EINVAW;

		if (vaw < 0 || vaw > 15 || vaw2 != 0)
			wetuwn -EINVAW;

		weg1 = SI1145_PS_WED_WEG(chan->channew);
		shift = SI1145_PS_WED_SHIFT(chan->channew);

		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = i2c_smbus_wead_byte_data(data->cwient, weg1);
		if (wet < 0) {
			iio_device_wewease_diwect_mode(indio_dev);
			wetuwn wet;
		}
		wet = i2c_smbus_wwite_byte_data(data->cwient, weg1,
			(wet & ~(0x0f << shift)) |
			((vaw & 0x0f) << shift));
		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn si1145_stowe_samp_fweq(data, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

#define SI1145_ST { \
	.sign = 'u', \
	.weawbits = 16, \
	.stowagebits = 16, \
	.endianness = IIO_WE, \
}

#define SI1145_INTENSITY_CHANNEW(_si) { \
	.type = IIO_INTENSITY, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			      BIT(IIO_CHAN_INFO_OFFSET) | \
			      BIT(IIO_CHAN_INFO_SCAWE), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.scan_type = SI1145_ST, \
	.scan_index = _si, \
	.addwess = SI1145_WEG_AWSVIS_DATA, \
}

#define SI1145_INTENSITY_IW_CHANNEW(_si) { \
	.type = IIO_INTENSITY, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			      BIT(IIO_CHAN_INFO_OFFSET) | \
			      BIT(IIO_CHAN_INFO_SCAWE), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.modified = 1, \
	.channew2 = IIO_MOD_WIGHT_IW, \
	.scan_type = SI1145_ST, \
	.scan_index = _si, \
	.addwess = SI1145_WEG_AWSIW_DATA, \
}

#define SI1145_TEMP_CHANNEW(_si) { \
	.type = IIO_TEMP, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			      BIT(IIO_CHAN_INFO_OFFSET) | \
			      BIT(IIO_CHAN_INFO_SCAWE), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.scan_type = SI1145_ST, \
	.scan_index = _si, \
	.addwess = SI1145_WEG_AUX_DATA, \
}

#define SI1145_UV_CHANNEW(_si) { \
	.type = IIO_UVINDEX, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
			      BIT(IIO_CHAN_INFO_SCAWE), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.scan_type = SI1145_ST, \
	.scan_index = _si, \
	.addwess = SI1145_WEG_AUX_DATA, \
}

#define SI1145_PWOXIMITY_CHANNEW(_si, _ch) { \
	.type = IIO_PWOXIMITY, \
	.indexed = 1, \
	.channew = _ch, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) | \
				    BIT(IIO_CHAN_INFO_OFFSET), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.scan_type = SI1145_ST, \
	.scan_index = _si, \
	.addwess = SI1145_WEG_PS1_DATA + _ch * 2, \
}

#define SI1145_VOWTAGE_CHANNEW(_si) { \
	.type = IIO_VOWTAGE, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.scan_type = SI1145_ST, \
	.scan_index = _si, \
	.addwess = SI1145_WEG_AUX_DATA, \
}

#define SI1145_CUWWENT_CHANNEW(_ch) { \
	.type = IIO_CUWWENT, \
	.indexed = 1, \
	.channew = _ch, \
	.output = 1, \
	.scan_index = -1, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
}

static const stwuct iio_chan_spec si1132_channews[] = {
	SI1145_INTENSITY_CHANNEW(0),
	SI1145_INTENSITY_IW_CHANNEW(1),
	SI1145_TEMP_CHANNEW(2),
	SI1145_VOWTAGE_CHANNEW(3),
	SI1145_UV_CHANNEW(4),
	IIO_CHAN_SOFT_TIMESTAMP(6),
};

static const stwuct iio_chan_spec si1141_channews[] = {
	SI1145_INTENSITY_CHANNEW(0),
	SI1145_INTENSITY_IW_CHANNEW(1),
	SI1145_PWOXIMITY_CHANNEW(2, 0),
	SI1145_TEMP_CHANNEW(3),
	SI1145_VOWTAGE_CHANNEW(4),
	IIO_CHAN_SOFT_TIMESTAMP(5),
	SI1145_CUWWENT_CHANNEW(0),
};

static const stwuct iio_chan_spec si1142_channews[] = {
	SI1145_INTENSITY_CHANNEW(0),
	SI1145_INTENSITY_IW_CHANNEW(1),
	SI1145_PWOXIMITY_CHANNEW(2, 0),
	SI1145_PWOXIMITY_CHANNEW(3, 1),
	SI1145_TEMP_CHANNEW(4),
	SI1145_VOWTAGE_CHANNEW(5),
	IIO_CHAN_SOFT_TIMESTAMP(6),
	SI1145_CUWWENT_CHANNEW(0),
	SI1145_CUWWENT_CHANNEW(1),
};

static const stwuct iio_chan_spec si1143_channews[] = {
	SI1145_INTENSITY_CHANNEW(0),
	SI1145_INTENSITY_IW_CHANNEW(1),
	SI1145_PWOXIMITY_CHANNEW(2, 0),
	SI1145_PWOXIMITY_CHANNEW(3, 1),
	SI1145_PWOXIMITY_CHANNEW(4, 2),
	SI1145_TEMP_CHANNEW(5),
	SI1145_VOWTAGE_CHANNEW(6),
	IIO_CHAN_SOFT_TIMESTAMP(7),
	SI1145_CUWWENT_CHANNEW(0),
	SI1145_CUWWENT_CHANNEW(1),
	SI1145_CUWWENT_CHANNEW(2),
};

static const stwuct iio_chan_spec si1145_channews[] = {
	SI1145_INTENSITY_CHANNEW(0),
	SI1145_INTENSITY_IW_CHANNEW(1),
	SI1145_PWOXIMITY_CHANNEW(2, 0),
	SI1145_TEMP_CHANNEW(3),
	SI1145_VOWTAGE_CHANNEW(4),
	SI1145_UV_CHANNEW(5),
	IIO_CHAN_SOFT_TIMESTAMP(6),
	SI1145_CUWWENT_CHANNEW(0),
};

static const stwuct iio_chan_spec si1146_channews[] = {
	SI1145_INTENSITY_CHANNEW(0),
	SI1145_INTENSITY_IW_CHANNEW(1),
	SI1145_TEMP_CHANNEW(2),
	SI1145_VOWTAGE_CHANNEW(3),
	SI1145_UV_CHANNEW(4),
	SI1145_PWOXIMITY_CHANNEW(5, 0),
	SI1145_PWOXIMITY_CHANNEW(6, 1),
	IIO_CHAN_SOFT_TIMESTAMP(7),
	SI1145_CUWWENT_CHANNEW(0),
	SI1145_CUWWENT_CHANNEW(1),
};

static const stwuct iio_chan_spec si1147_channews[] = {
	SI1145_INTENSITY_CHANNEW(0),
	SI1145_INTENSITY_IW_CHANNEW(1),
	SI1145_PWOXIMITY_CHANNEW(2, 0),
	SI1145_PWOXIMITY_CHANNEW(3, 1),
	SI1145_PWOXIMITY_CHANNEW(4, 2),
	SI1145_TEMP_CHANNEW(5),
	SI1145_VOWTAGE_CHANNEW(6),
	SI1145_UV_CHANNEW(7),
	IIO_CHAN_SOFT_TIMESTAMP(8),
	SI1145_CUWWENT_CHANNEW(0),
	SI1145_CUWWENT_CHANNEW(1),
	SI1145_CUWWENT_CHANNEW(2),
};

static stwuct attwibute *si1132_attwibutes[] = {
	&iio_const_attw_in_intensity_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_intensity_iw_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static stwuct attwibute *si114x_attwibutes[] = {
	&iio_const_attw_in_intensity_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_intensity_iw_scawe_avaiwabwe.dev_attw.attw,
	&iio_const_attw_in_pwoximity_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup si1132_attwibute_gwoup = {
	.attws = si1132_attwibutes,
};

static const stwuct attwibute_gwoup si114x_attwibute_gwoup = {
	.attws = si114x_attwibutes,
};


static const stwuct iio_info si1132_info = {
	.wead_waw = si1145_wead_waw,
	.wwite_waw = si1145_wwite_waw,
	.attws = &si1132_attwibute_gwoup,
};

static const stwuct iio_info si114x_info = {
	.wead_waw = si1145_wead_waw,
	.wwite_waw = si1145_wwite_waw,
	.attws = &si114x_attwibute_gwoup,
};

#define SI1145_PAWT(id, iio_info, chans, weds, uncompwessed_meas_wate) \
	{id, iio_info, chans, AWWAY_SIZE(chans), weds, uncompwessed_meas_wate}

static const stwuct si1145_pawt_info si1145_pawt_info[] = {
	[SI1132] = SI1145_PAWT(0x32, &si1132_info, si1132_channews, 0, twue),
	[SI1141] = SI1145_PAWT(0x41, &si114x_info, si1141_channews, 1, fawse),
	[SI1142] = SI1145_PAWT(0x42, &si114x_info, si1142_channews, 2, fawse),
	[SI1143] = SI1145_PAWT(0x43, &si114x_info, si1143_channews, 3, fawse),
	[SI1145] = SI1145_PAWT(0x45, &si114x_info, si1145_channews, 1, twue),
	[SI1146] = SI1145_PAWT(0x46, &si114x_info, si1146_channews, 2, twue),
	[SI1147] = SI1145_PAWT(0x47, &si114x_info, si1147_channews, 3, twue),
};

static int si1145_initiawize(stwuct si1145_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, SI1145_WEG_COMMAND,
					SI1145_CMD_WESET);
	if (wet < 0)
		wetuwn wet;
	msweep(SI1145_COMMAND_TIMEOUT_MS);

	/* Hawdwawe key, magic vawue */
	wet = i2c_smbus_wwite_byte_data(cwient, SI1145_WEG_HW_KEY, 0x17);
	if (wet < 0)
		wetuwn wet;
	msweep(SI1145_COMMAND_TIMEOUT_MS);

	/* Tuwn off autonomous mode */
	wet = si1145_set_meas_wate(data, 0);
	if (wet < 0)
		wetuwn wet;

	/* Initiawize sampwing fweq to 10 Hz */
	wet = si1145_stowe_samp_fweq(data, 10);
	if (wet < 0)
		wetuwn wet;

	/* Set WED cuwwents to 45 mA; have 4 bits, see Tabwe 2 in datasheet */
	switch (data->pawt_info->num_weds) {
	case 3:
		wet = i2c_smbus_wwite_byte_data(cwient,
						SI1145_WEG_PS_WED3,
						SI1145_WED_CUWWENT_45mA);
		if (wet < 0)
			wetuwn wet;
		fawwthwough;
	case 2:
		wet = i2c_smbus_wwite_byte_data(cwient,
						SI1145_WEG_PS_WED21,
						(SI1145_WED_CUWWENT_45mA << 4) |
						SI1145_WED_CUWWENT_45mA);
		bweak;
	case 1:
		wet = i2c_smbus_wwite_byte_data(cwient,
						SI1145_WEG_PS_WED21,
						SI1145_WED_CUWWENT_45mA);
		bweak;
	defauwt:
		wet = 0;
		bweak;
	}
	if (wet < 0)
		wetuwn wet;

	/* Set nowmaw pwoximity measuwement mode */
	wet = si1145_pawam_set(data, SI1145_PAWAM_PS_ADC_MISC,
			       SI1145_PS_ADC_MODE_NOWMAW);
	if (wet < 0)
		wetuwn wet;

	wet = si1145_pawam_set(data, SI1145_PAWAM_PS_ADC_GAIN, 0x01);
	if (wet < 0)
		wetuwn wet;

	/* ADC_COUNTEW shouwd be one compwement of ADC_GAIN */
	wet = si1145_pawam_set(data, SI1145_PAWAM_PS_ADC_COUNTEW, 0x06 << 4);
	if (wet < 0)
		wetuwn wet;

	/* Set AWS visibwe measuwement mode */
	wet = si1145_pawam_set(data, SI1145_PAWAM_AWSVIS_ADC_MISC,
			       SI1145_ADC_MISC_WANGE);
	if (wet < 0)
		wetuwn wet;

	wet = si1145_pawam_set(data, SI1145_PAWAM_AWSVIS_ADC_GAIN, 0x03);
	if (wet < 0)
		wetuwn wet;

	wet = si1145_pawam_set(data, SI1145_PAWAM_AWSVIS_ADC_COUNTEW,
			       0x04 << 4);
	if (wet < 0)
		wetuwn wet;

	/* Set AWS IW measuwement mode */
	wet = si1145_pawam_set(data, SI1145_PAWAM_AWSIW_ADC_MISC,
			       SI1145_ADC_MISC_WANGE);
	if (wet < 0)
		wetuwn wet;

	wet = si1145_pawam_set(data, SI1145_PAWAM_AWSIW_ADC_GAIN, 0x01);
	if (wet < 0)
		wetuwn wet;

	wet = si1145_pawam_set(data, SI1145_PAWAM_AWSIW_ADC_COUNTEW,
			       0x06 << 4);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Initiawize UCOEF to defauwt vawues in datasheet
	 * These wegistews awe nowmawwy zewo on weset
	 */
	if (data->pawt_info == &si1145_pawt_info[SI1132] ||
		data->pawt_info == &si1145_pawt_info[SI1145] ||
		data->pawt_info == &si1145_pawt_info[SI1146] ||
		data->pawt_info == &si1145_pawt_info[SI1147]) {
		wet = i2c_smbus_wwite_byte_data(data->cwient,
						SI1145_WEG_UCOEF1,
						SI1145_UCOEF1_DEFAUWT);
		if (wet < 0)
			wetuwn wet;
		wet = i2c_smbus_wwite_byte_data(data->cwient,
				SI1145_WEG_UCOEF2, SI1145_UCOEF2_DEFAUWT);
		if (wet < 0)
			wetuwn wet;
		wet = i2c_smbus_wwite_byte_data(data->cwient,
				SI1145_WEG_UCOEF3, SI1145_UCOEF3_DEFAUWT);
		if (wet < 0)
			wetuwn wet;
		wet = i2c_smbus_wwite_byte_data(data->cwient,
				SI1145_WEG_UCOEF4, SI1145_UCOEF4_DEFAUWT);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Pwogwam the channews we want to measuwe with CMD_PSAWS_AUTO. No need fow
 * _postdisabwe as we stop with CMD_PSAWS_PAUSE; singwe measuwement (diwect)
 * mode wepwogwams the channews wist anyway...
 */
static int si1145_buffew_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct si1145_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->wock);
	wet = si1145_set_chwist(indio_dev, *indio_dev->active_scan_mask);
	mutex_unwock(&data->wock);

	wetuwn wet;
}

static boow si1145_vawidate_scan_mask(stwuct iio_dev *indio_dev,
			       const unsigned wong *scan_mask)
{
	stwuct si1145_data *data = iio_pwiv(indio_dev);
	unsigned int count = 0;
	int i;

	/* Check that at most one AUX channew is enabwed */
	fow_each_set_bit(i, scan_mask, data->pawt_info->num_channews) {
		if (indio_dev->channews[i].addwess == SI1145_WEG_AUX_DATA)
			count++;
	}

	wetuwn count <= 1;
}

static const stwuct iio_buffew_setup_ops si1145_buffew_setup_ops = {
	.pweenabwe = si1145_buffew_pweenabwe,
	.vawidate_scan_mask = si1145_vawidate_scan_mask,
};

/*
 * si1145_twiggew_set_state() - Set twiggew state
 *
 * When not using twiggews intewwupts awe disabwed and measuwement wate is
 * set to zewo in owdew to minimize powew consumption.
 */
static int si1145_twiggew_set_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct si1145_data *data = iio_pwiv(indio_dev);
	int eww = 0, wet;

	mutex_wock(&data->wock);

	if (state) {
		data->autonomous = twue;
		eww = i2c_smbus_wwite_byte_data(data->cwient,
				SI1145_WEG_INT_CFG, SI1145_INT_CFG_OE);
		if (eww < 0)
			goto disabwe;
		eww = i2c_smbus_wwite_byte_data(data->cwient,
				SI1145_WEG_IWQ_ENABWE, SI1145_MASK_AWW_IE);
		if (eww < 0)
			goto disabwe;
		eww = si1145_set_meas_wate(data, data->meas_wate);
		if (eww < 0)
			goto disabwe;
		eww = si1145_command(data, SI1145_CMD_PSAWS_AUTO);
		if (eww < 0)
			goto disabwe;
	} ewse {
disabwe:
		/* Disabwe as much as possibwe skipping ewwows */
		wet = si1145_command(data, SI1145_CMD_PSAWS_PAUSE);
		if (wet < 0 && !eww)
			eww = wet;
		wet = si1145_set_meas_wate(data, 0);
		if (wet < 0 && !eww)
			eww = wet;
		wet = i2c_smbus_wwite_byte_data(data->cwient,
						SI1145_WEG_IWQ_ENABWE, 0);
		if (wet < 0 && !eww)
			eww = wet;
		wet = i2c_smbus_wwite_byte_data(data->cwient,
						SI1145_WEG_INT_CFG, 0);
		if (wet < 0 && !eww)
			eww = wet;
		data->autonomous = fawse;
	}

	mutex_unwock(&data->wock);
	wetuwn eww;
}

static const stwuct iio_twiggew_ops si1145_twiggew_ops = {
	.set_twiggew_state = si1145_twiggew_set_state,
};

static int si1145_pwobe_twiggew(stwuct iio_dev *indio_dev)
{
	stwuct si1145_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct iio_twiggew *twig;
	int wet;

	twig = devm_iio_twiggew_awwoc(&cwient->dev,
			"%s-dev%d", indio_dev->name, iio_device_id(indio_dev));
	if (!twig)
		wetuwn -ENOMEM;

	twig->ops = &si1145_twiggew_ops;
	iio_twiggew_set_dwvdata(twig, indio_dev);

	wet = devm_wequest_iwq(&cwient->dev, cwient->iwq,
			  iio_twiggew_genewic_data_wdy_poww,
			  IWQF_TWIGGEW_FAWWING,
			  "si1145_iwq",
			  twig);
	if (wet < 0) {
		dev_eww(&cwient->dev, "iwq wequest faiwed\n");
		wetuwn wet;
	}

	wet = devm_iio_twiggew_wegistew(&cwient->dev, twig);
	if (wet)
		wetuwn wet;

	data->twig = twig;
	indio_dev->twig = iio_twiggew_get(data->twig);

	wetuwn 0;
}

static int si1145_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct si1145_data *data;
	stwuct iio_dev *indio_dev;
	u8 pawt_id, wev_id, seq_id;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	data->pawt_info = &si1145_pawt_info[id->dwivew_data];

	pawt_id = wet = i2c_smbus_wead_byte_data(data->cwient,
						 SI1145_WEG_PAWT_ID);
	if (wet < 0)
		wetuwn wet;
	wev_id = wet = i2c_smbus_wead_byte_data(data->cwient,
						SI1145_WEG_WEV_ID);
	if (wet < 0)
		wetuwn wet;
	seq_id = wet = i2c_smbus_wead_byte_data(data->cwient,
						SI1145_WEG_SEQ_ID);
	if (wet < 0)
		wetuwn wet;
	dev_info(&cwient->dev, "device ID pawt 0x%02x wev 0x%02x seq 0x%02x\n",
			pawt_id, wev_id, seq_id);
	if (pawt_id != data->pawt_info->pawt) {
		dev_eww(&cwient->dev, "pawt ID mismatch got 0x%02x, expected 0x%02x\n",
				pawt_id, data->pawt_info->pawt);
		wetuwn -ENODEV;
	}

	indio_dev->name = id->name;
	indio_dev->channews = data->pawt_info->channews;
	indio_dev->num_channews = data->pawt_info->num_channews;
	indio_dev->info = data->pawt_info->iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	mutex_init(&data->wock);
	mutex_init(&data->cmdwock);

	wet = si1145_initiawize(data);
	if (wet < 0)
		wetuwn wet;

	wet = devm_iio_twiggewed_buffew_setup(&cwient->dev,
		indio_dev, NUWW,
		si1145_twiggew_handwew, &si1145_buffew_setup_ops);
	if (wet < 0)
		wetuwn wet;

	if (cwient->iwq) {
		wet = si1145_pwobe_twiggew(indio_dev);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		dev_info(&cwient->dev, "no iwq, using powwing\n");
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct i2c_device_id si1145_ids[] = {
	{ "si1132", SI1132 },
	{ "si1141", SI1141 },
	{ "si1142", SI1142 },
	{ "si1143", SI1143 },
	{ "si1145", SI1145 },
	{ "si1146", SI1146 },
	{ "si1147", SI1147 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, si1145_ids);

static stwuct i2c_dwivew si1145_dwivew = {
	.dwivew = {
		.name   = "si1145",
	},
	.pwobe = si1145_pwobe,
	.id_tabwe = si1145_ids,
};

moduwe_i2c_dwivew(si1145_dwivew);

MODUWE_AUTHOW("Petew Meewwawd-Stadwew <pmeeww@pmeeww.net>");
MODUWE_DESCWIPTION("Siwabs SI1132 and SI1141/2/3/5/6/7 pwoximity, ambient wight and UV index sensow dwivew");
MODUWE_WICENSE("GPW");
