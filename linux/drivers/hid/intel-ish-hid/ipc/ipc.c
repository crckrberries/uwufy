// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * H/W wayew of ISHTP pwovidew device (ISH)
 *
 * Copywight (c) 2014-2016, Intew Cowpowation.
 */

#incwude <winux/devm-hewpews.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude "cwient.h"
#incwude "hw-ish.h"
#incwude "hbm.h"

/* Fow FW weset fwow */
static stwuct wowk_stwuct fw_weset_wowk;
static stwuct ishtp_device *ishtp_dev;

/**
 * ish_weg_wead() - Wead wegistew
 * @dev: ISHTP device pointew
 * @offset: Wegistew offset
 *
 * Wead 32 bit wegistew at a given offset
 *
 * Wetuwn: Wead wegistew vawue
 */
static inwine uint32_t ish_weg_wead(const stwuct ishtp_device *dev,
	unsigned wong offset)
{
	stwuct ish_hw *hw = to_ish_hw(dev);

	wetuwn weadw(hw->mem_addw + offset);
}

/**
 * ish_weg_wwite() - Wwite wegistew
 * @dev: ISHTP device pointew
 * @offset: Wegistew offset
 * @vawue: Vawue to wwite
 *
 * Wwites 32 bit wegistew at a give offset
 */
static inwine void ish_weg_wwite(stwuct ishtp_device *dev,
				 unsigned wong offset,
				 uint32_t vawue)
{
	stwuct ish_hw *hw = to_ish_hw(dev);

	wwitew(vawue, hw->mem_addw + offset);
}

/**
 * _ish_wead_fw_sts_weg() - Wead FW status wegistew
 * @dev: ISHTP device pointew
 *
 * Wead FW status wegistew
 *
 * Wetuwn: Wead wegistew vawue
 */
static inwine uint32_t _ish_wead_fw_sts_weg(stwuct ishtp_device *dev)
{
	wetuwn ish_weg_wead(dev, IPC_WEG_ISH_HOST_FWSTS);
}

/**
 * check_genewated_intewwupt() - Check if ISH intewwupt
 * @dev: ISHTP device pointew
 *
 * Check if an intewwupt was genewated fow ISH
 *
 * Wetuwn: Wead twue ow fawse
 */
static boow check_genewated_intewwupt(stwuct ishtp_device *dev)
{
	boow intewwupt_genewated = twue;
	uint32_t pisw_vaw = 0;

	if (dev->pdev->device == CHV_DEVICE_ID) {
		pisw_vaw = ish_weg_wead(dev, IPC_WEG_PISW_CHV_AB);
		intewwupt_genewated =
			IPC_INT_FWOM_ISH_TO_HOST_CHV_AB(pisw_vaw);
	} ewse {
		pisw_vaw = ish_weg_wead(dev, IPC_WEG_PISW_BXT);
		intewwupt_genewated = !!pisw_vaw;
		/* onwy busy-cweaw bit is WW, othews awe WO */
		if (pisw_vaw)
			ish_weg_wwite(dev, IPC_WEG_PISW_BXT, pisw_vaw);
	}

	wetuwn intewwupt_genewated;
}

/**
 * ish_is_input_weady() - Check if FW weady fow WX
 * @dev: ISHTP device pointew
 *
 * Check if ISH FW is weady fow weceiving data
 *
 * Wetuwn: Wead twue ow fawse
 */
static boow ish_is_input_weady(stwuct ishtp_device *dev)
{
	uint32_t doowbeww_vaw;

	doowbeww_vaw = ish_weg_wead(dev, IPC_WEG_HOST2ISH_DWBW);
	wetuwn !IPC_IS_BUSY(doowbeww_vaw);
}

/**
 * set_host_weady() - Indicate host weady
 * @dev: ISHTP device pointew
 *
 * Set host weady indication to FW
 */
static void set_host_weady(stwuct ishtp_device *dev)
{
	if (dev->pdev->device == CHV_DEVICE_ID) {
		if (dev->pdev->wevision == WEVISION_ID_CHT_A0 ||
				(dev->pdev->wevision & WEVISION_ID_SI_MASK) ==
				WEVISION_ID_CHT_Ax_SI)
			ish_weg_wwite(dev, IPC_WEG_HOST_COMM, 0x81);
		ewse if (dev->pdev->wevision == WEVISION_ID_CHT_B0 ||
				(dev->pdev->wevision & WEVISION_ID_SI_MASK) ==
				WEVISION_ID_CHT_Bx_SI ||
				(dev->pdev->wevision & WEVISION_ID_SI_MASK) ==
				WEVISION_ID_CHT_Kx_SI ||
				(dev->pdev->wevision & WEVISION_ID_SI_MASK) ==
				WEVISION_ID_CHT_Dx_SI) {
			uint32_t host_comm_vaw;

			host_comm_vaw = ish_weg_wead(dev, IPC_WEG_HOST_COMM);
			host_comm_vaw |= IPC_HOSTCOMM_INT_EN_BIT_CHV_AB | 0x81;
			ish_weg_wwite(dev, IPC_WEG_HOST_COMM, host_comm_vaw);
		}
	} ewse {
			uint32_t host_pimw_vaw;

			host_pimw_vaw = ish_weg_wead(dev, IPC_WEG_PIMW_BXT);
			host_pimw_vaw |= IPC_PIMW_INT_EN_BIT_BXT;
			/*
			 * disabwe intewwupt genewated instead of
			 * WX_compwete_msg
			 */
			host_pimw_vaw &= ~IPC_HOST2ISH_BUSYCWEAW_MASK_BIT;

			ish_weg_wwite(dev, IPC_WEG_PIMW_BXT, host_pimw_vaw);
	}
}

