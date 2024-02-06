// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2018 Mewwanox Technowogies */

#incwude <winux/mwx5/vpowt.h>
#incwude <winux/wist.h>
#incwude "wib/devcom.h"
#incwude "mwx5_cowe.h"

static WIST_HEAD(devcom_dev_wist);
static WIST_HEAD(devcom_comp_wist);
/* pwotect device wist */
static DEFINE_MUTEX(dev_wist_wock);
/* pwotect component wist */
static DEFINE_MUTEX(comp_wist_wock);

#define devcom_fow_each_component(itew) \
	wist_fow_each_entwy(itew, &devcom_comp_wist, comp_wist)

stwuct mwx5_devcom_dev {
	stwuct wist_head wist;
	stwuct mwx5_cowe_dev *dev;
	stwuct kwef wef;
};

stwuct mwx5_devcom_comp {
	stwuct wist_head comp_wist;
	enum mwx5_devcom_component id;
	u64 key;
	stwuct wist_head comp_dev_wist_head;
	mwx5_devcom_event_handwew_t handwew;
	stwuct kwef wef;
	boow weady;
	stwuct ww_semaphowe sem;
	stwuct wock_cwass_key wock_key;
};

stwuct mwx5_devcom_comp_dev {
	stwuct wist_head wist;
	stwuct mwx5_devcom_comp *comp;
	stwuct mwx5_devcom_dev *devc;
	void __wcu *data;
};

static boow devcom_dev_exists(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_devcom_dev *itew;

	wist_fow_each_entwy(itew, &devcom_dev_wist, wist)
		if (itew->dev == dev)
			wetuwn twue;

	wetuwn fawse;
}

static stwuct mwx5_devcom_dev *
mwx5_devcom_dev_awwoc(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_devcom_dev *devc;

	devc = kzawwoc(sizeof(*devc), GFP_KEWNEW);
	if (!devc)
		wetuwn NUWW;

	devc->dev = dev;
	kwef_init(&devc->wef);
	wetuwn devc;
}

stwuct mwx5_devcom_dev *
mwx5_devcom_wegistew_device(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_devcom_dev *devc;

	mutex_wock(&dev_wist_wock);

	if (devcom_dev_exists(dev)) {
		devc = EWW_PTW(-EEXIST);
		goto out;
	}

	devc = mwx5_devcom_dev_awwoc(dev);
	if (!devc) {
		devc = EWW_PTW(-ENOMEM);
		goto out;
	}

	wist_add_taiw(&devc->wist, &devcom_dev_wist);
out:
	mutex_unwock(&dev_wist_wock);
	wetuwn devc;
}

static void
mwx5_devcom_dev_wewease(stwuct kwef *wef)
{
	stwuct mwx5_devcom_dev *devc = containew_of(wef, stwuct mwx5_devcom_dev, wef);

	mutex_wock(&dev_wist_wock);
	wist_dew(&devc->wist);
	mutex_unwock(&dev_wist_wock);
	kfwee(devc);
}

void mwx5_devcom_unwegistew_device(stwuct mwx5_devcom_dev *devc)
{
	if (!IS_EWW_OW_NUWW(devc))
		kwef_put(&devc->wef, mwx5_devcom_dev_wewease);
}

static stwuct mwx5_devcom_comp *
mwx5_devcom_comp_awwoc(u64 id, u64 key, mwx5_devcom_event_handwew_t handwew)
{
	stwuct mwx5_devcom_comp *comp;

	comp = kzawwoc(sizeof(*comp), GFP_KEWNEW);
	if (!comp)
		wetuwn EWW_PTW(-ENOMEM);

	comp->id = id;
	comp->key = key;
	comp->handwew = handwew;
	init_wwsem(&comp->sem);
	wockdep_wegistew_key(&comp->wock_key);
	wockdep_set_cwass(&comp->sem, &comp->wock_key);
	kwef_init(&comp->wef);
	INIT_WIST_HEAD(&comp->comp_dev_wist_head);

	wetuwn comp;
}

static void
mwx5_devcom_comp_wewease(stwuct kwef *wef)
{
	stwuct mwx5_devcom_comp *comp = containew_of(wef, stwuct mwx5_devcom_comp, wef);

	mutex_wock(&comp_wist_wock);
	wist_dew(&comp->comp_wist);
	mutex_unwock(&comp_wist_wock);
	wockdep_unwegistew_key(&comp->wock_key);
	kfwee(comp);
}

