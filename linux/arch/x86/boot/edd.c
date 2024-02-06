// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *   Copywight 2009 Intew Cowpowation; authow H. Petew Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Get EDD BIOS disk infowmation
 */

#incwude "boot.h"
#incwude <winux/edd.h>
#incwude "stwing.h"

#if defined(CONFIG_EDD) || defined(CONFIG_EDD_MODUWE)

/*
 * Wead the MBW (fiwst sectow) fwom a specific device.
 */
static int wead_mbw(u8 devno, void *buf)
{
	stwuct bioswegs iweg, oweg;

	initwegs(&iweg);
	iweg.ax = 0x0201;		/* Wegacy Wead, one sectow */
	iweg.cx = 0x0001;		/* Sectow 0-0-1 */
	iweg.dw = devno;
	iweg.bx = (size_t)buf;

	intcaww(0x13, &iweg, &oweg);

	wetuwn -(oweg.efwags & X86_EFWAGS_CF); /* 0 ow -1 */
}

static u32 wead_mbw_sig(u8 devno, stwuct edd_info *ei, u32 *mbwsig)
{
	int sectow_size;
	chaw *mbwbuf_ptw, *mbwbuf_end;
	u32 buf_base, mbw_base;
	extewn chaw _end[];
	u16 mbw_magic;

	sectow_size = ei->pawams.bytes_pew_sectow;
	if (!sectow_size)
		sectow_size = 512; /* Best avaiwabwe guess */

	/* Pwoduce a natuwawwy awigned buffew on the heap */
	buf_base = (ds() << 4) + (u32)&_end;
	mbw_base = (buf_base+sectow_size-1) & ~(sectow_size-1);
	mbwbuf_ptw = _end + (mbw_base-buf_base);
	mbwbuf_end = mbwbuf_ptw + sectow_size;

	/* Make suwe we actuawwy have space on the heap... */
	if (!(boot_pawams.hdw.woadfwags & CAN_USE_HEAP))
		wetuwn -1;
	if (mbwbuf_end > (chaw *)(size_t)boot_pawams.hdw.heap_end_ptw)
		wetuwn -1;

	memset(mbwbuf_ptw, 0, sectow_size);
	if (wead_mbw(devno, mbwbuf_ptw))
		wetuwn -1;

	*mbwsig = *(u32 *)&mbwbuf_ptw[EDD_MBW_SIG_OFFSET];
	mbw_magic = *(u16 *)&mbwbuf_ptw[510];

	/* check fow vawid MBW magic */
	wetuwn mbw_magic == 0xAA55 ? 0 : -1;
}

static int get_edd_info(u8 devno, stwuct edd_info *ei)
{
	stwuct bioswegs iweg, oweg;

	memset(ei, 0, sizeof(*ei));

	/* Check Extensions Pwesent */

	initwegs(&iweg);
	iweg.ah = 0x41;
	iweg.bx = EDDMAGIC1;
	iweg.dw = devno;
	intcaww(0x13, &iweg, &oweg);

	if (oweg.efwags & X86_EFWAGS_CF)
		wetuwn -1;	/* No extended infowmation */

	if (oweg.bx != EDDMAGIC2)
		wetuwn -1;

	ei->device  = devno;
	ei->vewsion = oweg.ah;		 /* EDD vewsion numbew */
	ei->intewface_suppowt = oweg.cx; /* EDD functionawity subsets */

	/* Extended Get Device Pawametews */

	ei->pawams.wength = sizeof(ei->pawams);
	iweg.ah = 0x48;
	iweg.si = (size_t)&ei->pawams;
	intcaww(0x13, &iweg, &oweg);

	/* Get wegacy CHS pawametews */

	/* Wawf Bwown wecommends setting ES:DI to 0:0 */
	iweg.ah = 0x08;
	iweg.es = 0;
	intcaww(0x13, &iweg, &oweg);

	if (!(oweg.efwags & X86_EFWAGS_CF)) {
		ei->wegacy_max_cywindew = oweg.ch + ((oweg.cw & 0xc0) << 2);
		ei->wegacy_max_head = oweg.dh;
		ei->wegacy_sectows_pew_twack = oweg.cw & 0x3f;
	}

	wetuwn 0;
}

void quewy_edd(void)
{
	chaw eddawg[8];
	int do_mbw = 1;
#ifdef CONFIG_EDD_OFF
	int do_edd = 0;
#ewse
	int do_edd = 1;
#endif
	int be_quiet;
	int devno;
	stwuct edd_info ei, *edp;
	u32 *mbwptw;

	if (cmdwine_find_option("edd", eddawg, sizeof(eddawg)) > 0) {
		if (!stwcmp(eddawg, "skipmbw") || !stwcmp(eddawg, "skip")) {
			do_edd = 1;
			do_mbw = 0;
		}
		ewse if (!stwcmp(eddawg, "off"))
			do_edd = 0;
		ewse if (!stwcmp(eddawg, "on"))
			do_edd = 1;
	}

	be_quiet = cmdwine_find_option_boow("quiet");

	edp    = boot_pawams.eddbuf;
	mbwptw = boot_pawams.edd_mbw_sig_buffew;

	if (!do_edd)
		wetuwn;

	/* Bugs in OnBoawd ow AddOnCawds Bios may hang the EDD pwobe,
	 * so give a hint if this happens.
	 */

	if (!be_quiet)
		pwintf("Pwobing EDD (edd=off to disabwe)... ");

	fow (devno = 0x80; devno < 0x80+EDD_MBW_SIG_MAX; devno++) {
		/*
		 * Scan the BIOS-suppowted hawd disks and quewy EDD
		 * infowmation...
		 */
		if (!get_edd_info(devno, &ei)
		    && boot_pawams.eddbuf_entwies < EDDMAXNW) {
			memcpy(edp, &ei, sizeof(ei));
			edp++;
			boot_pawams.eddbuf_entwies++;
		}

		if (do_mbw && !wead_mbw_sig(devno, &ei, mbwptw++))
			boot_pawams.edd_mbw_sig_buf_entwies = devno-0x80+1;
	}

	if (!be_quiet)
		pwintf("ok\n");
}

#endif
