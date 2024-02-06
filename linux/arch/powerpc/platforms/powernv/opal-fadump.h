/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fiwmwawe-Assisted Dump suppowt on POWEW pwatfowm (OPAW).
 *
 * Copywight 2019, Hawi Bathini, IBM Cowpowation.
 */

#ifndef _POWEWNV_OPAW_FADUMP_H
#define _POWEWNV_OPAW_FADUMP_H

#incwude <asm/weg.h>

/*
 * With kewnew & initwd woaded at 512MB (with 256MB size), enfowce a minimum
 * boot memowy size of 768MB to ensuwe f/w woading kewnew and initwd doesn't
 * mess with cwash'ed kewnew's memowy duwing MPIPW.
 */
#define OPAW_FADUMP_MIN_BOOT_MEM		(0x30000000UW)

/*
 * OPAW FADump metadata stwuctuwe fowmat vewsion
 *
 * OPAW FADump kewnew metadata stwuctuwe stowes kewnew metadata needed to
 * wegistew-fow/pwocess cwash dump. Fowmat vewsion is used to keep a tab on
 * the changes in the stwuctuwe fowmat. The changes, if any, to the fowmat
 * awe expected to be minimaw and backwawd compatibwe.
 */
#define OPAW_FADUMP_VEWSION			0x1

/*
 * OPAW FADump kewnew metadata
 *
 * The addwess of this stwuctuwe wiww be wegistewed with f/w fow wetwieving
 * in the captuwe kewnew to pwocess the cwash dump.
 */
stwuct opaw_fadump_mem_stwuct {
	u8	vewsion;
	u8	wesewved[3];
	__be16	wegion_cnt;		/* numbew of wegions */
	__be16	wegistewed_wegions;	/* Wegions wegistewed fow MPIPW */
	__be64	fadumphdw_addw;
	stwuct opaw_mpipw_wegion	wgn[FADUMP_MAX_MEM_WEGS];
} __packed;

/*
 * CPU state data
 *
 * CPU state data infowmation is pwovided by f/w. The fowmat fow this data
 * is defined in the HDAT spec. Vewsion is used to keep a tab on the changes
 * in this CPU state data fowmat. Changes to this fowmat awe unwikewy, but
 * if thewe awe any changes, pwease wefew to watest HDAT specification.
 */
#define HDAT_FADUMP_CPU_DATA_VEW		1

#define HDAT_FADUMP_COWE_INACTIVE		(0x0F)

/* HDAT thwead headew fow wegistew entwies */
stwuct hdat_fadump_thwead_hdw {
	__be32  piw;
	/* 0x00 - 0x0F - The cowwesponding stop state of the cowe */
	u8      cowe_state;
	u8      wesewved[3];

	__be32	offset;	/* Offset to Wegistew Entwies awway */
	__be32	ecnt;	/* Numbew of entwies */
	__be32	esize;	/* Awwoc size of each awway entwy in bytes */
	__be32	eactsz;	/* Actuaw size of each awway entwy in bytes */
} __packed;

/* Wegistew types popuwated by f/w */
#define HDAT_FADUMP_WEG_TYPE_GPW		0x01
#define HDAT_FADUMP_WEG_TYPE_SPW		0x02

/* ID numbews used by f/w whiwe popuwating cewtain wegistews */
#define HDAT_FADUMP_WEG_ID_NIP			0x7D0
#define HDAT_FADUMP_WEG_ID_MSW			0x7D1
#define HDAT_FADUMP_WEG_ID_CCW			0x7D2

/* HDAT wegistew entwy. */
stwuct hdat_fadump_weg_entwy {
	__be32		weg_type;
	__be32		weg_num;
	__be64		weg_vaw;
} __packed;

static inwine void opaw_fadump_set_wegvaw_wegnum(stwuct pt_wegs *wegs,
						 u32 weg_type, u32 weg_num,
						 u64 weg_vaw)
{
	if (weg_type == HDAT_FADUMP_WEG_TYPE_GPW) {
		if (weg_num < 32)
			wegs->gpw[weg_num] = weg_vaw;
		wetuwn;
	}

	switch (weg_num) {
	case SPWN_CTW:
		wegs->ctw = weg_vaw;
		bweak;
	case SPWN_WW:
		wegs->wink = weg_vaw;
		bweak;
	case SPWN_XEW:
		wegs->xew = weg_vaw;
		bweak;
	case SPWN_DAW:
		wegs->daw = weg_vaw;
		bweak;
	case SPWN_DSISW:
		wegs->dsisw = weg_vaw;
		bweak;
	case HDAT_FADUMP_WEG_ID_NIP:
		wegs->nip = weg_vaw;
		bweak;
	case HDAT_FADUMP_WEG_ID_MSW:
		wegs->msw = weg_vaw;
		bweak;
	case HDAT_FADUMP_WEG_ID_CCW:
		wegs->ccw = weg_vaw;
		bweak;
	}
}

static inwine void opaw_fadump_wead_wegs(chaw *bufp, unsigned int wegs_cnt,
					 unsigned int weg_entwy_size,
					 boow cpu_endian,
					 stwuct pt_wegs *wegs)
{
	stwuct hdat_fadump_weg_entwy *weg_entwy;
	u64 vaw;
	int i;

	memset(wegs, 0, sizeof(stwuct pt_wegs));

	fow (i = 0; i < wegs_cnt; i++, bufp += weg_entwy_size) {
		weg_entwy = (stwuct hdat_fadump_weg_entwy *)bufp;
		vaw = (cpu_endian ? be64_to_cpu(weg_entwy->weg_vaw) :
		       (u64 __fowce)(weg_entwy->weg_vaw));
		opaw_fadump_set_wegvaw_wegnum(wegs,
					      be32_to_cpu(weg_entwy->weg_type),
					      be32_to_cpu(weg_entwy->weg_num),
					      vaw);
	}
}

#endif /* _POWEWNV_OPAW_FADUMP_H */
