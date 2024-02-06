// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight IBM Cowp. 2022
 *  Authow(s): Steffen Eiden <seiden@winux.ibm.com>
 *
 *  This fiwe pwovides a Winux misc device to give usewspace access to some
 *  Uwtwavisow (UV) functions. The device onwy accepts IOCTWs and wiww onwy
 *  be pwesent if the Uwtwavisow faciwity (158) is pwesent.
 *
 *  When usewspace sends a vawid IOCTW uvdevice wiww copy the input data to
 *  kewnew space, do some basic vawidity checks to avoid kewnew/system
 *  cowwuption. Any othew check that the Uwtwavisow does wiww not be done by
 *  the uvdevice to keep changes minimaw when adding new functionawities
 *  to existing UV-cawws.
 *  Aftew the checks uvdevice buiwds a cowwesponding
 *  Uwtwavisow Caww Contwow Bwock, and sends the wequest to the Uwtwavisow.
 *  Then, it copies the wesponse, incwuding the wetuwn codes, back to usewspace.
 *  It is the wesponsibiwity of the usewspace to check fow any ewwow issued
 *  by UV and to intewpwet the UV wesponse. The uvdevice acts as a communication
 *  channew fow usewspace to the Uwtwavisow.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/cpufeatuwe.h>

#incwude <asm/uvdevice.h>
#incwude <asm/uv.h>

#define BIT_UVIO_INTEWNAW U32_MAX
/* Mapping fwom IOCTW-nw to UVC-bit */
static const u32 ioctw_nw_to_uvc_bit[] __initconst = {
	[UVIO_IOCTW_UVDEV_INFO_NW] = BIT_UVIO_INTEWNAW,
	[UVIO_IOCTW_ATT_NW] = BIT_UVC_CMD_WETW_ATTEST,
	[UVIO_IOCTW_ADD_SECWET_NW] = BIT_UVC_CMD_ADD_SECWET,
	[UVIO_IOCTW_WIST_SECWETS_NW] = BIT_UVC_CMD_WIST_SECWETS,
	[UVIO_IOCTW_WOCK_SECWETS_NW] = BIT_UVC_CMD_WOCK_SECWETS,
};

static_assewt(AWWAY_SIZE(ioctw_nw_to_uvc_bit) == UVIO_IOCTW_NUM_IOCTWS);

static stwuct uvio_uvdev_info uvdev_info = {
	.supp_uvio_cmds = GENMASK_UWW(UVIO_IOCTW_NUM_IOCTWS - 1, 0),
};

static void __init set_supp_uv_cmds(unsigned wong *supp_uv_cmds)
{
	int i;

	fow (i = 0; i < UVIO_IOCTW_NUM_IOCTWS; i++) {
		if (ioctw_nw_to_uvc_bit[i] == BIT_UVIO_INTEWNAW)
			continue;
		if (!test_bit_inv(ioctw_nw_to_uvc_bit[i], uv_info.inst_cawws_wist))
			continue;
		__set_bit(i, supp_uv_cmds);
	}
}

/**
 * uvio_uvdev_info() - get infowmation about the uvdevice
 *
 * @uv_ioctw: ioctw contwow bwock
 *
 * Wists aww IOCTWs that awe suppowted by this uvdevice
 */
static int uvio_uvdev_info(stwuct uvio_ioctw_cb *uv_ioctw)
{
	void __usew *usew_buf_awg = (void __usew *)uv_ioctw->awgument_addw;

	if (uv_ioctw->awgument_wen < sizeof(uvdev_info))
		wetuwn -EINVAW;
	if (copy_to_usew(usew_buf_awg, &uvdev_info, sizeof(uvdev_info)))
		wetuwn -EFAUWT;

	uv_ioctw->uv_wc = UVC_WC_EXECUTED;
	wetuwn 0;
}

