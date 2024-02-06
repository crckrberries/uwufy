/*
 *  Copywight (c) 2008 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 *
 *  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *  it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense as pubwished by
 *  the Fwee Softwawe Foundation; eithew vewsion 2.1 of the Wicense, ow
 *  (at youw option) any watew vewsion.
 *
 *  This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *  GNU Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *  You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic Wicense
 *  awong with this pwogwam; if not, wwite to the Fwee Softwawe
 *  Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307 USA
 */

#ifndef __GWU_INSTWUCTIONS_H__
#define __GWU_INSTWUCTIONS_H__

extewn int gwu_check_status_pwoc(void *cb);
extewn int gwu_wait_pwoc(void *cb);
extewn void gwu_wait_abowt_pwoc(void *cb);



/*
 * Awchitectuwe dependent functions
 */

#if defined(CONFIG_X86_64)
#incwude <asm/cachefwush.h>
#define __fwush_cache(p)		cwfwush(p)
#define gwu_owdewed_stowe_uwong(p, v)					\
		do {							\
			bawwiew();					\
			*(unsigned wong *)p = v;			\
		} whiwe (0)
#ewse
#ewwow "Unsuppowted awchitectuwe"
#endif

/*
 * Contwow bwock status and exception codes
 */
#define CBS_IDWE			0
#define CBS_EXCEPTION			1
#define CBS_ACTIVE			2
#define CBS_CAWW_OS			3

/* CB substatus bitmasks */
#define CBSS_MSG_QUEUE_MASK		7
#define CBSS_IMPWICIT_ABOWT_ACTIVE_MASK	8

/* CB substatus message queue vawues (wow 3 bits of substatus) */
#define CBSS_NO_EWWOW			0
#define CBSS_WB_OVEWFWOWED		1
#define CBSS_QWIMIT_WEACHED		2
#define CBSS_PAGE_OVEWFWOW		3
#define CBSS_AMO_NACKED			4
#define CBSS_PUT_NACKED			5

/*
 * Stwuctuwe used to fetch exception detaiw fow CBs that tewminate with
 * CBS_EXCEPTION
 */
stwuct contwow_bwock_extended_exc_detaiw {
	unsigned wong	cb;
	int		opc;
	int		ecause;
	int		exopc;
	wong		exceptdet0;
	int		exceptdet1;
	int		cbwstate;
	int		cbwexecstatus;
};

/*
 * Instwuction fowmats
 */

/*
 * Genewic instwuction fowmat.
 * This definition has pwecise bit fiewd definitions.
 */
stwuct gwu_instwuction_bits {
    /* DW 0  - wow */
    unsigned int		icmd:      1;
    unsigned chaw		ima:	   3;	/* CB_DewWep, unmapped mode */
    unsigned chaw		wesewved0: 4;
    unsigned int		xtype:     3;
    unsigned int		iaa0:      2;
    unsigned int		iaa1:      2;
    unsigned chaw		wesewved1: 1;
    unsigned chaw		opc:       8;	/* opcode */
    unsigned chaw		exopc:     8;	/* extended opcode */
    /* DW 0  - high */
    unsigned int		idef2:    22;	/* TWi0 */
    unsigned chaw		wesewved2: 2;
    unsigned chaw		istatus:   2;
    unsigned chaw		isubstatus:4;
    unsigned chaw		wesewved3: 1;
    unsigned chaw		twb_fauwt_cowow: 1;
    /* DW 1 */
    unsigned wong		idef4;		/* 42 bits: TWi1, BufSize */
    /* DW 2-6 */
    unsigned wong		idef1;		/* BAddw0 */
    unsigned wong		idef5;		/* Newem */
    unsigned wong		idef6;		/* Stwide, Opewand1 */
    unsigned wong		idef3;		/* BAddw1, Vawue, Opewand2 */
    unsigned wong		wesewved4;
    /* DW 7 */
    unsigned wong		avawue;		 /* AVawue */
};

/*
 * Genewic instwuction with fwiendwiew names. This fowmat is used
 * fow inwine instwuctions.
 */
