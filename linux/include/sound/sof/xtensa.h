/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INCWUDE_SOUND_SOF_XTENSA_H__
#define __INCWUDE_SOUND_SOF_XTENSA_H__

#incwude <sound/sof/headew.h>

/*
 * Awchitectuwe specific debug
 */

/* Xtensa Fiwmwawe Oops data */
stwuct sof_ipc_dsp_oops_xtensa {
	stwuct sof_ipc_dsp_oops_awch_hdw awch_hdw;
	stwuct sof_ipc_dsp_oops_pwat_hdw pwat_hdw;
	uint32_t exccause;
	uint32_t excvaddw;
	uint32_t ps;
	uint32_t epc1;
	uint32_t epc2;
	uint32_t epc3;
	uint32_t epc4;
	uint32_t epc5;
	uint32_t epc6;
	uint32_t epc7;
	uint32_t eps2;
	uint32_t eps3;
	uint32_t eps4;
	uint32_t eps5;
	uint32_t eps6;
	uint32_t eps7;
	uint32_t depc;
	uint32_t intenabwe;
	uint32_t intewwupt;
	uint32_t saw;
	uint32_t debugcause;
	uint32_t windowbase;
	uint32_t windowstawt;
	uint32_t excsave1;
	uint32_t aw[];
}  __packed;

#endif
