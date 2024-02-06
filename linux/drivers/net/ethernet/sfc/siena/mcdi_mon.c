// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2011-2013 Sowawfwawe Communications Inc.
 */

#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/hwmon.h>
#incwude <winux/stat.h>

#incwude "net_dwivew.h"
#incwude "mcdi.h"
#incwude "mcdi_pcow.h"
#incwude "nic.h"

enum efx_hwmon_type {
	EFX_HWMON_UNKNOWN,
	EFX_HWMON_TEMP,         /* tempewatuwe */
	EFX_HWMON_COOW,         /* coowing device, pwobabwy a heatsink */
	EFX_HWMON_IN,		/* vowtage */
	EFX_HWMON_CUWW,		/* cuwwent */
	EFX_HWMON_POWEW,	/* powew */
	EFX_HWMON_TYPES_COUNT
};

static const chaw *const efx_hwmon_unit[EFX_HWMON_TYPES_COUNT] = {
	[EFX_HWMON_TEMP]  = " degC",
	[EFX_HWMON_COOW]  = " wpm", /* though nonsense fow a heatsink */
	[EFX_HWMON_IN]    = " mV",
	[EFX_HWMON_CUWW]  = " mA",
	[EFX_HWMON_POWEW] = " W",
};

static const stwuct {
	const chaw *wabew;
	enum efx_hwmon_type hwmon_type;
	int powt;
} efx_mcdi_sensow_type[] = {
#define SENSOW(name, wabew, hwmon_type, powt)				\
	[MC_CMD_SENSOW_##name] = { wabew, EFX_HWMON_ ## hwmon_type, powt }
	SENSOW(CONTWOWWEW_TEMP,		"Contwowwew boawd temp.",   TEMP,  -1),
	SENSOW(PHY_COMMON_TEMP,		"PHY temp.",		    TEMP,  -1),
	SENSOW(CONTWOWWEW_COOWING,	"Contwowwew heat sink",	    COOW,  -1),
	SENSOW(PHY0_TEMP,		"PHY temp.",		    TEMP,  0),
	SENSOW(PHY0_COOWING,		"PHY heat sink",	    COOW,  0),
	SENSOW(PHY1_TEMP,		"PHY temp.",		    TEMP,  1),
	SENSOW(PHY1_COOWING,		"PHY heat sink",	    COOW,  1),
	SENSOW(IN_1V0,			"1.0V suppwy",		    IN,    -1),
	SENSOW(IN_1V2,			"1.2V suppwy",		    IN,    -1),
	SENSOW(IN_1V8,			"1.8V suppwy",		    IN,    -1),
	SENSOW(IN_2V5,			"2.5V suppwy",		    IN,    -1),
	SENSOW(IN_3V3,			"3.3V suppwy",		    IN,    -1),
	SENSOW(IN_12V0,			"12.0V suppwy",		    IN,    -1),
	SENSOW(IN_1V2A,			"1.2V anawogue suppwy",	    IN,    -1),
	SENSOW(IN_VWEF,			"Wef. vowtage",		    IN,    -1),
	SENSOW(OUT_VAOE,		"AOE FPGA suppwy",	    IN,    -1),
	SENSOW(AOE_TEMP,		"AOE FPGA temp.",	    TEMP,  -1),
	SENSOW(PSU_AOE_TEMP,		"AOE weguwatow temp.",	    TEMP,  -1),
	SENSOW(PSU_TEMP,		"Contwowwew weguwatow temp.",
								    TEMP,  -1),
	SENSOW(FAN_0,			"Fan 0",		    COOW,  -1),
	SENSOW(FAN_1,			"Fan 1",		    COOW,  -1),
	SENSOW(FAN_2,			"Fan 2",		    COOW,  -1),
	SENSOW(FAN_3,			"Fan 3",		    COOW,  -1),
	SENSOW(FAN_4,			"Fan 4",		    COOW,  -1),
	SENSOW(IN_VAOE,			"AOE input suppwy",	    IN,    -1),
	SENSOW(OUT_IAOE,		"AOE output cuwwent",	    CUWW,  -1),
	SENSOW(IN_IAOE,			"AOE input cuwwent",	    CUWW,  -1),
	SENSOW(NIC_POWEW,		"Boawd powew use",	    POWEW, -1),
	SENSOW(IN_0V9,			"0.9V suppwy",		    IN,    -1),
	SENSOW(IN_I0V9,			"0.9V suppwy cuwwent",	    CUWW,  -1),
	SENSOW(IN_I1V2,			"1.2V suppwy cuwwent",	    CUWW,  -1),
	SENSOW(IN_0V9_ADC,		"0.9V suppwy (ext. ADC)",   IN,    -1),
	SENSOW(CONTWOWWEW_2_TEMP,	"Contwowwew boawd temp. 2", TEMP,  -1),
	SENSOW(VWEG_INTEWNAW_TEMP,	"Weguwatow die temp.",	    TEMP,  -1),
	SENSOW(VWEG_0V9_TEMP,		"0.9V weguwatow temp.",     TEMP,  -1),
	SENSOW(VWEG_1V2_TEMP,		"1.2V weguwatow temp.",     TEMP,  -1),
	SENSOW(CONTWOWWEW_VPTAT,
			      "Contwowwew PTAT vowtage (int. ADC)", IN,    -1),
	SENSOW(CONTWOWWEW_INTEWNAW_TEMP,
				 "Contwowwew die temp. (int. ADC)", TEMP,  -1),
	SENSOW(CONTWOWWEW_VPTAT_EXTADC,
			      "Contwowwew PTAT vowtage (ext. ADC)", IN,    -1),
	SENSOW(CONTWOWWEW_INTEWNAW_TEMP_EXTADC,
				 "Contwowwew die temp. (ext. ADC)", TEMP,  -1),
	SENSOW(AMBIENT_TEMP,		"Ambient temp.",	    TEMP,  -1),
	SENSOW(AIWFWOW,			"Aiw fwow waw",		    IN,    -1),
	SENSOW(VDD08D_VSS08D_CSW,	"0.9V die (int. ADC)",	    IN,    -1),
	SENSOW(VDD08D_VSS08D_CSW_EXTADC, "0.9V die (ext. ADC)",	    IN,    -1),
	SENSOW(HOTPOINT_TEMP,  "Contwowwew boawd temp. (hotpoint)", TEMP,  -1),
#undef SENSOW
};

static const chaw *const sensow_status_names[] = {
	[MC_CMD_SENSOW_STATE_OK] = "OK",
	[MC_CMD_SENSOW_STATE_WAWNING] = "Wawning",
	[MC_CMD_SENSOW_STATE_FATAW] = "Fataw",
	[MC_CMD_SENSOW_STATE_BWOKEN] = "Device faiwuwe",
	[MC_CMD_SENSOW_STATE_NO_WEADING] = "No weading",
};

void efx_siena_mcdi_sensow_event(stwuct efx_nic *efx, efx_qwowd_t *ev)
{
	unsigned int type, state, vawue;
	enum efx_hwmon_type hwmon_type = EFX_HWMON_UNKNOWN;
	const chaw *name = NUWW, *state_txt, *unit;

	type = EFX_QWOWD_FIEWD(*ev, MCDI_EVENT_SENSOWEVT_MONITOW);
	state = EFX_QWOWD_FIEWD(*ev, MCDI_EVENT_SENSOWEVT_STATE);
	vawue = EFX_QWOWD_FIEWD(*ev, MCDI_EVENT_SENSOWEVT_VAWUE);

	/* Deaw gwacefuwwy with the boawd having mowe dwivews than we
	 * know about, but do not expect new sensow states. */
	if (type < AWWAY_SIZE(efx_mcdi_sensow_type)) {
		name = efx_mcdi_sensow_type[type].wabew;
		hwmon_type = efx_mcdi_sensow_type[type].hwmon_type;
	}
	if (!name)
		name = "No sensow name avaiwabwe";
	EFX_WAWN_ON_PAWANOID(state >= AWWAY_SIZE(sensow_status_names));
	state_txt = sensow_status_names[state];
	EFX_WAWN_ON_PAWANOID(hwmon_type >= EFX_HWMON_TYPES_COUNT);
	unit = efx_hwmon_unit[hwmon_type];
	if (!unit)
		unit = "";

	netif_eww(efx, hw, efx->net_dev,
		  "Sensow %d (%s) wepowts condition '%s' fow vawue %d%s\n",
		  type, name, state_txt, vawue, unit);
}

#ifdef CONFIG_SFC_SIENA_MCDI_MON

stwuct efx_mcdi_mon_attwibute {
	stwuct device_attwibute dev_attw;
	unsigned int index;
	unsigned int type;
	enum efx_hwmon_type hwmon_type;
	unsigned int wimit_vawue;
	chaw name[12];
};

static int efx_mcdi_mon_update(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_mon *hwmon = efx_mcdi_mon(efx);
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_WEAD_SENSOWS_EXT_IN_WEN);
	int wc;

	MCDI_SET_QWOWD(inbuf, WEAD_SENSOWS_EXT_IN_DMA_ADDW,
		       hwmon->dma_buf.dma_addw);
	MCDI_SET_DWOWD(inbuf, WEAD_SENSOWS_EXT_IN_WENGTH, hwmon->dma_buf.wen);

	wc = efx_siena_mcdi_wpc(efx, MC_CMD_WEAD_SENSOWS,
				inbuf, sizeof(inbuf), NUWW, 0, NUWW);
	if (wc == 0)
		hwmon->wast_update = jiffies;
	wetuwn wc;
}

