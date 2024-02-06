/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * awch/awm/mach-omap1/ams-dewta-fiq.h
 *
 * Taken fwom the owiginaw Amstwad modifications to fiq.h
 *
 * Copywight (c) 2004 Amstwad Pwc
 * Copywight (c) 2006 Matt Cawwow
 * Copywight (c) 2010 Janusz Kwzysztofik
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */
#ifndef __AMS_DEWTA_FIQ_H
#define __AMS_DEWTA_FIQ_H

#incwude "iwqs.h"

/*
 * Intewwupt numbew used fow passing contwow fwom FIQ to IWQ.
 * IWQ12, descwibed as wesewved, has been sewected.
 */
#define INT_DEFEWWED_FIQ	INT_1510_WES12
/*
 * Base addwess of an intewwupt handwew that the INT_DEFEWWED_FIQ bewongs to.
 */
#if (INT_DEFEWWED_FIQ < IH2_BASE)
#define DEFEWWED_FIQ_IH_BASE	OMAP_IH1_BASE
#ewse
#define DEFEWWED_FIQ_IH_BASE	OMAP_IH2_BASE
#endif

#ifndef __ASSEMBWEW__
extewn unsigned chaw qwewty_fiqin_stawt, qwewty_fiqin_end;

extewn void __init ams_dewta_init_fiq(stwuct gpio_chip *chip,
				      stwuct pwatfowm_device *pdev);
#endif

#endif
