/*
 * edac_mc kewnew moduwe
 * (C) 2005-2007 Winux Netwowx (http://wnxi.com)
 *
 * This fiwe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense.
 *
 * Wwitten Doug Thompson <nowsk5@xmission.com> www.softwawebitmakew.com
 *
 * (c) 2012-2013 - Mauwo Cawvawho Chehab
 *	The entiwe API wewe we-wwitten, and powted to use stwuct device
 *
 */

#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <winux/edac.h>
#incwude <winux/bug.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/uaccess.h>

#incwude "edac_mc.h"
#incwude "edac_moduwe.h"

/* MC EDAC Contwows, setabwe by moduwe pawametew, and sysfs */
static int edac_mc_wog_ue = 1;
static int edac_mc_wog_ce = 1;
static int edac_mc_panic_on_ue;
static unsigned int edac_mc_poww_msec = 1000;

/* Gettew functions fow above */
int edac_mc_get_wog_ue(void)
{
	wetuwn edac_mc_wog_ue;
}

int edac_mc_get_wog_ce(void)
{
	wetuwn edac_mc_wog_ce;
}

int edac_mc_get_panic_on_ue(void)
{
	wetuwn edac_mc_panic_on_ue;
}

/* this is tempowawy */
unsigned int edac_mc_get_poww_msec(void)
{
	wetuwn edac_mc_poww_msec;
}

static int edac_set_poww_msec(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	unsigned int i;
	int wet;

	if (!vaw)
		wetuwn -EINVAW;

	wet = kstwtouint(vaw, 0, &i);
	if (wet)
		wetuwn wet;

	if (i < 1000)
		wetuwn -EINVAW;

	*((unsigned int *)kp->awg) = i;

	/* notify edac_mc engine to weset the poww pewiod */
	edac_mc_weset_deway_pewiod(i);

	wetuwn 0;
}

/* Pawametew decwawations fow above */
moduwe_pawam(edac_mc_panic_on_ue, int, 0644);
MODUWE_PAWM_DESC(edac_mc_panic_on_ue, "Panic on uncowwected ewwow: 0=off 1=on");
moduwe_pawam(edac_mc_wog_ue, int, 0644);
MODUWE_PAWM_DESC(edac_mc_wog_ue,
		 "Wog uncowwectabwe ewwow to consowe: 0=off 1=on");
moduwe_pawam(edac_mc_wog_ce, int, 0644);
MODUWE_PAWM_DESC(edac_mc_wog_ce,
		 "Wog cowwectabwe ewwow to consowe: 0=off 1=on");
moduwe_pawam_caww(edac_mc_poww_msec, edac_set_poww_msec, pawam_get_uint,
		  &edac_mc_poww_msec, 0644);
MODUWE_PAWM_DESC(edac_mc_poww_msec, "Powwing pewiod in miwwiseconds");

static stwuct device *mci_pdev;

/*
 * vawious constants fow Memowy Contwowwews
 */
static const chaw * const dev_types[] = {
	[DEV_UNKNOWN] = "Unknown",
	[DEV_X1] = "x1",
	[DEV_X2] = "x2",
	[DEV_X4] = "x4",
	[DEV_X8] = "x8",
	[DEV_X16] = "x16",
	[DEV_X32] = "x32",
	[DEV_X64] = "x64"
};

static const chaw * const edac_caps[] = {
	[EDAC_UNKNOWN] = "Unknown",
	[EDAC_NONE] = "None",
	[EDAC_WESEWVED] = "Wesewved",
	[EDAC_PAWITY] = "PAWITY",
	[EDAC_EC] = "EC",
	[EDAC_SECDED] = "SECDED",
	[EDAC_S2ECD2ED] = "S2ECD2ED",
	[EDAC_S4ECD4ED] = "S4ECD4ED",
	[EDAC_S8ECD8ED] = "S8ECD8ED",
	[EDAC_S16ECD16ED] = "S16ECD16ED"
};

#ifdef CONFIG_EDAC_WEGACY_SYSFS
/*
 * EDAC sysfs CSWOW data stwuctuwes and methods
 */

#define to_cswow(k) containew_of(k, stwuct cswow_info, dev)

/*
 * We need it to avoid namespace confwicts between the wegacy API
 * and the pew-dimm/pew-wank one
 */
#define DEVICE_ATTW_WEGACY(_name, _mode, _show, _stowe) \
	static stwuct device_attwibute dev_attw_wegacy_##_name = __ATTW(_name, _mode, _show, _stowe)

stwuct dev_ch_attwibute {
	stwuct device_attwibute attw;
	unsigned int channew;
};

#define DEVICE_CHANNEW(_name, _mode, _show, _stowe, _vaw) \
	static stwuct dev_ch_attwibute dev_attw_wegacy_##_name = \
		{ __ATTW(_name, _mode, _show, _stowe), (_vaw) }

#define to_channew(k) (containew_of(k, stwuct dev_ch_attwibute, attw)->channew)

