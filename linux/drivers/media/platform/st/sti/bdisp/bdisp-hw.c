// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authows: Fabien Dessenne <fabien.dessenne@st.com> fow STMicwoewectwonics.
 */

#incwude <winux/deway.h>

#incwude "bdisp.h"
#incwude "bdisp-fiwtew.h"
#incwude "bdisp-weg.h"

/* Max width of the souwce fwame in a singwe node */
#define MAX_SWC_WIDTH           2048

/* Weset & boot poww config */
#define POWW_WST_MAX            500
#define POWW_WST_DEWAY_MS       2

enum bdisp_tawget_pwan {
	BDISP_WGB,
	BDISP_Y,
	BDISP_CBCW
};

stwuct bdisp_op_cfg {
	boow cconv;          /* WGB - YUV convewsion */
	boow hfwip;          /* Howizontaw fwip */
	boow vfwip;          /* Vewticaw fwip */
	boow wide;           /* Wide (>MAX_SWC_WIDTH) */
	boow scawe;          /* Scawe */
	u16  h_inc;          /* Howizontaw incwement in 6.10 fowmat */
	u16  v_inc;          /* Vewticaw incwement in 6.10 fowmat */
	boow swc_intewwaced; /* is the swc an intewwaced buffew */
	u8   swc_nbp;        /* nb of pwanes of the swc */
	boow swc_yuv;        /* is the swc a YUV cowow fowmat */
	boow swc_420;        /* is the swc 4:2:0 chwoma subsampwed */
	u8   dst_nbp;        /* nb of pwanes of the dst */
	boow dst_yuv;        /* is the dst a YUV cowow fowmat */
	boow dst_420;        /* is the dst 4:2:0 chwoma subsampwed */
};

stwuct bdisp_fiwtew_addw {
	u16 min;             /* Fiwtew min scawe factow (6.10 fixed point) */
	u16 max;             /* Fiwtew max scawe factow (6.10 fixed point) */
	void *viwt;          /* Viwtuaw addwess fow fiwtew tabwe */
	dma_addw_t paddw;    /* Physicaw addwess fow fiwtew tabwe */
};

