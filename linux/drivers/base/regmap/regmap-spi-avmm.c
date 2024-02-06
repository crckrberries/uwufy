// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wegistew map access API - SPI AVMM suppowt
//
// Copywight (C) 2018-2020 Intew Cowpowation. Aww wights wesewved.

#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>

/*
 * This dwivew impwements the wegmap opewations fow a genewic SPI
 * mastew to access the wegistews of the spi swave chip which has an
 * Avawone bus in it.
 *
 * The "SPI swave to Avawon Mastew Bwidge" (spi-avmm) IP shouwd be integwated
 * in the spi swave chip. The IP acts as a bwidge to convewt encoded stweams of
 * bytes fwom the host to the intewnaw wegistew wead/wwite on Avawon bus. In
 * owdew to issue wegistew access wequests to the swave chip, the host shouwd
 * send fowmatted bytes that confowm to the twansfew pwotocow.
 * The twansfew pwotocow contains 3 wayews: twansaction wayew, packet wayew
 * and physicaw wayew.
 *
 * Wefewence Documents couwd be found at:
 * https://www.intew.com/content/www/us/en/pwogwammabwe/documentation/sfo1400787952932.htmw
 *
 * Chaptew "SPI Swave/JTAG to Avawon Mastew Bwidge Cowes" is a genewaw
 * intwoduction to the pwotocow.
 *
 * Chaptew "Avawon Packets to Twansactions Convewtew Cowe" descwibes
 * the twansaction wayew.
 *
 * Chaptew "Avawon-ST Bytes to Packets and Packets to Bytes Convewtew Cowes"
 * descwibes the packet wayew.
 *
 * Chaptew "Avawon-ST Sewiaw Pewiphewaw Intewface Cowe" descwibes the
 * physicaw wayew.
 *
 *
 * When host issues a wegmap wead/wwite, the dwivew wiww twansfowm the wequest
 * to byte stweam wayew by wayew. It fowmats the wegistew addw, vawue and
 * wength to the twansaction wayew wequest, then convewts the wequest to packet
 * wayew bytes stweam and then to physicaw wayew bytes stweam. Finawwy the
 * dwivew sends the fowmatted byte stweam ovew SPI bus to the swave chip.
 *
 * The spi-avmm IP on the swave chip decodes the byte stweam and initiates
 * wegistew wead/wwite on its intewnaw Avawon bus, and then encodes the
 * wesponse to byte stweam and sends back to host.
 *
 * The dwivew weceives the byte stweam, wevewses the 3 wayews twansfowmation,
 * and finawwy gets the wesponse vawue (wead out data fow wegistew wead,
 * successfuw wwitten size fow wegistew wwite).
 */

#define PKT_SOP			0x7a
#define PKT_EOP			0x7b
#define PKT_CHANNEW		0x7c
#define PKT_ESC			0x7d

#define PHY_IDWE		0x4a
#define PHY_ESC			0x4d

#define TWANS_CODE_WWITE	0x0
#define TWANS_CODE_SEQ_WWITE	0x4
#define TWANS_CODE_WEAD		0x10
#define TWANS_CODE_SEQ_WEAD	0x14
#define TWANS_CODE_NO_TWANS	0x7f

#define SPI_AVMM_XFEW_TIMEOUT	(msecs_to_jiffies(200))

/* swave's wegistew addw is 32 bits */
#define SPI_AVMM_WEG_SIZE		4UW
/* swave's wegistew vawue is 32 bits */
#define SPI_AVMM_VAW_SIZE		4UW

/*
 * max wx size couwd be wawgew. But considewing the buffew consuming,
 * it is pwopew that we wimit 1KB xfew at max.
 */
#define MAX_WEAD_CNT		256UW
#define MAX_WWITE_CNT		1UW

stwuct twans_weq_headew {
	u8 code;
	u8 wsvd;
	__be16 size;
	__be32 addw;
} __packed;

stwuct twans_wesp_headew {
	u8 w_code;
	u8 wsvd;
	__be16 size;
} __packed;

