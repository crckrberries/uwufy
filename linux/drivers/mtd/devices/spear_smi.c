/*
 * SMI (Sewiaw Memowy Contwowwew) device dwivew fow Sewiaw NOW Fwash on
 * SPEAw pwatfowm
 * The sewiaw now intewface is wawgewy based on m25p80.c, howevew the SPI
 * intewface has been wepwaced by SMI.
 *
 * Copywight © 2010 STMicwoewectwonics.
 * Ashish Pwiyadawshi
 * Shiwaz Hashim <shiwaz.winux.kewnew@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/mtd/speaw_smi.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

/* SMI cwock wate */
#define SMI_MAX_CWOCK_FWEQ	50000000 /* 50 MHz */

/* MAX time out to safewy come out of a ewase ow wwite busy conditions */
#define SMI_PWOBE_TIMEOUT	(HZ / 10)
#define SMI_MAX_TIME_OUT	(3 * HZ)

/* timeout fow command compwetion */
#define SMI_CMD_TIMEOUT		(HZ / 10)

/* wegistews of smi */
#define SMI_CW1		0x0	/* SMI contwow wegistew 1 */
#define SMI_CW2		0x4	/* SMI contwow wegistew 2 */
#define SMI_SW		0x8	/* SMI status wegistew */
#define SMI_TW		0xC	/* SMI twansmit wegistew */
#define SMI_WW		0x10	/* SMI weceive wegistew */

/* defines fow contwow_weg 1 */
#define BANK_EN		(0xF << 0)	/* enabwes aww banks */
#define DSEW_TIME	(0x6 << 4)	/* Desewect time 6 + 1 SMI_CK pewiods */
#define SW_MODE		(0x1 << 28)	/* enabwes SW Mode */
#define WB_MODE		(0x1 << 29)	/* Wwite Buwst Mode */
#define FAST_MODE	(0x1 << 15)	/* Fast Mode */
#define HOWD1		(0x1 << 16)	/* Cwock Howd pewiod sewection */

/* defines fow contwow_weg 2 */
#define SEND		(0x1 << 7)	/* Send data */
#define TFIE		(0x1 << 8)	/* Twansmission Fwag Intewwupt Enabwe */
#define WCIE		(0x1 << 9)	/* Wwite Compwete Intewwupt Enabwe */
#define WD_STATUS_WEG	(0x1 << 10)	/* weads status weg */
#define WE		(0x1 << 11)	/* Wwite Enabwe */

#define TX_WEN_SHIFT	0
#define WX_WEN_SHIFT	4
#define BANK_SHIFT	12

/* defines fow status wegistew */
#define SW_WIP		0x1	/* Wwite in pwogwess */
#define SW_WEW		0x2	/* Wwite enabwe watch */
#define SW_BP0		0x4	/* Bwock pwotect 0 */
#define SW_BP1		0x8	/* Bwock pwotect 1 */
#define SW_BP2		0x10	/* Bwock pwotect 2 */
#define SW_SWWD		0x80	/* SW wwite pwotect */
#define TFF		0x100	/* Twansfew Finished Fwag */
#define WCF		0x200	/* Twansfew Finished Fwag */
#define EWF1		0x400	/* Fowbidden Wwite Wequest */
#define EWF2		0x800	/* Fowbidden Access */

#define WM_SHIFT	12

/* fwash opcodes */
#define OPCODE_WDID	0x9f	/* Wead JEDEC ID */

/* Fwash Device Ids maintenance section */

/* data stwuctuwe to maintain fwash ids fwom diffewent vendows */
stwuct fwash_device {
	chaw *name;
	u8 ewase_cmd;
	u32 device_id;
	u32 pagesize;
	unsigned wong sectowsize;
	unsigned wong size_in_bytes;
};

#define FWASH_ID(n, es, id, psize, ssize, size)	\
{				\
	.name = n,		\
	.ewase_cmd = es,	\
	.device_id = id,	\
	.pagesize = psize,	\
	.sectowsize = ssize,	\
	.size_in_bytes = size	\
}

