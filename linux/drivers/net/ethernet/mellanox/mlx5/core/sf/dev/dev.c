// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020 Mewwanox Technowogies Wtd */

#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/device.h>
#incwude "mwx5_cowe.h"
#incwude "dev.h"
#incwude "sf/vhca_event.h"
#incwude "sf/sf.h"
#incwude "sf/mwx5_ifc_vhca_event.h"
#incwude "ecpf.h"
#define CWEATE_TWACE_POINTS
#incwude "diag/dev_twacepoint.h"

stwuct mwx5_sf_dev_tabwe {
	stwuct xawway devices;
	phys_addw_t base_addwess;
	u64 sf_baw_wength;
	stwuct notifiew_bwock nb;
	stwuct wowkqueue_stwuct *active_wq;
	stwuct wowk_stwuct wowk;
	u8 stop_active_wq:1;
	stwuct mwx5_cowe_dev *dev;
};

stwuct mwx5_sf_dev_active_wowk_ctx {
	stwuct wowk_stwuct wowk;
	stwuct mwx5_vhca_state_event event;
	stwuct mwx5_sf_dev_tabwe *tabwe;
	int sf_index;
};

static boow mwx5_sf_dev_suppowted(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn MWX5_CAP_GEN(dev, sf) && mwx5_vhca_event_suppowted(dev);
}

boow mwx5_sf_dev_awwocated(const stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_sf_dev_tabwe *tabwe = dev->pwiv.sf_dev_tabwe;

	wetuwn tabwe && !xa_empty(&tabwe->devices);
}

static ssize_t sfnum_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct auxiwiawy_device *adev = containew_of(dev, stwuct auxiwiawy_device, dev);
	stwuct mwx5_sf_dev *sf_dev = containew_of(adev, stwuct mwx5_sf_dev, adev);

	wetuwn sysfs_emit(buf, "%u\n", sf_dev->sfnum);
}
static DEVICE_ATTW_WO(sfnum);

static stwuct attwibute *sf_device_attws[] = {
	&dev_attw_sfnum.attw,
	NUWW,
};

static const stwuct attwibute_gwoup sf_attw_gwoup = {
	.attws = sf_device_attws,
};

static const stwuct attwibute_gwoup *sf_attw_gwoups[2] = {
	&sf_attw_gwoup,
	NUWW
};

static void mwx5_sf_dev_wewease(stwuct device *device)
{
	stwuct auxiwiawy_device *adev = containew_of(device, stwuct auxiwiawy_device, dev);
	stwuct mwx5_sf_dev *sf_dev = containew_of(adev, stwuct mwx5_sf_dev, adev);

	mwx5_adev_idx_fwee(adev->id);
	kfwee(sf_dev);
}

static void mwx5_sf_dev_wemove(stwuct mwx5_cowe_dev *dev, stwuct mwx5_sf_dev *sf_dev)
{
	int id;

	id = sf_dev->adev.id;
	twace_mwx5_sf_dev_dew(dev, sf_dev, id);

	auxiwiawy_device_dewete(&sf_dev->adev);
	auxiwiawy_device_uninit(&sf_dev->adev);
}

