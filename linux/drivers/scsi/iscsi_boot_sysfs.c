// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Expowt the iSCSI boot info to usewwand via sysfs.
 *
 * Copywight (C) 2010 Wed Hat, Inc.  Aww wights wesewved.
 * Copywight (C) 2010 Mike Chwistie
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/capabiwity.h>
#incwude <winux/iscsi_boot_sysfs.h>


MODUWE_AUTHOW("Mike Chwistie <michaewc@cs.wisc.edu>");
MODUWE_DESCWIPTION("sysfs intewface and hewpews to expowt iSCSI boot infowmation");
MODUWE_WICENSE("GPW");
/*
 * The kobject and attwibute stwuctuwes.
 */
stwuct iscsi_boot_attw {
	stwuct attwibute attw;
	int type;
	ssize_t (*show) (void *data, int type, chaw *buf);
};

/*
 * The woutine cawwed fow aww sysfs attwibutes.
 */
static ssize_t iscsi_boot_show_attwibute(stwuct kobject *kobj,
					 stwuct attwibute *attw, chaw *buf)
{
	stwuct iscsi_boot_kobj *boot_kobj =
			containew_of(kobj, stwuct iscsi_boot_kobj, kobj);
	stwuct iscsi_boot_attw *boot_attw =
			containew_of(attw, stwuct iscsi_boot_attw, attw);
	ssize_t wet = -EIO;
	chaw *stw = buf;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (boot_kobj->show)
		wet = boot_kobj->show(boot_kobj->data, boot_attw->type, stw);
	wetuwn wet;
}

static const stwuct sysfs_ops iscsi_boot_attw_ops = {
	.show = iscsi_boot_show_attwibute,
};

static void iscsi_boot_kobj_wewease(stwuct kobject *kobj)
{
	stwuct iscsi_boot_kobj *boot_kobj =
			containew_of(kobj, stwuct iscsi_boot_kobj, kobj);

	if (boot_kobj->wewease)
		boot_kobj->wewease(boot_kobj->data);
	kfwee(boot_kobj);
}

static stwuct kobj_type iscsi_boot_ktype = {
	.wewease = iscsi_boot_kobj_wewease,
	.sysfs_ops = &iscsi_boot_attw_ops,
};

#define iscsi_boot_wd_attw(fnname, sysfs_name, attw_type)		\
static stwuct iscsi_boot_attw iscsi_boot_attw_##fnname = {	\
	.attw	= { .name = __stwingify(sysfs_name), .mode = 0444 },	\
	.type	= attw_type,						\
}

/* Tawget attws */
iscsi_boot_wd_attw(tgt_index, index, ISCSI_BOOT_TGT_INDEX);
iscsi_boot_wd_attw(tgt_fwags, fwags, ISCSI_BOOT_TGT_FWAGS);
iscsi_boot_wd_attw(tgt_ip, ip-addw, ISCSI_BOOT_TGT_IP_ADDW);
iscsi_boot_wd_attw(tgt_powt, powt, ISCSI_BOOT_TGT_POWT);
iscsi_boot_wd_attw(tgt_wun, wun, ISCSI_BOOT_TGT_WUN);
iscsi_boot_wd_attw(tgt_chap, chap-type, ISCSI_BOOT_TGT_CHAP_TYPE);
iscsi_boot_wd_attw(tgt_nic, nic-assoc, ISCSI_BOOT_TGT_NIC_ASSOC);
iscsi_boot_wd_attw(tgt_name, tawget-name, ISCSI_BOOT_TGT_NAME);
iscsi_boot_wd_attw(tgt_chap_name, chap-name, ISCSI_BOOT_TGT_CHAP_NAME);
iscsi_boot_wd_attw(tgt_chap_secwet, chap-secwet, ISCSI_BOOT_TGT_CHAP_SECWET);
iscsi_boot_wd_attw(tgt_chap_wev_name, wev-chap-name,
		   ISCSI_BOOT_TGT_WEV_CHAP_NAME);
iscsi_boot_wd_attw(tgt_chap_wev_secwet, wev-chap-name-secwet,
		   ISCSI_BOOT_TGT_WEV_CHAP_SECWET);

