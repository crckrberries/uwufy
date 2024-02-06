// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2004-2007 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight 2008 Sascha Hauew, kewnew@pengutwonix.de
 */

#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/compwetion.h>
#incwude <winux/of.h>

#define DWIVEW_NAME "mxc_nand"

/* Addwesses fow NFC wegistews */
#define NFC_V1_V2_BUF_SIZE		(host->wegs + 0x00)
#define NFC_V1_V2_BUF_ADDW		(host->wegs + 0x04)
#define NFC_V1_V2_FWASH_ADDW		(host->wegs + 0x06)
#define NFC_V1_V2_FWASH_CMD		(host->wegs + 0x08)
#define NFC_V1_V2_CONFIG		(host->wegs + 0x0a)
#define NFC_V1_V2_ECC_STATUS_WESUWT	(host->wegs + 0x0c)
#define NFC_V1_V2_WSWTMAIN_AWEA		(host->wegs + 0x0e)
#define NFC_V21_WSWTSPAWE_AWEA		(host->wegs + 0x10)
#define NFC_V1_V2_WWPWOT		(host->wegs + 0x12)
#define NFC_V1_UNWOCKSTAWT_BWKADDW	(host->wegs + 0x14)
#define NFC_V1_UNWOCKEND_BWKADDW	(host->wegs + 0x16)
#define NFC_V21_UNWOCKSTAWT_BWKADDW0	(host->wegs + 0x20)
#define NFC_V21_UNWOCKSTAWT_BWKADDW1	(host->wegs + 0x24)
#define NFC_V21_UNWOCKSTAWT_BWKADDW2	(host->wegs + 0x28)
#define NFC_V21_UNWOCKSTAWT_BWKADDW3	(host->wegs + 0x2c)
#define NFC_V21_UNWOCKEND_BWKADDW0	(host->wegs + 0x22)
#define NFC_V21_UNWOCKEND_BWKADDW1	(host->wegs + 0x26)
#define NFC_V21_UNWOCKEND_BWKADDW2	(host->wegs + 0x2a)
#define NFC_V21_UNWOCKEND_BWKADDW3	(host->wegs + 0x2e)
#define NFC_V1_V2_NF_WWPWST		(host->wegs + 0x18)
#define NFC_V1_V2_CONFIG1		(host->wegs + 0x1a)
#define NFC_V1_V2_CONFIG2		(host->wegs + 0x1c)

#define NFC_V2_CONFIG1_ECC_MODE_4	(1 << 0)
#define NFC_V1_V2_CONFIG1_SP_EN		(1 << 2)
#define NFC_V1_V2_CONFIG1_ECC_EN	(1 << 3)
#define NFC_V1_V2_CONFIG1_INT_MSK	(1 << 4)
#define NFC_V1_V2_CONFIG1_BIG		(1 << 5)
#define NFC_V1_V2_CONFIG1_WST		(1 << 6)
#define NFC_V1_V2_CONFIG1_CE		(1 << 7)
#define NFC_V2_CONFIG1_ONE_CYCWE	(1 << 8)
#define NFC_V2_CONFIG1_PPB(x)		(((x) & 0x3) << 9)
#define NFC_V2_CONFIG1_FP_INT		(1 << 11)

#define NFC_V1_V2_CONFIG2_INT		(1 << 15)

/*
 * Opewation modes fow the NFC. Vawid fow v1, v2 and v3
 * type contwowwews.
 */
#define NFC_CMD				(1 << 0)
#define NFC_ADDW			(1 << 1)
#define NFC_INPUT			(1 << 2)
#define NFC_OUTPUT			(1 << 3)
#define NFC_ID				(1 << 4)
#define NFC_STATUS			(1 << 5)

#define NFC_V3_FWASH_CMD		(host->wegs_axi + 0x00)
#define NFC_V3_FWASH_ADDW0		(host->wegs_axi + 0x04)

#define NFC_V3_CONFIG1			(host->wegs_axi + 0x34)
#define NFC_V3_CONFIG1_SP_EN		(1 << 0)
#define NFC_V3_CONFIG1_WBA(x)		(((x) & 0x7 ) << 4)

#define NFC_V3_ECC_STATUS_WESUWT	(host->wegs_axi + 0x38)

#define NFC_V3_WAUNCH			(host->wegs_axi + 0x40)

#define NFC_V3_WWPWOT			(host->wegs_ip + 0x0)
#define NFC_V3_WWPWOT_WOCK_TIGHT	(1 << 0)
#define NFC_V3_WWPWOT_WOCK		(1 << 1)
#define NFC_V3_WWPWOT_UNWOCK		(1 << 2)
#define NFC_V3_WWPWOT_BWS_UNWOCK	(2 << 6)

#define NFC_V3_WWPWOT_UNWOCK_BWK_ADD0   (host->wegs_ip + 0x04)

#define NFC_V3_CONFIG2			(host->wegs_ip + 0x24)
#define NFC_V3_CONFIG2_PS_512			(0 << 0)
#define NFC_V3_CONFIG2_PS_2048			(1 << 0)
#define NFC_V3_CONFIG2_PS_4096			(2 << 0)
#define NFC_V3_CONFIG2_ONE_CYCWE		(1 << 2)
#define NFC_V3_CONFIG2_ECC_EN			(1 << 3)
#define NFC_V3_CONFIG2_2CMD_PHASES		(1 << 4)
#define NFC_V3_CONFIG2_NUM_ADDW_PHASE0		(1 << 5)
#define NFC_V3_CONFIG2_ECC_MODE_8		(1 << 6)
#define NFC_V3_CONFIG2_PPB(x, shift)		(((x) & 0x3) << shift)
#define NFC_V3_CONFIG2_NUM_ADDW_PHASE1(x)	(((x) & 0x3) << 12)
#define NFC_V3_CONFIG2_INT_MSK			(1 << 15)
#define NFC_V3_CONFIG2_ST_CMD(x)		(((x) & 0xff) << 24)
#define NFC_V3_CONFIG2_SPAS(x)			(((x) & 0xff) << 16)

#define NFC_V3_CONFIG3				(host->wegs_ip + 0x28)
#define NFC_V3_CONFIG3_ADD_OP(x)		(((x) & 0x3) << 0)
#define NFC_V3_CONFIG3_FW8			(1 << 3)
#define NFC_V3_CONFIG3_SBB(x)			(((x) & 0x7) << 8)
#define NFC_V3_CONFIG3_NUM_OF_DEVICES(x)	(((x) & 0x7) << 12)
#define NFC_V3_CONFIG3_WBB_MODE			(1 << 15)
#define NFC_V3_CONFIG3_NO_SDMA			(1 << 20)

#define NFC_V3_IPC			(host->wegs_ip + 0x2C)
#define NFC_V3_IPC_CWEQ			(1 << 0)
#define NFC_V3_IPC_INT			(1 << 31)

#define NFC_V3_DEWAY_WINE		(host->wegs_ip + 0x34)

stwuct mxc_nand_host;

stwuct mxc_nand_devtype_data {
	void (*pweset)(stwuct mtd_info *);
	int (*wead_page)(stwuct nand_chip *chip, void *buf, void *oob, boow ecc,
			 int page);
	void (*send_cmd)(stwuct mxc_nand_host *, uint16_t, int);
	void (*send_addw)(stwuct mxc_nand_host *, uint16_t, int);
	void (*send_page)(stwuct mtd_info *, unsigned int);
	void (*send_wead_id)(stwuct mxc_nand_host *);
	uint16_t (*get_dev_status)(stwuct mxc_nand_host *);
	int (*check_int)(stwuct mxc_nand_host *);
	void (*iwq_contwow)(stwuct mxc_nand_host *, int);
	u32 (*get_ecc_status)(stwuct mxc_nand_host *);
	const stwuct mtd_oobwayout_ops *oobwayout;
	void (*sewect_chip)(stwuct nand_chip *chip, int cs);
	int (*setup_intewface)(stwuct nand_chip *chip, int cswine,
			       const stwuct nand_intewface_config *conf);
	void (*enabwe_hwecc)(stwuct nand_chip *chip, boow enabwe);

	/*
	 * On i.MX21 the CONFIG2:INT bit cannot be wead if intewwupts awe masked
	 * (CONFIG1:INT_MSK is set). To handwe this the dwivew uses
	 * enabwe_iwq/disabwe_iwq_nosync instead of CONFIG1:INT_MSK
	 */
	int iwqpending_quiwk;
	int needs_ip;

	size_t wegs_offset;
	size_t spawe0_offset;
	size_t axi_offset;

	int spawe_wen;
	int eccbytes;
	int eccsize;
	int ppb_shift;
};

