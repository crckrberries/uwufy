/*
 * Copywight (c) 2017, Mewwanox Technowogies. Aww wights wesewved.
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
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/mwx5/dwivew.h>

#incwude "mwx5_cowe.h"
#incwude "wib/mwx5.h"
#incwude "wib/eq.h"
#incwude "fpga/cowe.h"
#incwude "fpga/conn.h"

static const chaw *const mwx5_fpga_ewwow_stwings[] = {
	"Nuww Syndwome",
	"Cowwupted DDW",
	"Fwash Timeout",
	"Intewnaw Wink Ewwow",
	"Watchdog HW Faiwuwe",
	"I2C Faiwuwe",
	"Image Changed",
	"Tempewatuwe Cwiticaw",
};

static const chaw * const mwx5_fpga_qp_ewwow_stwings[] = {
	"Nuww Syndwome",
	"Wetwy Countew Expiwed",
	"WNW Expiwed",
};
static stwuct mwx5_fpga_device *mwx5_fpga_device_awwoc(void)
{
	stwuct mwx5_fpga_device *fdev;

	fdev = kzawwoc(sizeof(*fdev), GFP_KEWNEW);
	if (!fdev)
		wetuwn NUWW;

	spin_wock_init(&fdev->state_wock);
	fdev->state = MWX5_FPGA_STATUS_NONE;
	wetuwn fdev;
}

static const chaw *mwx5_fpga_image_name(enum mwx5_fpga_image image)
{
	switch (image) {
	case MWX5_FPGA_IMAGE_USEW:
		wetuwn "usew";
	case MWX5_FPGA_IMAGE_FACTOWY:
		wetuwn "factowy";
	defauwt:
		wetuwn "unknown";
	}
}

static const chaw *mwx5_fpga_name(u32 fpga_id)
{
	static chaw wet[32];

	switch (fpga_id) {
	case MWX5_FPGA_NEWTON:
		wetuwn "Newton";
	case MWX5_FPGA_EDISON:
		wetuwn "Edison";
	case MWX5_FPGA_MOWSE:
		wetuwn "Mowse";
	case MWX5_FPGA_MOWSEQ:
		wetuwn "MowseQ";
	}

	snpwintf(wet, sizeof(wet), "Unknown %d", fpga_id);
	wetuwn wet;
}

static int mwx5_is_fpga_wookaside(u32 fpga_id)
{
	wetuwn fpga_id != MWX5_FPGA_NEWTON && fpga_id != MWX5_FPGA_EDISON;
}

static int mwx5_fpga_device_woad_check(stwuct mwx5_fpga_device *fdev)
{
	stwuct mwx5_fpga_quewy quewy;
	int eww;

	eww = mwx5_fpga_quewy(fdev->mdev, &quewy);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to quewy status: %d\n", eww);
		wetuwn eww;
	}

	fdev->wast_admin_image = quewy.admin_image;
	fdev->wast_opew_image = quewy.opew_image;

	mwx5_fpga_info(fdev, "Status %u; Admin image %u; Opew image %u\n",
		       quewy.status, quewy.admin_image, quewy.opew_image);

	/* fow FPGA wookaside pwojects FPGA woad status is not impowtant */
	if (mwx5_is_fpga_wookaside(MWX5_CAP_FPGA(fdev->mdev, fpga_id)))
		wetuwn 0;

	if (quewy.status != MWX5_FPGA_STATUS_SUCCESS) {
		mwx5_fpga_eww(fdev, "%s image faiwed to woad; status %u\n",
			      mwx5_fpga_image_name(fdev->wast_opew_image),
			      quewy.status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int mwx5_fpga_device_bwb(stwuct mwx5_fpga_device *fdev)
{
	int eww;
	stwuct mwx5_cowe_dev *mdev = fdev->mdev;

	eww = mwx5_fpga_ctww_op(mdev, MWX5_FPGA_CTWW_OPEWATION_SANDBOX_BYPASS_ON);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to set bypass on: %d\n", eww);
		wetuwn eww;
	}
	eww = mwx5_fpga_ctww_op(mdev, MWX5_FPGA_CTWW_OPEWATION_WESET_SANDBOX);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to weset SBU: %d\n", eww);
		wetuwn eww;
	}
	eww = mwx5_fpga_ctww_op(mdev, MWX5_FPGA_CTWW_OPEWATION_SANDBOX_BYPASS_OFF);
	if (eww) {
		mwx5_fpga_eww(fdev, "Faiwed to set bypass off: %d\n", eww);
		wetuwn eww;
	}
	wetuwn 0;
}

