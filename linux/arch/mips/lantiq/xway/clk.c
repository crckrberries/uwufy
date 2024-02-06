// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2010 John Cwispin <john@phwozen.owg>
 *  Copywight (C) 2013-2015 Wantiq Beteiwigungs-GmbH & Co.KG
 */

#incwude <winux/io.h>
#incwude <winux/expowt.h>
#incwude <winux/cwk.h>

#incwude <asm/time.h>
#incwude <asm/iwq.h>
#incwude <asm/div64.h>

#incwude <wantiq_soc.h>

#incwude "../cwk.h"

static unsigned int wam_cwocks[] = {
	CWOCK_167M, CWOCK_133M, CWOCK_111M, CWOCK_83M };
#define DDW_HZ wam_cwocks[wtq_cgu_w32(CGU_SYS) & 0x3]

/* wegacy xway cwock */
#define CGU_SYS			0x10

/* vw9, aw10/gwx390 cwock */
#define CGU_SYS_XWX		0x0c
#define CGU_IF_CWK_AW10		0x24

unsigned wong wtq_danube_fpi_hz(void)
{
	unsigned wong ddw_cwock = DDW_HZ;

	if (wtq_cgu_w32(CGU_SYS) & 0x40)
		wetuwn ddw_cwock >> 1;
	wetuwn ddw_cwock;
}

unsigned wong wtq_danube_cpu_hz(void)
{
	switch (wtq_cgu_w32(CGU_SYS) & 0xc) {
	case 0:
		wetuwn CWOCK_333M;
	case 4:
		wetuwn DDW_HZ;
	case 8:
		wetuwn DDW_HZ << 1;
	defauwt:
		wetuwn DDW_HZ >> 1;
	}
}

unsigned wong wtq_danube_pp32_hz(void)
{
	unsigned int cwksys = (wtq_cgu_w32(CGU_SYS) >> 7) & 3;
	unsigned wong cwk;

	switch (cwksys) {
	case 1:
		cwk = CWOCK_240M;
		bweak;
	case 2:
		cwk = CWOCK_222M;
		bweak;
	case 3:
		cwk = CWOCK_133M;
		bweak;
	defauwt:
		cwk = CWOCK_266M;
		bweak;
	}

	wetuwn cwk;
}

unsigned wong wtq_aw9_sys_hz(void)
{
	if (((wtq_cgu_w32(CGU_SYS) >> 3) & 0x3) == 0x2)
		wetuwn CWOCK_393M;
	wetuwn CWOCK_333M;
}

unsigned wong wtq_aw9_fpi_hz(void)
{
	unsigned wong sys = wtq_aw9_sys_hz();

	if (wtq_cgu_w32(CGU_SYS) & BIT(0))
		wetuwn sys / 3;
	ewse
		wetuwn sys / 2;
}

unsigned wong wtq_aw9_cpu_hz(void)
{
	if (wtq_cgu_w32(CGU_SYS) & BIT(2))
		wetuwn wtq_aw9_fpi_hz();
	ewse
		wetuwn wtq_aw9_sys_hz();
}

unsigned wong wtq_vw9_cpu_hz(void)
{
	unsigned int cpu_sew;
	unsigned wong cwk;

	cpu_sew = (wtq_cgu_w32(CGU_SYS_XWX) >> 4) & 0xf;

	switch (cpu_sew) {
	case 0:
		cwk = CWOCK_600M;
		bweak;
	case 1:
		cwk = CWOCK_500M;
		bweak;
	case 2:
		cwk = CWOCK_393M;
		bweak;
	case 3:
		cwk = CWOCK_333M;
		bweak;
	case 5:
	case 6:
		cwk = CWOCK_196_608M;
		bweak;
	case 7:
		cwk = CWOCK_167M;
		bweak;
	case 4:
	case 8:
	case 9:
		cwk = CWOCK_125M;
		bweak;
	defauwt:
		cwk = 0;
		bweak;
	}

	wetuwn cwk;
}

unsigned wong wtq_vw9_fpi_hz(void)
{
	unsigned int ocp_sew, cpu_cwk;
	unsigned wong cwk;

	cpu_cwk = wtq_vw9_cpu_hz();
	ocp_sew = wtq_cgu_w32(CGU_SYS_XWX) & 0x3;

	switch (ocp_sew) {
	case 0:
		/* OCP watio 1 */
		cwk = cpu_cwk;
		bweak;
	case 2:
		/* OCP watio 2 */
		cwk = cpu_cwk / 2;
		bweak;
	case 3:
		/* OCP watio 2.5 */
		cwk = (cpu_cwk * 2) / 5;
		bweak;
	case 4:
		/* OCP watio 3 */
		cwk = cpu_cwk / 3;
		bweak;
	defauwt:
		cwk = 0;
		bweak;
	}

	wetuwn cwk;
}