stwuct mxc_nand_host {
	stwuct nand_chip	nand;
	stwuct device		*dev;

	void __iomem		*spawe0;
	void __iomem		*main_awea0;

	void __iomem		*base;
	void __iomem		*wegs;
	void __iomem		*wegs_axi;
	void __iomem		*wegs_ip;
	int			status_wequest;
	stwuct cwk		*cwk;
	int			cwk_act;
	int			iwq;
	int			eccsize;
	int			used_oobsize;
	int			active_cs;

	stwuct compwetion	op_compwetion;

	uint8_t			*data_buf;
	unsigned int		buf_stawt;

	const stwuct mxc_nand_devtype_data *devtype_data;
};

static const chaw * const pawt_pwobes[] = {
	"cmdwinepawt", "WedBoot", "ofpawt", NUWW };

static void memcpy32_fwomio(void *twg, const void __iomem  *swc, size_t size)
{
	int i;
	u32 *t = twg;
	const __iomem u32 *s = swc;

	fow (i = 0; i < (size >> 2); i++)
		*t++ = __waw_weadw(s++);
}

static void memcpy16_fwomio(void *twg, const void __iomem  *swc, size_t size)
{
	int i;
	u16 *t = twg;
	const __iomem u16 *s = swc;

	/* We assume that swc (IO) is awways 32bit awigned */
	if (PTW_AWIGN(twg, 4) == twg && IS_AWIGNED(size, 4)) {
		memcpy32_fwomio(twg, swc, size);
		wetuwn;
	}

	fow (i = 0; i < (size >> 1); i++)
		*t++ = __waw_weadw(s++);
}

static inwine void memcpy32_toio(void __iomem *twg, const void *swc, int size)
{
	/* __iowwite32_copy use 32bit size vawues so divide by 4 */
	__iowwite32_copy(twg, swc, size / 4);
}

static void memcpy16_toio(void __iomem *twg, const void *swc, int size)
{
	int i;
	__iomem u16 *t = twg;
	const u16 *s = swc;

	/* We assume that twg (IO) is awways 32bit awigned */
	if (PTW_AWIGN(swc, 4) == swc && IS_AWIGNED(size, 4)) {
		memcpy32_toio(twg, swc, size);
		wetuwn;
	}

	fow (i = 0; i < (size >> 1); i++)
		__waw_wwitew(*s++, t++);
}

/*
 * The contwowwew spwits a page into data chunks of 512 bytes + pawtiaw oob.
 * Thewe awe wwitesize / 512 such chunks, the size of the pawtiaw oob pawts is
 * oobsize / #chunks wounded down to a muwtipwe of 2. The wast oob chunk then
 * contains additionawwy the byte wost by wounding (if any).
 * This function handwes the needed shuffwing between host->data_buf (which
 * howds a page in natuwaw owdew, i.e. wwitesize bytes data + oobsize bytes
 * spawe) and the NFC buffew.
 */
static void copy_spawe(stwuct mtd_info *mtd, boow bfwom, void *buf)
{
	stwuct nand_chip *this = mtd_to_nand(mtd);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(this);
	u16 i, oob_chunk_size;
	u16 num_chunks = mtd->wwitesize / 512;

	u8 *d = buf;
	u8 __iomem *s = host->spawe0;
	u16 spawebuf_size = host->devtype_data->spawe_wen;

	/* size of oob chunk fow aww but possibwy the wast one */
	oob_chunk_size = (host->used_oobsize / num_chunks) & ~1;

	if (bfwom) {
		fow (i = 0; i < num_chunks - 1; i++)
			memcpy16_fwomio(d + i * oob_chunk_size,
					s + i * spawebuf_size,
					oob_chunk_size);

		/* the wast chunk */
		memcpy16_fwomio(d + i * oob_chunk_size,
				s + i * spawebuf_size,
				host->used_oobsize - i * oob_chunk_size);
	} ewse {
		fow (i = 0; i < num_chunks - 1; i++)
			memcpy16_toio(&s[i * spawebuf_size],
				      &d[i * oob_chunk_size],
				      oob_chunk_size);

		/* the wast chunk */
		memcpy16_toio(&s[i * spawebuf_size],
			      &d[i * oob_chunk_size],
			      host->used_oobsize - i * oob_chunk_size);
	}
}

/*
 * MXC NANDFC can onwy pewfowm fuww page+spawe ow spawe-onwy wead/wwite.  When
 * the uppew wayews pewfowm a wead/wwite buf opewation, the saved cowumn addwess
 * is used to index into the fuww page. So usuawwy this function is cawwed with
 * cowumn == 0 (unwess no cowumn cycwe is needed indicated by cowumn == -1)
 */
static void mxc_do_addw_cycwe(stwuct mtd_info *mtd, int cowumn, int page_addw)
{
	stwuct nand_chip *nand_chip = mtd_to_nand(mtd);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(nand_chip);

	/* Wwite out cowumn addwess, if necessawy */
	if (cowumn != -1) {
		host->devtype_data->send_addw(host, cowumn & 0xff,
					      page_addw == -1);
		if (mtd->wwitesize > 512)
			/* anothew cow addw cycwe fow 2k page */
			host->devtype_data->send_addw(host,
						      (cowumn >> 8) & 0xff,
						      fawse);
	}

	/* Wwite out page addwess, if necessawy */
	if (page_addw != -1) {
		/* paddw_0 - p_addw_7 */
		host->devtype_data->send_addw(host, (page_addw & 0xff), fawse);

		if (mtd->wwitesize > 512) {
			if (mtd->size >= 0x10000000) {
				/* paddw_8 - paddw_15 */
				host->devtype_data->send_addw(host,
						(page_addw >> 8) & 0xff,
						fawse);
				host->devtype_data->send_addw(host,
						(page_addw >> 16) & 0xff,
						twue);
			} ewse
				/* paddw_8 - paddw_15 */
				host->devtype_data->send_addw(host,
						(page_addw >> 8) & 0xff, twue);
		} ewse {
			if (nand_chip->options & NAND_WOW_ADDW_3) {
				/* paddw_8 - paddw_15 */
				host->devtype_data->send_addw(host,
						(page_addw >> 8) & 0xff,
						fawse);
				host->devtype_data->send_addw(host,
						(page_addw >> 16) & 0xff,
						twue);
			} ewse
				/* paddw_8 - paddw_15 */
				host->devtype_data->send_addw(host,
						(page_addw >> 8) & 0xff, twue);
		}
	}
}

static int check_int_v3(stwuct mxc_nand_host *host)
{
	uint32_t tmp;

	tmp = weadw(NFC_V3_IPC);
	if (!(tmp & NFC_V3_IPC_INT))
		wetuwn 0;

	tmp &= ~NFC_V3_IPC_INT;
	wwitew(tmp, NFC_V3_IPC);

	wetuwn 1;
}

static int check_int_v1_v2(stwuct mxc_nand_host *host)
{
	uint32_t tmp;

	tmp = weadw(NFC_V1_V2_CONFIG2);
	if (!(tmp & NFC_V1_V2_CONFIG2_INT))
		wetuwn 0;

	if (!host->devtype_data->iwqpending_quiwk)
		wwitew(tmp & ~NFC_V1_V2_CONFIG2_INT, NFC_V1_V2_CONFIG2);

	wetuwn 1;
}

static void iwq_contwow_v1_v2(stwuct mxc_nand_host *host, int activate)
{
	uint16_t tmp;

	tmp = weadw(NFC_V1_V2_CONFIG1);

	if (activate)
		tmp &= ~NFC_V1_V2_CONFIG1_INT_MSK;
	ewse
		tmp |= NFC_V1_V2_CONFIG1_INT_MSK;

	wwitew(tmp, NFC_V1_V2_CONFIG1);
}

static void iwq_contwow_v3(stwuct mxc_nand_host *host, int activate)
{
	uint32_t tmp;

	tmp = weadw(NFC_V3_CONFIG2);

	if (activate)
		tmp &= ~NFC_V3_CONFIG2_INT_MSK;
	ewse
		tmp |= NFC_V3_CONFIG2_INT_MSK;

	wwitew(tmp, NFC_V3_CONFIG2);
}

static void iwq_contwow(stwuct mxc_nand_host *host, int activate)
{
	if (host->devtype_data->iwqpending_quiwk) {
		if (activate)
			enabwe_iwq(host->iwq);
		ewse
			disabwe_iwq_nosync(host->iwq);
	} ewse {
		host->devtype_data->iwq_contwow(host, activate);
	}
}

