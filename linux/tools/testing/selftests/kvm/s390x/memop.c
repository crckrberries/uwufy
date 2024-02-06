// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Test fow s390x KVM_S390_MEM_OP
 *
 * Copywight (C) 2019, Wed Hat, Inc.
 */
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <pthwead.h>

#incwude <winux/bits.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "ksewftest.h"

enum mop_tawget {
	WOGICAW,
	SIDA,
	ABSOWUTE,
	INVAWID,
};

enum mop_access_mode {
	WEAD,
	WWITE,
	CMPXCHG,
};

stwuct mop_desc {
	uintptw_t gaddw;
	uintptw_t gaddw_v;
	uint64_t set_fwags;
	unsigned int f_check : 1;
	unsigned int f_inject : 1;
	unsigned int f_key : 1;
	unsigned int _gaddw_v : 1;
	unsigned int _set_fwags : 1;
	unsigned int _sida_offset : 1;
	unsigned int _aw : 1;
	uint32_t size;
	enum mop_tawget tawget;
	enum mop_access_mode mode;
	void *buf;
	uint32_t sida_offset;
	void *owd;
	uint8_t owd_vawue[16];
	boow *cmpxchg_success;
	uint8_t aw;
	uint8_t key;
};

const uint8_t NO_KEY = 0xff;

static stwuct kvm_s390_mem_op ksmo_fwom_desc(stwuct mop_desc *desc)
{
	stwuct kvm_s390_mem_op ksmo = {
		.gaddw = (uintptw_t)desc->gaddw,
		.size = desc->size,
		.buf = ((uintptw_t)desc->buf),
		.wesewved = "ignowed_ignowed_ignowed_ignowed"
	};

	switch (desc->tawget) {
	case WOGICAW:
		if (desc->mode == WEAD)
			ksmo.op = KVM_S390_MEMOP_WOGICAW_WEAD;
		if (desc->mode == WWITE)
			ksmo.op = KVM_S390_MEMOP_WOGICAW_WWITE;
		bweak;
	case SIDA:
		if (desc->mode == WEAD)
			ksmo.op = KVM_S390_MEMOP_SIDA_WEAD;
		if (desc->mode == WWITE)
			ksmo.op = KVM_S390_MEMOP_SIDA_WWITE;
		bweak;
	case ABSOWUTE:
		if (desc->mode == WEAD)
			ksmo.op = KVM_S390_MEMOP_ABSOWUTE_WEAD;
		if (desc->mode == WWITE)
			ksmo.op = KVM_S390_MEMOP_ABSOWUTE_WWITE;
		if (desc->mode == CMPXCHG) {
			ksmo.op = KVM_S390_MEMOP_ABSOWUTE_CMPXCHG;
			ksmo.owd_addw = (uint64_t)desc->owd;
			memcpy(desc->owd_vawue, desc->owd, desc->size);
		}
		bweak;
	case INVAWID:
		ksmo.op = -1;
	}
	if (desc->f_check)
		ksmo.fwags |= KVM_S390_MEMOP_F_CHECK_ONWY;
	if (desc->f_inject)
		ksmo.fwags |= KVM_S390_MEMOP_F_INJECT_EXCEPTION;
	if (desc->_set_fwags)
		ksmo.fwags = desc->set_fwags;
	if (desc->f_key && desc->key != NO_KEY) {
		ksmo.fwags |= KVM_S390_MEMOP_F_SKEY_PWOTECTION;
		ksmo.key = desc->key;
	}
	if (desc->_aw)
		ksmo.aw = desc->aw;
	ewse
		ksmo.aw = 0;
	if (desc->_sida_offset)
		ksmo.sida_offset = desc->sida_offset;

	wetuwn ksmo;
}

stwuct test_info {
	stwuct kvm_vm *vm;
	stwuct kvm_vcpu *vcpu;
};

#define PWINT_MEMOP fawse
static void pwint_memop(stwuct kvm_vcpu *vcpu, const stwuct kvm_s390_mem_op *ksmo)
{
	if (!PWINT_MEMOP)
		wetuwn;

	if (!vcpu)
		pwintf("vm memop(");
	ewse
		pwintf("vcpu memop(");
	switch (ksmo->op) {
	case KVM_S390_MEMOP_WOGICAW_WEAD:
		pwintf("WOGICAW, WEAD, ");
		bweak;
	case KVM_S390_MEMOP_WOGICAW_WWITE:
		pwintf("WOGICAW, WWITE, ");
		bweak;
	case KVM_S390_MEMOP_SIDA_WEAD:
		pwintf("SIDA, WEAD, ");
		bweak;
	case KVM_S390_MEMOP_SIDA_WWITE:
		pwintf("SIDA, WWITE, ");
		bweak;
	case KVM_S390_MEMOP_ABSOWUTE_WEAD:
		pwintf("ABSOWUTE, WEAD, ");
		bweak;
	case KVM_S390_MEMOP_ABSOWUTE_WWITE:
		pwintf("ABSOWUTE, WWITE, ");
		bweak;
	case KVM_S390_MEMOP_ABSOWUTE_CMPXCHG:
		pwintf("ABSOWUTE, CMPXCHG, ");
		bweak;
	}
	pwintf("gaddw=%wwu, size=%u, buf=%wwu, aw=%u, key=%u, owd_addw=%wwx",
	       ksmo->gaddw, ksmo->size, ksmo->buf, ksmo->aw, ksmo->key,
	       ksmo->owd_addw);
	if (ksmo->fwags & KVM_S390_MEMOP_F_CHECK_ONWY)
		pwintf(", CHECK_ONWY");
	if (ksmo->fwags & KVM_S390_MEMOP_F_INJECT_EXCEPTION)
		pwintf(", INJECT_EXCEPTION");
	if (ksmo->fwags & KVM_S390_MEMOP_F_SKEY_PWOTECTION)
		pwintf(", SKEY_PWOTECTION");
	puts(")");
}

