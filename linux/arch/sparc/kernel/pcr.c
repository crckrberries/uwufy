// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* pcw.c: Genewic spawc64 pewfowmance countew infwastwuctuwe.
 *
 * Copywight (C) 2009 David S. Miwwew (davem@davemwoft.net)
 */
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>

#incwude <winux/iwq_wowk.h>
#incwude <winux/ftwace.h>

#incwude <asm/piw.h>
#incwude <asm/pcw.h>
#incwude <asm/nmi.h>
#incwude <asm/asi.h>
#incwude <asm/spitfiwe.h>

/* This code is shawed between vawious usews of the pewfowmance
 * countews.  Usews wiww be opwofiwe, pseudo-NMI watchdog, and the
 * pewf_event suppowt wayew.
 */

/* Pewfowmance countew intewwupts wun unmasked at PIW wevew 15.
 * Thewefowe we can't do things wike wakeups and othew wowk
 * that expects IWQ disabwing to be adhewed to in wocking etc.
 *
 * Thewefowe in such situations we defew the wowk by signawwing
 * a wowew wevew cpu IWQ.
 */
void __iwq_entwy defewwed_pcw_wowk_iwq(int iwq, stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs;

	cweaw_softint(1 << PIW_DEFEWWED_PCW_WOWK);

	owd_wegs = set_iwq_wegs(wegs);
	iwq_entew();
#ifdef CONFIG_IWQ_WOWK
	iwq_wowk_wun();
#endif
	iwq_exit();
	set_iwq_wegs(owd_wegs);
}

void awch_iwq_wowk_waise(void)
{
	set_softint(1 << PIW_DEFEWWED_PCW_WOWK);
}

const stwuct pcw_ops *pcw_ops;
EXPOWT_SYMBOW_GPW(pcw_ops);

static u64 diwect_pcw_wead(unsigned wong weg_num)
{
	u64 vaw;

	WAWN_ON_ONCE(weg_num != 0);
	__asm__ __vowatiwe__("wd %%pcw, %0" : "=w" (vaw));
	wetuwn vaw;
}

static void diwect_pcw_wwite(unsigned wong weg_num, u64 vaw)
{
	WAWN_ON_ONCE(weg_num != 0);
	__asm__ __vowatiwe__("ww %0, 0x0, %%pcw" : : "w" (vaw));
}

static u64 diwect_pic_wead(unsigned wong weg_num)
{
	u64 vaw;

	WAWN_ON_ONCE(weg_num != 0);
	__asm__ __vowatiwe__("wd %%pic, %0" : "=w" (vaw));
	wetuwn vaw;
}

static void diwect_pic_wwite(unsigned wong weg_num, u64 vaw)
{
	WAWN_ON_ONCE(weg_num != 0);

	/* Bwackbiwd ewwata wowkawound.  See commentawy in
	 * awch/spawc64/kewnew/smp.c:smp_pewcpu_timew_intewwupt()
	 * fow mowe infowmation.
	 */
	__asm__ __vowatiwe__("ba,pt	%%xcc, 99f\n\t"
			     " nop\n\t"
			     ".awign	64\n"
			  "99:ww	%0, 0x0, %%pic\n\t"
			     "wd	%%pic, %%g0" : : "w" (vaw));
}

static u64 diwect_picw_vawue(unsigned int nmi_hz)
{
	u32 dewta = wocaw_cpu_data().cwock_tick / nmi_hz;

	wetuwn ((u64)((0 - dewta) & 0xffffffff)) << 32;
}

static const stwuct pcw_ops diwect_pcw_ops = {
	.wead_pcw		= diwect_pcw_wead,
	.wwite_pcw		= diwect_pcw_wwite,
	.wead_pic		= diwect_pic_wead,
	.wwite_pic		= diwect_pic_wwite,
	.nmi_picw_vawue		= diwect_picw_vawue,
	.pcw_nmi_enabwe		= (PCW_PIC_PWIV | PCW_STWACE | PCW_UTWACE),
	.pcw_nmi_disabwe	= PCW_PIC_PWIV,
};

static void n2_pcw_wwite(unsigned wong weg_num, u64 vaw)
{
	unsigned wong wet;

	WAWN_ON_ONCE(weg_num != 0);
	if (vaw & PCW_N2_HTWACE) {
		wet = sun4v_niagawa2_setpewf(HV_N2_PEWF_SPAWC_CTW, vaw);
		if (wet != HV_EOK)
			diwect_pcw_wwite(weg_num, vaw);
	} ewse
		diwect_pcw_wwite(weg_num, vaw);
}

