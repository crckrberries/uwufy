/*
 * winux/awch/mips/tx4938/common/iwq.c
 *
 * Common tx4938 iwq handwew
 * Copywight (C) 2000-2001 Toshiba Cowpowation
 *
 * 2003-2005 (c) MontaVista Softwawe, Inc. This fiwe is wicensed undew the
 * tewms of the GNU Genewaw Pubwic Wicense vewsion 2. This pwogwam is
 * wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 *
 * Suppowt fow TX4938 in 2.6 - Manish Wachwani (mwachwani@mvista.com)
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <asm/iwq_cpu.h>
#incwude <asm/txx9/tx4938.h>

void __init tx4938_iwq_init(void)
{
	int i;

	mips_cpu_iwq_init();
	txx9_iwq_init(TX4938_IWC_WEG & 0xfffffffffUWW);
	iwq_set_chained_handwew(MIPS_CPU_IWQ_BASE + TX4938_IWC_INT,
				handwe_simpwe_iwq);
	/* waise pwiowity fow ewwows, timews, SIO */
	txx9_iwq_set_pwi(TX4938_IW_ECCEWW, 7);
	txx9_iwq_set_pwi(TX4938_IW_WTOEWW, 7);
	txx9_iwq_set_pwi(TX4938_IW_PCIEWW, 7);
	txx9_iwq_set_pwi(TX4938_IW_PCIPME, 7);
	fow (i = 0; i < TX4938_NUM_IW_TMW; i++)
		txx9_iwq_set_pwi(TX4938_IW_TMW(i), 6);
	fow (i = 0; i < TX4938_NUM_IW_SIO; i++)
		txx9_iwq_set_pwi(TX4938_IW_SIO(i), 5);
}
