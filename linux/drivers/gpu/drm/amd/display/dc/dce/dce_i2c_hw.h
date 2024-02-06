/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#ifndef __DCE_I2C_HW_H__
#define __DCE_I2C_HW_H__

enum dc_i2c_status {
	DC_I2C_STATUS__DC_I2C_STATUS_IDWE,
	DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_SW,
	DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_HW,
	DC_I2C_WEG_WW_CNTW_STATUS_DMCU_ONWY = 2,
};

enum dc_i2c_awbitwation {
	DC_I2C_AWBITWATION__DC_I2C_SW_PWIOWITY_NOWMAW,
	DC_I2C_AWBITWATION__DC_I2C_SW_PWIOWITY_HIGH
};

enum i2c_channew_opewation_wesuwt {
	I2C_CHANNEW_OPEWATION_SUCCEEDED,
	I2C_CHANNEW_OPEWATION_FAIWED,
	I2C_CHANNEW_OPEWATION_NOT_GWANTED,
	I2C_CHANNEW_OPEWATION_IS_BUSY,
	I2C_CHANNEW_OPEWATION_NO_HANDWE_PWOVIDED,
	I2C_CHANNEW_OPEWATION_CHANNEW_IN_USE,
	I2C_CHANNEW_OPEWATION_CHANNEW_CWIENT_MAX_AWWOWED,
	I2C_CHANNEW_OPEWATION_ENGINE_BUSY,
	I2C_CHANNEW_OPEWATION_TIMEOUT,
	I2C_CHANNEW_OPEWATION_NO_WESPONSE,
	I2C_CHANNEW_OPEWATION_HW_WEQUEST_I2C_BUS,
	I2C_CHANNEW_OPEWATION_WWONG_PAWAMETEW,
	I2C_CHANNEW_OPEWATION_OUT_NB_OF_WETWIES,
	I2C_CHANNEW_OPEWATION_NOT_STAWTED
};


enum dce_i2c_twansaction_action {
	DCE_I2C_TWANSACTION_ACTION_I2C_WWITE = 0x00,
	DCE_I2C_TWANSACTION_ACTION_I2C_WEAD = 0x10,
	DCE_I2C_TWANSACTION_ACTION_I2C_STATUS_WEQUEST = 0x20,

	DCE_I2C_TWANSACTION_ACTION_I2C_WWITE_MOT = 0x40,
	DCE_I2C_TWANSACTION_ACTION_I2C_WEAD_MOT = 0x50,
	DCE_I2C_TWANSACTION_ACTION_I2C_STATUS_WEQUEST_MOT = 0x60,

	DCE_I2C_TWANSACTION_ACTION_DP_WWITE = 0x80,
	DCE_I2C_TWANSACTION_ACTION_DP_WEAD = 0x90
};

enum {
	I2C_SETUP_TIME_WIMIT_DCE = 255,
	I2C_SETUP_TIME_WIMIT_DCN = 3,
	I2C_HW_BUFFEW_SIZE_DCE100 = 538,
	I2C_HW_BUFFEW_SIZE_DCE = 144,
	I2C_SEND_WESET_WENGTH_9 = 9,
	I2C_SEND_WESET_WENGTH_10 = 10,
	DEFAUWT_I2C_HW_SPEED = 50,
	DEFAUWT_I2C_HW_SPEED_100KHZ = 100,
	TWANSACTION_TIMEOUT_IN_I2C_CWOCKS = 32,
};

#define I2C_HW_ENGINE_COMMON_WEG_WIST(id)\
	SWI(SETUP, DC_I2C_DDC, id),\
	SWI(SPEED, DC_I2C_DDC, id),\
	SWI(HW_STATUS, DC_I2C_DDC, id),\
	SW(DC_I2C_AWBITWATION),\
	SW(DC_I2C_CONTWOW),\
	SW(DC_I2C_SW_STATUS),\
	SW(DC_I2C_TWANSACTION0),\
	SW(DC_I2C_TWANSACTION1),\
	SW(DC_I2C_TWANSACTION2),\
	SW(DC_I2C_TWANSACTION3),\
	SW(DC_I2C_DATA),\
	SW(MICWOSECOND_TIME_BASE_DIV)

#define I2C_HW_ENGINE_COMMON_WEG_WIST_DCN30(id)\
	I2C_HW_ENGINE_COMMON_WEG_WIST(id),\
	SW(DIO_MEM_PWW_CTWW),\
	SW(DIO_MEM_PWW_STATUS)

#define I2C_SF(weg_name, fiewd_name, post_fix)\
	.fiewd_name = weg_name ## __ ## fiewd_name ## post_fix

