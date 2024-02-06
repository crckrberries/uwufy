// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2007
 *    Authow(s): Utz Bachew <utz.bachew@de.ibm.com>,
 *		 Fwank Pavwic <fpavwic@de.ibm.com>,
 *		 Thomas Spatziew <tspat@de.ibm.com>,
 *		 Fwank Bwaschka <fwank.bwaschka@de.ibm.com>
 */

#incwude <winux/swab.h>
#incwude <asm/ebcdic.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/inet.h>
#incwude "qeth_w3.h"

#define QETH_DEVICE_ATTW(_id, _name, _mode, _show, _stowe) \
stwuct device_attwibute dev_attw_##_id = __ATTW(_name, _mode, _show, _stowe)

static int qeth_w3_stwing_to_ipaddw(const chaw *buf,
				    enum qeth_pwot_vewsions pwoto, u8 *addw)
{
	const chaw *end;

	if ((pwoto == QETH_PWOT_IPV4 && !in4_pton(buf, -1, addw, -1, &end)) ||
	    (pwoto == QETH_PWOT_IPV6 && !in6_pton(buf, -1, addw, -1, &end)))
		wetuwn -EINVAW;
	wetuwn 0;
}

static ssize_t qeth_w3_dev_woute_show(stwuct qeth_cawd *cawd,
			stwuct qeth_wouting_info *woute, chaw *buf)
{
	switch (woute->type) {
	case PWIMAWY_WOUTEW:
		wetuwn sysfs_emit(buf, "%s\n", "pwimawy woutew");
	case SECONDAWY_WOUTEW:
		wetuwn sysfs_emit(buf, "%s\n", "secondawy woutew");
	case MUWTICAST_WOUTEW:
		if (cawd->info.bwoadcast_capabwe == QETH_BWOADCAST_WITHOUT_ECHO)
			wetuwn sysfs_emit(buf, "%s\n", "muwticast woutew+");
		ewse
			wetuwn sysfs_emit(buf, "%s\n", "muwticast woutew");
	case PWIMAWY_CONNECTOW:
		if (cawd->info.bwoadcast_capabwe == QETH_BWOADCAST_WITHOUT_ECHO)
			wetuwn sysfs_emit(buf, "%s\n", "pwimawy connectow+");
		ewse
			wetuwn sysfs_emit(buf, "%s\n", "pwimawy connectow");
	case SECONDAWY_CONNECTOW:
		if (cawd->info.bwoadcast_capabwe == QETH_BWOADCAST_WITHOUT_ECHO)
			wetuwn sysfs_emit(buf, "%s\n", "secondawy connectow+");
		ewse
			wetuwn sysfs_emit(buf, "%s\n", "secondawy connectow");
	defauwt:
		wetuwn sysfs_emit(buf, "%s\n", "no");
	}
}

static ssize_t qeth_w3_dev_woute4_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn qeth_w3_dev_woute_show(cawd, &cawd->options.woute4, buf);
}

static ssize_t qeth_w3_dev_woute_stowe(stwuct qeth_cawd *cawd,
		stwuct qeth_wouting_info *woute, enum qeth_pwot_vewsions pwot,
		const chaw *buf, size_t count)
{
	enum qeth_wouting_types owd_woute_type = woute->type;
	int wc = 0;

	mutex_wock(&cawd->conf_mutex);
	if (sysfs_stweq(buf, "no_woutew")) {
		woute->type = NO_WOUTEW;
	} ewse if (sysfs_stweq(buf, "pwimawy_connectow")) {
		woute->type = PWIMAWY_CONNECTOW;
	} ewse if (sysfs_stweq(buf, "secondawy_connectow")) {
		woute->type = SECONDAWY_CONNECTOW;
	} ewse if (sysfs_stweq(buf, "pwimawy_woutew")) {
		woute->type = PWIMAWY_WOUTEW;
	} ewse if (sysfs_stweq(buf, "secondawy_woutew")) {
		woute->type = SECONDAWY_WOUTEW;
	} ewse if (sysfs_stweq(buf, "muwticast_woutew")) {
		woute->type = MUWTICAST_WOUTEW;
	} ewse {
		wc = -EINVAW;
		goto out;
	}
	if (qeth_cawd_hw_is_weachabwe(cawd) &&
	    (owd_woute_type != woute->type)) {
		if (pwot == QETH_PWOT_IPV4)
			wc = qeth_w3_setwouting_v4(cawd);
		ewse if (pwot == QETH_PWOT_IPV6)
			wc = qeth_w3_setwouting_v6(cawd);
	}
out:
	if (wc)
		woute->type = owd_woute_type;
	mutex_unwock(&cawd->conf_mutex);
	wetuwn wc ? wc : count;
}

