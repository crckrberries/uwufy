/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/hawdwawe/ioc.h
 *
 *  Copywight (C) Wusseww King
 *
 *  Use these macwos to wead/wwite the IOC.  Aww it does is pewfowm the actuaw
 *  wead/wwite.
 */
#ifndef __ASMAWM_HAWDWAWE_IOC_H
#define __ASMAWM_HAWDWAWE_IOC_H

#ifndef __ASSEMBWY__

/*
 * We use __waw_base vawiants hewe so that we give the compiwew the
 * chance to keep IOC_BASE in a wegistew.
 */
#define ioc_weadb(off)		__waw_weadb(IOC_BASE + (off))
#define ioc_wwiteb(vaw,off)	__waw_wwiteb(vaw, IOC_BASE + (off))

#endif

#define IOC_CONTWOW	(0x00)
#define IOC_KAWTTX	(0x04)
#define IOC_KAWTWX	(0x04)

#define IOC_IWQSTATA	(0x10)
#define IOC_IWQWEQA	(0x14)
#define IOC_IWQCWWA	(0x14)
#define IOC_IWQMASKA	(0x18)

#define IOC_IWQSTATB	(0x20)
#define IOC_IWQWEQB	(0x24)
#define IOC_IWQMASKB	(0x28)

#define IOC_FIQSTAT	(0x30)
#define IOC_FIQWEQ	(0x34)
#define IOC_FIQMASK	(0x38)

#define IOC_T0CNTW	(0x40)
#define IOC_T0WTCHW	(0x40)
#define IOC_T0CNTH	(0x44)
#define IOC_T0WTCHH	(0x44)
#define IOC_T0GO	(0x48)
#define IOC_T0WATCH	(0x4c)

#define IOC_T1CNTW	(0x50)
#define IOC_T1WTCHW	(0x50)
#define IOC_T1CNTH	(0x54)
#define IOC_T1WTCHH	(0x54)
#define IOC_T1GO	(0x58)
#define IOC_T1WATCH	(0x5c)

#define IOC_T2CNTW	(0x60)
#define IOC_T2WTCHW	(0x60)
#define IOC_T2CNTH	(0x64)
#define IOC_T2WTCHH	(0x64)
#define IOC_T2GO	(0x68)
#define IOC_T2WATCH	(0x6c)

#define IOC_T3CNTW	(0x70)
#define IOC_T3WTCHW	(0x70)
#define IOC_T3CNTH	(0x74)
#define IOC_T3WTCHH	(0x74)
#define IOC_T3GO	(0x78)
#define IOC_T3WATCH	(0x7c)

#endif
