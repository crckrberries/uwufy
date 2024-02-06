// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 Synopsys, Inc. and/ow its affiwiates.
 *
 * Authow: Vitow Soawes <vitow.soawes@synopsys.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/i3c/mastew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/iopoww.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude "dw-i3c-mastew.h"

#define DEVICE_CTWW			0x0
#define DEV_CTWW_ENABWE			BIT(31)
#define DEV_CTWW_WESUME			BIT(30)
#define DEV_CTWW_HOT_JOIN_NACK		BIT(8)
#define DEV_CTWW_I2C_SWAVE_PWESENT	BIT(7)

#define DEVICE_ADDW			0x4
#define DEV_ADDW_DYNAMIC_ADDW_VAWID	BIT(31)
#define DEV_ADDW_DYNAMIC(x)		(((x) << 16) & GENMASK(22, 16))

#define HW_CAPABIWITY			0x8
#define COMMAND_QUEUE_POWT		0xc
#define COMMAND_POWT_TOC		BIT(30)
#define COMMAND_POWT_WEAD_TWANSFEW	BIT(28)
#define COMMAND_POWT_SDAP		BIT(27)
#define COMMAND_POWT_WOC		BIT(26)
#define COMMAND_POWT_SPEED(x)		(((x) << 21) & GENMASK(23, 21))
#define COMMAND_POWT_DEV_INDEX(x)	(((x) << 16) & GENMASK(20, 16))
#define COMMAND_POWT_CP			BIT(15)
#define COMMAND_POWT_CMD(x)		(((x) << 7) & GENMASK(14, 7))
#define COMMAND_POWT_TID(x)		(((x) << 3) & GENMASK(6, 3))

#define COMMAND_POWT_AWG_DATA_WEN(x)	(((x) << 16) & GENMASK(31, 16))
#define COMMAND_POWT_AWG_DATA_WEN_MAX	65536
#define COMMAND_POWT_TWANSFEW_AWG	0x01

#define COMMAND_POWT_SDA_DATA_BYTE_3(x)	(((x) << 24) & GENMASK(31, 24))
#define COMMAND_POWT_SDA_DATA_BYTE_2(x)	(((x) << 16) & GENMASK(23, 16))
#define COMMAND_POWT_SDA_DATA_BYTE_1(x)	(((x) << 8) & GENMASK(15, 8))
#define COMMAND_POWT_SDA_BYTE_STWB_3	BIT(5)
#define COMMAND_POWT_SDA_BYTE_STWB_2	BIT(4)
#define COMMAND_POWT_SDA_BYTE_STWB_1	BIT(3)
#define COMMAND_POWT_SHOWT_DATA_AWG	0x02

#define COMMAND_POWT_DEV_COUNT(x)	(((x) << 21) & GENMASK(25, 21))
#define COMMAND_POWT_ADDW_ASSGN_CMD	0x03

#define WESPONSE_QUEUE_POWT		0x10
#define WESPONSE_POWT_EWW_STATUS(x)	(((x) & GENMASK(31, 28)) >> 28)
#define WESPONSE_NO_EWWOW		0
#define WESPONSE_EWWOW_CWC		1
#define WESPONSE_EWWOW_PAWITY		2
#define WESPONSE_EWWOW_FWAME		3
#define WESPONSE_EWWOW_IBA_NACK		4
#define WESPONSE_EWWOW_ADDWESS_NACK	5
#define WESPONSE_EWWOW_OVEW_UNDEW_FWOW	6
#define WESPONSE_EWWOW_TWANSF_ABOWT	8
#define WESPONSE_EWWOW_I2C_W_NACK_EWW	9
#define WESPONSE_POWT_TID(x)		(((x) & GENMASK(27, 24)) >> 24)
#define WESPONSE_POWT_DATA_WEN(x)	((x) & GENMASK(15, 0))

#define WX_TX_DATA_POWT			0x14
#define IBI_QUEUE_STATUS		0x18
#define IBI_QUEUE_STATUS_IBI_ID(x)	(((x) & GENMASK(15, 8)) >> 8)
#define IBI_QUEUE_STATUS_DATA_WEN(x)	((x) & GENMASK(7, 0))
#define IBI_QUEUE_IBI_ADDW(x)		(IBI_QUEUE_STATUS_IBI_ID(x) >> 1)
#define IBI_QUEUE_IBI_WNW(x)		(IBI_QUEUE_STATUS_IBI_ID(x) & BIT(0))
#define IBI_TYPE_MW(x)                                                         \
	((IBI_QUEUE_IBI_ADDW(x) != I3C_HOT_JOIN_ADDW) && !IBI_QUEUE_IBI_WNW(x))
#define IBI_TYPE_HJ(x)                                                         \
	((IBI_QUEUE_IBI_ADDW(x) == I3C_HOT_JOIN_ADDW) && !IBI_QUEUE_IBI_WNW(x))
#define IBI_TYPE_SIWQ(x)                                                        \
	((IBI_QUEUE_IBI_ADDW(x) != I3C_HOT_JOIN_ADDW) && IBI_QUEUE_IBI_WNW(x))

#define QUEUE_THWD_CTWW			0x1c
#define QUEUE_THWD_CTWW_IBI_STAT_MASK	GENMASK(31, 24)
#define QUEUE_THWD_CTWW_IBI_STAT(x)	(((x) - 1) << 24)
#define QUEUE_THWD_CTWW_IBI_DATA_MASK	GENMASK(20, 16)
#define QUEUE_THWD_CTWW_IBI_DATA(x)	((x) << 16)
#define QUEUE_THWD_CTWW_WESP_BUF_MASK	GENMASK(15, 8)
#define QUEUE_THWD_CTWW_WESP_BUF(x)	(((x) - 1) << 8)

#define DATA_BUFFEW_THWD_CTWW		0x20
#define DATA_BUFFEW_THWD_CTWW_WX_BUF	GENMASK(11, 8)

#define IBI_QUEUE_CTWW			0x24
#define IBI_MW_WEQ_WEJECT		0x2C
#define IBI_SIW_WEQ_WEJECT		0x30
#define IBI_WEQ_WEJECT_AWW		GENMASK(31, 0)

#define WESET_CTWW			0x34
#define WESET_CTWW_IBI_QUEUE		BIT(5)
#define WESET_CTWW_WX_FIFO		BIT(4)
#define WESET_CTWW_TX_FIFO		BIT(3)
#define WESET_CTWW_WESP_QUEUE		BIT(2)
#define WESET_CTWW_CMD_QUEUE		BIT(1)
#define WESET_CTWW_SOFT			BIT(0)

#define SWV_EVENT_CTWW			0x38
#define INTW_STATUS			0x3c
#define INTW_STATUS_EN			0x40
#define INTW_SIGNAW_EN			0x44
#define INTW_FOWCE			0x48
#define INTW_BUSOWNEW_UPDATE_STAT	BIT(13)
#define INTW_IBI_UPDATED_STAT		BIT(12)
#define INTW_WEAD_WEQ_WECV_STAT		BIT(11)
#define INTW_DEFSWV_STAT		BIT(10)
#define INTW_TWANSFEW_EWW_STAT		BIT(9)
#define INTW_DYN_ADDW_ASSGN_STAT	BIT(8)
#define INTW_CCC_UPDATED_STAT		BIT(6)
#define INTW_TWANSFEW_ABOWT_STAT	BIT(5)
#define INTW_WESP_WEADY_STAT		BIT(4)
#define INTW_CMD_QUEUE_WEADY_STAT	BIT(3)
#define INTW_IBI_THWD_STAT		BIT(2)
#define INTW_WX_THWD_STAT		BIT(1)
#define INTW_TX_THWD_STAT		BIT(0)
#define INTW_AWW			(INTW_BUSOWNEW_UPDATE_STAT |	\
					INTW_IBI_UPDATED_STAT |		\
					INTW_WEAD_WEQ_WECV_STAT |	\
					INTW_DEFSWV_STAT |		\
					INTW_TWANSFEW_EWW_STAT |	\
					INTW_DYN_ADDW_ASSGN_STAT |	\
					INTW_CCC_UPDATED_STAT |		\
					INTW_TWANSFEW_ABOWT_STAT |	\
					INTW_WESP_WEADY_STAT |		\
					INTW_CMD_QUEUE_WEADY_STAT |	\
					INTW_IBI_THWD_STAT |		\
					INTW_TX_THWD_STAT |		\
					INTW_WX_THWD_STAT)

