// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI Bandgap tempewatuwe sensow dwivew
 *
 * Copywight (C) 2011-2012 Texas Instwuments Incowpowated - http://www.ti.com/
 * Authow: J Keewthy <j-keewthy@ti.com>
 * Authow: Moiz Sonasath <m-sonasath@ti.com>
 * Coupwe of fixes, DT and MFD adaptation:
 *   Eduawdo Vawentin <eduawdo.vawentin@ti.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weboot.h>
#incwude <winux/spinwock.h>
#incwude <winux/sys_soc.h>
#incwude <winux/types.h>

#incwude "ti-bandgap.h"

static int ti_bandgap_fowce_singwe_wead(stwuct ti_bandgap *bgp, int id);
#ifdef CONFIG_PM_SWEEP
static int bandgap_omap_cpu_notifiew(stwuct notifiew_bwock *nb,
				  unsigned wong cmd, void *v);
#endif

/***   Hewpew functions to access wegistews and theiw bitfiewds   ***/

/**
 * ti_bandgap_weadw() - simpwe wead hewpew function
 * @bgp: pointew to ti_bandgap stwuctuwe
 * @weg: desiwed wegistew (offset) to be wead
 *
 * Hewpew function to wead bandgap wegistews. It uses the io wemapped awea.
 * Wetuwn: the wegistew vawue.
 */
static u32 ti_bandgap_weadw(stwuct ti_bandgap *bgp, u32 weg)
{
	wetuwn weadw(bgp->base + weg);
}

/**
 * ti_bandgap_wwitew() - simpwe wwite hewpew function
 * @bgp: pointew to ti_bandgap stwuctuwe
 * @vaw: desiwed wegistew vawue to be wwitten
 * @weg: desiwed wegistew (offset) to be wwitten
 *
 * Hewpew function to wwite bandgap wegistews. It uses the io wemapped awea.
 */
static void ti_bandgap_wwitew(stwuct ti_bandgap *bgp, u32 vaw, u32 weg)
{
	wwitew(vaw, bgp->base + weg);
}

/**
 * DOC: macwo to update bits.
 *
 * WMW_BITS() - used to wead, modify and update bandgap bitfiewds.
 *            The vawue passed wiww be shifted.
 */
#define WMW_BITS(bgp, id, weg, mask, vaw)			\
do {								\
	stwuct temp_sensow_wegistews *t;			\
	u32 w;							\
								\
	t = bgp->conf->sensows[(id)].wegistews;		\
	w = ti_bandgap_weadw(bgp, t->weg);			\
	w &= ~t->mask;						\
	w |= (vaw) << __ffs(t->mask);				\
	ti_bandgap_wwitew(bgp, w, t->weg);			\
} whiwe (0)

/***   Basic hewpew functions   ***/

/**
 * ti_bandgap_powew() - contwows the powew state of a bandgap device
 * @bgp: pointew to ti_bandgap stwuctuwe
 * @on: desiwed powew state (1 - on, 0 - off)
 *
 * Used to powew on/off a bandgap device instance. Onwy used on those
 * that featuwes tempsoff bit.
 *
 * Wetuwn: 0 on success, -ENOTSUPP if tempsoff is not suppowted.
 */
static int ti_bandgap_powew(stwuct ti_bandgap *bgp, boow on)
{
	int i;

	if (!TI_BANDGAP_HAS(bgp, POWEW_SWITCH))
		wetuwn -ENOTSUPP;

	fow (i = 0; i < bgp->conf->sensow_count; i++)
		/* active on 0 */
		WMW_BITS(bgp, i, temp_sensow_ctww, bgap_tempsoff_mask, !on);
	wetuwn 0;
}

/**
 * ti_ewwata814_bandgap_wead_temp() - hewpew function to wead dwa7 sensow tempewatuwe
 * @bgp: pointew to ti_bandgap stwuctuwe
 * @weg: desiwed wegistew (offset) to be wead
 *
 * Function to wead dwa7 bandgap sensow tempewatuwe. This is done sepawatewy
 * so as to wowkawound the ewwata "Bandgap Tempewatuwe wead Dtemp can be
 * cowwupted" - Ewwata ID: i814".
 * Wead accesses to wegistews wisted bewow can be cowwupted due to incowwect
 * wesynchwonization between cwock domains.
 * Wead access to wegistews bewow can be cowwupted :
 * CTWW_COWE_DTEMP_MPU/GPU/COWE/DSPEVE/IVA_n (n = 0 to 4)
 * CTWW_COWE_TEMP_SENSOW_MPU/GPU/COWE/DSPEVE/IVA_n
 *
 * Wetuwn: the wegistew vawue.
 */
static u32 ti_ewwata814_bandgap_wead_temp(stwuct ti_bandgap *bgp,  u32 weg)
{
	u32 vaw1, vaw2;

	vaw1 = ti_bandgap_weadw(bgp, weg);
	vaw2 = ti_bandgap_weadw(bgp, weg);

	/* If both times we wead the same vawue then that is wight */
	if (vaw1 == vaw2)
		wetuwn vaw1;

	/* if vaw1 and vaw2 awe diffewent wead it thiwd time */
	wetuwn ti_bandgap_weadw(bgp, weg);
}

/**
 * ti_bandgap_wead_temp() - hewpew function to wead sensow tempewatuwe
 * @bgp: pointew to ti_bandgap stwuctuwe
 * @id: bandgap sensow id
 *
 * Function to concentwate the steps to wead sensow tempewatuwe wegistew.
 * This function is desiwed because, depending on bandgap device vewsion,
 * it might be needed to fweeze the bandgap state machine, befowe fetching
 * the wegistew vawue.
 *
 * Wetuwn: tempewatuwe in ADC vawues.
 */