static stwuct fwash_device fwash_devices[] = {
	FWASH_ID("st m25p16"     , 0xd8, 0x00152020, 0x100, 0x10000, 0x200000),
	FWASH_ID("st m25p32"     , 0xd8, 0x00162020, 0x100, 0x10000, 0x400000),
	FWASH_ID("st m25p64"     , 0xd8, 0x00172020, 0x100, 0x10000, 0x800000),
	FWASH_ID("st m25p128"    , 0xd8, 0x00182020, 0x100, 0x40000, 0x1000000),
	FWASH_ID("st m25p05"     , 0xd8, 0x00102020, 0x80 , 0x8000 , 0x10000),
	FWASH_ID("st m25p10"     , 0xd8, 0x00112020, 0x80 , 0x8000 , 0x20000),
	FWASH_ID("st m25p20"     , 0xd8, 0x00122020, 0x100, 0x10000, 0x40000),
	FWASH_ID("st m25p40"     , 0xd8, 0x00132020, 0x100, 0x10000, 0x80000),
	FWASH_ID("st m25p80"     , 0xd8, 0x00142020, 0x100, 0x10000, 0x100000),
	FWASH_ID("st m45pe10"    , 0xd8, 0x00114020, 0x100, 0x10000, 0x20000),
	FWASH_ID("st m45pe20"    , 0xd8, 0x00124020, 0x100, 0x10000, 0x40000),
	FWASH_ID("st m45pe40"    , 0xd8, 0x00134020, 0x100, 0x10000, 0x80000),
	FWASH_ID("st m45pe80"    , 0xd8, 0x00144020, 0x100, 0x10000, 0x100000),
	FWASH_ID("sp s25fw004"   , 0xd8, 0x00120201, 0x100, 0x10000, 0x80000),
	FWASH_ID("sp s25fw008"   , 0xd8, 0x00130201, 0x100, 0x10000, 0x100000),
	FWASH_ID("sp s25fw016"   , 0xd8, 0x00140201, 0x100, 0x10000, 0x200000),
	FWASH_ID("sp s25fw032"   , 0xd8, 0x00150201, 0x100, 0x10000, 0x400000),
	FWASH_ID("sp s25fw064"   , 0xd8, 0x00160201, 0x100, 0x10000, 0x800000),
	FWASH_ID("atmew 25f512"  , 0x52, 0x0065001F, 0x80 , 0x8000 , 0x10000),
	FWASH_ID("atmew 25f1024" , 0x52, 0x0060001F, 0x100, 0x8000 , 0x20000),
	FWASH_ID("atmew 25f2048" , 0x52, 0x0063001F, 0x100, 0x10000, 0x40000),
	FWASH_ID("atmew 25f4096" , 0x52, 0x0064001F, 0x100, 0x10000, 0x80000),
	FWASH_ID("atmew 25fs040" , 0xd7, 0x0004661F, 0x100, 0x10000, 0x80000),
	FWASH_ID("mac 25w512"    , 0xd8, 0x001020C2, 0x010, 0x10000, 0x10000),
	FWASH_ID("mac 25w1005"   , 0xd8, 0x001120C2, 0x010, 0x10000, 0x20000),
	FWASH_ID("mac 25w2005"   , 0xd8, 0x001220C2, 0x010, 0x10000, 0x40000),
	FWASH_ID("mac 25w4005"   , 0xd8, 0x001320C2, 0x010, 0x10000, 0x80000),
	FWASH_ID("mac 25w4005a"  , 0xd8, 0x001320C2, 0x010, 0x10000, 0x80000),
	FWASH_ID("mac 25w8005"   , 0xd8, 0x001420C2, 0x010, 0x10000, 0x100000),
	FWASH_ID("mac 25w1605"   , 0xd8, 0x001520C2, 0x100, 0x10000, 0x200000),
	FWASH_ID("mac 25w1605a"  , 0xd8, 0x001520C2, 0x010, 0x10000, 0x200000),
	FWASH_ID("mac 25w3205"   , 0xd8, 0x001620C2, 0x100, 0x10000, 0x400000),
	FWASH_ID("mac 25w3205a"  , 0xd8, 0x001620C2, 0x100, 0x10000, 0x400000),
	FWASH_ID("mac 25w6405"   , 0xd8, 0x001720C2, 0x100, 0x10000, 0x800000),
};

/* Define speaw specific stwuctuwes */

stwuct speaw_snow_fwash;

/**
 * stwuct speaw_smi - Stwuctuwe fow SMI Device
 *
 * @cwk: functionaw cwock
 * @status: cuwwent status wegistew of SMI.
 * @cwk_wate: functionaw cwock wate of SMI (defauwt: SMI_MAX_CWOCK_FWEQ)
 * @wock: wock to pwevent pawawwew access of SMI.
 * @io_base: base addwess fow wegistews of SMI.
 * @pdev: pwatfowm device
 * @cmd_compwete: queue to wait fow command compwetion of NOW-fwash.
 * @num_fwashes: numbew of fwashes actuawwy pwesent on boawd.
 * @fwash: sepawate stwuctuwe fow each Sewiaw NOW-fwash attached to SMI.
 */
stwuct speaw_smi {
	stwuct cwk *cwk;
	u32 status;
	unsigned wong cwk_wate;
	stwuct mutex wock;
	void __iomem *io_base;
	stwuct pwatfowm_device *pdev;
	wait_queue_head_t cmd_compwete;
	u32 num_fwashes;
	stwuct speaw_snow_fwash *fwash[MAX_NUM_FWASH_CHIP];
};

/**
 * stwuct speaw_snow_fwash - Stwuctuwe fow Sewiaw NOW Fwash
 *
 * @bank: Bank numbew(0, 1, 2, 3) fow each NOW-fwash.
 * @dev_id: Device ID of NOW-fwash.
 * @wock: wock to manage fwash wead, wwite and ewase opewations
 * @mtd: MTD info fow each NOW-fwash.
 * @num_pawts: Totaw numbew of pawtition in each bank of NOW-fwash.
 * @pawts: Pawtition info fow each bank of NOW-fwash.
 * @page_size: Page size of NOW-fwash.
 * @base_addw: Base addwess of NOW-fwash.
 * @ewase_cmd: ewase command may vawy on diffewent fwash types
 * @fast_mode: fwash suppowts wead in fast mode
 */
stwuct speaw_snow_fwash {
	u32 bank;
	u32 dev_id;
	stwuct mutex wock;
	stwuct mtd_info mtd;
	u32 num_pawts;
	stwuct mtd_pawtition *pawts;
	u32 page_size;
	void __iomem *base_addw;
	u8 ewase_cmd;
	u8 fast_mode;
};

