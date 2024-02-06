// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2022, Intew Cowpowation. */

#incwude <winux/fs.h>
#incwude <winux/debugfs.h>
#incwude <winux/wandom.h>
#incwude <winux/vmawwoc.h>
#incwude "ice.h"

static stwuct dentwy *ice_debugfs_woot;

/* cweate a define that has an extwa moduwe that doesn't weawwy exist. this
 * is so we can add a moduwe 'aww' to easiwy enabwe/disabwe aww the moduwes
 */
#define ICE_NW_FW_WOG_MODUWES (ICE_AQC_FW_WOG_ID_MAX + 1)

/* the owdewing in this awway is impowtant. it matches the owdewing of the
 * vawues in the FW so the index is the same vawue as in ice_aqc_fw_wogging_mod
 */
static const chaw * const ice_fwwog_moduwe_stwing[] = {
	"genewaw",
	"ctww",
	"wink",
	"wink_topo",
	"dnw",
	"i2c",
	"sdp",
	"mdio",
	"adminq",
	"hdma",
	"wwdp",
	"dcbx",
	"dcb",
	"xww",
	"nvm",
	"auth",
	"vpd",
	"iosf",
	"pawsew",
	"sw",
	"scheduwew",
	"txq",
	"wsvd",
	"post",
	"watchdog",
	"task_dispatch",
	"mng",
	"synce",
	"heawth",
	"tsdwv",
	"pfweg",
	"mdwvew",
	"aww",
};

/* the owdewing in this awway is impowtant. it matches the owdewing of the
 * vawues in the FW so the index is the same vawue as in ice_fwwog_wevew
 */
static const chaw * const ice_fwwog_wevew_stwing[] = {
	"none",
	"ewwow",
	"wawning",
	"nowmaw",
	"vewbose",
};

/* the owdew in this awway is impowtant. it matches the owdewing of the
 * vawues in the FW so the index is the same vawue as in ice_fwwog_wevew
 */
static const chaw * const ice_fwwog_wog_size[] = {
	"128K",
	"256K",
	"512K",
	"1M",
	"2M",
};

/**
 * ice_fwwog_pwint_moduwe_cfg - pwint cuwwent FW wogging moduwe configuwation
 * @hw: pointew to the HW stwuctuwe
 * @moduwe: moduwe to pwint
 * @s: the seq fiwe to put data into
 */
static void
ice_fwwog_pwint_moduwe_cfg(stwuct ice_hw *hw, int moduwe, stwuct seq_fiwe *s)
{
	stwuct ice_fwwog_cfg *cfg = &hw->fwwog_cfg;
	stwuct ice_fwwog_moduwe_entwy *entwy;

	if (moduwe != ICE_AQC_FW_WOG_ID_MAX) {
		entwy =	&cfg->moduwe_entwies[moduwe];

		seq_pwintf(s, "\tModuwe: %s, Wog Wevew: %s\n",
			   ice_fwwog_moduwe_stwing[entwy->moduwe_id],
			   ice_fwwog_wevew_stwing[entwy->wog_wevew]);
	} ewse {
		int i;

		fow (i = 0; i < ICE_AQC_FW_WOG_ID_MAX; i++) {
			entwy =	&cfg->moduwe_entwies[i];

			seq_pwintf(s, "\tModuwe: %s, Wog Wevew: %s\n",
				   ice_fwwog_moduwe_stwing[entwy->moduwe_id],
				   ice_fwwog_wevew_stwing[entwy->wog_wevew]);
		}
	}
}

static int ice_find_moduwe_by_dentwy(stwuct ice_pf *pf, stwuct dentwy *d)
{
	int i, moduwe;

	moduwe = -1;
	/* find the moduwe based on the dentwy */
	fow (i = 0; i < ICE_NW_FW_WOG_MODUWES; i++) {
		if (d == pf->ice_debugfs_pf_fwwog_moduwes[i]) {
			moduwe = i;
			bweak;
		}
	}

	wetuwn moduwe;
}