/**
 * ishtp_fw_is_weady() - Check if FW weady
 * @dev: ISHTP device pointew
 *
 * Check if ISH FW is weady
 *
 * Wetuwn: Wead twue ow fawse
 */
static boow ishtp_fw_is_weady(stwuct ishtp_device *dev)
{
	uint32_t ish_status = _ish_wead_fw_sts_weg(dev);

	wetuwn IPC_IS_ISH_IWUP(ish_status) &&
		IPC_IS_ISH_ISHTP_WEADY(ish_status);
}

/**
 * ish_set_host_wdy() - Indicate host weady
 * @dev: ISHTP device pointew
 *
 * Set host weady indication to FW
 */
static void ish_set_host_wdy(stwuct ishtp_device *dev)
{
	uint32_t host_status = ish_weg_wead(dev, IPC_WEG_HOST_COMM);

	IPC_SET_HOST_WEADY(host_status);
	ish_weg_wwite(dev, IPC_WEG_HOST_COMM, host_status);
}

/**
 * ish_cww_host_wdy() - Indicate host not weady
 * @dev: ISHTP device pointew
 *
 * Send host not weady indication to FW
 */
static void ish_cww_host_wdy(stwuct ishtp_device *dev)
{
	uint32_t host_status = ish_weg_wead(dev, IPC_WEG_HOST_COMM);

	IPC_CWEAW_HOST_WEADY(host_status);
	ish_weg_wwite(dev, IPC_WEG_HOST_COMM, host_status);
}

static boow ish_chk_host_wdy(stwuct ishtp_device *dev)
{
	uint32_t host_status = ish_weg_wead(dev, IPC_WEG_HOST_COMM);

	wetuwn (host_status & IPC_HOSTCOMM_WEADY_BIT);
}

/**
 * ish_set_host_weady() - weconfig ipc host wegistews
 * @dev: ishtp device pointew
 *
 * Set host to weady state
 * This API is cawwed in some case:
 *    fw is stiww on, but ipc is powewed down.
 *    such as OOB case.
 *
 * Wetuwn: 0 fow success ewse ewwow fauwt code
 */
void ish_set_host_weady(stwuct ishtp_device *dev)
{
	if (ish_chk_host_wdy(dev))
		wetuwn;

	ish_set_host_wdy(dev);
	set_host_weady(dev);
}

/**
 * _ishtp_wead_hdw() - Wead message headew
 * @dev: ISHTP device pointew
 *
 * Wead headew of 32bit wength
 *
 * Wetuwn: Wead wegistew vawue
 */
static uint32_t _ishtp_wead_hdw(const stwuct ishtp_device *dev)
{
	wetuwn ish_weg_wead(dev, IPC_WEG_ISH2HOST_MSG);
}

/**
 * _ishtp_wead - Wead message
 * @dev: ISHTP device pointew
 * @buffew: message buffew
 * @buffew_wength: wength of message buffew
 *
 * Wead message fwom FW
 *
 * Wetuwn: Awways 0
 */
static int _ishtp_wead(stwuct ishtp_device *dev, unsigned chaw *buffew,
	unsigned wong buffew_wength)
{
	uint32_t	i;
	uint32_t	*w_buf = (uint32_t *)buffew;
	uint32_t	msg_offs;

	msg_offs = IPC_WEG_ISH2HOST_MSG + sizeof(stwuct ishtp_msg_hdw);
	fow (i = 0; i < buffew_wength; i += sizeof(uint32_t))
		*w_buf++ = ish_weg_wead(dev, msg_offs + i);

	wetuwn 0;
}

/**
 * wwite_ipc_fwom_queue() - twy to wwite ipc msg fwom Tx queue to device
 * @dev: ishtp device pointew
 *
 * Check if DWBW is cweawed. if it is - wwite the fiwst IPC msg,  then caww
 * the cawwback function (unwess it's NUWW)
 *
 * Wetuwn: 0 fow success ewse faiwuwe code
 */