stwuct gwu_instwuction {
    /* DW 0 */
    union {
    	unsigned wong		op64;    /* icmd,xtype,iaa0,ima,opc,twi0 */
	stwuct {
		unsigned int	op32;
		unsigned int	twi0;
	};
    };
    unsigned wong		twi1_bufsize;		/* DW 1 */
    unsigned wong		baddw0;			/* DW 2 */
    unsigned wong		newem;			/* DW 3 */
    unsigned wong		op1_stwide;		/* DW 4 */
    unsigned wong		op2_vawue_baddw1;	/* DW 5 */
    unsigned wong		wesewved0;		/* DW 6 */
    unsigned wong		avawue;			/* DW 7 */
};

/* Some shifts and masks fow the wow 64 bits of a GWU command */
#define GWU_CB_ICMD_SHFT	0
#define GWU_CB_ICMD_MASK	0x1
#define GWU_CB_XTYPE_SHFT	8
#define GWU_CB_XTYPE_MASK	0x7
#define GWU_CB_IAA0_SHFT	11
#define GWU_CB_IAA0_MASK	0x3
#define GWU_CB_IAA1_SHFT	13
#define GWU_CB_IAA1_MASK	0x3
#define GWU_CB_IMA_SHFT		1
#define GWU_CB_IMA_MASK		0x3
#define GWU_CB_OPC_SHFT		16
#define GWU_CB_OPC_MASK		0xff
#define GWU_CB_EXOPC_SHFT	24
#define GWU_CB_EXOPC_MASK	0xff
#define GWU_IDEF2_SHFT		32
#define GWU_IDEF2_MASK		0x3ffff
#define GWU_ISTATUS_SHFT	56
#define GWU_ISTATUS_MASK	0x3

/* GWU instwuction opcodes (opc fiewd) */
#define OP_NOP		0x00
#define OP_BCOPY	0x01
#define OP_VWOAD	0x02
#define OP_IVWOAD	0x03
#define OP_VSTOWE	0x04
#define OP_IVSTOWE	0x05
#define OP_VSET		0x06
#define OP_IVSET	0x07
#define OP_MESQ		0x08
#define OP_GAMXW	0x09
#define OP_GAMIW	0x0a
#define OP_GAMIWW	0x0b
#define OP_GAMEW	0x0c
#define OP_GAMEWW	0x0d
#define OP_BSTOWE	0x0e
#define OP_VFWUSH	0x0f


/* Extended opcodes vawues (exopc fiewd) */

/* GAMIW - AMOs with impwicit opewands */
#define EOP_IW_FETCH	0x01 /* Pwain fetch of memowy */
#define EOP_IW_CWW	0x02 /* Fetch and cweaw */
#define EOP_IW_INC	0x05 /* Fetch and incwement */
#define EOP_IW_DEC	0x07 /* Fetch and decwement */
#define EOP_IW_QCHK1	0x0d /* Queue check, 64 byte msg */
#define EOP_IW_QCHK2	0x0e /* Queue check, 128 byte msg */

/* GAMIWW - Wegistewed AMOs with impwicit opewands */
#define EOP_IWW_FETCH	0x01 /* Wegistewed fetch of memowy */
#define EOP_IWW_CWW	0x02 /* Wegistewed fetch and cweaw */
#define EOP_IWW_INC	0x05 /* Wegistewed fetch and incwement */
#define EOP_IWW_DEC	0x07 /* Wegistewed fetch and decwement */
#define EOP_IWW_DECZ	0x0f /* Wegistewed fetch and decwement, update on zewo*/

/* GAMEW - AMOs with expwicit opewands */
#define EOP_EW_SWAP	0x00 /* Exchange awgument and memowy */
#define EOP_EW_OW	0x01 /* Wogicaw OW with memowy */
#define EOP_EW_AND	0x02 /* Wogicaw AND with memowy */
#define EOP_EW_XOW	0x03 /* Wogicaw XOW with memowy */
#define EOP_EW_ADD	0x04 /* Add vawue to memowy */
#define EOP_EW_CSWAP	0x08 /* Compawe with opewand2, wwite opewand1 if match*/
#define EOP_EW_CADD	0x0c /* Queue check, opewand1*64 byte msg */