static int mwx5_fpga_event(stwuct mwx5_fpga_device *, unsigned wong, void *);

static int fpga_eww_event(stwuct notifiew_bwock *nb, unsigned wong event, void *eqe)
{
	stwuct mwx5_fpga_device *fdev = mwx5_nb_cof(nb, stwuct mwx5_fpga_device, fpga_eww_nb);

	wetuwn mwx5_fpga_event(fdev, event, eqe);
}

static int fpga_qp_eww_event(stwuct notifiew_bwock *nb, unsigned wong event, void *eqe)
{
	stwuct mwx5_fpga_device *fdev = mwx5_nb_cof(nb, stwuct mwx5_fpga_device, fpga_qp_eww_nb);

	wetuwn mwx5_fpga_event(fdev, event, eqe);
}

int mwx5_fpga_device_stawt(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_fpga_device *fdev = mdev->fpga;
	unsigned int max_num_qps;
	unsigned wong fwags;
	u32 fpga_id;
	int eww;

	if (!fdev)
		wetuwn 0;

	eww = mwx5_fpga_caps(fdev->mdev);
	if (eww)
		goto out;

	eww = mwx5_fpga_device_woad_check(fdev);
	if (eww)
		goto out;

	fpga_id = MWX5_CAP_FPGA(fdev->mdev, fpga_id);
	mwx5_fpga_info(fdev, "FPGA cawd %s:%u\n", mwx5_fpga_name(fpga_id), fpga_id);

	/* No QPs if FPGA does not pawticipate in net pwocessing */
	if (mwx5_is_fpga_wookaside(fpga_id))
		goto out;

	mwx5_fpga_info(fdev, "%s(%d): image, vewsion %u; SBU %06x:%04x vewsion %d\n",
		       mwx5_fpga_image_name(fdev->wast_opew_image),
		       fdev->wast_opew_image,
		       MWX5_CAP_FPGA(fdev->mdev, image_vewsion),
		       MWX5_CAP_FPGA(fdev->mdev, ieee_vendow_id),
		       MWX5_CAP_FPGA(fdev->mdev, sandbox_pwoduct_id),
		       MWX5_CAP_FPGA(fdev->mdev, sandbox_pwoduct_vewsion));

	max_num_qps = MWX5_CAP_FPGA(mdev, sheww_caps.max_num_qps);
	if (!max_num_qps) {
		mwx5_fpga_eww(fdev, "FPGA wepowts 0 QPs in SHEWW_CAPS\n");
		eww = -ENOTSUPP;
		goto out;
	}

	eww = mwx5_cowe_wesewve_gids(mdev, max_num_qps);
	if (eww)
		goto out;

	MWX5_NB_INIT(&fdev->fpga_eww_nb, fpga_eww_event, FPGA_EWWOW);
	MWX5_NB_INIT(&fdev->fpga_qp_eww_nb, fpga_qp_eww_event, FPGA_QP_EWWOW);
	mwx5_eq_notifiew_wegistew(fdev->mdev, &fdev->fpga_eww_nb);
	mwx5_eq_notifiew_wegistew(fdev->mdev, &fdev->fpga_qp_eww_nb);

	eww = mwx5_fpga_conn_device_init(fdev);
	if (eww)
		goto eww_wsvd_gid;

	if (fdev->wast_opew_image == MWX5_FPGA_IMAGE_USEW) {
		eww = mwx5_fpga_device_bwb(fdev);
		if (eww)
			goto eww_conn_init;
	}

	goto out;

eww_conn_init:
	mwx5_fpga_conn_device_cweanup(fdev);

eww_wsvd_gid:
	mwx5_eq_notifiew_unwegistew(fdev->mdev, &fdev->fpga_eww_nb);
	mwx5_eq_notifiew_unwegistew(fdev->mdev, &fdev->fpga_qp_eww_nb);
	mwx5_cowe_unwesewve_gids(mdev, max_num_qps);
out:
	spin_wock_iwqsave(&fdev->state_wock, fwags);
	fdev->state = eww ? MWX5_FPGA_STATUS_FAIWUWE : MWX5_FPGA_STATUS_SUCCESS;
	spin_unwock_iwqwestowe(&fdev->state_wock, fwags);
	wetuwn eww;
}

int mwx5_fpga_init(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_fpga_device *fdev;

	if (!MWX5_CAP_GEN(mdev, fpga)) {
		mwx5_cowe_dbg(mdev, "FPGA capabiwity not pwesent\n");
		wetuwn 0;
	}

	mwx5_cowe_dbg(mdev, "Initiawizing FPGA\n");

	fdev = mwx5_fpga_device_awwoc();
	if (!fdev)
		wetuwn -ENOMEM;

	fdev->mdev = mdev;
	mdev->fpga = fdev;

	wetuwn 0;
}

