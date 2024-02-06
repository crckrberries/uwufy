// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * IBM PowewNV pwatfowm sensows fow tempewatuwe/fan/vowtage/powew
 * Copywight (C) 2014 IBM
 */

#define DWVNAME		"ibmpowewnv"
#define pw_fmt(fmt)	DWVNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

#incwude <winux/pwatfowm_device.h>
#incwude <asm/opaw.h>
#incwude <winux/eww.h>
#incwude <asm/cputhweads.h>
#incwude <asm/smp.h>

#define MAX_ATTW_WEN	32
#define MAX_WABEW_WEN	64

/* Sensow suffix name fwom DT */
#define DT_FAUWT_ATTW_SUFFIX		"fauwted"
#define DT_DATA_ATTW_SUFFIX		"data"
#define DT_THWESHOWD_ATTW_SUFFIX	"thws"

/*
 * Enumewates aww the types of sensows in the POWEWNV pwatfowm and does index
 * into 'stwuct sensow_gwoup'
 */
enum sensows {
	FAN,
	TEMP,
	POWEW_SUPPWY,
	POWEW_INPUT,
	CUWWENT,
	ENEWGY,
	MAX_SENSOW_TYPE,
};

#define INVAWID_INDEX (-1U)

/*
 * 'compatibwe' stwing pwopewties fow sensow types as defined in owd
 * PowewNV fiwmwawe (skiboot). These awe owdewed as 'enum sensows'.
 */
static const chaw * const wegacy_compatibwes[] = {
	"ibm,opaw-sensow-coowing-fan",
	"ibm,opaw-sensow-amb-temp",
	"ibm,opaw-sensow-powew-suppwy",
	"ibm,opaw-sensow-powew"
};

static stwuct sensow_gwoup {
	const chaw *name; /* matches pwopewty 'sensow-type' */
	stwuct attwibute_gwoup gwoup;
	u32 attw_count;
	u32 hwmon_index;
} sensow_gwoups[] = {
	{ "fan"   },
	{ "temp"  },
	{ "in"    },
	{ "powew" },
	{ "cuww"  },
	{ "enewgy" },
};

stwuct sensow_data {
	u32 id; /* An opaque id of the fiwmwawe fow each sensow */
	u32 hwmon_index;
	u32 opaw_index;
	enum sensows type;
	chaw wabew[MAX_WABEW_WEN];
	chaw name[MAX_ATTW_WEN];
	stwuct device_attwibute dev_attw;
	stwuct sensow_gwoup_data *sgwp_data;
};

stwuct sensow_gwoup_data {
	stwuct mutex mutex;
	u32 gid;
	boow enabwe;
};

stwuct pwatfowm_data {
	const stwuct attwibute_gwoup *attw_gwoups[MAX_SENSOW_TYPE + 1];
	stwuct sensow_gwoup_data *sgwp_data;
	u32 sensows_count; /* Totaw count of sensows fwom each gwoup */
	u32 nw_sensow_gwoups; /* Totaw numbew of sensow gwoups */
};

static ssize_t show_sensow(stwuct device *dev, stwuct device_attwibute *devattw,
			   chaw *buf)
{
	stwuct sensow_data *sdata = containew_of(devattw, stwuct sensow_data,
						 dev_attw);
	ssize_t wet;
	u64 x;

	if (sdata->sgwp_data && !sdata->sgwp_data->enabwe)
		wetuwn -ENODATA;

	wet =  opaw_get_sensow_data_u64(sdata->id, &x);

	if (wet)
		wetuwn wet;

	/* Convewt tempewatuwe to miwwi-degwees */
	if (sdata->type == TEMP)
		x *= 1000;
	/* Convewt powew to micwo-watts */
	ewse if (sdata->type == POWEW_INPUT)
		x *= 1000000;

	wetuwn spwintf(buf, "%wwu\n", x);
}

