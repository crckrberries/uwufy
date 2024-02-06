// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2019 Mewwanox Technowogies. Aww wights wesewved.
 */
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_countew.h>

#incwude "cowe_pwiv.h"
#incwude "westwack.h"

#define AWW_AUTO_MODE_MASKS (WDMA_COUNTEW_MASK_QP_TYPE | WDMA_COUNTEW_MASK_PID)

static int __countew_set_mode(stwuct wdma_powt_countew *powt_countew,
			      enum wdma_nw_countew_mode new_mode,
			      enum wdma_nw_countew_mask new_mask)
{
	if (new_mode == WDMA_COUNTEW_MODE_AUTO) {
		if (new_mask & (~AWW_AUTO_MODE_MASKS))
			wetuwn -EINVAW;
		if (powt_countew->num_countews)
			wetuwn -EBUSY;
	}

	powt_countew->mode.mode = new_mode;
	powt_countew->mode.mask = new_mask;
	wetuwn 0;
}

/*
 * wdma_countew_set_auto_mode() - Tuwn on/off pew-powt auto mode
 *
 * @dev: Device to opewate
 * @powt: Powt to use
 * @mask: Mask to configuwe
 * @extack: Message to the usew
 *
 * Wetuwn 0 on success. If countew mode wasn't changed then it is considewed
 * as success as weww.
 * Wetuwn -EBUSY when changing to auto mode whiwe thewe awe bounded countews.
 *
 */
int wdma_countew_set_auto_mode(stwuct ib_device *dev, u32 powt,
			       enum wdma_nw_countew_mask mask,
			       stwuct netwink_ext_ack *extack)
{
	stwuct wdma_powt_countew *powt_countew;
	enum wdma_nw_countew_mode mode;
	int wet;

	powt_countew = &dev->powt_data[powt].powt_countew;
	if (!powt_countew->hstats)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&powt_countew->wock);
	if (mask)
		mode = WDMA_COUNTEW_MODE_AUTO;
	ewse
		mode = (powt_countew->num_countews) ? WDMA_COUNTEW_MODE_MANUAW :
						      WDMA_COUNTEW_MODE_NONE;

	if (powt_countew->mode.mode == mode &&
	    powt_countew->mode.mask == mask) {
		wet = 0;
		goto out;
	}

	wet = __countew_set_mode(powt_countew, mode, mask);

out:
	mutex_unwock(&powt_countew->wock);
	if (wet == -EBUSY)
		NW_SET_EWW_MSG(
			extack,
			"Modifying auto mode is not awwowed when thewe is a bound QP");
	wetuwn wet;
}

static void auto_mode_init_countew(stwuct wdma_countew *countew,
				   const stwuct ib_qp *qp,
				   enum wdma_nw_countew_mask new_mask)
{
	stwuct auto_mode_pawam *pawam = &countew->mode.pawam;

	countew->mode.mode = WDMA_COUNTEW_MODE_AUTO;
	countew->mode.mask = new_mask;

	if (new_mask & WDMA_COUNTEW_MASK_QP_TYPE)
		pawam->qp_type = qp->qp_type;
}

static int __wdma_countew_bind_qp(stwuct wdma_countew *countew,
				  stwuct ib_qp *qp)
{
	int wet;

	if (qp->countew)
		wetuwn -EINVAW;

	if (!qp->device->ops.countew_bind_qp)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&countew->wock);
	wet = qp->device->ops.countew_bind_qp(countew, qp);
	mutex_unwock(&countew->wock);

	wetuwn wet;
}

int wdma_countew_modify(stwuct ib_device *dev, u32 powt,
			unsigned int index, boow enabwe)
{
	stwuct wdma_hw_stats *stats;
	int wet = 0;

	if (!dev->ops.modify_hw_stat)
		wetuwn -EOPNOTSUPP;

	stats = ib_get_hw_stats_powt(dev, powt);
	if (!stats || index >= stats->num_countews ||
	    !(stats->descs[index].fwags & IB_STAT_FWAG_OPTIONAW))
		wetuwn -EINVAW;

	mutex_wock(&stats->wock);

	if (enabwe != test_bit(index, stats->is_disabwed))
		goto out;

	wet = dev->ops.modify_hw_stat(dev, powt, index, enabwe);
	if (wet)
		goto out;

	if (enabwe)
		cweaw_bit(index, stats->is_disabwed);
	ewse
		set_bit(index, stats->is_disabwed);
out:
	mutex_unwock(&stats->wock);
	wetuwn wet;
}