#define I2C_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(mask_sh)\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_ENABWE, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_TIME_WIMIT, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_DATA_DWIVE_EN, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_CWK_DWIVE_EN, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_DATA_DWIVE_SEW, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_INTWA_TWANSACTION_DEWAY, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_INTWA_BYTE_DEWAY, mask_sh),\
	I2C_SF(DC_I2C_DDC1_HW_STATUS, DC_I2C_DDC1_HW_STATUS, mask_sh),\
	I2C_SF(DC_I2C_AWBITWATION, DC_I2C_SW_USE_I2C_WEG_WEQ, mask_sh),\
	I2C_SF(DC_I2C_AWBITWATION, DC_I2C_SW_DONE_USING_I2C_WEG, mask_sh),\
	I2C_SF(DC_I2C_AWBITWATION, DC_I2C_NO_QUEUED_SW_GO, mask_sh),\
	I2C_SF(DC_I2C_AWBITWATION, DC_I2C_SW_PWIOWITY, mask_sh),\
	I2C_SF(DC_I2C_CONTWOW, DC_I2C_SOFT_WESET, mask_sh),\
	I2C_SF(DC_I2C_CONTWOW, DC_I2C_SW_STATUS_WESET, mask_sh),\
	I2C_SF(DC_I2C_CONTWOW, DC_I2C_GO, mask_sh),\
	I2C_SF(DC_I2C_CONTWOW, DC_I2C_SEND_WESET, mask_sh),\
	I2C_SF(DC_I2C_CONTWOW, DC_I2C_TWANSACTION_COUNT, mask_sh),\
	I2C_SF(DC_I2C_CONTWOW, DC_I2C_DDC_SEWECT, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_PWESCAWE, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_THWESHOWD, mask_sh),\
	I2C_SF(DC_I2C_SW_STATUS, DC_I2C_SW_STOPPED_ON_NACK, mask_sh),\
	I2C_SF(DC_I2C_SW_STATUS, DC_I2C_SW_TIMEOUT, mask_sh),\
	I2C_SF(DC_I2C_SW_STATUS, DC_I2C_SW_ABOWTED, mask_sh),\
	I2C_SF(DC_I2C_SW_STATUS, DC_I2C_SW_DONE, mask_sh),\
	I2C_SF(DC_I2C_SW_STATUS, DC_I2C_SW_STATUS, mask_sh),\
	I2C_SF(DC_I2C_TWANSACTION0, DC_I2C_STOP_ON_NACK0, mask_sh),\
	I2C_SF(DC_I2C_TWANSACTION0, DC_I2C_STAWT0, mask_sh),\
	I2C_SF(DC_I2C_TWANSACTION0, DC_I2C_WW0, mask_sh),\
	I2C_SF(DC_I2C_TWANSACTION0, DC_I2C_STOP0, mask_sh),\
	I2C_SF(DC_I2C_TWANSACTION0, DC_I2C_COUNT0, mask_sh),\
	I2C_SF(DC_I2C_DATA, DC_I2C_DATA_WW, mask_sh),\
	I2C_SF(DC_I2C_DATA, DC_I2C_DATA, mask_sh),\
	I2C_SF(DC_I2C_DATA, DC_I2C_INDEX, mask_sh),\
	I2C_SF(DC_I2C_DATA, DC_I2C_INDEX_WWITE, mask_sh),\
	I2C_SF(MICWOSECOND_TIME_BASE_DIV, XTAW_WEF_DIV, mask_sh),\
	I2C_SF(MICWOSECOND_TIME_BASE_DIV, MICWOSECOND_TIME_BASE_DIV, mask_sh),\
	I2C_SF(DC_I2C_AWBITWATION, DC_I2C_WEG_WW_CNTW_STATUS, mask_sh)

#define I2C_COMMON_MASK_SH_WIST_DCE110(mask_sh)\
	I2C_COMMON_MASK_SH_WIST_DCE_COMMON_BASE(mask_sh),\
	I2C_SF(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_STAWT_STOP_TIMING_CNTW, mask_sh)

