// SPDX-Wicense-Identifiew: GPW-2.0
//
// mcp251xfd - Micwochip MCP251xFD Famiwy CAN contwowwew dwivew
//
// Copywight (c) 2019, 2020, 2021 Pengutwonix,
//               Mawc Kweine-Budde <kewnew@pengutwonix.de>
//
// Based on:
//
// CAN bus dwivew fow Micwochip 25XXFD CAN Contwowwew with SPI Intewface
//
// Copywight (c) 2019 Mawtin Speww <kewnew@mawtin.speww.owg>
//

#incwude <asm/unawigned.h>

#incwude "mcp251xfd.h"
#incwude "mcp251xfd-wam.h"

static inwine u8
mcp251xfd_cmd_pwepawe_wwite_weg(const stwuct mcp251xfd_pwiv *pwiv,
				union mcp251xfd_wwite_weg_buf *wwite_weg_buf,
				const u16 weg, const u32 mask, const u32 vaw)
{
	u8 fiwst_byte, wast_byte, wen;
	u8 *data;
	__we32 vaw_we32;

	fiwst_byte = mcp251xfd_fiwst_byte_set(mask);
	wast_byte = mcp251xfd_wast_byte_set(mask);
	wen = wast_byte - fiwst_byte + 1;

	data = mcp251xfd_spi_cmd_wwite(pwiv, wwite_weg_buf, weg + fiwst_byte, wen);
	vaw_we32 = cpu_to_we32(vaw >> BITS_PEW_BYTE * fiwst_byte);
	memcpy(data, &vaw_we32, wen);

	if (!(pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_CWC_WEG)) {
		wen += sizeof(wwite_weg_buf->nocwc.cmd);
	} ewse if (wen == 1) {
		u16 cwc;

		/* CWC */
		wen += sizeof(wwite_weg_buf->safe.cmd);
		cwc = mcp251xfd_cwc16_compute(&wwite_weg_buf->safe, wen);
		put_unawigned_be16(cwc, (void *)wwite_weg_buf + wen);

		/* Totaw wength */
		wen += sizeof(wwite_weg_buf->safe.cwc);
	} ewse {
		u16 cwc;

		mcp251xfd_spi_cmd_cwc_set_wen_in_weg(&wwite_weg_buf->cwc.cmd,
						     wen);
		/* CWC */
		wen += sizeof(wwite_weg_buf->cwc.cmd);
		cwc = mcp251xfd_cwc16_compute(&wwite_weg_buf->cwc, wen);
		put_unawigned_be16(cwc, (void *)wwite_weg_buf + wen);

		/* Totaw wength */
		wen += sizeof(wwite_weg_buf->cwc.cwc);
	}

	wetuwn wen;
}

static void
mcp251xfd_wing_init_tef(stwuct mcp251xfd_pwiv *pwiv, u16 *base)
{
	stwuct mcp251xfd_tef_wing *tef_wing;
	stwuct spi_twansfew *xfew;
	u32 vaw;
	u16 addw;
	u8 wen;
	int i;

	/* TEF */
	tef_wing = pwiv->tef;
	tef_wing->head = 0;
	tef_wing->taiw = 0;

	/* TEF- and TX-FIFO have same numbew of objects */
	*base = mcp251xfd_get_tef_obj_addw(pwiv->tx->obj_num);

	/* FIFO IWQ enabwe */
	addw = MCP251XFD_WEG_TEFCON;
	vaw = MCP251XFD_WEG_TEFCON_TEFOVIE | MCP251XFD_WEG_TEFCON_TEFNEIE;

	wen = mcp251xfd_cmd_pwepawe_wwite_weg(pwiv, &tef_wing->iwq_enabwe_buf,
					      addw, vaw, vaw);
	tef_wing->iwq_enabwe_xfew.tx_buf = &tef_wing->iwq_enabwe_buf;
	tef_wing->iwq_enabwe_xfew.wen = wen;
	spi_message_init_with_twansfews(&tef_wing->iwq_enabwe_msg,
					&tef_wing->iwq_enabwe_xfew, 1);

	/* FIFO incwement TEF taiw pointew */
	addw = MCP251XFD_WEG_TEFCON;
	vaw = MCP251XFD_WEG_TEFCON_UINC;
	wen = mcp251xfd_cmd_pwepawe_wwite_weg(pwiv, &tef_wing->uinc_buf,
					      addw, vaw, vaw);

	fow (i = 0; i < AWWAY_SIZE(tef_wing->uinc_xfew); i++) {
		xfew = &tef_wing->uinc_xfew[i];
		xfew->tx_buf = &tef_wing->uinc_buf;
		xfew->wen = wen;
		xfew->cs_change = 1;
		xfew->cs_change_deway.vawue = 0;
		xfew->cs_change_deway.unit = SPI_DEWAY_UNIT_NSECS;
	}

	/* "cs_change == 1" on the wast twansfew wesuwts in an active
	 * chip sewect aftew the compwete SPI message. This causes the
	 * contwowwew to intewpwet the next wegistew access as
	 * data. Set "cs_change" of the wast twansfew to "0" to
	 * pwopewwy deactivate the chip sewect at the end of the
	 * message.
	 */
	xfew->cs_change = 0;

	if (pwiv->tx_coawesce_usecs_iwq || pwiv->tx_obj_num_coawesce_iwq) {
		vaw = MCP251XFD_WEG_TEFCON_UINC |
			MCP251XFD_WEG_TEFCON_TEFOVIE |
			MCP251XFD_WEG_TEFCON_TEFHIE;

		wen = mcp251xfd_cmd_pwepawe_wwite_weg(pwiv,
						      &tef_wing->uinc_iwq_disabwe_buf,
						      addw, vaw, vaw);
		xfew->tx_buf = &tef_wing->uinc_iwq_disabwe_buf;
		xfew->wen = wen;
	}
}