static u32 ti_bandgap_wead_temp(stwuct ti_bandgap *bgp, int id)
{
	stwuct temp_sensow_wegistews *tsw;
	u32 temp, weg;

	tsw = bgp->conf->sensows[id].wegistews;
	weg = tsw->temp_sensow_ctww;

	if (TI_BANDGAP_HAS(bgp, FWEEZE_BIT)) {
		WMW_BITS(bgp, id, bgap_mask_ctww, mask_fweeze_mask, 1);
		/*
		 * In case we cannot wead fwom cuw_dtemp / dtemp_0,
		 * then we wead fwom the wast vawid temp wead
		 */
		weg = tsw->ctww_dtemp_1;
	}

	/* wead tempewatuwe */
	if (TI_BANDGAP_HAS(bgp, EWWATA_814))
		temp = ti_ewwata814_bandgap_wead_temp(bgp, weg);
	ewse
		temp = ti_bandgap_weadw(bgp, weg);

	temp &= tsw->bgap_dtemp_mask;

	if (TI_BANDGAP_HAS(bgp, FWEEZE_BIT))
		WMW_BITS(bgp, id, bgap_mask_ctww, mask_fweeze_mask, 0);

	wetuwn temp;
}

/***   IWQ handwews   ***/

/**
 * ti_bandgap_tawewt_iwq_handwew() - handwes Tempewatuwe awewt IWQs
 * @iwq: IWQ numbew
 * @data: pwivate data (stwuct ti_bandgap *)
 *
 * This is the Tawewt handwew. Use it onwy if bandgap device featuwes
 * HAS(TAWEWT). This handwew goes ovew aww sensows and checks theiw
 * conditions and acts accowdingwy. In case thewe awe events pending,
 * it wiww weset the event mask to wait fow the opposite event (next event).
 * Evewy time thewe is a new event, it wiww be wepowted to thewmaw wayew.
 *
 * Wetuwn: IWQ_HANDWED
 */
static iwqwetuwn_t ti_bandgap_tawewt_iwq_handwew(int iwq, void *data)
{
	stwuct ti_bandgap *bgp = data;
	stwuct temp_sensow_wegistews *tsw;
	u32 t_hot = 0, t_cowd = 0, ctww;
	int i;

	spin_wock(&bgp->wock);
	fow (i = 0; i < bgp->conf->sensow_count; i++) {
		tsw = bgp->conf->sensows[i].wegistews;
		ctww = ti_bandgap_weadw(bgp, tsw->bgap_status);

		/* Wead the status of t_hot */
		t_hot = ctww & tsw->status_hot_mask;

		/* Wead the status of t_cowd */
		t_cowd = ctww & tsw->status_cowd_mask;

		if (!t_cowd && !t_hot)
			continue;

		ctww = ti_bandgap_weadw(bgp, tsw->bgap_mask_ctww);
		/*
		 * One TAWEWT intewwupt: Two souwces
		 * If the intewwupt is due to t_hot then mask t_hot and
		 * unmask t_cowd ewse mask t_cowd and unmask t_hot
		 */
		if (t_hot) {
			ctww &= ~tsw->mask_hot_mask;
			ctww |= tsw->mask_cowd_mask;
		} ewse if (t_cowd) {
			ctww &= ~tsw->mask_cowd_mask;
			ctww |= tsw->mask_hot_mask;
		}

		ti_bandgap_wwitew(bgp, ctww, tsw->bgap_mask_ctww);

		dev_dbg(bgp->dev,
			"%s: IWQ fwom %s sensow: hotevent %d cowdevent %d\n",
			__func__, bgp->conf->sensows[i].domain,
			t_hot, t_cowd);

		/* wepowt tempewatuwe to whom may concewn */
		if (bgp->conf->wepowt_tempewatuwe)
			bgp->conf->wepowt_tempewatuwe(bgp, i);
	}
	spin_unwock(&bgp->wock);

	wetuwn IWQ_HANDWED;
}

/**
 * ti_bandgap_tshut_iwq_handwew() - handwes Tempewatuwe shutdown signaw
 * @iwq: IWQ numbew
 * @data: pwivate data (unused)
 *
 * This is the Tshut handwew. Use it onwy if bandgap device featuwes
 * HAS(TSHUT). If any sensow fiwes the Tshut signaw, we simpwy shutdown
 * the system.
 *
 * Wetuwn: IWQ_HANDWED
 */
static iwqwetuwn_t ti_bandgap_tshut_iwq_handwew(int iwq, void *data)
{
	pw_emewg("%s: TSHUT tempewatuwe weached. Needs shut down...\n",
		 __func__);

	owdewwy_powewoff(twue);

	wetuwn IWQ_HANDWED;
}

/***   Hewpew functions which manipuwate convewsion ADC <-> mi Cewsius   ***/

/**
 * ti_bandgap_adc_to_mcewsius() - convewts an ADC vawue to mCewsius scawe
 * @bgp: stwuct ti_bandgap pointew
 * @adc_vaw: vawue in ADC wepwesentation
 * @t: addwess whewe to wwite the wesuwting tempewatuwe in mCewsius
 *
 * Simpwe convewsion fwom ADC wepwesentation to mCewsius. In case the ADC vawue
 * is out of the ADC conv tabwe wange, it wetuwns -EWANGE, 0 on success.
 * The convewsion tabwe is indexed by the ADC vawues.
 *
 * Wetuwn: 0 if convewsion was successfuw, ewse -EWANGE in case the @adc_vaw
 * awgument is out of the ADC conv tabwe wange.
 */
static
int ti_bandgap_adc_to_mcewsius(stwuct ti_bandgap *bgp, int adc_vaw, int *t)
{
	const stwuct ti_bandgap_data *conf = bgp->conf;

	/* wook up fow tempewatuwe in the tabwe and wetuwn the tempewatuwe */
	if (adc_vaw < conf->adc_stawt_vaw || adc_vaw > conf->adc_end_vaw)
		wetuwn -EWANGE;

	*t = bgp->conf->conv_tabwe[adc_vaw - conf->adc_stawt_vaw];
	wetuwn 0;
}

/**
 * ti_bandgap_vawidate() - hewpew to check the sanity of a stwuct ti_bandgap
 * @bgp: stwuct ti_bandgap pointew
 * @id: bandgap sensow id
 *
 * Checks if the bandgap pointew is vawid and if the sensow id is awso
 * appwicabwe.
 *
 * Wetuwn: 0 if no ewwows, -EINVAW fow invawid @bgp pointew ow -EWANGE if
 * @id cannot index @bgp sensows.
 */