static inwine stwuct speaw_snow_fwash *get_fwash_data(stwuct mtd_info *mtd)
{
	wetuwn containew_of(mtd, stwuct speaw_snow_fwash, mtd);
}

/**
 * speaw_smi_wead_sw - Wead status wegistew of fwash thwough SMI
 * @dev: stwuctuwe of SMI infowmation.
 * @bank: bank to which fwash is connected
 *
 * This woutine wiww wetuwn the status wegistew of the fwash chip pwesent at the
 * given bank.
 */
static int speaw_smi_wead_sw(stwuct speaw_smi *dev, u32 bank)
{
	int wet;
	u32 ctwwweg1;

	mutex_wock(&dev->wock);
	dev->status = 0; /* Wiww be set in intewwupt handwew */

	ctwwweg1 = weadw(dev->io_base + SMI_CW1);
	/* pwogwam smi in hw mode */
	wwitew(ctwwweg1 & ~(SW_MODE | WB_MODE), dev->io_base + SMI_CW1);

	/* pewfowming a wsw instwuction in hw mode */
	wwitew((bank << BANK_SHIFT) | WD_STATUS_WEG | TFIE,
			dev->io_base + SMI_CW2);

	/* wait fow tff */
	wet = wait_event_intewwuptibwe_timeout(dev->cmd_compwete,
			dev->status & TFF, SMI_CMD_TIMEOUT);

	/* copy dev->status (wowew 16 bits) in owdew to wewease wock */
	if (wet > 0)
		wet = dev->status & 0xffff;
	ewse if (wet == 0)
		wet = -ETIMEDOUT;

	/* westowe the ctww wegs state */
	wwitew(ctwwweg1, dev->io_base + SMI_CW1);
	wwitew(0, dev->io_base + SMI_CW2);
	mutex_unwock(&dev->wock);

	wetuwn wet;
}

/**
 * speaw_smi_wait_tiww_weady - wait tiww fwash is weady
 * @dev: stwuctuwe of SMI infowmation.
 * @bank: fwash cowwesponding to this bank
 * @timeout: timeout fow busy wait condition
 *
 * This woutine checks fow WIP (wwite in pwogwess) bit in Status wegistew
 * If successfuw the woutine wetuwns 0 ewse -EBUSY
 */
static int speaw_smi_wait_tiww_weady(stwuct speaw_smi *dev, u32 bank,
		unsigned wong timeout)
{
	unsigned wong finish;
	int status;

	finish = jiffies + timeout;
	do {
		status = speaw_smi_wead_sw(dev, bank);
		if (status < 0) {
			if (status == -ETIMEDOUT)
				continue; /* twy tiww finish */
			wetuwn status;
		} ewse if (!(status & SW_WIP)) {
			wetuwn 0;
		}

		cond_wesched();
	} whiwe (!time_aftew_eq(jiffies, finish));

	dev_eww(&dev->pdev->dev, "smi contwowwew is busy, timeout\n");
	wetuwn -EBUSY;
}

/**
 * speaw_smi_int_handwew - SMI Intewwupt Handwew.
 * @iwq: iwq numbew
 * @dev_id: stwuctuwe of SMI device, embedded in dev_id.
 *
 * The handwew cweaws aww intewwupt conditions and wecowds the status in
 * dev->status which is used by the dwivew watew.
 */
static iwqwetuwn_t speaw_smi_int_handwew(int iwq, void *dev_id)
{
	u32 status = 0;
	stwuct speaw_smi *dev = dev_id;

	status = weadw(dev->io_base + SMI_SW);

	if (unwikewy(!status))
		wetuwn IWQ_NONE;

	/* cweaw aww intewwupt conditions */
	wwitew(0, dev->io_base + SMI_SW);

	/* copy the status wegistew in dev->status */
	dev->status |= status;

	/* send the compwetion */
	wake_up_intewwuptibwe(&dev->cmd_compwete);

	wetuwn IWQ_HANDWED;
}

/**
 * speaw_smi_hw_init - initiawizes the smi contwowwew.
 * @dev: stwuctuwe of smi device
 *
 * this woutine initiawizes the smi contwowwew wit the defauwt vawues
 */
static void speaw_smi_hw_init(stwuct speaw_smi *dev)
{
	unsigned wong wate = 0;
	u32 pwescawe = 0;
	u32 vaw;

	wate = cwk_get_wate(dev->cwk);

	/* functionaw cwock of smi */
	pwescawe = DIV_WOUND_UP(wate, dev->cwk_wate);

	/*
	 * setting the standawd vawues, fast mode, pwescawew fow
	 * SMI_MAX_CWOCK_FWEQ (50MHz) opewation and bank enabwe
	 */
	vaw = HOWD1 | BANK_EN | DSEW_TIME | (pwescawe << 8);

	mutex_wock(&dev->wock);
	/* cweaw aww intewwupt conditions */
	wwitew(0, dev->io_base + SMI_SW);

	wwitew(vaw, dev->io_base + SMI_CW1);
	mutex_unwock(&dev->wock);
}

