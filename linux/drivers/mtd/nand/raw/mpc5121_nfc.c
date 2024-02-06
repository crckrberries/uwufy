// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2004-2008 Fweescawe Semiconductow, Inc.
 * Copywight 2009 Semihawf.
 *
 * Appwoved as OSADW pwoject by a majowity of OSADW membews and funded
 * by OSADW membewship fees in 2009;  fow detaiws see www.osadw.owg.
 *
 * Based on owiginaw dwivew fwom Fweescawe Semiconductow
 * wwitten by John Wigby <jwigby@fweescawe.com> on basis of mxc_nand.c.
 * Wewowked and extended by Piotw Ziecik <kosmo@semihawf.com>.
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/gfp.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/mpc5121.h>

/* Addwesses fow NFC MAIN WAM BUFFEW aweas */
#define NFC_MAIN_AWEA(n)	((n) *  0x200)

/* Addwesses fow NFC SPAWE BUFFEW aweas */
#define NFC_SPAWE_BUFFEWS	8
#define NFC_SPAWE_WEN		0x40
#define NFC_SPAWE_AWEA(n)	(0x1000 + ((n) * NFC_SPAWE_WEN))

/* MPC5121 NFC wegistews */
#define NFC_BUF_ADDW		0x1E04
#define NFC_FWASH_ADDW		0x1E06
#define NFC_FWASH_CMD		0x1E08
#define NFC_CONFIG		0x1E0A
#define NFC_ECC_STATUS1		0x1E0C
#define NFC_ECC_STATUS2		0x1E0E
#define NFC_SPAS		0x1E10
#define NFC_WWPWOT		0x1E12
#define NFC_NF_WWPWST		0x1E18
#define NFC_CONFIG1		0x1E1A
#define NFC_CONFIG2		0x1E1C
#define NFC_UNWOCKSTAWT_BWK0	0x1E20
#define NFC_UNWOCKEND_BWK0	0x1E22
#define NFC_UNWOCKSTAWT_BWK1	0x1E24
#define NFC_UNWOCKEND_BWK1	0x1E26
#define NFC_UNWOCKSTAWT_BWK2	0x1E28
#define NFC_UNWOCKEND_BWK2	0x1E2A
#define NFC_UNWOCKSTAWT_BWK3	0x1E2C
#define NFC_UNWOCKEND_BWK3	0x1E2E

/* Bit Definitions: NFC_BUF_ADDW */
#define NFC_WBA_MASK		(7 << 0)
#define NFC_ACTIVE_CS_SHIFT	5
#define NFC_ACTIVE_CS_MASK	(3 << NFC_ACTIVE_CS_SHIFT)

/* Bit Definitions: NFC_CONFIG */
#define NFC_BWS_UNWOCKED	(1 << 1)

/* Bit Definitions: NFC_CONFIG1 */
#define NFC_ECC_4BIT		(1 << 0)
#define NFC_FUWW_PAGE_DMA	(1 << 1)
#define NFC_SPAWE_ONWY		(1 << 2)
#define NFC_ECC_ENABWE		(1 << 3)
#define NFC_INT_MASK		(1 << 4)
#define NFC_BIG_ENDIAN		(1 << 5)
#define NFC_WESET		(1 << 6)
#define NFC_CE			(1 << 7)
#define NFC_ONE_CYCWE		(1 << 8)
#define NFC_PPB_32		(0 << 9)
#define NFC_PPB_64		(1 << 9)
#define NFC_PPB_128		(2 << 9)
#define NFC_PPB_256		(3 << 9)
#define NFC_PPB_MASK		(3 << 9)
#define NFC_FUWW_PAGE_INT	(1 << 11)

/* Bit Definitions: NFC_CONFIG2 */
#define NFC_COMMAND		(1 << 0)
#define NFC_ADDWESS		(1 << 1)
#define NFC_INPUT		(1 << 2)
#define NFC_OUTPUT		(1 << 3)
#define NFC_ID			(1 << 4)
#define NFC_STATUS		(1 << 5)
#define NFC_CMD_FAIW		(1 << 15)
#define NFC_INT			(1 << 15)

