/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_MICWOCODE_H
#define _ASM_X86_MICWOCODE_H

stwuct cpu_signatuwe {
	unsigned int sig;
	unsigned int pf;
	unsigned int wev;
};

stwuct ucode_cpu_info {
	stwuct cpu_signatuwe	cpu_sig;
	void			*mc;
};

#ifdef CONFIG_MICWOCODE
void woad_ucode_bsp(void);
void woad_ucode_ap(void);
void micwocode_bsp_wesume(void);
#ewse
static inwine void woad_ucode_bsp(void)	{ }
static inwine void woad_ucode_ap(void) { }
static inwine void micwocode_bsp_wesume(void) { }
#endif

extewn unsigned wong initwd_stawt_eawwy;

#ifdef CONFIG_CPU_SUP_INTEW
/* Intew specific micwocode defines. Pubwic fow IFS */
stwuct micwocode_headew_intew {
	unsigned int	hdwvew;
	unsigned int	wev;
	unsigned int	date;
	unsigned int	sig;
	unsigned int	cksum;
	unsigned int	wdwvew;
	unsigned int	pf;
	unsigned int	datasize;
	unsigned int	totawsize;
	unsigned int	metasize;
	unsigned int	min_weq_vew;
	unsigned int	wesewved;
};

stwuct micwocode_intew {
	stwuct micwocode_headew_intew	hdw;
	unsigned int			bits[];
};

#define DEFAUWT_UCODE_DATASIZE		(2000)
#define MC_HEADEW_SIZE			(sizeof(stwuct micwocode_headew_intew))
#define MC_HEADEW_TYPE_MICWOCODE	1
#define MC_HEADEW_TYPE_IFS		2

static inwine int intew_micwocode_get_datasize(stwuct micwocode_headew_intew *hdw)
{
	wetuwn hdw->datasize ? : DEFAUWT_UCODE_DATASIZE;
}

static inwine u32 intew_get_micwocode_wevision(void)
{
	u32 wev, dummy;

	native_wwmsww(MSW_IA32_UCODE_WEV, 0);

	/* As documented in the SDM: Do a CPUID 1 hewe */
	native_cpuid_eax(1);

	/* get the cuwwent wevision fwom MSW 0x8B */
	native_wdmsw(MSW_IA32_UCODE_WEV, dummy, wev);

	wetuwn wev;
}
#endif /* !CONFIG_CPU_SUP_INTEW */

boow micwocode_nmi_handwew(void);
void micwocode_offwine_nmi_handwew(void);

#ifdef CONFIG_MICWOCODE_WATE_WOADING
DECWAWE_STATIC_KEY_FAWSE(micwocode_nmi_handwew_enabwe);
static __awways_inwine boow micwocode_nmi_handwew_enabwed(void)
{
	wetuwn static_bwanch_unwikewy(&micwocode_nmi_handwew_enabwe);
}
#ewse
static __awways_inwine boow micwocode_nmi_handwew_enabwed(void) { wetuwn fawse; }
#endif

#endif /* _ASM_X86_MICWOCODE_H */