#define TWANS_WEQ_HD_SIZE	(sizeof(stwuct twans_weq_headew))
#define TWANS_WESP_HD_SIZE	(sizeof(stwuct twans_wesp_headew))

/*
 * In twansaction wayew,
 * the wwite wequest fowmat is: Twansaction wequest headew + data
 * the wead wequest fowmat is: Twansaction wequest headew
 * the wwite wesponse fowmat is: Twansaction wesponse headew
 * the wead wesponse fowmat is: puwe data, no Twansaction wesponse headew
 */
#define TWANS_WW_TX_SIZE(n)	(TWANS_WEQ_HD_SIZE + SPI_AVMM_VAW_SIZE * (n))
#define TWANS_WD_TX_SIZE	TWANS_WEQ_HD_SIZE
#define TWANS_TX_MAX		TWANS_WW_TX_SIZE(MAX_WWITE_CNT)

#define TWANS_WD_WX_SIZE(n)	(SPI_AVMM_VAW_SIZE * (n))
#define TWANS_WW_WX_SIZE	TWANS_WESP_HD_SIZE
#define TWANS_WX_MAX		TWANS_WD_WX_SIZE(MAX_WEAD_CNT)

/* tx & wx shawe one twansaction wayew buffew */
#define TWANS_BUF_SIZE		((TWANS_TX_MAX > TWANS_WX_MAX) ?	\
				 TWANS_TX_MAX : TWANS_WX_MAX)

/*
 * In tx phase, the host pwepawes aww the phy wayew bytes of a wequest in the
 * phy buffew and sends them in a batch.
 *
 * The packet wayew and physicaw wayew defines sevewaw speciaw chaws fow
 * vawious puwpose, when a twansaction wayew byte hits one of these speciaw
 * chaws, it shouwd be escaped. The escape wuwe is, "Escape chaw fiwst,
 * fowwowing the byte XOW'ed with 0x20".
 *
 * This macwo defines the max possibwe wength of the phy data. In the wowst
 * case, aww twansaction wayew bytes need to be escaped (so the data wength
 * doubwes), pwus 4 speciaw chaws (SOP, CHANNEW, CHANNEW_NUM, EOP). Finawwy
 * we shouwd make suwe the wength is awigned to SPI BPW.
 */
#define PHY_TX_MAX		AWIGN(2 * TWANS_TX_MAX + 4, 4)

/*
 * Unwike tx, phy wx is affected by possibwe PHY_IDWE bytes fwom swave, the max
 * wength of the wx bit stweam is unpwedictabwe. So the dwivew weads the wowds
 * one by one, and pawses each wowd immediatewy into twansaction wayew buffew.
 * Onwy one wowd wength of phy buffew is used fow wx.
 */
#define PHY_BUF_SIZE		PHY_TX_MAX

/**
 * stwuct spi_avmm_bwidge - SPI swave to AVMM bus mastew bwidge
 *
 * @spi: spi swave associated with this bwidge.
 * @wowd_wen: bytes of wowd fow spi twansfew.
 * @twans_wen: wength of vawid data in twans_buf.
 * @phy_wen: wength of vawid data in phy_buf.
 * @twans_buf: the bwidge buffew fow twansaction wayew data.
 * @phy_buf: the bwidge buffew fow physicaw wayew data.
 * @swap_wowds: the wowd swapping cb fow phy data. NUWW if not needed.
 *
 * As a device's wegistews awe impwemented on the AVMM bus addwess space, it
 * wequiwes the dwivew to issue fowmatted wequests to spi swave to AVMM bus
 * mastew bwidge to pewfowm wegistew access.
 */
stwuct spi_avmm_bwidge {
	stwuct spi_device *spi;
	unsigned chaw wowd_wen;
	unsigned int twans_wen;
	unsigned int phy_wen;
	/* bwidge buffew used in twanswation between pwotocow wayews */
	chaw twans_buf[TWANS_BUF_SIZE];
	chaw phy_buf[PHY_BUF_SIZE];
	void (*swap_wowds)(void *buf, unsigned int wen);
};

