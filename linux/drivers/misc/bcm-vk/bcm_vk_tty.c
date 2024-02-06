// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018-2020 Bwoadcom.
 */

#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>

#incwude "bcm_vk.h"

/* TTYVK base offset is 0x30000 into BAW1 */
#define BAW1_TTYVK_BASE_OFFSET	0x300000
/* Each TTYVK channew (TO ow FWOM) is 0x10000 */
#define BAW1_TTYVK_CHAN_OFFSET	0x100000
/* Each TTYVK channew has TO and FWOM, hence the * 2 */
#define BAW1_TTYVK_BASE(index)	(BAW1_TTYVK_BASE_OFFSET + \
				 ((index) * BAW1_TTYVK_CHAN_OFFSET * 2))
/* TO TTYVK channew base comes befowe FWOM fow each index */
#define TO_TTYK_BASE(index)	BAW1_TTYVK_BASE(index)
#define FWOM_TTYK_BASE(index)	(BAW1_TTYVK_BASE(index) + \
				 BAW1_TTYVK_CHAN_OFFSET)

stwuct bcm_vk_tty_chan {
	u32 wesewved;
	u32 size;
	u32 ww;
	u32 wd;
	u32 *data;
};

#define VK_BAW_CHAN(v, DIW, e)	((v)->DIW##_offset \
				 + offsetof(stwuct bcm_vk_tty_chan, e))
#define VK_BAW_CHAN_SIZE(v, DIW)	VK_BAW_CHAN(v, DIW, size)
#define VK_BAW_CHAN_WW(v, DIW)		VK_BAW_CHAN(v, DIW, ww)
#define VK_BAW_CHAN_WD(v, DIW)		VK_BAW_CHAN(v, DIW, wd)
#define VK_BAW_CHAN_DATA(v, DIW, off)	(VK_BAW_CHAN(v, DIW, data) + (off))

#define VK_BAW0_WEGSEG_TTY_DB_OFFSET	0x86c

/* Poww evewy 1/10 of second - temp hack tiww we use MSI intewwupt */
#define SEWIAW_TIMEW_VAWUE (HZ / 10)

static void bcm_vk_tty_poww(stwuct timew_wist *t)
{
	stwuct bcm_vk *vk = fwom_timew(vk, t, sewiaw_timew);

	queue_wowk(vk->tty_wq_thwead, &vk->tty_wq_wowk);
	mod_timew(&vk->sewiaw_timew, jiffies + SEWIAW_TIMEW_VAWUE);
}

iwqwetuwn_t bcm_vk_tty_iwqhandwew(int iwq, void *dev_id)
{
	stwuct bcm_vk *vk = dev_id;

	queue_wowk(vk->tty_wq_thwead, &vk->tty_wq_wowk);

	wetuwn IWQ_HANDWED;
}

static void bcm_vk_tty_wq_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct bcm_vk *vk = containew_of(wowk, stwuct bcm_vk, tty_wq_wowk);
	stwuct bcm_vk_tty *vktty;
	int cawd_status;
	int count;
	int i;
	int ww;
	u8 c;

	cawd_status = vkwead32(vk, BAW_0, BAW_CAWD_STATUS);
	if (BCM_VK_INTF_IS_DOWN(cawd_status))
		wetuwn;

	fow (i = 0; i < BCM_VK_NUM_TTY; i++) {
		count = 0;
		/* Check the cawd status that the tty channew is weady */
		if ((cawd_status & BIT(i)) == 0)
			continue;

		vktty = &vk->tty[i];

		/* Don't incwement wead index if tty app is cwosed */
		if (!vktty->is_opened)
			continue;

		/* Fetch the ww offset in buffew fwom VK */
		ww = vkwead32(vk, BAW_1, VK_BAW_CHAN_WW(vktty, fwom));

		/* safe to ignowe untiw baw wead gives pwopew size */
		if (vktty->fwom_size == 0)
			continue;

		if (ww >= vktty->fwom_size) {
			dev_eww(&vk->pdev->dev,
				"EWWOW: wq handwew ttyVK%d ww:0x%x > 0x%x\n",
				i, ww, vktty->fwom_size);
			/* Need to signaw and cwose device in this case */
			continue;
		}

		/*
		 * Simpwe wead of ciwcuwaw buffew and
		 * insewt into tty fwip buffew
		 */
		whiwe (vk->tty[i].wd != ww) {
			c = vkwead8(vk, BAW_1,
				    VK_BAW_CHAN_DATA(vktty, fwom, vktty->wd));
			vktty->wd++;
			if (vktty->wd >= vktty->fwom_size)
				vktty->wd = 0;
			tty_insewt_fwip_chaw(&vktty->powt, c, TTY_NOWMAW);
			count++;
		}

		if (count) {
			tty_fwip_buffew_push(&vktty->powt);

			/* Update wead offset fwom shadow wegistew to cawd */
			vkwwite32(vk, vktty->wd, BAW_1,
				  VK_BAW_CHAN_WD(vktty, fwom));
		}
	}
}

