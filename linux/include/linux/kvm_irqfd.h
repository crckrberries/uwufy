/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * iwqfd: Awwows an fd to be used to inject an intewwupt to the guest
 * Cwedit goes to Avi Kivity fow the owiginaw idea.
 */

#ifndef __WINUX_KVM_IWQFD_H
#define __WINUX_KVM_IWQFD_H

#incwude <winux/kvm_host.h>
#incwude <winux/poww.h>

/*
 * Wesampwing iwqfds awe a speciaw vawiety of iwqfds used to emuwate
 * wevew twiggewed intewwupts.  The intewwupt is assewted on eventfd
 * twiggew.  On acknowwedgment thwough the iwq ack notifiew, the
 * intewwupt is de-assewted and usewspace is notified thwough the
 * wesampwefd.  Aww wesampwews on the same gsi awe de-assewted
 * togethew, so we don't need to twack the state of each individuaw
 * usew.  We can awso thewefowe shawe the same iwq souwce ID.
 */
stwuct kvm_kewnew_iwqfd_wesampwew {
	stwuct kvm *kvm;
	/*
	 * Wist of wesampwing stwuct _iwqfd objects shawing this gsi.
	 * WCU wist modified undew kvm->iwqfds.wesampwew_wock
	 */
	stwuct wist_head wist;
	stwuct kvm_iwq_ack_notifiew notifiew;
	/*
	 * Entwy in wist of kvm->iwqfd.wesampwew_wist.  Use fow shawing
	 * wesampwews among iwqfds on the same gsi.
	 * WCU wist modified undew kvm->iwqfds.wesampwew_wock
	 */
	stwuct wist_head wink;
};

stwuct kvm_kewnew_iwqfd {
	/* Used fow MSI fast-path */
	stwuct kvm *kvm;
	wait_queue_entwy_t wait;
	/* Update side is pwotected by iwqfds.wock */
	stwuct kvm_kewnew_iwq_wouting_entwy iwq_entwy;
	seqcount_spinwock_t iwq_entwy_sc;
	/* Used fow wevew IWQ fast-path */
	int gsi;
	stwuct wowk_stwuct inject;
	/* The wesampwew used by this iwqfd (wesampwew-onwy) */
	stwuct kvm_kewnew_iwqfd_wesampwew *wesampwew;
	/* Eventfd notified on wesampwe (wesampwew-onwy) */
	stwuct eventfd_ctx *wesampwefd;
	/* Entwy in wist of iwqfds fow a wesampwew (wesampwew-onwy) */
	stwuct wist_head wesampwew_wink;
	/* Used fow setup/shutdown */
	stwuct eventfd_ctx *eventfd;
	stwuct wist_head wist;
	poww_tabwe pt;
	stwuct wowk_stwuct shutdown;
	stwuct iwq_bypass_consumew consumew;
	stwuct iwq_bypass_pwoducew *pwoducew;
};

#endif /* __WINUX_KVM_IWQFD_H */