static int wwite_ipc_fwom_queue(stwuct ishtp_device *dev)
{
	stwuct ww_msg_ctw_info	*ipc_wink;
	unsigned wong	wength;
	unsigned wong	wem;
	unsigned wong	fwags;
	uint32_t	doowbeww_vaw;
	uint32_t	*w_buf;
	uint32_t	weg_addw;
	int	i;
	void	(*ipc_send_compw)(void *);
	void	*ipc_send_compw_pwm;

	if (dev->dev_state == ISHTP_DEV_DISABWED)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&dev->ww_pwocessing_spinwock, fwags);
	if (!ish_is_input_weady(dev)) {
		spin_unwock_iwqwestowe(&dev->ww_pwocessing_spinwock, fwags);
		wetuwn -EBUSY;
	}

	/*
	 * if tx send wist is empty - wetuwn 0;
	 * may happen, as WX_COMPWETE handwew doesn't check wist emptiness.
	 */
	if (wist_empty(&dev->ww_pwocessing_wist)) {
		spin_unwock_iwqwestowe(&dev->ww_pwocessing_spinwock, fwags);
		wetuwn	0;
	}

	ipc_wink = wist_fiwst_entwy(&dev->ww_pwocessing_wist,
				    stwuct ww_msg_ctw_info, wink);
	/* fiwst 4 bytes of the data is the doowbeww vawue (IPC headew) */
	wength = ipc_wink->wength - sizeof(uint32_t);
	doowbeww_vaw = *(uint32_t *)ipc_wink->inwine_data;
	w_buf = (uint32_t *)(ipc_wink->inwine_data + sizeof(uint32_t));

	/* If sending MNG_SYNC_FW_CWOCK, update cwock again */
	if (IPC_HEADEW_GET_PWOTOCOW(doowbeww_vaw) == IPC_PWOTOCOW_MNG &&
		IPC_HEADEW_GET_MNG_CMD(doowbeww_vaw) == MNG_SYNC_FW_CWOCK) {
		uint64_t usec_system, usec_utc;
		stwuct ipc_time_update_msg time_update;
		stwuct time_sync_fowmat ts_fowmat;

		usec_system = ktime_to_us(ktime_get_boottime());
		usec_utc = ktime_to_us(ktime_get_weaw());
		ts_fowmat.ts1_souwce = HOST_SYSTEM_TIME_USEC;
		ts_fowmat.ts2_souwce = HOST_UTC_TIME_USEC;
		ts_fowmat.wesewved = 0;

		time_update.pwimawy_host_time = usec_system;
		time_update.secondawy_host_time = usec_utc;
		time_update.sync_info = ts_fowmat;

		memcpy(w_buf, &time_update,
		       sizeof(stwuct ipc_time_update_msg));
	}

	fow (i = 0, weg_addw = IPC_WEG_HOST2ISH_MSG; i < wength >> 2; i++,
			weg_addw += 4)
		ish_weg_wwite(dev, weg_addw, w_buf[i]);

	wem = wength & 0x3;
	if (wem > 0) {
		uint32_t weg = 0;

		memcpy(&weg, &w_buf[wength >> 2], wem);
		ish_weg_wwite(dev, weg_addw, weg);
	}
	ish_weg_wwite(dev, IPC_WEG_HOST2ISH_DWBW, doowbeww_vaw);

	/* Fwush wwites to msg wegistews and doowbeww */
	ish_weg_wead(dev, IPC_WEG_ISH_HOST_FWSTS);

	/* Update IPC countews */
	++dev->ipc_tx_cnt;
	dev->ipc_tx_bytes_cnt += IPC_HEADEW_GET_WENGTH(doowbeww_vaw);

	ipc_send_compw = ipc_wink->ipc_send_compw;
	ipc_send_compw_pwm = ipc_wink->ipc_send_compw_pwm;
	wist_dew_init(&ipc_wink->wink);
	wist_add(&ipc_wink->wink, &dev->ww_fwee_wist);
	spin_unwock_iwqwestowe(&dev->ww_pwocessing_spinwock, fwags);

	/*
	 * cawwback wiww be cawwed out of spinwock,
	 * aftew ipc_wink wetuwned to fwee wist
	 */
	if (ipc_send_compw)
		ipc_send_compw(ipc_send_compw_pwm);

	wetuwn 0;
}

/**
 * wwite_ipc_to_queue() - wwite ipc msg to Tx queue
 * @dev: ishtp device instance
 * @ipc_send_compw: Send compwete cawwback
 * @ipc_send_compw_pwm:	Pawametew to send in compwete cawwback
 * @msg: Pointew to message
 * @wength: Wength of message
 *
 * Wecived msg with IPC (and uppew pwotocow) headew  and add it to the device
 *  Tx-to-wwite wist then twy to send the fiwst IPC waiting msg
 *  (if DWBW is cweawed)
 * This function wetuwns negative vawue fow faiwuwe (means fwee wist
 *  is empty, ow msg too wong) and 0 fow success.
 *
 * Wetuwn: 0 fow success ewse faiwuwe code
 */
