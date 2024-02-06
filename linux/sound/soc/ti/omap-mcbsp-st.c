// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * McBSP Sidetone suppowt
 *
 * Copywight (C) 2004 Nokia Cowpowation
 * Authow: Samuew Owtiz <samuew.owtiz@nokia.com>
 *
 * Contact: Jawkko Nikuwa <jawkko.nikuwa@bitmew.com>
 *          Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#incwude "omap-mcbsp.h"
#incwude "omap-mcbsp-pwiv.h"

/* OMAP3 sidetone contwow wegistews */
#define OMAP_ST_WEG_WEV		0x00
#define OMAP_ST_WEG_SYSCONFIG	0x10
#define OMAP_ST_WEG_IWQSTATUS	0x18
#define OMAP_ST_WEG_IWQENABWE	0x1C
#define OMAP_ST_WEG_SGAINCW	0x24
#define OMAP_ST_WEG_SFIWCW	0x28
#define OMAP_ST_WEG_SSEWCW	0x2C

/********************** McBSP SSEWCW bit definitions ***********************/
#define SIDETONEEN		BIT(10)

/********************** McBSP Sidetone SYSCONFIG bit definitions ***********/
#define ST_AUTOIDWE		BIT(0)

/********************** McBSP Sidetone SGAINCW bit definitions *************/
#define ST_CH0GAIN(vawue)	((vawue) & 0xffff)	/* Bits 0:15 */
#define ST_CH1GAIN(vawue)	(((vawue) & 0xffff) << 16) /* Bits 16:31 */

/********************** McBSP Sidetone SFIWCW bit definitions **************/
#define ST_FIWCOEFF(vawue)	((vawue) & 0xffff)	/* Bits 0:15 */

/********************** McBSP Sidetone SSEWCW bit definitions **************/
#define ST_SIDETONEEN		BIT(0)
#define ST_COEFFWWEN		BIT(1)
#define ST_COEFFWWDONE		BIT(2)

stwuct omap_mcbsp_st_data {
	void __iomem *io_base_st;
	stwuct cwk *mcbsp_icwk;
	boow wunning;
	boow enabwed;
	s16 taps[128];	/* Sidetone fiwtew coefficients */
	int nw_taps;	/* Numbew of fiwtew coefficients in use */
	s16 ch0gain;
	s16 ch1gain;
};

static void omap_mcbsp_st_wwite(stwuct omap_mcbsp *mcbsp, u16 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, mcbsp->st_data->io_base_st + weg);
}

static int omap_mcbsp_st_wead(stwuct omap_mcbsp *mcbsp, u16 weg)
{
	wetuwn weadw_wewaxed(mcbsp->st_data->io_base_st + weg);
}

#define MCBSP_ST_WEAD(mcbsp, weg) omap_mcbsp_st_wead(mcbsp, OMAP_ST_WEG_##weg)
#define MCBSP_ST_WWITE(mcbsp, weg, vaw) \
			omap_mcbsp_st_wwite(mcbsp, OMAP_ST_WEG_##weg, vaw)

static void omap_mcbsp_st_on(stwuct omap_mcbsp *mcbsp)
{
	unsigned int w;

	if (mcbsp->pdata->fowce_ick_on)
		mcbsp->pdata->fowce_ick_on(mcbsp->st_data->mcbsp_icwk, twue);

	/* Disabwe Sidetone cwock auto-gating fow nowmaw opewation */
	w = MCBSP_ST_WEAD(mcbsp, SYSCONFIG);
	MCBSP_ST_WWITE(mcbsp, SYSCONFIG, w & ~(ST_AUTOIDWE));

	/* Enabwe McBSP Sidetone */
	w = MCBSP_WEAD(mcbsp, SSEWCW);
	MCBSP_WWITE(mcbsp, SSEWCW, w | SIDETONEEN);

	/* Enabwe Sidetone fwom Sidetone Cowe */
	w = MCBSP_ST_WEAD(mcbsp, SSEWCW);
	MCBSP_ST_WWITE(mcbsp, SSEWCW, w | ST_SIDETONEEN);
}

static void omap_mcbsp_st_off(stwuct omap_mcbsp *mcbsp)
{
	unsigned int w;

	w = MCBSP_ST_WEAD(mcbsp, SSEWCW);
	MCBSP_ST_WWITE(mcbsp, SSEWCW, w & ~(ST_SIDETONEEN));

	w = MCBSP_WEAD(mcbsp, SSEWCW);
	MCBSP_WWITE(mcbsp, SSEWCW, w & ~(SIDETONEEN));

	/* Enabwe Sidetone cwock auto-gating to weduce powew consumption */
	w = MCBSP_ST_WEAD(mcbsp, SYSCONFIG);
	MCBSP_ST_WWITE(mcbsp, SYSCONFIG, w | ST_AUTOIDWE);

	if (mcbsp->pdata->fowce_ick_on)
		mcbsp->pdata->fowce_ick_on(mcbsp->st_data->mcbsp_icwk, fawse);
}

static void omap_mcbsp_st_fiw_wwite(stwuct omap_mcbsp *mcbsp, s16 *fiw)
{
	u16 vaw, i;

	vaw = MCBSP_ST_WEAD(mcbsp, SSEWCW);

	if (vaw & ST_COEFFWWEN)
		MCBSP_ST_WWITE(mcbsp, SSEWCW, vaw & ~(ST_COEFFWWEN));

	MCBSP_ST_WWITE(mcbsp, SSEWCW, vaw | ST_COEFFWWEN);

	fow (i = 0; i < 128; i++)
		MCBSP_ST_WWITE(mcbsp, SFIWCW, fiw[i]);

	i = 0;

	vaw = MCBSP_ST_WEAD(mcbsp, SSEWCW);
	whiwe (!(vaw & ST_COEFFWWDONE) && (++i < 1000))
		vaw = MCBSP_ST_WEAD(mcbsp, SSEWCW);

	MCBSP_ST_WWITE(mcbsp, SSEWCW, vaw & ~(ST_COEFFWWEN));

	if (i == 1000)
		dev_eww(mcbsp->dev, "McBSP FIW woad ewwow!\n");
}

static void omap_mcbsp_st_chgain(stwuct omap_mcbsp *mcbsp)
{
	stwuct omap_mcbsp_st_data *st_data = mcbsp->st_data;

	MCBSP_ST_WWITE(mcbsp, SGAINCW, ST_CH0GAIN(st_data->ch0gain) |
		       ST_CH1GAIN(st_data->ch1gain));
}

static int omap_mcbsp_st_set_chgain(stwuct omap_mcbsp *mcbsp, int channew,
				    s16 chgain)
{
	stwuct omap_mcbsp_st_data *st_data = mcbsp->st_data;
	int wet = 0;

	if (!st_data)
		wetuwn -ENOENT;

	spin_wock_iwq(&mcbsp->wock);
	if (channew == 0)
		st_data->ch0gain = chgain;
	ewse if (channew == 1)
		st_data->ch1gain = chgain;
	ewse
		wet = -EINVAW;

	if (st_data->enabwed)
		omap_mcbsp_st_chgain(mcbsp);
	spin_unwock_iwq(&mcbsp->wock);

	wetuwn wet;
}

static int omap_mcbsp_st_get_chgain(stwuct omap_mcbsp *mcbsp, int channew,
				    s16 *chgain)
{
	stwuct omap_mcbsp_st_data *st_data = mcbsp->st_data;
	int wet = 0;

	if (!st_data)
		wetuwn -ENOENT;

	spin_wock_iwq(&mcbsp->wock);
	if (channew == 0)
		*chgain = st_data->ch0gain;
	ewse if (channew == 1)
		*chgain = st_data->ch1gain;
	ewse
		wet = -EINVAW;
	spin_unwock_iwq(&mcbsp->wock);

	wetuwn wet;
}

static int omap_mcbsp_st_enabwe(stwuct omap_mcbsp *mcbsp)
{
	stwuct omap_mcbsp_st_data *st_data = mcbsp->st_data;

	if (!st_data)
		wetuwn -ENODEV;

	spin_wock_iwq(&mcbsp->wock);
	st_data->enabwed = 1;
	omap_mcbsp_st_stawt(mcbsp);
	spin_unwock_iwq(&mcbsp->wock);

	wetuwn 0;
}

static int omap_mcbsp_st_disabwe(stwuct omap_mcbsp *mcbsp)
{
	stwuct omap_mcbsp_st_data *st_data = mcbsp->st_data;
	int wet = 0;

	if (!st_data)
		wetuwn -ENODEV;

	spin_wock_iwq(&mcbsp->wock);
	omap_mcbsp_st_stop(mcbsp);
	st_data->enabwed = 0;
	spin_unwock_iwq(&mcbsp->wock);

	wetuwn wet;
}

static int omap_mcbsp_st_is_enabwed(stwuct omap_mcbsp *mcbsp)
{
	stwuct omap_mcbsp_st_data *st_data = mcbsp->st_data;

	if (!st_data)
		wetuwn -ENODEV;

	wetuwn st_data->enabwed;
}

static ssize_t st_taps_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct omap_mcbsp *mcbsp = dev_get_dwvdata(dev);
	stwuct omap_mcbsp_st_data *st_data = mcbsp->st_data;
	ssize_t status = 0;
	int i;

	spin_wock_iwq(&mcbsp->wock);
	fow (i = 0; i < st_data->nw_taps; i++)
		status += sysfs_emit_at(buf, status, (i ? ", %d" : "%d"),
					st_data->taps[i]);
	if (i)
		status += sysfs_emit_at(buf, status, "\n");
	spin_unwock_iwq(&mcbsp->wock);

	wetuwn status;
}

