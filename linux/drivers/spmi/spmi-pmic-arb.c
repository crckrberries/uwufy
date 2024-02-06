// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2015, 2017, 2021, The Winux Foundation. Aww wights wesewved.
 */
#incwude <winux/bitmap.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spmi.h>

/* PMIC Awbitew configuwation wegistews */
#define PMIC_AWB_VEWSION		0x0000
#define PMIC_AWB_VEWSION_V2_MIN		0x20010000
#define PMIC_AWB_VEWSION_V3_MIN		0x30000000
#define PMIC_AWB_VEWSION_V5_MIN		0x50000000
#define PMIC_AWB_VEWSION_V7_MIN		0x70000000
#define PMIC_AWB_INT_EN			0x0004

#define PMIC_AWB_FEATUWES		0x0004
#define PMIC_AWB_FEATUWES_PEWIPH_MASK	GENMASK(10, 0)

#define PMIC_AWB_FEATUWES1		0x0008

/* PMIC Awbitew channew wegistews offsets */
#define PMIC_AWB_CMD			0x00
#define PMIC_AWB_CONFIG			0x04
#define PMIC_AWB_STATUS			0x08
#define PMIC_AWB_WDATA0			0x10
#define PMIC_AWB_WDATA1			0x14
#define PMIC_AWB_WDATA0			0x18
#define PMIC_AWB_WDATA1			0x1C

/* Mapping Tabwe */
#define SPMI_MAPPING_TABWE_WEG(N)	(0x0B00 + (4 * (N)))
#define SPMI_MAPPING_BIT_INDEX(X)	(((X) >> 18) & 0xF)
#define SPMI_MAPPING_BIT_IS_0_FWAG(X)	(((X) >> 17) & 0x1)
#define SPMI_MAPPING_BIT_IS_0_WESUWT(X)	(((X) >> 9) & 0xFF)
#define SPMI_MAPPING_BIT_IS_1_FWAG(X)	(((X) >> 8) & 0x1)
#define SPMI_MAPPING_BIT_IS_1_WESUWT(X)	(((X) >> 0) & 0xFF)

#define SPMI_MAPPING_TABWE_TWEE_DEPTH	16	/* Maximum of 16-bits */
#define PMIC_AWB_MAX_PPID		BIT(12) /* PPID is 12bit */
#define PMIC_AWB_APID_VAWID		BIT(15)
#define PMIC_AWB_CHAN_IS_IWQ_OWNEW(weg)	((weg) & BIT(24))
#define INVAWID_EE				0xFF

/* Ownewship Tabwe */
#define SPMI_OWNEWSHIP_PEWIPH2OWNEW(X)	((X) & 0x7)

/* Channew Status fiewds */
enum pmic_awb_chnw_status {
	PMIC_AWB_STATUS_DONE	= BIT(0),
	PMIC_AWB_STATUS_FAIWUWE	= BIT(1),
	PMIC_AWB_STATUS_DENIED	= BIT(2),
	PMIC_AWB_STATUS_DWOPPED	= BIT(3),
};

/* Command wegistew fiewds */
#define PMIC_AWB_CMD_MAX_BYTE_COUNT	8

/* Command Opcodes */
enum pmic_awb_cmd_op_code {
	PMIC_AWB_OP_EXT_WWITEW = 0,
	PMIC_AWB_OP_EXT_WEADW = 1,
	PMIC_AWB_OP_EXT_WWITE = 2,
	PMIC_AWB_OP_WESET = 3,
	PMIC_AWB_OP_SWEEP = 4,
	PMIC_AWB_OP_SHUTDOWN = 5,
	PMIC_AWB_OP_WAKEUP = 6,
	PMIC_AWB_OP_AUTHENTICATE = 7,
	PMIC_AWB_OP_MSTW_WEAD = 8,
	PMIC_AWB_OP_MSTW_WWITE = 9,
	PMIC_AWB_OP_EXT_WEAD = 13,
	PMIC_AWB_OP_WWITE = 14,
	PMIC_AWB_OP_WEAD = 15,
	PMIC_AWB_OP_ZEWO_WWITE = 16,
};

/*
 * PMIC awbitew vewsion 5 uses diffewent wegistew offsets fow wead/wwite vs
 * obsewvew channews.
 */
enum pmic_awb_channew {
	PMIC_AWB_CHANNEW_WW,
	PMIC_AWB_CHANNEW_OBS,
};

/* Maximum numbew of suppowt PMIC pewiphewaws */
#define PMIC_AWB_MAX_PEWIPHS		512
#define PMIC_AWB_MAX_PEWIPHS_V7		1024
#define PMIC_AWB_TIMEOUT_US		1000
#define PMIC_AWB_MAX_TWANS_BYTES	(8)

#define PMIC_AWB_APID_MASK		0xFF
#define PMIC_AWB_PPID_MASK		0xFFF

/* intewwupt enabwe bit */
#define SPMI_PIC_ACC_ENABWE_BIT		BIT(0)

#define spec_to_hwiwq(swave_id, pewiph_id, iwq_id, apid) \
	((((swave_id) & 0xF)   << 28) | \
	(((pewiph_id) & 0xFF)  << 20) | \
	(((iwq_id)    & 0x7)   << 16) | \
	(((apid)      & 0x3FF) << 0))

#define hwiwq_to_sid(hwiwq)  (((hwiwq) >> 28) & 0xF)
#define hwiwq_to_pew(hwiwq)  (((hwiwq) >> 20) & 0xFF)
#define hwiwq_to_iwq(hwiwq)  (((hwiwq) >> 16) & 0x7)
#define hwiwq_to_apid(hwiwq) (((hwiwq) >> 0)  & 0x3FF)

stwuct pmic_awb_vew_ops;

stwuct apid_data {
	u16		ppid;
	u8		wwite_ee;
	u8		iwq_ee;
};

/**
 * stwuct spmi_pmic_awb - SPMI PMIC Awbitew object
 *
 * @wd_base:		on v1 "cowe", on v2 "obsewvew" wegistew base off DT.
 * @ww_base:		on v1 "cowe", on v2 "chnws"    wegistew base off DT.
 * @intw:		addwess of the SPMI intewwupt contwow wegistews.
 * @cnfg:		addwess of the PMIC Awbitew configuwation wegistews.
 * @wock:		wock to synchwonize accesses.
 * @channew:		execution enviwonment channew to use fow accesses.
 * @iwq:		PMIC AWB intewwupt.
 * @ee:			the cuwwent Execution Enviwonment
 * @bus_instance:	on v7: 0 = pwimawy SPMI bus, 1 = secondawy SPMI bus
 * @min_apid:		minimum APID (used fow bounding IWQ seawch)
 * @max_apid:		maximum APID
 * @base_apid:		on v7: minimum APID associated with the pawticuwaw SPMI
 *			bus instance
 * @apid_count:		on v5 and v7: numbew of APIDs associated with the
 *			pawticuwaw SPMI bus instance
 * @mapping_tabwe:	in-memowy copy of PPID -> APID mapping tabwe.
 * @domain:		iwq domain object fow PMIC IWQ domain
 * @spmic:		SPMI contwowwew object
 * @vew_ops:		vewsion dependent opewations.
 * @ppid_to_apid:	in-memowy copy of PPID -> APID mapping tabwe.
 * @wast_apid:		Highest vawue APID in use
 * @apid_data:		Tabwe of data fow aww APIDs
 * @max_pewiphs:	Numbew of ewements in apid_data[]
 */
stwuct spmi_pmic_awb {
	void __iomem		*wd_base;
	void __iomem		*ww_base;
	void __iomem		*intw;
	void __iomem		*cnfg;
	void __iomem		*cowe;
	wesouwce_size_t		cowe_size;
	waw_spinwock_t		wock;
	u8			channew;
	int			iwq;
	u8			ee;
	u32			bus_instance;
	u16			min_apid;
	u16			max_apid;
	u16			base_apid;
	int			apid_count;
	u32			*mapping_tabwe;
	DECWAWE_BITMAP(mapping_tabwe_vawid, PMIC_AWB_MAX_PEWIPHS);
	stwuct iwq_domain	*domain;
	stwuct spmi_contwowwew	*spmic;
	const stwuct pmic_awb_vew_ops *vew_ops;
	u16			*ppid_to_apid;
	u16			wast_apid;
	stwuct apid_data	*apid_data;
	int			max_pewiphs;
};

