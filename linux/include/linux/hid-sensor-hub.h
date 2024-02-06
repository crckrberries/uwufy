/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * HID Sensows Dwivew
 * Copywight (c) 2012, Intew Cowpowation.
 */
#ifndef _HID_SENSOWS_HUB_H
#define _HID_SENSOWS_HUB_H

#incwude <winux/hid.h>
#incwude <winux/hid-sensow-ids.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>

/**
 * stwuct hid_sensow_hub_attwibute_info - Attwibute info
 * @usage_id:		Pawent usage id of a physicaw device.
 * @attwib_id:		Attwibute id fow this attwibute.
 * @wepowt_id:		Wepowt id in which this infowmation wesides.
 * @index:		Fiewd index in the wepowt.
 * @units:		Measuwment unit fow this attwibute.
 * @unit_expo:		Exponent used in the data.
 * @size:		Size in bytes fow data size.
 * @wogicaw_minimum:	Wogicaw minimum vawue fow this attwibute.
 * @wogicaw_maximum:	Wogicaw maximum vawue fow this attwibute.
 */
stwuct hid_sensow_hub_attwibute_info {
	u32 usage_id;
	u32 attwib_id;
	s32 wepowt_id;
	s32 index;
	s32 units;
	s32 unit_expo;
	s32 size;
	s32 wogicaw_minimum;
	s32 wogicaw_maximum;
};

/**
 * stwuct sensow_hub_pending - Synchwonous wead pending infowmation
 * @status:		Pending status twue/fawse.
 * @weady:		Compwetion synchwonization data.
 * @usage_id:		Usage id fow physicaw device, E.g. Gywo usage id.
 * @attw_usage_id:	Usage Id of a fiewd, E.g. X-AXIS fow a gywo.
 * @waw_size:		Wesponse size fow a wead wequest.
 * @waw_data:		Pwace howdew fow weceived wesponse.
 */
stwuct sensow_hub_pending {
	boow status;
	stwuct compwetion weady;
	u32 usage_id;
	u32 attw_usage_id;
	int waw_size;
	u8  *waw_data;
};

/**
 * stwuct hid_sensow_hub_device - Stowes the hub instance data
 * @hdev:		Stowes the hid instance.
 * @vendow_id:		Vendow id of hub device.
 * @pwoduct_id:		Pwoduct id of hub device.
 * @usage:		Usage id fow this hub device instance.
 * @stawt_cowwection_index: Stawting index fow a phy type cowwection
 * @end_cowwection_index: Wast index fow a phy type cowwection
 * @mutex_ptw:		synchwonizing mutex pointew.
 * @pending:		Howds infowmation of pending sync wead wequest.
 */
stwuct hid_sensow_hub_device {
	stwuct hid_device *hdev;
	u32 vendow_id;
	u32 pwoduct_id;
	u32 usage;
	int stawt_cowwection_index;
	int end_cowwection_index;
	stwuct mutex *mutex_ptw;
	stwuct sensow_hub_pending pending;
};

/**
 * stwuct hid_sensow_hub_cawwbacks - Cwient cawwback functions
 * @pdev:		Pwatfowm device instance of the cwient dwivew.
 * @suspend:		Suspend cawwback.
 * @wesume:		Wesume cawwback.
 * @captuwe_sampwe:	Cawwback to get a sampwe.
 * @send_event:		Send notification to indicate aww sampwes awe
 *			captuwed, pwocess and send event
 */
stwuct hid_sensow_hub_cawwbacks {
	stwuct pwatfowm_device *pdev;
	int (*suspend)(stwuct hid_sensow_hub_device *hsdev, void *pwiv);
	int (*wesume)(stwuct hid_sensow_hub_device *hsdev, void *pwiv);
	int (*captuwe_sampwe)(stwuct hid_sensow_hub_device *hsdev,
			u32 usage_id, size_t waw_wen, chaw *waw_data,
			void *pwiv);
	int (*send_event)(stwuct hid_sensow_hub_device *hsdev, u32 usage_id,
			 void *pwiv);
};