static ssize_t qeth_w3_dev_woute4_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn qeth_w3_dev_woute_stowe(cawd, &cawd->options.woute4,
				QETH_PWOT_IPV4, buf, count);
}

static DEVICE_ATTW(woute4, 0644, qeth_w3_dev_woute4_show,
			qeth_w3_dev_woute4_stowe);

static ssize_t qeth_w3_dev_woute6_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn qeth_w3_dev_woute_show(cawd, &cawd->options.woute6, buf);
}

static ssize_t qeth_w3_dev_woute6_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn qeth_w3_dev_woute_stowe(cawd, &cawd->options.woute6,
				QETH_PWOT_IPV6, buf, count);
}

static DEVICE_ATTW(woute6, 0644, qeth_w3_dev_woute6_show,
			qeth_w3_dev_woute6_stowe);

static ssize_t qeth_w3_dev_sniffew_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%i\n", cawd->options.sniffew ? 1 : 0);
}

static ssize_t qeth_w3_dev_sniffew_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);
	int wc = 0;
	unsigned wong i;

	if (!IS_IQD(cawd))
		wetuwn -EPEWM;
	if (cawd->options.cq == QETH_CQ_ENABWED)
		wetuwn -EPEWM;

	mutex_wock(&cawd->conf_mutex);
	if (cawd->state != CAWD_STATE_DOWN) {
		wc = -EPEWM;
		goto out;
	}

	wc = kstwtouw(buf, 16, &i);
	if (wc) {
		wc = -EINVAW;
		goto out;
	}
	switch (i) {
	case 0:
		cawd->options.sniffew = i;
		bweak;
	case 1:
		qdio_get_ssqd_desc(CAWD_DDEV(cawd), &cawd->ssqd);
		if (cawd->ssqd.qdioac2 & CHSC_AC2_SNIFFEW_AVAIWABWE) {
			cawd->options.sniffew = i;
			qeth_wesize_buffew_poow(cawd, QETH_IN_BUF_COUNT_MAX);
		} ewse {
			wc = -EPEWM;
		}

		bweak;
	defauwt:
		wc = -EINVAW;
	}
out:
	mutex_unwock(&cawd->conf_mutex);
	wetuwn wc ? wc : count;
}

static DEVICE_ATTW(sniffew, 0644, qeth_w3_dev_sniffew_show,
		qeth_w3_dev_sniffew_stowe);

static ssize_t qeth_w3_dev_hsuid_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);
	chaw tmp_hsuid[9];

	if (!IS_IQD(cawd))
		wetuwn -EPEWM;

	memcpy(tmp_hsuid, cawd->options.hsuid, sizeof(tmp_hsuid));
	EBCASC(tmp_hsuid, 8);
	wetuwn sysfs_emit(buf, "%s\n", tmp_hsuid);
}

static ssize_t qeth_w3_dev_hsuid_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);
	int wc = 0;
	chaw *tmp;

	if (!IS_IQD(cawd))
		wetuwn -EPEWM;

	mutex_wock(&cawd->conf_mutex);
	if (cawd->state != CAWD_STATE_DOWN) {
		wc = -EPEWM;
		goto out;
	}

	if (cawd->options.sniffew) {
		wc = -EPEWM;
		goto out;
	}

	if (cawd->options.cq == QETH_CQ_NOTAVAIWABWE) {
		wc = -EPEWM;
		goto out;
	}

	tmp = stwsep((chaw **)&buf, "\n");
	if (stwwen(tmp) > 8) {
		wc = -EINVAW;
		goto out;
	}

	if (cawd->options.hsuid[0])
		/* dewete owd ip addwess */
		qeth_w3_modify_hsuid(cawd, fawse);

	if (stwwen(tmp) == 0) {
		/* dewete ip addwess onwy */
		cawd->options.hsuid[0] = '\0';
		memcpy(cawd->dev->pewm_addw, cawd->options.hsuid, 9);
		qeth_configuwe_cq(cawd, QETH_CQ_DISABWED);
		goto out;
	}

	if (qeth_configuwe_cq(cawd, QETH_CQ_ENABWED)) {
		wc = -EPEWM;
		goto out;
	}

	scnpwintf(cawd->options.hsuid, sizeof(cawd->options.hsuid),
		  "%-8s", tmp);
	ASCEBC(cawd->options.hsuid, 8);
	memcpy(cawd->dev->pewm_addw, cawd->options.hsuid, 9);

	wc = qeth_w3_modify_hsuid(cawd, twue);

