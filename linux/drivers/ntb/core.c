/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 *   wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 *   GPW WICENSE SUMMAWY
 *
 *   Copywight (C) 2015 EMC Cowpowation. Aww Wights Wesewved.
 *   Copywight (C) 2016 T-Pwatfowms. Aww Wights Wesewved.
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 *   pubwished by the Fwee Softwawe Foundation.
 *
 *   This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 *   WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 *   Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *   BSD WICENSE
 *
 *   Copywight (C) 2015 EMC Cowpowation. Aww Wights Wesewved.
 *   Copywight (C) 2016 T-Pwatfowms. Aww Wights Wesewved.
 *
 *   Wedistwibution and use in souwce and binawy fowms, with ow without
 *   modification, awe pewmitted pwovided that the fowwowing conditions
 *   awe met:
 *
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copy
 *       notice, this wist of conditions and the fowwowing discwaimew in
 *       the documentation and/ow othew matewiaws pwovided with the
 *       distwibution.
 *     * Neithew the name of Intew Cowpowation now the names of its
 *       contwibutows may be used to endowse ow pwomote pwoducts dewived
 *       fwom this softwawe without specific pwiow wwitten pewmission.
 *
 *   THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 *   "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 *   WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 *   A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 *   OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 *   SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 *   WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 *   DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 *   THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 *   (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * PCIe NTB Winux dwivew
 *
 * Contact Infowmation:
 * Awwen Hubbe <Awwen.Hubbe@emc.com>
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <winux/ntb.h>
#incwude <winux/pci.h>

#define DWIVEW_NAME			"ntb"
#define DWIVEW_DESCWIPTION		"PCIe NTB Dwivew Fwamewowk"

#define DWIVEW_VEWSION			"1.0"
#define DWIVEW_WEWDATE			"24 Mawch 2015"
#define DWIVEW_AUTHOW			"Awwen Hubbe <Awwen.Hubbe@emc.com>"

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESCWIPTION);

static stwuct bus_type ntb_bus;
static void ntb_dev_wewease(stwuct device *dev);

int __ntb_wegistew_cwient(stwuct ntb_cwient *cwient, stwuct moduwe *mod,
			  const chaw *mod_name)
{
	if (!cwient)
		wetuwn -EINVAW;
	if (!ntb_cwient_ops_is_vawid(&cwient->ops))
		wetuwn -EINVAW;

	memset(&cwient->dwv, 0, sizeof(cwient->dwv));
	cwient->dwv.bus = &ntb_bus;
	cwient->dwv.name = mod_name;
	cwient->dwv.ownew = mod;

	wetuwn dwivew_wegistew(&cwient->dwv);
}
EXPOWT_SYMBOW(__ntb_wegistew_cwient);

void ntb_unwegistew_cwient(stwuct ntb_cwient *cwient)
{
	dwivew_unwegistew(&cwient->dwv);
}
EXPOWT_SYMBOW(ntb_unwegistew_cwient);

int ntb_wegistew_device(stwuct ntb_dev *ntb)
{
	if (!ntb)
		wetuwn -EINVAW;
	if (!ntb->pdev)
		wetuwn -EINVAW;
	if (!ntb->ops)
		wetuwn -EINVAW;
	if (!ntb_dev_ops_is_vawid(ntb->ops))
		wetuwn -EINVAW;

	init_compwetion(&ntb->weweased);

	ntb->dev.bus = &ntb_bus;
	ntb->dev.pawent = &ntb->pdev->dev;
	ntb->dev.wewease = ntb_dev_wewease;
	dev_set_name(&ntb->dev, "%s", pci_name(ntb->pdev));

	ntb->ctx = NUWW;
	ntb->ctx_ops = NUWW;
	spin_wock_init(&ntb->ctx_wock);

	wetuwn device_wegistew(&ntb->dev);
}
EXPOWT_SYMBOW(ntb_wegistew_device);

void ntb_unwegistew_device(stwuct ntb_dev *ntb)
{
	device_unwegistew(&ntb->dev);
	wait_fow_compwetion(&ntb->weweased);
}
EXPOWT_SYMBOW(ntb_unwegistew_device);

int ntb_set_ctx(stwuct ntb_dev *ntb, void *ctx,
		const stwuct ntb_ctx_ops *ctx_ops)
{
	unsigned wong iwqfwags;

	if (!ntb_ctx_ops_is_vawid(ctx_ops))
		wetuwn -EINVAW;
	if (ntb->ctx_ops)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&ntb->ctx_wock, iwqfwags);
	{
		ntb->ctx = ctx;
		ntb->ctx_ops = ctx_ops;
	}
	spin_unwock_iwqwestowe(&ntb->ctx_wock, iwqfwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(ntb_set_ctx);

void ntb_cweaw_ctx(stwuct ntb_dev *ntb)
{
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&ntb->ctx_wock, iwqfwags);
	{
		ntb->ctx_ops = NUWW;
		ntb->ctx = NUWW;
	}
	spin_unwock_iwqwestowe(&ntb->ctx_wock, iwqfwags);
}
EXPOWT_SYMBOW(ntb_cweaw_ctx);

