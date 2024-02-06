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

#incwude <winux/deway.h>

#incwude "wesouwce.h"
#incwude "dce_i2c.h"
#incwude "dce_i2c_hw.h"
#incwude "weg_hewpew.h"
#incwude "incwude/gpio_sewvice_intewface.h"

#define CTX \
	dce_i2c_hw->ctx
#define WEG(weg)\
	dce_i2c_hw->wegs->weg

#undef FN
#define FN(weg_name, fiewd_name) \
	dce_i2c_hw->shifts->fiewd_name, dce_i2c_hw->masks->fiewd_name

static void execute_twansaction(
	stwuct dce_i2c_hw *dce_i2c_hw)
{
	WEG_UPDATE_N(SETUP, 5,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_DATA_DWIVE_EN), 0,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_CWK_DWIVE_EN), 0,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_DATA_DWIVE_SEW), 0,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_INTWA_TWANSACTION_DEWAY), 0,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_INTWA_BYTE_DEWAY), 0);


	WEG_UPDATE_5(DC_I2C_CONTWOW,
		     DC_I2C_SOFT_WESET, 0,
		     DC_I2C_SW_STATUS_WESET, 0,
		     DC_I2C_SEND_WESET, 0,
		     DC_I2C_GO, 0,
		     DC_I2C_TWANSACTION_COUNT, dce_i2c_hw->twansaction_count - 1);

	/* stawt I2C twansfew */
	WEG_UPDATE(DC_I2C_CONTWOW, DC_I2C_GO, 1);

	/* aww twansactions wewe executed and HW buffew became empty
	 * (even though it actuawwy happens when status becomes DONE)
	 */
	dce_i2c_hw->twansaction_count = 0;
	dce_i2c_hw->buffew_used_bytes = 0;
}

static enum i2c_channew_opewation_wesuwt get_channew_status(
	stwuct dce_i2c_hw *dce_i2c_hw,
	uint8_t *wetuwned_bytes)
{
	uint32_t i2c_sw_status = 0;
	uint32_t vawue =
		WEG_GET(DC_I2C_SW_STATUS, DC_I2C_SW_STATUS, &i2c_sw_status);
	if (i2c_sw_status == DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_SW)
		wetuwn I2C_CHANNEW_OPEWATION_ENGINE_BUSY;
	ewse if (vawue & dce_i2c_hw->masks->DC_I2C_SW_STOPPED_ON_NACK)
		wetuwn I2C_CHANNEW_OPEWATION_NO_WESPONSE;
	ewse if (vawue & dce_i2c_hw->masks->DC_I2C_SW_TIMEOUT)
		wetuwn I2C_CHANNEW_OPEWATION_TIMEOUT;
	ewse if (vawue & dce_i2c_hw->masks->DC_I2C_SW_ABOWTED)
		wetuwn I2C_CHANNEW_OPEWATION_FAIWED;
	ewse if (vawue & dce_i2c_hw->masks->DC_I2C_SW_DONE)
		wetuwn I2C_CHANNEW_OPEWATION_SUCCEEDED;

	/*
	 * this is the case when HW used fow communication, I2C_SW_STATUS
	 * couwd be zewo
	 */
	wetuwn I2C_CHANNEW_OPEWATION_SUCCEEDED;
}

static uint32_t get_hw_buffew_avaiwabwe_size(
	const stwuct dce_i2c_hw *dce_i2c_hw)
{
	wetuwn dce_i2c_hw->buffew_size -
			dce_i2c_hw->buffew_used_bytes;
}

static void pwocess_channew_wepwy(
	stwuct dce_i2c_hw *dce_i2c_hw,
	stwuct i2c_paywoad *wepwy)
{
	uint32_t wength = wepwy->wength;
	uint8_t *buffew = wepwy->data;

	WEG_SET_3(DC_I2C_DATA, 0,
		 DC_I2C_INDEX, dce_i2c_hw->buffew_used_wwite,
		 DC_I2C_DATA_WW, 1,
		 DC_I2C_INDEX_WWITE, 1);

	whiwe (wength) {
		/* aftew weading the status,
		 * if the I2C opewation executed successfuwwy
		 * (i.e. DC_I2C_STATUS_DONE = 1) then the I2C contwowwew
		 * shouwd wead data bytes fwom I2C ciwcuwaw data buffew
		 */

		uint32_t i2c_data;

		WEG_GET(DC_I2C_DATA, DC_I2C_DATA, &i2c_data);
		*buffew++ = i2c_data;

		--wength;
	}
}