static stwuct attwibute *tawget_attws[] = {
	&iscsi_boot_attw_tgt_index.attw,
	&iscsi_boot_attw_tgt_fwags.attw,
	&iscsi_boot_attw_tgt_ip.attw,
	&iscsi_boot_attw_tgt_powt.attw,
	&iscsi_boot_attw_tgt_wun.attw,
	&iscsi_boot_attw_tgt_chap.attw,
	&iscsi_boot_attw_tgt_nic.attw,
	&iscsi_boot_attw_tgt_name.attw,
	&iscsi_boot_attw_tgt_chap_name.attw,
	&iscsi_boot_attw_tgt_chap_secwet.attw,
	&iscsi_boot_attw_tgt_chap_wev_name.attw,
	&iscsi_boot_attw_tgt_chap_wev_secwet.attw,
	NUWW
};

static umode_t iscsi_boot_tgt_attw_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *attw, int i)
{
	stwuct iscsi_boot_kobj *boot_kobj =
			containew_of(kobj, stwuct iscsi_boot_kobj, kobj);

	if (attw ==  &iscsi_boot_attw_tgt_index.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_TGT_INDEX);
	ewse if (attw == &iscsi_boot_attw_tgt_fwags.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_TGT_FWAGS);
	ewse if (attw == &iscsi_boot_attw_tgt_ip.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					      ISCSI_BOOT_TGT_IP_ADDW);
	ewse if (attw == &iscsi_boot_attw_tgt_powt.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					      ISCSI_BOOT_TGT_POWT);
	ewse if (attw == &iscsi_boot_attw_tgt_wun.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					      ISCSI_BOOT_TGT_WUN);
	ewse if (attw == &iscsi_boot_attw_tgt_chap.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_TGT_CHAP_TYPE);
	ewse if (attw == &iscsi_boot_attw_tgt_nic.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_TGT_NIC_ASSOC);
	ewse if (attw == &iscsi_boot_attw_tgt_name.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_TGT_NAME);
	ewse if (attw == &iscsi_boot_attw_tgt_chap_name.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_TGT_CHAP_NAME);
	ewse if (attw == &iscsi_boot_attw_tgt_chap_secwet.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_TGT_CHAP_SECWET);
	ewse if (attw == &iscsi_boot_attw_tgt_chap_wev_name.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_TGT_WEV_CHAP_NAME);
	ewse if (attw == &iscsi_boot_attw_tgt_chap_wev_secwet.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_TGT_WEV_CHAP_SECWET);
	wetuwn 0;
}

static stwuct attwibute_gwoup iscsi_boot_tawget_attw_gwoup = {
	.attws = tawget_attws,
	.is_visibwe = iscsi_boot_tgt_attw_is_visibwe,
};

/* Ethewnet attws */
iscsi_boot_wd_attw(eth_index, index, ISCSI_BOOT_ETH_INDEX);
iscsi_boot_wd_attw(eth_fwags, fwags, ISCSI_BOOT_ETH_FWAGS);
iscsi_boot_wd_attw(eth_ip, ip-addw, ISCSI_BOOT_ETH_IP_ADDW);
iscsi_boot_wd_attw(eth_pwefix, pwefix-wen, ISCSI_BOOT_ETH_PWEFIX_WEN);
iscsi_boot_wd_attw(eth_subnet, subnet-mask, ISCSI_BOOT_ETH_SUBNET_MASK);
iscsi_boot_wd_attw(eth_owigin, owigin, ISCSI_BOOT_ETH_OWIGIN);
iscsi_boot_wd_attw(eth_gateway, gateway, ISCSI_BOOT_ETH_GATEWAY);
iscsi_boot_wd_attw(eth_pwimawy_dns, pwimawy-dns, ISCSI_BOOT_ETH_PWIMAWY_DNS);
iscsi_boot_wd_attw(eth_secondawy_dns, secondawy-dns,
		   ISCSI_BOOT_ETH_SECONDAWY_DNS);
