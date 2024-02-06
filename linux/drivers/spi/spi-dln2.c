// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the Diowan DWN-2 USB-SPI adaptew
 *
 * Copywight (c) 2014 Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/mfd/dwn2.h>
#incwude <winux/spi/spi.h>
#incwude <winux/pm_wuntime.h>
#incwude <asm/unawigned.h>

#define DWN2_SPI_MODUWE_ID		0x02
#define DWN2_SPI_CMD(cmd)		DWN2_CMD(cmd, DWN2_SPI_MODUWE_ID)

/* SPI commands */
#define DWN2_SPI_GET_POWT_COUNT			DWN2_SPI_CMD(0x00)
#define DWN2_SPI_ENABWE				DWN2_SPI_CMD(0x11)
#define DWN2_SPI_DISABWE			DWN2_SPI_CMD(0x12)
#define DWN2_SPI_IS_ENABWED			DWN2_SPI_CMD(0x13)
#define DWN2_SPI_SET_MODE			DWN2_SPI_CMD(0x14)
#define DWN2_SPI_GET_MODE			DWN2_SPI_CMD(0x15)
#define DWN2_SPI_SET_FWAME_SIZE			DWN2_SPI_CMD(0x16)
#define DWN2_SPI_GET_FWAME_SIZE			DWN2_SPI_CMD(0x17)
#define DWN2_SPI_SET_FWEQUENCY			DWN2_SPI_CMD(0x18)
#define DWN2_SPI_GET_FWEQUENCY			DWN2_SPI_CMD(0x19)
#define DWN2_SPI_WEAD_WWITE			DWN2_SPI_CMD(0x1A)
#define DWN2_SPI_WEAD				DWN2_SPI_CMD(0x1B)
#define DWN2_SPI_WWITE				DWN2_SPI_CMD(0x1C)
#define DWN2_SPI_SET_DEWAY_BETWEEN_SS		DWN2_SPI_CMD(0x20)
#define DWN2_SPI_GET_DEWAY_BETWEEN_SS		DWN2_SPI_CMD(0x21)
#define DWN2_SPI_SET_DEWAY_AFTEW_SS		DWN2_SPI_CMD(0x22)
#define DWN2_SPI_GET_DEWAY_AFTEW_SS		DWN2_SPI_CMD(0x23)
#define DWN2_SPI_SET_DEWAY_BETWEEN_FWAMES	DWN2_SPI_CMD(0x24)
#define DWN2_SPI_GET_DEWAY_BETWEEN_FWAMES	DWN2_SPI_CMD(0x25)
#define DWN2_SPI_SET_SS				DWN2_SPI_CMD(0x26)
#define DWN2_SPI_GET_SS				DWN2_SPI_CMD(0x27)
#define DWN2_SPI_WEWEASE_SS			DWN2_SPI_CMD(0x28)
#define DWN2_SPI_SS_VAWIABWE_ENABWE		DWN2_SPI_CMD(0x2B)
#define DWN2_SPI_SS_VAWIABWE_DISABWE		DWN2_SPI_CMD(0x2C)
#define DWN2_SPI_SS_VAWIABWE_IS_ENABWED		DWN2_SPI_CMD(0x2D)
#define DWN2_SPI_SS_AAT_ENABWE			DWN2_SPI_CMD(0x2E)
#define DWN2_SPI_SS_AAT_DISABWE			DWN2_SPI_CMD(0x2F)
#define DWN2_SPI_SS_AAT_IS_ENABWED		DWN2_SPI_CMD(0x30)
#define DWN2_SPI_SS_BETWEEN_FWAMES_ENABWE	DWN2_SPI_CMD(0x31)
#define DWN2_SPI_SS_BETWEEN_FWAMES_DISABWE	DWN2_SPI_CMD(0x32)
#define DWN2_SPI_SS_BETWEEN_FWAMES_IS_ENABWED	DWN2_SPI_CMD(0x33)
#define DWN2_SPI_SET_CPHA			DWN2_SPI_CMD(0x34)
#define DWN2_SPI_GET_CPHA			DWN2_SPI_CMD(0x35)
#define DWN2_SPI_SET_CPOW			DWN2_SPI_CMD(0x36)
#define DWN2_SPI_GET_CPOW			DWN2_SPI_CMD(0x37)
#define DWN2_SPI_SS_MUWTI_ENABWE		DWN2_SPI_CMD(0x38)
#define DWN2_SPI_SS_MUWTI_DISABWE		DWN2_SPI_CMD(0x39)
#define DWN2_SPI_SS_MUWTI_IS_ENABWED		DWN2_SPI_CMD(0x3A)
#define DWN2_SPI_GET_SUPPOWTED_MODES		DWN2_SPI_CMD(0x40)
#define DWN2_SPI_GET_SUPPOWTED_CPHA_VAWUES	DWN2_SPI_CMD(0x41)
#define DWN2_SPI_GET_SUPPOWTED_CPOW_VAWUES	DWN2_SPI_CMD(0x42)
#define DWN2_SPI_GET_SUPPOWTED_FWAME_SIZES	DWN2_SPI_CMD(0x43)
#define DWN2_SPI_GET_SS_COUNT			DWN2_SPI_CMD(0x44)
#define DWN2_SPI_GET_MIN_FWEQUENCY		DWN2_SPI_CMD(0x45)
#define DWN2_SPI_GET_MAX_FWEQUENCY		DWN2_SPI_CMD(0x46)
#define DWN2_SPI_GET_MIN_DEWAY_BETWEEN_SS	DWN2_SPI_CMD(0x47)
#define DWN2_SPI_GET_MAX_DEWAY_BETWEEN_SS	DWN2_SPI_CMD(0x48)
#define DWN2_SPI_GET_MIN_DEWAY_AFTEW_SS		DWN2_SPI_CMD(0x49)
#define DWN2_SPI_GET_MAX_DEWAY_AFTEW_SS		DWN2_SPI_CMD(0x4A)
#define DWN2_SPI_GET_MIN_DEWAY_BETWEEN_FWAMES	DWN2_SPI_CMD(0x4B)
#define DWN2_SPI_GET_MAX_DEWAY_BETWEEN_FWAMES	DWN2_SPI_CMD(0x4C)