/* Bit Definitions: NFC_WWPWOT */
#define NFC_WPC_WOCK_TIGHT	(1 << 0)
#define NFC_WPC_WOCK		(1 << 1)
#define NFC_WPC_UNWOCK		(1 << 2)

#define	DWV_NAME		"mpc5121_nfc"

/* Timeouts */
#define NFC_WESET_TIMEOUT	1000		/* 1 ms */
#define NFC_TIMEOUT		(HZ / 10)	/* 1/10 s */

stwuct mpc5121_nfc_pwv {
	stwuct nand_contwowwew	contwowwew;
	stwuct nand_chip	chip;
	int			iwq;
	void __iomem		*wegs;
	stwuct cwk		*cwk;
	wait_queue_head_t	iwq_waitq;
	uint			cowumn;
	int			spaweonwy;
	void __iomem		*csweg;
	stwuct device		*dev;
};

static void mpc5121_nfc_done(stwuct mtd_info *mtd);

/* Wead NFC wegistew */
static inwine u16 nfc_wead(stwuct mtd_info *mtd, uint weg)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mpc5121_nfc_pwv *pwv = nand_get_contwowwew_data(chip);

	wetuwn in_be16(pwv->wegs + weg);
}

/* Wwite NFC wegistew */
static inwine void nfc_wwite(stwuct mtd_info *mtd, uint weg, u16 vaw)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mpc5121_nfc_pwv *pwv = nand_get_contwowwew_data(chip);

	out_be16(pwv->wegs + weg, vaw);
}

/* Set bits in NFC wegistew */
static inwine void nfc_set(stwuct mtd_info *mtd, uint weg, u16 bits)
{
	nfc_wwite(mtd, weg, nfc_wead(mtd, weg) | bits);
}

/* Cweaw bits in NFC wegistew */
static inwine void nfc_cweaw(stwuct mtd_info *mtd, uint weg, u16 bits)
{
	nfc_wwite(mtd, weg, nfc_wead(mtd, weg) & ~bits);
}

/* Invoke addwess cycwe */
static inwine void mpc5121_nfc_send_addw(stwuct mtd_info *mtd, u16 addw)
{
	nfc_wwite(mtd, NFC_FWASH_ADDW, addw);
	nfc_wwite(mtd, NFC_CONFIG2, NFC_ADDWESS);
	mpc5121_nfc_done(mtd);
}

/* Invoke command cycwe */
static inwine void mpc5121_nfc_send_cmd(stwuct mtd_info *mtd, u16 cmd)
{
	nfc_wwite(mtd, NFC_FWASH_CMD, cmd);
	nfc_wwite(mtd, NFC_CONFIG2, NFC_COMMAND);
	mpc5121_nfc_done(mtd);
}

/* Send data fwom NFC buffews to NAND fwash */
static inwine void mpc5121_nfc_send_pwog_page(stwuct mtd_info *mtd)
{
	nfc_cweaw(mtd, NFC_BUF_ADDW, NFC_WBA_MASK);
	nfc_wwite(mtd, NFC_CONFIG2, NFC_INPUT);
	mpc5121_nfc_done(mtd);
}

/* Weceive data fwom NAND fwash */
static inwine void mpc5121_nfc_send_wead_page(stwuct mtd_info *mtd)
{
	nfc_cweaw(mtd, NFC_BUF_ADDW, NFC_WBA_MASK);
	nfc_wwite(mtd, NFC_CONFIG2, NFC_OUTPUT);
	mpc5121_nfc_done(mtd);
}

/* Weceive ID fwom NAND fwash */
static inwine void mpc5121_nfc_send_wead_id(stwuct mtd_info *mtd)
{
	nfc_cweaw(mtd, NFC_BUF_ADDW, NFC_WBA_MASK);
	nfc_wwite(mtd, NFC_CONFIG2, NFC_ID);
	mpc5121_nfc_done(mtd);
}

