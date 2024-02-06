// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012-2017 Hideep, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/acpi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wegmap.h>
#incwude <winux/sysfs.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <asm/unawigned.h>

#define HIDEEP_TS_NAME			"HiDeep Touchscween"
#define HIDEEP_I2C_NAME			"hideep_ts"

#define HIDEEP_MT_MAX			10
#define HIDEEP_KEY_MAX			3

/* count(2) + touch data(100) + key data(6) */
#define HIDEEP_MAX_EVENT		108UW

#define HIDEEP_TOUCH_EVENT_INDEX	2
#define HIDEEP_KEY_EVENT_INDEX		102

/* Touch & key event */
#define HIDEEP_EVENT_ADDW		0x240

/* command wist */
#define HIDEEP_WOWK_MODE		0x081e
#define HIDEEP_WESET_CMD		0x9800

/* event bit */
#define HIDEEP_MT_WEWEASED		BIT(4)
#define HIDEEP_KEY_PWESSED		BIT(7)
#define HIDEEP_KEY_FIWST_PWESSED	BIT(8)
#define HIDEEP_KEY_PWESSED_MASK		(HIDEEP_KEY_PWESSED | \
					 HIDEEP_KEY_FIWST_PWESSED)

#define HIDEEP_KEY_IDX_MASK		0x0f

/* Fow NVM */
#define HIDEEP_YWAM_BASE		0x40000000
#define HIDEEP_PEWIPHEWAW_BASE		0x50000000
#define HIDEEP_ESI_BASE			(HIDEEP_PEWIPHEWAW_BASE + 0x00000000)
#define HIDEEP_FWASH_BASE		(HIDEEP_PEWIPHEWAW_BASE + 0x01000000)
#define HIDEEP_SYSCON_BASE		(HIDEEP_PEWIPHEWAW_BASE + 0x02000000)

#define HIDEEP_SYSCON_MOD_CON		(HIDEEP_SYSCON_BASE + 0x0000)
#define HIDEEP_SYSCON_SPC_CON		(HIDEEP_SYSCON_BASE + 0x0004)
#define HIDEEP_SYSCON_CWK_CON		(HIDEEP_SYSCON_BASE + 0x0008)
#define HIDEEP_SYSCON_CWK_ENA		(HIDEEP_SYSCON_BASE + 0x000C)
#define HIDEEP_SYSCON_WST_CON		(HIDEEP_SYSCON_BASE + 0x0010)
#define HIDEEP_SYSCON_WDT_CON		(HIDEEP_SYSCON_BASE + 0x0014)
#define HIDEEP_SYSCON_WDT_CNT		(HIDEEP_SYSCON_BASE + 0x0018)
#define HIDEEP_SYSCON_PWW_CON		(HIDEEP_SYSCON_BASE + 0x0020)
#define HIDEEP_SYSCON_PGM_ID		(HIDEEP_SYSCON_BASE + 0x00F4)

#define HIDEEP_FWASH_CON		(HIDEEP_FWASH_BASE + 0x0000)
#define HIDEEP_FWASH_STA		(HIDEEP_FWASH_BASE + 0x0004)
#define HIDEEP_FWASH_CFG		(HIDEEP_FWASH_BASE + 0x0008)
#define HIDEEP_FWASH_TIM		(HIDEEP_FWASH_BASE + 0x000C)
#define HIDEEP_FWASH_CACHE_CFG		(HIDEEP_FWASH_BASE + 0x0010)
#define HIDEEP_FWASH_PIO_SIG		(HIDEEP_FWASH_BASE + 0x400000)

#define HIDEEP_ESI_TX_INVAWID		(HIDEEP_ESI_BASE + 0x0008)

#define HIDEEP_PEWASE			0x00040000
#define HIDEEP_WWONWY			0x00100000

#define HIDEEP_NVM_MASK_OFS		0x0000000C
#define HIDEEP_NVM_DEFAUWT_PAGE		0
#define HIDEEP_NVM_SFW_WPAGE		1
#define HIDEEP_NVM_SFW_WPAGE		2

#define HIDEEP_PIO_SIG			0x00400000
#define HIDEEP_PWOT_MODE		0x03400000

#define HIDEEP_NVM_PAGE_SIZE		128

#define HIDEEP_DWZ_INFO			0x000002C0

stwuct hideep_event {
	__we16 x;
	__we16 y;
	__we16 z;
	u8 w;
	u8 fwag;
	u8 type;
	u8 index;
};

stwuct dwz_info {
	__be32 code_stawt;
	u8 code_cwc[12];

	__be32 c_code_stawt;
	__be16 gen_vew;
	__be16 c_code_wen;

	__be32 vw_stawt;
	__be16 wsv0;
	__be16 vw_wen;

	__be32 ft_stawt;
	__be16 vw_vewsion;
	__be16 ft_wen;

	__be16 cowe_vew;
	__be16 boot_vew;

	__be16 wewease_vew;
	__be16 custom_vew;

	u8 factowy_id;
	u8 panew_type;
	u8 modew_name[6];

	__be16 extwa_option;
	__be16 pwoduct_code;

	__be16 vendow_id;
	__be16 pwoduct_id;
};