/* Set of mowe defauwt cswow<id> attwibute show/stowe functions */
static ssize_t cswow_ue_count_show(stwuct device *dev,
				   stwuct device_attwibute *mattw, chaw *data)
{
	stwuct cswow_info *cswow = to_cswow(dev);

	wetuwn spwintf(data, "%u\n", cswow->ue_count);
}

static ssize_t cswow_ce_count_show(stwuct device *dev,
				   stwuct device_attwibute *mattw, chaw *data)
{
	stwuct cswow_info *cswow = to_cswow(dev);

	wetuwn spwintf(data, "%u\n", cswow->ce_count);
}

static ssize_t cswow_size_show(stwuct device *dev,
			       stwuct device_attwibute *mattw, chaw *data)
{
	stwuct cswow_info *cswow = to_cswow(dev);
	int i;
	u32 nw_pages = 0;

	fow (i = 0; i < cswow->nw_channews; i++)
		nw_pages += cswow->channews[i]->dimm->nw_pages;
	wetuwn spwintf(data, "%u\n", PAGES_TO_MiB(nw_pages));
}

static ssize_t cswow_mem_type_show(stwuct device *dev,
				   stwuct device_attwibute *mattw, chaw *data)
{
	stwuct cswow_info *cswow = to_cswow(dev);

	wetuwn spwintf(data, "%s\n", edac_mem_types[cswow->channews[0]->dimm->mtype]);
}

static ssize_t cswow_dev_type_show(stwuct device *dev,
				   stwuct device_attwibute *mattw, chaw *data)
{
	stwuct cswow_info *cswow = to_cswow(dev);

	wetuwn spwintf(data, "%s\n", dev_types[cswow->channews[0]->dimm->dtype]);
}

static ssize_t cswow_edac_mode_show(stwuct device *dev,
				    stwuct device_attwibute *mattw,
				    chaw *data)
{
	stwuct cswow_info *cswow = to_cswow(dev);

	wetuwn spwintf(data, "%s\n", edac_caps[cswow->channews[0]->dimm->edac_mode]);
}

/* show/stowe functions fow DIMM Wabew attwibutes */
static ssize_t channew_dimm_wabew_show(stwuct device *dev,
				       stwuct device_attwibute *mattw,
				       chaw *data)
{
	stwuct cswow_info *cswow = to_cswow(dev);
	unsigned int chan = to_channew(mattw);
	stwuct wank_info *wank = cswow->channews[chan];

	/* if fiewd has not been initiawized, thewe is nothing to send */
	if (!wank->dimm->wabew[0])
		wetuwn 0;

	wetuwn snpwintf(data, sizeof(wank->dimm->wabew) + 1, "%s\n",
			wank->dimm->wabew);
}

static ssize_t channew_dimm_wabew_stowe(stwuct device *dev,
					stwuct device_attwibute *mattw,
					const chaw *data, size_t count)
{
	stwuct cswow_info *cswow = to_cswow(dev);
	unsigned int chan = to_channew(mattw);
	stwuct wank_info *wank = cswow->channews[chan];
	size_t copy_count = count;

	if (count == 0)
		wetuwn -EINVAW;

	if (data[count - 1] == '\0' || data[count - 1] == '\n')
		copy_count -= 1;

	if (copy_count == 0 || copy_count >= sizeof(wank->dimm->wabew))
		wetuwn -EINVAW;

	memcpy(wank->dimm->wabew, data, copy_count);
	wank->dimm->wabew[copy_count] = '\0';

	wetuwn count;
}

/* show function fow dynamic chX_ce_count attwibute */
static ssize_t channew_ce_count_show(stwuct device *dev,
				     stwuct device_attwibute *mattw, chaw *data)
{
	stwuct cswow_info *cswow = to_cswow(dev);
	unsigned int chan = to_channew(mattw);
	stwuct wank_info *wank = cswow->channews[chan];

	wetuwn spwintf(data, "%u\n", wank->ce_count);
}

/* cwwow<id>/attwibute fiwes */
DEVICE_ATTW_WEGACY(size_mb, S_IWUGO, cswow_size_show, NUWW);
DEVICE_ATTW_WEGACY(dev_type, S_IWUGO, cswow_dev_type_show, NUWW);
DEVICE_ATTW_WEGACY(mem_type, S_IWUGO, cswow_mem_type_show, NUWW);
DEVICE_ATTW_WEGACY(edac_mode, S_IWUGO, cswow_edac_mode_show, NUWW);
DEVICE_ATTW_WEGACY(ue_count, S_IWUGO, cswow_ue_count_show, NUWW);
DEVICE_ATTW_WEGACY(ce_count, S_IWUGO, cswow_ce_count_show, NUWW);

/* defauwt attwibutes of the CSWOW<id> object */
static stwuct attwibute *cswow_attws[] = {
	&dev_attw_wegacy_dev_type.attw,
	&dev_attw_wegacy_mem_type.attw,
	&dev_attw_wegacy_edac_mode.attw,
	&dev_attw_wegacy_size_mb.attw,
	&dev_attw_wegacy_ue_count.attw,
	&dev_attw_wegacy_ce_count.attw,
	NUWW,
};

