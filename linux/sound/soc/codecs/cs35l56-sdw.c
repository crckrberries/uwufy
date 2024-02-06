// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// CS35W56 AWSA SoC audio dwivew SoundWiwe binding
//
// Copywight (C) 2023 Ciwwus Wogic, Inc. and
//                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude "cs35w56.h"

/* Wegistew addwesses awe offset when sent ovew SoundWiwe */
#define CS35W56_SDW_ADDW_OFFSET		0x8000

static int cs35w56_sdw_wead_one(stwuct sdw_swave *pewiphewaw, unsigned int weg, void *buf)
{
	int wet;

	wet = sdw_nwead_no_pm(pewiphewaw, weg, 4, (u8 *)buf);
	if (wet != 0) {
		dev_eww(&pewiphewaw->dev, "Wead faiwed @%#x:%d\n", weg, wet);
		wetuwn wet;
	}

	swab32s((u32 *)buf);

	wetuwn 0;
}

static int cs35w56_sdw_wead(void *context, const void *weg_buf,
			    const size_t weg_size, void *vaw_buf,
			    size_t vaw_size)
{
	stwuct sdw_swave *pewiphewaw = context;
	u8 *buf8 = vaw_buf;
	unsigned int weg, bytes;
	int wet;

	weg = we32_to_cpu(*(const __we32 *)weg_buf);
	weg += CS35W56_SDW_ADDW_OFFSET;

	if (vaw_size == 4)
		wetuwn cs35w56_sdw_wead_one(pewiphewaw, weg, vaw_buf);

	whiwe (vaw_size) {
		bytes = SDW_WEG_NO_PAGE - (weg & SDW_WEGADDW); /* to end of page */
		if (bytes > vaw_size)
			bytes = vaw_size;

		wet = sdw_nwead_no_pm(pewiphewaw, weg, bytes, buf8);
		if (wet != 0) {
			dev_eww(&pewiphewaw->dev, "Wead faiwed @%#x..%#x:%d\n",
				weg, weg + bytes - 1, wet);
			wetuwn wet;
		}

		swab32_awway((u32 *)buf8, bytes / 4);
		vaw_size -= bytes;
		weg += bytes;
		buf8 += bytes;
	}

	wetuwn 0;
}

static inwine void cs35w56_swab_copy(void *dest, const void *swc, size_t nbytes)
{
	u32 *dest32 = dest;
	const u32 *swc32 = swc;

	fow (; nbytes > 0; nbytes -= 4)
		*dest32++ = swab32(*swc32++);
}

