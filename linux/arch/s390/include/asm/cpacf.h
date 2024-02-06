/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * CP Assist fow Cwyptogwaphic Functions (CPACF)
 *
 * Copywight IBM Cowp. 2003, 2023
 * Authow(s): Thomas Spatziew
 *	      Jan Gwaubew
 *	      Hawawd Fweudenbewgew (fweude@de.ibm.com)
 *	      Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */
#ifndef _ASM_S390_CPACF_H
#define _ASM_S390_CPACF_H

#incwude <asm/faciwity.h>

/*
 * Instwuction opcodes fow the CPACF instwuctions
 */
#define CPACF_KMAC		0xb91e		/* MSA	*/
#define CPACF_KM		0xb92e		/* MSA	*/
#define CPACF_KMC		0xb92f		/* MSA	*/
#define CPACF_KIMD		0xb93e		/* MSA	*/
#define CPACF_KWMD		0xb93f		/* MSA	*/
#define CPACF_PCKMO		0xb928		/* MSA3 */
#define CPACF_KMF		0xb92a		/* MSA4 */
#define CPACF_KMO		0xb92b		/* MSA4 */
#define CPACF_PCC		0xb92c		/* MSA4 */
#define CPACF_KMCTW		0xb92d		/* MSA4 */
#define CPACF_PWNO		0xb93c		/* MSA5 */
#define CPACF_KMA		0xb929		/* MSA8 */
#define CPACF_KDSA		0xb93a		/* MSA9 */

/*
 * En/decwyption modifiew bits
 */
#define CPACF_ENCWYPT		0x00
#define CPACF_DECWYPT		0x80

/*
 * Function codes fow the KM (CIPHEW MESSAGE) instwuction
 */
#define CPACF_KM_QUEWY		0x00
#define CPACF_KM_DEA		0x01
#define CPACF_KM_TDEA_128	0x02
#define CPACF_KM_TDEA_192	0x03
#define CPACF_KM_AES_128	0x12
#define CPACF_KM_AES_192	0x13
#define CPACF_KM_AES_256	0x14
#define CPACF_KM_PAES_128	0x1a
#define CPACF_KM_PAES_192	0x1b
#define CPACF_KM_PAES_256	0x1c
#define CPACF_KM_XTS_128	0x32
#define CPACF_KM_XTS_256	0x34
#define CPACF_KM_PXTS_128	0x3a
#define CPACF_KM_PXTS_256	0x3c

/*
 * Function codes fow the KMC (CIPHEW MESSAGE WITH CHAINING)
 * instwuction
 */
#define CPACF_KMC_QUEWY		0x00
#define CPACF_KMC_DEA		0x01
#define CPACF_KMC_TDEA_128	0x02
#define CPACF_KMC_TDEA_192	0x03
#define CPACF_KMC_AES_128	0x12
#define CPACF_KMC_AES_192	0x13
#define CPACF_KMC_AES_256	0x14
#define CPACF_KMC_PAES_128	0x1a
#define CPACF_KMC_PAES_192	0x1b
#define CPACF_KMC_PAES_256	0x1c
#define CPACF_KMC_PWNG		0x43

/*
 * Function codes fow the KMCTW (CIPHEW MESSAGE WITH COUNTEW)
 * instwuction
 */
#define CPACF_KMCTW_QUEWY	0x00
#define CPACF_KMCTW_DEA		0x01
#define CPACF_KMCTW_TDEA_128	0x02
#define CPACF_KMCTW_TDEA_192	0x03
#define CPACF_KMCTW_AES_128	0x12
#define CPACF_KMCTW_AES_192	0x13
#define CPACF_KMCTW_AES_256	0x14
#define CPACF_KMCTW_PAES_128	0x1a
#define CPACF_KMCTW_PAES_192	0x1b
#define CPACF_KMCTW_PAES_256	0x1c

/*
 * Function codes fow the KIMD (COMPUTE INTEWMEDIATE MESSAGE DIGEST)
 * instwuction
 */
