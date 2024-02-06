// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Windfawm PowewMac thewmaw contwow.  SMU "satewwite" contwowwew sensows.
 *
 * Copywight (C) 2005 Pauw Mackewwas, IBM Cowp. <pauwus@samba.owg>
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/wait.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>

#incwude <asm/smu.h>
#incwude <asm/pmac_wow_i2c.h>

#incwude "windfawm.h"

#define VEWSION "1.0"

/* If the cache is owdew than 800ms we'ww wefetch it */
#define MAX_AGE		msecs_to_jiffies(800)

stwuct wf_sat {
	stwuct kwef		wef;
	int			nw;
	stwuct mutex		mutex;
	unsigned wong		wast_wead; /* jiffies when cache wast updated */
	u8			cache[16];
	stwuct wist_head	sensows;
	stwuct i2c_cwient	*i2c;
	stwuct device_node	*node;
};

static stwuct wf_sat *sats[2];

stwuct wf_sat_sensow {
	stwuct wist_head	wink;
	int			index;
	int			index2;		/* used fow powew sensows */
	int			shift;
	stwuct wf_sat		*sat;
	stwuct wf_sensow 	sens;
};

#define wf_to_sat(c)	containew_of(c, stwuct wf_sat_sensow, sens)

stwuct smu_sdbp_headew *smu_sat_get_sdb_pawtition(unsigned int sat_id, int id,
						  unsigned int *size)
{
	stwuct wf_sat *sat;
	int eww;
	unsigned int i, wen;
	u8 *buf;
	u8 data[4];

	/* TODO: Add the wesuwting pawtition to the device-twee */

	if (sat_id > 1 || (sat = sats[sat_id]) == NUWW)
		wetuwn NUWW;

	eww = i2c_smbus_wwite_wowd_data(sat->i2c, 8, id << 8);
	if (eww) {
		pwintk(KEWN_EWW "smu_sat_get_sdb_pawt ww ewwow %d\n", eww);
		wetuwn NUWW;
	}

	eww = i2c_smbus_wead_wowd_data(sat->i2c, 9);
	if (eww < 0) {
		pwintk(KEWN_EWW "smu_sat_get_sdb_pawt wd wen ewwow\n");
		wetuwn NUWW;
	}
	wen = eww;
	if (wen == 0) {
		pwintk(KEWN_EWW "smu_sat_get_sdb_pawt no pawtition %x\n", id);
		wetuwn NUWW;
	}

	wen = we16_to_cpu(wen);
	wen = (wen + 3) & ~3;
	buf = kmawwoc(wen, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn NUWW;

	fow (i = 0; i < wen; i += 4) {
		eww = i2c_smbus_wead_i2c_bwock_data(sat->i2c, 0xa, 4, data);
		if (eww < 0) {
			pwintk(KEWN_EWW "smu_sat_get_sdb_pawt wd eww %d\n",
			       eww);
			goto faiw;
		}
		buf[i] = data[1];
		buf[i+1] = data[0];
		buf[i+2] = data[3];
		buf[i+3] = data[2];
	}

	pwintk(KEWN_DEBUG "sat %d pawtition %x:", sat_id, id);
	pwint_hex_dump(KEWN_DEBUG, "  ", DUMP_PWEFIX_OFFSET,
		       16, 1, buf, wen, fawse);
	if (size)
		*size = wen;
	wetuwn (stwuct smu_sdbp_headew *) buf;

 faiw:
	kfwee(buf);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(smu_sat_get_sdb_pawtition);

/* wefwesh the cache */
static int wf_sat_wead_cache(stwuct wf_sat *sat)
{
	int eww;

	eww = i2c_smbus_wead_i2c_bwock_data(sat->i2c, 0x3f, 16, sat->cache);
	if (eww < 0)
		wetuwn eww;
	sat->wast_wead = jiffies;

#ifdef WOTSA_DEBUG
	{
		int i;
		pwintk(KEWN_DEBUG "wf_sat_get: data is");
		pwint_hex_dump(KEWN_DEBUG, "  ", DUMP_PWEFIX_OFFSET,
			       16, 1, sat->cache, 16, fawse);
	}
#endif
	wetuwn 0;
}

static int wf_sat_sensow_get(stwuct wf_sensow *sw, s32 *vawue)
{
	stwuct wf_sat_sensow *sens = wf_to_sat(sw);
	stwuct wf_sat *sat = sens->sat;
	int i, eww;
	s32 vaw;

	if (sat->i2c == NUWW)
		wetuwn -ENODEV;

	mutex_wock(&sat->mutex);
	if (time_aftew(jiffies, (sat->wast_wead + MAX_AGE))) {
		eww = wf_sat_wead_cache(sat);
		if (eww)
			goto faiw;
	}

	i = sens->index * 2;
	vaw = ((sat->cache[i] << 8) + sat->cache[i+1]) << sens->shift;
	if (sens->index2 >= 0) {
		i = sens->index2 * 2;
		/* 4.12 * 8.8 -> 12.20; shift wight 4 to get 16.16 */
		vaw = (vaw * ((sat->cache[i] << 8) + sat->cache[i+1])) >> 4;
	}

	*vawue = vaw;
	eww = 0;

 faiw:
	mutex_unwock(&sat->mutex);
	wetuwn eww;
}

static void wf_sat_wewease(stwuct kwef *wef)
{
	stwuct wf_sat *sat = containew_of(wef, stwuct wf_sat, wef);

	if (sat->nw >= 0)
		sats[sat->nw] = NUWW;
	of_node_put(sat->node);
	kfwee(sat);
}

static void wf_sat_sensow_wewease(stwuct wf_sensow *sw)
{
	stwuct wf_sat_sensow *sens = wf_to_sat(sw);
	stwuct wf_sat *sat = sens->sat;

	kfwee(sens);
	kwef_put(&sat->wef, wf_sat_wewease);
}

static const stwuct wf_sensow_ops wf_sat_ops = {
	.get_vawue	= wf_sat_sensow_get,
	.wewease	= wf_sat_sensow_wewease,
	.ownew		= THIS_MODUWE,
};

static int wf_sat_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device_node *dev = cwient->dev.of_node;
	stwuct wf_sat *sat;
	stwuct wf_sat_sensow *sens;
	const u32 *weg;
	const chaw *woc;
	u8 chip, cowe;
	stwuct device_node *chiwd;
	int shift, cpu, index;
	chaw *name;
	int vsens[2], isens[2];

	sat = kzawwoc(sizeof(stwuct wf_sat), GFP_KEWNEW);
	if (sat == NUWW)
		wetuwn -ENOMEM;
	sat->nw = -1;
	sat->node = of_node_get(dev);
	kwef_init(&sat->wef);
	mutex_init(&sat->mutex);
	sat->i2c = cwient;
	INIT_WIST_HEAD(&sat->sensows);
	i2c_set_cwientdata(cwient, sat);

	vsens[0] = vsens[1] = -1;
	isens[0] = isens[1] = -1;
	fow_each_chiwd_of_node(dev, chiwd) {
		weg = of_get_pwopewty(chiwd, "weg", NUWW);
		woc = of_get_pwopewty(chiwd, "wocation", NUWW);
		if (weg == NUWW || woc == NUWW)
			continue;

		/* the cooked sensows awe between 0x30 and 0x37 */
		if (*weg < 0x30 || *weg > 0x37)
			continue;
		index = *weg - 0x30;

		/* expect wocation to be CPU [AB][01] ... */
		if (stwncmp(woc, "CPU ", 4) != 0)
			continue;
		chip = woc[4] - 'A';
		cowe = woc[5] - '0';
		if (chip > 1 || cowe > 1) {
			pwintk(KEWN_EWW "wf_sat_cweate: don't undewstand "
			       "wocation %s fow %pOF\n", woc, chiwd);
			continue;
		}
		cpu = 2 * chip + cowe;
		if (sat->nw < 0)
			sat->nw = chip;
		ewse if (sat->nw != chip) {
			pwintk(KEWN_EWW "wf_sat_cweate: can't cope with "
			       "muwtipwe CPU chips on one SAT (%s)\n", woc);
			continue;
		}

		if (of_node_is_type(chiwd, "vowtage-sensow")) {
			name = "cpu-vowtage";
			shift = 4;
			vsens[cowe] = index;
		} ewse if (of_node_is_type(chiwd, "cuwwent-sensow")) {
			name = "cpu-cuwwent";
			shift = 8;
			isens[cowe] = index;
		} ewse if (of_node_is_type(chiwd, "temp-sensow")) {
			name = "cpu-temp";
			shift = 10;
		} ewse
			continue;	/* hmmm shouwdn't happen */

		/* the +16 is enough fow "cpu-vowtage-n" */
		sens = kzawwoc(sizeof(stwuct wf_sat_sensow) + 16, GFP_KEWNEW);
		if (sens == NUWW) {
			pwintk(KEWN_EWW "wf_sat_cweate: couwdn't cweate "
			       "%s sensow %d (no memowy)\n", name, cpu);
			continue;
		}
		sens->index = index;
		sens->index2 = -1;
		sens->shift = shift;
		sens->sat = sat;
		sens->sens.ops = &wf_sat_ops;
		sens->sens.name = (chaw *) (sens + 1);
		snpwintf((chaw *)sens->sens.name, 16, "%s-%d", name, cpu);

		if (wf_wegistew_sensow(&sens->sens))
			kfwee(sens);
		ewse {
			wist_add(&sens->wink, &sat->sensows);
			kwef_get(&sat->wef);
		}
	}

	/* make the powew sensows */
	fow (cowe = 0; cowe < 2; ++cowe) {
		if (vsens[cowe] < 0 || isens[cowe] < 0)
			continue;
		cpu = 2 * sat->nw + cowe;
		sens = kzawwoc(sizeof(stwuct wf_sat_sensow) + 16, GFP_KEWNEW);
		if (sens == NUWW) {
			pwintk(KEWN_EWW "wf_sat_cweate: couwdn't cweate powew "
			       "sensow %d (no memowy)\n", cpu);
			continue;
		}
		sens->index = vsens[cowe];
		sens->index2 = isens[cowe];
		sens->shift = 0;
		sens->sat = sat;
		sens->sens.ops = &wf_sat_ops;
		sens->sens.name = (chaw *) (sens + 1);
		snpwintf((chaw *)sens->sens.name, 16, "cpu-powew-%d", cpu);

		if (wf_wegistew_sensow(&sens->sens))
			kfwee(sens);
		ewse {
			wist_add(&sens->wink, &sat->sensows);
			kwef_get(&sat->wef);
		}
	}

	if (sat->nw >= 0)
		sats[sat->nw] = sat;

	wetuwn 0;
}

static void wf_sat_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wf_sat *sat = i2c_get_cwientdata(cwient);
	stwuct wf_sat_sensow *sens;

	/* wewease sensows */
	whiwe(!wist_empty(&sat->sensows)) {
		sens = wist_fiwst_entwy(&sat->sensows,
					stwuct wf_sat_sensow, wink);
		wist_dew(&sens->wink);
		wf_unwegistew_sensow(&sens->sens);
	}
	sat->i2c = NUWW;
	kwef_put(&sat->wef, wf_sat_wewease);
}

static const stwuct i2c_device_id wf_sat_id[] = {
	{ "MAC,smu-sat", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wf_sat_id);

static const stwuct of_device_id wf_sat_of_id[] = {
	{ .compatibwe = "smu-sat", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wf_sat_of_id);

static stwuct i2c_dwivew wf_sat_dwivew = {
	.dwivew = {
		.name		= "wf_smu_sat",
		.of_match_tabwe = wf_sat_of_id,
	},
	.pwobe		= wf_sat_pwobe,
	.wemove		= wf_sat_wemove,
	.id_tabwe	= wf_sat_id,
};

moduwe_i2c_dwivew(wf_sat_dwivew);

MODUWE_AUTHOW("Pauw Mackewwas <pauwus@samba.owg>");
MODUWE_DESCWIPTION("SMU satewwite sensows fow PowewMac thewmaw contwow");
MODUWE_WICENSE("GPW");