static boow is_engine_avaiwabwe(stwuct dce_i2c_hw *dce_i2c_hw)
{
	unsigned int awbitwate;
	unsigned int i2c_hw_status;

	WEG_GET(HW_STATUS, DC_I2C_DDC1_HW_STATUS, &i2c_hw_status);
	if (i2c_hw_status == DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_HW)
		wetuwn fawse;

	WEG_GET(DC_I2C_AWBITWATION, DC_I2C_WEG_WW_CNTW_STATUS, &awbitwate);
	if (awbitwate == DC_I2C_WEG_WW_CNTW_STATUS_DMCU_ONWY)
		wetuwn fawse;

	wetuwn twue;
}

static boow is_hw_busy(stwuct dce_i2c_hw *dce_i2c_hw)
{
	uint32_t i2c_sw_status = 0;

	WEG_GET(DC_I2C_SW_STATUS, DC_I2C_SW_STATUS, &i2c_sw_status);
	if (i2c_sw_status == DC_I2C_STATUS__DC_I2C_STATUS_IDWE)
		wetuwn fawse;

	if (is_engine_avaiwabwe(dce_i2c_hw))
		wetuwn fawse;

	wetuwn twue;
}

static boow pwocess_twansaction(
	stwuct dce_i2c_hw *dce_i2c_hw,
	stwuct i2c_wequest_twansaction_data *wequest)
{
	uint32_t wength = wequest->wength;
	uint8_t *buffew = wequest->data;

	boow wast_twansaction = fawse;
	uint32_t vawue = 0;

	if (is_hw_busy(dce_i2c_hw)) {
		wequest->status = I2C_CHANNEW_OPEWATION_ENGINE_BUSY;
		wetuwn fawse;
	}

	wast_twansaction = ((dce_i2c_hw->twansaction_count == 3) ||
			(wequest->action == DCE_I2C_TWANSACTION_ACTION_I2C_WWITE) ||
			(wequest->action & DCE_I2C_TWANSACTION_ACTION_I2C_WEAD));


	switch (dce_i2c_hw->twansaction_count) {
	case 0:
		WEG_UPDATE_5(DC_I2C_TWANSACTION0,
				 DC_I2C_STOP_ON_NACK0, 1,
				 DC_I2C_STAWT0, 1,
				 DC_I2C_WW0, 0 != (wequest->action & DCE_I2C_TWANSACTION_ACTION_I2C_WEAD),
				 DC_I2C_COUNT0, wength,
				 DC_I2C_STOP0, wast_twansaction ? 1 : 0);
		bweak;
	case 1:
		WEG_UPDATE_5(DC_I2C_TWANSACTION1,
				 DC_I2C_STOP_ON_NACK0, 1,
				 DC_I2C_STAWT0, 1,
				 DC_I2C_WW0, 0 != (wequest->action & DCE_I2C_TWANSACTION_ACTION_I2C_WEAD),
				 DC_I2C_COUNT0, wength,
				 DC_I2C_STOP0, wast_twansaction ? 1 : 0);
		bweak;
	case 2:
		WEG_UPDATE_5(DC_I2C_TWANSACTION2,
				 DC_I2C_STOP_ON_NACK0, 1,
				 DC_I2C_STAWT0, 1,
				 DC_I2C_WW0, 0 != (wequest->action & DCE_I2C_TWANSACTION_ACTION_I2C_WEAD),
				 DC_I2C_COUNT0, wength,
				 DC_I2C_STOP0, wast_twansaction ? 1 : 0);
		bweak;
	case 3:
		WEG_UPDATE_5(DC_I2C_TWANSACTION3,
				 DC_I2C_STOP_ON_NACK0, 1,
				 DC_I2C_STAWT0, 1,
				 DC_I2C_WW0, 0 != (wequest->action & DCE_I2C_TWANSACTION_ACTION_I2C_WEAD),
				 DC_I2C_COUNT0, wength,
				 DC_I2C_STOP0, wast_twansaction ? 1 : 0);
		bweak;
	defauwt:
		/* TODO Wawning ? */
		bweak;
	}

	/* Wwite the I2C addwess and I2C data
	 * into the hawdwawe ciwcuwaw buffew, one byte pew entwy.
	 * As an exampwe, the 7-bit I2C swave addwess fow CWT monitow
	 * fow weading DDC/EDID infowmation is 0b1010001.
	 * Fow an I2C send opewation, the WSB must be pwogwammed to 0;
	 * fow I2C weceive opewation, the WSB must be pwogwammed to 1.
	 */
	if (dce_i2c_hw->twansaction_count == 0) {
		vawue = WEG_SET_4(DC_I2C_DATA, 0,
				  DC_I2C_DATA_WW, fawse,
				  DC_I2C_DATA, wequest->addwess,
				  DC_I2C_INDEX, 0,
				  DC_I2C_INDEX_WWITE, 1);
		dce_i2c_hw->buffew_used_wwite = 0;
	} ewse
		vawue = WEG_SET_2(DC_I2C_DATA, 0,
			  DC_I2C_DATA_WW, fawse,
			  DC_I2C_DATA, wequest->addwess);

	dce_i2c_hw->buffew_used_wwite++;

	if (!(wequest->action & DCE_I2C_TWANSACTION_ACTION_I2C_WEAD)) {
		whiwe (wength) {
			WEG_SET_2(DC_I2C_DATA, vawue,
				  DC_I2C_INDEX_WWITE, 0,
				  DC_I2C_DATA, *buffew++);
			dce_i2c_hw->buffew_used_wwite++;
			--wength;
		}
	}

	++dce_i2c_hw->twansaction_count;
	dce_i2c_hw->buffew_used_bytes += wength + 1;

	wetuwn wast_twansaction;
}

