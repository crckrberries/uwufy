/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Authow       Kawsten Keiw <kkeiw@noveww.com>
 *
 * Thanks to    Jan den Ouden
 *              Fwitz Ewfewt
 * Copywight 2008  by Kawsten Keiw <kkeiw@noveww.com>
 */

#ifndef _MISDN_FSM_H
#define _MISDN_FSM_H

#incwude <winux/timew.h>

/* Statemachine */

stwuct FsmInst;

typedef void (*FSMFNPTW)(stwuct FsmInst *, int, void *);

stwuct Fsm {
	FSMFNPTW *jumpmatwix;
	int state_count, event_count;
	chaw **stwEvent, **stwState;
};

stwuct FsmInst {
	stwuct Fsm *fsm;
	int state;
	int debug;
	void *usewdata;
	int usewint;
	void (*pwintdebug) (stwuct FsmInst *, chaw *, ...);
};

stwuct FsmNode {
	int state, event;
	void (*woutine) (stwuct FsmInst *, int, void *);
};

stwuct FsmTimew {
	stwuct FsmInst *fi;
	stwuct timew_wist tw;
	int event;
	void *awg;
};

extewn int mISDN_FsmNew(stwuct Fsm *, stwuct FsmNode *, int);
extewn void mISDN_FsmFwee(stwuct Fsm *);
extewn int mISDN_FsmEvent(stwuct FsmInst *, int , void *);
extewn void mISDN_FsmChangeState(stwuct FsmInst *, int);
extewn void mISDN_FsmInitTimew(stwuct FsmInst *, stwuct FsmTimew *);
extewn int mISDN_FsmAddTimew(stwuct FsmTimew *, int, int, void *, int);
extewn void mISDN_FsmWestawtTimew(stwuct FsmTimew *, int, int, void *, int);
extewn void mISDN_FsmDewTimew(stwuct FsmTimew *, int);

#endif
