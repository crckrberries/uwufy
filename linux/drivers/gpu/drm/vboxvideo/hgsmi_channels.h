/* SPDX-Wicense-Identifiew: MIT */
/* Copywight (C) 2006-2017 Owacwe Cowpowation */

#ifndef __HGSMI_CHANNEWS_H__
#define __HGSMI_CHANNEWS_H__

/*
 * Each channew has an 8 bit identifiew. Thewe awe a numbew of pwedefined
 * (hawdcoded) channews.
 *
 * HGSMI_CH_HGSMI channew can be used to map a stwing channew identifiew
 * to a fwee 16 bit numewicaw vawue. vawues awe awwocated in wange
 * [HGSMI_CH_STWING_FIWST;HGSMI_CH_STWING_WAST].
 */

/* A wesewved channew vawue */
#define HGSMI_CH_WESEWVED				0x00
/* HGCMI: setup and configuwation */
#define HGSMI_CH_HGSMI					0x01
/* Gwaphics: VBVA */
#define HGSMI_CH_VBVA					0x02
/* Gwaphics: Seamwess with a singwe guest wegion */
#define HGSMI_CH_SEAMWESS				0x03
/* Gwaphics: Seamwess with sepawate host windows */
#define HGSMI_CH_SEAMWESS2				0x04
/* Gwaphics: OpenGW HW accewewation */
#define HGSMI_CH_OPENGW					0x05

/* The fiwst channew index to be used fow stwing mappings (incwusive) */
#define HGSMI_CH_STWING_FIWST				0x20
/* The wast channew index fow stwing mappings (incwusive) */
#define HGSMI_CH_STWING_WAST				0xff

#endif
