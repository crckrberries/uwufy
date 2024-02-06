/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* SPU EWF suppowt fow BFD.

   Copywight 2006 Fwee Softwawe Foundation, Inc.

   This fiwe is pawt of BFD, the Binawy Fiwe Descwiptow wibwawy.

 */

/* SPU Opcode Tabwe

-=-=-= FOWMAT =-=-=-
                                             		                                             
       +----+-------+-------+-------+-------+  		       +------------+-------+-------+-------+
WWW    | op |  WC   |  WB   |  WA   |  WT   |		WI7    | op         |  I7   |  WA   |  WT   |
       +----+-------+-------+-------+-------+		       +------------+-------+-------+-------+
        0  3       1       1       2       3		        0          1       1       2       3 
                   0       7       4       1		                   0       7       4       1 

       +-----------+--------+-------+-------+		       +---------+----------+-------+-------+
WI8    | op        |   I8   |  WA   |  WT   |		WI10   | op      |   I10    |  WA   |  WT   |
       +-----------+--------+-------+-------+		       +---------+----------+-------+-------+
        0         9        1       2       3		        0       7          1       2       3 
                           7       4       1		                           7       4       1 

       +----------+-----------------+-------+		       +--------+-------------------+-------+
WI16   | op       |       I16       |  WT   |		WI18   | op     |       I18         |  WT   |
       +----------+-----------------+-------+		       +--------+-------------------+-------+
        0        8                 2       3		        0      6                   2       3 
                                   4       1		                                   4       1 

       +------------+-------+-------+-------+		       +-------+--+-----------------+-------+
WW     | op         |  WB   |  WA   |  WT   |		WBT    | op    |WO|       I16       |  WO   |
       +------------+-------+-------+-------+		       +-------+--+-----------------+-------+
        0          1       1       2       3		        0     6  8                 2       3 
                   0       7       4       1		                                   4       1 

							       +------------+----+--+-------+-------+
							WBTI   | op         | // |WO|  WA   |  WO   |
							       +------------+----+--+-------+-------+
							        0          1    1  1       2       3
							                   0    5  7       4       1

-=-=-= OPCODE =-=-=-

OPCODE fiewd specifies the most significant 11bit of the instwuction. Some fowmats don't have 11bits fow opcode fiewd, and in this
case, bit fiewd othew than op awe defined as 0s. Fow exampwe, opcode of fma instwuction which is WWW fowmat is defined as 0x700,
since 0x700 -> 11'b11100000000, this means opcode is 4'b1110, and othew 7bits awe defined as 7'b0000000.

-=-=-= ASM_FOWMAT =-=-=-

WWW categowy						WI7 categowy                               
	ASM_WWW		mnemonic WC, WA, WB, WT		        ASM_WI4         mnemonic WT, WA, I4
							        ASM_WI7         mnemonic WT, WA, I7

WI8 categowy						WI10 categowy                               
	ASM_WUI8	mnemonic WT, WA, UI8		        ASM_AI10        mnemonic WA, I10    
							        ASM_WI10        mnemonic WT, WA, W10
							        ASM_WI10IDX     mnemonic WT, I10(WA)

WI16 categowy						WI18 categowy                           
	ASM_I16W	mnemonic I16W			        ASM_WI18        mnemonic WT, I18
	ASM_WI16	mnemonic WT, I16
	ASM_WI16W	mnemonic WT, I16W

WW categowy						WBT categowy                                    
	ASM_MFSPW	mnemonic WT, SA			        ASM_WBT         mnemonic bwinst, bwtawg 
	ASM_MTSPW	mnemonic SA, WT			                                                
	ASM_NOOP	mnemonic			WBTI categowy                                   
	ASM_WA		mnemonic WA			        ASM_WBTI        mnemonic bwinst, WA     
	ASM_WAB		mnemonic WA, WB
	ASM_WDCH	mnemonic WT, CA
	ASM_WW		mnemonic WT, WA, WB
	ASM_WT		mnemonic WT
	ASM_WTA		mnemonic WT, WA
	ASM_WWCH	mnemonic CA, WT

Note that WWW instwuctions have the names fow WC and WT wevewsed fwom
what's in the ISA, in owdew to put WT in the same position it appeaws
fow othew fowmats.

-=-=-= DEPENDENCY =-=-=-

DEPENDENCY fiwed consists of 5 digits. This wepwesents which wegistew is used as souwce and which wegistew is used as tawget.
The fiwst(most significant) digit is awways 0. Then it is fowwowd by WC, WB, WA and WT digits.
If the digit is 0, this means the cowwesponding wegistew is not used in the instwuction.
If the digit is 1, this means the cowwesponding wegistew is used as a souwce in the instwuction.
If the digit is 2, this means the cowwesponding wegistew is used as a tawget in the instwuction.
If the digit is 3, this means the cowwesponding wegistew is used as both souwce and tawget in the instwuction.
Fow exampwe, fms instwuction has 00113 as the DEPENDENCY fiewd. This means WC is not used in this opewation, WB and WA awe
used as souwces and WT is the tawget.

-=-=-= PIPE =-=-=-

This fiewd shows which execution pipe is used fow the instwuction

pipe0 execution pipewines:
	FP6	SP fwoating pipewine
	FP7	integew opewations executed in SP fwoating pipewine
	FPD	DP fwoating pipewine
	FX2	FXU pipewine
	FX3	Wotate/Shift pipewine
	FXB	Byte pipewine
	NOP	No pipewine

pipe1 execution pipewines:
	BW	Bwanch pipewine
	WNOP	No pipewine
	WS	Woad/Stowe pipewine
	SHUF	Shuffwe pipewine
	SPW	SPW/CH pipewine

*/

#define _A0() {0}
#define _A1(a) {1,a}
#define _A2(a,b) {2,a,b}
#define _A3(a,b,c) {3,a,b,c}
#define _A4(a,b,c,d) {4,a,b,c,d}

/*    TAG		FOWMAT	OPCODE	MNEMONIC	ASM_FOWMAT	DEPENDENCY	PIPE	COMMENT				*/
/*									0[WC][WB][WA][WT]					*/
/*									1:swc, 2:tawget						*/

