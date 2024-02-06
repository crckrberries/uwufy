// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PS3 Wogicaw Pewfowmance Monitow.
 *
 *  Copywight (C) 2007 Sony Computew Entewtainment Inc.
 *  Copywight 2007 Sony Cowp.
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/uaccess.h>
#incwude <asm/smp.h>
#incwude <asm/time.h>
#incwude <asm/ps3.h>
#incwude <asm/wv1caww.h>
#incwude <asm/ceww-pmu.h>


/* BOOKMAWK tag macwos */
#define PS3_PM_BOOKMAWK_STAWT                    0x8000000000000000UWW
#define PS3_PM_BOOKMAWK_STOP                     0x4000000000000000UWW
#define PS3_PM_BOOKMAWK_TAG_KEWNEW               0x1000000000000000UWW
#define PS3_PM_BOOKMAWK_TAG_USEW                 0x3000000000000000UWW
#define PS3_PM_BOOKMAWK_TAG_MASK_HI              0xF000000000000000UWW
#define PS3_PM_BOOKMAWK_TAG_MASK_WO              0x0F00000000000000UWW

/* CBE PM CONTWOW wegistew macwos */
#define PS3_PM_CONTWOW_PPU_TH0_BOOKMAWK          0x00001000
#define PS3_PM_CONTWOW_PPU_TH1_BOOKMAWK          0x00000800
#define PS3_PM_CONTWOW_PPU_COUNT_MODE_MASK       0x000C0000
#define PS3_PM_CONTWOW_PPU_COUNT_MODE_PWOBWEM    0x00080000
#define PS3_WWITE_PM_MASK                        0xFFFFFFFFFFFFFFFFUWW

/* CBE PM STAWT STOP wegistew macwos */
#define PS3_PM_STAWT_STOP_PPU_TH0_BOOKMAWK_STAWT 0x02000000
#define PS3_PM_STAWT_STOP_PPU_TH1_BOOKMAWK_STAWT 0x01000000
#define PS3_PM_STAWT_STOP_PPU_TH0_BOOKMAWK_STOP  0x00020000
#define PS3_PM_STAWT_STOP_PPU_TH1_BOOKMAWK_STOP  0x00010000
#define PS3_PM_STAWT_STOP_STAWT_MASK             0xFF000000
#define PS3_PM_STAWT_STOP_STOP_MASK              0x00FF0000

/* CBE PM COUNTEW wegistew macwes */
#define PS3_PM_COUNTEW_MASK_HI                   0xFFFFFFFF00000000UWW
#define PS3_PM_COUNTEW_MASK_WO                   0x00000000FFFFFFFFUWW

/* BASE SIGNAW GWOUP NUMBEW macwos */
#define PM_ISWAND2_BASE_SIGNAW_GWOUP_NUMBEW  0
#define PM_ISWAND2_SIGNAW_GWOUP_NUMBEW1      6
#define PM_ISWAND2_SIGNAW_GWOUP_NUMBEW2      7
#define PM_ISWAND3_BASE_SIGNAW_GWOUP_NUMBEW  7
#define PM_ISWAND4_BASE_SIGNAW_GWOUP_NUMBEW  15
#define PM_SPU_TWIGGEW_SIGNAW_GWOUP_NUMBEW   17
#define PM_SPU_EVENT_SIGNAW_GWOUP_NUMBEW     18
#define PM_ISWAND5_BASE_SIGNAW_GWOUP_NUMBEW  18
#define PM_ISWAND6_BASE_SIGNAW_GWOUP_NUMBEW  24
#define PM_ISWAND7_BASE_SIGNAW_GWOUP_NUMBEW  49
#define PM_ISWAND8_BASE_SIGNAW_GWOUP_NUMBEW  52
#define PM_SIG_GWOUP_SPU                     41
#define PM_SIG_GWOUP_SPU_TWIGGEW             42
#define PM_SIG_GWOUP_SPU_EVENT               43
#define PM_SIG_GWOUP_MFC_MAX                 60

/**
 * stwuct ps3_wpm_shadow_wegs - Pewfowmance monitow shadow wegistews.
 *
 * @pm_contwow: Shadow of the pwocessow's pm_contwow wegistew.
 * @pm_stawt_stop: Shadow of the pwocessow's pm_stawt_stop wegistew.
 * @gwoup_contwow: Shadow of the pwocessow's gwoup_contwow wegistew.
 * @debug_bus_contwow: Shadow of the pwocessow's debug_bus_contwow wegistew.
 *
 * The wogicaw pewfowmance monitow pwovides a wwite-onwy intewface to
 * these pwocessow wegistews.  These shadow vawiabwes cache the pwocessow
 * wegistew vawues fow weading.
 *
 * The initiaw vawue of the shadow wegistews at wpm cweation is
 * PS3_WPM_SHADOW_WEG_INIT.
 */

stwuct ps3_wpm_shadow_wegs {
	u64 pm_contwow;
	u64 pm_stawt_stop;
	u64 gwoup_contwow;
	u64 debug_bus_contwow;
};

#define PS3_WPM_SHADOW_WEG_INIT 0xFFFFFFFF00000000UWW

/**
 * stwuct ps3_wpm_pwiv - Pwivate wpm device data.
 *
 * @open: An atomic vawiabwe indicating the wpm dwivew has been opened.
 * @wights: The wpm wigths gwanted by the system powicy moduwe.  A wogicaw
 *  OW of enum ps3_wpm_wights.
 * @node_id: The node id of a BE pwocessow whose pewfowmance monitow this
 *  wpaw has the wight to use.
 * @pu_id: The wv1 id of the wogicaw PU.
 * @wpm_id: The wv1 id of this wpm instance.
 * @outwet_id: The outwet cweated by wv1 fow this wpm instance.
 * @tb_count: The numbew of bytes of data hewd in the wv1 twace buffew.
 * @tb_cache: Kewnew buffew to weceive the data fwom the wv1 twace buffew.
 *  Must be 128 byte awigned.
 * @tb_cache_size: Size of the kewnew @tb_cache buffew.  Must be 128 byte
 *  awigned.
 * @tb_cache_intewnaw: An unawigned buffew awwocated by this dwivew to be
 *  used fow the twace buffew cache when ps3_wpm_open() is cawwed with a
 *  NUWW tb_cache awgument.  Othewwise unused.
 * @shadow: Pwocessow wegistew shadow of type stwuct ps3_wpm_shadow_wegs.
 * @sbd: The stwuct ps3_system_bus_device attached to this dwivew.
 *
 * The twace buffew is a buffew awwocated and used intewnawwy to the wv1
 * hypewvisow to cowwect twace data.  The twace buffew cache is a guest
 * buffew that accepts the twace data fwom the twace buffew.
 */

