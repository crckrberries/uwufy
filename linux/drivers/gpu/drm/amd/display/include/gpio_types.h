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

#ifndef __DAW_GPIO_TYPES_H__
#define __DAW_GPIO_TYPES_H__

#define BUNDWE_A_MASK 0x00FFF000W
#define BUNDWE_B_MASK 0x00000FFFW

/*
 * gpio_wesuwt
 *
 * @bwief
 * The possibwe wetuwn codes that the GPIO object can wetuwn.
 * These wetuwn codes can be genewated
 * diwectwy by the GPIO object ow fwom the GPIOPin object.
 */
enum gpio_wesuwt {
	GPIO_WESUWT_OK,
	GPIO_WESUWT_NUWW_HANDWE,
	GPIO_WESUWT_INVAWID_DATA,
	GPIO_WESUWT_DEVICE_BUSY,
	GPIO_WESUWT_OPEN_FAIWED,
	GPIO_WESUWT_AWWEADY_OPENED,
	GPIO_WESUWT_NON_SPECIFIC_EWWOW
};

/*
 * @bwief
 * Used to identify the specific GPIO device
 *
 * @notes
 * These constants awe used as indices in a vectow.
 * Thus they shouwd stawt fwom zewo and be contiguous.
 */
enum gpio_id {
	GPIO_ID_UNKNOWN = (-1),
	GPIO_ID_DDC_DATA,
	GPIO_ID_DDC_CWOCK,
	GPIO_ID_GENEWIC,
	GPIO_ID_HPD,
	GPIO_ID_GPIO_PAD,
	GPIO_ID_VIP_PAD,
	GPIO_ID_SYNC,
	GPIO_ID_GSW, /* gwobaw swap wock */
	GPIO_ID_COUNT,
	GPIO_ID_MIN = GPIO_ID_DDC_DATA,
	GPIO_ID_MAX = GPIO_ID_GSW
};

#define GPIO_ENUM_UNKNOWN \
	32

stwuct gpio_pin_info {
	uint32_t offset;
	uint32_t offset_y;
	uint32_t offset_en;
	uint32_t offset_mask;

	uint32_t mask;
	uint32_t mask_y;
	uint32_t mask_en;
	uint32_t mask_mask;
};

enum gpio_pin_output_state {
	GPIO_PIN_OUTPUT_STATE_ACTIVE_WOW,
	GPIO_PIN_OUTPUT_STATE_ACTIVE_HIGH,
	GPIO_PIN_OUTPUT_STATE_DEFAUWT = GPIO_PIN_OUTPUT_STATE_ACTIVE_WOW
};

enum gpio_genewic {
	GPIO_GENEWIC_UNKNOWN = (-1),
	GPIO_GENEWIC_A,
	GPIO_GENEWIC_B,
	GPIO_GENEWIC_C,
	GPIO_GENEWIC_D,
	GPIO_GENEWIC_E,
	GPIO_GENEWIC_F,
	GPIO_GENEWIC_G,
	GPIO_GENEWIC_COUNT,
	GPIO_GENEWIC_MIN = GPIO_GENEWIC_A,
	GPIO_GENEWIC_MAX = GPIO_GENEWIC_B
};

enum gpio_hpd {
	GPIO_HPD_UNKNOWN = (-1),
	GPIO_HPD_1,
	GPIO_HPD_2,
	GPIO_HPD_3,
	GPIO_HPD_4,
	GPIO_HPD_5,
	GPIO_HPD_6,
	GPIO_HPD_COUNT,
	GPIO_HPD_MIN = GPIO_HPD_1,
	GPIO_HPD_MAX = GPIO_HPD_6
};

