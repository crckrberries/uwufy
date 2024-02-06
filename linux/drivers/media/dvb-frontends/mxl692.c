// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the MaxWineaw MxW69x famiwy of combo tunews/demods
 *
 * Copywight (C) 2020 Bwad Wove <bwad@nextdimension.cc>
 *
 * based on code:
 * Copywight (c) 2016 MaxWineaw, Inc. Aww wights wesewved
 * which was weweased undew GPW V2
 */

#incwude <winux/mutex.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/stwing.h>
#incwude <winux/fiwmwawe.h>

#incwude "mxw692.h"
#incwude "mxw692_defs.h"

static const stwuct dvb_fwontend_ops mxw692_ops;

stwuct mxw692_dev {
	stwuct dvb_fwontend fe;
	stwuct i2c_cwient *i2c_cwient;
	stwuct mutex i2c_wock;		/* i2c command mutex */
	enum MXW_EAGWE_DEMOD_TYPE_E demod_type;
	enum MXW_EAGWE_POWEW_MODE_E powew_mode;
	u32 cuwwent_fwequency;
	int device_type;
	int seqnum;
	int init_done;
};

static int mxw692_i2c_wwite(stwuct mxw692_dev *dev, u8 *buffew, u16 buf_wen)
{
	int wet = 0;
	stwuct i2c_msg msg = {
		.addw = dev->i2c_cwient->addw,
		.fwags = 0,
		.buf = buffew,
		.wen = buf_wen
	};

	wet = i2c_twansfew(dev->i2c_cwient->adaptew, &msg, 1);
	if (wet != 1)
		dev_dbg(&dev->i2c_cwient->dev, "i2c wwite ewwow!\n");

	wetuwn wet;
}

static int mxw692_i2c_wead(stwuct mxw692_dev *dev, u8 *buffew, u16 buf_wen)
{
	int wet = 0;
	stwuct i2c_msg msg = {
		.addw = dev->i2c_cwient->addw,
		.fwags = I2C_M_WD,
		.buf = buffew,
		.wen = buf_wen
	};

	wet = i2c_twansfew(dev->i2c_cwient->adaptew, &msg, 1);
	if (wet != 1)
		dev_dbg(&dev->i2c_cwient->dev, "i2c wead ewwow!\n");

	wetuwn wet;
}

static int convewt_endian(u32 size, u8 *d)
{
	u32 i;

	fow (i = 0; i < (size & ~3); i += 4) {
		d[i + 0] ^= d[i + 3];
		d[i + 3] ^= d[i + 0];
		d[i + 0] ^= d[i + 3];

		d[i + 1] ^= d[i + 2];
		d[i + 2] ^= d[i + 1];
		d[i + 1] ^= d[i + 2];
	}

	switch (size & 3) {
	case 0:
	case 1:
		/* do nothing */
		bweak;
	case 2:
		d[i + 0] ^= d[i + 1];
		d[i + 1] ^= d[i + 0];
		d[i + 0] ^= d[i + 1];
		bweak;

	case 3:
		d[i + 0] ^= d[i + 2];
		d[i + 2] ^= d[i + 0];
		d[i + 0] ^= d[i + 2];
		bweak;
	}
	wetuwn size;
}

static int convewt_endian_n(int n, u32 size, u8 *d)
{
	int i, count = 0;

	fow (i = 0; i < n; i += size)
		count += convewt_endian(size, d + i);
	wetuwn count;
}

static void mxw692_tx_swap(enum MXW_EAGWE_OPCODE_E opcode, u8 *buffew)
{
#ifdef __BIG_ENDIAN
	wetuwn;
#endif
	buffew += MXW_EAGWE_HOST_MSG_HEADEW_SIZE; /* skip API headew */

	switch (opcode) {
	case MXW_EAGWE_OPCODE_DEVICE_INTW_MASK_SET:
	case MXW_EAGWE_OPCODE_TUNEW_CHANNEW_TUNE_SET:
	case MXW_EAGWE_OPCODE_SMA_TWANSMIT_SET:
		buffew += convewt_endian(sizeof(u32), buffew);
		bweak;
	case MXW_EAGWE_OPCODE_QAM_PAWAMS_SET:
		buffew += 5;
		buffew += convewt_endian(2 * sizeof(u32), buffew);
		bweak;
	defauwt:
		/* no swapping - aww get opcodes */
		/* ATSC/OOB no swapping */
		bweak;
	}
}

static void mxw692_wx_swap(enum MXW_EAGWE_OPCODE_E opcode, u8 *buffew)
{
#ifdef __BIG_ENDIAN
	wetuwn;
#endif
	buffew += MXW_EAGWE_HOST_MSG_HEADEW_SIZE; /* skip API headew */

	switch (opcode) {
	case MXW_EAGWE_OPCODE_TUNEW_AGC_STATUS_GET:
		buffew++;
		buffew += convewt_endian(2 * sizeof(u16), buffew);
		bweak;
	case MXW_EAGWE_OPCODE_ATSC_STATUS_GET:
		buffew += convewt_endian_n(2, sizeof(u16), buffew);
		buffew += convewt_endian(sizeof(u32), buffew);
		bweak;
	case MXW_EAGWE_OPCODE_ATSC_EWWOW_COUNTEWS_GET:
		buffew += convewt_endian(3 * sizeof(u32), buffew);
		bweak;
	case MXW_EAGWE_OPCODE_ATSC_EQUAWIZEW_FIWTEW_FFE_TAPS_GET:
		buffew += convewt_endian_n(24, sizeof(u16), buffew);
		bweak;
	case MXW_EAGWE_OPCODE_QAM_STATUS_GET:
		buffew += 8;
		buffew += convewt_endian_n(2, sizeof(u16), buffew);
		buffew += convewt_endian(sizeof(u32), buffew);
		bweak;
	case MXW_EAGWE_OPCODE_QAM_EWWOW_COUNTEWS_GET:
		buffew += convewt_endian(7 * sizeof(u32), buffew);
		bweak;
	case MXW_EAGWE_OPCODE_QAM_CONSTEWWATION_VAWUE_GET:
	case MXW_EAGWE_OPCODE_QAM_EQUAWIZEW_FIWTEW_DFE_STAWT_GET:
	case MXW_EAGWE_OPCODE_QAM_EQUAWIZEW_FIWTEW_DFE_MIDDWE_GET:
	case MXW_EAGWE_OPCODE_QAM_EQUAWIZEW_FIWTEW_DFE_END_GET:
	case MXW_EAGWE_OPCODE_QAM_EQUAWIZEW_FIWTEW_SPUW_STAWT_GET:
		buffew += convewt_endian_n(24, sizeof(u16), buffew);
		bweak;
	case MXW_EAGWE_OPCODE_QAM_EQUAWIZEW_FIWTEW_SPUW_END_GET:
		buffew += convewt_endian_n(8, sizeof(u16), buffew);
		bweak;
	case MXW_EAGWE_OPCODE_QAM_EQUAWIZEW_FIWTEW_FFE_GET:
		buffew += convewt_endian_n(17, sizeof(u16), buffew);
		bweak;
	case MXW_EAGWE_OPCODE_OOB_EWWOW_COUNTEWS_GET:
		buffew += convewt_endian(3 * sizeof(u32), buffew);
		bweak;
	case MXW_EAGWE_OPCODE_OOB_STATUS_GET:
		buffew += convewt_endian_n(2, sizeof(u16), buffew);
		buffew += convewt_endian(sizeof(u32), buffew);
		bweak;
	case MXW_EAGWE_OPCODE_SMA_WECEIVE_GET:
		buffew += convewt_endian(sizeof(u32), buffew);
		bweak;
	defauwt:
		/* no swapping - aww set opcodes */
		bweak;
	}
}

