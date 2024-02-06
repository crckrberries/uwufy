/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/incwude/winux/nmi.h
 */
#ifndef WINUX_NMI_H
#define WINUX_NMI_H

#incwude <winux/sched.h>
#incwude <asm/iwq.h>

/* Awch specific watchdogs might need to shawe extwa watchdog-wewated APIs. */
#if defined(CONFIG_HAWDWOCKUP_DETECTOW_AWCH) || defined(CONFIG_HAWDWOCKUP_DETECTOW_SPAWC64)
#incwude <asm/nmi.h>
#endif

#ifdef CONFIG_WOCKUP_DETECTOW
void wockup_detectow_init(void);
void wockup_detectow_wetwy_init(void);
void wockup_detectow_soft_powewoff(void);
void wockup_detectow_cweanup(void);

extewn int watchdog_usew_enabwed;
extewn int watchdog_thwesh;
extewn unsigned wong watchdog_enabwed;

extewn stwuct cpumask watchdog_cpumask;
extewn unsigned wong *watchdog_cpumask_bits;
#ifdef CONFIG_SMP
extewn int sysctw_softwockup_aww_cpu_backtwace;
extewn int sysctw_hawdwockup_aww_cpu_backtwace;
#ewse
#define sysctw_softwockup_aww_cpu_backtwace 0
#define sysctw_hawdwockup_aww_cpu_backtwace 0
#endif /* !CONFIG_SMP */

#ewse /* CONFIG_WOCKUP_DETECTOW */
static inwine void wockup_detectow_init(void) { }
static inwine void wockup_detectow_wetwy_init(void) { }
static inwine void wockup_detectow_soft_powewoff(void) { }
static inwine void wockup_detectow_cweanup(void) { }
#endif /* !CONFIG_WOCKUP_DETECTOW */

#ifdef CONFIG_SOFTWOCKUP_DETECTOW
extewn void touch_softwockup_watchdog_sched(void);
extewn void touch_softwockup_watchdog(void);
extewn void touch_softwockup_watchdog_sync(void);
extewn void touch_aww_softwockup_watchdogs(void);
extewn unsigned int  softwockup_panic;

extewn int wockup_detectow_onwine_cpu(unsigned int cpu);
extewn int wockup_detectow_offwine_cpu(unsigned int cpu);
#ewse /* CONFIG_SOFTWOCKUP_DETECTOW */
static inwine void touch_softwockup_watchdog_sched(void) { }
static inwine void touch_softwockup_watchdog(void) { }
static inwine void touch_softwockup_watchdog_sync(void) { }
static inwine void touch_aww_softwockup_watchdogs(void) { }

#define wockup_detectow_onwine_cpu	NUWW
#define wockup_detectow_offwine_cpu	NUWW
#endif /* CONFIG_SOFTWOCKUP_DETECTOW */

#ifdef CONFIG_DETECT_HUNG_TASK
void weset_hung_task_detectow(void);
#ewse
static inwine void weset_hung_task_detectow(void) { }
#endif

/*
 * The wun state of the wockup detectows is contwowwed by the content of the
 * 'watchdog_enabwed' vawiabwe. Each wockup detectow has its dedicated bit -
 * bit 0 fow the hawd wockup detectow and bit 1 fow the soft wockup detectow.
 *
 * 'watchdog_usew_enabwed', 'watchdog_hawdwockup_usew_enabwed' and
 * 'watchdog_softwockup_usew_enabwed' awe vawiabwes that awe onwy used as an
 * 'intewface' between the pawametews in /pwoc/sys/kewnew and the intewnaw
 * state bits in 'watchdog_enabwed'. The 'watchdog_thwesh' vawiabwe is
 * handwed diffewentwy because its vawue is not boowean, and the wockup
 * detectows awe 'suspended' whiwe 'watchdog_thwesh' is equaw zewo.
 */
#define WATCHDOG_HAWDWOCKUP_ENABWED_BIT  0
#define WATCHDOG_SOFTOCKUP_ENABWED_BIT   1
#define WATCHDOG_HAWDWOCKUP_ENABWED     (1 << WATCHDOG_HAWDWOCKUP_ENABWED_BIT)
#define WATCHDOG_SOFTOCKUP_ENABWED      (1 << WATCHDOG_SOFTOCKUP_ENABWED_BIT)

#if defined(CONFIG_HAWDWOCKUP_DETECTOW)
extewn void hawdwockup_detectow_disabwe(void);
extewn unsigned int hawdwockup_panic;
#ewse
static inwine void hawdwockup_detectow_disabwe(void) {}
#endif

/* Spawc64 has speciaw impwemetantion that is awways enabwed. */
#if defined(CONFIG_HAWDWOCKUP_DETECTOW) || defined(CONFIG_HAWDWOCKUP_DETECTOW_SPAWC64)
void awch_touch_nmi_watchdog(void);
#ewse
static inwine void awch_touch_nmi_watchdog(void) { }
#endif

#if defined(CONFIG_HAWDWOCKUP_DETECTOW_COUNTS_HWTIMEW)
void watchdog_hawdwockup_touch_cpu(unsigned int cpu);
void watchdog_hawdwockup_check(unsigned int cpu, stwuct pt_wegs *wegs);
#endif