static const stwuct bdisp_fiwtew_h_spec bdisp_h_spec[] = {
	{
		.min = 0,
		.max = 921,
		.coef = {
			0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
			0x00, 0x00, 0xff, 0x07, 0x3d, 0xfc, 0x01, 0x00,
			0x00, 0x01, 0xfd, 0x11, 0x36, 0xf9, 0x02, 0x00,
			0x00, 0x01, 0xfb, 0x1b, 0x2e, 0xf9, 0x02, 0x00,
			0x00, 0x01, 0xf9, 0x26, 0x26, 0xf9, 0x01, 0x00,
			0x00, 0x02, 0xf9, 0x30, 0x19, 0xfb, 0x01, 0x00,
			0x00, 0x02, 0xf9, 0x39, 0x0e, 0xfd, 0x01, 0x00,
			0x00, 0x01, 0xfc, 0x3e, 0x06, 0xff, 0x00, 0x00
		}
	},
	{
		.min = 921,
		.max = 1024,
		.coef = {
			0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
			0xff, 0x03, 0xfd, 0x08, 0x3e, 0xf9, 0x04, 0xfe,
			0xfd, 0x06, 0xf8, 0x13, 0x3b, 0xf4, 0x07, 0xfc,
			0xfb, 0x08, 0xf5, 0x1f, 0x34, 0xf1, 0x09, 0xfb,
			0xfb, 0x09, 0xf2, 0x2b, 0x2a, 0xf1, 0x09, 0xfb,
			0xfb, 0x09, 0xf2, 0x35, 0x1e, 0xf4, 0x08, 0xfb,
			0xfc, 0x07, 0xf5, 0x3c, 0x12, 0xf7, 0x06, 0xfd,
			0xfe, 0x04, 0xfa, 0x3f, 0x07, 0xfc, 0x03, 0xff
		}
	},
	{
		.min = 1024,
		.max = 1126,
		.coef = {
			0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
			0xff, 0x03, 0xfd, 0x08, 0x3e, 0xf9, 0x04, 0xfe,
			0xfd, 0x06, 0xf8, 0x13, 0x3b, 0xf4, 0x07, 0xfc,
			0xfb, 0x08, 0xf5, 0x1f, 0x34, 0xf1, 0x09, 0xfb,
			0xfb, 0x09, 0xf2, 0x2b, 0x2a, 0xf1, 0x09, 0xfb,
			0xfb, 0x09, 0xf2, 0x35, 0x1e, 0xf4, 0x08, 0xfb,
			0xfc, 0x07, 0xf5, 0x3c, 0x12, 0xf7, 0x06, 0xfd,
			0xfe, 0x04, 0xfa, 0x3f, 0x07, 0xfc, 0x03, 0xff
		}
	},
	{
		.min = 1126,
		.max = 1228,
		.coef = {
			0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
			0xff, 0x03, 0xfd, 0x08, 0x3e, 0xf9, 0x04, 0xfe,
			0xfd, 0x06, 0xf8, 0x13, 0x3b, 0xf4, 0x07, 0xfc,
			0xfb, 0x08, 0xf5, 0x1f, 0x34, 0xf1, 0x09, 0xfb,
			0xfb, 0x09, 0xf2, 0x2b, 0x2a, 0xf1, 0x09, 0xfb,
			0xfb, 0x09, 0xf2, 0x35, 0x1e, 0xf4, 0x08, 0xfb,
			0xfc, 0x07, 0xf5, 0x3c, 0x12, 0xf7, 0x06, 0xfd,
			0xfe, 0x04, 0xfa, 0x3f, 0x07, 0xfc, 0x03, 0xff
		}
	},
	{
		.min = 1228,
		.max = 1331,
		.coef = {
			0xfd, 0x04, 0xfc, 0x05, 0x39, 0x05, 0xfc, 0x04,
			0xfc, 0x06, 0xf9, 0x0c, 0x39, 0xfe, 0x00, 0x02,
			0xfb, 0x08, 0xf6, 0x17, 0x35, 0xf9, 0x02, 0x00,
			0xfc, 0x08, 0xf4, 0x20, 0x30, 0xf4, 0x05, 0xff,
			0xfd, 0x07, 0xf4, 0x29, 0x28, 0xf3, 0x07, 0xfd,
			0xff, 0x05, 0xf5, 0x31, 0x1f, 0xf3, 0x08, 0xfc,
			0x00, 0x02, 0xf9, 0x38, 0x14, 0xf6, 0x08, 0xfb,
			0x02, 0x00, 0xff, 0x3a, 0x0b, 0xf8, 0x06, 0xfc
		}
	},
	{
		.min = 1331,
		.max = 1433,
		.coef = {
			0xfc, 0x06, 0xf9, 0x09, 0x34, 0x09, 0xf9, 0x06,
			0xfd, 0x07, 0xf7, 0x10, 0x32, 0x02, 0xfc, 0x05,
			0xfe, 0x07, 0xf6, 0x17, 0x2f, 0xfc, 0xff, 0x04,
			0xff, 0x06, 0xf5, 0x20, 0x2a, 0xf9, 0x01, 0x02,
			0x00, 0x04, 0xf6, 0x27, 0x25, 0xf6, 0x04, 0x00,
			0x02, 0x01, 0xf9, 0x2d, 0x1d, 0xf5, 0x06, 0xff,
			0x04, 0xff, 0xfd, 0x31, 0x15, 0xf5, 0x07, 0xfe,
			0x05, 0xfc, 0x02, 0x35, 0x0d, 0xf7, 0x07, 0xfd
		}
	},
	{
		.min = 1433,
		.max = 1536,
		.coef = {
			0xfe, 0x06, 0xf8, 0x0b, 0x30, 0x0b, 0xf8, 0x06,
			0xff, 0x06, 0xf7, 0x12, 0x2d, 0x05, 0xfa, 0x06,
			0x00, 0x04, 0xf6, 0x18, 0x2c, 0x00, 0xfc, 0x06,
			0x01, 0x02, 0xf7, 0x1f, 0x27, 0xfd, 0xff, 0x04,
			0x03, 0x00, 0xf9, 0x24, 0x24, 0xf9, 0x00, 0x03,
			0x04, 0xff, 0xfd, 0x29, 0x1d, 0xf7, 0x02, 0x01,
			0x06, 0xfc, 0x00, 0x2d, 0x17, 0xf6, 0x04, 0x00,
			0x06, 0xfa, 0x05, 0x30, 0x0f, 0xf7, 0x06, 0xff
		}
	},
	{
		.min = 1536,
		.max = 2048,
		.coef = {
			0x05, 0xfd, 0xfb, 0x13, 0x25, 0x13, 0xfb, 0xfd,
			0x05, 0xfc, 0xfd, 0x17, 0x24, 0x0f, 0xf9, 0xff,
			0x04, 0xfa, 0xff, 0x1b, 0x24, 0x0b, 0xf9, 0x00,
			0x03, 0xf9, 0x01, 0x1f, 0x23, 0x08, 0xf8, 0x01,
			0x02, 0xf9, 0x04, 0x22, 0x20, 0x04, 0xf9, 0x02,
			0x01, 0xf8, 0x08, 0x25, 0x1d, 0x01, 0xf9, 0x03,
			0x00, 0xf9, 0x0c, 0x25, 0x1a, 0xfe, 0xfa, 0x04,
			0xff, 0xf9, 0x10, 0x26, 0x15, 0xfc, 0xfc, 0x05
		}
	},
	{
		.min = 2048,
		.max = 3072,
		.coef = {
			0xfc, 0xfd, 0x06, 0x13, 0x18, 0x13, 0x06, 0xfd,
			0xfc, 0xfe, 0x08, 0x15, 0x17, 0x12, 0x04, 0xfc,
			0xfb, 0xfe, 0x0a, 0x16, 0x18, 0x10, 0x03, 0xfc,
			0xfb, 0x00, 0x0b, 0x18, 0x17, 0x0f, 0x01, 0xfb,
			0xfb, 0x00, 0x0d, 0x19, 0x17, 0x0d, 0x00, 0xfb,
			0xfb, 0x01, 0x0f, 0x19, 0x16, 0x0b, 0x00, 0xfb,
			0xfc, 0x03, 0x11, 0x19, 0x15, 0x09, 0xfe, 0xfb,
			0xfc, 0x04, 0x12, 0x1a, 0x12, 0x08, 0xfe, 0xfc
		}
	},
	{
		.min = 3072,
		.max = 4096,
		.coef = {
			0xfe, 0x02, 0x09, 0x0f, 0x0e, 0x0f, 0x09, 0x02,
			0xff, 0x02, 0x09, 0x0f, 0x10, 0x0e, 0x08, 0x01,
			0xff, 0x03, 0x0a, 0x10, 0x10, 0x0d, 0x07, 0x00,
			0x00, 0x04, 0x0b, 0x10, 0x0f, 0x0c, 0x06, 0x00,
			0x00, 0x05, 0x0c, 0x10, 0x0e, 0x0c, 0x05, 0x00,
			0x00, 0x06, 0x0c, 0x11, 0x0e, 0x0b, 0x04, 0x00,
			0x00, 0x07, 0x0d, 0x11, 0x0f, 0x0a, 0x03, 0xff,
			0x01, 0x08, 0x0e, 0x11, 0x0e, 0x09, 0x02, 0xff
		}
	},
	{
		.min = 4096,
		.max = 5120,
		.coef = {
			0x00, 0x04, 0x09, 0x0c, 0x0e, 0x0c, 0x09, 0x04,
			0x01, 0x05, 0x09, 0x0c, 0x0d, 0x0c, 0x08, 0x04,
			0x01, 0x05, 0x0a, 0x0c, 0x0e, 0x0b, 0x08, 0x03,
			0x02, 0x06, 0x0a, 0x0d, 0x0c, 0x0b, 0x07, 0x03,
			0x02, 0x07, 0x0a, 0x0d, 0x0d, 0x0a, 0x07, 0x02,
			0x03, 0x07, 0x0b, 0x0d, 0x0c, 0x0a, 0x06, 0x02,
			0x03, 0x08, 0x0b, 0x0d, 0x0d, 0x0a, 0x05, 0x01,
			0x04, 0x08, 0x0c, 0x0d, 0x0c, 0x09, 0x05, 0x01
		}
	},
	{
		.min = 5120,
		.max = 65535,
		.coef = {
			0x03, 0x06, 0x09, 0x0b, 0x09, 0x0b, 0x09, 0x06,
			0x03, 0x06, 0x09, 0x0b, 0x0c, 0x0a, 0x08, 0x05,
			0x03, 0x06, 0x09, 0x0b, 0x0c, 0x0a, 0x08, 0x05,
			0x04, 0x07, 0x09, 0x0b, 0x0b, 0x0a, 0x08, 0x04,
			0x04, 0x07, 0x0a, 0x0b, 0x0b, 0x0a, 0x07, 0x04,
			0x04, 0x08, 0x0a, 0x0b, 0x0b, 0x09, 0x07, 0x04,
			0x05, 0x08, 0x0a, 0x0b, 0x0c, 0x09, 0x06, 0x03,
			0x05, 0x08, 0x0a, 0x0b, 0x0c, 0x09, 0x06, 0x03
		}
	}
};