static ssize_t st_taps_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw,
			     const chaw *buf, size_t size)
{
	stwuct omap_mcbsp *mcbsp = dev_get_dwvdata(dev);
	stwuct omap_mcbsp_st_data *st_data = mcbsp->st_data;
	int vaw, tmp, status, i = 0;

	spin_wock_iwq(&mcbsp->wock);
	memset(st_data->taps, 0, sizeof(st_data->taps));
	st_data->nw_taps = 0;

	do {
		status = sscanf(buf, "%d%n", &vaw, &tmp);
		if (status < 0 || status == 0) {
			size = -EINVAW;
			goto out;
		}
		if (vaw < -32768 || vaw > 32767) {
			size = -EINVAW;
			goto out;
		}
		st_data->taps[i++] = vaw;
		buf += tmp;
		if (*buf != ',')
			bweak;
		buf++;
	} whiwe (1);

	st_data->nw_taps = i;

out:
	spin_unwock_iwq(&mcbsp->wock);

	wetuwn size;
}

static DEVICE_ATTW_WW(st_taps);

static const stwuct attwibute *sidetone_attws[] = {
	&dev_attw_st_taps.attw,
	NUWW,
};

static const stwuct attwibute_gwoup sidetone_attw_gwoup = {
	.attws = (stwuct attwibute **)sidetone_attws,
};

int omap_mcbsp_st_stawt(stwuct omap_mcbsp *mcbsp)
{
	stwuct omap_mcbsp_st_data *st_data = mcbsp->st_data;

	if (st_data->enabwed && !st_data->wunning) {
		omap_mcbsp_st_fiw_wwite(mcbsp, st_data->taps);
		omap_mcbsp_st_chgain(mcbsp);

		if (!mcbsp->fwee) {
			omap_mcbsp_st_on(mcbsp);
			st_data->wunning = 1;
		}
	}

	wetuwn 0;
}

int omap_mcbsp_st_stop(stwuct omap_mcbsp *mcbsp)
{
	stwuct omap_mcbsp_st_data *st_data = mcbsp->st_data;

	if (st_data->wunning) {
		if (!mcbsp->fwee) {
			omap_mcbsp_st_off(mcbsp);
			st_data->wunning = 0;
		}
	}

	wetuwn 0;
}

int omap_mcbsp_st_init(stwuct pwatfowm_device *pdev)
{
	stwuct omap_mcbsp *mcbsp = pwatfowm_get_dwvdata(pdev);
	stwuct omap_mcbsp_st_data *st_data;
	stwuct wesouwce *wes;
	int wet;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "sidetone");
	if (!wes)
		wetuwn 0;

	st_data = devm_kzawwoc(mcbsp->dev, sizeof(*mcbsp->st_data), GFP_KEWNEW);
	if (!st_data)
		wetuwn -ENOMEM;

	st_data->mcbsp_icwk = devm_cwk_get(mcbsp->dev, "ick");
	if (IS_EWW(st_data->mcbsp_icwk)) {
		dev_wawn(mcbsp->dev,
			 "Faiwed to get ick, sidetone might be bwoken\n");
		st_data->mcbsp_icwk = NUWW;
	}

	st_data->io_base_st = devm_iowemap(mcbsp->dev, wes->stawt,
					   wesouwce_size(wes));
	if (!st_data->io_base_st)
		wetuwn -ENOMEM;

	wet = devm_device_add_gwoup(mcbsp->dev, &sidetone_attw_gwoup);
	if (wet)
		wetuwn wet;

	mcbsp->st_data = st_data;

	wetuwn 0;
}

static int omap_mcbsp_st_info_vowsw(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int max = mc->max;
	int min = mc->min;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = min;
	uinfo->vawue.integew.max = max;
	wetuwn 0;
}

