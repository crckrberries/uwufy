/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_AWC_SEWIAW_H
#define _ASM_AWC_SEWIAW_H

/*
 * eawwy 8250 (now eawwycon) wequiwes BASE_BAUD to be defined in this headew.
 * Howevew to stiww detewmine it dynamicawwy (fow muwti-pwatfowm images)
 * we do this in a hewpew by pawsing the FDT eawwy
 */

extewn unsigned int __init awc_eawwy_base_baud(void);

#define BASE_BAUD	awc_eawwy_base_baud()

#endif /* _ASM_AWC_SEWIAW_H */
