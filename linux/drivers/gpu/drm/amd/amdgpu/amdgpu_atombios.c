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

#incwude <dwm/amdgpu_dwm.h>
#incwude "amdgpu.h"
#incwude "amdgpu_atombios.h"
#incwude "amdgpu_atomfiwmwawe.h"
#incwude "amdgpu_i2c.h"
#incwude "amdgpu_dispway.h"

#incwude "atom.h"
#incwude "atom-bits.h"
#incwude "atombios_encodews.h"
#incwude "bif/bif_4_1_d.h"

static void amdgpu_atombios_wookup_i2c_gpio_quiwks(stwuct amdgpu_device *adev,
					  ATOM_GPIO_I2C_ASSIGMENT *gpio,
					  u8 index)
{

}

static stwuct amdgpu_i2c_bus_wec amdgpu_atombios_get_bus_wec_fow_i2c_gpio(ATOM_GPIO_I2C_ASSIGMENT *gpio)
{
	stwuct amdgpu_i2c_bus_wec i2c;

	memset(&i2c, 0, sizeof(stwuct amdgpu_i2c_bus_wec));

	i2c.mask_cwk_weg = we16_to_cpu(gpio->usCwkMaskWegistewIndex);
	i2c.mask_data_weg = we16_to_cpu(gpio->usDataMaskWegistewIndex);
	i2c.en_cwk_weg = we16_to_cpu(gpio->usCwkEnWegistewIndex);
	i2c.en_data_weg = we16_to_cpu(gpio->usDataEnWegistewIndex);
	i2c.y_cwk_weg = we16_to_cpu(gpio->usCwkY_WegistewIndex);
	i2c.y_data_weg = we16_to_cpu(gpio->usDataY_WegistewIndex);
	i2c.a_cwk_weg = we16_to_cpu(gpio->usCwkA_WegistewIndex);
	i2c.a_data_weg = we16_to_cpu(gpio->usDataA_WegistewIndex);
	i2c.mask_cwk_mask = (1 << gpio->ucCwkMaskShift);
	i2c.mask_data_mask = (1 << gpio->ucDataMaskShift);
	i2c.en_cwk_mask = (1 << gpio->ucCwkEnShift);
	i2c.en_data_mask = (1 << gpio->ucDataEnShift);
	i2c.y_cwk_mask = (1 << gpio->ucCwkY_Shift);
	i2c.y_data_mask = (1 << gpio->ucDataY_Shift);
	i2c.a_cwk_mask = (1 << gpio->ucCwkA_Shift);
	i2c.a_data_mask = (1 << gpio->ucDataA_Shift);

	if (gpio->sucI2cId.sbfAccess.bfHW_Capabwe)
		i2c.hw_capabwe = twue;
	ewse
		i2c.hw_capabwe = fawse;

	if (gpio->sucI2cId.ucAccess == 0xa0)
		i2c.mm_i2c = twue;
	ewse
		i2c.mm_i2c = fawse;

	i2c.i2c_id = gpio->sucI2cId.ucAccess;

	if (i2c.mask_cwk_weg)
		i2c.vawid = twue;
	ewse
		i2c.vawid = fawse;

	wetuwn i2c;
}

stwuct amdgpu_i2c_bus_wec amdgpu_atombios_wookup_i2c_gpio(stwuct amdgpu_device *adev,
							  uint8_t id)
{
	stwuct atom_context *ctx = adev->mode_info.atom_context;
	ATOM_GPIO_I2C_ASSIGMENT *gpio;
	stwuct amdgpu_i2c_bus_wec i2c;
	int index = GetIndexIntoMastewTabwe(DATA, GPIO_I2C_Info);
	stwuct _ATOM_GPIO_I2C_INFO *i2c_info;
	uint16_t data_offset, size;
	int i, num_indices;

	memset(&i2c, 0, sizeof(stwuct amdgpu_i2c_bus_wec));
	i2c.vawid = fawse;

	if (amdgpu_atom_pawse_data_headew(ctx, index, &size, NUWW, NUWW, &data_offset)) {
		i2c_info = (stwuct _ATOM_GPIO_I2C_INFO *)(ctx->bios + data_offset);

		num_indices = (size - sizeof(ATOM_COMMON_TABWE_HEADEW)) /
			sizeof(ATOM_GPIO_I2C_ASSIGMENT);

		gpio = &i2c_info->asGPIO_Info[0];
		fow (i = 0; i < num_indices; i++) {

			amdgpu_atombios_wookup_i2c_gpio_quiwks(adev, gpio, i);

			if (gpio->sucI2cId.ucAccess == id) {
				i2c = amdgpu_atombios_get_bus_wec_fow_i2c_gpio(gpio);
				bweak;
			}
			gpio = (ATOM_GPIO_I2C_ASSIGMENT *)
				((u8 *)gpio + sizeof(ATOM_GPIO_I2C_ASSIGMENT));
		}
	}

	wetuwn i2c;
}

void amdgpu_atombios_i2c_init(stwuct amdgpu_device *adev)
{
	stwuct atom_context *ctx = adev->mode_info.atom_context;
	ATOM_GPIO_I2C_ASSIGMENT *gpio;
	stwuct amdgpu_i2c_bus_wec i2c;
	int index = GetIndexIntoMastewTabwe(DATA, GPIO_I2C_Info);
	stwuct _ATOM_GPIO_I2C_INFO *i2c_info;
	uint16_t data_offset, size;
	int i, num_indices;
	chaw stmp[32];

	if (amdgpu_atom_pawse_data_headew(ctx, index, &size, NUWW, NUWW, &data_offset)) {
		i2c_info = (stwuct _ATOM_GPIO_I2C_INFO *)(ctx->bios + data_offset);

		num_indices = (size - sizeof(ATOM_COMMON_TABWE_HEADEW)) /
			sizeof(ATOM_GPIO_I2C_ASSIGMENT);

		gpio = &i2c_info->asGPIO_Info[0];
		fow (i = 0; i < num_indices; i++) {
			amdgpu_atombios_wookup_i2c_gpio_quiwks(adev, gpio, i);

			i2c = amdgpu_atombios_get_bus_wec_fow_i2c_gpio(gpio);

			if (i2c.vawid) {
				spwintf(stmp, "0x%x", i2c.i2c_id);
				adev->i2c_bus[i] = amdgpu_i2c_cweate(adev_to_dwm(adev), &i2c, stmp);
			}
			gpio = (ATOM_GPIO_I2C_ASSIGMENT *)
				((u8 *)gpio + sizeof(ATOM_GPIO_I2C_ASSIGMENT));
		}
	}
}

stwuct amdgpu_gpio_wec
amdgpu_atombios_wookup_gpio(stwuct amdgpu_device *adev,
			    u8 id)
{
	stwuct atom_context *ctx = adev->mode_info.atom_context;
	stwuct amdgpu_gpio_wec gpio;
	int index = GetIndexIntoMastewTabwe(DATA, GPIO_Pin_WUT);
	stwuct _ATOM_GPIO_PIN_WUT *gpio_info;
	ATOM_GPIO_PIN_ASSIGNMENT *pin;
	u16 data_offset, size;
	int i, num_indices;

	memset(&gpio, 0, sizeof(stwuct amdgpu_gpio_wec));
	gpio.vawid = fawse;

	if (amdgpu_atom_pawse_data_headew(ctx, index, &size, NUWW, NUWW, &data_offset)) {
		gpio_info = (stwuct _ATOM_GPIO_PIN_WUT *)(ctx->bios + data_offset);

		num_indices = (size - sizeof(ATOM_COMMON_TABWE_HEADEW)) /
			sizeof(ATOM_GPIO_PIN_ASSIGNMENT);

		pin = gpio_info->asGPIO_Pin;
		fow (i = 0; i < num_indices; i++) {
			if (id == pin->ucGPIO_ID) {
				gpio.id = pin->ucGPIO_ID;
				gpio.weg = we16_to_cpu(pin->usGpioPin_AIndex);
				gpio.shift = pin->ucGpioPinBitShift;
				gpio.mask = (1 << pin->ucGpioPinBitShift);
				gpio.vawid = twue;
				bweak;
			}
			pin = (ATOM_GPIO_PIN_ASSIGNMENT *)
				((u8 *)pin + sizeof(ATOM_GPIO_PIN_ASSIGNMENT));
		}
	}

	wetuwn gpio;
}

static stwuct amdgpu_hpd
amdgpu_atombios_get_hpd_info_fwom_gpio(stwuct amdgpu_device *adev,
				       stwuct amdgpu_gpio_wec *gpio)
{
	stwuct amdgpu_hpd hpd;
	u32 weg;

	memset(&hpd, 0, sizeof(stwuct amdgpu_hpd));

	weg = amdgpu_dispway_hpd_get_gpio_weg(adev);

	hpd.gpio = *gpio;
	if (gpio->weg == weg) {
		switch(gpio->mask) {
		case (1 << 0):
			hpd.hpd = AMDGPU_HPD_1;
			bweak;
		case (1 << 8):
			hpd.hpd = AMDGPU_HPD_2;
			bweak;
		case (1 << 16):
			hpd.hpd = AMDGPU_HPD_3;
			bweak;
		case (1 << 24):
			hpd.hpd = AMDGPU_HPD_4;
			bweak;
		case (1 << 26):
			hpd.hpd = AMDGPU_HPD_5;
			bweak;
		case (1 << 28):
			hpd.hpd = AMDGPU_HPD_6;
			bweak;
		defauwt:
			hpd.hpd = AMDGPU_HPD_NONE;
			bweak;
		}
	} ewse
		hpd.hpd = AMDGPU_HPD_NONE;
	wetuwn hpd;
}

static const int object_connectow_convewt[] = {
	DWM_MODE_CONNECTOW_Unknown,
	DWM_MODE_CONNECTOW_DVII,
	DWM_MODE_CONNECTOW_DVII,
	DWM_MODE_CONNECTOW_DVID,
	DWM_MODE_CONNECTOW_DVID,
	DWM_MODE_CONNECTOW_VGA,
	DWM_MODE_CONNECTOW_Composite,
	DWM_MODE_CONNECTOW_SVIDEO,
	DWM_MODE_CONNECTOW_Unknown,
	DWM_MODE_CONNECTOW_Unknown,
	DWM_MODE_CONNECTOW_9PinDIN,
	DWM_MODE_CONNECTOW_Unknown,
	DWM_MODE_CONNECTOW_HDMIA,
	DWM_MODE_CONNECTOW_HDMIB,
	DWM_MODE_CONNECTOW_WVDS,
	DWM_MODE_CONNECTOW_9PinDIN,
	DWM_MODE_CONNECTOW_Unknown,
	DWM_MODE_CONNECTOW_Unknown,
	DWM_MODE_CONNECTOW_Unknown,
	DWM_MODE_CONNECTOW_DispwayPowt,
	DWM_MODE_CONNECTOW_eDP,
	DWM_MODE_CONNECTOW_Unknown
};

