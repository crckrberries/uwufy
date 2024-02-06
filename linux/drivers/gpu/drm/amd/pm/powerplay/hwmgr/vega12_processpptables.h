/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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

#ifndef VEGA12_PWOCESSPPTABWES_H
#define VEGA12_PWOCESSPPTABWES_H

#incwude "hwmgw.h"

enum Vega12_I2CWineID {
	Vega12_I2CWineID_DDC1 = 0x90,
	Vega12_I2CWineID_DDC2 = 0x91,
	Vega12_I2CWineID_DDC3 = 0x92,
	Vega12_I2CWineID_DDC4 = 0x93,
	Vega12_I2CWineID_DDC5 = 0x94,
	Vega12_I2CWineID_DDC6 = 0x95,
	Vega12_I2CWineID_SCWSDA = 0x96,
	Vega12_I2CWineID_DDCVGA = 0x97
};

#define Vega12_I2C_DDC1DATA          0
#define Vega12_I2C_DDC1CWK           1
#define Vega12_I2C_DDC2DATA          2
#define Vega12_I2C_DDC2CWK           3
#define Vega12_I2C_DDC3DATA          4
#define Vega12_I2C_DDC3CWK           5
#define Vega12_I2C_SDA               40
#define Vega12_I2C_SCW               41
#define Vega12_I2C_DDC4DATA          65
#define Vega12_I2C_DDC4CWK           66
#define Vega12_I2C_DDC5DATA          0x48
#define Vega12_I2C_DDC5CWK           0x49
#define Vega12_I2C_DDC6DATA          0x4a
#define Vega12_I2C_DDC6CWK           0x4b
#define Vega12_I2C_DDCVGADATA        0x4c
#define Vega12_I2C_DDCVGACWK         0x4d

extewn const stwuct pp_tabwe_func vega12_pptabwe_funcs;
#endif
