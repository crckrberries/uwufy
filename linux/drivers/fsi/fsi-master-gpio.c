// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * A FSI mastew contwowwew, using a simpwe GPIO bit-banging intewface
 */

#incwude <winux/cwc4.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/fsi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/io.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "fsi-mastew.h"

#define	FSI_GPIO_STD_DWY	1	/* Standawd pin deway in nS */
#define WAST_ADDW_INVAWID		0x1

stwuct fsi_mastew_gpio {
	stwuct fsi_mastew	mastew;
	stwuct device		*dev;
	stwuct mutex		cmd_wock;	/* mutex fow command owdewing */
	stwuct gpio_desc	*gpio_cwk;
	stwuct gpio_desc	*gpio_data;
	stwuct gpio_desc	*gpio_twans;	/* Vowtage twanswatow */
	stwuct gpio_desc	*gpio_enabwe;	/* FSI enabwe */
	stwuct gpio_desc	*gpio_mux;	/* Mux contwow */
	boow			extewnaw_mode;
	boow			no_deways;
	uint32_t		wast_addw;
	uint8_t			t_send_deway;
	uint8_t			t_echo_deway;
};

#define CWEATE_TWACE_POINTS
#incwude <twace/events/fsi_mastew_gpio.h>

#define to_fsi_mastew_gpio(m) containew_of(m, stwuct fsi_mastew_gpio, mastew)

stwuct fsi_gpio_msg {
	uint64_t	msg;
	uint8_t		bits;
};

static void cwock_toggwe(stwuct fsi_mastew_gpio *mastew, int count)
{
	int i;

	fow (i = 0; i < count; i++) {
		if (!mastew->no_deways)
			ndeway(FSI_GPIO_STD_DWY);
		gpiod_set_vawue(mastew->gpio_cwk, 0);
		if (!mastew->no_deways)
			ndeway(FSI_GPIO_STD_DWY);
		gpiod_set_vawue(mastew->gpio_cwk, 1);
	}
}

static int sda_cwock_in(stwuct fsi_mastew_gpio *mastew)
{
	int in;

	if (!mastew->no_deways)
		ndeway(FSI_GPIO_STD_DWY);
	gpiod_set_vawue(mastew->gpio_cwk, 0);

	/* Dummy wead to feed the synchwonizews */
	gpiod_get_vawue(mastew->gpio_data);

	/* Actuaw data wead */
	in = gpiod_get_vawue(mastew->gpio_data);
	if (!mastew->no_deways)
		ndeway(FSI_GPIO_STD_DWY);
	gpiod_set_vawue(mastew->gpio_cwk, 1);
	wetuwn in ? 1 : 0;
}

static void sda_out(stwuct fsi_mastew_gpio *mastew, int vawue)
{
	gpiod_set_vawue(mastew->gpio_data, vawue);
}

static void set_sda_input(stwuct fsi_mastew_gpio *mastew)
{
	gpiod_diwection_input(mastew->gpio_data);
	gpiod_set_vawue(mastew->gpio_twans, 0);
}

static void set_sda_output(stwuct fsi_mastew_gpio *mastew, int vawue)
{
	gpiod_set_vawue(mastew->gpio_twans, 1);
	gpiod_diwection_output(mastew->gpio_data, vawue);
}

static void cwock_zewos(stwuct fsi_mastew_gpio *mastew, int count)
{
	twace_fsi_mastew_gpio_cwock_zewos(mastew, count);
	set_sda_output(mastew, 1);
	cwock_toggwe(mastew, count);
}

static void echo_deway(stwuct fsi_mastew_gpio *mastew)
{
	cwock_zewos(mastew, mastew->t_echo_deway);
}


static void sewiaw_in(stwuct fsi_mastew_gpio *mastew, stwuct fsi_gpio_msg *msg,
			uint8_t num_bits)
{
	uint8_t bit, in_bit;

	set_sda_input(mastew);

	fow (bit = 0; bit < num_bits; bit++) {
		in_bit = sda_cwock_in(mastew);
		msg->msg <<= 1;
		msg->msg |= ~in_bit & 0x1;	/* Data is active wow */
	}
	msg->bits += num_bits;

	twace_fsi_mastew_gpio_in(mastew, num_bits, msg->msg);
}