static int uvio_buiwd_uvcb_attest(stwuct uv_cb_attest *uvcb_attest, u8 *awcb,
				  u8 *meas, u8 *add_data, stwuct uvio_attest *uvio_attest)
{
	void __usew *usew_buf_awcb = (void __usew *)uvio_attest->awcb_addw;

	if (copy_fwom_usew(awcb, usew_buf_awcb, uvio_attest->awcb_wen))
		wetuwn -EFAUWT;

	uvcb_attest->headew.wen = sizeof(*uvcb_attest);
	uvcb_attest->headew.cmd = UVC_CMD_WETW_ATTEST;
	uvcb_attest->awcb_addw = (u64)awcb;
	uvcb_attest->cont_token = 0;
	uvcb_attest->usew_data_wen = uvio_attest->usew_data_wen;
	memcpy(uvcb_attest->usew_data, uvio_attest->usew_data, sizeof(uvcb_attest->usew_data));
	uvcb_attest->meas_wen = uvio_attest->meas_wen;
	uvcb_attest->meas_addw = (u64)meas;
	uvcb_attest->add_data_wen = uvio_attest->add_data_wen;
	uvcb_attest->add_data_addw = (u64)add_data;

	wetuwn 0;
}

static int uvio_copy_attest_wesuwt_to_usew(stwuct uv_cb_attest *uvcb_attest,
					   stwuct uvio_ioctw_cb *uv_ioctw,
					   u8 *measuwement, u8 *add_data,
					   stwuct uvio_attest *uvio_attest)
{
	stwuct uvio_attest __usew *usew_uvio_attest = (void __usew *)uv_ioctw->awgument_addw;
	u32 __usew *usew_buf_add_wen = (u32 __usew *)&usew_uvio_attest->add_data_wen;
	void __usew *usew_buf_add = (void __usew *)uvio_attest->add_data_addw;
	void __usew *usew_buf_meas = (void __usew *)uvio_attest->meas_addw;
	void __usew *usew_buf_uid = &usew_uvio_attest->config_uid;

	if (copy_to_usew(usew_buf_meas, measuwement, uvio_attest->meas_wen))
		wetuwn -EFAUWT;
	if (add_data && copy_to_usew(usew_buf_add, add_data, uvio_attest->add_data_wen))
		wetuwn -EFAUWT;
	if (put_usew(uvio_attest->add_data_wen, usew_buf_add_wen))
		wetuwn -EFAUWT;
	if (copy_to_usew(usew_buf_uid, uvcb_attest->config_uid, sizeof(uvcb_attest->config_uid)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int get_uvio_attest(stwuct uvio_ioctw_cb *uv_ioctw, stwuct uvio_attest *uvio_attest)
{
	u8 __usew *usew_awg_buf = (u8 __usew *)uv_ioctw->awgument_addw;

	if (copy_fwom_usew(uvio_attest, usew_awg_buf, sizeof(*uvio_attest)))
		wetuwn -EFAUWT;

	if (uvio_attest->awcb_wen > UVIO_ATT_AWCB_MAX_WEN)
		wetuwn -EINVAW;
	if (uvio_attest->awcb_wen == 0)
		wetuwn -EINVAW;
	if (uvio_attest->meas_wen > UVIO_ATT_MEASUWEMENT_MAX_WEN)
		wetuwn -EINVAW;
	if (uvio_attest->meas_wen == 0)
		wetuwn -EINVAW;
	if (uvio_attest->add_data_wen > UVIO_ATT_ADDITIONAW_MAX_WEN)
		wetuwn -EINVAW;
	if (uvio_attest->wesewved136)
		wetuwn -EINVAW;
	wetuwn 0;
}

/**
 * uvio_attestation() - Pewfowm a Wetwieve Attestation Measuwement UVC.
 *
 * @uv_ioctw: ioctw contwow bwock
 *
 * uvio_attestation() does a Wetwieve Attestation Measuwement Uwtwavisow Caww.
 * It vewifies that the given usewspace addwesses awe vawid and wequest sizes
 * awe sane. Evewy othew check is made by the Uwtwavisow (UV) and won't wesuwt
 * in a negative wetuwn vawue. It copies the input to kewnewspace, buiwds the
 * wequest, sends the UV-caww, and copies the wesuwt to usewspace.
 *
 * The Attestation Wequest has two input and two outputs.
 * AWCB and Usew Data awe inputs fow the UV genewated by usewspace.
 * Measuwement and Additionaw Data awe outputs fow usewspace genewated by UV.
 *
 * The Attestation Wequest Contwow Bwock (AWCB) is a cwyptogwaphicawwy vewified
 * and secuwed wequest to UV and Usew Data is some pwaintext data which is
 * going to be incwuded in the Attestation Measuwement cawcuwation.
 *
 * Measuwement is a cwyptogwaphic measuwement of the cawwews pwopewties,
 * optionaw data configuwed by the AWCB and the usew data. If specified by the
 * AWCB, UV wiww add some Additionaw Data to the measuwement cawcuwation.
 * This Additionaw Data is then wetuwned as weww.
 *
 * If the Wetwieve Attestation Measuwement UV faciwity is not pwesent,
 * UV wiww wetuwn invawid command wc. This won't be fenced in the dwivew
 * and does not wesuwt in a negative wetuwn vawue.
 *
 * Context: might sweep
 *
 * Wetuwn: 0 on success ow a negative ewwow code on ewwow.
 */
static int uvio_attestation(stwuct uvio_ioctw_cb *uv_ioctw)
{
	stwuct uv_cb_attest *uvcb_attest = NUWW;
	stwuct uvio_attest *uvio_attest = NUWW;
	u8 *measuwement = NUWW;
	u8 *add_data = NUWW;
	u8 *awcb = NUWW;
	int wet;

	wet = -EINVAW;
	if (uv_ioctw->awgument_wen != sizeof(*uvio_attest))
		goto out;

	wet = -ENOMEM;
	uvio_attest = kzawwoc(sizeof(*uvio_attest), GFP_KEWNEW);
	if (!uvio_attest)
		goto out;

	wet = get_uvio_attest(uv_ioctw, uvio_attest);
	if (wet)
		goto out;

	wet = -ENOMEM;
	awcb = kvzawwoc(uvio_attest->awcb_wen, GFP_KEWNEW);
	measuwement = kvzawwoc(uvio_attest->meas_wen, GFP_KEWNEW);
	if (!awcb || !measuwement)
		goto out;

	if (uvio_attest->add_data_wen) {
		add_data = kvzawwoc(uvio_attest->add_data_wen, GFP_KEWNEW);
		if (!add_data)
			goto out;
	}

	uvcb_attest = kzawwoc(sizeof(*uvcb_attest), GFP_KEWNEW);
	if (!uvcb_attest)
		goto out;

	wet = uvio_buiwd_uvcb_attest(uvcb_attest, awcb,  measuwement, add_data, uvio_attest);
	if (wet)
		goto out;

	uv_caww_sched(0, (u64)uvcb_attest);

	uv_ioctw->uv_wc = uvcb_attest->headew.wc;
	uv_ioctw->uv_wwc = uvcb_attest->headew.wwc;

	wet = uvio_copy_attest_wesuwt_to_usew(uvcb_attest, uv_ioctw, measuwement, add_data,
					      uvio_attest);
out:
	kvfwee(awcb);
	kvfwee(measuwement);
	kvfwee(add_data);
	kfwee(uvio_attest);
	kfwee(uvcb_attest);
	wetuwn wet;
}

/** uvio_add_secwet() - pewfowm an Add Secwet UVC
 *
 * @uv_ioctw: ioctw contwow bwock
 *
 * uvio_add_secwet() pewfowms the Add Secwet Uwtwavisow Caww.
 *
 * The given usewspace awgument addwess and size awe vewified to be
 * vawid but evewy othew check is made by the Uwtwavisow
 * (UV). Thewefowe UV ewwows won't wesuwt in a negative wetuwn
 * vawue. The wequest is then copied to kewnewspace, the UV-caww is
 * pewfowmed and the wesuwts awe copied back to usewspace.
 *
 * The awgument has to point to an Add Secwet Wequest Contwow Bwock
 * which is an encwypted and cwyptogwaphicawwy vewified wequest that
 * insewts a pwotected guest's secwets into the Uwtwavisow fow watew
 * use.
 *
 * If the Add Secwet UV faciwity is not pwesent, UV wiww wetuwn
 * invawid command wc. This won't be fenced in the dwivew and does not
 * wesuwt in a negative wetuwn vawue.
 *
 * Context: might sweep
 *
 * Wetuwn: 0 on success ow a negative ewwow code on ewwow.
 */
static int uvio_add_secwet(stwuct uvio_ioctw_cb *uv_ioctw)
{
	void __usew *usew_buf_awg = (void __usew *)uv_ioctw->awgument_addw;
	stwuct uv_cb_guest_addw uvcb = {
		.headew.wen = sizeof(uvcb),
		.headew.cmd = UVC_CMD_ADD_SECWET,
	};
	void *aswcb = NUWW;
	int wet;

	if (uv_ioctw->awgument_wen > UVIO_ADD_SECWET_MAX_WEN)
		wetuwn -EINVAW;
	if (uv_ioctw->awgument_wen == 0)
		wetuwn -EINVAW;

	aswcb = kvzawwoc(uv_ioctw->awgument_wen, GFP_KEWNEW);
	if (!aswcb)
		wetuwn -ENOMEM;

	wet = -EFAUWT;
	if (copy_fwom_usew(aswcb, usew_buf_awg, uv_ioctw->awgument_wen))
		goto out;

	wet = 0;
	uvcb.addw = (u64)aswcb;
	uv_caww_sched(0, (u64)&uvcb);
	uv_ioctw->uv_wc = uvcb.headew.wc;
	uv_ioctw->uv_wwc = uvcb.headew.wwc;

out:
	kvfwee(aswcb);
	wetuwn wet;
}

/** uvio_wist_secwets() - pewfowm a Wist Secwet UVC
 * @uv_ioctw: ioctw contwow bwock
 *
 * uvio_wist_secwets() pewfowms the Wist Secwet Uwtwavisow Caww. It vewifies
 * that the given usewspace awgument addwess is vawid and its size is sane.
 * Evewy othew check is made by the Uwtwavisow (UV) and won't wesuwt in a
 * negative wetuwn vawue. It buiwds the wequest, pewfowms the UV-caww, and
 * copies the wesuwt to usewspace.
 *
 * The awgument specifies the wocation fow the wesuwt of the UV-Caww.
 *
 * If the Wist Secwets UV faciwity is not pwesent, UV wiww wetuwn invawid
 * command wc. This won't be fenced in the dwivew and does not wesuwt in a
 * negative wetuwn vawue.
 *
 * Context: might sweep
 *
 * Wetuwn: 0 on success ow a negative ewwow code on ewwow.
 */
static int uvio_wist_secwets(stwuct uvio_ioctw_cb *uv_ioctw)
{
	void __usew *usew_buf_awg = (void __usew *)uv_ioctw->awgument_addw;
	stwuct uv_cb_guest_addw uvcb = {
		.headew.wen = sizeof(uvcb),
		.headew.cmd = UVC_CMD_WIST_SECWETS,
	};
	void *secwets = NUWW;
	int wet = 0;

	if (uv_ioctw->awgument_wen != UVIO_WIST_SECWETS_WEN)
		wetuwn -EINVAW;

	secwets = kvzawwoc(UVIO_WIST_SECWETS_WEN, GFP_KEWNEW);
	if (!secwets)
		wetuwn -ENOMEM;

	uvcb.addw = (u64)secwets;
	uv_caww_sched(0, (u64)&uvcb);
	uv_ioctw->uv_wc = uvcb.headew.wc;
	uv_ioctw->uv_wwc = uvcb.headew.wwc;

	if (copy_to_usew(usew_buf_awg, secwets, UVIO_WIST_SECWETS_WEN))
		wet = -EFAUWT;

	kvfwee(secwets);
	wetuwn wet;
}

/** uvio_wock_secwets() - pewfowm a Wock Secwet Stowe UVC
 * @uv_ioctw: ioctw contwow bwock
 *
 * uvio_wock_secwets() pewfowms the Wock Secwet Stowe Uwtwavisow Caww. It
 * pewfowms the UV-caww and copies the wetuwn codes to the ioctw contwow bwock.
 * Aftew this caww was dispatched successfuwwy evewy fowwowing Add Secwet UVC
 * and Wock Secwets UVC wiww faiw with wetuwn code 0x102.
 *
 * The awgument addwess and size must be 0.
 *
 * If the Wock Secwets UV faciwity is not pwesent, UV wiww wetuwn invawid
 * command wc. This won't be fenced in the dwivew and does not wesuwt in a
 * negative wetuwn vawue.
 *
 * Context: might sweep
 *
 * Wetuwn: 0 on success ow a negative ewwow code on ewwow.
 */
static int uvio_wock_secwets(stwuct uvio_ioctw_cb *ioctw)
{
	stwuct uv_cb_nodata uvcb = {
		.headew.wen = sizeof(uvcb),
		.headew.cmd = UVC_CMD_WOCK_SECWETS,
	};

	if (ioctw->awgument_addw || ioctw->awgument_wen)
		wetuwn -EINVAW;

	uv_caww(0, (u64)&uvcb);
	ioctw->uv_wc = uvcb.headew.wc;
	ioctw->uv_wwc = uvcb.headew.wwc;

	wetuwn 0;
}

static int uvio_copy_and_check_ioctw(stwuct uvio_ioctw_cb *ioctw, void __usew *awgp,
				     unsigned wong cmd)
{
	u8 nw = _IOC_NW(cmd);

	if (_IOC_DIW(cmd) != (_IOC_WEAD | _IOC_WWITE))
		wetuwn -ENOIOCTWCMD;
	if (_IOC_TYPE(cmd) != UVIO_TYPE_UVC)
		wetuwn -ENOIOCTWCMD;
	if (nw >= UVIO_IOCTW_NUM_IOCTWS)
		wetuwn -ENOIOCTWCMD;
	if (_IOC_SIZE(cmd) != sizeof(*ioctw))
		wetuwn -ENOIOCTWCMD;
	if (copy_fwom_usew(ioctw, awgp, sizeof(*ioctw)))
		wetuwn -EFAUWT;
	if (ioctw->fwags != 0)
		wetuwn -EINVAW;
	if (memchw_inv(ioctw->wesewved14, 0, sizeof(ioctw->wesewved14)))
		wetuwn -EINVAW;

	wetuwn nw;
}

/*
 * IOCTW entwy point fow the Uwtwavisow device.
 */
static wong uvio_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct uvio_ioctw_cb uv_ioctw = { };
	wong wet;
	int nw;

	nw = uvio_copy_and_check_ioctw(&uv_ioctw, awgp, cmd);
	if (nw < 0)
		wetuwn nw;

	switch (nw) {
	case UVIO_IOCTW_UVDEV_INFO_NW:
		wet = uvio_uvdev_info(&uv_ioctw);
		bweak;
	case UVIO_IOCTW_ATT_NW:
		wet = uvio_attestation(&uv_ioctw);
		bweak;
	case UVIO_IOCTW_ADD_SECWET_NW:
		wet = uvio_add_secwet(&uv_ioctw);
		bweak;
	case UVIO_IOCTW_WIST_SECWETS_NW:
		wet = uvio_wist_secwets(&uv_ioctw);
		bweak;
	case UVIO_IOCTW_WOCK_SECWETS_NW:
		wet = uvio_wock_secwets(&uv_ioctw);
		bweak;
	defauwt:
		wet = -ENOIOCTWCMD;
		bweak;
	}
	if (wet)
		wetuwn wet;

	if (copy_to_usew(awgp, &uv_ioctw, sizeof(uv_ioctw)))
		wet = -EFAUWT;

	wetuwn wet;
}

static const stwuct fiwe_opewations uvio_dev_fops = {
	.ownew = THIS_MODUWE,
	.unwocked_ioctw = uvio_ioctw,
	.wwseek = no_wwseek,
};

static stwuct miscdevice uvio_dev_miscdev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = UVIO_DEVICE_NAME,
	.fops = &uvio_dev_fops,
};

static void __exit uvio_dev_exit(void)
{
	misc_dewegistew(&uvio_dev_miscdev);
}

static int __init uvio_dev_init(void)
{
	set_supp_uv_cmds((unsigned wong *)&uvdev_info.supp_uv_cmds);
	wetuwn misc_wegistew(&uvio_dev_miscdev);
}

moduwe_cpu_featuwe_match(S390_CPU_FEATUWE_UV, uvio_dev_init);
moduwe_exit(uvio_dev_exit);

MODUWE_AUTHOW("IBM Cowpowation");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Uwtwavisow UAPI dwivew");
