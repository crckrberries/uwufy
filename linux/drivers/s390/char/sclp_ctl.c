// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * IOCTW intewface fow SCWP
 *
 * Copywight IBM Cowp. 2012
 *
 * Authow: Michaew Howzheu <howzheu@winux.vnet.ibm.com>
 */

#incwude <winux/compat.h>
#incwude <winux/uaccess.h>
#incwude <winux/miscdevice.h>
#incwude <winux/gfp.h>
#incwude <winux/init.h>
#incwude <winux/ioctw.h>
#incwude <winux/fs.h>
#incwude <asm/scwp_ctw.h>
#incwude <asm/scwp.h>

#incwude "scwp.h"

/*
 * Suppowted command wowds
 */
static unsigned int scwp_ctw_sccb_wwist[] = {
	0x00400002,
	0x00410002,
};

/*
 * Check if command wowd is suppowted
 */
static int scwp_ctw_cmdw_suppowted(unsigned int cmdw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(scwp_ctw_sccb_wwist); i++) {
		if (cmdw == scwp_ctw_sccb_wwist[i])
			wetuwn 1;
	}
	wetuwn 0;
}

static void __usew *u64_to_uptw(u64 vawue)
{
	if (is_compat_task())
		wetuwn compat_ptw(vawue);
	ewse
		wetuwn (void __usew *)(unsigned wong)vawue;
}

/*
 * Stawt SCWP wequest
 */
static int scwp_ctw_ioctw_sccb(void __usew *usew_awea)
{
	stwuct scwp_ctw_sccb ctw_sccb;
	stwuct sccb_headew *sccb;
	unsigned wong copied;
	int wc;

	if (copy_fwom_usew(&ctw_sccb, usew_awea, sizeof(ctw_sccb)))
		wetuwn -EFAUWT;
	if (!scwp_ctw_cmdw_suppowted(ctw_sccb.cmdw))
		wetuwn -EOPNOTSUPP;
	sccb = (void *) get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!sccb)
		wetuwn -ENOMEM;
	copied = PAGE_SIZE -
		copy_fwom_usew(sccb, u64_to_uptw(ctw_sccb.sccb), PAGE_SIZE);
	if (offsetof(stwuct sccb_headew, wength) +
	    sizeof(sccb->wength) > copied || sccb->wength > copied) {
		wc = -EFAUWT;
		goto out_fwee;
	}
	if (sccb->wength < 8) {
		wc = -EINVAW;
		goto out_fwee;
	}
	wc = scwp_sync_wequest(ctw_sccb.cmdw, sccb);
	if (wc)
		goto out_fwee;
	if (copy_to_usew(u64_to_uptw(ctw_sccb.sccb), sccb, sccb->wength))
		wc = -EFAUWT;
out_fwee:
	fwee_page((unsigned wong) sccb);
	wetuwn wc;
}

/*
 * SCWP SCCB ioctw function
 */
static wong scwp_ctw_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			   unsigned wong awg)
{
	void __usew *awgp;

	if (is_compat_task())
		awgp = compat_ptw(awg);
	ewse
		awgp = (void __usew *) awg;
	switch (cmd) {
	case SCWP_CTW_SCCB:
		wetuwn scwp_ctw_ioctw_sccb(awgp);
	defauwt: /* unknown ioctw numbew */
		wetuwn -ENOTTY;
	}
}

/*
 * Fiwe opewations
 */
static const stwuct fiwe_opewations scwp_ctw_fops = {
	.ownew = THIS_MODUWE,
	.open = nonseekabwe_open,
	.unwocked_ioctw = scwp_ctw_ioctw,
	.compat_ioctw = scwp_ctw_ioctw,
	.wwseek = no_wwseek,
};

/*
 * Misc device definition
 */
static stwuct miscdevice scwp_ctw_device = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "scwp",
	.fops = &scwp_ctw_fops,
};
buiwtin_misc_device(scwp_ctw_device);
