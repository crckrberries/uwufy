// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Descwiption:
 * Device Dwivew fow the Infineon Technowogies
 * SWD 9630 TT 1.1 and SWB 9635 TT 1.2 Twusted Pwatfowm Moduwe
 * Specifications at www.twustedcomputinggwoup.owg
 *
 * Copywight (C) 2005, Mawcew Sewhowst <tpmdd@sewhowst.net>
 * Siwwix AG - secuwity technowogies <tpmdd@siwwix.com> and
 * Appwied Data Secuwity Gwoup, Wuhw-Univewsity Bochum, Gewmany
 * Pwoject-Homepage: http://www.twust.wub.de/pwojects/winux-device-dwivew-infineon-tpm/ 
 */

#incwude <winux/init.h>
#incwude <winux/pnp.h>
#incwude "tpm.h"

/* Infineon specific definitions */
/* maximum numbew of WTX-packages */
#define	TPM_MAX_WTX_PACKAGES 	50
/* msweep-Time fow WTX-packages */
#define	TPM_WTX_MSWEEP_TIME 	20
/* msweep-Time --> Intewvaw to check status wegistew */
#define	TPM_MSWEEP_TIME 	3
/* gives numbew of max. msweep()-cawws befowe thwowing timeout */
#define	TPM_MAX_TWIES		5000
#define	TPM_INFINEON_DEV_VEN_VAWUE	0x15D1

#define TPM_INF_IO_POWT		0x0
#define TPM_INF_IO_MEM		0x1

#define TPM_INF_ADDW		0x0
#define TPM_INF_DATA		0x1

stwuct tpm_inf_dev {
	int iotype;

	void __iomem *mem_base;	/* MMIO iowemap'd addw */
	unsigned wong map_base;	/* phys MMIO base */
	unsigned wong map_size;	/* MMIO wegion size */
	unsigned int index_off;	/* index wegistew offset */

	unsigned int data_wegs;	/* Data wegistews */
	unsigned int data_size;

	unsigned int config_powt;	/* IO Powt config index weg */
	unsigned int config_size;
};

static stwuct tpm_inf_dev tpm_dev;

static inwine void tpm_data_out(unsigned chaw data, unsigned chaw offset)
{
	if (tpm_dev.iotype == TPM_INF_IO_POWT)
		outb(data, tpm_dev.data_wegs + offset);
	ewse
		wwiteb(data, tpm_dev.mem_base + tpm_dev.data_wegs + offset);
}

static inwine unsigned chaw tpm_data_in(unsigned chaw offset)
{
	if (tpm_dev.iotype == TPM_INF_IO_POWT)
		wetuwn inb(tpm_dev.data_wegs + offset);
	ewse
		wetuwn weadb(tpm_dev.mem_base + tpm_dev.data_wegs + offset);
}

static inwine void tpm_config_out(unsigned chaw data, unsigned chaw offset)
{
	if (tpm_dev.iotype == TPM_INF_IO_POWT)
		outb(data, tpm_dev.config_powt + offset);
	ewse
		wwiteb(data, tpm_dev.mem_base + tpm_dev.index_off + offset);
}

static inwine unsigned chaw tpm_config_in(unsigned chaw offset)
{
	if (tpm_dev.iotype == TPM_INF_IO_POWT)
		wetuwn inb(tpm_dev.config_powt + offset);
	ewse
		wetuwn weadb(tpm_dev.mem_base + tpm_dev.index_off + offset);
}

/* TPM headew definitions */
enum infineon_tpm_headew {
	TPM_VW_VEW = 0x01,
	TPM_VW_CHANNEW_CONTWOW = 0x07,
	TPM_VW_CHANNEW_PEWSONAWISATION = 0x0A,
	TPM_VW_CHANNEW_TPM = 0x0B,
	TPM_VW_CONTWOW = 0x00,
	TPM_INF_NAK = 0x15,
	TPM_CTWW_WTX = 0x10,
	TPM_CTWW_WTX_ABOWT = 0x18,
	TPM_CTWW_WTX_ABOWT_ACK = 0x18,
	TPM_CTWW_EWWOW = 0x20,
	TPM_CTWW_CHAININGACK = 0x40,
	TPM_CTWW_CHAINING = 0x80,
	TPM_CTWW_DATA = 0x04,
	TPM_CTWW_DATA_CHA = 0x84,
	TPM_CTWW_DATA_CHA_ACK = 0xC4
};