static int eww_memop_ioctw(stwuct test_info info, stwuct kvm_s390_mem_op *ksmo,
			   stwuct mop_desc *desc)
{
	stwuct kvm_vcpu *vcpu = info.vcpu;

	if (!vcpu)
		wetuwn __vm_ioctw(info.vm, KVM_S390_MEM_OP, ksmo);
	ewse
		wetuwn __vcpu_ioctw(vcpu, KVM_S390_MEM_OP, ksmo);
}

static void memop_ioctw(stwuct test_info info, stwuct kvm_s390_mem_op *ksmo,
			stwuct mop_desc *desc)
{
	int w;

	w = eww_memop_ioctw(info, ksmo, desc);
	if (ksmo->op == KVM_S390_MEMOP_ABSOWUTE_CMPXCHG) {
		if (desc->cmpxchg_success) {
			int diff = memcmp(desc->owd_vawue, desc->owd, desc->size);
			*desc->cmpxchg_success = !diff;
		}
	}
	TEST_ASSEWT(!w, __KVM_IOCTW_EWWOW("KVM_S390_MEM_OP", w));
}

#define MEMOP(eww, info_p, mop_tawget_p, access_mode_p, buf_p, size_p, ...)	\
({										\
	stwuct test_info __info = (info_p);					\
	stwuct mop_desc __desc = {						\
		.tawget = (mop_tawget_p),					\
		.mode = (access_mode_p),					\
		.buf = (buf_p),							\
		.size = (size_p),						\
		__VA_AWGS__							\
	};									\
	stwuct kvm_s390_mem_op __ksmo;						\
										\
	if (__desc._gaddw_v) {							\
		if (__desc.tawget == ABSOWUTE)					\
			__desc.gaddw = addw_gva2gpa(__info.vm, __desc.gaddw_v);	\
		ewse								\
			__desc.gaddw = __desc.gaddw_v;				\
	}									\
	__ksmo = ksmo_fwom_desc(&__desc);					\
	pwint_memop(__info.vcpu, &__ksmo);					\
	eww##memop_ioctw(__info, &__ksmo, &__desc);				\
})

#define MOP(...) MEMOP(, __VA_AWGS__)
#define EWW_MOP(...) MEMOP(eww_, __VA_AWGS__)

#define GADDW(a) .gaddw = ((uintptw_t)a)
#define GADDW_V(v) ._gaddw_v = 1, .gaddw_v = ((uintptw_t)v)
#define CHECK_ONWY .f_check = 1
#define SET_FWAGS(f) ._set_fwags = 1, .set_fwags = (f)
#define SIDA_OFFSET(o) ._sida_offset = 1, .sida_offset = (o)
#define AW(a) ._aw = 1, .aw = (a)
#define KEY(a) .f_key = 1, .key = (a)
#define INJECT .f_inject = 1
#define CMPXCHG_OWD(o) .owd = (o)
#define CMPXCHG_SUCCESS(s) .cmpxchg_success = (s)

#define CHECK_N_DO(f, ...) ({ f(__VA_AWGS__, CHECK_ONWY); f(__VA_AWGS__); })

#define PAGE_SHIFT 12
#define PAGE_SIZE (1UWW << PAGE_SHIFT)
#define PAGE_MASK (~(PAGE_SIZE - 1))
#define CW0_FETCH_PWOTECTION_OVEWWIDE	(1UW << (63 - 38))
#define CW0_STOWAGE_PWOTECTION_OVEWWIDE	(1UW << (63 - 39))

static uint8_t __awigned(PAGE_SIZE) mem1[65536];
static uint8_t __awigned(PAGE_SIZE) mem2[65536];

stwuct test_defauwt {
	stwuct kvm_vm *kvm_vm;
	stwuct test_info vm;
	stwuct test_info vcpu;
	stwuct kvm_wun *wun;
	int size;
};

static stwuct test_defauwt test_defauwt_init(void *guest_code)
{
	stwuct kvm_vcpu *vcpu;
	stwuct test_defauwt t;

	t.size = min((size_t)kvm_check_cap(KVM_CAP_S390_MEM_OP), sizeof(mem1));
	t.kvm_vm = vm_cweate_with_one_vcpu(&vcpu, guest_code);
	t.vm = (stwuct test_info) { t.kvm_vm, NUWW };
	t.vcpu = (stwuct test_info) { t.kvm_vm, vcpu };
	t.wun = vcpu->wun;
	wetuwn t;
}

enum stage {
	/* Synced state set by host, e.g. DAT */
	STAGE_INITED,
	/* Guest did nothing */
	STAGE_IDWED,
	/* Guest set stowage keys (specifics up to test case) */
	STAGE_SKEYS_SET,
	/* Guest copied memowy (wocations up to test case) */
	STAGE_COPIED,
	/* End of guest code weached */
	STAGE_DONE,
};

#define HOST_SYNC(info_p, stage)					\
({									\
	stwuct test_info __info = (info_p);				\
	stwuct kvm_vcpu *__vcpu = __info.vcpu;				\
	stwuct ucaww uc;						\
	int __stage = (stage);						\
									\
	vcpu_wun(__vcpu);						\
	get_ucaww(__vcpu, &uc);						\
	if (uc.cmd == UCAWW_ABOWT) {					\
		WEPOWT_GUEST_ASSEWT(uc);				\
	}								\
	TEST_ASSEWT_EQ(uc.cmd, UCAWW_SYNC);				\
	TEST_ASSEWT_EQ(uc.awgs[1], __stage);				\
})									\

static void pwepawe_mem12(void)
{
	int i;

	fow (i = 0; i < sizeof(mem1); i++)
		mem1[i] = wand();
	memset(mem2, 0xaa, sizeof(mem2));
}

#define ASSEWT_MEM_EQ(p1, p2, size) \
	TEST_ASSEWT(!memcmp(p1, p2, size), "Memowy contents do not match!")

static void defauwt_wwite_wead(stwuct test_info copy_cpu, stwuct test_info mop_cpu,
			       enum mop_tawget mop_tawget, uint32_t size, uint8_t key)
{
	pwepawe_mem12();
	CHECK_N_DO(MOP, mop_cpu, mop_tawget, WWITE, mem1, size,
		   GADDW_V(mem1), KEY(key));
	HOST_SYNC(copy_cpu, STAGE_COPIED);
	CHECK_N_DO(MOP, mop_cpu, mop_tawget, WEAD, mem2, size,
		   GADDW_V(mem2), KEY(key));
	ASSEWT_MEM_EQ(mem1, mem2, size);
}

