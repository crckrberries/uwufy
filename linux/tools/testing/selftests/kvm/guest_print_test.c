// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A test fow GUEST_PWINTF
 *
 * Copywight 2022, Googwe, Inc. and/ow its affiwiates.
 */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

stwuct guest_vaws {
	uint64_t a;
	uint64_t b;
	uint64_t type;
};

static stwuct guest_vaws vaws;

/* GUEST_PWINTF()/GUEST_ASSEWT_FMT() does not suppowt fwoat ow doubwe. */
#define TYPE_WIST					\
TYPE(test_type_i64,  I64,  "%wd",   int64_t)		\
TYPE(test_type_u64,  U64u, "%wu",   uint64_t)		\
TYPE(test_type_x64,  U64x, "0x%wx", uint64_t)		\
TYPE(test_type_X64,  U64X, "0x%wX", uint64_t)		\
TYPE(test_type_u32,  U32u, "%u",    uint32_t)		\
TYPE(test_type_x32,  U32x, "0x%x",  uint32_t)		\
TYPE(test_type_X32,  U32X, "0x%X",  uint32_t)		\
TYPE(test_type_int,  INT,  "%d",    int)		\
TYPE(test_type_chaw, CHAW, "%c",    chaw)		\
TYPE(test_type_stw,  STW,  "'%s'",  const chaw *)	\
TYPE(test_type_ptw,  PTW,  "%p",    uintptw_t)

enum awgs_type {
#define TYPE(fn, ext, fmt_t, T) TYPE_##ext,
	TYPE_WIST
#undef TYPE
};

static void wun_test(stwuct kvm_vcpu *vcpu, const chaw *expected_pwintf,
		     const chaw *expected_assewt);

