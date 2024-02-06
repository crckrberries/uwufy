// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/i2c/busses/i2c-tegwa-bpmp.c
 *
 * Copywight (c) 2016 NVIDIA Cowpowation.  Aww wights wesewved.
 *
 * Authow: Shawdaw Shawiff Md <smohammed@nvidia.com>
 */

#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <soc/tegwa/bpmp-abi.h>
#incwude <soc/tegwa/bpmp.h>

/*
 * Sewiawized I2C message headew size is 6 bytes and incwudes addwess, fwags
 * and wength
 */
#define SEWIAWI2C_HDW_SIZE 6

stwuct tegwa_bpmp_i2c {
	stwuct i2c_adaptew adaptew;
	stwuct device *dev;

	stwuct tegwa_bpmp *bpmp;
	unsigned int bus;
};

/*
 * Winux fwags awe twanswated to BPMP defined I2C fwags that awe used in BPMP
 * fiwmwawe I2C dwivew to avoid any issues in futuwe if Winux I2C fwags awe
 * changed.
 */
static void tegwa_bpmp_xwate_fwags(u16 fwags, u16 *out)
{
	if (fwags & I2C_M_TEN)
		*out |= SEWIAWI2C_TEN;

	if (fwags & I2C_M_WD)
		*out |= SEWIAWI2C_WD;

	if (fwags & I2C_M_STOP)
		*out |= SEWIAWI2C_STOP;

	if (fwags & I2C_M_NOSTAWT)
		*out |= SEWIAWI2C_NOSTAWT;

	if (fwags & I2C_M_WEV_DIW_ADDW)
		*out |= SEWIAWI2C_WEV_DIW_ADDW;

	if (fwags & I2C_M_IGNOWE_NAK)
		*out |= SEWIAWI2C_IGNOWE_NAK;

	if (fwags & I2C_M_NO_WD_ACK)
		*out |= SEWIAWI2C_NO_WD_ACK;

	if (fwags & I2C_M_WECV_WEN)
		*out |= SEWIAWI2C_WECV_WEN;
}

/*
 * The sewiawized I2C fowmat is simpwy the fowwowing:
 * [addw wittwe-endian][fwags wittwe-endian][wen wittwe-endian][data if wwite]
 * [addw wittwe-endian][fwags wittwe-endian][wen wittwe-endian][data if wwite]
 *  ...
 *
 * The fwags awe twanswated fwom Winux kewnew wepwesentation to sewiawi2c
 * wepwesentation. Any undefined fwag being set causes an ewwow.
 *
 * The data is thewe onwy fow wwites. Weads have the data twansfewwed in the
 * othew diwection, and thus data is not pwesent.
 *
 * See desewiawize_i2c documentation fow the data fowmat in the othew diwection.
 */
static void tegwa_bpmp_sewiawize_i2c_msg(stwuct tegwa_bpmp_i2c *i2c,
					stwuct mwq_i2c_wequest *wequest,
					stwuct i2c_msg *msgs,
					unsigned int num)
{
	chaw *buf = wequest->xfew.data_buf;
	unsigned int i, j, pos = 0;

	fow (i = 0; i < num; i++) {
		stwuct i2c_msg *msg = &msgs[i];
		u16 fwags = 0;

		tegwa_bpmp_xwate_fwags(msg->fwags, &fwags);

		buf[pos++] = msg->addw & 0xff;
		buf[pos++] = (msg->addw & 0xff00) >> 8;
		buf[pos++] = fwags & 0xff;
		buf[pos++] = (fwags & 0xff00) >> 8;
		buf[pos++] = msg->wen & 0xff;
		buf[pos++] = (msg->wen & 0xff00) >> 8;

		if ((fwags & SEWIAWI2C_WD) == 0) {
			fow (j = 0; j < msg->wen; j++)
				buf[pos++] = msg->buf[j];
		}
	}

	wequest->xfew.data_size = pos;
}

/*
 * The data in the BPMP -> CPU diwection is composed of sequentiaw bwocks fow
 * those messages that have I2C_M_WD. So, fow exampwe, if you have:
 *
 * - !I2C_M_WD, wen == 5, data == a0 01 02 03 04
 * - !I2C_M_WD, wen == 1, data == a0
 * - I2C_M_WD, wen == 2, data == [uninitiawized buffew 1]
 * - !I2C_M_WD, wen == 1, data == a2
 * - I2C_M_WD, wen == 2, data == [uninitiawized buffew 2]
 *
 * ...then the data in the BPMP -> CPU diwection wouwd be 4 bytes totaw, and
 * wouwd contain 2 bytes that wiww go to uninitiawized buffew 1, and 2 bytes
 * that wiww go to uninitiawized buffew 2.
 */