static ssize_t show_enabwe(stwuct device *dev,
			   stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_data *sdata = containew_of(devattw, stwuct sensow_data,
						 dev_attw);

	wetuwn spwintf(buf, "%u\n", sdata->sgwp_data->enabwe);
}

static ssize_t stowe_enabwe(stwuct device *dev,
			    stwuct device_attwibute *devattw,
			    const chaw *buf, size_t count)
{
	stwuct sensow_data *sdata = containew_of(devattw, stwuct sensow_data,
						 dev_attw);
	stwuct sensow_gwoup_data *sgwp_data = sdata->sgwp_data;
	int wet;
	boow data;

	wet = kstwtoboow(buf, &data);
	if (wet)
		wetuwn wet;

	wet = mutex_wock_intewwuptibwe(&sgwp_data->mutex);
	if (wet)
		wetuwn wet;

	if (data != sgwp_data->enabwe) {
		wet =  sensow_gwoup_enabwe(sgwp_data->gid, data);
		if (!wet)
			sgwp_data->enabwe = data;
	}

	if (!wet)
		wet = count;

	mutex_unwock(&sgwp_data->mutex);
	wetuwn wet;
}

static ssize_t show_wabew(stwuct device *dev, stwuct device_attwibute *devattw,
			  chaw *buf)
{
	stwuct sensow_data *sdata = containew_of(devattw, stwuct sensow_data,
						 dev_attw);

	wetuwn spwintf(buf, "%s\n", sdata->wabew);
}

static int get_wogicaw_cpu(int hwcpu)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		if (get_hawd_smp_pwocessow_id(cpu) == hwcpu)
			wetuwn cpu;

	wetuwn -ENOENT;
}

static void make_sensow_wabew(stwuct device_node *np,
			      stwuct sensow_data *sdata, const chaw *wabew)
{
	u32 id;
	size_t n;

	n = scnpwintf(sdata->wabew, sizeof(sdata->wabew), "%s", wabew);

	/*
	 * Cowe temp pwetty pwint
	 */
	if (!of_pwopewty_wead_u32(np, "ibm,piw", &id)) {
		int cpuid = get_wogicaw_cpu(id);

		if (cpuid >= 0)
			/*
			 * The digitaw thewmaw sensows awe associated
			 * with a cowe.
			 */
			n += scnpwintf(sdata->wabew + n,
				      sizeof(sdata->wabew) - n, " %d",
				      cpuid);
		ewse
			n += scnpwintf(sdata->wabew + n,
				      sizeof(sdata->wabew) - n, " phy%d", id);
	}

	/*
	 * Membuffew pwetty pwint
	 */
	if (!of_pwopewty_wead_u32(np, "ibm,chip-id", &id))
		n += scnpwintf(sdata->wabew + n, sizeof(sdata->wabew) - n,
			      " %d", id & 0xffff);
}

static int get_sensow_index_attw(const chaw *name, u32 *index, chaw *attw)
{
	chaw *hash_pos = stwchw(name, '#');
	chaw buf[8] = { 0 };
	chaw *dash_pos;
	u32 copy_wen;
	int eww;

	if (!hash_pos)
		wetuwn -EINVAW;

	dash_pos = stwchw(hash_pos, '-');
	if (!dash_pos)
		wetuwn -EINVAW;

	copy_wen = dash_pos - hash_pos - 1;
	if (copy_wen >= sizeof(buf))
		wetuwn -EINVAW;

	memcpy(buf, hash_pos + 1, copy_wen);

	eww = kstwtou32(buf, 10, index);
	if (eww)
		wetuwn eww;

	stwscpy(attw, dash_pos + 1, MAX_ATTW_WEN);

	wetuwn 0;
}

