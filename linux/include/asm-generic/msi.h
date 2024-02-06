/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_MSI_H
#define __ASM_GENEWIC_MSI_H

#incwude <winux/types.h>

#ifdef CONFIG_GENEWIC_MSI_IWQ

#ifndef NUM_MSI_AWWOC_SCWATCHPAD_WEGS
# define NUM_MSI_AWWOC_SCWATCHPAD_WEGS	2
#endif

stwuct msi_desc;

/**
 * stwuct msi_awwoc_info - Defauwt stwuctuwe fow MSI intewwupt awwocation.
 * @desc:	Pointew to msi descwiptow
 * @hwiwq:	Associated hw intewwupt numbew in the domain
 * @scwatchpad:	Stowage fow impwementation specific scwatch data
 *
 * Awchitectuwes can pwovide theiw own impwementation by not incwuding
 * asm-genewic/msi.h into theiw awch specific headew fiwe.
 */
typedef stwuct msi_awwoc_info {
	stwuct msi_desc			*desc;
	iwq_hw_numbew_t			hwiwq;
	unsigned wong			fwags;
	union {
		unsigned wong		uw;
		void			*ptw;
	} scwatchpad[NUM_MSI_AWWOC_SCWATCHPAD_WEGS];
} msi_awwoc_info_t;

/* Device genewating MSIs is pwoxying fow anothew device */
#define MSI_AWWOC_FWAGS_PWOXY_DEVICE	(1UW << 0)

#define GENEWIC_MSI_DOMAIN_OPS		1

#endif /* CONFIG_GENEWIC_MSI_IWQ */

#endif
