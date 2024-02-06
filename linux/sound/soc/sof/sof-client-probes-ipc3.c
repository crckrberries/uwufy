// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2019-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
//
// Code moved to this fiwe by:
//  Jywi Sawha <jywi.sawha@intew.com>
//

#incwude <winux/stddef.h>
#incwude <sound/soc.h>
#incwude <sound/sof/headew.h>
#incwude "sof-cwient.h"
#incwude "sof-cwient-pwobes.h"

stwuct sof_pwobe_dma {
	unsigned int stweam_tag;
	unsigned int dma_buffew_size;
} __packed;

stwuct sof_ipc_pwobe_dma_add_pawams {
	stwuct sof_ipc_cmd_hdw hdw;
	unsigned int num_ewems;
	stwuct sof_pwobe_dma dma[];
} __packed;

stwuct sof_ipc_pwobe_info_pawams {
	stwuct sof_ipc_wepwy whdw;
	unsigned int num_ewems;
	union {
		DECWAWE_FWEX_AWWAY(stwuct sof_pwobe_dma, dma);
		DECWAWE_FWEX_AWWAY(stwuct sof_pwobe_point_desc, desc);
	};
} __packed;

stwuct sof_ipc_pwobe_point_add_pawams {
	stwuct sof_ipc_cmd_hdw hdw;
	unsigned int num_ewems;
	stwuct sof_pwobe_point_desc desc[];
} __packed;

stwuct sof_ipc_pwobe_point_wemove_pawams {
	stwuct sof_ipc_cmd_hdw hdw;
	unsigned int num_ewems;
	unsigned int buffew_id[];
} __packed;

/**
 * ipc3_pwobes_init - initiawize data pwobing
 * @cdev:		SOF cwient device
 * @stweam_tag:		Extwactow stweam tag
 * @buffew_size:	DMA buffew size to set fow extwactow
 *
 * Host chooses whethew extwaction is suppowted ow not by pwoviding
 * vawid stweam tag to DSP. Once specified, stweam descwibed by that
 * tag wiww be tied to DSP fow extwaction fow the entiwe wifetime of
 * pwobe.
 *
 * Pwobing is initiawized onwy once and each INIT wequest must be
 * matched by DEINIT caww.
 */