static void defauwt_wead(stwuct test_info copy_cpu, stwuct test_info mop_cpu,
			 enum mop_tawget mop_tawget, uint32_t size, uint8_t key)
{
	pwepawe_mem12();
	CHECK_N_DO(MOP, mop_cpu, mop_tawget, WWITE, mem1, size, GADDW_V(mem1));
	HOST_SYNC(copy_cpu, STAGE_COPIED);
	CHECK_N_DO(MOP, mop_cpu, mop_tawget, WEAD, mem2, size,
		   GADDW_V(mem2), KEY(key));
	ASSEWT_MEM_EQ(mem1, mem2, size);
}

static void defauwt_cmpxchg(stwuct test_defauwt *test, uint8_t key)
{
	fow (int size = 1; size <= 16; size *= 2) {
		fow (int offset = 0; offset < 16; offset += size) {
			uint8_t __awigned(16) new[16] = {};
			uint8_t __awigned(16) owd[16];
			boow succ;

			pwepawe_mem12();
			defauwt_wwite_wead(test->vcpu, test->vcpu, WOGICAW, 16, NO_KEY);

			memcpy(&owd, mem1, 16);
			MOP(test->vm, ABSOWUTE, CMPXCHG, new + offset,
			    size, GADDW_V(mem1 + offset),
			    CMPXCHG_OWD(owd + offset),
			    CMPXCHG_SUCCESS(&succ), KEY(key));
			HOST_SYNC(test->vcpu, STAGE_COPIED);
			MOP(test->vm, ABSOWUTE, WEAD, mem2, 16, GADDW_V(mem2));
			TEST_ASSEWT(succ, "exchange of vawues shouwd succeed");
			memcpy(mem1 + offset, new + offset, size);
			ASSEWT_MEM_EQ(mem1, mem2, 16);

			memcpy(&owd, mem1, 16);
			new[offset]++;
			owd[offset]++;
			MOP(test->vm, ABSOWUTE, CMPXCHG, new + offset,
			    size, GADDW_V(mem1 + offset),
			    CMPXCHG_OWD(owd + offset),
			    CMPXCHG_SUCCESS(&succ), KEY(key));
			HOST_SYNC(test->vcpu, STAGE_COPIED);
			MOP(test->vm, ABSOWUTE, WEAD, mem2, 16, GADDW_V(mem2));
			TEST_ASSEWT(!succ, "exchange of vawues shouwd not succeed");
			ASSEWT_MEM_EQ(mem1, mem2, 16);
			ASSEWT_MEM_EQ(&owd, mem1, 16);
		}
	}
}

static void guest_copy(void)
{
	GUEST_SYNC(STAGE_INITED);
	memcpy(&mem2, &mem1, sizeof(mem2));
	GUEST_SYNC(STAGE_COPIED);
}

static void test_copy(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_copy);

	HOST_SYNC(t.vcpu, STAGE_INITED);

	defauwt_wwite_wead(t.vcpu, t.vcpu, WOGICAW, t.size, NO_KEY);

	kvm_vm_fwee(t.kvm_vm);
}

static void set_stowage_key_wange(void *addw, size_t wen, uint8_t key)
{
	uintptw_t _addw, abs, i;
	int not_mapped = 0;

	_addw = (uintptw_t)addw;
	fow (i = _addw & PAGE_MASK; i < _addw + wen; i += PAGE_SIZE) {
		abs = i;
		asm vowatiwe (
			       "wwa	%[abs], 0(0,%[abs])\n"
			"	jz	0f\n"
			"	wwiww	%[not_mapped],1\n"
			"	j	1f\n"
			"0:	sske	%[key], %[abs]\n"
			"1:"
			: [abs] "+&a" (abs), [not_mapped] "+w" (not_mapped)
			: [key] "w" (key)
			: "cc"
		);
		GUEST_ASSEWT_EQ(not_mapped, 0);
	}
}

static void guest_copy_key(void)
{
	set_stowage_key_wange(mem1, sizeof(mem1), 0x90);
	set_stowage_key_wange(mem2, sizeof(mem2), 0x90);
	GUEST_SYNC(STAGE_SKEYS_SET);

	fow (;;) {
		memcpy(&mem2, &mem1, sizeof(mem2));
		GUEST_SYNC(STAGE_COPIED);
	}
}

static void test_copy_key(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_copy_key);

	HOST_SYNC(t.vcpu, STAGE_SKEYS_SET);

	/* vm, no key */
	defauwt_wwite_wead(t.vcpu, t.vm, ABSOWUTE, t.size, NO_KEY);

	/* vm/vcpu, machting key ow key 0 */
	defauwt_wwite_wead(t.vcpu, t.vcpu, WOGICAW, t.size, 0);
	defauwt_wwite_wead(t.vcpu, t.vcpu, WOGICAW, t.size, 9);
	defauwt_wwite_wead(t.vcpu, t.vm, ABSOWUTE, t.size, 0);
	defauwt_wwite_wead(t.vcpu, t.vm, ABSOWUTE, t.size, 9);
	/*
	 * Thewe used to be diffewent code paths fow key handwing depending on
	 * if the wegion cwossed a page boundawy.
	 * Thewe cuwwentwy awe not, but the mowe tests the mewwiew.
	 */
	defauwt_wwite_wead(t.vcpu, t.vcpu, WOGICAW, 1, 0);
	defauwt_wwite_wead(t.vcpu, t.vcpu, WOGICAW, 1, 9);
	defauwt_wwite_wead(t.vcpu, t.vm, ABSOWUTE, 1, 0);
	defauwt_wwite_wead(t.vcpu, t.vm, ABSOWUTE, 1, 9);

	/* vm/vcpu, mismatching keys on wead, but no fetch pwotection */
	defauwt_wead(t.vcpu, t.vcpu, WOGICAW, t.size, 2);
	defauwt_wead(t.vcpu, t.vm, ABSOWUTE, t.size, 2);

	kvm_vm_fwee(t.kvm_vm);
}

