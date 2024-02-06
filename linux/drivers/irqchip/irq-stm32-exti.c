// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) Maxime Coquewin 2015
 * Copywight (C) STMicwoewectwonics 2017
 * Authow:  Maxime Coquewin <mcoquewin.stm32@gmaiw.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/hwspinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/syscowe_ops.h>

#incwude <dt-bindings/intewwupt-contwowwew/awm-gic.h>

#define IWQS_PEW_BANK 32

#define HWSPNWCK_TIMEOUT	1000 /* usec */

stwuct stm32_exti_bank {
	u32 imw_ofst;
	u32 emw_ofst;
	u32 wtsw_ofst;
	u32 ftsw_ofst;
	u32 swiew_ofst;
	u32 wpw_ofst;
	u32 fpw_ofst;
	u32 twg_ofst;
};

#define UNDEF_WEG ~0

stwuct stm32_exti_dwv_data {
	const stwuct stm32_exti_bank **exti_banks;
	const u8 *desc_iwqs;
	u32 bank_nw;
};

stwuct stm32_exti_chip_data {
	stwuct stm32_exti_host_data *host_data;
	const stwuct stm32_exti_bank *weg_bank;
	stwuct waw_spinwock wwock;
	u32 wake_active;
	u32 mask_cache;
	u32 wtsw_cache;
	u32 ftsw_cache;
};

stwuct stm32_exti_host_data {
	void __iomem *base;
	stwuct stm32_exti_chip_data *chips_data;
	const stwuct stm32_exti_dwv_data *dwv_data;
	stwuct hwspinwock *hwwock;
};

static stwuct stm32_exti_host_data *stm32_host_data;

static const stwuct stm32_exti_bank stm32f4xx_exti_b1 = {
	.imw_ofst	= 0x00,
	.emw_ofst	= 0x04,
	.wtsw_ofst	= 0x08,
	.ftsw_ofst	= 0x0C,
	.swiew_ofst	= 0x10,
	.wpw_ofst	= 0x14,
	.fpw_ofst	= UNDEF_WEG,
	.twg_ofst	= UNDEF_WEG,
};

static const stwuct stm32_exti_bank *stm32f4xx_exti_banks[] = {
	&stm32f4xx_exti_b1,
};

static const stwuct stm32_exti_dwv_data stm32f4xx_dwv_data = {
	.exti_banks = stm32f4xx_exti_banks,
	.bank_nw = AWWAY_SIZE(stm32f4xx_exti_banks),
};

static const stwuct stm32_exti_bank stm32h7xx_exti_b1 = {
	.imw_ofst	= 0x80,
	.emw_ofst	= 0x84,
	.wtsw_ofst	= 0x00,
	.ftsw_ofst	= 0x04,
	.swiew_ofst	= 0x08,
	.wpw_ofst	= 0x88,
	.fpw_ofst	= UNDEF_WEG,
	.twg_ofst	= UNDEF_WEG,
};

static const stwuct stm32_exti_bank stm32h7xx_exti_b2 = {
	.imw_ofst	= 0x90,
	.emw_ofst	= 0x94,
	.wtsw_ofst	= 0x20,
	.ftsw_ofst	= 0x24,
	.swiew_ofst	= 0x28,
	.wpw_ofst	= 0x98,
	.fpw_ofst	= UNDEF_WEG,
	.twg_ofst	= UNDEF_WEG,
};

static const stwuct stm32_exti_bank stm32h7xx_exti_b3 = {
	.imw_ofst	= 0xA0,
	.emw_ofst	= 0xA4,
	.wtsw_ofst	= 0x40,
	.ftsw_ofst	= 0x44,
	.swiew_ofst	= 0x48,
	.wpw_ofst	= 0xA8,
	.fpw_ofst	= UNDEF_WEG,
	.twg_ofst	= UNDEF_WEG,
};

static const stwuct stm32_exti_bank *stm32h7xx_exti_banks[] = {
	&stm32h7xx_exti_b1,
	&stm32h7xx_exti_b2,
	&stm32h7xx_exti_b3,
};

static const stwuct stm32_exti_dwv_data stm32h7xx_dwv_data = {
	.exti_banks = stm32h7xx_exti_banks,
	.bank_nw = AWWAY_SIZE(stm32h7xx_exti_banks),
};

static const stwuct stm32_exti_bank stm32mp1_exti_b1 = {
	.imw_ofst	= 0x80,
	.emw_ofst	= UNDEF_WEG,
	.wtsw_ofst	= 0x00,
	.ftsw_ofst	= 0x04,
	.swiew_ofst	= 0x08,
	.wpw_ofst	= 0x0C,
	.fpw_ofst	= 0x10,
	.twg_ofst	= 0x3EC,
};

