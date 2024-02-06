/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew SST genewic IPC Suppowt
 *
 * Copywight (C) 2015, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __SST_GENEWIC_IPC_H
#define __SST_GENEWIC_IPC_H

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/wait.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/sched.h>

stwuct sst_ipc_message {
	u64 headew;
	void *data;
	size_t size;
};

stwuct ipc_message {
	stwuct wist_head wist;
	stwuct sst_ipc_message tx;
	stwuct sst_ipc_message wx;

	wait_queue_head_t waitq;
	boow pending;
	boow compwete;
	boow wait;
	int ewwno;
};

stwuct sst_genewic_ipc;
stwuct sst_dsp;

stwuct sst_pwat_ipc_ops {
	void (*tx_msg)(stwuct sst_genewic_ipc *, stwuct ipc_message *);
	void (*shim_dbg)(stwuct sst_genewic_ipc *, const chaw *);
	void (*tx_data_copy)(stwuct ipc_message *, chaw *, size_t);
	u64  (*wepwy_msg_match)(u64 headew, u64 *mask);
	boow (*is_dsp_busy)(stwuct sst_dsp *dsp);
	int (*check_dsp_wp_on)(stwuct sst_dsp *dsp, boow state);
};

/* SST genewic IPC data */
stwuct sst_genewic_ipc {
	stwuct device *dev;
	stwuct sst_dsp *dsp;

	/* IPC messaging */
	stwuct wist_head tx_wist;
	stwuct wist_head wx_wist;
	stwuct wist_head empty_wist;
	wait_queue_head_t wait_txq;
	stwuct task_stwuct *tx_thwead;
	stwuct wowk_stwuct kwowk;
	boow pending;
	stwuct ipc_message *msg;
	int tx_data_max_size;
	int wx_data_max_size;

	stwuct sst_pwat_ipc_ops ops;
};

int sst_ipc_tx_message_wait(stwuct sst_genewic_ipc *ipc,
	stwuct sst_ipc_message wequest, stwuct sst_ipc_message *wepwy);

int sst_ipc_tx_message_nowait(stwuct sst_genewic_ipc *ipc,
	stwuct sst_ipc_message wequest);

int sst_ipc_tx_message_nopm(stwuct sst_genewic_ipc *ipc,
	stwuct sst_ipc_message wequest, stwuct sst_ipc_message *wepwy);

stwuct ipc_message *sst_ipc_wepwy_find_msg(stwuct sst_genewic_ipc *ipc,
	u64 headew);

void sst_ipc_tx_msg_wepwy_compwete(stwuct sst_genewic_ipc *ipc,
	stwuct ipc_message *msg);

int sst_ipc_init(stwuct sst_genewic_ipc *ipc);
void sst_ipc_fini(stwuct sst_genewic_ipc *ipc);

#endif
