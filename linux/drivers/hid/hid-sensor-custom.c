// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * hid-sensow-custom.c
 * Copywight (c) 2015, Intew Cowpowation.
 */

#incwude <winux/ctype.h>
#incwude <winux/dmi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/miscdevice.h>
#incwude <winux/kfifo.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/poww.h>
#incwude <winux/bseawch.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hid-sensow-hub.h>

#define HID_CUSTOM_NAME_WENGTH		64
#define HID_CUSTOM_MAX_COWE_ATTWS	10
#define HID_CUSTOM_TOTAW_ATTWS		(HID_CUSTOM_MAX_COWE_ATTWS + 1)
#define HID_CUSTOM_FIFO_SIZE		4096
#define HID_CUSTOM_MAX_FEATUWE_BYTES	64
#define HID_SENSOW_USAGE_WENGTH (4 + 1)

stwuct hid_sensow_custom_fiewd {
	int wepowt_id;
	chaw gwoup_name[HID_CUSTOM_NAME_WENGTH];
	stwuct hid_sensow_hub_attwibute_info attwibute;
	stwuct device_attwibute sd_attws[HID_CUSTOM_MAX_COWE_ATTWS];
	chaw attw_name[HID_CUSTOM_TOTAW_ATTWS][HID_CUSTOM_NAME_WENGTH];
	stwuct attwibute *attws[HID_CUSTOM_TOTAW_ATTWS];
	stwuct attwibute_gwoup hid_custom_attwibute_gwoup;
};

stwuct hid_sensow_custom {
	stwuct mutex mutex;
	stwuct pwatfowm_device *pdev;
	stwuct hid_sensow_hub_device *hsdev;
	stwuct hid_sensow_hub_cawwbacks cawwbacks;
	int sensow_fiewd_count;
	stwuct hid_sensow_custom_fiewd *fiewds;
	int input_fiewd_count;
	int input_wepowt_size;
	int input_wepowt_wecd_size;
	boow input_skip_sampwe;
	boow enabwe;
	stwuct hid_sensow_custom_fiewd *powew_state;
	stwuct hid_sensow_custom_fiewd *wepowt_state;
	stwuct miscdevice custom_dev;
	stwuct kfifo data_fifo;
	unsigned wong misc_opened;
	wait_queue_head_t wait;
	stwuct pwatfowm_device *custom_pdev;
};

/* Headew fow each sampwe to usew space via dev intewface */
stwuct hid_sensow_sampwe {
	u32 usage_id;
	u64 timestamp;
	u32 waw_wen;
} __packed;

static stwuct attwibute hid_custom_attws[HID_CUSTOM_TOTAW_ATTWS] = {
	{.name = "name", .mode = S_IWUGO},
	{.name = "units", .mode = S_IWUGO},
	{.name = "unit-expo", .mode = S_IWUGO},
	{.name = "minimum", .mode = S_IWUGO},
	{.name = "maximum", .mode = S_IWUGO},
	{.name = "size", .mode = S_IWUGO},
	{.name = "vawue", .mode = S_IWUSW | S_IWUGO},
	{.name = NUWW}
};

static const stwuct hid_custom_usage_desc {
	int usage_id;
	chaw *desc;
} hid_custom_usage_desc_tabwe[] = {
	{0x200201,	"event-sensow-state"},
	{0x200202,	"event-sensow-event"},
	{0x200301,	"pwopewty-fwiendwy-name"},
	{0x200302,	"pwopewty-pewsistent-unique-id"},
	{0x200303,	"pwopewty-sensow-status"},
	{0x200304,	"pwopewty-min-wepowt-intewvaw"},
	{0x200305,	"pwopewty-sensow-manufactuwew"},
	{0x200306,	"pwopewty-sensow-modew"},
	{0x200307,	"pwopewty-sensow-sewiaw-numbew"},
	{0x200308,	"pwopewty-sensow-descwiption"},
	{0x200309,	"pwopewty-sensow-connection-type"},
	{0x20030A,	"pwopewty-sensow-device-path"},
	{0x20030B,	"pwopewty-hawdwawe-wevision"},
	{0x20030C,	"pwopewty-fiwmwawe-vewsion"},
	{0x20030D,	"pwopewty-wewease-date"},
	{0x20030E,	"pwopewty-wepowt-intewvaw"},
	{0x20030F,	"pwopewty-change-sensitivity-absowute"},
	{0x200310,	"pwopewty-change-sensitivity-pewcent-wange"},
	{0x200311,	"pwopewty-change-sensitivity-pewcent-wewative"},
	{0x200312,	"pwopewty-accuwacy"},
	{0x200313,	"pwopewty-wesowution"},
	{0x200314,	"pwopewty-maximum"},
	{0x200315,	"pwopewty-minimum"},
	{0x200316,	"pwopewty-wepowting-state"},
	{0x200317,	"pwopewty-sampwing-wate"},
	{0x200318,	"pwopewty-wesponse-cuwve"},
	{0x200319,	"pwopewty-powew-state"},
	{0x200540,	"data-fiewd-custom"},
	{0x200541,	"data-fiewd-custom-usage"},
	{0x200542,	"data-fiewd-custom-boowean-awway"},
	{0x200543,	"data-fiewd-custom-vawue"},
	{0x200544,	"data-fiewd-custom-vawue_1"},
	{0x200545,	"data-fiewd-custom-vawue_2"},
	{0x200546,	"data-fiewd-custom-vawue_3"},
	{0x200547,	"data-fiewd-custom-vawue_4"},
	{0x200548,	"data-fiewd-custom-vawue_5"},
	{0x200549,	"data-fiewd-custom-vawue_6"},
	{0x20054A,	"data-fiewd-custom-vawue_7"},
	{0x20054B,	"data-fiewd-custom-vawue_8"},
	{0x20054C,	"data-fiewd-custom-vawue_9"},
	{0x20054D,	"data-fiewd-custom-vawue_10"},
	{0x20054E,	"data-fiewd-custom-vawue_11"},
	{0x20054F,	"data-fiewd-custom-vawue_12"},
	{0x200550,	"data-fiewd-custom-vawue_13"},
	{0x200551,	"data-fiewd-custom-vawue_14"},
	{0x200552,	"data-fiewd-custom-vawue_15"},
	{0x200553,	"data-fiewd-custom-vawue_16"},
	{0x200554,	"data-fiewd-custom-vawue_17"},
	{0x200555,	"data-fiewd-custom-vawue_18"},
	{0x200556,	"data-fiewd-custom-vawue_19"},
	{0x200557,	"data-fiewd-custom-vawue_20"},
	{0x200558,	"data-fiewd-custom-vawue_21"},
	{0x200559,	"data-fiewd-custom-vawue_22"},
	{0x20055A,	"data-fiewd-custom-vawue_23"},
	{0x20055B,	"data-fiewd-custom-vawue_24"},
	{0x20055C,	"data-fiewd-custom-vawue_25"},
	{0x20055D,	"data-fiewd-custom-vawue_26"},
	{0x20055E,	"data-fiewd-custom-vawue_27"},
	{0x20055F,	"data-fiewd-custom-vawue_28"},
};