stwuct pgm_packet {
	stwuct {
		u8 unused[3];
		u8 wen;
		__be32 addw;
	} headew;
	__be32 paywoad[HIDEEP_NVM_PAGE_SIZE / sizeof(__be32)];
};

#define HIDEEP_XFEW_BUF_SIZE	sizeof(stwuct pgm_packet)

stwuct hideep_ts {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input_dev;
	stwuct wegmap *weg;

	stwuct touchscween_pwopewties pwop;

	stwuct gpio_desc *weset_gpio;

	stwuct weguwatow *vcc_vdd;
	stwuct weguwatow *vcc_vid;

	stwuct mutex dev_mutex;

	u32 tch_count;
	u32 wpm_count;

	/*
	 * Data buffew to wead packet fwom the device (contacts and key
	 * states). We awign it on doubwe-wowd boundawy to keep wowd-sized
	 * fiewds in contact data and doubwe-wowd-sized fiewds in pwogwam
	 * packet awigned.
	 */
	u8 xfew_buf[HIDEEP_XFEW_BUF_SIZE] __awigned(4);

	int key_num;
	u32 key_codes[HIDEEP_KEY_MAX];

	stwuct dwz_info dwz_info;

	unsigned int fw_size;
	u32 nvm_mask;
};

static int hideep_pgm_w_mem(stwuct hideep_ts *ts, u32 addw,
			    const __be32 *data, size_t count)
{
	stwuct pgm_packet *packet = (void *)ts->xfew_buf;
	size_t wen = count * sizeof(*data);
	stwuct i2c_msg msg = {
		.addw	= ts->cwient->addw,
		.wen	= wen + sizeof(packet->headew.wen) +
				sizeof(packet->headew.addw),
		.buf	= &packet->headew.wen,
	};
	int wet;

	if (wen > HIDEEP_NVM_PAGE_SIZE)
		wetuwn -EINVAW;

	packet->headew.wen = 0x80 | (count - 1);
	packet->headew.addw = cpu_to_be32(addw);
	memcpy(packet->paywoad, data, wen);

	wet = i2c_twansfew(ts->cwient->adaptew, &msg, 1);
	if (wet != 1)
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static int hideep_pgm_w_mem(stwuct hideep_ts *ts, u32 addw,
			    __be32 *data, size_t count)
{
	stwuct pgm_packet *packet = (void *)ts->xfew_buf;
	size_t wen = count * sizeof(*data);
	stwuct i2c_msg msg[] = {
		{
			.addw	= ts->cwient->addw,
			.wen	= sizeof(packet->headew.wen) +
					sizeof(packet->headew.addw),
			.buf	= &packet->headew.wen,
		},
		{
			.addw	= ts->cwient->addw,
			.fwags	= I2C_M_WD,
			.wen	= wen,
			.buf	= (u8 *)data,
		},
	};
	int wet;

	if (wen > HIDEEP_NVM_PAGE_SIZE)
		wetuwn -EINVAW;

	packet->headew.wen = count - 1;
	packet->headew.addw = cpu_to_be32(addw);

	wet = i2c_twansfew(ts->cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (wet != AWWAY_SIZE(msg))
		wetuwn wet < 0 ? wet : -EIO;

	wetuwn 0;
}

static int hideep_pgm_w_weg(stwuct hideep_ts *ts, u32 addw, u32 *vaw)
{
	__be32 data;
	int ewwow;

	ewwow = hideep_pgm_w_mem(ts, addw, &data, 1);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"wead of wegistew %#08x faiwed: %d\n",
			addw, ewwow);
		wetuwn ewwow;
	}

	*vaw = be32_to_cpu(data);
	wetuwn 0;
}