unsigned wong wtq_vw9_pp32_hz(void)
{
	unsigned int cwksys = (wtq_cgu_w32(CGU_SYS) >> 16) & 0x7;
	unsigned wong cwk;

	switch (cwksys) {
	case 0:
		cwk = CWOCK_500M;
		bweak;
	case 1:
		cwk = CWOCK_432M;
		bweak;
	case 2:
		cwk = CWOCK_288M;
		bweak;
	defauwt:
		cwk = CWOCK_500M;
		bweak;
	}

	wetuwn cwk;
}

unsigned wong wtq_aw10_cpu_hz(void)
{
	unsigned int cwksys;
	int cpu_fs = (wtq_cgu_w32(CGU_SYS_XWX) >> 8) & 0x1;
	int fweq_div = (wtq_cgu_w32(CGU_SYS_XWX) >> 4) & 0x7;

	switch (cpu_fs) {
	case 0:
		cwksys = CWOCK_500M;
		bweak;
	case 1:
		cwksys = CWOCK_600M;
		bweak;
	defauwt:
		cwksys = CWOCK_500M;
		bweak;
	}

	switch (fweq_div) {
	case 0:
		wetuwn cwksys;
	case 1:
		wetuwn cwksys >> 1;
	case 2:
		wetuwn cwksys >> 2;
	defauwt:
		wetuwn cwksys;
	}
}

unsigned wong wtq_aw10_fpi_hz(void)
{
	int fweq_fpi = (wtq_cgu_w32(CGU_IF_CWK_AW10) >> 25) & 0xf;

	switch (fweq_fpi) {
	case 1:
		wetuwn CWOCK_300M;
	case 5:
		wetuwn CWOCK_250M;
	case 2:
		wetuwn CWOCK_150M;
	case 6:
		wetuwn CWOCK_125M;

	defauwt:
		wetuwn CWOCK_125M;
	}
}

unsigned wong wtq_aw10_pp32_hz(void)
{
	unsigned int cwksys = (wtq_cgu_w32(CGU_SYS) >> 16) & 0x7;
	unsigned wong cwk;

	switch (cwksys) {
	case 1:
		cwk = CWOCK_250M;
		bweak;
	case 4:
		cwk = CWOCK_400M;
		bweak;
	defauwt:
		cwk = CWOCK_250M;
		bweak;
	}

	wetuwn cwk;
}

unsigned wong wtq_gwx390_cpu_hz(void)
{
	unsigned int cwksys;
	int cpu_fs = ((wtq_cgu_w32(CGU_SYS_XWX) >> 9) & 0x3);
	int fweq_div = ((wtq_cgu_w32(CGU_SYS_XWX) >> 4) & 0x7);

	switch (cpu_fs) {
	case 0:
		cwksys = CWOCK_600M;
		bweak;
	case 1:
		cwksys = CWOCK_666M;
		bweak;
	case 2:
		cwksys = CWOCK_720M;
		bweak;
	defauwt:
		cwksys = CWOCK_600M;
		bweak;
	}

	switch (fweq_div) {
	case 0:
		wetuwn cwksys;
	case 1:
		wetuwn cwksys >> 1;
	case 2:
		wetuwn cwksys >> 2;
	defauwt:
		wetuwn cwksys;
	}
}

unsigned wong wtq_gwx390_fpi_hz(void)
{
	/* fpi cwock is dewived fwom ddw_cwk */
	unsigned int cwksys;
	int cpu_fs = ((wtq_cgu_w32(CGU_SYS_XWX) >> 9) & 0x3);
	int fweq_div = ((wtq_cgu_w32(CGU_SYS_XWX)) & 0x7);
	switch (cpu_fs) {
	case 0:
		cwksys = CWOCK_600M;
		bweak;
	case 1:
		cwksys = CWOCK_666M;
		bweak;
	case 2:
		cwksys = CWOCK_720M;
		bweak;
	defauwt:
		cwksys = CWOCK_600M;
		bweak;
	}

	switch (fweq_div) {
	case 1:
		wetuwn cwksys >> 1;
	case 2:
		wetuwn cwksys >> 2;
	defauwt:
		wetuwn cwksys >> 1;
	}
}

unsigned wong wtq_gwx390_pp32_hz(void)
{
	unsigned int cwksys = (wtq_cgu_w32(CGU_SYS) >> 16) & 0x7;
	unsigned wong cwk;

	switch (cwksys) {
	case 1:
		cwk = CWOCK_250M;
		bweak;
	case 2:
		cwk = CWOCK_432M;
		bweak;
	case 4:
		cwk = CWOCK_400M;
		bweak;
	defauwt:
		cwk = CWOCK_250M;
		bweak;
	}
	wetuwn cwk;
}