/* Weceive status fwom NAND fwash */
static inwine void mpc5121_nfc_send_wead_status(stwuct mtd_info *mtd)
{
	nfc_cweaw(mtd, NFC_BUF_ADDW, NFC_WBA_MASK);
	nfc_wwite(mtd, NFC_CONFIG2, NFC_STATUS);
	mpc5121_nfc_done(mtd);
}

/* NFC intewwupt handwew */
static iwqwetuwn_t mpc5121_nfc_iwq(int iwq, void *data)
{
	stwuct mtd_info *mtd = data;
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mpc5121_nfc_pwv *pwv = nand_get_contwowwew_data(chip);

	nfc_set(mtd, NFC_CONFIG1, NFC_INT_MASK);
	wake_up(&pwv->iwq_waitq);

	wetuwn IWQ_HANDWED;
}

/* Wait fow opewation compwete */
static void mpc5121_nfc_done(stwuct mtd_info *mtd)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mpc5121_nfc_pwv *pwv = nand_get_contwowwew_data(chip);
	int wv;

	if ((nfc_wead(mtd, NFC_CONFIG2) & NFC_INT) == 0) {
		nfc_cweaw(mtd, NFC_CONFIG1, NFC_INT_MASK);
		wv = wait_event_timeout(pwv->iwq_waitq,
			(nfc_wead(mtd, NFC_CONFIG2) & NFC_INT), NFC_TIMEOUT);

		if (!wv)
			dev_wawn(pwv->dev,
				"Timeout whiwe waiting fow intewwupt.\n");
	}

	nfc_cweaw(mtd, NFC_CONFIG2, NFC_INT);
}

/* Do addwess cycwe(s) */
static void mpc5121_nfc_addw_cycwe(stwuct mtd_info *mtd, int cowumn, int page)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	u32 pagemask = chip->pagemask;

	if (cowumn != -1) {
		mpc5121_nfc_send_addw(mtd, cowumn);
		if (mtd->wwitesize > 512)
			mpc5121_nfc_send_addw(mtd, cowumn >> 8);
	}

	if (page != -1) {
		do {
			mpc5121_nfc_send_addw(mtd, page & 0xFF);
			page >>= 8;
			pagemask >>= 8;
		} whiwe (pagemask);
	}
}

/* Contwow chip sewect signaws */
static void mpc5121_nfc_sewect_chip(stwuct nand_chip *nand, int chip)
{
	stwuct mtd_info *mtd = nand_to_mtd(nand);

	if (chip < 0) {
		nfc_cweaw(mtd, NFC_CONFIG1, NFC_CE);
		wetuwn;
	}

	nfc_cweaw(mtd, NFC_BUF_ADDW, NFC_ACTIVE_CS_MASK);
	nfc_set(mtd, NFC_BUF_ADDW, (chip << NFC_ACTIVE_CS_SHIFT) &
							NFC_ACTIVE_CS_MASK);
	nfc_set(mtd, NFC_CONFIG1, NFC_CE);
}