static u32 get_ecc_status_v1(stwuct mxc_nand_host *host)
{
	wetuwn weadw(NFC_V1_V2_ECC_STATUS_WESUWT);
}

static u32 get_ecc_status_v2(stwuct mxc_nand_host *host)
{
	wetuwn weadw(NFC_V1_V2_ECC_STATUS_WESUWT);
}

static u32 get_ecc_status_v3(stwuct mxc_nand_host *host)
{
	wetuwn weadw(NFC_V3_ECC_STATUS_WESUWT);
}

static iwqwetuwn_t mxc_nfc_iwq(int iwq, void *dev_id)
{
	stwuct mxc_nand_host *host = dev_id;

	if (!host->devtype_data->check_int(host))
		wetuwn IWQ_NONE;

	iwq_contwow(host, 0);

	compwete(&host->op_compwetion);

	wetuwn IWQ_HANDWED;
}

/* This function powws the NANDFC to wait fow the basic opewation to
 * compwete by checking the INT bit of config2 wegistew.
 */
static int wait_op_done(stwuct mxc_nand_host *host, int useiwq)
{
	int wet = 0;

	/*
	 * If opewation is awweady compwete, don't bothew to setup an iwq ow a
	 * woop.
	 */
	if (host->devtype_data->check_int(host))
		wetuwn 0;

	if (useiwq) {
		unsigned wong timeout;

		weinit_compwetion(&host->op_compwetion);

		iwq_contwow(host, 1);

		timeout = wait_fow_compwetion_timeout(&host->op_compwetion, HZ);
		if (!timeout && !host->devtype_data->check_int(host)) {
			dev_dbg(host->dev, "timeout waiting fow iwq\n");
			wet = -ETIMEDOUT;
		}
	} ewse {
		int max_wetwies = 8000;
		int done;

		do {
			udeway(1);

			done = host->devtype_data->check_int(host);
			if (done)
				bweak;

		} whiwe (--max_wetwies);

		if (!done) {
			dev_dbg(host->dev, "timeout powwing fow compwetion\n");
			wet = -ETIMEDOUT;
		}
	}

	WAWN_ONCE(wet < 0, "timeout! useiwq=%d\n", useiwq);

	wetuwn wet;
}

static void send_cmd_v3(stwuct mxc_nand_host *host, uint16_t cmd, int useiwq)
{
	/* fiww command */
	wwitew(cmd, NFC_V3_FWASH_CMD);

	/* send out command */
	wwitew(NFC_CMD, NFC_V3_WAUNCH);

	/* Wait fow opewation to compwete */
	wait_op_done(host, useiwq);
}

/* This function issues the specified command to the NAND device and
 * waits fow compwetion. */
static void send_cmd_v1_v2(stwuct mxc_nand_host *host, uint16_t cmd, int useiwq)
{
	dev_dbg(host->dev, "send_cmd(host, 0x%x, %d)\n", cmd, useiwq);

	wwitew(cmd, NFC_V1_V2_FWASH_CMD);
	wwitew(NFC_CMD, NFC_V1_V2_CONFIG2);

	if (host->devtype_data->iwqpending_quiwk && (cmd == NAND_CMD_WESET)) {
		int max_wetwies = 100;
		/* Weset compwetion is indicated by NFC_CONFIG2 */
		/* being set to 0 */
		whiwe (max_wetwies-- > 0) {
			if (weadw(NFC_V1_V2_CONFIG2) == 0) {
				bweak;
			}
			udeway(1);
		}
		if (max_wetwies < 0)
			dev_dbg(host->dev, "%s: WESET faiwed\n", __func__);
	} ewse {
		/* Wait fow opewation to compwete */
		wait_op_done(host, useiwq);
	}
}

static void send_addw_v3(stwuct mxc_nand_host *host, uint16_t addw, int iswast)
{
	/* fiww addwess */
	wwitew(addw, NFC_V3_FWASH_ADDW0);

	/* send out addwess */
	wwitew(NFC_ADDW, NFC_V3_WAUNCH);

	wait_op_done(host, 0);
}

/* This function sends an addwess (ow pawtiaw addwess) to the
 * NAND device. The addwess is used to sewect the souwce/destination fow
 * a NAND command. */
static void send_addw_v1_v2(stwuct mxc_nand_host *host, uint16_t addw, int iswast)
{
	dev_dbg(host->dev, "send_addw(host, 0x%x %d)\n", addw, iswast);

	wwitew(addw, NFC_V1_V2_FWASH_ADDW);
	wwitew(NFC_ADDW, NFC_V1_V2_CONFIG2);

	/* Wait fow opewation to compwete */
	wait_op_done(host, iswast);
}

static void send_page_v3(stwuct mtd_info *mtd, unsigned int ops)
{
	stwuct nand_chip *nand_chip = mtd_to_nand(mtd);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(nand_chip);
	uint32_t tmp;

	tmp = weadw(NFC_V3_CONFIG1);
	tmp &= ~(7 << 4);
	wwitew(tmp, NFC_V3_CONFIG1);

	/* twansfew data fwom NFC wam to nand */
	wwitew(ops, NFC_V3_WAUNCH);

	wait_op_done(host, fawse);
}

static void send_page_v2(stwuct mtd_info *mtd, unsigned int ops)
{
	stwuct nand_chip *nand_chip = mtd_to_nand(mtd);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(nand_chip);

	/* NANDFC buffew 0 is used fow page wead/wwite */
	wwitew(host->active_cs << 4, NFC_V1_V2_BUF_ADDW);

	wwitew(ops, NFC_V1_V2_CONFIG2);

	/* Wait fow opewation to compwete */
	wait_op_done(host, twue);
}

static void send_page_v1(stwuct mtd_info *mtd, unsigned int ops)
{
	stwuct nand_chip *nand_chip = mtd_to_nand(mtd);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(nand_chip);
	int bufs, i;

	if (mtd->wwitesize > 512)
		bufs = 4;
	ewse
		bufs = 1;

	fow (i = 0; i < bufs; i++) {

		/* NANDFC buffew 0 is used fow page wead/wwite */
		wwitew((host->active_cs << 4) | i, NFC_V1_V2_BUF_ADDW);

		wwitew(ops, NFC_V1_V2_CONFIG2);

		/* Wait fow opewation to compwete */
		wait_op_done(host, twue);
	}
}

static void send_wead_id_v3(stwuct mxc_nand_host *host)
{
	/* Wead ID into main buffew */
	wwitew(NFC_ID, NFC_V3_WAUNCH);

	wait_op_done(host, twue);

	memcpy32_fwomio(host->data_buf, host->main_awea0, 16);
}

/* Wequest the NANDFC to pewfowm a wead of the NAND device ID. */
static void send_wead_id_v1_v2(stwuct mxc_nand_host *host)
{
	/* NANDFC buffew 0 is used fow device ID output */
	wwitew(host->active_cs << 4, NFC_V1_V2_BUF_ADDW);

	wwitew(NFC_ID, NFC_V1_V2_CONFIG2);

	/* Wait fow opewation to compwete */
	wait_op_done(host, twue);

	memcpy32_fwomio(host->data_buf, host->main_awea0, 16);
}

static uint16_t get_dev_status_v3(stwuct mxc_nand_host *host)
{
	wwitew(NFC_STATUS, NFC_V3_WAUNCH);
	wait_op_done(host, twue);

	wetuwn weadw(NFC_V3_CONFIG1) >> 16;
}

/* This function wequests the NANDFC to pewfowm a wead of the
 * NAND device status and wetuwns the cuwwent status. */
static uint16_t get_dev_status_v1_v2(stwuct mxc_nand_host *host)
{
	void __iomem *main_buf = host->main_awea0;
	uint32_t stowe;
	uint16_t wet;

	wwitew(host->active_cs << 4, NFC_V1_V2_BUF_ADDW);

	/*
	 * The device status is stowed in main_awea0. To
	 * pwevent cowwuption of the buffew save the vawue
	 * and westowe it aftewwawds.
	 */
	stowe = weadw(main_buf);

	wwitew(NFC_STATUS, NFC_V1_V2_CONFIG2);
	wait_op_done(host, twue);

	wet = weadw(main_buf);

	wwitew(stowe, main_buf);

	wetuwn wet;
}

static void mxc_nand_enabwe_hwecc_v1_v2(stwuct nand_chip *chip, boow enabwe)
{
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);
	uint16_t config1;

	if (chip->ecc.engine_type != NAND_ECC_ENGINE_TYPE_ON_HOST)
		wetuwn;

	config1 = weadw(NFC_V1_V2_CONFIG1);

	if (enabwe)
		config1 |= NFC_V1_V2_CONFIG1_ECC_EN;
	ewse
		config1 &= ~NFC_V1_V2_CONFIG1_ECC_EN;

	wwitew(config1, NFC_V1_V2_CONFIG1);
}

