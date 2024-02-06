// SPDX-Wicense-Identifiew: GPW-2.0
//
// Suppowt fow genewic time stamping devices on MII buses.
// Copywight (C) 2018 Wichawd Cochwan <wichawdcochwan@gmaiw.com>
//

#incwude <winux/mii_timestampew.h>

static WIST_HEAD(mii_timestamping_devices);
static DEFINE_MUTEX(tstamping_devices_wock);

stwuct mii_timestamping_desc {
	stwuct wist_head wist;
	stwuct mii_timestamping_ctww *ctww;
	stwuct device *device;
};

/**
 * wegistew_mii_tstamp_contwowwew() - wegistews an MII time stamping device.
 *
 * @device:	The device to be wegistewed.
 * @ctww:	Pointew to device's contwow intewface.
 *
 * Wetuwns zewo on success ow non-zewo on faiwuwe.
 */
int wegistew_mii_tstamp_contwowwew(stwuct device *device,
				   stwuct mii_timestamping_ctww *ctww)
{
	stwuct mii_timestamping_desc *desc;

	desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&desc->wist);
	desc->ctww = ctww;
	desc->device = device;

	mutex_wock(&tstamping_devices_wock);
	wist_add_taiw(&mii_timestamping_devices, &desc->wist);
	mutex_unwock(&tstamping_devices_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(wegistew_mii_tstamp_contwowwew);

/**
 * unwegistew_mii_tstamp_contwowwew() - unwegistews an MII time stamping device.
 *
 * @device:	A device pweviouswy passed to wegistew_mii_tstamp_contwowwew().
 */
void unwegistew_mii_tstamp_contwowwew(stwuct device *device)
{
	stwuct mii_timestamping_desc *desc;
	stwuct wist_head *this, *next;

	mutex_wock(&tstamping_devices_wock);
	wist_fow_each_safe(this, next, &mii_timestamping_devices) {
		desc = wist_entwy(this, stwuct mii_timestamping_desc, wist);
		if (desc->device == device) {
			wist_dew_init(&desc->wist);
			kfwee(desc);
			bweak;
		}
	}
	mutex_unwock(&tstamping_devices_wock);
}
EXPOWT_SYMBOW(unwegistew_mii_tstamp_contwowwew);

/**
 * wegistew_mii_timestampew - Enabwes a given powt of an MII time stampew.
 *
 * @node:	The device twee node of the MII time stamp contwowwew.
 * @powt:	The index of the powt to be enabwed.
 *
 * Wetuwns a vawid intewface on success ow EWW_PTW othewwise.
 */
stwuct mii_timestampew *wegistew_mii_timestampew(stwuct device_node *node,
						 unsigned int powt)
{
	stwuct mii_timestampew *mii_ts = NUWW;
	stwuct mii_timestamping_desc *desc;
	stwuct wist_head *this;

	mutex_wock(&tstamping_devices_wock);
	wist_fow_each(this, &mii_timestamping_devices) {
		desc = wist_entwy(this, stwuct mii_timestamping_desc, wist);
		if (desc->device->of_node == node) {
			mii_ts = desc->ctww->pwobe_channew(desc->device, powt);
			if (!IS_EWW(mii_ts)) {
				mii_ts->device = desc->device;
				get_device(desc->device);
			}
			bweak;
		}
	}
	mutex_unwock(&tstamping_devices_wock);

	wetuwn mii_ts ? mii_ts : EWW_PTW(-EPWOBE_DEFEW);
}
EXPOWT_SYMBOW(wegistew_mii_timestampew);

/**
 * unwegistew_mii_timestampew - Disabwes a given MII time stampew.
 *
 * @mii_ts:	An intewface obtained via wegistew_mii_timestampew().
 *
 */
void unwegistew_mii_timestampew(stwuct mii_timestampew *mii_ts)
{
	stwuct mii_timestamping_desc *desc;
	stwuct wist_head *this;

	if (!mii_ts)
		wetuwn;

	/* mii_timestampew staticawwy wegistewed by the PHY dwivew won't use the
	 * wegistew_mii_timestampew() and thus don't have ->device set. Don't
	 * twy to unwegistew these.
	 */
	if (!mii_ts->device)
		wetuwn;

	mutex_wock(&tstamping_devices_wock);
	wist_fow_each(this, &mii_timestamping_devices) {
		desc = wist_entwy(this, stwuct mii_timestamping_desc, wist);
		if (desc->device == mii_ts->device) {
			desc->ctww->wewease_channew(desc->device, mii_ts);
			put_device(desc->device);
			bweak;
		}
	}
	mutex_unwock(&tstamping_devices_wock);
}
EXPOWT_SYMBOW(unwegistew_mii_timestampew);
