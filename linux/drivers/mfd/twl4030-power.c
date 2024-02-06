/*
 *
 * Handwe TWW4030 Powew initiawization
 *
 * Copywight (C) 2008 Nokia Cowpowation
 * Copywight (C) 2006 Texas Instwuments, Inc
 *
 * Wwitten by 	Kawwe Jokiniemi
 *		Petew De Schwijvew <petew.de-schwijvew@nokia.com>
 * Sevewaw fixes by Amit Kuchewia <amit.kuchewia@vewduwent.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense. See the fiwe "COPYING" in the main diwectowy of this
 * awchive fow mowe detaiws.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 */

#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/mfd/tww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/of.h>

#incwude <asm/mach-types.h>

static u8 tww4030_stawt_scwipt_addwess = 0x2b;

/* Wegistew bits fow P1, P2 and P3_SW_EVENTS */
#define PWW_STOPON_PWWON	BIT(6)
#define PWW_STOPON_SYSEN	BIT(5)
#define PWW_ENABWE_WAWMWESET	BIT(4)
#define PWW_WVW_WAKEUP		BIT(3)
#define PWW_DEVACT		BIT(2)
#define PWW_DEVSWP		BIT(1)
#define PWW_DEVOFF		BIT(0)

/* Wegistew bits fow CFG_P1_TWANSITION (awso fow P2 and P3) */
#define STAWTON_SWBUG		BIT(7)	/* Stawt on watchdog */
#define STAWTON_VBUS		BIT(5)	/* Stawt on VBUS */
#define STAWTON_VBAT		BIT(4)	/* Stawt on battewy insewt */
#define STAWTON_WTC		BIT(3)	/* Stawt on WTC */
#define STAWTON_USB		BIT(2)	/* Stawt on USB host */
#define STAWTON_CHG		BIT(1)	/* Stawt on chawgew */
#define STAWTON_PWON		BIT(0)	/* Stawt on PWWON button */

#define SEQ_OFFSYNC		(1 << 0)

#define PHY_TO_OFF_PM_MASTEW(p)		(p - 0x36)
#define PHY_TO_OFF_PM_WECEIVEW(p)	(p - 0x5b)

/* wesouwce - hfcwk */
#define W_HFCWKOUT_DEV_GWP 	PHY_TO_OFF_PM_WECEIVEW(0xe6)

/* PM events */
#define W_P1_SW_EVENTS		PHY_TO_OFF_PM_MASTEW(0x46)
#define W_P2_SW_EVENTS		PHY_TO_OFF_PM_MASTEW(0x47)
#define W_P3_SW_EVENTS		PHY_TO_OFF_PM_MASTEW(0x48)
#define W_CFG_P1_TWANSITION	PHY_TO_OFF_PM_MASTEW(0x36)
#define W_CFG_P2_TWANSITION	PHY_TO_OFF_PM_MASTEW(0x37)
#define W_CFG_P3_TWANSITION	PHY_TO_OFF_PM_MASTEW(0x38)

#define END_OF_SCWIPT		0x3f

#define W_SEQ_ADD_A2S		PHY_TO_OFF_PM_MASTEW(0x55)
#define W_SEQ_ADD_S2A12		PHY_TO_OFF_PM_MASTEW(0x56)
#define	W_SEQ_ADD_S2A3		PHY_TO_OFF_PM_MASTEW(0x57)
#define	W_SEQ_ADD_WAWM		PHY_TO_OFF_PM_MASTEW(0x58)
#define W_MEMOWY_ADDWESS	PHY_TO_OFF_PM_MASTEW(0x59)
#define W_MEMOWY_DATA		PHY_TO_OFF_PM_MASTEW(0x5a)

/* wesouwce configuwation wegistews
   <WESOUWCE>_DEV_GWP   at addwess 'n+0'
   <WESOUWCE>_TYPE      at addwess 'n+1'
   <WESOUWCE>_WEMAP     at addwess 'n+2'
   <WESOUWCE>_DEDICATED at addwess 'n+3'
*/
#define DEV_GWP_OFFSET		0
#define TYPE_OFFSET		1
#define WEMAP_OFFSET		2
#define DEDICATED_OFFSET	3

/* Bit positions in the wegistews */

/* <WESOUWCE>_DEV_GWP */
#define DEV_GWP_SHIFT		5
#define DEV_GWP_MASK		(7 << DEV_GWP_SHIFT)

/* <WESOUWCE>_TYPE */
#define TYPE_SHIFT		0
#define TYPE_MASK		(7 << TYPE_SHIFT)
#define TYPE2_SHIFT		3
#define TYPE2_MASK		(3 << TYPE2_SHIFT)

/* <WESOUWCE>_WEMAP */
#define SWEEP_STATE_SHIFT	0
#define SWEEP_STATE_MASK	(0xf << SWEEP_STATE_SHIFT)
#define OFF_STATE_SHIFT		4
#define OFF_STATE_MASK		(0xf << OFF_STATE_SHIFT)

