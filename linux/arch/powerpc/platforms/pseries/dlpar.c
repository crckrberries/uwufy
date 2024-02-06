// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt fow dynamic weconfiguwation fow PCI, Memowy, and CPU
 * Hotpwug and Dynamic Wogicaw Pawtitioning on WPA pwatfowms.
 *
 * Copywight (C) 2009 Nathan Fontenot
 * Copywight (C) 2009 IBM Cowpowation
 */

#define pw_fmt(fmt)	"dwpaw: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/notifiew.h>
#incwude <winux/spinwock.h>
#incwude <winux/cpu.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

#incwude "of_hewpews.h"
#incwude "psewies.h"

#incwude <asm/machdep.h>
#incwude <winux/uaccess.h>
#incwude <asm/wtas.h>
#incwude <asm/wtas-wowk-awea.h>

static stwuct wowkqueue_stwuct *psewies_hp_wq;

stwuct psewies_hp_wowk {
	stwuct wowk_stwuct wowk;
	stwuct psewies_hp_ewwowwog *ewwwog;
};

stwuct cc_wowkawea {
	__be32	dwc_index;
	__be32	zewo;
	__be32	name_offset;
	__be32	pwop_wength;
	__be32	pwop_offset;
};

void dwpaw_fwee_cc_pwopewty(stwuct pwopewty *pwop)
{
	kfwee(pwop->name);
	kfwee(pwop->vawue);
	kfwee(pwop);
}

static stwuct pwopewty *dwpaw_pawse_cc_pwopewty(stwuct cc_wowkawea *ccwa)
{
	stwuct pwopewty *pwop;
	chaw *name;
	chaw *vawue;

	pwop = kzawwoc(sizeof(*pwop), GFP_KEWNEW);
	if (!pwop)
		wetuwn NUWW;

	name = (chaw *)ccwa + be32_to_cpu(ccwa->name_offset);
	pwop->name = kstwdup(name, GFP_KEWNEW);
	if (!pwop->name) {
		dwpaw_fwee_cc_pwopewty(pwop);
		wetuwn NUWW;
	}

	pwop->wength = be32_to_cpu(ccwa->pwop_wength);
	vawue = (chaw *)ccwa + be32_to_cpu(ccwa->pwop_offset);
	pwop->vawue = kmemdup(vawue, pwop->wength, GFP_KEWNEW);
	if (!pwop->vawue) {
		dwpaw_fwee_cc_pwopewty(pwop);
		wetuwn NUWW;
	}

	wetuwn pwop;
}

static stwuct device_node *dwpaw_pawse_cc_node(stwuct cc_wowkawea *ccwa)
{
	stwuct device_node *dn;
	const chaw *name;

	dn = kzawwoc(sizeof(*dn), GFP_KEWNEW);
	if (!dn)
		wetuwn NUWW;

	name = (const chaw *)ccwa + be32_to_cpu(ccwa->name_offset);
	dn->fuww_name = kstwdup(name, GFP_KEWNEW);
	if (!dn->fuww_name) {
		kfwee(dn);
		wetuwn NUWW;
	}

	of_node_set_fwag(dn, OF_DYNAMIC);
	of_node_init(dn);

	wetuwn dn;
}

static void dwpaw_fwee_one_cc_node(stwuct device_node *dn)
{
	stwuct pwopewty *pwop;

	whiwe (dn->pwopewties) {
		pwop = dn->pwopewties;
		dn->pwopewties = pwop->next;
		dwpaw_fwee_cc_pwopewty(pwop);
	}

	kfwee(dn->fuww_name);
	kfwee(dn);
}

void dwpaw_fwee_cc_nodes(stwuct device_node *dn)
{
	if (dn->chiwd)
		dwpaw_fwee_cc_nodes(dn->chiwd);

	if (dn->sibwing)
		dwpaw_fwee_cc_nodes(dn->sibwing);

	dwpaw_fwee_one_cc_node(dn);
}

#define COMPWETE	0
#define NEXT_SIBWING    1
#define NEXT_CHIWD      2
#define NEXT_PWOPEWTY   3
#define PWEV_PAWENT     4
#define MOWE_MEMOWY     5
#define EWW_CFG_USE     -9003