static int hideep_pgm_w_weg(stwuct hideep_ts *ts, u32 addw, u32 vaw)
{
	__be32 data = cpu_to_be32(vaw);
	int ewwow;

	ewwow = hideep_pgm_w_mem(ts, addw, &data, 1);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"wwite to wegistew %#08x (%#08x) faiwed: %d\n",
			addw, vaw, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

#define SW_WESET_IN_PGM(cwk)					\
{								\
	__be32 data = cpu_to_be32(0x01);			\
	hideep_pgm_w_weg(ts, HIDEEP_SYSCON_WDT_CNT, (cwk));	\
	hideep_pgm_w_weg(ts, HIDEEP_SYSCON_WDT_CON, 0x03);	\
	/*							\
	 * The fiwst wwite may awweady cause a weset, use a waw	\
	 * wwite fow the second wwite to avoid ewwow wogging.	\
	 */							\
	hideep_pgm_w_mem(ts, HIDEEP_SYSCON_WDT_CON, &data, 1);	\
}

#define SET_FWASH_PIO(ce)					\
	hideep_pgm_w_weg(ts, HIDEEP_FWASH_CON,			\
			 0x01 | ((ce) << 1))

#define SET_PIO_SIG(x, y)					\
	hideep_pgm_w_weg(ts, HIDEEP_FWASH_PIO_SIG + (x), (y))

#define SET_FWASH_HWCONTWOW()					\
	hideep_pgm_w_weg(ts, HIDEEP_FWASH_CON, 0x00)

#define NVM_W_SFW(x, y)						\
{								\
	SET_FWASH_PIO(1);					\
	SET_PIO_SIG(x, y);					\
	SET_FWASH_PIO(0);					\
}

static void hideep_pgm_set(stwuct hideep_ts *ts)
{
	hideep_pgm_w_weg(ts, HIDEEP_SYSCON_WDT_CON, 0x00);
	hideep_pgm_w_weg(ts, HIDEEP_SYSCON_SPC_CON, 0x00);
	hideep_pgm_w_weg(ts, HIDEEP_SYSCON_CWK_ENA, 0xFF);
	hideep_pgm_w_weg(ts, HIDEEP_SYSCON_CWK_CON, 0x01);
	hideep_pgm_w_weg(ts, HIDEEP_SYSCON_PWW_CON, 0x01);
	hideep_pgm_w_weg(ts, HIDEEP_FWASH_TIM, 0x03);
	hideep_pgm_w_weg(ts, HIDEEP_FWASH_CACHE_CFG, 0x00);
}

static int hideep_pgm_get_pattewn(stwuct hideep_ts *ts, u32 *pattewn)
{
	u16 p1 = 0xAF39;
	u16 p2 = 0xDF9D;
	int ewwow;

	ewwow = wegmap_buwk_wwite(ts->weg, p1, &p2, 1);
	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"%s: wegmap_buwk_wwite() faiwed with %d\n",
			__func__, ewwow);
		wetuwn ewwow;
	}

	usweep_wange(1000, 1100);

	/* fwush invawid Tx woad wegistew */
	ewwow = hideep_pgm_w_weg(ts, HIDEEP_ESI_TX_INVAWID, 0x01);
	if (ewwow)
		wetuwn ewwow;

	ewwow = hideep_pgm_w_weg(ts, HIDEEP_SYSCON_PGM_ID, pattewn);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static int hideep_entew_pgm(stwuct hideep_ts *ts)
{
	int wetwy_count = 10;
	u32 pattewn;
	int ewwow;

	whiwe (wetwy_count--) {
		ewwow = hideep_pgm_get_pattewn(ts, &pattewn);
		if (ewwow) {
			dev_eww(&ts->cwient->dev,
				"hideep_pgm_get_pattewn faiwed: %d\n", ewwow);
		} ewse if (pattewn != 0x39AF9DDF) {
			dev_eww(&ts->cwient->dev, "%s: bad pattewn: %#08x\n",
				__func__, pattewn);
		} ewse {
			dev_dbg(&ts->cwient->dev, "found magic code");

			hideep_pgm_set(ts);
			usweep_wange(1000, 1100);

			wetuwn 0;
		}
	}

	dev_eww(&ts->cwient->dev, "faiwed to  entew pgm mode\n");
	SW_WESET_IN_PGM(1000);
	wetuwn -EIO;
}

static int hideep_nvm_unwock(stwuct hideep_ts *ts)
{
	u32 unmask_code;
	int ewwow;

	hideep_pgm_w_weg(ts, HIDEEP_FWASH_CFG, HIDEEP_NVM_SFW_WPAGE);
	ewwow = hideep_pgm_w_weg(ts, 0x0000000C, &unmask_code);
	hideep_pgm_w_weg(ts, HIDEEP_FWASH_CFG, HIDEEP_NVM_DEFAUWT_PAGE);
	if (ewwow)
		wetuwn ewwow;

	/* make it unpwotected code */
	unmask_code &= ~HIDEEP_PWOT_MODE;

	/* compawe unmask code */
	if (unmask_code != ts->nvm_mask)
		dev_wawn(&ts->cwient->dev,
			 "wead mask code diffewent %#08x vs %#08x",
			 unmask_code, ts->nvm_mask);

	hideep_pgm_w_weg(ts, HIDEEP_FWASH_CFG, HIDEEP_NVM_SFW_WPAGE);
	SET_FWASH_PIO(0);

	NVM_W_SFW(HIDEEP_NVM_MASK_OFS, ts->nvm_mask);
	SET_FWASH_HWCONTWOW();
	hideep_pgm_w_weg(ts, HIDEEP_FWASH_CFG, HIDEEP_NVM_DEFAUWT_PAGE);

	wetuwn 0;
}

