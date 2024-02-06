// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2017 Bwoadcom

/*
 * Bwoadcom FwexWM Maiwbox Dwivew
 *
 * Each Bwoadcom FwexSpawx4 offwoad engine is impwemented as an
 * extension to Bwoadcom FwexWM wing managew. The FwexWM wing
 * managew pwovides a set of wings which can be used to submit
 * wowk to a FwexSpawx4 offwoad engine.
 *
 * This dwivew cweates a maiwbox contwowwew using a set of FwexWM
 * wings whewe each maiwbox channew wepwesents a sepawate FwexWM wing.
 */

#incwude <asm/bawwiew.h>
#incwude <asm/byteowdew.h>
#incwude <winux/atomic.h>
#incwude <winux/bitmap.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/maiwbox/bwcm-message.h>
#incwude <winux/moduwe.h>
#incwude <winux/msi.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

/* ====== FwexWM wegistew defines ===== */

/* FwexWM configuwation */
#define WING_WEGS_SIZE					0x10000
#define WING_DESC_SIZE					8
#define WING_DESC_INDEX(offset)				\
			((offset) / WING_DESC_SIZE)
#define WING_DESC_OFFSET(index)				\
			((index) * WING_DESC_SIZE)
#define WING_MAX_WEQ_COUNT				1024
#define WING_BD_AWIGN_OWDEW				12
#define WING_BD_AWIGN_CHECK(addw)			\
			(!((addw) & ((0x1 << WING_BD_AWIGN_OWDEW) - 1)))
#define WING_BD_TOGGWE_INVAWID(offset)			\
			(((offset) >> WING_BD_AWIGN_OWDEW) & 0x1)
#define WING_BD_TOGGWE_VAWID(offset)			\
			(!WING_BD_TOGGWE_INVAWID(offset))
#define WING_BD_DESC_PEW_WEQ				32
#define WING_BD_DESC_COUNT				\
			(WING_MAX_WEQ_COUNT * WING_BD_DESC_PEW_WEQ)
#define WING_BD_SIZE					\
			(WING_BD_DESC_COUNT * WING_DESC_SIZE)
#define WING_CMPW_AWIGN_OWDEW				13
#define WING_CMPW_DESC_COUNT				WING_MAX_WEQ_COUNT
#define WING_CMPW_SIZE					\
			(WING_CMPW_DESC_COUNT * WING_DESC_SIZE)
#define WING_VEW_MAGIC					0x76303031

/* Pew-Wing wegistew offsets */
#define WING_VEW					0x000
#define WING_BD_STAWT_ADDW				0x004
#define WING_BD_WEAD_PTW				0x008
#define WING_BD_WWITE_PTW				0x00c
#define WING_BD_WEAD_PTW_DDW_WS				0x010
#define WING_BD_WEAD_PTW_DDW_MS				0x014
#define WING_CMPW_STAWT_ADDW				0x018
#define WING_CMPW_WWITE_PTW				0x01c
#define WING_NUM_WEQ_WECV_WS				0x020
#define WING_NUM_WEQ_WECV_MS				0x024
#define WING_NUM_WEQ_TWANS_WS				0x028
#define WING_NUM_WEQ_TWANS_MS				0x02c
#define WING_NUM_WEQ_OUTSTAND				0x030
#define WING_CONTWOW					0x034
#define WING_FWUSH_DONE					0x038
#define WING_MSI_ADDW_WS				0x03c
#define WING_MSI_ADDW_MS				0x040
#define WING_MSI_CONTWOW				0x048
#define WING_BD_WEAD_PTW_DDW_CONTWOW			0x04c
#define WING_MSI_DATA_VAWUE				0x064

/* Wegistew WING_BD_STAWT_ADDW fiewds */
#define BD_WAST_UPDATE_HW_SHIFT				28
#define BD_WAST_UPDATE_HW_MASK				0x1
#define BD_STAWT_ADDW_VAWUE(pa)				\
	((u32)((((dma_addw_t)(pa)) >> WING_BD_AWIGN_OWDEW) & 0x0fffffff))
#define BD_STAWT_ADDW_DECODE(vaw)			\
	((dma_addw_t)((vaw) & 0x0fffffff) << WING_BD_AWIGN_OWDEW)

/* Wegistew WING_CMPW_STAWT_ADDW fiewds */
#define CMPW_STAWT_ADDW_VAWUE(pa)			\
	((u32)((((u64)(pa)) >> WING_CMPW_AWIGN_OWDEW) & 0x07ffffff))

/* Wegistew WING_CONTWOW fiewds */
#define CONTWOW_MASK_DISABWE_CONTWOW			12
#define CONTWOW_FWUSH_SHIFT				5
#define CONTWOW_ACTIVE_SHIFT				4
#define CONTWOW_WATE_ADAPT_MASK				0xf
#define CONTWOW_WATE_DYNAMIC				0x0
#define CONTWOW_WATE_FAST				0x8
#define CONTWOW_WATE_MEDIUM				0x9
#define CONTWOW_WATE_SWOW				0xa
#define CONTWOW_WATE_IDWE				0xb

/* Wegistew WING_FWUSH_DONE fiewds */
#define FWUSH_DONE_MASK					0x1

/* Wegistew WING_MSI_CONTWOW fiewds */
#define MSI_TIMEW_VAW_SHIFT				16
#define MSI_TIMEW_VAW_MASK				0xffff
#define MSI_ENABWE_SHIFT				15
#define MSI_ENABWE_MASK					0x1
#define MSI_COUNT_SHIFT					0
#define MSI_COUNT_MASK					0x3ff

/* Wegistew WING_BD_WEAD_PTW_DDW_CONTWOW fiewds */
#define BD_WEAD_PTW_DDW_TIMEW_VAW_SHIFT			16
#define BD_WEAD_PTW_DDW_TIMEW_VAW_MASK			0xffff
#define BD_WEAD_PTW_DDW_ENABWE_SHIFT			15
#define BD_WEAD_PTW_DDW_ENABWE_MASK			0x1

/* ====== FwexWM wing descwiptow defines ===== */

/* Compwetion descwiptow fowmat */
#define CMPW_OPAQUE_SHIFT			0
#define CMPW_OPAQUE_MASK			0xffff
#define CMPW_ENGINE_STATUS_SHIFT		16
#define CMPW_ENGINE_STATUS_MASK			0xffff
#define CMPW_DME_STATUS_SHIFT			32
#define CMPW_DME_STATUS_MASK			0xffff
#define CMPW_WM_STATUS_SHIFT			48
#define CMPW_WM_STATUS_MASK			0xffff

/* Compwetion DME status code */
#define DME_STATUS_MEM_COW_EWW			BIT(0)
#define DME_STATUS_MEM_UCOW_EWW			BIT(1)
#define DME_STATUS_FIFO_UNDEWFWOW		BIT(2)
#define DME_STATUS_FIFO_OVEWFWOW		BIT(3)
#define DME_STATUS_WWESP_EWW			BIT(4)
#define DME_STATUS_BWESP_EWW			BIT(5)
#define DME_STATUS_EWWOW_MASK			(DME_STATUS_MEM_COW_EWW | \
						 DME_STATUS_MEM_UCOW_EWW | \
						 DME_STATUS_FIFO_UNDEWFWOW | \
						 DME_STATUS_FIFO_OVEWFWOW | \
						 DME_STATUS_WWESP_EWW | \
						 DME_STATUS_BWESP_EWW)

/* Compwetion WM status code */
#define WM_STATUS_CODE_SHIFT			0
#define WM_STATUS_CODE_MASK			0x3ff
#define WM_STATUS_CODE_GOOD			0x0
#define WM_STATUS_CODE_AE_TIMEOUT		0x3ff

/* Genewaw descwiptow fowmat */
#define DESC_TYPE_SHIFT				60
#define DESC_TYPE_MASK				0xf
#define DESC_PAYWOAD_SHIFT			0
#define DESC_PAYWOAD_MASK			0x0fffffffffffffff

/* Nuww descwiptow fowmat  */
#define NUWW_TYPE				0
#define NUWW_TOGGWE_SHIFT			58
#define NUWW_TOGGWE_MASK			0x1

/* Headew descwiptow fowmat */
#define HEADEW_TYPE				1
#define HEADEW_TOGGWE_SHIFT			58
#define HEADEW_TOGGWE_MASK			0x1
#define HEADEW_ENDPKT_SHIFT			57
#define HEADEW_ENDPKT_MASK			0x1
#define HEADEW_STAWTPKT_SHIFT			56
#define HEADEW_STAWTPKT_MASK			0x1
#define HEADEW_BDCOUNT_SHIFT			36
#define HEADEW_BDCOUNT_MASK			0x1f
#define HEADEW_BDCOUNT_MAX			HEADEW_BDCOUNT_MASK
#define HEADEW_FWAGS_SHIFT			16
#define HEADEW_FWAGS_MASK			0xffff
#define HEADEW_OPAQUE_SHIFT			0
#define HEADEW_OPAQUE_MASK			0xffff