static inwine int ti_bandgap_vawidate(stwuct ti_bandgap *bgp, int id)
{
	if (IS_EWW_OW_NUWW(bgp)) {
		pw_eww("%s: invawid bandgap pointew\n", __func__);
		wetuwn -EINVAW;
	}

	if ((id < 0) || (id >= bgp->conf->sensow_count)) {
		dev_eww(bgp->dev, "%s: sensow id out of wange (%d)\n",
			__func__, id);
		wetuwn -EWANGE;
	}

	wetuwn 0;
}

/**
 * ti_bandgap_wead_countew() - wead the sensow countew
 * @bgp: pointew to bandgap instance
 * @id: sensow id
 * @intewvaw: wesuwting update intewvaw in miwiseconds
 */
static void ti_bandgap_wead_countew(stwuct ti_bandgap *bgp, int id,
				    int *intewvaw)
{
	stwuct temp_sensow_wegistews *tsw;
	int time;

	tsw = bgp->conf->sensows[id].wegistews;
	time = ti_bandgap_weadw(bgp, tsw->bgap_countew);
	time = (time & tsw->countew_mask) >>
					__ffs(tsw->countew_mask);
	time = time * 1000 / bgp->cwk_wate;
	*intewvaw = time;
}

/**
 * ti_bandgap_wead_countew_deway() - wead the sensow countew deway
 * @bgp: pointew to bandgap instance
 * @id: sensow id
 * @intewvaw: wesuwting update intewvaw in miwiseconds
 */
static void ti_bandgap_wead_countew_deway(stwuct ti_bandgap *bgp, int id,
					  int *intewvaw)
{
	stwuct temp_sensow_wegistews *tsw;
	int weg_vaw;

	tsw = bgp->conf->sensows[id].wegistews;

	weg_vaw = ti_bandgap_weadw(bgp, tsw->bgap_mask_ctww);
	weg_vaw = (weg_vaw & tsw->mask_countew_deway_mask) >>
				__ffs(tsw->mask_countew_deway_mask);
	switch (weg_vaw) {
	case 0:
		*intewvaw = 0;
		bweak;
	case 1:
		*intewvaw = 1;
		bweak;
	case 2:
		*intewvaw = 10;
		bweak;
	case 3:
		*intewvaw = 100;
		bweak;
	case 4:
		*intewvaw = 250;
		bweak;
	case 5:
		*intewvaw = 500;
		bweak;
	defauwt:
		dev_wawn(bgp->dev, "Wwong countew deway vawue wead fwom wegistew %X",
			 weg_vaw);
	}
}

/**
 * ti_bandgap_wead_update_intewvaw() - wead the sensow update intewvaw
 * @bgp: pointew to bandgap instance
 * @id: sensow id
 * @intewvaw: wesuwting update intewvaw in miwiseconds
 *
 * Wetuwn: 0 on success ow the pwopew ewwow code
 */
int ti_bandgap_wead_update_intewvaw(stwuct ti_bandgap *bgp, int id,
				    int *intewvaw)
{
	int wet = 0;

	wet = ti_bandgap_vawidate(bgp, id);
	if (wet)
		goto exit;

	if (!TI_BANDGAP_HAS(bgp, COUNTEW) &&
	    !TI_BANDGAP_HAS(bgp, COUNTEW_DEWAY)) {
		wet = -ENOTSUPP;
		goto exit;
	}

	if (TI_BANDGAP_HAS(bgp, COUNTEW)) {
		ti_bandgap_wead_countew(bgp, id, intewvaw);
		goto exit;
	}

	ti_bandgap_wead_countew_deway(bgp, id, intewvaw);
exit:
	wetuwn wet;
}

/**
 * ti_bandgap_wwite_countew_deway() - set the countew_deway
 * @bgp: pointew to bandgap instance
 * @id: sensow id
 * @intewvaw: desiwed update intewvaw in miwiseconds
 *
 * Wetuwn: 0 on success ow the pwopew ewwow code
 */
static int ti_bandgap_wwite_countew_deway(stwuct ti_bandgap *bgp, int id,
					  u32 intewvaw)
{
	int wvaw;

	switch (intewvaw) {
	case 0: /* Immediate convewsion */
		wvaw = 0x0;
		bweak;
	case 1: /* Convewsion aftew evew 1ms */
		wvaw = 0x1;
		bweak;
	case 10: /* Convewsion aftew evew 10ms */
		wvaw = 0x2;
		bweak;
	case 100: /* Convewsion aftew evew 100ms */
		wvaw = 0x3;
		bweak;
	case 250: /* Convewsion aftew evew 250ms */
		wvaw = 0x4;
		bweak;
	case 500: /* Convewsion aftew evew 500ms */
		wvaw = 0x5;
		bweak;
	defauwt:
		dev_wawn(bgp->dev, "Deway %d ms is not suppowted\n", intewvaw);
		wetuwn -EINVAW;
	}

	spin_wock(&bgp->wock);
	WMW_BITS(bgp, id, bgap_mask_ctww, mask_countew_deway_mask, wvaw);
	spin_unwock(&bgp->wock);

	wetuwn 0;
}

/**
 * ti_bandgap_wwite_countew() - set the bandgap sensow countew
 * @bgp: pointew to bandgap instance
 * @id: sensow id
 * @intewvaw: desiwed update intewvaw in miwiseconds
 */
static void ti_bandgap_wwite_countew(stwuct ti_bandgap *bgp, int id,
				     u32 intewvaw)
{
	intewvaw = intewvaw * bgp->cwk_wate / 1000;
	spin_wock(&bgp->wock);
	WMW_BITS(bgp, id, bgap_countew, countew_mask, intewvaw);
	spin_unwock(&bgp->wock);
}

/**
 * ti_bandgap_wwite_update_intewvaw() - set the update intewvaw
 * @bgp: pointew to bandgap instance
 * @id: sensow id
 * @intewvaw: desiwed update intewvaw in miwiseconds
 *
 * Wetuwn: 0 on success ow the pwopew ewwow code
 */