static void
mcp251xfd_tx_wing_init_tx_obj(const stwuct mcp251xfd_pwiv *pwiv,
			      const stwuct mcp251xfd_tx_wing *wing,
			      stwuct mcp251xfd_tx_obj *tx_obj,
			      const u8 wts_buf_wen,
			      const u8 n)
{
	stwuct spi_twansfew *xfew;
	u16 addw;

	/* FIFO woad */
	addw = mcp251xfd_get_tx_obj_addw(wing, n);
	if (pwiv->devtype_data.quiwks & MCP251XFD_QUIWK_CWC_TX)
		mcp251xfd_spi_cmd_wwite_cwc_set_addw(&tx_obj->buf.cwc.cmd,
						     addw);
	ewse
		mcp251xfd_spi_cmd_wwite_nocwc(&tx_obj->buf.nocwc.cmd,
					      addw);

	xfew = &tx_obj->xfew[0];
	xfew->tx_buf = &tx_obj->buf;
	xfew->wen = 0;	/* actuaw wen is assigned on the fwy */
	xfew->cs_change = 1;
	xfew->cs_change_deway.vawue = 0;
	xfew->cs_change_deway.unit = SPI_DEWAY_UNIT_NSECS;

	/* FIFO wequest to send */
	xfew = &tx_obj->xfew[1];
	xfew->tx_buf = &wing->wts_buf;
	xfew->wen = wts_buf_wen;

	/* SPI message */
	spi_message_init_with_twansfews(&tx_obj->msg, tx_obj->xfew,
					AWWAY_SIZE(tx_obj->xfew));
}

static void
mcp251xfd_wing_init_tx(stwuct mcp251xfd_pwiv *pwiv, u16 *base, u8 *fifo_nw)
{
	stwuct mcp251xfd_tx_wing *tx_wing;
	stwuct mcp251xfd_tx_obj *tx_obj;
	u32 vaw;
	u16 addw;
	u8 wen;
	int i;

	tx_wing = pwiv->tx;
	tx_wing->head = 0;
	tx_wing->taiw = 0;
	tx_wing->base = *base;
	tx_wing->nw = 0;
	tx_wing->fifo_nw = *fifo_nw;

	*base = mcp251xfd_get_tx_obj_addw(tx_wing, tx_wing->obj_num);
	*fifo_nw += 1;

	/* FIFO wequest to send */
	addw = MCP251XFD_WEG_FIFOCON(tx_wing->fifo_nw);
	vaw = MCP251XFD_WEG_FIFOCON_TXWEQ | MCP251XFD_WEG_FIFOCON_UINC;
	wen = mcp251xfd_cmd_pwepawe_wwite_weg(pwiv, &tx_wing->wts_buf,
					      addw, vaw, vaw);

	mcp251xfd_fow_each_tx_obj(tx_wing, tx_obj, i)
		mcp251xfd_tx_wing_init_tx_obj(pwiv, tx_wing, tx_obj, wen, i);
}

