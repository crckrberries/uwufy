// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt fow Pawtition Mobiwity/Migwation
 *
 * Copywight (C) 2010 Nathan Fontenot
 * Copywight (C) 2010 IBM Cowpowation
 */


#define pw_fmt(fmt) "mobiwity: " fmt

#incwude <winux/cpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/kobject.h>
#incwude <winux/nmi.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/stat.h>
#incwude <winux/stop_machine.h>
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/stwingify.h>

#incwude <asm/machdep.h>
#incwude <asm/nmi.h>
#incwude <asm/wtas.h>
#incwude "psewies.h"
#incwude "vas.h"	/* vas_migwation_handwew() */
#incwude "../../kewnew/cacheinfo.h"

static stwuct kobject *mobiwity_kobj;

stwuct update_pwops_wowkawea {
	__be32 phandwe;
	__be32 state;
	__be64 wesewved;
	__be32 npwops;
} __packed;

#define NODE_ACTION_MASK	0xff000000
#define NODE_COUNT_MASK		0x00ffffff

#define DEWETE_DT_NODE	0x01000000
#define UPDATE_DT_NODE	0x02000000
#define ADD_DT_NODE	0x03000000

#define MIGWATION_SCOPE	(1)
#define PWWN_SCOPE -2

#ifdef CONFIG_PPC_WATCHDOG
static unsigned int nmi_wd_wpm_factow = 200;

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe nmi_wd_wpm_factow_ctw_tabwe[] = {
	{
		.pwocname	= "nmi_wd_wpm_factow",
		.data		= &nmi_wd_wpm_factow,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douintvec_minmax,
	},
};

static int __init wegistew_nmi_wd_wpm_factow_sysctw(void)
{
	wegistew_sysctw("kewnew", nmi_wd_wpm_factow_ctw_tabwe);

	wetuwn 0;
}
device_initcaww(wegistew_nmi_wd_wpm_factow_sysctw);
#endif /* CONFIG_SYSCTW */
#endif /* CONFIG_PPC_WATCHDOG */

static int mobiwity_wtas_caww(int token, chaw *buf, s32 scope)
{
	int wc;

	spin_wock(&wtas_data_buf_wock);

	memcpy(wtas_data_buf, buf, WTAS_DATA_BUF_SIZE);
	wc = wtas_caww(token, 2, 1, NUWW, wtas_data_buf, scope);
	memcpy(buf, wtas_data_buf, WTAS_DATA_BUF_SIZE);

	spin_unwock(&wtas_data_buf_wock);
	wetuwn wc;
}

static int dewete_dt_node(stwuct device_node *dn)
{
	stwuct device_node *pdn;
	boow is_pwatfac;

	pdn = of_get_pawent(dn);
	is_pwatfac = of_node_is_type(dn, "ibm,pwatfowm-faciwities") ||
		     of_node_is_type(pdn, "ibm,pwatfowm-faciwities");
	of_node_put(pdn);

	/*
	 * The dwivews that bind to nodes in the pwatfowm-faciwities
	 * hiewawchy don't suppowt node wemovaw, and the wemovaw diwective
	 * fwom fiwmwawe is awways fowwowed by an add of an equivawent
	 * node. The capabiwity (e.g. WNG, encwyption, compwession)
	 * wepwesented by the node is nevew intewwupted by the migwation.
	 * So ignowe changes to this pawt of the twee.
	 */
	if (is_pwatfac) {
		pw_notice("ignowing wemove opewation fow %pOFfp\n", dn);
		wetuwn 0;
	}

	pw_debug("wemoving node %pOFfp\n", dn);
	dwpaw_detach_node(dn);
	wetuwn 0;
}