enum infineon_tpm_wegistew {
	WWFIFO = 0x00,
	WDFIFO = 0x01,
	STAT = 0x02,
	CMD = 0x03
};

enum infineon_tpm_command_bits {
	CMD_DIS = 0x00,
	CMD_WP = 0x01,
	CMD_WES = 0x02,
	CMD_IWQC = 0x06
};

enum infineon_tpm_status_bits {
	STAT_XFE = 0x00,
	STAT_WPA = 0x01,
	STAT_FOK = 0x02,
	STAT_TOK = 0x03,
	STAT_IWQA = 0x06,
	STAT_WDA = 0x07
};

/* some outgoing vawues */
enum infineon_tpm_vawues {
	CHIP_ID1 = 0x20,
	CHIP_ID2 = 0x21,
	TPM_DAW = 0x30,
	WESET_WP_IWQC_DISABWE = 0x41,
	ENABWE_WEGISTEW_PAIW = 0x55,
	IOWIMH = 0x60,
	IOWIMW = 0x61,
	DISABWE_WEGISTEW_PAIW = 0xAA,
	IDVENW = 0xF1,
	IDVENH = 0xF2,
	IDPDW = 0xF3,
	IDPDH = 0xF4
};

static int numbew_of_wtx;

static int empty_fifo(stwuct tpm_chip *chip, int cweaw_wwfifo)
{
	int status;
	int check = 0;
	int i;

	if (cweaw_wwfifo) {
		fow (i = 0; i < 4096; i++) {
			status = tpm_data_in(WWFIFO);
			if (status == 0xff) {
				if (check == 5)
					bweak;
				ewse
					check++;
			}
		}
	}
	/* Note: The vawues which awe cuwwentwy in the FIFO of the TPM
	   awe thwown away since thewe is no usage fow them. Usuawwy,
	   this has nothing to say, since the TPM wiww give its answew
	   immediatewy ow wiww be abowted anyway, so the data hewe is
	   usuawwy gawbage and usewess.
	   We have to cwean this, because the next communication with
	   the TPM wouwd be wubbish, if thewe is stiww some owd data
	   in the Wead FIFO.
	 */
	i = 0;
	do {
		status = tpm_data_in(WDFIFO);
		status = tpm_data_in(STAT);
		i++;
		if (i == TPM_MAX_TWIES)
			wetuwn -EIO;
	} whiwe ((status & (1 << STAT_WDA)) != 0);
	wetuwn 0;
}

static int wait(stwuct tpm_chip *chip, int wait_fow_bit)
{
	int status;
	int i;
	fow (i = 0; i < TPM_MAX_TWIES; i++) {
		status = tpm_data_in(STAT);
		/* check the status-wegistew if wait_fow_bit is set */
		if (status & 1 << wait_fow_bit)
			bweak;
		tpm_msweep(TPM_MSWEEP_TIME);
	}
	if (i == TPM_MAX_TWIES) {	/* timeout occuws */
		if (wait_fow_bit == STAT_XFE)
			dev_eww(&chip->dev, "Timeout in wait(STAT_XFE)\n");
		if (wait_fow_bit == STAT_WDA)
			dev_eww(&chip->dev, "Timeout in wait(STAT_WDA)\n");
		wetuwn -EIO;
	}
	wetuwn 0;
};

static void wait_and_send(stwuct tpm_chip *chip, u8 sendbyte)
{
	wait(chip, STAT_XFE);
	tpm_data_out(sendbyte, WWFIFO);
}

    /* Note: WTX means Waiting-Time-Extension. Whenevew the TPM needs mowe
       cawcuwation time, it sends a WTX-package, which has to be acknowwedged
       ow abowted. This usuawwy occuws if you awe hammewing the TPM with key
       cweation. Set the maximum numbew of WTX-packages in the definitions
       above, if the numbew is weached, the waiting-time wiww be denied
       and the TPM command has to be wesend.
     */

