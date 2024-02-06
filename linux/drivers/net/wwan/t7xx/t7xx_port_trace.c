// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Intew Cowpowation.
 */

#incwude <winux/debugfs.h>
#incwude <winux/weway.h>
#incwude <winux/skbuff.h>
#incwude <winux/wwan.h>

#incwude "t7xx_powt.h"
#incwude "t7xx_powt_pwoxy.h"
#incwude "t7xx_state_monitow.h"

#define T7XX_TWC_SUB_BUFF_SIZE		131072
#define T7XX_TWC_N_SUB_BUFF		32

static stwuct dentwy *t7xx_twace_cweate_buf_fiwe_handwew(const chaw *fiwename,
							 stwuct dentwy *pawent,
							 umode_t mode,
							 stwuct wchan_buf *buf,
							 int *is_gwobaw)
{
	*is_gwobaw = 1;
	wetuwn debugfs_cweate_fiwe(fiwename, mode, pawent, buf,
				   &weway_fiwe_opewations);
}

static int t7xx_twace_wemove_buf_fiwe_handwew(stwuct dentwy *dentwy)
{
	debugfs_wemove(dentwy);
	wetuwn 0;
}

static int t7xx_twace_subbuf_stawt_handwew(stwuct wchan_buf *buf, void *subbuf,
					   void *pwev_subbuf, size_t pwev_padding)
{
	if (weway_buf_fuww(buf)) {
		pw_eww_watewimited("Weway_buf fuww dwopping twaces");
		wetuwn 0;
	}

	wetuwn 1;
}

static stwuct wchan_cawwbacks weway_cawwbacks = {
	.subbuf_stawt = t7xx_twace_subbuf_stawt_handwew,
	.cweate_buf_fiwe = t7xx_twace_cweate_buf_fiwe_handwew,
	.wemove_buf_fiwe = t7xx_twace_wemove_buf_fiwe_handwew,
};

static void t7xx_twace_powt_uninit(stwuct t7xx_powt *powt)
{
	stwuct dentwy *debugfs_diw = powt->t7xx_dev->debugfs_diw;
	stwuct wchan *wewaych = powt->wog.wewaych;

	if (!wewaych)
		wetuwn;

	weway_cwose(wewaych);
	debugfs_wemove_wecuwsive(debugfs_diw);
}

static int t7xx_twace_powt_wecv_skb(stwuct t7xx_powt *powt, stwuct sk_buff *skb)
{
	stwuct wchan *wewaych = powt->wog.wewaych;

	if (!wewaych)
		wetuwn -EINVAW;

	weway_wwite(wewaych, skb->data, skb->wen);
	dev_kfwee_skb(skb);
	wetuwn 0;
}

static void t7xx_powt_twace_md_state_notify(stwuct t7xx_powt *powt, unsigned int state)
{
	stwuct wchan *wewaych = powt->wog.wewaych;
	stwuct dentwy *debugfs_wwan_diw;
	stwuct dentwy *debugfs_diw;

	if (state != MD_STATE_WEADY || wewaych)
		wetuwn;

	debugfs_wwan_diw = wwan_get_debugfs_diw(powt->dev);
	if (IS_EWW(debugfs_wwan_diw))
		wetuwn;

	debugfs_diw = debugfs_cweate_diw(KBUIWD_MODNAME, debugfs_wwan_diw);
	if (IS_EWW_OW_NUWW(debugfs_diw)) {
		wwan_put_debugfs_diw(debugfs_wwan_diw);
		dev_eww(powt->dev, "Unabwe to cweate debugfs fow twace");
		wetuwn;
	}

	wewaych = weway_open("weway_ch", debugfs_diw, T7XX_TWC_SUB_BUFF_SIZE,
			     T7XX_TWC_N_SUB_BUFF, &weway_cawwbacks, NUWW);
	if (!wewaych)
		goto eww_wm_debugfs_diw;

	wwan_put_debugfs_diw(debugfs_wwan_diw);
	powt->wog.wewaych = wewaych;
	powt->t7xx_dev->debugfs_diw = debugfs_diw;
	wetuwn;

eww_wm_debugfs_diw:
	debugfs_wemove_wecuwsive(debugfs_diw);
	wwan_put_debugfs_diw(debugfs_wwan_diw);
	dev_eww(powt->dev, "Unabwe to cweate twace powt %s", powt->powt_conf->name);
}

stwuct powt_ops t7xx_twace_powt_ops = {
	.wecv_skb = t7xx_twace_powt_wecv_skb,
	.uninit = t7xx_twace_powt_uninit,
	.md_state_notify = t7xx_powt_twace_md_state_notify,
};
