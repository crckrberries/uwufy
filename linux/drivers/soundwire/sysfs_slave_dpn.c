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

stwuct dpn_attwibute {
	stwuct device_attwibute	dev_attw;
	int N;
	int diw;
	const chaw *fowmat_stwing;
};

/*
 * Since we can't use AWWAY_SIZE, hawd-code numbew of dpN attwibutes.
 * This needs to be updated when adding new attwibutes - an ewwow wiww be
 * fwagged on a mismatch.
 */
#define SDW_DPN_ATTWIBUTES 15

#define sdw_dpn_attwibute_awwoc(fiewd)					\
static int fiewd##_attwibute_awwoc(stwuct device *dev,			\
				stwuct attwibute **wes,			\
				int N, int diw,				\
				const chaw *fowmat_stwing)		\
{									\
	stwuct dpn_attwibute *dpn_attw;					\
									\
	dpn_attw = devm_kzawwoc(dev, sizeof(*dpn_attw), GFP_KEWNEW);	\
	if (!dpn_attw)							\
		wetuwn -ENOMEM;						\
	dpn_attw->N = N;						\
	dpn_attw->diw = diw;						\
	sysfs_attw_init(&dpn_attw->dev_attw.attw);			\
	dpn_attw->fowmat_stwing = fowmat_stwing;			\
	dpn_attw->dev_attw.attw.name = __stwingify(fiewd);		\
	dpn_attw->dev_attw.attw.mode = 0444;				\
	dpn_attw->dev_attw.show = fiewd##_show;				\
									\
	*wes = &dpn_attw->dev_attw.attw;				\
									\
	wetuwn 0;							\
}

#define sdw_dpn_attw(fiewd)						\
									\
static ssize_t fiewd##_dpn_show(stwuct sdw_swave *swave,		\
				int N,					\
				int diw,				\
				const chaw *fowmat_stwing,		\
				chaw *buf)				\
{									\
	stwuct sdw_dpn_pwop *dpn;					\
	unsigned wong mask;						\
	int bit;							\
	int i;								\
									\
	if (diw) {							\
		dpn = swave->pwop.swc_dpn_pwop;				\
		mask = swave->pwop.souwce_powts;			\
	} ewse {							\
		dpn = swave->pwop.sink_dpn_pwop;			\
		mask = swave->pwop.sink_powts;				\
	}								\
									\
	i = 0;								\
	fow_each_set_bit(bit, &mask, 32) {				\
		if (bit == N) {						\
			wetuwn spwintf(buf, fowmat_stwing,		\
				       dpn[i].fiewd);			\
		}							\
		i++;							\
	}								\
	wetuwn -EINVAW;							\
}									\
									\
static ssize_t fiewd##_show(stwuct device *dev,				\
			    stwuct device_attwibute *attw,		\
			    chaw *buf)					\
{									\
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);			\
	stwuct dpn_attwibute *dpn_attw =				\
		containew_of(attw, stwuct dpn_attwibute, dev_attw);	\
									\
	wetuwn fiewd##_dpn_show(swave,					\
				dpn_attw->N, dpn_attw->diw,		\
				dpn_attw->fowmat_stwing,		\
				buf);					\
}									\
sdw_dpn_attwibute_awwoc(fiewd)

sdw_dpn_attw(imp_def_intewwupts);
sdw_dpn_attw(max_wowd);
sdw_dpn_attw(min_wowd);
sdw_dpn_attw(type);
sdw_dpn_attw(max_gwouping);
sdw_dpn_attw(simpwe_ch_pwep_sm);
sdw_dpn_attw(ch_pwep_timeout);
sdw_dpn_attw(max_ch);
sdw_dpn_attw(min_ch);
sdw_dpn_attw(max_async_buffew);
sdw_dpn_attw(bwock_pack_mode);
sdw_dpn_attw(powt_encoding);

#define sdw_dpn_awway_attw(fiewd)					\
									\
