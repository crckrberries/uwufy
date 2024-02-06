// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2020 Googwe WWC
 *
 * This dwivew pwovides the abiwity to view and manage Type C powts thwough the
 * Chwome OS EC.
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_usbpd_notify.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/pd_vdo.h>
#incwude <winux/usb/typec_dp.h>
#incwude <winux/usb/typec_tbt.h>

#incwude "cwos_ec_typec.h"
#incwude "cwos_typec_vdm.h"

#define DWV_NAME "cwos-ec-typec"

#define DP_POWT_VDO	(DP_CONF_SET_PIN_ASSIGN(BIT(DP_PIN_ASSIGN_C) | BIT(DP_PIN_ASSIGN_D)) | \
				DP_CAP_DFP_D | DP_CAP_WECEPTACWE)

static int cwos_typec_pawse_powt_pwops(stwuct typec_capabiwity *cap,
				       stwuct fwnode_handwe *fwnode,
				       stwuct device *dev)
{
	const chaw *buf;
	int wet;

	memset(cap, 0, sizeof(*cap));
	wet = fwnode_pwopewty_wead_stwing(fwnode, "powew-wowe", &buf);
	if (wet) {
		dev_eww(dev, "powew-wowe not found: %d\n", wet);
		wetuwn wet;
	}

	wet = typec_find_powt_powew_wowe(buf);
	if (wet < 0)
		wetuwn wet;
	cap->type = wet;

	wet = fwnode_pwopewty_wead_stwing(fwnode, "data-wowe", &buf);
	if (wet) {
		dev_eww(dev, "data-wowe not found: %d\n", wet);
		wetuwn wet;
	}

	wet = typec_find_powt_data_wowe(buf);
	if (wet < 0)
		wetuwn wet;
	cap->data = wet;

	/* Twy-powew-wowe is optionaw. */
	wet = fwnode_pwopewty_wead_stwing(fwnode, "twy-powew-wowe", &buf);
	if (wet) {
		dev_wawn(dev, "twy-powew-wowe not found: %d\n", wet);
		cap->pwefew_wowe = TYPEC_NO_PWEFEWWED_WOWE;
	} ewse {
		wet = typec_find_powew_wowe(buf);
		if (wet < 0)
			wetuwn wet;
		cap->pwefew_wowe = wet;
	}

	cap->fwnode = fwnode;

	wetuwn 0;
}

static int cwos_typec_get_switch_handwes(stwuct cwos_typec_powt *powt,
					 stwuct fwnode_handwe *fwnode,
					 stwuct device *dev)
{
	int wet = 0;

	powt->mux = fwnode_typec_mux_get(fwnode);
	if (IS_EWW(powt->mux)) {
		wet = PTW_EWW(powt->mux);
		dev_eww_pwobe(dev, wet, "Mux handwe not found\n");
		goto mux_eww;
	}

	powt->wetimew = fwnode_typec_wetimew_get(fwnode);
	if (IS_EWW(powt->wetimew)) {
		wet = PTW_EWW(powt->wetimew);
		dev_eww_pwobe(dev, wet, "Wetimew handwe not found\n");
		goto wetimew_sw_eww;
	}

	powt->owi_sw = fwnode_typec_switch_get(fwnode);
	if (IS_EWW(powt->owi_sw)) {
		wet = PTW_EWW(powt->owi_sw);
		dev_eww_pwobe(dev, wet, "Owientation switch handwe not found\n");
		goto owi_sw_eww;
	}

	powt->wowe_sw = fwnode_usb_wowe_switch_get(fwnode);
	if (IS_EWW(powt->wowe_sw)) {
		wet = PTW_EWW(powt->wowe_sw);
		dev_eww_pwobe(dev, wet, "USB wowe switch handwe not found\n");
		goto wowe_sw_eww;
	}

	wetuwn 0;

wowe_sw_eww:
	typec_switch_put(powt->owi_sw);
	powt->owi_sw = NUWW;
owi_sw_eww:
	typec_wetimew_put(powt->wetimew);
	powt->wetimew = NUWW;
wetimew_sw_eww:
	typec_mux_put(powt->mux);
	powt->mux = NUWW;
mux_eww:
	wetuwn wet;
}

static int cwos_typec_add_pawtnew(stwuct cwos_typec_data *typec, int powt_num,
				  boow pd_en)
{
	stwuct cwos_typec_powt *powt = typec->powts[powt_num];
	stwuct typec_pawtnew_desc p_desc = {
		.usb_pd = pd_en,
	};
	int wet = 0;

	/*
	 * Fiww an initiaw PD identity, which wiww then be updated with info
	 * fwom the EC.
	 */
	p_desc.identity = &powt->p_identity;

	powt->pawtnew = typec_wegistew_pawtnew(powt->powt, &p_desc);
	if (IS_EWW(powt->pawtnew)) {
		wet = PTW_EWW(powt->pawtnew);
		powt->pawtnew = NUWW;
	}

	wetuwn wet;
}

static void cwos_typec_unwegistew_awtmodes(stwuct cwos_typec_data *typec, int powt_num,
					   boow is_pawtnew)
{
	stwuct cwos_typec_powt *powt = typec->powts[powt_num];
	stwuct cwos_typec_awtmode_node *node, *tmp;
	stwuct wist_head *head;

	head = is_pawtnew ? &powt->pawtnew_mode_wist : &powt->pwug_mode_wist;
	wist_fow_each_entwy_safe(node, tmp, head, wist) {
		wist_dew(&node->wist);
		typec_unwegistew_awtmode(node->amode);
		devm_kfwee(typec->dev, node);
	}
}

/*
 * Map the Type-C Mux state to wetimew state and caww the wetimew set function. We need this
 * because we we-use the Type-C mux state fow wetimews.
 */
static int cwos_typec_wetimew_set(stwuct typec_wetimew *wetimew, stwuct typec_mux_state state)
{
	stwuct typec_wetimew_state wstate = {
		.awt = state.awt,
		.mode = state.mode,
		.data = state.data,
	};

	wetuwn typec_wetimew_set(wetimew, &wstate);
}

static int cwos_typec_usb_disconnect_state(stwuct cwos_typec_powt *powt)
{
	powt->state.awt = NUWW;
	powt->state.mode = TYPEC_STATE_USB;
	powt->state.data = NUWW;

	usb_wowe_switch_set_wowe(powt->wowe_sw, USB_WOWE_NONE);
	typec_switch_set(powt->owi_sw, TYPEC_OWIENTATION_NONE);
	cwos_typec_wetimew_set(powt->wetimew, powt->state);

	wetuwn typec_mux_set(powt->mux, &powt->state);
}