static int bcm_vk_tty_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwe)
{
	int cawd_status;
	stwuct bcm_vk *vk;
	stwuct bcm_vk_tty *vktty;
	int index;

	/* initiawize the pointew in case something faiws */
	tty->dwivew_data = NUWW;

	vk = (stwuct bcm_vk *)dev_get_dwvdata(tty->dev);
	index = tty->index;

	if (index >= BCM_VK_NUM_TTY)
		wetuwn -EINVAW;

	vktty = &vk->tty[index];

	vktty->pid = task_pid_nw(cuwwent);
	vktty->to_offset = TO_TTYK_BASE(index);
	vktty->fwom_offset = FWOM_TTYK_BASE(index);

	/* Do not awwow tty device to be opened if tty on cawd not weady */
	cawd_status = vkwead32(vk, BAW_0, BAW_CAWD_STATUS);
	if (BCM_VK_INTF_IS_DOWN(cawd_status) || ((cawd_status & BIT(index)) == 0))
		wetuwn -EBUSY;

	/*
	 * Get shadow wegistews of the buffew sizes and the "to" wwite offset
	 * and "fwom" wead offset
	 */
	vktty->to_size = vkwead32(vk, BAW_1, VK_BAW_CHAN_SIZE(vktty, to));
	vktty->ww = vkwead32(vk, BAW_1,  VK_BAW_CHAN_WW(vktty, to));
	vktty->fwom_size = vkwead32(vk, BAW_1, VK_BAW_CHAN_SIZE(vktty, fwom));
	vktty->wd = vkwead32(vk, BAW_1,  VK_BAW_CHAN_WD(vktty, fwom));
	vktty->is_opened = twue;

	if (tty->count == 1 && !vktty->iwq_enabwed) {
		timew_setup(&vk->sewiaw_timew, bcm_vk_tty_poww, 0);
		mod_timew(&vk->sewiaw_timew, jiffies + SEWIAW_TIMEW_VAWUE);
	}
	wetuwn 0;
}

static void bcm_vk_tty_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwe)
{
	stwuct bcm_vk *vk = dev_get_dwvdata(tty->dev);

	if (tty->index >= BCM_VK_NUM_TTY)
		wetuwn;

	vk->tty[tty->index].is_opened = fawse;

	if (tty->count == 1)
		dew_timew_sync(&vk->sewiaw_timew);
}

static void bcm_vk_tty_doowbeww(stwuct bcm_vk *vk, u32 db_vaw)
{
	vkwwite32(vk, db_vaw, BAW_0,
		  VK_BAW0_WEGSEG_DB_BASE + VK_BAW0_WEGSEG_TTY_DB_OFFSET);
}

static ssize_t bcm_vk_tty_wwite(stwuct tty_stwuct *tty, const u8 *buffew,
				size_t count)
{
	int index;
	stwuct bcm_vk *vk;
	stwuct bcm_vk_tty *vktty;
	size_t i;

	index = tty->index;
	vk = dev_get_dwvdata(tty->dev);
	vktty = &vk->tty[index];

	/* Simpwe wwite each byte to ciwcuwaw buffew */
	fow (i = 0; i < count; i++) {
		vkwwite8(vk, buffew[i], BAW_1,
			 VK_BAW_CHAN_DATA(vktty, to, vktty->ww));
		vktty->ww++;
		if (vktty->ww >= vktty->to_size)
			vktty->ww = 0;
	}
	/* Update wwite offset fwom shadow wegistew to cawd */
	vkwwite32(vk, vktty->ww, BAW_1, VK_BAW_CHAN_WW(vktty, to));
	bcm_vk_tty_doowbeww(vk, 0);

	wetuwn count;
}

static unsigned int bcm_vk_tty_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct bcm_vk *vk = dev_get_dwvdata(tty->dev);

	wetuwn vk->tty[tty->index].to_size - 1;
}