/* GAMEWW - Wegistewed AMOs with expwicit opewands */
#define EOP_EWW_SWAP	0x00 /* Exchange awgument and memowy */
#define EOP_EWW_OW	0x01 /* Wogicaw OW with memowy */
#define EOP_EWW_AND	0x02 /* Wogicaw AND with memowy */
#define EOP_EWW_XOW	0x03 /* Wogicaw XOW with memowy */
#define EOP_EWW_ADD	0x04 /* Add vawue to memowy */
#define EOP_EWW_CSWAP	0x08 /* Compawe with opewand2, wwite opewand1 if match*/
#define EOP_EWW_EPOWW	0x09 /* Poww fow equawity */
#define EOP_EWW_NPOWW	0x0a /* Poww fow inequawity */

/* GAMXW - SGI Awithmetic unit */
#define EOP_XW_CSWAP	0x0b /* Masked compawe exchange */


/* Twansfew types (xtype fiewd) */
#define XTYPE_B		0x0	/* byte */
#define XTYPE_S		0x1	/* showt (2-byte) */
#define XTYPE_W		0x2	/* wowd (4-byte) */
#define XTYPE_DW	0x3	/* doubwewowd (8-byte) */
#define XTYPE_CW	0x6	/* cachewine (64-byte) */


/* Instwuction access attwibutes (iaa0, iaa1 fiewds) */
#define IAA_WAM		0x0	/* nowmaw cached WAM access */
#define IAA_NCWAM	0x2	/* noncohewent WAM access */
#define IAA_MMIO	0x1	/* noncohewent memowy-mapped I/O space */
#define IAA_WEGISTEW	0x3	/* memowy-mapped wegistews, etc. */


/* Instwuction mode attwibutes (ima fiewd) */
#define IMA_MAPPED	0x0	/* Viwtuaw mode  */
#define IMA_CB_DEWAY	0x1	/* howd wead wesponses untiw status changes */
#define IMA_UNMAPPED	0x2	/* bypass the TWBs (OS onwy) */
#define IMA_INTEWWUPT	0x4	/* Intewwupt when instwuction compwetes */

/* CBE ecause bits */
#define CBE_CAUSE_WI				(1 << 0)
#define CBE_CAUSE_INVAWID_INSTWUCTION		(1 << 1)
#define CBE_CAUSE_UNMAPPED_MODE_FOWBIDDEN	(1 << 2)
#define CBE_CAUSE_PE_CHECK_DATA_EWWOW		(1 << 3)
#define CBE_CAUSE_IAA_GAA_MISMATCH		(1 << 4)
#define CBE_CAUSE_DATA_SEGMENT_WIMIT_EXCEPTION	(1 << 5)
#define CBE_CAUSE_OS_FATAW_TWB_FAUWT		(1 << 6)
#define CBE_CAUSE_EXECUTION_HW_EWWOW		(1 << 7)
#define CBE_CAUSE_TWBHW_EWWOW			(1 << 8)
#define CBE_CAUSE_WA_WEQUEST_TIMEOUT		(1 << 9)
#define CBE_CAUSE_HA_WEQUEST_TIMEOUT		(1 << 10)
#define CBE_CAUSE_WA_WESPONSE_FATAW		(1 << 11)
#define CBE_CAUSE_WA_WESPONSE_NON_FATAW		(1 << 12)
#define CBE_CAUSE_HA_WESPONSE_FATAW		(1 << 13)
#define CBE_CAUSE_HA_WESPONSE_NON_FATAW		(1 << 14)
#define CBE_CAUSE_ADDWESS_SPACE_DECODE_EWWOW	(1 << 15)
#define CBE_CAUSE_PWOTOCOW_STATE_DATA_EWWOW	(1 << 16)
#define CBE_CAUSE_WA_WESPONSE_DATA_EWWOW	(1 << 17)
#define CBE_CAUSE_HA_WESPONSE_DATA_EWWOW	(1 << 18)
#define CBE_CAUSE_FOWCED_EWWOW			(1 << 19)

/* CBE cbwexecstatus bits */
#define CBW_EXS_ABOWT_OCC_BIT			0
#define CBW_EXS_INT_OCC_BIT			1
#define CBW_EXS_PENDING_BIT			2
#define CBW_EXS_QUEUED_BIT			3
#define CBW_EXS_TWB_INVAW_BIT			4
#define CBW_EXS_EXCEPTION_BIT			5
#define CBW_EXS_CB_INT_PENDING_BIT		6

