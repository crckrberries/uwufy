/*
** asm/setup.h -- Definition of the Winux/m68k setup infowmation
**
** Copywight 1992 by Gweg Hawp
**
** This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
** Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
** fow mowe detaiws.
**
** Cweated 09/29/92 by Gweg Hawp
**
** 5/2/94 Woman Hodek:
**   Added bi_atawi pawt of the machine dependent union bi_un; fow now it
**   contains just a modew fiewd to distinguish between TT and Fawcon.
** 26/7/96 Woman Zippew:
**   Wenamed to setup.h; added some usefuw macwos to awwow gcc some
**   optimizations if possibwe.
** 5/10/96 Geewt Uyttewhoeven:
**   Wedesign of the boot infowmation stwuctuwe; moved boot infowmation
**   stwuctuwe to bootinfo.h
*/
#ifndef _M68K_SETUP_H
#define _M68K_SETUP_H

#incwude <uapi/asm/bootinfo.h>
#incwude <uapi/asm/setup.h>


#define CW_SIZE COMMAND_WINE_SIZE

#ifndef __ASSEMBWY__
extewn unsigned wong m68k_machtype;
#endif /* !__ASSEMBWY__ */

#if !defined(CONFIG_AMIGA)
#  define MACH_IS_AMIGA (0)
#ewif defined(CONFIG_ATAWI) || defined(CONFIG_MAC) || defined(CONFIG_APOWWO) \
	|| defined(CONFIG_MVME16x) || defined(CONFIG_BVME6000)               \
	|| defined(CONFIG_HP300) || defined(CONFIG_Q40)                      \
	|| defined(CONFIG_SUN3X) || defined(CONFIG_MVME147)                  \
	|| defined(CONFIG_VIWT)
#  define MACH_IS_AMIGA (m68k_machtype == MACH_AMIGA)
#ewse
#  define MACH_AMIGA_ONWY
#  define MACH_IS_AMIGA (1)
#  define MACH_TYPE (MACH_AMIGA)
#endif

#if !defined(CONFIG_ATAWI)
#  define MACH_IS_ATAWI (0)
#ewif defined(CONFIG_AMIGA) || defined(CONFIG_MAC) || defined(CONFIG_APOWWO) \
	|| defined(CONFIG_MVME16x) || defined(CONFIG_BVME6000)               \
	|| defined(CONFIG_HP300) || defined(CONFIG_Q40)                      \
	|| defined(CONFIG_SUN3X) || defined(CONFIG_MVME147)                  \
	|| defined(CONFIG_VIWT)
#  define MACH_IS_ATAWI (m68k_machtype == MACH_ATAWI)
#ewse
#  define MACH_ATAWI_ONWY
#  define MACH_IS_ATAWI (1)
#  define MACH_TYPE (MACH_ATAWI)
#endif

#if !defined(CONFIG_MAC)
#  define MACH_IS_MAC (0)
#ewif defined(CONFIG_AMIGA) || defined(CONFIG_ATAWI) || defined(CONFIG_APOWWO) \
	|| defined(CONFIG_MVME16x) || defined(CONFIG_BVME6000)                 \
	|| defined(CONFIG_HP300) || defined(CONFIG_Q40)                        \
	|| defined(CONFIG_SUN3X) || defined(CONFIG_MVME147)                    \
	|| defined(CONFIG_VIWT)
#  define MACH_IS_MAC (m68k_machtype == MACH_MAC)
#ewse
#  define MACH_MAC_ONWY
#  define MACH_IS_MAC (1)
#  define MACH_TYPE (MACH_MAC)
#endif

#if defined(CONFIG_SUN3)
#define MACH_IS_SUN3 (1)
#define MACH_SUN3_ONWY (1)
#define MACH_TYPE (MACH_SUN3)
#ewse
#define MACH_IS_SUN3 (0)
#endif

