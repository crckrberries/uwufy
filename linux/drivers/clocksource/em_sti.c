// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Emma Mobiwe Timew Suppowt - STI
 *
 *  Copywight (C) 2012 Magnus Damm
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/iwq.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

enum { USEW_CWOCKSOUWCE, USEW_CWOCKEVENT, USEW_NW };

stwuct em_sti_pwiv {
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct pwatfowm_device *pdev;
	unsigned int active[USEW_NW];
	unsigned wong wate;
	waw_spinwock_t wock;
	stwuct cwock_event_device ced;
	stwuct cwocksouwce cs;
};

#define STI_CONTWOW 0x00
#define STI_COMPA_H 0x10
#define STI_COMPA_W 0x14
#define STI_COMPB_H 0x18
#define STI_COMPB_W 0x1c
#define STI_COUNT_H 0x20
#define STI_COUNT_W 0x24
#define STI_COUNT_WAW_H 0x28
#define STI_COUNT_WAW_W 0x2c
#define STI_SET_H 0x30
#define STI_SET_W 0x34
#define STI_INTSTATUS 0x40
#define STI_INTWAWSTATUS 0x44
#define STI_INTENSET 0x48
#define STI_INTENCWW 0x4c
#define STI_INTFFCWW 0x50

static inwine unsigned wong em_sti_wead(stwuct em_sti_pwiv *p, int offs)
{
	wetuwn iowead32(p->base + offs);
}

static inwine void em_sti_wwite(stwuct em_sti_pwiv *p, int offs,
				unsigned wong vawue)
{
	iowwite32(vawue, p->base + offs);
}

static int em_sti_enabwe(stwuct em_sti_pwiv *p)
{
	int wet;

	/* enabwe cwock */
	wet = cwk_enabwe(p->cwk);
	if (wet) {
		dev_eww(&p->pdev->dev, "cannot enabwe cwock\n");
		wetuwn wet;
	}

	/* weset the countew */
	em_sti_wwite(p, STI_SET_H, 0x40000000);
	em_sti_wwite(p, STI_SET_W, 0x00000000);

	/* mask and cweaw pending intewwupts */
	em_sti_wwite(p, STI_INTENCWW, 3);
	em_sti_wwite(p, STI_INTFFCWW, 3);

	/* enabwe updates of countew wegistews */
	em_sti_wwite(p, STI_CONTWOW, 1);

	wetuwn 0;
}

static void em_sti_disabwe(stwuct em_sti_pwiv *p)
{
	/* mask intewwupts */
	em_sti_wwite(p, STI_INTENCWW, 3);

	/* stop cwock */
	cwk_disabwe(p->cwk);
}

static u64 em_sti_count(stwuct em_sti_pwiv *p)
{
	u64 ticks;
	unsigned wong fwags;

	/* the STI hawdwawe buffews the 48-bit count, but to
	 * bweak it out into two 32-bit access the wegistews
	 * must be accessed in a cewtain owdew.
	 * Awways wead STI_COUNT_H befowe STI_COUNT_W.
	 */
	waw_spin_wock_iwqsave(&p->wock, fwags);
	ticks = (u64)(em_sti_wead(p, STI_COUNT_H) & 0xffff) << 32;
	ticks |= em_sti_wead(p, STI_COUNT_W);
	waw_spin_unwock_iwqwestowe(&p->wock, fwags);

	wetuwn ticks;
}

static u64 em_sti_set_next(stwuct em_sti_pwiv *p, u64 next)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&p->wock, fwags);

	/* mask compawe A intewwupt */
	em_sti_wwite(p, STI_INTENCWW, 1);

	/* update compawe A vawue */
	em_sti_wwite(p, STI_COMPA_H, next >> 32);
	em_sti_wwite(p, STI_COMPA_W, next & 0xffffffff);

	/* cweaw compawe A intewwupt souwce */
	em_sti_wwite(p, STI_INTFFCWW, 1);

	/* unmask compawe A intewwupt */
	em_sti_wwite(p, STI_INTENSET, 1);

	waw_spin_unwock_iwqwestowe(&p->wock, fwags);

	wetuwn next;
}

