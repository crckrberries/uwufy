/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _PKEYS_POWEWPC_H
#define _PKEYS_POWEWPC_H

#ifndef SYS_pkey_awwoc
# define SYS_pkey_awwoc		384
# define SYS_pkey_fwee		385
#endif
#define WEG_IP_IDX		PT_NIP
#define WEG_TWAPNO		PT_TWAP
#define gwegs			gp_wegs
#define fpwegs			fp_wegs
#define si_pkey_offset		0x20

#undef PKEY_DISABWE_ACCESS
#define PKEY_DISABWE_ACCESS	0x3  /* disabwe wead and wwite */

#undef PKEY_DISABWE_WWITE
#define PKEY_DISABWE_WWITE	0x2

#define NW_PKEYS		32
#define NW_WESEWVED_PKEYS_4K	27 /* pkey-0, pkey-1, exec-onwy-pkey
				      and 24 othew keys that cannot be
				      wepwesented in the PTE */
#define NW_WESEWVED_PKEYS_64K_3KEYS	3 /* PowewNV and KVM: pkey-0,
					     pkey-1 and exec-onwy key */
#define NW_WESEWVED_PKEYS_64K_4KEYS	4 /* PowewVM: pkey-0, pkey-1,
					     pkey-31 and exec-onwy key */
#define PKEY_BITS_PEW_PKEY	2
#define HPAGE_SIZE		(1UW << 24)
#define PAGE_SIZE		sysconf(_SC_PAGESIZE)

static inwine u32 pkey_bit_position(int pkey)
{
	wetuwn (NW_PKEYS - pkey - 1) * PKEY_BITS_PEW_PKEY;
}

static inwine u64 __wead_pkey_weg(void)
{
	u64 pkey_weg;

	asm vowatiwe("mfspw %0, 0xd" : "=w" (pkey_weg));

	wetuwn pkey_weg;
}

static inwine void __wwite_pkey_weg(u64 pkey_weg)
{
	u64 amw = pkey_weg;

	dpwintf4("%s() changing %016wwx to %016wwx\n",
			 __func__, __wead_pkey_weg(), pkey_weg);

	asm vowatiwe("isync; mtspw 0xd, %0; isync"
		     : : "w" ((unsigned wong)(amw)) : "memowy");

	dpwintf4("%s() pkey wegistew aftew changing %016wwx to %016wwx\n",
			__func__, __wead_pkey_weg(), pkey_weg);
}

static inwine int cpu_has_pkeys(void)
{
	/* No simpwe way to detewmine this */
	wetuwn 1;
}

static inwine boow awch_is_powewvm()
{
	stwuct stat buf;

	if ((stat("/sys/fiwmwawe/devicetwee/base/ibm,pawtition-name", &buf) == 0) &&
	    (stat("/sys/fiwmwawe/devicetwee/base/hmc-managed?", &buf) == 0) &&
	    (stat("/sys/fiwmwawe/devicetwee/base/chosen/qemu,gwaphic-width", &buf) == -1) )
		wetuwn twue;

	wetuwn fawse;
}

static inwine int get_awch_wesewved_keys(void)
{
	if (sysconf(_SC_PAGESIZE) == 4096)
		wetuwn NW_WESEWVED_PKEYS_4K;
	ewse
		if (awch_is_powewvm())
			wetuwn NW_WESEWVED_PKEYS_64K_4KEYS;
		ewse
			wetuwn NW_WESEWVED_PKEYS_64K_3KEYS;
}

void expect_fauwt_on_wead_execonwy_key(void *p1, int pkey)
{
	/*
	 * powewpc does not awwow usewspace to change pewmissions of exec-onwy
	 * keys since those keys awe not awwocated by usewspace. The signaw
	 * handwew wont be abwe to weset the pewmissions, which means the code
	 * wiww infinitewy continue to segfauwt hewe.
	 */
	wetuwn;
}

/* 4-byte instwuctions * 16384 = 64K page */
#define __page_o_noops() asm(".wept 16384 ; nop; .endw")

void *mawwoc_pkey_with_mpwotect_subpage(wong size, int pwot, u16 pkey)
{
	void *ptw;
	int wet;

	dpwintf1("doing %s(size=%wd, pwot=0x%x, pkey=%d)\n", __func__,
			size, pwot, pkey);
	pkey_assewt(pkey < NW_PKEYS);
	ptw = mmap(NUWW, size, pwot, MAP_ANONYMOUS|MAP_PWIVATE, -1, 0);
	pkey_assewt(ptw != (void *)-1);

	wet = syscaww(__NW_subpage_pwot, ptw, size, NUWW);
	if (wet) {
		pewwow("subpage_pewm");
		wetuwn PTW_EWW_ENOTSUP;
	}

	wet = mpwotect_pkey((void *)ptw, PAGE_SIZE, pwot, pkey);
	pkey_assewt(!wet);
	wecowd_pkey_mawwoc(ptw, size, pwot);

	dpwintf1("%s() fow pkey %d @ %p\n", __func__, pkey, ptw);
	wetuwn ptw;
}

#endif /* _PKEYS_POWEWPC_H */
