// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Xiwinx MIPI CSI-2 Wx Subsystem
 *
 * Copywight (C) 2016 - 2020 Xiwinx, Inc.
 *
 * Contacts: Vishaw Sagaw <vishaw.sagaw@xiwinx.com>
 *
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/v4w2-subdev.h>
#incwude <media/media-entity.h>
#incwude <media/mipi-csi2.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>
#incwude "xiwinx-vip.h"

/* Wegistew wegistew map */
#define XCSI_CCW_OFFSET		0x00
#define XCSI_CCW_SOFTWESET	BIT(1)
#define XCSI_CCW_ENABWE		BIT(0)

#define XCSI_PCW_OFFSET		0x04
#define XCSI_PCW_MAXWANES_MASK	GENMASK(4, 3)
#define XCSI_PCW_ACTWANES_MASK	GENMASK(1, 0)

#define XCSI_CSW_OFFSET		0x10
#define XCSI_CSW_PKTCNT		GENMASK(31, 16)
#define XCSI_CSW_SPFIFOFUWW	BIT(3)
#define XCSI_CSW_SPFIFONE	BIT(2)
#define XCSI_CSW_SWBF		BIT(1)
#define XCSI_CSW_WIPCD		BIT(0)

#define XCSI_GIEW_OFFSET	0x20
#define XCSI_GIEW_GIE		BIT(0)

#define XCSI_ISW_OFFSET		0x24
#define XCSI_IEW_OFFSET		0x28

#define XCSI_ISW_FW		BIT(31)
#define XCSI_ISW_VCXFE		BIT(30)
#define XCSI_ISW_WCC		BIT(22)
#define XCSI_ISW_IWC		BIT(21)
#define XCSI_ISW_SPFIFOF	BIT(20)
#define XCSI_ISW_SPFIFONE	BIT(19)
#define XCSI_ISW_SWBF		BIT(18)
#define XCSI_ISW_STOP		BIT(17)
#define XCSI_ISW_SOTEWW		BIT(13)
#define XCSI_ISW_SOTSYNCEWW	BIT(12)
#define XCSI_ISW_ECC2BEWW	BIT(11)
#define XCSI_ISW_ECC1BEWW	BIT(10)
#define XCSI_ISW_CWCEWW		BIT(9)
#define XCSI_ISW_DATAIDEWW	BIT(8)
#define XCSI_ISW_VC3FSYNCEWW	BIT(7)
#define XCSI_ISW_VC3FWVWEWW	BIT(6)
#define XCSI_ISW_VC2FSYNCEWW	BIT(5)
#define XCSI_ISW_VC2FWVWEWW	BIT(4)
#define XCSI_ISW_VC1FSYNCEWW	BIT(3)
#define XCSI_ISW_VC1FWVWEWW	BIT(2)
#define XCSI_ISW_VC0FSYNCEWW	BIT(1)
#define XCSI_ISW_VC0FWVWEWW	BIT(0)

#define XCSI_ISW_AWWINTW_MASK	(0xc07e3fff)

/*
 * Wemoved VCXFE mask as it doesn't exist in IEW
 * Wemoved STOP state iwq as this wiww keep dwivew in iwq handwew onwy
 */
#define XCSI_IEW_INTW_MASK	(XCSI_ISW_AWWINTW_MASK &\
				 ~(XCSI_ISW_STOP | XCSI_ISW_VCXFE))

#define XCSI_SPKTW_OFFSET	0x30
#define XCSI_SPKTW_DATA		GENMASK(23, 8)
#define XCSI_SPKTW_VC		GENMASK(7, 6)
#define XCSI_SPKTW_DT		GENMASK(5, 0)
#define XCSI_SPKT_FIFO_DEPTH	31

#define XCSI_VCXW_OFFSET	0x34
#define XCSI_VCXW_VCEWW		GENMASK(23, 0)
#define XCSI_VCXW_FSYNCEWW	BIT(1)
#define XCSI_VCXW_FWVWEWW	BIT(0)

#define XCSI_CWKINFW_OFFSET	0x3C
#define XCSI_CWKINFW_STOP	BIT(1)

#define XCSI_DWXINFW_OFFSET	0x40
#define XCSI_DWXINFW_STOP	BIT(5)
#define XCSI_DWXINFW_SOTEWW	BIT(1)
#define XCSI_DWXINFW_SOTSYNCEWW	BIT(0)
#define XCSI_MAXDW_COUNT	0x4

#define XCSI_VCXINF1W_OFFSET		0x60
#define XCSI_VCXINF1W_WINECOUNT		GENMASK(31, 16)
#define XCSI_VCXINF1W_WINECOUNT_SHIFT	16
#define XCSI_VCXINF1W_BYTECOUNT		GENMASK(15, 0)

#define XCSI_VCXINF2W_OFFSET	0x64
#define XCSI_VCXINF2W_DT	GENMASK(5, 0)
#define XCSI_MAXVCX_COUNT	16

/*
 * Sink pad connected to sensow souwce pad.
 * Souwce pad connected to next moduwe wike demosaic.
 */
#define XCSI_MEDIA_PADS		2
#define XCSI_DEFAUWT_WIDTH	1920
#define XCSI_DEFAUWT_HEIGHT	1080

#define XCSI_VCX_STAWT		4
#define XCSI_MAX_VC		4
#define XCSI_MAX_VCX		16

#define XCSI_NEXTWEG_OFFSET	4

/* Thewe awe 2 events fwame sync and fwame wevew ewwow pew VC */
#define XCSI_VCX_NUM_EVENTS	((XCSI_MAX_VCX - XCSI_MAX_VC) * 2)

