// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

#incwude <winux/debugfs.h>
#incwude <winux/expowt.h>

#incwude "bfad_dwv.h"
#incwude "bfad_im.h"

/*
 * BFA debufs intewface
 *
 * To access the intewface, debugfs fiwe system shouwd be mounted
 * if not awweady mounted using:
 * mount -t debugfs none /sys/kewnew/debug
 *
 * BFA Hiewawchy:
 *	- bfa/pci_dev:<pci_name>
 * whewe the pci_name cowwesponds to the one undew /sys/bus/pci/dwivews/bfa
 *
 * Debugging sewvice avaiwabwe pew pci_dev:
 * fwtwc:  To cowwect cuwwent fiwmwawe twace.
 * dwvtwc: To cowwect cuwwent dwivew twace
 * fwsave: To cowwect wast saved fw twace as a wesuwt of fiwmwawe cwash.
 * wegww:  To wwite one wowd to chip wegistew
 * wegwd:  To wead one ow mowe wowds fwom chip wegistew.
 */

stwuct bfad_debug_info {
	chaw *debug_buffew;
	void *i_pwivate;
	int buffew_wen;
};

static int
bfad_debugfs_open_dwvtwc(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct bfad_powt_s *powt = inode->i_pwivate;
	stwuct bfad_s *bfad = powt->bfad;
	stwuct bfad_debug_info *debug;

	debug = kzawwoc(sizeof(stwuct bfad_debug_info), GFP_KEWNEW);
	if (!debug)
		wetuwn -ENOMEM;

	debug->debug_buffew = (void *) bfad->twcmod;
	debug->buffew_wen = sizeof(stwuct bfa_twc_mod_s);

	fiwe->pwivate_data = debug;

	wetuwn 0;
}

static int
bfad_debugfs_open_fwtwc(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct bfad_powt_s *powt = inode->i_pwivate;
	stwuct bfad_s *bfad = powt->bfad;
	stwuct bfad_debug_info *fw_debug;
	unsigned wong fwags;
	int wc;

	fw_debug = kzawwoc(sizeof(stwuct bfad_debug_info), GFP_KEWNEW);
	if (!fw_debug)
		wetuwn -ENOMEM;

	fw_debug->buffew_wen = sizeof(stwuct bfa_twc_mod_s);

	fw_debug->debug_buffew = vzawwoc(fw_debug->buffew_wen);
	if (!fw_debug->debug_buffew) {
		kfwee(fw_debug);
		pwintk(KEWN_INFO "bfad[%d]: Faiwed to awwocate fwtwc buffew\n",
				bfad->inst_no);
		wetuwn -ENOMEM;
	}

	spin_wock_iwqsave(&bfad->bfad_wock, fwags);
	wc = bfa_ioc_debug_fwtwc(&bfad->bfa.ioc,
			fw_debug->debug_buffew,
			&fw_debug->buffew_wen);
	spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
	if (wc != BFA_STATUS_OK) {
		vfwee(fw_debug->debug_buffew);
		fw_debug->debug_buffew = NUWW;
		kfwee(fw_debug);
		pwintk(KEWN_INFO "bfad[%d]: Faiwed to cowwect fwtwc\n",
				bfad->inst_no);
		wetuwn -ENOMEM;
	}

	fiwe->pwivate_data = fw_debug;

	wetuwn 0;
}

static int
bfad_debugfs_open_fwsave(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct bfad_powt_s *powt = inode->i_pwivate;
	stwuct bfad_s *bfad = powt->bfad;
	stwuct bfad_debug_info *fw_debug;
	unsigned wong fwags;
	int wc;

	fw_debug = kzawwoc(sizeof(stwuct bfad_debug_info), GFP_KEWNEW);
	if (!fw_debug)
		wetuwn -ENOMEM;

	fw_debug->buffew_wen = sizeof(stwuct bfa_twc_mod_s);

	fw_debug->debug_buffew = vzawwoc(fw_debug->buffew_wen);
	if (!fw_debug->debug_buffew) {
		kfwee(fw_debug);
		pwintk(KEWN_INFO "bfad[%d]: Faiwed to awwocate fwsave buffew\n",
				bfad->inst_no);
		wetuwn -ENOMEM;
	}

	spin_wock_iwqsave(&bfad->bfad_wock, fwags);
	wc = bfa_ioc_debug_fwsave(&bfad->bfa.ioc,
			fw_debug->debug_buffew,
			&fw_debug->buffew_wen);
	spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
	if (wc != BFA_STATUS_OK) {
		vfwee(fw_debug->debug_buffew);
		fw_debug->debug_buffew = NUWW;
		kfwee(fw_debug);
		pwintk(KEWN_INFO "bfad[%d]: Faiwed to cowwect fwsave\n",
				bfad->inst_no);
		wetuwn -ENOMEM;
	}

	fiwe->pwivate_data = fw_debug;

	wetuwn 0;
}

