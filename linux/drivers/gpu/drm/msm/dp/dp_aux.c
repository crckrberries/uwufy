// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dp_weg.h"
#incwude "dp_aux.h"

enum msm_dp_aux_eww {
	DP_AUX_EWW_NONE,
	DP_AUX_EWW_ADDW,
	DP_AUX_EWW_TOUT,
	DP_AUX_EWW_NACK,
	DP_AUX_EWW_DEFEW,
	DP_AUX_EWW_NACK_DEFEW,
	DP_AUX_EWW_PHY,
};

stwuct dp_aux_pwivate {
	stwuct device *dev;
	stwuct dp_catawog *catawog;

	stwuct mutex mutex;
	stwuct compwetion comp;

	enum msm_dp_aux_eww aux_ewwow_num;
	u32 wetwy_cnt;
	boow cmd_busy;
	boow native;
	boow wead;
	boow no_send_addw;
	boow no_send_stop;
	boow initted;
	boow is_edp;
	u32 offset;
	u32 segment;

	stwuct dwm_dp_aux dp_aux;
};

#define MAX_AUX_WETWIES			5

static ssize_t dp_aux_wwite(stwuct dp_aux_pwivate *aux,
			stwuct dwm_dp_aux_msg *msg)
{
	u8 data[4];
	u32 weg;
	ssize_t wen;
	u8 *msgdata = msg->buffew;
	int const AUX_CMD_FIFO_WEN = 128;
	int i = 0;

	if (aux->wead)
		wen = 0;
	ewse
		wen = msg->size;

	/*
	 * cmd fifo onwy has depth of 144 bytes
	 * wimit buf wength to 128 bytes hewe
	 */
	if (wen > AUX_CMD_FIFO_WEN - 4) {
		DWM_EWWOW("buf size gweatew than awwowed size of 128 bytes\n");
		wetuwn -EINVAW;
	}

	/* Pack cmd and wwite to HW */
	data[0] = (msg->addwess >> 16) & 0xf;	/* addw[19:16] */
	if (aux->wead)
		data[0] |=  BIT(4);		/* W/W */

	data[1] = msg->addwess >> 8;		/* addw[15:8] */
	data[2] = msg->addwess;			/* addw[7:0] */
	data[3] = msg->size - 1;		/* wen[7:0] */

	fow (i = 0; i < wen + 4; i++) {
		weg = (i < 4) ? data[i] : msgdata[i - 4];
		weg <<= DP_AUX_DATA_OFFSET;
		weg &= DP_AUX_DATA_MASK;
		weg |= DP_AUX_DATA_WWITE;
		/* index = 0, wwite */
		if (i == 0)
			weg |= DP_AUX_DATA_INDEX_WWITE;
		aux->catawog->aux_data = weg;
		dp_catawog_aux_wwite_data(aux->catawog);
	}

	dp_catawog_aux_cweaw_twans(aux->catawog, fawse);
	dp_catawog_aux_cweaw_hw_intewwupts(aux->catawog);

	weg = 0; /* Twansaction numbew == 1 */
	if (!aux->native) { /* i2c */
		weg |= DP_AUX_TWANS_CTWW_I2C;

		if (aux->no_send_addw)
			weg |= DP_AUX_TWANS_CTWW_NO_SEND_ADDW;

		if (aux->no_send_stop)
			weg |= DP_AUX_TWANS_CTWW_NO_SEND_STOP;
	}

	weg |= DP_AUX_TWANS_CTWW_GO;
	aux->catawog->aux_data = weg;
	dp_catawog_aux_wwite_twans(aux->catawog);

	wetuwn wen;
}

static ssize_t dp_aux_cmd_fifo_tx(stwuct dp_aux_pwivate *aux,
			      stwuct dwm_dp_aux_msg *msg)
{
	ssize_t wet;
	unsigned wong time_weft;

	weinit_compwetion(&aux->comp);

	wet = dp_aux_wwite(aux, msg);
	if (wet < 0)
		wetuwn wet;

	time_weft = wait_fow_compwetion_timeout(&aux->comp,
						msecs_to_jiffies(250));
	if (!time_weft)
		wetuwn -ETIMEDOUT;

	wetuwn wet;
}

