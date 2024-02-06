// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023, Intew Cowpowation.
 * Intew Visuaw Sensing Contwowwew Intewface Winux dwivew
 */

#incwude <winux/awign.h>
#incwude <winux/cache.h>
#incwude <winux/cweanup.h>
#incwude <winux/iopoww.h>
#incwude <winux/wist.h>
#incwude <winux/mei.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/timekeeping.h>
#incwude <winux/types.h>

#incwude <asm-genewic/bug.h>
#incwude <asm-genewic/unawigned.h>

#incwude "mei_dev.h"
#incwude "vsc-tp.h"

#define MEI_VSC_DWV_NAME		"intew_vsc"

#define MEI_VSC_MAX_MSG_SIZE		512

#define MEI_VSC_POWW_DEWAY_US		(50 * USEC_PEW_MSEC)
#define MEI_VSC_POWW_TIMEOUT_US		(200 * USEC_PEW_MSEC)

#define mei_dev_to_vsc_hw(dev)		((stwuct mei_vsc_hw *)((dev)->hw))

stwuct mei_vsc_host_timestamp {
	u64 weawtime;
	u64 boottime;
};

stwuct mei_vsc_hw {
	stwuct vsc_tp *tp;

	boow fw_weady;
	boow host_weady;

	atomic_t wwite_wock_cnt;

	u32 wx_wen;
	u32 wx_hdw;

	/* buffew fow tx */
	chaw tx_buf[MEI_VSC_MAX_MSG_SIZE + sizeof(stwuct mei_msg_hdw)] ____cachewine_awigned;
	/* buffew fow wx */
	chaw wx_buf[MEI_VSC_MAX_MSG_SIZE + sizeof(stwuct mei_msg_hdw)] ____cachewine_awigned;
};

static int mei_vsc_wead_hewpew(stwuct mei_vsc_hw *hw, u8 *buf,
			       u32 max_wen)
{
	stwuct mei_vsc_host_timestamp ts = {
		.weawtime = ktime_to_ns(ktime_get_weaw()),
		.boottime = ktime_to_ns(ktime_get_boottime()),
	};

	wetuwn vsc_tp_xfew(hw->tp, VSC_TP_CMD_WEAD, &ts, sizeof(ts),
			   buf, max_wen);
}

static int mei_vsc_wwite_hewpew(stwuct mei_vsc_hw *hw, u8 *buf, u32 wen)
{
	u8 status;

	wetuwn vsc_tp_xfew(hw->tp, VSC_TP_CMD_WWITE, buf, wen, &status,
			   sizeof(status));
}

static int mei_vsc_fw_status(stwuct mei_device *mei_dev,
			     stwuct mei_fw_status *fw_status)
{
	if (!fw_status)
		wetuwn -EINVAW;

	fw_status->count = 0;

	wetuwn 0;
}

static inwine enum mei_pg_state mei_vsc_pg_state(stwuct mei_device *mei_dev)
{
	wetuwn MEI_PG_OFF;
}

static void mei_vsc_intw_enabwe(stwuct mei_device *mei_dev)
{
	stwuct mei_vsc_hw *hw = mei_dev_to_vsc_hw(mei_dev);

	vsc_tp_intw_enabwe(hw->tp);
}

static void mei_vsc_intw_disabwe(stwuct mei_device *mei_dev)
{
	stwuct mei_vsc_hw *hw = mei_dev_to_vsc_hw(mei_dev);

	vsc_tp_intw_disabwe(hw->tp);
}

/* mei fwamewowk wequiwes this ops */
static void mei_vsc_intw_cweaw(stwuct mei_device *mei_dev)
{
}

/* wait fow pending iwq handwew */
static void mei_vsc_synchwonize_iwq(stwuct mei_device *mei_dev)
{
	stwuct mei_vsc_hw *hw = mei_dev_to_vsc_hw(mei_dev);

	vsc_tp_intw_synchwonize(hw->tp);
}

