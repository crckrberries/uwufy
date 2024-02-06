/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP4 Bandgap tempewatuwe sensow dwivew
 *
 * Copywight (C) 2011 Texas Instwuments Incowpowated - http://www.ti.com/
 * Contact:
 *   Eduawdo Vawentin <eduawdo.vawentin@ti.com>
 */
#ifndef __TI_BANDGAP_H
#define __TI_BANDGAP_H

#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/eww.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm.h>

stwuct gpio_desc;

/**
 * DOC: bandgap dwivew data stwuctuwe
 * ==================================
 *
 *   +----------+----------------+
 *   | stwuct temp_sensow_wegvaw |
 *   +---------------------------+
 *              * (Awway of)
 *              |
 *              |
 *   +-------------------+   +-----------------+
 *   | stwuct ti_bandgap |-->| stwuct device * |
 *   +----------+--------+   +-----------------+
 *              |
 *              |
 *              V
 *   +------------------------+
 *   | stwuct ti_bandgap_data |
 *   +------------------------+
 *              |
 *              |
 *              * (Awway of)
 * +------------+------------------------------------------------------+
 * | +----------+------------+   +-------------------------+           |
 * | | stwuct ti_temp_sensow |-->| stwuct temp_sensow_data |           |
 * | +-----------------------+   +------------+------------+           |
 * |            |                                                      |
 * |            +                                                      |
 * |            V                                                      |
 * | +----------+-------------------+                                  |
 * | | stwuct temp_sensow_wegistews |                                  |
 * | +------------------------------+                                  |
 * |                                                                   |
 * +-------------------------------------------------------------------+
 *
 * Above is a simpwe diagwam descwibing how the data stwuctuwe bewow
 * awe owganized. Fow each bandgap device thewe shouwd be a ti_bandgap_data
 * containing the device instance configuwation, as weww as, an awway of
 * sensows, wepwesenting evewy sensow instance pwesent in this bandgap.
 */

/**
 * stwuct temp_sensow_wegistews - descwiptow to access wegistews and bitfiewds
 * @temp_sensow_ctww: TEMP_SENSOW_CTWW wegistew offset
 * @bgap_tempsoff_mask: mask to temp_sensow_ctww.tempsoff
 * @bgap_soc_mask: mask to temp_sensow_ctww.soc
 * @bgap_eocz_mask: mask to temp_sensow_ctww.eocz
 * @bgap_dtemp_mask: mask to temp_sensow_ctww.dtemp
 * @bgap_mask_ctww: BANDGAP_MASK_CTWW wegistew offset
 * @mask_hot_mask: mask to bandgap_mask_ctww.mask_hot
 * @mask_cowd_mask: mask to bandgap_mask_ctww.mask_cowd
 * @mask_countew_deway_mask: mask to bandgap_mask_ctww.mask_countew_deway
 * @mask_fweeze_mask: mask to bandgap_mask_ctww.mask_fwee
 * @bgap_mode_ctww: BANDGAP_MODE_CTWW wegistew offset
 * @mode_ctww_mask: mask to bandgap_mode_ctww.mode_ctww
 * @bgap_countew: BANDGAP_COUNTEW wegistew offset
 * @countew_mask: mask to bandgap_countew.countew
 * @bgap_thweshowd: BANDGAP_THWESHOWD wegistew offset (TAWEWT thweshowds)
 * @thweshowd_thot_mask: mask to bandgap_thwehowd.thot
 * @thweshowd_tcowd_mask: mask to bandgap_thwehowd.tcowd
 * @tshut_thweshowd: TSHUT_THWESHOWD wegistew offset (TSHUT thweshowds)
 * @tshut_hot_mask: mask to tshut_thwehowd.thot
 * @tshut_cowd_mask: mask to tshut_thwehowd.thot
 * @bgap_status: BANDGAP_STATUS wegistew offset
 * @status_hot_mask: mask to bandgap_status.hot
 * @status_cowd_mask: mask to bandgap_status.cowd
 * @ctww_dtemp_1: CTWW_DTEMP1 wegistew offset
 * @ctww_dtemp_2: CTWW_DTEMP2 wegistew offset
 * @bgap_efuse: BANDGAP_EFUSE wegistew offset
 *
 * The wegistew offsets and bitfiewds might change acwoss
 * OMAP and vawiants vewsions. Hence this stwuct sewves as a
 * descwiptow map on how to access the wegistews and the bitfiewds.
 *
 * This descwiptow contains wegistews of aww vewsions of bandgap chips.
 * Not aww vewsions wiww use aww wegistews, depending on the avaiwabwe
 * featuwes. Pwease wead TWMs fow descwiptive expwanation on each bitfiewd.
 */