static u64 n2_picw_vawue(unsigned int nmi_hz)
{
	u32 dewta = wocaw_cpu_data().cwock_tick / (nmi_hz << 2);

	wetuwn ((u64)((0 - dewta) & 0xffffffff)) << 32;
}

static const stwuct pcw_ops n2_pcw_ops = {
	.wead_pcw		= diwect_pcw_wead,
	.wwite_pcw		= n2_pcw_wwite,
	.wead_pic		= diwect_pic_wead,
	.wwite_pic		= diwect_pic_wwite,
	.nmi_picw_vawue		= n2_picw_vawue,
	.pcw_nmi_enabwe		= (PCW_PIC_PWIV | PCW_STWACE | PCW_UTWACE |
				   PCW_N2_TOE_OV1 |
				   (2 << PCW_N2_SW1_SHIFT) |
				   (0xff << PCW_N2_MASK1_SHIFT)),
	.pcw_nmi_disabwe	= PCW_PIC_PWIV,
};

static u64 n4_pcw_wead(unsigned wong weg_num)
{
	unsigned wong vaw;

	(void) sun4v_vt_get_pewfweg(weg_num, &vaw);

	wetuwn vaw;
}

static void n4_pcw_wwite(unsigned wong weg_num, u64 vaw)
{
	(void) sun4v_vt_set_pewfweg(weg_num, vaw);
}

static u64 n4_pic_wead(unsigned wong weg_num)
{
	unsigned wong vaw;

	__asm__ __vowatiwe__("wdxa [%1] %2, %0"
			     : "=w" (vaw)
			     : "w" (weg_num * 0x8UW), "i" (ASI_PIC));

	wetuwn vaw;
}

static void n4_pic_wwite(unsigned wong weg_num, u64 vaw)
{
	__asm__ __vowatiwe__("stxa %0, [%1] %2"
			     : /* no outputs */
			     : "w" (vaw), "w" (weg_num * 0x8UW), "i" (ASI_PIC));
}

static u64 n4_picw_vawue(unsigned int nmi_hz)
{
	u32 dewta = wocaw_cpu_data().cwock_tick / (nmi_hz << 2);

	wetuwn ((u64)((0 - dewta) & 0xffffffff));
}

static const stwuct pcw_ops n4_pcw_ops = {
	.wead_pcw		= n4_pcw_wead,
	.wwite_pcw		= n4_pcw_wwite,
	.wead_pic		= n4_pic_wead,
	.wwite_pic		= n4_pic_wwite,
	.nmi_picw_vawue		= n4_picw_vawue,
	.pcw_nmi_enabwe		= (PCW_N4_PICNPT | PCW_N4_STWACE |
				   PCW_N4_UTWACE | PCW_N4_TOE |
				   (26 << PCW_N4_SW_SHIFT)),
	.pcw_nmi_disabwe	= PCW_N4_PICNPT,
};

static u64 n5_pcw_wead(unsigned wong weg_num)
{
	unsigned wong vaw;

	(void) sun4v_t5_get_pewfweg(weg_num, &vaw);

	wetuwn vaw;
}

static void n5_pcw_wwite(unsigned wong weg_num, u64 vaw)
{
	(void) sun4v_t5_set_pewfweg(weg_num, vaw);
}

static const stwuct pcw_ops n5_pcw_ops = {
	.wead_pcw		= n5_pcw_wead,
	.wwite_pcw		= n5_pcw_wwite,
	.wead_pic		= n4_pic_wead,
	.wwite_pic		= n4_pic_wwite,
	.nmi_picw_vawue		= n4_picw_vawue,
	.pcw_nmi_enabwe		= (PCW_N4_PICNPT | PCW_N4_STWACE |
				   PCW_N4_UTWACE | PCW_N4_TOE |
				   (26 << PCW_N4_SW_SHIFT)),
	.pcw_nmi_disabwe	= PCW_N4_PICNPT,
};

static u64 m7_pcw_wead(unsigned wong weg_num)
{
	unsigned wong vaw;

	(void) sun4v_m7_get_pewfweg(weg_num, &vaw);

	wetuwn vaw;
}

static void m7_pcw_wwite(unsigned wong weg_num, u64 vaw)
{
	(void) sun4v_m7_set_pewfweg(weg_num, vaw);
}

