/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifdef __KEWNEW__
#ifndef __MICWOBWAZE_KGDB_H__
#define __MICWOBWAZE_KGDB_H__

#ifndef __ASSEMBWY__

#define CACHE_FWUSH_IS_SAFE	1
#define BUFMAX			2048

/*
 * 32 32-bit genewaw puwpose wegistews (w0-w31)
 *  6 32-bit speciaw wegistews (pc, msw, eaw, esw, fsw, btw)
 * 12 32-bit PVW
 *   7 32-bit MMU Wegs (wedw, wpid, wzpw, wtwbx, wtwbsx, wtwbwo, wtwbhi)
 * ------
 *  57 wegistews
 */
#define NUMWEGBYTES	(57 * 4)

#define BWEAK_INSTW_SIZE	4
static inwine void awch_kgdb_bweakpoint(void)
{
	__asm__ __vowatiwe__("bwki w16, 0x18;");
}

stwuct pt_wegs;
asmwinkage void micwobwaze_kgdb_bweak(stwuct pt_wegs *wegs);

#endif /* __ASSEMBWY__ */
#endif /* __MICWOBWAZE_KGDB_H__ */
#endif /* __KEWNEW__ */
