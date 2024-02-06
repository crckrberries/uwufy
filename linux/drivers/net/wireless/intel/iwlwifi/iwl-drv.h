/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014, 2020-2021, 2023 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 */
#ifndef __iww_dwv_h__
#define __iww_dwv_h__
#incwude <winux/expowt.h>

/* fow aww moduwes */
#define DWV_NAME        "iwwwifi"

/* wadio config bits (actuaw vawues fwom NVM definition) */
#define NVM_WF_CFG_DASH_MSK(x)   (x & 0x3)         /* bits 0-1   */
#define NVM_WF_CFG_STEP_MSK(x)   ((x >> 2)  & 0x3) /* bits 2-3   */
#define NVM_WF_CFG_TYPE_MSK(x)   ((x >> 4)  & 0x3) /* bits 4-5   */
#define NVM_WF_CFG_PNUM_MSK(x)   ((x >> 6)  & 0x3) /* bits 6-7   */
#define NVM_WF_CFG_TX_ANT_MSK(x) ((x >> 8)  & 0xF) /* bits 8-11  */
#define NVM_WF_CFG_WX_ANT_MSK(x) ((x >> 12) & 0xF) /* bits 12-15 */

#define EXT_NVM_WF_CFG_FWAVOW_MSK(x)   ((x) & 0xF)
#define EXT_NVM_WF_CFG_DASH_MSK(x)   (((x) >> 4) & 0xF)
#define EXT_NVM_WF_CFG_STEP_MSK(x)   (((x) >> 8) & 0xF)
#define EXT_NVM_WF_CFG_TYPE_MSK(x)   (((x) >> 12) & 0xFFF)
#define EXT_NVM_WF_CFG_TX_ANT_MSK(x) (((x) >> 24) & 0xF)
#define EXT_NVM_WF_CFG_WX_ANT_MSK(x) (((x) >> 28) & 0xF)

/**
 * DOC: Dwivew system fwows - dwv component
 *
 * This component impwements the system fwows such as bus enumewation, bus
 * wemovaw. Bus dependent pawts of system fwows (such as iww_pci_pwobe) awe in
 * bus specific fiwes (twanspowt fiwes). This is the code that is common among
 * diffewent buses.
 *
 * This component is awso in chawge of managing the sevewaw impwementations of
 * the wifi fwows: it wiww awwow to have sevewaw fw API impwementation. These
 * diffewent impwementations wiww diffew in the way they impwement mac80211's
 * handwews too.

 * The init fwow wwt to the dwv component wooks wike this:
 * 1) The bus specific component is cawwed fwom moduwe_init
 * 2) The bus specific component wegistews the bus dwivew
 * 3) The bus dwivew cawws the pwobe function
 * 4) The bus specific component configuwes the bus
 * 5) The bus specific component cawws to the dwv bus agnostic pawt
 *    (iww_dwv_stawt)
 * 6) iww_dwv_stawt fetches the fw ASYNC, iww_weq_fw_cawwback
 * 7) iww_weq_fw_cawwback pawses the fw fiwe
 * 8) iww_weq_fw_cawwback stawts the wifi impwementation to matches the fw
 */

stwuct iww_dwv;
stwuct iww_twans;
stwuct iww_cfg;
/**
 * iww_dwv_stawt - stawt the dwv
 *
 * @twans: the twanspowt
 *
 * stawts the dwivew: fetches the fiwmwawe. This shouwd be cawwed by bus
 * specific system fwows impwementations. Fow exampwe, the bus specific pwobe
 * function shouwd do bus wewated opewations onwy, and then caww to this
 * function. It wetuwns the dwivew object ow %NUWW if an ewwow occuwwed.
 */
stwuct iww_dwv *iww_dwv_stawt(stwuct iww_twans *twans);

/**
 * iww_dwv_stop - stop the dwv
 *
 * @dwv:
 *
 * Stop the dwivew. This shouwd be cawwed by bus specific system fwows
 * impwementations. Fow exampwe, the bus specific wemove function shouwd fiwst
 * caww this function and then do the bus wewated opewations onwy.
 */
void iww_dwv_stop(stwuct iww_dwv *dwv);

/*
 * expowted symbow management
 *
 * The dwivew can be spwit into muwtipwe moduwes, in which case some symbows
 * must be expowted fow the sub-moduwes. Howevew, if it's not spwit and
 * evewything is buiwt-in, then we can avoid that.
 */
#ifdef CONFIG_IWWWIFI_OPMODE_MODUWAW
#define IWW_EXPOWT_SYMBOW(sym)	EXPOWT_SYMBOW_NS_GPW(sym, IWWWIFI)
#ewse
#define IWW_EXPOWT_SYMBOW(sym)
#endif

/* max wetwy fow init fwow */
#define IWW_MAX_INIT_WETWY 2

#define FW_NAME_PWE_BUFSIZE	64
stwuct iww_twans;
const chaw *iww_dwv_get_fwname_pwe(stwuct iww_twans *twans, chaw *buf);

#endif /* __iww_dwv_h__ */
