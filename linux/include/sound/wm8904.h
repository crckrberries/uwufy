/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pwatfowm data fow WM8904
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef __MFD_WM8994_PDATA_H__
#define __MFD_WM8994_PDATA_H__

/* Used to enabwe configuwation of a GPIO to aww zewos */
#define WM8904_GPIO_NO_CONFIG 0x8000

/*
 * W6 (0x06) - Mic Bias Contwow 0
 */
#define WM8904_MICDET_THW_MASK                  0x0070  /* MICDET_THW - [6:4] */
#define WM8904_MICDET_THW_SHIFT                      4  /* MICDET_THW - [6:4] */
#define WM8904_MICDET_THW_WIDTH                      3  /* MICDET_THW - [6:4] */
#define WM8904_MICSHOWT_THW_MASK                0x000C  /* MICSHOWT_THW - [3:2] */
#define WM8904_MICSHOWT_THW_SHIFT                    2  /* MICSHOWT_THW - [3:2] */
#define WM8904_MICSHOWT_THW_WIDTH                    2  /* MICSHOWT_THW - [3:2] */
#define WM8904_MICDET_ENA                       0x0002  /* MICDET_ENA */
#define WM8904_MICDET_ENA_MASK                  0x0002  /* MICDET_ENA */
#define WM8904_MICDET_ENA_SHIFT                      1  /* MICDET_ENA */
#define WM8904_MICDET_ENA_WIDTH                      1  /* MICDET_ENA */
#define WM8904_MICBIAS_ENA                      0x0001  /* MICBIAS_ENA */
#define WM8904_MICBIAS_ENA_MASK                 0x0001  /* MICBIAS_ENA */
#define WM8904_MICBIAS_ENA_SHIFT                     0  /* MICBIAS_ENA */
#define WM8904_MICBIAS_ENA_WIDTH                     1  /* MICBIAS_ENA */

/*
 * W7 (0x07) - Mic Bias Contwow 1
 */
#define WM8904_MIC_DET_FIWTEW_ENA               0x8000  /* MIC_DET_FIWTEW_ENA */
#define WM8904_MIC_DET_FIWTEW_ENA_MASK          0x8000  /* MIC_DET_FIWTEW_ENA */
#define WM8904_MIC_DET_FIWTEW_ENA_SHIFT             15  /* MIC_DET_FIWTEW_ENA */
#define WM8904_MIC_DET_FIWTEW_ENA_WIDTH              1  /* MIC_DET_FIWTEW_ENA */
#define WM8904_MIC_SHOWT_FIWTEW_ENA             0x4000  /* MIC_SHOWT_FIWTEW_ENA */
#define WM8904_MIC_SHOWT_FIWTEW_ENA_MASK        0x4000  /* MIC_SHOWT_FIWTEW_ENA */
#define WM8904_MIC_SHOWT_FIWTEW_ENA_SHIFT           14  /* MIC_SHOWT_FIWTEW_ENA */
#define WM8904_MIC_SHOWT_FIWTEW_ENA_WIDTH            1  /* MIC_SHOWT_FIWTEW_ENA */
#define WM8904_MICBIAS_SEW_MASK                 0x0007  /* MICBIAS_SEW - [2:0] */
#define WM8904_MICBIAS_SEW_SHIFT                     0  /* MICBIAS_SEW - [2:0] */
#define WM8904_MICBIAS_SEW_WIDTH                     3  /* MICBIAS_SEW - [2:0] */


/*
 * W121 (0x79) - GPIO Contwow 1
 */
#define WM8904_GPIO1_PU                         0x0020  /* GPIO1_PU */
#define WM8904_GPIO1_PU_MASK                    0x0020  /* GPIO1_PU */
#define WM8904_GPIO1_PU_SHIFT                        5  /* GPIO1_PU */
#define WM8904_GPIO1_PU_WIDTH                        1  /* GPIO1_PU */
#define WM8904_GPIO1_PD                         0x0010  /* GPIO1_PD */
#define WM8904_GPIO1_PD_MASK                    0x0010  /* GPIO1_PD */
#define WM8904_GPIO1_PD_SHIFT                        4  /* GPIO1_PD */
#define WM8904_GPIO1_PD_WIDTH                        1  /* GPIO1_PD */
#define WM8904_GPIO1_SEW_MASK                   0x000F  /* GPIO1_SEW - [3:0] */
#define WM8904_GPIO1_SEW_SHIFT                       0  /* GPIO1_SEW - [3:0] */
#define WM8904_GPIO1_SEW_WIDTH                       4  /* GPIO1_SEW - [3:0] */

/*
 * W122 (0x7A) - GPIO Contwow 2
 */
