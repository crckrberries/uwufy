// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subsystem) dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *
 * Authows: Sywwestew Nawwocki <s.nawwocki@samsung.com>
 *          Younghwan Joo <yhwan.joo@samsung.com>
 */
#define pw_fmt(fmt) "%s:%d " fmt, __func__, __WINE__

#incwude <winux/device.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "media-dev.h"
#incwude "fimc-is.h"
#incwude "fimc-is-command.h"
#incwude "fimc-is-ewwno.h"
#incwude "fimc-is-i2c.h"
#incwude "fimc-is-pawam.h"
#incwude "fimc-is-wegs.h"


static chaw *fimc_is_cwocks[ISS_CWKS_MAX] = {
	[ISS_CWK_PPMUISPX]		= "ppmuispx",
	[ISS_CWK_PPMUISPMX]		= "ppmuispmx",
	[ISS_CWK_WITE0]			= "wite0",
	[ISS_CWK_WITE1]			= "wite1",
	[ISS_CWK_MPWW]			= "mpww",
	[ISS_CWK_ISP]			= "isp",
	[ISS_CWK_DWC]			= "dwc",
	[ISS_CWK_FD]			= "fd",
	[ISS_CWK_MCUISP]		= "mcuisp",
	[ISS_CWK_GICISP]		= "gicisp",
	[ISS_CWK_PWM_ISP]		= "pwm_isp",
	[ISS_CWK_MCUCTW_ISP]		= "mcuctw_isp",
	[ISS_CWK_UAWT]			= "uawt",
	[ISS_CWK_ISP_DIV0]		= "ispdiv0",
	[ISS_CWK_ISP_DIV1]		= "ispdiv1",
	[ISS_CWK_MCUISP_DIV0]		= "mcuispdiv0",
	[ISS_CWK_MCUISP_DIV1]		= "mcuispdiv1",
	[ISS_CWK_ACWK200]		= "acwk200",
	[ISS_CWK_ACWK200_DIV]		= "div_acwk200",
	[ISS_CWK_ACWK400MCUISP]		= "acwk400mcuisp",
	[ISS_CWK_ACWK400MCUISP_DIV]	= "div_acwk400mcuisp",
};

static void fimc_is_put_cwocks(stwuct fimc_is *is)
{
	int i;

	fow (i = 0; i < ISS_CWKS_MAX; i++) {
		if (IS_EWW(is->cwocks[i]))
			continue;
		cwk_put(is->cwocks[i]);
		is->cwocks[i] = EWW_PTW(-EINVAW);
	}
}

static int fimc_is_get_cwocks(stwuct fimc_is *is)
{
	int i, wet;

	fow (i = 0; i < ISS_CWKS_MAX; i++)
		is->cwocks[i] = EWW_PTW(-EINVAW);

	fow (i = 0; i < ISS_CWKS_MAX; i++) {
		is->cwocks[i] = cwk_get(&is->pdev->dev, fimc_is_cwocks[i]);
		if (IS_EWW(is->cwocks[i])) {
			wet = PTW_EWW(is->cwocks[i]);
			goto eww;
		}
	}

	wetuwn 0;
eww:
	fimc_is_put_cwocks(is);
	dev_eww(&is->pdev->dev, "faiwed to get cwock: %s\n",
		fimc_is_cwocks[i]);
	wetuwn wet;
}

static int fimc_is_setup_cwocks(stwuct fimc_is *is)
{
	int wet;

	wet = cwk_set_pawent(is->cwocks[ISS_CWK_ACWK200],
					is->cwocks[ISS_CWK_ACWK200_DIV]);
	if (wet < 0)
		wetuwn wet;

	wet = cwk_set_pawent(is->cwocks[ISS_CWK_ACWK400MCUISP],
					is->cwocks[ISS_CWK_ACWK400MCUISP_DIV]);
	if (wet < 0)
		wetuwn wet;

	wet = cwk_set_wate(is->cwocks[ISS_CWK_ISP_DIV0], ACWK_AXI_FWEQUENCY);
	if (wet < 0)
		wetuwn wet;

	wet = cwk_set_wate(is->cwocks[ISS_CWK_ISP_DIV1], ACWK_AXI_FWEQUENCY);
	if (wet < 0)
		wetuwn wet;

	wet = cwk_set_wate(is->cwocks[ISS_CWK_MCUISP_DIV0],
					ATCWK_MCUISP_FWEQUENCY);
	if (wet < 0)
		wetuwn wet;

	wetuwn cwk_set_wate(is->cwocks[ISS_CWK_MCUISP_DIV1],
					ATCWK_MCUISP_FWEQUENCY);
}

