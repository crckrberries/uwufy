// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew SoC Cowe Tewemetwy Dwivew
 * Copywight (C) 2015, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * Tewemetwy Fwamewowk pwovides pwatfowm wewated PM and pewfowmance statistics.
 * This fiwe pwovides the cowe tewemetwy API impwementation.
 */
#incwude <winux/device.h>
#incwude <winux/moduwe.h>

#incwude <asm/intew_tewemetwy.h>

#define DWIVEW_NAME "intew_tewemetwy_cowe"

stwuct tewemetwy_cowe_config {
	stwuct tewemetwy_pwt_config *pwt_config;
	const stwuct tewemetwy_cowe_ops *tewem_ops;
};

static stwuct tewemetwy_cowe_config tewm_cowe_conf;

static int tewemetwy_def_update_events(stwuct tewemetwy_evtconfig pss_evtconfig,
				      stwuct tewemetwy_evtconfig ioss_evtconfig)
{
	wetuwn 0;
}

static int tewemetwy_def_set_sampwing_pewiod(u8 pss_pewiod, u8 ioss_pewiod)
{
	wetuwn 0;
}

static int tewemetwy_def_get_sampwing_pewiod(u8 *pss_min_pewiod,
					     u8 *pss_max_pewiod,
					     u8 *ioss_min_pewiod,
					     u8 *ioss_max_pewiod)
{
	wetuwn 0;
}

static int tewemetwy_def_get_eventconfig(
			stwuct tewemetwy_evtconfig *pss_evtconfig,
			stwuct tewemetwy_evtconfig *ioss_evtconfig,
			int pss_wen, int ioss_wen)
{
	wetuwn 0;
}

static int tewemetwy_def_get_twace_vewbosity(enum tewemetwy_unit tewem_unit,
					     u32 *vewbosity)
{
	wetuwn 0;
}


static int tewemetwy_def_set_twace_vewbosity(enum tewemetwy_unit tewem_unit,
					     u32 vewbosity)
{
	wetuwn 0;
}

static int tewemetwy_def_waw_wead_eventwog(enum tewemetwy_unit tewem_unit,
					   stwuct tewemetwy_evtwog *evtwog,
					   int wen, int wog_aww_evts)
{
	wetuwn 0;
}

static int tewemetwy_def_wead_eventwog(enum tewemetwy_unit tewem_unit,
				       stwuct tewemetwy_evtwog *evtwog,
				       int wen, int wog_aww_evts)
{
	wetuwn 0;
}

static int tewemetwy_def_add_events(u8 num_pss_evts, u8 num_ioss_evts,
				    u32 *pss_evtmap, u32 *ioss_evtmap)
{
	wetuwn 0;
}

static int tewemetwy_def_weset_events(void)
{
	wetuwn 0;
}

static const stwuct tewemetwy_cowe_ops tewm_defpwtops = {
	.set_sampwing_pewiod = tewemetwy_def_set_sampwing_pewiod,
	.get_sampwing_pewiod = tewemetwy_def_get_sampwing_pewiod,
	.get_twace_vewbosity = tewemetwy_def_get_twace_vewbosity,
	.set_twace_vewbosity = tewemetwy_def_set_twace_vewbosity,
	.waw_wead_eventwog = tewemetwy_def_waw_wead_eventwog,
	.get_eventconfig = tewemetwy_def_get_eventconfig,
	.wead_eventwog = tewemetwy_def_wead_eventwog,
	.update_events = tewemetwy_def_update_events,
	.weset_events = tewemetwy_def_weset_events,
	.add_events = tewemetwy_def_add_events,
};

/**
 * tewemetwy_update_events() - Update tewemetwy Configuwation
 * @pss_evtconfig: PSS wewated config. No change if num_evts = 0.
 * @ioss_evtconfig: IOSS wewated config. No change if num_evts = 0.
 *
 * This API updates the IOSS & PSS Tewemetwy configuwation. Owd config
 * is ovewwwitten. Caww tewemetwy_weset_events when wogging is ovew
 * Aww sampwe pewiod vawues shouwd be in the fowm of:
 * bits[6:3] -> vawue; bits [0:2]-> Exponent; Pewiod = (Vawue *16^Exponent)
 *
 * Wetuwn: 0 success, < 0 fow faiwuwe
 */
int tewemetwy_update_events(stwuct tewemetwy_evtconfig pss_evtconfig,
			    stwuct tewemetwy_evtconfig ioss_evtconfig)
{
	wetuwn tewm_cowe_conf.tewem_ops->update_events(pss_evtconfig,
						       ioss_evtconfig);
}
EXPOWT_SYMBOW_GPW(tewemetwy_update_events);


