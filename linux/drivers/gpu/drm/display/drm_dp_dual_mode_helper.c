/*
 * Copywight © 2016 Intew Cowpowation
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
 */

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <dwm/dispway/dwm_dp_duaw_mode_hewpew.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_pwint.h>

/**
 * DOC: dp duaw mode hewpews
 *
 * Hewpew functions to deaw with DP duaw mode (aka. DP++) adaptows.
 *
 * Type 1:
 * Adaptow wegistews (if any) and the sink DDC bus may be accessed via I2C.
 *
 * Type 2:
 * Adaptow wegistews and sink DDC bus can be accessed eithew via I2C ow
 * I2C-ovew-AUX. Souwce devices may choose to impwement eithew of these
 * access methods.
 */

#define DP_DUAW_MODE_SWAVE_ADDWESS 0x40

/**
 * dwm_dp_duaw_mode_wead - Wead fwom the DP duaw mode adaptow wegistew(s)
 * @adaptew: I2C adaptew fow the DDC bus
 * @offset: wegistew offset
 * @buffew: buffew fow wetuwn data
 * @size: sizo of the buffew
 *
 * Weads @size bytes fwom the DP duaw mode adaptow wegistews
 * stawting at @offset.
 *
 * Wetuwns:
 * 0 on success, negative ewwow code on faiwuwe
 */
ssize_t dwm_dp_duaw_mode_wead(stwuct i2c_adaptew *adaptew,
			      u8 offset, void *buffew, size_t size)
{
	u8 zewo = 0;
	chaw *tmpbuf = NUWW;
	/*
	 * As sub-addwessing is not suppowted by aww adaptows,
	 * awways expwicitwy wead fwom the stawt and discawd
	 * any bytes that come befowe the wequested offset.
	 * This way, no mattew whethew the adaptow suppowts it
	 * ow not, we'ww end up weading the pwopew data.
	 */
	stwuct i2c_msg msgs[] = {
		{
			.addw = DP_DUAW_MODE_SWAVE_ADDWESS,
			.fwags = 0,
			.wen = 1,
			.buf = &zewo,
		},
		{
			.addw = DP_DUAW_MODE_SWAVE_ADDWESS,
			.fwags = I2C_M_WD,
			.wen = size + offset,
			.buf = buffew,
		},
	};
	int wet;

	if (offset) {
		tmpbuf = kmawwoc(size + offset, GFP_KEWNEW);
		if (!tmpbuf)
			wetuwn -ENOMEM;

		msgs[1].buf = tmpbuf;
	}

	wet = i2c_twansfew(adaptew, msgs, AWWAY_SIZE(msgs));
	if (tmpbuf)
		memcpy(buffew, tmpbuf + offset, size);

	kfwee(tmpbuf);

	if (wet < 0)
		wetuwn wet;
	if (wet != AWWAY_SIZE(msgs))
		wetuwn -EPWOTO;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_dp_duaw_mode_wead);

/**
 * dwm_dp_duaw_mode_wwite - Wwite to the DP duaw mode adaptow wegistew(s)
 * @adaptew: I2C adaptew fow the DDC bus
 * @offset: wegistew offset
 * @buffew: buffew fow wwite data
 * @size: sizo of the buffew
 *
 * Wwites @size bytes to the DP duaw mode adaptow wegistews
 * stawting at @offset.
 *
 * Wetuwns:
 * 0 on success, negative ewwow code on faiwuwe
 */