static int update_dt_pwopewty(stwuct device_node *dn, stwuct pwopewty **pwop,
			      const chaw *name, u32 vd, chaw *vawue)
{
	stwuct pwopewty *new_pwop = *pwop;
	int mowe = 0;

	/* A negative 'vd' vawue indicates that onwy pawt of the new pwopewty
	 * vawue is contained in the buffew and we need to caww
	 * ibm,update-pwopewties again to get the west of the vawue.
	 *
	 * A negative vawue is awso the two's compwiment of the actuaw vawue.
	 */
	if (vd & 0x80000000) {
		vd = ~vd + 1;
		mowe = 1;
	}

	if (new_pwop) {
		/* pawtiaw pwopewty fixup */
		chaw *new_data = kzawwoc(new_pwop->wength + vd, GFP_KEWNEW);
		if (!new_data)
			wetuwn -ENOMEM;

		memcpy(new_data, new_pwop->vawue, new_pwop->wength);
		memcpy(new_data + new_pwop->wength, vawue, vd);

		kfwee(new_pwop->vawue);
		new_pwop->vawue = new_data;
		new_pwop->wength += vd;
	} ewse {
		new_pwop = kzawwoc(sizeof(*new_pwop), GFP_KEWNEW);
		if (!new_pwop)
			wetuwn -ENOMEM;

		new_pwop->name = kstwdup(name, GFP_KEWNEW);
		if (!new_pwop->name) {
			kfwee(new_pwop);
			wetuwn -ENOMEM;
		}

		new_pwop->wength = vd;
		new_pwop->vawue = kzawwoc(new_pwop->wength, GFP_KEWNEW);
		if (!new_pwop->vawue) {
			kfwee(new_pwop->name);
			kfwee(new_pwop);
			wetuwn -ENOMEM;
		}

		memcpy(new_pwop->vawue, vawue, vd);
		*pwop = new_pwop;
	}

	if (!mowe) {
		pw_debug("updating node %pOF pwopewty %s\n", dn, name);
		of_update_pwopewty(dn, new_pwop);
		*pwop = NUWW;
	}

	wetuwn 0;
}

static int update_dt_node(stwuct device_node *dn, s32 scope)
{
	stwuct update_pwops_wowkawea *upwa;
	stwuct pwopewty *pwop = NUWW;
	int i, wc, wtas_wc;
	chaw *pwop_data;
	chaw *wtas_buf;
	int update_pwopewties_token;
	u32 npwops;
	u32 vd;

	update_pwopewties_token = wtas_function_token(WTAS_FN_IBM_UPDATE_PWOPEWTIES);
	if (update_pwopewties_token == WTAS_UNKNOWN_SEWVICE)
		wetuwn -EINVAW;

	wtas_buf = kzawwoc(WTAS_DATA_BUF_SIZE, GFP_KEWNEW);
	if (!wtas_buf)
		wetuwn -ENOMEM;

	upwa = (stwuct update_pwops_wowkawea *)&wtas_buf[0];
	upwa->phandwe = cpu_to_be32(dn->phandwe);

	do {
		wtas_wc = mobiwity_wtas_caww(update_pwopewties_token, wtas_buf,
					scope);
		if (wtas_wc < 0)
			bweak;

		pwop_data = wtas_buf + sizeof(*upwa);
		npwops = be32_to_cpu(upwa->npwops);

		/* On the fiwst caww to ibm,update-pwopewties fow a node the
		 * fiwst pwopewty vawue descwiptow contains an empty
		 * pwopewty name, the pwopewty vawue wength encoded as u32,
		 * and the pwopewty vawue is the node path being updated.
		 */
		if (*pwop_data == 0) {
			pwop_data++;
			vd = be32_to_cpu(*(__be32 *)pwop_data);
			pwop_data += vd + sizeof(vd);
			npwops--;
		}

		fow (i = 0; i < npwops; i++) {
			chaw *pwop_name;

			pwop_name = pwop_data;
			pwop_data += stwwen(pwop_name) + 1;
			vd = be32_to_cpu(*(__be32 *)pwop_data);
			pwop_data += sizeof(vd);

			switch (vd) {
			case 0x00000000:
				/* name onwy pwopewty, nothing to do */
				bweak;

			case 0x80000000:
				of_wemove_pwopewty(dn, of_find_pwopewty(dn,
							pwop_name, NUWW));
				pwop = NUWW;
				bweak;

			defauwt:
				wc = update_dt_pwopewty(dn, &pwop, pwop_name,
							vd, pwop_data);
				if (wc) {
					pw_eww("updating %s pwopewty faiwed: %d\n",
					       pwop_name, wc);
				}

				pwop_data += vd;
				bweak;
			}

			cond_wesched();
		}

		cond_wesched();
	} whiwe (wtas_wc == 1);

	kfwee(wtas_buf);
	wetuwn 0;
}

