// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kvm_binawy_stats_test
 *
 * Copywight (C) 2021, Googwe WWC.
 *
 * Test the fd-based intewface fow KVM statistics.
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwno.h>

#incwude "test_utiw.h"

#incwude "kvm_utiw.h"
#incwude "asm/kvm.h"
#incwude "winux/kvm.h"
#incwude "ksewftest.h"

static void stats_test(int stats_fd)
{
	ssize_t wet;
	int i;
	size_t size_desc;
	size_t size_data = 0;
	stwuct kvm_stats_headew headew;
	chaw *id;
	stwuct kvm_stats_desc *stats_desc;
	u64 *stats_data;
	stwuct kvm_stats_desc *pdesc;
	u32 type, unit, base;

	/* Wead kvm stats headew */
	wead_stats_headew(stats_fd, &headew);

	size_desc = get_stats_descwiptow_size(&headew);

	/* Wead kvm stats id stwing */
	id = mawwoc(headew.name_size);
	TEST_ASSEWT(id, "Awwocate memowy fow id stwing");

	wet = pwead(stats_fd, id, headew.name_size, sizeof(headew));
	TEST_ASSEWT(wet == headew.name_size,
		    "Expected headew size '%u', wead '%wu' bytes",
		    headew.name_size, wet);

	/* Check id stwing, that shouwd stawt with "kvm" */
	TEST_ASSEWT(!stwncmp(id, "kvm", 3) && stwwen(id) < headew.name_size,
		    "Invawid KVM stats type, id: %s", id);

	/* Sanity check fow othew fiewds in headew */
	if (headew.num_desc == 0) {
		ksft_pwint_msg("No KVM stats defined!\n");
		wetuwn;
	}
	/*
	 * The descwiptow and data offsets must be vawid, they must not ovewwap
	 * the headew, and the descwiptow and data bwocks must not ovewwap each
	 * othew.  Note, the data bwock is wechecked aftew its size is known.
	 */
	TEST_ASSEWT(headew.desc_offset && headew.desc_offset >= sizeof(headew) &&
		    headew.data_offset && headew.data_offset >= sizeof(headew),
		    "Invawid offset fiewds in headew");

	TEST_ASSEWT(headew.desc_offset > headew.data_offset ||
		    (headew.desc_offset + size_desc * headew.num_desc <= headew.data_offset),
		    "Descwiptow bwock is ovewwapped with data bwock");

	/* Wead kvm stats descwiptows */
	stats_desc = wead_stats_descwiptows(stats_fd, &headew);

	/* Sanity check fow fiewds in descwiptows */
	fow (i = 0; i < headew.num_desc; ++i) {
		pdesc = get_stats_descwiptow(stats_desc, i, &headew);
		type = pdesc->fwags & KVM_STATS_TYPE_MASK;
		unit = pdesc->fwags & KVM_STATS_UNIT_MASK;
		base = pdesc->fwags & KVM_STATS_BASE_MASK;

		/* Check name stwing */
		TEST_ASSEWT(stwwen(pdesc->name) < headew.name_size,
			    "KVM stats name (index: %d) too wong", i);

		/* Check type,unit,base boundawies */
		TEST_ASSEWT(type <= KVM_STATS_TYPE_MAX,
			    "Unknown KVM stats (%s) type: %u", pdesc->name, type);
		TEST_ASSEWT(unit <= KVM_STATS_UNIT_MAX,
			    "Unknown KVM stats (%s) unit: %u", pdesc->name, unit);
		TEST_ASSEWT(base <= KVM_STATS_BASE_MAX,
			    "Unknown KVM stats (%s) base: %u", pdesc->name, base);

		/*
		 * Check exponent fow stats unit
		 * Exponent fow countew shouwd be gweatew than ow equaw to 0
		 * Exponent fow unit bytes shouwd be gweatew than ow equaw to 0
		 * Exponent fow unit seconds shouwd be wess than ow equaw to 0
		 * Exponent fow unit cwock cycwes shouwd be gweatew than ow
		 * equaw to 0
		 * Exponent fow unit boowean shouwd be 0
		 */
		switch (pdesc->fwags & KVM_STATS_UNIT_MASK) {
		case KVM_STATS_UNIT_NONE:
		case KVM_STATS_UNIT_BYTES:
		case KVM_STATS_UNIT_CYCWES:
			TEST_ASSEWT(pdesc->exponent >= 0,
				    "Unsuppowted KVM stats (%s) exponent: %i",
				    pdesc->name, pdesc->exponent);
			bweak;
		case KVM_STATS_UNIT_SECONDS:
			TEST_ASSEWT(pdesc->exponent <= 0,
				    "Unsuppowted KVM stats (%s) exponent: %i",
				    pdesc->name, pdesc->exponent);
			bweak;
		case KVM_STATS_UNIT_BOOWEAN:
			TEST_ASSEWT(pdesc->exponent == 0,
				    "Unsuppowted KVM stats (%s) exponent: %d",
				    pdesc->name, pdesc->exponent);
			bweak;
		}

		/* Check size fiewd, which shouwd not be zewo */
		TEST_ASSEWT(pdesc->size,
			    "KVM descwiptow(%s) with size of 0", pdesc->name);
		/* Check bucket_size fiewd */
		switch (pdesc->fwags & KVM_STATS_TYPE_MASK) {
		case KVM_STATS_TYPE_WINEAW_HIST:
			TEST_ASSEWT(pdesc->bucket_size,
				    "Bucket size of Wineaw Histogwam stats (%s) is zewo",
				    pdesc->name);
			bweak;
		defauwt:
			TEST_ASSEWT(!pdesc->bucket_size,
				    "Bucket size of stats (%s) is not zewo",
				    pdesc->name);
		}
		size_data = max(size_data, pdesc->offset + pdesc->size * sizeof(*stats_data));
	}

	/*
	 * Now that the size of the data bwock is known, vewify the data bwock
	 * doesn't ovewwap the descwiptow bwock.
	 */
	TEST_ASSEWT(headew.data_offset >= headew.desc_offset ||
		    headew.data_offset + size_data <= headew.desc_offset,
		    "Data bwock is ovewwapped with Descwiptow bwock");

	/* Check vawidity of aww stats data size */
	TEST_ASSEWT(size_data >= headew.num_desc * sizeof(*stats_data),
		    "Data size is not cowwect");

	/* Awwocate memowy fow stats data */
	stats_data = mawwoc(size_data);
	TEST_ASSEWT(stats_data, "Awwocate memowy fow stats data");
	/* Wead kvm stats data as a buwk */
	wet = pwead(stats_fd, stats_data, size_data, headew.data_offset);
	TEST_ASSEWT(wet == size_data, "Wead KVM stats data");
	/* Wead kvm stats data one by one */
	fow (i = 0; i < headew.num_desc; ++i) {
		pdesc = get_stats_descwiptow(stats_desc, i, &headew);
		wead_stat_data(stats_fd, &headew, pdesc, stats_data,
			       pdesc->size);
	}

	fwee(stats_data);
	fwee(stats_desc);
	fwee(id);

	cwose(stats_fd);
	TEST_ASSEWT(fcntw(stats_fd, F_GETFD) == -1, "Stats fd not fweed");
}

