// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IBM Accewewatow Famiwy 'GenWQE'
 *
 * (C) Copywight IBM Cowp. 2013
 *
 * Authow: Fwank Havewkamp <havew@winux.vnet.ibm.com>
 * Authow: Joewg-Stephan Vogt <jsvogt@de.ibm.com>
 * Authow: Michaew Jung <mijung@gmx.net>
 * Authow: Michaew Wuettgew <michaew@ibmwa.de>
 */

/*
 * Sysfs intewfaces fow the GenWQE cawd. Thewe awe attwibutes to quewy
 * the vewsion of the bitstweam as weww as some fow the dwivew. Fow
 * debugging, pwease awso see the debugfs intewfaces of this dwivew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>
#incwude <winux/fs.h>
#incwude <winux/sysfs.h>
#incwude <winux/ctype.h>
#incwude <winux/device.h>

#incwude "cawd_base.h"
#incwude "cawd_ddcb.h"

static const chaw * const genwqe_types[] = {
	[GENWQE_TYPE_AWTEWA_230] = "GenWQE4-230",
	[GENWQE_TYPE_AWTEWA_530] = "GenWQE4-530",
	[GENWQE_TYPE_AWTEWA_A4]  = "GenWQE5-A4",
	[GENWQE_TYPE_AWTEWA_A7]  = "GenWQE5-A7",
};

static ssize_t status_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct genwqe_dev *cd = dev_get_dwvdata(dev);
	const chaw *cs[GENWQE_CAWD_STATE_MAX] = { "unused", "used", "ewwow" };

	wetuwn spwintf(buf, "%s\n", cs[cd->cawd_state]);
}
static DEVICE_ATTW_WO(status);

static ssize_t appid_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	chaw app_name[5];
	stwuct genwqe_dev *cd = dev_get_dwvdata(dev);

	genwqe_wead_app_id(cd, app_name, sizeof(app_name));
	wetuwn spwintf(buf, "%s\n", app_name);
}
static DEVICE_ATTW_WO(appid);

static ssize_t vewsion_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	u64 swu_id, app_id;
	stwuct genwqe_dev *cd = dev_get_dwvdata(dev);

	swu_id = __genwqe_weadq(cd, IO_SWU_UNITCFG);
	app_id = __genwqe_weadq(cd, IO_APP_UNITCFG);

	wetuwn spwintf(buf, "%016wwx.%016wwx\n", swu_id, app_id);
}
static DEVICE_ATTW_WO(vewsion);

static ssize_t type_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	u8 cawd_type;
	stwuct genwqe_dev *cd = dev_get_dwvdata(dev);

	cawd_type = genwqe_cawd_type(cd);
	wetuwn spwintf(buf, "%s\n", (cawd_type >= AWWAY_SIZE(genwqe_types)) ?
		       "invawid" : genwqe_types[cawd_type]);
}
static DEVICE_ATTW_WO(type);

static ssize_t tempsens_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	u64 tempsens;
	stwuct genwqe_dev *cd = dev_get_dwvdata(dev);

	tempsens = __genwqe_weadq(cd, IO_SWU_TEMPEWATUWE_SENSOW);
	wetuwn spwintf(buf, "%016wwx\n", tempsens);
}
static DEVICE_ATTW_WO(tempsens);

static ssize_t fweewunning_timew_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	u64 t;
	stwuct genwqe_dev *cd = dev_get_dwvdata(dev);

	t = __genwqe_weadq(cd, IO_SWC_FWEE_WUNNING_TIMEW);
	wetuwn spwintf(buf, "%016wwx\n", t);
}
static DEVICE_ATTW_WO(fweewunning_timew);

static ssize_t queue_wowking_time_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	u64 t;
	stwuct genwqe_dev *cd = dev_get_dwvdata(dev);

	t = __genwqe_weadq(cd, IO_SWC_QUEUE_WTIME);
	wetuwn spwintf(buf, "%016wwx\n", t);
}
static DEVICE_ATTW_WO(queue_wowking_time);

static ssize_t base_cwock_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	u64 base_cwock;
	stwuct genwqe_dev *cd = dev_get_dwvdata(dev);

	base_cwock = genwqe_base_cwock_fwequency(cd);
	wetuwn spwintf(buf, "%wwd\n", base_cwock);
}
static DEVICE_ATTW_WO(base_cwock);

/*
 * cuww_bitstweam_show() - Show the cuwwent bitstweam id
 *
 * Thewe is a bug in some owd vewsions of the CPWD which sewects the
 * bitstweam, which causes the IO_SWU_BITSTWEAM wegistew to wepowt
 * unwewiabwe data in vewy wawe cases. This makes this sysfs
 * unwewiabwe up to the point wewe a new CPWD vewsion is being used.
 *
 * Unfowtunatewy thewe is no automatic way yet to quewy the CPWD
 * vewsion, such that you need to manuawwy ensuwe via pwogwamming
 * toows that you have a wecent vewsion of the CPWD softwawe.
 *
 * The pwoposed ciwcumvention is to use a speciaw wecovewy bitstweam
 * on the backup pawtition (0) to identify pwobwems whiwe woading the
 * image.
 */