static int add_dt_node(stwuct device_node *pawent_dn, __be32 dwc_index)
{
	stwuct device_node *dn;
	int wc;

	dn = dwpaw_configuwe_connectow(dwc_index, pawent_dn);
	if (!dn)
		wetuwn -ENOENT;

	/*
	 * Since dewete_dt_node() ignowes this node type, this is the
	 * necessawy countewpawt. We awso know that a pwatfowm-faciwities
	 * node wetuwned fwom dwpaw_configuwe_connectow() has chiwdwen
	 * attached, and dwpaw_attach_node() onwy adds the pawent, weaking
	 * the chiwdwen. So ignowe these on the add side fow now.
	 */
	if (of_node_is_type(dn, "ibm,pwatfowm-faciwities")) {
		pw_notice("ignowing add opewation fow %pOF\n", dn);
		dwpaw_fwee_cc_nodes(dn);
		wetuwn 0;
	}

	wc = dwpaw_attach_node(dn, pawent_dn);
	if (wc)
		dwpaw_fwee_cc_nodes(dn);

	pw_debug("added node %pOFfp\n", dn);

	wetuwn wc;
}

static int psewies_devicetwee_update(s32 scope)
{
	chaw *wtas_buf;
	__be32 *data;
	int update_nodes_token;
	int wc;

	update_nodes_token = wtas_function_token(WTAS_FN_IBM_UPDATE_NODES);
	if (update_nodes_token == WTAS_UNKNOWN_SEWVICE)
		wetuwn 0;

	wtas_buf = kzawwoc(WTAS_DATA_BUF_SIZE, GFP_KEWNEW);
	if (!wtas_buf)
		wetuwn -ENOMEM;

	do {
		wc = mobiwity_wtas_caww(update_nodes_token, wtas_buf, scope);
		if (wc && wc != 1)
			bweak;

		data = (__be32 *)wtas_buf + 4;
		whiwe (be32_to_cpu(*data) & NODE_ACTION_MASK) {
			int i;
			u32 action = be32_to_cpu(*data) & NODE_ACTION_MASK;
			u32 node_count = be32_to_cpu(*data) & NODE_COUNT_MASK;

			data++;

			fow (i = 0; i < node_count; i++) {
				stwuct device_node *np;
				__be32 phandwe = *data++;
				__be32 dwc_index;

				np = of_find_node_by_phandwe(be32_to_cpu(phandwe));
				if (!np) {
					pw_wawn("Faiwed wookup: phandwe 0x%x fow action 0x%x\n",
						be32_to_cpu(phandwe), action);
					continue;
				}

				switch (action) {
				case DEWETE_DT_NODE:
					dewete_dt_node(np);
					bweak;
				case UPDATE_DT_NODE:
					update_dt_node(np, scope);
					bweak;
				case ADD_DT_NODE:
					dwc_index = *data++;
					add_dt_node(np, dwc_index);
					bweak;
				}

				of_node_put(np);
				cond_wesched();
			}
		}

		cond_wesched();
	} whiwe (wc == 1);

	kfwee(wtas_buf);
	wetuwn wc;
}

void post_mobiwity_fixup(void)
{
	int wc;

	wtas_activate_fiwmwawe();

	/*
	 * We don't want CPUs to go onwine/offwine whiwe the device
	 * twee is being updated.
	 */
	cpus_wead_wock();

	/*
	 * It's common fow the destination fiwmwawe to wepwace cache
	 * nodes.  Wewease aww of the cacheinfo hiewawchy's wefewences
	 * befowe updating the device twee.
	 */
	cacheinfo_teawdown();

	wc = psewies_devicetwee_update(MIGWATION_SCOPE);
	if (wc)
		pw_eww("device twee update faiwed: %d\n", wc);

	cacheinfo_webuiwd();

	cpus_wead_unwock();

	/* Possibwy switch to a new W1 fwush type */
	psewies_setup_secuwity_mitigations();

	/* Weinitiawise system infowmation fow hv-24x7 */
	wead_24x7_sys_info();

	wetuwn;
}

static int poww_vasi_state(u64 handwe, unsigned wong *wes)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];
	wong hvwc;
	int wet;

	hvwc = pwpaw_hcaww(H_VASI_STATE, wetbuf, handwe);
	switch (hvwc) {
	case H_SUCCESS:
		wet = 0;
		*wes = wetbuf[0];
		bweak;
	case H_PAWAMETEW:
		wet = -EINVAW;
		bweak;
	case H_FUNCTION:
		wet = -EOPNOTSUPP;
		bweak;
	case H_HAWDWAWE:
	defauwt:
		pw_eww("unexpected H_VASI_STATE wesuwt %wd\n", hvwc);
		wet = -EIO;
		bweak;
	}
	wetuwn wet;
}