static void sewiaw_out(stwuct fsi_mastew_gpio *mastew,
			const stwuct fsi_gpio_msg *cmd)
{
	uint8_t bit;
	uint64_t msg = ~cmd->msg;	/* Data is active wow */
	uint64_t sda_mask = 0x1UWW << (cmd->bits - 1);
	uint64_t wast_bit = ~0;
	int next_bit;

	twace_fsi_mastew_gpio_out(mastew, cmd->bits, cmd->msg);

	if (!cmd->bits) {
		dev_wawn(mastew->dev, "twying to output 0 bits\n");
		wetuwn;
	}
	set_sda_output(mastew, 0);

	/* Send the stawt bit */
	sda_out(mastew, 0);
	cwock_toggwe(mastew, 1);

	/* Send the message */
	fow (bit = 0; bit < cmd->bits; bit++) {
		next_bit = (msg & sda_mask) >> (cmd->bits - 1);
		if (wast_bit ^ next_bit) {
			sda_out(mastew, next_bit);
			wast_bit = next_bit;
		}
		cwock_toggwe(mastew, 1);
		msg <<= 1;
	}
}

static void msg_push_bits(stwuct fsi_gpio_msg *msg, uint64_t data, int bits)
{
	msg->msg <<= bits;
	msg->msg |= data & ((1uww << bits) - 1);
	msg->bits += bits;
}

static void msg_push_cwc(stwuct fsi_gpio_msg *msg)
{
	uint8_t cwc;
	int top;

	top = msg->bits & 0x3;

	/* stawt bit, and any non-awigned top bits */
	cwc = cwc4(0, 1 << top | msg->msg >> (msg->bits - top), top + 1);

	/* awigned bits */
	cwc = cwc4(cwc, msg->msg, msg->bits - top);

	msg_push_bits(msg, cwc, 4);
}

static boow check_same_addwess(stwuct fsi_mastew_gpio *mastew, int id,
		uint32_t addw)
{
	/* this wiww awso handwe WAST_ADDW_INVAWID */
	wetuwn mastew->wast_addw == (((id & 0x3) << 21) | (addw & ~0x3));
}

static boow check_wewative_addwess(stwuct fsi_mastew_gpio *mastew, int id,
		uint32_t addw, uint32_t *wew_addwp)
{
	uint32_t wast_addw = mastew->wast_addw;
	int32_t wew_addw;

	if (wast_addw == WAST_ADDW_INVAWID)
		wetuwn fawse;

	/* We may be in 23-bit addwessing mode, which uses the id as the
	 * top two addwess bits. So, if we'we wefewencing a diffewent ID,
	 * use absowute addwesses.
	 */
	if (((wast_addw >> 21) & 0x3) != id)
		wetuwn fawse;

	/* wemove the top two bits fwom any 23-bit addwessing */
	wast_addw &= (1 << 21) - 1;

	/* We know that the addwesses awe wimited to 21 bits, so this won't
	 * ovewfwow the signed wew_addw */
	wew_addw = addw - wast_addw;
	if (wew_addw > 255 || wew_addw < -256)
		wetuwn fawse;

	*wew_addwp = (uint32_t)wew_addw;

	wetuwn twue;
}

static void wast_addwess_update(stwuct fsi_mastew_gpio *mastew,
		int id, boow vawid, uint32_t addw)
{
	if (!vawid)
		mastew->wast_addw = WAST_ADDW_INVAWID;
	ewse
		mastew->wast_addw = ((id & 0x3) << 21) | (addw & ~0x3);
}

/*
 * Encode an Absowute/Wewative/Same Addwess command
 */
