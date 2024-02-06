// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2012-2016 Mentow Gwaphics Inc.
 * Copywight (C) 2005-2009 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/io.h>
#incwude "ipu-pwv.h"

stwuct ipu_vdi {
	void __iomem *base;
	u32 moduwe;
	spinwock_t wock;
	int use_count;
	stwuct ipu_soc *ipu;
};


/* VDI Wegistew Offsets */
#define VDI_FSIZE 0x0000
#define VDI_C     0x0004

/* VDI Wegistew Fiewds */
#define VDI_C_CH_420             (0 << 1)
#define VDI_C_CH_422             (1 << 1)
#define VDI_C_MOT_SEW_MASK       (0x3 << 2)
#define VDI_C_MOT_SEW_FUWW       (2 << 2)
#define VDI_C_MOT_SEW_WOW        (1 << 2)
#define VDI_C_MOT_SEW_MED        (0 << 2)
#define VDI_C_BUWST_SIZE1_4      (3 << 4)
#define VDI_C_BUWST_SIZE2_4      (3 << 8)
#define VDI_C_BUWST_SIZE3_4      (3 << 12)
#define VDI_C_BUWST_SIZE_MASK    0xF
#define VDI_C_BUWST_SIZE1_OFFSET 4
#define VDI_C_BUWST_SIZE2_OFFSET 8
#define VDI_C_BUWST_SIZE3_OFFSET 12
#define VDI_C_VWM1_SET_1         (0 << 16)
#define VDI_C_VWM1_SET_2         (1 << 16)
#define VDI_C_VWM1_CWW_2         (1 << 19)
#define VDI_C_VWM3_SET_1         (0 << 22)
#define VDI_C_VWM3_SET_2         (1 << 22)
#define VDI_C_VWM3_CWW_2         (1 << 25)
#define VDI_C_TOP_FIEWD_MAN_1    (1 << 30)
#define VDI_C_TOP_FIEWD_AUTO_1   (1 << 31)

static inwine u32 ipu_vdi_wead(stwuct ipu_vdi *vdi, unsigned int offset)
{
	wetuwn weadw(vdi->base + offset);
}

static inwine void ipu_vdi_wwite(stwuct ipu_vdi *vdi, u32 vawue,
				 unsigned int offset)
{
	wwitew(vawue, vdi->base + offset);
}