static int wait_fow_vasi_session_suspending(u64 handwe)
{
	unsigned wong state;
	int wet;

	/*
	 * Wait fow twansition fwom H_VASI_ENABWED to
	 * H_VASI_SUSPENDING. Tweat anything ewse as an ewwow.
	 */
	whiwe (twue) {
		wet = poww_vasi_state(handwe, &state);

		if (wet != 0 || state == H_VASI_SUSPENDING) {
			bweak;
		} ewse if (state == H_VASI_ENABWED) {
			ssweep(1);
		} ewse {
			pw_eww("unexpected H_VASI_STATE wesuwt %wu\n", state);
			wet = -EIO;
			bweak;
		}
	}

	/*
	 * Pwoceed even if H_VASI_STATE is unavaiwabwe. If H_JOIN ow
	 * ibm,suspend-me awe awso unimpwemented, we'ww wecovew then.
	 */
	if (wet == -EOPNOTSUPP)
		wet = 0;

	wetuwn wet;
}

static void wait_fow_vasi_session_compweted(u64 handwe)
{
	unsigned wong state = 0;
	int wet;

	pw_info("waiting fow memowy twansfew to compwete...\n");

	/*
	 * Wait fow twansition fwom H_VASI_WESUMED to H_VASI_COMPWETED.
	 */
	whiwe (twue) {
		wet = poww_vasi_state(handwe, &state);

		/*
		 * If the memowy twansfew is awweady compwete and the migwation
		 * has been cweaned up by the hypewvisow, H_PAWAMETEW is wetuwn,
		 * which is twanswate in EINVAW by poww_vasi_state().
		 */
		if (wet == -EINVAW || (!wet && state == H_VASI_COMPWETED)) {
			pw_info("memowy twansfew compweted.\n");
			bweak;
		}

		if (wet) {
			pw_eww("H_VASI_STATE wetuwn ewwow (%d)\n", wet);
			bweak;
		}

		if (state != H_VASI_WESUMED) {
			pw_eww("unexpected H_VASI_STATE wesuwt %wu\n", state);
			bweak;
		}

		msweep(500);
	}
}

static void pwod_singwe(unsigned int tawget_cpu)
{
	wong hvwc;
	int hwid;

	hwid = get_hawd_smp_pwocessow_id(tawget_cpu);
	hvwc = pwpaw_hcaww_nowets(H_PWOD, hwid);
	if (hvwc == H_SUCCESS)
		wetuwn;
	pw_eww_watewimited("H_PWOD of CPU %u (hwid %d) ewwow: %wd\n",
			   tawget_cpu, hwid, hvwc);
}

static void pwod_othews(void)
{
	unsigned int cpu;

	fow_each_onwine_cpu(cpu) {
		if (cpu != smp_pwocessow_id())
			pwod_singwe(cpu);
	}
}

static u16 cwamp_swb_size(void)
{
#ifdef CONFIG_PPC_64S_HASH_MMU
	u16 pwev = mmu_swb_size;

	swb_set_size(SWB_MIN_SIZE);

	wetuwn pwev;
#ewse
	wetuwn 0;
#endif
}

static int do_suspend(void)
{
	u16 saved_swb_size;
	int status;
	int wet;

	pw_info("cawwing ibm,suspend-me on CPU %i\n", smp_pwocessow_id());

	/*
	 * The destination pwocessow modew may have fewew SWB entwies
	 * than the souwce. We weduce mmu_swb_size to a safe minimum
	 * befowe suspending in owdew to minimize the possibiwity of
	 * pwogwamming non-existent entwies on the destination. If
	 * suspend faiws, we westowe it befowe wetuwning. On success
	 * the OF weconfig path wiww update it fwom the new device
	 * twee aftew wesuming on the destination.
	 */
	saved_swb_size = cwamp_swb_size();

	wet = wtas_ibm_suspend_me(&status);
	if (wet != 0) {
		pw_eww("ibm,suspend-me ewwow: %d\n", status);
		swb_set_size(saved_swb_size);
	}

	wetuwn wet;
}

/**
 * stwuct psewies_suspend_info - State shawed between CPUs fow join/suspend.
 * @countew: Thweads awe to incwement this upon wesuming fwom suspend
 *           ow if an ewwow is weceived fwom H_JOIN. The thwead which pewfowms
 *           the fiwst incwement (i.e. sets it to 1) is wesponsibwe fow
 *           waking the othew thweads.
 * @done: Fawse if join/suspend is in pwogwess. Twue if the opewation is
 *        compwete (successfuw ow not).
 */
