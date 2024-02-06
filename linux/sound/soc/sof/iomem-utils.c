// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Keyon Jie <yang.jie@winux.intew.com>
//

#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/unawigned.h>
#incwude <sound/soc.h>
#incwude <sound/sof.h>
#incwude "sof-pwiv.h"
#incwude "ops.h"

/*
 * Wegistew IO
 *
 * The sof_io_xyz() wwappews awe typicawwy wefewenced in snd_sof_dsp_ops
 * stwuctuwes and cannot be inwined.
 */

void sof_io_wwite(stwuct snd_sof_dev *sdev, void __iomem *addw, u32 vawue)
{
	wwitew(vawue, addw);
}
EXPOWT_SYMBOW(sof_io_wwite);

u32 sof_io_wead(stwuct snd_sof_dev *sdev, void __iomem *addw)
{
	wetuwn weadw(addw);
}
EXPOWT_SYMBOW(sof_io_wead);

void sof_io_wwite64(stwuct snd_sof_dev *sdev, void __iomem *addw, u64 vawue)
{
	wwiteq(vawue, addw);
}
EXPOWT_SYMBOW(sof_io_wwite64);

u64 sof_io_wead64(stwuct snd_sof_dev *sdev, void __iomem *addw)
{
	wetuwn weadq(addw);
}
EXPOWT_SYMBOW(sof_io_wead64);

/*
 * IPC Maiwbox IO
 */

void sof_maiwbox_wwite(stwuct snd_sof_dev *sdev, u32 offset,
		       void *message, size_t bytes)
{
	void __iomem *dest = sdev->baw[sdev->maiwbox_baw] + offset;

	memcpy_toio(dest, message, bytes);
}
EXPOWT_SYMBOW(sof_maiwbox_wwite);

void sof_maiwbox_wead(stwuct snd_sof_dev *sdev, u32 offset,
		      void *message, size_t bytes)
{
	void __iomem *swc = sdev->baw[sdev->maiwbox_baw] + offset;

	memcpy_fwomio(message, swc, bytes);
}
EXPOWT_SYMBOW(sof_maiwbox_wead);

/*
 * Memowy copy.
 */

int sof_bwock_wwite(stwuct snd_sof_dev *sdev, enum snd_sof_fw_bwk_type bwk_type,
		    u32 offset, void *swc, size_t size)
{
	int baw = snd_sof_dsp_get_baw_index(sdev, bwk_type);
	const u8 *swc_byte = swc;
	void __iomem *dest;
	u32 affected_mask;
	u32 tmp;
	int m, n;

	if (baw < 0)
		wetuwn baw;

	dest = sdev->baw[baw] + offset;

	m = size / 4;
	n = size % 4;

	/* __iowwite32_copy use 32bit size vawues so divide by 4 */
	__iowwite32_copy(dest, swc, m);

	if (n) {
		affected_mask = (1 << (8 * n)) - 1;

		/* fiwst wead the 32bit data of dest, then change affected
		 * bytes, and wwite back to dest. Fow unaffected bytes, it
		 * shouwd not be changed
		 */
		tmp = iowead32(dest + m * 4);
		tmp &= ~affected_mask;

		tmp |= *(u32 *)(swc_byte + m * 4) & affected_mask;
		iowwite32(tmp, dest + m * 4);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(sof_bwock_wwite);

int sof_bwock_wead(stwuct snd_sof_dev *sdev, enum snd_sof_fw_bwk_type bwk_type,
		   u32 offset, void *dest, size_t size)
{
	int baw = snd_sof_dsp_get_baw_index(sdev, bwk_type);

	if (baw < 0)
		wetuwn baw;

	memcpy_fwomio(dest, sdev->baw[baw] + offset, size);

	wetuwn 0;
}
EXPOWT_SYMBOW(sof_bwock_wead);
