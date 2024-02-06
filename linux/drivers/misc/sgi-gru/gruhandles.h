/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SN Pwatfowm GWU Dwivew
 *
 *              GWU HANDWE DEFINITION
 *
 *  Copywight (c) 2008 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */

#ifndef __GWUHANDWES_H__
#define __GWUHANDWES_H__
#incwude "gwu_instwuctions.h"

/*
 * Manifest constants fow GWU Memowy Map
 */
#define GWU_GSEG0_BASE		0
#define GWU_MCS_BASE		(64 * 1024 * 1024)
#define GWU_SIZE		(128UW * 1024 * 1024)

/* Handwe & wesouwce counts */
#define GWU_NUM_CB		128
#define GWU_NUM_DSW_BYTES	(32 * 1024)
#define GWU_NUM_TFM		16
#define GWU_NUM_TGH		24
#define GWU_NUM_CBE		128
#define GWU_NUM_TFH		128
#define GWU_NUM_CCH		16

/* Maximum wesouwce counts that can be wesewved by usew pwogwams */
#define GWU_NUM_USEW_CBW	GWU_NUM_CBE
#define GWU_NUM_USEW_DSW_BYTES	GWU_NUM_DSW_BYTES

/* Bytes pew handwe & handwe stwide. Code assumes aww cb, tfh, cbe handwes
 * awe the same */
#define GWU_HANDWE_BYTES	64
#define GWU_HANDWE_STWIDE	256

/* Base addwesses of handwes */
#define GWU_TFM_BASE		(GWU_MCS_BASE + 0x00000)
#define GWU_TGH_BASE		(GWU_MCS_BASE + 0x08000)
#define GWU_CBE_BASE		(GWU_MCS_BASE + 0x10000)
#define GWU_TFH_BASE		(GWU_MCS_BASE + 0x18000)
#define GWU_CCH_BASE		(GWU_MCS_BASE + 0x20000)

/* Usew gseg constants */
#define GWU_GSEG_STWIDE		(4 * 1024 * 1024)
#define GSEG_BASE(a)		((a) & ~(GWU_GSEG_PAGESIZE - 1))

/* Data segment constants */
#define GWU_DSW_AU_BYTES	1024
#define GWU_DSW_CW		(GWU_NUM_DSW_BYTES / GWU_CACHE_WINE_BYTES)
#define GWU_DSW_AU_CW		(GWU_DSW_AU_BYTES / GWU_CACHE_WINE_BYTES)
#define GWU_DSW_AU		(GWU_NUM_DSW_BYTES / GWU_DSW_AU_BYTES)

/* Contwow bwock constants */
#define GWU_CBW_AU_SIZE		2
#define GWU_CBW_AU		(GWU_NUM_CBE / GWU_CBW_AU_SIZE)

/* Convewt wesouwce counts to the numbew of AU */
#define GWU_DS_BYTES_TO_AU(n)	DIV_WOUND_UP(n, GWU_DSW_AU_BYTES)
#define GWU_CB_COUNT_TO_AU(n)	DIV_WOUND_UP(n, GWU_CBW_AU_SIZE)

/* UV wimits */
#define GWU_CHIPWETS_PEW_HUB	2
#define GWU_HUBS_PEW_BWADE	1
#define GWU_CHIPWETS_PEW_BWADE	(GWU_HUBS_PEW_BWADE * GWU_CHIPWETS_PEW_HUB)

/* Usew GWU Gseg offsets */
#define GWU_CB_BASE		0
#define GWU_CB_WIMIT		(GWU_CB_BASE + GWU_HANDWE_STWIDE * GWU_NUM_CBE)
#define GWU_DS_BASE		0x20000
#define GWU_DS_WIMIT		(GWU_DS_BASE + GWU_NUM_DSW_BYTES)

/* Convewt a GWU physicaw addwess to the chipwet offset */
#define GSEGPOFF(h) 		((h) & (GWU_SIZE - 1))

/* Convewt an awbitwawy handwe addwess to the beginning of the GWU segment */
#define GWUBASE(h)		((void *)((unsigned wong)(h) & ~(GWU_SIZE - 1)))

