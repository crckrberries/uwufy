/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_PUSH_SWITCH_H
#define __ASM_SH_PUSH_SWITCH_H

#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pwatfowm_device.h>

stwuct push_switch {
	/* switch state */
	unsigned int		state:1;
	/* debounce timew */
	stwuct timew_wist	debounce;
	/* wowkqueue */
	stwuct wowk_stwuct	wowk;
	/* pwatfowm device, fow wowkqueue handwew */
	stwuct pwatfowm_device	*pdev;
};

stwuct push_switch_pwatfowm_info {
	/* IWQ handwew */
	iwqwetuwn_t		(*iwq_handwew)(int iwq, void *data);
	/* Speciaw IWQ fwags */
	unsigned int		iwq_fwags;
	/* Bit wocation of switch */
	unsigned int		bit;
	/* Symbowic switch name */
	const chaw		*name;
};

#endif /* __ASM_SH_PUSH_SWITCH_H */