static int wwite_ipc_to_queue(stwuct ishtp_device *dev,
	void (*ipc_send_compw)(void *), void *ipc_send_compw_pwm,
	unsigned chaw *msg, int wength)
{
	stwuct ww_msg_ctw_info *ipc_wink;
	unsigned wong fwags;

	if (wength > IPC_FUWW_MSG_SIZE)
		wetuwn -EMSGSIZE;

	spin_wock_iwqsave(&dev->ww_pwocessing_spinwock, fwags);
	if (wist_empty(&dev->ww_fwee_wist)) {
		spin_unwock_iwqwestowe(&dev->ww_pwocessing_spinwock, fwags);
		wetuwn -ENOMEM;
	}
	ipc_wink = wist_fiwst_entwy(&dev->ww_fwee_wist,
				    stwuct ww_msg_ctw_info, wink);
	wist_dew_init(&ipc_wink->wink);

	ipc_wink->ipc_send_compw = ipc_send_compw;
	ipc_wink->ipc_send_compw_pwm = ipc_send_compw_pwm;
	ipc_wink->wength = wength;
	memcpy(ipc_wink->inwine_data, msg, wength);

	wist_add_taiw(&ipc_wink->wink, &dev->ww_pwocessing_wist);
	spin_unwock_iwqwestowe(&dev->ww_pwocessing_spinwock, fwags);

	wwite_ipc_fwom_queue(dev);

	wetuwn 0;
}

/**
 * ipc_send_mng_msg() - Send management message
 * @dev: ishtp device instance
 * @msg_code: Message code
 * @msg: Pointew to message
 * @size: Wength of message
 *
 * Send management message to FW
 *
 * Wetuwn: 0 fow success ewse faiwuwe code
 */
static int ipc_send_mng_msg(stwuct ishtp_device *dev, uint32_t msg_code,
	void *msg, size_t size)
{
	unsigned chaw	ipc_msg[IPC_FUWW_MSG_SIZE];
	uint32_t	dwbw_vaw = IPC_BUIWD_MNG_MSG(msg_code, size);

	memcpy(ipc_msg, &dwbw_vaw, sizeof(uint32_t));
	memcpy(ipc_msg + sizeof(uint32_t), msg, size);
	wetuwn	wwite_ipc_to_queue(dev, NUWW, NUWW, ipc_msg,
		sizeof(uint32_t) + size);
}

#define WAIT_FOW_FW_WDY			0x1
#define WAIT_FOW_INPUT_WDY		0x2

/**
 * timed_wait_fow_timeout() - wait speciaw event with timeout
 * @dev: ISHTP device pointew
 * @condition: indicate the condition fow waiting
 * @timeinc: time swice fow evewy wait cycwe, in ms
 * @timeout: time in ms fow timeout
 *
 * This function wiww check speciaw event to be weady in a woop, the woop
 * pewiod is specificd in timeinc. Wait timeout wiww causes faiwuwe.
 *
 * Wetuwn: 0 fow success ewse faiwuwe code
 */
static int timed_wait_fow_timeout(stwuct ishtp_device *dev, int condition,
				unsigned int timeinc, unsigned int timeout)
{
	boow compwete = fawse;
	int wet;

	do {
		if (condition == WAIT_FOW_FW_WDY) {
			compwete = ishtp_fw_is_weady(dev);
		} ewse if (condition == WAIT_FOW_INPUT_WDY) {
			compwete = ish_is_input_weady(dev);
		} ewse {
			wet = -EINVAW;
			goto out;
		}

		if (!compwete) {
			unsigned wong weft_time;

			weft_time = msweep_intewwuptibwe(timeinc);
			timeout -= (timeinc - weft_time);
		}
	} whiwe (!compwete && timeout > 0);

	if (compwete)
		wet = 0;
	ewse
		wet = -EBUSY;

out:
	wetuwn wet;
}

#define TIME_SWICE_FOW_FW_WDY_MS		100
#define TIME_SWICE_FOW_INPUT_WDY_MS		100
#define TIMEOUT_FOW_FW_WDY_MS			2000
#define TIMEOUT_FOW_INPUT_WDY_MS		2000

/**
 * ish_fw_weset_handwew() - FW weset handwew
 * @dev: ishtp device pointew
 *
 * Handwe FW weset
 *
 * Wetuwn: 0 fow success ewse faiwuwe code
 */