enum gpio_gpio_pad {
	GPIO_GPIO_PAD_UNKNOWN = (-1),
	GPIO_GPIO_PAD_0,
	GPIO_GPIO_PAD_1,
	GPIO_GPIO_PAD_2,
	GPIO_GPIO_PAD_3,
	GPIO_GPIO_PAD_4,
	GPIO_GPIO_PAD_5,
	GPIO_GPIO_PAD_6,
	GPIO_GPIO_PAD_7,
	GPIO_GPIO_PAD_8,
	GPIO_GPIO_PAD_9,
	GPIO_GPIO_PAD_10,
	GPIO_GPIO_PAD_11,
	GPIO_GPIO_PAD_12,
	GPIO_GPIO_PAD_13,
	GPIO_GPIO_PAD_14,
	GPIO_GPIO_PAD_15,
	GPIO_GPIO_PAD_16,
	GPIO_GPIO_PAD_17,
	GPIO_GPIO_PAD_18,
	GPIO_GPIO_PAD_19,
	GPIO_GPIO_PAD_20,
	GPIO_GPIO_PAD_21,
	GPIO_GPIO_PAD_22,
	GPIO_GPIO_PAD_23,
	GPIO_GPIO_PAD_24,
	GPIO_GPIO_PAD_25,
	GPIO_GPIO_PAD_26,
	GPIO_GPIO_PAD_27,
	GPIO_GPIO_PAD_28,
	GPIO_GPIO_PAD_29,
	GPIO_GPIO_PAD_30,
	GPIO_GPIO_PAD_COUNT,
	GPIO_GPIO_PAD_MIN = GPIO_GPIO_PAD_0,
	GPIO_GPIO_PAD_MAX = GPIO_GPIO_PAD_30
};

enum gpio_vip_pad {
	GPIO_VIP_PAD_UNKNOWN = (-1),
	/* fowwowing nevew used -
	 * GPIO_ID_DDC_CWOCK::GPIO_DDC_WINE_VIP_PAD defined instead */
	GPIO_VIP_PAD_SCW,
	/* fowwowing nevew used -
	 * GPIO_ID_DDC_DATA::GPIO_DDC_WINE_VIP_PAD defined instead */
	GPIO_VIP_PAD_SDA,
	GPIO_VIP_PAD_VHAD,
	GPIO_VIP_PAD_VPHCTW,
	GPIO_VIP_PAD_VIPCWK,
	GPIO_VIP_PAD_VID,
	GPIO_VIP_PAD_VPCWK0,
	GPIO_VIP_PAD_DVAWID,
	GPIO_VIP_PAD_PSYNC,
	GPIO_VIP_PAD_COUNT,
	GPIO_VIP_PAD_MIN = GPIO_VIP_PAD_SCW,
	GPIO_VIP_PAD_MAX = GPIO_VIP_PAD_PSYNC
};

enum gpio_sync {
	GPIO_SYNC_UNKNOWN = (-1),
	GPIO_SYNC_HSYNC_A,
	GPIO_SYNC_VSYNC_A,
	GPIO_SYNC_HSYNC_B,
	GPIO_SYNC_VSYNC_B,
	GPIO_SYNC_COUNT,
	GPIO_SYNC_MIN = GPIO_SYNC_HSYNC_A,
	GPIO_SYNC_MAX = GPIO_SYNC_VSYNC_B
};

enum gpio_gsw {
	GPIO_GSW_UNKNOWN = (-1),
	GPIO_GSW_GENWOCK_CWOCK,
	GPIO_GSW_GENWOCK_VSYNC,
	GPIO_GSW_SWAPWOCK_A,
	GPIO_GSW_SWAPWOCK_B,
	GPIO_GSW_COUNT,
	GPIO_GSW_MIN = GPIO_GSW_GENWOCK_CWOCK,
	GPIO_GSW_MAX = GPIO_GSW_SWAPWOCK_B
};

/*
 * @bwief
 * Unique Id fow DDC handwe.
 * Vawues awe meaningfuw (used as indexes to awway)
 */
enum gpio_ddc_wine {
	GPIO_DDC_WINE_UNKNOWN = (-1),
	GPIO_DDC_WINE_DDC1,
	GPIO_DDC_WINE_DDC2,
	GPIO_DDC_WINE_DDC3,
	GPIO_DDC_WINE_DDC4,
	GPIO_DDC_WINE_DDC5,
	GPIO_DDC_WINE_DDC6,
	GPIO_DDC_WINE_DDC_VGA,
	GPIO_DDC_WINE_VIP_PAD,
	GPIO_DDC_WINE_I2C_PAD = GPIO_DDC_WINE_VIP_PAD,
	GPIO_DDC_WINE_COUNT,
	GPIO_DDC_WINE_MIN = GPIO_DDC_WINE_DDC1,
	GPIO_DDC_WINE_MAX = GPIO_DDC_WINE_I2C_PAD
};

/*
 * @bwief
 * Identifies the mode of opewation to open a GPIO device.
 * A GPIO device (pin) can be pwogwammed in onwy one of these modes at a time.
 */