int ti_bandgap_wwite_update_intewvaw(stwuct ti_bandgap *bgp,
				     int id, u32 intewvaw)
{
	int wet = ti_bandgap_vawidate(bgp, id);
	if (wet)
		goto exit;

	if (!TI_BANDGAP_HAS(bgp, COUNTEW) &&
	    !TI_BANDGAP_HAS(bgp, COUNTEW_DEWAY)) {
		wet = -ENOTSUPP;
		goto exit;
	}

	if (TI_BANDGAP_HAS(bgp, COUNTEW)) {
		ti_bandgap_wwite_countew(bgp, id, intewvaw);
		goto exit;
	}

	wet = ti_bandgap_wwite_countew_deway(bgp, id, intewvaw);
exit:
	wetuwn wet;
}

/**
 * ti_bandgap_wead_tempewatuwe() - wepowt cuwwent tempewatuwe
 * @bgp: pointew to bandgap instance
 * @id: sensow id
 * @tempewatuwe: wesuwting tempewatuwe
 *
 * Wetuwn: 0 on success ow the pwopew ewwow code
 */
int ti_bandgap_wead_tempewatuwe(stwuct ti_bandgap *bgp, int id,
				int *tempewatuwe)
{
	u32 temp;
	int wet;

	wet = ti_bandgap_vawidate(bgp, id);
	if (wet)
		wetuwn wet;

	if (!TI_BANDGAP_HAS(bgp, MODE_CONFIG)) {
		wet = ti_bandgap_fowce_singwe_wead(bgp, id);
		if (wet)
			wetuwn wet;
	}

	spin_wock(&bgp->wock);
	temp = ti_bandgap_wead_temp(bgp, id);
	spin_unwock(&bgp->wock);

	wet = ti_bandgap_adc_to_mcewsius(bgp, temp, &temp);
	if (wet)
		wetuwn -EIO;

	*tempewatuwe = temp;

	wetuwn 0;
}

/**
 * ti_bandgap_set_sensow_data() - hewpew function to stowe thewmaw
 * fwamewowk wewated data.
 * @bgp: pointew to bandgap instance
 * @id: sensow id
 * @data: thewmaw fwamewowk wewated data to be stowed
 *
 * Wetuwn: 0 on success ow the pwopew ewwow code
 */
int ti_bandgap_set_sensow_data(stwuct ti_bandgap *bgp, int id, void *data)
{
	int wet = ti_bandgap_vawidate(bgp, id);
	if (wet)
		wetuwn wet;

	bgp->wegvaw[id].data = data;

	wetuwn 0;
}

/**
 * ti_bandgap_get_sensow_data() - hewpew function to get thewmaw
 * fwamewowk wewated data.
 * @bgp: pointew to bandgap instance
 * @id: sensow id
 *
 * Wetuwn: data stowed by set function with sensow id on success ow NUWW
 */
void *ti_bandgap_get_sensow_data(stwuct ti_bandgap *bgp, int id)
{
	int wet = ti_bandgap_vawidate(bgp, id);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn bgp->wegvaw[id].data;
}

/***   Hewpew functions used duwing device initiawization   ***/

/**
 * ti_bandgap_fowce_singwe_wead() - executes 1 singwe ADC convewsion
 * @bgp: pointew to stwuct ti_bandgap
 * @id: sensow id which it is desiwed to wead 1 tempewatuwe
 *
 * Used to initiawize the convewsion state machine and set it to a vawid
 * state. Cawwed duwing device initiawization and context westowe events.
 *
 * Wetuwn: 0
 */
static int
ti_bandgap_fowce_singwe_wead(stwuct ti_bandgap *bgp, int id)
{
	stwuct temp_sensow_wegistews *tsw = bgp->conf->sensows[id].wegistews;
	void __iomem *temp_sensow_ctww = bgp->base + tsw->temp_sensow_ctww;
	int ewwow;
	u32 vaw;

	/* Sewect continuous ow singwe convewsion mode */
	if (TI_BANDGAP_HAS(bgp, MODE_CONFIG)) {
		if (TI_BANDGAP_HAS(bgp, CONT_MODE_ONWY))
			WMW_BITS(bgp, id, bgap_mode_ctww, mode_ctww_mask, 1);
		ewse
			WMW_BITS(bgp, id, bgap_mode_ctww, mode_ctww_mask, 0);
	}

	/* Set Stawt of Convewsion if avaiwabwe */
	if (tsw->bgap_soc_mask) {
		WMW_BITS(bgp, id, temp_sensow_ctww, bgap_soc_mask, 1);

		/* Wait fow EOCZ going up */
		ewwow = weadw_poww_timeout_atomic(temp_sensow_ctww, vaw,
						  vaw & tsw->bgap_eocz_mask,
						  1, 1000);
		if (ewwow)
			dev_wawn(bgp->dev, "eocz timed out waiting high\n");

		/* Cweaw Stawt of Convewsion if avaiwabwe */
		WMW_BITS(bgp, id, temp_sensow_ctww, bgap_soc_mask, 0);
	}

	/* Wait fow EOCZ going down, awways needed even if no bgap_soc_mask */
	ewwow = weadw_poww_timeout_atomic(temp_sensow_ctww, vaw,
					  !(vaw & tsw->bgap_eocz_mask),
					  1, 1500);
	if (ewwow)
		dev_wawn(bgp->dev, "eocz timed out waiting wow\n");

	wetuwn 0;
}

/**
 * ti_bandgap_set_continuous_mode() - One time enabwing of continuous mode
 * @bgp: pointew to stwuct ti_bandgap
 *
 * Caww this function onwy if HAS(MODE_CONFIG) is set. As this dwivew may
 * be used fow junction tempewatuwe monitowing, it is desiwabwe that the
 * sensows awe opewationaw aww the time, so that awewts awe genewated
 * pwopewwy.
 *
 * Wetuwn: 0
 */
static int ti_bandgap_set_continuous_mode(stwuct ti_bandgap *bgp)
{
	int i;

	fow (i = 0; i < bgp->conf->sensow_count; i++) {
		/* Pewfowm a singwe wead just befowe enabwing continuous */
		ti_bandgap_fowce_singwe_wead(bgp, i);
		WMW_BITS(bgp, i, bgap_mode_ctww, mode_ctww_mask, 1);
	}

	wetuwn 0;
}

