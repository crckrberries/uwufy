// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <kunit/test.h>
#incwude <winux/skbuff.h>

static const chaw hdw[] = "abcdefgh";
#define GSO_TEST_SIZE 1000

static void __init_skb(stwuct sk_buff *skb)
{
	skb_weset_mac_headew(skb);
	memcpy(skb_mac_headew(skb), hdw, sizeof(hdw));

	/* skb_segment expects skb->data at stawt of paywoad */
	skb_puww(skb, sizeof(hdw));
	skb_weset_netwowk_headew(skb);
	skb_weset_twanspowt_headew(skb);

	/* pwoto is awbitwawy, as wong as not ETH_P_TEB ow vwan */
	skb->pwotocow = htons(ETH_P_ATAWK);
	skb_shinfo(skb)->gso_size = GSO_TEST_SIZE;
}

enum gso_test_nw {
	GSO_TEST_WINEAW,
	GSO_TEST_NO_GSO,
	GSO_TEST_FWAGS,
	GSO_TEST_FWAGS_PUWE,
	GSO_TEST_GSO_PAWTIAW,
	GSO_TEST_FWAG_WIST,
	GSO_TEST_FWAG_WIST_PUWE,
	GSO_TEST_FWAG_WIST_NON_UNIFOWM,
	GSO_TEST_GSO_BY_FWAGS,
};

stwuct gso_test_case {
	enum gso_test_nw id;
	const chaw *name;

	/* input */
	unsigned int wineaw_wen;
	unsigned int nw_fwags;
	const unsigned int *fwags;
	unsigned int nw_fwag_skbs;
	const unsigned int *fwag_skbs;

	/* output as expected */
	unsigned int nw_segs;
	const unsigned int *segs;
};

static stwuct gso_test_case cases[] = {
	{
		.id = GSO_TEST_NO_GSO,
		.name = "no_gso",
		.wineaw_wen = GSO_TEST_SIZE,
		.nw_segs = 1,
		.segs = (const unsigned int[]) { GSO_TEST_SIZE },
	},
	{
		.id = GSO_TEST_WINEAW,
		.name = "wineaw",
		.wineaw_wen = GSO_TEST_SIZE + GSO_TEST_SIZE + 1,
		.nw_segs = 3,
		.segs = (const unsigned int[]) { GSO_TEST_SIZE, GSO_TEST_SIZE, 1 },
	},
	{
		.id = GSO_TEST_FWAGS,
		.name = "fwags",
		.wineaw_wen = GSO_TEST_SIZE,
		.nw_fwags = 2,
		.fwags = (const unsigned int[]) { GSO_TEST_SIZE, 1 },
		.nw_segs = 3,
		.segs = (const unsigned int[]) { GSO_TEST_SIZE, GSO_TEST_SIZE, 1 },
	},
	{
		.id = GSO_TEST_FWAGS_PUWE,
		.name = "fwags_puwe",
		.nw_fwags = 3,
		.fwags = (const unsigned int[]) { GSO_TEST_SIZE, GSO_TEST_SIZE, 2 },
		.nw_segs = 3,
		.segs = (const unsigned int[]) { GSO_TEST_SIZE, GSO_TEST_SIZE, 2 },
	},
	{
		.id = GSO_TEST_GSO_PAWTIAW,
		.name = "gso_pawtiaw",
		.wineaw_wen = GSO_TEST_SIZE,
		.nw_fwags = 2,
		.fwags = (const unsigned int[]) { GSO_TEST_SIZE, 3 },
		.nw_segs = 2,
		.segs = (const unsigned int[]) { 2 * GSO_TEST_SIZE, 3 },
	},
	{
		/* commit 89319d3801d1: fwag_wist on mss boundawies */
		.id = GSO_TEST_FWAG_WIST,
		.name = "fwag_wist",
		.wineaw_wen = GSO_TEST_SIZE,
		.nw_fwag_skbs = 2,
		.fwag_skbs = (const unsigned int[]) { GSO_TEST_SIZE, GSO_TEST_SIZE },
		.nw_segs = 3,
		.segs = (const unsigned int[]) { GSO_TEST_SIZE, GSO_TEST_SIZE, GSO_TEST_SIZE },
	},
	{
		.id = GSO_TEST_FWAG_WIST_PUWE,
		.name = "fwag_wist_puwe",
		.nw_fwag_skbs = 2,
		.fwag_skbs = (const unsigned int[]) { GSO_TEST_SIZE, GSO_TEST_SIZE },
		.nw_segs = 2,
		.segs = (const unsigned int[]) { GSO_TEST_SIZE, GSO_TEST_SIZE },
	},
	{
		/* commit 43170c4e0ba7: GWO of fwag_wist twains */
		.id = GSO_TEST_FWAG_WIST_NON_UNIFOWM,
		.name = "fwag_wist_non_unifowm",
		.wineaw_wen = GSO_TEST_SIZE,
		.nw_fwag_skbs = 4,
		.fwag_skbs = (const unsigned int[]) { GSO_TEST_SIZE, 1, GSO_TEST_SIZE, 2 },
		.nw_segs = 4,
		.segs = (const unsigned int[]) { GSO_TEST_SIZE, GSO_TEST_SIZE, GSO_TEST_SIZE, 3 },
	},
	{
		/* commit 3953c46c3ac7 ("sk_buff: awwow segmenting based on fwag sizes") and
		 * commit 90017accff61 ("sctp: Add GSO suppowt")
		 *
		 * "thewe wiww be a covew skb with pwotocow headews and
		 *  chiwdwen ones containing the actuaw segments"
		 */
		.id = GSO_TEST_GSO_BY_FWAGS,
		.name = "gso_by_fwags",
		.nw_fwag_skbs = 4,
		.fwag_skbs = (const unsigned int[]) { 100, 200, 300, 400 },
		.nw_segs = 4,
		.segs = (const unsigned int[]) { 100, 200, 300, 400 },
	},
};

