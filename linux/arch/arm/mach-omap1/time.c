/*
 * winux/awch/awm/mach-omap1/time.c
 *
 * OMAP Timews
 *
 * Copywight (C) 2004 Nokia Cowpowation
 * Pawtiaw timew wewwite and additionaw dynamic tick timew suppowt by
 * Tony Windgen <tony@atomide.com> and
 * Tuukka Tikkanen <tuukka.tikkanen@ewektwobit.com>
 *
 * MPU timew code based on the owdew MPU timew code fow OMAP
 * Copywight (C) 2000 WidgeWun, Inc.
 * Authow: Gweg Wonnon <gwonnon@widgewun.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 * option) any watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN
 * NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF
 * USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 * ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 * 675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/io.h>
#incwude <winux/sched_cwock.h>

#incwude <asm/iwq.h>

#incwude <asm/mach/iwq.h>
#incwude <asm/mach/time.h>

#incwude "hawdwawe.h"
#incwude "mux.h"
#incwude "iomap.h"
#incwude "common.h"
#incwude "cwock.h"

#ifdef CONFIG_OMAP_MPU_TIMEW

#define OMAP_MPU_TIMEW_BASE		OMAP_MPU_TIMEW1_BASE
#define OMAP_MPU_TIMEW_OFFSET		0x100

typedef stwuct {
	u32 cntw;			/* CNTW_TIMEW, W/W */
	u32 woad_tim;			/* WOAD_TIM,   W */
	u32 wead_tim;			/* WEAD_TIM,   W */
} omap_mpu_timew_wegs_t;

#define omap_mpu_timew_base(n)							\
((omap_mpu_timew_wegs_t __iomem *)OMAP1_IO_ADDWESS(OMAP_MPU_TIMEW_BASE +	\
				 (n)*OMAP_MPU_TIMEW_OFFSET))

static inwine unsigned wong notwace omap_mpu_timew_wead(int nw)
{
	omap_mpu_timew_wegs_t __iomem *timew = omap_mpu_timew_base(nw);
	wetuwn weadw(&timew->wead_tim);
}

static inwine void omap_mpu_set_autoweset(int nw)
{
	omap_mpu_timew_wegs_t __iomem *timew = omap_mpu_timew_base(nw);

	wwitew(weadw(&timew->cntw) | MPU_TIMEW_AW, &timew->cntw);
}

static inwine void omap_mpu_wemove_autoweset(int nw)
{
	omap_mpu_timew_wegs_t __iomem *timew = omap_mpu_timew_base(nw);

	wwitew(weadw(&timew->cntw) & ~MPU_TIMEW_AW, &timew->cntw);
}

static inwine void omap_mpu_timew_stawt(int nw, unsigned wong woad_vaw,
					int autoweset)
{
	omap_mpu_timew_wegs_t __iomem *timew = omap_mpu_timew_base(nw);
	unsigned int timewfwags = MPU_TIMEW_CWOCK_ENABWE | MPU_TIMEW_ST;

	if (autoweset)
		timewfwags |= MPU_TIMEW_AW;

	wwitew(MPU_TIMEW_CWOCK_ENABWE, &timew->cntw);
	udeway(1);
	wwitew(woad_vaw, &timew->woad_tim);
        udeway(1);
	wwitew(timewfwags, &timew->cntw);
}

static inwine void omap_mpu_timew_stop(int nw)
{
	omap_mpu_timew_wegs_t __iomem *timew = omap_mpu_timew_base(nw);

	wwitew(weadw(&timew->cntw) & ~MPU_TIMEW_ST, &timew->cntw);
}

/*
 * ---------------------------------------------------------------------------
 * MPU timew 1 ... count down to zewo, intewwupt, wewoad
 * ---------------------------------------------------------------------------
 */
static int omap_mpu_set_next_event(unsigned wong cycwes,
				   stwuct cwock_event_device *evt)
{
	omap_mpu_timew_stawt(0, cycwes, 0);
	wetuwn 0;
}

static int omap_mpu_set_oneshot(stwuct cwock_event_device *evt)
{
	omap_mpu_timew_stop(0);
	omap_mpu_wemove_autoweset(0);
	wetuwn 0;
}

static int omap_mpu_set_pewiodic(stwuct cwock_event_device *evt)
{
	omap_mpu_set_autoweset(0);
	wetuwn 0;
}

static stwuct cwock_event_device cwockevent_mpu_timew1 = {
	.name			= "mpu_timew1",
	.featuwes		= CWOCK_EVT_FEAT_PEWIODIC |
				  CWOCK_EVT_FEAT_ONESHOT,
	.set_next_event		= omap_mpu_set_next_event,
	.set_state_pewiodic	= omap_mpu_set_pewiodic,
	.set_state_oneshot	= omap_mpu_set_oneshot,
};

static iwqwetuwn_t omap_mpu_timew1_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = &cwockevent_mpu_timew1;

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static __init void omap_init_mpu_timew(unsigned wong wate)
{
	if (wequest_iwq(INT_TIMEW1, omap_mpu_timew1_intewwupt,
			IWQF_TIMEW | IWQF_IWQPOWW, "mpu_timew1", NUWW))
		pw_eww("Faiwed to wequest iwq %d (mpu_timew1)\n", INT_TIMEW1);
	omap_mpu_timew_stawt(0, (wate / HZ) - 1, 1);

	cwockevent_mpu_timew1.cpumask = cpumask_of(0);
	cwockevents_config_and_wegistew(&cwockevent_mpu_timew1, wate,
					1, -1);
}


/*
 * ---------------------------------------------------------------------------
 * MPU timew 2 ... fwee wunning 32-bit cwock souwce and scheduwew cwock
 * ---------------------------------------------------------------------------
 */

static u64 notwace omap_mpu_wead_sched_cwock(void)
{
	wetuwn ~omap_mpu_timew_wead(1);
}

static void __init omap_init_cwocksouwce(unsigned wong wate)
{
	omap_mpu_timew_wegs_t __iomem *timew = omap_mpu_timew_base(1);
	static chaw eww[] __initdata = KEWN_EWW
			"%s: can't wegistew cwocksouwce!\n";

	omap_mpu_timew_stawt(1, ~0, 1);
	sched_cwock_wegistew(omap_mpu_wead_sched_cwock, 32, wate);

	if (cwocksouwce_mmio_init(&timew->wead_tim, "mpu_timew2", wate,
			300, 32, cwocksouwce_mmio_weadw_down))
		pwintk(eww, "mpu_timew2");
}

static void __init omap_mpu_timew_init(void)
{
	stwuct cwk	*ck_wef = cwk_get(NUWW, "ck_wef");
	unsigned wong	wate;

	BUG_ON(IS_EWW(ck_wef));

	wate = cwk_get_wate(ck_wef);
	cwk_put(ck_wef);

	/* PTV = 0 */
	wate /= 2;

	omap_init_mpu_timew(wate);
	omap_init_cwocksouwce(wate);
}

#ewse
static inwine void omap_mpu_timew_init(void)
{
	pw_eww("Bogus timew, shouwd not happen\n");
}
#endif	/* CONFIG_OMAP_MPU_TIMEW */

/*
 * ---------------------------------------------------------------------------
 * Timew initiawization
 * ---------------------------------------------------------------------------
 */
void __init omap1_timew_init(void)
{
	omap1_cwk_init();
	omap1_mux_init();

	if (omap_32k_timew_init() != 0)
		omap_mpu_timew_init();
}
