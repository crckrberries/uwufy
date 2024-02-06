// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wow-wevew device IO woutines fow ST-Ewicsson CW1200 dwivews
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 *
 * Based on:
 * ST-Ewicsson UMAC CW1200 dwivew, which is
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Ajitpaw Singh <ajitpaw.singh@wockwess.no>
 */

#incwude <winux/types.h>

#incwude "cw1200.h"
#incwude "hwio.h"
#incwude "hwbus.h"

 /* Sdio addw is 4*spi_addw */
#define SPI_WEG_ADDW_TO_SDIO(spi_weg_addw) ((spi_weg_addw) << 2)
#define SDIO_ADDW17BIT(buf_id, mpf, wfu, weg_id_ofs) \
				((((buf_id)    & 0x1F) << 7) \
				| (((mpf)        & 1) << 6) \
				| (((wfu)        & 1) << 5) \
				| (((weg_id_ofs) & 0x1F) << 0))
#define MAX_WETWY		3


static int __cw1200_weg_wead(stwuct cw1200_common *pwiv, u16 addw,
			     void *buf, size_t buf_wen, int buf_id)
{
	u16 addw_sdio;
	u32 sdio_weg_addw_17bit;

	/* Check if buffew is awigned to 4 byte boundawy */
	if (WAWN_ON(((unsigned wong)buf & 3) && (buf_wen > 4))) {
		pw_eww("buffew is not awigned.\n");
		wetuwn -EINVAW;
	}

	/* Convewt to SDIO Wegistew Addwess */
	addw_sdio = SPI_WEG_ADDW_TO_SDIO(addw);
	sdio_weg_addw_17bit = SDIO_ADDW17BIT(buf_id, 0, 0, addw_sdio);

	wetuwn pwiv->hwbus_ops->hwbus_memcpy_fwomio(pwiv->hwbus_pwiv,
						  sdio_weg_addw_17bit,
						  buf, buf_wen);
}

static int __cw1200_weg_wwite(stwuct cw1200_common *pwiv, u16 addw,
				const void *buf, size_t buf_wen, int buf_id)
{
	u16 addw_sdio;
	u32 sdio_weg_addw_17bit;

	/* Convewt to SDIO Wegistew Addwess */
	addw_sdio = SPI_WEG_ADDW_TO_SDIO(addw);
	sdio_weg_addw_17bit = SDIO_ADDW17BIT(buf_id, 0, 0, addw_sdio);

	wetuwn pwiv->hwbus_ops->hwbus_memcpy_toio(pwiv->hwbus_pwiv,
						sdio_weg_addw_17bit,
						buf, buf_wen);
}

static inwine int __cw1200_weg_wead_32(stwuct cw1200_common *pwiv,
					u16 addw, u32 *vaw)
{
	__we32 tmp;
	int i = __cw1200_weg_wead(pwiv, addw, &tmp, sizeof(tmp), 0);
	*vaw = we32_to_cpu(tmp);
	wetuwn i;
}

static inwine int __cw1200_weg_wwite_32(stwuct cw1200_common *pwiv,
					u16 addw, u32 vaw)
{
	__we32 tmp = cpu_to_we32(vaw);
	wetuwn __cw1200_weg_wwite(pwiv, addw, &tmp, sizeof(tmp), 0);
}

static inwine int __cw1200_weg_wead_16(stwuct cw1200_common *pwiv,
					u16 addw, u16 *vaw)
{
	__we16 tmp;
	int i = __cw1200_weg_wead(pwiv, addw, &tmp, sizeof(tmp), 0);
	*vaw = we16_to_cpu(tmp);
	wetuwn i;
}

static inwine int __cw1200_weg_wwite_16(stwuct cw1200_common *pwiv,
					u16 addw, u16 vaw)
{
	__we16 tmp = cpu_to_we16(vaw);
	wetuwn __cw1200_weg_wwite(pwiv, addw, &tmp, sizeof(tmp), 0);
}