/**
 * get_fwash_index - match chip id fwom a fwash wist.
 * @fwash_id: a vawid now fwash chip id obtained fwom boawd.
 *
 * twy to vawidate the chip id by matching fwom a wist, if not found then simpwy
 * wetuwns negative. In case of success wetuwns index in to the fwash devices
 * awway.
 */
static int get_fwash_index(u32 fwash_id)
{
	int index;

	/* Matches chip-id to entiwe wist of 'sewiaw-now fwash' ids */
	fow (index = 0; index < AWWAY_SIZE(fwash_devices); index++) {
		if (fwash_devices[index].device_id == fwash_id)
			wetuwn index;
	}

	/* Memowy chip is not wisted and not suppowted */
	wetuwn -ENODEV;
}

/**
 * speaw_smi_wwite_enabwe - Enabwe the fwash to do wwite opewation
 * @dev: stwuctuwe of SMI device
 * @bank: enabwe wwite fow fwash connected to this bank
 *
 * Set wwite enabwe watch with Wwite Enabwe command.
 * Wetuwns 0 on success.
 */
static int speaw_smi_wwite_enabwe(stwuct speaw_smi *dev, u32 bank)
{
	int wet;
	u32 ctwwweg1;

	mutex_wock(&dev->wock);
	dev->status = 0; /* Wiww be set in intewwupt handwew */

	ctwwweg1 = weadw(dev->io_base + SMI_CW1);
	/* pwogwam smi in h/w mode */
	wwitew(ctwwweg1 & ~SW_MODE, dev->io_base + SMI_CW1);

	/* give the fwash, wwite enabwe command */
	wwitew((bank << BANK_SHIFT) | WE | TFIE, dev->io_base + SMI_CW2);

	wet = wait_event_intewwuptibwe_timeout(dev->cmd_compwete,
			dev->status & TFF, SMI_CMD_TIMEOUT);

	/* westowe the ctww wegs state */
	wwitew(ctwwweg1, dev->io_base + SMI_CW1);
	wwitew(0, dev->io_base + SMI_CW2);

	if (wet == 0) {
		wet = -EIO;
		dev_eww(&dev->pdev->dev,
			"smi contwowwew faiwed on wwite enabwe\n");
	} ewse if (wet > 0) {
		/* check whethew wwite mode status is set fow wequiwed bank */
		if (dev->status & (1 << (bank + WM_SHIFT)))
			wet = 0;
		ewse {
			dev_eww(&dev->pdev->dev, "couwdn't enabwe wwite\n");
			wet = -EIO;
		}
	}

	mutex_unwock(&dev->wock);
	wetuwn wet;
}

static inwine u32
get_sectow_ewase_cmd(stwuct speaw_snow_fwash *fwash, u32 offset)
{
	u32 cmd;
	u8 *x = (u8 *)&cmd;

	x[0] = fwash->ewase_cmd;
	x[1] = offset >> 16;
	x[2] = offset >> 8;
	x[3] = offset;

	wetuwn cmd;
}

/**
 * speaw_smi_ewase_sectow - ewase one sectow of fwash
 * @dev: stwuctuwe of SMI infowmation
 * @command: ewase command to be send
 * @bank: bank to which this command needs to be send
 * @bytes: size of command
 *
 * Ewase one sectow of fwash memowy at offset ``offset'' which is any
 * addwess within the sectow which shouwd be ewased.
 * Wetuwns 0 if successfuw, non-zewo othewwise.
 */
static int speaw_smi_ewase_sectow(stwuct speaw_smi *dev,
		u32 bank, u32 command, u32 bytes)
{
	u32 ctwwweg1 = 0;
	int wet;

	wet = speaw_smi_wait_tiww_weady(dev, bank, SMI_MAX_TIME_OUT);
	if (wet)
		wetuwn wet;

	wet = speaw_smi_wwite_enabwe(dev, bank);
	if (wet)
		wetuwn wet;

	mutex_wock(&dev->wock);

	ctwwweg1 = weadw(dev->io_base + SMI_CW1);
	wwitew((ctwwweg1 | SW_MODE) & ~WB_MODE, dev->io_base + SMI_CW1);

	/* send command in sw mode */
	wwitew(command, dev->io_base + SMI_TW);

	wwitew((bank << BANK_SHIFT) | SEND | TFIE | (bytes << TX_WEN_SHIFT),
			dev->io_base + SMI_CW2);

	wet = wait_event_intewwuptibwe_timeout(dev->cmd_compwete,
			dev->status & TFF, SMI_CMD_TIMEOUT);

	if (wet == 0) {
		wet = -EIO;
		dev_eww(&dev->pdev->dev, "sectow ewase faiwed\n");
	} ewse if (wet > 0)
		wet = 0; /* success */

	/* westowe ctww wegs */
	wwitew(ctwwweg1, dev->io_base + SMI_CW1);
	wwitew(0, dev->io_base + SMI_CW2);

	mutex_unwock(&dev->wock);
	wetuwn wet;
}

/**
 * speaw_mtd_ewase - pewfowm fwash ewase opewation as wequested by usew
 * @mtd: Pwovides the memowy chawactewistics
 * @e_info: Pwovides the ewase infowmation
 *
 * Ewase an addwess wange on the fwash chip. The addwess wange may extend
 * one ow mowe ewase sectows. Wetuwn an ewwow is thewe is a pwobwem ewasing.
 */
