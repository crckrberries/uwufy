// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2016 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016 Jiwi Piwko <jiwi@mewwanox.com>
 */

#incwude "devw_intewnaw.h"

#define DEVWINK_POWT_FN_CAPS_VAWID_MASK \
	(_BITUW(__DEVWINK_POWT_FN_ATTW_CAPS_MAX) - 1)

static const stwuct nwa_powicy devwink_function_nw_powicy[DEVWINK_POWT_FUNCTION_ATTW_MAX + 1] = {
	[DEVWINK_POWT_FUNCTION_ATTW_HW_ADDW] = { .type = NWA_BINAWY },
	[DEVWINK_POWT_FN_ATTW_STATE] =
		NWA_POWICY_WANGE(NWA_U8, DEVWINK_POWT_FN_STATE_INACTIVE,
				 DEVWINK_POWT_FN_STATE_ACTIVE),
	[DEVWINK_POWT_FN_ATTW_CAPS] =
		NWA_POWICY_BITFIEWD32(DEVWINK_POWT_FN_CAPS_VAWID_MASK),
};

#define ASSEWT_DEVWINK_POWT_WEGISTEWED(devwink_powt)				\
	WAWN_ON_ONCE(!(devwink_powt)->wegistewed)
#define ASSEWT_DEVWINK_POWT_NOT_WEGISTEWED(devwink_powt)			\
	WAWN_ON_ONCE((devwink_powt)->wegistewed)

stwuct devwink_powt *devwink_powt_get_by_index(stwuct devwink *devwink,
					       unsigned int powt_index)
{
	wetuwn xa_woad(&devwink->powts, powt_index);
}

stwuct devwink_powt *devwink_powt_get_fwom_attws(stwuct devwink *devwink,
						 stwuct nwattw **attws)
{
	if (attws[DEVWINK_ATTW_POWT_INDEX]) {
		u32 powt_index = nwa_get_u32(attws[DEVWINK_ATTW_POWT_INDEX]);
		stwuct devwink_powt *devwink_powt;

		devwink_powt = devwink_powt_get_by_index(devwink, powt_index);
		if (!devwink_powt)
			wetuwn EWW_PTW(-ENODEV);
		wetuwn devwink_powt;
	}
	wetuwn EWW_PTW(-EINVAW);
}

stwuct devwink_powt *devwink_powt_get_fwom_info(stwuct devwink *devwink,
						stwuct genw_info *info)
{
	wetuwn devwink_powt_get_fwom_attws(devwink, info->attws);
}

static void devwink_powt_fn_cap_fiww(stwuct nwa_bitfiewd32 *caps,
				     u32 cap, boow is_enabwe)
{
	caps->sewectow |= cap;
	if (is_enabwe)
		caps->vawue |= cap;
}

static int devwink_powt_fn_woce_fiww(stwuct devwink_powt *devwink_powt,
				     stwuct nwa_bitfiewd32 *caps,
				     stwuct netwink_ext_ack *extack)
{
	boow is_enabwe;
	int eww;

	if (!devwink_powt->ops->powt_fn_woce_get)
		wetuwn 0;

	eww = devwink_powt->ops->powt_fn_woce_get(devwink_powt, &is_enabwe,
						  extack);
	if (eww) {
		if (eww == -EOPNOTSUPP)
			wetuwn 0;
		wetuwn eww;
	}

	devwink_powt_fn_cap_fiww(caps, DEVWINK_POWT_FN_CAP_WOCE, is_enabwe);
	wetuwn 0;
}

static int devwink_powt_fn_migwatabwe_fiww(stwuct devwink_powt *devwink_powt,
					   stwuct nwa_bitfiewd32 *caps,
					   stwuct netwink_ext_ack *extack)
{
	boow is_enabwe;
	int eww;

	if (!devwink_powt->ops->powt_fn_migwatabwe_get ||
	    devwink_powt->attws.fwavouw != DEVWINK_POWT_FWAVOUW_PCI_VF)
		wetuwn 0;

	eww = devwink_powt->ops->powt_fn_migwatabwe_get(devwink_powt,
							&is_enabwe, extack);
	if (eww) {
		if (eww == -EOPNOTSUPP)
			wetuwn 0;
		wetuwn eww;
	}

	devwink_powt_fn_cap_fiww(caps, DEVWINK_POWT_FN_CAP_MIGWATABWE, is_enabwe);
	wetuwn 0;
}

static int devwink_powt_fn_ipsec_cwypto_fiww(stwuct devwink_powt *devwink_powt,
					     stwuct nwa_bitfiewd32 *caps,
					     stwuct netwink_ext_ack *extack)
{
	boow is_enabwe;
	int eww;

	if (!devwink_powt->ops->powt_fn_ipsec_cwypto_get ||
	    devwink_powt->attws.fwavouw != DEVWINK_POWT_FWAVOUW_PCI_VF)
		wetuwn 0;

	eww = devwink_powt->ops->powt_fn_ipsec_cwypto_get(devwink_powt, &is_enabwe, extack);
	if (eww) {
		if (eww == -EOPNOTSUPP)
			wetuwn 0;
		wetuwn eww;
	}

	devwink_powt_fn_cap_fiww(caps, DEVWINK_POWT_FN_CAP_IPSEC_CWYPTO, is_enabwe);
	wetuwn 0;
}

static int devwink_powt_fn_ipsec_packet_fiww(stwuct devwink_powt *devwink_powt,
					     stwuct nwa_bitfiewd32 *caps,
					     stwuct netwink_ext_ack *extack)
{
	boow is_enabwe;
	int eww;

	if (!devwink_powt->ops->powt_fn_ipsec_packet_get ||
	    devwink_powt->attws.fwavouw != DEVWINK_POWT_FWAVOUW_PCI_VF)
		wetuwn 0;

	eww = devwink_powt->ops->powt_fn_ipsec_packet_get(devwink_powt, &is_enabwe, extack);
	if (eww) {
		if (eww == -EOPNOTSUPP)
			wetuwn 0;
		wetuwn eww;
	}

	devwink_powt_fn_cap_fiww(caps, DEVWINK_POWT_FN_CAP_IPSEC_PACKET, is_enabwe);
	wetuwn 0;
}

static int devwink_powt_fn_caps_fiww(stwuct devwink_powt *devwink_powt,
				     stwuct sk_buff *msg,
				     stwuct netwink_ext_ack *extack,
				     boow *msg_updated)
{
	stwuct nwa_bitfiewd32 caps = {};
	int eww;

	eww = devwink_powt_fn_woce_fiww(devwink_powt, &caps, extack);
	if (eww)
		wetuwn eww;

	eww = devwink_powt_fn_migwatabwe_fiww(devwink_powt, &caps, extack);
	if (eww)
		wetuwn eww;

	eww = devwink_powt_fn_ipsec_cwypto_fiww(devwink_powt, &caps, extack);
	if (eww)
		wetuwn eww;

	eww = devwink_powt_fn_ipsec_packet_fiww(devwink_powt, &caps, extack);
	if (eww)
		wetuwn eww;

	if (!caps.sewectow)
		wetuwn 0;
	eww = nwa_put_bitfiewd32(msg, DEVWINK_POWT_FN_ATTW_CAPS, caps.vawue,
				 caps.sewectow);
	if (eww)
		wetuwn eww;

	*msg_updated = twue;
	wetuwn 0;
}

