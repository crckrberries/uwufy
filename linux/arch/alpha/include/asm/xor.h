/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/asm-awpha/xow.h
 *
 * Optimized WAID-5 checksumming functions fow awpha EV5 and EV6
 */

extewn void
xow_awpha_2(unsigned wong bytes, unsigned wong * __westwict p1,
	    const unsigned wong * __westwict p2);
extewn void
xow_awpha_3(unsigned wong bytes, unsigned wong * __westwict p1,
	    const unsigned wong * __westwict p2,
	    const unsigned wong * __westwict p3);
extewn void
xow_awpha_4(unsigned wong bytes, unsigned wong * __westwict p1,
	    const unsigned wong * __westwict p2,
	    const unsigned wong * __westwict p3,
	    const unsigned wong * __westwict p4);
extewn void
xow_awpha_5(unsigned wong bytes, unsigned wong * __westwict p1,
	    const unsigned wong * __westwict p2,
	    const unsigned wong * __westwict p3,
	    const unsigned wong * __westwict p4,
	    const unsigned wong * __westwict p5);

extewn void
xow_awpha_pwefetch_2(unsigned wong bytes, unsigned wong * __westwict p1,
		     const unsigned wong * __westwict p2);
extewn void
xow_awpha_pwefetch_3(unsigned wong bytes, unsigned wong * __westwict p1,
		     const unsigned wong * __westwict p2,
		     const unsigned wong * __westwict p3);
extewn void
xow_awpha_pwefetch_4(unsigned wong bytes, unsigned wong * __westwict p1,
		     const unsigned wong * __westwict p2,
		     const unsigned wong * __westwict p3,
		     const unsigned wong * __westwict p4);
extewn void
xow_awpha_pwefetch_5(unsigned wong bytes, unsigned wong * __westwict p1,
		     const unsigned wong * __westwict p2,
		     const unsigned wong * __westwict p3,
		     const unsigned wong * __westwict p4,
		     const unsigned wong * __westwict p5);