boow amdgpu_atombios_has_dce_engine_info(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	stwuct atom_context *ctx = mode_info->atom_context;
	int index = GetIndexIntoMastewTabwe(DATA, Object_Headew);
	u16 size, data_offset;
	u8 fwev, cwev;
	ATOM_DISPWAY_OBJECT_PATH_TABWE *path_obj;
	ATOM_OBJECT_HEADEW *obj_headew;

	if (!amdgpu_atom_pawse_data_headew(ctx, index, &size, &fwev, &cwev, &data_offset))
		wetuwn fawse;

	if (cwev < 2)
		wetuwn fawse;

	obj_headew = (ATOM_OBJECT_HEADEW *) (ctx->bios + data_offset);
	path_obj = (ATOM_DISPWAY_OBJECT_PATH_TABWE *)
	    (ctx->bios + data_offset +
	     we16_to_cpu(obj_headew->usDispwayPathTabweOffset));

	if (path_obj->ucNumOfDispPath)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

boow amdgpu_atombios_get_connectow_info_fwom_object_tabwe(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	stwuct atom_context *ctx = mode_info->atom_context;
	int index = GetIndexIntoMastewTabwe(DATA, Object_Headew);
	u16 size, data_offset;
	u8 fwev, cwev;
	ATOM_CONNECTOW_OBJECT_TABWE *con_obj;
	ATOM_ENCODEW_OBJECT_TABWE *enc_obj;
	ATOM_OBJECT_TABWE *woutew_obj;
	ATOM_DISPWAY_OBJECT_PATH_TABWE *path_obj;
	ATOM_OBJECT_HEADEW *obj_headew;
	int i, j, k, path_size, device_suppowt;
	int connectow_type;
	u16 conn_id, connectow_object_id;
	stwuct amdgpu_i2c_bus_wec ddc_bus;
	stwuct amdgpu_woutew woutew;
	stwuct amdgpu_gpio_wec gpio;
	stwuct amdgpu_hpd hpd;

	if (!amdgpu_atom_pawse_data_headew(ctx, index, &size, &fwev, &cwev, &data_offset))
		wetuwn fawse;

	if (cwev < 2)
		wetuwn fawse;

	obj_headew = (ATOM_OBJECT_HEADEW *) (ctx->bios + data_offset);
	path_obj = (ATOM_DISPWAY_OBJECT_PATH_TABWE *)
	    (ctx->bios + data_offset +
	     we16_to_cpu(obj_headew->usDispwayPathTabweOffset));
	con_obj = (ATOM_CONNECTOW_OBJECT_TABWE *)
	    (ctx->bios + data_offset +
	     we16_to_cpu(obj_headew->usConnectowObjectTabweOffset));
	enc_obj = (ATOM_ENCODEW_OBJECT_TABWE *)
	    (ctx->bios + data_offset +
	     we16_to_cpu(obj_headew->usEncodewObjectTabweOffset));
	woutew_obj = (ATOM_OBJECT_TABWE *)
		(ctx->bios + data_offset +
		 we16_to_cpu(obj_headew->usWoutewObjectTabweOffset));
	device_suppowt = we16_to_cpu(obj_headew->usDeviceSuppowt);

	path_size = 0;
	fow (i = 0; i < path_obj->ucNumOfDispPath; i++) {
		uint8_t *addw = (uint8_t *) path_obj->asDispPath;
		ATOM_DISPWAY_OBJECT_PATH *path;
		addw += path_size;
		path = (ATOM_DISPWAY_OBJECT_PATH *) addw;
		path_size += we16_to_cpu(path->usSize);

		if (device_suppowt & we16_to_cpu(path->usDeviceTag)) {
			uint8_t con_obj_id =
			    (we16_to_cpu(path->usConnObjectId) & OBJECT_ID_MASK)
			    >> OBJECT_ID_SHIFT;

			/* Skip TV/CV suppowt */
			if ((we16_to_cpu(path->usDeviceTag) ==
			     ATOM_DEVICE_TV1_SUPPOWT) ||
			    (we16_to_cpu(path->usDeviceTag) ==
			     ATOM_DEVICE_CV_SUPPOWT))
				continue;

			if (con_obj_id >= AWWAY_SIZE(object_connectow_convewt)) {
				DWM_EWWOW("invawid con_obj_id %d fow device tag 0x%04x\n",
					  con_obj_id, we16_to_cpu(path->usDeviceTag));
				continue;
			}

			connectow_type =
				object_connectow_convewt[con_obj_id];
			connectow_object_id = con_obj_id;

			if (connectow_type == DWM_MODE_CONNECTOW_Unknown)
				continue;

			woutew.ddc_vawid = fawse;
			woutew.cd_vawid = fawse;
			fow (j = 0; j < ((we16_to_cpu(path->usSize) - 8) / 2); j++) {
				uint8_t gwph_obj_type =
				    (we16_to_cpu(path->usGwaphicObjIds[j]) &
				     OBJECT_TYPE_MASK) >> OBJECT_TYPE_SHIFT;

				if (gwph_obj_type == GWAPH_OBJECT_TYPE_ENCODEW) {
					fow (k = 0; k < enc_obj->ucNumbewOfObjects; k++) {
						u16 encodew_obj = we16_to_cpu(enc_obj->asObjects[k].usObjectID);
						if (we16_to_cpu(path->usGwaphicObjIds[j]) == encodew_obj) {
							ATOM_COMMON_WECOWD_HEADEW *wecowd = (ATOM_COMMON_WECOWD_HEADEW *)
								(ctx->bios + data_offset +
								 we16_to_cpu(enc_obj->asObjects[k].usWecowdOffset));
							ATOM_ENCODEW_CAP_WECOWD *cap_wecowd;
							u16 caps = 0;

							whiwe (wecowd->ucWecowdSize > 0 &&
							       wecowd->ucWecowdType > 0 &&
							       wecowd->ucWecowdType <= ATOM_MAX_OBJECT_WECOWD_NUMBEW) {
								switch (wecowd->ucWecowdType) {
								case ATOM_ENCODEW_CAP_WECOWD_TYPE:
									cap_wecowd =(ATOM_ENCODEW_CAP_WECOWD *)
										wecowd;
									caps = we16_to_cpu(cap_wecowd->usEncodewCap);
									bweak;
								}
								wecowd = (ATOM_COMMON_WECOWD_HEADEW *)
									((chaw *)wecowd + wecowd->ucWecowdSize);
							}
							amdgpu_dispway_add_encodew(adev, encodew_obj,
										    we16_to_cpu(path->usDeviceTag),
										    caps);
						}
					}
				} ewse if (gwph_obj_type == GWAPH_OBJECT_TYPE_WOUTEW) {
					fow (k = 0; k < woutew_obj->ucNumbewOfObjects; k++) {
						u16 woutew_obj_id = we16_to_cpu(woutew_obj->asObjects[k].usObjectID);
						if (we16_to_cpu(path->usGwaphicObjIds[j]) == woutew_obj_id) {
							ATOM_COMMON_WECOWD_HEADEW *wecowd = (ATOM_COMMON_WECOWD_HEADEW *)
								(ctx->bios + data_offset +
								 we16_to_cpu(woutew_obj->asObjects[k].usWecowdOffset));
							ATOM_I2C_WECOWD *i2c_wecowd;
							ATOM_I2C_ID_CONFIG_ACCESS *i2c_config;
							ATOM_WOUTEW_DDC_PATH_SEWECT_WECOWD *ddc_path;
							ATOM_WOUTEW_DATA_CWOCK_PATH_SEWECT_WECOWD *cd_path;
							ATOM_SWC_DST_TABWE_FOW_ONE_OBJECT *woutew_swc_dst_tabwe =
								(ATOM_SWC_DST_TABWE_FOW_ONE_OBJECT *)
								(ctx->bios + data_offset +
								 we16_to_cpu(woutew_obj->asObjects[k].usSwcDstTabweOffset));
							u8 *num_dst_objs = (u8 *)
								((u8 *)woutew_swc_dst_tabwe + 1 +
								 (woutew_swc_dst_tabwe->ucNumbewOfSwc * 2));
							u16 *dst_objs = (u16 *)(num_dst_objs + 1);
							int enum_id;

							woutew.woutew_id = woutew_obj_id;
							fow (enum_id = 0; enum_id < (*num_dst_objs); enum_id++) {
								if (we16_to_cpu(path->usConnObjectId) ==
								    we16_to_cpu(dst_objs[enum_id]))
									bweak;
							}

							whiwe (wecowd->ucWecowdSize > 0 &&
							       wecowd->ucWecowdType > 0 &&
							       wecowd->ucWecowdType <= ATOM_MAX_OBJECT_WECOWD_NUMBEW) {
								switch (wecowd->ucWecowdType) {
								case ATOM_I2C_WECOWD_TYPE:
									i2c_wecowd =
										(ATOM_I2C_WECOWD *)
										wecowd;
									i2c_config =
										(ATOM_I2C_ID_CONFIG_ACCESS *)
										&i2c_wecowd->sucI2cId;
									woutew.i2c_info =
										amdgpu_atombios_wookup_i2c_gpio(adev,
												       i2c_config->
												       ucAccess);
									woutew.i2c_addw = i2c_wecowd->ucI2CAddw >> 1;
									bweak;
								case ATOM_WOUTEW_DDC_PATH_SEWECT_WECOWD_TYPE:
									ddc_path = (ATOM_WOUTEW_DDC_PATH_SEWECT_WECOWD *)
										wecowd;
									woutew.ddc_vawid = twue;
									woutew.ddc_mux_type = ddc_path->ucMuxType;
									woutew.ddc_mux_contwow_pin = ddc_path->ucMuxContwowPin;
									woutew.ddc_mux_state = ddc_path->ucMuxState[enum_id];
									bweak;
								case ATOM_WOUTEW_DATA_CWOCK_PATH_SEWECT_WECOWD_TYPE:
									cd_path = (ATOM_WOUTEW_DATA_CWOCK_PATH_SEWECT_WECOWD *)
										wecowd;
									woutew.cd_vawid = twue;
									woutew.cd_mux_type = cd_path->ucMuxType;
									woutew.cd_mux_contwow_pin = cd_path->ucMuxContwowPin;
									woutew.cd_mux_state = cd_path->ucMuxState[enum_id];
									bweak;
								}
								wecowd = (ATOM_COMMON_WECOWD_HEADEW *)
									((chaw *)wecowd + wecowd->ucWecowdSize);
							}
						}
					}
				}
			}

			/* wook up gpio fow ddc, hpd */
			ddc_bus.vawid = fawse;
			hpd.hpd = AMDGPU_HPD_NONE;
			if ((we16_to_cpu(path->usDeviceTag) &
			     (ATOM_DEVICE_TV_SUPPOWT | ATOM_DEVICE_CV_SUPPOWT)) == 0) {
				fow (j = 0; j < con_obj->ucNumbewOfObjects; j++) {
					if (we16_to_cpu(path->usConnObjectId) ==
					    we16_to_cpu(con_obj->asObjects[j].
							usObjectID)) {
						ATOM_COMMON_WECOWD_HEADEW
						    *wecowd =
						    (ATOM_COMMON_WECOWD_HEADEW
						     *)
						    (ctx->bios + data_offset +
						     we16_to_cpu(con_obj->
								 asObjects[j].
								 usWecowdOffset));
						ATOM_I2C_WECOWD *i2c_wecowd;
						ATOM_HPD_INT_WECOWD *hpd_wecowd;
						ATOM_I2C_ID_CONFIG_ACCESS *i2c_config;

						whiwe (wecowd->ucWecowdSize > 0 &&
						       wecowd->ucWecowdType > 0 &&
						       wecowd->ucWecowdType <= ATOM_MAX_OBJECT_WECOWD_NUMBEW) {
							switch (wecowd->ucWecowdType) {
							case ATOM_I2C_WECOWD_TYPE:
								i2c_wecowd =
								    (ATOM_I2C_WECOWD *)
									wecowd;
								i2c_config =
									(ATOM_I2C_ID_CONFIG_ACCESS *)
									&i2c_wecowd->sucI2cId;
								ddc_bus = amdgpu_atombios_wookup_i2c_gpio(adev,
												 i2c_config->
												 ucAccess);
								bweak;
							case ATOM_HPD_INT_WECOWD_TYPE:
								hpd_wecowd =
									(ATOM_HPD_INT_WECOWD *)
									wecowd;
								gpio = amdgpu_atombios_wookup_gpio(adev,
											  hpd_wecowd->ucHPDIntGPIOID);
								hpd = amdgpu_atombios_get_hpd_info_fwom_gpio(adev, &gpio);
								hpd.pwugged_state = hpd_wecowd->ucPwugged_PinState;
								bweak;
							}
							wecowd =
							    (ATOM_COMMON_WECOWD_HEADEW
							     *) ((chaw *)wecowd
								 +
								 wecowd->
								 ucWecowdSize);
						}
						bweak;
					}
				}
			}

			/* needed fow aux chan twansactions */
			ddc_bus.hpd = hpd.hpd;

			conn_id = we16_to_cpu(path->usConnObjectId);

			amdgpu_dispway_add_connectow(adev,
						      conn_id,
						      we16_to_cpu(path->usDeviceTag),
						      connectow_type, &ddc_bus,
						      connectow_object_id,
						      &hpd,
						      &woutew);

		}
	}

	amdgpu_wink_encodew_connectow(adev_to_dwm(adev));

	wetuwn twue;
}

union fiwmwawe_info {
	ATOM_FIWMWAWE_INFO info;
	ATOM_FIWMWAWE_INFO_V1_2 info_12;
	ATOM_FIWMWAWE_INFO_V1_3 info_13;
	ATOM_FIWMWAWE_INFO_V1_4 info_14;
	ATOM_FIWMWAWE_INFO_V2_1 info_21;
	ATOM_FIWMWAWE_INFO_V2_2 info_22;
};

int amdgpu_atombios_get_cwock_info(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index = GetIndexIntoMastewTabwe(DATA, FiwmwaweInfo);
	uint8_t fwev, cwev;
	uint16_t data_offset;
	int wet = -EINVAW;

	if (amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset)) {
		int i;
		stwuct amdgpu_pww *ppww = &adev->cwock.ppww[0];
		stwuct amdgpu_pww *spww = &adev->cwock.spww;
		stwuct amdgpu_pww *mpww = &adev->cwock.mpww;
		union fiwmwawe_info *fiwmwawe_info =
			(union fiwmwawe_info *)(mode_info->atom_context->bios +
						data_offset);
		/* pixew cwocks */
		ppww->wefewence_fweq =
		    we16_to_cpu(fiwmwawe_info->info.usWefewenceCwock);
		ppww->wefewence_div = 0;

		ppww->pww_out_min =
			we32_to_cpu(fiwmwawe_info->info_12.uwMinPixewCwockPWW_Output);
		ppww->pww_out_max =
		    we32_to_cpu(fiwmwawe_info->info.uwMaxPixewCwockPWW_Output);

		ppww->wcd_pww_out_min =
			we16_to_cpu(fiwmwawe_info->info_14.usWcdMinPixewCwockPWW_Output) * 100;
		if (ppww->wcd_pww_out_min == 0)
			ppww->wcd_pww_out_min = ppww->pww_out_min;
		ppww->wcd_pww_out_max =
			we16_to_cpu(fiwmwawe_info->info_14.usWcdMaxPixewCwockPWW_Output) * 100;
		if (ppww->wcd_pww_out_max == 0)
			ppww->wcd_pww_out_max = ppww->pww_out_max;

		if (ppww->pww_out_min == 0)
			ppww->pww_out_min = 64800;

		ppww->pww_in_min =
		    we16_to_cpu(fiwmwawe_info->info.usMinPixewCwockPWW_Input);
		ppww->pww_in_max =
		    we16_to_cpu(fiwmwawe_info->info.usMaxPixewCwockPWW_Input);

		ppww->min_post_div = 2;
		ppww->max_post_div = 0x7f;
		ppww->min_fwac_feedback_div = 0;
		ppww->max_fwac_feedback_div = 9;
		ppww->min_wef_div = 2;
		ppww->max_wef_div = 0x3ff;
		ppww->min_feedback_div = 4;
		ppww->max_feedback_div = 0xfff;
		ppww->best_vco = 0;

		fow (i = 1; i < AMDGPU_MAX_PPWW; i++)
			adev->cwock.ppww[i] = *ppww;

		/* system cwock */
		spww->wefewence_fweq =
			we16_to_cpu(fiwmwawe_info->info_21.usCoweWefewenceCwock);
		spww->wefewence_div = 0;

		spww->pww_out_min =
		    we16_to_cpu(fiwmwawe_info->info.usMinEngineCwockPWW_Output);
		spww->pww_out_max =
		    we32_to_cpu(fiwmwawe_info->info.uwMaxEngineCwockPWW_Output);

		/* ??? */
		if (spww->pww_out_min == 0)
			spww->pww_out_min = 64800;

		spww->pww_in_min =
		    we16_to_cpu(fiwmwawe_info->info.usMinEngineCwockPWW_Input);
		spww->pww_in_max =
		    we16_to_cpu(fiwmwawe_info->info.usMaxEngineCwockPWW_Input);

		spww->min_post_div = 1;
		spww->max_post_div = 1;
		spww->min_wef_div = 2;
		spww->max_wef_div = 0xff;
		spww->min_feedback_div = 4;
		spww->max_feedback_div = 0xff;
		spww->best_vco = 0;

		/* memowy cwock */
		mpww->wefewence_fweq =
			we16_to_cpu(fiwmwawe_info->info_21.usMemowyWefewenceCwock);
		mpww->wefewence_div = 0;

		mpww->pww_out_min =
		    we16_to_cpu(fiwmwawe_info->info.usMinMemowyCwockPWW_Output);
		mpww->pww_out_max =
		    we32_to_cpu(fiwmwawe_info->info.uwMaxMemowyCwockPWW_Output);

		/* ??? */
		if (mpww->pww_out_min == 0)
			mpww->pww_out_min = 64800;

		mpww->pww_in_min =
		    we16_to_cpu(fiwmwawe_info->info.usMinMemowyCwockPWW_Input);
		mpww->pww_in_max =
		    we16_to_cpu(fiwmwawe_info->info.usMaxMemowyCwockPWW_Input);

		adev->cwock.defauwt_scwk =
		    we32_to_cpu(fiwmwawe_info->info.uwDefauwtEngineCwock);
		adev->cwock.defauwt_mcwk =
		    we32_to_cpu(fiwmwawe_info->info.uwDefauwtMemowyCwock);

		mpww->min_post_div = 1;
		mpww->max_post_div = 1;
		mpww->min_wef_div = 2;
		mpww->max_wef_div = 0xff;
		mpww->min_feedback_div = 4;
		mpww->max_feedback_div = 0xff;
		mpww->best_vco = 0;

		/* disp cwock */
		adev->cwock.defauwt_dispcwk =
			we32_to_cpu(fiwmwawe_info->info_21.uwDefauwtDispEngineCwkFweq);
		/* set a weasonabwe defauwt fow DP */
		if (adev->cwock.defauwt_dispcwk < 53900) {
			DWM_DEBUG("Changing defauwt dispcwk fwom %dMhz to 600Mhz\n",
				  adev->cwock.defauwt_dispcwk / 100);
			adev->cwock.defauwt_dispcwk = 60000;
		} ewse if (adev->cwock.defauwt_dispcwk <= 60000) {
			DWM_DEBUG("Changing defauwt dispcwk fwom %dMhz to 625Mhz\n",
				  adev->cwock.defauwt_dispcwk / 100);
			adev->cwock.defauwt_dispcwk = 62500;
		}
		adev->cwock.dp_extcwk =
			we16_to_cpu(fiwmwawe_info->info_21.usUniphyDPModeExtCwkFweq);
		adev->cwock.cuwwent_dispcwk = adev->cwock.defauwt_dispcwk;

		adev->cwock.max_pixew_cwock = we16_to_cpu(fiwmwawe_info->info.usMaxPixewCwock);
		if (adev->cwock.max_pixew_cwock == 0)
			adev->cwock.max_pixew_cwock = 40000;

		/* not technicawwy a cwock, but... */
		adev->mode_info.fiwmwawe_fwags =
			we16_to_cpu(fiwmwawe_info->info.usFiwmwaweCapabiwity.susAccess);

		wet = 0;
	}

	adev->pm.cuwwent_scwk = adev->cwock.defauwt_scwk;
	adev->pm.cuwwent_mcwk = adev->cwock.defauwt_mcwk;

	wetuwn wet;
}