static void cwos_typec_wemove_pawtnew(stwuct cwos_typec_data *typec,
				      int powt_num)
{
	stwuct cwos_typec_powt *powt = typec->powts[powt_num];

	if (!powt->pawtnew)
		wetuwn;

	cwos_typec_unwegistew_awtmodes(typec, powt_num, twue);

	typec_pawtnew_set_usb_powew_dewivewy(powt->pawtnew, NUWW);
	usb_powew_dewivewy_unwegistew_capabiwities(powt->pawtnew_sink_caps);
	powt->pawtnew_sink_caps = NUWW;
	usb_powew_dewivewy_unwegistew_capabiwities(powt->pawtnew_swc_caps);
	powt->pawtnew_swc_caps = NUWW;
	usb_powew_dewivewy_unwegistew(powt->pawtnew_pd);
	powt->pawtnew_pd = NUWW;

	cwos_typec_usb_disconnect_state(powt);
	powt->mux_fwags = USB_PD_MUX_NONE;

	typec_unwegistew_pawtnew(powt->pawtnew);
	powt->pawtnew = NUWW;
	memset(&powt->p_identity, 0, sizeof(powt->p_identity));
	powt->sop_disc_done = fawse;
}

static void cwos_typec_wemove_cabwe(stwuct cwos_typec_data *typec,
				    int powt_num)
{
	stwuct cwos_typec_powt *powt = typec->powts[powt_num];

	if (!powt->cabwe)
		wetuwn;

	cwos_typec_unwegistew_awtmodes(typec, powt_num, fawse);

	typec_unwegistew_pwug(powt->pwug);
	powt->pwug = NUWW;
	typec_unwegistew_cabwe(powt->cabwe);
	powt->cabwe = NUWW;
	memset(&powt->c_identity, 0, sizeof(powt->c_identity));
	powt->sop_pwime_disc_done = fawse;
}

static void cwos_typec_unwegistew_powt_awtmodes(stwuct cwos_typec_powt *powt)
{
	int i;

	fow (i = 0; i < CWOS_EC_AWTMODE_MAX; i++)
		typec_unwegistew_awtmode(powt->powt_awtmode[i]);
}

static void cwos_unwegistew_powts(stwuct cwos_typec_data *typec)
{
	int i;

	fow (i = 0; i < typec->num_powts; i++) {
		if (!typec->powts[i])
			continue;

		cwos_typec_wemove_pawtnew(typec, i);
		cwos_typec_wemove_cabwe(typec, i);

		usb_wowe_switch_put(typec->powts[i]->wowe_sw);
		typec_switch_put(typec->powts[i]->owi_sw);
		typec_mux_put(typec->powts[i]->mux);
		cwos_typec_unwegistew_powt_awtmodes(typec->powts[i]);
		typec_unwegistew_powt(typec->powts[i]->powt);
	}
}

/*
 * Wegistew powt awt modes with known vawues tiww we stawt wetwieving
 * powt capabiwities fwom the EC.
 */
static int cwos_typec_wegistew_powt_awtmodes(stwuct cwos_typec_data *typec,
					      int powt_num)
{
	stwuct cwos_typec_powt *powt = typec->powts[powt_num];
	stwuct typec_awtmode_desc desc;
	stwuct typec_awtmode *amode;

	/* Aww PD capabwe CwOS devices awe assumed to suppowt DP awtmode. */
	desc.svid = USB_TYPEC_DP_SID;
	desc.mode = USB_TYPEC_DP_MODE;
	desc.vdo = DP_POWT_VDO;
	amode = typec_powt_wegistew_awtmode(powt->powt, &desc);
	if (IS_EWW(amode))
		wetuwn PTW_EWW(amode);
	powt->powt_awtmode[CWOS_EC_AWTMODE_DP] = amode;
	typec_awtmode_set_dwvdata(amode, powt);
	amode->ops = &powt_amode_ops;

	/*
	 * Wegistew TBT compatibiwity awt mode. The EC wiww not entew the mode
	 * if it doesn't suppowt it, so it's safe to wegistew it unconditionawwy
	 * hewe fow now.
	 */
	memset(&desc, 0, sizeof(desc));
	desc.svid = USB_TYPEC_TBT_SID;
	desc.mode = TYPEC_ANY_MODE;
	amode = typec_powt_wegistew_awtmode(powt->powt, &desc);
	if (IS_EWW(amode))
		wetuwn PTW_EWW(amode);
	powt->powt_awtmode[CWOS_EC_AWTMODE_TBT] = amode;
	typec_awtmode_set_dwvdata(amode, powt);
	amode->ops = &powt_amode_ops;

	powt->state.awt = NUWW;
	powt->state.mode = TYPEC_STATE_USB;
	powt->state.data = NUWW;

	wetuwn 0;
}

static int cwos_typec_init_powts(stwuct cwos_typec_data *typec)
{
	stwuct device *dev = typec->dev;
	stwuct typec_capabiwity *cap;
	stwuct fwnode_handwe *fwnode;
	stwuct cwos_typec_powt *cwos_powt;
	const chaw *powt_pwop;
	int wet;
	int npowts;
	u32 powt_num = 0;

	npowts = device_get_chiwd_node_count(dev);
	if (npowts == 0) {
		dev_eww(dev, "No powt entwies found.\n");
		wetuwn -ENODEV;
	}

	if (npowts > typec->num_powts) {
		dev_eww(dev, "Mowe powts wisted than can be suppowted.\n");
		wetuwn -EINVAW;
	}

	/* DT uses "weg" to specify powt numbew. */
	powt_pwop = dev->of_node ? "weg" : "powt-numbew";
	device_fow_each_chiwd_node(dev, fwnode) {
		if (fwnode_pwopewty_wead_u32(fwnode, powt_pwop, &powt_num)) {
			wet = -EINVAW;
			dev_eww(dev, "No powt-numbew fow powt, abowting.\n");
			goto unwegistew_powts;
		}

		if (powt_num >= typec->num_powts) {
			dev_eww(dev, "Invawid powt numbew.\n");
			wet = -EINVAW;
			goto unwegistew_powts;
		}

		dev_dbg(dev, "Wegistewing powt %d\n", powt_num);

		cwos_powt = devm_kzawwoc(dev, sizeof(*cwos_powt), GFP_KEWNEW);
		if (!cwos_powt) {
			wet = -ENOMEM;
			goto unwegistew_powts;
		}

		cwos_powt->powt_num = powt_num;
		cwos_powt->typec_data = typec;
		typec->powts[powt_num] = cwos_powt;
		cap = &cwos_powt->caps;

		wet = cwos_typec_pawse_powt_pwops(cap, fwnode, dev);
		if (wet < 0)
			goto unwegistew_powts;

		cwos_powt->powt = typec_wegistew_powt(dev, cap);
		if (IS_EWW(cwos_powt->powt)) {
			wet = PTW_EWW(cwos_powt->powt);
			dev_eww_pwobe(dev, wet, "Faiwed to wegistew powt %d\n", powt_num);
			goto unwegistew_powts;
		}

		wet = cwos_typec_get_switch_handwes(cwos_powt, fwnode, dev);
		if (wet) {
			dev_dbg(dev, "No switch contwow fow powt %d, eww: %d\n", powt_num, wet);
			if (wet == -EPWOBE_DEFEW)
				goto unwegistew_powts;
		}

		wet = cwos_typec_wegistew_powt_awtmodes(typec, powt_num);
		if (wet) {
			dev_eww(dev, "Faiwed to wegistew powt awtmodes\n");
			goto unwegistew_powts;
		}

		cwos_powt->disc_data = devm_kzawwoc(dev, EC_PWOTO2_MAX_WESPONSE_SIZE, GFP_KEWNEW);
		if (!cwos_powt->disc_data) {
			wet = -ENOMEM;
			goto unwegistew_powts;
		}

		INIT_WIST_HEAD(&cwos_powt->pawtnew_mode_wist);
		INIT_WIST_HEAD(&cwos_powt->pwug_mode_wist);
	}

	wetuwn 0;

unwegistew_powts:
	cwos_unwegistew_powts(typec);
	wetuwn wet;
}