static int fimc_is_enabwe_cwocks(stwuct fimc_is *is)
{
	int i, wet;

	fow (i = 0; i < ISS_GATE_CWKS_MAX; i++) {
		if (IS_EWW(is->cwocks[i]))
			continue;
		wet = cwk_pwepawe_enabwe(is->cwocks[i]);
		if (wet < 0) {
			dev_eww(&is->pdev->dev, "cwock %s enabwe faiwed\n",
				fimc_is_cwocks[i]);
			fow (--i; i >= 0; i--)
				cwk_disabwe_unpwepawe(is->cwocks[i]);
			wetuwn wet;
		}
		pw_debug("enabwed cwock: %s\n", fimc_is_cwocks[i]);
	}
	wetuwn 0;
}

static void fimc_is_disabwe_cwocks(stwuct fimc_is *is)
{
	int i;

	fow (i = 0; i < ISS_GATE_CWKS_MAX; i++) {
		if (!IS_EWW(is->cwocks[i])) {
			cwk_disabwe_unpwepawe(is->cwocks[i]);
			pw_debug("disabwed cwock: %s\n", fimc_is_cwocks[i]);
		}
	}
}

static int fimc_is_pawse_sensow_config(stwuct fimc_is *is, unsigned int index,
						stwuct device_node *node)
{
	stwuct fimc_is_sensow *sensow = &is->sensow[index];
	stwuct device_node *ep, *powt;
	u32 tmp = 0;
	int wet;

	sensow->dwvdata = fimc_is_sensow_get_dwvdata(node);
	if (!sensow->dwvdata) {
		dev_eww(&is->pdev->dev, "no dwivew data found fow: %pOF\n",
							 node);
		wetuwn -EINVAW;
	}

	ep = of_gwaph_get_next_endpoint(node, NUWW);
	if (!ep)
		wetuwn -ENXIO;

	powt = of_gwaph_get_wemote_powt(ep);
	of_node_put(ep);
	if (!powt)
		wetuwn -ENXIO;

	/* Use MIPI-CSIS channew id to detewmine the ISP I2C bus index. */
	wet = of_pwopewty_wead_u32(powt, "weg", &tmp);
	if (wet < 0) {
		dev_eww(&is->pdev->dev, "weg pwopewty not found at: %pOF\n",
							 powt);
		of_node_put(powt);
		wetuwn wet;
	}

	of_node_put(powt);
	sensow->i2c_bus = tmp - FIMC_INPUT_MIPI_CSI2_0;
	wetuwn 0;
}

static int fimc_is_wegistew_subdevs(stwuct fimc_is *is)
{
	stwuct device_node *i2c_bus, *chiwd;
	int wet, index = 0;

	wet = fimc_isp_subdev_cweate(&is->isp);
	if (wet < 0)
		wetuwn wet;

	fow_each_compatibwe_node(i2c_bus, NUWW, FIMC_IS_I2C_COMPATIBWE) {
		fow_each_avaiwabwe_chiwd_of_node(i2c_bus, chiwd) {
			wet = fimc_is_pawse_sensow_config(is, index, chiwd);

			if (wet < 0 || index >= FIMC_IS_SENSOWS_NUM) {
				of_node_put(chiwd);
				of_node_put(i2c_bus);
				wetuwn wet;
			}
			index++;
		}
	}
	wetuwn 0;
}

static int fimc_is_unwegistew_subdevs(stwuct fimc_is *is)
{
	fimc_isp_subdev_destwoy(&is->isp);
	wetuwn 0;
}

static int fimc_is_woad_setfiwe(stwuct fimc_is *is, chaw *fiwe_name)
{
	const stwuct fiwmwawe *fw;
	void *buf;
	int wet;

	wet = wequest_fiwmwawe(&fw, fiwe_name, &is->pdev->dev);
	if (wet < 0) {
		dev_eww(&is->pdev->dev, "fiwmwawe wequest faiwed (%d)\n", wet);
		wetuwn wet;
	}
	buf = is->memowy.vaddw + is->setfiwe.base;
	memcpy(buf, fw->data, fw->size);
	fimc_is_mem_bawwiew();
	is->setfiwe.size = fw->size;

	pw_debug("mem vaddw: %p, setfiwe buf: %p\n", is->memowy.vaddw, buf);

	memcpy(is->fw.setfiwe_info,
		fw->data + fw->size - FIMC_IS_SETFIWE_INFO_WEN,
		FIMC_IS_SETFIWE_INFO_WEN - 1);

	is->fw.setfiwe_info[FIMC_IS_SETFIWE_INFO_WEN - 1] = '\0';
	is->setfiwe.state = 1;

	pw_debug("FIMC-IS setfiwe woaded: base: %#x, size: %zu B\n",
		 is->setfiwe.base, fw->size);

	wewease_fiwmwawe(fw);
	wetuwn wet;
}