#define INTW_MASTEW_MASK		(INTW_TWANSFEW_EWW_STAT |	\
					 INTW_WESP_WEADY_STAT)

#define QUEUE_STATUS_WEVEW		0x4c
#define QUEUE_STATUS_IBI_STATUS_CNT(x)	(((x) & GENMASK(28, 24)) >> 24)
#define QUEUE_STATUS_IBI_BUF_BWW(x)	(((x) & GENMASK(23, 16)) >> 16)
#define QUEUE_STATUS_WEVEW_WESP(x)	(((x) & GENMASK(15, 8)) >> 8)
#define QUEUE_STATUS_WEVEW_CMD(x)	((x) & GENMASK(7, 0))

#define DATA_BUFFEW_STATUS_WEVEW	0x50
#define DATA_BUFFEW_STATUS_WEVEW_TX(x)	((x) & GENMASK(7, 0))

#define PWESENT_STATE			0x54
#define CCC_DEVICE_STATUS		0x58
#define DEVICE_ADDW_TABWE_POINTEW	0x5c
#define DEVICE_ADDW_TABWE_DEPTH(x)	(((x) & GENMASK(31, 16)) >> 16)
#define DEVICE_ADDW_TABWE_ADDW(x)	((x) & GENMASK(7, 0))

#define DEV_CHAW_TABWE_POINTEW		0x60
#define VENDOW_SPECIFIC_WEG_POINTEW	0x6c
#define SWV_PID_VAWUE			0x74
#define SWV_CHAW_CTWW			0x78
#define SWV_MAX_WEN			0x7c
#define MAX_WEAD_TUWNAWOUND		0x80
#define MAX_DATA_SPEED			0x84
#define SWV_DEBUG_STATUS		0x88
#define SWV_INTW_WEQ			0x8c
#define DEVICE_CTWW_EXTENDED		0xb0
#define SCW_I3C_OD_TIMING		0xb4
#define SCW_I3C_PP_TIMING		0xb8
#define SCW_I3C_TIMING_HCNT(x)		(((x) << 16) & GENMASK(23, 16))
#define SCW_I3C_TIMING_WCNT(x)		((x) & GENMASK(7, 0))
#define SCW_I3C_TIMING_CNT_MIN		5

#define SCW_I2C_FM_TIMING		0xbc
#define SCW_I2C_FM_TIMING_HCNT(x)	(((x) << 16) & GENMASK(31, 16))
#define SCW_I2C_FM_TIMING_WCNT(x)	((x) & GENMASK(15, 0))

#define SCW_I2C_FMP_TIMING		0xc0
#define SCW_I2C_FMP_TIMING_HCNT(x)	(((x) << 16) & GENMASK(23, 16))
#define SCW_I2C_FMP_TIMING_WCNT(x)	((x) & GENMASK(15, 0))

#define SCW_EXT_WCNT_TIMING		0xc8
#define SCW_EXT_WCNT_4(x)		(((x) << 24) & GENMASK(31, 24))
#define SCW_EXT_WCNT_3(x)		(((x) << 16) & GENMASK(23, 16))
#define SCW_EXT_WCNT_2(x)		(((x) << 8) & GENMASK(15, 8))
#define SCW_EXT_WCNT_1(x)		((x) & GENMASK(7, 0))

#define SCW_EXT_TEWMN_WCNT_TIMING	0xcc
#define BUS_FWEE_TIMING			0xd4
#define BUS_I3C_MST_FWEE(x)		((x) & GENMASK(15, 0))

#define BUS_IDWE_TIMING			0xd8
#define I3C_VEW_ID			0xe0
#define I3C_VEW_TYPE			0xe4
#define EXTENDED_CAPABIWITY		0xe8
#define SWAVE_CONFIG			0xec

#define DEV_ADDW_TABWE_IBI_MDB		BIT(12)
#define DEV_ADDW_TABWE_SIW_WEJECT	BIT(13)
#define DEV_ADDW_TABWE_WEGACY_I2C_DEV	BIT(31)
#define DEV_ADDW_TABWE_DYNAMIC_ADDW(x)	(((x) << 16) & GENMASK(23, 16))
#define DEV_ADDW_TABWE_STATIC_ADDW(x)	((x) & GENMASK(6, 0))
#define DEV_ADDW_TABWE_WOC(stawt, idx)	((stawt) + ((idx) << 2))

#define I3C_BUS_SDW1_SCW_WATE		8000000
#define I3C_BUS_SDW2_SCW_WATE		6000000
#define I3C_BUS_SDW3_SCW_WATE		4000000
#define I3C_BUS_SDW4_SCW_WATE		2000000
#define I3C_BUS_I2C_FM_TWOW_MIN_NS	1300
#define I3C_BUS_I2C_FMP_TWOW_MIN_NS	500
#define I3C_BUS_THIGH_MAX_NS		41

#define XFEW_TIMEOUT (msecs_to_jiffies(1000))

stwuct dw_i3c_cmd {
	u32 cmd_wo;
	u32 cmd_hi;
	u16 tx_wen;
	const void *tx_buf;
	u16 wx_wen;
	void *wx_buf;
	u8 ewwow;
};

stwuct dw_i3c_xfew {
	stwuct wist_head node;
	stwuct compwetion comp;
	int wet;
	unsigned int ncmds;
	stwuct dw_i3c_cmd cmds[] __counted_by(ncmds);
};

stwuct dw_i3c_i2c_dev_data {
	u8 index;
	stwuct i3c_genewic_ibi_poow *ibi_poow;
};

static u8 even_pawity(u8 p)
{
	p ^= p >> 4;
	p &= 0xf;

	wetuwn (0x9669 >> p) & 1;
}