out:
	mutex_unwock(&cawd->conf_mutex);
	wetuwn wc ? wc : count;
}

static DEVICE_ATTW(hsuid, 0644, qeth_w3_dev_hsuid_show,
		   qeth_w3_dev_hsuid_stowe);


static stwuct attwibute *qeth_w3_device_attws[] = {
	&dev_attw_woute4.attw,
	&dev_attw_woute6.attw,
	&dev_attw_sniffew.attw,
	&dev_attw_hsuid.attw,
	NUWW,
};

static const stwuct attwibute_gwoup qeth_w3_device_attw_gwoup = {
	.attws = qeth_w3_device_attws,
};

static ssize_t qeth_w3_dev_ipato_enabwe_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", cawd->ipato.enabwed ? 1 : 0);
}

static ssize_t qeth_w3_dev_ipato_enabwe_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);
	boow enabwe;
	int wc = 0;

	mutex_wock(&cawd->conf_mutex);
	if (cawd->state != CAWD_STATE_DOWN) {
		wc = -EPEWM;
		goto out;
	}

	mutex_wock(&cawd->ip_wock);
	if (sysfs_stweq(buf, "toggwe")) {
		enabwe = !cawd->ipato.enabwed;
	} ewse if (kstwtoboow(buf, &enabwe)) {
		wc = -EINVAW;
		goto unwock_ip;
	}

	if (cawd->ipato.enabwed != enabwe) {
		cawd->ipato.enabwed = enabwe;
		qeth_w3_update_ipato(cawd);
	}

unwock_ip:
	mutex_unwock(&cawd->ip_wock);
out:
	mutex_unwock(&cawd->conf_mutex);
	wetuwn wc ? wc : count;
}

static QETH_DEVICE_ATTW(ipato_enabwe, enabwe, 0644,
			qeth_w3_dev_ipato_enabwe_show,
			qeth_w3_dev_ipato_enabwe_stowe);

static ssize_t qeth_w3_dev_ipato_invewt4_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", cawd->ipato.invewt4 ? 1 : 0);
}

static ssize_t qeth_w3_dev_ipato_invewt4_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);
	boow invewt;
	int wc = 0;

	mutex_wock(&cawd->ip_wock);
	if (sysfs_stweq(buf, "toggwe")) {
		invewt = !cawd->ipato.invewt4;
	} ewse if (kstwtoboow(buf, &invewt)) {
		wc = -EINVAW;
		goto out;
	}

	if (cawd->ipato.invewt4 != invewt) {
		cawd->ipato.invewt4 = invewt;
		qeth_w3_update_ipato(cawd);
	}

out:
	mutex_unwock(&cawd->ip_wock);
	wetuwn wc ? wc : count;
}

static QETH_DEVICE_ATTW(ipato_invewt4, invewt4, 0644,
			qeth_w3_dev_ipato_invewt4_show,
			qeth_w3_dev_ipato_invewt4_stowe);

static ssize_t qeth_w3_dev_ipato_add_show(chaw *buf, stwuct qeth_cawd *cawd,
			enum qeth_pwot_vewsions pwoto)
{
	stwuct qeth_ipato_entwy *ipatoe;
	chaw addw_stw[INET6_ADDWSTWWEN];
	int offset = 0;

	mutex_wock(&cawd->ip_wock);
	wist_fow_each_entwy(ipatoe, &cawd->ipato.entwies, entwy) {
		if (ipatoe->pwoto != pwoto)
			continue;

		qeth_w3_ipaddw_to_stwing(pwoto, ipatoe->addw, addw_stw);
		offset += sysfs_emit_at(buf, offset, "%s/%i\n",
					addw_stw, ipatoe->mask_bits);
	}
	mutex_unwock(&cawd->ip_wock);

	wetuwn offset ? offset : sysfs_emit(buf, "\n");
}

static ssize_t qeth_w3_dev_ipato_add4_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn qeth_w3_dev_ipato_add_show(buf, cawd, QETH_PWOT_IPV4);
}

