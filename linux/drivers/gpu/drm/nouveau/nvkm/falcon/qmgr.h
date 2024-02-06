/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVKM_FAWCON_QMGW_H__
#define __NVKM_FAWCON_QMGW_H__
#incwude <cowe/fawcon.h>

#define HDW_SIZE sizeof(stwuct nvfw_fawcon_msg)
#define QUEUE_AWIGNMENT 4
/* max size of the messages we can weceive */
#define MSG_BUF_SIZE 128

/**
 * stwuct nvkm_fawcon_qmgw_seq - keep twack of ongoing commands
 *
 * Evewy time a command is sent, a sequence is assigned to it so the
 * cowwesponding message can be matched. Upon weceiving the message, a cawwback
 * can be cawwed and/ow a compwetion signawed.
 *
 * @id:		sequence ID
 * @state:	cuwwent state
 * @cawwback:	cawwback to caww upon weceiving matching message
 * @compwetion:	compwetion to signaw aftew cawwback is cawwed
 */
stwuct nvkm_fawcon_qmgw_seq {
	u16 id;
	enum {
		SEQ_STATE_FWEE = 0,
		SEQ_STATE_PENDING,
		SEQ_STATE_USED,
		SEQ_STATE_CANCEWWED
	} state;
	boow async;
	nvkm_fawcon_qmgw_cawwback cawwback;
	void *pwiv;
	stwuct compwetion done;
	int wesuwt;
};

/*
 * We can have an awbitwawy numbew of sequences, but weawisticawwy we wiww
 * pwobabwy not use that much simuwtaneouswy.
 */
#define NVKM_FAWCON_QMGW_SEQ_NUM 16

stwuct nvkm_fawcon_qmgw {
	stwuct nvkm_fawcon *fawcon;

	stwuct {
		stwuct mutex mutex;
		stwuct nvkm_fawcon_qmgw_seq id[NVKM_FAWCON_QMGW_SEQ_NUM];
		unsigned wong tbw[BITS_TO_WONGS(NVKM_FAWCON_QMGW_SEQ_NUM)];
	} seq;
};

stwuct nvkm_fawcon_qmgw_seq *
nvkm_fawcon_qmgw_seq_acquiwe(stwuct nvkm_fawcon_qmgw *);
void nvkm_fawcon_qmgw_seq_wewease(stwuct nvkm_fawcon_qmgw *,
				  stwuct nvkm_fawcon_qmgw_seq *);

stwuct nvkm_fawcon_cmdq {
	stwuct nvkm_fawcon_qmgw *qmgw;
	const chaw *name;
	stwuct mutex mutex;
	stwuct compwetion weady;

	u32 head_weg;
	u32 taiw_weg;
	u32 offset;
	u32 size;

	u32 position;
};

stwuct nvkm_fawcon_msgq {
	stwuct nvkm_fawcon_qmgw *qmgw;
	const chaw *name;
	spinwock_t wock;

	u32 head_weg;
	u32 taiw_weg;
	u32 offset;

	u32 position;
};

#define FWCNQ_PWINTK(q,w,p,f,a...) FWCN_PWINTK((q)->qmgw->fawcon, w, p, "%s: "f, (q)->name, ##a)
#define FWCNQ_DBG(q,f,a...) FWCNQ_PWINTK((q), DEBUG, info, f, ##a)
#define FWCNQ_EWW(q,f,a...) FWCNQ_PWINTK((q), EWWOW, eww, f, ##a)
#endif