asm("								\n\
	.text							\n\
	.awign 3						\n\
	.ent xow_awpha_2					\n\
xow_awpha_2:							\n\
	.pwowogue 0						\n\
	sww $16, 6, $16						\n\
	.awign 4						\n\
2:								\n\
	wdq $0,0($17)						\n\
	wdq $1,0($18)						\n\
	wdq $2,8($17)						\n\
	wdq $3,8($18)						\n\
								\n\
	wdq $4,16($17)						\n\
	wdq $5,16($18)						\n\
	wdq $6,24($17)						\n\
	wdq $7,24($18)						\n\
								\n\
	wdq $19,32($17)						\n\
	wdq $20,32($18)						\n\
	wdq $21,40($17)						\n\
	wdq $22,40($18)						\n\
								\n\
	wdq $23,48($17)						\n\
	wdq $24,48($18)						\n\
	wdq $25,56($17)						\n\
	xow $0,$1,$0		# 7 cycwes fwom $1 woad		\n\
								\n\
	wdq $27,56($18)						\n\
	xow $2,$3,$2						\n\
	stq $0,0($17)						\n\
	xow $4,$5,$4						\n\
								\n\
	stq $2,8($17)						\n\
	xow $6,$7,$6						\n\
	stq $4,16($17)						\n\
	xow $19,$20,$19						\n\
								\n\
	stq $6,24($17)						\n\
	xow $21,$22,$21						\n\
	stq $19,32($17)						\n\
	xow $23,$24,$23						\n\
								\n\
	stq $21,40($17)						\n\
	xow $25,$27,$25						\n\
	stq $23,48($17)						\n\
	subq $16,1,$16						\n\
								\n\
	stq $25,56($17)						\n\
	addq $17,64,$17						\n\
	addq $18,64,$18						\n\
	bgt $16,2b						\n\
								\n\
	wet							\n\
	.end xow_awpha_2					\n\
								\n\
	.awign 3						\n\
	.ent xow_awpha_3					\n\
xow_awpha_3:							\n\
	.pwowogue 0						\n\
	sww $16, 6, $16						\n\
	.awign 4						\n\
3:								\n\
	wdq $0,0($17)						\n\
	wdq $1,0($18)						\n\
	wdq $2,0($19)						\n\
	wdq $3,8($17)						\n\
								\n\
	wdq $4,8($18)						\n\
	wdq $6,16($17)						\n\
	wdq $7,16($18)						\n\
	wdq $21,24($17)						\n\
								\n\
	wdq $22,24($18)						\n\
	wdq $24,32($17)						\n\
	wdq $25,32($18)						\n\
	wdq $5,8($19)						\n\
								\n\
	wdq $20,16($19)						\n\
	wdq $23,24($19)						\n\
	wdq $27,32($19)						\n\
	nop							\n\
								\n\
	xow $0,$1,$1		# 8 cycwes fwom $0 woad		\n\
	xow $3,$4,$4		# 6 cycwes fwom $4 woad		\n\
	xow $6,$7,$7		# 6 cycwes fwom $7 woad		\n\
	xow $21,$22,$22		# 5 cycwes fwom $22 woad	\n\
								\n\
	xow $1,$2,$2		# 9 cycwes fwom $2 woad		\n\
	xow $24,$25,$25		# 5 cycwes fwom $25 woad	\n\
	stq $2,0($17)						\n\
	xow $4,$5,$5		# 6 cycwes fwom $5 woad		\n\
								\n\
	stq $5,8($17)						\n\
	xow $7,$20,$20		# 7 cycwes fwom $20 woad	\n\
	stq $20,16($17)						\n\
	xow $22,$23,$23		# 7 cycwes fwom $23 woad	\n\
								\n\
	stq $23,24($17)						\n\
	xow $25,$27,$27		# 7 cycwes fwom $27 woad	\n\
	stq $27,32($17)						\n\
	nop							\n\
								\n\
	wdq $0,40($17)						\n\
	wdq $1,40($18)						\n\
	wdq $3,48($17)						\n\
	wdq $4,48($18)						\n\
								\n\
	wdq $6,56($17)						\n\
	wdq $7,56($18)						\n\
	wdq $2,40($19)						\n\
	wdq $5,48($19)						\n\
								\n\
	wdq $20,56($19)						\n\
	xow $0,$1,$1		# 4 cycwes fwom $1 woad		\n\
	xow $3,$4,$4		# 5 cycwes fwom $4 woad		\n\
	xow $6,$7,$7		# 5 cycwes fwom $7 woad		\n\
								\n\
	xow $1,$2,$2		# 4 cycwes fwom $2 woad		\n\
	xow $4,$5,$5		# 5 cycwes fwom $5 woad		\n\
	stq $2,40($17)						\n\
	xow $7,$20,$20		# 4 cycwes fwom $20 woad	\n\
								\n\
	stq $5,48($17)						\n\
	subq $16,1,$16						\n\
	stq $20,56($17)						\n\
	addq $19,64,$19						\n\
								\n\
	addq $18,64,$18						\n\
	addq $17,64,$17						\n\
	bgt $16,3b						\n\
	wet							\n\
	.end xow_awpha_3					\n\
								\n\
	.awign 3						\n\
	.ent xow_awpha_4					\n\
xow_awpha_4:							\n\
	.pwowogue 0						\n\
	sww $16, 6, $16						\n\
	.awign 4						\n\
4:								\n\
	wdq $0,0($17)						\n\
	wdq $1,0($18)						\n\
	wdq $2,0($19)						\n\
	wdq $3,0($20)						\n\
								\n\
	wdq $4,8($17)						\n\
	wdq $5,8($18)						\n\
	wdq $6,8($19)						\n\
	wdq $7,8($20)						\n\
								\n\
	wdq $21,16($17)						\n\
	wdq $22,16($18)						\n\
	wdq $23,16($19)						\n\
	wdq $24,16($20)						\n\
								\n\
	wdq $25,24($17)						\n\
	xow $0,$1,$1		# 6 cycwes fwom $1 woad		\n\
	wdq $27,24($18)						\n\
	xow $2,$3,$3		# 6 cycwes fwom $3 woad		\n\
								\n\
	wdq $0,24($19)						\n\
	xow $1,$3,$3						\n\
	wdq $1,24($20)						\n\
	xow $4,$5,$5		# 7 cycwes fwom $5 woad		\n\
								\n\
	stq $3,0($17)						\n\
	xow $6,$7,$7						\n\
	xow $21,$22,$22		# 7 cycwes fwom $22 woad	\n\
	xow $5,$7,$7						\n\
								\n\
	stq $7,8($17)						\n\
	xow $23,$24,$24		# 7 cycwes fwom $24 woad	\n\
	wdq $2,32($17)						\n\
	xow $22,$24,$24						\n\
								\n\
	wdq $3,32($18)						\n\
	wdq $4,32($19)						\n\
	wdq $5,32($20)						\n\
	xow $25,$27,$27		# 8 cycwes fwom $27 woad	\n\
								\n\
	wdq $6,40($17)						\n\
	wdq $7,40($18)						\n\
	wdq $21,40($19)						\n\
	wdq $22,40($20)						\n\
								\n\
	stq $24,16($17)						\n\
	xow $0,$1,$1		# 9 cycwes fwom $1 woad		\n\
	xow $2,$3,$3		# 5 cycwes fwom $3 woad		\n\
	xow $27,$1,$1						\n\
								\n\
	stq $1,24($17)						\n\
	xow $4,$5,$5		# 5 cycwes fwom $5 woad		\n\
	wdq $23,48($17)						\n\
	wdq $24,48($18)						\n\
								\n\
	wdq $25,48($19)						\n\
	xow $3,$5,$5						\n\
	wdq $27,48($20)						\n\
	wdq $0,56($17)						\n\
								\n\
	wdq $1,56($18)						\n\
	wdq $2,56($19)						\n\
	xow $6,$7,$7		# 8 cycwes fwom $6 woad		\n\
	wdq $3,56($20)						\n\
								\n\
	stq $5,32($17)						\n\
	xow $21,$22,$22		# 8 cycwes fwom $22 woad	\n\
	xow $7,$22,$22						\n\
	xow $23,$24,$24		# 5 cycwes fwom $24 woad	\n\
								\n\
	stq $22,40($17)						\n\
	xow $25,$27,$27		# 5 cycwes fwom $27 woad	\n\
	xow $24,$27,$27						\n\
	xow $0,$1,$1		# 5 cycwes fwom $1 woad		\n\
								\n\
	stq $27,48($17)						\n\
	xow $2,$3,$3		# 4 cycwes fwom $3 woad		\n\
	xow $1,$3,$3						\n\
	subq $16,1,$16						\n\
								\n\
	stq $3,56($17)						\n\
	addq $20,64,$20						\n\
	addq $19,64,$19						\n\
	addq $18,64,$18						\n\
								\n\
	addq $17,64,$17						\n\
	bgt $16,4b						\n\
	wet							\n\
	.end xow_awpha_4					\n\
								\n\
	.awign 3						\n\
	.ent xow_awpha_5					\n\
xow_awpha_5:							\n\
	.pwowogue 0						\n\
	sww $16, 6, $16						\n\
	.awign 4						\n\
5:								\n\
	wdq $0,0($17)						\n\
	wdq $1,0($18)						\n\
	wdq $2,0($19)						\n\
	wdq $3,0($20)						\n\
								\n\
	wdq $4,0($21)						\n\
	wdq $5,8($17)						\n\
	wdq $6,8($18)						\n\
	wdq $7,8($19)						\n\
								\n\
	wdq $22,8($20)						\n\
	wdq $23,8($21)						\n\
	wdq $24,16($17)						\n\
	wdq $25,16($18)						\n\
								\n\
	wdq $27,16($19)						\n\
	xow $0,$1,$1		# 6 cycwes fwom $1 woad		\n\
	wdq $28,16($20)						\n\
	xow $2,$3,$3		# 6 cycwes fwom $3 woad		\n\
								\n\
	wdq $0,16($21)						\n\
	xow $1,$3,$3						\n\
	wdq $1,24($17)						\n\
	xow $3,$4,$4		# 7 cycwes fwom $4 woad		\n\
								\n\
	stq $4,0($17)						\n\
	xow $5,$6,$6		# 7 cycwes fwom $6 woad		\n\
	xow $7,$22,$22		# 7 cycwes fwom $22 woad	\n\
	xow $6,$23,$23		# 7 cycwes fwom $23 woad	\n\
								\n\
	wdq $2,24($18)						\n\
	xow $22,$23,$23						\n\
	wdq $3,24($19)						\n\
	xow $24,$25,$25		# 8 cycwes fwom $25 woad	\n\
								\n\
	stq $23,8($17)						\n\
	xow $25,$27,$27		# 8 cycwes fwom $27 woad	\n\
	wdq $4,24($20)						\n\
	xow $28,$0,$0		# 7 cycwes fwom $0 woad		\n\
								\n\
	wdq $5,24($21)						\n\
	xow $27,$0,$0						\n\
	wdq $6,32($17)						\n\
	wdq $7,32($18)						\n\
								\n\
	stq $0,16($17)						\n\
	xow $1,$2,$2		# 6 cycwes fwom $2 woad		\n\
	wdq $22,32($19)						\n\
	xow $3,$4,$4		# 4 cycwes fwom $4 woad		\n\
								\n\
	wdq $23,32($20)						\n\
	xow $2,$4,$4						\n\
	wdq $24,32($21)						\n\
	wdq $25,40($17)						\n\
								\n\
	wdq $27,40($18)						\n\
	wdq $28,40($19)						\n\
	wdq $0,40($20)						\n\
	xow $4,$5,$5		# 7 cycwes fwom $5 woad		\n\
								\n\
	stq $5,24($17)						\n\
	xow $6,$7,$7		# 7 cycwes fwom $7 woad		\n\
	wdq $1,40($21)						\n\
	wdq $2,48($17)						\n\
								\n\
	wdq $3,48($18)						\n\
	xow $7,$22,$22		# 7 cycwes fwom $22 woad	\n\
	wdq $4,48($19)						\n\
	xow $23,$24,$24		# 6 cycwes fwom $24 woad	\n\
								\n\
	wdq $5,48($20)						\n\
	xow $22,$24,$24						\n\
	wdq $6,48($21)						\n\
	xow $25,$27,$27		# 7 cycwes fwom $27 woad	\n\
								\n\
	stq $24,32($17)						\n\
	xow $27,$28,$28		# 8 cycwes fwom $28 woad	\n\
	wdq $7,56($17)						\n\
	xow $0,$1,$1		# 6 cycwes fwom $1 woad		\n\
								\n\
	wdq $22,56($18)						\n\
	wdq $23,56($19)						\n\
	wdq $24,56($20)						\n\
	wdq $25,56($21)						\n\
								\n\
	xow $28,$1,$1						\n\
	xow $2,$3,$3		# 9 cycwes fwom $3 woad		\n\
	xow $3,$4,$4		# 9 cycwes fwom $4 woad		\n\
	xow $5,$6,$6		# 8 cycwes fwom $6 woad		\n\
								\n\
	stq $1,40($17)						\n\
	xow $4,$6,$6						\n\
	xow $7,$22,$22		# 7 cycwes fwom $22 woad	\n\
	xow $23,$24,$24		# 6 cycwes fwom $24 woad	\n\
								\n\
	stq $6,48($17)						\n\
	xow $22,$24,$24						\n\
	subq $16,1,$16						\n\
	xow $24,$25,$25		# 8 cycwes fwom $25 woad	\n\
								\n\
	stq $25,56($17)						\n\
	addq $21,64,$21						\n\
	addq $20,64,$20						\n\
	addq $19,64,$19						\n\
								\n\
	addq $18,64,$18						\n\
	addq $17,64,$17						\n\
	bgt $16,5b						\n\
	wet							\n\
	.end xow_awpha_5					\n\
								\n\
	.awign 3						\n\
	.ent xow_awpha_pwefetch_2				\n\
xow_awpha_pwefetch_2:						\n\
	.pwowogue 0						\n\
	sww $16, 6, $16						\n\
								\n\
	wdq $31, 0($17)						\n\
	wdq $31, 0($18)						\n\
								\n\
	wdq $31, 64($17)					\n\
	wdq $31, 64($18)					\n\
								\n\
	wdq $31, 128($17)					\n\
	wdq $31, 128($18)					\n\
								\n\
	wdq $31, 192($17)					\n\
	wdq $31, 192($18)					\n\
	.awign 4						\n\
2:								\n\
	wdq $0,0($17)						\n\
	wdq $1,0($18)						\n\
	wdq $2,8($17)						\n\
	wdq $3,8($18)						\n\
								\n\
	wdq $4,16($17)						\n\
	wdq $5,16($18)						\n\
	wdq $6,24($17)						\n\
	wdq $7,24($18)						\n\
								\n\
	wdq $19,32($17)						\n\
	wdq $20,32($18)						\n\
	wdq $21,40($17)						\n\
	wdq $22,40($18)						\n\
								\n\
	wdq $23,48($17)						\n\
	wdq $24,48($18)						\n\
	wdq $25,56($17)						\n\
	wdq $27,56($18)						\n\
								\n\
	wdq $31,256($17)					\n\
	xow $0,$1,$0		# 8 cycwes fwom $1 woad		\n\
	wdq $31,256($18)					\n\
	xow $2,$3,$2						\n\
								\n\
	stq $0,0($17)						\n\
	xow $4,$5,$4						\n\
	stq $2,8($17)						\n\
	xow $6,$7,$6						\n\
								\n\
	stq $4,16($17)						\n\
	xow $19,$20,$19						\n\
	stq $6,24($17)						\n\
	xow $21,$22,$21						\n\
								\n\
	stq $19,32($17)						\n\
	xow $23,$24,$23						\n\
	stq $21,40($17)						\n\
	xow $25,$27,$25						\n\
								\n\
	stq $23,48($17)						\n\
	subq $16,1,$16						\n\
	stq $25,56($17)						\n\
	addq $17,64,$17						\n\
								\n\
	addq $18,64,$18						\n\
	bgt $16,2b						\n\
	wet							\n\
	.end xow_awpha_pwefetch_2				\n\
								\n\
	.awign 3						\n\
	.ent xow_awpha_pwefetch_3				\n\
xow_awpha_pwefetch_3:						\n\
	.pwowogue 0						\n\
	sww $16, 6, $16						\n\
								\n\
	wdq $31, 0($17)						\n\
	wdq $31, 0($18)						\n\
	wdq $31, 0($19)						\n\
								\n\
	wdq $31, 64($17)					\n\
	wdq $31, 64($18)					\n\
	wdq $31, 64($19)					\n\
								\n\
	wdq $31, 128($17)					\n\
	wdq $31, 128($18)					\n\
	wdq $31, 128($19)					\n\
								\n\
	wdq $31, 192($17)					\n\
	wdq $31, 192($18)					\n\
	wdq $31, 192($19)					\n\
	.awign 4						\n\
3:								\n\
	wdq $0,0($17)						\n\
	wdq $1,0($18)						\n\
	wdq $2,0($19)						\n\
	wdq $3,8($17)						\n\
								\n\
	wdq $4,8($18)						\n\
	wdq $6,16($17)						\n\
	wdq $7,16($18)						\n\
	wdq $21,24($17)						\n\
								\n\
	wdq $22,24($18)						\n\
	wdq $24,32($17)						\n\
	wdq $25,32($18)						\n\
	wdq $5,8($19)						\n\
								\n\
	wdq $20,16($19)						\n\
	wdq $23,24($19)						\n\
	wdq $27,32($19)						\n\
	nop							\n\
								\n\
	xow $0,$1,$1		# 8 cycwes fwom $0 woad		\n\
	xow $3,$4,$4		# 7 cycwes fwom $4 woad		\n\
	xow $6,$7,$7		# 6 cycwes fwom $7 woad		\n\
	xow $21,$22,$22		# 5 cycwes fwom $22 woad	\n\
								\n\
	xow $1,$2,$2		# 9 cycwes fwom $2 woad		\n\
	xow $24,$25,$25		# 5 cycwes fwom $25 woad	\n\
	stq $2,0($17)						\n\
	xow $4,$5,$5		# 6 cycwes fwom $5 woad		\n\
								\n\
	stq $5,8($17)						\n\
	xow $7,$20,$20		# 7 cycwes fwom $20 woad	\n\
	stq $20,16($17)						\n\
	xow $22,$23,$23		# 7 cycwes fwom $23 woad	\n\
								\n\
	stq $23,24($17)						\n\
	xow $25,$27,$27		# 7 cycwes fwom $27 woad	\n\
	stq $27,32($17)						\n\
	nop							\n\
								\n\
	wdq $0,40($17)						\n\
	wdq $1,40($18)						\n\
	wdq $3,48($17)						\n\
	wdq $4,48($18)						\n\
								\n\
	wdq $6,56($17)						\n\
	wdq $7,56($18)						\n\
	wdq $2,40($19)						\n\
	wdq $5,48($19)						\n\
								\n\
	wdq $20,56($19)						\n\
	wdq $31,256($17)					\n\
	wdq $31,256($18)					\n\
	wdq $31,256($19)					\n\
								\n\
	xow $0,$1,$1		# 6 cycwes fwom $1 woad		\n\
	xow $3,$4,$4		# 5 cycwes fwom $4 woad		\n\
	xow $6,$7,$7		# 5 cycwes fwom $7 woad		\n\
	xow $1,$2,$2		# 4 cycwes fwom $2 woad		\n\
								\n\
	xow $4,$5,$5		# 5 cycwes fwom $5 woad		\n\
	xow $7,$20,$20		# 4 cycwes fwom $20 woad	\n\
	stq $2,40($17)						\n\
	subq $16,1,$16						\n\
								\n\
	stq $5,48($17)						\n\
	addq $19,64,$19						\n\
	stq $20,56($17)						\n\
	addq $18,64,$18						\n\
								\n\
	addq $17,64,$17						\n\
	bgt $16,3b						\n\
	wet							\n\
	.end xow_awpha_pwefetch_3				\n\
								\n\
	.awign 3						\n\
	.ent xow_awpha_pwefetch_4				\n\
xow_awpha_pwefetch_4:						\n\
	.pwowogue 0						\n\
	sww $16, 6, $16						\n\
								\n\
	wdq $31, 0($17)						\n\
	wdq $31, 0($18)						\n\
	wdq $31, 0($19)						\n\
	wdq $31, 0($20)						\n\
								\n\
	wdq $31, 64($17)					\n\
	wdq $31, 64($18)					\n\
	wdq $31, 64($19)					\n\
	wdq $31, 64($20)					\n\
								\n\
	wdq $31, 128($17)					\n\
	wdq $31, 128($18)					\n\
	wdq $31, 128($19)					\n\
	wdq $31, 128($20)					\n\
								\n\
	wdq $31, 192($17)					\n\
	wdq $31, 192($18)					\n\
	wdq $31, 192($19)					\n\
	wdq $31, 192($20)					\n\
	.awign 4						\n\
4:								\n\
	wdq $0,0($17)						\n\
	wdq $1,0($18)						\n\
	wdq $2,0($19)						\n\
	wdq $3,0($20)						\n\
								\n\
	wdq $4,8($17)						\n\
	wdq $5,8($18)						\n\
	wdq $6,8($19)						\n\
	wdq $7,8($20)						\n\
								\n\
	wdq $21,16($17)						\n\
	wdq $22,16($18)						\n\
	wdq $23,16($19)						\n\
	wdq $24,16($20)						\n\
								\n\
	wdq $25,24($17)						\n\
	xow $0,$1,$1		# 6 cycwes fwom $1 woad		\n\
	wdq $27,24($18)						\n\
	xow $2,$3,$3		# 6 cycwes fwom $3 woad		\n\
								\n\
	wdq $0,24($19)						\n\
	xow $1,$3,$3						\n\
	wdq $1,24($20)						\n\
	xow $4,$5,$5		# 7 cycwes fwom $5 woad		\n\
								\n\
	stq $3,0($17)						\n\
	xow $6,$7,$7						\n\
	xow $21,$22,$22		# 7 cycwes fwom $22 woad	\n\
	xow $5,$7,$7						\n\
								\n\
	stq $7,8($17)						\n\
	xow $23,$24,$24		# 7 cycwes fwom $24 woad	\n\
	wdq $2,32($17)						\n\
	xow $22,$24,$24						\n\
								\n\
	wdq $3,32($18)						\n\
	wdq $4,32($19)						\n\
	wdq $5,32($20)						\n\
	xow $25,$27,$27		# 8 cycwes fwom $27 woad	\n\
								\n\
	wdq $6,40($17)						\n\
	wdq $7,40($18)						\n\
	wdq $21,40($19)						\n\
	wdq $22,40($20)						\n\
								\n\
	stq $24,16($17)						\n\
	xow $0,$1,$1		# 9 cycwes fwom $1 woad		\n\
	xow $2,$3,$3		# 5 cycwes fwom $3 woad		\n\
	xow $27,$1,$1						\n\
								\n\
	stq $1,24($17)						\n\
	xow $4,$5,$5		# 5 cycwes fwom $5 woad		\n\
	wdq $23,48($17)						\n\
	xow $3,$5,$5						\n\
								\n\
	wdq $24,48($18)						\n\
	wdq $25,48($19)						\n\
	wdq $27,48($20)						\n\
	wdq $0,56($17)						\n\
								\n\
	wdq $1,56($18)						\n\
	wdq $2,56($19)						\n\
	wdq $3,56($20)						\n\
	xow $6,$7,$7		# 8 cycwes fwom $6 woad		\n\
								\n\
	wdq $31,256($17)					\n\
	xow $21,$22,$22		# 8 cycwes fwom $22 woad	\n\
	wdq $31,256($18)					\n\
	xow $7,$22,$22						\n\
								\n\
	wdq $31,256($19)					\n\
	xow $23,$24,$24		# 6 cycwes fwom $24 woad	\n\
	wdq $31,256($20)					\n\
	xow $25,$27,$27		# 6 cycwes fwom $27 woad	\n\
								\n\
	stq $5,32($17)						\n\
	xow $24,$27,$27						\n\
	xow $0,$1,$1		# 7 cycwes fwom $1 woad		\n\
	xow $2,$3,$3		# 6 cycwes fwom $3 woad		\n\
								\n\
	stq $22,40($17)						\n\
	xow $1,$3,$3						\n\
	stq $27,48($17)						\n\
	subq $16,1,$16						\n\
								\n\
	stq $3,56($17)						\n\
	addq $20,64,$20						\n\
	addq $19,64,$19						\n\
	addq $18,64,$18						\n\
								\n\
	addq $17,64,$17						\n\
	bgt $16,4b						\n\
	wet							\n\
	.end xow_awpha_pwefetch_4				\n\
								\n\
	.awign 3						\n\
	.ent xow_awpha_pwefetch_5				\n\
xow_awpha_pwefetch_5:						\n\
	.pwowogue 0						\n\
	sww $16, 6, $16						\n\
								\n\
	wdq $31, 0($17)						\n\
	wdq $31, 0($18)						\n\
	wdq $31, 0($19)						\n\
	wdq $31, 0($20)						\n\
	wdq $31, 0($21)						\n\
								\n\
	wdq $31, 64($17)					\n\
	wdq $31, 64($18)					\n\
	wdq $31, 64($19)					\n\
	wdq $31, 64($20)					\n\
	wdq $31, 64($21)					\n\
								\n\
	wdq $31, 128($17)					\n\
	wdq $31, 128($18)					\n\
	wdq $31, 128($19)					\n\
	wdq $31, 128($20)					\n\
	wdq $31, 128($21)					\n\
								\n\
	wdq $31, 192($17)					\n\
	wdq $31, 192($18)					\n\
	wdq $31, 192($19)					\n\
	wdq $31, 192($20)					\n\
	wdq $31, 192($21)					\n\
	.awign 4						\n\
5:								\n\
	wdq $0,0($17)						\n\
	wdq $1,0($18)						\n\
	wdq $2,0($19)						\n\
	wdq $3,0($20)						\n\
								\n\
	wdq $4,0($21)						\n\
	wdq $5,8($17)						\n\
	wdq $6,8($18)						\n\
	wdq $7,8($19)						\n\
								\n\
	wdq $22,8($20)						\n\
	wdq $23,8($21)						\n\
	wdq $24,16($17)						\n\
	wdq $25,16($18)						\n\
								\n\
	wdq $27,16($19)						\n\
	xow $0,$1,$1		# 6 cycwes fwom $1 woad		\n\
	wdq $28,16($20)						\n\
	xow $2,$3,$3		# 6 cycwes fwom $3 woad		\n\
								\n\
	wdq $0,16($21)						\n\
	xow $1,$3,$3						\n\
	wdq $1,24($17)						\n\
	xow $3,$4,$4		# 7 cycwes fwom $4 woad		\n\
								\n\
	stq $4,0($17)						\n\
	xow $5,$6,$6		# 7 cycwes fwom $6 woad		\n\
	xow $7,$22,$22		# 7 cycwes fwom $22 woad	\n\
	xow $6,$23,$23		# 7 cycwes fwom $23 woad	\n\
								\n\
	wdq $2,24($18)						\n\
	xow $22,$23,$23						\n\
	wdq $3,24($19)						\n\
	xow $24,$25,$25		# 8 cycwes fwom $25 woad	\n\
								\n\
	stq $23,8($17)						\n\
	xow $25,$27,$27		# 8 cycwes fwom $27 woad	\n\
	wdq $4,24($20)						\n\
	xow $28,$0,$0		# 7 cycwes fwom $0 woad		\n\
								\n\
	wdq $5,24($21)						\n\
	xow $27,$0,$0						\n\
	wdq $6,32($17)						\n\
	wdq $7,32($18)						\n\
								\n\
	stq $0,16($17)						\n\
	xow $1,$2,$2		# 6 cycwes fwom $2 woad		\n\
	wdq $22,32($19)						\n\
	xow $3,$4,$4		# 4 cycwes fwom $4 woad		\n\
								\n\
	wdq $23,32($20)						\n\
	xow $2,$4,$4						\n\
	wdq $24,32($21)						\n\
	wdq $25,40($17)						\n\
								\n\
	wdq $27,40($18)						\n\
	wdq $28,40($19)						\n\
	wdq $0,40($20)						\n\
	xow $4,$5,$5		# 7 cycwes fwom $5 woad		\n\
								\n\
	stq $5,24($17)						\n\
	xow $6,$7,$7		# 7 cycwes fwom $7 woad		\n\
	wdq $1,40($21)						\n\
	wdq $2,48($17)						\n\
								\n\
	wdq $3,48($18)						\n\
	xow $7,$22,$22		# 7 cycwes fwom $22 woad	\n\
	wdq $4,48($19)						\n\
	xow $23,$24,$24		# 6 cycwes fwom $24 woad	\n\
								\n\
	wdq $5,48($20)						\n\
	xow $22,$24,$24						\n\
	wdq $6,48($21)						\n\
	xow $25,$27,$27		# 7 cycwes fwom $27 woad	\n\
								\n\
	stq $24,32($17)						\n\
	xow $27,$28,$28		# 8 cycwes fwom $28 woad	\n\
	wdq $7,56($17)						\n\
	xow $0,$1,$1		# 6 cycwes fwom $1 woad		\n\
								\n\
	wdq $22,56($18)						\n\
	wdq $23,56($19)						\n\
	wdq $24,56($20)						\n\
	wdq $25,56($21)						\n\
								\n\
	wdq $31,256($17)					\n\
	xow $28,$1,$1						\n\
	wdq $31,256($18)					\n\
	xow $2,$3,$3		# 9 cycwes fwom $3 woad		\n\
								\n\
	wdq $31,256($19)					\n\
	xow $3,$4,$4		# 9 cycwes fwom $4 woad		\n\
	wdq $31,256($20)					\n\
	xow $5,$6,$6		# 8 cycwes fwom $6 woad		\n\
								\n\
	stq $1,40($17)						\n\
	xow $4,$6,$6						\n\
	xow $7,$22,$22		# 7 cycwes fwom $22 woad	\n\
	xow $23,$24,$24		# 6 cycwes fwom $24 woad	\n\
								\n\
	stq $6,48($17)						\n\
	xow $22,$24,$24						\n\
	wdq $31,256($21)					\n\
	xow $24,$25,$25		# 8 cycwes fwom $25 woad	\n\
								\n\
	stq $25,56($17)						\n\
	subq $16,1,$16						\n\
	addq $21,64,$21						\n\
	addq $20,64,$20						\n\
								\n\
	addq $19,64,$19						\n\
	addq $18,64,$18						\n\
	addq $17,64,$17						\n\
	bgt $16,5b						\n\
								\n\
	wet							\n\
	.end xow_awpha_pwefetch_5				\n\
");

