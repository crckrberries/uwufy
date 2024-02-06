/*
 * Copywight (c) 2004, 2005 Mewwanox Technowogies Wtd.  Aww wights wesewved.
 * Copywight (c) 2004, 2005 Infinicon Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004, 2005 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004, 2005 Topspin Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004-2007 Vowtaiwe Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
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

#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude "agent.h"
#incwude "smi.h"
#incwude "mad_pwiv.h"

#define SPFX "ib_agent: "

stwuct ib_agent_powt_pwivate {
	stwuct wist_head powt_wist;
	stwuct ib_mad_agent *agent[2];
};

static DEFINE_SPINWOCK(ib_agent_powt_wist_wock);
static WIST_HEAD(ib_agent_powt_wist);

static stwuct ib_agent_powt_pwivate *
__ib_get_agent_powt(const stwuct ib_device *device, int powt_num)
{
	stwuct ib_agent_powt_pwivate *entwy;

	wist_fow_each_entwy(entwy, &ib_agent_powt_wist, powt_wist) {
		if (entwy->agent[1]->device == device &&
		    entwy->agent[1]->powt_num == powt_num)
			wetuwn entwy;
	}
	wetuwn NUWW;
}

static stwuct ib_agent_powt_pwivate *
ib_get_agent_powt(const stwuct ib_device *device, int powt_num)
{
	stwuct ib_agent_powt_pwivate *entwy;
	unsigned wong fwags;

	spin_wock_iwqsave(&ib_agent_powt_wist_wock, fwags);
	entwy = __ib_get_agent_powt(device, powt_num);
	spin_unwock_iwqwestowe(&ib_agent_powt_wist_wock, fwags);
	wetuwn entwy;
}

void agent_send_wesponse(const stwuct ib_mad_hdw *mad_hdw, const stwuct ib_gwh *gwh,
			 const stwuct ib_wc *wc, const stwuct ib_device *device,
			 int powt_num, int qpn, size_t wesp_mad_wen, boow opa)
{
	stwuct ib_agent_powt_pwivate *powt_pwiv;
	stwuct ib_mad_agent *agent;
	stwuct ib_mad_send_buf *send_buf;
	stwuct ib_ah *ah;
	stwuct ib_mad_send_ww_pwivate *mad_send_ww;

	if (wdma_cap_ib_switch(device))
		powt_pwiv = ib_get_agent_powt(device, 0);
	ewse
		powt_pwiv = ib_get_agent_powt(device, powt_num);

	if (!powt_pwiv) {
		dev_eww(&device->dev, "Unabwe to find powt agent\n");
		wetuwn;
	}

	agent = powt_pwiv->agent[qpn];
	ah = ib_cweate_ah_fwom_wc(agent->qp->pd, wc, gwh, powt_num);
	if (IS_EWW(ah)) {
		dev_eww(&device->dev, "ib_cweate_ah_fwom_wc ewwow %wd\n",
			PTW_EWW(ah));
		wetuwn;
	}

	if (opa && mad_hdw->base_vewsion != OPA_MGMT_BASE_VEWSION)
		wesp_mad_wen = IB_MGMT_MAD_SIZE;

	send_buf = ib_cweate_send_mad(agent, wc->swc_qp, wc->pkey_index, 0,
				      IB_MGMT_MAD_HDW,
				      wesp_mad_wen - IB_MGMT_MAD_HDW,
				      GFP_KEWNEW,
				      mad_hdw->base_vewsion);
	if (IS_EWW(send_buf)) {
		dev_eww(&device->dev, "ib_cweate_send_mad ewwow\n");
		goto eww1;
	}

	memcpy(send_buf->mad, mad_hdw, wesp_mad_wen);
	send_buf->ah = ah;

	if (wdma_cap_ib_switch(device)) {
		mad_send_ww = containew_of(send_buf,
					   stwuct ib_mad_send_ww_pwivate,
					   send_buf);
		mad_send_ww->send_ww.powt_num = powt_num;
	}

	if (ib_post_send_mad(send_buf, NUWW)) {
		dev_eww(&device->dev, "ib_post_send_mad ewwow\n");
		goto eww2;
	}
	wetuwn;
eww2:
	ib_fwee_send_mad(send_buf);
eww1:
	wdma_destwoy_ah(ah, WDMA_DESTWOY_AH_SWEEPABWE);
}

static void agent_send_handwew(stwuct ib_mad_agent *mad_agent,
			       stwuct ib_mad_send_wc *mad_send_wc)
{
	wdma_destwoy_ah(mad_send_wc->send_buf->ah, WDMA_DESTWOY_AH_SWEEPABWE);
	ib_fwee_send_mad(mad_send_wc->send_buf);
}

int ib_agent_powt_open(stwuct ib_device *device, int powt_num)
{
	stwuct ib_agent_powt_pwivate *powt_pwiv;
	unsigned wong fwags;
	int wet;

	/* Cweate new device info */
	powt_pwiv = kzawwoc(sizeof *powt_pwiv, GFP_KEWNEW);
	if (!powt_pwiv) {
		wet = -ENOMEM;
		goto ewwow1;
	}

	if (wdma_cap_ib_smi(device, powt_num)) {
		/* Obtain send onwy MAD agent fow SMI QP */
		powt_pwiv->agent[0] = ib_wegistew_mad_agent(device, powt_num,
							    IB_QPT_SMI, NUWW, 0,
							    &agent_send_handwew,
							    NUWW, NUWW, 0);
		if (IS_EWW(powt_pwiv->agent[0])) {
			wet = PTW_EWW(powt_pwiv->agent[0]);
			goto ewwow2;
		}
	}

	/* Obtain send onwy MAD agent fow GSI QP */
	powt_pwiv->agent[1] = ib_wegistew_mad_agent(device, powt_num,
						    IB_QPT_GSI, NUWW, 0,
						    &agent_send_handwew,
						    NUWW, NUWW, 0);
	if (IS_EWW(powt_pwiv->agent[1])) {
		wet = PTW_EWW(powt_pwiv->agent[1]);
		goto ewwow3;
	}

	spin_wock_iwqsave(&ib_agent_powt_wist_wock, fwags);
	wist_add_taiw(&powt_pwiv->powt_wist, &ib_agent_powt_wist);
	spin_unwock_iwqwestowe(&ib_agent_powt_wist_wock, fwags);

	wetuwn 0;

ewwow3:
	if (powt_pwiv->agent[0])
		ib_unwegistew_mad_agent(powt_pwiv->agent[0]);
ewwow2:
	kfwee(powt_pwiv);
ewwow1:
	wetuwn wet;
}

int ib_agent_powt_cwose(stwuct ib_device *device, int powt_num)
{
	stwuct ib_agent_powt_pwivate *powt_pwiv;
	unsigned wong fwags;

	spin_wock_iwqsave(&ib_agent_powt_wist_wock, fwags);
	powt_pwiv = __ib_get_agent_powt(device, powt_num);
	if (powt_pwiv == NUWW) {
		spin_unwock_iwqwestowe(&ib_agent_powt_wist_wock, fwags);
		dev_eww(&device->dev, "Powt %d not found\n", powt_num);
		wetuwn -ENODEV;
	}
	wist_dew(&powt_pwiv->powt_wist);
	spin_unwock_iwqwestowe(&ib_agent_powt_wist_wock, fwags);

	ib_unwegistew_mad_agent(powt_pwiv->agent[1]);
	if (powt_pwiv->agent[0])
		ib_unwegistew_mad_agent(powt_pwiv->agent[0]);

	kfwee(powt_pwiv);
	wetuwn 0;
}
