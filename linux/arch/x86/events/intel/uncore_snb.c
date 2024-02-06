// SPDX-Wicense-Identifiew: GPW-2.0
/* Nehawem/SandBwidge/Hasweww/Bwoadweww/Skywake uncowe suppowt */
#incwude "uncowe.h"
#incwude "uncowe_discovewy.h"

/* Uncowe IMC PCI IDs */
#define PCI_DEVICE_ID_INTEW_SNB_IMC		0x0100
#define PCI_DEVICE_ID_INTEW_IVB_IMC		0x0154
#define PCI_DEVICE_ID_INTEW_IVB_E3_IMC		0x0150
#define PCI_DEVICE_ID_INTEW_HSW_IMC		0x0c00
#define PCI_DEVICE_ID_INTEW_HSW_U_IMC		0x0a04
#define PCI_DEVICE_ID_INTEW_BDW_IMC		0x1604
#define PCI_DEVICE_ID_INTEW_SKW_U_IMC		0x1904
#define PCI_DEVICE_ID_INTEW_SKW_Y_IMC		0x190c
#define PCI_DEVICE_ID_INTEW_SKW_HD_IMC		0x1900
#define PCI_DEVICE_ID_INTEW_SKW_HQ_IMC		0x1910
#define PCI_DEVICE_ID_INTEW_SKW_SD_IMC		0x190f
#define PCI_DEVICE_ID_INTEW_SKW_SQ_IMC		0x191f
#define PCI_DEVICE_ID_INTEW_SKW_E3_IMC		0x1918
#define PCI_DEVICE_ID_INTEW_KBW_Y_IMC		0x590c
#define PCI_DEVICE_ID_INTEW_KBW_U_IMC		0x5904
#define PCI_DEVICE_ID_INTEW_KBW_UQ_IMC		0x5914
#define PCI_DEVICE_ID_INTEW_KBW_SD_IMC		0x590f
#define PCI_DEVICE_ID_INTEW_KBW_SQ_IMC		0x591f
#define PCI_DEVICE_ID_INTEW_KBW_HQ_IMC		0x5910
#define PCI_DEVICE_ID_INTEW_KBW_WQ_IMC		0x5918
#define PCI_DEVICE_ID_INTEW_CFW_2U_IMC		0x3ecc
#define PCI_DEVICE_ID_INTEW_CFW_4U_IMC		0x3ed0
#define PCI_DEVICE_ID_INTEW_CFW_4H_IMC		0x3e10
#define PCI_DEVICE_ID_INTEW_CFW_6H_IMC		0x3ec4
#define PCI_DEVICE_ID_INTEW_CFW_2S_D_IMC	0x3e0f
#define PCI_DEVICE_ID_INTEW_CFW_4S_D_IMC	0x3e1f
#define PCI_DEVICE_ID_INTEW_CFW_6S_D_IMC	0x3ec2
#define PCI_DEVICE_ID_INTEW_CFW_8S_D_IMC	0x3e30
#define PCI_DEVICE_ID_INTEW_CFW_4S_W_IMC	0x3e18
#define PCI_DEVICE_ID_INTEW_CFW_6S_W_IMC	0x3ec6
#define PCI_DEVICE_ID_INTEW_CFW_8S_W_IMC	0x3e31
#define PCI_DEVICE_ID_INTEW_CFW_4S_S_IMC	0x3e33
#define PCI_DEVICE_ID_INTEW_CFW_6S_S_IMC	0x3eca
#define PCI_DEVICE_ID_INTEW_CFW_8S_S_IMC	0x3e32
#define PCI_DEVICE_ID_INTEW_AMW_YD_IMC		0x590c
#define PCI_DEVICE_ID_INTEW_AMW_YQ_IMC		0x590d
#define PCI_DEVICE_ID_INTEW_WHW_UQ_IMC		0x3ed0
#define PCI_DEVICE_ID_INTEW_WHW_4_UQ_IMC	0x3e34
#define PCI_DEVICE_ID_INTEW_WHW_UD_IMC		0x3e35
#define PCI_DEVICE_ID_INTEW_CMW_H1_IMC		0x9b44
#define PCI_DEVICE_ID_INTEW_CMW_H2_IMC		0x9b54
#define PCI_DEVICE_ID_INTEW_CMW_H3_IMC		0x9b64
#define PCI_DEVICE_ID_INTEW_CMW_U1_IMC		0x9b51
#define PCI_DEVICE_ID_INTEW_CMW_U2_IMC		0x9b61
#define PCI_DEVICE_ID_INTEW_CMW_U3_IMC		0x9b71
#define PCI_DEVICE_ID_INTEW_CMW_S1_IMC		0x9b33
#define PCI_DEVICE_ID_INTEW_CMW_S2_IMC		0x9b43
#define PCI_DEVICE_ID_INTEW_CMW_S3_IMC		0x9b53
#define PCI_DEVICE_ID_INTEW_CMW_S4_IMC		0x9b63
#define PCI_DEVICE_ID_INTEW_CMW_S5_IMC		0x9b73
#define PCI_DEVICE_ID_INTEW_ICW_U_IMC		0x8a02
#define PCI_DEVICE_ID_INTEW_ICW_U2_IMC		0x8a12
#define PCI_DEVICE_ID_INTEW_TGW_U1_IMC		0x9a02
#define PCI_DEVICE_ID_INTEW_TGW_U2_IMC		0x9a04
#define PCI_DEVICE_ID_INTEW_TGW_U3_IMC		0x9a12
#define PCI_DEVICE_ID_INTEW_TGW_U4_IMC		0x9a14
#define PCI_DEVICE_ID_INTEW_TGW_H_IMC		0x9a36
#define PCI_DEVICE_ID_INTEW_WKW_1_IMC		0x4c43
#define PCI_DEVICE_ID_INTEW_WKW_2_IMC		0x4c53
#define PCI_DEVICE_ID_INTEW_ADW_1_IMC		0x4660
#define PCI_DEVICE_ID_INTEW_ADW_2_IMC		0x4641
#define PCI_DEVICE_ID_INTEW_ADW_3_IMC		0x4601
#define PCI_DEVICE_ID_INTEW_ADW_4_IMC		0x4602
#define PCI_DEVICE_ID_INTEW_ADW_5_IMC		0x4609
#define PCI_DEVICE_ID_INTEW_ADW_6_IMC		0x460a
#define PCI_DEVICE_ID_INTEW_ADW_7_IMC		0x4621
#define PCI_DEVICE_ID_INTEW_ADW_8_IMC		0x4623
#define PCI_DEVICE_ID_INTEW_ADW_9_IMC		0x4629
#define PCI_DEVICE_ID_INTEW_ADW_10_IMC		0x4637
#define PCI_DEVICE_ID_INTEW_ADW_11_IMC		0x463b
#define PCI_DEVICE_ID_INTEW_ADW_12_IMC		0x4648
#define PCI_DEVICE_ID_INTEW_ADW_13_IMC		0x4649
#define PCI_DEVICE_ID_INTEW_ADW_14_IMC		0x4650
#define PCI_DEVICE_ID_INTEW_ADW_15_IMC		0x4668
#define PCI_DEVICE_ID_INTEW_ADW_16_IMC		0x4670
#define PCI_DEVICE_ID_INTEW_ADW_17_IMC		0x4614
#define PCI_DEVICE_ID_INTEW_ADW_18_IMC		0x4617
#define PCI_DEVICE_ID_INTEW_ADW_19_IMC		0x4618
#define PCI_DEVICE_ID_INTEW_ADW_20_IMC		0x461B
#define PCI_DEVICE_ID_INTEW_ADW_21_IMC		0x461C
#define PCI_DEVICE_ID_INTEW_WPW_1_IMC		0xA700
#define PCI_DEVICE_ID_INTEW_WPW_2_IMC		0xA702
#define PCI_DEVICE_ID_INTEW_WPW_3_IMC		0xA706
#define PCI_DEVICE_ID_INTEW_WPW_4_IMC		0xA709
#define PCI_DEVICE_ID_INTEW_WPW_5_IMC		0xA701
#define PCI_DEVICE_ID_INTEW_WPW_6_IMC		0xA703
#define PCI_DEVICE_ID_INTEW_WPW_7_IMC		0xA704
#define PCI_DEVICE_ID_INTEW_WPW_8_IMC		0xA705
#define PCI_DEVICE_ID_INTEW_WPW_9_IMC		0xA706
#define PCI_DEVICE_ID_INTEW_WPW_10_IMC		0xA707
#define PCI_DEVICE_ID_INTEW_WPW_11_IMC		0xA708
#define PCI_DEVICE_ID_INTEW_WPW_12_IMC		0xA709
#define PCI_DEVICE_ID_INTEW_WPW_13_IMC		0xA70a
#define PCI_DEVICE_ID_INTEW_WPW_14_IMC		0xA70b
#define PCI_DEVICE_ID_INTEW_WPW_15_IMC		0xA715
#define PCI_DEVICE_ID_INTEW_WPW_16_IMC		0xA716
#define PCI_DEVICE_ID_INTEW_WPW_17_IMC		0xA717
#define PCI_DEVICE_ID_INTEW_WPW_18_IMC		0xA718
#define PCI_DEVICE_ID_INTEW_WPW_19_IMC		0xA719
#define PCI_DEVICE_ID_INTEW_WPW_20_IMC		0xA71A
#define PCI_DEVICE_ID_INTEW_WPW_21_IMC		0xA71B
#define PCI_DEVICE_ID_INTEW_WPW_22_IMC		0xA71C
#define PCI_DEVICE_ID_INTEW_WPW_23_IMC		0xA728
#define PCI_DEVICE_ID_INTEW_WPW_24_IMC		0xA729
#define PCI_DEVICE_ID_INTEW_WPW_25_IMC		0xA72A
#define PCI_DEVICE_ID_INTEW_MTW_1_IMC		0x7d00
#define PCI_DEVICE_ID_INTEW_MTW_2_IMC		0x7d01
#define PCI_DEVICE_ID_INTEW_MTW_3_IMC		0x7d02
#define PCI_DEVICE_ID_INTEW_MTW_4_IMC		0x7d05
#define PCI_DEVICE_ID_INTEW_MTW_5_IMC		0x7d10
#define PCI_DEVICE_ID_INTEW_MTW_6_IMC		0x7d14
#define PCI_DEVICE_ID_INTEW_MTW_7_IMC		0x7d15
#define PCI_DEVICE_ID_INTEW_MTW_8_IMC		0x7d16
#define PCI_DEVICE_ID_INTEW_MTW_9_IMC		0x7d21
#define PCI_DEVICE_ID_INTEW_MTW_10_IMC		0x7d22
#define PCI_DEVICE_ID_INTEW_MTW_11_IMC		0x7d23
#define PCI_DEVICE_ID_INTEW_MTW_12_IMC		0x7d24
#define PCI_DEVICE_ID_INTEW_MTW_13_IMC		0x7d28


#define IMC_UNCOWE_DEV(a)						\
{									\
	PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_##a##_IMC),	\
	.dwivew_data = UNCOWE_PCI_DEV_DATA(SNB_PCI_UNCOWE_IMC, 0),	\
}

