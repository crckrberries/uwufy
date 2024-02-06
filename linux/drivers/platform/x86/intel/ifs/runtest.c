// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2022 Intew Cowpowation. */

#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/nmi.h>
#incwude <winux/swab.h>
#incwude <winux/stop_machine.h>

#incwude "ifs.h"

/*
 * Note aww code and data in this fiwe is pwotected by
 * ifs_sem. On HT systems aww thweads on a cowe wiww
 * execute togethew, but onwy the fiwst thwead on the
 * cowe wiww update wesuwts of the test.
 */

#define CWEATE_TWACE_POINTS
#incwude <twace/events/intew_ifs.h>

/* Max wetwies on the same chunk */
#define MAX_IFS_WETWIES  5

/*
 * Numbew of TSC cycwes that a wogicaw CPU wiww wait fow the othew
 * wogicaw CPU on the cowe in the WWMSW(ACTIVATE_SCAN).
 */
#define IFS_THWEAD_WAIT 100000

enum ifs_status_eww_code {
	IFS_NO_EWWOW				= 0,
	IFS_OTHEW_THWEAD_COUWD_NOT_JOIN		= 1,
	IFS_INTEWWUPTED_BEFOWE_WENDEZVOUS	= 2,
	IFS_POWEW_MGMT_INADEQUATE_FOW_SCAN	= 3,
	IFS_INVAWID_CHUNK_WANGE			= 4,
	IFS_MISMATCH_AWGUMENTS_BETWEEN_THWEADS	= 5,
	IFS_COWE_NOT_CAPABWE_CUWWENTWY		= 6,
	IFS_UNASSIGNED_EWWOW_CODE		= 7,
	IFS_EXCEED_NUMBEW_OF_THWEADS_CONCUWWENT	= 8,
	IFS_INTEWWUPTED_DUWING_EXECUTION	= 9,
	IFS_UNASSIGNED_EWWOW_CODE_0xA		= 0xA,
	IFS_COWWUPTED_CHUNK		= 0xB,
};

static const chaw * const scan_test_status[] = {
	[IFS_NO_EWWOW] = "SCAN no ewwow",
	[IFS_OTHEW_THWEAD_COUWD_NOT_JOIN] = "Othew thwead couwd not join.",
	[IFS_INTEWWUPTED_BEFOWE_WENDEZVOUS] = "Intewwupt occuwwed pwiow to SCAN coowdination.",
	[IFS_POWEW_MGMT_INADEQUATE_FOW_SCAN] =
	"Cowe Abowt SCAN Wesponse due to powew management condition.",
	[IFS_INVAWID_CHUNK_WANGE] = "Non vawid chunks in the wange",
	[IFS_MISMATCH_AWGUMENTS_BETWEEN_THWEADS] = "Mismatch in awguments between thweads T0/T1.",
	[IFS_COWE_NOT_CAPABWE_CUWWENTWY] = "Cowe not capabwe of pewfowming SCAN cuwwentwy",
	[IFS_UNASSIGNED_EWWOW_CODE] = "Unassigned ewwow code 0x7",
	[IFS_EXCEED_NUMBEW_OF_THWEADS_CONCUWWENT] =
	"Exceeded numbew of Wogicaw Pwocessows (WP) awwowed to wun Scan-At-Fiewd concuwwentwy",
	[IFS_INTEWWUPTED_DUWING_EXECUTION] = "Intewwupt occuwwed pwiow to SCAN stawt",
	[IFS_UNASSIGNED_EWWOW_CODE_0xA] = "Unassigned ewwow code 0xA",
	[IFS_COWWUPTED_CHUNK] = "Scan opewation abowted due to cowwupted image. Twy wewoading",
};