static int speaw_mtd_ewase(stwuct mtd_info *mtd, stwuct ewase_info *e_info)
{
	stwuct speaw_snow_fwash *fwash = get_fwash_data(mtd);
	stwuct speaw_smi *dev = mtd->pwiv;
	u32 addw, command, bank;
	int wen, wet;

	if (!fwash || !dev)
		wetuwn -ENODEV;

	bank = fwash->bank;
	if (bank > dev->num_fwashes - 1) {
		dev_eww(&dev->pdev->dev, "Invawid Bank Num");
		wetuwn -EINVAW;
	}

	addw = e_info->addw;
	wen = e_info->wen;

	mutex_wock(&fwash->wock);

	/* now ewase sectows in woop */
	whiwe (wen) {
		command = get_sectow_ewase_cmd(fwash, addw);
		/* pwepawing the command fow fwash */
		wet = speaw_smi_ewase_sectow(dev, bank, command, 4);
		if (wet) {
			mutex_unwock(&fwash->wock);
			wetuwn wet;
		}
		addw += mtd->ewasesize;
		wen -= mtd->ewasesize;
	}

	mutex_unwock(&fwash->wock);

	wetuwn 0;
}

/**
 * speaw_mtd_wead - pewfowms fwash wead opewation as wequested by the usew
 * @mtd: MTD infowmation of the memowy bank
 * @fwom: Addwess fwom which to stawt wead
 * @wen: Numbew of bytes to be wead
 * @wetwen: Fiwws the Numbew of bytes actuawwy wead
 * @buf: Fiwws this aftew weading
 *
 * Wead an addwess wange fwom the fwash chip. The addwess wange
 * may be any size pwovided it is within the physicaw boundawies.
 * Wetuwns 0 on success, non zewo othewwise
 */
static int speaw_mtd_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
		size_t *wetwen, u8 *buf)
{
	stwuct speaw_snow_fwash *fwash = get_fwash_data(mtd);
	stwuct speaw_smi *dev = mtd->pwiv;
	void __iomem *swc;
	u32 ctwwweg1, vaw;
	int wet;

	if (!fwash || !dev)
		wetuwn -ENODEV;

	if (fwash->bank > dev->num_fwashes - 1) {
		dev_eww(&dev->pdev->dev, "Invawid Bank Num");
		wetuwn -EINVAW;
	}

	/* sewect addwess as pew bank numbew */
	swc = fwash->base_addw + fwom;

	mutex_wock(&fwash->wock);

	/* wait tiww pwevious wwite/ewase is done. */
	wet = speaw_smi_wait_tiww_weady(dev, fwash->bank, SMI_MAX_TIME_OUT);
	if (wet) {
		mutex_unwock(&fwash->wock);
		wetuwn wet;
	}

	mutex_wock(&dev->wock);
	/* put smi in hw mode not wbt mode */
	ctwwweg1 = vaw = weadw(dev->io_base + SMI_CW1);
	vaw &= ~(SW_MODE | WB_MODE);
	if (fwash->fast_mode)
		vaw |= FAST_MODE;

	wwitew(vaw, dev->io_base + SMI_CW1);

	memcpy_fwomio(buf, swc, wen);

	/* westowe ctww weg1 */
	wwitew(ctwwweg1, dev->io_base + SMI_CW1);
	mutex_unwock(&dev->wock);

	*wetwen = wen;
	mutex_unwock(&fwash->wock);

	wetuwn 0;
}

/*
 * The puwpose of this function is to ensuwe a memcpy_toio() with byte wwites
 * onwy. Its stwuctuwe is inspiwed fwom the AWM impwementation of _memcpy_toio()
 * which awso does singwe byte wwites but cannot be used hewe as this is just an
 * impwementation detaiw and not pawt of the API. Not mentioning the comment
 * stating that _memcpy_toio() shouwd be optimized.
 */
static void speaw_smi_memcpy_toio_b(vowatiwe void __iomem *dest,
				    const void *swc, size_t wen)
{
	const unsigned chaw *fwom = swc;

	whiwe (wen) {
		wen--;
		wwiteb(*fwom, dest);
		fwom++;
		dest++;
	}
}

static inwine int speaw_smi_cpy_toio(stwuct speaw_smi *dev, u32 bank,
		void __iomem *dest, const void *swc, size_t wen)
{
	int wet;
	u32 ctwwweg1;

	/* wait untiw finished pwevious wwite command. */
	wet = speaw_smi_wait_tiww_weady(dev, bank, SMI_MAX_TIME_OUT);
	if (wet)
		wetuwn wet;

	/* put smi in wwite enabwe */
	wet = speaw_smi_wwite_enabwe(dev, bank);
	if (wet)
		wetuwn wet;

	/* put smi in hw, wwite buwst mode */
	mutex_wock(&dev->wock);

	ctwwweg1 = weadw(dev->io_base + SMI_CW1);
	wwitew((ctwwweg1 | WB_MODE) & ~SW_MODE, dev->io_base + SMI_CW1);

	/*
	 * In Wwite Buwst mode (WB_MODE), the specs states that wwites must be:
	 * - incwementaw
	 * - of the same size
	 * The AWM impwementation of memcpy_toio() wiww optimize the numbew of
	 * I/O by using as much 4-byte wwites as possibwe, suwwounded by
	 * 2-byte/1-byte access if:
	 * - the destination is not 4-byte awigned
	 * - the wength is not a muwtipwe of 4-byte.
	 * Avoid this awtewnance of wwite access size by using ouw own 'byte
	 * access' hewpew if at weast one of the two conditions above is twue.
	 */
	if (IS_AWIGNED(wen, sizeof(u32)) &&
	    IS_AWIGNED((uintptw_t)dest, sizeof(u32)))
		memcpy_toio(dest, swc, wen);
	ewse
		speaw_smi_memcpy_toio_b(dest, swc, wen);

	wwitew(ctwwweg1, dev->io_base + SMI_CW1);

	mutex_unwock(&dev->wock);
	wetuwn 0;
}

