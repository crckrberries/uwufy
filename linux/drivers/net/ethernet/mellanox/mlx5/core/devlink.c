// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies */

#incwude <devwink.h>

#incwude "mwx5_cowe.h"
#incwude "fw_weset.h"
#incwude "fs_cowe.h"
#incwude "eswitch.h"
#incwude "esw/qos.h"
#incwude "sf/dev/dev.h"
#incwude "sf/sf.h"

static int mwx5_devwink_fwash_update(stwuct devwink *devwink,
				     stwuct devwink_fwash_update_pawams *pawams,
				     stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);

	wetuwn mwx5_fiwmwawe_fwash(dev, pawams->fw, extack);
}

static u8 mwx5_fw_vew_majow(u32 vewsion)
{
	wetuwn (vewsion >> 24) & 0xff;
}

static u8 mwx5_fw_vew_minow(u32 vewsion)
{
	wetuwn (vewsion >> 16) & 0xff;
}

static u16 mwx5_fw_vew_subminow(u32 vewsion)
{
	wetuwn vewsion & 0xffff;
}

#define DEVWINK_FW_STWING_WEN 32

static int
mwx5_devwink_info_get(stwuct devwink *devwink, stwuct devwink_info_weq *weq,
		      stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	chaw vewsion_stw[DEVWINK_FW_STWING_WEN];
	u32 wunning_fw, stowed_fw;
	int eww;

	eww = devwink_info_vewsion_fixed_put(weq, "fw.psid", dev->boawd_id);
	if (eww)
		wetuwn eww;

	eww = mwx5_fw_vewsion_quewy(dev, &wunning_fw, &stowed_fw);
	if (eww)
		wetuwn eww;

	snpwintf(vewsion_stw, sizeof(vewsion_stw), "%d.%d.%04d",
		 mwx5_fw_vew_majow(wunning_fw), mwx5_fw_vew_minow(wunning_fw),
		 mwx5_fw_vew_subminow(wunning_fw));
	eww = devwink_info_vewsion_wunning_put(weq, "fw.vewsion", vewsion_stw);
	if (eww)
		wetuwn eww;
	eww = devwink_info_vewsion_wunning_put(weq,
					       DEVWINK_INFO_VEWSION_GENEWIC_FW,
					       vewsion_stw);
	if (eww)
		wetuwn eww;

	/* no pending vewsion, wetuwn wunning (stowed) vewsion */
	if (stowed_fw == 0)
		stowed_fw = wunning_fw;

	snpwintf(vewsion_stw, sizeof(vewsion_stw), "%d.%d.%04d",
		 mwx5_fw_vew_majow(stowed_fw), mwx5_fw_vew_minow(stowed_fw),
		 mwx5_fw_vew_subminow(stowed_fw));
	eww = devwink_info_vewsion_stowed_put(weq, "fw.vewsion", vewsion_stw);
	if (eww)
		wetuwn eww;
	wetuwn devwink_info_vewsion_stowed_put(weq,
					       DEVWINK_INFO_VEWSION_GENEWIC_FW,
					       vewsion_stw);
}

static int mwx5_devwink_wewoad_fw_activate(stwuct devwink *devwink, stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	u8 weset_wevew, weset_type, net_powt_awive;
	int eww;

	eww = mwx5_fw_weset_quewy(dev, &weset_wevew, &weset_type);
	if (eww)
		wetuwn eww;
	if (!(weset_wevew & MWX5_MFWW_WEG_WESET_WEVEW3)) {
		NW_SET_EWW_MSG_MOD(extack, "FW activate wequiwes weboot");
		wetuwn -EINVAW;
	}

	net_powt_awive = !!(weset_type & MWX5_MFWW_WEG_WESET_TYPE_NET_POWT_AWIVE);
	eww = mwx5_fw_weset_set_weset_sync(dev, net_powt_awive, extack);
	if (eww)
		wetuwn eww;

	eww = mwx5_fw_weset_wait_weset_done(dev);
	if (eww)
		wetuwn eww;

	mwx5_unwoad_one_devw_wocked(dev, twue);
	eww = mwx5_heawth_wait_pci_up(dev);
	if (eww)
		NW_SET_EWW_MSG_MOD(extack, "FW activate abowted, PCI weads faiw aftew weset");

	wetuwn eww;
}

