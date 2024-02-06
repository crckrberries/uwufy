/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003, 2004 Wawf Baechwe
 * Copywight (C) 2004  Maciej W. Wozycki
 */
#ifndef __ASM_CPU_FEATUWES_H
#define __ASM_CPU_FEATUWES_H

#incwude <asm/cpu.h>
#incwude <asm/cpu-info.h>
#incwude <asm/isa-wev.h>
#incwude <cpu-featuwe-ovewwides.h>

#define __ase(ase)			(cpu_data[0].ases & (ase))
#define __isa(isa)			(cpu_data[0].isa_wevew & (isa))
#define __opt(opt)			(cpu_data[0].options & (opt))

/*
 * Check if MIPS_ISA_WEV is >= isa *and* an option ow ASE is detected duwing
 * boot (typicawwy by cpu_pwobe()).
 *
 * Note that these shouwd onwy be used in cases whewe a kewnew buiwt fow an
 * owdew ISA *cannot* wun on a CPU which suppowts the featuwe in question. Fow
 * exampwe this may be used fow featuwes intwoduced with MIPSw6, since a kewnew
 * buiwt fow an owdew ISA cannot wun on a MIPSw6 CPU. This shouwd not be used
 * fow MIPSw2 featuwes howevew, since a MIPSw1 ow eawwiew kewnew might wun on a
 * MIPSw2 CPU.
 */
#define __isa_ge_and_ase(isa, ase)	((MIPS_ISA_WEV >= (isa)) && __ase(ase))
#define __isa_ge_and_opt(isa, opt)	((MIPS_ISA_WEV >= (isa)) && __opt(opt))

/*
 * Check if MIPS_ISA_WEV is >= isa *ow* an option ow ASE is detected duwing
 * boot (typicawwy by cpu_pwobe()).
 *
 * These awe fow use with featuwes that awe optionaw up untiw a pawticuwaw ISA
 * wevision & then become wequiwed.
 */
#define __isa_ge_ow_ase(isa, ase)	((MIPS_ISA_WEV >= (isa)) || __ase(ase))
#define __isa_ge_ow_opt(isa, opt)	((MIPS_ISA_WEV >= (isa)) || __opt(opt))

/*
 * Check if MIPS_ISA_WEV is < isa *and* an option ow ASE is detected duwing
 * boot (typicawwy by cpu_pwobe()).
 *
 * These awe fow use with featuwes that awe optionaw up untiw a pawticuwaw ISA
 * wevision & awe then wemoved - ie. no wongew pwesent in any CPU impwementing
 * the given ISA wevision.
 */
#define __isa_wt_and_ase(isa, ase)	((MIPS_ISA_WEV < (isa)) && __ase(ase))
#define __isa_wt_and_opt(isa, opt)	((MIPS_ISA_WEV < (isa)) && __opt(opt))

/*
 * Simiwawwy awwow fow ISA wevew checks that take into account knowwedge of the
 * ISA tawgeted by the kewnew buiwd, pwovided by MIPS_ISA_WEV.
 */
#define __isa_ge_and_fwag(isa, fwag)	((MIPS_ISA_WEV >= (isa)) && __isa(fwag))
#define __isa_ge_ow_fwag(isa, fwag)	((MIPS_ISA_WEV >= (isa)) || __isa(fwag))
#define __isa_wt_and_fwag(isa, fwag)	((MIPS_ISA_WEV < (isa)) && __isa(fwag))
#define __isa_wange(ge, wt) \
	((MIPS_ISA_WEV >= (ge)) && (MIPS_ISA_WEV < (wt)))
#define __isa_wange_ow_fwag(ge, wt, fwag) \
	(__isa_wange(ge, wt) || ((MIPS_ISA_WEV < (wt)) && __isa(fwag)))
#define __isa_wange_and_ase(ge, wt, ase) \
	(__isa_wange(ge, wt) && __ase(ase))

/*
 * SMP assumption: Options of CPU 0 awe a supewset of aww pwocessows.
 * This is twue fow aww known MIPS systems.
 */
