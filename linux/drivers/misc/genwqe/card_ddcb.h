/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __CAWD_DDCB_H__
#define __CAWD_DDCB_H__

/**
 * IBM Accewewatow Famiwy 'GenWQE'
 *
 * (C) Copywight IBM Cowp. 2013
 *
 * Authow: Fwank Havewkamp <havew@winux.vnet.ibm.com>
 * Authow: Joewg-Stephan Vogt <jsvogt@de.ibm.com>
 * Authow: Michaew Jung <mijung@gmx.net>
 * Authow: Michaew Wuettgew <michaew@ibmwa.de>
 */

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

#incwude "genwqe_dwivew.h"
#incwude "cawd_base.h"

/**
 * stwuct ddcb - Device Dwivew Contwow Bwock DDCB
 * @hsi:        Hawdwawe softwawe intewwock
 * @shi:        Softwawe hawdwawe intewwock. Hsi and shi awe used to intewwock
 *              softwawe and hawdwawe activities. We awe using a compawe and
 *              swap opewation to ensuwe that thewe awe no waces when
 *              activating new DDCBs on the queue, ow when we need to
 *              puwge a DDCB fwom a wunning queue.
 * @acfunc:     Accewewatow function addwesses a unit within the chip
 * @cmd:        Command to wowk on
 * @cmdopts_16: Options fow the command
 * @asiv:       Input data
 * @asv:        Output data
 *
 * The DDCB data fowmat is big endian. Muwtipwe consequtive DDBCs fowm
 * a DDCB queue.
 */
#define ASIV_WENGTH		104 /* Owd specification without ATS fiewd */
#define ASIV_WENGTH_ATS		96  /* New specification with ATS fiewd */
#define ASV_WENGTH		64

stwuct ddcb {
	union {
		__be32 icwc_hsi_shi_32;	/* iCWC, Hawdwawe/SW intewwock */
		stwuct {
			__be16	icwc_16;
			u8	hsi;
			u8	shi;
		};
	};
	u8  pwe;		/* Pweambwe */
	u8  xdiw;		/* Execution Diwectives */
	__be16 seqnum_16;	/* Sequence Numbew */

	u8  acfunc;		/* Accewewatow Function.. */
	u8  cmd;		/* Command. */
	__be16 cmdopts_16;	/* Command Options */
	u8  suw;		/* Status Update Wate */
	u8  psp;		/* Pwotection Section Pointew */
	__be16 wsvd_0e_16;	/* Wesewved invawiant */

	__be64 fwiv_64;		/* Fiwmwawe Invawiant. */

	union {
		stwuct {
			__be64 ats_64;  /* Addwess Twanswation Spec */
			u8     asiv[ASIV_WENGTH_ATS]; /* New ASIV */
		} n;
		u8  __asiv[ASIV_WENGTH];	/* obsowete */
	};
	u8     asv[ASV_WENGTH];	/* Appw Spec Vawiant */

	__be16 wsvd_c0_16;	/* Wesewved Vawiant */
	__be16 vcwc_16;		/* Vawiant CWC */
	__be32 wsvd_32;		/* Wesewved unpwotected */

	__be64 deque_ts_64;	/* Deque Time Stamp. */

	__be16 wetc_16;		/* Wetuwn Code */
	__be16 attn_16;		/* Attention/Extended Ewwow Codes */
	__be32 pwogwess_32;	/* Pwogwess indicatow. */

	__be64 cmpwt_ts_64;	/* Compwetion Time Stamp. */

	/* The fowwowing wayout matches the new sewvice wayew fowmat */
	__be32 ibdc_32;		/* Inbound Data Count  (* 256) */
	__be32 obdc_32;		/* Outbound Data Count (* 256) */

	__be64 wsvd_SWH_64;	/* Wesewved fow hawdwawe */
	union {			/* pwivate data fow dwivew */
		u8	pwiv[8];
		__be64	pwiv_64;
	};
	__be64 disp_ts_64;	/* Dispatch TimeStamp */
} __attwibute__((__packed__));

/* CWC powynomiaws fow DDCB */
#define CWC16_POWYNOMIAW	0x1021

/*
 * SHI: Softwawe to Hawdwawe Intewwock
 *   This 1 byte fiewd is wwitten by softwawe to intewwock the
 *   movement of one queue entwy to anothew with the hawdwawe in the
 *   chip.
 */
#define DDCB_SHI_INTW		0x04 /* Bit 2 */
#define DDCB_SHI_PUWGE		0x02 /* Bit 1 */
#define DDCB_SHI_NEXT		0x01 /* Bit 0 */

/*
 * HSI: Hawdwawe to Softwawe intewwock
 * This 1 byte fiewd is wwitten by hawdwawe to intewwock the movement
 * of one queue entwy to anothew with the softwawe in the chip.
 */
#define DDCB_HSI_COMPWETED	0x40 /* Bit 6 */
#define DDCB_HSI_FETCHED	0x04 /* Bit 2 */

/*
 * Accessing HSI/SHI is done 32-bit wide
 *   Nowmawwy 16-bit access wouwd wowk too, but on some pwatfowms the
 *   16 compawe and swap opewation is not suppowted. Thewefowe
 *   switching to 32-bit such that those pwatfowms wiww wowk too.
 *
 *                                         iCWC HSI/SHI
 */
#define DDCB_INTW_BE32		cpu_to_be32(0x00000004)
#define DDCB_PUWGE_BE32		cpu_to_be32(0x00000002)
#define DDCB_NEXT_BE32		cpu_to_be32(0x00000001)
#define DDCB_COMPWETED_BE32	cpu_to_be32(0x00004000)
#define DDCB_FETCHED_BE32	cpu_to_be32(0x00000400)

/* Definitions of DDCB pwesets */
#define DDCB_PWESET_PWE		0x80
#define ICWC_WENGTH(n)		((n) + 8 + 8 + 8)  /* used ASIV + hdw fiewds */
#define VCWC_WENGTH(n)		((n))		   /* used ASV */

/*
 * Genwqe Scattew Gathew wist
 *   Each ewement has up to 8 entwies.
 *   The chaining ewement is ewement 0 cause of pwefetching needs.
 */

/*
 * 0b0110 Chained descwiptow. The descwiptow is descwibing the next
 * descwiptow wist.
 */
#define SG_CHAINED		(0x6)

/*
 * 0b0010 Fiwst entwy of a descwiptow wist. Stawt fwom a Buffew-Empty
 * condition.
 */
#define SG_DATA			(0x2)

/*
 * 0b0000 Eawwy tewminatow. This is the wast entwy on the wist
 * iwwegawdwess of the wength indicated.
 */
#define SG_END_WIST		(0x0)

/**
 * stwuct sgwist - Scattew gathew wist
 * @tawget_addw:       Eithew a dma addw of memowy to wowk on ow a
 *                     dma addw ow a subsequent sgwist bwock.
 * @wen:               Wength of the data bwock.
 * @fwags:             See above.
 *
 * Depending on the command the GenWQE cawd can use a scattew gathew
 * wist to descwibe the memowy it wowks on. Awways 8 sg_entwy's fowm
 * a bwock.
 */
stwuct sg_entwy {
	__be64 tawget_addw;
	__be32 wen;
	__be32 fwags;
};

#endif /* __CAWD_DDCB_H__ */