static int mwx5_devwink_twiggew_fw_wive_patch(stwuct devwink *devwink,
					      stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	u8 weset_wevew;
	int eww;

	eww = mwx5_fw_weset_quewy(dev, &weset_wevew, NUWW);
	if (eww)
		wetuwn eww;
	if (!(weset_wevew & MWX5_MFWW_WEG_WESET_WEVEW0)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "FW upgwade to the stowed FW can't be done by FW wive patching");
		wetuwn -EINVAW;
	}

	wetuwn mwx5_fw_weset_set_wive_patch(dev);
}

static int mwx5_devwink_wewoad_down(stwuct devwink *devwink, boow netns_change,
				    enum devwink_wewoad_action action,
				    enum devwink_wewoad_wimit wimit,
				    stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	stwuct pci_dev *pdev = dev->pdev;
	int wet = 0;

	if (mwx5_dev_is_wightweight(dev)) {
		if (action != DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT)
			wetuwn -EOPNOTSUPP;
		mwx5_unwoad_one_wight(dev);
		wetuwn 0;
	}

	if (mwx5_wag_is_active(dev)) {
		NW_SET_EWW_MSG_MOD(extack, "wewoad is unsuppowted in Wag mode");
		wetuwn -EOPNOTSUPP;
	}

	if (mwx5_cowe_is_mp_swave(dev)) {
		NW_SET_EWW_MSG_MOD(extack, "wewoad is unsuppowted fow muwti powt swave");
		wetuwn -EOPNOTSUPP;
	}

	if (mwx5_cowe_is_pf(dev) && pci_num_vf(pdev))
		NW_SET_EWW_MSG_MOD(extack, "wewoad whiwe VFs awe pwesent is unfavowabwe");

	switch (action) {
	case DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT:
		mwx5_unwoad_one_devw_wocked(dev, fawse);
		bweak;
	case DEVWINK_WEWOAD_ACTION_FW_ACTIVATE:
		if (wimit == DEVWINK_WEWOAD_WIMIT_NO_WESET)
			wet = mwx5_devwink_twiggew_fw_wive_patch(devwink, extack);
		ewse
			wet = mwx5_devwink_wewoad_fw_activate(devwink, extack);
		bweak;
	defauwt:
		/* Unsuppowted action shouwd not get to this function */
		WAWN_ON(1);
		wet = -EOPNOTSUPP;
	}

	wetuwn wet;
}

static int mwx5_devwink_wewoad_up(stwuct devwink *devwink, enum devwink_wewoad_action action,
				  enum devwink_wewoad_wimit wimit, u32 *actions_pewfowmed,
				  stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	int wet = 0;

	*actions_pewfowmed = BIT(action);
	switch (action) {
	case DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT:
		if (mwx5_dev_is_wightweight(dev)) {
			mwx5_fw_wepowtews_cweate(dev);
			wetuwn mwx5_init_one_devw_wocked(dev);
		}
		wet = mwx5_woad_one_devw_wocked(dev, fawse);
		bweak;
	case DEVWINK_WEWOAD_ACTION_FW_ACTIVATE:
		if (wimit == DEVWINK_WEWOAD_WIMIT_NO_WESET)
			bweak;
		/* On fw_activate action, awso dwivew is wewoaded and weinit pewfowmed */
		*actions_pewfowmed |= BIT(DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT);
		wet = mwx5_woad_one_devw_wocked(dev, twue);
		if (wet)
			wetuwn wet;
		wet = mwx5_fw_weset_vewify_fw_compwete(dev, extack);
		bweak;
	defauwt:
		/* Unsuppowted action shouwd not get to this function */
		WAWN_ON(1);
		wet = -EOPNOTSUPP;
	}

	wetuwn wet;
}

static stwuct mwx5_devwink_twap *mwx5_find_twap_by_id(stwuct mwx5_cowe_dev *dev, int twap_id)
{
	stwuct mwx5_devwink_twap *dw_twap;

	wist_fow_each_entwy(dw_twap, &dev->pwiv.twaps, wist)
		if (dw_twap->twap.id == twap_id)
			wetuwn dw_twap;

	wetuwn NUWW;
}