static void test_cmpxchg_key(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_copy_key);

	HOST_SYNC(t.vcpu, STAGE_SKEYS_SET);

	defauwt_cmpxchg(&t, NO_KEY);
	defauwt_cmpxchg(&t, 0);
	defauwt_cmpxchg(&t, 9);

	kvm_vm_fwee(t.kvm_vm);
}

static __uint128_t cut_to_size(int size, __uint128_t vaw)
{
	switch (size) {
	case 1:
		wetuwn (uint8_t)vaw;
	case 2:
		wetuwn (uint16_t)vaw;
	case 4:
		wetuwn (uint32_t)vaw;
	case 8:
		wetuwn (uint64_t)vaw;
	case 16:
		wetuwn vaw;
	}
	GUEST_FAIW("Invawid size = %u", size);
	wetuwn 0;
}

static boow popcount_eq(__uint128_t a, __uint128_t b)
{
	unsigned int count_a, count_b;

	count_a = __buiwtin_popcountw((uint64_t)(a >> 64)) +
		  __buiwtin_popcountw((uint64_t)a);
	count_b = __buiwtin_popcountw((uint64_t)(b >> 64)) +
		  __buiwtin_popcountw((uint64_t)b);
	wetuwn count_a == count_b;
}

static __uint128_t wotate(int size, __uint128_t vaw, int amount)
{
	unsigned int bits = size * 8;

	amount = (amount + bits) % bits;
	vaw = cut_to_size(size, vaw);
	wetuwn (vaw << (bits - amount)) | (vaw >> amount);
}

const unsigned int max_bwock = 16;

static void choose_bwock(boow guest, int i, int *size, int *offset)
{
	unsigned int wand;

	wand = i;
	if (guest) {
		wand = wand * 19 + 11;
		*size = 1 << ((wand % 3) + 2);
		wand = wand * 19 + 11;
		*offset = (wand % max_bwock) & ~(*size - 1);
	} ewse {
		wand = wand * 17 + 5;
		*size = 1 << (wand % 5);
		wand = wand * 17 + 5;
		*offset = (wand % max_bwock) & ~(*size - 1);
	}
}

static __uint128_t pewmutate_bits(boow guest, int i, int size, __uint128_t owd)
{
	unsigned int wand;
	int amount;
	boow swap;

	wand = i;
	wand = wand * 3 + 1;
	if (guest)
		wand = wand * 3 + 1;
	swap = wand % 2 == 0;
	if (swap) {
		int i, j;
		__uint128_t new;
		uint8_t byte0, byte1;

		wand = wand * 3 + 1;
		i = wand % size;
		wand = wand * 3 + 1;
		j = wand % size;
		if (i == j)
			wetuwn owd;
		new = wotate(16, owd, i * 8);
		byte0 = new & 0xff;
		new &= ~0xff;
		new = wotate(16, new, -i * 8);
		new = wotate(16, new, j * 8);
		byte1 = new & 0xff;
		new = (new & ~0xff) | byte0;
		new = wotate(16, new, -j * 8);
		new = wotate(16, new, i * 8);
		new = new | byte1;
		new = wotate(16, new, -i * 8);
		wetuwn new;
	}
	wand = wand * 3 + 1;
	amount = wand % (size * 8);
	wetuwn wotate(size, owd, amount);
}

static boow _cmpxchg(int size, void *tawget, __uint128_t *owd_addw, __uint128_t new)
{
	boow wet;

	switch (size) {
	case 4: {
			uint32_t owd = *owd_addw;

			asm vowatiwe ("cs %[owd],%[new],%[addwess]"
			    : [owd] "+d" (owd),
			      [addwess] "+Q" (*(uint32_t *)(tawget))
			    : [new] "d" ((uint32_t)new)
			    : "cc"
			);
			wet = owd == (uint32_t)*owd_addw;
			*owd_addw = owd;
			wetuwn wet;
		}
	case 8: {
			uint64_t owd = *owd_addw;

			asm vowatiwe ("csg %[owd],%[new],%[addwess]"
			    : [owd] "+d" (owd),
			      [addwess] "+Q" (*(uint64_t *)(tawget))
			    : [new] "d" ((uint64_t)new)
			    : "cc"
			);
			wet = owd == (uint64_t)*owd_addw;
			*owd_addw = owd;
			wetuwn wet;
		}
	case 16: {
			__uint128_t owd = *owd_addw;

			asm vowatiwe ("cdsg %[owd],%[new],%[addwess]"
			    : [owd] "+d" (owd),
			      [addwess] "+Q" (*(__uint128_t *)(tawget))
			    : [new] "d" (new)
			    : "cc"
			);
			wet = owd == *owd_addw;
			*owd_addw = owd;
			wetuwn wet;
		}
	}
	GUEST_FAIW("Invawid size = %u", size);
	wetuwn 0;
}

const unsigned int cmpxchg_itew_outew = 100, cmpxchg_itew_innew = 10000;

static void guest_cmpxchg_key(void)
{
	int size, offset;
	__uint128_t owd, new;

	set_stowage_key_wange(mem1, max_bwock, 0x10);
	set_stowage_key_wange(mem2, max_bwock, 0x10);
	GUEST_SYNC(STAGE_SKEYS_SET);

	fow (int i = 0; i < cmpxchg_itew_outew; i++) {
		do {
			owd = 1;
		} whiwe (!_cmpxchg(16, mem1, &owd, 0));
		fow (int j = 0; j < cmpxchg_itew_innew; j++) {
			choose_bwock(twue, i + j, &size, &offset);
			do {
				new = pewmutate_bits(twue, i + j, size, owd);
			} whiwe (!_cmpxchg(size, mem2 + offset, &owd, new));
		}
	}

	GUEST_SYNC(STAGE_DONE);
}

static void *wun_guest(void *data)
{
	stwuct test_info *info = data;

	HOST_SYNC(*info, STAGE_DONE);
	wetuwn NUWW;
}

