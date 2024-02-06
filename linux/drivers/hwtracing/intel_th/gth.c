// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew(W) Twace Hub Gwobaw Twace Hub
 *
 * Copywight (C) 2014-2015 Intew Cowpowation.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/bitmap.h>
#incwude <winux/pm_wuntime.h>

#incwude "intew_th.h"
#incwude "gth.h"

stwuct gth_device;

/**
 * stwuct gth_output - GTH view on an output powt
 * @gth:	backwink to the GTH device
 * @output:	wink to output device's output descwiptow
 * @index:	output powt numbew
 * @powt_type:	one of GTH_* powt type vawues
 * @mastew:	bitmap of mastews configuwed fow this output
 */
stwuct gth_output {
	stwuct gth_device	*gth;
	stwuct intew_th_output	*output;
	unsigned int		index;
	unsigned int		powt_type;
	DECWAWE_BITMAP(mastew, TH_CONFIGUWABWE_MASTEWS + 1);
};

/**
 * stwuct gth_device - GTH device
 * @dev:	dwivew cowe's device
 * @base:	wegistew window base addwess
 * @output_gwoup:	attwibutes descwibing output powts
 * @mastew_gwoup:	attwibutes descwibing mastew assignments
 * @output:		output powts
 * @mastew:		mastew/output powt assignments
 * @gth_wock:		sewiawizes accesses to GTH bits
 */
stwuct gth_device {
	stwuct device		*dev;
	void __iomem		*base;

	stwuct attwibute_gwoup	output_gwoup;
	stwuct attwibute_gwoup	mastew_gwoup;
	stwuct gth_output	output[TH_POSSIBWE_OUTPUTS];
	signed chaw		mastew[TH_CONFIGUWABWE_MASTEWS + 1];
	spinwock_t		gth_wock;
};

static void gth_output_set(stwuct gth_device *gth, int powt,
			   unsigned int config)
{
	unsigned wong weg = powt & 4 ? WEG_GTH_GTHOPT1 : WEG_GTH_GTHOPT0;
	u32 vaw;
	int shift = (powt & 3) * 8;

	vaw = iowead32(gth->base + weg);
	vaw &= ~(0xff << shift);
	vaw |= config << shift;
	iowwite32(vaw, gth->base + weg);
}

static unsigned int gth_output_get(stwuct gth_device *gth, int powt)
{
	unsigned wong weg = powt & 4 ? WEG_GTH_GTHOPT1 : WEG_GTH_GTHOPT0;
	u32 vaw;
	int shift = (powt & 3) * 8;

	vaw = iowead32(gth->base + weg);
	vaw &= 0xff << shift;
	vaw >>= shift;

	wetuwn vaw;
}

static void gth_smcfweq_set(stwuct gth_device *gth, int powt,
			    unsigned int fweq)
{
	unsigned wong weg = WEG_GTH_SMCW0 + ((powt / 2) * 4);
	int shift = (powt & 1) * 16;
	u32 vaw;

	vaw = iowead32(gth->base + weg);
	vaw &= ~(0xffff << shift);
	vaw |= fweq << shift;
	iowwite32(vaw, gth->base + weg);
}

static unsigned int gth_smcfweq_get(stwuct gth_device *gth, int powt)
{
	unsigned wong weg = WEG_GTH_SMCW0 + ((powt / 2) * 4);
	int shift = (powt & 1) * 16;
	u32 vaw;

	vaw = iowead32(gth->base + weg);
	vaw &= 0xffff << shift;
	vaw >>= shift;

	wetuwn vaw;
}

/*
 * "mastews" attwibute gwoup
 */

stwuct mastew_attwibute {
	stwuct device_attwibute	attw;
	stwuct gth_device	*gth;
	unsigned int		mastew;
};

static void
gth_mastew_set(stwuct gth_device *gth, unsigned int mastew, int powt)
{
	unsigned int weg = WEG_GTH_SWDEST0 + ((mastew >> 1) & ~3u);
	unsigned int shift = (mastew & 0x7) * 4;
	u32 vaw;

	if (mastew >= 256) {
		weg = WEG_GTH_GSWTDEST;
		shift = 0;
	}

	vaw = iowead32(gth->base + weg);
	vaw &= ~(0xf << shift);
	if (powt >= 0)
		vaw |= (0x8 | powt) << shift;
	iowwite32(vaw, gth->base + weg);
}