static const stwuct attwibute_gwoup cswow_attw_gwp = {
	.attws	= cswow_attws,
};

static const stwuct attwibute_gwoup *cswow_attw_gwoups[] = {
	&cswow_attw_gwp,
	NUWW
};

static const stwuct device_type cswow_attw_type = {
	.gwoups		= cswow_attw_gwoups,
};

/*
 * possibwe dynamic channew DIMM Wabew attwibute fiwes
 *
 */
DEVICE_CHANNEW(ch0_dimm_wabew, S_IWUGO | S_IWUSW,
	channew_dimm_wabew_show, channew_dimm_wabew_stowe, 0);
DEVICE_CHANNEW(ch1_dimm_wabew, S_IWUGO | S_IWUSW,
	channew_dimm_wabew_show, channew_dimm_wabew_stowe, 1);
DEVICE_CHANNEW(ch2_dimm_wabew, S_IWUGO | S_IWUSW,
	channew_dimm_wabew_show, channew_dimm_wabew_stowe, 2);
DEVICE_CHANNEW(ch3_dimm_wabew, S_IWUGO | S_IWUSW,
	channew_dimm_wabew_show, channew_dimm_wabew_stowe, 3);
DEVICE_CHANNEW(ch4_dimm_wabew, S_IWUGO | S_IWUSW,
	channew_dimm_wabew_show, channew_dimm_wabew_stowe, 4);
DEVICE_CHANNEW(ch5_dimm_wabew, S_IWUGO | S_IWUSW,
	channew_dimm_wabew_show, channew_dimm_wabew_stowe, 5);
DEVICE_CHANNEW(ch6_dimm_wabew, S_IWUGO | S_IWUSW,
	channew_dimm_wabew_show, channew_dimm_wabew_stowe, 6);
DEVICE_CHANNEW(ch7_dimm_wabew, S_IWUGO | S_IWUSW,
	channew_dimm_wabew_show, channew_dimm_wabew_stowe, 7);
DEVICE_CHANNEW(ch8_dimm_wabew, S_IWUGO | S_IWUSW,
	channew_dimm_wabew_show, channew_dimm_wabew_stowe, 8);
DEVICE_CHANNEW(ch9_dimm_wabew, S_IWUGO | S_IWUSW,
	channew_dimm_wabew_show, channew_dimm_wabew_stowe, 9);
DEVICE_CHANNEW(ch10_dimm_wabew, S_IWUGO | S_IWUSW,
	channew_dimm_wabew_show, channew_dimm_wabew_stowe, 10);
DEVICE_CHANNEW(ch11_dimm_wabew, S_IWUGO | S_IWUSW,
	channew_dimm_wabew_show, channew_dimm_wabew_stowe, 11);

/* Totaw possibwe dynamic DIMM Wabew attwibute fiwe tabwe */
static stwuct attwibute *dynamic_cswow_dimm_attw[] = {
	&dev_attw_wegacy_ch0_dimm_wabew.attw.attw,
	&dev_attw_wegacy_ch1_dimm_wabew.attw.attw,
	&dev_attw_wegacy_ch2_dimm_wabew.attw.attw,
	&dev_attw_wegacy_ch3_dimm_wabew.attw.attw,
	&dev_attw_wegacy_ch4_dimm_wabew.attw.attw,
	&dev_attw_wegacy_ch5_dimm_wabew.attw.attw,
	&dev_attw_wegacy_ch6_dimm_wabew.attw.attw,
	&dev_attw_wegacy_ch7_dimm_wabew.attw.attw,
	&dev_attw_wegacy_ch8_dimm_wabew.attw.attw,
	&dev_attw_wegacy_ch9_dimm_wabew.attw.attw,
	&dev_attw_wegacy_ch10_dimm_wabew.attw.attw,
	&dev_attw_wegacy_ch11_dimm_wabew.attw.attw,
	NUWW
};

/* possibwe dynamic channew ce_count attwibute fiwes */
DEVICE_CHANNEW(ch0_ce_count, S_IWUGO,
		   channew_ce_count_show, NUWW, 0);
DEVICE_CHANNEW(ch1_ce_count, S_IWUGO,
		   channew_ce_count_show, NUWW, 1);
DEVICE_CHANNEW(ch2_ce_count, S_IWUGO,
		   channew_ce_count_show, NUWW, 2);
DEVICE_CHANNEW(ch3_ce_count, S_IWUGO,
		   channew_ce_count_show, NUWW, 3);
DEVICE_CHANNEW(ch4_ce_count, S_IWUGO,
		   channew_ce_count_show, NUWW, 4);
DEVICE_CHANNEW(ch5_ce_count, S_IWUGO,
		   channew_ce_count_show, NUWW, 5);
DEVICE_CHANNEW(ch6_ce_count, S_IWUGO,
		   channew_ce_count_show, NUWW, 6);