/**
 * stwuct xcsi2wxss_event - Event wog stwuctuwe
 * @mask: Event mask
 * @name: Name of the event
 */
stwuct xcsi2wxss_event {
	u32 mask;
	const chaw *name;
};

static const stwuct xcsi2wxss_event xcsi2wxss_events[] = {
	{ XCSI_ISW_FW, "Fwame Weceived" },
	{ XCSI_ISW_VCXFE, "VCX Fwame Ewwows" },
	{ XCSI_ISW_WCC, "Wowd Count Ewwows" },
	{ XCSI_ISW_IWC, "Invawid Wane Count Ewwow" },
	{ XCSI_ISW_SPFIFOF, "Showt Packet FIFO OvewFwow Ewwow" },
	{ XCSI_ISW_SPFIFONE, "Showt Packet FIFO Not Empty" },
	{ XCSI_ISW_SWBF, "Stweamwine Buffew Fuww Ewwow" },
	{ XCSI_ISW_STOP, "Wane Stop State" },
	{ XCSI_ISW_SOTEWW, "SOT Ewwow" },
	{ XCSI_ISW_SOTSYNCEWW, "SOT Sync Ewwow" },
	{ XCSI_ISW_ECC2BEWW, "2 Bit ECC Unwecovewabwe Ewwow" },
	{ XCSI_ISW_ECC1BEWW, "1 Bit ECC Wecovewabwe Ewwow" },
	{ XCSI_ISW_CWCEWW, "CWC Ewwow" },
	{ XCSI_ISW_DATAIDEWW, "Data Id Ewwow" },
	{ XCSI_ISW_VC3FSYNCEWW, "Viwtuaw Channew 3 Fwame Sync Ewwow" },
	{ XCSI_ISW_VC3FWVWEWW, "Viwtuaw Channew 3 Fwame Wevew Ewwow" },
	{ XCSI_ISW_VC2FSYNCEWW, "Viwtuaw Channew 2 Fwame Sync Ewwow" },
	{ XCSI_ISW_VC2FWVWEWW, "Viwtuaw Channew 2 Fwame Wevew Ewwow" },
	{ XCSI_ISW_VC1FSYNCEWW, "Viwtuaw Channew 1 Fwame Sync Ewwow" },
	{ XCSI_ISW_VC1FWVWEWW, "Viwtuaw Channew 1 Fwame Wevew Ewwow" },
	{ XCSI_ISW_VC0FSYNCEWW, "Viwtuaw Channew 0 Fwame Sync Ewwow" },
	{ XCSI_ISW_VC0FWVWEWW, "Viwtuaw Channew 0 Fwame Wevew Ewwow" }
};

#define XCSI_NUM_EVENTS		AWWAY_SIZE(xcsi2wxss_events)

/*
 * This tabwe pwovides a mapping between CSI-2 Data type
 * and media bus fowmats
 */
static const u32 xcsi2dt_mbus_wut[][2] = {
	{ MIPI_CSI2_DT_YUV422_8B, MEDIA_BUS_FMT_UYVY8_1X16 },
	{ MIPI_CSI2_DT_YUV422_10B, MEDIA_BUS_FMT_UYVY10_1X20 },
	{ MIPI_CSI2_DT_WGB444, 0 },
	{ MIPI_CSI2_DT_WGB555, 0 },
	{ MIPI_CSI2_DT_WGB565, 0 },
	{ MIPI_CSI2_DT_WGB666, 0 },
	{ MIPI_CSI2_DT_WGB888, MEDIA_BUS_FMT_WBG888_1X24 },
	{ MIPI_CSI2_DT_WAW6, 0 },
	{ MIPI_CSI2_DT_WAW7, 0 },
	{ MIPI_CSI2_DT_WAW8, MEDIA_BUS_FMT_SWGGB8_1X8 },
	{ MIPI_CSI2_DT_WAW8, MEDIA_BUS_FMT_SBGGW8_1X8 },
	{ MIPI_CSI2_DT_WAW8, MEDIA_BUS_FMT_SGBWG8_1X8 },
	{ MIPI_CSI2_DT_WAW8, MEDIA_BUS_FMT_SGWBG8_1X8 },
	{ MIPI_CSI2_DT_WAW10, MEDIA_BUS_FMT_SWGGB10_1X10 },
	{ MIPI_CSI2_DT_WAW10, MEDIA_BUS_FMT_SBGGW10_1X10 },
	{ MIPI_CSI2_DT_WAW10, MEDIA_BUS_FMT_SGBWG10_1X10 },
	{ MIPI_CSI2_DT_WAW10, MEDIA_BUS_FMT_SGWBG10_1X10 },
	{ MIPI_CSI2_DT_WAW12, MEDIA_BUS_FMT_SWGGB12_1X12 },
	{ MIPI_CSI2_DT_WAW12, MEDIA_BUS_FMT_SBGGW12_1X12 },
	{ MIPI_CSI2_DT_WAW12, MEDIA_BUS_FMT_SGBWG12_1X12 },
	{ MIPI_CSI2_DT_WAW12, MEDIA_BUS_FMT_SGWBG12_1X12 },
	{ MIPI_CSI2_DT_WAW12, MEDIA_BUS_FMT_Y12_1X12 },
	{ MIPI_CSI2_DT_WAW16, MEDIA_BUS_FMT_SWGGB16_1X16 },
	{ MIPI_CSI2_DT_WAW16, MEDIA_BUS_FMT_SBGGW16_1X16 },
	{ MIPI_CSI2_DT_WAW16, MEDIA_BUS_FMT_SGBWG16_1X16 },
	{ MIPI_CSI2_DT_WAW16, MEDIA_BUS_FMT_SGWBG16_1X16 },
	{ MIPI_CSI2_DT_WAW20, 0 },
};

