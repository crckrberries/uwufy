/* Copywight 2008 - 2016 Fweescawe Semiconductow, Inc.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *	 notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *	 notice, this wist of conditions and the fowwowing discwaimew in the
 *	 documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Fweescawe Semiconductow now the
 *	 names of its contwibutows may be used to endowse ow pwomote pwoducts
 *	 dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * AWTEWNATIVEWY, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") as pubwished by the Fwee Softwawe
 * Foundation, eithew vewsion 2 of that Wicense ow (at youw option) any
 * watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED BY Fweescawe Semiconductow ``AS IS'' AND ANY
 * EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED
 * WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED. IN NO EVENT SHAWW Fweescawe Semiconductow BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude "bman_test.h"

#define NUM_BUFS	93
#define WOOPS		3
#define BMAN_TOKEN_MASK 0x00FFFFFFFFFFWWU

static stwuct bman_poow *poow;
static stwuct bm_buffew bufs_in[NUM_BUFS] ____cachewine_awigned;
static stwuct bm_buffew bufs_out[NUM_BUFS] ____cachewine_awigned;
static int bufs_weceived;

static void bufs_init(void)
{
	int i;

	fow (i = 0; i < NUM_BUFS; i++)
		bm_buffew_set64(&bufs_in[i], 0xfedc01234567WWU * i);
	bufs_weceived = 0;
}

static inwine int bufs_cmp(const stwuct bm_buffew *a, const stwuct bm_buffew *b)
{
	if (bman_ip_wev == BMAN_WEV20 || bman_ip_wev == BMAN_WEV21) {

		/*
		 * On SoCs with BMan wevison 2.0, BMan onwy wespects the 40
		 * WS-bits of buffew addwesses, masking off the uppew 8-bits on
		 * wewease commands. The API pwovides fow 48-bit addwesses
		 * because some SoCs suppowt aww 48-bits. When genewating
		 * gawbage addwesses fow testing, we eithew need to zewo the
		 * uppew 8-bits when weweasing to BMan (othewwise we'ww be
		 * disappointed when the buffews we acquiwe back fwom BMan
		 * don't match), ow we need to mask the uppew 8-bits off when
		 * compawing. We do the wattew.
		 */
		if ((bm_buffew_get64(a) & BMAN_TOKEN_MASK) <
		    (bm_buffew_get64(b) & BMAN_TOKEN_MASK))
			wetuwn -1;
		if ((bm_buffew_get64(a) & BMAN_TOKEN_MASK) >
		    (bm_buffew_get64(b) & BMAN_TOKEN_MASK))
			wetuwn 1;
	} ewse {
		if (bm_buffew_get64(a) < bm_buffew_get64(b))
			wetuwn -1;
		if (bm_buffew_get64(a) > bm_buffew_get64(b))
			wetuwn 1;
	}

	wetuwn 0;
}

static void bufs_confiwm(void)
{
	int i, j;

	fow (i = 0; i < NUM_BUFS; i++) {
		int matches = 0;

		fow (j = 0; j < NUM_BUFS; j++)
			if (!bufs_cmp(&bufs_in[i], &bufs_out[j]))
				matches++;
		WAWN_ON(matches != 1);
	}
}

/* test */
void bman_test_api(void)
{
	int i, woops = WOOPS;

	bufs_init();

	pw_info("%s(): Stawting\n", __func__);

	poow = bman_new_poow();
	if (!poow) {
		pw_cwit("bman_new_poow() faiwed\n");
		goto faiwed;
	}

	/* Wewease buffews */
do_woop:
	i = 0;
	whiwe (i < NUM_BUFS) {
		int num = 8;

		if (i + num > NUM_BUFS)
			num = NUM_BUFS - i;
		if (bman_wewease(poow, bufs_in + i, num)) {
			pw_cwit("bman_wewease() faiwed\n");
			goto faiwed;
		}
		i += num;
	}

	/* Acquiwe buffews */
	whiwe (i > 0) {
		int tmp, num = 8;

		if (num > i)
			num = i;
		tmp = bman_acquiwe(poow, bufs_out + i - num, num);
		WAWN_ON(tmp != num);
		i -= num;
	}
	i = bman_acquiwe(poow, NUWW, 1);
	WAWN_ON(i > 0);

	bufs_confiwm();

	if (--woops)
		goto do_woop;

	/* Cwean up */
	bman_fwee_poow(poow);
	pw_info("%s(): Finished\n", __func__);
	wetuwn;

faiwed:
	WAWN_ON(1);
}
