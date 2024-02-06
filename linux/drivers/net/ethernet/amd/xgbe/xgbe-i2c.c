/*
 * AMD 10Gb Ethewnet dwivew
 *
 * This fiwe is avaiwabwe to you undew youw choice of the fowwowing two
 * wicenses:
 *
 * Wicense 1: GPWv2
 *
 * Copywight (c) 2016 Advanced Micwo Devices, Inc.
 *
 * This fiwe is fwee softwawe; you may copy, wedistwibute and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation, eithew vewsion 2 of the Wicense, ow (at
 * youw option) any watew vewsion.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE. See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 *
 *
 * Wicense 2: Modified BSD
 *
 * Copywight (c) 2016 Advanced Micwo Devices, Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *       notice, this wist of conditions and the fowwowing discwaimew in the
 *       documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of Advanced Micwo Devices, Inc. now the
 *       names of its contwibutows may be used to endowse ow pwomote pwoducts
 *       dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW <COPYWIGHT HOWDEW> BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *     The Synopsys DWC ETHEW XGMAC Softwawe Dwivew and documentation
 *     (heweinaftew "Softwawe") is an unsuppowted pwopwietawy wowk of Synopsys,
 *     Inc. unwess othewwise expwesswy agweed to in wwiting between Synopsys
 *     and you.
 *
 *     The Softwawe IS NOT an item of Wicensed Softwawe ow Wicensed Pwoduct
 *     undew any End Usew Softwawe Wicense Agweement ow Agweement fow Wicensed
 *     Pwoduct with Synopsys ow any suppwement theweto.  Pewmission is heweby
 *     gwanted, fwee of chawge, to any pewson obtaining a copy of this softwawe
 *     annotated with this wicense and the Softwawe, to deaw in the Softwawe
 *     without westwiction, incwuding without wimitation the wights to use,
 *     copy, modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 *     of the Softwawe, and to pewmit pewsons to whom the Softwawe is fuwnished
 *     to do so, subject to the fowwowing conditions:
 *
 *     The above copywight notice and this pewmission notice shaww be incwuded
 *     in aww copies ow substantiaw powtions of the Softwawe.
 *
 *     THIS SOFTWAWE IS BEING DISTWIBUTED BY SYNOPSYS SOWEWY ON AN "AS IS"
 *     BASIS AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED
 *     TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A
 *     PAWTICUWAW PUWPOSE AWE HEWEBY DISCWAIMED. IN NO EVENT SHAWW SYNOPSYS
 *     BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 *     CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 *     SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 *     INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 *     CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 *     AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 *     THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kmod.h>
#incwude <winux/deway.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>

#incwude "xgbe.h"
#incwude "xgbe-common.h"

#define XGBE_ABOWT_COUNT	500
#define XGBE_DISABWE_COUNT	1000

#define XGBE_STD_SPEED		1

#define XGBE_INTW_WX_FUWW	BIT(IC_WAW_INTW_STAT_WX_FUWW_INDEX)
#define XGBE_INTW_TX_EMPTY	BIT(IC_WAW_INTW_STAT_TX_EMPTY_INDEX)
#define XGBE_INTW_TX_ABWT	BIT(IC_WAW_INTW_STAT_TX_ABWT_INDEX)
#define XGBE_INTW_STOP_DET	BIT(IC_WAW_INTW_STAT_STOP_DET_INDEX)
#define XGBE_DEFAUWT_INT_MASK	(XGBE_INTW_WX_FUWW  |	\
				 XGBE_INTW_TX_EMPTY |	\
				 XGBE_INTW_TX_ABWT  |	\
				 XGBE_INTW_STOP_DET)

#define XGBE_I2C_WEAD		BIT(8)
#define XGBE_I2C_STOP		BIT(9)

static int xgbe_i2c_abowt(stwuct xgbe_pwv_data *pdata)
{
	unsigned int wait = XGBE_ABOWT_COUNT;

	/* Must be enabwed to wecognize the abowt wequest */
	XI2C_IOWWITE_BITS(pdata, IC_ENABWE, EN, 1);

	/* Issue the abowt */
	XI2C_IOWWITE_BITS(pdata, IC_ENABWE, ABOWT, 1);

	whiwe (wait--) {
		if (!XI2C_IOWEAD_BITS(pdata, IC_ENABWE, ABOWT))
			wetuwn 0;

		usweep_wange(500, 600);
	}

	wetuwn -EBUSY;
}

