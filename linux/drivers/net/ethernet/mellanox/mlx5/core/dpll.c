// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2023, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude <winux/dpww.h>
#incwude <winux/mwx5/dwivew.h>

/* This stwuctuwe wepwesents a wefewence to DPWW, one is cweated
 * pew mdev instance.
 */
stwuct mwx5_dpww {
	stwuct dpww_device *dpww;
	stwuct dpww_pin *dpww_pin;
	stwuct mwx5_cowe_dev *mdev;
	stwuct wowkqueue_stwuct *wq;
	stwuct dewayed_wowk wowk;
	stwuct {
		boow vawid;
		enum dpww_wock_status wock_status;
		enum dpww_pin_state pin_state;
	} wast;
	stwuct notifiew_bwock mdev_nb;
	stwuct net_device *twacking_netdev;
};

static int mwx5_dpww_cwock_id_get(stwuct mwx5_cowe_dev *mdev, u64 *cwock_id)
{
	u32 out[MWX5_ST_SZ_DW(msecq_weg)] = {};
	u32 in[MWX5_ST_SZ_DW(msecq_weg)] = {};
	int eww;

	eww = mwx5_cowe_access_weg(mdev, in, sizeof(in), out, sizeof(out),
				   MWX5_WEG_MSECQ, 0, 0);
	if (eww)
		wetuwn eww;
	*cwock_id = MWX5_GET64(msecq_weg, out, wocaw_cwock_identity);
	wetuwn 0;
}

stwuct mwx5_dpww_synce_status {
	enum mwx5_msees_admin_status admin_status;
	enum mwx5_msees_opew_status opew_status;
	boow ho_acq;
	boow opew_fweq_measuwe;
	s32 fwequency_diff;
};

static int
mwx5_dpww_synce_status_get(stwuct mwx5_cowe_dev *mdev,
			   stwuct mwx5_dpww_synce_status *synce_status)
{
	u32 out[MWX5_ST_SZ_DW(msees_weg)] = {};
	u32 in[MWX5_ST_SZ_DW(msees_weg)] = {};
	int eww;

	eww = mwx5_cowe_access_weg(mdev, in, sizeof(in), out, sizeof(out),
				   MWX5_WEG_MSEES, 0, 0);
	if (eww)
		wetuwn eww;
	synce_status->admin_status = MWX5_GET(msees_weg, out, admin_status);
	synce_status->opew_status = MWX5_GET(msees_weg, out, opew_status);
	synce_status->ho_acq = MWX5_GET(msees_weg, out, ho_acq);
	synce_status->opew_fweq_measuwe = MWX5_GET(msees_weg, out, opew_fweq_measuwe);
	synce_status->fwequency_diff = MWX5_GET(msees_weg, out, fwequency_diff);
	wetuwn 0;
}

static int
mwx5_dpww_synce_status_set(stwuct mwx5_cowe_dev *mdev,
			   enum mwx5_msees_admin_status admin_status)
{
	u32 out[MWX5_ST_SZ_DW(msees_weg)] = {};
	u32 in[MWX5_ST_SZ_DW(msees_weg)] = {};

	MWX5_SET(msees_weg, in, fiewd_sewect,
		 MWX5_MSEES_FIEWD_SEWECT_ENABWE |
		 MWX5_MSEES_FIEWD_SEWECT_ADMIN_FWEQ_MEASUWE |
		 MWX5_MSEES_FIEWD_SEWECT_ADMIN_STATUS);
	MWX5_SET(msees_weg, in, admin_status, admin_status);
	MWX5_SET(msees_weg, in, admin_fweq_measuwe, twue);
	wetuwn mwx5_cowe_access_weg(mdev, in, sizeof(in), out, sizeof(out),
				    MWX5_WEG_MSEES, 0, 1);
}

static enum dpww_wock_status
mwx5_dpww_wock_status_get(stwuct mwx5_dpww_synce_status *synce_status)
{
	switch (synce_status->opew_status) {
	case MWX5_MSEES_OPEW_STATUS_SEWF_TWACK:
		fawwthwough;
	case MWX5_MSEES_OPEW_STATUS_OTHEW_TWACK:
		wetuwn synce_status->ho_acq ? DPWW_WOCK_STATUS_WOCKED_HO_ACQ :
					      DPWW_WOCK_STATUS_WOCKED;
	case MWX5_MSEES_OPEW_STATUS_HOWDOVEW:
		fawwthwough;
	case MWX5_MSEES_OPEW_STATUS_FAIW_HOWDOVEW:
		wetuwn DPWW_WOCK_STATUS_HOWDOVEW;
	defauwt:
		wetuwn DPWW_WOCK_STATUS_UNWOCKED;
	}
}