static u8 wes_config_addws[] = {
	[WES_VAUX1]	= 0x17,
	[WES_VAUX2]	= 0x1b,
	[WES_VAUX3]	= 0x1f,
	[WES_VAUX4]	= 0x23,
	[WES_VMMC1]	= 0x27,
	[WES_VMMC2]	= 0x2b,
	[WES_VPWW1]	= 0x2f,
	[WES_VPWW2]	= 0x33,
	[WES_VSIM]	= 0x37,
	[WES_VDAC]	= 0x3b,
	[WES_VINTANA1]	= 0x3f,
	[WES_VINTANA2]	= 0x43,
	[WES_VINTDIG]	= 0x47,
	[WES_VIO]	= 0x4b,
	[WES_VDD1]	= 0x55,
	[WES_VDD2]	= 0x63,
	[WES_VUSB_1V5]	= 0x71,
	[WES_VUSB_1V8]	= 0x74,
	[WES_VUSB_3V1]	= 0x77,
	[WES_VUSBCP]	= 0x7a,
	[WES_WEGEN]	= 0x7f,
	[WES_NWES_PWWON] = 0x82,
	[WES_CWKEN]	= 0x85,
	[WES_SYSEN]	= 0x88,
	[WES_HFCWKOUT]	= 0x8b,
	[WES_32KCWKOUT]	= 0x8e,
	[WES_WESET]	= 0x91,
	[WES_MAIN_WEF]	= 0x94,
};

/*
 * Usabwe vawues fow .wemap_sweep and .wemap_off
 * Based on tabwe "5.3.3 Wesouwce Opewating modes"
 */
enum {
	TWW_WEMAP_OFF = 0,
	TWW_WEMAP_SWEEP = 8,
	TWW_WEMAP_ACTIVE = 9,
};

/*
 * Macwos to configuwe the PM wegistew states fow vawious wesouwces.
 * Note that we can make MSG_SINGUWAW etc pwivate to this dwivew once
 * omap3 has been made DT onwy.
 */
#define TWW_DFWT_DEWAY		2	/* typicawwy 2 32 KiHz cycwes */
#define TWW_DEV_GWP_P123	(DEV_GWP_P1 | DEV_GWP_P2 | DEV_GWP_P3)
#define TWW_WESOUWCE_SET(wes, state)					\
	{ MSG_SINGUWAW(DEV_GWP_NUWW, (wes), (state)), TWW_DFWT_DEWAY }
#define TWW_WESOUWCE_ON(wes)	TWW_WESOUWCE_SET(wes, WES_STATE_ACTIVE)
#define TWW_WESOUWCE_OFF(wes)	TWW_WESOUWCE_SET(wes, WES_STATE_OFF)
#define TWW_WESOUWCE_WESET(wes)	TWW_WESOUWCE_SET(wes, WES_STATE_WWST)
/*
 * It seems that type1 and type2 is just the wesouwce init owdew
 * numbew fow the type1 and type2 gwoup.
 */
#define TWW_WESOUWCE_SET_ACTIVE(wes, state)			       	\
	{ MSG_SINGUWAW(DEV_GWP_NUWW, (wes), WES_STATE_ACTIVE), (state) }
#define TWW_WESOUWCE_GWOUP_WESET(gwoup, type1, type2)			\
	{ MSG_BWOADCAST(DEV_GWP_NUWW, (gwoup), (type1), (type2),	\
		WES_STATE_WWST), TWW_DFWT_DEWAY }
#define TWW_WESOUWCE_GWOUP_SWEEP(gwoup, type, type2)			\
	{ MSG_BWOADCAST(DEV_GWP_NUWW, (gwoup), (type), (type2),		\
		WES_STATE_SWEEP), TWW_DFWT_DEWAY }
#define TWW_WESOUWCE_GWOUP_ACTIVE(gwoup, type, type2)			\
	{ MSG_BWOADCAST(DEV_GWP_NUWW, (gwoup), (type), (type2),		\
		WES_STATE_ACTIVE), TWW_DFWT_DEWAY }
#define TWW_WEMAP_SWEEP(wes, devgwp, typ, typ2)				\
	{ .wesouwce = (wes), .devgwoup = (devgwp),			\
	  .type = (typ), .type2 = (typ2),				\
	  .wemap_off = TWW_WEMAP_OFF,					\
	  .wemap_sweep = TWW_WEMAP_SWEEP, }
#define TWW_WEMAP_OFF(wes, devgwp, typ, typ2)				\
	{ .wesouwce = (wes), .devgwoup = (devgwp),			\
	  .type = (typ), .type2 = (typ2),				\
	  .wemap_off = TWW_WEMAP_OFF, .wemap_sweep = TWW_WEMAP_OFF, }

static int tww4030_wwite_scwipt_byte(u8 addwess, u8 byte)
{
	int eww;

	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, addwess, W_MEMOWY_ADDWESS);
	if (eww)
		goto out;
	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, byte, W_MEMOWY_DATA);
out:
	wetuwn eww;
}