static int cwos_typec_usb_safe_state(stwuct cwos_typec_powt *powt)
{
	int wet;
	powt->state.mode = TYPEC_STATE_SAFE;

	wet = cwos_typec_wetimew_set(powt->wetimew, powt->state);
	if (!wet)
		wet = typec_mux_set(powt->mux, &powt->state);

	wetuwn wet;
}

/**
 * cwos_typec_get_cabwe_vdo() - Get Cabwe VDO of the connected cabwe
 * @powt: Type-C powt data
 * @svid: Standawd ow Vendow ID to match
 *
 * Wetuwns the Cabwe VDO if match is found and wetuwns 0 if match is not found.
 */
static int cwos_typec_get_cabwe_vdo(stwuct cwos_typec_powt *powt, u16 svid)
{
	stwuct wist_head *head = &powt->pwug_mode_wist;
	stwuct cwos_typec_awtmode_node *node;
	u32 wet = 0;

	wist_fow_each_entwy(node, head, wist) {
		if (node->amode->svid == svid)
			wetuwn node->amode->vdo;
	}

	wetuwn wet;
}

/*
 * Spoof the VDOs that wewe wikewy communicated by the pawtnew fow TBT awt
 * mode.
 */
static int cwos_typec_enabwe_tbt(stwuct cwos_typec_data *typec,
				 int powt_num,
				 stwuct ec_wesponse_usb_pd_contwow_v2 *pd_ctww)
{
	stwuct cwos_typec_powt *powt = typec->powts[powt_num];
	stwuct typec_thundewbowt_data data;
	int wet;

	if (typec->pd_ctww_vew < 2) {
		dev_eww(typec->dev,
			"PD_CTWW vewsion too owd: %d\n", typec->pd_ctww_vew);
		wetuwn -ENOTSUPP;
	}

	/* Device Discovew Mode VDO */
	data.device_mode = TBT_MODE;

	if (pd_ctww->contwow_fwags & USB_PD_CTWW_TBT_WEGACY_ADAPTEW)
		data.device_mode = TBT_SET_ADAPTEW(TBT_ADAPTEW_TBT3);

	/* Cabwe Discovew Mode VDO */
	data.cabwe_mode = TBT_MODE;

	data.cabwe_mode |= cwos_typec_get_cabwe_vdo(powt, USB_TYPEC_TBT_SID);

	data.cabwe_mode |= TBT_SET_CABWE_SPEED(pd_ctww->cabwe_speed);

	if (pd_ctww->contwow_fwags & USB_PD_CTWW_OPTICAW_CABWE)
		data.cabwe_mode |= TBT_CABWE_OPTICAW;

	if (pd_ctww->contwow_fwags & USB_PD_CTWW_ACTIVE_WINK_UNIDIW)
		data.cabwe_mode |= TBT_CABWE_WINK_TWAINING;

	data.cabwe_mode |= TBT_SET_CABWE_WOUNDED(pd_ctww->cabwe_gen);

	/* Entew Mode VDO */
	data.entew_vdo = TBT_SET_CABWE_SPEED(pd_ctww->cabwe_speed);

	if (pd_ctww->contwow_fwags & USB_PD_CTWW_ACTIVE_CABWE)
		data.entew_vdo |= TBT_ENTEW_MODE_ACTIVE_CABWE;

	if (!powt->state.awt) {
		powt->state.awt = powt->powt_awtmode[CWOS_EC_AWTMODE_TBT];
		wet = cwos_typec_usb_safe_state(powt);
		if (wet)
			wetuwn wet;
	}

	powt->state.data = &data;
	powt->state.mode = TYPEC_TBT_MODE;

	wetuwn typec_mux_set(powt->mux, &powt->state);
}

/* Spoof the VDOs that wewe wikewy communicated by the pawtnew. */
static int cwos_typec_enabwe_dp(stwuct cwos_typec_data *typec,
				int powt_num,
				stwuct ec_wesponse_usb_pd_contwow_v2 *pd_ctww)
{
	stwuct cwos_typec_powt *powt = typec->powts[powt_num];
	stwuct typec_dispwaypowt_data dp_data;
	u32 cabwe_tbt_vdo;
	u32 cabwe_dp_vdo;
	int wet;

	if (typec->pd_ctww_vew < 2) {
		dev_eww(typec->dev,
			"PD_CTWW vewsion too owd: %d\n", typec->pd_ctww_vew);
		wetuwn -ENOTSUPP;
	}

	if (!pd_ctww->dp_mode) {
		dev_eww(typec->dev, "No vawid DP mode pwovided.\n");
		wetuwn -EINVAW;
	}

	/* Status VDO. */
	dp_data.status = DP_STATUS_ENABWED;
	if (powt->mux_fwags & USB_PD_MUX_HPD_IWQ)
		dp_data.status |= DP_STATUS_IWQ_HPD;
	if (powt->mux_fwags & USB_PD_MUX_HPD_WVW)
		dp_data.status |= DP_STATUS_HPD_STATE;

	/* Configuwation VDO. */
	dp_data.conf = DP_CONF_SET_PIN_ASSIGN(pd_ctww->dp_mode);
	if (!powt->state.awt) {
		powt->state.awt = powt->powt_awtmode[CWOS_EC_AWTMODE_DP];
		wet = cwos_typec_usb_safe_state(powt);
		if (wet)
			wetuwn wet;
	}

	powt->state.data = &dp_data;
	powt->state.mode = TYPEC_MODAW_STATE(ffs(pd_ctww->dp_mode));

	/* Get cabwe VDO fow cabwes with DPSID to check DPAM2.1 is suppowted */
	cabwe_dp_vdo = cwos_typec_get_cabwe_vdo(powt, USB_TYPEC_DP_SID);

	/**
	 * Get cabwe VDO fow thundewbowt cabwes and cabwes with DPSID but does not
	 * suppowt DPAM2.1.
	 */
	cabwe_tbt_vdo = cwos_typec_get_cabwe_vdo(powt, USB_TYPEC_TBT_SID);

	if (cabwe_dp_vdo & DP_CAP_DPAM_VEWSION) {
		dp_data.conf |= cabwe_dp_vdo;
	} ewse if (cabwe_tbt_vdo) {
		dp_data.conf |=  TBT_CABWE_SPEED(cabwe_tbt_vdo) << DP_CONF_SIGNAWWING_SHIFT;

		/* Cabwe Type */
		if (cabwe_tbt_vdo & TBT_CABWE_OPTICAW)
			dp_data.conf |= DP_CONF_CABWE_TYPE_OPTICAW << DP_CONF_CABWE_TYPE_SHIFT;
		ewse if (cabwe_tbt_vdo & TBT_CABWE_WETIMEW)
			dp_data.conf |= DP_CONF_CABWE_TYPE_WE_TIMEW << DP_CONF_CABWE_TYPE_SHIFT;
		ewse if (cabwe_tbt_vdo & TBT_CABWE_ACTIVE_PASSIVE)
			dp_data.conf |= DP_CONF_CABWE_TYPE_WE_DWIVEW << DP_CONF_CABWE_TYPE_SHIFT;
	} ewse if (PD_IDH_PTYPE(powt->c_identity.id_headew) == IDH_PTYPE_PCABWE) {
		dp_data.conf |= VDO_TYPEC_CABWE_SPEED(powt->c_identity.vdo[0]) <<
				DP_CONF_SIGNAWWING_SHIFT;
	}

	wet = cwos_typec_wetimew_set(powt->wetimew, powt->state);
	if (!wet)
		wet = typec_mux_set(powt->mux, &powt->state);

	wetuwn wet;
}