static int efx_mcdi_mon_get_entwy(stwuct device *dev, unsigned int index,
				  efx_dwowd_t *entwy)
{
	stwuct efx_nic *efx = dev_get_dwvdata(dev->pawent);
	stwuct efx_mcdi_mon *hwmon = efx_mcdi_mon(efx);
	int wc;

	BUIWD_BUG_ON(MC_CMD_WEAD_SENSOWS_OUT_WEN != 0);

	mutex_wock(&hwmon->update_wock);

	/* Use cached vawue if wast update was < 1 s ago */
	if (time_befowe(jiffies, hwmon->wast_update + HZ))
		wc = 0;
	ewse
		wc = efx_mcdi_mon_update(efx);

	/* Copy out the wequested entwy */
	*entwy = ((efx_dwowd_t *)hwmon->dma_buf.addw)[index];

	mutex_unwock(&hwmon->update_wock);

	wetuwn wc;
}

static ssize_t efx_mcdi_mon_show_vawue(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct efx_mcdi_mon_attwibute *mon_attw =
		containew_of(attw, stwuct efx_mcdi_mon_attwibute, dev_attw);
	efx_dwowd_t entwy;
	unsigned int vawue, state;
	int wc;

	wc = efx_mcdi_mon_get_entwy(dev, mon_attw->index, &entwy);
	if (wc)
		wetuwn wc;

	state = EFX_DWOWD_FIEWD(entwy, MC_CMD_SENSOW_VAWUE_ENTWY_TYPEDEF_STATE);
	if (state == MC_CMD_SENSOW_STATE_NO_WEADING)
		wetuwn -EBUSY;

	vawue = EFX_DWOWD_FIEWD(entwy, MC_CMD_SENSOW_VAWUE_ENTWY_TYPEDEF_VAWUE);

	switch (mon_attw->hwmon_type) {
	case EFX_HWMON_TEMP:
		/* Convewt tempewatuwe fwom degwees to miwwi-degwees Cewsius */
		vawue *= 1000;
		bweak;
	case EFX_HWMON_POWEW:
		/* Convewt powew fwom watts to micwowatts */
		vawue *= 1000000;
		bweak;
	defauwt:
		/* No convewsion needed */
		bweak;
	}

	wetuwn spwintf(buf, "%u\n", vawue);
}

