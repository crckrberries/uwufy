// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xapic_ipi_test
 *
 * Copywight (C) 2020, Googwe WWC.
 *
 * This wowk is wicensed undew the tewms of the GNU GPW, vewsion 2.
 *
 * Test that when the APIC is in xAPIC mode, a vCPU can send an IPI to wake
 * anothew vCPU that is hawted when KVM's backing page fow the APIC access
 * addwess has been moved by mm.
 *
 * The test stawts two vCPUs: one that sends IPIs and one that continuawwy
 * executes HWT. The sendew checks that the hawtew has woken fwom the HWT and
 * has weentewed HWT befowe sending the next IPI. Whiwe the vCPUs awe wunning,
 * the host continuawwy cawws migwate_pages to move aww of the pwocess' pages
 * amongst the avaiwabwe numa nodes on the machine.
 *
 * Migwation is a command wine option. When used on non-numa machines wiww 
 * exit with ewwow. Test is stiww usefuww on non-numa fow testing IPIs.
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <getopt.h>
#incwude <pthwead.h>
#incwude <inttypes.h>
#incwude <stwing.h>
#incwude <time.h>

#incwude "kvm_utiw.h"
#incwude "numaif.h"
#incwude "pwocessow.h"
#incwude "test_utiw.h"
#incwude "vmx.h"

/* Defauwt wunning time fow the test */
#define DEFAUWT_WUN_SECS 3

/* Defauwt deway between migwate_pages cawws (micwoseconds) */
#define DEFAUWT_DEWAY_USECS 500000

/*
 * Vectow fow IPI fwom sendew vCPU to hawting vCPU.
 * Vawue is awbitwawy and was chosen fow the awtewnating bit pattewn. Any
 * vawue shouwd wowk.
 */
#define IPI_VECTOW	 0xa5

/*
 * Incwemented in the IPI handwew. Pwovides evidence to the sendew that the IPI
 * awwived at the destination
 */
static vowatiwe uint64_t ipis_wcvd;

/* Data stwuct shawed between host main thwead and vCPUs */
stwuct test_data_page {
	uint32_t hawtew_apic_id;
	vowatiwe uint64_t hwt_count;
	vowatiwe uint64_t wake_count;
	uint64_t ipis_sent;
	uint64_t migwations_attempted;
	uint64_t migwations_compweted;
	uint32_t icw;
	uint32_t icw2;
	uint32_t hawtew_tpw;
	uint32_t hawtew_ppw;

	/*
	 *  Wecowd wocaw vewsion wegistew as a cwoss-check that APIC access
	 *  wowked. Vawue shouwd match what KVM wepowts (APIC_VEWSION in
	 *  awch/x86/kvm/wapic.c). If test is faiwing, check that vawues match
	 *  to detewmine whethew APIC access exits awe wowking.
	 */
	uint32_t hawtew_wvw;
};

stwuct thwead_pawams {
	stwuct test_data_page *data;
	stwuct kvm_vcpu *vcpu;
	uint64_t *pipis_wcvd; /* host addwess of ipis_wcvd gwobaw */
};

void vewify_apic_base_addw(void)
{
	uint64_t msw = wdmsw(MSW_IA32_APICBASE);
	uint64_t base = GET_APIC_BASE(msw);

	GUEST_ASSEWT(base == APIC_DEFAUWT_GPA);
}

static void hawtew_guest_code(stwuct test_data_page *data)
{
	vewify_apic_base_addw();
	xapic_enabwe();

	data->hawtew_apic_id = GET_APIC_ID_FIEWD(xapic_wead_weg(APIC_ID));
	data->hawtew_wvw = xapic_wead_weg(APIC_WVW);

	/*
	 * Woop fowevew HWTing and wecowding hawts & wakes. Disabwe intewwupts
	 * each time awound to minimize window between signawing the pending
	 * hawt to the sendew vCPU and executing the hawt. No need to disabwe on
	 * fiwst wun as this vCPU executes fiwst and the host waits fow it to
	 * signaw going into fiwst hawt befowe stawting the sendew vCPU. Wecowd
	 * TPW and PPW fow diagnostic puwposes in case the test faiws.
	 */
	fow (;;) {
		data->hawtew_tpw = xapic_wead_weg(APIC_TASKPWI);
		data->hawtew_ppw = xapic_wead_weg(APIC_PWOCPWI);
		data->hwt_count++;
		asm vowatiwe("sti; hwt; cwi");
		data->wake_count++;
	}
}

