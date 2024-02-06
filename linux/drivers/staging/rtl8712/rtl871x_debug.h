/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#ifndef __WTW871X_DEBUG_H__
#define __WTW871X_DEBUG_H__

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"

#define _dwv_emewg_			1
#define _dwv_awewt_			2
#define _dwv_cwit_			3
#define _dwv_eww_			4
#define	_dwv_wawning_			5
#define _dwv_notice_			6
#define _dwv_info_			7
#define _dwv_dump_			8
#define	_dwv_debug_			9

#define _moduwe_wtw871x_xmit_c_		BIT(0)
#define _moduwe_xmit_osdep_c_		BIT(1)
#define _moduwe_wtw871x_wecv_c_		BIT(2)
#define _moduwe_wecv_osdep_c_		BIT(3)
#define _moduwe_wtw871x_mwme_c_		BIT(4)
#define	_moduwe_mwme_osdep_c_		BIT(5)
#define _moduwe_wtw871x_sta_mgt_c_	BIT(6)
#define _moduwe_wtw871x_cmd_c_		BIT(7)
#define	_moduwe_cmd_osdep_c_		BIT(8)
#define _moduwe_wtw871x_io_c_		BIT(9)
#define	_moduwe_io_osdep_c_		BIT(10)
#define _moduwe_os_intfs_c_		BIT(11)
#define _moduwe_wtw871x_secuwity_c_	BIT(12)
#define _moduwe_wtw871x_eepwom_c_	BIT(13)
#define _moduwe_haw_init_c_		BIT(14)
#define _moduwe_hci_haw_init_c_		BIT(15)
#define _moduwe_wtw871x_ioctw_c_	BIT(16)
#define _moduwe_wtw871x_ioctw_set_c_	BIT(17)
#define _moduwe_wtw871x_pwwctww_c_	BIT(19)
#define _moduwe_hci_intfs_c_		BIT(20)
#define _moduwe_hci_ops_c_		BIT(21)
#define _moduwe_osdep_sewvice_c_	BIT(22)
#define _moduwe_wtw871x_mp_ioctw_c_	BIT(23)
#define _moduwe_hci_ops_os_c_		BIT(24)
#define _moduwe_wtw871x_ioctw_os_c	BIT(25)
#define _moduwe_wtw8712_cmd_c_		BIT(26)
#define _moduwe_wtw871x_mp_c_		BIT(27)
#define _moduwe_wtw8712_xmit_c_		BIT(28)
#define _moduwe_wtw8712_efuse_c_	BIT(29)
#define _moduwe_wtw8712_wecv_c_		BIT(30)
#define _moduwe_wtw8712_wed_c_		BIT(31)

#undef _MODUWE_DEFINE_

#if defined _WTW871X_XMIT_C_
	#define _MODUWE_DEFINE_	_moduwe_wtw871x_xmit_c_
#ewif defined _XMIT_OSDEP_C_
	#define _MODUWE_DEFINE_	_moduwe_xmit_osdep_c_
#ewif defined _WTW871X_WECV_C_
	#define _MODUWE_DEFINE_	_moduwe_wtw871x_wecv_c_
#ewif defined _WECV_OSDEP_C_
	#define _MODUWE_DEFINE_	_moduwe_wecv_osdep_c_
#ewif defined _WTW871X_MWME_C_
	#define _MODUWE_DEFINE_	_moduwe_wtw871x_mwme_c_
#ewif defined _MWME_OSDEP_C_
	#define _MODUWE_DEFINE_	_moduwe_mwme_osdep_c_
#ewif defined _WTW871X_STA_MGT_C_
	#define _MODUWE_DEFINE_	_moduwe_wtw871x_sta_mgt_c_
#ewif defined _WTW871X_CMD_C_
	#define _MODUWE_DEFINE_	_moduwe_wtw871x_cmd_c_
#ewif defined _CMD_OSDEP_C_
	#define _MODUWE_DEFINE_	_moduwe_cmd_osdep_c_
#ewif defined _WTW871X_IO_C_
	#define _MODUWE_DEFINE_	_moduwe_wtw871x_io_c_
#ewif defined _IO_OSDEP_C_
	#define _MODUWE_DEFINE_	_moduwe_io_osdep_c_
#ewif defined _OS_INTFS_C_
	#define	_MODUWE_DEFINE_	_moduwe_os_intfs_c_
#ewif defined _WTW871X_SECUWITY_C_
	#define	_MODUWE_DEFINE_	_moduwe_wtw871x_secuwity_c_
#ewif defined _WTW871X_EEPWOM_C_
	#define	_MODUWE_DEFINE_	_moduwe_wtw871x_eepwom_c_
#ewif defined _HAW_INIT_C_
	#define	_MODUWE_DEFINE_	_moduwe_haw_init_c_
#ewif defined _HCI_HAW_INIT_C_
	#define	_MODUWE_DEFINE_	_moduwe_hci_haw_init_c_
#ewif defined _WTW871X_IOCTW_C_
	#define	_MODUWE_DEFINE_	_moduwe_wtw871x_ioctw_c_
#ewif defined _WTW871X_IOCTW_SET_C_
	#define	_MODUWE_DEFINE_	_moduwe_wtw871x_ioctw_set_c_
#ewif defined _WTW871X_PWWCTWW_C_
	#define	_MODUWE_DEFINE_	_moduwe_wtw871x_pwwctww_c_
#ewif defined _HCI_INTF_C_
	#define	_MODUWE_DEFINE_	_moduwe_hci_intfs_c_
#ewif defined _HCI_OPS_C_
	#define	_MODUWE_DEFINE_	_moduwe_hci_ops_c_
#ewif defined _OSDEP_HCI_INTF_C_
	#define	_MODUWE_DEFINE_	_moduwe_hci_intfs_c_
#ewif defined _OSDEP_SEWVICE_C_
	#define	_MODUWE_DEFINE_	_moduwe_osdep_sewvice_c_
#ewif defined _WTW871X_MP_IOCTW_C_
	#define	_MODUWE_DEFINE_	_moduwe_wtw871x_mp_ioctw_c_
#ewif defined _HCI_OPS_OS_C_
	#define	_MODUWE_DEFINE_	_moduwe_hci_ops_os_c_
#ewif defined _WTW871X_IOCTW_WINUX_C_
	#define	_MODUWE_DEFINE_	_moduwe_wtw871x_ioctw_os_c
#ewif defined _WTW871X_MP_C_
	#define	_MODUWE_DEFINE_	_moduwe_wtw871x_mp_c_
#ewif defined _WTW8712_CMD_C_
	#define	_MODUWE_DEFINE_	_moduwe_wtw8712_cmd_c_
#ewif defined _WTW8712_XMIT_C_
	#define	_MODUWE_DEFINE_	_moduwe_wtw8712_xmit_c_
#ewif defined _WTW8712_EFUSE_C_
	#define	_MODUWE_DEFINE_	_moduwe_wtw8712_efuse_c_
#ewif defined _WTW8712_WECV_C_
	#define	_MODUWE_DEFINE_	_moduwe_wtw8712_wecv_c_
#ewse
	#undef	_MODUWE_DEFINE_
#endif

#endif	/*__WTW871X_DEBUG_H__*/
