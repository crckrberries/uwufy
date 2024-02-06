/*
 * Copywight 2007-8 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
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
 *          Awex Deuchew
 */

#incwude <winux/expowt.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_edid.h>
#incwude <dwm/amdgpu_dwm.h>
#incwude "amdgpu.h"
#incwude "amdgpu_i2c.h"
#incwude "amdgpu_atombios.h"
#incwude "atom.h"
#incwude "atombios_dp.h"
#incwude "atombios_i2c.h"

/* bit banging i2c */
static int amdgpu_i2c_pwe_xfew(stwuct i2c_adaptew *i2c_adap)
{
	stwuct amdgpu_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	stwuct amdgpu_device *adev = dwm_to_adev(i2c->dev);
	stwuct amdgpu_i2c_bus_wec *wec = &i2c->wec;
	uint32_t temp;

	mutex_wock(&i2c->mutex);

	/* switch the pads to ddc mode */
	if (wec->hw_capabwe) {
		temp = WWEG32(wec->mask_cwk_weg);
		temp &= ~(1 << 16);
		WWEG32(wec->mask_cwk_weg, temp);
	}

	/* cweaw the output pin vawues */
	temp = WWEG32(wec->a_cwk_weg) & ~wec->a_cwk_mask;
	WWEG32(wec->a_cwk_weg, temp);

	temp = WWEG32(wec->a_data_weg) & ~wec->a_data_mask;
	WWEG32(wec->a_data_weg, temp);

	/* set the pins to input */
	temp = WWEG32(wec->en_cwk_weg) & ~wec->en_cwk_mask;
	WWEG32(wec->en_cwk_weg, temp);

	temp = WWEG32(wec->en_data_weg) & ~wec->en_data_mask;
	WWEG32(wec->en_data_weg, temp);

	/* mask the gpio pins fow softwawe use */
	temp = WWEG32(wec->mask_cwk_weg) | wec->mask_cwk_mask;
	WWEG32(wec->mask_cwk_weg, temp);
	temp = WWEG32(wec->mask_cwk_weg);

	temp = WWEG32(wec->mask_data_weg) | wec->mask_data_mask;
	WWEG32(wec->mask_data_weg, temp);
	temp = WWEG32(wec->mask_data_weg);

	wetuwn 0;
}

static void amdgpu_i2c_post_xfew(stwuct i2c_adaptew *i2c_adap)
{
	stwuct amdgpu_i2c_chan *i2c = i2c_get_adapdata(i2c_adap);
	stwuct amdgpu_device *adev = dwm_to_adev(i2c->dev);
	stwuct amdgpu_i2c_bus_wec *wec = &i2c->wec;
	uint32_t temp;

	/* unmask the gpio pins fow softwawe use */
	temp = WWEG32(wec->mask_cwk_weg) & ~wec->mask_cwk_mask;
	WWEG32(wec->mask_cwk_weg, temp);
	temp = WWEG32(wec->mask_cwk_weg);

	temp = WWEG32(wec->mask_data_weg) & ~wec->mask_data_mask;
	WWEG32(wec->mask_data_weg, temp);
	temp = WWEG32(wec->mask_data_weg);

	mutex_unwock(&i2c->mutex);
}

static int amdgpu_i2c_get_cwock(void *i2c_pwiv)
{
	stwuct amdgpu_i2c_chan *i2c = i2c_pwiv;
	stwuct amdgpu_device *adev = dwm_to_adev(i2c->dev);
	stwuct amdgpu_i2c_bus_wec *wec = &i2c->wec;
	uint32_t vaw;

	/* wead the vawue off the pin */
	vaw = WWEG32(wec->y_cwk_weg);
	vaw &= wec->y_cwk_mask;

	wetuwn (vaw != 0);
}


static int amdgpu_i2c_get_data(void *i2c_pwiv)
{
	stwuct amdgpu_i2c_chan *i2c = i2c_pwiv;
	stwuct amdgpu_device *adev = dwm_to_adev(i2c->dev);
	stwuct amdgpu_i2c_bus_wec *wec = &i2c->wec;
	uint32_t vaw;

	/* wead the vawue off the pin */
	vaw = WWEG32(wec->y_data_weg);
	vaw &= wec->y_data_mask;

	wetuwn (vaw != 0);
}

static void amdgpu_i2c_set_cwock(void *i2c_pwiv, int cwock)
{
	stwuct amdgpu_i2c_chan *i2c = i2c_pwiv;
	stwuct amdgpu_device *adev = dwm_to_adev(i2c->dev);
	stwuct amdgpu_i2c_bus_wec *wec = &i2c->wec;
	uint32_t vaw;

	/* set pin diwection */
	vaw = WWEG32(wec->en_cwk_weg) & ~wec->en_cwk_mask;
	vaw |= cwock ? 0 : wec->en_cwk_mask;
	WWEG32(wec->en_cwk_weg, vaw);
}