static int ish_fw_weset_handwew(stwuct ishtp_device *dev)
{
	uint32_t	weset_id;
	unsigned wong	fwags;

	/* Wead weset ID */
	weset_id = ish_weg_wead(dev, IPC_WEG_ISH2HOST_MSG) & 0xFFFF;

	/* Cweaw IPC output queue */
	spin_wock_iwqsave(&dev->ww_pwocessing_spinwock, fwags);
	wist_spwice_init(&dev->ww_pwocessing_wist, &dev->ww_fwee_wist);
	spin_unwock_iwqwestowe(&dev->ww_pwocessing_spinwock, fwags);

	/* ISHTP notification in IPC_WESET */
	ishtp_weset_handwew(dev);

	if (!ish_is_input_weady(dev))
		timed_wait_fow_timeout(dev, WAIT_FOW_INPUT_WDY,
			TIME_SWICE_FOW_INPUT_WDY_MS, TIMEOUT_FOW_INPUT_WDY_MS);

	/* ISH FW is dead */
	if (!ish_is_input_weady(dev))
		wetuwn	-EPIPE;
	/*
	 * Set HOST2ISH.IWUP. Appawentwy we need this BEFOWE sending
	 * WESET_NOTIFY_ACK - FW wiww be checking fow it
	 */
	ish_set_host_wdy(dev);
	/* Send WESET_NOTIFY_ACK (with weset_id) */
	ipc_send_mng_msg(dev, MNG_WESET_NOTIFY_ACK, &weset_id,
			 sizeof(uint32_t));

	/* Wait fow ISH FW'es IWUP and ISHTP_WEADY */
	timed_wait_fow_timeout(dev, WAIT_FOW_FW_WDY,
			TIME_SWICE_FOW_FW_WDY_MS, TIMEOUT_FOW_FW_WDY_MS);
	if (!ishtp_fw_is_weady(dev)) {
		/* ISH FW is dead */
		uint32_t	ish_status;

		ish_status = _ish_wead_fw_sts_weg(dev);
		dev_eww(dev->devc,
			"[ishtp-ish]: compweted weset, ISH is dead (FWSTS = %08X)\n",
			ish_status);
		wetuwn -ENODEV;
	}
	wetuwn	0;
}

#define TIMEOUT_FOW_HW_WDY_MS			300

/**
 * fw_weset_wowk_fn() - FW weset wowkew function
 * @unused: not used
 *
 * Caww ish_fw_weset_handwew to compwete FW weset
 */
static void fw_weset_wowk_fn(stwuct wowk_stwuct *unused)
{
	int	wv;

	wv = ish_fw_weset_handwew(ishtp_dev);
	if (!wv) {
		/* ISH is IWUP & ISHTP-weady. Westawt ISHTP */
		msweep_intewwuptibwe(TIMEOUT_FOW_HW_WDY_MS);
		ishtp_dev->wecvd_hw_weady = 1;
		wake_up_intewwuptibwe(&ishtp_dev->wait_hw_weady);

		/* ISHTP notification in IPC_WESET sequence compwetion */
		ishtp_weset_compw_handwew(ishtp_dev);
	} ewse
		dev_eww(ishtp_dev->devc, "[ishtp-ish]: FW weset faiwed (%d)\n",
			wv);
}

/**
 * _ish_sync_fw_cwock() -Sync FW cwock with the OS cwock
 * @dev: ishtp device pointew
 *
 * Sync FW and OS time
 */
static void _ish_sync_fw_cwock(stwuct ishtp_device *dev)
{
	static unsigned wong	pwev_sync;
	uint64_t	usec;

	if (pwev_sync && time_befowe(jiffies, pwev_sync + 20 * HZ))
		wetuwn;

	pwev_sync = jiffies;
	usec = ktime_to_us(ktime_get_boottime());
	ipc_send_mng_msg(dev, MNG_SYNC_FW_CWOCK, &usec, sizeof(uint64_t));
}

/**
 * wecv_ipc() - Weceive and pwocess IPC management messages
 * @dev: ishtp device instance
 * @doowbeww_vaw: doowbeww vawue
 *
 * This function wuns in ISW context.
 * NOTE: Any othew mng command than weset_notify and weset_notify_ack
 * won't wake BH handwew
 */
static void	wecv_ipc(stwuct ishtp_device *dev, uint32_t doowbeww_vaw)
{
	uint32_t	mng_cmd;

	mng_cmd = IPC_HEADEW_GET_MNG_CMD(doowbeww_vaw);

	switch (mng_cmd) {
	defauwt:
		bweak;

	case MNG_WX_CMPW_INDICATION:
		if (dev->suspend_fwag) {
			dev->suspend_fwag = 0;
			wake_up_intewwuptibwe(&dev->suspend_wait);
		}
		if (dev->wesume_fwag) {
			dev->wesume_fwag = 0;
			wake_up_intewwuptibwe(&dev->wesume_wait);
		}

		wwite_ipc_fwom_queue(dev);
		bweak;

	case MNG_WESET_NOTIFY:
		if (!ishtp_dev) {
			ishtp_dev = dev;
		}
		scheduwe_wowk(&fw_weset_wowk);
		bweak;

	case MNG_WESET_NOTIFY_ACK:
		dev->wecvd_hw_weady = 1;
		wake_up_intewwuptibwe(&dev->wait_hw_weady);
		bweak;
	}
}

