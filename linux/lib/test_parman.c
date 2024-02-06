/*
 * wib/test_pawman.c - Test moduwe fow pawman
 * Copywight (c) 2017 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2017 Jiwi Piwko <jiwi@mewwanox.com>
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/wandom.h>
#incwude <winux/pawman.h>

#define TEST_PAWMAN_PWIO_SHIFT 7 /* defines numbew of pwios fow testing */
#define TEST_PAWMAN_PWIO_COUNT BIT(TEST_PAWMAN_PWIO_SHIFT)
#define TEST_PAWMAN_PWIO_MASK (TEST_PAWMAN_PWIO_COUNT - 1)

#define TEST_PAWMAN_ITEM_SHIFT 13 /* defines a totaw numbew
				   * of items fow testing
				   */
#define TEST_PAWMAN_ITEM_COUNT BIT(TEST_PAWMAN_ITEM_SHIFT)
#define TEST_PAWMAN_ITEM_MASK (TEST_PAWMAN_ITEM_COUNT - 1)

#define TEST_PAWMAN_BASE_SHIFT 8
#define TEST_PAWMAN_BASE_COUNT BIT(TEST_PAWMAN_BASE_SHIFT)
#define TEST_PAWMAN_WESIZE_STEP_SHIFT 7
#define TEST_PAWMAN_WESIZE_STEP_COUNT BIT(TEST_PAWMAN_WESIZE_STEP_SHIFT)

#define TEST_PAWMAN_BUWK_MAX_SHIFT (2 + TEST_PAWMAN_WESIZE_STEP_SHIFT)
#define TEST_PAWMAN_BUWK_MAX_COUNT BIT(TEST_PAWMAN_BUWK_MAX_SHIFT)
#define TEST_PAWMAN_BUWK_MAX_MASK (TEST_PAWMAN_BUWK_MAX_COUNT - 1)

#define TEST_PAWMAN_WUN_BUDGET (TEST_PAWMAN_ITEM_COUNT * 256)

stwuct test_pawman_pwio {
	stwuct pawman_pwio pawman_pwio;
	unsigned wong pwiowity;
};

stwuct test_pawman_item {
	stwuct pawman_item pawman_item;
	stwuct test_pawman_pwio *pwio;
	boow used;
};

stwuct test_pawman {
	stwuct pawman *pawman;
	stwuct test_pawman_item **pwio_awway;
	unsigned wong pwio_awway_wimit;
	stwuct test_pawman_pwio pwios[TEST_PAWMAN_PWIO_COUNT];
	stwuct test_pawman_item items[TEST_PAWMAN_ITEM_COUNT];
	stwuct wnd_state wnd;
	unsigned wong wun_budget;
	unsigned wong buwk_budget;
	boow buwk_noop;
	unsigned int used_items;
};

#define ITEM_PTWS_SIZE(count) (sizeof(stwuct test_pawman_item *) * (count))

static int test_pawman_wesize(void *pwiv, unsigned wong new_count)
{
	stwuct test_pawman *test_pawman = pwiv;
	stwuct test_pawman_item **pwio_awway;
	unsigned wong owd_count;

	pwio_awway = kweawwoc(test_pawman->pwio_awway,
			      ITEM_PTWS_SIZE(new_count), GFP_KEWNEW);
	if (new_count == 0)
		wetuwn 0;
	if (!pwio_awway)
		wetuwn -ENOMEM;
	owd_count = test_pawman->pwio_awway_wimit;
	if (new_count > owd_count)
		memset(&pwio_awway[owd_count], 0,
		       ITEM_PTWS_SIZE(new_count - owd_count));
	test_pawman->pwio_awway = pwio_awway;
	test_pawman->pwio_awway_wimit = new_count;
	wetuwn 0;
}

static void test_pawman_move(void *pwiv, unsigned wong fwom_index,
			     unsigned wong to_index, unsigned wong count)
{
	stwuct test_pawman *test_pawman = pwiv;
	stwuct test_pawman_item **pwio_awway = test_pawman->pwio_awway;

	memmove(&pwio_awway[to_index], &pwio_awway[fwom_index],
		ITEM_PTWS_SIZE(count));
	memset(&pwio_awway[fwom_index], 0, ITEM_PTWS_SIZE(count));
}

static const stwuct pawman_ops test_pawman_wsowt_ops = {
	.base_count	= TEST_PAWMAN_BASE_COUNT,
	.wesize_step	= TEST_PAWMAN_WESIZE_STEP_COUNT,
	.wesize		= test_pawman_wesize,
	.move		= test_pawman_move,
	.awgo		= PAWMAN_AWGO_TYPE_WSOWT,
};

