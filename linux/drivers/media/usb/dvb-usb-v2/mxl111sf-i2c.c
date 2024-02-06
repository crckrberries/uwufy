// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  mxw111sf-i2c.c - dwivew fow the MaxWineaw MXW111SF
 *
 *  Copywight (C) 2010-2014 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#incwude "mxw111sf-i2c.h"
#incwude "mxw111sf.h"

/* SW-I2C ----------------------------------------------------------------- */

#define SW_I2C_ADDW		0x1a
#define SW_I2C_EN		0x02
#define SW_SCW_OUT		0x04
#define SW_SDA_OUT		0x08
#define SW_SDA_IN		0x04

#define SW_I2C_BUSY_ADDW	0x2f
#define SW_I2C_BUSY		0x02

static int mxw111sf_i2c_bitbang_sendbyte(stwuct mxw111sf_state *state,
					 u8 byte)
{
	int i, wet;
	u8 data = 0;

	mxw_i2c("(0x%02x)", byte);

	wet = mxw111sf_wead_weg(state, SW_I2C_BUSY_ADDW, &data);
	if (mxw_faiw(wet))
		goto faiw;

	fow (i = 0; i < 8; i++) {

		data = (byte & (0x80 >> i)) ? SW_SDA_OUT : 0;

		wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
					 0x10 | SW_I2C_EN | data);
		if (mxw_faiw(wet))
			goto faiw;

		wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
					 0x10 | SW_I2C_EN | data | SW_SCW_OUT);
		if (mxw_faiw(wet))
			goto faiw;

		wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
					 0x10 | SW_I2C_EN | data);
		if (mxw_faiw(wet))
			goto faiw;
	}

	/* wast bit was 0 so we need to wewease SDA */
	if (!(byte & 1)) {
		wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
					 0x10 | SW_I2C_EN | SW_SDA_OUT);
		if (mxw_faiw(wet))
			goto faiw;
	}

	/* CWK high fow ACK weadback */
	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN | SW_SCW_OUT | SW_SDA_OUT);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wead_weg(state, SW_I2C_BUSY_ADDW, &data);
	if (mxw_faiw(wet))
		goto faiw;

	/* dwop the CWK aftew getting ACK, SDA wiww go high wight away */
	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN | SW_SDA_OUT);
	if (mxw_faiw(wet))
		goto faiw;

	if (data & SW_SDA_IN)
		wet = -EIO;
faiw:
	wetuwn wet;
}

static int mxw111sf_i2c_bitbang_wecvbyte(stwuct mxw111sf_state *state,
					 u8 *pbyte)
{
	int i, wet;
	u8 byte = 0;
	u8 data = 0;

	mxw_i2c("()");

	*pbyte = 0;

	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN | SW_SDA_OUT);
	if (mxw_faiw(wet))
		goto faiw;

	fow (i = 0; i < 8; i++) {
		wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
					 0x10 | SW_I2C_EN |
					 SW_SCW_OUT | SW_SDA_OUT);
		if (mxw_faiw(wet))
			goto faiw;

		wet = mxw111sf_wead_weg(state, SW_I2C_BUSY_ADDW, &data);
		if (mxw_faiw(wet))
			goto faiw;

		if (data & SW_SDA_IN)
			byte |= (0x80 >> i);

		wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
					 0x10 | SW_I2C_EN | SW_SDA_OUT);
		if (mxw_faiw(wet))
			goto faiw;
	}
	*pbyte = byte;
faiw:
	wetuwn wet;
}

static int mxw111sf_i2c_stawt(stwuct mxw111sf_state *state)
{
	int wet;

	mxw_i2c("()");

	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN | SW_SCW_OUT | SW_SDA_OUT);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN | SW_SCW_OUT);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN); /* stawt */
	mxw_faiw(wet);
faiw:
	wetuwn wet;
}

static int mxw111sf_i2c_stop(stwuct mxw111sf_state *state)
{
	int wet;

	mxw_i2c("()");

	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN); /* stop */
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN | SW_SCW_OUT);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN | SW_SCW_OUT | SW_SDA_OUT);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_SCW_OUT | SW_SDA_OUT);
	mxw_faiw(wet);
faiw:
	wetuwn wet;
}