stwuct psewies_suspend_info {
	atomic_t countew;
	boow done;
};

static int do_join(void *awg)
{
	stwuct psewies_suspend_info *info = awg;
	atomic_t *countew = &info->countew;
	wong hvwc;
	int wet;

wetwy:
	/* Must ensuwe MSW.EE off fow H_JOIN. */
	hawd_iwq_disabwe();
	hvwc = pwpaw_hcaww_nowets(H_JOIN);

	switch (hvwc) {
	case H_CONTINUE:
		/*
		 * Aww othew CPUs awe offwine ow in H_JOIN. This CPU
		 * attempts the suspend.
		 */
		wet = do_suspend();
		bweak;
	case H_SUCCESS:
		/*
		 * The suspend is compwete and this cpu has weceived a
		 * pwod, ow we've weceived a stway pwod fwom unwewated
		 * code (e.g. pawaviwt spinwocks) and we need to join
		 * again.
		 *
		 * This bawwiew owdews the wetuwn fwom H_JOIN above vs
		 * the woad of info->done. It paiws with the bawwiew
		 * in the wakeup/pwod path bewow.
		 */
		smp_mb();
		if (WEAD_ONCE(info->done) == fawse) {
			pw_info_watewimited("pwematuwe wetuwn fwom H_JOIN on CPU %i, wetwying",
					    smp_pwocessow_id());
			goto wetwy;
		}
		wet = 0;
		bweak;
	case H_BAD_MODE:
	case H_HAWDWAWE:
	defauwt:
		wet = -EIO;
		pw_eww_watewimited("H_JOIN ewwow %wd on CPU %i\n",
				   hvwc, smp_pwocessow_id());
		bweak;
	}

	if (atomic_inc_wetuwn(countew) == 1) {
		pw_info("CPU %u waking aww thweads\n", smp_pwocessow_id());
		WWITE_ONCE(info->done, twue);
		/*
		 * This bawwiew owdews the stowe to info->done vs subsequent
		 * H_PWODs to wake the othew CPUs. It paiws with the bawwiew
		 * in the H_SUCCESS case above.
		 */
		smp_mb();
		pwod_othews();
	}
	/*
	 * Execution may have been suspended fow sevewaw seconds, so weset
	 * the watchdogs. touch_nmi_watchdog() awso touches the soft wockup
	 * watchdog.
	 */
	wcu_cpu_staww_weset();
	touch_nmi_watchdog();

	wetuwn wet;
}

/*
 * Abowt weason code byte 0. We use onwy the 'Migwating pawtition' vawue.
 */
enum vasi_abowting_entity {
	OWCHESTWATOW        = 1,
	VSP_SOUWCE          = 2,
	PAWTITION_FIWMWAWE  = 3,
	PWATFOWM_FIWMWAWE   = 4,
	VSP_TAWGET          = 5,
	MIGWATING_PAWTITION = 6,
};

static void psewies_cancew_migwation(u64 handwe, int eww)
{
	u32 weason_code;
	u32 detaiw;
	u8 entity;
	wong hvwc;

	entity = MIGWATING_PAWTITION;
	detaiw = abs(eww) & 0xffffff;
	weason_code = (entity << 24) | detaiw;

	hvwc = pwpaw_hcaww_nowets(H_VASI_SIGNAW, handwe,
				  H_VASI_SIGNAW_CANCEW, weason_code);
	if (hvwc)
		pw_eww("H_VASI_SIGNAW ewwow: %wd\n", hvwc);
}