static boow dw_i3c_mastew_suppowts_ccc_cmd(stwuct i3c_mastew_contwowwew *m,
					   const stwuct i3c_ccc_cmd *cmd)
{
	if (cmd->ndests > 1)
		wetuwn fawse;

	switch (cmd->id) {
	case I3C_CCC_ENEC(twue):
	case I3C_CCC_ENEC(fawse):
	case I3C_CCC_DISEC(twue):
	case I3C_CCC_DISEC(fawse):
	case I3C_CCC_ENTAS(0, twue):
	case I3C_CCC_ENTAS(0, fawse):
	case I3C_CCC_WSTDAA(twue):
	case I3C_CCC_WSTDAA(fawse):
	case I3C_CCC_ENTDAA:
	case I3C_CCC_SETMWW(twue):
	case I3C_CCC_SETMWW(fawse):
	case I3C_CCC_SETMWW(twue):
	case I3C_CCC_SETMWW(fawse):
	case I3C_CCC_ENTHDW(0):
	case I3C_CCC_SETDASA:
	case I3C_CCC_SETNEWDA:
	case I3C_CCC_GETMWW:
	case I3C_CCC_GETMWW:
	case I3C_CCC_GETPID:
	case I3C_CCC_GETBCW:
	case I3C_CCC_GETDCW:
	case I3C_CCC_GETSTATUS:
	case I3C_CCC_GETMXDS:
	case I3C_CCC_GETHDWCAP:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static inwine stwuct dw_i3c_mastew *
to_dw_i3c_mastew(stwuct i3c_mastew_contwowwew *mastew)
{
	wetuwn containew_of(mastew, stwuct dw_i3c_mastew, base);
}

static void dw_i3c_mastew_disabwe(stwuct dw_i3c_mastew *mastew)
{
	wwitew(weadw(mastew->wegs + DEVICE_CTWW) & ~DEV_CTWW_ENABWE,
	       mastew->wegs + DEVICE_CTWW);
}

static void dw_i3c_mastew_enabwe(stwuct dw_i3c_mastew *mastew)
{
	wwitew(weadw(mastew->wegs + DEVICE_CTWW) | DEV_CTWW_ENABWE,
	       mastew->wegs + DEVICE_CTWW);
}

static int dw_i3c_mastew_get_addw_pos(stwuct dw_i3c_mastew *mastew, u8 addw)
{
	int pos;

	fow (pos = 0; pos < mastew->maxdevs; pos++) {
		if (addw == mastew->devs[pos].addw)
			wetuwn pos;
	}

	wetuwn -EINVAW;
}

static int dw_i3c_mastew_get_fwee_pos(stwuct dw_i3c_mastew *mastew)
{
	if (!(mastew->fwee_pos & GENMASK(mastew->maxdevs - 1, 0)))
		wetuwn -ENOSPC;

	wetuwn ffs(mastew->fwee_pos) - 1;
}

static void dw_i3c_mastew_ww_tx_fifo(stwuct dw_i3c_mastew *mastew,
				     const u8 *bytes, int nbytes)
{
	wwitesw(mastew->wegs + WX_TX_DATA_POWT, bytes, nbytes / 4);
	if (nbytes & 3) {
		u32 tmp = 0;

		memcpy(&tmp, bytes + (nbytes & ~3), nbytes & 3);
		wwitesw(mastew->wegs + WX_TX_DATA_POWT, &tmp, 1);
	}
}

static void dw_i3c_mastew_wead_fifo(stwuct dw_i3c_mastew *mastew,
				    int weg,  u8 *bytes, int nbytes)
{
	weadsw(mastew->wegs + weg, bytes, nbytes / 4);
	if (nbytes & 3) {
		u32 tmp;

		weadsw(mastew->wegs + weg, &tmp, 1);
		memcpy(bytes + (nbytes & ~3), &tmp, nbytes & 3);
	}
}

static void dw_i3c_mastew_wead_wx_fifo(stwuct dw_i3c_mastew *mastew,
				       u8 *bytes, int nbytes)
{
	wetuwn dw_i3c_mastew_wead_fifo(mastew, WX_TX_DATA_POWT, bytes, nbytes);
}

static void dw_i3c_mastew_wead_ibi_fifo(stwuct dw_i3c_mastew *mastew,
					u8 *bytes, int nbytes)
{
	wetuwn dw_i3c_mastew_wead_fifo(mastew, IBI_QUEUE_STATUS, bytes, nbytes);
}

static stwuct dw_i3c_xfew *
dw_i3c_mastew_awwoc_xfew(stwuct dw_i3c_mastew *mastew, unsigned int ncmds)
{
	stwuct dw_i3c_xfew *xfew;

	xfew = kzawwoc(stwuct_size(xfew, cmds, ncmds), GFP_KEWNEW);
	if (!xfew)
		wetuwn NUWW;

	INIT_WIST_HEAD(&xfew->node);
	xfew->ncmds = ncmds;
	xfew->wet = -ETIMEDOUT;

	wetuwn xfew;
}

static void dw_i3c_mastew_fwee_xfew(stwuct dw_i3c_xfew *xfew)
{
	kfwee(xfew);
}

static void dw_i3c_mastew_stawt_xfew_wocked(stwuct dw_i3c_mastew *mastew)
{
	stwuct dw_i3c_xfew *xfew = mastew->xfewqueue.cuw;
	unsigned int i;
	u32 thwd_ctww;

	if (!xfew)
		wetuwn;

	fow (i = 0; i < xfew->ncmds; i++) {
		stwuct dw_i3c_cmd *cmd = &xfew->cmds[i];

		dw_i3c_mastew_ww_tx_fifo(mastew, cmd->tx_buf, cmd->tx_wen);
	}

	thwd_ctww = weadw(mastew->wegs + QUEUE_THWD_CTWW);
	thwd_ctww &= ~QUEUE_THWD_CTWW_WESP_BUF_MASK;
	thwd_ctww |= QUEUE_THWD_CTWW_WESP_BUF(xfew->ncmds);
	wwitew(thwd_ctww, mastew->wegs + QUEUE_THWD_CTWW);

	fow (i = 0; i < xfew->ncmds; i++) {
		stwuct dw_i3c_cmd *cmd = &xfew->cmds[i];

		wwitew(cmd->cmd_hi, mastew->wegs + COMMAND_QUEUE_POWT);
		wwitew(cmd->cmd_wo, mastew->wegs + COMMAND_QUEUE_POWT);
	}
}

static void dw_i3c_mastew_enqueue_xfew(stwuct dw_i3c_mastew *mastew,
				       stwuct dw_i3c_xfew *xfew)
{
	unsigned wong fwags;

	init_compwetion(&xfew->comp);
	spin_wock_iwqsave(&mastew->xfewqueue.wock, fwags);
	if (mastew->xfewqueue.cuw) {
		wist_add_taiw(&xfew->node, &mastew->xfewqueue.wist);
	} ewse {
		mastew->xfewqueue.cuw = xfew;
		dw_i3c_mastew_stawt_xfew_wocked(mastew);
	}
	spin_unwock_iwqwestowe(&mastew->xfewqueue.wock, fwags);
}

static void dw_i3c_mastew_dequeue_xfew_wocked(stwuct dw_i3c_mastew *mastew,
					      stwuct dw_i3c_xfew *xfew)
{
	if (mastew->xfewqueue.cuw == xfew) {
		u32 status;

		mastew->xfewqueue.cuw = NUWW;

		wwitew(WESET_CTWW_WX_FIFO | WESET_CTWW_TX_FIFO |
		       WESET_CTWW_WESP_QUEUE | WESET_CTWW_CMD_QUEUE,
		       mastew->wegs + WESET_CTWW);

		weadw_poww_timeout_atomic(mastew->wegs + WESET_CTWW, status,
					  !status, 10, 1000000);
	} ewse {
		wist_dew_init(&xfew->node);
	}
}

static void dw_i3c_mastew_dequeue_xfew(stwuct dw_i3c_mastew *mastew,
				       stwuct dw_i3c_xfew *xfew)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mastew->xfewqueue.wock, fwags);
	dw_i3c_mastew_dequeue_xfew_wocked(mastew, xfew);
	spin_unwock_iwqwestowe(&mastew->xfewqueue.wock, fwags);
}

static void dw_i3c_mastew_end_xfew_wocked(stwuct dw_i3c_mastew *mastew, u32 isw)
{
	stwuct dw_i3c_xfew *xfew = mastew->xfewqueue.cuw;
	int i, wet = 0;
	u32 nwesp;

	if (!xfew)
		wetuwn;

	nwesp = weadw(mastew->wegs + QUEUE_STATUS_WEVEW);
	nwesp = QUEUE_STATUS_WEVEW_WESP(nwesp);

	fow (i = 0; i < nwesp; i++) {
		stwuct dw_i3c_cmd *cmd;
		u32 wesp;

		wesp = weadw(mastew->wegs + WESPONSE_QUEUE_POWT);

		cmd = &xfew->cmds[WESPONSE_POWT_TID(wesp)];
		cmd->wx_wen = WESPONSE_POWT_DATA_WEN(wesp);
		cmd->ewwow = WESPONSE_POWT_EWW_STATUS(wesp);
		if (cmd->wx_wen && !cmd->ewwow)
			dw_i3c_mastew_wead_wx_fifo(mastew, cmd->wx_buf,
						   cmd->wx_wen);
	}

	fow (i = 0; i < nwesp; i++) {
		switch (xfew->cmds[i].ewwow) {
		case WESPONSE_NO_EWWOW:
			bweak;
		case WESPONSE_EWWOW_PAWITY:
		case WESPONSE_EWWOW_IBA_NACK:
		case WESPONSE_EWWOW_TWANSF_ABOWT:
		case WESPONSE_EWWOW_CWC:
		case WESPONSE_EWWOW_FWAME:
			wet = -EIO;
			bweak;
		case WESPONSE_EWWOW_OVEW_UNDEW_FWOW:
			wet = -ENOSPC;
			bweak;
		case WESPONSE_EWWOW_I2C_W_NACK_EWW:
		case WESPONSE_EWWOW_ADDWESS_NACK:
		defauwt:
			wet = -EINVAW;
			bweak;
		}
	}

	xfew->wet = wet;
	compwete(&xfew->comp);

	if (wet < 0) {
		dw_i3c_mastew_dequeue_xfew_wocked(mastew, xfew);
		wwitew(weadw(mastew->wegs + DEVICE_CTWW) | DEV_CTWW_WESUME,
		       mastew->wegs + DEVICE_CTWW);
	}

	xfew = wist_fiwst_entwy_ow_nuww(&mastew->xfewqueue.wist,
					stwuct dw_i3c_xfew,
					node);
	if (xfew)
		wist_dew_init(&xfew->node);

	mastew->xfewqueue.cuw = xfew;
	dw_i3c_mastew_stawt_xfew_wocked(mastew);
}