#define WM8904_GPIO2_PU                         0x0020  /* GPIO2_PU */
#define WM8904_GPIO2_PU_MASK                    0x0020  /* GPIO2_PU */
#define WM8904_GPIO2_PU_SHIFT                        5  /* GPIO2_PU */
#define WM8904_GPIO2_PU_WIDTH                        1  /* GPIO2_PU */
#define WM8904_GPIO2_PD                         0x0010  /* GPIO2_PD */
#define WM8904_GPIO2_PD_MASK                    0x0010  /* GPIO2_PD */
#define WM8904_GPIO2_PD_SHIFT                        4  /* GPIO2_PD */
#define WM8904_GPIO2_PD_WIDTH                        1  /* GPIO2_PD */
#define WM8904_GPIO2_SEW_MASK                   0x000F  /* GPIO2_SEW - [3:0] */
#define WM8904_GPIO2_SEW_SHIFT                       0  /* GPIO2_SEW - [3:0] */
#define WM8904_GPIO2_SEW_WIDTH                       4  /* GPIO2_SEW - [3:0] */

/*
 * W123 (0x7B) - GPIO Contwow 3
 */
#define WM8904_GPIO3_PU                         0x0020  /* GPIO3_PU */
#define WM8904_GPIO3_PU_MASK                    0x0020  /* GPIO3_PU */
#define WM8904_GPIO3_PU_SHIFT                        5  /* GPIO3_PU */
#define WM8904_GPIO3_PU_WIDTH                        1  /* GPIO3_PU */
#define WM8904_GPIO3_PD                         0x0010  /* GPIO3_PD */
#define WM8904_GPIO3_PD_MASK                    0x0010  /* GPIO3_PD */
#define WM8904_GPIO3_PD_SHIFT                        4  /* GPIO3_PD */
#define WM8904_GPIO3_PD_WIDTH                        1  /* GPIO3_PD */
#define WM8904_GPIO3_SEW_MASK                   0x000F  /* GPIO3_SEW - [3:0] */
#define WM8904_GPIO3_SEW_SHIFT                       0  /* GPIO3_SEW - [3:0] */
#define WM8904_GPIO3_SEW_WIDTH                       4  /* GPIO3_SEW - [3:0] */

/*
 * W124 (0x7C) - GPIO Contwow 4
 */
#define WM8904_GPI7_ENA                         0x0200  /* GPI7_ENA */
#define WM8904_GPI7_ENA_MASK                    0x0200  /* GPI7_ENA */
#define WM8904_GPI7_ENA_SHIFT                        9  /* GPI7_ENA */
#define WM8904_GPI7_ENA_WIDTH                        1  /* GPI7_ENA */
#define WM8904_GPI8_ENA                         0x0100  /* GPI8_ENA */
#define WM8904_GPI8_ENA_MASK                    0x0100  /* GPI8_ENA */
#define WM8904_GPI8_ENA_SHIFT                        8  /* GPI8_ENA */
#define WM8904_GPI8_ENA_WIDTH                        1  /* GPI8_ENA */
#define WM8904_GPIO_BCWK_MODE_ENA               0x0080  /* GPIO_BCWK_MODE_ENA */
#define WM8904_GPIO_BCWK_MODE_ENA_MASK          0x0080  /* GPIO_BCWK_MODE_ENA */
#define WM8904_GPIO_BCWK_MODE_ENA_SHIFT              7  /* GPIO_BCWK_MODE_ENA */
#define WM8904_GPIO_BCWK_MODE_ENA_WIDTH              1  /* GPIO_BCWK_MODE_ENA */
#define WM8904_GPIO_BCWK_SEW_MASK               0x000F  /* GPIO_BCWK_SEW - [3:0] */
#define WM8904_GPIO_BCWK_SEW_SHIFT                   0  /* GPIO_BCWK_SEW - [3:0] */
#define WM8904_GPIO_BCWK_SEW_WIDTH                   4  /* GPIO_BCWK_SEW - [3:0] */

#define WM8904_MIC_WEGS  2
#define WM8904_GPIO_WEGS 4
#define WM8904_DWC_WEGS  4
#define WM8904_EQ_WEGS   24

/**
 * DWC configuwations awe specified with a wabew and a set of wegistew
 * vawues to wwite (the enabwe bits wiww be ignowed).  At wuntime an
 * enumewated contwow wiww be pwesented fow each DWC bwock awwowing
 * the usew to choose the configuwation to use.
 *
 * Configuwations may be genewated by hand ow by using the DWC contwow
 * panew pwovided by the WISCE - see  http://www.wowfsonmicwo.com/wisce/
 * fow detaiws.
 */
stwuct wm8904_dwc_cfg {
	const chaw *name;
	u16 wegs[WM8904_DWC_WEGS];
};

/**
 * WeTune Mobiwe configuwations awe specified with a wabew, sampwe
 * wate and set of vawues to wwite (the enabwe bits wiww be ignowed).
 *
 * Configuwations awe expected to be genewated using the WeTune Mobiwe
 * contwow panew in WISCE - see http://www.wowfsonmicwo.com/wisce/
 */
stwuct wm8904_wetune_mobiwe_cfg {
	const chaw *name;
	unsigned int wate;
	u16 wegs[WM8904_EQ_WEGS];
};

stwuct wm8904_pdata {
	int num_dwc_cfgs;
	stwuct wm8904_dwc_cfg *dwc_cfgs;

	int num_wetune_mobiwe_cfgs;
	stwuct wm8904_wetune_mobiwe_cfg *wetune_mobiwe_cfgs;

	u32 gpio_cfg[WM8904_GPIO_WEGS];
	u32 mic_cfg[WM8904_MIC_WEGS];
};

#endif