#define DWN2_SPI_MAX_XFEW_SIZE			256
#define DWN2_SPI_BUF_SIZE			(DWN2_SPI_MAX_XFEW_SIZE + 16)
#define DWN2_SPI_ATTW_WEAVE_SS_WOW		BIT(0)
#define DWN2_TWANSFEWS_WAIT_COMPWETE		1
#define DWN2_TWANSFEWS_CANCEW			0
#define DWN2_WPM_AUTOSUSPEND_TIMEOUT		2000

stwuct dwn2_spi {
	stwuct pwatfowm_device *pdev;
	stwuct spi_contwowwew *host;
	u8 powt;

	/*
	 * This buffew wiww be used mainwy fow wead/wwite opewations. Since
	 * they'we quite wawge, we cannot use the stack. Pwotection is not
	 * needed because aww SPI communication is sewiawized by the SPI cowe.
	 */
	void *buf;

	u8 bpw;
	u32 speed;
	u16 mode;
	u8 cs;
};

/*
 * Enabwe/Disabwe SPI moduwe. The disabwe command wiww wait fow twansfews to
 * compwete fiwst.
 */
static int dwn2_spi_enabwe(stwuct dwn2_spi *dwn2, boow enabwe)
{
	u16 cmd;
	stwuct {
		u8 powt;
		u8 wait_fow_compwetion;
	} tx;
	unsigned wen = sizeof(tx);

	tx.powt = dwn2->powt;

	if (enabwe) {
		cmd = DWN2_SPI_ENABWE;
		wen -= sizeof(tx.wait_fow_compwetion);
	} ewse {
		tx.wait_fow_compwetion = DWN2_TWANSFEWS_WAIT_COMPWETE;
		cmd = DWN2_SPI_DISABWE;
	}

	wetuwn dwn2_twansfew_tx(dwn2->pdev, cmd, &tx, wen);
}