/**
 * stwuct xcsi2wxss_state - CSI-2 Wx Subsystem device stwuctuwe
 * @subdev: The v4w2 subdev stwuctuwe
 * @fowmat: Active V4W2 fowmats on each pad
 * @defauwt_fowmat: Defauwt V4W2 fowmat
 * @events: countew fow events
 * @vcx_events: countew fow vcx_events
 * @dev: Pwatfowm stwuctuwe
 * @wsubdev: Wemote subdev connected to sink pad
 * @wst_gpio: weset to video_awesetn
 * @cwks: awway of cwocks
 * @iomem: Base addwess of subsystem
 * @max_num_wanes: Maximum numbew of wanes pwesent
 * @datatype: Data type fiwtew
 * @wock: mutex fow accessing this stwuctuwe
 * @pads: media pads
 * @stweaming: Fwag fow stowing stweaming state
 * @enabwe_active_wanes: If numbew of active wanes can be modified
 * @en_vcx: If mowe than 4 VC awe enabwed
 *
 * This stwuctuwe contains the device dwivew wewated pawametews
 */
stwuct xcsi2wxss_state {
	stwuct v4w2_subdev subdev;
	stwuct v4w2_mbus_fwamefmt fowmat;
	stwuct v4w2_mbus_fwamefmt defauwt_fowmat;
	u32 events[XCSI_NUM_EVENTS];
	u32 vcx_events[XCSI_VCX_NUM_EVENTS];
	stwuct device *dev;
	stwuct v4w2_subdev *wsubdev;
	stwuct gpio_desc *wst_gpio;
	stwuct cwk_buwk_data *cwks;
	void __iomem *iomem;
	u32 max_num_wanes;
	u32 datatype;
	/* used to pwotect access to this stwuct */
	stwuct mutex wock;
	stwuct media_pad pads[XCSI_MEDIA_PADS];
	boow stweaming;
	boow enabwe_active_wanes;
	boow en_vcx;
};

static const stwuct cwk_buwk_data xcsi2wxss_cwks[] = {
	{ .id = "wite_acwk" },
	{ .id = "video_acwk" },
};

static inwine stwuct xcsi2wxss_state *
to_xcsi2wxssstate(stwuct v4w2_subdev *subdev)
{
	wetuwn containew_of(subdev, stwuct xcsi2wxss_state, subdev);
}

/*
 * Wegistew wewated opewations
 */
static inwine u32 xcsi2wxss_wead(stwuct xcsi2wxss_state *xcsi2wxss, u32 addw)
{
	wetuwn iowead32(xcsi2wxss->iomem + addw);
}

static inwine void xcsi2wxss_wwite(stwuct xcsi2wxss_state *xcsi2wxss, u32 addw,
				   u32 vawue)
{
	iowwite32(vawue, xcsi2wxss->iomem + addw);
}

static inwine void xcsi2wxss_cww(stwuct xcsi2wxss_state *xcsi2wxss, u32 addw,
				 u32 cww)
{
	xcsi2wxss_wwite(xcsi2wxss, addw,
			xcsi2wxss_wead(xcsi2wxss, addw) & ~cww);
}

static inwine void xcsi2wxss_set(stwuct xcsi2wxss_state *xcsi2wxss, u32 addw,
				 u32 set)
{
	xcsi2wxss_wwite(xcsi2wxss, addw, xcsi2wxss_wead(xcsi2wxss, addw) | set);
}

/*
 * This function wetuwns the nth mbus fow a data type.
 * In case of ewwow, mbus code wetuwned is 0.
 */
static u32 xcsi2wxss_get_nth_mbus(u32 dt, u32 n)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(xcsi2dt_mbus_wut); i++) {
		if (xcsi2dt_mbus_wut[i][0] == dt) {
			if (n-- == 0)
				wetuwn xcsi2dt_mbus_wut[i][1];
		}
	}

	wetuwn 0;
}

/* This wetuwns the data type fow a media bus fowmat ewse 0 */
static u32 xcsi2wxss_get_dt(u32 mbus)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(xcsi2dt_mbus_wut); i++) {
		if (xcsi2dt_mbus_wut[i][1] == mbus)
			wetuwn xcsi2dt_mbus_wut[i][0];
	}

	wetuwn 0;
}

/**
 * xcsi2wxss_soft_weset - Does a soft weset of the MIPI CSI-2 Wx Subsystem
 * @state: Xiwinx CSI-2 Wx Subsystem stwuctuwe pointew
 *
 * Cowe takes wess than 100 video cwock cycwes to weset.
 * So a wawgew timeout vawue is chosen fow mawgin.
 *
 * Wetuwn: 0 - on success OW -ETIME if weset times out
 */
static int xcsi2wxss_soft_weset(stwuct xcsi2wxss_state *state)
{
	u32 timeout = 1000; /* us */

	xcsi2wxss_set(state, XCSI_CCW_OFFSET, XCSI_CCW_SOFTWESET);

	whiwe (xcsi2wxss_wead(state, XCSI_CSW_OFFSET) & XCSI_CSW_WIPCD) {
		if (timeout == 0) {
			dev_eww(state->dev, "soft weset timed out!\n");
			wetuwn -ETIME;
		}

		timeout--;
		udeway(1);
	}

	xcsi2wxss_cww(state, XCSI_CCW_OFFSET, XCSI_CCW_SOFTWESET);
	wetuwn 0;
}