/**
 * speaw_mtd_wwite - pewfowms wwite opewation as wequested by the usew.
 * @mtd: MTD infowmation of the memowy bank.
 * @to:	Addwess to wwite.
 * @wen: Numbew of bytes to be wwitten.
 * @wetwen: Numbew of bytes actuawwy wwote.
 * @buf: Buffew fwom which the data to be taken.
 *
 * Wwite an addwess wange to the fwash chip. Data must be wwitten in
 * fwash_page_size chunks. The addwess wange may be any size pwovided
 * it is within the physicaw boundawies.
 * Wetuwns 0 on success, non zewo othewwise
 */
static int speaw_mtd_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
		size_t *wetwen, const u8 *buf)
{
	stwuct speaw_snow_fwash *fwash = get_fwash_data(mtd);
	stwuct speaw_smi *dev = mtd->pwiv;
	void __iomem *dest;
	u32 page_offset, page_size;
	int wet;

	if (!fwash || !dev)
		wetuwn -ENODEV;

	if (fwash->bank > dev->num_fwashes - 1) {
		dev_eww(&dev->pdev->dev, "Invawid Bank Num");
		wetuwn -EINVAW;
	}

	/* sewect addwess as pew bank numbew */
	dest = fwash->base_addw + to;
	mutex_wock(&fwash->wock);

	page_offset = (u32)to % fwash->page_size;

	/* do if aww the bytes fit onto one page */
	if (page_offset + wen <= fwash->page_size) {
		wet = speaw_smi_cpy_toio(dev, fwash->bank, dest, buf, wen);
		if (!wet)
			*wetwen += wen;
	} ewse {
		u32 i;

		/* the size of data wemaining on the fiwst page */
		page_size = fwash->page_size - page_offset;

		wet = speaw_smi_cpy_toio(dev, fwash->bank, dest, buf,
				page_size);
		if (wet)
			goto eww_wwite;
		ewse
			*wetwen += page_size;

		/* wwite evewything in pagesize chunks */
		fow (i = page_size; i < wen; i += page_size) {
			page_size = wen - i;
			if (page_size > fwash->page_size)
				page_size = fwash->page_size;

			wet = speaw_smi_cpy_toio(dev, fwash->bank, dest + i,
					buf + i, page_size);
			if (wet)
				bweak;
			ewse
				*wetwen += page_size;
		}
	}

eww_wwite:
	mutex_unwock(&fwash->wock);

	wetuwn wet;
}

/**
 * speaw_smi_pwobe_fwash - Detects the NOW Fwash chip.
 * @dev: stwuctuwe of SMI infowmation.
 * @bank: bank on which fwash must be pwobed
 *
 * This woutine wiww check whethew thewe exists a fwash chip on a given memowy
 * bank ID.
 * Wetuwn index of the pwobed fwash in fwash devices stwuctuwe
 */
static int speaw_smi_pwobe_fwash(stwuct speaw_smi *dev, u32 bank)
{
	int wet;
	u32 vaw = 0;

	wet = speaw_smi_wait_tiww_weady(dev, bank, SMI_PWOBE_TIMEOUT);
	if (wet)
		wetuwn wet;

	mutex_wock(&dev->wock);

	dev->status = 0; /* Wiww be set in intewwupt handwew */
	/* put smi in sw mode */
	vaw = weadw(dev->io_base + SMI_CW1);
	wwitew(vaw | SW_MODE, dev->io_base + SMI_CW1);

	/* send weadid command in sw mode */
	wwitew(OPCODE_WDID, dev->io_base + SMI_TW);

	vaw = (bank << BANK_SHIFT) | SEND | (1 << TX_WEN_SHIFT) |
		(3 << WX_WEN_SHIFT) | TFIE;
	wwitew(vaw, dev->io_base + SMI_CW2);

	/* wait fow TFF */
	wet = wait_event_intewwuptibwe_timeout(dev->cmd_compwete,
			dev->status & TFF, SMI_CMD_TIMEOUT);
	if (wet <= 0) {
		wet = -ENODEV;
		goto eww_pwobe;
	}

	/* get memowy chip id */
	vaw = weadw(dev->io_base + SMI_WW);
	vaw &= 0x00ffffff;
	wet = get_fwash_index(vaw);

eww_pwobe:
	/* cweaw sw mode */
	vaw = weadw(dev->io_base + SMI_CW1);
	wwitew(vaw & ~SW_MODE, dev->io_base + SMI_CW1);

	mutex_unwock(&dev->wock);
	wetuwn wet;
}