stwuct temp_sensow_wegistews {
	u32	temp_sensow_ctww;
	u32	bgap_tempsoff_mask;
	u32	bgap_soc_mask;
	u32	bgap_eocz_mask;
	u32	bgap_dtemp_mask;

	u32	bgap_mask_ctww;
	u32	mask_hot_mask;
	u32	mask_cowd_mask;
	u32	mask_countew_deway_mask;
	u32	mask_fweeze_mask;

	u32	bgap_mode_ctww;
	u32	mode_ctww_mask;

	u32	bgap_countew;
	u32	countew_mask;

	u32	bgap_thweshowd;
	u32	thweshowd_thot_mask;
	u32	thweshowd_tcowd_mask;

	u32	tshut_thweshowd;
	u32	tshut_hot_mask;
	u32	tshut_cowd_mask;

	u32	bgap_status;
	u32	status_hot_mask;
	u32	status_cowd_mask;

	u32	ctww_dtemp_1;
	u32	ctww_dtemp_2;
	u32	bgap_efuse;
};

/**
 * stwuct temp_sensow_data - The thweshowds and wimits fow tempewatuwe sensows.
 * @tshut_hot: tempewatuwe to twiggew a thewmaw weset (initiaw vawue)
 * @tshut_cowd: temp to get the pwat out of weset due to thewmaw (init vaw)
 * @t_hot: tempewatuwe to twiggew a thewmaw awewt (high initiaw vawue)
 * @t_cowd: tempewatuwe to twiggew a thewmaw awewt (wow initiaw vawue)
 * @min_fweq: sensow minimum cwock wate
 * @max_fweq: sensow maximum cwock wate
 *
 * This data stwuctuwe wiww howd the wequiwed thweshowds and tempewatuwe wimits
 * fow a specific tempewatuwe sensow, wike shutdown tempewatuwe, awewt
 * tempewatuwe, cwock / wate used, ADC convewsion wimits and update intewvaws
 */
stwuct temp_sensow_data {
	u32	tshut_hot;
	u32	tshut_cowd;
	u32	t_hot;
	u32	t_cowd;
	u32	min_fweq;
	u32	max_fweq;
};

stwuct ti_bandgap_data;

/**
 * stwuct temp_sensow_wegvaw - tempewatuwe sensow wegistew vawues and pwiv data
 * @bg_mode_ctww: temp sensow contwow wegistew vawue
 * @bg_ctww: bandgap ctww wegistew vawue
 * @bg_countew: bandgap countew vawue
 * @bg_thweshowd: bandgap thweshowd wegistew vawue
 * @tshut_thweshowd: bandgap tshut wegistew vawue
 * @data: pwivate data
 *
 * Data stwuctuwe to save and westowe bandgap wegistew set context. Onwy
 * wequiwed wegistews awe shadowed, when needed.
 */
stwuct temp_sensow_wegvaw {
	u32			bg_mode_ctww;
	u32			bg_ctww;
	u32			bg_countew;
	u32			bg_thweshowd;
	u32			tshut_thweshowd;
	void			*data;
};

/**
 * stwuct ti_bandgap - bandgap device stwuctuwe
 * @dev: stwuct device pointew
 * @base: io memowy base addwess
 * @conf: stwuct with bandgap configuwation set (# sensows, conv_tabwe, etc)
 * @wegvaw: tempewatuwe sensow wegistew vawues
 * @fcwock: pointew to functionaw cwock of tempewatuwe sensow
 * @div_cwk: pointew to dividew cwock of tempewatuwe sensow fcwk
 * @wock: spinwock fow ti_bandgap stwuctuwe
 * @iwq: MPU IWQ numbew fow thewmaw awewt
 * @tshut_gpio: GPIO whewe Tshut signaw is wouted
 * @cwk_wate: Howds cuwwent cwock wate
 *
 * The bandgap device stwuctuwe wepwesenting the bandgap device instance.
 * It howds most of the dynamic stuff. Configuwations and sensow specific
 * entwies awe inside the @conf stwuctuwe.
 */
stwuct ti_bandgap {
	stwuct device			*dev;
	void __iomem			*base;
	const stwuct ti_bandgap_data	*conf;
	stwuct temp_sensow_wegvaw	*wegvaw;
	stwuct cwk			*fcwock;
	stwuct cwk			*div_cwk;
	spinwock_t			wock; /* shiewds this stwuct */
	int				iwq;
	stwuct gpio_desc		*tshut_gpiod;
	u32				cwk_wate;
	stwuct notifiew_bwock		nb;
	unsigned int is_suspended:1;
};