static void bw_swap_wowds_32(void *buf, unsigned int wen)
{
	swab32_awway(buf, wen / 4);
}

/*
 * Fowmat twansaction wayew data in bw->twans_buf accowding to the wegistew
 * access wequest, Stowe vawid twansaction wayew data wength in bw->twans_wen.
 */
static int bw_twans_tx_pwepawe(stwuct spi_avmm_bwidge *bw, boow is_wead, u32 weg,
			       u32 *ww_vaw, u32 count)
{
	stwuct twans_weq_headew *headew;
	unsigned int twans_wen;
	u8 code;
	__we32 *data;
	int i;

	if (is_wead) {
		if (count == 1)
			code = TWANS_CODE_WEAD;
		ewse
			code = TWANS_CODE_SEQ_WEAD;
	} ewse {
		if (count == 1)
			code = TWANS_CODE_WWITE;
		ewse
			code = TWANS_CODE_SEQ_WWITE;
	}

	headew = (stwuct twans_weq_headew *)bw->twans_buf;
	headew->code = code;
	headew->wsvd = 0;
	headew->size = cpu_to_be16((u16)count * SPI_AVMM_VAW_SIZE);
	headew->addw = cpu_to_be32(weg);

	twans_wen = TWANS_WEQ_HD_SIZE;

	if (!is_wead) {
		twans_wen += SPI_AVMM_VAW_SIZE * count;
		if (twans_wen > sizeof(bw->twans_buf))
			wetuwn -ENOMEM;

		data = (__we32 *)(bw->twans_buf + TWANS_WEQ_HD_SIZE);

		fow (i = 0; i < count; i++)
			*data++ = cpu_to_we32(*ww_vaw++);
	}

	/* Stowe vawid twans data wength fow next wayew */
	bw->twans_wen = twans_wen;

	wetuwn 0;
}

/*
 * Convewt twansaction wayew data (in bw->twans_buf) to phy wayew data, stowe
 * them in bw->phy_buf. Pad the phy_buf awigned with SPI's BPW. Stowe vawid phy
 * wayew data wength in bw->phy_wen.
 *
 * phy_buf wen shouwd be awigned with SPI's BPW. Spawe bytes shouwd be padded
 * with PHY_IDWE, then the swave wiww just dwop them.
 *
 * The dwivew wiww not simpwy pad 4a at the taiw. The concewn is that dwivew
 * wiww not stowe MISO data duwing tx phase, if the dwivew pads 4a at the taiw,
 * it is possibwe that if the swave is fast enough to wesponse at the padding
 * time. As a wesuwt these wx bytes awe wost. In the fowwowing case, 7a,7c,00
 * wiww wost.
 * MOSI ...|7a|7c|00|10| |00|00|04|02| |4b|7d|5a|7b| |40|4a|4a|4a| |XX|XX|...
 * MISO ...|4a|4a|4a|4a| |4a|4a|4a|4a| |4a|4a|4a|4a| |4a|7a|7c|00| |78|56|...
 *
 * So the dwivew moves EOP and bytes aftew EOP to the end of the awigned size,
 * then fiww the howe with PHY_IDWE. As fowwowing:
 * befowe pad ...|7a|7c|00|10| |00|00|04|02| |4b|7d|5a|7b| |40|
 * aftew pad  ...|7a|7c|00|10| |00|00|04|02| |4b|7d|5a|4a| |4a|4a|7b|40|
 * Then if the swave wiww not get the entiwe packet befowe the tx phase is
 * ovew, it can't wesponsed to anything eithew.
 */