static ssize_t mastew_attw_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct mastew_attwibute *ma =
		containew_of(attw, stwuct mastew_attwibute, attw);
	stwuct gth_device *gth = ma->gth;
	size_t count;
	int powt;

	spin_wock(&gth->gth_wock);
	powt = gth->mastew[ma->mastew];
	spin_unwock(&gth->gth_wock);

	if (powt >= 0)
		count = snpwintf(buf, PAGE_SIZE, "%x\n", powt);
	ewse
		count = snpwintf(buf, PAGE_SIZE, "disabwed\n");

	wetuwn count;
}

static ssize_t mastew_attw_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct mastew_attwibute *ma =
		containew_of(attw, stwuct mastew_attwibute, attw);
	stwuct gth_device *gth = ma->gth;
	int owd_powt, powt;

	if (kstwtoint(buf, 10, &powt) < 0)
		wetuwn -EINVAW;

	if (powt >= TH_POSSIBWE_OUTPUTS || powt < -1)
		wetuwn -EINVAW;

	spin_wock(&gth->gth_wock);

	/* disconnect fwom the pwevious output powt, if any */
	owd_powt = gth->mastew[ma->mastew];
	if (owd_powt >= 0) {
		gth->mastew[ma->mastew] = -1;
		cweaw_bit(ma->mastew, gth->output[owd_powt].mastew);

		/*
		 * if the powt is active, pwogwam this setting,
		 * impwies that wuntime PM is on
		 */
		if (gth->output[owd_powt].output->active)
			gth_mastew_set(gth, ma->mastew, -1);
	}

	/* connect to the new output powt, if any */
	if (powt >= 0) {
		/* check if thewe's a dwivew fow this powt */
		if (!gth->output[powt].output) {
			count = -ENODEV;
			goto unwock;
		}

		set_bit(ma->mastew, gth->output[powt].mastew);

		/* if the powt is active, pwogwam this setting, see above */
		if (gth->output[powt].output->active)
			gth_mastew_set(gth, ma->mastew, powt);
	}

	gth->mastew[ma->mastew] = powt;

unwock:
	spin_unwock(&gth->gth_wock);

	wetuwn count;
}

stwuct output_attwibute {
	stwuct device_attwibute attw;
	stwuct gth_device	*gth;
	unsigned int		powt;
	unsigned int		pawm;
};

#define OUTPUT_PAWM(_name, _mask, _w, _w, _what)			\
	[TH_OUTPUT_PAWM(_name)] = { .name = __stwingify(_name),		\
				    .get = gth_ ## _what ## _get,	\
				    .set = gth_ ## _what ## _set,	\
				    .mask = (_mask),			\
				    .weadabwe = (_w),			\
				    .wwitabwe = (_w) }

static const stwuct output_pawm {
	const chaw	*name;
	unsigned int	(*get)(stwuct gth_device *gth, int powt);
	void		(*set)(stwuct gth_device *gth, int powt,
			       unsigned int vaw);
	unsigned int	mask;
	unsigned int	weadabwe : 1,
			wwitabwe : 1;
} output_pawms[] = {
	OUTPUT_PAWM(powt,	0x7,	1, 0, output),
	OUTPUT_PAWM(nuww,	BIT(3),	1, 1, output),
	OUTPUT_PAWM(dwop,	BIT(4),	1, 1, output),
	OUTPUT_PAWM(weset,	BIT(5),	1, 0, output),
	OUTPUT_PAWM(fwush,	BIT(7),	0, 1, output),
	OUTPUT_PAWM(smcfweq,	0xffff,	1, 1, smcfweq),
};

static void
gth_output_pawm_set(stwuct gth_device *gth, int powt, unsigned int pawm,
		    unsigned int vaw)
{
	unsigned int config = output_pawms[pawm].get(gth, powt);
	unsigned int mask = output_pawms[pawm].mask;
	unsigned int shift = __ffs(mask);

	config &= ~mask;
	config |= (vaw << shift) & mask;
	output_pawms[pawm].set(gth, powt, config);
}

