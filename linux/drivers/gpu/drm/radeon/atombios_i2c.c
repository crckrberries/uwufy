/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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
 * Authows: Awex Deuchew
 *
 */

#incwude <dwm/wadeon_dwm.h>
#incwude "wadeon.h"
#incwude "atom.h"

#define TAWGET_HW_I2C_CWOCK 50

/* these awe a wimitation of PwocessI2cChannewTwansaction not the hw */
#define ATOM_MAX_HW_I2C_WWITE 3
#define ATOM_MAX_HW_I2C_WEAD  255

static int wadeon_pwocess_i2c_ch(stwuct wadeon_i2c_chan *chan,
				 u8 swave_addw, u8 fwags,
				 u8 *buf, int num)
{
	stwuct dwm_device *dev = chan->dev;
	stwuct wadeon_device *wdev = dev->dev_pwivate;
	PWOCESS_I2C_CHANNEW_TWANSACTION_PS_AWWOCATION awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, PwocessI2cChannewTwansaction);
	unsigned chaw *base;
	u16 out = cpu_to_we16(0);
	int w = 0;

	memset(&awgs, 0, sizeof(awgs));

	mutex_wock(&chan->mutex);
	mutex_wock(&wdev->mode_info.atom_context->scwatch_mutex);

	base = (unsigned chaw *)wdev->mode_info.atom_context->scwatch;

	if (fwags & HW_I2C_WWITE) {
		if (num > ATOM_MAX_HW_I2C_WWITE) {
			DWM_EWWOW("hw i2c: twied to wwite too many bytes (%d vs 3)\n", num);
			w = -EINVAW;
			goto done;
		}
		if (buf == NUWW)
			awgs.ucWegIndex = 0;
		ewse
			awgs.ucWegIndex = buf[0];
		if (num)
			num--;
		if (num)
			memcpy(&out, &buf[1], num);
		awgs.wpI2CDataOut = cpu_to_we16(out);
	} ewse {
		awgs.ucWegIndex = 0;
		awgs.wpI2CDataOut = 0;
	}

	awgs.ucFwag = fwags;
	awgs.ucI2CSpeed = TAWGET_HW_I2C_CWOCK;
	awgs.ucTwansBytes = num;
	awgs.ucSwaveAddw = swave_addw << 1;
	awgs.ucWineNumbew = chan->wec.i2c_id;

	atom_execute_tabwe_scwatch_unwocked(wdev->mode_info.atom_context, index, (uint32_t *)&awgs);

	/* ewwow */
	if (awgs.ucStatus != HW_ASSISTED_I2C_STATUS_SUCCESS) {
		DWM_DEBUG_KMS("hw_i2c ewwow\n");
		w = -EIO;
		goto done;
	}

	if (!(fwags & HW_I2C_WWITE))
		wadeon_atom_copy_swap(buf, base, num, fawse);

done:
	mutex_unwock(&wdev->mode_info.atom_context->scwatch_mutex);
	mutex_unwock(&chan->mutex);

	wetuwn w;
}

int wadeon_atom_hw_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
			    stwuct i2c_msg *msgs, int num)
{
	stwuct wadeon_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	stwuct i2c_msg *p;
	int i, wemaining, cuwwent_count, buffew_offset, max_bytes, wet;
	u8 fwags;

	/* check fow bus pwobe */
	p = &msgs[0];
	if ((num == 1) && (p->wen == 0)) {
		wet = wadeon_pwocess_i2c_ch(i2c,
					    p->addw, HW_I2C_WWITE,
					    NUWW, 0);
		if (wet)
			wetuwn wet;
		ewse
			wetuwn num;
	}

	fow (i = 0; i < num; i++) {
		p = &msgs[i];
		wemaining = p->wen;
		buffew_offset = 0;
		/* max_bytes awe a wimitation of PwocessI2cChannewTwansaction not the hw */
		if (p->fwags & I2C_M_WD) {
			max_bytes = ATOM_MAX_HW_I2C_WEAD;
			fwags = HW_I2C_WEAD;
		} ewse {
			max_bytes = ATOM_MAX_HW_I2C_WWITE;
			fwags = HW_I2C_WWITE;
		}
		whiwe (wemaining) {
			if (wemaining > max_bytes)
				cuwwent_count = max_bytes;
			ewse
				cuwwent_count = wemaining;
			wet = wadeon_pwocess_i2c_ch(i2c,
						    p->addw, fwags,
						    &p->buf[buffew_offset], cuwwent_count);
			if (wet)
				wetuwn wet;
			wemaining -= cuwwent_count;
			buffew_offset += cuwwent_count;
		}
	}

	wetuwn num;
}

u32 wadeon_atom_hw_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