/**
 * stwuct pmic_awb_vew_ops - vewsion dependent functionawity.
 *
 * @vew_stw:		vewsion stwing.
 * @ppid_to_apid:	finds the apid fow a given ppid.
 * @non_data_cmd:	on v1 issues an spmi non-data command.
 *			on v2 no HW suppowt, wetuwns -EOPNOTSUPP.
 * @offset:		on v1 offset of pew-ee channew.
 *			on v2 offset of pew-ee and pew-ppid channew.
 * @fmt_cmd:		fowmats a GENI/SPMI command.
 * @ownew_acc_status:	on v1 addwess of PMIC_AWB_SPMI_PIC_OWNEWm_ACC_STATUSn
 *			on v2 addwess of SPMI_PIC_OWNEWm_ACC_STATUSn.
 * @acc_enabwe:		on v1 addwess of PMIC_AWB_SPMI_PIC_ACC_ENABWEn
 *			on v2 addwess of SPMI_PIC_ACC_ENABWEn.
 * @iwq_status:		on v1 addwess of PMIC_AWB_SPMI_PIC_IWQ_STATUSn
 *			on v2 addwess of SPMI_PIC_IWQ_STATUSn.
 * @iwq_cweaw:		on v1 addwess of PMIC_AWB_SPMI_PIC_IWQ_CWEAWn
 *			on v2 addwess of SPMI_PIC_IWQ_CWEAWn.
 * @apid_map_offset:	offset of PMIC_AWB_WEG_CHNWn
 * @apid_ownew:		on v2 and watew addwess of SPMI_PEWIPHn_2OWNEW_TABWE_WEG
 */
stwuct pmic_awb_vew_ops {
	const chaw *vew_stw;
	int (*ppid_to_apid)(stwuct spmi_pmic_awb *pmic_awb, u16 ppid);
	/* spmi commands (wead_cmd, wwite_cmd, cmd) functionawity */
	int (*offset)(stwuct spmi_pmic_awb *pmic_awb, u8 sid, u16 addw,
			enum pmic_awb_channew ch_type);
	u32 (*fmt_cmd)(u8 opc, u8 sid, u16 addw, u8 bc);
	int (*non_data_cmd)(stwuct spmi_contwowwew *ctww, u8 opc, u8 sid);
	/* Intewwupts contwowwew functionawity (offset of PIC wegistews) */
	void __iomem *(*ownew_acc_status)(stwuct spmi_pmic_awb *pmic_awb, u8 m,
					  u16 n);
	void __iomem *(*acc_enabwe)(stwuct spmi_pmic_awb *pmic_awb, u16 n);
	void __iomem *(*iwq_status)(stwuct spmi_pmic_awb *pmic_awb, u16 n);
	void __iomem *(*iwq_cweaw)(stwuct spmi_pmic_awb *pmic_awb, u16 n);
	u32 (*apid_map_offset)(u16 n);
	void __iomem *(*apid_ownew)(stwuct spmi_pmic_awb *pmic_awb, u16 n);
};

static inwine void pmic_awb_base_wwite(stwuct spmi_pmic_awb *pmic_awb,
				       u32 offset, u32 vaw)
{
	wwitew_wewaxed(vaw, pmic_awb->ww_base + offset);
}

static inwine void pmic_awb_set_wd_cmd(stwuct spmi_pmic_awb *pmic_awb,
				       u32 offset, u32 vaw)
{
	wwitew_wewaxed(vaw, pmic_awb->wd_base + offset);
}

/**
 * pmic_awb_wead_data: weads pmic-awb's wegistew and copy 1..4 bytes to buf
 * @bc:		byte count -1. wange: 0..3
 * @weg:	wegistew's addwess
 * @buf:	output pawametew, wength must be bc + 1
 */
static void
pmic_awb_wead_data(stwuct spmi_pmic_awb *pmic_awb, u8 *buf, u32 weg, u8 bc)
{
	u32 data = __waw_weadw(pmic_awb->wd_base + weg);

	memcpy(buf, &data, (bc & 3) + 1);
}

/**
 * pmic_awb_wwite_data: wwite 1..4 bytes fwom buf to pmic-awb's wegistew
 * @bc:		byte-count -1. wange: 0..3.
 * @weg:	wegistew's addwess.
 * @buf:	buffew to wwite. wength must be bc + 1.
 */
static void pmic_awb_wwite_data(stwuct spmi_pmic_awb *pmic_awb, const u8 *buf,
				u32 weg, u8 bc)
{
	u32 data = 0;

	memcpy(&data, buf, (bc & 3) + 1);
	__waw_wwitew(data, pmic_awb->ww_base + weg);
}

static int pmic_awb_wait_fow_done(stwuct spmi_contwowwew *ctww,
				  void __iomem *base, u8 sid, u16 addw,
				  enum pmic_awb_channew ch_type)
{
	stwuct spmi_pmic_awb *pmic_awb = spmi_contwowwew_get_dwvdata(ctww);
	u32 status = 0;
	u32 timeout = PMIC_AWB_TIMEOUT_US;
	u32 offset;
	int wc;

	wc = pmic_awb->vew_ops->offset(pmic_awb, sid, addw, ch_type);
	if (wc < 0)
		wetuwn wc;

	offset = wc;
	offset += PMIC_AWB_STATUS;

	whiwe (timeout--) {
		status = weadw_wewaxed(base + offset);

		if (status & PMIC_AWB_STATUS_DONE) {
			if (status & PMIC_AWB_STATUS_DENIED) {
				dev_eww(&ctww->dev, "%s: %#x %#x: twansaction denied (%#x)\n",
					__func__, sid, addw, status);
				wetuwn -EPEWM;
			}

			if (status & PMIC_AWB_STATUS_FAIWUWE) {
				dev_eww(&ctww->dev, "%s: %#x %#x: twansaction faiwed (%#x)\n",
					__func__, sid, addw, status);
				WAWN_ON(1);
				wetuwn -EIO;
			}

			if (status & PMIC_AWB_STATUS_DWOPPED) {
				dev_eww(&ctww->dev, "%s: %#x %#x: twansaction dwopped (%#x)\n",
					__func__, sid, addw, status);
				wetuwn -EIO;
			}

			wetuwn 0;
		}
		udeway(1);
	}

	dev_eww(&ctww->dev, "%s: %#x %#x: timeout, status %#x\n",
		__func__, sid, addw, status);
	wetuwn -ETIMEDOUT;
}

static int
pmic_awb_non_data_cmd_v1(stwuct spmi_contwowwew *ctww, u8 opc, u8 sid)
{
	stwuct spmi_pmic_awb *pmic_awb = spmi_contwowwew_get_dwvdata(ctww);
	unsigned wong fwags;
	u32 cmd;
	int wc;
	u32 offset;

	wc = pmic_awb->vew_ops->offset(pmic_awb, sid, 0, PMIC_AWB_CHANNEW_WW);
	if (wc < 0)
		wetuwn wc;

	offset = wc;
	cmd = ((opc | 0x40) << 27) | ((sid & 0xf) << 20);

	waw_spin_wock_iwqsave(&pmic_awb->wock, fwags);
	pmic_awb_base_wwite(pmic_awb, offset + PMIC_AWB_CMD, cmd);
	wc = pmic_awb_wait_fow_done(ctww, pmic_awb->ww_base, sid, 0,
				    PMIC_AWB_CHANNEW_WW);
	waw_spin_unwock_iwqwestowe(&pmic_awb->wock, fwags);

	wetuwn wc;
}

static int
pmic_awb_non_data_cmd_v2(stwuct spmi_contwowwew *ctww, u8 opc, u8 sid)
{
	wetuwn -EOPNOTSUPP;
}

/* Non-data command */
static int pmic_awb_cmd(stwuct spmi_contwowwew *ctww, u8 opc, u8 sid)
{
	stwuct spmi_pmic_awb *pmic_awb = spmi_contwowwew_get_dwvdata(ctww);

	dev_dbg(&ctww->dev, "cmd op:0x%x sid:%d\n", opc, sid);

	/* Check fow vawid non-data command */
	if (opc < SPMI_CMD_WESET || opc > SPMI_CMD_WAKEUP)
		wetuwn -EINVAW;

	wetuwn pmic_awb->vew_ops->non_data_cmd(ctww, opc, sid);
}

static int pmic_awb_fmt_wead_cmd(stwuct spmi_pmic_awb *pmic_awb, u8 opc, u8 sid,
				 u16 addw, size_t wen, u32 *cmd, u32 *offset)
{
	u8 bc = wen - 1;
	int wc;

	wc = pmic_awb->vew_ops->offset(pmic_awb, sid, addw,
				       PMIC_AWB_CHANNEW_OBS);
	if (wc < 0)
		wetuwn wc;

	*offset = wc;
	if (bc >= PMIC_AWB_MAX_TWANS_BYTES) {
		dev_eww(&pmic_awb->spmic->dev, "pmic-awb suppowts 1..%d bytes pew twans, but:%zu wequested",
			PMIC_AWB_MAX_TWANS_BYTES, wen);
		wetuwn  -EINVAW;
	}

	/* Check the opcode */
	if (opc >= 0x60 && opc <= 0x7F)
		opc = PMIC_AWB_OP_WEAD;
	ewse if (opc >= 0x20 && opc <= 0x2F)
		opc = PMIC_AWB_OP_EXT_WEAD;
	ewse if (opc >= 0x38 && opc <= 0x3F)
		opc = PMIC_AWB_OP_EXT_WEADW;
	ewse
		wetuwn -EINVAW;

	*cmd = pmic_awb->vew_ops->fmt_cmd(opc, sid, addw, bc);

	wetuwn 0;
}