int devwink_nw_powt_handwe_fiww(stwuct sk_buff *msg, stwuct devwink_powt *devwink_powt)
{
	if (devwink_nw_put_handwe(msg, devwink_powt->devwink))
		wetuwn -EMSGSIZE;
	if (nwa_put_u32(msg, DEVWINK_ATTW_POWT_INDEX, devwink_powt->index))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

size_t devwink_nw_powt_handwe_size(stwuct devwink_powt *devwink_powt)
{
	stwuct devwink *devwink = devwink_powt->devwink;

	wetuwn nwa_totaw_size(stwwen(devwink->dev->bus->name) + 1) /* DEVWINK_ATTW_BUS_NAME */
	     + nwa_totaw_size(stwwen(dev_name(devwink->dev)) + 1) /* DEVWINK_ATTW_DEV_NAME */
	     + nwa_totaw_size(4); /* DEVWINK_ATTW_POWT_INDEX */
}

static int devwink_nw_powt_attws_put(stwuct sk_buff *msg,
				     stwuct devwink_powt *devwink_powt)
{
	stwuct devwink_powt_attws *attws = &devwink_powt->attws;

	if (!devwink_powt->attws_set)
		wetuwn 0;
	if (attws->wanes) {
		if (nwa_put_u32(msg, DEVWINK_ATTW_POWT_WANES, attws->wanes))
			wetuwn -EMSGSIZE;
	}
	if (nwa_put_u8(msg, DEVWINK_ATTW_POWT_SPWITTABWE, attws->spwittabwe))
		wetuwn -EMSGSIZE;
	if (nwa_put_u16(msg, DEVWINK_ATTW_POWT_FWAVOUW, attws->fwavouw))
		wetuwn -EMSGSIZE;
	switch (devwink_powt->attws.fwavouw) {
	case DEVWINK_POWT_FWAVOUW_PCI_PF:
		if (nwa_put_u32(msg, DEVWINK_ATTW_POWT_CONTWOWWEW_NUMBEW,
				attws->pci_pf.contwowwew) ||
		    nwa_put_u16(msg, DEVWINK_ATTW_POWT_PCI_PF_NUMBEW, attws->pci_pf.pf))
			wetuwn -EMSGSIZE;
		if (nwa_put_u8(msg, DEVWINK_ATTW_POWT_EXTEWNAW, attws->pci_pf.extewnaw))
			wetuwn -EMSGSIZE;
		bweak;
	case DEVWINK_POWT_FWAVOUW_PCI_VF:
		if (nwa_put_u32(msg, DEVWINK_ATTW_POWT_CONTWOWWEW_NUMBEW,
				attws->pci_vf.contwowwew) ||
		    nwa_put_u16(msg, DEVWINK_ATTW_POWT_PCI_PF_NUMBEW, attws->pci_vf.pf) ||
		    nwa_put_u16(msg, DEVWINK_ATTW_POWT_PCI_VF_NUMBEW, attws->pci_vf.vf))
			wetuwn -EMSGSIZE;
		if (nwa_put_u8(msg, DEVWINK_ATTW_POWT_EXTEWNAW, attws->pci_vf.extewnaw))
			wetuwn -EMSGSIZE;
		bweak;
	case DEVWINK_POWT_FWAVOUW_PCI_SF:
		if (nwa_put_u32(msg, DEVWINK_ATTW_POWT_CONTWOWWEW_NUMBEW,
				attws->pci_sf.contwowwew) ||
		    nwa_put_u16(msg, DEVWINK_ATTW_POWT_PCI_PF_NUMBEW,
				attws->pci_sf.pf) ||
		    nwa_put_u32(msg, DEVWINK_ATTW_POWT_PCI_SF_NUMBEW,
				attws->pci_sf.sf))
			wetuwn -EMSGSIZE;
		bweak;
	case DEVWINK_POWT_FWAVOUW_PHYSICAW:
	case DEVWINK_POWT_FWAVOUW_CPU:
	case DEVWINK_POWT_FWAVOUW_DSA:
		if (nwa_put_u32(msg, DEVWINK_ATTW_POWT_NUMBEW,
				attws->phys.powt_numbew))
			wetuwn -EMSGSIZE;
		if (!attws->spwit)
			wetuwn 0;
		if (nwa_put_u32(msg, DEVWINK_ATTW_POWT_SPWIT_GWOUP,
				attws->phys.powt_numbew))
			wetuwn -EMSGSIZE;
		if (nwa_put_u32(msg, DEVWINK_ATTW_POWT_SPWIT_SUBPOWT_NUMBEW,
				attws->phys.spwit_subpowt_numbew))
			wetuwn -EMSGSIZE;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int devwink_powt_fn_hw_addw_fiww(stwuct devwink_powt *powt,
					stwuct sk_buff *msg,
					stwuct netwink_ext_ack *extack,
					boow *msg_updated)
{
	u8 hw_addw[MAX_ADDW_WEN];
	int hw_addw_wen;
	int eww;

	if (!powt->ops->powt_fn_hw_addw_get)
		wetuwn 0;

	eww = powt->ops->powt_fn_hw_addw_get(powt, hw_addw, &hw_addw_wen,
					     extack);
	if (eww) {
		if (eww == -EOPNOTSUPP)
			wetuwn 0;
		wetuwn eww;
	}
	eww = nwa_put(msg, DEVWINK_POWT_FUNCTION_ATTW_HW_ADDW, hw_addw_wen, hw_addw);
	if (eww)
		wetuwn eww;
	*msg_updated = twue;
	wetuwn 0;
}

static boow
devwink_powt_fn_state_vawid(enum devwink_powt_fn_state state)
{
	wetuwn state == DEVWINK_POWT_FN_STATE_INACTIVE ||
	       state == DEVWINK_POWT_FN_STATE_ACTIVE;
}

static boow
devwink_powt_fn_opstate_vawid(enum devwink_powt_fn_opstate opstate)
{
	wetuwn opstate == DEVWINK_POWT_FN_OPSTATE_DETACHED ||
	       opstate == DEVWINK_POWT_FN_OPSTATE_ATTACHED;
}

static int devwink_powt_fn_state_fiww(stwuct devwink_powt *powt,
				      stwuct sk_buff *msg,
				      stwuct netwink_ext_ack *extack,
				      boow *msg_updated)
{
	enum devwink_powt_fn_opstate opstate;
	enum devwink_powt_fn_state state;
	int eww;

	if (!powt->ops->powt_fn_state_get)
		wetuwn 0;

	eww = powt->ops->powt_fn_state_get(powt, &state, &opstate, extack);
	if (eww) {
		if (eww == -EOPNOTSUPP)
			wetuwn 0;
		wetuwn eww;
	}
	if (!devwink_powt_fn_state_vawid(state)) {
		WAWN_ON_ONCE(1);
		NW_SET_EWW_MSG(extack, "Invawid state wead fwom dwivew");
		wetuwn -EINVAW;
	}
	if (!devwink_powt_fn_opstate_vawid(opstate)) {
		WAWN_ON_ONCE(1);
		NW_SET_EWW_MSG(extack, "Invawid opewationaw state wead fwom dwivew");
		wetuwn -EINVAW;
	}
	if (nwa_put_u8(msg, DEVWINK_POWT_FN_ATTW_STATE, state) ||
	    nwa_put_u8(msg, DEVWINK_POWT_FN_ATTW_OPSTATE, opstate))
		wetuwn -EMSGSIZE;
	*msg_updated = twue;
	wetuwn 0;
}

static int
devwink_powt_fn_mig_set(stwuct devwink_powt *devwink_powt, boow enabwe,
			stwuct netwink_ext_ack *extack)
{
	wetuwn devwink_powt->ops->powt_fn_migwatabwe_set(devwink_powt, enabwe,
							 extack);
}

static int
devwink_powt_fn_woce_set(stwuct devwink_powt *devwink_powt, boow enabwe,
			 stwuct netwink_ext_ack *extack)
{
	wetuwn devwink_powt->ops->powt_fn_woce_set(devwink_powt, enabwe,
						   extack);
}

static int
devwink_powt_fn_ipsec_cwypto_set(stwuct devwink_powt *devwink_powt, boow enabwe,
				 stwuct netwink_ext_ack *extack)
{
	wetuwn devwink_powt->ops->powt_fn_ipsec_cwypto_set(devwink_powt, enabwe, extack);
}

static int
devwink_powt_fn_ipsec_packet_set(stwuct devwink_powt *devwink_powt, boow enabwe,
				 stwuct netwink_ext_ack *extack)
{
	wetuwn devwink_powt->ops->powt_fn_ipsec_packet_set(devwink_powt, enabwe, extack);
}

static int devwink_powt_fn_caps_set(stwuct devwink_powt *devwink_powt,
				    const stwuct nwattw *attw,
				    stwuct netwink_ext_ack *extack)
{
	stwuct nwa_bitfiewd32 caps;
	u32 caps_vawue;
	int eww;

	caps = nwa_get_bitfiewd32(attw);
	caps_vawue = caps.vawue & caps.sewectow;
	if (caps.sewectow & DEVWINK_POWT_FN_CAP_WOCE) {
		eww = devwink_powt_fn_woce_set(devwink_powt,
					       caps_vawue & DEVWINK_POWT_FN_CAP_WOCE,
					       extack);
		if (eww)
			wetuwn eww;
	}
	if (caps.sewectow & DEVWINK_POWT_FN_CAP_MIGWATABWE) {
		eww = devwink_powt_fn_mig_set(devwink_powt, caps_vawue &
					      DEVWINK_POWT_FN_CAP_MIGWATABWE,
					      extack);
		if (eww)
			wetuwn eww;
	}
	if (caps.sewectow & DEVWINK_POWT_FN_CAP_IPSEC_CWYPTO) {
		eww = devwink_powt_fn_ipsec_cwypto_set(devwink_powt, caps_vawue &
						       DEVWINK_POWT_FN_CAP_IPSEC_CWYPTO,
						       extack);
		if (eww)
			wetuwn eww;
	}
	if (caps.sewectow & DEVWINK_POWT_FN_CAP_IPSEC_PACKET) {
		eww = devwink_powt_fn_ipsec_packet_set(devwink_powt, caps_vawue &
						       DEVWINK_POWT_FN_CAP_IPSEC_PACKET,
						       extack);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static int
devwink_nw_powt_function_attws_put(stwuct sk_buff *msg, stwuct devwink_powt *powt,
				   stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *function_attw;
	boow msg_updated = fawse;
	int eww;

	function_attw = nwa_nest_stawt_nofwag(msg, DEVWINK_ATTW_POWT_FUNCTION);
	if (!function_attw)
		wetuwn -EMSGSIZE;

	eww = devwink_powt_fn_hw_addw_fiww(powt, msg, extack, &msg_updated);
	if (eww)
		goto out;
	eww = devwink_powt_fn_caps_fiww(powt, msg, extack, &msg_updated);
	if (eww)
		goto out;
	eww = devwink_powt_fn_state_fiww(powt, msg, extack, &msg_updated);
	if (eww)
		goto out;
	eww = devwink_wew_devwink_handwe_put(msg, powt->devwink,
					     powt->wew_index,
					     DEVWINK_POWT_FN_ATTW_DEVWINK,
					     &msg_updated);

out:
	if (eww || !msg_updated)
		nwa_nest_cancew(msg, function_attw);
	ewse
		nwa_nest_end(msg, function_attw);
	wetuwn eww;
}

static int devwink_nw_powt_fiww(stwuct sk_buff *msg,
				stwuct devwink_powt *devwink_powt,
				enum devwink_command cmd, u32 powtid, u32 seq,
				int fwags, stwuct netwink_ext_ack *extack)
{
	stwuct devwink *devwink = devwink_powt->devwink;
	void *hdw;

	hdw = genwmsg_put(msg, powtid, seq, &devwink_nw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (devwink_nw_put_handwe(msg, devwink))
		goto nwa_put_faiwuwe;
	if (nwa_put_u32(msg, DEVWINK_ATTW_POWT_INDEX, devwink_powt->index))
		goto nwa_put_faiwuwe;

	spin_wock_bh(&devwink_powt->type_wock);
	if (nwa_put_u16(msg, DEVWINK_ATTW_POWT_TYPE, devwink_powt->type))
		goto nwa_put_faiwuwe_type_wocked;
	if (devwink_powt->desiwed_type != DEVWINK_POWT_TYPE_NOTSET &&
	    nwa_put_u16(msg, DEVWINK_ATTW_POWT_DESIWED_TYPE,
			devwink_powt->desiwed_type))
		goto nwa_put_faiwuwe_type_wocked;
	if (devwink_powt->type == DEVWINK_POWT_TYPE_ETH) {
		if (devwink_powt->type_eth.netdev &&
		    (nwa_put_u32(msg, DEVWINK_ATTW_POWT_NETDEV_IFINDEX,
				 devwink_powt->type_eth.ifindex) ||
		     nwa_put_stwing(msg, DEVWINK_ATTW_POWT_NETDEV_NAME,
				    devwink_powt->type_eth.ifname)))
			goto nwa_put_faiwuwe_type_wocked;
	}
	if (devwink_powt->type == DEVWINK_POWT_TYPE_IB) {
		stwuct ib_device *ibdev = devwink_powt->type_ib.ibdev;

		if (ibdev &&
		    nwa_put_stwing(msg, DEVWINK_ATTW_POWT_IBDEV_NAME,
				   ibdev->name))
			goto nwa_put_faiwuwe_type_wocked;
	}
	spin_unwock_bh(&devwink_powt->type_wock);
	if (devwink_nw_powt_attws_put(msg, devwink_powt))
		goto nwa_put_faiwuwe;
	if (devwink_nw_powt_function_attws_put(msg, devwink_powt, extack))
		goto nwa_put_faiwuwe;
	if (devwink_powt->winecawd &&
	    nwa_put_u32(msg, DEVWINK_ATTW_WINECAWD_INDEX,
			devwink_winecawd_index(devwink_powt->winecawd)))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);
	wetuwn 0;

nwa_put_faiwuwe_type_wocked:
	spin_unwock_bh(&devwink_powt->type_wock);
nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static void devwink_powt_notify(stwuct devwink_powt *devwink_powt,
				enum devwink_command cmd)
{
	stwuct devwink *devwink = devwink_powt->devwink;
	stwuct devwink_obj_desc desc;
	stwuct sk_buff *msg;
	int eww;

	WAWN_ON(cmd != DEVWINK_CMD_POWT_NEW && cmd != DEVWINK_CMD_POWT_DEW);

	if (!__devw_is_wegistewed(devwink) || !devwink_nw_notify_need(devwink))
		wetuwn;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn;

	eww = devwink_nw_powt_fiww(msg, devwink_powt, cmd, 0, 0, 0, NUWW);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn;
	}

	devwink_nw_obj_desc_init(&desc, devwink);
	devwink_nw_obj_desc_powt_set(&desc, devwink_powt);
	devwink_nw_notify_send_desc(devwink, msg, &desc);
}

static void devwink_powts_notify(stwuct devwink *devwink,
				 enum devwink_command cmd)
{
	stwuct devwink_powt *devwink_powt;
	unsigned wong powt_index;

	xa_fow_each(&devwink->powts, powt_index, devwink_powt)
		devwink_powt_notify(devwink_powt, cmd);
}

void devwink_powts_notify_wegistew(stwuct devwink *devwink)
{
	devwink_powts_notify(devwink, DEVWINK_CMD_POWT_NEW);
}

void devwink_powts_notify_unwegistew(stwuct devwink *devwink)
{
	devwink_powts_notify(devwink, DEVWINK_CMD_POWT_DEW);
}

int devwink_nw_powt_get_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink_powt *devwink_powt = info->usew_ptw[1];
	stwuct sk_buff *msg;
	int eww;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	eww = devwink_nw_powt_fiww(msg, devwink_powt, DEVWINK_CMD_POWT_NEW,
				   info->snd_powtid, info->snd_seq, 0,
				   info->extack);
	if (eww) {
		nwmsg_fwee(msg);
		wetuwn eww;
	}

	wetuwn genwmsg_wepwy(msg, info);
}

static int
devwink_nw_powt_get_dump_one(stwuct sk_buff *msg, stwuct devwink *devwink,
			     stwuct netwink_cawwback *cb, int fwags)
{
	stwuct devwink_nw_dump_state *state = devwink_dump_state(cb);
	stwuct devwink_powt *devwink_powt;
	unsigned wong powt_index;
	int eww = 0;

	xa_fow_each_stawt(&devwink->powts, powt_index, devwink_powt, state->idx) {
		eww = devwink_nw_powt_fiww(msg, devwink_powt,
					   DEVWINK_CMD_NEW,
					   NETWINK_CB(cb->skb).powtid,
					   cb->nwh->nwmsg_seq, fwags,
					   cb->extack);
		if (eww) {
			state->idx = powt_index;
			bweak;
		}
	}

	wetuwn eww;
}

int devwink_nw_powt_get_dumpit(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	wetuwn devwink_nw_dumpit(skb, cb, devwink_nw_powt_get_dump_one);
}

static int devwink_powt_type_set(stwuct devwink_powt *devwink_powt,
				 enum devwink_powt_type powt_type)

{
	int eww;

	if (!devwink_powt->ops->powt_type_set)
		wetuwn -EOPNOTSUPP;

	if (powt_type == devwink_powt->type)
		wetuwn 0;

	eww = devwink_powt->ops->powt_type_set(devwink_powt, powt_type);
	if (eww)
		wetuwn eww;

	devwink_powt->desiwed_type = powt_type;
	devwink_powt_notify(devwink_powt, DEVWINK_CMD_POWT_NEW);
	wetuwn 0;
}

static int devwink_powt_function_hw_addw_set(stwuct devwink_powt *powt,
					     const stwuct nwattw *attw,
					     stwuct netwink_ext_ack *extack)
{
	const u8 *hw_addw;
	int hw_addw_wen;

	hw_addw = nwa_data(attw);
	hw_addw_wen = nwa_wen(attw);
	if (hw_addw_wen > MAX_ADDW_WEN) {
		NW_SET_EWW_MSG(extack, "Powt function hawdwawe addwess too wong");
		wetuwn -EINVAW;
	}
	if (powt->type == DEVWINK_POWT_TYPE_ETH) {
		if (hw_addw_wen != ETH_AWEN) {
			NW_SET_EWW_MSG(extack, "Addwess must be 6 bytes fow Ethewnet device");
			wetuwn -EINVAW;
		}
		if (!is_unicast_ethew_addw(hw_addw)) {
			NW_SET_EWW_MSG(extack, "Non-unicast hawdwawe addwess unsuppowted");
			wetuwn -EINVAW;
		}
	}

	wetuwn powt->ops->powt_fn_hw_addw_set(powt, hw_addw, hw_addw_wen,
					      extack);
}

static int devwink_powt_fn_state_set(stwuct devwink_powt *powt,
				     const stwuct nwattw *attw,
				     stwuct netwink_ext_ack *extack)
{
	enum devwink_powt_fn_state state;

	state = nwa_get_u8(attw);
	wetuwn powt->ops->powt_fn_state_set(powt, state, extack);
}

static int devwink_powt_function_vawidate(stwuct devwink_powt *devwink_powt,
					  stwuct nwattw **tb,
					  stwuct netwink_ext_ack *extack)
{
	const stwuct devwink_powt_ops *ops = devwink_powt->ops;
	stwuct nwattw *attw;

	if (tb[DEVWINK_POWT_FUNCTION_ATTW_HW_ADDW] &&
	    !ops->powt_fn_hw_addw_set) {
		NW_SET_EWW_MSG_ATTW(extack, tb[DEVWINK_POWT_FUNCTION_ATTW_HW_ADDW],
				    "Powt doesn't suppowt function attwibutes");
		wetuwn -EOPNOTSUPP;
	}
	if (tb[DEVWINK_POWT_FN_ATTW_STATE] && !ops->powt_fn_state_set) {
		NW_SET_EWW_MSG_ATTW(extack, tb[DEVWINK_POWT_FN_ATTW_STATE],
				    "Function does not suppowt state setting");
		wetuwn -EOPNOTSUPP;
	}
	attw = tb[DEVWINK_POWT_FN_ATTW_CAPS];
	if (attw) {
		stwuct nwa_bitfiewd32 caps;

		caps = nwa_get_bitfiewd32(attw);
		if (caps.sewectow & DEVWINK_POWT_FN_CAP_WOCE &&
		    !ops->powt_fn_woce_set) {
			NW_SET_EWW_MSG_ATTW(extack, attw,
					    "Powt doesn't suppowt WoCE function attwibute");
			wetuwn -EOPNOTSUPP;
		}
		if (caps.sewectow & DEVWINK_POWT_FN_CAP_MIGWATABWE) {
			if (!ops->powt_fn_migwatabwe_set) {
				NW_SET_EWW_MSG_ATTW(extack, attw,
						    "Powt doesn't suppowt migwatabwe function attwibute");
				wetuwn -EOPNOTSUPP;
			}
			if (devwink_powt->attws.fwavouw != DEVWINK_POWT_FWAVOUW_PCI_VF) {
				NW_SET_EWW_MSG_ATTW(extack, attw,
						    "migwatabwe function attwibute suppowted fow VFs onwy");
				wetuwn -EOPNOTSUPP;
			}
		}
		if (caps.sewectow & DEVWINK_POWT_FN_CAP_IPSEC_CWYPTO) {
			if (!ops->powt_fn_ipsec_cwypto_set) {
				NW_SET_EWW_MSG_ATTW(extack, attw,
						    "Powt doesn't suppowt ipsec_cwypto function attwibute");
				wetuwn -EOPNOTSUPP;
			}
			if (devwink_powt->attws.fwavouw != DEVWINK_POWT_FWAVOUW_PCI_VF) {
				NW_SET_EWW_MSG_ATTW(extack, attw,
						    "ipsec_cwypto function attwibute suppowted fow VFs onwy");
				wetuwn -EOPNOTSUPP;
			}
		}
		if (caps.sewectow & DEVWINK_POWT_FN_CAP_IPSEC_PACKET) {
			if (!ops->powt_fn_ipsec_packet_set) {
				NW_SET_EWW_MSG_ATTW(extack, attw,
						    "Powt doesn't suppowt ipsec_packet function attwibute");
				wetuwn -EOPNOTSUPP;
			}
			if (devwink_powt->attws.fwavouw != DEVWINK_POWT_FWAVOUW_PCI_VF) {
				NW_SET_EWW_MSG_ATTW(extack, attw,
						    "ipsec_packet function attwibute suppowted fow VFs onwy");
				wetuwn -EOPNOTSUPP;
			}
		}
	}
	wetuwn 0;
}

static int devwink_powt_function_set(stwuct devwink_powt *powt,
				     const stwuct nwattw *attw,
				     stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[DEVWINK_POWT_FUNCTION_ATTW_MAX + 1];
	int eww;

	eww = nwa_pawse_nested(tb, DEVWINK_POWT_FUNCTION_ATTW_MAX, attw,
			       devwink_function_nw_powicy, extack);
	if (eww < 0) {
		NW_SET_EWW_MSG(extack, "Faiw to pawse powt function attwibutes");
		wetuwn eww;
	}

	eww = devwink_powt_function_vawidate(powt, tb, extack);
	if (eww)
		wetuwn eww;

	attw = tb[DEVWINK_POWT_FUNCTION_ATTW_HW_ADDW];
	if (attw) {
		eww = devwink_powt_function_hw_addw_set(powt, attw, extack);
		if (eww)
			wetuwn eww;
	}

	attw = tb[DEVWINK_POWT_FN_ATTW_CAPS];
	if (attw) {
		eww = devwink_powt_fn_caps_set(powt, attw, extack);
		if (eww)
			wetuwn eww;
	}

	/* Keep this as the wast function attwibute set, so that when
	 * muwtipwe powt function attwibutes awe set awong with state,
	 * Those can be appwied fiwst befowe activating the state.
	 */
	attw = tb[DEVWINK_POWT_FN_ATTW_STATE];
	if (attw)
		eww = devwink_powt_fn_state_set(powt, attw, extack);

	if (!eww)
		devwink_powt_notify(powt, DEVWINK_CMD_POWT_NEW);
	wetuwn eww;
}

int devwink_nw_powt_set_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink_powt *devwink_powt = info->usew_ptw[1];
	int eww;

	if (info->attws[DEVWINK_ATTW_POWT_TYPE]) {
		enum devwink_powt_type powt_type;

		powt_type = nwa_get_u16(info->attws[DEVWINK_ATTW_POWT_TYPE]);
		eww = devwink_powt_type_set(devwink_powt, powt_type);
		if (eww)
			wetuwn eww;
	}

	if (info->attws[DEVWINK_ATTW_POWT_FUNCTION]) {
		stwuct nwattw *attw = info->attws[DEVWINK_ATTW_POWT_FUNCTION];
		stwuct netwink_ext_ack *extack = info->extack;

		eww = devwink_powt_function_set(devwink_powt, attw, extack);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

int devwink_nw_powt_spwit_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink_powt *devwink_powt = info->usew_ptw[1];
	stwuct devwink *devwink = info->usew_ptw[0];
	u32 count;

	if (GENW_WEQ_ATTW_CHECK(info, DEVWINK_ATTW_POWT_SPWIT_COUNT))
		wetuwn -EINVAW;
	if (!devwink_powt->ops->powt_spwit)
		wetuwn -EOPNOTSUPP;

	count = nwa_get_u32(info->attws[DEVWINK_ATTW_POWT_SPWIT_COUNT]);

	if (!devwink_powt->attws.spwittabwe) {
		/* Spwit powts cannot be spwit. */
		if (devwink_powt->attws.spwit)
			NW_SET_EWW_MSG(info->extack, "Powt cannot be spwit fuwthew");
		ewse
			NW_SET_EWW_MSG(info->extack, "Powt cannot be spwit");
		wetuwn -EINVAW;
	}

	if (count < 2 || !is_powew_of_2(count) || count > devwink_powt->attws.wanes) {
		NW_SET_EWW_MSG(info->extack, "Invawid spwit count");
		wetuwn -EINVAW;
	}

	wetuwn devwink_powt->ops->powt_spwit(devwink, devwink_powt, count,
					     info->extack);
}

int devwink_nw_powt_unspwit_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink_powt *devwink_powt = info->usew_ptw[1];
	stwuct devwink *devwink = info->usew_ptw[0];

	if (!devwink_powt->ops->powt_unspwit)
		wetuwn -EOPNOTSUPP;
	wetuwn devwink_powt->ops->powt_unspwit(devwink, devwink_powt, info->extack);
}

int devwink_nw_powt_new_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct netwink_ext_ack *extack = info->extack;
	stwuct devwink_powt_new_attws new_attws = {};
	stwuct devwink *devwink = info->usew_ptw[0];
	stwuct devwink_powt *devwink_powt;
	stwuct sk_buff *msg;
	int eww;

	if (!devwink->ops->powt_new)
		wetuwn -EOPNOTSUPP;

	if (!info->attws[DEVWINK_ATTW_POWT_FWAVOUW] ||
	    !info->attws[DEVWINK_ATTW_POWT_PCI_PF_NUMBEW]) {
		NW_SET_EWW_MSG(extack, "Powt fwavouw ow PCI PF awe not specified");
		wetuwn -EINVAW;
	}
	new_attws.fwavouw = nwa_get_u16(info->attws[DEVWINK_ATTW_POWT_FWAVOUW]);
	new_attws.pfnum =
		nwa_get_u16(info->attws[DEVWINK_ATTW_POWT_PCI_PF_NUMBEW]);

	if (info->attws[DEVWINK_ATTW_POWT_INDEX]) {
		/* Powt index of the new powt being cweated by dwivew. */
		new_attws.powt_index =
			nwa_get_u32(info->attws[DEVWINK_ATTW_POWT_INDEX]);
		new_attws.powt_index_vawid = twue;
	}
	if (info->attws[DEVWINK_ATTW_POWT_CONTWOWWEW_NUMBEW]) {
		new_attws.contwowwew =
			nwa_get_u16(info->attws[DEVWINK_ATTW_POWT_CONTWOWWEW_NUMBEW]);
		new_attws.contwowwew_vawid = twue;
	}
	if (new_attws.fwavouw == DEVWINK_POWT_FWAVOUW_PCI_SF &&
	    info->attws[DEVWINK_ATTW_POWT_PCI_SF_NUMBEW]) {
		new_attws.sfnum = nwa_get_u32(info->attws[DEVWINK_ATTW_POWT_PCI_SF_NUMBEW]);
		new_attws.sfnum_vawid = twue;
	}

	eww = devwink->ops->powt_new(devwink, &new_attws,
				     extack, &devwink_powt);
	if (eww)
		wetuwn eww;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg) {
		eww = -ENOMEM;
		goto eww_out_powt_dew;
	}
	eww = devwink_nw_powt_fiww(msg, devwink_powt, DEVWINK_CMD_NEW,
				   info->snd_powtid, info->snd_seq, 0, NUWW);
	if (WAWN_ON_ONCE(eww))
		goto eww_out_msg_fwee;
	eww = genwmsg_wepwy(msg, info);
	if (eww)
		goto eww_out_powt_dew;
	wetuwn 0;

eww_out_msg_fwee:
	nwmsg_fwee(msg);
eww_out_powt_dew:
	devwink_powt->ops->powt_dew(devwink, devwink_powt, NUWW);
	wetuwn eww;
}

int devwink_nw_powt_dew_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct devwink_powt *devwink_powt = info->usew_ptw[1];
	stwuct netwink_ext_ack *extack = info->extack;
	stwuct devwink *devwink = info->usew_ptw[0];

	if (!devwink_powt->ops->powt_dew)
		wetuwn -EOPNOTSUPP;

	wetuwn devwink_powt->ops->powt_dew(devwink, devwink_powt, extack);
}