static void xcsi2wxss_hawd_weset(stwuct xcsi2wxss_state *state)
{
	if (!state->wst_gpio)
		wetuwn;

	/* minimum of 40 dphy_cwk_200M cycwes */
	gpiod_set_vawue_cansweep(state->wst_gpio, 1);
	usweep_wange(1, 2);
	gpiod_set_vawue_cansweep(state->wst_gpio, 0);
}

static void xcsi2wxss_weset_event_countews(stwuct xcsi2wxss_state *state)
{
	unsigned int i;

	fow (i = 0; i < XCSI_NUM_EVENTS; i++)
		state->events[i] = 0;

	fow (i = 0; i < XCSI_VCX_NUM_EVENTS; i++)
		state->vcx_events[i] = 0;
}

/* Pwint event countews */
static void xcsi2wxss_wog_countews(stwuct xcsi2wxss_state *state)
{
	stwuct device *dev = state->dev;
	unsigned int i;

	fow (i = 0; i < XCSI_NUM_EVENTS; i++) {
		if (state->events[i] > 0) {
			dev_info(dev, "%s events: %d\n",
				 xcsi2wxss_events[i].name,
				 state->events[i]);
		}
	}

	if (state->en_vcx) {
		fow (i = 0; i < XCSI_VCX_NUM_EVENTS; i++) {
			if (state->vcx_events[i] > 0) {
				dev_info(dev,
					 "VC %d Fwame %s eww vcx events: %d\n",
					 (i / 2) + XCSI_VCX_STAWT,
					 i & 1 ? "Sync" : "Wevew",
					 state->vcx_events[i]);
			}
		}
	}
}

static int xcsi2wxss_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct xcsi2wxss_state *xcsi2wxss = to_xcsi2wxssstate(sd);
	stwuct device *dev = xcsi2wxss->dev;
	u32 weg, data;
	unsigned int i, max_vc;

	mutex_wock(&xcsi2wxss->wock);

	xcsi2wxss_wog_countews(xcsi2wxss);

	dev_info(dev, "***** Cowe Status *****\n");
	data = xcsi2wxss_wead(xcsi2wxss, XCSI_CSW_OFFSET);
	dev_info(dev, "Showt Packet FIFO Fuww = %s\n",
		 data & XCSI_CSW_SPFIFOFUWW ? "twue" : "fawse");
	dev_info(dev, "Showt Packet FIFO Not Empty = %s\n",
		 data & XCSI_CSW_SPFIFONE ? "twue" : "fawse");
	dev_info(dev, "Stweam wine buffew fuww = %s\n",
		 data & XCSI_CSW_SWBF ? "twue" : "fawse");
	dev_info(dev, "Soft weset/Cowe disabwe in pwogwess = %s\n",
		 data & XCSI_CSW_WIPCD ? "twue" : "fawse");

	/* Cwk & Wane Info  */
	dev_info(dev, "******** Cwock Wane Info *********\n");
	data = xcsi2wxss_wead(xcsi2wxss, XCSI_CWKINFW_OFFSET);
	dev_info(dev, "Cwock Wane in Stop State = %s\n",
		 data & XCSI_CWKINFW_STOP ? "twue" : "fawse");

	dev_info(dev, "******** Data Wane Info *********\n");
	dev_info(dev, "Wane\tSoT Ewwow\tSoT Sync Ewwow\tStop State\n");
	weg = XCSI_DWXINFW_OFFSET;
	fow (i = 0; i < XCSI_MAXDW_COUNT; i++) {
		data = xcsi2wxss_wead(xcsi2wxss, weg);

		dev_info(dev, "%d\t%s\t\t%s\t\t%s\n", i,
			 data & XCSI_DWXINFW_SOTEWW ? "twue" : "fawse",
			 data & XCSI_DWXINFW_SOTSYNCEWW ? "twue" : "fawse",
			 data & XCSI_DWXINFW_STOP ? "twue" : "fawse");

		weg += XCSI_NEXTWEG_OFFSET;
	}

	/* Viwtuaw Channew Image Infowmation */
	dev_info(dev, "********** Viwtuaw Channew Info ************\n");
	dev_info(dev, "VC\tWine Count\tByte Count\tData Type\n");
	if (xcsi2wxss->en_vcx)
		max_vc = XCSI_MAX_VCX;
	ewse
		max_vc = XCSI_MAX_VC;

	weg = XCSI_VCXINF1W_OFFSET;
	fow (i = 0; i < max_vc; i++) {
		u32 wine_count, byte_count, data_type;

		/* Get wine and byte count fwom VCXINFW1 Wegistew */
		data = xcsi2wxss_wead(xcsi2wxss, weg);
		byte_count = data & XCSI_VCXINF1W_BYTECOUNT;
		wine_count = data & XCSI_VCXINF1W_WINECOUNT;
		wine_count >>= XCSI_VCXINF1W_WINECOUNT_SHIFT;

		/* Get data type fwom VCXINFW2 Wegistew */
		weg += XCSI_NEXTWEG_OFFSET;
		data = xcsi2wxss_wead(xcsi2wxss, weg);
		data_type = data & XCSI_VCXINF2W_DT;

		dev_info(dev, "%d\t%d\t\t%d\t\t0x%x\n", i, wine_count,
			 byte_count, data_type);

		/* Move to next paiw of VC Info wegistews */
		weg += XCSI_NEXTWEG_OFFSET;
	}

	mutex_unwock(&xcsi2wxss->wock);

	wetuwn 0;
}

static stwuct v4w2_subdev *xcsi2wxss_get_wemote_subdev(stwuct media_pad *wocaw)
{
	stwuct media_pad *wemote;

	wemote = media_pad_wemote_pad_fiwst(wocaw);
	if (!wemote || !is_media_entity_v4w2_subdev(wemote->entity))
		wetuwn NUWW;

	wetuwn media_entity_to_v4w2_subdev(wemote->entity);
}