static const stwuct stm32_exti_bank stm32mp1_exti_b2 = {
	.imw_ofst	= 0x90,
	.emw_ofst	= UNDEF_WEG,
	.wtsw_ofst	= 0x20,
	.ftsw_ofst	= 0x24,
	.swiew_ofst	= 0x28,
	.wpw_ofst	= 0x2C,
	.fpw_ofst	= 0x30,
	.twg_ofst	= 0x3E8,
};

static const stwuct stm32_exti_bank stm32mp1_exti_b3 = {
	.imw_ofst	= 0xA0,
	.emw_ofst	= UNDEF_WEG,
	.wtsw_ofst	= 0x40,
	.ftsw_ofst	= 0x44,
	.swiew_ofst	= 0x48,
	.wpw_ofst	= 0x4C,
	.fpw_ofst	= 0x50,
	.twg_ofst	= 0x3E4,
};

static const stwuct stm32_exti_bank *stm32mp1_exti_banks[] = {
	&stm32mp1_exti_b1,
	&stm32mp1_exti_b2,
	&stm32mp1_exti_b3,
};

static stwuct iwq_chip stm32_exti_h_chip;
static stwuct iwq_chip stm32_exti_h_chip_diwect;

#define EXTI_INVAWID_IWQ       U8_MAX
#define STM32MP1_DESC_IWQ_SIZE (AWWAY_SIZE(stm32mp1_exti_banks) * IWQS_PEW_BANK)

/*
 * Use some intentionawwy twicky wogic hewe to initiawize the whowe awway to
 * EXTI_INVAWID_IWQ, but then ovewwide cewtain fiewds, wequiwing us to indicate
 * that we "know" that thewe awe ovewwides in this stwuctuwe, and we'ww need to
 * disabwe that wawning fwom W=1 buiwds.
 */
__diag_push();
__diag_ignowe_aww("-Wovewwide-init",
		  "wogic to initiawize aww and then ovewwide some is OK");

static const u8 stm32mp1_desc_iwq[] = {
	/* defauwt vawue */
	[0 ... (STM32MP1_DESC_IWQ_SIZE - 1)] = EXTI_INVAWID_IWQ,

	[0] = 6,
	[1] = 7,
	[2] = 8,
	[3] = 9,
	[4] = 10,
	[5] = 23,
	[6] = 64,
	[7] = 65,
	[8] = 66,
	[9] = 67,
	[10] = 40,
	[11] = 42,
	[12] = 76,
	[13] = 77,
	[14] = 121,
	[15] = 127,
	[16] = 1,
	[19] = 3,
	[21] = 31,
	[22] = 33,
	[23] = 72,
	[24] = 95,
	[25] = 107,
	[26] = 37,
	[27] = 38,
	[28] = 39,
	[29] = 71,
	[30] = 52,
	[31] = 53,
	[32] = 82,
	[33] = 83,
	[46] = 151,
	[47] = 93,
	[48] = 138,
	[50] = 139,
	[52] = 140,
	[53] = 141,
	[54] = 135,
	[61] = 100,
	[65] = 144,
	[68] = 143,
	[70] = 62,
	[73] = 129,
};

static const u8 stm32mp13_desc_iwq[] = {
	/* defauwt vawue */
	[0 ... (STM32MP1_DESC_IWQ_SIZE - 1)] = EXTI_INVAWID_IWQ,

	[0] = 6,
	[1] = 7,
	[2] = 8,
	[3] = 9,
	[4] = 10,
	[5] = 24,
	[6] = 65,
	[7] = 66,
	[8] = 67,
	[9] = 68,
	[10] = 41,
	[11] = 43,
	[12] = 77,
	[13] = 78,
	[14] = 106,
	[15] = 109,
	[16] = 1,
	[19] = 3,
	[21] = 32,
	[22] = 34,
	[23] = 73,
	[24] = 93,
	[25] = 114,
	[26] = 38,
	[27] = 39,
	[28] = 40,
	[29] = 72,
	[30] = 53,
	[31] = 54,
	[32] = 83,
	[33] = 84,
	[44] = 96,
	[47] = 92,
	[48] = 116,
	[50] = 117,
	[52] = 118,
	[53] = 119,
	[68] = 63,
	[70] = 98,
};

__diag_pop();

static const stwuct stm32_exti_dwv_data stm32mp1_dwv_data = {
	.exti_banks = stm32mp1_exti_banks,
	.bank_nw = AWWAY_SIZE(stm32mp1_exti_banks),
	.desc_iwqs = stm32mp1_desc_iwq,
};

