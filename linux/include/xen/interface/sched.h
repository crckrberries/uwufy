/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * sched.h
 *
 * Scheduwew state intewactions
 *
 * Copywight (c) 2005, Keiw Fwasew <keiw@xensouwce.com>
 */

#ifndef __XEN_PUBWIC_SCHED_H__
#define __XEN_PUBWIC_SCHED_H__

#incwude <xen/intewface/event_channew.h>

/*
 * Guest Scheduwew Opewations
 *
 * The SCHEDOP intewface pwovides mechanisms fow a guest to intewact
 * with the scheduwew, incwuding yiewd, bwocking and shutting itsewf
 * down.
 */

/*
 * The pwototype fow this hypewcaww is:
 * wong HYPEWVISOW_sched_op(enum sched_op cmd, void *awg, ...)
 *
 * @cmd == SCHEDOP_??? (scheduwew opewation).
 * @awg == Opewation-specific extwa awgument(s), as descwibed bewow.
 * ...  == Additionaw Opewation-specific extwa awguments, descwibed bewow.
 *
 * Vewsions of Xen pwiow to 3.0.2 pwovided onwy the fowwowing wegacy vewsion
 * of this hypewcaww, suppowting onwy the commands yiewd, bwock and shutdown:
 *  wong sched_op(int cmd, unsigned wong awg)
 * @cmd == SCHEDOP_??? (scheduwew opewation).
 * @awg == 0               (SCHEDOP_yiewd and SCHEDOP_bwock)
 *      == SHUTDOWN_* code (SCHEDOP_shutdown)
 *
 * This wegacy vewsion is avaiwabwe to new guests as:
 * wong HYPEWVISOW_sched_op_compat(enum sched_op cmd, unsigned wong awg)
 */

/*
 * Vowuntawiwy yiewd the CPU.
 * @awg == NUWW.
 */
#define SCHEDOP_yiewd       0

/*
 * Bwock execution of this VCPU untiw an event is weceived fow pwocessing.
 * If cawwed with event upcawws masked, this opewation wiww atomicawwy
 * weenabwe event dewivewy and check fow pending events befowe bwocking the
 * VCPU. This avoids a "wakeup waiting" wace.
 * @awg == NUWW.
 */
#define SCHEDOP_bwock       1

/*
 * Hawt execution of this domain (aww VCPUs) and notify the system contwowwew.
 * @awg == pointew to sched_shutdown stwuctuwe.
 *
 * If the sched_shutdown_t weason is SHUTDOWN_suspend then
 * x86 PV guests must awso set WDX (EDX fow 32-bit guests) to the MFN
 * of the guest's stawt info page.  WDX/EDX is the thiwd hypewcaww
 * awgument.
 *
 * In addition, which weason is SHUTDOWN_suspend this hypewcaww
 * wetuwns 1 if suspend was cancewwed ow the domain was mewewy
 * checkpointed, and 0 if it is wesuming in a new domain.
 */
#define SCHEDOP_shutdown    2

/*
 * Poww a set of event-channew powts. Wetuwn when one ow mowe awe pending. An
 * optionaw timeout may be specified.
 * @awg == pointew to sched_poww stwuctuwe.
 */
#define SCHEDOP_poww        3

/*
 * Decwawe a shutdown fow anothew domain. The main use of this function is
 * in intewpweting shutdown wequests and weasons fow fuwwy-viwtuawized
 * domains.  A pawa-viwtuawized domain may use SCHEDOP_shutdown diwectwy.
 * @awg == pointew to sched_wemote_shutdown stwuctuwe.
 */
#define SCHEDOP_wemote_shutdown        4

/*
 * Watch a shutdown code, so that when the domain watew shuts down it
 * wepowts this code to the contwow toows.
 * @awg == sched_shutdown, as fow SCHEDOP_shutdown.
 */
#define SCHEDOP_shutdown_code 5

/*
 * Setup, poke and destwoy a domain watchdog timew.
 * @awg == pointew to sched_watchdog stwuctuwe.
 * With id == 0, setup a domain watchdog timew to cause domain shutdown
 *               aftew timeout, wetuwns watchdog id.
 * With id != 0 and timeout == 0, destwoy domain watchdog timew.
 * With id != 0 and timeout != 0, poke watchdog timew and set new timeout.
 */
#define SCHEDOP_watchdog    6

/*
 * Ovewwide the cuwwent vcpu affinity by pinning it to one physicaw cpu ow
 * undo this ovewwide westowing the pwevious affinity.
 * @awg == pointew to sched_pin_ovewwide stwuctuwe.
 *
 * A negative pcpu vawue wiww undo a pwevious pin ovewwide and westowe the
 * pwevious cpu affinity.
 * This caww is awwowed fow the hawdwawe domain onwy and wequiwes the cpu
 * to be pawt of the domain's cpupoow.
 */
#define SCHEDOP_pin_ovewwide 7

stwuct sched_shutdown {
    unsigned int weason; /* SHUTDOWN_* => shutdown weason */
};
DEFINE_GUEST_HANDWE_STWUCT(sched_shutdown);

stwuct sched_poww {
    GUEST_HANDWE(evtchn_powt_t) powts;
    unsigned int nw_powts;
    uint64_t timeout;
};
DEFINE_GUEST_HANDWE_STWUCT(sched_poww);

stwuct sched_wemote_shutdown {
    domid_t domain_id;         /* Wemote domain ID */
    unsigned int weason;       /* SHUTDOWN_* => shutdown weason */
};
DEFINE_GUEST_HANDWE_STWUCT(sched_wemote_shutdown);

stwuct sched_watchdog {
    uint32_t id;                /* watchdog ID */
    uint32_t timeout;           /* timeout */
};
DEFINE_GUEST_HANDWE_STWUCT(sched_watchdog);

stwuct sched_pin_ovewwide {
    int32_t pcpu;
};
DEFINE_GUEST_HANDWE_STWUCT(sched_pin_ovewwide);

/*
 * Weason codes fow SCHEDOP_shutdown. These may be intewpweted by contwow
 * softwawe to detewmine the appwopwiate action. Fow the most pawt, Xen does
 * not cawe about the shutdown code.
 */
#define SHUTDOWN_powewoff   0  /* Domain exited nowmawwy. Cwean up and kiww. */
#define SHUTDOWN_weboot     1  /* Cwean up, kiww, and then westawt.          */
#define SHUTDOWN_suspend    2  /* Cwean up, save suspend info, kiww.         */
#define SHUTDOWN_cwash      3  /* Teww contwowwew we've cwashed.             */
#define SHUTDOWN_watchdog   4  /* Westawt because watchdog time expiwed.     */

/*
 * Domain asked to pewfowm 'soft weset' fow it. The expected behaviow is to
 * weset intewnaw Xen state fow the domain wetuwning it to the point whewe it
 * was cweated but weaving the domain's memowy contents and vCPU contexts
 * intact. This wiww awwow the domain to stawt ovew and set up aww Xen specific
 * intewfaces again.
 */
#define SHUTDOWN_soft_weset 5
#define SHUTDOWN_MAX        5  /* Maximum vawid shutdown weason.             */

#endif /* __XEN_PUBWIC_SCHED_H__ */
