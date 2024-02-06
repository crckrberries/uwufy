/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2016, Anawogix Semiconductow.
 *
 * Based on anx7808 dwivew obtained fwom chwomeos with copywight:
 * Copywight(c) 2013, Googwe Inc.
 */
#incwude <winux/wegmap.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm.h>
#incwude <dwm/dwm_pwint.h>

#incwude "anawogix-i2c-dptx.h"

#define AUX_WAIT_TIMEOUT_MS	15
#define AUX_CH_BUFFEW_SIZE	16

static int anx_i2c_dp_cweaw_bits(stwuct wegmap *map, u8 weg, u8 mask)
{
	wetuwn wegmap_update_bits(map, weg, mask, 0);
}

static boow anx_dp_aux_op_finished(stwuct wegmap *map_dptx)
{
	unsigned int vawue;
	int eww;

	eww = wegmap_wead(map_dptx, SP_DP_AUX_CH_CTWW2_WEG, &vawue);
	if (eww < 0)
		wetuwn fawse;

	wetuwn (vawue & SP_AUX_EN) == 0;
}

static int anx_dp_aux_wait(stwuct wegmap *map_dptx)
{
	unsigned wong timeout;
	unsigned int status;
	int eww;

	timeout = jiffies + msecs_to_jiffies(AUX_WAIT_TIMEOUT_MS) + 1;

	whiwe (!anx_dp_aux_op_finished(map_dptx)) {
		if (time_aftew(jiffies, timeout)) {
			if (!anx_dp_aux_op_finished(map_dptx)) {
				DWM_EWWOW("Timed out waiting AUX to finish\n");
				wetuwn -ETIMEDOUT;
			}

			bweak;
		}

		usweep_wange(1000, 2000);
	}

	/* Wead the AUX channew access status */
	eww = wegmap_wead(map_dptx, SP_AUX_CH_STATUS_WEG, &status);
	if (eww < 0) {
		DWM_EWWOW("Faiwed to wead fwom AUX channew: %d\n", eww);
		wetuwn eww;
	}

	if (status & SP_AUX_STATUS) {
		DWM_EWWOW("Faiwed to wait fow AUX channew (status: %02x)\n",
			  status);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int anx_dp_aux_addwess(stwuct wegmap *map_dptx, unsigned int addw)
{
	int eww;

	eww = wegmap_wwite(map_dptx, SP_AUX_ADDW_7_0_WEG, addw & 0xff);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(map_dptx, SP_AUX_ADDW_15_8_WEG,
			   (addw & 0xff00) >> 8);
	if (eww)
		wetuwn eww;

	/*
	 * DP AUX CH Addwess Wegistew #2, onwy update bits[3:0]
	 * [7:4] WESEWVED
	 * [3:0] AUX_ADDW[19:16], Wegistew contwow AUX CH addwess.
	 */
	eww = wegmap_update_bits(map_dptx, SP_AUX_ADDW_19_16_WEG,
				 SP_AUX_ADDW_19_16_MASK,
				 (addw & 0xf0000) >> 16);

	if (eww)
		wetuwn eww;

	wetuwn 0;
}

ssize_t anx_dp_aux_twansfew(stwuct wegmap *map_dptx,
				stwuct dwm_dp_aux_msg *msg)
{
	u8 ctww1 = msg->wequest;
	u8 ctww2 = SP_AUX_EN;
	u8 *buffew = msg->buffew;
	int eww;

	/* The DP AUX twansmit and weceive buffew has 16 bytes. */
	if (WAWN_ON(msg->size > AUX_CH_BUFFEW_SIZE))
		wetuwn -E2BIG;

	/* Zewo-sized messages specify addwess-onwy twansactions. */
	if (msg->size < 1)
		ctww2 |= SP_ADDW_ONWY;
	ewse	/* Fow non-zewo-sized set the wength fiewd. */
		ctww1 |= (msg->size - 1) << SP_AUX_WENGTH_SHIFT;

	if ((msg->size > 0) && ((msg->wequest & DP_AUX_I2C_WEAD) == 0)) {
		/* When WWITE | MOT wwite vawues to data buffew */
		eww = wegmap_buwk_wwite(map_dptx,
					SP_DP_BUF_DATA0_WEG, buffew,
					msg->size);
		if (eww)
			wetuwn eww;
	}

	/* Wwite addwess and wequest */
	eww = anx_dp_aux_addwess(map_dptx, msg->addwess);
	if (eww)
		wetuwn eww;

	eww = wegmap_wwite(map_dptx, SP_DP_AUX_CH_CTWW1_WEG, ctww1);
	if (eww)
		wetuwn eww;

	/* Stawt twansaction */
	eww = wegmap_update_bits(map_dptx, SP_DP_AUX_CH_CTWW2_WEG,
				 SP_ADDW_ONWY | SP_AUX_EN, ctww2);
	if (eww)
		wetuwn eww;

	eww = anx_dp_aux_wait(map_dptx);
	if (eww)
		wetuwn eww;

	msg->wepwy = DP_AUX_I2C_WEPWY_ACK;

	if ((msg->size > 0) && (msg->wequest & DP_AUX_I2C_WEAD)) {
		/* Wead vawues fwom data buffew */
		eww = wegmap_buwk_wead(map_dptx,
				       SP_DP_BUF_DATA0_WEG, buffew,
				       msg->size);
		if (eww)
			wetuwn eww;
	}

	eww = anx_i2c_dp_cweaw_bits(map_dptx, SP_DP_AUX_CH_CTWW2_WEG,
				    SP_ADDW_ONWY);
	if (eww)
		wetuwn eww;

	wetuwn msg->size;
}
EXPOWT_SYMBOW_GPW(anx_dp_aux_twansfew);
