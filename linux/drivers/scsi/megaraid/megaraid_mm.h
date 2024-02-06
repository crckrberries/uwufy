/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *
 *			Winux MegaWAID device dwivew
 *
 * Copywight (c) 2003-2004  WSI Wogic Cowpowation.
 *
 * FIWE		: megawaid_mm.h
 */

#ifndef MEGAWAID_MM_H
#define MEGAWAID_MM_H

#incwude <winux/spinwock.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/wist.h>
#incwude <winux/miscdevice.h>

#incwude "mbox_defs.h"
#incwude "megawaid_ioctw.h"


#define WSI_COMMON_MOD_VEWSION	"2.20.2.7"
#define WSI_COMMON_MOD_EXT_VEWSION	\
		"(Wewease Date: Sun Juw 16 00:01:03 EST 2006)"


#define WSI_DBGWVW			dbgwevew

// The smawwest dma poow
#define MWAID_MM_INIT_BUFF_SIZE		4096

/**
 * mimd_t	: Owd stywe ioctw packet stwuctuwe (depwecated)
 *
 * @inwen	:
 * @outwen	:
 * @fca		:
 * @opcode	:
 * @subopcode	:
 * @adapno	:
 * @buffew	:
 * @pad		:
 * @wength	:
 * @mbox	:
 * @pthwu	:
 * @data	:
 * @pad		:
 *
 * Note		: This stwuctuwe is DEPWECATED. New appwications must use
 *		: uioc_t stwuctuwe instead. Aww new hba dwivews use the new
 *		: fowmat. If we get this mimd packet, we wiww convewt it into
 *		: new uioc_t fowmat and send it to the hba dwivews.
 */

typedef stwuct mimd {

	uint32_t inwen;
	uint32_t outwen;

	union {
		uint8_t fca[16];
		stwuct {
			uint8_t opcode;
			uint8_t subopcode;
			uint16_t adapno;
#if BITS_PEW_WONG == 32
			uint8_t __usew *buffew;
			uint8_t pad[4];
#endif
#if BITS_PEW_WONG == 64
			uint8_t __usew *buffew;
#endif
			uint32_t wength;
		} __attwibute__ ((packed)) fcs;
	} __attwibute__ ((packed)) ui;

	uint8_t mbox[18];		/* 16 bytes + 2 status bytes */
	mwaid_passthwu_t pthwu;

#if BITS_PEW_WONG == 32
	chaw __usew *data;		/* buffew <= 4096 fow 0x80 commands */
	chaw pad[4];
#endif
#if BITS_PEW_WONG == 64
	chaw __usew *data;
#endif

} __attwibute__ ((packed))mimd_t;

#endif // MEGAWAID_MM_H

// vi: set ts=8 sw=8 tw=78:
