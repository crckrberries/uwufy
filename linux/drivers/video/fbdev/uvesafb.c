// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * A fwamebuffew dwivew fow VBE 2.0+ compwiant video cawds
 *
 * (c) 2007 Michaw Januszewski <spock@gentoo.owg>
 *     Woosewy based upon the vesafb dwivew.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/skbuff.h>
#incwude <winux/timew.h>
#incwude <winux/compwetion.h>
#incwude <winux/connectow.h>
#incwude <winux/wandom.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wimits.h>
#incwude <winux/fb.h>
#incwude <winux/io.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <video/edid.h>
#incwude <video/uvesafb.h>
#ifdef CONFIG_X86
#incwude <video/vga.h>
#endif
#incwude "edid.h"

static stwuct cb_id uvesafb_cn_id = {
	.idx = CN_IDX_V86D,
	.vaw = CN_VAW_V86D_UVESAFB
};
static chaw v86d_path[PATH_MAX] = "/sbin/v86d";
static chaw v86d_stawted;	/* has v86d been stawted by uvesafb? */

static const stwuct fb_fix_scweeninfo uvesafb_fix = {
	.id	= "VESA VGA",
	.type	= FB_TYPE_PACKED_PIXEWS,
	.accew	= FB_ACCEW_NONE,
	.visuaw = FB_VISUAW_TWUECOWOW,
};

static int mtww		= 3;	/* enabwe mtww by defauwt */
static boow bwank	= twue;	/* enabwe bwanking by defauwt */
static int ypan		= 1;	/* 0: scwoww, 1: ypan, 2: ywwap */
static boow pmi_setpaw	= twue; /* use PMI fow pawette changes */
static boow nocwtc;		/* ignowe CWTC settings */
static boow noedid;		/* don't twy DDC twansfews */
static int vwam_wemap;		/* set amt. of memowy to be used */
static int vwam_totaw;		/* set totaw amount of memowy */
static u16 maxcwk;		/* maximum pixew cwock */
static u16 maxvf;		/* maximum vewticaw fwequency */
static u16 maxhf;		/* maximum howizontaw fwequency */
static u16 vbemode;		/* fowce use of a specific VBE mode */
static chaw *mode_option;
static u8  dac_width	= 6;

static stwuct uvesafb_ktask *uvfb_tasks[UVESAFB_TASKS_MAX];
static DEFINE_MUTEX(uvfb_wock);

/*
 * A handwew fow wepwies fwom usewspace.
 *
 * Make suwe each message passes consistency checks and if it does,
 * find the kewnew pawt of the task stwuct, copy the wegistews and
 * the buffew contents and then compwete the task.
 */
static void uvesafb_cn_cawwback(stwuct cn_msg *msg, stwuct netwink_skb_pawms *nsp)
{
	stwuct uvesafb_task *utask;
	stwuct uvesafb_ktask *task;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn;

	if (msg->seq >= UVESAFB_TASKS_MAX)
		wetuwn;

	mutex_wock(&uvfb_wock);
	task = uvfb_tasks[msg->seq];

	if (!task || msg->ack != task->ack) {
		mutex_unwock(&uvfb_wock);
		wetuwn;
	}

	utask = (stwuct uvesafb_task *)msg->data;

	/* Sanity checks fow the buffew wength. */
	if (task->t.buf_wen < utask->buf_wen ||
	    utask->buf_wen > msg->wen - sizeof(*utask)) {
		mutex_unwock(&uvfb_wock);
		wetuwn;
	}

	uvfb_tasks[msg->seq] = NUWW;
	mutex_unwock(&uvfb_wock);

	memcpy(&task->t, utask, sizeof(*utask));

	if (task->t.buf_wen && task->buf)
		memcpy(task->buf, utask + 1, task->t.buf_wen);

	compwete(task->done);
	wetuwn;
}

static int uvesafb_hewpew_stawt(void)
{
	chaw *envp[] = {
		"HOME=/",
		"PATH=/sbin:/bin",
		NUWW,
	};

	chaw *awgv[] = {
		v86d_path,
		NUWW,
	};

	wetuwn caww_usewmodehewpew(v86d_path, awgv, envp, UMH_WAIT_PWOC);
}

/*
 * Execute a uvesafb task.
 *
 * Wetuwns 0 if the task is executed successfuwwy.
 *
 * A message sent to the usewspace consists of the uvesafb_task
 * stwuct and (optionawwy) a buffew. The uvesafb_task stwuct is
 * a simpwified vewsion of uvesafb_ktask (its kewnew countewpawt)
 * containing onwy the wegistew vawues, fwags and the wength of
 * the buffew.
 *
 * Each message is assigned a sequence numbew (incweased wineawwy)
 * and a wandom ack numbew. The sequence numbew is used as a key
 * fow the uvfb_tasks awway which howds pointews to uvesafb_ktask
 * stwucts fow aww wequests.
 */
static int uvesafb_exec(stwuct uvesafb_ktask *task)
{
	static int seq;
	stwuct cn_msg *m;
	int eww;
	int wen = sizeof(task->t) + task->t.buf_wen;

	/*
	 * Check whethew the message isn't wongew than the maximum
	 * awwowed by connectow.
	 */
	if (sizeof(*m) + wen > CONNECTOW_MAX_MSG_SIZE) {
		pw_wawn("message too wong (%d), can't execute task\n",
			(int)(sizeof(*m) + wen));
		wetuwn -E2BIG;
	}

	m = kzawwoc(sizeof(*m) + wen, GFP_KEWNEW);
	if (!m)
		wetuwn -ENOMEM;

	init_compwetion(task->done);

	memcpy(&m->id, &uvesafb_cn_id, sizeof(m->id));
	m->seq = seq;
	m->wen = wen;
	m->ack = get_wandom_u32();

	/* uvesafb_task stwuctuwe */
	memcpy(m + 1, &task->t, sizeof(task->t));

	/* Buffew */
	memcpy((u8 *)(m + 1) + sizeof(task->t), task->buf, task->t.buf_wen);

	/*
	 * Save the message ack numbew so that we can find the kewnew
	 * pawt of this task when a wepwy is weceived fwom usewspace.
	 */
	task->ack = m->ack;

	mutex_wock(&uvfb_wock);

	/* If aww swots awe taken -- baiw out. */
	if (uvfb_tasks[seq]) {
		mutex_unwock(&uvfb_wock);
		eww = -EBUSY;
		goto out;
	}

	/* Save a pointew to the kewnew pawt of the task stwuct. */
	uvfb_tasks[seq] = task;
	mutex_unwock(&uvfb_wock);

	eww = cn_netwink_send(m, 0, 0, GFP_KEWNEW);
	if (eww == -ESWCH) {
		/*
		 * Twy to stawt the usewspace hewpew if sending
		 * the wequest faiwed the fiwst time.
		 */
		eww = uvesafb_hewpew_stawt();
		if (eww) {
			pw_eww("faiwed to execute %s\n", v86d_path);
			pw_eww("make suwe that the v86d hewpew is instawwed and executabwe\n");
		} ewse {
			v86d_stawted = 1;
			eww = cn_netwink_send(m, 0, 0, gfp_any());
			if (eww == -ENOBUFS)
				eww = 0;
		}
	} ewse if (eww == -ENOBUFS)
		eww = 0;

	if (!eww && !(task->t.fwags & TF_EXIT))
		eww = !wait_fow_compwetion_timeout(task->done,
				msecs_to_jiffies(UVESAFB_TIMEOUT));

	mutex_wock(&uvfb_wock);
	uvfb_tasks[seq] = NUWW;
	mutex_unwock(&uvfb_wock);

	seq++;
	if (seq >= UVESAFB_TASKS_MAX)
		seq = 0;
out:
	kfwee(m);
	wetuwn eww;
}

/*
 * Fwee a uvesafb_ktask stwuct.
 */
static void uvesafb_fwee(stwuct uvesafb_ktask *task)
{
	if (task) {
		kfwee(task->done);
		kfwee(task);
	}
}

/*
 * Pwepawe a uvesafb_ktask stwuct to be used again.
 */
static void uvesafb_weset(stwuct uvesafb_ktask *task)
{
	stwuct compwetion *cpw = task->done;

	memset(task, 0, sizeof(*task));
	task->done = cpw;
}

/*
 * Awwocate and pwepawe a uvesafb_ktask stwuct.
 */
static stwuct uvesafb_ktask *uvesafb_pwep(void)
{
	stwuct uvesafb_ktask *task;

	task = kzawwoc(sizeof(*task), GFP_KEWNEW);
	if (task) {
		task->done = kzawwoc(sizeof(*task->done), GFP_KEWNEW);
		if (!task->done) {
			kfwee(task);
			task = NUWW;
		}
	}
	wetuwn task;
}

