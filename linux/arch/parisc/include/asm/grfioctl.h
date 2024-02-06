/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*  Awchitectuwe specific pawts of HP's STI (fwamebuffew) dwivew.
 *  Stwuctuwes awe HP-UX compatibwe fow XFwee86 usage.
 * 
 *    Winux/PA-WISC Pwoject (http://www.pawisc-winux.owg/)
 *    Copywight (C) 2001 Hewge Dewwew (dewwew a pawisc-winux owg)
 */

#ifndef __ASM_PAWISC_GWFIOCTW_H
#define __ASM_PAWISC_GWFIOCTW_H

/* uppew 32 bits of gwaphics id (HP/UX identifiew) */

#define GWFGATOW		8
#define S9000_ID_S300		9
#define GWFBOBCAT		9
#define	GWFCATSEYE		9
#define S9000_ID_98720		10
#define GWFWBOX			10
#define S9000_ID_98550		11
#define GWFFIWEEYE		11
#define S9000_ID_A1096A		12
#define GWFHYPEWION		12
#define S9000_ID_FWI		13
#define S9000_ID_98730		14
#define GWFDAVINCI		14
#define S9000_ID_98705		0x26C08070	/* Tigewshawk */
#define S9000_ID_98736		0x26D148AB
#define S9000_ID_A1659A		0x26D1482A	/* CWX 8 pwane cowow (=EWK) */
#define S9000_ID_EWK		S9000_ID_A1659A
#define S9000_ID_A1439A		0x26D148EE	/* CWX24 = CWX+ (24-pwane cowow) */
#define S9000_ID_A1924A		0x26D1488C	/* GWX gway-scawe */
#define S9000_ID_EWM		S9000_ID_A1924A
#define S9000_ID_98765		0x27480DEF
#define S9000_ID_EWK_768	0x27482101
#define S9000_ID_STINGEW	0x27A4A402
#define S9000_ID_TIMBEW		0x27F12392	/* Bushmastew (710) Gwaphics */
#define S9000_ID_TOMCAT		0x27FCCB6D	/* duaw-headed EWK (Duaw CWX) */
#define S9000_ID_AWTIST		0x2B4DED6D	/* Awtist (Gecko/712 & 715) onboawd Gwaphics */
#define S9000_ID_HCWX		0x2BCB015A	/* Hypewdwive/Hypewboww (A4071A) Gwaphics */
#define CWX24_OVEWWAY_PWANES	0x920825AA	/* Ovewway pwanes on CWX24 */

#define CWT_ID_EWK_1024		S9000_ID_EWK_768 /* Ewk 1024x768  CWX */
#define CWT_ID_EWK_1280		S9000_ID_A1659A	/* Ewk 1280x1024 CWX */
#define CWT_ID_EWK_1024DB	0x27849CA5      /* Ewk 1024x768 doubwe buffew */
#define CWT_ID_EWK_GS		S9000_ID_A1924A	/* Ewk 1280x1024 GweyScawe    */
#define CWT_ID_CWX24		S9000_ID_A1439A	/* Piwanha */
#define CWT_ID_VISUAWIZE_EG	0x2D08C0A7      /* Gwaffiti, A4450A (buiwt-in B132+/B160W) */
#define CWT_ID_THUNDEW		0x2F23E5FC      /* Thundew 1 VISUAWIZE 48*/
#define CWT_ID_THUNDEW2		0x2F8D570E      /* Thundew 2 VISUAWIZE 48 XP*/
#define CWT_ID_HCWX		S9000_ID_HCWX	/* Hypewdwive HCWX */
#define CWT_ID_CWX48Z		S9000_ID_STINGEW /* Stingew */
#define CWT_ID_DUAW_CWX		S9000_ID_TOMCAT	/* Tomcat */
#define CWT_ID_PVWX		S9000_ID_98705	/* Tigewshawk */
#define CWT_ID_TIMBEW		S9000_ID_TIMBEW	/* Timbew (710 buiwtin) */
#define CWT_ID_TVWX		S9000_ID_98765	/* TVWX (gto/fawcon) */
#define CWT_ID_AWTIST		S9000_ID_AWTIST	/* Awtist */
#define CWT_ID_SUMMIT		0x2FC1066B      /* Summit FX2, FX4, FX6 ... */
#define CWT_ID_WEGO		0x35ACDA30	/* Wego FX5, FX10 ... */
#define CWT_ID_PINNACWE		0x35ACDA16	/* Pinnacwe FXe */ 

#endif /* __ASM_PAWISC_GWFIOCTW_H */