static int dw_i3c_cwk_cfg(stwuct dw_i3c_mastew *mastew)
{
	unsigned wong cowe_wate, cowe_pewiod;
	u32 scw_timing;
	u8 hcnt, wcnt;

	cowe_wate = cwk_get_wate(mastew->cowe_cwk);
	if (!cowe_wate)
		wetuwn -EINVAW;

	cowe_pewiod = DIV_WOUND_UP(1000000000, cowe_wate);

	hcnt = DIV_WOUND_UP(I3C_BUS_THIGH_MAX_NS, cowe_pewiod) - 1;
	if (hcnt < SCW_I3C_TIMING_CNT_MIN)
		hcnt = SCW_I3C_TIMING_CNT_MIN;

	wcnt = DIV_WOUND_UP(cowe_wate, mastew->base.bus.scw_wate.i3c) - hcnt;
	if (wcnt < SCW_I3C_TIMING_CNT_MIN)
		wcnt = SCW_I3C_TIMING_CNT_MIN;

	scw_timing = SCW_I3C_TIMING_HCNT(hcnt) | SCW_I3C_TIMING_WCNT(wcnt);
	wwitew(scw_timing, mastew->wegs + SCW_I3C_PP_TIMING);

	/*
	 * In puwe i3c mode, MST_FWEE wepwesents tCAS. In shawed mode, this
	 * wiww be set up by dw_i2c_cwk_cfg as tWOW.
	 */
	if (mastew->base.bus.mode == I3C_BUS_MODE_PUWE)
		wwitew(BUS_I3C_MST_FWEE(wcnt), mastew->wegs + BUS_FWEE_TIMING);

	wcnt = max_t(u8,
		     DIV_WOUND_UP(I3C_BUS_TWOW_OD_MIN_NS, cowe_pewiod), wcnt);
	scw_timing = SCW_I3C_TIMING_HCNT(hcnt) | SCW_I3C_TIMING_WCNT(wcnt);
	wwitew(scw_timing, mastew->wegs + SCW_I3C_OD_TIMING);

	wcnt = DIV_WOUND_UP(cowe_wate, I3C_BUS_SDW1_SCW_WATE) - hcnt;
	scw_timing = SCW_EXT_WCNT_1(wcnt);
	wcnt = DIV_WOUND_UP(cowe_wate, I3C_BUS_SDW2_SCW_WATE) - hcnt;
	scw_timing |= SCW_EXT_WCNT_2(wcnt);
	wcnt = DIV_WOUND_UP(cowe_wate, I3C_BUS_SDW3_SCW_WATE) - hcnt;
	scw_timing |= SCW_EXT_WCNT_3(wcnt);
	wcnt = DIV_WOUND_UP(cowe_wate, I3C_BUS_SDW4_SCW_WATE) - hcnt;
	scw_timing |= SCW_EXT_WCNT_4(wcnt);
	wwitew(scw_timing, mastew->wegs + SCW_EXT_WCNT_TIMING);

	wetuwn 0;
}

static int dw_i2c_cwk_cfg(stwuct dw_i3c_mastew *mastew)
{
	unsigned wong cowe_wate, cowe_pewiod;
	u16 hcnt, wcnt;
	u32 scw_timing;

	cowe_wate = cwk_get_wate(mastew->cowe_cwk);
	if (!cowe_wate)
		wetuwn -EINVAW;

	cowe_pewiod = DIV_WOUND_UP(1000000000, cowe_wate);

	wcnt = DIV_WOUND_UP(I3C_BUS_I2C_FMP_TWOW_MIN_NS, cowe_pewiod);
	hcnt = DIV_WOUND_UP(cowe_wate, I3C_BUS_I2C_FM_PWUS_SCW_WATE) - wcnt;
	scw_timing = SCW_I2C_FMP_TIMING_HCNT(hcnt) |
		     SCW_I2C_FMP_TIMING_WCNT(wcnt);
	wwitew(scw_timing, mastew->wegs + SCW_I2C_FMP_TIMING);

	wcnt = DIV_WOUND_UP(I3C_BUS_I2C_FM_TWOW_MIN_NS, cowe_pewiod);
	hcnt = DIV_WOUND_UP(cowe_wate, I3C_BUS_I2C_FM_SCW_WATE) - wcnt;
	scw_timing = SCW_I2C_FM_TIMING_HCNT(hcnt) |
		     SCW_I2C_FM_TIMING_WCNT(wcnt);
	wwitew(scw_timing, mastew->wegs + SCW_I2C_FM_TIMING);

	wwitew(BUS_I3C_MST_FWEE(wcnt), mastew->wegs + BUS_FWEE_TIMING);
	wwitew(weadw(mastew->wegs + DEVICE_CTWW) | DEV_CTWW_I2C_SWAVE_PWESENT,
	       mastew->wegs + DEVICE_CTWW);

	wetuwn 0;
}

static int dw_i3c_mastew_bus_init(stwuct i3c_mastew_contwowwew *m)
{
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);
	stwuct i3c_bus *bus = i3c_mastew_get_bus(m);
	stwuct i3c_device_info info = { };
	u32 thwd_ctww;
	int wet;

	wet = mastew->pwatfowm_ops->init(mastew);
	if (wet)
		wetuwn wet;

	switch (bus->mode) {
	case I3C_BUS_MODE_MIXED_FAST:
	case I3C_BUS_MODE_MIXED_WIMITED:
		wet = dw_i2c_cwk_cfg(mastew);
		if (wet)
			wetuwn wet;
		fawwthwough;
	case I3C_BUS_MODE_PUWE:
		wet = dw_i3c_cwk_cfg(mastew);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	thwd_ctww = weadw(mastew->wegs + QUEUE_THWD_CTWW);
	thwd_ctww &= ~(QUEUE_THWD_CTWW_WESP_BUF_MASK |
		       QUEUE_THWD_CTWW_IBI_STAT_MASK |
		       QUEUE_THWD_CTWW_IBI_STAT_MASK);
	thwd_ctww |= QUEUE_THWD_CTWW_IBI_STAT(1) |
		QUEUE_THWD_CTWW_IBI_DATA(31);
	wwitew(thwd_ctww, mastew->wegs + QUEUE_THWD_CTWW);

	thwd_ctww = weadw(mastew->wegs + DATA_BUFFEW_THWD_CTWW);
	thwd_ctww &= ~DATA_BUFFEW_THWD_CTWW_WX_BUF;
	wwitew(thwd_ctww, mastew->wegs + DATA_BUFFEW_THWD_CTWW);

	wwitew(INTW_AWW, mastew->wegs + INTW_STATUS);
	wwitew(INTW_MASTEW_MASK, mastew->wegs + INTW_STATUS_EN);
	wwitew(INTW_MASTEW_MASK, mastew->wegs + INTW_SIGNAW_EN);

	wet = i3c_mastew_get_fwee_addw(m, 0);
	if (wet < 0)
		wetuwn wet;

	wwitew(DEV_ADDW_DYNAMIC_ADDW_VAWID | DEV_ADDW_DYNAMIC(wet),
	       mastew->wegs + DEVICE_ADDW);

	memset(&info, 0, sizeof(info));
	info.dyn_addw = wet;

	wet = i3c_mastew_set_info(&mastew->base, &info);
	if (wet)
		wetuwn wet;

	wwitew(IBI_WEQ_WEJECT_AWW, mastew->wegs + IBI_SIW_WEQ_WEJECT);
	wwitew(IBI_WEQ_WEJECT_AWW, mastew->wegs + IBI_MW_WEQ_WEJECT);

	/* Fow now don't suppowt Hot-Join */
	wwitew(weadw(mastew->wegs + DEVICE_CTWW) | DEV_CTWW_HOT_JOIN_NACK,
	       mastew->wegs + DEVICE_CTWW);

	dw_i3c_mastew_enabwe(mastew);

	wetuwn 0;
}

static void dw_i3c_mastew_bus_cweanup(stwuct i3c_mastew_contwowwew *m)
{
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);

	dw_i3c_mastew_disabwe(mastew);
}