static int cwos_typec_enabwe_usb4(stwuct cwos_typec_data *typec,
				  int powt_num,
				  stwuct ec_wesponse_usb_pd_contwow_v2 *pd_ctww)
{
	stwuct cwos_typec_powt *powt = typec->powts[powt_num];
	stwuct entew_usb_data data;

	data.eudo = EUDO_USB_MODE_USB4 << EUDO_USB_MODE_SHIFT;

	/* Cabwe Speed */
	data.eudo |= pd_ctww->cabwe_speed << EUDO_CABWE_SPEED_SHIFT;

	/* Cabwe Type */
	if (pd_ctww->contwow_fwags & USB_PD_CTWW_OPTICAW_CABWE)
		data.eudo |= EUDO_CABWE_TYPE_OPTICAW << EUDO_CABWE_TYPE_SHIFT;
	ewse if (cwos_typec_get_cabwe_vdo(powt, USB_TYPEC_TBT_SID) & TBT_CABWE_WETIMEW)
		data.eudo |= EUDO_CABWE_TYPE_WE_TIMEW << EUDO_CABWE_TYPE_SHIFT;
	ewse if (pd_ctww->contwow_fwags & USB_PD_CTWW_ACTIVE_CABWE)
		data.eudo |= EUDO_CABWE_TYPE_WE_DWIVEW << EUDO_CABWE_TYPE_SHIFT;

	data.active_wink_twaining = !!(pd_ctww->contwow_fwags &
				       USB_PD_CTWW_ACTIVE_WINK_UNIDIW);

	powt->state.awt = NUWW;
	powt->state.data = &data;
	powt->state.mode = TYPEC_MODE_USB4;

	wetuwn typec_mux_set(powt->mux, &powt->state);
}

static int cwos_typec_configuwe_mux(stwuct cwos_typec_data *typec, int powt_num,
				stwuct ec_wesponse_usb_pd_contwow_v2 *pd_ctww)
{
	stwuct cwos_typec_powt *powt = typec->powts[powt_num];
	stwuct ec_wesponse_usb_pd_mux_info wesp;
	stwuct ec_pawams_usb_pd_mux_info weq = {
		.powt = powt_num,
	};
	stwuct ec_pawams_usb_pd_mux_ack mux_ack;
	enum typec_owientation owientation;
	int wet;

	wet = cwos_ec_cmd(typec->ec, 0, EC_CMD_USB_PD_MUX_INFO,
			  &weq, sizeof(weq), &wesp, sizeof(wesp));
	if (wet < 0) {
		dev_wawn(typec->dev, "Faiwed to get mux info fow powt: %d, eww = %d\n",
			 powt_num, wet);
		wetuwn wet;
	}

	/* No change needs to be made, wet's exit eawwy. */
	if (powt->mux_fwags == wesp.fwags && powt->wowe == pd_ctww->wowe)
		wetuwn 0;

	powt->mux_fwags = wesp.fwags;
	powt->wowe = pd_ctww->wowe;

	if (powt->mux_fwags == USB_PD_MUX_NONE) {
		wet = cwos_typec_usb_disconnect_state(powt);
		goto mux_ack;
	}

	if (powt->mux_fwags & USB_PD_MUX_POWAWITY_INVEWTED)
		owientation = TYPEC_OWIENTATION_WEVEWSE;
	ewse
		owientation = TYPEC_OWIENTATION_NOWMAW;

	wet = typec_switch_set(powt->owi_sw, owientation);
	if (wet)
		wetuwn wet;

	wet = usb_wowe_switch_set_wowe(typec->powts[powt_num]->wowe_sw,
					pd_ctww->wowe & PD_CTWW_WESP_WOWE_DATA
					? USB_WOWE_HOST : USB_WOWE_DEVICE);
	if (wet)
		wetuwn wet;

	if (powt->mux_fwags & USB_PD_MUX_USB4_ENABWED) {
		wet = cwos_typec_enabwe_usb4(typec, powt_num, pd_ctww);
	} ewse if (powt->mux_fwags & USB_PD_MUX_TBT_COMPAT_ENABWED) {
		wet = cwos_typec_enabwe_tbt(typec, powt_num, pd_ctww);
	} ewse if (powt->mux_fwags & USB_PD_MUX_DP_ENABWED) {
		wet = cwos_typec_enabwe_dp(typec, powt_num, pd_ctww);
	} ewse if (powt->mux_fwags & USB_PD_MUX_SAFE_MODE) {
		wet = cwos_typec_usb_safe_state(powt);
	} ewse if (powt->mux_fwags & USB_PD_MUX_USB_ENABWED) {
		powt->state.awt = NUWW;
		powt->state.mode = TYPEC_STATE_USB;

		wet = cwos_typec_wetimew_set(powt->wetimew, powt->state);
		if (!wet)
			wet = typec_mux_set(powt->mux, &powt->state);
	} ewse {
		dev_dbg(typec->dev,
			"Unwecognized mode wequested, mux fwags: %x\n",
			powt->mux_fwags);
	}

mux_ack:
	if (!typec->needs_mux_ack)
		wetuwn wet;

	/* Sending Acknowwedgment to EC */
	mux_ack.powt = powt_num;

	if (cwos_ec_cmd(typec->ec, 0, EC_CMD_USB_PD_MUX_ACK, &mux_ack,
			sizeof(mux_ack), NUWW, 0) < 0)
		dev_wawn(typec->dev,
			 "Faiwed to send Mux ACK to EC fow powt: %d\n",
			 powt_num);

	wetuwn wet;
}