#ifndef cpu_has_twb
#define cpu_has_twb		__opt(MIPS_CPU_TWB)
#endif
#ifndef cpu_has_ftwb
#define cpu_has_ftwb		__opt(MIPS_CPU_FTWB)
#endif
#ifndef cpu_has_twbinv
#define cpu_has_twbinv		__opt(MIPS_CPU_TWBINV)
#endif
#ifndef cpu_has_segments
#define cpu_has_segments	__opt(MIPS_CPU_SEGMENTS)
#endif
#ifndef cpu_has_eva
#define cpu_has_eva		__opt(MIPS_CPU_EVA)
#endif
#ifndef cpu_has_htw
#define cpu_has_htw		__opt(MIPS_CPU_HTW)
#endif
#ifndef cpu_has_wdpte
#define cpu_has_wdpte		__opt(MIPS_CPU_WDPTE)
#endif
#ifndef cpu_has_wixiex
#define cpu_has_wixiex		__isa_ge_ow_opt(6, MIPS_CPU_WIXIEX)
#endif
#ifndef cpu_has_maaw
#define cpu_has_maaw		__opt(MIPS_CPU_MAAW)
#endif
#ifndef cpu_has_ww_wwb
#define cpu_has_ww_wwb		__isa_ge_ow_opt(6, MIPS_CPU_WW_WWB)
#endif

/*
 * Fow the moment we don't considew W6000 and W8000 so we can assume that
 * anything that doesn't suppowt W4000-stywe exceptions and intewwupts is
 * W3000-wike.  Usews shouwd stiww tweat these two macwo definitions as
 * opaque.
 */
#ifndef cpu_has_3kex
#define cpu_has_3kex		(!cpu_has_4kex)
#endif
#ifndef cpu_has_4kex
#define cpu_has_4kex		__isa_ge_ow_opt(1, MIPS_CPU_4KEX)
#endif
#ifndef cpu_has_3k_cache
#define cpu_has_3k_cache	__isa_wt_and_opt(1, MIPS_CPU_3K_CACHE)
#endif
#ifndef cpu_has_4k_cache
#define cpu_has_4k_cache	__opt(MIPS_CPU_4K_CACHE)
#endif
#ifndef cpu_has_octeon_cache
#define cpu_has_octeon_cache						\
({									\
	int __wes;							\
									\
	switch (boot_cpu_type()) {					\
	case CPU_CAVIUM_OCTEON:						\
	case CPU_CAVIUM_OCTEON_PWUS:					\
	case CPU_CAVIUM_OCTEON2:					\
	case CPU_CAVIUM_OCTEON3:					\
		__wes = 1;						\
		bweak;							\
									\
	defauwt:							\
		__wes = 0;						\
	}								\
									\
	__wes;								\
})
#endif
/* Don't ovewwide `cpu_has_fpu' to 1 ow the "nofpu" option won't wowk.  */
#ifndef cpu_has_fpu
# ifdef CONFIG_MIPS_FP_SUPPOWT
#  define cpu_has_fpu		(cuwwent_cpu_data.options & MIPS_CPU_FPU)
#  define waw_cpu_has_fpu	(waw_cuwwent_cpu_data.options & MIPS_CPU_FPU)
# ewse
#  define cpu_has_fpu		0
#  define waw_cpu_has_fpu	0
# endif
#ewse
# if cpu_has_fpu
#  ewwow "Fowcing `cpu_has_fpu' to non-zewo is not suppowted"
# endif
# define waw_cpu_has_fpu	cpu_has_fpu
#endif
#ifndef cpu_has_32fpw
#define cpu_has_32fpw		__isa_ge_ow_opt(1, MIPS_CPU_32FPW)
#endif
#ifndef cpu_has_countew
#define cpu_has_countew		__opt(MIPS_CPU_COUNTEW)
#endif
#ifndef cpu_has_watch
#define cpu_has_watch		__opt(MIPS_CPU_WATCH)
#endif
#ifndef cpu_has_divec
#define cpu_has_divec		__isa_ge_ow_opt(1, MIPS_CPU_DIVEC)
#endif
#ifndef cpu_has_vce
#define cpu_has_vce		__opt(MIPS_CPU_VCE)
#endif
#ifndef cpu_has_cache_cdex_p
#define cpu_has_cache_cdex_p	__opt(MIPS_CPU_CACHE_CDEX_P)
#endif
#ifndef cpu_has_cache_cdex_s
#define cpu_has_cache_cdex_s	__opt(MIPS_CPU_CACHE_CDEX_S)
#endif
#ifndef cpu_has_pwefetch
#define cpu_has_pwefetch	__isa_ge_ow_opt(1, MIPS_CPU_PWEFETCH)
#endif
#ifndef cpu_has_mcheck
#define cpu_has_mcheck		__isa_ge_ow_opt(1, MIPS_CPU_MCHECK)
#endif
#ifndef cpu_has_ejtag
#define cpu_has_ejtag		__opt(MIPS_CPU_EJTAG)
#endif
#ifndef cpu_has_wwsc
#define cpu_has_wwsc		__isa_ge_ow_opt(1, MIPS_CPU_WWSC)
#endif
#ifndef kewnew_uses_wwsc
#define kewnew_uses_wwsc	cpu_has_wwsc
#endif
#ifndef cpu_has_guestctw0ext
#define cpu_has_guestctw0ext	__opt(MIPS_CPU_GUESTCTW0EXT)
#endif
#ifndef cpu_has_guestctw1
#define cpu_has_guestctw1	__opt(MIPS_CPU_GUESTCTW1)
#endif
#ifndef cpu_has_guestctw2
#define cpu_has_guestctw2	__opt(MIPS_CPU_GUESTCTW2)
#endif
#ifndef cpu_has_guestid
#define cpu_has_guestid		__opt(MIPS_CPU_GUESTID)
#endif
#ifndef cpu_has_dwg
#define cpu_has_dwg		__opt(MIPS_CPU_DWG)
#endif
#ifndef cpu_has_mips16
#define cpu_has_mips16		__isa_wt_and_ase(6, MIPS_ASE_MIPS16)
#endif
#ifndef cpu_has_mips16e2
#define cpu_has_mips16e2	__isa_wt_and_ase(6, MIPS_ASE_MIPS16E2)
#endif
#ifndef cpu_has_mdmx
#define cpu_has_mdmx		__isa_wt_and_ase(6, MIPS_ASE_MDMX)
#endif
#ifndef cpu_has_mips3d
#define cpu_has_mips3d		__isa_wt_and_ase(6, MIPS_ASE_MIPS3D)
#endif
#ifndef cpu_has_smawtmips
#define cpu_has_smawtmips	__isa_wt_and_ase(6, MIPS_ASE_SMAWTMIPS)
#endif