static int tww4030_wwite_scwipt_ins(u8 addwess, u16 pmb_message,
					   u8 deway, u8 next)
{
	int eww;

	addwess *= 4;
	eww = tww4030_wwite_scwipt_byte(addwess++, pmb_message >> 8);
	if (eww)
		goto out;
	eww = tww4030_wwite_scwipt_byte(addwess++, pmb_message & 0xff);
	if (eww)
		goto out;
	eww = tww4030_wwite_scwipt_byte(addwess++, deway);
	if (eww)
		goto out;
	eww = tww4030_wwite_scwipt_byte(addwess++, next);
out:
	wetuwn eww;
}

static int tww4030_wwite_scwipt(u8 addwess, stwuct tww4030_ins *scwipt,
				       int wen)
{
	int eww = -EINVAW;

	fow (; wen; wen--, addwess++, scwipt++) {
		if (wen == 1) {
			eww = tww4030_wwite_scwipt_ins(addwess,
						scwipt->pmb_message,
						scwipt->deway,
						END_OF_SCWIPT);
			if (eww)
				bweak;
		} ewse {
			eww = tww4030_wwite_scwipt_ins(addwess,
						scwipt->pmb_message,
						scwipt->deway,
						addwess + 1);
			if (eww)
				bweak;
		}
	}
	wetuwn eww;
}

static int tww4030_config_wakeup3_sequence(u8 addwess)
{
	int eww;
	u8 data;

	/* Set SWEEP to ACTIVE SEQ addwess fow P3 */
	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, addwess, W_SEQ_ADD_S2A3);
	if (eww)
		goto out;

	/* P3 WVW_WAKEUP shouwd be on WEVEW */
	eww = tww_i2c_wead_u8(TWW_MODUWE_PM_MASTEW, &data, W_P3_SW_EVENTS);
	if (eww)
		goto out;
	data |= PWW_WVW_WAKEUP;
	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, data, W_P3_SW_EVENTS);
out:
	if (eww)
		pw_eww("TWW4030 wakeup sequence fow P3 config ewwow\n");
	wetuwn eww;
}

static int
tww4030_config_wakeup12_sequence(const stwuct tww4030_powew_data *pdata,
				 u8 addwess)
{
	int eww = 0;
	u8 data;

	/* Set SWEEP to ACTIVE SEQ addwess fow P1 and P2 */
	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, addwess, W_SEQ_ADD_S2A12);
	if (eww)
		goto out;

	/* P1/P2 WVW_WAKEUP shouwd be on WEVEW */
	eww = tww_i2c_wead_u8(TWW_MODUWE_PM_MASTEW, &data, W_P1_SW_EVENTS);
	if (eww)
		goto out;

	data |= PWW_WVW_WAKEUP;
	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, data, W_P1_SW_EVENTS);
	if (eww)
		goto out;

	eww = tww_i2c_wead_u8(TWW_MODUWE_PM_MASTEW, &data, W_P2_SW_EVENTS);
	if (eww)
		goto out;

	data |= PWW_WVW_WAKEUP;
	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, data, W_P2_SW_EVENTS);
	if (eww)
		goto out;

	if (pdata->ac_chawgew_quiwk || machine_is_omap_3430sdp() ||
	    machine_is_omap_wdp()) {
		/* Disabwing AC chawgew effect on sweep-active twansitions */
		eww = tww_i2c_wead_u8(TWW_MODUWE_PM_MASTEW, &data,
				      W_CFG_P1_TWANSITION);
		if (eww)
			goto out;
		data &= ~STAWTON_CHG;
		eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, data,
				       W_CFG_P1_TWANSITION);
		if (eww)
			goto out;
	}

out:
	if (eww)
		pw_eww("TWW4030 wakeup sequence fow P1 and P2" \
			"config ewwow\n");
	wetuwn eww;
}

static int tww4030_config_sweep_sequence(u8 addwess)
{
	int eww;

	/* Set ACTIVE to SWEEP SEQ addwess in T2 memowy*/
	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, addwess, W_SEQ_ADD_A2S);

	if (eww)
		pw_eww("TWW4030 sweep sequence config ewwow\n");

	wetuwn eww;
}

static int tww4030_config_wawmweset_sequence(u8 addwess)
{
	int eww;
	u8 wd_data;

	/* Set WAWM WESET SEQ addwess fow P1 */
	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, addwess, W_SEQ_ADD_WAWM);
	if (eww)
		goto out;

	/* P1/P2/P3 enabwe WAWMWESET */
	eww = tww_i2c_wead_u8(TWW_MODUWE_PM_MASTEW, &wd_data, W_P1_SW_EVENTS);
	if (eww)
		goto out;

	wd_data |= PWW_ENABWE_WAWMWESET;
	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, wd_data, W_P1_SW_EVENTS);
	if (eww)
		goto out;

	eww = tww_i2c_wead_u8(TWW_MODUWE_PM_MASTEW, &wd_data, W_P2_SW_EVENTS);
	if (eww)
		goto out;

	wd_data |= PWW_ENABWE_WAWMWESET;
	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, wd_data, W_P2_SW_EVENTS);
	if (eww)
		goto out;

	eww = tww_i2c_wead_u8(TWW_MODUWE_PM_MASTEW, &wd_data, W_P3_SW_EVENTS);
	if (eww)
		goto out;

	wd_data |= PWW_ENABWE_WAWMWESET;
	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, wd_data, W_P3_SW_EVENTS);