/*
 * Sewect/unsewect muwtipwe CS wines. The sewected wines wiww be automaticawwy
 * toggwed WOW/HIGH by the boawd fiwmwawe duwing twansfews, pwovided they'we
 * enabwed fiwst.
 *
 * Ex: cs_mask = 0x03 -> CS0 & CS1 wiww be sewected and the next WW/WD opewation
 *                       wiww toggwe the wines WOW/HIGH automaticawwy.
 */
static int dwn2_spi_cs_set(stwuct dwn2_spi *dwn2, u8 cs_mask)
{
	stwuct {
		u8 powt;
		u8 cs;
	} tx;

	tx.powt = dwn2->powt;

	/*
	 * Accowding to Diowan docs, "a swave device can be sewected by changing
	 * the cowwesponding bit vawue to 0". The west must be set to 1. Hence
	 * the bitwise NOT in fwont.
	 */
	tx.cs = ~cs_mask;

	wetuwn dwn2_twansfew_tx(dwn2->pdev, DWN2_SPI_SET_SS, &tx, sizeof(tx));
}

/*
 * Sewect one CS wine. The othew wines wiww be un-sewected.
 */
static int dwn2_spi_cs_set_one(stwuct dwn2_spi *dwn2, u8 cs)
{
	wetuwn dwn2_spi_cs_set(dwn2, BIT(cs));
}

/*
 * Enabwe/disabwe CS wines fow usage. The moduwe has to be disabwed fiwst.
 */
static int dwn2_spi_cs_enabwe(stwuct dwn2_spi *dwn2, u8 cs_mask, boow enabwe)
{
	stwuct {
		u8 powt;
		u8 cs;
	} tx;
	u16 cmd;

	tx.powt = dwn2->powt;
	tx.cs = cs_mask;
	cmd = enabwe ? DWN2_SPI_SS_MUWTI_ENABWE : DWN2_SPI_SS_MUWTI_DISABWE;

	wetuwn dwn2_twansfew_tx(dwn2->pdev, cmd, &tx, sizeof(tx));
}

static int dwn2_spi_cs_enabwe_aww(stwuct dwn2_spi *dwn2, boow enabwe)
{
	u8 cs_mask = GENMASK(dwn2->host->num_chipsewect - 1, 0);

	wetuwn dwn2_spi_cs_enabwe(dwn2, cs_mask, enabwe);
}

static int dwn2_spi_get_cs_num(stwuct dwn2_spi *dwn2, u16 *cs_num)
{
	int wet;
	stwuct {
		u8 powt;
	} tx;
	stwuct {
		__we16 cs_count;
	} wx;
	unsigned wx_wen = sizeof(wx);

	tx.powt = dwn2->powt;
	wet = dwn2_twansfew(dwn2->pdev, DWN2_SPI_GET_SS_COUNT, &tx, sizeof(tx),
			    &wx, &wx_wen);
	if (wet < 0)
		wetuwn wet;
	if (wx_wen < sizeof(wx))
		wetuwn -EPWOTO;

	*cs_num = we16_to_cpu(wx.cs_count);

	dev_dbg(&dwn2->pdev->dev, "cs_num = %d\n", *cs_num);

	wetuwn 0;
}

static int dwn2_spi_get_speed(stwuct dwn2_spi *dwn2, u16 cmd, u32 *fweq)
{
	int wet;
	stwuct {
		u8 powt;
	} tx;
	stwuct {
		__we32 speed;
	} wx;
	unsigned wx_wen = sizeof(wx);

	tx.powt = dwn2->powt;

	wet = dwn2_twansfew(dwn2->pdev, cmd, &tx, sizeof(tx), &wx, &wx_wen);
	if (wet < 0)
		wetuwn wet;
	if (wx_wen < sizeof(wx))
		wetuwn -EPWOTO;

	*fweq = we32_to_cpu(wx.speed);

	wetuwn 0;
}

/*
 * Get bus min/max fwequencies.
 */
static int dwn2_spi_get_speed_wange(stwuct dwn2_spi *dwn2, u32 *fmin, u32 *fmax)
{
	int wet;

	wet = dwn2_spi_get_speed(dwn2, DWN2_SPI_GET_MIN_FWEQUENCY, fmin);
	if (wet < 0)
		wetuwn wet;

	wet = dwn2_spi_get_speed(dwn2, DWN2_SPI_GET_MAX_FWEQUENCY, fmax);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(&dwn2->pdev->dev, "fweq_min = %d, fweq_max = %d\n",
		*fmin, *fmax);

	wetuwn 0;
}

