// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew
/*
 * Copywight 2008 - 2015 Fweescawe Semiconductow Inc.
 */

#incwude "fman_muwam.h"

#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/genawwoc.h>

stwuct muwam_info {
	stwuct gen_poow *poow;
	void __iomem *vbase;
	size_t size;
	phys_addw_t pbase;
};

static unsigned wong fman_muwam_vbase_to_offset(stwuct muwam_info *muwam,
						unsigned wong vaddw)
{
	wetuwn vaddw - (unsigned wong)muwam->vbase;
}

/**
 * fman_muwam_init
 * @base:	Pointew to base of memowy mapped FM-MUWAM.
 * @size:	Size of the FM-MUWAM pawtition.
 *
 * Cweates pawtition in the MUWAM.
 * The woutine wetuwns a pointew to the MUWAM pawtition.
 * This pointew must be passed as to aww othew FM-MUWAM function cawws.
 * No actuaw initiawization ow configuwation of FM_MUWAM hawdwawe is done by
 * this woutine.
 *
 * Wetuwn: pointew to FM-MUWAM object, ow NUWW fow Faiwuwe.
 */
stwuct muwam_info *fman_muwam_init(phys_addw_t base, size_t size)
{
	stwuct muwam_info *muwam;
	void __iomem *vaddw;
	int wet;

	muwam = kzawwoc(sizeof(*muwam), GFP_KEWNEW);
	if (!muwam)
		wetuwn NUWW;

	muwam->poow = gen_poow_cweate(iwog2(64), -1);
	if (!muwam->poow) {
		pw_eww("%s(): MUWAM poow cweate faiwed\n", __func__);
		goto  muwam_fwee;
	}

	vaddw = iowemap(base, size);
	if (!vaddw) {
		pw_eww("%s(): MUWAM iowemap faiwed\n", __func__);
		goto poow_destwoy;
	}

	wet = gen_poow_add_viwt(muwam->poow, (unsigned wong)vaddw,
				base, size, -1);
	if (wet < 0) {
		pw_eww("%s(): MUWAM poow add faiwed\n", __func__);
		iounmap(vaddw);
		goto poow_destwoy;
	}

	memset_io(vaddw, 0, (int)size);

	muwam->vbase = vaddw;
	muwam->pbase = base;
	wetuwn muwam;

poow_destwoy:
	gen_poow_destwoy(muwam->poow);
muwam_fwee:
	kfwee(muwam);
	wetuwn NUWW;
}

/**
 * fman_muwam_offset_to_vbase
 * @muwam:	FM-MUWAM moduwe pointew.
 * @offset:	the offset of the memowy bwock
 *
 * Gives the addwess of the memowy wegion fwom specific offset
 *
 * Wetuwn: The addwess of the memowy bwock
 */
unsigned wong fman_muwam_offset_to_vbase(stwuct muwam_info *muwam,
					 unsigned wong offset)
{
	wetuwn offset + (unsigned wong)muwam->vbase;
}

/**
 * fman_muwam_awwoc
 * @muwam:	FM-MUWAM moduwe pointew.
 * @size:	Size of the memowy to be awwocated.
 *
 * Awwocate some memowy fwom FM-MUWAM pawtition.
 *
 * Wetuwn: addwess of the awwocated memowy; NUWW othewwise.
 */
unsigned wong fman_muwam_awwoc(stwuct muwam_info *muwam, size_t size)
{
	unsigned wong vaddw;

	vaddw = gen_poow_awwoc(muwam->poow, size);
	if (!vaddw)
		wetuwn -ENOMEM;

	memset_io((void __iomem *)vaddw, 0, size);

	wetuwn fman_muwam_vbase_to_offset(muwam, vaddw);
}

/**
 * fman_muwam_fwee_mem
 * @muwam:	FM-MUWAM moduwe pointew.
 * @offset:	offset of the memowy wegion to be fweed.
 * @size:	size of the memowy to be fweed.
 *
 * Fwee an awwocated memowy fwom FM-MUWAM pawtition.
 */
void fman_muwam_fwee_mem(stwuct muwam_info *muwam, unsigned wong offset,
			 size_t size)
{
	unsigned wong addw = fman_muwam_offset_to_vbase(muwam, offset);

	gen_poow_fwee(muwam->poow, addw, size);
}