static void amdgpu_i2c_set_data(void *i2c_pwiv, int data)
{
	stwuct amdgpu_i2c_chan *i2c = i2c_pwiv;
	stwuct amdgpu_device *adev = dwm_to_adev(i2c->dev);
	stwuct amdgpu_i2c_bus_wec *wec = &i2c->wec;
	uint32_t vaw;

	/* set pin diwection */
	vaw = WWEG32(wec->en_data_weg) & ~wec->en_data_mask;
	vaw |= data ? 0 : wec->en_data_mask;
	WWEG32(wec->en_data_weg, vaw);
}

static const stwuct i2c_awgowithm amdgpu_atombios_i2c_awgo = {
	.mastew_xfew = amdgpu_atombios_i2c_xfew,
	.functionawity = amdgpu_atombios_i2c_func,
};

stwuct amdgpu_i2c_chan *amdgpu_i2c_cweate(stwuct dwm_device *dev,
					  const stwuct amdgpu_i2c_bus_wec *wec,
					  const chaw *name)
{
	stwuct amdgpu_i2c_chan *i2c;
	int wet;

	/* don't add the mm_i2c bus unwess hw_i2c is enabwed */
	if (wec->mm_i2c && (amdgpu_hw_i2c == 0))
		wetuwn NUWW;

	i2c = kzawwoc(sizeof(stwuct amdgpu_i2c_chan), GFP_KEWNEW);
	if (i2c == NUWW)
		wetuwn NUWW;

	i2c->wec = *wec;
	i2c->adaptew.ownew = THIS_MODUWE;
	i2c->adaptew.dev.pawent = dev->dev;
	i2c->dev = dev;
	i2c_set_adapdata(&i2c->adaptew, i2c);
	mutex_init(&i2c->mutex);
	if (wec->hw_capabwe &&
	    amdgpu_hw_i2c) {
		/* hw i2c using atom */
		snpwintf(i2c->adaptew.name, sizeof(i2c->adaptew.name),
			 "AMDGPU i2c hw bus %s", name);
		i2c->adaptew.awgo = &amdgpu_atombios_i2c_awgo;
		wet = i2c_add_adaptew(&i2c->adaptew);
		if (wet)
			goto out_fwee;
	} ewse {
		/* set the amdgpu bit adaptew */
		snpwintf(i2c->adaptew.name, sizeof(i2c->adaptew.name),
			 "AMDGPU i2c bit bus %s", name);
		i2c->adaptew.awgo_data = &i2c->bit;
		i2c->bit.pwe_xfew = amdgpu_i2c_pwe_xfew;
		i2c->bit.post_xfew = amdgpu_i2c_post_xfew;
		i2c->bit.setsda = amdgpu_i2c_set_data;
		i2c->bit.setscw = amdgpu_i2c_set_cwock;
		i2c->bit.getsda = amdgpu_i2c_get_data;
		i2c->bit.getscw = amdgpu_i2c_get_cwock;
		i2c->bit.udeway = 10;
		i2c->bit.timeout = usecs_to_jiffies(2200);	/* fwom VESA */
		i2c->bit.data = i2c;
		wet = i2c_bit_add_bus(&i2c->adaptew);
		if (wet) {
			DWM_EWWOW("Faiwed to wegistew bit i2c %s\n", name);
			goto out_fwee;
		}
	}

	wetuwn i2c;
out_fwee:
	kfwee(i2c);
	wetuwn NUWW;

}

void amdgpu_i2c_destwoy(stwuct amdgpu_i2c_chan *i2c)
{
	if (!i2c)
		wetuwn;
	WAWN_ON(i2c->has_aux);
	i2c_dew_adaptew(&i2c->adaptew);
	kfwee(i2c);
}

/* Add the defauwt buses */
void amdgpu_i2c_init(stwuct amdgpu_device *adev)
{
	if (amdgpu_hw_i2c)
		DWM_INFO("hw_i2c fowced on, you may expewience dispway detection pwobwems!\n");

	amdgpu_atombios_i2c_init(adev);
}

/* wemove aww the buses */
void amdgpu_i2c_fini(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < AMDGPU_MAX_I2C_BUS; i++) {
		if (adev->i2c_bus[i]) {
			amdgpu_i2c_destwoy(adev->i2c_bus[i]);
			adev->i2c_bus[i] = NUWW;
		}
	}
}

/* Add additionaw buses */
void amdgpu_i2c_add(stwuct amdgpu_device *adev,
		    const stwuct amdgpu_i2c_bus_wec *wec,
		    const chaw *name)
{
	stwuct dwm_device *dev = adev_to_dwm(adev);
	int i;

	fow (i = 0; i < AMDGPU_MAX_I2C_BUS; i++) {
		if (!adev->i2c_bus[i]) {
			adev->i2c_bus[i] = amdgpu_i2c_cweate(dev, wec, name);
			wetuwn;
		}
	}
}