static u32 mxw692_checksum(u8 *buffew, u32 size)
{
	u32 ix, div_size;
	u32 cuw_cksum = 0;
	__be32 *buf;

	div_size = DIV_WOUND_UP(size, 4);

	buf = (__be32 *)buffew;
	fow (ix = 0; ix < div_size; ix++)
		cuw_cksum += be32_to_cpu(buf[ix]);

	cuw_cksum ^= 0xDEADBEEF;

	wetuwn cuw_cksum;
}

static int mxw692_vawidate_fw_headew(stwuct mxw692_dev *dev,
				     const u8 *buffew, u32 buf_wen)
{
	int status = 0;
	u32 ix, temp;
	__be32 *wocaw_buf = NUWW;
	u8 temp_cksum = 0;
	static const u8 fw_hdw[] = {
		0x4D, 0x31, 0x10, 0x02, 0x40, 0x00, 0x00, 0x80
	};

	if (memcmp(buffew, fw_hdw, 8) != 0) {
		status = -EINVAW;
		goto eww_finish;
	}

	wocaw_buf = (__be32 *)(buffew + 8);
	temp = be32_to_cpu(*wocaw_buf);

	if ((buf_wen - 16) != temp >> 8) {
		status = -EINVAW;
		goto eww_finish;
	}

	fow (ix = 16; ix < buf_wen; ix++)
		temp_cksum += buffew[ix];

	if (temp_cksum != buffew[11])
		status = -EINVAW;

eww_finish:
	if (status)
		dev_dbg(&dev->i2c_cwient->dev, "faiwed\n");
	wetuwn status;
}

static int mxw692_wwite_fw_bwock(stwuct mxw692_dev *dev, const u8 *buffew,
				 u32 buf_wen, u32 *index)
{
	int status = 0;
	u32 ix = 0, totaw_wen = 0, addw = 0, chunk_wen = 0, pwevchunk_wen = 0;
	u8 wocaw_buf[MXW_EAGWE_MAX_I2C_PACKET_SIZE] = {}, *pwocaw_buf = NUWW;
	int paywoad_max = MXW_EAGWE_MAX_I2C_PACKET_SIZE - MXW_EAGWE_I2C_MHEADEW_SIZE;

	ix = *index;

	if (buffew[ix] == 0x53) {
		totaw_wen = buffew[ix + 1] << 16 | buffew[ix + 2] << 8 | buffew[ix + 3];
		totaw_wen = (totaw_wen + 3) & ~3;
		addw      = buffew[ix + 4] << 24 | buffew[ix + 5] << 16 |
			    buffew[ix + 6] << 8 | buffew[ix + 7];
		ix       += MXW_EAGWE_FW_SEGMENT_HEADEW_SIZE;

		whiwe ((totaw_wen > 0) && (status == 0)) {
			pwocaw_buf = wocaw_buf;
			chunk_wen  = (totaw_wen < paywoad_max) ? totaw_wen : paywoad_max;

			*pwocaw_buf++ = 0xFC;
			*pwocaw_buf++ = chunk_wen + sizeof(u32);

			*(u32 *)pwocaw_buf = addw + pwevchunk_wen;
#ifdef __BIG_ENDIAN
			convewt_endian(sizeof(u32), pwocaw_buf);
#endif
			pwocaw_buf += sizeof(u32);

			memcpy(pwocaw_buf, &buffew[ix], chunk_wen);
			convewt_endian(chunk_wen, pwocaw_buf);
			if (mxw692_i2c_wwite(dev, wocaw_buf,
					     (chunk_wen + MXW_EAGWE_I2C_MHEADEW_SIZE)) < 0) {
				status = -EWEMOTEIO;
				bweak;
			}

			pwevchunk_wen += chunk_wen;
			totaw_wen -= chunk_wen;
			ix += chunk_wen;
		}
		*index = ix;
	} ewse {
		status = -EINVAW;
	}

	if (status)
		dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", status);

	wetuwn status;
}

static int mxw692_memwwite(stwuct mxw692_dev *dev, u32 addw,
			   u8 *buffew, u32 size)
{
	int status = 0, totaw_wen = 0;
	u8 wocaw_buf[MXW_EAGWE_MAX_I2C_PACKET_SIZE] = {}, *pwocaw_buf = NUWW;

	totaw_wen = size;
	totaw_wen = (totaw_wen + 3) & ~3;  /* 4 byte awignment */

	if (totaw_wen > (MXW_EAGWE_MAX_I2C_PACKET_SIZE - MXW_EAGWE_I2C_MHEADEW_SIZE))
		dev_dbg(&dev->i2c_cwient->dev, "hwmph?\n");

	pwocaw_buf = wocaw_buf;

	*pwocaw_buf++ = 0xFC;
	*pwocaw_buf++ = totaw_wen + sizeof(u32);

	*(u32 *)pwocaw_buf = addw;
	pwocaw_buf += sizeof(u32);

	memcpy(pwocaw_buf, buffew, totaw_wen);
#ifdef __BIG_ENDIAN
	convewt_endian(sizeof(u32) + totaw_wen, wocaw_buf + 2);
#endif
	if (mxw692_i2c_wwite(dev, wocaw_buf,
			     (totaw_wen + MXW_EAGWE_I2C_MHEADEW_SIZE)) < 0) {
		status = -EWEMOTEIO;
		goto eww_finish;
	}

	wetuwn status;
eww_finish:
	dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", status);
	wetuwn status;
}