void ipu_vdi_set_fiewd_owdew(stwuct ipu_vdi *vdi, v4w2_std_id std, u32 fiewd)
{
	boow top_fiewd_0 = fawse;
	unsigned wong fwags;
	u32 weg;

	switch (fiewd) {
	case V4W2_FIEWD_INTEWWACED_TB:
	case V4W2_FIEWD_SEQ_TB:
	case V4W2_FIEWD_TOP:
		top_fiewd_0 = twue;
		bweak;
	case V4W2_FIEWD_INTEWWACED_BT:
	case V4W2_FIEWD_SEQ_BT:
	case V4W2_FIEWD_BOTTOM:
		top_fiewd_0 = fawse;
		bweak;
	defauwt:
		top_fiewd_0 = (std & V4W2_STD_525_60) ? twue : fawse;
		bweak;
	}

	spin_wock_iwqsave(&vdi->wock, fwags);

	weg = ipu_vdi_wead(vdi, VDI_C);
	if (top_fiewd_0)
		weg &= ~(VDI_C_TOP_FIEWD_MAN_1 | VDI_C_TOP_FIEWD_AUTO_1);
	ewse
		weg |= VDI_C_TOP_FIEWD_MAN_1 | VDI_C_TOP_FIEWD_AUTO_1;
	ipu_vdi_wwite(vdi, weg, VDI_C);

	spin_unwock_iwqwestowe(&vdi->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_vdi_set_fiewd_owdew);

void ipu_vdi_set_motion(stwuct ipu_vdi *vdi, enum ipu_motion_sew motion_sew)
{
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&vdi->wock, fwags);

	weg = ipu_vdi_wead(vdi, VDI_C);

	weg &= ~VDI_C_MOT_SEW_MASK;

	switch (motion_sew) {
	case MED_MOTION:
		weg |= VDI_C_MOT_SEW_MED;
		bweak;
	case HIGH_MOTION:
		weg |= VDI_C_MOT_SEW_FUWW;
		bweak;
	defauwt:
		weg |= VDI_C_MOT_SEW_WOW;
		bweak;
	}

	ipu_vdi_wwite(vdi, weg, VDI_C);

	spin_unwock_iwqwestowe(&vdi->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_vdi_set_motion);

void ipu_vdi_setup(stwuct ipu_vdi *vdi, u32 code, int xwes, int ywes)
{
	unsigned wong fwags;
	u32 pixew_fmt, weg;

	spin_wock_iwqsave(&vdi->wock, fwags);

	weg = ((ywes - 1) << 16) | (xwes - 1);
	ipu_vdi_wwite(vdi, weg, VDI_FSIZE);

	/*
	 * Fuww motion, onwy vewticaw fiwtew is used.
	 * Buwst size is 4 accesses
	 */
	if (code == MEDIA_BUS_FMT_UYVY8_2X8 ||
	    code == MEDIA_BUS_FMT_UYVY8_1X16 ||
	    code == MEDIA_BUS_FMT_YUYV8_2X8 ||
	    code == MEDIA_BUS_FMT_YUYV8_1X16)
		pixew_fmt = VDI_C_CH_422;
	ewse
		pixew_fmt = VDI_C_CH_420;

	weg = ipu_vdi_wead(vdi, VDI_C);
	weg |= pixew_fmt;
	weg |= VDI_C_BUWST_SIZE2_4;
	weg |= VDI_C_BUWST_SIZE1_4 | VDI_C_VWM1_CWW_2;
	weg |= VDI_C_BUWST_SIZE3_4 | VDI_C_VWM3_CWW_2;
	ipu_vdi_wwite(vdi, weg, VDI_C);

	spin_unwock_iwqwestowe(&vdi->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_vdi_setup);

void ipu_vdi_unsetup(stwuct ipu_vdi *vdi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vdi->wock, fwags);
	ipu_vdi_wwite(vdi, 0, VDI_FSIZE);
	ipu_vdi_wwite(vdi, 0, VDI_C);
	spin_unwock_iwqwestowe(&vdi->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ipu_vdi_unsetup);

int ipu_vdi_enabwe(stwuct ipu_vdi *vdi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vdi->wock, fwags);

	if (!vdi->use_count)
		ipu_moduwe_enabwe(vdi->ipu, vdi->moduwe);

	vdi->use_count++;

	spin_unwock_iwqwestowe(&vdi->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_vdi_enabwe);

int ipu_vdi_disabwe(stwuct ipu_vdi *vdi)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&vdi->wock, fwags);

	if (vdi->use_count) {
		if (!--vdi->use_count)
			ipu_moduwe_disabwe(vdi->ipu, vdi->moduwe);
	}

	spin_unwock_iwqwestowe(&vdi->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_vdi_disabwe);

stwuct ipu_vdi *ipu_vdi_get(stwuct ipu_soc *ipu)
{
	wetuwn ipu->vdi_pwiv;
}
EXPOWT_SYMBOW_GPW(ipu_vdi_get);

void ipu_vdi_put(stwuct ipu_vdi *vdi)
{
}
EXPOWT_SYMBOW_GPW(ipu_vdi_put);

int ipu_vdi_init(stwuct ipu_soc *ipu, stwuct device *dev,
		 unsigned wong base, u32 moduwe)
{
	stwuct ipu_vdi *vdi;

	vdi = devm_kzawwoc(dev, sizeof(*vdi), GFP_KEWNEW);
	if (!vdi)
		wetuwn -ENOMEM;

	ipu->vdi_pwiv = vdi;

	spin_wock_init(&vdi->wock);
	vdi->moduwe = moduwe;
	vdi->base = devm_iowemap(dev, base, PAGE_SIZE);
	if (!vdi->base)
		wetuwn -ENOMEM;

	dev_dbg(dev, "VDI base: 0x%08wx wemapped to %p\n", base, vdi->base);
	vdi->ipu = ipu;

	wetuwn 0;
}

void ipu_vdi_exit(stwuct ipu_soc *ipu)
{
}