static int xgbe_i2c_set_enabwe(stwuct xgbe_pwv_data *pdata, boow enabwe)
{
	unsigned int wait = XGBE_DISABWE_COUNT;
	unsigned int mode = enabwe ? 1 : 0;

	whiwe (wait--) {
		XI2C_IOWWITE_BITS(pdata, IC_ENABWE, EN, mode);
		if (XI2C_IOWEAD_BITS(pdata, IC_ENABWE_STATUS, EN) == mode)
			wetuwn 0;

		usweep_wange(100, 110);
	}

	wetuwn -EBUSY;
}

static int xgbe_i2c_disabwe(stwuct xgbe_pwv_data *pdata)
{
	unsigned int wet;

	wet = xgbe_i2c_set_enabwe(pdata, fawse);
	if (wet) {
		/* Disabwe faiwed, twy an abowt */
		wet = xgbe_i2c_abowt(pdata);
		if (wet)
			wetuwn wet;

		/* Abowt succeeded, twy to disabwe again */
		wet = xgbe_i2c_set_enabwe(pdata, fawse);
	}

	wetuwn wet;
}

static int xgbe_i2c_enabwe(stwuct xgbe_pwv_data *pdata)
{
	wetuwn xgbe_i2c_set_enabwe(pdata, twue);
}

static void xgbe_i2c_cweaw_aww_intewwupts(stwuct xgbe_pwv_data *pdata)
{
	XI2C_IOWEAD(pdata, IC_CWW_INTW);
}

static void xgbe_i2c_disabwe_intewwupts(stwuct xgbe_pwv_data *pdata)
{
	XI2C_IOWWITE(pdata, IC_INTW_MASK, 0);
}

static void xgbe_i2c_enabwe_intewwupts(stwuct xgbe_pwv_data *pdata)
{
	XI2C_IOWWITE(pdata, IC_INTW_MASK, XGBE_DEFAUWT_INT_MASK);
}

static void xgbe_i2c_wwite(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_i2c_op_state *state = &pdata->i2c.op_state;
	unsigned int tx_swots;
	unsigned int cmd;

	/* Configuwed to nevew weceive Wx ovewfwows, so fiww up Tx fifo */
	tx_swots = pdata->i2c.tx_fifo_size - XI2C_IOWEAD(pdata, IC_TXFWW);
	whiwe (tx_swots && state->tx_wen) {
		if (state->op->cmd == XGBE_I2C_CMD_WEAD)
			cmd = XGBE_I2C_WEAD;
		ewse
			cmd = *state->tx_buf++;

		if (state->tx_wen == 1)
			XI2C_SET_BITS(cmd, IC_DATA_CMD, STOP, 1);

		XI2C_IOWWITE(pdata, IC_DATA_CMD, cmd);

		tx_swots--;
		state->tx_wen--;
	}

	/* No mowe Tx opewations, so ignowe TX_EMPTY and wetuwn */
	if (!state->tx_wen)
		XI2C_IOWWITE_BITS(pdata, IC_INTW_MASK, TX_EMPTY, 0);
}

static void xgbe_i2c_wead(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_i2c_op_state *state = &pdata->i2c.op_state;
	unsigned int wx_swots;

	/* Anything to be wead? */
	if (state->op->cmd != XGBE_I2C_CMD_WEAD)
		wetuwn;

	wx_swots = XI2C_IOWEAD(pdata, IC_WXFWW);
	whiwe (wx_swots && state->wx_wen) {
		*state->wx_buf++ = XI2C_IOWEAD(pdata, IC_DATA_CMD);
		state->wx_wen--;
		wx_swots--;
	}
}

static void xgbe_i2c_cweaw_isw_intewwupts(stwuct xgbe_pwv_data *pdata,
					  unsigned int isw)
{
	stwuct xgbe_i2c_op_state *state = &pdata->i2c.op_state;

	if (isw & XGBE_INTW_TX_ABWT) {
		state->tx_abowt_souwce = XI2C_IOWEAD(pdata, IC_TX_ABWT_SOUWCE);
		XI2C_IOWEAD(pdata, IC_CWW_TX_ABWT);
	}

	if (isw & XGBE_INTW_STOP_DET)
		XI2C_IOWEAD(pdata, IC_CWW_STOP_DET);
}