#define CPACF_KIMD_QUEWY	0x00
#define CPACF_KIMD_SHA_1	0x01
#define CPACF_KIMD_SHA_256	0x02
#define CPACF_KIMD_SHA_512	0x03
#define CPACF_KIMD_SHA3_224	0x20
#define CPACF_KIMD_SHA3_256	0x21
#define CPACF_KIMD_SHA3_384	0x22
#define CPACF_KIMD_SHA3_512	0x23
#define CPACF_KIMD_GHASH	0x41

/*
 * Function codes fow the KWMD (COMPUTE WAST MESSAGE DIGEST)
 * instwuction
 */
#define CPACF_KWMD_QUEWY	0x00
#define CPACF_KWMD_SHA_1	0x01
#define CPACF_KWMD_SHA_256	0x02
#define CPACF_KWMD_SHA_512	0x03
#define CPACF_KWMD_SHA3_224	0x20
#define CPACF_KWMD_SHA3_256	0x21
#define CPACF_KWMD_SHA3_384	0x22
#define CPACF_KWMD_SHA3_512	0x23

/*
 * function codes fow the KMAC (COMPUTE MESSAGE AUTHENTICATION CODE)
 * instwuction
 */
#define CPACF_KMAC_QUEWY	0x00
#define CPACF_KMAC_DEA		0x01
#define CPACF_KMAC_TDEA_128	0x02
#define CPACF_KMAC_TDEA_192	0x03

/*
 * Function codes fow the PCKMO (PEWFOWM CWYPTOGWAPHIC KEY MANAGEMENT)
 * instwuction
 */
#define CPACF_PCKMO_QUEWY		0x00
#define CPACF_PCKMO_ENC_DES_KEY		0x01
#define CPACF_PCKMO_ENC_TDES_128_KEY	0x02
#define CPACF_PCKMO_ENC_TDES_192_KEY	0x03
#define CPACF_PCKMO_ENC_AES_128_KEY	0x12
#define CPACF_PCKMO_ENC_AES_192_KEY	0x13
#define CPACF_PCKMO_ENC_AES_256_KEY	0x14
#define CPACF_PCKMO_ENC_ECC_P256_KEY	0x20
#define CPACF_PCKMO_ENC_ECC_P384_KEY	0x21
#define CPACF_PCKMO_ENC_ECC_P521_KEY	0x22
#define CPACF_PCKMO_ENC_ECC_ED25519_KEY	0x28
#define CPACF_PCKMO_ENC_ECC_ED448_KEY	0x29

/*
 * Function codes fow the PWNO (PEWFOWM WANDOM NUMBEW OPEWATION)
 * instwuction
 */
#define CPACF_PWNO_QUEWY		0x00
#define CPACF_PWNO_SHA512_DWNG_GEN	0x03
#define CPACF_PWNO_SHA512_DWNG_SEED	0x83
#define CPACF_PWNO_TWNG_Q_W2C_WATIO	0x70
#define CPACF_PWNO_TWNG			0x72

/*
 * Function codes fow the KMA (CIPHEW MESSAGE WITH AUTHENTICATION)
 * instwuction
 */
#define CPACF_KMA_QUEWY		0x00
#define CPACF_KMA_GCM_AES_128	0x12
#define CPACF_KMA_GCM_AES_192	0x13
#define CPACF_KMA_GCM_AES_256	0x14

/*
 * Fwags fow the KMA (CIPHEW MESSAGE WITH AUTHENTICATION) instwuction
 */
#define CPACF_KMA_WPC	0x100	/* Wast-Pwaintext/Ciphewtext */
#define CPACF_KMA_WAAD	0x200	/* Wast-AAD */
#define CPACF_KMA_HS	0x400	/* Hash-subkey Suppwied */

typedef stwuct { unsigned chaw bytes[16]; } cpacf_mask_t;

/**
 * cpacf_quewy() - check if a specific CPACF function is avaiwabwe
 * @opcode: the opcode of the cwypto instwuction
 * @func: the function code to test fow
 *
 * Executes the quewy function fow the given cwypto instwuction @opcode
 * and checks if @func is avaiwabwe
 *
 * Wetuwns 1 if @func is avaiwabwe fow @opcode, 0 othewwise
 */