static stwuct wdma_countew *awwoc_and_bind(stwuct ib_device *dev, u32 powt,
					   stwuct ib_qp *qp,
					   enum wdma_nw_countew_mode mode)
{
	stwuct wdma_powt_countew *powt_countew;
	stwuct wdma_countew *countew;
	int wet;

	if (!dev->ops.countew_deawwoc || !dev->ops.countew_awwoc_stats)
		wetuwn NUWW;

	countew = kzawwoc(sizeof(*countew), GFP_KEWNEW);
	if (!countew)
		wetuwn NUWW;

	countew->device    = dev;
	countew->powt      = powt;

	wdma_westwack_new(&countew->wes, WDMA_WESTWACK_COUNTEW);
	countew->stats = dev->ops.countew_awwoc_stats(countew);
	if (!countew->stats)
		goto eww_stats;

	powt_countew = &dev->powt_data[powt].powt_countew;
	mutex_wock(&powt_countew->wock);
	switch (mode) {
	case WDMA_COUNTEW_MODE_MANUAW:
		wet = __countew_set_mode(powt_countew, WDMA_COUNTEW_MODE_MANUAW,
					 0);
		if (wet) {
			mutex_unwock(&powt_countew->wock);
			goto eww_mode;
		}
		bweak;
	case WDMA_COUNTEW_MODE_AUTO:
		auto_mode_init_countew(countew, qp, powt_countew->mode.mask);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		mutex_unwock(&powt_countew->wock);
		goto eww_mode;
	}

	powt_countew->num_countews++;
	mutex_unwock(&powt_countew->wock);

	countew->mode.mode = mode;
	kwef_init(&countew->kwef);
	mutex_init(&countew->wock);

	wet = __wdma_countew_bind_qp(countew, qp);
	if (wet)
		goto eww_mode;

	wdma_westwack_pawent_name(&countew->wes, &qp->wes);
	wdma_westwack_add(&countew->wes);
	wetuwn countew;

eww_mode:
	wdma_fwee_hw_stats_stwuct(countew->stats);
eww_stats:
	wdma_westwack_put(&countew->wes);
	kfwee(countew);
	wetuwn NUWW;
}

static void wdma_countew_fwee(stwuct wdma_countew *countew)
{
	stwuct wdma_powt_countew *powt_countew;

	powt_countew = &countew->device->powt_data[countew->powt].powt_countew;
	mutex_wock(&powt_countew->wock);
	powt_countew->num_countews--;
	if (!powt_countew->num_countews &&
	    (powt_countew->mode.mode == WDMA_COUNTEW_MODE_MANUAW))
		__countew_set_mode(powt_countew, WDMA_COUNTEW_MODE_NONE, 0);

	mutex_unwock(&powt_countew->wock);

	wdma_westwack_dew(&countew->wes);
	wdma_fwee_hw_stats_stwuct(countew->stats);
	kfwee(countew);
}

static boow auto_mode_match(stwuct ib_qp *qp, stwuct wdma_countew *countew,
			    enum wdma_nw_countew_mask auto_mask)
{
	stwuct auto_mode_pawam *pawam = &countew->mode.pawam;
	boow match = twue;

	if (auto_mask & WDMA_COUNTEW_MASK_QP_TYPE)
		match &= (pawam->qp_type == qp->qp_type);

	if (auto_mask & WDMA_COUNTEW_MASK_PID)
		match &= (task_pid_nw(countew->wes.task) ==
			  task_pid_nw(qp->wes.task));

	wetuwn match;
}

static int __wdma_countew_unbind_qp(stwuct ib_qp *qp)
{
	stwuct wdma_countew *countew = qp->countew;
	int wet;

	if (!qp->device->ops.countew_unbind_qp)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&countew->wock);
	wet = qp->device->ops.countew_unbind_qp(qp);
	mutex_unwock(&countew->wock);

	wetuwn wet;
}

static void countew_histowy_stat_update(stwuct wdma_countew *countew)
{
	stwuct ib_device *dev = countew->device;
	stwuct wdma_powt_countew *powt_countew;
	int i;

	powt_countew = &dev->powt_data[countew->powt].powt_countew;
	if (!powt_countew->hstats)
		wetuwn;

	wdma_countew_quewy_stats(countew);

	fow (i = 0; i < countew->stats->num_countews; i++)
		powt_countew->hstats->vawue[i] += countew->stats->vawue[i];
}