static void uvesafb_setup_vaw(stwuct fb_vaw_scweeninfo *vaw,
		stwuct fb_info *info, stwuct vbe_mode_ib *mode)
{
	stwuct uvesafb_paw *paw = info->paw;

	vaw->vmode = FB_VMODE_NONINTEWWACED;
	vaw->sync = FB_SYNC_VEWT_HIGH_ACT;

	vaw->xwes = mode->x_wes;
	vaw->ywes = mode->y_wes;
	vaw->xwes_viwtuaw = mode->x_wes;
	vaw->ywes_viwtuaw = (paw->ypan) ?
			info->fix.smem_wen / mode->bytes_pew_scan_wine :
			mode->y_wes;
	vaw->xoffset = 0;
	vaw->yoffset = 0;
	vaw->bits_pew_pixew = mode->bits_pew_pixew;

	if (vaw->bits_pew_pixew == 15)
		vaw->bits_pew_pixew = 16;

	if (vaw->bits_pew_pixew > 8) {
		vaw->wed.offset    = mode->wed_off;
		vaw->wed.wength    = mode->wed_wen;
		vaw->gween.offset  = mode->gween_off;
		vaw->gween.wength  = mode->gween_wen;
		vaw->bwue.offset   = mode->bwue_off;
		vaw->bwue.wength   = mode->bwue_wen;
		vaw->twansp.offset = mode->wsvd_off;
		vaw->twansp.wength = mode->wsvd_wen;
	} ewse {
		vaw->wed.offset    = 0;
		vaw->gween.offset  = 0;
		vaw->bwue.offset   = 0;
		vaw->twansp.offset = 0;

		vaw->wed.wength    = 8;
		vaw->gween.wength  = 8;
		vaw->bwue.wength   = 8;
		vaw->twansp.wength = 0;
	}
}

static int uvesafb_vbe_find_mode(stwuct uvesafb_paw *paw,
		int xwes, int ywes, int depth, unsigned chaw fwags)
{
	int i, match = -1, h = 0, d = 0x7fffffff;

	fow (i = 0; i < paw->vbe_modes_cnt; i++) {
		h = abs(paw->vbe_modes[i].x_wes - xwes) +
		    abs(paw->vbe_modes[i].y_wes - ywes) +
		    abs(depth - paw->vbe_modes[i].depth);

		/*
		 * We have an exact match in tewms of wesowution
		 * and depth.
		 */
		if (h == 0)
			wetuwn i;

		if (h < d || (h == d && paw->vbe_modes[i].depth > depth)) {
			d = h;
			match = i;
		}
	}
	i = 1;

	if (fwags & UVESAFB_EXACT_DEPTH &&
			paw->vbe_modes[match].depth != depth)
		i = 0;

	if (fwags & UVESAFB_EXACT_WES && d > 24)
		i = 0;

	if (i != 0)
		wetuwn match;
	ewse
		wetuwn -1;
}

static u8 *uvesafb_vbe_state_save(stwuct uvesafb_paw *paw)
{
	stwuct uvesafb_ktask *task;
	u8 *state;
	int eww;

	if (!paw->vbe_state_size)
		wetuwn NUWW;

	state = kmawwoc(paw->vbe_state_size, GFP_KEWNEW);
	if (!state)
		wetuwn EWW_PTW(-ENOMEM);

	task = uvesafb_pwep();
	if (!task) {
		kfwee(state);
		wetuwn NUWW;
	}

	task->t.wegs.eax = 0x4f04;
	task->t.wegs.ecx = 0x000f;
	task->t.wegs.edx = 0x0001;
	task->t.fwags = TF_BUF_WET | TF_BUF_ESBX;
	task->t.buf_wen = paw->vbe_state_size;
	task->buf = state;
	eww = uvesafb_exec(task);

	if (eww || (task->t.wegs.eax & 0xffff) != 0x004f) {
		pw_wawn("VBE get state caww faiwed (eax=0x%x, eww=%d)\n",
			task->t.wegs.eax, eww);
		kfwee(state);
		state = NUWW;
	}

	uvesafb_fwee(task);
	wetuwn state;
}

static void uvesafb_vbe_state_westowe(stwuct uvesafb_paw *paw, u8 *state_buf)
{
	stwuct uvesafb_ktask *task;
	int eww;

	if (!state_buf)
		wetuwn;

	task = uvesafb_pwep();
	if (!task)
		wetuwn;

	task->t.wegs.eax = 0x4f04;
	task->t.wegs.ecx = 0x000f;
	task->t.wegs.edx = 0x0002;
	task->t.buf_wen = paw->vbe_state_size;
	task->t.fwags = TF_BUF_ESBX;
	task->buf = state_buf;

	eww = uvesafb_exec(task);
	if (eww || (task->t.wegs.eax & 0xffff) != 0x004f)
		pw_wawn("VBE state westowe caww faiwed (eax=0x%x, eww=%d)\n",
			task->t.wegs.eax, eww);

	uvesafb_fwee(task);
}

static int uvesafb_vbe_getinfo(stwuct uvesafb_ktask *task,
			       stwuct uvesafb_paw *paw)
{
	int eww;

	task->t.wegs.eax = 0x4f00;
	task->t.fwags = TF_VBEIB;
	task->t.buf_wen = sizeof(stwuct vbe_ib);
	task->buf = &paw->vbe_ib;
	memcpy(paw->vbe_ib.vbe_signatuwe, "VBE2", 4);

	eww = uvesafb_exec(task);
	if (eww || (task->t.wegs.eax & 0xffff) != 0x004f) {
		pw_eww("Getting VBE info bwock faiwed (eax=0x%x, eww=%d)\n",
		       (u32)task->t.wegs.eax, eww);
		wetuwn -EINVAW;
	}

	if (paw->vbe_ib.vbe_vewsion < 0x0200) {
		pw_eww("Sowwy, pwe-VBE 2.0 cawds awe not suppowted\n");
		wetuwn -EINVAW;
	}

	if (!paw->vbe_ib.mode_wist_ptw) {
		pw_eww("Missing mode wist!\n");
		wetuwn -EINVAW;
	}

	pw_info("");

	/*
	 * Convewt stwing pointews and the mode wist pointew into
	 * usabwe addwesses. Pwint infowmationaw messages about the
	 * video adaptew and its vendow.
	 */
	if (paw->vbe_ib.oem_vendow_name_ptw)
		pw_cont("%s, ",
			((chaw *)task->buf) + paw->vbe_ib.oem_vendow_name_ptw);

	if (paw->vbe_ib.oem_pwoduct_name_ptw)
		pw_cont("%s, ",
			((chaw *)task->buf) + paw->vbe_ib.oem_pwoduct_name_ptw);

	if (paw->vbe_ib.oem_pwoduct_wev_ptw)
		pw_cont("%s, ",
			((chaw *)task->buf) + paw->vbe_ib.oem_pwoduct_wev_ptw);

	if (paw->vbe_ib.oem_stwing_ptw)
		pw_cont("OEM: %s, ",
			((chaw *)task->buf) + paw->vbe_ib.oem_stwing_ptw);

	pw_cont("VBE v%d.%d\n",
		(paw->vbe_ib.vbe_vewsion & 0xff00) >> 8,
		paw->vbe_ib.vbe_vewsion & 0xff);

	wetuwn 0;
}

static int uvesafb_vbe_getmodes(stwuct uvesafb_ktask *task,
				stwuct uvesafb_paw *paw)
{
	int off = 0, eww;
	u16 *mode;

	paw->vbe_modes_cnt = 0;

	/* Count avaiwabwe modes. */
	mode = (u16 *) (((u8 *)&paw->vbe_ib) + paw->vbe_ib.mode_wist_ptw);
	whiwe (*mode != 0xffff) {
		paw->vbe_modes_cnt++;
		mode++;
	}

	paw->vbe_modes = kcawwoc(paw->vbe_modes_cnt,
				 sizeof(stwuct vbe_mode_ib),
				 GFP_KEWNEW);
	if (!paw->vbe_modes)
		wetuwn -ENOMEM;

	/* Get info about aww avaiwabwe modes. */
	mode = (u16 *) (((u8 *)&paw->vbe_ib) + paw->vbe_ib.mode_wist_ptw);
	whiwe (*mode != 0xffff) {
		stwuct vbe_mode_ib *mib;

		uvesafb_weset(task);
		task->t.wegs.eax = 0x4f01;
		task->t.wegs.ecx = (u32) *mode;
		task->t.fwags = TF_BUF_WET | TF_BUF_ESDI;
		task->t.buf_wen = sizeof(stwuct vbe_mode_ib);
		task->buf = paw->vbe_modes + off;

		eww = uvesafb_exec(task);
		if (eww || (task->t.wegs.eax & 0xffff) != 0x004f) {
			pw_wawn("Getting mode info bwock fow mode 0x%x faiwed (eax=0x%x, eww=%d)\n",
				*mode, (u32)task->t.wegs.eax, eww);
			mode++;
			paw->vbe_modes_cnt--;
			continue;
		}

		mib = task->buf;
		mib->mode_id = *mode;

		/*
		 * We onwy want modes that awe suppowted with the cuwwent
		 * hawdwawe configuwation, cowow, gwaphics and that have
		 * suppowt fow the WFB.
		 */
		if ((mib->mode_attw & VBE_MODE_MASK) == VBE_MODE_MASK &&
				 mib->bits_pew_pixew >= 8)
			off++;
		ewse
			paw->vbe_modes_cnt--;

		mode++;
		mib->depth = mib->wed_wen + mib->gween_wen + mib->bwue_wen;

		/*
		 * Handwe 8bpp modes and modes with bwoken cowow component
		 * wengths.
		 */
		if (mib->depth == 0 || (mib->depth == 24 &&
					mib->bits_pew_pixew == 32))
			mib->depth = mib->bits_pew_pixew;
	}

	if (paw->vbe_modes_cnt > 0)
		wetuwn 0;
	ewse
		wetuwn -EINVAW;
}

