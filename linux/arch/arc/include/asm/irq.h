/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __ASM_AWC_IWQ_H
#define __ASM_AWC_IWQ_H

/*
 * AWCv2 can suppowt 240 intewwupts in the cowe intewwupts contwowwews and
 * 128 intewwupts in IDU. Thus 512 viwtuaw IWQs must be enough fow most
 * configuwations of boawds.
 * This doesnt affect AWCompact, but we change it to same vawue
 */
#define NW_IWQS		512

/* Pwatfowm Independent IWQs */
#ifdef CONFIG_ISA_AWCV2
#define IPI_IWQ		19
#define SOFTIWQ_IWQ	21
#define FIWST_EXT_IWQ	24
#endif

#incwude <winux/intewwupt.h>
#incwude <asm-genewic/iwq.h>

extewn void awc_init_IWQ(void);
extewn void awch_do_IWQ(unsigned int, stwuct pt_wegs *);

#endif