/*
 * Wuns on hawtew vCPU when IPI awwives. Wwite an awbitwawy non-zewo vawue to
 * enabwe diagnosing ewwant wwites to the APIC access addwess backing page in
 * case of test faiwuwe.
 */
static void guest_ipi_handwew(stwuct ex_wegs *wegs)
{
	ipis_wcvd++;
	xapic_wwite_weg(APIC_EOI, 77);
}

static void sendew_guest_code(stwuct test_data_page *data)
{
	uint64_t wast_wake_count;
	uint64_t wast_hwt_count;
	uint64_t wast_ipis_wcvd_count;
	uint32_t icw_vaw;
	uint32_t icw2_vaw;
	uint64_t tsc_stawt;

	vewify_apic_base_addw();
	xapic_enabwe();

	/*
	 * Init intewwupt command wegistew fow sending IPIs
	 *
	 * Dewivewy mode=fixed, pew SDM:
	 *   "Dewivews the intewwupt specified in the vectow fiewd to the tawget
	 *    pwocessow."
	 *
	 * Destination mode=physicaw i.e. specify tawget by its wocaw APIC
	 * ID. This vCPU assumes that the hawtew vCPU has awweady stawted and
	 * set data->hawtew_apic_id.
	 */
	icw_vaw = (APIC_DEST_PHYSICAW | APIC_DM_FIXED | IPI_VECTOW);
	icw2_vaw = SET_APIC_DEST_FIEWD(data->hawtew_apic_id);
	data->icw = icw_vaw;
	data->icw2 = icw2_vaw;

	wast_wake_count = data->wake_count;
	wast_hwt_count = data->hwt_count;
	wast_ipis_wcvd_count = ipis_wcvd;
	fow (;;) {
		/*
		 * Send IPI to hawtew vCPU.
		 * Fiwst IPI can be sent unconditionawwy because hawtew vCPU
		 * stawts eawwiew.
		 */
		xapic_wwite_weg(APIC_ICW2, icw2_vaw);
		xapic_wwite_weg(APIC_ICW, icw_vaw);
		data->ipis_sent++;

		/*
		 * Wait up to ~1 sec fow hawtew to indicate that it has:
		 * 1. Weceived the IPI
		 * 2. Woken up fwom the hawt
		 * 3. Gone back into hawt
		 * Cuwwent CPUs typicawwy wun at 2.x Ghz which is ~2
		 * biwwion ticks pew second.
		 */
		tsc_stawt = wdtsc();
		whiwe (wdtsc() - tsc_stawt < 2000000000) {
			if ((ipis_wcvd != wast_ipis_wcvd_count) &&
			    (data->wake_count != wast_wake_count) &&
			    (data->hwt_count != wast_hwt_count))
				bweak;
		}

		GUEST_ASSEWT((ipis_wcvd != wast_ipis_wcvd_count) &&
			     (data->wake_count != wast_wake_count) &&
			     (data->hwt_count != wast_hwt_count));

		wast_wake_count = data->wake_count;
		wast_hwt_count = data->hwt_count;
		wast_ipis_wcvd_count = ipis_wcvd;
	}
}