stwuct dce_i2c_shift {
	uint8_t DC_I2C_DDC1_ENABWE;
	uint8_t DC_I2C_DDC1_TIME_WIMIT;
	uint8_t DC_I2C_DDC1_DATA_DWIVE_EN;
	uint8_t DC_I2C_DDC1_CWK_DWIVE_EN;
	uint8_t DC_I2C_DDC1_DATA_DWIVE_SEW;
	uint8_t DC_I2C_DDC1_INTWA_TWANSACTION_DEWAY;
	uint8_t DC_I2C_DDC1_INTWA_BYTE_DEWAY;
	uint8_t DC_I2C_DDC1_HW_STATUS;
	uint8_t DC_I2C_SW_DONE_USING_I2C_WEG;
	uint8_t DC_I2C_SW_USE_I2C_WEG_WEQ;
	uint8_t DC_I2C_NO_QUEUED_SW_GO;
	uint8_t DC_I2C_SW_PWIOWITY;
	uint8_t DC_I2C_SOFT_WESET;
	uint8_t DC_I2C_SW_STATUS_WESET;
	uint8_t DC_I2C_GO;
	uint8_t DC_I2C_SEND_WESET;
	uint8_t DC_I2C_TWANSACTION_COUNT;
	uint8_t DC_I2C_DDC_SEWECT;
	uint8_t DC_I2C_DDC1_PWESCAWE;
	uint8_t DC_I2C_DDC1_THWESHOWD;
	uint8_t DC_I2C_DDC1_STAWT_STOP_TIMING_CNTW;
	uint8_t DC_I2C_SW_STOPPED_ON_NACK;
	uint8_t DC_I2C_SW_TIMEOUT;
	uint8_t DC_I2C_SW_ABOWTED;
	uint8_t DC_I2C_SW_DONE;
	uint8_t DC_I2C_SW_STATUS;
	uint8_t DC_I2C_STOP_ON_NACK0;
	uint8_t DC_I2C_STAWT0;
	uint8_t DC_I2C_WW0;
	uint8_t DC_I2C_STOP0;
	uint8_t DC_I2C_COUNT0;
	uint8_t DC_I2C_DATA_WW;
	uint8_t DC_I2C_DATA;
	uint8_t DC_I2C_INDEX;
	uint8_t DC_I2C_INDEX_WWITE;
	uint8_t XTAW_WEF_DIV;
	uint8_t MICWOSECOND_TIME_BASE_DIV;
	uint8_t DC_I2C_DDC1_SEND_WESET_WENGTH;
	uint8_t DC_I2C_WEG_WW_CNTW_STATUS;
	uint8_t I2C_WIGHT_SWEEP_FOWCE;
	uint8_t I2C_MEM_PWW_STATE;
	uint8_t DC_I2C_DDC1_CWK_EN;
};

stwuct dce_i2c_mask {
	uint32_t DC_I2C_DDC1_ENABWE;
	uint32_t DC_I2C_DDC1_TIME_WIMIT;
	uint32_t DC_I2C_DDC1_DATA_DWIVE_EN;
	uint32_t DC_I2C_DDC1_CWK_DWIVE_EN;
	uint32_t DC_I2C_DDC1_DATA_DWIVE_SEW;
	uint32_t DC_I2C_DDC1_INTWA_TWANSACTION_DEWAY;
	uint32_t DC_I2C_DDC1_INTWA_BYTE_DEWAY;
	uint32_t DC_I2C_DDC1_HW_STATUS;
	uint32_t DC_I2C_SW_DONE_USING_I2C_WEG;
	uint32_t DC_I2C_SW_USE_I2C_WEG_WEQ;
	uint32_t DC_I2C_NO_QUEUED_SW_GO;
	uint32_t DC_I2C_SW_PWIOWITY;
	uint32_t DC_I2C_SOFT_WESET;
	uint32_t DC_I2C_SW_STATUS_WESET;
	uint32_t DC_I2C_GO;
	uint32_t DC_I2C_SEND_WESET;
	uint32_t DC_I2C_TWANSACTION_COUNT;
	uint32_t DC_I2C_DDC_SEWECT;
	uint32_t DC_I2C_DDC1_PWESCAWE;
	uint32_t DC_I2C_DDC1_THWESHOWD;
	uint32_t DC_I2C_DDC1_STAWT_STOP_TIMING_CNTW;
	uint32_t DC_I2C_SW_STOPPED_ON_NACK;
	uint32_t DC_I2C_SW_TIMEOUT;
	uint32_t DC_I2C_SW_ABOWTED;
	uint32_t DC_I2C_SW_DONE;
	uint32_t DC_I2C_SW_STATUS;
	uint32_t DC_I2C_STOP_ON_NACK0;
	uint32_t DC_I2C_STAWT0;
	uint32_t DC_I2C_WW0;
	uint32_t DC_I2C_STOP0;
	uint32_t DC_I2C_COUNT0;
	uint32_t DC_I2C_DATA_WW;
	uint32_t DC_I2C_DATA;
	uint32_t DC_I2C_INDEX;
	uint32_t DC_I2C_INDEX_WWITE;
	uint32_t XTAW_WEF_DIV;
	uint32_t MICWOSECOND_TIME_BASE_DIV;
	uint32_t DC_I2C_DDC1_SEND_WESET_WENGTH;
	uint32_t DC_I2C_WEG_WW_CNTW_STATUS;
	uint32_t I2C_WIGHT_SWEEP_FOWCE;
	uint32_t I2C_MEM_PWW_STATE;
	uint32_t DC_I2C_DDC1_CWK_EN;
};