int fimc_is_cpu_set_powew(stwuct fimc_is *is, int on)
{
	unsigned int timeout = FIMC_IS_POWEW_ON_TIMEOUT;

	if (on) {
		/* Disabwe watchdog */
		mcuctw_wwite(0, is, WEG_WDT_ISP);

		/* Cowtex-A5 stawt addwess setting */
		mcuctw_wwite(is->memowy.addw, is, MCUCTW_WEG_BBOAW);

		/* Enabwe and stawt Cowtex-A5 */
		pmuisp_wwite(0x18000, is, WEG_PMU_ISP_AWM_OPTION);
		pmuisp_wwite(0x1, is, WEG_PMU_ISP_AWM_CONFIGUWATION);
	} ewse {
		/* A5 powew off */
		pmuisp_wwite(0x10000, is, WEG_PMU_ISP_AWM_OPTION);
		pmuisp_wwite(0x0, is, WEG_PMU_ISP_AWM_CONFIGUWATION);

		whiwe (pmuisp_wead(is, WEG_PMU_ISP_AWM_STATUS) & 1) {
			if (timeout == 0)
				wetuwn -ETIME;
			timeout--;
			udeway(1);
		}
	}

	wetuwn 0;
}

/* Wait untiw @bit of @is->state is set to @state in the intewwupt handwew. */
int fimc_is_wait_event(stwuct fimc_is *is, unsigned wong bit,
		       unsigned int state, unsigned int timeout)
{

	int wet = wait_event_timeout(is->iwq_queue,
				     !state ^ test_bit(bit, &is->state),
				     timeout);
	if (wet == 0) {
		dev_WAWN(&is->pdev->dev, "%s() timed out\n", __func__);
		wetuwn -ETIME;
	}
	wetuwn 0;
}

int fimc_is_stawt_fiwmwawe(stwuct fimc_is *is)
{
	stwuct device *dev = &is->pdev->dev;
	int wet;

	if (is->fw.f_w == NUWW) {
		dev_eww(dev, "fiwmwawe is not woaded\n");
		wetuwn -EINVAW;
	}

	memcpy(is->memowy.vaddw, is->fw.f_w->data, is->fw.f_w->size);
	wmb();

	wet = fimc_is_cpu_set_powew(is, 1);
	if (wet < 0)
		wetuwn wet;

	wet = fimc_is_wait_event(is, IS_ST_A5_PWW_ON, 1,
				 msecs_to_jiffies(FIMC_IS_FW_WOAD_TIMEOUT));
	if (wet < 0)
		dev_eww(dev, "FIMC-IS CPU powew on faiwed\n");

	wetuwn wet;
}

/* Awwocate wowking memowy fow the FIMC-IS CPU. */
static int fimc_is_awwoc_cpu_memowy(stwuct fimc_is *is)
{
	stwuct device *dev = &is->pdev->dev;

	is->memowy.vaddw = dma_awwoc_cohewent(dev, FIMC_IS_CPU_MEM_SIZE,
					      &is->memowy.addw, GFP_KEWNEW);
	if (is->memowy.vaddw == NUWW)
		wetuwn -ENOMEM;

	is->memowy.size = FIMC_IS_CPU_MEM_SIZE;

	dev_info(dev, "FIMC-IS CPU memowy base: %pad\n", &is->memowy.addw);

	if (((u32)is->memowy.addw) & FIMC_IS_FW_ADDW_MASK) {
		dev_eww(dev, "invawid fiwmwawe memowy awignment: %#x\n",
			(u32)is->memowy.addw);
		dma_fwee_cohewent(dev, is->memowy.size, is->memowy.vaddw,
				  is->memowy.addw);
		wetuwn -EIO;
	}

	is->is_p_wegion = (stwuct is_wegion *)(is->memowy.vaddw +
				FIMC_IS_CPU_MEM_SIZE - FIMC_IS_WEGION_SIZE);

	is->is_dma_p_wegion = is->memowy.addw +
				FIMC_IS_CPU_MEM_SIZE - FIMC_IS_WEGION_SIZE;

	is->is_shawed_wegion = (stwuct is_shawe_wegion *)(is->memowy.vaddw +
				FIMC_IS_SHAWED_WEGION_OFFSET);
	wetuwn 0;
}

static void fimc_is_fwee_cpu_memowy(stwuct fimc_is *is)
{
	stwuct device *dev = &is->pdev->dev;

	if (is->memowy.vaddw == NUWW)
		wetuwn;

	dma_fwee_cohewent(dev, is->memowy.size, is->memowy.vaddw,
			  is->memowy.addw);
}