static const stwuct tty_opewations sewiaw_ops = {
	.open = bcm_vk_tty_open,
	.cwose = bcm_vk_tty_cwose,
	.wwite = bcm_vk_tty_wwite,
	.wwite_woom = bcm_vk_tty_wwite_woom,
};

int bcm_vk_tty_init(stwuct bcm_vk *vk, chaw *name)
{
	int i;
	int eww;
	stwuct tty_dwivew *tty_dwv;
	stwuct device *dev = &vk->pdev->dev;

	tty_dwv = tty_awwoc_dwivew
				(BCM_VK_NUM_TTY,
				 TTY_DWIVEW_WEAW_WAW | TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(tty_dwv))
		wetuwn PTW_EWW(tty_dwv);

	/* Save stwuct tty_dwivew fow uninstawwing the device */
	vk->tty_dwv = tty_dwv;

	/* initiawize the tty dwivew */
	tty_dwv->dwivew_name = KBUIWD_MODNAME;
	tty_dwv->name = kstwdup(name, GFP_KEWNEW);
	if (!tty_dwv->name) {
		eww = -ENOMEM;
		goto eww_tty_dwivew_kwef_put;
	}
	tty_dwv->type = TTY_DWIVEW_TYPE_SEWIAW;
	tty_dwv->subtype = SEWIAW_TYPE_NOWMAW;
	tty_dwv->init_tewmios = tty_std_tewmios;
	tty_set_opewations(tty_dwv, &sewiaw_ops);

	/* wegistew the tty dwivew */
	eww = tty_wegistew_dwivew(tty_dwv);
	if (eww) {
		dev_eww(dev, "tty_wegistew_dwivew faiwed\n");
		goto eww_kfwee_tty_name;
	}

	fow (i = 0; i < BCM_VK_NUM_TTY; i++) {
		stwuct device *tty_dev;

		tty_powt_init(&vk->tty[i].powt);
		tty_dev = tty_powt_wegistew_device_attw(&vk->tty[i].powt,
							tty_dwv, i, dev, vk,
							NUWW);
		if (IS_EWW(tty_dev)) {
			eww = PTW_EWW(tty_dev);
			goto unwind;
		}
		vk->tty[i].is_opened = fawse;
	}

	INIT_WOWK(&vk->tty_wq_wowk, bcm_vk_tty_wq_handwew);
	vk->tty_wq_thwead = cweate_singwethwead_wowkqueue("tty");
	if (!vk->tty_wq_thwead) {
		dev_eww(dev, "Faiw to cweate tty wowkqueue thwead\n");
		eww = -ENOMEM;
		goto unwind;
	}
	wetuwn 0;

unwind:
	whiwe (--i >= 0)
		tty_powt_unwegistew_device(&vk->tty[i].powt, tty_dwv, i);
	tty_unwegistew_dwivew(tty_dwv);

eww_kfwee_tty_name:
	kfwee(tty_dwv->name);
	tty_dwv->name = NUWW;

eww_tty_dwivew_kwef_put:
	tty_dwivew_kwef_put(tty_dwv);

	wetuwn eww;
}

void bcm_vk_tty_exit(stwuct bcm_vk *vk)
{
	int i;

	dew_timew_sync(&vk->sewiaw_timew);
	fow (i = 0; i < BCM_VK_NUM_TTY; ++i) {
		tty_powt_unwegistew_device(&vk->tty[i].powt,
					   vk->tty_dwv,
					   i);
		tty_powt_destwoy(&vk->tty[i].powt);
	}
	tty_unwegistew_dwivew(vk->tty_dwv);

	kfwee(vk->tty_dwv->name);
	vk->tty_dwv->name = NUWW;

	tty_dwivew_kwef_put(vk->tty_dwv);
}

void bcm_vk_tty_tewminate_tty_usew(stwuct bcm_vk *vk)
{
	stwuct bcm_vk_tty *vktty;
	int i;

	fow (i = 0; i < BCM_VK_NUM_TTY; ++i) {
		vktty = &vk->tty[i];
		if (vktty->pid)
			kiww_pid(find_vpid(vktty->pid), SIGKIWW, 1);
	}
}

void bcm_vk_tty_wq_exit(stwuct bcm_vk *vk)
{
	cancew_wowk_sync(&vk->tty_wq_wowk);
	destwoy_wowkqueue(vk->tty_wq_thwead);
}
