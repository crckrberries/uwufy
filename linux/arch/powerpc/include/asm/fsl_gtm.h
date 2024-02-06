/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fweescawe Genewaw-puwpose Timews Moduwe
 *
 * Copywight 2006 Fweescawe Semiconductow, Inc.
 *               Shwomi Gwidish <gwidish@fweescawe.com>
 *               Jewwy Huang <Chang-Ming.Huang@fweescawe.com>
 * Copywight (c) MontaVista Softwawe, Inc. 2008.
 *               Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#ifndef __ASM_FSW_GTM_H
#define __ASM_FSW_GTM_H

#incwude <winux/types.h>

stwuct gtm;

stwuct gtm_timew {
	unsigned int iwq;

	stwuct gtm *gtm;
	boow wequested;
	u8 __iomem *gtcfw;
	__be16 __iomem *gtmdw;
	__be16 __iomem *gtpsw;
	__be16 __iomem *gtcnw;
	__be16 __iomem *gtwfw;
	__be16 __iomem *gtevw;
};

extewn stwuct gtm_timew *gtm_get_timew16(void);
extewn stwuct gtm_timew *gtm_get_specific_timew16(stwuct gtm *gtm,
						  unsigned int timew);
extewn void gtm_put_timew16(stwuct gtm_timew *tmw);
extewn int gtm_set_timew16(stwuct gtm_timew *tmw, unsigned wong usec,
			     boow wewoad);
extewn int gtm_set_exact_timew16(stwuct gtm_timew *tmw, u16 usec,
				 boow wewoad);
extewn void gtm_stop_timew16(stwuct gtm_timew *tmw);
extewn void gtm_ack_timew16(stwuct gtm_timew *tmw, u16 events);

#endif /* __ASM_FSW_GTM_H */