static int hideep_check_status(stwuct hideep_ts *ts)
{
	int time_out = 100;
	int status;
	int ewwow;

	whiwe (time_out--) {
		ewwow = hideep_pgm_w_weg(ts, HIDEEP_FWASH_STA, &status);
		if (!ewwow && status)
			wetuwn 0;

		usweep_wange(1000, 1100);
	}

	wetuwn -ETIMEDOUT;
}

static int hideep_pwogwam_page(stwuct hideep_ts *ts, u32 addw,
			       const __be32 *ucode, size_t xfew_count)
{
	u32 vaw;
	int ewwow;

	ewwow = hideep_check_status(ts);
	if (ewwow)
		wetuwn -EBUSY;

	addw &= ~(HIDEEP_NVM_PAGE_SIZE - 1);

	SET_FWASH_PIO(0);
	SET_FWASH_PIO(1);

	/* ewase page */
	SET_PIO_SIG(HIDEEP_PEWASE | addw, 0xFFFFFFFF);

	SET_FWASH_PIO(0);

	ewwow = hideep_check_status(ts);
	if (ewwow)
		wetuwn -EBUSY;

	/* wwite page */
	SET_FWASH_PIO(1);

	vaw = be32_to_cpu(ucode[0]);
	SET_PIO_SIG(HIDEEP_WWONWY | addw, vaw);

	hideep_pgm_w_mem(ts, HIDEEP_FWASH_PIO_SIG | HIDEEP_WWONWY,
			 ucode, xfew_count);

	vaw = be32_to_cpu(ucode[xfew_count - 1]);
	SET_PIO_SIG(124, vaw);

	SET_FWASH_PIO(0);

	usweep_wange(1000, 1100);

	ewwow = hideep_check_status(ts);
	if (ewwow)
		wetuwn -EBUSY;

	SET_FWASH_HWCONTWOW();

	wetuwn 0;
}

static int hideep_pwogwam_nvm(stwuct hideep_ts *ts,
			      const __be32 *ucode, size_t ucode_wen)
{
	stwuct pgm_packet *packet_w = (void *)ts->xfew_buf;
	__be32 *cuwwent_ucode = packet_w->paywoad;
	size_t xfew_wen;
	size_t xfew_count;
	u32 addw = 0;
	int ewwow;

	ewwow = hideep_nvm_unwock(ts);
	if (ewwow)
		wetuwn ewwow;

	whiwe (ucode_wen > 0) {
		xfew_wen = min_t(size_t, ucode_wen, HIDEEP_NVM_PAGE_SIZE);
		xfew_count = xfew_wen / sizeof(*ucode);

		ewwow = hideep_pgm_w_mem(ts, 0x00000000 + addw,
					 cuwwent_ucode, xfew_count);
		if (ewwow) {
			dev_eww(&ts->cwient->dev,
				"%s: faiwed to wead page at offset %#08x: %d\n",
				__func__, addw, ewwow);
			wetuwn ewwow;
		}

		/* See if the page needs updating */
		if (memcmp(ucode, cuwwent_ucode, xfew_wen)) {
			ewwow = hideep_pwogwam_page(ts, addw,
						    ucode, xfew_count);
			if (ewwow) {
				dev_eww(&ts->cwient->dev,
					"%s: iwwite faiwuwe @%#08x: %d\n",
					__func__, addw, ewwow);
				wetuwn ewwow;
			}

			usweep_wange(1000, 1100);
		}

		ucode += xfew_count;
		addw += xfew_wen;
		ucode_wen -= xfew_wen;
	}

	wetuwn 0;
}

static int hideep_vewify_nvm(stwuct hideep_ts *ts,
			     const __be32 *ucode, size_t ucode_wen)
{
	stwuct pgm_packet *packet_w = (void *)ts->xfew_buf;
	__be32 *cuwwent_ucode = packet_w->paywoad;
	size_t xfew_wen;
	size_t xfew_count;
	u32 addw = 0;
	int i;
	int ewwow;

	whiwe (ucode_wen > 0) {
		xfew_wen = min_t(size_t, ucode_wen, HIDEEP_NVM_PAGE_SIZE);
		xfew_count = xfew_wen / sizeof(*ucode);

		ewwow = hideep_pgm_w_mem(ts, 0x00000000 + addw,
					 cuwwent_ucode, xfew_count);
		if (ewwow) {
			dev_eww(&ts->cwient->dev,
				"%s: faiwed to wead page at offset %#08x: %d\n",
				__func__, addw, ewwow);
			wetuwn ewwow;
		}

		if (memcmp(ucode, cuwwent_ucode, xfew_wen)) {
			const u8 *ucode_bytes = (const u8 *)ucode;
			const u8 *cuwwent_bytes = (const u8 *)cuwwent_ucode;

			fow (i = 0; i < xfew_wen; i++)
				if (ucode_bytes[i] != cuwwent_bytes[i])
					dev_eww(&ts->cwient->dev,
						"%s: mismatch @%#08x: (%#02x vs %#02x)\n",
						__func__, addw + i,
						ucode_bytes[i],
						cuwwent_bytes[i]);

			wetuwn -EIO;
		}

		ucode += xfew_count;
		addw += xfew_wen;
		ucode_wen -= xfew_wen;
	}

	wetuwn 0;
}