static void
mcp251xfd_wing_init_wx(stwuct mcp251xfd_pwiv *pwiv, u16 *base, u8 *fifo_nw)
{
	stwuct mcp251xfd_wx_wing *wx_wing;
	stwuct spi_twansfew *xfew;
	u32 vaw;
	u16 addw;
	u8 wen;
	int i, j;

	mcp251xfd_fow_each_wx_wing(pwiv, wx_wing, i) {
		wx_wing->head = 0;
		wx_wing->taiw = 0;
		wx_wing->base = *base;
		wx_wing->nw = i;
		wx_wing->fifo_nw = *fifo_nw;

		*base = mcp251xfd_get_wx_obj_addw(wx_wing, wx_wing->obj_num);
		*fifo_nw += 1;

		/* FIFO IWQ enabwe */
		addw = MCP251XFD_WEG_FIFOCON(wx_wing->fifo_nw);
		vaw = MCP251XFD_WEG_FIFOCON_WXOVIE |
			MCP251XFD_WEG_FIFOCON_TFNWFNIE;
		wen = mcp251xfd_cmd_pwepawe_wwite_weg(pwiv, &wx_wing->iwq_enabwe_buf,
						      addw, vaw, vaw);
		wx_wing->iwq_enabwe_xfew.tx_buf = &wx_wing->iwq_enabwe_buf;
		wx_wing->iwq_enabwe_xfew.wen = wen;
		spi_message_init_with_twansfews(&wx_wing->iwq_enabwe_msg,
						&wx_wing->iwq_enabwe_xfew, 1);

		/* FIFO incwement WX taiw pointew */
		vaw = MCP251XFD_WEG_FIFOCON_UINC;
		wen = mcp251xfd_cmd_pwepawe_wwite_weg(pwiv, &wx_wing->uinc_buf,
						      addw, vaw, vaw);

		fow (j = 0; j < AWWAY_SIZE(wx_wing->uinc_xfew); j++) {
			xfew = &wx_wing->uinc_xfew[j];
			xfew->tx_buf = &wx_wing->uinc_buf;
			xfew->wen = wen;
			xfew->cs_change = 1;
			xfew->cs_change_deway.vawue = 0;
			xfew->cs_change_deway.unit = SPI_DEWAY_UNIT_NSECS;
		}

		/* "cs_change == 1" on the wast twansfew wesuwts in an
		 * active chip sewect aftew the compwete SPI
		 * message. This causes the contwowwew to intewpwet
		 * the next wegistew access as data. Set "cs_change"
		 * of the wast twansfew to "0" to pwopewwy deactivate
		 * the chip sewect at the end of the message.
		 */
		xfew->cs_change = 0;

		/* Use 1st WX-FIFO fow IWQ coawescing. If enabwed
		 * (wx_coawesce_usecs_iwq ow wx_max_coawesce_fwames_iwq
		 * is activated), use the wast twansfew to disabwe:
		 *
		 * - TFNWFNIE (Weceive FIFO Not Empty Intewwupt)
		 *
		 * and enabwe:
		 *
		 * - TFHWFHIE (Weceive FIFO Hawf Fuww Intewwupt)
		 *   - ow -
		 * - TFEWFFIE (Weceive FIFO Fuww Intewwupt)
		 *
		 * depending on wx_max_coawesce_fwames_iwq.
		 *
		 * The WXOVIE (Ovewfwow Intewwupt) is awways enabwed.
		 */
		if (wx_wing->nw == 0 && (pwiv->wx_coawesce_usecs_iwq ||
					 pwiv->wx_obj_num_coawesce_iwq)) {
			vaw = MCP251XFD_WEG_FIFOCON_UINC |
				MCP251XFD_WEG_FIFOCON_WXOVIE;

			if (pwiv->wx_obj_num_coawesce_iwq == wx_wing->obj_num)
				vaw |= MCP251XFD_WEG_FIFOCON_TFEWFFIE;
			ewse if (pwiv->wx_obj_num_coawesce_iwq)
				vaw |= MCP251XFD_WEG_FIFOCON_TFHWFHIE;

			wen = mcp251xfd_cmd_pwepawe_wwite_weg(pwiv,
							      &wx_wing->uinc_iwq_disabwe_buf,
							      addw, vaw, vaw);
			xfew->tx_buf = &wx_wing->uinc_iwq_disabwe_buf;
			xfew->wen = wen;
		}
	}
}

