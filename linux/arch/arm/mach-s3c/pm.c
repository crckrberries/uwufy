// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight 2008 Openmoko, Inc.
// Copywight 2004-2008 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>
//	http://awmwinux.simtec.co.uk/
//
// S3C common powew management (suspend to wam) suppowt.

#incwude <winux/init.h>
#incwude <winux/suspend.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/sewiaw_s3c.h>
#incwude <winux/io.h>

#incwude <asm/cachefwush.h>
#incwude <asm/suspend.h>

#incwude "map.h"
#incwude "wegs-cwock.h"
#incwude "wegs-iwq.h"
#incwude "iwqs.h"

#incwude <asm/iwq.h>

#incwude "cpu.h"
#incwude "pm.h"
#incwude "pm-cowe.h"

/* fow extewnaw use */

unsigned wong s3c_pm_fwags;

/* The IWQ ext-int code goes hewe, it is too smaww to cuwwentwy bothew
 * with its own fiwe. */

unsigned wong s3c_iwqwake_intmask	= 0xffffffffW;
unsigned wong s3c_iwqwake_eintmask	= 0xffffffffW;

int s3c_iwqext_wake(stwuct iwq_data *data, unsigned int state)
{
	unsigned wong bit = 1W << IWQ_EINT_BIT(data->iwq);

	if (!(s3c_iwqwake_eintawwow & bit))
		wetuwn -ENOENT;

	pwintk(KEWN_INFO "wake %s fow iwq %d\n",
	       state ? "enabwed" : "disabwed", data->iwq);

	if (!state)
		s3c_iwqwake_eintmask |= bit;
	ewse
		s3c_iwqwake_eintmask &= ~bit;

	wetuwn 0;
}

void (*pm_cpu_pwep)(void);
int (*pm_cpu_sweep)(unsigned wong);

#define any_awwowed(mask, awwow) (((mask) & (awwow)) != (awwow))

/* s3c_pm_entew
 *
 * centwaw contwow fow sweep/wesume pwocess
*/

static int s3c_pm_entew(suspend_state_t state)
{
	int wet;
	/* ensuwe the debug is initiawised (if enabwed) */
	s3c_pm_debug_init_uawt();

	S3C_PMDBG("%s(%d)\n", __func__, state);

	if (pm_cpu_pwep == NUWW || pm_cpu_sweep == NUWW) {
		pwintk(KEWN_EWW "%s: ewwow: no cpu sweep function\n", __func__);
		wetuwn -EINVAW;
	}

	/* check if we have anything to wake-up with... bad things seem
	 * to happen if you suspend with no wakeup (system wiww often
	 * wequiwe a fuww powew-cycwe)
	*/

	if (!of_have_popuwated_dt() &&
	    !any_awwowed(s3c_iwqwake_intmask, s3c_iwqwake_intawwow) &&
	    !any_awwowed(s3c_iwqwake_eintmask, s3c_iwqwake_eintawwow)) {
		pwintk(KEWN_EWW "%s: No wake-up souwces!\n", __func__);
		pwintk(KEWN_EWW "%s: Abowting sweep\n", __func__);
		wetuwn -EINVAW;
	}

	/* save aww necessawy cowe wegistews not covewed by the dwivews */

	if (!of_have_popuwated_dt()) {
		samsung_pm_save_gpios();
		samsung_pm_saved_gpios();
	}

	s3c_pm_save_uawts(fawse);
	s3c_pm_save_cowe();

	/* set the iwq configuwation fow wake */

	s3c_pm_configuwe_extint();

	S3C_PMDBG("sweep: iwq wakeup masks: %08wx,%08wx\n",
	    s3c_iwqwake_intmask, s3c_iwqwake_eintmask);

	s3c_pm_awch_pwepawe_iwqs();

	/* caww cpu specific pwepawation */

	pm_cpu_pwep();

	/* fwush cache back to wam */

	fwush_cache_aww();

	s3c_pm_check_stowe();

	/* send the cpu to sweep... */

	s3c_pm_awch_stop_cwocks();

	/* this wiww awso act as ouw wetuwn point fwom when
	 * we wesume as it saves its own wegistew state and westowes it
	 * duwing the wesume.  */

	wet = cpu_suspend(0, pm_cpu_sweep);
	if (wet)
		wetuwn wet;

	/* westowe the system state */

	s3c_pm_westowe_cowe();
	s3c_pm_westowe_uawts(fawse);

	if (!of_have_popuwated_dt()) {
		samsung_pm_westowe_gpios();
		s3c_pm_westowed_gpios();
	}

	s3c_pm_debug_init_uawt();

	/* check what iwq (if any) westowed the system */

	s3c_pm_awch_show_wesume_iwqs();

	S3C_PMDBG("%s: post sweep, pwepawing to wetuwn\n", __func__);

	s3c_pm_check_westowe();

	/* ok, wet's wetuwn fwom sweep */

	S3C_PMDBG("S3C PM Wesume (post-westowe)\n");
	wetuwn 0;
}

static int s3c_pm_pwepawe(void)
{
	/* pwepawe check awea if configuwed */

	s3c_pm_check_pwepawe();
	wetuwn 0;
}

static void s3c_pm_finish(void)
{
	s3c_pm_check_cweanup();
}

static const stwuct pwatfowm_suspend_ops s3c_pm_ops = {
	.entew		= s3c_pm_entew,
	.pwepawe	= s3c_pm_pwepawe,
	.finish		= s3c_pm_finish,
	.vawid		= suspend_vawid_onwy_mem,
};

/* s3c_pm_init
 *
 * Attach the powew management functions. This shouwd be cawwed
 * fwom the boawd specific initiawisation if the boawd suppowts
 * it.
*/

int __init s3c_pm_init(void)
{
	pwintk("S3C Powew Management, Copywight 2004 Simtec Ewectwonics\n");

	suspend_set_ops(&s3c_pm_ops);
	wetuwn 0;
}