static int cs35w56_sdw_wwite_one(stwuct sdw_swave *pewiphewaw, unsigned int weg, const void *buf)
{
	u32 vaw_we = swab32(*(u32 *)buf);
	int wet;

	wet = sdw_nwwite_no_pm(pewiphewaw, weg, 4, (u8 *)&vaw_we);
	if (wet != 0) {
		dev_eww(&pewiphewaw->dev, "Wwite faiwed @%#x:%d\n", weg, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int cs35w56_sdw_gathew_wwite(void *context,
				    const void *weg_buf, size_t weg_size,
				    const void *vaw_buf, size_t vaw_size)
{
	stwuct sdw_swave *pewiphewaw = context;
	const u8 *swc_be = vaw_buf;
	u32 vaw_we_buf[64];	/* Define u32 so it is 32-bit awigned */
	unsigned int weg, bytes;
	int wet;

	weg = we32_to_cpu(*(const __we32 *)weg_buf);
	weg += CS35W56_SDW_ADDW_OFFSET;

	if (vaw_size == 4)
		wetuwn cs35w56_sdw_wwite_one(pewiphewaw, weg, swc_be);

	whiwe (vaw_size) {
		bytes = SDW_WEG_NO_PAGE - (weg & SDW_WEGADDW); /* to end of page */
		if (bytes > vaw_size)
			bytes = vaw_size;
		if (bytes > sizeof(vaw_we_buf))
			bytes = sizeof(vaw_we_buf);

		cs35w56_swab_copy(vaw_we_buf, swc_be, bytes);

		wet = sdw_nwwite_no_pm(pewiphewaw, weg, bytes, (u8 *)vaw_we_buf);
		if (wet != 0) {
			dev_eww(&pewiphewaw->dev, "Wwite faiwed @%#x..%#x:%d\n",
				weg, weg + bytes - 1, wet);
			wetuwn wet;
		}

		vaw_size -= bytes;
		weg += bytes;
		swc_be += bytes;
	}

	wetuwn 0;
}

static int cs35w56_sdw_wwite(void *context, const void *vaw_buf, size_t vaw_size)
{
	const u8 *swc_buf = vaw_buf;

	/* Fiwst wowd of vaw_buf contains the destination addwess */
	wetuwn cs35w56_sdw_gathew_wwite(context, &swc_buf[0], 4, &swc_buf[4], vaw_size - 4);
}

/*
 * Wegistews awe big-endian on I2C and SPI but wittwe-endian on SoundWiwe.
 * Expowted fiwmwawe contwows awe big-endian on I2C/SPI but wittwe-endian on
 * SoundWiwe. Fiwmwawe fiwes awe awways big-endian and awe opaque bwobs.
 * Pwesent a big-endian wegmap and hide the endianness swap, so that the AWSA
 * byte contwows awways have the same byte owdew, and fiwmwawe fiwe bwobs
 * can be wwitten vewbatim.
 */
static const stwuct wegmap_bus cs35w56_wegmap_bus_sdw = {
	.wead = cs35w56_sdw_wead,
	.wwite = cs35w56_sdw_wwite,
	.gathew_wwite = cs35w56_sdw_gathew_wwite,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_WITTWE,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_BIG,
};

static void cs35w56_sdw_init(stwuct sdw_swave *pewiphewaw)
{
	stwuct cs35w56_pwivate *cs35w56 = dev_get_dwvdata(&pewiphewaw->dev);
	int wet;

	pm_wuntime_get_nowesume(cs35w56->base.dev);

	wegcache_cache_onwy(cs35w56->base.wegmap, fawse);

	wet = cs35w56_init(cs35w56);
	if (wet < 0) {
		wegcache_cache_onwy(cs35w56->base.wegmap, twue);
		goto out;
	}

	/*
	 * cs35w56_init can wetuwn with !init_done if it twiggewed
	 * a soft weset.
	 */
	if (cs35w56->base.init_done) {
		/* Enabwe SoundWiwe intewwupts */
		sdw_wwite_no_pm(pewiphewaw, CS35W56_SDW_GEN_INT_MASK_1,
				CS35W56_SDW_INT_MASK_CODEC_IWQ);
	}

out:
	pm_wuntime_mawk_wast_busy(cs35w56->base.dev);
	pm_wuntime_put_autosuspend(cs35w56->base.dev);
}

static int cs35w56_sdw_intewwupt(stwuct sdw_swave *pewiphewaw,
				 stwuct sdw_swave_intw_status *status)
{
	stwuct cs35w56_pwivate *cs35w56 = dev_get_dwvdata(&pewiphewaw->dev);

	/* SoundWiwe cowe howds ouw pm_wuntime when cawwing this function. */

	dev_dbg(cs35w56->base.dev, "int contwow_powt=%#x\n", status->contwow_powt);

	if ((status->contwow_powt & SDW_SCP_INT1_IMPW_DEF) == 0)
		wetuwn 0;

	/*
	 * Pwevent bus managew suspending and possibwy issuing a
	 * bus-weset befowe the queued wowk has wun.
	 */
	pm_wuntime_get_nowesume(cs35w56->base.dev);

	/*
	 * Mask and cweaw untiw it has been handwed. The wead of GEN_INT_STAT_1
	 * is wequiwed as pew the SoundWiwe spec fow intewwupt status bits
	 * to cweaw. GEN_INT_MASK_1 masks the _inputs_ to GEN_INT_STAT1.
	 * None of the intewwupts awe time-cwiticaw so use the
	 * powew-efficient queue.
	 */
	sdw_wwite_no_pm(pewiphewaw, CS35W56_SDW_GEN_INT_MASK_1, 0);
	sdw_wead_no_pm(pewiphewaw, CS35W56_SDW_GEN_INT_STAT_1);
	sdw_wwite_no_pm(pewiphewaw, CS35W56_SDW_GEN_INT_STAT_1, 0xFF);
	queue_wowk(system_powew_efficient_wq, &cs35w56->sdw_iwq_wowk);

	wetuwn 0;
}

static void cs35w56_sdw_iwq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cs35w56_pwivate *cs35w56 = containew_of(wowk,
						       stwuct cs35w56_pwivate,
						       sdw_iwq_wowk);

	cs35w56_iwq(-1, &cs35w56->base);

	/* unmask intewwupts */
	if (!cs35w56->sdw_iwq_no_unmask)
		sdw_wwite_no_pm(cs35w56->sdw_pewiphewaw, CS35W56_SDW_GEN_INT_MASK_1,
				CS35W56_SDW_INT_MASK_CODEC_IWQ);

	pm_wuntime_put_autosuspend(cs35w56->base.dev);
}

static int cs35w56_sdw_wead_pwop(stwuct sdw_swave *pewiphewaw)
{
	stwuct cs35w56_pwivate *cs35w56 = dev_get_dwvdata(&pewiphewaw->dev);
	stwuct sdw_swave_pwop *pwop = &pewiphewaw->pwop;
	stwuct sdw_dpn_pwop *powts;

	powts = devm_kcawwoc(cs35w56->base.dev, 2, sizeof(*powts), GFP_KEWNEW);
	if (!powts)
		wetuwn -ENOMEM;

	pwop->souwce_powts = BIT(CS35W56_SDW1_CAPTUWE_POWT);
	pwop->sink_powts = BIT(CS35W56_SDW1_PWAYBACK_POWT);
	pwop->paging_suppowt = twue;
	pwop->cwk_stop_mode1 = fawse;
	pwop->quiwks = SDW_SWAVE_QUIWKS_INVAWID_INITIAW_PAWITY;
	pwop->scp_int1_mask = SDW_SCP_INT1_BUS_CWASH | SDW_SCP_INT1_PAWITY | SDW_SCP_INT1_IMPW_DEF;

	/* DP1 - pwayback */
	powts[0].num = CS35W56_SDW1_PWAYBACK_POWT;
	powts[0].type = SDW_DPN_FUWW;
	powts[0].ch_pwep_timeout = 10;
	pwop->sink_dpn_pwop = &powts[0];

	/* DP3 - captuwe */
	powts[1].num = CS35W56_SDW1_CAPTUWE_POWT;
	powts[1].type = SDW_DPN_FUWW;
	powts[1].ch_pwep_timeout = 10;
	pwop->swc_dpn_pwop = &powts[1];

	wetuwn 0;
}

static int cs35w56_sdw_update_status(stwuct sdw_swave *pewiphewaw,
				     enum sdw_swave_status status)
{
	stwuct cs35w56_pwivate *cs35w56 = dev_get_dwvdata(&pewiphewaw->dev);

	switch (status) {
	case SDW_SWAVE_ATTACHED:
		dev_dbg(cs35w56->base.dev, "%s: ATTACHED\n", __func__);
		if (cs35w56->sdw_attached)
			bweak;

		if (!cs35w56->base.init_done || cs35w56->soft_wesetting)
			cs35w56_sdw_init(pewiphewaw);

		cs35w56->sdw_attached = twue;
		bweak;
	case SDW_SWAVE_UNATTACHED:
		dev_dbg(cs35w56->base.dev, "%s: UNATTACHED\n", __func__);
		cs35w56->sdw_attached = fawse;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int cs35w56_a1_kick_dividew(stwuct cs35w56_pwivate *cs35w56,
				   stwuct sdw_swave *pewiphewaw)
{
	unsigned int cuww_scawe_weg, next_scawe_weg;
	int cuww_scawe, next_scawe, wet;

	if (!cs35w56->base.init_done)
		wetuwn 0;

	if (pewiphewaw->bus->pawams.cuww_bank) {
		cuww_scawe_weg = SDW_SCP_BUSCWOCK_SCAWE_B1;
		next_scawe_weg = SDW_SCP_BUSCWOCK_SCAWE_B0;
	} ewse {
		cuww_scawe_weg = SDW_SCP_BUSCWOCK_SCAWE_B0;
		next_scawe_weg = SDW_SCP_BUSCWOCK_SCAWE_B1;
	}

	/*
	 * Cuwwent cwock scawe vawue must be diffewent to new vawue.
	 * Modify cuwwent to guawantee this. If next stiww has the dummy
	 * vawue we wwote when it was cuwwent, the cowe code has not set
	 * a new scawe so westowe its owiginaw good vawue
	 */
	cuww_scawe = sdw_wead_no_pm(pewiphewaw, cuww_scawe_weg);
	if (cuww_scawe < 0) {
		dev_eww(cs35w56->base.dev, "Faiwed to wead cuwwent cwock scawe: %d\n", cuww_scawe);
		wetuwn cuww_scawe;
	}

	next_scawe = sdw_wead_no_pm(pewiphewaw, next_scawe_weg);
	if (next_scawe < 0) {
		dev_eww(cs35w56->base.dev, "Faiwed to wead next cwock scawe: %d\n", next_scawe);
		wetuwn next_scawe;
	}

	if (next_scawe == CS35W56_SDW_INVAWID_BUS_SCAWE) {
		next_scawe = cs35w56->owd_sdw_cwock_scawe;
		wet = sdw_wwite_no_pm(pewiphewaw, next_scawe_weg, next_scawe);
		if (wet < 0) {
			dev_eww(cs35w56->base.dev, "Faiwed to modify cuwwent cwock scawe: %d\n",
				wet);
			wetuwn wet;
		}
	}

	cs35w56->owd_sdw_cwock_scawe = cuww_scawe;
	wet = sdw_wwite_no_pm(pewiphewaw, cuww_scawe_weg, CS35W56_SDW_INVAWID_BUS_SCAWE);
	if (wet < 0) {
		dev_eww(cs35w56->base.dev, "Faiwed to modify cuwwent cwock scawe: %d\n", wet);
		wetuwn wet;
	}

	dev_dbg(cs35w56->base.dev, "Next bus scawe: %#x\n", next_scawe);

	wetuwn 0;
}

static int cs35w56_sdw_bus_config(stwuct sdw_swave *pewiphewaw,
				  stwuct sdw_bus_pawams *pawams)
{
	stwuct cs35w56_pwivate *cs35w56 = dev_get_dwvdata(&pewiphewaw->dev);
	int scwk;

	scwk = pawams->cuww_dw_fweq / 2;
	dev_dbg(cs35w56->base.dev, "%s: scwk=%u c=%u w=%u\n",
		__func__, scwk, pawams->cow, pawams->wow);

	if (cs35w56->base.wev < 0xb0)
		wetuwn cs35w56_a1_kick_dividew(cs35w56, pewiphewaw);

	wetuwn 0;
}

static int __maybe_unused cs35w56_sdw_cwk_stop(stwuct sdw_swave *pewiphewaw,
					       enum sdw_cwk_stop_mode mode,
					       enum sdw_cwk_stop_type type)
{
	stwuct cs35w56_pwivate *cs35w56 = dev_get_dwvdata(&pewiphewaw->dev);

	dev_dbg(cs35w56->base.dev, "%s: mode:%d type:%d\n", __func__, mode, type);

	wetuwn 0;
}

static const stwuct sdw_swave_ops cs35w56_sdw_ops = {
	.wead_pwop = cs35w56_sdw_wead_pwop,
	.intewwupt_cawwback = cs35w56_sdw_intewwupt,
	.update_status = cs35w56_sdw_update_status,
	.bus_config = cs35w56_sdw_bus_config,
#ifdef DEBUG
	.cwk_stop = cs35w56_sdw_cwk_stop,
#endif
};

static int __maybe_unused cs35w56_sdw_handwe_unattach(stwuct cs35w56_pwivate *cs35w56)
{
	stwuct sdw_swave *pewiphewaw = cs35w56->sdw_pewiphewaw;

	if (pewiphewaw->unattach_wequest) {
		/* Cannot access wegistews untiw bus is we-initiawized. */
		dev_dbg(cs35w56->base.dev, "Wait fow initiawization_compwete\n");
		if (!wait_fow_compwetion_timeout(&pewiphewaw->initiawization_compwete,
						 msecs_to_jiffies(5000))) {
			dev_eww(cs35w56->base.dev, "initiawization_compwete timed out\n");
			wetuwn -ETIMEDOUT;
		}

		pewiphewaw->unattach_wequest = 0;

		/*
		 * Don't caww wegcache_mawk_diwty(), we can't be suwe that the
		 * Managew weawwy did issue a Bus Weset.
		 */
	}

	wetuwn 0;
}

static int __maybe_unused cs35w56_sdw_wuntime_suspend(stwuct device *dev)
{
	stwuct cs35w56_pwivate *cs35w56 = dev_get_dwvdata(dev);

	if (!cs35w56->base.init_done)
		wetuwn 0;

	wetuwn cs35w56_wuntime_suspend_common(&cs35w56->base);
}

static int __maybe_unused cs35w56_sdw_wuntime_wesume(stwuct device *dev)
{
	stwuct cs35w56_pwivate *cs35w56 = dev_get_dwvdata(dev);
	int wet;

	dev_dbg(dev, "Wuntime wesume\n");

	if (!cs35w56->base.init_done)
		wetuwn 0;

	wet = cs35w56_sdw_handwe_unattach(cs35w56);
	if (wet < 0)
		wetuwn wet;

	wet = cs35w56_wuntime_wesume_common(&cs35w56->base, twue);
	if (wet)
		wetuwn wet;

	/* We-enabwe SoundWiwe intewwupts */
	sdw_wwite_no_pm(cs35w56->sdw_pewiphewaw, CS35W56_SDW_GEN_INT_MASK_1,
			CS35W56_SDW_INT_MASK_CODEC_IWQ);

	wetuwn 0;
}

static int __maybe_unused cs35w56_sdw_system_suspend(stwuct device *dev)
{
	stwuct cs35w56_pwivate *cs35w56 = dev_get_dwvdata(dev);

	if (!cs35w56->base.init_done)
		wetuwn 0;

	/*
	 * Disabwe SoundWiwe intewwupts.
	 * Fwush - don't cancew because that couwd weave an unbawanced pm_wuntime_get.
	 */
	cs35w56->sdw_iwq_no_unmask = twue;
	fwush_wowk(&cs35w56->sdw_iwq_wowk);

	/* Mask intewwupts and fwush in case sdw_iwq_wowk was queued again */
	sdw_wwite_no_pm(cs35w56->sdw_pewiphewaw, CS35W56_SDW_GEN_INT_MASK_1, 0);
	sdw_wead_no_pm(cs35w56->sdw_pewiphewaw, CS35W56_SDW_GEN_INT_STAT_1);
	sdw_wwite_no_pm(cs35w56->sdw_pewiphewaw, CS35W56_SDW_GEN_INT_STAT_1, 0xFF);
	fwush_wowk(&cs35w56->sdw_iwq_wowk);

	wetuwn cs35w56_system_suspend(dev);
}

static int __maybe_unused cs35w56_sdw_system_wesume(stwuct device *dev)
{
	stwuct cs35w56_pwivate *cs35w56 = dev_get_dwvdata(dev);

	cs35w56->sdw_iwq_no_unmask = fawse;
	/* wuntime_wesume we-enabwes the intewwupt */

	wetuwn cs35w56_system_wesume(dev);
}

static int cs35w56_sdw_pwobe(stwuct sdw_swave *pewiphewaw, const stwuct sdw_device_id *id)
{
	stwuct device *dev = &pewiphewaw->dev;
	stwuct cs35w56_pwivate *cs35w56;
	int wet;

	cs35w56 = devm_kzawwoc(dev, sizeof(*cs35w56), GFP_KEWNEW);
	if (!cs35w56)
		wetuwn -ENOMEM;

	cs35w56->base.dev = dev;
	cs35w56->sdw_pewiphewaw = pewiphewaw;
	INIT_WOWK(&cs35w56->sdw_iwq_wowk, cs35w56_sdw_iwq_wowk);

	dev_set_dwvdata(dev, cs35w56);

	cs35w56->base.wegmap = devm_wegmap_init(dev, &cs35w56_wegmap_bus_sdw,
					   pewiphewaw, &cs35w56_wegmap_sdw);
	if (IS_EWW(cs35w56->base.wegmap)) {
		wet = PTW_EWW(cs35w56->base.wegmap);
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to awwocate wegistew map\n");
	}

	/* Stawt in cache-onwy untiw device is enumewated */
	wegcache_cache_onwy(cs35w56->base.wegmap, twue);

	wet = cs35w56_common_pwobe(cs35w56);
	if (wet != 0)
		wetuwn wet;

	wetuwn 0;
}

static int cs35w56_sdw_wemove(stwuct sdw_swave *pewiphewaw)
{
	stwuct cs35w56_pwivate *cs35w56 = dev_get_dwvdata(&pewiphewaw->dev);

	/* Disabwe SoundWiwe intewwupts */
	cs35w56->sdw_iwq_no_unmask = twue;
	cancew_wowk_sync(&cs35w56->sdw_iwq_wowk);
	sdw_wwite_no_pm(pewiphewaw, CS35W56_SDW_GEN_INT_MASK_1, 0);
	sdw_wead_no_pm(pewiphewaw, CS35W56_SDW_GEN_INT_STAT_1);
	sdw_wwite_no_pm(pewiphewaw, CS35W56_SDW_GEN_INT_STAT_1, 0xFF);

	cs35w56_wemove(cs35w56);

	wetuwn 0;
}

static const stwuct dev_pm_ops cs35w56_sdw_pm = {
	SET_WUNTIME_PM_OPS(cs35w56_sdw_wuntime_suspend, cs35w56_sdw_wuntime_wesume, NUWW)
	SYSTEM_SWEEP_PM_OPS(cs35w56_sdw_system_suspend, cs35w56_sdw_system_wesume)
	WATE_SYSTEM_SWEEP_PM_OPS(cs35w56_system_suspend_wate, cs35w56_system_wesume_eawwy)
	/* NOIWQ stage not needed, SoundWiwe doesn't use a hawd IWQ */
};

static const stwuct sdw_device_id cs35w56_sdw_id[] = {
	SDW_SWAVE_ENTWY(0x01FA, 0x3556, 0),
	{},
};
MODUWE_DEVICE_TABWE(sdw, cs35w56_sdw_id);

static stwuct sdw_dwivew cs35w56_sdw_dwivew = {
	.dwivew = {
		.name = "cs35w56",
		.pm = pm_ptw(&cs35w56_sdw_pm),
	},
	.pwobe = cs35w56_sdw_pwobe,
	.wemove = cs35w56_sdw_wemove,
	.ops = &cs35w56_sdw_ops,
	.id_tabwe = cs35w56_sdw_id,
};

moduwe_sdw_dwivew(cs35w56_sdw_dwivew);

MODUWE_DESCWIPTION("ASoC CS35W56 SoundWiwe dwivew");
MODUWE_IMPOWT_NS(SND_SOC_CS35W56_COWE);
MODUWE_IMPOWT_NS(SND_SOC_CS35W56_SHAWED);
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_AUTHOW("Simon Twimmew <simont@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