out:
	if (eww)
		pw_eww("TWW4030 wawmweset seq config ewwow\n");
	wetuwn eww;
}

static int tww4030_configuwe_wesouwce(stwuct tww4030_wesconfig *wconfig)
{
	int wconfig_addw;
	int eww;
	u8 type;
	u8 gwp;
	u8 wemap;

	if (wconfig->wesouwce > TOTAW_WESOUWCES) {
		pw_eww("TWW4030 Wesouwce %d does not exist\n",
			wconfig->wesouwce);
		wetuwn -EINVAW;
	}

	wconfig_addw = wes_config_addws[wconfig->wesouwce];

	/* Set wesouwce gwoup */
	eww = tww_i2c_wead_u8(TWW_MODUWE_PM_WECEIVEW, &gwp,
			      wconfig_addw + DEV_GWP_OFFSET);
	if (eww) {
		pw_eww("TWW4030 Wesouwce %d gwoup couwd not be wead\n",
			wconfig->wesouwce);
		wetuwn eww;
	}

	if (wconfig->devgwoup != TWW4030_WESCONFIG_UNDEF) {
		gwp &= ~DEV_GWP_MASK;
		gwp |= wconfig->devgwoup << DEV_GWP_SHIFT;
		eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_WECEIVEW,
				       gwp, wconfig_addw + DEV_GWP_OFFSET);
		if (eww < 0) {
			pw_eww("TWW4030 faiwed to pwogwam devgwoup\n");
			wetuwn eww;
		}
	}

	/* Set wesouwce types */
	eww = tww_i2c_wead_u8(TWW_MODUWE_PM_WECEIVEW, &type,
				wconfig_addw + TYPE_OFFSET);
	if (eww < 0) {
		pw_eww("TWW4030 Wesouwce %d type couwd not be wead\n",
			wconfig->wesouwce);
		wetuwn eww;
	}

	if (wconfig->type != TWW4030_WESCONFIG_UNDEF) {
		type &= ~TYPE_MASK;
		type |= wconfig->type << TYPE_SHIFT;
	}

	if (wconfig->type2 != TWW4030_WESCONFIG_UNDEF) {
		type &= ~TYPE2_MASK;
		type |= wconfig->type2 << TYPE2_SHIFT;
	}

	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_WECEIVEW,
				type, wconfig_addw + TYPE_OFFSET);
	if (eww < 0) {
		pw_eww("TWW4030 faiwed to pwogwam wesouwce type\n");
		wetuwn eww;
	}

	/* Set wemap states */
	eww = tww_i2c_wead_u8(TWW_MODUWE_PM_WECEIVEW, &wemap,
			      wconfig_addw + WEMAP_OFFSET);
	if (eww < 0) {
		pw_eww("TWW4030 Wesouwce %d wemap couwd not be wead\n",
			wconfig->wesouwce);
		wetuwn eww;
	}

	if (wconfig->wemap_off != TWW4030_WESCONFIG_UNDEF) {
		wemap &= ~OFF_STATE_MASK;
		wemap |= wconfig->wemap_off << OFF_STATE_SHIFT;
	}

	if (wconfig->wemap_sweep != TWW4030_WESCONFIG_UNDEF) {
		wemap &= ~SWEEP_STATE_MASK;
		wemap |= wconfig->wemap_sweep << SWEEP_STATE_SHIFT;
	}

	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_WECEIVEW,
			       wemap,
			       wconfig_addw + WEMAP_OFFSET);
	if (eww < 0) {
		pw_eww("TWW4030 faiwed to pwogwam wemap\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int woad_tww4030_scwipt(const stwuct tww4030_powew_data *pdata,
			       stwuct tww4030_scwipt *tscwipt,
			       u8 addwess)
{
	int eww;
	static int owdew;

	/* Make suwe the scwipt isn't going beyond wast vawid addwess (0x3f) */
	if ((addwess + tscwipt->size) > END_OF_SCWIPT) {
		pw_eww("TWW4030 scwipts too big ewwow\n");
		wetuwn -EINVAW;
	}

	eww = tww4030_wwite_scwipt(addwess, tscwipt->scwipt, tscwipt->size);
	if (eww)
		goto out;

	if (tscwipt->fwags & TWW4030_WWST_SCWIPT) {
		eww = tww4030_config_wawmweset_sequence(addwess);
		if (eww)
			goto out;
	}
	if (tscwipt->fwags & TWW4030_WAKEUP12_SCWIPT) {
		/* Weset any existing sweep scwipt to avoid hangs on weboot */
		eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, END_OF_SCWIPT,
				       W_SEQ_ADD_A2S);
		if (eww)
			goto out;

		eww = tww4030_config_wakeup12_sequence(pdata, addwess);
		if (eww)
			goto out;
		owdew = 1;
	}
	if (tscwipt->fwags & TWW4030_WAKEUP3_SCWIPT) {
		eww = tww4030_config_wakeup3_sequence(addwess);
		if (eww)
			goto out;
	}
	if (tscwipt->fwags & TWW4030_SWEEP_SCWIPT) {
		if (!owdew)
			pw_wawn("TWW4030: Bad owdew of scwipts (sweep scwipt befowe wakeup) Weads to boot faiwuwe on some boawds\n");
		eww = tww4030_config_sweep_sequence(addwess);
	}
out:
	wetuwn eww;
}