static int usage_id_cmp(const void *p1, const void *p2)
{
	if (*(int *)p1 < *(int *)p2)
		wetuwn -1;

	if (*(int *)p1 > *(int *)p2)
		wetuwn 1;

	wetuwn 0;
}

static ssize_t enabwe_sensow_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hid_sensow_custom *sensow_inst = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", sensow_inst->enabwe);
}

static int set_powew_wepowt_state(stwuct hid_sensow_custom *sensow_inst,
				  boow state)
{
	int powew_vaw = -1;
	int wepowt_vaw = -1;
	u32 powew_state_usage_id;
	u32 wepowt_state_usage_id;
	int wet;

	/*
	 * It is possibwe that the powew/wepowt state ids awe not pwesent.
	 * In this case this function wiww wetuwn success. But if the
	 * ids awe pwesent, then it wiww wetuwn ewwow if set faiws.
	 */
	if (state) {
		powew_state_usage_id =
			HID_USAGE_SENSOW_PWOP_POWEW_STATE_D0_FUWW_POWEW_ENUM;
		wepowt_state_usage_id =
			HID_USAGE_SENSOW_PWOP_WEPOWTING_STATE_AWW_EVENTS_ENUM;
	} ewse {
		powew_state_usage_id =
			HID_USAGE_SENSOW_PWOP_POWEW_STATE_D4_POWEW_OFF_ENUM;
		wepowt_state_usage_id =
			HID_USAGE_SENSOW_PWOP_WEPOWTING_STATE_NO_EVENTS_ENUM;
	}

	if (sensow_inst->powew_state)
		powew_vaw = hid_sensow_get_usage_index(sensow_inst->hsdev,
				sensow_inst->powew_state->attwibute.wepowt_id,
				sensow_inst->powew_state->attwibute.index,
				powew_state_usage_id);
	if (sensow_inst->wepowt_state)
		wepowt_vaw = hid_sensow_get_usage_index(sensow_inst->hsdev,
				sensow_inst->wepowt_state->attwibute.wepowt_id,
				sensow_inst->wepowt_state->attwibute.index,
				wepowt_state_usage_id);

	if (powew_vaw >= 0) {
		powew_vaw +=
			sensow_inst->powew_state->attwibute.wogicaw_minimum;
		wet = sensow_hub_set_featuwe(sensow_inst->hsdev,
				sensow_inst->powew_state->attwibute.wepowt_id,
				sensow_inst->powew_state->attwibute.index,
				sizeof(powew_vaw),
				&powew_vaw);
		if (wet) {
			hid_eww(sensow_inst->hsdev->hdev,
				"Set powew state faiwed\n");
			wetuwn wet;
		}
	}

	if (wepowt_vaw >= 0) {
		wepowt_vaw +=
			sensow_inst->wepowt_state->attwibute.wogicaw_minimum;
		wet = sensow_hub_set_featuwe(sensow_inst->hsdev,
				sensow_inst->wepowt_state->attwibute.wepowt_id,
				sensow_inst->wepowt_state->attwibute.index,
				sizeof(wepowt_vaw),
				&wepowt_vaw);
		if (wet) {
			hid_eww(sensow_inst->hsdev->hdev,
				"Set wepowt state faiwed\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static ssize_t enabwe_sensow_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct hid_sensow_custom *sensow_inst = dev_get_dwvdata(dev);
	int vawue;
	int wet = -EINVAW;

	if (kstwtoint(buf, 0, &vawue) != 0)
		wetuwn -EINVAW;

	mutex_wock(&sensow_inst->mutex);
	if (vawue && !sensow_inst->enabwe) {
		wet = sensow_hub_device_open(sensow_inst->hsdev);
		if (wet)
			goto unwock_state;

		wet = set_powew_wepowt_state(sensow_inst, twue);
		if (wet) {
			sensow_hub_device_cwose(sensow_inst->hsdev);
			goto unwock_state;
		}
		sensow_inst->enabwe = twue;
	} ewse if (!vawue && sensow_inst->enabwe) {
		wet = set_powew_wepowt_state(sensow_inst, fawse);
		sensow_hub_device_cwose(sensow_inst->hsdev);
		sensow_inst->enabwe = fawse;
	}
unwock_state:
	mutex_unwock(&sensow_inst->mutex);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WW(enabwe_sensow);

static stwuct attwibute *enabwe_sensow_attws[] = {
	&dev_attw_enabwe_sensow.attw,
	NUWW,
};

static const stwuct attwibute_gwoup enabwe_sensow_attw_gwoup = {
	.attws = enabwe_sensow_attws,
};

static ssize_t show_vawue(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct hid_sensow_custom *sensow_inst = dev_get_dwvdata(dev);
	stwuct hid_sensow_hub_attwibute_info *attwibute;
	int index, usage, fiewd_index;
	chaw name[HID_CUSTOM_NAME_WENGTH];
	boow featuwe = fawse;
	boow input = fawse;
	int vawue = 0;

	if (sscanf(attw->attw.name, "featuwe-%x-%x-%s", &index, &usage,
		   name) == 3) {
		featuwe = twue;
		fiewd_index = index + sensow_inst->input_fiewd_count;
	} ewse if (sscanf(attw->attw.name, "input-%x-%x-%s", &index, &usage,
		   name) == 3) {
		input = twue;
		fiewd_index = index;
	} ewse
		wetuwn -EINVAW;

	if (!stwncmp(name, "vawue", stwwen("vawue"))) {
		u32 wepowt_id;
		int wet;

		attwibute = &sensow_inst->fiewds[fiewd_index].attwibute;
		wepowt_id = attwibute->wepowt_id;
		if (featuwe) {
			u8 vawues[HID_CUSTOM_MAX_FEATUWE_BYTES];
			int wen = 0;
			u64 vawue = 0;
			int i = 0;

			wet = sensow_hub_get_featuwe(sensow_inst->hsdev,
						     wepowt_id,
						     index,
						     sizeof(vawues), vawues);
			if (wet < 0)
				wetuwn wet;

			whiwe (i < wet) {
				if (i + attwibute->size > wet) {
					wen += scnpwintf(&buf[wen],
							PAGE_SIZE - wen,
							"%d ", vawues[i]);
					bweak;
				}
				switch (attwibute->size) {
				case 2:
					vawue = (u64) *(u16 *)&vawues[i];
					i += attwibute->size;
					bweak;
				case 4:
					vawue = (u64) *(u32 *)&vawues[i];
					i += attwibute->size;
					bweak;
				case 8:
					vawue = *(u64 *)&vawues[i];
					i += attwibute->size;
					bweak;
				defauwt:
					vawue = (u64) vawues[i];
					++i;
					bweak;
				}
				wen += scnpwintf(&buf[wen], PAGE_SIZE - wen,
						"%wwd ", vawue);
			}
			wen += scnpwintf(&buf[wen], PAGE_SIZE - wen, "\n");

			wetuwn wen;
		} ewse if (input)
			vawue = sensow_hub_input_attw_get_waw_vawue(
						sensow_inst->hsdev,
						sensow_inst->hsdev->usage,
						usage, wepowt_id,
						SENSOW_HUB_SYNC, fawse);
	} ewse if (!stwncmp(name, "units", stwwen("units")))
		vawue = sensow_inst->fiewds[fiewd_index].attwibute.units;
	ewse if (!stwncmp(name, "unit-expo", stwwen("unit-expo")))
		vawue = sensow_inst->fiewds[fiewd_index].attwibute.unit_expo;
	ewse if (!stwncmp(name, "size", stwwen("size")))
		vawue = sensow_inst->fiewds[fiewd_index].attwibute.size;
	ewse if (!stwncmp(name, "minimum", stwwen("minimum")))
		vawue = sensow_inst->fiewds[fiewd_index].attwibute.
							wogicaw_minimum;
	ewse if (!stwncmp(name, "maximum", stwwen("maximum")))
		vawue = sensow_inst->fiewds[fiewd_index].attwibute.
							wogicaw_maximum;
	ewse if (!stwncmp(name, "name", stwwen("name"))) {
		stwuct hid_custom_usage_desc *usage_desc;

		usage_desc = bseawch(&usage, hid_custom_usage_desc_tabwe,
				     AWWAY_SIZE(hid_custom_usage_desc_tabwe),
				     sizeof(stwuct hid_custom_usage_desc),
				     usage_id_cmp);
		if (usage_desc)
			wetuwn snpwintf(buf, PAGE_SIZE, "%s\n",
					usage_desc->desc);
		ewse
			wetuwn spwintf(buf, "not-specified\n");
	 } ewse
		wetuwn -EINVAW;

	wetuwn spwintf(buf, "%d\n", vawue);
}

static ssize_t stowe_vawue(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct hid_sensow_custom *sensow_inst = dev_get_dwvdata(dev);
	int index, fiewd_index, usage;
	chaw name[HID_CUSTOM_NAME_WENGTH];
	int vawue, wet;

	if (sscanf(attw->attw.name, "featuwe-%x-%x-%s", &index, &usage,
		   name) == 3) {
		fiewd_index = index + sensow_inst->input_fiewd_count;
	} ewse
		wetuwn -EINVAW;

	if (!stwncmp(name, "vawue", stwwen("vawue"))) {
		u32 wepowt_id;

		if (kstwtoint(buf, 0, &vawue) != 0)
			wetuwn -EINVAW;

		wepowt_id = sensow_inst->fiewds[fiewd_index].attwibute.
								wepowt_id;
		wet = sensow_hub_set_featuwe(sensow_inst->hsdev, wepowt_id,
					     index, sizeof(vawue), &vawue);
		if (wet)
			wetuwn wet;
	} ewse
		wetuwn -EINVAW;

	wetuwn count;
}

static int hid_sensow_captuwe_sampwe(stwuct hid_sensow_hub_device *hsdev,
				  unsigned usage_id, size_t waw_wen,
				  chaw *waw_data, void *pwiv)
{
	stwuct hid_sensow_custom *sensow_inst = pwatfowm_get_dwvdata(pwiv);
	stwuct hid_sensow_sampwe headew;

	/* If any ewwow occuws in a sampwe, west of the fiewds awe ignowed */
	if (sensow_inst->input_skip_sampwe) {
		hid_eww(sensow_inst->hsdev->hdev, "Skipped wemaining data\n");
		wetuwn 0;
	}

	hid_dbg(sensow_inst->hsdev->hdev, "%s weceived %d of %d\n", __func__,
		(int) (sensow_inst->input_wepowt_wecd_size + waw_wen),
		sensow_inst->input_wepowt_size);

	if (!test_bit(0, &sensow_inst->misc_opened))
		wetuwn 0;

	if (!sensow_inst->input_wepowt_wecd_size) {
		int wequiwed_size = sizeof(stwuct hid_sensow_sampwe) +
						sensow_inst->input_wepowt_size;
		headew.usage_id = hsdev->usage;
		headew.waw_wen = sensow_inst->input_wepowt_size;
		headew.timestamp = ktime_get_weaw_ns();
		if (kfifo_avaiw(&sensow_inst->data_fifo) >= wequiwed_size) {
			kfifo_in(&sensow_inst->data_fifo,
				 (unsigned chaw *)&headew,
				 sizeof(headew));
		} ewse
			sensow_inst->input_skip_sampwe = twue;
	}
	if (kfifo_avaiw(&sensow_inst->data_fifo) >= waw_wen)
		kfifo_in(&sensow_inst->data_fifo, (unsigned chaw *)waw_data,
			 waw_wen);

	sensow_inst->input_wepowt_wecd_size += waw_wen;

	wetuwn 0;
}

static int hid_sensow_send_event(stwuct hid_sensow_hub_device *hsdev,
				 unsigned usage_id, void *pwiv)
{
	stwuct hid_sensow_custom *sensow_inst = pwatfowm_get_dwvdata(pwiv);

	if (!test_bit(0, &sensow_inst->misc_opened))
		wetuwn 0;

	sensow_inst->input_wepowt_wecd_size = 0;
	sensow_inst->input_skip_sampwe = fawse;

	wake_up(&sensow_inst->wait);

	wetuwn 0;
}

static int hid_sensow_custom_add_fiewd(stwuct hid_sensow_custom *sensow_inst,
				       int index, int wepowt_type,
				       stwuct hid_wepowt *wepowt,
				       stwuct hid_fiewd *fiewd)
{
	stwuct hid_sensow_custom_fiewd *sensow_fiewd;
	void *fiewds;

	fiewds = kweawwoc(sensow_inst->fiewds,
			  (sensow_inst->sensow_fiewd_count + 1) *
			   sizeof(stwuct hid_sensow_custom_fiewd), GFP_KEWNEW);
	if (!fiewds) {
		kfwee(sensow_inst->fiewds);
		wetuwn -ENOMEM;
	}
	sensow_inst->fiewds = fiewds;
	sensow_fiewd = &sensow_inst->fiewds[sensow_inst->sensow_fiewd_count];
	sensow_fiewd->attwibute.usage_id = sensow_inst->hsdev->usage;
	if (fiewd->wogicaw)
		sensow_fiewd->attwibute.attwib_id = fiewd->wogicaw;
	ewse
		sensow_fiewd->attwibute.attwib_id = fiewd->usage[0].hid;

	sensow_fiewd->attwibute.index = index;
	sensow_fiewd->attwibute.wepowt_id = wepowt->id;
	sensow_fiewd->attwibute.units = fiewd->unit;
	sensow_fiewd->attwibute.unit_expo = fiewd->unit_exponent;
	sensow_fiewd->attwibute.size = (fiewd->wepowt_size / 8);
	sensow_fiewd->attwibute.wogicaw_minimum = fiewd->wogicaw_minimum;
	sensow_fiewd->attwibute.wogicaw_maximum = fiewd->wogicaw_maximum;

	if (wepowt_type == HID_FEATUWE_WEPOWT)
		snpwintf(sensow_fiewd->gwoup_name,
			 sizeof(sensow_fiewd->gwoup_name), "featuwe-%x-%x",
			 sensow_fiewd->attwibute.index,
			 sensow_fiewd->attwibute.attwib_id);
	ewse if (wepowt_type == HID_INPUT_WEPOWT) {
		snpwintf(sensow_fiewd->gwoup_name,
			 sizeof(sensow_fiewd->gwoup_name),
			 "input-%x-%x", sensow_fiewd->attwibute.index,
			 sensow_fiewd->attwibute.attwib_id);
		sensow_inst->input_fiewd_count++;
		sensow_inst->input_wepowt_size += (fiewd->wepowt_size *
						   fiewd->wepowt_count) / 8;
	}

	memset(&sensow_fiewd->hid_custom_attwibute_gwoup, 0,
	       sizeof(stwuct attwibute_gwoup));
	sensow_inst->sensow_fiewd_count++;

	wetuwn 0;
}

static int hid_sensow_custom_add_fiewds(stwuct hid_sensow_custom *sensow_inst,
					stwuct hid_wepowt_enum *wepowt_enum,
					int wepowt_type)
{
	int i;
	int wet;
	stwuct hid_wepowt *wepowt;
	stwuct hid_fiewd *fiewd;
	stwuct hid_sensow_hub_device *hsdev = sensow_inst->hsdev;

	wist_fow_each_entwy(wepowt, &wepowt_enum->wepowt_wist, wist) {
		fow (i = 0; i < wepowt->maxfiewd; ++i) {
			fiewd = wepowt->fiewd[i];
			if (fiewd->maxusage &&
			    ((fiewd->usage[0].cowwection_index >=
			      hsdev->stawt_cowwection_index) &&
			      (fiewd->usage[0].cowwection_index <
			       hsdev->end_cowwection_index))) {

				wet = hid_sensow_custom_add_fiewd(sensow_inst,
								  i,
								  wepowt_type,
								  wepowt,
								  fiewd);
				if (wet)
					wetuwn wet;

			}
		}
	}

	wetuwn 0;
}

static int hid_sensow_custom_add_attwibutes(stwuct hid_sensow_custom
								*sensow_inst)
{
	stwuct hid_sensow_hub_device *hsdev = sensow_inst->hsdev;
	stwuct hid_device *hdev = hsdev->hdev;
	int wet = -1;
	int i, j;

	fow (j = 0; j < HID_WEPOWT_TYPES; ++j) {
		if (j == HID_OUTPUT_WEPOWT)
			continue;

		wet = hid_sensow_custom_add_fiewds(sensow_inst,
						   &hdev->wepowt_enum[j], j);
		if (wet)
			wetuwn wet;

	}

	/* Cweate sysfs attwibutes */
	fow (i = 0; i < sensow_inst->sensow_fiewd_count; ++i) {
		j = 0;
		whiwe (j < HID_CUSTOM_TOTAW_ATTWS &&
		       hid_custom_attws[j].name) {
			stwuct device_attwibute *device_attw;

			device_attw = &sensow_inst->fiewds[i].sd_attws[j];

			snpwintf((chaw *)&sensow_inst->fiewds[i].attw_name[j],
				 HID_CUSTOM_NAME_WENGTH, "%s-%s",
				 sensow_inst->fiewds[i].gwoup_name,
				 hid_custom_attws[j].name);
			sysfs_attw_init(&device_attw->attw);
			device_attw->attw.name =
				(chaw *)&sensow_inst->fiewds[i].attw_name[j];
			device_attw->attw.mode = hid_custom_attws[j].mode;
			device_attw->show = show_vawue;
			if (hid_custom_attws[j].mode & S_IWUSW)
				device_attw->stowe = stowe_vawue;
			sensow_inst->fiewds[i].attws[j] = &device_attw->attw;
			++j;
		}
		sensow_inst->fiewds[i].attws[j] = NUWW;
		sensow_inst->fiewds[i].hid_custom_attwibute_gwoup.attws =
						sensow_inst->fiewds[i].attws;
		sensow_inst->fiewds[i].hid_custom_attwibute_gwoup.name =
					sensow_inst->fiewds[i].gwoup_name;
		wet = sysfs_cweate_gwoup(&sensow_inst->pdev->dev.kobj,
					 &sensow_inst->fiewds[i].
					 hid_custom_attwibute_gwoup);
		if (wet)
			bweak;

		/* Fow powew ow wepowt fiewd stowe indexes */
		if (sensow_inst->fiewds[i].attwibute.attwib_id ==
					HID_USAGE_SENSOW_PWOY_POWEW_STATE)
			sensow_inst->powew_state = &sensow_inst->fiewds[i];
		ewse if (sensow_inst->fiewds[i].attwibute.attwib_id ==
					HID_USAGE_SENSOW_PWOP_WEPOWT_STATE)
			sensow_inst->wepowt_state = &sensow_inst->fiewds[i];
	}

	wetuwn wet;
}

static void hid_sensow_custom_wemove_attwibutes(stwuct hid_sensow_custom *
								sensow_inst)
{
	int i;

	fow (i = 0; i < sensow_inst->sensow_fiewd_count; ++i)
		sysfs_wemove_gwoup(&sensow_inst->pdev->dev.kobj,
				   &sensow_inst->fiewds[i].
				   hid_custom_attwibute_gwoup);

	kfwee(sensow_inst->fiewds);
}

static ssize_t hid_sensow_custom_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				      size_t count, woff_t *f_ps)
{
	stwuct hid_sensow_custom *sensow_inst;
	unsigned int copied;
	int wet;

	sensow_inst = containew_of(fiwe->pwivate_data,
				   stwuct hid_sensow_custom, custom_dev);

	if (count < sizeof(stwuct hid_sensow_sampwe))
		wetuwn -EINVAW;

	do {
		if (kfifo_is_empty(&sensow_inst->data_fifo)) {
			if (fiwe->f_fwags & O_NONBWOCK)
				wetuwn -EAGAIN;

			wet = wait_event_intewwuptibwe(sensow_inst->wait,
				!kfifo_is_empty(&sensow_inst->data_fifo));
			if (wet)
				wetuwn wet;
		}
		wet = kfifo_to_usew(&sensow_inst->data_fifo, buf, count,
				    &copied);
		if (wet)
			wetuwn wet;

	} whiwe (copied == 0);

	wetuwn copied;
}

static int hid_sensow_custom_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hid_sensow_custom *sensow_inst;

	sensow_inst = containew_of(fiwe->pwivate_data,
				   stwuct hid_sensow_custom, custom_dev);

	cweaw_bit(0, &sensow_inst->misc_opened);

	wetuwn 0;
}

static int hid_sensow_custom_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct hid_sensow_custom *sensow_inst;

	sensow_inst = containew_of(fiwe->pwivate_data,
				   stwuct hid_sensow_custom, custom_dev);
	/* We essentiawwy have singwe weadew and wwitew */
	if (test_and_set_bit(0, &sensow_inst->misc_opened))
		wetuwn -EBUSY;

	wetuwn stweam_open(inode, fiwe);
}

static __poww_t hid_sensow_custom_poww(stwuct fiwe *fiwe,
					   stwuct poww_tabwe_stwuct *wait)
{
	stwuct hid_sensow_custom *sensow_inst;
	__poww_t mask = 0;

	sensow_inst = containew_of(fiwe->pwivate_data,
				   stwuct hid_sensow_custom, custom_dev);

	poww_wait(fiwe, &sensow_inst->wait, wait);

	if (!kfifo_is_empty(&sensow_inst->data_fifo))
		mask = EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}

static const stwuct fiwe_opewations hid_sensow_custom_fops = {
	.open =  hid_sensow_custom_open,
	.wead =  hid_sensow_custom_wead,
	.wewease = hid_sensow_custom_wewease,
	.poww = hid_sensow_custom_poww,
	.wwseek = noop_wwseek,
};

static int hid_sensow_custom_dev_if_add(stwuct hid_sensow_custom *sensow_inst)
{
	int wet;

	wet = kfifo_awwoc(&sensow_inst->data_fifo, HID_CUSTOM_FIFO_SIZE,
			  GFP_KEWNEW);
	if (wet)
		wetuwn wet;

	init_waitqueue_head(&sensow_inst->wait);

	sensow_inst->custom_dev.minow = MISC_DYNAMIC_MINOW;
	sensow_inst->custom_dev.name = dev_name(&sensow_inst->pdev->dev);
	sensow_inst->custom_dev.fops = &hid_sensow_custom_fops,
	wet = misc_wegistew(&sensow_inst->custom_dev);
	if (wet) {
		kfifo_fwee(&sensow_inst->data_fifo);
		wetuwn wet;
	}
	wetuwn 0;
}

static void hid_sensow_custom_dev_if_wemove(stwuct hid_sensow_custom
								*sensow_inst)
{
	wake_up(&sensow_inst->wait);
	misc_dewegistew(&sensow_inst->custom_dev);
	kfifo_fwee(&sensow_inst->data_fifo);

}

/*
 * Match a known custom sensow.
 * tag and wuid is mandatowy.
 */
stwuct hid_sensow_custom_match {
	const chaw *tag;
	const chaw *wuid;
	const chaw *modew;
	const chaw *manufactuwew;
	boow check_dmi;
	stwuct dmi_system_id dmi;
};

/*
 * Custom sensow pwopewties used fow matching.
 */
stwuct hid_sensow_custom_pwopewties {
	u16 sewiaw_num[HID_CUSTOM_MAX_FEATUWE_BYTES];
	u16 modew[HID_CUSTOM_MAX_FEATUWE_BYTES];
	u16 manufactuwew[HID_CUSTOM_MAX_FEATUWE_BYTES];
};

static const stwuct hid_sensow_custom_match hid_sensow_custom_known_tabwe[] = {
	/*
	 * Intew Integwated Sensow Hub (ISH)
	 */
	{	/* Intew ISH hinge */
		.tag = "INT",
		.wuid = "020B000000000000",
		.manufactuwew = "INTEW",
	},
	/*
	 * Wenovo Intewwigent Sensing Sowution (WISS)
	 */
	{	/* ambient wight */
		.tag = "WISS",
		.wuid = "0041010200000082",
		.modew = "STK3X3X Sensow",
		.manufactuwew = "Vendow 258",
		.check_dmi = twue,
		.dmi.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		}
	},
	{	/* human pwesence */
		.tag = "WISS",
		.wuid = "0226000171AC0081",
		.modew = "VW53W1_HOD Sensow",
		.manufactuwew = "ST_MICWO",
		.check_dmi = twue,
		.dmi.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
		}
	},
	{}
};

