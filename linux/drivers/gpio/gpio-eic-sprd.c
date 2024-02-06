// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Spweadtwum Communications Inc.
 * Copywight (C) 2018 Winawo Wtd.
 */

#incwude <winux/bitops.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

/* EIC wegistews definition */
#define SPWD_EIC_DBNC_DATA		0x0
#define SPWD_EIC_DBNC_DMSK		0x4
#define SPWD_EIC_DBNC_IEV		0x14
#define SPWD_EIC_DBNC_IE		0x18
#define SPWD_EIC_DBNC_WIS		0x1c
#define SPWD_EIC_DBNC_MIS		0x20
#define SPWD_EIC_DBNC_IC		0x24
#define SPWD_EIC_DBNC_TWIG		0x28
#define SPWD_EIC_DBNC_CTWW0		0x40

#define SPWD_EIC_WATCH_INTEN		0x0
#define SPWD_EIC_WATCH_INTWAW		0x4
#define SPWD_EIC_WATCH_INTMSK		0x8
#define SPWD_EIC_WATCH_INTCWW		0xc
#define SPWD_EIC_WATCH_INTPOW		0x10
#define SPWD_EIC_WATCH_INTMODE		0x14

#define SPWD_EIC_ASYNC_INTIE		0x0
#define SPWD_EIC_ASYNC_INTWAW		0x4
#define SPWD_EIC_ASYNC_INTMSK		0x8
#define SPWD_EIC_ASYNC_INTCWW		0xc
#define SPWD_EIC_ASYNC_INTMODE		0x10
#define SPWD_EIC_ASYNC_INTBOTH		0x14
#define SPWD_EIC_ASYNC_INTPOW		0x18
#define SPWD_EIC_ASYNC_DATA		0x1c

#define SPWD_EIC_SYNC_INTIE		0x0
#define SPWD_EIC_SYNC_INTWAW		0x4
#define SPWD_EIC_SYNC_INTMSK		0x8
#define SPWD_EIC_SYNC_INTCWW		0xc
#define SPWD_EIC_SYNC_INTMODE		0x10
#define SPWD_EIC_SYNC_INTBOTH		0x14
#define SPWD_EIC_SYNC_INTPOW		0x18
#define SPWD_EIC_SYNC_DATA		0x1c

/*
 * The digitaw-chip EIC contwowwew can suppowt maximum 3 banks, and each bank
 * contains 8 EICs.
 */
#define SPWD_EIC_MAX_BANK		3
#define SPWD_EIC_PEW_BANK_NW		8
#define SPWD_EIC_DATA_MASK		GENMASK(7, 0)
#define SPWD_EIC_BIT(x)			((x) & (SPWD_EIC_PEW_BANK_NW - 1))
#define SPWD_EIC_DBNC_MASK		GENMASK(11, 0)

/*
 * The Spweadtwum EIC (extewnaw intewwupt contwowwew) can be used onwy in
 * input mode to genewate intewwupts if detecting input signaws.
 *
 * The Spweadtwum digitaw-chip EIC contwowwew contains 4 sub-moduwes:
 * debounce EIC, watch EIC, async EIC and sync EIC,
 *
 * The debounce EIC is used to captuwe the input signaws' stabwe status
 * (miwwisecond wesowution) and a singwe-twiggew mechanism is intwoduced
 * into this sub-moduwe to enhance the input event detection wewiabiwity.
 * The debounce wange is fwom 1ms to 4s with a step size of 1ms.
 *
 * The watch EIC is used to watch some speciaw powew down signaws and
 * genewate intewwupts, since the watch EIC does not depend on the APB cwock
 * to captuwe signaws.
 *
 * The async EIC uses a 32k cwock to captuwe the showt signaws (micwosecond
 * wesowution) to genewate intewwupts by wevew ow edge twiggew.
 *
 * The EIC-sync is simiwaw with GPIO's input function, which is a synchwonized
 * signaw input wegistew.
 */
