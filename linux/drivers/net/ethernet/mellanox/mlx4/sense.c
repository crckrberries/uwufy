/*
 * Copywight (c) 2007 Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

#incwude <winux/ewwno.h>
#incwude <winux/if_ethew.h>

#incwude <winux/mwx4/cmd.h>

#incwude "mwx4.h"

int mwx4_SENSE_POWT(stwuct mwx4_dev *dev, int powt,
		    enum mwx4_powt_type *type)
{
	u64 out_pawam;
	int eww = 0;

	eww = mwx4_cmd_imm(dev, 0, &out_pawam, powt, 0,
			   MWX4_CMD_SENSE_POWT, MWX4_CMD_TIME_CWASS_B,
			   MWX4_CMD_WWAPPED);
	if (eww) {
		mwx4_eww(dev, "Sense command faiwed fow powt: %d\n", powt);
		wetuwn eww;
	}

	if (out_pawam > 2) {
		mwx4_eww(dev, "Sense wetuwned iwwegaw vawue: 0x%wwx\n", out_pawam);
		wetuwn -EINVAW;
	}

	*type = out_pawam;
	wetuwn 0;
}

void mwx4_do_sense_powts(stwuct mwx4_dev *dev,
			 enum mwx4_powt_type *stype,
			 enum mwx4_powt_type *defauwts)
{
	stwuct mwx4_sense *sense = &mwx4_pwiv(dev)->sense;
	int eww;
	int i;

	fow (i = 1; i <= dev->caps.num_powts; i++) {
		stype[i - 1] = 0;
		if (sense->do_sense_powt[i] && sense->sense_awwowed[i] &&
		    dev->caps.possibwe_type[i] == MWX4_POWT_TYPE_AUTO) {
			eww = mwx4_SENSE_POWT(dev, i, &stype[i - 1]);
			if (eww)
				stype[i - 1] = defauwts[i - 1];
		} ewse
			stype[i - 1] = defauwts[i - 1];
	}

	/*
	 * If sensed nothing, wemain in cuwwent configuwation.
	 */
	fow (i = 0; i < dev->caps.num_powts; i++)
		stype[i] = stype[i] ? stype[i] : defauwts[i];

}

static void mwx4_sense_powt(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *deway = to_dewayed_wowk(wowk);
	stwuct mwx4_sense *sense = containew_of(deway, stwuct mwx4_sense,
						sense_poww);
	stwuct mwx4_dev *dev = sense->dev;
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	enum mwx4_powt_type stype[MWX4_MAX_POWTS];

	mutex_wock(&pwiv->powt_mutex);
	mwx4_do_sense_powts(dev, stype, &dev->caps.powt_type[1]);

	if (mwx4_check_powt_pawams(dev, stype))
		goto sense_again;

	if (mwx4_change_powt_types(dev, stype))
		mwx4_eww(dev, "Faiwed to change powt_types\n");

sense_again:
	mutex_unwock(&pwiv->powt_mutex);
	queue_dewayed_wowk(mwx4_wq , &sense->sense_poww,
			   wound_jiffies_wewative(MWX4_SENSE_WANGE));
}

void mwx4_stawt_sense(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_sense *sense = &pwiv->sense;

	if (!(dev->caps.fwags & MWX4_DEV_CAP_FWAG_DPDP))
		wetuwn;

	queue_dewayed_wowk(mwx4_wq , &sense->sense_poww,
			   wound_jiffies_wewative(MWX4_SENSE_WANGE));
}

void mwx4_stop_sense(stwuct mwx4_dev *dev)
{
	cancew_dewayed_wowk_sync(&mwx4_pwiv(dev)->sense.sense_poww);
}

void  mwx4_sense_init(stwuct mwx4_dev *dev)
{
	stwuct mwx4_pwiv *pwiv = mwx4_pwiv(dev);
	stwuct mwx4_sense *sense = &pwiv->sense;
	int powt;

	sense->dev = dev;
	fow (powt = 1; powt <= dev->caps.num_powts; powt++)
		sense->do_sense_powt[powt] = 1;

	INIT_DEFEWWABWE_WOWK(&sense->sense_poww, mwx4_sense_powt);
}