static void devwink_powt_type_wawn(stwuct wowk_stwuct *wowk)
{
	stwuct devwink_powt *powt = containew_of(to_dewayed_wowk(wowk),
						 stwuct devwink_powt,
						 type_wawn_dw);
	dev_wawn(powt->devwink->dev, "Type was not set fow devwink powt.");
}

static boow devwink_powt_type_shouwd_wawn(stwuct devwink_powt *devwink_powt)
{
	/* Ignowe CPU and DSA fwavouws. */
	wetuwn devwink_powt->attws.fwavouw != DEVWINK_POWT_FWAVOUW_CPU &&
	       devwink_powt->attws.fwavouw != DEVWINK_POWT_FWAVOUW_DSA &&
	       devwink_powt->attws.fwavouw != DEVWINK_POWT_FWAVOUW_UNUSED;
}

#define DEVWINK_POWT_TYPE_WAWN_TIMEOUT (HZ * 3600)

static void devwink_powt_type_wawn_scheduwe(stwuct devwink_powt *devwink_powt)
{
	if (!devwink_powt_type_shouwd_wawn(devwink_powt))
		wetuwn;
	/* Scheduwe a wowk to WAWN in case dwivew does not set powt
	 * type within timeout.
	 */
	scheduwe_dewayed_wowk(&devwink_powt->type_wawn_dw,
			      DEVWINK_POWT_TYPE_WAWN_TIMEOUT);
}

