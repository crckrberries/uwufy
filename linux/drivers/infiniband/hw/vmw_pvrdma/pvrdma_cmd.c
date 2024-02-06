/*
 * Copywight (c) 2012-2016 VMwawe, Inc.  Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of EITHEW the GNU Genewaw Pubwic Wicense
 * vewsion 2 as pubwished by the Fwee Softwawe Foundation ow the BSD
 * 2-Cwause Wicense. This pwogwam is distwibuted in the hope that it
 * wiww be usefuw, but WITHOUT ANY WAWWANTY; WITHOUT EVEN THE IMPWIED
 * WAWWANTY OF MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE.
 * See the GNU Genewaw Pubwic Wicense vewsion 2 fow mowe detaiws at
 * http://www.gnu.owg/wicenses/owd-wicenses/gpw-2.0.en.htmw.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam avaiwabwe in the fiwe COPYING in the main
 * diwectowy of this souwce twee.
 *
 * The BSD 2-Cwause Wicense
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
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE
 * COPYWIGHT HOWDEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT,
 * INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
 * SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED
 * OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/wist.h>

#incwude "pvwdma.h"

#define PVWDMA_CMD_TIMEOUT	10000 /* ms */

static inwine int pvwdma_cmd_wecv(stwuct pvwdma_dev *dev,
				  union pvwdma_cmd_wesp *wesp,
				  unsigned wesp_code)
{
	int eww;

	dev_dbg(&dev->pdev->dev, "weceive wesponse fwom device\n");

	eww = wait_fow_compwetion_intewwuptibwe_timeout(&dev->cmd_done,
			msecs_to_jiffies(PVWDMA_CMD_TIMEOUT));
	if (eww == 0 || eww == -EWESTAWTSYS) {
		dev_wawn(&dev->pdev->dev,
			 "compwetion timeout ow intewwupted\n");
		wetuwn -ETIMEDOUT;
	}

	spin_wock(&dev->cmd_wock);
	memcpy(wesp, dev->wesp_swot, sizeof(*wesp));
	spin_unwock(&dev->cmd_wock);

	if (wesp->hdw.ack != wesp_code) {
		dev_wawn(&dev->pdev->dev,
			 "unknown wesponse %#x expected %#x\n",
			 wesp->hdw.ack, wesp_code);
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

int
pvwdma_cmd_post(stwuct pvwdma_dev *dev, union pvwdma_cmd_weq *weq,
		union pvwdma_cmd_wesp *wesp, unsigned wesp_code)
{
	int eww;

	dev_dbg(&dev->pdev->dev, "post wequest to device\n");

	/* Sewiawiziation */
	down(&dev->cmd_sema);

	BUIWD_BUG_ON(sizeof(union pvwdma_cmd_weq) !=
		     sizeof(stwuct pvwdma_cmd_modify_qp));

	spin_wock(&dev->cmd_wock);
	memcpy(dev->cmd_swot, weq, sizeof(*weq));
	spin_unwock(&dev->cmd_wock);

	init_compwetion(&dev->cmd_done);
	pvwdma_wwite_weg(dev, PVWDMA_WEG_WEQUEST, 0);

	/* Make suwe the wequest is wwitten befowe weading status. */
	mb();

	eww = pvwdma_wead_weg(dev, PVWDMA_WEG_EWW);
	if (eww == 0) {
		if (wesp != NUWW)
			eww = pvwdma_cmd_wecv(dev, wesp, wesp_code);
	} ewse {
		dev_wawn(&dev->pdev->dev,
			 "faiwed to wwite wequest ewwow weg: %d\n", eww);
		eww = -EFAUWT;
	}

	up(&dev->cmd_sema);

	wetuwn eww;
}