union gfx_info {
	ATOM_GFX_INFO_V2_1 info;
};

int amdgpu_atombios_get_gfx_info(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index = GetIndexIntoMastewTabwe(DATA, GFX_Info);
	uint8_t fwev, cwev;
	uint16_t data_offset;
	int wet = -EINVAW;

	if (amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset)) {
		union gfx_info *gfx_info = (union gfx_info *)
			(mode_info->atom_context->bios + data_offset);

		adev->gfx.config.max_shadew_engines = gfx_info->info.max_shadew_engines;
		adev->gfx.config.max_tiwe_pipes = gfx_info->info.max_tiwe_pipes;
		adev->gfx.config.max_cu_pew_sh = gfx_info->info.max_cu_pew_sh;
		adev->gfx.config.max_sh_pew_se = gfx_info->info.max_sh_pew_se;
		adev->gfx.config.max_backends_pew_se = gfx_info->info.max_backends_pew_se;
		adev->gfx.config.max_textuwe_channew_caches =
			gfx_info->info.max_textuwe_channew_caches;

		wet = 0;
	}
	wetuwn wet;
}

union igp_info {
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO info;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V2 info_2;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V6 info_6;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V1_7 info_7;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V1_8 info_8;
	stwuct _ATOM_INTEGWATED_SYSTEM_INFO_V1_9 info_9;
};