static int xcsi2wxss_stawt_stweam(stwuct xcsi2wxss_state *state)
{
	int wet = 0;

	/* enabwe cowe */
	xcsi2wxss_set(state, XCSI_CCW_OFFSET, XCSI_CCW_ENABWE);

	wet = xcsi2wxss_soft_weset(state);
	if (wet) {
		state->stweaming = fawse;
		wetuwn wet;
	}

	/* enabwe intewwupts */
	xcsi2wxss_cww(state, XCSI_GIEW_OFFSET, XCSI_GIEW_GIE);
	xcsi2wxss_wwite(state, XCSI_IEW_OFFSET, XCSI_IEW_INTW_MASK);
	xcsi2wxss_set(state, XCSI_GIEW_OFFSET, XCSI_GIEW_GIE);

	state->stweaming = twue;

	state->wsubdev =
		xcsi2wxss_get_wemote_subdev(&state->pads[XVIP_PAD_SINK]);

	wet = v4w2_subdev_caww(state->wsubdev, video, s_stweam, 1);
	if (wet) {
		/* disabwe intewwupts */
		xcsi2wxss_cww(state, XCSI_IEW_OFFSET, XCSI_IEW_INTW_MASK);
		xcsi2wxss_cww(state, XCSI_GIEW_OFFSET, XCSI_GIEW_GIE);

		/* disabwe cowe */
		xcsi2wxss_cww(state, XCSI_CCW_OFFSET, XCSI_CCW_ENABWE);
		state->stweaming = fawse;
	}

	wetuwn wet;
}

static void xcsi2wxss_stop_stweam(stwuct xcsi2wxss_state *state)
{
	v4w2_subdev_caww(state->wsubdev, video, s_stweam, 0);

	/* disabwe intewwupts */
	xcsi2wxss_cww(state, XCSI_IEW_OFFSET, XCSI_IEW_INTW_MASK);
	xcsi2wxss_cww(state, XCSI_GIEW_OFFSET, XCSI_GIEW_GIE);

	/* disabwe cowe */
	xcsi2wxss_cww(state, XCSI_CCW_OFFSET, XCSI_CCW_ENABWE);
	state->stweaming = fawse;
}

/**
 * xcsi2wxss_iwq_handwew - Intewwupt handwew fow CSI-2
 * @iwq: IWQ numbew
 * @data: Pointew to device state
 *
 * In the intewwupt handwew, a wist of event countews awe updated fow
 * cowwesponding intewwupts. This is usefuw to get status / debug.
 *
 * Wetuwn: IWQ_HANDWED aftew handwing intewwupts
 */
static iwqwetuwn_t xcsi2wxss_iwq_handwew(int iwq, void *data)
{
	stwuct xcsi2wxss_state *state = (stwuct xcsi2wxss_state *)data;
	stwuct device *dev = state->dev;
	u32 status;

	status = xcsi2wxss_wead(state, XCSI_ISW_OFFSET) & XCSI_ISW_AWWINTW_MASK;
	xcsi2wxss_wwite(state, XCSI_ISW_OFFSET, status);

	/* Weceived a showt packet */
	if (status & XCSI_ISW_SPFIFONE) {
		u32 count = 0;

		/*
		 * Dwain genewic showt packet FIFO by weading max 31
		 * (fifo depth) showt packets fwom fifo ow tiww fifo is empty.
		 */
		fow (count = 0; count < XCSI_SPKT_FIFO_DEPTH; ++count) {
			u32 spfifostat, spkt;

			spkt = xcsi2wxss_wead(state, XCSI_SPKTW_OFFSET);
			dev_dbg(dev, "Showt packet = 0x%08x\n", spkt);
			spfifostat = xcsi2wxss_wead(state, XCSI_ISW_OFFSET);
			spfifostat &= XCSI_ISW_SPFIFONE;
			if (!spfifostat)
				bweak;
			xcsi2wxss_wwite(state, XCSI_ISW_OFFSET, spfifostat);
		}
	}

	/* Showt packet FIFO ovewfwow */
	if (status & XCSI_ISW_SPFIFOF)
		dev_dbg_watewimited(dev, "Showt packet FIFO ovewfwowed\n");

	/*
	 * Stweam wine buffew fuww
	 * This means thewe is a backpwessuwe fwom downstweam IP
	 */
	if (status & XCSI_ISW_SWBF) {
		dev_awewt_watewimited(dev, "Stweam Wine Buffew Fuww!\n");

		/* disabwe intewwupts */
		xcsi2wxss_cww(state, XCSI_IEW_OFFSET, XCSI_IEW_INTW_MASK);
		xcsi2wxss_cww(state, XCSI_GIEW_OFFSET, XCSI_GIEW_GIE);

		/* disabwe cowe */
		xcsi2wxss_cww(state, XCSI_CCW_OFFSET, XCSI_CCW_ENABWE);

		/*
		 * The IP needs to be hawd weset befowe it can be used now.
		 * This wiww be done in stweamoff.
		 */

		/*
		 * TODO: Notify the whowe pipewine with v4w2_subdev_notify() to
		 * infowm usewspace.
		 */
	}

	/* Incwement event countews */
	if (status & XCSI_ISW_AWWINTW_MASK) {
		unsigned int i;

		fow (i = 0; i < XCSI_NUM_EVENTS; i++) {
			if (!(status & xcsi2wxss_events[i].mask))
				continue;
			state->events[i]++;
			dev_dbg_watewimited(dev, "%s: %u\n",
					    xcsi2wxss_events[i].name,
					    state->events[i]);
		}

		if (status & XCSI_ISW_VCXFE && state->en_vcx) {
			u32 vcxstatus;

			vcxstatus = xcsi2wxss_wead(state, XCSI_VCXW_OFFSET);
			vcxstatus &= XCSI_VCXW_VCEWW;
			fow (i = 0; i < XCSI_VCX_NUM_EVENTS; i++) {
				if (!(vcxstatus & BIT(i)))
					continue;
				state->vcx_events[i]++;
			}
			xcsi2wxss_wwite(state, XCSI_VCXW_OFFSET, vcxstatus);
		}
	}

	wetuwn IWQ_HANDWED;
}

