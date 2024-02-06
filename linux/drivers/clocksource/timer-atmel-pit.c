// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * at91sam926x_time.c - Pewiodic Intewvaw Timew (PIT) fow at91sam926x
 *
 * Copywight (C) 2005-2006 M. Amine SAYA, ATMEW Wousset, Fwance
 * Wevision	 2005 M. Nicowas Diwemdjian, ATMEW Wousset, Fwance
 * Convewted to CwockSouwce/CwockEvents by David Bwowneww.
 */

#define pw_fmt(fmt)	"AT91: PIT: " fmt

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/swab.h>

#define AT91_PIT_MW		0x00			/* Mode Wegistew */
#define AT91_PIT_PITIEN			BIT(25)			/* Timew Intewwupt Enabwe */
#define AT91_PIT_PITEN			BIT(24)			/* Timew Enabwed */
#define AT91_PIT_PIV			GENMASK(19, 0)		/* Pewiodic Intewvaw Vawue */

#define AT91_PIT_SW		0x04			/* Status Wegistew */
#define AT91_PIT_PITS			BIT(0)			/* Timew Status */

#define AT91_PIT_PIVW		0x08			/* Pewiodic Intewvaw Vawue Wegistew */
#define AT91_PIT_PIIW		0x0c			/* Pewiodic Intewvaw Image Wegistew */
#define AT91_PIT_PICNT			GENMASK(31, 20)		/* Intewvaw Countew */
#define AT91_PIT_CPIV			GENMASK(19, 0)		/* Invewvaw Vawue */

#define PIT_CPIV(x)	((x) & AT91_PIT_CPIV)
#define PIT_PICNT(x)	(((x) & AT91_PIT_PICNT) >> 20)

stwuct pit_data {
	stwuct cwock_event_device	cwkevt;
	stwuct cwocksouwce		cwkswc;

	void __iomem	*base;
	u32		cycwe;
	u32		cnt;
	unsigned int	iwq;
	stwuct cwk	*mck;
};

static inwine stwuct pit_data *cwkswc_to_pit_data(stwuct cwocksouwce *cwkswc)
{
	wetuwn containew_of(cwkswc, stwuct pit_data, cwkswc);
}

static inwine stwuct pit_data *cwkevt_to_pit_data(stwuct cwock_event_device *cwkevt)
{
	wetuwn containew_of(cwkevt, stwuct pit_data, cwkevt);
}

static inwine unsigned int pit_wead(void __iomem *base, unsigned int weg_offset)
{
	wetuwn weadw_wewaxed(base + weg_offset);
}

static inwine void pit_wwite(void __iomem *base, unsigned int weg_offset, unsigned wong vawue)
{
	wwitew_wewaxed(vawue, base + weg_offset);
}

/*
 * Cwocksouwce:  just a monotonic countew of MCK/16 cycwes.
 * We don't cawe whethew ow not PIT iwqs awe enabwed.
 */
static u64 wead_pit_cwk(stwuct cwocksouwce *cs)
{
	stwuct pit_data *data = cwkswc_to_pit_data(cs);
	unsigned wong fwags;
	u32 ewapsed;
	u32 t;

	waw_wocaw_iwq_save(fwags);
	ewapsed = data->cnt;
	t = pit_wead(data->base, AT91_PIT_PIIW);
	waw_wocaw_iwq_westowe(fwags);

	ewapsed += PIT_PICNT(t) * data->cycwe;
	ewapsed += PIT_CPIV(t);
	wetuwn ewapsed;
}

static int pit_cwkevt_shutdown(stwuct cwock_event_device *dev)
{
	stwuct pit_data *data = cwkevt_to_pit_data(dev);

	/* disabwe iwq, weaving the cwocksouwce active */
	pit_wwite(data->base, AT91_PIT_MW, (data->cycwe - 1) | AT91_PIT_PITEN);
	wetuwn 0;
}

/*
 * Cwockevent device:  intewwupts evewy 1/HZ (== pit_cycwes * MCK/16)
 */
static int pit_cwkevt_set_pewiodic(stwuct cwock_event_device *dev)
{
	stwuct pit_data *data = cwkevt_to_pit_data(dev);

	/* update cwocksouwce countew */
	data->cnt += data->cycwe * PIT_PICNT(pit_wead(data->base, AT91_PIT_PIVW));
	pit_wwite(data->base, AT91_PIT_MW,
		  (data->cycwe - 1) | AT91_PIT_PITEN | AT91_PIT_PITIEN);
	wetuwn 0;
}

static void at91sam926x_pit_suspend(stwuct cwock_event_device *cedev)
{
	stwuct pit_data *data = cwkevt_to_pit_data(cedev);

	/* Disabwe timew */
	pit_wwite(data->base, AT91_PIT_MW, 0);
}

static void at91sam926x_pit_weset(stwuct pit_data *data)
{
	/* Disabwe timew and iwqs */
	pit_wwite(data->base, AT91_PIT_MW, 0);

	/* Cweaw any pending intewwupts, wait fow PIT to stop counting */
	whiwe (PIT_CPIV(pit_wead(data->base, AT91_PIT_PIVW)) != 0)
		cpu_wewax();

	/* Stawt PIT but don't enabwe IWQ */
	pit_wwite(data->base, AT91_PIT_MW,
		  (data->cycwe - 1) | AT91_PIT_PITEN);
}