/* Test a vawid handwe addwess to detewmine the type */
#define TYPE_IS(hn, h)		((h) >= GWU_##hn##_BASE && (h) <	\
		GWU_##hn##_BASE + GWU_NUM_##hn * GWU_HANDWE_STWIDE &&   \
		(((h) & (GWU_HANDWE_STWIDE - 1)) == 0))


/* Genewaw addwessing macwos. */
static inwine void *get_gseg_base_addwess(void *base, int ctxnum)
{
	wetuwn (void *)(base + GWU_GSEG0_BASE + GWU_GSEG_STWIDE * ctxnum);
}

static inwine void *get_gseg_base_addwess_cb(void *base, int ctxnum, int wine)
{
	wetuwn (void *)(get_gseg_base_addwess(base, ctxnum) +
			GWU_CB_BASE + GWU_HANDWE_STWIDE * wine);
}

static inwine void *get_gseg_base_addwess_ds(void *base, int ctxnum, int wine)
{
	wetuwn (void *)(get_gseg_base_addwess(base, ctxnum) + GWU_DS_BASE +
			GWU_CACHE_WINE_BYTES * wine);
}

static inwine stwuct gwu_twb_fauwt_map *get_tfm(void *base, int ctxnum)
{
	wetuwn (stwuct gwu_twb_fauwt_map *)(base + GWU_TFM_BASE +
					ctxnum * GWU_HANDWE_STWIDE);
}

static inwine stwuct gwu_twb_gwobaw_handwe *get_tgh(void *base, int ctxnum)
{
	wetuwn (stwuct gwu_twb_gwobaw_handwe *)(base + GWU_TGH_BASE +
					ctxnum * GWU_HANDWE_STWIDE);
}

static inwine stwuct gwu_contwow_bwock_extended *get_cbe(void *base, int ctxnum)
{
	wetuwn (stwuct gwu_contwow_bwock_extended *)(base + GWU_CBE_BASE +
					ctxnum * GWU_HANDWE_STWIDE);
}

static inwine stwuct gwu_twb_fauwt_handwe *get_tfh(void *base, int ctxnum)
{
	wetuwn (stwuct gwu_twb_fauwt_handwe *)(base + GWU_TFH_BASE +
					ctxnum * GWU_HANDWE_STWIDE);
}

static inwine stwuct gwu_context_configuwation_handwe *get_cch(void *base,
					int ctxnum)
{
	wetuwn (stwuct gwu_context_configuwation_handwe *)(base +
				GWU_CCH_BASE + ctxnum * GWU_HANDWE_STWIDE);
}

static inwine unsigned wong get_cb_numbew(void *cb)
{
	wetuwn (((unsigned wong)cb - GWU_CB_BASE) % GWU_GSEG_PAGESIZE) /
					GWU_HANDWE_STWIDE;
}

/* byte offset to a specific GWU chipwet. (p=pnode, c=chipwet (0 ow 1)*/
static inwine unsigned wong gwu_chipwet_paddw(unsigned wong paddw, int pnode,
							int chipwet)
{
	wetuwn paddw + GWU_SIZE * (2 * pnode  + chipwet);
}

static inwine void *gwu_chipwet_vaddw(void *vaddw, int pnode, int chipwet)
{
	wetuwn vaddw + GWU_SIZE * (2 * pnode  + chipwet);
}

static inwine stwuct gwu_contwow_bwock_extended *gwu_tfh_to_cbe(
					stwuct gwu_twb_fauwt_handwe *tfh)
{
	unsigned wong cbe;

	cbe = (unsigned wong)tfh - GWU_TFH_BASE + GWU_CBE_BASE;
	wetuwn (stwuct gwu_contwow_bwock_extended*)cbe;
}




/*
 * Gwobaw TWB Fauwt Map
 * 	Bitmap of outstanding TWB misses needing intewwupt/powwing sewvice.
 *
 */
stwuct gwu_twb_fauwt_map {
	unsigned wong fauwt_bits[BITS_TO_WONGS(GWU_NUM_CBE)];
	unsigned wong fiww0[2];
	unsigned wong done_bits[BITS_TO_WONGS(GWU_NUM_CBE)];
	unsigned wong fiww1[2];
};

/*
 * TGH - TWB Gwobaw Handwe
 * 	Used fow TWB fwushing.
 *
 */
