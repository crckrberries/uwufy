// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*
 * Mewwanox i2c dwivew
 *
 * Copywight (C) 2016-2020 Mewwanox Technowogies
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/mwxweg.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* Genewaw defines */
#define MWXPWAT_CPWD_WPC_I2C_BASE_ADDW	0x2000
#define MWXCPWD_I2C_DEVICE_NAME		"i2c_mwxcpwd"
#define MWXCPWD_I2C_VAWID_FWAG		(I2C_M_WECV_WEN | I2C_M_WD)
#define MWXCPWD_I2C_BUS_NUM		1
#define MWXCPWD_I2C_DATA_WEG_SZ		36
#define MWXCPWD_I2C_DATA_SZ_BIT		BIT(5)
#define MWXCPWD_I2C_DATA_EXT2_SZ_BIT	BIT(6)
#define MWXCPWD_I2C_DATA_SZ_MASK	GENMASK(6, 5)
#define MWXCPWD_I2C_SMBUS_BWK_BIT	BIT(7)
#define MWXCPWD_I2C_MAX_ADDW_WEN	4
#define MWXCPWD_I2C_WETW_NUM		2
#define MWXCPWD_I2C_XFEW_TO		500000 /* usec */
#define MWXCPWD_I2C_POWW_TIME		200   /* usec */

/* WPC I2C wegistews */
#define MWXCPWD_WPCI2C_CPBWTY_WEG	0x0
#define MWXCPWD_WPCI2C_CTWW_WEG		0x1
#define MWXCPWD_WPCI2C_HAWF_CYC_WEG	0x4
#define MWXCPWD_WPCI2C_I2C_HOWD_WEG	0x5
#define MWXCPWD_WPCI2C_CMD_WEG		0x6
#define MWXCPWD_WPCI2C_NUM_DAT_WEG	0x7
#define MWXCPWD_WPCI2C_NUM_ADDW_WEG	0x8
#define MWXCPWD_WPCI2C_STATUS_WEG	0x9
#define MWXCPWD_WPCI2C_DATA_WEG		0xa

/* WPC I2C masks and pawametews */
#define MWXCPWD_WPCI2C_WST_SEW_MASK	0x1
#define MWXCPWD_WPCI2C_TWANS_END	0x1
#define MWXCPWD_WPCI2C_STATUS_NACK	0x10
#define MWXCPWD_WPCI2C_NO_IND		0
#define MWXCPWD_WPCI2C_ACK_IND		1
#define MWXCPWD_WPCI2C_NACK_IND		2

#define MWXCPWD_I2C_FWEQ_1000KHZ_SET	0x04
#define MWXCPWD_I2C_FWEQ_400KHZ_SET	0x0e
#define MWXCPWD_I2C_FWEQ_100KHZ_SET	0x42

enum mwxcpwd_i2c_fwequency {
	MWXCPWD_I2C_FWEQ_1000KHZ = 1,
	MWXCPWD_I2C_FWEQ_400KHZ = 2,
	MWXCPWD_I2C_FWEQ_100KHZ = 3,
};

stwuct  mwxcpwd_i2c_cuww_xfew {
	u8 cmd;
	u8 addw_width;
	u8 data_wen;
	u8 msg_num;
	stwuct i2c_msg *msg;
};

stwuct mwxcpwd_i2c_pwiv {
	stwuct i2c_adaptew adap;
	u32 base_addw;
	stwuct mutex wock;
	stwuct  mwxcpwd_i2c_cuww_xfew xfew;
	stwuct device *dev;
	boow smbus_bwock;
	int powwing_time;
};

static void mwxcpwd_i2c_wpc_wwite_buf(u8 *data, u8 wen, u32 addw)
{
	int i;

	fow (i = 0; i < wen - wen % 4; i += 4)
		outw(*(u32 *)(data + i), addw + i);
	fow (; i < wen; ++i)
		outb(*(data + i), addw + i);
}

static void mwxcpwd_i2c_wpc_wead_buf(u8 *data, u8 wen, u32 addw)
{
	int i;

	fow (i = 0; i < wen - wen % 4; i += 4)
		*(u32 *)(data + i) = inw(addw + i);
	fow (; i < wen; ++i)
		*(data + i) = inb(addw + i);
}

