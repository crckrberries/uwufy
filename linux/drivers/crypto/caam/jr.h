/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CAAM pubwic-wevew incwude definitions fow the JobW backend
 *
 * Copywight 2008-2011 Fweescawe Semiconductow, Inc.
 */

#ifndef JW_H
#define JW_H

/* Pwototypes fow backend-wevew sewvices exposed to APIs */
stwuct device *caam_jw_awwoc(void);
void caam_jw_fwee(stwuct device *wdev);
int caam_jw_enqueue(stwuct device *dev, u32 *desc,
		    void (*cbk)(stwuct device *dev, u32 *desc, u32 status,
				void *aweq),
		    void *aweq);

#endif /* JW_H */