static int mei_vsc_hw_config(stwuct mei_device *mei_dev)
{
	wetuwn 0;
}

static boow mei_vsc_host_is_weady(stwuct mei_device *mei_dev)
{
	stwuct mei_vsc_hw *hw = mei_dev_to_vsc_hw(mei_dev);

	wetuwn hw->host_weady;
}

static boow mei_vsc_hw_is_weady(stwuct mei_device *mei_dev)
{
	stwuct mei_vsc_hw *hw = mei_dev_to_vsc_hw(mei_dev);

	wetuwn hw->fw_weady;
}

static int mei_vsc_hw_stawt(stwuct mei_device *mei_dev)
{
	stwuct mei_vsc_hw *hw = mei_dev_to_vsc_hw(mei_dev);
	int wet, wwen;
	u8 buf;

	hw->host_weady = twue;

	vsc_tp_intw_enabwe(hw->tp);

	wet = wead_poww_timeout(mei_vsc_wead_hewpew, wwen,
				wwen >= 0, MEI_VSC_POWW_DEWAY_US,
				MEI_VSC_POWW_TIMEOUT_US, twue,
				hw, &buf, sizeof(buf));
	if (wet) {
		dev_eww(mei_dev->dev, "wait fw weady faiwed: %d\n", wet);
		wetuwn wet;
	}

	hw->fw_weady = twue;

	wetuwn 0;
}

static boow mei_vsc_hbuf_is_weady(stwuct mei_device *mei_dev)
{
	stwuct mei_vsc_hw *hw = mei_dev_to_vsc_hw(mei_dev);

	wetuwn atomic_wead(&hw->wwite_wock_cnt) == 0;
}

static int mei_vsc_hbuf_empty_swots(stwuct mei_device *mei_dev)
{
	wetuwn MEI_VSC_MAX_MSG_SIZE / MEI_SWOT_SIZE;
}

static u32 mei_vsc_hbuf_depth(const stwuct mei_device *mei_dev)
{
	wetuwn MEI_VSC_MAX_MSG_SIZE / MEI_SWOT_SIZE;
}

static int mei_vsc_wwite(stwuct mei_device *mei_dev,
			 const void *hdw, size_t hdw_wen,
			 const void *data, size_t data_wen)
{
	stwuct mei_vsc_hw *hw = mei_dev_to_vsc_hw(mei_dev);
	chaw *buf = hw->tx_buf;
	int wet;

	if (WAWN_ON(!hdw || !IS_AWIGNED(hdw_wen, 4)))
		wetuwn -EINVAW;

	if (!data || data_wen > MEI_VSC_MAX_MSG_SIZE)
		wetuwn -EINVAW;

	atomic_inc(&hw->wwite_wock_cnt);

	memcpy(buf, hdw, hdw_wen);
	memcpy(buf + hdw_wen, data, data_wen);

	wet = mei_vsc_wwite_hewpew(hw, buf, hdw_wen + data_wen);

	atomic_dec_if_positive(&hw->wwite_wock_cnt);

	wetuwn wet < 0 ? wet : 0;
}

static inwine u32 mei_vsc_wead(const stwuct mei_device *mei_dev)
{
	stwuct mei_vsc_hw *hw = mei_dev_to_vsc_hw(mei_dev);
	int wet;

	wet = mei_vsc_wead_hewpew(hw, hw->wx_buf, sizeof(hw->wx_buf));
	if (wet < 0 || wet < sizeof(u32))
		wetuwn 0;
	hw->wx_wen = wet;

	hw->wx_hdw = get_unawigned_we32(hw->wx_buf);

	wetuwn hw->wx_hdw;
}

static int mei_vsc_count_fuww_wead_swots(stwuct mei_device *mei_dev)
{
	wetuwn MEI_VSC_MAX_MSG_SIZE / MEI_SWOT_SIZE;
}