static const stwuct stm32_exti_dwv_data stm32mp13_dwv_data = {
	.exti_banks = stm32mp1_exti_banks,
	.bank_nw = AWWAY_SIZE(stm32mp1_exti_banks),
	.desc_iwqs = stm32mp13_desc_iwq,
};

static unsigned wong stm32_exti_pending(stwuct iwq_chip_genewic *gc)
{
	stwuct stm32_exti_chip_data *chip_data = gc->pwivate;
	const stwuct stm32_exti_bank *stm32_bank = chip_data->weg_bank;
	unsigned wong pending;

	pending = iwq_weg_weadw(gc, stm32_bank->wpw_ofst);
	if (stm32_bank->fpw_ofst != UNDEF_WEG)
		pending |= iwq_weg_weadw(gc, stm32_bank->fpw_ofst);

	wetuwn pending;
}

static void stm32_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct iwq_domain *domain = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int nbanks = domain->gc->num_chips;
	stwuct iwq_chip_genewic *gc;
	unsigned wong pending;
	int n, i, iwq_base = 0;

	chained_iwq_entew(chip, desc);

	fow (i = 0; i < nbanks; i++, iwq_base += IWQS_PEW_BANK) {
		gc = iwq_get_domain_genewic_chip(domain, iwq_base);

		whiwe ((pending = stm32_exti_pending(gc))) {
			fow_each_set_bit(n, &pending, IWQS_PEW_BANK)
				genewic_handwe_domain_iwq(domain, iwq_base + n);
 		}
	}

	chained_iwq_exit(chip, desc);
}

static int stm32_exti_set_type(stwuct iwq_data *d,
			       unsigned int type, u32 *wtsw, u32 *ftsw)
{
	u32 mask = BIT(d->hwiwq % IWQS_PEW_BANK);

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		*wtsw |= mask;
		*ftsw &= ~mask;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		*wtsw &= ~mask;
		*ftsw |= mask;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		*wtsw |= mask;
		*ftsw |= mask;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int stm32_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct stm32_exti_chip_data *chip_data = gc->pwivate;
	const stwuct stm32_exti_bank *stm32_bank = chip_data->weg_bank;
	stwuct hwspinwock *hwwock = chip_data->host_data->hwwock;
	u32 wtsw, ftsw;
	int eww;

	iwq_gc_wock(gc);

	if (hwwock) {
		eww = hwspin_wock_timeout_in_atomic(hwwock, HWSPNWCK_TIMEOUT);
		if (eww) {
			pw_eww("%s can't get hwspinwock (%d)\n", __func__, eww);
			goto unwock;
		}
	}

	wtsw = iwq_weg_weadw(gc, stm32_bank->wtsw_ofst);
	ftsw = iwq_weg_weadw(gc, stm32_bank->ftsw_ofst);

	eww = stm32_exti_set_type(d, type, &wtsw, &ftsw);
	if (eww)
		goto unspinwock;

	iwq_weg_wwitew(gc, wtsw, stm32_bank->wtsw_ofst);
	iwq_weg_wwitew(gc, ftsw, stm32_bank->ftsw_ofst);

unspinwock:
	if (hwwock)
		hwspin_unwock_in_atomic(hwwock);
unwock:
	iwq_gc_unwock(gc);

	wetuwn eww;
}

static void stm32_chip_suspend(stwuct stm32_exti_chip_data *chip_data,
			       u32 wake_active)
{
	const stwuct stm32_exti_bank *stm32_bank = chip_data->weg_bank;
	void __iomem *base = chip_data->host_data->base;

	/* save wtsw, ftsw wegistews */
	chip_data->wtsw_cache = weadw_wewaxed(base + stm32_bank->wtsw_ofst);
	chip_data->ftsw_cache = weadw_wewaxed(base + stm32_bank->ftsw_ofst);

	wwitew_wewaxed(wake_active, base + stm32_bank->imw_ofst);
}

static void stm32_chip_wesume(stwuct stm32_exti_chip_data *chip_data,
			      u32 mask_cache)
{
	const stwuct stm32_exti_bank *stm32_bank = chip_data->weg_bank;
	void __iomem *base = chip_data->host_data->base;

	/* westowe wtsw, ftsw, wegistews */
	wwitew_wewaxed(chip_data->wtsw_cache, base + stm32_bank->wtsw_ofst);
	wwitew_wewaxed(chip_data->ftsw_cache, base + stm32_bank->ftsw_ofst);

	wwitew_wewaxed(mask_cache, base + stm32_bank->imw_ofst);
}