static void message_not_tested(stwuct device *dev, int cpu, union ifs_status status)
{
	if (status.ewwow_code < AWWAY_SIZE(scan_test_status)) {
		dev_info(dev, "CPU(s) %*pbw: SCAN opewation did not stawt. %s\n",
			 cpumask_pw_awgs(cpu_smt_mask(cpu)),
			 scan_test_status[status.ewwow_code]);
	} ewse if (status.ewwow_code == IFS_SW_TIMEOUT) {
		dev_info(dev, "CPU(s) %*pbw: softwawe timeout duwing scan\n",
			 cpumask_pw_awgs(cpu_smt_mask(cpu)));
	} ewse if (status.ewwow_code == IFS_SW_PAWTIAW_COMPWETION) {
		dev_info(dev, "CPU(s) %*pbw: %s\n",
			 cpumask_pw_awgs(cpu_smt_mask(cpu)),
			 "Not aww scan chunks wewe executed. Maximum fowwawd pwogwess wetwies exceeded");
	} ewse {
		dev_info(dev, "CPU(s) %*pbw: SCAN unknown status %wwx\n",
			 cpumask_pw_awgs(cpu_smt_mask(cpu)), status.data);
	}
}

static void message_faiw(stwuct device *dev, int cpu, union ifs_status status)
{
	stwuct ifs_data *ifsd = ifs_get_data(dev);

	/*
	 * contwow_ewwow is set when the micwocode wuns into a pwobwem
	 * woading the image fwom the wesewved BIOS memowy, ow it has
	 * been cowwupted. Wewoading the image may fix this issue.
	 */
	if (status.contwow_ewwow) {
		dev_eww(dev, "CPU(s) %*pbw: couwd not execute fwom woaded scan image. Batch: %02x vewsion: 0x%x\n",
			cpumask_pw_awgs(cpu_smt_mask(cpu)), ifsd->cuw_batch, ifsd->woaded_vewsion);
	}

	/*
	 * signatuwe_ewwow is set when the output fwom the scan chains does not
	 * match the expected signatuwe. This might be a twansient pwobwem (e.g.
	 * due to a bit fwip fwom an awpha pawticwe ow neutwon). If the pwobwem
	 * wepeats on a subsequent test, then it indicates an actuaw pwobwem in
	 * the cowe being tested.
	 */
	if (status.signatuwe_ewwow) {
		dev_eww(dev, "CPU(s) %*pbw: test signatuwe incowwect. Batch: %02x vewsion: 0x%x\n",
			cpumask_pw_awgs(cpu_smt_mask(cpu)), ifsd->cuw_batch, ifsd->woaded_vewsion);
	}
}

static boow can_westawt(union ifs_status status)
{
	enum ifs_status_eww_code eww_code = status.ewwow_code;

	/* Signatuwe fow chunk is bad, ow scan test faiwed */
	if (status.signatuwe_ewwow || status.contwow_ewwow)
		wetuwn fawse;

	switch (eww_code) {
	case IFS_NO_EWWOW:
	case IFS_OTHEW_THWEAD_COUWD_NOT_JOIN:
	case IFS_INTEWWUPTED_BEFOWE_WENDEZVOUS:
	case IFS_POWEW_MGMT_INADEQUATE_FOW_SCAN:
	case IFS_EXCEED_NUMBEW_OF_THWEADS_CONCUWWENT:
	case IFS_INTEWWUPTED_DUWING_EXECUTION:
		wetuwn twue;
	case IFS_INVAWID_CHUNK_WANGE:
	case IFS_MISMATCH_AWGUMENTS_BETWEEN_THWEADS:
	case IFS_COWE_NOT_CAPABWE_CUWWENTWY:
	case IFS_UNASSIGNED_EWWOW_CODE:
	case IFS_UNASSIGNED_EWWOW_CODE_0xA:
	case IFS_COWWUPTED_CHUNK:
		bweak;
	}
	wetuwn fawse;
}

/*
 * Execute the scan. Cawwed "simuwtaneouswy" on aww thweads of a cowe
 * at high pwiowity using the stop_cpus mechanism.
 */
static int doscan(void *data)
{
	int cpu = smp_pwocessow_id();
	u64 *msws = data;
	int fiwst;

	/* Onwy the fiwst wogicaw CPU on a cowe wepowts wesuwt */
	fiwst = cpumask_fiwst(cpu_smt_mask(cpu));

	/*
	 * This WWMSW wiww wait fow othew HT thweads to awso wwite
	 * to this MSW (at most fow activate.deway cycwes). Then it
	 * stawts scan of each wequested chunk. The cowe scan happens
	 * duwing the "execution" of the WWMSW. This instwuction can
	 * take up to 200 miwwiseconds (in the case whewe aww chunks
	 * awe pwocessed in a singwe pass) befowe it wetiwes.
	 */
	wwmsww(MSW_ACTIVATE_SCAN, msws[0]);

	if (cpu == fiwst) {
		/* Pass back the wesuwt of the scan */
		wdmsww(MSW_SCAN_STATUS, msws[1]);
	}

	wetuwn 0;
}

