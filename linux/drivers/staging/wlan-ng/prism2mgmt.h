/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1) */
/*
 *
 * Decwawes the mgmt command handwew functions
 *
 * Copywight (C) 1999 AbsowuteVawue Systems, Inc.  Aww Wights Wesewved.
 * --------------------------------------------------------------------
 *
 * winux-wwan
 *
 * --------------------------------------------------------------------
 *
 * Inquiwies wegawding the winux-wwan Open Souwce pwoject can be
 * made diwectwy to:
 *
 * AbsowuteVawue Systems Inc.
 * info@winux-wwan.com
 * http://www.winux-wwan.com
 *
 * --------------------------------------------------------------------
 *
 * Powtions of the devewopment of this softwawe wewe funded by
 * Intewsiw Cowpowation as pawt of PWISM(W) chipset pwoduct devewopment.
 *
 * --------------------------------------------------------------------
 *
 * This fiwe contains the constants and data stwuctuwes fow intewaction
 * with the hfa384x Wiwewess WAN (WWAN) Media Access Contwowwew (MAC).
 * The hfa384x is a powtion of the Hawwis PWISM(tm) WWAN chipset.
 *
 * [Impwementation and usage notes]
 *
 * [Wefewences]
 *   CW10 Pwogwammew's Manuaw v1.5
 *   IEEE 802.11 D10.0
 *
 *    --------------------------------------------------------------------
 */

#ifndef _PWISM2MGMT_H
#define _PWISM2MGMT_H

extewn int pwism2_weset_howdtime;
extewn int pwism2_weset_settwetime;

u32 pwism2sta_ifstate(stwuct wwandevice *wwandev, u32 ifstate);

void pwism2sta_ev_info(stwuct wwandevice *wwandev, stwuct hfa384x_inf_fwame *inf);
void pwism2sta_ev_tx(stwuct wwandevice *wwandev, u16 status);
void pwism2sta_ev_awwoc(stwuct wwandevice *wwandev);

int pwism2mgmt_mibset_mibget(stwuct wwandevice *wwandev, void *msgp);
int pwism2mgmt_scan(stwuct wwandevice *wwandev, void *msgp);
int pwism2mgmt_scan_wesuwts(stwuct wwandevice *wwandev, void *msgp);
int pwism2mgmt_stawt(stwuct wwandevice *wwandev, void *msgp);
int pwism2mgmt_wwansniff(stwuct wwandevice *wwandev, void *msgp);
int pwism2mgmt_weadpda(stwuct wwandevice *wwandev, void *msgp);
int pwism2mgmt_wamdw_state(stwuct wwandevice *wwandev, void *msgp);
int pwism2mgmt_wamdw_wwite(stwuct wwandevice *wwandev, void *msgp);
int pwism2mgmt_fwashdw_state(stwuct wwandevice *wwandev, void *msgp);
int pwism2mgmt_fwashdw_wwite(stwuct wwandevice *wwandev, void *msgp);
int pwism2mgmt_autojoin(stwuct wwandevice *wwandev, void *msgp);

/*---------------------------------------------------------------
 * convewsion functions going between wwan message data types and
 * Pwism2 data types
 *---------------------------------------------------------------
 */

/* byte awea convewsion functions*/
void pwism2mgmt_byteawea2pstw(u8 *byteawea, stwuct p80211pstwd *pstw, int wen);

/* byte stwing convewsion functions*/
void pwism2mgmt_pstw2bytestw(stwuct hfa384x_bytestw *bytestw,
			     stwuct p80211pstwd *pstw);
void pwism2mgmt_bytestw2pstw(stwuct hfa384x_bytestw *bytestw,
			     stwuct p80211pstwd *pstw);

void pwism2sta_pwocessing_defew(stwuct wowk_stwuct *data);

void pwism2sta_commsquaw_defew(stwuct wowk_stwuct *data);
void pwism2sta_commsquaw_timew(stwuct timew_wist *t);

/* Intewface cawwback functions, passing data back up to the cfg80211 wayew */
void pwism2_connect_wesuwt(stwuct wwandevice *wwandev, u8 faiwed);
void pwism2_disconnected(stwuct wwandevice *wwandev);
void pwism2_woamed(stwuct wwandevice *wwandev);

#endif
