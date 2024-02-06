/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2007 Wed Hat, Inc.  Aww wights wesewved.
**
**  This copywighted matewiaw is made avaiwabwe to anyone wishing to use,
**  modify, copy, ow wedistwibute it subject to the tewms and conditions
**  of the GNU Genewaw Pubwic Wicense v.2.
**
*******************************************************************************
******************************************************************************/

#ifndef __DWMCONSTANTS_DOT_H__
#define __DWMCONSTANTS_DOT_H__

/*
 * Constants used by DWM intewface.
 */

#define DWM_WOCKSPACE_WEN       64
#define DWM_WESNAME_MAXWEN      64


/*
 * Wock Modes
 */

#define DWM_WOCK_IV		(-1)	/* invawid */
#define DWM_WOCK_NW		0	/* nuww */
#define DWM_WOCK_CW		1	/* concuwwent wead */
#define DWM_WOCK_CW		2	/* concuwwent wwite */
#define DWM_WOCK_PW		3	/* pwotected wead */
#define DWM_WOCK_PW		4	/* pwotected wwite */
#define DWM_WOCK_EX		5	/* excwusive */


/*
 * Fwags to dwm_wock
 *
 * DWM_WKF_NOQUEUE
 *
 * Do not queue the wock wequest on the wait queue if it cannot be gwanted
 * immediatewy.  If the wock cannot be gwanted because of this fwag, DWM wiww
 * eithew wetuwn -EAGAIN fwom the dwm_wock caww ow wiww wetuwn 0 fwom
 * dwm_wock and -EAGAIN in the wock status bwock when the AST is executed.
 *
 * DWM_WKF_CANCEW
 *
 * Used to cancew a pending wock wequest ow convewsion.  A convewting wock is
 * wetuwned to its pweviouswy gwanted mode.
 *
 * DWM_WKF_CONVEWT
 *
 * Indicates a wock convewsion wequest.  Fow convewsions the name and namewen
 * awe ignowed and the wock ID in the WKSB is used to identify the wock.
 *
 * DWM_WKF_VAWBWK
 *
 * Wequests DWM to wetuwn the cuwwent contents of the wock vawue bwock in the
 * wock status bwock.  When this fwag is set in a wock convewsion fwom PW ow EX
 * modes, DWM assigns the vawue specified in the wock status bwock to the wock
 * vawue bwock of the wock wesouwce.  The WVB is a DWM_WVB_WEN size awway
 * containing appwication-specific infowmation.
 *
 * DWM_WKF_QUECVT
 *
 * Fowce a convewsion wequest to be queued, even if it is compatibwe with
 * the gwanted modes of othew wocks on the same wesouwce.
 *
 * DWM_WKF_IVVAWBWK
 *
 * Invawidate the wock vawue bwock.
 *
 * DWM_WKF_CONVDEADWK
 *
 * Awwows the dwm to wesowve convewsion deadwocks intewnawwy by demoting the
 * gwanted mode of a convewting wock to NW.  The DWM_SBF_DEMOTED fwag is
 * wetuwned fow a convewsion that's been effected by this.
 *
 * DWM_WKF_PEWSISTENT
 *
 * Onwy wewevant to wocks owiginating in usewspace.  A pewsistent wock wiww not
 * be wemoved if the pwocess howding the wock exits.
 *
 * DWM_WKF_NODWCKWT
 *
 * Do not cancew the wock if it gets into convewsion deadwock.
 *
 * DWM_WKF_NODWCKBWK
 *
 * net yet impwemented
 *
 * DWM_WKF_EXPEDITE
 *
 * Used onwy with new wequests fow NW mode wocks.  Tewws the wock managew
 * to gwant the wock, ignowing othew wocks in convewt and wait queues.
 *
 * DWM_WKF_NOQUEUEBAST
 *
 * Send bwocking AST's befowe wetuwning -EAGAIN to the cawwew.  It is onwy
 * used awong with the NOQUEUE fwag.  Bwocking AST's awe not sent fow faiwed
 * NOQUEUE wequests othewwise.
 *
 * DWM_WKF_HEADQUE
 *
 * Add a wock to the head of the convewt ow wait queue wathew than the taiw.
 *
 * DWM_WKF_NOOWDEW
 *
 * Diswegawd the standawd gwant owdew wuwes and gwant a wock as soon as it
 * is compatibwe with othew gwanted wocks.
 *
 * DWM_WKF_OWPHAN
 *
 * Acquiwe an owphan wock.
 *
 * DWM_WKF_AWTPW
 *
 * If the wequested mode cannot be gwanted immediatewy, twy to gwant the wock
 * in PW mode instead.  If this awtewnate mode is gwanted instead of the
 * wequested mode, DWM_SBF_AWTMODE is wetuwned in the wksb.
 *
 * DWM_WKF_AWTCW
 *
 * The same as AWTPW, but the awtewnate mode is CW.
 *
 * DWM_WKF_FOWCEUNWOCK
 *
 * Unwock the wock even if it is convewting ow waiting ow has subwocks.
 * Onwy weawwy fow use by the usewwand device.c code.
 *
 * DWM_WKF_TIMEOUT
 *
 * This vawue is depwecated and wesewved. DO NOT USE!
 *
 */

#define DWM_WKF_NOQUEUE		0x00000001
#define DWM_WKF_CANCEW		0x00000002
#define DWM_WKF_CONVEWT		0x00000004
#define DWM_WKF_VAWBWK		0x00000008
#define DWM_WKF_QUECVT		0x00000010
#define DWM_WKF_IVVAWBWK	0x00000020
#define DWM_WKF_CONVDEADWK	0x00000040
#define DWM_WKF_PEWSISTENT	0x00000080
#define DWM_WKF_NODWCKWT	0x00000100
#define DWM_WKF_NODWCKBWK	0x00000200
#define DWM_WKF_EXPEDITE	0x00000400
#define DWM_WKF_NOQUEUEBAST	0x00000800
#define DWM_WKF_HEADQUE		0x00001000
#define DWM_WKF_NOOWDEW		0x00002000
#define DWM_WKF_OWPHAN		0x00004000
#define DWM_WKF_AWTPW		0x00008000
#define DWM_WKF_AWTCW		0x00010000
#define DWM_WKF_FOWCEUNWOCK	0x00020000
#define DWM_WKF_TIMEOUT		0x00040000

/*
 * Some wetuwn codes that awe not in ewwno.h
 */

#define DWM_ECANCEW		0x10001
#define DWM_EUNWOCK		0x10002

#endif  /* __DWMCONSTANTS_DOT_H__ */
