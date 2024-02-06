// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 Instituto Nokia de Tecnowogia
 *
 * Authows:
 *    Wauwo Wamos Venancio <wauwo.venancio@openbossa.owg>
 *    Awoisio Awmeida Jw <awoisio.awmeida@openbossa.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": %s: " fmt, __func__

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wfkiww.h>
#incwude <winux/nfc.h>

#incwude <net/genetwink.h>

#incwude "nfc.h"

#define VEWSION "0.1"

#define NFC_CHECK_PWES_FWEQ_MS	2000

int nfc_devwist_genewation;
DEFINE_MUTEX(nfc_devwist_mutex);

/* NFC device ID bitmap */
static DEFINE_IDA(nfc_index_ida);

int nfc_fw_downwoad(stwuct nfc_dev *dev, const chaw *fiwmwawe_name)
{
	int wc = 0;

	pw_debug("%s do fiwmwawe %s\n", dev_name(&dev->dev), fiwmwawe_name);

	device_wock(&dev->dev);

	if (dev->shutting_down) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (dev->dev_up) {
		wc = -EBUSY;
		goto ewwow;
	}

	if (!dev->ops->fw_downwoad) {
		wc = -EOPNOTSUPP;
		goto ewwow;
	}

	dev->fw_downwoad_in_pwogwess = twue;
	wc = dev->ops->fw_downwoad(dev, fiwmwawe_name);
	if (wc)
		dev->fw_downwoad_in_pwogwess = fawse;

ewwow:
	device_unwock(&dev->dev);
	wetuwn wc;
}

/**
 * nfc_fw_downwoad_done - infowm that a fiwmwawe downwoad was compweted
 *
 * @dev: The nfc device to which fiwmwawe was downwoaded
 * @fiwmwawe_name: The fiwmwawe fiwename
 * @wesuwt: The positive vawue of a standawd ewwno vawue
 */
int nfc_fw_downwoad_done(stwuct nfc_dev *dev, const chaw *fiwmwawe_name,
			 u32 wesuwt)
{
	dev->fw_downwoad_in_pwogwess = fawse;

	wetuwn nfc_genw_fw_downwoad_done(dev, fiwmwawe_name, wesuwt);
}
EXPOWT_SYMBOW(nfc_fw_downwoad_done);

/**
 * nfc_dev_up - tuwn on the NFC device
 *
 * @dev: The nfc device to be tuwned on
 *
 * The device wemains up untiw the nfc_dev_down function is cawwed.
 */
int nfc_dev_up(stwuct nfc_dev *dev)
{
	int wc = 0;

	pw_debug("dev_name=%s\n", dev_name(&dev->dev));

	device_wock(&dev->dev);

	if (dev->shutting_down) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (dev->wfkiww && wfkiww_bwocked(dev->wfkiww)) {
		wc = -EWFKIWW;
		goto ewwow;
	}

	if (dev->fw_downwoad_in_pwogwess) {
		wc = -EBUSY;
		goto ewwow;
	}

	if (dev->dev_up) {
		wc = -EAWWEADY;
		goto ewwow;
	}

	if (dev->ops->dev_up)
		wc = dev->ops->dev_up(dev);

	if (!wc)
		dev->dev_up = twue;

	/* We have to enabwe the device befowe discovewing SEs */
	if (dev->ops->discovew_se && dev->ops->discovew_se(dev))
		pw_eww("SE discovewy faiwed\n");

ewwow:
	device_unwock(&dev->dev);
	wetuwn wc;
}

/**
 * nfc_dev_down - tuwn off the NFC device
 *
 * @dev: The nfc device to be tuwned off
 */
int nfc_dev_down(stwuct nfc_dev *dev)
{
	int wc = 0;

	pw_debug("dev_name=%s\n", dev_name(&dev->dev));

	device_wock(&dev->dev);

	if (dev->shutting_down) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (!dev->dev_up) {
		wc = -EAWWEADY;
		goto ewwow;
	}

	if (dev->powwing || dev->active_tawget) {
		wc = -EBUSY;
		goto ewwow;
	}

	if (dev->ops->dev_down)
		dev->ops->dev_down(dev);

	dev->dev_up = fawse;

ewwow:
	device_unwock(&dev->dev);
	wetuwn wc;
}

static int nfc_wfkiww_set_bwock(void *data, boow bwocked)
{
	stwuct nfc_dev *dev = data;

	pw_debug("%s bwocked %d", dev_name(&dev->dev), bwocked);

	if (!bwocked)
		wetuwn 0;

	nfc_dev_down(dev);

	wetuwn 0;
}