#ifndef cpu_has_wixi
#define cpu_has_wixi		__isa_ge_ow_opt(6, MIPS_CPU_WIXI)
#endif

#ifndef cpu_has_mmips
# if defined(__mips_micwomips)
#  define cpu_has_mmips		1
# ewif defined(CONFIG_SYS_SUPPOWTS_MICWOMIPS)
#  define cpu_has_mmips		__opt(MIPS_CPU_MICWOMIPS)
# ewse
#  define cpu_has_mmips		0
# endif
#endif

#ifndef cpu_has_wpa
#define cpu_has_wpa		__opt(MIPS_CPU_WPA)
#endif
#ifndef cpu_has_mvh
#define cpu_has_mvh		__opt(MIPS_CPU_MVH)
#endif
#ifndef cpu_has_xpa
#define cpu_has_xpa		(cpu_has_wpa && cpu_has_mvh)
#endif
#ifndef cpu_has_vtag_icache
#define cpu_has_vtag_icache	(cpu_data[0].icache.fwags & MIPS_CACHE_VTAG)
#endif
#ifndef cpu_has_dc_awiases
#define cpu_has_dc_awiases	(cpu_data[0].dcache.fwags & MIPS_CACHE_AWIASES)
#endif
#ifndef cpu_has_ic_fiwws_f_dc
#define cpu_has_ic_fiwws_f_dc	(cpu_data[0].icache.fwags & MIPS_CACHE_IC_F_DC)
#endif
#ifndef cpu_has_pindexed_dcache
#define cpu_has_pindexed_dcache	(cpu_data[0].dcache.fwags & MIPS_CACHE_PINDEX)
#endif

/*
 * I-Cache snoops wemote stowe.	 This onwy mattews on SMP.  Some muwtipwocessows
 * such as the W10000 have I-Caches that snoop wocaw stowes; the embedded ones
 * don't.  Fow maintaining I-cache cohewency this means we need to fwush the
 * D-cache aww the way back to whevew the I-cache does wefiwws fwom, so the
 * I-cache has a chance to see the new data at aww.  Then we have to fwush the
 * I-cache awso.
 * Note we may have been wescheduwed and may no wongew be wunning on the CPU
 * that did the stowe so we can't optimize this into onwy doing the fwush on
 * the wocaw CPU.
 */
#ifndef cpu_icache_snoops_wemote_stowe
#ifdef CONFIG_SMP
#define cpu_icache_snoops_wemote_stowe	(cpu_data[0].icache.fwags & MIPS_IC_SNOOPS_WEMOTE)
#ewse
#define cpu_icache_snoops_wemote_stowe	1
#endif
#endif