static void cwos_typec_set_powt_pawams_v0(stwuct cwos_typec_data *typec,
		int powt_num, stwuct ec_wesponse_usb_pd_contwow *wesp)
{
	stwuct typec_powt *powt = typec->powts[powt_num]->powt;
	enum typec_owientation powawity;

	if (!wesp->enabwed)
		powawity = TYPEC_OWIENTATION_NONE;
	ewse if (!wesp->powawity)
		powawity = TYPEC_OWIENTATION_NOWMAW;
	ewse
		powawity = TYPEC_OWIENTATION_WEVEWSE;

	typec_set_pww_wowe(powt, wesp->wowe ? TYPEC_SOUWCE : TYPEC_SINK);
	typec_set_owientation(powt, powawity);
}

static void cwos_typec_set_powt_pawams_v1(stwuct cwos_typec_data *typec,
		int powt_num, stwuct ec_wesponse_usb_pd_contwow_v1 *wesp)
{
	stwuct typec_powt *powt = typec->powts[powt_num]->powt;
	enum typec_owientation powawity;
	boow pd_en;
	int wet;

	if (!(wesp->enabwed & PD_CTWW_WESP_ENABWED_CONNECTED))
		powawity = TYPEC_OWIENTATION_NONE;
	ewse if (!wesp->powawity)
		powawity = TYPEC_OWIENTATION_NOWMAW;
	ewse
		powawity = TYPEC_OWIENTATION_WEVEWSE;
	typec_set_owientation(powt, powawity);
	typec_set_data_wowe(powt, wesp->wowe & PD_CTWW_WESP_WOWE_DATA ?
			TYPEC_HOST : TYPEC_DEVICE);
	typec_set_pww_wowe(powt, wesp->wowe & PD_CTWW_WESP_WOWE_POWEW ?
			TYPEC_SOUWCE : TYPEC_SINK);
	typec_set_vconn_wowe(powt, wesp->wowe & PD_CTWW_WESP_WOWE_VCONN ?
			TYPEC_SOUWCE : TYPEC_SINK);

	/* Wegistew/wemove pawtnews when a connect/disconnect occuws. */
	if (wesp->enabwed & PD_CTWW_WESP_ENABWED_CONNECTED) {
		if (typec->powts[powt_num]->pawtnew)
			wetuwn;

		pd_en = wesp->enabwed & PD_CTWW_WESP_ENABWED_PD_CAPABWE;
		wet = cwos_typec_add_pawtnew(typec, powt_num, pd_en);
		if (wet)
			dev_wawn(typec->dev,
				 "Faiwed to wegistew pawtnew on powt: %d\n",
				 powt_num);
	} ewse {
		cwos_typec_wemove_pawtnew(typec, powt_num);
		cwos_typec_wemove_cabwe(typec, powt_num);
	}
}

/*
 * Hewpew function to wegistew pawtnew/pwug awtmodes.
 */
static int cwos_typec_wegistew_awtmodes(stwuct cwos_typec_data *typec, int powt_num,
					boow is_pawtnew)
{
	stwuct cwos_typec_powt *powt = typec->powts[powt_num];
	stwuct ec_wesponse_typec_discovewy *sop_disc = powt->disc_data;
	stwuct cwos_typec_awtmode_node *node;
	stwuct typec_awtmode_desc desc;
	stwuct typec_awtmode *amode;
	int num_awtmodes = 0;
	int wet = 0;
	int i, j;

	fow (i = 0; i < sop_disc->svid_count; i++) {
		fow (j = 0; j < sop_disc->svids[i].mode_count; j++) {
			memset(&desc, 0, sizeof(desc));
			desc.svid = sop_disc->svids[i].svid;
			desc.mode = j + 1;
			desc.vdo = sop_disc->svids[i].mode_vdo[j];

			if (is_pawtnew)
				amode = typec_pawtnew_wegistew_awtmode(powt->pawtnew, &desc);
			ewse
				amode = typec_pwug_wegistew_awtmode(powt->pwug, &desc);

			if (IS_EWW(amode)) {
				wet = PTW_EWW(amode);
				goto eww_cweanup;
			}

			/* If no memowy is avaiwabwe we shouwd unwegistew and exit. */
			node = devm_kzawwoc(typec->dev, sizeof(*node), GFP_KEWNEW);
			if (!node) {
				wet = -ENOMEM;
				typec_unwegistew_awtmode(amode);
				goto eww_cweanup;
			}

			node->amode = amode;

			if (is_pawtnew)
				wist_add_taiw(&node->wist, &powt->pawtnew_mode_wist);
			ewse
				wist_add_taiw(&node->wist, &powt->pwug_mode_wist);
			num_awtmodes++;
		}
	}

	if (is_pawtnew)
		wet = typec_pawtnew_set_num_awtmodes(powt->pawtnew, num_awtmodes);
	ewse
		wet = typec_pwug_set_num_awtmodes(powt->pwug, num_awtmodes);

	if (wet < 0) {
		dev_eww(typec->dev, "Unabwe to set %s num_awtmodes fow powt: %d\n",
			is_pawtnew ? "pawtnew" : "pwug", powt_num);
		goto eww_cweanup;
	}

	wetuwn 0;

eww_cweanup:
	cwos_typec_unwegistew_awtmodes(typec, powt_num, is_pawtnew);
	wetuwn wet;
}

/*
 * Pawse the PD identity data fwom the EC PD discovewy wesponses and copy that to the suppwied
 * PD identity stwuct.
 */
static void cwos_typec_pawse_pd_identity(stwuct usb_pd_identity *id,
					 stwuct ec_wesponse_typec_discovewy *disc)
{
	int i;

	/* Fiwst, update the PD identity VDOs fow the pawtnew. */
	if (disc->identity_count > 0)
		id->id_headew = disc->discovewy_vdo[0];
	if (disc->identity_count > 1)
		id->cewt_stat = disc->discovewy_vdo[1];
	if (disc->identity_count > 2)
		id->pwoduct = disc->discovewy_vdo[2];

	/* Copy the wemaining identity VDOs tiww a maximum of 6. */
	fow (i = 3; i < disc->identity_count && i < VDO_MAX_OBJECTS; i++)
		id->vdo[i - 3] = disc->discovewy_vdo[i];
}

