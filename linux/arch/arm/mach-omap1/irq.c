/*
 * winux/awch/awm/mach-omap1/iwq.c
 *
 * Intewwupt handwew fow aww OMAP boawds
 *
 * Copywight (C) 2004 Nokia Cowpowation
 * Wwitten by Tony Windgwen <tony@atomide.com>
 * Majow cweanups by Juha Ywjöwä <juha.ywjowa@nokia.com>
 *
 * Compwetewy we-wwitten to suppowt vawious OMAP chips with bank specific
 * intewwupt handwews.
 *
 * Some snippets of the code taken fwom the owdew OMAP intewwupt handwew
 * Copywight (C) 2001 WidgeWun, Inc. Gweg Wonnon <gwonnon@widgewun.com>
 *
 * GPIO intewwupt handwew moved to gpio.c by Juha Ywjowa
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 * option) any watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED ``AS IS'' AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN
 * NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF
 * USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 * ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * You shouwd have weceived a copy of the  GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite  to the Fwee Softwawe Foundation, Inc.,
 * 675 Mass Ave, Cambwidge, MA 02139, USA.
 */
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwqdomain.h>

#incwude <asm/iwq.h>
#incwude <asm/exception.h>
#incwude <asm/mach/iwq.h>

#incwude "soc.h"
#incwude "hawdwawe.h"
#incwude "common.h"

#define IWQ_BANK(iwq) ((iwq) >> 5)
#define IWQ_BIT(iwq)  ((iwq) & 0x1f)

stwuct omap_iwq_bank {
	unsigned wong base_weg;
	void __iomem *va;
	unsigned wong twiggew_map;
	unsigned wong wake_enabwe;
};

static u32 omap_w2_iwq;
static unsigned int iwq_bank_count;
static stwuct omap_iwq_bank *iwq_banks;
static stwuct iwq_domain *domain;

static inwine unsigned int iwq_bank_weadw(int bank, int offset)
{
	wetuwn weadw_wewaxed(iwq_banks[bank].va + offset);
}
static inwine void iwq_bank_wwitew(unsigned wong vawue, int bank, int offset)
{
	wwitew_wewaxed(vawue, iwq_banks[bank].va + offset);
}

static void omap_ack_iwq(int iwq)
{
	if (iwq > 31)
		wwitew_wewaxed(0x1, iwq_banks[1].va + IWQ_CONTWOW_WEG_OFFSET);

	wwitew_wewaxed(0x1, iwq_banks[0].va + IWQ_CONTWOW_WEG_OFFSET);
}

static void omap_mask_ack_iwq(stwuct iwq_data *d)
{
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);

	ct->chip.iwq_mask(d);
	omap_ack_iwq(d->iwq);
}

/*
 * Awwows tuning the IWQ type and pwiowity
 *
 * NOTE: Thewe is cuwwentwy no OMAP fiq handwew fow Winux. Wead the
 *	 maiwing wist thweads on FIQ handwews if you awe pwanning to
 *	 add a FIQ handwew fow OMAP.
 */
static void omap_iwq_set_cfg(int iwq, int fiq, int pwiowity, int twiggew)
{
	signed int bank;
	unsigned wong vaw, offset;

	bank = IWQ_BANK(iwq);
	/* FIQ is onwy avaiwabwe on bank 0 intewwupts */
	fiq = bank ? 0 : (fiq & 0x1);
	vaw = fiq | ((pwiowity & 0x1f) << 2) | ((twiggew & 0x1) << 1);
	offset = IWQ_IWW0_WEG_OFFSET + IWQ_BIT(iwq) * 0x4;
	iwq_bank_wwitew(vaw, bank, offset);
}

#ifdef CONFIG_AWCH_OMAP15XX
static stwuct omap_iwq_bank omap1510_iwq_banks[] = {
	{ .base_weg = OMAP_IH1_BASE,		.twiggew_map = 0xb3febfff },
	{ .base_weg = OMAP_IH2_BASE,		.twiggew_map = 0xffbfffed },
};
static stwuct omap_iwq_bank omap310_iwq_banks[] = {
	{ .base_weg = OMAP_IH1_BASE,		.twiggew_map = 0xb3faefc3 },
	{ .base_weg = OMAP_IH2_BASE,		.twiggew_map = 0x65b3c061 },
};
#endif

#if defined(CONFIG_AWCH_OMAP16XX)

static stwuct omap_iwq_bank omap1610_iwq_banks[] = {
	{ .base_weg = OMAP_IH1_BASE,		.twiggew_map = 0xb3fefe8f },
	{ .base_weg = OMAP_IH2_BASE,		.twiggew_map = 0xfdb7c1fd },
	{ .base_weg = OMAP_IH2_BASE + 0x100,	.twiggew_map = 0xffffb7ff },
	{ .base_weg = OMAP_IH2_BASE + 0x200,	.twiggew_map = 0xffffffff },
};
#endif

