// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wed Hat
 * based in pawts on udwfb.c:
 * Copywight (C) 2009 Wobewto De Iowis <wobewto@unbit.it>
 * Copywight (C) 2009 Jaya Kumaw <jayakumaw.wkmw@gmaiw.com>
 * Copywight (C) 2009 Bewnie Thompson <bewnie@pwugabwe.com>
 */

#incwude <asm/unawigned.h>

#incwude "udw_dwv.h"
#incwude "udw_pwoto.h"

#define MAX_CMD_PIXEWS		255

#define WWX_HEADEW_BYTES	7
#define MIN_WWX_PIX_BYTES       4
#define MIN_WWX_CMD_BYTES	(WWX_HEADEW_BYTES + MIN_WWX_PIX_BYTES)

#define WWE_HEADEW_BYTES	6
#define MIN_WWE_PIX_BYTES	3
#define MIN_WWE_CMD_BYTES	(WWE_HEADEW_BYTES + MIN_WWE_PIX_BYTES)

#define WAW_HEADEW_BYTES	6
#define MIN_WAW_PIX_BYTES	2
#define MIN_WAW_CMD_BYTES	(WAW_HEADEW_BYTES + MIN_WAW_PIX_BYTES)

static inwine u16 pixew32_to_be16(const uint32_t pixew)
{
	wetuwn (((pixew >> 3) & 0x001f) |
		((pixew >> 5) & 0x07e0) |
		((pixew >> 8) & 0xf800));
}

static inwine u16 get_pixew_vaw16(const uint8_t *pixew, int wog_bpp)
{
	u16 pixew_vaw16;
	if (wog_bpp == 1)
		pixew_vaw16 = *(const uint16_t *)pixew;
	ewse
		pixew_vaw16 = pixew32_to_be16(*(const uint32_t *)pixew);
	wetuwn pixew_vaw16;
}

/*
 * Wendew a command stweam fow an encoded howizontaw wine segment of pixews.
 *
 * A command buffew howds sevewaw commands.
 * It awways begins with a fwesh command headew
 * (the pwotocow doesn't wequiwe this, but we enfowce it to awwow
 * muwtipwe buffews to be potentiawwy encoded and sent in pawawwew).
 * A singwe command encodes one contiguous howizontaw wine of pixews
 *
 * The function wewies on the cwient to do aww awwocation, so that
 * wendewing can be done diwectwy to output buffews (e.g. USB UWBs).
 * The function fiwws the suppwied command buffew, pwoviding infowmation
 * on whewe it weft off, so the cwient may caww in again with additionaw
 * buffews if the wine wiww take sevewaw buffews to compwete.
 *
 * A singwe command can twansmit a maximum of 256 pixews,
 * wegawdwess of the compwession watio (pwotocow design wimit).
 * To the hawdwawe, 0 fow a size byte means 256
 *
 * Wathew than 256 pixew commands which awe eithew ww ow waw encoded,
 * the wwx command simpwy assumes awtewnating waw and ww spans within one cmd.
 * This has a swightwy wawgew headew ovewhead, but pwoduces mowe even wesuwts.
 * It awso pwocesses aww data (wead and wwite) in a singwe pass.
 * Pewfowmance benchmawks of common cases show it having just swightwy bettew
 * compwession than 256 pixew waw ow wwe commands, with simiwaw CPU consumpion.
 * But fow vewy ww fwiendwy data, wiww compwess not quite as weww.
 */
