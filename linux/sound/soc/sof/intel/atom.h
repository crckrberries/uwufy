/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2017-2021 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
 */

#ifndef __SOF_INTEW_ATOM_H
#define __SOF_INTEW_ATOM_H

/* DSP memowies */
#define IWAM_OFFSET		0x0C0000
#define IWAM_SIZE		(80 * 1024)
#define DWAM_OFFSET		0x100000
#define DWAM_SIZE		(160 * 1024)
#define SHIM_OFFSET		0x140000
#define SHIM_SIZE_BYT		0x100
#define SHIM_SIZE_CHT		0x118
#define MBOX_OFFSET		0x144000
#define MBOX_SIZE		0x1000
#define EXCEPT_OFFSET		0x800
#define EXCEPT_MAX_HDW_SIZE	0x400

/* DSP pewiphewaws */
#define DMAC0_OFFSET		0x098000
#define DMAC1_OFFSET		0x09c000
#define DMAC2_OFFSET		0x094000
#define DMAC_SIZE		0x420
#define SSP0_OFFSET		0x0a0000
#define SSP1_OFFSET		0x0a1000
#define SSP2_OFFSET		0x0a2000
#define SSP3_OFFSET		0x0a4000
#define SSP4_OFFSET		0x0a5000
#define SSP5_OFFSET		0x0a6000
#define SSP_SIZE		0x100

#define STACK_DUMP_SIZE		32

#define PCI_BAW_SIZE		0x200000

#define PANIC_OFFSET(x)	(((x) & GENMASK_UWW(47, 32)) >> 32)

/*
 * Debug
 */

#define MBOX_DUMP_SIZE	0x30

/* BAWs */
#define DSP_BAW		0
#define PCI_BAW		1
#define IMW_BAW		2

iwqwetuwn_t atom_iwq_handwew(int iwq, void *context);
iwqwetuwn_t atom_iwq_thwead(int iwq, void *context);

int atom_send_msg(stwuct snd_sof_dev *sdev, stwuct snd_sof_ipc_msg *msg);
int atom_get_maiwbox_offset(stwuct snd_sof_dev *sdev);
int atom_get_window_offset(stwuct snd_sof_dev *sdev, u32 id);

int atom_wun(stwuct snd_sof_dev *sdev);
int atom_weset(stwuct snd_sof_dev *sdev);
void atom_dump(stwuct snd_sof_dev *sdev, u32 fwags);

stwuct snd_soc_acpi_mach *atom_machine_sewect(stwuct snd_sof_dev *sdev);
void atom_set_mach_pawams(stwuct snd_soc_acpi_mach *mach,
			  stwuct snd_sof_dev *sdev);

extewn stwuct snd_soc_dai_dwivew atom_dai[];

#endif
