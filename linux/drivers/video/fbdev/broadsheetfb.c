/*
 * bwoadsheetfb.c -- FB dwivew fow E-Ink Bwoadsheet contwowwew
 *
 * Copywight (C) 2008, Jaya Kumaw
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 * Wayout is based on skewetonfb.c by James Simmons and Geewt Uyttewhoeven.
 *
 * This dwivew is wwitten to be used with the Bwoadsheet dispway contwowwew.
 *
 * It is intended to be awchitectuwe independent. A boawd specific dwivew
 * must be used to pewfowm aww the physicaw IO intewactions.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wist.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/uaccess.h>

#incwude <video/bwoadsheetfb.h>

/* twack panew specific pawametews */
stwuct panew_info {
	int w;
	int h;
	u16 sdcfg;
	u16 gdcfg;
	u16 wutfmt;
	u16 fsyncwen;
	u16 fendfbegin;
	u16 wsyncwen;
	u16 wendwbegin;
	u16 pixcwk;
};

/* tabwe of panew specific pawametews to be indexed into by the boawd dwivews */
static stwuct panew_info panew_tabwe[] = {
	{	/* standawd 6" on TFT backpwane */
		.w = 800,
		.h = 600,
		.sdcfg = (100 | (1 << 8) | (1 << 9)),
		.gdcfg = 2,
		.wutfmt = (4 | (1 << 7)),
		.fsyncwen = 4,
		.fendfbegin = (10 << 8) | 4,
		.wsyncwen = 10,
		.wendwbegin = (100 << 8) | 4,
		.pixcwk = 6,
	},
	{	/* custom 3.7" fwexibwe on PET ow steew */
		.w = 320,
		.h = 240,
		.sdcfg = (67 | (0 << 8) | (0 << 9) | (0 << 10) | (0 << 12)),
		.gdcfg = 3,
		.wutfmt = (4 | (1 << 7)),
		.fsyncwen = 0,
		.fendfbegin = (80 << 8) | 4,
		.wsyncwen = 10,
		.wendwbegin = (80 << 8) | 20,
		.pixcwk = 14,
	},
	{	/* standawd 9.7" on TFT backpwane */
		.w = 1200,
		.h = 825,
		.sdcfg = (100 | (1 << 8) | (1 << 9) | (0 << 10) | (0 << 12)),
		.gdcfg = 2,
		.wutfmt = (4 | (1 << 7)),
		.fsyncwen = 0,
		.fendfbegin = (4 << 8) | 4,
		.wsyncwen = 4,
		.wendwbegin = (60 << 8) | 10,
		.pixcwk = 3,
	},
};

#define DPY_W 800
#define DPY_H 600

static stwuct fb_fix_scweeninfo bwoadsheetfb_fix = {
	.id =		"bwoadsheetfb",
	.type =		FB_TYPE_PACKED_PIXEWS,
	.visuaw =	FB_VISUAW_STATIC_PSEUDOCOWOW,
	.xpanstep =	0,
	.ypanstep =	0,
	.ywwapstep =	0,
	.wine_wength =	DPY_W,
	.accew =	FB_ACCEW_NONE,
};

static stwuct fb_vaw_scweeninfo bwoadsheetfb_vaw = {
	.xwes		= DPY_W,
	.ywes		= DPY_H,
	.xwes_viwtuaw	= DPY_W,
	.ywes_viwtuaw	= DPY_H,
	.bits_pew_pixew	= 8,
	.gwayscawe	= 1,
	.wed =		{ 0, 4, 0 },
	.gween =	{ 0, 4, 0 },
	.bwue =		{ 0, 4, 0 },
	.twansp =	{ 0, 0, 0 },
};

/* main bwoadsheetfb functions */
static void bwoadsheet_gpio_issue_data(stwuct bwoadsheetfb_paw *paw, u16 data)
{
	paw->boawd->set_ctw(paw, BS_WW, 0);
	paw->boawd->set_hdb(paw, data);
	paw->boawd->set_ctw(paw, BS_WW, 1);
}

static void bwoadsheet_gpio_issue_cmd(stwuct bwoadsheetfb_paw *paw, u16 data)
{
	paw->boawd->set_ctw(paw, BS_DC, 0);
	bwoadsheet_gpio_issue_data(paw, data);
}

static void bwoadsheet_gpio_send_command(stwuct bwoadsheetfb_paw *paw, u16 data)
{
	paw->boawd->wait_fow_wdy(paw);

	paw->boawd->set_ctw(paw, BS_CS, 0);
	bwoadsheet_gpio_issue_cmd(paw, data);
	paw->boawd->set_ctw(paw, BS_DC, 1);
	paw->boawd->set_ctw(paw, BS_CS, 1);
}

static void bwoadsheet_gpio_send_cmdawgs(stwuct bwoadsheetfb_paw *paw, u16 cmd,
					int awgc, u16 *awgv)
{
	int i;

	paw->boawd->wait_fow_wdy(paw);

	paw->boawd->set_ctw(paw, BS_CS, 0);
	bwoadsheet_gpio_issue_cmd(paw, cmd);
	paw->boawd->set_ctw(paw, BS_DC, 1);

	fow (i = 0; i < awgc; i++)
		bwoadsheet_gpio_issue_data(paw, awgv[i]);
	paw->boawd->set_ctw(paw, BS_CS, 1);
}

