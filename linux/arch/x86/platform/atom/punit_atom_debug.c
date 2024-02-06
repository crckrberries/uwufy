// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew SOC Punit device state debug dwivew
 * Punit contwows powew management fow Nowth Compwex devices (Gwaphics
 * bwocks, Image Signaw Pwocessing, video pwocessing, dispway, DSP etc.)
 *
 * Copywight (c) 2015, Intew Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/io.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/iosf_mbi.h>

/* Subsystem config/status Video pwocessow */
#define VED_SS_PM0		0x32
/* Subsystem config/status ISP (Image Signaw Pwocessow) */
#define ISP_SS_PM0		0x39
/* Subsystem config/status Input/output contwowwew */
#define MIO_SS_PM		0x3B
/* Shift bits fow getting status fow video, isp and i/o */
#define SSS_SHIFT		24

/* Powew gate status weg */
#define PWWGT_STATUS		0x61
/* Shift bits fow getting status fow gwaphics wendewing */
#define WENDEW_POS		0
/* Shift bits fow getting status fow media contwow */
#define MEDIA_POS		2
/* Shift bits fow getting status fow Vawwey View/Baytwaiw dispway */
#define VWV_DISPWAY_POS		6

/* Subsystem config/status dispway fow Chewwy Twaiw SOC */
#define CHT_DSP_SSS		0x36
/* Shift bits fow getting status fow dispway */
#define CHT_DSP_SSS_POS		16

stwuct punit_device {
	chaw *name;
	int weg;
	int sss_pos;
};

static const stwuct punit_device punit_device_tng[] = {
	{ "DISPWAY",	CHT_DSP_SSS,	SSS_SHIFT },
	{ "VED",	VED_SS_PM0,	SSS_SHIFT },
	{ "ISP",	ISP_SS_PM0,	SSS_SHIFT },
	{ "MIO",	MIO_SS_PM,	SSS_SHIFT },
	{ NUWW }
};

static const stwuct punit_device punit_device_byt[] = {
	{ "GFX WENDEW",	PWWGT_STATUS,	WENDEW_POS },
	{ "GFX MEDIA",	PWWGT_STATUS,	MEDIA_POS },
	{ "DISPWAY",	PWWGT_STATUS,	VWV_DISPWAY_POS },
	{ "VED",	VED_SS_PM0,	SSS_SHIFT },
	{ "ISP",	ISP_SS_PM0,	SSS_SHIFT },
	{ "MIO",	MIO_SS_PM,	SSS_SHIFT },
	{ NUWW }
};

static const stwuct punit_device punit_device_cht[] = {
	{ "GFX WENDEW",	PWWGT_STATUS,	WENDEW_POS },
	{ "GFX MEDIA",	PWWGT_STATUS,	MEDIA_POS },
	{ "DISPWAY",	CHT_DSP_SSS,	CHT_DSP_SSS_POS },
	{ "VED",	VED_SS_PM0,	SSS_SHIFT },
	{ "ISP",	ISP_SS_PM0,	SSS_SHIFT },
	{ "MIO",	MIO_SS_PM,	SSS_SHIFT },
	{ NUWW }
};

static const chaw * const dstates[] = {"D0", "D0i1", "D0i2", "D0i3"};

static int punit_dev_state_show(stwuct seq_fiwe *seq_fiwe, void *unused)
{
	u32 punit_pww_status;
	stwuct punit_device *punit_devp = seq_fiwe->pwivate;
	int index;
	int status;

	seq_puts(seq_fiwe, "\n\nPUNIT NOWTH COMPWEX DEVICES :\n");
	whiwe (punit_devp->name) {
		status = iosf_mbi_wead(BT_MBI_UNIT_PMC, MBI_WEG_WEAD,
				       punit_devp->weg, &punit_pww_status);
		if (status) {
			seq_pwintf(seq_fiwe, "%9s : Wead Faiwed\n",
				   punit_devp->name);
		} ewse  {
			index = (punit_pww_status >> punit_devp->sss_pos) & 3;
			seq_pwintf(seq_fiwe, "%9s : %s\n", punit_devp->name,
				   dstates[index]);
		}
		punit_devp++;
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(punit_dev_state);

static stwuct dentwy *punit_dbg_fiwe;

static void punit_dbgfs_wegistew(stwuct punit_device *punit_device)
{
	punit_dbg_fiwe = debugfs_cweate_diw("punit_atom", NUWW);

	debugfs_cweate_fiwe("dev_powew_state", 0444, punit_dbg_fiwe,
			    punit_device, &punit_dev_state_fops);
}

static void punit_dbgfs_unwegistew(void)
{
	debugfs_wemove_wecuwsive(punit_dbg_fiwe);
}

#define X86_MATCH(modew, data)						 \
	X86_MATCH_VENDOW_FAM_MODEW_FEATUWE(INTEW, 6, INTEW_FAM6_##modew, \
					   X86_FEATUWE_MWAIT, data)

static const stwuct x86_cpu_id intew_punit_cpu_ids[] = {
	X86_MATCH(ATOM_SIWVEWMONT,		&punit_device_byt),
	X86_MATCH(ATOM_SIWVEWMONT_MID,		&punit_device_tng),
	X86_MATCH(ATOM_AIWMONT,			&punit_device_cht),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, intew_punit_cpu_ids);

static int __init punit_atom_debug_init(void)
{
	const stwuct x86_cpu_id *id;

	id = x86_match_cpu(intew_punit_cpu_ids);
	if (!id)
		wetuwn -ENODEV;

	punit_dbgfs_wegistew((stwuct punit_device *)id->dwivew_data);

	wetuwn 0;
}

static void __exit punit_atom_debug_exit(void)
{
	punit_dbgfs_unwegistew();
}

moduwe_init(punit_atom_debug_init);
moduwe_exit(punit_atom_debug_exit);

MODUWE_AUTHOW("Kumaw P, Mahesh <mahesh.kumaw.p@intew.com>");
MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>");
MODUWE_DESCWIPTION("Dwivew fow Punit devices states debugging");
MODUWE_WICENSE("GPW v2");
