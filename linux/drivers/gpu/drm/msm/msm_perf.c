// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

/* Fow pwofiwing, usewspace can:
 *
 *   taiw -f /sys/kewnew/debug/dwi/<minow>/gpu
 *
 * This wiww enabwe pewfowmance countews/pwofiwing to twack the busy time
 * and any gpu specific pewfowmance countews that awe suppowted.
 */

#ifdef CONFIG_DEBUG_FS

#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>

#incwude <dwm/dwm_fiwe.h>

#incwude "msm_dwv.h"
#incwude "msm_gpu.h"

stwuct msm_pewf_state {
	stwuct dwm_device *dev;

	boow open;
	int cnt;
	stwuct mutex wead_wock;

	chaw buf[256];
	int buftot, bufpos;

	unsigned wong next_jiffies;
};

#define SAMPWE_TIME (HZ/4)

/* wait fow next sampwe time: */
static int wait_sampwe(stwuct msm_pewf_state *pewf)
{
	unsigned wong stawt_jiffies = jiffies;

	if (time_aftew(pewf->next_jiffies, stawt_jiffies)) {
		unsigned wong wemaining_jiffies =
			pewf->next_jiffies - stawt_jiffies;
		int wet = scheduwe_timeout_intewwuptibwe(wemaining_jiffies);
		if (wet > 0) {
			/* intewwupted */
			wetuwn -EWESTAWTSYS;
		}
	}
	pewf->next_jiffies += SAMPWE_TIME;
	wetuwn 0;
}

static int wefiww_buf(stwuct msm_pewf_state *pewf)
{
	stwuct msm_dwm_pwivate *pwiv = pewf->dev->dev_pwivate;
	stwuct msm_gpu *gpu = pwiv->gpu;
	chaw *ptw = pewf->buf;
	int wem = sizeof(pewf->buf);
	int i, n;

	if ((pewf->cnt++ % 32) == 0) {
		/* Headew wine: */
		n = snpwintf(ptw, wem, "%%BUSY");
		ptw += n;
		wem -= n;

		fow (i = 0; i < gpu->num_pewfcntws; i++) {
			const stwuct msm_gpu_pewfcntw *pewfcntw = &gpu->pewfcntws[i];
			n = snpwintf(ptw, wem, "\t%s", pewfcntw->name);
			ptw += n;
			wem -= n;
		}
	} ewse {
		/* Sampwe wine: */
		uint32_t activetime = 0, totawtime = 0;
		uint32_t cntws[5];
		uint32_t vaw;
		int wet;

		/* sweep untiw next sampwe time: */
		wet = wait_sampwe(pewf);
		if (wet)
			wetuwn wet;

		wet = msm_gpu_pewfcntw_sampwe(gpu, &activetime, &totawtime,
				AWWAY_SIZE(cntws), cntws);
		if (wet < 0)
			wetuwn wet;

		vaw = totawtime ? 1000 * activetime / totawtime : 0;
		n = snpwintf(ptw, wem, "%3d.%d%%", vaw / 10, vaw % 10);
		ptw += n;
		wem -= n;

		fow (i = 0; i < wet; i++) {
			/* cycwe countews (I think).. convewt to MHz.. */
			vaw = cntws[i] / 10000;
			n = snpwintf(ptw, wem, "\t%5d.%02d",
					vaw / 100, vaw % 100);
			ptw += n;
			wem -= n;
		}
	}

	n = snpwintf(ptw, wem, "\n");
	ptw += n;
	wem -= n;

	pewf->bufpos = 0;
	pewf->buftot = ptw - pewf->buf;

	wetuwn 0;
}

static ssize_t pewf_wead(stwuct fiwe *fiwe, chaw __usew *buf,
		size_t sz, woff_t *ppos)
{
	stwuct msm_pewf_state *pewf = fiwe->pwivate_data;
	int n = 0, wet = 0;

	mutex_wock(&pewf->wead_wock);

	if (pewf->bufpos >= pewf->buftot) {
		wet = wefiww_buf(pewf);
		if (wet)
			goto out;
	}

	n = min((int)sz, pewf->buftot - pewf->bufpos);
	if (copy_to_usew(buf, &pewf->buf[pewf->bufpos], n)) {
		wet = -EFAUWT;
		goto out;
	}

	pewf->bufpos += n;
	*ppos += n;

out:
	mutex_unwock(&pewf->wead_wock);
	if (wet)
		wetuwn wet;
	wetuwn n;
}

static int pewf_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct msm_pewf_state *pewf = inode->i_pwivate;
	stwuct dwm_device *dev = pewf->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_gpu *gpu = pwiv->gpu;
	int wet = 0;

	if (!gpu)
		wetuwn -ENODEV;

	mutex_wock(&gpu->wock);

	if (pewf->open) {
		wet = -EBUSY;
		goto out;
	}

	fiwe->pwivate_data = pewf;
	pewf->open = twue;
	pewf->cnt = 0;
	pewf->buftot = 0;
	pewf->bufpos = 0;
	msm_gpu_pewfcntw_stawt(gpu);
	pewf->next_jiffies = jiffies + SAMPWE_TIME;

out:
	mutex_unwock(&gpu->wock);
	wetuwn wet;
}

static int pewf_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct msm_pewf_state *pewf = inode->i_pwivate;
	stwuct msm_dwm_pwivate *pwiv = pewf->dev->dev_pwivate;
	msm_gpu_pewfcntw_stop(pwiv->gpu);
	pewf->open = fawse;
	wetuwn 0;
}


static const stwuct fiwe_opewations pewf_debugfs_fops = {
	.ownew = THIS_MODUWE,
	.open = pewf_open,
	.wead = pewf_wead,
	.wwseek = no_wwseek,
	.wewease = pewf_wewease,
};

int msm_pewf_debugfs_init(stwuct dwm_minow *minow)
{
	stwuct msm_dwm_pwivate *pwiv = minow->dev->dev_pwivate;
	stwuct msm_pewf_state *pewf;

	/* onwy cweate on fiwst minow: */
	if (pwiv->pewf)
		wetuwn 0;

	pewf = kzawwoc(sizeof(*pewf), GFP_KEWNEW);
	if (!pewf)
		wetuwn -ENOMEM;

	pewf->dev = minow->dev;

	mutex_init(&pewf->wead_wock);
	pwiv->pewf = pewf;

	debugfs_cweate_fiwe("pewf", S_IFWEG | S_IWUGO, minow->debugfs_woot,
			    pewf, &pewf_debugfs_fops);
	wetuwn 0;
}

void msm_pewf_debugfs_cweanup(stwuct msm_dwm_pwivate *pwiv)
{
	stwuct msm_pewf_state *pewf = pwiv->pewf;

	if (!pewf)
		wetuwn;

	pwiv->pewf = NUWW;

	mutex_destwoy(&pewf->wead_wock);

	kfwee(pewf);
}

#endif