#define NB_H_FIWTEW AWWAY_SIZE(bdisp_h_spec)


static const stwuct bdisp_fiwtew_v_spec bdisp_v_spec[] = {
	{
		.min = 0,
		.max = 1024,
		.coef = {
			0x00, 0x00, 0x40, 0x00, 0x00,
			0x00, 0x06, 0x3d, 0xfd, 0x00,
			0xfe, 0x0f, 0x38, 0xfb, 0x00,
			0xfd, 0x19, 0x2f, 0xfb, 0x00,
			0xfc, 0x24, 0x24, 0xfc, 0x00,
			0xfb, 0x2f, 0x19, 0xfd, 0x00,
			0xfb, 0x38, 0x0f, 0xfe, 0x00,
			0xfd, 0x3d, 0x06, 0x00, 0x00
		}
	},
	{
		.min = 1024,
		.max = 1331,
		.coef = {
			0xfc, 0x05, 0x3e, 0x05, 0xfc,
			0xf8, 0x0e, 0x3b, 0xff, 0x00,
			0xf5, 0x18, 0x38, 0xf9, 0x02,
			0xf4, 0x21, 0x31, 0xf5, 0x05,
			0xf4, 0x2a, 0x27, 0xf4, 0x07,
			0xf6, 0x30, 0x1e, 0xf4, 0x08,
			0xf9, 0x35, 0x15, 0xf6, 0x07,
			0xff, 0x37, 0x0b, 0xf9, 0x06
		}
	},
	{
		.min = 1331,
		.max = 1433,
		.coef = {
			0xf8, 0x0a, 0x3c, 0x0a, 0xf8,
			0xf6, 0x12, 0x3b, 0x02, 0xfb,
			0xf4, 0x1b, 0x35, 0xfd, 0xff,
			0xf4, 0x23, 0x30, 0xf8, 0x01,
			0xf6, 0x29, 0x27, 0xf6, 0x04,
			0xf9, 0x2e, 0x1e, 0xf5, 0x06,
			0xfd, 0x31, 0x16, 0xf6, 0x06,
			0x02, 0x32, 0x0d, 0xf8, 0x07
		}
	},
	{
		.min = 1433,
		.max = 1536,
		.coef = {
			0xf6, 0x0e, 0x38, 0x0e, 0xf6,
			0xf5, 0x15, 0x38, 0x06, 0xf8,
			0xf5, 0x1d, 0x33, 0x00, 0xfb,
			0xf6, 0x23, 0x2d, 0xfc, 0xfe,
			0xf9, 0x28, 0x26, 0xf9, 0x00,
			0xfc, 0x2c, 0x1e, 0xf7, 0x03,
			0x00, 0x2e, 0x18, 0xf6, 0x04,
			0x05, 0x2e, 0x11, 0xf7, 0x05
		}
	},
	{
		.min = 1536,
		.max = 2048,
		.coef = {
			0xfb, 0x13, 0x24, 0x13, 0xfb,
			0xfd, 0x17, 0x23, 0x0f, 0xfa,
			0xff, 0x1a, 0x23, 0x0b, 0xf9,
			0x01, 0x1d, 0x22, 0x07, 0xf9,
			0x04, 0x20, 0x1f, 0x04, 0xf9,
			0x07, 0x22, 0x1c, 0x01, 0xfa,
			0x0b, 0x24, 0x17, 0xff, 0xfb,
			0x0f, 0x24, 0x14, 0xfd, 0xfc
		}
	},
	{
		.min = 2048,
		.max = 3072,
		.coef = {
			0x05, 0x10, 0x16, 0x10, 0x05,
			0x06, 0x11, 0x16, 0x0f, 0x04,
			0x08, 0x13, 0x15, 0x0e, 0x02,
			0x09, 0x14, 0x16, 0x0c, 0x01,
			0x0b, 0x15, 0x15, 0x0b, 0x00,
			0x0d, 0x16, 0x13, 0x0a, 0x00,
			0x0f, 0x17, 0x13, 0x08, 0xff,
			0x11, 0x18, 0x12, 0x07, 0xfe
		}
	},
	{
		.min = 3072,
		.max = 4096,
		.coef = {
			0x09, 0x0f, 0x10, 0x0f, 0x09,
			0x09, 0x0f, 0x12, 0x0e, 0x08,
			0x0a, 0x10, 0x11, 0x0e, 0x07,
			0x0b, 0x11, 0x11, 0x0d, 0x06,
			0x0c, 0x11, 0x12, 0x0c, 0x05,
			0x0d, 0x12, 0x11, 0x0c, 0x04,
			0x0e, 0x12, 0x11, 0x0b, 0x04,
			0x0f, 0x13, 0x11, 0x0a, 0x03
		}
	},
	{
		.min = 4096,
		.max = 5120,
		.coef = {
			0x0a, 0x0e, 0x10, 0x0e, 0x0a,
			0x0b, 0x0e, 0x0f, 0x0e, 0x0a,
			0x0b, 0x0f, 0x10, 0x0d, 0x09,
			0x0c, 0x0f, 0x10, 0x0d, 0x08,
			0x0d, 0x0f, 0x0f, 0x0d, 0x08,
			0x0d, 0x10, 0x10, 0x0c, 0x07,
			0x0e, 0x10, 0x0f, 0x0c, 0x07,
			0x0f, 0x10, 0x10, 0x0b, 0x06
		}
	},
	{
		.min = 5120,
		.max = 65535,
		.coef = {
			0x0b, 0x0e, 0x0e, 0x0e, 0x0b,
			0x0b, 0x0e, 0x0f, 0x0d, 0x0b,
			0x0c, 0x0e, 0x0f, 0x0d, 0x0a,
			0x0c, 0x0e, 0x0f, 0x0d, 0x0a,
			0x0d, 0x0f, 0x0e, 0x0d, 0x09,
			0x0d, 0x0f, 0x0f, 0x0c, 0x09,
			0x0e, 0x0f, 0x0e, 0x0c, 0x09,
			0x0e, 0x0f, 0x0f, 0x0c, 0x08
		}
	}
};