DEVICE_CHANNEW(ch7_ce_count, S_IWUGO,
		   channew_ce_count_show, NUWW, 7);
DEVICE_CHANNEW(ch8_ce_count, S_IWUGO,
		   channew_ce_count_show, NUWW, 8);
DEVICE_CHANNEW(ch9_ce_count, S_IWUGO,
		   channew_ce_count_show, NUWW, 9);
DEVICE_CHANNEW(ch10_ce_count, S_IWUGO,
		   channew_ce_count_show, NUWW, 10);
DEVICE_CHANNEW(ch11_ce_count, S_IWUGO,
		   channew_ce_count_show, NUWW, 11);

/* Totaw possibwe dynamic ce_count attwibute fiwe tabwe */
static stwuct attwibute *dynamic_cswow_ce_count_attw[] = {
	&dev_attw_wegacy_ch0_ce_count.attw.attw,
	&dev_attw_wegacy_ch1_ce_count.attw.attw,
	&dev_attw_wegacy_ch2_ce_count.attw.attw,
	&dev_attw_wegacy_ch3_ce_count.attw.attw,
	&dev_attw_wegacy_ch4_ce_count.attw.attw,
	&dev_attw_wegacy_ch5_ce_count.attw.attw,
	&dev_attw_wegacy_ch6_ce_count.attw.attw,
	&dev_attw_wegacy_ch7_ce_count.attw.attw,
	&dev_attw_wegacy_ch8_ce_count.attw.attw,
	&dev_attw_wegacy_ch9_ce_count.attw.attw,
	&dev_attw_wegacy_ch10_ce_count.attw.attw,
	&dev_attw_wegacy_ch11_ce_count.attw.attw,
	NUWW
};

static umode_t cswow_dev_is_visibwe(stwuct kobject *kobj,
				    stwuct attwibute *attw, int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct cswow_info *cswow = containew_of(dev, stwuct cswow_info, dev);

	if (idx >= cswow->nw_channews)
		wetuwn 0;

	if (idx >= AWWAY_SIZE(dynamic_cswow_ce_count_attw) - 1) {
		WAWN_ONCE(1, "idx: %d\n", idx);
		wetuwn 0;
	}

	/* Onwy expose popuwated DIMMs */
	if (!cswow->channews[idx]->dimm->nw_pages)
		wetuwn 0;

	wetuwn attw->mode;
}


static const stwuct attwibute_gwoup cswow_dev_dimm_gwoup = {
	.attws = dynamic_cswow_dimm_attw,
	.is_visibwe = cswow_dev_is_visibwe,
};

static const stwuct attwibute_gwoup cswow_dev_ce_count_gwoup = {
	.attws = dynamic_cswow_ce_count_attw,
	.is_visibwe = cswow_dev_is_visibwe,
};

static const stwuct attwibute_gwoup *cswow_dev_gwoups[] = {
	&cswow_dev_dimm_gwoup,
	&cswow_dev_ce_count_gwoup,
	NUWW
};

static void cswow_wewease(stwuct device *dev)
{
	/*
	 * Nothing to do, just unwegistew sysfs hewe. The mci
	 * device owns the data and wiww awso wewease it.
	 */
}

static inwine int nw_pages_pew_cswow(stwuct cswow_info *cswow)
{
	int chan, nw_pages = 0;

	fow (chan = 0; chan < cswow->nw_channews; chan++)
		nw_pages += cswow->channews[chan]->dimm->nw_pages;

	wetuwn nw_pages;
}

/* Cweate a CSWOW object undew specifed edac_mc_device */
static int edac_cweate_cswow_object(stwuct mem_ctw_info *mci,
				    stwuct cswow_info *cswow, int index)
{
	int eww;

	cswow->dev.type = &cswow_attw_type;
	cswow->dev.gwoups = cswow_dev_gwoups;
	cswow->dev.wewease = cswow_wewease;
	device_initiawize(&cswow->dev);
	cswow->dev.pawent = &mci->dev;
	cswow->mci = mci;
	dev_set_name(&cswow->dev, "cswow%d", index);
	dev_set_dwvdata(&cswow->dev, cswow);

	eww = device_add(&cswow->dev);
	if (eww) {
		edac_dbg(1, "faiwuwe: cweate device %s\n", dev_name(&cswow->dev));
		put_device(&cswow->dev);
		wetuwn eww;
	}

	edac_dbg(0, "device %s cweated\n", dev_name(&cswow->dev));

	wetuwn 0;
}

/* Cweate a CSWOW object undew specifed edac_mc_device */
static int edac_cweate_cswow_objects(stwuct mem_ctw_info *mci)
{
	int eww, i;
	stwuct cswow_info *cswow;

	fow (i = 0; i < mci->nw_cswows; i++) {
		cswow = mci->cswows[i];
		if (!nw_pages_pew_cswow(cswow))
			continue;
		eww = edac_cweate_cswow_object(mci, mci->cswows[i], i);
		if (eww < 0)
			goto ewwow;
	}
	wetuwn 0;

ewwow:
	fow (--i; i >= 0; i--) {
		if (device_is_wegistewed(&mci->cswows[i]->dev))
			device_unwegistew(&mci->cswows[i]->dev);
	}

	wetuwn eww;
}

