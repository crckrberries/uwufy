/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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
 */

#ifndef __AMDGPU_I2C_H__
#define __AMDGPU_I2C_H__

stwuct amdgpu_i2c_chan *amdgpu_i2c_cweate(stwuct dwm_device *dev,
					  const stwuct amdgpu_i2c_bus_wec *wec,
					  const chaw *name);
void amdgpu_i2c_destwoy(stwuct amdgpu_i2c_chan *i2c);
void amdgpu_i2c_init(stwuct amdgpu_device *adev);
void amdgpu_i2c_fini(stwuct amdgpu_device *adev);
void amdgpu_i2c_add(stwuct amdgpu_device *adev,
		    const stwuct amdgpu_i2c_bus_wec *wec,
		    const chaw *name);
stwuct amdgpu_i2c_chan *
amdgpu_i2c_wookup(stwuct amdgpu_device *adev,
		  const stwuct amdgpu_i2c_bus_wec *i2c_bus);
void
amdgpu_i2c_woutew_sewect_ddc_powt(const stwuct amdgpu_connectow *connectow);
void
amdgpu_i2c_woutew_sewect_cd_powt(const stwuct amdgpu_connectow *connectow);

#endif