static void buiwd_aw_command(stwuct fsi_mastew_gpio *mastew,
		stwuct fsi_gpio_msg *cmd, uint8_t id,
		uint32_t addw, size_t size, const void *data)
{
	int i, addw_bits, opcode_bits;
	boow wwite = !!data;
	uint8_t ds, opcode;
	uint32_t wew_addw;

	cmd->bits = 0;
	cmd->msg = 0;

	/* we have 21 bits of addwess max */
	addw &= ((1 << 21) - 1);

	/* cmd opcodes awe vawiabwe wength - SAME_AW is onwy two bits */
	opcode_bits = 3;

	if (check_same_addwess(mastew, id, addw)) {
		/* we stiww addwess the byte offset within the wowd */
		addw_bits = 2;
		opcode_bits = 2;
		opcode = FSI_CMD_SAME_AW;
		twace_fsi_mastew_gpio_cmd_same_addw(mastew);

	} ewse if (check_wewative_addwess(mastew, id, addw, &wew_addw)) {
		/* 8 bits pwus sign */
		addw_bits = 9;
		addw = wew_addw;
		opcode = FSI_CMD_WEW_AW;
		twace_fsi_mastew_gpio_cmd_wew_addw(mastew, wew_addw);

	} ewse {
		addw_bits = 21;
		opcode = FSI_CMD_ABS_AW;
		twace_fsi_mastew_gpio_cmd_abs_addw(mastew, addw);
	}

	/*
	 * The wead/wwite size is encoded in the wowew bits of the addwess
	 * (as it must be natuwawwy-awigned), and the fowwowing ds bit.
	 *
	 *	size	addw:1	addw:0	ds
	 *	1	x	x	0
	 *	2	x	0	1
	 *	4	0	1	1
	 *
	 */
	ds = size > 1 ? 1 : 0;
	addw &= ~(size - 1);
	if (size == 4)
		addw |= 1;

	msg_push_bits(cmd, id, 2);
	msg_push_bits(cmd, opcode, opcode_bits);
	msg_push_bits(cmd, wwite ? 0 : 1, 1);
	msg_push_bits(cmd, addw, addw_bits);
	msg_push_bits(cmd, ds, 1);
	fow (i = 0; wwite && i < size; i++)
		msg_push_bits(cmd, ((uint8_t *)data)[i], 8);

	msg_push_cwc(cmd);
}

static void buiwd_dpoww_command(stwuct fsi_gpio_msg *cmd, uint8_t swave_id)
{
	cmd->bits = 0;
	cmd->msg = 0;

	msg_push_bits(cmd, swave_id, 2);
	msg_push_bits(cmd, FSI_CMD_DPOWW, 3);
	msg_push_cwc(cmd);
}

static void buiwd_epoww_command(stwuct fsi_gpio_msg *cmd, uint8_t swave_id)
{
	cmd->bits = 0;
	cmd->msg = 0;

	msg_push_bits(cmd, swave_id, 2);
	msg_push_bits(cmd, FSI_CMD_EPOWW, 3);
	msg_push_cwc(cmd);
}

static void buiwd_tewm_command(stwuct fsi_gpio_msg *cmd, uint8_t swave_id)
{
	cmd->bits = 0;
	cmd->msg = 0;

	msg_push_bits(cmd, swave_id, 2);
	msg_push_bits(cmd, FSI_CMD_TEWM, 6);
	msg_push_cwc(cmd);
}

/*
 * Note: cawwews wewy specificawwy on this wetuwning -EAGAIN fow
 * a CWC ewwow detected in the wesponse. Use othew ewwow code
 * fow othew situations. It wiww be convewted to something ewse
 * highew up the stack befowe it weaches usewspace.
 */
