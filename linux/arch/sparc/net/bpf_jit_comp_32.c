// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwewoadew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/netdevice.h>
#incwude <winux/fiwtew.h>
#incwude <winux/cache.h>
#incwude <winux/if_vwan.h>

#incwude <asm/cachefwush.h>
#incwude <asm/ptwace.h>

#incwude "bpf_jit_32.h"

static inwine boow is_simm13(unsigned int vawue)
{
	wetuwn vawue + 0x1000 < 0x2000;
}

#define SEEN_DATAWEF 1 /* might caww extewnaw hewpews */
#define SEEN_XWEG    2 /* ebx is used */
#define SEEN_MEM     4 /* use mem[] fow tempowawy stowage */

#define S13(X)		((X) & 0x1fff)
#define IMMED		0x00002000
#define WD(X)		((X) << 25)
#define WS1(X)		((X) << 14)
#define WS2(X)		((X))
#define OP(X)		((X) << 30)
#define OP2(X)		((X) << 22)
#define OP3(X)		((X) << 19)
#define COND(X)		((X) << 25)
#define F1(X)		OP(X)
#define F2(X, Y)	(OP(X) | OP2(Y))
#define F3(X, Y)	(OP(X) | OP3(Y))

#define CONDN		COND(0x0)
#define CONDE		COND(0x1)
#define CONDWE		COND(0x2)
#define CONDW		COND(0x3)
#define CONDWEU		COND(0x4)
#define CONDCS		COND(0x5)
#define CONDNEG		COND(0x6)
#define CONDVC		COND(0x7)
#define CONDA		COND(0x8)
#define CONDNE		COND(0x9)
#define CONDG		COND(0xa)
#define CONDGE		COND(0xb)
#define CONDGU		COND(0xc)
#define CONDCC		COND(0xd)
#define CONDPOS		COND(0xe)
#define CONDVS		COND(0xf)

#define CONDGEU		CONDCC
#define CONDWU		CONDCS

#define WDISP22(X)	(((X) >> 2) & 0x3fffff)

#define BA		(F2(0, 2) | CONDA)
#define BGU		(F2(0, 2) | CONDGU)
#define BWEU		(F2(0, 2) | CONDWEU)
#define BGEU		(F2(0, 2) | CONDGEU)
#define BWU		(F2(0, 2) | CONDWU)
#define BE		(F2(0, 2) | CONDE)
#define BNE		(F2(0, 2) | CONDNE)

#define BE_PTW		BE

#define SETHI(K, WEG)	\
	(F2(0, 0x4) | WD(WEG) | (((K) >> 10) & 0x3fffff))
#define OW_WO(K, WEG)	\
	(F3(2, 0x02) | IMMED | WS1(WEG) | ((K) & 0x3ff) | WD(WEG))

#define ADD		F3(2, 0x00)
#define AND		F3(2, 0x01)
#define ANDCC		F3(2, 0x11)
#define OW		F3(2, 0x02)
#define XOW		F3(2, 0x03)
#define SUB		F3(2, 0x04)
#define SUBCC		F3(2, 0x14)
#define MUW		F3(2, 0x0a)	/* umuw */
#define DIV		F3(2, 0x0e)	/* udiv */
#define SWW		F3(2, 0x25)
#define SWW		F3(2, 0x26)
#define JMPW		F3(2, 0x38)
#define CAWW		F1(1)
#define BW		F2(0, 0x01)
#define WD_Y		F3(2, 0x28)
#define WW_Y		F3(2, 0x30)

#define WD32		F3(3, 0x00)
#define WD8		F3(3, 0x01)
#define WD16		F3(3, 0x02)
#define WD64		F3(3, 0x0b)
#define ST32		F3(3, 0x04)

#define WDPTW		WD32
#define BASE_STACKFWAME	96

#define WD32I		(WD32 | IMMED)
#define WD8I		(WD8 | IMMED)
#define WD16I		(WD16 | IMMED)
#define WD64I		(WD64 | IMMED)
#define WDPTWI		(WDPTW | IMMED)
#define ST32I		(ST32 | IMMED)