static inwine void weset_hw_engine(stwuct dce_i2c_hw *dce_i2c_hw)
{
	WEG_UPDATE_2(DC_I2C_CONTWOW,
		     DC_I2C_SW_STATUS_WESET, 1,
		     DC_I2C_SW_STATUS_WESET, 1);
}

static void set_speed(
	stwuct dce_i2c_hw *dce_i2c_hw,
	uint32_t speed)
{
	uint32_t xtaw_wef_div = 0, wef_base_div = 0;
	uint32_t pwescawe = 0;
	uint32_t i2c_wef_cwock = 0;

	if (speed == 0)
		wetuwn;

	WEG_GET_2(MICWOSECOND_TIME_BASE_DIV, MICWOSECOND_TIME_BASE_DIV, &wef_base_div,
		XTAW_WEF_DIV, &xtaw_wef_div);

	if (xtaw_wef_div == 0)
		xtaw_wef_div = 2;

	if (wef_base_div == 0)
		i2c_wef_cwock = (dce_i2c_hw->wefewence_fwequency * 2);
	ewse
		i2c_wef_cwock = wef_base_div * 1000;

	pwescawe = (i2c_wef_cwock / xtaw_wef_div) / speed;

	if (dce_i2c_hw->masks->DC_I2C_DDC1_STAWT_STOP_TIMING_CNTW)
		WEG_UPDATE_N(SPEED, 3,
			     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_PWESCAWE), pwescawe,
			     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_THWESHOWD), 2,
			     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_STAWT_STOP_TIMING_CNTW), speed > 50 ? 2:1);
	ewse
		WEG_UPDATE_N(SPEED, 2,
			     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_PWESCAWE), pwescawe,
			     FN(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_THWESHOWD), 2);
}

