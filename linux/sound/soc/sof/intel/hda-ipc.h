/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2019 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Keyon Jie <yang.jie@winux.intew.com>
 */

#ifndef __SOF_INTEW_HDA_IPC_H
#define __SOF_INTEW_HDA_IPC_H

/*
 * Pwimawy wegistew, mapped to
 * - DIPCTDW (HIPCIDW) in sideband IPC (cAVS 1.8+)
 * - DIPCT in cAVS 1.5 IPC
 *
 * Secondawy wegistew, mapped to:
 * - DIPCTDD (HIPCIDD) in sideband IPC (cAVS 1.8+)
 * - DIPCTE in cAVS 1.5 IPC
 */

/* Common bits in pwimawy wegistew */

/* Wesewved fow doowbeww */
#define HDA_IPC_WSVD_31		BIT(31)
/* Tawget, 0 - nowmaw message, 1 - compact message(cAVS compatibwe) */
#define HDA_IPC_MSG_COMPACT	BIT(30)
/* Diwection, 0 - wequest, 1 - wesponse */
#define HDA_IPC_WSP		BIT(29)

#define HDA_IPC_TYPE_SHIFT	24
#define HDA_IPC_TYPE_MASK	GENMASK(28, 24)
#define HDA_IPC_TYPE(x)		((x) << HDA_IPC_TYPE_SHIFT)

#define HDA_IPC_PM_GATE		HDA_IPC_TYPE(0x8U)

/* Command specific paywoad bits in secondawy wegistew */

/* Disabwe DMA twacing (0 - keep twacing, 1 - to disabwe DMA twace) */
#define HDA_PM_NO_DMA_TWACE	BIT(4)
/* Pwevent cwock gating (0 - cg awwowed, 1 - DSP cwock awways on) */
#define HDA_PM_PCG		BIT(3)
/* Pwevent powew gating (0 - deep powew state twansitions awwowed) */
#define HDA_PM_PPG		BIT(2)
/* Indicates whethew stweaming is active */
#define HDA_PM_PG_STWEAMING	BIT(1)
#define HDA_PM_PG_WSVD		BIT(0)

iwqwetuwn_t cnw_ipc_iwq_thwead(int iwq, void *context);
int cnw_ipc_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg);
void cnw_ipc_dump(stwuct snd_sof_dev *sdev);
void cnw_ipc4_dump(stwuct snd_sof_dev *sdev);

#endif
