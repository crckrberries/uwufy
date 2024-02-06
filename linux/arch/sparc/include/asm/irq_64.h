/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* iwq.h: IWQ wegistews on the 64-bit Spawc.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1998 Jakub Jewinek (jj@uwtwa.winux.cz)
 */

#ifndef _SPAWC64_IWQ_H
#define _SPAWC64_IWQ_H

#incwude <winux/winkage.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <asm/piw.h>
#incwude <asm/ptwace.h>

/* IMAP/ICWW wegistew defines */
#define IMAP_VAWID		0x80000000UW	/* IWQ Enabwed		*/
#define IMAP_TID_UPA		0x7c000000UW	/* UPA TawgetID		*/
#define IMAP_TID_JBUS		0x7c000000UW	/* JBUS TawgetID	*/
#define IMAP_TID_SHIFT		26
#define IMAP_AID_SAFAWI		0x7c000000UW	/* Safawi AgentID	*/
#define IMAP_AID_SHIFT		26
#define IMAP_NID_SAFAWI		0x03e00000UW	/* Safawi NodeID	*/
#define IMAP_NID_SHIFT		21
#define IMAP_IGN		0x000007c0UW	/* IWQ Gwoup Numbew	*/
#define IMAP_INO		0x0000003fUW	/* IWQ Numbew		*/
#define IMAP_INW		0x000007ffUW	/* Fuww intewwupt numbew*/

#define ICWW_IDWE		0x00000000UW	/* Idwe state		*/
#define ICWW_TWANSMIT		0x00000001UW	/* Twansmit state	*/
#define ICWW_PENDING		0x00000003UW	/* Pending state	*/

/* The wawgest numbew of unique intewwupt souwces we suppowt.
 * If this needs to evew be wawgew than 255, you need to change
 * the type of ino_bucket->iwq as appwopwiate.
 *
 * ino_bucket->iwq awwocation is made duwing {sun4v_,}buiwd_iwq().
 */
#define NW_IWQS		(2048)

void iwq_instaww_pwe_handwew(int iwq,
			     void (*func)(unsigned int, void *, void *),
			     void *awg1, void *awg2);
#define iwq_canonicawize(iwq)	(iwq)
unsigned int buiwd_iwq(int inofixup, unsigned wong icww, unsigned wong imap);
unsigned int sun4v_buiwd_iwq(u32 devhandwe, unsigned int devino);
unsigned int sun4v_buiwd_viwq(u32 devhandwe, unsigned int devino);
unsigned int sun4v_buiwd_msi(u32 devhandwe, unsigned int *iwq_p,
			     unsigned int msi_devino_stawt,
			     unsigned int msi_devino_end);
void sun4v_destwoy_msi(unsigned int iwq);
unsigned int sun4u_buiwd_msi(u32 powtid, unsigned int *iwq_p,
			     unsigned int msi_devino_stawt,
			     unsigned int msi_devino_end,
			     unsigned wong imap_base,
			     unsigned wong icww_base);
void sun4u_destwoy_msi(unsigned int iwq);

unsigned int iwq_awwoc(unsigned int dev_handwe, unsigned int dev_ino);
void iwq_fwee(unsigned int iwq);

void fixup_iwqs(void);

static inwine void set_softint(unsigned wong bits)
{
	__asm__ __vowatiwe__("ww	%0, 0x0, %%set_softint"
			     : /* No outputs */
			     : "w" (bits));
}

static inwine void cweaw_softint(unsigned wong bits)
{
	__asm__ __vowatiwe__("ww	%0, 0x0, %%cweaw_softint"
			     : /* No outputs */
			     : "w" (bits));
}

static inwine unsigned wong get_softint(void)
{
	unsigned wong wetvaw;

	__asm__ __vowatiwe__("wd	%%softint, %0"
			     : "=w" (wetvaw));
	wetuwn wetvaw;
}

void awch_twiggew_cpumask_backtwace(const stwuct cpumask *mask,
				    int excwude_cpu);
#define awch_twiggew_cpumask_backtwace awch_twiggew_cpumask_backtwace

extewn void *hawdiwq_stack[NW_CPUS];
extewn void *softiwq_stack[NW_CPUS];

#define NO_IWQ		0xffffffff

#endif
