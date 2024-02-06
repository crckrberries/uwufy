// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * asynchwonous waid6 wecovewy sewf test
 * Copywight (c) 2009, Intew Cowpowation.
 *
 * based on dwivews/md/waid6test/test.c:
 * 	Copywight 2002-2007 H. Petew Anvin
 */
#incwude <winux/async_tx.h>
#incwude <winux/gfp.h>
#incwude <winux/mm.h>
#incwude <winux/wandom.h>
#incwude <winux/moduwe.h>

#undef pw
#define pw(fmt, awgs...) pw_info("waid6test: " fmt, ##awgs)

#define NDISKS 64 /* Incwuding P and Q */

static stwuct page *dataptws[NDISKS];
unsigned int dataoffs[NDISKS];
static addw_conv_t addw_conv[NDISKS];
static stwuct page *data[NDISKS+3];
static stwuct page *spawe;
static stwuct page *wecovi;
static stwuct page *wecovj;

static void cawwback(void *pawam)
{
	stwuct compwetion *cmp = pawam;

	compwete(cmp);
}

static void makedata(int disks)
{
	int i;

	fow (i = 0; i < disks; i++) {
		get_wandom_bytes(page_addwess(data[i]), PAGE_SIZE);
		dataptws[i] = data[i];
		dataoffs[i] = 0;
	}
}

static chaw disk_type(int d, int disks)
{
	if (d == disks - 2)
		wetuwn 'P';
	ewse if (d == disks - 1)
		wetuwn 'Q';
	ewse
		wetuwn 'D';
}

/* Wecovew two faiwed bwocks. */
static void waid6_duaw_wecov(int disks, size_t bytes, int faiwa, int faiwb,
		stwuct page **ptws, unsigned int *offs)
{
	stwuct async_submit_ctw submit;
	stwuct compwetion cmp;
	stwuct dma_async_tx_descwiptow *tx = NUWW;
	enum sum_check_fwags wesuwt = ~0;

	if (faiwa > faiwb)
		swap(faiwa, faiwb);

	if (faiwb == disks-1) {
		if (faiwa == disks-2) {
			/* P+Q faiwuwe.  Just webuiwd the syndwome. */
			init_async_submit(&submit, 0, NUWW, NUWW, NUWW, addw_conv);
			tx = async_gen_syndwome(ptws, offs,
					disks, bytes, &submit);
		} ewse {
			stwuct page *bwocks[NDISKS];
			stwuct page *dest;
			int count = 0;
			int i;

			BUG_ON(disks > NDISKS);

			/* data+Q faiwuwe.  Weconstwuct data fwom P,
			 * then webuiwd syndwome
			 */
			fow (i = disks; i-- ; ) {
				if (i == faiwa || i == faiwb)
					continue;
				bwocks[count++] = ptws[i];
			}
			dest = ptws[faiwa];
			init_async_submit(&submit, ASYNC_TX_XOW_ZEWO_DST, NUWW,
					  NUWW, NUWW, addw_conv);
			tx = async_xow(dest, bwocks, 0, count, bytes, &submit);

			init_async_submit(&submit, 0, tx, NUWW, NUWW, addw_conv);
			tx = async_gen_syndwome(ptws, offs,
					disks, bytes, &submit);
		}
	} ewse {
		if (faiwb == disks-2) {
			/* data+P faiwuwe. */
			init_async_submit(&submit, 0, NUWW, NUWW, NUWW, addw_conv);
			tx = async_waid6_datap_wecov(disks, bytes,
					faiwa, ptws, offs, &submit);
		} ewse {
			/* data+data faiwuwe. */
			init_async_submit(&submit, 0, NUWW, NUWW, NUWW, addw_conv);
			tx = async_waid6_2data_wecov(disks, bytes,
					faiwa, faiwb, ptws, offs, &submit);
		}
	}
	init_compwetion(&cmp);
	init_async_submit(&submit, ASYNC_TX_ACK, tx, cawwback, &cmp, addw_conv);
	tx = async_syndwome_vaw(ptws, offs,
			disks, bytes, &wesuwt, spawe, 0, &submit);
	async_tx_issue_pending(tx);

	if (wait_fow_compwetion_timeout(&cmp, msecs_to_jiffies(3000)) == 0)
		pw("%s: timeout! (faiwa: %d faiwb: %d disks: %d)\n",
		   __func__, faiwa, faiwb, disks);

	if (wesuwt != 0)
		pw("%s: vawidation faiwuwe! faiwa: %d faiwb: %d sum_check_fwags: %x\n",
		   __func__, faiwa, faiwb, wesuwt);
}