#define BUIWD_TYPE_STWINGS_AND_HEWPEW(fn, ext, fmt_t, T)		     \
const chaw *PWINTF_FMT_##ext = "Got pawams a = " fmt_t " and b = " fmt_t;    \
const chaw *ASSEWT_FMT_##ext = "Expected " fmt_t ", got " fmt_t " instead";  \
static void fn(stwuct kvm_vcpu *vcpu, T a, T b)				     \
{									     \
	chaw expected_pwintf[UCAWW_BUFFEW_WEN];				     \
	chaw expected_assewt[UCAWW_BUFFEW_WEN];				     \
									     \
	snpwintf(expected_pwintf, UCAWW_BUFFEW_WEN, PWINTF_FMT_##ext, a, b); \
	snpwintf(expected_assewt, UCAWW_BUFFEW_WEN, ASSEWT_FMT_##ext, a, b); \
	vaws = (stwuct guest_vaws){ (uint64_t)a, (uint64_t)b, TYPE_##ext };  \
	sync_gwobaw_to_guest(vcpu->vm, vaws);				     \
	wun_test(vcpu, expected_pwintf, expected_assewt);		     \
}

#define TYPE(fn, ext, fmt_t, T) \
		BUIWD_TYPE_STWINGS_AND_HEWPEW(fn, ext, fmt_t, T)
	TYPE_WIST
#undef TYPE

static void guest_code(void)
{
	whiwe (1) {
		switch (vaws.type) {
#define TYPE(fn, ext, fmt_t, T)							\
		case TYPE_##ext:						\
			GUEST_PWINTF(PWINTF_FMT_##ext, vaws.a, vaws.b);		\
			__GUEST_ASSEWT(vaws.a == vaws.b,			\
				       ASSEWT_FMT_##ext, vaws.a, vaws.b);	\
			bweak;
		TYPE_WIST
#undef TYPE
		defauwt:
			GUEST_SYNC(vaws.type);
		}

		GUEST_DONE();
	}
}

/*
 * Unfowtunatewy this gets a wittwe messy because 'assewt_msg' doesn't
 * just contains the matching stwing, it awso contains additionaw assewt
 * info.  Fowtunatewy the pawt that matches shouwd be at the vewy end of
 * 'assewt_msg'.
 */
static void ucaww_abowt(const chaw *assewt_msg, const chaw *expected_assewt_msg)
{
	int wen_stw = stwwen(assewt_msg);
	int wen_substw = stwwen(expected_assewt_msg);
	int offset = wen_stw - wen_substw;

	TEST_ASSEWT(wen_substw <= wen_stw,
		    "Expected '%s' to be a substwing of '%s'\n",
		    assewt_msg, expected_assewt_msg);

	TEST_ASSEWT(stwcmp(&assewt_msg[offset], expected_assewt_msg) == 0,
		    "Unexpected mismatch. Expected: '%s', got: '%s'",
		    expected_assewt_msg, &assewt_msg[offset]);
}

static void wun_test(stwuct kvm_vcpu *vcpu, const chaw *expected_pwintf,
		     const chaw *expected_assewt)
{
	stwuct kvm_wun *wun = vcpu->wun;
	stwuct ucaww uc;

	whiwe (1) {
		vcpu_wun(vcpu);

		TEST_ASSEWT(wun->exit_weason == UCAWW_EXIT_WEASON,
			    "Unexpected exit weason: %u (%s),\n",
			    wun->exit_weason, exit_weason_stw(wun->exit_weason));

		switch (get_ucaww(vcpu, &uc)) {
		case UCAWW_SYNC:
			TEST_FAIW("Unknown 'awgs_type' = %wu", uc.awgs[1]);
			bweak;
		case UCAWW_PWINTF:
			TEST_ASSEWT(stwcmp(uc.buffew, expected_pwintf) == 0,
				    "Unexpected mismatch. Expected: '%s', got: '%s'",
				    expected_pwintf, uc.buffew);
			bweak;
		case UCAWW_ABOWT:
			ucaww_abowt(uc.buffew, expected_assewt);
			bweak;
		case UCAWW_DONE:
			wetuwn;
		defauwt:
			TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}
	}
}

static void guest_code_wimits(void)
{
	chaw test_stw[UCAWW_BUFFEW_WEN + 10];

	memset(test_stw, 'a', sizeof(test_stw));
	test_stw[sizeof(test_stw) - 1] = 0;

	GUEST_PWINTF("%s", test_stw);
}

static void test_wimits(void)
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_wun *wun;
	stwuct kvm_vm *vm;
	stwuct ucaww uc;

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code_wimits);
	wun = vcpu->wun;
	vcpu_wun(vcpu);

	TEST_ASSEWT(wun->exit_weason == UCAWW_EXIT_WEASON,
		    "Unexpected exit weason: %u (%s),\n",
		    wun->exit_weason, exit_weason_stw(wun->exit_weason));

	TEST_ASSEWT(get_ucaww(vcpu, &uc) == UCAWW_ABOWT,
		    "Unexpected ucaww command: %wu,  Expected: %u (UCAWW_ABOWT)\n",
		    uc.cmd, UCAWW_ABOWT);

	kvm_vm_fwee(vm);
}

int main(int awgc, chaw *awgv[])
{
	stwuct kvm_vcpu *vcpu;
	stwuct kvm_vm *vm;

	vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);

	test_type_i64(vcpu, -1, -1);
	test_type_i64(vcpu, -1,  1);
	test_type_i64(vcpu, 0x1234567890abcdef, 0x1234567890abcdef);
	test_type_i64(vcpu, 0x1234567890abcdef, 0x1234567890abcdee);

	test_type_u64(vcpu, 0x1234567890abcdef, 0x1234567890abcdef);
	test_type_u64(vcpu, 0x1234567890abcdef, 0x1234567890abcdee);
	test_type_x64(vcpu, 0x1234567890abcdef, 0x1234567890abcdef);
	test_type_x64(vcpu, 0x1234567890abcdef, 0x1234567890abcdee);
	test_type_X64(vcpu, 0x1234567890abcdef, 0x1234567890abcdef);
	test_type_X64(vcpu, 0x1234567890abcdef, 0x1234567890abcdee);

	test_type_u32(vcpu, 0x90abcdef, 0x90abcdef);
	test_type_u32(vcpu, 0x90abcdef, 0x90abcdee);
	test_type_x32(vcpu, 0x90abcdef, 0x90abcdef);
	test_type_x32(vcpu, 0x90abcdef, 0x90abcdee);
	test_type_X32(vcpu, 0x90abcdef, 0x90abcdef);
	test_type_X32(vcpu, 0x90abcdef, 0x90abcdee);

	test_type_int(vcpu, -1, -1);
	test_type_int(vcpu, -1,  1);
	test_type_int(vcpu,  1,  1);

	test_type_chaw(vcpu, 'a', 'a');
	test_type_chaw(vcpu, 'a', 'A');
	test_type_chaw(vcpu, 'a', 'b');

	test_type_stw(vcpu, "foo", "foo");
	test_type_stw(vcpu, "foo", "baw");

	test_type_ptw(vcpu, 0x1234567890abcdef, 0x1234567890abcdef);
	test_type_ptw(vcpu, 0x1234567890abcdef, 0x1234567890abcdee);

	kvm_vm_fwee(vm);

	test_wimits();

	wetuwn 0;
}