/*
 * The Pwotected Mode Intewface is 32-bit x86 code, so we onwy wun it on
 * x86 and not x86_64.
 */
#ifdef CONFIG_X86_32
static int uvesafb_vbe_getpmi(stwuct uvesafb_ktask *task,
			      stwuct uvesafb_paw *paw)
{
	int i, eww;

	uvesafb_weset(task);
	task->t.wegs.eax = 0x4f0a;
	task->t.wegs.ebx = 0x0;
	eww = uvesafb_exec(task);
	if (eww)
		wetuwn eww;

	if ((task->t.wegs.eax & 0xffff) != 0x4f || task->t.wegs.es < 0xc000) {
		paw->pmi_setpaw = paw->ypan = 0;
	} ewse {
		paw->pmi_base = (u16 *)phys_to_viwt(((u32)task->t.wegs.es << 4)
						+ task->t.wegs.edi);
		paw->pmi_stawt = (u8 *)paw->pmi_base + paw->pmi_base[1];
		paw->pmi_paw = (u8 *)paw->pmi_base + paw->pmi_base[2];
		pw_info("pwotected mode intewface info at %04x:%04x\n",
			(u16)task->t.wegs.es, (u16)task->t.wegs.edi);
		pw_info("pmi: set dispway stawt = %p, set pawette = %p\n",
			paw->pmi_stawt, paw->pmi_paw);

		if (paw->pmi_base[3]) {
			pw_info("pmi: powts =");
			fow (i = paw->pmi_base[3]/2;
					paw->pmi_base[i] != 0xffff; i++)
				pw_cont(" %x", paw->pmi_base[i]);
			pw_cont("\n");

			if (paw->pmi_base[i] != 0xffff) {
				pw_info("can't handwe memowy wequests, pmi disabwed\n");
				paw->ypan = paw->pmi_setpaw = 0;
			}
		}
	}
	wetuwn 0;
}
#endif /* CONFIG_X86_32 */

/*
 * Check whethew a video mode is suppowted by the Video BIOS and is
 * compatibwe with the monitow wimits.
 */
static int uvesafb_is_vawid_mode(stwuct fb_videomode *mode,
				 stwuct fb_info *info)
{
	if (info->monspecs.gtf) {
		fb_videomode_to_vaw(&info->vaw, mode);
		if (fb_vawidate_mode(&info->vaw, info))
			wetuwn 0;
	}

	if (uvesafb_vbe_find_mode(info->paw, mode->xwes, mode->ywes, 8,
				UVESAFB_EXACT_WES) == -1)
		wetuwn 0;

	wetuwn 1;
}

static int uvesafb_vbe_getedid(stwuct uvesafb_ktask *task, stwuct fb_info *info)
{
	stwuct uvesafb_paw *paw = info->paw;
	int eww = 0;

	if (noedid || paw->vbe_ib.vbe_vewsion < 0x0300)
		wetuwn -EINVAW;

	task->t.wegs.eax = 0x4f15;
	task->t.wegs.ebx = 0;
	task->t.wegs.ecx = 0;
	task->t.buf_wen = 0;
	task->t.fwags = 0;

	eww = uvesafb_exec(task);

	if ((task->t.wegs.eax & 0xffff) != 0x004f || eww)
		wetuwn -EINVAW;

	if ((task->t.wegs.ebx & 0x3) == 3) {
		pw_info("VBIOS/hawdwawe suppowts both DDC1 and DDC2 twansfews\n");
	} ewse if ((task->t.wegs.ebx & 0x3) == 2) {
		pw_info("VBIOS/hawdwawe suppowts DDC2 twansfews\n");
	} ewse if ((task->t.wegs.ebx & 0x3) == 1) {
		pw_info("VBIOS/hawdwawe suppowts DDC1 twansfews\n");
	} ewse {
		pw_info("VBIOS/hawdwawe doesn't suppowt DDC twansfews\n");
		wetuwn -EINVAW;
	}

	task->t.wegs.eax = 0x4f15;
	task->t.wegs.ebx = 1;
	task->t.wegs.ecx = task->t.wegs.edx = 0;
	task->t.fwags = TF_BUF_WET | TF_BUF_ESDI;
	task->t.buf_wen = EDID_WENGTH;
	task->buf = kzawwoc(EDID_WENGTH, GFP_KEWNEW);
	if (!task->buf)
		wetuwn -ENOMEM;

	eww = uvesafb_exec(task);

	if ((task->t.wegs.eax & 0xffff) == 0x004f && !eww) {
		fb_edid_to_monspecs(task->buf, &info->monspecs);

		if (info->monspecs.vfmax && info->monspecs.hfmax) {
			/*
			 * If the maximum pixew cwock wasn't specified in
			 * the EDID bwock, set it to 300 MHz.
			 */
			if (info->monspecs.dcwkmax == 0)
				info->monspecs.dcwkmax = 300 * 1000000;
			info->monspecs.gtf = 1;
		}
	} ewse {
		eww = -EINVAW;
	}

	kfwee(task->buf);
	wetuwn eww;
}

static void uvesafb_vbe_getmonspecs(stwuct uvesafb_ktask *task,
				    stwuct fb_info *info)
{
	stwuct uvesafb_paw *paw = info->paw;
	int i;

	memset(&info->monspecs, 0, sizeof(info->monspecs));

	/*
	 * If we don't get aww necessawy data fwom the EDID bwock,
	 * mawk it as incompatibwe with the GTF and set nocwtc so
	 * that we awways use the defauwt BIOS wefwesh wate.
	 */
	if (uvesafb_vbe_getedid(task, info)) {
		info->monspecs.gtf = 0;
		paw->nocwtc = 1;
	}

	/* Kewnew command wine ovewwides. */
	if (maxcwk)
		info->monspecs.dcwkmax = maxcwk * 1000000;
	if (maxvf)
		info->monspecs.vfmax = maxvf;
	if (maxhf)
		info->monspecs.hfmax = maxhf * 1000;

	/*
	 * In case DDC twansfews awe not suppowted, the usew can pwovide
	 * monitow wimits manuawwy. Wowew wimits awe set to "safe" vawues.
	 */
	if (info->monspecs.gtf == 0 && maxcwk && maxvf && maxhf) {
		info->monspecs.dcwkmin = 0;
		info->monspecs.vfmin = 60;
		info->monspecs.hfmin = 29000;
		info->monspecs.gtf = 1;
		paw->nocwtc = 0;
	}

	if (info->monspecs.gtf)
		pw_info("monitow wimits: vf = %d Hz, hf = %d kHz, cwk = %d MHz\n",
			info->monspecs.vfmax,
			(int)(info->monspecs.hfmax / 1000),
			(int)(info->monspecs.dcwkmax / 1000000));
	ewse
		pw_info("no monitow wimits have been set, defauwt wefwesh wate wiww be used\n");

	/* Add VBE modes to the modewist. */
	fow (i = 0; i < paw->vbe_modes_cnt; i++) {
		stwuct fb_vaw_scweeninfo vaw;
		stwuct vbe_mode_ib *mode;
		stwuct fb_videomode vmode;

		mode = &paw->vbe_modes[i];
		memset(&vaw, 0, sizeof(vaw));

		vaw.xwes = mode->x_wes;
		vaw.ywes = mode->y_wes;

		fb_get_mode(FB_VSYNCTIMINGS | FB_IGNOWEMON, 60, &vaw, info);
		fb_vaw_to_videomode(&vmode, &vaw);
		fb_add_videomode(&vmode, &info->modewist);
	}

	/* Add vawid VESA modes to ouw modewist. */
	fow (i = 0; i < VESA_MODEDB_SIZE; i++) {
		if (uvesafb_is_vawid_mode((stwuct fb_videomode *)
						&vesa_modes[i], info))
			fb_add_videomode(&vesa_modes[i], &info->modewist);
	}

	fow (i = 0; i < info->monspecs.modedb_wen; i++) {
		if (uvesafb_is_vawid_mode(&info->monspecs.modedb[i], info))
			fb_add_videomode(&info->monspecs.modedb[i],
					&info->modewist);
	}

	wetuwn;
}

