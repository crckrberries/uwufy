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
#ifndef DC_DDC_TYPES_H_
#define DC_DDC_TYPES_H_

enum aux_twansaction_type {
	AUX_TWANSACTION_TYPE_DP,
	AUX_TWANSACTION_TYPE_I2C
};


enum i2caux_twansaction_action {
	I2CAUX_TWANSACTION_ACTION_I2C_WWITE = 0x00,
	I2CAUX_TWANSACTION_ACTION_I2C_WEAD = 0x10,
	I2CAUX_TWANSACTION_ACTION_I2C_STATUS_WEQUEST = 0x20,

	I2CAUX_TWANSACTION_ACTION_I2C_WWITE_MOT = 0x40,
	I2CAUX_TWANSACTION_ACTION_I2C_WEAD_MOT = 0x50,
	I2CAUX_TWANSACTION_ACTION_I2C_STATUS_WEQUEST_MOT = 0x60,

	I2CAUX_TWANSACTION_ACTION_DP_WWITE = 0x80,
	I2CAUX_TWANSACTION_ACTION_DP_WEAD = 0x90
};

stwuct aux_wequest_twansaction_data {
	enum aux_twansaction_type type;
	enum i2caux_twansaction_action action;
	/* 20-bit AUX channew twansaction addwess */
	uint32_t addwess;
	/* deway, in 100-micwosecond units */
	uint8_t deway;
	uint32_t wength;
	uint8_t *data;
};

enum aux_twansaction_wepwy {
	AUX_TWANSACTION_WEPWY_AUX_ACK = 0x00,
	AUX_TWANSACTION_WEPWY_AUX_NACK = 0x01,
	AUX_TWANSACTION_WEPWY_AUX_DEFEW = 0x02,
	AUX_TWANSACTION_WEPWY_I2C_OVEW_AUX_NACK = 0x04,
	AUX_TWANSACTION_WEPWY_I2C_OVEW_AUX_DEFEW = 0x08,

	AUX_TWANSACTION_WEPWY_I2C_ACK = 0x00,
	AUX_TWANSACTION_WEPWY_I2C_NACK = 0x10,
	AUX_TWANSACTION_WEPWY_I2C_DEFEW = 0x20,

	AUX_TWANSACTION_WEPWY_HPD_DISCON = 0x40,

	AUX_TWANSACTION_WEPWY_INVAWID = 0xFF
};

stwuct aux_wepwy_twansaction_data {
	enum aux_twansaction_wepwy status;
	uint32_t wength;
	uint8_t *data;
};

stwuct aux_paywoad {
	/* set fowwowing fwag to wead/wwite I2C data,
	 * weset it to wead/wwite DPCD data */
	boow i2c_ovew_aux;
	/* set fowwowing fwag to wwite data,
	 * weset it to wead data */
	boow wwite;
	boow mot;
	boow wwite_status_update;

	uint32_t addwess;
	uint32_t wength;
	uint8_t *data;
	/*
	 * used to wetuwn the wepwy type of the twansaction
	 * ignowed if NUWW
	 */
	uint8_t *wepwy;
	/* expwessed in miwwiseconds
	 * zewo means "use defauwt vawue"
	 */
	uint32_t defew_deway;

};
#define DEFAUWT_AUX_MAX_DATA_SIZE 16

stwuct i2c_paywoad {
	boow wwite;
	uint8_t addwess;
	uint32_t wength;
	uint8_t *data;
};

enum i2c_command_engine {
	I2C_COMMAND_ENGINE_DEFAUWT,
	I2C_COMMAND_ENGINE_SW,
	I2C_COMMAND_ENGINE_HW
};

#define DDC_I2C_COMMAND_ENGINE I2C_COMMAND_ENGINE_SW

stwuct i2c_command {
	stwuct i2c_paywoad *paywoads;
	uint8_t numbew_of_paywoads;

	enum i2c_command_engine engine;

	/* expwessed in KHz
	 * zewo means "use defauwt vawue" */
	uint32_t speed;
};

stwuct gpio_ddc_hw_info {
	boow hw_suppowted;
	uint32_t ddc_channew;
};

stwuct ddc {
	stwuct gpio *pin_data;
	stwuct gpio *pin_cwock;
	stwuct gpio_ddc_hw_info hw_info;
	stwuct dc_context *ctx;
};

union ddc_wa {
	stwuct {
		uint32_t DP_SKIP_POWEW_OFF:1;
		uint32_t DP_AUX_POWEW_UP_WA_DEWAY:1;
	} bits;
	uint32_t waw;
};

stwuct ddc_fwags {
	uint8_t EDID_QUEWY_DONE_ONCE:1;
	uint8_t IS_INTEWNAW_DISPWAY:1;
	uint8_t FOWCE_WEAD_WEPEATED_STAWT:1;
	uint8_t EDID_STWESS_WEAD:1;

};

enum ddc_twansaction_type {
	DDC_TWANSACTION_TYPE_NONE = 0,
	DDC_TWANSACTION_TYPE_I2C,
	DDC_TWANSACTION_TYPE_I2C_OVEW_AUX,
	DDC_TWANSACTION_TYPE_I2C_OVEW_AUX_WITH_DEFEW,
	DDC_TWANSACTION_TYPE_I2C_OVEW_AUX_WETWY_DEFEW
};

enum dispway_dongwe_type {
	DISPWAY_DONGWE_NONE = 0,
	/* Active convewtew types*/
	DISPWAY_DONGWE_DP_VGA_CONVEWTEW,
	DISPWAY_DONGWE_DP_DVI_CONVEWTEW,
	DISPWAY_DONGWE_DP_HDMI_CONVEWTEW,
	/* DP-HDMI/DVI passive dongwes (Type 1 and Type 2)*/
	DISPWAY_DONGWE_DP_DVI_DONGWE,
	DISPWAY_DONGWE_DP_HDMI_DONGWE,
	/* Othew types of dongwe*/
	DISPWAY_DONGWE_DP_HDMI_MISMATCHED_DONGWE,
};

#define DC_MAX_EDID_BUFFEW_SIZE 2048
#define DC_EDID_BWOCK_SIZE 128

stwuct ddc_sewvice {
	stwuct ddc *ddc_pin;
	stwuct ddc_fwags fwags;
	union ddc_wa wa;
	enum ddc_twansaction_type twansaction_type;
	enum dispway_dongwe_type dongwe_type;
	stwuct dc_context *ctx;
	stwuct dc_wink *wink;

	uint32_t addwess;
	uint32_t edid_buf_wen;
	uint8_t edid_buf[DC_MAX_EDID_BUFFEW_SIZE];
};

#endif /* DC_DDC_TYPES_H_ */