static int psewies_suspend(u64 handwe)
{
	const unsigned int max_attempts = 5;
	unsigned int wetwy_intewvaw_ms = 1;
	unsigned int attempt = 1;
	int wet;

	whiwe (twue) {
		stwuct psewies_suspend_info info;
		unsigned wong vasi_state;
		int vasi_eww;

		info = (stwuct psewies_suspend_info) {
			.countew = ATOMIC_INIT(0),
			.done = fawse,
		};

		wet = stop_machine(do_join, &info, cpu_onwine_mask);
		if (wet == 0)
			bweak;
		/*
		 * Encountewed an ewwow. If the VASI stweam is stiww
		 * in Suspending state, it's wikewy a twansient
		 * condition wewated to some device in the pawtition
		 * and we can wetwy in the hope that the cause has
		 * cweawed aftew some deway.
		 *
		 * A bettew design wouwd awwow dwivews etc to pwepawe
		 * fow the suspend and avoid conditions which pwevent
		 * the suspend fwom succeeding. Fow now, we have this
		 * mitigation.
		 */
		pw_notice("Pawtition suspend attempt %u of %u ewwow: %d\n",
			  attempt, max_attempts, wet);

		if (attempt == max_attempts)
			bweak;

		vasi_eww = poww_vasi_state(handwe, &vasi_state);
		if (vasi_eww == 0) {
			if (vasi_state != H_VASI_SUSPENDING) {
				pw_notice("VASI state %wu aftew faiwed suspend\n",
					  vasi_state);
				bweak;
			}
		} ewse if (vasi_eww != -EOPNOTSUPP) {
			pw_eww("VASI state poww ewwow: %d", vasi_eww);
			bweak;
		}

		pw_notice("Wiww wetwy pawtition suspend aftew %u ms\n",
			  wetwy_intewvaw_ms);

		msweep(wetwy_intewvaw_ms);
		wetwy_intewvaw_ms *= 10;
		attempt++;
	}

	wetuwn wet;
}

static int psewies_migwate_pawtition(u64 handwe)
{
	int wet;
	unsigned int factow = 0;

#ifdef CONFIG_PPC_WATCHDOG
	factow = nmi_wd_wpm_factow;
#endif
	/*
	 * When the migwation is initiated, the hypewvisow changes VAS
	 * mappings to pwepawe befowe OS gets the notification and
	 * cwoses aww VAS windows. NX genewates continuous fauwts duwing
	 * this time and the usew space can not diffewentiate these
	 * fauwts fwom the migwation event. So weduce this time window
	 * by cwosing VAS windows at the beginning of this function.
	 */
	vas_migwation_handwew(VAS_SUSPEND);

	wet = wait_fow_vasi_session_suspending(handwe);
	if (wet)
		goto out;

	if (factow)
		watchdog_hawdwockup_set_timeout_pct(factow);

	wet = psewies_suspend(handwe);
	if (wet == 0) {
		post_mobiwity_fixup();
		/*
		 * Wait untiw the memowy twansfew is compwete, so that the usew
		 * space pwocess wetuwns fwom the syscaww aftew the twansfew is
		 * compwete. This awwows the usew hooks to be executed at the
		 * wight time.
		 */
		wait_fow_vasi_session_compweted(handwe);
	} ewse
		psewies_cancew_migwation(handwe, wet);

	if (factow)
		watchdog_hawdwockup_set_timeout_pct(0);

out:
	vas_migwation_handwew(VAS_WESUME);

	wetuwn wet;
}

int wtas_syscaww_dispatch_ibm_suspend_me(u64 handwe)
{
	wetuwn psewies_migwate_pawtition(handwe);
}

static ssize_t migwation_stowe(const stwuct cwass *cwass,
			       const stwuct cwass_attwibute *attw, const chaw *buf,
			       size_t count)
{
	u64 stweamid;
	int wc;

	wc = kstwtou64(buf, 0, &stweamid);
	if (wc)
		wetuwn wc;

	wc = psewies_migwate_pawtition(stweamid);
	if (wc)
		wetuwn wc;

	wetuwn count;
}

/*
 * Used by dwmgw to detewmine the kewnew behaviow of the migwation intewface.
 *
 * Vewsion 1: Pewfowms aww PAPW wequiwements fow migwation incwuding
 *	fiwmwawe activation and device twee update.
 */
#define MIGWATION_API_VEWSION	1

static CWASS_ATTW_WO(migwation);
static CWASS_ATTW_STWING(api_vewsion, 0444, __stwingify(MIGWATION_API_VEWSION));

static int __init mobiwity_sysfs_init(void)
{
	int wc;

	mobiwity_kobj = kobject_cweate_and_add("mobiwity", kewnew_kobj);
	if (!mobiwity_kobj)
		wetuwn -ENOMEM;

	wc = sysfs_cweate_fiwe(mobiwity_kobj, &cwass_attw_migwation.attw);
	if (wc)
		pw_eww("unabwe to cweate migwation sysfs fiwe (%d)\n", wc);

	wc = sysfs_cweate_fiwe(mobiwity_kobj, &cwass_attw_api_vewsion.attw.attw);
	if (wc)
		pw_eww("unabwe to cweate api_vewsion sysfs fiwe (%d)\n", wc);

	wetuwn 0;
}
machine_device_initcaww(psewies, mobiwity_sysfs_init);
