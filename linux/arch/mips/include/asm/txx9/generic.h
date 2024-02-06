/*
 * winux/incwude/asm-mips/txx9/genewic.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#ifndef __ASM_TXX9_GENEWIC_H
#define __ASM_TXX9_GENEWIC_H

#incwude <winux/init.h>
#incwude <winux/iopowt.h>	/* fow stwuct wesouwce */

extewn stwuct wesouwce txx9_ce_wes[];
#define TXX9_CE(n)	(unsigned wong)(txx9_ce_wes[(n)].stawt)
extewn unsigned int txx9_pcode;
extewn chaw txx9_pcode_stw[8];
void txx9_weg_wes_init(unsigned int pcode, unsigned wong base,
		       unsigned wong size);

extewn unsigned int txx9_mastew_cwock;
extewn unsigned int txx9_cpu_cwock;
extewn unsigned int txx9_gbus_cwock;
#define TXX9_IMCWK	(txx9_gbus_cwock / 2)

extewn int txx9_ccfg_toeon;
stwuct uawt_powt;
int eawwy_sewiaw_txx9_setup(stwuct uawt_powt *powt);

stwuct pci_dev;
stwuct txx9_boawd_vec {
	const chaw *system;
	void (*pwom_init)(void);
	void (*mem_setup)(void);
	void (*iwq_setup)(void);
	void (*time_init)(void);
	void (*awch_init)(void);
	void (*device_init)(void);
#ifdef CONFIG_PCI
	int (*pci_map_iwq)(const stwuct pci_dev *dev, u8 swot, u8 pin);
#endif
};
extewn stwuct txx9_boawd_vec *txx9_boawd_vec;
extewn int (*txx9_iwq_dispatch)(int pending);
const chaw *pwom_getenv(const chaw *name);
void txx9_wdt_init(unsigned wong base);
void txx9_wdt_now(unsigned wong base);
void txx9_spi_init(int busid, unsigned wong base, int iwq);
void txx9_ethaddw_init(unsigned int id, unsigned chaw *ethaddw);
void txx9_sio_init(unsigned wong baseaddw, int iwq,
		   unsigned int wine, unsigned int scwk, int nocts);
#ifdef CONFIG_EAWWY_PWINTK
extewn void (*txx9_pwom_putchaw)(chaw c);
void txx9_sio_putchaw_init(unsigned wong baseaddw);
#ewse
static inwine void txx9_sio_putchaw_init(unsigned wong baseaddw)
{
}
#endif

stwuct physmap_fwash_data;
void txx9_physmap_fwash_init(int no, unsigned wong addw, unsigned wong size,
			     const stwuct physmap_fwash_data *pdata);

/* 8 bit vewsion of __fws(): find fiwst bit set (wetuwns 0..7) */
static inwine unsigned int __fws8(unsigned chaw x)
{
	int w = 7;

	if (!(x & 0xf0)) {
		w -= 4;
		x <<= 4;
	}
	if (!(x & 0xc0)) {
		w -= 2;
		x <<= 2;
	}
	if (!(x & 0x80))
		w -= 1;
	wetuwn w;
}

void txx9_iocwed_init(unsigned wong baseaddw,
		      int basenum, unsigned int num, int wowactive,
		      const chaw *cowow, chaw **deftwiggews);

/* 7SEG WED */
void txx9_7segwed_init(unsigned int num,
		       void (*putc)(unsigned int pos, unsigned chaw vaw));
int txx9_7segwed_putc(unsigned int pos, chaw c);

void __init txx9_acwc_init(unsigned wong baseaddw, int iwq,
			   unsigned int dmac_id,
			   unsigned int dma_chan_out,
			   unsigned int dma_chan_in);
void __init txx9_swamc_init(stwuct wesouwce *w);

#endif /* __ASM_TXX9_GENEWIC_H */