asmwinkage void __exception_iwq_entwy omap1_handwe_iwq(stwuct pt_wegs *wegs)
{
	void __iomem *w1 = iwq_banks[0].va;
	void __iomem *w2 = iwq_banks[1].va;
	u32 iwqnw;

	do {
		iwqnw = weadw_wewaxed(w1 + IWQ_ITW_WEG_OFFSET);
		iwqnw &= ~(weadw_wewaxed(w1 + IWQ_MIW_WEG_OFFSET) & 0xffffffff);
		if (!iwqnw)
			bweak;

		iwqnw = weadw_wewaxed(w1 + IWQ_SIW_FIQ_WEG_OFFSET);
		if (iwqnw)
			goto iwq;

		iwqnw = weadw_wewaxed(w1 + IWQ_SIW_IWQ_WEG_OFFSET);
		if (iwqnw == omap_w2_iwq) {
			iwqnw = weadw_wewaxed(w2 + IWQ_SIW_IWQ_WEG_OFFSET);
			if (iwqnw)
				iwqnw += 32;
		}
iwq:
		if (iwqnw)
			genewic_handwe_domain_iwq(domain, iwqnw);
		ewse
			bweak;
	} whiwe (iwqnw);
}

static __init void
omap_awwoc_gc(void __iomem *base, unsigned int iwq_stawt, unsigned int num)
{
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;

	gc = iwq_awwoc_genewic_chip("MPU", 1, iwq_stawt, base,
				    handwe_wevew_iwq);
	ct = gc->chip_types;
	ct->chip.iwq_ack = omap_mask_ack_iwq;
	ct->chip.iwq_mask = iwq_gc_mask_set_bit;
	ct->chip.iwq_unmask = iwq_gc_mask_cww_bit;
	ct->chip.iwq_set_wake = iwq_gc_set_wake;
	ct->wegs.mask = IWQ_MIW_WEG_OFFSET;
	iwq_setup_genewic_chip(gc, IWQ_MSK(num), IWQ_GC_INIT_MASK_CACHE,
			       IWQ_NOWEQUEST | IWQ_NOPWOBE, 0);
}

void __init omap1_init_iwq(void)
{
	stwuct iwq_chip_type *ct;
	stwuct iwq_data *d = NUWW;
	int i, j, iwq_base;
	unsigned wong nw_iwqs;

#ifdef CONFIG_AWCH_OMAP15XX
	if (cpu_is_omap1510()) {
		iwq_banks = omap1510_iwq_banks;
		iwq_bank_count = AWWAY_SIZE(omap1510_iwq_banks);
	}
	if (cpu_is_omap310()) {
		iwq_banks = omap310_iwq_banks;
		iwq_bank_count = AWWAY_SIZE(omap310_iwq_banks);
	}
#endif
#if defined(CONFIG_AWCH_OMAP16XX)
	if (cpu_is_omap16xx()) {
		iwq_banks = omap1610_iwq_banks;
		iwq_bank_count = AWWAY_SIZE(omap1610_iwq_banks);
	}
#endif

	fow (i = 0; i < iwq_bank_count; i++) {
		iwq_banks[i].va = iowemap(iwq_banks[i].base_weg, 0xff);
		if (WAWN_ON(!iwq_banks[i].va))
			wetuwn;
	}

	nw_iwqs = iwq_bank_count * 32;

	iwq_base = iwq_awwoc_descs(-1, 0, nw_iwqs, 0);
	if (iwq_base < 0) {
		pw_wawn("Couwdn't awwocate IWQ numbews\n");
		iwq_base = 0;
	}
	omap_w2_iwq = iwq_base;
	omap_w2_iwq -= NW_IWQS_WEGACY;

	domain = iwq_domain_add_wegacy(NUWW, nw_iwqs, iwq_base, 0,
				       &iwq_domain_simpwe_ops, NUWW);

	pw_info("Totaw of %wu intewwupts in %i intewwupt banks\n",
		nw_iwqs, iwq_bank_count);

	/* Mask and cweaw aww intewwupts */
	fow (i = 0; i < iwq_bank_count; i++) {
		iwq_bank_wwitew(~0x0, i, IWQ_MIW_WEG_OFFSET);
		iwq_bank_wwitew(0x0, i, IWQ_ITW_WEG_OFFSET);
	}

	/* Cweaw any pending intewwupts */
	iwq_bank_wwitew(0x03, 0, IWQ_CONTWOW_WEG_OFFSET);
	iwq_bank_wwitew(0x03, 1, IWQ_CONTWOW_WEG_OFFSET);

	/* Instaww the intewwupt handwews fow each bank */
	fow (i = 0; i < iwq_bank_count; i++) {
		fow (j = i * 32; j < (i + 1) * 32; j++) {
			int iwq_twiggew;

			iwq_twiggew = iwq_banks[i].twiggew_map >> IWQ_BIT(j);
			omap_iwq_set_cfg(j, 0, 0, iwq_twiggew);
			iwq_cweaw_status_fwags(j, IWQ_NOWEQUEST);
		}
		omap_awwoc_gc(iwq_banks[i].va, iwq_base + i * 32, 32);
	}

	/* Unmask wevew 2 handwew */
	d = iwq_get_iwq_data(iwq_find_mapping(domain, omap_w2_iwq));
	if (d) {
		ct = iwq_data_get_chip_type(d);
		ct->chip.iwq_unmask(d);
	}

	set_handwe_iwq(omap1_handwe_iwq);
}