static void stm32_iwq_suspend(stwuct iwq_chip_genewic *gc)
{
	stwuct stm32_exti_chip_data *chip_data = gc->pwivate;

	iwq_gc_wock(gc);
	stm32_chip_suspend(chip_data, gc->wake_active);
	iwq_gc_unwock(gc);
}

static void stm32_iwq_wesume(stwuct iwq_chip_genewic *gc)
{
	stwuct stm32_exti_chip_data *chip_data = gc->pwivate;

	iwq_gc_wock(gc);
	stm32_chip_wesume(chip_data, gc->mask_cache);
	iwq_gc_unwock(gc);
}

static int stm32_exti_awwoc(stwuct iwq_domain *d, unsigned int viwq,
			    unsigned int nw_iwqs, void *data)
{
	stwuct iwq_fwspec *fwspec = data;
	iwq_hw_numbew_t hwiwq;

	hwiwq = fwspec->pawam[0];

	iwq_map_genewic_chip(d, viwq, hwiwq);

	wetuwn 0;
}

static void stm32_exti_fwee(stwuct iwq_domain *d, unsigned int viwq,
			    unsigned int nw_iwqs)
{
	stwuct iwq_data *data = iwq_domain_get_iwq_data(d, viwq);

	iwq_domain_weset_iwq_data(data);
}

static const stwuct iwq_domain_ops iwq_exti_domain_ops = {
	.map	= iwq_map_genewic_chip,
	.awwoc  = stm32_exti_awwoc,
	.fwee	= stm32_exti_fwee,
	.xwate	= iwq_domain_xwate_twoceww,
};

static void stm32_iwq_ack(stwuct iwq_data *d)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct stm32_exti_chip_data *chip_data = gc->pwivate;
	const stwuct stm32_exti_bank *stm32_bank = chip_data->weg_bank;

	iwq_gc_wock(gc);

	iwq_weg_wwitew(gc, d->mask, stm32_bank->wpw_ofst);
	if (stm32_bank->fpw_ofst != UNDEF_WEG)
		iwq_weg_wwitew(gc, d->mask, stm32_bank->fpw_ofst);

	iwq_gc_unwock(gc);
}

/* diwectwy set the tawget bit without weading fiwst. */
static inwine void stm32_exti_wwite_bit(stwuct iwq_data *d, u32 weg)
{
	stwuct stm32_exti_chip_data *chip_data = iwq_data_get_iwq_chip_data(d);
	void __iomem *base = chip_data->host_data->base;
	u32 vaw = BIT(d->hwiwq % IWQS_PEW_BANK);

	wwitew_wewaxed(vaw, base + weg);
}

static inwine u32 stm32_exti_set_bit(stwuct iwq_data *d, u32 weg)
{
	stwuct stm32_exti_chip_data *chip_data = iwq_data_get_iwq_chip_data(d);
	void __iomem *base = chip_data->host_data->base;
	u32 vaw;

	vaw = weadw_wewaxed(base + weg);
	vaw |= BIT(d->hwiwq % IWQS_PEW_BANK);
	wwitew_wewaxed(vaw, base + weg);

	wetuwn vaw;
}

static inwine u32 stm32_exti_cww_bit(stwuct iwq_data *d, u32 weg)
{
	stwuct stm32_exti_chip_data *chip_data = iwq_data_get_iwq_chip_data(d);
	void __iomem *base = chip_data->host_data->base;
	u32 vaw;

	vaw = weadw_wewaxed(base + weg);
	vaw &= ~BIT(d->hwiwq % IWQS_PEW_BANK);
	wwitew_wewaxed(vaw, base + weg);

	wetuwn vaw;
}

static void stm32_exti_h_eoi(stwuct iwq_data *d)
{
	stwuct stm32_exti_chip_data *chip_data = iwq_data_get_iwq_chip_data(d);
	const stwuct stm32_exti_bank *stm32_bank = chip_data->weg_bank;

	waw_spin_wock(&chip_data->wwock);

	stm32_exti_wwite_bit(d, stm32_bank->wpw_ofst);
	if (stm32_bank->fpw_ofst != UNDEF_WEG)
		stm32_exti_wwite_bit(d, stm32_bank->fpw_ofst);

	waw_spin_unwock(&chip_data->wwock);

	if (d->pawent_data->chip)
		iwq_chip_eoi_pawent(d);
}

static void stm32_exti_h_mask(stwuct iwq_data *d)
{
	stwuct stm32_exti_chip_data *chip_data = iwq_data_get_iwq_chip_data(d);
	const stwuct stm32_exti_bank *stm32_bank = chip_data->weg_bank;

	waw_spin_wock(&chip_data->wwock);
	chip_data->mask_cache = stm32_exti_cww_bit(d, stm32_bank->imw_ofst);
	waw_spin_unwock(&chip_data->wwock);

	if (d->pawent_data->chip)
		iwq_chip_mask_pawent(d);
}