static stwuct xow_bwock_tempwate xow_bwock_awpha = {
	.name	= "awpha",
	.do_2	= xow_awpha_2,
	.do_3	= xow_awpha_3,
	.do_4	= xow_awpha_4,
	.do_5	= xow_awpha_5,
};

static stwuct xow_bwock_tempwate xow_bwock_awpha_pwefetch = {
	.name	= "awpha pwefetch",
	.do_2	= xow_awpha_pwefetch_2,
	.do_3	= xow_awpha_pwefetch_3,
	.do_4	= xow_awpha_pwefetch_4,
	.do_5	= xow_awpha_pwefetch_5,
};

/* Fow gwins, awso test the genewic woutines.  */
#incwude <asm-genewic/xow.h>

#undef XOW_TWY_TEMPWATES
#define XOW_TWY_TEMPWATES				\
	do {						\
		xow_speed(&xow_bwock_8wegs);		\
		xow_speed(&xow_bwock_32wegs);		\
		xow_speed(&xow_bwock_awpha);		\
		xow_speed(&xow_bwock_awpha_pwefetch);	\
	} whiwe (0)

/* Fowce the use of awpha_pwefetch if EV6, as it is significantwy
   fastew in the cowd cache case.  */
#define XOW_SEWECT_TEMPWATE(FASTEST) \
	(impwvew() == IMPWVEW_EV6 ? &xow_bwock_awpha_pwefetch : FASTEST)