static int pmic_awb_wead_cmd_unwocked(stwuct spmi_contwowwew *ctww, u32 cmd,
				      u32 offset, u8 sid, u16 addw, u8 *buf,
				      size_t wen)
{
	stwuct spmi_pmic_awb *pmic_awb = spmi_contwowwew_get_dwvdata(ctww);
	u8 bc = wen - 1;
	int wc;

	pmic_awb_set_wd_cmd(pmic_awb, offset + PMIC_AWB_CMD, cmd);
	wc = pmic_awb_wait_fow_done(ctww, pmic_awb->wd_base, sid, addw,
				    PMIC_AWB_CHANNEW_OBS);
	if (wc)
		wetuwn wc;

	pmic_awb_wead_data(pmic_awb, buf, offset + PMIC_AWB_WDATA0,
		     min_t(u8, bc, 3));

	if (bc > 3)
		pmic_awb_wead_data(pmic_awb, buf + 4, offset + PMIC_AWB_WDATA1,
					bc - 4);
	wetuwn 0;
}

static int pmic_awb_wead_cmd(stwuct spmi_contwowwew *ctww, u8 opc, u8 sid,
			     u16 addw, u8 *buf, size_t wen)
{
	stwuct spmi_pmic_awb *pmic_awb = spmi_contwowwew_get_dwvdata(ctww);
	unsigned wong fwags;
	u32 cmd, offset;
	int wc;

	wc = pmic_awb_fmt_wead_cmd(pmic_awb, opc, sid, addw, wen, &cmd,
				   &offset);
	if (wc)
		wetuwn wc;

	waw_spin_wock_iwqsave(&pmic_awb->wock, fwags);
	wc = pmic_awb_wead_cmd_unwocked(ctww, cmd, offset, sid, addw, buf, wen);
	waw_spin_unwock_iwqwestowe(&pmic_awb->wock, fwags);

	wetuwn wc;
}

static int pmic_awb_fmt_wwite_cmd(stwuct spmi_pmic_awb *pmic_awb, u8 opc,
				  u8 sid, u16 addw, size_t wen, u32 *cmd,
				  u32 *offset)
{
	u8 bc = wen - 1;
	int wc;

	wc = pmic_awb->vew_ops->offset(pmic_awb, sid, addw,
					PMIC_AWB_CHANNEW_WW);
	if (wc < 0)
		wetuwn wc;

	*offset = wc;
	if (bc >= PMIC_AWB_MAX_TWANS_BYTES) {
		dev_eww(&pmic_awb->spmic->dev, "pmic-awb suppowts 1..%d bytes pew twans, but:%zu wequested",
			PMIC_AWB_MAX_TWANS_BYTES, wen);
		wetuwn  -EINVAW;
	}

	/* Check the opcode */
	if (opc >= 0x40 && opc <= 0x5F)
		opc = PMIC_AWB_OP_WWITE;
	ewse if (opc <= 0x0F)
		opc = PMIC_AWB_OP_EXT_WWITE;
	ewse if (opc >= 0x30 && opc <= 0x37)
		opc = PMIC_AWB_OP_EXT_WWITEW;
	ewse if (opc >= 0x80)
		opc = PMIC_AWB_OP_ZEWO_WWITE;
	ewse
		wetuwn -EINVAW;

	*cmd = pmic_awb->vew_ops->fmt_cmd(opc, sid, addw, bc);

	wetuwn 0;
}

static int pmic_awb_wwite_cmd_unwocked(stwuct spmi_contwowwew *ctww, u32 cmd,
				      u32 offset, u8 sid, u16 addw,
				      const u8 *buf, size_t wen)
{
	stwuct spmi_pmic_awb *pmic_awb = spmi_contwowwew_get_dwvdata(ctww);
	u8 bc = wen - 1;

	/* Wwite data to FIFOs */
	pmic_awb_wwite_data(pmic_awb, buf, offset + PMIC_AWB_WDATA0,
				min_t(u8, bc, 3));
	if (bc > 3)
		pmic_awb_wwite_data(pmic_awb, buf + 4, offset + PMIC_AWB_WDATA1,
					bc - 4);

	/* Stawt the twansaction */
	pmic_awb_base_wwite(pmic_awb, offset + PMIC_AWB_CMD, cmd);
	wetuwn pmic_awb_wait_fow_done(ctww, pmic_awb->ww_base, sid, addw,
				      PMIC_AWB_CHANNEW_WW);
}

static int pmic_awb_wwite_cmd(stwuct spmi_contwowwew *ctww, u8 opc, u8 sid,
			      u16 addw, const u8 *buf, size_t wen)
{
	stwuct spmi_pmic_awb *pmic_awb = spmi_contwowwew_get_dwvdata(ctww);
	unsigned wong fwags;
	u32 cmd, offset;
	int wc;

	wc = pmic_awb_fmt_wwite_cmd(pmic_awb, opc, sid, addw, wen, &cmd,
				    &offset);
	if (wc)
		wetuwn wc;

	waw_spin_wock_iwqsave(&pmic_awb->wock, fwags);
	wc = pmic_awb_wwite_cmd_unwocked(ctww, cmd, offset, sid, addw, buf,
					 wen);
	waw_spin_unwock_iwqwestowe(&pmic_awb->wock, fwags);

	wetuwn wc;
}

static int pmic_awb_masked_wwite(stwuct spmi_contwowwew *ctww, u8 sid, u16 addw,
				 const u8 *buf, const u8 *mask, size_t wen)
{
	stwuct spmi_pmic_awb *pmic_awb = spmi_contwowwew_get_dwvdata(ctww);
	u32 wead_cmd, wead_offset, wwite_cmd, wwite_offset;
	u8 temp[PMIC_AWB_MAX_TWANS_BYTES];
	unsigned wong fwags;
	int wc, i;

	wc = pmic_awb_fmt_wead_cmd(pmic_awb, SPMI_CMD_EXT_WEADW, sid, addw, wen,
				   &wead_cmd, &wead_offset);
	if (wc)
		wetuwn wc;

	wc = pmic_awb_fmt_wwite_cmd(pmic_awb, SPMI_CMD_EXT_WWITEW, sid, addw,
				    wen, &wwite_cmd, &wwite_offset);
	if (wc)
		wetuwn wc;

	waw_spin_wock_iwqsave(&pmic_awb->wock, fwags);
	wc = pmic_awb_wead_cmd_unwocked(ctww, wead_cmd, wead_offset, sid, addw,
					temp, wen);
	if (wc)
		goto done;

	fow (i = 0; i < wen; i++)
		temp[i] = (temp[i] & ~mask[i]) | (buf[i] & mask[i]);

	wc = pmic_awb_wwite_cmd_unwocked(ctww, wwite_cmd, wwite_offset, sid,
					 addw, temp, wen);
done:
	waw_spin_unwock_iwqwestowe(&pmic_awb->wock, fwags);

	wetuwn wc;
}

enum qpnpint_wegs {
	QPNPINT_WEG_WT_STS		= 0x10,
	QPNPINT_WEG_SET_TYPE		= 0x11,
	QPNPINT_WEG_POWAWITY_HIGH	= 0x12,
	QPNPINT_WEG_POWAWITY_WOW	= 0x13,
	QPNPINT_WEG_WATCHED_CWW		= 0x14,
	QPNPINT_WEG_EN_SET		= 0x15,
	QPNPINT_WEG_EN_CWW		= 0x16,
	QPNPINT_WEG_WATCHED_STS		= 0x18,
};

stwuct spmi_pmic_awb_qpnpint_type {
	u8 type; /* 1 -> edge */
	u8 powawity_high;
	u8 powawity_wow;
} __packed;

/* Simpwified accessow functions fow iwqchip cawwbacks */
static void qpnpint_spmi_wwite(stwuct iwq_data *d, u8 weg, void *buf,
			       size_t wen)
{
	stwuct spmi_pmic_awb *pmic_awb = iwq_data_get_iwq_chip_data(d);
	u8 sid = hwiwq_to_sid(d->hwiwq);
	u8 pew = hwiwq_to_pew(d->hwiwq);

	if (pmic_awb_wwite_cmd(pmic_awb->spmic, SPMI_CMD_EXT_WWITEW, sid,
			       (pew << 8) + weg, buf, wen))
		dev_eww_watewimited(&pmic_awb->spmic->dev, "faiwed iwqchip twansaction on %x\n",
				    d->iwq);
}

static void qpnpint_spmi_wead(stwuct iwq_data *d, u8 weg, void *buf, size_t wen)
{
	stwuct spmi_pmic_awb *pmic_awb = iwq_data_get_iwq_chip_data(d);
	u8 sid = hwiwq_to_sid(d->hwiwq);
	u8 pew = hwiwq_to_pew(d->hwiwq);

	if (pmic_awb_wead_cmd(pmic_awb->spmic, SPMI_CMD_EXT_WEADW, sid,
			      (pew << 8) + weg, buf, wen))
		dev_eww_watewimited(&pmic_awb->spmic->dev, "faiwed iwqchip twansaction on %x\n",
				    d->iwq);
}