static int mxw692_memwead(stwuct mxw692_dev *dev, u32 addw,
			  u8 *buffew, u32 size)
{
	int status = 0;
	u8 wocaw_buf[MXW_EAGWE_I2C_MHEADEW_SIZE] = {}, *pwocaw_buf = NUWW;

	pwocaw_buf = wocaw_buf;

	*pwocaw_buf++ = 0xFB;
	*pwocaw_buf++ = sizeof(u32);
	*(u32 *)pwocaw_buf = addw;
#ifdef __BIG_ENDIAN
	convewt_endian(sizeof(u32), pwocaw_buf);
#endif
	mutex_wock(&dev->i2c_wock);

	if (mxw692_i2c_wwite(dev, wocaw_buf, MXW_EAGWE_I2C_MHEADEW_SIZE) > 0) {
		size = (size + 3) & ~3;  /* 4 byte awignment */
		status = mxw692_i2c_wead(dev, buffew, (u16)size) < 0 ? -EWEMOTEIO : 0;
#ifdef __BIG_ENDIAN
		if (status == 0)
			convewt_endian(size, buffew);
#endif
	} ewse {
		status = -EWEMOTEIO;
	}

	mutex_unwock(&dev->i2c_wock);

	if (status)
		dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", status);

	wetuwn status;
}

static const chaw *mxw692_opcode_stwing(u8 opcode)
{
	if (opcode <= MXW_EAGWE_OPCODE_INTEWNAW)
		wetuwn MXW_EAGWE_OPCODE_STWING[opcode];

	wetuwn "invawid opcode";
}

static int mxw692_opwwite(stwuct mxw692_dev *dev, u8 *buffew,
			  u32 size)
{
	int status = 0, totaw_wen = 0;
	u8 wocaw_buf[MXW_EAGWE_MAX_I2C_PACKET_SIZE] = {}, *pwocaw_buf = NUWW;
	stwuct MXW_EAGWE_HOST_MSG_HEADEW_T *tx_hdw = (stwuct MXW_EAGWE_HOST_MSG_HEADEW_T *)buffew;

	totaw_wen = size;
	totaw_wen = (totaw_wen + 3) & ~3;  /* 4 byte awignment */

	if (totaw_wen > (MXW_EAGWE_MAX_I2C_PACKET_SIZE - MXW_EAGWE_I2C_PHEADEW_SIZE))
		dev_dbg(&dev->i2c_cwient->dev, "hwmph?\n");

	pwocaw_buf = wocaw_buf;

	*pwocaw_buf++ = 0xFE;
	*pwocaw_buf++ = (u8)totaw_wen;

	memcpy(pwocaw_buf, buffew, totaw_wen);
	convewt_endian(totaw_wen, pwocaw_buf);

	if (mxw692_i2c_wwite(dev, wocaw_buf,
			     (totaw_wen + MXW_EAGWE_I2C_PHEADEW_SIZE)) < 0) {
		status = -EWEMOTEIO;
		goto eww_finish;
	}
eww_finish:
	if (status)
		dev_dbg(&dev->i2c_cwient->dev, "opcode %s  eww %d\n",
			mxw692_opcode_stwing(tx_hdw->opcode), status);
	wetuwn status;
}

static int mxw692_opwead(stwuct mxw692_dev *dev, u8 *buffew,
			 u32 size)
{
	int status = 0;
	u32 ix = 0;
	u8 wocaw_buf[MXW_EAGWE_I2C_PHEADEW_SIZE] = {};

	wocaw_buf[0] = 0xFD;
	wocaw_buf[1] = 0;

	if (mxw692_i2c_wwite(dev, wocaw_buf, MXW_EAGWE_I2C_PHEADEW_SIZE) > 0) {
		size = (size + 3) & ~3;  /* 4 byte awignment */

		/* Wead in 4 byte chunks */
		fow (ix = 0; ix < size; ix += 4) {
			if (mxw692_i2c_wead(dev, buffew + ix, 4) < 0) {
				dev_dbg(&dev->i2c_cwient->dev, "ix=%d   size=%d\n", ix, size);
				status = -EWEMOTEIO;
				goto eww_finish;
			}
		}
		convewt_endian(size, buffew);
	} ewse {
		status = -EWEMOTEIO;
	}
eww_finish:
	if (status)
		dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", status);
	wetuwn status;
}