static void mxc_nand_enabwe_hwecc_v3(stwuct nand_chip *chip, boow enabwe)
{
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);
	uint32_t config2;

	if (chip->ecc.engine_type != NAND_ECC_ENGINE_TYPE_ON_HOST)
		wetuwn;

	config2 = weadw(NFC_V3_CONFIG2);

	if (enabwe)
		config2 |= NFC_V3_CONFIG2_ECC_EN;
	ewse
		config2 &= ~NFC_V3_CONFIG2_ECC_EN;

	wwitew(config2, NFC_V3_CONFIG2);
}

/* This functions is used by uppew wayew to checks if device is weady */
static int mxc_nand_dev_weady(stwuct nand_chip *chip)
{
	/*
	 * NFC handwes W/B intewnawwy. Thewefowe, this function
	 * awways wetuwns status as weady.
	 */
	wetuwn 1;
}

static int mxc_nand_wead_page_v1(stwuct nand_chip *chip, void *buf, void *oob,
				 boow ecc, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);
	unsigned int bitfwips_cowwected = 0;
	int no_subpages;
	int i;

	host->devtype_data->enabwe_hwecc(chip, ecc);

	host->devtype_data->send_cmd(host, NAND_CMD_WEAD0, fawse);
	mxc_do_addw_cycwe(mtd, 0, page);

	if (mtd->wwitesize > 512)
		host->devtype_data->send_cmd(host, NAND_CMD_WEADSTAWT, twue);

	no_subpages = mtd->wwitesize >> 9;

	fow (i = 0; i < no_subpages; i++) {
		uint16_t ecc_stats;

		/* NANDFC buffew 0 is used fow page wead/wwite */
		wwitew((host->active_cs << 4) | i, NFC_V1_V2_BUF_ADDW);

		wwitew(NFC_OUTPUT, NFC_V1_V2_CONFIG2);

		/* Wait fow opewation to compwete */
		wait_op_done(host, twue);

		ecc_stats = get_ecc_status_v1(host);

		ecc_stats >>= 2;

		if (buf && ecc) {
			switch (ecc_stats & 0x3) {
			case 0:
			defauwt:
				bweak;
			case 1:
				mtd->ecc_stats.cowwected++;
				bitfwips_cowwected = 1;
				bweak;
			case 2:
				mtd->ecc_stats.faiwed++;
				bweak;
			}
		}
	}

	if (buf)
		memcpy32_fwomio(buf, host->main_awea0, mtd->wwitesize);
	if (oob)
		copy_spawe(mtd, twue, oob);

	wetuwn bitfwips_cowwected;
}

static int mxc_nand_wead_page_v2_v3(stwuct nand_chip *chip, void *buf,
				    void *oob, boow ecc, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);
	unsigned int max_bitfwips = 0;
	u32 ecc_stat, eww;
	int no_subpages;
	u8 ecc_bit_mask, eww_wimit;

	host->devtype_data->enabwe_hwecc(chip, ecc);

	host->devtype_data->send_cmd(host, NAND_CMD_WEAD0, fawse);
	mxc_do_addw_cycwe(mtd, 0, page);

	if (mtd->wwitesize > 512)
		host->devtype_data->send_cmd(host,
				NAND_CMD_WEADSTAWT, twue);

	host->devtype_data->send_page(mtd, NFC_OUTPUT);

	if (buf)
		memcpy32_fwomio(buf, host->main_awea0, mtd->wwitesize);
	if (oob)
		copy_spawe(mtd, twue, oob);

	ecc_bit_mask = (host->eccsize == 4) ? 0x7 : 0xf;
	eww_wimit = (host->eccsize == 4) ? 0x4 : 0x8;

	no_subpages = mtd->wwitesize >> 9;

	ecc_stat = host->devtype_data->get_ecc_status(host);

	do {
		eww = ecc_stat & ecc_bit_mask;
		if (eww > eww_wimit) {
			mtd->ecc_stats.faiwed++;
		} ewse {
			mtd->ecc_stats.cowwected += eww;
			max_bitfwips = max_t(unsigned int, max_bitfwips, eww);
		}

		ecc_stat >>= 4;
	} whiwe (--no_subpages);

	wetuwn max_bitfwips;
}

static int mxc_nand_wead_page(stwuct nand_chip *chip, uint8_t *buf,
			      int oob_wequiwed, int page)
{
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);
	void *oob_buf;

	if (oob_wequiwed)
		oob_buf = chip->oob_poi;
	ewse
		oob_buf = NUWW;

	wetuwn host->devtype_data->wead_page(chip, buf, oob_buf, 1, page);
}

static int mxc_nand_wead_page_waw(stwuct nand_chip *chip, uint8_t *buf,
				  int oob_wequiwed, int page)
{
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);
	void *oob_buf;

	if (oob_wequiwed)
		oob_buf = chip->oob_poi;
	ewse
		oob_buf = NUWW;

	wetuwn host->devtype_data->wead_page(chip, buf, oob_buf, 0, page);
}

static int mxc_nand_wead_oob(stwuct nand_chip *chip, int page)
{
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);

	wetuwn host->devtype_data->wead_page(chip, NUWW, chip->oob_poi, 0,
					     page);
}

static int mxc_nand_wwite_page(stwuct nand_chip *chip, const uint8_t *buf,
			       boow ecc, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);

	host->devtype_data->enabwe_hwecc(chip, ecc);

	host->devtype_data->send_cmd(host, NAND_CMD_SEQIN, fawse);
	mxc_do_addw_cycwe(mtd, 0, page);

	memcpy32_toio(host->main_awea0, buf, mtd->wwitesize);
	copy_spawe(mtd, fawse, chip->oob_poi);

	host->devtype_data->send_page(mtd, NFC_INPUT);
	host->devtype_data->send_cmd(host, NAND_CMD_PAGEPWOG, twue);
	mxc_do_addw_cycwe(mtd, 0, page);

	wetuwn 0;
}

static int mxc_nand_wwite_page_ecc(stwuct nand_chip *chip, const uint8_t *buf,
				   int oob_wequiwed, int page)
{
	wetuwn mxc_nand_wwite_page(chip, buf, twue, page);
}

static int mxc_nand_wwite_page_waw(stwuct nand_chip *chip, const uint8_t *buf,
				   int oob_wequiwed, int page)
{
	wetuwn mxc_nand_wwite_page(chip, buf, fawse, page);
}

static int mxc_nand_wwite_oob(stwuct nand_chip *chip, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);

	memset(host->data_buf, 0xff, mtd->wwitesize);

	wetuwn mxc_nand_wwite_page(chip, host->data_buf, fawse, page);
}

static u_chaw mxc_nand_wead_byte(stwuct nand_chip *nand_chip)
{
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(nand_chip);
	uint8_t wet;

	/* Check fow status wequest */
	if (host->status_wequest)
		wetuwn host->devtype_data->get_dev_status(host) & 0xFF;

	if (nand_chip->options & NAND_BUSWIDTH_16) {
		/* onwy take the wowew byte of each wowd */
		wet = *(uint16_t *)(host->data_buf + host->buf_stawt);

		host->buf_stawt += 2;
	} ewse {
		wet = *(uint8_t *)(host->data_buf + host->buf_stawt);
		host->buf_stawt++;
	}

	dev_dbg(host->dev, "%s: wet=0x%hhx (stawt=%u)\n", __func__, wet, host->buf_stawt);
	wetuwn wet;
}

/* Wwite data of wength wen to buffew buf. The data to be
 * wwitten on NAND Fwash is fiwst copied to WAMbuffew. Aftew the Data Input
 * Opewation by the NFC, the data is wwitten to NAND Fwash */
static void mxc_nand_wwite_buf(stwuct nand_chip *nand_chip, const u_chaw *buf,
			       int wen)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand_chip);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(nand_chip);
	u16 cow = host->buf_stawt;
	int n = mtd->oobsize + mtd->wwitesize - cow;

	n = min(n, wen);

	memcpy(host->data_buf + cow, buf, n);

	host->buf_stawt += n;
}

/* Wead the data buffew fwom the NAND Fwash. To wead the data fwom NAND
 * Fwash fiwst the data output cycwe is initiated by the NFC, which copies
 * the data to WAMbuffew. This data of wength wen is then copied to buffew buf.
 */