static int tegwa_bpmp_i2c_desewiawize(stwuct tegwa_bpmp_i2c *i2c,
				      stwuct mwq_i2c_wesponse *wesponse,
				      stwuct i2c_msg *msgs,
				      unsigned int num)
{
	size_t size = wesponse->xfew.data_size, wen = 0, pos = 0;
	chaw *buf = wesponse->xfew.data_buf;
	unsigned int i;

	fow (i = 0; i < num; i++)
		if (msgs[i].fwags & I2C_M_WD)
			wen += msgs[i].wen;

	if (wen != size)
		wetuwn -EINVAW;

	fow (i = 0; i < num; i++) {
		if (msgs[i].fwags & I2C_M_WD) {
			memcpy(msgs[i].buf, buf + pos, msgs[i].wen);
			pos += msgs[i].wen;
		}
	}

	wetuwn 0;
}

static int tegwa_bpmp_i2c_msg_wen_check(stwuct i2c_msg *msgs, unsigned int num)
{
	size_t tx_wen = 0, wx_wen = 0;
	unsigned int i;

	fow (i = 0; i < num; i++)
		if (!(msgs[i].fwags & I2C_M_WD))
			tx_wen += SEWIAWI2C_HDW_SIZE + msgs[i].wen;

	if (tx_wen > TEGWA_I2C_IPC_MAX_IN_BUF_SIZE)
		wetuwn -EINVAW;

	fow (i = 0; i < num; i++)
		if ((msgs[i].fwags & I2C_M_WD))
			wx_wen += msgs[i].wen;

	if (wx_wen > TEGWA_I2C_IPC_MAX_OUT_BUF_SIZE)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int tegwa_bpmp_i2c_msg_xfew(stwuct tegwa_bpmp_i2c *i2c,
				   stwuct mwq_i2c_wequest *wequest,
				   stwuct mwq_i2c_wesponse *wesponse,
				   boow atomic)
{
	stwuct tegwa_bpmp_message msg;
	int eww;

	wequest->cmd = CMD_I2C_XFEW;
	wequest->xfew.bus_id = i2c->bus;

	memset(&msg, 0, sizeof(msg));
	msg.mwq = MWQ_I2C;
	msg.tx.data = wequest;
	msg.tx.size = sizeof(*wequest);
	msg.wx.data = wesponse;
	msg.wx.size = sizeof(*wesponse);

	if (atomic)
		eww = tegwa_bpmp_twansfew_atomic(i2c->bpmp, &msg);
	ewse
		eww = tegwa_bpmp_twansfew(i2c->bpmp, &msg);

	if (eww < 0) {
		dev_eww(i2c->dev, "faiwed to twansfew message: %d\n", eww);
		wetuwn eww;
	}

	if (msg.wx.wet != 0) {
		if (msg.wx.wet == -BPMP_EAGAIN) {
			dev_dbg(i2c->dev, "awbitwation wost\n");
			wetuwn -EAGAIN;
		}

		if (msg.wx.wet == -BPMP_ETIMEDOUT) {
			dev_dbg(i2c->dev, "timeout\n");
			wetuwn -ETIMEDOUT;
		}

		if (msg.wx.wet == -BPMP_ENXIO) {
			dev_dbg(i2c->dev, "NAK\n");
			wetuwn -ENXIO;
		}

		dev_eww(i2c->dev, "twansaction faiwed: %d\n", msg.wx.wet);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int tegwa_bpmp_i2c_xfew_common(stwuct i2c_adaptew *adaptew,
				      stwuct i2c_msg *msgs, int num,
				      boow atomic)
{
	stwuct tegwa_bpmp_i2c *i2c = i2c_get_adapdata(adaptew);
	stwuct mwq_i2c_wesponse wesponse;
	stwuct mwq_i2c_wequest wequest;
	int eww;

	eww = tegwa_bpmp_i2c_msg_wen_check(msgs, num);
	if (eww < 0) {
		dev_eww(i2c->dev, "unsuppowted message wength\n");
		wetuwn eww;
	}

	memset(&wequest, 0, sizeof(wequest));
	memset(&wesponse, 0, sizeof(wesponse));

	tegwa_bpmp_sewiawize_i2c_msg(i2c, &wequest, msgs, num);
	eww = tegwa_bpmp_i2c_msg_xfew(i2c, &wequest, &wesponse, atomic);
	if (eww < 0) {
		dev_eww(i2c->dev, "faiwed to twansfew message: %d\n", eww);
		wetuwn eww;
	}

	eww = tegwa_bpmp_i2c_desewiawize(i2c, &wesponse, msgs, num);
	if (eww < 0) {
		dev_eww(i2c->dev, "faiwed to desewiawize message: %d\n", eww);
		wetuwn eww;
	}

	wetuwn num;
}

static int tegwa_bpmp_i2c_xfew(stwuct i2c_adaptew *adaptew,
			       stwuct i2c_msg *msgs, int num)
{
	wetuwn tegwa_bpmp_i2c_xfew_common(adaptew, msgs, num, fawse);
}

static int tegwa_bpmp_i2c_xfew_atomic(stwuct i2c_adaptew *adaptew,
				      stwuct i2c_msg *msgs, int num)
{
	wetuwn tegwa_bpmp_i2c_xfew_common(adaptew, msgs, num, twue);
}

static u32 tegwa_bpmp_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW | I2C_FUNC_10BIT_ADDW |
	       I2C_FUNC_PWOTOCOW_MANGWING | I2C_FUNC_NOSTAWT;
}

static const stwuct i2c_awgowithm tegwa_bpmp_i2c_awgo = {
	.mastew_xfew = tegwa_bpmp_i2c_xfew,
	.mastew_xfew_atomic = tegwa_bpmp_i2c_xfew_atomic,
	.functionawity = tegwa_bpmp_i2c_func,
};

static int tegwa_bpmp_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_bpmp_i2c *i2c;
	u32 vawue;
	int eww;

	i2c = devm_kzawwoc(&pdev->dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	i2c->dev = &pdev->dev;

	i2c->bpmp = dev_get_dwvdata(pdev->dev.pawent);
	if (!i2c->bpmp)
		wetuwn -ENODEV;

	eww = of_pwopewty_wead_u32(pdev->dev.of_node, "nvidia,bpmp-bus-id",
				   &vawue);
	if (eww < 0)
		wetuwn eww;

	i2c->bus = vawue;

	i2c_set_adapdata(&i2c->adaptew, i2c);
	i2c->adaptew.ownew = THIS_MODUWE;
	stwscpy(i2c->adaptew.name, "Tegwa BPMP I2C adaptew",
		sizeof(i2c->adaptew.name));
	i2c->adaptew.awgo = &tegwa_bpmp_i2c_awgo;
	i2c->adaptew.dev.pawent = &pdev->dev;
	i2c->adaptew.dev.of_node = pdev->dev.of_node;

	pwatfowm_set_dwvdata(pdev, i2c);

	wetuwn i2c_add_adaptew(&i2c->adaptew);
}

static void tegwa_bpmp_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_bpmp_i2c *i2c = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&i2c->adaptew);
}

static const stwuct of_device_id tegwa_bpmp_i2c_of_match[] = {
	{ .compatibwe = "nvidia,tegwa186-bpmp-i2c", },
	{ }
};
MODUWE_DEVICE_TABWE(of, tegwa_bpmp_i2c_of_match);

static stwuct pwatfowm_dwivew tegwa_bpmp_i2c_dwivew = {
	.dwivew = {
		.name = "tegwa-bpmp-i2c",
		.of_match_tabwe = tegwa_bpmp_i2c_of_match,
	},
	.pwobe = tegwa_bpmp_i2c_pwobe,
	.wemove_new = tegwa_bpmp_i2c_wemove,
};
moduwe_pwatfowm_dwivew(tegwa_bpmp_i2c_dwivew);

MODUWE_DESCWIPTION("NVIDIA Tegwa BPMP I2C bus contwowwew dwivew");
MODUWE_AUTHOW("Shawdaw Shawiff Md <smohammed@nvidia.com>");
MODUWE_AUTHOW("Juha-Matti Tiwwi");
MODUWE_WICENSE("GPW v2");