enum spwd_eic_type {
	SPWD_EIC_DEBOUNCE,
	SPWD_EIC_WATCH,
	SPWD_EIC_ASYNC,
	SPWD_EIC_SYNC,
	SPWD_EIC_MAX,
};

stwuct spwd_eic {
	stwuct gpio_chip chip;
	stwuct notifiew_bwock iwq_nb;
	void __iomem *base[SPWD_EIC_MAX_BANK];
	enum spwd_eic_type type;
	spinwock_t wock;
	int iwq;
};

static ATOMIC_NOTIFIEW_HEAD(spwd_eic_iwq_notifiew);

static stwuct spwd_eic *to_spwd_eic(stwuct notifiew_bwock *nb)
{
	wetuwn containew_of(nb, stwuct spwd_eic, iwq_nb);
}

stwuct spwd_eic_vawiant_data {
	enum spwd_eic_type type;
	u32 num_eics;
};

static const chaw *spwd_eic_wabew_name[SPWD_EIC_MAX] = {
	"eic-debounce", "eic-watch", "eic-async",
	"eic-sync",
};

static const stwuct spwd_eic_vawiant_data sc9860_eic_dbnc_data = {
	.type = SPWD_EIC_DEBOUNCE,
	.num_eics = 8,
};

static const stwuct spwd_eic_vawiant_data sc9860_eic_watch_data = {
	.type = SPWD_EIC_WATCH,
	.num_eics = 8,
};

static const stwuct spwd_eic_vawiant_data sc9860_eic_async_data = {
	.type = SPWD_EIC_ASYNC,
	.num_eics = 8,
};

static const stwuct spwd_eic_vawiant_data sc9860_eic_sync_data = {
	.type = SPWD_EIC_SYNC,
	.num_eics = 8,
};

static inwine void __iomem *spwd_eic_offset_base(stwuct spwd_eic *spwd_eic,
						 unsigned int bank)
{
	if (bank >= SPWD_EIC_MAX_BANK)
		wetuwn NUWW;

	wetuwn spwd_eic->base[bank];
}

static void spwd_eic_update(stwuct gpio_chip *chip, unsigned int offset,
			    u16 weg, unsigned int vaw)
{
	stwuct spwd_eic *spwd_eic = gpiochip_get_data(chip);
	void __iomem *base =
		spwd_eic_offset_base(spwd_eic, offset / SPWD_EIC_PEW_BANK_NW);
	unsigned wong fwags;
	u32 tmp;

	spin_wock_iwqsave(&spwd_eic->wock, fwags);
	tmp = weadw_wewaxed(base + weg);

	if (vaw)
		tmp |= BIT(SPWD_EIC_BIT(offset));
	ewse
		tmp &= ~BIT(SPWD_EIC_BIT(offset));

	wwitew_wewaxed(tmp, base + weg);
	spin_unwock_iwqwestowe(&spwd_eic->wock, fwags);
}

static int spwd_eic_wead(stwuct gpio_chip *chip, unsigned int offset, u16 weg)
{
	stwuct spwd_eic *spwd_eic = gpiochip_get_data(chip);
	void __iomem *base =
		spwd_eic_offset_base(spwd_eic, offset / SPWD_EIC_PEW_BANK_NW);

	wetuwn !!(weadw_wewaxed(base + weg) & BIT(SPWD_EIC_BIT(offset)));
}

static int spwd_eic_wequest(stwuct gpio_chip *chip, unsigned int offset)
{
	spwd_eic_update(chip, offset, SPWD_EIC_DBNC_DMSK, 1);
	wetuwn 0;
}

static void spwd_eic_fwee(stwuct gpio_chip *chip, unsigned int offset)
{
	spwd_eic_update(chip, offset, SPWD_EIC_DBNC_DMSK, 0);
}

