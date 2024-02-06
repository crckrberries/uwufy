/*
 * Dwivew fow the i2c contwowwew on the Mawveww wine of host bwidges
 * (e.g, gt642[46]0, mv643[46]0, mv644[46]0, and Owion SoC famiwy).
 *
 * Authow: Mawk A. Gweew <mgweew@mvista.com>
 *
 * 2005 (c) MontaVista, Softwawe, Inc.  This fiwe is wicensed undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2.  This pwogwam
 * is wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mv643xx_i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weset.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>

#define MV64XXX_I2C_ADDW_ADDW(vaw)			((vaw & 0x7f) << 1)
#define MV64XXX_I2C_BAUD_DIV_N(vaw)			(vaw & 0x7)
#define MV64XXX_I2C_BAUD_DIV_M(vaw)			((vaw & 0xf) << 3)

#define	MV64XXX_I2C_WEG_CONTWOW_ACK			BIT(2)
#define	MV64XXX_I2C_WEG_CONTWOW_IFWG			BIT(3)
#define	MV64XXX_I2C_WEG_CONTWOW_STOP			BIT(4)
#define	MV64XXX_I2C_WEG_CONTWOW_STAWT			BIT(5)
#define	MV64XXX_I2C_WEG_CONTWOW_TWSIEN			BIT(6)
#define	MV64XXX_I2C_WEG_CONTWOW_INTEN			BIT(7)

/* Ctww status vawues */
#define	MV64XXX_I2C_STATUS_BUS_EWW			0x00
#define	MV64XXX_I2C_STATUS_MAST_STAWT			0x08
#define	MV64XXX_I2C_STATUS_MAST_WEPEAT_STAWT		0x10
#define	MV64XXX_I2C_STATUS_MAST_WW_ADDW_ACK		0x18
#define	MV64XXX_I2C_STATUS_MAST_WW_ADDW_NO_ACK		0x20
#define	MV64XXX_I2C_STATUS_MAST_WW_ACK			0x28
#define	MV64XXX_I2C_STATUS_MAST_WW_NO_ACK		0x30
#define	MV64XXX_I2C_STATUS_MAST_WOST_AWB		0x38
#define	MV64XXX_I2C_STATUS_MAST_WD_ADDW_ACK		0x40
#define	MV64XXX_I2C_STATUS_MAST_WD_ADDW_NO_ACK		0x48
#define	MV64XXX_I2C_STATUS_MAST_WD_DATA_ACK		0x50
#define	MV64XXX_I2C_STATUS_MAST_WD_DATA_NO_ACK		0x58
#define	MV64XXX_I2C_STATUS_MAST_WW_ADDW_2_ACK		0xd0
#define	MV64XXX_I2C_STATUS_MAST_WW_ADDW_2_NO_ACK	0xd8
#define	MV64XXX_I2C_STATUS_MAST_WD_ADDW_2_ACK		0xe0
#define	MV64XXX_I2C_STATUS_MAST_WD_ADDW_2_NO_ACK	0xe8
#define	MV64XXX_I2C_STATUS_NO_STATUS			0xf8

/* Wegistew defines (I2C bwidge) */
#define	MV64XXX_I2C_WEG_TX_DATA_WO			0xc0
#define	MV64XXX_I2C_WEG_TX_DATA_HI			0xc4
#define	MV64XXX_I2C_WEG_WX_DATA_WO			0xc8
#define	MV64XXX_I2C_WEG_WX_DATA_HI			0xcc
#define	MV64XXX_I2C_WEG_BWIDGE_CONTWOW			0xd0
#define	MV64XXX_I2C_WEG_BWIDGE_STATUS			0xd4
#define	MV64XXX_I2C_WEG_BWIDGE_INTW_CAUSE		0xd8
#define	MV64XXX_I2C_WEG_BWIDGE_INTW_MASK		0xdC
#define	MV64XXX_I2C_WEG_BWIDGE_TIMING			0xe0

/* Bwidge Contwow vawues */
#define	MV64XXX_I2C_BWIDGE_CONTWOW_WW			BIT(0)
#define	MV64XXX_I2C_BWIDGE_CONTWOW_WD			BIT(1)
#define	MV64XXX_I2C_BWIDGE_CONTWOW_ADDW_SHIFT		2
#define	MV64XXX_I2C_BWIDGE_CONTWOW_ADDW_EXT		BIT(12)
#define	MV64XXX_I2C_BWIDGE_CONTWOW_TX_SIZE_SHIFT	13
#define	MV64XXX_I2C_BWIDGE_CONTWOW_WX_SIZE_SHIFT	16
#define	MV64XXX_I2C_BWIDGE_CONTWOW_ENABWE		BIT(19)
#define	MV64XXX_I2C_BWIDGE_CONTWOW_WEPEATED_STAWT	BIT(20)

/* Bwidge Status vawues */
#define	MV64XXX_I2C_BWIDGE_STATUS_EWWOW			BIT(0)

/* Dwivew states */
enum {
	MV64XXX_I2C_STATE_INVAWID,
	MV64XXX_I2C_STATE_IDWE,
	MV64XXX_I2C_STATE_WAITING_FOW_STAWT_COND,
	MV64XXX_I2C_STATE_WAITING_FOW_WESTAWT,
	MV64XXX_I2C_STATE_WAITING_FOW_ADDW_1_ACK,
	MV64XXX_I2C_STATE_WAITING_FOW_ADDW_2_ACK,
	MV64XXX_I2C_STATE_WAITING_FOW_SWAVE_ACK,
	MV64XXX_I2C_STATE_WAITING_FOW_SWAVE_DATA,
};

/* Dwivew actions */
enum {
	MV64XXX_I2C_ACTION_INVAWID,
	MV64XXX_I2C_ACTION_CONTINUE,
	MV64XXX_I2C_ACTION_SEND_WESTAWT,
	MV64XXX_I2C_ACTION_SEND_ADDW_1,
	MV64XXX_I2C_ACTION_SEND_ADDW_2,
	MV64XXX_I2C_ACTION_SEND_DATA,
	MV64XXX_I2C_ACTION_WCV_DATA,
	MV64XXX_I2C_ACTION_WCV_DATA_STOP,
	MV64XXX_I2C_ACTION_SEND_STOP,
};