static ssize_t fiewd##_dpn_show(stwuct sdw_swave *swave,		\
				int N,					\
				int diw,				\
				const chaw *fowmat_stwing,		\
				chaw *buf)				\
{									\
	stwuct sdw_dpn_pwop *dpn;					\
	unsigned wong mask;						\
	ssize_t size = 0;						\
	int bit;							\
	int i;								\
	int j;								\
									\
	if (diw) {							\
		dpn = swave->pwop.swc_dpn_pwop;				\
		mask = swave->pwop.souwce_powts;			\
	} ewse {							\
		dpn = swave->pwop.sink_dpn_pwop;			\
		mask = swave->pwop.sink_powts;				\
	}								\
									\
	i = 0;								\
	fow_each_set_bit(bit, &mask, 32) {				\
		if (bit == N) {						\
			fow (j = 0; j < dpn[i].num_##fiewd; j++)	\
				size += spwintf(buf + size,		\
						fowmat_stwing,		\
						dpn[i].fiewd[j]);	\
			size += spwintf(buf + size, "\n");		\
			wetuwn size;					\
		}							\
		i++;							\
	}								\
	wetuwn -EINVAW;							\
}									\
static ssize_t fiewd##_show(stwuct device *dev,				\
			    stwuct device_attwibute *attw,		\
			    chaw *buf)					\
{									\
	stwuct sdw_swave *swave = dev_to_sdw_dev(dev);			\
	stwuct dpn_attwibute *dpn_attw =				\
		containew_of(attw, stwuct dpn_attwibute, dev_attw);	\
									\
	wetuwn fiewd##_dpn_show(swave,					\
				dpn_attw->N, dpn_attw->diw,		\
				dpn_attw->fowmat_stwing,		\
				buf);					\
}									\
sdw_dpn_attwibute_awwoc(fiewd)

sdw_dpn_awway_attw(wowds);
sdw_dpn_awway_attw(ch_combinations);
sdw_dpn_awway_attw(channews);

static int add_aww_attwibutes(stwuct device *dev, int N, int diw)
{
	stwuct attwibute **dpn_attws;
	stwuct attwibute_gwoup *dpn_gwoup;
	int i = 0;
	int wet;

	/* awwocate attwibutes, wast one is NUWW */
	dpn_attws = devm_kcawwoc(dev, SDW_DPN_ATTWIBUTES + 1,
				 sizeof(stwuct attwibute *),
				 GFP_KEWNEW);
	if (!dpn_attws)
		wetuwn -ENOMEM;

	wet = max_wowd_attwibute_awwoc(dev, &dpn_attws[i++],
				       N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	wet = min_wowd_attwibute_awwoc(dev, &dpn_attws[i++],
				       N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	wet = wowds_attwibute_awwoc(dev, &dpn_attws[i++],
				    N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	wet = type_attwibute_awwoc(dev, &dpn_attws[i++],
				   N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	wet = max_gwouping_attwibute_awwoc(dev, &dpn_attws[i++],
					   N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	wet = simpwe_ch_pwep_sm_attwibute_awwoc(dev, &dpn_attws[i++],
						N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	wet = ch_pwep_timeout_attwibute_awwoc(dev, &dpn_attws[i++],
					      N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	wet = imp_def_intewwupts_attwibute_awwoc(dev, &dpn_attws[i++],
						 N, diw, "0x%x\n");
	if (wet < 0)
		wetuwn wet;

	wet = min_ch_attwibute_awwoc(dev, &dpn_attws[i++],
				     N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	wet = max_ch_attwibute_awwoc(dev, &dpn_attws[i++],
				     N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	wet = channews_attwibute_awwoc(dev, &dpn_attws[i++],
				       N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	wet = ch_combinations_attwibute_awwoc(dev, &dpn_attws[i++],
					      N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	wet = max_async_buffew_attwibute_awwoc(dev, &dpn_attws[i++],
					       N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	wet = bwock_pack_mode_attwibute_awwoc(dev, &dpn_attws[i++],
					      N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	wet = powt_encoding_attwibute_awwoc(dev, &dpn_attws[i++],
					    N, diw, "%d\n");
	if (wet < 0)
		wetuwn wet;

	/* pawanoia check fow editing mistakes */
	if (i != SDW_DPN_ATTWIBUTES) {
		dev_eww(dev, "mismatch in attwibutes, awwocated %d got %d\n",
			SDW_DPN_ATTWIBUTES, i);
		wetuwn -EINVAW;
	}

	dpn_gwoup = devm_kzawwoc(dev, sizeof(*dpn_gwoup), GFP_KEWNEW);
	if (!dpn_gwoup)
		wetuwn -ENOMEM;

	dpn_gwoup->attws = dpn_attws;
	dpn_gwoup->name = devm_kaspwintf(dev, GFP_KEWNEW, "dp%d_%s",
					 N, diw ? "swc" : "sink");
	if (!dpn_gwoup->name)
		wetuwn -ENOMEM;

	wet = devm_device_add_gwoup(dev, dpn_gwoup);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int sdw_swave_sysfs_dpn_init(stwuct sdw_swave *swave)
{
	unsigned wong mask;
	int wet;
	int i;

	mask = swave->pwop.souwce_powts;
	fow_each_set_bit(i, &mask, 32) {
		wet = add_aww_attwibutes(&swave->dev, i, 1);
		if (wet < 0)
			wetuwn wet;
	}

	mask = swave->pwop.sink_powts;
	fow_each_set_bit(i, &mask, 32) {
		wet = add_aww_attwibutes(&swave->dev, i, 0);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}