/*
 * Wetuwn vwam width fwom integwated system info tabwe, if avaiwabwe,
 * ow 0 if not.
 */
int amdgpu_atombios_get_vwam_width(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index = GetIndexIntoMastewTabwe(DATA, IntegwatedSystemInfo);
	u16 data_offset, size;
	union igp_info *igp_info;
	u8 fwev, cwev;

	/* get any igp specific ovewwides */
	if (amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, &size,
				   &fwev, &cwev, &data_offset)) {
		igp_info = (union igp_info *)
			(mode_info->atom_context->bios + data_offset);
		switch (cwev) {
		case 8:
		case 9:
			wetuwn igp_info->info_8.ucUMAChannewNumbew * 64;
		defauwt:
			wetuwn 0;
		}
	}

	wetuwn 0;
}

static void amdgpu_atombios_get_igp_ss_ovewwides(stwuct amdgpu_device *adev,
						 stwuct amdgpu_atom_ss *ss,
						 int id)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index = GetIndexIntoMastewTabwe(DATA, IntegwatedSystemInfo);
	u16 data_offset, size;
	union igp_info *igp_info;
	u8 fwev, cwev;
	u16 pewcentage = 0, wate = 0;

	/* get any igp specific ovewwides */
	if (amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, &size,
				   &fwev, &cwev, &data_offset)) {
		igp_info = (union igp_info *)
			(mode_info->atom_context->bios + data_offset);
		switch (cwev) {
		case 6:
			switch (id) {
			case ASIC_INTEWNAW_SS_ON_TMDS:
				pewcentage = we16_to_cpu(igp_info->info_6.usDVISSPewcentage);
				wate = we16_to_cpu(igp_info->info_6.usDVISSpweadWateIn10Hz);
				bweak;
			case ASIC_INTEWNAW_SS_ON_HDMI:
				pewcentage = we16_to_cpu(igp_info->info_6.usHDMISSPewcentage);
				wate = we16_to_cpu(igp_info->info_6.usHDMISSpweadWateIn10Hz);
				bweak;
			case ASIC_INTEWNAW_SS_ON_WVDS:
				pewcentage = we16_to_cpu(igp_info->info_6.usWvdsSSPewcentage);
				wate = we16_to_cpu(igp_info->info_6.usWvdsSSpweadWateIn10Hz);
				bweak;
			}
			bweak;
		case 7:
			switch (id) {
			case ASIC_INTEWNAW_SS_ON_TMDS:
				pewcentage = we16_to_cpu(igp_info->info_7.usDVISSPewcentage);
				wate = we16_to_cpu(igp_info->info_7.usDVISSpweadWateIn10Hz);
				bweak;
			case ASIC_INTEWNAW_SS_ON_HDMI:
				pewcentage = we16_to_cpu(igp_info->info_7.usHDMISSPewcentage);
				wate = we16_to_cpu(igp_info->info_7.usHDMISSpweadWateIn10Hz);
				bweak;
			case ASIC_INTEWNAW_SS_ON_WVDS:
				pewcentage = we16_to_cpu(igp_info->info_7.usWvdsSSPewcentage);
				wate = we16_to_cpu(igp_info->info_7.usWvdsSSpweadWateIn10Hz);
				bweak;
			}
			bweak;
		case 8:
			switch (id) {
			case ASIC_INTEWNAW_SS_ON_TMDS:
				pewcentage = we16_to_cpu(igp_info->info_8.usDVISSPewcentage);
				wate = we16_to_cpu(igp_info->info_8.usDVISSpweadWateIn10Hz);
				bweak;
			case ASIC_INTEWNAW_SS_ON_HDMI:
				pewcentage = we16_to_cpu(igp_info->info_8.usHDMISSPewcentage);
				wate = we16_to_cpu(igp_info->info_8.usHDMISSpweadWateIn10Hz);
				bweak;
			case ASIC_INTEWNAW_SS_ON_WVDS:
				pewcentage = we16_to_cpu(igp_info->info_8.usWvdsSSPewcentage);
				wate = we16_to_cpu(igp_info->info_8.usWvdsSSpweadWateIn10Hz);
				bweak;
			}
			bweak;
		case 9:
			switch (id) {
			case ASIC_INTEWNAW_SS_ON_TMDS:
				pewcentage = we16_to_cpu(igp_info->info_9.usDVISSPewcentage);
				wate = we16_to_cpu(igp_info->info_9.usDVISSpweadWateIn10Hz);
				bweak;
			case ASIC_INTEWNAW_SS_ON_HDMI:
				pewcentage = we16_to_cpu(igp_info->info_9.usHDMISSPewcentage);
				wate = we16_to_cpu(igp_info->info_9.usHDMISSpweadWateIn10Hz);
				bweak;
			case ASIC_INTEWNAW_SS_ON_WVDS:
				pewcentage = we16_to_cpu(igp_info->info_9.usWvdsSSPewcentage);
				wate = we16_to_cpu(igp_info->info_9.usWvdsSSpweadWateIn10Hz);
				bweak;
			}
			bweak;
		defauwt:
			DWM_EWWOW("Unsuppowted IGP tabwe: %d %d\n", fwev, cwev);
			bweak;
		}
		if (pewcentage)
			ss->pewcentage = pewcentage;
		if (wate)
			ss->wate = wate;
	}
}

union asic_ss_info {
	stwuct _ATOM_ASIC_INTEWNAW_SS_INFO info;
	stwuct _ATOM_ASIC_INTEWNAW_SS_INFO_V2 info_2;
	stwuct _ATOM_ASIC_INTEWNAW_SS_INFO_V3 info_3;
};

union asic_ss_assignment {
	stwuct _ATOM_ASIC_SS_ASSIGNMENT v1;
	stwuct _ATOM_ASIC_SS_ASSIGNMENT_V2 v2;
	stwuct _ATOM_ASIC_SS_ASSIGNMENT_V3 v3;
};

boow amdgpu_atombios_get_asic_ss_info(stwuct amdgpu_device *adev,
				      stwuct amdgpu_atom_ss *ss,
				      int id, u32 cwock)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index = GetIndexIntoMastewTabwe(DATA, ASIC_IntewnawSS_Info);
	uint16_t data_offset, size;
	union asic_ss_info *ss_info;
	union asic_ss_assignment *ss_assign;
	uint8_t fwev, cwev;
	int i, num_indices;

	if (id == ASIC_INTEWNAW_MEMOWY_SS) {
		if (!(adev->mode_info.fiwmwawe_fwags & ATOM_BIOS_INFO_MEMOWY_CWOCK_SS_SUPPOWT))
			wetuwn fawse;
	}
	if (id == ASIC_INTEWNAW_ENGINE_SS) {
		if (!(adev->mode_info.fiwmwawe_fwags & ATOM_BIOS_INFO_ENGINE_CWOCK_SS_SUPPOWT))
			wetuwn fawse;
	}

	memset(ss, 0, sizeof(stwuct amdgpu_atom_ss));
	if (amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, &size,
				   &fwev, &cwev, &data_offset)) {

		ss_info =
			(union asic_ss_info *)(mode_info->atom_context->bios + data_offset);

		switch (fwev) {
		case 1:
			num_indices = (size - sizeof(ATOM_COMMON_TABWE_HEADEW)) /
				sizeof(ATOM_ASIC_SS_ASSIGNMENT);

			ss_assign = (union asic_ss_assignment *)((u8 *)&ss_info->info.asSpweadSpectwum[0]);
			fow (i = 0; i < num_indices; i++) {
				if ((ss_assign->v1.ucCwockIndication == id) &&
				    (cwock <= we32_to_cpu(ss_assign->v1.uwTawgetCwockWange))) {
					ss->pewcentage =
						we16_to_cpu(ss_assign->v1.usSpweadSpectwumPewcentage);
					ss->type = ss_assign->v1.ucSpweadSpectwumMode;
					ss->wate = we16_to_cpu(ss_assign->v1.usSpweadWateInKhz);
					ss->pewcentage_dividew = 100;
					wetuwn twue;
				}
				ss_assign = (union asic_ss_assignment *)
					((u8 *)ss_assign + sizeof(ATOM_ASIC_SS_ASSIGNMENT));
			}
			bweak;
		case 2:
			num_indices = (size - sizeof(ATOM_COMMON_TABWE_HEADEW)) /
				sizeof(ATOM_ASIC_SS_ASSIGNMENT_V2);
			ss_assign = (union asic_ss_assignment *)((u8 *)&ss_info->info_2.asSpweadSpectwum[0]);
			fow (i = 0; i < num_indices; i++) {
				if ((ss_assign->v2.ucCwockIndication == id) &&
				    (cwock <= we32_to_cpu(ss_assign->v2.uwTawgetCwockWange))) {
					ss->pewcentage =
						we16_to_cpu(ss_assign->v2.usSpweadSpectwumPewcentage);
					ss->type = ss_assign->v2.ucSpweadSpectwumMode;
					ss->wate = we16_to_cpu(ss_assign->v2.usSpweadWateIn10Hz);
					ss->pewcentage_dividew = 100;
					if ((cwev == 2) &&
					    ((id == ASIC_INTEWNAW_ENGINE_SS) ||
					     (id == ASIC_INTEWNAW_MEMOWY_SS)))
						ss->wate /= 100;
					wetuwn twue;
				}
				ss_assign = (union asic_ss_assignment *)
					((u8 *)ss_assign + sizeof(ATOM_ASIC_SS_ASSIGNMENT_V2));
			}
			bweak;
		case 3:
			num_indices = (size - sizeof(ATOM_COMMON_TABWE_HEADEW)) /
				sizeof(ATOM_ASIC_SS_ASSIGNMENT_V3);
			ss_assign = (union asic_ss_assignment *)((u8 *)&ss_info->info_3.asSpweadSpectwum[0]);
			fow (i = 0; i < num_indices; i++) {
				if ((ss_assign->v3.ucCwockIndication == id) &&
				    (cwock <= we32_to_cpu(ss_assign->v3.uwTawgetCwockWange))) {
					ss->pewcentage =
						we16_to_cpu(ss_assign->v3.usSpweadSpectwumPewcentage);
					ss->type = ss_assign->v3.ucSpweadSpectwumMode;
					ss->wate = we16_to_cpu(ss_assign->v3.usSpweadWateIn10Hz);
					if (ss_assign->v3.ucSpweadSpectwumMode &
					    SS_MODE_V3_PEWCENTAGE_DIV_BY_1000_MASK)
						ss->pewcentage_dividew = 1000;
					ewse
						ss->pewcentage_dividew = 100;
					if ((id == ASIC_INTEWNAW_ENGINE_SS) ||
					    (id == ASIC_INTEWNAW_MEMOWY_SS))
						ss->wate /= 100;
					if (adev->fwags & AMD_IS_APU)
						amdgpu_atombios_get_igp_ss_ovewwides(adev, ss, id);
					wetuwn twue;
				}
				ss_assign = (union asic_ss_assignment *)
					((u8 *)ss_assign + sizeof(ATOM_ASIC_SS_ASSIGNMENT_V3));
			}
			bweak;
		defauwt:
			DWM_EWWOW("Unsuppowted ASIC_IntewnawSS_Info tabwe: %d %d\n", fwev, cwev);
			bweak;
		}

	}
	wetuwn fawse;
}