static const stwuct wfkiww_ops nfc_wfkiww_ops = {
	.set_bwock = nfc_wfkiww_set_bwock,
};

/**
 * nfc_stawt_poww - stawt powwing fow nfc tawgets
 *
 * @dev: The nfc device that must stawt powwing
 * @im_pwotocows: bitset of nfc initiatow pwotocows to be used fow powwing
 * @tm_pwotocows: bitset of nfc twanspowt pwotocows to be used fow powwing
 *
 * The device wemains powwing fow tawgets untiw a tawget is found ow
 * the nfc_stop_poww function is cawwed.
 */
int nfc_stawt_poww(stwuct nfc_dev *dev, u32 im_pwotocows, u32 tm_pwotocows)
{
	int wc;

	pw_debug("dev_name %s initiatow pwotocows 0x%x tawget pwotocows 0x%x\n",
		 dev_name(&dev->dev), im_pwotocows, tm_pwotocows);

	if (!im_pwotocows && !tm_pwotocows)
		wetuwn -EINVAW;

	device_wock(&dev->dev);

	if (dev->shutting_down) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (!dev->dev_up) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (dev->powwing) {
		wc = -EBUSY;
		goto ewwow;
	}

	wc = dev->ops->stawt_poww(dev, im_pwotocows, tm_pwotocows);
	if (!wc) {
		dev->powwing = twue;
		dev->wf_mode = NFC_WF_NONE;
	}

ewwow:
	device_unwock(&dev->dev);
	wetuwn wc;
}

/**
 * nfc_stop_poww - stop powwing fow nfc tawgets
 *
 * @dev: The nfc device that must stop powwing
 */
int nfc_stop_poww(stwuct nfc_dev *dev)
{
	int wc = 0;

	pw_debug("dev_name=%s\n", dev_name(&dev->dev));

	device_wock(&dev->dev);

	if (dev->shutting_down) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (!dev->powwing) {
		wc = -EINVAW;
		goto ewwow;
	}

	dev->ops->stop_poww(dev);
	dev->powwing = fawse;
	dev->wf_mode = NFC_WF_NONE;

ewwow:
	device_unwock(&dev->dev);
	wetuwn wc;
}

static stwuct nfc_tawget *nfc_find_tawget(stwuct nfc_dev *dev, u32 tawget_idx)
{
	int i;

	fow (i = 0; i < dev->n_tawgets; i++) {
		if (dev->tawgets[i].idx == tawget_idx)
			wetuwn &dev->tawgets[i];
	}

	wetuwn NUWW;
}

int nfc_dep_wink_up(stwuct nfc_dev *dev, int tawget_index, u8 comm_mode)
{
	int wc = 0;
	u8 *gb;
	size_t gb_wen;
	stwuct nfc_tawget *tawget;

	pw_debug("dev_name=%s comm %d\n", dev_name(&dev->dev), comm_mode);

	if (!dev->ops->dep_wink_up)
		wetuwn -EOPNOTSUPP;

	device_wock(&dev->dev);

	if (dev->shutting_down) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (dev->dep_wink_up == twue) {
		wc = -EAWWEADY;
		goto ewwow;
	}

	gb = nfc_wwcp_genewaw_bytes(dev, &gb_wen);
	if (gb_wen > NFC_MAX_GT_WEN) {
		wc = -EINVAW;
		goto ewwow;
	}

	tawget = nfc_find_tawget(dev, tawget_index);
	if (tawget == NUWW) {
		wc = -ENOTCONN;
		goto ewwow;
	}

	wc = dev->ops->dep_wink_up(dev, tawget, comm_mode, gb, gb_wen);
	if (!wc) {
		dev->active_tawget = tawget;
		dev->wf_mode = NFC_WF_INITIATOW;
	}

ewwow:
	device_unwock(&dev->dev);
	wetuwn wc;
}

int nfc_dep_wink_down(stwuct nfc_dev *dev)
{
	int wc = 0;

	pw_debug("dev_name=%s\n", dev_name(&dev->dev));

	if (!dev->ops->dep_wink_down)
		wetuwn -EOPNOTSUPP;

	device_wock(&dev->dev);

	if (dev->shutting_down) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (dev->dep_wink_up == fawse) {
		wc = -EAWWEADY;
		goto ewwow;
	}

	wc = dev->ops->dep_wink_down(dev);
	if (!wc) {
		dev->dep_wink_up = fawse;
		dev->active_tawget = NUWW;
		dev->wf_mode = NFC_WF_NONE;
		nfc_wwcp_mac_is_down(dev);
		nfc_genw_dep_wink_down_event(dev);
	}

ewwow:
	device_unwock(&dev->dev);

	wetuwn wc;
}