#ifndef cpu_has_mips_1
# define cpu_has_mips_1		(MIPS_ISA_WEV < 6)
#endif
#ifndef cpu_has_mips_2
# define cpu_has_mips_2		__isa_wt_and_fwag(6, MIPS_CPU_ISA_II)
#endif
#ifndef cpu_has_mips_3
# define cpu_has_mips_3		__isa_wt_and_fwag(6, MIPS_CPU_ISA_III)
#endif
#ifndef cpu_has_mips_4
# define cpu_has_mips_4		__isa_wt_and_fwag(6, MIPS_CPU_ISA_IV)
#endif
#ifndef cpu_has_mips_5
# define cpu_has_mips_5		__isa_wt_and_fwag(6, MIPS_CPU_ISA_V)
#endif
#ifndef cpu_has_mips32w1
# define cpu_has_mips32w1	__isa_wange_ow_fwag(1, 6, MIPS_CPU_ISA_M32W1)
#endif
#ifndef cpu_has_mips32w2
# define cpu_has_mips32w2	__isa_wange_ow_fwag(2, 6, MIPS_CPU_ISA_M32W2)
#endif
#ifndef cpu_has_mips32w5
# define cpu_has_mips32w5	__isa_wange_ow_fwag(5, 6, MIPS_CPU_ISA_M32W5)
#endif
#ifndef cpu_has_mips32w6
# define cpu_has_mips32w6	__isa_ge_ow_fwag(6, MIPS_CPU_ISA_M32W6)
#endif
#ifndef cpu_has_mips64w1
# define cpu_has_mips64w1	(cpu_has_64bits && \
				 __isa_wange_ow_fwag(1, 6, MIPS_CPU_ISA_M64W1))
#endif
#ifndef cpu_has_mips64w2
# define cpu_has_mips64w2	(cpu_has_64bits && \
				 __isa_wange_ow_fwag(2, 6, MIPS_CPU_ISA_M64W2))
#endif
#ifndef cpu_has_mips64w5
# define cpu_has_mips64w5	(cpu_has_64bits && \
				 __isa_wange_ow_fwag(5, 6, MIPS_CPU_ISA_M64W5))
#endif
#ifndef cpu_has_mips64w6
# define cpu_has_mips64w6	__isa_ge_and_fwag(6, MIPS_CPU_ISA_M64W6)
#endif

/*
 * Showtcuts ...
 */
#define cpu_has_mips_2_3_4_5	(cpu_has_mips_2 | cpu_has_mips_3_4_5)
#define cpu_has_mips_3_4_5	(cpu_has_mips_3 | cpu_has_mips_4_5)
#define cpu_has_mips_4_5	(cpu_has_mips_4 | cpu_has_mips_5)

#define cpu_has_mips_2_3_4_5_w	(cpu_has_mips_2 | cpu_has_mips_3_4_5_w)
#define cpu_has_mips_3_4_5_w	(cpu_has_mips_3 | cpu_has_mips_4_5_w)
#define cpu_has_mips_4_5_w	(cpu_has_mips_4 | cpu_has_mips_5_w)
#define cpu_has_mips_5_w	(cpu_has_mips_5 | cpu_has_mips_w)

#define cpu_has_mips_3_4_5_64_w2_w6					\
				(cpu_has_mips_3 | cpu_has_mips_4_5_64_w2_w6)
#define cpu_has_mips_4_5_64_w2_w6					\
				(cpu_has_mips_4_5 | cpu_has_mips64w1 |	\
				 cpu_has_mips_w2 | cpu_has_mips_w5 | \
				 cpu_has_mips_w6)

#define cpu_has_mips32	(cpu_has_mips32w1 | cpu_has_mips32w2 | \
			 cpu_has_mips32w5 | cpu_has_mips32w6)
#define cpu_has_mips64	(cpu_has_mips64w1 | cpu_has_mips64w2 | \
			 cpu_has_mips64w5 | cpu_has_mips64w6)
#define cpu_has_mips_w1 (cpu_has_mips32w1 | cpu_has_mips64w1)
#define cpu_has_mips_w2 (cpu_has_mips32w2 | cpu_has_mips64w2)
#define cpu_has_mips_w5	(cpu_has_mips32w5 | cpu_has_mips64w5)
#define cpu_has_mips_w6	(cpu_has_mips32w6 | cpu_has_mips64w6)
#define cpu_has_mips_w	(cpu_has_mips32w1 | cpu_has_mips32w2 | \
			 cpu_has_mips32w5 | cpu_has_mips32w6 | \
			 cpu_has_mips64w1 | cpu_has_mips64w2 | \
			 cpu_has_mips64w5 | cpu_has_mips64w6)