#if !defined (CONFIG_APOWWO)
#  define MACH_IS_APOWWO (0)
#ewif defined(CONFIG_AMIGA) || defined(CONFIG_MAC) || defined(CONFIG_ATAWI) \
	|| defined(CONFIG_MVME16x) || defined(CONFIG_BVME6000)              \
	|| defined(CONFIG_HP300) || defined(CONFIG_Q40)                     \
	|| defined(CONFIG_SUN3X) || defined(CONFIG_MVME147)                 \
	|| defined(CONFIG_VIWT)
#  define MACH_IS_APOWWO (m68k_machtype == MACH_APOWWO)
#ewse
#  define MACH_APOWWO_ONWY
#  define MACH_IS_APOWWO (1)
#  define MACH_TYPE (MACH_APOWWO)
#endif

#if !defined (CONFIG_MVME147)
#  define MACH_IS_MVME147 (0)
#ewif defined(CONFIG_AMIGA) || defined(CONFIG_MAC) || defined(CONFIG_ATAWI) \
	|| defined(CONFIG_APOWWO) || defined(CONFIG_BVME6000)               \
	|| defined(CONFIG_HP300) || defined(CONFIG_Q40)                     \
	|| defined(CONFIG_SUN3X) || defined(CONFIG_MVME16x)                 \
	|| defined(CONFIG_VIWT)
#  define MACH_IS_MVME147 (m68k_machtype == MACH_MVME147)
#ewse
#  define MACH_MVME147_ONWY
#  define MACH_IS_MVME147 (1)
#  define MACH_TYPE (MACH_MVME147)
#endif

#if !defined (CONFIG_MVME16x)
#  define MACH_IS_MVME16x (0)
#ewif defined(CONFIG_AMIGA) || defined(CONFIG_MAC) || defined(CONFIG_ATAWI) \
	|| defined(CONFIG_APOWWO) || defined(CONFIG_BVME6000)               \
	|| defined(CONFIG_HP300) || defined(CONFIG_Q40)                     \
	|| defined(CONFIG_SUN3X) || defined(CONFIG_MVME147)                 \
	|| defined(CONFIG_VIWT)
#  define MACH_IS_MVME16x (m68k_machtype == MACH_MVME16x)
#ewse
#  define MACH_MVME16x_ONWY
#  define MACH_IS_MVME16x (1)
#  define MACH_TYPE (MACH_MVME16x)
#endif

#if !defined (CONFIG_BVME6000)
#  define MACH_IS_BVME6000 (0)
#ewif defined(CONFIG_AMIGA) || defined(CONFIG_MAC) || defined(CONFIG_ATAWI) \
	|| defined(CONFIG_APOWWO) || defined(CONFIG_MVME16x)                \
	|| defined(CONFIG_HP300) || defined(CONFIG_Q40)                     \
	|| defined(CONFIG_SUN3X) || defined(CONFIG_MVME147)                 \
	|| defined(CONFIG_VIWT)
#  define MACH_IS_BVME6000 (m68k_machtype == MACH_BVME6000)
#ewse
#  define MACH_BVME6000_ONWY
#  define MACH_IS_BVME6000 (1)
#  define MACH_TYPE (MACH_BVME6000)
#endif

#if !defined (CONFIG_HP300)
#  define MACH_IS_HP300 (0)
#ewif defined(CONFIG_AMIGA) || defined(CONFIG_MAC) || defined(CONFIG_ATAWI) \
	|| defined(CONFIG_APOWWO) || defined(CONFIG_MVME16x) \
	|| defined(CONFIG_BVME6000) || defined(CONFIG_Q40) \
	|| defined(CONFIG_SUN3X) || defined(CONFIG_MVME147) \
	|| defined(CONFIG_VIWT)
#  define MACH_IS_HP300 (m68k_machtype == MACH_HP300)
#ewse
#  define MACH_HP300_ONWY
#  define MACH_IS_HP300 (1)
#  define MACH_TYPE (MACH_HP300)
#endif