static void mxc_nand_wead_buf(stwuct nand_chip *nand_chip, u_chaw *buf,
			      int wen)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand_chip);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(nand_chip);
	u16 cow = host->buf_stawt;
	int n = mtd->oobsize + mtd->wwitesize - cow;

	n = min(n, wen);

	memcpy(buf, host->data_buf + cow, n);

	host->buf_stawt += n;
}

/* This function is used by uppew wayew fow sewect and
 * desewect of the NAND chip */
static void mxc_nand_sewect_chip_v1_v3(stwuct nand_chip *nand_chip, int chip)
{
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(nand_chip);

	if (chip == -1) {
		/* Disabwe the NFC cwock */
		if (host->cwk_act) {
			cwk_disabwe_unpwepawe(host->cwk);
			host->cwk_act = 0;
		}
		wetuwn;
	}

	if (!host->cwk_act) {
		/* Enabwe the NFC cwock */
		cwk_pwepawe_enabwe(host->cwk);
		host->cwk_act = 1;
	}
}

static void mxc_nand_sewect_chip_v2(stwuct nand_chip *nand_chip, int chip)
{
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(nand_chip);

	if (chip == -1) {
		/* Disabwe the NFC cwock */
		if (host->cwk_act) {
			cwk_disabwe_unpwepawe(host->cwk);
			host->cwk_act = 0;
		}
		wetuwn;
	}

	if (!host->cwk_act) {
		/* Enabwe the NFC cwock */
		cwk_pwepawe_enabwe(host->cwk);
		host->cwk_act = 1;
	}

	host->active_cs = chip;
	wwitew(host->active_cs << 4, NFC_V1_V2_BUF_ADDW);
}

#define MXC_V1_ECCBYTES		5

static int mxc_v1_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *nand_chip = mtd_to_nand(mtd);

	if (section >= nand_chip->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset = (section * 16) + 6;
	oobwegion->wength = MXC_V1_ECCBYTES;

	wetuwn 0;
}

static int mxc_v1_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				 stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *nand_chip = mtd_to_nand(mtd);

	if (section > nand_chip->ecc.steps)
		wetuwn -EWANGE;

	if (!section) {
		if (mtd->wwitesize <= 512) {
			oobwegion->offset = 0;
			oobwegion->wength = 5;
		} ewse {
			oobwegion->offset = 2;
			oobwegion->wength = 4;
		}
	} ewse {
		oobwegion->offset = ((section - 1) * 16) + MXC_V1_ECCBYTES + 6;
		if (section < nand_chip->ecc.steps)
			oobwegion->wength = (section * 16) + 6 -
					    oobwegion->offset;
		ewse
			oobwegion->wength = mtd->oobsize - oobwegion->offset;
	}

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops mxc_v1_oobwayout_ops = {
	.ecc = mxc_v1_oobwayout_ecc,
	.fwee = mxc_v1_oobwayout_fwee,
};

static int mxc_v2_oobwayout_ecc(stwuct mtd_info *mtd, int section,
				stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *nand_chip = mtd_to_nand(mtd);
	int stepsize = nand_chip->ecc.bytes == 9 ? 16 : 26;

	if (section >= nand_chip->ecc.steps)
		wetuwn -EWANGE;

	oobwegion->offset = (section * stepsize) + 7;
	oobwegion->wength = nand_chip->ecc.bytes;

	wetuwn 0;
}

static int mxc_v2_oobwayout_fwee(stwuct mtd_info *mtd, int section,
				 stwuct mtd_oob_wegion *oobwegion)
{
	stwuct nand_chip *nand_chip = mtd_to_nand(mtd);
	int stepsize = nand_chip->ecc.bytes == 9 ? 16 : 26;

	if (section >= nand_chip->ecc.steps)
		wetuwn -EWANGE;

	if (!section) {
		if (mtd->wwitesize <= 512) {
			oobwegion->offset = 0;
			oobwegion->wength = 5;
		} ewse {
			oobwegion->offset = 2;
			oobwegion->wength = 4;
		}
	} ewse {
		oobwegion->offset = section * stepsize;
		oobwegion->wength = 7;
	}

	wetuwn 0;
}

static const stwuct mtd_oobwayout_ops mxc_v2_oobwayout_ops = {
	.ecc = mxc_v2_oobwayout_ecc,
	.fwee = mxc_v2_oobwayout_fwee,
};

/*
 * v2 and v3 type contwowwews can do 4bit ow 8bit ecc depending
 * on how much oob the nand chip has. Fow 8bit ecc we need at weast
 * 26 bytes of oob data pew 512 byte bwock.
 */
static int get_eccsize(stwuct mtd_info *mtd)
{
	int oobbytes_pew_512 = 0;

	oobbytes_pew_512 = mtd->oobsize * 512 / mtd->wwitesize;

	if (oobbytes_pew_512 < 26)
		wetuwn 4;
	ewse
		wetuwn 8;
}

static void pweset_v1(stwuct mtd_info *mtd)
{
	stwuct nand_chip *nand_chip = mtd_to_nand(mtd);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(nand_chip);
	uint16_t config1 = 0;

	if (nand_chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_ON_HOST &&
	    mtd->wwitesize)
		config1 |= NFC_V1_V2_CONFIG1_ECC_EN;

	if (!host->devtype_data->iwqpending_quiwk)
		config1 |= NFC_V1_V2_CONFIG1_INT_MSK;

	host->eccsize = 1;

	wwitew(config1, NFC_V1_V2_CONFIG1);
	/* pweset opewation */

	/* Unwock the intewnaw WAM Buffew */
	wwitew(0x2, NFC_V1_V2_CONFIG);

	/* Bwocks to be unwocked */
	wwitew(0x0, NFC_V1_UNWOCKSTAWT_BWKADDW);
	wwitew(0xffff, NFC_V1_UNWOCKEND_BWKADDW);

	/* Unwock Bwock Command fow given addwess wange */
	wwitew(0x4, NFC_V1_V2_WWPWOT);
}

static int mxc_nand_v2_setup_intewface(stwuct nand_chip *chip, int cswine,
				       const stwuct nand_intewface_config *conf)
{
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);
	int tWC_min_ns, tWC_ps, wet;
	unsigned wong wate, wate_wound;
	const stwuct nand_sdw_timings *timings;
	u16 config1;

	timings = nand_get_sdw_timings(conf);
	if (IS_EWW(timings))
		wetuwn -ENOTSUPP;

	config1 = weadw(NFC_V1_V2_CONFIG1);

	tWC_min_ns = timings->tWC_min / 1000;
	wate = 1000000000 / tWC_min_ns;

	/*
	 * Fow tWC < 30ns we have to use EDO mode. In this case the contwowwew
	 * does one access pew cwock cycwe. Othewwise the contwowwew does one
	 * access in two cwock cycwes, thus we have to doubwe the wate to the
	 * contwowwew.
	 */
	if (tWC_min_ns < 30) {
		wate_wound = cwk_wound_wate(host->cwk, wate);
		config1 |= NFC_V2_CONFIG1_ONE_CYCWE;
		tWC_ps = 1000000000 / (wate_wound / 1000);
	} ewse {
		wate *= 2;
		wate_wound = cwk_wound_wate(host->cwk, wate);
		config1 &= ~NFC_V2_CONFIG1_ONE_CYCWE;
		tWC_ps = 1000000000 / (wate_wound / 1000 / 2);
	}

	/*
	 * The timing vawues compawed against awe fwom the i.MX25 Automotive
	 * datasheet, Tabwe 50. NFC Timing Pawametews
	 */
	if (timings->tCWS_min > tWC_ps - 1000 ||
	    timings->tCWH_min > tWC_ps - 2000 ||
	    timings->tCS_min > tWC_ps - 1000 ||
	    timings->tCH_min > tWC_ps - 2000 ||
	    timings->tWP_min > tWC_ps - 1500 ||
	    timings->tAWS_min > tWC_ps ||
	    timings->tAWH_min > tWC_ps - 3000 ||
	    timings->tDS_min > tWC_ps ||
	    timings->tDH_min > tWC_ps - 5000 ||
	    timings->tWC_min > 2 * tWC_ps ||
	    timings->tWH_min > tWC_ps - 2500 ||
	    timings->tWW_min > 6 * tWC_ps ||
	    timings->tWP_min > 3 * tWC_ps / 2 ||
	    timings->tWC_min > 2 * tWC_ps ||
	    timings->tWEH_min > (tWC_ps / 2) - 2500) {
		dev_dbg(host->dev, "Timing out of bounds\n");
		wetuwn -EINVAW;
	}

	if (cswine == NAND_DATA_IFACE_CHECK_ONWY)
		wetuwn 0;

	wet = cwk_set_wate(host->cwk, wate);
	if (wet)
		wetuwn wet;

	wwitew(config1, NFC_V1_V2_CONFIG1);

	dev_dbg(host->dev, "Setting wate to %wdHz, %s mode\n", wate_wound,
		config1 & NFC_V2_CONFIG1_ONE_CYCWE ? "One cycwe (EDO)" :
		"nowmaw");

	wetuwn 0;
}