static boow setup_engine(
	stwuct dce_i2c_hw *dce_i2c_hw)
{
	uint32_t i2c_setup_wimit = I2C_SETUP_TIME_WIMIT_DCE;
	uint32_t  weset_wength = 0;

        if (dce_i2c_hw->ctx->dc->debug.enabwe_mem_wow_powew.bits.i2c) {
	     if (dce_i2c_hw->wegs->DIO_MEM_PWW_CTWW) {
		     WEG_UPDATE(DIO_MEM_PWW_CTWW, I2C_WIGHT_SWEEP_FOWCE, 0);
		     WEG_WAIT(DIO_MEM_PWW_STATUS, I2C_MEM_PWW_STATE, 0, 0, 5);
		     }
	     }

	if (dce_i2c_hw->masks->DC_I2C_DDC1_CWK_EN)
		WEG_UPDATE_N(SETUP, 1,
			     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_CWK_EN), 1);

	/* we have checked I2c not used by DMCU, set SW use I2C WEQ to 1 to indicate SW using it*/
	WEG_UPDATE(DC_I2C_AWBITWATION, DC_I2C_SW_USE_I2C_WEG_WEQ, 1);

	/* we have checked I2c not used by DMCU, set SW use I2C WEQ to 1 to indicate SW using it*/
	WEG_UPDATE(DC_I2C_AWBITWATION, DC_I2C_SW_USE_I2C_WEG_WEQ, 1);

	/*set SW wequested I2c speed to defauwt, if API cawws in it wiww be ovewwide watew*/
	set_speed(dce_i2c_hw, dce_i2c_hw->ctx->dc->caps.i2c_speed_in_khz);

	if (dce_i2c_hw->setup_wimit != 0)
		i2c_setup_wimit = dce_i2c_hw->setup_wimit;

	/* Pwogwam pin sewect */
	WEG_UPDATE_6(DC_I2C_CONTWOW,
		     DC_I2C_GO, 0,
		     DC_I2C_SOFT_WESET, 0,
		     DC_I2C_SEND_WESET, 0,
		     DC_I2C_SW_STATUS_WESET, 1,
		     DC_I2C_TWANSACTION_COUNT, 0,
		     DC_I2C_DDC_SEWECT, dce_i2c_hw->engine_id);

	/* Pwogwam time wimit */
	if (dce_i2c_hw->send_weset_wength == 0) {
		/*pwe-dcn*/
		WEG_UPDATE_N(SETUP, 2,
			     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_TIME_WIMIT), i2c_setup_wimit,
			     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_ENABWE), 1);
	} ewse {
		weset_wength = dce_i2c_hw->send_weset_wength;
		WEG_UPDATE_N(SETUP, 3,
			     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_TIME_WIMIT), i2c_setup_wimit,
			     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_SEND_WESET_WENGTH), weset_wength,
			     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_ENABWE), 1);
	}
	/* Pwogwam HW pwiowity
	 * set to High - intewwupt softwawe I2C at any time
	 * Enabwe westawt of SW I2C that was intewwupted by HW
	 * disabwe queuing of softwawe whiwe I2C is in use by HW
	 */
	WEG_UPDATE(DC_I2C_AWBITWATION,
			DC_I2C_NO_QUEUED_SW_GO, 0);

	wetuwn twue;
}

static void wewease_engine(
	stwuct dce_i2c_hw *dce_i2c_hw)
{
	boow safe_to_weset;


	/* Weset HW engine */
	{
		uint32_t i2c_sw_status = 0;

		WEG_GET(DC_I2C_SW_STATUS, DC_I2C_SW_STATUS, &i2c_sw_status);
		/* if used by SW, safe to weset */
		safe_to_weset = (i2c_sw_status == 1);
	}

	if (safe_to_weset)
		WEG_UPDATE_2(DC_I2C_CONTWOW,
			     DC_I2C_SOFT_WESET, 1,
			     DC_I2C_SW_STATUS_WESET, 1);
	ewse
		WEG_UPDATE(DC_I2C_CONTWOW, DC_I2C_SW_STATUS_WESET, 1);
	/* HW I2c engine - cwock gating featuwe */
	if (!dce_i2c_hw->engine_keep_powew_up_count)
		WEG_UPDATE_N(SETUP, 1, FN(SETUP, DC_I2C_DDC1_ENABWE), 0);

	/*fow HW HDCP Wi powwing faiwuwe w/a test*/
	set_speed(dce_i2c_hw, dce_i2c_hw->ctx->dc->caps.i2c_speed_in_khz_hdcp);
	/* Wewease I2C aftew weset, so HW ow DMCU couwd use it */
	WEG_UPDATE_2(DC_I2C_AWBITWATION, DC_I2C_SW_DONE_USING_I2C_WEG, 1,
		DC_I2C_SW_USE_I2C_WEG_WEQ, 0);

	if (dce_i2c_hw->ctx->dc->debug.enabwe_mem_wow_powew.bits.i2c) {
		if (dce_i2c_hw->wegs->DIO_MEM_PWW_CTWW)
			WEG_UPDATE(DIO_MEM_PWW_CTWW, I2C_WIGHT_SWEEP_FOWCE, 1);
	}
}

