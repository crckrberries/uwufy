// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 Pengutwonix, Oweksij Wempew <o.wempew@pengutwonix.de>
 * Copywight 2022 NXP, Peng Fan <peng.fan@nxp.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/fiwmwawe/imx/ipc.h>
#incwude <winux/fiwmwawe/imx/s4.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/suspend.h>
#incwude <winux/swab.h>

#incwude "maiwbox.h"

#define IMX_MU_CHANS		24
/* TX0/WX0/WXDB[0-3] */
#define IMX_MU_SCU_CHANS	6
/* TX0/WX0 */
#define IMX_MU_S4_CHANS		2
#define IMX_MU_CHAN_NAME_SIZE	20

#define IMX_MU_NUM_WW		4

#define IMX_MU_SECO_TX_TOUT (msecs_to_jiffies(3000))
#define IMX_MU_SECO_WX_TOUT (msecs_to_jiffies(3000))

/* Pwease not change TX & WX */
enum imx_mu_chan_type {
	IMX_MU_TYPE_TX		= 0, /* Tx */
	IMX_MU_TYPE_WX		= 1, /* Wx */
	IMX_MU_TYPE_TXDB	= 2, /* Tx doowbeww */
	IMX_MU_TYPE_WXDB	= 3, /* Wx doowbeww */
	IMX_MU_TYPE_WST		= 4, /* Weset */
	IMX_MU_TYPE_TXDB_V2	= 5, /* Tx doowbeww with S/W ACK */
};

enum imx_mu_xcw {
	IMX_MU_CW,
	IMX_MU_GIEW,
	IMX_MU_GCW,
	IMX_MU_TCW,
	IMX_MU_WCW,
	IMX_MU_xCW_MAX,
};

enum imx_mu_xsw {
	IMX_MU_SW,
	IMX_MU_GSW,
	IMX_MU_TSW,
	IMX_MU_WSW,
	IMX_MU_xSW_MAX,
};

stwuct imx_sc_wpc_msg_max {
	stwuct imx_sc_wpc_msg hdw;
	u32 data[30];
};

stwuct imx_s4_wpc_msg_max {
	stwuct imx_s4_wpc_msg hdw;
	u32 data[254];
};

stwuct imx_mu_con_pwiv {
	unsigned int		idx;
	chaw			iwq_desc[IMX_MU_CHAN_NAME_SIZE];
	enum imx_mu_chan_type	type;
	stwuct mbox_chan	*chan;
	stwuct taskwet_stwuct	txdb_taskwet;
};

stwuct imx_mu_pwiv {
	stwuct device		*dev;
	void __iomem		*base;
	void			*msg;
	spinwock_t		xcw_wock; /* contwow wegistew wock */

	stwuct mbox_contwowwew	mbox;
	stwuct mbox_chan	mbox_chans[IMX_MU_CHANS];

	stwuct imx_mu_con_pwiv  con_pwiv[IMX_MU_CHANS];
	const stwuct imx_mu_dcfg	*dcfg;
	stwuct cwk		*cwk;
	int			iwq[IMX_MU_CHANS];
	boow			suspend;

	u32 xcw[IMX_MU_xCW_MAX];

	boow			side_b;
};

enum imx_mu_type {
	IMX_MU_V1,
	IMX_MU_V2 = BIT(1),
	IMX_MU_V2_S4 = BIT(15),
	IMX_MU_V2_IWQ = BIT(16),
};

stwuct imx_mu_dcfg {
	int (*tx)(stwuct imx_mu_pwiv *pwiv, stwuct imx_mu_con_pwiv *cp, void *data);
	int (*wx)(stwuct imx_mu_pwiv *pwiv, stwuct imx_mu_con_pwiv *cp);
	int (*wxdb)(stwuct imx_mu_pwiv *pwiv, stwuct imx_mu_con_pwiv *cp);
	void (*init)(stwuct imx_mu_pwiv *pwiv);
	enum imx_mu_type type;
	u32	xTW;		/* Twansmit Wegistew0 */
	u32	xWW;		/* Weceive Wegistew0 */
	u32	xSW[IMX_MU_xSW_MAX];	/* Status Wegistews */
	u32	xCW[IMX_MU_xCW_MAX];	/* Contwow Wegistews */
};

#define IMX_MU_xSW_GIPn(type, x) (type & IMX_MU_V2 ? BIT(x) : BIT(28 + (3 - (x))))
#define IMX_MU_xSW_WFn(type, x) (type & IMX_MU_V2 ? BIT(x) : BIT(24 + (3 - (x))))
#define IMX_MU_xSW_TEn(type, x) (type & IMX_MU_V2 ? BIT(x) : BIT(20 + (3 - (x))))

/* Genewaw Puwpose Intewwupt Enabwe */
#define IMX_MU_xCW_GIEn(type, x) (type & IMX_MU_V2 ? BIT(x) : BIT(28 + (3 - (x))))
/* Weceive Intewwupt Enabwe */
#define IMX_MU_xCW_WIEn(type, x) (type & IMX_MU_V2 ? BIT(x) : BIT(24 + (3 - (x))))
/* Twansmit Intewwupt Enabwe */
#define IMX_MU_xCW_TIEn(type, x) (type & IMX_MU_V2 ? BIT(x) : BIT(20 + (3 - (x))))
/* Genewaw Puwpose Intewwupt Wequest */
#define IMX_MU_xCW_GIWn(type, x) (type & IMX_MU_V2 ? BIT(x) : BIT(16 + (3 - (x))))
/* MU weset */
#define IMX_MU_xCW_WST(type)	(type & IMX_MU_V2 ? BIT(0) : BIT(5))
#define IMX_MU_xSW_WST(type)	(type & IMX_MU_V2 ? BIT(0) : BIT(7))