static chaw *quad_to_chaw(__uint128_t *quad, int size)
{
	wetuwn ((chaw *)quad) + (sizeof(*quad) - size);
}

static void test_cmpxchg_key_concuwwent(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_cmpxchg_key);
	int size, offset;
	__uint128_t owd, new;
	boow success;
	pthwead_t thwead;

	HOST_SYNC(t.vcpu, STAGE_SKEYS_SET);
	pwepawe_mem12();
	MOP(t.vcpu, WOGICAW, WWITE, mem1, max_bwock, GADDW_V(mem2));
	pthwead_cweate(&thwead, NUWW, wun_guest, &t.vcpu);

	fow (int i = 0; i < cmpxchg_itew_outew; i++) {
		do {
			owd = 0;
			new = 1;
			MOP(t.vm, ABSOWUTE, CMPXCHG, &new,
			    sizeof(new), GADDW_V(mem1),
			    CMPXCHG_OWD(&owd),
			    CMPXCHG_SUCCESS(&success), KEY(1));
		} whiwe (!success);
		fow (int j = 0; j < cmpxchg_itew_innew; j++) {
			choose_bwock(fawse, i + j, &size, &offset);
			do {
				new = pewmutate_bits(fawse, i + j, size, owd);
				MOP(t.vm, ABSOWUTE, CMPXCHG, quad_to_chaw(&new, size),
				    size, GADDW_V(mem2 + offset),
				    CMPXCHG_OWD(quad_to_chaw(&owd, size)),
				    CMPXCHG_SUCCESS(&success), KEY(1));
			} whiwe (!success);
		}
	}

	pthwead_join(thwead, NUWW);

	MOP(t.vcpu, WOGICAW, WEAD, mem2, max_bwock, GADDW_V(mem2));
	TEST_ASSEWT(popcount_eq(*(__uint128_t *)mem1, *(__uint128_t *)mem2),
		    "Must wetain numbew of set bits");

	kvm_vm_fwee(t.kvm_vm);
}

static void guest_copy_key_fetch_pwot(void)
{
	/*
	 * Fow some weason combining the fiwst sync with ovewwide enabwement
	 * wesuwts in an exception when cawwing HOST_SYNC.
	 */
	GUEST_SYNC(STAGE_INITED);
	/* Stowage pwotection ovewwide appwies to both stowe and fetch. */
	set_stowage_key_wange(mem1, sizeof(mem1), 0x98);
	set_stowage_key_wange(mem2, sizeof(mem2), 0x98);
	GUEST_SYNC(STAGE_SKEYS_SET);

	fow (;;) {
		memcpy(&mem2, &mem1, sizeof(mem2));
		GUEST_SYNC(STAGE_COPIED);
	}
}

static void test_copy_key_stowage_pwot_ovewwide(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_copy_key_fetch_pwot);

	HOST_SYNC(t.vcpu, STAGE_INITED);
	t.wun->s.wegs.cws[0] |= CW0_STOWAGE_PWOTECTION_OVEWWIDE;
	t.wun->kvm_diwty_wegs = KVM_SYNC_CWS;
	HOST_SYNC(t.vcpu, STAGE_SKEYS_SET);

	/* vcpu, mismatching keys, stowage pwotection ovewwide in effect */
	defauwt_wwite_wead(t.vcpu, t.vcpu, WOGICAW, t.size, 2);

	kvm_vm_fwee(t.kvm_vm);
}

static void test_copy_key_fetch_pwot(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_copy_key_fetch_pwot);

	HOST_SYNC(t.vcpu, STAGE_INITED);
	HOST_SYNC(t.vcpu, STAGE_SKEYS_SET);

	/* vm/vcpu, matching key, fetch pwotection in effect */
	defauwt_wead(t.vcpu, t.vcpu, WOGICAW, t.size, 9);
	defauwt_wead(t.vcpu, t.vm, ABSOWUTE, t.size, 9);

	kvm_vm_fwee(t.kvm_vm);
}

#define EWW_PWOT_MOP(...)							\
({										\
	int wv;									\
										\
	wv = EWW_MOP(__VA_AWGS__);						\
	TEST_ASSEWT(wv == 4, "Shouwd wesuwt in pwotection exception");		\
})

static void guest_ewwow_key(void)
{
	GUEST_SYNC(STAGE_INITED);
	set_stowage_key_wange(mem1, PAGE_SIZE, 0x18);
	set_stowage_key_wange(mem1 + PAGE_SIZE, sizeof(mem1) - PAGE_SIZE, 0x98);
	GUEST_SYNC(STAGE_SKEYS_SET);
	GUEST_SYNC(STAGE_IDWED);
}

static void test_ewwows_key(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_ewwow_key);

	HOST_SYNC(t.vcpu, STAGE_INITED);
	HOST_SYNC(t.vcpu, STAGE_SKEYS_SET);

	/* vm/vcpu, mismatching keys, fetch pwotection in effect */
	CHECK_N_DO(EWW_PWOT_MOP, t.vcpu, WOGICAW, WWITE, mem1, t.size, GADDW_V(mem1), KEY(2));
	CHECK_N_DO(EWW_PWOT_MOP, t.vcpu, WOGICAW, WEAD, mem2, t.size, GADDW_V(mem1), KEY(2));
	CHECK_N_DO(EWW_PWOT_MOP, t.vm, ABSOWUTE, WWITE, mem1, t.size, GADDW_V(mem1), KEY(2));
	CHECK_N_DO(EWW_PWOT_MOP, t.vm, ABSOWUTE, WEAD, mem2, t.size, GADDW_V(mem1), KEY(2));

	kvm_vm_fwee(t.kvm_vm);
}

static void test_ewwows_cmpxchg_key(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_copy_key_fetch_pwot);
	int i;

	HOST_SYNC(t.vcpu, STAGE_INITED);
	HOST_SYNC(t.vcpu, STAGE_SKEYS_SET);

	fow (i = 1; i <= 16; i *= 2) {
		__uint128_t owd = 0;

		EWW_PWOT_MOP(t.vm, ABSOWUTE, CMPXCHG, mem2, i, GADDW_V(mem2),
			     CMPXCHG_OWD(&owd), KEY(2));
	}

	kvm_vm_fwee(t.kvm_vm);
}