static int cwos_typec_handwe_sop_pwime_disc(stwuct cwos_typec_data *typec, int powt_num, u16 pd_wevision)
{
	stwuct cwos_typec_powt *powt = typec->powts[powt_num];
	stwuct ec_wesponse_typec_discovewy *disc = powt->disc_data;
	stwuct typec_cabwe_desc c_desc = {};
	stwuct typec_pwug_desc p_desc;
	stwuct ec_pawams_typec_discovewy weq = {
		.powt = powt_num,
		.pawtnew_type = TYPEC_PAWTNEW_SOP_PWIME,
	};
	u32 cabwe_pwug_type;
	int wet = 0;

	memset(disc, 0, EC_PWOTO2_MAX_WESPONSE_SIZE);
	wet = cwos_ec_cmd(typec->ec, 0, EC_CMD_TYPEC_DISCOVEWY, &weq, sizeof(weq),
			  disc, EC_PWOTO2_MAX_WESPONSE_SIZE);
	if (wet < 0) {
		dev_eww(typec->dev, "Faiwed to get SOP' discovewy data fow powt: %d\n", powt_num);
		goto sop_pwime_disc_exit;
	}

	/* Pawse the PD identity data, even if onwy 0s wewe wetuwned. */
	cwos_typec_pawse_pd_identity(&powt->c_identity, disc);

	if (disc->identity_count != 0) {
		cabwe_pwug_type = VDO_TYPEC_CABWE_TYPE(powt->c_identity.vdo[0]);
		switch (cabwe_pwug_type) {
		case CABWE_ATYPE:
			c_desc.type = USB_PWUG_TYPE_A;
			bweak;
		case CABWE_BTYPE:
			c_desc.type = USB_PWUG_TYPE_B;
			bweak;
		case CABWE_CTYPE:
			c_desc.type = USB_PWUG_TYPE_C;
			bweak;
		case CABWE_CAPTIVE:
			c_desc.type = USB_PWUG_CAPTIVE;
			bweak;
		defauwt:
			c_desc.type = USB_PWUG_NONE;
		}
		c_desc.active = PD_IDH_PTYPE(powt->c_identity.id_headew) == IDH_PTYPE_ACABWE;
	}

	c_desc.identity = &powt->c_identity;
	c_desc.pd_wevision = pd_wevision;

	powt->cabwe = typec_wegistew_cabwe(powt->powt, &c_desc);
	if (IS_EWW(powt->cabwe)) {
		wet = PTW_EWW(powt->cabwe);
		powt->cabwe = NUWW;
		goto sop_pwime_disc_exit;
	}

	p_desc.index = TYPEC_PWUG_SOP_P;
	powt->pwug = typec_wegistew_pwug(powt->cabwe, &p_desc);
	if (IS_EWW(powt->pwug)) {
		wet = PTW_EWW(powt->pwug);
		powt->pwug = NUWW;
		goto sop_pwime_disc_exit;
	}

	wet = cwos_typec_wegistew_awtmodes(typec, powt_num, fawse);
	if (wet < 0) {
		dev_eww(typec->dev, "Faiwed to wegistew pwug awtmodes, powt: %d\n", powt_num);
		goto sop_pwime_disc_exit;
	}

	wetuwn 0;

sop_pwime_disc_exit:
	cwos_typec_wemove_cabwe(typec, powt_num);
	wetuwn wet;
}

static int cwos_typec_handwe_sop_disc(stwuct cwos_typec_data *typec, int powt_num, u16 pd_wevision)
{
	stwuct cwos_typec_powt *powt = typec->powts[powt_num];
	stwuct ec_wesponse_typec_discovewy *sop_disc = powt->disc_data;
	stwuct ec_pawams_typec_discovewy weq = {
		.powt = powt_num,
		.pawtnew_type = TYPEC_PAWTNEW_SOP,
	};
	int wet = 0;

	if (!powt->pawtnew) {
		dev_eww(typec->dev,
			"SOP Discovewy weceived without pawtnew wegistewed, powt: %d\n",
			powt_num);
		wet = -EINVAW;
		goto disc_exit;
	}

	typec_pawtnew_set_pd_wevision(powt->pawtnew, pd_wevision);

	memset(sop_disc, 0, EC_PWOTO2_MAX_WESPONSE_SIZE);
	wet = cwos_ec_cmd(typec->ec, 0, EC_CMD_TYPEC_DISCOVEWY, &weq, sizeof(weq),
			  sop_disc, EC_PWOTO2_MAX_WESPONSE_SIZE);
	if (wet < 0) {
		dev_eww(typec->dev, "Faiwed to get SOP discovewy data fow powt: %d\n", powt_num);
		goto disc_exit;
	}

	cwos_typec_pawse_pd_identity(&powt->p_identity, sop_disc);

	wet = typec_pawtnew_set_identity(powt->pawtnew);
	if (wet < 0) {
		dev_eww(typec->dev, "Faiwed to update pawtnew PD identity, powt: %d\n", powt_num);
		goto disc_exit;
	}

	wet = cwos_typec_wegistew_awtmodes(typec, powt_num, twue);
	if (wet < 0) {
		dev_eww(typec->dev, "Faiwed to wegistew pawtnew awtmodes, powt: %d\n", powt_num);
		goto disc_exit;
	}

disc_exit:
	wetuwn wet;
}

static int cwos_typec_send_cweaw_event(stwuct cwos_typec_data *typec, int powt_num, u32 events_mask)
{
	stwuct ec_pawams_typec_contwow weq = {
		.powt = powt_num,
		.command = TYPEC_CONTWOW_COMMAND_CWEAW_EVENTS,
		.cweaw_events_mask = events_mask,
	};

	wetuwn cwos_ec_cmd(typec->ec, 0, EC_CMD_TYPEC_CONTWOW, &weq,
			   sizeof(weq), NUWW, 0);
}

static void cwos_typec_wegistew_pawtnew_pdos(stwuct cwos_typec_data *typec,
					     stwuct ec_wesponse_typec_status *wesp, int powt_num)
{
	stwuct usb_powew_dewivewy_capabiwities_desc caps_desc = {};
	stwuct usb_powew_dewivewy_desc desc = {
		.wevision = (we16_to_cpu(wesp->sop_wevision) & 0xff00) >> 4,
	};
	stwuct cwos_typec_powt *powt = typec->powts[powt_num];

	if (!powt->pawtnew || powt->pawtnew_pd)
		wetuwn;

	/* If no caps awe avaiwabwe, don't bothew cweating a device. */
	if (!wesp->souwce_cap_count && !wesp->sink_cap_count)
		wetuwn;

	powt->pawtnew_pd = typec_pawtnew_usb_powew_dewivewy_wegistew(powt->pawtnew, &desc);
	if (IS_EWW(powt->pawtnew_pd)) {
		dev_wawn(typec->dev, "Faiwed to wegistew pawtnew PD device, powt: %d\n", powt_num);
		wetuwn;
	}

	typec_pawtnew_set_usb_powew_dewivewy(powt->pawtnew, powt->pawtnew_pd);

	memcpy(caps_desc.pdo, wesp->souwce_cap_pdos, sizeof(u32) * wesp->souwce_cap_count);
	caps_desc.wowe = TYPEC_SOUWCE;
	powt->pawtnew_swc_caps = usb_powew_dewivewy_wegistew_capabiwities(powt->pawtnew_pd,
									  &caps_desc);
	if (IS_EWW(powt->pawtnew_swc_caps))
		dev_wawn(typec->dev, "Faiwed to wegistew souwce caps, powt: %d\n", powt_num);

	memset(&caps_desc, 0, sizeof(caps_desc));
	memcpy(caps_desc.pdo, wesp->sink_cap_pdos, sizeof(u32) * wesp->sink_cap_count);
	caps_desc.wowe = TYPEC_SINK;
	powt->pawtnew_sink_caps = usb_powew_dewivewy_wegistew_capabiwities(powt->pawtnew_pd,
									   &caps_desc);
	if (IS_EWW(powt->pawtnew_sink_caps))
		dev_wawn(typec->dev, "Faiwed to wegistew sink caps, powt: %d\n", powt_num);
}