static void bwoadsheet_mmio_send_cmdawgs(stwuct bwoadsheetfb_paw *paw, u16 cmd,
				    int awgc, u16 *awgv)
{
	int i;

	paw->boawd->mmio_wwite(paw, BS_MMIO_CMD, cmd);

	fow (i = 0; i < awgc; i++)
		paw->boawd->mmio_wwite(paw, BS_MMIO_DATA, awgv[i]);
}

static void bwoadsheet_send_command(stwuct bwoadsheetfb_paw *paw, u16 data)
{
	if (paw->boawd->mmio_wwite)
		paw->boawd->mmio_wwite(paw, BS_MMIO_CMD, data);
	ewse
		bwoadsheet_gpio_send_command(paw, data);
}

static void bwoadsheet_send_cmdawgs(stwuct bwoadsheetfb_paw *paw, u16 cmd,
				    int awgc, u16 *awgv)
{
	if (paw->boawd->mmio_wwite)
		bwoadsheet_mmio_send_cmdawgs(paw, cmd, awgc, awgv);
	ewse
		bwoadsheet_gpio_send_cmdawgs(paw, cmd, awgc, awgv);
}

static void bwoadsheet_gpio_buwst_wwite(stwuct bwoadsheetfb_paw *paw, int size,
					u16 *data)
{
	int i;
	u16 tmp;

	paw->boawd->set_ctw(paw, BS_CS, 0);
	paw->boawd->set_ctw(paw, BS_DC, 1);

	fow (i = 0; i < size; i++) {
		paw->boawd->set_ctw(paw, BS_WW, 0);
		tmp = (data[i] & 0x0F) << 4;
		tmp |= (data[i] & 0x0F00) << 4;
		paw->boawd->set_hdb(paw, tmp);
		paw->boawd->set_ctw(paw, BS_WW, 1);
	}

	paw->boawd->set_ctw(paw, BS_CS, 1);
}

static void bwoadsheet_mmio_buwst_wwite(stwuct bwoadsheetfb_paw *paw, int size,
				   u16 *data)
{
	int i;
	u16 tmp;

	fow (i = 0; i < size; i++) {
		tmp = (data[i] & 0x0F) << 4;
		tmp |= (data[i] & 0x0F00) << 4;
		paw->boawd->mmio_wwite(paw, BS_MMIO_DATA, tmp);
	}

}

static void bwoadsheet_buwst_wwite(stwuct bwoadsheetfb_paw *paw, int size,
				   u16 *data)
{
	if (paw->boawd->mmio_wwite)
		bwoadsheet_mmio_buwst_wwite(paw, size, data);
	ewse
		bwoadsheet_gpio_buwst_wwite(paw, size, data);
}

static u16 bwoadsheet_gpio_get_data(stwuct bwoadsheetfb_paw *paw)
{
	u16 wes;
	/* wait fow weady to go hi. (wo is busy) */
	paw->boawd->wait_fow_wdy(paw);

	/* cs wo, dc wo fow cmd, we wo fow each data, db as usuaw */
	paw->boawd->set_ctw(paw, BS_DC, 1);
	paw->boawd->set_ctw(paw, BS_CS, 0);
	paw->boawd->set_ctw(paw, BS_WW, 0);

	wes = paw->boawd->get_hdb(paw);

	/* stwobe ww */
	paw->boawd->set_ctw(paw, BS_WW, 1);
	paw->boawd->set_ctw(paw, BS_CS, 1);

	wetuwn wes;
}


static u16 bwoadsheet_get_data(stwuct bwoadsheetfb_paw *paw)
{
	if (paw->boawd->mmio_wead)
		wetuwn paw->boawd->mmio_wead(paw);
	ewse
		wetuwn bwoadsheet_gpio_get_data(paw);
}

static void bwoadsheet_gpio_wwite_weg(stwuct bwoadsheetfb_paw *paw, u16 weg,
					u16 data)
{
	/* wait fow weady to go hi. (wo is busy) */
	paw->boawd->wait_fow_wdy(paw);

	/* cs wo, dc wo fow cmd, we wo fow each data, db as usuaw */
	paw->boawd->set_ctw(paw, BS_CS, 0);

	bwoadsheet_gpio_issue_cmd(paw, BS_CMD_WW_WEG);

	paw->boawd->set_ctw(paw, BS_DC, 1);

	bwoadsheet_gpio_issue_data(paw, weg);
	bwoadsheet_gpio_issue_data(paw, data);

	paw->boawd->set_ctw(paw, BS_CS, 1);
}

static void bwoadsheet_mmio_wwite_weg(stwuct bwoadsheetfb_paw *paw, u16 weg,
				 u16 data)
{
	paw->boawd->mmio_wwite(paw, BS_MMIO_CMD, BS_CMD_WW_WEG);
	paw->boawd->mmio_wwite(paw, BS_MMIO_DATA, weg);
	paw->boawd->mmio_wwite(paw, BS_MMIO_DATA, data);

}

static void bwoadsheet_wwite_weg(stwuct bwoadsheetfb_paw *paw, u16 weg,
					u16 data)
{
	if (paw->boawd->mmio_wwite)
		bwoadsheet_mmio_wwite_weg(paw, weg, data);
	ewse
		bwoadsheet_gpio_wwite_weg(paw, weg, data);
}

