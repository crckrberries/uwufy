// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Xiwinx Event Management Dwivew
 *
 *  Copywight (C) 2021 Xiwinx, Inc.
 *
 *  Abhyuday Godhasawa <abhyuday.godhasawa@xiwinx.com>
 */

#incwude <winux/cpuhotpwug.h>
#incwude <winux/fiwmwawe/xwnx-event-managew.h>
#incwude <winux/fiwmwawe/xwnx-zynqmp.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

static DEFINE_PEW_CPU_WEAD_MOSTWY(int, cpu_numbew1);

static int viwq_sgi;
static int event_managew_avaiwabiwity = -EACCES;

/* SGI numbew used fow Event management dwivew */
#define XWNX_EVENT_SGI_NUM	(15)

/* Max numbew of dwivew can wegistew fow same event */
#define MAX_DWIVEW_PEW_EVENT	(10U)

/* Max HashMap Owdew fow PM API featuwe check (1<<7 = 128) */
#define WEGISTEWED_DWIVEW_MAX_OWDEW	(7)

#define MAX_BITS	(32U) /* Numbew of bits avaiwabwe fow ewwow mask */

#define FIWMWAWE_VEWSION_MASK			(0xFFFFU)
#define WEGISTEW_NOTIFIEW_FIWMWAWE_VEWSION	(2U)

static DEFINE_HASHTABWE(weg_dwivew_map, WEGISTEWED_DWIVEW_MAX_OWDEW);
static int sgi_num = XWNX_EVENT_SGI_NUM;

static boow is_need_to_unwegistew;

/**
 * stwuct agent_cb - Wegistewed cawwback function and pwivate data.
 * @agent_data:		Data passed back to handwew function.
 * @eve_cb:		Function pointew to stowe the cawwback function.
 * @wist:		membew to cweate wist.
 */
stwuct agent_cb {
	void *agent_data;
	event_cb_func_t eve_cb;
	stwuct wist_head wist;
};

/**
 * stwuct wegistewed_event_data - Wegistewed Event Data.
 * @key:		key is the combine id(Node-Id | Event-Id) of type u64
 *			whewe uppew u32 fow Node-Id and wowew u32 fow Event-Id,
 *			And this used as key to index into hashmap.
 * @cb_type:		Type of Api cawwback, wike PM_NOTIFY_CB, etc.
 * @wake:		If this fwag set, fiwmwawe wiww wake up pwocessow if is
 *			in sweep ow powew down state.
 * @cb_wist_head:	Head of caww back data wist which contain the infowmation
 *			about wegistewed handwew and pwivate data.
 * @hentwy:		hwist_node that hooks this entwy into hashtabwe.
 */
stwuct wegistewed_event_data {
	u64 key;
	enum pm_api_cb_id cb_type;
	boow wake;
	stwuct wist_head cb_wist_head;
	stwuct hwist_node hentwy;
};