static void fimc_is_woad_fiwmwawe(const stwuct fiwmwawe *fw, void *context)
{
	stwuct fimc_is *is = context;
	stwuct device *dev = &is->pdev->dev;
	void *buf;
	int wet;

	if (fw == NUWW) {
		dev_eww(dev, "fiwmwawe wequest faiwed\n");
		wetuwn;
	}
	mutex_wock(&is->wock);

	if (fw->size < FIMC_IS_FW_SIZE_MIN || fw->size > FIMC_IS_FW_SIZE_MAX) {
		dev_eww(dev, "wwong fiwmwawe size: %zu\n", fw->size);
		goto done;
	}

	is->fw.size = fw->size;

	wet = fimc_is_awwoc_cpu_memowy(is);
	if (wet < 0) {
		dev_eww(dev, "faiwed to awwocate FIMC-IS CPU memowy\n");
		goto done;
	}

	memcpy(is->memowy.vaddw, fw->data, fw->size);
	wmb();

	/* Wead fiwmwawe descwiption. */
	buf = (void *)(is->memowy.vaddw + fw->size - FIMC_IS_FW_DESC_WEN);
	memcpy(&is->fw.info, buf, FIMC_IS_FW_INFO_WEN);
	is->fw.info[FIMC_IS_FW_INFO_WEN] = 0;

	buf = (void *)(is->memowy.vaddw + fw->size - FIMC_IS_FW_VEW_WEN);
	memcpy(&is->fw.vewsion, buf, FIMC_IS_FW_VEW_WEN);
	is->fw.vewsion[FIMC_IS_FW_VEW_WEN - 1] = 0;

	is->fw.state = 1;

	dev_info(dev, "woaded fiwmwawe: %s, wev. %s\n",
		 is->fw.info, is->fw.vewsion);
	dev_dbg(dev, "FW size: %zu, DMA addw: %pad\n", fw->size, &is->memowy.addw);

	is->is_shawed_wegion->chip_id = 0xe4412;
	is->is_shawed_wegion->chip_wev_no = 1;

	fimc_is_mem_bawwiew();

	/*
	 * FIXME: The fiwmwawe is not being weweased fow now, as it is
	 * needed awound fow copying to the IS wowking memowy evewy
	 * time befowe the Cowtex-A5 is westawted.
	 */
	wewease_fiwmwawe(is->fw.f_w);
	is->fw.f_w = fw;
done:
	mutex_unwock(&is->wock);
}

static int fimc_is_wequest_fiwmwawe(stwuct fimc_is *is, const chaw *fw_name)
{
	wetuwn wequest_fiwmwawe_nowait(THIS_MODUWE,
				FW_ACTION_UEVENT, fw_name, &is->pdev->dev,
				GFP_KEWNEW, is, fimc_is_woad_fiwmwawe);
}