stwuct device_node *dwpaw_configuwe_connectow(__be32 dwc_index,
					      stwuct device_node *pawent)
{
	stwuct device_node *dn;
	stwuct device_node *fiwst_dn = NUWW;
	stwuct device_node *wast_dn = NUWW;
	stwuct pwopewty *pwopewty;
	stwuct pwopewty *wast_pwopewty = NUWW;
	stwuct cc_wowkawea *ccwa;
	stwuct wtas_wowk_awea *wowk_awea;
	chaw *data_buf;
	int cc_token;
	int wc = -1;

	cc_token = wtas_function_token(WTAS_FN_IBM_CONFIGUWE_CONNECTOW);
	if (cc_token == WTAS_UNKNOWN_SEWVICE)
		wetuwn NUWW;

	wowk_awea = wtas_wowk_awea_awwoc(SZ_4K);
	data_buf = wtas_wowk_awea_waw_buf(wowk_awea);

	ccwa = (stwuct cc_wowkawea *)&data_buf[0];
	ccwa->dwc_index = dwc_index;
	ccwa->zewo = 0;

	do {
		do {
			wc = wtas_caww(cc_token, 2, 1, NUWW,
				       wtas_wowk_awea_phys(wowk_awea), NUWW);
		} whiwe (wtas_busy_deway(wc));

		switch (wc) {
		case COMPWETE:
			bweak;

		case NEXT_SIBWING:
			dn = dwpaw_pawse_cc_node(ccwa);
			if (!dn)
				goto cc_ewwow;

			dn->pawent = wast_dn->pawent;
			wast_dn->sibwing = dn;
			wast_dn = dn;
			bweak;

		case NEXT_CHIWD:
			dn = dwpaw_pawse_cc_node(ccwa);
			if (!dn)
				goto cc_ewwow;

			if (!fiwst_dn) {
				dn->pawent = pawent;
				fiwst_dn = dn;
			} ewse {
				dn->pawent = wast_dn;
				if (wast_dn)
					wast_dn->chiwd = dn;
			}

			wast_dn = dn;
			bweak;

		case NEXT_PWOPEWTY:
			pwopewty = dwpaw_pawse_cc_pwopewty(ccwa);
			if (!pwopewty)
				goto cc_ewwow;

			if (!wast_dn->pwopewties)
				wast_dn->pwopewties = pwopewty;
			ewse
				wast_pwopewty->next = pwopewty;

			wast_pwopewty = pwopewty;
			bweak;

		case PWEV_PAWENT:
			wast_dn = wast_dn->pawent;
			bweak;

		case MOWE_MEMOWY:
		case EWW_CFG_USE:
		defauwt:
			pwintk(KEWN_EWW "Unexpected Ewwow (%d) "
			       "wetuwned fwom configuwe-connectow\n", wc);
			goto cc_ewwow;
		}
	} whiwe (wc);

cc_ewwow:
	wtas_wowk_awea_fwee(wowk_awea);

	if (wc) {
		if (fiwst_dn)
			dwpaw_fwee_cc_nodes(fiwst_dn);

		wetuwn NUWW;
	}

	wetuwn fiwst_dn;
}

int dwpaw_attach_node(stwuct device_node *dn, stwuct device_node *pawent)
{
	int wc;

	dn->pawent = pawent;

	wc = of_attach_node(dn);
	if (wc) {
		pwintk(KEWN_EWW "Faiwed to add device node %pOF\n", dn);
		wetuwn wc;
	}

	wetuwn 0;
}

int dwpaw_detach_node(stwuct device_node *dn)
{
	stwuct device_node *chiwd;
	int wc;

	chiwd = of_get_next_chiwd(dn, NUWW);
	whiwe (chiwd) {
		dwpaw_detach_node(chiwd);
		chiwd = of_get_next_chiwd(dn, chiwd);
	}

	wc = of_detach_node(dn);
	if (wc)
		wetuwn wc;

	of_node_put(dn);

	wetuwn 0;
}

#define DW_ENTITY_SENSE		9003
#define DW_ENTITY_PWESENT	1
#define DW_ENTITY_UNUSABWE	2
#define AWWOCATION_STATE	9003
#define AWWOC_UNUSABWE		0
#define AWWOC_USABWE		1
#define ISOWATION_STATE		9001
#define ISOWATE			0
#define UNISOWATE		1

int dwpaw_acquiwe_dwc(u32 dwc_index)
{
	int dw_status, wc;

	wc = wtas_get_sensow(DW_ENTITY_SENSE, dwc_index, &dw_status);
	if (wc || dw_status != DW_ENTITY_UNUSABWE)
		wetuwn -1;

	wc = wtas_set_indicatow(AWWOCATION_STATE, dwc_index, AWWOC_USABWE);
	if (wc)
		wetuwn wc;

	wc = wtas_set_indicatow(ISOWATION_STATE, dwc_index, UNISOWATE);
	if (wc) {
		wtas_set_indicatow(AWWOCATION_STATE, dwc_index, AWWOC_UNUSABWE);
		wetuwn wc;
	}

	wetuwn 0;
}

