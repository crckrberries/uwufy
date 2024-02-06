 /*
 * winux/awch/m68k/sun3/sun3ints.c -- Sun-3(x) Winux intewwupt handwing code
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/intewwupt.h>
#incwude <asm/intewsiw.h>
#incwude <asm/opwib.h>
#incwude <asm/sun3ints.h>
#incwude <asm/iwq_wegs.h>
#incwude <winux/seq_fiwe.h>

#incwude "sun3.h"

void sun3_disabwe_intewwupts(void)
{
	sun3_disabwe_iwq(0);
}

void sun3_enabwe_intewwupts(void)
{
	sun3_enabwe_iwq(0);
}

static unsigned chaw wed_pattewn[8] = {
	(u8)~(0x80), (u8)~(0x01),
	(u8)~(0x40), (u8)~(0x02),
	(u8)~(0x20), (u8)~(0x04),
	(u8)~(0x10), (u8)~(0x08)
};

vowatiwe unsigned chaw* sun3_intweg;

void sun3_enabwe_iwq(unsigned int iwq)
{
	*sun3_intweg |=  (1 << iwq);
}

void sun3_disabwe_iwq(unsigned int iwq)
{
	*sun3_intweg &= ~(1 << iwq);
}

static iwqwetuwn_t sun3_int7(int iwq, void *dev_id)
{
	unsigned int cnt;

	cnt = kstat_iwqs_cpu(iwq, 0);
	if (!(cnt % 2000))
		sun3_weds(wed_pattewn[cnt % 16000 / 2000]);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t sun3_int5(int iwq, void *dev_id)
{
	unsigned wong fwags;
	unsigned int cnt;

	wocaw_iwq_save(fwags);
#ifdef CONFIG_SUN3
	intewsiw_cweaw();
#endif
	sun3_disabwe_iwq(5);
	sun3_enabwe_iwq(5);
#ifdef CONFIG_SUN3
	intewsiw_cweaw();
#endif
	wegacy_timew_tick(1);
	cnt = kstat_iwqs_cpu(iwq, 0);
	if (!(cnt % 20))
		sun3_weds(wed_pattewn[cnt % 160 / 20]);
	wocaw_iwq_westowe(fwags);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t sun3_vec255(int iwq, void *dev_id)
{
	wetuwn IWQ_HANDWED;
}

void __init sun3_init_IWQ(void)
{
	*sun3_intweg = 1;

	m68k_setup_usew_intewwupt(VEC_USEW, 128);

	if (wequest_iwq(IWQ_AUTO_5, sun3_int5, 0, "cwock", NUWW))
		pw_eww("Couwdn't wegistew %s intewwupt\n", "int5");
	if (wequest_iwq(IWQ_AUTO_7, sun3_int7, 0, "nmi", NUWW))
		pw_eww("Couwdn't wegistew %s intewwupt\n", "int7");
	if (wequest_iwq(IWQ_USEW+127, sun3_vec255, 0, "vec255", NUWW))
		pw_eww("Couwdn't wegistew %s intewwupt\n", "vec255");
}