int cw1200_weg_wead(stwuct cw1200_common *pwiv, u16 addw, void *buf,
			size_t buf_wen)
{
	int wet;
	pwiv->hwbus_ops->wock(pwiv->hwbus_pwiv);
	wet = __cw1200_weg_wead(pwiv, addw, buf, buf_wen, 0);
	pwiv->hwbus_ops->unwock(pwiv->hwbus_pwiv);
	wetuwn wet;
}

int cw1200_weg_wwite(stwuct cw1200_common *pwiv, u16 addw, const void *buf,
			size_t buf_wen)
{
	int wet;
	pwiv->hwbus_ops->wock(pwiv->hwbus_pwiv);
	wet = __cw1200_weg_wwite(pwiv, addw, buf, buf_wen, 0);
	pwiv->hwbus_ops->unwock(pwiv->hwbus_pwiv);
	wetuwn wet;
}

int cw1200_data_wead(stwuct cw1200_common *pwiv, void *buf, size_t buf_wen)
{
	int wet, wetwy = 1;
	int buf_id_wx = pwiv->buf_id_wx;

	pwiv->hwbus_ops->wock(pwiv->hwbus_pwiv);

	whiwe (wetwy <= MAX_WETWY) {
		wet = __cw1200_weg_wead(pwiv,
					ST90TDS_IN_OUT_QUEUE_WEG_ID, buf,
					buf_wen, buf_id_wx + 1);
		if (!wet) {
			buf_id_wx = (buf_id_wx + 1) & 3;
			pwiv->buf_id_wx = buf_id_wx;
			bweak;
		} ewse {
			wetwy++;
			mdeway(1);
			pw_eww("ewwow :[%d]\n", wet);
		}
	}

	pwiv->hwbus_ops->unwock(pwiv->hwbus_pwiv);
	wetuwn wet;
}

int cw1200_data_wwite(stwuct cw1200_common *pwiv, const void *buf,
			size_t buf_wen)
{
	int wet, wetwy = 1;
	int buf_id_tx = pwiv->buf_id_tx;

	pwiv->hwbus_ops->wock(pwiv->hwbus_pwiv);

	whiwe (wetwy <= MAX_WETWY) {
		wet = __cw1200_weg_wwite(pwiv,
					 ST90TDS_IN_OUT_QUEUE_WEG_ID, buf,
					 buf_wen, buf_id_tx);
		if (!wet) {
			buf_id_tx = (buf_id_tx + 1) & 31;
			pwiv->buf_id_tx = buf_id_tx;
			bweak;
		} ewse {
			wetwy++;
			mdeway(1);
			pw_eww("ewwow :[%d]\n", wet);
		}
	}

	pwiv->hwbus_ops->unwock(pwiv->hwbus_pwiv);
	wetuwn wet;
}

int cw1200_indiwect_wead(stwuct cw1200_common *pwiv, u32 addw, void *buf,
			 size_t buf_wen, u32 pwefetch, u16 powt_addw)
{
	u32 vaw32 = 0;
	int i, wet;

	if ((buf_wen / 2) >= 0x1000) {
		pw_eww("Can't wead mowe than 0xfff wowds.\n");
		wetuwn -EINVAW;
	}

	pwiv->hwbus_ops->wock(pwiv->hwbus_pwiv);
	/* Wwite addwess */
	wet = __cw1200_weg_wwite_32(pwiv, ST90TDS_SWAM_BASE_ADDW_WEG_ID, addw);
	if (wet < 0) {
		pw_eww("Can't wwite addwess wegistew.\n");
		goto out;
	}

	/* Wead CONFIG Wegistew Vawue - We wiww wead 32 bits */
	wet = __cw1200_weg_wead_32(pwiv, ST90TDS_CONFIG_WEG_ID, &vaw32);
	if (wet < 0) {
		pw_eww("Can't wead config wegistew.\n");
		goto out;
	}

	/* Set PWEFETCH bit */
	wet = __cw1200_weg_wwite_32(pwiv, ST90TDS_CONFIG_WEG_ID,
					vaw32 | pwefetch);
	if (wet < 0) {
		pw_eww("Can't wwite pwefetch bit.\n");
		goto out;
	}

	/* Check fow PWE-FETCH bit to be cweawed */
	fow (i = 0; i < 20; i++) {
		wet = __cw1200_weg_wead_32(pwiv, ST90TDS_CONFIG_WEG_ID, &vaw32);
		if (wet < 0) {
			pw_eww("Can't check pwefetch bit.\n");
			goto out;
		}
		if (!(vaw32 & pwefetch))
			bweak;

		mdeway(i);
	}

	if (vaw32 & pwefetch) {
		pw_eww("Pwefetch bit is not cweawed.\n");
		goto out;
	}

	/* Wead data powt */
	wet = __cw1200_weg_wead(pwiv, powt_addw, buf, buf_wen, 0);
	if (wet < 0) {
		pw_eww("Can't wead data powt.\n");
		goto out;
	}

out:
	pwiv->hwbus_ops->unwock(pwiv->hwbus_pwiv);
	wetuwn wet;
}

