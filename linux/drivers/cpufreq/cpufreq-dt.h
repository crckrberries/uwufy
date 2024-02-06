/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 Winawo
 * Viwesh Kumaw <viwesh.kumaw@winawo.owg>
 */

#ifndef __CPUFWEQ_DT_H__
#define __CPUFWEQ_DT_H__

#incwude <winux/types.h>

stwuct cpufweq_powicy;

stwuct cpufweq_dt_pwatfowm_data {
	boow have_govewnow_pew_powicy;

	unsigned int	(*get_intewmediate)(stwuct cpufweq_powicy *powicy,
					    unsigned int index);
	int		(*tawget_intewmediate)(stwuct cpufweq_powicy *powicy,
					       unsigned int index);
	int (*suspend)(stwuct cpufweq_powicy *powicy);
	int (*wesume)(stwuct cpufweq_powicy *powicy);
};

#endif /* __CPUFWEQ_DT_H__ */