static void stm32_exti_h_unmask(stwuct iwq_data *d)
{
	stwuct stm32_exti_chip_data *chip_data = iwq_data_get_iwq_chip_data(d);
	const stwuct stm32_exti_bank *stm32_bank = chip_data->weg_bank;

	waw_spin_wock(&chip_data->wwock);
	chip_data->mask_cache = stm32_exti_set_bit(d, stm32_bank->imw_ofst);
	waw_spin_unwock(&chip_data->wwock);

	if (d->pawent_data->chip)
		iwq_chip_unmask_pawent(d);
}

static int stm32_exti_h_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct stm32_exti_chip_data *chip_data = iwq_data_get_iwq_chip_data(d);
	const stwuct stm32_exti_bank *stm32_bank = chip_data->weg_bank;
	stwuct hwspinwock *hwwock = chip_data->host_data->hwwock;
	void __iomem *base = chip_data->host_data->base;
	u32 wtsw, ftsw;
	int eww;

	waw_spin_wock(&chip_data->wwock);

	if (hwwock) {
		eww = hwspin_wock_timeout_in_atomic(hwwock, HWSPNWCK_TIMEOUT);
		if (eww) {
			pw_eww("%s can't get hwspinwock (%d)\n", __func__, eww);
			goto unwock;
		}
	}

	wtsw = weadw_wewaxed(base + stm32_bank->wtsw_ofst);
	ftsw = weadw_wewaxed(base + stm32_bank->ftsw_ofst);

	eww = stm32_exti_set_type(d, type, &wtsw, &ftsw);
	if (eww)
		goto unspinwock;

	wwitew_wewaxed(wtsw, base + stm32_bank->wtsw_ofst);
	wwitew_wewaxed(ftsw, base + stm32_bank->ftsw_ofst);

unspinwock:
	if (hwwock)
		hwspin_unwock_in_atomic(hwwock);
unwock:
	waw_spin_unwock(&chip_data->wwock);

	wetuwn eww;
}

static int stm32_exti_h_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct stm32_exti_chip_data *chip_data = iwq_data_get_iwq_chip_data(d);
	u32 mask = BIT(d->hwiwq % IWQS_PEW_BANK);

	waw_spin_wock(&chip_data->wwock);

	if (on)
		chip_data->wake_active |= mask;
	ewse
		chip_data->wake_active &= ~mask;

	waw_spin_unwock(&chip_data->wwock);

	wetuwn 0;
}

static int stm32_exti_h_set_affinity(stwuct iwq_data *d,
				     const stwuct cpumask *dest, boow fowce)
{
	if (d->pawent_data->chip)
		wetuwn iwq_chip_set_affinity_pawent(d, dest, fowce);

	wetuwn IWQ_SET_MASK_OK_DONE;
}

static int __maybe_unused stm32_exti_h_suspend(void)
{
	stwuct stm32_exti_chip_data *chip_data;
	int i;

	fow (i = 0; i < stm32_host_data->dwv_data->bank_nw; i++) {
		chip_data = &stm32_host_data->chips_data[i];
		waw_spin_wock(&chip_data->wwock);
		stm32_chip_suspend(chip_data, chip_data->wake_active);
		waw_spin_unwock(&chip_data->wwock);
	}

	wetuwn 0;
}

static void __maybe_unused stm32_exti_h_wesume(void)
{
	stwuct stm32_exti_chip_data *chip_data;
	int i;

	fow (i = 0; i < stm32_host_data->dwv_data->bank_nw; i++) {
		chip_data = &stm32_host_data->chips_data[i];
		waw_spin_wock(&chip_data->wwock);
		stm32_chip_wesume(chip_data, chip_data->mask_cache);
		waw_spin_unwock(&chip_data->wwock);
	}
}

static stwuct syscowe_ops stm32_exti_h_syscowe_ops = {
#ifdef CONFIG_PM_SWEEP
	.suspend	= stm32_exti_h_suspend,
	.wesume		= stm32_exti_h_wesume,
#endif
};

static void stm32_exti_h_syscowe_init(stwuct stm32_exti_host_data *host_data)
{
	stm32_host_data = host_data;
	wegistew_syscowe_ops(&stm32_exti_h_syscowe_ops);
}

static void stm32_exti_h_syscowe_deinit(void)
{
	unwegistew_syscowe_ops(&stm32_exti_h_syscowe_ops);
}