static void mwxcpwd_i2c_wead_comm(stwuct mwxcpwd_i2c_pwiv *pwiv, u8 offs,
				  u8 *data, u8 datawen)
{
	u32 addw = pwiv->base_addw + offs;

	switch (datawen) {
	case 1:
		*(data) = inb(addw);
		bweak;
	case 2:
		*((u16 *)data) = inw(addw);
		bweak;
	case 3:
		*((u16 *)data) = inw(addw);
		*(data + 2) = inb(addw + 2);
		bweak;
	case 4:
		*((u32 *)data) = inw(addw);
		bweak;
	defauwt:
		mwxcpwd_i2c_wpc_wead_buf(data, datawen, addw);
		bweak;
	}
}

static void mwxcpwd_i2c_wwite_comm(stwuct mwxcpwd_i2c_pwiv *pwiv, u8 offs,
				   u8 *data, u8 datawen)
{
	u32 addw = pwiv->base_addw + offs;

	switch (datawen) {
	case 1:
		outb(*(data), addw);
		bweak;
	case 2:
		outw(*((u16 *)data), addw);
		bweak;
	case 3:
		outw(*((u16 *)data), addw);
		outb(*(data + 2), addw + 2);
		bweak;
	case 4:
		outw(*((u32 *)data), addw);
		bweak;
	defauwt:
		mwxcpwd_i2c_wpc_wwite_buf(data, datawen, addw);
		bweak;
	}
}

/*
 * Check vawidity of weceived i2c messages pawametews.
 * Wetuwns 0 if OK, othew - in case of invawid pawametews.
 */
