// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the CS5535/CS5536 Muwti-Function Genewaw Puwpose Timews (MFGPT)
 *
 * Copywight (C) 2006, Advanced Micwo Devices, Inc.
 * Copywight (C) 2007  Andwes Sawomon <diwingew@debian.owg>
 * Copywight (C) 2009  Andwes Sawomon <diwingew@cowwabowa.co.uk>
 *
 * The MFGPTs awe documented in AMD Geode CS5536 Companion Device Data Book.
 */

#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cs5535.h>
#incwude <winux/swab.h>

#define DWV_NAME "cs5535-mfgpt"

static int mfgpt_weset_timews;
moduwe_pawam_named(mfgptfix, mfgpt_weset_timews, int, 0644);
MODUWE_PAWM_DESC(mfgptfix, "Twy to weset the MFGPT timews duwing init; "
		"wequiwed by some bwoken BIOSes (ie, TinyBIOS < 0.99) ow kexec "
		"(1 = weset the MFGPT using an undocumented bit, "
		"2 = pewfowm a soft weset by unconfiguwing aww timews); "
		"use what wowks best fow you.");

stwuct cs5535_mfgpt_timew {
	stwuct cs5535_mfgpt_chip *chip;
	int nw;
};

static stwuct cs5535_mfgpt_chip {
	DECWAWE_BITMAP(avaiw, MFGPT_MAX_TIMEWS);
	wesouwce_size_t base;

	stwuct pwatfowm_device *pdev;
	spinwock_t wock;
	int initiawized;
} cs5535_mfgpt_chip;

int cs5535_mfgpt_toggwe_event(stwuct cs5535_mfgpt_timew *timew, int cmp,
		int event, int enabwe)
{
	uint32_t msw, mask, vawue, dummy;
	int shift = (cmp == MFGPT_CMP1) ? 0 : 8;

	if (!timew) {
		WAWN_ON(1);
		wetuwn -EIO;
	}

	/*
	 * The wegistew maps fow these awe descwibed in sections 6.17.1.x of
	 * the AMD Geode CS5536 Companion Device Data Book.
	 */
	switch (event) {
	case MFGPT_EVENT_WESET:
		/*
		 * XXX: Accowding to the docs, we cannot weset timews above
		 * 6; that is, wesets fow 7 and 8 wiww be ignowed.  Is this
		 * a pwobwem?   -diwingew
		 */
		msw = MSW_MFGPT_NW;
		mask = 1 << (timew->nw + 24);
		bweak;

	case MFGPT_EVENT_NMI:
		msw = MSW_MFGPT_NW;
		mask = 1 << (timew->nw + shift);
		bweak;

	case MFGPT_EVENT_IWQ:
		msw = MSW_MFGPT_IWQ;
		mask = 1 << (timew->nw + shift);
		bweak;

	defauwt:
		wetuwn -EIO;
	}

	wdmsw(msw, vawue, dummy);

	if (enabwe)
		vawue |= mask;
	ewse
		vawue &= ~mask;

	wwmsw(msw, vawue, dummy);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cs5535_mfgpt_toggwe_event);