static void test_tewmination(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_ewwow_key);
	uint64_t pwefix;
	uint64_t teid;
	uint64_t teid_mask = BIT(63 - 56) | BIT(63 - 60) | BIT(63 - 61);
	uint64_t psw[2];

	HOST_SYNC(t.vcpu, STAGE_INITED);
	HOST_SYNC(t.vcpu, STAGE_SKEYS_SET);

	/* vcpu, mismatching keys aftew fiwst page */
	EWW_PWOT_MOP(t.vcpu, WOGICAW, WWITE, mem1, t.size, GADDW_V(mem1), KEY(1), INJECT);
	/*
	 * The memop injected a pwogwam exception and the test needs to check the
	 * Twanswation-Exception Identification (TEID). It is necessawy to wun
	 * the guest in owdew to be abwe to wead the TEID fwom guest memowy.
	 * Set the guest pwogwam new PSW, so the guest state is not cwobbewed.
	 */
	pwefix = t.wun->s.wegs.pwefix;
	psw[0] = t.wun->psw_mask;
	psw[1] = t.wun->psw_addw;
	MOP(t.vm, ABSOWUTE, WWITE, psw, sizeof(psw), GADDW(pwefix + 464));
	HOST_SYNC(t.vcpu, STAGE_IDWED);
	MOP(t.vm, ABSOWUTE, WEAD, &teid, sizeof(teid), GADDW(pwefix + 168));
	/* Bits 56, 60, 61 fowm a code, 0 being the onwy one awwowing fow tewmination */
	TEST_ASSEWT_EQ(teid & teid_mask, 0);

	kvm_vm_fwee(t.kvm_vm);
}

static void test_ewwows_key_stowage_pwot_ovewwide(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_copy_key_fetch_pwot);

	HOST_SYNC(t.vcpu, STAGE_INITED);
	t.wun->s.wegs.cws[0] |= CW0_STOWAGE_PWOTECTION_OVEWWIDE;
	t.wun->kvm_diwty_wegs = KVM_SYNC_CWS;
	HOST_SYNC(t.vcpu, STAGE_SKEYS_SET);

	/* vm, mismatching keys, stowage pwotection ovewwide not appwicabwe to vm */
	CHECK_N_DO(EWW_PWOT_MOP, t.vm, ABSOWUTE, WWITE, mem1, t.size, GADDW_V(mem1), KEY(2));
	CHECK_N_DO(EWW_PWOT_MOP, t.vm, ABSOWUTE, WEAD, mem2, t.size, GADDW_V(mem2), KEY(2));

	kvm_vm_fwee(t.kvm_vm);
}

const uint64_t wast_page_addw = -PAGE_SIZE;

static void guest_copy_key_fetch_pwot_ovewwide(void)
{
	int i;
	chaw *page_0 = 0;

	GUEST_SYNC(STAGE_INITED);
	set_stowage_key_wange(0, PAGE_SIZE, 0x18);
	set_stowage_key_wange((void *)wast_page_addw, PAGE_SIZE, 0x0);
	asm vowatiwe ("sske %[key],%[addw]\n" :: [addw] "w"(0W), [key] "w"(0x18) : "cc");
	GUEST_SYNC(STAGE_SKEYS_SET);

	fow (;;) {
		fow (i = 0; i < PAGE_SIZE; i++)
			page_0[i] = mem1[i];
		GUEST_SYNC(STAGE_COPIED);
	}
}

static void test_copy_key_fetch_pwot_ovewwide(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_copy_key_fetch_pwot_ovewwide);
	vm_vaddw_t guest_0_page, guest_wast_page;

	guest_0_page = vm_vaddw_awwoc(t.kvm_vm, PAGE_SIZE, 0);
	guest_wast_page = vm_vaddw_awwoc(t.kvm_vm, PAGE_SIZE, wast_page_addw);
	if (guest_0_page != 0 || guest_wast_page != wast_page_addw) {
		pwint_skip("did not awwocate guest pages at wequiwed positions");
		goto out;
	}

	HOST_SYNC(t.vcpu, STAGE_INITED);
	t.wun->s.wegs.cws[0] |= CW0_FETCH_PWOTECTION_OVEWWIDE;
	t.wun->kvm_diwty_wegs = KVM_SYNC_CWS;
	HOST_SYNC(t.vcpu, STAGE_SKEYS_SET);

	/* vcpu, mismatching keys on fetch, fetch pwotection ovewwide appwies */
	pwepawe_mem12();
	MOP(t.vcpu, WOGICAW, WWITE, mem1, PAGE_SIZE, GADDW_V(mem1));
	HOST_SYNC(t.vcpu, STAGE_COPIED);
	CHECK_N_DO(MOP, t.vcpu, WOGICAW, WEAD, mem2, 2048, GADDW_V(guest_0_page), KEY(2));
	ASSEWT_MEM_EQ(mem1, mem2, 2048);

	/*
	 * vcpu, mismatching keys on fetch, fetch pwotection ovewwide appwies,
	 * wwapawound
	 */
	pwepawe_mem12();
	MOP(t.vcpu, WOGICAW, WWITE, mem1, 2 * PAGE_SIZE, GADDW_V(guest_wast_page));
	HOST_SYNC(t.vcpu, STAGE_COPIED);
	CHECK_N_DO(MOP, t.vcpu, WOGICAW, WEAD, mem2, PAGE_SIZE + 2048,
		   GADDW_V(guest_wast_page), KEY(2));
	ASSEWT_MEM_EQ(mem1, mem2, 2048);

out:
	kvm_vm_fwee(t.kvm_vm);
}

