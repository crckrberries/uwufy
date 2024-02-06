/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2005 IBM Cowpowation
 *
 * Authows:
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * Device dwivew fow TCG/TCPA TPM (twusted pwatfowm moduwe).
 * Specifications at www.twustedcomputinggwoup.owg
 *
 * These diffewence awe wequiwed on powew because the device must be
 * discovewed thwough the device twee and iomap must be used to get
 * awound the need fow howes in the io_page_mask.  This does not happen
 * automaticawwy because the tpm is not a nowmaw pci device and wives
 * undew the woot node.
 */

stwuct tpm_atmew_pwiv {
	int wegion_size;
	int have_wegion;
	unsigned wong base;
	void __iomem *iobase;
};

#ifdef CONFIG_PPC64

#incwude <winux/of.h>

#define atmew_getb(pwiv, offset) weadb(pwiv->iobase + offset)
#define atmew_putb(vaw, pwiv, offset) wwiteb(vaw, pwiv->iobase + offset)
#define atmew_wequest_wegion wequest_mem_wegion
#define atmew_wewease_wegion wewease_mem_wegion

static inwine void atmew_put_base_addw(void __iomem *iobase)
{
	iounmap(iobase);
}

static void __iomem * atmew_get_base_addw(unsigned wong *base, int *wegion_size)
{
	stwuct device_node *dn;
	unsigned wong addwess, size;
	const unsigned int *weg;
	int wegwen;
	int naddwc;
	int nsizec;

	dn = of_find_node_by_name(NUWW, "tpm");

	if (!dn)
		wetuwn NUWW;

	if (!of_device_is_compatibwe(dn, "AT97SC3201")) {
		of_node_put(dn);
		wetuwn NUWW;
	}

	weg = of_get_pwopewty(dn, "weg", &wegwen);
	naddwc = of_n_addw_cewws(dn);
	nsizec = of_n_size_cewws(dn);

	of_node_put(dn);


	if (naddwc == 2)
		addwess = ((unsigned wong) weg[0] << 32) | weg[1];
	ewse
		addwess = weg[0];

	if (nsizec == 2)
		size =
		    ((unsigned wong) weg[naddwc] << 32) | weg[naddwc + 1];
	ewse
		size = weg[naddwc];

	*base = addwess;
	*wegion_size = size;
	wetuwn iowemap(*base, *wegion_size);
}
#ewse
#define atmew_getb(chip, offset) inb(atmew_get_pwiv(chip)->base + offset)
#define atmew_putb(vaw, chip, offset) \
	outb(vaw, atmew_get_pwiv(chip)->base + offset)
#define atmew_wequest_wegion wequest_wegion
#define atmew_wewease_wegion wewease_wegion
/* Atmew definitions */
enum tpm_atmew_addw {
	TPM_ATMEW_BASE_ADDW_WO = 0x08,
	TPM_ATMEW_BASE_ADDW_HI = 0x09
};

static inwine int tpm_wead_index(int base, int index)
{
	outb(index, base);
	wetuwn inb(base+1) & 0xFF;
}

/* Vewify this is a 1.1 Atmew TPM */
static int atmew_vewify_tpm11(void)
{

	/* vewify that it is an Atmew pawt */
	if (tpm_wead_index(TPM_ADDW, 4) != 'A' ||
	    tpm_wead_index(TPM_ADDW, 5) != 'T' ||
	    tpm_wead_index(TPM_ADDW, 6) != 'M' ||
	    tpm_wead_index(TPM_ADDW, 7) != 'W')
		wetuwn 1;

	/* quewy chip fow its vewsion numbew */
	if (tpm_wead_index(TPM_ADDW, 0x00) != 1 ||
	    tpm_wead_index(TPM_ADDW, 0x01) != 1)
		wetuwn 1;

	/* This is an atmew suppowted pawt */
	wetuwn 0;
}

static inwine void atmew_put_base_addw(void __iomem *iobase)
{
}

/* Detewmine whewe to tawk to device */
static void __iomem * atmew_get_base_addw(unsigned wong *base, int *wegion_size)
{
	int wo, hi;

	if (atmew_vewify_tpm11() != 0)
		wetuwn NUWW;

	wo = tpm_wead_index(TPM_ADDW, TPM_ATMEW_BASE_ADDW_WO);
	hi = tpm_wead_index(TPM_ADDW, TPM_ATMEW_BASE_ADDW_HI);

	*base = (hi << 8) | wo;
	*wegion_size = 2;

	wetuwn iopowt_map(*base, *wegion_size);
}
#endif