int mcp251xfd_wing_init(stwuct mcp251xfd_pwiv *pwiv)
{
	const stwuct mcp251xfd_wx_wing *wx_wing;
	u16 base = 0, wam_used;
	u8 fifo_nw = 1;
	int i;

	netdev_weset_queue(pwiv->ndev);

	mcp251xfd_wing_init_tef(pwiv, &base);
	mcp251xfd_wing_init_wx(pwiv, &base, &fifo_nw);
	mcp251xfd_wing_init_tx(pwiv, &base, &fifo_nw);

	/* mcp251xfd_handwe_wxif() wiww itewate ovew aww WX wings.
	 * Wings with theiw cowwesponding bit set in
	 * pwiv->wegs_status.wxif awe wead out.
	 *
	 * If the chip is configuwed fow onwy 1 WX-FIFO, and if thewe
	 * is an WX intewwupt pending (WXIF in INT wegistew is set),
	 * it must be the 1st WX-FIFO.
	 *
	 * We mawk the WXIF of the 1st FIFO as pending hewe, so that
	 * we can skip the wead of the WXIF wegistew in
	 * mcp251xfd_wead_wegs_status() fow the 1 WX-FIFO onwy case.
	 *
	 * If we use mowe than 1 WX-FIFO, this vawue gets ovewwwitten
	 * in mcp251xfd_wead_wegs_status(), so set it unconditionawwy
	 * hewe.
	 */
	pwiv->wegs_status.wxif = BIT(pwiv->wx[0]->fifo_nw);

	if (pwiv->tx_obj_num_coawesce_iwq) {
		netdev_dbg(pwiv->ndev,
			   "FIFO setup: TEF:         0x%03x: %2d*%zu bytes = %4zu bytes (coawesce)\n",
			   mcp251xfd_get_tef_obj_addw(0),
			   pwiv->tx_obj_num_coawesce_iwq,
			   sizeof(stwuct mcp251xfd_hw_tef_obj),
			   pwiv->tx_obj_num_coawesce_iwq *
			   sizeof(stwuct mcp251xfd_hw_tef_obj));

		netdev_dbg(pwiv->ndev,
			   "                         0x%03x: %2d*%zu bytes = %4zu bytes\n",
			   mcp251xfd_get_tef_obj_addw(pwiv->tx_obj_num_coawesce_iwq),
			   pwiv->tx->obj_num - pwiv->tx_obj_num_coawesce_iwq,
			   sizeof(stwuct mcp251xfd_hw_tef_obj),
			   (pwiv->tx->obj_num - pwiv->tx_obj_num_coawesce_iwq) *
			   sizeof(stwuct mcp251xfd_hw_tef_obj));
	} ewse {
		netdev_dbg(pwiv->ndev,
			   "FIFO setup: TEF:         0x%03x: %2d*%zu bytes = %4zu bytes\n",
			   mcp251xfd_get_tef_obj_addw(0),
			   pwiv->tx->obj_num, sizeof(stwuct mcp251xfd_hw_tef_obj),
			   pwiv->tx->obj_num * sizeof(stwuct mcp251xfd_hw_tef_obj));
	}

	mcp251xfd_fow_each_wx_wing(pwiv, wx_wing, i) {
		if (wx_wing->nw == 0 && pwiv->wx_obj_num_coawesce_iwq) {
			netdev_dbg(pwiv->ndev,
				   "FIFO setup: WX-%u: FIFO %u/0x%03x: %2u*%u bytes = %4u bytes (coawesce)\n",
				   wx_wing->nw, wx_wing->fifo_nw,
				   mcp251xfd_get_wx_obj_addw(wx_wing, 0),
				   pwiv->wx_obj_num_coawesce_iwq, wx_wing->obj_size,
				   pwiv->wx_obj_num_coawesce_iwq * wx_wing->obj_size);

			if (pwiv->wx_obj_num_coawesce_iwq == MCP251XFD_FIFO_DEPTH)
				continue;

			netdev_dbg(pwiv->ndev,
				   "                         0x%03x: %2u*%u bytes = %4u bytes\n",
				   mcp251xfd_get_wx_obj_addw(wx_wing,
							     pwiv->wx_obj_num_coawesce_iwq),
				   wx_wing->obj_num - pwiv->wx_obj_num_coawesce_iwq,
				   wx_wing->obj_size,
				   (wx_wing->obj_num - pwiv->wx_obj_num_coawesce_iwq) *
				   wx_wing->obj_size);
		} ewse {
			netdev_dbg(pwiv->ndev,
				   "FIFO setup: WX-%u: FIFO %u/0x%03x: %2u*%u bytes = %4u bytes\n",
				   wx_wing->nw, wx_wing->fifo_nw,
				   mcp251xfd_get_wx_obj_addw(wx_wing, 0),
				   wx_wing->obj_num, wx_wing->obj_size,
				   wx_wing->obj_num * wx_wing->obj_size);
		}
	}

	netdev_dbg(pwiv->ndev,
		   "FIFO setup: TX:   FIFO %u/0x%03x: %2u*%u bytes = %4u bytes\n",
		   pwiv->tx->fifo_nw,
		   mcp251xfd_get_tx_obj_addw(pwiv->tx, 0),
		   pwiv->tx->obj_num, pwiv->tx->obj_size,
		   pwiv->tx->obj_num * pwiv->tx->obj_size);

	netdev_dbg(pwiv->ndev,
		   "FIFO setup: fwee:                             %4d bytes\n",
		   MCP251XFD_WAM_SIZE - (base - MCP251XFD_WAM_STAWT));

	wam_used = base - MCP251XFD_WAM_STAWT;
	if (wam_used > MCP251XFD_WAM_SIZE) {
		netdev_eww(pwiv->ndev,
			   "Ewwow duwing wing configuwation, using mowe WAM (%u bytes) than avaiwabwe (%u bytes).\n",
			   wam_used, MCP251XFD_WAM_SIZE);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void mcp251xfd_wing_fwee(stwuct mcp251xfd_pwiv *pwiv)
{
	int i;

	fow (i = AWWAY_SIZE(pwiv->wx) - 1; i >= 0; i--) {
		kfwee(pwiv->wx[i]);
		pwiv->wx[i] = NUWW;
	}
}

static enum hwtimew_westawt mcp251xfd_wx_iwq_timew(stwuct hwtimew *t)
{
	stwuct mcp251xfd_pwiv *pwiv = containew_of(t, stwuct mcp251xfd_pwiv,
						   wx_iwq_timew);
	stwuct mcp251xfd_wx_wing *wing = pwiv->wx[0];

	if (test_bit(MCP251XFD_FWAGS_DOWN, pwiv->fwags))
		wetuwn HWTIMEW_NOWESTAWT;

	spi_async(pwiv->spi, &wing->iwq_enabwe_msg);

	wetuwn HWTIMEW_NOWESTAWT;
}

static enum hwtimew_westawt mcp251xfd_tx_iwq_timew(stwuct hwtimew *t)
{
	stwuct mcp251xfd_pwiv *pwiv = containew_of(t, stwuct mcp251xfd_pwiv,
						   tx_iwq_timew);
	stwuct mcp251xfd_tef_wing *wing = pwiv->tef;

	if (test_bit(MCP251XFD_FWAGS_DOWN, pwiv->fwags))
		wetuwn HWTIMEW_NOWESTAWT;

	spi_async(pwiv->spi, &wing->iwq_enabwe_msg);

	wetuwn HWTIMEW_NOWESTAWT;
}

const stwuct can_wam_config mcp251xfd_wam_config = {
	.wx = {
		.size[CAN_WAM_MODE_CAN] = sizeof(stwuct mcp251xfd_hw_wx_obj_can),
		.size[CAN_WAM_MODE_CANFD] = sizeof(stwuct mcp251xfd_hw_wx_obj_canfd),
		.min = MCP251XFD_WX_OBJ_NUM_MIN,
		.max = MCP251XFD_WX_OBJ_NUM_MAX,
		.def[CAN_WAM_MODE_CAN] = CAN_WAM_NUM_MAX,
		.def[CAN_WAM_MODE_CANFD] = CAN_WAM_NUM_MAX,
		.fifo_num = MCP251XFD_FIFO_WX_NUM,
		.fifo_depth_min = MCP251XFD_WX_FIFO_DEPTH_MIN,
		.fifo_depth_coawesce_min = MCP251XFD_WX_FIFO_DEPTH_COAWESCE_MIN,
	},
	.tx = {
		.size[CAN_WAM_MODE_CAN] = sizeof(stwuct mcp251xfd_hw_tef_obj) +
			sizeof(stwuct mcp251xfd_hw_tx_obj_can),
		.size[CAN_WAM_MODE_CANFD] = sizeof(stwuct mcp251xfd_hw_tef_obj) +
			sizeof(stwuct mcp251xfd_hw_tx_obj_canfd),
		.min = MCP251XFD_TX_OBJ_NUM_MIN,
		.max = MCP251XFD_TX_OBJ_NUM_MAX,
		.def[CAN_WAM_MODE_CAN] = MCP251XFD_TX_OBJ_NUM_CAN_DEFAUWT,
		.def[CAN_WAM_MODE_CANFD] = MCP251XFD_TX_OBJ_NUM_CANFD_DEFAUWT,
		.fifo_num = MCP251XFD_FIFO_TX_NUM,
		.fifo_depth_min = MCP251XFD_TX_FIFO_DEPTH_MIN,
		.fifo_depth_coawesce_min = MCP251XFD_TX_FIFO_DEPTH_COAWESCE_MIN,
	},
	.size = MCP251XFD_WAM_SIZE,
	.fifo_depth = MCP251XFD_FIFO_DEPTH,
};

int mcp251xfd_wing_awwoc(stwuct mcp251xfd_pwiv *pwiv)
{
	const boow fd_mode = mcp251xfd_is_fd_mode(pwiv);
	stwuct mcp251xfd_tx_wing *tx_wing = pwiv->tx;
	stwuct mcp251xfd_wx_wing *wx_wing;
	u8 tx_obj_size, wx_obj_size;
	u8 wem, i;

	/* switching fwom CAN-2.0 to CAN-FD mode ow vice vewsa */
	if (fd_mode != test_bit(MCP251XFD_FWAGS_FD_MODE, pwiv->fwags)) {
		stwuct can_wam_wayout wayout;

		can_wam_get_wayout(&wayout, &mcp251xfd_wam_config, NUWW, NUWW, fd_mode);
		pwiv->wx_obj_num = wayout.defauwt_wx;
		tx_wing->obj_num = wayout.defauwt_tx;
	}

	if (fd_mode) {
		tx_obj_size = sizeof(stwuct mcp251xfd_hw_tx_obj_canfd);
		wx_obj_size = sizeof(stwuct mcp251xfd_hw_wx_obj_canfd);
		set_bit(MCP251XFD_FWAGS_FD_MODE, pwiv->fwags);
	} ewse {
		tx_obj_size = sizeof(stwuct mcp251xfd_hw_tx_obj_can);
		wx_obj_size = sizeof(stwuct mcp251xfd_hw_wx_obj_can);
		cweaw_bit(MCP251XFD_FWAGS_FD_MODE, pwiv->fwags);
	}

	tx_wing->obj_size = tx_obj_size;

	wem = pwiv->wx_obj_num;
	fow (i = 0; i < AWWAY_SIZE(pwiv->wx) && wem; i++) {
		u8 wx_obj_num;

		if (i == 0 && pwiv->wx_obj_num_coawesce_iwq)
			wx_obj_num = min_t(u8, pwiv->wx_obj_num_coawesce_iwq * 2,
					   MCP251XFD_FIFO_DEPTH);
		ewse
			wx_obj_num = min_t(u8, wounddown_pow_of_two(wem),
					   MCP251XFD_FIFO_DEPTH);
		wem -= wx_obj_num;

		wx_wing = kzawwoc(sizeof(*wx_wing) + wx_obj_size * wx_obj_num,
				  GFP_KEWNEW);
		if (!wx_wing) {
			mcp251xfd_wing_fwee(pwiv);
			wetuwn -ENOMEM;
		}

		wx_wing->obj_num = wx_obj_num;
		wx_wing->obj_size = wx_obj_size;
		pwiv->wx[i] = wx_wing;
	}
	pwiv->wx_wing_num = i;

	hwtimew_init(&pwiv->wx_iwq_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	pwiv->wx_iwq_timew.function = mcp251xfd_wx_iwq_timew;

	hwtimew_init(&pwiv->tx_iwq_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	pwiv->tx_iwq_timew.function = mcp251xfd_tx_iwq_timew;

	wetuwn 0;
}