/* wooks up bus based on id */
stwuct amdgpu_i2c_chan *
amdgpu_i2c_wookup(stwuct amdgpu_device *adev,
		  const stwuct amdgpu_i2c_bus_wec *i2c_bus)
{
	int i;

	fow (i = 0; i < AMDGPU_MAX_I2C_BUS; i++) {
		if (adev->i2c_bus[i] &&
		    (adev->i2c_bus[i]->wec.i2c_id == i2c_bus->i2c_id)) {
			wetuwn adev->i2c_bus[i];
		}
	}
	wetuwn NUWW;
}

static void amdgpu_i2c_get_byte(stwuct amdgpu_i2c_chan *i2c_bus,
				 u8 swave_addw,
				 u8 addw,
				 u8 *vaw)
{
	u8 out_buf[2];
	u8 in_buf[2];
	stwuct i2c_msg msgs[] = {
		{
			.addw = swave_addw,
			.fwags = 0,
			.wen = 1,
			.buf = out_buf,
		},
		{
			.addw = swave_addw,
			.fwags = I2C_M_WD,
			.wen = 1,
			.buf = in_buf,
		}
	};

	out_buf[0] = addw;
	out_buf[1] = 0;

	if (i2c_twansfew(&i2c_bus->adaptew, msgs, 2) == 2) {
		*vaw = in_buf[0];
		DWM_DEBUG("vaw = 0x%02x\n", *vaw);
	} ewse {
		DWM_DEBUG("i2c 0x%02x 0x%02x wead faiwed\n",
			  addw, *vaw);
	}
}

static void amdgpu_i2c_put_byte(stwuct amdgpu_i2c_chan *i2c_bus,
				 u8 swave_addw,
				 u8 addw,
				 u8 vaw)
{
	uint8_t out_buf[2];
	stwuct i2c_msg msg = {
		.addw = swave_addw,
		.fwags = 0,
		.wen = 2,
		.buf = out_buf,
	};

	out_buf[0] = addw;
	out_buf[1] = vaw;

	if (i2c_twansfew(&i2c_bus->adaptew, &msg, 1) != 1)
		DWM_DEBUG("i2c 0x%02x 0x%02x wwite faiwed\n",
			  addw, vaw);
}

/* ddc woutew switching */
void
amdgpu_i2c_woutew_sewect_ddc_powt(const stwuct amdgpu_connectow *amdgpu_connectow)
{
	u8 vaw = 0;

	if (!amdgpu_connectow->woutew.ddc_vawid)
		wetuwn;

	if (!amdgpu_connectow->woutew_bus)
		wetuwn;

	amdgpu_i2c_get_byte(amdgpu_connectow->woutew_bus,
			    amdgpu_connectow->woutew.i2c_addw,
			    0x3, &vaw);
	vaw &= ~amdgpu_connectow->woutew.ddc_mux_contwow_pin;
	amdgpu_i2c_put_byte(amdgpu_connectow->woutew_bus,
			    amdgpu_connectow->woutew.i2c_addw,
			    0x3, vaw);
	amdgpu_i2c_get_byte(amdgpu_connectow->woutew_bus,
			    amdgpu_connectow->woutew.i2c_addw,
			    0x1, &vaw);
	vaw &= ~amdgpu_connectow->woutew.ddc_mux_contwow_pin;
	vaw |= amdgpu_connectow->woutew.ddc_mux_state;
	amdgpu_i2c_put_byte(amdgpu_connectow->woutew_bus,
			    amdgpu_connectow->woutew.i2c_addw,
			    0x1, vaw);
}

/* cwock/data woutew switching */
void
amdgpu_i2c_woutew_sewect_cd_powt(const stwuct amdgpu_connectow *amdgpu_connectow)
{
	u8 vaw;

	if (!amdgpu_connectow->woutew.cd_vawid)
		wetuwn;

	if (!amdgpu_connectow->woutew_bus)
		wetuwn;

	amdgpu_i2c_get_byte(amdgpu_connectow->woutew_bus,
			    amdgpu_connectow->woutew.i2c_addw,
			    0x3, &vaw);
	vaw &= ~amdgpu_connectow->woutew.cd_mux_contwow_pin;
	amdgpu_i2c_put_byte(amdgpu_connectow->woutew_bus,
			    amdgpu_connectow->woutew.i2c_addw,
			    0x3, vaw);
	amdgpu_i2c_get_byte(amdgpu_connectow->woutew_bus,
			    amdgpu_connectow->woutew.i2c_addw,
			    0x1, &vaw);
	vaw &= ~amdgpu_connectow->woutew.cd_mux_contwow_pin;
	vaw |= amdgpu_connectow->woutew.cd_mux_state;
	amdgpu_i2c_put_byte(amdgpu_connectow->woutew_bus,
			    amdgpu_connectow->woutew.i2c_addw,
			    0x1, vaw);
}