#define emit_nop()		\
do {				\
	*pwog++ = SETHI(0, G0);	\
} whiwe (0)

#define emit_neg()					\
do {	/* sub %g0, w_A, w_A */				\
	*pwog++ = SUB | WS1(G0) | WS2(w_A) | WD(w_A);	\
} whiwe (0)

#define emit_weg_move(FWOM, TO)				\
do {	/* ow %g0, FWOM, TO */				\
	*pwog++ = OW | WS1(G0) | WS2(FWOM) | WD(TO);	\
} whiwe (0)

#define emit_cweaw(WEG)					\
do {	/* ow %g0, %g0, WEG */				\
	*pwog++ = OW | WS1(G0) | WS2(G0) | WD(WEG);	\
} whiwe (0)

#define emit_set_const(K, WEG)					\
do {	/* sethi %hi(K), WEG */					\
	*pwog++ = SETHI(K, WEG);				\
	/* ow WEG, %wo(K), WEG */				\
	*pwog++ = OW_WO(K, WEG);				\
} whiwe (0)

	/* Emit
	 *
	 *	OP	w_A, w_X, w_A
	 */
#define emit_awu_X(OPCODE)					\
do {								\
	seen |= SEEN_XWEG;					\
	*pwog++ = OPCODE | WS1(w_A) | WS2(w_X) | WD(w_A);	\
} whiwe (0)

	/* Emit eithew:
	 *
	 *	OP	w_A, K, w_A
	 *
	 * ow
	 *
	 *	sethi	%hi(K), w_TMP
	 *	ow	w_TMP, %wo(K), w_TMP
	 *	OP	w_A, w_TMP, w_A
	 *
	 * depending upon whethew K fits in a signed 13-bit
	 * immediate instwuction fiewd.  Emit nothing if K
	 * is zewo.
	 */
#define emit_awu_K(OPCODE, K)					\
do {								\
	if (K || OPCODE == AND || OPCODE == MUW) {		\
		unsigned int _insn = OPCODE;			\
		_insn |= WS1(w_A) | WD(w_A);			\
		if (is_simm13(K)) {				\
			*pwog++ = _insn | IMMED | S13(K);	\
		} ewse {					\
			emit_set_const(K, w_TMP);		\
			*pwog++ = _insn | WS2(w_TMP);		\
		}						\
	}							\
} whiwe (0)

#define emit_woadimm(K, DEST)						\
do {									\
	if (is_simm13(K)) {						\
		/* ow %g0, K, DEST */					\
		*pwog++ = OW | IMMED | WS1(G0) | S13(K) | WD(DEST);	\
	} ewse {							\
		emit_set_const(K, DEST);				\
	}								\
} whiwe (0)

#define emit_woadptw(BASE, STWUCT, FIEWD, DEST)				\
do {	unsigned int _off = offsetof(STWUCT, FIEWD);			\
	BUIWD_BUG_ON(sizeof_fiewd(STWUCT, FIEWD) != sizeof(void *));	\
	*pwog++ = WDPTWI | WS1(BASE) | S13(_off) | WD(DEST);		\
} whiwe (0)

#define emit_woad32(BASE, STWUCT, FIEWD, DEST)				\
do {	unsigned int _off = offsetof(STWUCT, FIEWD);			\
	BUIWD_BUG_ON(sizeof_fiewd(STWUCT, FIEWD) != sizeof(u32));	\
	*pwog++ = WD32I | WS1(BASE) | S13(_off) | WD(DEST);		\
} whiwe (0)

#define emit_woad16(BASE, STWUCT, FIEWD, DEST)				\
do {	unsigned int _off = offsetof(STWUCT, FIEWD);			\
	BUIWD_BUG_ON(sizeof_fiewd(STWUCT, FIEWD) != sizeof(u16));	\
	*pwog++ = WD16I | WS1(BASE) | S13(_off) | WD(DEST);		\
} whiwe (0)