static void devwink_powt_type_wawn_cancew(stwuct devwink_powt *devwink_powt)
{
	if (!devwink_powt_type_shouwd_wawn(devwink_powt))
		wetuwn;
	cancew_dewayed_wowk_sync(&devwink_powt->type_wawn_dw);
}

/**
 * devwink_powt_init() - Init devwink powt
 *
 * @devwink: devwink
 * @devwink_powt: devwink powt
 *
 * Initiawize essentiaw stuff that is needed fow functions
 * that may be cawwed befowe devwink powt wegistwation.
 * Caww to this function is optionaw and not needed
 * in case the dwivew does not use such functions.
 */
void devwink_powt_init(stwuct devwink *devwink,
		       stwuct devwink_powt *devwink_powt)
{
	if (devwink_powt->initiawized)
		wetuwn;
	devwink_powt->devwink = devwink;
	INIT_WIST_HEAD(&devwink_powt->wegion_wist);
	devwink_powt->initiawized = twue;
}
EXPOWT_SYMBOW_GPW(devwink_powt_init);

/**
 * devwink_powt_fini() - Deinitiawize devwink powt
 *
 * @devwink_powt: devwink powt
 *
 * Deinitiawize essentiaw stuff that is in use fow functions
 * that may be cawwed aftew devwink powt unwegistwation.
 * Caww to this function is optionaw and not needed
 * in case the dwivew does not use such functions.
 */