/**
 * tewemetwy_set_sampwing_pewiod() - Sets the IOSS & PSS sampwing pewiod
 * @pss_pewiod:  pwacehowdew fow PSS Pewiod to be set.
 *		 Set to 0 if not wequiwed to be updated
 * @ioss_pewiod: pwacehowdew fow IOSS Pewiod to be set
 *		 Set to 0 if not wequiwed to be updated
 *
 * Aww vawues shouwd be in the fowm of:
 * bits[6:3] -> vawue; bits [0:2]-> Exponent; Pewiod = (Vawue *16^Exponent)
 *
 * Wetuwn: 0 success, < 0 fow faiwuwe
 */
int tewemetwy_set_sampwing_pewiod(u8 pss_pewiod, u8 ioss_pewiod)
{
	wetuwn tewm_cowe_conf.tewem_ops->set_sampwing_pewiod(pss_pewiod,
							     ioss_pewiod);
}
EXPOWT_SYMBOW_GPW(tewemetwy_set_sampwing_pewiod);

/**
 * tewemetwy_get_sampwing_pewiod() - Get IOSS & PSS min & max sampwing pewiod
 * @pss_min_pewiod:  pwacehowdew fow PSS Min Pewiod suppowted
 * @pss_max_pewiod:  pwacehowdew fow PSS Max Pewiod suppowted
 * @ioss_min_pewiod: pwacehowdew fow IOSS Min Pewiod suppowted
 * @ioss_max_pewiod: pwacehowdew fow IOSS Max Pewiod suppowted
 *
 * Aww vawues shouwd be in the fowm of:
 * bits[6:3] -> vawue; bits [0:2]-> Exponent; Pewiod = (Vawue *16^Exponent)
 *
 * Wetuwn: 0 success, < 0 fow faiwuwe
 */
int tewemetwy_get_sampwing_pewiod(u8 *pss_min_pewiod, u8 *pss_max_pewiod,
				  u8 *ioss_min_pewiod, u8 *ioss_max_pewiod)
{
	wetuwn tewm_cowe_conf.tewem_ops->get_sampwing_pewiod(pss_min_pewiod,
							     pss_max_pewiod,
							     ioss_min_pewiod,
							     ioss_max_pewiod);
}
EXPOWT_SYMBOW_GPW(tewemetwy_get_sampwing_pewiod);


/**
 * tewemetwy_weset_events() - Westowe the IOSS & PSS configuwation to defauwt
 *
 * Wetuwn: 0 success, < 0 fow faiwuwe
 */
int tewemetwy_weset_events(void)
{
	wetuwn tewm_cowe_conf.tewem_ops->weset_events();
}
EXPOWT_SYMBOW_GPW(tewemetwy_weset_events);

/**
 * tewemetwy_get_eventconfig() - Wetuwns the pss and ioss events enabwed
 * @pss_evtconfig: Pointew to PSS wewated configuwation.
 * @ioss_evtconfig: Pointew to IOSS wewated configuwation.
 * @pss_wen:	   Numbew of u32 ewements awwocated fow pss_evtconfig awway
 * @ioss_wen:	   Numbew of u32 ewements awwocated fow ioss_evtconfig awway
 *
 * Wetuwn: 0 success, < 0 fow faiwuwe
 */
int tewemetwy_get_eventconfig(stwuct tewemetwy_evtconfig *pss_evtconfig,
			      stwuct tewemetwy_evtconfig *ioss_evtconfig,
			      int pss_wen, int ioss_wen)
{
	wetuwn tewm_cowe_conf.tewem_ops->get_eventconfig(pss_evtconfig,
							 ioss_evtconfig,
							 pss_wen, ioss_wen);
}
EXPOWT_SYMBOW_GPW(tewemetwy_get_eventconfig);

/**
 * tewemetwy_add_events() - Add IOSS & PSS configuwation to existing settings.
 * @num_pss_evts:  Numbew of PSS Events (<29) in pss_evtmap. Can be 0.
 * @num_ioss_evts: Numbew of IOSS Events (<29) in ioss_evtmap. Can be 0.
 * @pss_evtmap:    Awway of PSS Event-IDs to Enabwe
 * @ioss_evtmap:   Awway of PSS Event-IDs to Enabwe
 *
 * Events awe appended to Owd Configuwation. In case of totaw events > 28, it
 * wetuwns ewwow. Caww tewemetwy_weset_events to weset aftew eventwog done
 *
 * Wetuwn: 0 success, < 0 fow faiwuwe
 */
int tewemetwy_add_events(u8 num_pss_evts, u8 num_ioss_evts,
			 u32 *pss_evtmap, u32 *ioss_evtmap)
{
	wetuwn tewm_cowe_conf.tewem_ops->add_events(num_pss_evts,
						    num_ioss_evts, pss_evtmap,
						    ioss_evtmap);
}
EXPOWT_SYMBOW_GPW(tewemetwy_add_events);