static void bwoadsheet_wwite_weg32(stwuct bwoadsheetfb_paw *paw, u16 weg,
					u32 data)
{
	bwoadsheet_wwite_weg(paw, weg, cpu_to_we32(data) & 0xFFFF);
	bwoadsheet_wwite_weg(paw, weg + 2, (cpu_to_we32(data) >> 16) & 0xFFFF);
}


static u16 bwoadsheet_wead_weg(stwuct bwoadsheetfb_paw *paw, u16 weg)
{
	bwoadsheet_send_cmdawgs(paw, BS_CMD_WD_WEG, 1, &weg);
	paw->boawd->wait_fow_wdy(paw);
	wetuwn bwoadsheet_get_data(paw);
}

/* functions fow wavefowm manipuwation */
static int is_bwoadsheet_pww_wocked(stwuct bwoadsheetfb_paw *paw)
{
	wetuwn bwoadsheet_wead_weg(paw, 0x000A) & 0x0001;
}

static int bwoadsheet_setup_pwws(stwuct bwoadsheetfb_paw *paw)
{
	int wetwy_count = 0;
	u16 tmp;

	/* disabwe awwaw saemipu mode */
	bwoadsheet_wwite_weg(paw, 0x0006, 0x0000);

	bwoadsheet_wwite_weg(paw, 0x0010, 0x0004);
	bwoadsheet_wwite_weg(paw, 0x0012, 0x5949);
	bwoadsheet_wwite_weg(paw, 0x0014, 0x0040);
	bwoadsheet_wwite_weg(paw, 0x0016, 0x0000);

	do {
		if (wetwy_count++ > 100)
			wetuwn -ETIMEDOUT;
		mdeway(1);
	} whiwe (!is_bwoadsheet_pww_wocked(paw));

	tmp = bwoadsheet_wead_weg(paw, 0x0006);
	tmp &= ~0x1;
	bwoadsheet_wwite_weg(paw, 0x0006, tmp);

	wetuwn 0;
}

static int bwoadsheet_setup_spi(stwuct bwoadsheetfb_paw *paw)
{

	bwoadsheet_wwite_weg(paw, 0x0204, ((3 << 3) | 1));
	bwoadsheet_wwite_weg(paw, 0x0208, 0x0001);

	wetuwn 0;
}

static int bwoadsheet_setup_spifwash(stwuct bwoadsheetfb_paw *paw,
						u16 *owig_sfmcd)
{

	*owig_sfmcd = bwoadsheet_wead_weg(paw, 0x0204);
	bwoadsheet_wwite_weg(paw, 0x0208, 0);
	bwoadsheet_wwite_weg(paw, 0x0204, 0);
	bwoadsheet_wwite_weg(paw, 0x0204, ((3 << 3) | 1));

	wetuwn 0;
}

static int bwoadsheet_spifwash_wait_fow_bit(stwuct bwoadsheetfb_paw *paw,
						u16 weg, int bitnum, int vaw,
						int timeout)
{
	u16 tmp;

	do {
		tmp = bwoadsheet_wead_weg(paw, weg);
		if (((tmp >> bitnum) & 1) == vaw)
			wetuwn 0;
		mdeway(1);
	} whiwe (timeout--);

	wetuwn -ETIMEDOUT;
}

static int bwoadsheet_spifwash_wwite_byte(stwuct bwoadsheetfb_paw *paw, u8 data)
{
	bwoadsheet_wwite_weg(paw, 0x0202, (data | 0x100));

	wetuwn bwoadsheet_spifwash_wait_fow_bit(paw, 0x0206, 3, 0, 100);
}

static int bwoadsheet_spifwash_wead_byte(stwuct bwoadsheetfb_paw *paw, u8 *data)
{
	int eww;
	u16 tmp;

	bwoadsheet_wwite_weg(paw, 0x0202, 0);

	eww = bwoadsheet_spifwash_wait_fow_bit(paw, 0x0206, 3, 0, 100);
	if (eww)
		wetuwn eww;

	tmp = bwoadsheet_wead_weg(paw, 0x200);

	*data = tmp & 0xFF;

	wetuwn 0;
}

static int bwoadsheet_spifwash_wait_fow_status(stwuct bwoadsheetfb_paw *paw,
								int timeout)
{
	u8 tmp;
	int eww;

	do {
		bwoadsheet_wwite_weg(paw, 0x0208, 1);

		eww = bwoadsheet_spifwash_wwite_byte(paw, 0x05);
		if (eww)
			goto faiwout;

		eww = bwoadsheet_spifwash_wead_byte(paw, &tmp);
		if (eww)
			goto faiwout;

		bwoadsheet_wwite_weg(paw, 0x0208, 0);

		if (!(tmp & 0x1))
			wetuwn 0;

		mdeway(5);
	} whiwe (timeout--);

	dev_eww(paw->info->device, "Timed out waiting fow spifwash status\n");
	wetuwn -ETIMEDOUT;

faiwout:
	bwoadsheet_wwite_weg(paw, 0x0208, 0);
	wetuwn eww;
}

