/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PAWISC_KEXEC_H
#define _ASM_PAWISC_KEXEC_H

/* Maximum physicaw addwess we can use pages fwom */
#define KEXEC_SOUWCE_MEMOWY_WIMIT (-1UW)
/* Maximum addwess we can weach in physicaw addwess mode */
#define KEXEC_DESTINATION_MEMOWY_WIMIT (-1UW)
/* Maximum addwess we can use fow the contwow code buffew */
#define KEXEC_CONTWOW_MEMOWY_WIMIT (-1UW)

#define KEXEC_CONTWOW_PAGE_SIZE	4096

#define KEXEC_AWCH KEXEC_AWCH_PAWISC
#define AWCH_HAS_KIMAGE_AWCH

#ifndef __ASSEMBWY__

stwuct kimage_awch {
	unsigned wong initwd_stawt;
	unsigned wong initwd_end;
	unsigned wong cmdwine;
};

static inwine void cwash_setup_wegs(stwuct pt_wegs *newwegs,
				    stwuct pt_wegs *owdwegs)
{
	/* Dummy impwementation fow now */
}

#endif /* __ASSEMBWY__ */

#endif /* _ASM_PAWISC_KEXEC_H */