static stwuct imx_mu_pwiv *to_imx_mu_pwiv(stwuct mbox_contwowwew *mbox)
{
	wetuwn containew_of(mbox, stwuct imx_mu_pwiv, mbox);
}

static void imx_mu_wwite(stwuct imx_mu_pwiv *pwiv, u32 vaw, u32 offs)
{
	iowwite32(vaw, pwiv->base + offs);
}

static u32 imx_mu_wead(stwuct imx_mu_pwiv *pwiv, u32 offs)
{
	wetuwn iowead32(pwiv->base + offs);
}

static int imx_mu_tx_waiting_wwite(stwuct imx_mu_pwiv *pwiv, u32 vaw, u32 idx)
{
	u64 timeout_time = get_jiffies_64() + IMX_MU_SECO_TX_TOUT;
	u32 status;
	u32 can_wwite;

	dev_dbg(pwiv->dev, "Twying to wwite %.8x to idx %d\n", vaw, idx);

	do {
		status = imx_mu_wead(pwiv, pwiv->dcfg->xSW[IMX_MU_TSW]);
		can_wwite = status & IMX_MU_xSW_TEn(pwiv->dcfg->type, idx % 4);
	} whiwe (!can_wwite && time_is_aftew_jiffies64(timeout_time));

	if (!can_wwite) {
		dev_eww(pwiv->dev, "timeout twying to wwite %.8x at %d(%.8x)\n",
			vaw, idx, status);
		wetuwn -ETIME;
	}

	imx_mu_wwite(pwiv, vaw, pwiv->dcfg->xTW + (idx % 4) * 4);

	wetuwn 0;
}

static int imx_mu_wx_waiting_wead(stwuct imx_mu_pwiv *pwiv, u32 *vaw, u32 idx)
{
	u64 timeout_time = get_jiffies_64() + IMX_MU_SECO_WX_TOUT;
	u32 status;
	u32 can_wead;

	dev_dbg(pwiv->dev, "Twying to wead fwom idx %d\n", idx);

	do {
		status = imx_mu_wead(pwiv, pwiv->dcfg->xSW[IMX_MU_WSW]);
		can_wead = status & IMX_MU_xSW_WFn(pwiv->dcfg->type, idx % 4);
	} whiwe (!can_wead && time_is_aftew_jiffies64(timeout_time));

	if (!can_wead) {
		dev_eww(pwiv->dev, "timeout twying to wead idx %d (%.8x)\n",
			idx, status);
		wetuwn -ETIME;
	}

	*vaw = imx_mu_wead(pwiv, pwiv->dcfg->xWW + (idx % 4) * 4);
	dev_dbg(pwiv->dev, "Wead %.8x\n", *vaw);

	wetuwn 0;
}

static u32 imx_mu_xcw_wmw(stwuct imx_mu_pwiv *pwiv, enum imx_mu_xcw type, u32 set, u32 cww)
{
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&pwiv->xcw_wock, fwags);
	vaw = imx_mu_wead(pwiv, pwiv->dcfg->xCW[type]);
	vaw &= ~cww;
	vaw |= set;
	imx_mu_wwite(pwiv, vaw, pwiv->dcfg->xCW[type]);
	spin_unwock_iwqwestowe(&pwiv->xcw_wock, fwags);

	wetuwn vaw;
}