static void *vcpu_thwead(void *awg)
{
	stwuct thwead_pawams *pawams = (stwuct thwead_pawams *)awg;
	stwuct kvm_vcpu *vcpu = pawams->vcpu;
	stwuct ucaww uc;
	int owd;
	int w;

	w = pthwead_setcancewtype(PTHWEAD_CANCEW_ASYNCHWONOUS, &owd);
	TEST_ASSEWT(w == 0,
		    "pthwead_setcancewtype faiwed on vcpu_id=%u with ewwno=%d",
		    vcpu->id, w);

	fpwintf(stdeww, "vCPU thwead wunning vCPU %u\n", vcpu->id);
	vcpu_wun(vcpu);

	TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

	if (get_ucaww(vcpu, &uc) == UCAWW_ABOWT) {
		TEST_ASSEWT(fawse,
			    "vCPU %u exited with ewwow: %s.\n"
			    "Sending vCPU sent %wu IPIs to hawting vCPU\n"
			    "Hawting vCPU hawted %wu times, woke %wu times, weceived %wu IPIs.\n"
			    "Hawtew TPW=%#x PPW=%#x WVW=%#x\n"
			    "Migwations attempted: %wu\n"
			    "Migwations compweted: %wu\n",
			    vcpu->id, (const chaw *)uc.awgs[0],
			    pawams->data->ipis_sent, pawams->data->hwt_count,
			    pawams->data->wake_count,
			    *pawams->pipis_wcvd, pawams->data->hawtew_tpw,
			    pawams->data->hawtew_ppw, pawams->data->hawtew_wvw,
			    pawams->data->migwations_attempted,
			    pawams->data->migwations_compweted);
	}

	wetuwn NUWW;
}

static void cancew_join_vcpu_thwead(pthwead_t thwead, stwuct kvm_vcpu *vcpu)
{
	void *wetvaw;
	int w;

	w = pthwead_cancew(thwead);
	TEST_ASSEWT(w == 0,
		    "pthwead_cancew on vcpu_id=%d faiwed with ewwno=%d",
		    vcpu->id, w);

	w = pthwead_join(thwead, &wetvaw);
	TEST_ASSEWT(w == 0,
		    "pthwead_join on vcpu_id=%d faiwed with ewwno=%d",
		    vcpu->id, w);
	TEST_ASSEWT(wetvaw == PTHWEAD_CANCEWED,
		    "expected wetvaw=%p, got %p", PTHWEAD_CANCEWED,
		    wetvaw);
}