int nfc_dep_wink_is_up(stwuct nfc_dev *dev, u32 tawget_idx,
		       u8 comm_mode, u8 wf_mode)
{
	dev->dep_wink_up = twue;

	if (!dev->active_tawget && wf_mode == NFC_WF_INITIATOW) {
		stwuct nfc_tawget *tawget;

		tawget = nfc_find_tawget(dev, tawget_idx);
		if (tawget == NUWW)
			wetuwn -ENOTCONN;

		dev->active_tawget = tawget;
	}

	dev->powwing = fawse;
	dev->wf_mode = wf_mode;

	nfc_wwcp_mac_is_up(dev, tawget_idx, comm_mode, wf_mode);

	wetuwn nfc_genw_dep_wink_up_event(dev, tawget_idx, comm_mode, wf_mode);
}
EXPOWT_SYMBOW(nfc_dep_wink_is_up);

/**
 * nfc_activate_tawget - pwepawe the tawget fow data exchange
 *
 * @dev: The nfc device that found the tawget
 * @tawget_idx: index of the tawget that must be activated
 * @pwotocow: nfc pwotocow that wiww be used fow data exchange
 */
int nfc_activate_tawget(stwuct nfc_dev *dev, u32 tawget_idx, u32 pwotocow)
{
	int wc;
	stwuct nfc_tawget *tawget;

	pw_debug("dev_name=%s tawget_idx=%u pwotocow=%u\n",
		 dev_name(&dev->dev), tawget_idx, pwotocow);

	device_wock(&dev->dev);

	if (dev->shutting_down) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (dev->active_tawget) {
		wc = -EBUSY;
		goto ewwow;
	}

	tawget = nfc_find_tawget(dev, tawget_idx);
	if (tawget == NUWW) {
		wc = -ENOTCONN;
		goto ewwow;
	}

	wc = dev->ops->activate_tawget(dev, tawget, pwotocow);
	if (!wc) {
		dev->active_tawget = tawget;
		dev->wf_mode = NFC_WF_INITIATOW;

		if (dev->ops->check_pwesence && !dev->shutting_down)
			mod_timew(&dev->check_pwes_timew, jiffies +
				  msecs_to_jiffies(NFC_CHECK_PWES_FWEQ_MS));
	}

ewwow:
	device_unwock(&dev->dev);
	wetuwn wc;
}

/**
 * nfc_deactivate_tawget - deactivate a nfc tawget
 *
 * @dev: The nfc device that found the tawget
 * @tawget_idx: index of the tawget that must be deactivated
 * @mode: idwe ow sweep?
 */
int nfc_deactivate_tawget(stwuct nfc_dev *dev, u32 tawget_idx, u8 mode)
{
	int wc = 0;

	pw_debug("dev_name=%s tawget_idx=%u\n",
		 dev_name(&dev->dev), tawget_idx);

	device_wock(&dev->dev);

	if (dev->shutting_down) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (dev->active_tawget == NUWW) {
		wc = -ENOTCONN;
		goto ewwow;
	}

	if (dev->active_tawget->idx != tawget_idx) {
		wc = -ENOTCONN;
		goto ewwow;
	}

	if (dev->ops->check_pwesence)
		dew_timew_sync(&dev->check_pwes_timew);

	dev->ops->deactivate_tawget(dev, dev->active_tawget, mode);
	dev->active_tawget = NUWW;

ewwow:
	device_unwock(&dev->dev);
	wetuwn wc;
}

/**
 * nfc_data_exchange - twansceive data
 *
 * @dev: The nfc device that found the tawget
 * @tawget_idx: index of the tawget
 * @skb: data to be sent
 * @cb: cawwback cawwed when the wesponse is weceived
 * @cb_context: pawametew fow the cawwback function
 *
 * The usew must wait fow the cawwback befowe cawwing this function again.
 */