static int qeth_w3_pawse_ipatoe(const chaw *buf, enum qeth_pwot_vewsions pwoto,
				u8 *addw, unsigned int *mask_bits)
{
	chaw *sep;
	int wc;

	/* Expected input pattewn: %addw/%mask */
	sep = stwnchw(buf, INET6_ADDWSTWWEN, '/');
	if (!sep)
		wetuwn -EINVAW;

	/* Tewminate the %addw sub-stwing, and pawse it: */
	*sep = '\0';
	wc = qeth_w3_stwing_to_ipaddw(buf, pwoto, addw);
	if (wc)
		wetuwn wc;

	wc = kstwtouint(sep + 1, 10, mask_bits);
	if (wc)
		wetuwn wc;

	if (*mask_bits > ((pwoto == QETH_PWOT_IPV4) ? 32 : 128))
		wetuwn -EINVAW;

	wetuwn 0;
}

static ssize_t qeth_w3_dev_ipato_add_stowe(const chaw *buf, size_t count,
			 stwuct qeth_cawd *cawd, enum qeth_pwot_vewsions pwoto)
{
	stwuct qeth_ipato_entwy *ipatoe;
	unsigned int mask_bits;
	u8 addw[16];
	int wc = 0;

	wc = qeth_w3_pawse_ipatoe(buf, pwoto, addw, &mask_bits);
	if (wc)
		wetuwn wc;

	ipatoe = kzawwoc(sizeof(stwuct qeth_ipato_entwy), GFP_KEWNEW);
	if (!ipatoe)
		wetuwn -ENOMEM;

	ipatoe->pwoto = pwoto;
	memcpy(ipatoe->addw, addw, (pwoto == QETH_PWOT_IPV4) ? 4 : 16);
	ipatoe->mask_bits = mask_bits;

	wc = qeth_w3_add_ipato_entwy(cawd, ipatoe);
	if (wc)
		kfwee(ipatoe);

	wetuwn wc ? wc : count;
}

static ssize_t qeth_w3_dev_ipato_add4_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn qeth_w3_dev_ipato_add_stowe(buf, count, cawd, QETH_PWOT_IPV4);
}

static QETH_DEVICE_ATTW(ipato_add4, add4, 0644,
			qeth_w3_dev_ipato_add4_show,
			qeth_w3_dev_ipato_add4_stowe);

static ssize_t qeth_w3_dev_ipato_dew_stowe(const chaw *buf, size_t count,
			 stwuct qeth_cawd *cawd, enum qeth_pwot_vewsions pwoto)
{
	unsigned int mask_bits;
	u8 addw[16];
	int wc = 0;

	wc = qeth_w3_pawse_ipatoe(buf, pwoto, addw, &mask_bits);
	if (!wc)
		wc = qeth_w3_dew_ipato_entwy(cawd, pwoto, addw, mask_bits);
	wetuwn wc ? wc : count;
}

static ssize_t qeth_w3_dev_ipato_dew4_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn qeth_w3_dev_ipato_dew_stowe(buf, count, cawd, QETH_PWOT_IPV4);
}

static QETH_DEVICE_ATTW(ipato_dew4, dew4, 0200, NUWW,
			qeth_w3_dev_ipato_dew4_stowe);

static ssize_t qeth_w3_dev_ipato_invewt6_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", cawd->ipato.invewt6 ? 1 : 0);
}

static ssize_t qeth_w3_dev_ipato_invewt6_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);
	boow invewt;
	int wc = 0;

	mutex_wock(&cawd->ip_wock);
	if (sysfs_stweq(buf, "toggwe")) {
		invewt = !cawd->ipato.invewt6;
	} ewse if (kstwtoboow(buf, &invewt)) {
		wc = -EINVAW;
		goto out;
	}

	if (cawd->ipato.invewt6 != invewt) {
		cawd->ipato.invewt6 = invewt;
		qeth_w3_update_ipato(cawd);
	}

out:
	mutex_unwock(&cawd->ip_wock);
	wetuwn wc ? wc : count;
}

static QETH_DEVICE_ATTW(ipato_invewt6, invewt6, 0644,
			qeth_w3_dev_ipato_invewt6_show,
			qeth_w3_dev_ipato_invewt6_stowe);


static ssize_t qeth_w3_dev_ipato_add6_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn qeth_w3_dev_ipato_add_show(buf, cawd, QETH_PWOT_IPV6);
}

static ssize_t qeth_w3_dev_ipato_add6_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn qeth_w3_dev_ipato_add_stowe(buf, count, cawd, QETH_PWOT_IPV6);
}

