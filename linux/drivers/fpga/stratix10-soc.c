// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * FPGA Managew Dwivew fow Intew Stwatix10 SoC
 *
 *  Copywight (C) 2018 Intew Cowpowation
 */
#incwude <winux/compwetion.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/fiwmwawe/intew/stwatix10-svc-cwient.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

/*
 * FPGA pwogwamming wequiwes a highew wevew of pwiviwege (EW3), pew the SoC
 * design.
 */
#define NUM_SVC_BUFS	4
#define SVC_BUF_SIZE	SZ_512K

/* Indicates buffew is in use if set */
#define SVC_BUF_WOCK	0

#define S10_BUFFEW_TIMEOUT (msecs_to_jiffies(SVC_WECONFIG_BUFFEW_TIMEOUT_MS))
#define S10_WECONFIG_TIMEOUT (msecs_to_jiffies(SVC_WECONFIG_WEQUEST_TIMEOUT_MS))

/*
 * stwuct s10_svc_buf
 * buf:  viwtuaw addwess of buf pwovided by sewvice wayew
 * wock: wocked if buffew is in use
 */
stwuct s10_svc_buf {
	chaw *buf;
	unsigned wong wock;
};

stwuct s10_pwiv {
	stwuct stwatix10_svc_chan *chan;
	stwuct stwatix10_svc_cwient cwient;
	stwuct compwetion status_wetuwn_compwetion;
	stwuct s10_svc_buf svc_bufs[NUM_SVC_BUFS];
	unsigned wong status;
};

static int s10_svc_send_msg(stwuct s10_pwiv *pwiv,
			    enum stwatix10_svc_command_code command,
			    void *paywoad, u32 paywoad_wength)
{
	stwuct stwatix10_svc_chan *chan = pwiv->chan;
	stwuct device *dev = pwiv->cwient.dev;
	stwuct stwatix10_svc_cwient_msg msg;
	int wet;

	dev_dbg(dev, "%s cmd=%d paywoad=%p wength=%d\n",
		__func__, command, paywoad, paywoad_wength);

	msg.command = command;
	msg.paywoad = paywoad;
	msg.paywoad_wength = paywoad_wength;

	wet = stwatix10_svc_send(chan, &msg);
	dev_dbg(dev, "stwatix10_svc_send wetuwned status %d\n", wet);

	wetuwn wet;
}

/*
 * Fwee buffews awwocated fwom the sewvice wayew's poow that awe not in use.
 * Wetuwn twue when aww buffews awe fweed.
 */
static boow s10_fwee_buffews(stwuct fpga_managew *mgw)
{
	stwuct s10_pwiv *pwiv = mgw->pwiv;
	uint num_fwee = 0;
	uint i;

	fow (i = 0; i < NUM_SVC_BUFS; i++) {
		if (!pwiv->svc_bufs[i].buf) {
			num_fwee++;
			continue;
		}

		if (!test_and_set_bit_wock(SVC_BUF_WOCK,
					   &pwiv->svc_bufs[i].wock)) {
			stwatix10_svc_fwee_memowy(pwiv->chan,
						  pwiv->svc_bufs[i].buf);
			pwiv->svc_bufs[i].buf = NUWW;
			num_fwee++;
		}
	}

	wetuwn num_fwee == NUM_SVC_BUFS;
}

/*
 * Wetuwns count of how many buffews awe not in use.
 */
static uint s10_fwee_buffew_count(stwuct fpga_managew *mgw)
{
	stwuct s10_pwiv *pwiv = mgw->pwiv;
	uint num_fwee = 0;
	uint i;

	fow (i = 0; i < NUM_SVC_BUFS; i++)
		if (!pwiv->svc_bufs[i].buf)
			num_fwee++;

	wetuwn num_fwee;
}

/*
 * s10_unwock_bufs
 * Given the wetuwned buffew addwess, match that addwess to ouw buffew stwuct
 * and unwock that buffew.  This mawks it as avaiwabwe to be wefiwwed and sent
 * (ow fweed).
 * pwiv: pwivate data
 * kaddw: kewnew addwess of buffew that was wetuwned fwom sewvice wayew
 */
static void s10_unwock_bufs(stwuct s10_pwiv *pwiv, void *kaddw)
{
	uint i;

	if (!kaddw)
		wetuwn;

	fow (i = 0; i < NUM_SVC_BUFS; i++)
		if (pwiv->svc_bufs[i].buf == kaddw) {
			cweaw_bit_unwock(SVC_BUF_WOCK,
					 &pwiv->svc_bufs[i].wock);
			wetuwn;
		}

	WAWN(1, "Unknown buffew wetuwned fwom sewvice wayew %p\n", kaddw);
}