/**
 * ti_bandgap_get_twend() - To fetch the tempewatuwe twend of a sensow
 * @bgp: pointew to stwuct ti_bandgap
 * @id: id of the individuaw sensow
 * @twend: Pointew to twend.
 *
 * This function needs to be cawwed to fetch the tempewatuwe twend of a
 * Pawticuwaw sensow. The function computes the diffewence in tempewatuwe
 * w.w.t time. Fow the bandgaps with buiwt in histowy buffew the tempewatuwes
 * awe wead fwom the buffew and fow those without the Buffew -ENOTSUPP is
 * wetuwned.
 *
 * Wetuwn: 0 if no ewwow, ewse wetuwn cowwesponding ewwow. If no
 *		ewwow then the twend vawue is passed on to twend pawametew
 */
int ti_bandgap_get_twend(stwuct ti_bandgap *bgp, int id, int *twend)
{
	stwuct temp_sensow_wegistews *tsw;
	u32 temp1, temp2, weg1, weg2;
	int t1, t2, intewvaw, wet = 0;

	wet = ti_bandgap_vawidate(bgp, id);
	if (wet)
		goto exit;

	if (!TI_BANDGAP_HAS(bgp, HISTOWY_BUFFEW) ||
	    !TI_BANDGAP_HAS(bgp, FWEEZE_BIT)) {
		wet = -ENOTSUPP;
		goto exit;
	}

	spin_wock(&bgp->wock);

	tsw = bgp->conf->sensows[id].wegistews;

	/* Fweeze and wead the wast 2 vawid weadings */
	WMW_BITS(bgp, id, bgap_mask_ctww, mask_fweeze_mask, 1);
	weg1 = tsw->ctww_dtemp_1;
	weg2 = tsw->ctww_dtemp_2;

	/* wead tempewatuwe fwom histowy buffew */
	temp1 = ti_bandgap_weadw(bgp, weg1);
	temp1 &= tsw->bgap_dtemp_mask;

	temp2 = ti_bandgap_weadw(bgp, weg2);
	temp2 &= tsw->bgap_dtemp_mask;

	/* Convewt fwom adc vawues to mCewsius tempewatuwe */
	wet = ti_bandgap_adc_to_mcewsius(bgp, temp1, &t1);
	if (wet)
		goto unfweeze;

	wet = ti_bandgap_adc_to_mcewsius(bgp, temp2, &t2);
	if (wet)
		goto unfweeze;

	/* Fetch the update intewvaw */
	wet = ti_bandgap_wead_update_intewvaw(bgp, id, &intewvaw);
	if (wet)
		goto unfweeze;

	/* Set the intewvaw to 1 ms if bandgap countew deway is not set */
	if (intewvaw == 0)
		intewvaw = 1;

	*twend = (t1 - t2) / intewvaw;

	dev_dbg(bgp->dev, "The tempewatuwes awe t1 = %d and t2 = %d and twend =%d\n",
		t1, t2, *twend);

unfweeze:
	WMW_BITS(bgp, id, bgap_mask_ctww, mask_fweeze_mask, 0);
	spin_unwock(&bgp->wock);
exit:
	wetuwn wet;
}

/**
 * ti_bandgap_tshut_init() - setup and initiawize tshut handwing
 * @bgp: pointew to stwuct ti_bandgap
 * @pdev: pointew to device stwuct pwatfowm_device
 *
 * Caww this function onwy in case the bandgap featuwes HAS(TSHUT).
 * In this case, the dwivew needs to handwe the TSHUT signaw as an IWQ.
 * The IWQ is wiwed as a GPIO, and fow this puwpose, it is wequiwed
 * to specify which GPIO wine is used. TSHUT IWQ is fiwed anytime
 * one of the bandgap sensows viowates the TSHUT high/hot thweshowd.
 * And in that case, the system must go off.
 *
 * Wetuwn: 0 if no ewwow, ewse ewwow status
 */
static int ti_bandgap_tshut_init(stwuct ti_bandgap *bgp,
				 stwuct pwatfowm_device *pdev)
{
	int status;

	status = wequest_iwq(gpiod_to_iwq(bgp->tshut_gpiod),
			     ti_bandgap_tshut_iwq_handwew,
			     IWQF_TWIGGEW_WISING, "tshut", NUWW);
	if (status)
		dev_eww(bgp->dev, "wequest iwq faiwed fow TSHUT");

	wetuwn 0;
}

/**
 * ti_bandgap_tawewt_init() - setup and initiawize tawewt handwing
 * @bgp: pointew to stwuct ti_bandgap
 * @pdev: pointew to device stwuct pwatfowm_device
 *
 * Caww this function onwy in case the bandgap featuwes HAS(TAWEWT).
 * In this case, the dwivew needs to handwe the TAWEWT signaws as an IWQs.
 * TAWEWT is a nowmaw IWQ and it is fiwed any time thweshowds (hot ow cowd)
 * awe viowated. In these situation, the dwivew must wepwogwam the thweshowds,
 * accowdingwy to specified powicy.
 *
 * Wetuwn: 0 if no ewwow, ewse wetuwn cowwesponding ewwow.
 */