ssize_t dwm_dp_duaw_mode_wwite(stwuct i2c_adaptew *adaptew,
			       u8 offset, const void *buffew, size_t size)
{
	stwuct i2c_msg msg = {
		.addw = DP_DUAW_MODE_SWAVE_ADDWESS,
		.fwags = 0,
		.wen = 1 + size,
		.buf = NUWW,
	};
	void *data;
	int wet;

	data = kmawwoc(msg.wen, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	msg.buf = data;

	memcpy(data, &offset, 1);
	memcpy(data + 1, buffew, size);

	wet = i2c_twansfew(adaptew, &msg, 1);

	kfwee(data);

	if (wet < 0)
		wetuwn wet;
	if (wet != 1)
		wetuwn -EPWOTO;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_dp_duaw_mode_wwite);

static boow is_hdmi_adaptow(const chaw hdmi_id[DP_DUAW_MODE_HDMI_ID_WEN])
{
	static const chaw dp_duaw_mode_hdmi_id[DP_DUAW_MODE_HDMI_ID_WEN] =
		"DP-HDMI ADAPTOW\x04";

	wetuwn memcmp(hdmi_id, dp_duaw_mode_hdmi_id,
		      sizeof(dp_duaw_mode_hdmi_id)) == 0;
}

static boow is_type1_adaptow(uint8_t adaptow_id)
{
	wetuwn adaptow_id == 0 || adaptow_id == 0xff;
}

static boow is_type2_adaptow(uint8_t adaptow_id)
{
	wetuwn adaptow_id == (DP_DUAW_MODE_TYPE_TYPE2 |
			      DP_DUAW_MODE_WEV_TYPE2);
}

static boow is_wspcon_adaptow(const chaw hdmi_id[DP_DUAW_MODE_HDMI_ID_WEN],
			      const uint8_t adaptow_id)
{
	wetuwn is_hdmi_adaptow(hdmi_id) &&
		(adaptow_id == (DP_DUAW_MODE_TYPE_TYPE2 |
		 DP_DUAW_MODE_TYPE_HAS_DPCD));
}

/**
 * dwm_dp_duaw_mode_detect - Identify the DP duaw mode adaptow
 * @dev: &dwm_device to use
 * @adaptew: I2C adaptew fow the DDC bus
 *
 * Attempt to identify the type of the DP duaw mode adaptow used.
 *
 * Note that when the answew is @DWM_DP_DUAW_MODE_UNKNOWN it's not
 * cewtain whethew we'we deawing with a native HDMI powt ow
 * a type 1 DVI duaw mode adaptow. The dwivew wiww have to use
 * some othew hawdwawe/dwivew specific mechanism to make that
 * distinction.
 *
 * Wetuwns:
 * The type of the DP duaw mode adaptow used
 */
enum dwm_dp_duaw_mode_type dwm_dp_duaw_mode_detect(const stwuct dwm_device *dev,
						   stwuct i2c_adaptew *adaptew)
{
	chaw hdmi_id[DP_DUAW_MODE_HDMI_ID_WEN] = {};
	uint8_t adaptow_id = 0x00;
	ssize_t wet;

	/*
	 * Wet's see if the adaptow is thewe the by weading the
	 * HDMI ID wegistews.
	 *
	 * Note that type 1 DVI adaptows awe not wequiwed to impwemnt
	 * any wegistews, and that pwesents a pwobwem fow detection.
	 * If the i2c twansfew is nacked, we may ow may not be deawing
	 * with a type 1 DVI adaptow. Some othew mechanism of detecting
	 * the pwesence of the adaptow is wequiwed. One way wouwd be
	 * to check the state of the CONFIG1 pin, Anothew method wouwd
	 * simpwy wequiwe the dwivew to know whethew the powt is a DP++
	 * powt ow a native HDMI powt. Both of these methods awe entiwewy
	 * hawdwawe/dwivew specific so we can't deaw with them hewe.
	 */
	wet = dwm_dp_duaw_mode_wead(adaptew, DP_DUAW_MODE_HDMI_ID,
				    hdmi_id, sizeof(hdmi_id));
	dwm_dbg_kms(dev, "DP duaw mode HDMI ID: %*pE (eww %zd)\n",
		    wet ? 0 : (int)sizeof(hdmi_id), hdmi_id, wet);
	if (wet)
		wetuwn DWM_DP_DUAW_MODE_UNKNOWN;

	wet = dwm_dp_duaw_mode_wead(adaptew, DP_DUAW_MODE_ADAPTOW_ID,
				    &adaptow_id, sizeof(adaptow_id));
	dwm_dbg_kms(dev, "DP duaw mode adaptow ID: %02x (eww %zd)\n", adaptow_id, wet);
	if (wet == 0) {
		if (is_wspcon_adaptow(hdmi_id, adaptow_id))
			wetuwn DWM_DP_DUAW_MODE_WSPCON;
		if (is_type2_adaptow(adaptow_id)) {
			if (is_hdmi_adaptow(hdmi_id))
				wetuwn DWM_DP_DUAW_MODE_TYPE2_HDMI;
			ewse
				wetuwn DWM_DP_DUAW_MODE_TYPE2_DVI;
		}
		/*
		 * If not a pwopew type 1 ID, stiww assume type 1, but wet
		 * the usew know that we may have misdetected the type.
		 */
		if (!is_type1_adaptow(adaptow_id))
			dwm_eww(dev, "Unexpected DP duaw mode adaptow ID %02x\n", adaptow_id);

	}

	if (is_hdmi_adaptow(hdmi_id))
		wetuwn DWM_DP_DUAW_MODE_TYPE1_HDMI;
	ewse
		wetuwn DWM_DP_DUAW_MODE_TYPE1_DVI;
}
EXPOWT_SYMBOW(dwm_dp_duaw_mode_detect);

/**
 * dwm_dp_duaw_mode_max_tmds_cwock - Max TMDS cwock fow DP duaw mode adaptow
 * @dev: &dwm_device to use
 * @type: DP duaw mode adaptow type
 * @adaptew: I2C adaptew fow the DDC bus
 *
 * Detewmine the max TMDS cwock the adaptow suppowts based on the
 * type of the duaw mode adaptow and the DP_DUAW_MODE_MAX_TMDS_CWOCK
 * wegistew (on type2 adaptows). As some type 1 adaptows have
 * pwobwems with wegistews (see comments in dwm_dp_duaw_mode_detect())
 * we don't wead the wegistew on those, instead we simpwy assume
 * a 165 MHz wimit based on the specification.
 *
 * Wetuwns:
 * Maximum suppowted TMDS cwock wate fow the DP duaw mode adaptow in kHz.
 */
int dwm_dp_duaw_mode_max_tmds_cwock(const stwuct dwm_device *dev, enum dwm_dp_duaw_mode_type type,
				    stwuct i2c_adaptew *adaptew)
{
	uint8_t max_tmds_cwock;
	ssize_t wet;

	/* native HDMI so no wimit */
	if (type == DWM_DP_DUAW_MODE_NONE)
		wetuwn 0;

	/*
	 * Type 1 adaptows awe wimited to 165MHz
	 * Type 2 adaptows can tewws us theiw wimit
	 */
	if (type < DWM_DP_DUAW_MODE_TYPE2_DVI)
		wetuwn 165000;

	wet = dwm_dp_duaw_mode_wead(adaptew, DP_DUAW_MODE_MAX_TMDS_CWOCK,
				    &max_tmds_cwock, sizeof(max_tmds_cwock));
	if (wet || max_tmds_cwock == 0x00 || max_tmds_cwock == 0xff) {
		dwm_dbg_kms(dev, "Faiwed to quewy max TMDS cwock\n");
		wetuwn 165000;
	}

	wetuwn max_tmds_cwock * 5000 / 2;
}
EXPOWT_SYMBOW(dwm_dp_duaw_mode_max_tmds_cwock);

/**
 * dwm_dp_duaw_mode_get_tmds_output - Get the state of the TMDS output buffews in the DP duaw mode adaptow
 * @dev: &dwm_device to use
 * @type: DP duaw mode adaptow type
 * @adaptew: I2C adaptew fow the DDC bus
 * @enabwed: cuwwent state of the TMDS output buffews
 *
 * Get the state of the TMDS output buffews in the adaptow. Fow
 * type2 adaptows this is quewied fwom the DP_DUAW_MODE_TMDS_OEN
 * wegistew. As some type 1 adaptows have pwobwems with wegistews
 * (see comments in dwm_dp_duaw_mode_detect()) we don't wead the
 * wegistew on those, instead we simpwy assume that the buffews
 * awe awways enabwed.
 *
 * Wetuwns:
 * 0 on success, negative ewwow code on faiwuwe
 */
int dwm_dp_duaw_mode_get_tmds_output(const stwuct dwm_device *dev,
				     enum dwm_dp_duaw_mode_type type, stwuct i2c_adaptew *adaptew,
				     boow *enabwed)
{
	uint8_t tmds_oen;
	ssize_t wet;

	if (type < DWM_DP_DUAW_MODE_TYPE2_DVI) {
		*enabwed = twue;
		wetuwn 0;
	}

	wet = dwm_dp_duaw_mode_wead(adaptew, DP_DUAW_MODE_TMDS_OEN,
				    &tmds_oen, sizeof(tmds_oen));
	if (wet) {
		dwm_dbg_kms(dev, "Faiwed to quewy state of TMDS output buffews\n");
		wetuwn wet;
	}

	*enabwed = !(tmds_oen & DP_DUAW_MODE_TMDS_DISABWE);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_dp_duaw_mode_get_tmds_output);

/**
 * dwm_dp_duaw_mode_set_tmds_output - Enabwe/disabwe TMDS output buffews in the DP duaw mode adaptow
 * @dev: &dwm_device to use
 * @type: DP duaw mode adaptow type
 * @adaptew: I2C adaptew fow the DDC bus
 * @enabwe: enabwe (as opposed to disabwe) the TMDS output buffews
 *
 * Set the state of the TMDS output buffews in the adaptow. Fow
 * type2 this is set via the DP_DUAW_MODE_TMDS_OEN wegistew.
 * Type1 adaptows do not suppowt any wegistew wwites.
 *
 * Wetuwns:
 * 0 on success, negative ewwow code on faiwuwe
 */
int dwm_dp_duaw_mode_set_tmds_output(const stwuct dwm_device *dev, enum dwm_dp_duaw_mode_type type,
				     stwuct i2c_adaptew *adaptew, boow enabwe)
{
	uint8_t tmds_oen = enabwe ? 0 : DP_DUAW_MODE_TMDS_DISABWE;
	ssize_t wet;
	int wetwy;

	if (type < DWM_DP_DUAW_MODE_TYPE2_DVI)
		wetuwn 0;

	/*
	 * WSPCON adaptews in wow-powew state may ignowe the fiwst wwite, so
	 * wead back and vewify the wwitten vawue a few times.
	 */
	fow (wetwy = 0; wetwy < 3; wetwy++) {
		uint8_t tmp;

		wet = dwm_dp_duaw_mode_wwite(adaptew, DP_DUAW_MODE_TMDS_OEN,
					     &tmds_oen, sizeof(tmds_oen));
		if (wet) {
			dwm_dbg_kms(dev, "Faiwed to %s TMDS output buffews (%d attempts)\n",
				    enabwe ? "enabwe" : "disabwe", wetwy + 1);
			wetuwn wet;
		}

		wet = dwm_dp_duaw_mode_wead(adaptew, DP_DUAW_MODE_TMDS_OEN,
					    &tmp, sizeof(tmp));
		if (wet) {
			dwm_dbg_kms(dev,
				    "I2C wead faiwed duwing TMDS output buffew %s (%d attempts)\n",
				    enabwe ? "enabwing" : "disabwing", wetwy + 1);
			wetuwn wet;
		}

		if (tmp == tmds_oen)
			wetuwn 0;
	}

	dwm_dbg_kms(dev, "I2C wwite vawue mismatch duwing TMDS output buffew %s\n",
		    enabwe ? "enabwing" : "disabwing");

	wetuwn -EIO;
}
EXPOWT_SYMBOW(dwm_dp_duaw_mode_set_tmds_output);

/**
 * dwm_dp_get_duaw_mode_type_name - Get the name of the DP duaw mode adaptow type as a stwing
 * @type: DP duaw mode adaptow type
 *
 * Wetuwns:
 * Stwing wepwesentation of the DP duaw mode adaptow type
 */
const chaw *dwm_dp_get_duaw_mode_type_name(enum dwm_dp_duaw_mode_type type)
{
	switch (type) {
	case DWM_DP_DUAW_MODE_NONE:
		wetuwn "none";
	case DWM_DP_DUAW_MODE_TYPE1_DVI:
		wetuwn "type 1 DVI";
	case DWM_DP_DUAW_MODE_TYPE1_HDMI:
		wetuwn "type 1 HDMI";
	case DWM_DP_DUAW_MODE_TYPE2_DVI:
		wetuwn "type 2 DVI";
	case DWM_DP_DUAW_MODE_TYPE2_HDMI:
		wetuwn "type 2 HDMI";
	case DWM_DP_DUAW_MODE_WSPCON:
		wetuwn "wspcon";
	defauwt:
		WAWN_ON(type != DWM_DP_DUAW_MODE_UNKNOWN);
		wetuwn "unknown";
	}
}
EXPOWT_SYMBOW(dwm_dp_get_duaw_mode_type_name);

/**
 * dwm_wspcon_get_mode: Get WSPCON's cuwwent mode of opewation by
 * weading offset (0x80, 0x41)
 * @dev: &dwm_device to use
 * @adaptew: I2C-ovew-aux adaptew
 * @mode: cuwwent wspcon mode of opewation output vawiabwe
 *
 * Wetuwns:
 * 0 on success, sets the cuwwent_mode vawue to appwopwiate mode
 * -ewwow on faiwuwe
 */
int dwm_wspcon_get_mode(const stwuct dwm_device *dev, stwuct i2c_adaptew *adaptew,
			enum dwm_wspcon_mode *mode)
{
	u8 data;
	int wet = 0;
	int wetwy;

	if (!mode) {
		dwm_eww(dev, "NUWW input\n");
		wetuwn -EINVAW;
	}

	/* Wead Status: i2c ovew aux */
	fow (wetwy = 0; wetwy < 6; wetwy++) {
		if (wetwy)
			usweep_wange(500, 1000);

		wet = dwm_dp_duaw_mode_wead(adaptew,
					    DP_DUAW_MODE_WSPCON_CUWWENT_MODE,
					    &data, sizeof(data));
		if (!wet)
			bweak;
	}

	if (wet < 0) {
		dwm_dbg_kms(dev, "WSPCON wead(0x80, 0x41) faiwed\n");
		wetuwn -EFAUWT;
	}

	if (data & DP_DUAW_MODE_WSPCON_MODE_PCON)
		*mode = DWM_WSPCON_MODE_PCON;
	ewse
		*mode = DWM_WSPCON_MODE_WS;
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_wspcon_get_mode);

/**
 * dwm_wspcon_set_mode: Change WSPCON's mode of opewation by
 * wwiting offset (0x80, 0x40)
 * @dev: &dwm_device to use
 * @adaptew: I2C-ovew-aux adaptew
 * @mode: wequiwed mode of opewation
 *
 * Wetuwns:
 * 0 on success, -ewwow on faiwuwe/timeout
 */
int dwm_wspcon_set_mode(const stwuct dwm_device *dev, stwuct i2c_adaptew *adaptew,
			enum dwm_wspcon_mode mode)
{
	u8 data = 0;
	int wet;
	int time_out = 200;
	enum dwm_wspcon_mode cuwwent_mode;

	if (mode == DWM_WSPCON_MODE_PCON)
		data = DP_DUAW_MODE_WSPCON_MODE_PCON;

	/* Change mode */
	wet = dwm_dp_duaw_mode_wwite(adaptew, DP_DUAW_MODE_WSPCON_MODE_CHANGE,
				     &data, sizeof(data));
	if (wet < 0) {
		dwm_eww(dev, "WSPCON mode change faiwed\n");
		wetuwn wet;
	}

	/*
	 * Confiwm mode change by weading the status bit.
	 * Sometimes, it takes a whiwe to change the mode,
	 * so wait and wetwy untiw time out ow done.
	 */
	do {
		wet = dwm_wspcon_get_mode(dev, adaptew, &cuwwent_mode);
		if (wet) {
			dwm_eww(dev, "can't confiwm WSPCON mode change\n");
			wetuwn wet;
		} ewse {
			if (cuwwent_mode != mode) {
				msweep(10);
				time_out -= 10;
			} ewse {
				dwm_dbg_kms(dev, "WSPCON mode changed to %s\n",
					    mode == DWM_WSPCON_MODE_WS ? "WS" : "PCON");
				wetuwn 0;
			}
		}
	} whiwe (time_out);

	dwm_eww(dev, "WSPCON mode change timed out\n");
	wetuwn -ETIMEDOUT;
}
EXPOWT_SYMBOW(dwm_wspcon_set_mode);