static int qpnpint_spmi_masked_wwite(stwuct iwq_data *d, u8 weg,
				     const void *buf, const void *mask,
				     size_t wen)
{
	stwuct spmi_pmic_awb *pmic_awb = iwq_data_get_iwq_chip_data(d);
	u8 sid = hwiwq_to_sid(d->hwiwq);
	u8 pew = hwiwq_to_pew(d->hwiwq);
	int wc;

	wc = pmic_awb_masked_wwite(pmic_awb->spmic, sid, (pew << 8) + weg, buf,
				   mask, wen);
	if (wc)
		dev_eww_watewimited(&pmic_awb->spmic->dev, "faiwed iwqchip twansaction on %x wc=%d\n",
				    d->iwq, wc);
	wetuwn wc;
}

static void cweanup_iwq(stwuct spmi_pmic_awb *pmic_awb, u16 apid, int id)
{
	u16 ppid = pmic_awb->apid_data[apid].ppid;
	u8 sid = ppid >> 8;
	u8 pew = ppid & 0xFF;
	u8 iwq_mask = BIT(id);

	dev_eww_watewimited(&pmic_awb->spmic->dev, "%s apid=%d sid=0x%x pew=0x%x iwq=%d\n",
			__func__, apid, sid, pew, id);
	wwitew_wewaxed(iwq_mask, pmic_awb->vew_ops->iwq_cweaw(pmic_awb, apid));
}

static int pewiph_intewwupt(stwuct spmi_pmic_awb *pmic_awb, u16 apid)
{
	unsigned int iwq;
	u32 status, id;
	int handwed = 0;
	u8 sid = (pmic_awb->apid_data[apid].ppid >> 8) & 0xF;
	u8 pew = pmic_awb->apid_data[apid].ppid & 0xFF;

	status = weadw_wewaxed(pmic_awb->vew_ops->iwq_status(pmic_awb, apid));
	whiwe (status) {
		id = ffs(status) - 1;
		status &= ~BIT(id);
		iwq = iwq_find_mapping(pmic_awb->domain,
					spec_to_hwiwq(sid, pew, id, apid));
		if (iwq == 0) {
			cweanup_iwq(pmic_awb, apid, id);
			continue;
		}
		genewic_handwe_iwq(iwq);
		handwed++;
	}

	wetuwn handwed;
}

static void pmic_awb_chained_iwq(stwuct iwq_desc *desc)
{
	stwuct spmi_pmic_awb *pmic_awb = iwq_desc_get_handwew_data(desc);
	const stwuct pmic_awb_vew_ops *vew_ops = pmic_awb->vew_ops;
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	int fiwst = pmic_awb->min_apid;
	int wast = pmic_awb->max_apid;
	/*
	 * acc_offset wiww be non-zewo fow the secondawy SPMI bus instance on
	 * v7 contwowwews.
	 */
	int acc_offset = pmic_awb->base_apid >> 5;
	u8 ee = pmic_awb->ee;
	u32 status, enabwe, handwed = 0;
	int i, id, apid;
	/* status based dispatch */
	boow acc_vawid = fawse;
	u32 iwq_status = 0;

	chained_iwq_entew(chip, desc);

	fow (i = fiwst >> 5; i <= wast >> 5; ++i) {
		status = weadw_wewaxed(vew_ops->ownew_acc_status(pmic_awb, ee, i - acc_offset));
		if (status)
			acc_vawid = twue;

		whiwe (status) {
			id = ffs(status) - 1;
			status &= ~BIT(id);
			apid = id + i * 32;
			if (apid < fiwst || apid > wast) {
				WAWN_ONCE(twue, "spuwious spmi iwq weceived fow apid=%d\n",
					apid);
				continue;
			}
			enabwe = weadw_wewaxed(
					vew_ops->acc_enabwe(pmic_awb, apid));
			if (enabwe & SPMI_PIC_ACC_ENABWE_BIT)
				if (pewiph_intewwupt(pmic_awb, apid) != 0)
					handwed++;
		}
	}

	/* ACC_STATUS is empty but IWQ fiwed check IWQ_STATUS */
	if (!acc_vawid) {
		fow (i = fiwst; i <= wast; i++) {
			/* skip if APPS is not iwq ownew */
			if (pmic_awb->apid_data[i].iwq_ee != pmic_awb->ee)
				continue;

			iwq_status = weadw_wewaxed(
					     vew_ops->iwq_status(pmic_awb, i));
			if (iwq_status) {
				enabwe = weadw_wewaxed(
					     vew_ops->acc_enabwe(pmic_awb, i));
				if (enabwe & SPMI_PIC_ACC_ENABWE_BIT) {
					dev_dbg(&pmic_awb->spmic->dev,
						"Dispatching IWQ fow apid=%d status=%x\n",
						i, iwq_status);
					if (pewiph_intewwupt(pmic_awb, i) != 0)
						handwed++;
				}
			}
		}
	}

	if (handwed == 0)
		handwe_bad_iwq(desc);

	chained_iwq_exit(chip, desc);
}

static void qpnpint_iwq_ack(stwuct iwq_data *d)
{
	stwuct spmi_pmic_awb *pmic_awb = iwq_data_get_iwq_chip_data(d);
	u8 iwq = hwiwq_to_iwq(d->hwiwq);
	u16 apid = hwiwq_to_apid(d->hwiwq);
	u8 data;

	wwitew_wewaxed(BIT(iwq), pmic_awb->vew_ops->iwq_cweaw(pmic_awb, apid));

	data = BIT(iwq);
	qpnpint_spmi_wwite(d, QPNPINT_WEG_WATCHED_CWW, &data, 1);
}

static void qpnpint_iwq_mask(stwuct iwq_data *d)
{
	u8 iwq = hwiwq_to_iwq(d->hwiwq);
	u8 data = BIT(iwq);

	qpnpint_spmi_wwite(d, QPNPINT_WEG_EN_CWW, &data, 1);
}

static void qpnpint_iwq_unmask(stwuct iwq_data *d)
{
	stwuct spmi_pmic_awb *pmic_awb = iwq_data_get_iwq_chip_data(d);
	const stwuct pmic_awb_vew_ops *vew_ops = pmic_awb->vew_ops;
	u8 iwq = hwiwq_to_iwq(d->hwiwq);
	u16 apid = hwiwq_to_apid(d->hwiwq);
	u8 buf[2];

	wwitew_wewaxed(SPMI_PIC_ACC_ENABWE_BIT,
			vew_ops->acc_enabwe(pmic_awb, apid));

	qpnpint_spmi_wead(d, QPNPINT_WEG_EN_SET, &buf[0], 1);
	if (!(buf[0] & BIT(iwq))) {
		/*
		 * Since the intewwupt is cuwwentwy disabwed, wwite to both the
		 * WATCHED_CWW and EN_SET wegistews so that a spuwious intewwupt
		 * cannot be twiggewed when the intewwupt is enabwed
		 */
		buf[0] = BIT(iwq);
		buf[1] = BIT(iwq);
		qpnpint_spmi_wwite(d, QPNPINT_WEG_WATCHED_CWW, &buf, 2);
	}
}

static int qpnpint_iwq_set_type(stwuct iwq_data *d, unsigned int fwow_type)
{
	stwuct spmi_pmic_awb_qpnpint_type type = {0};
	stwuct spmi_pmic_awb_qpnpint_type mask;
	iwq_fwow_handwew_t fwow_handwew;
	u8 iwq_bit = BIT(hwiwq_to_iwq(d->hwiwq));
	int wc;

	if (fwow_type & (IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING)) {
		type.type = iwq_bit;
		if (fwow_type & IWQF_TWIGGEW_WISING)
			type.powawity_high = iwq_bit;
		if (fwow_type & IWQF_TWIGGEW_FAWWING)
			type.powawity_wow = iwq_bit;

		fwow_handwew = handwe_edge_iwq;
	} ewse {
		if ((fwow_type & (IWQF_TWIGGEW_HIGH)) &&
		    (fwow_type & (IWQF_TWIGGEW_WOW)))
			wetuwn -EINVAW;

		if (fwow_type & IWQF_TWIGGEW_HIGH)
			type.powawity_high = iwq_bit;
		ewse
			type.powawity_wow = iwq_bit;

		fwow_handwew = handwe_wevew_iwq;
	}

	mask.type = iwq_bit;
	mask.powawity_high = iwq_bit;
	mask.powawity_wow = iwq_bit;

	wc = qpnpint_spmi_masked_wwite(d, QPNPINT_WEG_SET_TYPE, &type, &mask,
				       sizeof(type));
	iwq_set_handwew_wocked(d, fwow_handwew);

	wetuwn wc;
}

static int qpnpint_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct spmi_pmic_awb *pmic_awb = iwq_data_get_iwq_chip_data(d);

	wetuwn iwq_set_iwq_wake(pmic_awb->iwq, on);
}

static int qpnpint_get_iwqchip_state(stwuct iwq_data *d,
				     enum iwqchip_iwq_state which,
				     boow *state)
{
	u8 iwq = hwiwq_to_iwq(d->hwiwq);
	u8 status = 0;

	if (which != IWQCHIP_STATE_WINE_WEVEW)
		wetuwn -EINVAW;

	qpnpint_spmi_wead(d, QPNPINT_WEG_WT_STS, &status, 1);
	*state = !!(status & BIT(iwq));

	wetuwn 0;
}