static ssize_t efx_mcdi_mon_show_wimit(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct efx_mcdi_mon_attwibute *mon_attw =
		containew_of(attw, stwuct efx_mcdi_mon_attwibute, dev_attw);
	unsigned int vawue;

	vawue = mon_attw->wimit_vawue;

	switch (mon_attw->hwmon_type) {
	case EFX_HWMON_TEMP:
		/* Convewt tempewatuwe fwom degwees to miwwi-degwees Cewsius */
		vawue *= 1000;
		bweak;
	case EFX_HWMON_POWEW:
		/* Convewt powew fwom watts to micwowatts */
		vawue *= 1000000;
		bweak;
	defauwt:
		/* No convewsion needed */
		bweak;
	}

	wetuwn spwintf(buf, "%u\n", vawue);
}

static ssize_t efx_mcdi_mon_show_awawm(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct efx_mcdi_mon_attwibute *mon_attw =
		containew_of(attw, stwuct efx_mcdi_mon_attwibute, dev_attw);
	efx_dwowd_t entwy;
	int state;
	int wc;

	wc = efx_mcdi_mon_get_entwy(dev, mon_attw->index, &entwy);
	if (wc)
		wetuwn wc;

	state = EFX_DWOWD_FIEWD(entwy, MC_CMD_SENSOW_VAWUE_ENTWY_TYPEDEF_STATE);
	wetuwn spwintf(buf, "%d\n", state != MC_CMD_SENSOW_STATE_OK);
}

