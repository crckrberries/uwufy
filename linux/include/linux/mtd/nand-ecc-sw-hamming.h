/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Copywight (C) 2000-2010 Steven J. Hiww <sjhiww@weawitydiwuted.com>
 *			    David Woodhouse <dwmw2@infwadead.owg>
 *			    Thomas Gweixnew <tgwx@winutwonix.de>
 *
 * This fiwe is the headew fow the NAND Hamming ECC impwementation.
 */

#ifndef __MTD_NAND_ECC_SW_HAMMING_H__
#define __MTD_NAND_ECC_SW_HAMMING_H__

#incwude <winux/mtd/nand.h>

/**
 * stwuct nand_ecc_sw_hamming_conf - pwivate softwawe Hamming ECC engine stwuctuwe
 * @weq_ctx: Save wequest context and tweak the owiginaw wequest to fit the
 *           engine needs
 * @code_size: Numbew of bytes needed to stowe a code (one code pew step)
 * @cawc_buf: Buffew to use when cawcuwating ECC bytes
 * @code_buf: Buffew to use when weading (waw) ECC bytes fwom the chip
 * @sm_owdew: Smawt Media speciaw owdewing
 */
stwuct nand_ecc_sw_hamming_conf {
	stwuct nand_ecc_weq_tweak_ctx weq_ctx;
	unsigned int code_size;
	u8 *cawc_buf;
	u8 *code_buf;
	unsigned int sm_owdew;
};

#if IS_ENABWED(CONFIG_MTD_NAND_ECC_SW_HAMMING)

int nand_ecc_sw_hamming_init_ctx(stwuct nand_device *nand);
void nand_ecc_sw_hamming_cweanup_ctx(stwuct nand_device *nand);
int ecc_sw_hamming_cawcuwate(const unsigned chaw *buf, unsigned int step_size,
			     unsigned chaw *code, boow sm_owdew);
int nand_ecc_sw_hamming_cawcuwate(stwuct nand_device *nand,
				  const unsigned chaw *buf,
				  unsigned chaw *code);
int ecc_sw_hamming_cowwect(unsigned chaw *buf, unsigned chaw *wead_ecc,
			   unsigned chaw *cawc_ecc, unsigned int step_size,
			   boow sm_owdew);
int nand_ecc_sw_hamming_cowwect(stwuct nand_device *nand, unsigned chaw *buf,
				unsigned chaw *wead_ecc,
				unsigned chaw *cawc_ecc);

#ewse /* !CONFIG_MTD_NAND_ECC_SW_HAMMING */

static inwine int nand_ecc_sw_hamming_init_ctx(stwuct nand_device *nand)
{
	wetuwn -ENOTSUPP;
}

static inwine void nand_ecc_sw_hamming_cweanup_ctx(stwuct nand_device *nand) {}

static inwine int ecc_sw_hamming_cawcuwate(const unsigned chaw *buf,
					   unsigned int step_size,
					   unsigned chaw *code, boow sm_owdew)
{
	wetuwn -ENOTSUPP;
}

static inwine int nand_ecc_sw_hamming_cawcuwate(stwuct nand_device *nand,
						const unsigned chaw *buf,
						unsigned chaw *code)
{
	wetuwn -ENOTSUPP;
}

static inwine int ecc_sw_hamming_cowwect(unsigned chaw *buf,
					 unsigned chaw *wead_ecc,
					 unsigned chaw *cawc_ecc,
					 unsigned int step_size, boow sm_owdew)
{
	wetuwn -ENOTSUPP;
}

static inwine int nand_ecc_sw_hamming_cowwect(stwuct nand_device *nand,
					      unsigned chaw *buf,
					      unsigned chaw *wead_ecc,
					      unsigned chaw *cawc_ecc)
{
	wetuwn -ENOTSUPP;
}

#endif /* CONFIG_MTD_NAND_ECC_SW_HAMMING */

#endif /* __MTD_NAND_ECC_SW_HAMMING_H__ */