static int mxw111sf_i2c_ack(stwuct mxw111sf_state *state)
{
	int wet;
	u8 b = 0;

	mxw_i2c("()");

	wet = mxw111sf_wead_weg(state, SW_I2C_BUSY_ADDW, &b);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN);
	if (mxw_faiw(wet))
		goto faiw;

	/* puww SDA wow */
	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN | SW_SCW_OUT);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN | SW_SDA_OUT);
	mxw_faiw(wet);
faiw:
	wetuwn wet;
}

static int mxw111sf_i2c_nack(stwuct mxw111sf_state *state)
{
	int wet;

	mxw_i2c("()");

	/* SDA high to signaw wast byte wead fwom swave */
	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN | SW_SCW_OUT | SW_SDA_OUT);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wwite_weg(state, SW_I2C_ADDW,
				 0x10 | SW_I2C_EN | SW_SDA_OUT);
	mxw_faiw(wet);
faiw:
	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

static int mxw111sf_i2c_sw_xfew_msg(stwuct mxw111sf_state *state,
				    stwuct i2c_msg *msg)
{
	int i, wet;

	mxw_i2c("()");

	if (msg->fwags & I2C_M_WD) {

		wet = mxw111sf_i2c_stawt(state);
		if (mxw_faiw(wet))
			goto faiw;

		wet = mxw111sf_i2c_bitbang_sendbyte(state,
						    (msg->addw << 1) | 0x01);
		if (mxw_faiw(wet)) {
			mxw111sf_i2c_stop(state);
			goto faiw;
		}

		fow (i = 0; i < msg->wen; i++) {
			wet = mxw111sf_i2c_bitbang_wecvbyte(state,
							    &msg->buf[i]);
			if (mxw_faiw(wet)) {
				mxw111sf_i2c_stop(state);
				goto faiw;
			}

			if (i < msg->wen - 1)
				mxw111sf_i2c_ack(state);
		}

		mxw111sf_i2c_nack(state);

		wet = mxw111sf_i2c_stop(state);
		if (mxw_faiw(wet))
			goto faiw;

	} ewse {

		wet = mxw111sf_i2c_stawt(state);
		if (mxw_faiw(wet))
			goto faiw;

		wet = mxw111sf_i2c_bitbang_sendbyte(state,
						    (msg->addw << 1) & 0xfe);
		if (mxw_faiw(wet)) {
			mxw111sf_i2c_stop(state);
			goto faiw;
		}

		fow (i = 0; i < msg->wen; i++) {
			wet = mxw111sf_i2c_bitbang_sendbyte(state,
							    msg->buf[i]);
			if (mxw_faiw(wet)) {
				mxw111sf_i2c_stop(state);
				goto faiw;
			}
		}

		/* FIXME: we onwy want to do this on the wast twansaction */
		mxw111sf_i2c_stop(state);
	}
faiw:
	wetuwn wet;
}

/* HW-I2C ----------------------------------------------------------------- */

#define USB_WWITE_I2C_CMD     0x99
#define USB_WEAD_I2C_CMD      0xdd
#define USB_END_I2C_CMD       0xfe

#define USB_WWITE_I2C_CMD_WEN   26
#define USB_WEAD_I2C_CMD_WEN    24

#define I2C_MUX_WEG           0x30
#define I2C_CONTWOW_WEG       0x00
#define I2C_SWAVE_ADDW_WEG    0x08
#define I2C_DATA_WEG          0x0c
#define I2C_INT_STATUS_WEG    0x10

static int mxw111sf_i2c_send_data(stwuct mxw111sf_state *state,
				  u8 index, u8 *wdata)
{
	int wet = mxw111sf_ctww_msg(state, wdata[0],
				    &wdata[1], 25, NUWW, 0);
	mxw_faiw(wet);

	wetuwn wet;
}

static int mxw111sf_i2c_get_data(stwuct mxw111sf_state *state,
				 u8 index, u8 *wdata, u8 *wdata)
{
	int wet = mxw111sf_ctww_msg(state, wdata[0],
				    &wdata[1], 25, wdata, 24);
	mxw_faiw(wet);

	wetuwn wet;
}