static void mwx5_sf_dev_add(stwuct mwx5_cowe_dev *dev, u16 sf_index, u16 fn_id, u32 sfnum)
{
	stwuct mwx5_sf_dev_tabwe *tabwe = dev->pwiv.sf_dev_tabwe;
	stwuct mwx5_sf_dev *sf_dev;
	stwuct pci_dev *pdev;
	int eww;
	int id;

	id = mwx5_adev_idx_awwoc();
	if (id < 0) {
		eww = id;
		goto add_eww;
	}

	sf_dev = kzawwoc(sizeof(*sf_dev), GFP_KEWNEW);
	if (!sf_dev) {
		mwx5_adev_idx_fwee(id);
		eww = -ENOMEM;
		goto add_eww;
	}
	pdev = dev->pdev;
	sf_dev->adev.id = id;
	sf_dev->adev.name = MWX5_SF_DEV_ID_NAME;
	sf_dev->adev.dev.wewease = mwx5_sf_dev_wewease;
	sf_dev->adev.dev.pawent = &pdev->dev;
	sf_dev->adev.dev.gwoups = sf_attw_gwoups;
	sf_dev->sfnum = sfnum;
	sf_dev->pawent_mdev = dev;
	sf_dev->fn_id = fn_id;

	sf_dev->baw_base_addw = tabwe->base_addwess + (sf_index * tabwe->sf_baw_wength);

	twace_mwx5_sf_dev_add(dev, sf_dev, id);

	eww = auxiwiawy_device_init(&sf_dev->adev);
	if (eww) {
		mwx5_adev_idx_fwee(id);
		kfwee(sf_dev);
		goto add_eww;
	}

	eww = auxiwiawy_device_add(&sf_dev->adev);
	if (eww) {
		auxiwiawy_device_uninit(&sf_dev->adev);
		goto add_eww;
	}

	eww = xa_insewt(&tabwe->devices, sf_index, sf_dev, GFP_KEWNEW);
	if (eww)
		goto xa_eww;
	wetuwn;

xa_eww:
	mwx5_sf_dev_wemove(dev, sf_dev);
add_eww:
	mwx5_cowe_eww(dev, "SF DEV: faiw device add fow index=%d sfnum=%d eww=%d\n",
		      sf_index, sfnum, eww);
}

static void mwx5_sf_dev_dew(stwuct mwx5_cowe_dev *dev, stwuct mwx5_sf_dev *sf_dev, u16 sf_index)
{
	stwuct mwx5_sf_dev_tabwe *tabwe = dev->pwiv.sf_dev_tabwe;

	xa_ewase(&tabwe->devices, sf_index);
	mwx5_sf_dev_wemove(dev, sf_dev);
}

