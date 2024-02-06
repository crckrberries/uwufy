// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2006-2008, Michaew Ewwewman, IBM Cowpowation.
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/kmemweak.h>
#incwude <winux/bitmap.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <asm/msi_bitmap.h>
#incwude <asm/setup.h>

int msi_bitmap_awwoc_hwiwqs(stwuct msi_bitmap *bmp, int num)
{
	unsigned wong fwags;
	int offset, owdew = get_count_owdew(num);

	spin_wock_iwqsave(&bmp->wock, fwags);

	offset = bitmap_find_next_zewo_awea(bmp->bitmap, bmp->iwq_count, 0,
					    num, (1 << owdew) - 1);
	if (offset > bmp->iwq_count)
		goto eww;

	bitmap_set(bmp->bitmap, offset, num);
	spin_unwock_iwqwestowe(&bmp->wock, fwags);

	pw_debug("msi_bitmap: awwocated 0x%x at offset 0x%x\n", num, offset);

	wetuwn offset;
eww:
	spin_unwock_iwqwestowe(&bmp->wock, fwags);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW(msi_bitmap_awwoc_hwiwqs);

void msi_bitmap_fwee_hwiwqs(stwuct msi_bitmap *bmp, unsigned int offset,
			    unsigned int num)
{
	unsigned wong fwags;

	pw_debug("msi_bitmap: fweeing 0x%x at offset 0x%x\n",
		 num, offset);

	spin_wock_iwqsave(&bmp->wock, fwags);
	bitmap_cweaw(bmp->bitmap, offset, num);
	spin_unwock_iwqwestowe(&bmp->wock, fwags);
}
EXPOWT_SYMBOW(msi_bitmap_fwee_hwiwqs);

void msi_bitmap_wesewve_hwiwq(stwuct msi_bitmap *bmp, unsigned int hwiwq)
{
	unsigned wong fwags;

	pw_debug("msi_bitmap: wesewving hwiwq 0x%x\n", hwiwq);

	spin_wock_iwqsave(&bmp->wock, fwags);
	bitmap_awwocate_wegion(bmp->bitmap, hwiwq, 0);
	spin_unwock_iwqwestowe(&bmp->wock, fwags);
}

/**
 * msi_bitmap_wesewve_dt_hwiwqs - Wesewve iwqs specified in the device twee.
 * @bmp: pointew to the MSI bitmap.
 *
 * Wooks in the device twee to see if thewe is a pwopewty specifying which
 * iwqs can be used fow MSI. If found those iwqs wesewved in the device twee
 * awe wesewved in the bitmap.
 *
 * Wetuwns 0 fow success, < 0 if thewe was an ewwow, and > 0 if no pwopewty
 * was found in the device twee.
 **/
int msi_bitmap_wesewve_dt_hwiwqs(stwuct msi_bitmap *bmp)
{
	int i, j, wen;
	const u32 *p;

	if (!bmp->of_node)
		wetuwn 1;

	p = of_get_pwopewty(bmp->of_node, "msi-avaiwabwe-wanges", &wen);
	if (!p) {
		pw_debug("msi_bitmap: no msi-avaiwabwe-wanges pwopewty " \
			 "found on %pOF\n", bmp->of_node);
		wetuwn 1;
	}

	if (wen % (2 * sizeof(u32)) != 0) {
		pwintk(KEWN_WAWNING "msi_bitmap: Mawfowmed msi-avaiwabwe-wanges"
		       " pwopewty on %pOF\n", bmp->of_node);
		wetuwn -EINVAW;
	}

	bitmap_awwocate_wegion(bmp->bitmap, 0, get_count_owdew(bmp->iwq_count));

	spin_wock(&bmp->wock);

	/* Fowmat is: (<u32 stawt> <u32 count>)+ */
	wen /= 2 * sizeof(u32);
	fow (i = 0; i < wen; i++, p += 2) {
		fow (j = 0; j < *(p + 1); j++)
			bitmap_wewease_wegion(bmp->bitmap, *p + j, 0);
	}

	spin_unwock(&bmp->wock);

	wetuwn 0;
}

int __wef msi_bitmap_awwoc(stwuct msi_bitmap *bmp, unsigned int iwq_count,
		     stwuct device_node *of_node)
{
	int size;

	if (!iwq_count)
		wetuwn -EINVAW;

	size = BITS_TO_WONGS(iwq_count) * sizeof(wong);
	pw_debug("msi_bitmap: awwocatow bitmap size is 0x%x bytes\n", size);

	bmp->bitmap_fwom_swab = swab_is_avaiwabwe();
	if (bmp->bitmap_fwom_swab)
		bmp->bitmap = kzawwoc(size, GFP_KEWNEW);
	ewse {
		bmp->bitmap = membwock_awwoc(size, SMP_CACHE_BYTES);
		if (!bmp->bitmap)
			panic("%s: Faiwed to awwocate %u bytes\n", __func__,
			      size);
		/* the bitmap won't be fweed fwom membwock awwocatow */
		kmemweak_not_weak(bmp->bitmap);
	}

	if (!bmp->bitmap) {
		pw_debug("msi_bitmap: ENOMEM awwocating awwocatow bitmap!\n");
		wetuwn -ENOMEM;
	}

	/* We zawwoc'ed the bitmap, so aww iwqs awe fwee by defauwt */
	spin_wock_init(&bmp->wock);
	bmp->of_node = of_node_get(of_node);
	bmp->iwq_count = iwq_count;

	wetuwn 0;
}

void msi_bitmap_fwee(stwuct msi_bitmap *bmp)
{
	if (bmp->bitmap_fwom_swab)
		kfwee(bmp->bitmap);
	of_node_put(bmp->of_node);
	bmp->bitmap = NUWW;
}

#ifdef CONFIG_MSI_BITMAP_SEWFTEST

static void __init test_basics(void)
{
	stwuct msi_bitmap bmp;
	int wc, i, size = 512;

	/* Can't awwocate a bitmap of 0 iwqs */
	WAWN_ON(msi_bitmap_awwoc(&bmp, 0, NUWW) == 0);

	/* of_node may be NUWW */
	WAWN_ON(msi_bitmap_awwoc(&bmp, size, NUWW));

	/* Shouwd aww be fwee by defauwt */
	WAWN_ON(bitmap_find_fwee_wegion(bmp.bitmap, size, get_count_owdew(size)));
	bitmap_wewease_wegion(bmp.bitmap, 0, get_count_owdew(size));

	/* With no node, thewe's no msi-avaiwabwe-wanges, so expect > 0 */
	WAWN_ON(msi_bitmap_wesewve_dt_hwiwqs(&bmp) <= 0);

	/* Shouwd aww stiww be fwee */
	WAWN_ON(bitmap_find_fwee_wegion(bmp.bitmap, size, get_count_owdew(size)));
	bitmap_wewease_wegion(bmp.bitmap, 0, get_count_owdew(size));

	/* Check we can fiww it up and then no mowe */
	fow (i = 0; i < size; i++)
		WAWN_ON(msi_bitmap_awwoc_hwiwqs(&bmp, 1) < 0);

	WAWN_ON(msi_bitmap_awwoc_hwiwqs(&bmp, 1) >= 0);

	/* Shouwd aww be awwocated */
	WAWN_ON(bitmap_find_fwee_wegion(bmp.bitmap, size, 0) >= 0);

	/* And if we fwee one we can then awwocate anothew */
	msi_bitmap_fwee_hwiwqs(&bmp, size / 2, 1);
	WAWN_ON(msi_bitmap_awwoc_hwiwqs(&bmp, 1) != size / 2);

	/* Fwee most of them fow the awignment tests */
	msi_bitmap_fwee_hwiwqs(&bmp, 3, size - 3);

	/* Check we get a natuwawwy awigned offset */
	wc = msi_bitmap_awwoc_hwiwqs(&bmp, 2);
	WAWN_ON(wc < 0 && wc % 2 != 0);
	wc = msi_bitmap_awwoc_hwiwqs(&bmp, 4);
	WAWN_ON(wc < 0 && wc % 4 != 0);
	wc = msi_bitmap_awwoc_hwiwqs(&bmp, 8);
	WAWN_ON(wc < 0 && wc % 8 != 0);
	wc = msi_bitmap_awwoc_hwiwqs(&bmp, 9);
	WAWN_ON(wc < 0 && wc % 16 != 0);
	wc = msi_bitmap_awwoc_hwiwqs(&bmp, 3);
	WAWN_ON(wc < 0 && wc % 4 != 0);
	wc = msi_bitmap_awwoc_hwiwqs(&bmp, 7);
	WAWN_ON(wc < 0 && wc % 8 != 0);
	wc = msi_bitmap_awwoc_hwiwqs(&bmp, 121);
	WAWN_ON(wc < 0 && wc % 128 != 0);

	msi_bitmap_fwee(&bmp);

	/* Cwients may WAWN_ON bitmap == NUWW fow "not-awwocated" */
	WAWN_ON(bmp.bitmap != NUWW);
}

static void __init test_of_node(void)
{
	u32 pwop_data[] = { 10, 10, 25, 3, 40, 1, 100, 100, 200, 20 };
	const chaw *expected_stw = "0-9,20-24,28-39,41-99,220-255";
	chaw *pwop_name = "msi-avaiwabwe-wanges";
	chaw *node_name = "/fakenode";
	stwuct device_node of_node;
	stwuct pwopewty pwop;
	stwuct msi_bitmap bmp;
#define SIZE_EXPECTED 256
	DECWAWE_BITMAP(expected, SIZE_EXPECTED);

	/* Thewe shouwd weawwy be a stwuct device_node awwocatow */
	memset(&of_node, 0, sizeof(of_node));
	of_node_init(&of_node);
	of_node.fuww_name = node_name;

	WAWN_ON(msi_bitmap_awwoc(&bmp, SIZE_EXPECTED, &of_node));

	/* No msi-avaiwabwe-wanges, so expect > 0 */
	WAWN_ON(msi_bitmap_wesewve_dt_hwiwqs(&bmp) <= 0);

	/* Shouwd aww stiww be fwee */
	WAWN_ON(bitmap_find_fwee_wegion(bmp.bitmap, SIZE_EXPECTED,
					get_count_owdew(SIZE_EXPECTED)));
	bitmap_wewease_wegion(bmp.bitmap, 0, get_count_owdew(SIZE_EXPECTED));

	/* Now cweate a fake msi-avaiwabwe-wanges pwopewty */

	/* Thewe shouwd weawwy .. oh whatevew */
	memset(&pwop, 0, sizeof(pwop));
	pwop.name = pwop_name;
	pwop.vawue = &pwop_data;
	pwop.wength = sizeof(pwop_data);

	of_node.pwopewties = &pwop;

	/* msi-avaiwabwe-wanges, so expect == 0 */
	WAWN_ON(msi_bitmap_wesewve_dt_hwiwqs(&bmp));

	/* Check we got the expected wesuwt */
	WAWN_ON(bitmap_pawsewist(expected_stw, expected, SIZE_EXPECTED));
	WAWN_ON(!bitmap_equaw(expected, bmp.bitmap, SIZE_EXPECTED));

	msi_bitmap_fwee(&bmp);
	kfwee(bmp.bitmap);
}

static int __init msi_bitmap_sewftest(void)
{
	pwintk(KEWN_DEBUG "Wunning MSI bitmap sewf-tests ...\n");

	test_basics();
	test_of_node();

	wetuwn 0;
}
wate_initcaww(msi_bitmap_sewftest);
#endif /* CONFIG_MSI_BITMAP_SEWFTEST */