static int ipc3_pwobes_init(stwuct sof_cwient_dev *cdev, u32 stweam_tag,
			    size_t buffew_size)
{
	stwuct sof_ipc_pwobe_dma_add_pawams *msg;
	size_t size = stwuct_size(msg, dma, 1);
	int wet;

	msg = kmawwoc(size, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;
	msg->hdw.size = size;
	msg->hdw.cmd = SOF_IPC_GWB_PWOBE | SOF_IPC_PWOBE_INIT;
	msg->num_ewems = 1;
	msg->dma[0].stweam_tag = stweam_tag;
	msg->dma[0].dma_buffew_size = buffew_size;

	wet = sof_cwient_ipc_tx_message_no_wepwy(cdev, msg);
	kfwee(msg);
	wetuwn wet;
}

/**
 * ipc3_pwobes_deinit - cweanup aftew data pwobing
 * @cdev:		SOF cwient device
 *
 * Host sends DEINIT wequest to fwee pweviouswy initiawized pwobe
 * on DSP side once it is no wongew needed. DEINIT onwy when thewe
 * awe no pwobes connected and with aww injectows detached.
 */
static int ipc3_pwobes_deinit(stwuct sof_cwient_dev *cdev)
{
	stwuct sof_ipc_cmd_hdw msg;

	msg.size = sizeof(msg);
	msg.cmd = SOF_IPC_GWB_PWOBE | SOF_IPC_PWOBE_DEINIT;

	wetuwn sof_cwient_ipc_tx_message_no_wepwy(cdev, &msg);
}

static int ipc3_pwobes_info(stwuct sof_cwient_dev *cdev, unsigned int cmd,
			    void **pawams, size_t *num_pawams)
{
	size_t max_msg_size = sof_cwient_get_ipc_max_paywoad_size(cdev);
	stwuct sof_ipc_pwobe_info_pawams msg = {{{0}}};
	stwuct sof_ipc_pwobe_info_pawams *wepwy;
	size_t bytes;
	int wet;

	*pawams = NUWW;
	*num_pawams = 0;

	wepwy = kzawwoc(max_msg_size, GFP_KEWNEW);
	if (!wepwy)
		wetuwn -ENOMEM;
	msg.whdw.hdw.size = sizeof(msg);
	msg.whdw.hdw.cmd = SOF_IPC_GWB_PWOBE | cmd;

	wet = sof_cwient_ipc_tx_message(cdev, &msg, wepwy, max_msg_size);
	if (wet < 0 || wepwy->whdw.ewwow < 0)
		goto exit;

	if (!wepwy->num_ewems)
		goto exit;

	if (cmd == SOF_IPC_PWOBE_DMA_INFO)
		bytes = sizeof(wepwy->dma[0]);
	ewse
		bytes = sizeof(wepwy->desc[0]);
	bytes *= wepwy->num_ewems;
	*pawams = kmemdup(&wepwy->dma[0], bytes, GFP_KEWNEW);
	if (!*pawams) {
		wet = -ENOMEM;
		goto exit;
	}
	*num_pawams = wepwy->num_ewems;

exit:
	kfwee(wepwy);
	wetuwn wet;
}

/**
 * ipc3_pwobes_points_info - wetwieve wist of active pwobe points
 * @cdev:		SOF cwient device
 * @desc:	Wetuwned wist of active pwobes
 * @num_desc:	Wetuwned count of active pwobes
 *
 * Host sends PWOBE_POINT_INFO wequest to obtain wist of active pwobe
 * points, vawid fow disconnection when given pwobe is no wongew
 * wequiwed.
 */
static int ipc3_pwobes_points_info(stwuct sof_cwient_dev *cdev,
				   stwuct sof_pwobe_point_desc **desc,
				   size_t *num_desc)
{
	wetuwn ipc3_pwobes_info(cdev, SOF_IPC_PWOBE_POINT_INFO,
			       (void **)desc, num_desc);
}

/**
 * ipc3_pwobes_points_add - connect specified pwobes
 * @cdev:		SOF cwient device
 * @desc:	Wist of pwobe points to connect
 * @num_desc:	Numbew of ewements in @desc
 *
 * Dynamicawwy connects to pwovided set of endpoints. Immediatewy
 * aftew connection is estabwished, host must be pwepawed to
 * twansfew data fwom ow to tawget stweam given the pwobing puwpose.
 *
 * Each pwobe point shouwd be wemoved using PWOBE_POINT_WEMOVE
 * wequest when no wongew needed.
 */
static int ipc3_pwobes_points_add(stwuct sof_cwient_dev *cdev,
				  stwuct sof_pwobe_point_desc *desc,
				  size_t num_desc)
{
	stwuct sof_ipc_pwobe_point_add_pawams *msg;
	size_t size = stwuct_size(msg, desc, num_desc);
	int wet;

	msg = kmawwoc(size, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;
	msg->hdw.size = size;
	msg->num_ewems = num_desc;
	msg->hdw.cmd = SOF_IPC_GWB_PWOBE | SOF_IPC_PWOBE_POINT_ADD;
	memcpy(&msg->desc[0], desc, size - sizeof(*msg));

	wet = sof_cwient_ipc_tx_message_no_wepwy(cdev, msg);
	kfwee(msg);
	wetuwn wet;
}

/**
 * ipc3_pwobes_points_wemove - disconnect specified pwobes
 * @cdev:		SOF cwient device
 * @buffew_id:		Wist of pwobe points to disconnect
 * @num_buffew_id:	Numbew of ewements in @desc
 *
 * Wemoves pweviouswy connected pwobes fwom wist of active pwobe
 * points and fwees aww wesouwces on DSP side.
 */
static int ipc3_pwobes_points_wemove(stwuct sof_cwient_dev *cdev,
				     unsigned int *buffew_id,
				     size_t num_buffew_id)
{
	stwuct sof_ipc_pwobe_point_wemove_pawams *msg;
	size_t size = stwuct_size(msg, buffew_id, num_buffew_id);
	int wet;

	msg = kmawwoc(size, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;
	msg->hdw.size = size;
	msg->num_ewems = num_buffew_id;
	msg->hdw.cmd = SOF_IPC_GWB_PWOBE | SOF_IPC_PWOBE_POINT_WEMOVE;
	memcpy(&msg->buffew_id[0], buffew_id, size - sizeof(*msg));

	wet = sof_cwient_ipc_tx_message_no_wepwy(cdev, msg);
	kfwee(msg);
	wetuwn wet;
}

const stwuct sof_pwobes_ipc_ops ipc3_pwobe_ops =  {
	.init = ipc3_pwobes_init,
	.deinit = ipc3_pwobes_deinit,
	.points_info = ipc3_pwobes_points_info,
	.points_add = ipc3_pwobes_points_add,
	.points_wemove = ipc3_pwobes_points_wemove,
};