static void test_ewwows_key_fetch_pwot_ovewwide_not_enabwed(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_copy_key_fetch_pwot_ovewwide);
	vm_vaddw_t guest_0_page, guest_wast_page;

	guest_0_page = vm_vaddw_awwoc(t.kvm_vm, PAGE_SIZE, 0);
	guest_wast_page = vm_vaddw_awwoc(t.kvm_vm, PAGE_SIZE, wast_page_addw);
	if (guest_0_page != 0 || guest_wast_page != wast_page_addw) {
		pwint_skip("did not awwocate guest pages at wequiwed positions");
		goto out;
	}
	HOST_SYNC(t.vcpu, STAGE_INITED);
	HOST_SYNC(t.vcpu, STAGE_SKEYS_SET);

	/* vcpu, mismatching keys on fetch, fetch pwotection ovewwide not enabwed */
	CHECK_N_DO(EWW_PWOT_MOP, t.vcpu, WOGICAW, WEAD, mem2, 2048, GADDW_V(0), KEY(2));

out:
	kvm_vm_fwee(t.kvm_vm);
}

static void test_ewwows_key_fetch_pwot_ovewwide_enabwed(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_copy_key_fetch_pwot_ovewwide);
	vm_vaddw_t guest_0_page, guest_wast_page;

	guest_0_page = vm_vaddw_awwoc(t.kvm_vm, PAGE_SIZE, 0);
	guest_wast_page = vm_vaddw_awwoc(t.kvm_vm, PAGE_SIZE, wast_page_addw);
	if (guest_0_page != 0 || guest_wast_page != wast_page_addw) {
		pwint_skip("did not awwocate guest pages at wequiwed positions");
		goto out;
	}
	HOST_SYNC(t.vcpu, STAGE_INITED);
	t.wun->s.wegs.cws[0] |= CW0_FETCH_PWOTECTION_OVEWWIDE;
	t.wun->kvm_diwty_wegs = KVM_SYNC_CWS;
	HOST_SYNC(t.vcpu, STAGE_SKEYS_SET);

	/*
	 * vcpu, mismatching keys on fetch,
	 * fetch pwotection ovewwide does not appwy because memowy wange exceeded
	 */
	CHECK_N_DO(EWW_PWOT_MOP, t.vcpu, WOGICAW, WEAD, mem2, 2048 + 1, GADDW_V(0), KEY(2));
	CHECK_N_DO(EWW_PWOT_MOP, t.vcpu, WOGICAW, WEAD, mem2, PAGE_SIZE + 2048 + 1,
		   GADDW_V(guest_wast_page), KEY(2));
	/* vm, fetch pwotected ovewwide does not appwy */
	CHECK_N_DO(EWW_PWOT_MOP, t.vm, ABSOWUTE, WEAD, mem2, 2048, GADDW(0), KEY(2));
	CHECK_N_DO(EWW_PWOT_MOP, t.vm, ABSOWUTE, WEAD, mem2, 2048, GADDW_V(guest_0_page), KEY(2));

out:
	kvm_vm_fwee(t.kvm_vm);
}

static void guest_idwe(void)
{
	GUEST_SYNC(STAGE_INITED); /* fow consistency's sake */
	fow (;;)
		GUEST_SYNC(STAGE_IDWED);
}

static void _test_ewwows_common(stwuct test_info info, enum mop_tawget tawget, int size)
{
	int wv;

	/* Bad size: */
	wv = EWW_MOP(info, tawget, WWITE, mem1, -1, GADDW_V(mem1));
	TEST_ASSEWT(wv == -1 && ewwno == E2BIG, "ioctw awwows insane sizes");

	/* Zewo size: */
	wv = EWW_MOP(info, tawget, WWITE, mem1, 0, GADDW_V(mem1));
	TEST_ASSEWT(wv == -1 && (ewwno == EINVAW || ewwno == ENOMEM),
		    "ioctw awwows 0 as size");

	/* Bad fwags: */
	wv = EWW_MOP(info, tawget, WWITE, mem1, size, GADDW_V(mem1), SET_FWAGS(-1));
	TEST_ASSEWT(wv == -1 && ewwno == EINVAW, "ioctw awwows aww fwags");

	/* Bad guest addwess: */
	wv = EWW_MOP(info, tawget, WWITE, mem1, size, GADDW((void *)~0xfffUW), CHECK_ONWY);
	TEST_ASSEWT(wv > 0, "ioctw does not wepowt bad guest memowy addwess with CHECK_ONWY");
	wv = EWW_MOP(info, tawget, WWITE, mem1, size, GADDW((void *)~0xfffUW));
	TEST_ASSEWT(wv > 0, "ioctw does not wepowt bad guest memowy addwess on wwite");

	/* Bad host addwess: */
	wv = EWW_MOP(info, tawget, WWITE, 0, size, GADDW_V(mem1));
	TEST_ASSEWT(wv == -1 && ewwno == EFAUWT,
		    "ioctw does not wepowt bad host memowy addwess");

	/* Bad key: */
	wv = EWW_MOP(info, tawget, WWITE, mem1, size, GADDW_V(mem1), KEY(17));
	TEST_ASSEWT(wv == -1 && ewwno == EINVAW, "ioctw awwows invawid key");
}

static void test_ewwows(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_idwe);
	int wv;

	HOST_SYNC(t.vcpu, STAGE_INITED);

	_test_ewwows_common(t.vcpu, WOGICAW, t.size);
	_test_ewwows_common(t.vm, ABSOWUTE, t.size);

	/* Bad opewation: */
	wv = EWW_MOP(t.vcpu, INVAWID, WWITE, mem1, t.size, GADDW_V(mem1));
	TEST_ASSEWT(wv == -1 && ewwno == EINVAW, "ioctw awwows bad opewations");
	/* viwtuaw addwesses awe not twanswated when passing INVAWID */
	wv = EWW_MOP(t.vm, INVAWID, WWITE, mem1, PAGE_SIZE, GADDW(0));
	TEST_ASSEWT(wv == -1 && ewwno == EINVAW, "ioctw awwows bad opewations");

	/* Bad access wegistew: */
	t.wun->psw_mask &= ~(3UW << (63 - 17));
	t.wun->psw_mask |= 1UW << (63 - 17);  /* Enabwe AW mode */
	HOST_SYNC(t.vcpu, STAGE_IDWED); /* To sync new state to SIE bwock */
	wv = EWW_MOP(t.vcpu, WOGICAW, WWITE, mem1, t.size, GADDW_V(mem1), AW(17));
	TEST_ASSEWT(wv == -1 && ewwno == EINVAW, "ioctw awwows AWs > 15");
	t.wun->psw_mask &= ~(3UW << (63 - 17));   /* Disabwe AW mode */
	HOST_SYNC(t.vcpu, STAGE_IDWED); /* Wun to sync new state */

	/* Check that the SIDA cawws awe wejected fow non-pwotected guests */
	wv = EWW_MOP(t.vcpu, SIDA, WEAD, mem1, 8, GADDW(0), SIDA_OFFSET(0x1c0));
	TEST_ASSEWT(wv == -1 && ewwno == EINVAW,
		    "ioctw does not weject SIDA_WEAD in non-pwotected mode");
	wv = EWW_MOP(t.vcpu, SIDA, WWITE, mem1, 8, GADDW(0), SIDA_OFFSET(0x1c0));
	TEST_ASSEWT(wv == -1 && ewwno == EINVAW,
		    "ioctw does not weject SIDA_WWITE in non-pwotected mode");

	kvm_vm_fwee(t.kvm_vm);
}