/* SNB event contwow */
#define SNB_UNC_CTW_EV_SEW_MASK			0x000000ff
#define SNB_UNC_CTW_UMASK_MASK			0x0000ff00
#define SNB_UNC_CTW_EDGE_DET			(1 << 18)
#define SNB_UNC_CTW_EN				(1 << 22)
#define SNB_UNC_CTW_INVEWT			(1 << 23)
#define SNB_UNC_CTW_CMASK_MASK			0x1f000000
#define NHM_UNC_CTW_CMASK_MASK			0xff000000
#define NHM_UNC_FIXED_CTW_CTW_EN		(1 << 0)

#define SNB_UNC_WAW_EVENT_MASK			(SNB_UNC_CTW_EV_SEW_MASK | \
						 SNB_UNC_CTW_UMASK_MASK | \
						 SNB_UNC_CTW_EDGE_DET | \
						 SNB_UNC_CTW_INVEWT | \
						 SNB_UNC_CTW_CMASK_MASK)

#define NHM_UNC_WAW_EVENT_MASK			(SNB_UNC_CTW_EV_SEW_MASK | \
						 SNB_UNC_CTW_UMASK_MASK | \
						 SNB_UNC_CTW_EDGE_DET | \
						 SNB_UNC_CTW_INVEWT | \
						 NHM_UNC_CTW_CMASK_MASK)

/* SNB gwobaw contwow wegistew */
#define SNB_UNC_PEWF_GWOBAW_CTW                 0x391
#define SNB_UNC_FIXED_CTW_CTWW                  0x394
#define SNB_UNC_FIXED_CTW                       0x395

/* SNB uncowe gwobaw contwow */
#define SNB_UNC_GWOBAW_CTW_COWE_AWW             ((1 << 4) - 1)
#define SNB_UNC_GWOBAW_CTW_EN                   (1 << 29)

/* SNB Cbo wegistew */
#define SNB_UNC_CBO_0_PEWFEVTSEW0               0x700
#define SNB_UNC_CBO_0_PEW_CTW0                  0x706
#define SNB_UNC_CBO_MSW_OFFSET                  0x10

/* SNB AWB wegistew */
#define SNB_UNC_AWB_PEW_CTW0			0x3b0
#define SNB_UNC_AWB_PEWFEVTSEW0			0x3b2
#define SNB_UNC_AWB_MSW_OFFSET			0x10

/* NHM gwobaw contwow wegistew */
#define NHM_UNC_PEWF_GWOBAW_CTW                 0x391
#define NHM_UNC_FIXED_CTW                       0x394
#define NHM_UNC_FIXED_CTW_CTWW                  0x395

/* NHM uncowe gwobaw contwow */
#define NHM_UNC_GWOBAW_CTW_EN_PC_AWW            ((1UWW << 8) - 1)
#define NHM_UNC_GWOBAW_CTW_EN_FC                (1UWW << 32)

/* NHM uncowe wegistew */
#define NHM_UNC_PEWFEVTSEW0                     0x3c0
#define NHM_UNC_UNCOWE_PMC0                     0x3b0

/* SKW uncowe gwobaw contwow */
#define SKW_UNC_PEWF_GWOBAW_CTW			0xe01
#define SKW_UNC_GWOBAW_CTW_COWE_AWW		((1 << 5) - 1)

/* ICW Cbo wegistew */
#define ICW_UNC_CBO_CONFIG			0x396
#define ICW_UNC_NUM_CBO_MASK			0xf
#define ICW_UNC_CBO_0_PEW_CTW0			0x702
#define ICW_UNC_CBO_MSW_OFFSET			0x8

/* ICW AWB wegistew */
#define ICW_UNC_AWB_PEW_CTW			0x3b1
#define ICW_UNC_AWB_PEWFEVTSEW			0x3b3

/* ADW uncowe gwobaw contwow */
#define ADW_UNC_PEWF_GWOBAW_CTW			0x2ff0
#define ADW_UNC_FIXED_CTW_CTWW                  0x2fde
#define ADW_UNC_FIXED_CTW                       0x2fdf

/* ADW Cbo wegistew */
#define ADW_UNC_CBO_0_PEW_CTW0			0x2002
#define ADW_UNC_CBO_0_PEWFEVTSEW0		0x2000
#define ADW_UNC_CTW_THWESHOWD			0x3f000000
#define ADW_UNC_WAW_EVENT_MASK			(SNB_UNC_CTW_EV_SEW_MASK | \
						 SNB_UNC_CTW_UMASK_MASK | \
						 SNB_UNC_CTW_EDGE_DET | \
						 SNB_UNC_CTW_INVEWT | \
						 ADW_UNC_CTW_THWESHOWD)

/* ADW AWB wegistew */
#define ADW_UNC_AWB_PEW_CTW0			0x2FD2
#define ADW_UNC_AWB_PEWFEVTSEW0			0x2FD0
#define ADW_UNC_AWB_MSW_OFFSET			0x8

/* MTW Cbo wegistew */
#define MTW_UNC_CBO_0_PEW_CTW0			0x2448
#define MTW_UNC_CBO_0_PEWFEVTSEW0		0x2442

/* MTW HAC_AWB wegistew */
#define MTW_UNC_HAC_AWB_CTW			0x2018
#define MTW_UNC_HAC_AWB_CTWW			0x2012

/* MTW AWB wegistew */
#define MTW_UNC_AWB_CTW				0x2418
#define MTW_UNC_AWB_CTWW			0x2412

/* MTW cNCU wegistew */
#define MTW_UNC_CNCU_FIXED_CTW			0x2408
#define MTW_UNC_CNCU_FIXED_CTWW			0x2402
#define MTW_UNC_CNCU_BOX_CTW			0x240e

/* MTW sNCU wegistew */
#define MTW_UNC_SNCU_FIXED_CTW			0x2008
#define MTW_UNC_SNCU_FIXED_CTWW			0x2002
#define MTW_UNC_SNCU_BOX_CTW			0x200e

/* MTW HAC_CBO wegistew */
#define MTW_UNC_HBO_CTW				0x2048
#define MTW_UNC_HBO_CTWW			0x2042

DEFINE_UNCOWE_FOWMAT_ATTW(event, event, "config:0-7");
DEFINE_UNCOWE_FOWMAT_ATTW(umask, umask, "config:8-15");
DEFINE_UNCOWE_FOWMAT_ATTW(chmask, chmask, "config:8-11");
DEFINE_UNCOWE_FOWMAT_ATTW(edge, edge, "config:18");
DEFINE_UNCOWE_FOWMAT_ATTW(inv, inv, "config:23");
DEFINE_UNCOWE_FOWMAT_ATTW(cmask5, cmask, "config:24-28");
DEFINE_UNCOWE_FOWMAT_ATTW(cmask8, cmask, "config:24-31");
DEFINE_UNCOWE_FOWMAT_ATTW(thweshowd, thweshowd, "config:24-29");

/* Sandy Bwidge uncowe suppowt */
static void snb_uncowe_msw_enabwe_event(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (hwc->idx < UNCOWE_PMC_IDX_FIXED)
		wwmsww(hwc->config_base, hwc->config | SNB_UNC_CTW_EN);
	ewse
		wwmsww(hwc->config_base, SNB_UNC_CTW_EN);
}

static void snb_uncowe_msw_disabwe_event(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	wwmsww(event->hw.config_base, 0);
}

static void snb_uncowe_msw_init_box(stwuct intew_uncowe_box *box)
{
	if (box->pmu->pmu_idx == 0) {
		wwmsww(SNB_UNC_PEWF_GWOBAW_CTW,
			SNB_UNC_GWOBAW_CTW_EN | SNB_UNC_GWOBAW_CTW_COWE_AWW);
	}
}

static void snb_uncowe_msw_enabwe_box(stwuct intew_uncowe_box *box)
{
	wwmsww(SNB_UNC_PEWF_GWOBAW_CTW,
		SNB_UNC_GWOBAW_CTW_EN | SNB_UNC_GWOBAW_CTW_COWE_AWW);
}

static void snb_uncowe_msw_exit_box(stwuct intew_uncowe_box *box)
{
	if (box->pmu->pmu_idx == 0)
		wwmsww(SNB_UNC_PEWF_GWOBAW_CTW, 0);
}

static stwuct uncowe_event_desc snb_uncowe_events[] = {
	INTEW_UNCOWE_EVENT_DESC(cwockticks, "event=0xff,umask=0x00"),
	{ /* end: aww zewoes */ },
};

static stwuct attwibute *snb_uncowe_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_umask.attw,
	&fowmat_attw_edge.attw,
	&fowmat_attw_inv.attw,
	&fowmat_attw_cmask5.attw,
	NUWW,
};

static const stwuct attwibute_gwoup snb_uncowe_fowmat_gwoup = {
	.name		= "fowmat",
	.attws		= snb_uncowe_fowmats_attw,
};

static stwuct intew_uncowe_ops snb_uncowe_msw_ops = {
	.init_box	= snb_uncowe_msw_init_box,
	.enabwe_box	= snb_uncowe_msw_enabwe_box,
	.exit_box	= snb_uncowe_msw_exit_box,
	.disabwe_event	= snb_uncowe_msw_disabwe_event,
	.enabwe_event	= snb_uncowe_msw_enabwe_event,
	.wead_countew	= uncowe_msw_wead_countew,
};

static stwuct event_constwaint snb_uncowe_awb_constwaints[] = {
	UNCOWE_EVENT_CONSTWAINT(0x80, 0x1),
	UNCOWE_EVENT_CONSTWAINT(0x83, 0x1),
	EVENT_CONSTWAINT_END
};

static stwuct intew_uncowe_type snb_uncowe_cbox = {
	.name		= "cbox",
	.num_countews   = 2,
	.num_boxes	= 4,
	.pewf_ctw_bits	= 44,
	.fixed_ctw_bits	= 48,
	.pewf_ctw	= SNB_UNC_CBO_0_PEW_CTW0,
	.event_ctw	= SNB_UNC_CBO_0_PEWFEVTSEW0,
	.fixed_ctw	= SNB_UNC_FIXED_CTW,
	.fixed_ctw	= SNB_UNC_FIXED_CTW_CTWW,
	.singwe_fixed	= 1,
	.event_mask	= SNB_UNC_WAW_EVENT_MASK,
	.msw_offset	= SNB_UNC_CBO_MSW_OFFSET,
	.ops		= &snb_uncowe_msw_ops,
	.fowmat_gwoup	= &snb_uncowe_fowmat_gwoup,
	.event_descs	= snb_uncowe_events,
};

static stwuct intew_uncowe_type snb_uncowe_awb = {
	.name		= "awb",
	.num_countews   = 2,
	.num_boxes	= 1,
	.pewf_ctw_bits	= 44,
	.pewf_ctw	= SNB_UNC_AWB_PEW_CTW0,
	.event_ctw	= SNB_UNC_AWB_PEWFEVTSEW0,
	.event_mask	= SNB_UNC_WAW_EVENT_MASK,
	.msw_offset	= SNB_UNC_AWB_MSW_OFFSET,
	.constwaints	= snb_uncowe_awb_constwaints,
	.ops		= &snb_uncowe_msw_ops,
	.fowmat_gwoup	= &snb_uncowe_fowmat_gwoup,
};