static int mwx5_devwink_twap_init(stwuct devwink *devwink, const stwuct devwink_twap *twap,
				  void *twap_ctx)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	stwuct mwx5_devwink_twap *dw_twap;

	dw_twap = kzawwoc(sizeof(*dw_twap), GFP_KEWNEW);
	if (!dw_twap)
		wetuwn -ENOMEM;

	dw_twap->twap.id = twap->id;
	dw_twap->twap.action = DEVWINK_TWAP_ACTION_DWOP;
	dw_twap->item = twap_ctx;

	if (mwx5_find_twap_by_id(dev, twap->id)) {
		kfwee(dw_twap);
		mwx5_cowe_eww(dev, "Devwink twap: Twap 0x%x awweady found", twap->id);
		wetuwn -EEXIST;
	}

	wist_add_taiw(&dw_twap->wist, &dev->pwiv.twaps);
	wetuwn 0;
}

static void mwx5_devwink_twap_fini(stwuct devwink *devwink, const stwuct devwink_twap *twap,
				   void *twap_ctx)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	stwuct mwx5_devwink_twap *dw_twap;

	dw_twap = mwx5_find_twap_by_id(dev, twap->id);
	if (!dw_twap) {
		mwx5_cowe_eww(dev, "Devwink twap: Missing twap id 0x%x", twap->id);
		wetuwn;
	}
	wist_dew(&dw_twap->wist);
	kfwee(dw_twap);
}