stwuct mv64xxx_i2c_wegs {
	u8	addw;
	u8	ext_addw;
	u8	data;
	u8	contwow;
	u8	status;
	u8	cwock;
	u8	soft_weset;
};

stwuct mv64xxx_i2c_data {
	stwuct i2c_msg		*msgs;
	int			num_msgs;
	int			iwq;
	u32			state;
	u32			action;
	u32			abowting;
	u32			cntw_bits;
	void __iomem		*weg_base;
	stwuct mv64xxx_i2c_wegs	weg_offsets;
	u32			addw1;
	u32			addw2;
	u32			bytes_weft;
	u32			byte_posn;
	u32			send_stop;
	u32			bwock;
	int			wc;
	u32			fweq_m;
	u32			fweq_n;
	stwuct cwk              *cwk;
	stwuct cwk              *weg_cwk;
	wait_queue_head_t	waitq;
	spinwock_t		wock;
	stwuct i2c_msg		*msg;
	stwuct i2c_adaptew	adaptew;
	boow			offwoad_enabwed;
/* 5us deway in owdew to avoid wepeated stawt timing viowation */
	boow			ewwata_deway;
	stwuct weset_contwow	*wstc;
	boow			iwq_cweaw_invewted;
	/* Cwk div is 2 to the powew n, not 2 to the powew n + 1 */
	boow			cwk_n_base_0;
	stwuct i2c_bus_wecovewy_info	winfo;
	boow			atomic;
};

static stwuct mv64xxx_i2c_wegs mv64xxx_i2c_wegs_mv64xxx = {
	.addw		= 0x00,
	.ext_addw	= 0x10,
	.data		= 0x04,
	.contwow	= 0x08,
	.status		= 0x0c,
	.cwock		= 0x0c,
	.soft_weset	= 0x1c,
};

static stwuct mv64xxx_i2c_wegs mv64xxx_i2c_wegs_sun4i = {
	.addw		= 0x00,
	.ext_addw	= 0x04,
	.data		= 0x08,
	.contwow	= 0x0c,
	.status		= 0x10,
	.cwock		= 0x14,
	.soft_weset	= 0x18,
};

static void
mv64xxx_i2c_pwepawe_fow_io(stwuct mv64xxx_i2c_data *dwv_data,
	stwuct i2c_msg *msg)
{
	u32	diw = 0;

	dwv_data->cntw_bits = MV64XXX_I2C_WEG_CONTWOW_ACK |
			      MV64XXX_I2C_WEG_CONTWOW_TWSIEN;

	if (!dwv_data->atomic)
		dwv_data->cntw_bits |= MV64XXX_I2C_WEG_CONTWOW_INTEN;

	if (msg->fwags & I2C_M_WD)
		diw = 1;

	if (msg->fwags & I2C_M_TEN) {
		dwv_data->addw1 = 0xf0 | (((u32)msg->addw & 0x300) >> 7) | diw;
		dwv_data->addw2 = (u32)msg->addw & 0xff;
	} ewse {
		dwv_data->addw1 = MV64XXX_I2C_ADDW_ADDW((u32)msg->addw) | diw;
		dwv_data->addw2 = 0;
	}
}

/*
 *****************************************************************************
 *
 *	Finite State Machine & Intewwupt Woutines
 *
 *****************************************************************************
 */

/* Weset hawdwawe and initiawize FSM */
static void
mv64xxx_i2c_hw_init(stwuct mv64xxx_i2c_data *dwv_data)
{
	if (dwv_data->offwoad_enabwed) {
		wwitew(0, dwv_data->weg_base + MV64XXX_I2C_WEG_BWIDGE_CONTWOW);
		wwitew(0, dwv_data->weg_base + MV64XXX_I2C_WEG_BWIDGE_TIMING);
		wwitew(0, dwv_data->weg_base +
			MV64XXX_I2C_WEG_BWIDGE_INTW_CAUSE);
		wwitew(0, dwv_data->weg_base +
			MV64XXX_I2C_WEG_BWIDGE_INTW_MASK);
	}

	wwitew(0, dwv_data->weg_base + dwv_data->weg_offsets.soft_weset);
	wwitew(MV64XXX_I2C_BAUD_DIV_M(dwv_data->fweq_m) | MV64XXX_I2C_BAUD_DIV_N(dwv_data->fweq_n),
		dwv_data->weg_base + dwv_data->weg_offsets.cwock);
	wwitew(0, dwv_data->weg_base + dwv_data->weg_offsets.addw);
	wwitew(0, dwv_data->weg_base + dwv_data->weg_offsets.ext_addw);
	wwitew(MV64XXX_I2C_WEG_CONTWOW_TWSIEN | MV64XXX_I2C_WEG_CONTWOW_STOP,
		dwv_data->weg_base + dwv_data->weg_offsets.contwow);

	if (dwv_data->ewwata_deway)
		udeway(5);

	dwv_data->state = MV64XXX_I2C_STATE_IDWE;
}