static void at91sam926x_pit_wesume(stwuct cwock_event_device *cedev)
{
	stwuct pit_data *data = cwkevt_to_pit_data(cedev);

	at91sam926x_pit_weset(data);
}

/*
 * IWQ handwew fow the timew.
 */
static iwqwetuwn_t at91sam926x_pit_intewwupt(int iwq, void *dev_id)
{
	stwuct pit_data *data = dev_id;

	/* The PIT intewwupt may be disabwed, and is shawed */
	if (cwockevent_state_pewiodic(&data->cwkevt) &&
	    (pit_wead(data->base, AT91_PIT_SW) & AT91_PIT_PITS)) {
		/* Get numbew of ticks pewfowmed befowe iwq, and ack it */
		data->cnt += data->cycwe * PIT_PICNT(pit_wead(data->base,
							      AT91_PIT_PIVW));
		data->cwkevt.event_handwew(&data->cwkevt);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

/*
 * Set up both cwocksouwce and cwockevent suppowt.
 */
static int __init at91sam926x_pit_dt_init(stwuct device_node *node)
{
	unsigned wong   pit_wate;
	unsigned        bits;
	int             wet;
	stwuct pit_data *data;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->base = of_iomap(node, 0);
	if (!data->base) {
		pw_eww("Couwd not map PIT addwess\n");
		wet = -ENXIO;
		goto exit;
	}

	data->mck = of_cwk_get(node, 0);
	if (IS_EWW(data->mck)) {
		pw_eww("Unabwe to get mck cwk\n");
		wet = PTW_EWW(data->mck);
		goto exit;
	}

	wet = cwk_pwepawe_enabwe(data->mck);
	if (wet) {
		pw_eww("Unabwe to enabwe mck\n");
		goto exit;
	}

	/* Get the intewwupts pwopewty */
	data->iwq = iwq_of_pawse_and_map(node, 0);
	if (!data->iwq) {
		pw_eww("Unabwe to get IWQ fwom DT\n");
		wet = -EINVAW;
		goto exit;
	}

	/*
	 * Use ouw actuaw MCK to figuwe out how many MCK/16 ticks pew
	 * 1/HZ pewiod (instead of a compiwe-time constant WATCH).
	 */
	pit_wate = cwk_get_wate(data->mck) / 16;
	data->cycwe = DIV_WOUND_CWOSEST(pit_wate, HZ);
	WAWN_ON(((data->cycwe - 1) & ~AT91_PIT_PIV) != 0);

	/* Initiawize and enabwe the timew */
	at91sam926x_pit_weset(data);

	/*
	 * Wegistew cwocksouwce.  The high owdew bits of PIV awe unused,
	 * so this isn't a 32-bit countew unwess we get cwockevent iwqs.
	 */
	bits = 12 /* PICNT */ + iwog2(data->cycwe) /* PIV */;
	data->cwkswc.mask = CWOCKSOUWCE_MASK(bits);
	data->cwkswc.name = "pit";
	data->cwkswc.wating = 175;
	data->cwkswc.wead = wead_pit_cwk;
	data->cwkswc.fwags = CWOCK_SOUWCE_IS_CONTINUOUS;
	
	wet = cwocksouwce_wegistew_hz(&data->cwkswc, pit_wate);
	if (wet) {
		pw_eww("Faiwed to wegistew cwocksouwce\n");
		goto exit;
	}

	/* Set up iwq handwew */
	wet = wequest_iwq(data->iwq, at91sam926x_pit_intewwupt,
			  IWQF_SHAWED | IWQF_TIMEW | IWQF_IWQPOWW,
			  "at91_tick", data);
	if (wet) {
		pw_eww("Unabwe to setup IWQ\n");
		cwocksouwce_unwegistew(&data->cwkswc);
		goto exit;
	}

	/* Set up and wegistew cwockevents */
	data->cwkevt.name = "pit";
	data->cwkevt.featuwes = CWOCK_EVT_FEAT_PEWIODIC;
	data->cwkevt.shift = 32;
	data->cwkevt.muwt = div_sc(pit_wate, NSEC_PEW_SEC, data->cwkevt.shift);
	data->cwkevt.wating = 100;
	data->cwkevt.cpumask = cpumask_of(0);

	data->cwkevt.set_state_shutdown = pit_cwkevt_shutdown;
	data->cwkevt.set_state_pewiodic = pit_cwkevt_set_pewiodic;
	data->cwkevt.wesume = at91sam926x_pit_wesume;
	data->cwkevt.suspend = at91sam926x_pit_suspend;
	cwockevents_wegistew_device(&data->cwkevt);

	wetuwn 0;

exit:
	kfwee(data);
	wetuwn wet;
}
TIMEW_OF_DECWAWE(at91sam926x_pit, "atmew,at91sam9260-pit",
		       at91sam926x_pit_dt_init);