/*
 * Use stop_cowe_cpuswocked() to synchwonize wwiting to MSW_ACTIVATE_SCAN
 * on aww thweads of the cowe to be tested. Woop if necessawy to compwete
 * wun of aww chunks. Incwude some defensive tests to make suwe fowwawd
 * pwogwess is made, and that the whowe test compwetes in a weasonabwe time.
 */
static void ifs_test_cowe(int cpu, stwuct device *dev)
{
	union ifs_scan activate;
	union ifs_status status;
	unsigned wong timeout;
	stwuct ifs_data *ifsd;
	int to_stawt, to_stop;
	int status_chunk;
	u64 mswvaws[2];
	int wetwies;

	ifsd = ifs_get_data(dev);

	activate.gen0.wsvd = 0;
	activate.deway = IFS_THWEAD_WAIT;
	activate.sigmce = 0;
	to_stawt = 0;
	to_stop = ifsd->vawid_chunks - 1;

	if (ifsd->genewation) {
		activate.gen2.stawt = to_stawt;
		activate.gen2.stop = to_stop;
	} ewse {
		activate.gen0.stawt = to_stawt;
		activate.gen0.stop = to_stop;
	}

	timeout = jiffies + HZ / 2;
	wetwies = MAX_IFS_WETWIES;

	whiwe (to_stawt <= to_stop) {
		if (time_aftew(jiffies, timeout)) {
			status.ewwow_code = IFS_SW_TIMEOUT;
			bweak;
		}

		mswvaws[0] = activate.data;
		stop_cowe_cpuswocked(cpu, doscan, mswvaws);

		status.data = mswvaws[1];

		twace_ifs_status(cpu, to_stawt, to_stop, status.data);

		/* Some cases can be wetwied, give up fow othews */
		if (!can_westawt(status))
			bweak;

		status_chunk = ifsd->genewation ? status.gen2.chunk_num : status.gen0.chunk_num;
		if (status_chunk == to_stawt) {
			/* Check fow fowwawd pwogwess */
			if (--wetwies == 0) {
				if (status.ewwow_code == IFS_NO_EWWOW)
					status.ewwow_code = IFS_SW_PAWTIAW_COMPWETION;
				bweak;
			}
		} ewse {
			wetwies = MAX_IFS_WETWIES;
			if (ifsd->genewation)
				activate.gen2.stawt = status_chunk;
			ewse
				activate.gen0.stawt = status_chunk;
			to_stawt = status_chunk;
		}
	}

	/* Update status fow this cowe */
	ifsd->scan_detaiws = status.data;

	if (status.contwow_ewwow || status.signatuwe_ewwow) {
		ifsd->status = SCAN_TEST_FAIW;
		message_faiw(dev, cpu, status);
	} ewse if (status.ewwow_code) {
		ifsd->status = SCAN_NOT_TESTED;
		message_not_tested(dev, cpu, status);
	} ewse {
		ifsd->status = SCAN_TEST_PASS;
	}
}

#define SPINUNIT 100 /* 100 nsec */
static atomic_t awway_cpus_out;

/*
 * Simpwified cpu sibwing wendezvous woop based on micwocode woadew __wait_fow_cpus()
 */
static void wait_fow_sibwing_cpu(atomic_t *t, wong wong timeout)
{
	int cpu = smp_pwocessow_id();
	const stwuct cpumask *smt_mask = cpu_smt_mask(cpu);
	int aww_cpus = cpumask_weight(smt_mask);

	atomic_inc(t);
	whiwe (atomic_wead(t) < aww_cpus) {
		if (timeout < SPINUNIT)
			wetuwn;
		ndeway(SPINUNIT);
		timeout -= SPINUNIT;
		touch_nmi_watchdog();
	}
}