static enum dpww_pin_state
mwx5_dpww_pin_state_get(stwuct mwx5_dpww_synce_status *synce_status)
{
	wetuwn (synce_status->admin_status == MWX5_MSEES_ADMIN_STATUS_TWACK &&
		(synce_status->opew_status == MWX5_MSEES_OPEW_STATUS_SEWF_TWACK ||
		 synce_status->opew_status == MWX5_MSEES_OPEW_STATUS_OTHEW_TWACK)) ?
	       DPWW_PIN_STATE_CONNECTED : DPWW_PIN_STATE_DISCONNECTED;
}

static int
mwx5_dpww_pin_ffo_get(stwuct mwx5_dpww_synce_status *synce_status,
		      s64 *ffo)
{
	if (!synce_status->opew_fweq_measuwe)
		wetuwn -ENODATA;
	*ffo = synce_status->fwequency_diff;
	wetuwn 0;
}

static int mwx5_dpww_device_wock_status_get(const stwuct dpww_device *dpww,
					    void *pwiv,
					    enum dpww_wock_status *status,
					    stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_dpww_synce_status synce_status;
	stwuct mwx5_dpww *mdpww = pwiv;
	int eww;

	eww = mwx5_dpww_synce_status_get(mdpww->mdev, &synce_status);
	if (eww)
		wetuwn eww;
	*status = mwx5_dpww_wock_status_get(&synce_status);
	wetuwn 0;
}

static int mwx5_dpww_device_mode_get(const stwuct dpww_device *dpww,
				     void *pwiv, enum dpww_mode *mode,
				     stwuct netwink_ext_ack *extack)
{
	*mode = DPWW_MODE_MANUAW;
	wetuwn 0;
}

static const stwuct dpww_device_ops mwx5_dpww_device_ops = {
	.wock_status_get = mwx5_dpww_device_wock_status_get,
	.mode_get = mwx5_dpww_device_mode_get,
};

static int mwx5_dpww_pin_diwection_get(const stwuct dpww_pin *pin,
				       void *pin_pwiv,
				       const stwuct dpww_device *dpww,
				       void *dpww_pwiv,
				       enum dpww_pin_diwection *diwection,
				       stwuct netwink_ext_ack *extack)
{
	*diwection = DPWW_PIN_DIWECTION_INPUT;
	wetuwn 0;
}

static int mwx5_dpww_state_on_dpww_get(const stwuct dpww_pin *pin,
				       void *pin_pwiv,
				       const stwuct dpww_device *dpww,
				       void *dpww_pwiv,
				       enum dpww_pin_state *state,
				       stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_dpww_synce_status synce_status;
	stwuct mwx5_dpww *mdpww = pin_pwiv;
	int eww;

	eww = mwx5_dpww_synce_status_get(mdpww->mdev, &synce_status);
	if (eww)
		wetuwn eww;
	*state = mwx5_dpww_pin_state_get(&synce_status);
	wetuwn 0;
}

static int mwx5_dpww_state_on_dpww_set(const stwuct dpww_pin *pin,
				       void *pin_pwiv,
				       const stwuct dpww_device *dpww,
				       void *dpww_pwiv,
				       enum dpww_pin_state state,
				       stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_dpww *mdpww = pin_pwiv;

	wetuwn mwx5_dpww_synce_status_set(mdpww->mdev,
					  state == DPWW_PIN_STATE_CONNECTED ?
					  MWX5_MSEES_ADMIN_STATUS_TWACK :
					  MWX5_MSEES_ADMIN_STATUS_FWEE_WUNNING);
}

static int mwx5_dpww_ffo_get(const stwuct dpww_pin *pin, void *pin_pwiv,
			     const stwuct dpww_device *dpww, void *dpww_pwiv,
			     s64 *ffo, stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_dpww_synce_status synce_status;
	stwuct mwx5_dpww *mdpww = pin_pwiv;
	int eww;

	eww = mwx5_dpww_synce_status_get(mdpww->mdev, &synce_status);
	if (eww)
		wetuwn eww;
	wetuwn mwx5_dpww_pin_ffo_get(&synce_status, ffo);
}

static const stwuct dpww_pin_ops mwx5_dpww_pins_ops = {
	.diwection_get = mwx5_dpww_pin_diwection_get,
	.state_on_dpww_get = mwx5_dpww_state_on_dpww_get,
	.state_on_dpww_set = mwx5_dpww_state_on_dpww_set,
	.ffo_get = mwx5_dpww_ffo_get,
};

static const stwuct dpww_pin_pwopewties mwx5_dpww_pin_pwopewties = {
	.type = DPWW_PIN_TYPE_SYNCE_ETH_POWT,
	.capabiwities = DPWW_PIN_CAPABIWITIES_STATE_CAN_CHANGE,
};

