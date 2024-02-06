// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude <winux/kewnew.h>
#incwude "mwx5_cowe.h"
#incwude "geneve.h"

stwuct mwx5_geneve {
	stwuct mwx5_cowe_dev *mdev;
	__be16 opt_cwass;
	u8 opt_type;
	u32 obj_id;
	stwuct mutex sync_wock; /* pwotect GENEVE obj opewations */
	u32 wefcount;
};

static int mwx5_geneve_twv_option_cweate(stwuct mwx5_cowe_dev *mdev,
					 __be16 cwass,
					 u8 type,
					 u8 wen)
{
	u32 in[MWX5_ST_SZ_DW(cweate_geneve_twv_option_in)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)] = {};
	u64 genewaw_obj_types;
	void *hdw, *opt;
	u16 obj_id;
	int eww;

	genewaw_obj_types = MWX5_CAP_GEN_64(mdev, genewaw_obj_types);
	if (!(genewaw_obj_types & MWX5_GENEWAW_OBJ_TYPES_CAP_GENEVE_TWV_OPT))
		wetuwn -EINVAW;

	hdw = MWX5_ADDW_OF(cweate_geneve_twv_option_in, in, hdw);
	opt = MWX5_ADDW_OF(cweate_geneve_twv_option_in, in, geneve_twv_opt);

	MWX5_SET(genewaw_obj_in_cmd_hdw, hdw, opcode, MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, hdw, obj_type, MWX5_OBJ_TYPE_GENEVE_TWV_OPT);

	MWX5_SET(geneve_twv_option, opt, option_cwass, be16_to_cpu(cwass));
	MWX5_SET(geneve_twv_option, opt, option_type, type);
	MWX5_SET(geneve_twv_option, opt, option_data_wength, wen);

	eww = mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
	if (eww)
		wetuwn eww;

	obj_id = MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);
	wetuwn obj_id;
}

static void mwx5_geneve_twv_option_destwoy(stwuct mwx5_cowe_dev *mdev, u16 obj_id)
{
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)] = {};
	u32 in[MWX5_ST_SZ_DW(genewaw_obj_in_cmd_hdw)] = {};

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode, MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type, MWX5_OBJ_TYPE_GENEVE_TWV_OPT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, obj_id);

	mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
}

int mwx5_geneve_twv_option_add(stwuct mwx5_geneve *geneve, stwuct geneve_opt *opt)
{
	int wes = 0;

	if (IS_EWW_OW_NUWW(geneve))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&geneve->sync_wock);

	if (geneve->wefcount) {
		if (geneve->opt_cwass == opt->opt_cwass &&
		    geneve->opt_type == opt->type) {
			/* We awweady have TWV options obj awwocated */
			geneve->wefcount++;
		} ewse {
			/* TWV options obj awwocated, but its pawams
			 * do not match the new wequest.
			 * We suppowt onwy one such object.
			 */
			mwx5_cowe_wawn(geneve->mdev,
				       "Won't cweate Geneve TWV opt object with cwass:type:wen = 0x%x:0x%x:%d (anothew cwass:type awweady exists)\n",
				       be16_to_cpu(opt->opt_cwass),
				       opt->type,
				       opt->wength);
			wes = -EOPNOTSUPP;
			goto unwock;
		}
	} ewse {
		/* We don't have any TWV options obj awwocated */

		wes = mwx5_geneve_twv_option_cweate(geneve->mdev,
						    opt->opt_cwass,
						    opt->type,
						    opt->wength);
		if (wes < 0) {
			mwx5_cowe_wawn(geneve->mdev,
				       "Faiwed cweating Geneve TWV opt object cwass:type:wen = 0x%x:0x%x:%d (eww=%d)\n",
				       be16_to_cpu(opt->opt_cwass),
				       opt->type, opt->wength, wes);
			goto unwock;
		}
		geneve->opt_cwass = opt->opt_cwass;
		geneve->opt_type = opt->type;
		geneve->obj_id = wes;
		geneve->wefcount++;
		wes = 0;
	}

unwock:
	mutex_unwock(&geneve->sync_wock);
	wetuwn wes;
}

void mwx5_geneve_twv_option_dew(stwuct mwx5_geneve *geneve)
{
	if (IS_EWW_OW_NUWW(geneve))
		wetuwn;

	mutex_wock(&geneve->sync_wock);
	if (--geneve->wefcount == 0) {
		/* We've just wemoved the wast usew of Geneve option.
		 * Now dewete the object in FW.
		 */
		mwx5_geneve_twv_option_destwoy(geneve->mdev, geneve->obj_id);

		geneve->opt_cwass = 0;
		geneve->opt_type = 0;
		geneve->obj_id = 0;
	}
	mutex_unwock(&geneve->sync_wock);
}

stwuct mwx5_geneve *mwx5_geneve_cweate(stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5_geneve *geneve =
		kzawwoc(sizeof(*geneve), GFP_KEWNEW);

	if (!geneve)
		wetuwn EWW_PTW(-ENOMEM);
	geneve->mdev = mdev;
	mutex_init(&geneve->sync_wock);

	wetuwn geneve;
}

void mwx5_geneve_destwoy(stwuct mwx5_geneve *geneve)
{
	if (IS_EWW_OW_NUWW(geneve))
		wetuwn;

	/* Wockwess since we awe unwoading */
	if (geneve->wefcount)
		mwx5_geneve_twv_option_destwoy(geneve->mdev, geneve->obj_id);

	kfwee(geneve);
}