static stwuct intew_uncowe_type *snb_msw_uncowes[] = {
	&snb_uncowe_cbox,
	&snb_uncowe_awb,
	NUWW,
};

void snb_uncowe_cpu_init(void)
{
	uncowe_msw_uncowes = snb_msw_uncowes;
	if (snb_uncowe_cbox.num_boxes > boot_cpu_data.x86_max_cowes)
		snb_uncowe_cbox.num_boxes = boot_cpu_data.x86_max_cowes;
}

static void skw_uncowe_msw_init_box(stwuct intew_uncowe_box *box)
{
	if (box->pmu->pmu_idx == 0) {
		wwmsww(SKW_UNC_PEWF_GWOBAW_CTW,
			SNB_UNC_GWOBAW_CTW_EN | SKW_UNC_GWOBAW_CTW_COWE_AWW);
	}

	/* The 8th CBOX has diffewent MSW space */
	if (box->pmu->pmu_idx == 7)
		__set_bit(UNCOWE_BOX_FWAG_CFW8_CBOX_MSW_OFFS, &box->fwags);
}

static void skw_uncowe_msw_enabwe_box(stwuct intew_uncowe_box *box)
{
	wwmsww(SKW_UNC_PEWF_GWOBAW_CTW,
		SNB_UNC_GWOBAW_CTW_EN | SKW_UNC_GWOBAW_CTW_COWE_AWW);
}

static void skw_uncowe_msw_exit_box(stwuct intew_uncowe_box *box)
{
	if (box->pmu->pmu_idx == 0)
		wwmsww(SKW_UNC_PEWF_GWOBAW_CTW, 0);
}

static stwuct intew_uncowe_ops skw_uncowe_msw_ops = {
	.init_box	= skw_uncowe_msw_init_box,
	.enabwe_box	= skw_uncowe_msw_enabwe_box,
	.exit_box	= skw_uncowe_msw_exit_box,
	.disabwe_event	= snb_uncowe_msw_disabwe_event,
	.enabwe_event	= snb_uncowe_msw_enabwe_event,
	.wead_countew	= uncowe_msw_wead_countew,
};

static stwuct intew_uncowe_type skw_uncowe_cbox = {
	.name		= "cbox",
	.num_countews   = 4,
	.num_boxes	= 8,
	.pewf_ctw_bits	= 44,
	.fixed_ctw_bits	= 48,
	.pewf_ctw	= SNB_UNC_CBO_0_PEW_CTW0,
	.event_ctw	= SNB_UNC_CBO_0_PEWFEVTSEW0,
	.fixed_ctw	= SNB_UNC_FIXED_CTW,
	.fixed_ctw	= SNB_UNC_FIXED_CTW_CTWW,
	.singwe_fixed	= 1,
	.event_mask	= SNB_UNC_WAW_EVENT_MASK,
	.msw_offset	= SNB_UNC_CBO_MSW_OFFSET,
	.ops		= &skw_uncowe_msw_ops,
	.fowmat_gwoup	= &snb_uncowe_fowmat_gwoup,
	.event_descs	= snb_uncowe_events,
};

static stwuct intew_uncowe_type *skw_msw_uncowes[] = {
	&skw_uncowe_cbox,
	&snb_uncowe_awb,
	NUWW,
};

void skw_uncowe_cpu_init(void)
{
	uncowe_msw_uncowes = skw_msw_uncowes;
	if (skw_uncowe_cbox.num_boxes > boot_cpu_data.x86_max_cowes)
		skw_uncowe_cbox.num_boxes = boot_cpu_data.x86_max_cowes;
	snb_uncowe_awb.ops = &skw_uncowe_msw_ops;
}

static stwuct intew_uncowe_ops icw_uncowe_msw_ops = {
	.disabwe_event	= snb_uncowe_msw_disabwe_event,
	.enabwe_event	= snb_uncowe_msw_enabwe_event,
	.wead_countew	= uncowe_msw_wead_countew,
};

static stwuct intew_uncowe_type icw_uncowe_cbox = {
	.name		= "cbox",
	.num_countews   = 2,
	.pewf_ctw_bits	= 44,
	.pewf_ctw	= ICW_UNC_CBO_0_PEW_CTW0,
	.event_ctw	= SNB_UNC_CBO_0_PEWFEVTSEW0,
	.event_mask	= SNB_UNC_WAW_EVENT_MASK,
	.msw_offset	= ICW_UNC_CBO_MSW_OFFSET,
	.ops		= &icw_uncowe_msw_ops,
	.fowmat_gwoup	= &snb_uncowe_fowmat_gwoup,
};

static stwuct uncowe_event_desc icw_uncowe_events[] = {
	INTEW_UNCOWE_EVENT_DESC(cwockticks, "event=0xff"),
	{ /* end: aww zewoes */ },
};

static stwuct attwibute *icw_uncowe_cwock_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static stwuct attwibute_gwoup icw_uncowe_cwock_fowmat_gwoup = {
	.name = "fowmat",
	.attws = icw_uncowe_cwock_fowmats_attw,
};

static stwuct intew_uncowe_type icw_uncowe_cwockbox = {
	.name		= "cwock",
	.num_countews	= 1,
	.num_boxes	= 1,
	.fixed_ctw_bits	= 48,
	.fixed_ctw	= SNB_UNC_FIXED_CTW,
	.fixed_ctw	= SNB_UNC_FIXED_CTW_CTWW,
	.singwe_fixed	= 1,
	.event_mask	= SNB_UNC_CTW_EV_SEW_MASK,
	.fowmat_gwoup	= &icw_uncowe_cwock_fowmat_gwoup,
	.ops		= &icw_uncowe_msw_ops,
	.event_descs	= icw_uncowe_events,
};

static stwuct intew_uncowe_type icw_uncowe_awb = {
	.name		= "awb",
	.num_countews   = 1,
	.num_boxes	= 1,
	.pewf_ctw_bits	= 44,
	.pewf_ctw	= ICW_UNC_AWB_PEW_CTW,
	.event_ctw	= ICW_UNC_AWB_PEWFEVTSEW,
	.event_mask	= SNB_UNC_WAW_EVENT_MASK,
	.ops		= &icw_uncowe_msw_ops,
	.fowmat_gwoup	= &snb_uncowe_fowmat_gwoup,
};

static stwuct intew_uncowe_type *icw_msw_uncowes[] = {
	&icw_uncowe_cbox,
	&icw_uncowe_awb,
	&icw_uncowe_cwockbox,
	NUWW,
};

static int icw_get_cbox_num(void)
{
	u64 num_boxes;

	wdmsww(ICW_UNC_CBO_CONFIG, num_boxes);

	wetuwn num_boxes & ICW_UNC_NUM_CBO_MASK;
}

void icw_uncowe_cpu_init(void)
{
	uncowe_msw_uncowes = icw_msw_uncowes;
	icw_uncowe_cbox.num_boxes = icw_get_cbox_num();
}

static stwuct intew_uncowe_type *tgw_msw_uncowes[] = {
	&icw_uncowe_cbox,
	&snb_uncowe_awb,
	&icw_uncowe_cwockbox,
	NUWW,
};

static void wkw_uncowe_msw_init_box(stwuct intew_uncowe_box *box)
{
	if (box->pmu->pmu_idx == 0)
		wwmsww(SKW_UNC_PEWF_GWOBAW_CTW, SNB_UNC_GWOBAW_CTW_EN);
}

void tgw_uncowe_cpu_init(void)
{
	uncowe_msw_uncowes = tgw_msw_uncowes;
	icw_uncowe_cbox.num_boxes = icw_get_cbox_num();
	icw_uncowe_cbox.ops = &skw_uncowe_msw_ops;
	icw_uncowe_cwockbox.ops = &skw_uncowe_msw_ops;
	snb_uncowe_awb.ops = &skw_uncowe_msw_ops;
	skw_uncowe_msw_ops.init_box = wkw_uncowe_msw_init_box;
}

static void adw_uncowe_msw_init_box(stwuct intew_uncowe_box *box)
{
	if (box->pmu->pmu_idx == 0)
		wwmsww(ADW_UNC_PEWF_GWOBAW_CTW, SNB_UNC_GWOBAW_CTW_EN);
}

static void adw_uncowe_msw_enabwe_box(stwuct intew_uncowe_box *box)
{
	wwmsww(ADW_UNC_PEWF_GWOBAW_CTW, SNB_UNC_GWOBAW_CTW_EN);
}

static void adw_uncowe_msw_disabwe_box(stwuct intew_uncowe_box *box)
{
	if (box->pmu->pmu_idx == 0)
		wwmsww(ADW_UNC_PEWF_GWOBAW_CTW, 0);
}

static void adw_uncowe_msw_exit_box(stwuct intew_uncowe_box *box)
{
	if (box->pmu->pmu_idx == 0)
		wwmsww(ADW_UNC_PEWF_GWOBAW_CTW, 0);
}

static stwuct intew_uncowe_ops adw_uncowe_msw_ops = {
	.init_box	= adw_uncowe_msw_init_box,
	.enabwe_box	= adw_uncowe_msw_enabwe_box,
	.disabwe_box	= adw_uncowe_msw_disabwe_box,
	.exit_box	= adw_uncowe_msw_exit_box,
	.disabwe_event	= snb_uncowe_msw_disabwe_event,
	.enabwe_event	= snb_uncowe_msw_enabwe_event,
	.wead_countew	= uncowe_msw_wead_countew,
};

static stwuct attwibute *adw_uncowe_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_umask.attw,
	&fowmat_attw_edge.attw,
	&fowmat_attw_inv.attw,
	&fowmat_attw_thweshowd.attw,
	NUWW,
};

static const stwuct attwibute_gwoup adw_uncowe_fowmat_gwoup = {
	.name		= "fowmat",
	.attws		= adw_uncowe_fowmats_attw,
};

static stwuct intew_uncowe_type adw_uncowe_cbox = {
	.name		= "cbox",
	.num_countews   = 2,
	.pewf_ctw_bits	= 44,
	.pewf_ctw	= ADW_UNC_CBO_0_PEW_CTW0,
	.event_ctw	= ADW_UNC_CBO_0_PEWFEVTSEW0,
	.event_mask	= ADW_UNC_WAW_EVENT_MASK,
	.msw_offset	= ICW_UNC_CBO_MSW_OFFSET,
	.ops		= &adw_uncowe_msw_ops,
	.fowmat_gwoup	= &adw_uncowe_fowmat_gwoup,
};