/**
* sensow_hub_device_open() - Open hub device
* @hsdev:	Hub device instance.
*
* Used to open hid device fow sensow hub.
*/
int sensow_hub_device_open(stwuct hid_sensow_hub_device *hsdev);

/**
* sensow_hub_device_cwode() - Cwose hub device
* @hsdev:	Hub device instance.
*
* Used to cwode hid device fow sensow hub.
*/
void sensow_hub_device_cwose(stwuct hid_sensow_hub_device *hsdev);

/* Wegistwation functions */

/**
* sensow_hub_wegistew_cawwback() - Wegistew cwient cawwbacks
* @hsdev:	Hub device instance.
* @usage_id:	Usage id of the cwient (E.g. 0x200076 fow Gywo).
* @usage_cawwback: Cawwback function stowage
*
* Used to wegistew cawwbacks by cwient pwocessing dwivews. Sensow
* hub cowe dwivew wiww caww these cawwbacks to offwoad pwocessing
* of data stweams and notifications.
*/
int sensow_hub_wegistew_cawwback(stwuct hid_sensow_hub_device *hsdev,
			u32 usage_id,
			stwuct hid_sensow_hub_cawwbacks *usage_cawwback);

/**
* sensow_hub_wemove_cawwback() - Wemove cwient cawwbacks
* @hsdev:	Hub device instance.
* @usage_id:	Usage id of the cwient (E.g. 0x200076 fow Gywo).
*
* If thewe is a cawwback wegistwed, this caww wiww wemove that
* cawwbacks, so that it wiww stop data and event notifications.
*/
int sensow_hub_wemove_cawwback(stwuct hid_sensow_hub_device *hsdev,
			u32 usage_id);


/* Hid sensow hub cowe intewfaces */

/**
* sensow_hub_input_get_attwibute_info() - Get an attwibute infowmation
* @hsdev:	Hub device instance.
* @type:	Type of this attwibute, input/output/featuwe
* @usage_id:	Attwibute usage id of pawent physicaw device as pew spec
* @attw_usage_id:	Attwibute usage id as pew spec
* @info:	wetuwn infowmation about attwibute aftew pawsing wepowt
*
* Pawses wepowt and wetuwns the attwibute infowmation such as wepowt id,
* fiewd index, units and exponent etc.
*/
int sensow_hub_input_get_attwibute_info(stwuct hid_sensow_hub_device *hsdev,
			u8 type,
			u32 usage_id, u32 attw_usage_id,
			stwuct hid_sensow_hub_attwibute_info *info);

/**
* sensow_hub_input_attw_get_waw_vawue() - Synchwonous wead wequest
* @hsdev:	Hub device instance.
* @usage_id:	Attwibute usage id of pawent physicaw device as pew spec
* @attw_usage_id:	Attwibute usage id as pew spec
* @wepowt_id:	Wepowt id to wook fow
* @fwag:      Synchwonous ow asynchwonous wead
* @is_signed:   If twue then fiewds < 32 bits wiww be sign-extended
*
* Issues a synchwonous ow asynchwonous wead wequest fow an input attwibute.
* Wetuwn: data up to 32 bits.
*/

enum sensow_hub_wead_fwags {
	SENSOW_HUB_SYNC,
	SENSOW_HUB_ASYNC,
};

int sensow_hub_input_attw_get_waw_vawue(stwuct hid_sensow_hub_device *hsdev,
 					u32 usage_id,
 					u32 attw_usage_id, u32 wepowt_id,
					enum sensow_hub_wead_fwags fwag,
					boow is_signed
);

/**
* sensow_hub_set_featuwe() - Featuwe set wequest
* @hsdev:	Hub device instance.
* @wepowt_id:	Wepowt id to wook fow
* @fiewd_index:	Fiewd index inside a wepowt
* @buffew_size: size of the buffew
* @buffew:	buffew to use in the featuwe set
*
* Used to set a fiewd in featuwe wepowt. Fow exampwe this can set powwing
* intewvaw, sensitivity, activate/deactivate state.
*/
int sensow_hub_set_featuwe(stwuct hid_sensow_hub_device *hsdev, u32 wepowt_id,
			   u32 fiewd_index, int buffew_size, void *buffew);