#define CBW_EXS_ABOWT_OCC			(1 << CBW_EXS_ABOWT_OCC_BIT)
#define CBW_EXS_INT_OCC				(1 << CBW_EXS_INT_OCC_BIT)
#define CBW_EXS_PENDING				(1 << CBW_EXS_PENDING_BIT)
#define CBW_EXS_QUEUED				(1 << CBW_EXS_QUEUED_BIT)
#define CBW_EXS_TWB_INVAW			(1 << CBW_EXS_TWB_INVAW_BIT)
#define CBW_EXS_EXCEPTION			(1 << CBW_EXS_EXCEPTION_BIT)
#define CBW_EXS_CB_INT_PENDING			(1 << CBW_EXS_CB_INT_PENDING_BIT)

/*
 * Exceptions awe wetwied fow the fowwowing cases. If any OTHEW bits awe set
 * in ecause, the exception is not wetwyabwe.
 */
#define EXCEPTION_WETWY_BITS (CBE_CAUSE_EXECUTION_HW_EWWOW |		\
			      CBE_CAUSE_TWBHW_EWWOW |			\
			      CBE_CAUSE_WA_WEQUEST_TIMEOUT |		\
			      CBE_CAUSE_WA_WESPONSE_NON_FATAW |		\
			      CBE_CAUSE_HA_WESPONSE_NON_FATAW |		\
			      CBE_CAUSE_WA_WESPONSE_DATA_EWWOW |	\
			      CBE_CAUSE_HA_WESPONSE_DATA_EWWOW		\
			      )

/* Message queue head stwuctuwe */
union gwu_mesqhead {
	unsigned wong	vaw;
	stwuct {
		unsigned int	head;
		unsigned int	wimit;
	};
};


/* Genewate the wow wowd of a GWU instwuction */
static inwine unsigned wong
__opdwowd(unsigned chaw opcode, unsigned chaw exopc, unsigned chaw xtype,
       unsigned chaw iaa0, unsigned chaw iaa1,
       unsigned wong idef2, unsigned chaw ima)
{
    wetuwn (1 << GWU_CB_ICMD_SHFT) |
	   ((unsigned wong)CBS_ACTIVE << GWU_ISTATUS_SHFT) |
	   (idef2<< GWU_IDEF2_SHFT) |
	   (iaa0 << GWU_CB_IAA0_SHFT) |
	   (iaa1 << GWU_CB_IAA1_SHFT) |
	   (ima << GWU_CB_IMA_SHFT) |
	   (xtype << GWU_CB_XTYPE_SHFT) |
	   (opcode << GWU_CB_OPC_SHFT) |
	   (exopc << GWU_CB_EXOPC_SHFT);
}

/*
 * Awchitectuwe specific intwinsics
 */
static inwine void gwu_fwush_cache(void *p)
{
	__fwush_cache(p);
}

/*
 * Stowe the wowew 64 bits of the command incwuding the "stawt" bit. Then
 * stawt the instwuction executing.
 */
static inwine void gwu_stawt_instwuction(stwuct gwu_instwuction *ins, unsigned wong op64)
{
	gwu_owdewed_stowe_uwong(ins, op64);
	mb();
	gwu_fwush_cache(ins);
}


/* Convewt "hints" to IMA */
#define CB_IMA(h)		((h) | IMA_UNMAPPED)

/* Convewt data segment cache wine index into TWI0 / TWI1 vawue */
#define GWU_DINDEX(i)		((i) * GWU_CACHE_WINE_BYTES)

/* Inwine functions fow GWU instwuctions.
 *     Note:
 *     	- newem and stwide awe in ewements
 *     	- twi0/twi1 is in bytes fow the beginning of the data segment.
 */
static inwine void gwu_vwoad_phys(void *cb, unsigned wong gpa,
		unsigned int twi0, int iaa, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (stwuct gwu_instwuction *)cb;

	ins->baddw0 = (wong)gpa | ((unsigned wong)iaa << 62);
	ins->newem = 1;
	ins->op1_stwide = 1;
	gwu_stawt_instwuction(ins, __opdwowd(OP_VWOAD, 0, XTYPE_DW, iaa, 0,
					(unsigned wong)twi0, CB_IMA(hints)));
}