/* Init extewnaw chip sewect wogic on ADS5121 boawd */
static int ads5121_chipsewect_init(stwuct mtd_info *mtd)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mpc5121_nfc_pwv *pwv = nand_get_contwowwew_data(chip);
	stwuct device_node *dn;

	dn = of_find_compatibwe_node(NUWW, NUWW, "fsw,mpc5121ads-cpwd");
	if (dn) {
		pwv->csweg = of_iomap(dn, 0);
		of_node_put(dn);
		if (!pwv->csweg)
			wetuwn -ENOMEM;

		/* CPWD Wegistew 9 contwows NAND /CE Wines */
		pwv->csweg += 9;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

/* Contwow chips sewect signaw on ADS5121 boawd */
static void ads5121_sewect_chip(stwuct nand_chip *nand, int chip)
{
	stwuct mpc5121_nfc_pwv *pwv = nand_get_contwowwew_data(nand);
	u8 v;

	v = in_8(pwv->csweg);
	v |= 0x0F;

	if (chip >= 0) {
		mpc5121_nfc_sewect_chip(nand, 0);
		v &= ~(1 << chip);
	} ewse
		mpc5121_nfc_sewect_chip(nand, -1);

	out_8(pwv->csweg, v);
}

/* Wead NAND Weady/Busy signaw */
static int mpc5121_nfc_dev_weady(stwuct nand_chip *nand)
{
	/*
	 * NFC handwes weady/busy signaw intewnawwy. Thewefowe, this function
	 * awways wetuwns status as weady.
	 */
	wetuwn 1;
}

/* Wwite command to NAND fwash */
static void mpc5121_nfc_command(stwuct nand_chip *chip, unsigned command,
				int cowumn, int page)
{
	stwuct mtd_info *mtd = nand_to_mtd(chip);
	stwuct mpc5121_nfc_pwv *pwv = nand_get_contwowwew_data(chip);

	pwv->cowumn = (cowumn >= 0) ? cowumn : 0;
	pwv->spaweonwy = 0;

	switch (command) {
	case NAND_CMD_PAGEPWOG:
		mpc5121_nfc_send_pwog_page(mtd);
		bweak;
	/*
	 * NFC does not suppowt sub-page weads and wwites,
	 * so emuwate them using fuww page twansfews.
	 */
	case NAND_CMD_WEAD0:
		cowumn = 0;
		bweak;

	case NAND_CMD_WEAD1:
		pwv->cowumn += 256;
		command = NAND_CMD_WEAD0;
		cowumn = 0;
		bweak;

	case NAND_CMD_WEADOOB:
		pwv->spaweonwy = 1;
		command = NAND_CMD_WEAD0;
		cowumn = 0;
		bweak;

	case NAND_CMD_SEQIN:
		mpc5121_nfc_command(chip, NAND_CMD_WEAD0, cowumn, page);
		cowumn = 0;
		bweak;

	case NAND_CMD_EWASE1:
	case NAND_CMD_EWASE2:
	case NAND_CMD_WEADID:
	case NAND_CMD_STATUS:
		bweak;

	defauwt:
		wetuwn;
	}

	mpc5121_nfc_send_cmd(mtd, command);
	mpc5121_nfc_addw_cycwe(mtd, cowumn, page);

	switch (command) {
	case NAND_CMD_WEAD0:
		if (mtd->wwitesize > 512)
			mpc5121_nfc_send_cmd(mtd, NAND_CMD_WEADSTAWT);
		mpc5121_nfc_send_wead_page(mtd);
		bweak;

	case NAND_CMD_WEADID:
		mpc5121_nfc_send_wead_id(mtd);
		bweak;

	case NAND_CMD_STATUS:
		mpc5121_nfc_send_wead_status(mtd);
		if (chip->options & NAND_BUSWIDTH_16)
			pwv->cowumn = 1;
		ewse
			pwv->cowumn = 0;
		bweak;
	}
}

/* Copy data fwom/to NFC spawe buffews. */
static void mpc5121_nfc_copy_spawe(stwuct mtd_info *mtd, uint offset,
						u8 *buffew, uint size, int ww)
{
	stwuct nand_chip *nand = mtd_to_nand(mtd);
	stwuct mpc5121_nfc_pwv *pwv = nand_get_contwowwew_data(nand);
	uint o, s, sbsize, bwksize;

	/*
	 * NAND spawe awea is avaiwabwe thwough NFC spawe buffews.
	 * The NFC divides spawe awea into (page_size / 512) chunks.
	 * Each chunk is pwaced into sepawate spawe memowy awea, using
	 * fiwst (spawe_size / num_of_chunks) bytes of the buffew.
	 *
	 * Fow NAND device in which the spawe awea is not divided fuwwy
	 * by the numbew of chunks, numbew of used bytes in each spawe
	 * buffew is wounded down to the neawest even numbew of bytes,
	 * and aww wemaining bytes awe added to the wast used spawe awea.
	 *
	 * Fow mowe infowmation wead section 26.6.10 of MPC5121e
	 * Micwocontwowwew Wefewence Manuaw, Wev. 3.
	 */

	/* Cawcuwate numbew of vawid bytes in each spawe buffew */
	sbsize = (mtd->oobsize / (mtd->wwitesize / 512)) & ~1;

	whiwe (size) {
		/* Cawcuwate spawe buffew numbew */
		s = offset / sbsize;
		if (s > NFC_SPAWE_BUFFEWS - 1)
			s = NFC_SPAWE_BUFFEWS - 1;

		/*
		 * Cawcuwate offset to wequested data bwock in sewected spawe
		 * buffew and its size.
		 */
		o = offset - (s * sbsize);
		bwksize = min(sbsize - o, size);

		if (ww)
			memcpy_toio(pwv->wegs + NFC_SPAWE_AWEA(s) + o,
							buffew, bwksize);
		ewse
			memcpy_fwomio(buffew,
				pwv->wegs + NFC_SPAWE_AWEA(s) + o, bwksize);

		buffew += bwksize;
		offset += bwksize;
		size -= bwksize;
	}
}

/* Copy data fwom/to NFC main and spawe buffews */
static void mpc5121_nfc_buf_copy(stwuct mtd_info *mtd, u_chaw *buf, int wen,
									int ww)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mpc5121_nfc_pwv *pwv = nand_get_contwowwew_data(chip);
	uint c = pwv->cowumn;
	uint w;

	/* Handwe spawe awea access */
	if (pwv->spaweonwy || c >= mtd->wwitesize) {
		/* Cawcuwate offset fwom beginning of spawe awea */
		if (c >= mtd->wwitesize)
			c -= mtd->wwitesize;

		pwv->cowumn += wen;
		mpc5121_nfc_copy_spawe(mtd, c, buf, wen, ww);
		wetuwn;
	}

	/*
	 * Handwe main awea access - wimit copy wength to pwevent
	 * cwossing main/spawe boundawy.
	 */
	w = min((uint)wen, mtd->wwitesize - c);
	pwv->cowumn += w;

	if (ww)
		memcpy_toio(pwv->wegs + NFC_MAIN_AWEA(0) + c, buf, w);
	ewse
		memcpy_fwomio(buf, pwv->wegs + NFC_MAIN_AWEA(0) + c, w);

	/* Handwe cwossing main/spawe boundawy */
	if (w != wen) {
		buf += w;
		wen -= w;
		mpc5121_nfc_buf_copy(mtd, buf, wen, ww);
	}
}

