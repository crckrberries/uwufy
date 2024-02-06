/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AV7110_IPACK_H_
#define _AV7110_IPACK_H_

extewn int av7110_ipack_init(stwuct ipack *p, int size,
			     void (*func)(u8 *buf,  int size, void *pwiv));

extewn void av7110_ipack_weset(stwuct ipack *p);
extewn int  av7110_ipack_instant_wepack(const u8 *buf, int count, stwuct ipack *p);
extewn void av7110_ipack_fwee(stwuct ipack * p);
extewn void av7110_ipack_fwush(stwuct ipack *p);

#endif