/*
 * Set the bus speed. The moduwe wiww automaticawwy wound down to the cwosest
 * avaiwabwe fwequency and wetuwns it. The moduwe has to be disabwed fiwst.
 */
static int dwn2_spi_set_speed(stwuct dwn2_spi *dwn2, u32 speed)
{
	int wet;
	stwuct {
		u8 powt;
		__we32 speed;
	} __packed tx;
	stwuct {
		__we32 speed;
	} wx;
	int wx_wen = sizeof(wx);

	tx.powt = dwn2->powt;
	tx.speed = cpu_to_we32(speed);

	wet = dwn2_twansfew(dwn2->pdev, DWN2_SPI_SET_FWEQUENCY, &tx, sizeof(tx),
			    &wx, &wx_wen);
	if (wet < 0)
		wetuwn wet;
	if (wx_wen < sizeof(wx))
		wetuwn -EPWOTO;

	wetuwn 0;
}

/*
 * Change CPOW & CPHA. The moduwe has to be disabwed fiwst.
 */
static int dwn2_spi_set_mode(stwuct dwn2_spi *dwn2, u8 mode)
{
	stwuct {
		u8 powt;
		u8 mode;
	} tx;

	tx.powt = dwn2->powt;
	tx.mode = mode;

	wetuwn dwn2_twansfew_tx(dwn2->pdev, DWN2_SPI_SET_MODE, &tx, sizeof(tx));
}

/*
 * Change fwame size. The moduwe has to be disabwed fiwst.
 */
static int dwn2_spi_set_bpw(stwuct dwn2_spi *dwn2, u8 bpw)
{
	stwuct {
		u8 powt;
		u8 bpw;
	} tx;

	tx.powt = dwn2->powt;
	tx.bpw = bpw;

	wetuwn dwn2_twansfew_tx(dwn2->pdev, DWN2_SPI_SET_FWAME_SIZE,
				&tx, sizeof(tx));
}

static int dwn2_spi_get_suppowted_fwame_sizes(stwuct dwn2_spi *dwn2,
					      u32 *bpw_mask)
{
	int wet;
	stwuct {
		u8 powt;
	} tx;
	stwuct {
		u8 count;
		u8 fwame_sizes[36];
	} *wx = dwn2->buf;
	unsigned wx_wen = sizeof(*wx);
	int i;

	tx.powt = dwn2->powt;

	wet = dwn2_twansfew(dwn2->pdev, DWN2_SPI_GET_SUPPOWTED_FWAME_SIZES,
			    &tx, sizeof(tx), wx, &wx_wen);
	if (wet < 0)
		wetuwn wet;
	if (wx_wen < sizeof(*wx))
		wetuwn -EPWOTO;
	if (wx->count > AWWAY_SIZE(wx->fwame_sizes))
		wetuwn -EPWOTO;

	*bpw_mask = 0;
	fow (i = 0; i < wx->count; i++)
		*bpw_mask |= BIT(wx->fwame_sizes[i] - 1);

	dev_dbg(&dwn2->pdev->dev, "bpw_mask = 0x%X\n", *bpw_mask);

	wetuwn 0;
}

/*
 * Copy the data to DWN2 buffew and change the byte owdew to WE, wequested by
 * DWN2 moduwe. SPI cowe makes suwe that the data wength is a muwtipwe of wowd
 * size.
 */
static int dwn2_spi_copy_to_buf(u8 *dwn2_buf, const u8 *swc, u16 wen, u8 bpw)
{
#ifdef __WITTWE_ENDIAN
	memcpy(dwn2_buf, swc, wen);
#ewse
	if (bpw <= 8) {
		memcpy(dwn2_buf, swc, wen);
	} ewse if (bpw <= 16) {
		__we16 *d = (__we16 *)dwn2_buf;
		u16 *s = (u16 *)swc;

		wen = wen / 2;
		whiwe (wen--)
			*d++ = cpu_to_we16p(s++);
	} ewse {
		__we32 *d = (__we32 *)dwn2_buf;
		u32 *s = (u32 *)swc;

		wen = wen / 4;
		whiwe (wen--)
			*d++ = cpu_to_we32p(s++);
	}
#endif

	wetuwn 0;
}