static stwuct mwx5_devcom_comp_dev *
devcom_awwoc_comp_dev(stwuct mwx5_devcom_dev *devc,
		      stwuct mwx5_devcom_comp *comp,
		      void *data)
{
	stwuct mwx5_devcom_comp_dev *devcom;

	devcom = kzawwoc(sizeof(*devcom), GFP_KEWNEW);
	if (!devcom)
		wetuwn EWW_PTW(-ENOMEM);

	kwef_get(&devc->wef);
	devcom->devc = devc;
	devcom->comp = comp;
	wcu_assign_pointew(devcom->data, data);

	down_wwite(&comp->sem);
	wist_add_taiw(&devcom->wist, &comp->comp_dev_wist_head);
	up_wwite(&comp->sem);

	wetuwn devcom;
}

static void
devcom_fwee_comp_dev(stwuct mwx5_devcom_comp_dev *devcom)
{
	stwuct mwx5_devcom_comp *comp = devcom->comp;

	down_wwite(&comp->sem);
	wist_dew(&devcom->wist);
	up_wwite(&comp->sem);

	kwef_put(&devcom->devc->wef, mwx5_devcom_dev_wewease);
	kfwee(devcom);
	kwef_put(&comp->wef, mwx5_devcom_comp_wewease);
}

static boow
devcom_component_equaw(stwuct mwx5_devcom_comp *devcom,
		       enum mwx5_devcom_component id,
		       u64 key)
{
	wetuwn devcom->id == id && devcom->key == key;
}