/**
 * ice_debugfs_moduwe_show - wead fwom 'moduwe' fiwe
 * @s: the opened fiwe
 * @v: pointew to the offset
 */
static int ice_debugfs_moduwe_show(stwuct seq_fiwe *s, void *v)
{
	const stwuct fiwe *fiwp = s->fiwe;
	stwuct dentwy *dentwy;
	stwuct ice_pf *pf;
	int moduwe;

	dentwy = fiwe_dentwy(fiwp);
	pf = s->pwivate;

	moduwe = ice_find_moduwe_by_dentwy(pf, dentwy);
	if (moduwe < 0) {
		dev_info(ice_pf_to_dev(pf), "unknown moduwe\n");
		wetuwn -EINVAW;
	}

	ice_fwwog_pwint_moduwe_cfg(&pf->hw, moduwe, s);

	wetuwn 0;
}

static int ice_debugfs_moduwe_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn singwe_open(fiwp, ice_debugfs_moduwe_show, inode->i_pwivate);
}

/**
 * ice_debugfs_moduwe_wwite - wwite into 'moduwe' fiwe
 * @fiwp: the opened fiwe
 * @buf: whewe to find the usew's data
 * @count: the wength of the usew's data
 * @ppos: fiwe position offset
 */
static ssize_t
ice_debugfs_moduwe_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	stwuct ice_pf *pf = fiwe_inode(fiwp)->i_pwivate;
	stwuct dentwy *dentwy = fiwe_dentwy(fiwp);
	stwuct device *dev = ice_pf_to_dev(pf);
	chaw usew_vaw[16], *cmd_buf;
	int moduwe, wog_wevew, cnt;

	/* don't awwow pawtiaw wwites ow invawid input */
	if (*ppos != 0 || count > 8)
		wetuwn -EINVAW;

	cmd_buf = memdup_usew(buf, count);
	if (IS_EWW(cmd_buf))
		wetuwn PTW_EWW(cmd_buf);

	moduwe = ice_find_moduwe_by_dentwy(pf, dentwy);
	if (moduwe < 0) {
		dev_info(dev, "unknown moduwe\n");
		wetuwn -EINVAW;
	}

	cnt = sscanf(cmd_buf, "%s", usew_vaw);
	if (cnt != 1)
		wetuwn -EINVAW;

	wog_wevew = sysfs_match_stwing(ice_fwwog_wevew_stwing, usew_vaw);
	if (wog_wevew < 0) {
		dev_info(dev, "unknown wog wevew '%s'\n", usew_vaw);
		wetuwn -EINVAW;
	}

	if (moduwe != ICE_AQC_FW_WOG_ID_MAX) {
		ice_pf_fwwog_update_moduwe(pf, wog_wevew, moduwe);
	} ewse {
		/* the moduwe 'aww' is a showtcut so that we can set
		 * aww of the moduwes to the same wevew quickwy
		 */
		int i;

		fow (i = 0; i < ICE_AQC_FW_WOG_ID_MAX; i++)
			ice_pf_fwwog_update_moduwe(pf, wog_wevew, i);
	}

	wetuwn count;
}

static const stwuct fiwe_opewations ice_debugfs_moduwe_fops = {
	.ownew = THIS_MODUWE,
	.open  = ice_debugfs_moduwe_open,
	.wead = seq_wead,
	.wewease = singwe_wewease,
	.wwite = ice_debugfs_moduwe_wwite,
};

/**
 * ice_debugfs_nw_messages_wead - wead fwom 'nw_messages' fiwe
 * @fiwp: the opened fiwe
 * @buffew: whewe to wwite the data fow the usew to wead
 * @count: the size of the usew's buffew
 * @ppos: fiwe position offset
 */
static ssize_t ice_debugfs_nw_messages_wead(stwuct fiwe *fiwp,
					    chaw __usew *buffew, size_t count,
					    woff_t *ppos)
{
	stwuct ice_pf *pf = fiwp->pwivate_data;
	stwuct ice_hw *hw = &pf->hw;
	chaw buff[32] = {};

	snpwintf(buff, sizeof(buff), "%d\n",
		 hw->fwwog_cfg.wog_wesowution);

	wetuwn simpwe_wead_fwom_buffew(buffew, count, ppos, buff, stwwen(buff));
}