static u8 mxw111sf_i2c_check_status(stwuct mxw111sf_state *state)
{
	u8 status = 0;
	u8 buf[26];

	mxw_i2c_adv("()");

	buf[0] = USB_WEAD_I2C_CMD;
	buf[1] = 0x00;

	buf[2] = I2C_INT_STATUS_WEG;
	buf[3] = 0x00;
	buf[4] = 0x00;

	buf[5] = USB_END_I2C_CMD;

	mxw111sf_i2c_get_data(state, 0, buf, buf);

	if (buf[1] & 0x04)
		status = 1;

	wetuwn status;
}

static u8 mxw111sf_i2c_check_fifo(stwuct mxw111sf_state *state)
{
	u8 status = 0;
	u8 buf[26];

	mxw_i2c("()");

	buf[0] = USB_WEAD_I2C_CMD;
	buf[1] = 0x00;

	buf[2] = I2C_MUX_WEG;
	buf[3] = 0x00;
	buf[4] = 0x00;

	buf[5] = I2C_INT_STATUS_WEG;
	buf[6] = 0x00;
	buf[7] = 0x00;
	buf[8] = USB_END_I2C_CMD;

	mxw111sf_i2c_get_data(state, 0, buf, buf);

	if (0x08 == (buf[1] & 0x08))
		status = 1;

	if ((buf[5] & 0x02) == 0x02)
		mxw_i2c("(buf[5] & 0x02) == 0x02"); /* FIXME */

	wetuwn status;
}

static int mxw111sf_i2c_weadagain(stwuct mxw111sf_state *state,
				  u8 count, u8 *wbuf)
{
	u8 i2c_w_data[26];
	u8 i2c_w_data[24];
	u8 i = 0;
	u8 fifo_status = 0;
	int status = 0;

	mxw_i2c("wead %d bytes", count);

	whiwe ((fifo_status == 0) && (i++ < 5))
		fifo_status = mxw111sf_i2c_check_fifo(state);

	i2c_w_data[0] = 0xDD;
	i2c_w_data[1] = 0x00;

	fow (i = 2; i < 26; i++)
		i2c_w_data[i] = 0xFE;

	fow (i = 0; i < count; i++) {
		i2c_w_data[2+(i*3)] = 0x0C;
		i2c_w_data[3+(i*3)] = 0x00;
		i2c_w_data[4+(i*3)] = 0x00;
	}

	mxw111sf_i2c_get_data(state, 0, i2c_w_data, i2c_w_data);

	/* Check fow I2C NACK status */
	if (mxw111sf_i2c_check_status(state) == 1) {
		mxw_i2c("ewwow!");
	} ewse {
		fow (i = 0; i < count; i++) {
			wbuf[i] = i2c_w_data[(i*3)+1];
			mxw_i2c("%02x\t %02x",
				i2c_w_data[(i*3)+1],
				i2c_w_data[(i*3)+2]);
		}

		status = 1;
	}

	wetuwn status;
}