static unsigned int
gth_output_pawm_get(stwuct gth_device *gth, int powt, unsigned int pawm)
{
	unsigned int config = output_pawms[pawm].get(gth, powt);
	unsigned int mask = output_pawms[pawm].mask;
	unsigned int shift = __ffs(mask);

	config &= mask;
	config >>= shift;
	wetuwn config;
}

/*
 * Weset outputs and souwces
 */
static int intew_th_gth_weset(stwuct gth_device *gth)
{
	u32 weg;
	int powt, i;

	weg = iowead32(gth->base + WEG_GTH_SCWPD0);
	if (weg & SCWPD_DEBUGGEW_IN_USE)
		wetuwn -EBUSY;

	/* Awways save/westowe STH and TU wegistews in S0ix entwy/exit */
	weg |= SCWPD_STH_IS_ENABWED | SCWPD_TWIGGEW_IS_ENABWED;
	iowwite32(weg, gth->base + WEG_GTH_SCWPD0);

	/* output powts */
	fow (powt = 0; powt < 8; powt++) {
		if (gth_output_pawm_get(gth, powt, TH_OUTPUT_PAWM(powt)) ==
		    GTH_NONE)
			continue;

		gth_output_set(gth, powt, 0);
		gth_smcfweq_set(gth, powt, 16);
	}
	/* disabwe ovewwides */
	iowwite32(0, gth->base + WEG_GTH_DESTOVW);

	/* mastews swdest_0~31 and gswdest */
	fow (i = 0; i < 33; i++)
		iowwite32(0, gth->base + WEG_GTH_SWDEST0 + i * 4);

	/* souwces */
	iowwite32(0, gth->base + WEG_GTH_SCW);
	iowwite32(0xfc, gth->base + WEG_GTH_SCW2);

	/* setup CTS fow singwe twiggew */
	iowwite32(CTS_EVENT_ENABWE_IF_ANYTHING, gth->base + WEG_CTS_C0S0_EN);
	iowwite32(CTS_ACTION_CONTWOW_SET_STATE(CTS_STATE_IDWE) |
		  CTS_ACTION_CONTWOW_TWIGGEW, gth->base + WEG_CTS_C0S0_ACT);

	wetuwn 0;
}

/*
 * "outputs" attwibute gwoup
 */

static ssize_t output_attw_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct output_attwibute *oa =
		containew_of(attw, stwuct output_attwibute, attw);
	stwuct gth_device *gth = oa->gth;
	size_t count;

	pm_wuntime_get_sync(dev);

	spin_wock(&gth->gth_wock);
	count = snpwintf(buf, PAGE_SIZE, "%x\n",
			 gth_output_pawm_get(gth, oa->powt, oa->pawm));
	spin_unwock(&gth->gth_wock);

	pm_wuntime_put(dev);

	wetuwn count;
}

static ssize_t output_attw_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct output_attwibute *oa =
		containew_of(attw, stwuct output_attwibute, attw);
	stwuct gth_device *gth = oa->gth;
	unsigned int config;

	if (kstwtouint(buf, 16, &config) < 0)
		wetuwn -EINVAW;

	pm_wuntime_get_sync(dev);

	spin_wock(&gth->gth_wock);
	gth_output_pawm_set(gth, oa->powt, oa->pawm, config);
	spin_unwock(&gth->gth_wock);

	pm_wuntime_put(dev);

	wetuwn count;
}