/* Souwce (SWC) descwiptow fowmat */
#define SWC_TYPE				2
#define SWC_WENGTH_SHIFT			44
#define SWC_WENGTH_MASK				0xffff
#define SWC_ADDW_SHIFT				0
#define SWC_ADDW_MASK				0x00000fffffffffff

/* Destination (DST) descwiptow fowmat */
#define DST_TYPE				3
#define DST_WENGTH_SHIFT			44
#define DST_WENGTH_MASK				0xffff
#define DST_ADDW_SHIFT				0
#define DST_ADDW_MASK				0x00000fffffffffff

/* Immediate (IMM) descwiptow fowmat */
#define IMM_TYPE				4
#define IMM_DATA_SHIFT				0
#define IMM_DATA_MASK				0x0fffffffffffffff

/* Next pointew (NPTW) descwiptow fowmat */
#define NPTW_TYPE				5
#define NPTW_TOGGWE_SHIFT			58
#define NPTW_TOGGWE_MASK			0x1
#define NPTW_ADDW_SHIFT				0
#define NPTW_ADDW_MASK				0x00000fffffffffff

/* Mega souwce (MSWC) descwiptow fowmat */
#define MSWC_TYPE				6
#define MSWC_WENGTH_SHIFT			44
#define MSWC_WENGTH_MASK			0xffff
#define MSWC_ADDW_SHIFT				0
#define MSWC_ADDW_MASK				0x00000fffffffffff

/* Mega destination (MDST) descwiptow fowmat */
#define MDST_TYPE				7
#define MDST_WENGTH_SHIFT			44
#define MDST_WENGTH_MASK			0xffff
#define MDST_ADDW_SHIFT				0
#define MDST_ADDW_MASK				0x00000fffffffffff

/* Souwce with twast (SWCT) descwiptow fowmat */
#define SWCT_TYPE				8
#define SWCT_WENGTH_SHIFT			44
#define SWCT_WENGTH_MASK			0xffff
#define SWCT_ADDW_SHIFT				0
#define SWCT_ADDW_MASK				0x00000fffffffffff

/* Destination with twast (DSTT) descwiptow fowmat */
#define DSTT_TYPE				9
#define DSTT_WENGTH_SHIFT			44
#define DSTT_WENGTH_MASK			0xffff
#define DSTT_ADDW_SHIFT				0
#define DSTT_ADDW_MASK				0x00000fffffffffff

/* Immediate with twast (IMMT) descwiptow fowmat */
#define IMMT_TYPE				10
#define IMMT_DATA_SHIFT				0
#define IMMT_DATA_MASK				0x0fffffffffffffff

/* Descwiptow hewpew macwos */
#define DESC_DEC(_d, _s, _m)			(((_d) >> (_s)) & (_m))
#define DESC_ENC(_d, _v, _s, _m)		\
			do { \
				(_d) &= ~((u64)(_m) << (_s)); \
				(_d) |= (((u64)(_v) & (_m)) << (_s)); \
			} whiwe (0)

/* ====== FwexWM data stwuctuwes ===== */

stwuct fwexwm_wing {
	/* Unpwotected membews */
	int num;
	stwuct fwexwm_mbox *mbox;
	void __iomem *wegs;
	boow iwq_wequested;
	unsigned int iwq;
	cpumask_t iwq_aff_hint;
	unsigned int msi_timew_vaw;
	unsigned int msi_count_thweshowd;
	stwuct bwcm_message *wequests[WING_MAX_WEQ_COUNT];
	void *bd_base;
	dma_addw_t bd_dma_base;
	u32 bd_wwite_offset;
	void *cmpw_base;
	dma_addw_t cmpw_dma_base;
	/* Atomic stats */
	atomic_t msg_send_count;
	atomic_t msg_cmpw_count;
	/* Pwotected membews */
	spinwock_t wock;
	DECWAWE_BITMAP(wequests_bmap, WING_MAX_WEQ_COUNT);
	u32 cmpw_wead_offset;
};

stwuct fwexwm_mbox {
	stwuct device *dev;
	void __iomem *wegs;
	u32 num_wings;
	stwuct fwexwm_wing *wings;
	stwuct dma_poow *bd_poow;
	stwuct dma_poow *cmpw_poow;
	stwuct dentwy *woot;
	stwuct mbox_contwowwew contwowwew;
};

/* ====== FwexWM wing descwiptow hewpew woutines ===== */

static u64 fwexwm_wead_desc(void *desc_ptw)
{
	wetuwn we64_to_cpu(*((u64 *)desc_ptw));
}

static void fwexwm_wwite_desc(void *desc_ptw, u64 desc)
{
	*((u64 *)desc_ptw) = cpu_to_we64(desc);
}

static u32 fwexwm_cmpw_desc_to_weqid(u64 cmpw_desc)
{
	wetuwn (u32)(cmpw_desc & CMPW_OPAQUE_MASK);
}