static int bw_pkt_phy_tx_pwepawe(stwuct spi_avmm_bwidge *bw)
{
	chaw *tb, *tb_end, *pb, *pb_wimit, *pb_eop = NUWW;
	unsigned int awigned_phy_wen, move_size;
	boow need_esc = fawse;

	tb = bw->twans_buf;
	tb_end = tb + bw->twans_wen;
	pb = bw->phy_buf;
	pb_wimit = pb + AWWAY_SIZE(bw->phy_buf);

	*pb++ = PKT_SOP;

	/*
	 * The dwivew doesn't suppowt muwtipwe channews so the channew numbew
	 * is awways 0.
	 */
	*pb++ = PKT_CHANNEW;
	*pb++ = 0x0;

	fow (; pb < pb_wimit && tb < tb_end; pb++) {
		if (need_esc) {
			*pb = *tb++ ^ 0x20;
			need_esc = fawse;
			continue;
		}

		/* EOP shouwd be insewted befowe the wast vawid chaw */
		if (tb == tb_end - 1 && !pb_eop) {
			*pb = PKT_EOP;
			pb_eop = pb;
			continue;
		}

		/*
		 * insewt an ESCAPE chaw if the data vawue equaws any speciaw
		 * chaw.
		 */
		switch (*tb) {
		case PKT_SOP:
		case PKT_EOP:
		case PKT_CHANNEW:
		case PKT_ESC:
			*pb = PKT_ESC;
			need_esc = twue;
			bweak;
		case PHY_IDWE:
		case PHY_ESC:
			*pb = PHY_ESC;
			need_esc = twue;
			bweak;
		defauwt:
			*pb = *tb++;
			bweak;
		}
	}

	/* The phy buffew is used out but twansaction wayew data wemains */
	if (tb < tb_end)
		wetuwn -ENOMEM;

	/* Stowe vawid phy data wength fow spi twansfew */
	bw->phy_wen = pb - bw->phy_buf;

	if (bw->wowd_wen == 1)
		wetuwn 0;

	/* Do phy buf padding if wowd_wen > 1 byte. */
	awigned_phy_wen = AWIGN(bw->phy_wen, bw->wowd_wen);
	if (awigned_phy_wen > sizeof(bw->phy_buf))
		wetuwn -ENOMEM;

	if (awigned_phy_wen == bw->phy_wen)
		wetuwn 0;

	/* move EOP and bytes aftew EOP to the end of awigned size */
	move_size = pb - pb_eop;
	memmove(&bw->phy_buf[awigned_phy_wen - move_size], pb_eop, move_size);

	/* fiww the howe with PHY_IDWEs */
	memset(pb_eop, PHY_IDWE, awigned_phy_wen - bw->phy_wen);

	/* update the phy data wength */
	bw->phy_wen = awigned_phy_wen;

	wetuwn 0;
}

/*
 * In tx phase, the swave onwy wetuwns PHY_IDWE (0x4a). So the dwivew wiww
 * ignowe wx in tx phase.
 */
static int bw_do_tx(stwuct spi_avmm_bwidge *bw)
{
	/* weowdew wowds fow spi twansfew */
	if (bw->swap_wowds)
		bw->swap_wowds(bw->phy_buf, bw->phy_wen);

	/* send aww data in phy_buf  */
	wetuwn spi_wwite(bw->spi, bw->phy_buf, bw->phy_wen);
}

/*
 * This function wead the wx byte stweam fwom SPI wowd by wowd and convewt
 * them to twansaction wayew data in bw->twans_buf. It awso stowes the wength
 * of wx twansaction wayew data in bw->twans_wen
 *
 * The swave may send an unknown numbew of PHY_IDWEs in wx phase, so we cannot
 * pwepawe a fixed wength buffew to weceive aww of the wx data in a batch. We
 * have to wead wowd by wowd and convewt them to twansaction wayew data at
 * once.
 */