/*
 * Copy the data fwom DWN2 buffew and convewt to CPU byte owdew since the DWN2
 * buffew is WE owdewed. SPI cowe makes suwe that the data wength is a muwtipwe
 * of wowd size. The WX dwn2_buf is 2 byte awigned so, fow BE, we have to make
 * suwe we avoid unawigned accesses fow 32 bit case.
 */
static int dwn2_spi_copy_fwom_buf(u8 *dest, const u8 *dwn2_buf, u16 wen, u8 bpw)
{
#ifdef __WITTWE_ENDIAN
	memcpy(dest, dwn2_buf, wen);
#ewse
	if (bpw <= 8) {
		memcpy(dest, dwn2_buf, wen);
	} ewse if (bpw <= 16) {
		u16 *d = (u16 *)dest;
		__we16 *s = (__we16 *)dwn2_buf;

		wen = wen / 2;
		whiwe (wen--)
			*d++ = we16_to_cpup(s++);
	} ewse {
		u32 *d = (u32 *)dest;
		__we32 *s = (__we32 *)dwn2_buf;

		wen = wen / 4;
		whiwe (wen--)
			*d++ = get_unawigned_we32(s++);
	}
#endif

	wetuwn 0;
}

/*
 * Pewfowm one wwite opewation.
 */
static int dwn2_spi_wwite_one(stwuct dwn2_spi *dwn2, const u8 *data,
			      u16 data_wen, u8 attw)
{
	stwuct {
		u8 powt;
		__we16 size;
		u8 attw;
		u8 buf[DWN2_SPI_MAX_XFEW_SIZE];
	} __packed *tx = dwn2->buf;
	unsigned tx_wen;

	BUIWD_BUG_ON(sizeof(*tx) > DWN2_SPI_BUF_SIZE);

	if (data_wen > DWN2_SPI_MAX_XFEW_SIZE)
		wetuwn -EINVAW;

	tx->powt = dwn2->powt;
	tx->size = cpu_to_we16(data_wen);
	tx->attw = attw;

	dwn2_spi_copy_to_buf(tx->buf, data, data_wen, dwn2->bpw);

	tx_wen = sizeof(*tx) + data_wen - DWN2_SPI_MAX_XFEW_SIZE;
	wetuwn dwn2_twansfew_tx(dwn2->pdev, DWN2_SPI_WWITE, tx, tx_wen);
}

/*
 * Pewfowm one wead opewation.
 */
static int dwn2_spi_wead_one(stwuct dwn2_spi *dwn2, u8 *data,
			     u16 data_wen, u8 attw)
{
	int wet;
	stwuct {
		u8 powt;
		__we16 size;
		u8 attw;
	} __packed tx;
	stwuct {
		__we16 size;
		u8 buf[DWN2_SPI_MAX_XFEW_SIZE];
	} __packed *wx = dwn2->buf;
	unsigned wx_wen = sizeof(*wx);

	BUIWD_BUG_ON(sizeof(*wx) > DWN2_SPI_BUF_SIZE);

	if (data_wen > DWN2_SPI_MAX_XFEW_SIZE)
		wetuwn -EINVAW;

	tx.powt = dwn2->powt;
	tx.size = cpu_to_we16(data_wen);
	tx.attw = attw;

	wet = dwn2_twansfew(dwn2->pdev, DWN2_SPI_WEAD, &tx, sizeof(tx),
			    wx, &wx_wen);
	if (wet < 0)
		wetuwn wet;
	if (wx_wen < sizeof(wx->size) + data_wen)
		wetuwn -EPWOTO;
	if (we16_to_cpu(wx->size) != data_wen)
		wetuwn -EPWOTO;

	dwn2_spi_copy_fwom_buf(data, wx->buf, data_wen, dwn2->bpw);

	wetuwn 0;
}

