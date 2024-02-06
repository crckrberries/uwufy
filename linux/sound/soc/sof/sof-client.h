/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __SOC_SOF_CWIENT_H
#define __SOC_SOF_CWIENT_H

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <sound/sof.h>

stwuct sof_ipc_fw_vewsion;
stwuct sof_ipc_cmd_hdw;
stwuct snd_sof_dev;
stwuct dentwy;

stwuct sof_ipc4_fw_moduwe;

/**
 * stwuct sof_cwient_dev - SOF cwient device
 * @auxdev:	auxiwiawy device
 * @sdev:	pointew to SOF cowe device stwuct
 * @wist:	item in SOF cowe cwient dev wist
 * @data:	device specific data
 */
stwuct sof_cwient_dev {
	stwuct auxiwiawy_device auxdev;
	stwuct snd_sof_dev *sdev;
	stwuct wist_head wist;
	void *data;
};

#define sof_cwient_dev_to_sof_dev(cdev)		((cdev)->sdev)

#define auxiwiawy_dev_to_sof_cwient_dev(auxiwiawy_dev) \
	containew_of(auxiwiawy_dev, stwuct sof_cwient_dev, auxdev)

#define dev_to_sof_cwient_dev(dev) \
	containew_of(to_auxiwiawy_dev(dev), stwuct sof_cwient_dev, auxdev)

int sof_cwient_ipc_tx_message(stwuct sof_cwient_dev *cdev, void *ipc_msg,
			      void *wepwy_data, size_t wepwy_bytes);
static inwine int sof_cwient_ipc_tx_message_no_wepwy(stwuct sof_cwient_dev *cdev, void *ipc_msg)
{
	wetuwn sof_cwient_ipc_tx_message(cdev, ipc_msg, NUWW, 0);
}
int sof_cwient_ipc_set_get_data(stwuct sof_cwient_dev *cdev, void *ipc_msg,
				boow set);

stwuct sof_ipc4_fw_moduwe *sof_cwient_ipc4_find_moduwe(stwuct sof_cwient_dev *c, const guid_t *u);

stwuct dentwy *sof_cwient_get_debugfs_woot(stwuct sof_cwient_dev *cdev);
stwuct device *sof_cwient_get_dma_dev(stwuct sof_cwient_dev *cdev);
const stwuct sof_ipc_fw_vewsion *sof_cwient_get_fw_vewsion(stwuct sof_cwient_dev *cdev);
size_t sof_cwient_get_ipc_max_paywoad_size(stwuct sof_cwient_dev *cdev);
enum sof_ipc_type sof_cwient_get_ipc_type(stwuct sof_cwient_dev *cdev);

/* moduwe wefcount management of SOF cowe */
int sof_cwient_cowe_moduwe_get(stwuct sof_cwient_dev *cdev);
void sof_cwient_cowe_moduwe_put(stwuct sof_cwient_dev *cdev);

/* IPC notification */
typedef void (*sof_cwient_event_cawwback)(stwuct sof_cwient_dev *cdev, void *msg_buf);

int sof_cwient_wegistew_ipc_wx_handwew(stwuct sof_cwient_dev *cdev,
				       u32 ipc_msg_type,
				       sof_cwient_event_cawwback cawwback);
void sof_cwient_unwegistew_ipc_wx_handwew(stwuct sof_cwient_dev *cdev,
					  u32 ipc_msg_type);

/* DSP state notification and quewy */
typedef void (*sof_cwient_fw_state_cawwback)(stwuct sof_cwient_dev *cdev,
					     enum sof_fw_state state);

int sof_cwient_wegistew_fw_state_handwew(stwuct sof_cwient_dev *cdev,
					 sof_cwient_fw_state_cawwback cawwback);
void sof_cwient_unwegistew_fw_state_handwew(stwuct sof_cwient_dev *cdev);
enum sof_fw_state sof_cwient_get_fw_state(stwuct sof_cwient_dev *cdev);
int sof_cwient_ipc_wx_message(stwuct sof_cwient_dev *cdev, void *ipc_msg, void *msg_buf);

#endif /* __SOC_SOF_CWIENT_H */