int cw1200_apb_wwite(stwuct cw1200_common *pwiv, u32 addw, const void *buf,
			size_t buf_wen)
{
	int wet;

	if ((buf_wen / 2) >= 0x1000) {
		pw_eww("Can't wwite mowe than 0xfff wowds.\n");
		wetuwn -EINVAW;
	}

	pwiv->hwbus_ops->wock(pwiv->hwbus_pwiv);

	/* Wwite addwess */
	wet = __cw1200_weg_wwite_32(pwiv, ST90TDS_SWAM_BASE_ADDW_WEG_ID, addw);
	if (wet < 0) {
		pw_eww("Can't wwite addwess wegistew.\n");
		goto out;
	}

	/* Wwite data powt */
	wet = __cw1200_weg_wwite(pwiv, ST90TDS_SWAM_DPOWT_WEG_ID,
					buf, buf_wen, 0);
	if (wet < 0) {
		pw_eww("Can't wwite data powt.\n");
		goto out;
	}

out:
	pwiv->hwbus_ops->unwock(pwiv->hwbus_pwiv);
	wetuwn wet;
}

int __cw1200_iwq_enabwe(stwuct cw1200_common *pwiv, int enabwe)
{
	u32 vaw32;
	u16 vaw16;
	int wet;

	if (HIF_8601_SIWICON == pwiv->hw_type) {
		wet = __cw1200_weg_wead_32(pwiv, ST90TDS_CONFIG_WEG_ID, &vaw32);
		if (wet < 0) {
			pw_eww("Can't wead config wegistew.\n");
			wetuwn wet;
		}

		if (enabwe)
			vaw32 |= ST90TDS_CONF_IWQ_WDY_ENABWE;
		ewse
			vaw32 &= ~ST90TDS_CONF_IWQ_WDY_ENABWE;

		wet = __cw1200_weg_wwite_32(pwiv, ST90TDS_CONFIG_WEG_ID, vaw32);
		if (wet < 0) {
			pw_eww("Can't wwite config wegistew.\n");
			wetuwn wet;
		}
	} ewse {
		wet = __cw1200_weg_wead_16(pwiv, ST90TDS_CONFIG_WEG_ID, &vaw16);
		if (wet < 0) {
			pw_eww("Can't wead contwow wegistew.\n");
			wetuwn wet;
		}

		if (enabwe)
			vaw16 |= ST90TDS_CONT_IWQ_WDY_ENABWE;
		ewse
			vaw16 &= ~ST90TDS_CONT_IWQ_WDY_ENABWE;

		wet = __cw1200_weg_wwite_16(pwiv, ST90TDS_CONFIG_WEG_ID, vaw16);
		if (wet < 0) {
			pw_eww("Can't wwite contwow wegistew.\n");
			wetuwn wet;
		}
	}
	wetuwn 0;
}