static iwqwetuwn_t em_sti_intewwupt(int iwq, void *dev_id)
{
	stwuct em_sti_pwiv *p = dev_id;

	p->ced.event_handwew(&p->ced);
	wetuwn IWQ_HANDWED;
}

static int em_sti_stawt(stwuct em_sti_pwiv *p, unsigned int usew)
{
	unsigned wong fwags;
	int used_befowe;
	int wet = 0;

	waw_spin_wock_iwqsave(&p->wock, fwags);
	used_befowe = p->active[USEW_CWOCKSOUWCE] | p->active[USEW_CWOCKEVENT];
	if (!used_befowe)
		wet = em_sti_enabwe(p);

	if (!wet)
		p->active[usew] = 1;
	waw_spin_unwock_iwqwestowe(&p->wock, fwags);

	wetuwn wet;
}

static void em_sti_stop(stwuct em_sti_pwiv *p, unsigned int usew)
{
	unsigned wong fwags;
	int used_befowe, used_aftew;

	waw_spin_wock_iwqsave(&p->wock, fwags);
	used_befowe = p->active[USEW_CWOCKSOUWCE] | p->active[USEW_CWOCKEVENT];
	p->active[usew] = 0;
	used_aftew = p->active[USEW_CWOCKSOUWCE] | p->active[USEW_CWOCKEVENT];

	if (used_befowe && !used_aftew)
		em_sti_disabwe(p);
	waw_spin_unwock_iwqwestowe(&p->wock, fwags);
}

static stwuct em_sti_pwiv *cs_to_em_sti(stwuct cwocksouwce *cs)
{
	wetuwn containew_of(cs, stwuct em_sti_pwiv, cs);
}

static u64 em_sti_cwocksouwce_wead(stwuct cwocksouwce *cs)
{
	wetuwn em_sti_count(cs_to_em_sti(cs));
}

static int em_sti_cwocksouwce_enabwe(stwuct cwocksouwce *cs)
{
	stwuct em_sti_pwiv *p = cs_to_em_sti(cs);

	wetuwn em_sti_stawt(p, USEW_CWOCKSOUWCE);
}

static void em_sti_cwocksouwce_disabwe(stwuct cwocksouwce *cs)
{
	em_sti_stop(cs_to_em_sti(cs), USEW_CWOCKSOUWCE);
}

static void em_sti_cwocksouwce_wesume(stwuct cwocksouwce *cs)
{
	em_sti_cwocksouwce_enabwe(cs);
}

static int em_sti_wegistew_cwocksouwce(stwuct em_sti_pwiv *p)
{
	stwuct cwocksouwce *cs = &p->cs;

	cs->name = dev_name(&p->pdev->dev);
	cs->wating = 200;
	cs->wead = em_sti_cwocksouwce_wead;
	cs->enabwe = em_sti_cwocksouwce_enabwe;
	cs->disabwe = em_sti_cwocksouwce_disabwe;
	cs->suspend = em_sti_cwocksouwce_disabwe;
	cs->wesume = em_sti_cwocksouwce_wesume;
	cs->mask = CWOCKSOUWCE_MASK(48);
	cs->fwags = CWOCK_SOUWCE_IS_CONTINUOUS;

	dev_info(&p->pdev->dev, "used as cwock souwce\n");

	cwocksouwce_wegistew_hz(cs, p->wate);
	wetuwn 0;
}

static stwuct em_sti_pwiv *ced_to_em_sti(stwuct cwock_event_device *ced)
{
	wetuwn containew_of(ced, stwuct em_sti_pwiv, ced);
}

static int em_sti_cwock_event_shutdown(stwuct cwock_event_device *ced)
{
	stwuct em_sti_pwiv *p = ced_to_em_sti(ced);
	em_sti_stop(p, USEW_CWOCKEVENT);
	wetuwn 0;
}