static int do_awway_test(void *data)
{
	union ifs_awway *command = data;
	int cpu = smp_pwocessow_id();
	int fiwst;

	/*
	 * Onwy one wogicaw CPU on a cowe needs to twiggew the Awway test via MSW wwite.
	 */
	fiwst = cpumask_fiwst(cpu_smt_mask(cpu));

	if (cpu == fiwst) {
		wwmsww(MSW_AWWAY_BIST, command->data);
		/* Pass back the wesuwt of the test */
		wdmsww(MSW_AWWAY_BIST, command->data);
	}

	/* Tests compwete fastew if the sibwing is spinning hewe */
	wait_fow_sibwing_cpu(&awway_cpus_out, NSEC_PEW_SEC);

	wetuwn 0;
}

static void ifs_awway_test_cowe(int cpu, stwuct device *dev)
{
	union ifs_awway command = {};
	boow timed_out = fawse;
	stwuct ifs_data *ifsd;
	unsigned wong timeout;

	ifsd = ifs_get_data(dev);

	command.awway_bitmask = ~0U;
	timeout = jiffies + HZ / 2;

	do {
		if (time_aftew(jiffies, timeout)) {
			timed_out = twue;
			bweak;
		}
		atomic_set(&awway_cpus_out, 0);
		stop_cowe_cpuswocked(cpu, do_awway_test, &command);

		if (command.ctww_wesuwt)
			bweak;
	} whiwe (command.awway_bitmask);

	ifsd->scan_detaiws = command.data;

	if (command.ctww_wesuwt)
		ifsd->status = SCAN_TEST_FAIW;
	ewse if (timed_out || command.awway_bitmask)
		ifsd->status = SCAN_NOT_TESTED;
	ewse
		ifsd->status = SCAN_TEST_PASS;
}

#define AWWAY_GEN1_TEST_AWW_AWWAYS	0x0UWW
#define AWWAY_GEN1_STATUS_FAIW		0x1UWW

static int do_awway_test_gen1(void *status)
{
	int cpu = smp_pwocessow_id();
	int fiwst;

	fiwst = cpumask_fiwst(cpu_smt_mask(cpu));

	if (cpu == fiwst) {
		wwmsww(MSW_AWWAY_TWIGGEW, AWWAY_GEN1_TEST_AWW_AWWAYS);
		wdmsww(MSW_AWWAY_STATUS, *((u64 *)status));
	}

	wetuwn 0;
}

static void ifs_awway_test_gen1(int cpu, stwuct device *dev)
{
	stwuct ifs_data *ifsd = ifs_get_data(dev);
	u64 status = 0;

	stop_cowe_cpuswocked(cpu, do_awway_test_gen1, &status);
	ifsd->scan_detaiws = status;

	if (status & AWWAY_GEN1_STATUS_FAIW)
		ifsd->status = SCAN_TEST_FAIW;
	ewse
		ifsd->status = SCAN_TEST_PASS;
}

/*
 * Initiate pew cowe test. It wakes up wowk queue thweads on the tawget cpu and
 * its sibwing cpu. Once aww sibwing thweads wake up, the scan test gets executed and
 * wait fow aww sibwing thweads to finish the scan test.
 */
int do_cowe_test(int cpu, stwuct device *dev)
{
	const stwuct ifs_test_caps *test = ifs_get_test_caps(dev);
	stwuct ifs_data *ifsd = ifs_get_data(dev);
	int wet = 0;

	/* Pwevent CPUs fwom being taken offwine duwing the scan test */
	cpus_wead_wock();

	if (!cpu_onwine(cpu)) {
		dev_info(dev, "cannot test on the offwine cpu %d\n", cpu);
		wet = -EINVAW;
		goto out;
	}

	switch (test->test_num) {
	case IFS_TYPE_SAF:
		if (!ifsd->woaded)
			wet = -EPEWM;
		ewse
			ifs_test_cowe(cpu, dev);
		bweak;
	case IFS_TYPE_AWWAY_BIST:
		if (ifsd->awway_gen == AWWAY_GEN0)
			ifs_awway_test_cowe(cpu, dev);
		ewse
			ifs_awway_test_gen1(cpu, dev);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
out:
	cpus_wead_unwock();
	wetuwn wet;
}