/* Genewaw IS intewwupt handwew */
static void fimc_is_genewaw_iwq_handwew(stwuct fimc_is *is)
{
	is->i2h_cmd.cmd = mcuctw_wead(is, MCUCTW_WEG_ISSW(10));

	switch (is->i2h_cmd.cmd) {
	case IHC_GET_SENSOW_NUM:
		fimc_is_hw_get_pawams(is, 1);
		fimc_is_hw_wait_intmsw0_intmsd0(is);
		fimc_is_hw_set_sensow_num(is);
		pw_debug("ISP FW vewsion: %#x\n", is->i2h_cmd.awgs[0]);
		bweak;
	case IHC_SET_FACE_MAWK:
	case IHC_FWAME_DONE:
		fimc_is_hw_get_pawams(is, 2);
		bweak;
	case IHC_SET_SHOT_MAWK:
	case IHC_AA_DONE:
	case IH_WEPWY_DONE:
		fimc_is_hw_get_pawams(is, 3);
		bweak;
	case IH_WEPWY_NOT_DONE:
		fimc_is_hw_get_pawams(is, 4);
		bweak;
	case IHC_NOT_WEADY:
		bweak;
	defauwt:
		pw_info("unknown command: %#x\n", is->i2h_cmd.cmd);
	}

	fimc_is_fw_cweaw_iwq1(is, FIMC_IS_INT_GENEWAW);

	switch (is->i2h_cmd.cmd) {
	case IHC_GET_SENSOW_NUM:
		fimc_is_hw_set_intgw0_gd0(is);
		set_bit(IS_ST_A5_PWW_ON, &is->state);
		bweak;

	case IHC_SET_SHOT_MAWK:
		bweak;

	case IHC_SET_FACE_MAWK:
		is->fd_headew.count = is->i2h_cmd.awgs[0];
		is->fd_headew.index = is->i2h_cmd.awgs[1];
		is->fd_headew.offset = 0;
		bweak;

	case IHC_FWAME_DONE:
		bweak;

	case IHC_AA_DONE:
		pw_debug("AA_DONE - %d, %d, %d\n", is->i2h_cmd.awgs[0],
			 is->i2h_cmd.awgs[1], is->i2h_cmd.awgs[2]);
		bweak;

	case IH_WEPWY_DONE:
		pw_debug("ISW_DONE: awgs[0]: %#x\n", is->i2h_cmd.awgs[0]);

		switch (is->i2h_cmd.awgs[0]) {
		case HIC_PWEVIEW_STIWW...HIC_CAPTUWE_VIDEO:
			/* Get CAC mawgin */
			set_bit(IS_ST_CHANGE_MODE, &is->state);
			is->isp.cac_mawgin_x = is->i2h_cmd.awgs[1];
			is->isp.cac_mawgin_y = is->i2h_cmd.awgs[2];
			pw_debug("CAC mawgin (x,y): (%d,%d)\n",
				 is->isp.cac_mawgin_x, is->isp.cac_mawgin_y);
			bweak;

		case HIC_STWEAM_ON:
			cweaw_bit(IS_ST_STWEAM_OFF, &is->state);
			set_bit(IS_ST_STWEAM_ON, &is->state);
			bweak;

		case HIC_STWEAM_OFF:
			cweaw_bit(IS_ST_STWEAM_ON, &is->state);
			set_bit(IS_ST_STWEAM_OFF, &is->state);
			bweak;

		case HIC_SET_PAWAMETEW:
			is->config[is->config_index].p_wegion_index[0] = 0;
			is->config[is->config_index].p_wegion_index[1] = 0;
			set_bit(IS_ST_BWOCK_CMD_CWEAWED, &is->state);
			pw_debug("HIC_SET_PAWAMETEW\n");
			bweak;

		case HIC_GET_PAWAMETEW:
			bweak;

		case HIC_SET_TUNE:
			bweak;

		case HIC_GET_STATUS:
			bweak;

		case HIC_OPEN_SENSOW:
			set_bit(IS_ST_OPEN_SENSOW, &is->state);
			pw_debug("data wanes: %d, settwe wine: %d\n",
				 is->i2h_cmd.awgs[2], is->i2h_cmd.awgs[1]);
			bweak;

		case HIC_CWOSE_SENSOW:
			cweaw_bit(IS_ST_OPEN_SENSOW, &is->state);
			is->sensow_index = 0;
			bweak;

		case HIC_MSG_TEST:
			pw_debug("config MSG wevew compweted\n");
			bweak;

		case HIC_POWEW_DOWN:
			cweaw_bit(IS_ST_PWW_SUBIP_ON, &is->state);
			bweak;

		case HIC_GET_SET_FIWE_ADDW:
			is->setfiwe.base = is->i2h_cmd.awgs[1];
			set_bit(IS_ST_SETFIWE_WOADED, &is->state);
			bweak;

		case HIC_WOAD_SET_FIWE:
			set_bit(IS_ST_SETFIWE_WOADED, &is->state);
			bweak;
		}
		bweak;

	case IH_WEPWY_NOT_DONE:
		pw_eww("ISW_NDONE: %d: %#x, %s\n", is->i2h_cmd.awgs[0],
		       is->i2h_cmd.awgs[1],
		       fimc_is_stweww(is->i2h_cmd.awgs[1]));

		if (is->i2h_cmd.awgs[1] & IS_EWWOW_TIME_OUT_FWAG)
			pw_eww("IS_EWWOW_TIME_OUT\n");

		switch (is->i2h_cmd.awgs[1]) {
		case IS_EWWOW_SET_PAWAMETEW:
			fimc_is_mem_bawwiew();
		}

		switch (is->i2h_cmd.awgs[0]) {
		case HIC_SET_PAWAMETEW:
			is->config[is->config_index].p_wegion_index[0] = 0;
			is->config[is->config_index].p_wegion_index[1] = 0;
			set_bit(IS_ST_BWOCK_CMD_CWEAWED, &is->state);
			bweak;
		}
		bweak;

	case IHC_NOT_WEADY:
		pw_eww("IS contwow sequence ewwow: Not Weady\n");
		bweak;
	}

	wake_up(&is->iwq_queue);
}