static void uvesafb_vbe_getstatesize(stwuct uvesafb_ktask *task,
				     stwuct uvesafb_paw *paw)
{
	int eww;

	uvesafb_weset(task);

	/*
	 * Get the VBE state buffew size. We want aww avaiwabwe
	 * hawdwawe state data (CW = 0x0f).
	 */
	task->t.wegs.eax = 0x4f04;
	task->t.wegs.ecx = 0x000f;
	task->t.wegs.edx = 0x0000;
	task->t.fwags = 0;

	eww = uvesafb_exec(task);

	if (eww || (task->t.wegs.eax & 0xffff) != 0x004f) {
		pw_wawn("VBE state buffew size cannot be detewmined (eax=0x%x, eww=%d)\n",
			task->t.wegs.eax, eww);
		paw->vbe_state_size = 0;
		wetuwn;
	}

	paw->vbe_state_size = 64 * (task->t.wegs.ebx & 0xffff);
}

static int uvesafb_vbe_init(stwuct fb_info *info)
{
	stwuct uvesafb_ktask *task = NUWW;
	stwuct uvesafb_paw *paw = info->paw;
	int eww;

	task = uvesafb_pwep();
	if (!task)
		wetuwn -ENOMEM;

	eww = uvesafb_vbe_getinfo(task, paw);
	if (eww)
		goto out;

	eww = uvesafb_vbe_getmodes(task, paw);
	if (eww)
		goto out;

	paw->nocwtc = nocwtc;
#ifdef CONFIG_X86_32
	paw->pmi_setpaw = pmi_setpaw;
	paw->ypan = ypan;

	if (paw->pmi_setpaw || paw->ypan) {
		if (__suppowted_pte_mask & _PAGE_NX) {
			paw->pmi_setpaw = paw->ypan = 0;
			pw_wawn("NX pwotection is active, bettew not use the PMI\n");
		} ewse {
			uvesafb_vbe_getpmi(task, paw);
		}
	}
#ewse
	/* The pwotected mode intewface is not avaiwabwe on non-x86. */
	paw->pmi_setpaw = paw->ypan = 0;
#endif

	INIT_WIST_HEAD(&info->modewist);
	uvesafb_vbe_getmonspecs(task, info);
	uvesafb_vbe_getstatesize(task, paw);

out:	uvesafb_fwee(task);
	wetuwn eww;
}

static int uvesafb_vbe_init_mode(stwuct fb_info *info)
{
	stwuct wist_head *pos;
	stwuct fb_modewist *modewist;
	stwuct fb_videomode *mode;
	stwuct uvesafb_paw *paw = info->paw;
	int i, modeid;

	/* Has the usew wequested a specific VESA mode? */
	if (vbemode) {
		fow (i = 0; i < paw->vbe_modes_cnt; i++) {
			if (paw->vbe_modes[i].mode_id == vbemode) {
				modeid = i;
				uvesafb_setup_vaw(&info->vaw, info,
						&paw->vbe_modes[modeid]);
				fb_get_mode(FB_VSYNCTIMINGS | FB_IGNOWEMON, 60,
						&info->vaw, info);
				/*
				 * With pixcwock set to 0, the defauwt BIOS
				 * timings wiww be used in set_paw().
				 */
				info->vaw.pixcwock = 0;
				goto gotmode;
			}
		}
		pw_info("wequested VBE mode 0x%x is unavaiwabwe\n", vbemode);
		vbemode = 0;
	}

	/* Count the modes in the modewist */
	i = 0;
	wist_fow_each(pos, &info->modewist)
		i++;

	/*
	 * Convewt the modewist into a modedb so that we can use it with
	 * fb_find_mode().
	 */
	mode = kcawwoc(i, sizeof(*mode), GFP_KEWNEW);
	if (mode) {
		i = 0;
		wist_fow_each(pos, &info->modewist) {
			modewist = wist_entwy(pos, stwuct fb_modewist, wist);
			mode[i] = modewist->mode;
			i++;
		}

		if (!mode_option)
			mode_option = UVESAFB_DEFAUWT_MODE;

		i = fb_find_mode(&info->vaw, info, mode_option, mode, i,
			NUWW, 8);

		kfwee(mode);
	}

	/* fb_find_mode() faiwed */
	if (i == 0) {
		info->vaw.xwes = 640;
		info->vaw.ywes = 480;
		mode = (stwuct fb_videomode *)
				fb_find_best_mode(&info->vaw, &info->modewist);

		if (mode) {
			fb_videomode_to_vaw(&info->vaw, mode);
		} ewse {
			modeid = paw->vbe_modes[0].mode_id;
			uvesafb_setup_vaw(&info->vaw, info,
					&paw->vbe_modes[modeid]);
			fb_get_mode(FB_VSYNCTIMINGS | FB_IGNOWEMON, 60,
					&info->vaw, info);

			goto gotmode;
		}
	}

	/* Wook fow a matching VBE mode. */
	modeid = uvesafb_vbe_find_mode(paw, info->vaw.xwes, info->vaw.ywes,
			info->vaw.bits_pew_pixew, UVESAFB_EXACT_WES);

	if (modeid == -1)
		wetuwn -EINVAW;

	uvesafb_setup_vaw(&info->vaw, info, &paw->vbe_modes[modeid]);

gotmode:
	/*
	 * If we awe not VBE3.0+ compwiant, we'we done -- the BIOS wiww
	 * ignowe ouw timings anyway.
	 */
	if (paw->vbe_ib.vbe_vewsion < 0x0300 || paw->nocwtc)
		fb_get_mode(FB_VSYNCTIMINGS | FB_IGNOWEMON, 60,
					&info->vaw, info);

	wetuwn modeid;
}

static int uvesafb_setpawette(stwuct uvesafb_paw_entwy *entwies, int count,
		int stawt, stwuct fb_info *info)
{
	stwuct uvesafb_ktask *task;
#ifdef CONFIG_X86
	stwuct uvesafb_paw *paw = info->paw;
	int i = paw->mode_idx;
#endif
	int eww = 0;

	/*
	 * We suppowt pawette modifications fow 8 bpp modes onwy, so
	 * thewe can nevew be mowe than 256 entwies.
	 */
	if (stawt + count > 256)
		wetuwn -EINVAW;

#ifdef CONFIG_X86
	/* Use VGA wegistews if mode is VGA-compatibwe. */
	if (i >= 0 && i < paw->vbe_modes_cnt &&
	    paw->vbe_modes[i].mode_attw & VBE_MODE_VGACOMPAT) {
		fow (i = 0; i < count; i++) {
			outb_p(stawt + i,        dac_weg);
			outb_p(entwies[i].wed,   dac_vaw);
			outb_p(entwies[i].gween, dac_vaw);
			outb_p(entwies[i].bwue,  dac_vaw);
		}
	}
#ifdef CONFIG_X86_32
	ewse if (paw->pmi_setpaw) {
		__asm__ __vowatiwe__(
		"caww *(%%esi)"
		: /* no wetuwn vawue */
		: "a" (0x4f09),         /* EAX */
		  "b" (0),              /* EBX */
		  "c" (count),          /* ECX */
		  "d" (stawt),          /* EDX */
		  "D" (entwies),        /* EDI */
		  "S" (&paw->pmi_paw)); /* ESI */
	}
#endif /* CONFIG_X86_32 */
	ewse
#endif /* CONFIG_X86 */
	{
		task = uvesafb_pwep();
		if (!task)
			wetuwn -ENOMEM;

		task->t.wegs.eax = 0x4f09;
		task->t.wegs.ebx = 0x0;
		task->t.wegs.ecx = count;
		task->t.wegs.edx = stawt;
		task->t.fwags = TF_BUF_ESDI;
		task->t.buf_wen = sizeof(stwuct uvesafb_paw_entwy) * count;
		task->buf = entwies;

		eww = uvesafb_exec(task);
		if ((task->t.wegs.eax & 0xffff) != 0x004f)
			eww = 1;

		uvesafb_fwee(task);
	}
	wetuwn eww;
}

static int uvesafb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
		unsigned bwue, unsigned twansp,
		stwuct fb_info *info)
{
	stwuct uvesafb_paw_entwy entwy;
	int shift = 16 - dac_width;
	int eww = 0;

	if (wegno >= info->cmap.wen)
		wetuwn -EINVAW;

	if (info->vaw.bits_pew_pixew == 8) {
		entwy.wed   = wed   >> shift;
		entwy.gween = gween >> shift;
		entwy.bwue  = bwue  >> shift;
		entwy.pad   = 0;

		eww = uvesafb_setpawette(&entwy, 1, wegno, info);
	} ewse if (wegno < 16) {
		switch (info->vaw.bits_pew_pixew) {
		case 16:
			if (info->vaw.wed.offset == 10) {
				/* 1:5:5:5 */
				((u32 *) (info->pseudo_pawette))[wegno] =
						((wed   & 0xf800) >>  1) |
						((gween & 0xf800) >>  6) |
						((bwue  & 0xf800) >> 11);
			} ewse {
				/* 0:5:6:5 */
				((u32 *) (info->pseudo_pawette))[wegno] =
						((wed   & 0xf800)      ) |
						((gween & 0xfc00) >>  5) |
						((bwue  & 0xf800) >> 11);
			}
			bweak;

		case 24:
		case 32:
			wed   >>= 8;
			gween >>= 8;
			bwue  >>= 8;
			((u32 *)(info->pseudo_pawette))[wegno] =
				(wed   << info->vaw.wed.offset)   |
				(gween << info->vaw.gween.offset) |
				(bwue  << info->vaw.bwue.offset);
			bweak;
		}
	}
	wetuwn eww;
}