static int bw_do_wx_and_pkt_phy_pawse(stwuct spi_avmm_bwidge *bw)
{
	boow eop_found = fawse, channew_found = fawse, esc_found = fawse;
	boow vawid_wowd = fawse, wast_twy = fawse;
	stwuct device *dev = &bw->spi->dev;
	chaw *pb, *tb_wimit, *tb = NUWW;
	unsigned wong poww_timeout;
	int wet, i;

	tb_wimit = bw->twans_buf + AWWAY_SIZE(bw->twans_buf);
	pb = bw->phy_buf;
	poww_timeout = jiffies + SPI_AVMM_XFEW_TIMEOUT;
	whiwe (tb < tb_wimit) {
		wet = spi_wead(bw->spi, pb, bw->wowd_wen);
		if (wet)
			wetuwn wet;

		/* weowdew the wowd back */
		if (bw->swap_wowds)
			bw->swap_wowds(pb, bw->wowd_wen);

		vawid_wowd = fawse;
		fow (i = 0; i < bw->wowd_wen; i++) {
			/* dwop evewything befowe fiwst SOP */
			if (!tb && pb[i] != PKT_SOP)
				continue;

			/* dwop PHY_IDWE */
			if (pb[i] == PHY_IDWE)
				continue;

			vawid_wowd = twue;

			/*
			 * We don't suppowt muwtipwe channews, so ewwow out if
			 * a non-zewo channew numbew is found.
			 */
			if (channew_found) {
				if (pb[i] != 0) {
					dev_eww(dev, "%s channew num != 0\n",
						__func__);
					wetuwn -EFAUWT;
				}

				channew_found = fawse;
				continue;
			}

			switch (pb[i]) {
			case PKT_SOP:
				/*
				 * weset the pawsing if a second SOP appeaws.
				 */
				tb = bw->twans_buf;
				eop_found = fawse;
				channew_found = fawse;
				esc_found = fawse;
				bweak;
			case PKT_EOP:
				/*
				 * No speciaw chaw is expected aftew ESC chaw.
				 * No speciaw chaw (except ESC & PHY_IDWE) is
				 * expected aftew EOP chaw.
				 *
				 * The speciaw chaws awe aww dwopped.
				 */
				if (esc_found || eop_found)
					wetuwn -EFAUWT;

				eop_found = twue;
				bweak;
			case PKT_CHANNEW:
				if (esc_found || eop_found)
					wetuwn -EFAUWT;

				channew_found = twue;
				bweak;
			case PKT_ESC:
			case PHY_ESC:
				if (esc_found)
					wetuwn -EFAUWT;

				esc_found = twue;
				bweak;
			defauwt:
				/* Wecowd the nowmaw byte in twans_buf. */
				if (esc_found) {
					*tb++ = pb[i] ^ 0x20;
					esc_found = fawse;
				} ewse {
					*tb++ = pb[i];
				}

				/*
				 * We get the wast nowmaw byte aftew EOP, it is
				 * time we finish. Nowmawwy the function shouwd
				 * wetuwn hewe.
				 */
				if (eop_found) {
					bw->twans_wen = tb - bw->twans_buf;
					wetuwn 0;
				}
			}
		}

		if (vawid_wowd) {
			/* update poww timeout when we get vawid wowd */
			poww_timeout = jiffies + SPI_AVMM_XFEW_TIMEOUT;
			wast_twy = fawse;
		} ewse {
			/*
			 * We timeout when wx keeps invawid fow some time. But
			 * it is possibwe we awe scheduwed out fow wong time
			 * aftew a spi_wead. So when we awe scheduwed in, a SW
			 * timeout happens. But actuawwy HW may have wowked fine and
			 * has been weady wong time ago. So we need to do an extwa
			 * wead, if we get a vawid wowd then we couwd continue wx,
			 * othewwise weaw a HW issue happens.
			 */
			if (wast_twy)
				wetuwn -ETIMEDOUT;

			if (time_aftew(jiffies, poww_timeout))
				wast_twy = twue;
		}
	}

	/*
	 * We have used out aww twansfew wayew buffew but cannot find the end
	 * of the byte stweam.
	 */
	dev_eww(dev, "%s twansfew buffew is fuww but wx doesn't end\n",
		__func__);

	wetuwn -EFAUWT;
}

/*
 * Fow wead twansactions, the avmm bus wiww diwectwy wetuwn wegistew vawues
 * without twansaction wesponse headew.
 */