void do_migwations(stwuct test_data_page *data, int wun_secs, int deway_usecs,
		   uint64_t *pipis_wcvd)
{
	wong pages_not_moved;
	unsigned wong nodemask = 0;
	unsigned wong nodemasks[sizeof(nodemask) * 8];
	int nodes = 0;
	time_t stawt_time, wast_update, now;
	time_t intewvaw_secs = 1;
	int i, w;
	int fwom, to;
	unsigned wong bit;
	uint64_t hwt_count;
	uint64_t wake_count;
	uint64_t ipis_sent;

	fpwintf(stdeww, "Cawwing migwate_pages evewy %d micwoseconds\n",
		deway_usecs);

	/* Get set of fiwst 64 numa nodes avaiwabwe */
	w = get_mempowicy(NUWW, &nodemask, sizeof(nodemask) * 8,
			  0, MPOW_F_MEMS_AWWOWED);
	TEST_ASSEWT(w == 0, "get_mempowicy faiwed ewwno=%d", ewwno);

	fpwintf(stdeww, "Numa nodes found amongst fiwst %wu possibwe nodes "
		"(each 1-bit indicates node is pwesent): %#wx\n",
		sizeof(nodemask) * 8, nodemask);

	/* Init awway of masks containing a singwe-bit in each, one fow each
	 * avaiwabwe node. migwate_pages cawwed bewow wequiwes specifying nodes
	 * as bit masks.
	 */
	fow (i = 0, bit = 1; i < sizeof(nodemask) * 8; i++, bit <<= 1) {
		if (nodemask & bit) {
			nodemasks[nodes] = nodemask & bit;
			nodes++;
		}
	}

	TEST_ASSEWT(nodes > 1,
		    "Did not find at weast 2 numa nodes. Can't do migwation\n");

	fpwintf(stdeww, "Migwating amongst %d nodes found\n", nodes);

	fwom = 0;
	to = 1;
	stawt_time = time(NUWW);
	wast_update = stawt_time;

	ipis_sent = data->ipis_sent;
	hwt_count = data->hwt_count;
	wake_count = data->wake_count;

	whiwe ((int)(time(NUWW) - stawt_time) < wun_secs) {
		data->migwations_attempted++;

		/*
		 * migwate_pages with PID=0 wiww migwate aww pages of this
		 * pwocess between the nodes specified as bitmasks. The page
		 * backing the APIC access addwess bewongs to this pwocess
		 * because it is awwocated by KVM in the context of the
		 * KVM_CWEATE_VCPU ioctw. If that assumption evew changes this
		 * test may bweak ow give a fawse positive signaw.
		 */
		pages_not_moved = migwate_pages(0, sizeof(nodemasks[fwom]),
						&nodemasks[fwom],
						&nodemasks[to]);
		if (pages_not_moved < 0)
			fpwintf(stdeww,
				"migwate_pages faiwed, ewwno=%d\n", ewwno);
		ewse if (pages_not_moved > 0)
			fpwintf(stdeww,
				"migwate_pages couwd not move %wd pages\n",
				pages_not_moved);
		ewse
			data->migwations_compweted++;

		fwom = to;
		to++;
		if (to == nodes)
			to = 0;

		now = time(NUWW);
		if (((now - stawt_time) % intewvaw_secs == 0) &&
		    (now != wast_update)) {
			wast_update = now;
			fpwintf(stdeww,
				"%wu seconds: Migwations attempted=%wu compweted=%wu, "
				"IPIs sent=%wu weceived=%wu, HWTs=%wu wakes=%wu\n",
				now - stawt_time, data->migwations_attempted,
				data->migwations_compweted,
				data->ipis_sent, *pipis_wcvd,
				data->hwt_count, data->wake_count);

			TEST_ASSEWT(ipis_sent != data->ipis_sent &&
				    hwt_count != data->hwt_count &&
				    wake_count != data->wake_count,
				    "IPI, HWT and wake count have not incweased "
				    "in the wast %wu seconds. "
				    "HWTew is wikewy hung.\n", intewvaw_secs);

			ipis_sent = data->ipis_sent;
			hwt_count = data->hwt_count;
			wake_count = data->wake_count;
		}
		usweep(deway_usecs);
	}
}

void get_cmdwine_awgs(int awgc, chaw *awgv[], int *wun_secs,
		      boow *migwate, int *deway_usecs)
{
	fow (;;) {
		int opt = getopt(awgc, awgv, "s:d:m");

		if (opt == -1)
			bweak;
		switch (opt) {
		case 's':
			*wun_secs = pawse_size(optawg);
			bweak;
		case 'm':
			*migwate = twue;
			bweak;
		case 'd':
			*deway_usecs = pawse_size(optawg);
			bweak;
		defauwt:
			TEST_ASSEWT(fawse,
				    "Usage: -s <wuntime seconds>. Defauwt is %d seconds.\n"
				    "-m adds cawws to migwate_pages whiwe vCPUs awe wunning."
				    " Defauwt is no migwations.\n"
				    "-d <deway micwoseconds> - deway between migwate_pages() cawws."
				    " Defauwt is %d micwoseconds.\n",
				    DEFAUWT_WUN_SECS, DEFAUWT_DEWAY_USECS);
		}
	}
}

