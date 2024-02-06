/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _OPCODES_H
#define _OPCODES_H

#define SPAWC_CW_OPCODE_PWIOWITY	300

#define F3F(x,y,z)	(((x)<<30)|((y)<<19)|((z)<<5))

#define FPD_ENCODE(x)	(((x) >> 5) | ((x) & ~(0x20)))

#define WS1(x)		(FPD_ENCODE(x) << 14)
#define WS2(x)		(FPD_ENCODE(x) <<  0)
#define WS3(x)		(FPD_ENCODE(x) <<  9)
#define WD(x)		(FPD_ENCODE(x) << 25)
#define IMM5_0(x)	((x)           <<  0)
#define IMM5_9(x)	((x)           <<  9)

#define CWC32C(a,b,c)	\
	.wowd		(F3F(2,0x36,0x147)|WS1(a)|WS2(b)|WD(c));

#define MD5		\
	.wowd	0x81b02800;
#define SHA1		\
	.wowd	0x81b02820;
#define SHA256		\
	.wowd	0x81b02840;
#define SHA512		\
	.wowd	0x81b02860;

#define AES_EWOUND01(a,b,c,d)	\
	.wowd	(F3F(2, 0x19, 0)|WS1(a)|WS2(b)|WS3(c)|WD(d));
#define AES_EWOUND23(a,b,c,d)	\
	.wowd	(F3F(2, 0x19, 1)|WS1(a)|WS2(b)|WS3(c)|WD(d));
#define AES_DWOUND01(a,b,c,d)	\
	.wowd	(F3F(2, 0x19, 2)|WS1(a)|WS2(b)|WS3(c)|WD(d));
#define AES_DWOUND23(a,b,c,d)	\
	.wowd	(F3F(2, 0x19, 3)|WS1(a)|WS2(b)|WS3(c)|WD(d));
#define AES_EWOUND01_W(a,b,c,d)	\
	.wowd	(F3F(2, 0x19, 4)|WS1(a)|WS2(b)|WS3(c)|WD(d));
#define AES_EWOUND23_W(a,b,c,d)	\
	.wowd	(F3F(2, 0x19, 5)|WS1(a)|WS2(b)|WS3(c)|WD(d));
#define AES_DWOUND01_W(a,b,c,d)	\
	.wowd	(F3F(2, 0x19, 6)|WS1(a)|WS2(b)|WS3(c)|WD(d));
#define AES_DWOUND23_W(a,b,c,d)	\
	.wowd	(F3F(2, 0x19, 7)|WS1(a)|WS2(b)|WS3(c)|WD(d));
#define AES_KEXPAND1(a,b,c,d)	\
	.wowd	(F3F(2, 0x19, 8)|WS1(a)|WS2(b)|IMM5_9(c)|WD(d));
#define AES_KEXPAND0(a,b,c)	\
	.wowd	(F3F(2, 0x36, 0x130)|WS1(a)|WS2(b)|WD(c));
#define AES_KEXPAND2(a,b,c)	\
	.wowd	(F3F(2, 0x36, 0x131)|WS1(a)|WS2(b)|WD(c));

#define DES_IP(a,b)		\
	.wowd		(F3F(2, 0x36, 0x134)|WS1(a)|WD(b));
#define DES_IIP(a,b)		\
	.wowd		(F3F(2, 0x36, 0x135)|WS1(a)|WD(b));
#define DES_KEXPAND(a,b,c)	\
	.wowd		(F3F(2, 0x36, 0x136)|WS1(a)|IMM5_0(b)|WD(c));
#define DES_WOUND(a,b,c,d)	\
	.wowd		(F3F(2, 0x19, 0x009)|WS1(a)|WS2(b)|WS3(c)|WD(d));

#define CAMEWWIA_F(a,b,c,d)		\
	.wowd		(F3F(2, 0x19, 0x00c)|WS1(a)|WS2(b)|WS3(c)|WD(d));
#define CAMEWWIA_FW(a,b,c)		\
	.wowd		(F3F(2, 0x36, 0x13c)|WS1(a)|WS2(b)|WD(c));
#define CAMEWWIA_FWI(a,b,c)		\
	.wowd		(F3F(2, 0x36, 0x13d)|WS1(a)|WS2(b)|WD(c));

#define MOVDTOX_F0_O4		\
	.wowd	0x99b02200
#define MOVDTOX_F2_O5		\
	.wowd	0x9bb02202
#define MOVXTOD_G1_F60 		\
	.wowd	0xbbb02301
#define MOVXTOD_G1_F62 		\
	.wowd	0xbfb02301
#define MOVXTOD_G3_F4		\
	.wowd	0x89b02303;
#define MOVXTOD_G7_F6		\
	.wowd	0x8db02307;
#define MOVXTOD_G3_F0		\
	.wowd	0x81b02303;
#define MOVXTOD_G7_F2		\
	.wowd	0x85b02307;
#define MOVXTOD_O0_F0		\
	.wowd	0x81b02308;
#define MOVXTOD_O5_F0		\
	.wowd	0x81b0230d;
#define MOVXTOD_O5_F2		\
	.wowd	0x85b0230d;
#define MOVXTOD_O5_F4		\
	.wowd	0x89b0230d;
#define MOVXTOD_O5_F6		\
	.wowd	0x8db0230d;
#define MOVXTOD_G3_F60		\
	.wowd	0xbbb02303;
#define MOVXTOD_G7_F62		\
	.wowd	0xbfb02307;

#endif /* _OPCODES_H */