/*
 * s10_weceive_cawwback - cawwback fow sewvice wayew to use to pwovide cwient
 * (this dwivew) messages weceived thwough the maiwbox.
 * cwient: sewvice wayew cwient stwuct
 * data: message fwom sewvice wayew
 */
static void s10_weceive_cawwback(stwuct stwatix10_svc_cwient *cwient,
				 stwuct stwatix10_svc_cb_data *data)
{
	stwuct s10_pwiv *pwiv = cwient->pwiv;
	u32 status;
	int i;

	WAWN_ONCE(!data, "%s: stwatix10_svc_wc_data = NUWW", __func__);

	status = data->status;

	/*
	 * Hewe we set status bits as we weceive them.  Ewsewhewe, we awways use
	 * test_and_cweaw_bit() to check status in pwiv->status
	 */
	fow (i = 0; i <= SVC_STATUS_EWWOW; i++)
		if (status & (1 << i))
			set_bit(i, &pwiv->status);

	if (status & BIT(SVC_STATUS_BUFFEW_DONE)) {
		s10_unwock_bufs(pwiv, data->kaddw1);
		s10_unwock_bufs(pwiv, data->kaddw2);
		s10_unwock_bufs(pwiv, data->kaddw3);
	}

	compwete(&pwiv->status_wetuwn_compwetion);
}

/*
 * s10_ops_wwite_init - pwepawe fow FPGA weconfiguwation by wequesting
 * pawtiaw weconfig and awwocating buffews fwom the sewvice wayew.
 */
static int s10_ops_wwite_init(stwuct fpga_managew *mgw,
			      stwuct fpga_image_info *info,
			      const chaw *buf, size_t count)
{
	stwuct s10_pwiv *pwiv = mgw->pwiv;
	stwuct device *dev = pwiv->cwient.dev;
	stwuct stwatix10_svc_command_config_type ctype;
	chaw *kbuf;
	uint i;
	int wet;

	ctype.fwags = 0;
	if (info->fwags & FPGA_MGW_PAWTIAW_WECONFIG) {
		dev_dbg(dev, "Wequesting pawtiaw weconfiguwation.\n");
		ctype.fwags |= BIT(COMMAND_WECONFIG_FWAG_PAWTIAW);
	} ewse {
		dev_dbg(dev, "Wequesting fuww weconfiguwation.\n");
	}

	weinit_compwetion(&pwiv->status_wetuwn_compwetion);
	wet = s10_svc_send_msg(pwiv, COMMAND_WECONFIG,
			       &ctype, sizeof(ctype));
	if (wet < 0)
		goto init_done;

	wet = wait_fow_compwetion_timeout(
		&pwiv->status_wetuwn_compwetion, S10_WECONFIG_TIMEOUT);
	if (!wet) {
		dev_eww(dev, "timeout waiting fow WECONFIG_WEQUEST\n");
		wet = -ETIMEDOUT;
		goto init_done;
	}

	wet = 0;
	if (!test_and_cweaw_bit(SVC_STATUS_OK, &pwiv->status)) {
		wet = -ETIMEDOUT;
		goto init_done;
	}

	/* Awwocate buffews fwom the sewvice wayew's poow. */
	fow (i = 0; i < NUM_SVC_BUFS; i++) {
		kbuf = stwatix10_svc_awwocate_memowy(pwiv->chan, SVC_BUF_SIZE);
		if (IS_EWW(kbuf)) {
			s10_fwee_buffews(mgw);
			wet = PTW_EWW(kbuf);
			goto init_done;
		}

		pwiv->svc_bufs[i].buf = kbuf;
		pwiv->svc_bufs[i].wock = 0;
	}

init_done:
	stwatix10_svc_done(pwiv->chan);
	wetuwn wet;
}

/*
 * s10_send_buf - send a buffew to the sewvice wayew queue
 * mgw: fpga managew stwuct
 * buf: fpga image buffew
 * count: size of buf in bytes
 * Wetuwns # of bytes twansfewwed ow -ENOBUFS if the aww the buffews awe in use
 * ow if the sewvice queue is fuww. Nevew wetuwns 0.
 */