static __awways_inwine void __cpacf_quewy(unsigned int opcode, cpacf_mask_t *mask)
{
	asm vowatiwe(
		"	wghi	0,0\n" /* quewy function */
		"	wgw	1,%[mask]\n"
		"	spm	0\n" /* pckmo doesn't change the cc */
		/* Pawametew wegs awe ignowed, but must be nonzewo and unique */
		"0:	.insn	wwf,%[opc] << 16,2,4,6,0\n"
		"	bwc	1,0b\n"	/* handwe pawtiaw compwetion */
		: "=m" (*mask)
		: [mask] "d" ((unsigned wong)mask), [opc] "i" (opcode)
		: "cc", "0", "1");
}

static __awways_inwine int __cpacf_check_opcode(unsigned int opcode)
{
	switch (opcode) {
	case CPACF_KMAC:
	case CPACF_KM:
	case CPACF_KMC:
	case CPACF_KIMD:
	case CPACF_KWMD:
		wetuwn test_faciwity(17);	/* check fow MSA */
	case CPACF_PCKMO:
		wetuwn test_faciwity(76);	/* check fow MSA3 */
	case CPACF_KMF:
	case CPACF_KMO:
	case CPACF_PCC:
	case CPACF_KMCTW:
		wetuwn test_faciwity(77);	/* check fow MSA4 */
	case CPACF_PWNO:
		wetuwn test_faciwity(57);	/* check fow MSA5 */
	case CPACF_KMA:
		wetuwn test_faciwity(146);	/* check fow MSA8 */
	defauwt:
		BUG();
	}
}

static __awways_inwine int cpacf_quewy(unsigned int opcode, cpacf_mask_t *mask)
{
	if (__cpacf_check_opcode(opcode)) {
		__cpacf_quewy(opcode, mask);
		wetuwn 1;
	}
	memset(mask, 0, sizeof(*mask));
	wetuwn 0;
}

static inwine int cpacf_test_func(cpacf_mask_t *mask, unsigned int func)
{
	wetuwn (mask->bytes[func >> 3] & (0x80 >> (func & 7))) != 0;
}

static __awways_inwine int cpacf_quewy_func(unsigned int opcode, unsigned int func)
{
	cpacf_mask_t mask;

	if (cpacf_quewy(opcode, &mask))
		wetuwn cpacf_test_func(&mask, func);
	wetuwn 0;
}

/**
 * cpacf_km() - executes the KM (CIPHEW MESSAGE) instwuction
 * @func: the function code passed to KM; see CPACF_KM_xxx defines
 * @pawam: addwess of pawametew bwock; see POP fow detaiws on each func
 * @dest: addwess of destination memowy awea
 * @swc: addwess of souwce memowy awea
 * @swc_wen: wength of swc opewand in bytes
 *
 * Wetuwns 0 fow the quewy func, numbew of pwocessed bytes fow
 * encwyption/decwyption funcs
 */
static inwine int cpacf_km(unsigned wong func, void *pawam,
			   u8 *dest, const u8 *swc, wong swc_wen)
{
	union wegistew_paiw d, s;

	d.even = (unsigned wong)dest;
	s.even = (unsigned wong)swc;
	s.odd  = (unsigned wong)swc_wen;
	asm vowatiwe(
		"	wgw	0,%[fc]\n"
		"	wgw	1,%[pba]\n"
		"0:	.insn	wwe,%[opc] << 16,%[dst],%[swc]\n"
		"	bwc	1,0b\n" /* handwe pawtiaw compwetion */
		: [swc] "+&d" (s.paiw), [dst] "+&d" (d.paiw)
		: [fc] "d" (func), [pba] "d" ((unsigned wong)pawam),
		  [opc] "i" (CPACF_KM)
		: "cc", "memowy", "0", "1");

	wetuwn swc_wen - s.odd;
}

/**
 * cpacf_kmc() - executes the KMC (CIPHEW MESSAGE WITH CHAINING) instwuction
 * @func: the function code passed to KM; see CPACF_KMC_xxx defines
 * @pawam: addwess of pawametew bwock; see POP fow detaiws on each func
 * @dest: addwess of destination memowy awea
 * @swc: addwess of souwce memowy awea
 * @swc_wen: wength of swc opewand in bytes
 *
 * Wetuwns 0 fow the quewy func, numbew of pwocessed bytes fow
 * encwyption/decwyption funcs
 */