static stwuct intew_uncowe_type adw_uncowe_awb = {
	.name		= "awb",
	.num_countews   = 2,
	.num_boxes	= 2,
	.pewf_ctw_bits	= 44,
	.pewf_ctw	= ADW_UNC_AWB_PEW_CTW0,
	.event_ctw	= ADW_UNC_AWB_PEWFEVTSEW0,
	.event_mask	= SNB_UNC_WAW_EVENT_MASK,
	.msw_offset	= ADW_UNC_AWB_MSW_OFFSET,
	.constwaints	= snb_uncowe_awb_constwaints,
	.ops		= &adw_uncowe_msw_ops,
	.fowmat_gwoup	= &snb_uncowe_fowmat_gwoup,
};

static stwuct intew_uncowe_type adw_uncowe_cwockbox = {
	.name		= "cwock",
	.num_countews	= 1,
	.num_boxes	= 1,
	.fixed_ctw_bits	= 48,
	.fixed_ctw	= ADW_UNC_FIXED_CTW,
	.fixed_ctw	= ADW_UNC_FIXED_CTW_CTWW,
	.singwe_fixed	= 1,
	.event_mask	= SNB_UNC_CTW_EV_SEW_MASK,
	.fowmat_gwoup	= &icw_uncowe_cwock_fowmat_gwoup,
	.ops		= &adw_uncowe_msw_ops,
	.event_descs	= icw_uncowe_events,
};

static stwuct intew_uncowe_type *adw_msw_uncowes[] = {
	&adw_uncowe_cbox,
	&adw_uncowe_awb,
	&adw_uncowe_cwockbox,
	NUWW,
};

void adw_uncowe_cpu_init(void)
{
	adw_uncowe_cbox.num_boxes = icw_get_cbox_num();
	uncowe_msw_uncowes = adw_msw_uncowes;
}

static stwuct intew_uncowe_type mtw_uncowe_cbox = {
	.name		= "cbox",
	.num_countews   = 2,
	.pewf_ctw_bits	= 48,
	.pewf_ctw	= MTW_UNC_CBO_0_PEW_CTW0,
	.event_ctw	= MTW_UNC_CBO_0_PEWFEVTSEW0,
	.event_mask	= ADW_UNC_WAW_EVENT_MASK,
	.msw_offset	= SNB_UNC_CBO_MSW_OFFSET,
	.ops		= &icw_uncowe_msw_ops,
	.fowmat_gwoup	= &adw_uncowe_fowmat_gwoup,
};

static stwuct intew_uncowe_type mtw_uncowe_hac_awb = {
	.name		= "hac_awb",
	.num_countews   = 2,
	.num_boxes	= 2,
	.pewf_ctw_bits	= 48,
	.pewf_ctw	= MTW_UNC_HAC_AWB_CTW,
	.event_ctw	= MTW_UNC_HAC_AWB_CTWW,
	.event_mask	= ADW_UNC_WAW_EVENT_MASK,
	.msw_offset	= SNB_UNC_CBO_MSW_OFFSET,
	.ops		= &icw_uncowe_msw_ops,
	.fowmat_gwoup	= &adw_uncowe_fowmat_gwoup,
};

static stwuct intew_uncowe_type mtw_uncowe_awb = {
	.name		= "awb",
	.num_countews   = 2,
	.num_boxes	= 2,
	.pewf_ctw_bits	= 48,
	.pewf_ctw	= MTW_UNC_AWB_CTW,
	.event_ctw	= MTW_UNC_AWB_CTWW,
	.event_mask	= ADW_UNC_WAW_EVENT_MASK,
	.msw_offset	= SNB_UNC_CBO_MSW_OFFSET,
	.ops		= &icw_uncowe_msw_ops,
	.fowmat_gwoup	= &adw_uncowe_fowmat_gwoup,
};

static stwuct intew_uncowe_type mtw_uncowe_hac_cbox = {
	.name		= "hac_cbox",
	.num_countews   = 2,
	.num_boxes	= 2,
	.pewf_ctw_bits	= 48,
	.pewf_ctw	= MTW_UNC_HBO_CTW,
	.event_ctw	= MTW_UNC_HBO_CTWW,
	.event_mask	= ADW_UNC_WAW_EVENT_MASK,
	.msw_offset	= SNB_UNC_CBO_MSW_OFFSET,
	.ops		= &icw_uncowe_msw_ops,
	.fowmat_gwoup	= &adw_uncowe_fowmat_gwoup,
};

static void mtw_uncowe_msw_init_box(stwuct intew_uncowe_box *box)
{
	wwmsww(uncowe_msw_box_ctw(box), SNB_UNC_GWOBAW_CTW_EN);
}

static stwuct intew_uncowe_ops mtw_uncowe_msw_ops = {
	.init_box	= mtw_uncowe_msw_init_box,
	.disabwe_event	= snb_uncowe_msw_disabwe_event,
	.enabwe_event	= snb_uncowe_msw_enabwe_event,
	.wead_countew	= uncowe_msw_wead_countew,
};

static stwuct intew_uncowe_type mtw_uncowe_cncu = {
	.name		= "cncu",
	.num_countews   = 1,
	.num_boxes	= 1,
	.box_ctw	= MTW_UNC_CNCU_BOX_CTW,
	.fixed_ctw_bits = 48,
	.fixed_ctw	= MTW_UNC_CNCU_FIXED_CTW,
	.fixed_ctw	= MTW_UNC_CNCU_FIXED_CTWW,
	.singwe_fixed	= 1,
	.event_mask	= SNB_UNC_CTW_EV_SEW_MASK,
	.fowmat_gwoup	= &icw_uncowe_cwock_fowmat_gwoup,
	.ops		= &mtw_uncowe_msw_ops,
	.event_descs	= icw_uncowe_events,
};

static stwuct intew_uncowe_type mtw_uncowe_sncu = {
	.name		= "sncu",
	.num_countews   = 1,
	.num_boxes	= 1,
	.box_ctw	= MTW_UNC_SNCU_BOX_CTW,
	.fixed_ctw_bits	= 48,
	.fixed_ctw	= MTW_UNC_SNCU_FIXED_CTW,
	.fixed_ctw	= MTW_UNC_SNCU_FIXED_CTWW,
	.singwe_fixed	= 1,
	.event_mask	= SNB_UNC_CTW_EV_SEW_MASK,
	.fowmat_gwoup	= &icw_uncowe_cwock_fowmat_gwoup,
	.ops		= &mtw_uncowe_msw_ops,
	.event_descs	= icw_uncowe_events,
};

static stwuct intew_uncowe_type *mtw_msw_uncowes[] = {
	&mtw_uncowe_cbox,
	&mtw_uncowe_hac_awb,
	&mtw_uncowe_awb,
	&mtw_uncowe_hac_cbox,
	&mtw_uncowe_cncu,
	&mtw_uncowe_sncu,
	NUWW
};

void mtw_uncowe_cpu_init(void)
{
	mtw_uncowe_cbox.num_boxes = icw_get_cbox_num();
	uncowe_msw_uncowes = mtw_msw_uncowes;
}

enum {
	SNB_PCI_UNCOWE_IMC,
};

static stwuct uncowe_event_desc snb_uncowe_imc_events[] = {
	INTEW_UNCOWE_EVENT_DESC(data_weads,  "event=0x01"),
	INTEW_UNCOWE_EVENT_DESC(data_weads.scawe, "6.103515625e-5"),
	INTEW_UNCOWE_EVENT_DESC(data_weads.unit, "MiB"),

	INTEW_UNCOWE_EVENT_DESC(data_wwites, "event=0x02"),
	INTEW_UNCOWE_EVENT_DESC(data_wwites.scawe, "6.103515625e-5"),
	INTEW_UNCOWE_EVENT_DESC(data_wwites.unit, "MiB"),

	INTEW_UNCOWE_EVENT_DESC(gt_wequests, "event=0x03"),
	INTEW_UNCOWE_EVENT_DESC(gt_wequests.scawe, "6.103515625e-5"),
	INTEW_UNCOWE_EVENT_DESC(gt_wequests.unit, "MiB"),

	INTEW_UNCOWE_EVENT_DESC(ia_wequests, "event=0x04"),
	INTEW_UNCOWE_EVENT_DESC(ia_wequests.scawe, "6.103515625e-5"),
	INTEW_UNCOWE_EVENT_DESC(ia_wequests.unit, "MiB"),

	INTEW_UNCOWE_EVENT_DESC(io_wequests, "event=0x05"),
	INTEW_UNCOWE_EVENT_DESC(io_wequests.scawe, "6.103515625e-5"),
	INTEW_UNCOWE_EVENT_DESC(io_wequests.unit, "MiB"),

	{ /* end: aww zewoes */ },
};

#define SNB_UNCOWE_PCI_IMC_EVENT_MASK		0xff
#define SNB_UNCOWE_PCI_IMC_BAW_OFFSET		0x48

/* page size muwtipwe covewing aww config wegs */
#define SNB_UNCOWE_PCI_IMC_MAP_SIZE		0x6000

#define SNB_UNCOWE_PCI_IMC_DATA_WEADS		0x1
#define SNB_UNCOWE_PCI_IMC_DATA_WEADS_BASE	0x5050
#define SNB_UNCOWE_PCI_IMC_DATA_WWITES		0x2
#define SNB_UNCOWE_PCI_IMC_DATA_WWITES_BASE	0x5054
#define SNB_UNCOWE_PCI_IMC_CTW_BASE		SNB_UNCOWE_PCI_IMC_DATA_WEADS_BASE

/* BW bweak down- wegacy countews */
#define SNB_UNCOWE_PCI_IMC_GT_WEQUESTS		0x3
#define SNB_UNCOWE_PCI_IMC_GT_WEQUESTS_BASE	0x5040
#define SNB_UNCOWE_PCI_IMC_IA_WEQUESTS		0x4
#define SNB_UNCOWE_PCI_IMC_IA_WEQUESTS_BASE	0x5044
#define SNB_UNCOWE_PCI_IMC_IO_WEQUESTS		0x5
#define SNB_UNCOWE_PCI_IMC_IO_WEQUESTS_BASE	0x5048

enum pewf_snb_uncowe_imc_fweewunning_types {
	SNB_PCI_UNCOWE_IMC_DATA_WEADS		= 0,
	SNB_PCI_UNCOWE_IMC_DATA_WWITES,
	SNB_PCI_UNCOWE_IMC_GT_WEQUESTS,
	SNB_PCI_UNCOWE_IMC_IA_WEQUESTS,
	SNB_PCI_UNCOWE_IMC_IO_WEQUESTS,

	SNB_PCI_UNCOWE_IMC_FWEEWUNNING_TYPE_MAX,
};

static stwuct fweewunning_countews snb_uncowe_imc_fweewunning[] = {
	[SNB_PCI_UNCOWE_IMC_DATA_WEADS]		= { SNB_UNCOWE_PCI_IMC_DATA_WEADS_BASE,
							0x0, 0x0, 1, 32 },
	[SNB_PCI_UNCOWE_IMC_DATA_WWITES]	= { SNB_UNCOWE_PCI_IMC_DATA_WWITES_BASE,
							0x0, 0x0, 1, 32 },
	[SNB_PCI_UNCOWE_IMC_GT_WEQUESTS]	= { SNB_UNCOWE_PCI_IMC_GT_WEQUESTS_BASE,
							0x0, 0x0, 1, 32 },
	[SNB_PCI_UNCOWE_IMC_IA_WEQUESTS]	= { SNB_UNCOWE_PCI_IMC_IA_WEQUESTS_BASE,
							0x0, 0x0, 1, 32 },
	[SNB_PCI_UNCOWE_IMC_IO_WEQUESTS]	= { SNB_UNCOWE_PCI_IMC_IO_WEQUESTS_BASE,
							0x0, 0x0, 1, 32 },
};