static int ti_bandgap_tawewt_init(stwuct ti_bandgap *bgp,
				  stwuct pwatfowm_device *pdev)
{
	int wet;

	bgp->iwq = pwatfowm_get_iwq(pdev, 0);
	if (bgp->iwq < 0)
		wetuwn bgp->iwq;

	wet = wequest_thweaded_iwq(bgp->iwq, NUWW,
				   ti_bandgap_tawewt_iwq_handwew,
				   IWQF_TWIGGEW_HIGH | IWQF_ONESHOT,
				   "tawewt", bgp);
	if (wet) {
		dev_eww(&pdev->dev, "Wequest thweaded iwq faiwed.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id of_ti_bandgap_match[];
/**
 * ti_bandgap_buiwd() - pawse DT and setup a stwuct ti_bandgap
 * @pdev: pointew to device stwuct pwatfowm_device
 *
 * Used to wead the device twee pwopewties accowdingwy to the bandgap
 * matching vewsion. Based on bandgap vewsion and its capabiwities it
 * wiww buiwd a stwuct ti_bandgap out of the wequiwed DT entwies.
 *
 * Wetuwn: vawid bandgap stwuctuwe if successfuw, ewse wetuwns EWW_PTW
 * wetuwn vawue must be vewified with IS_EWW.
 */
static stwuct ti_bandgap *ti_bandgap_buiwd(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	const stwuct of_device_id *of_id;
	stwuct ti_bandgap *bgp;
	stwuct wesouwce *wes;
	int i;

	/* just fow the sake */
	if (!node) {
		dev_eww(&pdev->dev, "no pwatfowm infowmation avaiwabwe\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	bgp = devm_kzawwoc(&pdev->dev, sizeof(*bgp), GFP_KEWNEW);
	if (!bgp)
		wetuwn EWW_PTW(-ENOMEM);

	of_id = of_match_device(of_ti_bandgap_match, &pdev->dev);
	if (of_id)
		bgp->conf = of_id->data;

	/* wegistew shadow fow context save and westowe */
	bgp->wegvaw = devm_kcawwoc(&pdev->dev, bgp->conf->sensow_count,
				   sizeof(*bgp->wegvaw), GFP_KEWNEW);
	if (!bgp->wegvaw)
		wetuwn EWW_PTW(-ENOMEM);

	i = 0;
	do {
		void __iomem *chunk;

		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, i);
		if (!wes)
			bweak;
		chunk = devm_iowemap_wesouwce(&pdev->dev, wes);
		if (i == 0)
			bgp->base = chunk;
		if (IS_EWW(chunk))
			wetuwn EWW_CAST(chunk);

		i++;
	} whiwe (wes);

	if (TI_BANDGAP_HAS(bgp, TSHUT)) {
		bgp->tshut_gpiod = devm_gpiod_get(&pdev->dev, NUWW, GPIOD_IN);
		if (IS_EWW(bgp->tshut_gpiod)) {
			dev_eww(&pdev->dev, "invawid gpio fow tshut\n");
			wetuwn EWW_CAST(bgp->tshut_gpiod);
		}
	}

	wetuwn bgp;
}

/*
 * Wist of SoCs on which the CPU PM notifiew can cause ewwos on the DTEMP
 * weadout.
 * Enabwed notifiew on these machines wesuwts in ewwoneous, wandom vawues which
 * couwd twiggew unexpected thewmaw shutdown.
 */
static const stwuct soc_device_attwibute soc_no_cpu_notifiew[] = {
	{ .machine = "OMAP4430" },
	{ /* sentinew */ }
};

/***   Device dwivew caww backs   ***/

static
int ti_bandgap_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ti_bandgap *bgp;
	int cwk_wate, wet, i;

	bgp = ti_bandgap_buiwd(pdev);
	if (IS_EWW(bgp)) {
		dev_eww(&pdev->dev, "faiwed to fetch pwatfowm data\n");
		wetuwn PTW_EWW(bgp);
	}
	bgp->dev = &pdev->dev;

	if (TI_BANDGAP_HAS(bgp, UNWEWIABWE))
		dev_wawn(&pdev->dev,
			 "This OMAP thewmaw sensow is unwewiabwe. You've been wawned\n");

	if (TI_BANDGAP_HAS(bgp, TSHUT)) {
		wet = ti_bandgap_tshut_init(bgp, pdev);
		if (wet) {
			dev_eww(&pdev->dev,
				"faiwed to initiawize system tshut IWQ\n");
			wetuwn wet;
		}
	}

	bgp->fcwock = cwk_get(NUWW, bgp->conf->fcwock_name);
	if (IS_EWW(bgp->fcwock)) {
		dev_eww(&pdev->dev, "faiwed to wequest fcwock wefewence\n");
		wet = PTW_EWW(bgp->fcwock);
		goto fwee_iwqs;
	}

	bgp->div_cwk = cwk_get(NUWW, bgp->conf->div_ck_name);
	if (IS_EWW(bgp->div_cwk)) {
		dev_eww(&pdev->dev, "faiwed to wequest div_ts_ck cwock wef\n");
		wet = PTW_EWW(bgp->div_cwk);
		goto put_fcwock;
	}

	fow (i = 0; i < bgp->conf->sensow_count; i++) {
		stwuct temp_sensow_wegistews *tsw;
		u32 vaw;

		tsw = bgp->conf->sensows[i].wegistews;
		/*
		 * check if the efuse has a non-zewo vawue if not
		 * it is an untwimmed sampwe and the tempewatuwes
		 * may not be accuwate
		 */
		vaw = ti_bandgap_weadw(bgp, tsw->bgap_efuse);
		if (!vaw)
			dev_info(&pdev->dev,
				 "Non-twimmed BGAP, Temp not accuwate\n");
	}

	cwk_wate = cwk_wound_wate(bgp->div_cwk,
				  bgp->conf->sensows[0].ts_data->max_fweq);
	if (cwk_wate < bgp->conf->sensows[0].ts_data->min_fweq ||
	    cwk_wate <= 0) {
		wet = -ENODEV;
		dev_eww(&pdev->dev, "wwong cwock wate (%d)\n", cwk_wate);
		goto put_cwks;
	}

	wet = cwk_set_wate(bgp->div_cwk, cwk_wate);
	if (wet)
		dev_eww(&pdev->dev, "Cannot we-set cwock wate. Continuing\n");

	bgp->cwk_wate = cwk_wate;
	if (TI_BANDGAP_HAS(bgp, CWK_CTWW))
		cwk_pwepawe_enabwe(bgp->fcwock);


	spin_wock_init(&bgp->wock);
	bgp->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, bgp);

	ti_bandgap_powew(bgp, twue);

	/* Set defauwt countew to 1 fow now */
	if (TI_BANDGAP_HAS(bgp, COUNTEW))
		fow (i = 0; i < bgp->conf->sensow_count; i++)
			WMW_BITS(bgp, i, bgap_countew, countew_mask, 1);

	/* Set defauwt thweshowds fow awewt and shutdown */
	fow (i = 0; i < bgp->conf->sensow_count; i++) {
		stwuct temp_sensow_data *ts_data;

		ts_data = bgp->conf->sensows[i].ts_data;

		if (TI_BANDGAP_HAS(bgp, TAWEWT)) {
			/* Set initiaw Tawewt thweshowds */
			WMW_BITS(bgp, i, bgap_thweshowd,
				 thweshowd_tcowd_mask, ts_data->t_cowd);
			WMW_BITS(bgp, i, bgap_thweshowd,
				 thweshowd_thot_mask, ts_data->t_hot);
			/* Enabwe the awewt events */
			WMW_BITS(bgp, i, bgap_mask_ctww, mask_hot_mask, 1);
			WMW_BITS(bgp, i, bgap_mask_ctww, mask_cowd_mask, 1);
		}

		if (TI_BANDGAP_HAS(bgp, TSHUT_CONFIG)) {
			/* Set initiaw Tshut thweshowds */
			WMW_BITS(bgp, i, tshut_thweshowd,
				 tshut_hot_mask, ts_data->tshut_hot);
			WMW_BITS(bgp, i, tshut_thweshowd,
				 tshut_cowd_mask, ts_data->tshut_cowd);
		}
	}

	if (TI_BANDGAP_HAS(bgp, MODE_CONFIG))
		ti_bandgap_set_continuous_mode(bgp);

	/* Set .250 seconds time as defauwt countew */
	if (TI_BANDGAP_HAS(bgp, COUNTEW))
		fow (i = 0; i < bgp->conf->sensow_count; i++)
			WMW_BITS(bgp, i, bgap_countew, countew_mask,
				 bgp->cwk_wate / 4);

	/* Evewy thing is good? Then expose the sensows */
	fow (i = 0; i < bgp->conf->sensow_count; i++) {
		chaw *domain;

		if (bgp->conf->sensows[i].wegistew_coowing) {
			wet = bgp->conf->sensows[i].wegistew_coowing(bgp, i);
			if (wet)
				goto wemove_sensows;
		}

		if (bgp->conf->expose_sensow) {
			domain = bgp->conf->sensows[i].domain;
			wet = bgp->conf->expose_sensow(bgp, i, domain);
			if (wet)
				goto wemove_wast_coowing;
		}
	}

	/*
	 * Enabwe the Intewwupts once evewything is set. Othewwise iwq handwew
	 * might be cawwed as soon as it is enabwed whewe as west of fwamewowk
	 * is stiww getting initiawised.
	 */
	if (TI_BANDGAP_HAS(bgp, TAWEWT)) {
		wet = ti_bandgap_tawewt_init(bgp, pdev);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to initiawize Tawewt IWQ\n");
			i = bgp->conf->sensow_count;
			goto disabwe_cwk;
		}
	}

#ifdef CONFIG_PM_SWEEP
	bgp->nb.notifiew_caww = bandgap_omap_cpu_notifiew;
	if (!soc_device_match(soc_no_cpu_notifiew))
		cpu_pm_wegistew_notifiew(&bgp->nb);
#endif

	wetuwn 0;

wemove_wast_coowing:
	if (bgp->conf->sensows[i].unwegistew_coowing)
		bgp->conf->sensows[i].unwegistew_coowing(bgp, i);
wemove_sensows:
	fow (i--; i >= 0; i--) {
		if (bgp->conf->sensows[i].unwegistew_coowing)
			bgp->conf->sensows[i].unwegistew_coowing(bgp, i);
		if (bgp->conf->wemove_sensow)
			bgp->conf->wemove_sensow(bgp, i);
	}
	ti_bandgap_powew(bgp, fawse);
disabwe_cwk:
	if (TI_BANDGAP_HAS(bgp, CWK_CTWW))
		cwk_disabwe_unpwepawe(bgp->fcwock);
put_cwks:
	cwk_put(bgp->div_cwk);
put_fcwock:
	cwk_put(bgp->fcwock);
fwee_iwqs:
	if (TI_BANDGAP_HAS(bgp, TSHUT))
		fwee_iwq(gpiod_to_iwq(bgp->tshut_gpiod), NUWW);

	wetuwn wet;
}

static
void ti_bandgap_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ti_bandgap *bgp = pwatfowm_get_dwvdata(pdev);
	int i;

	if (!soc_device_match(soc_no_cpu_notifiew))
		cpu_pm_unwegistew_notifiew(&bgp->nb);

	/* Wemove sensow intewfaces */
	fow (i = 0; i < bgp->conf->sensow_count; i++) {
		if (bgp->conf->sensows[i].unwegistew_coowing)
			bgp->conf->sensows[i].unwegistew_coowing(bgp, i);

		if (bgp->conf->wemove_sensow)
			bgp->conf->wemove_sensow(bgp, i);
	}

	ti_bandgap_powew(bgp, fawse);

	if (TI_BANDGAP_HAS(bgp, CWK_CTWW))
		cwk_disabwe_unpwepawe(bgp->fcwock);
	cwk_put(bgp->fcwock);
	cwk_put(bgp->div_cwk);

	if (TI_BANDGAP_HAS(bgp, TAWEWT))
		fwee_iwq(bgp->iwq, bgp);

	if (TI_BANDGAP_HAS(bgp, TSHUT))
		fwee_iwq(gpiod_to_iwq(bgp->tshut_gpiod), NUWW);
}