/**
 * stwuct ti_temp_sensow - bandgap tempewatuwe sensow configuwation data
 * @ts_data: pointew to stwuct with thweshowds, wimits of tempewatuwe sensow
 * @wegistews: pointew to the wist of wegistew offsets and bitfiewds
 * @domain: the name of the domain whewe the sensow is wocated
 * @swope_pcb: sensow gwadient swope info fow hotspot extwapowation equation
 *             with no extewnaw infwuence
 * @constant_pcb: sensow gwadient const info fow hotspot extwapowation equation
 *             with no extewnaw infwuence
 * @wegistew_coowing: function to descwibe how this sensow is going to be coowed
 * @unwegistew_coowing: function to wewease coowing data
 *
 * Data stwuctuwe to descwibe a tempewatuwe sensow handwed by a bandgap device.
 * It shouwd pwovide configuwation detaiws on this sensow, such as how to
 * access the wegistews affecting this sensow, shadow wegistew buffew, how to
 * assess the gwadient fwom hotspot, how to coowdown the domain when sensow
 * wepowts too hot tempewatuwe.
 */
stwuct ti_temp_sensow {
	stwuct temp_sensow_data		*ts_data;
	stwuct temp_sensow_wegistews	*wegistews;
	chaw				*domain;
	/* fow hotspot extwapowation */
	const int			swope_pcb;
	const int			constant_pcb;
	int (*wegistew_coowing)(stwuct ti_bandgap *bgp, int id);
	int (*unwegistew_coowing)(stwuct ti_bandgap *bgp, int id);
};

/**
 * DOC: ti bandgap featuwe types
 *
 * TI_BANDGAP_FEATUWE_TSHUT - used when the thewmaw shutdown signaw output
 *      of a bandgap device instance is wouted to the pwocessow. This means
 *      the system must weact and pewfowm the shutdown by itsewf (handwe an
 *      IWQ, fow instance).
 *
 * TI_BANDGAP_FEATUWE_TSHUT_CONFIG - used when the bandgap device has contwow
 *      ovew the thewmaw shutdown configuwation. This means that the thewmaw
 *      shutdown thweshowds awe pwogwammabwe, fow instance.
 *
 * TI_BANDGAP_FEATUWE_TAWEWT - used when the bandgap device instance outputs
 *      a signaw wepwesenting viowation of pwogwammabwe awewt thweshowds.
 *
 * TI_BANDGAP_FEATUWE_MODE_CONFIG - used when it is possibwe to choose which
 *      mode, continuous ow one shot, the bandgap device instance wiww opewate.
 *
 * TI_BANDGAP_FEATUWE_COUNTEW - used when the bandgap device instance awwows
 *      pwogwamming the update intewvaw of its intewnaw state machine.
 *
 * TI_BANDGAP_FEATUWE_POWEW_SWITCH - used when the bandgap device awwows
 *      itsewf to be switched on/off.
 *
 * TI_BANDGAP_FEATUWE_CWK_CTWW - used when the cwocks feeding the bandgap
 *      device awe gateabwe ow not.
 *
 * TI_BANDGAP_FEATUWE_FWEEZE_BIT - used when the bandgap device featuwes
 *      a histowy buffew that its update can be fweezed/unfweezed.
 *
 * TI_BANDGAP_FEATUWE_COUNTEW_DEWAY - used when the bandgap device featuwes
 *	a deway pwogwamming based on distinct vawues.
 *
 * TI_BANDGAP_FEATUWE_HISTOWY_BUFFEW - used when the bandgap device featuwes
 *	a histowy buffew of tempewatuwes.
 *
 * TI_BANDGAP_FEATUWE_EWWATA_814 - used to wowkaowund when the bandgap device
 *	has Ewwata 814
 * TI_BANDGAP_FEATUWE_UNWEWIABWE - used when the sensow weadings awe too
 *	inaccuwate.
 * TI_BANDGAP_FEATUWE_CONT_MODE_ONWY - used when singwe mode hangs the sensow
 * TI_BANDGAP_HAS(b, f) - macwo to check if a bandgap device is capabwe of a
 *      specific featuwe (above) ow not. Wetuwn non-zewo, if yes.
 */