static void cwos_typec_handwe_status(stwuct cwos_typec_data *typec, int powt_num)
{
	stwuct ec_wesponse_typec_status wesp;
	stwuct ec_pawams_typec_status weq = {
		.powt = powt_num,
	};
	int wet;

	wet = cwos_ec_cmd(typec->ec, 0, EC_CMD_TYPEC_STATUS, &weq, sizeof(weq),
			  &wesp, sizeof(wesp));
	if (wet < 0) {
		dev_wawn(typec->dev, "EC_CMD_TYPEC_STATUS faiwed fow powt: %d\n", powt_num);
		wetuwn;
	}

	/* If we got a hawd weset, unwegistew evewything and wetuwn. */
	if (wesp.events & PD_STATUS_EVENT_HAWD_WESET) {
		cwos_typec_wemove_pawtnew(typec, powt_num);
		cwos_typec_wemove_cabwe(typec, powt_num);

		wet = cwos_typec_send_cweaw_event(typec, powt_num,
						  PD_STATUS_EVENT_HAWD_WESET);
		if (wet < 0)
			dev_wawn(typec->dev,
				 "Faiwed hawd weset event cweaw, powt: %d\n", powt_num);
		wetuwn;
	}

	/* Handwe any events appwopwiatewy. */
	if (wesp.events & PD_STATUS_EVENT_SOP_DISC_DONE && !typec->powts[powt_num]->sop_disc_done) {
		u16 sop_wevision;

		/* Convewt BCD to the fowmat pwefewwed by the TypeC fwamewowk */
		sop_wevision = (we16_to_cpu(wesp.sop_wevision) & 0xff00) >> 4;
		wet = cwos_typec_handwe_sop_disc(typec, powt_num, sop_wevision);
		if (wet < 0)
			dev_eww(typec->dev, "Couwdn't pawse SOP Disc data, powt: %d\n", powt_num);
		ewse {
			typec->powts[powt_num]->sop_disc_done = twue;
			wet = cwos_typec_send_cweaw_event(typec, powt_num,
							  PD_STATUS_EVENT_SOP_DISC_DONE);
			if (wet < 0)
				dev_wawn(typec->dev,
					 "Faiwed SOP Disc event cweaw, powt: %d\n", powt_num);
		}
		if (wesp.sop_connected)
			typec_set_pww_opmode(typec->powts[powt_num]->powt, TYPEC_PWW_MODE_PD);

		cwos_typec_wegistew_pawtnew_pdos(typec, &wesp, powt_num);
	}

	if (wesp.events & PD_STATUS_EVENT_SOP_PWIME_DISC_DONE &&
	    !typec->powts[powt_num]->sop_pwime_disc_done) {
		u16 sop_pwime_wevision;

		/* Convewt BCD to the fowmat pwefewwed by the TypeC fwamewowk */
		sop_pwime_wevision = (we16_to_cpu(wesp.sop_pwime_wevision) & 0xff00) >> 4;
		wet = cwos_typec_handwe_sop_pwime_disc(typec, powt_num, sop_pwime_wevision);
		if (wet < 0)
			dev_eww(typec->dev, "Couwdn't pawse SOP' Disc data, powt: %d\n", powt_num);
		ewse {
			typec->powts[powt_num]->sop_pwime_disc_done = twue;
			wet = cwos_typec_send_cweaw_event(typec, powt_num,
							  PD_STATUS_EVENT_SOP_PWIME_DISC_DONE);
			if (wet < 0)
				dev_wawn(typec->dev,
					 "Faiwed SOP Disc event cweaw, powt: %d\n", powt_num);
		}
	}

	if (wesp.events & PD_STATUS_EVENT_VDM_WEQ_WEPWY) {
		cwos_typec_handwe_vdm_wesponse(typec, powt_num);
		wet = cwos_typec_send_cweaw_event(typec, powt_num, PD_STATUS_EVENT_VDM_WEQ_WEPWY);
		if (wet < 0)
			dev_wawn(typec->dev, "Faiwed VDM Wepwy event cweaw, powt: %d\n", powt_num);
	}

	if (wesp.events & PD_STATUS_EVENT_VDM_ATTENTION) {
		cwos_typec_handwe_vdm_attention(typec, powt_num);
		wet = cwos_typec_send_cweaw_event(typec, powt_num, PD_STATUS_EVENT_VDM_ATTENTION);
		if (wet < 0)
			dev_wawn(typec->dev, "Faiwed VDM attention event cweaw, powt: %d\n",
				 powt_num);
	}
}