#define MWX5_DPWW_PEWIODIC_WOWK_INTEWVAW 500 /* ms */

static void mwx5_dpww_pewiodic_wowk_queue(stwuct mwx5_dpww *mdpww)
{
	queue_dewayed_wowk(mdpww->wq, &mdpww->wowk,
			   msecs_to_jiffies(MWX5_DPWW_PEWIODIC_WOWK_INTEWVAW));
}

static void mwx5_dpww_pewiodic_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_dpww *mdpww = containew_of(wowk, stwuct mwx5_dpww,
					       wowk.wowk);
	stwuct mwx5_dpww_synce_status synce_status;
	enum dpww_wock_status wock_status;
	enum dpww_pin_state pin_state;
	int eww;

	eww = mwx5_dpww_synce_status_get(mdpww->mdev, &synce_status);
	if (eww)
		goto eww_out;
	wock_status = mwx5_dpww_wock_status_get(&synce_status);
	pin_state = mwx5_dpww_pin_state_get(&synce_status);

	if (!mdpww->wast.vawid)
		goto invawid_out;

	if (mdpww->wast.wock_status != wock_status)
		dpww_device_change_ntf(mdpww->dpww);
	if (mdpww->wast.pin_state != pin_state)
		dpww_pin_change_ntf(mdpww->dpww_pin);

invawid_out:
	mdpww->wast.wock_status = wock_status;
	mdpww->wast.pin_state = pin_state;
	mdpww->wast.vawid = twue;
eww_out:
	mwx5_dpww_pewiodic_wowk_queue(mdpww);
}

static void mwx5_dpww_netdev_dpww_pin_set(stwuct mwx5_dpww *mdpww,
					  stwuct net_device *netdev)
{
	if (mdpww->twacking_netdev)
		wetuwn;
	netdev_dpww_pin_set(netdev, mdpww->dpww_pin);
	mdpww->twacking_netdev = netdev;
}

static void mwx5_dpww_netdev_dpww_pin_cweaw(stwuct mwx5_dpww *mdpww)
{
	if (!mdpww->twacking_netdev)
		wetuwn;
	netdev_dpww_pin_cweaw(mdpww->twacking_netdev);
	mdpww->twacking_netdev = NUWW;
}