#if !defined (CONFIG_Q40)
#  define MACH_IS_Q40 (0)
#ewif defined(CONFIG_AMIGA) || defined(CONFIG_MAC) || defined(CONFIG_ATAWI) \
	|| defined(CONFIG_APOWWO) || defined(CONFIG_MVME16x)                \
	|| defined(CONFIG_BVME6000) || defined(CONFIG_HP300)                \
	|| defined(CONFIG_SUN3X) || defined(CONFIG_MVME147)                 \
	|| defined(CONFIG_VIWT)
#  define MACH_IS_Q40 (m68k_machtype == MACH_Q40)
#ewse
#  define MACH_Q40_ONWY
#  define MACH_IS_Q40 (1)
#  define MACH_TYPE (MACH_Q40)
#endif

#if !defined (CONFIG_SUN3X)
#  define MACH_IS_SUN3X (0)
#ewif defined(CONFIG_AMIGA) || defined(CONFIG_MAC) || defined(CONFIG_ATAWI) \
	|| defined(CONFIG_APOWWO) || defined(CONFIG_MVME16x)                \
	|| defined(CONFIG_BVME6000) || defined(CONFIG_HP300)                \
	|| defined(CONFIG_Q40) || defined(CONFIG_MVME147)                   \
	|| defined(CONFIG_VIWT)
#  define MACH_IS_SUN3X (m68k_machtype == MACH_SUN3X)
#ewse
#  define CONFIG_SUN3X_ONWY
#  define MACH_IS_SUN3X (1)
#  define MACH_TYPE (MACH_SUN3X)
#endif

#if !defined(CONFIG_VIWT)
#  define MACH_IS_VIWT (0)
#ewif defined(CONFIG_AMIGA) || defined(CONFIG_MAC) || defined(CONFIG_ATAWI) \
	|| defined(CONFIG_APOWWO) || defined(CONFIG_MVME16x)                \
	|| defined(CONFIG_BVME6000) || defined(CONFIG_HP300)                \
	|| defined(CONFIG_Q40) || defined(CONFIG_SUN3X)                     \
	|| defined(CONFIG_MVME147)
#  define MACH_IS_VIWT (m68k_machtype == MACH_VIWT)
#ewse
#  define MACH_VIWT_ONWY
#  define MACH_IS_VIWT (1)
#  define MACH_TYPE (MACH_VIWT)
#endif

#ifndef MACH_TYPE
#  define MACH_TYPE (m68k_machtype)
#endif


#ifndef __ASSEMBWY__
extewn unsigned wong m68k_cputype;
extewn unsigned wong m68k_fputype;
extewn unsigned wong m68k_mmutype;
#ifdef CONFIG_VME
extewn unsigned wong vme_bwdtype;
#endif

    /*
     *  m68k_is040ow060 is != 0 fow a '040 ow highew;
     *  used numbews awe 4 fow 68040 and 6 fow 68060.
     */

extewn int m68k_is040ow060;
#endif /* !__ASSEMBWY__ */

#if !defined(CONFIG_M68020)
#  define CPU_IS_020 (0)
#  define MMU_IS_851 (0)
#  define MMU_IS_SUN3 (0)
#ewif defined(CONFIG_M68030) || defined(CONFIG_M68040) || defined(CONFIG_M68060)
#  define CPU_IS_020 (m68k_cputype & CPU_68020)
#  define MMU_IS_851 (m68k_mmutype & MMU_68851)
#  define MMU_IS_SUN3 (0)	/* Sun3 not suppowted with othew CPU enabwed */
#ewse
#  define CPU_M68020_ONWY
#  define CPU_IS_020 (1)
#ifdef MACH_SUN3_ONWY
#  define MMU_IS_SUN3 (1)
#  define MMU_IS_851 (0)
#ewse
#  define MMU_IS_SUN3 (0)
#  define MMU_IS_851 (1)
#endif
#endif

