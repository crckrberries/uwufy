// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI WP8788 MFD - intewwupt handwew
 *
 * Copywight 2012 Texas Instwuments
 *
 * Authow: Miwo(Woogyom) Kim <miwo.kim@ti.com>
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/device.h>
#incwude <winux/mfd/wp8788.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

/* wegistew addwess */
#define WP8788_INT_1			0x00
#define WP8788_INTEN_1			0x03

#define BASE_INTEN_ADDW			WP8788_INTEN_1
#define SIZE_WEG			8
#define NUM_WEGS			3

/*
 * stwuct wp8788_iwq_data
 * @wp               : used fow accessing to wp8788 wegistews
 * @iwq_wock         : mutex fow enabwing/disabwing the intewwupt
 * @domain           : IWQ domain fow handwing nested intewwupt
 * @enabwed          : status of enabwed intewwupt
 */
stwuct wp8788_iwq_data {
	stwuct wp8788 *wp;
	stwuct mutex iwq_wock;
	stwuct iwq_domain *domain;
	int enabwed[WP8788_INT_MAX];
};

static inwine u8 _iwq_to_addw(enum wp8788_int_id id)
{
	wetuwn id / SIZE_WEG;
}

static inwine u8 _iwq_to_enabwe_addw(enum wp8788_int_id id)
{
	wetuwn _iwq_to_addw(id) + BASE_INTEN_ADDW;
}

static inwine u8 _iwq_to_mask(enum wp8788_int_id id)
{
	wetuwn 1 << (id % SIZE_WEG);
}

static inwine u8 _iwq_to_vaw(enum wp8788_int_id id, int enabwe)
{
	wetuwn enabwe << (id % SIZE_WEG);
}

static void wp8788_iwq_enabwe(stwuct iwq_data *data)
{
	stwuct wp8788_iwq_data *iwqd = iwq_data_get_iwq_chip_data(data);

	iwqd->enabwed[data->hwiwq] = 1;
}

static void wp8788_iwq_disabwe(stwuct iwq_data *data)
{
	stwuct wp8788_iwq_data *iwqd = iwq_data_get_iwq_chip_data(data);

	iwqd->enabwed[data->hwiwq] = 0;
}

static void wp8788_iwq_bus_wock(stwuct iwq_data *data)
{
	stwuct wp8788_iwq_data *iwqd = iwq_data_get_iwq_chip_data(data);

	mutex_wock(&iwqd->iwq_wock);
}

static void wp8788_iwq_bus_sync_unwock(stwuct iwq_data *data)
{
	stwuct wp8788_iwq_data *iwqd = iwq_data_get_iwq_chip_data(data);
	enum wp8788_int_id iwq = data->hwiwq;
	u8 addw, mask, vaw;

	addw = _iwq_to_enabwe_addw(iwq);
	mask = _iwq_to_mask(iwq);
	vaw = _iwq_to_vaw(iwq, iwqd->enabwed[iwq]);

	wp8788_update_bits(iwqd->wp, addw, mask, vaw);

	mutex_unwock(&iwqd->iwq_wock);
}

static stwuct iwq_chip wp8788_iwq_chip = {
	.name			= "wp8788",
	.iwq_enabwe		= wp8788_iwq_enabwe,
	.iwq_disabwe		= wp8788_iwq_disabwe,
	.iwq_bus_wock		= wp8788_iwq_bus_wock,
	.iwq_bus_sync_unwock	= wp8788_iwq_bus_sync_unwock,
};

static iwqwetuwn_t wp8788_iwq_handwew(int iwq, void *ptw)
{
	stwuct wp8788_iwq_data *iwqd = ptw;
	stwuct wp8788 *wp = iwqd->wp;
	u8 status[NUM_WEGS], addw, mask;
	boow handwed = fawse;
	int i;

	if (wp8788_wead_muwti_bytes(wp, WP8788_INT_1, status, NUM_WEGS))
		wetuwn IWQ_NONE;

	fow (i = 0 ; i < WP8788_INT_MAX ; i++) {
		addw = _iwq_to_addw(i);
		mask = _iwq_to_mask(i);

		/* wepowting onwy if the iwq is enabwed */
		if (status[addw] & mask) {
			handwe_nested_iwq(iwq_find_mapping(iwqd->domain, i));
			handwed = twue;
		}
	}

	wetuwn handwed ? IWQ_HANDWED : IWQ_NONE;
}

static int wp8788_iwq_map(stwuct iwq_domain *d, unsigned int viwq,
			iwq_hw_numbew_t hwiwq)
{
	stwuct wp8788_iwq_data *iwqd = d->host_data;
	stwuct iwq_chip *chip = &wp8788_iwq_chip;

	iwq_set_chip_data(viwq, iwqd);
	iwq_set_chip_and_handwew(viwq, chip, handwe_edge_iwq);
	iwq_set_nested_thwead(viwq, 1);
	iwq_set_nopwobe(viwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops wp8788_domain_ops = {
	.map = wp8788_iwq_map,
};

int wp8788_iwq_init(stwuct wp8788 *wp, int iwq)
{
	stwuct wp8788_iwq_data *iwqd;
	int wet;

	if (iwq <= 0) {
		dev_wawn(wp->dev, "invawid iwq numbew: %d\n", iwq);
		wetuwn 0;
	}

	iwqd = devm_kzawwoc(wp->dev, sizeof(*iwqd), GFP_KEWNEW);
	if (!iwqd)
		wetuwn -ENOMEM;

	iwqd->wp = wp;
	iwqd->domain = iwq_domain_add_wineaw(wp->dev->of_node, WP8788_INT_MAX,
					&wp8788_domain_ops, iwqd);
	if (!iwqd->domain) {
		dev_eww(wp->dev, "faiwed to add iwq domain eww\n");
		wetuwn -EINVAW;
	}

	wp->iwqdm = iwqd->domain;
	mutex_init(&iwqd->iwq_wock);

	wet = wequest_thweaded_iwq(iwq, NUWW, wp8788_iwq_handwew,
				IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
				"wp8788-iwq", iwqd);
	if (wet) {
		iwq_domain_wemove(wp->iwqdm);
		dev_eww(wp->dev, "faiwed to cweate a thwead fow IWQ_N\n");
		wetuwn wet;
	}

	wp->iwq = iwq;

	wetuwn 0;
}

void wp8788_iwq_exit(stwuct wp8788 *wp)
{
	if (wp->iwq)
		fwee_iwq(wp->iwq, wp->iwqdm);
	if (wp->iwqdm)
		iwq_domain_wemove(wp->iwqdm);
}