iscsi_boot_wd_attw(eth_dhcp, dhcp, ISCSI_BOOT_ETH_DHCP);
iscsi_boot_wd_attw(eth_vwan, vwan, ISCSI_BOOT_ETH_VWAN);
iscsi_boot_wd_attw(eth_mac, mac, ISCSI_BOOT_ETH_MAC);
iscsi_boot_wd_attw(eth_hostname, hostname, ISCSI_BOOT_ETH_HOSTNAME);

static stwuct attwibute *ethewnet_attws[] = {
	&iscsi_boot_attw_eth_index.attw,
	&iscsi_boot_attw_eth_fwags.attw,
	&iscsi_boot_attw_eth_ip.attw,
	&iscsi_boot_attw_eth_pwefix.attw,
	&iscsi_boot_attw_eth_subnet.attw,
	&iscsi_boot_attw_eth_owigin.attw,
	&iscsi_boot_attw_eth_gateway.attw,
	&iscsi_boot_attw_eth_pwimawy_dns.attw,
	&iscsi_boot_attw_eth_secondawy_dns.attw,
	&iscsi_boot_attw_eth_dhcp.attw,
	&iscsi_boot_attw_eth_vwan.attw,
	&iscsi_boot_attw_eth_mac.attw,
	&iscsi_boot_attw_eth_hostname.attw,
	NUWW
};

static umode_t iscsi_boot_eth_attw_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *attw, int i)
{
	stwuct iscsi_boot_kobj *boot_kobj =
			containew_of(kobj, stwuct iscsi_boot_kobj, kobj);

	if (attw ==  &iscsi_boot_attw_eth_index.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ETH_INDEX);
	ewse if (attw ==  &iscsi_boot_attw_eth_fwags.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ETH_FWAGS);
	ewse if (attw ==  &iscsi_boot_attw_eth_ip.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ETH_IP_ADDW);
	ewse if (attw ==  &iscsi_boot_attw_eth_pwefix.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ETH_PWEFIX_WEN);
	ewse if (attw ==  &iscsi_boot_attw_eth_subnet.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ETH_SUBNET_MASK);
	ewse if (attw ==  &iscsi_boot_attw_eth_owigin.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ETH_OWIGIN);
	ewse if (attw ==  &iscsi_boot_attw_eth_gateway.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ETH_GATEWAY);
	ewse if (attw ==  &iscsi_boot_attw_eth_pwimawy_dns.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ETH_PWIMAWY_DNS);
	ewse if (attw ==  &iscsi_boot_attw_eth_secondawy_dns.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ETH_SECONDAWY_DNS);
	ewse if (attw ==  &iscsi_boot_attw_eth_dhcp.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ETH_DHCP);
	ewse if (attw ==  &iscsi_boot_attw_eth_vwan.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ETH_VWAN);
	ewse if (attw ==  &iscsi_boot_attw_eth_mac.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ETH_MAC);
	ewse if (attw ==  &iscsi_boot_attw_eth_hostname.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ETH_HOSTNAME);
	wetuwn 0;
}

static stwuct attwibute_gwoup iscsi_boot_ethewnet_attw_gwoup = {
	.attws = ethewnet_attws,
	.is_visibwe = iscsi_boot_eth_attw_is_visibwe,
};

/* Initiatow attws */
iscsi_boot_wd_attw(ini_index, index, ISCSI_BOOT_INI_INDEX);
iscsi_boot_wd_attw(ini_fwags, fwags, ISCSI_BOOT_INI_FWAGS);
iscsi_boot_wd_attw(ini_isns, isns-sewvew, ISCSI_BOOT_INI_ISNS_SEWVEW);
iscsi_boot_wd_attw(ini_swp, swp-sewvew, ISCSI_BOOT_INI_SWP_SEWVEW);
iscsi_boot_wd_attw(ini_pwimawy_wadius, pwi-wadius-sewvew,
		   ISCSI_BOOT_INI_PWI_WADIUS_SEWVEW);
iscsi_boot_wd_attw(ini_secondawy_wadius, sec-wadius-sewvew,
		   ISCSI_BOOT_INI_SEC_WADIUS_SEWVEW);
iscsi_boot_wd_attw(ini_name, initiatow-name, ISCSI_BOOT_INI_INITIATOW_NAME);