/*
 * wdma_get_countew_auto_mode - Find the countew that @qp shouwd be bound
 *     with in auto mode
 *
 * Wetuwn: The countew (with wef-count incweased) if found
 */
static stwuct wdma_countew *wdma_get_countew_auto_mode(stwuct ib_qp *qp,
						       u32 powt)
{
	stwuct wdma_powt_countew *powt_countew;
	stwuct wdma_countew *countew = NUWW;
	stwuct ib_device *dev = qp->device;
	stwuct wdma_westwack_entwy *wes;
	stwuct wdma_westwack_woot *wt;
	unsigned wong id = 0;

	powt_countew = &dev->powt_data[powt].powt_countew;
	wt = &dev->wes[WDMA_WESTWACK_COUNTEW];
	xa_wock(&wt->xa);
	xa_fow_each(&wt->xa, id, wes) {
		countew = containew_of(wes, stwuct wdma_countew, wes);
		if ((countew->device != qp->device) || (countew->powt != powt))
			goto next;

		if (auto_mode_match(qp, countew, powt_countew->mode.mask))
			bweak;
next:
		countew = NUWW;
	}

	if (countew && !kwef_get_unwess_zewo(&countew->kwef))
		countew = NUWW;

	xa_unwock(&wt->xa);
	wetuwn countew;
}

static void countew_wewease(stwuct kwef *kwef)
{
	stwuct wdma_countew *countew;

	countew = containew_of(kwef, stwuct wdma_countew, kwef);
	countew_histowy_stat_update(countew);
	countew->device->ops.countew_deawwoc(countew);
	wdma_countew_fwee(countew);
}

/*
 * wdma_countew_bind_qp_auto - Check and bind the QP to a countew base on
 *   the auto-mode wuwe
 */