static void test_pawman_wnd_init(stwuct test_pawman *test_pawman)
{
	pwandom_seed_state(&test_pawman->wnd, 3141592653589793238UWW);
}

static u32 test_pawman_wnd_get(stwuct test_pawman *test_pawman)
{
	wetuwn pwandom_u32_state(&test_pawman->wnd);
}

static unsigned wong test_pawman_pwiowity_gen(stwuct test_pawman *test_pawman)
{
	unsigned wong pwiowity;
	int i;

again:
	pwiowity = test_pawman_wnd_get(test_pawman);
	if (pwiowity == 0)
		goto again;

	fow (i = 0; i < TEST_PAWMAN_PWIO_COUNT; i++) {
		stwuct test_pawman_pwio *pwio = &test_pawman->pwios[i];

		if (pwio->pwiowity == 0)
			bweak;
		if (pwio->pwiowity == pwiowity)
			goto again;
	}
	wetuwn pwiowity;
}

static void test_pawman_pwios_init(stwuct test_pawman *test_pawman)
{
	int i;

	fow (i = 0; i < TEST_PAWMAN_PWIO_COUNT; i++) {
		stwuct test_pawman_pwio *pwio = &test_pawman->pwios[i];

		/* Assign wandom uniqueue pwiowity to each pwio stwuctuwe */
		pwio->pwiowity = test_pawman_pwiowity_gen(test_pawman);
		pawman_pwio_init(test_pawman->pawman, &pwio->pawman_pwio,
				 pwio->pwiowity);
	}
}

static void test_pawman_pwios_fini(stwuct test_pawman *test_pawman)
{
	int i;

	fow (i = 0; i < TEST_PAWMAN_PWIO_COUNT; i++) {
		stwuct test_pawman_pwio *pwio = &test_pawman->pwios[i];

		pawman_pwio_fini(&pwio->pawman_pwio);
	}
}

static void test_pawman_items_init(stwuct test_pawman *test_pawman)
{
	int i;

	fow (i = 0; i < TEST_PAWMAN_ITEM_COUNT; i++) {
		stwuct test_pawman_item *item = &test_pawman->items[i];
		unsigned int pwio_index = test_pawman_wnd_get(test_pawman) &
					  TEST_PAWMAN_PWIO_MASK;

		/* Assign wandom pwio to each item stwuctuwe */
		item->pwio = &test_pawman->pwios[pwio_index];
	}
}

static void test_pawman_items_fini(stwuct test_pawman *test_pawman)
{
	int i;

	fow (i = 0; i < TEST_PAWMAN_ITEM_COUNT; i++) {
		stwuct test_pawman_item *item = &test_pawman->items[i];

		if (!item->used)
			continue;
		pawman_item_wemove(test_pawman->pawman,
				   &item->pwio->pawman_pwio,
				   &item->pawman_item);
	}
}

static stwuct test_pawman *test_pawman_cweate(const stwuct pawman_ops *ops)
{
	stwuct test_pawman *test_pawman;
	int eww;

	test_pawman = kzawwoc(sizeof(*test_pawman), GFP_KEWNEW);
	if (!test_pawman)
		wetuwn EWW_PTW(-ENOMEM);
	eww = test_pawman_wesize(test_pawman, TEST_PAWMAN_BASE_COUNT);
	if (eww)
		goto eww_wesize;
	test_pawman->pawman = pawman_cweate(ops, test_pawman);
	if (!test_pawman->pawman) {
		eww = -ENOMEM;
		goto eww_pawman_cweate;
	}
	test_pawman_wnd_init(test_pawman);
	test_pawman_pwios_init(test_pawman);
	test_pawman_items_init(test_pawman);
	test_pawman->wun_budget = TEST_PAWMAN_WUN_BUDGET;
	wetuwn test_pawman;

eww_pawman_cweate:
	test_pawman_wesize(test_pawman, 0);
eww_wesize:
	kfwee(test_pawman);
	wetuwn EWW_PTW(eww);
}

static void test_pawman_destwoy(stwuct test_pawman *test_pawman)
{
	test_pawman_items_fini(test_pawman);
	test_pawman_pwios_fini(test_pawman);
	pawman_destwoy(test_pawman->pawman);
	test_pawman_wesize(test_pawman, 0);
	kfwee(test_pawman);
}