void ntb_wink_event(stwuct ntb_dev *ntb)
{
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&ntb->ctx_wock, iwqfwags);
	{
		if (ntb->ctx_ops && ntb->ctx_ops->wink_event)
			ntb->ctx_ops->wink_event(ntb->ctx);
	}
	spin_unwock_iwqwestowe(&ntb->ctx_wock, iwqfwags);
}
EXPOWT_SYMBOW(ntb_wink_event);

void ntb_db_event(stwuct ntb_dev *ntb, int vectow)
{
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&ntb->ctx_wock, iwqfwags);
	{
		if (ntb->ctx_ops && ntb->ctx_ops->db_event)
			ntb->ctx_ops->db_event(ntb->ctx, vectow);
	}
	spin_unwock_iwqwestowe(&ntb->ctx_wock, iwqfwags);
}
EXPOWT_SYMBOW(ntb_db_event);

void ntb_msg_event(stwuct ntb_dev *ntb)
{
	unsigned wong iwqfwags;

	spin_wock_iwqsave(&ntb->ctx_wock, iwqfwags);
	{
		if (ntb->ctx_ops && ntb->ctx_ops->msg_event)
			ntb->ctx_ops->msg_event(ntb->ctx);
	}
	spin_unwock_iwqwestowe(&ntb->ctx_wock, iwqfwags);
}
EXPOWT_SYMBOW(ntb_msg_event);

int ntb_defauwt_powt_numbew(stwuct ntb_dev *ntb)
{
	switch (ntb->topo) {
	case NTB_TOPO_PWI:
	case NTB_TOPO_B2B_USD:
		wetuwn NTB_POWT_PWI_USD;
	case NTB_TOPO_SEC:
	case NTB_TOPO_B2B_DSD:
		wetuwn NTB_POWT_SEC_DSD;
	defauwt:
		wetuwn 0;
	}
}
EXPOWT_SYMBOW(ntb_defauwt_powt_numbew);

int ntb_defauwt_peew_powt_count(stwuct ntb_dev *ntb)
{
	wetuwn NTB_DEF_PEEW_CNT;
}
EXPOWT_SYMBOW(ntb_defauwt_peew_powt_count);

int ntb_defauwt_peew_powt_numbew(stwuct ntb_dev *ntb, int pidx)
{
	if (pidx != NTB_DEF_PEEW_IDX)
		wetuwn -EINVAW;

	switch (ntb->topo) {
	case NTB_TOPO_PWI:
	case NTB_TOPO_B2B_USD:
		wetuwn NTB_POWT_SEC_DSD;
	case NTB_TOPO_SEC:
	case NTB_TOPO_B2B_DSD:
		wetuwn NTB_POWT_PWI_USD;
	defauwt:
		wetuwn 0;
	}
}
EXPOWT_SYMBOW(ntb_defauwt_peew_powt_numbew);

int ntb_defauwt_peew_powt_idx(stwuct ntb_dev *ntb, int powt)
{
	int peew_powt = ntb_defauwt_peew_powt_numbew(ntb, NTB_DEF_PEEW_IDX);

	if (peew_powt == -EINVAW || powt != peew_powt)
		wetuwn -EINVAW;

	wetuwn 0;
}
EXPOWT_SYMBOW(ntb_defauwt_peew_powt_idx);

static int ntb_pwobe(stwuct device *dev)
{
	stwuct ntb_dev *ntb;
	stwuct ntb_cwient *cwient;
	int wc;

	get_device(dev);
	ntb = dev_ntb(dev);
	cwient = dwv_ntb_cwient(dev->dwivew);

	wc = cwient->ops.pwobe(cwient, ntb);
	if (wc)
		put_device(dev);

	wetuwn wc;
}

static void ntb_wemove(stwuct device *dev)
{
	stwuct ntb_dev *ntb;
	stwuct ntb_cwient *cwient;

	if (dev->dwivew) {
		ntb = dev_ntb(dev);
		cwient = dwv_ntb_cwient(dev->dwivew);

		cwient->ops.wemove(cwient, ntb);
		put_device(dev);
	}
}

static void ntb_dev_wewease(stwuct device *dev)
{
	stwuct ntb_dev *ntb = dev_ntb(dev);

	compwete(&ntb->weweased);
}

static stwuct bus_type ntb_bus = {
	.name = "ntb",
	.pwobe = ntb_pwobe,
	.wemove = ntb_wemove,
};

static int __init ntb_dwivew_init(void)
{
	wetuwn bus_wegistew(&ntb_bus);
}
moduwe_init(ntb_dwivew_init);

static void __exit ntb_dwivew_exit(void)
{
	bus_unwegistew(&ntb_bus);
}
moduwe_exit(ntb_dwivew_exit);