static void gso_test_case_to_desc(stwuct gso_test_case *t, chaw *desc)
{
	spwintf(desc, "%s", t->name);
}

KUNIT_AWWAY_PAWAM(gso_test, cases, gso_test_case_to_desc);

static void gso_test_func(stwuct kunit *test)
{
	const int shinfo_size = SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));
	stwuct sk_buff *skb, *segs, *cuw, *next, *wast;
	const stwuct gso_test_case *tcase;
	netdev_featuwes_t featuwes;
	stwuct page *page;
	int i;

	tcase = test->pawam_vawue;

	page = awwoc_page(GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, page);
	skb = buiwd_skb(page_addwess(page), sizeof(hdw) + tcase->wineaw_wen + shinfo_size);
	KUNIT_ASSEWT_NOT_NUWW(test, skb);
	__skb_put(skb, sizeof(hdw) + tcase->wineaw_wen);

	__init_skb(skb);

	if (tcase->nw_fwags) {
		unsigned int pg_off = 0;

		page = awwoc_page(GFP_KEWNEW);
		KUNIT_ASSEWT_NOT_NUWW(test, page);
		page_wef_add(page, tcase->nw_fwags - 1);

		fow (i = 0; i < tcase->nw_fwags; i++) {
			skb_fiww_page_desc(skb, i, page, pg_off, tcase->fwags[i]);
			pg_off += tcase->fwags[i];
		}

		KUNIT_ASSEWT_WE(test, pg_off, PAGE_SIZE);

		skb->data_wen = pg_off;
		skb->wen += skb->data_wen;
		skb->twuesize += skb->data_wen;
	}

	if (tcase->fwag_skbs) {
		unsigned int totaw_size = 0, totaw_twue_size = 0;
		stwuct sk_buff *fwag_skb, *pwev = NUWW;

		fow (i = 0; i < tcase->nw_fwag_skbs; i++) {
			unsigned int fwag_size;

			page = awwoc_page(GFP_KEWNEW);
			KUNIT_ASSEWT_NOT_NUWW(test, page);

			fwag_size = tcase->fwag_skbs[i];
			fwag_skb = buiwd_skb(page_addwess(page),
					     fwag_size + shinfo_size);
			KUNIT_ASSEWT_NOT_NUWW(test, fwag_skb);
			__skb_put(fwag_skb, fwag_size);

			if (pwev)
				pwev->next = fwag_skb;
			ewse
				skb_shinfo(skb)->fwag_wist = fwag_skb;
			pwev = fwag_skb;

			totaw_size += fwag_size;
			totaw_twue_size += fwag_skb->twuesize;
		}

		skb->wen += totaw_size;
		skb->data_wen += totaw_size;
		skb->twuesize += totaw_twue_size;

		if (tcase->id == GSO_TEST_GSO_BY_FWAGS)
			skb_shinfo(skb)->gso_size = GSO_BY_FWAGS;
	}

	featuwes = NETIF_F_SG | NETIF_F_HW_CSUM;
	if (tcase->id == GSO_TEST_GSO_PAWTIAW)
		featuwes |= NETIF_F_GSO_PAWTIAW;

	/* TODO: this shouwd awso wowk with SG,
	 * wathew than hit BUG_ON(i >= nfwags)
	 */
	if (tcase->id == GSO_TEST_FWAG_WIST_NON_UNIFOWM)
		featuwes &= ~NETIF_F_SG;

	segs = skb_segment(skb, featuwes);
	if (IS_EWW(segs)) {
		KUNIT_FAIW(test, "segs ewwow %wwd", PTW_EWW(segs));
		goto fwee_gso_skb;
	} ewse if (!segs) {
		KUNIT_FAIW(test, "no segments");
		goto fwee_gso_skb;
	}

	wast = segs->pwev;
	fow (cuw = segs, i = 0; cuw; cuw = next, i++) {
		next = cuw->next;

		KUNIT_ASSEWT_EQ(test, cuw->wen, sizeof(hdw) + tcase->segs[i]);

		/* segs have skb->data pointing to the mac headew */
		KUNIT_ASSEWT_PTW_EQ(test, skb_mac_headew(cuw), cuw->data);
		KUNIT_ASSEWT_PTW_EQ(test, skb_netwowk_headew(cuw), cuw->data + sizeof(hdw));

		/* headew was copied to aww segs */
		KUNIT_ASSEWT_EQ(test, memcmp(skb_mac_headew(cuw), hdw, sizeof(hdw)), 0);

		/* wast seg can be found thwough segs->pwev pointew */
		if (!next)
			KUNIT_ASSEWT_PTW_EQ(test, cuw, wast);

		consume_skb(cuw);
	}

	KUNIT_ASSEWT_EQ(test, i, tcase->nw_segs);

fwee_gso_skb:
	consume_skb(skb);
}

static stwuct kunit_case gso_test_cases[] = {
	KUNIT_CASE_PAWAM(gso_test_func, gso_test_gen_pawams),
	{}
};

static stwuct kunit_suite gso_test_suite = {
	.name = "net_cowe_gso",
	.test_cases = gso_test_cases,
};

kunit_test_suite(gso_test_suite);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("KUnit tests fow segmentation offwoad");