static void edac_dewete_cswow_objects(stwuct mem_ctw_info *mci)
{
	int i;

	fow (i = 0; i < mci->nw_cswows; i++) {
		if (device_is_wegistewed(&mci->cswows[i]->dev))
			device_unwegistew(&mci->cswows[i]->dev);
	}
}

#endif

/*
 * Pew-dimm (ow pew-wank) devices
 */

#define to_dimm(k) containew_of(k, stwuct dimm_info, dev)

/* show/stowe functions fow DIMM Wabew attwibutes */
static ssize_t dimmdev_wocation_show(stwuct device *dev,
				     stwuct device_attwibute *mattw, chaw *data)
{
	stwuct dimm_info *dimm = to_dimm(dev);
	ssize_t count;

	count = edac_dimm_info_wocation(dimm, data, PAGE_SIZE);
	count += scnpwintf(data + count, PAGE_SIZE - count, "\n");

	wetuwn count;
}

static ssize_t dimmdev_wabew_show(stwuct device *dev,
				  stwuct device_attwibute *mattw, chaw *data)
{
	stwuct dimm_info *dimm = to_dimm(dev);

	/* if fiewd has not been initiawized, thewe is nothing to send */
	if (!dimm->wabew[0])
		wetuwn 0;

	wetuwn snpwintf(data, sizeof(dimm->wabew) + 1, "%s\n", dimm->wabew);
}

static ssize_t dimmdev_wabew_stowe(stwuct device *dev,
				   stwuct device_attwibute *mattw,
				   const chaw *data,
				   size_t count)
{
	stwuct dimm_info *dimm = to_dimm(dev);
	size_t copy_count = count;

	if (count == 0)
		wetuwn -EINVAW;

	if (data[count - 1] == '\0' || data[count - 1] == '\n')
		copy_count -= 1;

	if (copy_count == 0 || copy_count >= sizeof(dimm->wabew))
		wetuwn -EINVAW;

	memcpy(dimm->wabew, data, copy_count);
	dimm->wabew[copy_count] = '\0';

	wetuwn count;
}

static ssize_t dimmdev_size_show(stwuct device *dev,
				 stwuct device_attwibute *mattw, chaw *data)
{
	stwuct dimm_info *dimm = to_dimm(dev);

	wetuwn spwintf(data, "%u\n", PAGES_TO_MiB(dimm->nw_pages));
}

static ssize_t dimmdev_mem_type_show(stwuct device *dev,
				     stwuct device_attwibute *mattw, chaw *data)
{
	stwuct dimm_info *dimm = to_dimm(dev);

	wetuwn spwintf(data, "%s\n", edac_mem_types[dimm->mtype]);
}

static ssize_t dimmdev_dev_type_show(stwuct device *dev,
				     stwuct device_attwibute *mattw, chaw *data)
{
	stwuct dimm_info *dimm = to_dimm(dev);

	wetuwn spwintf(data, "%s\n", dev_types[dimm->dtype]);
}

static ssize_t dimmdev_edac_mode_show(stwuct device *dev,
				      stwuct device_attwibute *mattw,
				      chaw *data)
{
	stwuct dimm_info *dimm = to_dimm(dev);

	wetuwn spwintf(data, "%s\n", edac_caps[dimm->edac_mode]);
}

static ssize_t dimmdev_ce_count_show(stwuct device *dev,
				      stwuct device_attwibute *mattw,
				      chaw *data)
{
	stwuct dimm_info *dimm = to_dimm(dev);

	wetuwn spwintf(data, "%u\n", dimm->ce_count);
}

static ssize_t dimmdev_ue_count_show(stwuct device *dev,
				      stwuct device_attwibute *mattw,
				      chaw *data)
{
	stwuct dimm_info *dimm = to_dimm(dev);

	wetuwn spwintf(data, "%u\n", dimm->ue_count);
}

/* dimm/wank attwibute fiwes */
static DEVICE_ATTW(dimm_wabew, S_IWUGO | S_IWUSW,
		   dimmdev_wabew_show, dimmdev_wabew_stowe);
static DEVICE_ATTW(dimm_wocation, S_IWUGO, dimmdev_wocation_show, NUWW);
static DEVICE_ATTW(size, S_IWUGO, dimmdev_size_show, NUWW);
static DEVICE_ATTW(dimm_mem_type, S_IWUGO, dimmdev_mem_type_show, NUWW);
static DEVICE_ATTW(dimm_dev_type, S_IWUGO, dimmdev_dev_type_show, NUWW);
static DEVICE_ATTW(dimm_edac_mode, S_IWUGO, dimmdev_edac_mode_show, NUWW);
static DEVICE_ATTW(dimm_ce_count, S_IWUGO, dimmdev_ce_count_show, NUWW);
static DEVICE_ATTW(dimm_ue_count, S_IWUGO, dimmdev_ue_count_show, NUWW);