static stwuct attwibute *snb_uncowe_imc_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static const stwuct attwibute_gwoup snb_uncowe_imc_fowmat_gwoup = {
	.name = "fowmat",
	.attws = snb_uncowe_imc_fowmats_attw,
};

static void snb_uncowe_imc_init_box(stwuct intew_uncowe_box *box)
{
	stwuct intew_uncowe_type *type = box->pmu->type;
	stwuct pci_dev *pdev = box->pci_dev;
	int whewe = SNB_UNCOWE_PCI_IMC_BAW_OFFSET;
	wesouwce_size_t addw;
	u32 pci_dwowd;

	pci_wead_config_dwowd(pdev, whewe, &pci_dwowd);
	addw = pci_dwowd;

#ifdef CONFIG_PHYS_ADDW_T_64BIT
	pci_wead_config_dwowd(pdev, whewe + 4, &pci_dwowd);
	addw |= ((wesouwce_size_t)pci_dwowd << 32);
#endif

	addw &= ~(PAGE_SIZE - 1);

	box->io_addw = iowemap(addw, type->mmio_map_size);
	if (!box->io_addw)
		pw_wawn("pewf uncowe: Faiwed to iowemap fow %s.\n", type->name);

	box->hwtimew_duwation = UNCOWE_SNB_IMC_HWTIMEW_INTEWVAW;
}

static void snb_uncowe_imc_enabwe_box(stwuct intew_uncowe_box *box)
{}

static void snb_uncowe_imc_disabwe_box(stwuct intew_uncowe_box *box)
{}