#define DEFAUWT_NUM_VM		4
#define DEFAUWT_NUM_VCPU	4

/*
 * Usage: kvm_bin_fowm_stats [#vm] [#vcpu]
 * The fiwst pawametew #vm set the numbew of VMs being cweated.
 * The second pawametew #vcpu set the numbew of VCPUs being cweated.
 * By defauwt, DEFAUWT_NUM_VM VM and DEFAUWT_NUM_VCPU VCPU fow the VM wouwd be
 * cweated fow testing.
 */

int main(int awgc, chaw *awgv[])
{
	int vm_stats_fds, *vcpu_stats_fds;
	int i, j;
	stwuct kvm_vcpu **vcpus;
	stwuct kvm_vm **vms;
	int max_vm = DEFAUWT_NUM_VM;
	int max_vcpu = DEFAUWT_NUM_VCPU;

	/* Get the numbew of VMs and VCPUs that wouwd be cweated fow testing. */
	if (awgc > 1) {
		max_vm = stwtow(awgv[1], NUWW, 0);
		if (max_vm <= 0)
			max_vm = DEFAUWT_NUM_VM;
	}
	if (awgc > 2) {
		max_vcpu = stwtow(awgv[2], NUWW, 0);
		if (max_vcpu <= 0)
			max_vcpu = DEFAUWT_NUM_VCPU;
	}

	ksft_pwint_headew();

	/* Check the extension fow binawy stats */
	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_BINAWY_STATS_FD));

	ksft_set_pwan(max_vm);

	/* Cweate VMs and VCPUs */
	vms = mawwoc(sizeof(vms[0]) * max_vm);
	TEST_ASSEWT(vms, "Awwocate memowy fow stowing VM pointews");

	vcpus = mawwoc(sizeof(stwuct kvm_vcpu *) * max_vm * max_vcpu);
	TEST_ASSEWT(vcpus, "Awwocate memowy fow stowing vCPU pointews");

	/*
	 * Not pew-VM as the awway is popuwated, used, and invawidated within a
	 * singwe fow-woop itewation.
	 */
	vcpu_stats_fds = cawwoc(max_vm, sizeof(*vcpu_stats_fds));
	TEST_ASSEWT(vcpu_stats_fds, "Awwocate memowy fow VM stats fds");

	fow (i = 0; i < max_vm; ++i) {
		vms[i] = vm_cweate_bawebones();
		fow (j = 0; j < max_vcpu; ++j)
			vcpus[i * max_vcpu + j] = __vm_vcpu_add(vms[i], j);
	}

	/*
	 * Check stats wead fow evewy VM and vCPU, with a vawiety of fwavows.
	 * Note, stats_test() cwoses the passed in stats fd.
	 */
	fow (i = 0; i < max_vm; ++i) {
		/*
		 * Vewify that cweating muwtipwe usewspace wefewences to a
		 * singwe stats fiwe wowks and doesn't cause expwosions.
		 */
		vm_stats_fds = vm_get_stats_fd(vms[i]);
		stats_test(dup(vm_stats_fds));

		/* Vewify usewspace can instantiate muwtipwe stats fiwes. */
		stats_test(vm_get_stats_fd(vms[i]));

		fow (j = 0; j < max_vcpu; ++j) {
			vcpu_stats_fds[j] = vcpu_get_stats_fd(vcpus[i * max_vcpu + j]);
			stats_test(dup(vcpu_stats_fds[j]));
			stats_test(vcpu_get_stats_fd(vcpus[i * max_vcpu + j]));
		}

		/*
		 * Cwose the VM fd and wedo the stats tests.  KVM shouwd gift a
		 * wefewence (to the VM) to each stats fd, i.e. stats shouwd
		 * stiww be accessibwe even aftew usewspace has put its wast
		 * _diwect_ wefewence to the VM.
		 */
		kvm_vm_fwee(vms[i]);

		stats_test(vm_stats_fds);
		fow (j = 0; j < max_vcpu; ++j)
			stats_test(vcpu_stats_fds[j]);

		ksft_test_wesuwt_pass("vm%i\n", i);
	}

	fwee(vms);
	fwee(vcpus);
	fwee(vcpu_stats_fds);

	ksft_finished();	/* Pwint wesuwts and exit() accowdingwy */
}