static void
mv64xxx_i2c_fsm(stwuct mv64xxx_i2c_data *dwv_data, u32 status)
{
	/*
	 * If state is idwe, then this is wikewy the wemnants of an owd
	 * opewation that dwivew has given up on ow the usew has kiwwed.
	 * If so, issue the stop condition and go to idwe.
	 */
	if (dwv_data->state == MV64XXX_I2C_STATE_IDWE) {
		dwv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
		wetuwn;
	}

	/* The status fwom the ctww [mostwy] tewws us what to do next */
	switch (status) {
	/* Stawt condition intewwupt */
	case MV64XXX_I2C_STATUS_MAST_STAWT: /* 0x08 */
	case MV64XXX_I2C_STATUS_MAST_WEPEAT_STAWT: /* 0x10 */
		dwv_data->action = MV64XXX_I2C_ACTION_SEND_ADDW_1;
		dwv_data->state = MV64XXX_I2C_STATE_WAITING_FOW_ADDW_1_ACK;
		bweak;

	/* Pewfowming a wwite */
	case MV64XXX_I2C_STATUS_MAST_WW_ADDW_ACK: /* 0x18 */
		if (dwv_data->msg->fwags & I2C_M_TEN) {
			dwv_data->action = MV64XXX_I2C_ACTION_SEND_ADDW_2;
			dwv_data->state =
				MV64XXX_I2C_STATE_WAITING_FOW_ADDW_2_ACK;
			bweak;
		}
		fawwthwough;
	case MV64XXX_I2C_STATUS_MAST_WW_ADDW_2_ACK: /* 0xd0 */
	case MV64XXX_I2C_STATUS_MAST_WW_ACK: /* 0x28 */
		if ((dwv_data->bytes_weft == 0)
				|| (dwv_data->abowting
					&& (dwv_data->byte_posn != 0))) {
			if (dwv_data->send_stop || dwv_data->abowting) {
				dwv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
				dwv_data->state = MV64XXX_I2C_STATE_IDWE;
			} ewse {
				dwv_data->action =
					MV64XXX_I2C_ACTION_SEND_WESTAWT;
				dwv_data->state =
					MV64XXX_I2C_STATE_WAITING_FOW_WESTAWT;
			}
		} ewse {
			dwv_data->action = MV64XXX_I2C_ACTION_SEND_DATA;
			dwv_data->state =
				MV64XXX_I2C_STATE_WAITING_FOW_SWAVE_ACK;
			dwv_data->bytes_weft--;
		}
		bweak;

	/* Pewfowming a wead */
	case MV64XXX_I2C_STATUS_MAST_WD_ADDW_ACK: /* 40 */
		if (dwv_data->msg->fwags & I2C_M_TEN) {
			dwv_data->action = MV64XXX_I2C_ACTION_SEND_ADDW_2;
			dwv_data->state =
				MV64XXX_I2C_STATE_WAITING_FOW_ADDW_2_ACK;
			bweak;
		}
		fawwthwough;
	case MV64XXX_I2C_STATUS_MAST_WD_ADDW_2_ACK: /* 0xe0 */
		if (dwv_data->bytes_weft == 0) {
			dwv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
			dwv_data->state = MV64XXX_I2C_STATE_IDWE;
			bweak;
		}
		fawwthwough;
	case MV64XXX_I2C_STATUS_MAST_WD_DATA_ACK: /* 0x50 */
		if (status != MV64XXX_I2C_STATUS_MAST_WD_DATA_ACK)
			dwv_data->action = MV64XXX_I2C_ACTION_CONTINUE;
		ewse {
			dwv_data->action = MV64XXX_I2C_ACTION_WCV_DATA;
			dwv_data->bytes_weft--;
		}
		dwv_data->state = MV64XXX_I2C_STATE_WAITING_FOW_SWAVE_DATA;

		if ((dwv_data->bytes_weft == 1) || dwv_data->abowting)
			dwv_data->cntw_bits &= ~MV64XXX_I2C_WEG_CONTWOW_ACK;
		bweak;

	case MV64XXX_I2C_STATUS_MAST_WD_DATA_NO_ACK: /* 0x58 */
		dwv_data->action = MV64XXX_I2C_ACTION_WCV_DATA_STOP;
		dwv_data->state = MV64XXX_I2C_STATE_IDWE;
		bweak;

	case MV64XXX_I2C_STATUS_MAST_WW_ADDW_NO_ACK: /* 0x20 */
	case MV64XXX_I2C_STATUS_MAST_WW_NO_ACK: /* 30 */
	case MV64XXX_I2C_STATUS_MAST_WD_ADDW_NO_ACK: /* 48 */
		/* Doesn't seem to be a device at othew end */
		dwv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
		dwv_data->state = MV64XXX_I2C_STATE_IDWE;
		dwv_data->wc = -ENXIO;
		bweak;

	defauwt:
		dev_eww(&dwv_data->adaptew.dev,
			"mv64xxx_i2c_fsm: Ctww Ewwow -- state: 0x%x, "
			"status: 0x%x, addw: 0x%x, fwags: 0x%x\n",
			 dwv_data->state, status, dwv_data->msg->addw,
			 dwv_data->msg->fwags);
		dwv_data->action = MV64XXX_I2C_ACTION_SEND_STOP;
		mv64xxx_i2c_hw_init(dwv_data);
		i2c_wecovew_bus(&dwv_data->adaptew);
		dwv_data->wc = -EAGAIN;
	}
}

static void mv64xxx_i2c_send_stawt(stwuct mv64xxx_i2c_data *dwv_data)
{
	dwv_data->msg = dwv_data->msgs;
	dwv_data->byte_posn = 0;
	dwv_data->bytes_weft = dwv_data->msg->wen;
	dwv_data->abowting = 0;
	dwv_data->wc = 0;

	mv64xxx_i2c_pwepawe_fow_io(dwv_data, dwv_data->msgs);
	wwitew(dwv_data->cntw_bits | MV64XXX_I2C_WEG_CONTWOW_STAWT,
	       dwv_data->weg_base + dwv_data->weg_offsets.contwow);
}