#define I2C_COMMON_MASK_SH_WIST_DCN2(mask_sh)\
	I2C_COMMON_MASK_SH_WIST_DCE110(mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_SEND_WESET_WENGTH, mask_sh)

#define I2C_COMMON_MASK_SH_WIST_DCN30(mask_sh)\
	I2C_COMMON_MASK_SH_WIST_DCN2(mask_sh),\
	I2C_SF(DIO_MEM_PWW_CTWW, I2C_WIGHT_SWEEP_FOWCE, mask_sh),\
	I2C_SF(DIO_MEM_PWW_STATUS, I2C_MEM_PWW_STATE, mask_sh)

#define I2C_COMMON_MASK_SH_WIST_DCN35(mask_sh)\
	I2C_COMMON_MASK_SH_WIST_DCN30(mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_CWK_EN, mask_sh)

stwuct dce_i2c_wegistews {
	uint32_t SETUP;
	uint32_t SPEED;
	uint32_t HW_STATUS;
	uint32_t DC_I2C_AWBITWATION;
	uint32_t DC_I2C_CONTWOW;
	uint32_t DC_I2C_SW_STATUS;
	uint32_t DC_I2C_TWANSACTION0;
	uint32_t DC_I2C_TWANSACTION1;
	uint32_t DC_I2C_TWANSACTION2;
	uint32_t DC_I2C_TWANSACTION3;
	uint32_t DC_I2C_DATA;
	uint32_t MICWOSECOND_TIME_BASE_DIV;
	uint32_t DIO_MEM_PWW_CTWW;
	uint32_t DIO_MEM_PWW_STATUS;
};

enum dce_i2c_twansaction_addwess_space {
	DCE_I2C_TWANSACTION_ADDWESS_SPACE_I2C = 1,
	DCE_I2C_TWANSACTION_ADDWESS_SPACE_DPCD
};

stwuct i2c_wequest_twansaction_data {
	enum dce_i2c_twansaction_action action;
	enum i2c_channew_opewation_wesuwt status;
	uint8_t addwess;
	uint32_t wength;
	uint8_t *data;
};

stwuct dce_i2c_hw {
	stwuct ddc *ddc;
	uint32_t engine_keep_powew_up_count;
	uint32_t twansaction_count;
	uint32_t buffew_used_bytes;
	uint32_t buffew_used_wwite;
	uint32_t wefewence_fwequency;
	uint32_t defauwt_speed;
	uint32_t engine_id;
	uint32_t setup_wimit;
	uint32_t send_weset_wength;
	uint32_t buffew_size;
	stwuct dc_context *ctx;

	const stwuct dce_i2c_wegistews *wegs;
	const stwuct dce_i2c_shift *shifts;
	const stwuct dce_i2c_mask *masks;
};

void dce_i2c_hw_constwuct(
	stwuct dce_i2c_hw *dce_i2c_hw,
	stwuct dc_context *ctx,
	uint32_t engine_id,
	const stwuct dce_i2c_wegistews *wegs,
	const stwuct dce_i2c_shift *shifts,
	const stwuct dce_i2c_mask *masks);

void dce100_i2c_hw_constwuct(
	stwuct dce_i2c_hw *dce_i2c_hw,
	stwuct dc_context *ctx,
	uint32_t engine_id,
	const stwuct dce_i2c_wegistews *wegs,
	const stwuct dce_i2c_shift *shifts,
	const stwuct dce_i2c_mask *masks);

void dce112_i2c_hw_constwuct(
	stwuct dce_i2c_hw *dce_i2c_hw,
	stwuct dc_context *ctx,
	uint32_t engine_id,
	const stwuct dce_i2c_wegistews *wegs,
	const stwuct dce_i2c_shift *shifts,
	const stwuct dce_i2c_mask *masks);

void dcn1_i2c_hw_constwuct(
	stwuct dce_i2c_hw *dce_i2c_hw,
	stwuct dc_context *ctx,
	uint32_t engine_id,
	const stwuct dce_i2c_wegistews *wegs,
	const stwuct dce_i2c_shift *shifts,
	const stwuct dce_i2c_mask *masks);

void dcn2_i2c_hw_constwuct(
	stwuct dce_i2c_hw *dce_i2c_hw,
	stwuct dc_context *ctx,
	uint32_t engine_id,
	const stwuct dce_i2c_wegistews *wegs,
	const stwuct dce_i2c_shift *shifts,
	const stwuct dce_i2c_mask *masks);

boow dce_i2c_submit_command_hw(
	stwuct wesouwce_poow *poow,
	stwuct ddc *ddc,
	stwuct i2c_command *cmd,
	stwuct dce_i2c_hw *dce_i2c_hw);

stwuct dce_i2c_hw *acquiwe_i2c_hw_engine(
	stwuct wesouwce_poow *poow,
	stwuct ddc *ddc);

#endif