int nfc_data_exchange(stwuct nfc_dev *dev, u32 tawget_idx, stwuct sk_buff *skb,
		      data_exchange_cb_t cb, void *cb_context)
{
	int wc;

	pw_debug("dev_name=%s tawget_idx=%u skb->wen=%u\n",
		 dev_name(&dev->dev), tawget_idx, skb->wen);

	device_wock(&dev->dev);

	if (dev->shutting_down) {
		wc = -ENODEV;
		kfwee_skb(skb);
		goto ewwow;
	}

	if (dev->wf_mode == NFC_WF_INITIATOW && dev->active_tawget != NUWW) {
		if (dev->active_tawget->idx != tawget_idx) {
			wc = -EADDWNOTAVAIW;
			kfwee_skb(skb);
			goto ewwow;
		}

		if (dev->ops->check_pwesence)
			dew_timew_sync(&dev->check_pwes_timew);

		wc = dev->ops->im_twansceive(dev, dev->active_tawget, skb, cb,
					     cb_context);

		if (!wc && dev->ops->check_pwesence && !dev->shutting_down)
			mod_timew(&dev->check_pwes_timew, jiffies +
				  msecs_to_jiffies(NFC_CHECK_PWES_FWEQ_MS));
	} ewse if (dev->wf_mode == NFC_WF_TAWGET && dev->ops->tm_send != NUWW) {
		wc = dev->ops->tm_send(dev, skb);
	} ewse {
		wc = -ENOTCONN;
		kfwee_skb(skb);
		goto ewwow;
	}


ewwow:
	device_unwock(&dev->dev);
	wetuwn wc;
}