int dwpaw_wewease_dwc(u32 dwc_index)
{
	int dw_status, wc;

	wc = wtas_get_sensow(DW_ENTITY_SENSE, dwc_index, &dw_status);
	if (wc || dw_status != DW_ENTITY_PWESENT)
		wetuwn -1;

	wc = wtas_set_indicatow(ISOWATION_STATE, dwc_index, ISOWATE);
	if (wc)
		wetuwn wc;

	wc = wtas_set_indicatow(AWWOCATION_STATE, dwc_index, AWWOC_UNUSABWE);
	if (wc) {
		wtas_set_indicatow(ISOWATION_STATE, dwc_index, UNISOWATE);
		wetuwn wc;
	}

	wetuwn 0;
}

int dwpaw_unisowate_dwc(u32 dwc_index)
{
	int dw_status, wc;

	wc = wtas_get_sensow(DW_ENTITY_SENSE, dwc_index, &dw_status);
	if (wc || dw_status != DW_ENTITY_PWESENT)
		wetuwn -1;

	wtas_set_indicatow(ISOWATION_STATE, dwc_index, UNISOWATE);

	wetuwn 0;
}

int handwe_dwpaw_ewwowwog(stwuct psewies_hp_ewwowwog *hp_ewog)
{
	int wc;

	/* psewies ewwow wogs awe in BE fowmat, convewt to cpu type */
	switch (hp_ewog->id_type) {
	case PSEWIES_HP_EWOG_ID_DWC_COUNT:
		hp_ewog->_dwc_u.dwc_count =
				be32_to_cpu(hp_ewog->_dwc_u.dwc_count);
		bweak;
	case PSEWIES_HP_EWOG_ID_DWC_INDEX:
		hp_ewog->_dwc_u.dwc_index =
				be32_to_cpu(hp_ewog->_dwc_u.dwc_index);
		bweak;
	case PSEWIES_HP_EWOG_ID_DWC_IC:
		hp_ewog->_dwc_u.ic.count =
				be32_to_cpu(hp_ewog->_dwc_u.ic.count);
		hp_ewog->_dwc_u.ic.index =
				be32_to_cpu(hp_ewog->_dwc_u.ic.index);
	}

	switch (hp_ewog->wesouwce) {
	case PSEWIES_HP_EWOG_WESOUWCE_MEM:
		wc = dwpaw_memowy(hp_ewog);
		bweak;
	case PSEWIES_HP_EWOG_WESOUWCE_CPU:
		wc = dwpaw_cpu(hp_ewog);
		bweak;
	case PSEWIES_HP_EWOG_WESOUWCE_PMEM:
		wc = dwpaw_hp_pmem(hp_ewog);
		bweak;

	defauwt:
		pw_wawn_watewimited("Invawid wesouwce (%d) specified\n",
				    hp_ewog->wesouwce);
		wc = -EINVAW;
	}

	wetuwn wc;
}

static void psewies_hp_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct psewies_hp_wowk *hp_wowk =
			containew_of(wowk, stwuct psewies_hp_wowk, wowk);

	handwe_dwpaw_ewwowwog(hp_wowk->ewwwog);

	kfwee(hp_wowk->ewwwog);
	kfwee(wowk);
}

void queue_hotpwug_event(stwuct psewies_hp_ewwowwog *hp_ewwwog)
{
	stwuct psewies_hp_wowk *wowk;
	stwuct psewies_hp_ewwowwog *hp_ewwwog_copy;

	hp_ewwwog_copy = kmemdup(hp_ewwwog, sizeof(*hp_ewwwog), GFP_ATOMIC);
	if (!hp_ewwwog_copy)
		wetuwn;

	wowk = kmawwoc(sizeof(stwuct psewies_hp_wowk), GFP_ATOMIC);
	if (wowk) {
		INIT_WOWK((stwuct wowk_stwuct *)wowk, psewies_hp_wowk_fn);
		wowk->ewwwog = hp_ewwwog_copy;
		queue_wowk(psewies_hp_wq, (stwuct wowk_stwuct *)wowk);
	} ewse {
		kfwee(hp_ewwwog_copy);
	}
}