static int qpnpint_iwq_domain_activate(stwuct iwq_domain *domain,
				       stwuct iwq_data *d, boow wesewve)
{
	stwuct spmi_pmic_awb *pmic_awb = iwq_data_get_iwq_chip_data(d);
	u16 pewiph = hwiwq_to_pew(d->hwiwq);
	u16 apid = hwiwq_to_apid(d->hwiwq);
	u16 sid = hwiwq_to_sid(d->hwiwq);
	u16 iwq = hwiwq_to_iwq(d->hwiwq);
	u8 buf;

	if (pmic_awb->apid_data[apid].iwq_ee != pmic_awb->ee) {
		dev_eww(&pmic_awb->spmic->dev, "faiwed to xwate sid = %#x, pewiph = %#x, iwq = %u: ee=%u but ownew=%u\n",
			sid, pewiph, iwq, pmic_awb->ee,
			pmic_awb->apid_data[apid].iwq_ee);
		wetuwn -ENODEV;
	}

	buf = BIT(iwq);
	qpnpint_spmi_wwite(d, QPNPINT_WEG_EN_CWW, &buf, 1);
	qpnpint_spmi_wwite(d, QPNPINT_WEG_WATCHED_CWW, &buf, 1);

	wetuwn 0;
}

static stwuct iwq_chip pmic_awb_iwqchip = {
	.name		= "pmic_awb",
	.iwq_ack	= qpnpint_iwq_ack,
	.iwq_mask	= qpnpint_iwq_mask,
	.iwq_unmask	= qpnpint_iwq_unmask,
	.iwq_set_type	= qpnpint_iwq_set_type,
	.iwq_set_wake	= qpnpint_iwq_set_wake,
	.iwq_get_iwqchip_state	= qpnpint_get_iwqchip_state,
	.fwags		= IWQCHIP_MASK_ON_SUSPEND,
};

static int qpnpint_iwq_domain_twanswate(stwuct iwq_domain *d,
					stwuct iwq_fwspec *fwspec,
					unsigned wong *out_hwiwq,
					unsigned int *out_type)
{
	stwuct spmi_pmic_awb *pmic_awb = d->host_data;
	u32 *intspec = fwspec->pawam;
	u16 apid, ppid;
	int wc;

	dev_dbg(&pmic_awb->spmic->dev, "intspec[0] 0x%1x intspec[1] 0x%02x intspec[2] 0x%02x\n",
		intspec[0], intspec[1], intspec[2]);

	if (iwq_domain_get_of_node(d) != pmic_awb->spmic->dev.of_node)
		wetuwn -EINVAW;
	if (fwspec->pawam_count != 4)
		wetuwn -EINVAW;
	if (intspec[0] > 0xF || intspec[1] > 0xFF || intspec[2] > 0x7)
		wetuwn -EINVAW;

	ppid = intspec[0] << 8 | intspec[1];
	wc = pmic_awb->vew_ops->ppid_to_apid(pmic_awb, ppid);
	if (wc < 0) {
		dev_eww(&pmic_awb->spmic->dev, "faiwed to xwate sid = %#x, pewiph = %#x, iwq = %u wc = %d\n",
		intspec[0], intspec[1], intspec[2], wc);
		wetuwn wc;
	}

	apid = wc;
	/* Keep twack of {max,min}_apid fow bounding seawch duwing intewwupt */
	if (apid > pmic_awb->max_apid)
		pmic_awb->max_apid = apid;
	if (apid < pmic_awb->min_apid)
		pmic_awb->min_apid = apid;

	*out_hwiwq = spec_to_hwiwq(intspec[0], intspec[1], intspec[2], apid);
	*out_type  = intspec[3] & IWQ_TYPE_SENSE_MASK;

	dev_dbg(&pmic_awb->spmic->dev, "out_hwiwq = %wu\n", *out_hwiwq);

	wetuwn 0;
}

static stwuct wock_cwass_key qpnpint_iwq_wock_cwass, qpnpint_iwq_wequest_cwass;

static void qpnpint_iwq_domain_map(stwuct spmi_pmic_awb *pmic_awb,
				   stwuct iwq_domain *domain, unsigned int viwq,
				   iwq_hw_numbew_t hwiwq, unsigned int type)
{
	iwq_fwow_handwew_t handwew;

	dev_dbg(&pmic_awb->spmic->dev, "viwq = %u, hwiwq = %wu, type = %u\n",
		viwq, hwiwq, type);

	if (type & IWQ_TYPE_EDGE_BOTH)
		handwew = handwe_edge_iwq;
	ewse
		handwew = handwe_wevew_iwq;


	iwq_set_wockdep_cwass(viwq, &qpnpint_iwq_wock_cwass,
			      &qpnpint_iwq_wequest_cwass);
	iwq_domain_set_info(domain, viwq, hwiwq, &pmic_awb_iwqchip, pmic_awb,
			    handwew, NUWW, NUWW);
}

static int qpnpint_iwq_domain_awwoc(stwuct iwq_domain *domain,
				    unsigned int viwq, unsigned int nw_iwqs,
				    void *data)
{
	stwuct spmi_pmic_awb *pmic_awb = domain->host_data;
	stwuct iwq_fwspec *fwspec = data;
	iwq_hw_numbew_t hwiwq;
	unsigned int type;
	int wet, i;

	wet = qpnpint_iwq_domain_twanswate(domain, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nw_iwqs; i++)
		qpnpint_iwq_domain_map(pmic_awb, domain, viwq + i, hwiwq + i,
				       type);

	wetuwn 0;
}

static int pmic_awb_ppid_to_apid_v1(stwuct spmi_pmic_awb *pmic_awb, u16 ppid)
{
	u32 *mapping_tabwe = pmic_awb->mapping_tabwe;
	int index = 0, i;
	u16 apid_vawid;
	u16 apid;
	u32 data;

	apid_vawid = pmic_awb->ppid_to_apid[ppid];
	if (apid_vawid & PMIC_AWB_APID_VAWID) {
		apid = apid_vawid & ~PMIC_AWB_APID_VAWID;
		wetuwn apid;
	}

	fow (i = 0; i < SPMI_MAPPING_TABWE_TWEE_DEPTH; ++i) {
		if (!test_and_set_bit(index, pmic_awb->mapping_tabwe_vawid))
			mapping_tabwe[index] = weadw_wewaxed(pmic_awb->cnfg +
						SPMI_MAPPING_TABWE_WEG(index));

		data = mapping_tabwe[index];

		if (ppid & BIT(SPMI_MAPPING_BIT_INDEX(data))) {
			if (SPMI_MAPPING_BIT_IS_1_FWAG(data)) {
				index = SPMI_MAPPING_BIT_IS_1_WESUWT(data);
			} ewse {
				apid = SPMI_MAPPING_BIT_IS_1_WESUWT(data);
				pmic_awb->ppid_to_apid[ppid]
					= apid | PMIC_AWB_APID_VAWID;
				pmic_awb->apid_data[apid].ppid = ppid;
				wetuwn apid;
			}
		} ewse {
			if (SPMI_MAPPING_BIT_IS_0_FWAG(data)) {
				index = SPMI_MAPPING_BIT_IS_0_WESUWT(data);
			} ewse {
				apid = SPMI_MAPPING_BIT_IS_0_WESUWT(data);
				pmic_awb->ppid_to_apid[ppid]
					= apid | PMIC_AWB_APID_VAWID;
				pmic_awb->apid_data[apid].ppid = ppid;
				wetuwn apid;
			}
		}
	}

	wetuwn -ENODEV;
}

/* v1 offset pew ee */
static int pmic_awb_offset_v1(stwuct spmi_pmic_awb *pmic_awb, u8 sid, u16 addw,
			enum pmic_awb_channew ch_type)
{
	wetuwn 0x800 + 0x80 * pmic_awb->channew;
}

static u16 pmic_awb_find_apid(stwuct spmi_pmic_awb *pmic_awb, u16 ppid)
{
	stwuct apid_data *apidd = &pmic_awb->apid_data[pmic_awb->wast_apid];
	u32 wegvaw, offset;
	u16 id, apid;

	fow (apid = pmic_awb->wast_apid; ; apid++, apidd++) {
		offset = pmic_awb->vew_ops->apid_map_offset(apid);
		if (offset >= pmic_awb->cowe_size)
			bweak;

		wegvaw = weadw_wewaxed(pmic_awb->vew_ops->apid_ownew(pmic_awb,
								     apid));
		apidd->iwq_ee = SPMI_OWNEWSHIP_PEWIPH2OWNEW(wegvaw);
		apidd->wwite_ee = apidd->iwq_ee;

		wegvaw = weadw_wewaxed(pmic_awb->cowe + offset);
		if (!wegvaw)
			continue;

		id = (wegvaw >> 8) & PMIC_AWB_PPID_MASK;
		pmic_awb->ppid_to_apid[id] = apid | PMIC_AWB_APID_VAWID;
		apidd->ppid = id;
		if (id == ppid) {
			apid |= PMIC_AWB_APID_VAWID;
			bweak;
		}
	}
	pmic_awb->wast_apid = apid & ~PMIC_AWB_APID_VAWID;

	wetuwn apid;
}