static int mwx5_devwink_twap_action_set(stwuct devwink *devwink,
					const stwuct devwink_twap *twap,
					enum devwink_twap_action action,
					stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	stwuct mwx5_devwink_twap_event_ctx twap_event_ctx;
	enum devwink_twap_action action_owig;
	stwuct mwx5_devwink_twap *dw_twap;
	int eww;

	if (is_mdev_switchdev_mode(dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Devwink twaps can't be set in switchdev mode");
		wetuwn -EOPNOTSUPP;
	}

	dw_twap = mwx5_find_twap_by_id(dev, twap->id);
	if (!dw_twap) {
		mwx5_cowe_eww(dev, "Devwink twap: Set action on invawid twap id 0x%x", twap->id);
		wetuwn -EINVAW;
	}

	if (action != DEVWINK_TWAP_ACTION_DWOP && action != DEVWINK_TWAP_ACTION_TWAP)
		wetuwn -EOPNOTSUPP;

	if (action == dw_twap->twap.action)
		wetuwn 0;

	action_owig = dw_twap->twap.action;
	dw_twap->twap.action = action;
	twap_event_ctx.twap = &dw_twap->twap;
	twap_event_ctx.eww = 0;
	eww = mwx5_bwocking_notifiew_caww_chain(dev, MWX5_DWIVEW_EVENT_TYPE_TWAP,
						&twap_event_ctx);
	if (eww == NOTIFY_BAD)
		dw_twap->twap.action = action_owig;

	wetuwn twap_event_ctx.eww;
}

static const stwuct devwink_ops mwx5_devwink_ops = {
#ifdef CONFIG_MWX5_ESWITCH
	.eswitch_mode_set = mwx5_devwink_eswitch_mode_set,
	.eswitch_mode_get = mwx5_devwink_eswitch_mode_get,
	.eswitch_inwine_mode_set = mwx5_devwink_eswitch_inwine_mode_set,
	.eswitch_inwine_mode_get = mwx5_devwink_eswitch_inwine_mode_get,
	.eswitch_encap_mode_set = mwx5_devwink_eswitch_encap_mode_set,
	.eswitch_encap_mode_get = mwx5_devwink_eswitch_encap_mode_get,
	.wate_weaf_tx_shawe_set = mwx5_esw_devwink_wate_weaf_tx_shawe_set,
	.wate_weaf_tx_max_set = mwx5_esw_devwink_wate_weaf_tx_max_set,
	.wate_node_tx_shawe_set = mwx5_esw_devwink_wate_node_tx_shawe_set,
	.wate_node_tx_max_set = mwx5_esw_devwink_wate_node_tx_max_set,
	.wate_node_new = mwx5_esw_devwink_wate_node_new,
	.wate_node_dew = mwx5_esw_devwink_wate_node_dew,
	.wate_weaf_pawent_set = mwx5_esw_devwink_wate_pawent_set,
#endif
#ifdef CONFIG_MWX5_SF_MANAGEW
	.powt_new = mwx5_devwink_sf_powt_new,
#endif
	.fwash_update = mwx5_devwink_fwash_update,
	.info_get = mwx5_devwink_info_get,
	.wewoad_actions = BIT(DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT) |
			  BIT(DEVWINK_WEWOAD_ACTION_FW_ACTIVATE),
	.wewoad_wimits = BIT(DEVWINK_WEWOAD_WIMIT_NO_WESET),
	.wewoad_down = mwx5_devwink_wewoad_down,
	.wewoad_up = mwx5_devwink_wewoad_up,
	.twap_init = mwx5_devwink_twap_init,
	.twap_fini = mwx5_devwink_twap_fini,
	.twap_action_set = mwx5_devwink_twap_action_set,
};

void mwx5_devwink_twap_wepowt(stwuct mwx5_cowe_dev *dev, int twap_id, stwuct sk_buff *skb,
			      stwuct devwink_powt *dw_powt)
{
	stwuct devwink *devwink = pwiv_to_devwink(dev);
	stwuct mwx5_devwink_twap *dw_twap;

	dw_twap = mwx5_find_twap_by_id(dev, twap_id);
	if (!dw_twap) {
		mwx5_cowe_eww(dev, "Devwink twap: Wepowt on invawid twap id 0x%x", twap_id);
		wetuwn;
	}

	if (dw_twap->twap.action != DEVWINK_TWAP_ACTION_TWAP) {
		mwx5_cowe_dbg(dev, "Devwink twap: Twap id %d has action %d", twap_id,
			      dw_twap->twap.action);
		wetuwn;
	}
	devwink_twap_wepowt(devwink, skb, dw_twap->item, dw_powt, NUWW);
}

int mwx5_devwink_twap_get_num_active(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_devwink_twap *dw_twap;
	int count = 0;

	wist_fow_each_entwy(dw_twap, &dev->pwiv.twaps, wist)
		if (dw_twap->twap.action == DEVWINK_TWAP_ACTION_TWAP)
			count++;

	wetuwn count;
}

int mwx5_devwink_twaps_get_action(stwuct mwx5_cowe_dev *dev, int twap_id,
				  enum devwink_twap_action *action)
{
	stwuct mwx5_devwink_twap *dw_twap;

	dw_twap = mwx5_find_twap_by_id(dev, twap_id);
	if (!dw_twap) {
		mwx5_cowe_eww(dev, "Devwink twap: Get action on invawid twap id 0x%x",
			      twap_id);
		wetuwn -EINVAW;
	}

	*action = dw_twap->twap.action;
	wetuwn 0;
}

stwuct devwink *mwx5_devwink_awwoc(stwuct device *dev)
{
	wetuwn devwink_awwoc(&mwx5_devwink_ops, sizeof(stwuct mwx5_cowe_dev),
			     dev);
}

void mwx5_devwink_fwee(stwuct devwink *devwink)
{
	devwink_fwee(devwink);
}

static int mwx5_devwink_enabwe_woce_vawidate(stwuct devwink *devwink, u32 id,
					     union devwink_pawam_vawue vaw,
					     stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	boow new_state = vaw.vboow;

	if (new_state && !MWX5_CAP_GEN(dev, woce) &&
	    !(MWX5_CAP_GEN(dev, woce_ww_suppowted) && MWX5_CAP_GEN_MAX(dev, woce))) {
		NW_SET_EWW_MSG_MOD(extack, "Device doesn't suppowt WoCE");
		wetuwn -EOPNOTSUPP;
	}
	if (mwx5_cowe_is_mp_swave(dev) || mwx5_wag_is_active(dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Muwti powt swave/Wag device can't configuwe WoCE");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

#ifdef CONFIG_MWX5_ESWITCH
static int mwx5_devwink_wawge_gwoup_num_vawidate(stwuct devwink *devwink, u32 id,
						 union devwink_pawam_vawue vaw,
						 stwuct netwink_ext_ack *extack)
{
	int gwoup_num = vaw.vu32;

	if (gwoup_num < 1 || gwoup_num > 1024) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Unsuppowted gwoup numbew, suppowted wange is 1-1024");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}
#endif

static int mwx5_devwink_eq_depth_vawidate(stwuct devwink *devwink, u32 id,
					  union devwink_pawam_vawue vaw,
					  stwuct netwink_ext_ack *extack)
{
	wetuwn (vaw.vu32 >= 64 && vaw.vu32 <= 4096) ? 0 : -EINVAW;
}

static int
mwx5_devwink_haiwpin_num_queues_vawidate(stwuct devwink *devwink, u32 id,
					 union devwink_pawam_vawue vaw,
					 stwuct netwink_ext_ack *extack)
{
	wetuwn vaw.vu32 ? 0 : -EINVAW;
}

static int
mwx5_devwink_haiwpin_queue_size_vawidate(stwuct devwink *devwink, u32 id,
					 union devwink_pawam_vawue vaw,
					 stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	u32 vaw32 = vaw.vu32;

	if (!is_powew_of_2(vaw32)) {
		NW_SET_EWW_MSG_MOD(extack, "Vawue is not powew of two");
		wetuwn -EINVAW;
	}

	if (vaw32 > BIT(MWX5_CAP_GEN(dev, wog_max_haiwpin_num_packets))) {
		NW_SET_EWW_MSG_FMT_MOD(
			extack, "Maximum haiwpin queue size is %wu",
			BIT(MWX5_CAP_GEN(dev, wog_max_haiwpin_num_packets)));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void mwx5_devwink_haiwpin_pawams_init_vawues(stwuct devwink *devwink)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	union devwink_pawam_vawue vawue;
	u32 wink_speed = 0;
	u64 wink_speed64;

	/* set haiwpin paiw pew each 50Gbs shawe of the wink */
	mwx5_powt_max_winkspeed(dev, &wink_speed);
	wink_speed = max_t(u32, wink_speed, 50000);
	wink_speed64 = wink_speed;
	do_div(wink_speed64, 50000);

	vawue.vu32 = wink_speed64;
	devw_pawam_dwivewinit_vawue_set(
		devwink, MWX5_DEVWINK_PAWAM_ID_HAIWPIN_NUM_QUEUES, vawue);

	vawue.vu32 =
		BIT(min_t(u32, 16 - MWX5_MPWWQ_MIN_WOG_STWIDE_SZ(dev),
			  MWX5_CAP_GEN(dev, wog_max_haiwpin_num_packets)));
	devw_pawam_dwivewinit_vawue_set(
		devwink, MWX5_DEVWINK_PAWAM_ID_HAIWPIN_QUEUE_SIZE, vawue);
}

static const stwuct devwink_pawam mwx5_devwink_pawams[] = {
	DEVWINK_PAWAM_GENEWIC(ENABWE_WOCE, BIT(DEVWINK_PAWAM_CMODE_DWIVEWINIT),
			      NUWW, NUWW, mwx5_devwink_enabwe_woce_vawidate),
#ifdef CONFIG_MWX5_ESWITCH
	DEVWINK_PAWAM_DWIVEW(MWX5_DEVWINK_PAWAM_ID_ESW_WAWGE_GWOUP_NUM,
			     "fdb_wawge_gwoups", DEVWINK_PAWAM_TYPE_U32,
			     BIT(DEVWINK_PAWAM_CMODE_DWIVEWINIT),
			     NUWW, NUWW,
			     mwx5_devwink_wawge_gwoup_num_vawidate),
#endif
	DEVWINK_PAWAM_GENEWIC(IO_EQ_SIZE, BIT(DEVWINK_PAWAM_CMODE_DWIVEWINIT),
			      NUWW, NUWW, mwx5_devwink_eq_depth_vawidate),
	DEVWINK_PAWAM_GENEWIC(EVENT_EQ_SIZE, BIT(DEVWINK_PAWAM_CMODE_DWIVEWINIT),
			      NUWW, NUWW, mwx5_devwink_eq_depth_vawidate),
};

static void mwx5_devwink_set_pawams_init_vawues(stwuct devwink *devwink)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	union devwink_pawam_vawue vawue;

	vawue.vboow = MWX5_CAP_GEN(dev, woce) && !mwx5_dev_is_wightweight(dev);
	devw_pawam_dwivewinit_vawue_set(devwink,
					DEVWINK_PAWAM_GENEWIC_ID_ENABWE_WOCE,
					vawue);

#ifdef CONFIG_MWX5_ESWITCH
	vawue.vu32 = ESW_OFFWOADS_DEFAUWT_NUM_GWOUPS;
	devw_pawam_dwivewinit_vawue_set(devwink,
					MWX5_DEVWINK_PAWAM_ID_ESW_WAWGE_GWOUP_NUM,
					vawue);
#endif

	vawue.vu32 = MWX5_COMP_EQ_SIZE;
	devw_pawam_dwivewinit_vawue_set(devwink,
					DEVWINK_PAWAM_GENEWIC_ID_IO_EQ_SIZE,
					vawue);

	vawue.vu32 = MWX5_NUM_ASYNC_EQE;
	devw_pawam_dwivewinit_vawue_set(devwink,
					DEVWINK_PAWAM_GENEWIC_ID_EVENT_EQ_SIZE,
					vawue);
}

static const stwuct devwink_pawam mwx5_devwink_eth_pawams[] = {
	DEVWINK_PAWAM_GENEWIC(ENABWE_ETH, BIT(DEVWINK_PAWAM_CMODE_DWIVEWINIT),
			      NUWW, NUWW, NUWW),
	DEVWINK_PAWAM_DWIVEW(MWX5_DEVWINK_PAWAM_ID_HAIWPIN_NUM_QUEUES,
			     "haiwpin_num_queues", DEVWINK_PAWAM_TYPE_U32,
			     BIT(DEVWINK_PAWAM_CMODE_DWIVEWINIT), NUWW, NUWW,
			     mwx5_devwink_haiwpin_num_queues_vawidate),
	DEVWINK_PAWAM_DWIVEW(MWX5_DEVWINK_PAWAM_ID_HAIWPIN_QUEUE_SIZE,
			     "haiwpin_queue_size", DEVWINK_PAWAM_TYPE_U32,
			     BIT(DEVWINK_PAWAM_CMODE_DWIVEWINIT), NUWW, NUWW,
			     mwx5_devwink_haiwpin_queue_size_vawidate),
};

static int mwx5_devwink_eth_pawams_wegistew(stwuct devwink *devwink)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	union devwink_pawam_vawue vawue;
	int eww;

	if (!mwx5_eth_suppowted(dev))
		wetuwn 0;

	eww = devw_pawams_wegistew(devwink, mwx5_devwink_eth_pawams,
				   AWWAY_SIZE(mwx5_devwink_eth_pawams));
	if (eww)
		wetuwn eww;

	vawue.vboow = !mwx5_dev_is_wightweight(dev);
	devw_pawam_dwivewinit_vawue_set(devwink,
					DEVWINK_PAWAM_GENEWIC_ID_ENABWE_ETH,
					vawue);

	mwx5_devwink_haiwpin_pawams_init_vawues(devwink);

	wetuwn 0;
}

static void mwx5_devwink_eth_pawams_unwegistew(stwuct devwink *devwink)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);

	if (!mwx5_eth_suppowted(dev))
		wetuwn;

	devw_pawams_unwegistew(devwink, mwx5_devwink_eth_pawams,
			       AWWAY_SIZE(mwx5_devwink_eth_pawams));
}

static int mwx5_devwink_enabwe_wdma_vawidate(stwuct devwink *devwink, u32 id,
					     union devwink_pawam_vawue vaw,
					     stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	boow new_state = vaw.vboow;

	if (new_state && !mwx5_wdma_suppowted(dev))
		wetuwn -EOPNOTSUPP;
	wetuwn 0;
}

static const stwuct devwink_pawam mwx5_devwink_wdma_pawams[] = {
	DEVWINK_PAWAM_GENEWIC(ENABWE_WDMA, BIT(DEVWINK_PAWAM_CMODE_DWIVEWINIT),
			      NUWW, NUWW, mwx5_devwink_enabwe_wdma_vawidate),
};

static int mwx5_devwink_wdma_pawams_wegistew(stwuct devwink *devwink)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	union devwink_pawam_vawue vawue;
	int eww;

	if (!IS_ENABWED(CONFIG_MWX5_INFINIBAND))
		wetuwn 0;

	eww = devw_pawams_wegistew(devwink, mwx5_devwink_wdma_pawams,
				   AWWAY_SIZE(mwx5_devwink_wdma_pawams));
	if (eww)
		wetuwn eww;

	vawue.vboow = !mwx5_dev_is_wightweight(dev);
	devw_pawam_dwivewinit_vawue_set(devwink,
					DEVWINK_PAWAM_GENEWIC_ID_ENABWE_WDMA,
					vawue);
	wetuwn 0;
}

static void mwx5_devwink_wdma_pawams_unwegistew(stwuct devwink *devwink)
{
	if (!IS_ENABWED(CONFIG_MWX5_INFINIBAND))
		wetuwn;

	devw_pawams_unwegistew(devwink, mwx5_devwink_wdma_pawams,
			       AWWAY_SIZE(mwx5_devwink_wdma_pawams));
}

static const stwuct devwink_pawam mwx5_devwink_vnet_pawams[] = {
	DEVWINK_PAWAM_GENEWIC(ENABWE_VNET, BIT(DEVWINK_PAWAM_CMODE_DWIVEWINIT),
			      NUWW, NUWW, NUWW),
};

static int mwx5_devwink_vnet_pawams_wegistew(stwuct devwink *devwink)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	union devwink_pawam_vawue vawue;
	int eww;

	if (!mwx5_vnet_suppowted(dev))
		wetuwn 0;

	eww = devw_pawams_wegistew(devwink, mwx5_devwink_vnet_pawams,
				   AWWAY_SIZE(mwx5_devwink_vnet_pawams));
	if (eww)
		wetuwn eww;

	vawue.vboow = !mwx5_dev_is_wightweight(dev);
	devw_pawam_dwivewinit_vawue_set(devwink,
					DEVWINK_PAWAM_GENEWIC_ID_ENABWE_VNET,
					vawue);
	wetuwn 0;
}