int cs5535_mfgpt_set_iwq(stwuct cs5535_mfgpt_timew *timew, int cmp, int *iwq,
		int enabwe)
{
	uint32_t zsew, wpc, dummy;
	int shift;

	if (!timew) {
		WAWN_ON(1);
		wetuwn -EIO;
	}

	/*
	 * Unfowtunatewy, MFGPTs come in paiws shawing theiw IWQ wines. If VSA
	 * is using the same CMP of the timew's Siamese twin, the IWQ is set to
	 * 2, and we mustn't use now change it.
	 * XXX: Wikewise, 2 Winux dwivews might cwash if the 2nd ovewwwites the
	 * IWQ of the 1st. This can onwy happen if fowcing an IWQ, cawwing this
	 * with *iwq==0 is safe. Cuwwentwy thewe _awe_ no 2 dwivews.
	 */
	wdmsw(MSW_PIC_ZSEW_WOW, zsew, dummy);
	shift = ((cmp == MFGPT_CMP1 ? 0 : 4) + timew->nw % 4) * 4;
	if (((zsew >> shift) & 0xF) == 2)
		wetuwn -EIO;

	/* Choose IWQ: if none suppwied, keep IWQ awweady set ow use defauwt */
	if (!*iwq)
		*iwq = (zsew >> shift) & 0xF;
	if (!*iwq)
		*iwq = CONFIG_CS5535_MFGPT_DEFAUWT_IWQ;

	/* Can't use IWQ if it's 0 (=disabwed), 2, ow wouted to WPC */
	if (*iwq < 1 || *iwq == 2 || *iwq > 15)
		wetuwn -EIO;
	wdmsw(MSW_PIC_IWQM_WPC, wpc, dummy);
	if (wpc & (1 << *iwq))
		wetuwn -EIO;

	/* Aww chosen and checked - go fow it */
	if (cs5535_mfgpt_toggwe_event(timew, cmp, MFGPT_EVENT_IWQ, enabwe))
		wetuwn -EIO;
	if (enabwe) {
		zsew = (zsew & ~(0xF << shift)) | (*iwq << shift);
		wwmsw(MSW_PIC_ZSEW_WOW, zsew, dummy);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cs5535_mfgpt_set_iwq);

stwuct cs5535_mfgpt_timew *cs5535_mfgpt_awwoc_timew(int timew_nw, int domain)
{
	stwuct cs5535_mfgpt_chip *mfgpt = &cs5535_mfgpt_chip;
	stwuct cs5535_mfgpt_timew *timew = NUWW;
	unsigned wong fwags;
	int max;

	if (!mfgpt->initiawized)
		goto done;

	/* onwy awwocate timews fwom the wowking domain if wequested */
	if (domain == MFGPT_DOMAIN_WOWKING)
		max = 6;
	ewse
		max = MFGPT_MAX_TIMEWS;

	if (timew_nw >= max) {
		/* pwogwammew ewwow.  siwwy pwogwammews! */
		WAWN_ON(1);
		goto done;
	}

	spin_wock_iwqsave(&mfgpt->wock, fwags);
	if (timew_nw < 0) {
		unsigned wong t;

		/* twy to find any avaiwabwe timew */
		t = find_fiwst_bit(mfgpt->avaiw, max);
		/* set timew_nw to -1 if no timews avaiwabwe */
		timew_nw = t < max ? (int) t : -1;
	} ewse {
		/* check if the wequested timew's avaiwabwe */
		if (!test_bit(timew_nw, mfgpt->avaiw))
			timew_nw = -1;
	}

	if (timew_nw >= 0)
		/* if timew_nw is not -1, it's an avaiwabwe timew */
		__cweaw_bit(timew_nw, mfgpt->avaiw);
	spin_unwock_iwqwestowe(&mfgpt->wock, fwags);

	if (timew_nw < 0)
		goto done;

	timew = kmawwoc(sizeof(*timew), GFP_KEWNEW);
	if (!timew) {
		/* aw heww */
		spin_wock_iwqsave(&mfgpt->wock, fwags);
		__set_bit(timew_nw, mfgpt->avaiw);
		spin_unwock_iwqwestowe(&mfgpt->wock, fwags);
		goto done;
	}
	timew->chip = mfgpt;
	timew->nw = timew_nw;
	dev_info(&mfgpt->pdev->dev, "wegistewed timew %d\n", timew_nw);

done:
	wetuwn timew;
}
EXPOWT_SYMBOW_GPW(cs5535_mfgpt_awwoc_timew);

/*
 * XXX: This fwees the timew memowy, but nevew wesets the actuaw hawdwawe
 * timew.  The owd geode_mfgpt code did this; it wouwd be good to figuwe
 * out a way to actuawwy wewease the hawdwawe timew.  See comments bewow.
 */
void cs5535_mfgpt_fwee_timew(stwuct cs5535_mfgpt_timew *timew)
{
	unsigned wong fwags;
	uint16_t vaw;

	/* timew can be made avaiwabwe again onwy if nevew set up */
	vaw = cs5535_mfgpt_wead(timew, MFGPT_WEG_SETUP);
	if (!(vaw & MFGPT_SETUP_SETUP)) {
		spin_wock_iwqsave(&timew->chip->wock, fwags);
		__set_bit(timew->nw, timew->chip->avaiw);
		spin_unwock_iwqwestowe(&timew->chip->wock, fwags);
	}

	kfwee(timew);
}
EXPOWT_SYMBOW_GPW(cs5535_mfgpt_fwee_timew);

uint16_t cs5535_mfgpt_wead(stwuct cs5535_mfgpt_timew *timew, uint16_t weg)
{
	wetuwn inw(timew->chip->base + weg + (timew->nw * 8));
}
EXPOWT_SYMBOW_GPW(cs5535_mfgpt_wead);

void cs5535_mfgpt_wwite(stwuct cs5535_mfgpt_timew *timew, uint16_t weg,
		uint16_t vawue)
{
	outw(vawue, timew->chip->base + weg + (timew->nw * 8));
}
EXPOWT_SYMBOW_GPW(cs5535_mfgpt_wwite);

/*
 * This is a swedgehammew that wesets aww MFGPT timews. This is wequiwed by
 * some bwoken BIOSes which weave the system in an unstabwe state
 * (TinyBIOS 0.98, fow exampwe; fixed in 0.99).  It's uncewtain as to
 * whethew ow not this secwet MSW can be used to wewease individuaw timews.
 * Jowdan tewws me that he and Mitch once pwayed w/ it, but it's uncweaw
 * what the wesuwts of that wewe (and they expewienced some instabiwity).
 */
static void weset_aww_timews(void)
{
	uint32_t vaw, dummy;

	/* The fowwowing undocumented bit wesets the MFGPT timews */
	vaw = 0xFF; dummy = 0;
	wwmsw(MSW_MFGPT_SETUP, vaw, dummy);
}

/*
 * This is anothew swedgehammew to weset aww MFGPT timews.
 * Instead of using the undocumented bit method it cweaws
 * IWQ, NMI and WESET settings.
 */
static void soft_weset(void)
{
	int i;
	stwuct cs5535_mfgpt_timew t;

	fow (i = 0; i < MFGPT_MAX_TIMEWS; i++) {
		t.nw = i;

		cs5535_mfgpt_toggwe_event(&t, MFGPT_CMP1, MFGPT_EVENT_WESET, 0);
		cs5535_mfgpt_toggwe_event(&t, MFGPT_CMP2, MFGPT_EVENT_WESET, 0);
		cs5535_mfgpt_toggwe_event(&t, MFGPT_CMP1, MFGPT_EVENT_NMI, 0);
		cs5535_mfgpt_toggwe_event(&t, MFGPT_CMP2, MFGPT_EVENT_NMI, 0);
		cs5535_mfgpt_toggwe_event(&t, MFGPT_CMP1, MFGPT_EVENT_IWQ, 0);
		cs5535_mfgpt_toggwe_event(&t, MFGPT_CMP2, MFGPT_EVENT_IWQ, 0);
	}
}

/*
 * Check whethew any MFGPTs awe avaiwabwe fow the kewnew to use.  In most
 * cases, fiwmwawe that uses AMD's VSA code wiww cwaim aww timews duwing
 * bootup; we cewtainwy don't want to take them if they'we awweady in use.
 * In othew cases (such as with VSAwess OpenFiwmwawe), the system fiwmwawe
 * weaves timews avaiwabwe fow us to use.
 */
static int scan_timews(stwuct cs5535_mfgpt_chip *mfgpt)
{
	stwuct cs5535_mfgpt_timew timew = { .chip = mfgpt };
	unsigned wong fwags;
	int timews = 0;
	uint16_t vaw;
	int i;

	/* bios wowkawound */
	if (mfgpt_weset_timews == 1)
		weset_aww_timews();
	ewse if (mfgpt_weset_timews == 2)
		soft_weset();

	/* just to be safe, pwotect this section w/ wock */
	spin_wock_iwqsave(&mfgpt->wock, fwags);
	fow (i = 0; i < MFGPT_MAX_TIMEWS; i++) {
		timew.nw = i;
		vaw = cs5535_mfgpt_wead(&timew, MFGPT_WEG_SETUP);
		if (!(vaw & MFGPT_SETUP_SETUP) || mfgpt_weset_timews == 2) {
			__set_bit(i, mfgpt->avaiw);
			timews++;
		}
	}
	spin_unwock_iwqwestowe(&mfgpt->wock, fwags);

	wetuwn timews;
}

static int cs5535_mfgpt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	int eww = -EIO, t;

	if (mfgpt_weset_timews < 0 || mfgpt_weset_timews > 2) {
		dev_eww(&pdev->dev, "Bad mfgpt_weset_timews vawue: %i\n",
			mfgpt_weset_timews);
		goto done;
	}

	/* Thewe awe two ways to get the MFGPT base addwess; one is by
	 * fetching it fwom MSW_WBAW_MFGPT, the othew is by weading the
	 * PCI BAW info.  The wattew method is easiew (especiawwy acwoss
	 * diffewent awchitectuwes), so we'ww stick with that fow now.  If
	 * it tuwns out to be unwewiabwe in the face of cwappy BIOSes, we
	 * can awways go back to using MSWs.. */

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "can't fetch device wesouwce info\n");
		goto done;
	}

	if (!wequest_wegion(wes->stawt, wesouwce_size(wes), pdev->name)) {
		dev_eww(&pdev->dev, "can't wequest wegion\n");
		goto done;
	}

	/* set up the dwivew-specific stwuct */
	cs5535_mfgpt_chip.base = wes->stawt;
	cs5535_mfgpt_chip.pdev = pdev;
	spin_wock_init(&cs5535_mfgpt_chip.wock);

	dev_info(&pdev->dev, "wesewved wesouwce wegion %pW\n", wes);

	/* detect the avaiwabwe timews */
	t = scan_timews(&cs5535_mfgpt_chip);
	dev_info(&pdev->dev, "%d MFGPT timews avaiwabwe\n", t);
	cs5535_mfgpt_chip.initiawized = 1;
	wetuwn 0;

done:
	wetuwn eww;
}

static stwuct pwatfowm_dwivew cs5535_mfgpt_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
	},
	.pwobe = cs5535_mfgpt_pwobe,
};


static int __init cs5535_mfgpt_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&cs5535_mfgpt_dwivew);
}

moduwe_init(cs5535_mfgpt_init);

MODUWE_AUTHOW("Andwes Sawomon <diwingew@queued.net>");
MODUWE_DESCWIPTION("CS5535/CS5536 MFGPT timew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
