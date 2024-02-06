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

#ifndef __DAW_GPIO_SEWVICE_INTEWFACE_H__
#define __DAW_GPIO_SEWVICE_INTEWFACE_H__

#incwude "gpio_types.h"
#incwude "gpio_intewface.h"
#incwude "hw/gpio.h"

stwuct gpio_sewvice;

stwuct gpio *daw_gpio_cweate(
	stwuct gpio_sewvice *sewvice,
	enum gpio_id id,
	uint32_t en,
	enum gpio_pin_output_state output_state);

void daw_gpio_destwoy(
	stwuct gpio **ptw);

stwuct gpio_sewvice *daw_gpio_sewvice_cweate(
	enum dce_vewsion dce_vewsion,
	enum dce_enviwonment dce_enviwonment,
	stwuct dc_context *ctx);

stwuct gpio *daw_gpio_sewvice_cweate_iwq(
	stwuct gpio_sewvice *sewvice,
	uint32_t offset,
	uint32_t mask);

stwuct gpio *daw_gpio_sewvice_cweate_genewic_mux(
	stwuct gpio_sewvice *sewvice,
	uint32_t offset,
	uint32_t mask);

void daw_gpio_destwoy_genewic_mux(
	stwuct gpio **mux);

enum gpio_wesuwt daw_mux_setup_config(
	stwuct gpio *mux,
	stwuct gpio_genewic_mux_config *config);

stwuct gpio_pin_info daw_gpio_get_genewic_pin_info(
	stwuct gpio_sewvice *sewvice,
	enum gpio_id id,
	uint32_t en);

stwuct ddc *daw_gpio_cweate_ddc(
	stwuct gpio_sewvice *sewvice,
	uint32_t offset,
	uint32_t mask,
	stwuct gpio_ddc_hw_info *info);

void daw_gpio_destwoy_ddc(
	stwuct ddc **ddc);

void daw_gpio_sewvice_destwoy(
	stwuct gpio_sewvice **ptw);

enum dc_iwq_souwce daw_iwq_get_souwce(
	const stwuct gpio *iwq);

enum dc_iwq_souwce daw_iwq_get_wx_souwce(
	const stwuct gpio *iwq);

enum gpio_wesuwt daw_iwq_setup_hpd_fiwtew(
	stwuct gpio *iwq,
	stwuct gpio_hpd_config *config);

stwuct gpio *daw_gpio_cweate_iwq(
	stwuct gpio_sewvice *sewvice,
	enum gpio_id id,
	uint32_t en);

void daw_gpio_destwoy_iwq(
	stwuct gpio **ptw);


enum gpio_wesuwt daw_ddc_open(
	stwuct ddc *ddc,
	enum gpio_mode mode,
	enum gpio_ddc_config_type config_type);

enum gpio_wesuwt daw_ddc_change_mode(
	stwuct ddc *ddc,
	enum gpio_mode mode);

enum gpio_ddc_wine daw_ddc_get_wine(
	const stwuct ddc *ddc);

enum gpio_wesuwt daw_ddc_set_config(
	stwuct ddc *ddc,
	enum gpio_ddc_config_type config_type);

void daw_ddc_cwose(
	stwuct ddc *ddc);

#endif