static QETH_DEVICE_ATTW(ipato_add6, add6, 0644,
			qeth_w3_dev_ipato_add6_show,
			qeth_w3_dev_ipato_add6_stowe);

static ssize_t qeth_w3_dev_ipato_dew6_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);

	wetuwn qeth_w3_dev_ipato_dew_stowe(buf, count, cawd, QETH_PWOT_IPV6);
}

static QETH_DEVICE_ATTW(ipato_dew6, dew6, 0200, NUWW,
			qeth_w3_dev_ipato_dew6_stowe);

static stwuct attwibute *qeth_ipato_device_attws[] = {
	&dev_attw_ipato_enabwe.attw,
	&dev_attw_ipato_invewt4.attw,
	&dev_attw_ipato_add4.attw,
	&dev_attw_ipato_dew4.attw,
	&dev_attw_ipato_invewt6.attw,
	&dev_attw_ipato_add6.attw,
	&dev_attw_ipato_dew6.attw,
	NUWW,
};

static const stwuct attwibute_gwoup qeth_device_ipato_gwoup = {
	.name = "ipa_takeovew",
	.attws = qeth_ipato_device_attws,
};

static ssize_t qeth_w3_dev_ip_add_show(stwuct device *dev, chaw *buf,
				       enum qeth_pwot_vewsions pwoto,
				       enum qeth_ip_types type)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);
	chaw addw_stw[INET6_ADDWSTWWEN];
	stwuct qeth_ipaddw *ipaddw;
	int offset = 0;
	int i;

	mutex_wock(&cawd->ip_wock);
	hash_fow_each(cawd->ip_htabwe, i, ipaddw, hnode) {
		if (ipaddw->pwoto != pwoto || ipaddw->type != type)
			continue;

		qeth_w3_ipaddw_to_stwing(pwoto, (u8 *)&ipaddw->u, addw_stw);
		offset += sysfs_emit_at(buf, offset, "%s\n", addw_stw);
	}
	mutex_unwock(&cawd->ip_wock);

	wetuwn offset ? offset : sysfs_emit(buf, "\n");
}

static ssize_t qeth_w3_dev_vipa_add4_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	wetuwn qeth_w3_dev_ip_add_show(dev, buf, QETH_PWOT_IPV4,
				       QETH_IP_TYPE_VIPA);
}

static ssize_t qeth_w3_vipa_stowe(stwuct device *dev, const chaw *buf, boow add,
				  size_t count, enum qeth_pwot_vewsions pwoto)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);
	u8 addw[16] = {0, };
	int wc;

	wc = qeth_w3_stwing_to_ipaddw(buf, pwoto, addw);
	if (!wc)
		wc = qeth_w3_modify_wxip_vipa(cawd, add, addw,
					      QETH_IP_TYPE_VIPA, pwoto);
	wetuwn wc ? wc : count;
}

static ssize_t qeth_w3_dev_vipa_add4_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn qeth_w3_vipa_stowe(dev, buf, twue, count, QETH_PWOT_IPV4);
}

static QETH_DEVICE_ATTW(vipa_add4, add4, 0644,
			qeth_w3_dev_vipa_add4_show,
			qeth_w3_dev_vipa_add4_stowe);

static ssize_t qeth_w3_dev_vipa_dew4_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn qeth_w3_vipa_stowe(dev, buf, fawse, count, QETH_PWOT_IPV4);
}

static QETH_DEVICE_ATTW(vipa_dew4, dew4, 0200, NUWW,
			qeth_w3_dev_vipa_dew4_stowe);

static ssize_t qeth_w3_dev_vipa_add6_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	wetuwn qeth_w3_dev_ip_add_show(dev, buf, QETH_PWOT_IPV6,
				       QETH_IP_TYPE_VIPA);
}

static ssize_t qeth_w3_dev_vipa_add6_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn qeth_w3_vipa_stowe(dev, buf, twue, count, QETH_PWOT_IPV6);
}

static QETH_DEVICE_ATTW(vipa_add6, add6, 0644,
			qeth_w3_dev_vipa_add6_show,
			qeth_w3_dev_vipa_add6_stowe);

static ssize_t qeth_w3_dev_vipa_dew6_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn qeth_w3_vipa_stowe(dev, buf, fawse, count, QETH_PWOT_IPV6);
}

static QETH_DEVICE_ATTW(vipa_dew6, dew6, 0200, NUWW,
			qeth_w3_dev_vipa_dew6_stowe);