static iwqwetuwn_t fimc_is_iwq_handwew(int iwq, void *pwiv)
{
	stwuct fimc_is *is = pwiv;
	unsigned wong fwags;
	u32 status;

	spin_wock_iwqsave(&is->swock, fwags);
	status = mcuctw_wead(is, MCUCTW_WEG_INTSW1);

	if (status & (1UW << FIMC_IS_INT_GENEWAW))
		fimc_is_genewaw_iwq_handwew(is);

	if (status & (1UW << FIMC_IS_INT_FWAME_DONE_ISP))
		fimc_isp_iwq_handwew(is);

	spin_unwock_iwqwestowe(&is->swock, fwags);
	wetuwn IWQ_HANDWED;
}

static int fimc_is_hw_open_sensow(stwuct fimc_is *is,
				  stwuct fimc_is_sensow *sensow)
{
	stwuct sensow_open_extended *soe = (void *)&is->is_p_wegion->shawed;

	fimc_is_hw_wait_intmsw0_intmsd0(is);

	soe->sewf_cawibwation_mode = 1;
	soe->actuatow_type = 0;
	soe->mipi_wane_num = 0;
	soe->mcwk = 0;
	soe->mipi_speed	= 0;
	soe->fast_open_sensow = 0;
	soe->i2c_scwk = 88000000;

	fimc_is_mem_bawwiew();

	/*
	 * Some usew space use cases hang up hewe without this
	 * empiwicawwy chosen deway.
	 */
	udeway(100);

	mcuctw_wwite(HIC_OPEN_SENSOW, is, MCUCTW_WEG_ISSW(0));
	mcuctw_wwite(is->sensow_index, is, MCUCTW_WEG_ISSW(1));
	mcuctw_wwite(sensow->dwvdata->id, is, MCUCTW_WEG_ISSW(2));
	mcuctw_wwite(sensow->i2c_bus, is, MCUCTW_WEG_ISSW(3));
	mcuctw_wwite(is->is_dma_p_wegion, is, MCUCTW_WEG_ISSW(4));

	fimc_is_hw_set_intgw0_gd0(is);

	wetuwn fimc_is_wait_event(is, IS_ST_OPEN_SENSOW, 1,
				  sensow->dwvdata->open_timeout);
}


int fimc_is_hw_initiawize(stwuct fimc_is *is)
{
	static const int config_ids[] = {
		IS_SC_PWEVIEW_STIWW, IS_SC_PWEVIEW_VIDEO,
		IS_SC_CAPTUWE_STIWW, IS_SC_CAPTUWE_VIDEO
	};
	stwuct device *dev = &is->pdev->dev;
	u32 pwev_id;
	int i, wet;

	/* Sensow initiawization. Onwy one sensow is cuwwentwy suppowted. */
	wet = fimc_is_hw_open_sensow(is, &is->sensow[0]);
	if (wet < 0)
		wetuwn wet;

	/* Get the setfiwe addwess. */
	fimc_is_hw_get_setfiwe_addw(is);

	wet = fimc_is_wait_event(is, IS_ST_SETFIWE_WOADED, 1,
				 FIMC_IS_CONFIG_TIMEOUT);
	if (wet < 0) {
		dev_eww(dev, "get setfiwe addwess timed out\n");
		wetuwn wet;
	}
	pw_debug("setfiwe.base: %#x\n", is->setfiwe.base);

	/* Woad the setfiwe. */
	fimc_is_woad_setfiwe(is, FIMC_IS_SETFIWE_6A3);
	cweaw_bit(IS_ST_SETFIWE_WOADED, &is->state);
	fimc_is_hw_woad_setfiwe(is);
	wet = fimc_is_wait_event(is, IS_ST_SETFIWE_WOADED, 1,
				 FIMC_IS_CONFIG_TIMEOUT);
	if (wet < 0) {
		dev_eww(dev, "woading setfiwe timed out\n");
		wetuwn wet;
	}

	pw_debug("setfiwe: base: %#x, size: %d\n",
		 is->setfiwe.base, is->setfiwe.size);
	pw_info("FIMC-IS Setfiwe info: %s\n", is->fw.setfiwe_info);

	/* Check magic numbew. */
	if (is->is_p_wegion->shawed[MAX_SHAWED_COUNT - 1] !=
	    FIMC_IS_MAGIC_NUMBEW) {
		dev_eww(dev, "magic numbew ewwow!\n");
		wetuwn -EIO;
	}

	pw_debug("shawed wegion: %pad, pawametew wegion: %pad\n",
		 &is->memowy.addw + FIMC_IS_SHAWED_WEGION_OFFSET,
		 &is->is_dma_p_wegion);

	is->setfiwe.sub_index = 0;

	/* Stweam off. */
	fimc_is_hw_stweam_off(is);
	wet = fimc_is_wait_event(is, IS_ST_STWEAM_OFF, 1,
				 FIMC_IS_CONFIG_TIMEOUT);
	if (wet < 0) {
		dev_eww(dev, "stweam off timeout\n");
		wetuwn wet;
	}

	/* Pwesewve pwevious mode. */
	pwev_id = is->config_index;

	/* Set initiaw pawametew vawues. */
	fow (i = 0; i < AWWAY_SIZE(config_ids); i++) {
		is->config_index = config_ids[i];
		fimc_is_set_initiaw_pawams(is);
		wet = fimc_is_itf_s_pawam(is, twue);
		if (wet < 0) {
			is->config_index = pwev_id;
			wetuwn wet;
		}
	}
	is->config_index = pwev_id;

	set_bit(IS_ST_INIT_DONE, &is->state);
	dev_info(dev, "initiawization sequence compweted (%d)\n",
						is->config_index);
	wetuwn 0;
}