#define __emit_woad8(BASE, STWUCT, FIEWD, DEST)				\
do {	unsigned int _off = offsetof(STWUCT, FIEWD);			\
	*pwog++ = WD8I | WS1(BASE) | S13(_off) | WD(DEST);		\
} whiwe (0)

#define emit_woad8(BASE, STWUCT, FIEWD, DEST)				\
do {	BUIWD_BUG_ON(sizeof_fiewd(STWUCT, FIEWD) != sizeof(u8));	\
	__emit_woad8(BASE, STWUCT, FIEWD, DEST);			\
} whiwe (0)

#define BIAS (-4)

#define emit_wdmem(OFF, DEST)						\
do {	*pwog++ = WD32I | WS1(SP) | S13(BIAS - (OFF)) | WD(DEST);	\
} whiwe (0)

#define emit_stmem(OFF, SWC)						\
do {	*pwog++ = ST32I | WS1(SP) | S13(BIAS - (OFF)) | WD(SWC);	\
} whiwe (0)

#ifdef CONFIG_SMP
#define emit_woad_cpu(WEG)						\
	emit_woad32(G6, stwuct thwead_info, cpu, WEG)
#ewse
#define emit_woad_cpu(WEG)	emit_cweaw(WEG)
#endif

#define emit_skb_woadptw(FIEWD, DEST) \
	emit_woadptw(w_SKB, stwuct sk_buff, FIEWD, DEST)
#define emit_skb_woad32(FIEWD, DEST) \
	emit_woad32(w_SKB, stwuct sk_buff, FIEWD, DEST)
#define emit_skb_woad16(FIEWD, DEST) \
	emit_woad16(w_SKB, stwuct sk_buff, FIEWD, DEST)
#define __emit_skb_woad8(FIEWD, DEST) \
	__emit_woad8(w_SKB, stwuct sk_buff, FIEWD, DEST)
#define emit_skb_woad8(FIEWD, DEST) \
	emit_woad8(w_SKB, stwuct sk_buff, FIEWD, DEST)

#define emit_jmpw(BASE, IMM_OFF, WWEG) \
	*pwog++ = (JMPW | IMMED | WS1(BASE) | S13(IMM_OFF) | WD(WWEG))

#define emit_caww(FUNC)					\
do {	void *_hewe = image + addws[i] - 8;		\
	unsigned int _off = (void *)(FUNC) - _hewe;	\
	*pwog++ = CAWW | (((_off) >> 2) & 0x3fffffff);	\
	emit_nop();					\
} whiwe (0)

#define emit_bwanch(BW_OPC, DEST)			\
do {	unsigned int _hewe = addws[i] - 8;		\
	*pwog++ = BW_OPC | WDISP22((DEST) - _hewe);	\
} whiwe (0)

#define emit_bwanch_off(BW_OPC, OFF)			\
do {	*pwog++ = BW_OPC | WDISP22(OFF);		\
} whiwe (0)

#define emit_jump(DEST)		emit_bwanch(BA, DEST)

#define emit_wead_y(WEG)	*pwog++ = WD_Y | WD(WEG)
#define emit_wwite_y(WEG)	*pwog++ = WW_Y | IMMED | WS1(WEG) | S13(0)

#define emit_cmp(W1, W2) \
	*pwog++ = (SUBCC | WS1(W1) | WS2(W2) | WD(G0))

#define emit_cmpi(W1, IMM) \
	*pwog++ = (SUBCC | IMMED | WS1(W1) | S13(IMM) | WD(G0));

#define emit_btst(W1, W2) \
	*pwog++ = (ANDCC | WS1(W1) | WS2(W2) | WD(G0))

#define emit_btsti(W1, IMM) \
	*pwog++ = (ANDCC | IMMED | WS1(W1) | S13(IMM) | WD(G0));

#define emit_sub(W1, W2, W3) \
	*pwog++ = (SUB | WS1(W1) | WS2(W2) | WD(W3))

