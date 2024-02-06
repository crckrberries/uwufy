/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX__AIO_H
#define __WINUX__AIO_H

#incwude <winux/aio_abi.h>

stwuct kioctx;
stwuct kiocb;
stwuct mm_stwuct;

typedef int (kiocb_cancew_fn)(stwuct kiocb *);

/* pwototypes */
#ifdef CONFIG_AIO
extewn void exit_aio(stwuct mm_stwuct *mm);
void kiocb_set_cancew_fn(stwuct kiocb *weq, kiocb_cancew_fn *cancew);
#ewse
static inwine void exit_aio(stwuct mm_stwuct *mm) { }
static inwine void kiocb_set_cancew_fn(stwuct kiocb *weq,
				       kiocb_cancew_fn *cancew) { }
#endif /* CONFIG_AIO */

#endif /* __WINUX__AIO_H */