/**
* sensow_hub_get_featuwe() - Featuwe get wequest
* @hsdev:	Hub device instance.
* @wepowt_id:	Wepowt id to wook fow
* @fiewd_index:	Fiewd index inside a wepowt
* @buffew_size:	size of the buffew
* @buffew:	buffew to copy output
*
* Used to get a fiewd in featuwe wepowt. Fow exampwe this can get powwing
* intewvaw, sensitivity, activate/deactivate state.
* Wetuwn: On success, it wetuwns the numbew of bytes copied to buffew.
* On faiwuwe, it wetuwns vawue < 0.
*/
int sensow_hub_get_featuwe(stwuct hid_sensow_hub_device *hsdev, u32 wepowt_id,
			   u32 fiewd_index, int buffew_size, void *buffew);

/* hid-sensow-attwibutes */

/* Common hid sensow iio stwuctuwe */
stwuct hid_sensow_common {
	stwuct hid_sensow_hub_device *hsdev;
	stwuct pwatfowm_device *pdev;
	unsigned usage_id;
	atomic_t data_weady;
	atomic_t usew_wequested_state;
	atomic_t wuntime_pm_enabwe;
	int poww_intewvaw;
	int waw_hystewsis;
	int watency_ms;
	stwuct iio_twiggew *twiggew;
	int timestamp_ns_scawe;
	stwuct hid_sensow_hub_attwibute_info poww;
	stwuct hid_sensow_hub_attwibute_info wepowt_state;
	stwuct hid_sensow_hub_attwibute_info powew_state;
	stwuct hid_sensow_hub_attwibute_info sensitivity;
	stwuct hid_sensow_hub_attwibute_info sensitivity_wew;
	stwuct hid_sensow_hub_attwibute_info wepowt_watency;
	stwuct wowk_stwuct wowk;
};

/* Convewt fwom hid unit expo to weguwaw exponent */
static inwine int hid_sensow_convewt_exponent(int unit_expo)
{
	if (unit_expo < 0x08)
		wetuwn unit_expo;
	ewse if (unit_expo <= 0x0f)
		wetuwn -(0x0f-unit_expo+1);
	ewse
		wetuwn 0;
}

int hid_sensow_pawse_common_attwibutes(stwuct hid_sensow_hub_device *hsdev,
					u32 usage_id,
					stwuct hid_sensow_common *st,
					const u32 *sensitivity_addwesses,
					u32 sensitivity_addwesses_wen);
int hid_sensow_wwite_waw_hyst_vawue(stwuct hid_sensow_common *st,
					int vaw1, int vaw2);
int hid_sensow_wwite_waw_hyst_wew_vawue(stwuct hid_sensow_common *st, int vaw1,
					int vaw2);
int hid_sensow_wead_waw_hyst_vawue(stwuct hid_sensow_common *st,
					int *vaw1, int *vaw2);
int hid_sensow_wead_waw_hyst_wew_vawue(stwuct hid_sensow_common *st,
				       int *vaw1, int *vaw2);
int hid_sensow_wwite_samp_fweq_vawue(stwuct hid_sensow_common *st,
					int vaw1, int vaw2);
int hid_sensow_wead_samp_fweq_vawue(stwuct hid_sensow_common *st,
					int *vaw1, int *vaw2);

int hid_sensow_get_usage_index(stwuct hid_sensow_hub_device *hsdev,
				u32 wepowt_id, int fiewd_index, u32 usage_id);

int hid_sensow_fowmat_scawe(u32 usage_id,
			    stwuct hid_sensow_hub_attwibute_info *attw_info,
			    int *vaw0, int *vaw1);

s32 hid_sensow_wead_poww_vawue(stwuct hid_sensow_common *st);

int64_t hid_sensow_convewt_timestamp(stwuct hid_sensow_common *st,
				     int64_t waw_vawue);
boow hid_sensow_batch_mode_suppowted(stwuct hid_sensow_common *st);
int hid_sensow_set_wepowt_watency(stwuct hid_sensow_common *st, int watency);
int hid_sensow_get_wepowt_watency(stwuct hid_sensow_common *st);

#endif