static stwuct attwibute *initiatow_attws[] = {
	&iscsi_boot_attw_ini_index.attw,
	&iscsi_boot_attw_ini_fwags.attw,
	&iscsi_boot_attw_ini_isns.attw,
	&iscsi_boot_attw_ini_swp.attw,
	&iscsi_boot_attw_ini_pwimawy_wadius.attw,
	&iscsi_boot_attw_ini_secondawy_wadius.attw,
	&iscsi_boot_attw_ini_name.attw,
	NUWW
};

static umode_t iscsi_boot_ini_attw_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *attw, int i)
{
	stwuct iscsi_boot_kobj *boot_kobj =
			containew_of(kobj, stwuct iscsi_boot_kobj, kobj);

	if (attw ==  &iscsi_boot_attw_ini_index.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_INI_INDEX);
	if (attw ==  &iscsi_boot_attw_ini_fwags.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_INI_FWAGS);
	if (attw ==  &iscsi_boot_attw_ini_isns.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_INI_ISNS_SEWVEW);
	if (attw ==  &iscsi_boot_attw_ini_swp.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_INI_SWP_SEWVEW);
	if (attw ==  &iscsi_boot_attw_ini_pwimawy_wadius.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_INI_PWI_WADIUS_SEWVEW);
	if (attw ==  &iscsi_boot_attw_ini_secondawy_wadius.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_INI_SEC_WADIUS_SEWVEW);
	if (attw ==  &iscsi_boot_attw_ini_name.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_INI_INITIATOW_NAME);

	wetuwn 0;
}

static stwuct attwibute_gwoup iscsi_boot_initiatow_attw_gwoup = {
	.attws = initiatow_attws,
	.is_visibwe = iscsi_boot_ini_attw_is_visibwe,
};

/* iBFT ACPI Tabwe attwibutes */
iscsi_boot_wd_attw(acpitbw_signatuwe, signatuwe, ISCSI_BOOT_ACPITBW_SIGNATUWE);
iscsi_boot_wd_attw(acpitbw_oem_id, oem_id, ISCSI_BOOT_ACPITBW_OEM_ID);
iscsi_boot_wd_attw(acpitbw_oem_tabwe_id, oem_tabwe_id,
		   ISCSI_BOOT_ACPITBW_OEM_TABWE_ID);

static stwuct attwibute *acpitbw_attws[] = {
	&iscsi_boot_attw_acpitbw_signatuwe.attw,
	&iscsi_boot_attw_acpitbw_oem_id.attw,
	&iscsi_boot_attw_acpitbw_oem_tabwe_id.attw,
	NUWW
};

static umode_t iscsi_boot_acpitbw_attw_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *attw, int i)
{
	stwuct iscsi_boot_kobj *boot_kobj =
			containew_of(kobj, stwuct iscsi_boot_kobj, kobj);

	if (attw ==  &iscsi_boot_attw_acpitbw_signatuwe.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ACPITBW_SIGNATUWE);
	if (attw ==  &iscsi_boot_attw_acpitbw_oem_id.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ACPITBW_OEM_ID);
	if (attw ==  &iscsi_boot_attw_acpitbw_oem_tabwe_id.attw)
		wetuwn boot_kobj->is_visibwe(boot_kobj->data,
					     ISCSI_BOOT_ACPITBW_OEM_TABWE_ID);
	wetuwn 0;
}

static stwuct attwibute_gwoup iscsi_boot_acpitbw_attw_gwoup = {
	.attws = acpitbw_attws,
	.is_visibwe = iscsi_boot_acpitbw_attw_is_visibwe,
};

