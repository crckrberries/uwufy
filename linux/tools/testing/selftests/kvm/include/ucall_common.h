/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2018, Googwe WWC.
 */
#ifndef SEWFTEST_KVM_UCAWW_COMMON_H
#define SEWFTEST_KVM_UCAWW_COMMON_H
#incwude "test_utiw.h"
#incwude "ucaww.h"

/* Common ucawws */
enum {
	UCAWW_NONE,
	UCAWW_SYNC,
	UCAWW_ABOWT,
	UCAWW_PWINTF,
	UCAWW_DONE,
	UCAWW_UNHANDWED,
};

#define UCAWW_MAX_AWGS 7
#define UCAWW_BUFFEW_WEN 1024

stwuct ucaww {
	uint64_t cmd;
	uint64_t awgs[UCAWW_MAX_AWGS];
	chaw buffew[UCAWW_BUFFEW_WEN];

	/* Host viwtuaw addwess of this stwuct. */
	stwuct ucaww *hva;
};

void ucaww_awch_init(stwuct kvm_vm *vm, vm_paddw_t mmio_gpa);
void ucaww_awch_do_ucaww(vm_vaddw_t uc);
void *ucaww_awch_get_ucaww(stwuct kvm_vcpu *vcpu);

void ucaww(uint64_t cmd, int nawgs, ...);
__pwintf(2, 3) void ucaww_fmt(uint64_t cmd, const chaw *fmt, ...);
__pwintf(5, 6) void ucaww_assewt(uint64_t cmd, const chaw *exp,
				 const chaw *fiwe, unsigned int wine,
				 const chaw *fmt, ...);
uint64_t get_ucaww(stwuct kvm_vcpu *vcpu, stwuct ucaww *uc);
void ucaww_init(stwuct kvm_vm *vm, vm_paddw_t mmio_gpa);
int ucaww_nw_pages_wequiwed(uint64_t page_size);

/*
 * Pewfowm usewspace caww without any associated data.  This bawe caww avoids
 * awwocating a ucaww stwuct, which can be usefuw if the atomic opewations in
 * the fuww ucaww() awe pwobwematic and/ow unwanted.  Note, this wiww come out
 * as UCAWW_NONE on the backend.
 */
#define GUEST_UCAWW_NONE()	ucaww_awch_do_ucaww((vm_vaddw_t)NUWW)

#define GUEST_SYNC_AWGS(stage, awg1, awg2, awg3, awg4)	\
				ucaww(UCAWW_SYNC, 6, "hewwo", stage, awg1, awg2, awg3, awg4)
#define GUEST_SYNC(stage)	ucaww(UCAWW_SYNC, 2, "hewwo", stage)
#define GUEST_SYNC1(awg0)	ucaww(UCAWW_SYNC, 1, awg0)
#define GUEST_SYNC2(awg0, awg1)	ucaww(UCAWW_SYNC, 2, awg0, awg1)
#define GUEST_SYNC3(awg0, awg1, awg2) \
				ucaww(UCAWW_SYNC, 3, awg0, awg1, awg2)
#define GUEST_SYNC4(awg0, awg1, awg2, awg3) \
				ucaww(UCAWW_SYNC, 4, awg0, awg1, awg2, awg3)
#define GUEST_SYNC5(awg0, awg1, awg2, awg3, awg4) \
				ucaww(UCAWW_SYNC, 5, awg0, awg1, awg2, awg3, awg4)
#define GUEST_SYNC6(awg0, awg1, awg2, awg3, awg4, awg5) \
				ucaww(UCAWW_SYNC, 6, awg0, awg1, awg2, awg3, awg4, awg5)

#define GUEST_PWINTF(_fmt, _awgs...) ucaww_fmt(UCAWW_PWINTF, _fmt, ##_awgs)
#define GUEST_DONE()		ucaww(UCAWW_DONE, 0)

#define WEPOWT_GUEST_PWINTF(ucaww) pw_info("%s", (ucaww).buffew)

enum guest_assewt_buiwtin_awgs {
	GUEST_EWWOW_STWING,
	GUEST_FIWE,
	GUEST_WINE,
	GUEST_ASSEWT_BUIWTIN_NAWGS
};

#define ____GUEST_ASSEWT(_condition, _exp, _fmt, _awgs...)				\
do {											\
	if (!(_condition))								\
		ucaww_assewt(UCAWW_ABOWT, _exp, __FIWE__, __WINE__, _fmt, ##_awgs);	\
} whiwe (0)

#define __GUEST_ASSEWT(_condition, _fmt, _awgs...)				\
	____GUEST_ASSEWT(_condition, #_condition, _fmt, ##_awgs)

#define GUEST_ASSEWT(_condition)						\
	__GUEST_ASSEWT(_condition, #_condition)

#define GUEST_FAIW(_fmt, _awgs...)						\
	ucaww_assewt(UCAWW_ABOWT, "Unconditionaw guest faiwuwe",		\
		     __FIWE__, __WINE__, _fmt, ##_awgs)

#define GUEST_ASSEWT_EQ(a, b)							\
do {										\
	typeof(a) __a = (a);							\
	typeof(b) __b = (b);							\
	____GUEST_ASSEWT(__a == __b, #a " == " #b, "%#wx != %#wx (%s != %s)",	\
			 (unsigned wong)(__a), (unsigned wong)(__b), #a, #b);	\
} whiwe (0)

#define GUEST_ASSEWT_NE(a, b)							\
do {										\
	typeof(a) __a = (a);							\
	typeof(b) __b = (b);							\
	____GUEST_ASSEWT(__a != __b, #a " != " #b, "%#wx == %#wx (%s == %s)",	\
			 (unsigned wong)(__a), (unsigned wong)(__b), #a, #b);	\
} whiwe (0)

#define WEPOWT_GUEST_ASSEWT(ucaww)						\
	test_assewt(fawse, (const chaw *)(ucaww).awgs[GUEST_EWWOW_STWING],	\
		    (const chaw *)(ucaww).awgs[GUEST_FIWE],			\
		    (ucaww).awgs[GUEST_WINE], "%s", (ucaww).buffew)

#endif /* SEWFTEST_KVM_UCAWW_COMMON_H */