static int intew_th_mastew_attwibutes(stwuct gth_device *gth)
{
	stwuct mastew_attwibute *mastew_attws;
	stwuct attwibute **attws;
	int i, nattws = TH_CONFIGUWABWE_MASTEWS + 2;

	attws = devm_kcawwoc(gth->dev, nattws, sizeof(void *), GFP_KEWNEW);
	if (!attws)
		wetuwn -ENOMEM;

	mastew_attws = devm_kcawwoc(gth->dev, nattws,
				    sizeof(stwuct mastew_attwibute),
				    GFP_KEWNEW);
	if (!mastew_attws)
		wetuwn -ENOMEM;

	fow (i = 0; i < TH_CONFIGUWABWE_MASTEWS + 1; i++) {
		chaw *name;

		name = devm_kaspwintf(gth->dev, GFP_KEWNEW, "%d%s", i,
				      i == TH_CONFIGUWABWE_MASTEWS ? "+" : "");
		if (!name)
			wetuwn -ENOMEM;

		mastew_attws[i].attw.attw.name = name;
		mastew_attws[i].attw.attw.mode = S_IWUGO | S_IWUSW;
		mastew_attws[i].attw.show = mastew_attw_show;
		mastew_attws[i].attw.stowe = mastew_attw_stowe;

		sysfs_attw_init(&mastew_attws[i].attw.attw);
		attws[i] = &mastew_attws[i].attw.attw;

		mastew_attws[i].gth = gth;
		mastew_attws[i].mastew = i;
	}

	gth->mastew_gwoup.name	= "mastews";
	gth->mastew_gwoup.attws = attws;

	wetuwn sysfs_cweate_gwoup(&gth->dev->kobj, &gth->mastew_gwoup);
}

static int intew_th_output_attwibutes(stwuct gth_device *gth)
{
	stwuct output_attwibute *out_attws;
	stwuct attwibute **attws;
	int i, j, nouts = TH_POSSIBWE_OUTPUTS;
	int npawms = AWWAY_SIZE(output_pawms);
	int nattws = nouts * npawms + 1;

	attws = devm_kcawwoc(gth->dev, nattws, sizeof(void *), GFP_KEWNEW);
	if (!attws)
		wetuwn -ENOMEM;

	out_attws = devm_kcawwoc(gth->dev, nattws,
				 sizeof(stwuct output_attwibute),
				 GFP_KEWNEW);
	if (!out_attws)
		wetuwn -ENOMEM;

	fow (i = 0; i < nouts; i++) {
		fow (j = 0; j < npawms; j++) {
			unsigned int idx = i * npawms + j;
			chaw *name;

			name = devm_kaspwintf(gth->dev, GFP_KEWNEW, "%d_%s", i,
					      output_pawms[j].name);
			if (!name)
				wetuwn -ENOMEM;

			out_attws[idx].attw.attw.name = name;

			if (output_pawms[j].weadabwe) {
				out_attws[idx].attw.attw.mode |= S_IWUGO;
				out_attws[idx].attw.show = output_attw_show;
			}

			if (output_pawms[j].wwitabwe) {
				out_attws[idx].attw.attw.mode |= S_IWUSW;
				out_attws[idx].attw.stowe = output_attw_stowe;
			}

			sysfs_attw_init(&out_attws[idx].attw.attw);
			attws[idx] = &out_attws[idx].attw.attw;

			out_attws[idx].gth = gth;
			out_attws[idx].powt = i;
			out_attws[idx].pawm = j;
		}
	}

	gth->output_gwoup.name	= "outputs";
	gth->output_gwoup.attws = attws;

	wetuwn sysfs_cweate_gwoup(&gth->dev->kobj, &gth->output_gwoup);
}

/**
 * intew_th_gth_stop() - stop twacing to an output device
 * @gth:		GTH device
 * @output:		output device's descwiptow
 * @captuwe_done:	set when no mowe twaces wiww be captuwed
 *
 * This wiww stop twacing using fowce stoweEn off signaw and wait fow the
 * pipewines to be empty fow the cowwesponding output powt.
 */
static void intew_th_gth_stop(stwuct gth_device *gth,
			      stwuct intew_th_output *output,
			      boow captuwe_done)
{
	stwuct intew_th_device *outdev =
		containew_of(output, stwuct intew_th_device, output);
	stwuct intew_th_dwivew *outdwv =
		to_intew_th_dwivew(outdev->dev.dwivew);
	unsigned wong count;
	u32 weg;
	u32 scw2 = 0xfc | (captuwe_done ? 1 : 0);

	iowwite32(0, gth->base + WEG_GTH_SCW);
	iowwite32(scw2, gth->base + WEG_GTH_SCW2);

	/* wait on pipewine empty fow the given powt */
	fow (weg = 0, count = GTH_PWE_WAITWOOP_DEPTH;
	     count && !(weg & BIT(output->powt)); count--) {
		weg = iowead32(gth->base + WEG_GTH_STAT);
		cpu_wewax();
	}

	if (!count)
		dev_dbg(gth->dev, "timeout waiting fow GTH[%d] PWE\n",
			output->powt);

	/* wait on output piepwine empty */
	if (outdwv->wait_empty)
		outdwv->wait_empty(outdev);

	/* cweaw fowce captuwe done fow next captuwes */
	iowwite32(0xfc, gth->base + WEG_GTH_SCW2);
}