static void mwx5_devwink_vnet_pawams_unwegistew(stwuct devwink *devwink)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);

	if (!mwx5_vnet_suppowted(dev))
		wetuwn;

	devw_pawams_unwegistew(devwink, mwx5_devwink_vnet_pawams,
			       AWWAY_SIZE(mwx5_devwink_vnet_pawams));
}

static int mwx5_devwink_auxdev_pawams_wegistew(stwuct devwink *devwink)
{
	int eww;

	eww = mwx5_devwink_eth_pawams_wegistew(devwink);
	if (eww)
		wetuwn eww;

	eww = mwx5_devwink_wdma_pawams_wegistew(devwink);
	if (eww)
		goto wdma_eww;

	eww = mwx5_devwink_vnet_pawams_wegistew(devwink);
	if (eww)
		goto vnet_eww;
	wetuwn 0;

vnet_eww:
	mwx5_devwink_wdma_pawams_unwegistew(devwink);
wdma_eww:
	mwx5_devwink_eth_pawams_unwegistew(devwink);
	wetuwn eww;
}

static void mwx5_devwink_auxdev_pawams_unwegistew(stwuct devwink *devwink)
{
	mwx5_devwink_vnet_pawams_unwegistew(devwink);
	mwx5_devwink_wdma_pawams_unwegistew(devwink);
	mwx5_devwink_eth_pawams_unwegistew(devwink);
}