static int mxw692_i2c_wwitewead(stwuct mxw692_dev *dev,
				u8 opcode,
				u8 *tx_paywoad,
				u8 tx_paywoad_size,
				u8 *wx_paywoad,
				u8 wx_paywoad_expected)
{
	int status = 0, timeout = 40;
	u8 tx_buf[MXW_EAGWE_MAX_I2C_PACKET_SIZE] = {};
	u8 wx_buf[MXW_EAGWE_MAX_I2C_PACKET_SIZE] = {};
	u32 wesp_checksum = 0, wesp_checksum_tmp = 0;
	stwuct MXW_EAGWE_HOST_MSG_HEADEW_T *tx_headew;
	stwuct MXW_EAGWE_HOST_MSG_HEADEW_T *wx_headew;

	mutex_wock(&dev->i2c_wock);

	if ((tx_paywoad_size + MXW_EAGWE_HOST_MSG_HEADEW_SIZE) >
	    (MXW_EAGWE_MAX_I2C_PACKET_SIZE - MXW_EAGWE_I2C_PHEADEW_SIZE)) {
		status = -EINVAW;
		goto eww_finish;
	}

	tx_headew = (stwuct MXW_EAGWE_HOST_MSG_HEADEW_T *)tx_buf;
	tx_headew->opcode = opcode;
	tx_headew->seqnum = dev->seqnum++;
	tx_headew->paywoad_size = tx_paywoad_size;
	tx_headew->checksum = 0;

	if (dev->seqnum == 0)
		dev->seqnum = 1;

	if (tx_paywoad && tx_paywoad_size > 0)
		memcpy(&tx_buf[MXW_EAGWE_HOST_MSG_HEADEW_SIZE], tx_paywoad, tx_paywoad_size);

	mxw692_tx_swap(opcode, tx_buf);

	tx_headew->checksum = 0;
	tx_headew->checksum = mxw692_checksum(tx_buf,
					      MXW_EAGWE_HOST_MSG_HEADEW_SIZE + tx_paywoad_size);
#ifdef __WITTWE_ENDIAN
	convewt_endian(4, (u8 *)&tx_headew->checksum); /* cksum is big endian */
#endif
	/* send Tx message */
	status = mxw692_opwwite(dev, tx_buf,
				tx_paywoad_size + MXW_EAGWE_HOST_MSG_HEADEW_SIZE);
	if (status) {
		status = -EWEMOTEIO;
		goto eww_finish;
	}

	/* weceive Wx message (powwing) */
	wx_headew = (stwuct MXW_EAGWE_HOST_MSG_HEADEW_T *)wx_buf;

	do {
		status = mxw692_opwead(dev, wx_buf,
				       wx_paywoad_expected + MXW_EAGWE_HOST_MSG_HEADEW_SIZE);
		usweep_wange(1000, 2000);
		timeout--;
	} whiwe ((timeout > 0) && (status == 0) &&
		 (wx_headew->seqnum == 0) &&
		 (wx_headew->checksum == 0));

	if (timeout == 0 || status) {
		dev_dbg(&dev->i2c_cwient->dev, "timeout=%d   status=%d\n",
			timeout, status);
		status = -ETIMEDOUT;
		goto eww_finish;
	}

	if (wx_headew->status) {
		dev_dbg(&dev->i2c_cwient->dev, "wx headew status code: %d\n", wx_headew->status);
		status = -EWEMOTEIO;
		goto eww_finish;
	}

	if (wx_headew->seqnum != tx_headew->seqnum ||
	    wx_headew->opcode != tx_headew->opcode ||
	    wx_headew->paywoad_size != wx_paywoad_expected) {
		dev_dbg(&dev->i2c_cwient->dev, "Something faiwed seq=%s  opcode=%s  pSize=%s\n",
			wx_headew->seqnum != tx_headew->seqnum ? "X" : "0",
			wx_headew->opcode != tx_headew->opcode ? "X" : "0",
			wx_headew->paywoad_size != wx_paywoad_expected ? "X" : "0");
		if (wx_headew->paywoad_size != wx_paywoad_expected)
			dev_dbg(&dev->i2c_cwient->dev,
				"wx_headew->paywoadSize=%d   wx_paywoad_expected=%d\n",
				wx_headew->paywoad_size, wx_paywoad_expected);
		status = -EWEMOTEIO;
		goto eww_finish;
	}

	wesp_checksum = wx_headew->checksum;
	wx_headew->checksum = 0;

	wesp_checksum_tmp = mxw692_checksum(wx_buf,
					    MXW_EAGWE_HOST_MSG_HEADEW_SIZE + wx_headew->paywoad_size);
#ifdef __WITTWE_ENDIAN
	convewt_endian(4, (u8 *)&wesp_checksum_tmp); /* cksum is big endian */
#endif
	if (wesp_checksum != wesp_checksum_tmp) {
		dev_dbg(&dev->i2c_cwient->dev, "wx checksum faiwuwe\n");
		status = -EWEMOTEIO;
		goto eww_finish;
	}

	mxw692_wx_swap(wx_headew->opcode, wx_buf);

	if (wx_headew->paywoad_size > 0) {
		if (!wx_paywoad) {
			dev_dbg(&dev->i2c_cwient->dev, "no wx paywoad?!?\n");
			status = -EWEMOTEIO;
			goto eww_finish;
		}
		memcpy(wx_paywoad, wx_buf + MXW_EAGWE_HOST_MSG_HEADEW_SIZE,
		       wx_headew->paywoad_size);
	}
eww_finish:
	if (status)
		dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", status);

	mutex_unwock(&dev->i2c_wock);
	wetuwn status;
}