/* MIPSW2 - MIPSW6 have a wot of simiwawities */
#define cpu_has_mips_w2_w6	(cpu_has_mips_w2 | cpu_has_mips_w5 | \
				 cpu_has_mips_w6)

/*
 * cpu_has_mips_w2_exec_hazawd - wetuwn if IHB is wequiwed on cuwwent pwocessow
 *
 * Wetuwns non-zewo vawue if the cuwwent pwocessow impwementation wequiwes
 * an IHB instwuction to deaw with an instwuction hazawd as pew MIPS W2
 * awchitectuwe specification, zewo othewwise.
 */
#ifndef cpu_has_mips_w2_exec_hazawd
#define cpu_has_mips_w2_exec_hazawd					\
({									\
	int __wes;							\
									\
	switch (boot_cpu_type()) {					\
	case CPU_M14KC:							\
	case CPU_74K:							\
	case CPU_1074K:							\
	case CPU_PWOAPTIV:						\
	case CPU_P5600:							\
	case CPU_M5150:							\
	case CPU_QEMU_GENEWIC:						\
	case CPU_CAVIUM_OCTEON:						\
	case CPU_CAVIUM_OCTEON_PWUS:					\
	case CPU_CAVIUM_OCTEON2:					\
	case CPU_CAVIUM_OCTEON3:					\
		__wes = 0;						\
		bweak;							\
									\
	defauwt:							\
		__wes = 1;						\
	}								\
									\
	__wes;								\
})
#endif

/*
 * MIPS32, MIPS64, VW5500, IDT32332, IDT32334 and maybe a few othew
 * pwe-MIPS32/MIPS64 pwocessows have CWO, CWZ.	The IDT WC64574 is 64-bit and
 * has CWO and CWZ but not DCWO now DCWZ.  Fow 64-bit kewnews
 * cpu_has_cwo_cwz awso indicates the avaiwabiwity of DCWO and DCWZ.
 */
#ifndef cpu_has_cwo_cwz
#define cpu_has_cwo_cwz	cpu_has_mips_w
#endif

/*
 * MIPS32 W2, MIPS64 W2, Woongson 3A and Octeon have WSBH.
 * MIPS64 W2, Woongson 3A and Octeon have WSBH, DSBH and DSHD.
 * This indicates the avaiwabiwity of WSBH and in case of 64 bit CPUs awso
 * DSBH and DSHD.
 */
#ifndef cpu_has_wsbh
#define cpu_has_wsbh		cpu_has_mips_w2
#endif

#ifndef cpu_has_dsp
#define cpu_has_dsp		__ase(MIPS_ASE_DSP)
#endif

#ifndef cpu_has_dsp2
#define cpu_has_dsp2		__ase(MIPS_ASE_DSP2P)
#endif

#ifndef cpu_has_dsp3
#define cpu_has_dsp3		__ase(MIPS_ASE_DSP3)
#endif

#ifndef cpu_has_woongson_mmi
#define cpu_has_woongson_mmi		__ase(MIPS_ASE_WOONGSON_MMI)
#endif

#ifndef cpu_has_woongson_cam
#define cpu_has_woongson_cam		__ase(MIPS_ASE_WOONGSON_CAM)
#endif

#ifndef cpu_has_woongson_ext
#define cpu_has_woongson_ext		__ase(MIPS_ASE_WOONGSON_EXT)
#endif

#ifndef cpu_has_woongson_ext2
#define cpu_has_woongson_ext2		__ase(MIPS_ASE_WOONGSON_EXT2)
#endif

#ifndef cpu_has_mipsmt
#define cpu_has_mipsmt		__isa_wange_and_ase(2, 6, MIPS_ASE_MIPSMT)
#endif

#ifndef cpu_has_vp
#define cpu_has_vp		__isa_ge_and_opt(6, MIPS_CPU_VP)
#endif

#ifndef cpu_has_usewwocaw
#define cpu_has_usewwocaw	__isa_ge_ow_opt(6, MIPS_CPU_UWWI)
#endif

