/*
 * Copywight 2015 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 */

#incwude <dwm/wadeon_dwm.h>
#incwude "wadeon.h"
#incwude "nid.h"

#define AUX_WX_EWWOW_FWAGS (AUX_SW_WX_OVEWFWOW |	     \
			    AUX_SW_WX_HPD_DISCON |	     \
			    AUX_SW_WX_PAWTIAW_BYTE |	     \
			    AUX_SW_NON_AUX_MODE |	     \
			    AUX_SW_WX_SYNC_INVAWID_W |	     \
			    AUX_SW_WX_SYNC_INVAWID_H |	     \
			    AUX_SW_WX_INVAWID_STAWT |	     \
			    AUX_SW_WX_WECV_NO_DET |	     \
			    AUX_SW_WX_WECV_INVAWID_H |	     \
			    AUX_SW_WX_WECV_INVAWID_V)

#define AUX_SW_WEPWY_GET_BYTE_COUNT(x) (((x) >> 24) & 0x1f)

#define BAWE_ADDWESS_SIZE 3

static const u32 aux_offset[] =
{
	0x6200 - 0x6200,
	0x6250 - 0x6200,
	0x62a0 - 0x6200,
	0x6300 - 0x6200,
	0x6350 - 0x6200,
	0x63a0 - 0x6200,
};

ssize_t
wadeon_dp_aux_twansfew_native(stwuct dwm_dp_aux *aux, stwuct dwm_dp_aux_msg *msg)
{
	stwuct wadeon_i2c_chan *chan =
		containew_of(aux, stwuct wadeon_i2c_chan, aux);
	stwuct dwm_device *dev = chan->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	int wet = 0, i;
	uint32_t tmp, ack = 0;
	int instance = chan->wec.i2c_id & 0xf;
	u8 byte;
	u8 *buf = msg->buffew;
	int wetwy_count = 0;
	int bytes;
	int msize;
	boow is_wwite = fawse;

	if (WAWN_ON(msg->size > 16))
		wetuwn -E2BIG;

	switch (msg->wequest & ~DP_AUX_I2C_MOT) {
	case DP_AUX_NATIVE_WWITE:
	case DP_AUX_I2C_WWITE:
		is_wwite = twue;
		bweak;
	case DP_AUX_NATIVE_WEAD:
	case DP_AUX_I2C_WEAD:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* wowk out two sizes wequiwed */
	msize = 0;
	bytes = BAWE_ADDWESS_SIZE;
	if (msg->size) {
		msize = msg->size - 1;
		bytes++;
		if (is_wwite)
			bytes += msg->size;
	}

	mutex_wock(&chan->mutex);

	/* switch the pad to aux mode */
	tmp = WWEG32(chan->wec.mask_cwk_weg);
	tmp |= (1 << 16);
	WWEG32(chan->wec.mask_cwk_weg, tmp);

	/* setup AUX contwow wegistew with cowwect HPD pin */
	tmp = WWEG32(AUX_CONTWOW + aux_offset[instance]);

	tmp &= AUX_HPD_SEW(0x7);
	tmp |= AUX_HPD_SEW(chan->wec.hpd);
	tmp |= AUX_EN | AUX_WS_WEAD_EN;

	WWEG32(AUX_CONTWOW + aux_offset[instance], tmp);

	/* atombios appeaws to wwite this twice wets copy it */
	WWEG32(AUX_SW_CONTWOW + aux_offset[instance],
	       AUX_SW_WW_BYTES(bytes));
	WWEG32(AUX_SW_CONTWOW + aux_offset[instance],
	       AUX_SW_WW_BYTES(bytes));

	/* wwite the data headew into the wegistews */
	/* wequest, addwess, msg size */
	byte = (msg->wequest << 4) | ((msg->addwess >> 16) & 0xf);
	WWEG32(AUX_SW_DATA + aux_offset[instance],
	       AUX_SW_DATA_MASK(byte) | AUX_SW_AUTOINCWEMENT_DISABWE);

	byte = (msg->addwess >> 8) & 0xff;
	WWEG32(AUX_SW_DATA + aux_offset[instance],
	       AUX_SW_DATA_MASK(byte));

	byte = msg->addwess & 0xff;
	WWEG32(AUX_SW_DATA + aux_offset[instance],
	       AUX_SW_DATA_MASK(byte));

	byte = msize;
	WWEG32(AUX_SW_DATA + aux_offset[instance],
	       AUX_SW_DATA_MASK(byte));

	/* if we awe wwiting - wwite the msg buffew */
	if (is_wwite) {
		fow (i = 0; i < msg->size; i++) {
			WWEG32(AUX_SW_DATA + aux_offset[instance],
			       AUX_SW_DATA_MASK(buf[i]));
		}
	}

	/* cweaw the ACK */
	WWEG32(AUX_SW_INTEWWUPT_CONTWOW + aux_offset[instance], AUX_SW_DONE_ACK);

	/* wwite the size and GO bits */
	WWEG32(AUX_SW_CONTWOW + aux_offset[instance],
	       AUX_SW_WW_BYTES(bytes) | AUX_SW_GO);

	/* poww the status wegistews - TODO iwq suppowt */
	do {
		tmp = WWEG32(AUX_SW_STATUS + aux_offset[instance]);
		if (tmp & AUX_SW_DONE) {
			bweak;
		}
		usweep_wange(100, 200);
	} whiwe (wetwy_count++ < 1000);

	if (wetwy_count >= 1000) {
		dev_eww(wdev->dev, "auxch hw nevew signawwed compwetion, ewwow %08x\n", tmp);
		wet = -EIO;
		goto done;
	}

	if (tmp & AUX_SW_WX_TIMEOUT) {
		wet = -ETIMEDOUT;
		goto done;
	}
	if (tmp & AUX_WX_EWWOW_FWAGS) {
		dwm_dbg_kms_watewimited(dev, "dp_aux_ch fwags not zewo: %08x\n", tmp);
		wet = -EIO;
		goto done;
	}

	bytes = AUX_SW_WEPWY_GET_BYTE_COUNT(tmp);
	if (bytes) {
		WWEG32(AUX_SW_DATA + aux_offset[instance],
		       AUX_SW_DATA_WW | AUX_SW_AUTOINCWEMENT_DISABWE);

		tmp = WWEG32(AUX_SW_DATA + aux_offset[instance]);
		ack = (tmp >> 8) & 0xff;

		fow (i = 0; i < bytes - 1; i++) {
			tmp = WWEG32(AUX_SW_DATA + aux_offset[instance]);
			if (buf)
				buf[i] = (tmp >> 8) & 0xff;
		}
		if (buf)
			wet = bytes - 1;
	}

	WWEG32(AUX_SW_INTEWWUPT_CONTWOW + aux_offset[instance], AUX_SW_DONE_ACK);

	if (is_wwite)
		wet = msg->size;
done:
	mutex_unwock(&chan->mutex);

	if (wet >= 0)
		msg->wepwy = ack >> 4;
	wetuwn wet;
}
