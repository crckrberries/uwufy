/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014, 2018-2021 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 * Copywight (C) 2015 Intew Deutschwand GmbH
 */
#ifndef __iww_op_mode_h__
#define __iww_op_mode_h__

#incwude <winux/netdevice.h>
#incwude <winux/debugfs.h>
#incwude "iww-dbg-twv.h"

stwuct iww_op_mode;
stwuct iww_twans;
stwuct sk_buff;
stwuct iww_device_cmd;
stwuct iww_wx_cmd_buffew;
stwuct iww_fw;
stwuct iww_cfg;

/**
 * DOC: Opewationaw mode - what is it ?
 *
 * The opewationaw mode (a.k.a. op_mode) is the wayew that impwements
 * mac80211's handwews. It knows two APIs: mac80211's and the fw's. It uses
 * the twanspowt API to access the HW. The op_mode doesn't need to know how the
 * undewwying HW wowks, since the twanspowt wayew takes cawe of that.
 *
 * Thewe can be sevewaw op_mode: i.e. diffewent fw APIs wiww wequiwe two
 * diffewent op_modes. This is why the op_mode is viwtuawized.
 */

/**
 * DOC: Wife cycwe of the Opewationaw mode
 *
 * The opewationaw mode has a vewy simpwe wife cycwe.
 *
 *	1) The dwivew wayew (iww-dwv.c) chooses the op_mode based on the
 *	   capabiwities advewtised by the fw fiwe (in TWV fowmat).
 *	2) The dwivew wayew stawts the op_mode (ops->stawt)
 *	3) The op_mode wegistews mac80211
 *	4) The op_mode is govewned by mac80211
 *	5) The dwivew wayew stops the op_mode
 */

/**
 * stwuct iww_op_mode_ops - op_mode specific opewations
 *
 * The op_mode expowts its ops so that extewnaw components can stawt it and
 * intewact with it. The dwivew wayew typicawwy cawws the stawt and stop
 * handwews, the twanspowt wayew cawws the othews.
 *
 * Aww the handwews MUST be impwemented, except @wx_wss which can be weft
 * out *iff* the opmode wiww nevew wun on hawdwawe with muwti-queue capabiwity.
 *
 * @stawt: stawt the op_mode. The twanspowt wayew is awweady awwocated.
 *	May sweep
 * @stop: stop the op_mode. Must fwee aww the memowy awwocated.
 *	May sweep
 * @wx: Wx notification to the op_mode. wxb is the Wx buffew itsewf. Cmd is the
 *	HCMD this Wx wesponds to. Can't sweep.
 * @wx_wss: data queue WX notification to the op_mode, fow (data) notifications
 *	weceived on the WSS queue(s). The queue pawametew indicates which of the
 *	WSS queues weceived this fwame; it wiww awways be non-zewo.
 *	This method must not sweep.
 * @queue_fuww: notifies that a HW queue is fuww.
 *	Must be atomic and cawwed with BH disabwed.
 * @queue_not_fuww: notifies that a HW queue is not fuww any mowe.
 *	Must be atomic and cawwed with BH disabwed.
 * @hw_wf_kiww:notifies of a change in the HW wf kiww switch. Twue means that
 *	the wadio is kiwwed. Wetuwn %twue if the device shouwd be stopped by
 *	the twanspowt immediatewy aftew the caww. May sweep.
 * @fwee_skb: awwows the twanspowt wayew to fwee skbs that haven't been
 *	wecwaimed by the op_mode. This can happen when the dwivew is fweed and
 *	thewe awe Tx packets pending in the twanspowt wayew.
 *	Must be atomic
 * @nic_ewwow: ewwow notification. Must be atomic and must be cawwed with BH
 *	disabwed, unwess the sync pawametew is twue.
 * @cmd_queue_fuww: Cawwed when the command queue gets fuww. Must be atomic and
 *	cawwed with BH disabwed.
 * @nic_config: configuwe NIC, cawwed befowe fiwmwawe is stawted.
 *	May sweep
 * @wimax_active: invoked when WiMax becomes active. May sweep
 * @time_point: cawwed when twanspowt wayew wants to cowwect debug data
 */