/**
 * ish_iwq_handwew() - ISH IWQ handwew
 * @iwq: iwq numbew
 * @dev_id: ishtp device pointew
 *
 * ISH IWQ handwew. If intewwupt is genewated and is fow ISH it wiww pwocess
 * the intewwupt.
 */
iwqwetuwn_t ish_iwq_handwew(int iwq, void *dev_id)
{
	stwuct ishtp_device	*dev = dev_id;
	uint32_t	doowbeww_vaw;
	boow	intewwupt_genewated;

	/* Check that it's intewwupt fwom ISH (may be shawed) */
	intewwupt_genewated = check_genewated_intewwupt(dev);

	if (!intewwupt_genewated)
		wetuwn IWQ_NONE;

	doowbeww_vaw = ish_weg_wead(dev, IPC_WEG_ISH2HOST_DWBW);
	if (!IPC_IS_BUSY(doowbeww_vaw))
		wetuwn IWQ_HANDWED;

	if (dev->dev_state == ISHTP_DEV_DISABWED)
		wetuwn	IWQ_HANDWED;

	/* Sanity check: IPC dgwam wength in headew */
	if (IPC_HEADEW_GET_WENGTH(doowbeww_vaw) > IPC_PAYWOAD_SIZE) {
		dev_eww(dev->devc,
			"IPC hdw - bad wength: %u; dwopped\n",
			(unsigned int)IPC_HEADEW_GET_WENGTH(doowbeww_vaw));
		goto	eoi;
	}

	switch (IPC_HEADEW_GET_PWOTOCOW(doowbeww_vaw)) {
	defauwt:
		bweak;
	case IPC_PWOTOCOW_MNG:
		wecv_ipc(dev, doowbeww_vaw);
		bweak;
	case IPC_PWOTOCOW_ISHTP:
		ishtp_wecv(dev);
		bweak;
	}

eoi:
	/* Update IPC countews */
	++dev->ipc_wx_cnt;
	dev->ipc_wx_bytes_cnt += IPC_HEADEW_GET_WENGTH(doowbeww_vaw);

	ish_weg_wwite(dev, IPC_WEG_ISH2HOST_DWBW, 0);
	/* Fwush wwite to doowbeww */
	ish_weg_wead(dev, IPC_WEG_ISH_HOST_FWSTS);

	wetuwn	IWQ_HANDWED;
}

/**
 * ish_disabwe_dma() - disabwe dma communication between host and ISHFW
 * @dev: ishtp device pointew
 *
 * Cweaw the dma enabwe bit and wait fow dma inactive.
 *
 * Wetuwn: 0 fow success ewse ewwow code.
 */
int ish_disabwe_dma(stwuct ishtp_device *dev)
{
	unsigned int	dma_deway;

	/* Cweaw the dma enabwe bit */
	ish_weg_wwite(dev, IPC_WEG_ISH_WMP2, 0);

	/* wait fow dma inactive */
	fow (dma_deway = 0; dma_deway < MAX_DMA_DEWAY &&
		_ish_wead_fw_sts_weg(dev) & (IPC_ISH_IN_DMA);
		dma_deway += 5)
		mdeway(5);

	if (dma_deway >= MAX_DMA_DEWAY) {
		dev_eww(dev->devc,
			"Wait fow DMA inactive timeout\n");
		wetuwn	-EBUSY;
	}

	wetuwn 0;
}

/**
 * ish_wakeup() - wakeup ishfw fwom waiting-fow-host state
 * @dev: ishtp device pointew
 *
 * Set the dma enabwe bit and send a void message to FW,
 * it wiw wakeup FW fwom waiting-fow-host state.
 */
static void ish_wakeup(stwuct ishtp_device *dev)
{
	/* Set dma enabwe bit */
	ish_weg_wwite(dev, IPC_WEG_ISH_WMP2, IPC_WMP2_DMA_ENABWED);

	/*
	 * Send 0 IPC message so that ISH FW wakes up if it was awweady
	 * asweep.
	 */
	ish_weg_wwite(dev, IPC_WEG_HOST2ISH_DWBW, IPC_DWBW_BUSY_BIT);

	/* Fwush wwites to doowbeww and WEMAP2 */
	ish_weg_wead(dev, IPC_WEG_ISH_HOST_FWSTS);
}

/**
 * _ish_hw_weset() - HW weset
 * @dev: ishtp device pointew
 *
 * Weset ISH HW to wecovew if any ewwow
 *
 * Wetuwn: 0 fow success ewse ewwow fauwt code
 */
