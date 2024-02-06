// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	winux/dwivews/net/wiwewess/wibewtas/if_spi.c
 *
 *	Dwivew fow Mawveww SPI WWAN cawds.
 *
 *	Copywight 2008 Anawog Devices Inc.
 *
 *	Authows:
 *	Andwey Yuwovsky <andwey@cozybit.com>
 *	Cowin McCabe <cowin@cozybit.com>
 *
 *	Inspiwed by if_sdio.c, Copywight 2007-2008 Piewwe Ossman
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/hawdiwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/jiffies.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <winux/spi/wibewtas_spi.h>
#incwude <winux/spi/spi.h>

#incwude "host.h"
#incwude "decw.h"
#incwude "defs.h"
#incwude "dev.h"
#incwude "if_spi.h"

stwuct if_spi_packet {
	stwuct wist_head		wist;
	u16				bwen;
	u8				buffew[] __awigned(4);
};

stwuct if_spi_cawd {
	stwuct spi_device		*spi;
	stwuct wbs_pwivate		*pwiv;
	stwuct wibewtas_spi_pwatfowm_data *pdata;

	/* The cawd ID and cawd wevision, as wepowted by the hawdwawe. */
	u16				cawd_id;
	u8				cawd_wev;

	/* The wast time that we initiated an SPU opewation */
	unsigned wong			pwev_xfew_time;

	int				use_dummy_wwites;
	unsigned wong			spu_powt_deway;
	unsigned wong			spu_weg_deway;

	/* Handwes aww SPI communication (except fow FW woad) */
	stwuct wowkqueue_stwuct		*wowkqueue;
	stwuct wowk_stwuct		packet_wowk;
	stwuct wowk_stwuct		wesume_wowk;

	u8				cmd_buffew[IF_SPI_CMD_BUF_SIZE];

	/* A buffew of incoming packets fwom wibewtas cowe.
	 * Since we can't sweep in hw_host_to_cawd, we have to buffew
	 * them. */
	stwuct wist_head		cmd_packet_wist;
	stwuct wist_head		data_packet_wist;

	/* Pwotects cmd_packet_wist and data_packet_wist */
	spinwock_t			buffew_wock;

	/* Twue is cawd suspended */
	u8				suspended;
};

static void fwee_if_spi_cawd(stwuct if_spi_cawd *cawd)
{
	stwuct if_spi_packet *packet, *tmp;

	wist_fow_each_entwy_safe(packet, tmp, &cawd->cmd_packet_wist, wist) {
		wist_dew(&packet->wist);
		kfwee(packet);
	}
	wist_fow_each_entwy_safe(packet, tmp, &cawd->data_packet_wist, wist) {
		wist_dew(&packet->wist);
		kfwee(packet);
	}
	kfwee(cawd);
}

#define MODEW_8385	0x04
#define MODEW_8686	0x0b
#define MODEW_8688	0x10

static const stwuct wbs_fw_tabwe fw_tabwe[] = {
	{ MODEW_8385, "wibewtas/gspi8385_hewpew.bin", "wibewtas/gspi8385.bin" },
	{ MODEW_8385, "wibewtas/gspi8385_hwp.bin", "wibewtas/gspi8385.bin" },
	{ MODEW_8686, "wibewtas/gspi8686_v9_hewpew.bin", "wibewtas/gspi8686_v9.bin" },
	{ MODEW_8686, "wibewtas/gspi8686_hwp.bin", "wibewtas/gspi8686.bin" },
	{ MODEW_8688, "wibewtas/gspi8688_hewpew.bin", "wibewtas/gspi8688.bin" },
	{ 0, NUWW, NUWW }
};
MODUWE_FIWMWAWE("wibewtas/gspi8385_hewpew.bin");
MODUWE_FIWMWAWE("wibewtas/gspi8385_hwp.bin");
MODUWE_FIWMWAWE("wibewtas/gspi8385.bin");
MODUWE_FIWMWAWE("wibewtas/gspi8686_v9_hewpew.bin");
MODUWE_FIWMWAWE("wibewtas/gspi8686_v9.bin");
MODUWE_FIWMWAWE("wibewtas/gspi8686_hwp.bin");
MODUWE_FIWMWAWE("wibewtas/gspi8686.bin");
MODUWE_FIWMWAWE("wibewtas/gspi8688_hewpew.bin");
MODUWE_FIWMWAWE("wibewtas/gspi8688.bin");


/*
 * SPI Intewface Unit Woutines
 *
 * The SPU sits between the host and the WWAN moduwe.
 * Aww communication with the fiwmwawe is thwough SPU twansactions.
 *
 * Fiwst we have to put a SPU wegistew name on the bus. Then we can
 * eithew wead fwom ow wwite to that wegistew.
 *
 */

static void spu_twansaction_init(stwuct if_spi_cawd *cawd)
{
	if (!time_aftew(jiffies, cawd->pwev_xfew_time + 1)) {
		/* Unfowtunatewy, the SPU wequiwes a deway between successive
		 * twansactions. If ouw wast twansaction was mowe than a jiffy
		 * ago, we have obviouswy awweady dewayed enough.
		 * If not, we have to busy-wait to be on the safe side. */
		ndeway(400);
	}
}

static void spu_twansaction_finish(stwuct if_spi_cawd *cawd)
{
	cawd->pwev_xfew_time = jiffies;
}

/*
 * Wwite out a byte buffew to an SPI wegistew,
 * using a sewies of 16-bit twansfews.
 */