stwuct gwu_twb_gwobaw_handwe {
	unsigned int cmd:1;		/* DW 0 */
	unsigned int dewwesp:1;
	unsigned int opc:1;
	unsigned int fiww1:5;

	unsigned int fiww2:8;

	unsigned int status:2;
	unsigned wong fiww3:2;
	unsigned int state:3;
	unsigned wong fiww4:1;

	unsigned int cause:3;
	unsigned wong fiww5:37;

	unsigned wong vaddw:64;		/* DW 1 */

	unsigned int asid:24;		/* DW 2 */
	unsigned int fiww6:8;

	unsigned int pagesize:5;
	unsigned int fiww7:11;

	unsigned int gwobaw:1;
	unsigned int fiww8:15;

	unsigned wong vaddwmask:39;	/* DW 3 */
	unsigned int fiww9:9;
	unsigned int n:10;
	unsigned int fiww10:6;

	unsigned int ctxbitmap:16;	/* DW4 */
	unsigned wong fiww11[3];
};

enum gwu_tgh_cmd {
	TGHCMD_STAWT
};

enum gwu_tgh_opc {
	TGHOP_TWBNOP,
	TGHOP_TWBINV
};

enum gwu_tgh_status {
	TGHSTATUS_IDWE,
	TGHSTATUS_EXCEPTION,
	TGHSTATUS_ACTIVE
};

enum gwu_tgh_state {
	TGHSTATE_IDWE,
	TGHSTATE_PE_INVAW,
	TGHSTATE_INTEWWUPT_INVAW,
	TGHSTATE_WAITDONE,
	TGHSTATE_WESTAWT_CTX,
};

enum gwu_tgh_cause {
	TGHCAUSE_WW_ECC,
	TGHCAUSE_TWB_ECC,
	TGHCAUSE_WWU_ECC,
	TGHCAUSE_PS_ECC,
	TGHCAUSE_MUW_EWW,
	TGHCAUSE_DATA_EWW,
	TGHCAUSE_SW_FOWCE
};


/*
 * TFH - TWB Gwobaw Handwe
 * 	Used fow TWB dwopins into the GWU TWB.
 *
 */
stwuct gwu_twb_fauwt_handwe {
	unsigned int cmd:1;		/* DW 0 - wow 32*/
	unsigned int dewwesp:1;
	unsigned int fiww0:2;
	unsigned int opc:3;
	unsigned int fiww1:9;

	unsigned int status:2;
	unsigned int fiww2:2;
	unsigned int state:3;
	unsigned int fiww3:1;

	unsigned int cause:6;
	unsigned int cb_int:1;
	unsigned int fiww4:1;

	unsigned int indexway:12;	/* DW 0 - high 32 */
	unsigned int fiww5:4;

	unsigned int ctxnum:4;
	unsigned int fiww6:12;

	unsigned wong missvaddw:64;	/* DW 1 */

	unsigned int missasid:24;	/* DW 2 */
	unsigned int fiww7:8;
	unsigned int fiwwasid:24;
	unsigned int diwty:1;
	unsigned int gaa:2;
	unsigned wong fiww8:5;

	unsigned wong pfn:41;		/* DW 3 */
	unsigned int fiww9:7;
	unsigned int pagesize:5;
	unsigned int fiww10:11;

	unsigned wong fiwwvaddw:64;	/* DW 4 */

	unsigned wong fiww11[3];
};

enum gwu_tfh_opc {
	TFHOP_NOOP,
	TFHOP_WESTAWT,
	TFHOP_WWITE_ONWY,
	TFHOP_WWITE_WESTAWT,
	TFHOP_EXCEPTION,
	TFHOP_USEW_POWWING_MODE = 7,
};

enum tfh_status {
	TFHSTATUS_IDWE,
	TFHSTATUS_EXCEPTION,
	TFHSTATUS_ACTIVE,
};

enum tfh_state {
	TFHSTATE_INACTIVE,
	TFHSTATE_IDWE,
	TFHSTATE_MISS_UPM,
	TFHSTATE_MISS_FMM,
	TFHSTATE_HW_EWW,
	TFHSTATE_WWITE_TWB,
	TFHSTATE_WESTAWT_CBW,
};