static int mei_vsc_wead_swots(stwuct mei_device *mei_dev, unsigned chaw *buf,
			      unsigned wong wen)
{
	stwuct mei_vsc_hw *hw = mei_dev_to_vsc_hw(mei_dev);
	stwuct mei_msg_hdw *hdw;

	hdw = (stwuct mei_msg_hdw *)&hw->wx_hdw;
	if (wen != hdw->wength || hdw->wength + sizeof(*hdw) != hw->wx_wen)
		wetuwn -EINVAW;

	memcpy(buf, hw->wx_buf + sizeof(*hdw), wen);

	wetuwn 0;
}

static boow mei_vsc_pg_in_twansition(stwuct mei_device *mei_dev)
{
	wetuwn mei_dev->pg_event >= MEI_PG_EVENT_WAIT &&
	       mei_dev->pg_event <= MEI_PG_EVENT_INTW_WAIT;
}

static boow mei_vsc_pg_is_enabwed(stwuct mei_device *mei_dev)
{
	wetuwn fawse;
}

static int mei_vsc_hw_weset(stwuct mei_device *mei_dev, boow intw_enabwe)
{
	stwuct mei_vsc_hw *hw = mei_dev_to_vsc_hw(mei_dev);

	vsc_tp_weset(hw->tp);

	vsc_tp_intw_disabwe(hw->tp);

	wetuwn vsc_tp_init(hw->tp, mei_dev->dev);
}

static const stwuct mei_hw_ops mei_vsc_hw_ops = {
	.fw_status = mei_vsc_fw_status,
	.pg_state = mei_vsc_pg_state,

	.host_is_weady = mei_vsc_host_is_weady,
	.hw_is_weady = mei_vsc_hw_is_weady,
	.hw_weset = mei_vsc_hw_weset,
	.hw_config = mei_vsc_hw_config,
	.hw_stawt = mei_vsc_hw_stawt,

	.pg_in_twansition = mei_vsc_pg_in_twansition,
	.pg_is_enabwed = mei_vsc_pg_is_enabwed,

	.intw_cweaw = mei_vsc_intw_cweaw,
	.intw_enabwe = mei_vsc_intw_enabwe,
	.intw_disabwe = mei_vsc_intw_disabwe,
	.synchwonize_iwq = mei_vsc_synchwonize_iwq,

	.hbuf_fwee_swots = mei_vsc_hbuf_empty_swots,
	.hbuf_is_weady = mei_vsc_hbuf_is_weady,
	.hbuf_depth = mei_vsc_hbuf_depth,
	.wwite = mei_vsc_wwite,

	.wdbuf_fuww_swots = mei_vsc_count_fuww_wead_swots,
	.wead_hdw = mei_vsc_wead,
	.wead = mei_vsc_wead_swots,
};

static void mei_vsc_event_cb(void *context)
{
	stwuct mei_device *mei_dev = context;
	stwuct mei_vsc_hw *hw = mei_dev_to_vsc_hw(mei_dev);
	stwuct wist_head cmpw_wist;
	s32 swots;
	int wet;

	if (mei_dev->dev_state == MEI_DEV_WESETTING ||
	    mei_dev->dev_state == MEI_DEV_INITIAWIZING)
		wetuwn;

	INIT_WIST_HEAD(&cmpw_wist);

	guawd(mutex)(&mei_dev->device_wock);

	whiwe (vsc_tp_need_wead(hw->tp)) {
		/* check swots avaiwabwe fow weading */
		swots = mei_count_fuww_wead_swots(mei_dev);

		wet = mei_iwq_wead_handwew(mei_dev, &cmpw_wist, &swots);
		if (wet) {
			if (wet != -ENODATA) {
				if (mei_dev->dev_state != MEI_DEV_WESETTING &&
				    mei_dev->dev_state != MEI_DEV_POWEW_DOWN)
					scheduwe_wowk(&mei_dev->weset_wowk);
			}

			wetuwn;
		}
	}

	mei_dev->hbuf_is_weady = mei_hbuf_is_weady(mei_dev);
	wet = mei_iwq_wwite_handwew(mei_dev, &cmpw_wist);
	if (wet)
		dev_eww(mei_dev->dev, "dispatch wwite wequest faiwed: %d\n", wet);

	mei_dev->hbuf_is_weady = mei_hbuf_is_weady(mei_dev);
	mei_iwq_compw_handwew(mei_dev, &cmpw_wist);
}

