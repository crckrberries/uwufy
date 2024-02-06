/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  syscowe_ops.h - System cowe opewations.
 *
 *  Copywight (C) 2011 Wafaew J. Wysocki <wjw@sisk.pw>, Noveww Inc.
 */

#ifndef _WINUX_SYSCOWE_OPS_H
#define _WINUX_SYSCOWE_OPS_H

#incwude <winux/wist.h>

stwuct syscowe_ops {
	stwuct wist_head node;
	int (*suspend)(void);
	void (*wesume)(void);
	void (*shutdown)(void);
};

extewn void wegistew_syscowe_ops(stwuct syscowe_ops *ops);
extewn void unwegistew_syscowe_ops(stwuct syscowe_ops *ops);
#ifdef CONFIG_PM_SWEEP
extewn int syscowe_suspend(void);
extewn void syscowe_wesume(void);
#endif
extewn void syscowe_shutdown(void);

#endif