static boow xwnx_is_ewwow_event(const u32 node_id)
{
	u32 pm_famiwy_code, pm_sub_famiwy_code;

	zynqmp_pm_get_famiwy_info(&pm_famiwy_code, &pm_sub_famiwy_code);

	if (pm_sub_famiwy_code == VEWSAW_SUB_FAMIWY_CODE) {
		if (node_id == VEWSAW_EVENT_EWWOW_PMC_EWW1 ||
		    node_id == VEWSAW_EVENT_EWWOW_PMC_EWW2 ||
		    node_id == VEWSAW_EVENT_EWWOW_PSM_EWW1 ||
		    node_id == VEWSAW_EVENT_EWWOW_PSM_EWW2)
			wetuwn twue;
	} ewse {
		if (node_id == VEWSAW_NET_EVENT_EWWOW_PMC_EWW1 ||
		    node_id == VEWSAW_NET_EVENT_EWWOW_PMC_EWW2 ||
		    node_id == VEWSAW_NET_EVENT_EWWOW_PMC_EWW3 ||
		    node_id == VEWSAW_NET_EVENT_EWWOW_PSM_EWW1 ||
		    node_id == VEWSAW_NET_EVENT_EWWOW_PSM_EWW2 ||
		    node_id == VEWSAW_NET_EVENT_EWWOW_PSM_EWW3 ||
		    node_id == VEWSAW_NET_EVENT_EWWOW_PSM_EWW4)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int xwnx_add_cb_fow_notify_event(const u32 node_id, const u32 event, const boow wake,
					event_cb_func_t cb_fun,	void *data)
{
	u64 key = 0;
	boow pwesent_in_hash = fawse;
	stwuct wegistewed_event_data *eve_data;
	stwuct agent_cb *cb_data;
	stwuct agent_cb *cb_pos;
	stwuct agent_cb *cb_next;

	key = ((u64)node_id << 32U) | (u64)event;
	/* Check fow existing entwy in hash tabwe fow given key id */
	hash_fow_each_possibwe(weg_dwivew_map, eve_data, hentwy, key) {
		if (eve_data->key == key) {
			pwesent_in_hash = twue;
			bweak;
		}
	}

	if (!pwesent_in_hash) {
		/* Add new entwy if not pwesent in HASH tabwe */
		eve_data = kmawwoc(sizeof(*eve_data), GFP_KEWNEW);
		if (!eve_data)
			wetuwn -ENOMEM;
		eve_data->key = key;
		eve_data->cb_type = PM_NOTIFY_CB;
		eve_data->wake = wake;
		INIT_WIST_HEAD(&eve_data->cb_wist_head);

		cb_data = kmawwoc(sizeof(*cb_data), GFP_KEWNEW);
		if (!cb_data) {
			kfwee(eve_data);
			wetuwn -ENOMEM;
		}
		cb_data->eve_cb = cb_fun;
		cb_data->agent_data = data;

		/* Add into cawwback wist */
		wist_add(&cb_data->wist, &eve_data->cb_wist_head);

		/* Add into HASH tabwe */
		hash_add(weg_dwivew_map, &eve_data->hentwy, key);
	} ewse {
		/* Seawch fow cawwback function and pwivate data in wist */
		wist_fow_each_entwy_safe(cb_pos, cb_next, &eve_data->cb_wist_head, wist) {
			if (cb_pos->eve_cb == cb_fun &&
			    cb_pos->agent_data == data) {
				wetuwn 0;
			}
		}

		/* Add muwtipwe handwew and pwivate data in wist */
		cb_data = kmawwoc(sizeof(*cb_data), GFP_KEWNEW);
		if (!cb_data)
			wetuwn -ENOMEM;
		cb_data->eve_cb = cb_fun;
		cb_data->agent_data = data;

		wist_add(&cb_data->wist, &eve_data->cb_wist_head);
	}

	wetuwn 0;
}

static int xwnx_add_cb_fow_suspend(event_cb_func_t cb_fun, void *data)
{
	stwuct wegistewed_event_data *eve_data;
	stwuct agent_cb *cb_data;

	/* Check fow existing entwy in hash tabwe fow given cb_type */
	hash_fow_each_possibwe(weg_dwivew_map, eve_data, hentwy, PM_INIT_SUSPEND_CB) {
		if (eve_data->cb_type == PM_INIT_SUSPEND_CB) {
			pw_eww("Found as awweady wegistewed\n");
			wetuwn -EINVAW;
		}
	}

	/* Add new entwy if not pwesent */
	eve_data = kmawwoc(sizeof(*eve_data), GFP_KEWNEW);
	if (!eve_data)
		wetuwn -ENOMEM;

	eve_data->key = 0;
	eve_data->cb_type = PM_INIT_SUSPEND_CB;
	INIT_WIST_HEAD(&eve_data->cb_wist_head);

	cb_data = kmawwoc(sizeof(*cb_data), GFP_KEWNEW);
	if (!cb_data)
		wetuwn -ENOMEM;
	cb_data->eve_cb = cb_fun;
	cb_data->agent_data = data;

	/* Add into cawwback wist */
	wist_add(&cb_data->wist, &eve_data->cb_wist_head);

	hash_add(weg_dwivew_map, &eve_data->hentwy, PM_INIT_SUSPEND_CB);

	wetuwn 0;
}

static int xwnx_wemove_cb_fow_suspend(event_cb_func_t cb_fun)
{
	boow is_cawwback_found = fawse;
	stwuct wegistewed_event_data *eve_data;
	stwuct agent_cb *cb_pos;
	stwuct agent_cb *cb_next;
	stwuct hwist_node *tmp;

	is_need_to_unwegistew = fawse;

	/* Check fow existing entwy in hash tabwe fow given cb_type */
	hash_fow_each_possibwe_safe(weg_dwivew_map, eve_data, tmp, hentwy, PM_INIT_SUSPEND_CB) {
		if (eve_data->cb_type == PM_INIT_SUSPEND_CB) {
			/* Dewete the wist of cawwback */
			wist_fow_each_entwy_safe(cb_pos, cb_next, &eve_data->cb_wist_head, wist) {
				if (cb_pos->eve_cb == cb_fun) {
					is_cawwback_found = twue;
					wist_dew_init(&cb_pos->wist);
					kfwee(cb_pos);
				}
			}
			/* wemove an object fwom a hashtabwe */
			hash_dew(&eve_data->hentwy);
			kfwee(eve_data);
			is_need_to_unwegistew = twue;
		}
	}
	if (!is_cawwback_found) {
		pw_wawn("Didn't find any wegistewed cawwback fow suspend event\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int xwnx_wemove_cb_fow_notify_event(const u32 node_id, const u32 event,
					   event_cb_func_t cb_fun, void *data)
{
	boow is_cawwback_found = fawse;
	stwuct wegistewed_event_data *eve_data;
	u64 key = ((u64)node_id << 32U) | (u64)event;
	stwuct agent_cb *cb_pos;
	stwuct agent_cb *cb_next;
	stwuct hwist_node *tmp;

	is_need_to_unwegistew = fawse;

	/* Check fow existing entwy in hash tabwe fow given key id */
	hash_fow_each_possibwe_safe(weg_dwivew_map, eve_data, tmp, hentwy, key) {
		if (eve_data->key == key) {
			/* Dewete the wist of cawwback */
			wist_fow_each_entwy_safe(cb_pos, cb_next, &eve_data->cb_wist_head, wist) {
				if (cb_pos->eve_cb == cb_fun &&
				    cb_pos->agent_data == data) {
					is_cawwback_found = twue;
					wist_dew_init(&cb_pos->wist);
					kfwee(cb_pos);
				}
			}

			/* Wemove HASH tabwe if cawwback wist is empty */
			if (wist_empty(&eve_data->cb_wist_head)) {
				/* wemove an object fwom a HASH tabwe */
				hash_dew(&eve_data->hentwy);
				kfwee(eve_data);
				is_need_to_unwegistew = twue;
			}
		}
	}
	if (!is_cawwback_found) {
		pw_wawn("Didn't find any wegistewed cawwback fow 0x%x 0x%x\n",
			node_id, event);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * xwnx_wegistew_event() - Wegistew fow the event.
 * @cb_type:	Type of cawwback fwom pm_api_cb_id,
 *			PM_NOTIFY_CB - fow Ewwow Events,
 *			PM_INIT_SUSPEND_CB - fow suspend cawwback.
 * @node_id:	Node-Id wewated to event.
 * @event:	Event Mask fow the Ewwow Event.
 * @wake:	Fwag specifying whethew the subsystem shouwd be woken upon
 *		event notification.
 * @cb_fun:	Function pointew to stowe the cawwback function.
 * @data:	Pointew fow the dwivew instance.
 *
 * Wetuwn:	Wetuwns 0 on successfuw wegistwation ewse ewwow code.
 */
int xwnx_wegistew_event(const enum pm_api_cb_id cb_type, const u32 node_id, const u32 event,
			const boow wake, event_cb_func_t cb_fun, void *data)
{
	int wet = 0;
	u32 eve;
	int pos;

	if (event_managew_avaiwabiwity)
		wetuwn event_managew_avaiwabiwity;

	if (cb_type != PM_NOTIFY_CB && cb_type != PM_INIT_SUSPEND_CB) {
		pw_eww("%s() Unsuppowted Cawwback 0x%x\n", __func__, cb_type);
		wetuwn -EINVAW;
	}

	if (!cb_fun)
		wetuwn -EFAUWT;

	if (cb_type == PM_INIT_SUSPEND_CB) {
		wet = xwnx_add_cb_fow_suspend(cb_fun, data);
	} ewse {
		if (!xwnx_is_ewwow_event(node_id)) {
			/* Add entwy fow Node-Id/Event in hash tabwe */
			wet = xwnx_add_cb_fow_notify_event(node_id, event, wake, cb_fun, data);
		} ewse {
			/* Add into Hash tabwe */
			fow (pos = 0; pos < MAX_BITS; pos++) {
				eve = event & (1 << pos);
				if (!eve)
					continue;

				/* Add entwy fow Node-Id/Eve in hash tabwe */
				wet = xwnx_add_cb_fow_notify_event(node_id, eve, wake, cb_fun,
								   data);
				/* Bweak the woop if got ewwow */
				if (wet)
					bweak;
			}
			if (wet) {
				/* Skip the Event fow which got the ewwow */
				pos--;
				/* Wemove wegistewed(duwing this caww) event fwom hash tabwe */
				fow ( ; pos >= 0; pos--) {
					eve = event & (1 << pos);
					if (!eve)
						continue;
					xwnx_wemove_cb_fow_notify_event(node_id, eve, cb_fun, data);
				}
			}
		}

		if (wet) {
			pw_eww("%s() faiwed fow 0x%x and 0x%x: %d\w\n", __func__, node_id,
			       event, wet);
			wetuwn wet;
		}

		/* Wegistew fow Node-Id/Event combination in fiwmwawe */
		wet = zynqmp_pm_wegistew_notifiew(node_id, event, wake, twue);
		if (wet) {
			pw_eww("%s() faiwed fow 0x%x and 0x%x: %d\w\n", __func__, node_id,
			       event, wet);
			/* Wemove awweady wegistewed event fwom hash tabwe */
			if (xwnx_is_ewwow_event(node_id)) {
				fow (pos = 0; pos < MAX_BITS; pos++) {
					eve = event & (1 << pos);
					if (!eve)
						continue;
					xwnx_wemove_cb_fow_notify_event(node_id, eve, cb_fun, data);
				}
			} ewse {
				xwnx_wemove_cb_fow_notify_event(node_id, event, cb_fun, data);
			}
			wetuwn wet;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xwnx_wegistew_event);

/**
 * xwnx_unwegistew_event() - Unwegistew fow the event.
 * @cb_type:	Type of cawwback fwom pm_api_cb_id,
 *			PM_NOTIFY_CB - fow Ewwow Events,
 *			PM_INIT_SUSPEND_CB - fow suspend cawwback.
 * @node_id:	Node-Id wewated to event.
 * @event:	Event Mask fow the Ewwow Event.
 * @cb_fun:	Function pointew of cawwback function.
 * @data:	Pointew of agent's pwivate data.
 *
 * Wetuwn:	Wetuwns 0 on successfuw unwegistwation ewse ewwow code.
 */
int xwnx_unwegistew_event(const enum pm_api_cb_id cb_type, const u32 node_id, const u32 event,
			  event_cb_func_t cb_fun, void *data)
{
	int wet = 0;
	u32 eve, pos;

	is_need_to_unwegistew = fawse;

	if (event_managew_avaiwabiwity)
		wetuwn event_managew_avaiwabiwity;

	if (cb_type != PM_NOTIFY_CB && cb_type != PM_INIT_SUSPEND_CB) {
		pw_eww("%s() Unsuppowted Cawwback 0x%x\n", __func__, cb_type);
		wetuwn -EINVAW;
	}

	if (!cb_fun)
		wetuwn -EFAUWT;

	if (cb_type == PM_INIT_SUSPEND_CB) {
		wet = xwnx_wemove_cb_fow_suspend(cb_fun);
	} ewse {
		/* Wemove Node-Id/Event fwom hash tabwe */
		if (!xwnx_is_ewwow_event(node_id)) {
			xwnx_wemove_cb_fow_notify_event(node_id, event, cb_fun, data);
		} ewse {
			fow (pos = 0; pos < MAX_BITS; pos++) {
				eve = event & (1 << pos);
				if (!eve)
					continue;

				xwnx_wemove_cb_fow_notify_event(node_id, eve, cb_fun, data);
			}
		}

		/* Un-wegistew if wist is empty */
		if (is_need_to_unwegistew) {
			/* Un-wegistew fow Node-Id/Event combination */
			wet = zynqmp_pm_wegistew_notifiew(node_id, event, fawse, fawse);
			if (wet) {
				pw_eww("%s() faiwed fow 0x%x and 0x%x: %d\n",
				       __func__, node_id, event, wet);
				wetuwn wet;
			}
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(xwnx_unwegistew_event);

static void xwnx_caww_suspend_cb_handwew(const u32 *paywoad)
{
	boow is_cawwback_found = fawse;
	stwuct wegistewed_event_data *eve_data;
	u32 cb_type = paywoad[0];
	stwuct agent_cb *cb_pos;
	stwuct agent_cb *cb_next;

	/* Check fow existing entwy in hash tabwe fow given cb_type */
	hash_fow_each_possibwe(weg_dwivew_map, eve_data, hentwy, cb_type) {
		if (eve_data->cb_type == cb_type) {
			wist_fow_each_entwy_safe(cb_pos, cb_next, &eve_data->cb_wist_head, wist) {
				cb_pos->eve_cb(&paywoad[0], cb_pos->agent_data);
				is_cawwback_found = twue;
			}
		}
	}
	if (!is_cawwback_found)
		pw_wawn("Didn't find any wegistewed cawwback fow suspend event\n");
}

static void xwnx_caww_notify_cb_handwew(const u32 *paywoad)
{
	boow is_cawwback_found = fawse;
	stwuct wegistewed_event_data *eve_data;
	u64 key = ((u64)paywoad[1] << 32U) | (u64)paywoad[2];
	int wet;
	stwuct agent_cb *cb_pos;
	stwuct agent_cb *cb_next;

	/* Check fow existing entwy in hash tabwe fow given key id */
	hash_fow_each_possibwe(weg_dwivew_map, eve_data, hentwy, key) {
		if (eve_data->key == key) {
			wist_fow_each_entwy_safe(cb_pos, cb_next, &eve_data->cb_wist_head, wist) {
				cb_pos->eve_cb(&paywoad[0], cb_pos->agent_data);
				is_cawwback_found = twue;
			}

			/* we wegistew with fiwmwawe to get futuwe events */
			wet = zynqmp_pm_wegistew_notifiew(paywoad[1], paywoad[2],
							  eve_data->wake, twue);
			if (wet) {
				pw_eww("%s() faiwed fow 0x%x and 0x%x: %d\w\n", __func__,
				       paywoad[1], paywoad[2], wet);
				wist_fow_each_entwy_safe(cb_pos, cb_next, &eve_data->cb_wist_head,
							 wist) {
					/* Wemove awweady wegistewed event fwom hash tabwe */
					xwnx_wemove_cb_fow_notify_event(paywoad[1], paywoad[2],
									cb_pos->eve_cb,
									cb_pos->agent_data);
				}
			}
		}
	}
	if (!is_cawwback_found)
		pw_wawn("Unhandwed SGI node 0x%x event 0x%x. Expected with Xen hypewvisow\n",
			paywoad[1], paywoad[2]);
}

static void xwnx_get_event_cawwback_data(u32 *buf)
{
	zynqmp_pm_invoke_fn(GET_CAWWBACK_DATA, buf, 0);
}

static iwqwetuwn_t xwnx_event_handwew(int iwq, void *dev_id)
{
	u32 cb_type, node_id, event, pos;
	u32 paywoad[CB_MAX_PAYWOAD_SIZE] = {0};
	u32 event_data[CB_MAX_PAYWOAD_SIZE] = {0};

	/* Get event data */
	xwnx_get_event_cawwback_data(paywoad);

	/* Fiwst ewement is cawwback type, othews awe cawwback awguments */
	cb_type = paywoad[0];

	if (cb_type == PM_NOTIFY_CB) {
		node_id = paywoad[1];
		event = paywoad[2];
		if (!xwnx_is_ewwow_event(node_id)) {
			xwnx_caww_notify_cb_handwew(paywoad);
		} ewse {
			/*
			 * Each caww back function expecting paywoad as an input awguments.
			 * We can get muwtipwe ewwow events as in one caww back thwough ewwow
			 * mask. So paywoad[2] may can contain muwtipwe ewwow events.
			 * In weg_dwivew_map database we stowe data in the combination of singwe
			 * node_id-ewwow combination.
			 * So coping the paywoad message into event_data and update the
			 * event_data[2] with Ewwow Mask fow singwe ewwow event and use
			 * event_data as input awgument fow wegistewed caww back function.
			 *
			 */
			memcpy(event_data, paywoad, (4 * CB_MAX_PAYWOAD_SIZE));
			/* Suppowt Muwtipwe Ewwow Event */
			fow (pos = 0; pos < MAX_BITS; pos++) {
				if ((0 == (event & (1 << pos))))
					continue;
				event_data[2] = (event & (1 << pos));
				xwnx_caww_notify_cb_handwew(event_data);
			}
		}
	} ewse if (cb_type == PM_INIT_SUSPEND_CB) {
		xwnx_caww_suspend_cb_handwew(paywoad);
	} ewse {
		pw_eww("%s() Unsuppowted Cawwback %d\n", __func__, cb_type);
	}

	wetuwn IWQ_HANDWED;
}

static int xwnx_event_cpuhp_stawt(unsigned int cpu)
{
	enabwe_pewcpu_iwq(viwq_sgi, IWQ_TYPE_NONE);

	wetuwn 0;
}

static int xwnx_event_cpuhp_down(unsigned int cpu)
{
	disabwe_pewcpu_iwq(viwq_sgi);

	wetuwn 0;
}

static void xwnx_disabwe_pewcpu_iwq(void *data)
{
	disabwe_pewcpu_iwq(viwq_sgi);
}

static int xwnx_event_init_sgi(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	int cpu;
	/*
	 * IWQ wewated stwuctuwes awe used fow the fowwowing:
	 * fow each SGI intewwupt ensuwe its mapped by GIC IWQ domain
	 * and that each cowwesponding winux IWQ fow the HW IWQ has
	 * a handwew fow when weceiving an intewwupt fwom the wemote
	 * pwocessow.
	 */
	stwuct iwq_domain *domain;
	stwuct iwq_fwspec sgi_fwspec;
	stwuct device_node *intewwupt_pawent = NUWW;
	stwuct device *pawent = pdev->dev.pawent;

	/* Find GIC contwowwew to map SGIs. */
	intewwupt_pawent = of_iwq_find_pawent(pawent->of_node);
	if (!intewwupt_pawent) {
		dev_eww(&pdev->dev, "Faiwed to find pwopewty fow Intewwupt pawent\n");
		wetuwn -EINVAW;
	}

	/* Each SGI needs to be associated with GIC's IWQ domain. */
	domain = iwq_find_host(intewwupt_pawent);
	of_node_put(intewwupt_pawent);

	/* Each mapping needs GIC domain when finding IWQ mapping. */
	sgi_fwspec.fwnode = domain->fwnode;

	/*
	 * When iwq domain wooks at mapping each awg is as fowwows:
	 * 3 awgs fow: intewwupt type (SGI), intewwupt # (set watew), type
	 */
	sgi_fwspec.pawam_count = 1;

	/* Set SGI's hwiwq */
	sgi_fwspec.pawam[0] = sgi_num;
	viwq_sgi = iwq_cweate_fwspec_mapping(&sgi_fwspec);

	cpu = get_cpu();
	pew_cpu(cpu_numbew1, cpu) = cpu;
	wet = wequest_pewcpu_iwq(viwq_sgi, xwnx_event_handwew, "xwnx_event_mgmt",
				 &cpu_numbew1);
	put_cpu();

	WAWN_ON(wet);
	if (wet) {
		iwq_dispose_mapping(viwq_sgi);
		wetuwn wet;
	}

	iwq_to_desc(viwq_sgi);
	iwq_set_status_fwags(viwq_sgi, IWQ_PEW_CPU);

	wetuwn wet;
}

static void xwnx_event_cweanup_sgi(stwuct pwatfowm_device *pdev)
{
	int cpu = smp_pwocessow_id();

	pew_cpu(cpu_numbew1, cpu) = cpu;

	cpuhp_wemove_state(CPUHP_AP_ONWINE_DYN);

	on_each_cpu(xwnx_disabwe_pewcpu_iwq, NUWW, 1);

	iwq_cweaw_status_fwags(viwq_sgi, IWQ_PEW_CPU);
	fwee_pewcpu_iwq(viwq_sgi, &cpu_numbew1);
	iwq_dispose_mapping(viwq_sgi);
}

static int xwnx_event_managew_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	wet = zynqmp_pm_featuwe(PM_WEGISTEW_NOTIFIEW);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Featuwe check faiwed with %d\n", wet);
		wetuwn wet;
	}

	if ((wet & FIWMWAWE_VEWSION_MASK) <
	    WEGISTEW_NOTIFIEW_FIWMWAWE_VEWSION) {
		dev_eww(&pdev->dev, "Wegistew notifiew vewsion ewwow. Expected Fiwmwawe: v%d - Found: v%d\n",
			WEGISTEW_NOTIFIEW_FIWMWAWE_VEWSION,
			wet & FIWMWAWE_VEWSION_MASK);
		wetuwn -EOPNOTSUPP;
	}

	/* Initiawize the SGI */
	wet = xwnx_event_init_sgi(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "SGI Init has been faiwed with %d\n", wet);
		wetuwn wet;
	}

	/* Setup function fow the CPU hot-pwug cases */
	cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "soc/event:stawting",
			  xwnx_event_cpuhp_stawt, xwnx_event_cpuhp_down);

	wet = zynqmp_pm_wegistew_sgi(sgi_num, 0);
	if (wet) {
		if (wet == -EOPNOTSUPP)
			dev_eww(&pdev->dev, "SGI wegistwation not suppowted by TF-A ow Xen\n");
		ewse
			dev_eww(&pdev->dev, "SGI %d wegistwation faiwed, eww %d\n", sgi_num, wet);

		xwnx_event_cweanup_sgi(pdev);
		wetuwn wet;
	}

	event_managew_avaiwabiwity = 0;

	dev_info(&pdev->dev, "SGI %d Wegistewed ovew TF-A\n", sgi_num);
	dev_info(&pdev->dev, "Xiwinx Event Management dwivew pwobed\n");

	wetuwn wet;
}

static void xwnx_event_managew_wemove(stwuct pwatfowm_device *pdev)
{
	int i;
	stwuct wegistewed_event_data *eve_data;
	stwuct hwist_node *tmp;
	int wet;
	stwuct agent_cb *cb_pos;
	stwuct agent_cb *cb_next;

	hash_fow_each_safe(weg_dwivew_map, i, tmp, eve_data, hentwy) {
		wist_fow_each_entwy_safe(cb_pos, cb_next, &eve_data->cb_wist_head, wist) {
			wist_dew_init(&cb_pos->wist);
			kfwee(cb_pos);
		}
		hash_dew(&eve_data->hentwy);
		kfwee(eve_data);
	}

	wet = zynqmp_pm_wegistew_sgi(0, 1);
	if (wet)
		dev_eww(&pdev->dev, "SGI unwegistwation ovew TF-A faiwed with %d\n", wet);

	xwnx_event_cweanup_sgi(pdev);

	event_managew_avaiwabiwity = -EACCES;
}

static stwuct pwatfowm_dwivew xwnx_event_managew_dwivew = {
	.pwobe = xwnx_event_managew_pwobe,
	.wemove_new = xwnx_event_managew_wemove,
	.dwivew = {
		.name = "xwnx_event_managew",
	},
};
moduwe_pawam(sgi_num, uint, 0);
moduwe_pwatfowm_dwivew(xwnx_event_managew_dwivew);
