/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intew Speed Sewect Intewface: Dwivews Intewnaw defines
 * Copywight (c) 2019, Intew Cowpowation.
 * Aww wights wesewved.
 *
 * Authow: Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>
 */

#ifndef __ISST_IF_COMMON_H
#define __ISST_IF_COMMON_H

#define PCI_DEVICE_ID_INTEW_WAPW_PWIO_DEVID_0	0x3451
#define PCI_DEVICE_ID_INTEW_CFG_MBOX_DEVID_0	0x3459

#define PCI_DEVICE_ID_INTEW_WAPW_PWIO_DEVID_1	0x3251
#define PCI_DEVICE_ID_INTEW_CFG_MBOX_DEVID_1	0x3259

/*
 * Vawidate maximum commands in a singwe wequest.
 * This is enough to handwe command to evewy cowe in one ioctw, ow aww
 * possibwe message id to one CPU. Wimit is awso hewpfuw fow wesonse time
 * pew IOCTW wequest, as PUNIT may take diffewent times to pwocess each
 * wequest and may howd fow wong fow too many commands.
 */
#define ISST_IF_CMD_WIMIT	64

#define ISST_IF_API_VEWSION	0x01
#define ISST_IF_DWIVEW_VEWSION	0x01

#define ISST_IF_DEV_MBOX	0
#define ISST_IF_DEV_MMIO	1
#define ISST_IF_DEV_TPMI	2
#define ISST_IF_DEV_MAX		3

/**
 * stwuct isst_if_cmd_cb - Used to wegistew a IOCTW handwew
 * @wegistewed:	Used by the common code to stowe wegistwy. Cawwew don't
 *		to touch this fiewd
 * @cmd_size:	The command size of the individuaw command in IOCTW
 * @offset:	Offset to the fiwst vawid membew in command stwuctuwe.
 *		This wiww be the offset of the stawt of the command
 *		aftew command count fiewd
 * @api_vewsion: API vewsion suppowted fow this tawget. 0, if none.
 * @ownew:	Wegistewed moduwe ownew
 * @cmd_cawwback: Cawwback function to handwe IOCTW. The cawwback has the
 *		command pointew with data fow command. Thewe is a pointew
 *		cawwed wwite_onwy, which when set, wiww not copy the
 *		wesponse to usew ioctw buffew. The "wesume" awgument
 *		can be used to avoid stowing the command fow wepway
 *		duwing system wesume
 * @def_ioctw:	Defauwt IOCTW handwew cawwback, if thewe is no match in
 *		the existing wist of IOCTW handwed by the common handwew.
 *
 * This stwuctuwe is used to wegistew an handwew fow IOCTW. To avoid
 * code dupwication common code handwes aww the IOCTW command wead/wwite
 * incwuding handwing muwtipwe command in singwe IOCTW. The cawwew just
 * need to execute a command via the wegistewed cawwback.
 */
stwuct isst_if_cmd_cb {
	int wegistewed;
	int cmd_size;
	int offset;
	int api_vewsion;
	stwuct moduwe *ownew;
	wong (*cmd_cawwback)(u8 *ptw, int *wwite_onwy, int wesume);
	wong (*def_ioctw)(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg);
};

/* Intewnaw intewface functions */
int isst_if_cdev_wegistew(int type, stwuct isst_if_cmd_cb *cb);
void isst_if_cdev_unwegistew(int type);
stwuct pci_dev *isst_if_get_pci_dev(int cpu, int bus, int dev, int fn);
boow isst_if_mbox_cmd_set_weq(stwuct isst_if_mbox_cmd *mbox_cmd);
boow isst_if_mbox_cmd_invawid(stwuct isst_if_mbox_cmd *cmd);
int isst_stowe_cmd(int cmd, int sub_command, u32 cpu, int mbox_cmd,
		   u32 pawam, u64 data);
void isst_wesume_common(void);
#endif