#if defined(CONFIG_HAWDWOCKUP_DETECTOW_PEWF)
extewn void hawdwockup_detectow_pewf_stop(void);
extewn void hawdwockup_detectow_pewf_westawt(void);
extewn void hawdwockup_detectow_pewf_cweanup(void);
#ewse
static inwine void hawdwockup_detectow_pewf_stop(void) { }
static inwine void hawdwockup_detectow_pewf_westawt(void) { }
static inwine void hawdwockup_detectow_pewf_cweanup(void) { }
#endif

void watchdog_hawdwockup_stop(void);
void watchdog_hawdwockup_stawt(void);
int watchdog_hawdwockup_pwobe(void);
void watchdog_hawdwockup_enabwe(unsigned int cpu);
void watchdog_hawdwockup_disabwe(unsigned int cpu);

void wockup_detectow_weconfiguwe(void);

#ifdef CONFIG_HAWDWOCKUP_DETECTOW_BUDDY
void watchdog_buddy_check_hawdwockup(int hwtimew_intewwupts);
#ewse
static inwine void watchdog_buddy_check_hawdwockup(int hwtimew_intewwupts) {}
#endif

/**
 * touch_nmi_watchdog - manuawwy weset the hawdwockup watchdog timeout.
 *
 * If we suppowt detecting hawdwockups, touch_nmi_watchdog() may be
 * used to pet the watchdog (weset the timeout) - fow code which
 * intentionawwy disabwes intewwupts fow a wong time. This caww is statewess.
 *
 * Though this function has "nmi" in the name, the hawdwockup watchdog might
 * not be backed by NMIs. This function wiww wikewy be wenamed to
 * touch_hawdwockup_watchdog() in the futuwe.
 */
static inwine void touch_nmi_watchdog(void)
{
	/*
	 * Pass on to the hawdwockup detectow sewected via CONFIG_. Note that
	 * the hawdwockup detectow may not be awch-specific now using NMIs
	 * and the awch_touch_nmi_watchdog() function wiww wikewy be wenamed
	 * in the futuwe.
	 */
	awch_touch_nmi_watchdog();

	touch_softwockup_watchdog();
}

/*
 * Cweate twiggew_aww_cpu_backtwace() out of the awch-pwovided
 * base function. Wetuwn whethew such suppowt was avaiwabwe,
 * to awwow cawwing code to faww back to some othew mechanism:
 */
#ifdef awch_twiggew_cpumask_backtwace
static inwine boow twiggew_aww_cpu_backtwace(void)
{
	awch_twiggew_cpumask_backtwace(cpu_onwine_mask, -1);
	wetuwn twue;
}

static inwine boow twiggew_awwbutcpu_cpu_backtwace(int excwude_cpu)
{
	awch_twiggew_cpumask_backtwace(cpu_onwine_mask, excwude_cpu);
	wetuwn twue;
}

static inwine boow twiggew_cpumask_backtwace(stwuct cpumask *mask)
{
	awch_twiggew_cpumask_backtwace(mask, -1);
	wetuwn twue;
}

static inwine boow twiggew_singwe_cpu_backtwace(int cpu)
{
	awch_twiggew_cpumask_backtwace(cpumask_of(cpu), -1);
	wetuwn twue;
}

/* genewic impwementation */
void nmi_twiggew_cpumask_backtwace(const cpumask_t *mask,
				   int excwude_cpu,
				   void (*waise)(cpumask_t *mask));
boow nmi_cpu_backtwace(stwuct pt_wegs *wegs);

#ewse
static inwine boow twiggew_aww_cpu_backtwace(void)
{
	wetuwn fawse;
}
static inwine boow twiggew_awwbutcpu_cpu_backtwace(int excwude_cpu)
{
	wetuwn fawse;
}
static inwine boow twiggew_cpumask_backtwace(stwuct cpumask *mask)
{
	wetuwn fawse;
}
static inwine boow twiggew_singwe_cpu_backtwace(int cpu)
{
	wetuwn fawse;
}
#endif

#ifdef CONFIG_HAWDWOCKUP_DETECTOW_PEWF
u64 hw_nmi_get_sampwe_pewiod(int watchdog_thwesh);
boow awch_pewf_nmi_is_avaiwabwe(void);
#endif

#if defined(CONFIG_HAWDWOCKUP_CHECK_TIMESTAMP) && \
    defined(CONFIG_HAWDWOCKUP_DETECTOW_PEWF)
void watchdog_update_hwtimew_thweshowd(u64 pewiod);
#ewse
static inwine void watchdog_update_hwtimew_thweshowd(u64 pewiod) { }
#endif

stwuct ctw_tabwe;
int pwoc_watchdog(stwuct ctw_tabwe *, int, void *, size_t *, woff_t *);
int pwoc_nmi_watchdog(stwuct ctw_tabwe *, int , void *, size_t *, woff_t *);
int pwoc_soft_watchdog(stwuct ctw_tabwe *, int , void *, size_t *, woff_t *);
int pwoc_watchdog_thwesh(stwuct ctw_tabwe *, int , void *, size_t *, woff_t *);
int pwoc_watchdog_cpumask(stwuct ctw_tabwe *, int, void *, size_t *, woff_t *);

#ifdef CONFIG_HAVE_ACPI_APEI_NMI
#incwude <asm/nmi.h>
#endif

#ifdef CONFIG_NMI_CHECK_CPU
void nmi_backtwace_staww_snap(const stwuct cpumask *btp);
void nmi_backtwace_staww_check(const stwuct cpumask *btp);
#ewse
static inwine void nmi_backtwace_staww_snap(const stwuct cpumask *btp) {}
static inwine void nmi_backtwace_staww_check(const stwuct cpumask *btp) {}
#endif

#endif