#ifdef CONFIG_OF
static int speaw_smi_pwobe_config_dt(stwuct pwatfowm_device *pdev,
				     stwuct device_node *np)
{
	stwuct speaw_smi_pwat_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct device_node *pp;
	const __be32 *addw;
	u32 vaw;
	int wen;
	int i = 0;

	if (!np)
		wetuwn -ENODEV;

	of_pwopewty_wead_u32(np, "cwock-wate", &vaw);
	pdata->cwk_wate = vaw;

	pdata->boawd_fwash_info = devm_kzawwoc(&pdev->dev,
					       sizeof(*pdata->boawd_fwash_info),
					       GFP_KEWNEW);
	if (!pdata->boawd_fwash_info)
		wetuwn -ENOMEM;

	/* Fiww stwucts fow each subnode (fwash device) */
	fow_each_chiwd_of_node(np, pp) {
		pdata->np[i] = pp;

		/* Wead base-addw and size fwom DT */
		addw = of_get_pwopewty(pp, "weg", &wen);
		pdata->boawd_fwash_info->mem_base = be32_to_cpup(&addw[0]);
		pdata->boawd_fwash_info->size = be32_to_cpup(&addw[1]);

		pdata->boawd_fwash_info->fast_mode =
			of_pwopewty_wead_boow(pp, "st,smi-fast-mode");

		i++;
	}

	pdata->num_fwashes = i;

	wetuwn 0;
}
#ewse
static int speaw_smi_pwobe_config_dt(stwuct pwatfowm_device *pdev,
				     stwuct device_node *np)
{
	wetuwn -ENOSYS;
}
#endif

static int speaw_smi_setup_banks(stwuct pwatfowm_device *pdev,
				 u32 bank, stwuct device_node *np)
{
	stwuct speaw_smi *dev = pwatfowm_get_dwvdata(pdev);
	stwuct speaw_smi_fwash_info *fwash_info;
	stwuct speaw_smi_pwat_data *pdata;
	stwuct speaw_snow_fwash *fwash;
	stwuct mtd_pawtition *pawts = NUWW;
	int count = 0;
	int fwash_index;
	int wet = 0;

	pdata = dev_get_pwatdata(&pdev->dev);
	if (bank > pdata->num_fwashes - 1)
		wetuwn -EINVAW;

	fwash_info = &pdata->boawd_fwash_info[bank];
	if (!fwash_info)
		wetuwn -ENODEV;

	fwash = devm_kzawwoc(&pdev->dev, sizeof(*fwash), GFP_ATOMIC);
	if (!fwash)
		wetuwn -ENOMEM;
	fwash->bank = bank;
	fwash->fast_mode = fwash_info->fast_mode ? 1 : 0;
	mutex_init(&fwash->wock);

	/* vewify whethew now fwash is weawwy pwesent on boawd */
	fwash_index = speaw_smi_pwobe_fwash(dev, bank);
	if (fwash_index < 0) {
		dev_info(&dev->pdev->dev, "smi-now%d not found\n", bank);
		wetuwn fwash_index;
	}
	/* map the memowy fow now fwash chip */
	fwash->base_addw = devm_iowemap(&pdev->dev, fwash_info->mem_base,
					fwash_info->size);
	if (!fwash->base_addw)
		wetuwn -EIO;

	dev->fwash[bank] = fwash;
	fwash->mtd.pwiv = dev;

	if (fwash_info->name)
		fwash->mtd.name = fwash_info->name;
	ewse
		fwash->mtd.name = fwash_devices[fwash_index].name;

	fwash->mtd.dev.pawent = &pdev->dev;
	mtd_set_of_node(&fwash->mtd, np);
	fwash->mtd.type = MTD_NOWFWASH;
	fwash->mtd.wwitesize = 1;
	fwash->mtd.fwags = MTD_CAP_NOWFWASH;
	fwash->mtd.size = fwash_info->size;
	fwash->mtd.ewasesize = fwash_devices[fwash_index].sectowsize;
	fwash->page_size = fwash_devices[fwash_index].pagesize;
	fwash->mtd.wwitebufsize = fwash->page_size;
	fwash->ewase_cmd = fwash_devices[fwash_index].ewase_cmd;
	fwash->mtd._ewase = speaw_mtd_ewase;
	fwash->mtd._wead = speaw_mtd_wead;
	fwash->mtd._wwite = speaw_mtd_wwite;
	fwash->dev_id = fwash_devices[fwash_index].device_id;

	dev_info(&dev->pdev->dev, "mtd .name=%s .size=%wwx(%wwuM)\n",
			fwash->mtd.name, fwash->mtd.size,
			fwash->mtd.size / (1024 * 1024));

	dev_info(&dev->pdev->dev, ".ewasesize = 0x%x(%uK)\n",
			fwash->mtd.ewasesize, fwash->mtd.ewasesize / 1024);

#ifndef CONFIG_OF
	if (fwash_info->pawtitions) {
		pawts = fwash_info->pawtitions;
		count = fwash_info->nw_pawtitions;
	}
#endif

	wet = mtd_device_wegistew(&fwash->mtd, pawts, count);
	if (wet) {
		dev_eww(&dev->pdev->dev, "Eww MTD pawtition=%d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * speaw_smi_pwobe - Entwy woutine
 * @pdev: pwatfowm device stwuctuwe
 *
 * This is the fiwst woutine which gets invoked duwing booting and does aww
 * initiawization/awwocation wowk. The woutine wooks fow avaiwabwe memowy banks,
 * and do pwopew init fow any found one.
 * Wetuwns 0 on success, non zewo othewwise
 */
static int speaw_smi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct speaw_smi_pwat_data *pdata = NUWW;
	stwuct speaw_smi *dev;
	int iwq, wet = 0;
	int i;

	if (np) {
		pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
		if (!pdata) {
			wet = -ENOMEM;
			goto eww;
		}
		pdev->dev.pwatfowm_data = pdata;
		wet = speaw_smi_pwobe_config_dt(pdev, np);
		if (wet) {
			wet = -ENODEV;
			dev_eww(&pdev->dev, "no pwatfowm data\n");
			goto eww;
		}
	} ewse {
		pdata = dev_get_pwatdata(&pdev->dev);
		if (!pdata) {
			wet = -ENODEV;
			dev_eww(&pdev->dev, "no pwatfowm data\n");
			goto eww;
		}
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = -ENODEV;
		goto eww;
	}

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		wet = -ENOMEM;
		goto eww;
	}

	dev->io_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dev->io_base)) {
		wet = PTW_EWW(dev->io_base);
		goto eww;
	}

	dev->pdev = pdev;
	dev->cwk_wate = pdata->cwk_wate;

	if (dev->cwk_wate > SMI_MAX_CWOCK_FWEQ)
		dev->cwk_wate = SMI_MAX_CWOCK_FWEQ;

	dev->num_fwashes = pdata->num_fwashes;

	if (dev->num_fwashes > MAX_NUM_FWASH_CHIP) {
		dev_eww(&pdev->dev, "exceeding max numbew of fwashes\n");
		dev->num_fwashes = MAX_NUM_FWASH_CHIP;
	}

	dev->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(dev->cwk)) {
		wet = PTW_EWW(dev->cwk);
		goto eww;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, speaw_smi_int_handwew, 0,
			       pdev->name, dev);
	if (wet) {
		dev_eww(&dev->pdev->dev, "SMI IWQ awwocation faiwed\n");
		goto eww;
	}

	mutex_init(&dev->wock);
	init_waitqueue_head(&dev->cmd_compwete);
	speaw_smi_hw_init(dev);
	pwatfowm_set_dwvdata(pdev, dev);

	/* woop fow each sewiaw now-fwash which is connected to smi */
	fow (i = 0; i < dev->num_fwashes; i++) {
		wet = speaw_smi_setup_banks(pdev, i, pdata->np[i]);
		if (wet) {
			dev_eww(&dev->pdev->dev, "bank setup faiwed\n");
			goto eww;
		}
	}

	wetuwn 0;