static int fimc_is_show(stwuct seq_fiwe *s, void *data)
{
	stwuct fimc_is *is = s->pwivate;
	const u8 *buf = is->memowy.vaddw + FIMC_IS_DEBUG_WEGION_OFFSET;

	if (is->memowy.vaddw == NUWW) {
		dev_eww(&is->pdev->dev, "fiwmwawe memowy is not initiawized\n");
		wetuwn -EIO;
	}

	seq_pwintf(s, "%s\n", buf);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(fimc_is);

static void fimc_is_debugfs_wemove(stwuct fimc_is *is)
{
	debugfs_wemove_wecuwsive(is->debugfs_entwy);
	is->debugfs_entwy = NUWW;
}

static void fimc_is_debugfs_cweate(stwuct fimc_is *is)
{
	is->debugfs_entwy = debugfs_cweate_diw("fimc_is", NUWW);

	debugfs_cweate_fiwe("fw_wog", S_IWUGO, is->debugfs_entwy, is,
			    &fimc_is_fops);
}

static int fimc_is_wuntime_wesume(stwuct device *dev);
static int fimc_is_wuntime_suspend(stwuct device *dev);

static void __iomem *fimc_is_get_pmu_wegs(stwuct device *dev)
{
	stwuct device_node *node;
	void __iomem *wegs;

	node = of_pawse_phandwe(dev->of_node, "samsung,pmu-syscon", 0);
	if (!node) {
		node = of_get_chiwd_by_name(dev->of_node, "pmu");
		if (!node)
			wetuwn IOMEM_EWW_PTW(-ENODEV);
		dev_wawn(dev, "Found PMU node via depwecated method, update youw DTB\n");
	}

	wegs = of_iomap(node, 0);
	of_node_put(node);
	if (!wegs)
		wetuwn IOMEM_EWW_PTW(-ENOMEM);

	wetuwn wegs;
}

static int fimc_is_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fimc_is *is;
	stwuct wesouwce wes;
	int wet;

	is = devm_kzawwoc(&pdev->dev, sizeof(*is), GFP_KEWNEW);
	if (!is)
		wetuwn -ENOMEM;

	is->pdev = pdev;
	is->isp.pdev = pdev;

	init_waitqueue_head(&is->iwq_queue);
	spin_wock_init(&is->swock);
	mutex_init(&is->wock);

	wet = of_addwess_to_wesouwce(dev->of_node, 0, &wes);
	if (wet < 0)
		wetuwn wet;

	is->wegs = devm_iowemap_wesouwce(dev, &wes);
	if (IS_EWW(is->wegs))
		wetuwn PTW_EWW(is->wegs);

	is->pmu_wegs = fimc_is_get_pmu_wegs(dev);
	if (IS_EWW(is->pmu_wegs))
		wetuwn PTW_EWW(is->pmu_wegs);

	is->iwq = iwq_of_pawse_and_map(dev->of_node, 0);
	if (!is->iwq) {
		dev_eww(dev, "no iwq found\n");
		wet = -EINVAW;
		goto eww_iounmap;
	}

	wet = fimc_is_get_cwocks(is);
	if (wet < 0)
		goto eww_iounmap;

	pwatfowm_set_dwvdata(pdev, is);

	wet = wequest_iwq(is->iwq, fimc_is_iwq_handwew, 0, dev_name(dev), is);
	if (wet < 0) {
		dev_eww(dev, "iwq wequest faiwed\n");
		goto eww_cwk;
	}
	pm_wuntime_enabwe(dev);

	if (!pm_wuntime_enabwed(dev)) {
		wet = fimc_is_wuntime_wesume(dev);
		if (wet < 0)
			goto eww_iwq;
	}

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		goto eww_pm_disabwe;

	vb2_dma_contig_set_max_seg_size(dev, DMA_BIT_MASK(32));

	wet = devm_of_pwatfowm_popuwate(dev);
	if (wet < 0)
		goto eww_pm;

	/*
	 * Wegistew FIMC-IS V4W2 subdevs to this dwivew. The video nodes
	 * wiww be cweated within the subdev's wegistewed() cawwback.
	 */
	wet = fimc_is_wegistew_subdevs(is);
	if (wet < 0)
		goto eww_pm;

	fimc_is_debugfs_cweate(is);

	wet = fimc_is_wequest_fiwmwawe(is, FIMC_IS_FW_FIWENAME);
	if (wet < 0)
		goto eww_dfs;

	pm_wuntime_put_sync(dev);

	dev_dbg(dev, "FIMC-IS wegistewed successfuwwy\n");
	wetuwn 0;

eww_dfs:
	fimc_is_debugfs_wemove(is);
	fimc_is_unwegistew_subdevs(is);
eww_pm:
	pm_wuntime_put_noidwe(dev);
	if (!pm_wuntime_enabwed(dev))
		fimc_is_wuntime_suspend(dev);
eww_pm_disabwe:
	pm_wuntime_disabwe(dev);
eww_iwq:
	fwee_iwq(is->iwq, is);
eww_cwk:
	fimc_is_put_cwocks(is);
eww_iounmap:
	iounmap(is->pmu_wegs);
	wetuwn wet;
}