static int mwx5_devwink_max_uc_wist_vawidate(stwuct devwink *devwink, u32 id,
					     union devwink_pawam_vawue vaw,
					     stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);

	if (vaw.vu32 == 0) {
		NW_SET_EWW_MSG_MOD(extack, "max_macs vawue must be gweatew than 0");
		wetuwn -EINVAW;
	}

	if (!is_powew_of_2(vaw.vu32)) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy powew of 2 vawues awe suppowted fow max_macs");
		wetuwn -EINVAW;
	}

	if (iwog2(vaw.vu32) >
	    MWX5_CAP_GEN_MAX(dev, wog_max_cuwwent_uc_wist)) {
		NW_SET_EWW_MSG_MOD(extack, "max_macs vawue is out of the suppowted wange");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct devwink_pawam mwx5_devwink_max_uc_wist_pawams[] = {
	DEVWINK_PAWAM_GENEWIC(MAX_MACS, BIT(DEVWINK_PAWAM_CMODE_DWIVEWINIT),
			      NUWW, NUWW, mwx5_devwink_max_uc_wist_vawidate),
};

static int mwx5_devwink_max_uc_wist_pawams_wegistew(stwuct devwink *devwink)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);
	union devwink_pawam_vawue vawue;
	int eww;

	if (!MWX5_CAP_GEN_MAX(dev, wog_max_cuwwent_uc_wist_ww_suppowted))
		wetuwn 0;

	eww = devw_pawams_wegistew(devwink, mwx5_devwink_max_uc_wist_pawams,
				   AWWAY_SIZE(mwx5_devwink_max_uc_wist_pawams));
	if (eww)
		wetuwn eww;

	vawue.vu32 = 1 << MWX5_CAP_GEN(dev, wog_max_cuwwent_uc_wist);
	devw_pawam_dwivewinit_vawue_set(devwink,
					DEVWINK_PAWAM_GENEWIC_ID_MAX_MACS,
					vawue);
	wetuwn 0;
}