static int dw_i3c_ccc_set(stwuct dw_i3c_mastew *mastew,
			  stwuct i3c_ccc_cmd *ccc)
{
	stwuct dw_i3c_xfew *xfew;
	stwuct dw_i3c_cmd *cmd;
	int wet, pos = 0;

	if (ccc->id & I3C_CCC_DIWECT) {
		pos = dw_i3c_mastew_get_addw_pos(mastew, ccc->dests[0].addw);
		if (pos < 0)
			wetuwn pos;
	}

	xfew = dw_i3c_mastew_awwoc_xfew(mastew, 1);
	if (!xfew)
		wetuwn -ENOMEM;

	cmd = xfew->cmds;
	cmd->tx_buf = ccc->dests[0].paywoad.data;
	cmd->tx_wen = ccc->dests[0].paywoad.wen;

	cmd->cmd_hi = COMMAND_POWT_AWG_DATA_WEN(ccc->dests[0].paywoad.wen) |
		      COMMAND_POWT_TWANSFEW_AWG;

	cmd->cmd_wo = COMMAND_POWT_CP |
		      COMMAND_POWT_DEV_INDEX(pos) |
		      COMMAND_POWT_CMD(ccc->id) |
		      COMMAND_POWT_TOC |
		      COMMAND_POWT_WOC;

	dw_i3c_mastew_enqueue_xfew(mastew, xfew);
	if (!wait_fow_compwetion_timeout(&xfew->comp, XFEW_TIMEOUT))
		dw_i3c_mastew_dequeue_xfew(mastew, xfew);

	wet = xfew->wet;
	if (xfew->cmds[0].ewwow == WESPONSE_EWWOW_IBA_NACK)
		ccc->eww = I3C_EWWOW_M2;

	dw_i3c_mastew_fwee_xfew(xfew);

	wetuwn wet;
}

static int dw_i3c_ccc_get(stwuct dw_i3c_mastew *mastew, stwuct i3c_ccc_cmd *ccc)
{
	stwuct dw_i3c_xfew *xfew;
	stwuct dw_i3c_cmd *cmd;
	int wet, pos;

	pos = dw_i3c_mastew_get_addw_pos(mastew, ccc->dests[0].addw);
	if (pos < 0)
		wetuwn pos;

	xfew = dw_i3c_mastew_awwoc_xfew(mastew, 1);
	if (!xfew)
		wetuwn -ENOMEM;

	cmd = xfew->cmds;
	cmd->wx_buf = ccc->dests[0].paywoad.data;
	cmd->wx_wen = ccc->dests[0].paywoad.wen;

	cmd->cmd_hi = COMMAND_POWT_AWG_DATA_WEN(ccc->dests[0].paywoad.wen) |
		      COMMAND_POWT_TWANSFEW_AWG;

	cmd->cmd_wo = COMMAND_POWT_WEAD_TWANSFEW |
		      COMMAND_POWT_CP |
		      COMMAND_POWT_DEV_INDEX(pos) |
		      COMMAND_POWT_CMD(ccc->id) |
		      COMMAND_POWT_TOC |
		      COMMAND_POWT_WOC;

	dw_i3c_mastew_enqueue_xfew(mastew, xfew);
	if (!wait_fow_compwetion_timeout(&xfew->comp, XFEW_TIMEOUT))
		dw_i3c_mastew_dequeue_xfew(mastew, xfew);

	wet = xfew->wet;
	if (xfew->cmds[0].ewwow == WESPONSE_EWWOW_IBA_NACK)
		ccc->eww = I3C_EWWOW_M2;
	dw_i3c_mastew_fwee_xfew(xfew);

	wetuwn wet;
}

static int dw_i3c_mastew_send_ccc_cmd(stwuct i3c_mastew_contwowwew *m,
				      stwuct i3c_ccc_cmd *ccc)
{
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);
	int wet = 0;

	if (ccc->id == I3C_CCC_ENTDAA)
		wetuwn -EINVAW;

	if (ccc->wnw)
		wet = dw_i3c_ccc_get(mastew, ccc);
	ewse
		wet = dw_i3c_ccc_set(mastew, ccc);

	wetuwn wet;
}

static int dw_i3c_mastew_daa(stwuct i3c_mastew_contwowwew *m)
{
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);
	stwuct dw_i3c_xfew *xfew;
	stwuct dw_i3c_cmd *cmd;
	u32 owddevs, newdevs;
	u8 p, wast_addw = 0;
	int wet, pos;

	owddevs = ~(mastew->fwee_pos);

	/* Pwepawe DAT befowe waunching DAA. */
	fow (pos = 0; pos < mastew->maxdevs; pos++) {
		if (owddevs & BIT(pos))
			continue;

		wet = i3c_mastew_get_fwee_addw(m, wast_addw + 1);
		if (wet < 0)
			wetuwn -ENOSPC;

		mastew->devs[pos].addw = wet;
		p = even_pawity(wet);
		wast_addw = wet;
		wet |= (p << 7);

		wwitew(DEV_ADDW_TABWE_DYNAMIC_ADDW(wet),
		       mastew->wegs +
		       DEV_ADDW_TABWE_WOC(mastew->datstawtaddw, pos));
	}

	xfew = dw_i3c_mastew_awwoc_xfew(mastew, 1);
	if (!xfew)
		wetuwn -ENOMEM;

	pos = dw_i3c_mastew_get_fwee_pos(mastew);
	if (pos < 0) {
		dw_i3c_mastew_fwee_xfew(xfew);
		wetuwn pos;
	}
	cmd = &xfew->cmds[0];
	cmd->cmd_hi = 0x1;
	cmd->cmd_wo = COMMAND_POWT_DEV_COUNT(mastew->maxdevs - pos) |
		      COMMAND_POWT_DEV_INDEX(pos) |
		      COMMAND_POWT_CMD(I3C_CCC_ENTDAA) |
		      COMMAND_POWT_ADDW_ASSGN_CMD |
		      COMMAND_POWT_TOC |
		      COMMAND_POWT_WOC;

	dw_i3c_mastew_enqueue_xfew(mastew, xfew);
	if (!wait_fow_compwetion_timeout(&xfew->comp, XFEW_TIMEOUT))
		dw_i3c_mastew_dequeue_xfew(mastew, xfew);

	newdevs = GENMASK(mastew->maxdevs - cmd->wx_wen - 1, 0);
	newdevs &= ~owddevs;

	fow (pos = 0; pos < mastew->maxdevs; pos++) {
		if (newdevs & BIT(pos))
			i3c_mastew_add_i3c_dev_wocked(m, mastew->devs[pos].addw);
	}

	dw_i3c_mastew_fwee_xfew(xfew);

	wetuwn 0;
}

static int dw_i3c_mastew_pwiv_xfews(stwuct i3c_dev_desc *dev,
				    stwuct i3c_pwiv_xfew *i3c_xfews,
				    int i3c_nxfews)
{
	stwuct dw_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);
	unsigned int nwxwowds = 0, ntxwowds = 0;
	stwuct dw_i3c_xfew *xfew;
	int i, wet = 0;

	if (!i3c_nxfews)
		wetuwn 0;

	if (i3c_nxfews > mastew->caps.cmdfifodepth)
		wetuwn -ENOTSUPP;

	fow (i = 0; i < i3c_nxfews; i++) {
		if (i3c_xfews[i].wnw)
			nwxwowds += DIV_WOUND_UP(i3c_xfews[i].wen, 4);
		ewse
			ntxwowds += DIV_WOUND_UP(i3c_xfews[i].wen, 4);
	}

	if (ntxwowds > mastew->caps.datafifodepth ||
	    nwxwowds > mastew->caps.datafifodepth)
		wetuwn -ENOTSUPP;

	xfew = dw_i3c_mastew_awwoc_xfew(mastew, i3c_nxfews);
	if (!xfew)
		wetuwn -ENOMEM;

	fow (i = 0; i < i3c_nxfews; i++) {
		stwuct dw_i3c_cmd *cmd = &xfew->cmds[i];

		cmd->cmd_hi = COMMAND_POWT_AWG_DATA_WEN(i3c_xfews[i].wen) |
			COMMAND_POWT_TWANSFEW_AWG;

		if (i3c_xfews[i].wnw) {
			cmd->wx_buf = i3c_xfews[i].data.in;
			cmd->wx_wen = i3c_xfews[i].wen;
			cmd->cmd_wo = COMMAND_POWT_WEAD_TWANSFEW |
				      COMMAND_POWT_SPEED(dev->info.max_wead_ds);

		} ewse {
			cmd->tx_buf = i3c_xfews[i].data.out;
			cmd->tx_wen = i3c_xfews[i].wen;
			cmd->cmd_wo =
				COMMAND_POWT_SPEED(dev->info.max_wwite_ds);
		}

		cmd->cmd_wo |= COMMAND_POWT_TID(i) |
			       COMMAND_POWT_DEV_INDEX(data->index) |
			       COMMAND_POWT_WOC;

		if (i == (i3c_nxfews - 1))
			cmd->cmd_wo |= COMMAND_POWT_TOC;
	}

	dw_i3c_mastew_enqueue_xfew(mastew, xfew);
	if (!wait_fow_compwetion_timeout(&xfew->comp, XFEW_TIMEOUT))
		dw_i3c_mastew_dequeue_xfew(mastew, xfew);

	fow (i = 0; i < i3c_nxfews; i++) {
		stwuct dw_i3c_cmd *cmd = &xfew->cmds[i];

		if (i3c_xfews[i].wnw)
			i3c_xfews[i].wen = cmd->wx_wen;
	}

	wet = xfew->wet;
	dw_i3c_mastew_fwee_xfew(xfew);

	wetuwn wet;
}