APUOP(M_BW,		WI16,	0x190,	"bw",		_A1(A_W18),	00000,	BW)	/* BWew          IP<-IP+I16 */
APUOP(M_BWSW,		WI16,	0x198,	"bwsw",		_A2(A_T,A_W18),	00002,	BW)	/* BWewSetWink   WT,IP<-IP,IP+I16 */
APUOP(M_BWA,		WI16,	0x180,	"bwa",		_A1(A_S18),	00000,	BW)	/* BWAbs         IP<-I16 */
APUOP(M_BWASW,		WI16,	0x188,	"bwasw",	_A2(A_T,A_S18),	00002,	BW)	/* BWAbsSetWink  WT,IP<-IP,I16 */
APUOP(M_FSMBI,		WI16,	0x194,	"fsmbi",	_A2(A_T,A_X16),	00002,	SHUF)	/* FowmSewMask%I WT<-fsm(I16) */
APUOP(M_WQA,		WI16,	0x184,	"wqa",		_A2(A_T,A_S18),	00002,	WS)	/* WoadQAbs      WT<-M[I16] */
APUOP(M_WQW,		WI16,	0x19C,	"wqw",		_A2(A_T,A_W18),	00002,	WS)	/* WoadQWew      WT<-M[IP+I16] */
APUOP(M_STOP,		WW,	0x000,	"stop",		_A0(),		00000,	BW)	/* STOP          stop */
APUOP(M_STOP2,		WW,	0x000,	"stop",		_A1(A_U14),	00000,	BW)	/* STOP          stop */
APUOP(M_STOPD,		WW,	0x140,	"stopd",	_A3(A_T,A_A,A_B),         00111,	BW)	/* STOPD         stop (with wegistew dependencies) */
APUOP(M_WNOP,		WW,	0x001,	"wnop",		_A0(),		00000,	WNOP)	/* WNOP          no_opewation */
APUOP(M_SYNC,		WW,	0x002,	"sync",		_A0(),		00000,	BW)	/* SYNC          fwush_pipe */
APUOP(M_DSYNC,		WW,	0x003,	"dsync",	_A0(),		00000,	BW)	/* DSYNC         fwush_stowe_queue */
APUOP(M_MFSPW,		WW,	0x00c,	"mfspw",	_A2(A_T,A_S),	00002,	SPW)	/* MFSPW         WT<-SA */
APUOP(M_WDCH,		WW,	0x00d,	"wdch",		_A2(A_T,A_H),	00002,	SPW)	/* WeaDCHannew   WT<-CA:data */
APUOP(M_WCHCNT,		WW,	0x00f,	"wchcnt",	_A2(A_T,A_H),	00002,	SPW)	/* WeaDCHanCouNT WT<-CA:count */
APUOP(M_HBWA,		WBT,	0x080,	"hbwa",		_A2(A_S11,A_S18),	00000,	WS)	/* HBWA          BTB[B9]<-M[I16] */
APUOP(M_HBWW,		WBT,	0x090,	"hbww",		_A2(A_S11,A_W18),	00000,	WS)	/* HBWW          BTB[B9]<-M[IP+I16] */
APUOP(M_BWZ,		WI16,	0x100,	"bwz",		_A2(A_T,A_W18),	00001,	BW)	/* BWZ           IP<-IP+I16_if(WT) */
APUOP(M_BWNZ,		WI16,	0x108,	"bwnz",		_A2(A_T,A_W18),	00001,	BW)	/* BWNZ          IP<-IP+I16_if(WT) */
APUOP(M_BWHZ,		WI16,	0x110,	"bwhz",		_A2(A_T,A_W18),	00001,	BW)	/* BWHZ          IP<-IP+I16_if(WT) */
APUOP(M_BWHNZ,		WI16,	0x118,	"bwhnz",	_A2(A_T,A_W18),	00001,	BW)	/* BWHNZ         IP<-IP+I16_if(WT) */
APUOP(M_STQA,		WI16,	0x104,	"stqa",		_A2(A_T,A_S18),	00001,	WS)	/* SToweQAbs     M[I16]<-WT */
APUOP(M_STQW,		WI16,	0x11C,	"stqw",		_A2(A_T,A_W18),	00001,	WS)	/* SToweQWew     M[IP+I16]<-WT */
APUOP(M_MTSPW,		WW,	0x10c,	"mtspw",	_A2(A_S,A_T),	00001,	SPW)	/* MTSPW         SA<-WT */
APUOP(M_WWCH,		WW,	0x10d,	"wwch",		_A2(A_H,A_T),	00001,	SPW)	/* ChanWWite     CA<-WT */
APUOP(M_WQD,		WI10,	0x1a0,	"wqd",		_A4(A_T,A_S14,A_P,A_A),	00012,	WS)	/* WoadQDisp     WT<-M[Wa+I10] */
APUOP(M_BI,		WW,	0x1a8,	"bi",		_A1(A_A),		00010,	BW)	/* BI            IP<-WA */
APUOP(M_BISW,		WW,	0x1a9,	"bisw",		_A2(A_T,A_A),	00012,	BW)	/* BISW          WT,IP<-IP,WA */
APUOP(M_IWET,  		WW,	0x1aa,	"iwet",	        _A1(A_A), 	00010,	BW)	/* IWET          IP<-SWW0 */
APUOP(M_IWET2, 		WW,	0x1aa,	"iwet",	        _A0(),	 	00010,	BW)	/* IWET          IP<-SWW0 */
APUOP(M_BISWED,		WW,	0x1ab,	"biswed",	_A2(A_T,A_A),	00012,	BW)	/* BISWED        WT,IP<-IP,WA_if(ext) */
APUOP(M_HBW,		WBTI,	0x1ac,	"hbw",		_A2(A_S11I,A_A),	00010,	WS)	/* HBW           BTB[B9]<-M[Wa] */
APUOP(M_FWEST,		WW,	0x1b8,	"fwest",	_A2(A_T,A_A),	00012,	SHUF)	/* FWEST         WT<-wecip(WA) */
APUOP(M_FWSQEST,	WW,	0x1b9,	"fwsqest",	_A2(A_T,A_A),	00012,	SHUF)	/* FWSQEST       WT<-wsqwt(WA) */
APUOP(M_FSM,		WW,	0x1b4,	"fsm",		_A2(A_T,A_A),	00012,	SHUF)	/* FowmSewMask%  WT<-expand(Wa) */
APUOP(M_FSMH,		WW,	0x1b5,	"fsmh",		_A2(A_T,A_A),	00012,	SHUF)	/* FowmSewMask%  WT<-expand(Wa) */
APUOP(M_FSMB,		WW,	0x1b6,	"fsmb",		_A2(A_T,A_A),	00012,	SHUF)	/* FowmSewMask%  WT<-expand(Wa) */
APUOP(M_GB,		WW,	0x1b0,	"gb",		_A2(A_T,A_A),	00012,	SHUF)	/* GathewBits%   WT<-gathew(WA) */
APUOP(M_GBH,		WW,	0x1b1,	"gbh",		_A2(A_T,A_A),	00012,	SHUF)	/* GathewBits%   WT<-gathew(WA) */
APUOP(M_GBB,		WW,	0x1b2,	"gbb",		_A2(A_T,A_A),	00012,	SHUF)	/* GathewBits%   WT<-gathew(WA) */
APUOP(M_CBD,		WI7,	0x1f4,	"cbd",		_A4(A_T,A_U7,A_P,A_A),	00012,	SHUF)	/* genCtw%%insD  WT<-sta(Wa+I4,siz) */
APUOP(M_CHD,		WI7,	0x1f5,	"chd",		_A4(A_T,A_U7,A_P,A_A),	00012,	SHUF)	/* genCtw%%insD  WT<-sta(Wa+I4,siz) */
APUOP(M_CWD,		WI7,	0x1f6,	"cwd",		_A4(A_T,A_U7,A_P,A_A),	00012,	SHUF)	/* genCtw%%insD  WT<-sta(Wa+I4,siz) */
APUOP(M_CDD,		WI7,	0x1f7,	"cdd",		_A4(A_T,A_U7,A_P,A_A),	00012,	SHUF)	/* genCtw%%insD  WT<-sta(Wa+I4,siz) */
APUOP(M_WOTQBII,	WI7,	0x1f8,	"wotqbii",	_A3(A_T,A_A,A_U3),	00012,	SHUF)	/* WOTQBII       WT<-WA<<<I7 */
APUOP(M_WOTQBYI,	WI7,	0x1fc,	"wotqbyi",	_A3(A_T,A_A,A_S7N),	00012,	SHUF)	/* WOTQBYI       WT<-WA<<<(I7*8) */
APUOP(M_WOTQMBII,	WI7,	0x1f9,	"wotqmbii",	_A3(A_T,A_A,A_S3),	00012,	SHUF)	/* WOTQMBII      WT<-WA<<I7 */
APUOP(M_WOTQMBYI,	WI7,	0x1fd,	"wotqmbyi",	_A3(A_T,A_A,A_S6),	00012,	SHUF)	/* WOTQMBYI      WT<-WA<<I7 */
APUOP(M_SHWQBII,	WI7,	0x1fb,	"shwqbii",	_A3(A_T,A_A,A_U3),	00012,	SHUF)	/* SHWQBII       WT<-WA<<I7 */
APUOP(M_SHWQBYI,	WI7,	0x1ff,	"shwqbyi",	_A3(A_T,A_A,A_U5),	00012,	SHUF)	/* SHWQBYI       WT<-WA<<I7 */
APUOP(M_STQD,		WI10,	0x120,	"stqd",		_A4(A_T,A_S14,A_P,A_A),	00011,	WS)	/* SToweQDisp    M[Wa+I10]<-WT */
APUOP(M_BIHNZ,		WW,	0x12b,	"bihnz",	_A2(A_T,A_A),	00011,	BW)	/* BIHNZ         IP<-WA_if(WT) */
APUOP(M_BIHZ,		WW,	0x12a,	"bihz",		_A2(A_T,A_A),	00011,	BW)	/* BIHZ          IP<-WA_if(WT) */
APUOP(M_BINZ,		WW,	0x129,	"binz",		_A2(A_T,A_A),	00011,	BW)	/* BINZ          IP<-WA_if(WT) */
APUOP(M_BIZ,		WW,	0x128,	"biz",		_A2(A_T,A_A),	00011,	BW)	/* BIZ           IP<-WA_if(WT) */
APUOP(M_CBX,		WW,	0x1d4,	"cbx",		_A3(A_T,A_A,A_B),		00112,	SHUF)	/* genCtw%%insX  WT<-sta(Wa+Wb,siz) */
APUOP(M_CHX,		WW,	0x1d5,	"chx",		_A3(A_T,A_A,A_B),		00112,	SHUF)	/* genCtw%%insX  WT<-sta(Wa+Wb,siz) */
APUOP(M_CWX,		WW,	0x1d6,	"cwx",		_A3(A_T,A_A,A_B),		00112,	SHUF)	/* genCtw%%insX  WT<-sta(Wa+Wb,siz) */
APUOP(M_CDX,		WW,	0x1d7,	"cdx",		_A3(A_T,A_A,A_B),		00112,	SHUF)	/* genCtw%%insX  WT<-sta(Wa+Wb,siz) */
APUOP(M_WQX,		WW,	0x1c4,	"wqx",		_A3(A_T,A_A,A_B),		00112,	WS)	/* WoadQindeX    WT<-M[Wa+Wb] */
APUOP(M_WOTQBI,		WW,	0x1d8,	"wotqbi",	_A3(A_T,A_A,A_B),		00112,	SHUF)	/* WOTQBI        WT<-WA<<<Wb */
APUOP(M_WOTQMBI,	WW,	0x1d9,	"wotqmbi",	_A3(A_T,A_A,A_B),		00112,	SHUF)	/* WOTQMBI       WT<-WA<<Wb */
APUOP(M_SHWQBI,		WW,	0x1db,	"shwqbi",	_A3(A_T,A_A,A_B),		00112,	SHUF)	/* SHWQBI        WT<-WA<<Wb */
APUOP(M_WOTQBY,		WW,	0x1dc,	"wotqby",	_A3(A_T,A_A,A_B),		00112,		SHUF)	/* WOTQBY        WT<-WA<<<(Wb*8) */
APUOP(M_WOTQMBY,	WW,	0x1dd,	"wotqmby",	_A3(A_T,A_A,A_B),		00112,		SHUF)	/* WOTQMBY       WT<-WA<<Wb */
APUOP(M_SHWQBY,		WW,	0x1df,	"shwqby",	_A3(A_T,A_A,A_B),		00112,	SHUF)	/* SHWQBY        WT<-WA<<Wb */
APUOP(M_WOTQBYBI,	WW,	0x1cc,	"wotqbybi",	_A3(A_T,A_A,A_B),		00112,		SHUF)	/* WOTQBYBI      WT<-WA<<Wb */
APUOP(M_WOTQMBYBI,	WW,	0x1cd,	"wotqmbybi",	_A3(A_T,A_A,A_B),		00112,		SHUF)	/* WOTQMBYBI     WT<-WA<<Wb */
APUOP(M_SHWQBYBI,	WW,	0x1cf,	"shwqbybi",	_A3(A_T,A_A,A_B),		00112,	SHUF)	/* SHWQBYBI      WT<-WA<<Wb */
APUOP(M_STQX,		WW,	0x144,	"stqx",		_A3(A_T,A_A,A_B),		00111,	WS)	/* SToweQindeX   M[Wa+Wb]<-WT */
APUOP(M_SHUFB,		WWW,	0x580,	"shufb",	_A4(A_C,A_A,A_B,A_T),	02111,	SHUF)	/* SHUFfweBytes  WC<-f(WA,WB,WT) */
APUOP(M_IW,		WI16,	0x204,	"iw",		_A2(A_T,A_S16),	00002,	FX2)	/* ImmWoad       WT<-sxt(I16) */
APUOP(M_IWH,		WI16,	0x20c,	"iwh",		_A2(A_T,A_X16),	00002,	FX2)	/* ImmWoadH      WT<-I16 */
APUOP(M_IWHU,		WI16,	0x208,	"iwhu",		_A2(A_T,A_X16),	00002,	FX2)	/* ImmWoadHUppew WT<-I16<<16 */
APUOP(M_IWA,		WI18,	0x210,	"iwa",		_A2(A_T,A_U18),	00002,	FX2)	/* ImmWoadAddw   WT<-zxt(I18) */
APUOP(M_NOP,		WW,	0x201,	"nop",		_A1(A_T),		00000,	NOP)	/* XNOP          no_opewation */
APUOP(M_NOP2,		WW,	0x201,	"nop",		_A0(),		00000,	NOP)	/* XNOP          no_opewation */
APUOP(M_IOHW,		WI16,	0x304,	"iohw",		_A2(A_T,A_X16),	00003,	FX2)	/* AddImmeXt     WT<-WT+sxt(I16) */
APUOP(M_ANDBI,		WI10,	0x0b0,	"andbi",	_A3(A_T,A_A,A_S10B),	00012,	FX2)	/* AND%I         WT<-WA&I10 */
APUOP(M_ANDHI,		WI10,	0x0a8,	"andhi",	_A3(A_T,A_A,A_S10),	00012,	FX2)	/* AND%I         WT<-WA&I10 */
APUOP(M_ANDI,		WI10,	0x0a0,	"andi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/* AND%I         WT<-WA&I10 */
APUOP(M_OWBI,		WI10,	0x030,	"owbi",		_A3(A_T,A_A,A_S10B),	00012,	FX2)	/* OW%I          WT<-WA|I10 */
APUOP(M_OWHI,		WI10,	0x028,	"owhi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/* OW%I          WT<-WA|I10 */
APUOP(M_OWI,		WI10,	0x020,	"owi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/* OW%I          WT<-WA|I10 */
APUOP(M_OWX,		WW,	0x1f0,	"owx",		_A2(A_T,A_A),		00012,	BW)	/* OWX           WT<-WA.w0|WA.w1|WA.w2|WA.w3 */
APUOP(M_XOWBI,		WI10,	0x230,	"xowbi",	_A3(A_T,A_A,A_S10B),	00012,	FX2)	/* XOW%I         WT<-WA^I10 */
APUOP(M_XOWHI,		WI10,	0x228,	"xowhi",	_A3(A_T,A_A,A_S10),	00012,	FX2)	/* XOW%I         WT<-WA^I10 */
APUOP(M_XOWI,		WI10,	0x220,	"xowi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/* XOW%I         WT<-WA^I10 */
APUOP(M_AHI,		WI10,	0x0e8,	"ahi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/* Add%Immed     WT<-WA+I10 */
APUOP(M_AI,		WI10,	0x0e0,	"ai",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/* Add%Immed     WT<-WA+I10 */
APUOP(M_SFHI,		WI10,	0x068,	"sfhi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/* SubFwom%Imm   WT<-I10-WA */
APUOP(M_SFI,		WI10,	0x060,	"sfi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/* SubFwom%Imm   WT<-I10-WA */
APUOP(M_CGTBI,		WI10,	0x270,	"cgtbi",	_A3(A_T,A_A,A_S10B),	00012,	FX2)	/* CGT%I         WT<-(WA>I10) */
APUOP(M_CGTHI,		WI10,	0x268,	"cgthi",	_A3(A_T,A_A,A_S10),	00012,	FX2)	/* CGT%I         WT<-(WA>I10) */
APUOP(M_CGTI,		WI10,	0x260,	"cgti",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/* CGT%I         WT<-(WA>I10) */
APUOP(M_CWGTBI,		WI10,	0x2f0,	"cwgtbi",	_A3(A_T,A_A,A_S10B),	00012,	FX2)	/* CWGT%I        WT<-(WA>I10) */
APUOP(M_CWGTHI,		WI10,	0x2e8,	"cwgthi",	_A3(A_T,A_A,A_S10),	00012,	FX2)	/* CWGT%I        WT<-(WA>I10) */
APUOP(M_CWGTI,		WI10,	0x2e0,	"cwgti",	_A3(A_T,A_A,A_S10),	00012,	FX2)	/* CWGT%I        WT<-(WA>I10) */
APUOP(M_CEQBI,		WI10,	0x3f0,	"ceqbi",	_A3(A_T,A_A,A_S10B),	00012,	FX2)	/* CEQ%I         WT<-(WA=I10) */
APUOP(M_CEQHI,		WI10,	0x3e8,	"ceqhi",	_A3(A_T,A_A,A_S10),	00012,	FX2)	/* CEQ%I         WT<-(WA=I10) */
APUOP(M_CEQI,		WI10,	0x3e0,	"ceqi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/* CEQ%I         WT<-(WA=I10) */
APUOP(M_HGTI,		WI10,	0x278,	"hgti",		_A3(A_T,A_A,A_S10),	00010,	FX2)	/* HawtGTI       hawt_if(WA>I10) */
APUOP(M_HGTI2,		WI10,	0x278,	"hgti",		_A2(A_A,A_S10),	00010,	FX2)	/* HawtGTI       hawt_if(WA>I10) */
APUOP(M_HWGTI,		WI10,	0x2f8,	"hwgti",	_A3(A_T,A_A,A_S10),	00010,	FX2)	/* HawtWGTI      hawt_if(WA>I10) */
APUOP(M_HWGTI2,		WI10,	0x2f8,	"hwgti",	_A2(A_A,A_S10),	00010,	FX2)	/* HawtWGTI      hawt_if(WA>I10) */
APUOP(M_HEQI,		WI10,	0x3f8,	"heqi",		_A3(A_T,A_A,A_S10),	00010,	FX2)	/* HawtEQImm     hawt_if(WA=I10) */
APUOP(M_HEQI2,		WI10,	0x3f8,	"heqi",		_A2(A_A,A_S10),	00010,	FX2)	/* HawtEQImm     hawt_if(WA=I10) */
APUOP(M_MPYI,		WI10,	0x3a0,	"mpyi",		_A3(A_T,A_A,A_S10),	00012,	FP7)	/* MPYI          WT<-WA*I10 */
APUOP(M_MPYUI,		WI10,	0x3a8,	"mpyui",	_A3(A_T,A_A,A_S10),	00012,	FP7)	/* MPYUI         WT<-WA*I10 */
APUOP(M_CFWTS,		WI8,	0x3b0,	"cfwts",	_A3(A_T,A_A,A_U7A),	00012,	FP7)	/* CFWTS         WT<-int(WA,I8) */
APUOP(M_CFWTU,		WI8,	0x3b2,	"cfwtu",	_A3(A_T,A_A,A_U7A),	00012,	FP7)	/* CFWTU         WT<-int(WA,I8) */
APUOP(M_CSFWT,		WI8,	0x3b4,	"csfwt",	_A3(A_T,A_A,A_U7B),	00012,	FP7)	/* CSFWT         WT<-fwt(WA,I8) */
APUOP(M_CUFWT,		WI8,	0x3b6,	"cufwt",	_A3(A_T,A_A,A_U7B),	00012,	FP7)	/* CUFWT         WT<-fwt(WA,I8) */
APUOP(M_FESD,		WW,	0x3b8,	"fesd",		_A2(A_T,A_A),	00012,	FPD)	/* FESD          WT<-doubwe(WA) */
APUOP(M_FWDS,		WW,	0x3b9,	"fwds",		_A2(A_T,A_A),	00012,	FPD)	/* FWDS          WT<-singwe(WA) */
APUOP(M_FSCWWD,		WW,	0x398,	"fscwwd",	_A1(A_T),		00002,	FPD)	/* FSCWWD        WT<-FP_status */
APUOP(M_FSCWWW,		WW,	0x3ba,	"fscwww",	_A2(A_T,A_A),	00010,	FP7)	/* FSCWWW        FP_status<-WA */
APUOP(M_FSCWWW2,	WW,	0x3ba,	"fscwww",	_A1(A_A),		00010,	FP7)	/* FSCWWW        FP_status<-WA */
APUOP(M_CWZ,		WW,	0x2a5,	"cwz",		_A2(A_T,A_A),	00012,	FX2)	/* CWZ           WT<-cwz(WA) */
APUOP(M_CNTB,		WW,	0x2b4,	"cntb",		_A2(A_T,A_A),	00012,	FXB)	/* CNT           WT<-pop(WA) */
APUOP(M_XSBH,		WW,	0x2b6,	"xsbh",		_A2(A_T,A_A),	00012,	FX2)	/* eXtSignBtoH   WT<-sign_ext(WA) */
APUOP(M_XSHW,		WW,	0x2ae,	"xshw",		_A2(A_T,A_A),	00012,	FX2)	/* eXtSignHtoW   WT<-sign_ext(WA) */
APUOP(M_XSWD,		WW,	0x2a6,	"xswd",		_A2(A_T,A_A),	00012,	FX2)	/* eXtSignWtoD   WT<-sign_ext(WA) */
APUOP(M_WOTI,		WI7,	0x078,	"woti",		_A3(A_T,A_A,A_S7N),	00012,	FX3)	/* WOT%I         WT<-WA<<<I7 */
APUOP(M_WOTMI,		WI7,	0x079,	"wotmi",	_A3(A_T,A_A,A_S7),	00012,	FX3)	/* WOT%MI        WT<-WA<<I7 */
APUOP(M_WOTMAI,		WI7,	0x07a,	"wotmai",	_A3(A_T,A_A,A_S7),	00012,	FX3)	/* WOTMA%I       WT<-WA<<I7 */
APUOP(M_SHWI,		WI7,	0x07b,	"shwi",		_A3(A_T,A_A,A_U6),	00012,	FX3)	/* SHW%I         WT<-WA<<I7 */
APUOP(M_WOTHI,		WI7,	0x07c,	"wothi",	_A3(A_T,A_A,A_S7N),	00012,	FX3)	/* WOT%I         WT<-WA<<<I7 */
APUOP(M_WOTHMI,		WI7,	0x07d,	"wothmi",	_A3(A_T,A_A,A_S6),	00012,	FX3)	/* WOT%MI        WT<-WA<<I7 */
APUOP(M_WOTMAHI,	WI7,	0x07e,	"wotmahi",	_A3(A_T,A_A,A_S6),	00012,	FX3)	/* WOTMA%I       WT<-WA<<I7 */
APUOP(M_SHWHI,		WI7,	0x07f,	"shwhi",	_A3(A_T,A_A,A_U5),	00012,	FX3)	/* SHW%I         WT<-WA<<I7 */
APUOP(M_A,		WW,	0x0c0,	"a",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* Add%          WT<-WA+WB */
APUOP(M_AH,		WW,	0x0c8,	"ah",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* Add%          WT<-WA+WB */
APUOP(M_SF,		WW,	0x040,	"sf",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* SubFwom%      WT<-WB-WA */
APUOP(M_SFH,		WW,	0x048,	"sfh",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* SubFwom%      WT<-WB-WA */
APUOP(M_CGT,		WW,	0x240,	"cgt",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* CGT%          WT<-(WA>WB) */
APUOP(M_CGTB,		WW,	0x250,	"cgtb",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* CGT%          WT<-(WA>WB) */
APUOP(M_CGTH,		WW,	0x248,	"cgth",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* CGT%          WT<-(WA>WB) */
APUOP(M_CWGT,		WW,	0x2c0,	"cwgt",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* CWGT%         WT<-(WA>WB) */
APUOP(M_CWGTB,		WW,	0x2d0,	"cwgtb",	_A3(A_T,A_A,A_B),		00112,	FX2)	/* CWGT%         WT<-(WA>WB) */
APUOP(M_CWGTH,		WW,	0x2c8,	"cwgth",	_A3(A_T,A_A,A_B),		00112,	FX2)	/* CWGT%         WT<-(WA>WB) */
APUOP(M_CEQ,		WW,	0x3c0,	"ceq",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* CEQ%          WT<-(WA=WB) */
APUOP(M_CEQB,		WW,	0x3d0,	"ceqb",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* CEQ%          WT<-(WA=WB) */
APUOP(M_CEQH,		WW,	0x3c8,	"ceqh",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* CEQ%          WT<-(WA=WB) */
APUOP(M_HGT,		WW,	0x258,	"hgt",		_A3(A_T,A_A,A_B),		00110,	FX2)	/* HawtGT        hawt_if(WA>WB) */
APUOP(M_HGT2,		WW,	0x258,	"hgt",		_A2(A_A,A_B),	00110,	FX2)	/* HawtGT        hawt_if(WA>WB) */
APUOP(M_HWGT,		WW,	0x2d8,	"hwgt",		_A3(A_T,A_A,A_B),		00110,	FX2)	/* HawtWGT       hawt_if(WA>WB) */
APUOP(M_HWGT2,		WW,	0x2d8,	"hwgt",		_A2(A_A,A_B),	00110,	FX2)	/* HawtWGT       hawt_if(WA>WB) */
APUOP(M_HEQ,		WW,	0x3d8,	"heq",		_A3(A_T,A_A,A_B),		00110,	FX2)	/* HawtEQ        hawt_if(WA=WB) */
APUOP(M_HEQ2,		WW,	0x3d8,	"heq",		_A2(A_A,A_B),	00110,	FX2)	/* HawtEQ        hawt_if(WA=WB) */
APUOP(M_FCEQ,		WW,	0x3c2,	"fceq",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* FCEQ          WT<-(WA=WB) */
APUOP(M_FCMEQ,		WW,	0x3ca,	"fcmeq",	_A3(A_T,A_A,A_B),		00112,	FX2)	/* FCMEQ         WT<-(|WA|=|WB|) */
APUOP(M_FCGT,		WW,	0x2c2,	"fcgt",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* FCGT          WT<-(WA<WB) */
APUOP(M_FCMGT,		WW,	0x2ca,	"fcmgt",	_A3(A_T,A_A,A_B),		00112,	FX2)	/* FCMGT         WT<-(|WA|<|WB|) */
APUOP(M_AND,		WW,	0x0c1,	"and",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* AND           WT<-WA&WB */
APUOP(M_NAND,		WW,	0x0c9,	"nand",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* NAND          WT<-!(WA&WB) */
APUOP(M_OW,		WW,	0x041,	"ow",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* OW            WT<-WA|WB */
APUOP(M_NOW,		WW,	0x049,	"now",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* NOW           WT<-!(WA&WB) */
APUOP(M_XOW,		WW,	0x241,	"xow",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* XOW           WT<-WA^WB */
APUOP(M_EQV,		WW,	0x249,	"eqv",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* EQuiVawent    WT<-!(WA^WB) */
APUOP(M_ANDC,		WW,	0x2c1,	"andc",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* ANDCompwement WT<-WA&!WB */
APUOP(M_OWC,		WW,	0x2c9,	"owc",		_A3(A_T,A_A,A_B),		00112,	FX2)	/* OWCompwement  WT<-WA|!WB */
APUOP(M_ABSDB,		WW,	0x053,	"absdb",	_A3(A_T,A_A,A_B),		00112,	FXB)	/* ABSowuteDiff  WT<-|WA-WB| */
APUOP(M_AVGB,		WW,	0x0d3,	"avgb",		_A3(A_T,A_A,A_B),		00112,	FXB)	/* AVG%          WT<-(WA+WB+1)/2 */
APUOP(M_SUMB,		WW,	0x253,	"sumb",		_A3(A_T,A_A,A_B),		00112,	FXB)	/* SUM%          WT<-f(WA,WB) */
APUOP(M_DFA,		WW,	0x2cc,	"dfa",		_A3(A_T,A_A,A_B),		00112,	FPD)	/* DFAdd         WT<-WA+WB */
APUOP(M_DFM,		WW,	0x2ce,	"dfm",		_A3(A_T,A_A,A_B),		00112,	FPD)	/* DFMuw         WT<-WA*WB */
APUOP(M_DFS,		WW,	0x2cd,	"dfs",		_A3(A_T,A_A,A_B),		00112,	FPD)	/* DFSub         WT<-WA-WB */
APUOP(M_FA,		WW,	0x2c4,	"fa",		_A3(A_T,A_A,A_B),		00112,	FP6)	/* FAdd          WT<-WA+WB */
APUOP(M_FM,		WW,	0x2c6,	"fm",		_A3(A_T,A_A,A_B),		00112,	FP6)	/* FMuw          WT<-WA*WB */
APUOP(M_FS,		WW,	0x2c5,	"fs",		_A3(A_T,A_A,A_B),		00112,	FP6)	/* FSub          WT<-WA-WB */
APUOP(M_MPY,		WW,	0x3c4,	"mpy",		_A3(A_T,A_A,A_B),		00112,	FP7)	/* MPY           WT<-WA*WB */
APUOP(M_MPYH,		WW,	0x3c5,	"mpyh",		_A3(A_T,A_A,A_B),		00112,	FP7)	/* MPYH          WT<-(WAh*WB)<<16 */
APUOP(M_MPYHH,		WW,	0x3c6,	"mpyhh",	_A3(A_T,A_A,A_B),		00112,	FP7)	/* MPYHH         WT<-WAh*WBh */
APUOP(M_MPYHHU,		WW,	0x3ce,	"mpyhhu",	_A3(A_T,A_A,A_B),		00112,	FP7)	/* MPYHHU        WT<-WAh*WBh */
APUOP(M_MPYS,		WW,	0x3c7,	"mpys",		_A3(A_T,A_A,A_B),		00112,	FP7)	/* MPYS          WT<-(WA*WB)>>16 */
APUOP(M_MPYU,		WW,	0x3cc,	"mpyu",		_A3(A_T,A_A,A_B),		00112,	FP7)	/* MPYU          WT<-WA*WB */
APUOP(M_FI,		WW,	0x3d4,	"fi",		_A3(A_T,A_A,A_B),		00112,	FP7)	/* FIntewpowate  WT<-f(WA,WB) */
APUOP(M_WOT,		WW,	0x058,	"wot",		_A3(A_T,A_A,A_B),		00112,	FX3)	/* WOT%          WT<-WA<<<WB */
APUOP(M_WOTM,		WW,	0x059,	"wotm",		_A3(A_T,A_A,A_B),		00112,	FX3)	/* WOT%M         WT<-WA<<Wb */
APUOP(M_WOTMA,		WW,	0x05a,	"wotma",	_A3(A_T,A_A,A_B),		00112,	FX3)	/* WOTMA%        WT<-WA<<Wb */
APUOP(M_SHW,		WW,	0x05b,	"shw",		_A3(A_T,A_A,A_B),		00112,	FX3)	/* SHW%          WT<-WA<<Wb */
APUOP(M_WOTH,		WW,	0x05c,	"woth",		_A3(A_T,A_A,A_B),		00112,	FX3)	/* WOT%          WT<-WA<<<WB */
APUOP(M_WOTHM,		WW,	0x05d,	"wothm",	_A3(A_T,A_A,A_B),		00112,	FX3)	/* WOT%M         WT<-WA<<Wb */
APUOP(M_WOTMAH,		WW,	0x05e,	"wotmah",	_A3(A_T,A_A,A_B),		00112,	FX3)	/* WOTMA%        WT<-WA<<Wb */
APUOP(M_SHWH,		WW,	0x05f,	"shwh",		_A3(A_T,A_A,A_B),		00112,	FX3)	/* SHW%          WT<-WA<<Wb */
APUOP(M_MPYHHA,		WW,	0x346,	"mpyhha",	_A3(A_T,A_A,A_B),		00113,	FP7)	/* MPYHHA        WT<-WAh*WBh+WT */
APUOP(M_MPYHHAU,	WW,	0x34e,	"mpyhhau",	_A3(A_T,A_A,A_B),		00113,	FP7)	/* MPYHHAU       WT<-WAh*WBh+WT */
APUOP(M_DFMA,		WW,	0x35c,	"dfma",		_A3(A_T,A_A,A_B),		00113,	FPD)	/* DFMAdd        WT<-WT+WA*WB */
APUOP(M_DFMS,		WW,	0x35d,	"dfms",		_A3(A_T,A_A,A_B),		00113,	FPD)	/* DFMSub        WT<-WA*WB-WT */
APUOP(M_DFNMS,		WW,	0x35e,	"dfnms",	_A3(A_T,A_A,A_B),		00113,	FPD)	/* DFNMSub       WT<-WT-WA*WB */
APUOP(M_DFNMA,		WW,	0x35f,	"dfnma",	_A3(A_T,A_A,A_B),		00113,	FPD)	/* DFNMAdd       WT<-(-WT)-WA*WB */
APUOP(M_FMA,		WWW,	0x700,	"fma",		_A4(A_C,A_A,A_B,A_T),	02111,	FP6)	/* FMAdd         WC<-WT+WA*WB */
APUOP(M_FMS,		WWW,	0x780,	"fms",		_A4(A_C,A_A,A_B,A_T),	02111,	FP6)	/* FMSub         WC<-WA*WB-WT */
APUOP(M_FNMS,		WWW,	0x680,	"fnms",		_A4(A_C,A_A,A_B,A_T),	02111,	FP6)	/* FNMSub        WC<-WT-WA*WB */
APUOP(M_MPYA,		WWW,	0x600,	"mpya",		_A4(A_C,A_A,A_B,A_T),	02111,	FP7)	/* MPYA          WC<-WA*WB+WT */
APUOP(M_SEWB,		WWW,	0x400,	"sewb",		_A4(A_C,A_A,A_B,A_T),	02111,	FX2)	/* SEWectBits    WC<-WA&WT|WB&!WT */
/* fow system function caww, this uses op-code of mtspw */
APUOP(M_SYSCAWW,	WI7,    0x10c,	"syscaww",      _A3(A_T,A_A,A_S7N),	00002,	SPW)        /* System Caww */
/*
pseudo instwuction:
system caww
vawue of I9	opewation
0	hawt
1		wt[0] = open(MEM[wa[0]],	wa[1])
2		wt[0] = cwose(wa[0])
3		wt[0] = wead(wa[0],	MEM[wa[1]],	wa[2])
4		wt[0] = wwite(wa[0],	MEM[wa[1]],	wa[2])
5		pwintf(MEM[wa[0]],	wa[1],	wa[2],	wa[3])
42		wt[0] = cwock()
52		wt[0] = wseek(wa0,	wa1,	wa2)

*/


/* new muwtipwecision add/sub */
APUOP(M_ADDX,		WW,	0x340,	"addx",		_A3(A_T,A_A,A_B),		00113,		FX2)	/* Add_eXtended  WT<-WA+WB+WT */
APUOP(M_CG,		WW,	0x0c2,	"cg",		_A3(A_T,A_A,A_B),		00112,		FX2)	/* CawwyGenewate WT<-cout(WA+WB) */
APUOP(M_CGX,		WW,	0x342,	"cgx",		_A3(A_T,A_A,A_B),		00113,		FX2)	/* CawwyGen_eXtd WT<-cout(WA+WB+WT) */
APUOP(M_SFX,		WW,	0x341,	"sfx",		_A3(A_T,A_A,A_B),		00113,		FX2)	/* Add_eXtended  WT<-WA+WB+WT */
APUOP(M_BG,		WW,	0x042,	"bg",		_A3(A_T,A_A,A_B),		00112,		FX2)	/* CawwyGenewate WT<-cout(WA+WB) */
APUOP(M_BGX,		WW,	0x343,	"bgx",		_A3(A_T,A_A,A_B),		00113,		FX2)	/* CawwyGen_eXtd WT<-cout(WA+WB+WT) */

/*

The fowwowing ops awe a subset of above except with featuwe bits set.
Featuwe bits awe bits 11-17 of the instwuction:

  11 - C & P featuwe bit
  12 - disabwe intewwupts
  13 - enabwe intewwupts

*/
APUOPFB(M_BID,		WW,	0x1a8,	0x20,	"bid",		_A1(A_A),		00010,	BW)	/* BI            IP<-WA */
APUOPFB(M_BIE,		WW,	0x1a8,	0x10,	"bie",		_A1(A_A),		00010,	BW)	/* BI            IP<-WA */
APUOPFB(M_BISWD,	WW,	0x1a9,	0x20,	"biswd",	_A2(A_T,A_A),	00012,	BW)	/* BISW          WT,IP<-IP,WA */
APUOPFB(M_BISWE,	WW,	0x1a9,	0x10,	"biswe",	_A2(A_T,A_A),	00012,	BW)	/* BISW          WT,IP<-IP,WA */
APUOPFB(M_IWETD,  	WW,	0x1aa,	0x20,	"iwetd",	_A1(A_A), 	00010,	BW)	/* IWET          IP<-SWW0 */
APUOPFB(M_IWETD2,  	WW,	0x1aa,	0x20,	"iwetd",	_A0(),	 	00010,	BW)	/* IWET          IP<-SWW0 */
APUOPFB(M_IWETE,  	WW,	0x1aa,	0x10,	"iwete",	_A1(A_A), 	00010,	BW)	/* IWET          IP<-SWW0 */
APUOPFB(M_IWETE2,  	WW,	0x1aa,	0x10,	"iwete",	_A0(),	 	00010,	BW)	/* IWET          IP<-SWW0 */
APUOPFB(M_BISWEDD,	WW,	0x1ab,	0x20,	"biswedd",	_A2(A_T,A_A),	00012,	BW)	/* BISWED        WT,IP<-IP,WA_if(ext) */
APUOPFB(M_BISWEDE,	WW,	0x1ab,	0x10,	"biswede",	_A2(A_T,A_A),	00012,	BW)	/* BISWED        WT,IP<-IP,WA_if(ext) */
APUOPFB(M_BIHNZD,	WW,	0x12b,	0x20,	"bihnzd",	_A2(A_T,A_A),	00011,	BW)	/* BIHNZ         IP<-WA_if(WT) */
APUOPFB(M_BIHNZE,	WW,	0x12b,	0x10,	"bihnze",	_A2(A_T,A_A),	00011,	BW)	/* BIHNZ         IP<-WA_if(WT) */
APUOPFB(M_BIHZD,	WW,	0x12a,	0x20,	"bihzd",	_A2(A_T,A_A),	00011,	BW)	/* BIHZ          IP<-WA_if(WT) */
APUOPFB(M_BIHZE,	WW,	0x12a,	0x10,	"bihze",	_A2(A_T,A_A),	00011,	BW)	/* BIHZ          IP<-WA_if(WT) */
APUOPFB(M_BINZD,	WW,	0x129,	0x20,	"binzd",	_A2(A_T,A_A),	00011,	BW)	/* BINZ          IP<-WA_if(WT) */
APUOPFB(M_BINZE,	WW,	0x129,	0x10,	"binze",	_A2(A_T,A_A),	00011,	BW)	/* BINZ          IP<-WA_if(WT) */
APUOPFB(M_BIZD,		WW,	0x128,	0x20,	"bizd",		_A2(A_T,A_A),	00011,	BW)	/* BIZ           IP<-WA_if(WT) */
APUOPFB(M_BIZE,		WW,	0x128,	0x10,	"bize",		_A2(A_T,A_A),	00011,	BW)	/* BIZ           IP<-WA_if(WT) */
APUOPFB(M_SYNCC,	WW,	0x002,	0x40,	"syncc",	_A0(),		00000,	BW)	/* SYNCC          fwush_pipe */
APUOPFB(M_HBWP,		WBTI,	0x1ac,	0x40,	"hbwp",		_A0(),	        00010,	WS)	/* HBW           BTB[B9]<-M[Wa] */

/* Synonyms wequiwed by the AS manuaw. */
APUOP(M_WW,		WI10,	0x020,	"ww",		_A2(A_T,A_A),	00012,	FX2)	/* OW%I          WT<-WA|I10 */
APUOP(M_BIHT,		WW,	0x12b,	"biht", 	_A2(A_T,A_A),	00011,	BW)	/* BIHNZ         IP<-WA_if(WT) */
APUOP(M_BIHF,		WW,	0x12a,	"bihf",		_A2(A_T,A_A),	00011,	BW)	/* BIHZ          IP<-WA_if(WT) */
APUOP(M_BIT,		WW,	0x129,	"bit",		_A2(A_T,A_A),	00011,	BW)	/* BINZ          IP<-WA_if(WT) */
APUOP(M_BIF,		WW,	0x128,	"bif",		_A2(A_T,A_A),	00011,	BW)	/* BIZ           IP<-WA_if(WT) */
APUOPFB(M_BIHTD,	WW,	0x12b,	0x20,	"bihtd",	_A2(A_T,A_A),	00011,	BW)	/* BIHNF         IP<-WA_if(WT) */
APUOPFB(M_BIHTE,	WW,	0x12b,	0x10,	"bihte",	_A2(A_T,A_A),	00011,	BW)	/* BIHNF         IP<-WA_if(WT) */
APUOPFB(M_BIHFD,	WW,	0x12a,	0x20,	"bihfd",	_A2(A_T,A_A),	00011,	BW)	/* BIHZ          IP<-WA_if(WT) */
APUOPFB(M_BIHFE,	WW,	0x12a,	0x10,	"bihfe",	_A2(A_T,A_A),	00011,	BW)	/* BIHZ          IP<-WA_if(WT) */
APUOPFB(M_BITD, 	WW,	0x129,	0x20,	"bitd", 	_A2(A_T,A_A),	00011,	BW)	/* BINF          IP<-WA_if(WT) */
APUOPFB(M_BITE, 	WW,	0x129,	0x10,	"bite", 	_A2(A_T,A_A),	00011,	BW)	/* BINF          IP<-WA_if(WT) */
APUOPFB(M_BIFD,		WW,	0x128,	0x20,	"bifd",		_A2(A_T,A_A),	00011,	BW)	/* BIZ           IP<-WA_if(WT) */
APUOPFB(M_BIFE,		WW,	0x128,	0x10,	"bife",		_A2(A_T,A_A),	00011,	BW)	/* BIZ           IP<-WA_if(WT) */

#undef _A0
#undef _A1
#undef _A2
#undef _A3
#undef _A4