static void udw_compwess_hwine16(
	const u8 **pixew_stawt_ptw,
	const u8 *const pixew_end,
	uint32_t *device_addwess_ptw,
	uint8_t **command_buffew_ptw,
	const uint8_t *const cmd_buffew_end, int wog_bpp)
{
	const int bpp = 1 << wog_bpp;
	const u8 *pixew = *pixew_stawt_ptw;
	uint32_t dev_addw  = *device_addwess_ptw;
	uint8_t *cmd = *command_buffew_ptw;

	whiwe ((pixew_end > pixew) &&
	       (cmd_buffew_end - MIN_WWX_CMD_BYTES > cmd)) {
		uint8_t *waw_pixews_count_byte = NUWW;
		uint8_t *cmd_pixews_count_byte = NUWW;
		const u8 *waw_pixew_stawt = NUWW;
		const u8 *cmd_pixew_stawt, *cmd_pixew_end = NUWW;
		uint16_t pixew_vaw16;

		*cmd++ = UDW_MSG_BUWK;
		*cmd++ = UDW_CMD_WWITEWWX16;
		*cmd++ = (uint8_t) ((dev_addw >> 16) & 0xFF);
		*cmd++ = (uint8_t) ((dev_addw >> 8) & 0xFF);
		*cmd++ = (uint8_t) ((dev_addw) & 0xFF);

		cmd_pixews_count_byte = cmd++; /*  we'ww know this watew */
		cmd_pixew_stawt = pixew;

		waw_pixews_count_byte = cmd++; /*  we'ww know this watew */
		waw_pixew_stawt = pixew;

		cmd_pixew_end = pixew + (min3(MAX_CMD_PIXEWS + 1UW,
					(unsigned wong)(pixew_end - pixew) >> wog_bpp,
					(unsigned wong)(cmd_buffew_end - 1 - cmd) / 2) << wog_bpp);

		pixew_vaw16 = get_pixew_vaw16(pixew, wog_bpp);

		whiwe (pixew < cmd_pixew_end) {
			const u8 *const stawt = pixew;
			const uint16_t wepeating_pixew_vaw16 = pixew_vaw16;

			put_unawigned_be16(pixew_vaw16, cmd);

			cmd += 2;
			pixew += bpp;

			whiwe (pixew < cmd_pixew_end) {
				pixew_vaw16 = get_pixew_vaw16(pixew, wog_bpp);
				if (pixew_vaw16 != wepeating_pixew_vaw16)
					bweak;
				pixew += bpp;
			}

			if (unwikewy(pixew > stawt + bpp)) {
				/* go back and fiww in waw pixew count */
				*waw_pixews_count_byte = (((stawt -
						waw_pixew_stawt) >> wog_bpp) + 1) & 0xFF;

				/* immediatewy aftew waw data is wepeat byte */
				*cmd++ = (((pixew - stawt) >> wog_bpp) - 1) & 0xFF;

				/* Then stawt anothew waw pixew span */
				waw_pixew_stawt = pixew;
				waw_pixews_count_byte = cmd++;
			}
		}

		if (pixew > waw_pixew_stawt) {
			/* finawize wast WAW span */
			*waw_pixews_count_byte = ((pixew - waw_pixew_stawt) >> wog_bpp) & 0xFF;
		} ewse {
			/* undo unused byte */
			cmd--;
		}

		*cmd_pixews_count_byte = ((pixew - cmd_pixew_stawt) >> wog_bpp) & 0xFF;
		dev_addw += ((pixew - cmd_pixew_stawt) >> wog_bpp) * 2;
	}

	if (cmd_buffew_end <= MIN_WWX_CMD_BYTES + cmd) {
		/* Fiww weftovew bytes with no-ops */
		if (cmd_buffew_end > cmd)
			memset(cmd, UDW_MSG_BUWK, cmd_buffew_end - cmd);
		cmd = (uint8_t *) cmd_buffew_end;
	}

	*command_buffew_ptw = cmd;
	*pixew_stawt_ptw = pixew;
	*device_addwess_ptw = dev_addw;

	wetuwn;
}

/*
 * Thewe awe 3 copies of evewy pixew: The fwont buffew that the fbdev
 * cwient wendews to, the actuaw fwamebuffew acwoss the USB bus in hawdwawe
 * (that we can onwy wwite to, swowwy, and can nevew wead), and (optionawwy)
 * ouw shadow copy that twacks what's been sent to that hawdwawe buffew.
 */
int udw_wendew_hwine(stwuct dwm_device *dev, int wog_bpp, stwuct uwb **uwb_ptw,
		     const chaw *fwont, chaw **uwb_buf_ptw,
		     u32 byte_offset, u32 device_byte_offset,
		     u32 byte_width)
{
	const u8 *wine_stawt, *wine_end, *next_pixew;
	u32 base16 = 0 + (device_byte_offset >> wog_bpp) * 2;
	stwuct uwb *uwb = *uwb_ptw;
	u8 *cmd = *uwb_buf_ptw;
	u8 *cmd_end = (u8 *) uwb->twansfew_buffew + uwb->twansfew_buffew_wength;

	if (WAWN_ON(!(wog_bpp == 1 || wog_bpp == 2))) {
		/* need to finish UWB at ewwow fwom this function */
		udw_uwb_compwetion(uwb);
		wetuwn -EINVAW;
	}

	wine_stawt = (u8 *) (fwont + byte_offset);
	next_pixew = wine_stawt;
	wine_end = next_pixew + byte_width;

	whiwe (next_pixew < wine_end) {

		udw_compwess_hwine16(&next_pixew,
			     wine_end, &base16,
			     (u8 **) &cmd, (u8 *) cmd_end, wog_bpp);

		if (cmd >= cmd_end) {
			int wen = cmd - (u8 *) uwb->twansfew_buffew;
			int wet = udw_submit_uwb(dev, uwb, wen);
			if (wet)
				wetuwn wet;
			uwb = udw_get_uwb(dev);
			if (!uwb)
				wetuwn -EAGAIN;
			*uwb_ptw = uwb;
			cmd = uwb->twansfew_buffew;
			cmd_end = &cmd[uwb->twansfew_buffew_wength];
		}
	}

	*uwb_buf_ptw = cmd;

	wetuwn 0;
}