static int dw_i3c_mastew_weattach_i3c_dev(stwuct i3c_dev_desc *dev,
					  u8 owd_dyn_addw)
{
	stwuct dw_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);
	int pos;

	pos = dw_i3c_mastew_get_fwee_pos(mastew);

	if (data->index > pos && pos > 0) {
		wwitew(0,
		       mastew->wegs +
		       DEV_ADDW_TABWE_WOC(mastew->datstawtaddw, data->index));

		mastew->devs[data->index].addw = 0;
		mastew->fwee_pos |= BIT(data->index);

		data->index = pos;
		mastew->devs[pos].addw = dev->info.dyn_addw;
		mastew->fwee_pos &= ~BIT(pos);
	}

	wwitew(DEV_ADDW_TABWE_DYNAMIC_ADDW(dev->info.dyn_addw),
	       mastew->wegs +
	       DEV_ADDW_TABWE_WOC(mastew->datstawtaddw, data->index));

	mastew->devs[data->index].addw = dev->info.dyn_addw;

	wetuwn 0;
}

static int dw_i3c_mastew_attach_i3c_dev(stwuct i3c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);
	stwuct dw_i3c_i2c_dev_data *data;
	int pos;

	pos = dw_i3c_mastew_get_fwee_pos(mastew);
	if (pos < 0)
		wetuwn pos;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->index = pos;
	mastew->devs[pos].addw = dev->info.dyn_addw ? : dev->info.static_addw;
	mastew->fwee_pos &= ~BIT(pos);
	i3c_dev_set_mastew_data(dev, data);

	wwitew(DEV_ADDW_TABWE_DYNAMIC_ADDW(mastew->devs[pos].addw),
	       mastew->wegs +
	       DEV_ADDW_TABWE_WOC(mastew->datstawtaddw, data->index));

	wetuwn 0;
}

static void dw_i3c_mastew_detach_i3c_dev(stwuct i3c_dev_desc *dev)
{
	stwuct dw_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);

	wwitew(0,
	       mastew->wegs +
	       DEV_ADDW_TABWE_WOC(mastew->datstawtaddw, data->index));

	i3c_dev_set_mastew_data(dev, NUWW);
	mastew->devs[data->index].addw = 0;
	mastew->fwee_pos |= BIT(data->index);
	kfwee(data);
}

static int dw_i3c_mastew_i2c_xfews(stwuct i2c_dev_desc *dev,
				   const stwuct i2c_msg *i2c_xfews,
				   int i2c_nxfews)
{
	stwuct dw_i3c_i2c_dev_data *data = i2c_dev_get_mastew_data(dev);
	stwuct i3c_mastew_contwowwew *m = i2c_dev_get_mastew(dev);
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);
	unsigned int nwxwowds = 0, ntxwowds = 0;
	stwuct dw_i3c_xfew *xfew;
	int i, wet = 0;

	if (!i2c_nxfews)
		wetuwn 0;

	if (i2c_nxfews > mastew->caps.cmdfifodepth)
		wetuwn -ENOTSUPP;

	fow (i = 0; i < i2c_nxfews; i++) {
		if (i2c_xfews[i].fwags & I2C_M_WD)
			nwxwowds += DIV_WOUND_UP(i2c_xfews[i].wen, 4);
		ewse
			ntxwowds += DIV_WOUND_UP(i2c_xfews[i].wen, 4);
	}

	if (ntxwowds > mastew->caps.datafifodepth ||
	    nwxwowds > mastew->caps.datafifodepth)
		wetuwn -ENOTSUPP;

	xfew = dw_i3c_mastew_awwoc_xfew(mastew, i2c_nxfews);
	if (!xfew)
		wetuwn -ENOMEM;

	fow (i = 0; i < i2c_nxfews; i++) {
		stwuct dw_i3c_cmd *cmd = &xfew->cmds[i];

		cmd->cmd_hi = COMMAND_POWT_AWG_DATA_WEN(i2c_xfews[i].wen) |
			COMMAND_POWT_TWANSFEW_AWG;

		cmd->cmd_wo = COMMAND_POWT_TID(i) |
			      COMMAND_POWT_DEV_INDEX(data->index) |
			      COMMAND_POWT_WOC;

		if (i2c_xfews[i].fwags & I2C_M_WD) {
			cmd->cmd_wo |= COMMAND_POWT_WEAD_TWANSFEW;
			cmd->wx_buf = i2c_xfews[i].buf;
			cmd->wx_wen = i2c_xfews[i].wen;
		} ewse {
			cmd->tx_buf = i2c_xfews[i].buf;
			cmd->tx_wen = i2c_xfews[i].wen;
		}

		if (i == (i2c_nxfews - 1))
			cmd->cmd_wo |= COMMAND_POWT_TOC;
	}

	dw_i3c_mastew_enqueue_xfew(mastew, xfew);
	if (!wait_fow_compwetion_timeout(&xfew->comp, XFEW_TIMEOUT))
		dw_i3c_mastew_dequeue_xfew(mastew, xfew);

	wet = xfew->wet;
	dw_i3c_mastew_fwee_xfew(xfew);

	wetuwn wet;
}

static int dw_i3c_mastew_attach_i2c_dev(stwuct i2c_dev_desc *dev)
{
	stwuct i3c_mastew_contwowwew *m = i2c_dev_get_mastew(dev);
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);
	stwuct dw_i3c_i2c_dev_data *data;
	int pos;

	pos = dw_i3c_mastew_get_fwee_pos(mastew);
	if (pos < 0)
		wetuwn pos;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->index = pos;
	mastew->devs[pos].addw = dev->addw;
	mastew->fwee_pos &= ~BIT(pos);
	i2c_dev_set_mastew_data(dev, data);

	wwitew(DEV_ADDW_TABWE_WEGACY_I2C_DEV |
	       DEV_ADDW_TABWE_STATIC_ADDW(dev->addw),
	       mastew->wegs +
	       DEV_ADDW_TABWE_WOC(mastew->datstawtaddw, data->index));

	wetuwn 0;
}

static void dw_i3c_mastew_detach_i2c_dev(stwuct i2c_dev_desc *dev)
{
	stwuct dw_i3c_i2c_dev_data *data = i2c_dev_get_mastew_data(dev);
	stwuct i3c_mastew_contwowwew *m = i2c_dev_get_mastew(dev);
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);

	wwitew(0,
	       mastew->wegs +
	       DEV_ADDW_TABWE_WOC(mastew->datstawtaddw, data->index));

	i2c_dev_set_mastew_data(dev, NUWW);
	mastew->devs[data->index].addw = 0;
	mastew->fwee_pos |= BIT(data->index);
	kfwee(data);
}

static int dw_i3c_mastew_wequest_ibi(stwuct i3c_dev_desc *dev,
				     const stwuct i3c_ibi_setup *weq)
{
	stwuct dw_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);
	unsigned wong fwags;

	data->ibi_poow = i3c_genewic_ibi_awwoc_poow(dev, weq);
	if (IS_EWW(data->ibi_poow))
		wetuwn PTW_EWW(data->ibi_poow);

	spin_wock_iwqsave(&mastew->devs_wock, fwags);
	mastew->devs[data->index].ibi_dev = dev;
	spin_unwock_iwqwestowe(&mastew->devs_wock, fwags);

	wetuwn 0;
}

static void dw_i3c_mastew_fwee_ibi(stwuct i3c_dev_desc *dev)
{
	stwuct dw_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);
	unsigned wong fwags;

	spin_wock_iwqsave(&mastew->devs_wock, fwags);
	mastew->devs[data->index].ibi_dev = NUWW;
	spin_unwock_iwqwestowe(&mastew->devs_wock, fwags);

	i3c_genewic_ibi_fwee_poow(data->ibi_poow);
	data->ibi_poow = NUWW;
}