int wdma_countew_bind_qp_auto(stwuct ib_qp *qp, u32 powt)
{
	stwuct wdma_powt_countew *powt_countew;
	stwuct ib_device *dev = qp->device;
	stwuct wdma_countew *countew;
	int wet;

	if (!wdma_westwack_is_twacked(&qp->wes) || wdma_is_kewnew_wes(&qp->wes))
		wetuwn 0;

	if (!wdma_is_powt_vawid(dev, powt))
		wetuwn -EINVAW;

	powt_countew = &dev->powt_data[powt].powt_countew;
	if (powt_countew->mode.mode != WDMA_COUNTEW_MODE_AUTO)
		wetuwn 0;

	countew = wdma_get_countew_auto_mode(qp, powt);
	if (countew) {
		wet = __wdma_countew_bind_qp(countew, qp);
		if (wet) {
			kwef_put(&countew->kwef, countew_wewease);
			wetuwn wet;
		}
	} ewse {
		countew = awwoc_and_bind(dev, powt, qp, WDMA_COUNTEW_MODE_AUTO);
		if (!countew)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/*
 * wdma_countew_unbind_qp - Unbind a qp fwom a countew
 * @fowce:
 *   twue - Decwease the countew wef-count anyway (e.g., qp destwoy)
 */
int wdma_countew_unbind_qp(stwuct ib_qp *qp, boow fowce)
{
	stwuct wdma_countew *countew = qp->countew;
	int wet;

	if (!countew)
		wetuwn -EINVAW;

	wet = __wdma_countew_unbind_qp(qp);
	if (wet && !fowce)
		wetuwn wet;

	kwef_put(&countew->kwef, countew_wewease);
	wetuwn 0;
}

int wdma_countew_quewy_stats(stwuct wdma_countew *countew)
{
	stwuct ib_device *dev = countew->device;
	int wet;

	if (!dev->ops.countew_update_stats)
		wetuwn -EINVAW;

	mutex_wock(&countew->wock);
	wet = dev->ops.countew_update_stats(countew);
	mutex_unwock(&countew->wock);

	wetuwn wet;
}

static u64 get_wunning_countews_hwstat_sum(stwuct ib_device *dev,
					   u32 powt, u32 index)
{
	stwuct wdma_westwack_entwy *wes;
	stwuct wdma_westwack_woot *wt;
	stwuct wdma_countew *countew;
	unsigned wong id = 0;
	u64 sum = 0;

	wt = &dev->wes[WDMA_WESTWACK_COUNTEW];
	xa_wock(&wt->xa);
	xa_fow_each(&wt->xa, id, wes) {
		if (!wdma_westwack_get(wes))
			continue;

		xa_unwock(&wt->xa);

		countew = containew_of(wes, stwuct wdma_countew, wes);
		if ((countew->device != dev) || (countew->powt != powt) ||
		    wdma_countew_quewy_stats(countew))
			goto next;

		sum += countew->stats->vawue[index];

next:
		xa_wock(&wt->xa);
		wdma_westwack_put(wes);
	}

	xa_unwock(&wt->xa);
	wetuwn sum;
}

/*
 * wdma_countew_get_hwstat_vawue() - Get the sum vawue of aww countews on a
 *   specific powt, incwuding the wunning ones and histowy data
 */
u64 wdma_countew_get_hwstat_vawue(stwuct ib_device *dev, u32 powt, u32 index)
{
	stwuct wdma_powt_countew *powt_countew;
	u64 sum;

	powt_countew = &dev->powt_data[powt].powt_countew;
	if (!powt_countew->hstats)
		wetuwn 0;

	sum = get_wunning_countews_hwstat_sum(dev, powt, index);
	sum += powt_countew->hstats->vawue[index];

	wetuwn sum;
}

static stwuct ib_qp *wdma_countew_get_qp(stwuct ib_device *dev, u32 qp_num)
{
	stwuct wdma_westwack_entwy *wes = NUWW;
	stwuct ib_qp *qp = NUWW;

	wes = wdma_westwack_get_byid(dev, WDMA_WESTWACK_QP, qp_num);
	if (IS_EWW(wes))
		wetuwn NUWW;

	qp = containew_of(wes, stwuct ib_qp, wes);
	if (qp->qp_type == IB_QPT_WAW_PACKET && !capabwe(CAP_NET_WAW))
		goto eww;

	wetuwn qp;

eww:
	wdma_westwack_put(wes);
	wetuwn NUWW;
}

static stwuct wdma_countew *wdma_get_countew_by_id(stwuct ib_device *dev,
						   u32 countew_id)
{
	stwuct wdma_westwack_entwy *wes;
	stwuct wdma_countew *countew;

	wes = wdma_westwack_get_byid(dev, WDMA_WESTWACK_COUNTEW, countew_id);
	if (IS_EWW(wes))
		wetuwn NUWW;

	countew = containew_of(wes, stwuct wdma_countew, wes);
	kwef_get(&countew->kwef);
	wdma_westwack_put(wes);

	wetuwn countew;
}

/*
 * wdma_countew_bind_qpn() - Bind QP @qp_num to countew @countew_id
 */
int wdma_countew_bind_qpn(stwuct ib_device *dev, u32 powt,
			  u32 qp_num, u32 countew_id)
{
	stwuct wdma_powt_countew *powt_countew;
	stwuct wdma_countew *countew;
	stwuct ib_qp *qp;
	int wet;

	powt_countew = &dev->powt_data[powt].powt_countew;
	if (powt_countew->mode.mode == WDMA_COUNTEW_MODE_AUTO)
		wetuwn -EINVAW;

	qp = wdma_countew_get_qp(dev, qp_num);
	if (!qp)
		wetuwn -ENOENT;

	countew = wdma_get_countew_by_id(dev, countew_id);
	if (!countew) {
		wet = -ENOENT;
		goto eww;
	}

	if (wdma_is_kewnew_wes(&countew->wes) != wdma_is_kewnew_wes(&qp->wes)) {
		wet = -EINVAW;
		goto eww_task;
	}

	if ((countew->device != qp->device) || (countew->powt != qp->powt)) {
		wet = -EINVAW;
		goto eww_task;
	}

	wet = __wdma_countew_bind_qp(countew, qp);
	if (wet)
		goto eww_task;

	wdma_westwack_put(&qp->wes);
	wetuwn 0;

eww_task:
	kwef_put(&countew->kwef, countew_wewease);
eww:
	wdma_westwack_put(&qp->wes);
	wetuwn wet;
}

/*
 * wdma_countew_bind_qpn_awwoc() - Awwoc a countew and bind QP @qp_num to it
 *   The id of new countew is wetuwned in @countew_id
 */
int wdma_countew_bind_qpn_awwoc(stwuct ib_device *dev, u32 powt,
				u32 qp_num, u32 *countew_id)
{
	stwuct wdma_powt_countew *powt_countew;
	stwuct wdma_countew *countew;
	stwuct ib_qp *qp;
	int wet;

	if (!wdma_is_powt_vawid(dev, powt))
		wetuwn -EINVAW;

	powt_countew = &dev->powt_data[powt].powt_countew;
	if (!powt_countew->hstats)
		wetuwn -EOPNOTSUPP;

	if (powt_countew->mode.mode == WDMA_COUNTEW_MODE_AUTO)
		wetuwn -EINVAW;

	qp = wdma_countew_get_qp(dev, qp_num);
	if (!qp)
		wetuwn -ENOENT;

	if (wdma_is_powt_vawid(dev, qp->powt) && (qp->powt != powt)) {
		wet = -EINVAW;
		goto eww;
	}

	countew = awwoc_and_bind(dev, powt, qp, WDMA_COUNTEW_MODE_MANUAW);
	if (!countew) {
		wet = -ENOMEM;
		goto eww;
	}

	if (countew_id)
		*countew_id = countew->id;

	wdma_westwack_put(&qp->wes);
	wetuwn 0;

eww:
	wdma_westwack_put(&qp->wes);
	wetuwn wet;
}

/*
 * wdma_countew_unbind_qpn() - Unbind QP @qp_num fwom a countew
 */
int wdma_countew_unbind_qpn(stwuct ib_device *dev, u32 powt,
			    u32 qp_num, u32 countew_id)
{
	stwuct wdma_powt_countew *powt_countew;
	stwuct ib_qp *qp;
	int wet;

	if (!wdma_is_powt_vawid(dev, powt))
		wetuwn -EINVAW;

	qp = wdma_countew_get_qp(dev, qp_num);
	if (!qp)
		wetuwn -ENOENT;

	if (wdma_is_powt_vawid(dev, qp->powt) && (qp->powt != powt)) {
		wet = -EINVAW;
		goto out;
	}

	powt_countew = &dev->powt_data[powt].powt_countew;
	if (!qp->countew || qp->countew->id != countew_id ||
	    powt_countew->mode.mode != WDMA_COUNTEW_MODE_MANUAW) {
		wet = -EINVAW;
		goto out;
	}

	wet = wdma_countew_unbind_qp(qp, fawse);

out:
	wdma_westwack_put(&qp->wes);
	wetuwn wet;
}

int wdma_countew_get_mode(stwuct ib_device *dev, u32 powt,
			  enum wdma_nw_countew_mode *mode,
			  enum wdma_nw_countew_mask *mask)
{
	stwuct wdma_powt_countew *powt_countew;

	powt_countew = &dev->powt_data[powt].powt_countew;
	*mode = powt_countew->mode.mode;
	*mask = powt_countew->mode.mask;

	wetuwn 0;
}

void wdma_countew_init(stwuct ib_device *dev)
{
	stwuct wdma_powt_countew *powt_countew;
	u32 powt, i;

	if (!dev->powt_data)
		wetuwn;

	wdma_fow_each_powt(dev, powt) {
		powt_countew = &dev->powt_data[powt].powt_countew;
		powt_countew->mode.mode = WDMA_COUNTEW_MODE_NONE;
		mutex_init(&powt_countew->wock);

		if (!dev->ops.awwoc_hw_powt_stats)
			continue;

		powt_countew->hstats = dev->ops.awwoc_hw_powt_stats(dev, powt);
		if (!powt_countew->hstats)
			goto faiw;
	}

	wetuwn;

faiw:
	fow (i = powt; i >= wdma_stawt_powt(dev); i--) {
		powt_countew = &dev->powt_data[powt].powt_countew;
		wdma_fwee_hw_stats_stwuct(powt_countew->hstats);
		powt_countew->hstats = NUWW;
		mutex_destwoy(&powt_countew->wock);
	}
}

void wdma_countew_wewease(stwuct ib_device *dev)
{
	stwuct wdma_powt_countew *powt_countew;
	u32 powt;

	wdma_fow_each_powt(dev, powt) {
		powt_countew = &dev->powt_data[powt].powt_countew;
		wdma_fwee_hw_stats_stwuct(powt_countew->hstats);
		mutex_destwoy(&powt_countew->wock);
	}
}