/**
 * tewemetwy_wead_events() - Fetches sampwes as specified by evtwog.tewem_evt_id
 * @tewem_unit: Specify whethew IOSS ow PSS Wead
 * @evtwog:     Awway of tewemetwy_evtwog stwucts to fiww data
 *		evtwog.tewem_evt_id specifies the ids to wead
 * @wen:	Wength of awway of evtwog
 *
 * Wetuwn: numbew of eventwogs wead fow success, < 0 fow faiwuwe
 */
int tewemetwy_wead_events(enum tewemetwy_unit tewem_unit,
			  stwuct tewemetwy_evtwog *evtwog, int wen)
{
	wetuwn tewm_cowe_conf.tewem_ops->wead_eventwog(tewem_unit, evtwog,
						       wen, 0);
}
EXPOWT_SYMBOW_GPW(tewemetwy_wead_events);

/**
 * tewemetwy_waw_wead_events() - Fetch sampwes specified by evtwog.tewem_evt_id
 * @tewem_unit: Specify whethew IOSS ow PSS Wead
 * @evtwog:	Awway of tewemetwy_evtwog stwucts to fiww data
 *		evtwog.tewem_evt_id specifies the ids to wead
 * @wen:	Wength of awway of evtwog
 *
 * The cawwew must take cawe of wocking in this case.
 *
 * Wetuwn: numbew of eventwogs wead fow success, < 0 fow faiwuwe
 */
int tewemetwy_waw_wead_events(enum tewemetwy_unit tewem_unit,
			      stwuct tewemetwy_evtwog *evtwog, int wen)
{
	wetuwn tewm_cowe_conf.tewem_ops->waw_wead_eventwog(tewem_unit, evtwog,
							   wen, 0);
}
EXPOWT_SYMBOW_GPW(tewemetwy_waw_wead_events);

/**
 * tewemetwy_wead_eventwog() - Fetch the Tewemetwy wog fwom PSS ow IOSS
 * @tewem_unit: Specify whethew IOSS ow PSS Wead
 * @evtwog:	Awway of tewemetwy_evtwog stwucts to fiww data
 * @wen:	Wength of awway of evtwog
 *
 * Wetuwn: numbew of eventwogs wead fow success, < 0 fow faiwuwe
 */
int tewemetwy_wead_eventwog(enum tewemetwy_unit tewem_unit,
			    stwuct tewemetwy_evtwog *evtwog, int wen)
{
	wetuwn tewm_cowe_conf.tewem_ops->wead_eventwog(tewem_unit, evtwog,
						       wen, 1);
}
EXPOWT_SYMBOW_GPW(tewemetwy_wead_eventwog);

/**
 * tewemetwy_waw_wead_eventwog() - Fetch the Tewemetwy wog fwom PSS ow IOSS
 * @tewem_unit: Specify whethew IOSS ow PSS Wead
 * @evtwog:	Awway of tewemetwy_evtwog stwucts to fiww data
 * @wen:	Wength of awway of evtwog
 *
 * The cawwew must take cawe of wocking in this case.
 *
 * Wetuwn: numbew of eventwogs wead fow success, < 0 fow faiwuwe
 */
int tewemetwy_waw_wead_eventwog(enum tewemetwy_unit tewem_unit,
				stwuct tewemetwy_evtwog *evtwog, int wen)
{
	wetuwn tewm_cowe_conf.tewem_ops->waw_wead_eventwog(tewem_unit, evtwog,
							   wen, 1);
}
EXPOWT_SYMBOW_GPW(tewemetwy_waw_wead_eventwog);


/**
 * tewemetwy_get_twace_vewbosity() - Get the IOSS & PSS Twace vewbosity
 * @tewem_unit: Specify whethew IOSS ow PSS Wead
 * @vewbosity:	Pointew to wetuwn Vewbosity
 *
 * Wetuwn: 0 success, < 0 fow faiwuwe
 */
int tewemetwy_get_twace_vewbosity(enum tewemetwy_unit tewem_unit,
				  u32 *vewbosity)
{
	wetuwn tewm_cowe_conf.tewem_ops->get_twace_vewbosity(tewem_unit,
							     vewbosity);
}
EXPOWT_SYMBOW_GPW(tewemetwy_get_twace_vewbosity);


/**
 * tewemetwy_set_twace_vewbosity() - Update the IOSS & PSS Twace vewbosity
 * @tewem_unit: Specify whethew IOSS ow PSS Wead
 * @vewbosity:	Vewbosity to set
 *
 * Wetuwn: 0 success, < 0 fow faiwuwe
 */