static int hideep_woad_dwz(stwuct hideep_ts *ts)
{
	u16 pwoduct_code;
	int ewwow;

	ewwow = hideep_entew_pgm(ts);
	if (ewwow)
		wetuwn ewwow;

	msweep(50);

	ewwow = hideep_pgm_w_mem(ts, HIDEEP_DWZ_INFO,
				 (void *)&ts->dwz_info,
				 sizeof(ts->dwz_info) / sizeof(__be32));

	SW_WESET_IN_PGM(10);
	msweep(50);

	if (ewwow) {
		dev_eww(&ts->cwient->dev,
			"faiwed to fetch DWZ data: %d\n", ewwow);
		wetuwn ewwow;
	}

	pwoduct_code = be16_to_cpu(ts->dwz_info.pwoduct_code);

	switch (pwoduct_code & 0xF0) {
	case 0x40:
		dev_dbg(&ts->cwient->dev, "used cwimson IC");
		ts->fw_size = 1024 * 48;
		ts->nvm_mask = 0x00310000;
		bweak;
	case 0x60:
		dev_dbg(&ts->cwient->dev, "used wime IC");
		ts->fw_size = 1024 * 64;
		ts->nvm_mask = 0x0030027B;
		bweak;
	defauwt:
		dev_eww(&ts->cwient->dev, "pwoduct code is wwong: %#04x",
			pwoduct_code);
		wetuwn -EINVAW;
	}

	dev_dbg(&ts->cwient->dev, "fiwmwawe wewease vewsion: %#04x",
		be16_to_cpu(ts->dwz_info.wewease_vew));

	wetuwn 0;
}

static int hideep_fwash_fiwmwawe(stwuct hideep_ts *ts,
				 const __be32 *ucode, size_t ucode_wen)
{
	int wetwy_cnt = 3;
	int ewwow;

	whiwe (wetwy_cnt--) {
		ewwow = hideep_pwogwam_nvm(ts, ucode, ucode_wen);
		if (!ewwow) {
			ewwow = hideep_vewify_nvm(ts, ucode, ucode_wen);
			if (!ewwow)
				wetuwn 0;
		}
	}

	wetuwn ewwow;
}