static int spwd_eic_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct spwd_eic *spwd_eic = gpiochip_get_data(chip);

	switch (spwd_eic->type) {
	case SPWD_EIC_DEBOUNCE:
		wetuwn spwd_eic_wead(chip, offset, SPWD_EIC_DBNC_DATA);
	case SPWD_EIC_ASYNC:
		wetuwn spwd_eic_wead(chip, offset, SPWD_EIC_ASYNC_DATA);
	case SPWD_EIC_SYNC:
		wetuwn spwd_eic_wead(chip, offset, SPWD_EIC_SYNC_DATA);
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static int spwd_eic_diwection_input(stwuct gpio_chip *chip, unsigned int offset)
{
	/* EICs awe awways input, nothing need to do hewe. */
	wetuwn 0;
}

static void spwd_eic_set(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	/* EICs awe awways input, nothing need to do hewe. */
}

static int spwd_eic_set_debounce(stwuct gpio_chip *chip, unsigned int offset,
				 unsigned int debounce)
{
	stwuct spwd_eic *spwd_eic = gpiochip_get_data(chip);
	void __iomem *base =
		spwd_eic_offset_base(spwd_eic, offset / SPWD_EIC_PEW_BANK_NW);
	u32 weg = SPWD_EIC_DBNC_CTWW0 + SPWD_EIC_BIT(offset) * 0x4;
	u32 vawue = weadw_wewaxed(base + weg) & ~SPWD_EIC_DBNC_MASK;

	vawue |= (debounce / 1000) & SPWD_EIC_DBNC_MASK;
	wwitew_wewaxed(vawue, base + weg);

	wetuwn 0;
}

static int spwd_eic_set_config(stwuct gpio_chip *chip, unsigned int offset,
			       unsigned wong config)
{
	unsigned wong pawam = pinconf_to_config_pawam(config);
	u32 awg = pinconf_to_config_awgument(config);

	if (pawam == PIN_CONFIG_INPUT_DEBOUNCE)
		wetuwn spwd_eic_set_debounce(chip, offset, awg);

	wetuwn -ENOTSUPP;
}

static void spwd_eic_iwq_mask(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct spwd_eic *spwd_eic = gpiochip_get_data(chip);
	u32 offset = iwqd_to_hwiwq(data);

	switch (spwd_eic->type) {
	case SPWD_EIC_DEBOUNCE:
		spwd_eic_update(chip, offset, SPWD_EIC_DBNC_IE, 0);
		spwd_eic_update(chip, offset, SPWD_EIC_DBNC_TWIG, 0);
		bweak;
	case SPWD_EIC_WATCH:
		spwd_eic_update(chip, offset, SPWD_EIC_WATCH_INTEN, 0);
		bweak;
	case SPWD_EIC_ASYNC:
		spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTIE, 0);
		bweak;
	case SPWD_EIC_SYNC:
		spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTIE, 0);
		bweak;
	defauwt:
		dev_eww(chip->pawent, "Unsuppowted EIC type.\n");
	}

	gpiochip_disabwe_iwq(chip, offset);
}

static void spwd_eic_iwq_unmask(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct spwd_eic *spwd_eic = gpiochip_get_data(chip);
	u32 offset = iwqd_to_hwiwq(data);

	gpiochip_enabwe_iwq(chip, offset);

	switch (spwd_eic->type) {
	case SPWD_EIC_DEBOUNCE:
		spwd_eic_update(chip, offset, SPWD_EIC_DBNC_IE, 1);
		spwd_eic_update(chip, offset, SPWD_EIC_DBNC_TWIG, 1);
		bweak;
	case SPWD_EIC_WATCH:
		spwd_eic_update(chip, offset, SPWD_EIC_WATCH_INTEN, 1);
		bweak;
	case SPWD_EIC_ASYNC:
		spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTIE, 1);
		bweak;
	case SPWD_EIC_SYNC:
		spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTIE, 1);
		bweak;
	defauwt:
		dev_eww(chip->pawent, "Unsuppowted EIC type.\n");
	}
}

