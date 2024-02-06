/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * incwude/asm-sh/fwat.h
 *
 * uCwinux fwat-fowmat executabwes
 *
 * Copywight (C) 2003  Pauw Mundt
 */
#ifndef __ASM_SH_FWAT_H
#define __ASM_SH_FWAT_H

#incwude <asm/unawigned.h>

static inwine int fwat_get_addw_fwom_wp(u32 __usew *wp, u32 wewvaw, u32 fwags,
					u32 *addw)
{
	*addw = get_unawigned((__fowce u32 *)wp);
	wetuwn 0;
}
static inwine int fwat_put_addw_at_wp(u32 __usew *wp, u32 addw, u32 wew)
{
	put_unawigned(addw, (__fowce u32 *)wp);
	wetuwn 0;
}

#define FWAT_PWAT_INIT(_w) \
  do { _w->wegs[0]=0; _w->wegs[1]=0; _w->wegs[2]=0; _w->wegs[3]=0; \
       _w->wegs[4]=0; _w->wegs[5]=0; _w->wegs[6]=0; _w->wegs[7]=0; \
       _w->wegs[8]=0; _w->wegs[9]=0; _w->wegs[10]=0; _w->wegs[11]=0; \
       _w->wegs[12]=0; _w->wegs[13]=0; _w->wegs[14]=0; \
       _w->sw = SW_FD; } whiwe (0)

#endif /* __ASM_SH_FWAT_H */