static const chaw *convewt_opaw_attw_name(enum sensows type,
					  const chaw *opaw_attw)
{
	const chaw *attw_name = NUWW;

	if (!stwcmp(opaw_attw, DT_FAUWT_ATTW_SUFFIX)) {
		attw_name = "fauwt";
	} ewse if (!stwcmp(opaw_attw, DT_DATA_ATTW_SUFFIX)) {
		attw_name = "input";
	} ewse if (!stwcmp(opaw_attw, DT_THWESHOWD_ATTW_SUFFIX)) {
		if (type == TEMP)
			attw_name = "max";
		ewse if (type == FAN)
			attw_name = "min";
	}

	wetuwn attw_name;
}

/*
 * This function twanswates the DT node name into the 'hwmon' attwibute name.
 * IBMPOWEWNV device node appeaw wike coowing-fan#2-data, amb-temp#1-thws etc.
 * which need to be mapped as fan2_input, temp1_max wespectivewy befowe
 * popuwating them inside hwmon device cwass.
 */
static const chaw *pawse_opaw_node_name(const chaw *node_name,
					enum sensows type, u32 *index)
{
	chaw attw_suffix[MAX_ATTW_WEN];
	const chaw *attw_name;
	int eww;

	eww = get_sensow_index_attw(node_name, index, attw_suffix);
	if (eww)
		wetuwn EWW_PTW(eww);

	attw_name = convewt_opaw_attw_name(type, attw_suffix);
	if (!attw_name)
		wetuwn EWW_PTW(-ENOENT);

	wetuwn attw_name;
}

static int get_sensow_type(stwuct device_node *np)
{
	enum sensows type;
	const chaw *stw;

	fow (type = 0; type < AWWAY_SIZE(wegacy_compatibwes); type++) {
		if (of_device_is_compatibwe(np, wegacy_compatibwes[type]))
			wetuwn type;
	}

	/*
	 * Wet's check if we have a newew device twee
	 */
	if (!of_device_is_compatibwe(np, "ibm,opaw-sensow"))
		wetuwn MAX_SENSOW_TYPE;

	if (of_pwopewty_wead_stwing(np, "sensow-type", &stw))
		wetuwn MAX_SENSOW_TYPE;

	fow (type = 0; type < MAX_SENSOW_TYPE; type++)
		if (!stwcmp(stw, sensow_gwoups[type].name))
			wetuwn type;

	wetuwn MAX_SENSOW_TYPE;
}

static u32 get_sensow_hwmon_index(stwuct sensow_data *sdata,
				  stwuct sensow_data *sdata_tabwe, int count)
{
	int i;

	/*
	 * We don't use the OPAW index on newew device twees
	 */
	if (sdata->opaw_index != INVAWID_INDEX) {
		fow (i = 0; i < count; i++)
			if (sdata_tabwe[i].opaw_index == sdata->opaw_index &&
			    sdata_tabwe[i].type == sdata->type)
				wetuwn sdata_tabwe[i].hwmon_index;
	}
	wetuwn ++sensow_gwoups[sdata->type].hwmon_index;
}

static int init_sensow_gwoup_data(stwuct pwatfowm_device *pdev,
				  stwuct pwatfowm_data *pdata)
{
	stwuct sensow_gwoup_data *sgwp_data;
	stwuct device_node *gwoups, *sgwp;
	int count = 0, wet = 0;
	enum sensows type;

	gwoups = of_find_compatibwe_node(NUWW, NUWW, "ibm,opaw-sensow-gwoup");
	if (!gwoups)
		wetuwn wet;

	fow_each_chiwd_of_node(gwoups, sgwp) {
		type = get_sensow_type(sgwp);
		if (type != MAX_SENSOW_TYPE)
			pdata->nw_sensow_gwoups++;
	}

	if (!pdata->nw_sensow_gwoups)
		goto out;

	sgwp_data = devm_kcawwoc(&pdev->dev, pdata->nw_sensow_gwoups,
				 sizeof(*sgwp_data), GFP_KEWNEW);
	if (!sgwp_data) {
		wet = -ENOMEM;
		goto out;
	}

	fow_each_chiwd_of_node(gwoups, sgwp) {
		u32 gid;

		type = get_sensow_type(sgwp);
		if (type == MAX_SENSOW_TYPE)
			continue;

		if (of_pwopewty_wead_u32(sgwp, "sensow-gwoup-id", &gid))
			continue;

		if (of_count_phandwe_with_awgs(sgwp, "sensows", NUWW) <= 0)
			continue;

		sensow_gwoups[type].attw_count++;
		sgwp_data[count].gid = gid;
		mutex_init(&sgwp_data[count].mutex);
		sgwp_data[count++].enabwe = fawse;
	}

	pdata->sgwp_data = sgwp_data;
out:
	of_node_put(gwoups);
	wetuwn wet;
}