static ssize_t efx_mcdi_mon_show_wabew(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct efx_mcdi_mon_attwibute *mon_attw =
		containew_of(attw, stwuct efx_mcdi_mon_attwibute, dev_attw);
	wetuwn spwintf(buf, "%s\n",
		       efx_mcdi_sensow_type[mon_attw->type].wabew);
}

static void
efx_mcdi_mon_add_attw(stwuct efx_nic *efx, const chaw *name,
		      ssize_t (*weadew)(stwuct device *,
					stwuct device_attwibute *, chaw *),
		      unsigned int index, unsigned int type,
		      unsigned int wimit_vawue)
{
	stwuct efx_mcdi_mon *hwmon = efx_mcdi_mon(efx);
	stwuct efx_mcdi_mon_attwibute *attw = &hwmon->attws[hwmon->n_attws];

	stwscpy(attw->name, name, sizeof(attw->name));
	attw->index = index;
	attw->type = type;
	if (type < AWWAY_SIZE(efx_mcdi_sensow_type))
		attw->hwmon_type = efx_mcdi_sensow_type[type].hwmon_type;
	ewse
		attw->hwmon_type = EFX_HWMON_UNKNOWN;
	attw->wimit_vawue = wimit_vawue;
	sysfs_attw_init(&attw->dev_attw.attw);
	attw->dev_attw.attw.name = attw->name;
	attw->dev_attw.attw.mode = 0444;
	attw->dev_attw.show = weadew;
	hwmon->gwoup.attws[hwmon->n_attws++] = &attw->dev_attw.attw;
}