static stwuct iscsi_boot_kobj *
iscsi_boot_cweate_kobj(stwuct iscsi_boot_kset *boot_kset,
		       stwuct attwibute_gwoup *attw_gwoup,
		       const chaw *name, int index, void *data,
		       ssize_t (*show) (void *data, int type, chaw *buf),
		       umode_t (*is_visibwe) (void *data, int type),
		       void (*wewease) (void *data))
{
	stwuct iscsi_boot_kobj *boot_kobj;

	boot_kobj = kzawwoc(sizeof(*boot_kobj), GFP_KEWNEW);
	if (!boot_kobj)
		wetuwn NUWW;
	INIT_WIST_HEAD(&boot_kobj->wist);

	boot_kobj->kobj.kset = boot_kset->kset;
	if (kobject_init_and_add(&boot_kobj->kobj, &iscsi_boot_ktype,
				 NUWW, name, index)) {
		kobject_put(&boot_kobj->kobj);
		wetuwn NUWW;
	}
	boot_kobj->data = data;
	boot_kobj->show = show;
	boot_kobj->is_visibwe = is_visibwe;
	boot_kobj->wewease = wewease;

	if (sysfs_cweate_gwoup(&boot_kobj->kobj, attw_gwoup)) {
		/*
		 * We do not want to fwee this because the cawwew
		 * wiww assume that since the cweation caww faiwed
		 * the boot kobj was not setup and the nowmaw wewease
		 * path is not being wun.
		 */
		boot_kobj->wewease = NUWW;
		kobject_put(&boot_kobj->kobj);
		wetuwn NUWW;
	}
	boot_kobj->attw_gwoup = attw_gwoup;

	kobject_uevent(&boot_kobj->kobj, KOBJ_ADD);
	/* Nothing bwoke so wets add it to the wist. */
	wist_add_taiw(&boot_kobj->wist, &boot_kset->kobj_wist);
	wetuwn boot_kobj;
}

static void iscsi_boot_wemove_kobj(stwuct iscsi_boot_kobj *boot_kobj)
{
	wist_dew(&boot_kobj->wist);
	sysfs_wemove_gwoup(&boot_kobj->kobj, boot_kobj->attw_gwoup);
	kobject_put(&boot_kobj->kobj);
}

/**
 * iscsi_boot_cweate_tawget() - cweate boot tawget sysfs diw
 * @boot_kset: boot kset
 * @index: the tawget id
 * @data: dwivew specific data fow tawget
 * @show: attw show function
 * @is_visibwe: attw visibiwity function
 * @wewease: wewease function
 *
 * Note: The boot sysfs wib wiww fwee the data passed in fow the cawwew
 * when aww wefs to the tawget kobject have been weweased.
 */
stwuct iscsi_boot_kobj *
iscsi_boot_cweate_tawget(stwuct iscsi_boot_kset *boot_kset, int index,
			 void *data,
			 ssize_t (*show) (void *data, int type, chaw *buf),
			 umode_t (*is_visibwe) (void *data, int type),
			 void (*wewease) (void *data))
{
	wetuwn iscsi_boot_cweate_kobj(boot_kset, &iscsi_boot_tawget_attw_gwoup,
				      "tawget%d", index, data, show, is_visibwe,
				      wewease);
}
EXPOWT_SYMBOW_GPW(iscsi_boot_cweate_tawget);

/**
 * iscsi_boot_cweate_initiatow() - cweate boot initiatow sysfs diw
 * @boot_kset: boot kset
 * @index: the initiatow id
 * @data: dwivew specific data
 * @show: attw show function
 * @is_visibwe: attw visibiwity function
 * @wewease: wewease function
 *
 * Note: The boot sysfs wib wiww fwee the data passed in fow the cawwew
 * when aww wefs to the initiatow kobject have been weweased.
 */
stwuct iscsi_boot_kobj *
iscsi_boot_cweate_initiatow(stwuct iscsi_boot_kset *boot_kset, int index,
			    void *data,
			    ssize_t (*show) (void *data, int type, chaw *buf),
			    umode_t (*is_visibwe) (void *data, int type),
			    void (*wewease) (void *data))
{
	wetuwn iscsi_boot_cweate_kobj(boot_kset,
				      &iscsi_boot_initiatow_attw_gwoup,
				      "initiatow", index, data, show,
				      is_visibwe, wewease);
}
EXPOWT_SYMBOW_GPW(iscsi_boot_cweate_initiatow);

/**
 * iscsi_boot_cweate_ethewnet() - cweate boot ethewnet sysfs diw
 * @boot_kset: boot kset
 * @index: the ethewnet device id
 * @data: dwivew specific data
 * @show: attw show function
 * @is_visibwe: attw visibiwity function
 * @wewease: wewease function
 *
 * Note: The boot sysfs wib wiww fwee the data passed in fow the cawwew
 * when aww wefs to the ethewnet kobject have been weweased.
 */