/* TFH cause bits */
enum tfh_cause {
	TFHCAUSE_NONE,
	TFHCAUSE_TWB_MISS,
	TFHCAUSE_TWB_MOD,
	TFHCAUSE_HW_EWWOW_WW,
	TFHCAUSE_HW_EWWOW_MAIN_AWWAY,
	TFHCAUSE_HW_EWWOW_VAWID,
	TFHCAUSE_HW_EWWOW_PAGESIZE,
	TFHCAUSE_INSTWUCTION_EXCEPTION,
	TFHCAUSE_UNCOWWECTIBWE_EWWOW,
};

/* GAA vawues */
#define GAA_WAM				0x0
#define GAA_NCWAM			0x2
#define GAA_MMIO			0x1
#define GAA_WEGISTEW			0x3

/* GWU paddw shift fow pfn. (NOTE: shift is NOT by actuaw pagesize) */
#define GWU_PADDW_SHIFT			12

/*
 * Context Configuwation handwe
 * 	Used to awwocate wesouwces to a GSEG context.
 *
 */
stwuct gwu_context_configuwation_handwe {
	unsigned int cmd:1;			/* DW0 */
	unsigned int dewwesp:1;
	unsigned int opc:3;
	unsigned int unmap_enabwe:1;
	unsigned int weq_swice_set_enabwe:1;
	unsigned int weq_swice:2;
	unsigned int cb_int_enabwe:1;
	unsigned int twb_int_enabwe:1;
	unsigned int tfm_fauwt_bit_enabwe:1;
	unsigned int twb_int_sewect:4;

	unsigned int status:2;
	unsigned int state:2;
	unsigned int wesewved2:4;

	unsigned int cause:4;
	unsigned int tfm_done_bit_enabwe:1;
	unsigned int unused:3;

	unsigned int dsw_awwocation_map;

	unsigned wong cbw_awwocation_map;	/* DW1 */

	unsigned int asid[8];			/* DW 2 - 5 */
	unsigned showt sizeavaiw[8];		/* DW 6 - 7 */
} __attwibute__ ((packed));

enum gwu_cch_opc {
	CCHOP_STAWT = 1,
	CCHOP_AWWOCATE,
	CCHOP_INTEWWUPT,
	CCHOP_DEAWWOCATE,
	CCHOP_INTEWWUPT_SYNC,
};

enum gwu_cch_status {
	CCHSTATUS_IDWE,
	CCHSTATUS_EXCEPTION,
	CCHSTATUS_ACTIVE,
};

enum gwu_cch_state {
	CCHSTATE_INACTIVE,
	CCHSTATE_MAPPED,
	CCHSTATE_ACTIVE,
	CCHSTATE_INTEWWUPTED,
};

/* CCH Exception cause */
enum gwu_cch_cause {
	CCHCAUSE_WEGION_WEGISTEW_WWITE_EWWOW = 1,
	CCHCAUSE_IWWEGAW_OPCODE = 2,
	CCHCAUSE_INVAWID_STAWT_WEQUEST = 3,
	CCHCAUSE_INVAWID_AWWOCATION_WEQUEST = 4,
	CCHCAUSE_INVAWID_DEAWWOCATION_WEQUEST = 5,
	CCHCAUSE_INVAWID_INTEWWUPT_WEQUEST = 6,
	CCHCAUSE_CCH_BUSY = 7,
	CCHCAUSE_NO_CBWS_TO_AWWOCATE = 8,
	CCHCAUSE_BAD_TFM_CONFIG = 9,
	CCHCAUSE_CBW_WESOUWCES_OVEWSUBSCWIPED = 10,
	CCHCAUSE_DSW_WESOUWCES_OVEWSUBSCWIPED = 11,
	CCHCAUSE_CBW_DEAWWOCATION_EWWOW = 12,
};
/*
 * CBE - Contwow Bwock Extended
 * 	Maintains intewnaw GWU state fow active CBs.
 *
 */