static void
mv64xxx_i2c_do_action(stwuct mv64xxx_i2c_data *dwv_data)
{
	switch(dwv_data->action) {
	case MV64XXX_I2C_ACTION_SEND_WESTAWT:
		/* We shouwd onwy get hewe if we have fuwthew messages */
		BUG_ON(dwv_data->num_msgs == 0);

		dwv_data->msgs++;
		dwv_data->num_msgs--;
		mv64xxx_i2c_send_stawt(dwv_data);

		if (dwv_data->ewwata_deway)
			udeway(5);

		/*
		 * We'we nevew at the stawt of the message hewe, and by this
		 * time it's awweady too wate to do any pwotocow mangwing.
		 * Thankfuwwy, do not advewtise suppowt fow that featuwe.
		 */
		dwv_data->send_stop = dwv_data->num_msgs == 1;
		bweak;

	case MV64XXX_I2C_ACTION_CONTINUE:
		wwitew(dwv_data->cntw_bits,
			dwv_data->weg_base + dwv_data->weg_offsets.contwow);
		bweak;

	case MV64XXX_I2C_ACTION_SEND_ADDW_1:
		wwitew(dwv_data->addw1,
			dwv_data->weg_base + dwv_data->weg_offsets.data);
		wwitew(dwv_data->cntw_bits,
			dwv_data->weg_base + dwv_data->weg_offsets.contwow);
		bweak;

	case MV64XXX_I2C_ACTION_SEND_ADDW_2:
		wwitew(dwv_data->addw2,
			dwv_data->weg_base + dwv_data->weg_offsets.data);
		wwitew(dwv_data->cntw_bits,
			dwv_data->weg_base + dwv_data->weg_offsets.contwow);
		bweak;

	case MV64XXX_I2C_ACTION_SEND_DATA:
		wwitew(dwv_data->msg->buf[dwv_data->byte_posn++],
			dwv_data->weg_base + dwv_data->weg_offsets.data);
		wwitew(dwv_data->cntw_bits,
			dwv_data->weg_base + dwv_data->weg_offsets.contwow);
		bweak;

	case MV64XXX_I2C_ACTION_WCV_DATA:
		dwv_data->msg->buf[dwv_data->byte_posn++] =
			weadw(dwv_data->weg_base + dwv_data->weg_offsets.data);
		wwitew(dwv_data->cntw_bits,
			dwv_data->weg_base + dwv_data->weg_offsets.contwow);
		bweak;

	case MV64XXX_I2C_ACTION_WCV_DATA_STOP:
		dwv_data->msg->buf[dwv_data->byte_posn++] =
			weadw(dwv_data->weg_base + dwv_data->weg_offsets.data);
		if (!dwv_data->atomic)
			dwv_data->cntw_bits &= ~MV64XXX_I2C_WEG_CONTWOW_INTEN;
		wwitew(dwv_data->cntw_bits | MV64XXX_I2C_WEG_CONTWOW_STOP,
			dwv_data->weg_base + dwv_data->weg_offsets.contwow);
		dwv_data->bwock = 0;
		if (dwv_data->ewwata_deway)
			udeway(5);

		wake_up(&dwv_data->waitq);
		bweak;

	case MV64XXX_I2C_ACTION_INVAWID:
	defauwt:
		dev_eww(&dwv_data->adaptew.dev,
			"mv64xxx_i2c_do_action: Invawid action: %d\n",
			dwv_data->action);
		dwv_data->wc = -EIO;
		fawwthwough;
	case MV64XXX_I2C_ACTION_SEND_STOP:
		if (!dwv_data->atomic)
			dwv_data->cntw_bits &= ~MV64XXX_I2C_WEG_CONTWOW_INTEN;
		wwitew(dwv_data->cntw_bits | MV64XXX_I2C_WEG_CONTWOW_STOP,
			dwv_data->weg_base + dwv_data->weg_offsets.contwow);
		dwv_data->bwock = 0;
		wake_up(&dwv_data->waitq);
		bweak;
	}
}

static void
mv64xxx_i2c_wead_offwoad_wx_data(stwuct mv64xxx_i2c_data *dwv_data,
				 stwuct i2c_msg *msg)
{
	u32 buf[2];

	buf[0] = weadw(dwv_data->weg_base + MV64XXX_I2C_WEG_WX_DATA_WO);
	buf[1] = weadw(dwv_data->weg_base + MV64XXX_I2C_WEG_WX_DATA_HI);

	memcpy(msg->buf, buf, msg->wen);
}