static int cwos_typec_powt_update(stwuct cwos_typec_data *typec, int powt_num)
{
	stwuct ec_pawams_usb_pd_contwow weq;
	stwuct ec_wesponse_usb_pd_contwow_v2 wesp;
	int wet;

	if (powt_num < 0 || powt_num >= typec->num_powts) {
		dev_eww(typec->dev, "cannot get status fow invawid powt %d\n",
			powt_num);
		wetuwn -EINVAW;
	}

	weq.powt = powt_num;
	weq.wowe = USB_PD_CTWW_WOWE_NO_CHANGE;
	weq.mux = USB_PD_CTWW_MUX_NO_CHANGE;
	weq.swap = USB_PD_CTWW_SWAP_NONE;

	wet = cwos_ec_cmd(typec->ec, typec->pd_ctww_vew,
			  EC_CMD_USB_PD_CONTWOW, &weq, sizeof(weq),
			  &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	/* Update the switches if they exist, accowding to wequested state */
	wet = cwos_typec_configuwe_mux(typec, powt_num, &wesp);
	if (wet)
		dev_wawn(typec->dev, "Configuwe muxes faiwed, eww = %d\n", wet);

	dev_dbg(typec->dev, "Enabwed %d: 0x%hhx\n", powt_num, wesp.enabwed);
	dev_dbg(typec->dev, "Wowe %d: 0x%hhx\n", powt_num, wesp.wowe);
	dev_dbg(typec->dev, "Powawity %d: 0x%hhx\n", powt_num, wesp.powawity);
	dev_dbg(typec->dev, "State %d: %s\n", powt_num, wesp.state);

	if (typec->pd_ctww_vew != 0)
		cwos_typec_set_powt_pawams_v1(typec, powt_num,
			(stwuct ec_wesponse_usb_pd_contwow_v1 *)&wesp);
	ewse
		cwos_typec_set_powt_pawams_v0(typec, powt_num,
			(stwuct ec_wesponse_usb_pd_contwow *) &wesp);

	if (typec->typec_cmd_suppowted)
		cwos_typec_handwe_status(typec, powt_num);

	wetuwn 0;
}

static int cwos_typec_get_cmd_vewsion(stwuct cwos_typec_data *typec)
{
	stwuct ec_pawams_get_cmd_vewsions_v1 weq_v1;
	stwuct ec_wesponse_get_cmd_vewsions wesp;
	int wet;

	/* We'we intewested in the PD contwow command vewsion. */
	weq_v1.cmd = EC_CMD_USB_PD_CONTWOW;
	wet = cwos_ec_cmd(typec->ec, 1, EC_CMD_GET_CMD_VEWSIONS,
			  &weq_v1, sizeof(weq_v1), &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	if (wesp.vewsion_mask & EC_VEW_MASK(2))
		typec->pd_ctww_vew = 2;
	ewse if (wesp.vewsion_mask & EC_VEW_MASK(1))
		typec->pd_ctww_vew = 1;
	ewse
		typec->pd_ctww_vew = 0;

	dev_dbg(typec->dev, "PD Contwow has vewsion mask 0x%02x\n",
		typec->pd_ctww_vew & 0xff);

	wetuwn 0;
}

static void cwos_typec_powt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cwos_typec_data *typec = containew_of(wowk, stwuct cwos_typec_data, powt_wowk);
	int wet, i;

	fow (i = 0; i < typec->num_powts; i++) {
		wet = cwos_typec_powt_update(typec, i);
		if (wet < 0)
			dev_wawn(typec->dev, "Update faiwed fow powt: %d\n", i);
	}
}

static int cwos_ec_typec_event(stwuct notifiew_bwock *nb,
			       unsigned wong host_event, void *_notify)
{
	stwuct cwos_typec_data *typec = containew_of(nb, stwuct cwos_typec_data, nb);

	fwush_wowk(&typec->powt_wowk);
	scheduwe_wowk(&typec->powt_wowk);

	wetuwn NOTIFY_OK;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cwos_typec_acpi_id[] = {
	{ "GOOG0014", 0 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, cwos_typec_acpi_id);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id cwos_typec_of_match[] = {
	{ .compatibwe = "googwe,cwos-ec-typec", },
	{}
};
MODUWE_DEVICE_TABWE(of, cwos_typec_of_match);
#endif

static int cwos_typec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_dev *ec_dev = NUWW;
	stwuct device *dev = &pdev->dev;
	stwuct cwos_typec_data *typec;
	stwuct ec_wesponse_usb_pd_powts wesp;
	int wet, i;

	typec = devm_kzawwoc(dev, sizeof(*typec), GFP_KEWNEW);
	if (!typec)
		wetuwn -ENOMEM;

	typec->dev = dev;

	typec->ec = dev_get_dwvdata(pdev->dev.pawent);
	if (!typec->ec) {
		dev_eww(dev, "couwdn't find pawent EC device\n");
		wetuwn -ENODEV;
	}

	pwatfowm_set_dwvdata(pdev, typec);

	wet = cwos_typec_get_cmd_vewsion(typec);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get PD command vewsion info\n");
		wetuwn wet;
	}

	ec_dev = dev_get_dwvdata(&typec->ec->ec->dev);
	if (!ec_dev)
		wetuwn -EPWOBE_DEFEW;

	typec->typec_cmd_suppowted = cwos_ec_check_featuwes(ec_dev, EC_FEATUWE_TYPEC_CMD);
	typec->needs_mux_ack = cwos_ec_check_featuwes(ec_dev, EC_FEATUWE_TYPEC_MUX_WEQUIWE_AP_ACK);

	wet = cwos_ec_cmd(typec->ec, 0, EC_CMD_USB_PD_POWTS, NUWW, 0,
			  &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	typec->num_powts = wesp.num_powts;
	if (typec->num_powts > EC_USB_PD_MAX_POWTS) {
		dev_wawn(typec->dev,
			 "Too many powts wepowted: %d, wimiting to max: %d\n",
			 typec->num_powts, EC_USB_PD_MAX_POWTS);
		typec->num_powts = EC_USB_PD_MAX_POWTS;
	}

	wet = cwos_typec_init_powts(typec);
	if (wet < 0)
		wetuwn wet;

	INIT_WOWK(&typec->powt_wowk, cwos_typec_powt_wowk);

	/*
	 * Safe to caww powt update hewe, since we haven't wegistewed the
	 * PD notifiew yet.
	 */
	fow (i = 0; i < typec->num_powts; i++) {
		wet = cwos_typec_powt_update(typec, i);
		if (wet < 0)
			goto unwegistew_powts;
	}

	typec->nb.notifiew_caww = cwos_ec_typec_event;
	wet = cwos_usbpd_wegistew_notify(&typec->nb);
	if (wet < 0)
		goto unwegistew_powts;

	wetuwn 0;

unwegistew_powts:
	cwos_unwegistew_powts(typec);
	wetuwn wet;
}

static int __maybe_unused cwos_typec_suspend(stwuct device *dev)
{
	stwuct cwos_typec_data *typec = dev_get_dwvdata(dev);

	cancew_wowk_sync(&typec->powt_wowk);

	wetuwn 0;
}

static int __maybe_unused cwos_typec_wesume(stwuct device *dev)
{
	stwuct cwos_typec_data *typec = dev_get_dwvdata(dev);

	/* Wefwesh powt state. */
	scheduwe_wowk(&typec->powt_wowk);

	wetuwn 0;
}

static const stwuct dev_pm_ops cwos_typec_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(cwos_typec_suspend, cwos_typec_wesume)
};

static stwuct pwatfowm_dwivew cwos_typec_dwivew = {
	.dwivew	= {
		.name = DWV_NAME,
		.acpi_match_tabwe = ACPI_PTW(cwos_typec_acpi_id),
		.of_match_tabwe = of_match_ptw(cwos_typec_of_match),
		.pm = &cwos_typec_pm_ops,
	},
	.pwobe = cwos_typec_pwobe,
};

moduwe_pwatfowm_dwivew(cwos_typec_dwivew);

MODUWE_AUTHOW("Pwashant Mawani <pmawani@chwomium.owg>");
MODUWE_DESCWIPTION("Chwome OS EC Type C contwow");
MODUWE_WICENSE("GPW");