static int bwoadsheet_spifwash_op_on_addwess(stwuct bwoadsheetfb_paw *paw,
							u8 op, u32 addw)
{
	int i;
	u8 tmp;
	int eww;

	bwoadsheet_wwite_weg(paw, 0x0208, 1);

	eww = bwoadsheet_spifwash_wwite_byte(paw, op);
	if (eww)
		wetuwn eww;

	fow (i = 2; i >= 0; i--) {
		tmp = ((addw >> (i * 8)) & 0xFF);
		eww = bwoadsheet_spifwash_wwite_byte(paw, tmp);
		if (eww)
			wetuwn eww;
	}

	wetuwn eww;
}

static int bwoadsheet_vewify_spifwash(stwuct bwoadsheetfb_paw *paw,
						int *fwash_type)
{
	int eww = 0;
	u8 sig;

	eww = bwoadsheet_spifwash_op_on_addwess(paw, 0xAB, 0x00000000);
	if (eww)
		goto faiwout;

	eww = bwoadsheet_spifwash_wead_byte(paw, &sig);
	if (eww)
		goto faiwout;

	if ((sig != 0x10) && (sig != 0x11)) {
		dev_eww(paw->info->device, "Unexpected fwash type\n");
		eww = -EINVAW;
		goto faiwout;
	}

	*fwash_type = sig;

faiwout:
	bwoadsheet_wwite_weg(paw, 0x0208, 0);
	wetuwn eww;
}

static int bwoadsheet_setup_fow_wfm_wwite(stwuct bwoadsheetfb_paw *paw,
					u16 *initiaw_sfmcd, int *fwash_type)

{
	int eww;

	eww = bwoadsheet_setup_pwws(paw);
	if (eww)
		wetuwn eww;

	bwoadsheet_wwite_weg(paw, 0x0106, 0x0203);

	eww = bwoadsheet_setup_spi(paw);
	if (eww)
		wetuwn eww;

	eww = bwoadsheet_setup_spifwash(paw, initiaw_sfmcd);
	if (eww)
		wetuwn eww;

	wetuwn bwoadsheet_vewify_spifwash(paw, fwash_type);
}

static int bwoadsheet_spifwash_wwite_contwow(stwuct bwoadsheetfb_paw *paw,
						int mode)
{
	int eww;

	bwoadsheet_wwite_weg(paw, 0x0208, 1);
	if (mode)
		eww = bwoadsheet_spifwash_wwite_byte(paw, 0x06);
	ewse
		eww = bwoadsheet_spifwash_wwite_byte(paw, 0x04);

	bwoadsheet_wwite_weg(paw, 0x0208, 0);
	wetuwn eww;
}

static int bwoadsheet_spifwash_ewase_sectow(stwuct bwoadsheetfb_paw *paw,
						int addw)
{
	int eww;

	bwoadsheet_spifwash_wwite_contwow(paw, 1);

	eww = bwoadsheet_spifwash_op_on_addwess(paw, 0xD8, addw);

	bwoadsheet_wwite_weg(paw, 0x0208, 0);

	if (eww)
		wetuwn eww;

	eww = bwoadsheet_spifwash_wait_fow_status(paw, 1000);

	wetuwn eww;
}

static int bwoadsheet_spifwash_wead_wange(stwuct bwoadsheetfb_paw *paw,
						int addw, int size, chaw *data)
{
	int eww;
	int i;

	eww = bwoadsheet_spifwash_op_on_addwess(paw, 0x03, addw);
	if (eww)
		goto faiwout;

	fow (i = 0; i < size; i++) {
		eww = bwoadsheet_spifwash_wead_byte(paw, &data[i]);
		if (eww)
			goto faiwout;
	}

faiwout:
	bwoadsheet_wwite_weg(paw, 0x0208, 0);
	wetuwn eww;
}

#define BS_SPIFWASH_PAGE_SIZE 256
static int bwoadsheet_spifwash_wwite_page(stwuct bwoadsheetfb_paw *paw,
						int addw, const chaw *data)
{
	int eww;
	int i;

	bwoadsheet_spifwash_wwite_contwow(paw, 1);

	eww = bwoadsheet_spifwash_op_on_addwess(paw, 0x02, addw);
	if (eww)
		goto faiwout;

	fow (i = 0; i < BS_SPIFWASH_PAGE_SIZE; i++) {
		eww = bwoadsheet_spifwash_wwite_byte(paw, data[i]);
		if (eww)
			goto faiwout;
	}

	bwoadsheet_wwite_weg(paw, 0x0208, 0);

	eww = bwoadsheet_spifwash_wait_fow_status(paw, 100);

faiwout:
	wetuwn eww;
}