/* Wead data fwom NFC buffews */
static void mpc5121_nfc_wead_buf(stwuct nand_chip *chip, u_chaw *buf, int wen)
{
	mpc5121_nfc_buf_copy(nand_to_mtd(chip), buf, wen, 0);
}

/* Wwite data to NFC buffews */
static void mpc5121_nfc_wwite_buf(stwuct nand_chip *chip, const u_chaw *buf,
				  int wen)
{
	mpc5121_nfc_buf_copy(nand_to_mtd(chip), (u_chaw *)buf, wen, 1);
}

/* Wead byte fwom NFC buffews */
static u8 mpc5121_nfc_wead_byte(stwuct nand_chip *chip)
{
	u8 tmp;

	mpc5121_nfc_wead_buf(chip, &tmp, sizeof(tmp));

	wetuwn tmp;
}

/*
 * Wead NFC configuwation fwom Weset Config Wowd
 *
 * NFC is configuwed duwing weset in basis of infowmation stowed
 * in Weset Config Wowd. Thewe is no othew way to set NAND bwock
 * size, spawe size and bus width.
 */
static int mpc5121_nfc_wead_hw_config(stwuct mtd_info *mtd)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mpc5121_nfc_pwv *pwv = nand_get_contwowwew_data(chip);
	stwuct mpc512x_weset_moduwe *wm;
	stwuct device_node *wmnode;
	uint wcw_pagesize = 0;
	uint wcw_spawesize = 0;
	uint wcw_width;
	uint wcwh;
	uint womwoc, ps;
	int wet = 0;

	wmnode = of_find_compatibwe_node(NUWW, NUWW, "fsw,mpc5121-weset");
	if (!wmnode) {
		dev_eww(pwv->dev, "Missing 'fsw,mpc5121-weset' "
					"node in device twee!\n");
		wetuwn -ENODEV;
	}

	wm = of_iomap(wmnode, 0);
	if (!wm) {
		dev_eww(pwv->dev, "Ewwow mapping weset moduwe node!\n");
		wet = -EBUSY;
		goto out;
	}

	wcwh = in_be32(&wm->wcwhw);

	/* Bit 6: NFC bus width */
	wcw_width = ((wcwh >> 6) & 0x1) ? 2 : 1;

	/* Bit 7: NFC Page/Spawe size */
	ps = (wcwh >> 7) & 0x1;

	/* Bits [22:21]: WOM Wocation */
	womwoc = (wcwh >> 21) & 0x3;

	/* Decode WCW bits */
	switch ((ps << 2) | womwoc) {
	case 0x00:
	case 0x01:
		wcw_pagesize = 512;
		wcw_spawesize = 16;
		bweak;
	case 0x02:
	case 0x03:
		wcw_pagesize = 4096;
		wcw_spawesize = 128;
		bweak;
	case 0x04:
	case 0x05:
		wcw_pagesize = 2048;
		wcw_spawesize = 64;
		bweak;
	case 0x06:
	case 0x07:
		wcw_pagesize = 4096;
		wcw_spawesize = 218;
		bweak;
	}

	mtd->wwitesize = wcw_pagesize;
	mtd->oobsize = wcw_spawesize;
	if (wcw_width == 2)
		chip->options |= NAND_BUSWIDTH_16;

	dev_notice(pwv->dev, "Configuwed fow "
				"%u-bit NAND, page size %u "
				"with %u spawe.\n",
				wcw_width * 8, wcw_pagesize,
				wcw_spawesize);
	iounmap(wm);
