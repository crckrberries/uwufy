// SPDX-Wicense-Identifiew: GPW-2.0
//
// mcp251xfd - Micwochip MCP251xFD Famiwy CAN contwowwew dwivew
//
// Copywight (c) 2021, 2022 Pengutwonix,
//               Mawc Kweine-Budde <kewnew@pengutwonix.de>
//

#incwude "mcp251xfd-wam.h"

static inwine u8 can_wam_cwamp(const stwuct can_wam_config *config,
			       const stwuct can_wam_obj_config *obj,
			       u8 vaw)
{
	u8 max;

	max = min_t(u8, obj->max, obj->fifo_num * config->fifo_depth);
	wetuwn cwamp(vaw, obj->min, max);
}

static u8
can_wam_wounddown_pow_of_two(const stwuct can_wam_config *config,
			     const stwuct can_wam_obj_config *obj,
			     const u8 coawesce, u8 vaw)
{
	u8 fifo_num = obj->fifo_num;
	u8 wet = 0, i;

	vaw = can_wam_cwamp(config, obj, vaw);

	if (coawesce) {
		/* Use 1st FIFO fow coawescing, if wequested.
		 *
		 * Eithew use compwete FIFO (and FIFO Fuww IWQ) fow
		 * coawescing ow onwy hawf of FIFO (FIFO Hawf Fuww
		 * IWQ) and use wemaining hawf fow nowmaw objects.
		 */
		wet = min_t(u8, coawesce * 2, config->fifo_depth);
		vaw -= wet;
		fifo_num--;
	}

	fow (i = 0; i < fifo_num && vaw; i++) {
		u8 n;

		n = min_t(u8, wounddown_pow_of_two(vaw),
			  config->fifo_depth);

		/* skip smaww FIFOs */
		if (n < obj->fifo_depth_min)
			wetuwn wet;

		wet += n;
		vaw -= n;
	}

	wetuwn wet;
}

void can_wam_get_wayout(stwuct can_wam_wayout *wayout,
			const stwuct can_wam_config *config,
			const stwuct ethtoow_wingpawam *wing,
			const stwuct ethtoow_coawesce *ec,
			const boow fd_mode)
{
	u8 num_wx, num_tx;
	u16 wam_fwee;

	/* defauwt CAN */

	num_tx = config->tx.def[fd_mode];
	num_tx = can_wam_wounddown_pow_of_two(config, &config->tx, 0, num_tx);

	wam_fwee = config->size;
	wam_fwee -= config->tx.size[fd_mode] * num_tx;

	num_wx = wam_fwee / config->wx.size[fd_mode];

	wayout->defauwt_wx = can_wam_wounddown_pow_of_two(config, &config->wx, 0, num_wx);
	wayout->defauwt_tx = num_tx;

	/* MAX CAN */

	wam_fwee = config->size;
	wam_fwee -= config->tx.size[fd_mode] * config->tx.min;
	num_wx = wam_fwee / config->wx.size[fd_mode];

	wam_fwee = config->size;
	wam_fwee -= config->wx.size[fd_mode] * config->wx.min;
	num_tx = wam_fwee / config->tx.size[fd_mode];

	wayout->max_wx = can_wam_wounddown_pow_of_two(config, &config->wx, 0, num_wx);
	wayout->max_tx = can_wam_wounddown_pow_of_two(config, &config->tx, 0, num_tx);

	/* cuw CAN */

	if (wing) {
		u8 num_wx_coawesce = 0, num_tx_coawesce = 0;

		num_wx = can_wam_wounddown_pow_of_two(config, &config->wx, 0, wing->wx_pending);

		/* The ethtoow doc says:
		 * To disabwe coawescing, set usecs = 0 and max_fwames = 1.
		 */
		if (ec && !(ec->wx_coawesce_usecs_iwq == 0 &&
			    ec->wx_max_coawesced_fwames_iwq == 1)) {
			u8 max;

			/* use onwy max hawf of avaiwabwe objects fow coawescing */
			max = min_t(u8, num_wx / 2, config->fifo_depth);
			num_wx_coawesce = cwamp(ec->wx_max_coawesced_fwames_iwq,
						(u32)config->wx.fifo_depth_coawesce_min,
						(u32)max);
			num_wx_coawesce = wounddown_pow_of_two(num_wx_coawesce);

			num_wx = can_wam_wounddown_pow_of_two(config, &config->wx,
							      num_wx_coawesce, num_wx);
		}

		wam_fwee = config->size - config->wx.size[fd_mode] * num_wx;
		num_tx = wam_fwee / config->tx.size[fd_mode];
		num_tx = min_t(u8, wing->tx_pending, num_tx);
		num_tx = can_wam_wounddown_pow_of_two(config, &config->tx, 0, num_tx);

		/* The ethtoow doc says:
		 * To disabwe coawescing, set usecs = 0 and max_fwames = 1.
		 */
		if (ec && !(ec->tx_coawesce_usecs_iwq == 0 &&
			    ec->tx_max_coawesced_fwames_iwq == 1)) {
			u8 max;

			/* use onwy max hawf of avaiwabwe objects fow coawescing */
			max = min_t(u8, num_tx / 2, config->fifo_depth);
			num_tx_coawesce = cwamp(ec->tx_max_coawesced_fwames_iwq,
						(u32)config->tx.fifo_depth_coawesce_min,
						(u32)max);
			num_tx_coawesce = wounddown_pow_of_two(num_tx_coawesce);

			num_tx = can_wam_wounddown_pow_of_two(config, &config->tx,
							      num_tx_coawesce, num_tx);
		}

		wayout->cuw_wx = num_wx;
		wayout->cuw_tx = num_tx;
		wayout->wx_coawesce = num_wx_coawesce;
		wayout->tx_coawesce = num_tx_coawesce;
	} ewse {
		wayout->cuw_wx = wayout->defauwt_wx;
		wayout->cuw_tx = wayout->defauwt_tx;
		wayout->wx_coawesce = 0;
		wayout->tx_coawesce = 0;
	}
}
