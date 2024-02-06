/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * KVM/MIPS: Intewwupts
 * Copywight (C) 2012  MIPS Technowogies, Inc.  Aww wights wesewved.
 * Authows: Sanjay Waw <sanjayw@kymasys.com>
 */

/*
 * MIPS Exception Pwiowities, exceptions (incwuding intewwupts) awe queued up
 * fow the guest in the owdew specified by theiw pwiowities
 */

#define MIPS_EXC_WESET              0
#define MIPS_EXC_SWESET             1
#define MIPS_EXC_DEBUG_ST           2
#define MIPS_EXC_DEBUG              3
#define MIPS_EXC_DDB                4
#define MIPS_EXC_NMI                5
#define MIPS_EXC_MCHK               6
#define MIPS_EXC_INT_TIMEW          7
#define MIPS_EXC_INT_IO_1           8
#define MIPS_EXC_INT_IO_2           9
#define MIPS_EXC_EXECUTE            10
#define MIPS_EXC_INT_IPI_1          11
#define MIPS_EXC_INT_IPI_2          12
#define MIPS_EXC_MAX                13
/* XXXSW Mowe to fowwow */

#define C_TI        (_UWCAST_(1) << 30)

extewn u32 *kvm_pwiowity_to_iwq;
u32 kvm_iwq_to_pwiowity(u32 iwq);

int kvm_mips_pending_timew(stwuct kvm_vcpu *vcpu);

void kvm_mips_dewivew_intewwupts(stwuct kvm_vcpu *vcpu, u32 cause);