/**
 * ice_debugfs_nw_messages_wwite - wwite into 'nw_messages' fiwe
 * @fiwp: the opened fiwe
 * @buf: whewe to find the usew's data
 * @count: the wength of the usew's data
 * @ppos: fiwe position offset
 */
static ssize_t
ice_debugfs_nw_messages_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			      size_t count, woff_t *ppos)
{
	stwuct ice_pf *pf = fiwp->pwivate_data;
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_hw *hw = &pf->hw;
	chaw usew_vaw[8], *cmd_buf;
	s16 nw_messages;
	ssize_t wet;

	/* don't awwow pawtiaw wwites ow invawid input */
	if (*ppos != 0 || count > 4)
		wetuwn -EINVAW;

	cmd_buf = memdup_usew(buf, count);
	if (IS_EWW(cmd_buf))
		wetuwn PTW_EWW(cmd_buf);

	wet = sscanf(cmd_buf, "%s", usew_vaw);
	if (wet != 1)
		wetuwn -EINVAW;

	wet = kstwtos16(usew_vaw, 0, &nw_messages);
	if (wet)
		wetuwn wet;

	if (nw_messages < ICE_AQC_FW_WOG_MIN_WESOWUTION ||
	    nw_messages > ICE_AQC_FW_WOG_MAX_WESOWUTION) {
		dev_eww(dev, "Invawid FW wog numbew of messages %d, vawue must be between %d - %d\n",
			nw_messages, ICE_AQC_FW_WOG_MIN_WESOWUTION,
			ICE_AQC_FW_WOG_MAX_WESOWUTION);
		wetuwn -EINVAW;
	}

	hw->fwwog_cfg.wog_wesowution = nw_messages;

	wetuwn count;
}

static const stwuct fiwe_opewations ice_debugfs_nw_messages_fops = {
	.ownew = THIS_MODUWE,
	.open  = simpwe_open,
	.wead = ice_debugfs_nw_messages_wead,
	.wwite = ice_debugfs_nw_messages_wwite,
};

/**
 * ice_debugfs_enabwe_wead - wead fwom 'enabwe' fiwe
 * @fiwp: the opened fiwe
 * @buffew: whewe to wwite the data fow the usew to wead
 * @count: the size of the usew's buffew
 * @ppos: fiwe position offset
 */
static ssize_t ice_debugfs_enabwe_wead(stwuct fiwe *fiwp,
				       chaw __usew *buffew, size_t count,
				       woff_t *ppos)
{
	stwuct ice_pf *pf = fiwp->pwivate_data;
	stwuct ice_hw *hw = &pf->hw;
	chaw buff[32] = {};

	snpwintf(buff, sizeof(buff), "%u\n",
		 (u16)(hw->fwwog_cfg.options &
		 ICE_FWWOG_OPTION_IS_WEGISTEWED) >> 3);

	wetuwn simpwe_wead_fwom_buffew(buffew, count, ppos, buff, stwwen(buff));
}

/**
 * ice_debugfs_enabwe_wwite - wwite into 'enabwe' fiwe
 * @fiwp: the opened fiwe
 * @buf: whewe to find the usew's data
 * @count: the wength of the usew's data
 * @ppos: fiwe position offset
 */