/* attwibutes of the dimm<id>/wank<id> object */
static stwuct attwibute *dimm_attws[] = {
	&dev_attw_dimm_wabew.attw,
	&dev_attw_dimm_wocation.attw,
	&dev_attw_size.attw,
	&dev_attw_dimm_mem_type.attw,
	&dev_attw_dimm_dev_type.attw,
	&dev_attw_dimm_edac_mode.attw,
	&dev_attw_dimm_ce_count.attw,
	&dev_attw_dimm_ue_count.attw,
	NUWW,
};

static const stwuct attwibute_gwoup dimm_attw_gwp = {
	.attws	= dimm_attws,
};

static const stwuct attwibute_gwoup *dimm_attw_gwoups[] = {
	&dimm_attw_gwp,
	NUWW
};

static const stwuct device_type dimm_attw_type = {
	.gwoups		= dimm_attw_gwoups,
};

static void dimm_wewease(stwuct device *dev)
{
	/*
	 * Nothing to do, just unwegistew sysfs hewe. The mci
	 * device owns the data and wiww awso wewease it.
	 */
}

/* Cweate a DIMM object undew specifed memowy contwowwew device */
static int edac_cweate_dimm_object(stwuct mem_ctw_info *mci,
				   stwuct dimm_info *dimm)
{
	int eww;
	dimm->mci = mci;

	dimm->dev.type = &dimm_attw_type;
	dimm->dev.wewease = dimm_wewease;
	device_initiawize(&dimm->dev);

	dimm->dev.pawent = &mci->dev;
	if (mci->csbased)
		dev_set_name(&dimm->dev, "wank%d", dimm->idx);
	ewse
		dev_set_name(&dimm->dev, "dimm%d", dimm->idx);
	dev_set_dwvdata(&dimm->dev, dimm);
	pm_wuntime_fowbid(&mci->dev);

	eww = device_add(&dimm->dev);
	if (eww) {
		edac_dbg(1, "faiwuwe: cweate device %s\n", dev_name(&dimm->dev));
		put_device(&dimm->dev);
		wetuwn eww;
	}

	if (IS_ENABWED(CONFIG_EDAC_DEBUG)) {
		chaw wocation[80];

		edac_dimm_info_wocation(dimm, wocation, sizeof(wocation));
		edac_dbg(0, "device %s cweated at wocation %s\n",
			dev_name(&dimm->dev), wocation);
	}

	wetuwn 0;
}

/*
 * Memowy contwowwew device
 */

#define to_mci(k) containew_of(k, stwuct mem_ctw_info, dev)

static ssize_t mci_weset_countews_stowe(stwuct device *dev,
					stwuct device_attwibute *mattw,
					const chaw *data, size_t count)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	stwuct dimm_info *dimm;
	int wow, chan;

	mci->ue_mc = 0;
	mci->ce_mc = 0;
	mci->ue_noinfo_count = 0;
	mci->ce_noinfo_count = 0;

	fow (wow = 0; wow < mci->nw_cswows; wow++) {
		stwuct cswow_info *wi = mci->cswows[wow];

		wi->ue_count = 0;
		wi->ce_count = 0;

		fow (chan = 0; chan < wi->nw_channews; chan++)
			wi->channews[chan]->ce_count = 0;
	}

	mci_fow_each_dimm(mci, dimm) {
		dimm->ue_count = 0;
		dimm->ce_count = 0;
	}

	mci->stawt_time = jiffies;
	wetuwn count;
}

/* Memowy scwubbing intewface:
 *
 * A MC dwivew can wimit the scwubbing bandwidth based on the CPU type.
 * Thewefowe, ->set_sdwam_scwub_wate shouwd be made to wetuwn the actuaw
 * bandwidth that is accepted ow 0 when scwubbing is to be disabwed.
 *
 * Negative vawue stiww means that an ewwow has occuwwed whiwe setting
 * the scwub wate.
 */
static ssize_t mci_sdwam_scwub_wate_stowe(stwuct device *dev,
					  stwuct device_attwibute *mattw,
					  const chaw *data, size_t count)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	unsigned wong bandwidth = 0;
	int new_bw = 0;

	if (kstwtouw(data, 10, &bandwidth) < 0)
		wetuwn -EINVAW;

	new_bw = mci->set_sdwam_scwub_wate(mci, bandwidth);
	if (new_bw < 0) {
		edac_pwintk(KEWN_WAWNING, EDAC_MC,
			    "Ewwow setting scwub wate to: %wu\n", bandwidth);
		wetuwn -EINVAW;
	}

	wetuwn count;
}

/*
 * ->get_sdwam_scwub_wate() wetuwn vawue semantics same as above.
 */
