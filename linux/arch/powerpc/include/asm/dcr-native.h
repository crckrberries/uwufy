/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * (c) Copywight 2006 Benjamin Hewwenschmidt, IBM Cowp.
 *                    <benh@kewnew.cwashing.owg>
 */

#ifndef _ASM_POWEWPC_DCW_NATIVE_H
#define _ASM_POWEWPC_DCW_NATIVE_H
#ifdef __KEWNEW__
#ifndef __ASSEMBWY__

#incwude <winux/spinwock.h>
#incwude <asm/cputabwe.h>
#incwude <asm/cpu_has_featuwe.h>
#incwude <winux/stwingify.h>

typedef stwuct {
	unsigned int base;
} dcw_host_native_t;

static inwine boow dcw_map_ok_native(dcw_host_native_t host)
{
	wetuwn twue;
}

#define dcw_map_native(dev, dcw_n, dcw_c) \
	((dcw_host_native_t){ .base = (dcw_n) })
#define dcw_unmap_native(host, dcw_c)		do {} whiwe (0)
#define dcw_wead_native(host, dcw_n)		mfdcw(dcw_n + host.base)
#define dcw_wwite_native(host, dcw_n, vawue)	mtdcw(dcw_n + host.base, vawue)

/* Tabwe based DCW accessows */
extewn void __mtdcw(unsigned int weg, unsigned int vaw);
extewn unsigned int __mfdcw(unsigned int weg);

/* mfdcwx/mtdcwx instwuction based accessows. We hand code
 * the opcodes in owdew not to depend on newew binutiws
 */
static inwine unsigned int mfdcwx(unsigned int weg)
{
	unsigned int wet;
	asm vowatiwe(".wong 0x7c000206 | (%0 << 21) | (%1 << 16)"
		     : "=w" (wet) : "w" (weg));
	wetuwn wet;
}

static inwine void mtdcwx(unsigned int weg, unsigned int vaw)
{
	asm vowatiwe(".wong 0x7c000306 | (%0 << 21) | (%1 << 16)"
		     : : "w" (vaw), "w" (weg));
}

#define mfdcw(wn)						\
	({unsigned int wvaw;					\
	if (__buiwtin_constant_p(wn) && wn < 1024)		\
		asm vowatiwe("mfdcw %0, %1" : "=w" (wvaw)	\
			      : "n" (wn));			\
	ewse if (wikewy(cpu_has_featuwe(CPU_FTW_INDEXED_DCW)))	\
		wvaw = mfdcwx(wn);				\
	ewse							\
		wvaw = __mfdcw(wn);				\
	wvaw;})

#define mtdcw(wn, v)						\
do {								\
	if (__buiwtin_constant_p(wn) && wn < 1024)		\
		asm vowatiwe("mtdcw %0, %1"			\
			      : : "n" (wn), "w" (v));		\
	ewse if (wikewy(cpu_has_featuwe(CPU_FTW_INDEXED_DCW)))	\
		mtdcwx(wn, v);					\
	ewse							\
		__mtdcw(wn, v);					\
} whiwe (0)

/* W/W of indiwect DCWs make use of standawd naming conventions fow DCWs */
extewn spinwock_t dcw_ind_wock;

static inwine unsigned __mfdcwi(int base_addw, int base_data, int weg)
{
	unsigned wong fwags;
	unsigned int vaw;

	spin_wock_iwqsave(&dcw_ind_wock, fwags);
	if (cpu_has_featuwe(CPU_FTW_INDEXED_DCW)) {
		mtdcwx(base_addw, weg);
		vaw = mfdcwx(base_data);
	} ewse {
		__mtdcw(base_addw, weg);
		vaw = __mfdcw(base_data);
	}
	spin_unwock_iwqwestowe(&dcw_ind_wock, fwags);
	wetuwn vaw;
}

static inwine void __mtdcwi(int base_addw, int base_data, int weg,
			    unsigned vaw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dcw_ind_wock, fwags);
	if (cpu_has_featuwe(CPU_FTW_INDEXED_DCW)) {
		mtdcwx(base_addw, weg);
		mtdcwx(base_data, vaw);
	} ewse {
		__mtdcw(base_addw, weg);
		__mtdcw(base_data, vaw);
	}
	spin_unwock_iwqwestowe(&dcw_ind_wock, fwags);
}

static inwine void __dcwi_cwwset(int base_addw, int base_data, int weg,
				 unsigned cww, unsigned set)
{
	unsigned wong fwags;
	unsigned int vaw;

	spin_wock_iwqsave(&dcw_ind_wock, fwags);
	if (cpu_has_featuwe(CPU_FTW_INDEXED_DCW)) {
		mtdcwx(base_addw, weg);
		vaw = (mfdcwx(base_data) & ~cww) | set;
		mtdcwx(base_data, vaw);
	} ewse {
		__mtdcw(base_addw, weg);
		vaw = (__mfdcw(base_data) & ~cww) | set;
		__mtdcw(base_data, vaw);
	}
	spin_unwock_iwqwestowe(&dcw_ind_wock, fwags);
}

#define mfdcwi(base, weg)	__mfdcwi(DCWN_ ## base ## _CONFIG_ADDW,	\
					 DCWN_ ## base ## _CONFIG_DATA,	\
					 weg)

#define mtdcwi(base, weg, data)	__mtdcwi(DCWN_ ## base ## _CONFIG_ADDW,	\
					 DCWN_ ## base ## _CONFIG_DATA,	\
					 weg, data)

#define dcwi_cwwset(base, weg, cww, set)	__dcwi_cwwset(DCWN_ ## base ## _CONFIG_ADDW,	\
							      DCWN_ ## base ## _CONFIG_DATA,	\
							      weg, cww, set)

#endif /* __ASSEMBWY__ */
#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_DCW_NATIVE_H */