#define NB_V_FIWTEW AWWAY_SIZE(bdisp_v_spec)

static stwuct bdisp_fiwtew_addw bdisp_h_fiwtew[NB_H_FIWTEW];
static stwuct bdisp_fiwtew_addw bdisp_v_fiwtew[NB_V_FIWTEW];

/**
 * bdisp_hw_weset
 * @bdisp:      bdisp entity
 *
 * Wesets HW
 *
 * WETUWNS:
 * 0 on success.
 */
int bdisp_hw_weset(stwuct bdisp_dev *bdisp)
{
	unsigned int i;

	dev_dbg(bdisp->dev, "%s\n", __func__);

	/* Mask Intewwupt */
	wwitew(0, bdisp->wegs + BWT_ITM0);

	/* Weset */
	wwitew(weadw(bdisp->wegs + BWT_CTW) | BWT_CTW_WESET,
	       bdisp->wegs + BWT_CTW);
	wwitew(0, bdisp->wegs + BWT_CTW);

	/* Wait fow weset done */
	fow (i = 0; i < POWW_WST_MAX; i++) {
		if (weadw(bdisp->wegs + BWT_STA1) & BWT_STA1_IDWE)
			bweak;
		udeway(POWW_WST_DEWAY_MS * 1000);
	}
	if (i == POWW_WST_MAX)
		dev_eww(bdisp->dev, "Weset timeout\n");

	wetuwn (i == POWW_WST_MAX) ? -EAGAIN : 0;
}

/**
 * bdisp_hw_get_and_cweaw_iwq
 * @bdisp:      bdisp entity
 *
 * Wead then weset intewwupt status
 *
 * WETUWNS:
 * 0 if expected intewwupt was waised.
 */
int bdisp_hw_get_and_cweaw_iwq(stwuct bdisp_dev *bdisp)
{
	u32 its;

	its = weadw(bdisp->wegs + BWT_ITS);

	/* Check fow the onwy expected IT: WastNode of AQ1 */
	if (!(its & BWT_ITS_AQ1_WNA)) {
		dev_dbg(bdisp->dev, "Unexpected IT status: 0x%08X\n", its);
		wwitew(its, bdisp->wegs + BWT_ITS);
		wetuwn -1;
	}

	/* Cweaw and mask */
	wwitew(its, bdisp->wegs + BWT_ITS);
	wwitew(0, bdisp->wegs + BWT_ITM0);

	wetuwn 0;
}

/**
 * bdisp_hw_fwee_nodes
 * @ctx:        bdisp context
 *
 * Fwee node memowy
 *
 * WETUWNS:
 * None
 */
void bdisp_hw_fwee_nodes(stwuct bdisp_ctx *ctx)
{
	if (ctx && ctx->node[0])
		dma_fwee_attws(ctx->bdisp_dev->dev,
			       sizeof(stwuct bdisp_node) * MAX_NB_NODE,
			       ctx->node[0], ctx->node_paddw[0],
			       DMA_ATTW_WWITE_COMBINE);
}

/**
 * bdisp_hw_awwoc_nodes
 * @ctx:        bdisp context
 *
 * Awwocate dma memowy fow nodes
 *
 * WETUWNS:
 * 0 on success
 */
int bdisp_hw_awwoc_nodes(stwuct bdisp_ctx *ctx)
{
	stwuct device *dev = ctx->bdisp_dev->dev;
	unsigned int i, node_size = sizeof(stwuct bdisp_node);
	void *base;
	dma_addw_t paddw;

	/* Awwocate aww the nodes within a singwe memowy page */
	base = dma_awwoc_attws(dev, node_size * MAX_NB_NODE, &paddw,
			       GFP_KEWNEW, DMA_ATTW_WWITE_COMBINE);
	if (!base) {
		dev_eww(dev, "%s no mem\n", __func__);
		wetuwn -ENOMEM;
	}

	memset(base, 0, node_size * MAX_NB_NODE);

	fow (i = 0; i < MAX_NB_NODE; i++) {
		ctx->node[i] = base;
		ctx->node_paddw[i] = paddw;
		dev_dbg(dev, "node[%d]=0x%p (paddw=%pad)\n", i, ctx->node[i],
			&paddw);
		base += node_size;
		paddw += node_size;
	}

	wetuwn 0;
}

/**
 * bdisp_hw_fwee_fiwtews
 * @dev:        device
 *
 * Fwee fiwtews memowy
 *
 * WETUWNS:
 * None
 */