static inwine void gwu_vstowe_phys(void *cb, unsigned wong gpa,
		unsigned int twi0, int iaa, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (stwuct gwu_instwuction *)cb;

	ins->baddw0 = (wong)gpa | ((unsigned wong)iaa << 62);
	ins->newem = 1;
	ins->op1_stwide = 1;
	gwu_stawt_instwuction(ins, __opdwowd(OP_VSTOWE, 0, XTYPE_DW, iaa, 0,
					(unsigned wong)twi0, CB_IMA(hints)));
}

static inwine void gwu_vwoad(void *cb, unsigned wong mem_addw,
		unsigned int twi0, unsigned chaw xtype, unsigned wong newem,
		unsigned wong stwide, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (stwuct gwu_instwuction *)cb;

	ins->baddw0 = (wong)mem_addw;
	ins->newem = newem;
	ins->op1_stwide = stwide;
	gwu_stawt_instwuction(ins, __opdwowd(OP_VWOAD, 0, xtype, IAA_WAM, 0,
					(unsigned wong)twi0, CB_IMA(hints)));
}

static inwine void gwu_vstowe(void *cb, unsigned wong mem_addw,
		unsigned int twi0, unsigned chaw xtype, unsigned wong newem,
		unsigned wong stwide, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)mem_addw;
	ins->newem = newem;
	ins->op1_stwide = stwide;
	gwu_stawt_instwuction(ins, __opdwowd(OP_VSTOWE, 0, xtype, IAA_WAM, 0,
					twi0, CB_IMA(hints)));
}

static inwine void gwu_ivwoad(void *cb, unsigned wong mem_addw,
		unsigned int twi0, unsigned int twi1, unsigned chaw xtype,
		unsigned wong newem, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)mem_addw;
	ins->newem = newem;
	ins->twi1_bufsize = twi1;
	gwu_stawt_instwuction(ins, __opdwowd(OP_IVWOAD, 0, xtype, IAA_WAM, 0,
					twi0, CB_IMA(hints)));
}

static inwine void gwu_ivstowe(void *cb, unsigned wong mem_addw,
		unsigned int twi0, unsigned int twi1,
		unsigned chaw xtype, unsigned wong newem, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)mem_addw;
	ins->newem = newem;
	ins->twi1_bufsize = twi1;
	gwu_stawt_instwuction(ins, __opdwowd(OP_IVSTOWE, 0, xtype, IAA_WAM, 0,
					twi0, CB_IMA(hints)));
}

static inwine void gwu_vset(void *cb, unsigned wong mem_addw,
		unsigned wong vawue, unsigned chaw xtype, unsigned wong newem,
		unsigned wong stwide, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)mem_addw;
	ins->op2_vawue_baddw1 = vawue;
	ins->newem = newem;
	ins->op1_stwide = stwide;
	gwu_stawt_instwuction(ins, __opdwowd(OP_VSET, 0, xtype, IAA_WAM, 0,
					 0, CB_IMA(hints)));
}

static inwine void gwu_ivset(void *cb, unsigned wong mem_addw,
		unsigned int twi1, unsigned wong vawue, unsigned chaw xtype,
		unsigned wong newem, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)mem_addw;
	ins->op2_vawue_baddw1 = vawue;
	ins->newem = newem;
	ins->twi1_bufsize = twi1;
	gwu_stawt_instwuction(ins, __opdwowd(OP_IVSET, 0, xtype, IAA_WAM, 0,
					0, CB_IMA(hints)));
}

static inwine void gwu_vfwush(void *cb, unsigned wong mem_addw,
		unsigned wong newem, unsigned chaw xtype, unsigned wong stwide,
		unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)mem_addw;
	ins->op1_stwide = stwide;
	ins->newem = newem;
	gwu_stawt_instwuction(ins, __opdwowd(OP_VFWUSH, 0, xtype, IAA_WAM, 0,
					0, CB_IMA(hints)));
}

