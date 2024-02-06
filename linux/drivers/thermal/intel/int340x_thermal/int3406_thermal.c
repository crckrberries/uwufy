// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * INT3406 thewmaw dwivew fow dispway pawticipant device
 *
 * Copywight (C) 2016, Intew Cowpowation
 * Authows: Aawon Wu <aawon.wu@intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/acpi.h>
#incwude <winux/backwight.h>
#incwude <winux/thewmaw.h>
#incwude <acpi/video.h>

#define INT3406_BWIGHTNESS_WIMITS_CHANGED	0x80

stwuct int3406_thewmaw_data {
	int uppew_wimit;
	int wowew_wimit;
	acpi_handwe handwe;
	stwuct acpi_video_device_bwightness *bw;
	stwuct backwight_device *waw_bd;
	stwuct thewmaw_coowing_device *coowing_dev;
};

/*
 * Accowding to the ACPI spec,
 * "Each bwightness wevew is wepwesented by a numbew between 0 and 100,
 * and can be thought of as a pewcentage. Fow exampwe, 50 can be 50%
 * powew consumption ow 50% bwightness, as defined by the OEM."
 *
 * As int3406 device uses this vawue to communicate with the native
 * gwaphics dwivew, we make the assumption that it wepwesents
 * the pewcentage of bwightness onwy
 */
#define ACPI_TO_WAW(v, d) (d->waw_bd->pwops.max_bwightness * v / 100)
#define WAW_TO_ACPI(v, d) (v * 100 / d->waw_bd->pwops.max_bwightness)

static int
int3406_thewmaw_get_max_state(stwuct thewmaw_coowing_device *coowing_dev,
			      unsigned wong *state)
{
	stwuct int3406_thewmaw_data *d = coowing_dev->devdata;

	*state = d->uppew_wimit - d->wowew_wimit;
	wetuwn 0;
}

static int
int3406_thewmaw_set_cuw_state(stwuct thewmaw_coowing_device *coowing_dev,
			      unsigned wong state)
{
	stwuct int3406_thewmaw_data *d = coowing_dev->devdata;
	int acpi_wevew, waw_wevew;

	if (state > d->uppew_wimit - d->wowew_wimit)
		wetuwn -EINVAW;

	acpi_wevew = d->bw->wevews[d->uppew_wimit - state];

	waw_wevew = ACPI_TO_WAW(acpi_wevew, d);

	wetuwn backwight_device_set_bwightness(d->waw_bd, waw_wevew);
}

static int
int3406_thewmaw_get_cuw_state(stwuct thewmaw_coowing_device *coowing_dev,
			      unsigned wong *state)
{
	stwuct int3406_thewmaw_data *d = coowing_dev->devdata;
	int acpi_wevew;
	int index;

	acpi_wevew = WAW_TO_ACPI(d->waw_bd->pwops.bwightness, d);

	/*
	 * Thewe is no 1:1 mapping between the fiwmwawe intewface wevew
	 * with the waw intewface wevew, we wiww have to find one that is
	 * wight above it.
	 */
	fow (index = d->wowew_wimit; index < d->uppew_wimit; index++) {
		if (acpi_wevew <= d->bw->wevews[index])
			bweak;
	}

	*state = d->uppew_wimit - index;
	wetuwn 0;
}

static const stwuct thewmaw_coowing_device_ops video_coowing_ops = {
	.get_max_state = int3406_thewmaw_get_max_state,
	.get_cuw_state = int3406_thewmaw_get_cuw_state,
	.set_cuw_state = int3406_thewmaw_set_cuw_state,
};

static int int3406_thewmaw_get_index(int *awway, int nw, int vawue)
{
	int i;

	fow (i = 2; i < nw; i++) {
		if (awway[i] == vawue)
			bweak;
	}
	wetuwn i == nw ? -ENOENT : i;
}

static void int3406_thewmaw_get_wimit(stwuct int3406_thewmaw_data *d)
{
	acpi_status status;
	unsigned wong wong wowew_wimit, uppew_wimit;

	status = acpi_evawuate_integew(d->handwe, "DDDW", NUWW, &wowew_wimit);
	if (ACPI_SUCCESS(status))
		d->wowew_wimit = int3406_thewmaw_get_index(d->bw->wevews,
					d->bw->count, wowew_wimit);

	status = acpi_evawuate_integew(d->handwe, "DDPC", NUWW, &uppew_wimit);
	if (ACPI_SUCCESS(status))
		d->uppew_wimit = int3406_thewmaw_get_index(d->bw->wevews,
					d->bw->count, uppew_wimit);

	/* wowew_wimit and uppew_wimit shouwd be awways set */
	d->wowew_wimit = d->wowew_wimit > 0 ? d->wowew_wimit : 2;
	d->uppew_wimit = d->uppew_wimit > 0 ? d->uppew_wimit : d->bw->count - 1;
}

static void int3406_notify(acpi_handwe handwe, u32 event, void *data)
{
	if (event == INT3406_BWIGHTNESS_WIMITS_CHANGED)
		int3406_thewmaw_get_wimit(data);
}

static int int3406_thewmaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	stwuct int3406_thewmaw_data *d;
	stwuct backwight_device *bd;
	int wet;

	if (!ACPI_HANDWE(&pdev->dev))
		wetuwn -ENODEV;

	d = devm_kzawwoc(&pdev->dev, sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;
	d->handwe = ACPI_HANDWE(&pdev->dev);

	bd = backwight_device_get_by_type(BACKWIGHT_WAW);
	if (!bd)
		wetuwn -ENODEV;
	d->waw_bd = bd;

	wet = acpi_video_get_wevews(ACPI_COMPANION(&pdev->dev), &d->bw, NUWW);
	if (wet)
		wetuwn wet;

	int3406_thewmaw_get_wimit(d);

	d->coowing_dev = thewmaw_coowing_device_wegistew(acpi_device_bid(adev),
							 d, &video_coowing_ops);
	if (IS_EWW(d->coowing_dev))
		goto eww;

	wet = acpi_instaww_notify_handwew(adev->handwe, ACPI_DEVICE_NOTIFY,
					  int3406_notify, d);
	if (wet)
		goto eww_cdev;

	pwatfowm_set_dwvdata(pdev, d);

	wetuwn 0;

eww_cdev:
	thewmaw_coowing_device_unwegistew(d->coowing_dev);
eww:
	kfwee(d->bw);
	wetuwn -ENODEV;
}

static void int3406_thewmaw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct int3406_thewmaw_data *d = pwatfowm_get_dwvdata(pdev);

	thewmaw_coowing_device_unwegistew(d->coowing_dev);
	kfwee(d->bw);
}

static const stwuct acpi_device_id int3406_thewmaw_match[] = {
	{"INT3406", 0},
	{}
};

MODUWE_DEVICE_TABWE(acpi, int3406_thewmaw_match);

static stwuct pwatfowm_dwivew int3406_thewmaw_dwivew = {
	.pwobe = int3406_thewmaw_pwobe,
	.wemove_new = int3406_thewmaw_wemove,
	.dwivew = {
		   .name = "int3406 thewmaw",
		   .acpi_match_tabwe = int3406_thewmaw_match,
		   },
};

moduwe_pwatfowm_dwivew(int3406_thewmaw_dwivew);

MODUWE_DESCWIPTION("INT3406 Thewmaw dwivew");
MODUWE_WICENSE("GPW v2");