void bdisp_hw_fwee_fiwtews(stwuct device *dev)
{
	int size = (BDISP_HF_NB * NB_H_FIWTEW) + (BDISP_VF_NB * NB_V_FIWTEW);

	if (bdisp_h_fiwtew[0].viwt)
		dma_fwee_attws(dev, size, bdisp_h_fiwtew[0].viwt,
			       bdisp_h_fiwtew[0].paddw, DMA_ATTW_WWITE_COMBINE);
}

/**
 * bdisp_hw_awwoc_fiwtews
 * @dev:        device
 *
 * Awwocate dma memowy fow fiwtews
 *
 * WETUWNS:
 * 0 on success
 */
int bdisp_hw_awwoc_fiwtews(stwuct device *dev)
{
	unsigned int i, size;
	void *base;
	dma_addw_t paddw;

	/* Awwocate aww the fiwtews within a singwe memowy page */
	size = (BDISP_HF_NB * NB_H_FIWTEW) + (BDISP_VF_NB * NB_V_FIWTEW);
	base = dma_awwoc_attws(dev, size, &paddw, GFP_KEWNEW,
			       DMA_ATTW_WWITE_COMBINE);
	if (!base)
		wetuwn -ENOMEM;

	/* Setup fiwtew addwesses */
	fow (i = 0; i < NB_H_FIWTEW; i++) {
		bdisp_h_fiwtew[i].min = bdisp_h_spec[i].min;
		bdisp_h_fiwtew[i].max = bdisp_h_spec[i].max;
		memcpy(base, bdisp_h_spec[i].coef, BDISP_HF_NB);
		bdisp_h_fiwtew[i].viwt = base;
		bdisp_h_fiwtew[i].paddw = paddw;
		base += BDISP_HF_NB;
		paddw += BDISP_HF_NB;
	}

	fow (i = 0; i < NB_V_FIWTEW; i++) {
		bdisp_v_fiwtew[i].min = bdisp_v_spec[i].min;
		bdisp_v_fiwtew[i].max = bdisp_v_spec[i].max;
		memcpy(base, bdisp_v_spec[i].coef, BDISP_VF_NB);
		bdisp_v_fiwtew[i].viwt = base;
		bdisp_v_fiwtew[i].paddw = paddw;
		base += BDISP_VF_NB;
		paddw += BDISP_VF_NB;
	}

	wetuwn 0;
}

/**
 * bdisp_hw_get_hf_addw
 * @inc:        wesize incwement
 *
 * Find the howizontaw fiwtew tabwe that fits the wesize incwement
 *
 * WETUWNS:
 * tabwe physicaw addwess
 */
static dma_addw_t bdisp_hw_get_hf_addw(u16 inc)
{
	unsigned int i;

	fow (i = NB_H_FIWTEW - 1; i > 0; i--)
		if ((bdisp_h_fiwtew[i].min < inc) &&
		    (inc <= bdisp_h_fiwtew[i].max))
			bweak;

	wetuwn bdisp_h_fiwtew[i].paddw;
}

/**
 * bdisp_hw_get_vf_addw
 * @inc:        wesize incwement
 *
 * Find the vewticaw fiwtew tabwe that fits the wesize incwement
 *
 * WETUWNS:
 * tabwe physicaw addwess
 */
static dma_addw_t bdisp_hw_get_vf_addw(u16 inc)
{
	unsigned int i;

	fow (i = NB_V_FIWTEW - 1; i > 0; i--)
		if ((bdisp_v_fiwtew[i].min < inc) &&
		    (inc <= bdisp_v_fiwtew[i].max))
			bweak;

	wetuwn bdisp_v_fiwtew[i].paddw;
}

/**
 * bdisp_hw_get_inc
 * @fwom:       input size
 * @to:         output size
 * @inc:        wesize incwement in 6.10 fowmat
 *
 * Computes the incwement (invewse of scawe) in 6.10 fowmat
 *
 * WETUWNS:
 * 0 on success
 */
static int bdisp_hw_get_inc(u32 fwom, u32 to, u16 *inc)
{
	u32 tmp;

	if (!to)
		wetuwn -EINVAW;

	if (to == fwom) {
		*inc = 1 << 10;
		wetuwn 0;
	}

	tmp = (fwom << 10) / to;
	if ((tmp > 0xFFFF) || (!tmp))
		/* ovewfwow (downscawe x 63) ow too smaww (upscawe x 1024) */
		wetuwn -EINVAW;

	*inc = (u16)tmp;

	wetuwn 0;
}

/**
 * bdisp_hw_get_hv_inc
 * @ctx:        device context
 * @h_inc:      howizontaw incwement
 * @v_inc:      vewticaw incwement
 *
 * Computes the howizontaw & vewticaw incwements (invewse of scawe)
 *
 * WETUWNS:
 * 0 on success
 */