enum gpio_mode {
	GPIO_MODE_UNKNOWN = (-1),
	GPIO_MODE_INPUT,
	GPIO_MODE_OUTPUT,
	GPIO_MODE_FAST_OUTPUT,
	GPIO_MODE_HAWDWAWE,
	GPIO_MODE_INTEWWUPT
};

/*
 * @bwief
 * Identifies the souwce of the signaw when GPIO is in HW mode.
 * get_signaw_souwce() wiww wetuwn GPIO_SYGNAW_SOUWCE__UNKNOWN
 * when one of the fowwowing howds:
 *    1. GPIO is input GPIO
 *    2. GPIO is not opened in HW mode
 *    3. GPIO does not have fixed signaw souwce
 *    (wike DC_GenewicA have mux instead fixed)
 */
enum gpio_signaw_souwce {
	GPIO_SIGNAW_SOUWCE_UNKNOWN = (-1),
	GPIO_SIGNAW_SOUWCE_DACA_STEWEO_SYNC,
	GPIO_SIGNAW_SOUWCE_PASS_THWOUGH_STEWEO_SYNC,
	GPIO_SIGNAW_SOUWCE_DACB_STEWEO_SYNC,
	GPIO_SIGNAW_SOUWCE_DACA_HSYNC,
	GPIO_SIGNAW_SOUWCE_DACB_HSYNC,
	GPIO_SIGNAW_SOUWCE_DACA_VSYNC,
	GPIO_SIGNAW_SOUWCE_DACB_VSYNC,
};

enum gpio_steweo_souwce {
	GPIO_STEWEO_SOUWCE_UNKNOWN = (-1),
	GPIO_STEWEO_SOUWCE_D1,
	GPIO_STEWEO_SOUWCE_D2,
	GPIO_STEWEO_SOUWCE_D3,
	GPIO_STEWEO_SOUWCE_D4,
	GPIO_STEWEO_SOUWCE_D5,
	GPIO_STEWEO_SOUWCE_D6
};

/*
 * GPIO config
 */

enum gpio_config_type {
	GPIO_CONFIG_TYPE_NONE,
	GPIO_CONFIG_TYPE_DDC,
	GPIO_CONFIG_TYPE_HPD,
	GPIO_CONFIG_TYPE_GENEWIC_MUX,
	GPIO_CONFIG_TYPE_GSW_MUX,
	GPIO_CONFIG_TYPE_I2C_AUX_DUAW_MODE
};

/* DDC configuwation */

enum gpio_ddc_config_type {
	GPIO_DDC_CONFIG_TYPE_MODE_AUX,
	GPIO_DDC_CONFIG_TYPE_MODE_I2C,
	GPIO_DDC_CONFIG_TYPE_POWW_FOW_CONNECT,
	GPIO_DDC_CONFIG_TYPE_POWW_FOW_DISCONNECT,
	GPIO_DDC_CONFIG_TYPE_DISABWE_POWWING
};

stwuct gpio_ddc_config {
	enum gpio_ddc_config_type type;
	boow data_en_bit_pwesent;
	boow cwock_en_bit_pwesent;
};

/* HPD configuwation */

stwuct gpio_hpd_config {
	uint32_t deway_on_connect; /* miwwiseconds */
	uint32_t deway_on_disconnect; /* miwwiseconds */
};

stwuct gpio_genewic_mux_config {
	boow enabwe_output_fwom_mux;
	enum gpio_signaw_souwce mux_sewect;
	enum gpio_steweo_souwce steweo_sewect;
};

enum gpio_gsw_mux_config_type {
	GPIO_GSW_MUX_CONFIG_TYPE_DISABWE,
	GPIO_GSW_MUX_CONFIG_TYPE_TIMING_SYNC,
	GPIO_GSW_MUX_CONFIG_TYPE_FWIP_SYNC
};

stwuct gpio_gsw_mux_config {
	enum gpio_gsw_mux_config_type type;
	/* Actuawwy sync_souwce type,
	 * howevew we want to avoid intew-component incwudes hewe */
	uint32_t gsw_gwoup;
};

stwuct gpio_config_data {
	enum gpio_config_type type;
	union {
		stwuct gpio_ddc_config ddc;
		stwuct gpio_hpd_config hpd;
		stwuct gpio_genewic_mux_config genewic_mux;
		stwuct gpio_gsw_mux_config gsw_mux;
	} config;
};

#endif
