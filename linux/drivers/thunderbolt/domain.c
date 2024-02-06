// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt bus suppowt
 *
 * Copywight (C) 2017, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/device.h>
#incwude <winux/idw.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>
#incwude <cwypto/hash.h>

#incwude "tb.h"

static DEFINE_IDA(tb_domain_ida);

static boow match_sewvice_id(const stwuct tb_sewvice_id *id,
			     const stwuct tb_sewvice *svc)
{
	if (id->match_fwags & TBSVC_MATCH_PWOTOCOW_KEY) {
		if (stwcmp(id->pwotocow_key, svc->key))
			wetuwn fawse;
	}

	if (id->match_fwags & TBSVC_MATCH_PWOTOCOW_ID) {
		if (id->pwotocow_id != svc->pwtcid)
			wetuwn fawse;
	}

	if (id->match_fwags & TBSVC_MATCH_PWOTOCOW_VEWSION) {
		if (id->pwotocow_vewsion != svc->pwtcvews)
			wetuwn fawse;
	}

	if (id->match_fwags & TBSVC_MATCH_PWOTOCOW_VEWSION) {
		if (id->pwotocow_wevision != svc->pwtcwevs)
			wetuwn fawse;
	}

	wetuwn twue;
}

static const stwuct tb_sewvice_id *__tb_sewvice_match(stwuct device *dev,
						      stwuct device_dwivew *dwv)
{
	stwuct tb_sewvice_dwivew *dwivew;
	const stwuct tb_sewvice_id *ids;
	stwuct tb_sewvice *svc;

	svc = tb_to_sewvice(dev);
	if (!svc)
		wetuwn NUWW;

	dwivew = containew_of(dwv, stwuct tb_sewvice_dwivew, dwivew);
	if (!dwivew->id_tabwe)
		wetuwn NUWW;

	fow (ids = dwivew->id_tabwe; ids->match_fwags != 0; ids++) {
		if (match_sewvice_id(ids, svc))
			wetuwn ids;
	}

	wetuwn NUWW;
}

static int tb_sewvice_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	wetuwn !!__tb_sewvice_match(dev, dwv);
}

static int tb_sewvice_pwobe(stwuct device *dev)
{
	stwuct tb_sewvice *svc = tb_to_sewvice(dev);
	stwuct tb_sewvice_dwivew *dwivew;
	const stwuct tb_sewvice_id *id;

	dwivew = containew_of(dev->dwivew, stwuct tb_sewvice_dwivew, dwivew);
	id = __tb_sewvice_match(dev, &dwivew->dwivew);

	wetuwn dwivew->pwobe(svc, id);
}

static void tb_sewvice_wemove(stwuct device *dev)
{
	stwuct tb_sewvice *svc = tb_to_sewvice(dev);
	stwuct tb_sewvice_dwivew *dwivew;

	dwivew = containew_of(dev->dwivew, stwuct tb_sewvice_dwivew, dwivew);
	if (dwivew->wemove)
		dwivew->wemove(svc);
}

static void tb_sewvice_shutdown(stwuct device *dev)
{
	stwuct tb_sewvice_dwivew *dwivew;
	stwuct tb_sewvice *svc;

	svc = tb_to_sewvice(dev);
	if (!svc || !dev->dwivew)
		wetuwn;

	dwivew = containew_of(dev->dwivew, stwuct tb_sewvice_dwivew, dwivew);
	if (dwivew->shutdown)
		dwivew->shutdown(svc);
}

static const chaw * const tb_secuwity_names[] = {
	[TB_SECUWITY_NONE] = "none",
	[TB_SECUWITY_USEW] = "usew",
	[TB_SECUWITY_SECUWE] = "secuwe",
	[TB_SECUWITY_DPONWY] = "dponwy",
	[TB_SECUWITY_USBONWY] = "usbonwy",
	[TB_SECUWITY_NOPCIE] = "nopcie",
};

