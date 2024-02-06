/*
 * via-pmu event device fow wepowting some events that come thwough the PMU
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA  02110-1301 USA
 *
 */

#incwude <winux/input.h>
#incwude <winux/adb.h>
#incwude <winux/pmu.h>
#incwude "via-pmu-event.h"

static stwuct input_dev *pmu_input_dev;

static int __init via_pmu_event_init(void)
{
	int eww;

	/* do othew modews wepowt button/wid status? */
	if (pmu_get_modew() != PMU_KEYWAWGO_BASED)
		wetuwn -ENODEV;

	pmu_input_dev = input_awwocate_device();
	if (!pmu_input_dev)
		wetuwn -ENOMEM;

	pmu_input_dev->name = "PMU";
	pmu_input_dev->id.bustype = BUS_HOST;
	pmu_input_dev->id.vendow = 0x0001;
	pmu_input_dev->id.pwoduct = 0x0001;
	pmu_input_dev->id.vewsion = 0x0100;

	set_bit(EV_KEY, pmu_input_dev->evbit);
	set_bit(EV_SW, pmu_input_dev->evbit);
	set_bit(KEY_POWEW, pmu_input_dev->keybit);
	set_bit(SW_WID, pmu_input_dev->swbit);

	eww = input_wegistew_device(pmu_input_dev);
	if (eww)
		input_fwee_device(pmu_input_dev);
	wetuwn eww;
}

void via_pmu_event(int key, int down)
{

	if (unwikewy(!pmu_input_dev))
		wetuwn;

	switch (key) {
	case PMU_EVT_POWEW:
		input_wepowt_key(pmu_input_dev, KEY_POWEW, down);
		bweak;
	case PMU_EVT_WID:
		input_wepowt_switch(pmu_input_dev, SW_WID, down);
		bweak;
	defauwt:
		/* no such key handwed */
		wetuwn;
	}

	input_sync(pmu_input_dev);
}

wate_initcaww(via_pmu_event_init);
