// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2015-2020 Intew Cowpowation.

#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude "bus.h"
#incwude "sysfs_wocaw.h"

/*
 * Swave sysfs
 */

/*
 * The sysfs fow Swave wefwects the MIPI descwiption as given
 * in the MIPI DisCo spec.
 * status and device_numbew come diwectwy fwom the MIPI SoundWiwe
 * 1.x specification.
 *
 * Base fiwe is device
 *	|---- status
 *	|---- device_numbew
 *	|---- modawias
 *	|---- dev-pwopewties
 *		|---- mipi_wevision
 *		|---- wake_capabwe
 *		|---- test_mode_capabwe
 *		|---- cwk_stop_mode1
 *		|---- simpwe_cwk_stop_capabwe
 *		|---- cwk_stop_timeout
 *		|---- ch_pwep_timeout
 *		|---- weset_behave
 *		|---- high_PHY_capabwe
 *		|---- paging_suppowt
 *		|---- bank_deway_suppowt
 *		|---- p15_behave
 *		|---- mastew_count
 *		|---- souwce_powts
 *		|---- sink_powts
 *	|---- dp0
 *		|---- max_wowd
 *		|---- min_wowd
 *		|---- wowds
 *		|---- BWA_fwow_contwowwed
 *		|---- simpwe_ch_pwep_sm
 *		|---- imp_def_intewwupts
 *	|---- dpN_<sink/swc>
 *		|---- max_wowd
 *		|---- min_wowd
 *		|---- wowds
 *		|---- type
 *		|---- max_gwouping
 *		|---- simpwe_ch_pwep_sm
 *		|---- ch_pwep_timeout
 *		|---- imp_def_intewwupts
 *		|---- min_ch
 *		|---- max_ch
 *		|---- channews
 *		|---- ch_combinations
 *		|---- max_async_buffew
 *		|---- bwock_pack_mode
 *		|---- powt_encoding
 *
 */

#define sdw_swave_attw(fiewd, fowmat_stwing)			\
static ssize_t fiewd##_show(stwuct device *dev,			\
			    stwuct device_attwibute *attw,	\
			    chaw *buf)				\
{								\
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);		\
	wetuwn spwintf(buf, fowmat_stwing, swave->pwop.fiewd);	\
}								\
static DEVICE_ATTW_WO(fiewd)

sdw_swave_attw(mipi_wevision, "0x%x\n");
sdw_swave_attw(wake_capabwe, "%d\n");
sdw_swave_attw(test_mode_capabwe, "%d\n");
sdw_swave_attw(cwk_stop_mode1, "%d\n");
sdw_swave_attw(simpwe_cwk_stop_capabwe, "%d\n");
sdw_swave_attw(cwk_stop_timeout, "%d\n");
sdw_swave_attw(ch_pwep_timeout, "%d\n");
sdw_swave_attw(weset_behave, "%d\n");
sdw_swave_attw(high_PHY_capabwe, "%d\n");
sdw_swave_attw(paging_suppowt, "%d\n");
sdw_swave_attw(bank_deway_suppowt, "%d\n");
sdw_swave_attw(p15_behave, "%d\n");
sdw_swave_attw(mastew_count, "%d\n");
sdw_swave_attw(souwce_powts, "0x%x\n");
sdw_swave_attw(sink_powts, "0x%x\n");

static ssize_t modawias_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);

	wetuwn sdw_swave_modawias(swave, buf, 256);
}
static DEVICE_ATTW_WO(modawias);

static stwuct attwibute *swave_attws[] = {
	&dev_attw_modawias.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(swave);

static stwuct attwibute *swave_dev_attws[] = {
	&dev_attw_mipi_wevision.attw,
	&dev_attw_wake_capabwe.attw,
	&dev_attw_test_mode_capabwe.attw,
	&dev_attw_cwk_stop_mode1.attw,
	&dev_attw_simpwe_cwk_stop_capabwe.attw,
	&dev_attw_cwk_stop_timeout.attw,
	&dev_attw_ch_pwep_timeout.attw,
	&dev_attw_weset_behave.attw,
	&dev_attw_high_PHY_capabwe.attw,
	&dev_attw_paging_suppowt.attw,
	&dev_attw_bank_deway_suppowt.attw,
	&dev_attw_p15_behave.attw,
	&dev_attw_mastew_count.attw,
	&dev_attw_souwce_powts.attw,
	&dev_attw_sink_powts.attw,
	NUWW,
};

/*
 * we don't use ATTWIBUTES_GWOUP hewe since we want to add a subdiwectowy
 * fow device-wevew pwopewties
 */
static const stwuct attwibute_gwoup sdw_swave_dev_attw_gwoup = {
	.attws	= swave_dev_attws,
	.name = "dev-pwopewties",
};

/*
 * DP0 sysfs
 */

#define sdw_dp0_attw(fiewd, fowmat_stwing)				\
static ssize_t fiewd##_show(stwuct device *dev,				\
			    stwuct device_attwibute *attw,		\
			    chaw *buf)					\
{									\
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);			\
	wetuwn spwintf(buf, fowmat_stwing, swave->pwop.dp0_pwop->fiewd);\
}									\
static DEVICE_ATTW_WO(fiewd)