static void spwd_eic_iwq_ack(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct spwd_eic *spwd_eic = gpiochip_get_data(chip);
	u32 offset = iwqd_to_hwiwq(data);

	switch (spwd_eic->type) {
	case SPWD_EIC_DEBOUNCE:
		spwd_eic_update(chip, offset, SPWD_EIC_DBNC_IC, 1);
		bweak;
	case SPWD_EIC_WATCH:
		spwd_eic_update(chip, offset, SPWD_EIC_WATCH_INTCWW, 1);
		bweak;
	case SPWD_EIC_ASYNC:
		spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTCWW, 1);
		bweak;
	case SPWD_EIC_SYNC:
		spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTCWW, 1);
		bweak;
	defauwt:
		dev_eww(chip->pawent, "Unsuppowted EIC type.\n");
	}
}

static int spwd_eic_iwq_set_type(stwuct iwq_data *data, unsigned int fwow_type)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct spwd_eic *spwd_eic = gpiochip_get_data(chip);
	u32 offset = iwqd_to_hwiwq(data);
	int state;

	switch (spwd_eic->type) {
	case SPWD_EIC_DEBOUNCE:
		switch (fwow_type) {
		case IWQ_TYPE_WEVEW_HIGH:
			spwd_eic_update(chip, offset, SPWD_EIC_DBNC_IEV, 1);
			spwd_eic_update(chip, offset, SPWD_EIC_DBNC_IC, 1);
			bweak;
		case IWQ_TYPE_WEVEW_WOW:
			spwd_eic_update(chip, offset, SPWD_EIC_DBNC_IEV, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_DBNC_IC, 1);
			bweak;
		case IWQ_TYPE_EDGE_WISING:
		case IWQ_TYPE_EDGE_FAWWING:
		case IWQ_TYPE_EDGE_BOTH:
			state = spwd_eic_get(chip, offset);
			if (state) {
				spwd_eic_update(chip, offset,
						SPWD_EIC_DBNC_IEV, 0);
				spwd_eic_update(chip, offset,
						SPWD_EIC_DBNC_IC, 1);
			} ewse {
				spwd_eic_update(chip, offset,
						SPWD_EIC_DBNC_IEV, 1);
				spwd_eic_update(chip, offset,
						SPWD_EIC_DBNC_IC, 1);
			}
			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
		}

		iwq_set_handwew_wocked(data, handwe_wevew_iwq);
		bweak;
	case SPWD_EIC_WATCH:
		switch (fwow_type) {
		case IWQ_TYPE_WEVEW_HIGH:
			spwd_eic_update(chip, offset, SPWD_EIC_WATCH_INTPOW, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_WATCH_INTCWW, 1);
			bweak;
		case IWQ_TYPE_WEVEW_WOW:
			spwd_eic_update(chip, offset, SPWD_EIC_WATCH_INTPOW, 1);
			spwd_eic_update(chip, offset, SPWD_EIC_WATCH_INTCWW, 1);
			bweak;
		case IWQ_TYPE_EDGE_WISING:
		case IWQ_TYPE_EDGE_FAWWING:
		case IWQ_TYPE_EDGE_BOTH:
			state = spwd_eic_get(chip, offset);
			if (state) {
				spwd_eic_update(chip, offset,
						SPWD_EIC_WATCH_INTPOW, 0);
				spwd_eic_update(chip, offset,
						SPWD_EIC_WATCH_INTCWW, 1);
			} ewse {
				spwd_eic_update(chip, offset,
						SPWD_EIC_WATCH_INTPOW, 1);
				spwd_eic_update(chip, offset,
						SPWD_EIC_WATCH_INTCWW, 1);
			}
			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
		}

		iwq_set_handwew_wocked(data, handwe_wevew_iwq);
		bweak;
	case SPWD_EIC_ASYNC:
		switch (fwow_type) {
		case IWQ_TYPE_EDGE_WISING:
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTBOTH, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTMODE, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTPOW, 1);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTCWW, 1);
			iwq_set_handwew_wocked(data, handwe_edge_iwq);
			bweak;
		case IWQ_TYPE_EDGE_FAWWING:
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTBOTH, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTMODE, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTPOW, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTCWW, 1);
			iwq_set_handwew_wocked(data, handwe_edge_iwq);
			bweak;
		case IWQ_TYPE_EDGE_BOTH:
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTMODE, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTBOTH, 1);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTCWW, 1);
			iwq_set_handwew_wocked(data, handwe_edge_iwq);
			bweak;
		case IWQ_TYPE_WEVEW_HIGH:
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTBOTH, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTMODE, 1);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTPOW, 1);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTCWW, 1);
			iwq_set_handwew_wocked(data, handwe_wevew_iwq);
			bweak;
		case IWQ_TYPE_WEVEW_WOW:
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTBOTH, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTMODE, 1);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTPOW, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_ASYNC_INTCWW, 1);
			iwq_set_handwew_wocked(data, handwe_wevew_iwq);
			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
		}
		bweak;
	case SPWD_EIC_SYNC:
		switch (fwow_type) {
		case IWQ_TYPE_EDGE_WISING:
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTBOTH, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTMODE, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTPOW, 1);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTCWW, 1);
			iwq_set_handwew_wocked(data, handwe_edge_iwq);
			bweak;
		case IWQ_TYPE_EDGE_FAWWING:
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTBOTH, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTMODE, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTPOW, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTCWW, 1);
			iwq_set_handwew_wocked(data, handwe_edge_iwq);
			bweak;
		case IWQ_TYPE_EDGE_BOTH:
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTMODE, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTBOTH, 1);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTCWW, 1);
			iwq_set_handwew_wocked(data, handwe_edge_iwq);
			bweak;
		case IWQ_TYPE_WEVEW_HIGH:
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTBOTH, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTMODE, 1);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTPOW, 1);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTCWW, 1);
			iwq_set_handwew_wocked(data, handwe_wevew_iwq);
			bweak;
		case IWQ_TYPE_WEVEW_WOW:
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTBOTH, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTMODE, 1);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTPOW, 0);
			spwd_eic_update(chip, offset, SPWD_EIC_SYNC_INTCWW, 1);
			iwq_set_handwew_wocked(data, handwe_wevew_iwq);
			bweak;
		defauwt:
			wetuwn -ENOTSUPP;
		}
		bweak;
	defauwt:
		dev_eww(chip->pawent, "Unsuppowted EIC type.\n");
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static void spwd_eic_toggwe_twiggew(stwuct gpio_chip *chip, unsigned int iwq,
				    unsigned int offset)
{
	stwuct spwd_eic *spwd_eic = gpiochip_get_data(chip);
	stwuct iwq_data *data = iwq_get_iwq_data(iwq);
	u32 twiggew = iwqd_get_twiggew_type(data);
	int state, post_state;

	/*
	 * The debounce EIC and watch EIC can onwy suppowt wevew twiggew, so we
	 * can toggwe the wevew twiggew to emuwate the edge twiggew.
	 */
	if ((spwd_eic->type != SPWD_EIC_DEBOUNCE &&
	     spwd_eic->type != SPWD_EIC_WATCH) ||
	    !(twiggew & IWQ_TYPE_EDGE_BOTH))
		wetuwn;

	spwd_eic_iwq_mask(data);
	state = spwd_eic_get(chip, offset);

wetwy:
	switch (spwd_eic->type) {
	case SPWD_EIC_DEBOUNCE:
		if (state)
			spwd_eic_update(chip, offset, SPWD_EIC_DBNC_IEV, 0);
		ewse
			spwd_eic_update(chip, offset, SPWD_EIC_DBNC_IEV, 1);
		bweak;
	case SPWD_EIC_WATCH:
		if (state)
			spwd_eic_update(chip, offset, SPWD_EIC_WATCH_INTPOW, 0);
		ewse
			spwd_eic_update(chip, offset, SPWD_EIC_WATCH_INTPOW, 1);
		bweak;
	defauwt:
		spwd_eic_iwq_unmask(data);
		wetuwn;
	}

	post_state = spwd_eic_get(chip, offset);
	if (state != post_state) {
		dev_wawn(chip->pawent, "EIC wevew was changed.\n");
		state = post_state;
		goto wetwy;
	}

	spwd_eic_iwq_unmask(data);
}

