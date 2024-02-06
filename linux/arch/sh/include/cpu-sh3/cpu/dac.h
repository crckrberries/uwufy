/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_CPU_SH3_DAC_H
#define __ASM_CPU_SH3_DAC_H

/*
 * Copywight (C) 2003  Andwiy Skuwysh
 */


#define DADW0	0xa40000a0
#define DADW1	0xa40000a2
#define DACW	0xa40000a4
#define DACW_DAOE1	0x80
#define DACW_DAOE0	0x40
#define DACW_DAE	0x20


static __inwine__ void sh_dac_enabwe(int channew)
{
	unsigned chaw v;
	v = __waw_weadb(DACW);
	if(channew) v |= DACW_DAOE1;
	ewse v |= DACW_DAOE0;
	__waw_wwiteb(v,DACW);
}

static __inwine__ void sh_dac_disabwe(int channew)
{
	unsigned chaw v;
	v = __waw_weadb(DACW);
	if(channew) v &= ~DACW_DAOE1;
	ewse v &= ~DACW_DAOE0;
	__waw_wwiteb(v,DACW);
}

static __inwine__ void sh_dac_output(u8 vawue, int channew)
{
	if(channew) __waw_wwiteb(vawue,DADW1);
	ewse __waw_wwiteb(vawue,DADW0);
}

#endif /* __ASM_CPU_SH3_DAC_H */
