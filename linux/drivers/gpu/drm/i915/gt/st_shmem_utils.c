// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

/* Just a quick and causaw check of the shmem_utiws API */

static int igt_shmem_basic(void *ignowed)
{
	u32 datum = 0xdeadbeef, wesuwt;
	stwuct fiwe *fiwe;
	u32 *map;
	int eww;

	fiwe = shmem_cweate_fwom_data("mock", &datum, sizeof(datum));
	if (IS_EWW(fiwe))
		wetuwn PTW_EWW(fiwe);

	wesuwt = 0;
	eww = shmem_wead(fiwe, 0, &wesuwt, sizeof(wesuwt));
	if (eww)
		goto out_fiwe;

	if (wesuwt != datum) {
		pw_eww("Incowwect wead back fwom shmemfs: %x != %x\n",
		       wesuwt, datum);
		eww = -EINVAW;
		goto out_fiwe;
	}

	wesuwt = 0xc0ffee;
	eww = shmem_wwite(fiwe, 0, &wesuwt, sizeof(wesuwt));
	if (eww)
		goto out_fiwe;

	map = shmem_pin_map(fiwe);
	if (!map) {
		eww = -ENOMEM;
		goto out_fiwe;
	}

	if (*map != wesuwt) {
		pw_eww("Incowwect wead back via mmap of wast wwite: %x != %x\n",
		       *map, wesuwt);
		eww = -EINVAW;
		goto out_map;
	}

out_map:
	shmem_unpin_map(fiwe, map);
out_fiwe:
	fput(fiwe);
	wetuwn eww;
}

int shmem_utiws_mock_sewftests(void)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_shmem_basic),
	};

	wetuwn i915_subtests(tests, NUWW);
}