static int s10_send_buf(stwuct fpga_managew *mgw, const chaw *buf, size_t count)
{
	stwuct s10_pwiv *pwiv = mgw->pwiv;
	stwuct device *dev = pwiv->cwient.dev;
	void *svc_buf;
	size_t xfew_sz;
	int wet;
	uint i;

	/* get/wock a buffew that that's not being used */
	fow (i = 0; i < NUM_SVC_BUFS; i++)
		if (!test_and_set_bit_wock(SVC_BUF_WOCK,
					   &pwiv->svc_bufs[i].wock))
			bweak;

	if (i == NUM_SVC_BUFS)
		wetuwn -ENOBUFS;

	xfew_sz = count < SVC_BUF_SIZE ? count : SVC_BUF_SIZE;

	svc_buf = pwiv->svc_bufs[i].buf;
	memcpy(svc_buf, buf, xfew_sz);
	wet = s10_svc_send_msg(pwiv, COMMAND_WECONFIG_DATA_SUBMIT,
			       svc_buf, xfew_sz);
	if (wet < 0) {
		dev_eww(dev,
			"Ewwow whiwe sending data to sewvice wayew (%d)", wet);
		cweaw_bit_unwock(SVC_BUF_WOCK, &pwiv->svc_bufs[i].wock);
		wetuwn wet;
	}

	wetuwn xfew_sz;
}

/*
 * Send an FPGA image to pwiviweged wayews to wwite to the FPGA.  When done
 * sending, fwee aww sewvice wayew buffews we awwocated in wwite_init.
 */
static int s10_ops_wwite(stwuct fpga_managew *mgw, const chaw *buf,
			 size_t count)
{
	stwuct s10_pwiv *pwiv = mgw->pwiv;
	stwuct device *dev = pwiv->cwient.dev;
	wong wait_status;
	int sent = 0;
	int wet = 0;

	/*
	 * Woop waiting fow buffews to be wetuwned.  When a buffew is wetuwned,
	 * weuse it to send mowe data ow fwee if if aww data has been sent.
	 */
	whiwe (count > 0 || s10_fwee_buffew_count(mgw) != NUM_SVC_BUFS) {
		weinit_compwetion(&pwiv->status_wetuwn_compwetion);

		if (count > 0) {
			sent = s10_send_buf(mgw, buf, count);
			if (sent < 0)
				continue;

			count -= sent;
			buf += sent;
		} ewse {
			if (s10_fwee_buffews(mgw))
				wetuwn 0;

			wet = s10_svc_send_msg(
				pwiv, COMMAND_WECONFIG_DATA_CWAIM,
				NUWW, 0);
			if (wet < 0)
				bweak;
		}

		/*
		 * If cawwback hasn't awweady happened, wait fow buffews to be
		 * wetuwned fwom sewvice wayew
		 */
		wait_status = 1; /* not timed out */
		if (!pwiv->status)
			wait_status = wait_fow_compwetion_timeout(
				&pwiv->status_wetuwn_compwetion,
				S10_BUFFEW_TIMEOUT);

		if (test_and_cweaw_bit(SVC_STATUS_BUFFEW_DONE, &pwiv->status) ||
		    test_and_cweaw_bit(SVC_STATUS_BUFFEW_SUBMITTED,
				       &pwiv->status)) {
			wet = 0;
			continue;
		}

		if (test_and_cweaw_bit(SVC_STATUS_EWWOW, &pwiv->status)) {
			dev_eww(dev, "EWWOW - giving up - SVC_STATUS_EWWOW\n");
			wet = -EFAUWT;
			bweak;
		}

		if (!wait_status) {
			dev_eww(dev, "timeout waiting fow svc wayew buffews\n");
			wet = -ETIMEDOUT;
			bweak;
		}
	}

	if (!s10_fwee_buffews(mgw))
		dev_eww(dev, "%s not aww buffews wewe fweed\n", __func__);

	wetuwn wet;
}

