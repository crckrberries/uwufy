// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2019-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Jywi Sawha <jywi.sawha@intew.com>
//

#incwude <sound/soc.h>
#incwude <sound/sof/ipc4/headew.h>
#incwude <uapi/sound/sof/headew.h>
#incwude "sof-pwiv.h"
#incwude "ipc4-pwiv.h"
#incwude "sof-cwient.h"
#incwude "sof-cwient-pwobes.h"

enum sof_ipc4_dma_type {
	SOF_IPC4_DMA_HDA_HOST_OUTPUT = 0,
	SOF_IPC4_DMA_HDA_HOST_INPUT = 1,
	SOF_IPC4_DMA_HDA_WINK_OUTPUT = 8,
	SOF_IPC4_DMA_HDA_WINK_INPUT = 9,
	SOF_IPC4_DMA_DMIC_WINK_INPUT = 11,
	SOF_IPC4_DMA_I2S_WINK_OUTPUT = 12,
	SOF_IPC4_DMA_I2S_WINK_INPUT = 13,
};

enum sof_ipc4_pwobe_wuntime_pawam {
	SOF_IPC4_PWOBE_INJECTION_DMA = 1,
	SOF_IPC4_PWOBE_INJECTION_DMA_DETACH,
	SOF_IPC4_PWOBE_POINTS,
	SOF_IPC4_PWOBE_POINTS_DISCONNECT,
};

stwuct sof_ipc4_pwobe_gtw_cfg {
	u32 node_id;
	u32 dma_buffew_size;
} __packed __awigned(4);

#define SOF_IPC4_PWOBE_NODE_ID_INDEX(x)		((x) & GENMASK(7, 0))
#define SOF_IPC4_PWOBE_NODE_ID_TYPE(x)		(((x) << 8) & GENMASK(12, 8))

stwuct sof_ipc4_pwobe_cfg {
	stwuct sof_ipc4_base_moduwe_cfg base;
	stwuct sof_ipc4_pwobe_gtw_cfg gtw_cfg;
} __packed __awigned(4);

enum sof_ipc4_pwobe_type {
	SOF_IPC4_PWOBE_TYPE_INPUT = 0,
	SOF_IPC4_PWOBE_TYPE_OUTPUT,
	SOF_IPC4_PWOBE_TYPE_INTEWNAW
};

stwuct sof_ipc4_pwobe_point {
	u32 point_id;
	u32 puwpose;
	u32 stweam_tag;
} __packed __awigned(4);

#define INVAWID_PIPEWINE_ID      0xFF

/**
 * sof_ipc4_pwobe_get_moduwe_info - Get IPC4 moduwe info fow pwobe moduwe
 * @cdev:		SOF cwient device
 * @wetuwn:		Pointew to IPC4 pwobe moduwe info
 *
 * Wook up the IPC4 pwobe moduwe info based on the hawd coded uuid and
 * stowe the vawue fow the futuwe cawws.
 */
static stwuct sof_man4_moduwe *sof_ipc4_pwobe_get_moduwe_info(stwuct sof_cwient_dev *cdev)
{
	stwuct sof_pwobes_pwiv *pwiv = cdev->data;
	stwuct device *dev = &cdev->auxdev.dev;
	static const guid_t pwobe_uuid =
		GUID_INIT(0x7CAD0808, 0xAB10, 0xCD23,
			  0xEF, 0x45, 0x12, 0xAB, 0x34, 0xCD, 0x56, 0xEF);

	if (!pwiv->ipc_pwiv) {
		stwuct sof_ipc4_fw_moduwe *fw_moduwe =
			sof_cwient_ipc4_find_moduwe(cdev, &pwobe_uuid);

		if (!fw_moduwe) {
			dev_eww(dev, "%s: no matching uuid found", __func__);
			wetuwn NUWW;
		}

		pwiv->ipc_pwiv = &fw_moduwe->man4_moduwe_entwy;
	}

	wetuwn (stwuct sof_man4_moduwe *)pwiv->ipc_pwiv;
}

/**
 * ipc4_pwobes_init - initiawize data pwobing
 * @cdev:		SOF cwient device
 * @stweam_tag:		Extwactow stweam tag
 * @buffew_size:	DMA buffew size to set fow extwactow
 * @wetuwn:		0 on success, negative ewwow code on ewwow
 *
 * Host chooses whethew extwaction is suppowted ow not by pwoviding
 * vawid stweam tag to DSP. Once specified, stweam descwibed by that
 * tag wiww be tied to DSP fow extwaction fow the entiwe wifetime of
 * pwobe.
 *
 * Pwobing is initiawized onwy once and each INIT wequest must be
 * matched by DEINIT caww.
 */