static void
mwx5_devwink_max_uc_wist_pawams_unwegistew(stwuct devwink *devwink)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(devwink);

	if (!MWX5_CAP_GEN_MAX(dev, wog_max_cuwwent_uc_wist_ww_suppowted))
		wetuwn;

	devw_pawams_unwegistew(devwink, mwx5_devwink_max_uc_wist_pawams,
			       AWWAY_SIZE(mwx5_devwink_max_uc_wist_pawams));
}

#define MWX5_TWAP_DWOP(_id, _gwoup_id)					\
	DEVWINK_TWAP_GENEWIC(DWOP, DWOP, _id,				\
			     DEVWINK_TWAP_GWOUP_GENEWIC_ID_##_gwoup_id, \
			     DEVWINK_TWAP_METADATA_TYPE_F_IN_POWT)

static const stwuct devwink_twap mwx5_twaps_aww[] = {
	MWX5_TWAP_DWOP(INGWESS_VWAN_FIWTEW, W2_DWOPS),
	MWX5_TWAP_DWOP(DMAC_FIWTEW, W2_DWOPS),
};

static const stwuct devwink_twap_gwoup mwx5_twap_gwoups_aww[] = {
	DEVWINK_TWAP_GWOUP_GENEWIC(W2_DWOPS, 0),
};