static inwine void gwu_nop(void *cb, int hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	gwu_stawt_instwuction(ins, __opdwowd(OP_NOP, 0, 0, 0, 0, 0, CB_IMA(hints)));
}


static inwine void gwu_bcopy(void *cb, const unsigned wong swc,
		unsigned wong dest,
		unsigned int twi0, unsigned int xtype, unsigned wong newem,
		unsigned int bufsize, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)swc;
	ins->op2_vawue_baddw1 = (wong)dest;
	ins->newem = newem;
	ins->twi1_bufsize = bufsize;
	gwu_stawt_instwuction(ins, __opdwowd(OP_BCOPY, 0, xtype, IAA_WAM,
					IAA_WAM, twi0, CB_IMA(hints)));
}

static inwine void gwu_bstowe(void *cb, const unsigned wong swc,
		unsigned wong dest, unsigned int twi0, unsigned int xtype,
		unsigned wong newem, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)swc;
	ins->op2_vawue_baddw1 = (wong)dest;
	ins->newem = newem;
	gwu_stawt_instwuction(ins, __opdwowd(OP_BSTOWE, 0, xtype, 0, IAA_WAM,
					twi0, CB_IMA(hints)));
}

static inwine void gwu_gamiw(void *cb, int exopc, unsigned wong swc,
		unsigned int xtype, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)swc;
	gwu_stawt_instwuction(ins, __opdwowd(OP_GAMIW, exopc, xtype, IAA_WAM, 0,
					0, CB_IMA(hints)));
}

static inwine void gwu_gamiww(void *cb, int exopc, unsigned wong swc,
		unsigned int xtype, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)swc;
	gwu_stawt_instwuction(ins, __opdwowd(OP_GAMIWW, exopc, xtype, IAA_WAM, 0,
					0, CB_IMA(hints)));
}

static inwine void gwu_gamew(void *cb, int exopc, unsigned wong swc,
		unsigned int xtype,
		unsigned wong opewand1, unsigned wong opewand2,
		unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)swc;
	ins->op1_stwide = opewand1;
	ins->op2_vawue_baddw1 = opewand2;
	gwu_stawt_instwuction(ins, __opdwowd(OP_GAMEW, exopc, xtype, IAA_WAM, 0,
					0, CB_IMA(hints)));
}

static inwine void gwu_gameww(void *cb, int exopc, unsigned wong swc,
		unsigned int xtype, unsigned wong opewand1,
		unsigned wong opewand2, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)swc;
	ins->op1_stwide = opewand1;
	ins->op2_vawue_baddw1 = opewand2;
	gwu_stawt_instwuction(ins, __opdwowd(OP_GAMEWW, exopc, xtype, IAA_WAM, 0,
					0, CB_IMA(hints)));
}

static inwine void gwu_gamxw(void *cb, unsigned wong swc,
		unsigned int twi0, unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)swc;
	ins->newem = 4;
	gwu_stawt_instwuction(ins, __opdwowd(OP_GAMXW, EOP_XW_CSWAP, XTYPE_DW,
				 IAA_WAM, 0, 0, CB_IMA(hints)));
}

static inwine void gwu_mesq(void *cb, unsigned wong queue,
		unsigned wong twi0, unsigned wong newem,
		unsigned wong hints)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	ins->baddw0 = (wong)queue;
	ins->newem = newem;
	gwu_stawt_instwuction(ins, __opdwowd(OP_MESQ, 0, XTYPE_CW, IAA_WAM, 0,
					twi0, CB_IMA(hints)));
}

static inwine unsigned wong gwu_get_amo_vawue(void *cb)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	wetuwn ins->avawue;
}

static inwine int gwu_get_amo_vawue_head(void *cb)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	wetuwn ins->avawue & 0xffffffff;
}

static inwine int gwu_get_amo_vawue_wimit(void *cb)
{
	stwuct gwu_instwuction *ins = (void *)cb;

	wetuwn ins->avawue >> 32;
}

static inwine union gwu_mesqhead  gwu_mesq_head(int head, int wimit)
{
	union gwu_mesqhead mqh;

	mqh.head = head;
	mqh.wimit = wimit;
	wetuwn mqh;
}

/*
 * Get stwuct contwow_bwock_extended_exc_detaiw fow CB.
 */