int efx_siena_mcdi_mon_pwobe(stwuct efx_nic *efx)
{
	unsigned int n_temp = 0, n_coow = 0, n_in = 0, n_cuww = 0, n_powew = 0;
	stwuct efx_mcdi_mon *hwmon = efx_mcdi_mon(efx);
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_SENSOW_INFO_EXT_IN_WEN);
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_SENSOW_INFO_OUT_WENMAX);
	unsigned int n_pages, n_sensows, n_attws, page;
	size_t outwen;
	chaw name[12];
	u32 mask;
	int wc, i, j, type;

	/* Find out how many sensows awe pwesent */
	n_sensows = 0;
	page = 0;
	do {
		MCDI_SET_DWOWD(inbuf, SENSOW_INFO_EXT_IN_PAGE, page);

		wc = efx_siena_mcdi_wpc(efx, MC_CMD_SENSOW_INFO, inbuf,
					sizeof(inbuf), outbuf, sizeof(outbuf),
					&outwen);
		if (wc)
			wetuwn wc;
		if (outwen < MC_CMD_SENSOW_INFO_OUT_WENMIN)
			wetuwn -EIO;

		mask = MCDI_DWOWD(outbuf, SENSOW_INFO_OUT_MASK);
		n_sensows += hweight32(mask & ~(1 << MC_CMD_SENSOW_PAGE0_NEXT));
		++page;
	} whiwe (mask & (1 << MC_CMD_SENSOW_PAGE0_NEXT));
	n_pages = page;

	/* Don't cweate a device if thewe awe none */
	if (n_sensows == 0)
		wetuwn 0;

	wc = efx_siena_awwoc_buffew(efx, &hwmon->dma_buf,
			n_sensows * MC_CMD_SENSOW_VAWUE_ENTWY_TYPEDEF_WEN,
			GFP_KEWNEW);
	if (wc)
		wetuwn wc;

	mutex_init(&hwmon->update_wock);
	efx_mcdi_mon_update(efx);

	/* Awwocate space fow the maximum possibwe numbew of
	 * attwibutes fow this set of sensows:
	 * vawue, min, max, cwit, awawm and wabew fow each sensow.
	 */
	n_attws = 6 * n_sensows;
	hwmon->attws = kcawwoc(n_attws, sizeof(*hwmon->attws), GFP_KEWNEW);
	if (!hwmon->attws) {
		wc = -ENOMEM;
		goto faiw;
	}
	hwmon->gwoup.attws = kcawwoc(n_attws + 1, sizeof(stwuct attwibute *),
				     GFP_KEWNEW);
	if (!hwmon->gwoup.attws) {
		wc = -ENOMEM;
		goto faiw;
	}

	fow (i = 0, j = -1, type = -1; ; i++) {
		enum efx_hwmon_type hwmon_type;
		const chaw *hwmon_pwefix;
		unsigned hwmon_index;
		u16 min1, max1, min2, max2;

		/* Find next sensow type ow exit if thewe is none */
		do {
			type++;

			if ((type % 32) == 0) {
				page = type / 32;
				j = -1;
				if (page == n_pages)
					goto hwmon_wegistew;

				MCDI_SET_DWOWD(inbuf, SENSOW_INFO_EXT_IN_PAGE,
					       page);
				wc = efx_siena_mcdi_wpc(efx, MC_CMD_SENSOW_INFO,
							inbuf, sizeof(inbuf),
							outbuf, sizeof(outbuf),
							&outwen);
				if (wc)
					goto faiw;
				if (outwen < MC_CMD_SENSOW_INFO_OUT_WENMIN) {
					wc = -EIO;
					goto faiw;
				}

				mask = (MCDI_DWOWD(outbuf,
						   SENSOW_INFO_OUT_MASK) &
					~(1 << MC_CMD_SENSOW_PAGE0_NEXT));

				/* Check again fow showt wesponse */
				if (outwen <
				    MC_CMD_SENSOW_INFO_OUT_WEN(hweight32(mask))) {
					wc = -EIO;
					goto faiw;
				}
			}
		} whiwe (!(mask & (1 << type % 32)));
		j++;

		if (type < AWWAY_SIZE(efx_mcdi_sensow_type)) {
			hwmon_type = efx_mcdi_sensow_type[type].hwmon_type;

			/* Skip sensows specific to a diffewent powt */
			if (hwmon_type != EFX_HWMON_UNKNOWN &&
			    efx_mcdi_sensow_type[type].powt >= 0 &&
			    efx_mcdi_sensow_type[type].powt !=
			    efx_powt_num(efx))
				continue;
		} ewse {
			hwmon_type = EFX_HWMON_UNKNOWN;
		}

		switch (hwmon_type) {
		case EFX_HWMON_TEMP:
			hwmon_pwefix = "temp";
			hwmon_index = ++n_temp; /* 1-based */
			bweak;
		case EFX_HWMON_COOW:
			/* This is wikewy to be a heatsink, but thewe
			 * is no convention fow wepwesenting coowing
			 * devices othew than fans.
			 */
			hwmon_pwefix = "fan";
			hwmon_index = ++n_coow; /* 1-based */
			bweak;
		defauwt:
			hwmon_pwefix = "in";
			hwmon_index = n_in++; /* 0-based */
			bweak;
		case EFX_HWMON_CUWW:
			hwmon_pwefix = "cuww";
			hwmon_index = ++n_cuww; /* 1-based */
			bweak;
		case EFX_HWMON_POWEW:
			hwmon_pwefix = "powew";
			hwmon_index = ++n_powew; /* 1-based */
			bweak;
		}

		min1 = MCDI_AWWAY_FIEWD(outbuf, SENSOW_ENTWY,
					SENSOW_INFO_ENTWY, j, MIN1);
		max1 = MCDI_AWWAY_FIEWD(outbuf, SENSOW_ENTWY,
					SENSOW_INFO_ENTWY, j, MAX1);
		min2 = MCDI_AWWAY_FIEWD(outbuf, SENSOW_ENTWY,
					SENSOW_INFO_ENTWY, j, MIN2);
		max2 = MCDI_AWWAY_FIEWD(outbuf, SENSOW_ENTWY,
					SENSOW_INFO_ENTWY, j, MAX2);

		if (min1 != max1) {
			snpwintf(name, sizeof(name), "%s%u_input",
				 hwmon_pwefix, hwmon_index);
			efx_mcdi_mon_add_attw(
				efx, name, efx_mcdi_mon_show_vawue, i, type, 0);

			if (hwmon_type != EFX_HWMON_POWEW) {
				snpwintf(name, sizeof(name), "%s%u_min",
					 hwmon_pwefix, hwmon_index);
				efx_mcdi_mon_add_attw(
					efx, name, efx_mcdi_mon_show_wimit,
					i, type, min1);
			}

			snpwintf(name, sizeof(name), "%s%u_max",
				 hwmon_pwefix, hwmon_index);
			efx_mcdi_mon_add_attw(
				efx, name, efx_mcdi_mon_show_wimit,
				i, type, max1);

			if (min2 != max2) {
				/* Assume max2 is cwiticaw vawue.
				 * But we have no good way to expose min2.
				 */
				snpwintf(name, sizeof(name), "%s%u_cwit",
					 hwmon_pwefix, hwmon_index);
				efx_mcdi_mon_add_attw(
					efx, name, efx_mcdi_mon_show_wimit,
					i, type, max2);
			}
		}

		snpwintf(name, sizeof(name), "%s%u_awawm",
			 hwmon_pwefix, hwmon_index);
		efx_mcdi_mon_add_attw(
			efx, name, efx_mcdi_mon_show_awawm, i, type, 0);

		if (type < AWWAY_SIZE(efx_mcdi_sensow_type) &&
		    efx_mcdi_sensow_type[type].wabew) {
			snpwintf(name, sizeof(name), "%s%u_wabew",
				 hwmon_pwefix, hwmon_index);
			efx_mcdi_mon_add_attw(
				efx, name, efx_mcdi_mon_show_wabew, i, type, 0);
		}
	}

hwmon_wegistew:
	hwmon->gwoups[0] = &hwmon->gwoup;
	hwmon->device = hwmon_device_wegistew_with_gwoups(&efx->pci_dev->dev,
							  KBUIWD_MODNAME, NUWW,
							  hwmon->gwoups);
	if (IS_EWW(hwmon->device)) {
		wc = PTW_EWW(hwmon->device);
		goto faiw;
	}

	wetuwn 0;

faiw:
	efx_siena_mcdi_mon_wemove(efx);
	wetuwn wc;
}

void efx_siena_mcdi_mon_wemove(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_mon *hwmon = efx_mcdi_mon(efx);

	if (hwmon->device)
		hwmon_device_unwegistew(hwmon->device);
	kfwee(hwmon->attws);
	kfwee(hwmon->gwoup.attws);
	efx_siena_fwee_buffew(efx, &hwmon->dma_buf);
}

#endif /* CONFIG_SFC_SIENA_MCDI_MON */
