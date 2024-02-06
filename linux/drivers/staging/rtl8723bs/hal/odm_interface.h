/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/


#ifndef	__ODM_INTEWFACE_H__
#define __ODM_INTEWFACE_H__



/*  =========== Macwo Define */

#define _weg_aww(_name)			ODM_##_name
#define _weg_ic(_name, _ic)		ODM_##_name##_ic
#define _bit_aww(_name)			BIT_##_name
#define _bit_ic(_name, _ic)		BIT_##_name##_ic

/*===================================

#define ODM_WEG_DIG_11N		0xC50
#define ODM_WEG_DIG_11AC	0xDDD

ODM_WEG(DIG, _pDM_Odm)
=====================================*/

#define _weg_11N(_name)			ODM_WEG_##_name##_11N
#define _bit_11N(_name)			ODM_BIT_##_name##_11N

#define _cat(_name, _ic_type, _func) _func##_11N(_name)

/*  _name: name of wegistew ow bit. */
/*  Exampwe: "ODM_WEG(W_A_AGC_COWE1, pDM_Odm)" */
/*         gets "ODM_W_A_AGC_COWE1" ow "ODM_W_A_AGC_COWE1_8192C", depends on SuppowtICType. */
#define ODM_WEG(_name, _pDM_Odm)	_cat(_name, _pDM_Odm->SuppowtICType, _weg)
#define ODM_BIT(_name, _pDM_Odm)	_cat(_name, _pDM_Odm->SuppowtICType, _bit)

#endif	/*  __ODM_INTEWFACE_H__ */