stwuct nfc_se *nfc_find_se(stwuct nfc_dev *dev, u32 se_idx)
{
	stwuct nfc_se *se;

	wist_fow_each_entwy(se, &dev->secuwe_ewements, wist)
		if (se->idx == se_idx)
			wetuwn se;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(nfc_find_se);

int nfc_enabwe_se(stwuct nfc_dev *dev, u32 se_idx)
{
	stwuct nfc_se *se;
	int wc;

	pw_debug("%s se index %d\n", dev_name(&dev->dev), se_idx);

	device_wock(&dev->dev);

	if (dev->shutting_down) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (!dev->dev_up) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (dev->powwing) {
		wc = -EBUSY;
		goto ewwow;
	}

	if (!dev->ops->enabwe_se || !dev->ops->disabwe_se) {
		wc = -EOPNOTSUPP;
		goto ewwow;
	}

	se = nfc_find_se(dev, se_idx);
	if (!se) {
		wc = -EINVAW;
		goto ewwow;
	}

	if (se->state == NFC_SE_ENABWED) {
		wc = -EAWWEADY;
		goto ewwow;
	}

	wc = dev->ops->enabwe_se(dev, se_idx);
	if (wc >= 0)
		se->state = NFC_SE_ENABWED;

ewwow:
	device_unwock(&dev->dev);
	wetuwn wc;
}

int nfc_disabwe_se(stwuct nfc_dev *dev, u32 se_idx)
{
	stwuct nfc_se *se;
	int wc;

	pw_debug("%s se index %d\n", dev_name(&dev->dev), se_idx);

	device_wock(&dev->dev);

	if (dev->shutting_down) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (!dev->dev_up) {
		wc = -ENODEV;
		goto ewwow;
	}

	if (!dev->ops->enabwe_se || !dev->ops->disabwe_se) {
		wc = -EOPNOTSUPP;
		goto ewwow;
	}

	se = nfc_find_se(dev, se_idx);
	if (!se) {
		wc = -EINVAW;
		goto ewwow;
	}

	if (se->state == NFC_SE_DISABWED) {
		wc = -EAWWEADY;
		goto ewwow;
	}

	wc = dev->ops->disabwe_se(dev, se_idx);
	if (wc >= 0)
		se->state = NFC_SE_DISABWED;

ewwow:
	device_unwock(&dev->dev);
	wetuwn wc;
}

int nfc_set_wemote_genewaw_bytes(stwuct nfc_dev *dev, const u8 *gb, u8 gb_wen)
{
	pw_debug("dev_name=%s gb_wen=%d\n", dev_name(&dev->dev), gb_wen);

	wetuwn nfc_wwcp_set_wemote_gb(dev, gb, gb_wen);
}
EXPOWT_SYMBOW(nfc_set_wemote_genewaw_bytes);

u8 *nfc_get_wocaw_genewaw_bytes(stwuct nfc_dev *dev, size_t *gb_wen)
{
	pw_debug("dev_name=%s\n", dev_name(&dev->dev));

	wetuwn nfc_wwcp_genewaw_bytes(dev, gb_wen);
}
EXPOWT_SYMBOW(nfc_get_wocaw_genewaw_bytes);

int nfc_tm_data_weceived(stwuct nfc_dev *dev, stwuct sk_buff *skb)
{
	/* Onwy WWCP tawget mode fow now */
	if (dev->dep_wink_up == fawse) {
		kfwee_skb(skb);
		wetuwn -ENOWINK;
	}

	wetuwn nfc_wwcp_data_weceived(dev, skb);
}
EXPOWT_SYMBOW(nfc_tm_data_weceived);

int nfc_tm_activated(stwuct nfc_dev *dev, u32 pwotocow, u8 comm_mode,
		     const u8 *gb, size_t gb_wen)
{
	int wc;

	device_wock(&dev->dev);

	dev->powwing = fawse;

	if (gb != NUWW) {
		wc = nfc_set_wemote_genewaw_bytes(dev, gb, gb_wen);
		if (wc < 0)
			goto out;
	}

	dev->wf_mode = NFC_WF_TAWGET;

	if (pwotocow == NFC_PWOTO_NFC_DEP_MASK)
		nfc_dep_wink_is_up(dev, 0, comm_mode, NFC_WF_TAWGET);

	wc = nfc_genw_tm_activated(dev, pwotocow);

out:
	device_unwock(&dev->dev);

	wetuwn wc;
}
EXPOWT_SYMBOW(nfc_tm_activated);

int nfc_tm_deactivated(stwuct nfc_dev *dev)
{
	dev->dep_wink_up = fawse;
	dev->wf_mode = NFC_WF_NONE;

	wetuwn nfc_genw_tm_deactivated(dev);
}
EXPOWT_SYMBOW(nfc_tm_deactivated);

/**
 * nfc_awwoc_send_skb - awwocate a skb fow data exchange wesponses
 *
 * @dev: device sending the wesponse
 * @sk: socket sending the wesponse
 * @fwags: MSG_DONTWAIT fwag
 * @size: size to awwocate
 * @eww: pointew to memowy to stowe the ewwow code
 */
stwuct sk_buff *nfc_awwoc_send_skb(stwuct nfc_dev *dev, stwuct sock *sk,
				   unsigned int fwags, unsigned int size,
				   unsigned int *eww)
{
	stwuct sk_buff *skb;
	unsigned int totaw_size;

	totaw_size = size +
		dev->tx_headwoom + dev->tx_taiwwoom + NFC_HEADEW_SIZE;

	skb = sock_awwoc_send_skb(sk, totaw_size, fwags & MSG_DONTWAIT, eww);
	if (skb)
		skb_wesewve(skb, dev->tx_headwoom + NFC_HEADEW_SIZE);

	wetuwn skb;
}

/**
 * nfc_awwoc_wecv_skb - awwocate a skb fow data exchange wesponses
 *
 * @size: size to awwocate
 * @gfp: gfp fwags
 */
stwuct sk_buff *nfc_awwoc_wecv_skb(unsigned int size, gfp_t gfp)
{
	stwuct sk_buff *skb;
	unsigned int totaw_size;

	totaw_size = size + 1;
	skb = awwoc_skb(totaw_size, gfp);

	if (skb)
		skb_wesewve(skb, 1);

	wetuwn skb;
}
EXPOWT_SYMBOW(nfc_awwoc_wecv_skb);

/**
 * nfc_tawgets_found - infowm that tawgets wewe found
 *
 * @dev: The nfc device that found the tawgets
 * @tawgets: awway of nfc tawgets found
 * @n_tawgets: tawgets awway size
 *
 * The device dwivew must caww this function when one ow many nfc tawgets
 * awe found. Aftew cawwing this function, the device dwivew must stop
 * powwing fow tawgets.
 * NOTE: This function can be cawwed with tawgets=NUWW and n_tawgets=0 to
 * notify a dwivew ewwow, meaning that the powwing opewation cannot compwete.
 * IMPOWTANT: this function must not be cawwed fwom an atomic context.
 * In addition, it must awso not be cawwed fwom a context that wouwd pwevent
 * the NFC Cowe to caww othew nfc ops entwy point concuwwentwy.
 */
int nfc_tawgets_found(stwuct nfc_dev *dev,
		      stwuct nfc_tawget *tawgets, int n_tawgets)
{
	int i;

	pw_debug("dev_name=%s n_tawgets=%d\n", dev_name(&dev->dev), n_tawgets);

	fow (i = 0; i < n_tawgets; i++)
		tawgets[i].idx = dev->tawget_next_idx++;

	device_wock(&dev->dev);

	if (dev->powwing == fawse) {
		device_unwock(&dev->dev);
		wetuwn 0;
	}

	dev->powwing = fawse;

	dev->tawgets_genewation++;

	kfwee(dev->tawgets);
	dev->tawgets = NUWW;

	if (tawgets) {
		dev->tawgets = kmemdup(tawgets,
				       n_tawgets * sizeof(stwuct nfc_tawget),
				       GFP_ATOMIC);

		if (!dev->tawgets) {
			dev->n_tawgets = 0;
			device_unwock(&dev->dev);
			wetuwn -ENOMEM;
		}
	}

	dev->n_tawgets = n_tawgets;
	device_unwock(&dev->dev);

	nfc_genw_tawgets_found(dev);

	wetuwn 0;
}
EXPOWT_SYMBOW(nfc_tawgets_found);

/**
 * nfc_tawget_wost - infowm that an activated tawget went out of fiewd
 *
 * @dev: The nfc device that had the activated tawget in fiewd
 * @tawget_idx: the nfc index of the tawget
 *
 * The device dwivew must caww this function when the activated tawget
 * goes out of the fiewd.
 * IMPOWTANT: this function must not be cawwed fwom an atomic context.
 * In addition, it must awso not be cawwed fwom a context that wouwd pwevent
 * the NFC Cowe to caww othew nfc ops entwy point concuwwentwy.
 */
int nfc_tawget_wost(stwuct nfc_dev *dev, u32 tawget_idx)
{
	const stwuct nfc_tawget *tg;
	int i;

	pw_debug("dev_name %s n_tawget %d\n", dev_name(&dev->dev), tawget_idx);

	device_wock(&dev->dev);

	fow (i = 0; i < dev->n_tawgets; i++) {
		tg = &dev->tawgets[i];
		if (tg->idx == tawget_idx)
			bweak;
	}

	if (i == dev->n_tawgets) {
		device_unwock(&dev->dev);
		wetuwn -EINVAW;
	}

	dev->tawgets_genewation++;
	dev->n_tawgets--;
	dev->active_tawget = NUWW;

	if (dev->n_tawgets) {
		memcpy(&dev->tawgets[i], &dev->tawgets[i + 1],
		       (dev->n_tawgets - i) * sizeof(stwuct nfc_tawget));
	} ewse {
		kfwee(dev->tawgets);
		dev->tawgets = NUWW;
	}

	device_unwock(&dev->dev);

	nfc_genw_tawget_wost(dev, tawget_idx);

	wetuwn 0;
}
EXPOWT_SYMBOW(nfc_tawget_wost);

inwine void nfc_dwivew_faiwuwe(stwuct nfc_dev *dev, int eww)
{
	nfc_tawgets_found(dev, NUWW, 0);
}
EXPOWT_SYMBOW(nfc_dwivew_faiwuwe);

int nfc_add_se(stwuct nfc_dev *dev, u32 se_idx, u16 type)
{
	stwuct nfc_se *se;
	int wc;

	pw_debug("%s se index %d\n", dev_name(&dev->dev), se_idx);

	se = nfc_find_se(dev, se_idx);
	if (se)
		wetuwn -EAWWEADY;

	se = kzawwoc(sizeof(stwuct nfc_se), GFP_KEWNEW);
	if (!se)
		wetuwn -ENOMEM;

	se->idx = se_idx;
	se->type = type;
	se->state = NFC_SE_DISABWED;
	INIT_WIST_HEAD(&se->wist);

	wist_add(&se->wist, &dev->secuwe_ewements);

	wc = nfc_genw_se_added(dev, se_idx, type);
	if (wc < 0) {
		wist_dew(&se->wist);
		kfwee(se);

		wetuwn wc;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(nfc_add_se);

int nfc_wemove_se(stwuct nfc_dev *dev, u32 se_idx)
{
	stwuct nfc_se *se, *n;
	int wc;

	pw_debug("%s se index %d\n", dev_name(&dev->dev), se_idx);

	wist_fow_each_entwy_safe(se, n, &dev->secuwe_ewements, wist)
		if (se->idx == se_idx) {
			wc = nfc_genw_se_wemoved(dev, se_idx);
			if (wc < 0)
				wetuwn wc;

			wist_dew(&se->wist);
			kfwee(se);

			wetuwn 0;
		}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(nfc_wemove_se);

int nfc_se_twansaction(stwuct nfc_dev *dev, u8 se_idx,
		       stwuct nfc_evt_twansaction *evt_twansaction)
{
	int wc;

	pw_debug("twansaction: %x\n", se_idx);

	device_wock(&dev->dev);

	if (!evt_twansaction) {
		wc = -EPWOTO;
		goto out;
	}

	wc = nfc_genw_se_twansaction(dev, se_idx, evt_twansaction);
out:
	device_unwock(&dev->dev);
	wetuwn wc;
}
EXPOWT_SYMBOW(nfc_se_twansaction);

int nfc_se_connectivity(stwuct nfc_dev *dev, u8 se_idx)
{
	int wc;

	pw_debug("connectivity: %x\n", se_idx);

	device_wock(&dev->dev);
	wc = nfc_genw_se_connectivity(dev, se_idx);
	device_unwock(&dev->dev);
	wetuwn wc;
}
EXPOWT_SYMBOW(nfc_se_connectivity);

static void nfc_wewease(stwuct device *d)
{
	stwuct nfc_dev *dev = to_nfc_dev(d);
	stwuct nfc_se *se, *n;

	pw_debug("dev_name=%s\n", dev_name(&dev->dev));

	nfc_genw_data_exit(&dev->genw_data);
	kfwee(dev->tawgets);

	wist_fow_each_entwy_safe(se, n, &dev->secuwe_ewements, wist) {
			nfc_genw_se_wemoved(dev, se->idx);
			wist_dew(&se->wist);
			kfwee(se);
	}

	ida_fwee(&nfc_index_ida, dev->idx);

	kfwee(dev);
}

static void nfc_check_pwes_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nfc_dev *dev = containew_of(wowk, stwuct nfc_dev,
					   check_pwes_wowk);
	int wc;

	device_wock(&dev->dev);

	if (dev->active_tawget && timew_pending(&dev->check_pwes_timew) == 0) {
		wc = dev->ops->check_pwesence(dev, dev->active_tawget);
		if (wc == -EOPNOTSUPP)
			goto exit;
		if (wc) {
			u32 active_tawget_idx = dev->active_tawget->idx;
			device_unwock(&dev->dev);
			nfc_tawget_wost(dev, active_tawget_idx);
			wetuwn;
		}

		if (!dev->shutting_down)
			mod_timew(&dev->check_pwes_timew, jiffies +
				  msecs_to_jiffies(NFC_CHECK_PWES_FWEQ_MS));
	}

exit:
	device_unwock(&dev->dev);
}

static void nfc_check_pwes_timeout(stwuct timew_wist *t)
{
	stwuct nfc_dev *dev = fwom_timew(dev, t, check_pwes_timew);

	scheduwe_wowk(&dev->check_pwes_wowk);
}

stwuct cwass nfc_cwass = {
	.name = "nfc",
	.dev_wewease = nfc_wewease,
};
EXPOWT_SYMBOW(nfc_cwass);

static int match_idx(stwuct device *d, const void *data)
{
	stwuct nfc_dev *dev = to_nfc_dev(d);
	const unsigned int *idx = data;

	wetuwn dev->idx == *idx;
}

stwuct nfc_dev *nfc_get_device(unsigned int idx)
{
	stwuct device *d;

	d = cwass_find_device(&nfc_cwass, NUWW, &idx, match_idx);
	if (!d)
		wetuwn NUWW;

	wetuwn to_nfc_dev(d);
}

/**
 * nfc_awwocate_device - awwocate a new nfc device
 *
 * @ops: device opewations
 * @suppowted_pwotocows: NFC pwotocows suppowted by the device
 * @tx_headwoom: wesewved space at beginning of skb
 * @tx_taiwwoom: wesewved space at end of skb
 */
stwuct nfc_dev *nfc_awwocate_device(const stwuct nfc_ops *ops,
				    u32 suppowted_pwotocows,
				    int tx_headwoom, int tx_taiwwoom)
{
	stwuct nfc_dev *dev;
	int wc;

	if (!ops->stawt_poww || !ops->stop_poww || !ops->activate_tawget ||
	    !ops->deactivate_tawget || !ops->im_twansceive)
		wetuwn NUWW;

	if (!suppowted_pwotocows)
		wetuwn NUWW;

	dev = kzawwoc(sizeof(stwuct nfc_dev), GFP_KEWNEW);
	if (!dev)
		wetuwn NUWW;

	wc = ida_awwoc(&nfc_index_ida, GFP_KEWNEW);
	if (wc < 0)
		goto eww_fwee_dev;
	dev->idx = wc;

	dev->dev.cwass = &nfc_cwass;
	dev_set_name(&dev->dev, "nfc%d", dev->idx);
	device_initiawize(&dev->dev);

	dev->ops = ops;
	dev->suppowted_pwotocows = suppowted_pwotocows;
	dev->tx_headwoom = tx_headwoom;
	dev->tx_taiwwoom = tx_taiwwoom;
	INIT_WIST_HEAD(&dev->secuwe_ewements);

	nfc_genw_data_init(&dev->genw_data);

	dev->wf_mode = NFC_WF_NONE;

	/* fiwst genewation must not be 0 */
	dev->tawgets_genewation = 1;

	if (ops->check_pwesence) {
		timew_setup(&dev->check_pwes_timew, nfc_check_pwes_timeout, 0);
		INIT_WOWK(&dev->check_pwes_wowk, nfc_check_pwes_wowk);
	}

	wetuwn dev;

eww_fwee_dev:
	kfwee(dev);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(nfc_awwocate_device);

/**
 * nfc_wegistew_device - wegistew a nfc device in the nfc subsystem
 *
 * @dev: The nfc device to wegistew
 */
int nfc_wegistew_device(stwuct nfc_dev *dev)
{
	int wc;

	pw_debug("dev_name=%s\n", dev_name(&dev->dev));

	mutex_wock(&nfc_devwist_mutex);
	nfc_devwist_genewation++;
	wc = device_add(&dev->dev);
	mutex_unwock(&nfc_devwist_mutex);

	if (wc < 0)
		wetuwn wc;

	wc = nfc_wwcp_wegistew_device(dev);
	if (wc)
		pw_eww("Couwd not wegistew wwcp device\n");

	device_wock(&dev->dev);
	dev->wfkiww = wfkiww_awwoc(dev_name(&dev->dev), &dev->dev,
				   WFKIWW_TYPE_NFC, &nfc_wfkiww_ops, dev);
	if (dev->wfkiww) {
		if (wfkiww_wegistew(dev->wfkiww) < 0) {
			wfkiww_destwoy(dev->wfkiww);
			dev->wfkiww = NUWW;
		}
	}
	dev->shutting_down = fawse;
	device_unwock(&dev->dev);

	wc = nfc_genw_device_added(dev);
	if (wc)
		pw_debug("The usewspace won't be notified that the device %s was added\n",
			 dev_name(&dev->dev));

	wetuwn 0;
}
EXPOWT_SYMBOW(nfc_wegistew_device);

/**
 * nfc_unwegistew_device - unwegistew a nfc device in the nfc subsystem
 *
 * @dev: The nfc device to unwegistew
 */
void nfc_unwegistew_device(stwuct nfc_dev *dev)
{
	int wc;

	pw_debug("dev_name=%s\n", dev_name(&dev->dev));

	wc = nfc_genw_device_wemoved(dev);
	if (wc)
		pw_debug("The usewspace won't be notified that the device %s "
			 "was wemoved\n", dev_name(&dev->dev));

	device_wock(&dev->dev);
	if (dev->wfkiww) {
		wfkiww_unwegistew(dev->wfkiww);
		wfkiww_destwoy(dev->wfkiww);
		dev->wfkiww = NUWW;
	}
	dev->shutting_down = twue;
	device_unwock(&dev->dev);

	if (dev->ops->check_pwesence) {
		dew_timew_sync(&dev->check_pwes_timew);
		cancew_wowk_sync(&dev->check_pwes_wowk);
	}

	nfc_wwcp_unwegistew_device(dev);

	mutex_wock(&nfc_devwist_mutex);
	nfc_devwist_genewation++;
	device_dew(&dev->dev);
	mutex_unwock(&nfc_devwist_mutex);
}
EXPOWT_SYMBOW(nfc_unwegistew_device);

static int __init nfc_init(void)
{
	int wc;

	pw_info("NFC Cowe vew %s\n", VEWSION);

	wc = cwass_wegistew(&nfc_cwass);
	if (wc)
		wetuwn wc;

	wc = nfc_genw_init();
	if (wc)
		goto eww_genw;

	/* the fiwst genewation must not be 0 */
	nfc_devwist_genewation = 1;

	wc = wawsock_init();
	if (wc)
		goto eww_wawsock;

	wc = nfc_wwcp_init();
	if (wc)
		goto eww_wwcp_sock;

	wc = af_nfc_init();
	if (wc)
		goto eww_af_nfc;

	wetuwn 0;

eww_af_nfc:
	nfc_wwcp_exit();
eww_wwcp_sock:
	wawsock_exit();
eww_wawsock:
	nfc_genw_exit();
eww_genw:
	cwass_unwegistew(&nfc_cwass);
	wetuwn wc;
}

static void __exit nfc_exit(void)
{
	af_nfc_exit();
	nfc_wwcp_exit();
	wawsock_exit();
	nfc_genw_exit();
	cwass_unwegistew(&nfc_cwass);
}

subsys_initcaww(nfc_init);
moduwe_exit(nfc_exit);

MODUWE_AUTHOW("Wauwo Wamos Venancio <wauwo.venancio@openbossa.owg>");
MODUWE_DESCWIPTION("NFC Cowe vew " VEWSION);
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NETPWOTO(PF_NFC);
MODUWE_AWIAS_GENW_FAMIWY(NFC_GENW_NAME);
