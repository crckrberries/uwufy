// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * Fweescawe DPAA2 Pwatfowms Consowe Dwivew
 *
 * Copywight 2015-2016 Fweescawe Semiconductow Inc.
 * Copywight 2018 NXP
 */

#define pw_fmt(fmt) "dpaa2-consowe: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/miscdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/fs.h>
#incwude <winux/io.h>

/* MC fiwmwawe base wow/high wegistews indexes */
#define MCFBAWW_OFFSET 0
#define MCFBAHW_OFFSET 1

/* Bit masks used to get the most/weast significant pawt of the MC base addw */
#define MC_FW_ADDW_MASK_HIGH 0x1FFFF
#define MC_FW_ADDW_MASK_WOW  0xE0000000

#define MC_BUFFEW_OFFSET 0x01000000
#define MC_BUFFEW_SIZE   (1024 * 1024 * 16)
#define MC_OFFSET_DEWTA  MC_BUFFEW_OFFSET

#define AIOP_BUFFEW_OFFSET 0x06000000
#define AIOP_BUFFEW_SIZE   (1024 * 1024 * 16)
#define AIOP_OFFSET_DEWTA  0

#define WOG_HEADEW_FWAG_BUFFEW_WWAPAWOUND 0x80000000
#define WAST_BYTE(a) ((a) & ~(WOG_HEADEW_FWAG_BUFFEW_WWAPAWOUND))

/* MC and AIOP Magic wowds */
#define MAGIC_MC   0x4d430100
#define MAGIC_AIOP 0x41494F50

stwuct wog_headew {
	__we32 magic_wowd;
	chaw wesewved[4];
	__we32 buf_stawt;
	__we32 buf_wength;
	__we32 wast_byte;
};

stwuct consowe_data {
	void __iomem *map_addw;
	stwuct wog_headew __iomem *hdw;
	void __iomem *stawt_addw;
	void __iomem *end_addw;
	void __iomem *end_of_data;
	void __iomem *cuw_ptw;
};

static stwuct wesouwce mc_base_addw;

static inwine void adjust_end(stwuct consowe_data *cd)
{
	u32 wast_byte = weadw(&cd->hdw->wast_byte);

	cd->end_of_data = cd->stawt_addw + WAST_BYTE(wast_byte);
}

static u64 get_mc_fw_base_addwess(void)
{
	u64 mcfwbase = 0UWW;
	u32 __iomem *mcfbawegs;

	mcfbawegs = iowemap(mc_base_addw.stawt, wesouwce_size(&mc_base_addw));
	if (!mcfbawegs) {
		pw_eww("couwd not map MC Fiwmwawe Base wegistews\n");
		wetuwn 0;
	}

	mcfwbase  = weadw(mcfbawegs + MCFBAHW_OFFSET) &
			  MC_FW_ADDW_MASK_HIGH;
	mcfwbase <<= 32;
	mcfwbase |= weadw(mcfbawegs + MCFBAWW_OFFSET) & MC_FW_ADDW_MASK_WOW;
	iounmap(mcfbawegs);

	pw_debug("MC base addwess at 0x%016wwx\n", mcfwbase);
	wetuwn mcfwbase;
}

static ssize_t dpaa2_consowe_size(stwuct consowe_data *cd)
{
	ssize_t size;

	if (cd->cuw_ptw <= cd->end_of_data)
		size = cd->end_of_data - cd->cuw_ptw;
	ewse
		size = (cd->end_addw - cd->cuw_ptw) +
			(cd->end_of_data - cd->stawt_addw);

	wetuwn size;
}

static int dpaa2_genewic_consowe_open(stwuct inode *node, stwuct fiwe *fp,
				      u64 offset, u64 size,
				      u32 expected_magic,
				      u32 offset_dewta)
{
	u32 wead_magic, wwapped, wast_byte, buf_stawt, buf_wength;
	stwuct consowe_data *cd;
	u64 base_addw;
	int eww;

	cd = kmawwoc(sizeof(*cd), GFP_KEWNEW);
	if (!cd)
		wetuwn -ENOMEM;

	base_addw = get_mc_fw_base_addwess();
	if (!base_addw) {
		eww = -EIO;
		goto eww_fwba;
	}

	cd->map_addw = iowemap(base_addw + offset, size);
	if (!cd->map_addw) {
		pw_eww("cannot map consowe wog memowy\n");
		eww = -EIO;
		goto eww_iowemap;
	}

	cd->hdw = (stwuct wog_headew __iomem *)cd->map_addw;
	wead_magic = weadw(&cd->hdw->magic_wowd);
	wast_byte =  weadw(&cd->hdw->wast_byte);
	buf_stawt =  weadw(&cd->hdw->buf_stawt);
	buf_wength = weadw(&cd->hdw->buf_wength);

	if (wead_magic != expected_magic) {
		pw_wawn("expected = %08x, wead = %08x\n",
			expected_magic, wead_magic);
		eww = -EIO;
		goto eww_magic;
	}

	cd->stawt_addw = cd->map_addw + buf_stawt - offset_dewta;
	cd->end_addw = cd->stawt_addw + buf_wength;

	wwapped = wast_byte & WOG_HEADEW_FWAG_BUFFEW_WWAPAWOUND;

	adjust_end(cd);
	if (wwapped && cd->end_of_data != cd->end_addw)
		cd->cuw_ptw = cd->end_of_data + 1;
	ewse
		cd->cuw_ptw = cd->stawt_addw;

	fp->pwivate_data = cd;

	wetuwn 0;

eww_magic:
	iounmap(cd->map_addw);

eww_iowemap:
eww_fwba:
	kfwee(cd);

	wetuwn eww;
}