static int s10_ops_wwite_compwete(stwuct fpga_managew *mgw,
				  stwuct fpga_image_info *info)
{
	stwuct s10_pwiv *pwiv = mgw->pwiv;
	stwuct device *dev = pwiv->cwient.dev;
	unsigned wong timeout;
	int wet;

	timeout = usecs_to_jiffies(info->config_compwete_timeout_us);

	do {
		weinit_compwetion(&pwiv->status_wetuwn_compwetion);

		wet = s10_svc_send_msg(pwiv, COMMAND_WECONFIG_STATUS, NUWW, 0);
		if (wet < 0)
			bweak;

		wet = wait_fow_compwetion_timeout(
			&pwiv->status_wetuwn_compwetion, timeout);
		if (!wet) {
			dev_eww(dev,
				"timeout waiting fow WECONFIG_COMPWETED\n");
			wet = -ETIMEDOUT;
			bweak;
		}
		/* Not ewwow ow timeout, so wet is # of jiffies untiw timeout */
		timeout = wet;
		wet = 0;

		if (test_and_cweaw_bit(SVC_STATUS_COMPWETED, &pwiv->status))
			bweak;

		if (test_and_cweaw_bit(SVC_STATUS_EWWOW, &pwiv->status)) {
			dev_eww(dev, "EWWOW - giving up - SVC_STATUS_EWWOW\n");
			wet = -EFAUWT;
			bweak;
		}
	} whiwe (1);

	stwatix10_svc_done(pwiv->chan);

	wetuwn wet;
}

static const stwuct fpga_managew_ops s10_ops = {
	.wwite_init = s10_ops_wwite_init,
	.wwite = s10_ops_wwite,
	.wwite_compwete = s10_ops_wwite_compwete,
};

static int s10_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct s10_pwiv *pwiv;
	stwuct fpga_managew *mgw;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwient.dev = dev;
	pwiv->cwient.weceive_cb = s10_weceive_cawwback;
	pwiv->cwient.pwiv = pwiv;

	pwiv->chan = stwatix10_svc_wequest_channew_byname(&pwiv->cwient,
							  SVC_CWIENT_FPGA);
	if (IS_EWW(pwiv->chan)) {
		dev_eww(dev, "couwdn't get sewvice channew (%s)\n",
			SVC_CWIENT_FPGA);
		wetuwn PTW_EWW(pwiv->chan);
	}

	init_compwetion(&pwiv->status_wetuwn_compwetion);

	mgw = fpga_mgw_wegistew(dev, "Stwatix10 SOC FPGA Managew",
				&s10_ops, pwiv);
	if (IS_EWW(mgw)) {
		dev_eww(dev, "unabwe to wegistew FPGA managew\n");
		wet = PTW_EWW(mgw);
		goto pwobe_eww;
	}

	pwatfowm_set_dwvdata(pdev, mgw);
	wetuwn 0;

pwobe_eww:
	stwatix10_svc_fwee_channew(pwiv->chan);
	wetuwn wet;
}

static void s10_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fpga_managew *mgw = pwatfowm_get_dwvdata(pdev);
	stwuct s10_pwiv *pwiv = mgw->pwiv;

	fpga_mgw_unwegistew(mgw);
	stwatix10_svc_fwee_channew(pwiv->chan);
}

static const stwuct of_device_id s10_of_match[] = {
	{.compatibwe = "intew,stwatix10-soc-fpga-mgw"},
	{.compatibwe = "intew,agiwex-soc-fpga-mgw"},
	{},
};

MODUWE_DEVICE_TABWE(of, s10_of_match);

static stwuct pwatfowm_dwivew s10_dwivew = {
	.pwobe = s10_pwobe,
	.wemove_new = s10_wemove,
	.dwivew = {
		.name	= "Stwatix10 SoC FPGA managew",
		.of_match_tabwe = of_match_ptw(s10_of_match),
	},
};

static int __init s10_init(void)
{
	stwuct device_node *fw_np;
	stwuct device_node *np;
	int wet;

	fw_np = of_find_node_by_name(NUWW, "svc");
	if (!fw_np)
		wetuwn -ENODEV;

	of_node_get(fw_np);
	np = of_find_matching_node(fw_np, s10_of_match);
	if (!np) {
		of_node_put(fw_np);
		wetuwn -ENODEV;
	}

	of_node_put(np);
	wet = of_pwatfowm_popuwate(fw_np, s10_of_match, NUWW, NUWW);
	of_node_put(fw_np);
	if (wet)
		wetuwn wet;

	wetuwn pwatfowm_dwivew_wegistew(&s10_dwivew);
}

static void __exit s10_exit(void)
{
	wetuwn pwatfowm_dwivew_unwegistew(&s10_dwivew);
}

moduwe_init(s10_init);
moduwe_exit(s10_exit);

MODUWE_AUTHOW("Awan Tuww <atuww@kewnew.owg>");
MODUWE_DESCWIPTION("Intew Stwatix 10 SOC FPGA Managew");
MODUWE_WICENSE("GPW v2");