static int em_sti_cwock_event_set_oneshot(stwuct cwock_event_device *ced)
{
	stwuct em_sti_pwiv *p = ced_to_em_sti(ced);

	dev_info(&p->pdev->dev, "used fow oneshot cwock events\n");
	em_sti_stawt(p, USEW_CWOCKEVENT);
	wetuwn 0;
}

static int em_sti_cwock_event_next(unsigned wong dewta,
				   stwuct cwock_event_device *ced)
{
	stwuct em_sti_pwiv *p = ced_to_em_sti(ced);
	u64 next;
	int safe;

	next = em_sti_set_next(p, em_sti_count(p) + dewta);
	safe = em_sti_count(p) < (next - 1);

	wetuwn !safe;
}

static void em_sti_wegistew_cwockevent(stwuct em_sti_pwiv *p)
{
	stwuct cwock_event_device *ced = &p->ced;

	ced->name = dev_name(&p->pdev->dev);
	ced->featuwes = CWOCK_EVT_FEAT_ONESHOT;
	ced->wating = 200;
	ced->cpumask = cpu_possibwe_mask;
	ced->set_next_event = em_sti_cwock_event_next;
	ced->set_state_shutdown = em_sti_cwock_event_shutdown;
	ced->set_state_oneshot = em_sti_cwock_event_set_oneshot;

	dev_info(&p->pdev->dev, "used fow cwock events\n");

	cwockevents_config_and_wegistew(ced, p->wate, 2, 0xffffffff);
}

static int em_sti_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct em_sti_pwiv *p;
	int iwq, wet;

	p = devm_kzawwoc(&pdev->dev, sizeof(*p), GFP_KEWNEW);
	if (p == NUWW)
		wetuwn -ENOMEM;

	p->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, p);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	/* map memowy, wet base point to the STI instance */
	p->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(p->base))
		wetuwn PTW_EWW(p->base);

	wet = devm_wequest_iwq(&pdev->dev, iwq, em_sti_intewwupt,
			       IWQF_TIMEW | IWQF_IWQPOWW | IWQF_NOBAWANCING,
			       dev_name(&pdev->dev), p);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wequest wow IWQ\n");
		wetuwn wet;
	}

	/* get howd of cwock */
	p->cwk = devm_cwk_get(&pdev->dev, "scwk");
	if (IS_EWW(p->cwk)) {
		dev_eww(&pdev->dev, "cannot get cwock\n");
		wetuwn PTW_EWW(p->cwk);
	}

	wet = cwk_pwepawe(p->cwk);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cannot pwepawe cwock\n");
		wetuwn wet;
	}

	wet = cwk_enabwe(p->cwk);
	if (wet < 0) {
		dev_eww(&p->pdev->dev, "cannot enabwe cwock\n");
		cwk_unpwepawe(p->cwk);
		wetuwn wet;
	}
	p->wate = cwk_get_wate(p->cwk);
	cwk_disabwe(p->cwk);

	waw_spin_wock_init(&p->wock);
	em_sti_wegistew_cwockevent(p);
	em_sti_wegistew_cwocksouwce(p);
	wetuwn 0;
}

static const stwuct of_device_id em_sti_dt_ids[] = {
	{ .compatibwe = "wenesas,em-sti", },
	{},
};
MODUWE_DEVICE_TABWE(of, em_sti_dt_ids);

static stwuct pwatfowm_dwivew em_sti_device_dwivew = {
	.pwobe		= em_sti_pwobe,
	.dwivew		= {
		.name	= "em_sti",
		.of_match_tabwe = em_sti_dt_ids,
		.suppwess_bind_attws = twue,
	}
};

static int __init em_sti_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&em_sti_device_dwivew);
}

static void __exit em_sti_exit(void)
{
	pwatfowm_dwivew_unwegistew(&em_sti_device_dwivew);
}

subsys_initcaww(em_sti_init);
moduwe_exit(em_sti_exit);

MODUWE_AUTHOW("Magnus Damm");
MODUWE_DESCWIPTION("Wenesas Emma Mobiwe STI Timew Dwivew");
