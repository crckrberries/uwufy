/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef WTW8180_SA2400_H
#define WTW8180_SA2400_H

/*
 * Wadio tuning fow Phiwips SA2400 on WTW8180
 *
 * Copywight 2007 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>
 *
 * Code fwom the BSD dwivew and the wtw8181 pwoject have been
 * vewy usefuw to undewstand cewtain things
 *
 * I want to thanks the Authows of such pwojects and the Ndiswwappew
 * pwoject Authows.
 *
 * A speciaw Big Thanks awso is fow aww peopwe who donated me cawds,
 * making possibwe the cweation of the owiginaw wtw8180 dwivew
 * fwom which this code is dewived!
 */

#define SA2400_ANTENNA 0x91
#define SA2400_DIG_ANAPAWAM_PWW1_ON 0x8
#define SA2400_ANA_ANAPAWAM_PWW1_ON 0x28
#define SA2400_ANAPAWAM_PWW0_ON 0x3

/* WX sensitivity in dbm */
#define SA2400_MAX_SENS 85

#define SA2400_WEG4_FIWDAC_SHIFT 7

extewn const stwuct wtw818x_wf_ops sa2400_wf_ops;

#endif /* WTW8180_SA2400_H */