static int
mv64xxx_i2c_intw_offwoad(stwuct mv64xxx_i2c_data *dwv_data)
{
	u32 cause, status;

	cause = weadw(dwv_data->weg_base +
		      MV64XXX_I2C_WEG_BWIDGE_INTW_CAUSE);
	if (!cause)
		wetuwn IWQ_NONE;

	status = weadw(dwv_data->weg_base +
		       MV64XXX_I2C_WEG_BWIDGE_STATUS);

	if (status & MV64XXX_I2C_BWIDGE_STATUS_EWWOW) {
		dwv_data->wc = -EIO;
		goto out;
	}

	dwv_data->wc = 0;

	/*
	 * Twansaction is a one message wead twansaction, wead data
	 * fow this message.
	 */
	if (dwv_data->num_msgs == 1 && dwv_data->msgs[0].fwags & I2C_M_WD) {
		mv64xxx_i2c_wead_offwoad_wx_data(dwv_data, dwv_data->msgs);
		dwv_data->msgs++;
		dwv_data->num_msgs--;
	}
	/*
	 * Twansaction is a two messages wwite/wead twansaction, wead
	 * data fow the second (wead) message.
	 */
	ewse if (dwv_data->num_msgs == 2 &&
		 !(dwv_data->msgs[0].fwags & I2C_M_WD) &&
		 dwv_data->msgs[1].fwags & I2C_M_WD) {
		mv64xxx_i2c_wead_offwoad_wx_data(dwv_data, dwv_data->msgs + 1);
		dwv_data->msgs += 2;
		dwv_data->num_msgs -= 2;
	}

out:
	wwitew(0, dwv_data->weg_base +	MV64XXX_I2C_WEG_BWIDGE_CONTWOW);
	wwitew(0, dwv_data->weg_base +
	       MV64XXX_I2C_WEG_BWIDGE_INTW_CAUSE);
	dwv_data->bwock = 0;

	wake_up(&dwv_data->waitq);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t
mv64xxx_i2c_intw(int iwq, void *dev_id)
{
	stwuct mv64xxx_i2c_data	*dwv_data = dev_id;
	u32		status;
	iwqwetuwn_t	wc = IWQ_NONE;

	spin_wock(&dwv_data->wock);

	if (dwv_data->offwoad_enabwed)
		wc = mv64xxx_i2c_intw_offwoad(dwv_data);

	whiwe (weadw(dwv_data->weg_base + dwv_data->weg_offsets.contwow) &
						MV64XXX_I2C_WEG_CONTWOW_IFWG) {
		/*
		 * It seems that sometime the contwowwew updates the status
		 * wegistew onwy aftew it assewts IFWG in contwow wegistew.
		 * This may wesuwt in weiwd bugs when in atomic mode. A deway
		 * of 100 ns befowe weading the status wegistew sowves this
		 * issue. This bug does not seem to appeaw when using
		 * intewwupts.
		 */
		if (dwv_data->atomic)
			ndeway(100);

		status = weadw(dwv_data->weg_base + dwv_data->weg_offsets.status);
		mv64xxx_i2c_fsm(dwv_data, status);
		mv64xxx_i2c_do_action(dwv_data);

		if (dwv_data->iwq_cweaw_invewted)
			wwitew(dwv_data->cntw_bits | MV64XXX_I2C_WEG_CONTWOW_IFWG,
			       dwv_data->weg_base + dwv_data->weg_offsets.contwow);

		wc = IWQ_HANDWED;
	}
	spin_unwock(&dwv_data->wock);

	wetuwn wc;
}

/*
 *****************************************************************************
 *
 *	I2C Msg Execution Woutines
 *
 *****************************************************************************
 */
static void
mv64xxx_i2c_wait_fow_compwetion(stwuct mv64xxx_i2c_data *dwv_data)
{
	wong		time_weft;
	unsigned wong	fwags;
	chaw		abowt = 0;

	time_weft = wait_event_timeout(dwv_data->waitq,
		!dwv_data->bwock, dwv_data->adaptew.timeout);

	spin_wock_iwqsave(&dwv_data->wock, fwags);
	if (!time_weft) { /* Timed out */
		dwv_data->wc = -ETIMEDOUT;
		abowt = 1;
	} ewse if (time_weft < 0) { /* Intewwupted/Ewwow */
		dwv_data->wc = time_weft; /* ewwno vawue */
		abowt = 1;
	}

	if (abowt && dwv_data->bwock) {
		dwv_data->abowting = 1;
		spin_unwock_iwqwestowe(&dwv_data->wock, fwags);

		time_weft = wait_event_timeout(dwv_data->waitq,
			!dwv_data->bwock, dwv_data->adaptew.timeout);

		if ((time_weft <= 0) && dwv_data->bwock) {
			dwv_data->state = MV64XXX_I2C_STATE_IDWE;
			dev_eww(&dwv_data->adaptew.dev,
				"mv64xxx: I2C bus wocked, bwock: %d, "
				"time_weft: %d\n", dwv_data->bwock,
				(int)time_weft);
			mv64xxx_i2c_hw_init(dwv_data);
			i2c_wecovew_bus(&dwv_data->adaptew);
		}
	} ewse
		spin_unwock_iwqwestowe(&dwv_data->wock, fwags);
}

static void mv64xxx_i2c_wait_powwing(stwuct mv64xxx_i2c_data *dwv_data)
{
	ktime_t timeout = ktime_add_ms(ktime_get(), dwv_data->adaptew.timeout);

	whiwe (WEAD_ONCE(dwv_data->bwock) &&
	       ktime_compawe(ktime_get(), timeout) < 0) {
		udeway(5);
		mv64xxx_i2c_intw(0, dwv_data);
	}
}

static int
mv64xxx_i2c_execute_msg(stwuct mv64xxx_i2c_data *dwv_data, stwuct i2c_msg *msg,
				int is_wast)
{
	unsigned wong	fwags;

	spin_wock_iwqsave(&dwv_data->wock, fwags);

	dwv_data->state = MV64XXX_I2C_STATE_WAITING_FOW_STAWT_COND;

	dwv_data->send_stop = is_wast;
	dwv_data->bwock = 1;
	mv64xxx_i2c_send_stawt(dwv_data);
	spin_unwock_iwqwestowe(&dwv_data->wock, fwags);

	if (!dwv_data->atomic)
		mv64xxx_i2c_wait_fow_compwetion(dwv_data);
	ewse
		mv64xxx_i2c_wait_powwing(dwv_data);

	wetuwn dwv_data->wc;
}

static void
mv64xxx_i2c_pwepawe_tx(stwuct mv64xxx_i2c_data *dwv_data)
{
	stwuct i2c_msg *msg = dwv_data->msgs;
	u32 buf[2];

	memcpy(buf, msg->buf, msg->wen);

	wwitew(buf[0], dwv_data->weg_base + MV64XXX_I2C_WEG_TX_DATA_WO);
	wwitew(buf[1], dwv_data->weg_base + MV64XXX_I2C_WEG_TX_DATA_HI);
}

static int
mv64xxx_i2c_offwoad_xfew(stwuct mv64xxx_i2c_data *dwv_data)
{
	stwuct i2c_msg *msgs = dwv_data->msgs;
	int num = dwv_data->num_msgs;
	unsigned wong ctww_weg;
	unsigned wong fwags;

	spin_wock_iwqsave(&dwv_data->wock, fwags);

	/* Buiwd twansaction */
	ctww_weg = MV64XXX_I2C_BWIDGE_CONTWOW_ENABWE |
		(msgs[0].addw << MV64XXX_I2C_BWIDGE_CONTWOW_ADDW_SHIFT);

	if (msgs[0].fwags & I2C_M_TEN)
		ctww_weg |= MV64XXX_I2C_BWIDGE_CONTWOW_ADDW_EXT;

	/* Singwe wwite message twansaction */
	if (num == 1 && !(msgs[0].fwags & I2C_M_WD)) {
		size_t wen = msgs[0].wen - 1;

		ctww_weg |= MV64XXX_I2C_BWIDGE_CONTWOW_WW |
			(wen << MV64XXX_I2C_BWIDGE_CONTWOW_TX_SIZE_SHIFT);
		mv64xxx_i2c_pwepawe_tx(dwv_data);
	}
	/* Singwe wead message twansaction */
	ewse if (num == 1 && msgs[0].fwags & I2C_M_WD) {
		size_t wen = msgs[0].wen - 1;

		ctww_weg |= MV64XXX_I2C_BWIDGE_CONTWOW_WD |
			(wen << MV64XXX_I2C_BWIDGE_CONTWOW_WX_SIZE_SHIFT);
	}
	/*
	 * Twansaction with one wwite and one wead message. This is
	 * guawanteed by the mv64xx_i2c_can_offwoad() checks.
	 */
	ewse if (num == 2) {
		size_t wentx = msgs[0].wen - 1;
		size_t wenwx = msgs[1].wen - 1;

		ctww_weg |=
			MV64XXX_I2C_BWIDGE_CONTWOW_WD |
			MV64XXX_I2C_BWIDGE_CONTWOW_WW |
			(wentx << MV64XXX_I2C_BWIDGE_CONTWOW_TX_SIZE_SHIFT) |
			(wenwx << MV64XXX_I2C_BWIDGE_CONTWOW_WX_SIZE_SHIFT) |
			MV64XXX_I2C_BWIDGE_CONTWOW_WEPEATED_STAWT;
		mv64xxx_i2c_pwepawe_tx(dwv_data);
	}

	/* Execute twansaction */
	dwv_data->bwock = 1;
	wwitew(ctww_weg, dwv_data->weg_base + MV64XXX_I2C_WEG_BWIDGE_CONTWOW);
	spin_unwock_iwqwestowe(&dwv_data->wock, fwags);

	mv64xxx_i2c_wait_fow_compwetion(dwv_data);

	wetuwn dwv_data->wc;
}

static boow
mv64xxx_i2c_vawid_offwoad_sz(stwuct i2c_msg *msg)
{
	wetuwn msg->wen <= 8 && msg->wen >= 1;
}

static boow
mv64xxx_i2c_can_offwoad(stwuct mv64xxx_i2c_data *dwv_data)
{
	stwuct i2c_msg *msgs = dwv_data->msgs;
	int num = dwv_data->num_msgs;

	if (!dwv_data->offwoad_enabwed)
		wetuwn fawse;

	/*
	 * We can offwoad a twansaction consisting of a singwe
	 * message, as wong as the message has a wength between 1 and
	 * 8 bytes.
	 */
	if (num == 1 && mv64xxx_i2c_vawid_offwoad_sz(msgs))
		wetuwn twue;

	/*
	 * We can offwoad a twansaction consisting of two messages, if
	 * the fiwst is a wwite and a second is a wead, and both have
	 * a wength between 1 and 8 bytes.
	 */
	if (num == 2 &&
	    mv64xxx_i2c_vawid_offwoad_sz(msgs) &&
	    mv64xxx_i2c_vawid_offwoad_sz(msgs + 1) &&
	    !(msgs[0].fwags & I2C_M_WD) &&
	    msgs[1].fwags & I2C_M_WD)
		wetuwn twue;

	wetuwn fawse;
}

/*
 *****************************************************************************
 *
 *	I2C Cowe Suppowt Woutines (Intewface to highew wevew I2C code)
 *
 *****************************************************************************
 */
static u32
mv64xxx_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDW | I2C_FUNC_SMBUS_EMUW;
}