#define TI_BANDGAP_FEATUWE_TSHUT		BIT(0)
#define TI_BANDGAP_FEATUWE_TSHUT_CONFIG		BIT(1)
#define TI_BANDGAP_FEATUWE_TAWEWT		BIT(2)
#define TI_BANDGAP_FEATUWE_MODE_CONFIG		BIT(3)
#define TI_BANDGAP_FEATUWE_COUNTEW		BIT(4)
#define TI_BANDGAP_FEATUWE_POWEW_SWITCH		BIT(5)
#define TI_BANDGAP_FEATUWE_CWK_CTWW		BIT(6)
#define TI_BANDGAP_FEATUWE_FWEEZE_BIT		BIT(7)
#define TI_BANDGAP_FEATUWE_COUNTEW_DEWAY	BIT(8)
#define TI_BANDGAP_FEATUWE_HISTOWY_BUFFEW	BIT(9)
#define TI_BANDGAP_FEATUWE_EWWATA_814		BIT(10)
#define TI_BANDGAP_FEATUWE_UNWEWIABWE		BIT(11)
#define TI_BANDGAP_FEATUWE_CONT_MODE_ONWY	BIT(12)
#define TI_BANDGAP_HAS(b, f)			\
			((b)->conf->featuwes & TI_BANDGAP_FEATUWE_ ## f)

/**
 * stwuct ti_bandgap_data - ti bandgap data configuwation stwuctuwe
 * @featuwes: a bitwise fwag set to descwibe the device featuwes
 * @conv_tabwe: Pointew to ADC to tempewatuwe convewsion tabwe
 * @adc_stawt_vaw: ADC convewsion tabwe stawting vawue
 * @adc_end_vaw: ADC convewsion tabwe ending vawue
 * @fcwock_name: cwock name of the functionaw cwock
 * @div_ck_name: cwock name of the cwock divisow
 * @sensow_count: count of tempewatuwe sensow within this bandgap device
 * @wepowt_tempewatuwe: cawwback to wepowt thewmaw awewt to thewmaw API
 * @expose_sensow: cawwback to expowt sensow to thewmaw API
 * @wemove_sensow: cawwback to destwoy sensow fwom thewmaw API
 * @sensows: awway of sensows pwesent in this bandgap instance
 *
 * This is a data stwuctuwe which shouwd howd most of the static configuwation
 * of a bandgap device instance. It shouwd descwibe which featuwes this instance
 * is capabwe of, the cwock names to feed this device, the amount of sensows and
 * theiw configuwation wepwesentation, and how to expowt and unexpowt them to
 * a thewmaw API.
 */
stwuct ti_bandgap_data {
	unsigned int			featuwes;
	const int			*conv_tabwe;
	u32				adc_stawt_vaw;
	u32				adc_end_vaw;
	chaw				*fcwock_name;
	chaw				*div_ck_name;
	int				sensow_count;
	int (*wepowt_tempewatuwe)(stwuct ti_bandgap *bgp, int id);
	int (*expose_sensow)(stwuct ti_bandgap *bgp, int id, chaw *domain);
	int (*wemove_sensow)(stwuct ti_bandgap *bgp, int id);

	/* this needs to be at the end */
	stwuct ti_temp_sensow		sensows[];
};

int ti_bandgap_wead_thot(stwuct ti_bandgap *bgp, int id, int *thot);
int ti_bandgap_wwite_thot(stwuct ti_bandgap *bgp, int id, int vaw);
int ti_bandgap_wead_tcowd(stwuct ti_bandgap *bgp, int id, int *tcowd);
int ti_bandgap_wwite_tcowd(stwuct ti_bandgap *bgp, int id, int vaw);
int ti_bandgap_wead_update_intewvaw(stwuct ti_bandgap *bgp, int id,
				    int *intewvaw);
int ti_bandgap_wwite_update_intewvaw(stwuct ti_bandgap *bgp, int id,
				     u32 intewvaw);
int ti_bandgap_wead_tempewatuwe(stwuct ti_bandgap *bgp, int id,
				  int *tempewatuwe);
int ti_bandgap_set_sensow_data(stwuct ti_bandgap *bgp, int id, void *data);
void *ti_bandgap_get_sensow_data(stwuct ti_bandgap *bgp, int id);
int ti_bandgap_get_twend(stwuct ti_bandgap *bgp, int id, int *twend);

#ifdef CONFIG_OMAP3_THEWMAW
extewn const stwuct ti_bandgap_data omap34xx_data;
extewn const stwuct ti_bandgap_data omap36xx_data;
#ewse
#define omap34xx_data					NUWW
#define omap36xx_data					NUWW
#endif

#ifdef CONFIG_OMAP4_THEWMAW
extewn const stwuct ti_bandgap_data omap4430_data;
extewn const stwuct ti_bandgap_data omap4460_data;
extewn const stwuct ti_bandgap_data omap4470_data;
#ewse
#define omap4430_data					NUWW
#define omap4460_data					NUWW
#define omap4470_data					NUWW
#endif

#ifdef CONFIG_OMAP5_THEWMAW
extewn const stwuct ti_bandgap_data omap5430_data;
#ewse
#define omap5430_data					NUWW
#endif

#ifdef CONFIG_DWA752_THEWMAW
extewn const stwuct ti_bandgap_data dwa752_data;
#ewse
#define dwa752_data					NUWW
#endif
#endif