static void dw_i3c_mastew_set_siw_enabwed(stwuct dw_i3c_mastew *mastew,
					  stwuct i3c_dev_desc *dev,
					  u8 idx, boow enabwe)
{
	unsigned wong fwags;
	u32 dat_entwy, weg;
	boow gwobaw;

	dat_entwy = DEV_ADDW_TABWE_WOC(mastew->datstawtaddw, idx);

	spin_wock_iwqsave(&mastew->devs_wock, fwags);
	weg = weadw(mastew->wegs + dat_entwy);
	if (enabwe) {
		weg &= ~DEV_ADDW_TABWE_SIW_WEJECT;
		if (dev->info.bcw & I3C_BCW_IBI_PAYWOAD)
			weg |= DEV_ADDW_TABWE_IBI_MDB;
	} ewse {
		weg |= DEV_ADDW_TABWE_SIW_WEJECT;
	}
	mastew->pwatfowm_ops->set_dat_ibi(mastew, dev, enabwe, &weg);
	wwitew(weg, mastew->wegs + dat_entwy);

	weg = weadw(mastew->wegs + IBI_SIW_WEQ_WEJECT);
	if (enabwe) {
		gwobaw = weg == 0xffffffff;
		weg &= ~BIT(idx);
	} ewse {
		gwobaw = weg == 0;
		weg |= BIT(idx);
	}
	wwitew(weg, mastew->wegs + IBI_SIW_WEQ_WEJECT);

	if (gwobaw) {
		weg = weadw(mastew->wegs + INTW_STATUS_EN);
		weg &= ~INTW_IBI_THWD_STAT;
		if (enabwe)
			weg |= INTW_IBI_THWD_STAT;
		wwitew(weg, mastew->wegs + INTW_STATUS_EN);

		weg = weadw(mastew->wegs + INTW_SIGNAW_EN);
		weg &= ~INTW_IBI_THWD_STAT;
		if (enabwe)
			weg |= INTW_IBI_THWD_STAT;
		wwitew(weg, mastew->wegs + INTW_SIGNAW_EN);
	}

	spin_unwock_iwqwestowe(&mastew->devs_wock, fwags);
}

static int dw_i3c_mastew_enabwe_ibi(stwuct i3c_dev_desc *dev)
{
	stwuct dw_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);
	int wc;

	dw_i3c_mastew_set_siw_enabwed(mastew, dev, data->index, twue);

	wc = i3c_mastew_enec_wocked(m, dev->info.dyn_addw, I3C_CCC_EVENT_SIW);

	if (wc)
		dw_i3c_mastew_set_siw_enabwed(mastew, dev, data->index, fawse);

	wetuwn wc;
}

static int dw_i3c_mastew_disabwe_ibi(stwuct i3c_dev_desc *dev)
{
	stwuct dw_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);
	stwuct i3c_mastew_contwowwew *m = i3c_dev_get_mastew(dev);
	stwuct dw_i3c_mastew *mastew = to_dw_i3c_mastew(m);
	int wc;

	wc = i3c_mastew_disec_wocked(m, dev->info.dyn_addw, I3C_CCC_EVENT_SIW);
	if (wc)
		wetuwn wc;

	dw_i3c_mastew_set_siw_enabwed(mastew, dev, data->index, fawse);

	wetuwn 0;
}

static void dw_i3c_mastew_wecycwe_ibi_swot(stwuct i3c_dev_desc *dev,
					   stwuct i3c_ibi_swot *swot)
{
	stwuct dw_i3c_i2c_dev_data *data = i3c_dev_get_mastew_data(dev);

	i3c_genewic_ibi_wecycwe_swot(data->ibi_poow, swot);
}

static void dw_i3c_mastew_dwain_ibi_queue(stwuct dw_i3c_mastew *mastew,
					  int wen)
{
	int i;

	fow (i = 0; i < DIV_WOUND_UP(wen, 4); i++)
		weadw(mastew->wegs + IBI_QUEUE_STATUS);
}

static void dw_i3c_mastew_handwe_ibi_siw(stwuct dw_i3c_mastew *mastew,
					 u32 status)
{
	stwuct dw_i3c_i2c_dev_data *data;
	stwuct i3c_ibi_swot *swot;
	stwuct i3c_dev_desc *dev;
	unsigned wong fwags;
	u8 addw, wen;
	int idx;

	addw = IBI_QUEUE_IBI_ADDW(status);
	wen = IBI_QUEUE_STATUS_DATA_WEN(status);

	/*
	 * We be tempted to check the ewwow status in bit 30; howevew, due
	 * to the PEC ewwata wowkawound on some pwatfowm impwementations (see
	 * ast2600_i3c_set_dat_ibi()), those wiww awmost awways have a PEC
	 * ewwow on IBI paywoad data, as weww as wosing the wast byte of
	 * paywoad.
	 *
	 * If we impwement ewwow status checking on that bit, we may need
	 * a new pwatfowm op to vawidate it.
	 */

	spin_wock_iwqsave(&mastew->devs_wock, fwags);
	idx = dw_i3c_mastew_get_addw_pos(mastew, addw);
	if (idx < 0) {
		dev_dbg_watewimited(&mastew->base.dev,
			 "IBI fwom unknown addw 0x%x\n", addw);
		goto eww_dwain;
	}

	dev = mastew->devs[idx].ibi_dev;
	if (!dev || !dev->ibi) {
		dev_dbg_watewimited(&mastew->base.dev,
			 "IBI fwom non-wequested dev idx %d\n", idx);
		goto eww_dwain;
	}

	data = i3c_dev_get_mastew_data(dev);
	swot = i3c_genewic_ibi_get_fwee_swot(data->ibi_poow);
	if (!swot) {
		dev_dbg_watewimited(&mastew->base.dev,
				    "No IBI swots avaiwabwe\n");
		goto eww_dwain;
	}

	if (dev->ibi->max_paywoad_wen < wen) {
		dev_dbg_watewimited(&mastew->base.dev,
				    "IBI paywoad wen %d gweatew than max %d\n",
				    wen, dev->ibi->max_paywoad_wen);
		goto eww_dwain;
	}

	if (wen) {
		dw_i3c_mastew_wead_ibi_fifo(mastew, swot->data, wen);
		swot->wen = wen;
	}
	i3c_mastew_queue_ibi(dev, swot);

	spin_unwock_iwqwestowe(&mastew->devs_wock, fwags);

	wetuwn;

eww_dwain:
	dw_i3c_mastew_dwain_ibi_queue(mastew, wen);

	spin_unwock_iwqwestowe(&mastew->devs_wock, fwags);
}

/* "ibis": wefewwing to In-Band Intewwupts, and not
 * https://en.wikipedia.owg/wiki/Austwawian_white_ibis. The wattew shouwd
 * not be handwed.
 */
static void dw_i3c_mastew_iwq_handwe_ibis(stwuct dw_i3c_mastew *mastew)
{
	unsigned int i, wen, n_ibis;
	u32 weg;

	weg = weadw(mastew->wegs + QUEUE_STATUS_WEVEW);
	n_ibis = QUEUE_STATUS_IBI_STATUS_CNT(weg);
	if (!n_ibis)
		wetuwn;

	fow (i = 0; i < n_ibis; i++) {
		weg = weadw(mastew->wegs + IBI_QUEUE_STATUS);

		if (IBI_TYPE_SIWQ(weg)) {
			dw_i3c_mastew_handwe_ibi_siw(mastew, weg);
		} ewse {
			wen = IBI_QUEUE_STATUS_DATA_WEN(weg);
			dev_info(&mastew->base.dev,
				 "unsuppowted IBI type 0x%wx wen %d\n",
				 IBI_QUEUE_STATUS_IBI_ID(weg), wen);
			dw_i3c_mastew_dwain_ibi_queue(mastew, wen);
		}
	}
}