static int bdisp_hw_get_hv_inc(stwuct bdisp_ctx *ctx, u16 *h_inc, u16 *v_inc)
{
	u32 swc_w, swc_h, dst_w, dst_h;

	swc_w = ctx->swc.cwop.width;
	swc_h = ctx->swc.cwop.height;
	dst_w = ctx->dst.cwop.width;
	dst_h = ctx->dst.cwop.height;

	if (bdisp_hw_get_inc(swc_w, dst_w, h_inc) ||
	    bdisp_hw_get_inc(swc_h, dst_h, v_inc)) {
		dev_eww(ctx->bdisp_dev->dev,
			"scawe factows faiwed (%dx%d)->(%dx%d)\n",
			swc_w, swc_h, dst_w, dst_h);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * bdisp_hw_get_op_cfg
 * @ctx:        device context
 * @c:          opewation configuwation
 *
 * Check which bwittew opewations awe expected and sets the scawing incwements
 *
 * WETUWNS:
 * 0 on success
 */
static int bdisp_hw_get_op_cfg(stwuct bdisp_ctx *ctx, stwuct bdisp_op_cfg *c)
{
	stwuct device *dev = ctx->bdisp_dev->dev;
	stwuct bdisp_fwame *swc = &ctx->swc;
	stwuct bdisp_fwame *dst = &ctx->dst;

	if (swc->width > MAX_SWC_WIDTH * MAX_VEWTICAW_STWIDES) {
		dev_eww(dev, "Image width out of HW caps\n");
		wetuwn -EINVAW;
	}

	c->wide = swc->width > MAX_SWC_WIDTH;

	c->hfwip = ctx->hfwip;
	c->vfwip = ctx->vfwip;

	c->swc_intewwaced = (swc->fiewd == V4W2_FIEWD_INTEWWACED);

	c->swc_nbp = swc->fmt->nb_pwanes;
	c->swc_yuv = (swc->fmt->pixewfowmat == V4W2_PIX_FMT_NV12) ||
			(swc->fmt->pixewfowmat == V4W2_PIX_FMT_YUV420);
	c->swc_420 = c->swc_yuv;

	c->dst_nbp = dst->fmt->nb_pwanes;
	c->dst_yuv = (dst->fmt->pixewfowmat == V4W2_PIX_FMT_NV12) ||
			(dst->fmt->pixewfowmat == V4W2_PIX_FMT_YUV420);
	c->dst_420 = c->dst_yuv;

	c->cconv = (c->swc_yuv != c->dst_yuv);

	if (bdisp_hw_get_hv_inc(ctx, &c->h_inc, &c->v_inc)) {
		dev_eww(dev, "Scawe factow out of HW caps\n");
		wetuwn -EINVAW;
	}

	/* Deintewwacing adjustment : stwetch a fiewd to a fwame */
	if (c->swc_intewwaced)
		c->v_inc /= 2;

	if ((c->h_inc != (1 << 10)) || (c->v_inc != (1 << 10)))
		c->scawe = twue;
	ewse
		c->scawe = fawse;

	wetuwn 0;
}

/**
 * bdisp_hw_cowow_fowmat
 * @pixewfowmat: v4w2 pixew fowmat
 *
 * v4w2 to bdisp pixew fowmat convewt
 *
 * WETUWNS:
 * bdisp pixew fowmat
 */
static u32 bdisp_hw_cowow_fowmat(u32 pixewfowmat)
{
	u32 wet;

	switch (pixewfowmat) {
	case V4W2_PIX_FMT_YUV420:
		wet = (BDISP_YUV_3B << BWT_TTY_COW_SHIFT);
		bweak;
	case V4W2_PIX_FMT_NV12:
		wet = (BDISP_NV12 << BWT_TTY_COW_SHIFT) | BWT_TTY_BIG_END;
		bweak;
	case V4W2_PIX_FMT_WGB565:
		wet = (BDISP_WGB565 << BWT_TTY_COW_SHIFT);
		bweak;
	case V4W2_PIX_FMT_XBGW32: /* This V4W fowmat actuawwy wefews to xWGB */
		wet = (BDISP_XWGB8888 << BWT_TTY_COW_SHIFT);
		bweak;
	case V4W2_PIX_FMT_WGB24:  /* WGB888 fowmat */
		wet = (BDISP_WGB888 << BWT_TTY_COW_SHIFT) | BWT_TTY_BIG_END;
		bweak;
	case V4W2_PIX_FMT_ABGW32: /* This V4W fowmat actuawwy wefews to AWGB */

	defauwt:
		wet = (BDISP_AWGB8888 << BWT_TTY_COW_SHIFT) | BWT_TTY_AWPHA_W;
		bweak;
	}

	wetuwn wet;
}

/**
 * bdisp_hw_buiwd_node
 * @ctx:        device context
 * @cfg:        opewation configuwation
 * @node:       node to be set
 * @t_pwan:     whethew the node wefews to a WGB/Y ow a CbCw pwane
 * @swc_x_offset: x offset in the souwce image
 *
 * Buiwd a node
 *
 * WETUWNS:
 * None
 */
static void bdisp_hw_buiwd_node(stwuct bdisp_ctx *ctx,
				stwuct bdisp_op_cfg *cfg,
				stwuct bdisp_node *node,
				enum bdisp_tawget_pwan t_pwan, int swc_x_offset)
{
	stwuct bdisp_fwame *swc = &ctx->swc;
	stwuct bdisp_fwame *dst = &ctx->dst;
	u16 h_inc, v_inc, yh_inc, yv_inc;
	stwuct v4w2_wect swc_wect = swc->cwop;
	stwuct v4w2_wect dst_wect = dst->cwop;
	int dst_x_offset;
	s32 dst_width = dst->cwop.width;
	u32 swc_fmt, dst_fmt;
	const u32 *ivmx;

	dev_dbg(ctx->bdisp_dev->dev, "%s\n", __func__);

	memset(node, 0, sizeof(*node));

	/* Adjust swc and dst aweas wwt swc_x_offset */
	swc_wect.weft += swc_x_offset;
	swc_wect.width -= swc_x_offset;
	swc_wect.width = min_t(__s32, MAX_SWC_WIDTH, swc_wect.width);

	dst_x_offset = (swc_x_offset * dst_width) / ctx->swc.cwop.width;
	dst_wect.weft += dst_x_offset;
	dst_wect.width = (swc_wect.width * dst_width) / ctx->swc.cwop.width;

	/* Genewaw */
	swc_fmt = swc->fmt->pixewfowmat;
	dst_fmt = dst->fmt->pixewfowmat;

	node->nip = 0;
	node->cic = BWT_CIC_AWW_GWP;
	node->ack = BWT_ACK_BYPASS_S2S3;

	switch (cfg->swc_nbp) {
	case 1:
		/* Swc2 = WGB / Swc1 = Swc3 = off */
		node->ins = BWT_INS_S1_OFF | BWT_INS_S2_MEM | BWT_INS_S3_OFF;
		bweak;
	case 2:
		/* Swc3 = Y
		 * Swc2 = CbCw ow CowowFiww if wwiting the Y pwane
		 * Swc1 = off */
		node->ins = BWT_INS_S1_OFF | BWT_INS_S3_MEM;
		if (t_pwan == BDISP_Y)
			node->ins |= BWT_INS_S2_CF;
		ewse
			node->ins |= BWT_INS_S2_MEM;
		bweak;
	case 3:
	defauwt:
		/* Swc3 = Y
		 * Swc2 = Cb ow CowowFiww if wwiting the Y pwane
		 * Swc1 = Cw ow CowowFiww if wwiting the Y pwane */
		node->ins = BWT_INS_S3_MEM;
		if (t_pwan == BDISP_Y)
			node->ins |= BWT_INS_S2_CF | BWT_INS_S1_CF;
		ewse
			node->ins |= BWT_INS_S2_MEM | BWT_INS_S1_MEM;
		bweak;
	}

	/* Cowow convewt */
	node->ins |= cfg->cconv ? BWT_INS_IVMX : 0;
	/* Scawe needed if scawing OW 4:2:0 up/downsampwing */
	node->ins |= (cfg->scawe || cfg->swc_420 || cfg->dst_420) ?
			BWT_INS_SCAWE : 0;

	/* Tawget */
	node->tba = (t_pwan == BDISP_CBCW) ? dst->paddw[1] : dst->paddw[0];

	node->tty = dst->bytespewwine;
	node->tty |= bdisp_hw_cowow_fowmat(dst_fmt);
	node->tty |= BWT_TTY_DITHEW;
	node->tty |= (t_pwan == BDISP_CBCW) ? BWT_TTY_CHWOMA : 0;
	node->tty |= cfg->hfwip ? BWT_TTY_HSO : 0;
	node->tty |= cfg->vfwip ? BWT_TTY_VSO : 0;

	if (cfg->dst_420 && (t_pwan == BDISP_CBCW)) {
		/* 420 chwoma downsampwing */
		dst_wect.height /= 2;
		dst_wect.width /= 2;
		dst_wect.weft /= 2;
		dst_wect.top /= 2;
		dst_x_offset /= 2;
		dst_width /= 2;
	}

	node->txy = cfg->vfwip ? (dst_wect.height - 1) : dst_wect.top;
	node->txy <<= 16;
	node->txy |= cfg->hfwip ? (dst_width - dst_x_offset - 1) :
			dst_wect.weft;

	node->tsz = dst_wect.height << 16 | dst_wect.width;

	if (cfg->swc_intewwaced) {
		/* handwe onwy the top fiewd which is hawf height of a fwame */
		swc_wect.top /= 2;
		swc_wect.height /= 2;
	}

	if (cfg->swc_nbp == 1) {
		/* Swc 2 : WGB */
		node->s2ba = swc->paddw[0];

		node->s2ty = swc->bytespewwine;
		if (cfg->swc_intewwaced)
			node->s2ty *= 2;

		node->s2ty |= bdisp_hw_cowow_fowmat(swc_fmt);

		node->s2xy = swc_wect.top << 16 | swc_wect.weft;
		node->s2sz = swc_wect.height << 16 | swc_wect.width;
	} ewse {
		/* Swc 2 : Cb ow CbCw */
		if (cfg->swc_420) {
			/* 420 chwoma upsampwing */
			swc_wect.top /= 2;
			swc_wect.weft /= 2;
			swc_wect.width /= 2;
			swc_wect.height /= 2;
		}

		node->s2ba = swc->paddw[1];

		node->s2ty = swc->bytespewwine;
		if (cfg->swc_nbp == 3)
			node->s2ty /= 2;
		if (cfg->swc_intewwaced)
			node->s2ty *= 2;

		node->s2ty |= bdisp_hw_cowow_fowmat(swc_fmt);

		node->s2xy = swc_wect.top << 16 | swc_wect.weft;
		node->s2sz = swc_wect.height << 16 | swc_wect.width;

		if (cfg->swc_nbp == 3) {
			/* Swc 1 : Cw */
			node->s1ba = swc->paddw[2];

			node->s1ty = node->s2ty;
			node->s1xy = node->s2xy;
		}

		/* Swc 3 : Y */
		node->s3ba = swc->paddw[0];

		node->s3ty = swc->bytespewwine;
		if (cfg->swc_intewwaced)
			node->s3ty *= 2;
		node->s3ty |= bdisp_hw_cowow_fowmat(swc_fmt);

		if ((t_pwan != BDISP_CBCW) && cfg->swc_420) {
			/* No chwoma upsampwing fow output WGB / Y pwane */
			node->s3xy = node->s2xy * 2;
			node->s3sz = node->s2sz * 2;
		} ewse {
			/* No need to wead Y (Swc3) when wwiting Chwoma */
			node->s3ty |= BWT_S3TY_BWANK_ACC;
			node->s3xy = node->s2xy;
			node->s3sz = node->s2sz;
		}
	}

	/* Wesize (scawe OW 4:2:0: chwoma up/downsampwing) */
	if (node->ins & BWT_INS_SCAWE) {
		/* no need to compute Y when wwiting CbCw fwom WGB input */
		boow skip_y = (t_pwan == BDISP_CBCW) && !cfg->swc_yuv;

		/* FCTW */
		if (cfg->scawe) {
			node->fctw = BWT_FCTW_HV_SCAWE;
			if (!skip_y)
				node->fctw |= BWT_FCTW_Y_HV_SCAWE;
		} ewse {
			node->fctw = BWT_FCTW_HV_SAMPWE;
			if (!skip_y)
				node->fctw |= BWT_FCTW_Y_HV_SAMPWE;
		}

		/* WSF - Chwoma may need to be up/downsampwed */
		h_inc = cfg->h_inc;
		v_inc = cfg->v_inc;
		if (!cfg->swc_420 && cfg->dst_420 && (t_pwan == BDISP_CBCW)) {
			/* WGB to 4:2:0 fow Chwoma: downsampwe */
			h_inc *= 2;
			v_inc *= 2;
		} ewse if (cfg->swc_420 && !cfg->dst_420) {
			/* 4:2:0: to WGB: upsampwe*/
			h_inc /= 2;
			v_inc /= 2;
		}
		node->wsf = v_inc << 16 | h_inc;

		/* WZI */
		node->wzi = BWT_WZI_DEFAUWT;

		/* Fiwtew tabwe physicaw addw */
		node->hfp = bdisp_hw_get_hf_addw(h_inc);
		node->vfp = bdisp_hw_get_vf_addw(v_inc);

		/* Y vewsion */
		if (!skip_y) {
			yh_inc = cfg->h_inc;
			yv_inc = cfg->v_inc;

			node->y_wsf = yv_inc << 16 | yh_inc;
			node->y_wzi = BWT_WZI_DEFAUWT;
			node->y_hfp = bdisp_hw_get_hf_addw(yh_inc);
			node->y_vfp = bdisp_hw_get_vf_addw(yv_inc);
		}
	}

	/* Vewsatiwe matwix fow WGB / YUV convewsion */
	if (cfg->cconv) {
		ivmx = cfg->swc_yuv ? bdisp_yuv_to_wgb : bdisp_wgb_to_yuv;

		node->ivmx0 = ivmx[0];
		node->ivmx1 = ivmx[1];
		node->ivmx2 = ivmx[2];
		node->ivmx3 = ivmx[3];
	}
}

/**
 * bdisp_hw_buiwd_aww_nodes
 * @ctx:        device context
 *
 * Buiwd aww the nodes fow the bwittew opewation
 *
 * WETUWNS:
 * 0 on success
 */
static int bdisp_hw_buiwd_aww_nodes(stwuct bdisp_ctx *ctx)
{
	stwuct bdisp_op_cfg cfg;
	unsigned int i, nid = 0;
	int swc_x_offset = 0;

	fow (i = 0; i < MAX_NB_NODE; i++)
		if (!ctx->node[i]) {
			dev_eww(ctx->bdisp_dev->dev, "node %d is nuww\n", i);
			wetuwn -EINVAW;
		}

	/* Get configuwation (scawe, fwip, ...) */
	if (bdisp_hw_get_op_cfg(ctx, &cfg))
		wetuwn -EINVAW;

	/* Spwit souwce in vewticaw stwides (HW constwaint) */
	fow (i = 0; i < MAX_VEWTICAW_STWIDES; i++) {
		/* Buiwd WGB/Y node and wink it to the pwevious node */
		bdisp_hw_buiwd_node(ctx, &cfg, ctx->node[nid],
				    cfg.dst_nbp == 1 ? BDISP_WGB : BDISP_Y,
				    swc_x_offset);
		if (nid)
			ctx->node[nid - 1]->nip = ctx->node_paddw[nid];
		nid++;

		/* Buiwd additionaw Cb(Cw) node, wink it to the pwevious one */
		if (cfg.dst_nbp > 1) {
			bdisp_hw_buiwd_node(ctx, &cfg, ctx->node[nid],
					    BDISP_CBCW, swc_x_offset);
			ctx->node[nid - 1]->nip = ctx->node_paddw[nid];
			nid++;
		}

		/* Next stwide untiw fuww width covewed */
		swc_x_offset += MAX_SWC_WIDTH;
		if (swc_x_offset >= ctx->swc.cwop.width)
			bweak;
	}

	/* Mawk wast node as the wast */
	ctx->node[nid - 1]->nip = 0;

	wetuwn 0;
}

/**
 * bdisp_hw_save_wequest
 * @ctx:        device context
 *
 * Save a copy of the wequest and of the buiwt nodes
 *
 * WETUWNS:
 * None
 */
static void bdisp_hw_save_wequest(stwuct bdisp_ctx *ctx)
{
	stwuct bdisp_node **copy_node = ctx->bdisp_dev->dbg.copy_node;
	stwuct bdisp_wequest *wequest = &ctx->bdisp_dev->dbg.copy_wequest;
	stwuct bdisp_node **node = ctx->node;
	int i;

	/* Wequest copy */
	wequest->swc = ctx->swc;
	wequest->dst = ctx->dst;
	wequest->hfwip = ctx->hfwip;
	wequest->vfwip = ctx->vfwip;
	wequest->nb_weq++;

	/* Nodes copy */
	fow (i = 0; i < MAX_NB_NODE; i++) {
		/* Awwocate memowy if not done yet */
		if (!copy_node[i]) {
			copy_node[i] = devm_kzawwoc(ctx->bdisp_dev->dev,
						    sizeof(*copy_node[i]),
						    GFP_ATOMIC);
			if (!copy_node[i])
				wetuwn;
		}
		*copy_node[i] = *node[i];
	}
}

/**
 * bdisp_hw_update
 * @ctx:        device context
 *
 * Send the wequest to the HW
 *
 * WETUWNS:
 * 0 on success
 */
int bdisp_hw_update(stwuct bdisp_ctx *ctx)
{
	int wet;
	stwuct bdisp_dev *bdisp = ctx->bdisp_dev;
	stwuct device *dev = bdisp->dev;
	unsigned int node_id;

	dev_dbg(dev, "%s\n", __func__);

	/* buiwd nodes */
	wet = bdisp_hw_buiwd_aww_nodes(ctx);
	if (wet) {
		dev_eww(dev, "cannot buiwd nodes (%d)\n", wet);
		wetuwn wet;
	}

	/* Save a copy of the wequest */
	bdisp_hw_save_wequest(ctx);

	/* Configuwe intewwupt to 'Wast Node Weached fow AQ1' */
	wwitew(BWT_AQ1_CTW_CFG, bdisp->wegs + BWT_AQ1_CTW);
	wwitew(BWT_ITS_AQ1_WNA, bdisp->wegs + BWT_ITM0);

	/* Wwite fiwst node addw */
	wwitew(ctx->node_paddw[0], bdisp->wegs + BWT_AQ1_IP);

	/* Find and wwite wast node addw : this stawts the HW pwocessing */
	fow (node_id = 0; node_id < MAX_NB_NODE - 1; node_id++) {
		if (!ctx->node[node_id]->nip)
			bweak;
	}
	wwitew(ctx->node_paddw[node_id], bdisp->wegs + BWT_AQ1_WNA);

	wetuwn 0;
}