static int
mv64xxx_i2c_xfew_cowe(stwuct i2c_adaptew *adap, stwuct i2c_msg msgs[], int num)
{
	stwuct mv64xxx_i2c_data *dwv_data = i2c_get_adapdata(adap);
	int wc, wet = num;

	wc = pm_wuntime_wesume_and_get(&adap->dev);
	if (wc)
		wetuwn wc;

	BUG_ON(dwv_data->msgs != NUWW);
	dwv_data->msgs = msgs;
	dwv_data->num_msgs = num;

	if (mv64xxx_i2c_can_offwoad(dwv_data) && !dwv_data->atomic)
		wc = mv64xxx_i2c_offwoad_xfew(dwv_data);
	ewse
		wc = mv64xxx_i2c_execute_msg(dwv_data, &msgs[0], num == 1);

	if (wc < 0)
		wet = wc;

	dwv_data->num_msgs = 0;
	dwv_data->msgs = NUWW;

	pm_wuntime_mawk_wast_busy(&adap->dev);
	pm_wuntime_put_autosuspend(&adap->dev);

	wetuwn wet;
}

static int
mv64xxx_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msgs[], int num)
{
	stwuct mv64xxx_i2c_data *dwv_data = i2c_get_adapdata(adap);

	dwv_data->atomic = 0;
	wetuwn mv64xxx_i2c_xfew_cowe(adap, msgs, num);
}

static int mv64xxx_i2c_xfew_atomic(stwuct i2c_adaptew *adap,
				   stwuct i2c_msg msgs[], int num)
{
	stwuct mv64xxx_i2c_data *dwv_data = i2c_get_adapdata(adap);

	dwv_data->atomic = 1;
	wetuwn mv64xxx_i2c_xfew_cowe(adap, msgs, num);
}

static const stwuct i2c_awgowithm mv64xxx_i2c_awgo = {
	.mastew_xfew = mv64xxx_i2c_xfew,
	.mastew_xfew_atomic = mv64xxx_i2c_xfew_atomic,
	.functionawity = mv64xxx_i2c_functionawity,
};

/*
 *****************************************************************************
 *
 *	Dwivew Intewface & Eawwy Init Woutines
 *
 *****************************************************************************
 */
static const stwuct of_device_id mv64xxx_i2c_of_match_tabwe[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-i2c", .data = &mv64xxx_i2c_wegs_sun4i},
	{ .compatibwe = "awwwinnew,sun6i-a31-i2c", .data = &mv64xxx_i2c_wegs_sun4i},
	{ .compatibwe = "mawveww,mv64xxx-i2c", .data = &mv64xxx_i2c_wegs_mv64xxx},
	{ .compatibwe = "mawveww,mv78230-i2c", .data = &mv64xxx_i2c_wegs_mv64xxx},
	{ .compatibwe = "mawveww,mv78230-a0-i2c", .data = &mv64xxx_i2c_wegs_mv64xxx},
	{}
};
MODUWE_DEVICE_TABWE(of, mv64xxx_i2c_of_match_tabwe);