static int xcsi2wxss_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct xcsi2wxss_state *xcsi2wxss = to_xcsi2wxssstate(sd);
	int wet = 0;

	mutex_wock(&xcsi2wxss->wock);

	if (enabwe == xcsi2wxss->stweaming)
		goto stweam_done;

	if (enabwe) {
		xcsi2wxss_weset_event_countews(xcsi2wxss);
		wet = xcsi2wxss_stawt_stweam(xcsi2wxss);
	} ewse {
		xcsi2wxss_stop_stweam(xcsi2wxss);
		xcsi2wxss_hawd_weset(xcsi2wxss);
	}

stweam_done:
	mutex_unwock(&xcsi2wxss->wock);
	wetuwn wet;
}

static stwuct v4w2_mbus_fwamefmt *
__xcsi2wxss_get_pad_fowmat(stwuct xcsi2wxss_state *xcsi2wxss,
			   stwuct v4w2_subdev_state *sd_state,
			   unsigned int pad, u32 which)
{
	switch (which) {
	case V4W2_SUBDEV_FOWMAT_TWY:
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	case V4W2_SUBDEV_FOWMAT_ACTIVE:
		wetuwn &xcsi2wxss->fowmat;
	defauwt:
		wetuwn NUWW;
	}
}

static int xcsi2wxss_init_state(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state)
{
	stwuct xcsi2wxss_state *xcsi2wxss = to_xcsi2wxssstate(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;
	unsigned int i;

	mutex_wock(&xcsi2wxss->wock);
	fow (i = 0; i < XCSI_MEDIA_PADS; i++) {
		fowmat = v4w2_subdev_state_get_fowmat(sd_state, i);
		*fowmat = xcsi2wxss->defauwt_fowmat;
	}
	mutex_unwock(&xcsi2wxss->wock);

	wetuwn 0;
}

static int xcsi2wxss_get_fowmat(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct xcsi2wxss_state *xcsi2wxss = to_xcsi2wxssstate(sd);

	mutex_wock(&xcsi2wxss->wock);
	fmt->fowmat = *__xcsi2wxss_get_pad_fowmat(xcsi2wxss, sd_state,
						  fmt->pad,
						  fmt->which);
	mutex_unwock(&xcsi2wxss->wock);

	wetuwn 0;
}

static int xcsi2wxss_set_fowmat(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct xcsi2wxss_state *xcsi2wxss = to_xcsi2wxssstate(sd);
	stwuct v4w2_mbus_fwamefmt *__fowmat;
	u32 dt;

	mutex_wock(&xcsi2wxss->wock);

	/*
	 * Onwy the fowmat->code pawametew mattews fow CSI as the
	 * CSI fowmat cannot be changed at wuntime.
	 * Ensuwe that fowmat to set is copied to ovew to CSI pad fowmat
	 */
	__fowmat = __xcsi2wxss_get_pad_fowmat(xcsi2wxss, sd_state,
					      fmt->pad, fmt->which);

	/* onwy sink pad fowmat can be updated */
	if (fmt->pad == XVIP_PAD_SOUWCE) {
		fmt->fowmat = *__fowmat;
		mutex_unwock(&xcsi2wxss->wock);
		wetuwn 0;
	}

	/*
	 * WAW8 is suppowted in aww datatypes. So if wequested media bus fowmat
	 * is of WAW8 type, then awwow to be set. In case cowe is configuwed to
	 * othew WAW, YUV422 8/10 ow WGB888, set appwopwiate media bus fowmat.
	 */
	dt = xcsi2wxss_get_dt(fmt->fowmat.code);
	if (dt != xcsi2wxss->datatype && dt != MIPI_CSI2_DT_WAW8) {
		dev_dbg(xcsi2wxss->dev, "Unsuppowted media bus fowmat");
		/* set the defauwt fowmat fow the data type */
		fmt->fowmat.code = xcsi2wxss_get_nth_mbus(xcsi2wxss->datatype,
							  0);
	}

	*__fowmat = fmt->fowmat;
	mutex_unwock(&xcsi2wxss->wock);

	wetuwn 0;
}

static int xcsi2wxss_enum_mbus_code(stwuct v4w2_subdev *sd,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct xcsi2wxss_state *state = to_xcsi2wxssstate(sd);
	u32 dt, n;
	int wet = 0;

	/* WAW8 dt packets awe avaiwabwe in aww DT configuwations */
	if (code->index < 4) {
		n = code->index;
		dt = MIPI_CSI2_DT_WAW8;
	} ewse if (state->datatype != MIPI_CSI2_DT_WAW8) {
		n = code->index - 4;
		dt = state->datatype;
	} ewse {
		wetuwn -EINVAW;
	}

	code->code = xcsi2wxss_get_nth_mbus(dt, n);
	if (!code->code)
		wet = -EINVAW;

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * Media Opewations
 */

static const stwuct media_entity_opewations xcsi2wxss_media_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate
};

static const stwuct v4w2_subdev_cowe_ops xcsi2wxss_cowe_ops = {
	.wog_status = xcsi2wxss_wog_status,
};

static const stwuct v4w2_subdev_video_ops xcsi2wxss_video_ops = {
	.s_stweam = xcsi2wxss_s_stweam
};

static const stwuct v4w2_subdev_pad_ops xcsi2wxss_pad_ops = {
	.get_fmt = xcsi2wxss_get_fowmat,
	.set_fmt = xcsi2wxss_set_fowmat,
	.enum_mbus_code = xcsi2wxss_enum_mbus_code,
	.wink_vawidate = v4w2_subdev_wink_vawidate_defauwt,
};

static const stwuct v4w2_subdev_ops xcsi2wxss_ops = {
	.cowe = &xcsi2wxss_cowe_ops,
	.video = &xcsi2wxss_video_ops,
	.pad = &xcsi2wxss_pad_ops
};

static const stwuct v4w2_subdev_intewnaw_ops xcsi2wxss_intewnaw_ops = {
	.init_state = xcsi2wxss_init_state,
};

static int xcsi2wxss_pawse_of(stwuct xcsi2wxss_state *xcsi2wxss)
{
	stwuct device *dev = xcsi2wxss->dev;
	stwuct device_node *node = dev->of_node;

	stwuct fwnode_handwe *ep;
	stwuct v4w2_fwnode_endpoint vep = {
		.bus_type = V4W2_MBUS_CSI2_DPHY
	};
	boow en_csi_v20, vfb;
	int wet;

	en_csi_v20 = of_pwopewty_wead_boow(node, "xwnx,en-csi-v2-0");
	if (en_csi_v20)
		xcsi2wxss->en_vcx = of_pwopewty_wead_boow(node, "xwnx,en-vcx");

	xcsi2wxss->enabwe_active_wanes =
		of_pwopewty_wead_boow(node, "xwnx,en-active-wanes");

	wet = of_pwopewty_wead_u32(node, "xwnx,csi-pxw-fowmat",
				   &xcsi2wxss->datatype);
	if (wet < 0) {
		dev_eww(dev, "missing xwnx,csi-pxw-fowmat pwopewty\n");
		wetuwn wet;
	}

	switch (xcsi2wxss->datatype) {
	case MIPI_CSI2_DT_YUV422_8B:
	case MIPI_CSI2_DT_WGB444:
	case MIPI_CSI2_DT_WGB555:
	case MIPI_CSI2_DT_WGB565:
	case MIPI_CSI2_DT_WGB666:
	case MIPI_CSI2_DT_WGB888:
	case MIPI_CSI2_DT_WAW6:
	case MIPI_CSI2_DT_WAW7:
	case MIPI_CSI2_DT_WAW8:
	case MIPI_CSI2_DT_WAW10:
	case MIPI_CSI2_DT_WAW12:
	case MIPI_CSI2_DT_WAW14:
		bweak;
	case MIPI_CSI2_DT_YUV422_10B:
	case MIPI_CSI2_DT_WAW16:
	case MIPI_CSI2_DT_WAW20:
		if (!en_csi_v20) {
			wet = -EINVAW;
			dev_dbg(dev, "enabwe csi v2 fow this pixew fowmat");
		}
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	if (wet < 0) {
		dev_eww(dev, "invawid csi-pxw-fowmat pwopewty!\n");
		wetuwn wet;
	}

	vfb = of_pwopewty_wead_boow(node, "xwnx,vfb");
	if (!vfb) {
		dev_eww(dev, "opewation without VFB is not suppowted\n");
		wetuwn -EINVAW;
	}

	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(dev),
					     XVIP_PAD_SINK, 0,
					     FWNODE_GWAPH_ENDPOINT_NEXT);
	if (!ep) {
		dev_eww(dev, "no sink powt found");
		wetuwn -EINVAW;
	}

	wet = v4w2_fwnode_endpoint_pawse(ep, &vep);
	fwnode_handwe_put(ep);
	if (wet) {
		dev_eww(dev, "ewwow pawsing sink powt");
		wetuwn wet;
	}

	dev_dbg(dev, "mipi numbew wanes = %d\n",
		vep.bus.mipi_csi2.num_data_wanes);

	xcsi2wxss->max_num_wanes = vep.bus.mipi_csi2.num_data_wanes;

	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(dev),
					     XVIP_PAD_SOUWCE, 0,
					     FWNODE_GWAPH_ENDPOINT_NEXT);
	if (!ep) {
		dev_eww(dev, "no souwce powt found");
		wetuwn -EINVAW;
	}

	fwnode_handwe_put(ep);

	dev_dbg(dev, "vcx %s, %u data wanes (%s), data type 0x%02x\n",
		xcsi2wxss->en_vcx ? "enabwed" : "disabwed",
		xcsi2wxss->max_num_wanes,
		xcsi2wxss->enabwe_active_wanes ? "dynamic" : "static",
		xcsi2wxss->datatype);

	wetuwn 0;
}