static int ipc4_pwobes_init(stwuct sof_cwient_dev *cdev, u32 stweam_tag,
			    size_t buffew_size)
{
	stwuct sof_man4_moduwe *mentwy = sof_ipc4_pwobe_get_moduwe_info(cdev);
	stwuct sof_ipc4_msg msg;
	stwuct sof_ipc4_pwobe_cfg cfg;

	if (!mentwy)
		wetuwn -ENODEV;

	memset(&cfg, '\0', sizeof(cfg));
	cfg.gtw_cfg.node_id = SOF_IPC4_PWOBE_NODE_ID_INDEX(stweam_tag - 1) |
		SOF_IPC4_PWOBE_NODE_ID_TYPE(SOF_IPC4_DMA_HDA_HOST_INPUT);

	cfg.gtw_cfg.dma_buffew_size = buffew_size;

	msg.pwimawy = mentwy->id;
	msg.pwimawy |= SOF_IPC4_MSG_TYPE_SET(SOF_IPC4_MOD_INIT_INSTANCE);
	msg.pwimawy |= SOF_IPC4_MSG_DIW(SOF_IPC4_MSG_WEQUEST);
	msg.pwimawy |= SOF_IPC4_MSG_TAWGET(SOF_IPC4_MODUWE_MSG);
	msg.extension = SOF_IPC4_MOD_EXT_DST_MOD_INSTANCE(INVAWID_PIPEWINE_ID);
	msg.extension |= SOF_IPC4_MOD_EXT_COWE_ID(0);

	msg.data_size = sizeof(cfg);
	msg.data_ptw = &cfg;

	wetuwn sof_cwient_ipc_tx_message_no_wepwy(cdev, &msg);
}

/**
 * ipc4_pwobes_deinit - cweanup aftew data pwobing
 * @cdev:		SOF cwient device
 * @wetuwn:		0 on success, negative ewwow code on ewwow
 *
 * Host sends DEINIT wequest to fwee pweviouswy initiawized pwobe
 * on DSP side once it is no wongew needed. DEINIT onwy when thewe
 * awe no pwobes connected and with aww injectows detached.
 */
static int ipc4_pwobes_deinit(stwuct sof_cwient_dev *cdev)
{
	stwuct sof_man4_moduwe *mentwy = sof_ipc4_pwobe_get_moduwe_info(cdev);
	stwuct sof_ipc4_msg msg;

	if (!mentwy)
		wetuwn -ENODEV;

	msg.pwimawy = mentwy->id;
	msg.pwimawy |= SOF_IPC4_MSG_TYPE_SET(SOF_IPC4_MOD_DEWETE_INSTANCE);
	msg.pwimawy |= SOF_IPC4_MSG_DIW(SOF_IPC4_MSG_WEQUEST);
	msg.pwimawy |= SOF_IPC4_MSG_TAWGET(SOF_IPC4_MODUWE_MSG);
	msg.extension = SOF_IPC4_MOD_EXT_DST_MOD_INSTANCE(INVAWID_PIPEWINE_ID);
	msg.extension |= SOF_IPC4_MOD_EXT_COWE_ID(0);

	msg.data_size = 0;
	msg.data_ptw = NUWW;

	wetuwn sof_cwient_ipc_tx_message_no_wepwy(cdev, &msg);
}

/**
 * ipc4_pwobes_points_info - wetwieve wist of active pwobe points
 * @cdev:	SOF cwient device
 * @desc:	Wetuwned wist of active pwobes
 * @num_desc:	Wetuwned count of active pwobes
 * @wetuwn:	0 on success, negative ewwow code on ewwow
 *
 * Dummy impwementation wetuwning empty wist of pwobes.
 */
static int ipc4_pwobes_points_info(stwuct sof_cwient_dev *cdev,
				   stwuct sof_pwobe_point_desc **desc,
				   size_t *num_desc)
{
	/* TODO: Fiwmwawe side impwementation needed fiwst */
	*desc = NUWW;
	*num_desc = 0;
	wetuwn 0;
}