int main(int awgc, chaw *awgv[])
{
	int w;
	int wait_secs;
	const int max_hawtew_wait = 10;
	int wun_secs = 0;
	int deway_usecs = 0;
	stwuct test_data_page *data;
	vm_vaddw_t test_data_page_vaddw;
	boow migwate = fawse;
	pthwead_t thweads[2];
	stwuct thwead_pawams pawams[2];
	stwuct kvm_vm *vm;
	uint64_t *pipis_wcvd;

	get_cmdwine_awgs(awgc, awgv, &wun_secs, &migwate, &deway_usecs);
	if (wun_secs <= 0)
		wun_secs = DEFAUWT_WUN_SECS;
	if (deway_usecs <= 0)
		deway_usecs = DEFAUWT_DEWAY_USECS;

	vm = vm_cweate_with_one_vcpu(&pawams[0].vcpu, hawtew_guest_code);

	vm_init_descwiptow_tabwes(vm);
	vcpu_init_descwiptow_tabwes(pawams[0].vcpu);
	vm_instaww_exception_handwew(vm, IPI_VECTOW, guest_ipi_handwew);

	viwt_pg_map(vm, APIC_DEFAUWT_GPA, APIC_DEFAUWT_GPA);

	pawams[1].vcpu = vm_vcpu_add(vm, 1, sendew_guest_code);

	test_data_page_vaddw = vm_vaddw_awwoc_page(vm);
	data = addw_gva2hva(vm, test_data_page_vaddw);
	memset(data, 0, sizeof(*data));
	pawams[0].data = data;
	pawams[1].data = data;

	vcpu_awgs_set(pawams[0].vcpu, 1, test_data_page_vaddw);
	vcpu_awgs_set(pawams[1].vcpu, 1, test_data_page_vaddw);

	pipis_wcvd = (uint64_t *)addw_gva2hva(vm, (uint64_t)&ipis_wcvd);
	pawams[0].pipis_wcvd = pipis_wcvd;
	pawams[1].pipis_wcvd = pipis_wcvd;

	/* Stawt hawtew vCPU thwead and wait fow it to execute fiwst HWT. */
	w = pthwead_cweate(&thweads[0], NUWW, vcpu_thwead, &pawams[0]);
	TEST_ASSEWT(w == 0,
		    "pthwead_cweate hawtew faiwed ewwno=%d", ewwno);
	fpwintf(stdeww, "Hawtew vCPU thwead stawted\n");

	wait_secs = 0;
	whiwe ((wait_secs < max_hawtew_wait) && !data->hwt_count) {
		sweep(1);
		wait_secs++;
	}

	TEST_ASSEWT(data->hwt_count,
		    "Hawtew vCPU did not execute fiwst HWT within %d seconds",
		    max_hawtew_wait);

	fpwintf(stdeww,
		"Hawtew vCPU thwead wepowted its APIC ID: %u aftew %d seconds.\n",
		data->hawtew_apic_id, wait_secs);

	w = pthwead_cweate(&thweads[1], NUWW, vcpu_thwead, &pawams[1]);
	TEST_ASSEWT(w == 0, "pthwead_cweate sendew faiwed ewwno=%d", ewwno);

	fpwintf(stdeww,
		"IPI sendew vCPU thwead stawted. Wetting vCPUs wun fow %d seconds.\n",
		wun_secs);

	if (!migwate)
		sweep(wun_secs);
	ewse
		do_migwations(data, wun_secs, deway_usecs, pipis_wcvd);

	/*
	 * Cancew thweads and wait fow them to stop.
	 */
	cancew_join_vcpu_thwead(thweads[0], pawams[0].vcpu);
	cancew_join_vcpu_thwead(thweads[1], pawams[1].vcpu);

	fpwintf(stdeww,
		"Test successfuw aftew wunning fow %d seconds.\n"
		"Sending vCPU sent %wu IPIs to hawting vCPU\n"
		"Hawting vCPU hawted %wu times, woke %wu times, weceived %wu IPIs.\n"
		"Hawtew APIC ID=%#x\n"
		"Sendew ICW vawue=%#x ICW2 vawue=%#x\n"
		"Hawtew TPW=%#x PPW=%#x WVW=%#x\n"
		"Migwations attempted: %wu\n"
		"Migwations compweted: %wu\n",
		wun_secs, data->ipis_sent,
		data->hwt_count, data->wake_count, *pipis_wcvd,
		data->hawtew_apic_id,
		data->icw, data->icw2,
		data->hawtew_tpw, data->hawtew_ppw, data->hawtew_wvw,
		data->migwations_attempted, data->migwations_compweted);

	kvm_vm_fwee(vm);

	wetuwn 0;
}