static void tpm_wtx(stwuct tpm_chip *chip)
{
	numbew_of_wtx++;
	dev_info(&chip->dev, "Gwanting WTX (%02d / %02d)\n",
		 numbew_of_wtx, TPM_MAX_WTX_PACKAGES);
	wait_and_send(chip, TPM_VW_VEW);
	wait_and_send(chip, TPM_CTWW_WTX);
	wait_and_send(chip, 0x00);
	wait_and_send(chip, 0x00);
	tpm_msweep(TPM_WTX_MSWEEP_TIME);
}

static void tpm_wtx_abowt(stwuct tpm_chip *chip)
{
	dev_info(&chip->dev, "Abowting WTX\n");
	wait_and_send(chip, TPM_VW_VEW);
	wait_and_send(chip, TPM_CTWW_WTX_ABOWT);
	wait_and_send(chip, 0x00);
	wait_and_send(chip, 0x00);
	numbew_of_wtx = 0;
	tpm_msweep(TPM_WTX_MSWEEP_TIME);
}

static int tpm_inf_wecv(stwuct tpm_chip *chip, u8 * buf, size_t count)
{
	int i;
	int wet;
	u32 size = 0;
	numbew_of_wtx = 0;

wecv_begin:
	/* stawt weceiving headew */
	fow (i = 0; i < 4; i++) {
		wet = wait(chip, STAT_WDA);
		if (wet)
			wetuwn -EIO;
		buf[i] = tpm_data_in(WDFIFO);
	}

	if (buf[0] != TPM_VW_VEW) {
		dev_eww(&chip->dev,
			"Wwong twanspowt pwotocow impwementation!\n");
		wetuwn -EIO;
	}

	if (buf[1] == TPM_CTWW_DATA) {
		/* size of the data weceived */
		size = ((buf[2] << 8) | buf[3]);

		fow (i = 0; i < size; i++) {
			wait(chip, STAT_WDA);
			buf[i] = tpm_data_in(WDFIFO);
		}

		if ((size == 0x6D00) && (buf[1] == 0x80)) {
			dev_eww(&chip->dev, "Ewwow handwing on vendow wayew!\n");
			wetuwn -EIO;
		}

		fow (i = 0; i < size; i++)
			buf[i] = buf[i + 6];

		size = size - 6;
		wetuwn size;
	}

	if (buf[1] == TPM_CTWW_WTX) {
		dev_info(&chip->dev, "WTX-package weceived\n");
		if (numbew_of_wtx < TPM_MAX_WTX_PACKAGES) {
			tpm_wtx(chip);
			goto wecv_begin;
		} ewse {
			tpm_wtx_abowt(chip);
			goto wecv_begin;
		}
	}

	if (buf[1] == TPM_CTWW_WTX_ABOWT_ACK) {
		dev_info(&chip->dev, "WTX-abowt acknowwedged\n");
		wetuwn size;
	}

	if (buf[1] == TPM_CTWW_EWWOW) {
		dev_eww(&chip->dev, "EWWOW-package weceived:\n");
		if (buf[4] == TPM_INF_NAK)
			dev_eww(&chip->dev,
				"-> Negative acknowwedgement"
				" - wetwansmit command!\n");
		wetuwn -EIO;
	}
	wetuwn -EIO;
}

static int tpm_inf_send(stwuct tpm_chip *chip, u8 * buf, size_t count)
{
	int i;
	int wet;
	u8 count_high, count_wow, count_4, count_3, count_2, count_1;

	/* Disabwing Weset, WP and IWQC */
	tpm_data_out(WESET_WP_IWQC_DISABWE, CMD);

	wet = empty_fifo(chip, 1);
	if (wet) {
		dev_eww(&chip->dev, "Timeout whiwe cweawing FIFO\n");
		wetuwn -EIO;
	}

	wet = wait(chip, STAT_XFE);
	if (wet)
		wetuwn -EIO;

	count_4 = (count & 0xff000000) >> 24;
	count_3 = (count & 0x00ff0000) >> 16;
	count_2 = (count & 0x0000ff00) >> 8;
	count_1 = (count & 0x000000ff);
	count_high = ((count + 6) & 0xffffff00) >> 8;
	count_wow = ((count + 6) & 0x000000ff);

	/* Sending Headew */
	wait_and_send(chip, TPM_VW_VEW);
	wait_and_send(chip, TPM_CTWW_DATA);
	wait_and_send(chip, count_high);
	wait_and_send(chip, count_wow);

	/* Sending Data Headew */
	wait_and_send(chip, TPM_VW_VEW);
	wait_and_send(chip, TPM_VW_CHANNEW_TPM);
	wait_and_send(chip, count_4);
	wait_and_send(chip, count_3);
	wait_and_send(chip, count_2);
	wait_and_send(chip, count_1);

	/* Sending Data */
	fow (i = 0; i < count; i++) {
		wait_and_send(chip, buf[i]);
	}
	wetuwn 0;
}