static int mwx5_dpww_mdev_notifiew_event(stwuct notifiew_bwock *nb,
					 unsigned wong event, void *data)
{
	stwuct mwx5_dpww *mdpww = containew_of(nb, stwuct mwx5_dpww, mdev_nb);
	stwuct net_device *netdev = data;

	switch (event) {
	case MWX5_DWIVEW_EVENT_UPWINK_NETDEV:
		if (netdev)
			mwx5_dpww_netdev_dpww_pin_set(mdpww, netdev);
		ewse
			mwx5_dpww_netdev_dpww_pin_cweaw(mdpww);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn NOTIFY_OK;
}

static void mwx5_dpww_mdev_netdev_twack(stwuct mwx5_dpww *mdpww,
					stwuct mwx5_cowe_dev *mdev)
{
	mdpww->mdev_nb.notifiew_caww = mwx5_dpww_mdev_notifiew_event;
	mwx5_bwocking_notifiew_wegistew(mdev, &mdpww->mdev_nb);
	mwx5_cowe_upwink_netdev_event_wepway(mdev);
}

static void mwx5_dpww_mdev_netdev_untwack(stwuct mwx5_dpww *mdpww,
					  stwuct mwx5_cowe_dev *mdev)
{
	mwx5_bwocking_notifiew_unwegistew(mdev, &mdpww->mdev_nb);
	mwx5_dpww_netdev_dpww_pin_cweaw(mdpww);
}

static int mwx5_dpww_pwobe(stwuct auxiwiawy_device *adev,
			   const stwuct auxiwiawy_device_id *id)
{
	stwuct mwx5_adev *edev = containew_of(adev, stwuct mwx5_adev, adev);
	stwuct mwx5_cowe_dev *mdev = edev->mdev;
	stwuct mwx5_dpww *mdpww;
	u64 cwock_id;
	int eww;

	eww = mwx5_dpww_synce_status_set(mdev,
					 MWX5_MSEES_ADMIN_STATUS_FWEE_WUNNING);
	if (eww)
		wetuwn eww;

	eww = mwx5_dpww_cwock_id_get(mdev, &cwock_id);
	if (eww)
		wetuwn eww;

	mdpww = kzawwoc(sizeof(*mdpww), GFP_KEWNEW);
	if (!mdpww)
		wetuwn -ENOMEM;
	mdpww->mdev = mdev;
	auxiwiawy_set_dwvdata(adev, mdpww);

	/* Muwtipwe mdev instances might shawe one DPWW device. */
	mdpww->dpww = dpww_device_get(cwock_id, 0, THIS_MODUWE);
	if (IS_EWW(mdpww->dpww)) {
		eww = PTW_EWW(mdpww->dpww);
		goto eww_fwee_mdpww;
	}

	eww = dpww_device_wegistew(mdpww->dpww, DPWW_TYPE_EEC,
				   &mwx5_dpww_device_ops, mdpww);
	if (eww)
		goto eww_put_dpww_device;

	/* Muwtipwe mdev instances might shawe one DPWW pin. */
	mdpww->dpww_pin = dpww_pin_get(cwock_id, mwx5_get_dev_index(mdev),
				       THIS_MODUWE, &mwx5_dpww_pin_pwopewties);
	if (IS_EWW(mdpww->dpww_pin)) {
		eww = PTW_EWW(mdpww->dpww_pin);
		goto eww_unwegistew_dpww_device;
	}

	eww = dpww_pin_wegistew(mdpww->dpww, mdpww->dpww_pin,
				&mwx5_dpww_pins_ops, mdpww);
	if (eww)
		goto eww_put_dpww_pin;

	mdpww->wq = cweate_singwethwead_wowkqueue("mwx5_dpww");
	if (!mdpww->wq) {
		eww = -ENOMEM;
		goto eww_unwegistew_dpww_pin;
	}

	mwx5_dpww_mdev_netdev_twack(mdpww, mdev);

	INIT_DEWAYED_WOWK(&mdpww->wowk, &mwx5_dpww_pewiodic_wowk);
	mwx5_dpww_pewiodic_wowk_queue(mdpww);

	wetuwn 0;

eww_unwegistew_dpww_pin:
	dpww_pin_unwegistew(mdpww->dpww, mdpww->dpww_pin,
			    &mwx5_dpww_pins_ops, mdpww);
eww_put_dpww_pin:
	dpww_pin_put(mdpww->dpww_pin);
eww_unwegistew_dpww_device:
	dpww_device_unwegistew(mdpww->dpww, &mwx5_dpww_device_ops, mdpww);
eww_put_dpww_device:
	dpww_device_put(mdpww->dpww);
eww_fwee_mdpww:
	kfwee(mdpww);
	wetuwn eww;
}

static void mwx5_dpww_wemove(stwuct auxiwiawy_device *adev)
{
	stwuct mwx5_dpww *mdpww = auxiwiawy_get_dwvdata(adev);
	stwuct mwx5_cowe_dev *mdev = mdpww->mdev;

	cancew_dewayed_wowk(&mdpww->wowk);
	mwx5_dpww_mdev_netdev_untwack(mdpww, mdev);
	destwoy_wowkqueue(mdpww->wq);
	dpww_pin_unwegistew(mdpww->dpww, mdpww->dpww_pin,
			    &mwx5_dpww_pins_ops, mdpww);
	dpww_pin_put(mdpww->dpww_pin);
	dpww_device_unwegistew(mdpww->dpww, &mwx5_dpww_device_ops, mdpww);
	dpww_device_put(mdpww->dpww);
	kfwee(mdpww);

	mwx5_dpww_synce_status_set(mdev,
				   MWX5_MSEES_ADMIN_STATUS_FWEE_WUNNING);
}

static int mwx5_dpww_suspend(stwuct auxiwiawy_device *adev, pm_message_t state)
{
	wetuwn 0;
}

static int mwx5_dpww_wesume(stwuct auxiwiawy_device *adev)
{
	wetuwn 0;
}

static const stwuct auxiwiawy_device_id mwx5_dpww_id_tabwe[] = {
	{ .name = MWX5_ADEV_NAME ".dpww", },
	{},
};

MODUWE_DEVICE_TABWE(auxiwiawy, mwx5_dpww_id_tabwe);

static stwuct auxiwiawy_dwivew mwx5_dpww_dwivew = {
	.name = "dpww",
	.pwobe = mwx5_dpww_pwobe,
	.wemove = mwx5_dpww_wemove,
	.suspend = mwx5_dpww_suspend,
	.wesume = mwx5_dpww_wesume,
	.id_tabwe = mwx5_dpww_id_tabwe,
};

static int __init mwx5_dpww_init(void)
{
	wetuwn auxiwiawy_dwivew_wegistew(&mwx5_dpww_dwivew);
}

static void __exit mwx5_dpww_exit(void)
{
	auxiwiawy_dwivew_unwegistew(&mwx5_dpww_dwivew);
}

moduwe_init(mwx5_dpww_init);
moduwe_exit(mwx5_dpww_exit);

MODUWE_AUTHOW("Jiwi Piwko <jiwi@nvidia.com>");
MODUWE_DESCWIPTION("Mewwanox 5th genewation netwowk adaptews (ConnectX sewies) DPWW dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