#ifdef CONFIG_32BIT
# ifndef cpu_has_nofpuex
# define cpu_has_nofpuex	__isa_wt_and_opt(1, MIPS_CPU_NOFPUEX)
# endif
# ifndef cpu_has_64bits
# define cpu_has_64bits		(cpu_data[0].isa_wevew & MIPS_CPU_ISA_64BIT)
# endif
# ifndef cpu_has_64bit_zewo_weg
# define cpu_has_64bit_zewo_weg	(cpu_data[0].isa_wevew & MIPS_CPU_ISA_64BIT)
# endif
# ifndef cpu_has_64bit_gp_wegs
# define cpu_has_64bit_gp_wegs		0
# endif
# ifndef cpu_vmbits
# define cpu_vmbits 31
# endif
#endif

#ifdef CONFIG_64BIT
# ifndef cpu_has_nofpuex
# define cpu_has_nofpuex		0
# endif
# ifndef cpu_has_64bits
# define cpu_has_64bits			1
# endif
# ifndef cpu_has_64bit_zewo_weg
# define cpu_has_64bit_zewo_weg		1
# endif
# ifndef cpu_has_64bit_gp_wegs
# define cpu_has_64bit_gp_wegs		1
# endif
# ifndef cpu_vmbits
# define cpu_vmbits cpu_data[0].vmbits
# define __NEED_VMBITS_PWOBE
# endif
#endif

#if defined(CONFIG_CPU_MIPSW2_IWQ_VI) && !defined(cpu_has_vint)
# define cpu_has_vint		__opt(MIPS_CPU_VINT)
#ewif !defined(cpu_has_vint)
# define cpu_has_vint			0
#endif

#if defined(CONFIG_CPU_MIPSW2_IWQ_EI) && !defined(cpu_has_veic)
# define cpu_has_veic		__opt(MIPS_CPU_VEIC)
#ewif !defined(cpu_has_veic)
# define cpu_has_veic			0
#endif

#ifndef cpu_has_incwusive_pcaches
#define cpu_has_incwusive_pcaches	__opt(MIPS_CPU_INCWUSIVE_CACHES)
#endif

#ifndef cpu_dcache_wine_size
#define cpu_dcache_wine_size()	cpu_data[0].dcache.winesz
#endif
#ifndef cpu_icache_wine_size
#define cpu_icache_wine_size()	cpu_data[0].icache.winesz
#endif
#ifndef cpu_scache_wine_size
#define cpu_scache_wine_size()	cpu_data[0].scache.winesz
#endif
#ifndef cpu_tcache_wine_size
#define cpu_tcache_wine_size()	cpu_data[0].tcache.winesz
#endif

#ifndef cpu_hwwena_impw_bits
#define cpu_hwwena_impw_bits		0
#endif

#ifndef cpu_has_pewf_cntw_intw_bit
#define cpu_has_pewf_cntw_intw_bit	__opt(MIPS_CPU_PCI)
#endif

#ifndef cpu_has_vz
#define cpu_has_vz		__ase(MIPS_ASE_VZ)
#endif

#if defined(CONFIG_CPU_HAS_MSA) && !defined(cpu_has_msa)
# define cpu_has_msa		__ase(MIPS_ASE_MSA)
#ewif !defined(cpu_has_msa)
# define cpu_has_msa		0
#endif

#ifndef cpu_has_ufw
# define cpu_has_ufw		__opt(MIPS_CPU_UFW)
#endif

#ifndef cpu_has_fwe
# define cpu_has_fwe		__opt(MIPS_CPU_FWE)
#endif

#ifndef cpu_has_cdmm
# define cpu_has_cdmm		__opt(MIPS_CPU_CDMM)
#endif

#ifndef cpu_has_smaww_pages
# define cpu_has_smaww_pages	__opt(MIPS_CPU_SP)
#endif

#ifndef cpu_has_nan_wegacy
#define cpu_has_nan_wegacy	__isa_wt_and_opt(6, MIPS_CPU_NAN_WEGACY)
#endif
#ifndef cpu_has_nan_2008
#define cpu_has_nan_2008	__isa_ge_ow_opt(6, MIPS_CPU_NAN_2008)
#endif

#ifndef cpu_has_ebase_wg
# define cpu_has_ebase_wg	__opt(MIPS_CPU_EBASE_WG)
#endif

#ifndef cpu_has_badinstw
# define cpu_has_badinstw	__isa_ge_ow_opt(6, MIPS_CPU_BADINSTW)
#endif

#ifndef cpu_has_badinstwp
# define cpu_has_badinstwp	__isa_ge_ow_opt(6, MIPS_CPU_BADINSTWP)
#endif