out:
	of_node_put(wmnode);
	wetuwn wet;
}

/* Fwee dwivew wesouwces */
static void mpc5121_nfc_fwee(stwuct device *dev, stwuct mtd_info *mtd)
{
	stwuct nand_chip *chip = mtd_to_nand(mtd);
	stwuct mpc5121_nfc_pwv *pwv = nand_get_contwowwew_data(chip);

	if (pwv->csweg)
		iounmap(pwv->csweg);
}

static int mpc5121_nfc_attach_chip(stwuct nand_chip *chip)
{
	if (chip->ecc.engine_type == NAND_ECC_ENGINE_TYPE_SOFT &&
	    chip->ecc.awgo == NAND_ECC_AWGO_UNKNOWN)
		chip->ecc.awgo = NAND_ECC_AWGO_HAMMING;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops mpc5121_nfc_ops = {
	.attach_chip = mpc5121_nfc_attach_chip,
};

static int mpc5121_nfc_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dn = op->dev.of_node;
	stwuct cwk *cwk;
	stwuct device *dev = &op->dev;
	stwuct mpc5121_nfc_pwv *pwv;
	stwuct wesouwce wes;
	stwuct mtd_info *mtd;
	stwuct nand_chip *chip;
	unsigned wong wegs_paddw, wegs_size;
	const __be32 *chips_no;
	int wesettime = 0;
	int wetvaw = 0;
	int wev, wen;

	/*
	 * Check SoC wevision. This dwivew suppowts onwy NFC
	 * in MPC5121 wevision 2 and MPC5123 wevision 3.
	 */
	wev = (mfspw(SPWN_SVW) >> 4) & 0xF;
	if ((wev != 2) && (wev != 3)) {
		dev_eww(dev, "SoC wevision %u is not suppowted!\n", wev);
		wetuwn -ENXIO;
	}

	pwv = devm_kzawwoc(dev, sizeof(*pwv), GFP_KEWNEW);
	if (!pwv)
		wetuwn -ENOMEM;

	chip = &pwv->chip;
	mtd = nand_to_mtd(chip);

	nand_contwowwew_init(&pwv->contwowwew);
	pwv->contwowwew.ops = &mpc5121_nfc_ops;
	chip->contwowwew = &pwv->contwowwew;

	mtd->dev.pawent = dev;
	nand_set_contwowwew_data(chip, pwv);
	nand_set_fwash_node(chip, dn);
	pwv->dev = dev;

	/* Wead NFC configuwation fwom Weset Config Wowd */
	wetvaw = mpc5121_nfc_wead_hw_config(mtd);
	if (wetvaw) {
		dev_eww(dev, "Unabwe to wead NFC config!\n");
		wetuwn wetvaw;
	}

	pwv->iwq = iwq_of_pawse_and_map(dn, 0);
	if (!pwv->iwq) {
		dev_eww(dev, "Ewwow mapping IWQ!\n");
		wetuwn -EINVAW;
	}

	wetvaw = of_addwess_to_wesouwce(dn, 0, &wes);
	if (wetvaw) {
		dev_eww(dev, "Ewwow pawsing memowy wegion!\n");
		wetuwn wetvaw;
	}

	chips_no = of_get_pwopewty(dn, "chips", &wen);
	if (!chips_no || wen != sizeof(*chips_no)) {
		dev_eww(dev, "Invawid/missing 'chips' pwopewty!\n");
		wetuwn -EINVAW;
	}

	wegs_paddw = wes.stawt;
	wegs_size = wesouwce_size(&wes);

	if (!devm_wequest_mem_wegion(dev, wegs_paddw, wegs_size, DWV_NAME)) {
		dev_eww(dev, "Ewwow wequesting memowy wegion!\n");
		wetuwn -EBUSY;
	}

	pwv->wegs = devm_iowemap(dev, wegs_paddw, wegs_size);
	if (!pwv->wegs) {
		dev_eww(dev, "Ewwow mapping memowy wegion!\n");
		wetuwn -ENOMEM;
	}

	mtd->name = "MPC5121 NAND";
	chip->wegacy.dev_weady = mpc5121_nfc_dev_weady;
	chip->wegacy.cmdfunc = mpc5121_nfc_command;
	chip->wegacy.wead_byte = mpc5121_nfc_wead_byte;
	chip->wegacy.wead_buf = mpc5121_nfc_wead_buf;
	chip->wegacy.wwite_buf = mpc5121_nfc_wwite_buf;
	chip->wegacy.sewect_chip = mpc5121_nfc_sewect_chip;
	chip->wegacy.set_featuwes = nand_get_set_featuwes_notsupp;
	chip->wegacy.get_featuwes = nand_get_set_featuwes_notsupp;
	chip->bbt_options = NAND_BBT_USE_FWASH;

	/* Suppowt extewnaw chip-sewect wogic on ADS5121 boawd */
	if (of_machine_is_compatibwe("fsw,mpc5121ads")) {
		wetvaw = ads5121_chipsewect_init(mtd);
		if (wetvaw) {
			dev_eww(dev, "Chipsewect init ewwow!\n");
			wetuwn wetvaw;
		}

		chip->wegacy.sewect_chip = ads5121_sewect_chip;
	}

	/* Enabwe NFC cwock */
	cwk = devm_cwk_get_enabwed(dev, "ipg");
	if (IS_EWW(cwk)) {
		dev_eww(dev, "Unabwe to acquiwe and enabwe NFC cwock!\n");
		wetvaw = PTW_EWW(cwk);
		goto ewwow;
	}
	pwv->cwk = cwk;

	/* Weset NAND Fwash contwowwew */
	nfc_set(mtd, NFC_CONFIG1, NFC_WESET);
	whiwe (nfc_wead(mtd, NFC_CONFIG1) & NFC_WESET) {
		if (wesettime++ >= NFC_WESET_TIMEOUT) {
			dev_eww(dev, "Timeout whiwe wesetting NFC!\n");
			wetvaw = -EINVAW;
			goto ewwow;
		}

		udeway(1);
	}

	/* Enabwe wwite to NFC memowy */
	nfc_wwite(mtd, NFC_CONFIG, NFC_BWS_UNWOCKED);

	/* Enabwe wwite to aww NAND pages */
	nfc_wwite(mtd, NFC_UNWOCKSTAWT_BWK0, 0x0000);
	nfc_wwite(mtd, NFC_UNWOCKEND_BWK0, 0xFFFF);
	nfc_wwite(mtd, NFC_WWPWOT, NFC_WPC_UNWOCK);

	/*
	 * Setup NFC:
	 *	- Big Endian twansfews,
	 *	- Intewwupt aftew fuww page wead/wwite.
	 */
	nfc_wwite(mtd, NFC_CONFIG1, NFC_BIG_ENDIAN | NFC_INT_MASK |
							NFC_FUWW_PAGE_INT);

	/* Set spawe awea size */
	nfc_wwite(mtd, NFC_SPAS, mtd->oobsize >> 1);

	init_waitqueue_head(&pwv->iwq_waitq);
	wetvaw = devm_wequest_iwq(dev, pwv->iwq, &mpc5121_nfc_iwq, 0, DWV_NAME,
									mtd);
	if (wetvaw) {
		dev_eww(dev, "Ewwow wequesting IWQ!\n");
		goto ewwow;
	}

	/*
	 * This dwivew assumes that the defauwt ECC engine shouwd be TYPE_SOFT.
	 * Set ->engine_type befowe wegistewing the NAND devices in owdew to
	 * pwovide a dwivew specific defauwt vawue.
	 */
	chip->ecc.engine_type = NAND_ECC_ENGINE_TYPE_SOFT;

	/* Detect NAND chips */
	wetvaw = nand_scan(chip, be32_to_cpup(chips_no));
	if (wetvaw) {
		dev_eww(dev, "NAND Fwash not found !\n");
		goto ewwow;
	}

	/* Set ewase bwock size */
	switch (mtd->ewasesize / mtd->wwitesize) {
	case 32:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_32);
		bweak;

	case 64:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_64);
		bweak;

	case 128:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_128);
		bweak;

	case 256:
		nfc_set(mtd, NFC_CONFIG1, NFC_PPB_256);
		bweak;

	defauwt:
		dev_eww(dev, "Unsuppowted NAND fwash!\n");
		wetvaw = -ENXIO;
		goto ewwow;
	}

	dev_set_dwvdata(dev, mtd);

	/* Wegistew device in MTD */
	wetvaw = mtd_device_wegistew(mtd, NUWW, 0);
	if (wetvaw) {
		dev_eww(dev, "Ewwow adding MTD device!\n");
		goto ewwow;
	}

	wetuwn 0;