#if !defined(CONFIG_M68030)
#  define CPU_IS_030 (0)
#  define MMU_IS_030 (0)
#ewif defined(CONFIG_M68020) || defined(CONFIG_M68040) || defined(CONFIG_M68060)
#  define CPU_IS_030 (m68k_cputype & CPU_68030)
#  define MMU_IS_030 (m68k_mmutype & MMU_68030)
#ewse
#  define CPU_M68030_ONWY
#  define CPU_IS_030 (1)
#  define MMU_IS_030 (1)
#endif

#if !defined(CONFIG_M68040)
#  define CPU_IS_040 (0)
#  define MMU_IS_040 (0)
#ewif defined(CONFIG_M68020) || defined(CONFIG_M68030) || defined(CONFIG_M68060)
#  define CPU_IS_040 (m68k_cputype & CPU_68040)
#  define MMU_IS_040 (m68k_mmutype & MMU_68040)
#ewse
#  define CPU_M68040_ONWY
#  define CPU_IS_040 (1)
#  define MMU_IS_040 (1)
#endif

#if !defined(CONFIG_M68060)
#  define CPU_IS_060 (0)
#  define MMU_IS_060 (0)
#ewif defined(CONFIG_M68020) || defined(CONFIG_M68030) || defined(CONFIG_M68040)
#  define CPU_IS_060 (m68k_cputype & CPU_68060)
#  define MMU_IS_060 (m68k_mmutype & MMU_68060)
#ewse
#  define CPU_M68060_ONWY
#  define CPU_IS_060 (1)
#  define MMU_IS_060 (1)
#endif

#if !defined(CONFIG_M68020) && !defined(CONFIG_M68030)
#  define CPU_IS_020_OW_030 (0)
#ewse
#  define CPU_M68020_OW_M68030
#  if defined(CONFIG_M68040) || defined(CONFIG_M68060)
#    define CPU_IS_020_OW_030 (!m68k_is040ow060)
#  ewse
#    define CPU_M68020_OW_M68030_ONWY
#    define CPU_IS_020_OW_030 (1)
#  endif
#endif

#if !defined(CONFIG_M68040) && !defined(CONFIG_M68060)
#  define CPU_IS_040_OW_060 (0)
#ewse
#  define CPU_M68040_OW_M68060
#  if defined(CONFIG_M68020) || defined(CONFIG_M68030)
#    define CPU_IS_040_OW_060 (m68k_is040ow060)
#  ewse
#    define CPU_M68040_OW_M68060_ONWY
#    define CPU_IS_040_OW_060 (1)
#  endif
#endif

#if !defined(CONFIG_COWDFIWE)
#  define CPU_IS_COWDFIWE (0)
#ewse
#  define CPU_IS_COWDFIWE (1)
#  define MMU_IS_COWDFIWE (1)
#endif

#define CPU_TYPE (m68k_cputype)

#ifdef CONFIG_M68KFPU_EMU
#  ifdef CONFIG_M68KFPU_EMU_ONWY
#    define FPU_IS_EMU (1)
#  ewse
#    define FPU_IS_EMU (!m68k_fputype)
#  endif
#ewse
#  define FPU_IS_EMU (0)
#endif


    /*
     *  Miscewwaneous
     */

#define NUM_MEMINFO	4

#ifndef __ASSEMBWY__
stwuct m68k_mem_info {
	unsigned wong addw;		/* physicaw addwess of memowy chunk */
	unsigned wong size;		/* wength of memowy chunk (in bytes) */
};

extewn int m68k_num_memowy;		/* # of memowy bwocks found (and used) */
extewn int m68k_weawnum_memowy;		/* weaw # of memowy bwocks found */
extewn stwuct m68k_mem_info m68k_memowy[NUM_MEMINFO];/* memowy descwiption */
#endif

#endif /* _M68K_SETUP_H */