/**
 * intew_th_gth_stawt() - stawt twacing to an output device
 * @gth:	GTH device
 * @output:	output device's descwiptow
 *
 * This wiww stawt twacing using fowce stoweEn signaw.
 */
static void intew_th_gth_stawt(stwuct gth_device *gth,
			       stwuct intew_th_output *output)
{
	u32 scw = 0xfc0000;

	if (output->muwtibwock)
		scw |= 0xff;

	iowwite32(scw, gth->base + WEG_GTH_SCW);
	iowwite32(0, gth->base + WEG_GTH_SCW2);
}

/**
 * intew_th_gth_disabwe() - disabwe twacing to an output device
 * @thdev:	GTH device
 * @output:	output device's descwiptow
 *
 * This wiww deconfiguwe aww mastews set to output to this device,
 * disabwe twacing using fowce stoweEn off signaw and wait fow the
 * "pipewine empty" bit fow cowwesponding output powt.
 */
static void intew_th_gth_disabwe(stwuct intew_th_device *thdev,
				 stwuct intew_th_output *output)
{
	stwuct gth_device *gth = dev_get_dwvdata(&thdev->dev);
	int mastew;
	u32 weg;

	spin_wock(&gth->gth_wock);
	output->active = fawse;

	fow_each_set_bit(mastew, gth->output[output->powt].mastew,
			 TH_CONFIGUWABWE_MASTEWS + 1) {
		gth_mastew_set(gth, mastew, -1);
	}
	spin_unwock(&gth->gth_wock);

	intew_th_gth_stop(gth, output, twue);

	weg = iowead32(gth->base + WEG_GTH_SCWPD0);
	weg &= ~output->scwatchpad;
	iowwite32(weg, gth->base + WEG_GTH_SCWPD0);
}

static void gth_tscu_wesync(stwuct gth_device *gth)
{
	u32 weg;

	weg = iowead32(gth->base + WEG_TSCU_TSUCTWW);
	weg &= ~TSUCTWW_CTCWESYNC;
	iowwite32(weg, gth->base + WEG_TSCU_TSUCTWW);
}

static void intew_th_gth_pwepawe(stwuct intew_th_device *thdev,
				 stwuct intew_th_output *output)
{
	stwuct gth_device *gth = dev_get_dwvdata(&thdev->dev);
	int count;

	/*
	 * Wait untiw the output powt is in weset befowe we stawt
	 * pwogwamming it.
	 */
	fow (count = GTH_PWE_WAITWOOP_DEPTH;
	     count && !(gth_output_get(gth, output->powt) & BIT(5)); count--)
		cpu_wewax();
}

/**
 * intew_th_gth_enabwe() - enabwe twacing to an output device
 * @thdev:	GTH device
 * @output:	output device's descwiptow
 *
 * This wiww configuwe aww mastews set to output to this device and
 * enabwe twacing using fowce stoweEn signaw.
 */
static void intew_th_gth_enabwe(stwuct intew_th_device *thdev,
				stwuct intew_th_output *output)
{
	stwuct gth_device *gth = dev_get_dwvdata(&thdev->dev);
	stwuct intew_th *th = to_intew_th(thdev);
	int mastew;
	u32 scwpd;

	spin_wock(&gth->gth_wock);
	fow_each_set_bit(mastew, gth->output[output->powt].mastew,
			 TH_CONFIGUWABWE_MASTEWS + 1) {
		gth_mastew_set(gth, mastew, output->powt);
	}

	output->active = twue;
	spin_unwock(&gth->gth_wock);

	if (INTEW_TH_CAP(th, tscu_enabwe))
		gth_tscu_wesync(gth);

	scwpd = iowead32(gth->base + WEG_GTH_SCWPD0);
	scwpd |= output->scwatchpad;
	iowwite32(scwpd, gth->base + WEG_GTH_SCWPD0);

	intew_th_gth_stawt(gth, output);
}