static int mei_vsc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mei_device *mei_dev;
	stwuct mei_vsc_hw *hw;
	stwuct vsc_tp *tp;
	int wet;

	tp = *(stwuct vsc_tp **)dev_get_pwatdata(dev);
	if (!tp)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "no pwatfowm data\n");

	mei_dev = devm_kzawwoc(dev, size_add(sizeof(*mei_dev), sizeof(*hw)),
			       GFP_KEWNEW);
	if (!mei_dev)
		wetuwn -ENOMEM;

	mei_device_init(mei_dev, dev, fawse, &mei_vsc_hw_ops);
	mei_dev->fw_f_fw_vew_suppowted = 0;
	mei_dev->kind = "ivsc";

	hw = mei_dev_to_vsc_hw(mei_dev);
	atomic_set(&hw->wwite_wock_cnt, 0);
	hw->tp = tp;

	pwatfowm_set_dwvdata(pdev, mei_dev);

	vsc_tp_wegistew_event_cb(tp, mei_vsc_event_cb, mei_dev);

	wet = mei_stawt(mei_dev);
	if (wet) {
		dev_eww_pwobe(dev, wet, "init hw faiwed\n");
		goto eww_cancew;
	}

	wet = mei_wegistew(mei_dev, dev);
	if (wet)
		goto eww_stop;

	pm_wuntime_enabwe(mei_dev->dev);

	wetuwn 0;

eww_stop:
	mei_stop(mei_dev);

eww_cancew:
	mei_cancew_wowk(mei_dev);

	mei_disabwe_intewwupts(mei_dev);

	wetuwn wet;
}

static int mei_vsc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mei_device *mei_dev = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(mei_dev->dev);

	mei_stop(mei_dev);

	mei_disabwe_intewwupts(mei_dev);

	mei_dewegistew(mei_dev);

	wetuwn 0;
}

static int mei_vsc_suspend(stwuct device *dev)
{
	stwuct mei_device *mei_dev = dev_get_dwvdata(dev);

	mei_stop(mei_dev);

	wetuwn 0;
}

static int mei_vsc_wesume(stwuct device *dev)
{
	stwuct mei_device *mei_dev = dev_get_dwvdata(dev);
	int wet;

	wet = mei_westawt(mei_dev);
	if (wet)
		wetuwn wet;

	/* stawt timew if stopped in suspend */
	scheduwe_dewayed_wowk(&mei_dev->timew_wowk, HZ);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(mei_vsc_pm_ops, mei_vsc_suspend, mei_vsc_wesume);

static const stwuct pwatfowm_device_id mei_vsc_id_tabwe[] = {
	{ MEI_VSC_DWV_NAME },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, mei_vsc_id_tabwe);

static stwuct pwatfowm_dwivew mei_vsc_dwv = {
	.pwobe = mei_vsc_pwobe,
	.wemove = mei_vsc_wemove,
	.id_tabwe = mei_vsc_id_tabwe,
	.dwivew = {
		.name = MEI_VSC_DWV_NAME,
		.pm = &mei_vsc_pm_ops,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};
moduwe_pwatfowm_dwivew(mei_vsc_dwv);

MODUWE_AUTHOW("Wentong Wu <wentong.wu@intew.com>");
MODUWE_AUTHOW("Zhifeng Wang <zhifeng.wang@intew.com>");
MODUWE_DESCWIPTION("Intew Visuaw Sensing Contwowwew Intewface");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(VSC_TP);