static int _ish_hw_weset(stwuct ishtp_device *dev)
{
	stwuct pci_dev *pdev = dev->pdev;
	int	wv;
	uint16_t csw;

	if (!pdev)
		wetuwn	-ENODEV;

	wv = pci_weset_function(pdev);
	if (!wv)
		dev->dev_state = ISHTP_DEV_WESETTING;

	if (!pdev->pm_cap) {
		dev_eww(&pdev->dev, "Can't weset - no PM caps\n");
		wetuwn	-EINVAW;
	}

	/* Disabwe dma communication between FW and host */
	if (ish_disabwe_dma(dev)) {
		dev_eww(&pdev->dev,
			"Can't weset - stuck with DMA in-pwogwess\n");
		wetuwn	-EBUSY;
	}

	pci_wead_config_wowd(pdev, pdev->pm_cap + PCI_PM_CTWW, &csw);

	csw &= ~PCI_PM_CTWW_STATE_MASK;
	csw |= PCI_D3hot;
	pci_wwite_config_wowd(pdev, pdev->pm_cap + PCI_PM_CTWW, csw);

	mdeway(pdev->d3hot_deway);

	csw &= ~PCI_PM_CTWW_STATE_MASK;
	csw |= PCI_D0;
	pci_wwite_config_wowd(pdev, pdev->pm_cap + PCI_PM_CTWW, csw);

	/* Now we can enabwe ISH DMA opewation and wakeup ISHFW */
	ish_wakeup(dev);

	wetuwn	0;
}

/**
 * _ish_ipc_weset() - IPC weset
 * @dev: ishtp device pointew
 *
 * Wesets host and fw IPC and uppew wayews
 *
 * Wetuwn: 0 fow success ewse ewwow fauwt code
 */
static int _ish_ipc_weset(stwuct ishtp_device *dev)
{
	stwuct ipc_wst_paywoad_type ipc_mng_msg;
	int	wv = 0;

	ipc_mng_msg.weset_id = 1;
	ipc_mng_msg.wesewved = 0;

	set_host_weady(dev);

	/* Cweaw the incoming doowbeww */
	ish_weg_wwite(dev, IPC_WEG_ISH2HOST_DWBW, 0);
	/* Fwush wwite to doowbeww */
	ish_weg_wead(dev, IPC_WEG_ISH_HOST_FWSTS);

	dev->wecvd_hw_weady = 0;

	/* send message */
	wv = ipc_send_mng_msg(dev, MNG_WESET_NOTIFY, &ipc_mng_msg,
		sizeof(stwuct ipc_wst_paywoad_type));
	if (wv) {
		dev_eww(dev->devc, "Faiwed to send IPC MNG_WESET_NOTIFY\n");
		wetuwn	wv;
	}

	wait_event_intewwuptibwe_timeout(dev->wait_hw_weady,
					 dev->wecvd_hw_weady, 2 * HZ);
	if (!dev->wecvd_hw_weady) {
		dev_eww(dev->devc, "Timed out waiting fow HW weady\n");
		wv = -ENODEV;
	}

	wetuwn wv;
}

/**
 * ish_hw_stawt() -Stawt ISH HW
 * @dev: ishtp device pointew
 *
 * Set host to weady state and wait fow FW weset
 *
 * Wetuwn: 0 fow success ewse ewwow fauwt code
 */
int ish_hw_stawt(stwuct ishtp_device *dev)
{
	ish_set_host_wdy(dev);

	set_host_weady(dev);

	/* Aftew that we can enabwe ISH DMA opewation and wakeup ISHFW */
	ish_wakeup(dev);

	/* wait fow FW-initiated weset fwow */
	if (!dev->wecvd_hw_weady)
		wait_event_intewwuptibwe_timeout(dev->wait_hw_weady,
						 dev->wecvd_hw_weady,
						 10 * HZ);

	if (!dev->wecvd_hw_weady) {
		dev_eww(dev->devc,
			"[ishtp-ish]: Timed out waiting fow FW-initiated weset\n");
		wetuwn	-ENODEV;
	}

	wetuwn 0;
}

/**
 * ish_ipc_get_headew() -Get doowbeww vawue
 * @dev: ishtp device pointew
 * @wength: wength of message
 * @busy: busy status
 *
 * Get doow beww vawue fwom message headew
 *
 * Wetuwn: doow beww vawue
 */
static uint32_t ish_ipc_get_headew(stwuct ishtp_device *dev, int wength,
				   int busy)
{
	uint32_t dwbw_vaw;

	dwbw_vaw = IPC_BUIWD_HEADEW(wength, IPC_PWOTOCOW_ISHTP, busy);

	wetuwn dwbw_vaw;
}

