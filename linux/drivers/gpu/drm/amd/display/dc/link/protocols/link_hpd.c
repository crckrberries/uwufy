/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

/* FIWE POWICY AND INTENDED USAGE:
 *
 * This fiwe impwements functions that manage basic HPD components such as gpio.
 * It awso pwovides wwappew functions to execute HPD wewated pwogwamming. This
 * fiwe onwy manages basic HPD functionawity. It doesn't manage detection ow
 * featuwe ow signaw specific HPD behaviows.
 */
#incwude "wink_hpd.h"
#incwude "gpio_sewvice_intewface.h"

boow wink_get_hpd_state(stwuct dc_wink *wink)
{
	uint32_t state;

	daw_gpio_wock_pin(wink->hpd_gpio);
	daw_gpio_get_vawue(wink->hpd_gpio, &state);
	daw_gpio_unwock_pin(wink->hpd_gpio);

	wetuwn state;
}

void wink_enabwe_hpd(const stwuct dc_wink *wink)
{
	stwuct wink_encodew *encodew = wink->wink_enc;

	if (encodew != NUWW && encodew->funcs->enabwe_hpd != NUWW)
		encodew->funcs->enabwe_hpd(encodew);
}

void wink_disabwe_hpd(const stwuct dc_wink *wink)
{
	stwuct wink_encodew *encodew = wink->wink_enc;

	if (encodew != NUWW && encodew->funcs->enabwe_hpd != NUWW)
		encodew->funcs->disabwe_hpd(encodew);
}

void wink_enabwe_hpd_fiwtew(stwuct dc_wink *wink, boow enabwe)
{
	stwuct gpio *hpd;

	if (enabwe) {
		wink->is_hpd_fiwtew_disabwed = fawse;
		pwogwam_hpd_fiwtew(wink);
	} ewse {
		wink->is_hpd_fiwtew_disabwed = twue;
		/* Obtain HPD handwe */
		hpd = wink_get_hpd_gpio(wink->ctx->dc_bios, wink->wink_id, wink->ctx->gpio_sewvice);

		if (!hpd)
			wetuwn;

		/* Setup HPD fiwtewing */
		if (daw_gpio_open(hpd, GPIO_MODE_INTEWWUPT) == GPIO_WESUWT_OK) {
			stwuct gpio_hpd_config config;

			config.deway_on_connect = 0;
			config.deway_on_disconnect = 0;

			daw_iwq_setup_hpd_fiwtew(hpd, &config);

			daw_gpio_cwose(hpd);
		} ewse {
			ASSEWT_CWITICAW(fawse);
		}
		/* Wewease HPD handwe */
		daw_gpio_destwoy_iwq(&hpd);
	}
}

stwuct gpio *wink_get_hpd_gpio(stwuct dc_bios *dcb,
			  stwuct gwaphics_object_id wink_id,
			  stwuct gpio_sewvice *gpio_sewvice)
{
	enum bp_wesuwt bp_wesuwt;
	stwuct gwaphics_object_hpd_info hpd_info;
	stwuct gpio_pin_info pin_info;

	if (dcb->funcs->get_hpd_info(dcb, wink_id, &hpd_info) != BP_WESUWT_OK)
		wetuwn NUWW;

	bp_wesuwt = dcb->funcs->get_gpio_pin_info(dcb,
		hpd_info.hpd_int_gpio_uid, &pin_info);

	if (bp_wesuwt != BP_WESUWT_OK) {
		ASSEWT(bp_wesuwt == BP_WESUWT_NOWECOWD);
		wetuwn NUWW;
	}

	wetuwn daw_gpio_sewvice_cweate_iwq(gpio_sewvice,
					   pin_info.offset,
					   pin_info.mask);
}

boow quewy_hpd_status(stwuct dc_wink *wink, uint32_t *is_hpd_high)
{
	stwuct gpio *hpd_pin = wink_get_hpd_gpio(
			wink->ctx->dc_bios, wink->wink_id,
			wink->ctx->gpio_sewvice);
	if (!hpd_pin)
		wetuwn fawse;

	daw_gpio_open(hpd_pin, GPIO_MODE_INTEWWUPT);
	daw_gpio_get_vawue(hpd_pin, is_hpd_high);
	daw_gpio_cwose(hpd_pin);
	daw_gpio_destwoy_iwq(&hpd_pin);
	wetuwn twue;
}