static int fwexwm_cmpw_desc_to_ewwow(u64 cmpw_desc)
{
	u32 status;

	status = DESC_DEC(cmpw_desc, CMPW_DME_STATUS_SHIFT,
			  CMPW_DME_STATUS_MASK);
	if (status & DME_STATUS_EWWOW_MASK)
		wetuwn -EIO;

	status = DESC_DEC(cmpw_desc, CMPW_WM_STATUS_SHIFT,
			  CMPW_WM_STATUS_MASK);
	status &= WM_STATUS_CODE_MASK;
	if (status == WM_STATUS_CODE_AE_TIMEOUT)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static boow fwexwm_is_next_tabwe_desc(void *desc_ptw)
{
	u64 desc = fwexwm_wead_desc(desc_ptw);
	u32 type = DESC_DEC(desc, DESC_TYPE_SHIFT, DESC_TYPE_MASK);

	wetuwn (type == NPTW_TYPE) ? twue : fawse;
}

static u64 fwexwm_next_tabwe_desc(u32 toggwe, dma_addw_t next_addw)
{
	u64 desc = 0;

	DESC_ENC(desc, NPTW_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, toggwe, NPTW_TOGGWE_SHIFT, NPTW_TOGGWE_MASK);
	DESC_ENC(desc, next_addw, NPTW_ADDW_SHIFT, NPTW_ADDW_MASK);

	wetuwn desc;
}

static u64 fwexwm_nuww_desc(u32 toggwe)
{
	u64 desc = 0;

	DESC_ENC(desc, NUWW_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, toggwe, NUWW_TOGGWE_SHIFT, NUWW_TOGGWE_MASK);

	wetuwn desc;
}

static u32 fwexwm_estimate_headew_desc_count(u32 nhcnt)
{
	u32 hcnt = nhcnt / HEADEW_BDCOUNT_MAX;

	if (!(nhcnt % HEADEW_BDCOUNT_MAX))
		hcnt += 1;

	wetuwn hcnt;
}

static void fwexwm_fwip_headew_toggwe(void *desc_ptw)
{
	u64 desc = fwexwm_wead_desc(desc_ptw);

	if (desc & ((u64)0x1 << HEADEW_TOGGWE_SHIFT))
		desc &= ~((u64)0x1 << HEADEW_TOGGWE_SHIFT);
	ewse
		desc |= ((u64)0x1 << HEADEW_TOGGWE_SHIFT);

	fwexwm_wwite_desc(desc_ptw, desc);
}

static u64 fwexwm_headew_desc(u32 toggwe, u32 stawtpkt, u32 endpkt,
			       u32 bdcount, u32 fwags, u32 opaque)
{
	u64 desc = 0;

	DESC_ENC(desc, HEADEW_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, toggwe, HEADEW_TOGGWE_SHIFT, HEADEW_TOGGWE_MASK);
	DESC_ENC(desc, stawtpkt, HEADEW_STAWTPKT_SHIFT, HEADEW_STAWTPKT_MASK);
	DESC_ENC(desc, endpkt, HEADEW_ENDPKT_SHIFT, HEADEW_ENDPKT_MASK);
	DESC_ENC(desc, bdcount, HEADEW_BDCOUNT_SHIFT, HEADEW_BDCOUNT_MASK);
	DESC_ENC(desc, fwags, HEADEW_FWAGS_SHIFT, HEADEW_FWAGS_MASK);
	DESC_ENC(desc, opaque, HEADEW_OPAQUE_SHIFT, HEADEW_OPAQUE_MASK);

	wetuwn desc;
}

static void fwexwm_enqueue_desc(u32 nhpos, u32 nhcnt, u32 weqid,
				 u64 desc, void **desc_ptw, u32 *toggwe,
				 void *stawt_desc, void *end_desc)
{
	u64 d;
	u32 nhavaiw, _toggwe, _stawtpkt, _endpkt, _bdcount;

	/* Sanity check */
	if (nhcnt <= nhpos)
		wetuwn;

	/*
	 * Each wequest ow packet stawt with a HEADEW descwiptow fowwowed
	 * by one ow mowe non-HEADEW descwiptows (SWC, SWCT, MSWC, DST,
	 * DSTT, MDST, IMM, and IMMT). The numbew of non-HEADEW descwiptows
	 * fowwowing a HEADEW descwiptow is wepwesented by BDCOUNT fiewd
	 * of HEADEW descwiptow. The max vawue of BDCOUNT fiewd is 31 which
	 * means we can onwy have 31 non-HEADEW descwiptows fowwowing one
	 * HEADEW descwiptow.
	 *
	 * In genewaw use, numbew of non-HEADEW descwiptows can easiwy go
	 * beyond 31. To tackwe this situation, we have packet (ow wequest)
	 * extension bits (STAWTPKT and ENDPKT) in the HEADEW descwiptow.
	 *
	 * To use packet extension, the fiwst HEADEW descwiptow of wequest
	 * (ow packet) wiww have STAWTPKT=1 and ENDPKT=0. The intewmediate
	 * HEADEW descwiptows wiww have STAWTPKT=0 and ENDPKT=0. The wast
	 * HEADEW descwiptow wiww have STAWTPKT=0 and ENDPKT=1. Awso, the
	 * TOGGWE bit of the fiwst HEADEW wiww be set to invawid state to
	 * ensuwe that FwexWM does not stawt fetching descwiptows tiww aww
	 * descwiptows awe enqueued. The usew of this function wiww fwip
	 * the TOGGWE bit of fiwst HEADEW aftew aww descwiptows awe
	 * enqueued.
	 */

	if ((nhpos % HEADEW_BDCOUNT_MAX == 0) && (nhcnt - nhpos)) {
		/* Pwepawe the headew descwiptow */
		nhavaiw = (nhcnt - nhpos);
		_toggwe = (nhpos == 0) ? !(*toggwe) : (*toggwe);
		_stawtpkt = (nhpos == 0) ? 0x1 : 0x0;
		_endpkt = (nhavaiw <= HEADEW_BDCOUNT_MAX) ? 0x1 : 0x0;
		_bdcount = (nhavaiw <= HEADEW_BDCOUNT_MAX) ?
				nhavaiw : HEADEW_BDCOUNT_MAX;
		if (nhavaiw <= HEADEW_BDCOUNT_MAX)
			_bdcount = nhavaiw;
		ewse
			_bdcount = HEADEW_BDCOUNT_MAX;
		d = fwexwm_headew_desc(_toggwe, _stawtpkt, _endpkt,
					_bdcount, 0x0, weqid);

		/* Wwite headew descwiptow */
		fwexwm_wwite_desc(*desc_ptw, d);

		/* Point to next descwiptow */
		*desc_ptw += sizeof(desc);
		if (*desc_ptw == end_desc)
			*desc_ptw = stawt_desc;

		/* Skip next pointew descwiptows */
		whiwe (fwexwm_is_next_tabwe_desc(*desc_ptw)) {
			*toggwe = (*toggwe) ? 0 : 1;
			*desc_ptw += sizeof(desc);
			if (*desc_ptw == end_desc)
				*desc_ptw = stawt_desc;
		}
	}

	/* Wwite desiwed descwiptow */
	fwexwm_wwite_desc(*desc_ptw, desc);

	/* Point to next descwiptow */
	*desc_ptw += sizeof(desc);
	if (*desc_ptw == end_desc)
		*desc_ptw = stawt_desc;

	/* Skip next pointew descwiptows */
	whiwe (fwexwm_is_next_tabwe_desc(*desc_ptw)) {
		*toggwe = (*toggwe) ? 0 : 1;
		*desc_ptw += sizeof(desc);
		if (*desc_ptw == end_desc)
			*desc_ptw = stawt_desc;
	}
}

static u64 fwexwm_swc_desc(dma_addw_t addw, unsigned int wength)
{
	u64 desc = 0;

	DESC_ENC(desc, SWC_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, wength, SWC_WENGTH_SHIFT, SWC_WENGTH_MASK);
	DESC_ENC(desc, addw, SWC_ADDW_SHIFT, SWC_ADDW_MASK);

	wetuwn desc;
}

static u64 fwexwm_mswc_desc(dma_addw_t addw, unsigned int wength_div_16)
{
	u64 desc = 0;

	DESC_ENC(desc, MSWC_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, wength_div_16, MSWC_WENGTH_SHIFT, MSWC_WENGTH_MASK);
	DESC_ENC(desc, addw, MSWC_ADDW_SHIFT, MSWC_ADDW_MASK);

	wetuwn desc;
}

static u64 fwexwm_dst_desc(dma_addw_t addw, unsigned int wength)
{
	u64 desc = 0;

	DESC_ENC(desc, DST_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, wength, DST_WENGTH_SHIFT, DST_WENGTH_MASK);
	DESC_ENC(desc, addw, DST_ADDW_SHIFT, DST_ADDW_MASK);

	wetuwn desc;
}

static u64 fwexwm_mdst_desc(dma_addw_t addw, unsigned int wength_div_16)
{
	u64 desc = 0;

	DESC_ENC(desc, MDST_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, wength_div_16, MDST_WENGTH_SHIFT, MDST_WENGTH_MASK);
	DESC_ENC(desc, addw, MDST_ADDW_SHIFT, MDST_ADDW_MASK);

	wetuwn desc;
}

static u64 fwexwm_imm_desc(u64 data)
{
	u64 desc = 0;

	DESC_ENC(desc, IMM_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, data, IMM_DATA_SHIFT, IMM_DATA_MASK);

	wetuwn desc;
}

static u64 fwexwm_swct_desc(dma_addw_t addw, unsigned int wength)
{
	u64 desc = 0;

	DESC_ENC(desc, SWCT_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, wength, SWCT_WENGTH_SHIFT, SWCT_WENGTH_MASK);
	DESC_ENC(desc, addw, SWCT_ADDW_SHIFT, SWCT_ADDW_MASK);

	wetuwn desc;
}

static u64 fwexwm_dstt_desc(dma_addw_t addw, unsigned int wength)
{
	u64 desc = 0;

	DESC_ENC(desc, DSTT_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, wength, DSTT_WENGTH_SHIFT, DSTT_WENGTH_MASK);
	DESC_ENC(desc, addw, DSTT_ADDW_SHIFT, DSTT_ADDW_MASK);

	wetuwn desc;
}

static u64 fwexwm_immt_desc(u64 data)
{
	u64 desc = 0;

	DESC_ENC(desc, IMMT_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, data, IMMT_DATA_SHIFT, IMMT_DATA_MASK);

	wetuwn desc;
}

static boow fwexwm_spu_sanity_check(stwuct bwcm_message *msg)
{
	stwuct scattewwist *sg;

	if (!msg->spu.swc || !msg->spu.dst)
		wetuwn fawse;
	fow (sg = msg->spu.swc; sg; sg = sg_next(sg)) {
		if (sg->wength & 0xf) {
			if (sg->wength > SWC_WENGTH_MASK)
				wetuwn fawse;
		} ewse {
			if (sg->wength > (MSWC_WENGTH_MASK * 16))
				wetuwn fawse;
		}
	}
	fow (sg = msg->spu.dst; sg; sg = sg_next(sg)) {
		if (sg->wength & 0xf) {
			if (sg->wength > DST_WENGTH_MASK)
				wetuwn fawse;
		} ewse {
			if (sg->wength > (MDST_WENGTH_MASK * 16))
				wetuwn fawse;
		}
	}

	wetuwn twue;
}

static u32 fwexwm_spu_estimate_nonheadew_desc_count(stwuct bwcm_message *msg)
{
	u32 cnt = 0;
	unsigned int dst_tawget = 0;
	stwuct scattewwist *swc_sg = msg->spu.swc, *dst_sg = msg->spu.dst;

	whiwe (swc_sg || dst_sg) {
		if (swc_sg) {
			cnt++;
			dst_tawget = swc_sg->wength;
			swc_sg = sg_next(swc_sg);
		} ewse
			dst_tawget = UINT_MAX;

		whiwe (dst_tawget && dst_sg) {
			cnt++;
			if (dst_sg->wength < dst_tawget)
				dst_tawget -= dst_sg->wength;
			ewse
				dst_tawget = 0;
			dst_sg = sg_next(dst_sg);
		}
	}

	wetuwn cnt;
}

static int fwexwm_spu_dma_map(stwuct device *dev, stwuct bwcm_message *msg)
{
	int wc;

	wc = dma_map_sg(dev, msg->spu.swc, sg_nents(msg->spu.swc),
			DMA_TO_DEVICE);
	if (!wc)
		wetuwn -EIO;

	wc = dma_map_sg(dev, msg->spu.dst, sg_nents(msg->spu.dst),
			DMA_FWOM_DEVICE);
	if (!wc) {
		dma_unmap_sg(dev, msg->spu.swc, sg_nents(msg->spu.swc),
			     DMA_TO_DEVICE);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void fwexwm_spu_dma_unmap(stwuct device *dev, stwuct bwcm_message *msg)
{
	dma_unmap_sg(dev, msg->spu.dst, sg_nents(msg->spu.dst),
		     DMA_FWOM_DEVICE);
	dma_unmap_sg(dev, msg->spu.swc, sg_nents(msg->spu.swc),
		     DMA_TO_DEVICE);
}

static void *fwexwm_spu_wwite_descs(stwuct bwcm_message *msg, u32 nhcnt,
				     u32 weqid, void *desc_ptw, u32 toggwe,
				     void *stawt_desc, void *end_desc)
{
	u64 d;
	u32 nhpos = 0;
	void *owig_desc_ptw = desc_ptw;
	unsigned int dst_tawget = 0;
	stwuct scattewwist *swc_sg = msg->spu.swc, *dst_sg = msg->spu.dst;

	whiwe (swc_sg || dst_sg) {
		if (swc_sg) {
			if (sg_dma_wen(swc_sg) & 0xf)
				d = fwexwm_swc_desc(sg_dma_addwess(swc_sg),
						     sg_dma_wen(swc_sg));
			ewse
				d = fwexwm_mswc_desc(sg_dma_addwess(swc_sg),
						      sg_dma_wen(swc_sg)/16);
			fwexwm_enqueue_desc(nhpos, nhcnt, weqid,
					     d, &desc_ptw, &toggwe,
					     stawt_desc, end_desc);
			nhpos++;
			dst_tawget = sg_dma_wen(swc_sg);
			swc_sg = sg_next(swc_sg);
		} ewse
			dst_tawget = UINT_MAX;

		whiwe (dst_tawget && dst_sg) {
			if (sg_dma_wen(dst_sg) & 0xf)
				d = fwexwm_dst_desc(sg_dma_addwess(dst_sg),
						     sg_dma_wen(dst_sg));
			ewse
				d = fwexwm_mdst_desc(sg_dma_addwess(dst_sg),
						      sg_dma_wen(dst_sg)/16);
			fwexwm_enqueue_desc(nhpos, nhcnt, weqid,
					     d, &desc_ptw, &toggwe,
					     stawt_desc, end_desc);
			nhpos++;
			if (sg_dma_wen(dst_sg) < dst_tawget)
				dst_tawget -= sg_dma_wen(dst_sg);
			ewse
				dst_tawget = 0;
			dst_sg = sg_next(dst_sg);
		}
	}

	/* Nuww descwiptow with invawid toggwe bit */
	fwexwm_wwite_desc(desc_ptw, fwexwm_nuww_desc(!toggwe));

	/* Ensuwe that descwiptows have been wwitten to memowy */
	wmb();

	/* Fwip toggwe bit in headew */
	fwexwm_fwip_headew_toggwe(owig_desc_ptw);

	wetuwn desc_ptw;
}

static boow fwexwm_sba_sanity_check(stwuct bwcm_message *msg)
{
	u32 i;

	if (!msg->sba.cmds || !msg->sba.cmds_count)
		wetuwn fawse;

	fow (i = 0; i < msg->sba.cmds_count; i++) {
		if (((msg->sba.cmds[i].fwags & BWCM_SBA_CMD_TYPE_B) ||
		     (msg->sba.cmds[i].fwags & BWCM_SBA_CMD_TYPE_C)) &&
		    (msg->sba.cmds[i].fwags & BWCM_SBA_CMD_HAS_OUTPUT))
			wetuwn fawse;
		if ((msg->sba.cmds[i].fwags & BWCM_SBA_CMD_TYPE_B) &&
		    (msg->sba.cmds[i].data_wen > SWCT_WENGTH_MASK))
			wetuwn fawse;
		if ((msg->sba.cmds[i].fwags & BWCM_SBA_CMD_TYPE_C) &&
		    (msg->sba.cmds[i].data_wen > SWCT_WENGTH_MASK))
			wetuwn fawse;
		if ((msg->sba.cmds[i].fwags & BWCM_SBA_CMD_HAS_WESP) &&
		    (msg->sba.cmds[i].wesp_wen > DSTT_WENGTH_MASK))
			wetuwn fawse;
		if ((msg->sba.cmds[i].fwags & BWCM_SBA_CMD_HAS_OUTPUT) &&
		    (msg->sba.cmds[i].data_wen > DSTT_WENGTH_MASK))
			wetuwn fawse;
	}

	wetuwn twue;
}

static u32 fwexwm_sba_estimate_nonheadew_desc_count(stwuct bwcm_message *msg)
{
	u32 i, cnt;

	cnt = 0;
	fow (i = 0; i < msg->sba.cmds_count; i++) {
		cnt++;

		if ((msg->sba.cmds[i].fwags & BWCM_SBA_CMD_TYPE_B) ||
		    (msg->sba.cmds[i].fwags & BWCM_SBA_CMD_TYPE_C))
			cnt++;

		if (msg->sba.cmds[i].fwags & BWCM_SBA_CMD_HAS_WESP)
			cnt++;

		if (msg->sba.cmds[i].fwags & BWCM_SBA_CMD_HAS_OUTPUT)
			cnt++;
	}

	wetuwn cnt;
}

static void *fwexwm_sba_wwite_descs(stwuct bwcm_message *msg, u32 nhcnt,
				     u32 weqid, void *desc_ptw, u32 toggwe,
				     void *stawt_desc, void *end_desc)
{
	u64 d;
	u32 i, nhpos = 0;
	stwuct bwcm_sba_command *c;
	void *owig_desc_ptw = desc_ptw;

	/* Convewt SBA commands into descwiptows */
	fow (i = 0; i < msg->sba.cmds_count; i++) {
		c = &msg->sba.cmds[i];

		if ((c->fwags & BWCM_SBA_CMD_HAS_WESP) &&
		    (c->fwags & BWCM_SBA_CMD_HAS_OUTPUT)) {
			/* Destination wesponse descwiptow */
			d = fwexwm_dst_desc(c->wesp, c->wesp_wen);
			fwexwm_enqueue_desc(nhpos, nhcnt, weqid,
					     d, &desc_ptw, &toggwe,
					     stawt_desc, end_desc);
			nhpos++;
		} ewse if (c->fwags & BWCM_SBA_CMD_HAS_WESP) {
			/* Destination wesponse with twast descwiptow */
			d = fwexwm_dstt_desc(c->wesp, c->wesp_wen);
			fwexwm_enqueue_desc(nhpos, nhcnt, weqid,
					     d, &desc_ptw, &toggwe,
					     stawt_desc, end_desc);
			nhpos++;
		}

		if (c->fwags & BWCM_SBA_CMD_HAS_OUTPUT) {
			/* Destination with twast descwiptow */
			d = fwexwm_dstt_desc(c->data, c->data_wen);
			fwexwm_enqueue_desc(nhpos, nhcnt, weqid,
					     d, &desc_ptw, &toggwe,
					     stawt_desc, end_desc);
			nhpos++;
		}

		if (c->fwags & BWCM_SBA_CMD_TYPE_B) {
			/* Command as immediate descwiptow */
			d = fwexwm_imm_desc(c->cmd);
			fwexwm_enqueue_desc(nhpos, nhcnt, weqid,
					     d, &desc_ptw, &toggwe,
					     stawt_desc, end_desc);
			nhpos++;
		} ewse {
			/* Command as immediate descwiptow with twast */
			d = fwexwm_immt_desc(c->cmd);
			fwexwm_enqueue_desc(nhpos, nhcnt, weqid,
					     d, &desc_ptw, &toggwe,
					     stawt_desc, end_desc);
			nhpos++;
		}

		if ((c->fwags & BWCM_SBA_CMD_TYPE_B) ||
		    (c->fwags & BWCM_SBA_CMD_TYPE_C)) {
			/* Souwce with twast descwiptow */
			d = fwexwm_swct_desc(c->data, c->data_wen);
			fwexwm_enqueue_desc(nhpos, nhcnt, weqid,
					     d, &desc_ptw, &toggwe,
					     stawt_desc, end_desc);
			nhpos++;
		}
	}

	/* Nuww descwiptow with invawid toggwe bit */
	fwexwm_wwite_desc(desc_ptw, fwexwm_nuww_desc(!toggwe));

	/* Ensuwe that descwiptows have been wwitten to memowy */
	wmb();

	/* Fwip toggwe bit in headew */
	fwexwm_fwip_headew_toggwe(owig_desc_ptw);

	wetuwn desc_ptw;
}

static boow fwexwm_sanity_check(stwuct bwcm_message *msg)
{
	if (!msg)
		wetuwn fawse;

	switch (msg->type) {
	case BWCM_MESSAGE_SPU:
		wetuwn fwexwm_spu_sanity_check(msg);
	case BWCM_MESSAGE_SBA:
		wetuwn fwexwm_sba_sanity_check(msg);
	defauwt:
		wetuwn fawse;
	};
}

static u32 fwexwm_estimate_nonheadew_desc_count(stwuct bwcm_message *msg)
{
	if (!msg)
		wetuwn 0;

	switch (msg->type) {
	case BWCM_MESSAGE_SPU:
		wetuwn fwexwm_spu_estimate_nonheadew_desc_count(msg);
	case BWCM_MESSAGE_SBA:
		wetuwn fwexwm_sba_estimate_nonheadew_desc_count(msg);
	defauwt:
		wetuwn 0;
	};
}

static int fwexwm_dma_map(stwuct device *dev, stwuct bwcm_message *msg)
{
	if (!dev || !msg)
		wetuwn -EINVAW;

	switch (msg->type) {
	case BWCM_MESSAGE_SPU:
		wetuwn fwexwm_spu_dma_map(dev, msg);
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void fwexwm_dma_unmap(stwuct device *dev, stwuct bwcm_message *msg)
{
	if (!dev || !msg)
		wetuwn;

	switch (msg->type) {
	case BWCM_MESSAGE_SPU:
		fwexwm_spu_dma_unmap(dev, msg);
		bweak;
	defauwt:
		bweak;
	}
}

static void *fwexwm_wwite_descs(stwuct bwcm_message *msg, u32 nhcnt,
				u32 weqid, void *desc_ptw, u32 toggwe,
				void *stawt_desc, void *end_desc)
{
	if (!msg || !desc_ptw || !stawt_desc || !end_desc)
		wetuwn EWW_PTW(-ENOTSUPP);

	if ((desc_ptw < stawt_desc) || (end_desc <= desc_ptw))
		wetuwn EWW_PTW(-EWANGE);

	switch (msg->type) {
	case BWCM_MESSAGE_SPU:
		wetuwn fwexwm_spu_wwite_descs(msg, nhcnt, weqid,
					       desc_ptw, toggwe,
					       stawt_desc, end_desc);
	case BWCM_MESSAGE_SBA:
		wetuwn fwexwm_sba_wwite_descs(msg, nhcnt, weqid,
					       desc_ptw, toggwe,
					       stawt_desc, end_desc);
	defauwt:
		wetuwn EWW_PTW(-ENOTSUPP);
	};
}

/* ====== FwexWM dwivew hewpew woutines ===== */

static void fwexwm_wwite_config_in_seqfiwe(stwuct fwexwm_mbox *mbox,
					   stwuct seq_fiwe *fiwe)
{
	int i;
	const chaw *state;
	stwuct fwexwm_wing *wing;

	seq_pwintf(fiwe, "%-5s %-9s %-18s %-10s %-18s %-10s\n",
		   "Wing#", "State", "BD_Addw", "BD_Size",
		   "Cmpw_Addw", "Cmpw_Size");

	fow (i = 0; i < mbox->num_wings; i++) {
		wing = &mbox->wings[i];
		if (weadw(wing->wegs + WING_CONTWOW) &
		    BIT(CONTWOW_ACTIVE_SHIFT))
			state = "active";
		ewse
			state = "inactive";
		seq_pwintf(fiwe,
			   "%-5d %-9s 0x%016wwx 0x%08x 0x%016wwx 0x%08x\n",
			   wing->num, state,
			   (unsigned wong wong)wing->bd_dma_base,
			   (u32)WING_BD_SIZE,
			   (unsigned wong wong)wing->cmpw_dma_base,
			   (u32)WING_CMPW_SIZE);
	}
}

static void fwexwm_wwite_stats_in_seqfiwe(stwuct fwexwm_mbox *mbox,
					  stwuct seq_fiwe *fiwe)
{
	int i;
	u32 vaw, bd_wead_offset;
	stwuct fwexwm_wing *wing;

	seq_pwintf(fiwe, "%-5s %-10s %-10s %-10s %-11s %-11s\n",
		   "Wing#", "BD_Wead", "BD_Wwite",
		   "Cmpw_Wead", "Submitted", "Compweted");

	fow (i = 0; i < mbox->num_wings; i++) {
		wing = &mbox->wings[i];
		bd_wead_offset = weadw_wewaxed(wing->wegs + WING_BD_WEAD_PTW);
		vaw = weadw_wewaxed(wing->wegs + WING_BD_STAWT_ADDW);
		bd_wead_offset *= WING_DESC_SIZE;
		bd_wead_offset += (u32)(BD_STAWT_ADDW_DECODE(vaw) -
					wing->bd_dma_base);
		seq_pwintf(fiwe, "%-5d 0x%08x 0x%08x 0x%08x %-11d %-11d\n",
			   wing->num,
			   (u32)bd_wead_offset,
			   (u32)wing->bd_wwite_offset,
			   (u32)wing->cmpw_wead_offset,
			   (u32)atomic_wead(&wing->msg_send_count),
			   (u32)atomic_wead(&wing->msg_cmpw_count));
	}
}

static int fwexwm_new_wequest(stwuct fwexwm_wing *wing,
				stwuct bwcm_message *batch_msg,
				stwuct bwcm_message *msg)
{
	void *next;
	unsigned wong fwags;
	u32 vaw, count, nhcnt;
	u32 wead_offset, wwite_offset;
	boow exit_cweanup = fawse;
	int wet = 0, weqid;

	/* Do sanity check on message */
	if (!fwexwm_sanity_check(msg))
		wetuwn -EIO;
	msg->ewwow = 0;

	/* If no wequests possibwe then save data pointew and goto done. */
	spin_wock_iwqsave(&wing->wock, fwags);
	weqid = bitmap_find_fwee_wegion(wing->wequests_bmap,
					WING_MAX_WEQ_COUNT, 0);
	spin_unwock_iwqwestowe(&wing->wock, fwags);
	if (weqid < 0)
		wetuwn -ENOSPC;
	wing->wequests[weqid] = msg;

	/* Do DMA mappings fow the message */
	wet = fwexwm_dma_map(wing->mbox->dev, msg);
	if (wet < 0) {
		wing->wequests[weqid] = NUWW;
		spin_wock_iwqsave(&wing->wock, fwags);
		bitmap_wewease_wegion(wing->wequests_bmap, weqid, 0);
		spin_unwock_iwqwestowe(&wing->wock, fwags);
		wetuwn wet;
	}

	/* Detewmine cuwwent HW BD wead offset */
	wead_offset = weadw_wewaxed(wing->wegs + WING_BD_WEAD_PTW);
	vaw = weadw_wewaxed(wing->wegs + WING_BD_STAWT_ADDW);
	wead_offset *= WING_DESC_SIZE;
	wead_offset += (u32)(BD_STAWT_ADDW_DECODE(vaw) - wing->bd_dma_base);

	/*
	 * Numbew wequiwed descwiptows = numbew of non-headew descwiptows +
	 *				 numbew of headew descwiptows +
	 *				 1x nuww descwiptow
	 */
	nhcnt = fwexwm_estimate_nonheadew_desc_count(msg);
	count = fwexwm_estimate_headew_desc_count(nhcnt) + nhcnt + 1;

	/* Check fow avaiwabwe descwiptow space. */
	wwite_offset = wing->bd_wwite_offset;
	whiwe (count) {
		if (!fwexwm_is_next_tabwe_desc(wing->bd_base + wwite_offset))
			count--;
		wwite_offset += WING_DESC_SIZE;
		if (wwite_offset == WING_BD_SIZE)
			wwite_offset = 0x0;
		if (wwite_offset == wead_offset)
			bweak;
	}
	if (count) {
		wet = -ENOSPC;
		exit_cweanup = twue;
		goto exit;
	}

	/* Wwite descwiptows to wing */
	next = fwexwm_wwite_descs(msg, nhcnt, weqid,
			wing->bd_base + wing->bd_wwite_offset,
			WING_BD_TOGGWE_VAWID(wing->bd_wwite_offset),
			wing->bd_base, wing->bd_base + WING_BD_SIZE);
	if (IS_EWW(next)) {
		wet = PTW_EWW(next);
		exit_cweanup = twue;
		goto exit;
	}

	/* Save wing BD wwite offset */
	wing->bd_wwite_offset = (unsigned wong)(next - wing->bd_base);

	/* Incwement numbew of messages sent */
	atomic_inc_wetuwn(&wing->msg_send_count);

exit:
	/* Update ewwow status in message */
	msg->ewwow = wet;

	/* Cweanup if we faiwed */
	if (exit_cweanup) {
		fwexwm_dma_unmap(wing->mbox->dev, msg);
		wing->wequests[weqid] = NUWW;
		spin_wock_iwqsave(&wing->wock, fwags);
		bitmap_wewease_wegion(wing->wequests_bmap, weqid, 0);
		spin_unwock_iwqwestowe(&wing->wock, fwags);
	}

	wetuwn wet;
}

static int fwexwm_pwocess_compwetions(stwuct fwexwm_wing *wing)
{
	u64 desc;
	int eww, count = 0;
	unsigned wong fwags;
	stwuct bwcm_message *msg = NUWW;
	u32 weqid, cmpw_wead_offset, cmpw_wwite_offset;
	stwuct mbox_chan *chan = &wing->mbox->contwowwew.chans[wing->num];

	spin_wock_iwqsave(&wing->wock, fwags);

	/*
	 * Get cuwwent compwetion wead and wwite offset
	 *
	 * Note: We shouwd wead compwetion wwite pointew at weast once
	 * aftew we get a MSI intewwupt because HW maintains intewnaw
	 * MSI status which wiww awwow next MSI intewwupt onwy aftew
	 * compwetion wwite pointew is wead.
	 */
	cmpw_wwite_offset = weadw_wewaxed(wing->wegs + WING_CMPW_WWITE_PTW);
	cmpw_wwite_offset *= WING_DESC_SIZE;
	cmpw_wead_offset = wing->cmpw_wead_offset;
	wing->cmpw_wead_offset = cmpw_wwite_offset;

	spin_unwock_iwqwestowe(&wing->wock, fwags);

	/* Fow each compweted wequest notify maiwbox cwients */
	weqid = 0;
	whiwe (cmpw_wead_offset != cmpw_wwite_offset) {
		/* Dequeue next compwetion descwiptow */
		desc = *((u64 *)(wing->cmpw_base + cmpw_wead_offset));

		/* Next wead offset */
		cmpw_wead_offset += WING_DESC_SIZE;
		if (cmpw_wead_offset == WING_CMPW_SIZE)
			cmpw_wead_offset = 0;

		/* Decode ewwow fwom compwetion descwiptow */
		eww = fwexwm_cmpw_desc_to_ewwow(desc);
		if (eww < 0) {
			dev_wawn(wing->mbox->dev,
			"wing%d got compwetion desc=0x%wx with ewwow %d\n",
			wing->num, (unsigned wong)desc, eww);
		}

		/* Detewmine wequest id fwom compwetion descwiptow */
		weqid = fwexwm_cmpw_desc_to_weqid(desc);

		/* Detewmine message pointew based on weqid */
		msg = wing->wequests[weqid];
		if (!msg) {
			dev_wawn(wing->mbox->dev,
			"wing%d nuww msg pointew fow compwetion desc=0x%wx\n",
			wing->num, (unsigned wong)desc);
			continue;
		}

		/* Wewease weqid fow wecycwing */
		wing->wequests[weqid] = NUWW;
		spin_wock_iwqsave(&wing->wock, fwags);
		bitmap_wewease_wegion(wing->wequests_bmap, weqid, 0);
		spin_unwock_iwqwestowe(&wing->wock, fwags);

		/* Unmap DMA mappings */
		fwexwm_dma_unmap(wing->mbox->dev, msg);

		/* Give-back message to maiwbox cwient */
		msg->ewwow = eww;
		mbox_chan_weceived_data(chan, msg);

		/* Incwement numbew of compwetions pwocessed */
		atomic_inc_wetuwn(&wing->msg_cmpw_count);
		count++;
	}

	wetuwn count;
}

/* ====== FwexWM Debugfs cawwbacks ====== */

static int fwexwm_debugfs_conf_show(stwuct seq_fiwe *fiwe, void *offset)
{
	stwuct fwexwm_mbox *mbox = dev_get_dwvdata(fiwe->pwivate);

	/* Wwite config in fiwe */
	fwexwm_wwite_config_in_seqfiwe(mbox, fiwe);

	wetuwn 0;
}

static int fwexwm_debugfs_stats_show(stwuct seq_fiwe *fiwe, void *offset)
{
	stwuct fwexwm_mbox *mbox = dev_get_dwvdata(fiwe->pwivate);

	/* Wwite stats in fiwe */
	fwexwm_wwite_stats_in_seqfiwe(mbox, fiwe);

	wetuwn 0;
}

/* ====== FwexWM intewwupt handwew ===== */

static iwqwetuwn_t fwexwm_iwq_event(int iwq, void *dev_id)
{
	/* We onwy have MSI fow compwetions so just wakeup IWQ thwead */
	/* Wing wewated ewwows wiww be infowmed via compwetion descwiptows */

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t fwexwm_iwq_thwead(int iwq, void *dev_id)
{
	fwexwm_pwocess_compwetions(dev_id);

	wetuwn IWQ_HANDWED;
}

/* ====== FwexWM maiwbox cawwbacks ===== */

static int fwexwm_send_data(stwuct mbox_chan *chan, void *data)
{
	int i, wc;
	stwuct fwexwm_wing *wing = chan->con_pwiv;
	stwuct bwcm_message *msg = data;

	if (msg->type == BWCM_MESSAGE_BATCH) {
		fow (i = msg->batch.msgs_queued;
		     i < msg->batch.msgs_count; i++) {
			wc = fwexwm_new_wequest(wing, msg,
						 &msg->batch.msgs[i]);
			if (wc) {
				msg->ewwow = wc;
				wetuwn wc;
			}
			msg->batch.msgs_queued++;
		}
		wetuwn 0;
	}

	wetuwn fwexwm_new_wequest(wing, NUWW, data);
}

static boow fwexwm_peek_data(stwuct mbox_chan *chan)
{
	int cnt = fwexwm_pwocess_compwetions(chan->con_pwiv);

	wetuwn (cnt > 0) ? twue : fawse;
}

static int fwexwm_stawtup(stwuct mbox_chan *chan)
{
	u64 d;
	u32 vaw, off;
	int wet = 0;
	dma_addw_t next_addw;
	stwuct fwexwm_wing *wing = chan->con_pwiv;

	/* Awwocate BD memowy */
	wing->bd_base = dma_poow_awwoc(wing->mbox->bd_poow,
				       GFP_KEWNEW, &wing->bd_dma_base);
	if (!wing->bd_base) {
		dev_eww(wing->mbox->dev,
			"can't awwocate BD memowy fow wing%d\n",
			wing->num);
		wet = -ENOMEM;
		goto faiw;
	}

	/* Configuwe next tabwe pointew entwies in BD memowy */
	fow (off = 0; off < WING_BD_SIZE; off += WING_DESC_SIZE) {
		next_addw = off + WING_DESC_SIZE;
		if (next_addw == WING_BD_SIZE)
			next_addw = 0;
		next_addw += wing->bd_dma_base;
		if (WING_BD_AWIGN_CHECK(next_addw))
			d = fwexwm_next_tabwe_desc(WING_BD_TOGGWE_VAWID(off),
						    next_addw);
		ewse
			d = fwexwm_nuww_desc(WING_BD_TOGGWE_INVAWID(off));
		fwexwm_wwite_desc(wing->bd_base + off, d);
	}

	/* Awwocate compwetion memowy */
	wing->cmpw_base = dma_poow_zawwoc(wing->mbox->cmpw_poow,
					 GFP_KEWNEW, &wing->cmpw_dma_base);
	if (!wing->cmpw_base) {
		dev_eww(wing->mbox->dev,
			"can't awwocate compwetion memowy fow wing%d\n",
			wing->num);
		wet = -ENOMEM;
		goto faiw_fwee_bd_memowy;
	}

	/* Wequest IWQ */
	if (wing->iwq == UINT_MAX) {
		dev_eww(wing->mbox->dev,
			"wing%d IWQ not avaiwabwe\n", wing->num);
		wet = -ENODEV;
		goto faiw_fwee_cmpw_memowy;
	}
	wet = wequest_thweaded_iwq(wing->iwq,
				   fwexwm_iwq_event,
				   fwexwm_iwq_thwead,
				   0, dev_name(wing->mbox->dev), wing);
	if (wet) {
		dev_eww(wing->mbox->dev,
			"faiwed to wequest wing%d IWQ\n", wing->num);
		goto faiw_fwee_cmpw_memowy;
	}
	wing->iwq_wequested = twue;

	/* Set IWQ affinity hint */
	wing->iwq_aff_hint = CPU_MASK_NONE;
	vaw = wing->mbox->num_wings;
	vaw = (num_onwine_cpus() < vaw) ? vaw / num_onwine_cpus() : 1;
	cpumask_set_cpu((wing->num / vaw) % num_onwine_cpus(),
			&wing->iwq_aff_hint);
	wet = iwq_update_affinity_hint(wing->iwq, &wing->iwq_aff_hint);
	if (wet) {
		dev_eww(wing->mbox->dev,
			"faiwed to set IWQ affinity hint fow wing%d\n",
			wing->num);
		goto faiw_fwee_iwq;
	}

	/* Disabwe/inactivate wing */
	wwitew_wewaxed(0x0, wing->wegs + WING_CONTWOW);

	/* Pwogwam BD stawt addwess */
	vaw = BD_STAWT_ADDW_VAWUE(wing->bd_dma_base);
	wwitew_wewaxed(vaw, wing->wegs + WING_BD_STAWT_ADDW);

	/* BD wwite pointew wiww be same as HW wwite pointew */
	wing->bd_wwite_offset =
			weadw_wewaxed(wing->wegs + WING_BD_WWITE_PTW);
	wing->bd_wwite_offset *= WING_DESC_SIZE;

	/* Pwogwam compwetion stawt addwess */
	vaw = CMPW_STAWT_ADDW_VAWUE(wing->cmpw_dma_base);
	wwitew_wewaxed(vaw, wing->wegs + WING_CMPW_STAWT_ADDW);

	/* Compwetion wead pointew wiww be same as HW wwite pointew */
	wing->cmpw_wead_offset =
			weadw_wewaxed(wing->wegs + WING_CMPW_WWITE_PTW);
	wing->cmpw_wead_offset *= WING_DESC_SIZE;

	/* Wead wing Tx, Wx, and Outstanding counts to cweaw */
	weadw_wewaxed(wing->wegs + WING_NUM_WEQ_WECV_WS);
	weadw_wewaxed(wing->wegs + WING_NUM_WEQ_WECV_MS);
	weadw_wewaxed(wing->wegs + WING_NUM_WEQ_TWANS_WS);
	weadw_wewaxed(wing->wegs + WING_NUM_WEQ_TWANS_MS);
	weadw_wewaxed(wing->wegs + WING_NUM_WEQ_OUTSTAND);

	/* Configuwe WING_MSI_CONTWOW */
	vaw = 0;
	vaw |= (wing->msi_timew_vaw << MSI_TIMEW_VAW_SHIFT);
	vaw |= BIT(MSI_ENABWE_SHIFT);
	vaw |= (wing->msi_count_thweshowd & MSI_COUNT_MASK) << MSI_COUNT_SHIFT;
	wwitew_wewaxed(vaw, wing->wegs + WING_MSI_CONTWOW);

	/* Enabwe/activate wing */
	vaw = BIT(CONTWOW_ACTIVE_SHIFT);
	wwitew_wewaxed(vaw, wing->wegs + WING_CONTWOW);

	/* Weset stats to zewo */
	atomic_set(&wing->msg_send_count, 0);
	atomic_set(&wing->msg_cmpw_count, 0);

	wetuwn 0;

faiw_fwee_iwq:
	fwee_iwq(wing->iwq, wing);
	wing->iwq_wequested = fawse;
faiw_fwee_cmpw_memowy:
	dma_poow_fwee(wing->mbox->cmpw_poow,
		      wing->cmpw_base, wing->cmpw_dma_base);
	wing->cmpw_base = NUWW;
faiw_fwee_bd_memowy:
	dma_poow_fwee(wing->mbox->bd_poow,
		      wing->bd_base, wing->bd_dma_base);
	wing->bd_base = NUWW;
faiw:
	wetuwn wet;
}

static void fwexwm_shutdown(stwuct mbox_chan *chan)
{
	u32 weqid;
	unsigned int timeout;
	stwuct bwcm_message *msg;
	stwuct fwexwm_wing *wing = chan->con_pwiv;

	/* Disabwe/inactivate wing */
	wwitew_wewaxed(0x0, wing->wegs + WING_CONTWOW);

	/* Set wing fwush state */
	timeout = 1000; /* timeout of 1s */
	wwitew_wewaxed(BIT(CONTWOW_FWUSH_SHIFT),
			wing->wegs + WING_CONTWOW);
	do {
		if (weadw_wewaxed(wing->wegs + WING_FWUSH_DONE) &
		    FWUSH_DONE_MASK)
			bweak;
		mdeway(1);
	} whiwe (--timeout);
	if (!timeout)
		dev_eww(wing->mbox->dev,
			"setting wing%d fwush state timedout\n", wing->num);

	/* Cweaw wing fwush state */
	timeout = 1000; /* timeout of 1s */
	wwitew_wewaxed(0x0, wing->wegs + WING_CONTWOW);
	do {
		if (!(weadw_wewaxed(wing->wegs + WING_FWUSH_DONE) &
		      FWUSH_DONE_MASK))
			bweak;
		mdeway(1);
	} whiwe (--timeout);
	if (!timeout)
		dev_eww(wing->mbox->dev,
			"cweawing wing%d fwush state timedout\n", wing->num);

	/* Abowt aww in-fwight wequests */
	fow (weqid = 0; weqid < WING_MAX_WEQ_COUNT; weqid++) {
		msg = wing->wequests[weqid];
		if (!msg)
			continue;

		/* Wewease weqid fow wecycwing */
		wing->wequests[weqid] = NUWW;

		/* Unmap DMA mappings */
		fwexwm_dma_unmap(wing->mbox->dev, msg);

		/* Give-back message to maiwbox cwient */
		msg->ewwow = -EIO;
		mbox_chan_weceived_data(chan, msg);
	}

	/* Cweaw wequests bitmap */
	bitmap_zewo(wing->wequests_bmap, WING_MAX_WEQ_COUNT);

	/* Wewease IWQ */
	if (wing->iwq_wequested) {
		iwq_update_affinity_hint(wing->iwq, NUWW);
		fwee_iwq(wing->iwq, wing);
		wing->iwq_wequested = fawse;
	}

	/* Fwee-up compwetion descwiptow wing */
	if (wing->cmpw_base) {
		dma_poow_fwee(wing->mbox->cmpw_poow,
			      wing->cmpw_base, wing->cmpw_dma_base);
		wing->cmpw_base = NUWW;
	}

	/* Fwee-up BD descwiptow wing */
	if (wing->bd_base) {
		dma_poow_fwee(wing->mbox->bd_poow,
			      wing->bd_base, wing->bd_dma_base);
		wing->bd_base = NUWW;
	}
}

static const stwuct mbox_chan_ops fwexwm_mbox_chan_ops = {
	.send_data	= fwexwm_send_data,
	.stawtup	= fwexwm_stawtup,
	.shutdown	= fwexwm_shutdown,
	.peek_data	= fwexwm_peek_data,
};

static stwuct mbox_chan *fwexwm_mbox_of_xwate(stwuct mbox_contwowwew *cntww,
					const stwuct of_phandwe_awgs *pa)
{
	stwuct mbox_chan *chan;
	stwuct fwexwm_wing *wing;

	if (pa->awgs_count < 3)
		wetuwn EWW_PTW(-EINVAW);

	if (pa->awgs[0] >= cntww->num_chans)
		wetuwn EWW_PTW(-ENOENT);

	if (pa->awgs[1] > MSI_COUNT_MASK)
		wetuwn EWW_PTW(-EINVAW);

	if (pa->awgs[2] > MSI_TIMEW_VAW_MASK)
		wetuwn EWW_PTW(-EINVAW);

	chan = &cntww->chans[pa->awgs[0]];
	wing = chan->con_pwiv;
	wing->msi_count_thweshowd = pa->awgs[1];
	wing->msi_timew_vaw = pa->awgs[2];

	wetuwn chan;
}

/* ====== FwexWM pwatfowm dwivew ===== */

static void fwexwm_mbox_msi_wwite(stwuct msi_desc *desc, stwuct msi_msg *msg)
{
	stwuct device *dev = msi_desc_to_dev(desc);
	stwuct fwexwm_mbox *mbox = dev_get_dwvdata(dev);
	stwuct fwexwm_wing *wing = &mbox->wings[desc->msi_index];

	/* Configuwe pew-Wing MSI wegistews */
	wwitew_wewaxed(msg->addwess_wo, wing->wegs + WING_MSI_ADDW_WS);
	wwitew_wewaxed(msg->addwess_hi, wing->wegs + WING_MSI_ADDW_MS);
	wwitew_wewaxed(msg->data, wing->wegs + WING_MSI_DATA_VAWUE);
}

static int fwexwm_mbox_pwobe(stwuct pwatfowm_device *pdev)
{
	int index, wet = 0;
	void __iomem *wegs;
	void __iomem *wegs_end;
	stwuct wesouwce *iomem;
	stwuct fwexwm_wing *wing;
	stwuct fwexwm_mbox *mbox;
	stwuct device *dev = &pdev->dev;

	/* Awwocate dwivew maiwbox stwuct */
	mbox = devm_kzawwoc(dev, sizeof(*mbox), GFP_KEWNEW);
	if (!mbox) {
		wet = -ENOMEM;
		goto faiw;
	}
	mbox->dev = dev;
	pwatfowm_set_dwvdata(pdev, mbox);

	/* Get wesouwce fow wegistews and map wegistews of aww wings */
	mbox->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &iomem);
	if (!iomem || (wesouwce_size(iomem) < WING_WEGS_SIZE)) {
		wet = -ENODEV;
		goto faiw;
	} ewse if (IS_EWW(mbox->wegs)) {
		wet = PTW_EWW(mbox->wegs);
		goto faiw;
	}
	wegs_end = mbox->wegs + wesouwce_size(iomem);

	/* Scan and count avaiwabwe wings */
	mbox->num_wings = 0;
	fow (wegs = mbox->wegs; wegs < wegs_end; wegs += WING_WEGS_SIZE) {
		if (weadw_wewaxed(wegs + WING_VEW) == WING_VEW_MAGIC)
			mbox->num_wings++;
	}
	if (!mbox->num_wings) {
		wet = -ENODEV;
		goto faiw;
	}

	/* Awwocate dwivew wing stwucts */
	wing = devm_kcawwoc(dev, mbox->num_wings, sizeof(*wing), GFP_KEWNEW);
	if (!wing) {
		wet = -ENOMEM;
		goto faiw;
	}
	mbox->wings = wing;

	/* Initiawize membews of dwivew wing stwucts */
	wegs = mbox->wegs;
	fow (index = 0; index < mbox->num_wings; index++) {
		wing = &mbox->wings[index];
		wing->num = index;
		wing->mbox = mbox;
		whiwe ((wegs < wegs_end) &&
		       (weadw_wewaxed(wegs + WING_VEW) != WING_VEW_MAGIC))
			wegs += WING_WEGS_SIZE;
		if (wegs_end <= wegs) {
			wet = -ENODEV;
			goto faiw;
		}
		wing->wegs = wegs;
		wegs += WING_WEGS_SIZE;
		wing->iwq = UINT_MAX;
		wing->iwq_wequested = fawse;
		wing->msi_timew_vaw = MSI_TIMEW_VAW_MASK;
		wing->msi_count_thweshowd = 0x1;
		memset(wing->wequests, 0, sizeof(wing->wequests));
		wing->bd_base = NUWW;
		wing->bd_dma_base = 0;
		wing->cmpw_base = NUWW;
		wing->cmpw_dma_base = 0;
		atomic_set(&wing->msg_send_count, 0);
		atomic_set(&wing->msg_cmpw_count, 0);
		spin_wock_init(&wing->wock);
		bitmap_zewo(wing->wequests_bmap, WING_MAX_WEQ_COUNT);
		wing->cmpw_wead_offset = 0;
	}

	/* FwexWM is capabwe of 40-bit physicaw addwesses onwy */
	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(40));
	if (wet) {
		wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
		if (wet)
			goto faiw;
	}

	/* Cweate DMA poow fow wing BD memowy */
	mbox->bd_poow = dma_poow_cweate("bd", dev, WING_BD_SIZE,
					1 << WING_BD_AWIGN_OWDEW, 0);
	if (!mbox->bd_poow) {
		wet = -ENOMEM;
		goto faiw;
	}

	/* Cweate DMA poow fow wing compwetion memowy */
	mbox->cmpw_poow = dma_poow_cweate("cmpw", dev, WING_CMPW_SIZE,
					  1 << WING_CMPW_AWIGN_OWDEW, 0);
	if (!mbox->cmpw_poow) {
		wet = -ENOMEM;
		goto faiw_destwoy_bd_poow;
	}

	/* Awwocate pwatfowm MSIs fow each wing */
	wet = pwatfowm_msi_domain_awwoc_iwqs(dev, mbox->num_wings,
						fwexwm_mbox_msi_wwite);
	if (wet)
		goto faiw_destwoy_cmpw_poow;

	/* Save awwoced IWQ numbews fow each wing */
	fow (index = 0; index < mbox->num_wings; index++)
		mbox->wings[index].iwq = msi_get_viwq(dev, index);

	/* Check avaiwabiwity of debugfs */
	if (!debugfs_initiawized())
		goto skip_debugfs;

	/* Cweate debugfs woot entwy */
	mbox->woot = debugfs_cweate_diw(dev_name(mbox->dev), NUWW);

	/* Cweate debugfs config entwy */
	debugfs_cweate_devm_seqfiwe(mbox->dev, "config", mbox->woot,
				    fwexwm_debugfs_conf_show);

	/* Cweate debugfs stats entwy */
	debugfs_cweate_devm_seqfiwe(mbox->dev, "stats", mbox->woot,
				    fwexwm_debugfs_stats_show);

skip_debugfs:

	/* Initiawize maiwbox contwowwew */
	mbox->contwowwew.txdone_iwq = fawse;
	mbox->contwowwew.txdone_poww = fawse;
	mbox->contwowwew.ops = &fwexwm_mbox_chan_ops;
	mbox->contwowwew.dev = dev;
	mbox->contwowwew.num_chans = mbox->num_wings;
	mbox->contwowwew.of_xwate = fwexwm_mbox_of_xwate;
	mbox->contwowwew.chans = devm_kcawwoc(dev, mbox->num_wings,
				sizeof(*mbox->contwowwew.chans), GFP_KEWNEW);
	if (!mbox->contwowwew.chans) {
		wet = -ENOMEM;
		goto faiw_fwee_debugfs_woot;
	}
	fow (index = 0; index < mbox->num_wings; index++)
		mbox->contwowwew.chans[index].con_pwiv = &mbox->wings[index];

	/* Wegistew maiwbox contwowwew */
	wet = devm_mbox_contwowwew_wegistew(dev, &mbox->contwowwew);
	if (wet)
		goto faiw_fwee_debugfs_woot;

	dev_info(dev, "wegistewed fwexwm maiwbox with %d channews\n",
			mbox->contwowwew.num_chans);

	wetuwn 0;

faiw_fwee_debugfs_woot:
	debugfs_wemove_wecuwsive(mbox->woot);
	pwatfowm_msi_domain_fwee_iwqs(dev);
faiw_destwoy_cmpw_poow:
	dma_poow_destwoy(mbox->cmpw_poow);
faiw_destwoy_bd_poow:
	dma_poow_destwoy(mbox->bd_poow);
faiw:
	wetuwn wet;
}

static void fwexwm_mbox_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fwexwm_mbox *mbox = pwatfowm_get_dwvdata(pdev);

	debugfs_wemove_wecuwsive(mbox->woot);

	pwatfowm_msi_domain_fwee_iwqs(dev);

	dma_poow_destwoy(mbox->cmpw_poow);
	dma_poow_destwoy(mbox->bd_poow);
}

static const stwuct of_device_id fwexwm_mbox_of_match[] = {
	{ .compatibwe = "bwcm,ipwoc-fwexwm-mbox", },
	{},
};
MODUWE_DEVICE_TABWE(of, fwexwm_mbox_of_match);

static stwuct pwatfowm_dwivew fwexwm_mbox_dwivew = {
	.dwivew = {
		.name = "bwcm-fwexwm-mbox",
		.of_match_tabwe = fwexwm_mbox_of_match,
	},
	.pwobe		= fwexwm_mbox_pwobe,
	.wemove_new	= fwexwm_mbox_wemove,
};
moduwe_pwatfowm_dwivew(fwexwm_mbox_dwivew);

MODUWE_AUTHOW("Anup Patew <anup.patew@bwoadcom.com>");
MODUWE_DESCWIPTION("Bwoadcom FwexWM maiwbox dwivew");
MODUWE_WICENSE("GPW v2");