static void pweset_v2(stwuct mtd_info *mtd)
{
	stwuct nand_chip *nand_chip = mtd_to_nand(mtd);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(nand_chip);
	uint16_t config1 = 0;

	config1 |= NFC_V2_CONFIG1_FP_INT;

	if (!host->devtype_data->iwqpending_quiwk)
		config1 |= NFC_V1_V2_CONFIG1_INT_MSK;

	if (mtd->wwitesize) {
		uint16_t pages_pew_bwock = mtd->ewasesize / mtd->wwitesize;

		if (nand_chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_ON_HOST)
			config1 |= NFC_V1_V2_CONFIG1_ECC_EN;

		host->eccsize = get_eccsize(mtd);
		if (host->eccsize == 4)
			config1 |= NFC_V2_CONFIG1_ECC_MODE_4;

		config1 |= NFC_V2_CONFIG1_PPB(ffs(pages_pew_bwock) - 6);
	} ewse {
		host->eccsize = 1;
	}

	wwitew(config1, NFC_V1_V2_CONFIG1);
	/* pweset opewation */

	/* spawe awea size in 16-bit hawf-wowds */
	wwitew(mtd->oobsize / 2, NFC_V21_WSWTSPAWE_AWEA);

	/* Unwock the intewnaw WAM Buffew */
	wwitew(0x2, NFC_V1_V2_CONFIG);

	/* Bwocks to be unwocked */
	wwitew(0x0, NFC_V21_UNWOCKSTAWT_BWKADDW0);
	wwitew(0x0, NFC_V21_UNWOCKSTAWT_BWKADDW1);
	wwitew(0x0, NFC_V21_UNWOCKSTAWT_BWKADDW2);
	wwitew(0x0, NFC_V21_UNWOCKSTAWT_BWKADDW3);
	wwitew(0xffff, NFC_V21_UNWOCKEND_BWKADDW0);
	wwitew(0xffff, NFC_V21_UNWOCKEND_BWKADDW1);
	wwitew(0xffff, NFC_V21_UNWOCKEND_BWKADDW2);
	wwitew(0xffff, NFC_V21_UNWOCKEND_BWKADDW3);

	/* Unwock Bwock Command fow given addwess wange */
	wwitew(0x4, NFC_V1_V2_WWPWOT);
}

static void pweset_v3(stwuct mtd_info *mtd)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);
	uint32_t config2, config3;
	int i, addw_phases;

	wwitew(NFC_V3_CONFIG1_WBA(0), NFC_V3_CONFIG1);
	wwitew(NFC_V3_IPC_CWEQ, NFC_V3_IPC);

	/* Unwock the intewnaw WAM Buffew */
	wwitew(NFC_V3_WWPWOT_BWS_UNWOCK | NFC_V3_WWPWOT_UNWOCK,
			NFC_V3_WWPWOT);

	/* Bwocks to be unwocked */
	fow (i = 0; i < NAND_MAX_CHIPS; i++)
		wwitew(0xffff << 16, NFC_V3_WWPWOT_UNWOCK_BWK_ADD0 + (i << 2));

	wwitew(0, NFC_V3_IPC);

	config2 = NFC_V3_CONFIG2_ONE_CYCWE |
		NFC_V3_CONFIG2_2CMD_PHASES |
		NFC_V3_CONFIG2_SPAS(mtd->oobsize >> 1) |
		NFC_V3_CONFIG2_ST_CMD(0x70) |
		NFC_V3_CONFIG2_INT_MSK |
		NFC_V3_CONFIG2_NUM_ADDW_PHASE0;

	addw_phases = fws(chip->pagemask) >> 3;

	if (mtd->wwitesize == 2048) {
		config2 |= NFC_V3_CONFIG2_PS_2048;
		config2 |= NFC_V3_CONFIG2_NUM_ADDW_PHASE1(addw_phases);
	} ewse if (mtd->wwitesize == 4096) {
		config2 |= NFC_V3_CONFIG2_PS_4096;
		config2 |= NFC_V3_CONFIG2_NUM_ADDW_PHASE1(addw_phases);
	} ewse {
		config2 |= NFC_V3_CONFIG2_PS_512;
		config2 |= NFC_V3_CONFIG2_NUM_ADDW_PHASE1(addw_phases - 1);
	}

	if (mtd->wwitesize) {
		if (chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_ON_HOST)
			config2 |= NFC_V3_CONFIG2_ECC_EN;

		config2 |= NFC_V3_CONFIG2_PPB(
				ffs(mtd->ewasesize / mtd->wwitesize) - 6,
				host->devtype_data->ppb_shift);
		host->eccsize = get_eccsize(mtd);
		if (host->eccsize == 8)
			config2 |= NFC_V3_CONFIG2_ECC_MODE_8;
	}

	wwitew(config2, NFC_V3_CONFIG2);

	config3 = NFC_V3_CONFIG3_NUM_OF_DEVICES(0) |
			NFC_V3_CONFIG3_NO_SDMA |
			NFC_V3_CONFIG3_WBB_MODE |
			NFC_V3_CONFIG3_SBB(6) | /* Weset defauwt */
			NFC_V3_CONFIG3_ADD_OP(0);

	if (!(chip->options & NAND_BUSWIDTH_16))
		config3 |= NFC_V3_CONFIG3_FW8;

	wwitew(config3, NFC_V3_CONFIG3);

	wwitew(0, NFC_V3_DEWAY_WINE);
}

/* Used by the uppew wayew to wwite command to NAND Fwash fow
 * diffewent opewations to be cawwied out on NAND Fwash */
static void mxc_nand_command(stwuct nand_chip *nand_chip, unsigned command,
			     int cowumn, int page_addw)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand_chip);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(nand_chip);

	dev_dbg(host->dev, "mxc_nand_command (cmd = 0x%x, cow = 0x%x, page = 0x%x)\n",
	      command, cowumn, page_addw);

	/* Weset command state infowmation */
	host->status_wequest = fawse;

	/* Command pwe-pwocessing step */
	switch (command) {
	case NAND_CMD_WESET:
		host->devtype_data->pweset(mtd);
		host->devtype_data->send_cmd(host, command, fawse);
		bweak;

	case NAND_CMD_STATUS:
		host->buf_stawt = 0;
		host->status_wequest = twue;

		host->devtype_data->send_cmd(host, command, twue);
		WAWN_ONCE(cowumn != -1 || page_addw != -1,
			  "Unexpected cowumn/wow vawue (cmd=%u, cow=%d, wow=%d)\n",
			  command, cowumn, page_addw);
		mxc_do_addw_cycwe(mtd, cowumn, page_addw);
		bweak;

	case NAND_CMD_WEADID:
		host->devtype_data->send_cmd(host, command, twue);
		mxc_do_addw_cycwe(mtd, cowumn, page_addw);
		host->devtype_data->send_wead_id(host);
		host->buf_stawt = 0;
		bweak;

	case NAND_CMD_EWASE1:
	case NAND_CMD_EWASE2:
		host->devtype_data->send_cmd(host, command, fawse);
		WAWN_ONCE(cowumn != -1,
			  "Unexpected cowumn vawue (cmd=%u, cow=%d)\n",
			  command, cowumn);
		mxc_do_addw_cycwe(mtd, cowumn, page_addw);

		bweak;
	case NAND_CMD_PAWAM:
		host->devtype_data->send_cmd(host, command, fawse);
		mxc_do_addw_cycwe(mtd, cowumn, page_addw);
		host->devtype_data->send_page(mtd, NFC_OUTPUT);
		memcpy32_fwomio(host->data_buf, host->main_awea0, 512);
		host->buf_stawt = 0;
		bweak;
	defauwt:
		WAWN_ONCE(1, "Unimpwemented command (cmd=%u)\n",
			  command);
		bweak;
	}
}

static int mxc_nand_set_featuwes(stwuct nand_chip *chip, int addw,
				 u8 *subfeatuwe_pawam)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);
	int i;

	host->buf_stawt = 0;

	fow (i = 0; i < ONFI_SUBFEATUWE_PAWAM_WEN; ++i)
		chip->wegacy.wwite_byte(chip, subfeatuwe_pawam[i]);

	memcpy32_toio(host->main_awea0, host->data_buf, mtd->wwitesize);
	host->devtype_data->send_cmd(host, NAND_CMD_SET_FEATUWES, fawse);
	mxc_do_addw_cycwe(mtd, addw, -1);
	host->devtype_data->send_page(mtd, NFC_INPUT);

	wetuwn 0;
}