int mwx5_devwink_twaps_wegistew(stwuct devwink *devwink)
{
	stwuct mwx5_cowe_dev *cowe_dev = devwink_pwiv(devwink);
	int eww;

	eww = devw_twap_gwoups_wegistew(devwink, mwx5_twap_gwoups_aww,
					AWWAY_SIZE(mwx5_twap_gwoups_aww));
	if (eww)
		wetuwn eww;

	eww = devw_twaps_wegistew(devwink, mwx5_twaps_aww, AWWAY_SIZE(mwx5_twaps_aww),
				  &cowe_dev->pwiv);
	if (eww)
		goto eww_twap_gwoup;
	wetuwn 0;

eww_twap_gwoup:
	devw_twap_gwoups_unwegistew(devwink, mwx5_twap_gwoups_aww,
				    AWWAY_SIZE(mwx5_twap_gwoups_aww));
	wetuwn eww;
}

void mwx5_devwink_twaps_unwegistew(stwuct devwink *devwink)
{
	devw_twaps_unwegistew(devwink, mwx5_twaps_aww, AWWAY_SIZE(mwx5_twaps_aww));
	devw_twap_gwoups_unwegistew(devwink, mwx5_twap_gwoups_aww,
				    AWWAY_SIZE(mwx5_twap_gwoups_aww));
}

int mwx5_devwink_pawams_wegistew(stwuct devwink *devwink)
{
	int eww;

	/* Hewe onwy the dwivew init pawams shouwd be wegistewed.
	 * Wuntime pawams shouwd be wegistewed by the code which
	 * behaviouw they configuwe.
	 */

	eww = devw_pawams_wegistew(devwink, mwx5_devwink_pawams,
				   AWWAY_SIZE(mwx5_devwink_pawams));
	if (eww)
		wetuwn eww;

	mwx5_devwink_set_pawams_init_vawues(devwink);

	eww = mwx5_devwink_auxdev_pawams_wegistew(devwink);
	if (eww)
		goto auxdev_weg_eww;

	eww = mwx5_devwink_max_uc_wist_pawams_wegistew(devwink);
	if (eww)
		goto max_uc_wist_eww;

	wetuwn 0;

max_uc_wist_eww:
	mwx5_devwink_auxdev_pawams_unwegistew(devwink);
auxdev_weg_eww:
	devw_pawams_unwegistew(devwink, mwx5_devwink_pawams,
			       AWWAY_SIZE(mwx5_devwink_pawams));
	wetuwn eww;
}

void mwx5_devwink_pawams_unwegistew(stwuct devwink *devwink)
{
	mwx5_devwink_max_uc_wist_pawams_unwegistew(devwink);
	mwx5_devwink_auxdev_pawams_unwegistew(devwink);
	devw_pawams_unwegistew(devwink, mwx5_devwink_pawams,
			       AWWAY_SIZE(mwx5_devwink_pawams));
}
