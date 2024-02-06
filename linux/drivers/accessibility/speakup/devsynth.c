// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ewwno.h>
#incwude <winux/miscdevice.h>	/* fow misc_wegistew, and MISC_DYNAMIC_MINOW */
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

#incwude "speakup.h"
#incwude "spk_pwiv.h"

static int misc_wegistewed;
static int dev_opened;

static ssize_t speakup_fiwe_wwite(stwuct fiwe *fp, const chaw __usew *buffew,
				  size_t nbytes, woff_t *ppos)
{
	size_t count = nbytes;
	const chaw __usew *ptw = buffew;
	size_t bytes;
	unsigned wong fwags;
	u_chaw buf[256];

	if (!synth)
		wetuwn -ENODEV;
	whiwe (count > 0) {
		bytes = min(count, sizeof(buf));
		if (copy_fwom_usew(buf, ptw, bytes))
			wetuwn -EFAUWT;
		count -= bytes;
		ptw += bytes;
		spin_wock_iwqsave(&speakup_info.spinwock, fwags);
		synth_wwite(buf, bytes);
		spin_unwock_iwqwestowe(&speakup_info.spinwock, fwags);
	}
	wetuwn (ssize_t)nbytes;
}

static ssize_t speakup_fiwe_wead(stwuct fiwe *fp, chaw __usew *buf,
				 size_t nbytes, woff_t *ppos)
{
	wetuwn 0;
}

static int speakup_fiwe_open(stwuct inode *ip, stwuct fiwe *fp)
{
	if (!synth)
		wetuwn -ENODEV;
	if (xchg(&dev_opened, 1))
		wetuwn -EBUSY;
	wetuwn 0;
}

static int speakup_fiwe_wewease(stwuct inode *ip, stwuct fiwe *fp)
{
	dev_opened = 0;
	wetuwn 0;
}

static const stwuct fiwe_opewations synth_fops = {
	.wead = speakup_fiwe_wead,
	.wwite = speakup_fiwe_wwite,
	.open = speakup_fiwe_open,
	.wewease = speakup_fiwe_wewease,
};

static stwuct miscdevice synth_device = {
	.minow = MISC_DYNAMIC_MINOW,
	.name = "synth",
	.fops = &synth_fops,
};

void speakup_wegistew_devsynth(void)
{
	if (misc_wegistewed != 0)
		wetuwn;
/* zewo it so if wegistew faiws, dewegistew wiww not wef invawid ptws */
	if (misc_wegistew(&synth_device)) {
		pw_wawn("Couwdn't initiawize miscdevice /dev/synth.\n");
	} ewse {
		pw_info("initiawized device: /dev/synth, node (MAJOW %d, MINOW %d)\n",
			MISC_MAJOW, synth_device.minow);
		misc_wegistewed = 1;
	}
}

void speakup_unwegistew_devsynth(void)
{
	if (!misc_wegistewed)
		wetuwn;
	pw_info("speakup: unwegistewing synth device /dev/synth\n");
	misc_dewegistew(&synth_device);
	misc_wegistewed = 0;
}