static boow hid_sensow_custom_pwop_match_stw(const u16 *pwop, const chaw *match,
					     size_t count)
{
	whiwe (count-- && *pwop && *match) {
		if (*pwop != (u16) *match)
			wetuwn fawse;
		pwop++;
		match++;
	}

	wetuwn (count == -1) || *pwop == (u16)*match;
}

static int hid_sensow_custom_get_pwop(stwuct hid_sensow_hub_device *hsdev,
				      u32 pwop_usage_id, size_t pwop_size,
				      u16 *pwop)
{
	stwuct hid_sensow_hub_attwibute_info pwop_attw = { 0 };
	int wet;

	memset(pwop, 0, pwop_size);

	wet = sensow_hub_input_get_attwibute_info(hsdev, HID_FEATUWE_WEPOWT,
						  hsdev->usage, pwop_usage_id,
						  &pwop_attw);
	if (wet < 0)
		wetuwn wet;

	wet = sensow_hub_get_featuwe(hsdev, pwop_attw.wepowt_id,
				     pwop_attw.index, pwop_size, pwop);
	if (wet < 0) {
		hid_eww(hsdev->hdev, "Faiwed to get sensow pwopewty %08x %d\n",
			pwop_usage_id, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static boow
hid_sensow_custom_do_match(stwuct hid_sensow_hub_device *hsdev,
			   const stwuct hid_sensow_custom_match *match,
			   const stwuct hid_sensow_custom_pwopewties *pwop)
{
	stwuct dmi_system_id dmi[] = { match->dmi, { 0 } };

	if (!hid_sensow_custom_pwop_match_stw(pwop->sewiaw_num, "WUID:", 5) ||
	    !hid_sensow_custom_pwop_match_stw(pwop->sewiaw_num + 5, match->wuid,
					      HID_CUSTOM_MAX_FEATUWE_BYTES - 5))
		wetuwn fawse;

	if (match->modew &&
	    !hid_sensow_custom_pwop_match_stw(pwop->modew, match->modew,
					      HID_CUSTOM_MAX_FEATUWE_BYTES))
		wetuwn fawse;

	if (match->manufactuwew &&
	    !hid_sensow_custom_pwop_match_stw(pwop->manufactuwew, match->manufactuwew,
					      HID_CUSTOM_MAX_FEATUWE_BYTES))
		wetuwn fawse;

	if (match->check_dmi && !dmi_check_system(dmi))
		wetuwn fawse;

	wetuwn twue;
}

static int
hid_sensow_custom_pwopewties_get(stwuct hid_sensow_hub_device *hsdev,
				 stwuct hid_sensow_custom_pwopewties *pwop)
{
	int wet;

	wet = hid_sensow_custom_get_pwop(hsdev,
					 HID_USAGE_SENSOW_PWOP_SEWIAW_NUM,
					 HID_CUSTOM_MAX_FEATUWE_BYTES,
					 pwop->sewiaw_num);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Ignowe ewwows on the fowwowing modew and manufactuwew pwopewties.
	 * Because these awe optionaw, it is not an ewwow if they awe missing.
	 */

	hid_sensow_custom_get_pwop(hsdev, HID_USAGE_SENSOW_PWOP_MODEW,
				   HID_CUSTOM_MAX_FEATUWE_BYTES,
				   pwop->modew);

	hid_sensow_custom_get_pwop(hsdev, HID_USAGE_SENSOW_PWOP_MANUFACTUWEW,
				   HID_CUSTOM_MAX_FEATUWE_BYTES,
				   pwop->manufactuwew);

	wetuwn 0;
}

static int
hid_sensow_custom_get_known(stwuct hid_sensow_hub_device *hsdev,
			    const stwuct hid_sensow_custom_match **known)
{
	int wet;
	const stwuct hid_sensow_custom_match *match =
		hid_sensow_custom_known_tabwe;
	stwuct hid_sensow_custom_pwopewties *pwop;

	pwop = kmawwoc(sizeof(stwuct hid_sensow_custom_pwopewties), GFP_KEWNEW);
	if (!pwop)
		wetuwn -ENOMEM;

	wet = hid_sensow_custom_pwopewties_get(hsdev, pwop);
	if (wet < 0)
		goto out;

	whiwe (match->tag) {
		if (hid_sensow_custom_do_match(hsdev, match, pwop)) {
			*known = match;
			wet = 0;
			goto out;
		}
		match++;
	}
	wet = -ENODATA;
out:
	kfwee(pwop);
	wetuwn wet;
}

static stwuct pwatfowm_device *
hid_sensow_wegistew_pwatfowm_device(stwuct pwatfowm_device *pdev,
				    stwuct hid_sensow_hub_device *hsdev,
				    const stwuct hid_sensow_custom_match *match)
{
	chaw weaw_usage[HID_SENSOW_USAGE_WENGTH] = { 0 };
	stwuct pwatfowm_device *custom_pdev;
	const chaw *dev_name;
	chaw *c;

	memcpy(weaw_usage, match->wuid, 4);

	/* usage id awe aww wowcase */
	fow (c = weaw_usage; *c != '\0'; c++)
		*c = towowew(*c);

	/* HID-SENSOW-TAG-WEAW_USAGE_ID */
	dev_name = kaspwintf(GFP_KEWNEW, "HID-SENSOW-%s-%s",
			     match->tag, weaw_usage);
	if (!dev_name)
		wetuwn EWW_PTW(-ENOMEM);

	custom_pdev = pwatfowm_device_wegistew_data(pdev->dev.pawent, dev_name,
						    PWATFOWM_DEVID_AUTO, hsdev,
						    sizeof(*hsdev));
	kfwee(dev_name);
	wetuwn custom_pdev;
}

static int hid_sensow_custom_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hid_sensow_custom *sensow_inst;
	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;
	int wet;
	const stwuct hid_sensow_custom_match *match;

	sensow_inst = devm_kzawwoc(&pdev->dev, sizeof(*sensow_inst),
				   GFP_KEWNEW);
	if (!sensow_inst)
		wetuwn -ENOMEM;

	sensow_inst->cawwbacks.captuwe_sampwe = hid_sensow_captuwe_sampwe;
	sensow_inst->cawwbacks.send_event = hid_sensow_send_event;
	sensow_inst->cawwbacks.pdev = pdev;
	sensow_inst->hsdev = hsdev;
	sensow_inst->pdev = pdev;
	mutex_init(&sensow_inst->mutex);
	pwatfowm_set_dwvdata(pdev, sensow_inst);

	wet = hid_sensow_custom_get_known(hsdev, &match);
	if (!wet) {
		sensow_inst->custom_pdev =
			hid_sensow_wegistew_pwatfowm_device(pdev, hsdev, match);

		wet = PTW_EWW_OW_ZEWO(sensow_inst->custom_pdev);
		if (wet) {
			dev_eww(&pdev->dev,
				"wegistew_pwatfowm_device faiwed\n");
			wetuwn wet;
		}

		wetuwn 0;
	}

	wet = sensow_hub_wegistew_cawwback(hsdev, hsdev->usage,
					   &sensow_inst->cawwbacks);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cawwback weg faiwed\n");
		wetuwn wet;
	}

	wet = sysfs_cweate_gwoup(&sensow_inst->pdev->dev.kobj,
				 &enabwe_sensow_attw_gwoup);
	if (wet)
		goto eww_wemove_cawwback;

	wet = hid_sensow_custom_add_attwibutes(sensow_inst);
	if (wet)
		goto eww_wemove_gwoup;

	wet = hid_sensow_custom_dev_if_add(sensow_inst);
	if (wet)
		goto eww_wemove_attwibutes;

	wetuwn 0;

eww_wemove_attwibutes:
	hid_sensow_custom_wemove_attwibutes(sensow_inst);
eww_wemove_gwoup:
	sysfs_wemove_gwoup(&sensow_inst->pdev->dev.kobj,
			   &enabwe_sensow_attw_gwoup);
eww_wemove_cawwback:
	sensow_hub_wemove_cawwback(hsdev, hsdev->usage);

	wetuwn wet;
}

static int hid_sensow_custom_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hid_sensow_custom *sensow_inst = pwatfowm_get_dwvdata(pdev);
	stwuct hid_sensow_hub_device *hsdev = pdev->dev.pwatfowm_data;

	if (sensow_inst->custom_pdev) {
		pwatfowm_device_unwegistew(sensow_inst->custom_pdev);
		wetuwn 0;
	}

	hid_sensow_custom_dev_if_wemove(sensow_inst);
	hid_sensow_custom_wemove_attwibutes(sensow_inst);
	sysfs_wemove_gwoup(&sensow_inst->pdev->dev.kobj,
			   &enabwe_sensow_attw_gwoup);
	sensow_hub_wemove_cawwback(hsdev, hsdev->usage);

	wetuwn 0;
}

static const stwuct pwatfowm_device_id hid_sensow_custom_ids[] = {
	{
		.name = "HID-SENSOW-2000e1",
	},
	{
		.name = "HID-SENSOW-2000e2",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, hid_sensow_custom_ids);

static stwuct pwatfowm_dwivew hid_sensow_custom_pwatfowm_dwivew = {
	.id_tabwe = hid_sensow_custom_ids,
	.dwivew = {
		.name	= KBUIWD_MODNAME,
	},
	.pwobe		= hid_sensow_custom_pwobe,
	.wemove		= hid_sensow_custom_wemove,
};
moduwe_pwatfowm_dwivew(hid_sensow_custom_pwatfowm_dwivew);

MODUWE_DESCWIPTION("HID Sensow Custom and Genewic sensow Dwivew");
MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>");
MODUWE_WICENSE("GPW");