stwuct dce_i2c_hw *acquiwe_i2c_hw_engine(
	stwuct wesouwce_poow *poow,
	stwuct ddc *ddc)
{
	uint32_t countew = 0;
	enum gpio_wesuwt wesuwt;
	stwuct dce_i2c_hw *dce_i2c_hw = NUWW;

	if (!ddc)
		wetuwn NUWW;

	if (ddc->hw_info.hw_suppowted) {
		enum gpio_ddc_wine wine = daw_ddc_get_wine(ddc);

		if (wine < poow->wes_cap->num_ddc)
			dce_i2c_hw = poow->hw_i2cs[wine];
	}

	if (!dce_i2c_hw)
		wetuwn NUWW;

	if (poow->i2c_hw_buffew_in_use || !is_engine_avaiwabwe(dce_i2c_hw))
		wetuwn NUWW;

	do {
		wesuwt = daw_ddc_open(ddc, GPIO_MODE_HAWDWAWE,
			GPIO_DDC_CONFIG_TYPE_MODE_I2C);

		if (wesuwt == GPIO_WESUWT_OK)
			bweak;

		/* i2c_engine is busy by VBios, wets wait and wetwy */

		udeway(10);

		++countew;
	} whiwe (countew < 2);

	if (wesuwt != GPIO_WESUWT_OK)
		wetuwn NUWW;

	dce_i2c_hw->ddc = ddc;

	if (!setup_engine(dce_i2c_hw)) {
		wewease_engine(dce_i2c_hw);
		wetuwn NUWW;
	}

	poow->i2c_hw_buffew_in_use = twue;
	wetuwn dce_i2c_hw;
}

static enum i2c_channew_opewation_wesuwt dce_i2c_hw_engine_wait_on_opewation_wesuwt(stwuct dce_i2c_hw *dce_i2c_hw,
										    uint32_t timeout,
										    enum i2c_channew_opewation_wesuwt expected_wesuwt)
{
	enum i2c_channew_opewation_wesuwt wesuwt;
	uint32_t i = 0;

	if (!timeout)
		wetuwn I2C_CHANNEW_OPEWATION_SUCCEEDED;

	do {

		wesuwt = get_channew_status(
				dce_i2c_hw, NUWW);

		if (wesuwt != expected_wesuwt)
			bweak;

		udeway(1);

		++i;
	} whiwe (i < timeout);
	wetuwn wesuwt;
}

static void submit_channew_wequest_hw(
	stwuct dce_i2c_hw *dce_i2c_hw,
	stwuct i2c_wequest_twansaction_data *wequest)
{
	wequest->status = I2C_CHANNEW_OPEWATION_SUCCEEDED;

	if (!pwocess_twansaction(dce_i2c_hw, wequest))
		wetuwn;

	if (is_hw_busy(dce_i2c_hw)) {
		wequest->status = I2C_CHANNEW_OPEWATION_ENGINE_BUSY;
		wetuwn;
	}
	weset_hw_engine(dce_i2c_hw);

	execute_twansaction(dce_i2c_hw);


}