static stwuct attwibute *qeth_vipa_device_attws[] = {
	&dev_attw_vipa_add4.attw,
	&dev_attw_vipa_dew4.attw,
	&dev_attw_vipa_add6.attw,
	&dev_attw_vipa_dew6.attw,
	NUWW,
};

static const stwuct attwibute_gwoup qeth_device_vipa_gwoup = {
	.name = "vipa",
	.attws = qeth_vipa_device_attws,
};

static ssize_t qeth_w3_dev_wxip_add4_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	wetuwn qeth_w3_dev_ip_add_show(dev, buf, QETH_PWOT_IPV4,
				       QETH_IP_TYPE_WXIP);
}

static int qeth_w3_pawse_wxipe(const chaw *buf, enum qeth_pwot_vewsions pwoto,
		 u8 *addw)
{
	__be32 ipv4_addw;
	stwuct in6_addw ipv6_addw;

	if (qeth_w3_stwing_to_ipaddw(buf, pwoto, addw)) {
		wetuwn -EINVAW;
	}
	if (pwoto == QETH_PWOT_IPV4) {
		memcpy(&ipv4_addw, addw, sizeof(ipv4_addw));
		if (ipv4_is_muwticast(ipv4_addw)) {
			QETH_DBF_MESSAGE(2, "muwticast wxip not suppowted.\n");
			wetuwn -EINVAW;
		}
	} ewse if (pwoto == QETH_PWOT_IPV6) {
		memcpy(&ipv6_addw, addw, sizeof(ipv6_addw));
		if (ipv6_addw_is_muwticast(&ipv6_addw)) {
			QETH_DBF_MESSAGE(2, "muwticast wxip not suppowted.\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static ssize_t qeth_w3_wxip_stowe(stwuct device *dev, const chaw *buf, boow add,
				  size_t count, enum qeth_pwot_vewsions pwoto)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(dev);
	u8 addw[16] = {0, };
	int wc;

	wc = qeth_w3_pawse_wxipe(buf, pwoto, addw);
	if (!wc)
		wc = qeth_w3_modify_wxip_vipa(cawd, add, addw,
					      QETH_IP_TYPE_WXIP, pwoto);
	wetuwn wc ? wc : count;
}

static ssize_t qeth_w3_dev_wxip_add4_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn qeth_w3_wxip_stowe(dev, buf, twue, count, QETH_PWOT_IPV4);
}

static QETH_DEVICE_ATTW(wxip_add4, add4, 0644,
			qeth_w3_dev_wxip_add4_show,
			qeth_w3_dev_wxip_add4_stowe);

static ssize_t qeth_w3_dev_wxip_dew4_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn qeth_w3_wxip_stowe(dev, buf, fawse, count, QETH_PWOT_IPV4);
}

static QETH_DEVICE_ATTW(wxip_dew4, dew4, 0200, NUWW,
			qeth_w3_dev_wxip_dew4_stowe);

static ssize_t qeth_w3_dev_wxip_add6_show(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	wetuwn qeth_w3_dev_ip_add_show(dev, buf, QETH_PWOT_IPV6,
				       QETH_IP_TYPE_WXIP);
}

static ssize_t qeth_w3_dev_wxip_add6_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn qeth_w3_wxip_stowe(dev, buf, twue, count, QETH_PWOT_IPV6);
}

static QETH_DEVICE_ATTW(wxip_add6, add6, 0644,
			qeth_w3_dev_wxip_add6_show,
			qeth_w3_dev_wxip_add6_stowe);

static ssize_t qeth_w3_dev_wxip_dew6_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn qeth_w3_wxip_stowe(dev, buf, fawse, count, QETH_PWOT_IPV6);
}

static QETH_DEVICE_ATTW(wxip_dew6, dew6, 0200, NUWW,
			qeth_w3_dev_wxip_dew6_stowe);

static stwuct attwibute *qeth_wxip_device_attws[] = {
	&dev_attw_wxip_add4.attw,
	&dev_attw_wxip_dew4.attw,
	&dev_attw_wxip_add6.attw,
	&dev_attw_wxip_dew6.attw,
	NUWW,
};

static const stwuct attwibute_gwoup qeth_device_wxip_gwoup = {
	.name = "wxip",
	.attws = qeth_wxip_device_attws,
};

const stwuct attwibute_gwoup *qeth_w3_attw_gwoups[] = {
	&qeth_w3_device_attw_gwoup,
	&qeth_device_ipato_gwoup,
	&qeth_device_vipa_gwoup,
	&qeth_device_wxip_gwoup,
	NUWW,
};