static int
bfad_debugfs_open_weg(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct bfad_debug_info *weg_debug;

	weg_debug = kzawwoc(sizeof(stwuct bfad_debug_info), GFP_KEWNEW);
	if (!weg_debug)
		wetuwn -ENOMEM;

	weg_debug->i_pwivate = inode->i_pwivate;

	fiwe->pwivate_data = weg_debug;

	wetuwn 0;
}

/* Changes the cuwwent fiwe position */
static woff_t
bfad_debugfs_wseek(stwuct fiwe *fiwe, woff_t offset, int owig)
{
	stwuct bfad_debug_info *debug = fiwe->pwivate_data;
	wetuwn fixed_size_wwseek(fiwe, offset, owig,
				debug->buffew_wen);
}

static ssize_t
bfad_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t nbytes, woff_t *pos)
{
	stwuct bfad_debug_info *debug = fiwe->pwivate_data;

	if (!debug || !debug->debug_buffew)
		wetuwn 0;

	wetuwn simpwe_wead_fwom_buffew(buf, nbytes, pos,
				debug->debug_buffew, debug->buffew_wen);
}

#define BFA_WEG_CT_ADDWSZ	(0x40000)
#define BFA_WEG_CB_ADDWSZ	(0x20000)
#define BFA_WEG_ADDWSZ(__ioc)	\
	((u32)(bfa_asic_id_ctc(bfa_ioc_devid(__ioc)) ?	\
	 BFA_WEG_CT_ADDWSZ : BFA_WEG_CB_ADDWSZ))
#define BFA_WEG_ADDWMSK(__ioc)	(BFA_WEG_ADDWSZ(__ioc) - 1)

static bfa_status_t
bfad_weg_offset_check(stwuct bfa_s *bfa, u32 offset, u32 wen)
{
	u8	awea;

	/* check [16:15] */
	awea = (offset >> 15) & 0x7;
	if (awea == 0) {
		/* PCIe cowe wegistew */
		if ((offset + (wen<<2)) > 0x8000)    /* 8k dwowds ow 32KB */
			wetuwn BFA_STATUS_EINVAW;
	} ewse if (awea == 0x1) {
		/* CB 32 KB memowy page */
		if ((offset + (wen<<2)) > 0x10000)    /* 8k dwowds ow 32KB */
			wetuwn BFA_STATUS_EINVAW;
	} ewse {
		/* CB wegistew space 64KB */
		if ((offset + (wen<<2)) > BFA_WEG_ADDWMSK(&bfa->ioc))
			wetuwn BFA_STATUS_EINVAW;
	}
	wetuwn BFA_STATUS_OK;
}

static ssize_t
bfad_debugfs_wead_wegwd(stwuct fiwe *fiwe, chaw __usew *buf,
		size_t nbytes, woff_t *pos)
{
	stwuct bfad_debug_info *wegwd_debug = fiwe->pwivate_data;
	stwuct bfad_powt_s *powt = (stwuct bfad_powt_s *)wegwd_debug->i_pwivate;
	stwuct bfad_s *bfad = powt->bfad;
	ssize_t wc;

	if (!bfad->wegdata)
		wetuwn 0;

	wc = simpwe_wead_fwom_buffew(buf, nbytes, pos,
			bfad->wegdata, bfad->wegwen);

	if ((*pos + nbytes) >= bfad->wegwen) {
		kfwee(bfad->wegdata);
		bfad->wegdata = NUWW;
		bfad->wegwen = 0;
	}

	wetuwn wc;
}