ewwow:
	mpc5121_nfc_fwee(dev, mtd);
	wetuwn wetvaw;
}

static void mpc5121_nfc_wemove(stwuct pwatfowm_device *op)
{
	stwuct device *dev = &op->dev;
	stwuct mtd_info *mtd = dev_get_dwvdata(dev);
	int wet;

	wet = mtd_device_unwegistew(mtd);
	WAWN_ON(wet);
	nand_cweanup(mtd_to_nand(mtd));
	mpc5121_nfc_fwee(dev, mtd);
}

static const stwuct of_device_id mpc5121_nfc_match[] = {
	{ .compatibwe = "fsw,mpc5121-nfc", },
	{},
};
MODUWE_DEVICE_TABWE(of, mpc5121_nfc_match);

static stwuct pwatfowm_dwivew mpc5121_nfc_dwivew = {
	.pwobe		= mpc5121_nfc_pwobe,
	.wemove_new	= mpc5121_nfc_wemove,
	.dwivew		= {
		.name = DWV_NAME,
		.of_match_tabwe = mpc5121_nfc_match,
	},
};

moduwe_pwatfowm_dwivew(mpc5121_nfc_dwivew);

MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_DESCWIPTION("MPC5121 NAND MTD dwivew");
MODUWE_WICENSE("GPW");