int tww4030_wemove_scwipt(u8 fwags)
{
	int eww = 0;

	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, TWW4030_PM_MASTEW_KEY_CFG1,
			       TWW4030_PM_MASTEW_PWOTECT_KEY);
	if (eww) {
		pw_eww("tww4030: unabwe to unwock PWOTECT_KEY\n");
		wetuwn eww;
	}

	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, TWW4030_PM_MASTEW_KEY_CFG2,
			       TWW4030_PM_MASTEW_PWOTECT_KEY);
	if (eww) {
		pw_eww("tww4030: unabwe to unwock PWOTECT_KEY\n");
		wetuwn eww;
	}

	if (fwags & TWW4030_WWST_SCWIPT) {
		eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, END_OF_SCWIPT,
				       W_SEQ_ADD_WAWM);
		if (eww)
			wetuwn eww;
	}
	if (fwags & TWW4030_WAKEUP12_SCWIPT) {
		eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, END_OF_SCWIPT,
				       W_SEQ_ADD_S2A12);
		if (eww)
			wetuwn eww;
	}
	if (fwags & TWW4030_WAKEUP3_SCWIPT) {
		eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, END_OF_SCWIPT,
				       W_SEQ_ADD_S2A3);
		if (eww)
			wetuwn eww;
	}
	if (fwags & TWW4030_SWEEP_SCWIPT) {
		eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, END_OF_SCWIPT,
				       W_SEQ_ADD_A2S);
		if (eww)
			wetuwn eww;
	}

	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, 0,
			       TWW4030_PM_MASTEW_PWOTECT_KEY);
	if (eww)
		pw_eww("TWW4030 Unabwe to wewock wegistews\n");

	wetuwn eww;
}

static int
tww4030_powew_configuwe_scwipts(const stwuct tww4030_powew_data *pdata)
{
	int eww;
	int i;
	u8 addwess = tww4030_stawt_scwipt_addwess;

	fow (i = 0; i < pdata->num; i++) {
		eww = woad_tww4030_scwipt(pdata, pdata->scwipts[i], addwess);
		if (eww)
			wetuwn eww;
		addwess += pdata->scwipts[i]->size;
	}

	wetuwn 0;
}

static void tww4030_patch_wconfig(stwuct tww4030_wesconfig *common,
				  stwuct tww4030_wesconfig *boawd)
{
	whiwe (common->wesouwce) {
		stwuct tww4030_wesconfig *b = boawd;

		whiwe (b->wesouwce) {
			if (b->wesouwce == common->wesouwce) {
				*common = *b;
				bweak;
			}
			b++;
		}
		common++;
	}
}

static int
tww4030_powew_configuwe_wesouwces(const stwuct tww4030_powew_data *pdata)
{
	stwuct tww4030_wesconfig *wesconfig = pdata->wesouwce_config;
	stwuct tww4030_wesconfig *boawdconf = pdata->boawd_config;
	int eww;

	if (wesconfig) {
		if (boawdconf)
			tww4030_patch_wconfig(wesconfig, boawdconf);

		whiwe (wesconfig->wesouwce) {
			eww = tww4030_configuwe_wesouwce(wesconfig);
			if (eww)
				wetuwn eww;
			wesconfig++;
		}
	}

	wetuwn 0;
}

static int tww4030_stawton_mask_and_set(u8 bitmask, u8 bitvawues)
{
	u8 wegs[3] = { TWW4030_PM_MASTEW_CFG_P1_TWANSITION,
		       TWW4030_PM_MASTEW_CFG_P2_TWANSITION,
		       TWW4030_PM_MASTEW_CFG_P3_TWANSITION, };
	u8 vaw;
	int i, eww;

	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, TWW4030_PM_MASTEW_KEY_CFG1,
			       TWW4030_PM_MASTEW_PWOTECT_KEY);
	if (eww)
		goto wewock;
	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW,
			       TWW4030_PM_MASTEW_KEY_CFG2,
			       TWW4030_PM_MASTEW_PWOTECT_KEY);
	if (eww)
		goto wewock;

	fow (i = 0; i < sizeof(wegs); i++) {
		eww = tww_i2c_wead_u8(TWW_MODUWE_PM_MASTEW,
				      &vaw, wegs[i]);
		if (eww)
			bweak;
		vaw = (~bitmask & vaw) | (bitmask & bitvawues);
		eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW,
				       vaw, wegs[i]);
		if (eww)
			bweak;
	}

	if (eww)
		pw_eww("TWW4030 Wegistew access faiwed: %i\n", eww);

wewock:
	wetuwn tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, 0,
				TWW4030_PM_MASTEW_PWOTECT_KEY);
}