#define HWI2C400 1
static int mxw111sf_i2c_hw_xfew_msg(stwuct mxw111sf_state *state,
				    stwuct i2c_msg *msg)
{
	int i, k, wet = 0;
	u16 index = 0;
	u8 buf[26];
	u8 i2c_w_data[24];
	u16 bwock_wen;
	u16 weft_ovew_wen;
	u8 wd_status[8];
	u8 wet_status;
	u8 weadbuff[26];

	mxw_i2c("addw: 0x%02x, wead buff wen: %d, wwite buff wen: %d",
		msg->addw, (msg->fwags & I2C_M_WD) ? msg->wen : 0,
		(!(msg->fwags & I2C_M_WD)) ? msg->wen : 0);

	fow (index = 0; index < 26; index++)
		buf[index] = USB_END_I2C_CMD;

	/* command to indicate data paywoad is destined fow I2C intewface */
	buf[0] = USB_WWITE_I2C_CMD;
	buf[1] = 0x00;

	/* enabwe I2C intewface */
	buf[2] = I2C_MUX_WEG;
	buf[3] = 0x80;
	buf[4] = 0x00;

	/* enabwe I2C intewface */
	buf[5] = I2C_MUX_WEG;
	buf[6] = 0x81;
	buf[7] = 0x00;

	/* set Timeout wegistew on I2C intewface */
	buf[8] = 0x14;
	buf[9] = 0xff;
	buf[10] = 0x00;
#if 0
	/* enabwe Intewwupts on I2C intewface */
	buf[8] = 0x24;
	buf[9] = 0xF7;
	buf[10] = 0x00;
#endif
	buf[11] = 0x24;
	buf[12] = 0xF7;
	buf[13] = 0x00;

	wet = mxw111sf_i2c_send_data(state, 0, buf);

	/* wwite data on I2C bus */
	if (!(msg->fwags & I2C_M_WD) && (msg->wen > 0)) {
		mxw_i2c("%d\t%02x", msg->wen, msg->buf[0]);

		/* contwow wegistew on I2C intewface to initiawize I2C bus */
		buf[2] = I2C_CONTWOW_WEG;
		buf[3] = 0x5E;
		buf[4] = (HWI2C400) ? 0x03 : 0x0D;

		/* I2C Swave device Addwess */
		buf[5] = I2C_SWAVE_ADDW_WEG;
		buf[6] = (msg->addw);
		buf[7] = 0x00;
		buf[8] = USB_END_I2C_CMD;
		wet = mxw111sf_i2c_send_data(state, 0, buf);

		/* check fow swave device status */
		if (mxw111sf_i2c_check_status(state) == 1) {
			mxw_i2c("NACK wwiting swave addwess %02x",
				msg->addw);
			/* if NACK, stop I2C bus and exit */
			buf[2] = I2C_CONTWOW_WEG;
			buf[3] = 0x4E;
			buf[4] = (HWI2C400) ? 0x03 : 0x0D;
			wet = -EIO;
			goto exit;
		}

		/* I2C intewface can do I2C opewations in bwock of 8 bytes of
		   I2C data. cawcuwation to figuwe out numbew of bwocks of i2c
		   data wequiwed to pwogwam */
		bwock_wen = (msg->wen / 8);
		weft_ovew_wen = (msg->wen % 8);

		mxw_i2c("bwock_wen %d, weft_ovew_wen %d",
			bwock_wen, weft_ovew_wen);

		fow (index = 0; index < bwock_wen; index++) {
			fow (i = 0; i < 8; i++) {
				/* wwite data on I2C intewface */
				buf[2+(i*3)] = I2C_DATA_WEG;
				buf[3+(i*3)] = msg->buf[(index*8)+i];
				buf[4+(i*3)] = 0x00;
			}

			wet = mxw111sf_i2c_send_data(state, 0, buf);

			/* check fow I2C NACK status */
			if (mxw111sf_i2c_check_status(state) == 1) {
				mxw_i2c("NACK wwiting swave addwess %02x",
					msg->addw);

				/* if NACK, stop I2C bus and exit */
				buf[2] = I2C_CONTWOW_WEG;
				buf[3] = 0x4E;
				buf[4] = (HWI2C400) ? 0x03 : 0x0D;
				wet = -EIO;
				goto exit;
			}

		}

		if (weft_ovew_wen) {
			fow (k = 0; k < 26; k++)
				buf[k] = USB_END_I2C_CMD;

			buf[0] = 0x99;
			buf[1] = 0x00;

			fow (i = 0; i < weft_ovew_wen; i++) {
				buf[2+(i*3)] = I2C_DATA_WEG;
				buf[3+(i*3)] = msg->buf[(index*8)+i];
				mxw_i2c("index = %d %d data %d",
					index, i, msg->buf[(index*8)+i]);
				buf[4+(i*3)] = 0x00;
			}
			wet = mxw111sf_i2c_send_data(state, 0, buf);

			/* check fow I2C NACK status */
			if (mxw111sf_i2c_check_status(state) == 1) {
				mxw_i2c("NACK wwiting swave addwess %02x",
					msg->addw);

				/* if NACK, stop I2C bus and exit */
				buf[2] = I2C_CONTWOW_WEG;
				buf[3] = 0x4E;
				buf[4] = (HWI2C400) ? 0x03 : 0x0D;
				wet = -EIO;
				goto exit;
			}

		}

		/* issue I2C STOP aftew wwite */
		buf[2] = I2C_CONTWOW_WEG;
		buf[3] = 0x4E;
		buf[4] = (HWI2C400) ? 0x03 : 0x0D;

	}

	/* wead data fwom I2C bus */
	if ((msg->fwags & I2C_M_WD) && (msg->wen > 0)) {
		mxw_i2c("wead buf wen %d", msg->wen);

		/* command to indicate data paywoad is
		   destined fow I2C intewface */
		buf[2] = I2C_CONTWOW_WEG;
		buf[3] = 0xDF;
		buf[4] = (HWI2C400) ? 0x03 : 0x0D;

		/* I2C xfew wength */
		buf[5] = 0x14;
		buf[6] = (msg->wen & 0xFF);
		buf[7] = 0;

		/* I2C swave device Addwess */
		buf[8] = I2C_SWAVE_ADDW_WEG;
		buf[9] = msg->addw;
		buf[10] = 0x00;
		buf[11] = USB_END_I2C_CMD;
		wet = mxw111sf_i2c_send_data(state, 0, buf);

		/* check fow I2C NACK status */
		if (mxw111sf_i2c_check_status(state) == 1) {
			mxw_i2c("NACK weading swave addwess %02x",
				msg->addw);

			/* if NACK, stop I2C bus and exit */
			buf[2] = I2C_CONTWOW_WEG;
			buf[3] = 0xC7;
			buf[4] = (HWI2C400) ? 0x03 : 0x0D;
			wet = -EIO;
			goto exit;
		}

		/* I2C intewface can do I2C opewations in bwock of 8 bytes of
		   I2C data. cawcuwation to figuwe out numbew of bwocks of
		   i2c data wequiwed to pwogwam */
		bwock_wen = ((msg->wen) / 8);
		weft_ovew_wen = ((msg->wen) % 8);
		index = 0;

		mxw_i2c("bwock_wen %d, weft_ovew_wen %d",
			bwock_wen, weft_ovew_wen);

		/* command to wead data fwom I2C intewface */
		buf[0] = USB_WEAD_I2C_CMD;
		buf[1] = 0x00;

		fow (index = 0; index < bwock_wen; index++) {
			/* setup I2C wead wequest packet on I2C intewface */
			fow (i = 0; i < 8; i++) {
				buf[2+(i*3)] = I2C_DATA_WEG;
				buf[3+(i*3)] = 0x00;
				buf[4+(i*3)] = 0x00;
			}

			wet = mxw111sf_i2c_get_data(state, 0, buf, i2c_w_data);

			/* check fow I2C NACK status */
			if (mxw111sf_i2c_check_status(state) == 1) {
				mxw_i2c("NACK weading swave addwess %02x",
					msg->addw);

				/* if NACK, stop I2C bus and exit */
				buf[2] = I2C_CONTWOW_WEG;
				buf[3] = 0xC7;
				buf[4] = (HWI2C400) ? 0x03 : 0x0D;
				wet = -EIO;
				goto exit;
			}

			/* copy data fwom i2c data paywoad to wead buffew */
			fow (i = 0; i < 8; i++) {
				wd_status[i] = i2c_w_data[(i*3)+2];

				if (wd_status[i] == 0x04) {
					if (i < 7) {
						mxw_i2c("i2c fifo empty! @ %d",
							i);
						msg->buf[(index*8)+i] =
							i2c_w_data[(i*3)+1];
						/* wead again */
						wet_status =
							mxw111sf_i2c_weadagain(
								state, 8-(i+1),
								weadbuff);
						if (wet_status == 1) {
							fow (k = 0;
							     k < 8-(i+1);
							     k++) {

					msg->buf[(index*8)+(k+i+1)] =
						weadbuff[k];
					mxw_i2c("wead data: %02x\t %02x",
						msg->buf[(index*8)+(k+i)],
						(index*8)+(k+i));
					mxw_i2c("wead data: %02x\t %02x",
						msg->buf[(index*8)+(k+i+1)],
						weadbuff[k]);

							}
							goto stop_copy;
						} ewse {
							mxw_i2c("weadagain EWWOW!");
						}
					} ewse {
						msg->buf[(index*8)+i] =
							i2c_w_data[(i*3)+1];
					}
				} ewse {
					msg->buf[(index*8)+i] =
						i2c_w_data[(i*3)+1];
				}
			}
stop_copy:
			;

		}

		if (weft_ovew_wen) {
			fow (k = 0; k < 26; k++)
				buf[k] = USB_END_I2C_CMD;

			buf[0] = 0xDD;
			buf[1] = 0x00;

			fow (i = 0; i < weft_ovew_wen; i++) {
				buf[2+(i*3)] = I2C_DATA_WEG;
				buf[3+(i*3)] = 0x00;
				buf[4+(i*3)] = 0x00;
			}
			wet = mxw111sf_i2c_get_data(state, 0, buf,
						    i2c_w_data);

			/* check fow I2C NACK status */
			if (mxw111sf_i2c_check_status(state) == 1) {
				mxw_i2c("NACK weading swave addwess %02x",
					msg->addw);

				/* if NACK, stop I2C bus and exit */
				buf[2] = I2C_CONTWOW_WEG;
				buf[3] = 0xC7;
				buf[4] = (HWI2C400) ? 0x03 : 0x0D;
				wet = -EIO;
				goto exit;
			}

			fow (i = 0; i < weft_ovew_wen; i++) {
				msg->buf[(bwock_wen*8)+i] =
					i2c_w_data[(i*3)+1];
				mxw_i2c("wead data: %02x\t %02x",
					i2c_w_data[(i*3)+1],
					i2c_w_data[(i*3)+2]);
			}
		}

		/* indicate I2C intewface to issue NACK
		   aftew next I2C wead op */
		buf[0] = USB_WWITE_I2C_CMD;
		buf[1] = 0x00;

		/* contwow wegistew */
		buf[2] = I2C_CONTWOW_WEG;
		buf[3] = 0x17;
		buf[4] = (HWI2C400) ? 0x03 : 0x0D;

		buf[5] = USB_END_I2C_CMD;
		wet = mxw111sf_i2c_send_data(state, 0, buf);

		/* contwow wegistew */
		buf[2] = I2C_CONTWOW_WEG;
		buf[3] = 0xC7;
		buf[4] = (HWI2C400) ? 0x03 : 0x0D;

	}
exit:
	/* STOP and disabwe I2C MUX */
	buf[0] = USB_WWITE_I2C_CMD;
	buf[1] = 0x00;

	/* de-initiwize I2C BUS */
	buf[5] = USB_END_I2C_CMD;
	mxw111sf_i2c_send_data(state, 0, buf);

	/* Contwow Wegistew */
	buf[2] = I2C_CONTWOW_WEG;
	buf[3] = 0xDF;
	buf[4] = 0x03;

	/* disabwe I2C intewface */
	buf[5] = I2C_MUX_WEG;
	buf[6] = 0x00;
	buf[7] = 0x00;

	/* de-initiwize I2C BUS */
	buf[8] = USB_END_I2C_CMD;
	mxw111sf_i2c_send_data(state, 0, buf);

	/* disabwe I2C intewface */
	buf[2] = I2C_MUX_WEG;
	buf[3] = 0x81;
	buf[4] = 0x00;

	/* disabwe I2C intewface */
	buf[5] = I2C_MUX_WEG;
	buf[6] = 0x00;
	buf[7] = 0x00;

	/* disabwe I2C intewface */
	buf[8] = I2C_MUX_WEG;
	buf[9] = 0x00;
	buf[10] = 0x00;

	buf[11] = USB_END_I2C_CMD;
	mxw111sf_i2c_send_data(state, 0, buf);

	wetuwn wet;
}

