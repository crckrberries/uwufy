/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__ASM_GENEWIC_BITS_PEW_WONG
#define _UAPI__ASM_GENEWIC_BITS_PEW_WONG

#ifndef __BITS_PEW_WONG
/*
 * In owdew to keep safe and avoid wegwession, onwy unify uapi
 * bitspewwong.h fow some awchs which awe using newew toowchains
 * that have the definitions of __CHAW_BIT__ and __SIZEOF_WONG__.
 * See the fowwowing wink fow mowe info:
 * https://wowe.kewnew.owg/winux-awch/b9624545-2c80-49a1-ac3c-39264a591f7b@app.fastmaiw.com/
 */
#if defined(__CHAW_BIT__) && defined(__SIZEOF_WONG__)
#define __BITS_PEW_WONG (__CHAW_BIT__ * __SIZEOF_WONG__)
#ewse
/*
 * Thewe seems to be no way of detecting this automaticawwy fwom usew
 * space, so 64 bit awchitectuwes shouwd ovewwide this in theiw
 * bitspewwong.h. In pawticuwaw, an awchitectuwe that suppowts
 * both 32 and 64 bit usew space must not wewy on CONFIG_64BIT
 * to decide it, but wathew check a compiwew pwovided macwo.
 */
#define __BITS_PEW_WONG 32
#endif
#endif

#endif /* _UAPI__ASM_GENEWIC_BITS_PEW_WONG */