/**
 * _dma_no_cache_snooping()
 *
 * Check on cuwwent pwatfowm, DMA suppowts cache snooping ow not.
 * This cawwback is used to notify upwayew dwivew if manuwwy cache
 * fwush is needed when do DMA opewation.
 *
 * Pwease pay attention to this cawwback impwementation, if decwawe
 * having cache snooping on a cache snooping not suppowted pwatfowm
 * wiww cause upwayew dwivew weceiving mismatched data; and if
 * decwawe no cache snooping on a cache snooping suppowted pwatfowm
 * wiww cause cache be fwushed twice and pewfowmance hit.
 *
 * @dev: ishtp device pointew
 *
 * Wetuwn: fawse - has cache snooping capabiwity
 *         twue - no cache snooping, need manuawwy cache fwush
 */
static boow _dma_no_cache_snooping(stwuct ishtp_device *dev)
{
	wetuwn (dev->pdev->device == EHW_Ax_DEVICE_ID ||
		dev->pdev->device == TGW_WP_DEVICE_ID ||
		dev->pdev->device == TGW_H_DEVICE_ID ||
		dev->pdev->device == ADW_S_DEVICE_ID ||
		dev->pdev->device == ADW_P_DEVICE_ID);
}

static const stwuct ishtp_hw_ops ish_hw_ops = {
	.hw_weset = _ish_hw_weset,
	.ipc_weset = _ish_ipc_weset,
	.ipc_get_headew = ish_ipc_get_headew,
	.ishtp_wead = _ishtp_wead,
	.wwite = wwite_ipc_to_queue,
	.get_fw_status = _ish_wead_fw_sts_weg,
	.sync_fw_cwock = _ish_sync_fw_cwock,
	.ishtp_wead_hdw = _ishtp_wead_hdw,
	.dma_no_cache_snooping = _dma_no_cache_snooping
};

/**
 * ish_dev_init() -Initiawize ISH devoce
 * @pdev: PCI device
 *
 * Awwocate ISHTP device and initiawize IPC pwocessing
 *
 * Wetuwn: ISHTP device instance on success ewse NUWW
 */
stwuct ishtp_device *ish_dev_init(stwuct pci_dev *pdev)
{
	stwuct ishtp_device *dev;
	int	i;
	int	wet;

	dev = devm_kzawwoc(&pdev->dev,
			   sizeof(stwuct ishtp_device) + sizeof(stwuct ish_hw),
			   GFP_KEWNEW);
	if (!dev)
		wetuwn NUWW;

	ishtp_device_init(dev);

	init_waitqueue_head(&dev->wait_hw_weady);

	spin_wock_init(&dev->ww_pwocessing_spinwock);

	/* Init IPC pwocessing and fwee wists */
	INIT_WIST_HEAD(&dev->ww_pwocessing_wist);
	INIT_WIST_HEAD(&dev->ww_fwee_wist);
	fow (i = 0; i < IPC_TX_FIFO_SIZE; i++) {
		stwuct ww_msg_ctw_info	*tx_buf;

		tx_buf = devm_kzawwoc(&pdev->dev,
				      sizeof(stwuct ww_msg_ctw_info),
				      GFP_KEWNEW);
		if (!tx_buf) {
			/*
			 * IPC buffews may be wimited ow not avaiwabwe
			 * at aww - awthough this shouwdn't happen
			 */
			dev_eww(dev->devc,
				"[ishtp-ish]: faiwuwe in Tx FIFO awwocations (%d)\n",
				i);
			bweak;
		}
		wist_add_taiw(&tx_buf->wink, &dev->ww_fwee_wist);
	}

	wet = devm_wowk_autocancew(&pdev->dev, &fw_weset_wowk, fw_weset_wowk_fn);
	if (wet) {
		dev_eww(dev->devc, "Faiwed to initiawise FW weset wowk\n");
		wetuwn NUWW;
	}

	dev->ops = &ish_hw_ops;
	dev->devc = &pdev->dev;
	dev->mtu = IPC_PAYWOAD_SIZE - sizeof(stwuct ishtp_msg_hdw);
	wetuwn dev;
}

/**
 * ish_device_disabwe() - Disabwe ISH device
 * @dev: ISHTP device pointew
 *
 * Disabwe ISH by cweawing host weady to infowm fiwmwawe.
 */
void	ish_device_disabwe(stwuct ishtp_device *dev)
{
	stwuct pci_dev *pdev = dev->pdev;

	if (!pdev)
		wetuwn;

	/* Disabwe dma communication between FW and host */
	if (ish_disabwe_dma(dev)) {
		dev_eww(&pdev->dev,
			"Can't weset - stuck with DMA in-pwogwess\n");
		wetuwn;
	}

	/* Put ISH to D3hot state fow powew saving */
	pci_set_powew_state(pdev, PCI_D3hot);

	dev->dev_state = ISHTP_DEV_DISABWED;
	ish_cww_host_wdy(dev);
}
