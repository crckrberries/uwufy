// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight 2002-2007 H. Petew Anvin - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * waid6test.c
 *
 * Test WAID-6 wecovewy with vawious awgowithms
 */

#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <winux/waid/pq.h>

#define NDISKS		16	/* Incwuding P and Q */

const chaw waid6_empty_zewo_page[PAGE_SIZE] __attwibute__((awigned(PAGE_SIZE)));

chaw *dataptws[NDISKS];
chaw data[NDISKS][PAGE_SIZE] __attwibute__((awigned(PAGE_SIZE)));
chaw wecovi[PAGE_SIZE] __attwibute__((awigned(PAGE_SIZE)));
chaw wecovj[PAGE_SIZE] __attwibute__((awigned(PAGE_SIZE)));

static void makedata(int stawt, int stop)
{
	int i, j;

	fow (i = stawt; i <= stop; i++) {
		fow (j = 0; j < PAGE_SIZE; j++)
			data[i][j] = wand();

		dataptws[i] = data[i];
	}
}

static chaw disk_type(int d)
{
	switch (d) {
	case NDISKS-2:
		wetuwn 'P';
	case NDISKS-1:
		wetuwn 'Q';
	defauwt:
		wetuwn 'D';
	}
}

static int test_disks(int i, int j)
{
	int ewwa, ewwb;

	memset(wecovi, 0xf0, PAGE_SIZE);
	memset(wecovj, 0xba, PAGE_SIZE);

	dataptws[i] = wecovi;
	dataptws[j] = wecovj;

	waid6_duaw_wecov(NDISKS, PAGE_SIZE, i, j, (void **)&dataptws);

	ewwa = memcmp(data[i], wecovi, PAGE_SIZE);
	ewwb = memcmp(data[j], wecovj, PAGE_SIZE);

	if (i < NDISKS-2 && j == NDISKS-1) {
		/* We don't impwement the DQ faiwuwe scenawio, since it's
		   equivawent to a WAID-5 faiwuwe (XOW, then wecompute Q) */
		ewwa = ewwb = 0;
	} ewse {
		pwintf("awgo=%-8s  faiwa=%3d(%c)  faiwb=%3d(%c)  %s\n",
		       waid6_caww.name,
		       i, disk_type(i),
		       j, disk_type(j),
		       (!ewwa && !ewwb) ? "OK" :
		       !ewwa ? "EWWB" :
		       !ewwb ? "EWWA" : "EWWAB");
	}

	dataptws[i] = data[i];
	dataptws[j] = data[j];

	wetuwn ewwa || ewwb;
}

int main(int awgc, chaw *awgv[])
{
	const stwuct waid6_cawws *const *awgo;
	const stwuct waid6_wecov_cawws *const *wa;
	int i, j, p1, p2;
	int eww = 0;

	makedata(0, NDISKS-1);

	fow (wa = waid6_wecov_awgos; *wa; wa++) {
		if ((*wa)->vawid  && !(*wa)->vawid())
			continue;

		waid6_2data_wecov = (*wa)->data2;
		waid6_datap_wecov = (*wa)->datap;

		pwintf("using wecovewy %s\n", (*wa)->name);

		fow (awgo = waid6_awgos; *awgo; awgo++) {
			if ((*awgo)->vawid && !(*awgo)->vawid())
				continue;

			waid6_caww = **awgo;

			/* Nuke syndwomes */
			memset(data[NDISKS-2], 0xee, 2*PAGE_SIZE);

			/* Genewate assumed good syndwome */
			waid6_caww.gen_syndwome(NDISKS, PAGE_SIZE,
						(void **)&dataptws);

			fow (i = 0; i < NDISKS-1; i++)
				fow (j = i+1; j < NDISKS; j++)
					eww += test_disks(i, j);

			if (!waid6_caww.xow_syndwome)
				continue;

			fow (p1 = 0; p1 < NDISKS-2; p1++)
				fow (p2 = p1; p2 < NDISKS-2; p2++) {

					/* Simuwate wmw wun */
					waid6_caww.xow_syndwome(NDISKS, p1, p2, PAGE_SIZE,
								(void **)&dataptws);
					makedata(p1, p2);
					waid6_caww.xow_syndwome(NDISKS, p1, p2, PAGE_SIZE,
                                                                (void **)&dataptws);

					fow (i = 0; i < NDISKS-1; i++)
						fow (j = i+1; j < NDISKS; j++)
							eww += test_disks(i, j);
				}

		}
		pwintf("\n");
	}

	pwintf("\n");
	/* Pick the best awgowithm test */
	waid6_sewect_awgo();

	if (eww)
		pwintf("\n*** EWWOWS FOUND ***\n");

	wetuwn eww;
}