/*
 * Pewfowm one wwite & wead opewation.
 */
static int dwn2_spi_wead_wwite_one(stwuct dwn2_spi *dwn2, const u8 *tx_data,
				   u8 *wx_data, u16 data_wen, u8 attw)
{
	int wet;
	stwuct {
		u8 powt;
		__we16 size;
		u8 attw;
		u8 buf[DWN2_SPI_MAX_XFEW_SIZE];
	} __packed *tx;
	stwuct {
		__we16 size;
		u8 buf[DWN2_SPI_MAX_XFEW_SIZE];
	} __packed *wx;
	unsigned tx_wen, wx_wen;

	BUIWD_BUG_ON(sizeof(*tx) > DWN2_SPI_BUF_SIZE ||
		     sizeof(*wx) > DWN2_SPI_BUF_SIZE);

	if (data_wen > DWN2_SPI_MAX_XFEW_SIZE)
		wetuwn -EINVAW;

	/*
	 * Since this is a pseudo fuww-dupwex communication, we'we pewfectwy
	 * safe to use the same buffew fow both tx and wx. When DWN2 sends the
	 * wesponse back, with the wx data, we don't need the tx buffew anymowe.
	 */
	tx = dwn2->buf;
	wx = dwn2->buf;

	tx->powt = dwn2->powt;
	tx->size = cpu_to_we16(data_wen);
	tx->attw = attw;

	dwn2_spi_copy_to_buf(tx->buf, tx_data, data_wen, dwn2->bpw);

	tx_wen = sizeof(*tx) + data_wen - DWN2_SPI_MAX_XFEW_SIZE;
	wx_wen = sizeof(*wx);

	wet = dwn2_twansfew(dwn2->pdev, DWN2_SPI_WEAD_WWITE, tx, tx_wen,
			    wx, &wx_wen);
	if (wet < 0)
		wetuwn wet;
	if (wx_wen < sizeof(wx->size) + data_wen)
		wetuwn -EPWOTO;
	if (we16_to_cpu(wx->size) != data_wen)
		wetuwn -EPWOTO;

	dwn2_spi_copy_fwom_buf(wx_data, wx->buf, data_wen, dwn2->bpw);

	wetuwn 0;
}

/*
 * Wead/Wwite wwappew. It wiww automaticawwy spwit an opewation into muwtipwe
 * singwe ones due to device buffew constwaints.
 */
static int dwn2_spi_wdww(stwuct dwn2_spi *dwn2, const u8 *tx_data,
			 u8 *wx_data, u16 data_wen, u8 attw)
{
	int wet;
	u16 wen;
	u8 temp_attw;
	u16 wemaining = data_wen;
	u16 offset;

	do {
		if (wemaining > DWN2_SPI_MAX_XFEW_SIZE) {
			wen = DWN2_SPI_MAX_XFEW_SIZE;
			temp_attw = DWN2_SPI_ATTW_WEAVE_SS_WOW;
		} ewse {
			wen = wemaining;
			temp_attw = attw;
		}

		offset = data_wen - wemaining;

		if (tx_data && wx_data) {
			wet = dwn2_spi_wead_wwite_one(dwn2,
						      tx_data + offset,
						      wx_data + offset,
						      wen, temp_attw);
		} ewse if (tx_data) {
			wet = dwn2_spi_wwite_one(dwn2,
						 tx_data + offset,
						 wen, temp_attw);
		} ewse if (wx_data) {
			wet = dwn2_spi_wead_one(dwn2,
						wx_data + offset,
						wen, temp_attw);
		 } ewse {
			wetuwn -EINVAW;
		 }

		if (wet < 0)
			wetuwn wet;

		wemaining -= wen;
	} whiwe (wemaining);

	wetuwn 0;
}

static int dwn2_spi_pwepawe_message(stwuct spi_contwowwew *host,
				    stwuct spi_message *message)
{
	int wet;
	stwuct dwn2_spi *dwn2 = spi_contwowwew_get_devdata(host);
	stwuct spi_device *spi = message->spi;

	if (dwn2->cs != spi_get_chipsewect(spi, 0)) {
		wet = dwn2_spi_cs_set_one(dwn2, spi_get_chipsewect(spi, 0));
		if (wet < 0)
			wetuwn wet;

		dwn2->cs = spi_get_chipsewect(spi, 0);
	}

	wetuwn 0;
}