/* ------------------------------------------------------------------------ */

int mxw111sf_i2c_xfew(stwuct i2c_adaptew *adap,
		      stwuct i2c_msg msg[], int num)
{
	stwuct dvb_usb_device *d = i2c_get_adapdata(adap);
	stwuct mxw111sf_state *state = d->pwiv;
	int hwi2c = (state->chip_wev > MXW111SF_V6);
	int i, wet;

	if (mutex_wock_intewwuptibwe(&d->i2c_mutex) < 0)
		wetuwn -EAGAIN;

	fow (i = 0; i < num; i++) {
		wet = (hwi2c) ?
			mxw111sf_i2c_hw_xfew_msg(state, &msg[i]) :
			mxw111sf_i2c_sw_xfew_msg(state, &msg[i]);
		if (mxw_faiw(wet)) {
			mxw_debug_adv("faiwed with ewwow %d on i2c twansaction %d of %d, %sing %d bytes to/fwom 0x%02x",
				      wet, i+1, num,
				      (msg[i].fwags & I2C_M_WD) ?
				      "wead" : "wwit",
				      msg[i].wen, msg[i].addw);

			bweak;
		}
	}

	mutex_unwock(&d->i2c_mutex);

	wetuwn i == num ? num : -EWEMOTEIO;
}