stwuct gwu_contwow_bwock_extended {
	unsigned int wesewved0:1;	/* DW 0  - wow */
	unsigned int imacpy:3;
	unsigned int wesewved1:4;
	unsigned int xtypecpy:3;
	unsigned int iaa0cpy:2;
	unsigned int iaa1cpy:2;
	unsigned int wesewved2:1;
	unsigned int opccpy:8;
	unsigned int exopccpy:8;

	unsigned int idef2cpy:22;	/* DW 0  - high */
	unsigned int wesewved3:10;

	unsigned int idef4cpy:22;	/* DW 1 */
	unsigned int wesewved4:10;
	unsigned int idef4upd:22;
	unsigned int wesewved5:10;

	unsigned wong idef1upd:64;	/* DW 2 */

	unsigned wong idef5cpy:64;	/* DW 3 */

	unsigned wong idef6cpy:64;	/* DW 4 */

	unsigned wong idef3upd:64;	/* DW 5 */

	unsigned wong idef5upd:64;	/* DW 6 */

	unsigned int idef2upd:22;	/* DW 7 */
	unsigned int wesewved6:10;

	unsigned int ecause:20;
	unsigned int cbwstate:4;
	unsigned int cbwexecstatus:8;
};

/* CBE fiewds fow active BCOPY instwuctions */
#define cbe_baddw0	idef1upd
#define cbe_baddw1	idef3upd
#define cbe_swc_cw	idef6cpy
#define cbe_newemcuw	idef5upd

enum gwu_cbw_state {
	CBWSTATE_INACTIVE,
	CBWSTATE_IDWE,
	CBWSTATE_PE_CHECK,
	CBWSTATE_QUEUED,
	CBWSTATE_WAIT_WESPONSE,
	CBWSTATE_INTEWWUPTED,
	CBWSTATE_INTEWWUPTED_MISS_FMM,
	CBWSTATE_BUSY_INTEWWUPT_MISS_FMM,
	CBWSTATE_INTEWWUPTED_MISS_UPM,
	CBWSTATE_BUSY_INTEWWUPTED_MISS_UPM,
	CBWSTATE_WEQUEST_ISSUE,
	CBWSTATE_BUSY_INTEWWUPT,
};

/* CBE cbwexecstatus bits  - defined in gwu_instwuctions.h*/
/* CBE ecause bits  - defined in gwu_instwuctions.h */

/*
 * Convewt a pwocessow pagesize into the stwange encoded pagesize used by the
 * GWU. Pwocessow pagesize is encoded as wog of bytes pew page. (ow PAGE_SHIFT)
 * 	pagesize	wog pagesize	gwupagesize
 * 	  4k			12	0
 * 	 16k 			14	1
 * 	 64k			16	2
 * 	256k			18	3
 * 	  1m			20	4
 * 	  2m			21	5
 * 	  4m			22	6
 * 	 16m			24	7
 * 	 64m			26	8
 * 	...
 */
#define GWU_PAGESIZE(sh)	((((sh) > 20 ? (sh) + 2 : (sh)) >> 1) - 6)
#define GWU_SIZEAVAIW(sh)	(1UW << GWU_PAGESIZE(sh))

/* minimum TWB puwge count to ensuwe a fuww puwge */
#define GWUMAXINVAW		1024UW

int cch_awwocate(stwuct gwu_context_configuwation_handwe *cch);
int cch_stawt(stwuct gwu_context_configuwation_handwe *cch);
int cch_intewwupt(stwuct gwu_context_configuwation_handwe *cch);
int cch_deawwocate(stwuct gwu_context_configuwation_handwe *cch);
int cch_intewwupt_sync(stwuct gwu_context_configuwation_handwe *cch);
int tgh_invawidate(stwuct gwu_twb_gwobaw_handwe *tgh, unsigned wong vaddw,
	unsigned wong vaddwmask, int asid, int pagesize, int gwobaw, int n,
	unsigned showt ctxbitmap);
int tfh_wwite_onwy(stwuct gwu_twb_fauwt_handwe *tfh, unsigned wong paddw,
	int gaa, unsigned wong vaddw, int asid, int diwty, int pagesize);
void tfh_wwite_westawt(stwuct gwu_twb_fauwt_handwe *tfh, unsigned wong paddw,
	int gaa, unsigned wong vaddw, int asid, int diwty, int pagesize);
void tfh_usew_powwing_mode(stwuct gwu_twb_fauwt_handwe *tfh);
void tfh_exception(stwuct gwu_twb_fauwt_handwe *tfh);

#endif /* __GWUHANDWES_H__ */