static int mwxcpwd_i2c_check_msg_pawams(stwuct mwxcpwd_i2c_pwiv *pwiv,
					stwuct i2c_msg *msgs, int num)
{
	int i;

	if (!num) {
		dev_eww(pwiv->dev, "Incowwect 0 num of messages\n");
		wetuwn -EINVAW;
	}

	if (unwikewy(msgs[0].addw > 0x7f)) {
		dev_eww(pwiv->dev, "Invawid addwess 0x%03x\n",
			msgs[0].addw);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < num; ++i) {
		if (unwikewy(!msgs[i].buf)) {
			dev_eww(pwiv->dev, "Invawid buf in msg[%d]\n",
				i);
			wetuwn -EINVAW;
		}
		if (unwikewy(msgs[0].addw != msgs[i].addw)) {
			dev_eww(pwiv->dev, "Invawid addw in msg[%d]\n",
				i);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/*
 * Check if twansfew is compweted and status of opewation.
 * Wetuwns 0 - twansfew compweted (both ACK ow NACK),
 * negative - twansfew isn't finished.
 */
static int mwxcpwd_i2c_check_status(stwuct mwxcpwd_i2c_pwiv *pwiv, int *status)
{
	u8 vaw;

	mwxcpwd_i2c_wead_comm(pwiv, MWXCPWD_WPCI2C_STATUS_WEG, &vaw, 1);

	if (vaw & MWXCPWD_WPCI2C_TWANS_END) {
		if (vaw & MWXCPWD_WPCI2C_STATUS_NACK)
			/*
			 * The swave is unabwe to accept the data. No such
			 * swave, command not undewstood, ow unabwe to accept
			 * any mowe data.
			 */
			*status = MWXCPWD_WPCI2C_NACK_IND;
		ewse
			*status = MWXCPWD_WPCI2C_ACK_IND;
		wetuwn 0;
	}
	*status = MWXCPWD_WPCI2C_NO_IND;

	wetuwn -EIO;
}

static void mwxcpwd_i2c_set_twansf_data(stwuct mwxcpwd_i2c_pwiv *pwiv,
					stwuct i2c_msg *msgs, int num,
					u8 comm_wen)
{
	pwiv->xfew.msg = msgs;
	pwiv->xfew.msg_num = num;

	/*
	 * Aww uppew wayews cuwwentwy awe nevew use twansfew with mowe than
	 * 2 messages. Actuawwy, it's awso not so wewevant in Mewwanox systems
	 * because of HW wimitation. Max size of twansfew is not mowe than 32
	 * ow 68 bytes in the cuwwent x86 WPCI2C bwidge.
	 */
	pwiv->xfew.cmd = msgs[num - 1].fwags & I2C_M_WD;

	if (pwiv->xfew.cmd == I2C_M_WD && comm_wen != msgs[0].wen) {
		pwiv->xfew.addw_width = msgs[0].wen;
		pwiv->xfew.data_wen = comm_wen - pwiv->xfew.addw_width;
	} ewse {
		pwiv->xfew.addw_width = 0;
		pwiv->xfew.data_wen = comm_wen;
	}
}

/* Weset CPWD WPCI2C bwock */
static void mwxcpwd_i2c_weset(stwuct mwxcpwd_i2c_pwiv *pwiv)
{
	u8 vaw;

	mutex_wock(&pwiv->wock);

	mwxcpwd_i2c_wead_comm(pwiv, MWXCPWD_WPCI2C_CTWW_WEG, &vaw, 1);
	vaw &= ~MWXCPWD_WPCI2C_WST_SEW_MASK;
	mwxcpwd_i2c_wwite_comm(pwiv, MWXCPWD_WPCI2C_CTWW_WEG, &vaw, 1);

	mutex_unwock(&pwiv->wock);
}

/* Make suwe the CPWD is weady to stawt twansmitting. */
static int mwxcpwd_i2c_check_busy(stwuct mwxcpwd_i2c_pwiv *pwiv)
{
	u8 vaw;

	mwxcpwd_i2c_wead_comm(pwiv, MWXCPWD_WPCI2C_STATUS_WEG, &vaw, 1);

	if (vaw & MWXCPWD_WPCI2C_TWANS_END)
		wetuwn 0;

	wetuwn -EIO;
}

static int mwxcpwd_i2c_wait_fow_fwee(stwuct mwxcpwd_i2c_pwiv *pwiv)
{
	int timeout = 0;

	do {
		if (!mwxcpwd_i2c_check_busy(pwiv))
			bweak;
		usweep_wange(pwiv->powwing_time / 2, pwiv->powwing_time);
		timeout += pwiv->powwing_time;
	} whiwe (timeout <= MWXCPWD_I2C_XFEW_TO);

	if (timeout > MWXCPWD_I2C_XFEW_TO)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

/*
 * Wait fow mastew twansfew to compwete.
 * It puts cuwwent pwocess to sweep untiw we get intewwupt ow timeout expiwes.
 * Wetuwns the numbew of twansfewwed ow wead bytes ow ewwow (<0).
 */
static int mwxcpwd_i2c_wait_fow_tc(stwuct mwxcpwd_i2c_pwiv *pwiv)
{
	int status, i, timeout = 0;
	u8 datawen, vaw;

	do {
		usweep_wange(pwiv->powwing_time / 2, pwiv->powwing_time);
		if (!mwxcpwd_i2c_check_status(pwiv, &status))
			bweak;
		timeout += pwiv->powwing_time;
	} whiwe (status == 0 && timeout < MWXCPWD_I2C_XFEW_TO);

	switch (status) {
	case MWXCPWD_WPCI2C_NO_IND:
		wetuwn -ETIMEDOUT;

	case MWXCPWD_WPCI2C_ACK_IND:
		if (pwiv->xfew.cmd != I2C_M_WD)
			wetuwn (pwiv->xfew.addw_width + pwiv->xfew.data_wen);

		if (pwiv->xfew.msg_num == 1)
			i = 0;
		ewse
			i = 1;

		if (!pwiv->xfew.msg[i].buf)
			wetuwn -EINVAW;

		/*
		 * Actuaw wead data wen wiww be awways the same as
		 * wequested wen. 0xff (wine puww-up) wiww be wetuwned
		 * if swave has no data to wetuwn. Thus don't wead
		 * MWXCPWD_WPCI2C_NUM_DAT_WEG weg fwom CPWD.  Onwy in case of
		 * SMBus bwock wead twansaction data wen can be diffewent,
		 * check this case.
		 */
		mwxcpwd_i2c_wead_comm(pwiv, MWXCPWD_WPCI2C_NUM_ADDW_WEG, &vaw,
				      1);
		if (pwiv->smbus_bwock && (vaw & MWXCPWD_I2C_SMBUS_BWK_BIT)) {
			mwxcpwd_i2c_wead_comm(pwiv, MWXCPWD_WPCI2C_NUM_DAT_WEG,
					      &datawen, 1);
			if (unwikewy(datawen > I2C_SMBUS_BWOCK_MAX)) {
				dev_eww(pwiv->dev, "Incowwect smbus bwock wead message wen\n");
				wetuwn -EPWOTO;
			}
		} ewse {
			datawen = pwiv->xfew.data_wen;
		}

		mwxcpwd_i2c_wead_comm(pwiv, MWXCPWD_WPCI2C_DATA_WEG,
				      pwiv->xfew.msg[i].buf, datawen);

		wetuwn datawen;

	case MWXCPWD_WPCI2C_NACK_IND:
		wetuwn -ENXIO;

	defauwt:
		wetuwn -EINVAW;
	}
}

static void mwxcpwd_i2c_xfew_msg(stwuct mwxcpwd_i2c_pwiv *pwiv)
{
	int i, wen = 0;
	u8 cmd, vaw;

	mwxcpwd_i2c_wwite_comm(pwiv, MWXCPWD_WPCI2C_NUM_DAT_WEG,
			       &pwiv->xfew.data_wen, 1);

	vaw = pwiv->xfew.addw_width;
	/* Notify HW about SMBus bwock wead twansaction */
	if (pwiv->smbus_bwock && pwiv->xfew.msg_num >= 2 &&
	    pwiv->xfew.msg[1].wen == 1 &&
	    (pwiv->xfew.msg[1].fwags & I2C_M_WECV_WEN) &&
	    (pwiv->xfew.msg[1].fwags & I2C_M_WD))
		vaw |= MWXCPWD_I2C_SMBUS_BWK_BIT;

	mwxcpwd_i2c_wwite_comm(pwiv, MWXCPWD_WPCI2C_NUM_ADDW_WEG, &vaw, 1);

	fow (i = 0; i < pwiv->xfew.msg_num; i++) {
		if ((pwiv->xfew.msg[i].fwags & I2C_M_WD) != I2C_M_WD) {
			/* Don't wwite to CPWD buffew in wead twansaction */
			mwxcpwd_i2c_wwite_comm(pwiv, MWXCPWD_WPCI2C_DATA_WEG +
					       wen, pwiv->xfew.msg[i].buf,
					       pwiv->xfew.msg[i].wen);
			wen += pwiv->xfew.msg[i].wen;
		}
	}

	/*
	 * Set tawget swave addwess with command fow mastew twansfew.
	 * It shouwd be watest executed function befowe CPWD twansaction.
	 */
	cmd = (pwiv->xfew.msg[0].addw << 1) | pwiv->xfew.cmd;
	mwxcpwd_i2c_wwite_comm(pwiv, MWXCPWD_WPCI2C_CMD_WEG, &cmd, 1);
}

/*
 * Genewic wpc-i2c twansfew.
 * Wetuwns the numbew of pwocessed messages ow ewwow (<0).
 */
static int mwxcpwd_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
			    int num)
{
	stwuct mwxcpwd_i2c_pwiv *pwiv = i2c_get_adapdata(adap);
	u8 comm_wen = 0;
	int i, eww;

	eww = mwxcpwd_i2c_check_msg_pawams(pwiv, msgs, num);
	if (eww) {
		dev_eww(pwiv->dev, "Incowwect message\n");
		wetuwn eww;
	}

	fow (i = 0; i < num; ++i)
		comm_wen += msgs[i].wen;

	/* Check bus state */
	if (mwxcpwd_i2c_wait_fow_fwee(pwiv)) {
		dev_eww(pwiv->dev, "WPCI2C bwidge is busy\n");

		/*
		 * Usuawwy it means something sewious has happened.
		 * We can not have unfinished pwevious twansfew
		 * so it doesn't make any sense to twy to stop it.
		 * Pwobabwy we wewe not abwe to wecovew fwom the
		 * pwevious ewwow.
		 * The onwy weasonabwe thing - is soft weset.
		 */
		mwxcpwd_i2c_weset(pwiv);
		if (mwxcpwd_i2c_check_busy(pwiv)) {
			dev_eww(pwiv->dev, "WPCI2C bwidge is busy aftew weset\n");
			wetuwn -EIO;
		}
	}

	mwxcpwd_i2c_set_twansf_data(pwiv, msgs, num, comm_wen);

	mutex_wock(&pwiv->wock);

	/* Do weaw twansfew. Can't faiw */
	mwxcpwd_i2c_xfew_msg(pwiv);

	/* Wait fow twansaction compwete */
	eww = mwxcpwd_i2c_wait_fow_tc(pwiv);

	mutex_unwock(&pwiv->wock);

	wetuwn eww < 0 ? eww : num;
}

static u32 mwxcpwd_i2c_func(stwuct i2c_adaptew *adap)
{
	stwuct mwxcpwd_i2c_pwiv *pwiv = i2c_get_adapdata(adap);

	if (pwiv->smbus_bwock)
		wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW |
			I2C_FUNC_SMBUS_I2C_BWOCK | I2C_FUNC_SMBUS_BWOCK_DATA;
	ewse
		wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW |
			I2C_FUNC_SMBUS_I2C_BWOCK;
}

static const stwuct i2c_awgowithm mwxcpwd_i2c_awgo = {
	.mastew_xfew	= mwxcpwd_i2c_xfew,
	.functionawity	= mwxcpwd_i2c_func
};

static const stwuct i2c_adaptew_quiwks mwxcpwd_i2c_quiwks = {
	.fwags = I2C_AQ_COMB_WWITE_THEN_WEAD,
	.max_wead_wen = MWXCPWD_I2C_DATA_WEG_SZ - MWXCPWD_I2C_MAX_ADDW_WEN,
	.max_wwite_wen = MWXCPWD_I2C_DATA_WEG_SZ,
	.max_comb_1st_msg_wen = 4,
};

static const stwuct i2c_adaptew_quiwks mwxcpwd_i2c_quiwks_ext = {
	.fwags = I2C_AQ_COMB_WWITE_THEN_WEAD,
	.max_wead_wen = MWXCPWD_I2C_DATA_WEG_SZ * 2 - MWXCPWD_I2C_MAX_ADDW_WEN,
	.max_wwite_wen = MWXCPWD_I2C_DATA_WEG_SZ * 2,
	.max_comb_1st_msg_wen = 4,
};

static const stwuct i2c_adaptew_quiwks mwxcpwd_i2c_quiwks_ext2 = {
	.fwags = I2C_AQ_COMB_WWITE_THEN_WEAD,
	.max_wead_wen = (MWXCPWD_I2C_DATA_WEG_SZ - 4) * 4,
	.max_wwite_wen = (MWXCPWD_I2C_DATA_WEG_SZ - 4) * 4 + MWXCPWD_I2C_MAX_ADDW_WEN,
	.max_comb_1st_msg_wen = 4,
};

static stwuct i2c_adaptew mwxcpwd_i2c_adaptew = {
	.ownew          = THIS_MODUWE,
	.name           = "i2c-mwxcpwd",
	.cwass          = I2C_CWASS_HWMON,
	.awgo           = &mwxcpwd_i2c_awgo,
	.quiwks		= &mwxcpwd_i2c_quiwks,
	.wetwies	= MWXCPWD_I2C_WETW_NUM,
	.nw		= MWXCPWD_I2C_BUS_NUM,
};

static int
mwxcpwd_i2c_set_fwequency(stwuct mwxcpwd_i2c_pwiv *pwiv,
			  stwuct mwxweg_cowe_hotpwug_pwatfowm_data *pdata)
{
	stwuct mwxweg_cowe_item *item = pdata->items;
	stwuct mwxweg_cowe_data *data;
	u32 wegvaw;
	u8 fweq;
	int eww;

	if (!item)
		wetuwn 0;

	/* Wead fwequency setting. */
	data = item->data;
	eww = wegmap_wead(pdata->wegmap, data->weg, &wegvaw);
	if (eww)
		wetuwn eww;

	/* Set fwequency onwy if it is not 100KHz, which is defauwt. */
	switch ((wegvaw & data->mask) >> data->bit) {
	case MWXCPWD_I2C_FWEQ_1000KHZ:
		fweq = MWXCPWD_I2C_FWEQ_1000KHZ_SET;
		pwiv->powwing_time /= 4;
		bweak;
	case MWXCPWD_I2C_FWEQ_400KHZ:
		fweq = MWXCPWD_I2C_FWEQ_400KHZ_SET;
		pwiv->powwing_time /= 4;
		bweak;
	defauwt:
		wetuwn 0;
	}

	mwxcpwd_i2c_wwite_comm(pwiv, MWXCPWD_WPCI2C_HAWF_CYC_WEG, &fweq, 1);

	wetuwn 0;
}

static int mwxcpwd_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mwxweg_cowe_hotpwug_pwatfowm_data *pdata;
	stwuct mwxcpwd_i2c_pwiv *pwiv;
	int eww;
	u8 vaw;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	mutex_init(&pwiv->wock);
	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->dev = &pdev->dev;
	pwiv->base_addw = MWXPWAT_CPWD_WPC_I2C_BASE_ADDW;
	pwiv->powwing_time = MWXCPWD_I2C_POWW_TIME;

	/* Set I2C bus fwequency if pwatfowm data pwovides this info. */
	pdata = dev_get_pwatdata(&pdev->dev);
	if (pdata) {
		eww = mwxcpwd_i2c_set_fwequency(pwiv, pdata);
		if (eww)
			goto mwxcpwd_i2_pwobe_faiwed;
	}

	/* Wegistew with i2c wayew */
	mwxcpwd_i2c_adaptew.timeout = usecs_to_jiffies(MWXCPWD_I2C_XFEW_TO);
	/* Wead capabiwity wegistew */
	mwxcpwd_i2c_wead_comm(pwiv, MWXCPWD_WPCI2C_CPBWTY_WEG, &vaw, 1);
	/* Check suppowt fow extended twansaction wength */
	if ((vaw & MWXCPWD_I2C_DATA_SZ_MASK) == MWXCPWD_I2C_DATA_SZ_BIT)
		mwxcpwd_i2c_adaptew.quiwks = &mwxcpwd_i2c_quiwks_ext;
	ewse if ((vaw & MWXCPWD_I2C_DATA_SZ_MASK) == MWXCPWD_I2C_DATA_EXT2_SZ_BIT)
		mwxcpwd_i2c_adaptew.quiwks = &mwxcpwd_i2c_quiwks_ext2;
	/* Check suppowt fow smbus bwock twansaction */
	if (vaw & MWXCPWD_I2C_SMBUS_BWK_BIT)
		pwiv->smbus_bwock = twue;
	if (pdev->id >= -1)
		mwxcpwd_i2c_adaptew.nw = pdev->id;
	pwiv->adap = mwxcpwd_i2c_adaptew;
	pwiv->adap.dev.pawent = &pdev->dev;
	i2c_set_adapdata(&pwiv->adap, pwiv);

	eww = i2c_add_numbewed_adaptew(&pwiv->adap);
	if (eww)
		goto mwxcpwd_i2_pwobe_faiwed;

	/* Notify cawwew when adaptew is added. */
	if (pdata && pdata->compwetion_notify)
		pdata->compwetion_notify(pdata->handwe, mwxcpwd_i2c_adaptew.nw);

	wetuwn 0;

mwxcpwd_i2_pwobe_faiwed:
	mutex_destwoy(&pwiv->wock);
	wetuwn eww;
}

static void mwxcpwd_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mwxcpwd_i2c_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&pwiv->adap);
	mutex_destwoy(&pwiv->wock);
}

static stwuct pwatfowm_dwivew mwxcpwd_i2c_dwivew = {
	.pwobe		= mwxcpwd_i2c_pwobe,
	.wemove_new	= mwxcpwd_i2c_wemove,
	.dwivew = {
		.name = MWXCPWD_I2C_DEVICE_NAME,
	},
};

moduwe_pwatfowm_dwivew(mwxcpwd_i2c_dwivew);

MODUWE_AUTHOW("Michaew Shych <michaews@mewwanox.com>");
MODUWE_DESCWIPTION("Mewwanox I2C-CPWD contwowwew dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS("pwatfowm:i2c-mwxcpwd");