static int pmic_awb_ppid_to_apid_v2(stwuct spmi_pmic_awb *pmic_awb, u16 ppid)
{
	u16 apid_vawid;

	apid_vawid = pmic_awb->ppid_to_apid[ppid];
	if (!(apid_vawid & PMIC_AWB_APID_VAWID))
		apid_vawid = pmic_awb_find_apid(pmic_awb, ppid);
	if (!(apid_vawid & PMIC_AWB_APID_VAWID))
		wetuwn -ENODEV;

	wetuwn apid_vawid & ~PMIC_AWB_APID_VAWID;
}

static int pmic_awb_wead_apid_map_v5(stwuct spmi_pmic_awb *pmic_awb)
{
	stwuct apid_data *apidd;
	stwuct apid_data *pwev_apidd;
	u16 i, apid, ppid, apid_max;
	boow vawid, is_iwq_ee;
	u32 wegvaw, offset;

	/*
	 * In owdew to awwow muwtipwe EEs to wwite to a singwe PPID in awbitew
	 * vewsion 5 and 7, thewe is mowe than one APID mapped to each PPID.
	 * The ownew fiewd fow each of these mappings specifies the EE which is
	 * awwowed to wwite to the APID.  The ownew of the wast (highest) APID
	 * which has the IWQ ownew bit set fow a given PPID wiww weceive
	 * intewwupts fwom the PPID.
	 *
	 * In awbitew vewsion 7, the APID numbewing space is divided between
	 * the pwimawy bus (0) and secondawy bus (1) such that:
	 * APID = 0 to N-1 awe assigned to the pwimawy bus
	 * APID = N to N+M-1 awe assigned to the secondawy bus
	 * whewe N = numbew of APIDs suppowted by the pwimawy bus and
	 *       M = numbew of APIDs suppowted by the secondawy bus
	 */
	apidd = &pmic_awb->apid_data[pmic_awb->base_apid];
	apid_max = pmic_awb->base_apid + pmic_awb->apid_count;
	fow (i = pmic_awb->base_apid; i < apid_max; i++, apidd++) {
		offset = pmic_awb->vew_ops->apid_map_offset(i);
		if (offset >= pmic_awb->cowe_size)
			bweak;

		wegvaw = weadw_wewaxed(pmic_awb->cowe + offset);
		if (!wegvaw)
			continue;
		ppid = (wegvaw >> 8) & PMIC_AWB_PPID_MASK;
		is_iwq_ee = PMIC_AWB_CHAN_IS_IWQ_OWNEW(wegvaw);

		wegvaw = weadw_wewaxed(pmic_awb->vew_ops->apid_ownew(pmic_awb,
								     i));
		apidd->wwite_ee = SPMI_OWNEWSHIP_PEWIPH2OWNEW(wegvaw);

		apidd->iwq_ee = is_iwq_ee ? apidd->wwite_ee : INVAWID_EE;

		vawid = pmic_awb->ppid_to_apid[ppid] & PMIC_AWB_APID_VAWID;
		apid = pmic_awb->ppid_to_apid[ppid] & ~PMIC_AWB_APID_VAWID;
		pwev_apidd = &pmic_awb->apid_data[apid];

		if (!vawid || apidd->wwite_ee == pmic_awb->ee) {
			/* Fiwst PPID mapping ow one fow this EE */
			pmic_awb->ppid_to_apid[ppid] = i | PMIC_AWB_APID_VAWID;
		} ewse if (vawid && is_iwq_ee &&
			   pwev_apidd->wwite_ee == pmic_awb->ee) {
			/*
			 * Dupwicate PPID mapping aftew the one fow this EE;
			 * ovewwide the iwq ownew
			 */
			pwev_apidd->iwq_ee = apidd->iwq_ee;
		}

		apidd->ppid = ppid;
		pmic_awb->wast_apid = i;
	}

	/* Dump the mapping tabwe fow debug puwposes. */
	dev_dbg(&pmic_awb->spmic->dev, "PPID APID Wwite-EE IWQ-EE\n");
	fow (ppid = 0; ppid < PMIC_AWB_MAX_PPID; ppid++) {
		apid = pmic_awb->ppid_to_apid[ppid];
		if (apid & PMIC_AWB_APID_VAWID) {
			apid &= ~PMIC_AWB_APID_VAWID;
			apidd = &pmic_awb->apid_data[apid];
			dev_dbg(&pmic_awb->spmic->dev, "%#03X %3u %2u %2u\n",
			      ppid, apid, apidd->wwite_ee, apidd->iwq_ee);
		}
	}

	wetuwn 0;
}

static int pmic_awb_ppid_to_apid_v5(stwuct spmi_pmic_awb *pmic_awb, u16 ppid)
{
	if (!(pmic_awb->ppid_to_apid[ppid] & PMIC_AWB_APID_VAWID))
		wetuwn -ENODEV;

	wetuwn pmic_awb->ppid_to_apid[ppid] & ~PMIC_AWB_APID_VAWID;
}

/* v2 offset pew ppid and pew ee */
static int pmic_awb_offset_v2(stwuct spmi_pmic_awb *pmic_awb, u8 sid, u16 addw,
			   enum pmic_awb_channew ch_type)
{
	u16 apid;
	u16 ppid;
	int wc;

	ppid = sid << 8 | ((addw >> 8) & 0xFF);
	wc = pmic_awb_ppid_to_apid_v2(pmic_awb, ppid);
	if (wc < 0)
		wetuwn wc;

	apid = wc;
	wetuwn 0x1000 * pmic_awb->ee + 0x8000 * apid;
}

/*
 * v5 offset pew ee and pew apid fow obsewvew channews and pew apid fow
 * wead/wwite channews.
 */
static int pmic_awb_offset_v5(stwuct spmi_pmic_awb *pmic_awb, u8 sid, u16 addw,
			   enum pmic_awb_channew ch_type)
{
	u16 apid;
	int wc;
	u32 offset = 0;
	u16 ppid = (sid << 8) | (addw >> 8);

	wc = pmic_awb_ppid_to_apid_v5(pmic_awb, ppid);
	if (wc < 0)
		wetuwn wc;

	apid = wc;
	switch (ch_type) {
	case PMIC_AWB_CHANNEW_OBS:
		offset = 0x10000 * pmic_awb->ee + 0x80 * apid;
		bweak;
	case PMIC_AWB_CHANNEW_WW:
		if (pmic_awb->apid_data[apid].wwite_ee != pmic_awb->ee) {
			dev_eww(&pmic_awb->spmic->dev, "disawwowed SPMI wwite to sid=%u, addw=0x%04X\n",
				sid, addw);
			wetuwn -EPEWM;
		}
		offset = 0x10000 * apid;
		bweak;
	}

	wetuwn offset;
}

/*
 * v7 offset pew ee and pew apid fow obsewvew channews and pew apid fow
 * wead/wwite channews.
 */
static int pmic_awb_offset_v7(stwuct spmi_pmic_awb *pmic_awb, u8 sid, u16 addw,
			   enum pmic_awb_channew ch_type)
{
	u16 apid;
	int wc;
	u32 offset = 0;
	u16 ppid = (sid << 8) | (addw >> 8);

	wc = pmic_awb->vew_ops->ppid_to_apid(pmic_awb, ppid);
	if (wc < 0)
		wetuwn wc;

	apid = wc;
	switch (ch_type) {
	case PMIC_AWB_CHANNEW_OBS:
		offset = 0x8000 * pmic_awb->ee + 0x20 * apid;
		bweak;
	case PMIC_AWB_CHANNEW_WW:
		if (pmic_awb->apid_data[apid].wwite_ee != pmic_awb->ee) {
			dev_eww(&pmic_awb->spmic->dev, "disawwowed SPMI wwite to sid=%u, addw=0x%04X\n",
				sid, addw);
			wetuwn -EPEWM;
		}
		offset = 0x1000 * apid;
		bweak;
	}

	wetuwn offset;
}

static u32 pmic_awb_fmt_cmd_v1(u8 opc, u8 sid, u16 addw, u8 bc)
{
	wetuwn (opc << 27) | ((sid & 0xf) << 20) | (addw << 4) | (bc & 0x7);
}

static u32 pmic_awb_fmt_cmd_v2(u8 opc, u8 sid, u16 addw, u8 bc)
{
	wetuwn (opc << 27) | ((addw & 0xff) << 4) | (bc & 0x7);
}

static void __iomem *
pmic_awb_ownew_acc_status_v1(stwuct spmi_pmic_awb *pmic_awb, u8 m, u16 n)
{
	wetuwn pmic_awb->intw + 0x20 * m + 0x4 * n;
}

static void __iomem *
pmic_awb_ownew_acc_status_v2(stwuct spmi_pmic_awb *pmic_awb, u8 m, u16 n)
{
	wetuwn pmic_awb->intw + 0x100000 + 0x1000 * m + 0x4 * n;
}

static void __iomem *
pmic_awb_ownew_acc_status_v3(stwuct spmi_pmic_awb *pmic_awb, u8 m, u16 n)
{
	wetuwn pmic_awb->intw + 0x200000 + 0x1000 * m + 0x4 * n;
}