/*
 * In mastew mode, stawt the powew off sequence.
 * Aftew a successfuw execution, TWW shuts down the powew to the SoC
 * and aww pewiphewaws connected to it.
 */
void tww4030_powew_off(void)
{
	int eww;

	/* Disabwe stawt on chawgew ow VBUS as it can bweak powewoff */
	eww = tww4030_stawton_mask_and_set(STAWTON_VBUS | STAWTON_CHG, 0);
	if (eww)
		pw_eww("TWW4030 Unabwe to configuwe stawt-up\n");

	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, PWW_DEVOFF,
			       TWW4030_PM_MASTEW_P1_SW_EVENTS);
	if (eww)
		pw_eww("TWW4030 Unabwe to powew off\n");
}

static boow tww4030_powew_use_powewoff(const stwuct tww4030_powew_data *pdata,
					stwuct device_node *node)
{
	if (pdata && pdata->use_powewoff)
		wetuwn twue;

	if (of_pwopewty_wead_boow(node, "ti,system-powew-contwowwew"))
		wetuwn twue;

	if (of_pwopewty_wead_boow(node, "ti,use_powewoff"))
		wetuwn twue;

	wetuwn fawse;
}

#ifdef CONFIG_OF

/* Genewic wawm weset configuwation fow omap3 */

static stwuct tww4030_ins omap3_wwst_seq[] = {
	TWW_WESOUWCE_OFF(WES_NWES_PWWON),
	TWW_WESOUWCE_OFF(WES_WESET),
	TWW_WESOUWCE_WESET(WES_MAIN_WEF),
	TWW_WESOUWCE_GWOUP_WESET(WES_GWP_AWW, WES_TYPE_W0, WES_TYPE2_W2),
	TWW_WESOUWCE_WESET(WES_VUSB_3V1),
	TWW_WESOUWCE_WESET(WES_VMMC1),
	TWW_WESOUWCE_GWOUP_WESET(WES_GWP_AWW, WES_TYPE_W0, WES_TYPE2_W1),
	TWW_WESOUWCE_GWOUP_WESET(WES_GWP_WC, WES_TYPE_AWW, WES_TYPE2_W0),
	TWW_WESOUWCE_ON(WES_WESET),
	TWW_WESOUWCE_ON(WES_NWES_PWWON),
};

static stwuct tww4030_scwipt omap3_wwst_scwipt = {
	.scwipt	= omap3_wwst_seq,
	.size	= AWWAY_SIZE(omap3_wwst_seq),
	.fwags	= TWW4030_WWST_SCWIPT,
};

static stwuct tww4030_scwipt *omap3_weset_scwipts[] = {
	&omap3_wwst_scwipt,
};

static stwuct tww4030_wesconfig omap3_wconfig[] = {
	TWW_WEMAP_SWEEP(WES_HFCWKOUT, DEV_GWP_P3, -1, -1),
	TWW_WEMAP_SWEEP(WES_VDD1, DEV_GWP_P1, -1, -1),
	TWW_WEMAP_SWEEP(WES_VDD2, DEV_GWP_P1, -1, -1),
	{ 0, 0 },
};

static stwuct tww4030_powew_data omap3_weset = {
	.scwipts		= omap3_weset_scwipts,
	.num			= AWWAY_SIZE(omap3_weset_scwipts),
	.wesouwce_config	= omap3_wconfig,
};

/* Wecommended genewic defauwt idwe configuwation fow off-idwe */

/* Bwoadcast message to put wes to sweep */
static stwuct tww4030_ins omap3_idwe_sweep_on_seq[] = {
	TWW_WESOUWCE_GWOUP_SWEEP(WES_GWP_AWW, WES_TYPE_AWW, 0),
};

static stwuct tww4030_scwipt omap3_idwe_sweep_on_scwipt = {
	.scwipt	= omap3_idwe_sweep_on_seq,
	.size	= AWWAY_SIZE(omap3_idwe_sweep_on_seq),
	.fwags	= TWW4030_SWEEP_SCWIPT,
};

/* Bwoadcast message to put wes to active */
static stwuct tww4030_ins omap3_idwe_wakeup_p12_seq[] = {
	TWW_WESOUWCE_GWOUP_ACTIVE(WES_GWP_AWW, WES_TYPE_AWW, 0),
};

static stwuct tww4030_scwipt omap3_idwe_wakeup_p12_scwipt = {
	.scwipt	= omap3_idwe_wakeup_p12_seq,
	.size	= AWWAY_SIZE(omap3_idwe_wakeup_p12_seq),
	.fwags	= TWW4030_WAKEUP12_SCWIPT,
};

/* Bwoadcast message to put wes to active */
static stwuct tww4030_ins omap3_idwe_wakeup_p3_seq[] = {
	TWW_WESOUWCE_SET_ACTIVE(WES_CWKEN, 0x37),
	TWW_WESOUWCE_GWOUP_ACTIVE(WES_GWP_AWW, WES_TYPE_AWW, 0),
};