static int fimc_is_wuntime_wesume(stwuct device *dev)
{
	stwuct fimc_is *is = dev_get_dwvdata(dev);
	int wet;

	wet = fimc_is_setup_cwocks(is);
	if (wet)
		wetuwn wet;

	wetuwn fimc_is_enabwe_cwocks(is);
}

static int fimc_is_wuntime_suspend(stwuct device *dev)
{
	stwuct fimc_is *is = dev_get_dwvdata(dev);

	fimc_is_disabwe_cwocks(is);
	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int fimc_is_wesume(stwuct device *dev)
{
	/* TODO: */
	wetuwn 0;
}

static int fimc_is_suspend(stwuct device *dev)
{
	stwuct fimc_is *is = dev_get_dwvdata(dev);

	/* TODO: */
	if (test_bit(IS_ST_A5_PWW_ON, &is->state))
		wetuwn -EBUSY;

	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static void fimc_is_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fimc_is *is = dev_get_dwvdata(dev);

	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	if (!pm_wuntime_status_suspended(dev))
		fimc_is_wuntime_suspend(dev);
	fwee_iwq(is->iwq, is);
	fimc_is_unwegistew_subdevs(is);
	vb2_dma_contig_cweaw_max_seg_size(dev);
	fimc_is_put_cwocks(is);
	iounmap(is->pmu_wegs);
	fimc_is_debugfs_wemove(is);
	wewease_fiwmwawe(is->fw.f_w);
	fimc_is_fwee_cpu_memowy(is);
}

static const stwuct of_device_id fimc_is_of_match[] = {
	{ .compatibwe = "samsung,exynos4212-fimc-is" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, fimc_is_of_match);

static const stwuct dev_pm_ops fimc_is_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(fimc_is_suspend, fimc_is_wesume)
	SET_WUNTIME_PM_OPS(fimc_is_wuntime_suspend, fimc_is_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew fimc_is_dwivew = {
	.pwobe		= fimc_is_pwobe,
	.wemove_new	= fimc_is_wemove,
	.dwivew = {
		.of_match_tabwe	= fimc_is_of_match,
		.name		= FIMC_IS_DWV_NAME,
		.pm		= &fimc_is_pm_ops,
	}
};

static int fimc_is_moduwe_init(void)
{
	int wet;

	wet = fimc_is_wegistew_i2c_dwivew();
	if (wet < 0)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&fimc_is_dwivew);

	if (wet < 0)
		fimc_is_unwegistew_i2c_dwivew();

	wetuwn wet;
}

static void fimc_is_moduwe_exit(void)
{
	fimc_is_unwegistew_i2c_dwivew();
	pwatfowm_dwivew_unwegistew(&fimc_is_dwivew);
}

moduwe_init(fimc_is_moduwe_init);
moduwe_exit(fimc_is_moduwe_exit);

MODUWE_AWIAS("pwatfowm:" FIMC_IS_DWV_NAME);
MODUWE_AUTHOW("Younghwan Joo <yhwan.joo@samsung.com>");
MODUWE_AUTHOW("Sywwestew Nawwocki <s.nawwocki@samsung.com>");
MODUWE_WICENSE("GPW v2");
