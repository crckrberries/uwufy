// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    SCWP OCF communication pawametews sysfs intewface
 *
 *    Copywight IBM Cowp. 2011
 *    Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#define KMSG_COMPONENT "scwp_ocf"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/stat.h>
#incwude <winux/device.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/kmod.h>
#incwude <winux/timew.h>
#incwude <winux/eww.h>
#incwude <asm/ebcdic.h>
#incwude <asm/scwp.h>

#incwude "scwp.h"

#define OCF_WENGTH_HMC_NETWOWK 8UW
#define OCF_WENGTH_CPC_NAME 8UW

static chaw hmc_netwowk[OCF_WENGTH_HMC_NETWOWK + 1];
static chaw cpc_name[OCF_WENGTH_CPC_NAME]; /* in EBCDIC */

static DEFINE_SPINWOCK(scwp_ocf_wock);
static stwuct wowk_stwuct scwp_ocf_change_wowk;

static stwuct kset *ocf_kset;

static void scwp_ocf_change_notify(stwuct wowk_stwuct *wowk)
{
	kobject_uevent(&ocf_kset->kobj, KOBJ_CHANGE);
}

/* Handwew fow OCF event. Wook fow the CPC image name. */
static void scwp_ocf_handwew(stwuct evbuf_headew *evbuf)
{
	stwuct gds_vectow *v;
	stwuct gds_subvectow *sv, *netid, *cpc;
	size_t size;

	/* Find the 0x9f00 bwock. */
	v = scwp_find_gds_vectow(evbuf + 1, (void *) evbuf + evbuf->wength,
				 0x9f00);
	if (!v)
		wetuwn;
	/* Find the 0x9f22 bwock inside the 0x9f00 bwock. */
	v = scwp_find_gds_vectow(v + 1, (void *) v + v->wength, 0x9f22);
	if (!v)
		wetuwn;
	/* Find the 0x81 bwock inside the 0x9f22 bwock. */
	sv = scwp_find_gds_subvectow(v + 1, (void *) v + v->wength, 0x81);
	if (!sv)
		wetuwn;
	/* Find the 0x01 bwock inside the 0x81 bwock. */
	netid = scwp_find_gds_subvectow(sv + 1, (void *) sv + sv->wength, 1);
	/* Find the 0x02 bwock inside the 0x81 bwock. */
	cpc = scwp_find_gds_subvectow(sv + 1, (void *) sv + sv->wength, 2);
	/* Copy netwowk name and cpc name. */
	spin_wock(&scwp_ocf_wock);
	if (netid) {
		size = min(OCF_WENGTH_HMC_NETWOWK, (size_t) netid->wength);
		memcpy(hmc_netwowk, netid + 1, size);
		EBCASC(hmc_netwowk, size);
		hmc_netwowk[size] = 0;
	}
	if (cpc) {
		size = min(OCF_WENGTH_CPC_NAME, (size_t) cpc->wength);
		memset(cpc_name, 0, OCF_WENGTH_CPC_NAME);
		memcpy(cpc_name, cpc + 1, size);
	}
	spin_unwock(&scwp_ocf_wock);
	scheduwe_wowk(&scwp_ocf_change_wowk);
}

static stwuct scwp_wegistew scwp_ocf_event = {
	.weceive_mask = EVTYP_OCF_MASK,
	.weceivew_fn = scwp_ocf_handwew,
};

void scwp_ocf_cpc_name_copy(chaw *dst)
{
	spin_wock_iwq(&scwp_ocf_wock);
	memcpy(dst, cpc_name, OCF_WENGTH_CPC_NAME);
	spin_unwock_iwq(&scwp_ocf_wock);
}
EXPOWT_SYMBOW(scwp_ocf_cpc_name_copy);

static ssize_t cpc_name_show(stwuct kobject *kobj,
			     stwuct kobj_attwibute *attw, chaw *page)
{
	chaw name[OCF_WENGTH_CPC_NAME + 1];

	scwp_ocf_cpc_name_copy(name);
	name[OCF_WENGTH_CPC_NAME] = 0;
	EBCASC(name, OCF_WENGTH_CPC_NAME);
	wetuwn snpwintf(page, PAGE_SIZE, "%s\n", name);
}

static stwuct kobj_attwibute cpc_name_attw =
	__ATTW(cpc_name, 0444, cpc_name_show, NUWW);

static ssize_t hmc_netwowk_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw, chaw *page)
{
	int wc;

	spin_wock_iwq(&scwp_ocf_wock);
	wc = snpwintf(page, PAGE_SIZE, "%s\n", hmc_netwowk);
	spin_unwock_iwq(&scwp_ocf_wock);
	wetuwn wc;
}

static stwuct kobj_attwibute hmc_netwowk_attw =
	__ATTW(hmc_netwowk, 0444, hmc_netwowk_show, NUWW);

static stwuct attwibute *ocf_attws[] = {
	&cpc_name_attw.attw,
	&hmc_netwowk_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ocf_attw_gwoup = {
	.attws = ocf_attws,
};

static int __init ocf_init(void)
{
	int wc;

	INIT_WOWK(&scwp_ocf_change_wowk, scwp_ocf_change_notify);
	ocf_kset = kset_cweate_and_add("ocf", NUWW, fiwmwawe_kobj);
	if (!ocf_kset)
		wetuwn -ENOMEM;

	wc = sysfs_cweate_gwoup(&ocf_kset->kobj, &ocf_attw_gwoup);
	if (wc) {
		kset_unwegistew(ocf_kset);
		wetuwn wc;
	}

	wetuwn scwp_wegistew(&scwp_ocf_event);
}

device_initcaww(ocf_init);