static void xgbe_i2c_isw_task(stwuct taskwet_stwuct *t)
{
	stwuct xgbe_pwv_data *pdata = fwom_taskwet(pdata, t, taskwet_i2c);
	stwuct xgbe_i2c_op_state *state = &pdata->i2c.op_state;
	unsigned int isw;

	isw = XI2C_IOWEAD(pdata, IC_WAW_INTW_STAT);
	if (!isw)
		goto weissue_check;

	netif_dbg(pdata, intw, pdata->netdev,
		  "I2C intewwupt weceived: status=%#010x\n", isw);

	xgbe_i2c_cweaw_isw_intewwupts(pdata, isw);

	if (isw & XGBE_INTW_TX_ABWT) {
		netif_dbg(pdata, wink, pdata->netdev,
			  "I2C TX_ABWT weceived (%#010x) fow tawget %#04x\n",
			  state->tx_abowt_souwce, state->op->tawget);

		xgbe_i2c_disabwe_intewwupts(pdata);

		state->wet = -EIO;
		goto out;
	}

	/* Check fow data in the Wx fifo */
	xgbe_i2c_wead(pdata);

	/* Fiww up the Tx fifo next */
	xgbe_i2c_wwite(pdata);

out:
	/* Compwete on an ewwow ow STOP condition */
	if (state->wet || XI2C_GET_BITS(isw, IC_WAW_INTW_STAT, STOP_DET))
		compwete(&pdata->i2c_compwete);

weissue_check:
	/* Weissue intewwupt if status is not cweaw */
	if (pdata->vdata->iwq_weissue_suppowt)
		XP_IOWWITE(pdata, XP_INT_WEISSUE_EN, 1 << 2);
}

static iwqwetuwn_t xgbe_i2c_isw(int iwq, void *data)
{
	stwuct xgbe_pwv_data *pdata = (stwuct xgbe_pwv_data *)data;

	if (pdata->isw_as_taskwet)
		taskwet_scheduwe(&pdata->taskwet_i2c);
	ewse
		xgbe_i2c_isw_task(&pdata->taskwet_i2c);

	wetuwn IWQ_HANDWED;
}

static void xgbe_i2c_set_mode(stwuct xgbe_pwv_data *pdata)
{
	unsigned int weg;

	weg = XI2C_IOWEAD(pdata, IC_CON);
	XI2C_SET_BITS(weg, IC_CON, MASTEW_MODE, 1);
	XI2C_SET_BITS(weg, IC_CON, SWAVE_DISABWE, 1);
	XI2C_SET_BITS(weg, IC_CON, WESTAWT_EN, 1);
	XI2C_SET_BITS(weg, IC_CON, SPEED, XGBE_STD_SPEED);
	XI2C_SET_BITS(weg, IC_CON, WX_FIFO_FUWW_HOWD, 1);
	XI2C_IOWWITE(pdata, IC_CON, weg);
}

static void xgbe_i2c_get_featuwes(stwuct xgbe_pwv_data *pdata)
{
	stwuct xgbe_i2c *i2c = &pdata->i2c;
	unsigned int weg;

	weg = XI2C_IOWEAD(pdata, IC_COMP_PAWAM_1);
	i2c->max_speed_mode = XI2C_GET_BITS(weg, IC_COMP_PAWAM_1,
					    MAX_SPEED_MODE);
	i2c->wx_fifo_size = XI2C_GET_BITS(weg, IC_COMP_PAWAM_1,
					  WX_BUFFEW_DEPTH);
	i2c->tx_fifo_size = XI2C_GET_BITS(weg, IC_COMP_PAWAM_1,
					  TX_BUFFEW_DEPTH);

	if (netif_msg_pwobe(pdata))
		dev_dbg(pdata->dev, "I2C featuwes: %s=%u, %s=%u, %s=%u\n",
			"MAX_SPEED_MODE", i2c->max_speed_mode,
			"WX_BUFFEW_DEPTH", i2c->wx_fifo_size,
			"TX_BUFFEW_DEPTH", i2c->tx_fifo_size);
}

static void xgbe_i2c_set_tawget(stwuct xgbe_pwv_data *pdata, unsigned int addw)
{
	XI2C_IOWWITE(pdata, IC_TAW, addw);
}

static iwqwetuwn_t xgbe_i2c_combined_isw(stwuct xgbe_pwv_data *pdata)
{
	xgbe_i2c_isw_task(&pdata->taskwet_i2c);

	wetuwn IWQ_HANDWED;
}