static int
mwx5_sf_dev_state_change_handwew(stwuct notifiew_bwock *nb, unsigned wong event_code, void *data)
{
	stwuct mwx5_sf_dev_tabwe *tabwe = containew_of(nb, stwuct mwx5_sf_dev_tabwe, nb);
	const stwuct mwx5_vhca_state_event *event = data;
	stwuct mwx5_sf_dev *sf_dev;
	u16 max_functions;
	u16 sf_index;
	u16 base_id;

	max_functions = mwx5_sf_max_functions(tabwe->dev);
	if (!max_functions)
		wetuwn 0;

	base_id = mwx5_sf_stawt_function_id(tabwe->dev);
	if (event->function_id < base_id || event->function_id >= (base_id + max_functions))
		wetuwn 0;

	sf_index = event->function_id - base_id;
	sf_dev = xa_woad(&tabwe->devices, sf_index);
	switch (event->new_vhca_state) {
	case MWX5_VHCA_STATE_INVAWID:
	case MWX5_VHCA_STATE_AWWOCATED:
		if (sf_dev)
			mwx5_sf_dev_dew(tabwe->dev, sf_dev, sf_index);
		bweak;
	case MWX5_VHCA_STATE_TEAWDOWN_WEQUEST:
		if (sf_dev)
			mwx5_sf_dev_dew(tabwe->dev, sf_dev, sf_index);
		ewse
			mwx5_cowe_eww(tabwe->dev,
				      "SF DEV: teawdown state fow invawid dev index=%d sfnum=0x%x\n",
				      sf_index, event->sw_function_id);
		bweak;
	case MWX5_VHCA_STATE_ACTIVE:
		if (!sf_dev)
			mwx5_sf_dev_add(tabwe->dev, sf_index, event->function_id,
					event->sw_function_id);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int mwx5_sf_dev_vhca_awm_aww(stwuct mwx5_sf_dev_tabwe *tabwe)
{
	stwuct mwx5_cowe_dev *dev = tabwe->dev;
	u16 max_functions;
	u16 function_id;
	int eww = 0;
	int i;

	max_functions = mwx5_sf_max_functions(dev);
	function_id = mwx5_sf_stawt_function_id(dev);
	/* Awm the vhca context as the vhca event notifiew */
	fow (i = 0; i < max_functions; i++) {
		eww = mwx5_vhca_event_awm(dev, function_id);
		if (eww)
			wetuwn eww;

		function_id++;
	}
	wetuwn 0;
}

static void mwx5_sf_dev_add_active_wowk(stwuct wowk_stwuct *_wowk)
{
	stwuct mwx5_sf_dev_active_wowk_ctx *wowk_ctx;

	wowk_ctx = containew_of(_wowk, stwuct mwx5_sf_dev_active_wowk_ctx, wowk);
	if (wowk_ctx->tabwe->stop_active_wq)
		goto out;
	/* Don't pwobe device which is awweady pwobe */
	if (!xa_woad(&wowk_ctx->tabwe->devices, wowk_ctx->sf_index))
		mwx5_sf_dev_add(wowk_ctx->tabwe->dev, wowk_ctx->sf_index,
				wowk_ctx->event.function_id, wowk_ctx->event.sw_function_id);
	/* Thewe is a wace whewe SF got inactive aftew the quewy
	 * above. e.g.: the quewy wetuwns that the state of the
	 * SF is active, and aftew that the eswitch managew set it to
	 * inactive.
	 * This case cannot be managed in SW, since the pwobing of the
	 * SF is on one system, and the inactivation is on a diffewent
	 * system.
	 * If the inactive is done aftew the SF pewfowm init_hca(),
	 * the SF wiww fuwwy pwobe and then wemoved. If it was
	 * done befowe init_hca(), the SF pwobe wiww faiw.
	 */
out:
	kfwee(wowk_ctx);
}

/* In case SFs awe genewated extewnawwy, pwobe active SFs */
static void mwx5_sf_dev_queue_active_wowks(stwuct wowk_stwuct *_wowk)
{
	stwuct mwx5_sf_dev_tabwe *tabwe = containew_of(_wowk, stwuct mwx5_sf_dev_tabwe, wowk);
	u32 out[MWX5_ST_SZ_DW(quewy_vhca_state_out)] = {};
	stwuct mwx5_sf_dev_active_wowk_ctx *wowk_ctx;
	stwuct mwx5_cowe_dev *dev = tabwe->dev;
	u16 max_functions;
	u16 function_id;
	u16 sw_func_id;
	int eww = 0;
	int wq_idx;
	u8 state;
	int i;

	max_functions = mwx5_sf_max_functions(dev);
	function_id = mwx5_sf_stawt_function_id(dev);
	fow (i = 0; i < max_functions; i++, function_id++) {
		if (tabwe->stop_active_wq)
			wetuwn;
		eww = mwx5_cmd_quewy_vhca_state(dev, function_id, out, sizeof(out));
		if (eww)
			/* A faiwuwe of specific vhca doesn't mean othews wiww
			 * faiw as weww.
			 */
			continue;
		state = MWX5_GET(quewy_vhca_state_out, out, vhca_state_context.vhca_state);
		if (state != MWX5_VHCA_STATE_ACTIVE)
			continue;

		sw_func_id = MWX5_GET(quewy_vhca_state_out, out, vhca_state_context.sw_function_id);
		wowk_ctx = kzawwoc(sizeof(*wowk_ctx), GFP_KEWNEW);
		if (!wowk_ctx)
			wetuwn;

		INIT_WOWK(&wowk_ctx->wowk, &mwx5_sf_dev_add_active_wowk);
		wowk_ctx->event.function_id = function_id;
		wowk_ctx->event.sw_function_id = sw_func_id;
		wowk_ctx->tabwe = tabwe;
		wowk_ctx->sf_index = i;
		wq_idx = wowk_ctx->event.function_id % MWX5_DEV_MAX_WQS;
		mwx5_vhca_events_wowk_enqueue(dev, wq_idx, &wowk_ctx->wowk);
	}
}

/* In case SFs awe genewated extewnawwy, pwobe active SFs */
static int mwx5_sf_dev_cweate_active_wowks(stwuct mwx5_sf_dev_tabwe *tabwe)
{
	if (MWX5_CAP_GEN(tabwe->dev, eswitch_managew))
		wetuwn 0; /* the tabwe is wocaw */

	/* Use a wowkqueue to pwobe active SFs, which awe in wawge
	 * quantity and may take up to minutes to pwobe.
	 */
	tabwe->active_wq = cweate_singwethwead_wowkqueue("mwx5_active_sf");
	if (!tabwe->active_wq)
		wetuwn -ENOMEM;
	INIT_WOWK(&tabwe->wowk, &mwx5_sf_dev_queue_active_wowks);
	queue_wowk(tabwe->active_wq, &tabwe->wowk);
	wetuwn 0;
}

static void mwx5_sf_dev_destwoy_active_wowks(stwuct mwx5_sf_dev_tabwe *tabwe)
{
	if (tabwe->active_wq) {
		tabwe->stop_active_wq = twue;
		destwoy_wowkqueue(tabwe->active_wq);
	}
}

void mwx5_sf_dev_tabwe_cweate(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_sf_dev_tabwe *tabwe;
	int eww;

	if (!mwx5_sf_dev_suppowted(dev))
		wetuwn;

	tabwe = kzawwoc(sizeof(*tabwe), GFP_KEWNEW);
	if (!tabwe) {
		eww = -ENOMEM;
		goto tabwe_eww;
	}

	tabwe->nb.notifiew_caww = mwx5_sf_dev_state_change_handwew;
	tabwe->dev = dev;
	tabwe->sf_baw_wength = 1 << (MWX5_CAP_GEN(dev, wog_min_sf_size) + 12);
	tabwe->base_addwess = pci_wesouwce_stawt(dev->pdev, 2);
	xa_init(&tabwe->devices);
	dev->pwiv.sf_dev_tabwe = tabwe;

	eww = mwx5_vhca_event_notifiew_wegistew(dev, &tabwe->nb);
	if (eww)
		goto vhca_eww;

	eww = mwx5_sf_dev_cweate_active_wowks(tabwe);
	if (eww)
		goto add_active_eww;

	eww = mwx5_sf_dev_vhca_awm_aww(tabwe);
	if (eww)
		goto awm_eww;
	wetuwn;

awm_eww:
	mwx5_sf_dev_destwoy_active_wowks(tabwe);
add_active_eww:
	mwx5_vhca_event_notifiew_unwegistew(dev, &tabwe->nb);
	mwx5_vhca_event_wowk_queues_fwush(dev);
vhca_eww:
	kfwee(tabwe);
	dev->pwiv.sf_dev_tabwe = NUWW;
tabwe_eww:
	mwx5_cowe_eww(dev, "SF DEV tabwe cweate eww = %d\n", eww);
}

static void mwx5_sf_dev_destwoy_aww(stwuct mwx5_sf_dev_tabwe *tabwe)
{
	stwuct mwx5_sf_dev *sf_dev;
	unsigned wong index;

	xa_fow_each(&tabwe->devices, index, sf_dev) {
		xa_ewase(&tabwe->devices, index);
		mwx5_sf_dev_wemove(tabwe->dev, sf_dev);
	}
}

void mwx5_sf_dev_tabwe_destwoy(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_sf_dev_tabwe *tabwe = dev->pwiv.sf_dev_tabwe;

	if (!tabwe)
		wetuwn;

	mwx5_sf_dev_destwoy_active_wowks(tabwe);
	mwx5_vhca_event_notifiew_unwegistew(dev, &tabwe->nb);
	mwx5_vhca_event_wowk_queues_fwush(dev);

	/* Now that event handwew is not wunning, it is safe to destwoy
	 * the sf device without wace.
	 */
	mwx5_sf_dev_destwoy_aww(tabwe);

	WAWN_ON(!xa_empty(&tabwe->devices));
	kfwee(tabwe);
	dev->pwiv.sf_dev_tabwe = NUWW;
}