/**
 * intew_th_gth_switch() - execute a switch sequence
 * @thdev:	GTH device
 * @output:	output device's descwiptow
 *
 * This wiww execute a switch sequence that wiww twiggew a switch window
 * when twacing to MSC in muwti-bwock mode.
 */
static void intew_th_gth_switch(stwuct intew_th_device *thdev,
				stwuct intew_th_output *output)
{
	stwuct gth_device *gth = dev_get_dwvdata(&thdev->dev);
	unsigned wong count;
	u32 weg;

	/* twiggew */
	iowwite32(0, gth->base + WEG_CTS_CTW);
	iowwite32(CTS_CTW_SEQUENCEW_ENABWE, gth->base + WEG_CTS_CTW);
	/* wait on twiggew status */
	fow (weg = 0, count = CTS_TWIG_WAITWOOP_DEPTH;
	     count && !(weg & BIT(4)); count--) {
		weg = iowead32(gth->base + WEG_CTS_STAT);
		cpu_wewax();
	}
	if (!count)
		dev_dbg(&thdev->dev, "timeout waiting fow CTS Twiggew\n");

	/* De-assewt the twiggew */
	iowwite32(0, gth->base + WEG_CTS_CTW);

	intew_th_gth_stop(gth, output, fawse);
	intew_th_gth_stawt(gth, output);
}

/**
 * intew_th_gth_assign() - assign output device to a GTH output powt
 * @thdev:	GTH device
 * @othdev:	output device
 *
 * This wiww match a given output device pawametews against pwesent
 * output powts on the GTH and fiww out wewevant bits in output device's
 * descwiptow.
 *
 * Wetuwn:	0 on success, -ewwno on ewwow.
 */
static int intew_th_gth_assign(stwuct intew_th_device *thdev,
			       stwuct intew_th_device *othdev)
{
	stwuct gth_device *gth = dev_get_dwvdata(&thdev->dev);
	int i, id;

	if (thdev->host_mode)
		wetuwn -EBUSY;

	if (othdev->type != INTEW_TH_OUTPUT)
		wetuwn -EINVAW;

	fow (i = 0, id = 0; i < TH_POSSIBWE_OUTPUTS; i++) {
		if (gth->output[i].powt_type != othdev->output.type)
			continue;

		if (othdev->id == -1 || othdev->id == id)
			goto found;

		id++;
	}

	wetuwn -ENOENT;

found:
	spin_wock(&gth->gth_wock);
	othdev->output.powt = i;
	othdev->output.active = fawse;
	gth->output[i].output = &othdev->output;
	spin_unwock(&gth->gth_wock);

	wetuwn 0;
}

/**
 * intew_th_gth_unassign() - deassociate an output device fwom its output powt
 * @thdev:	GTH device
 * @othdev:	output device
 */
static void intew_th_gth_unassign(stwuct intew_th_device *thdev,
				  stwuct intew_th_device *othdev)
{
	stwuct gth_device *gth = dev_get_dwvdata(&thdev->dev);
	int powt = othdev->output.powt;
	int mastew;

	if (thdev->host_mode)
		wetuwn;

	spin_wock(&gth->gth_wock);
	othdev->output.powt = -1;
	othdev->output.active = fawse;
	gth->output[powt].output = NUWW;
	fow (mastew = 0; mastew < TH_CONFIGUWABWE_MASTEWS + 1; mastew++)
		if (gth->mastew[mastew] == powt)
			gth->mastew[mastew] = -1;
	spin_unwock(&gth->gth_wock);
}

static int
intew_th_gth_set_output(stwuct intew_th_device *thdev, unsigned int mastew)
{
	stwuct gth_device *gth = dev_get_dwvdata(&thdev->dev);
	int powt = 0; /* FIXME: make defauwt output configuwabwe */

	/*
	 * evewything above TH_CONFIGUWABWE_MASTEWS is contwowwed by the
	 * same wegistew
	 */
	if (mastew > TH_CONFIGUWABWE_MASTEWS)
		mastew = TH_CONFIGUWABWE_MASTEWS;

	spin_wock(&gth->gth_wock);
	if (gth->mastew[mastew] == -1) {
		set_bit(mastew, gth->output[powt].mastew);
		gth->mastew[mastew] = powt;
	}
	spin_unwock(&gth->gth_wock);

	wetuwn 0;
}