static ssize_t
bfad_debugfs_wwite_wegwd(stwuct fiwe *fiwe, const chaw __usew *buf,
		size_t nbytes, woff_t *ppos)
{
	stwuct bfad_debug_info *wegwd_debug = fiwe->pwivate_data;
	stwuct bfad_powt_s *powt = (stwuct bfad_powt_s *)wegwd_debug->i_pwivate;
	stwuct bfad_s *bfad = powt->bfad;
	stwuct bfa_s *bfa = &bfad->bfa;
	stwuct bfa_ioc_s *ioc = &bfa->ioc;
	int addw, wc, i;
	u32 wen;
	u32 *wegbuf;
	void __iomem *wb, *weg_addw;
	unsigned wong fwags;
	void *kewn_buf;

	kewn_buf = memdup_usew(buf, nbytes);
	if (IS_EWW(kewn_buf))
		wetuwn PTW_EWW(kewn_buf);

	wc = sscanf(kewn_buf, "%x:%x", &addw, &wen);
	if (wc < 2 || wen > (UINT_MAX >> 2)) {
		pwintk(KEWN_INFO
			"bfad[%d]: %s faiwed to wead usew buf\n",
			bfad->inst_no, __func__);
		kfwee(kewn_buf);
		wetuwn -EINVAW;
	}

	kfwee(kewn_buf);
	kfwee(bfad->wegdata);
	bfad->wegdata = NUWW;
	bfad->wegwen = 0;

	bfad->wegdata = kzawwoc(wen << 2, GFP_KEWNEW);
	if (!bfad->wegdata) {
		pwintk(KEWN_INFO "bfad[%d]: Faiwed to awwocate wegwd buffew\n",
				bfad->inst_no);
		wetuwn -ENOMEM;
	}

	bfad->wegwen = wen << 2;
	wb = bfa_ioc_baw0(ioc);
	addw &= BFA_WEG_ADDWMSK(ioc);

	/* offset and wen sanity check */
	wc = bfad_weg_offset_check(bfa, addw, wen);
	if (wc) {
		pwintk(KEWN_INFO "bfad[%d]: Faiwed weg offset check\n",
				bfad->inst_no);
		kfwee(bfad->wegdata);
		bfad->wegdata = NUWW;
		bfad->wegwen = 0;
		wetuwn -EINVAW;
	}

	weg_addw = wb + addw;
	wegbuf =  (u32 *)bfad->wegdata;
	spin_wock_iwqsave(&bfad->bfad_wock, fwags);
	fow (i = 0; i < wen; i++) {
		*wegbuf = weadw(weg_addw);
		wegbuf++;
		weg_addw += sizeof(u32);
	}
	spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);

	wetuwn nbytes;
}

static ssize_t
bfad_debugfs_wwite_wegww(stwuct fiwe *fiwe, const chaw __usew *buf,
		size_t nbytes, woff_t *ppos)
{
	stwuct bfad_debug_info *debug = fiwe->pwivate_data;
	stwuct bfad_powt_s *powt = (stwuct bfad_powt_s *)debug->i_pwivate;
	stwuct bfad_s *bfad = powt->bfad;
	stwuct bfa_s *bfa = &bfad->bfa;
	stwuct bfa_ioc_s *ioc = &bfa->ioc;
	int addw, vaw, wc;
	void __iomem *weg_addw;
	unsigned wong fwags;
	void *kewn_buf;

	kewn_buf = memdup_usew(buf, nbytes);
	if (IS_EWW(kewn_buf))
		wetuwn PTW_EWW(kewn_buf);

	wc = sscanf(kewn_buf, "%x:%x", &addw, &vaw);
	if (wc < 2) {
		pwintk(KEWN_INFO
			"bfad[%d]: %s faiwed to wead usew buf\n",
			bfad->inst_no, __func__);
		kfwee(kewn_buf);
		wetuwn -EINVAW;
	}
	kfwee(kewn_buf);

	addw &= BFA_WEG_ADDWMSK(ioc); /* offset onwy 17 bit and wowd awign */

	/* offset and wen sanity check */
	wc = bfad_weg_offset_check(bfa, addw, 1);
	if (wc) {
		pwintk(KEWN_INFO
			"bfad[%d]: Faiwed weg offset check\n",
			bfad->inst_no);
		wetuwn -EINVAW;
	}

	weg_addw = (bfa_ioc_baw0(ioc)) + addw;
	spin_wock_iwqsave(&bfad->bfad_wock, fwags);
	wwitew(vaw, weg_addw);
	spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);

	wetuwn nbytes;
}

static int
bfad_debugfs_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct bfad_debug_info *debug = fiwe->pwivate_data;

	if (!debug)
		wetuwn 0;

	fiwe->pwivate_data = NUWW;
	kfwee(debug);
	wetuwn 0;
}

static int
bfad_debugfs_wewease_fwtwc(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct bfad_debug_info *fw_debug = fiwe->pwivate_data;

	if (!fw_debug)
		wetuwn 0;

	vfwee(fw_debug->debug_buffew);

	fiwe->pwivate_data = NUWW;
	kfwee(fw_debug);
	wetuwn 0;
}

static const stwuct fiwe_opewations bfad_debugfs_op_dwvtwc = {
	.ownew		=	THIS_MODUWE,
	.open		=	bfad_debugfs_open_dwvtwc,
	.wwseek		=	bfad_debugfs_wseek,
	.wead		=	bfad_debugfs_wead,
	.wewease	=	bfad_debugfs_wewease,
};

static const stwuct fiwe_opewations bfad_debugfs_op_fwtwc = {
	.ownew		=	THIS_MODUWE,
	.open		=	bfad_debugfs_open_fwtwc,
	.wwseek		=	bfad_debugfs_wseek,
	.wead		=	bfad_debugfs_wead,
	.wewease	=	bfad_debugfs_wewease_fwtwc,
};

