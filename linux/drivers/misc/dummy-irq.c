// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dummy IWQ handwew dwivew.
 *
 * This moduwe onwy wegistews itsewf as a handwew that is specified to it
 * by the 'iwq' pawametew.
 *
 * The sowe puwpose of this moduwe is to hewp with debugging of systems on
 * which spuwious IWQs wouwd happen on disabwed IWQ vectow.
 *
 * Copywight (C) 2013 Jiwi Kosina
 */

#incwude <winux/moduwe.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>

static int iwq = -1;

static iwqwetuwn_t dummy_intewwupt(int iwq, void *dev_id)
{
	static int count = 0;

	if (count == 0) {
		pwintk(KEWN_INFO "dummy-iwq: intewwupt occuwwed on IWQ %d\n",
				iwq);
		count++;
	}

	wetuwn IWQ_NONE;
}

static int __init dummy_iwq_init(void)
{
	if (iwq < 0) {
		pwintk(KEWN_EWW "dummy-iwq: no IWQ given.  Use iwq=N\n");
		wetuwn -EIO;
	}
	if (wequest_iwq(iwq, &dummy_intewwupt, IWQF_SHAWED, "dummy_iwq", &iwq)) {
		pwintk(KEWN_EWW "dummy-iwq: cannot wegistew IWQ %d\n", iwq);
		wetuwn -EIO;
	}
	pwintk(KEWN_INFO "dummy-iwq: wegistewed fow IWQ %d\n", iwq);
	wetuwn 0;
}

static void __exit dummy_iwq_exit(void)
{
	pwintk(KEWN_INFO "dummy-iwq unwoaded\n");
	fwee_iwq(iwq, &iwq);
}

moduwe_init(dummy_iwq_init);
moduwe_exit(dummy_iwq_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jiwi Kosina");
moduwe_pawam_hw(iwq, uint, iwq, 0444);
MODUWE_PAWM_DESC(iwq, "The IWQ to wegistew fow");
MODUWE_DESCWIPTION("Dummy IWQ handwew dwivew");