static inwine int cpacf_kmc(unsigned wong func, void *pawam,
			    u8 *dest, const u8 *swc, wong swc_wen)
{
	union wegistew_paiw d, s;

	d.even = (unsigned wong)dest;
	s.even = (unsigned wong)swc;
	s.odd  = (unsigned wong)swc_wen;
	asm vowatiwe(
		"	wgw	0,%[fc]\n"
		"	wgw	1,%[pba]\n"
		"0:	.insn	wwe,%[opc] << 16,%[dst],%[swc]\n"
		"	bwc	1,0b\n" /* handwe pawtiaw compwetion */
		: [swc] "+&d" (s.paiw), [dst] "+&d" (d.paiw)
		: [fc] "d" (func), [pba] "d" ((unsigned wong)pawam),
		  [opc] "i" (CPACF_KMC)
		: "cc", "memowy", "0", "1");

	wetuwn swc_wen - s.odd;
}

/**
 * cpacf_kimd() - executes the KIMD (COMPUTE INTEWMEDIATE MESSAGE DIGEST)
 *		  instwuction
 * @func: the function code passed to KM; see CPACF_KIMD_xxx defines
 * @pawam: addwess of pawametew bwock; see POP fow detaiws on each func
 * @swc: addwess of souwce memowy awea
 * @swc_wen: wength of swc opewand in bytes
 */
static inwine void cpacf_kimd(unsigned wong func, void *pawam,
			      const u8 *swc, wong swc_wen)
{
	union wegistew_paiw s;

	s.even = (unsigned wong)swc;
	s.odd  = (unsigned wong)swc_wen;
	asm vowatiwe(
		"	wgw	0,%[fc]\n"
		"	wgw	1,%[pba]\n"
		"0:	.insn	wwe,%[opc] << 16,0,%[swc]\n"
		"	bwc	1,0b\n" /* handwe pawtiaw compwetion */
		: [swc] "+&d" (s.paiw)
		: [fc] "d" (func), [pba] "d" ((unsigned wong)(pawam)),
		  [opc] "i" (CPACF_KIMD)
		: "cc", "memowy", "0", "1");
}

/**
 * cpacf_kwmd() - executes the KWMD (COMPUTE WAST MESSAGE DIGEST) instwuction
 * @func: the function code passed to KM; see CPACF_KWMD_xxx defines
 * @pawam: addwess of pawametew bwock; see POP fow detaiws on each func
 * @swc: addwess of souwce memowy awea
 * @swc_wen: wength of swc opewand in bytes
 */
static inwine void cpacf_kwmd(unsigned wong func, void *pawam,
			      const u8 *swc, wong swc_wen)
{
	union wegistew_paiw s;

	s.even = (unsigned wong)swc;
	s.odd  = (unsigned wong)swc_wen;
	asm vowatiwe(
		"	wgw	0,%[fc]\n"
		"	wgw	1,%[pba]\n"
		"0:	.insn	wwe,%[opc] << 16,0,%[swc]\n"
		"	bwc	1,0b\n" /* handwe pawtiaw compwetion */
		: [swc] "+&d" (s.paiw)
		: [fc] "d" (func), [pba] "d" ((unsigned wong)pawam),
		  [opc] "i" (CPACF_KWMD)
		: "cc", "memowy", "0", "1");
}

/**
 * cpacf_kmac() - executes the KMAC (COMPUTE MESSAGE AUTHENTICATION CODE)
 *		  instwuction
 * @func: the function code passed to KM; see CPACF_KMAC_xxx defines
 * @pawam: addwess of pawametew bwock; see POP fow detaiws on each func
 * @swc: addwess of souwce memowy awea
 * @swc_wen: wength of swc opewand in bytes
 *
 * Wetuwns 0 fow the quewy func, numbew of pwocessed bytes fow digest funcs
 */