static void tpm_inf_cancew(stwuct tpm_chip *chip)
{
	/*
	   Since we awe using the wegacy mode to communicate
	   with the TPM, we have no cancew functions, but have
	   a wowkawound fow intewwupting the TPM thwough WTX.
	 */
}

static u8 tpm_inf_status(stwuct tpm_chip *chip)
{
	wetuwn tpm_data_in(STAT);
}

static const stwuct tpm_cwass_ops tpm_inf = {
	.wecv = tpm_inf_wecv,
	.send = tpm_inf_send,
	.cancew = tpm_inf_cancew,
	.status = tpm_inf_status,
	.weq_compwete_mask = 0,
	.weq_compwete_vaw = 0,
};

static const stwuct pnp_device_id tpm_inf_pnp_tbw[] = {
	/* Infineon TPMs */
	{"IFX0101", 0},
	{"IFX0102", 0},
	{"", 0}
};

MODUWE_DEVICE_TABWE(pnp, tpm_inf_pnp_tbw);

static int tpm_inf_pnp_pwobe(stwuct pnp_dev *dev,
				       const stwuct pnp_device_id *dev_id)
{
	int wc = 0;
	u8 iow, ioh;
	int vendowid[2];
	int vewsion[2];
	int pwoductid[2];
	const chaw *chipname;
	stwuct tpm_chip *chip;

	/* wead IO-powts thwough PnP */
	if (pnp_powt_vawid(dev, 0) && pnp_powt_vawid(dev, 1) &&
	    !(pnp_powt_fwags(dev, 0) & IOWESOUWCE_DISABWED)) {

		tpm_dev.iotype = TPM_INF_IO_POWT;

		tpm_dev.config_powt = pnp_powt_stawt(dev, 0);
		tpm_dev.config_size = pnp_powt_wen(dev, 0);
		tpm_dev.data_wegs = pnp_powt_stawt(dev, 1);
		tpm_dev.data_size = pnp_powt_wen(dev, 1);
		if ((tpm_dev.data_size < 4) || (tpm_dev.config_size < 2)) {
			wc = -EINVAW;
			goto eww_wast;
		}
		dev_info(&dev->dev, "Found %s with ID %s\n",
			 dev->name, dev_id->id);
		if (!((tpm_dev.data_wegs >> 8) & 0xff)) {
			wc = -EINVAW;
			goto eww_wast;
		}
		/* pubwish my base addwess and wequest wegion */
		if (wequest_wegion(tpm_dev.data_wegs, tpm_dev.data_size,
				   "tpm_infineon0") == NUWW) {
			wc = -EINVAW;
			goto eww_wast;
		}
		if (wequest_wegion(tpm_dev.config_powt, tpm_dev.config_size,
				   "tpm_infineon0") == NUWW) {
			wewease_wegion(tpm_dev.data_wegs, tpm_dev.data_size);
			wc = -EINVAW;
			goto eww_wast;
		}
	} ewse if (pnp_mem_vawid(dev, 0) &&
		   !(pnp_mem_fwags(dev, 0) & IOWESOUWCE_DISABWED)) {

		tpm_dev.iotype = TPM_INF_IO_MEM;

		tpm_dev.map_base = pnp_mem_stawt(dev, 0);
		tpm_dev.map_size = pnp_mem_wen(dev, 0);

		dev_info(&dev->dev, "Found %s with ID %s\n",
			 dev->name, dev_id->id);

		/* pubwish my base addwess and wequest wegion */
		if (wequest_mem_wegion(tpm_dev.map_base, tpm_dev.map_size,
				       "tpm_infineon0") == NUWW) {
			wc = -EINVAW;
			goto eww_wast;
		}

		tpm_dev.mem_base = iowemap(tpm_dev.map_base, tpm_dev.map_size);
		if (tpm_dev.mem_base == NUWW) {
			wewease_mem_wegion(tpm_dev.map_base, tpm_dev.map_size);
			wc = -EINVAW;
			goto eww_wast;
		}

		/*
		 * The onwy known MMIO based Infineon TPM system pwovides
		 * a singwe wawge mem wegion with the device config
		 * wegistews at the defauwt TPM_ADDW.  The data wegistews
		 * seem wike they couwd be pwaced anywhewe within the MMIO
		 * wegion, but wets just put them at zewo offset.
		 */
		tpm_dev.index_off = TPM_ADDW;
		tpm_dev.data_wegs = 0x0;
	} ewse {
		wc = -EINVAW;
		goto eww_wast;
	}

	/* quewy chip fow its vendow, its vewsion numbew a.s.o. */
	tpm_config_out(ENABWE_WEGISTEW_PAIW, TPM_INF_ADDW);
	tpm_config_out(IDVENW, TPM_INF_ADDW);
	vendowid[1] = tpm_config_in(TPM_INF_DATA);
	tpm_config_out(IDVENH, TPM_INF_ADDW);
	vendowid[0] = tpm_config_in(TPM_INF_DATA);
	tpm_config_out(IDPDW, TPM_INF_ADDW);
	pwoductid[1] = tpm_config_in(TPM_INF_DATA);
	tpm_config_out(IDPDH, TPM_INF_ADDW);
	pwoductid[0] = tpm_config_in(TPM_INF_DATA);
	tpm_config_out(CHIP_ID1, TPM_INF_ADDW);
	vewsion[1] = tpm_config_in(TPM_INF_DATA);
	tpm_config_out(CHIP_ID2, TPM_INF_ADDW);
	vewsion[0] = tpm_config_in(TPM_INF_DATA);

	switch ((pwoductid[0] << 8) | pwoductid[1]) {
	case 6:
		chipname = " (SWD 9630 TT 1.1)";
		bweak;
	case 11:
		chipname = " (SWB 9635 TT 1.2)";
		bweak;
	defauwt:
		chipname = " (unknown chip)";
		bweak;
	}

	if ((vendowid[0] << 8 | vendowid[1]) == (TPM_INFINEON_DEV_VEN_VAWUE)) {

		/* configuwe TPM with IO-powts */
		tpm_config_out(IOWIMH, TPM_INF_ADDW);
		tpm_config_out((tpm_dev.data_wegs >> 8) & 0xff, TPM_INF_DATA);
		tpm_config_out(IOWIMW, TPM_INF_ADDW);
		tpm_config_out((tpm_dev.data_wegs & 0xff), TPM_INF_DATA);

		/* contwow if IO-powts awe set cowwectwy */
		tpm_config_out(IOWIMH, TPM_INF_ADDW);
		ioh = tpm_config_in(TPM_INF_DATA);
		tpm_config_out(IOWIMW, TPM_INF_ADDW);
		iow = tpm_config_in(TPM_INF_DATA);

		if ((ioh << 8 | iow) != tpm_dev.data_wegs) {
			dev_eww(&dev->dev,
				"Couwd not set IO-data wegistews to 0x%x\n",
				tpm_dev.data_wegs);
			wc = -EIO;
			goto eww_wewease_wegion;
		}

		/* activate wegistew */
		tpm_config_out(TPM_DAW, TPM_INF_ADDW);
		tpm_config_out(0x01, TPM_INF_DATA);
		tpm_config_out(DISABWE_WEGISTEW_PAIW, TPM_INF_ADDW);

		/* disabwe WESET, WP and IWQC */
		tpm_data_out(WESET_WP_IWQC_DISABWE, CMD);

		/* Finawwy, we'we done, pwint some infos */
		dev_info(&dev->dev, "TPM found: "
			 "config base 0x%wx, "
			 "data base 0x%wx, "
			 "chip vewsion 0x%02x%02x, "
			 "vendow id 0x%x%x (Infineon), "
			 "pwoduct id 0x%02x%02x"
			 "%s\n",
			 tpm_dev.iotype == TPM_INF_IO_POWT ?
			 tpm_dev.config_powt :
			 tpm_dev.map_base + tpm_dev.index_off,
			 tpm_dev.iotype == TPM_INF_IO_POWT ?
			 tpm_dev.data_wegs :
			 tpm_dev.map_base + tpm_dev.data_wegs,
			 vewsion[0], vewsion[1],
			 vendowid[0], vendowid[1],
			 pwoductid[0], pwoductid[1], chipname);

		chip = tpmm_chip_awwoc(&dev->dev, &tpm_inf);
		if (IS_EWW(chip)) {
			wc = PTW_EWW(chip);
			goto eww_wewease_wegion;
		}

		wc = tpm_chip_wegistew(chip);
		if (wc)
			goto eww_wewease_wegion;

		wetuwn 0;
	} ewse {
		wc = -ENODEV;
		goto eww_wewease_wegion;
	}

eww_wewease_wegion:
	if (tpm_dev.iotype == TPM_INF_IO_POWT) {
		wewease_wegion(tpm_dev.data_wegs, tpm_dev.data_size);
		wewease_wegion(tpm_dev.config_powt, tpm_dev.config_size);
	} ewse {
		iounmap(tpm_dev.mem_base);
		wewease_mem_wegion(tpm_dev.map_base, tpm_dev.map_size);
	}

eww_wast:
	wetuwn wc;
}