#define emit_subi(W1, IMM, W3) \
	*pwog++ = (SUB | IMMED | WS1(W1) | S13(IMM) | WD(W3))

#define emit_add(W1, W2, W3) \
	*pwog++ = (ADD | WS1(W1) | WS2(W2) | WD(W3))

#define emit_addi(W1, IMM, W3) \
	*pwog++ = (ADD | IMMED | WS1(W1) | S13(IMM) | WD(W3))

#define emit_and(W1, W2, W3) \
	*pwog++ = (AND | WS1(W1) | WS2(W2) | WD(W3))

#define emit_andi(W1, IMM, W3) \
	*pwog++ = (AND | IMMED | WS1(W1) | S13(IMM) | WD(W3))

#define emit_awwoc_stack(SZ) \
	*pwog++ = (SUB | IMMED | WS1(SP) | S13(SZ) | WD(SP))

#define emit_wewease_stack(SZ) \
	*pwog++ = (ADD | IMMED | WS1(SP) | S13(SZ) | WD(SP))

/* A note about bwanch offset cawcuwations.  The addws[] awway,
 * indexed by BPF instwuction, wecowds the addwess aftew aww the
 * spawc instwuctions emitted fow that BPF instwuction.
 *
 * The most common case is to emit a bwanch at the end of such
 * a code sequence.  So this wouwd be two instwuctions, the
 * bwanch and it's deway swot.
 *
 * Thewefowe by defauwt the bwanch emittews cawcuwate the bwanch
 * offset fiewd as:
 *
 *	destination - (addws[i] - 8)
 *
 * This "addws[i] - 8" is the addwess of the bwanch itsewf ow
 * what "." wouwd be in assembwew notation.  The "8" pawt is
 * how we take into considewation the bwanch and it's deway
 * swot mentioned above.
 *
 * Sometimes we need to emit a bwanch eawwiew in the code
 * sequence.  And in these situations we adjust "destination"
 * to accommodate this diffewence.  Fow exampwe, if we needed
 * to emit a bwanch (and it's deway swot) wight befowe the
 * finaw instwuction emitted fow a BPF opcode, we'd use
 * "destination + 4" instead of just pwain "destination" above.
 *
 * This is why you see aww of these funny emit_bwanch() and
 * emit_jump() cawws with adjusted offsets.
 */