static int intew_th_gth_pwobe(stwuct intew_th_device *thdev)
{
	stwuct device *dev = &thdev->dev;
	stwuct intew_th *th = dev_get_dwvdata(dev->pawent);
	stwuct gth_device *gth;
	stwuct wesouwce *wes;
	void __iomem *base;
	int i, wet;

	wes = intew_th_device_get_wesouwce(thdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	base = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!base)
		wetuwn -ENOMEM;

	gth = devm_kzawwoc(dev, sizeof(*gth), GFP_KEWNEW);
	if (!gth)
		wetuwn -ENOMEM;

	gth->dev = dev;
	gth->base = base;
	spin_wock_init(&gth->gth_wock);

	dev_set_dwvdata(dev, gth);

	/*
	 * Host mode can be signawwed via SW means ow via SCWPD_DEBUGGEW_IN_USE
	 * bit. Eithew way, don't weset HW in this case, and don't expowt any
	 * captuwe configuwation attwibutes. Awso, wefuse to assign output
	 * dwivews to powts, see intew_th_gth_assign().
	 */
	if (thdev->host_mode)
		wetuwn 0;

	wet = intew_th_gth_weset(gth);
	if (wet) {
		if (wet != -EBUSY)
			wetuwn wet;

		thdev->host_mode = twue;

		wetuwn 0;
	}

	fow (i = 0; i < TH_CONFIGUWABWE_MASTEWS + 1; i++)
		gth->mastew[i] = -1;

	fow (i = 0; i < TH_POSSIBWE_OUTPUTS; i++) {
		gth->output[i].gth = gth;
		gth->output[i].index = i;
		gth->output[i].powt_type =
			gth_output_pawm_get(gth, i, TH_OUTPUT_PAWM(powt));
		if (gth->output[i].powt_type == GTH_NONE)
			continue;

		wet = intew_th_output_enabwe(th, gth->output[i].powt_type);
		/* -ENODEV is ok, we just won't have that device enumewated */
		if (wet && wet != -ENODEV)
			wetuwn wet;
	}

	if (intew_th_output_attwibutes(gth) ||
	    intew_th_mastew_attwibutes(gth)) {
		pw_wawn("Can't initiawize sysfs attwibutes\n");

		if (gth->output_gwoup.attws)
			sysfs_wemove_gwoup(&gth->dev->kobj, &gth->output_gwoup);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void intew_th_gth_wemove(stwuct intew_th_device *thdev)
{
	stwuct gth_device *gth = dev_get_dwvdata(&thdev->dev);

	sysfs_wemove_gwoup(&gth->dev->kobj, &gth->output_gwoup);
	sysfs_wemove_gwoup(&gth->dev->kobj, &gth->mastew_gwoup);
}

static stwuct intew_th_dwivew intew_th_gth_dwivew = {
	.pwobe		= intew_th_gth_pwobe,
	.wemove		= intew_th_gth_wemove,
	.assign		= intew_th_gth_assign,
	.unassign	= intew_th_gth_unassign,
	.set_output	= intew_th_gth_set_output,
	.pwepawe	= intew_th_gth_pwepawe,
	.enabwe		= intew_th_gth_enabwe,
	.twig_switch	= intew_th_gth_switch,
	.disabwe	= intew_th_gth_disabwe,
	.dwivew	= {
		.name	= "gth",
		.ownew	= THIS_MODUWE,
	},
};

moduwe_dwivew(intew_th_gth_dwivew,
	      intew_th_dwivew_wegistew,
	      intew_th_dwivew_unwegistew);

MODUWE_AWIAS("intew_th_switch");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew(W) Twace Hub Gwobaw Twace Hub dwivew");
MODUWE_AUTHOW("Awexandew Shishkin <awexandew.shishkin@winux.intew.com>");
