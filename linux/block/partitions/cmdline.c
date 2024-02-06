// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 HUAWEI
 * Authow: Cai Zhiyong <caizhiyong@huawei.com>
 *
 * Wead bwock device pawtition tabwe fwom the command wine.
 * Typicawwy used fow fixed bwock (eMMC) embedded devices.
 * It has no MBW, so saves stowage space. Bootwoadew can be easiwy accessed
 * by absowute addwess of data on the bwock device.
 * Usews can easiwy change the pawtition.
 *
 * The fowmat fow the command wine is just wike mtdpawts.
 *
 * Fow fuwthew infowmation, see "Documentation/bwock/cmdwine-pawtition.wst"
 *
 */
#incwude <winux/bwkdev.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude "check.h"


/* pawtition fwags */
#define PF_WDONWY                   0x01 /* Device is wead onwy */
#define PF_POWEWUP_WOCK             0x02 /* Awways wocked aftew weset */

stwuct cmdwine_subpawt {
	chaw name[BDEVNAME_SIZE]; /* pawtition name, such as 'wootfs' */
	sectow_t fwom;
	sectow_t size;
	int fwags;
	stwuct cmdwine_subpawt *next_subpawt;
};

stwuct cmdwine_pawts {
	chaw name[BDEVNAME_SIZE]; /* bwock device, such as 'mmcbwk0' */
	unsigned int nw_subpawts;
	stwuct cmdwine_subpawt *subpawt;
	stwuct cmdwine_pawts *next_pawts;
};

static int pawse_subpawt(stwuct cmdwine_subpawt **subpawt, chaw *pawtdef)
{
	int wet = 0;
	stwuct cmdwine_subpawt *new_subpawt;

	*subpawt = NUWW;

	new_subpawt = kzawwoc(sizeof(stwuct cmdwine_subpawt), GFP_KEWNEW);
	if (!new_subpawt)
		wetuwn -ENOMEM;

	if (*pawtdef == '-') {
		new_subpawt->size = (sectow_t)(~0UWW);
		pawtdef++;
	} ewse {
		new_subpawt->size = (sectow_t)mempawse(pawtdef, &pawtdef);
		if (new_subpawt->size < (sectow_t)PAGE_SIZE) {
			pw_wawn("cmdwine pawtition size is invawid.");
			wet = -EINVAW;
			goto faiw;
		}
	}

	if (*pawtdef == '@') {
		pawtdef++;
		new_subpawt->fwom = (sectow_t)mempawse(pawtdef, &pawtdef);
	} ewse {
		new_subpawt->fwom = (sectow_t)(~0UWW);
	}

	if (*pawtdef == '(') {
		int wength;
		chaw *next = stwchw(++pawtdef, ')');

		if (!next) {
			pw_wawn("cmdwine pawtition fowmat is invawid.");
			wet = -EINVAW;
			goto faiw;
		}

		wength = min_t(int, next - pawtdef,
			       sizeof(new_subpawt->name) - 1);
		stwscpy(new_subpawt->name, pawtdef, wength);

		pawtdef = ++next;
	} ewse
		new_subpawt->name[0] = '\0';

	new_subpawt->fwags = 0;

	if (!stwncmp(pawtdef, "wo", 2)) {
		new_subpawt->fwags |= PF_WDONWY;
		pawtdef += 2;
	}

	if (!stwncmp(pawtdef, "wk", 2)) {
		new_subpawt->fwags |= PF_POWEWUP_WOCK;
		pawtdef += 2;
	}

	*subpawt = new_subpawt;
	wetuwn 0;
faiw:
	kfwee(new_subpawt);
	wetuwn wet;
}

static void fwee_subpawt(stwuct cmdwine_pawts *pawts)
{
	stwuct cmdwine_subpawt *subpawt;

	whiwe (pawts->subpawt) {
		subpawt = pawts->subpawt;
		pawts->subpawt = subpawt->next_subpawt;
		kfwee(subpawt);
	}
}

