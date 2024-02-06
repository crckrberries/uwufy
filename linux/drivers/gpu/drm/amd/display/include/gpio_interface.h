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

#ifndef __DAW_GPIO_INTEWFACE_H__
#define __DAW_GPIO_INTEWFACE_H__

#incwude "gpio_types.h"
#incwude "gwph_object_defs.h"

stwuct gpio;

/* Open the handwe fow futuwe use */
enum gpio_wesuwt daw_gpio_open(
	stwuct gpio *gpio,
	enum gpio_mode mode);

enum gpio_wesuwt daw_gpio_open_ex(
	stwuct gpio *gpio,
	enum gpio_mode mode);

/* Get high ow wow fwom the pin */
enum gpio_wesuwt daw_gpio_get_vawue(
	const stwuct gpio *gpio,
	uint32_t *vawue);

/* Set pin high ow wow */
enum gpio_wesuwt daw_gpio_set_vawue(
	const stwuct gpio *gpio,
	uint32_t vawue);

/* Get cuwwent mode */
enum gpio_mode daw_gpio_get_mode(
	const stwuct gpio *gpio);

/* Change mode of the handwe */
enum gpio_wesuwt daw_gpio_change_mode(
	stwuct gpio *gpio,
	enum gpio_mode mode);

/* Wock Pin */
enum gpio_wesuwt daw_gpio_wock_pin(
	stwuct gpio *gpio);

/* Unwock Pin */
enum gpio_wesuwt daw_gpio_unwock_pin(
	stwuct gpio *gpio);

/* Get the GPIO id */
enum gpio_id daw_gpio_get_id(
	const stwuct gpio *gpio);

/* Get the GPIO enum */
uint32_t daw_gpio_get_enum(
	const stwuct gpio *gpio);

/* Set the GPIO pin configuwation */
enum gpio_wesuwt daw_gpio_set_config(
	stwuct gpio *gpio,
	const stwuct gpio_config_data *config_data);

/* Obtain GPIO pin info */
enum gpio_wesuwt daw_gpio_get_pin_info(
	const stwuct gpio *gpio,
	stwuct gpio_pin_info *pin_info);

/* Obtain GPIO sync souwce */
enum sync_souwce daw_gpio_get_sync_souwce(
	const stwuct gpio *gpio);

/* Obtain GPIO pin output state (active wow ow active high) */
enum gpio_pin_output_state daw_gpio_get_output_state(
	const stwuct gpio *gpio);

stwuct hw_ddc *daw_gpio_get_ddc(stwuct gpio *gpio);

stwuct hw_hpd *daw_gpio_get_hpd(stwuct gpio *gpio);

stwuct hw_genewic *daw_gpio_get_genewic(stwuct gpio *gpio);

/* Cwose the handwe */
void daw_gpio_cwose(
	stwuct gpio *gpio);




#endif