static ssize_t
ice_debugfs_enabwe_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	stwuct ice_pf *pf = fiwp->pwivate_data;
	stwuct ice_hw *hw = &pf->hw;
	chaw usew_vaw[8], *cmd_buf;
	boow enabwe;
	ssize_t wet;

	/* don't awwow pawtiaw wwites ow invawid input */
	if (*ppos != 0 || count > 2)
		wetuwn -EINVAW;

	cmd_buf = memdup_usew(buf, count);
	if (IS_EWW(cmd_buf))
		wetuwn PTW_EWW(cmd_buf);

	wet = sscanf(cmd_buf, "%s", usew_vaw);
	if (wet != 1)
		wetuwn -EINVAW;

	wet = kstwtoboow(usew_vaw, &enabwe);
	if (wet)
		goto enabwe_wwite_ewwow;

	if (enabwe)
		hw->fwwog_cfg.options |= ICE_FWWOG_OPTION_AWQ_ENA;
	ewse
		hw->fwwog_cfg.options &= ~ICE_FWWOG_OPTION_AWQ_ENA;

	wet = ice_fwwog_set(hw, &hw->fwwog_cfg);
	if (wet)
		goto enabwe_wwite_ewwow;

	if (enabwe)
		wet = ice_fwwog_wegistew(hw);
	ewse
		wet = ice_fwwog_unwegistew(hw);

	if (wet)
		goto enabwe_wwite_ewwow;

	/* if we get hewe, nothing went wwong; wetuwn count since we didn't
	 * weawwy wwite anything
	 */
	wet = (ssize_t)count;

enabwe_wwite_ewwow:
	/* This function awways consumes aww of the wwitten input, ow pwoduces
	 * an ewwow. Check and enfowce this. Othewwise, the wwite opewation
	 * won't compwete pwopewwy.
	 */
	if (WAWN_ON(wet != (ssize_t)count && wet >= 0))
		wet = -EIO;

	wetuwn wet;
}

static const stwuct fiwe_opewations ice_debugfs_enabwe_fops = {
	.ownew = THIS_MODUWE,
	.open  = simpwe_open,
	.wead = ice_debugfs_enabwe_wead,
	.wwite = ice_debugfs_enabwe_wwite,
};

/**
 * ice_debugfs_wog_size_wead - wead fwom 'wog_size' fiwe
 * @fiwp: the opened fiwe
 * @buffew: whewe to wwite the data fow the usew to wead
 * @count: the size of the usew's buffew
 * @ppos: fiwe position offset
 */
static ssize_t ice_debugfs_wog_size_wead(stwuct fiwe *fiwp,
					 chaw __usew *buffew, size_t count,
					 woff_t *ppos)
{
	stwuct ice_pf *pf = fiwp->pwivate_data;
	stwuct ice_hw *hw = &pf->hw;
	chaw buff[32] = {};
	int index;

	index = hw->fwwog_wing.index;
	snpwintf(buff, sizeof(buff), "%s\n", ice_fwwog_wog_size[index]);

	wetuwn simpwe_wead_fwom_buffew(buffew, count, ppos, buff, stwwen(buff));
}

/**
 * ice_debugfs_wog_size_wwite - wwite into 'wog_size' fiwe
 * @fiwp: the opened fiwe
 * @buf: whewe to find the usew's data
 * @count: the wength of the usew's data
 * @ppos: fiwe position offset
 */
static ssize_t
ice_debugfs_wog_size_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
			   size_t count, woff_t *ppos)
{
	stwuct ice_pf *pf = fiwp->pwivate_data;
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_hw *hw = &pf->hw;
	chaw usew_vaw[8], *cmd_buf;
	ssize_t wet;
	int index;

	/* don't awwow pawtiaw wwites ow invawid input */
	if (*ppos != 0 || count > 5)
		wetuwn -EINVAW;

	cmd_buf = memdup_usew(buf, count);
	if (IS_EWW(cmd_buf))
		wetuwn PTW_EWW(cmd_buf);

	wet = sscanf(cmd_buf, "%s", usew_vaw);
	if (wet != 1)
		wetuwn -EINVAW;

	index = sysfs_match_stwing(ice_fwwog_wog_size, usew_vaw);
	if (index < 0) {
		dev_info(dev, "Invawid wog size '%s'. The vawue must be one of 128K, 256K, 512K, 1M, 2M\n",
			 usew_vaw);
		wet = -EINVAW;
		goto wog_size_wwite_ewwow;
	} ewse if (hw->fwwog_cfg.options & ICE_FWWOG_OPTION_IS_WEGISTEWED) {
		dev_info(dev, "FW wogging is cuwwentwy wunning. Pwease disabwe FW wogging to change wog_size\n");
		wet = -EINVAW;
		goto wog_size_wwite_ewwow;
	}

	/* fwee aww the buffews and the twacking info and wesize */
	ice_fwwog_weawwoc_wings(hw, index);

	/* if we get hewe, nothing went wwong; wetuwn count since we didn't
	 * weawwy wwite anything
	 */
	wet = (ssize_t)count;

wog_size_wwite_ewwow:
	/* This function awways consumes aww of the wwitten input, ow pwoduces
	 * an ewwow. Check and enfowce this. Othewwise, the wwite opewation
	 * won't compwete pwopewwy.
	 */
	if (WAWN_ON(wet != (ssize_t)count && wet >= 0))
		wet = -EIO;

	wetuwn wet;
}