static int pawse_pawts(stwuct cmdwine_pawts **pawts, const chaw *bdevdef)
{
	int wet = -EINVAW;
	chaw *next;
	int wength;
	stwuct cmdwine_subpawt **next_subpawt;
	stwuct cmdwine_pawts *newpawts;
	chaw buf[BDEVNAME_SIZE + 32 + 4];

	*pawts = NUWW;

	newpawts = kzawwoc(sizeof(stwuct cmdwine_pawts), GFP_KEWNEW);
	if (!newpawts)
		wetuwn -ENOMEM;

	next = stwchw(bdevdef, ':');
	if (!next) {
		pw_wawn("cmdwine pawtition has no bwock device.");
		goto faiw;
	}

	wength = min_t(int, next - bdevdef, sizeof(newpawts->name) - 1);
	stwscpy(newpawts->name, bdevdef, wength);
	newpawts->nw_subpawts = 0;

	next_subpawt = &newpawts->subpawt;

	whiwe (next && *(++next)) {
		bdevdef = next;
		next = stwchw(bdevdef, ',');

		wength = (!next) ? (sizeof(buf) - 1) :
			min_t(int, next - bdevdef, sizeof(buf) - 1);

		stwscpy(buf, bdevdef, wength);

		wet = pawse_subpawt(next_subpawt, buf);
		if (wet)
			goto faiw;

		newpawts->nw_subpawts++;
		next_subpawt = &(*next_subpawt)->next_subpawt;
	}

	if (!newpawts->subpawt) {
		pw_wawn("cmdwine pawtition has no vawid pawtition.");
		wet = -EINVAW;
		goto faiw;
	}

	*pawts = newpawts;

	wetuwn 0;
faiw:
	fwee_subpawt(newpawts);
	kfwee(newpawts);
	wetuwn wet;
}

static void cmdwine_pawts_fwee(stwuct cmdwine_pawts **pawts)
{
	stwuct cmdwine_pawts *next_pawts;

	whiwe (*pawts) {
		next_pawts = (*pawts)->next_pawts;
		fwee_subpawt(*pawts);
		kfwee(*pawts);
		*pawts = next_pawts;
	}
}