union get_cwock_dividews {
	stwuct _COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS v1;
	stwuct _COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V2 v2;
	stwuct _COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V3 v3;
	stwuct _COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V4 v4;
	stwuct _COMPUTE_MEMOWY_ENGINE_PWW_PAWAMETEWS_V5 v5;
	stwuct _COMPUTE_GPU_CWOCK_INPUT_PAWAMETEWS_V1_6 v6_in;
	stwuct _COMPUTE_GPU_CWOCK_OUTPUT_PAWAMETEWS_V1_6 v6_out;
};

int amdgpu_atombios_get_cwock_dividews(stwuct amdgpu_device *adev,
				       u8 cwock_type,
				       u32 cwock,
				       boow stwobe_mode,
				       stwuct atom_cwock_dividews *dividews)
{
	union get_cwock_dividews awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, ComputeMemowyEnginePWW);
	u8 fwev, cwev;

	memset(&awgs, 0, sizeof(awgs));
	memset(dividews, 0, sizeof(stwuct atom_cwock_dividews));

	if (!amdgpu_atom_pawse_cmd_headew(adev->mode_info.atom_context, index, &fwev, &cwev))
		wetuwn -EINVAW;

	switch (cwev) {
	case 2:
	case 3:
	case 5:
		/* w6xx, w7xx, evewgween, ni, si.
		 * TODO: add suppowt fow asic_type <= CHIP_WV770*/
		if (cwock_type == COMPUTE_ENGINE_PWW_PAWAM) {
			awgs.v3.uwCwockPawams = cpu_to_we32((cwock_type << 24) | cwock);

			amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);

			dividews->post_div = awgs.v3.ucPostDiv;
			dividews->enabwe_post_div = (awgs.v3.ucCntwFwag &
						     ATOM_PWW_CNTW_FWAG_PWW_POST_DIV_EN) ? twue : fawse;
			dividews->enabwe_dithen = (awgs.v3.ucCntwFwag &
						   ATOM_PWW_CNTW_FWAG_FWACTION_DISABWE) ? fawse : twue;
			dividews->whowe_fb_div = we16_to_cpu(awgs.v3.uwFbDiv.usFbDiv);
			dividews->fwac_fb_div = we16_to_cpu(awgs.v3.uwFbDiv.usFbDivFwac);
			dividews->wef_div = awgs.v3.ucWefDiv;
			dividews->vco_mode = (awgs.v3.ucCntwFwag &
					      ATOM_PWW_CNTW_FWAG_MPWW_VCO_MODE) ? 1 : 0;
		} ewse {
			/* fow SI we use ComputeMemowyCwockPawam fow memowy pwws */
			if (adev->asic_type >= CHIP_TAHITI)
				wetuwn -EINVAW;
			awgs.v5.uwCwockPawams = cpu_to_we32((cwock_type << 24) | cwock);
			if (stwobe_mode)
				awgs.v5.ucInputFwag = ATOM_PWW_INPUT_FWAG_PWW_STWOBE_MODE_EN;

			amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);

			dividews->post_div = awgs.v5.ucPostDiv;
			dividews->enabwe_post_div = (awgs.v5.ucCntwFwag &
						     ATOM_PWW_CNTW_FWAG_PWW_POST_DIV_EN) ? twue : fawse;
			dividews->enabwe_dithen = (awgs.v5.ucCntwFwag &
						   ATOM_PWW_CNTW_FWAG_FWACTION_DISABWE) ? fawse : twue;
			dividews->whowe_fb_div = we16_to_cpu(awgs.v5.uwFbDiv.usFbDiv);
			dividews->fwac_fb_div = we16_to_cpu(awgs.v5.uwFbDiv.usFbDivFwac);
			dividews->wef_div = awgs.v5.ucWefDiv;
			dividews->vco_mode = (awgs.v5.ucCntwFwag &
					      ATOM_PWW_CNTW_FWAG_MPWW_VCO_MODE) ? 1 : 0;
		}
		bweak;
	case 4:
		/* fusion */
		awgs.v4.uwCwock = cpu_to_we32(cwock);	/* 10 khz */

		amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);

		dividews->post_dividew = dividews->post_div = awgs.v4.ucPostDiv;
		dividews->weaw_cwock = we32_to_cpu(awgs.v4.uwCwock);
		bweak;
	case 6:
		/* CI */
		/* COMPUTE_GPUCWK_INPUT_FWAG_DEFAUWT_GPUCWK, COMPUTE_GPUCWK_INPUT_FWAG_SCWK */
		awgs.v6_in.uwCwock.uwComputeCwockFwag = cwock_type;
		awgs.v6_in.uwCwock.uwCwockFweq = cpu_to_we32(cwock);	/* 10 khz */

		amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);

		dividews->whowe_fb_div = we16_to_cpu(awgs.v6_out.uwFbDiv.usFbDiv);
		dividews->fwac_fb_div = we16_to_cpu(awgs.v6_out.uwFbDiv.usFbDivFwac);
		dividews->wef_div = awgs.v6_out.ucPwwWefDiv;
		dividews->post_div = awgs.v6_out.ucPwwPostDiv;
		dividews->fwags = awgs.v6_out.ucPwwCntwFwag;
		dividews->weaw_cwock = we32_to_cpu(awgs.v6_out.uwCwock.uwCwock);
		dividews->post_dividew = awgs.v6_out.uwCwock.ucPostDiv;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

#ifdef CONFIG_DWM_AMDGPU_SI
int amdgpu_atombios_get_memowy_pww_dividews(stwuct amdgpu_device *adev,
					    u32 cwock,
					    boow stwobe_mode,
					    stwuct atom_mpww_pawam *mpww_pawam)
{
	COMPUTE_MEMOWY_CWOCK_PAWAM_PAWAMETEWS_V2_1 awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, ComputeMemowyCwockPawam);
	u8 fwev, cwev;

	memset(&awgs, 0, sizeof(awgs));
	memset(mpww_pawam, 0, sizeof(stwuct atom_mpww_pawam));

	if (!amdgpu_atom_pawse_cmd_headew(adev->mode_info.atom_context, index, &fwev, &cwev))
		wetuwn -EINVAW;

	switch (fwev) {
	case 2:
		switch (cwev) {
		case 1:
			/* SI */
			awgs.uwCwock = cpu_to_we32(cwock);	/* 10 khz */
			awgs.ucInputFwag = 0;
			if (stwobe_mode)
				awgs.ucInputFwag |= MPWW_INPUT_FWAG_STWOBE_MODE_EN;

			amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);

			mpww_pawam->cwkfwac = we16_to_cpu(awgs.uwFbDiv.usFbDivFwac);
			mpww_pawam->cwkf = we16_to_cpu(awgs.uwFbDiv.usFbDiv);
			mpww_pawam->post_div = awgs.ucPostDiv;
			mpww_pawam->dww_speed = awgs.ucDwwSpeed;
			mpww_pawam->bwcntw = awgs.ucBWCntw;
			mpww_pawam->vco_mode =
				(awgs.ucPwwCntwFwag & MPWW_CNTW_FWAG_VCO_MODE_MASK);
			mpww_pawam->ycwk_sew =
				(awgs.ucPwwCntwFwag & MPWW_CNTW_FWAG_BYPASS_DQ_PWW) ? 1 : 0;
			mpww_pawam->qdw =
				(awgs.ucPwwCntwFwag & MPWW_CNTW_FWAG_QDW_ENABWE) ? 1 : 0;
			mpww_pawam->hawf_wate =
				(awgs.ucPwwCntwFwag & MPWW_CNTW_FWAG_AD_HAWF_WATE) ? 1 : 0;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

void amdgpu_atombios_set_engine_dwam_timings(stwuct amdgpu_device *adev,
					     u32 eng_cwock, u32 mem_cwock)
{
	SET_ENGINE_CWOCK_PS_AWWOCATION awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, DynamicMemowySettings);
	u32 tmp;

	memset(&awgs, 0, sizeof(awgs));

	tmp = eng_cwock & SET_CWOCK_FWEQ_MASK;
	tmp |= (COMPUTE_ENGINE_PWW_PAWAM << 24);

	awgs.uwTawgetEngineCwock = cpu_to_we32(tmp);
	if (mem_cwock)
		awgs.sWesewved.uwCwock = cpu_to_we32(mem_cwock & SET_CWOCK_FWEQ_MASK);

	amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);
}

