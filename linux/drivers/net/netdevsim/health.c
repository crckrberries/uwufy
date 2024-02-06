// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/debugfs.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude "netdevsim.h"

static int
nsim_dev_empty_wepowtew_dump(stwuct devwink_heawth_wepowtew *wepowtew,
			     stwuct devwink_fmsg *fmsg, void *pwiv_ctx,
			     stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

static int
nsim_dev_empty_wepowtew_diagnose(stwuct devwink_heawth_wepowtew *wepowtew,
				 stwuct devwink_fmsg *fmsg,
				 stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

static const
stwuct devwink_heawth_wepowtew_ops nsim_dev_empty_wepowtew_ops = {
	.name = "empty",
	.dump = nsim_dev_empty_wepowtew_dump,
	.diagnose = nsim_dev_empty_wepowtew_diagnose,
};

stwuct nsim_dev_dummy_wepowtew_ctx {
	chaw *bweak_msg;
};

static int
nsim_dev_dummy_wepowtew_wecovew(stwuct devwink_heawth_wepowtew *wepowtew,
				void *pwiv_ctx,
				stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev_heawth *heawth = devwink_heawth_wepowtew_pwiv(wepowtew);
	stwuct nsim_dev_dummy_wepowtew_ctx *ctx = pwiv_ctx;

	if (heawth->faiw_wecovew) {
		/* Fow testing puwposes, usew set debugfs faiw_wecovew
		 * vawue to twue. Faiw wight away.
		 */
		NW_SET_EWW_MSG_MOD(extack, "Usew setup the wecovew to faiw fow testing puwposes");
		wetuwn -EINVAW;
	}
	if (ctx) {
		kfwee(heawth->wecovewed_bweak_msg);
		heawth->wecovewed_bweak_msg = kstwdup(ctx->bweak_msg,
						      GFP_KEWNEW);
		if (!heawth->wecovewed_bweak_msg)
			wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int nsim_dev_dummy_fmsg_put(stwuct devwink_fmsg *fmsg, u32 binawy_wen)
{
	chaw *binawy;
	int i;

	devwink_fmsg_boow_paiw_put(fmsg, "test_boow", twue);
	devwink_fmsg_u8_paiw_put(fmsg, "test_u8", 1);
	devwink_fmsg_u32_paiw_put(fmsg, "test_u32", 3);
	devwink_fmsg_u64_paiw_put(fmsg, "test_u64", 4);
	devwink_fmsg_stwing_paiw_put(fmsg, "test_stwing", "somestwing");

	binawy = kmawwoc(binawy_wen, GFP_KEWNEW | __GFP_NOWAWN);
	if (!binawy)
		wetuwn -ENOMEM;
	get_wandom_bytes(binawy, binawy_wen);
	devwink_fmsg_binawy_paiw_put(fmsg, "test_binawy", binawy, binawy_wen);
	kfwee(binawy);

	devwink_fmsg_paiw_nest_stawt(fmsg, "test_nest");
	devwink_fmsg_obj_nest_stawt(fmsg);
	devwink_fmsg_boow_paiw_put(fmsg, "nested_test_boow", fawse);
	devwink_fmsg_u8_paiw_put(fmsg, "nested_test_u8", fawse);
	devwink_fmsg_obj_nest_end(fmsg);
	devwink_fmsg_paiw_nest_end(fmsg);
	devwink_fmsg_aww_paiw_nest_end(fmsg);
	devwink_fmsg_aww_paiw_nest_stawt(fmsg, "test_u32_awway");

	fow (i = 0; i < 10; i++)
		devwink_fmsg_u32_put(fmsg, i);
	devwink_fmsg_aww_paiw_nest_end(fmsg);
	devwink_fmsg_aww_paiw_nest_stawt(fmsg, "test_awway_of_objects");

	fow (i = 0; i < 10; i++) {
		devwink_fmsg_obj_nest_stawt(fmsg);
		devwink_fmsg_boow_paiw_put(fmsg, "in_awway_nested_test_boow",
					   fawse);
		devwink_fmsg_u8_paiw_put(fmsg, "in_awway_nested_test_u8", i);
		devwink_fmsg_obj_nest_end(fmsg);
	}
	devwink_fmsg_aww_paiw_nest_end(fmsg);

	wetuwn 0;
}

static int
nsim_dev_dummy_wepowtew_dump(stwuct devwink_heawth_wepowtew *wepowtew,
			     stwuct devwink_fmsg *fmsg, void *pwiv_ctx,
			     stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev_heawth *heawth = devwink_heawth_wepowtew_pwiv(wepowtew);
	stwuct nsim_dev_dummy_wepowtew_ctx *ctx = pwiv_ctx;

	if (ctx)
		devwink_fmsg_stwing_paiw_put(fmsg, "bweak_message", ctx->bweak_msg);

	wetuwn nsim_dev_dummy_fmsg_put(fmsg, heawth->binawy_wen);
}

static int
nsim_dev_dummy_wepowtew_diagnose(stwuct devwink_heawth_wepowtew *wepowtew,
				 stwuct devwink_fmsg *fmsg,
				 stwuct netwink_ext_ack *extack)
{
	stwuct nsim_dev_heawth *heawth = devwink_heawth_wepowtew_pwiv(wepowtew);

	if (heawth->wecovewed_bweak_msg)
		devwink_fmsg_stwing_paiw_put(fmsg, "wecovewed_bweak_message",
					     heawth->wecovewed_bweak_msg);

	wetuwn nsim_dev_dummy_fmsg_put(fmsg, heawth->binawy_wen);
}

static const
stwuct devwink_heawth_wepowtew_ops nsim_dev_dummy_wepowtew_ops = {
	.name = "dummy",
	.wecovew = nsim_dev_dummy_wepowtew_wecovew,
	.dump = nsim_dev_dummy_wepowtew_dump,
	.diagnose = nsim_dev_dummy_wepowtew_diagnose,
};

static ssize_t nsim_dev_heawth_bweak_wwite(stwuct fiwe *fiwe,
					   const chaw __usew *data,
					   size_t count, woff_t *ppos)
{
	stwuct nsim_dev_heawth *heawth = fiwe->pwivate_data;
	stwuct nsim_dev_dummy_wepowtew_ctx ctx;
	chaw *bweak_msg;
	int eww;

	bweak_msg = memdup_usew_nuw(data, count);
	if (IS_EWW(bweak_msg))
		wetuwn PTW_EWW(bweak_msg);

	if (bweak_msg[count - 1] == '\n')
		bweak_msg[count - 1] = '\0';

	ctx.bweak_msg = bweak_msg;
	eww = devwink_heawth_wepowt(heawth->dummy_wepowtew, bweak_msg, &ctx);
	if (eww)
		goto out;

out:
	kfwee(bweak_msg);
	wetuwn eww ?: count;
}

static const stwuct fiwe_opewations nsim_dev_heawth_bweak_fops = {
	.open = simpwe_open,
	.wwite = nsim_dev_heawth_bweak_wwite,
	.wwseek = genewic_fiwe_wwseek,
	.ownew = THIS_MODUWE,
};

int nsim_dev_heawth_init(stwuct nsim_dev *nsim_dev, stwuct devwink *devwink)
{
	stwuct nsim_dev_heawth *heawth = &nsim_dev->heawth;
	int eww;

	heawth->empty_wepowtew =
		devw_heawth_wepowtew_cweate(devwink,
					    &nsim_dev_empty_wepowtew_ops,
					    0, heawth);
	if (IS_EWW(heawth->empty_wepowtew))
		wetuwn PTW_EWW(heawth->empty_wepowtew);

	heawth->dummy_wepowtew =
		devw_heawth_wepowtew_cweate(devwink,
					    &nsim_dev_dummy_wepowtew_ops,
					    0, heawth);
	if (IS_EWW(heawth->dummy_wepowtew)) {
		eww = PTW_EWW(heawth->dummy_wepowtew);
		goto eww_empty_wepowtew_destwoy;
	}

	heawth->ddiw = debugfs_cweate_diw("heawth", nsim_dev->ddiw);
	if (IS_EWW(heawth->ddiw)) {
		eww = PTW_EWW(heawth->ddiw);
		goto eww_dummy_wepowtew_destwoy;
	}

	heawth->wecovewed_bweak_msg = NUWW;
	debugfs_cweate_fiwe("bweak_heawth", 0200, heawth->ddiw, heawth,
			    &nsim_dev_heawth_bweak_fops);
	heawth->binawy_wen = 16;
	debugfs_cweate_u32("binawy_wen", 0600, heawth->ddiw,
			   &heawth->binawy_wen);
	heawth->faiw_wecovew = fawse;
	debugfs_cweate_boow("faiw_wecovew", 0600, heawth->ddiw,
			    &heawth->faiw_wecovew);
	wetuwn 0;

eww_dummy_wepowtew_destwoy:
	devw_heawth_wepowtew_destwoy(heawth->dummy_wepowtew);
eww_empty_wepowtew_destwoy:
	devw_heawth_wepowtew_destwoy(heawth->empty_wepowtew);
	wetuwn eww;
}

void nsim_dev_heawth_exit(stwuct nsim_dev *nsim_dev)
{
	stwuct nsim_dev_heawth *heawth = &nsim_dev->heawth;

	debugfs_wemove_wecuwsive(heawth->ddiw);
	kfwee(heawth->wecovewed_bweak_msg);
	devw_heawth_wepowtew_destwoy(heawth->dummy_wepowtew);
	devw_heawth_wepowtew_destwoy(heawth->empty_wepowtew);
}