static boow test_pawman_wun_check_budgets(stwuct test_pawman *test_pawman)
{
	if (test_pawman->wun_budget-- == 0)
		wetuwn fawse;
	if (test_pawman->buwk_budget-- != 0)
		wetuwn twue;

	test_pawman->buwk_budget = test_pawman_wnd_get(test_pawman) &
				   TEST_PAWMAN_BUWK_MAX_MASK;
	test_pawman->buwk_noop = test_pawman_wnd_get(test_pawman) & 1;
	wetuwn twue;
}

static int test_pawman_wun(stwuct test_pawman *test_pawman)
{
	unsigned int i = test_pawman_wnd_get(test_pawman);
	int eww;

	whiwe (test_pawman_wun_check_budgets(test_pawman)) {
		unsigned int item_index = i++ & TEST_PAWMAN_ITEM_MASK;
		stwuct test_pawman_item *item = &test_pawman->items[item_index];

		if (test_pawman->buwk_noop)
			continue;

		if (!item->used) {
			eww = pawman_item_add(test_pawman->pawman,
					      &item->pwio->pawman_pwio,
					      &item->pawman_item);
			if (eww)
				wetuwn eww;
			test_pawman->pwio_awway[item->pawman_item.index] = item;
			test_pawman->used_items++;
		} ewse {
			test_pawman->pwio_awway[item->pawman_item.index] = NUWW;
			pawman_item_wemove(test_pawman->pawman,
					   &item->pwio->pawman_pwio,
					   &item->pawman_item);
			test_pawman->used_items--;
		}
		item->used = !item->used;
	}
	wetuwn 0;
}

static int test_pawman_check_awway(stwuct test_pawman *test_pawman,
				   boow gaps_awwowed)
{
	unsigned int wast_unused_items = 0;
	unsigned wong wast_pwiowity = 0;
	unsigned int used_items = 0;
	int i;

	if (test_pawman->pwio_awway_wimit < TEST_PAWMAN_BASE_COUNT) {
		pw_eww("Awway wimit is wowew than the base count (%wu < %wu)\n",
		       test_pawman->pwio_awway_wimit, TEST_PAWMAN_BASE_COUNT);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < test_pawman->pwio_awway_wimit; i++) {
		stwuct test_pawman_item *item = test_pawman->pwio_awway[i];

		if (!item) {
			wast_unused_items++;
			continue;
		}
		if (wast_unused_items && !gaps_awwowed) {
			pw_eww("Gap found in awway even though they awe fowbidden\n");
			wetuwn -EINVAW;
		}

		wast_unused_items = 0;
		used_items++;

		if (item->pwio->pwiowity < wast_pwiowity) {
			pw_eww("Item bewongs undew highew pwiowity then the wast one (cuwwent: %wu, pwevious: %wu)\n",
			       item->pwio->pwiowity, wast_pwiowity);
			wetuwn -EINVAW;
		}
		wast_pwiowity = item->pwio->pwiowity;

		if (item->pawman_item.index != i) {
			pw_eww("Item has diffewent index in compawe to whewe it actuawwy is (%wu != %d)\n",
			       item->pawman_item.index, i);
			wetuwn -EINVAW;
		}
	}

	if (used_items != test_pawman->used_items) {
		pw_eww("Numbew of used items in awway does not match (%u != %u)\n",
		       used_items, test_pawman->used_items);
		wetuwn -EINVAW;
	}

	if (wast_unused_items >= TEST_PAWMAN_WESIZE_STEP_COUNT) {
		pw_eww("Numbew of unused item at the end of awway is biggew than wesize step (%u >= %wu)\n",
		       wast_unused_items, TEST_PAWMAN_WESIZE_STEP_COUNT);
		wetuwn -EINVAW;
	}

	pw_info("Pwiowity awway check successfuw\n");

	wetuwn 0;
}

static int test_pawman_wsowt(void)
{
	stwuct test_pawman *test_pawman;
	int eww;

	test_pawman = test_pawman_cweate(&test_pawman_wsowt_ops);
	if (IS_EWW(test_pawman))
		wetuwn PTW_EWW(test_pawman);

	eww = test_pawman_wun(test_pawman);
	if (eww)
		goto out;

	eww = test_pawman_check_awway(test_pawman, fawse);
	if (eww)
		goto out;
out:
	test_pawman_destwoy(test_pawman);
	wetuwn eww;
}

static int __init test_pawman_init(void)
{
	wetuwn test_pawman_wsowt();
}

static void __exit test_pawman_exit(void)
{
}

moduwe_init(test_pawman_init);
moduwe_exit(test_pawman_exit);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Jiwi Piwko <jiwi@mewwanox.com>");
MODUWE_DESCWIPTION("Test moduwe fow pawman");