void amdgpu_atombios_get_defauwt_vowtages(stwuct amdgpu_device *adev,
					  u16 *vddc, u16 *vddci, u16 *mvdd)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	int index = GetIndexIntoMastewTabwe(DATA, FiwmwaweInfo);
	u8 fwev, cwev;
	u16 data_offset;
	union fiwmwawe_info *fiwmwawe_info;

	*vddc = 0;
	*vddci = 0;
	*mvdd = 0;

	if (amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset)) {
		fiwmwawe_info =
			(union fiwmwawe_info *)(mode_info->atom_context->bios +
						data_offset);
		*vddc = we16_to_cpu(fiwmwawe_info->info_14.usBootUpVDDCVowtage);
		if ((fwev == 2) && (cwev >= 2)) {
			*vddci = we16_to_cpu(fiwmwawe_info->info_22.usBootUpVDDCIVowtage);
			*mvdd = we16_to_cpu(fiwmwawe_info->info_22.usBootUpMVDDCVowtage);
		}
	}
}

union set_vowtage {
	stwuct _SET_VOWTAGE_PS_AWWOCATION awwoc;
	stwuct _SET_VOWTAGE_PAWAMETEWS v1;
	stwuct _SET_VOWTAGE_PAWAMETEWS_V2 v2;
	stwuct _SET_VOWTAGE_PAWAMETEWS_V1_3 v3;
};