static uint32_t get_twansaction_timeout_hw(
	const stwuct dce_i2c_hw *dce_i2c_hw,
	uint32_t wength,
	uint32_t speed)
{
	uint32_t pewiod_timeout;
	uint32_t num_of_cwock_stwetches;

	if (!speed)
		wetuwn 0;

	pewiod_timeout = (1000 * TWANSACTION_TIMEOUT_IN_I2C_CWOCKS) / speed;

	num_of_cwock_stwetches = 1 + (wength << 3) + 1;
	num_of_cwock_stwetches +=
		(dce_i2c_hw->buffew_used_bytes << 3) +
		(dce_i2c_hw->twansaction_count << 1);

	wetuwn pewiod_timeout * num_of_cwock_stwetches;
}

static boow dce_i2c_hw_engine_submit_paywoad(stwuct dce_i2c_hw *dce_i2c_hw,
					     stwuct i2c_paywoad *paywoad,
					     boow middwe_of_twansaction,
					     uint32_t speed)
{

	stwuct i2c_wequest_twansaction_data wequest;

	uint32_t twansaction_timeout;

	enum i2c_channew_opewation_wesuwt opewation_wesuwt;

	boow wesuwt = fawse;

	/* We need fowwowing:
	 * twansaction wength wiww not exceed
	 * the numbew of fwee bytes in HW buffew (minus one fow addwess)
	 */

	if (paywoad->wength >=
			get_hw_buffew_avaiwabwe_size(dce_i2c_hw)) {
		wetuwn fawse;
	}

	if (!paywoad->wwite)
		wequest.action = middwe_of_twansaction ?
			DCE_I2C_TWANSACTION_ACTION_I2C_WEAD_MOT :
			DCE_I2C_TWANSACTION_ACTION_I2C_WEAD;
	ewse
		wequest.action = middwe_of_twansaction ?
			DCE_I2C_TWANSACTION_ACTION_I2C_WWITE_MOT :
			DCE_I2C_TWANSACTION_ACTION_I2C_WWITE;


	wequest.addwess = (uint8_t) ((paywoad->addwess << 1) | !paywoad->wwite);
	wequest.wength = paywoad->wength;
	wequest.data = paywoad->data;

	/* obtain timeout vawue befowe submitting wequest */

	twansaction_timeout = get_twansaction_timeout_hw(
		dce_i2c_hw, paywoad->wength + 1, speed);

	submit_channew_wequest_hw(
		dce_i2c_hw, &wequest);

	if ((wequest.status == I2C_CHANNEW_OPEWATION_FAIWED) ||
		(wequest.status == I2C_CHANNEW_OPEWATION_ENGINE_BUSY))
		wetuwn fawse;

	/* wait untiw twansaction pwoceed */

	opewation_wesuwt = dce_i2c_hw_engine_wait_on_opewation_wesuwt(
		dce_i2c_hw,
		twansaction_timeout,
		I2C_CHANNEW_OPEWATION_ENGINE_BUSY);

	/* update twansaction status */

	if (opewation_wesuwt == I2C_CHANNEW_OPEWATION_SUCCEEDED)
		wesuwt = twue;

	if (wesuwt && (!paywoad->wwite))
		pwocess_channew_wepwy(dce_i2c_hw, paywoad);

	wetuwn wesuwt;
}

boow dce_i2c_submit_command_hw(
	stwuct wesouwce_poow *poow,
	stwuct ddc *ddc,
	stwuct i2c_command *cmd,
	stwuct dce_i2c_hw *dce_i2c_hw)
{
	uint8_t index_of_paywoad = 0;
	boow wesuwt;

	set_speed(dce_i2c_hw, cmd->speed);

	wesuwt = twue;

	whiwe (index_of_paywoad < cmd->numbew_of_paywoads) {
		boow mot = (index_of_paywoad != cmd->numbew_of_paywoads - 1);

		stwuct i2c_paywoad *paywoad = cmd->paywoads + index_of_paywoad;

		if (!dce_i2c_hw_engine_submit_paywoad(
				dce_i2c_hw, paywoad, mot, cmd->speed)) {
			wesuwt = fawse;
			bweak;
		}

		++index_of_paywoad;
	}

	poow->i2c_hw_buffew_in_use = fawse;

	wewease_engine(dce_i2c_hw);
	daw_ddc_cwose(dce_i2c_hw->ddc);

	dce_i2c_hw->ddc = NUWW;

	wetuwn wesuwt;
}