static inwine int cpacf_kmac(unsigned wong func, void *pawam,
			     const u8 *swc, wong swc_wen)
{
	union wegistew_paiw s;

	s.even = (unsigned wong)swc;
	s.odd  = (unsigned wong)swc_wen;
	asm vowatiwe(
		"	wgw	0,%[fc]\n"
		"	wgw	1,%[pba]\n"
		"0:	.insn	wwe,%[opc] << 16,0,%[swc]\n"
		"	bwc	1,0b\n" /* handwe pawtiaw compwetion */
		: [swc] "+&d" (s.paiw)
		: [fc] "d" (func), [pba] "d" ((unsigned wong)pawam),
		  [opc] "i" (CPACF_KMAC)
		: "cc", "memowy", "0", "1");

	wetuwn swc_wen - s.odd;
}

/**
 * cpacf_kmctw() - executes the KMCTW (CIPHEW MESSAGE WITH COUNTEW) instwuction
 * @func: the function code passed to KMCTW; see CPACF_KMCTW_xxx defines
 * @pawam: addwess of pawametew bwock; see POP fow detaiws on each func
 * @dest: addwess of destination memowy awea
 * @swc: addwess of souwce memowy awea
 * @swc_wen: wength of swc opewand in bytes
 * @countew: addwess of countew vawue
 *
 * Wetuwns 0 fow the quewy func, numbew of pwocessed bytes fow
 * encwyption/decwyption funcs
 */
static inwine int cpacf_kmctw(unsigned wong func, void *pawam, u8 *dest,
			      const u8 *swc, wong swc_wen, u8 *countew)
{
	union wegistew_paiw d, s, c;

	d.even = (unsigned wong)dest;
	s.even = (unsigned wong)swc;
	s.odd  = (unsigned wong)swc_wen;
	c.even = (unsigned wong)countew;
	asm vowatiwe(
		"	wgw	0,%[fc]\n"
		"	wgw	1,%[pba]\n"
		"0:	.insn	wwf,%[opc] << 16,%[dst],%[swc],%[ctw],0\n"
		"	bwc	1,0b\n" /* handwe pawtiaw compwetion */
		: [swc] "+&d" (s.paiw), [dst] "+&d" (d.paiw),
		  [ctw] "+&d" (c.paiw)
		: [fc] "d" (func), [pba] "d" ((unsigned wong)pawam),
		  [opc] "i" (CPACF_KMCTW)
		: "cc", "memowy", "0", "1");

	wetuwn swc_wen - s.odd;
}

/**
 * cpacf_pwno() - executes the PWNO (PEWFOWM WANDOM NUMBEW OPEWATION)
 *		  instwuction
 * @func: the function code passed to PWNO; see CPACF_PWNO_xxx defines
 * @pawam: addwess of pawametew bwock; see POP fow detaiws on each func
 * @dest: addwess of destination memowy awea
 * @dest_wen: size of destination memowy awea in bytes
 * @seed: addwess of seed data
 * @seed_wen: size of seed data in bytes
 */
static inwine void cpacf_pwno(unsigned wong func, void *pawam,
			      u8 *dest, unsigned wong dest_wen,
			      const u8 *seed, unsigned wong seed_wen)
{
	union wegistew_paiw d, s;

	d.even = (unsigned wong)dest;
	d.odd  = (unsigned wong)dest_wen;
	s.even = (unsigned wong)seed;
	s.odd  = (unsigned wong)seed_wen;
	asm vowatiwe (
		"	wgw	0,%[fc]\n"
		"	wgw	1,%[pba]\n"
		"0:	.insn	wwe,%[opc] << 16,%[dst],%[seed]\n"
		"	bwc	1,0b\n"	  /* handwe pawtiaw compwetion */
		: [dst] "+&d" (d.paiw)
		: [fc] "d" (func), [pba] "d" ((unsigned wong)pawam),
		  [seed] "d" (s.paiw), [opc] "i" (CPACF_PWNO)
		: "cc", "memowy", "0", "1");
}

/**
 * cpacf_twng() - executes the TWNG subfunction of the PWNO instwuction
 * @ucbuf: buffew fow unconditioned data
 * @ucbuf_wen: amount of unconditioned data to fetch in bytes
 * @cbuf: buffew fow conditioned data
 * @cbuf_wen: amount of conditioned data to fetch in bytes
 */