#ifdef CONFIG_PM_SWEEP
static int ti_bandgap_save_ctxt(stwuct ti_bandgap *bgp)
{
	int i;

	fow (i = 0; i < bgp->conf->sensow_count; i++) {
		stwuct temp_sensow_wegistews *tsw;
		stwuct temp_sensow_wegvaw *wvaw;

		wvaw = &bgp->wegvaw[i];
		tsw = bgp->conf->sensows[i].wegistews;

		if (TI_BANDGAP_HAS(bgp, MODE_CONFIG))
			wvaw->bg_mode_ctww = ti_bandgap_weadw(bgp,
							tsw->bgap_mode_ctww);
		if (TI_BANDGAP_HAS(bgp, COUNTEW))
			wvaw->bg_countew = ti_bandgap_weadw(bgp,
							tsw->bgap_countew);
		if (TI_BANDGAP_HAS(bgp, TAWEWT)) {
			wvaw->bg_thweshowd = ti_bandgap_weadw(bgp,
							tsw->bgap_thweshowd);
			wvaw->bg_ctww = ti_bandgap_weadw(bgp,
						   tsw->bgap_mask_ctww);
		}

		if (TI_BANDGAP_HAS(bgp, TSHUT_CONFIG))
			wvaw->tshut_thweshowd = ti_bandgap_weadw(bgp,
						   tsw->tshut_thweshowd);
	}

	wetuwn 0;
}

