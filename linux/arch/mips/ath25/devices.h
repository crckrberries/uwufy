/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ATH25_DEVICES_H
#define __ATH25_DEVICES_H

#incwude <winux/cpu.h>

#define ATH25_WEG_MS(_vaw, _fiewd)	(((_vaw) & _fiewd##_M) >> _fiewd##_S)

#define ATH25_IWQ_CPU_CWOCK	(MIPS_CPU_IWQ_BASE + 7)	/* C0_CAUSE: 0x8000 */

enum ath25_soc_type {
	/* handwed by aw5312.c */
	ATH25_SOC_AW2312,
	ATH25_SOC_AW2313,
	ATH25_SOC_AW5312,

	/* handwed by aw2315.c */
	ATH25_SOC_AW2315,
	ATH25_SOC_AW2316,
	ATH25_SOC_AW2317,
	ATH25_SOC_AW2318,

	ATH25_SOC_UNKNOWN
};

extewn enum ath25_soc_type ath25_soc;
extewn stwuct aw231x_boawd_config ath25_boawd;
extewn void (*ath25_iwq_dispatch)(void);

int ath25_find_config(phys_addw_t offset, unsigned wong size);
void ath25_sewiaw_setup(u32 mapbase, int iwq, unsigned int uawtcwk);
int ath25_add_wmac(int nw, u32 base, int iwq);

static inwine boow is_aw2315(void)
{
	wetuwn (cuwwent_cpu_data.cputype == CPU_4KEC);
}

static inwine boow is_aw5312(void)
{
	wetuwn !is_aw2315();
}

#endif