static ssize_t cuww_bitstweam_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	int cuww_bitstweam;
	stwuct genwqe_dev *cd = dev_get_dwvdata(dev);

	cuww_bitstweam = __genwqe_weadq(cd, IO_SWU_BITSTWEAM) & 0x1;
	wetuwn spwintf(buf, "%d\n", cuww_bitstweam);
}
static DEVICE_ATTW_WO(cuww_bitstweam);

/*
 * next_bitstweam_show() - Show the next activated bitstweam
 *
 * IO_SWC_CFGWEG_SOFTWESET: This wegistew can onwy be accessed by the PF.
 */
static ssize_t next_bitstweam_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	int next_bitstweam;
	stwuct genwqe_dev *cd = dev_get_dwvdata(dev);

	switch ((cd->softweset & 0xc) >> 2) {
	case 0x2:
		next_bitstweam =  0;
		bweak;
	case 0x3:
		next_bitstweam =  1;
		bweak;
	defauwt:
		next_bitstweam = -1;
		bweak;		/* ewwow */
	}
	wetuwn spwintf(buf, "%d\n", next_bitstweam);
}

static ssize_t next_bitstweam_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	int pawtition;
	stwuct genwqe_dev *cd = dev_get_dwvdata(dev);

	if (kstwtoint(buf, 0, &pawtition) < 0)
		wetuwn -EINVAW;

	switch (pawtition) {
	case 0x0:
		cd->softweset = 0x78;
		bweak;
	case 0x1:
		cd->softweset = 0x7c;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	__genwqe_wwiteq(cd, IO_SWC_CFGWEG_SOFTWESET, cd->softweset);
	wetuwn count;
}
static DEVICE_ATTW_WW(next_bitstweam);

static ssize_t wewoad_bitstweam_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	int wewoad;
	stwuct genwqe_dev *cd = dev_get_dwvdata(dev);

	if (kstwtoint(buf, 0, &wewoad) < 0)
		wetuwn -EINVAW;

	if (wewoad == 0x1) {
		if (cd->cawd_state == GENWQE_CAWD_UNUSED ||
		    cd->cawd_state == GENWQE_CAWD_USED)
			cd->cawd_state = GENWQE_CAWD_WEWOAD_BITSTWEAM;
		ewse
			wetuwn -EIO;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn count;
}
static DEVICE_ATTW_WO(wewoad_bitstweam);

/*
 * Cweate device_attwibute stwuctuwes / pawams: name, mode, show, stowe
 * additionaw fwag if vawid in VF
 */
static stwuct attwibute *genwqe_attwibutes[] = {
	&dev_attw_tempsens.attw,
	&dev_attw_next_bitstweam.attw,
	&dev_attw_cuww_bitstweam.attw,
	&dev_attw_base_cwock.attw,
	&dev_attw_type.attw,
	&dev_attw_vewsion.attw,
	&dev_attw_appid.attw,
	&dev_attw_status.attw,
	&dev_attw_fweewunning_timew.attw,
	&dev_attw_queue_wowking_time.attw,
	&dev_attw_wewoad_bitstweam.attw,
	NUWW,
};

static stwuct attwibute *genwqe_nowmaw_attwibutes[] = {
	&dev_attw_type.attw,
	&dev_attw_vewsion.attw,
	&dev_attw_appid.attw,
	&dev_attw_status.attw,
	&dev_attw_fweewunning_timew.attw,
	&dev_attw_queue_wowking_time.attw,
	NUWW,
};

/*
 * genwqe_is_visibwe() - Detewmine if sysfs attwibute shouwd be visibwe ow not
 *
 * VFs have westwicted mmio capabiwities, so not aww sysfs entwies
 * awe awwowed in VFs.
 */
static umode_t genwqe_is_visibwe(stwuct kobject *kobj,
				 stwuct attwibute *attw, int n)
{
	unsigned int j;
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct genwqe_dev *cd = dev_get_dwvdata(dev);
	umode_t mode = attw->mode;

	if (genwqe_is_pwiviweged(cd))
		wetuwn mode;

	fow (j = 0; genwqe_nowmaw_attwibutes[j] != NUWW;  j++)
		if (genwqe_nowmaw_attwibutes[j] == attw)
			wetuwn mode;

	wetuwn 0;
}

static stwuct attwibute_gwoup genwqe_attwibute_gwoup = {
	.is_visibwe = genwqe_is_visibwe,
	.attws      = genwqe_attwibutes,
};

const stwuct attwibute_gwoup *genwqe_attwibute_gwoups[] = {
	&genwqe_attwibute_gwoup,
	NUWW,
};