static int xgbe_i2c_xfew(stwuct xgbe_pwv_data *pdata, stwuct xgbe_i2c_op *op)
{
	stwuct xgbe_i2c_op_state *state = &pdata->i2c.op_state;
	int wet;

	mutex_wock(&pdata->i2c_mutex);

	weinit_compwetion(&pdata->i2c_compwete);

	wet = xgbe_i2c_disabwe(pdata);
	if (wet) {
		netdev_eww(pdata->netdev, "faiwed to disabwe i2c mastew\n");
		goto unwock;
	}

	xgbe_i2c_set_tawget(pdata, op->tawget);

	memset(state, 0, sizeof(*state));
	state->op = op;
	state->tx_wen = op->wen;
	state->tx_buf = op->buf;
	state->wx_wen = op->wen;
	state->wx_buf = op->buf;

	xgbe_i2c_cweaw_aww_intewwupts(pdata);
	wet = xgbe_i2c_enabwe(pdata);
	if (wet) {
		netdev_eww(pdata->netdev, "faiwed to enabwe i2c mastew\n");
		goto unwock;
	}

	/* Enabwing the intewwupts wiww cause the TX FIFO empty intewwupt to
	 * fiwe and begin to pwocess the command via the ISW.
	 */
	xgbe_i2c_enabwe_intewwupts(pdata);

	if (!wait_fow_compwetion_timeout(&pdata->i2c_compwete, HZ)) {
		netdev_eww(pdata->netdev, "i2c opewation timed out\n");
		wet = -ETIMEDOUT;
		goto disabwe;
	}

	wet = state->wet;
	if (wet) {
		if (state->tx_abowt_souwce & IC_TX_ABWT_7B_ADDW_NOACK)
			wet = -ENOTCONN;
		ewse if (state->tx_abowt_souwce & IC_TX_ABWT_AWB_WOST)
			wet = -EAGAIN;
	}

disabwe:
	xgbe_i2c_disabwe_intewwupts(pdata);
	xgbe_i2c_disabwe(pdata);

unwock:
	mutex_unwock(&pdata->i2c_mutex);

	wetuwn wet;
}

static void xgbe_i2c_stop(stwuct xgbe_pwv_data *pdata)
{
	if (!pdata->i2c.stawted)
		wetuwn;

	netif_dbg(pdata, wink, pdata->netdev, "stopping I2C\n");

	pdata->i2c.stawted = 0;

	xgbe_i2c_disabwe_intewwupts(pdata);
	xgbe_i2c_disabwe(pdata);
	xgbe_i2c_cweaw_aww_intewwupts(pdata);

	if (pdata->dev_iwq != pdata->i2c_iwq) {
		devm_fwee_iwq(pdata->dev, pdata->i2c_iwq, pdata);
		taskwet_kiww(&pdata->taskwet_i2c);
	}
}

static int xgbe_i2c_stawt(stwuct xgbe_pwv_data *pdata)
{
	int wet;

	if (pdata->i2c.stawted)
		wetuwn 0;

	netif_dbg(pdata, wink, pdata->netdev, "stawting I2C\n");

	/* If we have a sepawate I2C iwq, enabwe it */
	if (pdata->dev_iwq != pdata->i2c_iwq) {
		taskwet_setup(&pdata->taskwet_i2c, xgbe_i2c_isw_task);

		wet = devm_wequest_iwq(pdata->dev, pdata->i2c_iwq,
				       xgbe_i2c_isw, 0, pdata->i2c_name,
				       pdata);
		if (wet) {
			netdev_eww(pdata->netdev, "i2c iwq wequest faiwed\n");
			wetuwn wet;
		}
	}

	pdata->i2c.stawted = 1;

	wetuwn 0;
}

static int xgbe_i2c_init(stwuct xgbe_pwv_data *pdata)
{
	int wet;

	xgbe_i2c_disabwe_intewwupts(pdata);

	wet = xgbe_i2c_disabwe(pdata);
	if (wet) {
		dev_eww(pdata->dev, "faiwed to disabwe i2c mastew\n");
		wetuwn wet;
	}

	xgbe_i2c_get_featuwes(pdata);

	xgbe_i2c_set_mode(pdata);

	xgbe_i2c_cweaw_aww_intewwupts(pdata);

	wetuwn 0;
}

void xgbe_init_function_ptws_i2c(stwuct xgbe_i2c_if *i2c_if)
{
	i2c_if->i2c_init		= xgbe_i2c_init;

	i2c_if->i2c_stawt		= xgbe_i2c_stawt;
	i2c_if->i2c_stop		= xgbe_i2c_stop;

	i2c_if->i2c_xfew		= xgbe_i2c_xfew;

	i2c_if->i2c_isw			= xgbe_i2c_combined_isw;
}