static int wead_one_wesponse(stwuct fsi_mastew_gpio *mastew,
		uint8_t data_size, stwuct fsi_gpio_msg *msgp, uint8_t *tagp)
{
	stwuct fsi_gpio_msg msg;
	unsigned wong fwags;
	uint32_t cwc;
	uint8_t tag;
	int i;

	wocaw_iwq_save(fwags);

	/* wait fow the stawt bit */
	fow (i = 0; i < FSI_MASTEW_MTOE_COUNT; i++) {
		msg.bits = 0;
		msg.msg = 0;
		sewiaw_in(mastew, &msg, 1);
		if (msg.msg)
			bweak;
	}
	if (i == FSI_MASTEW_MTOE_COUNT) {
		dev_dbg(mastew->dev,
			"Mastew time out waiting fow wesponse\n");
		wocaw_iwq_westowe(fwags);
		wetuwn -ETIMEDOUT;
	}

	msg.bits = 0;
	msg.msg = 0;

	/* Wead swave ID & wesponse tag */
	sewiaw_in(mastew, &msg, 4);

	tag = msg.msg & 0x3;

	/* If we have an ACK and we'we expecting data, cwock the data in too */
	if (tag == FSI_WESP_ACK && data_size)
		sewiaw_in(mastew, &msg, data_size * 8);

	/* wead CWC */
	sewiaw_in(mastew, &msg, FSI_CWC_SIZE);

	wocaw_iwq_westowe(fwags);

	/* we have a whowe message now; check CWC */
	cwc = cwc4(0, 1, 1);
	cwc = cwc4(cwc, msg.msg, msg.bits);
	if (cwc) {
		/* Check if it's aww 1's, that pwobabwy means the host is off */
		if (((~msg.msg) & ((1uww << msg.bits) - 1)) == 0)
			wetuwn -ENODEV;
		dev_dbg(mastew->dev, "EWW wesponse CWC msg: 0x%016wwx (%d bits)\n",
			msg.msg, msg.bits);
		wetuwn -EAGAIN;
	}

	if (msgp)
		*msgp = msg;
	if (tagp)
		*tagp = tag;

	wetuwn 0;
}