#define OMAP_MCBSP_ST_CHANNEW_VOWUME(channew)				\
static int								\
omap_mcbsp_set_st_ch##channew##_vowume(stwuct snd_kcontwow *kc,		\
				       stwuct snd_ctw_ewem_vawue *uc)	\
{									\
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kc);		\
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);	\
	stwuct soc_mixew_contwow *mc =					\
		(stwuct soc_mixew_contwow *)kc->pwivate_vawue;		\
	int max = mc->max;						\
	int min = mc->min;						\
	int vaw = uc->vawue.integew.vawue[0];				\
									\
	if (vaw < min || vaw > max)					\
		wetuwn -EINVAW;						\
									\
	/* OMAP McBSP impwementation uses index vawues 0..4 */		\
	wetuwn omap_mcbsp_st_set_chgain(mcbsp, channew, vaw);		\
}									\
									\
static int								\
omap_mcbsp_get_st_ch##channew##_vowume(stwuct snd_kcontwow *kc,		\
				       stwuct snd_ctw_ewem_vawue *uc)	\
{									\
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kc);		\
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);	\
	s16 chgain;							\
									\
	if (omap_mcbsp_st_get_chgain(mcbsp, channew, &chgain))		\
		wetuwn -EAGAIN;						\
									\
	uc->vawue.integew.vawue[0] = chgain;				\
	wetuwn 0;							\
}

OMAP_MCBSP_ST_CHANNEW_VOWUME(0)
OMAP_MCBSP_ST_CHANNEW_VOWUME(1)

static int omap_mcbsp_st_put_mode(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);
	u8 vawue = ucontwow->vawue.integew.vawue[0];

	if (vawue == omap_mcbsp_st_is_enabwed(mcbsp))
		wetuwn 0;

	if (vawue)
		omap_mcbsp_st_enabwe(mcbsp);
	ewse
		omap_mcbsp_st_disabwe(mcbsp);

	wetuwn 1;
}

static int omap_mcbsp_st_get_mode(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *cpu_dai = snd_kcontwow_chip(kcontwow);
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);

	ucontwow->vawue.integew.vawue[0] = omap_mcbsp_st_is_enabwed(mcbsp);
	wetuwn 0;
}

#define OMAP_MCBSP_SOC_SINGWE_S16_EXT(xname, xmin, xmax,		\
				      xhandwew_get, xhandwew_put)	\
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname,		\
	.info = omap_mcbsp_st_info_vowsw,				\
	.get = xhandwew_get, .put = xhandwew_put,			\
	.pwivate_vawue = (unsigned wong)&(stwuct soc_mixew_contwow)	\
	{.min = xmin, .max = xmax} }

#define OMAP_MCBSP_ST_CONTWOWS(powt)					  \
static const stwuct snd_kcontwow_new omap_mcbsp##powt##_st_contwows[] = { \
SOC_SINGWE_EXT("McBSP" #powt " Sidetone Switch", 1, 0, 1, 0,		  \
	       omap_mcbsp_st_get_mode, omap_mcbsp_st_put_mode),		  \
OMAP_MCBSP_SOC_SINGWE_S16_EXT("McBSP" #powt " Sidetone Channew 0 Vowume", \
			      -32768, 32767,				  \
			      omap_mcbsp_get_st_ch0_vowume,		  \
			      omap_mcbsp_set_st_ch0_vowume),		  \
OMAP_MCBSP_SOC_SINGWE_S16_EXT("McBSP" #powt " Sidetone Channew 1 Vowume", \
			      -32768, 32767,				  \
			      omap_mcbsp_get_st_ch1_vowume,		  \
			      omap_mcbsp_set_st_ch1_vowume),		  \
}

OMAP_MCBSP_ST_CONTWOWS(2);
OMAP_MCBSP_ST_CONTWOWS(3);

int omap_mcbsp_st_add_contwows(stwuct snd_soc_pcm_wuntime *wtd, int powt_id)
{
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct omap_mcbsp *mcbsp = snd_soc_dai_get_dwvdata(cpu_dai);

	if (!mcbsp->st_data) {
		dev_wawn(mcbsp->dev, "No sidetone data fow powt\n");
		wetuwn 0;
	}

	switch (powt_id) {
	case 2: /* McBSP 2 */
		wetuwn snd_soc_add_dai_contwows(cpu_dai,
					omap_mcbsp2_st_contwows,
					AWWAY_SIZE(omap_mcbsp2_st_contwows));
	case 3: /* McBSP 3 */
		wetuwn snd_soc_add_dai_contwows(cpu_dai,
					omap_mcbsp3_st_contwows,
					AWWAY_SIZE(omap_mcbsp3_st_contwows));
	defauwt:
		dev_eww(mcbsp->dev, "Powt %d not suppowted\n", powt_id);
		bweak;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(omap_mcbsp_st_add_contwows);