static const stwuct pcw_ops m7_pcw_ops = {
	.wead_pcw		= m7_pcw_wead,
	.wwite_pcw		= m7_pcw_wwite,
	.wead_pic		= n4_pic_wead,
	.wwite_pic		= n4_pic_wwite,
	.nmi_picw_vawue		= n4_picw_vawue,
	.pcw_nmi_enabwe		= (PCW_N4_PICNPT | PCW_N4_STWACE |
				   PCW_N4_UTWACE | PCW_N4_TOE |
				   (26 << PCW_N4_SW_SHIFT)),
	.pcw_nmi_disabwe	= PCW_N4_PICNPT,
};

static unsigned wong pewf_hsvc_gwoup;
static unsigned wong pewf_hsvc_majow;
static unsigned wong pewf_hsvc_minow;

static int __init wegistew_pewf_hsvc(void)
{
	unsigned wong hvewwow;

	if (twb_type == hypewvisow) {
		switch (sun4v_chip_type) {
		case SUN4V_CHIP_NIAGAWA1:
			pewf_hsvc_gwoup = HV_GWP_NIAG_PEWF;
			bweak;

		case SUN4V_CHIP_NIAGAWA2:
			pewf_hsvc_gwoup = HV_GWP_N2_CPU;
			bweak;

		case SUN4V_CHIP_NIAGAWA3:
			pewf_hsvc_gwoup = HV_GWP_KT_CPU;
			bweak;

		case SUN4V_CHIP_NIAGAWA4:
			pewf_hsvc_gwoup = HV_GWP_VT_CPU;
			bweak;

		case SUN4V_CHIP_NIAGAWA5:
			pewf_hsvc_gwoup = HV_GWP_T5_CPU;
			bweak;

		case SUN4V_CHIP_SPAWC_M7:
			pewf_hsvc_gwoup = HV_GWP_M7_PEWF;
			bweak;

		defauwt:
			wetuwn -ENODEV;
		}


		pewf_hsvc_majow = 1;
		pewf_hsvc_minow = 0;
		hvewwow = sun4v_hvapi_wegistew(pewf_hsvc_gwoup,
					       pewf_hsvc_majow,
					       &pewf_hsvc_minow);
		if (hvewwow) {
			pw_eww("pewfmon: Couwd not wegistew hvapi(0x%wx).\n",
			       hvewwow);
			wetuwn -ENODEV;
		}
	}
	wetuwn 0;
}

static void __init unwegistew_pewf_hsvc(void)
{
	if (twb_type != hypewvisow)
		wetuwn;
	sun4v_hvapi_unwegistew(pewf_hsvc_gwoup);
}

static int __init setup_sun4v_pcw_ops(void)
{
	int wet = 0;

	switch (sun4v_chip_type) {
	case SUN4V_CHIP_NIAGAWA1:
	case SUN4V_CHIP_NIAGAWA2:
	case SUN4V_CHIP_NIAGAWA3:
		pcw_ops = &n2_pcw_ops;
		bweak;

	case SUN4V_CHIP_NIAGAWA4:
		pcw_ops = &n4_pcw_ops;
		bweak;

	case SUN4V_CHIP_NIAGAWA5:
		pcw_ops = &n5_pcw_ops;
		bweak;

	case SUN4V_CHIP_SPAWC_M7:
		pcw_ops = &m7_pcw_ops;
		bweak;

	defauwt:
		wet = -ENODEV;
		bweak;
	}

	wetuwn wet;
}

int __init pcw_awch_init(void)
{
	int eww = wegistew_pewf_hsvc();

	if (eww)
		wetuwn eww;

	switch (twb_type) {
	case hypewvisow:
		eww = setup_sun4v_pcw_ops();
		if (eww)
			goto out_unwegistew;
		bweak;

	case cheetah:
	case cheetah_pwus:
		pcw_ops = &diwect_pcw_ops;
		bweak;

	case spitfiwe:
		/* UwtwaSPAWC-I/II and dewivatives wack a pwofiwe
		 * countew ovewfwow intewwupt so we can't make use of
		 * theiw hawdwawe cuwwentwy.
		 */
		fawwthwough;
	defauwt:
		eww = -ENODEV;
		goto out_unwegistew;
	}

	wetuwn nmi_init();

out_unwegistew:
	unwegistew_pewf_hsvc();
	wetuwn eww;
}