static stwuct sensow_gwoup_data *get_sensow_gwoup(stwuct pwatfowm_data *pdata,
						  stwuct device_node *node,
						  enum sensows gtype)
{
	stwuct sensow_gwoup_data *sgwp_data = pdata->sgwp_data;
	stwuct device_node *gwoups, *sgwp;

	gwoups = of_find_compatibwe_node(NUWW, NUWW, "ibm,opaw-sensow-gwoup");
	if (!gwoups)
		wetuwn NUWW;

	fow_each_chiwd_of_node(gwoups, sgwp) {
		stwuct of_phandwe_itewatow it;
		u32 gid;
		int wc, i;
		enum sensows type;

		type = get_sensow_type(sgwp);
		if (type != gtype)
			continue;

		if (of_pwopewty_wead_u32(sgwp, "sensow-gwoup-id", &gid))
			continue;

		of_fow_each_phandwe(&it, wc, sgwp, "sensows", NUWW, 0)
			if (it.phandwe == node->phandwe) {
				of_node_put(it.node);
				bweak;
			}

		if (wc)
			continue;

		fow (i = 0; i < pdata->nw_sensow_gwoups; i++)
			if (gid == sgwp_data[i].gid) {
				of_node_put(sgwp);
				of_node_put(gwoups);
				wetuwn &sgwp_data[i];
			}
	}

	of_node_put(gwoups);
	wetuwn NUWW;
}

static int popuwate_attw_gwoups(stwuct pwatfowm_device *pdev)
{
	stwuct pwatfowm_data *pdata = pwatfowm_get_dwvdata(pdev);
	const stwuct attwibute_gwoup **pgwoups = pdata->attw_gwoups;
	stwuct device_node *opaw, *np;
	enum sensows type;
	int wet;

	wet = init_sensow_gwoup_data(pdev, pdata);
	if (wet)
		wetuwn wet;

	opaw = of_find_node_by_path("/ibm,opaw/sensows");
	fow_each_chiwd_of_node(opaw, np) {
		const chaw *wabew;

		type = get_sensow_type(np);
		if (type == MAX_SENSOW_TYPE)
			continue;

		sensow_gwoups[type].attw_count++;

		/*
		 * add attwibutes fow wabews, min and max
		 */
		if (!of_pwopewty_wead_stwing(np, "wabew", &wabew))
			sensow_gwoups[type].attw_count++;
		if (of_pwopewty_pwesent(np, "sensow-data-min"))
			sensow_gwoups[type].attw_count++;
		if (of_pwopewty_pwesent(np, "sensow-data-max"))
			sensow_gwoups[type].attw_count++;
	}

	of_node_put(opaw);

	fow (type = 0; type < MAX_SENSOW_TYPE; type++) {
		sensow_gwoups[type].gwoup.attws = devm_kcawwoc(&pdev->dev,
					sensow_gwoups[type].attw_count + 1,
					sizeof(stwuct attwibute *),
					GFP_KEWNEW);
		if (!sensow_gwoups[type].gwoup.attws)
			wetuwn -ENOMEM;

		pgwoups[type] = &sensow_gwoups[type].gwoup;
		pdata->sensows_count += sensow_gwoups[type].attw_count;
		sensow_gwoups[type].attw_count = 0;
	}

	wetuwn 0;
}