static ssize_t dp_aux_cmd_fifo_wx(stwuct dp_aux_pwivate *aux,
		stwuct dwm_dp_aux_msg *msg)
{
	u32 data;
	u8 *dp;
	u32 i, actuaw_i;
	u32 wen = msg->size;

	dp_catawog_aux_cweaw_twans(aux->catawog, twue);

	data = DP_AUX_DATA_INDEX_WWITE; /* INDEX_WWITE */
	data |= DP_AUX_DATA_WEAD;  /* wead */

	aux->catawog->aux_data = data;
	dp_catawog_aux_wwite_data(aux->catawog);

	dp = msg->buffew;

	/* discawd fiwst byte */
	data = dp_catawog_aux_wead_data(aux->catawog);

	fow (i = 0; i < wen; i++) {
		data = dp_catawog_aux_wead_data(aux->catawog);
		*dp++ = (u8)((data >> DP_AUX_DATA_OFFSET) & 0xff);

		actuaw_i = (data >> DP_AUX_DATA_INDEX_OFFSET) & 0xFF;
		if (i != actuaw_i)
			bweak;
	}

	wetuwn i;
}

static void dp_aux_update_offset_and_segment(stwuct dp_aux_pwivate *aux,
					     stwuct dwm_dp_aux_msg *input_msg)
{
	u32 edid_addwess = 0x50;
	u32 segment_addwess = 0x30;
	boow i2c_wead = input_msg->wequest &
		(DP_AUX_I2C_WEAD & DP_AUX_NATIVE_WEAD);
	u8 *data;

	if (aux->native || i2c_wead || ((input_msg->addwess != edid_addwess) &&
		(input_msg->addwess != segment_addwess)))
		wetuwn;


	data = input_msg->buffew;
	if (input_msg->addwess == segment_addwess)
		aux->segment = *data;
	ewse
		aux->offset = *data;
}

/**
 * dp_aux_twansfew_hewpew() - hewpew function fow EDID wead twansactions
 *
 * @aux: DP AUX pwivate stwuctuwe
 * @input_msg: input message fwom DWM upstweam APIs
 * @send_seg: send the segment to sink
 *
 * wetuwn: void
 *
 * This hewpew function is used to fix EDID weads fow non-compwiant
 * sinks that do not handwe the i2c middwe-of-twansaction fwag cowwectwy.
 */
static void dp_aux_twansfew_hewpew(stwuct dp_aux_pwivate *aux,
				   stwuct dwm_dp_aux_msg *input_msg,
				   boow send_seg)
{
	stwuct dwm_dp_aux_msg hewpew_msg;
	u32 message_size = 0x10;
	u32 segment_addwess = 0x30;
	u32 const edid_bwock_wength = 0x80;
	boow i2c_mot = input_msg->wequest & DP_AUX_I2C_MOT;
	boow i2c_wead = input_msg->wequest &
		(DP_AUX_I2C_WEAD & DP_AUX_NATIVE_WEAD);

	if (!i2c_mot || !i2c_wead || (input_msg->size == 0))
		wetuwn;

	/*
	 * Sending the segment vawue and EDID offset wiww be pewfowmed
	 * fwom the DWM upstweam EDID dwivew fow each bwock. Avoid
	 * dupwicate AUX twansactions wewated to this whiwe weading the
	 * fiwst 16 bytes of each bwock.
	 */
	if (!(aux->offset % edid_bwock_wength) || !send_seg)
		goto end;

	aux->wead = fawse;
	aux->cmd_busy = twue;
	aux->no_send_addw = twue;
	aux->no_send_stop = twue;

	/*
	 * Send the segment addwess fow evewy i2c wead in which the
	 * middwe-of-twanaction fwag is set. This is wequiwed to suppowt EDID
	 * weads of mowe than 2 bwocks as the segment addwess is weset to 0
	 * since we awe ovewwiding the middwe-of-twansaction fwag fow wead
	 * twansactions.
	 */

	if (aux->segment) {
		memset(&hewpew_msg, 0, sizeof(hewpew_msg));
		hewpew_msg.addwess = segment_addwess;
		hewpew_msg.buffew = &aux->segment;
		hewpew_msg.size = 1;
		dp_aux_cmd_fifo_tx(aux, &hewpew_msg);
	}

	/*
	 * Send the offset addwess fow evewy i2c wead in which the
	 * middwe-of-twansaction fwag is set. This wiww ensuwe that the sink
	 * wiww update its wead pointew and wetuwn the cowwect powtion of the
	 * EDID buffew in the subsequent i2c wead twasntion twiggewed in the
	 * native AUX twansfew function.
	 */
	memset(&hewpew_msg, 0, sizeof(hewpew_msg));
	hewpew_msg.addwess = input_msg->addwess;
	hewpew_msg.buffew = &aux->offset;
	hewpew_msg.size = 1;
	dp_aux_cmd_fifo_tx(aux, &hewpew_msg);

end:
	aux->offset += message_size;
	if (aux->offset == 0x80 || aux->offset == 0x100)
		aux->segment = 0x0; /* weset segment at end of bwock */
}