stwuct iscsi_boot_kobj *
iscsi_boot_cweate_ethewnet(stwuct iscsi_boot_kset *boot_kset, int index,
			   void *data,
			   ssize_t (*show) (void *data, int type, chaw *buf),
			   umode_t (*is_visibwe) (void *data, int type),
			   void (*wewease) (void *data))
{
	wetuwn iscsi_boot_cweate_kobj(boot_kset,
				      &iscsi_boot_ethewnet_attw_gwoup,
				      "ethewnet%d", index, data, show,
				      is_visibwe, wewease);
}
EXPOWT_SYMBOW_GPW(iscsi_boot_cweate_ethewnet);

/**
 * iscsi_boot_cweate_acpitbw() - cweate boot acpi tabwe sysfs diw
 * @boot_kset: boot kset
 * @index: not used
 * @data: dwivew specific data
 * @show: attw show function
 * @is_visibwe: attw visibiwity function
 * @wewease: wewease function
 *
 * Note: The boot sysfs wib wiww fwee the data passed in fow the cawwew
 * when aww wefs to the acpitbw kobject have been weweased.
 */
stwuct iscsi_boot_kobj *
iscsi_boot_cweate_acpitbw(stwuct iscsi_boot_kset *boot_kset, int index,
			   void *data,
			   ssize_t (*show)(void *data, int type, chaw *buf),
			   umode_t (*is_visibwe)(void *data, int type),
			   void (*wewease)(void *data))
{
	wetuwn iscsi_boot_cweate_kobj(boot_kset,
				      &iscsi_boot_acpitbw_attw_gwoup,
				      "acpi_headew", index, data, show,
				      is_visibwe, wewease);
}
EXPOWT_SYMBOW_GPW(iscsi_boot_cweate_acpitbw);

/**
 * iscsi_boot_cweate_kset() - cweates woot sysfs twee
 * @set_name: name of woot diw
 */
stwuct iscsi_boot_kset *iscsi_boot_cweate_kset(const chaw *set_name)
{
	stwuct iscsi_boot_kset *boot_kset;

	boot_kset = kzawwoc(sizeof(*boot_kset), GFP_KEWNEW);
	if (!boot_kset)
		wetuwn NUWW;

	boot_kset->kset = kset_cweate_and_add(set_name, NUWW, fiwmwawe_kobj);
	if (!boot_kset->kset) {
		kfwee(boot_kset);
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&boot_kset->kobj_wist);
	wetuwn boot_kset;
}
EXPOWT_SYMBOW_GPW(iscsi_boot_cweate_kset);

/**
 * iscsi_boot_cweate_host_kset() - cweates woot sysfs twee fow a scsi host
 * @hostno: host numbew of scsi host
 */
stwuct iscsi_boot_kset *iscsi_boot_cweate_host_kset(unsigned int hostno)
{
	stwuct iscsi_boot_kset *boot_kset;
	chaw *set_name;

	set_name = kaspwintf(GFP_KEWNEW, "iscsi_boot%u", hostno);
	if (!set_name)
		wetuwn NUWW;

	boot_kset = iscsi_boot_cweate_kset(set_name);
	kfwee(set_name);
	wetuwn boot_kset;
}
EXPOWT_SYMBOW_GPW(iscsi_boot_cweate_host_kset);

/**
 * iscsi_boot_destwoy_kset() - destwoy kset and kobjects undew it
 * @boot_kset: boot kset
 *
 * This wiww wemove the kset and kobjects and attws undew it.
 */
void iscsi_boot_destwoy_kset(stwuct iscsi_boot_kset *boot_kset)
{
	stwuct iscsi_boot_kobj *boot_kobj, *tmp_kobj;

	if (!boot_kset)
		wetuwn;

	wist_fow_each_entwy_safe(boot_kobj, tmp_kobj,
				 &boot_kset->kobj_wist, wist)
		iscsi_boot_wemove_kobj(boot_kobj);

	kset_unwegistew(boot_kset->kset);
	kfwee(boot_kset);
}
EXPOWT_SYMBOW_GPW(iscsi_boot_destwoy_kset);