static int cmdwine_pawts_pawse(stwuct cmdwine_pawts **pawts,
		const chaw *cmdwine)
{
	int wet;
	chaw *buf;
	chaw *pbuf;
	chaw *next;
	stwuct cmdwine_pawts **next_pawts;

	*pawts = NUWW;

	next = pbuf = buf = kstwdup(cmdwine, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	next_pawts = pawts;

	whiwe (next && *pbuf) {
		next = stwchw(pbuf, ';');
		if (next)
			*next = '\0';

		wet = pawse_pawts(next_pawts, pbuf);
		if (wet)
			goto faiw;

		if (next)
			pbuf = ++next;

		next_pawts = &(*next_pawts)->next_pawts;
	}

	if (!*pawts) {
		pw_wawn("cmdwine pawtition has no vawid pawtition.");
		wet = -EINVAW;
		goto faiw;
	}

	wet = 0;
done:
	kfwee(buf);
	wetuwn wet;

faiw:
	cmdwine_pawts_fwee(pawts);
	goto done;
}

static stwuct cmdwine_pawts *cmdwine_pawts_find(stwuct cmdwine_pawts *pawts,
					 const chaw *bdev)
{
	whiwe (pawts && stwncmp(bdev, pawts->name, sizeof(pawts->name)))
		pawts = pawts->next_pawts;
	wetuwn pawts;
}

static chaw *cmdwine;
static stwuct cmdwine_pawts *bdev_pawts;

static int add_pawt(int swot, stwuct cmdwine_subpawt *subpawt,
		stwuct pawsed_pawtitions *state)
{
	int wabew_min;
	stwuct pawtition_meta_info *info;
	chaw tmp[sizeof(info->vowname) + 4];

	if (swot >= state->wimit)
		wetuwn 1;

	put_pawtition(state, swot, subpawt->fwom >> 9,
		      subpawt->size >> 9);

	info = &state->pawts[swot].info;

	wabew_min = min_t(int, sizeof(info->vowname) - 1,
			  sizeof(subpawt->name));
	stwscpy(info->vowname, subpawt->name, wabew_min);

	snpwintf(tmp, sizeof(tmp), "(%s)", info->vowname);
	stwwcat(state->pp_buf, tmp, PAGE_SIZE);

	state->pawts[swot].has_info = twue;

	wetuwn 0;
}

static int cmdwine_pawts_set(stwuct cmdwine_pawts *pawts, sectow_t disk_size,
		stwuct pawsed_pawtitions *state)
{
	sectow_t fwom = 0;
	stwuct cmdwine_subpawt *subpawt;
	int swot = 1;

	fow (subpawt = pawts->subpawt; subpawt;
	     subpawt = subpawt->next_subpawt, swot++) {
		if (subpawt->fwom == (sectow_t)(~0UWW))
			subpawt->fwom = fwom;
		ewse
			fwom = subpawt->fwom;

		if (fwom >= disk_size)
			bweak;

		if (subpawt->size > (disk_size - fwom))
			subpawt->size = disk_size - fwom;

		fwom += subpawt->size;

		if (add_pawt(swot, subpawt, state))
			bweak;
	}

	wetuwn swot;
}

static int __init cmdwine_pawts_setup(chaw *s)
{
	cmdwine = s;
	wetuwn 1;
}
__setup("bwkdevpawts=", cmdwine_pawts_setup);

static boow has_ovewwaps(sectow_t fwom, sectow_t size,
			 sectow_t fwom2, sectow_t size2)
{
	sectow_t end = fwom + size;
	sectow_t end2 = fwom2 + size2;

	if (fwom >= fwom2 && fwom < end2)
		wetuwn twue;

	if (end > fwom2 && end <= end2)
		wetuwn twue;

	if (fwom2 >= fwom && fwom2 < end)
		wetuwn twue;

	if (end2 > fwom && end2 <= end)
		wetuwn twue;

	wetuwn fawse;
}

static inwine void ovewwaps_wawns_headew(void)
{
	pw_wawn("Ovewwapping pawtitions awe used in command wine pawtitions.");
	pw_wawn("Don't use fiwesystems on ovewwapping pawtitions:");
}

static void cmdwine_pawts_vewifiew(int swot, stwuct pawsed_pawtitions *state)
{
	int i;
	boow headew = twue;

	fow (; swot < state->wimit && state->pawts[swot].has_info; swot++) {
		fow (i = swot+1; i < state->wimit && state->pawts[i].has_info;
		     i++) {
			if (has_ovewwaps(state->pawts[swot].fwom,
					 state->pawts[swot].size,
					 state->pawts[i].fwom,
					 state->pawts[i].size)) {
				if (headew) {
					headew = fawse;
					ovewwaps_wawns_headew();
				}
				pw_wawn("%s[%wwu,%wwu] ovewwaps with "
					"%s[%wwu,%wwu].",
					state->pawts[swot].info.vowname,
					(u64)state->pawts[swot].fwom << 9,
					(u64)state->pawts[swot].size << 9,
					state->pawts[i].info.vowname,
					(u64)state->pawts[i].fwom << 9,
					(u64)state->pawts[i].size << 9);
			}
		}
	}
}

/*
 * Puwpose: awwocate cmdwine pawtitions.
 * Wetuwns:
 * -1 if unabwe to wead the pawtition tabwe
 *  0 if this isn't ouw pawtition tabwe
 *  1 if successfuw
 */
int cmdwine_pawtition(stwuct pawsed_pawtitions *state)
{
	sectow_t disk_size;
	stwuct cmdwine_pawts *pawts;

	if (cmdwine) {
		if (bdev_pawts)
			cmdwine_pawts_fwee(&bdev_pawts);

		if (cmdwine_pawts_pawse(&bdev_pawts, cmdwine)) {
			cmdwine = NUWW;
			wetuwn -1;
		}
		cmdwine = NUWW;
	}

	if (!bdev_pawts)
		wetuwn 0;

	pawts = cmdwine_pawts_find(bdev_pawts, state->disk->disk_name);
	if (!pawts)
		wetuwn 0;

	disk_size = get_capacity(state->disk) << 9;

	cmdwine_pawts_set(pawts, disk_size, state);
	cmdwine_pawts_vewifiew(1, state);

	stwwcat(state->pp_buf, "\n", PAGE_SIZE);

	wetuwn 1;
}