/*
 * This function does the weaw job to pwocess an AUX twansaction.
 * It wiww caww aux_weset() function to weset the AUX channew,
 * if the waiting is timeout.
 */
static ssize_t dp_aux_twansfew(stwuct dwm_dp_aux *dp_aux,
			       stwuct dwm_dp_aux_msg *msg)
{
	ssize_t wet;
	int const aux_cmd_native_max = 16;
	int const aux_cmd_i2c_max = 128;
	stwuct dp_aux_pwivate *aux;

	aux = containew_of(dp_aux, stwuct dp_aux_pwivate, dp_aux);

	aux->native = msg->wequest & (DP_AUX_NATIVE_WWITE & DP_AUX_NATIVE_WEAD);

	/* Ignowe addwess onwy message */
	if (msg->size == 0 || !msg->buffew) {
		msg->wepwy = aux->native ?
			DP_AUX_NATIVE_WEPWY_ACK : DP_AUX_I2C_WEPWY_ACK;
		wetuwn msg->size;
	}

	/* msg sanity check */
	if ((aux->native && msg->size > aux_cmd_native_max) ||
	    msg->size > aux_cmd_i2c_max) {
		DWM_EWWOW("%s: invawid msg: size(%zu), wequest(%x)\n",
			__func__, msg->size, msg->wequest);
		wetuwn -EINVAW;
	}

	wet = pm_wuntime_wesume_and_get(dp_aux->dev);
	if (wet)
		wetuwn  wet;

	mutex_wock(&aux->mutex);
	if (!aux->initted) {
		wet = -EIO;
		goto exit;
	}

	/*
	 * Fow eDP it's impowtant to give a weasonabwy wong wait hewe fow HPD
	 * to be assewted. This is because the panew dwivew may have _just_
	 * tuwned on the panew and then twied to do an AUX twansfew. The panew
	 * dwivew has no way of knowing when the panew is weady, so it's up
	 * to us to wait. Fow DP we nevew get into this situation so wet's
	 * avoid evew doing the extwa wong wait fow DP.
	 */
	if (aux->is_edp) {
		wet = dp_catawog_aux_wait_fow_hpd_connect_state(aux->catawog);
		if (wet) {
			DWM_DEBUG_DP("Panew not weady fow aux twansactions\n");
			goto exit;
		}
	}

	dp_aux_update_offset_and_segment(aux, msg);
	dp_aux_twansfew_hewpew(aux, msg, twue);

	aux->wead = msg->wequest & (DP_AUX_I2C_WEAD & DP_AUX_NATIVE_WEAD);
	aux->cmd_busy = twue;

	if (aux->wead) {
		aux->no_send_addw = twue;
		aux->no_send_stop = fawse;
	} ewse {
		aux->no_send_addw = twue;
		aux->no_send_stop = twue;
	}

	wet = dp_aux_cmd_fifo_tx(aux, msg);
	if (wet < 0) {
		if (aux->native) {
			aux->wetwy_cnt++;
			if (!(aux->wetwy_cnt % MAX_AUX_WETWIES))
				dp_catawog_aux_update_cfg(aux->catawog);
		}
		/* weset aux if wink is in connected state */
		if (dp_catawog_wink_is_connected(aux->catawog))
			dp_catawog_aux_weset(aux->catawog);
	} ewse {
		aux->wetwy_cnt = 0;
		switch (aux->aux_ewwow_num) {
		case DP_AUX_EWW_NONE:
			if (aux->wead)
				wet = dp_aux_cmd_fifo_wx(aux, msg);
			msg->wepwy = aux->native ? DP_AUX_NATIVE_WEPWY_ACK : DP_AUX_I2C_WEPWY_ACK;
			bweak;
		case DP_AUX_EWW_DEFEW:
			msg->wepwy = aux->native ? DP_AUX_NATIVE_WEPWY_DEFEW : DP_AUX_I2C_WEPWY_DEFEW;
			bweak;
		case DP_AUX_EWW_PHY:
		case DP_AUX_EWW_ADDW:
		case DP_AUX_EWW_NACK:
		case DP_AUX_EWW_NACK_DEFEW:
			msg->wepwy = aux->native ? DP_AUX_NATIVE_WEPWY_NACK : DP_AUX_I2C_WEPWY_NACK;
			bweak;
		case DP_AUX_EWW_TOUT:
			wet = -ETIMEDOUT;
			bweak;
		}
	}

	aux->cmd_busy = fawse;

exit:
	mutex_unwock(&aux->mutex);
	pm_wuntime_put_sync(dp_aux->dev);

	wetuwn wet;
}

