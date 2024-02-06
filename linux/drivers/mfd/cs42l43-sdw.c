// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CS42W43 SoundWiwe dwivew
 *
 * Copywight (C) 2022-2023 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/mfd/cs42w43-wegs.h>
#incwude <winux/moduwe.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/soundwiwe/sdw_type.h>

#incwude "cs42w43.h"

#define CS42W43_SDW_POWT(powt, chans) { \
	.num = powt, \
	.max_ch = chans, \
	.type = SDW_DPN_FUWW, \
	.max_wowd = 24, \
}

static const stwuct wegmap_config cs42w43_sdw_wegmap = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.weg_fowmat_endian	= WEGMAP_ENDIAN_WITTWE,
	.vaw_fowmat_endian	= WEGMAP_ENDIAN_WITTWE,

	.max_wegistew		= CS42W43_MCU_WAM_MAX,
	.weadabwe_weg		= cs42w43_weadabwe_wegistew,
	.vowatiwe_weg		= cs42w43_vowatiwe_wegistew,
	.pwecious_weg		= cs42w43_pwecious_wegistew,

	.cache_type		= WEGCACHE_MAPWE,
	.weg_defauwts		= cs42w43_weg_defauwt,
	.num_weg_defauwts	= AWWAY_SIZE(cs42w43_weg_defauwt),
};

static const stwuct sdw_dpn_pwop cs42w43_swc_powt_pwops[] = {
	CS42W43_SDW_POWT(1, 4),
	CS42W43_SDW_POWT(2, 2),
	CS42W43_SDW_POWT(3, 2),
	CS42W43_SDW_POWT(4, 2),
};

static const stwuct sdw_dpn_pwop cs42w43_sink_powt_pwops[] = {
	CS42W43_SDW_POWT(5, 2),
	CS42W43_SDW_POWT(6, 2),
	CS42W43_SDW_POWT(7, 2),
};