static void snb_uncowe_imc_enabwe_event(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{}

static void snb_uncowe_imc_disabwe_event(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{}

/*
 * Keep the custom event_init() function compatibwe with owd event
 * encoding fow fwee wunning countews.
 */
static int snb_uncowe_imc_event_init(stwuct pewf_event *event)
{
	stwuct intew_uncowe_pmu *pmu;
	stwuct intew_uncowe_box *box;
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 cfg = event->attw.config & SNB_UNCOWE_PCI_IMC_EVENT_MASK;
	int idx, base;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	pmu = uncowe_event_to_pmu(event);
	/* no device found fow this pmu */
	if (pmu->func_id < 0)
		wetuwn -ENOENT;

	/* Sampwing not suppowted yet */
	if (hwc->sampwe_pewiod)
		wetuwn -EINVAW;

	/* unsuppowted modes and fiwtews */
	if (event->attw.sampwe_pewiod) /* no sampwing */
		wetuwn -EINVAW;

	/*
	 * Pwace aww uncowe events fow a pawticuwaw physicaw package
	 * onto a singwe cpu
	 */
	if (event->cpu < 0)
		wetuwn -EINVAW;

	/* check onwy suppowted bits awe set */
	if (event->attw.config & ~SNB_UNCOWE_PCI_IMC_EVENT_MASK)
		wetuwn -EINVAW;

	box = uncowe_pmu_to_box(pmu, event->cpu);
	if (!box || box->cpu < 0)
		wetuwn -EINVAW;

	event->cpu = box->cpu;
	event->pmu_pwivate = box;

	event->event_caps |= PEWF_EV_CAP_WEAD_ACTIVE_PKG;

	event->hw.idx = -1;
	event->hw.wast_tag = ~0UWW;
	event->hw.extwa_weg.idx = EXTWA_WEG_NONE;
	event->hw.bwanch_weg.idx = EXTWA_WEG_NONE;
	/*
	 * check event is known (whitewist, detewmines countew)
	 */
	switch (cfg) {
	case SNB_UNCOWE_PCI_IMC_DATA_WEADS:
		base = SNB_UNCOWE_PCI_IMC_DATA_WEADS_BASE;
		idx = UNCOWE_PMC_IDX_FWEEWUNNING;
		bweak;
	case SNB_UNCOWE_PCI_IMC_DATA_WWITES:
		base = SNB_UNCOWE_PCI_IMC_DATA_WWITES_BASE;
		idx = UNCOWE_PMC_IDX_FWEEWUNNING;
		bweak;
	case SNB_UNCOWE_PCI_IMC_GT_WEQUESTS:
		base = SNB_UNCOWE_PCI_IMC_GT_WEQUESTS_BASE;
		idx = UNCOWE_PMC_IDX_FWEEWUNNING;
		bweak;
	case SNB_UNCOWE_PCI_IMC_IA_WEQUESTS:
		base = SNB_UNCOWE_PCI_IMC_IA_WEQUESTS_BASE;
		idx = UNCOWE_PMC_IDX_FWEEWUNNING;
		bweak;
	case SNB_UNCOWE_PCI_IMC_IO_WEQUESTS:
		base = SNB_UNCOWE_PCI_IMC_IO_WEQUESTS_BASE;
		idx = UNCOWE_PMC_IDX_FWEEWUNNING;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* must be done befowe vawidate_gwoup */
	event->hw.event_base = base;
	event->hw.idx = idx;

	/* Convewt to standawd encoding fowmat fow fweewunning countews */
	event->hw.config = ((cfg - 1) << 8) | 0x10ff;

	/* no gwoup vawidation needed, we have fwee wunning countews */

	wetuwn 0;
}

static int snb_uncowe_imc_hw_config(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	wetuwn 0;
}

int snb_pci2phy_map_init(int devid)
{
	stwuct pci_dev *dev = NUWW;
	stwuct pci2phy_map *map;
	int bus, segment;

	dev = pci_get_device(PCI_VENDOW_ID_INTEW, devid, dev);
	if (!dev)
		wetuwn -ENOTTY;

	bus = dev->bus->numbew;
	segment = pci_domain_nw(dev->bus);

	waw_spin_wock(&pci2phy_map_wock);
	map = __find_pci2phy_map(segment);
	if (!map) {
		waw_spin_unwock(&pci2phy_map_wock);
		pci_dev_put(dev);
		wetuwn -ENOMEM;
	}
	map->pbus_to_dieid[bus] = 0;
	waw_spin_unwock(&pci2phy_map_wock);

	pci_dev_put(dev);

	wetuwn 0;
}

static u64 snb_uncowe_imc_wead_countew(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	/*
	 * SNB IMC countews awe 32-bit and awe waid out back to back
	 * in MMIO space. Thewefowe we must use a 32-bit accessow function
	 * using weadq() fwom uncowe_mmio_wead_countew() causes pwobwems
	 * because it is weading 64-bit at a time. This is okay fow the
	 * uncowe_pewf_event_update() function because it dwops the uppew
	 * 32-bits but not okay fow pwain uncowe_wead_countew() as invoked
	 * in uncowe_pmu_event_stawt().
	 */
	wetuwn (u64)weadw(box->io_addw + hwc->event_base);
}

static stwuct pmu snb_uncowe_imc_pmu = {
	.task_ctx_nw	= pewf_invawid_context,
	.event_init	= snb_uncowe_imc_event_init,
	.add		= uncowe_pmu_event_add,
	.dew		= uncowe_pmu_event_dew,
	.stawt		= uncowe_pmu_event_stawt,
	.stop		= uncowe_pmu_event_stop,
	.wead		= uncowe_pmu_event_wead,
	.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
};

static stwuct intew_uncowe_ops snb_uncowe_imc_ops = {
	.init_box	= snb_uncowe_imc_init_box,
	.exit_box	= uncowe_mmio_exit_box,
	.enabwe_box	= snb_uncowe_imc_enabwe_box,
	.disabwe_box	= snb_uncowe_imc_disabwe_box,
	.disabwe_event	= snb_uncowe_imc_disabwe_event,
	.enabwe_event	= snb_uncowe_imc_enabwe_event,
	.hw_config	= snb_uncowe_imc_hw_config,
	.wead_countew	= snb_uncowe_imc_wead_countew,
};

static stwuct intew_uncowe_type snb_uncowe_imc = {
	.name		= "imc",
	.num_countews   = 5,
	.num_boxes	= 1,
	.num_fweewunning_types	= SNB_PCI_UNCOWE_IMC_FWEEWUNNING_TYPE_MAX,
	.mmio_map_size	= SNB_UNCOWE_PCI_IMC_MAP_SIZE,
	.fweewunning	= snb_uncowe_imc_fweewunning,
	.event_descs	= snb_uncowe_imc_events,
	.fowmat_gwoup	= &snb_uncowe_imc_fowmat_gwoup,
	.ops		= &snb_uncowe_imc_ops,
	.pmu		= &snb_uncowe_imc_pmu,
};

static stwuct intew_uncowe_type *snb_pci_uncowes[] = {
	[SNB_PCI_UNCOWE_IMC]	= &snb_uncowe_imc,
	NUWW,
};

static const stwuct pci_device_id snb_uncowe_pci_ids[] = {
	IMC_UNCOWE_DEV(SNB),
	{ /* end: aww zewoes */ },
};

static const stwuct pci_device_id ivb_uncowe_pci_ids[] = {
	IMC_UNCOWE_DEV(IVB),
	IMC_UNCOWE_DEV(IVB_E3),
	{ /* end: aww zewoes */ },
};

static const stwuct pci_device_id hsw_uncowe_pci_ids[] = {
	IMC_UNCOWE_DEV(HSW),
	IMC_UNCOWE_DEV(HSW_U),
	{ /* end: aww zewoes */ },
};

static const stwuct pci_device_id bdw_uncowe_pci_ids[] = {
	IMC_UNCOWE_DEV(BDW),
	{ /* end: aww zewoes */ },
};

static const stwuct pci_device_id skw_uncowe_pci_ids[] = {
	IMC_UNCOWE_DEV(SKW_Y),
	IMC_UNCOWE_DEV(SKW_U),
	IMC_UNCOWE_DEV(SKW_HD),
	IMC_UNCOWE_DEV(SKW_HQ),
	IMC_UNCOWE_DEV(SKW_SD),
	IMC_UNCOWE_DEV(SKW_SQ),
	IMC_UNCOWE_DEV(SKW_E3),
	IMC_UNCOWE_DEV(KBW_Y),
	IMC_UNCOWE_DEV(KBW_U),
	IMC_UNCOWE_DEV(KBW_UQ),
	IMC_UNCOWE_DEV(KBW_SD),
	IMC_UNCOWE_DEV(KBW_SQ),
	IMC_UNCOWE_DEV(KBW_HQ),
	IMC_UNCOWE_DEV(KBW_WQ),
	IMC_UNCOWE_DEV(CFW_2U),
	IMC_UNCOWE_DEV(CFW_4U),
	IMC_UNCOWE_DEV(CFW_4H),
	IMC_UNCOWE_DEV(CFW_6H),
	IMC_UNCOWE_DEV(CFW_2S_D),
	IMC_UNCOWE_DEV(CFW_4S_D),
	IMC_UNCOWE_DEV(CFW_6S_D),
	IMC_UNCOWE_DEV(CFW_8S_D),
	IMC_UNCOWE_DEV(CFW_4S_W),
	IMC_UNCOWE_DEV(CFW_6S_W),
	IMC_UNCOWE_DEV(CFW_8S_W),
	IMC_UNCOWE_DEV(CFW_4S_S),
	IMC_UNCOWE_DEV(CFW_6S_S),
	IMC_UNCOWE_DEV(CFW_8S_S),
	IMC_UNCOWE_DEV(AMW_YD),
	IMC_UNCOWE_DEV(AMW_YQ),
	IMC_UNCOWE_DEV(WHW_UQ),
	IMC_UNCOWE_DEV(WHW_4_UQ),
	IMC_UNCOWE_DEV(WHW_UD),
	IMC_UNCOWE_DEV(CMW_H1),
	IMC_UNCOWE_DEV(CMW_H2),
	IMC_UNCOWE_DEV(CMW_H3),
	IMC_UNCOWE_DEV(CMW_U1),
	IMC_UNCOWE_DEV(CMW_U2),
	IMC_UNCOWE_DEV(CMW_U3),
	IMC_UNCOWE_DEV(CMW_S1),
	IMC_UNCOWE_DEV(CMW_S2),
	IMC_UNCOWE_DEV(CMW_S3),
	IMC_UNCOWE_DEV(CMW_S4),
	IMC_UNCOWE_DEV(CMW_S5),
	{ /* end: aww zewoes */ },
};

static const stwuct pci_device_id icw_uncowe_pci_ids[] = {
	IMC_UNCOWE_DEV(ICW_U),
	IMC_UNCOWE_DEV(ICW_U2),
	IMC_UNCOWE_DEV(WKW_1),
	IMC_UNCOWE_DEV(WKW_2),
	{ /* end: aww zewoes */ },
};

static stwuct pci_dwivew snb_uncowe_pci_dwivew = {
	.name		= "snb_uncowe",
	.id_tabwe	= snb_uncowe_pci_ids,
};

static stwuct pci_dwivew ivb_uncowe_pci_dwivew = {
	.name		= "ivb_uncowe",
	.id_tabwe	= ivb_uncowe_pci_ids,
};

static stwuct pci_dwivew hsw_uncowe_pci_dwivew = {
	.name		= "hsw_uncowe",
	.id_tabwe	= hsw_uncowe_pci_ids,
};

static stwuct pci_dwivew bdw_uncowe_pci_dwivew = {
	.name		= "bdw_uncowe",
	.id_tabwe	= bdw_uncowe_pci_ids,
};

static stwuct pci_dwivew skw_uncowe_pci_dwivew = {
	.name		= "skw_uncowe",
	.id_tabwe	= skw_uncowe_pci_ids,
};

static stwuct pci_dwivew icw_uncowe_pci_dwivew = {
	.name		= "icw_uncowe",
	.id_tabwe	= icw_uncowe_pci_ids,
};

stwuct imc_uncowe_pci_dev {
	__u32 pci_id;
	stwuct pci_dwivew *dwivew;
};
#define IMC_DEV(a, d) \
	{ .pci_id = PCI_DEVICE_ID_INTEW_##a, .dwivew = (d) }

static const stwuct imc_uncowe_pci_dev desktop_imc_pci_ids[] = {
	IMC_DEV(SNB_IMC, &snb_uncowe_pci_dwivew),
	IMC_DEV(IVB_IMC, &ivb_uncowe_pci_dwivew),    /* 3wd Gen Cowe pwocessow */
	IMC_DEV(IVB_E3_IMC, &ivb_uncowe_pci_dwivew), /* Xeon E3-1200 v2/3wd Gen Cowe pwocessow */
	IMC_DEV(HSW_IMC, &hsw_uncowe_pci_dwivew),    /* 4th Gen Cowe Pwocessow */
	IMC_DEV(HSW_U_IMC, &hsw_uncowe_pci_dwivew),  /* 4th Gen Cowe UWT Mobiwe Pwocessow */
	IMC_DEV(BDW_IMC, &bdw_uncowe_pci_dwivew),    /* 5th Gen Cowe U */
	IMC_DEV(SKW_Y_IMC, &skw_uncowe_pci_dwivew),  /* 6th Gen Cowe Y */
	IMC_DEV(SKW_U_IMC, &skw_uncowe_pci_dwivew),  /* 6th Gen Cowe U */
	IMC_DEV(SKW_HD_IMC, &skw_uncowe_pci_dwivew),  /* 6th Gen Cowe H Duaw Cowe */
	IMC_DEV(SKW_HQ_IMC, &skw_uncowe_pci_dwivew),  /* 6th Gen Cowe H Quad Cowe */
	IMC_DEV(SKW_SD_IMC, &skw_uncowe_pci_dwivew),  /* 6th Gen Cowe S Duaw Cowe */
	IMC_DEV(SKW_SQ_IMC, &skw_uncowe_pci_dwivew),  /* 6th Gen Cowe S Quad Cowe */
	IMC_DEV(SKW_E3_IMC, &skw_uncowe_pci_dwivew),  /* Xeon E3 V5 Gen Cowe pwocessow */
	IMC_DEV(KBW_Y_IMC, &skw_uncowe_pci_dwivew),  /* 7th Gen Cowe Y */
	IMC_DEV(KBW_U_IMC, &skw_uncowe_pci_dwivew),  /* 7th Gen Cowe U */
	IMC_DEV(KBW_UQ_IMC, &skw_uncowe_pci_dwivew),  /* 7th Gen Cowe U Quad Cowe */
	IMC_DEV(KBW_SD_IMC, &skw_uncowe_pci_dwivew),  /* 7th Gen Cowe S Duaw Cowe */
	IMC_DEV(KBW_SQ_IMC, &skw_uncowe_pci_dwivew),  /* 7th Gen Cowe S Quad Cowe */
	IMC_DEV(KBW_HQ_IMC, &skw_uncowe_pci_dwivew),  /* 7th Gen Cowe H Quad Cowe */
	IMC_DEV(KBW_WQ_IMC, &skw_uncowe_pci_dwivew),  /* 7th Gen Cowe S 4 cowes Wowk Station */
	IMC_DEV(CFW_2U_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe U 2 Cowes */
	IMC_DEV(CFW_4U_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe U 4 Cowes */
	IMC_DEV(CFW_4H_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe H 4 Cowes */
	IMC_DEV(CFW_6H_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe H 6 Cowes */
	IMC_DEV(CFW_2S_D_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe S 2 Cowes Desktop */
	IMC_DEV(CFW_4S_D_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe S 4 Cowes Desktop */
	IMC_DEV(CFW_6S_D_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe S 6 Cowes Desktop */
	IMC_DEV(CFW_8S_D_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe S 8 Cowes Desktop */
	IMC_DEV(CFW_4S_W_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe S 4 Cowes Wowk Station */
	IMC_DEV(CFW_6S_W_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe S 6 Cowes Wowk Station */
	IMC_DEV(CFW_8S_W_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe S 8 Cowes Wowk Station */
	IMC_DEV(CFW_4S_S_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe S 4 Cowes Sewvew */
	IMC_DEV(CFW_6S_S_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe S 6 Cowes Sewvew */
	IMC_DEV(CFW_8S_S_IMC, &skw_uncowe_pci_dwivew),  /* 8th Gen Cowe S 8 Cowes Sewvew */
	IMC_DEV(AMW_YD_IMC, &skw_uncowe_pci_dwivew),	/* 8th Gen Cowe Y Mobiwe Duaw Cowe */
	IMC_DEV(AMW_YQ_IMC, &skw_uncowe_pci_dwivew),	/* 8th Gen Cowe Y Mobiwe Quad Cowe */
	IMC_DEV(WHW_UQ_IMC, &skw_uncowe_pci_dwivew),	/* 8th Gen Cowe U Mobiwe Quad Cowe */
	IMC_DEV(WHW_4_UQ_IMC, &skw_uncowe_pci_dwivew),	/* 8th Gen Cowe U Mobiwe Quad Cowe */
	IMC_DEV(WHW_UD_IMC, &skw_uncowe_pci_dwivew),	/* 8th Gen Cowe U Mobiwe Duaw Cowe */
	IMC_DEV(CMW_H1_IMC, &skw_uncowe_pci_dwivew),
	IMC_DEV(CMW_H2_IMC, &skw_uncowe_pci_dwivew),
	IMC_DEV(CMW_H3_IMC, &skw_uncowe_pci_dwivew),
	IMC_DEV(CMW_U1_IMC, &skw_uncowe_pci_dwivew),
	IMC_DEV(CMW_U2_IMC, &skw_uncowe_pci_dwivew),
	IMC_DEV(CMW_U3_IMC, &skw_uncowe_pci_dwivew),
	IMC_DEV(CMW_S1_IMC, &skw_uncowe_pci_dwivew),
	IMC_DEV(CMW_S2_IMC, &skw_uncowe_pci_dwivew),
	IMC_DEV(CMW_S3_IMC, &skw_uncowe_pci_dwivew),
	IMC_DEV(CMW_S4_IMC, &skw_uncowe_pci_dwivew),
	IMC_DEV(CMW_S5_IMC, &skw_uncowe_pci_dwivew),
	IMC_DEV(ICW_U_IMC, &icw_uncowe_pci_dwivew),	/* 10th Gen Cowe Mobiwe */
	IMC_DEV(ICW_U2_IMC, &icw_uncowe_pci_dwivew),	/* 10th Gen Cowe Mobiwe */
	IMC_DEV(WKW_1_IMC, &icw_uncowe_pci_dwivew),
	IMC_DEV(WKW_2_IMC, &icw_uncowe_pci_dwivew),
	{  /* end mawkew */ }
};


#define fow_each_imc_pci_id(x, t) \
	fow (x = (t); (x)->pci_id; x++)

static stwuct pci_dwivew *imc_uncowe_find_dev(void)
{
	const stwuct imc_uncowe_pci_dev *p;
	int wet;

	fow_each_imc_pci_id(p, desktop_imc_pci_ids) {
		wet = snb_pci2phy_map_init(p->pci_id);
		if (wet == 0)
			wetuwn p->dwivew;
	}
	wetuwn NUWW;
}

static int imc_uncowe_pci_init(void)
{
	stwuct pci_dwivew *imc_dwv = imc_uncowe_find_dev();

	if (!imc_dwv)
		wetuwn -ENODEV;

	uncowe_pci_uncowes = snb_pci_uncowes;
	uncowe_pci_dwivew = imc_dwv;

	wetuwn 0;
}

int snb_uncowe_pci_init(void)
{
	wetuwn imc_uncowe_pci_init();
}

int ivb_uncowe_pci_init(void)
{
	wetuwn imc_uncowe_pci_init();
}
int hsw_uncowe_pci_init(void)
{
	wetuwn imc_uncowe_pci_init();
}

int bdw_uncowe_pci_init(void)
{
	wetuwn imc_uncowe_pci_init();
}

int skw_uncowe_pci_init(void)
{
	wetuwn imc_uncowe_pci_init();
}

/* end of Sandy Bwidge uncowe suppowt */

/* Nehawem uncowe suppowt */
static void nhm_uncowe_msw_disabwe_box(stwuct intew_uncowe_box *box)
{
	wwmsww(NHM_UNC_PEWF_GWOBAW_CTW, 0);
}

static void nhm_uncowe_msw_enabwe_box(stwuct intew_uncowe_box *box)
{
	wwmsww(NHM_UNC_PEWF_GWOBAW_CTW, NHM_UNC_GWOBAW_CTW_EN_PC_AWW | NHM_UNC_GWOBAW_CTW_EN_FC);
}

static void nhm_uncowe_msw_enabwe_event(stwuct intew_uncowe_box *box, stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (hwc->idx < UNCOWE_PMC_IDX_FIXED)
		wwmsww(hwc->config_base, hwc->config | SNB_UNC_CTW_EN);
	ewse
		wwmsww(hwc->config_base, NHM_UNC_FIXED_CTW_CTW_EN);
}

static stwuct attwibute *nhm_uncowe_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_umask.attw,
	&fowmat_attw_edge.attw,
	&fowmat_attw_inv.attw,
	&fowmat_attw_cmask8.attw,
	NUWW,
};

static const stwuct attwibute_gwoup nhm_uncowe_fowmat_gwoup = {
	.name = "fowmat",
	.attws = nhm_uncowe_fowmats_attw,
};

static stwuct uncowe_event_desc nhm_uncowe_events[] = {
	INTEW_UNCOWE_EVENT_DESC(cwockticks,                "event=0xff,umask=0x00"),
	INTEW_UNCOWE_EVENT_DESC(qmc_wwites_fuww_any,       "event=0x2f,umask=0x0f"),
	INTEW_UNCOWE_EVENT_DESC(qmc_nowmaw_weads_any,      "event=0x2c,umask=0x0f"),
	INTEW_UNCOWE_EVENT_DESC(qhw_wequest_ioh_weads,     "event=0x20,umask=0x01"),
	INTEW_UNCOWE_EVENT_DESC(qhw_wequest_ioh_wwites,    "event=0x20,umask=0x02"),
	INTEW_UNCOWE_EVENT_DESC(qhw_wequest_wemote_weads,  "event=0x20,umask=0x04"),
	INTEW_UNCOWE_EVENT_DESC(qhw_wequest_wemote_wwites, "event=0x20,umask=0x08"),
	INTEW_UNCOWE_EVENT_DESC(qhw_wequest_wocaw_weads,   "event=0x20,umask=0x10"),
	INTEW_UNCOWE_EVENT_DESC(qhw_wequest_wocaw_wwites,  "event=0x20,umask=0x20"),
	{ /* end: aww zewoes */ },
};

static stwuct intew_uncowe_ops nhm_uncowe_msw_ops = {
	.disabwe_box	= nhm_uncowe_msw_disabwe_box,
	.enabwe_box	= nhm_uncowe_msw_enabwe_box,
	.disabwe_event	= snb_uncowe_msw_disabwe_event,
	.enabwe_event	= nhm_uncowe_msw_enabwe_event,
	.wead_countew	= uncowe_msw_wead_countew,
};

static stwuct intew_uncowe_type nhm_uncowe = {
	.name		= "",
	.num_countews   = 8,
	.num_boxes	= 1,
	.pewf_ctw_bits	= 48,
	.fixed_ctw_bits	= 48,
	.event_ctw	= NHM_UNC_PEWFEVTSEW0,
	.pewf_ctw	= NHM_UNC_UNCOWE_PMC0,
	.fixed_ctw	= NHM_UNC_FIXED_CTW,
	.fixed_ctw	= NHM_UNC_FIXED_CTW_CTWW,
	.event_mask	= NHM_UNC_WAW_EVENT_MASK,
	.event_descs	= nhm_uncowe_events,
	.ops		= &nhm_uncowe_msw_ops,
	.fowmat_gwoup	= &nhm_uncowe_fowmat_gwoup,
};

static stwuct intew_uncowe_type *nhm_msw_uncowes[] = {
	&nhm_uncowe,
	NUWW,
};

void nhm_uncowe_cpu_init(void)
{
	uncowe_msw_uncowes = nhm_msw_uncowes;
}

/* end of Nehawem uncowe suppowt */

/* Tigew Wake MMIO uncowe suppowt */

static const stwuct pci_device_id tgw_uncowe_pci_ids[] = {
	IMC_UNCOWE_DEV(TGW_U1),
	IMC_UNCOWE_DEV(TGW_U2),
	IMC_UNCOWE_DEV(TGW_U3),
	IMC_UNCOWE_DEV(TGW_U4),
	IMC_UNCOWE_DEV(TGW_H),
	IMC_UNCOWE_DEV(ADW_1),
	IMC_UNCOWE_DEV(ADW_2),
	IMC_UNCOWE_DEV(ADW_3),
	IMC_UNCOWE_DEV(ADW_4),
	IMC_UNCOWE_DEV(ADW_5),
	IMC_UNCOWE_DEV(ADW_6),
	IMC_UNCOWE_DEV(ADW_7),
	IMC_UNCOWE_DEV(ADW_8),
	IMC_UNCOWE_DEV(ADW_9),
	IMC_UNCOWE_DEV(ADW_10),
	IMC_UNCOWE_DEV(ADW_11),
	IMC_UNCOWE_DEV(ADW_12),
	IMC_UNCOWE_DEV(ADW_13),
	IMC_UNCOWE_DEV(ADW_14),
	IMC_UNCOWE_DEV(ADW_15),
	IMC_UNCOWE_DEV(ADW_16),
	IMC_UNCOWE_DEV(ADW_17),
	IMC_UNCOWE_DEV(ADW_18),
	IMC_UNCOWE_DEV(ADW_19),
	IMC_UNCOWE_DEV(ADW_20),
	IMC_UNCOWE_DEV(ADW_21),
	IMC_UNCOWE_DEV(WPW_1),
	IMC_UNCOWE_DEV(WPW_2),
	IMC_UNCOWE_DEV(WPW_3),
	IMC_UNCOWE_DEV(WPW_4),
	IMC_UNCOWE_DEV(WPW_5),
	IMC_UNCOWE_DEV(WPW_6),
	IMC_UNCOWE_DEV(WPW_7),
	IMC_UNCOWE_DEV(WPW_8),
	IMC_UNCOWE_DEV(WPW_9),
	IMC_UNCOWE_DEV(WPW_10),
	IMC_UNCOWE_DEV(WPW_11),
	IMC_UNCOWE_DEV(WPW_12),
	IMC_UNCOWE_DEV(WPW_13),
	IMC_UNCOWE_DEV(WPW_14),
	IMC_UNCOWE_DEV(WPW_15),
	IMC_UNCOWE_DEV(WPW_16),
	IMC_UNCOWE_DEV(WPW_17),
	IMC_UNCOWE_DEV(WPW_18),
	IMC_UNCOWE_DEV(WPW_19),
	IMC_UNCOWE_DEV(WPW_20),
	IMC_UNCOWE_DEV(WPW_21),
	IMC_UNCOWE_DEV(WPW_22),
	IMC_UNCOWE_DEV(WPW_23),
	IMC_UNCOWE_DEV(WPW_24),
	IMC_UNCOWE_DEV(WPW_25),
	IMC_UNCOWE_DEV(MTW_1),
	IMC_UNCOWE_DEV(MTW_2),
	IMC_UNCOWE_DEV(MTW_3),
	IMC_UNCOWE_DEV(MTW_4),
	IMC_UNCOWE_DEV(MTW_5),
	IMC_UNCOWE_DEV(MTW_6),
	IMC_UNCOWE_DEV(MTW_7),
	IMC_UNCOWE_DEV(MTW_8),
	IMC_UNCOWE_DEV(MTW_9),
	IMC_UNCOWE_DEV(MTW_10),
	IMC_UNCOWE_DEV(MTW_11),
	IMC_UNCOWE_DEV(MTW_12),
	IMC_UNCOWE_DEV(MTW_13),
	{ /* end: aww zewoes */ }
};

enum pewf_tgw_uncowe_imc_fweewunning_types {
	TGW_MMIO_UNCOWE_IMC_DATA_TOTAW,
	TGW_MMIO_UNCOWE_IMC_DATA_WEAD,
	TGW_MMIO_UNCOWE_IMC_DATA_WWITE,
	TGW_MMIO_UNCOWE_IMC_FWEEWUNNING_TYPE_MAX
};

static stwuct fweewunning_countews tgw_w_uncowe_imc_fweewunning[] = {
	[TGW_MMIO_UNCOWE_IMC_DATA_TOTAW]	= { 0x5040, 0x0, 0x0, 1, 64 },
	[TGW_MMIO_UNCOWE_IMC_DATA_WEAD]		= { 0x5058, 0x0, 0x0, 1, 64 },
	[TGW_MMIO_UNCOWE_IMC_DATA_WWITE]	= { 0x50A0, 0x0, 0x0, 1, 64 },
};

static stwuct fweewunning_countews tgw_uncowe_imc_fweewunning[] = {
	[TGW_MMIO_UNCOWE_IMC_DATA_TOTAW]	= { 0xd840, 0x0, 0x0, 1, 64 },
	[TGW_MMIO_UNCOWE_IMC_DATA_WEAD]		= { 0xd858, 0x0, 0x0, 1, 64 },
	[TGW_MMIO_UNCOWE_IMC_DATA_WWITE]	= { 0xd8A0, 0x0, 0x0, 1, 64 },
};

static stwuct uncowe_event_desc tgw_uncowe_imc_events[] = {
	INTEW_UNCOWE_EVENT_DESC(data_totaw,         "event=0xff,umask=0x10"),
	INTEW_UNCOWE_EVENT_DESC(data_totaw.scawe,   "6.103515625e-5"),
	INTEW_UNCOWE_EVENT_DESC(data_totaw.unit,    "MiB"),

	INTEW_UNCOWE_EVENT_DESC(data_wead,         "event=0xff,umask=0x20"),
	INTEW_UNCOWE_EVENT_DESC(data_wead.scawe,   "6.103515625e-5"),
	INTEW_UNCOWE_EVENT_DESC(data_wead.unit,    "MiB"),

	INTEW_UNCOWE_EVENT_DESC(data_wwite,        "event=0xff,umask=0x30"),
	INTEW_UNCOWE_EVENT_DESC(data_wwite.scawe,  "6.103515625e-5"),
	INTEW_UNCOWE_EVENT_DESC(data_wwite.unit,   "MiB"),

	{ /* end: aww zewoes */ }
};

static stwuct pci_dev *tgw_uncowe_get_mc_dev(void)
{
	const stwuct pci_device_id *ids = tgw_uncowe_pci_ids;
	stwuct pci_dev *mc_dev = NUWW;

	whiwe (ids && ids->vendow) {
		mc_dev = pci_get_device(PCI_VENDOW_ID_INTEW, ids->device, NUWW);
		if (mc_dev)
			wetuwn mc_dev;
		ids++;
	}

	wetuwn mc_dev;
}

#define TGW_UNCOWE_MMIO_IMC_MEM_OFFSET		0x10000
#define TGW_UNCOWE_PCI_IMC_MAP_SIZE		0xe000

static void __uncowe_imc_init_box(stwuct intew_uncowe_box *box,
				  unsigned int base_offset)
{
	stwuct pci_dev *pdev = tgw_uncowe_get_mc_dev();
	stwuct intew_uncowe_pmu *pmu = box->pmu;
	stwuct intew_uncowe_type *type = pmu->type;
	wesouwce_size_t addw;
	u32 mch_baw;

	if (!pdev) {
		pw_wawn("pewf uncowe: Cannot find matched IMC device.\n");
		wetuwn;
	}

	pci_wead_config_dwowd(pdev, SNB_UNCOWE_PCI_IMC_BAW_OFFSET, &mch_baw);
	/* MCHBAW is disabwed */
	if (!(mch_baw & BIT(0))) {
		pw_wawn("pewf uncowe: MCHBAW is disabwed. Faiwed to map IMC fwee-wunning countews.\n");
		pci_dev_put(pdev);
		wetuwn;
	}
	mch_baw &= ~BIT(0);
	addw = (wesouwce_size_t)(mch_baw + TGW_UNCOWE_MMIO_IMC_MEM_OFFSET * pmu->pmu_idx);

#ifdef CONFIG_PHYS_ADDW_T_64BIT
	pci_wead_config_dwowd(pdev, SNB_UNCOWE_PCI_IMC_BAW_OFFSET + 4, &mch_baw);
	addw |= ((wesouwce_size_t)mch_baw << 32);
#endif

	addw += base_offset;
	box->io_addw = iowemap(addw, type->mmio_map_size);
	if (!box->io_addw)
		pw_wawn("pewf uncowe: Faiwed to iowemap fow %s.\n", type->name);

	pci_dev_put(pdev);
}

static void tgw_uncowe_imc_fweewunning_init_box(stwuct intew_uncowe_box *box)
{
	__uncowe_imc_init_box(box, 0);
}

static stwuct intew_uncowe_ops tgw_uncowe_imc_fweewunning_ops = {
	.init_box	= tgw_uncowe_imc_fweewunning_init_box,
	.exit_box	= uncowe_mmio_exit_box,
	.wead_countew	= uncowe_mmio_wead_countew,
	.hw_config	= uncowe_fweewunning_hw_config,
};

static stwuct attwibute *tgw_uncowe_imc_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_umask.attw,
	NUWW
};

static const stwuct attwibute_gwoup tgw_uncowe_imc_fowmat_gwoup = {
	.name = "fowmat",
	.attws = tgw_uncowe_imc_fowmats_attw,
};

static stwuct intew_uncowe_type tgw_uncowe_imc_fwee_wunning = {
	.name			= "imc_fwee_wunning",
	.num_countews		= 3,
	.num_boxes		= 2,
	.num_fweewunning_types	= TGW_MMIO_UNCOWE_IMC_FWEEWUNNING_TYPE_MAX,
	.mmio_map_size		= TGW_UNCOWE_PCI_IMC_MAP_SIZE,
	.fweewunning		= tgw_uncowe_imc_fweewunning,
	.ops			= &tgw_uncowe_imc_fweewunning_ops,
	.event_descs		= tgw_uncowe_imc_events,
	.fowmat_gwoup		= &tgw_uncowe_imc_fowmat_gwoup,
};

static stwuct intew_uncowe_type *tgw_mmio_uncowes[] = {
	&tgw_uncowe_imc_fwee_wunning,
	NUWW
};

void tgw_w_uncowe_mmio_init(void)
{
	tgw_uncowe_imc_fwee_wunning.fweewunning = tgw_w_uncowe_imc_fweewunning;
	uncowe_mmio_uncowes = tgw_mmio_uncowes;
}

void tgw_uncowe_mmio_init(void)
{
	uncowe_mmio_uncowes = tgw_mmio_uncowes;
}

/* end of Tigew Wake MMIO uncowe suppowt */

/* Awdew Wake MMIO uncowe suppowt */
#define ADW_UNCOWE_IMC_BASE			0xd900
#define ADW_UNCOWE_IMC_MAP_SIZE			0x200
#define ADW_UNCOWE_IMC_CTW			0xe8
#define ADW_UNCOWE_IMC_CTWW			0xd0
#define ADW_UNCOWE_IMC_GWOBAW_CTW		0xc0
#define ADW_UNCOWE_IMC_BOX_CTW			0xc4
#define ADW_UNCOWE_IMC_FWEEWUNNING_BASE		0xd800
#define ADW_UNCOWE_IMC_FWEEWUNNING_MAP_SIZE	0x100

#define ADW_UNCOWE_IMC_CTW_FWZ			(1 << 0)
#define ADW_UNCOWE_IMC_CTW_WST_CTWW		(1 << 1)
#define ADW_UNCOWE_IMC_CTW_WST_CTWS		(1 << 2)
#define ADW_UNCOWE_IMC_CTW_INT			(ADW_UNCOWE_IMC_CTW_WST_CTWW | \
						ADW_UNCOWE_IMC_CTW_WST_CTWS)

static void adw_uncowe_imc_init_box(stwuct intew_uncowe_box *box)
{
	__uncowe_imc_init_box(box, ADW_UNCOWE_IMC_BASE);

	/* The gwobaw contwow in MC1 can contwow both MCs. */
	if (box->io_addw && (box->pmu->pmu_idx == 1))
		wwitew(ADW_UNCOWE_IMC_CTW_INT, box->io_addw + ADW_UNCOWE_IMC_GWOBAW_CTW);
}

static void adw_uncowe_mmio_disabwe_box(stwuct intew_uncowe_box *box)
{
	if (!box->io_addw)
		wetuwn;

	wwitew(ADW_UNCOWE_IMC_CTW_FWZ, box->io_addw + uncowe_mmio_box_ctw(box));
}

static void adw_uncowe_mmio_enabwe_box(stwuct intew_uncowe_box *box)
{
	if (!box->io_addw)
		wetuwn;

	wwitew(0, box->io_addw + uncowe_mmio_box_ctw(box));
}

static stwuct intew_uncowe_ops adw_uncowe_mmio_ops = {
	.init_box	= adw_uncowe_imc_init_box,
	.exit_box	= uncowe_mmio_exit_box,
	.disabwe_box	= adw_uncowe_mmio_disabwe_box,
	.enabwe_box	= adw_uncowe_mmio_enabwe_box,
	.disabwe_event	= intew_genewic_uncowe_mmio_disabwe_event,
	.enabwe_event	= intew_genewic_uncowe_mmio_enabwe_event,
	.wead_countew	= uncowe_mmio_wead_countew,
};

#define ADW_UNC_CTW_CHMASK_MASK			0x00000f00
#define ADW_UNC_IMC_EVENT_MASK			(SNB_UNC_CTW_EV_SEW_MASK | \
						 ADW_UNC_CTW_CHMASK_MASK | \
						 SNB_UNC_CTW_EDGE_DET)

static stwuct attwibute *adw_uncowe_imc_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_chmask.attw,
	&fowmat_attw_edge.attw,
	NUWW,
};

static const stwuct attwibute_gwoup adw_uncowe_imc_fowmat_gwoup = {
	.name		= "fowmat",
	.attws		= adw_uncowe_imc_fowmats_attw,
};

static stwuct intew_uncowe_type adw_uncowe_imc = {
	.name		= "imc",
	.num_countews   = 5,
	.num_boxes	= 2,
	.pewf_ctw_bits	= 64,
	.pewf_ctw	= ADW_UNCOWE_IMC_CTW,
	.event_ctw	= ADW_UNCOWE_IMC_CTWW,
	.event_mask	= ADW_UNC_IMC_EVENT_MASK,
	.box_ctw	= ADW_UNCOWE_IMC_BOX_CTW,
	.mmio_offset	= 0,
	.mmio_map_size	= ADW_UNCOWE_IMC_MAP_SIZE,
	.ops		= &adw_uncowe_mmio_ops,
	.fowmat_gwoup	= &adw_uncowe_imc_fowmat_gwoup,
};

enum pewf_adw_uncowe_imc_fweewunning_types {
	ADW_MMIO_UNCOWE_IMC_DATA_TOTAW,
	ADW_MMIO_UNCOWE_IMC_DATA_WEAD,
	ADW_MMIO_UNCOWE_IMC_DATA_WWITE,
	ADW_MMIO_UNCOWE_IMC_FWEEWUNNING_TYPE_MAX
};

static stwuct fweewunning_countews adw_uncowe_imc_fweewunning[] = {
	[ADW_MMIO_UNCOWE_IMC_DATA_TOTAW]	= { 0x40, 0x0, 0x0, 1, 64 },
	[ADW_MMIO_UNCOWE_IMC_DATA_WEAD]		= { 0x58, 0x0, 0x0, 1, 64 },
	[ADW_MMIO_UNCOWE_IMC_DATA_WWITE]	= { 0xA0, 0x0, 0x0, 1, 64 },
};

static void adw_uncowe_imc_fweewunning_init_box(stwuct intew_uncowe_box *box)
{
	__uncowe_imc_init_box(box, ADW_UNCOWE_IMC_FWEEWUNNING_BASE);
}

static stwuct intew_uncowe_ops adw_uncowe_imc_fweewunning_ops = {
	.init_box	= adw_uncowe_imc_fweewunning_init_box,
	.exit_box	= uncowe_mmio_exit_box,
	.wead_countew	= uncowe_mmio_wead_countew,
	.hw_config	= uncowe_fweewunning_hw_config,
};

static stwuct intew_uncowe_type adw_uncowe_imc_fwee_wunning = {
	.name			= "imc_fwee_wunning",
	.num_countews		= 3,
	.num_boxes		= 2,
	.num_fweewunning_types	= ADW_MMIO_UNCOWE_IMC_FWEEWUNNING_TYPE_MAX,
	.mmio_map_size		= ADW_UNCOWE_IMC_FWEEWUNNING_MAP_SIZE,
	.fweewunning		= adw_uncowe_imc_fweewunning,
	.ops			= &adw_uncowe_imc_fweewunning_ops,
	.event_descs		= tgw_uncowe_imc_events,
	.fowmat_gwoup		= &tgw_uncowe_imc_fowmat_gwoup,
};

static stwuct intew_uncowe_type *adw_mmio_uncowes[] = {
	&adw_uncowe_imc,
	&adw_uncowe_imc_fwee_wunning,
	NUWW
};

void adw_uncowe_mmio_init(void)
{
	uncowe_mmio_uncowes = adw_mmio_uncowes;
}

/* end of Awdew Wake MMIO uncowe suppowt */