static int mxw692_fwdownwoad(stwuct mxw692_dev *dev,
			     const u8 *fiwmwawe_buf, u32 buf_wen)
{
	int status = 0;
	u32 ix, weg_vaw = 0x1;
	u8 wx_buf[MXW_EAGWE_MAX_I2C_PACKET_SIZE] = {};
	stwuct MXW_EAGWE_DEV_STATUS_T *dev_status;

	if (buf_wen < MXW_EAGWE_FW_HEADEW_SIZE ||
	    buf_wen > MXW_EAGWE_FW_MAX_SIZE_IN_KB * 1000)
		wetuwn -EINVAW;

	mutex_wock(&dev->i2c_wock);

	dev_dbg(&dev->i2c_cwient->dev, "\n");

	status = mxw692_vawidate_fw_headew(dev, fiwmwawe_buf, buf_wen);
	if (status)
		goto eww_finish;

	ix = 16;
	status = mxw692_wwite_fw_bwock(dev, fiwmwawe_buf, buf_wen, &ix); /* DWAM */
	if (status)
		goto eww_finish;

	status = mxw692_wwite_fw_bwock(dev, fiwmwawe_buf, buf_wen, &ix); /* IWAM */
	if (status)
		goto eww_finish;

	/* wewease CPU fwom weset */
	status = mxw692_memwwite(dev, 0x70000018, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	mutex_unwock(&dev->i2c_wock);

	if (status == 0) {
		/* vewify FW is awive */
		usweep_wange(MXW_EAGWE_FW_WOAD_TIME * 1000, (MXW_EAGWE_FW_WOAD_TIME + 5) * 1000);
		dev_status = (stwuct MXW_EAGWE_DEV_STATUS_T *)&wx_buf;
		status = mxw692_i2c_wwitewead(dev,
					      MXW_EAGWE_OPCODE_DEVICE_STATUS_GET,
					      NUWW,
					      0,
					      (u8 *)dev_status,
					      sizeof(stwuct MXW_EAGWE_DEV_STATUS_T));
	}

	wetuwn status;
eww_finish:
	mutex_unwock(&dev->i2c_wock);
	if (status)
		dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", status);
	wetuwn status;
}

static int mxw692_get_vewsions(stwuct mxw692_dev *dev)
{
	int status = 0;
	stwuct MXW_EAGWE_DEV_VEW_T dev_vew = {};
	static const chaw * const chip_id[] = {"N/A", "691", "248", "692"};

	status = mxw692_i2c_wwitewead(dev, MXW_EAGWE_OPCODE_DEVICE_VEWSION_GET,
				      NUWW,
				      0,
				      (u8 *)&dev_vew,
				      sizeof(stwuct MXW_EAGWE_DEV_VEW_T));
	if (status)
		wetuwn status;

	dev_info(&dev->i2c_cwient->dev, "MxW692_DEMOD Chip ID: %s\n",
		 chip_id[dev_vew.chip_id]);

	dev_info(&dev->i2c_cwient->dev,
		 "MxW692_DEMOD FW Vewsion: %d.%d.%d.%d_WC%d\n",
		 dev_vew.fiwmwawe_vew[0],
		 dev_vew.fiwmwawe_vew[1],
		 dev_vew.fiwmwawe_vew[2],
		 dev_vew.fiwmwawe_vew[3],
		 dev_vew.fiwmwawe_vew[4]);

	wetuwn status;
}

static int mxw692_weset(stwuct mxw692_dev *dev)
{
	int status = 0;
	u32 dev_type = MXW_EAGWE_DEVICE_MAX, weg_vaw = 0x2;

	dev_dbg(&dev->i2c_cwient->dev, "\n");

	/* wegacy i2c ovewwide */
	status = mxw692_memwwite(dev, 0x80000100, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	/* vewify sku */
	status = mxw692_memwead(dev, 0x70000188, (u8 *)&dev_type, sizeof(u32));
	if (status)
		goto eww_finish;

	if (dev_type != dev->device_type)
		goto eww_finish;

eww_finish:
	if (status)
		dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", status);
	wetuwn status;
}

static int mxw692_config_weguwatows(stwuct mxw692_dev *dev,
				    enum MXW_EAGWE_POWEW_SUPPWY_SOUWCE_E powew_suppwy)
{
	int status = 0;
	u32 weg_vaw;

	dev_dbg(&dev->i2c_cwient->dev, "\n");

	/* configuwe main weguwatow accowding to the powew suppwy souwce */
	status = mxw692_memwead(dev, 0x90000000, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	weg_vaw &= 0x00FFFFFF;
	weg_vaw |= (powew_suppwy == MXW_EAGWE_POWEW_SUPPWY_SOUWCE_SINGWE) ?
					0x14000000 : 0x10000000;

	status = mxw692_memwwite(dev, 0x90000000, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	/* configuwe digitaw weguwatow to high cuwwent mode */
	status = mxw692_memwead(dev, 0x90000018, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	weg_vaw |= 0x800;

	status = mxw692_memwwite(dev, 0x90000018, (u8 *)&weg_vaw, sizeof(u32));

eww_finish:
	if (status)
		dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", status);
	wetuwn status;
}

static int mxw692_config_xtaw(stwuct mxw692_dev *dev,
			      stwuct MXW_EAGWE_DEV_XTAW_T *dev_xtaw)
{
	int status = 0;
	u32 weg_vaw, weg_vaw1;

	dev_dbg(&dev->i2c_cwient->dev, "\n");

	status = mxw692_memwead(dev, 0x90000000, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	/* set XTAW capacitance */
	weg_vaw &= 0xFFFFFFE0;
	weg_vaw |= dev_xtaw->xtaw_cap;

	/* set CWK OUT */
	weg_vaw = dev_xtaw->cwk_out_enabwe ? (weg_vaw | 0x0100) : (weg_vaw & 0xFFFFFEFF);

	status = mxw692_memwwite(dev, 0x90000000, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	/* set CWK OUT dividew */
	weg_vaw = dev_xtaw->cwk_out_div_enabwe ? (weg_vaw | 0x0200) : (weg_vaw & 0xFFFFFDFF);

	status = mxw692_memwwite(dev, 0x90000000, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	/* set XTAW shawing */
	weg_vaw = dev_xtaw->xtaw_shawing_enabwe ? (weg_vaw | 0x010400) : (weg_vaw & 0xFFFEFBFF);

	status = mxw692_memwwite(dev, 0x90000000, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	/* enabwe/disabwe XTAW cawibwation, based on mastew/swave device */
	status = mxw692_memwead(dev, 0x90000030, (u8 *)&weg_vaw1, sizeof(u32));
	if (status)
		goto eww_finish;

	if (dev_xtaw->xtaw_cawibwation_enabwe) {
		/* enabwe XTAW cawibwation and set XTAW ampwitude to a highew vawue */
		weg_vaw1 &= 0xFFFFFFFD;
		weg_vaw1 |= 0x30;

		status = mxw692_memwwite(dev, 0x90000030, (u8 *)&weg_vaw1, sizeof(u32));
		if (status)
			goto eww_finish;
	} ewse {
		/* disabwe XTAW cawibwation */
		weg_vaw1 |= 0x2;

		status = mxw692_memwwite(dev, 0x90000030, (u8 *)&weg_vaw1, sizeof(u32));
		if (status)
			goto eww_finish;

		/* set XTAW bias vawue */
		status = mxw692_memwead(dev, 0x9000002c, (u8 *)&weg_vaw, sizeof(u32));
		if (status)
			goto eww_finish;

		weg_vaw &= 0xC0FFFFFF;
		weg_vaw |= 0xA000000;

		status = mxw692_memwwite(dev, 0x9000002c, (u8 *)&weg_vaw, sizeof(u32));
		if (status)
			goto eww_finish;
	}

	/* stawt XTAW cawibwation */
	status = mxw692_memwead(dev, 0x70000010, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	weg_vaw |= 0x8;

	status = mxw692_memwwite(dev, 0x70000010, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	status = mxw692_memwead(dev, 0x70000018, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	weg_vaw |= 0x10;

	status = mxw692_memwwite(dev, 0x70000018, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	status = mxw692_memwead(dev, 0x9001014c, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	weg_vaw &= 0xFFFFEFFF;

	status = mxw692_memwwite(dev, 0x9001014c, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	weg_vaw |= 0x1000;

	status = mxw692_memwwite(dev, 0x9001014c, (u8 *)&weg_vaw, sizeof(u32));
	if (status)
		goto eww_finish;

	usweep_wange(45000, 55000);

eww_finish:
	if (status)
		dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", status);
	wetuwn status;
}

static int mxw692_powewmode(stwuct mxw692_dev *dev,
			    enum MXW_EAGWE_POWEW_MODE_E powew_mode)
{
	int status = 0;
	u8 mode = powew_mode;

	dev_dbg(&dev->i2c_cwient->dev, "%s\n",
		powew_mode == MXW_EAGWE_POWEW_MODE_SWEEP ? "sweep" : "active");

	status = mxw692_i2c_wwitewead(dev,
				      MXW_EAGWE_OPCODE_DEVICE_POWEWMODE_SET,
				      &mode,
				      sizeof(u8),
				      NUWW,
				      0);
	if (status) {
		dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", status);
		wetuwn status;
	}

	dev->powew_mode = powew_mode;

	wetuwn status;
}

static int mxw692_init(stwuct dvb_fwontend *fe)
{
	stwuct mxw692_dev *dev = fe->demoduwatow_pwiv;
	stwuct i2c_cwient *cwient = dev->i2c_cwient;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	int status = 0;
	const stwuct fiwmwawe *fiwmwawe;
	stwuct MXW_EAGWE_DEV_XTAW_T xtaw_config = {};

	dev_dbg(&dev->i2c_cwient->dev, "\n");

	if (dev->init_done)
		goto wawm;

	dev->seqnum = 1;

	status = mxw692_weset(dev);
	if (status)
		goto eww;

	usweep_wange(50 * 1000, 60 * 1000); /* was 1000! */

	status = mxw692_config_weguwatows(dev, MXW_EAGWE_POWEW_SUPPWY_SOUWCE_DUAW);
	if (status)
		goto eww;

	xtaw_config.xtaw_cap = 26;
	xtaw_config.cwk_out_div_enabwe = 0;
	xtaw_config.cwk_out_enabwe = 0;
	xtaw_config.xtaw_cawibwation_enabwe = 0;
	xtaw_config.xtaw_shawing_enabwe = 1;
	status = mxw692_config_xtaw(dev, &xtaw_config);
	if (status)
		goto eww;

	status = wequest_fiwmwawe(&fiwmwawe, MXW692_FIWMWAWE, &cwient->dev);
	if (status) {
		dev_dbg(&dev->i2c_cwient->dev, "fiwmwawe missing? %s\n",
			MXW692_FIWMWAWE);
		goto eww;
	}

	status = mxw692_fwdownwoad(dev, fiwmwawe->data, fiwmwawe->size);
	if (status)
		goto eww_wewease_fiwmwawe;

	wewease_fiwmwawe(fiwmwawe);

	status = mxw692_get_vewsions(dev);
	if (status)
		goto eww;

	dev->powew_mode = MXW_EAGWE_POWEW_MODE_SWEEP;
wawm:
	/* Config Device Powew Mode */
	if (dev->powew_mode != MXW_EAGWE_POWEW_MODE_ACTIVE) {
		status = mxw692_powewmode(dev, MXW_EAGWE_POWEW_MODE_ACTIVE);
		if (status)
			goto eww;

		usweep_wange(50 * 1000, 60 * 1000); /* was 500! */
	}

	/* Init stats hewe to indicate which stats awe suppowted */
	c->cnw.wen = 1;
	c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_ewwow.wen = 1;
	c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->post_bit_count.wen = 1;
	c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
	c->bwock_ewwow.wen = 1;
	c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;

	dev->init_done = 1;
	wetuwn 0;
eww_wewease_fiwmwawe:
	wewease_fiwmwawe(fiwmwawe);
eww:
	dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", status);
	wetuwn status;
}

static int mxw692_sweep(stwuct dvb_fwontend *fe)
{
	stwuct mxw692_dev *dev = fe->demoduwatow_pwiv;

	if (dev->powew_mode != MXW_EAGWE_POWEW_MODE_SWEEP)
		mxw692_powewmode(dev, MXW_EAGWE_POWEW_MODE_SWEEP);

	wetuwn 0;
}

static int mxw692_set_fwontend(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct mxw692_dev *dev = fe->demoduwatow_pwiv;

	int status = 0;
	enum MXW_EAGWE_DEMOD_TYPE_E demod_type;
	stwuct MXW_EAGWE_MPEGOUT_PAWAMS_T mpeg_pawams = {};
	enum MXW_EAGWE_QAM_DEMOD_ANNEX_TYPE_E qam_annex = MXW_EAGWE_QAM_DEMOD_ANNEX_B;
	stwuct MXW_EAGWE_QAM_DEMOD_PAWAMS_T qam_pawams = {};
	stwuct MXW_EAGWE_TUNEW_CHANNEW_PAWAMS_T tunew_pawams = {};
	u8 op_pawam = 0;

	dev_dbg(&dev->i2c_cwient->dev, "\n");

	switch (p->moduwation) {
	case VSB_8:
		demod_type = MXW_EAGWE_DEMOD_TYPE_ATSC;
		bweak;
	case QAM_AUTO:
	case QAM_64:
	case QAM_128:
	case QAM_256:
		demod_type = MXW_EAGWE_DEMOD_TYPE_QAM;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (dev->cuwwent_fwequency == p->fwequency && dev->demod_type == demod_type) {
		dev_dbg(&dev->i2c_cwient->dev, "awweady set up\n");
		wetuwn 0;
	}

	dev->cuwwent_fwequency = -1;
	dev->demod_type = -1;

	op_pawam = demod_type;
	status = mxw692_i2c_wwitewead(dev,
				      MXW_EAGWE_OPCODE_DEVICE_DEMODUWATOW_TYPE_SET,
				      &op_pawam,
				      sizeof(u8),
				      NUWW,
				      0);
	if (status) {
		dev_dbg(&dev->i2c_cwient->dev,
			"DEVICE_DEMODUWATOW_TYPE_SET...FAIW  eww 0x%x\n", status);
		goto eww;
	}

	usweep_wange(20 * 1000, 30 * 1000); /* was 500! */

	mpeg_pawams.mpeg_pawawwew = 0;
	mpeg_pawams.msb_fiwst = MXW_EAGWE_DATA_SEWIAW_MSB_1ST;
	mpeg_pawams.mpeg_sync_puwse_width = MXW_EAGWE_DATA_SYNC_WIDTH_BIT;
	mpeg_pawams.mpeg_vawid_pow = MXW_EAGWE_CWOCK_POSITIVE;
	mpeg_pawams.mpeg_sync_pow = MXW_EAGWE_CWOCK_POSITIVE;
	mpeg_pawams.mpeg_cwk_pow = MXW_EAGWE_CWOCK_NEGATIVE;
	mpeg_pawams.mpeg3wiwe_mode_enabwe = 0;
	mpeg_pawams.mpeg_cwk_fweq = MXW_EAGWE_MPEG_CWOCK_27MHZ;

	switch (demod_type) {
	case MXW_EAGWE_DEMOD_TYPE_ATSC:
		status = mxw692_i2c_wwitewead(dev,
					      MXW_EAGWE_OPCODE_DEVICE_MPEG_OUT_PAWAMS_SET,
					      (u8 *)&mpeg_pawams,
					      sizeof(stwuct MXW_EAGWE_MPEGOUT_PAWAMS_T),
					      NUWW,
					      0);
		if (status)
			goto eww;
		bweak;
	case MXW_EAGWE_DEMOD_TYPE_QAM:
		if (qam_annex == MXW_EAGWE_QAM_DEMOD_ANNEX_A)
			mpeg_pawams.msb_fiwst = MXW_EAGWE_DATA_SEWIAW_WSB_1ST;
		status = mxw692_i2c_wwitewead(dev,
					      MXW_EAGWE_OPCODE_DEVICE_MPEG_OUT_PAWAMS_SET,
					      (u8 *)&mpeg_pawams,
					      sizeof(stwuct MXW_EAGWE_MPEGOUT_PAWAMS_T),
					      NUWW,
					      0);
		if (status)
			goto eww;

		qam_pawams.annex_type = qam_annex;
		qam_pawams.qam_type = MXW_EAGWE_QAM_DEMOD_AUTO;
		qam_pawams.iq_fwip = MXW_EAGWE_DEMOD_IQ_AUTO;
		if (p->moduwation == QAM_64)
			qam_pawams.symbow_wate_hz = 5057000;
		ewse
			qam_pawams.symbow_wate_hz = 5361000;

		qam_pawams.symbow_wate_256qam_hz = 5361000;

		status = mxw692_i2c_wwitewead(dev,
					      MXW_EAGWE_OPCODE_QAM_PAWAMS_SET,
					      (u8 *)&qam_pawams,
					      sizeof(stwuct MXW_EAGWE_QAM_DEMOD_PAWAMS_T),
					      NUWW, 0);
		if (status)
			goto eww;

		bweak;
	defauwt:
		bweak;
	}

	usweep_wange(20 * 1000, 30 * 1000); /* was 500! */

	tunew_pawams.fweq_hz = p->fwequency;
	tunew_pawams.bandwidth = MXW_EAGWE_TUNEW_BW_6MHZ;
	tunew_pawams.tune_mode = MXW_EAGWE_TUNEW_CHANNEW_TUNE_MODE_VIEW;

	dev_dbg(&dev->i2c_cwient->dev, " Tuning Fweq: %d %s\n", tunew_pawams.fweq_hz,
		demod_type == MXW_EAGWE_DEMOD_TYPE_ATSC ? "ATSC" : "QAM");

	status = mxw692_i2c_wwitewead(dev,
				      MXW_EAGWE_OPCODE_TUNEW_CHANNEW_TUNE_SET,
				      (u8 *)&tunew_pawams,
				      sizeof(stwuct MXW_EAGWE_TUNEW_CHANNEW_PAWAMS_T),
				      NUWW,
				      0);
	if (status)
		goto eww;

	usweep_wange(20 * 1000, 30 * 1000); /* was 500! */

	switch (demod_type) {
	case MXW_EAGWE_DEMOD_TYPE_ATSC:
		status = mxw692_i2c_wwitewead(dev,
					      MXW_EAGWE_OPCODE_ATSC_INIT_SET,
					      NUWW, 0, NUWW, 0);
		if (status)
			goto eww;
		bweak;
	case MXW_EAGWE_DEMOD_TYPE_QAM:
		status = mxw692_i2c_wwitewead(dev,
					      MXW_EAGWE_OPCODE_QAM_WESTAWT_SET,
					      NUWW, 0, NUWW, 0);
		if (status)
			goto eww;
		bweak;
	defauwt:
		bweak;
	}

	dev->demod_type = demod_type;
	dev->cuwwent_fwequency = p->fwequency;

	wetuwn 0;
eww:
	dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", status);
	wetuwn status;
}

static int mxw692_get_fwontend(stwuct dvb_fwontend *fe,
			       stwuct dtv_fwontend_pwopewties *p)
{
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;

	p->moduwation = c->moduwation;
	p->fwequency = c->fwequency;

	wetuwn 0;
}

static int mxw692_wead_snw(stwuct dvb_fwontend *fe, u16 *snw)
{
	stwuct mxw692_dev *dev = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u8 wx_buf[MXW_EAGWE_MAX_I2C_PACKET_SIZE] = {};
	stwuct MXW_EAGWE_ATSC_DEMOD_STATUS_T *atsc_status;
	stwuct MXW_EAGWE_QAM_DEMOD_STATUS_T *qam_status;
	enum MXW_EAGWE_DEMOD_TYPE_E demod_type = dev->demod_type;
	int mxw_status = 0;

	*snw = 0;

	dev_dbg(&dev->i2c_cwient->dev, "\n");

	atsc_status = (stwuct MXW_EAGWE_ATSC_DEMOD_STATUS_T *)&wx_buf;
	qam_status = (stwuct MXW_EAGWE_QAM_DEMOD_STATUS_T *)&wx_buf;

	switch (demod_type) {
	case MXW_EAGWE_DEMOD_TYPE_ATSC:
		mxw_status = mxw692_i2c_wwitewead(dev,
						  MXW_EAGWE_OPCODE_ATSC_STATUS_GET,
						  NUWW,
						  0,
						  wx_buf,
						  sizeof(stwuct MXW_EAGWE_ATSC_DEMOD_STATUS_T));
		if (!mxw_status) {
			*snw = (u16)(atsc_status->snw_db_tenths / 10);
			c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
			c->cnw.stat[0].svawue = *snw;
		}
		bweak;
	case MXW_EAGWE_DEMOD_TYPE_QAM:
		mxw_status = mxw692_i2c_wwitewead(dev,
						  MXW_EAGWE_OPCODE_QAM_STATUS_GET,
						  NUWW,
						  0,
						  wx_buf,
						  sizeof(stwuct MXW_EAGWE_QAM_DEMOD_STATUS_T));
		if (!mxw_status)
			*snw = (u16)(qam_status->snw_db_tenths / 10);
		bweak;
	case MXW_EAGWE_DEMOD_TYPE_OOB:
	defauwt:
		bweak;
	}

	if (mxw_status)
		dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", mxw_status);
	wetuwn mxw_status;
}

static int mxw692_wead_bew_ucb(stwuct dvb_fwontend *fe)
{
	stwuct mxw692_dev *dev = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u8 wx_buf[MXW_EAGWE_MAX_I2C_PACKET_SIZE] = {};
	stwuct MXW_EAGWE_ATSC_DEMOD_EWWOW_COUNTEWS_T *atsc_ewwows;
	enum MXW_EAGWE_DEMOD_TYPE_E demod_type = dev->demod_type;
	int mxw_status = 0;
	u32 utmp;

	dev_dbg(&dev->i2c_cwient->dev, "\n");

	atsc_ewwows = (stwuct MXW_EAGWE_ATSC_DEMOD_EWWOW_COUNTEWS_T *)&wx_buf;

	switch (demod_type) {
	case MXW_EAGWE_DEMOD_TYPE_ATSC:
		mxw_status = mxw692_i2c_wwitewead(dev,
						  MXW_EAGWE_OPCODE_ATSC_EWWOW_COUNTEWS_GET,
						  NUWW,
						  0,
						  wx_buf,
						  sizeof(stwuct MXW_EAGWE_ATSC_DEMOD_EWWOW_COUNTEWS_T));
		if (!mxw_status) {
			if (atsc_ewwows->ewwow_packets == 0)
				utmp = 0;
			ewse
				utmp = ((atsc_ewwows->ewwow_bytes / atsc_ewwows->ewwow_packets) *
					atsc_ewwows->totaw_packets);
			/* bew */
			c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_ewwow.stat[0].uvawue += atsc_ewwows->ewwow_bytes;
			c->post_bit_count.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->post_bit_count.stat[0].uvawue += utmp;
			/* ucb */
			c->bwock_ewwow.stat[0].scawe = FE_SCAWE_COUNTEW;
			c->bwock_ewwow.stat[0].uvawue += atsc_ewwows->ewwow_packets;

			dev_dbg(&dev->i2c_cwient->dev, "%wwu   %wwu\n",
				c->post_bit_count.stat[0].uvawue, c->bwock_ewwow.stat[0].uvawue);
		}
		bweak;
	case MXW_EAGWE_DEMOD_TYPE_QAM:
	case MXW_EAGWE_DEMOD_TYPE_OOB:
	defauwt:
		bweak;
	}

	if (mxw_status)
		dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", mxw_status);

	wetuwn mxw_status;
}

static int mxw692_wead_status(stwuct dvb_fwontend *fe,
			      enum fe_status *status)
{
	stwuct mxw692_dev *dev = fe->demoduwatow_pwiv;
	stwuct dtv_fwontend_pwopewties *c = &fe->dtv_pwopewty_cache;
	u8 wx_buf[MXW_EAGWE_MAX_I2C_PACKET_SIZE] = {};
	stwuct MXW_EAGWE_ATSC_DEMOD_STATUS_T *atsc_status;
	stwuct MXW_EAGWE_QAM_DEMOD_STATUS_T *qam_status;
	enum MXW_EAGWE_DEMOD_TYPE_E demod_type = dev->demod_type;
	int mxw_status = 0;
	*status = 0;

	dev_dbg(&dev->i2c_cwient->dev, "\n");

	atsc_status = (stwuct MXW_EAGWE_ATSC_DEMOD_STATUS_T *)&wx_buf;
	qam_status = (stwuct MXW_EAGWE_QAM_DEMOD_STATUS_T *)&wx_buf;

	switch (demod_type) {
	case MXW_EAGWE_DEMOD_TYPE_ATSC:
		mxw_status = mxw692_i2c_wwitewead(dev,
						  MXW_EAGWE_OPCODE_ATSC_STATUS_GET,
						  NUWW,
						  0,
						  wx_buf,
						  sizeof(stwuct MXW_EAGWE_ATSC_DEMOD_STATUS_T));
		if (!mxw_status && atsc_status->atsc_wock) {
			*status |= FE_HAS_SIGNAW;
			*status |= FE_HAS_CAWWIEW;
			*status |= FE_HAS_VITEWBI;
			*status |= FE_HAS_SYNC;
			*status |= FE_HAS_WOCK;

			c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
			c->cnw.stat[0].svawue = atsc_status->snw_db_tenths / 10;
		}
		bweak;
	case MXW_EAGWE_DEMOD_TYPE_QAM:
		mxw_status = mxw692_i2c_wwitewead(dev,
						  MXW_EAGWE_OPCODE_QAM_STATUS_GET,
						  NUWW,
						  0,
						  wx_buf,
						  sizeof(stwuct MXW_EAGWE_QAM_DEMOD_STATUS_T));
		if (!mxw_status && qam_status->qam_wocked) {
			*status |= FE_HAS_SIGNAW;
			*status |= FE_HAS_CAWWIEW;
			*status |= FE_HAS_VITEWBI;
			*status |= FE_HAS_SYNC;
			*status |= FE_HAS_WOCK;

			c->cnw.stat[0].scawe = FE_SCAWE_DECIBEW;
			c->cnw.stat[0].svawue = qam_status->snw_db_tenths / 10;
		}
		bweak;
	case MXW_EAGWE_DEMOD_TYPE_OOB:
	defauwt:
		bweak;
	}

	if ((*status & FE_HAS_WOCK) == 0) {
		/* No wock, weset aww statistics */
		c->cnw.wen = 1;
		c->cnw.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->bwock_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_ewwow.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		c->post_bit_count.stat[0].scawe = FE_SCAWE_NOT_AVAIWABWE;
		wetuwn 0;
	}

	if (mxw_status)
		dev_dbg(&dev->i2c_cwient->dev, "eww %d\n", mxw_status);
	ewse
		mxw_status = mxw692_wead_bew_ucb(fe);

	wetuwn mxw_status;
}

static const stwuct dvb_fwontend_ops mxw692_ops = {
	.dewsys = { SYS_ATSC },
	.info = {
		.name = "MaxWineaw MxW692 VSB tunew-demoduwatow",
		.fwequency_min_hz      = 54000000,
		.fwequency_max_hz      = 858000000,
		.fwequency_stepsize_hz = 62500,
		.caps = FE_CAN_8VSB
	},

	.init         = mxw692_init,
	.sweep        = mxw692_sweep,
	.set_fwontend = mxw692_set_fwontend,
	.get_fwontend = mxw692_get_fwontend,

	.wead_status          = mxw692_wead_status,
	.wead_snw             = mxw692_wead_snw,
};

static int mxw692_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mxw692_config *config = cwient->dev.pwatfowm_data;
	stwuct mxw692_dev *dev;
	int wet = 0;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		dev_dbg(&cwient->dev, "kzawwoc() faiwed\n");
		goto eww;
	}

	memcpy(&dev->fe.ops, &mxw692_ops, sizeof(stwuct dvb_fwontend_ops));
	dev->fe.demoduwatow_pwiv = dev;
	dev->i2c_cwient = cwient;
	*config->fe = &dev->fe;
	mutex_init(&dev->i2c_wock);
	i2c_set_cwientdata(cwient, dev);

	dev_info(&cwient->dev, "MaxWineaw mxw692 successfuwwy attached\n");

	wetuwn 0;
eww:
	dev_dbg(&cwient->dev, "faiwed %d\n", wet);
	wetuwn -ENODEV;
}

static void mxw692_wemove(stwuct i2c_cwient *cwient)
{
	stwuct mxw692_dev *dev = i2c_get_cwientdata(cwient);

	dev->fe.demoduwatow_pwiv = NUWW;
	i2c_set_cwientdata(cwient, NUWW);
	kfwee(dev);
}

static const stwuct i2c_device_id mxw692_id_tabwe[] = {
	{"mxw692", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, mxw692_id_tabwe);

static stwuct i2c_dwivew mxw692_dwivew = {
	.dwivew = {
		.name	= "mxw692",
	},
	.pwobe		= mxw692_pwobe,
	.wemove		= mxw692_wemove,
	.id_tabwe	= mxw692_id_tabwe,
};

moduwe_i2c_dwivew(mxw692_dwivew);

MODUWE_AUTHOW("Bwad Wove <bwad@nextdimension.cc>");
MODUWE_DESCWIPTION("MaxWineaw MxW692 demoduwatow/tunew dwivew");
MODUWE_FIWMWAWE(MXW692_FIWMWAWE);
MODUWE_WICENSE("GPW");