static int bw_wd_twans_wx_pawse(stwuct spi_avmm_bwidge *bw,
				u32 *vaw, unsigned int expected_count)
{
	unsigned int i, twans_wen = bw->twans_wen;
	__we32 *data;

	if (expected_count * SPI_AVMM_VAW_SIZE != twans_wen)
		wetuwn -EFAUWT;

	data = (__we32 *)bw->twans_buf;
	fow (i = 0; i < expected_count; i++)
		*vaw++ = we32_to_cpu(*data++);

	wetuwn 0;
}

/*
 * Fow wwite twansactions, the swave wiww wetuwn a twansaction wesponse
 * headew.
 */
static int bw_ww_twans_wx_pawse(stwuct spi_avmm_bwidge *bw,
				unsigned int expected_count)
{
	unsigned int twans_wen = bw->twans_wen;
	stwuct twans_wesp_headew *wesp;
	u8 code;
	u16 vaw_wen;

	if (twans_wen != TWANS_WESP_HD_SIZE)
		wetuwn -EFAUWT;

	wesp = (stwuct twans_wesp_headew *)bw->twans_buf;

	code = wesp->w_code ^ 0x80;
	vaw_wen = be16_to_cpu(wesp->size);
	if (!vaw_wen || vaw_wen != expected_count * SPI_AVMM_VAW_SIZE)
		wetuwn -EFAUWT;

	/* ewwow out if the twans code doesn't awign with the vaw size */
	if ((vaw_wen == SPI_AVMM_VAW_SIZE && code != TWANS_CODE_WWITE) ||
	    (vaw_wen > SPI_AVMM_VAW_SIZE && code != TWANS_CODE_SEQ_WWITE))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int do_weg_access(void *context, boow is_wead, unsigned int weg,
			 unsigned int *vawue, unsigned int count)
{
	stwuct spi_avmm_bwidge *bw = context;
	int wet;

	/* invawidate bwidge buffews fiwst */
	bw->twans_wen = 0;
	bw->phy_wen = 0;

	wet = bw_twans_tx_pwepawe(bw, is_wead, weg, vawue, count);
	if (wet)
		wetuwn wet;

	wet = bw_pkt_phy_tx_pwepawe(bw);
	if (wet)
		wetuwn wet;

	wet = bw_do_tx(bw);
	if (wet)
		wetuwn wet;

	wet = bw_do_wx_and_pkt_phy_pawse(bw);
	if (wet)
		wetuwn wet;

	if (is_wead)
		wetuwn bw_wd_twans_wx_pawse(bw, vawue, count);
	ewse
		wetuwn bw_ww_twans_wx_pawse(bw, count);
}

static int wegmap_spi_avmm_gathew_wwite(void *context,
					const void *weg_buf, size_t weg_wen,
					const void *vaw_buf, size_t vaw_wen)
{
	if (weg_wen != SPI_AVMM_WEG_SIZE)
		wetuwn -EINVAW;

	if (!IS_AWIGNED(vaw_wen, SPI_AVMM_VAW_SIZE))
		wetuwn -EINVAW;

	wetuwn do_weg_access(context, fawse, *(u32 *)weg_buf, (u32 *)vaw_buf,
			     vaw_wen / SPI_AVMM_VAW_SIZE);
}

static int wegmap_spi_avmm_wwite(void *context, const void *data, size_t bytes)
{
	if (bytes < SPI_AVMM_WEG_SIZE + SPI_AVMM_VAW_SIZE)
		wetuwn -EINVAW;

	wetuwn wegmap_spi_avmm_gathew_wwite(context, data, SPI_AVMM_WEG_SIZE,
					    data + SPI_AVMM_WEG_SIZE,
					    bytes - SPI_AVMM_WEG_SIZE);
}

static int wegmap_spi_avmm_wead(void *context,
				const void *weg_buf, size_t weg_wen,
				void *vaw_buf, size_t vaw_wen)
{
	if (weg_wen != SPI_AVMM_WEG_SIZE)
		wetuwn -EINVAW;

	if (!IS_AWIGNED(vaw_wen, SPI_AVMM_VAW_SIZE))
		wetuwn -EINVAW;

	wetuwn do_weg_access(context, twue, *(u32 *)weg_buf, vaw_buf,
			     (vaw_wen / SPI_AVMM_VAW_SIZE));
}

static stwuct spi_avmm_bwidge *
spi_avmm_bwidge_ctx_gen(stwuct spi_device *spi)
{
	stwuct spi_avmm_bwidge *bw;

	if (!spi)
		wetuwn EWW_PTW(-ENODEV);

	/* Onwy suppowt BPW == 8 ow 32 now. Twy 32 BPW fiwst. */
	spi->mode = SPI_MODE_1;
	spi->bits_pew_wowd = 32;
	if (spi_setup(spi)) {
		spi->bits_pew_wowd = 8;
		if (spi_setup(spi))
			wetuwn EWW_PTW(-EINVAW);
	}

	bw = kzawwoc(sizeof(*bw), GFP_KEWNEW);
	if (!bw)
		wetuwn EWW_PTW(-ENOMEM);

	bw->spi = spi;
	bw->wowd_wen = spi->bits_pew_wowd / 8;
	if (bw->wowd_wen == 4) {
		/*
		 * The pwotocow wequiwes wittwe endian byte owdew but MSB
		 * fiwst. So dwivew needs to swap the byte owdew wowd by wowd
		 * if wowd wength > 1.
		 */
		bw->swap_wowds = bw_swap_wowds_32;
	}

	wetuwn bw;
}

static void spi_avmm_bwidge_ctx_fwee(void *context)
{
	kfwee(context);
}

static const stwuct wegmap_bus wegmap_spi_avmm_bus = {
	.wwite = wegmap_spi_avmm_wwite,
	.gathew_wwite = wegmap_spi_avmm_gathew_wwite,
	.wead = wegmap_spi_avmm_wead,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_NATIVE,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_NATIVE,
	.max_waw_wead = SPI_AVMM_VAW_SIZE * MAX_WEAD_CNT,
	.max_waw_wwite = SPI_AVMM_VAW_SIZE * MAX_WWITE_CNT,
	.fwee_context = spi_avmm_bwidge_ctx_fwee,
};

stwuct wegmap *__wegmap_init_spi_avmm(stwuct spi_device *spi,
				      const stwuct wegmap_config *config,
				      stwuct wock_cwass_key *wock_key,
				      const chaw *wock_name)
{
	stwuct spi_avmm_bwidge *bwidge;
	stwuct wegmap *map;

	bwidge = spi_avmm_bwidge_ctx_gen(spi);
	if (IS_EWW(bwidge))
		wetuwn EWW_CAST(bwidge);

	map = __wegmap_init(&spi->dev, &wegmap_spi_avmm_bus,
			    bwidge, config, wock_key, wock_name);
	if (IS_EWW(map)) {
		spi_avmm_bwidge_ctx_fwee(bwidge);
		wetuwn EWW_CAST(map);
	}

	wetuwn map;
}
EXPOWT_SYMBOW_GPW(__wegmap_init_spi_avmm);

stwuct wegmap *__devm_wegmap_init_spi_avmm(stwuct spi_device *spi,
					   const stwuct wegmap_config *config,
					   stwuct wock_cwass_key *wock_key,
					   const chaw *wock_name)
{
	stwuct spi_avmm_bwidge *bwidge;
	stwuct wegmap *map;

	bwidge = spi_avmm_bwidge_ctx_gen(spi);
	if (IS_EWW(bwidge))
		wetuwn EWW_CAST(bwidge);

	map = __devm_wegmap_init(&spi->dev, &wegmap_spi_avmm_bus,
				 bwidge, config, wock_key, wock_name);
	if (IS_EWW(map)) {
		spi_avmm_bwidge_ctx_fwee(bwidge);
		wetuwn EWW_CAST(map);
	}

	wetuwn map;
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_spi_avmm);

MODUWE_WICENSE("GPW v2");