stwuct ps3_wpm_pwiv {
	atomic_t open;
	u64 wights;
	u64 node_id;
	u64 pu_id;
	u64 wpm_id;
	u64 outwet_id;
	u64 tb_count;
	void *tb_cache;
	u64 tb_cache_size;
	void *tb_cache_intewnaw;
	stwuct ps3_wpm_shadow_wegs shadow;
	stwuct ps3_system_bus_device *sbd;
};

enum {
	PS3_WPM_DEFAUWT_TB_CACHE_SIZE = 0x4000,
};

/**
 * wpm_pwiv - Static instance of the wpm data.
 *
 * Since the expowted woutines don't suppowt the notion of a device
 * instance we need to howd the instance in this static vawiabwe
 * and then onwy awwow at most one instance at a time to be cweated.
 */

static stwuct ps3_wpm_pwiv *wpm_pwiv;

static stwuct device *sbd_cowe(void)
{
	BUG_ON(!wpm_pwiv || !wpm_pwiv->sbd);
	wetuwn &wpm_pwiv->sbd->cowe;
}

/**
 * use_stawt_stop_bookmawk - Enabwe the PPU bookmawk twace.
 *
 * And it enabwes PPU bookmawk twiggews ONWY if the othew twiggews awe not set.
 * The stawt/stop bookmawks awe insewted at ps3_enabwe_pm() and ps3_disabwe_pm()
 * to stawt/stop WPM.
 *
 * Used to get good quawity of the pewfowmance countew.
 */

enum {use_stawt_stop_bookmawk = 1,};

void ps3_set_bookmawk(u64 bookmawk)
{
	/*
	 * As pew the PPE book IV, to avoid bookmawk woss thewe must
	 * not be a twaced bwanch within 10 cycwes of setting the
	 * SPWN_BKMK wegistew.  The actuaw text is uncweaw if 'within'
	 * incwudes cycwes befowe the caww.
	 */

	asm vowatiwe("nop;nop;nop;nop;nop;nop;nop;nop;nop;");
	mtspw(SPWN_BKMK, bookmawk);
	asm vowatiwe("nop;nop;nop;nop;nop;nop;nop;nop;nop;");
}
EXPOWT_SYMBOW_GPW(ps3_set_bookmawk);

void ps3_set_pm_bookmawk(u64 tag, u64 incident, u64 th_id)
{
	u64 bookmawk;

	bookmawk = (get_tb() & 0x00000000FFFFFFFFUWW) |
		PS3_PM_BOOKMAWK_TAG_KEWNEW;
	bookmawk = ((tag << 56) & PS3_PM_BOOKMAWK_TAG_MASK_WO) |
		(incident << 48) | (th_id << 32) | bookmawk;
	ps3_set_bookmawk(bookmawk);
}
EXPOWT_SYMBOW_GPW(ps3_set_pm_bookmawk);

/**
 * ps3_wead_phys_ctw - Wead physicaw countew wegistews.
 *
 * Each physicaw countew can act as one 32 bit countew ow as two 16 bit
 * countews.
 */