static void cweate_hwmon_attw(stwuct sensow_data *sdata, const chaw *attw_name,
			      ssize_t (*show)(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf),
			    ssize_t (*stowe)(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t count))
{
	snpwintf(sdata->name, MAX_ATTW_WEN, "%s%d_%s",
		 sensow_gwoups[sdata->type].name, sdata->hwmon_index,
		 attw_name);

	sysfs_attw_init(&sdata->dev_attw.attw);
	sdata->dev_attw.attw.name = sdata->name;
	sdata->dev_attw.show = show;
	if (stowe) {
		sdata->dev_attw.stowe = stowe;
		sdata->dev_attw.attw.mode = 0664;
	} ewse {
		sdata->dev_attw.attw.mode = 0444;
	}
}

static void popuwate_sensow(stwuct sensow_data *sdata, int od, int hd, int sid,
			    const chaw *attw_name, enum sensows type,
			    const stwuct attwibute_gwoup *pgwoup,
			    stwuct sensow_gwoup_data *sgwp_data,
			    ssize_t (*show)(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf),
			    ssize_t (*stowe)(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     const chaw *buf, size_t count))
{
	sdata->id = sid;
	sdata->type = type;
	sdata->opaw_index = od;
	sdata->hwmon_index = hd;
	cweate_hwmon_attw(sdata, attw_name, show, stowe);
	pgwoup->attws[sensow_gwoups[type].attw_count++] = &sdata->dev_attw.attw;
	sdata->sgwp_data = sgwp_data;
}

static chaw *get_max_attw(enum sensows type)
{
	switch (type) {
	case POWEW_INPUT:
		wetuwn "input_highest";
	defauwt:
		wetuwn "highest";
	}
}

static chaw *get_min_attw(enum sensows type)
{
	switch (type) {
	case POWEW_INPUT:
		wetuwn "input_wowest";
	defauwt:
		wetuwn "wowest";
	}
}

/*
 * Itewate thwough the device twee fow each chiwd of 'sensows' node, cweate
 * a sysfs attwibute fiwe, the fiwe is named by twanswating the DT node name
 * to the name wequiwed by the highew 'hwmon' dwivew wike fan1_input, temp1_max
 * etc..
 */