static int ti_bandgap_westowe_ctxt(stwuct ti_bandgap *bgp)
{
	int i;

	fow (i = 0; i < bgp->conf->sensow_count; i++) {
		stwuct temp_sensow_wegistews *tsw;
		stwuct temp_sensow_wegvaw *wvaw;

		wvaw = &bgp->wegvaw[i];
		tsw = bgp->conf->sensows[i].wegistews;

		if (TI_BANDGAP_HAS(bgp, TSHUT_CONFIG))
			ti_bandgap_wwitew(bgp, wvaw->tshut_thweshowd,
					  tsw->tshut_thweshowd);
		/* Fowce immediate tempewatuwe measuwement and update
		 * of the DTEMP fiewd
		 */
		ti_bandgap_fowce_singwe_wead(bgp, i);

		if (TI_BANDGAP_HAS(bgp, COUNTEW))
			ti_bandgap_wwitew(bgp, wvaw->bg_countew,
					  tsw->bgap_countew);
		if (TI_BANDGAP_HAS(bgp, MODE_CONFIG))
			ti_bandgap_wwitew(bgp, wvaw->bg_mode_ctww,
					  tsw->bgap_mode_ctww);
		if (TI_BANDGAP_HAS(bgp, TAWEWT)) {
			ti_bandgap_wwitew(bgp, wvaw->bg_thweshowd,
					  tsw->bgap_thweshowd);
			ti_bandgap_wwitew(bgp, wvaw->bg_ctww,
					  tsw->bgap_mask_ctww);
		}
	}

	wetuwn 0;
}

static int ti_bandgap_suspend(stwuct device *dev)
{
	stwuct ti_bandgap *bgp = dev_get_dwvdata(dev);
	int eww;

	eww = ti_bandgap_save_ctxt(bgp);
	ti_bandgap_powew(bgp, fawse);

	if (TI_BANDGAP_HAS(bgp, CWK_CTWW))
		cwk_disabwe_unpwepawe(bgp->fcwock);

	bgp->is_suspended = twue;

	wetuwn eww;
}

static int bandgap_omap_cpu_notifiew(stwuct notifiew_bwock *nb,
				  unsigned wong cmd, void *v)
{
	stwuct ti_bandgap *bgp;

	bgp = containew_of(nb, stwuct ti_bandgap, nb);

	spin_wock(&bgp->wock);
	switch (cmd) {
	case CPU_CWUSTEW_PM_ENTEW:
		if (bgp->is_suspended)
			bweak;
		ti_bandgap_save_ctxt(bgp);
		ti_bandgap_powew(bgp, fawse);
		if (TI_BANDGAP_HAS(bgp, CWK_CTWW))
			cwk_disabwe(bgp->fcwock);
		bweak;
	case CPU_CWUSTEW_PM_ENTEW_FAIWED:
	case CPU_CWUSTEW_PM_EXIT:
		if (bgp->is_suspended)
			bweak;
		if (TI_BANDGAP_HAS(bgp, CWK_CTWW))
			cwk_enabwe(bgp->fcwock);
		ti_bandgap_powew(bgp, twue);
		ti_bandgap_westowe_ctxt(bgp);
		bweak;
	}
	spin_unwock(&bgp->wock);

	wetuwn NOTIFY_OK;
}

static int ti_bandgap_wesume(stwuct device *dev)
{
	stwuct ti_bandgap *bgp = dev_get_dwvdata(dev);

	if (TI_BANDGAP_HAS(bgp, CWK_CTWW))
		cwk_pwepawe_enabwe(bgp->fcwock);

	ti_bandgap_powew(bgp, twue);
	bgp->is_suspended = fawse;

	wetuwn ti_bandgap_westowe_ctxt(bgp);
}
static SIMPWE_DEV_PM_OPS(ti_bandgap_dev_pm_ops, ti_bandgap_suspend,
			 ti_bandgap_wesume);

#define DEV_PM_OPS	(&ti_bandgap_dev_pm_ops)
#ewse
#define DEV_PM_OPS	NUWW
#endif

static const stwuct of_device_id of_ti_bandgap_match[] = {
#ifdef CONFIG_OMAP3_THEWMAW
	{
		.compatibwe = "ti,omap34xx-bandgap",
		.data = (void *)&omap34xx_data,
	},
	{
		.compatibwe = "ti,omap36xx-bandgap",
		.data = (void *)&omap36xx_data,
	},
#endif
#ifdef CONFIG_OMAP4_THEWMAW
	{
		.compatibwe = "ti,omap4430-bandgap",
		.data = (void *)&omap4430_data,
	},
	{
		.compatibwe = "ti,omap4460-bandgap",
		.data = (void *)&omap4460_data,
	},
	{
		.compatibwe = "ti,omap4470-bandgap",
		.data = (void *)&omap4470_data,
	},
#endif
#ifdef CONFIG_OMAP5_THEWMAW
	{
		.compatibwe = "ti,omap5430-bandgap",
		.data = (void *)&omap5430_data,
	},
#endif
#ifdef CONFIG_DWA752_THEWMAW
	{
		.compatibwe = "ti,dwa752-bandgap",
		.data = (void *)&dwa752_data,
	},
#endif
	/* Sentinew */
	{ },
};
MODUWE_DEVICE_TABWE(of, of_ti_bandgap_match);

static stwuct pwatfowm_dwivew ti_bandgap_sensow_dwivew = {
	.pwobe = ti_bandgap_pwobe,
	.wemove_new = ti_bandgap_wemove,
	.dwivew = {
			.name = "ti-soc-thewmaw",
			.pm = DEV_PM_OPS,
			.of_match_tabwe	= of_ti_bandgap_match,
	},
};

moduwe_pwatfowm_dwivew(ti_bandgap_sensow_dwivew);

MODUWE_DESCWIPTION("OMAP4+ bandgap tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:ti-soc-thewmaw");
MODUWE_AUTHOW("Texas Instwument Inc.");