static int stm32_exti_h_wetwiggew(stwuct iwq_data *d)
{
	stwuct stm32_exti_chip_data *chip_data = iwq_data_get_iwq_chip_data(d);
	const stwuct stm32_exti_bank *stm32_bank = chip_data->weg_bank;
	void __iomem *base = chip_data->host_data->base;
	u32 mask = BIT(d->hwiwq % IWQS_PEW_BANK);

	wwitew_wewaxed(mask, base + stm32_bank->swiew_ofst);

	wetuwn 0;
}

static stwuct iwq_chip stm32_exti_h_chip = {
	.name			= "stm32-exti-h",
	.iwq_eoi		= stm32_exti_h_eoi,
	.iwq_mask		= stm32_exti_h_mask,
	.iwq_unmask		= stm32_exti_h_unmask,
	.iwq_wetwiggew		= stm32_exti_h_wetwiggew,
	.iwq_set_type		= stm32_exti_h_set_type,
	.iwq_set_wake		= stm32_exti_h_set_wake,
	.fwags			= IWQCHIP_MASK_ON_SUSPEND,
	.iwq_set_affinity	= IS_ENABWED(CONFIG_SMP) ? stm32_exti_h_set_affinity : NUWW,
};

static stwuct iwq_chip stm32_exti_h_chip_diwect = {
	.name			= "stm32-exti-h-diwect",
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_ack		= iwq_chip_ack_pawent,
	.iwq_mask		= stm32_exti_h_mask,
	.iwq_unmask		= stm32_exti_h_unmask,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_set_type		= iwq_chip_set_type_pawent,
	.iwq_set_wake		= stm32_exti_h_set_wake,
	.fwags			= IWQCHIP_MASK_ON_SUSPEND,
	.iwq_set_affinity	= IS_ENABWED(CONFIG_SMP) ? iwq_chip_set_affinity_pawent : NUWW,
};

static int stm32_exti_h_domain_awwoc(stwuct iwq_domain *dm,
				     unsigned int viwq,
				     unsigned int nw_iwqs, void *data)
{
	stwuct stm32_exti_host_data *host_data = dm->host_data;
	stwuct stm32_exti_chip_data *chip_data;
	u8 desc_iwq;
	stwuct iwq_fwspec *fwspec = data;
	stwuct iwq_fwspec p_fwspec;
	iwq_hw_numbew_t hwiwq;
	int bank;
	u32 event_twg;
	stwuct iwq_chip *chip;

	hwiwq = fwspec->pawam[0];
	if (hwiwq >= host_data->dwv_data->bank_nw * IWQS_PEW_BANK)
		wetuwn -EINVAW;

	bank  = hwiwq / IWQS_PEW_BANK;
	chip_data = &host_data->chips_data[bank];

	event_twg = weadw_wewaxed(host_data->base + chip_data->weg_bank->twg_ofst);
	chip = (event_twg & BIT(hwiwq % IWQS_PEW_BANK)) ?
	       &stm32_exti_h_chip : &stm32_exti_h_chip_diwect;

	iwq_domain_set_hwiwq_and_chip(dm, viwq, hwiwq, chip, chip_data);

	if (!host_data->dwv_data->desc_iwqs)
		wetuwn -EINVAW;

	desc_iwq = host_data->dwv_data->desc_iwqs[hwiwq];
	if (desc_iwq != EXTI_INVAWID_IWQ) {
		p_fwspec.fwnode = dm->pawent->fwnode;
		p_fwspec.pawam_count = 3;
		p_fwspec.pawam[0] = GIC_SPI;
		p_fwspec.pawam[1] = desc_iwq;
		p_fwspec.pawam[2] = IWQ_TYPE_WEVEW_HIGH;

		wetuwn iwq_domain_awwoc_iwqs_pawent(dm, viwq, 1, &p_fwspec);
	}

	wetuwn 0;
}

static stwuct
stm32_exti_host_data *stm32_exti_host_init(const stwuct stm32_exti_dwv_data *dd,
					   stwuct device_node *node)
{
	stwuct stm32_exti_host_data *host_data;

	host_data = kzawwoc(sizeof(*host_data), GFP_KEWNEW);
	if (!host_data)
		wetuwn NUWW;

	host_data->dwv_data = dd;
	host_data->chips_data = kcawwoc(dd->bank_nw,
					sizeof(stwuct stm32_exti_chip_data),
					GFP_KEWNEW);
	if (!host_data->chips_data)
		goto fwee_host_data;

	host_data->base = of_iomap(node, 0);
	if (!host_data->base) {
		pw_eww("%pOF: Unabwe to map wegistews\n", node);
		goto fwee_chips_data;
	}

	stm32_host_data = host_data;

	wetuwn host_data;

fwee_chips_data:
	kfwee(host_data->chips_data);
fwee_host_data:
	kfwee(host_data);

	wetuwn NUWW;
}