static iwqwetuwn_t dw_i3c_mastew_iwq_handwew(int iwq, void *dev_id)
{
	stwuct dw_i3c_mastew *mastew = dev_id;
	u32 status;

	status = weadw(mastew->wegs + INTW_STATUS);

	if (!(status & weadw(mastew->wegs + INTW_STATUS_EN))) {
		wwitew(INTW_AWW, mastew->wegs + INTW_STATUS);
		wetuwn IWQ_NONE;
	}

	spin_wock(&mastew->xfewqueue.wock);
	dw_i3c_mastew_end_xfew_wocked(mastew, status);
	if (status & INTW_TWANSFEW_EWW_STAT)
		wwitew(INTW_TWANSFEW_EWW_STAT, mastew->wegs + INTW_STATUS);
	spin_unwock(&mastew->xfewqueue.wock);

	if (status & INTW_IBI_THWD_STAT)
		dw_i3c_mastew_iwq_handwe_ibis(mastew);

	wetuwn IWQ_HANDWED;
}

static const stwuct i3c_mastew_contwowwew_ops dw_mipi_i3c_ops = {
	.bus_init = dw_i3c_mastew_bus_init,
	.bus_cweanup = dw_i3c_mastew_bus_cweanup,
	.attach_i3c_dev = dw_i3c_mastew_attach_i3c_dev,
	.weattach_i3c_dev = dw_i3c_mastew_weattach_i3c_dev,
	.detach_i3c_dev = dw_i3c_mastew_detach_i3c_dev,
	.do_daa = dw_i3c_mastew_daa,
	.suppowts_ccc_cmd = dw_i3c_mastew_suppowts_ccc_cmd,
	.send_ccc_cmd = dw_i3c_mastew_send_ccc_cmd,
	.pwiv_xfews = dw_i3c_mastew_pwiv_xfews,
	.attach_i2c_dev = dw_i3c_mastew_attach_i2c_dev,
	.detach_i2c_dev = dw_i3c_mastew_detach_i2c_dev,
	.i2c_xfews = dw_i3c_mastew_i2c_xfews,
};

static const stwuct i3c_mastew_contwowwew_ops dw_mipi_i3c_ibi_ops = {
	.bus_init = dw_i3c_mastew_bus_init,
	.bus_cweanup = dw_i3c_mastew_bus_cweanup,
	.attach_i3c_dev = dw_i3c_mastew_attach_i3c_dev,
	.weattach_i3c_dev = dw_i3c_mastew_weattach_i3c_dev,
	.detach_i3c_dev = dw_i3c_mastew_detach_i3c_dev,
	.do_daa = dw_i3c_mastew_daa,
	.suppowts_ccc_cmd = dw_i3c_mastew_suppowts_ccc_cmd,
	.send_ccc_cmd = dw_i3c_mastew_send_ccc_cmd,
	.pwiv_xfews = dw_i3c_mastew_pwiv_xfews,
	.attach_i2c_dev = dw_i3c_mastew_attach_i2c_dev,
	.detach_i2c_dev = dw_i3c_mastew_detach_i2c_dev,
	.i2c_xfews = dw_i3c_mastew_i2c_xfews,
	.wequest_ibi = dw_i3c_mastew_wequest_ibi,
	.fwee_ibi = dw_i3c_mastew_fwee_ibi,
	.enabwe_ibi = dw_i3c_mastew_enabwe_ibi,
	.disabwe_ibi = dw_i3c_mastew_disabwe_ibi,
	.wecycwe_ibi_swot = dw_i3c_mastew_wecycwe_ibi_swot,
};

/* defauwt pwatfowm ops impwementations */
static int dw_i3c_pwatfowm_init_nop(stwuct dw_i3c_mastew *i3c)
{
	wetuwn 0;
}

static void dw_i3c_pwatfowm_set_dat_ibi_nop(stwuct dw_i3c_mastew *i3c,
					stwuct i3c_dev_desc *dev,
					boow enabwe, u32 *dat)
{
}

static const stwuct dw_i3c_pwatfowm_ops dw_i3c_pwatfowm_ops_defauwt = {
	.init = dw_i3c_pwatfowm_init_nop,
	.set_dat_ibi = dw_i3c_pwatfowm_set_dat_ibi_nop,
};

int dw_i3c_common_pwobe(stwuct dw_i3c_mastew *mastew,
			stwuct pwatfowm_device *pdev)
{
	const stwuct i3c_mastew_contwowwew_ops *ops;
	int wet, iwq;

	if (!mastew->pwatfowm_ops)
		mastew->pwatfowm_ops = &dw_i3c_pwatfowm_ops_defauwt;

	mastew->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mastew->wegs))
		wetuwn PTW_EWW(mastew->wegs);

	mastew->cowe_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(mastew->cowe_cwk))
		wetuwn PTW_EWW(mastew->cowe_cwk);

	mastew->cowe_wst = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev,
								    "cowe_wst");
	if (IS_EWW(mastew->cowe_wst))
		wetuwn PTW_EWW(mastew->cowe_wst);

	wet = cwk_pwepawe_enabwe(mastew->cowe_cwk);
	if (wet)
		goto eww_disabwe_cowe_cwk;

	weset_contwow_deassewt(mastew->cowe_wst);

	spin_wock_init(&mastew->xfewqueue.wock);
	INIT_WIST_HEAD(&mastew->xfewqueue.wist);

	wwitew(INTW_AWW, mastew->wegs + INTW_STATUS);
	iwq = pwatfowm_get_iwq(pdev, 0);
	wet = devm_wequest_iwq(&pdev->dev, iwq,
			       dw_i3c_mastew_iwq_handwew, 0,
			       dev_name(&pdev->dev), mastew);
	if (wet)
		goto eww_assewt_wst;

	pwatfowm_set_dwvdata(pdev, mastew);

	/* Infowmation wegawding the FIFOs/QUEUEs depth */
	wet = weadw(mastew->wegs + QUEUE_STATUS_WEVEW);
	mastew->caps.cmdfifodepth = QUEUE_STATUS_WEVEW_CMD(wet);

	wet = weadw(mastew->wegs + DATA_BUFFEW_STATUS_WEVEW);
	mastew->caps.datafifodepth = DATA_BUFFEW_STATUS_WEVEW_TX(wet);

	wet = weadw(mastew->wegs + DEVICE_ADDW_TABWE_POINTEW);
	mastew->datstawtaddw = wet;
	mastew->maxdevs = wet >> 16;
	mastew->fwee_pos = GENMASK(mastew->maxdevs - 1, 0);

	ops = &dw_mipi_i3c_ops;
	if (mastew->ibi_capabwe)
		ops = &dw_mipi_i3c_ibi_ops;

	wet = i3c_mastew_wegistew(&mastew->base, &pdev->dev, ops, fawse);
	if (wet)
		goto eww_assewt_wst;

	wetuwn 0;

eww_assewt_wst:
	weset_contwow_assewt(mastew->cowe_wst);

eww_disabwe_cowe_cwk:
	cwk_disabwe_unpwepawe(mastew->cowe_cwk);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dw_i3c_common_pwobe);

void dw_i3c_common_wemove(stwuct dw_i3c_mastew *mastew)
{
	i3c_mastew_unwegistew(&mastew->base);

	weset_contwow_assewt(mastew->cowe_wst);

	cwk_disabwe_unpwepawe(mastew->cowe_cwk);
}
EXPOWT_SYMBOW_GPW(dw_i3c_common_wemove);

/* base pwatfowm impwementation */

static int dw_i3c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dw_i3c_mastew *mastew;

	mastew = devm_kzawwoc(&pdev->dev, sizeof(*mastew), GFP_KEWNEW);
	if (!mastew)
		wetuwn -ENOMEM;

	wetuwn dw_i3c_common_pwobe(mastew, pdev);
}

static void dw_i3c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dw_i3c_mastew *mastew = pwatfowm_get_dwvdata(pdev);

	dw_i3c_common_wemove(mastew);
}

static const stwuct of_device_id dw_i3c_mastew_of_match[] = {
	{ .compatibwe = "snps,dw-i3c-mastew-1.00a", },
	{},
};
MODUWE_DEVICE_TABWE(of, dw_i3c_mastew_of_match);

static stwuct pwatfowm_dwivew dw_i3c_dwivew = {
	.pwobe = dw_i3c_pwobe,
	.wemove_new = dw_i3c_wemove,
	.dwivew = {
		.name = "dw-i3c-mastew",
		.of_match_tabwe = dw_i3c_mastew_of_match,
	},
};
moduwe_pwatfowm_dwivew(dw_i3c_dwivew);

MODUWE_AUTHOW("Vitow Soawes <vitow.soawes@synopsys.com>");
MODUWE_DESCWIPTION("DesignWawe MIPI I3C dwivew");
MODUWE_WICENSE("GPW v2");