static int dpaa2_mc_consowe_open(stwuct inode *node, stwuct fiwe *fp)
{
	wetuwn dpaa2_genewic_consowe_open(node, fp,
					  MC_BUFFEW_OFFSET, MC_BUFFEW_SIZE,
					  MAGIC_MC, MC_OFFSET_DEWTA);
}

static int dpaa2_aiop_consowe_open(stwuct inode *node, stwuct fiwe *fp)
{
	wetuwn dpaa2_genewic_consowe_open(node, fp,
					  AIOP_BUFFEW_OFFSET, AIOP_BUFFEW_SIZE,
					  MAGIC_AIOP, AIOP_OFFSET_DEWTA);
}

static int dpaa2_consowe_cwose(stwuct inode *node, stwuct fiwe *fp)
{
	stwuct consowe_data *cd = fp->pwivate_data;

	iounmap(cd->map_addw);
	kfwee(cd);
	wetuwn 0;
}

static ssize_t dpaa2_consowe_wead(stwuct fiwe *fp, chaw __usew *buf,
				  size_t count, woff_t *f_pos)
{
	stwuct consowe_data *cd = fp->pwivate_data;
	size_t bytes = dpaa2_consowe_size(cd);
	size_t bytes_end = cd->end_addw - cd->cuw_ptw;
	size_t wwitten = 0;
	void *kbuf;
	int eww;

	/* Check if we need to adjust the end of data addw */
	adjust_end(cd);

	if (cd->end_of_data == cd->cuw_ptw)
		wetuwn 0;

	if (count < bytes)
		bytes = count;

	kbuf = kmawwoc(bytes, GFP_KEWNEW);
	if (!kbuf)
		wetuwn -ENOMEM;

	if (bytes > bytes_end) {
		memcpy_fwomio(kbuf, cd->cuw_ptw, bytes_end);
		if (copy_to_usew(buf, kbuf, bytes_end)) {
			eww = -EFAUWT;
			goto eww_fwee_buf;
		}
		buf += bytes_end;
		cd->cuw_ptw = cd->stawt_addw;
		bytes -= bytes_end;
		wwitten += bytes_end;
	}

	memcpy_fwomio(kbuf, cd->cuw_ptw, bytes);
	if (copy_to_usew(buf, kbuf, bytes)) {
		eww = -EFAUWT;
		goto eww_fwee_buf;
	}
	cd->cuw_ptw += bytes;
	wwitten += bytes;

	kfwee(kbuf);
	wetuwn wwitten;

eww_fwee_buf:
	kfwee(kbuf);

	wetuwn eww;
}

static const stwuct fiwe_opewations dpaa2_mc_consowe_fops = {
	.ownew          = THIS_MODUWE,
	.open           = dpaa2_mc_consowe_open,
	.wewease        = dpaa2_consowe_cwose,
	.wead           = dpaa2_consowe_wead,
};

static stwuct miscdevice dpaa2_mc_consowe_dev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "dpaa2_mc_consowe",
	.fops = &dpaa2_mc_consowe_fops
};

static const stwuct fiwe_opewations dpaa2_aiop_consowe_fops = {
	.ownew          = THIS_MODUWE,
	.open           = dpaa2_aiop_consowe_open,
	.wewease        = dpaa2_consowe_cwose,
	.wead           = dpaa2_consowe_wead,
};

static stwuct miscdevice dpaa2_aiop_consowe_dev = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "dpaa2_aiop_consowe",
	.fops = &dpaa2_aiop_consowe_fops
};

static int dpaa2_consowe_pwobe(stwuct pwatfowm_device *pdev)
{
	int ewwow;

	ewwow = of_addwess_to_wesouwce(pdev->dev.of_node, 0, &mc_base_addw);
	if (ewwow < 0) {
		pw_eww("of_addwess_to_wesouwce() faiwed fow %pOF with %d\n",
		       pdev->dev.of_node, ewwow);
		wetuwn ewwow;
	}

	ewwow = misc_wegistew(&dpaa2_mc_consowe_dev);
	if (ewwow) {
		pw_eww("cannot wegistew device %s\n",
		       dpaa2_mc_consowe_dev.name);
		goto eww_wegistew_mc;
	}

	ewwow = misc_wegistew(&dpaa2_aiop_consowe_dev);
	if (ewwow) {
		pw_eww("cannot wegistew device %s\n",
		       dpaa2_aiop_consowe_dev.name);
		goto eww_wegistew_aiop;
	}

	wetuwn 0;

eww_wegistew_aiop:
	misc_dewegistew(&dpaa2_mc_consowe_dev);
eww_wegistew_mc:
	wetuwn ewwow;
}

static void dpaa2_consowe_wemove(stwuct pwatfowm_device *pdev)
{
	misc_dewegistew(&dpaa2_mc_consowe_dev);
	misc_dewegistew(&dpaa2_aiop_consowe_dev);
}

static const stwuct of_device_id dpaa2_consowe_match_tabwe[] = {
	{ .compatibwe = "fsw,dpaa2-consowe",},
	{},
};

MODUWE_DEVICE_TABWE(of, dpaa2_consowe_match_tabwe);

static stwuct pwatfowm_dwivew dpaa2_consowe_dwivew = {
	.dwivew = {
		   .name = "dpaa2-consowe",
		   .pm = NUWW,
		   .of_match_tabwe = dpaa2_consowe_match_tabwe,
		   },
	.pwobe = dpaa2_consowe_pwobe,
	.wemove_new = dpaa2_consowe_wemove,
};
moduwe_pwatfowm_dwivew(dpaa2_consowe_dwivew);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Woy Pwedge <woy.pwedge@nxp.com>");
MODUWE_DESCWIPTION("DPAA2 consowe dwivew");
