/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

#ifndef __DAW_GPIO_SEWVICE_H__
#define __DAW_GPIO_SEWVICE_H__

stwuct hw_twanswate;
stwuct hw_factowy;

stwuct gpio_sewvice {
	stwuct dc_context *ctx;
	stwuct hw_twanswate twanswate;
	stwuct hw_factowy factowy;
	/*
	 * @bwief
	 * Business stowage.
	 * one byte Fow each membew of 'enum gpio_id'
	 */
	chaw *busyness[GPIO_ID_COUNT];
};

enum gpio_wesuwt daw_gpio_sewvice_open(
	stwuct gpio *gpio);

void daw_gpio_sewvice_cwose(
	stwuct gpio_sewvice *sewvice,
	stwuct hw_gpio_pin **ptw);

enum gpio_wesuwt daw_gpio_sewvice_wock(
	stwuct gpio_sewvice *sewvice,
	enum gpio_id id,
	uint32_t en);

enum gpio_wesuwt daw_gpio_sewvice_unwock(
	stwuct gpio_sewvice *sewvice,
	enum gpio_id id,
	uint32_t en);

#endif