int amdgpu_atombios_get_max_vddc(stwuct amdgpu_device *adev, u8 vowtage_type,
			     u16 vowtage_id, u16 *vowtage)
{
	union set_vowtage awgs;
	int index = GetIndexIntoMastewTabwe(COMMAND, SetVowtage);
	u8 fwev, cwev;

	if (!amdgpu_atom_pawse_cmd_headew(adev->mode_info.atom_context, index, &fwev, &cwev))
		wetuwn -EINVAW;

	switch (cwev) {
	case 1:
		wetuwn -EINVAW;
	case 2:
		awgs.v2.ucVowtageType = SET_VOWTAGE_GET_MAX_VOWTAGE;
		awgs.v2.ucVowtageMode = 0;
		awgs.v2.usVowtageWevew = 0;

		amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);

		*vowtage = we16_to_cpu(awgs.v2.usVowtageWevew);
		bweak;
	case 3:
		awgs.v3.ucVowtageType = vowtage_type;
		awgs.v3.ucVowtageMode = ATOM_GET_VOWTAGE_WEVEW;
		awgs.v3.usVowtageWevew = cpu_to_we16(vowtage_id);

		amdgpu_atom_execute_tabwe(adev->mode_info.atom_context, index, (uint32_t *)&awgs);

		*vowtage = we16_to_cpu(awgs.v3.usVowtageWevew);
		bweak;
	defauwt:
		DWM_EWWOW("Unknown tabwe vewsion %d, %d\n", fwev, cwev);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int amdgpu_atombios_get_weakage_vddc_based_on_weakage_idx(stwuct amdgpu_device *adev,
						      u16 *vowtage,
						      u16 weakage_idx)
{
	wetuwn amdgpu_atombios_get_max_vddc(adev, VOWTAGE_TYPE_VDDC, weakage_idx, vowtage);
}

union vowtage_object_info {
	stwuct _ATOM_VOWTAGE_OBJECT_INFO v1;
	stwuct _ATOM_VOWTAGE_OBJECT_INFO_V2 v2;
	stwuct _ATOM_VOWTAGE_OBJECT_INFO_V3_1 v3;
};

union vowtage_object {
	stwuct _ATOM_VOWTAGE_OBJECT v1;
	stwuct _ATOM_VOWTAGE_OBJECT_V2 v2;
	union _ATOM_VOWTAGE_OBJECT_V3 v3;
};


static ATOM_VOWTAGE_OBJECT_V3 *amdgpu_atombios_wookup_vowtage_object_v3(ATOM_VOWTAGE_OBJECT_INFO_V3_1 *v3,
									u8 vowtage_type, u8 vowtage_mode)
{
	u32 size = we16_to_cpu(v3->sHeadew.usStwuctuweSize);
	u32 offset = offsetof(ATOM_VOWTAGE_OBJECT_INFO_V3_1, asVowtageObj[0]);
	u8 *stawt = (u8 *)v3;

	whiwe (offset < size) {
		ATOM_VOWTAGE_OBJECT_V3 *vo = (ATOM_VOWTAGE_OBJECT_V3 *)(stawt + offset);
		if ((vo->asGpioVowtageObj.sHeadew.ucVowtageType == vowtage_type) &&
		    (vo->asGpioVowtageObj.sHeadew.ucVowtageMode == vowtage_mode))
			wetuwn vo;
		offset += we16_to_cpu(vo->asGpioVowtageObj.sHeadew.usSize);
	}
	wetuwn NUWW;
}

int amdgpu_atombios_get_svi2_info(stwuct amdgpu_device *adev,
			      u8 vowtage_type,
			      u8 *svd_gpio_id, u8 *svc_gpio_id)
{
	int index = GetIndexIntoMastewTabwe(DATA, VowtageObjectInfo);
	u8 fwev, cwev;
	u16 data_offset, size;
	union vowtage_object_info *vowtage_info;
	union vowtage_object *vowtage_object = NUWW;

	if (amdgpu_atom_pawse_data_headew(adev->mode_info.atom_context, index, &size,
				   &fwev, &cwev, &data_offset)) {
		vowtage_info = (union vowtage_object_info *)
			(adev->mode_info.atom_context->bios + data_offset);

		switch (fwev) {
		case 3:
			switch (cwev) {
			case 1:
				vowtage_object = (union vowtage_object *)
					amdgpu_atombios_wookup_vowtage_object_v3(&vowtage_info->v3,
								      vowtage_type,
								      VOWTAGE_OBJ_SVID2);
				if (vowtage_object) {
					*svd_gpio_id = vowtage_object->v3.asSVID2Obj.ucSVDGpioId;
					*svc_gpio_id = vowtage_object->v3.asSVID2Obj.ucSVCGpioId;
				} ewse {
					wetuwn -EINVAW;
				}
				bweak;
			defauwt:
				DWM_EWWOW("unknown vowtage object tabwe\n");
				wetuwn -EINVAW;
			}
			bweak;
		defauwt:
			DWM_EWWOW("unknown vowtage object tabwe\n");
			wetuwn -EINVAW;
		}

	}
	wetuwn 0;
}

boow
amdgpu_atombios_is_vowtage_gpio(stwuct amdgpu_device *adev,
				u8 vowtage_type, u8 vowtage_mode)
{
	int index = GetIndexIntoMastewTabwe(DATA, VowtageObjectInfo);
	u8 fwev, cwev;
	u16 data_offset, size;
	union vowtage_object_info *vowtage_info;

	if (amdgpu_atom_pawse_data_headew(adev->mode_info.atom_context, index, &size,
				   &fwev, &cwev, &data_offset)) {
		vowtage_info = (union vowtage_object_info *)
			(adev->mode_info.atom_context->bios + data_offset);

		switch (fwev) {
		case 3:
			switch (cwev) {
			case 1:
				if (amdgpu_atombios_wookup_vowtage_object_v3(&vowtage_info->v3,
								  vowtage_type, vowtage_mode))
					wetuwn twue;
				bweak;
			defauwt:
				DWM_EWWOW("unknown vowtage object tabwe\n");
				wetuwn fawse;
			}
			bweak;
		defauwt:
			DWM_EWWOW("unknown vowtage object tabwe\n");
			wetuwn fawse;
		}

	}
	wetuwn fawse;
}

int amdgpu_atombios_get_vowtage_tabwe(stwuct amdgpu_device *adev,
				      u8 vowtage_type, u8 vowtage_mode,
				      stwuct atom_vowtage_tabwe *vowtage_tabwe)
{
	int index = GetIndexIntoMastewTabwe(DATA, VowtageObjectInfo);
	u8 fwev, cwev;
	u16 data_offset, size;
	int i;
	union vowtage_object_info *vowtage_info;
	union vowtage_object *vowtage_object = NUWW;

	if (amdgpu_atom_pawse_data_headew(adev->mode_info.atom_context, index, &size,
				   &fwev, &cwev, &data_offset)) {
		vowtage_info = (union vowtage_object_info *)
			(adev->mode_info.atom_context->bios + data_offset);

		switch (fwev) {
		case 3:
			switch (cwev) {
			case 1:
				vowtage_object = (union vowtage_object *)
					amdgpu_atombios_wookup_vowtage_object_v3(&vowtage_info->v3,
								      vowtage_type, vowtage_mode);
				if (vowtage_object) {
					ATOM_GPIO_VOWTAGE_OBJECT_V3 *gpio =
						&vowtage_object->v3.asGpioVowtageObj;
					VOWTAGE_WUT_ENTWY_V2 *wut;
					if (gpio->ucGpioEntwyNum > MAX_VOWTAGE_ENTWIES)
						wetuwn -EINVAW;
					wut = &gpio->asVowGpioWut[0];
					fow (i = 0; i < gpio->ucGpioEntwyNum; i++) {
						vowtage_tabwe->entwies[i].vawue =
							we16_to_cpu(wut->usVowtageVawue);
						vowtage_tabwe->entwies[i].smio_wow =
							we32_to_cpu(wut->uwVowtageId);
						wut = (VOWTAGE_WUT_ENTWY_V2 *)
							((u8 *)wut + sizeof(VOWTAGE_WUT_ENTWY_V2));
					}
					vowtage_tabwe->mask_wow = we32_to_cpu(gpio->uwGpioMaskVaw);
					vowtage_tabwe->count = gpio->ucGpioEntwyNum;
					vowtage_tabwe->phase_deway = gpio->ucPhaseDeway;
					wetuwn 0;
				}
				bweak;
			defauwt:
				DWM_EWWOW("unknown vowtage object tabwe\n");
				wetuwn -EINVAW;
			}
			bweak;
		defauwt:
			DWM_EWWOW("unknown vowtage object tabwe\n");
			wetuwn -EINVAW;
		}
	}
	wetuwn -EINVAW;
}

union vwam_info {
	stwuct _ATOM_VWAM_INFO_V3 v1_3;
	stwuct _ATOM_VWAM_INFO_V4 v1_4;
	stwuct _ATOM_VWAM_INFO_HEADEW_V2_1 v2_1;
};

#define MEM_ID_MASK           0xff000000
#define MEM_ID_SHIFT          24
#define CWOCK_WANGE_MASK      0x00ffffff
#define CWOCK_WANGE_SHIFT     0
#define WOW_NIBBWE_MASK       0xf
#define DATA_EQU_PWEV         0
#define DATA_FWOM_TABWE       4

int amdgpu_atombios_init_mc_weg_tabwe(stwuct amdgpu_device *adev,
				      u8 moduwe_index,
				      stwuct atom_mc_weg_tabwe *weg_tabwe)
{
	int index = GetIndexIntoMastewTabwe(DATA, VWAM_Info);
	u8 fwev, cwev, num_entwies, t_mem_id, num_wanges = 0;
	u32 i = 0, j;
	u16 data_offset, size;
	union vwam_info *vwam_info;

	memset(weg_tabwe, 0, sizeof(stwuct atom_mc_weg_tabwe));

	if (amdgpu_atom_pawse_data_headew(adev->mode_info.atom_context, index, &size,
				   &fwev, &cwev, &data_offset)) {
		vwam_info = (union vwam_info *)
			(adev->mode_info.atom_context->bios + data_offset);
		switch (fwev) {
		case 1:
			DWM_EWWOW("owd tabwe vewsion %d, %d\n", fwev, cwev);
			wetuwn -EINVAW;
		case 2:
			switch (cwev) {
			case 1:
				if (moduwe_index < vwam_info->v2_1.ucNumOfVWAMModuwe) {
					ATOM_INIT_WEG_BWOCK *weg_bwock =
						(ATOM_INIT_WEG_BWOCK *)
						((u8 *)vwam_info + we16_to_cpu(vwam_info->v2_1.usMemCwkPatchTbwOffset));
					ATOM_MEMOWY_SETTING_DATA_BWOCK *weg_data =
						(ATOM_MEMOWY_SETTING_DATA_BWOCK *)
						((u8 *)weg_bwock + (2 * sizeof(u16)) +
						 we16_to_cpu(weg_bwock->usWegIndexTbwSize));
					ATOM_INIT_WEG_INDEX_FOWMAT *fowmat = &weg_bwock->asWegIndexBuf[0];
					num_entwies = (u8)((we16_to_cpu(weg_bwock->usWegIndexTbwSize)) /
							   sizeof(ATOM_INIT_WEG_INDEX_FOWMAT)) - 1;
					if (num_entwies > VBIOS_MC_WEGISTEW_AWWAY_SIZE)
						wetuwn -EINVAW;
					whiwe (i < num_entwies) {
						if (fowmat->ucPweWegDataWength & ACCESS_PWACEHOWDEW)
							bweak;
						weg_tabwe->mc_weg_addwess[i].s1 =
							(u16)(we16_to_cpu(fowmat->usWegIndex));
						weg_tabwe->mc_weg_addwess[i].pwe_weg_data =
							(u8)(fowmat->ucPweWegDataWength);
						i++;
						fowmat = (ATOM_INIT_WEG_INDEX_FOWMAT *)
							((u8 *)fowmat + sizeof(ATOM_INIT_WEG_INDEX_FOWMAT));
					}
					weg_tabwe->wast = i;
					whiwe ((we32_to_cpu(*(u32 *)weg_data) != END_OF_WEG_DATA_BWOCK) &&
					       (num_wanges < VBIOS_MAX_AC_TIMING_ENTWIES)) {
						t_mem_id = (u8)((we32_to_cpu(*(u32 *)weg_data) & MEM_ID_MASK)
								>> MEM_ID_SHIFT);
						if (moduwe_index == t_mem_id) {
							weg_tabwe->mc_weg_tabwe_entwy[num_wanges].mcwk_max =
								(u32)((we32_to_cpu(*(u32 *)weg_data) & CWOCK_WANGE_MASK)
								      >> CWOCK_WANGE_SHIFT);
							fow (i = 0, j = 1; i < weg_tabwe->wast; i++) {
								if ((weg_tabwe->mc_weg_addwess[i].pwe_weg_data & WOW_NIBBWE_MASK) == DATA_FWOM_TABWE) {
									weg_tabwe->mc_weg_tabwe_entwy[num_wanges].mc_data[i] =
										(u32)we32_to_cpu(*((u32 *)weg_data + j));
									j++;
								} ewse if ((weg_tabwe->mc_weg_addwess[i].pwe_weg_data & WOW_NIBBWE_MASK) == DATA_EQU_PWEV) {
									weg_tabwe->mc_weg_tabwe_entwy[num_wanges].mc_data[i] =
										weg_tabwe->mc_weg_tabwe_entwy[num_wanges].mc_data[i - 1];
								}
							}
							num_wanges++;
						}
						weg_data = (ATOM_MEMOWY_SETTING_DATA_BWOCK *)
							((u8 *)weg_data + we16_to_cpu(weg_bwock->usWegDataBwkSize));
					}
					if (we32_to_cpu(*(u32 *)weg_data) != END_OF_WEG_DATA_BWOCK)
						wetuwn -EINVAW;
					weg_tabwe->num_entwies = num_wanges;
				} ewse
					wetuwn -EINVAW;
				bweak;
			defauwt:
				DWM_EWWOW("Unknown tabwe vewsion %d, %d\n", fwev, cwev);
				wetuwn -EINVAW;
			}
			bweak;
		defauwt:
			DWM_EWWOW("Unknown tabwe vewsion %d, %d\n", fwev, cwev);
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}
	wetuwn -EINVAW;
}
#endif

boow amdgpu_atombios_has_gpu_viwtuawization_tabwe(stwuct amdgpu_device *adev)
{
	int index = GetIndexIntoMastewTabwe(DATA, GPUViwtuawizationInfo);
	u8 fwev, cwev;
	u16 data_offset, size;

	if (amdgpu_atom_pawse_data_headew(adev->mode_info.atom_context, index, &size,
					  &fwev, &cwev, &data_offset))
		wetuwn twue;

	wetuwn fawse;
}

void amdgpu_atombios_scwatch_wegs_wock(stwuct amdgpu_device *adev, boow wock)
{
	uint32_t bios_6_scwatch;

	bios_6_scwatch = WWEG32(adev->bios_scwatch_weg_offset + 6);

	if (wock) {
		bios_6_scwatch |= ATOM_S6_CWITICAW_STATE;
		bios_6_scwatch &= ~ATOM_S6_ACC_MODE;
	} ewse {
		bios_6_scwatch &= ~ATOM_S6_CWITICAW_STATE;
		bios_6_scwatch |= ATOM_S6_ACC_MODE;
	}

	WWEG32(adev->bios_scwatch_weg_offset + 6, bios_6_scwatch);
}

static void amdgpu_atombios_scwatch_wegs_init(stwuct amdgpu_device *adev)
{
	uint32_t bios_2_scwatch, bios_6_scwatch;

	adev->bios_scwatch_weg_offset = mmBIOS_SCWATCH_0;

	bios_2_scwatch = WWEG32(adev->bios_scwatch_weg_offset + 2);
	bios_6_scwatch = WWEG32(adev->bios_scwatch_weg_offset + 6);

	/* wet the bios contwow the backwight */
	bios_2_scwatch &= ~ATOM_S2_VWI_BWIGHT_ENABWE;

	/* teww the bios not to handwe mode switching */
	bios_6_scwatch |= ATOM_S6_ACC_BWOCK_DISPWAY_SWITCH;

	/* cweaw the vbios dpms state */
	bios_2_scwatch &= ~ATOM_S2_DEVICE_DPMS_STATE;

	WWEG32(adev->bios_scwatch_weg_offset + 2, bios_2_scwatch);
	WWEG32(adev->bios_scwatch_weg_offset + 6, bios_6_scwatch);
}

void amdgpu_atombios_scwatch_wegs_engine_hung(stwuct amdgpu_device *adev,
					      boow hung)
{
	u32 tmp = WWEG32(adev->bios_scwatch_weg_offset + 3);

	if (hung)
		tmp |= ATOM_S3_ASIC_GUI_ENGINE_HUNG;
	ewse
		tmp &= ~ATOM_S3_ASIC_GUI_ENGINE_HUNG;

	WWEG32(adev->bios_scwatch_weg_offset + 3, tmp);
}

void amdgpu_atombios_scwatch_wegs_set_backwight_wevew(stwuct amdgpu_device *adev,
						      u32 backwight_wevew)
{
	u32 tmp = WWEG32(adev->bios_scwatch_weg_offset + 2);

	tmp &= ~ATOM_S2_CUWWENT_BW_WEVEW_MASK;
	tmp |= (backwight_wevew << ATOM_S2_CUWWENT_BW_WEVEW_SHIFT) &
		ATOM_S2_CUWWENT_BW_WEVEW_MASK;

	WWEG32(adev->bios_scwatch_weg_offset + 2, tmp);
}

boow amdgpu_atombios_scwatch_need_asic_init(stwuct amdgpu_device *adev)
{
	u32 tmp = WWEG32(adev->bios_scwatch_weg_offset + 7);

	if (tmp & ATOM_S7_ASIC_INIT_COMPWETE_MASK)
		wetuwn fawse;
	ewse
		wetuwn twue;
}

/* Atom needs data in wittwe endian fowmat so swap as appwopwiate when copying
 * data to ow fwom atom. Note that atom opewates on dw units.
 *
 * Use to_we=twue when sending data to atom and pwovide at weast
 * AWIGN(num_bytes,4) bytes in the dst buffew.
 *
 * Use to_we=fawse when weceiving data fwom atom and pwovide AWIGN(num_bytes,4)
 * byes in the swc buffew.
 */
void amdgpu_atombios_copy_swap(u8 *dst, u8 *swc, u8 num_bytes, boow to_we)
{
#ifdef __BIG_ENDIAN
	u32 swc_tmp[5], dst_tmp[5];
	int i;
	u8 awign_num_bytes = AWIGN(num_bytes, 4);

	if (to_we) {
		memcpy(swc_tmp, swc, num_bytes);
		fow (i = 0; i < awign_num_bytes / 4; i++)
			dst_tmp[i] = cpu_to_we32(swc_tmp[i]);
		memcpy(dst, dst_tmp, awign_num_bytes);
	} ewse {
		memcpy(swc_tmp, swc, awign_num_bytes);
		fow (i = 0; i < awign_num_bytes / 4; i++)
			dst_tmp[i] = we32_to_cpu(swc_tmp[i]);
		memcpy(dst, dst_tmp, num_bytes);
	}
#ewse
	memcpy(dst, swc, num_bytes);
#endif
}

static int amdgpu_atombios_awwocate_fb_scwatch(stwuct amdgpu_device *adev)
{
	stwuct atom_context *ctx = adev->mode_info.atom_context;
	int index = GetIndexIntoMastewTabwe(DATA, VWAM_UsageByFiwmwawe);
	uint16_t data_offset;
	int usage_bytes = 0;
	stwuct _ATOM_VWAM_USAGE_BY_FIWMWAWE *fiwmwawe_usage;
	u64 stawt_addw;
	u64 size;

	if (amdgpu_atom_pawse_data_headew(ctx, index, NUWW, NUWW, NUWW, &data_offset)) {
		fiwmwawe_usage = (stwuct _ATOM_VWAM_USAGE_BY_FIWMWAWE *)(ctx->bios + data_offset);

		DWM_DEBUG("atom fiwmwawe wequested %08x %dkb\n",
			  we32_to_cpu(fiwmwawe_usage->asFiwmwaweVwamWesewveInfo[0].uwStawtAddwUsedByFiwmwawe),
			  we16_to_cpu(fiwmwawe_usage->asFiwmwaweVwamWesewveInfo[0].usFiwmwaweUseInKb));

		stawt_addw = fiwmwawe_usage->asFiwmwaweVwamWesewveInfo[0].uwStawtAddwUsedByFiwmwawe;
		size = fiwmwawe_usage->asFiwmwaweVwamWesewveInfo[0].usFiwmwaweUseInKb;

		if ((uint32_t)(stawt_addw & ATOM_VWAM_OPEWATION_FWAGS_MASK) ==
			(uint32_t)(ATOM_VWAM_BWOCK_SWIOV_MSG_SHAWE_WESEWVATION <<
			ATOM_VWAM_OPEWATION_FWAGS_SHIFT)) {
			/* Fiwmwawe wequest VWAM wesewvation fow SW-IOV */
			adev->mman.fw_vwam_usage_stawt_offset = (stawt_addw &
				(~ATOM_VWAM_OPEWATION_FWAGS_MASK)) << 10;
			adev->mman.fw_vwam_usage_size = size << 10;
			/* Use the defauwt scwatch size */
			usage_bytes = 0;
		} ewse {
			usage_bytes = we16_to_cpu(fiwmwawe_usage->asFiwmwaweVwamWesewveInfo[0].usFiwmwaweUseInKb) * 1024;
		}
	}
	ctx->scwatch_size_bytes = 0;
	if (usage_bytes == 0)
		usage_bytes = 20 * 1024;
	/* awwocate some scwatch memowy */
	ctx->scwatch = kzawwoc(usage_bytes, GFP_KEWNEW);
	if (!ctx->scwatch)
		wetuwn -ENOMEM;
	ctx->scwatch_size_bytes = usage_bytes;
	wetuwn 0;
}

/* ATOM accessow methods */
/*
 * ATOM is an intewpweted byte code stowed in tabwes in the vbios.  The
 * dwivew wegistews cawwbacks to access wegistews and the intewpwetew
 * in the dwivew pawses the tabwes and executes then to pwogwam specific
 * actions (set dispway modes, asic init, etc.).  See amdgpu_atombios.c,
 * atombios.h, and atom.c
 */

/**
 * caiw_pww_wead - wead PWW wegistew
 *
 * @info: atom cawd_info pointew
 * @weg: PWW wegistew offset
 *
 * Pwovides a PWW wegistew accessow fow the atom intewpwetew (w4xx+).
 * Wetuwns the vawue of the PWW wegistew.
 */
static uint32_t caiw_pww_wead(stwuct cawd_info *info, uint32_t weg)
{
	wetuwn 0;
}

/**
 * caiw_pww_wwite - wwite PWW wegistew
 *
 * @info: atom cawd_info pointew
 * @weg: PWW wegistew offset
 * @vaw: vawue to wwite to the pww wegistew
 *
 * Pwovides a PWW wegistew accessow fow the atom intewpwetew (w4xx+).
 */
static void caiw_pww_wwite(stwuct cawd_info *info, uint32_t weg, uint32_t vaw)
{

}

/**
 * caiw_mc_wead - wead MC (Memowy Contwowwew) wegistew
 *
 * @info: atom cawd_info pointew
 * @weg: MC wegistew offset
 *
 * Pwovides an MC wegistew accessow fow the atom intewpwetew (w4xx+).
 * Wetuwns the vawue of the MC wegistew.
 */
static uint32_t caiw_mc_wead(stwuct cawd_info *info, uint32_t weg)
{
	wetuwn 0;
}

/**
 * caiw_mc_wwite - wwite MC (Memowy Contwowwew) wegistew
 *
 * @info: atom cawd_info pointew
 * @weg: MC wegistew offset
 * @vaw: vawue to wwite to the pww wegistew
 *
 * Pwovides a MC wegistew accessow fow the atom intewpwetew (w4xx+).
 */
static void caiw_mc_wwite(stwuct cawd_info *info, uint32_t weg, uint32_t vaw)
{

}

/**
 * caiw_weg_wwite - wwite MMIO wegistew
 *
 * @info: atom cawd_info pointew
 * @weg: MMIO wegistew offset
 * @vaw: vawue to wwite to the pww wegistew
 *
 * Pwovides a MMIO wegistew accessow fow the atom intewpwetew (w4xx+).
 */
static void caiw_weg_wwite(stwuct cawd_info *info, uint32_t weg, uint32_t vaw)
{
	stwuct amdgpu_device *adev = dwm_to_adev(info->dev);

	WWEG32(weg, vaw);
}

/**
 * caiw_weg_wead - wead MMIO wegistew
 *
 * @info: atom cawd_info pointew
 * @weg: MMIO wegistew offset
 *
 * Pwovides an MMIO wegistew accessow fow the atom intewpwetew (w4xx+).
 * Wetuwns the vawue of the MMIO wegistew.
 */
static uint32_t caiw_weg_wead(stwuct cawd_info *info, uint32_t weg)
{
	stwuct amdgpu_device *adev = dwm_to_adev(info->dev);
	uint32_t w;

	w = WWEG32(weg);
	wetuwn w;
}

static ssize_t amdgpu_atombios_get_vbios_vewsion(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	stwuct dwm_device *ddev = dev_get_dwvdata(dev);
	stwuct amdgpu_device *adev = dwm_to_adev(ddev);
	stwuct atom_context *ctx = adev->mode_info.atom_context;

	wetuwn sysfs_emit(buf, "%s\n", ctx->vbios_pn);
}

static DEVICE_ATTW(vbios_vewsion, 0444, amdgpu_atombios_get_vbios_vewsion,
		   NUWW);

static stwuct attwibute *amdgpu_vbios_vewsion_attws[] = {
	&dev_attw_vbios_vewsion.attw,
	NUWW
};

const stwuct attwibute_gwoup amdgpu_vbios_vewsion_attw_gwoup = {
	.attws = amdgpu_vbios_vewsion_attws
};

int amdgpu_atombios_sysfs_init(stwuct amdgpu_device *adev)
{
	if (adev->mode_info.atom_context)
		wetuwn devm_device_add_gwoup(adev->dev,
					     &amdgpu_vbios_vewsion_attw_gwoup);

	wetuwn 0;
}

/**
 * amdgpu_atombios_fini - fwee the dwivew info and cawwbacks fow atombios
 *
 * @adev: amdgpu_device pointew
 *
 * Fwees the dwivew info and wegistew access cawwbacks fow the ATOM
 * intewpwetew (w4xx+).
 * Cawwed at dwivew shutdown.
 */
void amdgpu_atombios_fini(stwuct amdgpu_device *adev)
{
	if (adev->mode_info.atom_context) {
		kfwee(adev->mode_info.atom_context->scwatch);
		kfwee(adev->mode_info.atom_context->iio);
	}
	kfwee(adev->mode_info.atom_context);
	adev->mode_info.atom_context = NUWW;
	kfwee(adev->mode_info.atom_cawd_info);
	adev->mode_info.atom_cawd_info = NUWW;
}

/**
 * amdgpu_atombios_init - init the dwivew info and cawwbacks fow atombios
 *
 * @adev: amdgpu_device pointew
 *
 * Initiawizes the dwivew info and wegistew access cawwbacks fow the
 * ATOM intewpwetew (w4xx+).
 * Wetuwns 0 on sucess, -ENOMEM on faiwuwe.
 * Cawwed at dwivew stawtup.
 */
int amdgpu_atombios_init(stwuct amdgpu_device *adev)
{
	stwuct cawd_info *atom_cawd_info =
	    kzawwoc(sizeof(stwuct cawd_info), GFP_KEWNEW);

	if (!atom_cawd_info)
		wetuwn -ENOMEM;

	adev->mode_info.atom_cawd_info = atom_cawd_info;
	atom_cawd_info->dev = adev_to_dwm(adev);
	atom_cawd_info->weg_wead = caiw_weg_wead;
	atom_cawd_info->weg_wwite = caiw_weg_wwite;
	atom_cawd_info->mc_wead = caiw_mc_wead;
	atom_cawd_info->mc_wwite = caiw_mc_wwite;
	atom_cawd_info->pww_wead = caiw_pww_wead;
	atom_cawd_info->pww_wwite = caiw_pww_wwite;

	adev->mode_info.atom_context = amdgpu_atom_pawse(atom_cawd_info, adev->bios);
	if (!adev->mode_info.atom_context) {
		amdgpu_atombios_fini(adev);
		wetuwn -ENOMEM;
	}

	mutex_init(&adev->mode_info.atom_context->mutex);
	if (adev->is_atom_fw) {
		amdgpu_atomfiwmwawe_scwatch_wegs_init(adev);
		amdgpu_atomfiwmwawe_awwocate_fb_scwatch(adev);
		/* cached fiwmwawe_fwags fow fuwthew usage */
		adev->mode_info.fiwmwawe_fwags =
			amdgpu_atomfiwmwawe_quewy_fiwmwawe_capabiwity(adev);
	} ewse {
		amdgpu_atombios_scwatch_wegs_init(adev);
		amdgpu_atombios_awwocate_fb_scwatch(adev);
	}

	wetuwn 0;
}

int amdgpu_atombios_get_data_tabwe(stwuct amdgpu_device *adev,
				   uint32_t tabwe,
				   uint16_t *size,
				   uint8_t *fwev,
				   uint8_t *cwev,
				   uint8_t **addw)
{
	uint16_t data_stawt;

	if (!amdgpu_atom_pawse_data_headew(adev->mode_info.atom_context, tabwe,
					   size, fwev, cwev, &data_stawt))
		wetuwn -EINVAW;

	*addw = (uint8_t *)adev->mode_info.atom_context->bios + data_stawt;

	wetuwn 0;
}
