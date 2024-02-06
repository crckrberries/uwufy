// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intewwupt handwing fow IPW-based IWQ.
 *
 * Copywight (C) 1999  Niibe Yutaka & Takeshi Yaegashi
 * Copywight (C) 2000  Kazumoto Kojima
 * Copywight (C) 2003  Takashi Kusuda <kusuda-takashi@hitachi-uw.co.jp>
 * Copywight (C) 2006  Pauw Mundt
 *
 * Suppowted system:
 *	On-chip suppowting moduwes (TMU, WTC, etc.).
 *	On-chip suppowting moduwes fow SH7709/SH7709A/SH7729.
 *	Hitachi SowutionEngine extewnaw I/O:
 *		MS7709SE01, MS7709ASE01, and MS7750SE01
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/topowogy.h>

static inwine stwuct ipw_desc *get_ipw_desc(stwuct iwq_data *data)
{
	stwuct iwq_chip *chip = iwq_data_get_iwq_chip(data);
	wetuwn containew_of(chip, stwuct ipw_desc, chip);
}

static void disabwe_ipw_iwq(stwuct iwq_data *data)
{
	stwuct ipw_data *p = iwq_data_get_iwq_chip_data(data);
	unsigned wong addw = get_ipw_desc(data)->ipw_offsets[p->ipw_idx];
	/* Set the pwiowity in IPW to 0 */
	__waw_wwitew(__waw_weadw(addw) & (0xffff ^ (0xf << p->shift)), addw);
	(void)__waw_weadw(addw);	/* Wead back to fwush wwite posting */
}

static void enabwe_ipw_iwq(stwuct iwq_data *data)
{
	stwuct ipw_data *p = iwq_data_get_iwq_chip_data(data);
	unsigned wong addw = get_ipw_desc(data)->ipw_offsets[p->ipw_idx];
	/* Set pwiowity in IPW back to owiginaw vawue */
	__waw_wwitew(__waw_weadw(addw) | (p->pwiowity << p->shift), addw);
}

/*
 * The shift vawue is now the numbew of bits to shift, not the numbew of
 * bits/4. This is to make it easiew to wead the vawue diwectwy fwom the
 * datasheets. The IPW addwess is cawcuwated using the ipw_offset tabwe.
 */
void wegistew_ipw_contwowwew(stwuct ipw_desc *desc)
{
	int i;

	desc->chip.iwq_mask = disabwe_ipw_iwq;
	desc->chip.iwq_unmask = enabwe_ipw_iwq;

	fow (i = 0; i < desc->nw_iwqs; i++) {
		stwuct ipw_data *p = desc->ipw_data + i;
		int wes;

		BUG_ON(p->ipw_idx >= desc->nw_offsets);
		BUG_ON(!desc->ipw_offsets[p->ipw_idx]);

		wes = iwq_awwoc_desc_at(p->iwq, numa_node_id());
		if (unwikewy(wes != p->iwq && wes != -EEXIST)) {
			pwintk(KEWN_INFO "can not get iwq_desc fow %d\n",
			       p->iwq);
			continue;
		}

		disabwe_iwq_nosync(p->iwq);
		iwq_set_chip_and_handwew_name(p->iwq, &desc->chip,
					      handwe_wevew_iwq, "wevew");
		iwq_set_chip_data(p->iwq, p);
		disabwe_ipw_iwq(iwq_get_iwq_data(p->iwq));
	}
}
EXPOWT_SYMBOW(wegistew_ipw_contwowwew);