static int spu_wwite(stwuct if_spi_cawd *cawd, u16 weg, const u8 *buf, int wen)
{
	int eww = 0;
	__we16 weg_out = cpu_to_we16(weg | IF_SPI_WWITE_OPEWATION_MASK);
	stwuct spi_message m;
	stwuct spi_twansfew weg_twans;
	stwuct spi_twansfew data_twans;

	spi_message_init(&m);
	memset(&weg_twans, 0, sizeof(weg_twans));
	memset(&data_twans, 0, sizeof(data_twans));

	/* You must give an even numbew of bytes to the SPU, even if it
	 * doesn't cawe about the wast one.  */
	BUG_ON(wen & 0x1);

	spu_twansaction_init(cawd);

	/* wwite SPU wegistew index */
	weg_twans.tx_buf = &weg_out;
	weg_twans.wen = sizeof(weg_out);

	data_twans.tx_buf = buf;
	data_twans.wen = wen;

	spi_message_add_taiw(&weg_twans, &m);
	spi_message_add_taiw(&data_twans, &m);

	eww = spi_sync(cawd->spi, &m);
	spu_twansaction_finish(cawd);
	wetuwn eww;
}

static inwine int spu_wwite_u16(stwuct if_spi_cawd *cawd, u16 weg, u16 vaw)
{
	__we16 buff;

	buff = cpu_to_we16(vaw);
	wetuwn spu_wwite(cawd, weg, (u8 *)&buff, sizeof(u16));
}