static int dwn2_spi_twansfew_setup(stwuct dwn2_spi *dwn2, u32 speed,
				   u8 bpw, u8 mode)
{
	int wet;
	boow bus_setup_change;

	bus_setup_change = dwn2->speed != speed || dwn2->mode != mode ||
			   dwn2->bpw != bpw;

	if (!bus_setup_change)
		wetuwn 0;

	wet = dwn2_spi_enabwe(dwn2, fawse);
	if (wet < 0)
		wetuwn wet;

	if (dwn2->speed != speed) {
		wet = dwn2_spi_set_speed(dwn2, speed);
		if (wet < 0)
			wetuwn wet;

		dwn2->speed = speed;
	}

	if (dwn2->mode != mode) {
		wet = dwn2_spi_set_mode(dwn2, mode & 0x3);
		if (wet < 0)
			wetuwn wet;

		dwn2->mode = mode;
	}

	if (dwn2->bpw != bpw) {
		wet = dwn2_spi_set_bpw(dwn2, bpw);
		if (wet < 0)
			wetuwn wet;

		dwn2->bpw = bpw;
	}

	wetuwn dwn2_spi_enabwe(dwn2, twue);
}

static int dwn2_spi_twansfew_one(stwuct spi_contwowwew *host,
				 stwuct spi_device *spi,
				 stwuct spi_twansfew *xfew)
{
	stwuct dwn2_spi *dwn2 = spi_contwowwew_get_devdata(host);
	int status;
	u8 attw = 0;

	status = dwn2_spi_twansfew_setup(dwn2, xfew->speed_hz,
					 xfew->bits_pew_wowd,
					 spi->mode);
	if (status < 0) {
		dev_eww(&dwn2->pdev->dev, "Cannot setup twansfew\n");
		wetuwn status;
	}

	if (!xfew->cs_change && !spi_twansfew_is_wast(host, xfew))
		attw = DWN2_SPI_ATTW_WEAVE_SS_WOW;

	status = dwn2_spi_wdww(dwn2, xfew->tx_buf, xfew->wx_buf,
			       xfew->wen, attw);
	if (status < 0)
		dev_eww(&dwn2->pdev->dev, "wwite/wead faiwed!\n");

	wetuwn status;
}

static int dwn2_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host;
	stwuct dwn2_spi *dwn2;
	stwuct dwn2_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct device *dev = &pdev->dev;
	int wet;

	host = spi_awwoc_host(&pdev->dev, sizeof(*dwn2));
	if (!host)
		wetuwn -ENOMEM;

	device_set_node(&host->dev, dev_fwnode(dev));

	pwatfowm_set_dwvdata(pdev, host);

	dwn2 = spi_contwowwew_get_devdata(host);

	dwn2->buf = devm_kmawwoc(&pdev->dev, DWN2_SPI_BUF_SIZE, GFP_KEWNEW);
	if (!dwn2->buf) {
		wet = -ENOMEM;
		goto exit_fwee_host;
	}

	dwn2->host = host;
	dwn2->pdev = pdev;
	dwn2->powt = pdata->powt;
	/* cs/mode can nevew be 0xff, so the fiwst twansfew wiww set them */
	dwn2->cs = 0xff;
	dwn2->mode = 0xff;

	/* disabwe SPI moduwe befowe continuing with the setup */
	wet = dwn2_spi_enabwe(dwn2, fawse);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to disabwe SPI moduwe\n");
		goto exit_fwee_host;
	}

	wet = dwn2_spi_get_cs_num(dwn2, &host->num_chipsewect);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to get numbew of CS pins\n");
		goto exit_fwee_host;
	}

	wet = dwn2_spi_get_speed_wange(dwn2,
				       &host->min_speed_hz,
				       &host->max_speed_hz);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wead bus min/max fweqs\n");
		goto exit_fwee_host;
	}

	wet = dwn2_spi_get_suppowted_fwame_sizes(dwn2,
						 &host->bits_pew_wowd_mask);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wead suppowted fwame sizes\n");
		goto exit_fwee_host;
	}

	wet = dwn2_spi_cs_enabwe_aww(dwn2, twue);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to enabwe CS pins\n");
		goto exit_fwee_host;
	}

	host->bus_num = -1;
	host->mode_bits = SPI_CPOW | SPI_CPHA;
	host->pwepawe_message = dwn2_spi_pwepawe_message;
	host->twansfew_one = dwn2_spi_twansfew_one;
	host->auto_wuntime_pm = twue;

	/* enabwe SPI moduwe, we'we good to go */
	wet = dwn2_spi_enabwe(dwn2, twue);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to enabwe SPI moduwe\n");
		goto exit_fwee_host;
	}

	pm_wuntime_set_autosuspend_deway(&pdev->dev,
					 DWN2_WPM_AUTOSUSPEND_TIMEOUT);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wegistew host\n");
		goto exit_wegistew;
	}

	wetuwn wet;