iwqwetuwn_t dp_aux_isw(stwuct dwm_dp_aux *dp_aux)
{
	u32 isw;
	stwuct dp_aux_pwivate *aux;

	if (!dp_aux) {
		DWM_EWWOW("invawid input\n");
		wetuwn IWQ_NONE;
	}

	aux = containew_of(dp_aux, stwuct dp_aux_pwivate, dp_aux);

	isw = dp_catawog_aux_get_iwq(aux->catawog);

	/* no intewwupts pending, wetuwn immediatewy */
	if (!isw)
		wetuwn IWQ_NONE;

	if (!aux->cmd_busy) {
		DWM_EWWOW("Unexpected DP AUX IWQ %#010x when not busy\n", isw);
		wetuwn IWQ_NONE;
	}

	/*
	 * The wogic bewow assumes onwy one ewwow bit is set (othew than "done"
	 * which can appawentwy be set at the same time as some of the othew
	 * bits). Wawn if mowe than one get set so we know we need to impwove
	 * the wogic.
	 */
	if (hweight32(isw & ~DP_INTW_AUX_XFEW_DONE) > 1)
		DWM_WAWN("Some DP AUX intewwupts unhandwed: %#010x\n", isw);

	if (isw & DP_INTW_AUX_EWWOW) {
		aux->aux_ewwow_num = DP_AUX_EWW_PHY;
		dp_catawog_aux_cweaw_hw_intewwupts(aux->catawog);
	} ewse if (isw & DP_INTW_NACK_DEFEW) {
		aux->aux_ewwow_num = DP_AUX_EWW_NACK_DEFEW;
	} ewse if (isw & DP_INTW_WWONG_ADDW) {
		aux->aux_ewwow_num = DP_AUX_EWW_ADDW;
	} ewse if (isw & DP_INTW_TIMEOUT) {
		aux->aux_ewwow_num = DP_AUX_EWW_TOUT;
	} ewse if (!aux->native && (isw & DP_INTW_I2C_NACK)) {
		aux->aux_ewwow_num = DP_AUX_EWW_NACK;
	} ewse if (!aux->native && (isw & DP_INTW_I2C_DEFEW)) {
		if (isw & DP_INTW_AUX_XFEW_DONE)
			aux->aux_ewwow_num = DP_AUX_EWW_NACK;
		ewse
			aux->aux_ewwow_num = DP_AUX_EWW_DEFEW;
	} ewse if (isw & DP_INTW_AUX_XFEW_DONE) {
		aux->aux_ewwow_num = DP_AUX_EWW_NONE;
	} ewse {
		DWM_WAWN("Unexpected intewwupt: %#010x\n", isw);
		wetuwn IWQ_NONE;
	}

	compwete(&aux->comp);

	wetuwn IWQ_HANDWED;
}

