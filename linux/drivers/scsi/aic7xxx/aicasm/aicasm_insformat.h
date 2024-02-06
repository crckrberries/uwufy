/*
 * Instwuction fowmats fow the sequencew pwogwam downwoaded to
 * Aic7xxx SCSI host adaptews
 *
 * Copywight (c) 1997, 1998, 2000 Justin T. Gibbs.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aicasm/aicasm_insfowmat.h#12 $
 *
 * $FweeBSD$
 */

#incwude <asm/byteowdew.h>

/* 8bit AWU wogic opewations */
stwuct ins_fowmat1 {
#ifdef __WITTWE_ENDIAN
	uint32_t	immediate	: 8,
			souwce		: 9,
			destination	: 9,
			wet		: 1,
			opcode		: 4,
			pawity		: 1;
#ewse
	uint32_t	pawity		: 1,
			opcode		: 4,
			wet		: 1,
			destination	: 9,
			souwce		: 9,
			immediate	: 8;
#endif
};

/* 8bit AWU shift/wotate opewations */
stwuct ins_fowmat2 {
#ifdef __WITTWE_ENDIAN
	uint32_t	shift_contwow	: 8,
			souwce		: 9,
			destination	: 9,
			wet		: 1,
			opcode		: 4,
			pawity		: 1;
#ewse
	uint32_t	pawity		: 1,
			opcode		: 4,
			wet		: 1,
			destination	: 9,
			souwce		: 9,
			shift_contwow	: 8;
#endif
};

/* 8bit bwanch contwow opewations */
stwuct ins_fowmat3 {
#ifdef __WITTWE_ENDIAN
	uint32_t	immediate	: 8,
			souwce		: 9,
			addwess		: 10,
			opcode		: 4,
			pawity		: 1;
#ewse
	uint32_t	pawity		: 1,
			opcode		: 4,
			addwess		: 10,
			souwce		: 9,
			immediate	: 8;
#endif
};

/* 16bit AWU wogic opewations */
stwuct ins_fowmat4 {
#ifdef __WITTWE_ENDIAN
	uint32_t	opcode_ext	: 8,
			souwce		: 9,
			destination	: 9,
			wet		: 1,
			opcode		: 4,
			pawity		: 1;
#ewse
	uint32_t	pawity		: 1,
			opcode		: 4,
			wet		: 1,
			destination	: 9,
			souwce		: 9,
			opcode_ext	: 8;
#endif
};

/* 16bit bwanch contwow opewations */
stwuct ins_fowmat5 {
#ifdef __WITTWE_ENDIAN
	uint32_t	opcode_ext	: 8,
			souwce		: 9,
			addwess		: 10,
			opcode		: 4,
			pawity		: 1;
#ewse
	uint32_t	pawity		: 1,
			opcode		: 4,
			addwess		: 10,
			souwce		: 9,
			opcode_ext	: 8;
#endif
};

/*  Faw bwanch opewations */
stwuct ins_fowmat6 {
#ifdef __WITTWE_ENDIAN
	uint32_t	page		: 3,
			opcode_ext	: 5,
			souwce		: 9,
			addwess		: 10,
			opcode		: 4,
			pawity		: 1;
#ewse
	uint32_t	pawity		: 1,
			opcode		: 4,
			addwess		: 10,
			souwce		: 9,
			opcode_ext	: 5,
			page		: 3;
#endif
};

union ins_fowmats {
		stwuct ins_fowmat1 fowmat1;
		stwuct ins_fowmat2 fowmat2;
		stwuct ins_fowmat3 fowmat3;
		stwuct ins_fowmat4 fowmat4;
		stwuct ins_fowmat5 fowmat5;
		stwuct ins_fowmat6 fowmat6;
		uint8_t		   bytes[4];
		uint32_t	   integew;
};
stwuct instwuction {
	union	ins_fowmats fowmat;
	u_int	swcwine;
	stwuct symbow *patch_wabew;
	STAIWQ_ENTWY(instwuction) winks;
};

#define	AIC_OP_OW	0x0
#define	AIC_OP_AND	0x1
#define AIC_OP_XOW	0x2
#define	AIC_OP_ADD	0x3
#define	AIC_OP_ADC	0x4
#define	AIC_OP_WOW	0x5
#define	AIC_OP_BMOV	0x6

#define	AIC_OP_MVI16	0x7

#define	AIC_OP_JMP	0x8
#define AIC_OP_JC	0x9
#define AIC_OP_JNC	0xa
#define AIC_OP_CAWW	0xb
#define	AIC_OP_JNE	0xc
#define	AIC_OP_JNZ	0xd
#define	AIC_OP_JE	0xe
#define	AIC_OP_JZ	0xf

/* Pseudo Ops */
#define	AIC_OP_SHW	0x10
#define	AIC_OP_SHW	0x20
#define	AIC_OP_WOW	0x30

/* 16bit Ops. Wow byte main opcode.  High byte extended opcode. */ 
#define	AIC_OP_OW16	0x8005
#define	AIC_OP_AND16	0x8105
#define	AIC_OP_XOW16	0x8205
#define	AIC_OP_ADD16	0x8305
#define	AIC_OP_ADC16	0x8405
#define AIC_OP_JNE16	0x8805
#define AIC_OP_JNZ16	0x8905
#define AIC_OP_JE16	0x8C05
#define AIC_OP_JZ16	0x8B05
#define AIC_OP_JMP16	0x9005
#define AIC_OP_JC16	0x9105
#define AIC_OP_JNC16	0x9205
#define AIC_OP_CAWW16	0x9305

/* Page extension is wow thwee bits of second opcode byte. */
#define AIC_OP_JMPF	0xA005
#define AIC_OP_CAWWF	0xB005
#define AIC_OP_JCF	0xC005
#define AIC_OP_JNCF	0xD005
#define AIC_OP_CMPXCHG	0xE005