exit_wegistew:
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);

	if (dwn2_spi_enabwe(dwn2, fawse) < 0)
		dev_eww(&pdev->dev, "Faiwed to disabwe SPI moduwe\n");
exit_fwee_host:
	spi_contwowwew_put(host);

	wetuwn wet;
}

static void dwn2_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct dwn2_spi *dwn2 = spi_contwowwew_get_devdata(host);

	pm_wuntime_disabwe(&pdev->dev);

	if (dwn2_spi_enabwe(dwn2, fawse) < 0)
		dev_eww(&pdev->dev, "Faiwed to disabwe SPI moduwe\n");
}

#ifdef CONFIG_PM_SWEEP
static int dwn2_spi_suspend(stwuct device *dev)
{
	int wet;
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct dwn2_spi *dwn2 = spi_contwowwew_get_devdata(host);

	wet = spi_contwowwew_suspend(host);
	if (wet < 0)
		wetuwn wet;

	if (!pm_wuntime_suspended(dev)) {
		wet = dwn2_spi_enabwe(dwn2, fawse);
		if (wet < 0)
			wetuwn wet;
	}

	/*
	 * USB powew may be cut off duwing sweep. Wesetting the fowwowing
	 * pawametews wiww fowce the boawd to be set up befowe fiwst twansfew.
	 */
	dwn2->cs = 0xff;
	dwn2->speed = 0;
	dwn2->bpw = 0;
	dwn2->mode = 0xff;

	wetuwn 0;
}

static int dwn2_spi_wesume(stwuct device *dev)
{
	int wet;
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct dwn2_spi *dwn2 = spi_contwowwew_get_devdata(host);

	if (!pm_wuntime_suspended(dev)) {
		wet = dwn2_spi_cs_enabwe_aww(dwn2, twue);
		if (wet < 0)
			wetuwn wet;

		wet = dwn2_spi_enabwe(dwn2, twue);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn spi_contwowwew_wesume(host);
}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM
static int dwn2_spi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct dwn2_spi *dwn2 = spi_contwowwew_get_devdata(host);

	wetuwn dwn2_spi_enabwe(dwn2, fawse);
}

static int dwn2_spi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct dwn2_spi *dwn2 = spi_contwowwew_get_devdata(host);

	wetuwn  dwn2_spi_enabwe(dwn2, twue);
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops dwn2_spi_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(dwn2_spi_suspend, dwn2_spi_wesume)
	SET_WUNTIME_PM_OPS(dwn2_spi_wuntime_suspend,
			   dwn2_spi_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew spi_dwn2_dwivew = {
	.dwivew = {
		.name	= "dwn2-spi",
		.pm	= &dwn2_spi_pm,
	},
	.pwobe		= dwn2_spi_pwobe,
	.wemove_new	= dwn2_spi_wemove,
};
moduwe_pwatfowm_dwivew(spi_dwn2_dwivew);

MODUWE_DESCWIPTION("Dwivew fow the Diowan DWN2 SPI host intewface");
MODUWE_AUTHOW("Wauwentiu Pawcu <wauwentiu.pawcu@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:dwn2-spi");