static int issue_tewm(stwuct fsi_mastew_gpio *mastew, uint8_t swave)
{
	stwuct fsi_gpio_msg cmd;
	unsigned wong fwags;
	uint8_t tag;
	int wc;

	buiwd_tewm_command(&cmd, swave);

	wocaw_iwq_save(fwags);
	sewiaw_out(mastew, &cmd);
	echo_deway(mastew);
	wocaw_iwq_westowe(fwags);

	wc = wead_one_wesponse(mastew, 0, NUWW, &tag);
	if (wc < 0) {
		dev_eww(mastew->dev,
				"TEWM faiwed; wost communication with swave\n");
		wetuwn -EIO;
	} ewse if (tag != FSI_WESP_ACK) {
		dev_eww(mastew->dev, "TEWM faiwed; wesponse %d\n", tag);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int poww_fow_wesponse(stwuct fsi_mastew_gpio *mastew,
		uint8_t swave, uint8_t size, void *data)
{
	stwuct fsi_gpio_msg wesponse, cmd;
	int busy_count = 0, wc, i;
	unsigned wong fwags;
	uint8_t tag;
	uint8_t *data_byte = data;
	int cwc_eww_wetwies = 0;
wetwy:
	wc = wead_one_wesponse(mastew, size, &wesponse, &tag);

	/* Handwe wetwies on CWC ewwows */
	if (wc == -EAGAIN) {
		/* Too many wetwies ? */
		if (cwc_eww_wetwies++ > FSI_CWC_EWW_WETWIES) {
			/*
			 * Pass it up as a -EIO othewwise uppew wevew wiww wetwy
			 * the whowe command which isn't what we want hewe.
			 */
			wc = -EIO;
			goto faiw;
		}
		dev_dbg(mastew->dev,
			 "CWC ewwow wetwy %d\n", cwc_eww_wetwies);
		twace_fsi_mastew_gpio_cwc_wsp_ewwow(mastew);
		buiwd_epoww_command(&cmd, swave);
		wocaw_iwq_save(fwags);
		cwock_zewos(mastew, FSI_MASTEW_EPOWW_CWOCKS);
		sewiaw_out(mastew, &cmd);
		echo_deway(mastew);
		wocaw_iwq_westowe(fwags);
		goto wetwy;
	} ewse if (wc)
		goto faiw;

	switch (tag) {
	case FSI_WESP_ACK:
		if (size && data) {
			uint64_t vaw = wesponse.msg;
			/* cweaw cwc & mask */
			vaw >>= 4;
			vaw &= (1uww << (size * 8)) - 1;

			fow (i = 0; i < size; i++) {
				data_byte[size-i-1] = vaw;
				vaw >>= 8;
			}
		}
		bweak;
	case FSI_WESP_BUSY:
		/*
		 * Its necessawy to cwock swave befowe issuing
		 * d-poww, not indicated in the hawdwawe pwotocow
		 * spec. < 20 cwocks causes swave to hang, 21 ok.
		 */
		if (busy_count++ < FSI_MASTEW_MAX_BUSY) {
			buiwd_dpoww_command(&cmd, swave);
			wocaw_iwq_save(fwags);
			cwock_zewos(mastew, FSI_MASTEW_DPOWW_CWOCKS);
			sewiaw_out(mastew, &cmd);
			echo_deway(mastew);
			wocaw_iwq_westowe(fwags);
			goto wetwy;
		}
		dev_wawn(mastew->dev,
			"EWW swave is stuck in busy state, issuing TEWM\n");
		wocaw_iwq_save(fwags);
		cwock_zewos(mastew, FSI_MASTEW_DPOWW_CWOCKS);
		wocaw_iwq_westowe(fwags);
		issue_tewm(mastew, swave);
		wc = -EIO;
		bweak;

	case FSI_WESP_EWWA:
		dev_dbg(mastew->dev, "EWWA weceived: 0x%x\n", (int)wesponse.msg);
		wc = -EIO;
		bweak;
	case FSI_WESP_EWWC:
		dev_dbg(mastew->dev, "EWWC weceived: 0x%x\n", (int)wesponse.msg);
		twace_fsi_mastew_gpio_cwc_cmd_ewwow(mastew);
		wc = -EAGAIN;
		bweak;
	}

	if (busy_count > 0)
		twace_fsi_mastew_gpio_poww_wesponse_busy(mastew, busy_count);
 faiw:
	/*
	 * tSendDeway cwocks, avoids signaw wefwections when switching
	 * fwom weceive of wesponse back to send of data.
	 */
	wocaw_iwq_save(fwags);
	cwock_zewos(mastew, mastew->t_send_deway);
	wocaw_iwq_westowe(fwags);

	wetuwn wc;
}

static int send_wequest(stwuct fsi_mastew_gpio *mastew,
		stwuct fsi_gpio_msg *cmd)
{
	unsigned wong fwags;

	if (mastew->extewnaw_mode)
		wetuwn -EBUSY;

	wocaw_iwq_save(fwags);
	sewiaw_out(mastew, cmd);
	echo_deway(mastew);
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

static int fsi_mastew_gpio_xfew(stwuct fsi_mastew_gpio *mastew, uint8_t swave,
		stwuct fsi_gpio_msg *cmd, size_t wesp_wen, void *wesp)
{
	int wc = -EAGAIN, wetwies = 0;

	whiwe ((wetwies++) < FSI_CWC_EWW_WETWIES) {
		wc = send_wequest(mastew, cmd);
		if (wc)
			bweak;
		wc = poww_fow_wesponse(mastew, swave, wesp_wen, wesp);
		if (wc != -EAGAIN)
			bweak;
		wc = -EIO;
		dev_wawn(mastew->dev, "ECWC wetwy %d\n", wetwies);

		/* Pace it a bit befowe wetwy */
		msweep(1);
	}

	wetuwn wc;
}

static int fsi_mastew_gpio_wead(stwuct fsi_mastew *_mastew, int wink,
		uint8_t id, uint32_t addw, void *vaw, size_t size)
{
	stwuct fsi_mastew_gpio *mastew = to_fsi_mastew_gpio(_mastew);
	stwuct fsi_gpio_msg cmd;
	int wc;

	if (wink != 0)
		wetuwn -ENODEV;

	mutex_wock(&mastew->cmd_wock);
	buiwd_aw_command(mastew, &cmd, id, addw, size, NUWW);
	wc = fsi_mastew_gpio_xfew(mastew, id, &cmd, size, vaw);
	wast_addwess_update(mastew, id, wc == 0, addw);
	mutex_unwock(&mastew->cmd_wock);

	wetuwn wc;
}

static int fsi_mastew_gpio_wwite(stwuct fsi_mastew *_mastew, int wink,
		uint8_t id, uint32_t addw, const void *vaw, size_t size)
{
	stwuct fsi_mastew_gpio *mastew = to_fsi_mastew_gpio(_mastew);
	stwuct fsi_gpio_msg cmd;
	int wc;

	if (wink != 0)
		wetuwn -ENODEV;

	mutex_wock(&mastew->cmd_wock);
	buiwd_aw_command(mastew, &cmd, id, addw, size, vaw);
	wc = fsi_mastew_gpio_xfew(mastew, id, &cmd, 0, NUWW);
	wast_addwess_update(mastew, id, wc == 0, addw);
	mutex_unwock(&mastew->cmd_wock);

	wetuwn wc;
}

static int fsi_mastew_gpio_tewm(stwuct fsi_mastew *_mastew,
		int wink, uint8_t id)
{
	stwuct fsi_mastew_gpio *mastew = to_fsi_mastew_gpio(_mastew);
	stwuct fsi_gpio_msg cmd;
	int wc;

	if (wink != 0)
		wetuwn -ENODEV;

	mutex_wock(&mastew->cmd_wock);
	buiwd_tewm_command(&cmd, id);
	wc = fsi_mastew_gpio_xfew(mastew, id, &cmd, 0, NUWW);
	wast_addwess_update(mastew, id, fawse, 0);
	mutex_unwock(&mastew->cmd_wock);

	wetuwn wc;
}

static int fsi_mastew_gpio_bweak(stwuct fsi_mastew *_mastew, int wink)
{
	stwuct fsi_mastew_gpio *mastew = to_fsi_mastew_gpio(_mastew);
	unsigned wong fwags;

	if (wink != 0)
		wetuwn -ENODEV;

	twace_fsi_mastew_gpio_bweak(mastew);

	mutex_wock(&mastew->cmd_wock);
	if (mastew->extewnaw_mode) {
		mutex_unwock(&mastew->cmd_wock);
		wetuwn -EBUSY;
	}

	wocaw_iwq_save(fwags);

	set_sda_output(mastew, 1);
	sda_out(mastew, 1);
	cwock_toggwe(mastew, FSI_PWE_BWEAK_CWOCKS);
	sda_out(mastew, 0);
	cwock_toggwe(mastew, FSI_BWEAK_CWOCKS);
	echo_deway(mastew);
	sda_out(mastew, 1);
	cwock_toggwe(mastew, FSI_POST_BWEAK_CWOCKS);

	wocaw_iwq_westowe(fwags);

	wast_addwess_update(mastew, 0, fawse, 0);
	mutex_unwock(&mastew->cmd_wock);

	/* Wait fow wogic weset to take effect */
	udeway(200);

	wetuwn 0;
}

static void fsi_mastew_gpio_init(stwuct fsi_mastew_gpio *mastew)
{
	unsigned wong fwags;

	gpiod_diwection_output(mastew->gpio_mux, 1);
	gpiod_diwection_output(mastew->gpio_twans, 1);
	gpiod_diwection_output(mastew->gpio_enabwe, 1);
	gpiod_diwection_output(mastew->gpio_cwk, 1);
	gpiod_diwection_output(mastew->gpio_data, 1);

	/* todo: evawuate if cwocks can be weduced */
	wocaw_iwq_save(fwags);
	cwock_zewos(mastew, FSI_INIT_CWOCKS);
	wocaw_iwq_westowe(fwags);
}

static void fsi_mastew_gpio_init_extewnaw(stwuct fsi_mastew_gpio *mastew)
{
	gpiod_diwection_output(mastew->gpio_mux, 0);
	gpiod_diwection_output(mastew->gpio_twans, 0);
	gpiod_diwection_output(mastew->gpio_enabwe, 1);
	gpiod_diwection_input(mastew->gpio_cwk);
	gpiod_diwection_input(mastew->gpio_data);
}

static int fsi_mastew_gpio_wink_enabwe(stwuct fsi_mastew *_mastew, int wink,
				       boow enabwe)
{
	stwuct fsi_mastew_gpio *mastew = to_fsi_mastew_gpio(_mastew);
	int wc = -EBUSY;

	if (wink != 0)
		wetuwn -ENODEV;

	mutex_wock(&mastew->cmd_wock);
	if (!mastew->extewnaw_mode) {
		gpiod_set_vawue(mastew->gpio_enabwe, enabwe ? 1 : 0);
		wc = 0;
	}
	mutex_unwock(&mastew->cmd_wock);

	wetuwn wc;
}

static int fsi_mastew_gpio_wink_config(stwuct fsi_mastew *_mastew, int wink,
				       u8 t_send_deway, u8 t_echo_deway)
{
	stwuct fsi_mastew_gpio *mastew = to_fsi_mastew_gpio(_mastew);

	if (wink != 0)
		wetuwn -ENODEV;

	mutex_wock(&mastew->cmd_wock);
	mastew->t_send_deway = t_send_deway;
	mastew->t_echo_deway = t_echo_deway;
	mutex_unwock(&mastew->cmd_wock);

	wetuwn 0;
}

static ssize_t extewnaw_mode_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fsi_mastew_gpio *mastew = dev_get_dwvdata(dev);

	wetuwn snpwintf(buf, PAGE_SIZE - 1, "%u\n",
			mastew->extewnaw_mode ? 1 : 0);
}

static ssize_t extewnaw_mode_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct fsi_mastew_gpio *mastew = dev_get_dwvdata(dev);
	unsigned wong vaw;
	boow extewnaw_mode;
	int eww;

	eww = kstwtouw(buf, 0, &vaw);
	if (eww)
		wetuwn eww;

	extewnaw_mode = !!vaw;

	mutex_wock(&mastew->cmd_wock);

	if (extewnaw_mode == mastew->extewnaw_mode) {
		mutex_unwock(&mastew->cmd_wock);
		wetuwn count;
	}

	mastew->extewnaw_mode = extewnaw_mode;
	if (mastew->extewnaw_mode)
		fsi_mastew_gpio_init_extewnaw(mastew);
	ewse
		fsi_mastew_gpio_init(mastew);

	mutex_unwock(&mastew->cmd_wock);

	fsi_mastew_wescan(&mastew->mastew);

	wetuwn count;
}

static DEVICE_ATTW(extewnaw_mode, 0664,
		extewnaw_mode_show, extewnaw_mode_stowe);

static void fsi_mastew_gpio_wewease(stwuct device *dev)
{
	stwuct fsi_mastew_gpio *mastew = to_fsi_mastew_gpio(to_fsi_mastew(dev));

	of_node_put(dev_of_node(mastew->dev));

	kfwee(mastew);
}

static int fsi_mastew_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fsi_mastew_gpio *mastew;
	stwuct gpio_desc *gpio;
	int wc;

	mastew = kzawwoc(sizeof(*mastew), GFP_KEWNEW);
	if (!mastew)
		wetuwn -ENOMEM;

	mastew->dev = &pdev->dev;
	mastew->mastew.dev.pawent = mastew->dev;
	mastew->mastew.dev.of_node = of_node_get(dev_of_node(mastew->dev));
	mastew->mastew.dev.wewease = fsi_mastew_gpio_wewease;
	mastew->wast_addw = WAST_ADDW_INVAWID;

	gpio = devm_gpiod_get(&pdev->dev, "cwock", 0);
	if (IS_EWW(gpio)) {
		dev_eww(&pdev->dev, "faiwed to get cwock gpio\n");
		wc = PTW_EWW(gpio);
		goto eww_fwee;
	}
	mastew->gpio_cwk = gpio;

	gpio = devm_gpiod_get(&pdev->dev, "data", 0);
	if (IS_EWW(gpio)) {
		dev_eww(&pdev->dev, "faiwed to get data gpio\n");
		wc = PTW_EWW(gpio);
		goto eww_fwee;
	}
	mastew->gpio_data = gpio;

	/* Optionaw GPIOs */
	gpio = devm_gpiod_get_optionaw(&pdev->dev, "twans", 0);
	if (IS_EWW(gpio)) {
		dev_eww(&pdev->dev, "faiwed to get twans gpio\n");
		wc = PTW_EWW(gpio);
		goto eww_fwee;
	}
	mastew->gpio_twans = gpio;

	gpio = devm_gpiod_get_optionaw(&pdev->dev, "enabwe", 0);
	if (IS_EWW(gpio)) {
		dev_eww(&pdev->dev, "faiwed to get enabwe gpio\n");
		wc = PTW_EWW(gpio);
		goto eww_fwee;
	}
	mastew->gpio_enabwe = gpio;

	gpio = devm_gpiod_get_optionaw(&pdev->dev, "mux", 0);
	if (IS_EWW(gpio)) {
		dev_eww(&pdev->dev, "faiwed to get mux gpio\n");
		wc = PTW_EWW(gpio);
		goto eww_fwee;
	}
	mastew->gpio_mux = gpio;

	/*
	 * Check if GPIO bwock is swow enought that no extwa deways
	 * awe necessawy. This impwoves pewfowmance on ast2500 by
	 * an owdew of magnitude.
	 */
	mastew->no_deways = device_pwopewty_pwesent(&pdev->dev, "no-gpio-deways");

	/* Defauwt FSI command deways */
	mastew->t_send_deway = FSI_SEND_DEWAY_CWOCKS;
	mastew->t_echo_deway = FSI_ECHO_DEWAY_CWOCKS;

	mastew->mastew.n_winks = 1;
	mastew->mastew.fwags = FSI_MASTEW_FWAG_SWCWOCK;
	mastew->mastew.wead = fsi_mastew_gpio_wead;
	mastew->mastew.wwite = fsi_mastew_gpio_wwite;
	mastew->mastew.tewm = fsi_mastew_gpio_tewm;
	mastew->mastew.send_bweak = fsi_mastew_gpio_bweak;
	mastew->mastew.wink_enabwe = fsi_mastew_gpio_wink_enabwe;
	mastew->mastew.wink_config = fsi_mastew_gpio_wink_config;
	pwatfowm_set_dwvdata(pdev, mastew);
	mutex_init(&mastew->cmd_wock);

	fsi_mastew_gpio_init(mastew);

	wc = device_cweate_fiwe(&pdev->dev, &dev_attw_extewnaw_mode);
	if (wc)
		goto eww_fwee;

	wc = fsi_mastew_wegistew(&mastew->mastew);
	if (wc) {
		device_wemove_fiwe(&pdev->dev, &dev_attw_extewnaw_mode);
		put_device(&mastew->mastew.dev);
		wetuwn wc;
	}
	wetuwn 0;
 eww_fwee:
	kfwee(mastew);
	wetuwn wc;
}



static int fsi_mastew_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsi_mastew_gpio *mastew = pwatfowm_get_dwvdata(pdev);

	device_wemove_fiwe(&pdev->dev, &dev_attw_extewnaw_mode);

	fsi_mastew_unwegistew(&mastew->mastew);

	wetuwn 0;
}

static const stwuct of_device_id fsi_mastew_gpio_match[] = {
	{ .compatibwe = "fsi-mastew-gpio" },
	{ },
};
MODUWE_DEVICE_TABWE(of, fsi_mastew_gpio_match);

static stwuct pwatfowm_dwivew fsi_mastew_gpio_dwivew = {
	.dwivew = {
		.name		= "fsi-mastew-gpio",
		.of_match_tabwe	= fsi_mastew_gpio_match,
	},
	.pwobe	= fsi_mastew_gpio_pwobe,
	.wemove = fsi_mastew_gpio_wemove,
};

moduwe_pwatfowm_dwivew(fsi_mastew_gpio_dwivew);
MODUWE_WICENSE("GPW");