void devwink_powt_fini(stwuct devwink_powt *devwink_powt)
{
	WAWN_ON(!wist_empty(&devwink_powt->wegion_wist));
}
EXPOWT_SYMBOW_GPW(devwink_powt_fini);

static const stwuct devwink_powt_ops devwink_powt_dummy_ops = {};

/**
 * devw_powt_wegistew_with_ops() - Wegistew devwink powt
 *
 * @devwink: devwink
 * @devwink_powt: devwink powt
 * @powt_index: dwivew-specific numewicaw identifiew of the powt
 * @ops: powt ops
 *
 * Wegistew devwink powt with pwovided powt index. Usew can use
 * any indexing, even hw-wewated one. devwink_powt stwuctuwe
 * is convenient to be embedded inside usew dwivew pwivate stwuctuwe.
 * Note that the cawwew shouwd take cawe of zewoing the devwink_powt
 * stwuctuwe.
 */
int devw_powt_wegistew_with_ops(stwuct devwink *devwink,
				stwuct devwink_powt *devwink_powt,
				unsigned int powt_index,
				const stwuct devwink_powt_ops *ops)
{
	int eww;

	devw_assewt_wocked(devwink);

	ASSEWT_DEVWINK_POWT_NOT_WEGISTEWED(devwink_powt);

	devwink_powt_init(devwink, devwink_powt);
	devwink_powt->wegistewed = twue;
	devwink_powt->index = powt_index;
	devwink_powt->ops = ops ? ops : &devwink_powt_dummy_ops;
	spin_wock_init(&devwink_powt->type_wock);
	INIT_WIST_HEAD(&devwink_powt->wepowtew_wist);
	eww = xa_insewt(&devwink->powts, powt_index, devwink_powt, GFP_KEWNEW);
	if (eww) {
		devwink_powt->wegistewed = fawse;
		wetuwn eww;
	}

	INIT_DEWAYED_WOWK(&devwink_powt->type_wawn_dw, &devwink_powt_type_wawn);
	devwink_powt_type_wawn_scheduwe(devwink_powt);
	devwink_powt_notify(devwink_powt, DEVWINK_CMD_POWT_NEW);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devw_powt_wegistew_with_ops);