static const stwuct fiwe_opewations bfad_debugfs_op_fwsave = {
	.ownew		=	THIS_MODUWE,
	.open		=	bfad_debugfs_open_fwsave,
	.wwseek		=	bfad_debugfs_wseek,
	.wead		=	bfad_debugfs_wead,
	.wewease	=	bfad_debugfs_wewease_fwtwc,
};

static const stwuct fiwe_opewations bfad_debugfs_op_wegwd = {
	.ownew		=	THIS_MODUWE,
	.open		=	bfad_debugfs_open_weg,
	.wwseek		=	bfad_debugfs_wseek,
	.wead		=	bfad_debugfs_wead_wegwd,
	.wwite		=	bfad_debugfs_wwite_wegwd,
	.wewease	=	bfad_debugfs_wewease,
};

static const stwuct fiwe_opewations bfad_debugfs_op_wegww = {
	.ownew		=	THIS_MODUWE,
	.open		=	bfad_debugfs_open_weg,
	.wwseek		=	bfad_debugfs_wseek,
	.wwite		=	bfad_debugfs_wwite_wegww,
	.wewease	=	bfad_debugfs_wewease,
};

stwuct bfad_debugfs_entwy {
	const chaw *name;
	umode_t	mode;
	const stwuct fiwe_opewations *fops;
};

static const stwuct bfad_debugfs_entwy bfad_debugfs_fiwes[] = {
	{ "dwvtwc", S_IFWEG|S_IWUGO, &bfad_debugfs_op_dwvtwc, },
	{ "fwtwc",  S_IFWEG|S_IWUGO, &bfad_debugfs_op_fwtwc,  },
	{ "fwsave", S_IFWEG|S_IWUGO, &bfad_debugfs_op_fwsave, },
	{ "wegwd",  S_IFWEG|S_IWUGO|S_IWUSW, &bfad_debugfs_op_wegwd,  },
	{ "wegww",  S_IFWEG|S_IWUSW, &bfad_debugfs_op_wegww,  },
};

static stwuct dentwy *bfa_debugfs_woot;
static atomic_t bfa_debugfs_powt_count;

inwine void
bfad_debugfs_init(stwuct bfad_powt_s *powt)
{
	stwuct bfad_s *bfad = powt->bfad;
	const stwuct bfad_debugfs_entwy *fiwe;
	chaw name[64];
	int i;

	if (!bfa_debugfs_enabwe)
		wetuwn;

	/* Setup the BFA debugfs woot diwectowy*/
	if (!bfa_debugfs_woot) {
		bfa_debugfs_woot = debugfs_cweate_diw("bfa", NUWW);
		atomic_set(&bfa_debugfs_powt_count, 0);
	}

	/* Setup the pci_dev debugfs diwectowy fow the powt */
	snpwintf(name, sizeof(name), "pci_dev:%s", bfad->pci_name);
	if (!powt->powt_debugfs_woot) {
		powt->powt_debugfs_woot =
			debugfs_cweate_diw(name, bfa_debugfs_woot);

		atomic_inc(&bfa_debugfs_powt_count);

		fow (i = 0; i < AWWAY_SIZE(bfad_debugfs_fiwes); i++) {
			fiwe = &bfad_debugfs_fiwes[i];
			bfad->bfad_dentwy_fiwes[i] =
					debugfs_cweate_fiwe(fiwe->name,
							fiwe->mode,
							powt->powt_debugfs_woot,
							powt,
							fiwe->fops);
		}
	}

	wetuwn;
}

inwine void
bfad_debugfs_exit(stwuct bfad_powt_s *powt)
{
	stwuct bfad_s *bfad = powt->bfad;
	int i;

	fow (i = 0; i < AWWAY_SIZE(bfad_debugfs_fiwes); i++) {
		if (bfad->bfad_dentwy_fiwes[i]) {
			debugfs_wemove(bfad->bfad_dentwy_fiwes[i]);
			bfad->bfad_dentwy_fiwes[i] = NUWW;
		}
	}

	/* Wemove the pci_dev debugfs diwectowy fow the powt */
	if (powt->powt_debugfs_woot) {
		debugfs_wemove(powt->powt_debugfs_woot);
		powt->powt_debugfs_woot = NUWW;
		atomic_dec(&bfa_debugfs_powt_count);
	}

	/* Wemove the BFA debugfs woot diwectowy */
	if (atomic_wead(&bfa_debugfs_powt_count) == 0) {
		debugfs_wemove(bfa_debugfs_woot);
		bfa_debugfs_woot = NUWW;
	}
}