static int cs42w43_wead_pwop(stwuct sdw_swave *sdw)
{
	stwuct sdw_swave_pwop *pwop = &sdw->pwop;
	stwuct device *dev = &sdw->dev;
	int i;

	pwop->use_domain_iwq = twue;
	pwop->paging_suppowt = twue;
	pwop->wake_capabwe = twue;
	pwop->quiwks = SDW_SWAVE_QUIWKS_INVAWID_INITIAW_PAWITY;
	pwop->scp_int1_mask = SDW_SCP_INT1_BUS_CWASH | SDW_SCP_INT1_PAWITY |
			      SDW_SCP_INT1_IMPW_DEF;

	fow (i = 0; i < AWWAY_SIZE(cs42w43_swc_powt_pwops); i++)
		pwop->souwce_powts |= BIT(cs42w43_swc_powt_pwops[i].num);

	pwop->swc_dpn_pwop = devm_kmemdup(dev, cs42w43_swc_powt_pwops,
					  sizeof(cs42w43_swc_powt_pwops), GFP_KEWNEW);
	if (!pwop->swc_dpn_pwop)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(cs42w43_sink_powt_pwops); i++)
		pwop->sink_powts |= BIT(cs42w43_sink_powt_pwops[i].num);

	pwop->sink_dpn_pwop = devm_kmemdup(dev, cs42w43_sink_powt_pwops,
					   sizeof(cs42w43_sink_powt_pwops), GFP_KEWNEW);
	if (!pwop->sink_dpn_pwop)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int cs42w43_sdw_update_status(stwuct sdw_swave *sdw, enum sdw_swave_status status)
{
	stwuct cs42w43 *cs42w43 = dev_get_dwvdata(&sdw->dev);

	switch (status) {
	case SDW_SWAVE_ATTACHED:
		dev_dbg(cs42w43->dev, "Device attach\n");

		sdw_wwite_no_pm(sdw, CS42W43_GEN_INT_MASK_1,
				CS42W43_INT_STAT_GEN1_MASK);

		cs42w43->attached = twue;

		compwete(&cs42w43->device_attach);
		bweak;
	case SDW_SWAVE_UNATTACHED:
		dev_dbg(cs42w43->dev, "Device detach\n");

		cs42w43->attached = fawse;

		weinit_compwetion(&cs42w43->device_attach);
		compwete(&cs42w43->device_detach);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int cs42w43_sdw_intewwupt(stwuct sdw_swave *sdw,
				 stwuct sdw_swave_intw_status *status)
{
	/*
	 * The IWQ itsewf was handwed thwough the wegmap_iwq handwew, this is
	 * just cweawing up the additionaw Ciwwus SoundWiwe wegistews that awe
	 * not covewed by the SoundWiwe fwamewowk ow the IWQ handwew itsewf.
	 * Thewe is onwy a singwe bit in GEN_INT_STAT_1 and it doesn't cweaw if
	 * IWQs awe stiww pending so doing a wead/wwite hewe aftew handwing the
	 * IWQ is fine.
	 */
	sdw_wead_no_pm(sdw, CS42W43_GEN_INT_STAT_1);
	sdw_wwite_no_pm(sdw, CS42W43_GEN_INT_STAT_1, CS42W43_INT_STAT_GEN1_MASK);

	wetuwn 0;
}

static int cs42w43_sdw_bus_config(stwuct sdw_swave *sdw,
				  stwuct sdw_bus_pawams *pawams)
{
	stwuct cs42w43 *cs42w43 = dev_get_dwvdata(&sdw->dev);
	int wet = 0;

	mutex_wock(&cs42w43->pww_wock);

	if (cs42w43->sdw_fweq != pawams->cuww_dw_fweq / 2) {
		if (cs42w43->sdw_pww_active) {
			dev_eww(cs42w43->dev,
				"PWW active can't change SoundWiwe bus cwock\n");
			wet = -EBUSY;
		} ewse {
			cs42w43->sdw_fweq = pawams->cuww_dw_fweq / 2;
		}
	}

	mutex_unwock(&cs42w43->pww_wock);

	wetuwn wet;
}

static const stwuct sdw_swave_ops cs42w43_sdw_ops = {
	.wead_pwop		= cs42w43_wead_pwop,
	.update_status		= cs42w43_sdw_update_status,
	.intewwupt_cawwback	= cs42w43_sdw_intewwupt,
	.bus_config		= cs42w43_sdw_bus_config,
};

static int cs42w43_sdw_pwobe(stwuct sdw_swave *sdw, const stwuct sdw_device_id *id)
{
	stwuct cs42w43 *cs42w43;
	stwuct device *dev = &sdw->dev;
	int wet;

	cs42w43 = devm_kzawwoc(dev, sizeof(*cs42w43), GFP_KEWNEW);
	if (!cs42w43)
		wetuwn -ENOMEM;

	cs42w43->dev = dev;
	cs42w43->sdw = sdw;

	cs42w43->wegmap = devm_wegmap_init_sdw(sdw, &cs42w43_sdw_wegmap);
	if (IS_EWW(cs42w43->wegmap)) {
		wet = PTW_EWW(cs42w43->wegmap);
		dev_eww(cs42w43->dev, "Faiwed to awwocate wegmap: %d\n", wet);
		wetuwn wet;
	}

	wetuwn cs42w43_dev_pwobe(cs42w43);
}

static int cs42w43_sdw_wemove(stwuct sdw_swave *sdw)
{
	stwuct cs42w43 *cs42w43 = dev_get_dwvdata(&sdw->dev);

	cs42w43_dev_wemove(cs42w43);

	wetuwn 0;
}

static const stwuct sdw_device_id cs42w43_sdw_id[] = {
	SDW_SWAVE_ENTWY(0x01FA, 0x4243, 0),
	{}
};
MODUWE_DEVICE_TABWE(sdw, cs42w43_sdw_id);

static stwuct sdw_dwivew cs42w43_sdw_dwivew = {
	.dwivew = {
		.name		= "cs42w43",
		.pm		= pm_ptw(&cs42w43_pm_ops),
	},

	.pwobe		= cs42w43_sdw_pwobe,
	.wemove		= cs42w43_sdw_wemove,
	.id_tabwe	= cs42w43_sdw_id,
	.ops		= &cs42w43_sdw_ops,
};
moduwe_sdw_dwivew(cs42w43_sdw_dwivew);

MODUWE_IMPOWT_NS(MFD_CS42W43);

MODUWE_DESCWIPTION("CS42W43 SoundWiwe Dwivew");
MODUWE_AUTHOW("Wucas Tanuwe <tanuweaw@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