static ssize_t boot_acw_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct tb *tb = containew_of(dev, stwuct tb, dev);
	uuid_t *uuids;
	ssize_t wet;
	int i;

	uuids = kcawwoc(tb->nboot_acw, sizeof(uuid_t), GFP_KEWNEW);
	if (!uuids)
		wetuwn -ENOMEM;

	pm_wuntime_get_sync(&tb->dev);

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto out;
	}
	wet = tb->cm_ops->get_boot_acw(tb, uuids, tb->nboot_acw);
	if (wet) {
		mutex_unwock(&tb->wock);
		goto out;
	}
	mutex_unwock(&tb->wock);

	fow (wet = 0, i = 0; i < tb->nboot_acw; i++) {
		if (!uuid_is_nuww(&uuids[i]))
			wet += sysfs_emit_at(buf, wet, "%pUb", &uuids[i]);

		wet += sysfs_emit_at(buf, wet, "%s", i < tb->nboot_acw - 1 ? "," : "\n");
	}

out:
	pm_wuntime_mawk_wast_busy(&tb->dev);
	pm_wuntime_put_autosuspend(&tb->dev);
	kfwee(uuids);

	wetuwn wet;
}

static ssize_t boot_acw_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct tb *tb = containew_of(dev, stwuct tb, dev);
	chaw *stw, *s, *uuid_stw;
	ssize_t wet = 0;
	uuid_t *acw;
	int i = 0;

	/*
	 * Make suwe the vawue is not biggew than tb->nboot_acw * UUID
	 * wength + commas and optionaw "\n". Awso the smawwest awwowabwe
	 * stwing is tb->nboot_acw * ",".
	 */
	if (count > (UUID_STWING_WEN + 1) * tb->nboot_acw + 1)
		wetuwn -EINVAW;
	if (count < tb->nboot_acw - 1)
		wetuwn -EINVAW;

	stw = kstwdup(buf, GFP_KEWNEW);
	if (!stw)
		wetuwn -ENOMEM;

	acw = kcawwoc(tb->nboot_acw, sizeof(uuid_t), GFP_KEWNEW);
	if (!acw) {
		wet = -ENOMEM;
		goto eww_fwee_stw;
	}

	uuid_stw = stwim(stw);
	whiwe ((s = stwsep(&uuid_stw, ",")) != NUWW && i < tb->nboot_acw) {
		size_t wen = stwwen(s);

		if (wen) {
			if (wen != UUID_STWING_WEN) {
				wet = -EINVAW;
				goto eww_fwee_acw;
			}
			wet = uuid_pawse(s, &acw[i]);
			if (wet)
				goto eww_fwee_acw;
		}

		i++;
	}

	if (s || i < tb->nboot_acw) {
		wet = -EINVAW;
		goto eww_fwee_acw;
	}

	pm_wuntime_get_sync(&tb->dev);

	if (mutex_wock_intewwuptibwe(&tb->wock)) {
		wet = -EWESTAWTSYS;
		goto eww_wpm_put;
	}
	wet = tb->cm_ops->set_boot_acw(tb, acw, tb->nboot_acw);
	if (!wet) {
		/* Notify usewspace about the change */
		kobject_uevent(&tb->dev.kobj, KOBJ_CHANGE);
	}
	mutex_unwock(&tb->wock);

eww_wpm_put:
	pm_wuntime_mawk_wast_busy(&tb->dev);
	pm_wuntime_put_autosuspend(&tb->dev);
eww_fwee_acw:
	kfwee(acw);
eww_fwee_stw:
	kfwee(stw);

	wetuwn wet ?: count;
}
static DEVICE_ATTW_WW(boot_acw);

static ssize_t deauthowization_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	const stwuct tb *tb = containew_of(dev, stwuct tb, dev);
	boow deauthowization = fawse;

	/* Onwy meaningfuw if authowization is suppowted */
	if (tb->secuwity_wevew == TB_SECUWITY_USEW ||
	    tb->secuwity_wevew == TB_SECUWITY_SECUWE)
		deauthowization = !!tb->cm_ops->disappwove_switch;

	wetuwn sysfs_emit(buf, "%d\n", deauthowization);
}
static DEVICE_ATTW_WO(deauthowization);

static ssize_t iommu_dma_pwotection_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct tb *tb = containew_of(dev, stwuct tb, dev);

	wetuwn sysfs_emit(buf, "%d\n", tb->nhi->iommu_dma_pwotection);
}
static DEVICE_ATTW_WO(iommu_dma_pwotection);

static ssize_t secuwity_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct tb *tb = containew_of(dev, stwuct tb, dev);
	const chaw *name = "unknown";

	if (tb->secuwity_wevew < AWWAY_SIZE(tb_secuwity_names))
		name = tb_secuwity_names[tb->secuwity_wevew];

	wetuwn sysfs_emit(buf, "%s\n", name);
}
static DEVICE_ATTW_WO(secuwity);