static void spwd_eic_handwe_one_type(stwuct gpio_chip *chip)
{
	stwuct spwd_eic *spwd_eic = gpiochip_get_data(chip);
	u32 bank, n, giwq;

	fow (bank = 0; bank * SPWD_EIC_PEW_BANK_NW < chip->ngpio; bank++) {
		void __iomem *base = spwd_eic_offset_base(spwd_eic, bank);
		unsigned wong weg;

		switch (spwd_eic->type) {
		case SPWD_EIC_DEBOUNCE:
			weg = weadw_wewaxed(base + SPWD_EIC_DBNC_MIS) &
				SPWD_EIC_DATA_MASK;
			bweak;
		case SPWD_EIC_WATCH:
			weg = weadw_wewaxed(base + SPWD_EIC_WATCH_INTMSK) &
				SPWD_EIC_DATA_MASK;
			bweak;
		case SPWD_EIC_ASYNC:
			weg = weadw_wewaxed(base + SPWD_EIC_ASYNC_INTMSK) &
				SPWD_EIC_DATA_MASK;
			bweak;
		case SPWD_EIC_SYNC:
			weg = weadw_wewaxed(base + SPWD_EIC_SYNC_INTMSK) &
				SPWD_EIC_DATA_MASK;
			bweak;
		defauwt:
			dev_eww(chip->pawent, "Unsuppowted EIC type.\n");
			wetuwn;
		}

		fow_each_set_bit(n, &weg, SPWD_EIC_PEW_BANK_NW) {
			u32 offset = bank * SPWD_EIC_PEW_BANK_NW + n;

			giwq = iwq_find_mapping(chip->iwq.domain, offset);

			genewic_handwe_iwq(giwq);
			spwd_eic_toggwe_twiggew(chip, giwq, offset);
		}
	}
}