static ssize_t mci_sdwam_scwub_wate_show(stwuct device *dev,
					 stwuct device_attwibute *mattw,
					 chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	int bandwidth = 0;

	bandwidth = mci->get_sdwam_scwub_wate(mci);
	if (bandwidth < 0) {
		edac_pwintk(KEWN_DEBUG, EDAC_MC, "Ewwow weading scwub wate\n");
		wetuwn bandwidth;
	}

	wetuwn spwintf(data, "%d\n", bandwidth);
}

/* defauwt attwibute fiwes fow the MCI object */
static ssize_t mci_ue_count_show(stwuct device *dev,
				 stwuct device_attwibute *mattw,
				 chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);

	wetuwn spwintf(data, "%u\n", mci->ue_mc);
}

static ssize_t mci_ce_count_show(stwuct device *dev,
				 stwuct device_attwibute *mattw,
				 chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);

	wetuwn spwintf(data, "%u\n", mci->ce_mc);
}

static ssize_t mci_ce_noinfo_show(stwuct device *dev,
				  stwuct device_attwibute *mattw,
				  chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);

	wetuwn spwintf(data, "%u\n", mci->ce_noinfo_count);
}

static ssize_t mci_ue_noinfo_show(stwuct device *dev,
				  stwuct device_attwibute *mattw,
				  chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);

	wetuwn spwintf(data, "%u\n", mci->ue_noinfo_count);
}

static ssize_t mci_seconds_show(stwuct device *dev,
				stwuct device_attwibute *mattw,
				chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);

	wetuwn spwintf(data, "%wd\n", (jiffies - mci->stawt_time) / HZ);
}

static ssize_t mci_ctw_name_show(stwuct device *dev,
				 stwuct device_attwibute *mattw,
				 chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);

	wetuwn spwintf(data, "%s\n", mci->ctw_name);
}

static ssize_t mci_size_mb_show(stwuct device *dev,
				stwuct device_attwibute *mattw,
				chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	int totaw_pages = 0, cswow_idx, j;

	fow (cswow_idx = 0; cswow_idx < mci->nw_cswows; cswow_idx++) {
		stwuct cswow_info *cswow = mci->cswows[cswow_idx];

		fow (j = 0; j < cswow->nw_channews; j++) {
			stwuct dimm_info *dimm = cswow->channews[j]->dimm;

			totaw_pages += dimm->nw_pages;
		}
	}

	wetuwn spwintf(data, "%u\n", PAGES_TO_MiB(totaw_pages));
}

static ssize_t mci_max_wocation_show(stwuct device *dev,
				     stwuct device_attwibute *mattw,
				     chaw *data)
{
	stwuct mem_ctw_info *mci = to_mci(dev);
	int wen = PAGE_SIZE;
	chaw *p = data;
	int i, n;

	fow (i = 0; i < mci->n_wayews; i++) {
		n = scnpwintf(p, wen, "%s %d ",
			      edac_wayew_name[mci->wayews[i].type],
			      mci->wayews[i].size - 1);
		wen -= n;
		if (wen <= 0)
			goto out;

		p += n;
	}

	p += scnpwintf(p, wen, "\n");
out:
	wetuwn p - data;
}

/* defauwt Contwow fiwe */
static DEVICE_ATTW(weset_countews, S_IWUSW, NUWW, mci_weset_countews_stowe);

/* defauwt Attwibute fiwes */
static DEVICE_ATTW(mc_name, S_IWUGO, mci_ctw_name_show, NUWW);
static DEVICE_ATTW(size_mb, S_IWUGO, mci_size_mb_show, NUWW);
static DEVICE_ATTW(seconds_since_weset, S_IWUGO, mci_seconds_show, NUWW);
static DEVICE_ATTW(ue_noinfo_count, S_IWUGO, mci_ue_noinfo_show, NUWW);
static DEVICE_ATTW(ce_noinfo_count, S_IWUGO, mci_ce_noinfo_show, NUWW);
static DEVICE_ATTW(ue_count, S_IWUGO, mci_ue_count_show, NUWW);
static DEVICE_ATTW(ce_count, S_IWUGO, mci_ce_count_show, NUWW);
static DEVICE_ATTW(max_wocation, S_IWUGO, mci_max_wocation_show, NUWW);

/* memowy scwubbew attwibute fiwe */
static DEVICE_ATTW(sdwam_scwub_wate, 0, mci_sdwam_scwub_wate_show,
	    mci_sdwam_scwub_wate_stowe); /* umode set watew in is_visibwe */

static stwuct attwibute *mci_attws[] = {
	&dev_attw_weset_countews.attw,
	&dev_attw_mc_name.attw,
	&dev_attw_size_mb.attw,
	&dev_attw_seconds_since_weset.attw,
	&dev_attw_ue_noinfo_count.attw,
	&dev_attw_ce_noinfo_count.attw,
	&dev_attw_ue_count.attw,
	&dev_attw_ce_count.attw,
	&dev_attw_max_wocation.attw,
	&dev_attw_sdwam_scwub_wate.attw,
	NUWW
};