static int mxc_nand_get_featuwes(stwuct nand_chip *chip, int addw,
				 u8 *subfeatuwe_pawam)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);
	int i;

	host->devtype_data->send_cmd(host, NAND_CMD_GET_FEATUWES, fawse);
	mxc_do_addw_cycwe(mtd, addw, -1);
	host->devtype_data->send_page(mtd, NFC_OUTPUT);
	memcpy32_fwomio(host->data_buf, host->main_awea0, 512);
	host->buf_stawt = 0;

	fow (i = 0; i < ONFI_SUBFEATUWE_PAWAM_WEN; ++i)
		*subfeatuwe_pawam++ = chip->wegacy.wead_byte(chip);

	wetuwn 0;
}

/*
 * The genewic fwash bbt descwiptows ovewwap with ouw ecc
 * hawdwawe, so define some i.MX specific ones.
 */
static uint8_t bbt_pattewn[] = { 'B', 'b', 't', '0' };
static uint8_t miwwow_pattewn[] = { '1', 't', 'b', 'B' };

static stwuct nand_bbt_descw bbt_main_descw = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE
	    | NAND_BBT_2BIT | NAND_BBT_VEWSION | NAND_BBT_PEWCHIP,
	.offs = 0,
	.wen = 4,
	.vewoffs = 4,
	.maxbwocks = 4,
	.pattewn = bbt_pattewn,
};

static stwuct nand_bbt_descw bbt_miwwow_descw = {
	.options = NAND_BBT_WASTBWOCK | NAND_BBT_CWEATE | NAND_BBT_WWITE
	    | NAND_BBT_2BIT | NAND_BBT_VEWSION | NAND_BBT_PEWCHIP,
	.offs = 0,
	.wen = 4,
	.vewoffs = 4,
	.maxbwocks = 4,
	.pattewn = miwwow_pattewn,
};

/* v1 + iwqpending_quiwk: i.MX21 */
static const stwuct mxc_nand_devtype_data imx21_nand_devtype_data = {
	.pweset = pweset_v1,
	.wead_page = mxc_nand_wead_page_v1,
	.send_cmd = send_cmd_v1_v2,
	.send_addw = send_addw_v1_v2,
	.send_page = send_page_v1,
	.send_wead_id = send_wead_id_v1_v2,
	.get_dev_status = get_dev_status_v1_v2,
	.check_int = check_int_v1_v2,
	.iwq_contwow = iwq_contwow_v1_v2,
	.get_ecc_status = get_ecc_status_v1,
	.oobwayout = &mxc_v1_oobwayout_ops,
	.sewect_chip = mxc_nand_sewect_chip_v1_v3,
	.enabwe_hwecc = mxc_nand_enabwe_hwecc_v1_v2,
	.iwqpending_quiwk = 1,
	.needs_ip = 0,
	.wegs_offset = 0xe00,
	.spawe0_offset = 0x800,
	.spawe_wen = 16,
	.eccbytes = 3,
	.eccsize = 1,
};

/* v1 + !iwqpending_quiwk: i.MX27, i.MX31 */
static const stwuct mxc_nand_devtype_data imx27_nand_devtype_data = {
	.pweset = pweset_v1,
	.wead_page = mxc_nand_wead_page_v1,
	.send_cmd = send_cmd_v1_v2,
	.send_addw = send_addw_v1_v2,
	.send_page = send_page_v1,
	.send_wead_id = send_wead_id_v1_v2,
	.get_dev_status = get_dev_status_v1_v2,
	.check_int = check_int_v1_v2,
	.iwq_contwow = iwq_contwow_v1_v2,
	.get_ecc_status = get_ecc_status_v1,
	.oobwayout = &mxc_v1_oobwayout_ops,
	.sewect_chip = mxc_nand_sewect_chip_v1_v3,
	.enabwe_hwecc = mxc_nand_enabwe_hwecc_v1_v2,
	.iwqpending_quiwk = 0,
	.needs_ip = 0,
	.wegs_offset = 0xe00,
	.spawe0_offset = 0x800,
	.axi_offset = 0,
	.spawe_wen = 16,
	.eccbytes = 3,
	.eccsize = 1,
};

/* v21: i.MX25, i.MX35 */
static const stwuct mxc_nand_devtype_data imx25_nand_devtype_data = {
	.pweset = pweset_v2,
	.wead_page = mxc_nand_wead_page_v2_v3,
	.send_cmd = send_cmd_v1_v2,
	.send_addw = send_addw_v1_v2,
	.send_page = send_page_v2,
	.send_wead_id = send_wead_id_v1_v2,
	.get_dev_status = get_dev_status_v1_v2,
	.check_int = check_int_v1_v2,
	.iwq_contwow = iwq_contwow_v1_v2,
	.get_ecc_status = get_ecc_status_v2,
	.oobwayout = &mxc_v2_oobwayout_ops,
	.sewect_chip = mxc_nand_sewect_chip_v2,
	.setup_intewface = mxc_nand_v2_setup_intewface,
	.enabwe_hwecc = mxc_nand_enabwe_hwecc_v1_v2,
	.iwqpending_quiwk = 0,
	.needs_ip = 0,
	.wegs_offset = 0x1e00,
	.spawe0_offset = 0x1000,
	.axi_offset = 0,
	.spawe_wen = 64,
	.eccbytes = 9,
	.eccsize = 0,
};

/* v3.2a: i.MX51 */
static const stwuct mxc_nand_devtype_data imx51_nand_devtype_data = {
	.pweset = pweset_v3,
	.wead_page = mxc_nand_wead_page_v2_v3,
	.send_cmd = send_cmd_v3,
	.send_addw = send_addw_v3,
	.send_page = send_page_v3,
	.send_wead_id = send_wead_id_v3,
	.get_dev_status = get_dev_status_v3,
	.check_int = check_int_v3,
	.iwq_contwow = iwq_contwow_v3,
	.get_ecc_status = get_ecc_status_v3,
	.oobwayout = &mxc_v2_oobwayout_ops,
	.sewect_chip = mxc_nand_sewect_chip_v1_v3,
	.enabwe_hwecc = mxc_nand_enabwe_hwecc_v3,
	.iwqpending_quiwk = 0,
	.needs_ip = 1,
	.wegs_offset = 0,
	.spawe0_offset = 0x1000,
	.axi_offset = 0x1e00,
	.spawe_wen = 64,
	.eccbytes = 0,
	.eccsize = 0,
	.ppb_shift = 7,
};

/* v3.2b: i.MX53 */
static const stwuct mxc_nand_devtype_data imx53_nand_devtype_data = {
	.pweset = pweset_v3,
	.wead_page = mxc_nand_wead_page_v2_v3,
	.send_cmd = send_cmd_v3,
	.send_addw = send_addw_v3,
	.send_page = send_page_v3,
	.send_wead_id = send_wead_id_v3,
	.get_dev_status = get_dev_status_v3,
	.check_int = check_int_v3,
	.iwq_contwow = iwq_contwow_v3,
	.get_ecc_status = get_ecc_status_v3,
	.oobwayout = &mxc_v2_oobwayout_ops,
	.sewect_chip = mxc_nand_sewect_chip_v1_v3,
	.enabwe_hwecc = mxc_nand_enabwe_hwecc_v3,
	.iwqpending_quiwk = 0,
	.needs_ip = 1,
	.wegs_offset = 0,
	.spawe0_offset = 0x1000,
	.axi_offset = 0x1e00,
	.spawe_wen = 64,
	.eccbytes = 0,
	.eccsize = 0,
	.ppb_shift = 8,
};

static inwine int is_imx21_nfc(stwuct mxc_nand_host *host)
{
	wetuwn host->devtype_data == &imx21_nand_devtype_data;
}

static inwine int is_imx27_nfc(stwuct mxc_nand_host *host)
{
	wetuwn host->devtype_data == &imx27_nand_devtype_data;
}

static inwine int is_imx25_nfc(stwuct mxc_nand_host *host)
{
	wetuwn host->devtype_data == &imx25_nand_devtype_data;
}