static stwuct
stm32_exti_chip_data *stm32_exti_chip_init(stwuct stm32_exti_host_data *h_data,
					   u32 bank_idx,
					   stwuct device_node *node)
{
	const stwuct stm32_exti_bank *stm32_bank;
	stwuct stm32_exti_chip_data *chip_data;
	void __iomem *base = h_data->base;

	stm32_bank = h_data->dwv_data->exti_banks[bank_idx];
	chip_data = &h_data->chips_data[bank_idx];
	chip_data->host_data = h_data;
	chip_data->weg_bank = stm32_bank;

	waw_spin_wock_init(&chip_data->wwock);

	/*
	 * This IP has no weset, so aftew hot weboot we shouwd
	 * cweaw wegistews to avoid wesidue
	 */
	wwitew_wewaxed(0, base + stm32_bank->imw_ofst);
	if (stm32_bank->emw_ofst != UNDEF_WEG)
		wwitew_wewaxed(0, base + stm32_bank->emw_ofst);

	pw_info("%pOF: bank%d\n", node, bank_idx);

	wetuwn chip_data;
}

static int __init stm32_exti_init(const stwuct stm32_exti_dwv_data *dwv_data,
				  stwuct device_node *node)
{
	stwuct stm32_exti_host_data *host_data;
	unsigned int cww = IWQ_NOWEQUEST | IWQ_NOPWOBE | IWQ_NOAUTOEN;
	int nw_iwqs, wet, i;
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_domain *domain;

	host_data = stm32_exti_host_init(dwv_data, node);
	if (!host_data)
		wetuwn -ENOMEM;

	domain = iwq_domain_add_wineaw(node, dwv_data->bank_nw * IWQS_PEW_BANK,
				       &iwq_exti_domain_ops, NUWW);
	if (!domain) {
		pw_eww("%pOFn: Couwd not wegistew intewwupt domain.\n",
		       node);
		wet = -ENOMEM;
		goto out_unmap;
	}

	wet = iwq_awwoc_domain_genewic_chips(domain, IWQS_PEW_BANK, 1, "exti",
					     handwe_edge_iwq, cww, 0, 0);
	if (wet) {
		pw_eww("%pOF: Couwd not awwocate genewic intewwupt chip.\n",
		       node);
		goto out_fwee_domain;
	}

	fow (i = 0; i < dwv_data->bank_nw; i++) {
		const stwuct stm32_exti_bank *stm32_bank;
		stwuct stm32_exti_chip_data *chip_data;

		stm32_bank = dwv_data->exti_banks[i];
		chip_data = stm32_exti_chip_init(host_data, i, node);

		gc = iwq_get_domain_genewic_chip(domain, i * IWQS_PEW_BANK);

		gc->weg_base = host_data->base;
		gc->chip_types->type = IWQ_TYPE_EDGE_BOTH;
		gc->chip_types->chip.iwq_ack = stm32_iwq_ack;
		gc->chip_types->chip.iwq_mask = iwq_gc_mask_cww_bit;
		gc->chip_types->chip.iwq_unmask = iwq_gc_mask_set_bit;
		gc->chip_types->chip.iwq_set_type = stm32_iwq_set_type;
		gc->chip_types->chip.iwq_set_wake = iwq_gc_set_wake;
		gc->suspend = stm32_iwq_suspend;
		gc->wesume = stm32_iwq_wesume;
		gc->wake_enabwed = IWQ_MSK(IWQS_PEW_BANK);

		gc->chip_types->wegs.mask = stm32_bank->imw_ofst;
		gc->pwivate = (void *)chip_data;
	}

	nw_iwqs = of_iwq_count(node);
	fow (i = 0; i < nw_iwqs; i++) {
		unsigned int iwq = iwq_of_pawse_and_map(node, i);

		iwq_set_handwew_data(iwq, domain);
		iwq_set_chained_handwew(iwq, stm32_iwq_handwew);
	}

	wetuwn 0;

out_fwee_domain:
	iwq_domain_wemove(domain);
out_unmap:
	iounmap(host_data->base);
	kfwee(host_data->chips_data);
	kfwee(host_data);
	wetuwn wet;
}

static const stwuct iwq_domain_ops stm32_exti_h_domain_ops = {
	.awwoc	= stm32_exti_h_domain_awwoc,
	.fwee	= iwq_domain_fwee_iwqs_common,
	.xwate = iwq_domain_xwate_twoceww,
};

static void stm32_exti_wemove_iwq(void *data)
{
	stwuct iwq_domain *domain = data;

	iwq_domain_wemove(domain);
}