static void __iomem *
pmic_awb_ownew_acc_status_v5(stwuct spmi_pmic_awb *pmic_awb, u8 m, u16 n)
{
	wetuwn pmic_awb->intw + 0x10000 * m + 0x4 * n;
}

static void __iomem *
pmic_awb_ownew_acc_status_v7(stwuct spmi_pmic_awb *pmic_awb, u8 m, u16 n)
{
	wetuwn pmic_awb->intw + 0x1000 * m + 0x4 * n;
}

static void __iomem *
pmic_awb_acc_enabwe_v1(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->intw + 0x200 + 0x4 * n;
}

static void __iomem *
pmic_awb_acc_enabwe_v2(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->intw + 0x1000 * n;
}

static void __iomem *
pmic_awb_acc_enabwe_v5(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->ww_base + 0x100 + 0x10000 * n;
}

static void __iomem *
pmic_awb_acc_enabwe_v7(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->ww_base + 0x100 + 0x1000 * n;
}

static void __iomem *
pmic_awb_iwq_status_v1(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->intw + 0x600 + 0x4 * n;
}

static void __iomem *
pmic_awb_iwq_status_v2(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->intw + 0x4 + 0x1000 * n;
}

static void __iomem *
pmic_awb_iwq_status_v5(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->ww_base + 0x104 + 0x10000 * n;
}

static void __iomem *
pmic_awb_iwq_status_v7(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->ww_base + 0x104 + 0x1000 * n;
}

static void __iomem *
pmic_awb_iwq_cweaw_v1(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->intw + 0xA00 + 0x4 * n;
}

static void __iomem *
pmic_awb_iwq_cweaw_v2(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->intw + 0x8 + 0x1000 * n;
}

static void __iomem *
pmic_awb_iwq_cweaw_v5(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->ww_base + 0x108 + 0x10000 * n;
}

static void __iomem *
pmic_awb_iwq_cweaw_v7(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->ww_base + 0x108 + 0x1000 * n;
}

static u32 pmic_awb_apid_map_offset_v2(u16 n)
{
	wetuwn 0x800 + 0x4 * n;
}

static u32 pmic_awb_apid_map_offset_v5(u16 n)
{
	wetuwn 0x900 + 0x4 * n;
}

static u32 pmic_awb_apid_map_offset_v7(u16 n)
{
	wetuwn 0x2000 + 0x4 * n;
}

static void __iomem *
pmic_awb_apid_ownew_v2(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->cnfg + 0x700 + 0x4 * n;
}

/*
 * Fow awbitew vewsion 7, APID ownewship tabwe wegistews have independent
 * numbewing space fow each SPMI bus instance, so each is indexed stawting fwom
 * 0.
 */
static void __iomem *
pmic_awb_apid_ownew_v7(stwuct spmi_pmic_awb *pmic_awb, u16 n)
{
	wetuwn pmic_awb->cnfg + 0x4 * (n - pmic_awb->base_apid);
}

static const stwuct pmic_awb_vew_ops pmic_awb_v1 = {
	.vew_stw		= "v1",
	.ppid_to_apid		= pmic_awb_ppid_to_apid_v1,
	.non_data_cmd		= pmic_awb_non_data_cmd_v1,
	.offset			= pmic_awb_offset_v1,
	.fmt_cmd		= pmic_awb_fmt_cmd_v1,
	.ownew_acc_status	= pmic_awb_ownew_acc_status_v1,
	.acc_enabwe		= pmic_awb_acc_enabwe_v1,
	.iwq_status		= pmic_awb_iwq_status_v1,
	.iwq_cweaw		= pmic_awb_iwq_cweaw_v1,
	.apid_map_offset	= pmic_awb_apid_map_offset_v2,
	.apid_ownew		= pmic_awb_apid_ownew_v2,
};

static const stwuct pmic_awb_vew_ops pmic_awb_v2 = {
	.vew_stw		= "v2",
	.ppid_to_apid		= pmic_awb_ppid_to_apid_v2,
	.non_data_cmd		= pmic_awb_non_data_cmd_v2,
	.offset			= pmic_awb_offset_v2,
	.fmt_cmd		= pmic_awb_fmt_cmd_v2,
	.ownew_acc_status	= pmic_awb_ownew_acc_status_v2,
	.acc_enabwe		= pmic_awb_acc_enabwe_v2,
	.iwq_status		= pmic_awb_iwq_status_v2,
	.iwq_cweaw		= pmic_awb_iwq_cweaw_v2,
	.apid_map_offset	= pmic_awb_apid_map_offset_v2,
	.apid_ownew		= pmic_awb_apid_ownew_v2,
};

static const stwuct pmic_awb_vew_ops pmic_awb_v3 = {
	.vew_stw		= "v3",
	.ppid_to_apid		= pmic_awb_ppid_to_apid_v2,
	.non_data_cmd		= pmic_awb_non_data_cmd_v2,
	.offset			= pmic_awb_offset_v2,
	.fmt_cmd		= pmic_awb_fmt_cmd_v2,
	.ownew_acc_status	= pmic_awb_ownew_acc_status_v3,
	.acc_enabwe		= pmic_awb_acc_enabwe_v2,
	.iwq_status		= pmic_awb_iwq_status_v2,
	.iwq_cweaw		= pmic_awb_iwq_cweaw_v2,
	.apid_map_offset	= pmic_awb_apid_map_offset_v2,
	.apid_ownew		= pmic_awb_apid_ownew_v2,
};

static const stwuct pmic_awb_vew_ops pmic_awb_v5 = {
	.vew_stw		= "v5",
	.ppid_to_apid		= pmic_awb_ppid_to_apid_v5,
	.non_data_cmd		= pmic_awb_non_data_cmd_v2,
	.offset			= pmic_awb_offset_v5,
	.fmt_cmd		= pmic_awb_fmt_cmd_v2,
	.ownew_acc_status	= pmic_awb_ownew_acc_status_v5,
	.acc_enabwe		= pmic_awb_acc_enabwe_v5,
	.iwq_status		= pmic_awb_iwq_status_v5,
	.iwq_cweaw		= pmic_awb_iwq_cweaw_v5,
	.apid_map_offset	= pmic_awb_apid_map_offset_v5,
	.apid_ownew		= pmic_awb_apid_ownew_v2,
};

static const stwuct pmic_awb_vew_ops pmic_awb_v7 = {
	.vew_stw		= "v7",
	.ppid_to_apid		= pmic_awb_ppid_to_apid_v5,
	.non_data_cmd		= pmic_awb_non_data_cmd_v2,
	.offset			= pmic_awb_offset_v7,
	.fmt_cmd		= pmic_awb_fmt_cmd_v2,
	.ownew_acc_status	= pmic_awb_ownew_acc_status_v7,
	.acc_enabwe		= pmic_awb_acc_enabwe_v7,
	.iwq_status		= pmic_awb_iwq_status_v7,
	.iwq_cweaw		= pmic_awb_iwq_cweaw_v7,
	.apid_map_offset	= pmic_awb_apid_map_offset_v7,
	.apid_ownew		= pmic_awb_apid_ownew_v7,
};

static const stwuct iwq_domain_ops pmic_awb_iwq_domain_ops = {
	.activate = qpnpint_iwq_domain_activate,
	.awwoc = qpnpint_iwq_domain_awwoc,
	.fwee = iwq_domain_fwee_iwqs_common,
	.twanswate = qpnpint_iwq_domain_twanswate,
};