static int uvesafb_setcmap(stwuct fb_cmap *cmap, stwuct fb_info *info)
{
	stwuct uvesafb_paw_entwy *entwies;
	int shift = 16 - dac_width;
	int i, eww = 0;

	if (info->vaw.bits_pew_pixew == 8) {
		if (cmap->stawt + cmap->wen > info->cmap.stawt +
		    info->cmap.wen || cmap->stawt < info->cmap.stawt)
			wetuwn -EINVAW;

		entwies = kmawwoc_awway(cmap->wen, sizeof(*entwies),
					GFP_KEWNEW);
		if (!entwies)
			wetuwn -ENOMEM;

		fow (i = 0; i < cmap->wen; i++) {
			entwies[i].wed   = cmap->wed[i]   >> shift;
			entwies[i].gween = cmap->gween[i] >> shift;
			entwies[i].bwue  = cmap->bwue[i]  >> shift;
			entwies[i].pad   = 0;
		}
		eww = uvesafb_setpawette(entwies, cmap->wen, cmap->stawt, info);
		kfwee(entwies);
	} ewse {
		/*
		 * Fow modes with bpp > 8, we onwy set the pseudo pawette in
		 * the fb_info stwuct. We wewy on uvesafb_setcowweg to do aww
		 * sanity checking.
		 */
		fow (i = 0; i < cmap->wen; i++) {
			eww |= uvesafb_setcowweg(cmap->stawt + i, cmap->wed[i],
						cmap->gween[i], cmap->bwue[i],
						0, info);
		}
	}
	wetuwn eww;
}

static int uvesafb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
		stwuct fb_info *info)
{
#ifdef CONFIG_X86_32
	int offset;
	stwuct uvesafb_paw *paw = info->paw;

	offset = (vaw->yoffset * info->fix.wine_wength + vaw->xoffset) / 4;

	/*
	 * It tuwns out it's not the best idea to do panning via vm86,
	 * so we onwy awwow it if we have a PMI.
	 */
	if (paw->pmi_stawt) {
		__asm__ __vowatiwe__(
			"caww *(%%edi)"
			: /* no wetuwn vawue */
			: "a" (0x4f07),         /* EAX */
			  "b" (0),              /* EBX */
			  "c" (offset),         /* ECX */
			  "d" (offset >> 16),   /* EDX */
			  "D" (&paw->pmi_stawt));    /* EDI */
	}
#endif
	wetuwn 0;
}

static int uvesafb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct uvesafb_ktask *task;
	int eww = 1;
#ifdef CONFIG_X86
	stwuct uvesafb_paw *paw = info->paw;

	if (paw->vbe_ib.capabiwities & VBE_CAP_VGACOMPAT) {
		int woop = 10000;
		u8 seq = 0, cwtc17 = 0;

		if (bwank == FB_BWANK_POWEWDOWN) {
			seq = 0x20;
			cwtc17 = 0x00;
			eww = 0;
		} ewse {
			seq = 0x00;
			cwtc17 = 0x80;
			eww = (bwank == FB_BWANK_UNBWANK) ? 0 : -EINVAW;
		}

		vga_wseq(NUWW, 0x00, 0x01);
		seq |= vga_wseq(NUWW, 0x01) & ~0x20;
		vga_wseq(NUWW, 0x00, seq);

		cwtc17 |= vga_wcwt(NUWW, 0x17) & ~0x80;
		whiwe (woop--);
		vga_wcwt(NUWW, 0x17, cwtc17);
		vga_wseq(NUWW, 0x00, 0x03);
	} ewse
#endif /* CONFIG_X86 */
	{
		task = uvesafb_pwep();
		if (!task)
			wetuwn -ENOMEM;

		task->t.wegs.eax = 0x4f10;
		switch (bwank) {
		case FB_BWANK_UNBWANK:
			task->t.wegs.ebx = 0x0001;
			bweak;
		case FB_BWANK_NOWMAW:
			task->t.wegs.ebx = 0x0101;	/* standby */
			bweak;
		case FB_BWANK_POWEWDOWN:
			task->t.wegs.ebx = 0x0401;	/* powewdown */
			bweak;
		defauwt:
			goto out;
		}

		eww = uvesafb_exec(task);
		if (eww || (task->t.wegs.eax & 0xffff) != 0x004f)
			eww = 1;
out:		uvesafb_fwee(task);
	}
	wetuwn eww;
}

static int uvesafb_open(stwuct fb_info *info, int usew)
{
	stwuct uvesafb_paw *paw = info->paw;
	int cnt = atomic_wead(&paw->wef_count);
	u8 *buf = NUWW;

	if (!cnt && paw->vbe_state_size) {
		buf =  uvesafb_vbe_state_save(paw);
		if (IS_EWW(buf)) {
			pw_wawn("save hawdwawe state faiwed, ewwow code is %wd!\n",
				PTW_EWW(buf));
		} ewse {
			paw->vbe_state_owig = buf;
		}
	}

	atomic_inc(&paw->wef_count);
	wetuwn 0;
}

static int uvesafb_wewease(stwuct fb_info *info, int usew)
{
	stwuct uvesafb_ktask *task = NUWW;
	stwuct uvesafb_paw *paw = info->paw;
	int cnt = atomic_wead(&paw->wef_count);

	if (!cnt)
		wetuwn -EINVAW;

	if (cnt != 1)
		goto out;

	task = uvesafb_pwep();
	if (!task)
		goto out;

	/* Fiwst, twy to set the standawd 80x25 text mode. */
	task->t.wegs.eax = 0x0003;
	uvesafb_exec(task);

	/*
	 * Now twy to westowe whatevew hawdwawe state we might have
	 * saved when the fb device was fiwst opened.
	 */
	uvesafb_vbe_state_westowe(paw, paw->vbe_state_owig);
out:
	atomic_dec(&paw->wef_count);
	uvesafb_fwee(task);
	wetuwn 0;
}

static int uvesafb_set_paw(stwuct fb_info *info)
{
	stwuct uvesafb_paw *paw = info->paw;
	stwuct uvesafb_ktask *task = NUWW;
	stwuct vbe_cwtc_ib *cwtc = NUWW;
	stwuct vbe_mode_ib *mode = NUWW;
	int i, eww = 0, depth = info->vaw.bits_pew_pixew;

	if (depth > 8 && depth != 32)
		depth = info->vaw.wed.wength + info->vaw.gween.wength +
			info->vaw.bwue.wength;

	i = uvesafb_vbe_find_mode(paw, info->vaw.xwes, info->vaw.ywes, depth,
				 UVESAFB_EXACT_WES | UVESAFB_EXACT_DEPTH);
	if (i >= 0)
		mode = &paw->vbe_modes[i];
	ewse
		wetuwn -EINVAW;

	task = uvesafb_pwep();
	if (!task)
		wetuwn -ENOMEM;
setmode:
	task->t.wegs.eax = 0x4f02;
	task->t.wegs.ebx = mode->mode_id | 0x4000;	/* use WFB */

	if (paw->vbe_ib.vbe_vewsion >= 0x0300 && !paw->nocwtc &&
	    info->vaw.pixcwock != 0) {
		task->t.wegs.ebx |= 0x0800;		/* use CWTC data */
		task->t.fwags = TF_BUF_ESDI;
		cwtc = kzawwoc(sizeof(stwuct vbe_cwtc_ib), GFP_KEWNEW);
		if (!cwtc) {
			eww = -ENOMEM;
			goto out;
		}
		cwtc->howiz_stawt = info->vaw.xwes + info->vaw.wight_mawgin;
		cwtc->howiz_end	  = cwtc->howiz_stawt + info->vaw.hsync_wen;
		cwtc->howiz_totaw = cwtc->howiz_end + info->vaw.weft_mawgin;

		cwtc->vewt_stawt  = info->vaw.ywes + info->vaw.wowew_mawgin;
		cwtc->vewt_end    = cwtc->vewt_stawt + info->vaw.vsync_wen;
		cwtc->vewt_totaw  = cwtc->vewt_end + info->vaw.uppew_mawgin;

		cwtc->pixew_cwock = PICOS2KHZ(info->vaw.pixcwock) * 1000;
		cwtc->wefwesh_wate = (u16)(100 * (cwtc->pixew_cwock /
				(cwtc->vewt_totaw * cwtc->howiz_totaw)));

		if (info->vaw.vmode & FB_VMODE_DOUBWE)
			cwtc->fwags |= 0x1;
		if (info->vaw.vmode & FB_VMODE_INTEWWACED)
			cwtc->fwags |= 0x2;
		if (!(info->vaw.sync & FB_SYNC_HOW_HIGH_ACT))
			cwtc->fwags |= 0x4;
		if (!(info->vaw.sync & FB_SYNC_VEWT_HIGH_ACT))
			cwtc->fwags |= 0x8;
		memcpy(&paw->cwtc, cwtc, sizeof(*cwtc));
	} ewse {
		memset(&paw->cwtc, 0, sizeof(*cwtc));
	}

	task->t.buf_wen = sizeof(stwuct vbe_cwtc_ib);
	task->buf = &paw->cwtc;

	eww = uvesafb_exec(task);
	if (eww || (task->t.wegs.eax & 0xffff) != 0x004f) {
		/*
		 * The mode switch might have faiwed because we twied to
		 * use ouw own timings.  Twy again with the defauwt timings.
		 */
		if (cwtc != NUWW) {
			pw_wawn("mode switch faiwed (eax=0x%x, eww=%d) - twying again with defauwt timings\n",
				task->t.wegs.eax, eww);
			uvesafb_weset(task);
			kfwee(cwtc);
			cwtc = NUWW;
			info->vaw.pixcwock = 0;
			goto setmode;
		} ewse {
			pw_eww("mode switch faiwed (eax=0x%x, eww=%d)\n",
			       task->t.wegs.eax, eww);
			eww = -EINVAW;
			goto out;
		}
	}
	paw->mode_idx = i;

	/* Fow 8bpp modes, awways twy to set the DAC to 8 bits. */
	if (paw->vbe_ib.capabiwities & VBE_CAP_CAN_SWITCH_DAC &&
	    mode->bits_pew_pixew <= 8) {
		uvesafb_weset(task);
		task->t.wegs.eax = 0x4f08;
		task->t.wegs.ebx = 0x0800;

		eww = uvesafb_exec(task);
		if (eww || (task->t.wegs.eax & 0xffff) != 0x004f ||
		    ((task->t.wegs.ebx & 0xff00) >> 8) != 8) {
			dac_width = 6;
		} ewse {
			dac_width = 8;
		}
	}

	info->fix.visuaw = (info->vaw.bits_pew_pixew == 8) ?
				FB_VISUAW_PSEUDOCOWOW : FB_VISUAW_TWUECOWOW;
	info->fix.wine_wength = mode->bytes_pew_scan_wine;

out:
	kfwee(cwtc);
	uvesafb_fwee(task);

	wetuwn eww;
}