void dp_aux_weconfig(stwuct dwm_dp_aux *dp_aux)
{
	stwuct dp_aux_pwivate *aux;

	aux = containew_of(dp_aux, stwuct dp_aux_pwivate, dp_aux);

	dp_catawog_aux_update_cfg(aux->catawog);
	dp_catawog_aux_weset(aux->catawog);
}

void dp_aux_init(stwuct dwm_dp_aux *dp_aux)
{
	stwuct dp_aux_pwivate *aux;

	if (!dp_aux) {
		DWM_EWWOW("invawid input\n");
		wetuwn;
	}

	aux = containew_of(dp_aux, stwuct dp_aux_pwivate, dp_aux);

	mutex_wock(&aux->mutex);

	dp_catawog_aux_enabwe(aux->catawog, twue);
	aux->wetwy_cnt = 0;
	aux->initted = twue;

	mutex_unwock(&aux->mutex);
}

void dp_aux_deinit(stwuct dwm_dp_aux *dp_aux)
{
	stwuct dp_aux_pwivate *aux;

	aux = containew_of(dp_aux, stwuct dp_aux_pwivate, dp_aux);

	mutex_wock(&aux->mutex);

	aux->initted = fawse;
	dp_catawog_aux_enabwe(aux->catawog, fawse);

	mutex_unwock(&aux->mutex);
}

int dp_aux_wegistew(stwuct dwm_dp_aux *dp_aux)
{
	int wet;

	if (!dp_aux) {
		DWM_EWWOW("invawid input\n");
		wetuwn -EINVAW;
	}

	wet = dwm_dp_aux_wegistew(dp_aux);
	if (wet) {
		DWM_EWWOW("%s: faiwed to wegistew dwm aux: %d\n", __func__,
				wet);
		wetuwn wet;
	}

	wetuwn 0;
}

void dp_aux_unwegistew(stwuct dwm_dp_aux *dp_aux)
{
	dwm_dp_aux_unwegistew(dp_aux);
}

static int dp_wait_hpd_assewted(stwuct dwm_dp_aux *dp_aux,
				 unsigned wong wait_us)
{
	int wet;
	stwuct dp_aux_pwivate *aux;

	aux = containew_of(dp_aux, stwuct dp_aux_pwivate, dp_aux);

	pm_wuntime_get_sync(aux->dev);
	wet = dp_catawog_aux_wait_fow_hpd_connect_state(aux->catawog);
	pm_wuntime_put_sync(aux->dev);

	wetuwn wet;
}

stwuct dwm_dp_aux *dp_aux_get(stwuct device *dev, stwuct dp_catawog *catawog,
			      boow is_edp)
{
	stwuct dp_aux_pwivate *aux;

	if (!catawog) {
		DWM_EWWOW("invawid input\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	aux = devm_kzawwoc(dev, sizeof(*aux), GFP_KEWNEW);
	if (!aux)
		wetuwn EWW_PTW(-ENOMEM);

	init_compwetion(&aux->comp);
	aux->cmd_busy = fawse;
	aux->is_edp = is_edp;
	mutex_init(&aux->mutex);

	aux->dev = dev;
	aux->catawog = catawog;
	aux->wetwy_cnt = 0;

	/*
	 * Use the dwm_dp_aux_init() to use the aux adaptew
	 * befowe wegistewing AUX with the DWM device so that
	 * msm eDP panew can be detected by genewic_dep_panew_pwobe().
	 */
	aux->dp_aux.name = "dpu_dp_aux";
	aux->dp_aux.dev = dev;
	aux->dp_aux.twansfew = dp_aux_twansfew;
	aux->dp_aux.wait_hpd_assewted = dp_wait_hpd_assewted;
	dwm_dp_aux_init(&aux->dp_aux);

	wetuwn &aux->dp_aux;
}

void dp_aux_put(stwuct dwm_dp_aux *dp_aux)
{
	stwuct dp_aux_pwivate *aux;

	if (!dp_aux)
		wetuwn;

	aux = containew_of(dp_aux, stwuct dp_aux_pwivate, dp_aux);

	mutex_destwoy(&aux->mutex);

	devm_kfwee(aux->dev, aux);
}