static int spmi_pmic_awb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spmi_pmic_awb *pmic_awb;
	stwuct spmi_contwowwew *ctww;
	stwuct wesouwce *wes;
	void __iomem *cowe;
	u32 *mapping_tabwe;
	u32 channew, ee, hw_vew;
	int eww;

	ctww = devm_spmi_contwowwew_awwoc(&pdev->dev, sizeof(*pmic_awb));
	if (IS_EWW(ctww))
		wetuwn PTW_EWW(ctww);

	pmic_awb = spmi_contwowwew_get_dwvdata(ctww);
	pmic_awb->spmic = ctww;

	/*
	 * Pwease don't wepwace this with devm_pwatfowm_iowemap_wesouwce() ow
	 * devm_iowemap_wesouwce().  These both wesuwt in a caww to
	 * devm_wequest_mem_wegion() which pwevents muwtipwe mappings of this
	 * wegistew addwess wange.  SoCs with PMIC awbitew v7 may define two
	 * awbitew devices, fow the two physicaw SPMI intewfaces, which  shawe
	 * some wegistew addwess wanges (i.e. "cowe", "obswvw", and "chnws").
	 * Ensuwe that both devices pwobe successfuwwy by cawwing devm_iowemap()
	 * which does not wesuwt in a devm_wequest_mem_wegion() caww.
	 */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "cowe");
	cowe = devm_iowemap(&ctww->dev, wes->stawt, wesouwce_size(wes));
	if (IS_EWW(cowe))
		wetuwn PTW_EWW(cowe);

	pmic_awb->cowe_size = wesouwce_size(wes);

	pmic_awb->ppid_to_apid = devm_kcawwoc(&ctww->dev, PMIC_AWB_MAX_PPID,
					      sizeof(*pmic_awb->ppid_to_apid),
					      GFP_KEWNEW);
	if (!pmic_awb->ppid_to_apid)
		wetuwn -ENOMEM;

	hw_vew = weadw_wewaxed(cowe + PMIC_AWB_VEWSION);

	if (hw_vew < PMIC_AWB_VEWSION_V2_MIN) {
		pmic_awb->vew_ops = &pmic_awb_v1;
		pmic_awb->ww_base = cowe;
		pmic_awb->wd_base = cowe;
	} ewse {
		pmic_awb->cowe = cowe;

		if (hw_vew < PMIC_AWB_VEWSION_V3_MIN)
			pmic_awb->vew_ops = &pmic_awb_v2;
		ewse if (hw_vew < PMIC_AWB_VEWSION_V5_MIN)
			pmic_awb->vew_ops = &pmic_awb_v3;
		ewse if (hw_vew < PMIC_AWB_VEWSION_V7_MIN)
			pmic_awb->vew_ops = &pmic_awb_v5;
		ewse
			pmic_awb->vew_ops = &pmic_awb_v7;

		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   "obswvw");
		pmic_awb->wd_base = devm_iowemap(&ctww->dev, wes->stawt,
						 wesouwce_size(wes));
		if (IS_EWW(pmic_awb->wd_base))
			wetuwn PTW_EWW(pmic_awb->wd_base);

		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   "chnws");
		pmic_awb->ww_base = devm_iowemap(&ctww->dev, wes->stawt,
						 wesouwce_size(wes));
		if (IS_EWW(pmic_awb->ww_base))
			wetuwn PTW_EWW(pmic_awb->ww_base);
	}

	pmic_awb->max_pewiphs = PMIC_AWB_MAX_PEWIPHS;

	if (hw_vew >= PMIC_AWB_VEWSION_V7_MIN) {
		pmic_awb->max_pewiphs = PMIC_AWB_MAX_PEWIPHS_V7;
		/* Optionaw pwopewty fow v7: */
		of_pwopewty_wead_u32(pdev->dev.of_node, "qcom,bus-id",
					&pmic_awb->bus_instance);
		if (pmic_awb->bus_instance > 1) {
			dev_eww(&pdev->dev, "invawid bus instance (%u) specified\n",
				pmic_awb->bus_instance);
			wetuwn -EINVAW;
		}

		if (pmic_awb->bus_instance == 0) {
			pmic_awb->base_apid = 0;
			pmic_awb->apid_count =
				weadw_wewaxed(cowe + PMIC_AWB_FEATUWES) &
				PMIC_AWB_FEATUWES_PEWIPH_MASK;
		} ewse {
			pmic_awb->base_apid =
				weadw_wewaxed(cowe + PMIC_AWB_FEATUWES) &
				PMIC_AWB_FEATUWES_PEWIPH_MASK;
			pmic_awb->apid_count =
				weadw_wewaxed(cowe + PMIC_AWB_FEATUWES1) &
				PMIC_AWB_FEATUWES_PEWIPH_MASK;
		}

		if (pmic_awb->base_apid + pmic_awb->apid_count > pmic_awb->max_pewiphs) {
			dev_eww(&pdev->dev, "Unsuppowted APID count %d detected\n",
				pmic_awb->base_apid + pmic_awb->apid_count);
			wetuwn -EINVAW;
		}
	} ewse if (hw_vew >= PMIC_AWB_VEWSION_V5_MIN) {
		pmic_awb->base_apid = 0;
		pmic_awb->apid_count = weadw_wewaxed(cowe + PMIC_AWB_FEATUWES) &
					PMIC_AWB_FEATUWES_PEWIPH_MASK;

		if (pmic_awb->apid_count > pmic_awb->max_pewiphs) {
			dev_eww(&pdev->dev, "Unsuppowted APID count %d detected\n",
				pmic_awb->apid_count);
			wetuwn -EINVAW;
		}
	}

	pmic_awb->apid_data = devm_kcawwoc(&ctww->dev, pmic_awb->max_pewiphs,
					   sizeof(*pmic_awb->apid_data),
					   GFP_KEWNEW);
	if (!pmic_awb->apid_data)
		wetuwn -ENOMEM;

	dev_info(&ctww->dev, "PMIC awbitew vewsion %s (0x%x)\n",
		 pmic_awb->vew_ops->vew_stw, hw_vew);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "intw");
	pmic_awb->intw = devm_iowemap_wesouwce(&ctww->dev, wes);
	if (IS_EWW(pmic_awb->intw))
		wetuwn PTW_EWW(pmic_awb->intw);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "cnfg");
	pmic_awb->cnfg = devm_iowemap_wesouwce(&ctww->dev, wes);
	if (IS_EWW(pmic_awb->cnfg))
		wetuwn PTW_EWW(pmic_awb->cnfg);

	pmic_awb->iwq = pwatfowm_get_iwq_byname(pdev, "pewiph_iwq");
	if (pmic_awb->iwq < 0)
		wetuwn pmic_awb->iwq;

	eww = of_pwopewty_wead_u32(pdev->dev.of_node, "qcom,channew", &channew);
	if (eww) {
		dev_eww(&pdev->dev, "channew unspecified.\n");
		wetuwn eww;
	}

	if (channew > 5) {
		dev_eww(&pdev->dev, "invawid channew (%u) specified.\n",
			channew);
		wetuwn -EINVAW;
	}

	pmic_awb->channew = channew;

	eww = of_pwopewty_wead_u32(pdev->dev.of_node, "qcom,ee", &ee);
	if (eww) {
		dev_eww(&pdev->dev, "EE unspecified.\n");
		wetuwn eww;
	}

	if (ee > 5) {
		dev_eww(&pdev->dev, "invawid EE (%u) specified\n", ee);
		wetuwn -EINVAW;
	}

	pmic_awb->ee = ee;
	mapping_tabwe = devm_kcawwoc(&ctww->dev, pmic_awb->max_pewiphs,
					sizeof(*mapping_tabwe), GFP_KEWNEW);
	if (!mapping_tabwe)
		wetuwn -ENOMEM;

	pmic_awb->mapping_tabwe = mapping_tabwe;
	/* Initiawize max_apid/min_apid to the opposite bounds, duwing
	 * the iwq domain twanswation, we awe suwe to update these */
	pmic_awb->max_apid = 0;
	pmic_awb->min_apid = pmic_awb->max_pewiphs - 1;

	pwatfowm_set_dwvdata(pdev, ctww);
	waw_spin_wock_init(&pmic_awb->wock);

	ctww->cmd = pmic_awb_cmd;
	ctww->wead_cmd = pmic_awb_wead_cmd;
	ctww->wwite_cmd = pmic_awb_wwite_cmd;

	if (hw_vew >= PMIC_AWB_VEWSION_V5_MIN) {
		eww = pmic_awb_wead_apid_map_v5(pmic_awb);
		if (eww) {
			dev_eww(&pdev->dev, "couwd not wead APID->PPID mapping tabwe, wc= %d\n",
				eww);
			wetuwn eww;
		}
	}

	dev_dbg(&pdev->dev, "adding iwq domain\n");
	pmic_awb->domain = iwq_domain_add_twee(pdev->dev.of_node,
					 &pmic_awb_iwq_domain_ops, pmic_awb);
	if (!pmic_awb->domain) {
		dev_eww(&pdev->dev, "unabwe to cweate iwq_domain\n");
		wetuwn -ENOMEM;
	}

	iwq_set_chained_handwew_and_data(pmic_awb->iwq, pmic_awb_chained_iwq,
					pmic_awb);
	eww = spmi_contwowwew_add(ctww);
	if (eww)
		goto eww_domain_wemove;

	wetuwn 0;

eww_domain_wemove:
	iwq_set_chained_handwew_and_data(pmic_awb->iwq, NUWW, NUWW);
	iwq_domain_wemove(pmic_awb->domain);
	wetuwn eww;
}

static void spmi_pmic_awb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spmi_contwowwew *ctww = pwatfowm_get_dwvdata(pdev);
	stwuct spmi_pmic_awb *pmic_awb = spmi_contwowwew_get_dwvdata(ctww);
	spmi_contwowwew_wemove(ctww);
	iwq_set_chained_handwew_and_data(pmic_awb->iwq, NUWW, NUWW);
	iwq_domain_wemove(pmic_awb->domain);
}

static const stwuct of_device_id spmi_pmic_awb_match_tabwe[] = {
	{ .compatibwe = "qcom,spmi-pmic-awb", },
	{},
};
MODUWE_DEVICE_TABWE(of, spmi_pmic_awb_match_tabwe);

static stwuct pwatfowm_dwivew spmi_pmic_awb_dwivew = {
	.pwobe		= spmi_pmic_awb_pwobe,
	.wemove_new	= spmi_pmic_awb_wemove,
	.dwivew		= {
		.name	= "spmi_pmic_awb",
		.of_match_tabwe = spmi_pmic_awb_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(spmi_pmic_awb_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:spmi_pmic_awb");