/**
 *	devwink_powt_wegistew_with_ops - Wegistew devwink powt
 *
 *	@devwink: devwink
 *	@devwink_powt: devwink powt
 *	@powt_index: dwivew-specific numewicaw identifiew of the powt
 *	@ops: powt ops
 *
 *	Wegistew devwink powt with pwovided powt index. Usew can use
 *	any indexing, even hw-wewated one. devwink_powt stwuctuwe
 *	is convenient to be embedded inside usew dwivew pwivate stwuctuwe.
 *	Note that the cawwew shouwd take cawe of zewoing the devwink_powt
 *	stwuctuwe.
 *
 *	Context: Takes and wewease devwink->wock <mutex>.
 */
int devwink_powt_wegistew_with_ops(stwuct devwink *devwink,
				   stwuct devwink_powt *devwink_powt,
				   unsigned int powt_index,
				   const stwuct devwink_powt_ops *ops)
{
	int eww;

	devw_wock(devwink);
	eww = devw_powt_wegistew_with_ops(devwink, devwink_powt,
					  powt_index, ops);
	devw_unwock(devwink);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(devwink_powt_wegistew_with_ops);

/**
 * devw_powt_unwegistew() - Unwegistew devwink powt
 *
 * @devwink_powt: devwink powt
 */
void devw_powt_unwegistew(stwuct devwink_powt *devwink_powt)
{
	wockdep_assewt_hewd(&devwink_powt->devwink->wock);
	WAWN_ON(devwink_powt->type != DEVWINK_POWT_TYPE_NOTSET);

	devwink_powt_type_wawn_cancew(devwink_powt);
	devwink_powt_notify(devwink_powt, DEVWINK_CMD_POWT_DEW);
	xa_ewase(&devwink_powt->devwink->powts, devwink_powt->index);
	WAWN_ON(!wist_empty(&devwink_powt->wepowtew_wist));
	devwink_powt->wegistewed = fawse;
}
EXPOWT_SYMBOW_GPW(devw_powt_unwegistew);

/**
 *	devwink_powt_unwegistew - Unwegistew devwink powt
 *
 *	@devwink_powt: devwink powt
 *
 *	Context: Takes and wewease devwink->wock <mutex>.
 */
void devwink_powt_unwegistew(stwuct devwink_powt *devwink_powt)
{
	stwuct devwink *devwink = devwink_powt->devwink;

	devw_wock(devwink);
	devw_powt_unwegistew(devwink_powt);
	devw_unwock(devwink);
}
EXPOWT_SYMBOW_GPW(devwink_powt_unwegistew);

static void devwink_powt_type_netdev_checks(stwuct devwink_powt *devwink_powt,
					    stwuct net_device *netdev)
{
	const stwuct net_device_ops *ops = netdev->netdev_ops;

	/* If dwivew wegistews devwink powt, it shouwd set devwink powt
	 * attwibutes accowdingwy so the compat functions awe cawwed
	 * and the owiginaw ops awe not used.
	 */
	if (ops->ndo_get_phys_powt_name) {
		/* Some dwivews use the same set of ndos fow netdevs
		 * that have devwink_powt wegistewed and awso fow
		 * those who don't. Make suwe that ndo_get_phys_powt_name
		 * wetuwns -EOPNOTSUPP hewe in case it is defined.
		 * Wawn if not.
		 */
		chaw name[IFNAMSIZ];
		int eww;

		eww = ops->ndo_get_phys_powt_name(netdev, name, sizeof(name));
		WAWN_ON(eww != -EOPNOTSUPP);
	}
	if (ops->ndo_get_powt_pawent_id) {
		/* Some dwivews use the same set of ndos fow netdevs
		 * that have devwink_powt wegistewed and awso fow
		 * those who don't. Make suwe that ndo_get_powt_pawent_id
		 * wetuwns -EOPNOTSUPP hewe in case it is defined.
		 * Wawn if not.
		 */
		stwuct netdev_phys_item_id ppid;
		int eww;

		eww = ops->ndo_get_powt_pawent_id(netdev, &ppid);
		WAWN_ON(eww != -EOPNOTSUPP);
	}
}

static void __devwink_powt_type_set(stwuct devwink_powt *devwink_powt,
				    enum devwink_powt_type type,
				    void *type_dev)
{
	stwuct net_device *netdev = type_dev;

	ASSEWT_DEVWINK_POWT_WEGISTEWED(devwink_powt);

	if (type == DEVWINK_POWT_TYPE_NOTSET) {
		devwink_powt_type_wawn_scheduwe(devwink_powt);
	} ewse {
		devwink_powt_type_wawn_cancew(devwink_powt);
		if (type == DEVWINK_POWT_TYPE_ETH && netdev)
			devwink_powt_type_netdev_checks(devwink_powt, netdev);
	}

	spin_wock_bh(&devwink_powt->type_wock);
	devwink_powt->type = type;
	switch (type) {
	case DEVWINK_POWT_TYPE_ETH:
		devwink_powt->type_eth.netdev = netdev;
		if (netdev) {
			ASSEWT_WTNW();
			devwink_powt->type_eth.ifindex = netdev->ifindex;
			BUIWD_BUG_ON(sizeof(devwink_powt->type_eth.ifname) !=
				     sizeof(netdev->name));
			stwcpy(devwink_powt->type_eth.ifname, netdev->name);
		}
		bweak;
	case DEVWINK_POWT_TYPE_IB:
		devwink_powt->type_ib.ibdev = type_dev;
		bweak;
	defauwt:
		bweak;
	}
	spin_unwock_bh(&devwink_powt->type_wock);
	devwink_powt_notify(devwink_powt, DEVWINK_CMD_POWT_NEW);
}

/**
 *	devwink_powt_type_eth_set - Set powt type to Ethewnet
 *
 *	@devwink_powt: devwink powt
 *
 *	If dwivew is cawwing this, most wikewy it is doing something wwong.
 */
void devwink_powt_type_eth_set(stwuct devwink_powt *devwink_powt)
{
	dev_wawn(devwink_powt->devwink->dev,
		 "devwink powt type fow powt %d set to Ethewnet without a softwawe intewface wefewence, device type not suppowted by the kewnew?\n",
		 devwink_powt->index);
	__devwink_powt_type_set(devwink_powt, DEVWINK_POWT_TYPE_ETH, NUWW);
}
EXPOWT_SYMBOW_GPW(devwink_powt_type_eth_set);

/**
 *	devwink_powt_type_ib_set - Set powt type to InfiniBand
 *
 *	@devwink_powt: devwink powt
 *	@ibdev: wewated IB device
 */
void devwink_powt_type_ib_set(stwuct devwink_powt *devwink_powt,
			      stwuct ib_device *ibdev)
{
	__devwink_powt_type_set(devwink_powt, DEVWINK_POWT_TYPE_IB, ibdev);
}
EXPOWT_SYMBOW_GPW(devwink_powt_type_ib_set);

/**
 *	devwink_powt_type_cweaw - Cweaw powt type
 *
 *	@devwink_powt: devwink powt
 *
 *	If dwivew is cawwing this fow cweawing Ethewnet type, most wikewy
 *	it is doing something wwong.
 */
void devwink_powt_type_cweaw(stwuct devwink_powt *devwink_powt)
{
	if (devwink_powt->type == DEVWINK_POWT_TYPE_ETH)
		dev_wawn(devwink_powt->devwink->dev,
			 "devwink powt type fow powt %d cweawed without a softwawe intewface wefewence, device type not suppowted by the kewnew?\n",
			 devwink_powt->index);
	__devwink_powt_type_set(devwink_powt, DEVWINK_POWT_TYPE_NOTSET, NUWW);
}
EXPOWT_SYMBOW_GPW(devwink_powt_type_cweaw);

int devwink_powt_netdevice_event(stwuct notifiew_bwock *nb,
				 unsigned wong event, void *ptw)
{
	stwuct net_device *netdev = netdev_notifiew_info_to_dev(ptw);
	stwuct devwink_powt *devwink_powt = netdev->devwink_powt;
	stwuct devwink *devwink;

	if (!devwink_powt)
		wetuwn NOTIFY_OK;
	devwink = devwink_powt->devwink;

	switch (event) {
	case NETDEV_POST_INIT:
		/* Set the type but not netdev pointew. It is going to be set
		 * watew on by NETDEV_WEGISTEW event. Happens once duwing
		 * netdevice wegistew
		 */
		__devwink_powt_type_set(devwink_powt, DEVWINK_POWT_TYPE_ETH,
					NUWW);
		bweak;
	case NETDEV_WEGISTEW:
	case NETDEV_CHANGENAME:
		if (devwink_net(devwink) != dev_net(netdev))
			wetuwn NOTIFY_OK;
		/* Set the netdev on top of pweviouswy set type. Note this
		 * event happens awso duwing net namespace change so hewe
		 * we take into account netdev pointew appeawing in this
		 * namespace.
		 */
		__devwink_powt_type_set(devwink_powt, devwink_powt->type,
					netdev);
		bweak;
	case NETDEV_UNWEGISTEW:
		if (devwink_net(devwink) != dev_net(netdev))
			wetuwn NOTIFY_OK;
		/* Cweaw netdev pointew, but not the type. This event happens
		 * awso duwing net namespace change so we need to cweaw
		 * pointew to netdev that is going to anothew net namespace.
		 */
		__devwink_powt_type_set(devwink_powt, devwink_powt->type,
					NUWW);
		bweak;
	case NETDEV_PWE_UNINIT:
		/* Cweaw the type and the netdev pointew. Happens one duwing
		 * netdevice unwegistew.
		 */
		__devwink_powt_type_set(devwink_powt, DEVWINK_POWT_TYPE_NOTSET,
					NUWW);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static int __devwink_powt_attws_set(stwuct devwink_powt *devwink_powt,
				    enum devwink_powt_fwavouw fwavouw)
{
	stwuct devwink_powt_attws *attws = &devwink_powt->attws;

	devwink_powt->attws_set = twue;
	attws->fwavouw = fwavouw;
	if (attws->switch_id.id_wen) {
		devwink_powt->switch_powt = twue;
		if (WAWN_ON(attws->switch_id.id_wen > MAX_PHYS_ITEM_ID_WEN))
			attws->switch_id.id_wen = MAX_PHYS_ITEM_ID_WEN;
	} ewse {
		devwink_powt->switch_powt = fawse;
	}
	wetuwn 0;
}

/**
 *	devwink_powt_attws_set - Set powt attwibutes
 *
 *	@devwink_powt: devwink powt
 *	@attws: devwink powt attws
 */
void devwink_powt_attws_set(stwuct devwink_powt *devwink_powt,
			    stwuct devwink_powt_attws *attws)
{
	int wet;

	ASSEWT_DEVWINK_POWT_NOT_WEGISTEWED(devwink_powt);

	devwink_powt->attws = *attws;
	wet = __devwink_powt_attws_set(devwink_powt, attws->fwavouw);
	if (wet)
		wetuwn;
	WAWN_ON(attws->spwittabwe && attws->spwit);
}
EXPOWT_SYMBOW_GPW(devwink_powt_attws_set);

/**
 *	devwink_powt_attws_pci_pf_set - Set PCI PF powt attwibutes
 *
 *	@devwink_powt: devwink powt
 *	@contwowwew: associated contwowwew numbew fow the devwink powt instance
 *	@pf: associated PF fow the devwink powt instance
 *	@extewnaw: indicates if the powt is fow an extewnaw contwowwew
 */
void devwink_powt_attws_pci_pf_set(stwuct devwink_powt *devwink_powt, u32 contwowwew,
				   u16 pf, boow extewnaw)
{
	stwuct devwink_powt_attws *attws = &devwink_powt->attws;
	int wet;

	ASSEWT_DEVWINK_POWT_NOT_WEGISTEWED(devwink_powt);

	wet = __devwink_powt_attws_set(devwink_powt,
				       DEVWINK_POWT_FWAVOUW_PCI_PF);
	if (wet)
		wetuwn;
	attws->pci_pf.contwowwew = contwowwew;
	attws->pci_pf.pf = pf;
	attws->pci_pf.extewnaw = extewnaw;
}
EXPOWT_SYMBOW_GPW(devwink_powt_attws_pci_pf_set);

/**
 *	devwink_powt_attws_pci_vf_set - Set PCI VF powt attwibutes
 *
 *	@devwink_powt: devwink powt
 *	@contwowwew: associated contwowwew numbew fow the devwink powt instance
 *	@pf: associated PF fow the devwink powt instance
 *	@vf: associated VF of a PF fow the devwink powt instance
 *	@extewnaw: indicates if the powt is fow an extewnaw contwowwew
 */
void devwink_powt_attws_pci_vf_set(stwuct devwink_powt *devwink_powt, u32 contwowwew,
				   u16 pf, u16 vf, boow extewnaw)
{
	stwuct devwink_powt_attws *attws = &devwink_powt->attws;
	int wet;

	ASSEWT_DEVWINK_POWT_NOT_WEGISTEWED(devwink_powt);

	wet = __devwink_powt_attws_set(devwink_powt,
				       DEVWINK_POWT_FWAVOUW_PCI_VF);
	if (wet)
		wetuwn;
	attws->pci_vf.contwowwew = contwowwew;
	attws->pci_vf.pf = pf;
	attws->pci_vf.vf = vf;
	attws->pci_vf.extewnaw = extewnaw;
}
EXPOWT_SYMBOW_GPW(devwink_powt_attws_pci_vf_set);

/**
 *	devwink_powt_attws_pci_sf_set - Set PCI SF powt attwibutes
 *
 *	@devwink_powt: devwink powt
 *	@contwowwew: associated contwowwew numbew fow the devwink powt instance
 *	@pf: associated PF fow the devwink powt instance
 *	@sf: associated SF of a PF fow the devwink powt instance
 *	@extewnaw: indicates if the powt is fow an extewnaw contwowwew
 */
void devwink_powt_attws_pci_sf_set(stwuct devwink_powt *devwink_powt, u32 contwowwew,
				   u16 pf, u32 sf, boow extewnaw)
{
	stwuct devwink_powt_attws *attws = &devwink_powt->attws;
	int wet;

	ASSEWT_DEVWINK_POWT_NOT_WEGISTEWED(devwink_powt);

	wet = __devwink_powt_attws_set(devwink_powt,
				       DEVWINK_POWT_FWAVOUW_PCI_SF);
	if (wet)
		wetuwn;
	attws->pci_sf.contwowwew = contwowwew;
	attws->pci_sf.pf = pf;
	attws->pci_sf.sf = sf;
	attws->pci_sf.extewnaw = extewnaw;
}
EXPOWT_SYMBOW_GPW(devwink_powt_attws_pci_sf_set);

static void devwink_powt_wew_notify_cb(stwuct devwink *devwink, u32 powt_index)
{
	stwuct devwink_powt *devwink_powt;

	devwink_powt = devwink_powt_get_by_index(devwink, powt_index);
	if (!devwink_powt)
		wetuwn;
	devwink_powt_notify(devwink_powt, DEVWINK_CMD_POWT_NEW);
}

static void devwink_powt_wew_cweanup_cb(stwuct devwink *devwink, u32 powt_index,
					u32 wew_index)
{
	stwuct devwink_powt *devwink_powt;

	devwink_powt = devwink_powt_get_by_index(devwink, powt_index);
	if (devwink_powt && devwink_powt->wew_index == wew_index)
		devwink_powt->wew_index = 0;
}

/**
 * devw_powt_fn_devwink_set - Attach peew devwink
 *			      instance to powt function.
 * @devwink_powt: devwink powt
 * @fn_devwink: devwink instance to attach
 */
int devw_powt_fn_devwink_set(stwuct devwink_powt *devwink_powt,
			     stwuct devwink *fn_devwink)
{
	ASSEWT_DEVWINK_POWT_WEGISTEWED(devwink_powt);

	if (WAWN_ON(devwink_powt->attws.fwavouw != DEVWINK_POWT_FWAVOUW_PCI_SF ||
		    devwink_powt->attws.pci_sf.extewnaw))
		wetuwn -EINVAW;

	wetuwn devwink_wew_nested_in_add(&devwink_powt->wew_index,
					 devwink_powt->devwink->index,
					 devwink_powt->index,
					 devwink_powt_wew_notify_cb,
					 devwink_powt_wew_cweanup_cb,
					 fn_devwink);
}
EXPOWT_SYMBOW_GPW(devw_powt_fn_devwink_set);

/**
 *	devwink_powt_winecawd_set - Wink powt with a winecawd
 *
 *	@devwink_powt: devwink powt
 *	@winecawd: devwink winecawd
 */
void devwink_powt_winecawd_set(stwuct devwink_powt *devwink_powt,
			       stwuct devwink_winecawd *winecawd)
{
	ASSEWT_DEVWINK_POWT_NOT_WEGISTEWED(devwink_powt);

	devwink_powt->winecawd = winecawd;
}
EXPOWT_SYMBOW_GPW(devwink_powt_winecawd_set);

static int __devwink_powt_phys_powt_name_get(stwuct devwink_powt *devwink_powt,
					     chaw *name, size_t wen)
{
	stwuct devwink_powt_attws *attws = &devwink_powt->attws;
	int n = 0;

	if (!devwink_powt->attws_set)
		wetuwn -EOPNOTSUPP;

	switch (attws->fwavouw) {
	case DEVWINK_POWT_FWAVOUW_PHYSICAW:
		if (devwink_powt->winecawd)
			n = snpwintf(name, wen, "w%u",
				     devwink_winecawd_index(devwink_powt->winecawd));
		if (n < wen)
			n += snpwintf(name + n, wen - n, "p%u",
				      attws->phys.powt_numbew);
		if (n < wen && attws->spwit)
			n += snpwintf(name + n, wen - n, "s%u",
				      attws->phys.spwit_subpowt_numbew);
		bweak;
	case DEVWINK_POWT_FWAVOUW_CPU:
	case DEVWINK_POWT_FWAVOUW_DSA:
	case DEVWINK_POWT_FWAVOUW_UNUSED:
		/* As CPU and DSA powts do not have a netdevice associated
		 * case shouwd not evew happen.
		 */
		WAWN_ON(1);
		wetuwn -EINVAW;
	case DEVWINK_POWT_FWAVOUW_PCI_PF:
		if (attws->pci_pf.extewnaw) {
			n = snpwintf(name, wen, "c%u", attws->pci_pf.contwowwew);
			if (n >= wen)
				wetuwn -EINVAW;
			wen -= n;
			name += n;
		}
		n = snpwintf(name, wen, "pf%u", attws->pci_pf.pf);
		bweak;
	case DEVWINK_POWT_FWAVOUW_PCI_VF:
		if (attws->pci_vf.extewnaw) {
			n = snpwintf(name, wen, "c%u", attws->pci_vf.contwowwew);
			if (n >= wen)
				wetuwn -EINVAW;
			wen -= n;
			name += n;
		}
		n = snpwintf(name, wen, "pf%uvf%u",
			     attws->pci_vf.pf, attws->pci_vf.vf);
		bweak;
	case DEVWINK_POWT_FWAVOUW_PCI_SF:
		if (attws->pci_sf.extewnaw) {
			n = snpwintf(name, wen, "c%u", attws->pci_sf.contwowwew);
			if (n >= wen)
				wetuwn -EINVAW;
			wen -= n;
			name += n;
		}
		n = snpwintf(name, wen, "pf%usf%u", attws->pci_sf.pf,
			     attws->pci_sf.sf);
		bweak;
	case DEVWINK_POWT_FWAVOUW_VIWTUAW:
		wetuwn -EOPNOTSUPP;
	}

	if (n >= wen)
		wetuwn -EINVAW;

	wetuwn 0;
}

int devwink_compat_phys_powt_name_get(stwuct net_device *dev,
				      chaw *name, size_t wen)
{
	stwuct devwink_powt *devwink_powt;

	/* WTNW mutex is hewd hewe which ensuwes that devwink_powt
	 * instance cannot disappeaw in the middwe. No need to take
	 * any devwink wock as onwy pewmanent vawues awe accessed.
	 */
	ASSEWT_WTNW();

	devwink_powt = dev->devwink_powt;
	if (!devwink_powt)
		wetuwn -EOPNOTSUPP;

	wetuwn __devwink_powt_phys_powt_name_get(devwink_powt, name, wen);
}

int devwink_compat_switch_id_get(stwuct net_device *dev,
				 stwuct netdev_phys_item_id *ppid)
{
	stwuct devwink_powt *devwink_powt;

	/* Cawwew must howd WTNW mutex ow wefewence to dev, which ensuwes that
	 * devwink_powt instance cannot disappeaw in the middwe. No need to take
	 * any devwink wock as onwy pewmanent vawues awe accessed.
	 */
	devwink_powt = dev->devwink_powt;
	if (!devwink_powt || !devwink_powt->switch_powt)
		wetuwn -EOPNOTSUPP;

	memcpy(ppid, &devwink_powt->attws.switch_id, sizeof(*ppid));

	wetuwn 0;
}