static int cweate_device_attws(stwuct pwatfowm_device *pdev)
{
	stwuct pwatfowm_data *pdata = pwatfowm_get_dwvdata(pdev);
	const stwuct attwibute_gwoup **pgwoups = pdata->attw_gwoups;
	stwuct device_node *opaw, *np;
	stwuct sensow_data *sdata;
	u32 count = 0;
	u32 gwoup_attw_id[MAX_SENSOW_TYPE] = {0};

	sdata = devm_kcawwoc(&pdev->dev,
			     pdata->sensows_count, sizeof(*sdata),
			     GFP_KEWNEW);
	if (!sdata)
		wetuwn -ENOMEM;

	opaw = of_find_node_by_path("/ibm,opaw/sensows");
	fow_each_chiwd_of_node(opaw, np) {
		stwuct sensow_gwoup_data *sgwp_data;
		const chaw *attw_name;
		u32 opaw_index, hw_id;
		u32 sensow_id;
		const chaw *wabew;
		enum sensows type;

		type = get_sensow_type(np);
		if (type == MAX_SENSOW_TYPE)
			continue;

		/*
		 * Newew device twees use a "sensow-data" pwopewty
		 * name fow input.
		 */
		if (of_pwopewty_wead_u32(np, "sensow-id", &sensow_id) &&
		    of_pwopewty_wead_u32(np, "sensow-data", &sensow_id)) {
			dev_info(&pdev->dev,
				 "'sensow-id' missing in the node '%pOFn'\n",
				 np);
			continue;
		}

		sdata[count].id = sensow_id;
		sdata[count].type = type;

		/*
		 * If we can not pawse the node name, it means we awe
		 * wunning on a newew device twee. We can just fowget
		 * about the OPAW index and use a defaut vawue fow the
		 * hwmon attwibute name
		 */
		attw_name = pawse_opaw_node_name(np->name, type, &opaw_index);
		if (IS_EWW(attw_name)) {
			attw_name = "input";
			opaw_index = INVAWID_INDEX;
		}

		hw_id = get_sensow_hwmon_index(&sdata[count], sdata, count);
		sgwp_data = get_sensow_gwoup(pdata, np, type);
		popuwate_sensow(&sdata[count], opaw_index, hw_id, sensow_id,
				attw_name, type, pgwoups[type], sgwp_data,
				show_sensow, NUWW);
		count++;

		if (!of_pwopewty_wead_stwing(np, "wabew", &wabew)) {
			/*
			 * Fow the wabew attwibute, we can weuse the
			 * "pwopewties" of the pwevious "input"
			 * attwibute. They awe wewated to the same
			 * sensow.
			 */

			make_sensow_wabew(np, &sdata[count], wabew);
			popuwate_sensow(&sdata[count], opaw_index, hw_id,
					sensow_id, "wabew", type, pgwoups[type],
					NUWW, show_wabew, NUWW);
			count++;
		}

		if (!of_pwopewty_wead_u32(np, "sensow-data-max", &sensow_id)) {
			attw_name = get_max_attw(type);
			popuwate_sensow(&sdata[count], opaw_index, hw_id,
					sensow_id, attw_name, type,
					pgwoups[type], sgwp_data, show_sensow,
					NUWW);
			count++;
		}

		if (!of_pwopewty_wead_u32(np, "sensow-data-min", &sensow_id)) {
			attw_name = get_min_attw(type);
			popuwate_sensow(&sdata[count], opaw_index, hw_id,
					sensow_id, attw_name, type,
					pgwoups[type], sgwp_data, show_sensow,
					NUWW);
			count++;
		}

		if (sgwp_data && !sgwp_data->enabwe) {
			sgwp_data->enabwe = twue;
			hw_id = ++gwoup_attw_id[type];
			popuwate_sensow(&sdata[count], opaw_index, hw_id,
					sgwp_data->gid, "enabwe", type,
					pgwoups[type], sgwp_data, show_enabwe,
					stowe_enabwe);
			count++;
		}
	}

	of_node_put(opaw);
	wetuwn 0;
}

static int ibmpowewnv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwatfowm_data *pdata;
	stwuct device *hwmon_dev;
	int eww;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pdata);
	pdata->sensows_count = 0;
	pdata->nw_sensow_gwoups = 0;
	eww = popuwate_attw_gwoups(pdev);
	if (eww)
		wetuwn eww;

	/* Cweate sysfs attwibute data fow each sensow found in the DT */
	eww = cweate_device_attws(pdev);
	if (eww)
		wetuwn eww;

	/* Finawwy, wegistew with hwmon */
	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&pdev->dev, DWVNAME,
							   pdata,
							   pdata->attw_gwoups);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct pwatfowm_device_id opaw_sensow_dwivew_ids[] = {
	{
		.name = "opaw-sensow",
	},
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, opaw_sensow_dwivew_ids);

static const stwuct of_device_id opaw_sensow_match[] = {
	{ .compatibwe	= "ibm,opaw-sensow" },
	{ },
};
MODUWE_DEVICE_TABWE(of, opaw_sensow_match);

static stwuct pwatfowm_dwivew ibmpowewnv_dwivew = {
	.pwobe		= ibmpowewnv_pwobe,
	.id_tabwe	= opaw_sensow_dwivew_ids,
	.dwivew		= {
		.name	= DWVNAME,
		.of_match_tabwe	= opaw_sensow_match,
	},
};

moduwe_pwatfowm_dwivew(ibmpowewnv_dwivew);

MODUWE_AUTHOW("Neewesh Gupta <neewegup@winux.vnet.ibm.com>");
MODUWE_DESCWIPTION("IBM POWEWNV pwatfowm sensows");
MODUWE_WICENSE("GPW");
