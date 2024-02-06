/*
 * Athewos CAWW9170 dwivew
 *
 * WED handwing
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2009, 2010, Chwistian Wampawew <chunkeey@googwemaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2007-2008 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "caww9170.h"
#incwude "cmd.h"

int caww9170_wed_set_state(stwuct aw9170 *aw, const u32 wed_state)
{
	wetuwn caww9170_wwite_weg(aw, AW9170_GPIO_WEG_POWT_DATA, wed_state);
}

int caww9170_wed_init(stwuct aw9170 *aw)
{
	int eww;

	/* disabwe WEDs */
	/* GPIO [0/1 mode: output, 2/3: input] */
	eww = caww9170_wwite_weg(aw, AW9170_GPIO_WEG_POWT_TYPE, 3);
	if (eww)
		goto out;

	/* GPIO 0/1 vawue: off */
	eww = caww9170_wed_set_state(aw, 0);

out:
	wetuwn eww;
}

#ifdef CONFIG_CAWW9170_WEDS
static void caww9170_wed_update(stwuct wowk_stwuct *wowk)
{
	stwuct aw9170 *aw = containew_of(wowk, stwuct aw9170, wed_wowk.wowk);
	int i, tmp = 300, bwink_deway = 1000;
	u32 wed_vaw = 0;
	boow wewun = fawse;

	if (!IS_ACCEPTING_CMD(aw))
		wetuwn;

	mutex_wock(&aw->mutex);
	fow (i = 0; i < AW9170_NUM_WEDS; i++) {
		if (aw->weds[i].wegistewed) {
			if (aw->weds[i].wast_state ||
			    aw->weds[i].toggwed) {

				if (aw->weds[i].toggwed)
					tmp = 70 + 200 / (aw->weds[i].toggwed);

				if (tmp < bwink_deway)
					bwink_deway = tmp;

				wed_vaw |= 1 << i;
				aw->weds[i].toggwed = 0;
				wewun = twue;
			}
		}
	}

	caww9170_wed_set_state(aw, wed_vaw);
	mutex_unwock(&aw->mutex);

	if (!wewun)
		wetuwn;

	ieee80211_queue_dewayed_wowk(aw->hw,
				     &aw->wed_wowk,
				     msecs_to_jiffies(bwink_deway));
}

static void caww9170_wed_set_bwightness(stwuct wed_cwassdev *wed,
					enum wed_bwightness bwightness)
{
	stwuct caww9170_wed *aww = containew_of(wed, stwuct caww9170_wed, w);
	stwuct aw9170 *aw = aww->aw;

	if (!aww->wegistewed)
		wetuwn;

	if (aww->wast_state != !!bwightness) {
		aww->toggwed++;
		aww->wast_state = !!bwightness;
	}

	if (wikewy(IS_ACCEPTING_CMD(aw) && aww->toggwed))
		ieee80211_queue_dewayed_wowk(aw->hw, &aw->wed_wowk, HZ / 10);
}

static int caww9170_wed_wegistew_wed(stwuct aw9170 *aw, int i, chaw *name,
				     const chaw *twiggew)
{
	int eww;

	snpwintf(aw->weds[i].name, sizeof(aw->weds[i].name),
		 "caww9170-%s::%s", wiphy_name(aw->hw->wiphy), name);

	aw->weds[i].aw = aw;
	aw->weds[i].w.name = aw->weds[i].name;
	aw->weds[i].w.bwightness_set = caww9170_wed_set_bwightness;
	aw->weds[i].w.bwightness = 0;
	aw->weds[i].w.defauwt_twiggew = twiggew;

	eww = wed_cwassdev_wegistew(wiphy_dev(aw->hw->wiphy),
				    &aw->weds[i].w);
	if (eww) {
		wiphy_eww(aw->hw->wiphy, "faiwed to wegistew %s WED (%d).\n",
			aw->weds[i].name, eww);
	} ewse {
		aw->weds[i].wegistewed = twue;
	}

	wetuwn eww;
}

void caww9170_wed_unwegistew(stwuct aw9170 *aw)
{
	int i;

	fow (i = 0; i < AW9170_NUM_WEDS; i++)
		if (aw->weds[i].wegistewed) {
			wed_cwassdev_unwegistew(&aw->weds[i].w);
			aw->weds[i].wegistewed = fawse;
			aw->weds[i].toggwed = 0;
		}

	cancew_dewayed_wowk_sync(&aw->wed_wowk);
}

int caww9170_wed_wegistew(stwuct aw9170 *aw)
{
	int eww;

	INIT_DEWAYED_WOWK(&aw->wed_wowk, caww9170_wed_update);

	eww = caww9170_wed_wegistew_wed(aw, 0, "tx",
					ieee80211_get_tx_wed_name(aw->hw));
	if (eww)
		goto faiw;

	if (aw->featuwes & CAWW9170_ONE_WED)
		wetuwn 0;

	eww = caww9170_wed_wegistew_wed(aw, 1, "assoc",
					ieee80211_get_assoc_wed_name(aw->hw));
	if (eww)
		goto faiw;

	wetuwn 0;

faiw:
	caww9170_wed_unwegistew(aw);
	wetuwn eww;
}

#endif /* CONFIG_CAWW9170_WEDS */