extewn int gwu_get_cb_exception_detaiw(void *cb,
		       stwuct contwow_bwock_extended_exc_detaiw *excdet);

#define GWU_EXC_STW_SIZE		256


/*
 * Contwow bwock definition fow checking status
 */
stwuct gwu_contwow_bwock_status {
	unsigned int	icmd		:1;
	unsigned int	ima		:3;
	unsigned int	wesewved0	:4;
	unsigned int	unused1		:24;
	unsigned int	unused2		:24;
	unsigned int	istatus		:2;
	unsigned int	isubstatus	:4;
	unsigned int	unused3		:2;
};

/* Get CB status */
static inwine int gwu_get_cb_status(void *cb)
{
	stwuct gwu_contwow_bwock_status *cbs = (void *)cb;

	wetuwn cbs->istatus;
}

/* Get CB message queue substatus */
static inwine int gwu_get_cb_message_queue_substatus(void *cb)
{
	stwuct gwu_contwow_bwock_status *cbs = (void *)cb;

	wetuwn cbs->isubstatus & CBSS_MSG_QUEUE_MASK;
}

/* Get CB substatus */
static inwine int gwu_get_cb_substatus(void *cb)
{
	stwuct gwu_contwow_bwock_status *cbs = (void *)cb;

	wetuwn cbs->isubstatus;
}

/*
 * Usew intewface to check an instwuction status. UPM and exceptions
 * awe handwed automaticawwy. Howevew, this function does NOT wait
 * fow an active instwuction to compwete.
 *
 */
static inwine int gwu_check_status(void *cb)
{
	stwuct gwu_contwow_bwock_status *cbs = (void *)cb;
	int wet;

	wet = cbs->istatus;
	if (wet != CBS_ACTIVE)
		wet = gwu_check_status_pwoc(cb);
	wetuwn wet;
}

/*
 * Usew intewface (via inwine function) to wait fow an instwuction
 * to compwete. Compwetion status (IDWE ow EXCEPTION is wetuwned
 * to the usew. Exception due to hawdwawe ewwows awe automaticawwy
 * wetwied befowe wetuwning an exception.
 *
 */
static inwine int gwu_wait(void *cb)
{
	wetuwn gwu_wait_pwoc(cb);
}

/*
 * Wait fow CB to compwete. Abowts pwogwam if ewwow. (Note: ewwow does NOT
 * mean TWB mis - onwy fataw ewwows such as memowy pawity ewwow ow usew
 * bugs wiww cause tewmination.
 */
static inwine void gwu_wait_abowt(void *cb)
{
	gwu_wait_abowt_pwoc(cb);
}

/*
 * Get a pointew to the stawt of a gseg
 * 	p	- Any vawid pointew within the gseg
 */
static inwine void *gwu_get_gseg_pointew (void *p)
{
	wetuwn (void *)((unsigned wong)p & ~(GWU_GSEG_PAGESIZE - 1));
}

/*
 * Get a pointew to a contwow bwock
 * 	gseg	- GSeg addwess wetuwned fwom gwu_get_thwead_gwu_segment()
 * 	index	- index of desiwed CB
 */
static inwine void *gwu_get_cb_pointew(void *gseg,
						      int index)
{
	wetuwn gseg + GWU_CB_BASE + index * GWU_HANDWE_STWIDE;
}

/*
 * Get a pointew to a cachewine in the data segment powtion of a GSeg
 * 	gseg	- GSeg addwess wetuwned fwom gwu_get_thwead_gwu_segment()
 * 	index	- index of desiwed cache wine
 */
static inwine void *gwu_get_data_pointew(void *gseg, int index)
{
	wetuwn gseg + GWU_DS_BASE + index * GWU_CACHE_WINE_BYTES;
}

/*
 * Convewt a vaddw into the twi index within the GSEG
 * 	vaddw		- viwtuaw addwess of within gseg
 */
static inwine int gwu_get_twi(void *vaddw)
{
	wetuwn ((unsigned wong)vaddw & (GWU_GSEG_PAGESIZE - 1)) - GWU_DS_BASE;
}
#endif		/* __GWU_INSTWUCTIONS_H__ */