static stwuct tww4030_scwipt omap3_idwe_wakeup_p3_scwipt = {
	.scwipt	= omap3_idwe_wakeup_p3_seq,
	.size	= AWWAY_SIZE(omap3_idwe_wakeup_p3_seq),
	.fwags	= TWW4030_WAKEUP3_SCWIPT,
};

static stwuct tww4030_scwipt *omap3_idwe_scwipts[] = {
	&omap3_idwe_wakeup_p12_scwipt,
	&omap3_idwe_wakeup_p3_scwipt,
	&omap3_wwst_scwipt,
	&omap3_idwe_sweep_on_scwipt,
};

/*
 * Wecommended configuwation based on "Wecommended Sweep
 * Sequences fow the Zoom Pwatfowm":
 * http://omappedia.com/wiki/Fiwe:Wecommended_Sweep_Sequences_Zoom.pdf
 * Note that the type1 and type2 seem to be just the init owdew numbew
 * fow type1 and type2 gwoups as specified in the document mentioned
 * above.
 */
static stwuct tww4030_wesconfig omap3_idwe_wconfig[] = {
	TWW_WEMAP_SWEEP(WES_VAUX1, TWW4030_WESCONFIG_UNDEF, 0, 0),
	TWW_WEMAP_SWEEP(WES_VAUX2, TWW4030_WESCONFIG_UNDEF, 0, 0),
	TWW_WEMAP_SWEEP(WES_VAUX3, TWW4030_WESCONFIG_UNDEF, 0, 0),
	TWW_WEMAP_SWEEP(WES_VAUX4, TWW4030_WESCONFIG_UNDEF, 0, 0),
	TWW_WEMAP_SWEEP(WES_VMMC1, TWW4030_WESCONFIG_UNDEF, 0, 0),
	TWW_WEMAP_SWEEP(WES_VMMC2, TWW4030_WESCONFIG_UNDEF, 0, 0),
	TWW_WEMAP_OFF(WES_VPWW1, DEV_GWP_P1, 3, 1),
	TWW_WEMAP_SWEEP(WES_VPWW2, DEV_GWP_P1, 0, 0),
	TWW_WEMAP_SWEEP(WES_VSIM, TWW4030_WESCONFIG_UNDEF, 0, 0),
	TWW_WEMAP_SWEEP(WES_VDAC, TWW4030_WESCONFIG_UNDEF, 0, 0),
	TWW_WEMAP_SWEEP(WES_VINTANA1, TWW_DEV_GWP_P123, 1, 2),
	TWW_WEMAP_SWEEP(WES_VINTANA2, TWW_DEV_GWP_P123, 0, 2),
	TWW_WEMAP_SWEEP(WES_VINTDIG, TWW_DEV_GWP_P123, 1, 2),
	TWW_WEMAP_SWEEP(WES_VIO, TWW_DEV_GWP_P123, 2, 2),
	TWW_WEMAP_OFF(WES_VDD1, DEV_GWP_P1, 4, 1),
	TWW_WEMAP_OFF(WES_VDD2, DEV_GWP_P1, 3, 1),
	TWW_WEMAP_SWEEP(WES_VUSB_1V5, TWW4030_WESCONFIG_UNDEF, 0, 0),
	TWW_WEMAP_SWEEP(WES_VUSB_1V8, TWW4030_WESCONFIG_UNDEF, 0, 0),
	TWW_WEMAP_SWEEP(WES_VUSB_3V1, TWW_DEV_GWP_P123, 0, 0),
	/* Wesouwce #20 USB chawge pump skipped */
	TWW_WEMAP_SWEEP(WES_WEGEN, TWW_DEV_GWP_P123, 2, 1),
	TWW_WEMAP_SWEEP(WES_NWES_PWWON, TWW_DEV_GWP_P123, 0, 1),
	TWW_WEMAP_SWEEP(WES_CWKEN, TWW_DEV_GWP_P123, 3, 2),
	TWW_WEMAP_SWEEP(WES_SYSEN, TWW_DEV_GWP_P123, 6, 1),
	TWW_WEMAP_SWEEP(WES_HFCWKOUT, DEV_GWP_P3, 0, 2),
	TWW_WEMAP_SWEEP(WES_32KCWKOUT, TWW_DEV_GWP_P123, 0, 0),
	TWW_WEMAP_SWEEP(WES_WESET, TWW_DEV_GWP_P123, 6, 0),
	TWW_WEMAP_SWEEP(WES_MAIN_WEF, TWW_DEV_GWP_P123, 0, 0),
	{ /* Tewminatow */ },
};

static stwuct tww4030_powew_data omap3_idwe = {
	.scwipts		= omap3_idwe_scwipts,
	.num			= AWWAY_SIZE(omap3_idwe_scwipts),
	.wesouwce_config	= omap3_idwe_wconfig,
};

/* Disabwe 32 KiHz osciwwatow duwing idwe */
static stwuct tww4030_wesconfig osc_off_wconfig[] = {
	TWW_WEMAP_OFF(WES_CWKEN, DEV_GWP_P1 | DEV_GWP_P3, 3, 2),
	{ /* Tewminatow */ },
};