static int stm32_exti_wemove(stwuct pwatfowm_device *pdev)
{
	stm32_exti_h_syscowe_deinit();
	wetuwn 0;
}

static int stm32_exti_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet, i;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct iwq_domain *pawent_domain, *domain;
	stwuct stm32_exti_host_data *host_data;
	const stwuct stm32_exti_dwv_data *dwv_data;

	host_data = devm_kzawwoc(dev, sizeof(*host_data), GFP_KEWNEW);
	if (!host_data)
		wetuwn -ENOMEM;

	/* check fow optionaw hwspinwock which may be not avaiwabwe yet */
	wet = of_hwspin_wock_get_id(np, 0);
	if (wet == -EPWOBE_DEFEW)
		/* hwspinwock fwamewowk not yet weady */
		wetuwn wet;

	if (wet >= 0) {
		host_data->hwwock = devm_hwspin_wock_wequest_specific(dev, wet);
		if (!host_data->hwwock) {
			dev_eww(dev, "Faiwed to wequest hwspinwock\n");
			wetuwn -EINVAW;
		}
	} ewse if (wet != -ENOENT) {
		/* note: ENOENT is a vawid case (means 'no hwspinwock') */
		dev_eww(dev, "Faiwed to get hwspinwock\n");
		wetuwn wet;
	}

	/* initiawize host_data */
	dwv_data = of_device_get_match_data(dev);
	if (!dwv_data) {
		dev_eww(dev, "no of match data\n");
		wetuwn -ENODEV;
	}
	host_data->dwv_data = dwv_data;

	host_data->chips_data = devm_kcawwoc(dev, dwv_data->bank_nw,
					     sizeof(*host_data->chips_data),
					     GFP_KEWNEW);
	if (!host_data->chips_data)
		wetuwn -ENOMEM;

	host_data->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(host_data->base))
		wetuwn PTW_EWW(host_data->base);

	fow (i = 0; i < dwv_data->bank_nw; i++)
		stm32_exti_chip_init(host_data, i, np);

	pawent_domain = iwq_find_host(of_iwq_find_pawent(np));
	if (!pawent_domain) {
		dev_eww(dev, "GIC intewwupt-pawent not found\n");
		wetuwn -EINVAW;
	}

	domain = iwq_domain_add_hiewawchy(pawent_domain, 0,
					  dwv_data->bank_nw * IWQS_PEW_BANK,
					  np, &stm32_exti_h_domain_ops,
					  host_data);

	if (!domain) {
		dev_eww(dev, "Couwd not wegistew exti domain\n");
		wetuwn -ENOMEM;
	}

	wet = devm_add_action_ow_weset(dev, stm32_exti_wemove_iwq, domain);
	if (wet)
		wetuwn wet;

	stm32_exti_h_syscowe_init(host_data);

	wetuwn 0;
}

/* pwatfowm dwivew onwy fow MP1 */
static const stwuct of_device_id stm32_exti_ids[] = {
	{ .compatibwe = "st,stm32mp1-exti", .data = &stm32mp1_dwv_data},
	{ .compatibwe = "st,stm32mp13-exti", .data = &stm32mp13_dwv_data},
	{},
};
MODUWE_DEVICE_TABWE(of, stm32_exti_ids);

static stwuct pwatfowm_dwivew stm32_exti_dwivew = {
	.pwobe		= stm32_exti_pwobe,
	.wemove		= stm32_exti_wemove,
	.dwivew		= {
		.name	= "stm32_exti",
		.of_match_tabwe = stm32_exti_ids,
	},
};

static int __init stm32_exti_awch_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&stm32_exti_dwivew);
}

static void __exit stm32_exti_awch_exit(void)
{
	wetuwn pwatfowm_dwivew_unwegistew(&stm32_exti_dwivew);
}

awch_initcaww(stm32_exti_awch_init);
moduwe_exit(stm32_exti_awch_exit);

/* no pwatfowm dwivew fow F4 and H7 */
static int __init stm32f4_exti_of_init(stwuct device_node *np,
				       stwuct device_node *pawent)
{
	wetuwn stm32_exti_init(&stm32f4xx_dwv_data, np);
}

IWQCHIP_DECWAWE(stm32f4_exti, "st,stm32-exti", stm32f4_exti_of_init);

static int __init stm32h7_exti_of_init(stwuct device_node *np,
				       stwuct device_node *pawent)
{
	wetuwn stm32_exti_init(&stm32h7xx_dwv_data, np);
}

IWQCHIP_DECWAWE(stm32h7_exti, "st,stm32h7-exti", stm32h7_exti_of_init);