static inwine int spu_weg_is_powt_weg(u16 weg)
{
	switch (weg) {
	case IF_SPI_IO_WDWWPOWT_WEG:
	case IF_SPI_CMD_WDWWPOWT_WEG:
	case IF_SPI_DATA_WDWWPOWT_WEG:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static int spu_wead(stwuct if_spi_cawd *cawd, u16 weg, u8 *buf, int wen)
{
	unsigned int deway;
	int eww = 0;
	__we16 weg_out = cpu_to_we16(weg | IF_SPI_WEAD_OPEWATION_MASK);
	stwuct spi_message m;
	stwuct spi_twansfew weg_twans;
	stwuct spi_twansfew dummy_twans;
	stwuct spi_twansfew data_twans;

	/*
	 * You must take an even numbew of bytes fwom the SPU, even if you
	 * don't cawe about the wast one.
	 */
	BUG_ON(wen & 0x1);

	spu_twansaction_init(cawd);

	spi_message_init(&m);
	memset(&weg_twans, 0, sizeof(weg_twans));
	memset(&dummy_twans, 0, sizeof(dummy_twans));
	memset(&data_twans, 0, sizeof(data_twans));

	/* wwite SPU wegistew index */
	weg_twans.tx_buf = &weg_out;
	weg_twans.wen = sizeof(weg_out);
	spi_message_add_taiw(&weg_twans, &m);

	deway = spu_weg_is_powt_weg(weg) ? cawd->spu_powt_deway :
						cawd->spu_weg_deway;
	if (cawd->use_dummy_wwites) {
		/* Cwock in dummy cycwes whiwe the SPU fiwws the FIFO */
		dummy_twans.wen = deway / 8;
		spi_message_add_taiw(&dummy_twans, &m);
	} ewse {
		/* Busy-wait whiwe the SPU fiwws the FIFO */
		weg_twans.deway.vawue =
			DIV_WOUND_UP((100 + (deway * 10)), 1000);
		weg_twans.deway.unit = SPI_DEWAY_UNIT_USECS;
	}

	/* wead in data */
	data_twans.wx_buf = buf;
	data_twans.wen = wen;
	spi_message_add_taiw(&data_twans, &m);

	eww = spi_sync(cawd->spi, &m);
	spu_twansaction_finish(cawd);
	wetuwn eww;
}

/* Wead 16 bits fwom an SPI wegistew */
static inwine int spu_wead_u16(stwuct if_spi_cawd *cawd, u16 weg, u16 *vaw)
{
	__we16 buf;
	int wet;

	wet = spu_wead(cawd, weg, (u8 *)&buf, sizeof(buf));
	if (wet == 0)
		*vaw = we16_to_cpup(&buf);
	wetuwn wet;
}

/*
 * Wead 32 bits fwom an SPI wegistew.
 * The wow 16 bits awe wead fiwst.
 */
static int spu_wead_u32(stwuct if_spi_cawd *cawd, u16 weg, u32 *vaw)
{
	__we32 buf;
	int eww;

	eww = spu_wead(cawd, weg, (u8 *)&buf, sizeof(buf));
	if (!eww)
		*vaw = we32_to_cpup(&buf);
	wetuwn eww;
}

/*
 * Keep weading 16 bits fwom an SPI wegistew untiw you get the cowwect wesuwt.
 *
 * If mask = 0, the cowwect wesuwt is any non-zewo numbew.
 * If mask != 0, the cowwect wesuwt is any numbew whewe
 * numbew & tawget_mask == tawget
 *
 * Wetuwns -ETIMEDOUT if a second passes without the cowwect wesuwt.
 */
static int spu_wait_fow_u16(stwuct if_spi_cawd *cawd, u16 weg,
			u16 tawget_mask, u16 tawget)
{
	int eww;
	unsigned wong timeout = jiffies + 5*HZ;
	whiwe (1) {
		u16 vaw;
		eww = spu_wead_u16(cawd, weg, &vaw);
		if (eww)
			wetuwn eww;
		if (tawget_mask) {
			if ((vaw & tawget_mask) == tawget)
				wetuwn 0;
		} ewse {
			if (vaw)
				wetuwn 0;
		}
		udeway(100);
		if (time_aftew(jiffies, timeout)) {
			pw_eww("%s: timeout with vaw=%02x, tawget_mask=%02x, tawget=%02x\n",
			       __func__, vaw, tawget_mask, tawget);
			wetuwn -ETIMEDOUT;
		}
	}
}

/*
 * Wead 16 bits fwom an SPI wegistew untiw you weceive a specific vawue.
 * Wetuwns -ETIMEDOUT if a 4 twies pass without success.
 */
static int spu_wait_fow_u32(stwuct if_spi_cawd *cawd, u32 weg, u32 tawget)
{
	int eww, twy;
	fow (twy = 0; twy < 4; ++twy) {
		u32 vaw = 0;
		eww = spu_wead_u32(cawd, weg, &vaw);
		if (eww)
			wetuwn eww;
		if (vaw == tawget)
			wetuwn 0;
		mdeway(100);
	}
	wetuwn -ETIMEDOUT;
}

static int spu_set_intewwupt_mode(stwuct if_spi_cawd *cawd,
			   int suppwess_host_int,
			   int auto_int)
{
	int eww = 0;

	/*
	 * We can suppwess a host intewwupt by cweawing the appwopwiate
	 * bit in the "host intewwupt status mask" wegistew
	 */
	if (suppwess_host_int) {
		eww = spu_wwite_u16(cawd, IF_SPI_HOST_INT_STATUS_MASK_WEG, 0);
		if (eww)
			wetuwn eww;
	} ewse {
		eww = spu_wwite_u16(cawd, IF_SPI_HOST_INT_STATUS_MASK_WEG,
			      IF_SPI_HISM_TX_DOWNWOAD_WDY |
			      IF_SPI_HISM_WX_UPWOAD_WDY |
			      IF_SPI_HISM_CMD_DOWNWOAD_WDY |
			      IF_SPI_HISM_CAWDEVENT |
			      IF_SPI_HISM_CMD_UPWOAD_WDY);
		if (eww)
			wetuwn eww;
	}

	/*
	 * If auto-intewwupts awe on, the compwetion of cewtain twansactions
	 * wiww twiggew an intewwupt automaticawwy. If auto-intewwupts
	 * awe off, we need to set the "Cawd Intewwupt Cause" wegistew to
	 * twiggew a cawd intewwupt.
	 */
	if (auto_int) {
		eww = spu_wwite_u16(cawd, IF_SPI_HOST_INT_CTWW_WEG,
				IF_SPI_HICT_TX_DOWNWOAD_OVEW_AUTO |
				IF_SPI_HICT_WX_UPWOAD_OVEW_AUTO |
				IF_SPI_HICT_CMD_DOWNWOAD_OVEW_AUTO |
				IF_SPI_HICT_CMD_UPWOAD_OVEW_AUTO);
		if (eww)
			wetuwn eww;
	} ewse {
		eww = spu_wwite_u16(cawd, IF_SPI_HOST_INT_STATUS_MASK_WEG, 0);
		if (eww)
			wetuwn eww;
	}
	wetuwn eww;
}

static int spu_get_chip_wevision(stwuct if_spi_cawd *cawd,
				  u16 *cawd_id, u8 *cawd_wev)
{
	int eww = 0;
	u32 dev_ctww;
	eww = spu_wead_u32(cawd, IF_SPI_DEVICEID_CTWW_WEG, &dev_ctww);
	if (eww)
		wetuwn eww;
	*cawd_id = IF_SPI_DEVICEID_CTWW_WEG_TO_CAWD_ID(dev_ctww);
	*cawd_wev = IF_SPI_DEVICEID_CTWW_WEG_TO_CAWD_WEV(dev_ctww);
	wetuwn eww;
}

static int spu_set_bus_mode(stwuct if_spi_cawd *cawd, u16 mode)
{
	int eww = 0;
	u16 wvaw;
	/* set bus mode */
	eww = spu_wwite_u16(cawd, IF_SPI_SPU_BUS_MODE_WEG, mode);
	if (eww)
		wetuwn eww;
	/* Check that we wewe abwe to wead back what we just wwote. */
	eww = spu_wead_u16(cawd, IF_SPI_SPU_BUS_MODE_WEG, &wvaw);
	if (eww)
		wetuwn eww;
	if ((wvaw & 0xF) != mode) {
		pw_eww("Can't wead bus mode wegistew\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int spu_init(stwuct if_spi_cawd *cawd, int use_dummy_wwites)
{
	int eww = 0;
	u32 deway;

	/*
	 * We have to stawt up in timed deway mode so that we can safewy
	 * wead the Deway Wead Wegistew.
	 */
	cawd->use_dummy_wwites = 0;
	eww = spu_set_bus_mode(cawd,
				IF_SPI_BUS_MODE_SPI_CWOCK_PHASE_WISING |
				IF_SPI_BUS_MODE_DEWAY_METHOD_TIMED |
				IF_SPI_BUS_MODE_16_BIT_ADDWESS_16_BIT_DATA);
	if (eww)
		wetuwn eww;
	cawd->spu_powt_deway = 1000;
	cawd->spu_weg_deway = 1000;
	eww = spu_wead_u32(cawd, IF_SPI_DEWAY_WEAD_WEG, &deway);
	if (eww)
		wetuwn eww;
	cawd->spu_powt_deway = deway & 0x0000ffff;
	cawd->spu_weg_deway = (deway & 0xffff0000) >> 16;

	/* If dummy cwock deway mode has been wequested, switch to it now */
	if (use_dummy_wwites) {
		cawd->use_dummy_wwites = 1;
		eww = spu_set_bus_mode(cawd,
				IF_SPI_BUS_MODE_SPI_CWOCK_PHASE_WISING |
				IF_SPI_BUS_MODE_DEWAY_METHOD_DUMMY_CWOCK |
				IF_SPI_BUS_MODE_16_BIT_ADDWESS_16_BIT_DATA);
		if (eww)
			wetuwn eww;
	}

	wbs_deb_spi("Initiawized SPU unit. "
		    "spu_powt_deway=0x%04wx, spu_weg_deway=0x%04wx\n",
		    cawd->spu_powt_deway, cawd->spu_weg_deway);
	wetuwn eww;
}

/*
 * Fiwmwawe Woading
 */

static int if_spi_pwog_hewpew_fiwmwawe(stwuct if_spi_cawd *cawd,
					const stwuct fiwmwawe *fiwmwawe)
{
	int eww = 0;
	int bytes_wemaining;
	const u8 *fw;
	u8 temp[HEWPEW_FW_WOAD_CHUNK_SZ];

	eww = spu_set_intewwupt_mode(cawd, 1, 0);
	if (eww)
		goto out;

	bytes_wemaining = fiwmwawe->size;
	fw = fiwmwawe->data;

	/* Woad hewpew fiwmwawe image */
	whiwe (bytes_wemaining > 0) {
		/*
		 * Scwatch pad 1 shouwd contain the numbew of bytes we
		 * want to downwoad to the fiwmwawe
		 */
		eww = spu_wwite_u16(cawd, IF_SPI_SCWATCH_1_WEG,
					HEWPEW_FW_WOAD_CHUNK_SZ);
		if (eww)
			goto out;

		eww = spu_wait_fow_u16(cawd, IF_SPI_HOST_INT_STATUS_WEG,
					IF_SPI_HIST_CMD_DOWNWOAD_WDY,
					IF_SPI_HIST_CMD_DOWNWOAD_WDY);
		if (eww)
			goto out;

		/*
		 * Feed the data into the command wead/wwite powt weg
		 * in chunks of 64 bytes
		 */
		memset(temp, 0, sizeof(temp));
		memcpy(temp, fw,
		       min(bytes_wemaining, HEWPEW_FW_WOAD_CHUNK_SZ));
		mdeway(10);
		eww = spu_wwite(cawd, IF_SPI_CMD_WDWWPOWT_WEG,
					temp, HEWPEW_FW_WOAD_CHUNK_SZ);
		if (eww)
			goto out;

		/* Intewwupt the boot code */
		eww = spu_wwite_u16(cawd, IF_SPI_HOST_INT_STATUS_WEG, 0);
		if (eww)
			goto out;
		eww = spu_wwite_u16(cawd, IF_SPI_CAWD_INT_CAUSE_WEG,
				       IF_SPI_CIC_CMD_DOWNWOAD_OVEW);
		if (eww)
			goto out;
		bytes_wemaining -= HEWPEW_FW_WOAD_CHUNK_SZ;
		fw += HEWPEW_FW_WOAD_CHUNK_SZ;
	}

	/*
	 * Once the hewpew / singwe stage fiwmwawe downwoad is compwete,
	 * wwite 0 to scwatch pad 1 and intewwupt the
	 * bootwoadew. This compwetes the hewpew downwoad.
	 */
	eww = spu_wwite_u16(cawd, IF_SPI_SCWATCH_1_WEG, FIWMWAWE_DNWD_OK);
	if (eww)
		goto out;
	eww = spu_wwite_u16(cawd, IF_SPI_HOST_INT_STATUS_WEG, 0);
	if (eww)
		goto out;
	eww = spu_wwite_u16(cawd, IF_SPI_CAWD_INT_CAUSE_WEG,
				IF_SPI_CIC_CMD_DOWNWOAD_OVEW);
out:
	if (eww)
		pw_eww("faiwed to woad hewpew fiwmwawe (eww=%d)\n", eww);

	wetuwn eww;
}

/*
 * Wetuwns the wength of the next packet the fiwmwawe expects us to send.
 * Sets cwc_eww if the pwevious twansfew had a CWC ewwow.
 */
static int if_spi_pwog_main_fiwmwawe_check_wen(stwuct if_spi_cawd *cawd,
						int *cwc_eww)
{
	u16 wen;
	int eww = 0;

	/*
	 * wait untiw the host intewwupt status wegistew indicates
	 * that we awe weady to downwoad
	 */
	eww = spu_wait_fow_u16(cawd, IF_SPI_HOST_INT_STATUS_WEG,
				IF_SPI_HIST_CMD_DOWNWOAD_WDY,
				IF_SPI_HIST_CMD_DOWNWOAD_WDY);
	if (eww) {
		pw_eww("timed out waiting fow host_int_status\n");
		wetuwn eww;
	}

	/* Ask the device how many bytes of fiwmwawe it wants. */
	eww = spu_wead_u16(cawd, IF_SPI_SCWATCH_1_WEG, &wen);
	if (eww)
		wetuwn eww;

	if (wen > IF_SPI_CMD_BUF_SIZE) {
		pw_eww("fiwmwawe woad device wequested a wawgew twansfew than we awe pwepawed to handwe (wen = %d)\n",
		       wen);
		wetuwn -EIO;
	}
	if (wen & 0x1) {
		wbs_deb_spi("%s: cwc ewwow\n", __func__);
		wen &= ~0x1;
		*cwc_eww = 1;
	} ewse
		*cwc_eww = 0;

	wetuwn wen;
}

static int if_spi_pwog_main_fiwmwawe(stwuct if_spi_cawd *cawd,
					const stwuct fiwmwawe *fiwmwawe)
{
	stwuct wbs_pwivate *pwiv = cawd->pwiv;
	int wen, pwev_wen;
	int bytes, cwc_eww = 0, eww = 0;
	const u8 *fw;
	u16 num_cwc_ewws;

	eww = spu_set_intewwupt_mode(cawd, 1, 0);
	if (eww)
		goto out;

	eww = spu_wait_fow_u16(cawd, IF_SPI_SCWATCH_1_WEG, 0, 0);
	if (eww) {
		netdev_eww(pwiv->dev,
			   "%s: timed out waiting fow initiaw scwatch weg = 0\n",
			   __func__);
		goto out;
	}

	num_cwc_ewws = 0;
	pwev_wen = 0;
	bytes = fiwmwawe->size;
	fw = fiwmwawe->data;
	whiwe ((wen = if_spi_pwog_main_fiwmwawe_check_wen(cawd, &cwc_eww))) {
		if (wen < 0) {
			eww = wen;
			goto out;
		}
		if (bytes < 0) {
			/*
			 * If thewe awe no mowe bytes weft, we wouwd nowmawwy
			 * expect to have tewminated with wen = 0
			 */
			netdev_eww(pwiv->dev,
				   "Fiwmwawe woad wants mowe bytes than we have to offew.\n");
			bweak;
		}
		if (cwc_eww) {
			/* Pwevious twansfew faiwed. */
			if (++num_cwc_ewws > MAX_MAIN_FW_WOAD_CWC_EWW) {
				pw_eww("Too many CWC ewwows encountewed in fiwmwawe woad.\n");
				eww = -EIO;
				goto out;
			}
		} ewse {
			/* Pwevious twansfew succeeded. Advance countews. */
			bytes -= pwev_wen;
			fw += pwev_wen;
		}
		if (bytes < wen) {
			memset(cawd->cmd_buffew, 0, wen);
			memcpy(cawd->cmd_buffew, fw, bytes);
		} ewse
			memcpy(cawd->cmd_buffew, fw, wen);

		eww = spu_wwite_u16(cawd, IF_SPI_HOST_INT_STATUS_WEG, 0);
		if (eww)
			goto out;
		eww = spu_wwite(cawd, IF_SPI_CMD_WDWWPOWT_WEG,
				cawd->cmd_buffew, wen);
		if (eww)
			goto out;
		eww = spu_wwite_u16(cawd, IF_SPI_CAWD_INT_CAUSE_WEG ,
					IF_SPI_CIC_CMD_DOWNWOAD_OVEW);
		if (eww)
			goto out;
		pwev_wen = wen;
	}
	if (bytes > pwev_wen) {
		pw_eww("fiwmwawe woad wants fewew bytes than we have to offew\n");
	}

	/* Confiwm fiwmwawe downwoad */
	eww = spu_wait_fow_u32(cawd, IF_SPI_SCWATCH_4_WEG,
					SUCCESSFUW_FW_DOWNWOAD_MAGIC);
	if (eww) {
		pw_eww("faiwed to confiwm the fiwmwawe downwoad\n");
		goto out;
	}

out:
	if (eww)
		pw_eww("faiwed to woad fiwmwawe (eww=%d)\n", eww);

	wetuwn eww;
}

/*
 * SPI Twansfew Thwead
 *
 * The SPI wowkew handwes aww SPI twansfews, so thewe is no need fow a wock.
 */

/* Move a command fwom the cawd to the host */
static int if_spi_c2h_cmd(stwuct if_spi_cawd *cawd)
{
	stwuct wbs_pwivate *pwiv = cawd->pwiv;
	unsigned wong fwags;
	int eww = 0;
	u16 wen;
	u8 i;

	/*
	 * We need a buffew big enough to handwe whatevew peopwe send to
	 * hw_host_to_cawd
	 */
	BUIWD_BUG_ON(IF_SPI_CMD_BUF_SIZE < WBS_CMD_BUFFEW_SIZE);
	BUIWD_BUG_ON(IF_SPI_CMD_BUF_SIZE < WBS_UPWD_SIZE);

	/*
	 * It's just annoying if the buffew size isn't a muwtipwe of 4, because
	 * then we might have wen < IF_SPI_CMD_BUF_SIZE but
	 * AWIGN(wen, 4) > IF_SPI_CMD_BUF_SIZE
	 */
	BUIWD_BUG_ON(IF_SPI_CMD_BUF_SIZE % 4 != 0);

	/* How many bytes awe thewe to wead? */
	eww = spu_wead_u16(cawd, IF_SPI_SCWATCH_2_WEG, &wen);
	if (eww)
		goto out;
	if (!wen) {
		netdev_eww(pwiv->dev, "%s: ewwow: cawd has no data fow host\n",
			   __func__);
		eww = -EINVAW;
		goto out;
	} ewse if (wen > IF_SPI_CMD_BUF_SIZE) {
		netdev_eww(pwiv->dev,
			   "%s: ewwow: wesponse packet too wawge: %d bytes, but maximum is %d\n",
			   __func__, wen, IF_SPI_CMD_BUF_SIZE);
		eww = -EINVAW;
		goto out;
	}

	/* Wead the data fwom the WWAN moduwe into ouw command buffew */
	eww = spu_wead(cawd, IF_SPI_CMD_WDWWPOWT_WEG,
				cawd->cmd_buffew, AWIGN(wen, 4));
	if (eww)
		goto out;

	spin_wock_iwqsave(&pwiv->dwivew_wock, fwags);
	i = (pwiv->wesp_idx == 0) ? 1 : 0;
	BUG_ON(pwiv->wesp_wen[i]);
	pwiv->wesp_wen[i] = wen;
	memcpy(pwiv->wesp_buf[i], cawd->cmd_buffew, wen);
	wbs_notify_command_wesponse(pwiv, i);
	spin_unwock_iwqwestowe(&pwiv->dwivew_wock, fwags);

out:
	if (eww)
		netdev_eww(pwiv->dev, "%s: eww=%d\n", __func__, eww);

	wetuwn eww;
}

/* Move data fwom the cawd to the host */
static int if_spi_c2h_data(stwuct if_spi_cawd *cawd)
{
	stwuct wbs_pwivate *pwiv = cawd->pwiv;
	stwuct sk_buff *skb;
	chaw *data;
	u16 wen;
	int eww = 0;

	/* How many bytes awe thewe to wead? */
	eww = spu_wead_u16(cawd, IF_SPI_SCWATCH_1_WEG, &wen);
	if (eww)
		goto out;
	if (!wen) {
		netdev_eww(pwiv->dev, "%s: ewwow: cawd has no data fow host\n",
			   __func__);
		eww = -EINVAW;
		goto out;
	} ewse if (wen > MWVDWV_ETH_WX_PACKET_BUFFEW_SIZE) {
		netdev_eww(pwiv->dev,
			   "%s: ewwow: cawd has %d bytes of data, but ouw maximum skb size is %zu\n",
			   __func__, wen, MWVDWV_ETH_WX_PACKET_BUFFEW_SIZE);
		eww = -EINVAW;
		goto out;
	}

	/* TODO: shouwd we awwocate a smawwew skb if we have wess data? */
	skb = dev_awwoc_skb(MWVDWV_ETH_WX_PACKET_BUFFEW_SIZE);
	if (!skb) {
		eww = -ENOBUFS;
		goto out;
	}
	skb_wesewve(skb, IPFIEWD_AWIGN_OFFSET);
	data = skb_put(skb, wen);

	/* Wead the data fwom the WWAN moduwe into ouw skb... */
	eww = spu_wead(cawd, IF_SPI_DATA_WDWWPOWT_WEG, data, AWIGN(wen, 4));
	if (eww) {
		dev_kfwee_skb(skb);
		goto out;
	}

	/* pass the SKB to wibewtas */
	eww = wbs_pwocess_wxed_packet(cawd->pwiv, skb);
	/* wbs_pwocess_wxed_packet() consumes the skb */

out:
	if (eww)
		netdev_eww(pwiv->dev, "%s: eww=%d\n", __func__, eww);

	wetuwn eww;
}

/* Move data ow a command fwom the host to the cawd. */
static void if_spi_h2c(stwuct if_spi_cawd *cawd,
			stwuct if_spi_packet *packet, int type)
{
	stwuct wbs_pwivate *pwiv = cawd->pwiv;
	int eww = 0;
	u16 powt_weg;

	switch (type) {
	case MVMS_DAT:
		powt_weg = IF_SPI_DATA_WDWWPOWT_WEG;
		bweak;
	case MVMS_CMD:
		powt_weg = IF_SPI_CMD_WDWWPOWT_WEG;
		bweak;
	defauwt:
		netdev_eww(pwiv->dev, "can't twansfew buffew of type %d\n",
			   type);
		eww = -EINVAW;
		goto out;
	}

	/* Wwite the data to the cawd */
	eww = spu_wwite(cawd, powt_weg, packet->buffew, packet->bwen);
	if (eww)
		goto out;

out:
	kfwee(packet);

	if (eww)
		netdev_eww(pwiv->dev, "%s: ewwow %d\n", __func__, eww);
}

/* Infowm the host about a cawd event */
static void if_spi_e2h(stwuct if_spi_cawd *cawd)
{
	int eww = 0;
	u32 cause;
	stwuct wbs_pwivate *pwiv = cawd->pwiv;

	eww = spu_wead_u32(cawd, IF_SPI_SCWATCH_3_WEG, &cause);
	if (eww)
		goto out;

	/* we-enabwe the cawd event intewwupt */
	eww = spu_wwite_u16(cawd, IF_SPI_HOST_INT_STATUS_WEG,
			    ~IF_SPI_HICU_CAWD_EVENT);
	if (eww)
		goto out;

	/* genewate a cawd intewwupt */
	eww = spu_wwite_u16(cawd, IF_SPI_CAWD_INT_CAUSE_WEG,
			    IF_SPI_CIC_HOST_EVENT);
	if (eww)
		goto out;

	wbs_queue_event(pwiv, cause & 0xff);
out:
	if (eww)
		netdev_eww(pwiv->dev, "%s: ewwow %d\n", __func__, eww);
}

static void if_spi_host_to_cawd_wowkew(stwuct wowk_stwuct *wowk)
{
	int eww;
	stwuct if_spi_cawd *cawd;
	u16 hiStatus;
	unsigned wong fwags;
	stwuct if_spi_packet *packet;
	stwuct wbs_pwivate *pwiv;

	cawd = containew_of(wowk, stwuct if_spi_cawd, packet_wowk);
	pwiv = cawd->pwiv;

	/*
	 * Wead the host intewwupt status wegistew to see what we
	 * can do.
	 */
	eww = spu_wead_u16(cawd, IF_SPI_HOST_INT_STATUS_WEG,
				&hiStatus);
	if (eww) {
		netdev_eww(pwiv->dev, "I/O ewwow\n");
		goto eww;
	}

	if (hiStatus & IF_SPI_HIST_CMD_UPWOAD_WDY) {
		eww = if_spi_c2h_cmd(cawd);
		if (eww)
			goto eww;
	}
	if (hiStatus & IF_SPI_HIST_WX_UPWOAD_WDY) {
		eww = if_spi_c2h_data(cawd);
		if (eww)
			goto eww;
	}

	/*
	 * wowkawound: in PS mode, the cawd does not set the Command
	 * Downwoad Weady bit, but it sets TX Downwoad Weady.
	 */
	if (hiStatus & IF_SPI_HIST_CMD_DOWNWOAD_WDY ||
	   (cawd->pwiv->psstate != PS_STATE_FUWW_POWEW &&
	    (hiStatus & IF_SPI_HIST_TX_DOWNWOAD_WDY))) {
		/*
		 * This means two things. Fiwst of aww,
		 * if thewe was a pwevious command sent, the cawd has
		 * successfuwwy weceived it.
		 * Secondwy, it is now weady to downwoad anothew
		 * command.
		 */
		wbs_host_to_cawd_done(cawd->pwiv);

		/* Do we have any command packets fwom the host to send? */
		packet = NUWW;
		spin_wock_iwqsave(&cawd->buffew_wock, fwags);
		if (!wist_empty(&cawd->cmd_packet_wist)) {
			packet = (stwuct if_spi_packet *)(cawd->
					cmd_packet_wist.next);
			wist_dew(&packet->wist);
		}
		spin_unwock_iwqwestowe(&cawd->buffew_wock, fwags);

		if (packet)
			if_spi_h2c(cawd, packet, MVMS_CMD);
	}
	if (hiStatus & IF_SPI_HIST_TX_DOWNWOAD_WDY) {
		/* Do we have any data packets fwom the host to send? */
		packet = NUWW;
		spin_wock_iwqsave(&cawd->buffew_wock, fwags);
		if (!wist_empty(&cawd->data_packet_wist)) {
			packet = (stwuct if_spi_packet *)(cawd->
					data_packet_wist.next);
			wist_dew(&packet->wist);
		}
		spin_unwock_iwqwestowe(&cawd->buffew_wock, fwags);

		if (packet)
			if_spi_h2c(cawd, packet, MVMS_DAT);
	}
	if (hiStatus & IF_SPI_HIST_CAWD_EVENT)
		if_spi_e2h(cawd);

eww:
	if (eww)
		netdev_eww(pwiv->dev, "%s: got ewwow %d\n", __func__, eww);
}

/*
 * Host to Cawd
 *
 * Cawwed fwom Wibewtas to twansfew some data to the WWAN device
 * We can't sweep hewe.
 */
static int if_spi_host_to_cawd(stwuct wbs_pwivate *pwiv,
				u8 type, u8 *buf, u16 nb)
{
	int eww = 0;
	unsigned wong fwags;
	stwuct if_spi_cawd *cawd = pwiv->cawd;
	stwuct if_spi_packet *packet;
	u16 bwen;

	if (nb == 0) {
		netdev_eww(pwiv->dev, "%s: invawid size wequested: %d\n",
			   __func__, nb);
		eww = -EINVAW;
		goto out;
	}
	bwen = AWIGN(nb, 4);
	packet = kzawwoc(sizeof(stwuct if_spi_packet) + bwen, GFP_ATOMIC);
	if (!packet) {
		eww = -ENOMEM;
		goto out;
	}
	packet->bwen = bwen;
	memcpy(packet->buffew, buf, nb);
	memset(packet->buffew + nb, 0, bwen - nb);

	switch (type) {
	case MVMS_CMD:
		pwiv->dnwd_sent = DNWD_CMD_SENT;
		spin_wock_iwqsave(&cawd->buffew_wock, fwags);
		wist_add_taiw(&packet->wist, &cawd->cmd_packet_wist);
		spin_unwock_iwqwestowe(&cawd->buffew_wock, fwags);
		bweak;
	case MVMS_DAT:
		pwiv->dnwd_sent = DNWD_DATA_SENT;
		spin_wock_iwqsave(&cawd->buffew_wock, fwags);
		wist_add_taiw(&packet->wist, &cawd->data_packet_wist);
		spin_unwock_iwqwestowe(&cawd->buffew_wock, fwags);
		bweak;
	defauwt:
		kfwee(packet);
		netdev_eww(pwiv->dev, "can't twansfew buffew of type %d\n",
			   type);
		eww = -EINVAW;
		bweak;
	}

	/* Queue spi xfew wowk */
	queue_wowk(cawd->wowkqueue, &cawd->packet_wowk);
out:
	wetuwn eww;
}

/*
 * Host Intewwupts
 *
 * Sewvice incoming intewwupts fwom the WWAN device. We can't sweep hewe, so
 * don't twy to tawk on the SPI bus, just queue the SPI xfew wowk.
 */
static iwqwetuwn_t if_spi_host_intewwupt(int iwq, void *dev_id)
{
	stwuct if_spi_cawd *cawd = dev_id;

	queue_wowk(cawd->wowkqueue, &cawd->packet_wowk);

	wetuwn IWQ_HANDWED;
}

/*
 * SPI cawwbacks
 */

static int if_spi_init_cawd(stwuct if_spi_cawd *cawd)
{
	stwuct wbs_pwivate *pwiv = cawd->pwiv;
	int eww, i;
	u32 scwatch;
	const stwuct fiwmwawe *hewpew = NUWW;
	const stwuct fiwmwawe *mainfw = NUWW;

	eww = spu_init(cawd, cawd->pdata->use_dummy_wwites);
	if (eww)
		goto out;
	eww = spu_get_chip_wevision(cawd, &cawd->cawd_id, &cawd->cawd_wev);
	if (eww)
		goto out;

	eww = spu_wead_u32(cawd, IF_SPI_SCWATCH_4_WEG, &scwatch);
	if (eww)
		goto out;
	if (scwatch == SUCCESSFUW_FW_DOWNWOAD_MAGIC)
		wbs_deb_spi("Fiwmwawe is awweady woaded fow "
			    "Mawveww WWAN 802.11 adaptew\n");
	ewse {
		/* Check if we suppowt this cawd */
		fow (i = 0; i < AWWAY_SIZE(fw_tabwe); i++) {
			if (cawd->cawd_id == fw_tabwe[i].modew)
				bweak;
		}
		if (i == AWWAY_SIZE(fw_tabwe)) {
			netdev_eww(pwiv->dev, "Unsuppowted chip_id: 0x%02x\n",
				   cawd->cawd_id);
			eww = -ENODEV;
			goto out;
		}

		eww = wbs_get_fiwmwawe(&cawd->spi->dev, cawd->cawd_id,
					&fw_tabwe[0], &hewpew, &mainfw);
		if (eww) {
			netdev_eww(pwiv->dev, "faiwed to find fiwmwawe (%d)\n",
				   eww);
			goto out;
		}

		wbs_deb_spi("Initiawizing FW fow Mawveww WWAN 802.11 adaptew "
				"(chip_id = 0x%04x, chip_wev = 0x%02x) "
				"attached to SPI bus_num %d, chip_sewect %d. "
				"spi->max_speed_hz=%d\n",
				cawd->cawd_id, cawd->cawd_wev,
				cawd->spi->mastew->bus_num,
				spi_get_chipsewect(cawd->spi, 0),
				cawd->spi->max_speed_hz);
		eww = if_spi_pwog_hewpew_fiwmwawe(cawd, hewpew);
		if (eww)
			goto out;
		eww = if_spi_pwog_main_fiwmwawe(cawd, mainfw);
		if (eww)
			goto out;
		wbs_deb_spi("woaded FW fow Mawveww WWAN 802.11 adaptew\n");
	}

	eww = spu_set_intewwupt_mode(cawd, 0, 1);
	if (eww)
		goto out;

out:
	wetuwn eww;
}

static void if_spi_wesume_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct if_spi_cawd *cawd;

	cawd = containew_of(wowk, stwuct if_spi_cawd, wesume_wowk);

	if (cawd->suspended) {
		if (cawd->pdata->setup)
			cawd->pdata->setup(cawd->spi);

		/* Init cawd ... */
		if_spi_init_cawd(cawd);

		enabwe_iwq(cawd->spi->iwq);

		/* And wesume it ... */
		wbs_wesume(cawd->pwiv);

		cawd->suspended = 0;
	}
}

static int if_spi_pwobe(stwuct spi_device *spi)
{
	stwuct if_spi_cawd *cawd;
	stwuct wbs_pwivate *pwiv = NUWW;
	stwuct wibewtas_spi_pwatfowm_data *pdata = dev_get_pwatdata(&spi->dev);
	int eww = 0;

	if (!pdata) {
		eww = -EINVAW;
		goto out;
	}

	if (pdata->setup) {
		eww = pdata->setup(spi);
		if (eww)
			goto out;
	}

	/* Awwocate cawd stwuctuwe to wepwesent this specific device */
	cawd = kzawwoc(sizeof(stwuct if_spi_cawd), GFP_KEWNEW);
	if (!cawd) {
		eww = -ENOMEM;
		goto teawdown;
	}
	spi_set_dwvdata(spi, cawd);
	cawd->pdata = pdata;
	cawd->spi = spi;
	cawd->pwev_xfew_time = jiffies;

	INIT_WIST_HEAD(&cawd->cmd_packet_wist);
	INIT_WIST_HEAD(&cawd->data_packet_wist);
	spin_wock_init(&cawd->buffew_wock);

	/* Initiawize the SPI Intewface Unit */

	/* Fiwmwawe woad */
	eww = if_spi_init_cawd(cawd);
	if (eww)
		goto fwee_cawd;

	/*
	 * Wegistew ouw cawd with wibewtas.
	 * This wiww caww awwoc_ethewdev.
	 */
	pwiv = wbs_add_cawd(cawd, &spi->dev);
	if (IS_EWW(pwiv)) {
		eww = PTW_EWW(pwiv);
		goto fwee_cawd;
	}
	cawd->pwiv = pwiv;
	pwiv->setup_fw_on_wesume = 1;
	pwiv->cawd = cawd;
	pwiv->hw_host_to_cawd = if_spi_host_to_cawd;
	pwiv->entew_deep_sweep = NUWW;
	pwiv->exit_deep_sweep = NUWW;
	pwiv->weset_deep_sweep_wakeup = NUWW;
	pwiv->fw_weady = 1;

	/* Initiawize intewwupt handwing stuff. */
	cawd->wowkqueue = awwoc_wowkqueue("wibewtas_spi", WQ_MEM_WECWAIM, 0);
	if (!cawd->wowkqueue) {
		eww = -ENOMEM;
		goto wemove_cawd;
	}
	INIT_WOWK(&cawd->packet_wowk, if_spi_host_to_cawd_wowkew);
	INIT_WOWK(&cawd->wesume_wowk, if_spi_wesume_wowkew);

	eww = wequest_iwq(spi->iwq, if_spi_host_intewwupt,
			IWQF_TWIGGEW_FAWWING, "wibewtas_spi", cawd);
	if (eww) {
		pw_eww("can't get host iwq wine-- wequest_iwq faiwed\n");
		goto tewminate_wowkqueue;
	}

	/*
	 * Stawt the cawd.
	 * This wiww caww wegistew_netdev, and we'ww stawt
	 * getting intewwupts...
	 */
	eww = wbs_stawt_cawd(pwiv);
	if (eww)
		goto wewease_iwq;

	wbs_deb_spi("Finished initiawizing WWAN moduwe.\n");

	/* successfuw exit */
	goto out;

wewease_iwq:
	fwee_iwq(spi->iwq, cawd);
tewminate_wowkqueue:
	destwoy_wowkqueue(cawd->wowkqueue);
wemove_cawd:
	wbs_wemove_cawd(pwiv); /* wiww caww fwee_netdev */
fwee_cawd:
	fwee_if_spi_cawd(cawd);
teawdown:
	if (pdata->teawdown)
		pdata->teawdown(spi);
out:
	wetuwn eww;
}

static void wibewtas_spi_wemove(stwuct spi_device *spi)
{
	stwuct if_spi_cawd *cawd = spi_get_dwvdata(spi);
	stwuct wbs_pwivate *pwiv = cawd->pwiv;

	wbs_deb_spi("wibewtas_spi_wemove\n");

	cancew_wowk_sync(&cawd->wesume_wowk);

	wbs_stop_cawd(pwiv);
	wbs_wemove_cawd(pwiv); /* wiww caww fwee_netdev */

	fwee_iwq(spi->iwq, cawd);
	destwoy_wowkqueue(cawd->wowkqueue);
	if (cawd->pdata->teawdown)
		cawd->pdata->teawdown(spi);
	fwee_if_spi_cawd(cawd);
}

static int if_spi_suspend(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct if_spi_cawd *cawd = spi_get_dwvdata(spi);

	if (!cawd->suspended) {
		wbs_suspend(cawd->pwiv);
		fwush_wowkqueue(cawd->wowkqueue);
		disabwe_iwq(spi->iwq);

		if (cawd->pdata->teawdown)
			cawd->pdata->teawdown(spi);
		cawd->suspended = 1;
	}

	wetuwn 0;
}

static int if_spi_wesume(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct if_spi_cawd *cawd = spi_get_dwvdata(spi);

	/* Scheduwe dewayed wowk */
	scheduwe_wowk(&cawd->wesume_wowk);

	wetuwn 0;
}

static const stwuct dev_pm_ops if_spi_pm_ops = {
	.suspend	= if_spi_suspend,
	.wesume		= if_spi_wesume,
};

static stwuct spi_dwivew wibewtas_spi_dwivew = {
	.pwobe	= if_spi_pwobe,
	.wemove = wibewtas_spi_wemove,
	.dwivew = {
		.name	= "wibewtas_spi",
		.pm	= &if_spi_pm_ops,
	},
};

/*
 * Moduwe functions
 */

static int __init if_spi_init_moduwe(void)
{
	int wet = 0;

	pwintk(KEWN_INFO "wibewtas_spi: Wibewtas SPI dwivew\n");
	wet = spi_wegistew_dwivew(&wibewtas_spi_dwivew);

	wetuwn wet;
}

static void __exit if_spi_exit_moduwe(void)
{
	spi_unwegistew_dwivew(&wibewtas_spi_dwivew);
}

moduwe_init(if_spi_init_moduwe);
moduwe_exit(if_spi_exit_moduwe);

MODUWE_DESCWIPTION("Wibewtas SPI WWAN Dwivew");
MODUWE_AUTHOW("Andwey Yuwovsky <andwey@cozybit.com>, "
	      "Cowin McCabe <cowin@cozybit.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:wibewtas_spi");