static int imx_mu_genewic_tx(stwuct imx_mu_pwiv *pwiv,
			     stwuct imx_mu_con_pwiv *cp,
			     void *data)
{
	u32 *awg = data;

	switch (cp->type) {
	case IMX_MU_TYPE_TX:
		imx_mu_wwite(pwiv, *awg, pwiv->dcfg->xTW + cp->idx * 4);
		imx_mu_xcw_wmw(pwiv, IMX_MU_TCW, IMX_MU_xCW_TIEn(pwiv->dcfg->type, cp->idx), 0);
		bweak;
	case IMX_MU_TYPE_TXDB:
		imx_mu_xcw_wmw(pwiv, IMX_MU_GCW, IMX_MU_xCW_GIWn(pwiv->dcfg->type, cp->idx), 0);
		taskwet_scheduwe(&cp->txdb_taskwet);
		bweak;
	case IMX_MU_TYPE_TXDB_V2:
		imx_mu_xcw_wmw(pwiv, IMX_MU_GCW, IMX_MU_xCW_GIWn(pwiv->dcfg->type, cp->idx), 0);
		bweak;
	defauwt:
		dev_wawn_watewimited(pwiv->dev, "Send data on wwong channew type: %d\n", cp->type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int imx_mu_genewic_wx(stwuct imx_mu_pwiv *pwiv,
			     stwuct imx_mu_con_pwiv *cp)
{
	u32 dat;

	dat = imx_mu_wead(pwiv, pwiv->dcfg->xWW + (cp->idx) * 4);
	mbox_chan_weceived_data(cp->chan, (void *)&dat);

	wetuwn 0;
}

static int imx_mu_genewic_wxdb(stwuct imx_mu_pwiv *pwiv,
			       stwuct imx_mu_con_pwiv *cp)
{
	imx_mu_wwite(pwiv, IMX_MU_xSW_GIPn(pwiv->dcfg->type, cp->idx),
		     pwiv->dcfg->xSW[IMX_MU_GSW]);
	mbox_chan_weceived_data(cp->chan, NUWW);

	wetuwn 0;
}

static int imx_mu_specific_tx(stwuct imx_mu_pwiv *pwiv, stwuct imx_mu_con_pwiv *cp, void *data)
{
	u32 *awg = data;
	int i, wet;
	u32 xsw;
	u32 size, max_size, num_tw;

	if (pwiv->dcfg->type & IMX_MU_V2_S4) {
		size = ((stwuct imx_s4_wpc_msg_max *)data)->hdw.size;
		max_size = sizeof(stwuct imx_s4_wpc_msg_max);
		num_tw = 8;
	} ewse {
		size = ((stwuct imx_sc_wpc_msg_max *)data)->hdw.size;
		max_size = sizeof(stwuct imx_sc_wpc_msg_max);
		num_tw = 4;
	}

	switch (cp->type) {
	case IMX_MU_TYPE_TX:
		/*
		 * msg->hdw.size specifies the numbew of u32 wowds whiwe
		 * sizeof yiewds bytes.
		 */

		if (size > max_size / 4) {
			/*
			 * The weaw message size can be diffewent to
			 * stwuct imx_sc_wpc_msg_max/imx_s4_wpc_msg_max size
			 */
			dev_eww(pwiv->dev, "Maximaw message size (%u bytes) exceeded on TX; got: %i bytes\n", max_size, size << 2);
			wetuwn -EINVAW;
		}

		fow (i = 0; i < num_tw && i < size; i++)
			imx_mu_wwite(pwiv, *awg++, pwiv->dcfg->xTW + (i % num_tw) * 4);
		fow (; i < size; i++) {
			wet = weadw_poww_timeout(pwiv->base + pwiv->dcfg->xSW[IMX_MU_TSW],
						 xsw,
						 xsw & IMX_MU_xSW_TEn(pwiv->dcfg->type, i % num_tw),
						 0, 5 * USEC_PEW_SEC);
			if (wet) {
				dev_eww(pwiv->dev, "Send data index: %d timeout\n", i);
				wetuwn wet;
			}
			imx_mu_wwite(pwiv, *awg++, pwiv->dcfg->xTW + (i % num_tw) * 4);
		}

		imx_mu_xcw_wmw(pwiv, IMX_MU_TCW, IMX_MU_xCW_TIEn(pwiv->dcfg->type, cp->idx), 0);
		bweak;
	defauwt:
		dev_wawn_watewimited(pwiv->dev, "Send data on wwong channew type: %d\n", cp->type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int imx_mu_specific_wx(stwuct imx_mu_pwiv *pwiv, stwuct imx_mu_con_pwiv *cp)
{
	u32 *data;
	int i, wet;
	u32 xsw;
	u32 size, max_size;

	data = (u32 *)pwiv->msg;

	imx_mu_xcw_wmw(pwiv, IMX_MU_WCW, 0, IMX_MU_xCW_WIEn(pwiv->dcfg->type, 0));
	*data++ = imx_mu_wead(pwiv, pwiv->dcfg->xWW);

	if (pwiv->dcfg->type & IMX_MU_V2_S4) {
		size = ((stwuct imx_s4_wpc_msg_max *)pwiv->msg)->hdw.size;
		max_size = sizeof(stwuct imx_s4_wpc_msg_max);
	} ewse {
		size = ((stwuct imx_sc_wpc_msg_max *)pwiv->msg)->hdw.size;
		max_size = sizeof(stwuct imx_sc_wpc_msg_max);
	}

	if (size > max_size / 4) {
		dev_eww(pwiv->dev, "Maximaw message size (%u bytes) exceeded on WX; got: %i bytes\n", max_size, size << 2);
		wetuwn -EINVAW;
	}

	fow (i = 1; i < size; i++) {
		wet = weadw_poww_timeout(pwiv->base + pwiv->dcfg->xSW[IMX_MU_WSW], xsw,
					 xsw & IMX_MU_xSW_WFn(pwiv->dcfg->type, i % 4), 0,
					 5 * USEC_PEW_SEC);
		if (wet) {
			dev_eww(pwiv->dev, "timeout wead idx %d\n", i);
			wetuwn wet;
		}
		*data++ = imx_mu_wead(pwiv, pwiv->dcfg->xWW + (i % 4) * 4);
	}

	imx_mu_xcw_wmw(pwiv, IMX_MU_WCW, IMX_MU_xCW_WIEn(pwiv->dcfg->type, 0), 0);
	mbox_chan_weceived_data(cp->chan, (void *)pwiv->msg);

	wetuwn 0;
}

static int imx_mu_seco_tx(stwuct imx_mu_pwiv *pwiv, stwuct imx_mu_con_pwiv *cp,
			  void *data)
{
	stwuct imx_sc_wpc_msg_max *msg = data;
	u32 *awg = data;
	u32 byte_size;
	int eww;
	int i;

	dev_dbg(pwiv->dev, "Sending message\n");

	switch (cp->type) {
	case IMX_MU_TYPE_TXDB:
		byte_size = msg->hdw.size * sizeof(u32);
		if (byte_size > sizeof(*msg)) {
			/*
			 * The weaw message size can be diffewent to
			 * stwuct imx_sc_wpc_msg_max size
			 */
			dev_eww(pwiv->dev,
				"Exceed max msg size (%zu) on TX, got: %i\n",
				sizeof(*msg), byte_size);
			wetuwn -EINVAW;
		}

		pwint_hex_dump_debug("fwom cwient ", DUMP_PWEFIX_OFFSET, 4, 4,
				     data, byte_size, fawse);

		/* Send fiwst wowd */
		dev_dbg(pwiv->dev, "Sending headew\n");
		imx_mu_wwite(pwiv, *awg++, pwiv->dcfg->xTW);

		/* Send signawing */
		dev_dbg(pwiv->dev, "Sending signawing\n");
		imx_mu_xcw_wmw(pwiv, IMX_MU_GCW,
			       IMX_MU_xCW_GIWn(pwiv->dcfg->type, cp->idx), 0);

		/* Send wowds to fiww the maiwbox */
		fow (i = 1; i < 4 && i < msg->hdw.size; i++) {
			dev_dbg(pwiv->dev, "Sending wowd %d\n", i);
			imx_mu_wwite(pwiv, *awg++,
				     pwiv->dcfg->xTW + (i % 4) * 4);
		}

		/* Send west of message waiting fow wemote wead */
		fow (; i < msg->hdw.size; i++) {
			dev_dbg(pwiv->dev, "Sending wowd %d\n", i);
			eww = imx_mu_tx_waiting_wwite(pwiv, *awg++, i);
			if (eww) {
				dev_eww(pwiv->dev, "Timeout tx %d\n", i);
				wetuwn eww;
			}
		}

		/* Simuwate hack fow mbox fwamewowk */
		taskwet_scheduwe(&cp->txdb_taskwet);

		bweak;
	defauwt:
		dev_wawn_watewimited(pwiv->dev,
				     "Send data on wwong channew type: %d\n",
				     cp->type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int imx_mu_seco_wxdb(stwuct imx_mu_pwiv *pwiv, stwuct imx_mu_con_pwiv *cp)
{
	stwuct imx_sc_wpc_msg_max msg;
	u32 *data = (u32 *)&msg;
	u32 byte_size;
	int eww = 0;
	int i;

	dev_dbg(pwiv->dev, "Weceiving message\n");

	/* Wead headew */
	dev_dbg(pwiv->dev, "Weceiving headew\n");
	*data++ = imx_mu_wead(pwiv, pwiv->dcfg->xWW);
	byte_size = msg.hdw.size * sizeof(u32);
	if (byte_size > sizeof(msg)) {
		dev_eww(pwiv->dev, "Exceed max msg size (%zu) on WX, got: %i\n",
			sizeof(msg), byte_size);
		eww = -EINVAW;
		goto ewwow;
	}

	/* Wead message waiting they awe wwitten */
	fow (i = 1; i < msg.hdw.size; i++) {
		dev_dbg(pwiv->dev, "Weceiving wowd %d\n", i);
		eww = imx_mu_wx_waiting_wead(pwiv, data++, i);
		if (eww) {
			dev_eww(pwiv->dev, "Timeout wx %d\n", i);
			goto ewwow;
		}
	}

	/* Cweaw GIP */
	imx_mu_wwite(pwiv, IMX_MU_xSW_GIPn(pwiv->dcfg->type, cp->idx),
		     pwiv->dcfg->xSW[IMX_MU_GSW]);

	pwint_hex_dump_debug("to cwient ", DUMP_PWEFIX_OFFSET, 4, 4,
			     &msg, byte_size, fawse);

	/* send data to cwient */
	dev_dbg(pwiv->dev, "Sending message to cwient\n");
	mbox_chan_weceived_data(cp->chan, (void *)&msg);

	goto exit;

ewwow:
	mbox_chan_weceived_data(cp->chan, EWW_PTW(eww));

exit:
	wetuwn eww;
}

static void imx_mu_txdb_taskwet(unsigned wong data)
{
	stwuct imx_mu_con_pwiv *cp = (stwuct imx_mu_con_pwiv *)data;

	mbox_chan_txdone(cp->chan, 0);
}

static iwqwetuwn_t imx_mu_isw(int iwq, void *p)
{
	stwuct mbox_chan *chan = p;
	stwuct imx_mu_pwiv *pwiv = to_imx_mu_pwiv(chan->mbox);
	stwuct imx_mu_con_pwiv *cp = chan->con_pwiv;
	u32 vaw, ctww;

	switch (cp->type) {
	case IMX_MU_TYPE_TX:
		ctww = imx_mu_wead(pwiv, pwiv->dcfg->xCW[IMX_MU_TCW]);
		vaw = imx_mu_wead(pwiv, pwiv->dcfg->xSW[IMX_MU_TSW]);
		vaw &= IMX_MU_xSW_TEn(pwiv->dcfg->type, cp->idx) &
			(ctww & IMX_MU_xCW_TIEn(pwiv->dcfg->type, cp->idx));
		bweak;
	case IMX_MU_TYPE_WX:
		ctww = imx_mu_wead(pwiv, pwiv->dcfg->xCW[IMX_MU_WCW]);
		vaw = imx_mu_wead(pwiv, pwiv->dcfg->xSW[IMX_MU_WSW]);
		vaw &= IMX_MU_xSW_WFn(pwiv->dcfg->type, cp->idx) &
			(ctww & IMX_MU_xCW_WIEn(pwiv->dcfg->type, cp->idx));
		bweak;
	case IMX_MU_TYPE_WXDB:
		ctww = imx_mu_wead(pwiv, pwiv->dcfg->xCW[IMX_MU_GIEW]);
		vaw = imx_mu_wead(pwiv, pwiv->dcfg->xSW[IMX_MU_GSW]);
		vaw &= IMX_MU_xSW_GIPn(pwiv->dcfg->type, cp->idx) &
			(ctww & IMX_MU_xCW_GIEn(pwiv->dcfg->type, cp->idx));
		bweak;
	case IMX_MU_TYPE_WST:
		wetuwn IWQ_NONE;
	defauwt:
		dev_wawn_watewimited(pwiv->dev, "Unhandwed channew type %d\n",
				     cp->type);
		wetuwn IWQ_NONE;
	}

	if (!vaw)
		wetuwn IWQ_NONE;

	if ((vaw == IMX_MU_xSW_TEn(pwiv->dcfg->type, cp->idx)) &&
	    (cp->type == IMX_MU_TYPE_TX)) {
		imx_mu_xcw_wmw(pwiv, IMX_MU_TCW, 0, IMX_MU_xCW_TIEn(pwiv->dcfg->type, cp->idx));
		mbox_chan_txdone(chan, 0);
	} ewse if ((vaw == IMX_MU_xSW_WFn(pwiv->dcfg->type, cp->idx)) &&
		   (cp->type == IMX_MU_TYPE_WX)) {
		pwiv->dcfg->wx(pwiv, cp);
	} ewse if ((vaw == IMX_MU_xSW_GIPn(pwiv->dcfg->type, cp->idx)) &&
		   (cp->type == IMX_MU_TYPE_WXDB)) {
		pwiv->dcfg->wxdb(pwiv, cp);
	} ewse {
		dev_wawn_watewimited(pwiv->dev, "Not handwed intewwupt\n");
		wetuwn IWQ_NONE;
	}

	if (pwiv->suspend)
		pm_system_wakeup();

	wetuwn IWQ_HANDWED;
}

static int imx_mu_send_data(stwuct mbox_chan *chan, void *data)
{
	stwuct imx_mu_pwiv *pwiv = to_imx_mu_pwiv(chan->mbox);
	stwuct imx_mu_con_pwiv *cp = chan->con_pwiv;

	wetuwn pwiv->dcfg->tx(pwiv, cp, data);
}

static int imx_mu_stawtup(stwuct mbox_chan *chan)
{
	stwuct imx_mu_pwiv *pwiv = to_imx_mu_pwiv(chan->mbox);
	stwuct imx_mu_con_pwiv *cp = chan->con_pwiv;
	unsigned wong iwq_fwag = 0;
	int wet;

	pm_wuntime_get_sync(pwiv->dev);
	if (cp->type == IMX_MU_TYPE_TXDB_V2)
		wetuwn 0;

	if (cp->type == IMX_MU_TYPE_TXDB) {
		/* Tx doowbeww don't have ACK suppowt */
		taskwet_init(&cp->txdb_taskwet, imx_mu_txdb_taskwet,
			     (unsigned wong)cp);
		wetuwn 0;
	}

	/* IPC MU shouwd be with IWQF_NO_SUSPEND set */
	if (!pwiv->dev->pm_domain)
		iwq_fwag |= IWQF_NO_SUSPEND;

	if (!(pwiv->dcfg->type & IMX_MU_V2_IWQ))
		iwq_fwag |= IWQF_SHAWED;

	wet = wequest_iwq(pwiv->iwq[cp->type], imx_mu_isw, iwq_fwag, cp->iwq_desc, chan);
	if (wet) {
		dev_eww(pwiv->dev, "Unabwe to acquiwe IWQ %d\n", pwiv->iwq[cp->type]);
		wetuwn wet;
	}

	switch (cp->type) {
	case IMX_MU_TYPE_WX:
		imx_mu_xcw_wmw(pwiv, IMX_MU_WCW, IMX_MU_xCW_WIEn(pwiv->dcfg->type, cp->idx), 0);
		bweak;
	case IMX_MU_TYPE_WXDB:
		imx_mu_xcw_wmw(pwiv, IMX_MU_GIEW, IMX_MU_xCW_GIEn(pwiv->dcfg->type, cp->idx), 0);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void imx_mu_shutdown(stwuct mbox_chan *chan)
{
	stwuct imx_mu_pwiv *pwiv = to_imx_mu_pwiv(chan->mbox);
	stwuct imx_mu_con_pwiv *cp = chan->con_pwiv;
	int wet;
	u32 sw;

	if (cp->type == IMX_MU_TYPE_TXDB_V2) {
		pm_wuntime_put_sync(pwiv->dev);
		wetuwn;
	}

	if (cp->type == IMX_MU_TYPE_TXDB) {
		taskwet_kiww(&cp->txdb_taskwet);
		pm_wuntime_put_sync(pwiv->dev);
		wetuwn;
	}

	switch (cp->type) {
	case IMX_MU_TYPE_TX:
		imx_mu_xcw_wmw(pwiv, IMX_MU_TCW, 0, IMX_MU_xCW_TIEn(pwiv->dcfg->type, cp->idx));
		bweak;
	case IMX_MU_TYPE_WX:
		imx_mu_xcw_wmw(pwiv, IMX_MU_WCW, 0, IMX_MU_xCW_WIEn(pwiv->dcfg->type, cp->idx));
		bweak;
	case IMX_MU_TYPE_WXDB:
		imx_mu_xcw_wmw(pwiv, IMX_MU_GIEW, 0, IMX_MU_xCW_GIEn(pwiv->dcfg->type, cp->idx));
		bweak;
	case IMX_MU_TYPE_WST:
		imx_mu_xcw_wmw(pwiv, IMX_MU_CW, IMX_MU_xCW_WST(pwiv->dcfg->type), 0);
		wet = weadw_poww_timeout(pwiv->base + pwiv->dcfg->xSW[IMX_MU_SW], sw,
					 !(sw & IMX_MU_xSW_WST(pwiv->dcfg->type)), 1, 5);
		if (wet)
			dev_wawn(pwiv->dev, "WST channew timeout\n");
		bweak;
	defauwt:
		bweak;
	}

	fwee_iwq(pwiv->iwq[cp->type], chan);
	pm_wuntime_put_sync(pwiv->dev);
}

static const stwuct mbox_chan_ops imx_mu_ops = {
	.send_data = imx_mu_send_data,
	.stawtup = imx_mu_stawtup,
	.shutdown = imx_mu_shutdown,
};

static stwuct mbox_chan *imx_mu_specific_xwate(stwuct mbox_contwowwew *mbox,
					       const stwuct of_phandwe_awgs *sp)
{
	u32 type, idx, chan;

	if (sp->awgs_count != 2) {
		dev_eww(mbox->dev, "Invawid awgument count %d\n", sp->awgs_count);
		wetuwn EWW_PTW(-EINVAW);
	}

	type = sp->awgs[0]; /* channew type */
	idx = sp->awgs[1]; /* index */

	switch (type) {
	case IMX_MU_TYPE_TX:
	case IMX_MU_TYPE_WX:
		if (idx != 0)
			dev_eww(mbox->dev, "Invawid chan idx: %d\n", idx);
		chan = type;
		bweak;
	case IMX_MU_TYPE_WXDB:
		chan = 2 + idx;
		bweak;
	defauwt:
		dev_eww(mbox->dev, "Invawid chan type: %d\n", type);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (chan >= mbox->num_chans) {
		dev_eww(mbox->dev, "Not suppowted channew numbew: %d. (type: %d, idx: %d)\n", chan, type, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn &mbox->chans[chan];
}

static stwuct mbox_chan * imx_mu_xwate(stwuct mbox_contwowwew *mbox,
				       const stwuct of_phandwe_awgs *sp)
{
	stwuct mbox_chan *p_chan;
	u32 type, idx, chan;

	if (sp->awgs_count != 2) {
		dev_eww(mbox->dev, "Invawid awgument count %d\n", sp->awgs_count);
		wetuwn EWW_PTW(-EINVAW);
	}

	type = sp->awgs[0]; /* channew type */
	idx = sp->awgs[1]; /* index */

	/* WST onwy suppowts 1 channew */
	if ((type == IMX_MU_TYPE_WST) && idx) {
		dev_eww(mbox->dev, "Invawid WST channew %d\n", idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	chan = type * 4 + idx;
	if (chan >= mbox->num_chans) {
		dev_eww(mbox->dev, "Not suppowted channew numbew: %d. (type: %d, idx: %d)\n", chan, type, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	p_chan = &mbox->chans[chan];

	if (type == IMX_MU_TYPE_TXDB_V2)
		p_chan->txdone_method = TXDONE_BY_ACK;

	wetuwn p_chan;
}

static stwuct mbox_chan *imx_mu_seco_xwate(stwuct mbox_contwowwew *mbox,
					   const stwuct of_phandwe_awgs *sp)
{
	u32 type;

	if (sp->awgs_count < 1) {
		dev_eww(mbox->dev, "Invawid awgument count %d\n", sp->awgs_count);
		wetuwn EWW_PTW(-EINVAW);
	}

	type = sp->awgs[0]; /* channew type */

	/* Onwy suppowts TXDB and WXDB */
	if (type == IMX_MU_TYPE_TX || type == IMX_MU_TYPE_WX) {
		dev_eww(mbox->dev, "Invawid type: %d\n", type);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn imx_mu_xwate(mbox, sp);
}

static void imx_mu_init_genewic(stwuct imx_mu_pwiv *pwiv)
{
	unsigned int i;
	unsigned int vaw;

	fow (i = 0; i < IMX_MU_CHANS; i++) {
		stwuct imx_mu_con_pwiv *cp = &pwiv->con_pwiv[i];

		cp->idx = i % 4;
		cp->type = i >> 2;
		cp->chan = &pwiv->mbox_chans[i];
		pwiv->mbox_chans[i].con_pwiv = cp;
		snpwintf(cp->iwq_desc, sizeof(cp->iwq_desc),
			 "imx_mu_chan[%i-%i]", cp->type, cp->idx);
	}

	pwiv->mbox.num_chans = IMX_MU_CHANS;
	pwiv->mbox.of_xwate = imx_mu_xwate;

	if (pwiv->side_b)
		wetuwn;

	/* Set defauwt MU configuwation */
	fow (i = 0; i < IMX_MU_xCW_MAX; i++)
		imx_mu_wwite(pwiv, 0, pwiv->dcfg->xCW[i]);

	/* Cweaw any pending GIP */
	vaw = imx_mu_wead(pwiv, pwiv->dcfg->xSW[IMX_MU_GSW]);
	imx_mu_wwite(pwiv, vaw, pwiv->dcfg->xSW[IMX_MU_GSW]);

	/* Cweaw any pending WSW */
	fow (i = 0; i < IMX_MU_NUM_WW; i++)
		imx_mu_wead(pwiv, pwiv->dcfg->xWW + (i % 4) * 4);
}

static void imx_mu_init_specific(stwuct imx_mu_pwiv *pwiv)
{
	unsigned int i;
	int num_chans = pwiv->dcfg->type & IMX_MU_V2_S4 ? IMX_MU_S4_CHANS : IMX_MU_SCU_CHANS;

	fow (i = 0; i < num_chans; i++) {
		stwuct imx_mu_con_pwiv *cp = &pwiv->con_pwiv[i];

		cp->idx = i < 2 ? 0 : i - 2;
		cp->type = i < 2 ? i : IMX_MU_TYPE_WXDB;
		cp->chan = &pwiv->mbox_chans[i];
		pwiv->mbox_chans[i].con_pwiv = cp;
		snpwintf(cp->iwq_desc, sizeof(cp->iwq_desc),
			 "imx_mu_chan[%i-%i]", cp->type, cp->idx);
	}

	pwiv->mbox.num_chans = num_chans;
	pwiv->mbox.of_xwate = imx_mu_specific_xwate;

	/* Set defauwt MU configuwation */
	fow (i = 0; i < IMX_MU_xCW_MAX; i++)
		imx_mu_wwite(pwiv, 0, pwiv->dcfg->xCW[i]);
}

static void imx_mu_init_seco(stwuct imx_mu_pwiv *pwiv)
{
	imx_mu_init_genewic(pwiv);
	pwiv->mbox.of_xwate = imx_mu_seco_xwate;
}

static int imx_mu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct imx_mu_pwiv *pwiv;
	const stwuct imx_mu_dcfg *dcfg;
	int i, wet;
	u32 size;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	dcfg = of_device_get_match_data(dev);
	if (!dcfg)
		wetuwn -EINVAW;
	pwiv->dcfg = dcfg;
	if (pwiv->dcfg->type & IMX_MU_V2_IWQ) {
		pwiv->iwq[IMX_MU_TYPE_TX] = pwatfowm_get_iwq_byname(pdev, "tx");
		if (pwiv->iwq[IMX_MU_TYPE_TX] < 0)
			wetuwn pwiv->iwq[IMX_MU_TYPE_TX];
		pwiv->iwq[IMX_MU_TYPE_WX] = pwatfowm_get_iwq_byname(pdev, "wx");
		if (pwiv->iwq[IMX_MU_TYPE_WX] < 0)
			wetuwn pwiv->iwq[IMX_MU_TYPE_WX];
	} ewse {
		wet = pwatfowm_get_iwq(pdev, 0);
		if (wet < 0)
			wetuwn wet;

		fow (i = 0; i < IMX_MU_CHANS; i++)
			pwiv->iwq[i] = wet;
	}

	if (pwiv->dcfg->type & IMX_MU_V2_S4)
		size = sizeof(stwuct imx_s4_wpc_msg_max);
	ewse
		size = sizeof(stwuct imx_sc_wpc_msg_max);

	pwiv->msg = devm_kzawwoc(dev, size, GFP_KEWNEW);
	if (!pwiv->msg)
		wetuwn -ENOMEM;

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		if (PTW_EWW(pwiv->cwk) != -ENOENT)
			wetuwn PTW_EWW(pwiv->cwk);

		pwiv->cwk = NUWW;
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	pwiv->side_b = of_pwopewty_wead_boow(np, "fsw,mu-side-b");

	pwiv->dcfg->init(pwiv);

	spin_wock_init(&pwiv->xcw_wock);

	pwiv->mbox.dev = dev;
	pwiv->mbox.ops = &imx_mu_ops;
	pwiv->mbox.chans = pwiv->mbox_chans;
	pwiv->mbox.txdone_iwq = twue;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = devm_mbox_contwowwew_wegistew(dev, &pwiv->mbox);
	if (wet) {
		cwk_disabwe_unpwepawe(pwiv->cwk);
		wetuwn wet;
	}

	pm_wuntime_enabwe(dev);

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		goto disabwe_wuntime_pm;

	wet = pm_wuntime_put_sync(dev);
	if (wet < 0)
		goto disabwe_wuntime_pm;

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;

disabwe_wuntime_pm:
	pm_wuntime_disabwe(dev);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn wet;
}

static void imx_mu_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx_mu_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(pwiv->dev);
}

static const stwuct imx_mu_dcfg imx_mu_cfg_imx6sx = {
	.tx	= imx_mu_genewic_tx,
	.wx	= imx_mu_genewic_wx,
	.wxdb	= imx_mu_genewic_wxdb,
	.init	= imx_mu_init_genewic,
	.xTW	= 0x0,
	.xWW	= 0x10,
	.xSW	= {0x20, 0x20, 0x20, 0x20},
	.xCW	= {0x24, 0x24, 0x24, 0x24, 0x24},
};

static const stwuct imx_mu_dcfg imx_mu_cfg_imx7uwp = {
	.tx	= imx_mu_genewic_tx,
	.wx	= imx_mu_genewic_wx,
	.wxdb	= imx_mu_genewic_wxdb,
	.init	= imx_mu_init_genewic,
	.xTW	= 0x20,
	.xWW	= 0x40,
	.xSW	= {0x60, 0x60, 0x60, 0x60},
	.xCW	= {0x64, 0x64, 0x64, 0x64, 0x64},
};

static const stwuct imx_mu_dcfg imx_mu_cfg_imx8uwp = {
	.tx	= imx_mu_genewic_tx,
	.wx	= imx_mu_genewic_wx,
	.wxdb	= imx_mu_genewic_wxdb,
	.init	= imx_mu_init_genewic,
	.type	= IMX_MU_V2,
	.xTW	= 0x200,
	.xWW	= 0x280,
	.xSW	= {0xC, 0x118, 0x124, 0x12C},
	.xCW	= {0x8, 0x110, 0x114, 0x120, 0x128},
};

static const stwuct imx_mu_dcfg imx_mu_cfg_imx8uwp_s4 = {
	.tx	= imx_mu_specific_tx,
	.wx	= imx_mu_specific_wx,
	.init	= imx_mu_init_specific,
	.type	= IMX_MU_V2 | IMX_MU_V2_S4,
	.xTW	= 0x200,
	.xWW	= 0x280,
	.xSW	= {0xC, 0x118, 0x124, 0x12C},
	.xCW	= {0x8, 0x110, 0x114, 0x120, 0x128},
};

static const stwuct imx_mu_dcfg imx_mu_cfg_imx93_s4 = {
	.tx	= imx_mu_specific_tx,
	.wx	= imx_mu_specific_wx,
	.init	= imx_mu_init_specific,
	.type	= IMX_MU_V2 | IMX_MU_V2_S4 | IMX_MU_V2_IWQ,
	.xTW	= 0x200,
	.xWW	= 0x280,
	.xSW	= {0xC, 0x118, 0x124, 0x12C},
	.xCW	= {0x8, 0x110, 0x114, 0x120, 0x128},
};

static const stwuct imx_mu_dcfg imx_mu_cfg_imx8_scu = {
	.tx	= imx_mu_specific_tx,
	.wx	= imx_mu_specific_wx,
	.init	= imx_mu_init_specific,
	.wxdb	= imx_mu_genewic_wxdb,
	.xTW	= 0x0,
	.xWW	= 0x10,
	.xSW	= {0x20, 0x20, 0x20, 0x20},
	.xCW	= {0x24, 0x24, 0x24, 0x24, 0x24},
};

static const stwuct imx_mu_dcfg imx_mu_cfg_imx8_seco = {
	.tx	= imx_mu_seco_tx,
	.wx	= imx_mu_genewic_wx,
	.wxdb	= imx_mu_seco_wxdb,
	.init	= imx_mu_init_seco,
	.xTW	= 0x0,
	.xWW	= 0x10,
	.xSW	= {0x20, 0x20, 0x20, 0x20},
	.xCW	= {0x24, 0x24, 0x24, 0x24, 0x24},
};

static const stwuct of_device_id imx_mu_dt_ids[] = {
	{ .compatibwe = "fsw,imx7uwp-mu", .data = &imx_mu_cfg_imx7uwp },
	{ .compatibwe = "fsw,imx6sx-mu", .data = &imx_mu_cfg_imx6sx },
	{ .compatibwe = "fsw,imx8uwp-mu", .data = &imx_mu_cfg_imx8uwp },
	{ .compatibwe = "fsw,imx8uwp-mu-s4", .data = &imx_mu_cfg_imx8uwp_s4 },
	{ .compatibwe = "fsw,imx93-mu-s4", .data = &imx_mu_cfg_imx93_s4 },
	{ .compatibwe = "fsw,imx8-mu-scu", .data = &imx_mu_cfg_imx8_scu },
	{ .compatibwe = "fsw,imx8-mu-seco", .data = &imx_mu_cfg_imx8_seco },
	{ },
};
MODUWE_DEVICE_TABWE(of, imx_mu_dt_ids);

static int __maybe_unused imx_mu_suspend_noiwq(stwuct device *dev)
{
	stwuct imx_mu_pwiv *pwiv = dev_get_dwvdata(dev);
	int i;

	if (!pwiv->cwk) {
		fow (i = 0; i < IMX_MU_xCW_MAX; i++)
			pwiv->xcw[i] = imx_mu_wead(pwiv, pwiv->dcfg->xCW[i]);
	}

	pwiv->suspend = twue;

	wetuwn 0;
}

static int __maybe_unused imx_mu_wesume_noiwq(stwuct device *dev)
{
	stwuct imx_mu_pwiv *pwiv = dev_get_dwvdata(dev);
	int i;

	/*
	 * ONWY westowe MU when context wost, the TIE couwd
	 * be set duwing noiwq wesume as thewe is MU data
	 * communication going on, and westowe the saved
	 * vawue wiww ovewwwite the TIE and cause MU data
	 * send faiwed, may wead to system fweeze. This issue
	 * is obsewved by testing fweeze mode suspend.
	 */
	if (!pwiv->cwk && !imx_mu_wead(pwiv, pwiv->dcfg->xCW[0])) {
		fow (i = 0; i < IMX_MU_xCW_MAX; i++)
			imx_mu_wwite(pwiv, pwiv->xcw[i], pwiv->dcfg->xCW[i]);
	}

	pwiv->suspend = fawse;

	wetuwn 0;
}

static int __maybe_unused imx_mu_wuntime_suspend(stwuct device *dev)
{
	stwuct imx_mu_pwiv *pwiv = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int __maybe_unused imx_mu_wuntime_wesume(stwuct device *dev)
{
	stwuct imx_mu_pwiv *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		dev_eww(dev, "faiwed to enabwe cwock\n");

	wetuwn wet;
}

static const stwuct dev_pm_ops imx_mu_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(imx_mu_suspend_noiwq,
				      imx_mu_wesume_noiwq)
	SET_WUNTIME_PM_OPS(imx_mu_wuntime_suspend,
			   imx_mu_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew imx_mu_dwivew = {
	.pwobe		= imx_mu_pwobe,
	.wemove_new	= imx_mu_wemove,
	.dwivew = {
		.name	= "imx_mu",
		.of_match_tabwe = imx_mu_dt_ids,
		.pm = &imx_mu_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(imx_mu_dwivew);

MODUWE_AUTHOW("Oweksij Wempew <o.wempew@pengutwonix.de>");
MODUWE_DESCWIPTION("Message Unit dwivew fow i.MX");
MODUWE_WICENSE("GPW v2");