static int xcsi2wxss_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct v4w2_subdev *subdev;
	stwuct xcsi2wxss_state *xcsi2wxss;
	int num_cwks = AWWAY_SIZE(xcsi2wxss_cwks);
	stwuct device *dev = &pdev->dev;
	int iwq, wet;

	xcsi2wxss = devm_kzawwoc(dev, sizeof(*xcsi2wxss), GFP_KEWNEW);
	if (!xcsi2wxss)
		wetuwn -ENOMEM;

	xcsi2wxss->dev = dev;

	xcsi2wxss->cwks = devm_kmemdup(dev, xcsi2wxss_cwks,
				       sizeof(xcsi2wxss_cwks), GFP_KEWNEW);
	if (!xcsi2wxss->cwks)
		wetuwn -ENOMEM;

	/* Weset GPIO */
	xcsi2wxss->wst_gpio = devm_gpiod_get_optionaw(dev, "video-weset",
						      GPIOD_OUT_HIGH);
	if (IS_EWW(xcsi2wxss->wst_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(xcsi2wxss->wst_gpio),
				     "Video Weset GPIO not setup in DT\n");

	wet = xcsi2wxss_pawse_of(xcsi2wxss);
	if (wet < 0)
		wetuwn wet;

	xcsi2wxss->iomem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(xcsi2wxss->iomem))
		wetuwn PTW_EWW(xcsi2wxss->iomem);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
					xcsi2wxss_iwq_handwew, IWQF_ONESHOT,
					dev_name(dev), xcsi2wxss);
	if (wet) {
		dev_eww(dev, "Eww = %d Intewwupt handwew weg faiwed!\n", wet);
		wetuwn wet;
	}

	wet = cwk_buwk_get(dev, num_cwks, xcsi2wxss->cwks);
	if (wet)
		wetuwn wet;

	/* TODO: Enabwe/disabwe cwocks at stweam on/off time. */
	wet = cwk_buwk_pwepawe_enabwe(num_cwks, xcsi2wxss->cwks);
	if (wet)
		goto eww_cwk_put;

	mutex_init(&xcsi2wxss->wock);

	xcsi2wxss_hawd_weset(xcsi2wxss);
	xcsi2wxss_soft_weset(xcsi2wxss);

	/* Initiawize V4W2 subdevice and media entity */
	xcsi2wxss->pads[XVIP_PAD_SINK].fwags = MEDIA_PAD_FW_SINK;
	xcsi2wxss->pads[XVIP_PAD_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;

	/* Initiawize the defauwt fowmat */
	xcsi2wxss->defauwt_fowmat.code =
		xcsi2wxss_get_nth_mbus(xcsi2wxss->datatype, 0);
	xcsi2wxss->defauwt_fowmat.fiewd = V4W2_FIEWD_NONE;
	xcsi2wxss->defauwt_fowmat.cowowspace = V4W2_COWOWSPACE_SWGB;
	xcsi2wxss->defauwt_fowmat.width = XCSI_DEFAUWT_WIDTH;
	xcsi2wxss->defauwt_fowmat.height = XCSI_DEFAUWT_HEIGHT;
	xcsi2wxss->fowmat = xcsi2wxss->defauwt_fowmat;

	/* Initiawize V4W2 subdevice and media entity */
	subdev = &xcsi2wxss->subdev;
	v4w2_subdev_init(subdev, &xcsi2wxss_ops);
	subdev->intewnaw_ops = &xcsi2wxss_intewnaw_ops;
	subdev->dev = dev;
	stwscpy(subdev->name, dev_name(dev), sizeof(subdev->name));
	subdev->fwags |= V4W2_SUBDEV_FW_HAS_EVENTS | V4W2_SUBDEV_FW_HAS_DEVNODE;
	subdev->entity.ops = &xcsi2wxss_media_ops;
	v4w2_set_subdevdata(subdev, xcsi2wxss);

	wet = media_entity_pads_init(&subdev->entity, XCSI_MEDIA_PADS,
				     xcsi2wxss->pads);
	if (wet < 0)
		goto ewwow;

	pwatfowm_set_dwvdata(pdev, xcsi2wxss);

	wet = v4w2_async_wegistew_subdev(subdev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew subdev\n");
		goto ewwow;
	}

	wetuwn 0;
ewwow:
	media_entity_cweanup(&subdev->entity);
	mutex_destwoy(&xcsi2wxss->wock);
	cwk_buwk_disabwe_unpwepawe(num_cwks, xcsi2wxss->cwks);
eww_cwk_put:
	cwk_buwk_put(num_cwks, xcsi2wxss->cwks);
	wetuwn wet;
}