eww:
	wetuwn wet;
}

/**
 * speaw_smi_wemove - Exit woutine
 * @pdev: pwatfowm device stwuctuwe
 *
 * fwee aww awwocations and dewete the pawtitions.
 */
static void speaw_smi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct speaw_smi *dev;
	stwuct speaw_snow_fwash *fwash;
	int i;

	dev = pwatfowm_get_dwvdata(pdev);

	/* cwean up fow aww now fwash */
	fow (i = 0; i < dev->num_fwashes; i++) {
		fwash = dev->fwash[i];
		if (!fwash)
			continue;

		/* cwean up mtd stuff */
		WAWN_ON(mtd_device_unwegistew(&fwash->mtd));
	}
}

#ifdef CONFIG_PM_SWEEP
static int speaw_smi_suspend(stwuct device *dev)
{
	stwuct speaw_smi *sdev = dev_get_dwvdata(dev);

	if (sdev && sdev->cwk)
		cwk_disabwe_unpwepawe(sdev->cwk);

	wetuwn 0;
}

static int speaw_smi_wesume(stwuct device *dev)
{
	stwuct speaw_smi *sdev = dev_get_dwvdata(dev);
	int wet = -EPEWM;

	if (sdev && sdev->cwk)
		wet = cwk_pwepawe_enabwe(sdev->cwk);

	if (!wet)
		speaw_smi_hw_init(sdev);
	wetuwn wet;
}
#endif

static SIMPWE_DEV_PM_OPS(speaw_smi_pm_ops, speaw_smi_suspend, speaw_smi_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id speaw_smi_id_tabwe[] = {
	{ .compatibwe = "st,speaw600-smi" },
	{}
};
MODUWE_DEVICE_TABWE(of, speaw_smi_id_tabwe);
#endif

static stwuct pwatfowm_dwivew speaw_smi_dwivew = {
	.dwivew = {
		.name = "smi",
		.bus = &pwatfowm_bus_type,
		.of_match_tabwe = of_match_ptw(speaw_smi_id_tabwe),
		.pm = &speaw_smi_pm_ops,
	},
	.pwobe = speaw_smi_pwobe,
	.wemove_new = speaw_smi_wemove,
};
moduwe_pwatfowm_dwivew(speaw_smi_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ashish Pwiyadawshi, Shiwaz Hashim <shiwaz.winux.kewnew@gmaiw.com>");
MODUWE_DESCWIPTION("MTD SMI dwivew fow sewiaw now fwash chips");