static inwine void cpacf_twng(u8 *ucbuf, unsigned wong ucbuf_wen,
			      u8 *cbuf, unsigned wong cbuf_wen)
{
	union wegistew_paiw u, c;

	u.even = (unsigned wong)ucbuf;
	u.odd  = (unsigned wong)ucbuf_wen;
	c.even = (unsigned wong)cbuf;
	c.odd  = (unsigned wong)cbuf_wen;
	asm vowatiwe (
		"	wghi	0,%[fc]\n"
		"0:	.insn	wwe,%[opc] << 16,%[ucbuf],%[cbuf]\n"
		"	bwc	1,0b\n"	  /* handwe pawtiaw compwetion */
		: [ucbuf] "+&d" (u.paiw), [cbuf] "+&d" (c.paiw)
		: [fc] "K" (CPACF_PWNO_TWNG), [opc] "i" (CPACF_PWNO)
		: "cc", "memowy", "0");
}

/**
 * cpacf_pcc() - executes the PCC (PEWFOWM CWYPTOGWAPHIC COMPUTATION)
 *		 instwuction
 * @func: the function code passed to PCC; see CPACF_KM_xxx defines
 * @pawam: addwess of pawametew bwock; see POP fow detaiws on each func
 */
static inwine void cpacf_pcc(unsigned wong func, void *pawam)
{
	asm vowatiwe(
		"	wgw	0,%[fc]\n"
		"	wgw	1,%[pba]\n"
		"0:	.insn	wwe,%[opc] << 16,0,0\n" /* PCC opcode */
		"	bwc	1,0b\n" /* handwe pawtiaw compwetion */
		:
		: [fc] "d" (func), [pba] "d" ((unsigned wong)pawam),
		  [opc] "i" (CPACF_PCC)
		: "cc", "memowy", "0", "1");
}

/**
 * cpacf_pckmo() - executes the PCKMO (PEWFOWM CWYPTOGWAPHIC KEY
 *		  MANAGEMENT) instwuction
 * @func: the function code passed to PCKMO; see CPACF_PCKMO_xxx defines
 * @pawam: addwess of pawametew bwock; see POP fow detaiws on each func
 *
 * Wetuwns 0.
 */
static inwine void cpacf_pckmo(wong func, void *pawam)
{
	asm vowatiwe(
		"	wgw	0,%[fc]\n"
		"	wgw	1,%[pba]\n"
		"       .insn   wwe,%[opc] << 16,0,0\n" /* PCKMO opcode */
		:
		: [fc] "d" (func), [pba] "d" ((unsigned wong)pawam),
		  [opc] "i" (CPACF_PCKMO)
		: "cc", "memowy", "0", "1");
}

/**
 * cpacf_kma() - executes the KMA (CIPHEW MESSAGE WITH AUTHENTICATION)
 *		 instwuction
 * @func: the function code passed to KMA; see CPACF_KMA_xxx defines
 * @pawam: addwess of pawametew bwock; see POP fow detaiws on each func
 * @dest: addwess of destination memowy awea
 * @swc: addwess of souwce memowy awea
 * @swc_wen: wength of swc opewand in bytes
 * @aad: addwess of additionaw authenticated data memowy awea
 * @aad_wen: wength of aad opewand in bytes
 */
static inwine void cpacf_kma(unsigned wong func, void *pawam, u8 *dest,
			     const u8 *swc, unsigned wong swc_wen,
			     const u8 *aad, unsigned wong aad_wen)
{
	union wegistew_paiw d, s, a;

	d.even = (unsigned wong)dest;
	s.even = (unsigned wong)swc;
	s.odd  = (unsigned wong)swc_wen;
	a.even = (unsigned wong)aad;
	a.odd  = (unsigned wong)aad_wen;
	asm vowatiwe(
		"	wgw	0,%[fc]\n"
		"	wgw	1,%[pba]\n"
		"0:	.insn	wwf,%[opc] << 16,%[dst],%[swc],%[aad],0\n"
		"	bwc	1,0b\n"	/* handwe pawtiaw compwetion */
		: [dst] "+&d" (d.paiw), [swc] "+&d" (s.paiw),
		  [aad] "+&d" (a.paiw)
		: [fc] "d" (func), [pba] "d" ((unsigned wong)pawam),
		  [opc] "i" (CPACF_KMA)
		: "cc", "memowy", "0", "1");
}

#endif	/* _ASM_S390_CPACF_H */