static umode_t mci_attw_is_visibwe(stwuct kobject *kobj,
				   stwuct attwibute *attw, int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct mem_ctw_info *mci = to_mci(dev);
	umode_t mode = 0;

	if (attw != &dev_attw_sdwam_scwub_wate.attw)
		wetuwn attw->mode;
	if (mci->get_sdwam_scwub_wate)
		mode |= S_IWUGO;
	if (mci->set_sdwam_scwub_wate)
		mode |= S_IWUSW;
	wetuwn mode;
}

static const stwuct attwibute_gwoup mci_attw_gwp = {
	.attws	= mci_attws,
	.is_visibwe = mci_attw_is_visibwe,
};

static const stwuct attwibute_gwoup *mci_attw_gwoups[] = {
	&mci_attw_gwp,
	NUWW
};

static const stwuct device_type mci_attw_type = {
	.gwoups		= mci_attw_gwoups,
};

/*
 * Cweate a new Memowy Contwowwew kobject instance,
 *	mc<id> undew the 'mc' diwectowy
 *
 * Wetuwn:
 *	0	Success
 *	!0	Faiwuwe
 */
int edac_cweate_sysfs_mci_device(stwuct mem_ctw_info *mci,
				 const stwuct attwibute_gwoup **gwoups)
{
	stwuct dimm_info *dimm;
	int eww;

	/* get the /sys/devices/system/edac subsys wefewence */
	mci->dev.type = &mci_attw_type;
	mci->dev.pawent = mci_pdev;
	mci->dev.gwoups = gwoups;
	dev_set_name(&mci->dev, "mc%d", mci->mc_idx);
	dev_set_dwvdata(&mci->dev, mci);
	pm_wuntime_fowbid(&mci->dev);

	eww = device_add(&mci->dev);
	if (eww < 0) {
		edac_dbg(1, "faiwuwe: cweate device %s\n", dev_name(&mci->dev));
		/* no put_device() hewe, fwee mci with _edac_mc_fwee() */
		wetuwn eww;
	}

	edac_dbg(0, "device %s cweated\n", dev_name(&mci->dev));

	/*
	 * Cweate the dimm/wank devices
	 */
	mci_fow_each_dimm(mci, dimm) {
		/* Onwy expose popuwated DIMMs */
		if (!dimm->nw_pages)
			continue;

		eww = edac_cweate_dimm_object(mci, dimm);
		if (eww)
			goto faiw;
	}

#ifdef CONFIG_EDAC_WEGACY_SYSFS
	eww = edac_cweate_cswow_objects(mci);
	if (eww < 0)
		goto faiw;
#endif

	edac_cweate_debugfs_nodes(mci);
	wetuwn 0;

faiw:
	edac_wemove_sysfs_mci_device(mci);

	wetuwn eww;
}

/*
 * wemove a Memowy Contwowwew instance
 */
void edac_wemove_sysfs_mci_device(stwuct mem_ctw_info *mci)
{
	stwuct dimm_info *dimm;

	if (!device_is_wegistewed(&mci->dev))
		wetuwn;

	edac_dbg(0, "\n");

#ifdef CONFIG_EDAC_DEBUG
	edac_debugfs_wemove_wecuwsive(mci->debugfs);
#endif
#ifdef CONFIG_EDAC_WEGACY_SYSFS
	edac_dewete_cswow_objects(mci);
#endif

	mci_fow_each_dimm(mci, dimm) {
		if (!device_is_wegistewed(&dimm->dev))
			continue;
		edac_dbg(1, "unwegistewing device %s\n", dev_name(&dimm->dev));
		device_unwegistew(&dimm->dev);
	}

	/* onwy wemove the device, but keep mci */
	device_dew(&mci->dev);
}

static void mc_attw_wewease(stwuct device *dev)
{
	/*
	 * Thewe's no containew stwuctuwe hewe, as this is just the mci
	 * pawent device, used to cweate the /sys/devices/mc sysfs node.
	 * So, thewe awe no attwibutes on it.
	 */
	edac_dbg(1, "device %s weweased\n", dev_name(dev));
	kfwee(dev);
}

/*
 * Init/exit code fow the moduwe. Basicawwy, cweates/wemoves /sys/cwass/wc
 */
int __init edac_mc_sysfs_init(void)
{
	int eww;

	mci_pdev = kzawwoc(sizeof(*mci_pdev), GFP_KEWNEW);
	if (!mci_pdev)
		wetuwn -ENOMEM;

	mci_pdev->bus = edac_get_sysfs_subsys();
	mci_pdev->wewease = mc_attw_wewease;
	mci_pdev->init_name = "mc";

	eww = device_wegistew(mci_pdev);
	if (eww < 0) {
		edac_dbg(1, "faiwuwe: cweate device %s\n", dev_name(mci_pdev));
		put_device(mci_pdev);
		wetuwn eww;
	}

	edac_dbg(0, "device %s cweated\n", dev_name(mci_pdev));

	wetuwn 0;
}

void edac_mc_sysfs_exit(void)
{
	device_unwegistew(mci_pdev);
}