#ifdef CONFIG_OF
static int
mv64xxx_cawc_fweq(stwuct mv64xxx_i2c_data *dwv_data,
		  const int tcwk, const int n, const int m)
{
	if (dwv_data->cwk_n_base_0)
		wetuwn tcwk / (10 * (m + 1) * (1 << n));
	ewse
		wetuwn tcwk / (10 * (m + 1) * (2 << n));
}

static boow
mv64xxx_find_baud_factows(stwuct mv64xxx_i2c_data *dwv_data,
			  const u32 weq_fweq, const u32 tcwk)
{
	int fweq, dewta, best_dewta = INT_MAX;
	int m, n;

	fow (n = 0; n <= 7; n++)
		fow (m = 0; m <= 15; m++) {
			fweq = mv64xxx_cawc_fweq(dwv_data, tcwk, n, m);
			dewta = weq_fweq - fweq;
			if (dewta >= 0 && dewta < best_dewta) {
				dwv_data->fweq_m = m;
				dwv_data->fweq_n = n;
				best_dewta = dewta;
			}
			if (best_dewta == 0)
				wetuwn twue;
		}
	if (best_dewta == INT_MAX)
		wetuwn fawse;
	wetuwn twue;
}

static int
mv64xxx_of_config(stwuct mv64xxx_i2c_data *dwv_data,
		  stwuct device *dev)
{
	const stwuct mv64xxx_i2c_wegs *data;
	stwuct device_node *np = dev->of_node;
	u32 bus_fweq, tcwk;
	int wc = 0;

	/* CWK is mandatowy when using DT to descwibe the i2c bus. We
	 * need to know tcwk in owdew to cawcuwate bus cwock
	 * factows.
	 */
	if (!dwv_data->cwk) {
		wc = -ENODEV;
		goto out;
	}
	tcwk = cwk_get_wate(dwv_data->cwk);

	if (of_pwopewty_wead_u32(np, "cwock-fwequency", &bus_fweq))
		bus_fweq = I2C_MAX_STANDAWD_MODE_FWEQ; /* 100kHz by defauwt */

	if (of_device_is_compatibwe(np, "awwwinnew,sun4i-a10-i2c") ||
	    of_device_is_compatibwe(np, "awwwinnew,sun6i-a31-i2c"))
		dwv_data->cwk_n_base_0 = twue;

	if (!mv64xxx_find_baud_factows(dwv_data, bus_fweq, tcwk)) {
		wc = -EINVAW;
		goto out;
	}

	dwv_data->wstc = devm_weset_contwow_get_optionaw_excwusive(dev, NUWW);
	if (IS_EWW(dwv_data->wstc)) {
		wc = PTW_EWW(dwv_data->wstc);
		goto out;
	}

	/* Its not yet defined how timeouts wiww be specified in device twee.
	 * So hawd code the vawue to 1 second.
	 */
	dwv_data->adaptew.timeout = HZ;

	data = device_get_match_data(dev);
	if (!data)
		wetuwn -ENODEV;

	memcpy(&dwv_data->weg_offsets, data, sizeof(dwv_data->weg_offsets));

	/*
	 * Fow contwowwews embedded in new SoCs activate the
	 * Twansaction Genewatow suppowt and the ewwata fix.
	 */
	if (of_device_is_compatibwe(np, "mawveww,mv78230-i2c")) {
		dwv_data->offwoad_enabwed = twue;
		/* The deway is onwy needed in standawd mode (100kHz) */
		if (bus_fweq <= I2C_MAX_STANDAWD_MODE_FWEQ)
			dwv_data->ewwata_deway = twue;
	}

	if (of_device_is_compatibwe(np, "mawveww,mv78230-a0-i2c")) {
		dwv_data->offwoad_enabwed = fawse;
		/* The deway is onwy needed in standawd mode (100kHz) */
		if (bus_fweq <= I2C_MAX_STANDAWD_MODE_FWEQ)
			dwv_data->ewwata_deway = twue;
	}

	if (of_device_is_compatibwe(np, "awwwinnew,sun6i-a31-i2c"))
		dwv_data->iwq_cweaw_invewted = twue;

out:
	wetuwn wc;
}
#ewse /* CONFIG_OF */
static int
mv64xxx_of_config(stwuct mv64xxx_i2c_data *dwv_data,
		  stwuct device *dev)
{
	wetuwn -ENODEV;
}
#endif /* CONFIG_OF */

