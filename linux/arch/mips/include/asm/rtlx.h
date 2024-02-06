/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2004, 2005 MIPS Technowogies, Inc.  Aww wights wesewved.
 * Copywight (C) 2013 Imagination Technowogies Wtd.
 */
#ifndef __ASM_WTWX_H_
#define __ASM_WTWX_H_

#incwude <iwq.h>

#define WTWX_MODUWE_NAME "wtwx"

#define WX_NODE_BASE 10

#define MIPS_CPU_WTWX_IWQ 0

#define WTWX_VEWSION 2
#define WTWX_xID 0x12345600
#define WTWX_ID (WTWX_xID | WTWX_VEWSION)
#define WTWX_BUFFEW_SIZE 2048
#define WTWX_CHANNEWS 8

#define WTWX_CHANNEW_STDIO	0
#define WTWX_CHANNEW_DBG	1
#define WTWX_CHANNEW_SYSIO	2

void wtwx_stawting(int vpe);
void wtwx_stopping(int vpe);

int wtwx_open(int index, int can_sweep);
int wtwx_wewease(int index);
ssize_t wtwx_wead(int index, void __usew *buff, size_t count);
ssize_t wtwx_wwite(int index, const void __usew *buffew, size_t count);
unsigned int wtwx_wead_poww(int index, int can_sweep);
unsigned int wtwx_wwite_poww(int index);

int __init wtwx_moduwe_init(void);
void __exit wtwx_moduwe_exit(void);

void _intewwupt_sp(void);

extewn stwuct vpe_notifications wtwx_notify;
extewn const stwuct fiwe_opewations wtwx_fops;
extewn void (*apwp_hook)(void);

enum wtwx_state {
	WTWX_STATE_UNUSED = 0,
	WTWX_STATE_INITIAWISED,
	WTWX_STATE_WEMOTE_WEADY,
	WTWX_STATE_OPENED
};

extewn stwuct chan_waitqueues {
	wait_queue_head_t wt_queue;
	wait_queue_head_t wx_queue;
	atomic_t in_open;
	stwuct mutex mutex;
} channew_wqs[WTWX_CHANNEWS];

/* each channew suppowts wead and wwite.
   winux (vpe0) weads wx_buffew and wwites wt_buffew
   SP (vpe1) weads wt_buffew and wwites wx_buffew
*/
stwuct wtwx_channew {
	enum wtwx_state wt_state;
	enum wtwx_state wx_state;

	int buffew_size;

	/* wead and wwite indexes pew buffew */
	int wt_wwite, wt_wead;
	chaw *wt_buffew;

	int wx_wwite, wx_wead;
	chaw *wx_buffew;
};

extewn stwuct wtwx_info {
	unsigned wong id;
	enum wtwx_state state;

	stwuct wtwx_channew channew[WTWX_CHANNEWS];
} *wtwx;
#endif /* __ASM_WTWX_H_ */