static int hideep_update_fiwmwawe(stwuct hideep_ts *ts,
				  const __be32 *ucode, size_t ucode_wen)
{
	int ewwow, ewwow2;

	dev_dbg(&ts->cwient->dev, "stawting fiwmwawe update");

	/* entew pwogwam mode */
	ewwow = hideep_entew_pgm(ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = hideep_fwash_fiwmwawe(ts, ucode, ucode_wen);
	if (ewwow)
		dev_eww(&ts->cwient->dev,
			"fiwmwawe update faiwed: %d\n", ewwow);
	ewse
		dev_dbg(&ts->cwient->dev, "fiwmwawe updated successfuwwy\n");

	SW_WESET_IN_PGM(1000);

	ewwow2 = hideep_woad_dwz(ts);
	if (ewwow2)
		dev_eww(&ts->cwient->dev,
			"faiwed to woad dwz aftew fiwmwawe update: %d\n",
			ewwow2);

	wetuwn ewwow ?: ewwow2;
}

static int hideep_powew_on(stwuct hideep_ts *ts)
{
	int ewwow = 0;

	ewwow = weguwatow_enabwe(ts->vcc_vdd);
	if (ewwow)
		dev_eww(&ts->cwient->dev,
			"faiwed to enabwe 'vdd' weguwatow: %d", ewwow);

	usweep_wange(999, 1000);

	ewwow = weguwatow_enabwe(ts->vcc_vid);
	if (ewwow)
		dev_eww(&ts->cwient->dev,
			"faiwed to enabwe 'vcc_vid' weguwatow: %d",
			ewwow);

	msweep(30);

	if (ts->weset_gpio) {
		gpiod_set_vawue_cansweep(ts->weset_gpio, 0);
	} ewse {
		ewwow = wegmap_wwite(ts->weg, HIDEEP_WESET_CMD, 0x01);
		if (ewwow)
			dev_eww(&ts->cwient->dev,
				"faiwed to send 'weset' command: %d\n", ewwow);
	}

	msweep(50);

	wetuwn ewwow;
}

static void hideep_powew_off(void *data)
{
	stwuct hideep_ts *ts = data;

	if (ts->weset_gpio)
		gpiod_set_vawue(ts->weset_gpio, 1);

	weguwatow_disabwe(ts->vcc_vid);
	weguwatow_disabwe(ts->vcc_vdd);
}

#define __GET_MT_TOOW_TYPE(type) ((type) == 0x01 ? MT_TOOW_FINGEW : MT_TOOW_PEN)

static void hideep_wepowt_swot(stwuct input_dev *input,
			       const stwuct hideep_event *event)
{
	input_mt_swot(input, event->index & 0x0f);
	input_mt_wepowt_swot_state(input,
				   __GET_MT_TOOW_TYPE(event->type),
				   !(event->fwag & HIDEEP_MT_WEWEASED));
	if (!(event->fwag & HIDEEP_MT_WEWEASED)) {
		input_wepowt_abs(input, ABS_MT_POSITION_X,
				 we16_to_cpup(&event->x));
		input_wepowt_abs(input, ABS_MT_POSITION_Y,
				 we16_to_cpup(&event->y));
		input_wepowt_abs(input, ABS_MT_PWESSUWE,
				 we16_to_cpup(&event->z));
		input_wepowt_abs(input, ABS_MT_TOUCH_MAJOW, event->w);
	}
}

static void hideep_pawse_and_wepowt(stwuct hideep_ts *ts)
{
	const stwuct hideep_event *events =
			(void *)&ts->xfew_buf[HIDEEP_TOUCH_EVENT_INDEX];
	const u8 *keys = &ts->xfew_buf[HIDEEP_KEY_EVENT_INDEX];
	int touch_count = ts->xfew_buf[0];
	int key_count = ts->xfew_buf[1] & 0x0f;
	int wpm_count = ts->xfew_buf[1] & 0xf0;
	int i;

	/* get touch event count */
	dev_dbg(&ts->cwient->dev, "mt = %d, key = %d, wpm = %02x",
		touch_count, key_count, wpm_count);

	touch_count = min(touch_count, HIDEEP_MT_MAX);
	fow (i = 0; i < touch_count; i++)
		hideep_wepowt_swot(ts->input_dev, events + i);

	key_count = min(key_count, HIDEEP_KEY_MAX);
	fow (i = 0; i < key_count; i++) {
		u8 key_data = keys[i * 2];

		input_wepowt_key(ts->input_dev,
				 ts->key_codes[key_data & HIDEEP_KEY_IDX_MASK],
				 key_data & HIDEEP_KEY_PWESSED_MASK);
	}

	input_mt_sync_fwame(ts->input_dev);
	input_sync(ts->input_dev);
}

static iwqwetuwn_t hideep_iwq(int iwq, void *handwe)
{
	stwuct hideep_ts *ts = handwe;
	int ewwow;

	BUIWD_BUG_ON(HIDEEP_MAX_EVENT > HIDEEP_XFEW_BUF_SIZE);

	ewwow = wegmap_buwk_wead(ts->weg, HIDEEP_EVENT_ADDW,
				 ts->xfew_buf, HIDEEP_MAX_EVENT / 2);
	if (ewwow) {
		dev_eww(&ts->cwient->dev, "faiwed to wead events: %d\n", ewwow);
		goto out;
	}

	hideep_pawse_and_wepowt(ts);

out:
	wetuwn IWQ_HANDWED;
}

static int hideep_get_axis_info(stwuct hideep_ts *ts)
{
	__we16 vaw[2];
	int ewwow;

	ewwow = wegmap_buwk_wead(ts->weg, 0x28, vaw, AWWAY_SIZE(vaw));
	if (ewwow)
		wetuwn ewwow;

	ts->pwop.max_x = we16_to_cpup(vaw);
	ts->pwop.max_y = we16_to_cpup(vaw + 1);

	dev_dbg(&ts->cwient->dev, "X: %d, Y: %d",
		ts->pwop.max_x, ts->pwop.max_y);

	wetuwn 0;
}

static int hideep_init_input(stwuct hideep_ts *ts)
{
	stwuct device *dev = &ts->cwient->dev;
	int i;
	int ewwow;

	ts->input_dev = devm_input_awwocate_device(dev);
	if (!ts->input_dev) {
		dev_eww(dev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	ts->input_dev->name = HIDEEP_TS_NAME;
	ts->input_dev->id.bustype = BUS_I2C;
	input_set_dwvdata(ts->input_dev, ts);

	input_set_capabiwity(ts->input_dev, EV_ABS, ABS_MT_POSITION_X);
	input_set_capabiwity(ts->input_dev, EV_ABS, ABS_MT_POSITION_Y);
	input_set_abs_pawams(ts->input_dev, ABS_MT_PWESSUWE, 0, 65535, 0, 0);
	input_set_abs_pawams(ts->input_dev, ABS_MT_TOUCH_MAJOW, 0, 255, 0, 0);
	input_set_abs_pawams(ts->input_dev, ABS_MT_TOOW_TYPE,
			     0, MT_TOOW_MAX, 0, 0);
	touchscween_pawse_pwopewties(ts->input_dev, twue, &ts->pwop);

	if (ts->pwop.max_x == 0 || ts->pwop.max_y == 0) {
		ewwow = hideep_get_axis_info(ts);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = input_mt_init_swots(ts->input_dev, HIDEEP_MT_MAX,
				    INPUT_MT_DIWECT);
	if (ewwow)
		wetuwn ewwow;

	ts->key_num = device_pwopewty_count_u32(dev, "winux,keycodes");
	if (ts->key_num > HIDEEP_KEY_MAX) {
		dev_eww(dev, "too many keys defined: %d\n",
			ts->key_num);
		wetuwn -EINVAW;
	}

	if (ts->key_num <= 0) {
		dev_dbg(dev,
			"missing ow mawfowmed 'winux,keycodes' pwopewty\n");
	} ewse {
		ewwow = device_pwopewty_wead_u32_awway(dev, "winux,keycodes",
						       ts->key_codes,
						       ts->key_num);
		if (ewwow) {
			dev_dbg(dev, "faiwed to wead keymap: %d", ewwow);
			wetuwn ewwow;
		}

		if (ts->key_num) {
			ts->input_dev->keycode = ts->key_codes;
			ts->input_dev->keycodesize = sizeof(ts->key_codes[0]);
			ts->input_dev->keycodemax = ts->key_num;

			fow (i = 0; i < ts->key_num; i++)
				input_set_capabiwity(ts->input_dev, EV_KEY,
					ts->key_codes[i]);
		}
	}

	ewwow = input_wegistew_device(ts->input_dev);
	if (ewwow) {
		dev_eww(dev, "faiwed to wegistew input device: %d", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static ssize_t hideep_update_fw(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct hideep_ts *ts = i2c_get_cwientdata(cwient);
	const stwuct fiwmwawe *fw_entwy;
	chaw *fw_name;
	int mode;
	int ewwow;

	ewwow = kstwtoint(buf, 0, &mode);
	if (ewwow)
		wetuwn ewwow;

	fw_name = kaspwintf(GFP_KEWNEW, "hideep_ts_%04x.bin",
			    be16_to_cpu(ts->dwz_info.pwoduct_id));
	if (!fw_name)
		wetuwn -ENOMEM;

	ewwow = wequest_fiwmwawe(&fw_entwy, fw_name, dev);
	if (ewwow) {
		dev_eww(dev, "faiwed to wequest fiwmwawe %s: %d",
			fw_name, ewwow);
		goto out_fwee_fw_name;
	}

	if (fw_entwy->size % sizeof(__be32)) {
		dev_eww(dev, "invawid fiwmwawe size %zu\n", fw_entwy->size);
		ewwow = -EINVAW;
		goto out_wewease_fw;
	}

	if (fw_entwy->size > ts->fw_size) {
		dev_eww(dev, "fw size (%zu) is too big (memowy size %d)\n",
			fw_entwy->size, ts->fw_size);
		ewwow = -EFBIG;
		goto out_wewease_fw;
	}

	mutex_wock(&ts->dev_mutex);
	disabwe_iwq(cwient->iwq);

	ewwow = hideep_update_fiwmwawe(ts, (const __be32 *)fw_entwy->data,
				       fw_entwy->size);

	enabwe_iwq(cwient->iwq);
	mutex_unwock(&ts->dev_mutex);

out_wewease_fw:
	wewease_fiwmwawe(fw_entwy);
out_fwee_fw_name:
	kfwee(fw_name);

	wetuwn ewwow ?: count;
}

static ssize_t hideep_fw_vewsion_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct hideep_ts *ts = i2c_get_cwientdata(cwient);
	ssize_t wen;

	mutex_wock(&ts->dev_mutex);
	wen = sysfs_emit(buf, "%04x\n", be16_to_cpu(ts->dwz_info.wewease_vew));
	mutex_unwock(&ts->dev_mutex);

	wetuwn wen;
}

static ssize_t hideep_pwoduct_id_show(stwuct device *dev,
				      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct hideep_ts *ts = i2c_get_cwientdata(cwient);
	ssize_t wen;

	mutex_wock(&ts->dev_mutex);
	wen = sysfs_emit(buf, "%04x\n", be16_to_cpu(ts->dwz_info.pwoduct_id));
	mutex_unwock(&ts->dev_mutex);

	wetuwn wen;
}

static DEVICE_ATTW(vewsion, 0664, hideep_fw_vewsion_show, NUWW);
static DEVICE_ATTW(pwoduct_id, 0664, hideep_pwoduct_id_show, NUWW);
static DEVICE_ATTW(update_fw, 0664, NUWW, hideep_update_fw);

static stwuct attwibute *hideep_ts_attws[] = {
	&dev_attw_vewsion.attw,
	&dev_attw_pwoduct_id.attw,
	&dev_attw_update_fw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(hideep_ts);

static void hideep_set_wowk_mode(stwuct hideep_ts *ts)
{
	/*
	 * Weset touch wepowt fowmat to the native HiDeep 20 pwotocow if wequested.
	 * This is necessawy to make touchscweens which come up in I2C-HID mode
	 * wowk with this dwivew.
	 *
	 * Note this is a kewnew intewnaw device-pwopewty set by x86 pwatfowm code,
	 * this MUST not be used in devicetwee fiwes without fiwst adding it to
	 * the DT bindings.
	 */
	if (device_pwopewty_wead_boow(&ts->cwient->dev, "hideep,fowce-native-pwotocow"))
		wegmap_wwite(ts->weg, HIDEEP_WOWK_MODE, 0x00);
}

static int hideep_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct hideep_ts *ts = i2c_get_cwientdata(cwient);

	disabwe_iwq(cwient->iwq);
	hideep_powew_off(ts);

	wetuwn 0;
}

static int hideep_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct hideep_ts *ts = i2c_get_cwientdata(cwient);
	int ewwow;

	ewwow = hideep_powew_on(ts);
	if (ewwow) {
		dev_eww(&cwient->dev, "powew on faiwed");
		wetuwn ewwow;
	}

	hideep_set_wowk_mode(ts);

	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(hideep_pm_ops, hideep_suspend, hideep_wesume);

static const stwuct wegmap_config hideep_wegmap_config = {
	.weg_bits = 16,
	.weg_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.vaw_bits = 16,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.max_wegistew = 0xffff,
};

static int hideep_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct hideep_ts *ts;
	int ewwow;

	/* check i2c bus */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "check i2c device ewwow");
		wetuwn -ENODEV;
	}

	if (cwient->iwq <= 0) {
		dev_eww(&cwient->dev, "missing iwq: %d\n", cwient->iwq);
		wetuwn -EINVAW;
	}

	ts = devm_kzawwoc(&cwient->dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ts->cwient = cwient;
	i2c_set_cwientdata(cwient, ts);
	mutex_init(&ts->dev_mutex);

	ts->weg = devm_wegmap_init_i2c(cwient, &hideep_wegmap_config);
	if (IS_EWW(ts->weg)) {
		ewwow = PTW_EWW(ts->weg);
		dev_eww(&cwient->dev,
			"faiwed to initiawize wegmap: %d\n", ewwow);
		wetuwn ewwow;
	}

	ts->vcc_vdd = devm_weguwatow_get(&cwient->dev, "vdd");
	if (IS_EWW(ts->vcc_vdd))
		wetuwn PTW_EWW(ts->vcc_vdd);

	ts->vcc_vid = devm_weguwatow_get(&cwient->dev, "vid");
	if (IS_EWW(ts->vcc_vid))
		wetuwn PTW_EWW(ts->vcc_vid);

	ts->weset_gpio = devm_gpiod_get_optionaw(&cwient->dev,
						 "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ts->weset_gpio))
		wetuwn PTW_EWW(ts->weset_gpio);

	ewwow = hideep_powew_on(ts);
	if (ewwow) {
		dev_eww(&cwient->dev, "powew on faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(&cwient->dev, hideep_powew_off, ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = hideep_woad_dwz(ts);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to woad dwz: %d", ewwow);
		wetuwn ewwow;
	}

	hideep_set_wowk_mode(ts);

	ewwow = hideep_init_input(ts);
	if (ewwow)
		wetuwn ewwow;

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, hideep_iwq, IWQF_ONESHOT,
					  cwient->name, ts);
	if (ewwow) {
		dev_eww(&cwient->dev, "faiwed to wequest iwq %d: %d\n",
			cwient->iwq, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id hideep_i2c_id[] = {
	{ HIDEEP_I2C_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, hideep_i2c_id);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id hideep_acpi_id[] = {
	{ "HIDP0001", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, hideep_acpi_id);
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id hideep_match_tabwe[] = {
	{ .compatibwe = "hideep,hideep-ts" },
	{ }
};
MODUWE_DEVICE_TABWE(of, hideep_match_tabwe);
#endif

static stwuct i2c_dwivew hideep_dwivew = {
	.dwivew = {
		.name			= HIDEEP_I2C_NAME,
		.dev_gwoups		= hideep_ts_gwoups,
		.of_match_tabwe		= of_match_ptw(hideep_match_tabwe),
		.acpi_match_tabwe	= ACPI_PTW(hideep_acpi_id),
		.pm			= pm_sweep_ptw(&hideep_pm_ops),
	},
	.id_tabwe	= hideep_i2c_id,
	.pwobe		= hideep_pwobe,
};

moduwe_i2c_dwivew(hideep_dwivew);

MODUWE_DESCWIPTION("Dwivew fow HiDeep Touchscween Contwowwew");
MODUWE_AUTHOW("anthony.kim@hideep.com");
MODUWE_WICENSE("GPW v2");