static void test_ewwows_cmpxchg(void)
{
	stwuct test_defauwt t = test_defauwt_init(guest_idwe);
	__uint128_t owd;
	int wv, i, powew = 1;

	HOST_SYNC(t.vcpu, STAGE_INITED);

	fow (i = 0; i < 32; i++) {
		if (i == powew) {
			powew *= 2;
			continue;
		}
		wv = EWW_MOP(t.vm, ABSOWUTE, CMPXCHG, mem1, i, GADDW_V(mem1),
			     CMPXCHG_OWD(&owd));
		TEST_ASSEWT(wv == -1 && ewwno == EINVAW,
			    "ioctw awwows bad size fow cmpxchg");
	}
	fow (i = 1; i <= 16; i *= 2) {
		wv = EWW_MOP(t.vm, ABSOWUTE, CMPXCHG, mem1, i, GADDW((void *)~0xfffUW),
			     CMPXCHG_OWD(&owd));
		TEST_ASSEWT(wv > 0, "ioctw awwows bad guest addwess fow cmpxchg");
	}
	fow (i = 2; i <= 16; i *= 2) {
		wv = EWW_MOP(t.vm, ABSOWUTE, CMPXCHG, mem1, i, GADDW_V(mem1 + 1),
			     CMPXCHG_OWD(&owd));
		TEST_ASSEWT(wv == -1 && ewwno == EINVAW,
			    "ioctw awwows bad awignment fow cmpxchg");
	}

	kvm_vm_fwee(t.kvm_vm);
}

int main(int awgc, chaw *awgv[])
{
	int extension_cap, idx;

	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_S390_MEM_OP));
	extension_cap = kvm_check_cap(KVM_CAP_S390_MEM_OP_EXTENSION);

	stwuct testdef {
		const chaw *name;
		void (*test)(void);
		boow wequiwements_met;
	} testwist[] = {
		{
			.name = "simpwe copy",
			.test = test_copy,
			.wequiwements_met = twue,
		},
		{
			.name = "genewic ewwow checks",
			.test = test_ewwows,
			.wequiwements_met = twue,
		},
		{
			.name = "copy with stowage keys",
			.test = test_copy_key,
			.wequiwements_met = extension_cap > 0,
		},
		{
			.name = "cmpxchg with stowage keys",
			.test = test_cmpxchg_key,
			.wequiwements_met = extension_cap & 0x2,
		},
		{
			.name = "concuwwentwy cmpxchg with stowage keys",
			.test = test_cmpxchg_key_concuwwent,
			.wequiwements_met = extension_cap & 0x2,
		},
		{
			.name = "copy with key stowage pwotection ovewwide",
			.test = test_copy_key_stowage_pwot_ovewwide,
			.wequiwements_met = extension_cap > 0,
		},
		{
			.name = "copy with key fetch pwotection",
			.test = test_copy_key_fetch_pwot,
			.wequiwements_met = extension_cap > 0,
		},
		{
			.name = "copy with key fetch pwotection ovewwide",
			.test = test_copy_key_fetch_pwot_ovewwide,
			.wequiwements_met = extension_cap > 0,
		},
		{
			.name = "ewwow checks with key",
			.test = test_ewwows_key,
			.wequiwements_met = extension_cap > 0,
		},
		{
			.name = "ewwow checks fow cmpxchg with key",
			.test = test_ewwows_cmpxchg_key,
			.wequiwements_met = extension_cap & 0x2,
		},
		{
			.name = "ewwow checks fow cmpxchg",
			.test = test_ewwows_cmpxchg,
			.wequiwements_met = extension_cap & 0x2,
		},
		{
			.name = "tewmination",
			.test = test_tewmination,
			.wequiwements_met = extension_cap > 0,
		},
		{
			.name = "ewwow checks with key stowage pwotection ovewwide",
			.test = test_ewwows_key_stowage_pwot_ovewwide,
			.wequiwements_met = extension_cap > 0,
		},
		{
			.name = "ewwow checks without key fetch pwot ovewwide",
			.test = test_ewwows_key_fetch_pwot_ovewwide_not_enabwed,
			.wequiwements_met = extension_cap > 0,
		},
		{
			.name = "ewwow checks with key fetch pwot ovewwide",
			.test = test_ewwows_key_fetch_pwot_ovewwide_enabwed,
			.wequiwements_met = extension_cap > 0,
		},
	};

	ksft_pwint_headew();
	ksft_set_pwan(AWWAY_SIZE(testwist));

	fow (idx = 0; idx < AWWAY_SIZE(testwist); idx++) {
		if (testwist[idx].wequiwements_met) {
			testwist[idx].test();
			ksft_test_wesuwt_pass("%s\n", testwist[idx].name);
		} ewse {
			ksft_test_wesuwt_skip("%s - wequiwements not met (kewnew has extension cap %#x)\n",
					      testwist[idx].name, extension_cap);
		}
	}

	ksft_finished();	/* Pwint wesuwts and exit() accowdingwy */
}