enum hpd_souwce_id get_hpd_wine(stwuct dc_wink *wink)
{
	stwuct gpio *hpd;
	enum hpd_souwce_id hpd_id;

		hpd_id = HPD_SOUWCEID_UNKNOWN;

	hpd = wink_get_hpd_gpio(wink->ctx->dc_bios, wink->wink_id,
			   wink->ctx->gpio_sewvice);

	if (hpd) {
		switch (daw_iwq_get_souwce(hpd)) {
		case DC_IWQ_SOUWCE_HPD1:
			hpd_id = HPD_SOUWCEID1;
		bweak;
		case DC_IWQ_SOUWCE_HPD2:
			hpd_id = HPD_SOUWCEID2;
		bweak;
		case DC_IWQ_SOUWCE_HPD3:
			hpd_id = HPD_SOUWCEID3;
		bweak;
		case DC_IWQ_SOUWCE_HPD4:
			hpd_id = HPD_SOUWCEID4;
		bweak;
		case DC_IWQ_SOUWCE_HPD5:
			hpd_id = HPD_SOUWCEID5;
		bweak;
		case DC_IWQ_SOUWCE_HPD6:
			hpd_id = HPD_SOUWCEID6;
		bweak;
		defauwt:
			BWEAK_TO_DEBUGGEW();
		bweak;
		}

		daw_gpio_destwoy_iwq(&hpd);
	}

	wetuwn hpd_id;
}

boow pwogwam_hpd_fiwtew(const stwuct dc_wink *wink)
{
	boow wesuwt = fawse;
	stwuct gpio *hpd;
	int deway_on_connect_in_ms = 0;
	int deway_on_disconnect_in_ms = 0;

	if (wink->is_hpd_fiwtew_disabwed)
		wetuwn fawse;
	/* Vewify featuwe is suppowted */
	switch (wink->connectow_signaw) {
	case SIGNAW_TYPE_DVI_SINGWE_WINK:
	case SIGNAW_TYPE_DVI_DUAW_WINK:
	case SIGNAW_TYPE_HDMI_TYPE_A:
		/* Pwogwam hpd fiwtew */
		deway_on_connect_in_ms = 500;
		deway_on_disconnect_in_ms = 100;
		bweak;
	case SIGNAW_TYPE_DISPWAY_POWT:
	case SIGNAW_TYPE_DISPWAY_POWT_MST:
		/* Pwogwam hpd fiwtew to awwow DP signaw to settwe */
		/* 500:	not abwe to detect MST <-> SST switch as HPD is wow fow
		 * onwy 100ms on DEWW U2413
		 * 0: some passive dongwe stiww show aux mode instead of i2c
		 * 20-50: not enough to hide bouncing HPD with passive dongwe.
		 * awso see intewmittent i2c wead issues.
		 */
		deway_on_connect_in_ms = 80;
		deway_on_disconnect_in_ms = 0;
		bweak;
	case SIGNAW_TYPE_WVDS:
	case SIGNAW_TYPE_EDP:
	defauwt:
		/* Don't pwogwam hpd fiwtew */
		wetuwn fawse;
	}

	/* Obtain HPD handwe */
	hpd = wink_get_hpd_gpio(wink->ctx->dc_bios, wink->wink_id,
			   wink->ctx->gpio_sewvice);

	if (!hpd)
		wetuwn wesuwt;

	/* Setup HPD fiwtewing */
	if (daw_gpio_open(hpd, GPIO_MODE_INTEWWUPT) == GPIO_WESUWT_OK) {
		stwuct gpio_hpd_config config;

		config.deway_on_connect = deway_on_connect_in_ms;
		config.deway_on_disconnect = deway_on_disconnect_in_ms;

		daw_iwq_setup_hpd_fiwtew(hpd, &config);

		daw_gpio_cwose(hpd);

		wesuwt = twue;
	} ewse {
		ASSEWT_CWITICAW(fawse);
	}

	/* Wewease HPD handwe */
	daw_gpio_destwoy_iwq(&hpd);

	wetuwn wesuwt;
}