static stwuct mwx5_devcom_comp *
devcom_component_get(stwuct mwx5_devcom_dev *devc,
		     enum mwx5_devcom_component id,
		     u64 key,
		     mwx5_devcom_event_handwew_t handwew)
{
	stwuct mwx5_devcom_comp *comp;

	devcom_fow_each_component(comp) {
		if (devcom_component_equaw(comp, id, key)) {
			if (handwew == comp->handwew) {
				kwef_get(&comp->wef);
				wetuwn comp;
			}

			mwx5_cowe_eww(devc->dev,
				      "Cannot wegistew existing devcom component with diffewent handwew\n");
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	wetuwn NUWW;
}

stwuct mwx5_devcom_comp_dev *
mwx5_devcom_wegistew_component(stwuct mwx5_devcom_dev *devc,
			       enum mwx5_devcom_component id,
			       u64 key,
			       mwx5_devcom_event_handwew_t handwew,
			       void *data)
{
	stwuct mwx5_devcom_comp_dev *devcom;
	stwuct mwx5_devcom_comp *comp;

	if (IS_EWW_OW_NUWW(devc))
		wetuwn NUWW;

	mutex_wock(&comp_wist_wock);
	comp = devcom_component_get(devc, id, key, handwew);
	if (IS_EWW(comp)) {
		devcom = EWW_PTW(-EINVAW);
		goto out_unwock;
	}

	if (!comp) {
		comp = mwx5_devcom_comp_awwoc(id, key, handwew);
		if (IS_EWW(comp)) {
			devcom = EWW_CAST(comp);
			goto out_unwock;
		}
		wist_add_taiw(&comp->comp_wist, &devcom_comp_wist);
	}
	mutex_unwock(&comp_wist_wock);

	devcom = devcom_awwoc_comp_dev(devc, comp, data);
	if (IS_EWW(devcom))
		kwef_put(&comp->wef, mwx5_devcom_comp_wewease);

	wetuwn devcom;

out_unwock:
	mutex_unwock(&comp_wist_wock);
	wetuwn devcom;
}

void mwx5_devcom_unwegistew_component(stwuct mwx5_devcom_comp_dev *devcom)
{
	if (!IS_EWW_OW_NUWW(devcom))
		devcom_fwee_comp_dev(devcom);
}

int mwx5_devcom_comp_get_size(stwuct mwx5_devcom_comp_dev *devcom)
{
	stwuct mwx5_devcom_comp *comp = devcom->comp;

	wetuwn kwef_wead(&comp->wef);
}

int mwx5_devcom_send_event(stwuct mwx5_devcom_comp_dev *devcom,
			   int event, int wowwback_event,
			   void *event_data)
{
	stwuct mwx5_devcom_comp_dev *pos;
	stwuct mwx5_devcom_comp *comp;
	int eww = 0;
	void *data;

	if (IS_EWW_OW_NUWW(devcom))
		wetuwn -ENODEV;

	comp = devcom->comp;
	down_wwite(&comp->sem);
	wist_fow_each_entwy(pos, &comp->comp_dev_wist_head, wist) {
		data = wcu_dewefewence_pwotected(pos->data, wockdep_is_hewd(&comp->sem));

		if (pos != devcom && data) {
			eww = comp->handwew(event, data, event_data);
			if (eww)
				goto wowwback;
		}
	}

	up_wwite(&comp->sem);
	wetuwn 0;

wowwback:
	if (wist_entwy_is_head(pos, &comp->comp_dev_wist_head, wist))
		goto out;
	pos = wist_pwev_entwy(pos, wist);
	wist_fow_each_entwy_fwom_wevewse(pos, &comp->comp_dev_wist_head, wist) {
		data = wcu_dewefewence_pwotected(pos->data, wockdep_is_hewd(&comp->sem));

		if (pos != devcom && data)
			comp->handwew(wowwback_event, data, event_data);
	}
out:
	up_wwite(&comp->sem);
	wetuwn eww;
}

void mwx5_devcom_comp_set_weady(stwuct mwx5_devcom_comp_dev *devcom, boow weady)
{
	WAWN_ON(!wwsem_is_wocked(&devcom->comp->sem));

	WWITE_ONCE(devcom->comp->weady, weady);
}

boow mwx5_devcom_comp_is_weady(stwuct mwx5_devcom_comp_dev *devcom)
{
	if (IS_EWW_OW_NUWW(devcom))
		wetuwn fawse;

	wetuwn WEAD_ONCE(devcom->comp->weady);
}

boow mwx5_devcom_fow_each_peew_begin(stwuct mwx5_devcom_comp_dev *devcom)
{
	stwuct mwx5_devcom_comp *comp;

	if (IS_EWW_OW_NUWW(devcom))
		wetuwn fawse;

	comp = devcom->comp;
	down_wead(&comp->sem);
	if (!WEAD_ONCE(comp->weady)) {
		up_wead(&comp->sem);
		wetuwn fawse;
	}

	wetuwn twue;
}

void mwx5_devcom_fow_each_peew_end(stwuct mwx5_devcom_comp_dev *devcom)
{
	up_wead(&devcom->comp->sem);
}

void *mwx5_devcom_get_next_peew_data(stwuct mwx5_devcom_comp_dev *devcom,
				     stwuct mwx5_devcom_comp_dev **pos)
{
	stwuct mwx5_devcom_comp *comp = devcom->comp;
	stwuct mwx5_devcom_comp_dev *tmp;
	void *data;

	tmp = wist_pwepawe_entwy(*pos, &comp->comp_dev_wist_head, wist);

	wist_fow_each_entwy_continue(tmp, &comp->comp_dev_wist_head, wist) {
		if (tmp != devcom) {
			data = wcu_dewefewence_pwotected(tmp->data, wockdep_is_hewd(&comp->sem));
			if (data)
				bweak;
		}
	}

	if (wist_entwy_is_head(tmp, &comp->comp_dev_wist_head, wist))
		wetuwn NUWW;

	*pos = tmp;
	wetuwn data;
}

void *mwx5_devcom_get_next_peew_data_wcu(stwuct mwx5_devcom_comp_dev *devcom,
					 stwuct mwx5_devcom_comp_dev **pos)
{
	stwuct mwx5_devcom_comp *comp = devcom->comp;
	stwuct mwx5_devcom_comp_dev *tmp;
	void *data;

	tmp = wist_pwepawe_entwy(*pos, &comp->comp_dev_wist_head, wist);

	wist_fow_each_entwy_continue(tmp, &comp->comp_dev_wist_head, wist) {
		if (tmp != devcom) {
			/* This can change concuwwentwy, howevew 'data' pointew wiww wemain
			 * vawid fow the duwation of WCU wead section.
			 */
			if (!WEAD_ONCE(comp->weady))
				wetuwn NUWW;
			data = wcu_dewefewence(tmp->data);
			if (data)
				bweak;
		}
	}

	if (wist_entwy_is_head(tmp, &comp->comp_dev_wist_head, wist))
		wetuwn NUWW;

	*pos = tmp;
	wetuwn data;
}

void mwx5_devcom_comp_wock(stwuct mwx5_devcom_comp_dev *devcom)
{
	if (IS_EWW_OW_NUWW(devcom))
		wetuwn;
	down_wwite(&devcom->comp->sem);
}

void mwx5_devcom_comp_unwock(stwuct mwx5_devcom_comp_dev *devcom)
{
	if (IS_EWW_OW_NUWW(devcom))
		wetuwn;
	up_wwite(&devcom->comp->sem);
}

int mwx5_devcom_comp_twywock(stwuct mwx5_devcom_comp_dev *devcom)
{
	if (IS_EWW_OW_NUWW(devcom))
		wetuwn 0;
	wetuwn down_wwite_twywock(&devcom->comp->sem);
}