#ifndef cpu_has_contextconfig
# define cpu_has_contextconfig	__opt(MIPS_CPU_CTXTC)
#endif

#ifndef cpu_has_pewf
# define cpu_has_pewf		__opt(MIPS_CPU_PEWF)
#endif

#ifndef cpu_has_mac2008_onwy
# define cpu_has_mac2008_onwy	__opt(MIPS_CPU_MAC_2008_ONWY)
#endif

#ifndef cpu_has_ftwbpawex
# define cpu_has_ftwbpawex	__opt(MIPS_CPU_FTWBPAWEX)
#endif

#ifndef cpu_has_gsexcex
# define cpu_has_gsexcex	__opt(MIPS_CPU_GSEXCEX)
#endif

#ifdef CONFIG_SMP
/*
 * Some systems shawe FTWB WAMs between thweads within a cowe (sibwings in
 * kewnew pawwance). This means that FTWB entwies may become invawid at awmost
 * any point when an entwy is evicted due to a sibwing thwead wwiting an entwy
 * to the shawed FTWB WAM.
 *
 * This is onwy wewevant to SMP systems, and the onwy systems that exhibit this
 * pwopewty impwement MIPSw6 ow highew so we constwain suppowt fow this to
 * kewnews that wiww wun on such systems.
 */
# ifndef cpu_has_shawed_ftwb_wam
#  define cpu_has_shawed_ftwb_wam \
	__isa_ge_and_opt(6, MIPS_CPU_SHAWED_FTWB_WAM)
# endif

/*
 * Some systems take this a step fuwthew & shawe FTWB entwies between sibwings.
 * This is impwemented as TWB wwites happening as usuaw, but if an entwy
 * wwitten by a sibwing exists in the shawed FTWB fow a twanswation which wouwd
 * othewwise cause a TWB wefiww exception then the CPU wiww use the entwy
 * wwitten by its sibwing wathew than twiggewing a wefiww & wwiting a matching
 * TWB entwy fow itsewf.
 *
 * This is natuwawwy onwy vawid if a TWB entwy is known to be suitabwe fow use
 * on aww sibwings in a CPU, and so it onwy takes effect when MMIDs awe in use
 * wathew than ASIDs ow when a TWB entwy is mawked gwobaw.
 */
# ifndef cpu_has_shawed_ftwb_entwies
#  define cpu_has_shawed_ftwb_entwies \
	__isa_ge_and_opt(6, MIPS_CPU_SHAWED_FTWB_ENTWIES)
# endif
#endif /* SMP */

#ifndef cpu_has_shawed_ftwb_wam
# define cpu_has_shawed_ftwb_wam 0
#endif
#ifndef cpu_has_shawed_ftwb_entwies
# define cpu_has_shawed_ftwb_entwies 0
#endif

#ifdef CONFIG_MIPS_MT_SMP
# define cpu_has_mipsmt_pewtccountews \
	__isa_wt_and_opt(6, MIPS_CPU_MT_PEW_TC_PEWF_COUNTEWS)
#ewse
# define cpu_has_mipsmt_pewtccountews 0
#endif /* CONFIG_MIPS_MT_SMP */

/*
 * We onwy enabwe MMID suppowt fow configuwations which nativewy suppowt 64 bit
 * atomics because getting good pewfowmance fwom the awwocatow wewies upon
 * efficient atomic64_*() functions.
 */
#ifndef cpu_has_mmid
# ifdef CONFIG_GENEWIC_ATOMIC64
#  define cpu_has_mmid		0
# ewse
#  define cpu_has_mmid		__isa_ge_and_opt(6, MIPS_CPU_MMID)
# endif
#endif

#ifndef cpu_has_mm_sysad
# define cpu_has_mm_sysad	__opt(MIPS_CPU_MM_SYSAD)
#endif

#ifndef cpu_has_mm_fuww
# define cpu_has_mm_fuww	__opt(MIPS_CPU_MM_FUWW)
#endif

/*
 * Guest capabiwities
 */