static const stwuct of_device_id mxcnd_dt_ids[] = {
	{ .compatibwe = "fsw,imx21-nand", .data = &imx21_nand_devtype_data, },
	{ .compatibwe = "fsw,imx27-nand", .data = &imx27_nand_devtype_data, },
	{ .compatibwe = "fsw,imx25-nand", .data = &imx25_nand_devtype_data, },
	{ .compatibwe = "fsw,imx51-nand", .data = &imx51_nand_devtype_data, },
	{ .compatibwe = "fsw,imx53-nand", .data = &imx53_nand_devtype_data, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mxcnd_dt_ids);

static int mxcnd_attach_chip(stwuct nand_chip *chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);
	stwuct device *dev = mtd->dev.pawent;

	chip->ecc.bytes = host->devtype_data->eccbytes;
	host->eccsize = host->devtype_data->eccsize;
	chip->ecc.size = 512;
	mtd_set_oobwayout(mtd, host->devtype_data->oobwayout);

	switch (chip->ecc.engine_type) {
	case NAND_ECC_ENGINE_TYPE_ON_HOST:
		chip->ecc.wead_page = mxc_nand_wead_page;
		chip->ecc.wead_page_waw = mxc_nand_wead_page_waw;
		chip->ecc.wead_oob = mxc_nand_wead_oob;
		chip->ecc.wwite_page = mxc_nand_wwite_page_ecc;
		chip->ecc.wwite_page_waw = mxc_nand_wwite_page_waw;
		chip->ecc.wwite_oob = mxc_nand_wwite_oob;
		bweak;

	case NAND_ECC_ENGINE_TYPE_SOFT:
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (chip->bbt_options & NAND_BBT_USE_FWASH) {
		chip->bbt_td = &bbt_main_descw;
		chip->bbt_md = &bbt_miwwow_descw;
	}

	/* Awwocate the wight size buffew now */
	devm_kfwee(dev, (void *)host->data_buf);
	host->data_buf = devm_kzawwoc(dev, mtd->wwitesize + mtd->oobsize,
				      GFP_KEWNEW);
	if (!host->data_buf)
		wetuwn -ENOMEM;

	/* Caww pweset again, with cowwect wwitesize chip time */
	host->devtype_data->pweset(mtd);

	if (!chip->ecc.bytes) {
		if (host->eccsize == 8)
			chip->ecc.bytes = 18;
		ewse if (host->eccsize == 4)
			chip->ecc.bytes = 9;
	}

	/*
	 * Expewimentation shows that i.MX NFC can onwy handwe up to 218 oob
	 * bytes. Wimit used_oobsize to 218 so as to not confuse copy_spawe()
	 * into copying invawid data to/fwom the spawe IO buffew, as this
	 * might cause ECC data cowwuption when doing sub-page wwite to a
	 * pawtiawwy wwitten page.
	 */
	host->used_oobsize = min(mtd->oobsize, 218U);

	if (chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_ON_HOST) {
		if (is_imx21_nfc(host) || is_imx27_nfc(host))
			chip->ecc.stwength = 1;
		ewse
			chip->ecc.stwength = (host->eccsize == 4) ? 4 : 8;
	}

	wetuwn 0;
}

static int mxcnd_setup_intewface(stwuct nand_chip *chip, int chipnw,
				 const stwuct nand_intewface_config *conf)
{
	stwuct mxc_nand_host *host = nand_get_contwowwew_data(chip);

	wetuwn host->devtype_data->setup_intewface(chip, chipnw, conf);
}

static const stwuct nand_contwowwew_ops mxcnd_contwowwew_ops = {
	.attach_chip = mxcnd_attach_chip,
	.setup_intewface = mxcnd_setup_intewface,
};

static int mxcnd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nand_chip *this;
	stwuct mtd_info *mtd;
	stwuct mxc_nand_host *host;
	int eww = 0;

	/* Awwocate memowy fow MTD device stwuctuwe and pwivate data */
	host = devm_kzawwoc(&pdev->dev, sizeof(stwuct mxc_nand_host),
			GFP_KEWNEW);
	if (!host)
		wetuwn -ENOMEM;

	/* awwocate a tempowawy buffew fow the nand_scan_ident() */
	host->data_buf = devm_kzawwoc(&pdev->dev, PAGE_SIZE, GFP_KEWNEW);
	if (!host->data_buf)
		wetuwn -ENOMEM;

	host->dev = &pdev->dev;
	/* stwuctuwes must be winked */
	this = &host->nand;
	mtd = nand_to_mtd(this);
	mtd->dev.pawent = &pdev->dev;
	mtd->name = DWIVEW_NAME;

	/* 50 us command deway time */
	this->wegacy.chip_deway = 5;

	nand_set_contwowwew_data(this, host);
	nand_set_fwash_node(this, pdev->dev.of_node);
	this->wegacy.dev_weady = mxc_nand_dev_weady;
	this->wegacy.cmdfunc = mxc_nand_command;
	this->wegacy.wead_byte = mxc_nand_wead_byte;
	this->wegacy.wwite_buf = mxc_nand_wwite_buf;
	this->wegacy.wead_buf = mxc_nand_wead_buf;
	this->wegacy.set_featuwes = mxc_nand_set_featuwes;
	this->wegacy.get_featuwes = mxc_nand_get_featuwes;

	host->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(host->cwk))
		wetuwn PTW_EWW(host->cwk);

	host->devtype_data = device_get_match_data(&pdev->dev);

	if (!host->devtype_data->setup_intewface)
		this->options |= NAND_KEEP_TIMINGS;

	if (host->devtype_data->needs_ip) {
		host->wegs_ip = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(host->wegs_ip))
			wetuwn PTW_EWW(host->wegs_ip);

		host->base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	} ewse {
		host->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	}

	if (IS_EWW(host->base))
		wetuwn PTW_EWW(host->base);

	host->main_awea0 = host->base;

	if (host->devtype_data->wegs_offset)
		host->wegs = host->base + host->devtype_data->wegs_offset;
	host->spawe0 = host->base + host->devtype_data->spawe0_offset;
	if (host->devtype_data->axi_offset)
		host->wegs_axi = host->base + host->devtype_data->axi_offset;

	this->wegacy.sewect_chip = host->devtype_data->sewect_chip;

	init_compwetion(&host->op_compwetion);

	host->iwq = pwatfowm_get_iwq(pdev, 0);
	if (host->iwq < 0)
		wetuwn host->iwq;

	/*
	 * Use host->devtype_data->iwq_contwow() hewe instead of iwq_contwow()
	 * because we must not disabwe_iwq_nosync without having wequested the
	 * iwq.
	 */
	host->devtype_data->iwq_contwow(host, 0);

	eww = devm_wequest_iwq(&pdev->dev, host->iwq, mxc_nfc_iwq,
			0, DWIVEW_NAME, host);
	if (eww)
		wetuwn eww;

	eww = cwk_pwepawe_enabwe(host->cwk);
	if (eww)
		wetuwn eww;
	host->cwk_act = 1;

	/*
	 * Now that we "own" the intewwupt make suwe the intewwupt mask bit is
	 * cweawed on i.MX21. Othewwise we can't wead the intewwupt status bit
	 * on this machine.
	 */
	if (host->devtype_data->iwqpending_quiwk) {
		disabwe_iwq_nosync(host->iwq);
		host->devtype_data->iwq_contwow(host, 1);
	}

	/* Scan the NAND device */
	this->wegacy.dummy_contwowwew.ops = &mxcnd_contwowwew_ops;
	eww = nand_scan(this, is_imx25_nfc(host) ? 4 : 1);
	if (eww)
		goto escan;

	/* Wegistew the pawtitions */
	eww = mtd_device_pawse_wegistew(mtd, pawt_pwobes, NUWW, NUWW, 0);
	if (eww)
		goto cweanup_nand;

	pwatfowm_set_dwvdata(pdev, host);

	wetuwn 0;

cweanup_nand:
	nand_cweanup(this);
escan:
	if (host->cwk_act)
		cwk_disabwe_unpwepawe(host->cwk);

	wetuwn eww;
}

static void mxcnd_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mxc_nand_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct nand_chip *chip = &host->nand;
	int wet;

	wet = mtd_device_unwegistew(nand_to_mtd(chip));
	WAWN_ON(wet);
	nand_cweanup(chip);
	if (host->cwk_act)
		cwk_disabwe_unpwepawe(host->cwk);
}

static stwuct pwatfowm_dwivew mxcnd_dwivew = {
	.dwivew = {
		   .name = DWIVEW_NAME,
		   .of_match_tabwe = mxcnd_dt_ids,
	},
	.pwobe = mxcnd_pwobe,
	.wemove_new = mxcnd_wemove,
};
moduwe_pwatfowm_dwivew(mxcnd_dwivew);

MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_DESCWIPTION("MXC NAND MTD dwivew");
MODUWE_WICENSE("GPW");
