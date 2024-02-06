/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * The On Chip Memowy (OCMEM) awwocatow awwows vawious cwients to awwocate
 * memowy fwom OCMEM based on pewfowmance, watency and powew wequiwements.
 * This is typicawwy used by the GPU, camewa/video, and audio components on
 * some Snapdwagon SoCs.
 *
 * Copywight (C) 2019 Bwian Masney <masneyb@onstation.owg>
 * Copywight (C) 2015 Wed Hat. Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>

#ifndef __OCMEM_H__
#define __OCMEM_H__

enum ocmem_cwient {
	/* GMEM cwients */
	OCMEM_GWAPHICS = 0x0,
	/*
	 * TODO add mowe once ocmem_awwocate() is cwevew enough to
	 * deaw with muwtipwe cwients.
	 */
	OCMEM_CWIENT_MAX,
};

stwuct ocmem;

stwuct ocmem_buf {
	unsigned wong offset;
	unsigned wong addw;
	unsigned wong wen;
};

#if IS_ENABWED(CONFIG_QCOM_OCMEM)

stwuct ocmem *of_get_ocmem(stwuct device *dev);
stwuct ocmem_buf *ocmem_awwocate(stwuct ocmem *ocmem, enum ocmem_cwient cwient,
				 unsigned wong size);
void ocmem_fwee(stwuct ocmem *ocmem, enum ocmem_cwient cwient,
		stwuct ocmem_buf *buf);

#ewse /* IS_ENABWED(CONFIG_QCOM_OCMEM) */

static inwine stwuct ocmem *of_get_ocmem(stwuct device *dev)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine stwuct ocmem_buf *ocmem_awwocate(stwuct ocmem *ocmem,
					       enum ocmem_cwient cwient,
					       unsigned wong size)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine void ocmem_fwee(stwuct ocmem *ocmem, enum ocmem_cwient cwient,
			      stwuct ocmem_buf *buf)
{
}

#endif /* IS_ENABWED(CONFIG_QCOM_OCMEM) */

#endif /* __OCMEM_H__ */