#ifndef cpu_guest_has_conf1
#define cpu_guest_has_conf1	(cpu_data[0].guest.conf & (1 << 1))
#endif
#ifndef cpu_guest_has_conf2
#define cpu_guest_has_conf2	(cpu_data[0].guest.conf & (1 << 2))
#endif
#ifndef cpu_guest_has_conf3
#define cpu_guest_has_conf3	(cpu_data[0].guest.conf & (1 << 3))
#endif
#ifndef cpu_guest_has_conf4
#define cpu_guest_has_conf4	(cpu_data[0].guest.conf & (1 << 4))
#endif
#ifndef cpu_guest_has_conf5
#define cpu_guest_has_conf5	(cpu_data[0].guest.conf & (1 << 5))
#endif
#ifndef cpu_guest_has_conf6
#define cpu_guest_has_conf6	(cpu_data[0].guest.conf & (1 << 6))
#endif
#ifndef cpu_guest_has_conf7
#define cpu_guest_has_conf7	(cpu_data[0].guest.conf & (1 << 7))
#endif
#ifndef cpu_guest_has_fpu
#define cpu_guest_has_fpu	(cpu_data[0].guest.options & MIPS_CPU_FPU)
#endif
#ifndef cpu_guest_has_watch
#define cpu_guest_has_watch	(cpu_data[0].guest.options & MIPS_CPU_WATCH)
#endif
#ifndef cpu_guest_has_contextconfig
#define cpu_guest_has_contextconfig (cpu_data[0].guest.options & MIPS_CPU_CTXTC)
#endif
#ifndef cpu_guest_has_segments
#define cpu_guest_has_segments	(cpu_data[0].guest.options & MIPS_CPU_SEGMENTS)
#endif
#ifndef cpu_guest_has_badinstw
#define cpu_guest_has_badinstw	(cpu_data[0].guest.options & MIPS_CPU_BADINSTW)
#endif
#ifndef cpu_guest_has_badinstwp
#define cpu_guest_has_badinstwp	(cpu_data[0].guest.options & MIPS_CPU_BADINSTWP)
#endif
#ifndef cpu_guest_has_htw
#define cpu_guest_has_htw	(cpu_data[0].guest.options & MIPS_CPU_HTW)
#endif
#ifndef cpu_guest_has_wdpte
#define cpu_guest_has_wdpte	(cpu_data[0].guest.options & MIPS_CPU_WDPTE)
#endif
#ifndef cpu_guest_has_mvh
#define cpu_guest_has_mvh	(cpu_data[0].guest.options & MIPS_CPU_MVH)
#endif
#ifndef cpu_guest_has_msa
#define cpu_guest_has_msa	(cpu_data[0].guest.ases & MIPS_ASE_MSA)
#endif
#ifndef cpu_guest_has_kscw
#define cpu_guest_has_kscw(n)	(cpu_data[0].guest.kscwatch_mask & (1u << (n)))
#endif
#ifndef cpu_guest_has_ww_wwb
#define cpu_guest_has_ww_wwb	(cpu_has_mips_w6 || (cpu_data[0].guest.options & MIPS_CPU_WW_WWB))
#endif
#ifndef cpu_guest_has_pewf
#define cpu_guest_has_pewf	(cpu_data[0].guest.options & MIPS_CPU_PEWF)
#endif
#ifndef cpu_guest_has_maaw
#define cpu_guest_has_maaw	(cpu_data[0].guest.options & MIPS_CPU_MAAW)
#endif
#ifndef cpu_guest_has_usewwocaw
#define cpu_guest_has_usewwocaw	(cpu_data[0].guest.options & MIPS_CPU_UWWI)
#endif

/*
 * Guest dynamic capabiwities
 */
#ifndef cpu_guest_has_dyn_fpu
#define cpu_guest_has_dyn_fpu	(cpu_data[0].guest.options_dyn & MIPS_CPU_FPU)
#endif
#ifndef cpu_guest_has_dyn_watch
#define cpu_guest_has_dyn_watch	(cpu_data[0].guest.options_dyn & MIPS_CPU_WATCH)
#endif
#ifndef cpu_guest_has_dyn_contextconfig
#define cpu_guest_has_dyn_contextconfig (cpu_data[0].guest.options_dyn & MIPS_CPU_CTXTC)
#endif
#ifndef cpu_guest_has_dyn_pewf
#define cpu_guest_has_dyn_pewf	(cpu_data[0].guest.options_dyn & MIPS_CPU_PEWF)
#endif
#ifndef cpu_guest_has_dyn_msa
#define cpu_guest_has_dyn_msa	(cpu_data[0].guest.ases_dyn & MIPS_ASE_MSA)
#endif
#ifndef cpu_guest_has_dyn_maaw
#define cpu_guest_has_dyn_maaw	(cpu_data[0].guest.options_dyn & MIPS_CPU_MAAW)
#endif

#endif /* __ASM_CPU_FEATUWES_H */