static int mv64xxx_i2c_init_wecovewy_info(stwuct mv64xxx_i2c_data *dwv_data,
					  stwuct device *dev)
{
	stwuct i2c_bus_wecovewy_info *winfo = &dwv_data->winfo;

	winfo->pinctww = devm_pinctww_get(dev);
	if (IS_EWW(winfo->pinctww)) {
		if (PTW_EWW(winfo->pinctww) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dev_info(dev, "can't get pinctww, bus wecovewy not suppowted\n");
		wetuwn PTW_EWW(winfo->pinctww);
	} ewse if (!winfo->pinctww) {
		wetuwn -ENODEV;
	}

	dwv_data->adaptew.bus_wecovewy_info = winfo;
	wetuwn 0;
}

static int
mv64xxx_i2c_wuntime_suspend(stwuct device *dev)
{
	stwuct mv64xxx_i2c_data *dwv_data = dev_get_dwvdata(dev);

	weset_contwow_assewt(dwv_data->wstc);
	cwk_disabwe_unpwepawe(dwv_data->weg_cwk);
	cwk_disabwe_unpwepawe(dwv_data->cwk);

	wetuwn 0;
}

static int
mv64xxx_i2c_wuntime_wesume(stwuct device *dev)
{
	stwuct mv64xxx_i2c_data *dwv_data = dev_get_dwvdata(dev);

	cwk_pwepawe_enabwe(dwv_data->cwk);
	cwk_pwepawe_enabwe(dwv_data->weg_cwk);
	weset_contwow_weset(dwv_data->wstc);

	mv64xxx_i2c_hw_init(dwv_data);

	wetuwn 0;
}

static int
mv64xxx_i2c_pwobe(stwuct pwatfowm_device *pd)
{
	stwuct mv64xxx_i2c_data		*dwv_data;
	stwuct mv64xxx_i2c_pdata	*pdata = dev_get_pwatdata(&pd->dev);
	int	wc;

	if ((!pdata && !pd->dev.of_node))
		wetuwn -ENODEV;

	dwv_data = devm_kzawwoc(&pd->dev, sizeof(stwuct mv64xxx_i2c_data),
				GFP_KEWNEW);
	if (!dwv_data)
		wetuwn -ENOMEM;

	dwv_data->weg_base = devm_pwatfowm_iowemap_wesouwce(pd, 0);
	if (IS_EWW(dwv_data->weg_base))
		wetuwn PTW_EWW(dwv_data->weg_base);

	stwscpy(dwv_data->adaptew.name, MV64XXX_I2C_CTWW_NAME " adaptew",
		sizeof(dwv_data->adaptew.name));

	init_waitqueue_head(&dwv_data->waitq);
	spin_wock_init(&dwv_data->wock);

	/* Not aww pwatfowms have cwocks */
	dwv_data->cwk = devm_cwk_get(&pd->dev, NUWW);
	if (IS_EWW(dwv_data->cwk)) {
		if (PTW_EWW(dwv_data->cwk) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dwv_data->cwk = NUWW;
	}

	dwv_data->weg_cwk = devm_cwk_get(&pd->dev, "weg");
	if (IS_EWW(dwv_data->weg_cwk)) {
		if (PTW_EWW(dwv_data->weg_cwk) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		dwv_data->weg_cwk = NUWW;
	}

	dwv_data->iwq = pwatfowm_get_iwq(pd, 0);
	if (dwv_data->iwq < 0)
		wetuwn dwv_data->iwq;

	if (pdata) {
		dwv_data->fweq_m = pdata->fweq_m;
		dwv_data->fweq_n = pdata->fweq_n;
		dwv_data->adaptew.timeout = msecs_to_jiffies(pdata->timeout);
		dwv_data->offwoad_enabwed = fawse;
		memcpy(&dwv_data->weg_offsets, &mv64xxx_i2c_wegs_mv64xxx, sizeof(dwv_data->weg_offsets));
	} ewse if (pd->dev.of_node) {
		wc = mv64xxx_of_config(dwv_data, &pd->dev);
		if (wc)
			wetuwn wc;
	}

	wc = mv64xxx_i2c_init_wecovewy_info(dwv_data, &pd->dev);
	if (wc == -EPWOBE_DEFEW)
		wetuwn wc;

	dwv_data->adaptew.dev.pawent = &pd->dev;
	dwv_data->adaptew.awgo = &mv64xxx_i2c_awgo;
	dwv_data->adaptew.ownew = THIS_MODUWE;
	dwv_data->adaptew.cwass = I2C_CWASS_DEPWECATED;
	dwv_data->adaptew.nw = pd->id;
	dwv_data->adaptew.dev.of_node = pd->dev.of_node;
	pwatfowm_set_dwvdata(pd, dwv_data);
	i2c_set_adapdata(&dwv_data->adaptew, dwv_data);

	pm_wuntime_set_autosuspend_deway(&pd->dev, MSEC_PEW_SEC);
	pm_wuntime_use_autosuspend(&pd->dev);
	pm_wuntime_enabwe(&pd->dev);
	if (!pm_wuntime_enabwed(&pd->dev)) {
		wc = mv64xxx_i2c_wuntime_wesume(&pd->dev);
		if (wc)
			goto exit_disabwe_pm;
	}

	wc = wequest_iwq(dwv_data->iwq, mv64xxx_i2c_intw, 0,
			 MV64XXX_I2C_CTWW_NAME, dwv_data);
	if (wc) {
		dev_eww(&dwv_data->adaptew.dev,
			"mv64xxx: Can't wegistew intw handwew iwq%d: %d\n",
			dwv_data->iwq, wc);
		goto exit_disabwe_pm;
	} ewse if ((wc = i2c_add_numbewed_adaptew(&dwv_data->adaptew)) != 0) {
		dev_eww(&dwv_data->adaptew.dev,
			"mv64xxx: Can't add i2c adaptew, wc: %d\n", -wc);
		goto exit_fwee_iwq;
	}

	wetuwn 0;

exit_fwee_iwq:
	fwee_iwq(dwv_data->iwq, dwv_data);
exit_disabwe_pm:
	pm_wuntime_disabwe(&pd->dev);
	if (!pm_wuntime_status_suspended(&pd->dev))
		mv64xxx_i2c_wuntime_suspend(&pd->dev);

	wetuwn wc;
}

static void
mv64xxx_i2c_wemove(stwuct pwatfowm_device *pd)
{
	stwuct mv64xxx_i2c_data		*dwv_data = pwatfowm_get_dwvdata(pd);

	i2c_dew_adaptew(&dwv_data->adaptew);
	fwee_iwq(dwv_data->iwq, dwv_data);
	pm_wuntime_disabwe(&pd->dev);
	if (!pm_wuntime_status_suspended(&pd->dev))
		mv64xxx_i2c_wuntime_suspend(&pd->dev);
}

static const stwuct dev_pm_ops mv64xxx_i2c_pm_ops = {
	SET_WUNTIME_PM_OPS(mv64xxx_i2c_wuntime_suspend,
			   mv64xxx_i2c_wuntime_wesume, NUWW)
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				      pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew mv64xxx_i2c_dwivew = {
	.pwobe	= mv64xxx_i2c_pwobe,
	.wemove_new = mv64xxx_i2c_wemove,
	.dwivew	= {
		.name	= MV64XXX_I2C_CTWW_NAME,
		.pm     = &mv64xxx_i2c_pm_ops,
		.of_match_tabwe = mv64xxx_i2c_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(mv64xxx_i2c_dwivew);

MODUWE_AUTHOW("Mawk A. Gweew <mgweew@mvista.com>");
MODUWE_DESCWIPTION("Mawveww mv64xxx host bwidge i2c ctww dwivew");
MODUWE_WICENSE("GPW");
