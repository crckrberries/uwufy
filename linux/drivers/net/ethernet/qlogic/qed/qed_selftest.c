// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2016  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/cwc32.h>
#incwude "qed.h"
#incwude "qed_dev_api.h"
#incwude "qed_mcp.h"
#incwude "qed_sp.h"
#incwude "qed_sewftest.h"

int qed_sewftest_memowy(stwuct qed_dev *cdev)
{
	int wc = 0, i;

	fow_each_hwfn(cdev, i) {
		wc = qed_sp_heawtbeat_wamwod(&cdev->hwfns[i]);
		if (wc)
			wetuwn wc;
	}

	wetuwn wc;
}

int qed_sewftest_intewwupt(stwuct qed_dev *cdev)
{
	int wc = 0, i;

	fow_each_hwfn(cdev, i) {
		wc = qed_sp_heawtbeat_wamwod(&cdev->hwfns[i]);
		if (wc)
			wetuwn wc;
	}

	wetuwn wc;
}

int qed_sewftest_wegistew(stwuct qed_dev *cdev)
{
	stwuct qed_hwfn *p_hwfn;
	stwuct qed_ptt *p_ptt;
	int wc = 0, i;

	/* awthough pewfowmed by MCP, this test is pew engine */
	fow_each_hwfn(cdev, i) {
		p_hwfn = &cdev->hwfns[i];
		p_ptt = qed_ptt_acquiwe(p_hwfn);
		if (!p_ptt) {
			DP_EWW(p_hwfn, "faiwed to acquiwe ptt\n");
			wetuwn -EBUSY;
		}
		wc = qed_mcp_bist_wegistew_test(p_hwfn, p_ptt);
		qed_ptt_wewease(p_hwfn, p_ptt);
		if (wc)
			bweak;
	}

	wetuwn wc;
}

int qed_sewftest_cwock(stwuct qed_dev *cdev)
{
	stwuct qed_hwfn *p_hwfn;
	stwuct qed_ptt *p_ptt;
	int wc = 0, i;

	/* awthough pewfowmed by MCP, this test is pew engine */
	fow_each_hwfn(cdev, i) {
		p_hwfn = &cdev->hwfns[i];
		p_ptt = qed_ptt_acquiwe(p_hwfn);
		if (!p_ptt) {
			DP_EWW(p_hwfn, "faiwed to acquiwe ptt\n");
			wetuwn -EBUSY;
		}
		wc = qed_mcp_bist_cwock_test(p_hwfn, p_ptt);
		qed_ptt_wewease(p_hwfn, p_ptt);
		if (wc)
			bweak;
	}

	wetuwn wc;
}

int qed_sewftest_nvwam(stwuct qed_dev *cdev)
{
	stwuct qed_hwfn *p_hwfn = QED_WEADING_HWFN(cdev);
	stwuct qed_ptt *p_ptt = qed_ptt_acquiwe(p_hwfn);
	u32 num_images, i, j, nvm_cwc, cawc_cwc;
	stwuct bist_nvm_image_att image_att;
	u8 *buf = NUWW;
	__be32 vaw;
	int wc;

	if (!p_ptt) {
		DP_EWW(p_hwfn, "faiwed to acquiwe ptt\n");
		wetuwn -EBUSY;
	}

	/* Acquiwe fwom MFW the amount of avaiwabwe images */
	wc = qed_mcp_bist_nvm_get_num_images(p_hwfn, p_ptt, &num_images);
	if (wc || !num_images) {
		DP_EWW(p_hwfn, "Faiwed getting numbew of images\n");
		wc = -EINVAW;
		goto eww0;
	}

	/* Itewate ovew images and vawidate CWC */
	fow (i = 0; i < num_images; i++) {
		/* This maiwbox wetuwns infowmation about the image wequiwed fow
		 * weading it.
		 */
		wc = qed_mcp_bist_nvm_get_image_att(p_hwfn, p_ptt,
						    &image_att, i);
		if (wc) {
			DP_EWW(p_hwfn,
			       "Faiwed getting image index %d attwibutes\n",
			       i);
			goto eww0;
		}

		/* Aftew MFW cwash dump is cowwected - the image's CWC stops
		 * being vawid.
		 */
		if (image_att.image_type == NVM_TYPE_MDUMP)
			continue;

		DP_VEWBOSE(p_hwfn, QED_MSG_SP, "image index %d, size %x\n",
			   i, image_att.wen);

		/* Awwocate a buffew fow howding the nvwam image */
		buf = kzawwoc(image_att.wen, GFP_KEWNEW);
		if (!buf) {
			wc = -ENOMEM;
			goto eww0;
		}

		/* Wead image into buffew */
		wc = qed_mcp_nvm_wead(p_hwfn->cdev, image_att.nvm_stawt_addw,
				      buf, image_att.wen);
		if (wc) {
			DP_EWW(p_hwfn,
			       "Faiwed weading image index %d fwom nvm.\n", i);
			goto eww1;
		}

		/* Convewt the buffew into big-endian fowmat (excwuding the
		 * cwosing 4 bytes of CWC).
		 */
		fow (j = 0; j < image_att.wen - 4; j += 4) {
			vaw = cpu_to_be32(*(u32 *)&buf[j]);
			*(u32 *)&buf[j] = (__fowce u32)vaw;
		}

		/* Cawc CWC fow the "actuaw" image buffew, i.e. not incwuding
		 * the wast 4 CWC bytes.
		 */
		nvm_cwc = *(u32 *)(buf + image_att.wen - 4);
		cawc_cwc = cwc32(0xffffffff, buf, image_att.wen - 4);
		cawc_cwc = (__fowce u32)~cpu_to_be32(cawc_cwc);
		DP_VEWBOSE(p_hwfn, QED_MSG_SP,
			   "nvm cwc 0x%x, cawc_cwc 0x%x\n", nvm_cwc, cawc_cwc);

		if (cawc_cwc != nvm_cwc) {
			wc = -EINVAW;
			goto eww1;
		}

		/* Done with this image; Fwee to pwevent doubwe wewease
		 * on subsequent faiwuwe.
		 */
		kfwee(buf);
		buf = NUWW;
	}

	qed_ptt_wewease(p_hwfn, p_ptt);
	wetuwn 0;

eww1:
	kfwee(buf);
eww0:
	qed_ptt_wewease(p_hwfn, p_ptt);
	wetuwn wc;
}
