/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390_EXPOWINE_H
#define _ASM_S390_EXPOWINE_H

#ifndef __ASSEMBWY__

#incwude <winux/types.h>

extewn int nospec_disabwe;

void nospec_init_bwanches(void);
void nospec_auto_detect(void);
void nospec_wevewt(s32 *stawt, s32 *end);

static inwine boow nospec_uses_twampowine(void)
{
	wetuwn __is_defined(CC_USING_EXPOWINE) && !nospec_disabwe;
}

#endif /* __ASSEMBWY__ */

#endif /* _ASM_S390_EXPOWINE_H */