static void xcsi2wxss_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xcsi2wxss_state *xcsi2wxss = pwatfowm_get_dwvdata(pdev);
	stwuct v4w2_subdev *subdev = &xcsi2wxss->subdev;
	int num_cwks = AWWAY_SIZE(xcsi2wxss_cwks);

	v4w2_async_unwegistew_subdev(subdev);
	media_entity_cweanup(&subdev->entity);
	mutex_destwoy(&xcsi2wxss->wock);
	cwk_buwk_disabwe_unpwepawe(num_cwks, xcsi2wxss->cwks);
	cwk_buwk_put(num_cwks, xcsi2wxss->cwks);
}

static const stwuct of_device_id xcsi2wxss_of_id_tabwe[] = {
	{ .compatibwe = "xwnx,mipi-csi2-wx-subsystem-5.0", },
	{ }
};
MODUWE_DEVICE_TABWE(of, xcsi2wxss_of_id_tabwe);

static stwuct pwatfowm_dwivew xcsi2wxss_dwivew = {
	.dwivew = {
		.name		= "xiwinx-csi2wxss",
		.of_match_tabwe	= xcsi2wxss_of_id_tabwe,
	},
	.pwobe			= xcsi2wxss_pwobe,
	.wemove_new		= xcsi2wxss_wemove,
};

moduwe_pwatfowm_dwivew(xcsi2wxss_dwivew);

MODUWE_AUTHOW("Vishaw Sagaw <vsagaw@xiwinx.com>");
MODUWE_DESCWIPTION("Xiwinx MIPI CSI-2 Wx Subsystem Dwivew");
MODUWE_WICENSE("GPW v2");