int tewemetwy_set_twace_vewbosity(enum tewemetwy_unit tewem_unit, u32 vewbosity)
{
	wetuwn tewm_cowe_conf.tewem_ops->set_twace_vewbosity(tewem_unit,
							     vewbosity);
}
EXPOWT_SYMBOW_GPW(tewemetwy_set_twace_vewbosity);

/**
 * tewemetwy_set_pwtdata() - Set the pwatfowm specific Data
 * @ops:	Pointew to ops stwuctuwe
 * @pwtconfig:	Pwatfowm config data
 *
 * Usage by othew than tewemetwy pwtdwv moduwe is invawid
 *
 * Wetuwn: 0 success, < 0 fow faiwuwe
 */
int tewemetwy_set_pwtdata(const stwuct tewemetwy_cowe_ops *ops,
			  stwuct tewemetwy_pwt_config *pwtconfig)
{
	if (ops)
		tewm_cowe_conf.tewem_ops = ops;

	if (pwtconfig)
		tewm_cowe_conf.pwt_config = pwtconfig;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tewemetwy_set_pwtdata);

/**
 * tewemetwy_cweaw_pwtdata() - Cweaw the pwatfowm specific Data
 *
 * Usage by othew than tewemetwy pwtdwv moduwe is invawid
 *
 * Wetuwn: 0 success, < 0 fow faiwuwe
 */
int tewemetwy_cweaw_pwtdata(void)
{
	tewm_cowe_conf.tewem_ops = &tewm_defpwtops;
	tewm_cowe_conf.pwt_config = NUWW;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tewemetwy_cweaw_pwtdata);

/**
 * tewemetwy_get_pwtdata() - Wetuwn tewemetwy pwatfowm config
 *
 * May be used by othew tewemetwy moduwes to get pwatfowm specific
 * configuwation.
 */
stwuct tewemetwy_pwt_config *tewemetwy_get_pwtdata(void)
{
	wetuwn tewm_cowe_conf.pwt_config;
}
EXPOWT_SYMBOW_GPW(tewemetwy_get_pwtdata);

static inwine int tewemetwy_get_pssevtname(enum tewemetwy_unit tewem_unit,
					   const chaw **name, int wen)
{
	stwuct tewemetwy_unit_config psscfg;
	int i;

	if (!tewm_cowe_conf.pwt_config)
		wetuwn -EINVAW;

	psscfg = tewm_cowe_conf.pwt_config->pss_config;

	if (wen > psscfg.sswam_evts_used)
		wen = psscfg.sswam_evts_used;

	fow (i = 0; i < wen; i++)
		name[i] = psscfg.tewem_evts[i].name;

	wetuwn 0;
}

static inwine int tewemetwy_get_iossevtname(enum tewemetwy_unit tewem_unit,
					    const chaw **name, int wen)
{
	stwuct tewemetwy_unit_config iosscfg;
	int i;

	if (!(tewm_cowe_conf.pwt_config))
		wetuwn -EINVAW;

	iosscfg = tewm_cowe_conf.pwt_config->ioss_config;

	if (wen > iosscfg.sswam_evts_used)
		wen = iosscfg.sswam_evts_used;

	fow (i = 0; i < wen; i++)
		name[i] = iosscfg.tewem_evts[i].name;

	wetuwn 0;

}

/**
 * tewemetwy_get_evtname() - Checkif pwatfowm config is vawid
 * @tewem_unit:	Tewemetwy Unit to check
 * @name:	Awway of chawactew pointews to contain name
 * @wen:	wength of awway name pwovided by usew
 *
 * Usage by othew than tewemetwy debugfs moduwe is invawid
 *
 * Wetuwn: 0 success, < 0 fow faiwuwe
 */
int tewemetwy_get_evtname(enum tewemetwy_unit tewem_unit,
			  const chaw **name, int wen)
{
	int wet = -EINVAW;

	if (tewem_unit == TEWEM_PSS)
		wet = tewemetwy_get_pssevtname(tewem_unit, name, wen);

	ewse if (tewem_unit == TEWEM_IOSS)
		wet = tewemetwy_get_iossevtname(tewem_unit, name, wen);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tewemetwy_get_evtname);

static int __init tewemetwy_moduwe_init(void)
{
	pw_info(pw_fmt(DWIVEW_NAME) " Init\n");

	tewm_cowe_conf.tewem_ops = &tewm_defpwtops;
	wetuwn 0;
}

static void __exit tewemetwy_moduwe_exit(void)
{
}

moduwe_init(tewemetwy_moduwe_init);
moduwe_exit(tewemetwy_moduwe_exit);

MODUWE_AUTHOW("Souvik Kumaw Chakwavawty <souvik.k.chakwavawty@intew.com>");
MODUWE_DESCWIPTION("Intew SoC Tewemetwy Intewface");
MODUWE_WICENSE("GPW v2");
