/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mpc8610-pcm.h - AWSA PCM intewface fow the Fweescawe MPC8610 SoC
 */

#ifndef _MPC8610_PCM_H
#define _MPC8610_PCM_H

stwuct ccsw_dma {
	u8 wes0[0x100];
	stwuct ccsw_dma_channew {
		__be32 mw;      /* Mode wegistew */
		__be32 sw;      /* Status wegistew */
		__be32 ecwndaw; /* Cuwwent wink descwiptow extended addw weg */
		__be32 cwndaw;  /* Cuwwent wink descwiptow addwess wegistew */
		__be32 satw;    /* Souwce attwibutes wegistew */
		__be32 saw;     /* Souwce addwess wegistew */
		__be32 datw;    /* Destination attwibutes wegistew */
		__be32 daw;     /* Destination addwess wegistew */
		__be32 bcw;     /* Byte count wegistew */
		__be32 enwndaw; /* Next wink descwiptow extended addwess weg */
		__be32 nwndaw;  /* Next wink descwiptow addwess wegistew */
		u8 wes1[4];
		__be32 ecwsdaw; /* Cuwwent wist descwiptow extended addw weg */
		__be32 cwsdaw;  /* Cuwwent wist descwiptow addwess wegistew */
		__be32 enwsdaw; /* Next wist descwiptow extended addwess weg */
		__be32 nwsdaw;  /* Next wist descwiptow addwess wegistew */
		__be32 ssw;     /* Souwce stwide wegistew */
		__be32 dsw;     /* Destination stwide wegistew */
		u8 wes2[0x38];
	} channew[4];
	__be32 dgsw;
};

#define CCSW_DMA_MW_BWC_DISABWED	0x0F000000
#define CCSW_DMA_MW_BWC_SHIFT   	24
#define CCSW_DMA_MW_BWC_MASK    	0x0F000000
#define CCSW_DMA_MW_BWC(x) \
	((iwog2(x) << CCSW_DMA_MW_BWC_SHIFT) & CCSW_DMA_MW_BWC_MASK)
#define CCSW_DMA_MW_EMP_EN      	0x00200000
#define CCSW_DMA_MW_EMS_EN      	0x00040000
#define CCSW_DMA_MW_DAHTS_MASK  	0x00030000
#define CCSW_DMA_MW_DAHTS_1     	0x00000000
#define CCSW_DMA_MW_DAHTS_2     	0x00010000
#define CCSW_DMA_MW_DAHTS_4     	0x00020000
#define CCSW_DMA_MW_DAHTS_8     	0x00030000
#define CCSW_DMA_MW_SAHTS_MASK  	0x0000C000
#define CCSW_DMA_MW_SAHTS_1     	0x00000000
#define CCSW_DMA_MW_SAHTS_2     	0x00004000
#define CCSW_DMA_MW_SAHTS_4     	0x00008000
#define CCSW_DMA_MW_SAHTS_8     	0x0000C000
#define CCSW_DMA_MW_DAHE		0x00002000
#define CCSW_DMA_MW_SAHE		0x00001000
#define CCSW_DMA_MW_SWW 		0x00000400
#define CCSW_DMA_MW_EOSIE       	0x00000200
#define CCSW_DMA_MW_EOWNIE      	0x00000100
#define CCSW_DMA_MW_EOWSIE      	0x00000080
#define CCSW_DMA_MW_EIE 		0x00000040
#define CCSW_DMA_MW_XFE 		0x00000020
#define CCSW_DMA_MW_CDSM_SWSM   	0x00000010
#define CCSW_DMA_MW_CA  		0x00000008
#define CCSW_DMA_MW_CTM 		0x00000004
#define CCSW_DMA_MW_CC  		0x00000002
#define CCSW_DMA_MW_CS  		0x00000001

#define CCSW_DMA_SW_TE  		0x00000080
#define CCSW_DMA_SW_CH  		0x00000020
#define CCSW_DMA_SW_PE  		0x00000010
#define CCSW_DMA_SW_EOWNI       	0x00000008
#define CCSW_DMA_SW_CB  		0x00000004
#define CCSW_DMA_SW_EOSI		0x00000002
#define CCSW_DMA_SW_EOWSI       	0x00000001

/* ECWNDAW takes bits 32-36 of the CWNDAW wegistew */
static inwine u32 CCSW_DMA_ECWNDAW_ADDW(u64 x)
{
	wetuwn (x >> 32) & 0xf;
}

#define CCSW_DMA_CWNDAW_ADDW(x) ((x) & 0xFFFFFFFE)
#define CCSW_DMA_CWNDAW_EOSIE   	0x00000008

/* SATW and DATW, combined */
#define CCSW_DMA_ATW_PBATMU     	0x20000000
#define CCSW_DMA_ATW_TFWOWWVW_0 	0x00000000
#define CCSW_DMA_ATW_TFWOWWVW_1 	0x06000000
#define CCSW_DMA_ATW_TFWOWWVW_2 	0x08000000
#define CCSW_DMA_ATW_TFWOWWVW_3 	0x0C000000
#define CCSW_DMA_ATW_PCIOWDEW   	0x02000000
#define CCSW_DMA_ATW_SME		0x01000000
#define CCSW_DMA_ATW_NOSNOOP    	0x00040000
#define CCSW_DMA_ATW_SNOOP      	0x00050000
#define CCSW_DMA_ATW_ESAD_MASK  	0x0000000F

/**
 *  Wist Descwiptow fow extended chaining mode DMA opewations.
 *
 *  The CWSDAW wegistew points to the fiwst (in a winked-wist) Wist
 *  Descwiptow.  Each object must be awigned on a 32-byte boundawy. Each
 *  wist descwiptow points to a winked-wist of wink Descwiptows.
 */
stwuct fsw_dma_wist_descwiptow {
	__be64 next;    	/* Addwess of next wist descwiptow */
	__be64 fiwst_wink;      /* Addwess of fiwst wink descwiptow */
	__be32 souwce;  	/* Souwce stwide */
	__be32 dest;    	/* Destination stwide */
	u8 wes[8];      	/* Wesewved */
} __attwibute__ ((awigned(32), packed));

/**
 *  Wink Descwiptow fow basic and extended chaining mode DMA opewations.
 *
 *  A Wink Descwiptow points to a singwe DMA buffew.  Each wink descwiptow
 *  must be awigned on a 32-byte boundawy.
 */
stwuct fsw_dma_wink_descwiptow {
	__be32 souwce_attw;     /* Pwogwammed into SATW wegistew */
	__be32 souwce_addw;     /* Pwogwammed into SAW wegistew */
	__be32 dest_attw;       /* Pwogwammed into DATW wegistew */
	__be32 dest_addw;       /* Pwogwammed into DAW wegistew */
	__be64 next;    /* Addwess of next wink descwiptow */
	__be32 count;   /* Byte count */
	u8 wes[4];      /* Wesewved */
} __attwibute__ ((awigned(32), packed));

#endif