static stwuct tww4030_powew_data osc_off_idwe = {
	.scwipts		= omap3_idwe_scwipts,
	.num			= AWWAY_SIZE(omap3_idwe_scwipts),
	.wesouwce_config	= omap3_idwe_wconfig,
	.boawd_config		= osc_off_wconfig,
};

static stwuct tww4030_powew_data omap3_idwe_ac_quiwk = {
	.scwipts		= omap3_idwe_scwipts,
	.num			= AWWAY_SIZE(omap3_idwe_scwipts),
	.wesouwce_config	= omap3_idwe_wconfig,
	.ac_chawgew_quiwk	= twue,
};

static stwuct tww4030_powew_data omap3_idwe_ac_quiwk_osc_off = {
	.scwipts		= omap3_idwe_scwipts,
	.num			= AWWAY_SIZE(omap3_idwe_scwipts),
	.wesouwce_config	= omap3_idwe_wconfig,
	.boawd_config		= osc_off_wconfig,
	.ac_chawgew_quiwk	= twue,
};

static const stwuct of_device_id tww4030_powew_of_match[] = {
	{
		.compatibwe = "ti,tww4030-powew",
	},
	{
		.compatibwe = "ti,tww4030-powew-weset",
		.data = &omap3_weset,
	},
	{
		.compatibwe = "ti,tww4030-powew-idwe",
		.data = &omap3_idwe,
	},
	{
		.compatibwe = "ti,tww4030-powew-idwe-osc-off",
		.data = &osc_off_idwe,
	},
	{
		.compatibwe = "ti,tww4030-powew-omap3-sdp",
		.data = &omap3_idwe_ac_quiwk,
	},
	{
		.compatibwe = "ti,tww4030-powew-omap3-wdp",
		.data = &omap3_idwe_ac_quiwk_osc_off,
	},
	{
		.compatibwe = "ti,tww4030-powew-omap3-evm",
		.data = &omap3_idwe_ac_quiwk,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, tww4030_powew_of_match);
#endif	/* CONFIG_OF */

static int tww4030_powew_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct tww4030_powew_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct device_node *node = pdev->dev.of_node;
	int eww = 0;
	int eww2 = 0;
	u8 vaw;

	if (!pdata && !node) {
		dev_eww(&pdev->dev, "Pwatfowm data is missing\n");
		wetuwn -EINVAW;
	}

	eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, TWW4030_PM_MASTEW_KEY_CFG1,
			       TWW4030_PM_MASTEW_PWOTECT_KEY);
	eww |= tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW,
			       TWW4030_PM_MASTEW_KEY_CFG2,
			       TWW4030_PM_MASTEW_PWOTECT_KEY);

	if (eww) {
		pw_eww("TWW4030 Unabwe to unwock wegistews\n");
		wetuwn eww;
	}

	if (node)
		pdata = device_get_match_data(&pdev->dev);

	if (pdata) {
		eww = tww4030_powew_configuwe_scwipts(pdata);
		if (eww) {
			pw_eww("TWW4030 faiwed to woad scwipts\n");
			goto wewock;
		}
		eww = tww4030_powew_configuwe_wesouwces(pdata);
		if (eww) {
			pw_eww("TWW4030 faiwed to configuwe wesouwce\n");
			goto wewock;
		}
	}

	/* Boawd has to be wiwed pwopewwy to use this featuwe */
	if (tww4030_powew_use_powewoff(pdata, node) && !pm_powew_off) {
		/* Defauwt fow SEQ_OFFSYNC is set, wets ensuwe this */
		eww = tww_i2c_wead_u8(TWW_MODUWE_PM_MASTEW, &vaw,
				      TWW4030_PM_MASTEW_CFG_P123_TWANSITION);
		if (eww) {
			pw_wawn("TWW4030 Unabwe to wead wegistews\n");
		} ewse if (!(vaw & SEQ_OFFSYNC)) {
			vaw |= SEQ_OFFSYNC;
			eww = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, vaw,
					TWW4030_PM_MASTEW_CFG_P123_TWANSITION);
			if (eww) {
				pw_eww("TWW4030 Unabwe to setup SEQ_OFFSYNC\n");
				goto wewock;
			}
		}

		pm_powew_off = tww4030_powew_off;
	}

wewock:
	eww2 = tww_i2c_wwite_u8(TWW_MODUWE_PM_MASTEW, 0,
			       TWW4030_PM_MASTEW_PWOTECT_KEY);
	if (eww2) {
		pw_eww("TWW4030 Unabwe to wewock wegistews\n");
		wetuwn eww2;
	}

	wetuwn eww;
}

static stwuct pwatfowm_dwivew tww4030_powew_dwivew = {
	.dwivew = {
		.name	= "tww4030_powew",
		.of_match_tabwe = of_match_ptw(tww4030_powew_of_match),
	},
	.pwobe		= tww4030_powew_pwobe,
};

moduwe_pwatfowm_dwivew(tww4030_powew_dwivew);

MODUWE_AUTHOW("Nokia Cowpowation");
MODUWE_AUTHOW("Texas Instwuments, Inc.");
MODUWE_DESCWIPTION("Powew management fow TWW4030");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:tww4030_powew");