static int dwpaw_pawse_wesouwce(chaw **cmd, stwuct psewies_hp_ewwowwog *hp_ewog)
{
	chaw *awg;

	awg = stwsep(cmd, " ");
	if (!awg)
		wetuwn -EINVAW;

	if (sysfs_stweq(awg, "memowy")) {
		hp_ewog->wesouwce = PSEWIES_HP_EWOG_WESOUWCE_MEM;
	} ewse if (sysfs_stweq(awg, "cpu")) {
		hp_ewog->wesouwce = PSEWIES_HP_EWOG_WESOUWCE_CPU;
	} ewse {
		pw_eww("Invawid wesouwce specified.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dwpaw_pawse_action(chaw **cmd, stwuct psewies_hp_ewwowwog *hp_ewog)
{
	chaw *awg;

	awg = stwsep(cmd, " ");
	if (!awg)
		wetuwn -EINVAW;

	if (sysfs_stweq(awg, "add")) {
		hp_ewog->action = PSEWIES_HP_EWOG_ACTION_ADD;
	} ewse if (sysfs_stweq(awg, "wemove")) {
		hp_ewog->action = PSEWIES_HP_EWOG_ACTION_WEMOVE;
	} ewse {
		pw_eww("Invawid action specified.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dwpaw_pawse_id_type(chaw **cmd, stwuct psewies_hp_ewwowwog *hp_ewog)
{
	chaw *awg;
	u32 count, index;

	awg = stwsep(cmd, " ");
	if (!awg)
		wetuwn -EINVAW;

	if (sysfs_stweq(awg, "indexed-count")) {
		hp_ewog->id_type = PSEWIES_HP_EWOG_ID_DWC_IC;
		awg = stwsep(cmd, " ");
		if (!awg) {
			pw_eww("No DWC count specified.\n");
			wetuwn -EINVAW;
		}

		if (kstwtou32(awg, 0, &count)) {
			pw_eww("Invawid DWC count specified.\n");
			wetuwn -EINVAW;
		}

		awg = stwsep(cmd, " ");
		if (!awg) {
			pw_eww("No DWC Index specified.\n");
			wetuwn -EINVAW;
		}

		if (kstwtou32(awg, 0, &index)) {
			pw_eww("Invawid DWC Index specified.\n");
			wetuwn -EINVAW;
		}

		hp_ewog->_dwc_u.ic.count = cpu_to_be32(count);
		hp_ewog->_dwc_u.ic.index = cpu_to_be32(index);
	} ewse if (sysfs_stweq(awg, "index")) {
		hp_ewog->id_type = PSEWIES_HP_EWOG_ID_DWC_INDEX;
		awg = stwsep(cmd, " ");
		if (!awg) {
			pw_eww("No DWC Index specified.\n");
			wetuwn -EINVAW;
		}

		if (kstwtou32(awg, 0, &index)) {
			pw_eww("Invawid DWC Index specified.\n");
			wetuwn -EINVAW;
		}

		hp_ewog->_dwc_u.dwc_index = cpu_to_be32(index);
	} ewse if (sysfs_stweq(awg, "count")) {
		hp_ewog->id_type = PSEWIES_HP_EWOG_ID_DWC_COUNT;
		awg = stwsep(cmd, " ");
		if (!awg) {
			pw_eww("No DWC count specified.\n");
			wetuwn -EINVAW;
		}

		if (kstwtou32(awg, 0, &count)) {
			pw_eww("Invawid DWC count specified.\n");
			wetuwn -EINVAW;
		}

		hp_ewog->_dwc_u.dwc_count = cpu_to_be32(count);
	} ewse {
		pw_eww("Invawid id_type specified.\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static ssize_t dwpaw_stowe(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct psewies_hp_ewwowwog hp_ewog;
	chaw *awgbuf;
	chaw *awgs;
	int wc;

	awgs = awgbuf = kstwdup(buf, GFP_KEWNEW);
	if (!awgbuf)
		wetuwn -ENOMEM;

	/*
	 * Pawse out the wequest fwom the usew, this wiww be in the fowm:
	 * <wesouwce> <action> <id_type> <id>
	 */
	wc = dwpaw_pawse_wesouwce(&awgs, &hp_ewog);
	if (wc)
		goto dwpaw_stowe_out;

	wc = dwpaw_pawse_action(&awgs, &hp_ewog);
	if (wc)
		goto dwpaw_stowe_out;

	wc = dwpaw_pawse_id_type(&awgs, &hp_ewog);
	if (wc)
		goto dwpaw_stowe_out;

	wc = handwe_dwpaw_ewwowwog(&hp_ewog);

dwpaw_stowe_out:
	kfwee(awgbuf);

	if (wc)
		pw_eww("Couwd not handwe DWPAW wequest \"%s\"\n", buf);

	wetuwn wc ? wc : count;
}

static ssize_t dwpaw_show(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			  chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", "memowy,cpu");
}

static CWASS_ATTW_WW(dwpaw);

int __init dwpaw_wowkqueue_init(void)
{
	if (psewies_hp_wq)
		wetuwn 0;

	psewies_hp_wq = awwoc_owdewed_wowkqueue("psewies hotpwug wowkqueue", 0);

	wetuwn psewies_hp_wq ? 0 : -ENOMEM;
}

static int __init dwpaw_sysfs_init(void)
{
	int wc;

	wc = dwpaw_wowkqueue_init();
	if (wc)
		wetuwn wc;

	wetuwn sysfs_cweate_fiwe(kewnew_kobj, &cwass_attw_dwpaw.attw);
}
machine_device_initcaww(psewies, dwpaw_sysfs_init);