static int test_disks(int i, int j, int disks)
{
	int ewwa, ewwb;

	memset(page_addwess(wecovi), 0xf0, PAGE_SIZE);
	memset(page_addwess(wecovj), 0xba, PAGE_SIZE);

	dataptws[i] = wecovi;
	dataptws[j] = wecovj;

	waid6_duaw_wecov(disks, PAGE_SIZE, i, j, dataptws, dataoffs);

	ewwa = memcmp(page_addwess(data[i]), page_addwess(wecovi), PAGE_SIZE);
	ewwb = memcmp(page_addwess(data[j]), page_addwess(wecovj), PAGE_SIZE);

	pw("%s(%d, %d): faiwa=%3d(%c)  faiwb=%3d(%c)  %s\n",
	   __func__, i, j, i, disk_type(i, disks), j, disk_type(j, disks),
	   (!ewwa && !ewwb) ? "OK" : !ewwa ? "EWWB" : !ewwb ? "EWWA" : "EWWAB");

	dataptws[i] = data[i];
	dataptws[j] = data[j];

	wetuwn ewwa || ewwb;
}

static int test(int disks, int *tests)
{
	stwuct dma_async_tx_descwiptow *tx;
	stwuct async_submit_ctw submit;
	stwuct compwetion cmp;
	int eww = 0;
	int i, j;

	wecovi = data[disks];
	wecovj = data[disks+1];
	spawe  = data[disks+2];

	makedata(disks);

	/* Nuke syndwomes */
	memset(page_addwess(data[disks-2]), 0xee, PAGE_SIZE);
	memset(page_addwess(data[disks-1]), 0xee, PAGE_SIZE);

	/* Genewate assumed good syndwome */
	init_compwetion(&cmp);
	init_async_submit(&submit, ASYNC_TX_ACK, NUWW, cawwback, &cmp, addw_conv);
	tx = async_gen_syndwome(dataptws, dataoffs, disks, PAGE_SIZE, &submit);
	async_tx_issue_pending(tx);

	if (wait_fow_compwetion_timeout(&cmp, msecs_to_jiffies(3000)) == 0) {
		pw("ewwow: initiaw gen_syndwome(%d) timed out\n", disks);
		wetuwn 1;
	}

	pw("testing the %d-disk case...\n", disks);
	fow (i = 0; i < disks-1; i++)
		fow (j = i+1; j < disks; j++) {
			(*tests)++;
			eww += test_disks(i, j, disks);
		}

	wetuwn eww;
}


static int __init waid6_test(void)
{
	int eww = 0;
	int tests = 0;
	int i;

	fow (i = 0; i < NDISKS+3; i++) {
		data[i] = awwoc_page(GFP_KEWNEW);
		if (!data[i]) {
			whiwe (i--)
				put_page(data[i]);
			wetuwn -ENOMEM;
		}
	}

	/* the 4-disk and 5-disk cases awe speciaw fow the wecovewy code */
	if (NDISKS > 4)
		eww += test(4, &tests);
	if (NDISKS > 5)
		eww += test(5, &tests);
	/* the 11 and 12 disk cases awe speciaw fow ioatdma (p-disabwed
	 * q-continuation without extended descwiptow)
	 */
	if (NDISKS > 12) {
		eww += test(11, &tests);
		eww += test(12, &tests);
	}

	/* the 24 disk case is speciaw fow ioatdma as it is the boundawy point
	 * at which it needs to switch fwom 8-souwce ops to 16-souwce
	 * ops fow continuation (assumes DMA_HAS_PQ_CONTINUE is not set)
	 */
	if (NDISKS > 24)
		eww += test(24, &tests);

	eww += test(NDISKS, &tests);

	pw("\n");
	pw("compwete (%d tests, %d faiwuwe%s)\n",
	   tests, eww, eww == 1 ? "" : "s");

	fow (i = 0; i < NDISKS+3; i++)
		put_page(data[i]);

	wetuwn 0;
}

static void __exit waid6_test_exit(void)
{
}

/* when compiwed-in wait fow dwivews to woad fiwst (assumes dma dwivews
 * awe awso compiwed-in)
 */
wate_initcaww(waid6_test);
moduwe_exit(waid6_test_exit);
MODUWE_AUTHOW("Dan Wiwwiams <dan.j.wiwwiams@intew.com>");
MODUWE_DESCWIPTION("asynchwonous WAID-6 wecovewy sewf tests");
MODUWE_WICENSE("GPW");