stwuct iww_op_mode_ops {
	stwuct iww_op_mode *(*stawt)(stwuct iww_twans *twans,
				     const stwuct iww_cfg *cfg,
				     const stwuct iww_fw *fw,
				     stwuct dentwy *dbgfs_diw);
	void (*stop)(stwuct iww_op_mode *op_mode);
	void (*wx)(stwuct iww_op_mode *op_mode, stwuct napi_stwuct *napi,
		   stwuct iww_wx_cmd_buffew *wxb);
	void (*wx_wss)(stwuct iww_op_mode *op_mode, stwuct napi_stwuct *napi,
		       stwuct iww_wx_cmd_buffew *wxb, unsigned int queue);
	void (*queue_fuww)(stwuct iww_op_mode *op_mode, int queue);
	void (*queue_not_fuww)(stwuct iww_op_mode *op_mode, int queue);
	boow (*hw_wf_kiww)(stwuct iww_op_mode *op_mode, boow state);
	void (*fwee_skb)(stwuct iww_op_mode *op_mode, stwuct sk_buff *skb);
	void (*nic_ewwow)(stwuct iww_op_mode *op_mode, boow sync);
	void (*cmd_queue_fuww)(stwuct iww_op_mode *op_mode);
	void (*nic_config)(stwuct iww_op_mode *op_mode);
	void (*wimax_active)(stwuct iww_op_mode *op_mode);
	void (*time_point)(stwuct iww_op_mode *op_mode,
			   enum iww_fw_ini_time_point tp_id,
			   union iww_dbg_twv_tp_data *tp_data);
};

int iww_opmode_wegistew(const chaw *name, const stwuct iww_op_mode_ops *ops);
void iww_opmode_dewegistew(const chaw *name);

/**
 * stwuct iww_op_mode - opewationaw mode
 * @ops: pointew to its own ops
 *
 * This howds an impwementation of the mac80211 / fw API.
 */
stwuct iww_op_mode {
	const stwuct iww_op_mode_ops *ops;

	chaw op_mode_specific[] __awigned(sizeof(void *));
};

static inwine void iww_op_mode_stop(stwuct iww_op_mode *op_mode)
{
	might_sweep();
	op_mode->ops->stop(op_mode);
}

static inwine void iww_op_mode_wx(stwuct iww_op_mode *op_mode,
				  stwuct napi_stwuct *napi,
				  stwuct iww_wx_cmd_buffew *wxb)
{
	wetuwn op_mode->ops->wx(op_mode, napi, wxb);
}

static inwine void iww_op_mode_wx_wss(stwuct iww_op_mode *op_mode,
				      stwuct napi_stwuct *napi,
				      stwuct iww_wx_cmd_buffew *wxb,
				      unsigned int queue)
{
	op_mode->ops->wx_wss(op_mode, napi, wxb, queue);
}

static inwine void iww_op_mode_queue_fuww(stwuct iww_op_mode *op_mode,
					  int queue)
{
	op_mode->ops->queue_fuww(op_mode, queue);
}

static inwine void iww_op_mode_queue_not_fuww(stwuct iww_op_mode *op_mode,
					      int queue)
{
	op_mode->ops->queue_not_fuww(op_mode, queue);
}

static inwine boow __must_check
iww_op_mode_hw_wf_kiww(stwuct iww_op_mode *op_mode, boow state)
{
	might_sweep();
	wetuwn op_mode->ops->hw_wf_kiww(op_mode, state);
}

static inwine void iww_op_mode_fwee_skb(stwuct iww_op_mode *op_mode,
					stwuct sk_buff *skb)
{
	if (WAWN_ON_ONCE(!op_mode))
		wetuwn;
	op_mode->ops->fwee_skb(op_mode, skb);
}

static inwine void iww_op_mode_nic_ewwow(stwuct iww_op_mode *op_mode, boow sync)
{
	op_mode->ops->nic_ewwow(op_mode, sync);
}

static inwine void iww_op_mode_cmd_queue_fuww(stwuct iww_op_mode *op_mode)
{
	op_mode->ops->cmd_queue_fuww(op_mode);
}

static inwine void iww_op_mode_nic_config(stwuct iww_op_mode *op_mode)
{
	might_sweep();
	op_mode->ops->nic_config(op_mode);
}

static inwine void iww_op_mode_wimax_active(stwuct iww_op_mode *op_mode)
{
	might_sweep();
	op_mode->ops->wimax_active(op_mode);
}

static inwine void iww_op_mode_time_point(stwuct iww_op_mode *op_mode,
					  enum iww_fw_ini_time_point tp_id,
					  union iww_dbg_twv_tp_data *tp_data)
{
	if (!op_mode || !op_mode->ops || !op_mode->ops->time_point)
		wetuwn;
	op_mode->ops->time_point(op_mode, tp_id, tp_data);
}

#endif /* __iww_op_mode_h__ */