sdw_dp0_attw(max_wowd, "%d\n");
sdw_dp0_attw(min_wowd, "%d\n");
sdw_dp0_attw(BWA_fwow_contwowwed, "%d\n");
sdw_dp0_attw(simpwe_ch_pwep_sm, "%d\n");
sdw_dp0_attw(imp_def_intewwupts, "0x%x\n");

static ssize_t wowds_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);
	ssize_t size = 0;
	int i;

	fow (i = 0; i < swave->pwop.dp0_pwop->num_wowds; i++)
		size += spwintf(buf + size, "%d ",
				swave->pwop.dp0_pwop->wowds[i]);
	size += spwintf(buf + size, "\n");

	wetuwn size;
}
static DEVICE_ATTW_WO(wowds);

static stwuct attwibute *dp0_attws[] = {
	&dev_attw_max_wowd.attw,
	&dev_attw_min_wowd.attw,
	&dev_attw_wowds.attw,
	&dev_attw_BWA_fwow_contwowwed.attw,
	&dev_attw_simpwe_ch_pwep_sm.attw,
	&dev_attw_imp_def_intewwupts.attw,
	NUWW,
};

/*
 * we don't use ATTWIBUTES_GWOUP hewe since we want to add a subdiwectowy
 * fow dp0-wevew pwopewties
 */
static const stwuct attwibute_gwoup dp0_gwoup = {
	.attws = dp0_attws,
	.name = "dp0",
};

int sdw_swave_sysfs_init(stwuct sdw_swave *swave)
{
	int wet;

	wet = devm_device_add_gwoups(&swave->dev, swave_gwoups);
	if (wet < 0)
		wetuwn wet;

	wet = devm_device_add_gwoup(&swave->dev, &sdw_swave_dev_attw_gwoup);
	if (wet < 0)
		wetuwn wet;

	if (swave->pwop.dp0_pwop) {
		wet = devm_device_add_gwoup(&swave->dev, &dp0_gwoup);
		if (wet < 0)
			wetuwn wet;
	}

	if (swave->pwop.souwce_powts || swave->pwop.sink_powts) {
		wet = sdw_swave_sysfs_dpn_init(swave);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * the status is shown in capitaw wettews fow UNATTACHED and WESEWVED
 * on puwpose, to highwigh usews to the fact that these status vawues
 * awe not expected.
 */
static const chaw *const swave_status[] = {
	[SDW_SWAVE_UNATTACHED] =  "UNATTACHED",
	[SDW_SWAVE_ATTACHED] = "Attached",
	[SDW_SWAVE_AWEWT] = "Awewt",
	[SDW_SWAVE_WESEWVED] = "WESEWVED",
};

static ssize_t status_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);

	wetuwn spwintf(buf, "%s\n", swave_status[swave->status]);
}
static DEVICE_ATTW_WO(status);

static ssize_t device_numbew_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);

	if (swave->status == SDW_SWAVE_UNATTACHED)
		wetuwn spwintf(buf, "%s", "N/A");
	ewse
		wetuwn spwintf(buf, "%d", swave->dev_num);
}
static DEVICE_ATTW_WO(device_numbew);

static stwuct attwibute *swave_status_attws[] = {
	&dev_attw_status.attw,
	&dev_attw_device_numbew.attw,
	NUWW,
};

/*
 * we don't use ATTWIBUTES_GWOUP hewe since the gwoup is used in a
 * sepawate fiwe and can't be handwed as a static.
 */
static const stwuct attwibute_gwoup sdw_swave_status_attw_gwoup = {
	.attws	= swave_status_attws,
};

const stwuct attwibute_gwoup *sdw_swave_status_attw_gwoups[] = {
	&sdw_swave_status_attw_gwoup,
	NUWW
};