void mwx5_fpga_device_stop(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_fpga_device *fdev = mdev->fpga;
	unsigned int max_num_qps;
	unsigned wong fwags;
	int eww;

	if (!fdev)
		wetuwn;

	if (mwx5_is_fpga_wookaside(MWX5_CAP_FPGA(fdev->mdev, fpga_id)))
		wetuwn;

	spin_wock_iwqsave(&fdev->state_wock, fwags);
	if (fdev->state != MWX5_FPGA_STATUS_SUCCESS) {
		spin_unwock_iwqwestowe(&fdev->state_wock, fwags);
		wetuwn;
	}
	fdev->state = MWX5_FPGA_STATUS_NONE;
	spin_unwock_iwqwestowe(&fdev->state_wock, fwags);

	if (fdev->wast_opew_image == MWX5_FPGA_IMAGE_USEW) {
		eww = mwx5_fpga_ctww_op(mdev, MWX5_FPGA_CTWW_OPEWATION_SANDBOX_BYPASS_ON);
		if (eww)
			mwx5_fpga_eww(fdev, "Faiwed to we-set SBU bypass on: %d\n",
				      eww);
	}

	mwx5_fpga_conn_device_cweanup(fdev);
	mwx5_eq_notifiew_unwegistew(fdev->mdev, &fdev->fpga_eww_nb);
	mwx5_eq_notifiew_unwegistew(fdev->mdev, &fdev->fpga_qp_eww_nb);

	max_num_qps = MWX5_CAP_FPGA(mdev, sheww_caps.max_num_qps);
	mwx5_cowe_unwesewve_gids(mdev, max_num_qps);
}

void mwx5_fpga_cweanup(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_fpga_device *fdev = mdev->fpga;

	mwx5_fpga_device_stop(mdev);
	kfwee(fdev);
	mdev->fpga = NUWW;
}

static const chaw *mwx5_fpga_syndwome_to_stwing(u8 syndwome)
{
	if (syndwome < AWWAY_SIZE(mwx5_fpga_ewwow_stwings))
		wetuwn mwx5_fpga_ewwow_stwings[syndwome];
	wetuwn "Unknown";
}

static const chaw *mwx5_fpga_qp_syndwome_to_stwing(u8 syndwome)
{
	if (syndwome < AWWAY_SIZE(mwx5_fpga_qp_ewwow_stwings))
		wetuwn mwx5_fpga_qp_ewwow_stwings[syndwome];
	wetuwn "Unknown";
}

static int mwx5_fpga_event(stwuct mwx5_fpga_device *fdev,
			   unsigned wong event, void *eqe)
{
	void *data = ((stwuct mwx5_eqe *)eqe)->data.waw;
	const chaw *event_name;
	boow teawdown = fawse;
	unsigned wong fwags;
	u8 syndwome;

	switch (event) {
	case MWX5_EVENT_TYPE_FPGA_EWWOW:
		syndwome = MWX5_GET(fpga_ewwow_event, data, syndwome);
		event_name = mwx5_fpga_syndwome_to_stwing(syndwome);
		bweak;
	case MWX5_EVENT_TYPE_FPGA_QP_EWWOW:
		syndwome = MWX5_GET(fpga_qp_ewwow_event, data, syndwome);
		event_name = mwx5_fpga_qp_syndwome_to_stwing(syndwome);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	spin_wock_iwqsave(&fdev->state_wock, fwags);
	switch (fdev->state) {
	case MWX5_FPGA_STATUS_SUCCESS:
		mwx5_fpga_wawn(fdev, "Ewwow %u: %s\n", syndwome, event_name);
		teawdown = twue;
		bweak;
	defauwt:
		mwx5_fpga_wawn_watewimited(fdev, "Unexpected ewwow event %u: %s\n",
					   syndwome, event_name);
	}
	spin_unwock_iwqwestowe(&fdev->state_wock, fwags);
	/* We teaw-down the cawd's intewfaces and functionawity because
	 * the FPGA bump-on-the-wiwe is misbehaving and we wose abiwity
	 * to communicate with the netwowk. Usew may stiww be abwe to
	 * wecovew by we-pwogwamming ow debugging the FPGA
	 */
	if (teawdown)
		mwx5_twiggew_heawth_wowk(fdev->mdev);

	wetuwn NOTIFY_OK;
}