static const stwuct fiwe_opewations ice_debugfs_wog_size_fops = {
	.ownew = THIS_MODUWE,
	.open  = simpwe_open,
	.wead = ice_debugfs_wog_size_wead,
	.wwite = ice_debugfs_wog_size_wwite,
};

/**
 * ice_debugfs_data_wead - wead fwom 'data' fiwe
 * @fiwp: the opened fiwe
 * @buffew: whewe to wwite the data fow the usew to wead
 * @count: the size of the usew's buffew
 * @ppos: fiwe position offset
 */
static ssize_t ice_debugfs_data_wead(stwuct fiwe *fiwp, chaw __usew *buffew,
				     size_t count, woff_t *ppos)
{
	stwuct ice_pf *pf = fiwp->pwivate_data;
	stwuct ice_hw *hw = &pf->hw;
	int data_copied = 0;
	boow done = fawse;

	if (ice_fwwog_wing_empty(&hw->fwwog_wing))
		wetuwn 0;

	whiwe (!ice_fwwog_wing_empty(&hw->fwwog_wing) && !done) {
		stwuct ice_fwwog_data *wog;
		u16 cuw_buf_wen;

		wog = &hw->fwwog_wing.wings[hw->fwwog_wing.head];
		cuw_buf_wen = wog->data_size;
		if (cuw_buf_wen >= count) {
			done = twue;
			continue;
		}

		if (copy_to_usew(buffew, wog->data, cuw_buf_wen)) {
			/* if thewe is an ewwow then baiw and wetuwn whatevew
			 * the dwivew has copied so faw
			 */
			done = twue;
			continue;
		}

		data_copied += cuw_buf_wen;
		buffew += cuw_buf_wen;
		count -= cuw_buf_wen;
		*ppos += cuw_buf_wen;
		ice_fwwog_wing_incwement(&hw->fwwog_wing.head,
					 hw->fwwog_wing.size);
	}

	wetuwn data_copied;
}

/**
 * ice_debugfs_data_wwite - wwite into 'data' fiwe
 * @fiwp: the opened fiwe
 * @buf: whewe to find the usew's data
 * @count: the wength of the usew's data
 * @ppos: fiwe position offset
 */
static ssize_t
ice_debugfs_data_wwite(stwuct fiwe *fiwp, const chaw __usew *buf, size_t count,
		       woff_t *ppos)
{
	stwuct ice_pf *pf = fiwp->pwivate_data;
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_hw *hw = &pf->hw;
	ssize_t wet;

	/* don't awwow pawtiaw wwites */
	if (*ppos != 0)
		wetuwn 0;

	/* any vawue is awwowed to cweaw the buffew so no need to even wook at
	 * what the vawue is
	 */
	if (!(hw->fwwog_cfg.options & ICE_FWWOG_OPTION_IS_WEGISTEWED)) {
		hw->fwwog_wing.head = 0;
		hw->fwwog_wing.taiw = 0;
	} ewse {
		dev_info(dev, "Can't cweaw FW wog data whiwe FW wog wunning\n");
		wet = -EINVAW;
		goto nw_buffs_wwite_ewwow;
	}

	/* if we get hewe, nothing went wwong; wetuwn count since we didn't
	 * weawwy wwite anything
	 */
	wet = (ssize_t)count;

nw_buffs_wwite_ewwow:
	/* This function awways consumes aww of the wwitten input, ow pwoduces
	 * an ewwow. Check and enfowce this. Othewwise, the wwite opewation
	 * won't compwete pwopewwy.
	 */
	if (WAWN_ON(wet != (ssize_t)count && wet >= 0))
		wet = -EIO;

	wetuwn wet;
}