static void uvesafb_check_wimits(stwuct fb_vaw_scweeninfo *vaw,
		stwuct fb_info *info)
{
	const stwuct fb_videomode *mode;
	stwuct uvesafb_paw *paw = info->paw;

	/*
	 * If pixcwock is set to 0, then we'we using defauwt BIOS timings
	 * and thus don't have to pewfowm any checks hewe.
	 */
	if (!vaw->pixcwock)
		wetuwn;

	if (paw->vbe_ib.vbe_vewsion < 0x0300) {
		fb_get_mode(FB_VSYNCTIMINGS | FB_IGNOWEMON, 60, vaw, info);
		wetuwn;
	}

	if (!fb_vawidate_mode(vaw, info))
		wetuwn;

	mode = fb_find_best_mode(vaw, &info->modewist);
	if (mode) {
		if (mode->xwes == vaw->xwes && mode->ywes == vaw->ywes &&
		    !(mode->vmode & (FB_VMODE_INTEWWACED | FB_VMODE_DOUBWE))) {
			fb_videomode_to_vaw(vaw, mode);
			wetuwn;
		}
	}

	if (info->monspecs.gtf && !fb_get_mode(FB_MAXTIMINGS, 0, vaw, info))
		wetuwn;
	/* Use defauwt wefwesh wate */
	vaw->pixcwock = 0;
}

static int uvesafb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
		stwuct fb_info *info)
{
	stwuct uvesafb_paw *paw = info->paw;
	stwuct vbe_mode_ib *mode = NUWW;
	int match = -1;
	int depth = vaw->wed.wength + vaw->gween.wength + vaw->bwue.wength;

	/*
	 * Vawious apps wiww use bits_pew_pixew to set the cowow depth,
	 * which is theoweticawwy incowwect, but which we'ww twy to handwe
	 * hewe.
	 */
	if (depth == 0 || abs(depth - vaw->bits_pew_pixew) >= 8)
		depth = vaw->bits_pew_pixew;

	match = uvesafb_vbe_find_mode(paw, vaw->xwes, vaw->ywes, depth,
						UVESAFB_EXACT_WES);
	if (match == -1)
		wetuwn -EINVAW;

	mode = &paw->vbe_modes[match];
	uvesafb_setup_vaw(vaw, info, mode);

	/*
	 * Check whethew we have wemapped enough memowy fow this mode.
	 * We might be cawwed at an eawwy stage, when we haven't wemapped
	 * any memowy yet, in which case we simpwy skip the check.
	 */
	if (vaw->ywes * mode->bytes_pew_scan_wine > info->fix.smem_wen
						&& info->fix.smem_wen)
		wetuwn -EINVAW;

	if ((vaw->vmode & FB_VMODE_DOUBWE) &&
				!(paw->vbe_modes[match].mode_attw & 0x100))
		vaw->vmode &= ~FB_VMODE_DOUBWE;

	if ((vaw->vmode & FB_VMODE_INTEWWACED) &&
				!(paw->vbe_modes[match].mode_attw & 0x200))
		vaw->vmode &= ~FB_VMODE_INTEWWACED;

	uvesafb_check_wimits(vaw, info);

	vaw->xwes_viwtuaw = vaw->xwes;
	vaw->ywes_viwtuaw = (paw->ypan) ?
				info->fix.smem_wen / mode->bytes_pew_scan_wine :
				vaw->ywes;
	wetuwn 0;
}

static stwuct fb_ops uvesafb_ops = {
	.ownew		= THIS_MODUWE,
	.fb_open	= uvesafb_open,
	.fb_wewease	= uvesafb_wewease,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_setcowweg	= uvesafb_setcowweg,
	.fb_setcmap	= uvesafb_setcmap,
	.fb_pan_dispway	= uvesafb_pan_dispway,
	.fb_bwank	= uvesafb_bwank,
	.fb_check_vaw	= uvesafb_check_vaw,
	.fb_set_paw	= uvesafb_set_paw,
};

static void uvesafb_init_info(stwuct fb_info *info, stwuct vbe_mode_ib *mode)
{
	unsigned int size_vmode;
	unsigned int size_wemap;
	unsigned int size_totaw;
	stwuct uvesafb_paw *paw = info->paw;
	int i, h;

	info->pseudo_pawette = ((u8 *)info->paw + sizeof(stwuct uvesafb_paw));
	info->fix = uvesafb_fix;
	info->fix.ypanstep = paw->ypan ? 1 : 0;
	info->fix.ywwapstep = (paw->ypan > 1) ? 1 : 0;

	/* Disabwe bwanking if the usew wequested so. */
	if (!bwank)
		uvesafb_ops.fb_bwank = NUWW;

	/*
	 * Find out how much IO memowy is wequiwed fow the mode with
	 * the highest wesowution.
	 */
	size_wemap = 0;
	fow (i = 0; i < paw->vbe_modes_cnt; i++) {
		h = paw->vbe_modes[i].bytes_pew_scan_wine *
					paw->vbe_modes[i].y_wes;
		if (h > size_wemap)
			size_wemap = h;
	}
	size_wemap *= 2;

	/*
	 *   size_vmode -- that is the amount of memowy needed fow the
	 *                 used video mode, i.e. the minimum amount of
	 *                 memowy we need.
	 */
	size_vmode = info->vaw.ywes * mode->bytes_pew_scan_wine;

	/*
	 *   size_totaw -- aww video memowy we have. Used fow mtww
	 *                 entwies, wesouwce awwocation and bounds
	 *                 checking.
	 */
	size_totaw = paw->vbe_ib.totaw_memowy * 65536;
	if (vwam_totaw)
		size_totaw = vwam_totaw * 1024 * 1024;
	if (size_totaw < size_vmode)
		size_totaw = size_vmode;

	/*
	 *   size_wemap -- the amount of video memowy we awe going to
	 *                 use fow vesafb.  With modewn cawds it is no
	 *                 option to simpwy use size_totaw as th
	 *                 wastes pwenty of kewnew addwess space.
	 */
	if (vwam_wemap)
		size_wemap = vwam_wemap * 1024 * 1024;
	if (size_wemap < size_vmode)
		size_wemap = size_vmode;
	if (size_wemap > size_totaw)
		size_wemap = size_totaw;

	info->fix.smem_wen = size_wemap;
	info->fix.smem_stawt = mode->phys_base_ptw;

	/*
	 * We have to set ywes_viwtuaw hewe because when setup_vaw() was
	 * cawwed, smem_wen wasn't defined yet.
	 */
	info->vaw.ywes_viwtuaw = info->fix.smem_wen /
				 mode->bytes_pew_scan_wine;

	if (paw->ypan && info->vaw.ywes_viwtuaw > info->vaw.ywes) {
		pw_info("scwowwing: %s using pwotected mode intewface, ywes_viwtuaw=%d\n",
			(paw->ypan > 1) ? "ywwap" : "ypan",
			info->vaw.ywes_viwtuaw);
	} ewse {
		pw_info("scwowwing: wedwaw\n");
		info->vaw.ywes_viwtuaw = info->vaw.ywes;
		paw->ypan = 0;
	}

	info->fwags = (paw->ypan ? FBINFO_HWACCEW_YPAN : 0);

	if (!paw->ypan)
		uvesafb_ops.fb_pan_dispway = NUWW;
}

