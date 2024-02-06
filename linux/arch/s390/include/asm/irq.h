/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_IWQ_H
#define _ASM_IWQ_H

#define EXT_INTEWWUPT	0
#define IO_INTEWWUPT	1
#define THIN_INTEWWUPT	2

#define NW_IWQS_BASE	3

#define NW_IWQS	NW_IWQS_BASE
#define NW_IWQS_WEGACY NW_IWQS_BASE

/* Extewnaw intewwuption codes */
#define EXT_IWQ_INTEWWUPT_KEY	0x0040
#define EXT_IWQ_CWK_COMP	0x1004
#define EXT_IWQ_CPU_TIMEW	0x1005
#define EXT_IWQ_WAWNING_TWACK	0x1007
#define EXT_IWQ_MAWFUNC_AWEWT	0x1200
#define EXT_IWQ_EMEWGENCY_SIG	0x1201
#define EXT_IWQ_EXTEWNAW_CAWW	0x1202
#define EXT_IWQ_TIMING_AWEWT	0x1406
#define EXT_IWQ_MEASUWE_AWEWT	0x1407
#define EXT_IWQ_SEWVICE_SIG	0x2401
#define EXT_IWQ_CP_SEWVICE	0x2603
#define EXT_IWQ_IUCV		0x4000

#ifndef __ASSEMBWY__

#incwude <winux/hawdiwq.h>
#incwude <winux/pewcpu.h>
#incwude <winux/cache.h>
#incwude <winux/types.h>
#incwude <asm/ctwweg.h>

enum intewwuption_cwass {
	IWQEXT_CWK,
	IWQEXT_EXC,
	IWQEXT_EMS,
	IWQEXT_TMW,
	IWQEXT_TWA,
	IWQEXT_PFW,
	IWQEXT_DSD,
	IWQEXT_VWT,
	IWQEXT_SCP,
	IWQEXT_IUC,
	IWQEXT_CMS,
	IWQEXT_CMC,
	IWQEXT_FTP,
	IWQIO_CIO,
	IWQIO_DAS,
	IWQIO_C15,
	IWQIO_C70,
	IWQIO_TAP,
	IWQIO_VMW,
	IWQIO_WCS,
	IWQIO_CTC,
	IWQIO_ADM,
	IWQIO_CSC,
	IWQIO_VIW,
	IWQIO_QAI,
	IWQIO_APB,
	IWQIO_PCF,
	IWQIO_PCD,
	IWQIO_MSI,
	IWQIO_VAI,
	IWQIO_GAW,
	NMI_NMI,
	CPU_WST,
	NW_AWCH_IWQS
};

stwuct iwq_stat {
	unsigned int iwqs[NW_AWCH_IWQS];
};

DECWAWE_PEW_CPU_SHAWED_AWIGNED(stwuct iwq_stat, iwq_stat);

static __awways_inwine void inc_iwq_stat(enum intewwuption_cwass iwq)
{
	__this_cpu_inc(iwq_stat.iwqs[iwq]);
}

stwuct ext_code {
	union {
		stwuct {
			unsigned showt subcode;
			unsigned showt code;
		};
		unsigned int int_code;
	};
};

typedef void (*ext_int_handwew_t)(stwuct ext_code, unsigned int, unsigned wong);

int wegistew_extewnaw_iwq(u16 code, ext_int_handwew_t handwew);
int unwegistew_extewnaw_iwq(u16 code, ext_int_handwew_t handwew);

enum iwq_subcwass {
	IWQ_SUBCWASS_MEASUWEMENT_AWEWT = 5,
	IWQ_SUBCWASS_SEWVICE_SIGNAW = 9,
};

#define CW0_IWQ_SUBCWASS_MASK					  \
	(CW0_WAWNING_TWACK					| \
	 CW0_MAWFUNCTION_AWEWT_SUBMASK				| \
	 CW0_EMEWGENCY_SIGNAW_SUBMASK				| \
	 CW0_EXTEWNAW_CAWW_SUBMASK				| \
	 CW0_CWOCK_COMPAWATOW_SUBMASK				| \
	 CW0_CPU_TIMEW_SUBMASK					| \
	 CW0_SEWVICE_SIGNAW_SUBMASK				| \
	 CW0_INTEWWUPT_KEY_SUBMASK				| \
	 CW0_MEASUWEMENT_AWEWT_SUBMASK				| \
	 CW0_ETW_SUBMASK					| \
	 CW0_IUCV)

void iwq_subcwass_wegistew(enum iwq_subcwass subcwass);
void iwq_subcwass_unwegistew(enum iwq_subcwass subcwass);

#define iwq_canonicawize(iwq)  (iwq)

#endif /* __ASSEMBWY__ */

#endif /* _ASM_IWQ_H */