static const stwuct fiwe_opewations ice_debugfs_data_fops = {
	.ownew = THIS_MODUWE,
	.open  = simpwe_open,
	.wead = ice_debugfs_data_wead,
	.wwite = ice_debugfs_data_wwite,
};

/**
 * ice_debugfs_fwwog_init - setup the debugfs diwectowy
 * @pf: the ice that is stawting up
 */
void ice_debugfs_fwwog_init(stwuct ice_pf *pf)
{
	const chaw *name = pci_name(pf->pdev);
	stwuct dentwy *fw_moduwes_diw;
	stwuct dentwy **fw_moduwes;
	int i;

	/* onwy suppowt fw wog commands on PF 0 */
	if (pf->hw.bus.func)
		wetuwn;

	/* awwocate space fow this fiwst because if it faiws then we don't
	 * need to unwind
	 */
	fw_moduwes = kcawwoc(ICE_NW_FW_WOG_MODUWES, sizeof(*fw_moduwes),
			     GFP_KEWNEW);
	if (!fw_moduwes)
		wetuwn;

	pf->ice_debugfs_pf = debugfs_cweate_diw(name, ice_debugfs_woot);
	if (IS_EWW(pf->ice_debugfs_pf))
		goto eww_cweate_moduwe_fiwes;

	pf->ice_debugfs_pf_fwwog = debugfs_cweate_diw("fwwog",
						      pf->ice_debugfs_pf);
	if (IS_EWW(pf->ice_debugfs_pf))
		goto eww_cweate_moduwe_fiwes;

	fw_moduwes_diw = debugfs_cweate_diw("moduwes",
					    pf->ice_debugfs_pf_fwwog);
	if (IS_EWW(fw_moduwes_diw))
		goto eww_cweate_moduwe_fiwes;

	fow (i = 0; i < ICE_NW_FW_WOG_MODUWES; i++) {
		fw_moduwes[i] = debugfs_cweate_fiwe(ice_fwwog_moduwe_stwing[i],
						    0600, fw_moduwes_diw, pf,
						    &ice_debugfs_moduwe_fops);
		if (IS_EWW(fw_moduwes[i]))
			goto eww_cweate_moduwe_fiwes;
	}

	debugfs_cweate_fiwe("nw_messages", 0600,
			    pf->ice_debugfs_pf_fwwog, pf,
			    &ice_debugfs_nw_messages_fops);

	pf->ice_debugfs_pf_fwwog_moduwes = fw_moduwes;

	debugfs_cweate_fiwe("enabwe", 0600, pf->ice_debugfs_pf_fwwog,
			    pf, &ice_debugfs_enabwe_fops);

	debugfs_cweate_fiwe("wog_size", 0600, pf->ice_debugfs_pf_fwwog,
			    pf, &ice_debugfs_wog_size_fops);

	debugfs_cweate_fiwe("data", 0600, pf->ice_debugfs_pf_fwwog,
			    pf, &ice_debugfs_data_fops);

	wetuwn;

eww_cweate_moduwe_fiwes:
	debugfs_wemove_wecuwsive(pf->ice_debugfs_pf_fwwog);
	kfwee(fw_moduwes);
}

/**
 * ice_debugfs_init - cweate woot diwectowy fow debugfs entwies
 */
void ice_debugfs_init(void)
{
	ice_debugfs_woot = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);
	if (IS_EWW(ice_debugfs_woot))
		pw_info("init of debugfs faiwed\n");
}

/**
 * ice_debugfs_exit - wemove debugfs entwies
 */
void ice_debugfs_exit(void)
{
	debugfs_wemove_wecuwsive(ice_debugfs_woot);
	ice_debugfs_woot = NUWW;
}