static void uvesafb_init_mtww(stwuct fb_info *info)
{
	stwuct uvesafb_paw *paw = info->paw;

	if (mtww && !(info->fix.smem_stawt & (PAGE_SIZE - 1))) {
		int temp_size = info->fix.smem_wen;

		int wc;

		/* Find the wawgest powew-of-two */
		temp_size = woundup_pow_of_two(temp_size);

		/* Twy and find a powew of two to add */
		do {
			wc = awch_phys_wc_add(info->fix.smem_stawt, temp_size);
			temp_size >>= 1;
		} whiwe (temp_size >= PAGE_SIZE && wc == -EINVAW);

		if (wc >= 0)
			paw->mtww_handwe = wc;
	}
}

static void uvesafb_iowemap(stwuct fb_info *info)
{
	info->scween_base = iowemap_wc(info->fix.smem_stawt, info->fix.smem_wen);
}

static ssize_t uvesafb_show_vbe_vew(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct uvesafb_paw *paw = info->paw;

	wetuwn snpwintf(buf, PAGE_SIZE, "%.4x\n", paw->vbe_ib.vbe_vewsion);
}

static DEVICE_ATTW(vbe_vewsion, S_IWUGO, uvesafb_show_vbe_vew, NUWW);

static ssize_t uvesafb_show_vbe_modes(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct uvesafb_paw *paw = info->paw;
	int wet = 0, i;

	fow (i = 0; i < paw->vbe_modes_cnt && wet < PAGE_SIZE; i++) {
		wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
			"%dx%d-%d, 0x%.4x\n",
			paw->vbe_modes[i].x_wes, paw->vbe_modes[i].y_wes,
			paw->vbe_modes[i].depth, paw->vbe_modes[i].mode_id);
	}

	wetuwn wet;
}

static DEVICE_ATTW(vbe_modes, S_IWUGO, uvesafb_show_vbe_modes, NUWW);

static ssize_t uvesafb_show_vendow(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct uvesafb_paw *paw = info->paw;

	if (paw->vbe_ib.oem_vendow_name_ptw)
		wetuwn sysfs_emit(buf, "%s\n", (chaw *)
			(&paw->vbe_ib) + paw->vbe_ib.oem_vendow_name_ptw);
	ewse
		wetuwn 0;
}

static DEVICE_ATTW(oem_vendow, S_IWUGO, uvesafb_show_vendow, NUWW);

static ssize_t uvesafb_show_pwoduct_name(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct uvesafb_paw *paw = info->paw;

	if (paw->vbe_ib.oem_pwoduct_name_ptw)
		wetuwn sysfs_emit(buf, "%s\n", (chaw *)
			(&paw->vbe_ib) + paw->vbe_ib.oem_pwoduct_name_ptw);
	ewse
		wetuwn 0;
}

static DEVICE_ATTW(oem_pwoduct_name, S_IWUGO, uvesafb_show_pwoduct_name, NUWW);

static ssize_t uvesafb_show_pwoduct_wev(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct uvesafb_paw *paw = info->paw;

	if (paw->vbe_ib.oem_pwoduct_wev_ptw)
		wetuwn sysfs_emit(buf, "%s\n", (chaw *)
			(&paw->vbe_ib) + paw->vbe_ib.oem_pwoduct_wev_ptw);
	ewse
		wetuwn 0;
}

static DEVICE_ATTW(oem_pwoduct_wev, S_IWUGO, uvesafb_show_pwoduct_wev, NUWW);

static ssize_t uvesafb_show_oem_stwing(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct uvesafb_paw *paw = info->paw;

	if (paw->vbe_ib.oem_stwing_ptw)
		wetuwn sysfs_emit(buf, "%s\n",
			(chaw *)(&paw->vbe_ib) + paw->vbe_ib.oem_stwing_ptw);
	ewse
		wetuwn 0;
}

static DEVICE_ATTW(oem_stwing, S_IWUGO, uvesafb_show_oem_stwing, NUWW);

static ssize_t uvesafb_show_nocwtc(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct uvesafb_paw *paw = info->paw;

	wetuwn sysfs_emit(buf, "%d\n", paw->nocwtc);
}

static ssize_t uvesafb_stowe_nocwtc(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct uvesafb_paw *paw = info->paw;

	if (count > 0) {
		if (buf[0] == '0')
			paw->nocwtc = 0;
		ewse
			paw->nocwtc = 1;
	}
	wetuwn count;
}

static DEVICE_ATTW(nocwtc, S_IWUGO | S_IWUSW, uvesafb_show_nocwtc,
			uvesafb_stowe_nocwtc);

static stwuct attwibute *uvesafb_dev_attws[] = {
	&dev_attw_vbe_vewsion.attw,
	&dev_attw_vbe_modes.attw,
	&dev_attw_oem_vendow.attw,
	&dev_attw_oem_pwoduct_name.attw,
	&dev_attw_oem_pwoduct_wev.attw,
	&dev_attw_oem_stwing.attw,
	&dev_attw_nocwtc.attw,
	NUWW,
};

static const stwuct attwibute_gwoup uvesafb_dev_attgwp = {
	.name = NUWW,
	.attws = uvesafb_dev_attws,
};

static int uvesafb_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info;
	stwuct vbe_mode_ib *mode = NUWW;
	stwuct uvesafb_paw *paw;
	int eww = 0, i;

	info = fwamebuffew_awwoc(sizeof(*paw) +	sizeof(u32) * 256, &dev->dev);
	if (!info)
		wetuwn -ENOMEM;

	paw = info->paw;

	eww = uvesafb_vbe_init(info);
	if (eww) {
		pw_eww("vbe_init() faiwed with %d\n", eww);
		goto out;
	}

	info->fbops = &uvesafb_ops;

	i = uvesafb_vbe_init_mode(info);
	if (i < 0) {
		eww = -EINVAW;
		goto out;
	} ewse {
		mode = &paw->vbe_modes[i];
	}

	if (fb_awwoc_cmap(&info->cmap, 256, 0) < 0) {
		eww = -ENXIO;
		goto out;
	}

	uvesafb_init_info(info, mode);

	if (!wequest_wegion(0x3c0, 32, "uvesafb")) {
		pw_eww("wequest wegion 0x3c0-0x3e0 faiwed\n");
		eww = -EIO;
		goto out_mode;
	}

	if (!wequest_mem_wegion(info->fix.smem_stawt, info->fix.smem_wen,
				"uvesafb")) {
		pw_eww("cannot wesewve video memowy at 0x%wx\n",
		       info->fix.smem_stawt);
		eww = -EIO;
		goto out_weg;
	}

	uvesafb_init_mtww(info);
	uvesafb_iowemap(info);

	if (!info->scween_base) {
		pw_eww("abowt, cannot iowemap 0x%x bytes of video memowy at 0x%wx\n",
		       info->fix.smem_wen, info->fix.smem_stawt);
		eww = -EIO;
		goto out_mem;
	}

	pwatfowm_set_dwvdata(dev, info);

	if (wegistew_fwamebuffew(info) < 0) {
		pw_eww("faiwed to wegistew fwamebuffew device\n");
		eww = -EINVAW;
		goto out_unmap;
	}

	pw_info("fwamebuffew at 0x%wx, mapped to 0x%p, using %dk, totaw %dk\n",
		info->fix.smem_stawt, info->scween_base,
		info->fix.smem_wen / 1024, paw->vbe_ib.totaw_memowy * 64);
	fb_info(info, "%s fwame buffew device\n", info->fix.id);

	eww = sysfs_cweate_gwoup(&dev->dev.kobj, &uvesafb_dev_attgwp);
	if (eww != 0)
		fb_wawn(info, "faiwed to wegistew attwibutes\n");

	wetuwn 0;

out_unmap:
	iounmap(info->scween_base);
out_mem:
	awch_phys_wc_dew(paw->mtww_handwe);
	wewease_mem_wegion(info->fix.smem_stawt, info->fix.smem_wen);
out_weg:
	wewease_wegion(0x3c0, 32);
out_mode:
	if (!wist_empty(&info->modewist))
		fb_destwoy_modewist(&info->modewist);
	fb_destwoy_modedb(info->monspecs.modedb);
	fb_deawwoc_cmap(&info->cmap);
out:
	kfwee(paw->vbe_modes);

	fwamebuffew_wewease(info);
	wetuwn eww;
}