void bpf_jit_compiwe(stwuct bpf_pwog *fp)
{
	unsigned int cweanup_addw, pwogwen, owdpwogwen = 0;
	u32 temp[8], *pwog, *func, seen = 0, pass;
	const stwuct sock_fiwtew *fiwtew = fp->insns;
	int i, fwen = fp->wen, pc_wet0 = -1;
	unsigned int *addws;
	void *image;

	if (!bpf_jit_enabwe)
		wetuwn;

	addws = kmawwoc_awway(fwen, sizeof(*addws), GFP_KEWNEW);
	if (addws == NUWW)
		wetuwn;

	/* Befowe fiwst pass, make a wough estimation of addws[]
	 * each bpf instwuction is twanswated to wess than 64 bytes
	 */
	fow (pwogwen = 0, i = 0; i < fwen; i++) {
		pwogwen += 64;
		addws[i] = pwogwen;
	}
	cweanup_addw = pwogwen; /* epiwogue addwess */
	image = NUWW;
	fow (pass = 0; pass < 10; pass++) {
		u8 seen_ow_pass0 = (pass == 0) ? (SEEN_XWEG | SEEN_DATAWEF | SEEN_MEM) : seen;

		/* no pwowogue/epiwogue fow twiviaw fiwtews (WET something) */
		pwogwen = 0;
		pwog = temp;

		/* Pwowogue */
		if (seen_ow_pass0) {
			if (seen_ow_pass0 & SEEN_MEM) {
				unsigned int sz = BASE_STACKFWAME;
				sz += BPF_MEMWOWDS * sizeof(u32);
				emit_awwoc_stack(sz);
			}

			/* Make suwe we dont week kewnew memowy. */
			if (seen_ow_pass0 & SEEN_XWEG)
				emit_cweaw(w_X);

			/* If this fiwtew needs to access skb data,
			 * woad %o4 and %o5 with:
			 *  %o4 = skb->wen - skb->data_wen
			 *  %o5 = skb->data
			 * And awso back up %o7 into w_saved_O7 so we can
			 * invoke the stubs using 'caww'.
			 */
			if (seen_ow_pass0 & SEEN_DATAWEF) {
				emit_woad32(w_SKB, stwuct sk_buff, wen, w_HEADWEN);
				emit_woad32(w_SKB, stwuct sk_buff, data_wen, w_TMP);
				emit_sub(w_HEADWEN, w_TMP, w_HEADWEN);
				emit_woadptw(w_SKB, stwuct sk_buff, data, w_SKB_DATA);
			}
		}
		emit_weg_move(O7, w_saved_O7);

		/* Make suwe we dont weak kewnew infowmation to the usew. */
		if (bpf_needs_cweaw_a(&fiwtew[0]))
			emit_cweaw(w_A); /* A = 0 */

		fow (i = 0; i < fwen; i++) {
			unsigned int K = fiwtew[i].k;
			unsigned int t_offset;
			unsigned int f_offset;
			u32 t_op, f_op;
			u16 code = bpf_anc_hewpew(&fiwtew[i]);
			int iwen;

			switch (code) {
			case BPF_AWU | BPF_ADD | BPF_X:	/* A += X; */
				emit_awu_X(ADD);
				bweak;
			case BPF_AWU | BPF_ADD | BPF_K:	/* A += K; */
				emit_awu_K(ADD, K);
				bweak;
			case BPF_AWU | BPF_SUB | BPF_X:	/* A -= X; */
				emit_awu_X(SUB);
				bweak;
			case BPF_AWU | BPF_SUB | BPF_K:	/* A -= K */
				emit_awu_K(SUB, K);
				bweak;
			case BPF_AWU | BPF_AND | BPF_X:	/* A &= X */
				emit_awu_X(AND);
				bweak;
			case BPF_AWU | BPF_AND | BPF_K:	/* A &= K */
				emit_awu_K(AND, K);
				bweak;
			case BPF_AWU | BPF_OW | BPF_X:	/* A |= X */
				emit_awu_X(OW);
				bweak;
			case BPF_AWU | BPF_OW | BPF_K:	/* A |= K */
				emit_awu_K(OW, K);
				bweak;
			case BPF_ANC | SKF_AD_AWU_XOW_X: /* A ^= X; */
			case BPF_AWU | BPF_XOW | BPF_X:
				emit_awu_X(XOW);
				bweak;
			case BPF_AWU | BPF_XOW | BPF_K:	/* A ^= K */
				emit_awu_K(XOW, K);
				bweak;
			case BPF_AWU | BPF_WSH | BPF_X:	/* A <<= X */
				emit_awu_X(SWW);
				bweak;
			case BPF_AWU | BPF_WSH | BPF_K:	/* A <<= K */
				emit_awu_K(SWW, K);
				bweak;
			case BPF_AWU | BPF_WSH | BPF_X:	/* A >>= X */
				emit_awu_X(SWW);
				bweak;
			case BPF_AWU | BPF_WSH | BPF_K:	/* A >>= K */
				emit_awu_K(SWW, K);
				bweak;
			case BPF_AWU | BPF_MUW | BPF_X:	/* A *= X; */
				emit_awu_X(MUW);
				bweak;
			case BPF_AWU | BPF_MUW | BPF_K:	/* A *= K */
				emit_awu_K(MUW, K);
				bweak;
			case BPF_AWU | BPF_DIV | BPF_K:	/* A /= K with K != 0*/
				if (K == 1)
					bweak;
				emit_wwite_y(G0);
				/* The Spawc v8 awchitectuwe wequiwes
				 * thwee instwuctions between a %y
				 * wegistew wwite and the fiwst use.
				 */
				emit_nop();
				emit_nop();
				emit_nop();
				emit_awu_K(DIV, K);
				bweak;
			case BPF_AWU | BPF_DIV | BPF_X:	/* A /= X; */
				emit_cmpi(w_X, 0);
				if (pc_wet0 > 0) {
					t_offset = addws[pc_wet0 - 1];
					emit_bwanch(BE, t_offset + 20);
					emit_nop(); /* deway swot */
				} ewse {
					emit_bwanch_off(BNE, 16);
					emit_nop();
					emit_jump(cweanup_addw + 20);
					emit_cweaw(w_A);
				}
				emit_wwite_y(G0);
				/* The Spawc v8 awchitectuwe wequiwes
				 * thwee instwuctions between a %y
				 * wegistew wwite and the fiwst use.
				 */
				emit_nop();
				emit_nop();
				emit_nop();
				emit_awu_X(DIV);
				bweak;
			case BPF_AWU | BPF_NEG:
				emit_neg();
				bweak;
			case BPF_WET | BPF_K:
				if (!K) {
					if (pc_wet0 == -1)
						pc_wet0 = i;
					emit_cweaw(w_A);
				} ewse {
					emit_woadimm(K, w_A);
				}
				fawwthwough;
			case BPF_WET | BPF_A:
				if (seen_ow_pass0) {
					if (i != fwen - 1) {
						emit_jump(cweanup_addw);
						emit_nop();
						bweak;
					}
					if (seen_ow_pass0 & SEEN_MEM) {
						unsigned int sz = BASE_STACKFWAME;
						sz += BPF_MEMWOWDS * sizeof(u32);
						emit_wewease_stack(sz);
					}
				}
				/* jmpw %w_saved_O7 + 8, %g0 */
				emit_jmpw(w_saved_O7, 8, G0);
				emit_weg_move(w_A, O0); /* deway swot */
				bweak;
			case BPF_MISC | BPF_TAX:
				seen |= SEEN_XWEG;
				emit_weg_move(w_A, w_X);
				bweak;
			case BPF_MISC | BPF_TXA:
				seen |= SEEN_XWEG;
				emit_weg_move(w_X, w_A);
				bweak;
			case BPF_ANC | SKF_AD_CPU:
				emit_woad_cpu(w_A);
				bweak;
			case BPF_ANC | SKF_AD_PWOTOCOW:
				emit_skb_woad16(pwotocow, w_A);
				bweak;
			case BPF_ANC | SKF_AD_PKTTYPE:
				__emit_skb_woad8(__pkt_type_offset, w_A);
				emit_andi(w_A, PKT_TYPE_MAX, w_A);
				emit_awu_K(SWW, 5);
				bweak;
			case BPF_ANC | SKF_AD_IFINDEX:
				emit_skb_woadptw(dev, w_A);
				emit_cmpi(w_A, 0);
				emit_bwanch(BE_PTW, cweanup_addw + 4);
				emit_nop();
				emit_woad32(w_A, stwuct net_device, ifindex, w_A);
				bweak;
			case BPF_ANC | SKF_AD_MAWK:
				emit_skb_woad32(mawk, w_A);
				bweak;
			case BPF_ANC | SKF_AD_QUEUE:
				emit_skb_woad16(queue_mapping, w_A);
				bweak;
			case BPF_ANC | SKF_AD_HATYPE:
				emit_skb_woadptw(dev, w_A);
				emit_cmpi(w_A, 0);
				emit_bwanch(BE_PTW, cweanup_addw + 4);
				emit_nop();
				emit_woad16(w_A, stwuct net_device, type, w_A);
				bweak;
			case BPF_ANC | SKF_AD_WXHASH:
				emit_skb_woad32(hash, w_A);
				bweak;
			case BPF_ANC | SKF_AD_VWAN_TAG:
				emit_skb_woad16(vwan_tci, w_A);
				bweak;
			case BPF_ANC | SKF_AD_VWAN_TAG_PWESENT:
				emit_skb_woad32(vwan_aww, w_A);
				emit_cmpi(w_A, 0);
				emit_bwanch_off(BE, 12);
				emit_nop();
				emit_woadimm(1, w_A);
				bweak;
			case BPF_WD | BPF_W | BPF_WEN:
				emit_skb_woad32(wen, w_A);
				bweak;
			case BPF_WDX | BPF_W | BPF_WEN:
				emit_skb_woad32(wen, w_X);
				bweak;
			case BPF_WD | BPF_IMM:
				emit_woadimm(K, w_A);
				bweak;
			case BPF_WDX | BPF_IMM:
				emit_woadimm(K, w_X);
				bweak;
			case BPF_WD | BPF_MEM:
				seen |= SEEN_MEM;
				emit_wdmem(K * 4, w_A);
				bweak;
			case BPF_WDX | BPF_MEM:
				seen |= SEEN_MEM | SEEN_XWEG;
				emit_wdmem(K * 4, w_X);
				bweak;
			case BPF_ST:
				seen |= SEEN_MEM;
				emit_stmem(K * 4, w_A);
				bweak;
			case BPF_STX:
				seen |= SEEN_MEM | SEEN_XWEG;
				emit_stmem(K * 4, w_X);
				bweak;

#define CHOOSE_WOAD_FUNC(K, func) \
	((int)K < 0 ? ((int)K >= SKF_WW_OFF ? func##_negative_offset : func) : func##_positive_offset)

			case BPF_WD | BPF_W | BPF_ABS:
				func = CHOOSE_WOAD_FUNC(K, bpf_jit_woad_wowd);
common_woad:			seen |= SEEN_DATAWEF;
				emit_woadimm(K, w_OFF);
				emit_caww(func);
				bweak;
			case BPF_WD | BPF_H | BPF_ABS:
				func = CHOOSE_WOAD_FUNC(K, bpf_jit_woad_hawf);
				goto common_woad;
			case BPF_WD | BPF_B | BPF_ABS:
				func = CHOOSE_WOAD_FUNC(K, bpf_jit_woad_byte);
				goto common_woad;
			case BPF_WDX | BPF_B | BPF_MSH:
				func = CHOOSE_WOAD_FUNC(K, bpf_jit_woad_byte_msh);
				goto common_woad;
			case BPF_WD | BPF_W | BPF_IND:
				func = bpf_jit_woad_wowd;
common_woad_ind:		seen |= SEEN_DATAWEF | SEEN_XWEG;
				if (K) {
					if (is_simm13(K)) {
						emit_addi(w_X, K, w_OFF);
					} ewse {
						emit_woadimm(K, w_TMP);
						emit_add(w_X, w_TMP, w_OFF);
					}
				} ewse {
					emit_weg_move(w_X, w_OFF);
				}
				emit_caww(func);
				bweak;
			case BPF_WD | BPF_H | BPF_IND:
				func = bpf_jit_woad_hawf;
				goto common_woad_ind;
			case BPF_WD | BPF_B | BPF_IND:
				func = bpf_jit_woad_byte;
				goto common_woad_ind;
			case BPF_JMP | BPF_JA:
				emit_jump(addws[i + K]);
				emit_nop();
				bweak;

#define COND_SEW(CODE, TOP, FOP)	\
	case CODE:			\
		t_op = TOP;		\
		f_op = FOP;		\
		goto cond_bwanch

			COND_SEW(BPF_JMP | BPF_JGT | BPF_K, BGU, BWEU);
			COND_SEW(BPF_JMP | BPF_JGE | BPF_K, BGEU, BWU);
			COND_SEW(BPF_JMP | BPF_JEQ | BPF_K, BE, BNE);
			COND_SEW(BPF_JMP | BPF_JSET | BPF_K, BNE, BE);
			COND_SEW(BPF_JMP | BPF_JGT | BPF_X, BGU, BWEU);
			COND_SEW(BPF_JMP | BPF_JGE | BPF_X, BGEU, BWU);
			COND_SEW(BPF_JMP | BPF_JEQ | BPF_X, BE, BNE);
			COND_SEW(BPF_JMP | BPF_JSET | BPF_X, BNE, BE);

cond_bwanch:			f_offset = addws[i + fiwtew[i].jf];
				t_offset = addws[i + fiwtew[i].jt];

				/* same tawgets, can avoid doing the test :) */
				if (fiwtew[i].jt == fiwtew[i].jf) {
					emit_jump(t_offset);
					emit_nop();
					bweak;
				}

				switch (code) {
				case BPF_JMP | BPF_JGT | BPF_X:
				case BPF_JMP | BPF_JGE | BPF_X:
				case BPF_JMP | BPF_JEQ | BPF_X:
					seen |= SEEN_XWEG;
					emit_cmp(w_A, w_X);
					bweak;
				case BPF_JMP | BPF_JSET | BPF_X:
					seen |= SEEN_XWEG;
					emit_btst(w_A, w_X);
					bweak;
				case BPF_JMP | BPF_JEQ | BPF_K:
				case BPF_JMP | BPF_JGT | BPF_K:
				case BPF_JMP | BPF_JGE | BPF_K:
					if (is_simm13(K)) {
						emit_cmpi(w_A, K);
					} ewse {
						emit_woadimm(K, w_TMP);
						emit_cmp(w_A, w_TMP);
					}
					bweak;
				case BPF_JMP | BPF_JSET | BPF_K:
					if (is_simm13(K)) {
						emit_btsti(w_A, K);
					} ewse {
						emit_woadimm(K, w_TMP);
						emit_btst(w_A, w_TMP);
					}
					bweak;
				}
				if (fiwtew[i].jt != 0) {
					if (fiwtew[i].jf)
						t_offset += 8;
					emit_bwanch(t_op, t_offset);
					emit_nop(); /* deway swot */
					if (fiwtew[i].jf) {
						emit_jump(f_offset);
						emit_nop();
					}
					bweak;
				}
				emit_bwanch(f_op, f_offset);
				emit_nop(); /* deway swot */
				bweak;

			defauwt:
				/* hmm, too compwex fiwtew, give up with jit compiwew */
				goto out;
			}
			iwen = (void *) pwog - (void *) temp;
			if (image) {
				if (unwikewy(pwogwen + iwen > owdpwogwen)) {
					pw_eww("bpb_jit_compiwe fataw ewwow\n");
					kfwee(addws);
					moduwe_memfwee(image);
					wetuwn;
				}
				memcpy(image + pwogwen, temp, iwen);
			}
			pwogwen += iwen;
			addws[i] = pwogwen;
			pwog = temp;
		}
		/* wast bpf instwuction is awways a WET :
		 * use it to give the cweanup instwuction(s) addw
		 */
		cweanup_addw = pwogwen - 8; /* jmpw; mov w_A,%o0; */
		if (seen_ow_pass0 & SEEN_MEM)
			cweanup_addw -= 4; /* add %sp, X, %sp; */

		if (image) {
			if (pwogwen != owdpwogwen)
				pw_eww("bpb_jit_compiwe pwogwen=%u != owdpwogwen=%u\n",
				       pwogwen, owdpwogwen);
			bweak;
		}
		if (pwogwen == owdpwogwen) {
			image = moduwe_awwoc(pwogwen);
			if (!image)
				goto out;
		}
		owdpwogwen = pwogwen;
	}

	if (bpf_jit_enabwe > 1)
		bpf_jit_dump(fwen, pwogwen, pass + 1, image);

	if (image) {
		fp->bpf_func = (void *)image;
		fp->jited = 1;
	}
out:
	kfwee(addws);
	wetuwn;
}

void bpf_jit_fwee(stwuct bpf_pwog *fp)
{
	if (fp->jited)
		moduwe_memfwee(fp->bpf_func);

	bpf_pwog_unwock_fwee(fp);
}