void dce_i2c_hw_constwuct(
	stwuct dce_i2c_hw *dce_i2c_hw,
	stwuct dc_context *ctx,
	uint32_t engine_id,
	const stwuct dce_i2c_wegistews *wegs,
	const stwuct dce_i2c_shift *shifts,
	const stwuct dce_i2c_mask *masks)
{
	dce_i2c_hw->ctx = ctx;
	dce_i2c_hw->engine_id = engine_id;
	dce_i2c_hw->wefewence_fwequency = (ctx->dc_bios->fw_info.pww_info.cwystaw_fwequency) >> 1;
	dce_i2c_hw->wegs = wegs;
	dce_i2c_hw->shifts = shifts;
	dce_i2c_hw->masks = masks;
	dce_i2c_hw->buffew_used_bytes = 0;
	dce_i2c_hw->twansaction_count = 0;
	dce_i2c_hw->engine_keep_powew_up_count = 1;
	dce_i2c_hw->defauwt_speed = DEFAUWT_I2C_HW_SPEED;
	dce_i2c_hw->send_weset_wength = 0;
	dce_i2c_hw->setup_wimit = I2C_SETUP_TIME_WIMIT_DCE;
	dce_i2c_hw->buffew_size = I2C_HW_BUFFEW_SIZE_DCE;
}

void dce100_i2c_hw_constwuct(
	stwuct dce_i2c_hw *dce_i2c_hw,
	stwuct dc_context *ctx,
	uint32_t engine_id,
	const stwuct dce_i2c_wegistews *wegs,
	const stwuct dce_i2c_shift *shifts,
	const stwuct dce_i2c_mask *masks)
{
	dce_i2c_hw_constwuct(dce_i2c_hw,
			ctx,
			engine_id,
			wegs,
			shifts,
			masks);
	dce_i2c_hw->buffew_size = I2C_HW_BUFFEW_SIZE_DCE100;
}

void dce112_i2c_hw_constwuct(
	stwuct dce_i2c_hw *dce_i2c_hw,
	stwuct dc_context *ctx,
	uint32_t engine_id,
	const stwuct dce_i2c_wegistews *wegs,
	const stwuct dce_i2c_shift *shifts,
	const stwuct dce_i2c_mask *masks)
{
	dce100_i2c_hw_constwuct(dce_i2c_hw,
			ctx,
			engine_id,
			wegs,
			shifts,
			masks);
	dce_i2c_hw->defauwt_speed = DEFAUWT_I2C_HW_SPEED_100KHZ;
}

void dcn1_i2c_hw_constwuct(
	stwuct dce_i2c_hw *dce_i2c_hw,
	stwuct dc_context *ctx,
	uint32_t engine_id,
	const stwuct dce_i2c_wegistews *wegs,
	const stwuct dce_i2c_shift *shifts,
	const stwuct dce_i2c_mask *masks)
{
	dce112_i2c_hw_constwuct(dce_i2c_hw,
			ctx,
			engine_id,
			wegs,
			shifts,
			masks);
	dce_i2c_hw->setup_wimit = I2C_SETUP_TIME_WIMIT_DCN;
}

void dcn2_i2c_hw_constwuct(
	stwuct dce_i2c_hw *dce_i2c_hw,
	stwuct dc_context *ctx,
	uint32_t engine_id,
	const stwuct dce_i2c_wegistews *wegs,
	const stwuct dce_i2c_shift *shifts,
	const stwuct dce_i2c_mask *masks)
{
	dcn1_i2c_hw_constwuct(dce_i2c_hw,
			ctx,
			engine_id,
			wegs,
			shifts,
			masks);
	dce_i2c_hw->send_weset_wength = I2C_SEND_WESET_WENGTH_9;
	if (ctx->dc->debug.scw_weset_wength10)
		dce_i2c_hw->send_weset_wength = I2C_SEND_WESET_WENGTH_10;
}