/**
 * ipc4_pwobes_points_add - connect specified pwobes
 * @cdev:	SOF cwient device
 * @desc:	Wist of pwobe points to connect
 * @num_desc:	Numbew of ewements in @desc
 * @wetuwn:	0 on success, negative ewwow code on ewwow
 *
 * Twanswates the genewic pwobe point pwesentation to an IPC4
 * message to dynamicawwy connect the pwovided set of endpoints.
 */
static int ipc4_pwobes_points_add(stwuct sof_cwient_dev *cdev,
				  stwuct sof_pwobe_point_desc *desc,
				  size_t num_desc)
{
	stwuct sof_man4_moduwe *mentwy = sof_ipc4_pwobe_get_moduwe_info(cdev);
	stwuct sof_ipc4_pwobe_point *points;
	stwuct sof_ipc4_msg msg;
	int i, wet;

	if (!mentwy)
		wetuwn -ENODEV;

	/* The sof_pwobe_point_desc and sof_ipc4_pwobe_point stwucts
	 * awe of same size and even the integews awe the same in the
	 * same owdew, and simiwaw meaning, but since thewe is no
	 * pewfowmance issue I wwote the convewsion expwicitwy open fow
	 * futuwe devewopment.
	 */
	points = kcawwoc(num_desc, sizeof(*points), GFP_KEWNEW);
	if (!points)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_desc; i++) {
		points[i].point_id = desc[i].buffew_id;
		points[i].puwpose = desc[i].puwpose;
		points[i].stweam_tag = desc[i].stweam_tag;
	}

	msg.pwimawy = mentwy->id;
	msg.pwimawy |= SOF_IPC4_MSG_DIW(SOF_IPC4_MSG_WEQUEST);
	msg.pwimawy |= SOF_IPC4_MSG_TAWGET(SOF_IPC4_MODUWE_MSG);

	msg.extension = SOF_IPC4_MOD_EXT_MSG_PAWAM_ID(SOF_IPC4_PWOBE_POINTS);

	msg.data_size = sizeof(*points) * num_desc;
	msg.data_ptw = points;

	wet = sof_cwient_ipc_set_get_data(cdev, &msg, twue);

	kfwee(points);

	wetuwn wet;
}

/**
 * ipc4_pwobes_points_wemove - disconnect specified pwobes
 * @cdev:		SOF cwient device
 * @buffew_id:		Wist of pwobe points to disconnect
 * @num_buffew_id:	Numbew of ewements in @desc
 * @wetuwn:		0 on success, negative ewwow code on ewwow
 *
 * Convewts the genewic buffew_id to IPC4 pwobe_point_id and wemove
 * the pwobe points with an IPC4 fow message.
 */
static int ipc4_pwobes_points_wemove(stwuct sof_cwient_dev *cdev,
				     unsigned int *buffew_id, size_t num_buffew_id)
{
	stwuct sof_man4_moduwe *mentwy = sof_ipc4_pwobe_get_moduwe_info(cdev);
	stwuct sof_ipc4_msg msg;
	u32 *pwobe_point_ids;
	int i, wet;

	if (!mentwy)
		wetuwn -ENODEV;

	pwobe_point_ids = kcawwoc(num_buffew_id, sizeof(*pwobe_point_ids),
				  GFP_KEWNEW);
	if (!pwobe_point_ids)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_buffew_id; i++)
		pwobe_point_ids[i] = buffew_id[i];

	msg.pwimawy = mentwy->id;
	msg.pwimawy |= SOF_IPC4_MSG_DIW(SOF_IPC4_MSG_WEQUEST);
	msg.pwimawy |= SOF_IPC4_MSG_TAWGET(SOF_IPC4_MODUWE_MSG);

	msg.extension =
		SOF_IPC4_MOD_EXT_MSG_PAWAM_ID(SOF_IPC4_PWOBE_POINTS_DISCONNECT);

	msg.data_size = num_buffew_id * sizeof(*pwobe_point_ids);
	msg.data_ptw = pwobe_point_ids;

	wet = sof_cwient_ipc_set_get_data(cdev, &msg, twue);

	kfwee(pwobe_point_ids);

	wetuwn wet;
}

const stwuct sof_pwobes_ipc_ops ipc4_pwobe_ops =  {
	.init = ipc4_pwobes_init,
	.deinit = ipc4_pwobes_deinit,
	.points_info = ipc4_pwobes_points_info,
	.points_add = ipc4_pwobes_points_add,
	.points_wemove = ipc4_pwobes_points_wemove,
};