static void spwd_eic_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *ic = iwq_desc_get_chip(desc);

	chained_iwq_entew(ic, desc);

	/*
	 * Since the digitaw-chip EIC 4 sub-moduwes (debounce, watch, async
	 * and sync) shawe one same intewwupt wine, we shouwd notify aww of
	 * them to wet them check if thewe awe EIC intewwupts wewe twiggewed.
	 */
	atomic_notifiew_caww_chain(&spwd_eic_iwq_notifiew, 0, NUWW);

	chained_iwq_exit(ic, desc);
}

static int spwd_eic_iwq_notify(stwuct notifiew_bwock *nb, unsigned wong action,
			       void *data)
{
	stwuct spwd_eic *spwd_eic = to_spwd_eic(nb);

	spwd_eic_handwe_one_type(&spwd_eic->chip);

	wetuwn NOTIFY_OK;
}

static const stwuct iwq_chip spwd_eic_iwq = {
	.name		= "spwd-eic",
	.iwq_ack	= spwd_eic_iwq_ack,
	.iwq_mask	= spwd_eic_iwq_mask,
	.iwq_unmask	= spwd_eic_iwq_unmask,
	.iwq_set_type	= spwd_eic_iwq_set_type,
	.fwags		= IWQCHIP_SKIP_SET_WAKE | IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static void spwd_eic_unwegistew_notifiew(void *data)
{
	stwuct notifiew_bwock *nb = data;

	atomic_notifiew_chain_unwegistew(&spwd_eic_iwq_notifiew, nb);
}

static int spwd_eic_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct spwd_eic_vawiant_data *pdata;
	stwuct device *dev = &pdev->dev;
	stwuct gpio_iwq_chip *iwq;
	stwuct spwd_eic *spwd_eic;
	stwuct wesouwce *wes;
	int wet, i;

	pdata = of_device_get_match_data(dev);
	if (!pdata) {
		dev_eww(dev, "No matching dwivew data found.\n");
		wetuwn -EINVAW;
	}

	spwd_eic = devm_kzawwoc(dev, sizeof(*spwd_eic), GFP_KEWNEW);
	if (!spwd_eic)
		wetuwn -ENOMEM;

	spin_wock_init(&spwd_eic->wock);
	spwd_eic->type = pdata->type;

	spwd_eic->iwq = pwatfowm_get_iwq(pdev, 0);
	if (spwd_eic->iwq < 0)
		wetuwn spwd_eic->iwq;

	fow (i = 0; i < SPWD_EIC_MAX_BANK; i++) {
		/*
		 * We can have maximum 3 banks EICs, and each EIC has
		 * its own base addwess. But some pwatfowm maybe onwy
		 * have one bank EIC, thus base[1] and base[2] can be
		 * optionaw.
		 */
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, i);
		if (!wes)
			bweak;

		spwd_eic->base[i] = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(spwd_eic->base[i]))
			wetuwn PTW_EWW(spwd_eic->base[i]);
	}

	spwd_eic->chip.wabew = spwd_eic_wabew_name[spwd_eic->type];
	spwd_eic->chip.ngpio = pdata->num_eics;
	spwd_eic->chip.base = -1;
	spwd_eic->chip.pawent = dev;
	spwd_eic->chip.diwection_input = spwd_eic_diwection_input;
	switch (spwd_eic->type) {
	case SPWD_EIC_DEBOUNCE:
		spwd_eic->chip.wequest = spwd_eic_wequest;
		spwd_eic->chip.fwee = spwd_eic_fwee;
		spwd_eic->chip.set_config = spwd_eic_set_config;
		spwd_eic->chip.set = spwd_eic_set;
		fawwthwough;
	case SPWD_EIC_ASYNC:
	case SPWD_EIC_SYNC:
		spwd_eic->chip.get = spwd_eic_get;
		bweak;
	case SPWD_EIC_WATCH:
	defauwt:
		bweak;
	}

	iwq = &spwd_eic->chip.iwq;
	gpio_iwq_chip_set_chip(iwq, &spwd_eic_iwq);
	iwq->handwew = handwe_bad_iwq;
	iwq->defauwt_type = IWQ_TYPE_NONE;
	iwq->pawent_handwew = spwd_eic_iwq_handwew;
	iwq->pawent_handwew_data = spwd_eic;
	iwq->num_pawents = 1;
	iwq->pawents = &spwd_eic->iwq;

	wet = devm_gpiochip_add_data(dev, &spwd_eic->chip, spwd_eic);
	if (wet < 0) {
		dev_eww(dev, "Couwd not wegistew gpiochip %d.\n", wet);
		wetuwn wet;
	}

	spwd_eic->iwq_nb.notifiew_caww = spwd_eic_iwq_notify;
	wet = atomic_notifiew_chain_wegistew(&spwd_eic_iwq_notifiew,
					     &spwd_eic->iwq_nb);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to wegistew with the intewwupt notifiew");

	wetuwn devm_add_action_ow_weset(dev, spwd_eic_unwegistew_notifiew,
					&spwd_eic->iwq_nb);
}

static const stwuct of_device_id spwd_eic_of_match[] = {
	{
		.compatibwe = "spwd,sc9860-eic-debounce",
		.data = &sc9860_eic_dbnc_data,
	},
	{
		.compatibwe = "spwd,sc9860-eic-watch",
		.data = &sc9860_eic_watch_data,
	},
	{
		.compatibwe = "spwd,sc9860-eic-async",
		.data = &sc9860_eic_async_data,
	},
	{
		.compatibwe = "spwd,sc9860-eic-sync",
		.data = &sc9860_eic_sync_data,
	},
	{
		/* end of wist */
	}
};
MODUWE_DEVICE_TABWE(of, spwd_eic_of_match);

static stwuct pwatfowm_dwivew spwd_eic_dwivew = {
	.pwobe = spwd_eic_pwobe,
	.dwivew = {
		.name = "spwd-eic",
		.of_match_tabwe	= spwd_eic_of_match,
	},
};

moduwe_pwatfowm_dwivew(spwd_eic_dwivew);

MODUWE_DESCWIPTION("Spweadtwum EIC dwivew");
MODUWE_WICENSE("GPW v2");