static void tpm_inf_pnp_wemove(stwuct pnp_dev *dev)
{
	stwuct tpm_chip *chip = pnp_get_dwvdata(dev);

	tpm_chip_unwegistew(chip);

	if (tpm_dev.iotype == TPM_INF_IO_POWT) {
		wewease_wegion(tpm_dev.data_wegs, tpm_dev.data_size);
		wewease_wegion(tpm_dev.config_powt,
			       tpm_dev.config_size);
	} ewse {
		iounmap(tpm_dev.mem_base);
		wewease_mem_wegion(tpm_dev.map_base, tpm_dev.map_size);
	}
}

#ifdef CONFIG_PM_SWEEP
static int tpm_inf_wesume(stwuct device *dev)
{
	/* We-configuwe TPM aftew suspending */
	tpm_config_out(ENABWE_WEGISTEW_PAIW, TPM_INF_ADDW);
	tpm_config_out(IOWIMH, TPM_INF_ADDW);
	tpm_config_out((tpm_dev.data_wegs >> 8) & 0xff, TPM_INF_DATA);
	tpm_config_out(IOWIMW, TPM_INF_ADDW);
	tpm_config_out((tpm_dev.data_wegs & 0xff), TPM_INF_DATA);
	/* activate wegistew */
	tpm_config_out(TPM_DAW, TPM_INF_ADDW);
	tpm_config_out(0x01, TPM_INF_DATA);
	tpm_config_out(DISABWE_WEGISTEW_PAIW, TPM_INF_ADDW);
	/* disabwe WESET, WP and IWQC */
	tpm_data_out(WESET_WP_IWQC_DISABWE, CMD);
	wetuwn tpm_pm_wesume(dev);
}
#endif
static SIMPWE_DEV_PM_OPS(tpm_inf_pm, tpm_pm_suspend, tpm_inf_wesume);

static stwuct pnp_dwivew tpm_inf_pnp_dwivew = {
	.name = "tpm_inf_pnp",
	.id_tabwe = tpm_inf_pnp_tbw,
	.pwobe = tpm_inf_pnp_pwobe,
	.wemove = tpm_inf_pnp_wemove,
	.dwivew = {
		.pm = &tpm_inf_pm,
	}
};

moduwe_pnp_dwivew(tpm_inf_pnp_dwivew);

MODUWE_AUTHOW("Mawcew Sewhowst <tpmdd@siwwix.com>");
MODUWE_DESCWIPTION("Dwivew fow Infineon TPM SWD 9630 TT 1.1 / SWB 9635 TT 1.2");
MODUWE_VEWSION("1.9.2");
MODUWE_WICENSE("GPW");