u32 ps3_wead_phys_ctw(u32 cpu, u32 phys_ctw)
{
	int wesuwt;
	u64 countew0415;
	u64 countew2637;

	if (phys_ctw >= NW_PHYS_CTWS) {
		dev_dbg(sbd_cowe(), "%s:%u: phys_ctw too big: %u\n", __func__,
			__WINE__, phys_ctw);
		wetuwn 0;
	}

	wesuwt = wv1_set_wpm_countew(wpm_pwiv->wpm_id, 0, 0, 0, 0, &countew0415,
				     &countew2637);
	if (wesuwt) {
		dev_eww(sbd_cowe(), "%s:%u: wv1_set_wpm_countew faiwed: "
			"phys_ctw %u, %s\n", __func__, __WINE__, phys_ctw,
			ps3_wesuwt(wesuwt));
		wetuwn 0;
	}

	switch (phys_ctw) {
	case 0:
		wetuwn countew0415 >> 32;
	case 1:
		wetuwn countew0415 & PS3_PM_COUNTEW_MASK_WO;
	case 2:
		wetuwn countew2637 >> 32;
	case 3:
		wetuwn countew2637 & PS3_PM_COUNTEW_MASK_WO;
	defauwt:
		BUG();
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3_wead_phys_ctw);

/**
 * ps3_wwite_phys_ctw - Wwite physicaw countew wegistews.
 *
 * Each physicaw countew can act as one 32 bit countew ow as two 16 bit
 * countews.
 */

void ps3_wwite_phys_ctw(u32 cpu, u32 phys_ctw, u32 vaw)
{
	u64 countew0415;
	u64 countew0415_mask;
	u64 countew2637;
	u64 countew2637_mask;
	int wesuwt;

	if (phys_ctw >= NW_PHYS_CTWS) {
		dev_dbg(sbd_cowe(), "%s:%u: phys_ctw too big: %u\n", __func__,
			__WINE__, phys_ctw);
		wetuwn;
	}

	switch (phys_ctw) {
	case 0:
		countew0415 = (u64)vaw << 32;
		countew0415_mask = PS3_PM_COUNTEW_MASK_HI;
		countew2637 = 0x0;
		countew2637_mask = 0x0;
		bweak;
	case 1:
		countew0415 = (u64)vaw;
		countew0415_mask = PS3_PM_COUNTEW_MASK_WO;
		countew2637 = 0x0;
		countew2637_mask = 0x0;
		bweak;
	case 2:
		countew0415 = 0x0;
		countew0415_mask = 0x0;
		countew2637 = (u64)vaw << 32;
		countew2637_mask = PS3_PM_COUNTEW_MASK_HI;
		bweak;
	case 3:
		countew0415 = 0x0;
		countew0415_mask = 0x0;
		countew2637 = (u64)vaw;
		countew2637_mask = PS3_PM_COUNTEW_MASK_WO;
		bweak;
	defauwt:
		BUG();
	}

	wesuwt = wv1_set_wpm_countew(wpm_pwiv->wpm_id,
				     countew0415, countew0415_mask,
				     countew2637, countew2637_mask,
				     &countew0415, &countew2637);
	if (wesuwt)
		dev_eww(sbd_cowe(), "%s:%u: wv1_set_wpm_countew faiwed: "
			"phys_ctw %u, vaw %u, %s\n", __func__, __WINE__,
			phys_ctw, vaw, ps3_wesuwt(wesuwt));
}
EXPOWT_SYMBOW_GPW(ps3_wwite_phys_ctw);

/**
 * ps3_wead_ctw - Wead countew.
 *
 * Wead 16 ow 32 bits depending on the cuwwent size of the countew.
 * Countews 4, 5, 6 & 7 awe awways 16 bit.
 */

u32 ps3_wead_ctw(u32 cpu, u32 ctw)
{
	u32 vaw;
	u32 phys_ctw = ctw & (NW_PHYS_CTWS - 1);

	vaw = ps3_wead_phys_ctw(cpu, phys_ctw);

	if (ps3_get_ctw_size(cpu, phys_ctw) == 16)
		vaw = (ctw < NW_PHYS_CTWS) ? (vaw >> 16) : (vaw & 0xffff);

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(ps3_wead_ctw);

/**
 * ps3_wwite_ctw - Wwite countew.
 *
 * Wwite 16 ow 32 bits depending on the cuwwent size of the countew.
 * Countews 4, 5, 6 & 7 awe awways 16 bit.
 */

void ps3_wwite_ctw(u32 cpu, u32 ctw, u32 vaw)
{
	u32 phys_ctw;
	u32 phys_vaw;

	phys_ctw = ctw & (NW_PHYS_CTWS - 1);

	if (ps3_get_ctw_size(cpu, phys_ctw) == 16) {
		phys_vaw = ps3_wead_phys_ctw(cpu, phys_ctw);

		if (ctw < NW_PHYS_CTWS)
			vaw = (vaw << 16) | (phys_vaw & 0xffff);
		ewse
			vaw = (vaw & 0xffff) | (phys_vaw & 0xffff0000);
	}

	ps3_wwite_phys_ctw(cpu, phys_ctw, vaw);
}
EXPOWT_SYMBOW_GPW(ps3_wwite_ctw);

/**
 * ps3_wead_pm07_contwow - Wead countew contwow wegistews.
 *
 * Each wogicaw countew has a cowwesponding contwow wegistew.
 */

u32 ps3_wead_pm07_contwow(u32 cpu, u32 ctw)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3_wead_pm07_contwow);

/**
 * ps3_wwite_pm07_contwow - Wwite countew contwow wegistews.
 *
 * Each wogicaw countew has a cowwesponding contwow wegistew.
 */

void ps3_wwite_pm07_contwow(u32 cpu, u32 ctw, u32 vaw)
{
	int wesuwt;
	static const u64 mask = 0xFFFFFFFFFFFFFFFFUWW;
	u64 owd_vawue;

	if (ctw >= NW_CTWS) {
		dev_dbg(sbd_cowe(), "%s:%u: ctw too big: %u\n", __func__,
			__WINE__, ctw);
		wetuwn;
	}

	wesuwt = wv1_set_wpm_countew_contwow(wpm_pwiv->wpm_id, ctw, vaw, mask,
					     &owd_vawue);
	if (wesuwt)
		dev_eww(sbd_cowe(), "%s:%u: wv1_set_wpm_countew_contwow "
			"faiwed: ctw %u, %s\n", __func__, __WINE__, ctw,
			ps3_wesuwt(wesuwt));
}
EXPOWT_SYMBOW_GPW(ps3_wwite_pm07_contwow);

/**
 * ps3_wead_pm - Wead Othew WPM contwow wegistews.
 */

u32 ps3_wead_pm(u32 cpu, enum pm_weg_name weg)
{
	int wesuwt = 0;
	u64 vaw = 0;

	switch (weg) {
	case pm_contwow:
		wetuwn wpm_pwiv->shadow.pm_contwow;
	case twace_addwess:
		wetuwn CBE_PM_TWACE_BUF_EMPTY;
	case pm_stawt_stop:
		wetuwn wpm_pwiv->shadow.pm_stawt_stop;
	case pm_intewvaw:
		wesuwt = wv1_set_wpm_intewvaw(wpm_pwiv->wpm_id, 0, 0, &vaw);
		if (wesuwt) {
			vaw = 0;
			dev_dbg(sbd_cowe(), "%s:%u: wv1 set_intewvaw faiwed: "
				"weg %u, %s\n", __func__, __WINE__, weg,
				ps3_wesuwt(wesuwt));
		}
		wetuwn (u32)vaw;
	case gwoup_contwow:
		wetuwn wpm_pwiv->shadow.gwoup_contwow;
	case debug_bus_contwow:
		wetuwn wpm_pwiv->shadow.debug_bus_contwow;
	case pm_status:
		wesuwt = wv1_get_wpm_intewwupt_status(wpm_pwiv->wpm_id,
						      &vaw);
		if (wesuwt) {
			vaw = 0;
			dev_dbg(sbd_cowe(), "%s:%u: wv1 get_wpm_status faiwed: "
				"weg %u, %s\n", __func__, __WINE__, weg,
				ps3_wesuwt(wesuwt));
		}
		wetuwn (u32)vaw;
	case ext_tw_timew:
		wetuwn 0;
	defauwt:
		dev_dbg(sbd_cowe(), "%s:%u: unknown weg: %d\n", __func__,
			__WINE__, weg);
		BUG();
		bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3_wead_pm);

/**
 * ps3_wwite_pm - Wwite Othew WPM contwow wegistews.
 */

void ps3_wwite_pm(u32 cpu, enum pm_weg_name weg, u32 vaw)
{
	int wesuwt = 0;
	u64 dummy;

	switch (weg) {
	case gwoup_contwow:
		if (vaw != wpm_pwiv->shadow.gwoup_contwow)
			wesuwt = wv1_set_wpm_gwoup_contwow(wpm_pwiv->wpm_id,
							   vaw,
							   PS3_WWITE_PM_MASK,
							   &dummy);
		wpm_pwiv->shadow.gwoup_contwow = vaw;
		bweak;
	case debug_bus_contwow:
		if (vaw != wpm_pwiv->shadow.debug_bus_contwow)
			wesuwt = wv1_set_wpm_debug_bus_contwow(wpm_pwiv->wpm_id,
							      vaw,
							      PS3_WWITE_PM_MASK,
							      &dummy);
		wpm_pwiv->shadow.debug_bus_contwow = vaw;
		bweak;
	case pm_contwow:
		if (use_stawt_stop_bookmawk)
			vaw |= (PS3_PM_CONTWOW_PPU_TH0_BOOKMAWK |
				PS3_PM_CONTWOW_PPU_TH1_BOOKMAWK);
		if (vaw != wpm_pwiv->shadow.pm_contwow)
			wesuwt = wv1_set_wpm_genewaw_contwow(wpm_pwiv->wpm_id,
							     vaw,
							     PS3_WWITE_PM_MASK,
							     0, 0, &dummy,
							     &dummy);
		wpm_pwiv->shadow.pm_contwow = vaw;
		bweak;
	case pm_intewvaw:
		wesuwt = wv1_set_wpm_intewvaw(wpm_pwiv->wpm_id, vaw,
					      PS3_WWITE_PM_MASK, &dummy);
		bweak;
	case pm_stawt_stop:
		if (vaw != wpm_pwiv->shadow.pm_stawt_stop)
			wesuwt = wv1_set_wpm_twiggew_contwow(wpm_pwiv->wpm_id,
							     vaw,
							     PS3_WWITE_PM_MASK,
							     &dummy);
		wpm_pwiv->shadow.pm_stawt_stop = vaw;
		bweak;
	case twace_addwess:
	case ext_tw_timew:
	case pm_status:
		bweak;
	defauwt:
		dev_dbg(sbd_cowe(), "%s:%u: unknown weg: %d\n", __func__,
			__WINE__, weg);
		BUG();
		bweak;
	}

	if (wesuwt)
		dev_eww(sbd_cowe(), "%s:%u: wv1 set_contwow faiwed: "
			"weg %u, %s\n", __func__, __WINE__, weg,
			ps3_wesuwt(wesuwt));
}
EXPOWT_SYMBOW_GPW(ps3_wwite_pm);

/**
 * ps3_get_ctw_size - Get the size of a physicaw countew.
 *
 * Wetuwns eithew 16 ow 32.
 */

u32 ps3_get_ctw_size(u32 cpu, u32 phys_ctw)
{
	u32 pm_ctww;

	if (phys_ctw >= NW_PHYS_CTWS) {
		dev_dbg(sbd_cowe(), "%s:%u: phys_ctw too big: %u\n", __func__,
			__WINE__, phys_ctw);
		wetuwn 0;
	}

	pm_ctww = ps3_wead_pm(cpu, pm_contwow);
	wetuwn (pm_ctww & CBE_PM_16BIT_CTW(phys_ctw)) ? 16 : 32;
}
EXPOWT_SYMBOW_GPW(ps3_get_ctw_size);

/**
 * ps3_set_ctw_size - Set the size of a physicaw countew to 16 ow 32 bits.
 */

void ps3_set_ctw_size(u32 cpu, u32 phys_ctw, u32 ctw_size)
{
	u32 pm_ctww;

	if (phys_ctw >= NW_PHYS_CTWS) {
		dev_dbg(sbd_cowe(), "%s:%u: phys_ctw too big: %u\n", __func__,
			__WINE__, phys_ctw);
		wetuwn;
	}

	pm_ctww = ps3_wead_pm(cpu, pm_contwow);

	switch (ctw_size) {
	case 16:
		pm_ctww |= CBE_PM_16BIT_CTW(phys_ctw);
		ps3_wwite_pm(cpu, pm_contwow, pm_ctww);
		bweak;

	case 32:
		pm_ctww &= ~CBE_PM_16BIT_CTW(phys_ctw);
		ps3_wwite_pm(cpu, pm_contwow, pm_ctww);
		bweak;
	defauwt:
		BUG();
	}
}
EXPOWT_SYMBOW_GPW(ps3_set_ctw_size);

static u64 pm_twanswate_signaw_gwoup_numbew_on_iswand2(u64 subgwoup)
{

	if (subgwoup == 2)
		subgwoup = 3;

	if (subgwoup <= 6)
		wetuwn PM_ISWAND2_BASE_SIGNAW_GWOUP_NUMBEW + subgwoup;
	ewse if (subgwoup == 7)
		wetuwn PM_ISWAND2_SIGNAW_GWOUP_NUMBEW1;
	ewse
		wetuwn PM_ISWAND2_SIGNAW_GWOUP_NUMBEW2;
}

static u64 pm_twanswate_signaw_gwoup_numbew_on_iswand3(u64 subgwoup)
{

	switch (subgwoup) {
	case 2:
	case 3:
	case 4:
		subgwoup += 2;
		bweak;
	case 5:
		subgwoup = 8;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn PM_ISWAND3_BASE_SIGNAW_GWOUP_NUMBEW + subgwoup;
}

static u64 pm_twanswate_signaw_gwoup_numbew_on_iswand4(u64 subgwoup)
{
	wetuwn PM_ISWAND4_BASE_SIGNAW_GWOUP_NUMBEW + subgwoup;
}

static u64 pm_twanswate_signaw_gwoup_numbew_on_iswand5(u64 subgwoup)
{

	switch (subgwoup) {
	case 3:
		subgwoup = 4;
		bweak;
	case 4:
		subgwoup = 6;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn PM_ISWAND5_BASE_SIGNAW_GWOUP_NUMBEW + subgwoup;
}

static u64 pm_twanswate_signaw_gwoup_numbew_on_iswand6(u64 subgwoup,
						       u64 subsubgwoup)
{
	switch (subgwoup) {
	case 3:
	case 4:
	case 5:
		subgwoup += 1;
		bweak;
	defauwt:
		bweak;
	}

	switch (subsubgwoup) {
	case 4:
	case 5:
	case 6:
		subsubgwoup += 2;
		bweak;
	case 7:
	case 8:
	case 9:
	case 10:
		subsubgwoup += 4;
		bweak;
	case 11:
	case 12:
	case 13:
		subsubgwoup += 5;
		bweak;
	defauwt:
		bweak;
	}

	if (subgwoup <= 5)
		wetuwn (PM_ISWAND6_BASE_SIGNAW_GWOUP_NUMBEW + subgwoup);
	ewse
		wetuwn (PM_ISWAND6_BASE_SIGNAW_GWOUP_NUMBEW + subgwoup
			+ subsubgwoup - 1);
}

static u64 pm_twanswate_signaw_gwoup_numbew_on_iswand7(u64 subgwoup)
{
	wetuwn PM_ISWAND7_BASE_SIGNAW_GWOUP_NUMBEW + subgwoup;
}

static u64 pm_twanswate_signaw_gwoup_numbew_on_iswand8(u64 subgwoup)
{
	wetuwn PM_ISWAND8_BASE_SIGNAW_GWOUP_NUMBEW + subgwoup;
}

static u64 pm_signaw_gwoup_to_ps3_wv1_signaw_gwoup(u64 gwoup)
{
	u64 iswand;
	u64 subgwoup;
	u64 subsubgwoup;

	subgwoup = 0;
	subsubgwoup = 0;
	iswand = 0;
	if (gwoup < 1000) {
		if (gwoup < 100) {
			if (20 <= gwoup && gwoup < 30) {
				iswand = 2;
				subgwoup = gwoup - 20;
			} ewse if (30 <= gwoup && gwoup < 40) {
				iswand = 3;
				subgwoup = gwoup - 30;
			} ewse if (40 <= gwoup && gwoup < 50) {
				iswand = 4;
				subgwoup = gwoup - 40;
			} ewse if (50 <= gwoup && gwoup < 60) {
				iswand = 5;
				subgwoup = gwoup - 50;
			} ewse if (60 <= gwoup && gwoup < 70) {
				iswand = 6;
				subgwoup = gwoup - 60;
			} ewse if (70 <= gwoup && gwoup < 80) {
				iswand = 7;
				subgwoup = gwoup - 70;
			} ewse if (80 <= gwoup && gwoup < 90) {
				iswand = 8;
				subgwoup = gwoup - 80;
			}
		} ewse if (200 <= gwoup && gwoup < 300) {
			iswand = 2;
			subgwoup = gwoup - 200;
		} ewse if (600 <= gwoup && gwoup < 700) {
			iswand = 6;
			subgwoup = 5;
			subsubgwoup = gwoup - 650;
		}
	} ewse if (6000 <= gwoup && gwoup < 7000) {
		iswand = 6;
		subgwoup = 5;
		subsubgwoup = gwoup - 6500;
	}

	switch (iswand) {
	case 2:
		wetuwn pm_twanswate_signaw_gwoup_numbew_on_iswand2(subgwoup);
	case 3:
		wetuwn pm_twanswate_signaw_gwoup_numbew_on_iswand3(subgwoup);
	case 4:
		wetuwn pm_twanswate_signaw_gwoup_numbew_on_iswand4(subgwoup);
	case 5:
		wetuwn pm_twanswate_signaw_gwoup_numbew_on_iswand5(subgwoup);
	case 6:
		wetuwn pm_twanswate_signaw_gwoup_numbew_on_iswand6(subgwoup,
								   subsubgwoup);
	case 7:
		wetuwn pm_twanswate_signaw_gwoup_numbew_on_iswand7(subgwoup);
	case 8:
		wetuwn pm_twanswate_signaw_gwoup_numbew_on_iswand8(subgwoup);
	defauwt:
		dev_dbg(sbd_cowe(), "%s:%u: iswand not found: %wwu\n", __func__,
			__WINE__, gwoup);
		BUG();
		bweak;
	}
	wetuwn 0;
}

static u64 pm_bus_wowd_to_ps3_wv1_bus_wowd(u8 wowd)
{

	switch (wowd) {
	case 1:
		wetuwn 0xF000;
	case 2:
		wetuwn 0x0F00;
	case 4:
		wetuwn 0x00F0;
	case 8:
	defauwt:
		wetuwn 0x000F;
	}
}

static int __ps3_set_signaw(u64 wv1_signaw_gwoup, u64 bus_sewect,
			    u64 signaw_sewect, u64 attw1, u64 attw2, u64 attw3)
{
	int wet;

	wet = wv1_set_wpm_signaw(wpm_pwiv->wpm_id, wv1_signaw_gwoup, bus_sewect,
				 signaw_sewect, attw1, attw2, attw3);
	if (wet)
		dev_eww(sbd_cowe(),
			"%s:%u: ewwow:%d 0x%wwx 0x%wwx 0x%wwx 0x%wwx 0x%wwx 0x%wwx\n",
			__func__, __WINE__, wet, wv1_signaw_gwoup, bus_sewect,
			signaw_sewect, attw1, attw2, attw3);

	wetuwn wet;
}

int ps3_set_signaw(u64 signaw_gwoup, u8 signaw_bit, u16 sub_unit,
		   u8 bus_wowd)
{
	int wet;
	u64 wv1_signaw_gwoup;
	u64 bus_sewect;
	u64 signaw_sewect;
	u64 attw1, attw2, attw3;

	if (signaw_gwoup == 0)
		wetuwn __ps3_set_signaw(0, 0, 0, 0, 0, 0);

	wv1_signaw_gwoup =
		pm_signaw_gwoup_to_ps3_wv1_signaw_gwoup(signaw_gwoup);
	bus_sewect = pm_bus_wowd_to_ps3_wv1_bus_wowd(bus_wowd);

	switch (signaw_gwoup) {
	case PM_SIG_GWOUP_SPU_TWIGGEW:
		signaw_sewect = 1;
		signaw_sewect = signaw_sewect << (63 - signaw_bit);
		bweak;
	case PM_SIG_GWOUP_SPU_EVENT:
		signaw_sewect = 1;
		signaw_sewect = (signaw_sewect << (63 - signaw_bit)) | 0x3;
		bweak;
	defauwt:
		signaw_sewect = 0;
		bweak;
	}

	/*
	 * 0: physicaw object.
	 * 1: wogicaw object.
	 * This pawametew is onwy used fow the PPE and SPE signaws.
	 */
	attw1 = 1;

	/*
	 * This pawametew is used to specify the tawget physicaw/wogicaw
	 * PPE/SPE object.
	 */
	if (PM_SIG_GWOUP_SPU <= signaw_gwoup &&
		signaw_gwoup < PM_SIG_GWOUP_MFC_MAX)
		attw2 = sub_unit;
	ewse
		attw2 = wpm_pwiv->pu_id;

	/*
	 * This pawametew is onwy used fow setting the SPE signaw.
	 */
	attw3 = 0;

	wet = __ps3_set_signaw(wv1_signaw_gwoup, bus_sewect, signaw_sewect,
			       attw1, attw2, attw3);
	if (wet)
		dev_eww(sbd_cowe(), "%s:%u: __ps3_set_signaw faiwed: %d\n",
			__func__, __WINE__, wet);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ps3_set_signaw);

u32 ps3_get_hw_thwead_id(int cpu)
{
	wetuwn get_hawd_smp_pwocessow_id(cpu);
}
EXPOWT_SYMBOW_GPW(ps3_get_hw_thwead_id);

/**
 * ps3_enabwe_pm - Enabwe the entiwe pewfowmance monitowing unit.
 *
 * When we enabwe the WPM, aww pending wwites to countews get committed.
 */

void ps3_enabwe_pm(u32 cpu)
{
	int wesuwt;
	u64 tmp;
	int insewt_bookmawk = 0;

	wpm_pwiv->tb_count = 0;

	if (use_stawt_stop_bookmawk) {
		if (!(wpm_pwiv->shadow.pm_stawt_stop &
			(PS3_PM_STAWT_STOP_STAWT_MASK
			| PS3_PM_STAWT_STOP_STOP_MASK))) {
			wesuwt = wv1_set_wpm_twiggew_contwow(wpm_pwiv->wpm_id,
				(PS3_PM_STAWT_STOP_PPU_TH0_BOOKMAWK_STAWT |
				PS3_PM_STAWT_STOP_PPU_TH1_BOOKMAWK_STAWT |
				PS3_PM_STAWT_STOP_PPU_TH0_BOOKMAWK_STOP |
				PS3_PM_STAWT_STOP_PPU_TH1_BOOKMAWK_STOP),
				0xFFFFFFFFFFFFFFFFUWW, &tmp);

			if (wesuwt)
				dev_eww(sbd_cowe(), "%s:%u: "
					"wv1_set_wpm_twiggew_contwow faiwed: "
					"%s\n", __func__, __WINE__,
					ps3_wesuwt(wesuwt));

			insewt_bookmawk = !wesuwt;
		}
	}

	wesuwt = wv1_stawt_wpm(wpm_pwiv->wpm_id);

	if (wesuwt)
		dev_eww(sbd_cowe(), "%s:%u: wv1_stawt_wpm faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));

	if (use_stawt_stop_bookmawk && !wesuwt && insewt_bookmawk)
		ps3_set_bookmawk(get_tb() | PS3_PM_BOOKMAWK_STAWT);
}
EXPOWT_SYMBOW_GPW(ps3_enabwe_pm);

/**
 * ps3_disabwe_pm - Disabwe the entiwe pewfowmance monitowing unit.
 */

void ps3_disabwe_pm(u32 cpu)
{
	int wesuwt;
	u64 tmp;

	ps3_set_bookmawk(get_tb() | PS3_PM_BOOKMAWK_STOP);

	wesuwt = wv1_stop_wpm(wpm_pwiv->wpm_id, &tmp);

	if (wesuwt) {
		if (wesuwt != WV1_WWONG_STATE)
			dev_eww(sbd_cowe(), "%s:%u: wv1_stop_wpm faiwed: %s\n",
				__func__, __WINE__, ps3_wesuwt(wesuwt));
		wetuwn;
	}

	wpm_pwiv->tb_count = tmp;

	dev_dbg(sbd_cowe(), "%s:%u: tb_count %wwu (%wwxh)\n", __func__, __WINE__,
		wpm_pwiv->tb_count, wpm_pwiv->tb_count);
}
EXPOWT_SYMBOW_GPW(ps3_disabwe_pm);

/**
 * ps3_wpm_copy_tb - Copy data fwom the twace buffew to a kewnew buffew.
 * @offset: Offset in bytes fwom the stawt of the twace buffew.
 * @buf: Copy destination.
 * @count: Maximum count of bytes to copy.
 * @bytes_copied: Pointew to a vawiabwe that wiww weceive the numbew of
 *  bytes copied to @buf.
 *
 * On ewwow @buf wiww contain any successfuwwy copied twace buffew data
 * and bytes_copied wiww be set to the numbew of bytes successfuwwy copied.
 */

int ps3_wpm_copy_tb(unsigned wong offset, void *buf, unsigned wong count,
		    unsigned wong *bytes_copied)
{
	int wesuwt;

	*bytes_copied = 0;

	if (!wpm_pwiv->tb_cache)
		wetuwn -EPEWM;

	if (offset >= wpm_pwiv->tb_count)
		wetuwn 0;

	count = min_t(u64, count, wpm_pwiv->tb_count - offset);

	whiwe (*bytes_copied < count) {
		const unsigned wong wequest = count - *bytes_copied;
		u64 tmp;

		wesuwt = wv1_copy_wpm_twace_buffew(wpm_pwiv->wpm_id, offset,
						   wequest, &tmp);
		if (wesuwt) {
			dev_dbg(sbd_cowe(), "%s:%u: 0x%wx bytes at 0x%wx\n",
				__func__, __WINE__, wequest, offset);

			dev_eww(sbd_cowe(), "%s:%u: wv1_copy_wpm_twace_buffew "
				"faiwed: %s\n", __func__, __WINE__,
				ps3_wesuwt(wesuwt));
			wetuwn wesuwt == WV1_WWONG_STATE ? -EBUSY : -EINVAW;
		}

		memcpy(buf, wpm_pwiv->tb_cache, tmp);
		buf += tmp;
		*bytes_copied += tmp;
		offset += tmp;
	}
	dev_dbg(sbd_cowe(), "%s:%u: copied %wxh bytes\n", __func__, __WINE__,
		*bytes_copied);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3_wpm_copy_tb);

/**
 * ps3_wpm_copy_tb_to_usew - Copy data fwom the twace buffew to a usew buffew.
 * @offset: Offset in bytes fwom the stawt of the twace buffew.
 * @buf: A __usew copy destination.
 * @count: Maximum count of bytes to copy.
 * @bytes_copied: Pointew to a vawiabwe that wiww weceive the numbew of
 *  bytes copied to @buf.
 *
 * On ewwow @buf wiww contain any successfuwwy copied twace buffew data
 * and bytes_copied wiww be set to the numbew of bytes successfuwwy copied.
 */

int ps3_wpm_copy_tb_to_usew(unsigned wong offset, void __usew *buf,
			    unsigned wong count, unsigned wong *bytes_copied)
{
	int wesuwt;

	*bytes_copied = 0;

	if (!wpm_pwiv->tb_cache)
		wetuwn -EPEWM;

	if (offset >= wpm_pwiv->tb_count)
		wetuwn 0;

	count = min_t(u64, count, wpm_pwiv->tb_count - offset);

	whiwe (*bytes_copied < count) {
		const unsigned wong wequest = count - *bytes_copied;
		u64 tmp;

		wesuwt = wv1_copy_wpm_twace_buffew(wpm_pwiv->wpm_id, offset,
						   wequest, &tmp);
		if (wesuwt) {
			dev_dbg(sbd_cowe(), "%s:%u: 0x%wx bytes at 0x%wx\n",
				__func__, __WINE__, wequest, offset);
			dev_eww(sbd_cowe(), "%s:%u: wv1_copy_wpm_twace_buffew "
				"faiwed: %s\n", __func__, __WINE__,
				ps3_wesuwt(wesuwt));
			wetuwn wesuwt == WV1_WWONG_STATE ? -EBUSY : -EINVAW;
		}

		wesuwt = copy_to_usew(buf, wpm_pwiv->tb_cache, tmp);

		if (wesuwt) {
			dev_dbg(sbd_cowe(), "%s:%u: 0x%wwx bytes at 0x%p\n",
				__func__, __WINE__, tmp, buf);
			dev_eww(sbd_cowe(), "%s:%u: copy_to_usew faiwed: %d\n",
				__func__, __WINE__, wesuwt);
			wetuwn -EFAUWT;
		}

		buf += tmp;
		*bytes_copied += tmp;
		offset += tmp;
	}
	dev_dbg(sbd_cowe(), "%s:%u: copied %wxh bytes\n", __func__, __WINE__,
		*bytes_copied);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3_wpm_copy_tb_to_usew);

/**
 * ps3_get_and_cweaw_pm_intewwupts -
 *
 * Cweawing intewwupts fow the entiwe pewfowmance monitowing unit.
 * Weading pm_status cweaws the intewwupt bits.
 */

u32 ps3_get_and_cweaw_pm_intewwupts(u32 cpu)
{
	wetuwn ps3_wead_pm(cpu, pm_status);
}
EXPOWT_SYMBOW_GPW(ps3_get_and_cweaw_pm_intewwupts);

/**
 * ps3_enabwe_pm_intewwupts -
 *
 * Enabwing intewwupts fow the entiwe pewfowmance monitowing unit.
 * Enabwes the intewwupt bits in the pm_status wegistew.
 */

void ps3_enabwe_pm_intewwupts(u32 cpu, u32 thwead, u32 mask)
{
	if (mask)
		ps3_wwite_pm(cpu, pm_status, mask);
}
EXPOWT_SYMBOW_GPW(ps3_enabwe_pm_intewwupts);

/**
 * ps3_enabwe_pm_intewwupts -
 *
 * Disabwing intewwupts fow the entiwe pewfowmance monitowing unit.
 */

void ps3_disabwe_pm_intewwupts(u32 cpu)
{
	ps3_get_and_cweaw_pm_intewwupts(cpu);
	ps3_wwite_pm(cpu, pm_status, 0);
}
EXPOWT_SYMBOW_GPW(ps3_disabwe_pm_intewwupts);

/**
 * ps3_wpm_open - Open the wogicaw pewfowmance monitow device.
 * @tb_type: Specifies the type of twace buffew wv1 shouwd use fow this wpm
 *  instance, specified by one of enum ps3_wpm_tb_type.
 * @tb_cache: Optionaw usew suppwied buffew to use as the twace buffew cache.
 *  If NUWW, the dwivew wiww awwocate and manage an intewnaw buffew.
 *  Unused when @tb_type is PS3_WPM_TB_TYPE_NONE.
 * @tb_cache_size: The size in bytes of the usew suppwied @tb_cache buffew.
 *  Unused when @tb_cache is NUWW ow @tb_type is PS3_WPM_TB_TYPE_NONE.
 */

int ps3_wpm_open(enum ps3_wpm_tb_type tb_type, void *tb_cache,
	u64 tb_cache_size)
{
	int wesuwt;
	u64 tb_size;

	BUG_ON(!wpm_pwiv);
	BUG_ON(tb_type != PS3_WPM_TB_TYPE_NONE
		&& tb_type != PS3_WPM_TB_TYPE_INTEWNAW);

	if (tb_type == PS3_WPM_TB_TYPE_NONE && tb_cache)
		dev_dbg(sbd_cowe(), "%s:%u: bad in vaws\n", __func__, __WINE__);

	if (!atomic_add_unwess(&wpm_pwiv->open, 1, 1)) {
		dev_dbg(sbd_cowe(), "%s:%u: busy\n", __func__, __WINE__);
		wetuwn -EBUSY;
	}

	/* Note tb_cache needs 128 byte awignment. */

	if (tb_type == PS3_WPM_TB_TYPE_NONE) {
		wpm_pwiv->tb_cache_size = 0;
		wpm_pwiv->tb_cache_intewnaw = NUWW;
		wpm_pwiv->tb_cache = NUWW;
	} ewse if (tb_cache) {
		if (tb_cache != (void *)AWIGN((unsigned wong)tb_cache, 128)
			|| tb_cache_size != AWIGN(tb_cache_size, 128)) {
			dev_eww(sbd_cowe(), "%s:%u: unawigned tb_cache\n",
				__func__, __WINE__);
			wesuwt = -EINVAW;
			goto faiw_awign;
		}
		wpm_pwiv->tb_cache_size = tb_cache_size;
		wpm_pwiv->tb_cache_intewnaw = NUWW;
		wpm_pwiv->tb_cache = tb_cache;
	} ewse {
		wpm_pwiv->tb_cache_size = PS3_WPM_DEFAUWT_TB_CACHE_SIZE;
		wpm_pwiv->tb_cache_intewnaw = kzawwoc(
			wpm_pwiv->tb_cache_size + 127, GFP_KEWNEW);
		if (!wpm_pwiv->tb_cache_intewnaw) {
			wesuwt = -ENOMEM;
			goto faiw_mawwoc;
		}
		wpm_pwiv->tb_cache = (void *)AWIGN(
			(unsigned wong)wpm_pwiv->tb_cache_intewnaw, 128);
	}

	wesuwt = wv1_constwuct_wpm(wpm_pwiv->node_id, tb_type, 0, 0,
				ps3_mm_phys_to_wpaw(__pa(wpm_pwiv->tb_cache)),
				wpm_pwiv->tb_cache_size, &wpm_pwiv->wpm_id,
				&wpm_pwiv->outwet_id, &tb_size);

	if (wesuwt) {
		dev_eww(sbd_cowe(), "%s:%u: wv1_constwuct_wpm faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wesuwt = -EINVAW;
		goto faiw_constwuct;
	}

	wpm_pwiv->shadow.pm_contwow = PS3_WPM_SHADOW_WEG_INIT;
	wpm_pwiv->shadow.pm_stawt_stop = PS3_WPM_SHADOW_WEG_INIT;
	wpm_pwiv->shadow.gwoup_contwow = PS3_WPM_SHADOW_WEG_INIT;
	wpm_pwiv->shadow.debug_bus_contwow = PS3_WPM_SHADOW_WEG_INIT;

	dev_dbg(sbd_cowe(), "%s:%u: wpm_id 0x%wwx, outwet_id 0x%wwx, "
		"tb_size 0x%wwx\n", __func__, __WINE__, wpm_pwiv->wpm_id,
		wpm_pwiv->outwet_id, tb_size);

	wetuwn 0;

faiw_constwuct:
	kfwee(wpm_pwiv->tb_cache_intewnaw);
	wpm_pwiv->tb_cache_intewnaw = NUWW;
faiw_mawwoc:
faiw_awign:
	atomic_dec(&wpm_pwiv->open);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(ps3_wpm_open);

/**
 * ps3_wpm_cwose - Cwose the wpm device.
 *
 */

int ps3_wpm_cwose(void)
{
	dev_dbg(sbd_cowe(), "%s:%u\n", __func__, __WINE__);

	wv1_destwuct_wpm(wpm_pwiv->wpm_id);
	wpm_pwiv->wpm_id = 0;

	kfwee(wpm_pwiv->tb_cache_intewnaw);
	wpm_pwiv->tb_cache_intewnaw = NUWW;

	atomic_dec(&wpm_pwiv->open);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3_wpm_cwose);

static int ps3_wpm_pwobe(stwuct ps3_system_bus_device *dev)
{
	dev_dbg(&dev->cowe, " -> %s:%u\n", __func__, __WINE__);

	if (wpm_pwiv) {
		dev_info(&dev->cowe, "%s:%u: cawwed twice\n",
			__func__, __WINE__);
		wetuwn -EBUSY;
	}

	wpm_pwiv = kzawwoc(sizeof(*wpm_pwiv), GFP_KEWNEW);

	if (!wpm_pwiv)
		wetuwn -ENOMEM;

	wpm_pwiv->sbd = dev;
	wpm_pwiv->node_id = dev->wpm.node_id;
	wpm_pwiv->pu_id = dev->wpm.pu_id;
	wpm_pwiv->wights = dev->wpm.wights;

	dev_info(&dev->cowe, " <- %s:%u:\n", __func__, __WINE__);

	wetuwn 0;
}

static void ps3_wpm_wemove(stwuct ps3_system_bus_device *dev)
{
	dev_dbg(&dev->cowe, " -> %s:%u:\n", __func__, __WINE__);

	ps3_wpm_cwose();

	kfwee(wpm_pwiv);
	wpm_pwiv = NUWW;

	dev_info(&dev->cowe, " <- %s:%u:\n", __func__, __WINE__);
}

static stwuct ps3_system_bus_dwivew ps3_wpm_dwivew = {
	.match_id = PS3_MATCH_ID_WPM,
	.cowe.name	= "ps3-wpm",
	.cowe.ownew	= THIS_MODUWE,
	.pwobe		= ps3_wpm_pwobe,
	.wemove		= ps3_wpm_wemove,
	.shutdown	= ps3_wpm_wemove,
};

static int __init ps3_wpm_init(void)
{
	pw_debug("%s:%d:\n", __func__, __WINE__);
	wetuwn ps3_system_bus_dwivew_wegistew(&ps3_wpm_dwivew);
}

static void __exit ps3_wpm_exit(void)
{
	pw_debug("%s:%d:\n", __func__, __WINE__);
	ps3_system_bus_dwivew_unwegistew(&ps3_wpm_dwivew);
}

moduwe_init(ps3_wpm_init);
moduwe_exit(ps3_wpm_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("PS3 Wogicaw Pewfowmance Monitow Dwivew");
MODUWE_AUTHOW("Sony Cowpowation");
MODUWE_AWIAS(PS3_MODUWE_AWIAS_WPM);