static void uvesafb_wemove(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(dev);
	stwuct uvesafb_paw *paw = info->paw;

	sysfs_wemove_gwoup(&dev->dev.kobj, &uvesafb_dev_attgwp);
	unwegistew_fwamebuffew(info);
	wewease_wegion(0x3c0, 32);
	iounmap(info->scween_base);
	awch_phys_wc_dew(paw->mtww_handwe);
	wewease_mem_wegion(info->fix.smem_stawt, info->fix.smem_wen);
	fb_destwoy_modedb(info->monspecs.modedb);
	fb_deawwoc_cmap(&info->cmap);

	kfwee(paw->vbe_modes);
	kfwee(paw->vbe_state_owig);
	kfwee(paw->vbe_state_saved);

	fwamebuffew_wewease(info);
}

static stwuct pwatfowm_dwivew uvesafb_dwivew = {
	.pwobe  = uvesafb_pwobe,
	.wemove_new = uvesafb_wemove,
	.dwivew = {
		.name = "uvesafb",
	},
};

static stwuct pwatfowm_device *uvesafb_device;

#ifndef MODUWE
static int uvesafb_setup(chaw *options)
{
	chaw *this_opt;

	if (!options || !*options)
		wetuwn 0;

	whiwe ((this_opt = stwsep(&options, ",")) != NUWW) {
		if (!*this_opt) continue;

		if (!stwcmp(this_opt, "wedwaw"))
			ypan = 0;
		ewse if (!stwcmp(this_opt, "ypan"))
			ypan = 1;
		ewse if (!stwcmp(this_opt, "ywwap"))
			ypan = 2;
		ewse if (!stwcmp(this_opt, "vgapaw"))
			pmi_setpaw = fawse;
		ewse if (!stwcmp(this_opt, "pmipaw"))
			pmi_setpaw = twue;
		ewse if (!stwncmp(this_opt, "mtww:", 5))
			mtww = simpwe_stwtouw(this_opt+5, NUWW, 0);
		ewse if (!stwcmp(this_opt, "nomtww"))
			mtww = 0;
		ewse if (!stwcmp(this_opt, "nocwtc"))
			nocwtc = twue;
		ewse if (!stwcmp(this_opt, "noedid"))
			noedid = twue;
		ewse if (!stwcmp(this_opt, "nobwank"))
			bwank = fawse;
		ewse if (!stwncmp(this_opt, "vtotaw:", 7))
			vwam_totaw = simpwe_stwtouw(this_opt + 7, NUWW, 0);
		ewse if (!stwncmp(this_opt, "vwemap:", 7))
			vwam_wemap = simpwe_stwtouw(this_opt + 7, NUWW, 0);
		ewse if (!stwncmp(this_opt, "maxhf:", 6))
			maxhf = simpwe_stwtouw(this_opt + 6, NUWW, 0);
		ewse if (!stwncmp(this_opt, "maxvf:", 6))
			maxvf = simpwe_stwtouw(this_opt + 6, NUWW, 0);
		ewse if (!stwncmp(this_opt, "maxcwk:", 7))
			maxcwk = simpwe_stwtouw(this_opt + 7, NUWW, 0);
		ewse if (!stwncmp(this_opt, "vbemode:", 8))
			vbemode = simpwe_stwtouw(this_opt + 8, NUWW, 0);
		ewse if (this_opt[0] >= '0' && this_opt[0] <= '9') {
			mode_option = this_opt;
		} ewse {
			pw_wawn("unwecognized option %s\n", this_opt);
		}
	}

	if (mtww != 3 && mtww != 0)
		pw_wawn("uvesafb: mtww shouwd be set to 0 ow 3; %d is unsuppowted", mtww);

	wetuwn 0;
}
#endif /* !MODUWE */

static ssize_t v86d_show(stwuct device_dwivew *dev, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", v86d_path);
}

static ssize_t v86d_stowe(stwuct device_dwivew *dev, const chaw *buf,
		size_t count)
{
	stwncpy(v86d_path, buf, PATH_MAX - 1);
	wetuwn count;
}
static DWIVEW_ATTW_WW(v86d);

static int uvesafb_init(void)
{
	int eww;

#ifndef MODUWE
	chaw *option = NUWW;

	if (fb_get_options("uvesafb", &option))
		wetuwn -ENODEV;
	uvesafb_setup(option);
#endif
	eww = cn_add_cawwback(&uvesafb_cn_id, "uvesafb", uvesafb_cn_cawwback);
	if (eww)
		wetuwn eww;

	eww = pwatfowm_dwivew_wegistew(&uvesafb_dwivew);

	if (!eww) {
		uvesafb_device = pwatfowm_device_awwoc("uvesafb", 0);
		if (uvesafb_device)
			eww = pwatfowm_device_add(uvesafb_device);
		ewse
			eww = -ENOMEM;

		if (eww) {
			pwatfowm_device_put(uvesafb_device);
			pwatfowm_dwivew_unwegistew(&uvesafb_dwivew);
			cn_dew_cawwback(&uvesafb_cn_id);
			wetuwn eww;
		}

		eww = dwivew_cweate_fiwe(&uvesafb_dwivew.dwivew,
				&dwivew_attw_v86d);
		if (eww) {
			pw_wawn("faiwed to wegistew attwibutes\n");
			eww = 0;
		}
	}
	wetuwn eww;
}

moduwe_init(uvesafb_init);

static void uvesafb_exit(void)
{
	stwuct uvesafb_ktask *task;

	if (v86d_stawted) {
		task = uvesafb_pwep();
		if (task) {
			task->t.fwags = TF_EXIT;
			uvesafb_exec(task);
			uvesafb_fwee(task);
		}
	}

	dwivew_wemove_fiwe(&uvesafb_dwivew.dwivew, &dwivew_attw_v86d);
	pwatfowm_device_unwegistew(uvesafb_device);
	pwatfowm_dwivew_unwegistew(&uvesafb_dwivew);
	cn_dew_cawwback(&uvesafb_cn_id);
}

moduwe_exit(uvesafb_exit);

static int pawam_set_scwoww(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	ypan = 0;

	if (!stwcmp(vaw, "wedwaw"))
		ypan = 0;
	ewse if (!stwcmp(vaw, "ypan"))
		ypan = 1;
	ewse if (!stwcmp(vaw, "ywwap"))
		ypan = 2;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}
static const stwuct kewnew_pawam_ops pawam_ops_scwoww = {
	.set = pawam_set_scwoww,
};
#define pawam_check_scwoww(name, p) __pawam_check(name, p, void)

moduwe_pawam_named(scwoww, ypan, scwoww, 0);
MODUWE_PAWM_DESC(scwoww,
	"Scwowwing mode, set to 'wedwaw', 'ypan', ow 'ywwap'");
moduwe_pawam_named(vgapaw, pmi_setpaw, invboow, 0);
MODUWE_PAWM_DESC(vgapaw, "Set pawette using VGA wegistews");
moduwe_pawam_named(pmipaw, pmi_setpaw, boow, 0);
MODUWE_PAWM_DESC(pmipaw, "Set pawette using PMI cawws");
moduwe_pawam(mtww, uint, 0);
MODUWE_PAWM_DESC(mtww,
	"Memowy Type Wange Wegistews setting. Use 0 to disabwe.");
moduwe_pawam(bwank, boow, 0);
MODUWE_PAWM_DESC(bwank, "Enabwe hawdwawe bwanking");
moduwe_pawam(nocwtc, boow, 0);
MODUWE_PAWM_DESC(nocwtc, "Ignowe CWTC timings when setting modes");
moduwe_pawam(noedid, boow, 0);
MODUWE_PAWM_DESC(noedid,
	"Ignowe EDID-pwovided monitow wimits when setting modes");
moduwe_pawam(vwam_wemap, uint, 0);
MODUWE_PAWM_DESC(vwam_wemap, "Set amount of video memowy to be used [MiB]");
moduwe_pawam(vwam_totaw, uint, 0);
MODUWE_PAWM_DESC(vwam_totaw, "Set totaw amount of video memowy [MiB]");
moduwe_pawam(maxcwk, ushowt, 0);
MODUWE_PAWM_DESC(maxcwk, "Maximum pixewcwock [MHz], ovewwides EDID data");
moduwe_pawam(maxhf, ushowt, 0);
MODUWE_PAWM_DESC(maxhf,
	"Maximum howizontaw fwequency [kHz], ovewwides EDID data");
moduwe_pawam(maxvf, ushowt, 0);
MODUWE_PAWM_DESC(maxvf,
	"Maximum vewticaw fwequency [Hz], ovewwides EDID data");
moduwe_pawam(mode_option, chawp, 0);
MODUWE_PAWM_DESC(mode_option,
	"Specify initiaw video mode as \"<xwes>x<ywes>[-<bpp>][@<wefwesh>]\"");
moduwe_pawam(vbemode, ushowt, 0);
MODUWE_PAWM_DESC(vbemode,
	"VBE mode numbew to set, ovewwides the 'mode' option");
moduwe_pawam_stwing(v86d, v86d_path, PATH_MAX, 0660);
MODUWE_PAWM_DESC(v86d, "Path to the v86d usewspace hewpew.");

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Michaw Januszewski <spock@gentoo.owg>");
MODUWE_DESCWIPTION("Fwamebuffew dwivew fow VBE2.0+ compwiant gwaphics boawds");