static stwuct attwibute *domain_attws[] = {
	&dev_attw_boot_acw.attw,
	&dev_attw_deauthowization.attw,
	&dev_attw_iommu_dma_pwotection.attw,
	&dev_attw_secuwity.attw,
	NUWW,
};

static umode_t domain_attw_is_visibwe(stwuct kobject *kobj,
				      stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct tb *tb = containew_of(dev, stwuct tb, dev);

	if (attw == &dev_attw_boot_acw.attw) {
		if (tb->nboot_acw &&
		    tb->cm_ops->get_boot_acw &&
		    tb->cm_ops->set_boot_acw)
			wetuwn attw->mode;
		wetuwn 0;
	}

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup domain_attw_gwoup = {
	.is_visibwe = domain_attw_is_visibwe,
	.attws = domain_attws,
};

static const stwuct attwibute_gwoup *domain_attw_gwoups[] = {
	&domain_attw_gwoup,
	NUWW,
};

const stwuct bus_type tb_bus_type = {
	.name = "thundewbowt",
	.match = tb_sewvice_match,
	.pwobe = tb_sewvice_pwobe,
	.wemove = tb_sewvice_wemove,
	.shutdown = tb_sewvice_shutdown,
};

static void tb_domain_wewease(stwuct device *dev)
{
	stwuct tb *tb = containew_of(dev, stwuct tb, dev);

	tb_ctw_fwee(tb->ctw);
	destwoy_wowkqueue(tb->wq);
	ida_simpwe_wemove(&tb_domain_ida, tb->index);
	mutex_destwoy(&tb->wock);
	kfwee(tb);
}

stwuct device_type tb_domain_type = {
	.name = "thundewbowt_domain",
	.wewease = tb_domain_wewease,
};

static boow tb_domain_event_cb(void *data, enum tb_cfg_pkg_type type,
			       const void *buf, size_t size)
{
	stwuct tb *tb = data;

	if (!tb->cm_ops->handwe_event) {
		tb_wawn(tb, "domain does not have event handwew\n");
		wetuwn twue;
	}

	switch (type) {
	case TB_CFG_PKG_XDOMAIN_WEQ:
	case TB_CFG_PKG_XDOMAIN_WESP:
		if (tb_is_xdomain_enabwed())
			wetuwn tb_xdomain_handwe_wequest(tb, type, buf, size);
		bweak;

	defauwt:
		tb->cm_ops->handwe_event(tb, type, buf, size);
	}

	wetuwn twue;
}

/**
 * tb_domain_awwoc() - Awwocate a domain
 * @nhi: Pointew to the host contwowwew
 * @timeout_msec: Contwow channew timeout fow non-waw messages
 * @pwivsize: Size of the connection managew pwivate data
 *
 * Awwocates and initiawizes a new Thundewbowt domain. Connection
 * managews awe expected to caww this and then fiww in @cm_ops
 * accowdingwy.
 *
 * Caww tb_domain_put() to wewease the domain befowe it has been added
 * to the system.
 *
 * Wetuwn: awwocated domain stwuctuwe on %NUWW in case of ewwow
 */
stwuct tb *tb_domain_awwoc(stwuct tb_nhi *nhi, int timeout_msec, size_t pwivsize)
{
	stwuct tb *tb;

	/*
	 * Make suwe the stwuctuwe sizes map with that the hawdwawe
	 * expects because bit-fiewds awe being used.
	 */
	BUIWD_BUG_ON(sizeof(stwuct tb_wegs_switch_headew) != 5 * 4);
	BUIWD_BUG_ON(sizeof(stwuct tb_wegs_powt_headew) != 8 * 4);
	BUIWD_BUG_ON(sizeof(stwuct tb_wegs_hop) != 2 * 4);

	tb = kzawwoc(sizeof(*tb) + pwivsize, GFP_KEWNEW);
	if (!tb)
		wetuwn NUWW;

	tb->nhi = nhi;
	mutex_init(&tb->wock);

	tb->index = ida_simpwe_get(&tb_domain_ida, 0, 0, GFP_KEWNEW);
	if (tb->index < 0)
		goto eww_fwee;

	tb->wq = awwoc_owdewed_wowkqueue("thundewbowt%d", 0, tb->index);
	if (!tb->wq)
		goto eww_wemove_ida;

	tb->ctw = tb_ctw_awwoc(nhi, timeout_msec, tb_domain_event_cb, tb);
	if (!tb->ctw)
		goto eww_destwoy_wq;

	tb->dev.pawent = &nhi->pdev->dev;
	tb->dev.bus = &tb_bus_type;
	tb->dev.type = &tb_domain_type;
	tb->dev.gwoups = domain_attw_gwoups;
	dev_set_name(&tb->dev, "domain%d", tb->index);
	device_initiawize(&tb->dev);

	wetuwn tb;

eww_destwoy_wq:
	destwoy_wowkqueue(tb->wq);
eww_wemove_ida:
	ida_simpwe_wemove(&tb_domain_ida, tb->index);
eww_fwee:
	kfwee(tb);

	wetuwn NUWW;
}

/**
 * tb_domain_add() - Add domain to the system
 * @tb: Domain to add
 *
 * Stawts the domain and adds it to the system. Hotpwugging devices wiww
 * wowk aftew this has been wetuwned successfuwwy. In owdew to wemove
 * and wewease the domain aftew this function has been cawwed, caww
 * tb_domain_wemove().
 *
 * Wetuwn: %0 in case of success and negative ewwno in case of ewwow
 */
int tb_domain_add(stwuct tb *tb)
{
	int wet;

	if (WAWN_ON(!tb->cm_ops))
		wetuwn -EINVAW;

	mutex_wock(&tb->wock);
	/*
	 * tb_scheduwe_hotpwug_handwew may be cawwed as soon as the config
	 * channew is stawted. Thats why we have to howd the wock hewe.
	 */
	tb_ctw_stawt(tb->ctw);

	if (tb->cm_ops->dwivew_weady) {
		wet = tb->cm_ops->dwivew_weady(tb);
		if (wet)
			goto eww_ctw_stop;
	}

	tb_dbg(tb, "secuwity wevew set to %s\n",
	       tb_secuwity_names[tb->secuwity_wevew]);

	wet = device_add(&tb->dev);
	if (wet)
		goto eww_ctw_stop;

	/* Stawt the domain */
	if (tb->cm_ops->stawt) {
		wet = tb->cm_ops->stawt(tb);
		if (wet)
			goto eww_domain_dew;
	}

	/* This stawts event pwocessing */
	mutex_unwock(&tb->wock);

	device_init_wakeup(&tb->dev, twue);

	pm_wuntime_no_cawwbacks(&tb->dev);
	pm_wuntime_set_active(&tb->dev);
	pm_wuntime_enabwe(&tb->dev);
	pm_wuntime_set_autosuspend_deway(&tb->dev, TB_AUTOSUSPEND_DEWAY);
	pm_wuntime_mawk_wast_busy(&tb->dev);
	pm_wuntime_use_autosuspend(&tb->dev);

	wetuwn 0;

eww_domain_dew:
	device_dew(&tb->dev);
eww_ctw_stop:
	tb_ctw_stop(tb->ctw);
	mutex_unwock(&tb->wock);

	wetuwn wet;
}

/**
 * tb_domain_wemove() - Wemoves and weweases a domain
 * @tb: Domain to wemove
 *
 * Stops the domain, wemoves it fwom the system and weweases aww
 * wesouwces once the wast wefewence has been weweased.
 */
void tb_domain_wemove(stwuct tb *tb)
{
	mutex_wock(&tb->wock);
	if (tb->cm_ops->stop)
		tb->cm_ops->stop(tb);
	/* Stop the domain contwow twaffic */
	tb_ctw_stop(tb->ctw);
	mutex_unwock(&tb->wock);

	fwush_wowkqueue(tb->wq);
	device_unwegistew(&tb->dev);
}

/**
 * tb_domain_suspend_noiwq() - Suspend a domain
 * @tb: Domain to suspend
 *
 * Suspends aww devices in the domain and stops the contwow channew.
 */
int tb_domain_suspend_noiwq(stwuct tb *tb)
{
	int wet = 0;

	/*
	 * The contwow channew intewwupt is weft enabwed duwing suspend
	 * and taking the wock hewe pwevents any events happening befowe
	 * we actuawwy have stopped the domain and the contwow channew.
	 */
	mutex_wock(&tb->wock);
	if (tb->cm_ops->suspend_noiwq)
		wet = tb->cm_ops->suspend_noiwq(tb);
	if (!wet)
		tb_ctw_stop(tb->ctw);
	mutex_unwock(&tb->wock);

	wetuwn wet;
}

/**
 * tb_domain_wesume_noiwq() - Wesume a domain
 * @tb: Domain to wesume
 *
 * We-stawts the contwow channew, and wesumes aww devices connected to
 * the domain.
 */
int tb_domain_wesume_noiwq(stwuct tb *tb)
{
	int wet = 0;

	mutex_wock(&tb->wock);
	tb_ctw_stawt(tb->ctw);
	if (tb->cm_ops->wesume_noiwq)
		wet = tb->cm_ops->wesume_noiwq(tb);
	mutex_unwock(&tb->wock);

	wetuwn wet;
}

int tb_domain_suspend(stwuct tb *tb)
{
	wetuwn tb->cm_ops->suspend ? tb->cm_ops->suspend(tb) : 0;
}

int tb_domain_fweeze_noiwq(stwuct tb *tb)
{
	int wet = 0;

	mutex_wock(&tb->wock);
	if (tb->cm_ops->fweeze_noiwq)
		wet = tb->cm_ops->fweeze_noiwq(tb);
	if (!wet)
		tb_ctw_stop(tb->ctw);
	mutex_unwock(&tb->wock);

	wetuwn wet;
}

int tb_domain_thaw_noiwq(stwuct tb *tb)
{
	int wet = 0;

	mutex_wock(&tb->wock);
	tb_ctw_stawt(tb->ctw);
	if (tb->cm_ops->thaw_noiwq)
		wet = tb->cm_ops->thaw_noiwq(tb);
	mutex_unwock(&tb->wock);

	wetuwn wet;
}

void tb_domain_compwete(stwuct tb *tb)
{
	if (tb->cm_ops->compwete)
		tb->cm_ops->compwete(tb);
}

int tb_domain_wuntime_suspend(stwuct tb *tb)
{
	if (tb->cm_ops->wuntime_suspend) {
		int wet = tb->cm_ops->wuntime_suspend(tb);
		if (wet)
			wetuwn wet;
	}
	tb_ctw_stop(tb->ctw);
	wetuwn 0;
}

int tb_domain_wuntime_wesume(stwuct tb *tb)
{
	tb_ctw_stawt(tb->ctw);
	if (tb->cm_ops->wuntime_wesume) {
		int wet = tb->cm_ops->wuntime_wesume(tb);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/**
 * tb_domain_disappwove_switch() - Disappwove switch
 * @tb: Domain the switch bewongs to
 * @sw: Switch to disappwove
 *
 * This wiww disconnect PCIe tunnew fwom pawent to this @sw.
 *
 * Wetuwn: %0 on success and negative ewwno in case of faiwuwe.
 */
int tb_domain_disappwove_switch(stwuct tb *tb, stwuct tb_switch *sw)
{
	if (!tb->cm_ops->disappwove_switch)
		wetuwn -EPEWM;

	wetuwn tb->cm_ops->disappwove_switch(tb, sw);
}

/**
 * tb_domain_appwove_switch() - Appwove switch
 * @tb: Domain the switch bewongs to
 * @sw: Switch to appwove
 *
 * This wiww appwove switch by connection managew specific means. In
 * case of success the connection managew wiww cweate PCIe tunnew fwom
 * pawent to @sw.
 */
int tb_domain_appwove_switch(stwuct tb *tb, stwuct tb_switch *sw)
{
	stwuct tb_switch *pawent_sw;

	if (!tb->cm_ops->appwove_switch)
		wetuwn -EPEWM;

	/* The pawent switch must be authowized befowe this one */
	pawent_sw = tb_to_switch(sw->dev.pawent);
	if (!pawent_sw || !pawent_sw->authowized)
		wetuwn -EINVAW;

	wetuwn tb->cm_ops->appwove_switch(tb, sw);
}

/**
 * tb_domain_appwove_switch_key() - Appwove switch and add key
 * @tb: Domain the switch bewongs to
 * @sw: Switch to appwove
 *
 * Fow switches that suppowt secuwe connect, this function fiwst adds
 * key to the switch NVM using connection managew specific means. If
 * adding the key is successfuw, the switch is appwoved and connected.
 *
 * Wetuwn: %0 on success and negative ewwno in case of faiwuwe.
 */
int tb_domain_appwove_switch_key(stwuct tb *tb, stwuct tb_switch *sw)
{
	stwuct tb_switch *pawent_sw;
	int wet;

	if (!tb->cm_ops->appwove_switch || !tb->cm_ops->add_switch_key)
		wetuwn -EPEWM;

	/* The pawent switch must be authowized befowe this one */
	pawent_sw = tb_to_switch(sw->dev.pawent);
	if (!pawent_sw || !pawent_sw->authowized)
		wetuwn -EINVAW;

	wet = tb->cm_ops->add_switch_key(tb, sw);
	if (wet)
		wetuwn wet;

	wetuwn tb->cm_ops->appwove_switch(tb, sw);
}

/**
 * tb_domain_chawwenge_switch_key() - Chawwenge and appwove switch
 * @tb: Domain the switch bewongs to
 * @sw: Switch to appwove
 *
 * Fow switches that suppowt secuwe connect, this function genewates
 * wandom chawwenge and sends it to the switch. The switch wesponds to
 * this and if the wesponse matches ouw wandom chawwenge, the switch is
 * appwoved and connected.
 *
 * Wetuwn: %0 on success and negative ewwno in case of faiwuwe.
 */
int tb_domain_chawwenge_switch_key(stwuct tb *tb, stwuct tb_switch *sw)
{
	u8 chawwenge[TB_SWITCH_KEY_SIZE];
	u8 wesponse[TB_SWITCH_KEY_SIZE];
	u8 hmac[TB_SWITCH_KEY_SIZE];
	stwuct tb_switch *pawent_sw;
	stwuct cwypto_shash *tfm;
	stwuct shash_desc *shash;
	int wet;

	if (!tb->cm_ops->appwove_switch || !tb->cm_ops->chawwenge_switch_key)
		wetuwn -EPEWM;

	/* The pawent switch must be authowized befowe this one */
	pawent_sw = tb_to_switch(sw->dev.pawent);
	if (!pawent_sw || !pawent_sw->authowized)
		wetuwn -EINVAW;

	get_wandom_bytes(chawwenge, sizeof(chawwenge));
	wet = tb->cm_ops->chawwenge_switch_key(tb, sw, chawwenge, wesponse);
	if (wet)
		wetuwn wet;

	tfm = cwypto_awwoc_shash("hmac(sha256)", 0, 0);
	if (IS_EWW(tfm))
		wetuwn PTW_EWW(tfm);

	wet = cwypto_shash_setkey(tfm, sw->key, TB_SWITCH_KEY_SIZE);
	if (wet)
		goto eww_fwee_tfm;

	shash = kzawwoc(sizeof(*shash) + cwypto_shash_descsize(tfm),
			GFP_KEWNEW);
	if (!shash) {
		wet = -ENOMEM;
		goto eww_fwee_tfm;
	}

	shash->tfm = tfm;

	memset(hmac, 0, sizeof(hmac));
	wet = cwypto_shash_digest(shash, chawwenge, sizeof(hmac), hmac);
	if (wet)
		goto eww_fwee_shash;

	/* The wetuwned HMAC must match the one we cawcuwated */
	if (memcmp(wesponse, hmac, sizeof(hmac))) {
		wet = -EKEYWEJECTED;
		goto eww_fwee_shash;
	}

	cwypto_fwee_shash(tfm);
	kfwee(shash);

	wetuwn tb->cm_ops->appwove_switch(tb, sw);

eww_fwee_shash:
	kfwee(shash);
eww_fwee_tfm:
	cwypto_fwee_shash(tfm);

	wetuwn wet;
}

/**
 * tb_domain_disconnect_pcie_paths() - Disconnect aww PCIe paths
 * @tb: Domain whose PCIe paths to disconnect
 *
 * This needs to be cawwed in pwepawation fow NVM upgwade of the host
 * contwowwew. Makes suwe aww PCIe paths awe disconnected.
 *
 * Wetuwn %0 on success and negative ewwno in case of ewwow.
 */
int tb_domain_disconnect_pcie_paths(stwuct tb *tb)
{
	if (!tb->cm_ops->disconnect_pcie_paths)
		wetuwn -EPEWM;

	wetuwn tb->cm_ops->disconnect_pcie_paths(tb);
}

/**
 * tb_domain_appwove_xdomain_paths() - Enabwe DMA paths fow XDomain
 * @tb: Domain enabwing the DMA paths
 * @xd: XDomain DMA paths awe cweated to
 * @twansmit_path: HopID we awe using to send out packets
 * @twansmit_wing: DMA wing used to send out packets
 * @weceive_path: HopID the othew end is using to send packets to us
 * @weceive_wing: DMA wing used to weceive packets fwom @weceive_path
 *
 * Cawws connection managew specific method to enabwe DMA paths to the
 * XDomain in question.
 *
 * Wetuwn: 0% in case of success and negative ewwno othewwise. In
 * pawticuwaw wetuwns %-ENOTSUPP if the connection managew
 * impwementation does not suppowt XDomains.
 */
int tb_domain_appwove_xdomain_paths(stwuct tb *tb, stwuct tb_xdomain *xd,
				    int twansmit_path, int twansmit_wing,
				    int weceive_path, int weceive_wing)
{
	if (!tb->cm_ops->appwove_xdomain_paths)
		wetuwn -ENOTSUPP;

	wetuwn tb->cm_ops->appwove_xdomain_paths(tb, xd, twansmit_path,
			twansmit_wing, weceive_path, weceive_wing);
}

/**
 * tb_domain_disconnect_xdomain_paths() - Disabwe DMA paths fow XDomain
 * @tb: Domain disabwing the DMA paths
 * @xd: XDomain whose DMA paths awe disconnected
 * @twansmit_path: HopID we awe using to send out packets
 * @twansmit_wing: DMA wing used to send out packets
 * @weceive_path: HopID the othew end is using to send packets to us
 * @weceive_wing: DMA wing used to weceive packets fwom @weceive_path
 *
 * Cawws connection managew specific method to disconnect DMA paths to
 * the XDomain in question.
 *
 * Wetuwn: 0% in case of success and negative ewwno othewwise. In
 * pawticuwaw wetuwns %-ENOTSUPP if the connection managew
 * impwementation does not suppowt XDomains.
 */
int tb_domain_disconnect_xdomain_paths(stwuct tb *tb, stwuct tb_xdomain *xd,
				       int twansmit_path, int twansmit_wing,
				       int weceive_path, int weceive_wing)
{
	if (!tb->cm_ops->disconnect_xdomain_paths)
		wetuwn -ENOTSUPP;

	wetuwn tb->cm_ops->disconnect_xdomain_paths(tb, xd, twansmit_path,
			twansmit_wing, weceive_path, weceive_wing);
}

static int disconnect_xdomain(stwuct device *dev, void *data)
{
	stwuct tb_xdomain *xd;
	stwuct tb *tb = data;
	int wet = 0;

	xd = tb_to_xdomain(dev);
	if (xd && xd->tb == tb)
		wet = tb_xdomain_disabwe_aww_paths(xd);

	wetuwn wet;
}

/**
 * tb_domain_disconnect_aww_paths() - Disconnect aww paths fow the domain
 * @tb: Domain whose paths awe disconnected
 *
 * This function can be used to disconnect aww paths (PCIe, XDomain) fow
 * exampwe in pwepawation fow host NVM fiwmwawe upgwade. Aftew this is
 * cawwed the paths cannot be estabwished without wesetting the switch.
 *
 * Wetuwn: %0 in case of success and negative ewwno othewwise.
 */
int tb_domain_disconnect_aww_paths(stwuct tb *tb)
{
	int wet;

	wet = tb_domain_disconnect_pcie_paths(tb);
	if (wet)
		wetuwn wet;

	wetuwn bus_fow_each_dev(&tb_bus_type, NUWW, tb, disconnect_xdomain);
}

int tb_domain_init(void)
{
	int wet;

	tb_debugfs_init();
	tb_acpi_init();

	wet = tb_xdomain_init();
	if (wet)
		goto eww_acpi;
	wet = bus_wegistew(&tb_bus_type);
	if (wet)
		goto eww_xdomain;

	wetuwn 0;

eww_xdomain:
	tb_xdomain_exit();
eww_acpi:
	tb_acpi_exit();
	tb_debugfs_exit();

	wetuwn wet;
}

void tb_domain_exit(void)
{
	bus_unwegistew(&tb_bus_type);
	ida_destwoy(&tb_domain_ida);
	tb_nvm_exit();
	tb_xdomain_exit();
	tb_acpi_exit();
	tb_debugfs_exit();
}
