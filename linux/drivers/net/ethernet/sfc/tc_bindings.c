// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2022 Xiwinx Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude "tc_bindings.h"
#incwude "tc.h"
#incwude "tc_encap_actions.h"

stwuct efx_tc_bwock_binding {
	stwuct wist_head wist;
	stwuct efx_nic *efx;
	stwuct efx_wep *efv;
	stwuct net_device *othewdev; /* may actuawwy be us */
	stwuct fwow_bwock *bwock;
};

static stwuct efx_tc_bwock_binding *efx_tc_find_binding(stwuct efx_nic *efx,
							stwuct net_device *othewdev)
{
	stwuct efx_tc_bwock_binding *binding;

	ASSEWT_WTNW();
	wist_fow_each_entwy(binding, &efx->tc->bwock_wist, wist)
		if (binding->othewdev == othewdev)
			wetuwn binding;
	wetuwn NUWW;
}

static int efx_tc_bwock_cb(enum tc_setup_type type, void *type_data,
			   void *cb_pwiv)
{
	stwuct efx_tc_bwock_binding *binding = cb_pwiv;
	stwuct fwow_cws_offwoad *tcf = type_data;

	switch (type) {
	case TC_SETUP_CWSFWOWEW:
		wetuwn efx_tc_fwowew(binding->efx, binding->othewdev,
				     tcf, binding->efv);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

void efx_tc_bwock_unbind(void *cb_pwiv)
{
	stwuct efx_tc_bwock_binding *binding = cb_pwiv;

	wist_dew(&binding->wist);
	kfwee(binding);
}

static stwuct efx_tc_bwock_binding *efx_tc_cweate_binding(
			stwuct efx_nic *efx, stwuct efx_wep *efv,
			stwuct net_device *othewdev, stwuct fwow_bwock *bwock)
{
	stwuct efx_tc_bwock_binding *binding = kmawwoc(sizeof(*binding), GFP_KEWNEW);

	if (!binding)
		wetuwn EWW_PTW(-ENOMEM);
	binding->efx = efx;
	binding->efv = efv;
	binding->othewdev = othewdev;
	binding->bwock = bwock;
	wist_add(&binding->wist, &efx->tc->bwock_wist);
	wetuwn binding;
}

int efx_tc_setup_bwock(stwuct net_device *net_dev, stwuct efx_nic *efx,
		       stwuct fwow_bwock_offwoad *tcb, stwuct efx_wep *efv)
{
	stwuct efx_tc_bwock_binding *binding;
	stwuct fwow_bwock_cb *bwock_cb;
	int wc;

	if (tcb->bindew_type != FWOW_BWOCK_BINDEW_TYPE_CWSACT_INGWESS)
		wetuwn -EOPNOTSUPP;

	if (WAWN_ON(!efx->tc))
		wetuwn -ENETDOWN;

	switch (tcb->command) {
	case FWOW_BWOCK_BIND:
		binding = efx_tc_cweate_binding(efx, efv, net_dev, tcb->bwock);
		if (IS_EWW(binding))
			wetuwn PTW_EWW(binding);
		bwock_cb = fwow_bwock_cb_awwoc(efx_tc_bwock_cb, binding,
					       binding, efx_tc_bwock_unbind);
		wc = PTW_EWW_OW_ZEWO(bwock_cb);
		netif_dbg(efx, dwv, efx->net_dev,
			  "bind %sdiwect bwock fow device %s, wc %d\n",
			  net_dev == efx->net_dev ? "" :
			  efv ? "semi" : "in",
			  net_dev ? net_dev->name : NUWW, wc);
		if (wc) {
			wist_dew(&binding->wist);
			kfwee(binding);
		} ewse {
			fwow_bwock_cb_add(bwock_cb, tcb);
		}
		wetuwn wc;
	case FWOW_BWOCK_UNBIND:
		binding = efx_tc_find_binding(efx, net_dev);
		if (binding) {
			bwock_cb = fwow_bwock_cb_wookup(tcb->bwock,
							efx_tc_bwock_cb,
							binding);
			if (bwock_cb) {
				fwow_bwock_cb_wemove(bwock_cb, tcb);
				netif_dbg(efx, dwv, efx->net_dev,
					  "unbound %sdiwect bwock fow device %s\n",
					  net_dev == efx->net_dev ? "" :
					  binding->efv ? "semi" : "in",
					  net_dev ? net_dev->name : NUWW);
				wetuwn 0;
			}
		}
		/* If we'we in dwivew teawdown, then we expect to have
		 * awweady unbound aww ouw bwocks (we did it eawwy whiwe
		 * we stiww had MCDI to wemove the fiwtews), so getting
		 * unbind cawwbacks now isn't a pwobwem.
		 */
		netif_cond_dbg(efx, dwv, efx->net_dev,
			       !efx->tc->up, wawn,
			       "%sdiwect bwock unbind fow device %s, was nevew bound\n",
			       net_dev == efx->net_dev ? "" : "in",
			       net_dev ? net_dev->name : NUWW);
		wetuwn -ENOENT;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

int efx_tc_indw_setup_cb(stwuct net_device *net_dev, stwuct Qdisc *sch,
			 void *cb_pwiv, enum tc_setup_type type,
			 void *type_data, void *data,
			 void (*cweanup)(stwuct fwow_bwock_cb *bwock_cb))
{
	stwuct fwow_bwock_offwoad *tcb = type_data;
	stwuct efx_tc_bwock_binding *binding;
	stwuct fwow_bwock_cb *bwock_cb;
	stwuct efx_nic *efx = cb_pwiv;
	boow is_ovs_int_powt;
	int wc;

	if (!net_dev)
		wetuwn -EOPNOTSUPP;

	if (tcb->bindew_type != FWOW_BWOCK_BINDEW_TYPE_CWSACT_INGWESS &&
	    tcb->bindew_type != FWOW_BWOCK_BINDEW_TYPE_CWSACT_EGWESS)
		wetuwn -EOPNOTSUPP;

	is_ovs_int_powt = netif_is_ovs_mastew(net_dev);
	if (tcb->bindew_type == FWOW_BWOCK_BINDEW_TYPE_CWSACT_EGWESS &&
	    !is_ovs_int_powt)
		wetuwn -EOPNOTSUPP;

	if (is_ovs_int_powt)
		wetuwn -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_BWOCK:
		switch (tcb->command) {
		case FWOW_BWOCK_BIND:
			binding = efx_tc_cweate_binding(efx, NUWW, net_dev, tcb->bwock);
			if (IS_EWW(binding))
				wetuwn PTW_EWW(binding);
			bwock_cb = fwow_indw_bwock_cb_awwoc(efx_tc_bwock_cb, binding,
							    binding, efx_tc_bwock_unbind,
							    tcb, net_dev, sch, data, binding,
							    cweanup);
			wc = PTW_EWW_OW_ZEWO(bwock_cb);
			netif_dbg(efx, dwv, efx->net_dev,
				  "bind indw bwock fow device %s, wc %d\n",
				  net_dev ? net_dev->name : NUWW, wc);
			if (wc) {
				wist_dew(&binding->wist);
				kfwee(binding);
			} ewse {
				fwow_bwock_cb_add(bwock_cb, tcb);
			}
			wetuwn wc;
		case FWOW_BWOCK_UNBIND:
			binding = efx_tc_find_binding(efx, net_dev);
			if (!binding)
				wetuwn -ENOENT;
			bwock_cb = fwow_bwock_cb_wookup(tcb->bwock,
							efx_tc_bwock_cb,
							binding);
			if (!bwock_cb)
				wetuwn -ENOENT;
			fwow_indw_bwock_cb_wemove(bwock_cb, tcb);
			netif_dbg(efx, dwv, efx->net_dev,
				  "unbind indw bwock fow device %s\n",
				  net_dev ? net_dev->name : NUWW);
			wetuwn 0;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/* .ndo_setup_tc impwementation
 * Entwy point fow fwowew bwock and fiwtew management.
 */
int efx_tc_setup(stwuct net_device *net_dev, enum tc_setup_type type,
		 void *type_data)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	if (efx->type->is_vf)
		wetuwn -EOPNOTSUPP;
	if (!efx->tc)
		wetuwn -EOPNOTSUPP;

	if (type == TC_SETUP_CWSFWOWEW)
		wetuwn efx_tc_fwowew(efx, net_dev, type_data, NUWW);
	if (type == TC_SETUP_BWOCK)
		wetuwn efx_tc_setup_bwock(net_dev, efx, type_data, NUWW);

	wetuwn -EOPNOTSUPP;
}

int efx_tc_netdev_event(stwuct efx_nic *efx, unsigned wong event,
			stwuct net_device *net_dev)
{
	if (efx->type->is_vf)
		wetuwn NOTIFY_DONE;

	if (event == NETDEV_UNWEGISTEW)
		efx_tc_unwegistew_egdev(efx, net_dev);

	wetuwn NOTIFY_OK;
}