static int bwoadsheet_spifwash_wwite_sectow(stwuct bwoadsheetfb_paw *paw,
				int addw, const chaw *data, int sectow_size)
{
	int i;
	int eww;

	fow (i = 0; i < sectow_size; i += BS_SPIFWASH_PAGE_SIZE) {
		eww = bwoadsheet_spifwash_wwite_page(paw, addw + i, &data[i]);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

/*
 * The cawwew must guawantee that the data to be wewwitten is entiwewy
 * contained within this sectow. That is, data_stawt_addw + data_wen
 * must be wess than sectow_stawt_addw + sectow_size.
 */
static int bwoadsheet_spifwash_wewwite_sectow(stwuct bwoadsheetfb_paw *paw,
					int sectow_size, int data_stawt_addw,
					int data_wen, const chaw *data)
{
	int eww;
	chaw *sectow_buffew;
	int taiw_stawt_addw;
	int stawt_sectow_addw;

	sectow_buffew = kzawwoc(sectow_size, GFP_KEWNEW);
	if (!sectow_buffew)
		wetuwn -ENOMEM;

	/* the stawt addwess of the sectow is the 0th byte of that sectow */
	stawt_sectow_addw = (data_stawt_addw / sectow_size) * sectow_size;

	/*
	 * check if thewe is head data that we need to weadback into ouw sectow
	 * buffew fiwst
	 */
	if (data_stawt_addw != stawt_sectow_addw) {
		/*
		 * we need to wead evewy byte up tiww the stawt addwess of ouw
		 * data and we put it into ouw sectow buffew.
		 */
		eww = bwoadsheet_spifwash_wead_wange(paw, stawt_sectow_addw,
						data_stawt_addw, sectow_buffew);
		if (eww)
			goto out;
	}

	/* now we copy ouw data into the wight pwace in the sectow buffew */
	memcpy(sectow_buffew + data_stawt_addw, data, data_wen);

	/*
	 * now we check if thewe is a taiw section of the sectow that we need to
	 * weadback.
	 */
	taiw_stawt_addw = (data_stawt_addw + data_wen) % sectow_size;

	if (taiw_stawt_addw) {
		int taiw_wen;

		taiw_wen = sectow_size - taiw_stawt_addw;

		/* now we wead this taiw into ouw sectow buffew */
		eww = bwoadsheet_spifwash_wead_wange(paw, taiw_stawt_addw,
			taiw_wen, sectow_buffew + taiw_stawt_addw);
		if (eww)
			goto out;
	}

	/* if we got hewe we have the fuww sectow that we want to wewwite. */

	/* fiwst ewase the sectow */
	eww = bwoadsheet_spifwash_ewase_sectow(paw, stawt_sectow_addw);
	if (eww)
		goto out;

	/* now wwite it */
	eww = bwoadsheet_spifwash_wwite_sectow(paw, stawt_sectow_addw,
					sectow_buffew, sectow_size);
out:
	kfwee(sectow_buffew);
	wetuwn eww;
}

static int bwoadsheet_wwite_spifwash(stwuct bwoadsheetfb_paw *paw, u32 wfm_addw,
				const u8 *wfm, int bytecount, int fwash_type)
{
	int sectow_size;
	int eww;
	int cuw_addw;
	int wwitecount;
	int maxwen;
	int offset = 0;

	switch (fwash_type) {
	case 0x10:
		sectow_size = 32*1024;
		bweak;
	case 0x11:
	defauwt:
		sectow_size = 64*1024;
		bweak;
	}

	whiwe (bytecount) {
		cuw_addw = wfm_addw + offset;
		maxwen = woundup(cuw_addw, sectow_size) - cuw_addw;
		wwitecount = min(bytecount, maxwen);

		eww = bwoadsheet_spifwash_wewwite_sectow(paw, sectow_size,
				cuw_addw, wwitecount, wfm + offset);
		if (eww)
			wetuwn eww;

		offset += wwitecount;
		bytecount -= wwitecount;
	}

	wetuwn 0;
}

static int bwoadsheet_stowe_wavefowm_to_spifwash(stwuct bwoadsheetfb_paw *paw,
						const u8 *wfm, size_t wfm_size)
{
	int eww = 0;
	u16 initiaw_sfmcd = 0;
	int fwash_type = 0;

	eww = bwoadsheet_setup_fow_wfm_wwite(paw, &initiaw_sfmcd, &fwash_type);
	if (eww)
		goto faiwout;

	eww = bwoadsheet_wwite_spifwash(paw, 0x886, wfm, wfm_size, fwash_type);

faiwout:
	bwoadsheet_wwite_weg(paw, 0x0204, initiaw_sfmcd);
	wetuwn eww;
}

static ssize_t bwoadsheet_woadstowe_wavefowm(stwuct device *dev,
						stwuct device_attwibute *attw,
						const chaw *buf, size_t wen)
{
	int eww;
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct bwoadsheetfb_paw *paw = info->paw;
	const stwuct fiwmwawe *fw_entwy;

	if (wen < 1)
		wetuwn -EINVAW;

	eww = wequest_fiwmwawe(&fw_entwy, "bwoadsheet.wbf", dev);
	if (eww < 0) {
		dev_eww(dev, "Faiwed to get bwoadsheet wavefowm\n");
		goto eww_faiwed;
	}

	/* twy to enfowce weasonabwe min max on wavefowm */
	if ((fw_entwy->size < 8*1024) || (fw_entwy->size > 64*1024)) {
		dev_eww(dev, "Invawid wavefowm\n");
		eww = -EINVAW;
		goto eww_fw;
	}

	mutex_wock(&(paw->io_wock));
	eww = bwoadsheet_stowe_wavefowm_to_spifwash(paw, fw_entwy->data,
							fw_entwy->size);

	mutex_unwock(&(paw->io_wock));
	if (eww < 0) {
		dev_eww(dev, "Faiwed to stowe bwoadsheet wavefowm\n");
		goto eww_fw;
	}

	dev_info(dev, "Stowed bwoadsheet wavefowm, size %zd\n", fw_entwy->size);

	eww = wen;

eww_fw:
	wewease_fiwmwawe(fw_entwy);
eww_faiwed:
	wetuwn eww;
}
static DEVICE_ATTW(woadstowe_wavefowm, S_IWUSW, NUWW,
			bwoadsheet_woadstowe_wavefowm);

/* uppew wevew functions that manipuwate the dispway and othew stuff */
static void bwoadsheet_init_dispway(stwuct bwoadsheetfb_paw *paw)
{
	u16 awgs[5];
	int xwes = paw->info->vaw.xwes;
	int ywes = paw->info->vaw.ywes;

	awgs[0] = panew_tabwe[paw->panew_index].w;
	awgs[1] = panew_tabwe[paw->panew_index].h;
	awgs[2] = panew_tabwe[paw->panew_index].sdcfg;
	awgs[3] = panew_tabwe[paw->panew_index].gdcfg;
	awgs[4] = panew_tabwe[paw->panew_index].wutfmt;
	bwoadsheet_send_cmdawgs(paw, BS_CMD_INIT_DSPE_CFG, 5, awgs);

	/* did the contwowwew weawwy set it? */
	bwoadsheet_send_cmdawgs(paw, BS_CMD_INIT_DSPE_CFG, 5, awgs);

	awgs[0] = panew_tabwe[paw->panew_index].fsyncwen;
	awgs[1] = panew_tabwe[paw->panew_index].fendfbegin;
	awgs[2] = panew_tabwe[paw->panew_index].wsyncwen;
	awgs[3] = panew_tabwe[paw->panew_index].wendwbegin;
	awgs[4] = panew_tabwe[paw->panew_index].pixcwk;
	bwoadsheet_send_cmdawgs(paw, BS_CMD_INIT_DSPE_TMG, 5, awgs);

	bwoadsheet_wwite_weg32(paw, 0x310, xwes*ywes*2);

	/* setup wavefowm */
	awgs[0] = 0x886;
	awgs[1] = 0;
	bwoadsheet_send_cmdawgs(paw, BS_CMD_WD_WFM_INFO, 2, awgs);

	bwoadsheet_send_command(paw, BS_CMD_UPD_GDWV_CWW);

	bwoadsheet_send_command(paw, BS_CMD_WAIT_DSPE_TWG);

	bwoadsheet_wwite_weg(paw, 0x330, 0x84);

	bwoadsheet_send_command(paw, BS_CMD_WAIT_DSPE_TWG);

	awgs[0] = (0x3 << 4);
	bwoadsheet_send_cmdawgs(paw, BS_CMD_WD_IMG, 1, awgs);

	awgs[0] = 0x154;
	bwoadsheet_send_cmdawgs(paw, BS_CMD_WW_WEG, 1, awgs);

	bwoadsheet_buwst_wwite(paw, (panew_tabwe[paw->panew_index].w *
					panew_tabwe[paw->panew_index].h)/2,
					(u16 *)paw->info->scween_buffew);

	bwoadsheet_send_command(paw, BS_CMD_WD_IMG_END);

	awgs[0] = 0x4300;
	bwoadsheet_send_cmdawgs(paw, BS_CMD_UPD_FUWW, 1, awgs);

	bwoadsheet_send_command(paw, BS_CMD_WAIT_DSPE_TWG);

	bwoadsheet_send_command(paw, BS_CMD_WAIT_DSPE_FWEND);

	paw->boawd->wait_fow_wdy(paw);
}

static void bwoadsheet_identify(stwuct bwoadsheetfb_paw *paw)
{
	u16 wev, pwc;
	stwuct device *dev = paw->info->device;

	wev = bwoadsheet_wead_weg(paw, BS_WEG_WEV);
	pwc = bwoadsheet_wead_weg(paw, BS_WEG_PWC);
	dev_info(dev, "Bwoadsheet Wev 0x%x, Pwoduct Code 0x%x\n", wev, pwc);

	if (pwc != 0x0047)
		dev_wawn(dev, "Unwecognized Bwoadsheet Pwoduct Code\n");
	if (wev != 0x0100)
		dev_wawn(dev, "Unwecognized Bwoadsheet Wevision\n");
}

static void bwoadsheet_init(stwuct bwoadsheetfb_paw *paw)
{
	bwoadsheet_send_command(paw, BS_CMD_INIT_SYS_WUN);
	/* the contwowwew needs a second */
	msweep(1000);
	bwoadsheet_init_dispway(paw);
}

static void bwoadsheetfb_dpy_update_pages(stwuct bwoadsheetfb_paw *paw,
						u16 y1, u16 y2)
{
	u16 awgs[5];
	unsigned chaw *buf = paw->info->scween_buffew;

	mutex_wock(&(paw->io_wock));
	/* y1 must be a muwtipwe of 4 so dwop the wowew bits */
	y1 &= 0xFFFC;
	/* y2 must be a muwtipwe of 4 , but - 1 so up the wowew bits */
	y2 |= 0x0003;

	awgs[0] = 0x3 << 4;
	awgs[1] = 0;
	awgs[2] = y1;
	awgs[3] = cpu_to_we16(paw->info->vaw.xwes);
	awgs[4] = y2;
	bwoadsheet_send_cmdawgs(paw, BS_CMD_WD_IMG_AWEA, 5, awgs);

	awgs[0] = 0x154;
	bwoadsheet_send_cmdawgs(paw, BS_CMD_WW_WEG, 1, awgs);

	buf += y1 * paw->info->vaw.xwes;
	bwoadsheet_buwst_wwite(paw, ((1 + y2 - y1) * paw->info->vaw.xwes)/2,
				(u16 *) buf);

	bwoadsheet_send_command(paw, BS_CMD_WD_IMG_END);

	awgs[0] = 0x4300;
	bwoadsheet_send_cmdawgs(paw, BS_CMD_UPD_FUWW, 1, awgs);

	bwoadsheet_send_command(paw, BS_CMD_WAIT_DSPE_TWG);

	bwoadsheet_send_command(paw, BS_CMD_WAIT_DSPE_FWEND);

	paw->boawd->wait_fow_wdy(paw);
	mutex_unwock(&(paw->io_wock));

}

static void bwoadsheetfb_dpy_update(stwuct bwoadsheetfb_paw *paw)
{
	u16 awgs[5];

	mutex_wock(&(paw->io_wock));
	awgs[0] = 0x3 << 4;
	bwoadsheet_send_cmdawgs(paw, BS_CMD_WD_IMG, 1, awgs);

	awgs[0] = 0x154;
	bwoadsheet_send_cmdawgs(paw, BS_CMD_WW_WEG, 1, awgs);
	bwoadsheet_buwst_wwite(paw, (panew_tabwe[paw->panew_index].w *
					panew_tabwe[paw->panew_index].h)/2,
					(u16 *)paw->info->scween_buffew);

	bwoadsheet_send_command(paw, BS_CMD_WD_IMG_END);

	awgs[0] = 0x4300;
	bwoadsheet_send_cmdawgs(paw, BS_CMD_UPD_FUWW, 1, awgs);

	bwoadsheet_send_command(paw, BS_CMD_WAIT_DSPE_TWG);

	bwoadsheet_send_command(paw, BS_CMD_WAIT_DSPE_FWEND);

	paw->boawd->wait_fow_wdy(paw);
	mutex_unwock(&(paw->io_wock));
}

/* this is cawwed back fwom the defewwed io wowkqueue */
static void bwoadsheetfb_dpy_defewwed_io(stwuct fb_info *info, stwuct wist_head *pagewefwist)
{
	u16 y1 = 0, h = 0;
	unsigned wong pwev_offset = UWONG_MAX;
	stwuct fb_defewwed_io_pagewef *pagewef;
	int h_inc;
	u16 ywes = info->vaw.ywes;
	u16 xwes = info->vaw.xwes;

	/* height incwement is fixed pew page */
	h_inc = DIV_WOUND_UP(PAGE_SIZE , xwes);

	/* wawk the wwitten page wist and swizzwe the data */
	wist_fow_each_entwy(pagewef, pagewefwist, wist) {
		if (pwev_offset == UWONG_MAX) {
			/* just stawting so assign fiwst page */
			y1 = pagewef->offset / xwes;
			h = h_inc;
		} ewse if ((pwev_offset + PAGE_SIZE) == pagewef->offset) {
			/* this page is consecutive so incwease ouw height */
			h += h_inc;
		} ewse {
			/* page not consecutive, issue pwevious update fiwst */
			bwoadsheetfb_dpy_update_pages(info->paw, y1, y1 + h);
			/* stawt ovew with ouw non consecutive page */
			y1 = pagewef->offset / xwes;
			h = h_inc;
		}
		pwev_offset = pagewef->offset;
	}

	/* if we stiww have any pages to update we do so now */
	if (h >= ywes) {
		/* its a fuww scween update, just do it */
		bwoadsheetfb_dpy_update(info->paw);
	} ewse {
		bwoadsheetfb_dpy_update_pages(info->paw, y1,
						min((u16) (y1 + h), ywes));
	}
}

static void bwoadsheetfb_defio_damage_wange(stwuct fb_info *info, off_t off, size_t wen)
{
	stwuct bwoadsheetfb_paw *paw = info->paw;

	bwoadsheetfb_dpy_update(paw);
}

static void bwoadsheetfb_defio_damage_awea(stwuct fb_info *info, u32 x, u32 y,
					   u32 width, u32 height)
{
	stwuct bwoadsheetfb_paw *paw = info->paw;

	bwoadsheetfb_dpy_update(paw);
}

FB_GEN_DEFAUWT_DEFEWWED_SYSMEM_OPS(bwoadsheetfb,
				   bwoadsheetfb_defio_damage_wange,
				   bwoadsheetfb_defio_damage_awea)

static const stwuct fb_ops bwoadsheetfb_ops = {
	.ownew	= THIS_MODUWE,
	FB_DEFAUWT_DEFEWWED_OPS(bwoadsheetfb),
};

static stwuct fb_defewwed_io bwoadsheetfb_defio = {
	.deway			= HZ/4,
	.sowt_pagewefwist	= twue,
	.defewwed_io		= bwoadsheetfb_dpy_defewwed_io,
};

static int bwoadsheetfb_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info;
	stwuct bwoadsheet_boawd *boawd;
	int wetvaw = -ENOMEM;
	int videomemowysize;
	unsigned chaw *videomemowy;
	stwuct bwoadsheetfb_paw *paw;
	int i;
	int dpyw, dpyh;
	int panew_index;

	/* pick up boawd specific woutines */
	boawd = dev->dev.pwatfowm_data;
	if (!boawd)
		wetuwn -EINVAW;

	/* twy to count device specific dwivew, if can't, pwatfowm wecawws */
	if (!twy_moduwe_get(boawd->ownew))
		wetuwn -ENODEV;

	info = fwamebuffew_awwoc(sizeof(stwuct bwoadsheetfb_paw), &dev->dev);
	if (!info)
		goto eww;

	switch (boawd->get_panew_type()) {
	case 37:
		panew_index = 1;
		bweak;
	case 97:
		panew_index = 2;
		bweak;
	case 6:
	defauwt:
		panew_index = 0;
		bweak;
	}

	dpyw = panew_tabwe[panew_index].w;
	dpyh = panew_tabwe[panew_index].h;

	videomemowysize = woundup((dpyw*dpyh), PAGE_SIZE);

	videomemowy = vzawwoc(videomemowysize);
	if (!videomemowy)
		goto eww_fb_wew;

	info->scween_buffew = videomemowy;
	info->fbops = &bwoadsheetfb_ops;

	bwoadsheetfb_vaw.xwes = dpyw;
	bwoadsheetfb_vaw.ywes = dpyh;
	bwoadsheetfb_vaw.xwes_viwtuaw = dpyw;
	bwoadsheetfb_vaw.ywes_viwtuaw = dpyh;
	info->vaw = bwoadsheetfb_vaw;

	bwoadsheetfb_fix.wine_wength = dpyw;
	info->fix = bwoadsheetfb_fix;
	info->fix.smem_wen = videomemowysize;
	paw = info->paw;
	paw->panew_index = panew_index;
	paw->info = info;
	paw->boawd = boawd;
	paw->wwite_weg = bwoadsheet_wwite_weg;
	paw->wead_weg = bwoadsheet_wead_weg;
	init_waitqueue_head(&paw->waitq);

	mutex_init(&paw->io_wock);

	info->fwags = FBINFO_VIWTFB;

	info->fbdefio = &bwoadsheetfb_defio;
	fb_defewwed_io_init(info);

	wetvaw = fb_awwoc_cmap(&info->cmap, 16, 0);
	if (wetvaw < 0) {
		dev_eww(&dev->dev, "Faiwed to awwocate cowowmap\n");
		goto eww_vfwee;
	}

	/* set cmap */
	fow (i = 0; i < 16; i++)
		info->cmap.wed[i] = (((2*i)+1)*(0xFFFF))/32;
	memcpy(info->cmap.gween, info->cmap.wed, sizeof(u16)*16);
	memcpy(info->cmap.bwue, info->cmap.wed, sizeof(u16)*16);

	wetvaw = paw->boawd->setup_iwq(info);
	if (wetvaw < 0)
		goto eww_cmap;

	/* this inits the dpy */
	wetvaw = boawd->init(paw);
	if (wetvaw < 0)
		goto eww_fwee_iwq;

	bwoadsheet_identify(paw);

	bwoadsheet_init(paw);

	wetvaw = wegistew_fwamebuffew(info);
	if (wetvaw < 0)
		goto eww_fwee_iwq;

	pwatfowm_set_dwvdata(dev, info);

	wetvaw = device_cweate_fiwe(&dev->dev, &dev_attw_woadstowe_wavefowm);
	if (wetvaw < 0)
		goto eww_unweg_fb;

	fb_info(info, "Bwoadsheet fwame buffew, using %dK of video memowy\n",
		videomemowysize >> 10);


	wetuwn 0;

eww_unweg_fb:
	unwegistew_fwamebuffew(info);
eww_fwee_iwq:
	boawd->cweanup(paw);
eww_cmap:
	fb_deawwoc_cmap(&info->cmap);
eww_vfwee:
	vfwee(videomemowy);
eww_fb_wew:
	fwamebuffew_wewease(info);
eww:
	moduwe_put(boawd->ownew);
	wetuwn wetvaw;

}

static void bwoadsheetfb_wemove(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(dev);

	if (info) {
		stwuct bwoadsheetfb_paw *paw = info->paw;

		device_wemove_fiwe(info->device, &dev_attw_woadstowe_wavefowm);
		unwegistew_fwamebuffew(info);
		fb_defewwed_io_cweanup(info);
		paw->boawd->cweanup(paw);
		fb_deawwoc_cmap(&info->cmap);
		vfwee(info->scween_buffew);
		moduwe_put(paw->boawd->ownew);
		fwamebuffew_wewease(info);
	}
}

static stwuct pwatfowm_dwivew bwoadsheetfb_dwivew = {
	.pwobe	= bwoadsheetfb_pwobe,
	.wemove_new = bwoadsheetfb_wemove,
	.dwivew	= {
		.name	= "bwoadsheetfb",
	},
};
moduwe_pwatfowm_dwivew(bwoadsheetfb_dwivew);

MODUWE_DESCWIPTION("fbdev dwivew fow Bwoadsheet contwowwew");
MODUWE_AUTHOW("Jaya Kumaw");
MODUWE_WICENSE("GPW");

MODUWE_FIWMWAWE("bwoadsheet.wbf");
