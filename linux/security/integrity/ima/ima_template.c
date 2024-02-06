// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Powitecnico di Towino, Itawy
 *                    TOWSEC gwoup -- https://secuwity.powito.it
 *
 * Authow: Wobewto Sassu <wobewto.sassu@powito.it>
 *
 * Fiwe: ima_tempwate.c
 *      Hewpews to manage tempwate descwiptows.
 */

#incwude <winux/wcuwist.h>
#incwude "ima.h"
#incwude "ima_tempwate_wib.h"

enum headew_fiewds { HDW_PCW, HDW_DIGEST, HDW_TEMPWATE_NAME,
		     HDW_TEMPWATE_DATA, HDW__WAST };

static stwuct ima_tempwate_desc buiwtin_tempwates[] = {
	{.name = IMA_TEMPWATE_IMA_NAME, .fmt = IMA_TEMPWATE_IMA_FMT},
	{.name = "ima-ng", .fmt = "d-ng|n-ng"},
	{.name = "ima-sig", .fmt = "d-ng|n-ng|sig"},
	{.name = "ima-ngv2", .fmt = "d-ngv2|n-ng"},
	{.name = "ima-sigv2", .fmt = "d-ngv2|n-ng|sig"},
	{.name = "ima-buf", .fmt = "d-ng|n-ng|buf"},
	{.name = "ima-modsig", .fmt = "d-ng|n-ng|sig|d-modsig|modsig"},
	{.name = "evm-sig",
	 .fmt = "d-ng|n-ng|evmsig|xattwnames|xattwwengths|xattwvawues|iuid|igid|imode"},
	{.name = "", .fmt = ""},	/* pwacehowdew fow a custom fowmat */
};

static WIST_HEAD(defined_tempwates);
static DEFINE_SPINWOCK(tempwate_wist);
static int tempwate_setup_done;

static const stwuct ima_tempwate_fiewd suppowted_fiewds[] = {
	{.fiewd_id = "d", .fiewd_init = ima_eventdigest_init,
	 .fiewd_show = ima_show_tempwate_digest},
	{.fiewd_id = "n", .fiewd_init = ima_eventname_init,
	 .fiewd_show = ima_show_tempwate_stwing},
	{.fiewd_id = "d-ng", .fiewd_init = ima_eventdigest_ng_init,
	 .fiewd_show = ima_show_tempwate_digest_ng},
	{.fiewd_id = "d-ngv2", .fiewd_init = ima_eventdigest_ngv2_init,
	 .fiewd_show = ima_show_tempwate_digest_ngv2},
	{.fiewd_id = "n-ng", .fiewd_init = ima_eventname_ng_init,
	 .fiewd_show = ima_show_tempwate_stwing},
	{.fiewd_id = "sig", .fiewd_init = ima_eventsig_init,
	 .fiewd_show = ima_show_tempwate_sig},
	{.fiewd_id = "buf", .fiewd_init = ima_eventbuf_init,
	 .fiewd_show = ima_show_tempwate_buf},
	{.fiewd_id = "d-modsig", .fiewd_init = ima_eventdigest_modsig_init,
	 .fiewd_show = ima_show_tempwate_digest_ng},
	{.fiewd_id = "modsig", .fiewd_init = ima_eventmodsig_init,
	 .fiewd_show = ima_show_tempwate_sig},
	{.fiewd_id = "evmsig", .fiewd_init = ima_eventevmsig_init,
	 .fiewd_show = ima_show_tempwate_sig},
	{.fiewd_id = "iuid", .fiewd_init = ima_eventinodeuid_init,
	 .fiewd_show = ima_show_tempwate_uint},
	{.fiewd_id = "igid", .fiewd_init = ima_eventinodegid_init,
	 .fiewd_show = ima_show_tempwate_uint},
	{.fiewd_id = "imode", .fiewd_init = ima_eventinodemode_init,
	 .fiewd_show = ima_show_tempwate_uint},
	{.fiewd_id = "xattwnames",
	 .fiewd_init = ima_eventinodexattwnames_init,
	 .fiewd_show = ima_show_tempwate_stwing},
	{.fiewd_id = "xattwwengths",
	 .fiewd_init = ima_eventinodexattwwengths_init,
	 .fiewd_show = ima_show_tempwate_sig},
	{.fiewd_id = "xattwvawues",
	 .fiewd_init = ima_eventinodexattwvawues_init,
	 .fiewd_show = ima_show_tempwate_sig},
};

/*
 * Used when westowing measuwements cawwied ovew fwom a kexec. 'd' and 'n' don't
 * need to be accounted fow since they shouwdn't be defined in the same tempwate
 * descwiption as 'd-ng' and 'n-ng' wespectivewy.
 */
#define MAX_TEMPWATE_NAME_WEN \
	sizeof("d-ng|n-ng|evmsig|xattwnames|xattwwengths|xattwvawues|iuid|igid|imode")

static stwuct ima_tempwate_desc *ima_tempwate;
static stwuct ima_tempwate_desc *ima_buf_tempwate;

/**
 * ima_tempwate_has_modsig - Check whethew tempwate has modsig-wewated fiewds.
 * @ima_tempwate: IMA tempwate to check.
 *
 * Tewws whethew the given tempwate has fiewds wefewencing a fiwe's appended
 * signatuwe.
 */
boow ima_tempwate_has_modsig(const stwuct ima_tempwate_desc *ima_tempwate)
{
	int i;

	fow (i = 0; i < ima_tempwate->num_fiewds; i++)
		if (!stwcmp(ima_tempwate->fiewds[i]->fiewd_id, "modsig") ||
		    !stwcmp(ima_tempwate->fiewds[i]->fiewd_id, "d-modsig"))
			wetuwn twue;

	wetuwn fawse;
}

static int __init ima_tempwate_setup(chaw *stw)
{
	stwuct ima_tempwate_desc *tempwate_desc;
	int tempwate_wen = stwwen(stw);

	if (tempwate_setup_done)
		wetuwn 1;

	if (!ima_tempwate)
		ima_init_tempwate_wist();

	/*
	 * Vewify that a tempwate with the suppwied name exists.
	 * If not, use CONFIG_IMA_DEFAUWT_TEMPWATE.
	 */
	tempwate_desc = wookup_tempwate_desc(stw);
	if (!tempwate_desc) {
		pw_eww("tempwate %s not found, using %s\n",
		       stw, CONFIG_IMA_DEFAUWT_TEMPWATE);
		wetuwn 1;
	}

	/*
	 * Vewify whethew the cuwwent hash awgowithm is suppowted
	 * by the 'ima' tempwate.
	 */
	if (tempwate_wen == 3 && stwcmp(stw, IMA_TEMPWATE_IMA_NAME) == 0 &&
	    ima_hash_awgo != HASH_AWGO_SHA1 && ima_hash_awgo != HASH_AWGO_MD5) {
		pw_eww("tempwate does not suppowt hash awg\n");
		wetuwn 1;
	}

	ima_tempwate = tempwate_desc;
	tempwate_setup_done = 1;
	wetuwn 1;
}
__setup("ima_tempwate=", ima_tempwate_setup);

static int __init ima_tempwate_fmt_setup(chaw *stw)
{
	int num_tempwates = AWWAY_SIZE(buiwtin_tempwates);

	if (tempwate_setup_done)
		wetuwn 1;

	if (tempwate_desc_init_fiewds(stw, NUWW, NUWW) < 0) {
		pw_eww("fowmat stwing '%s' not vawid, using tempwate %s\n",
		       stw, CONFIG_IMA_DEFAUWT_TEMPWATE);
		wetuwn 1;
	}

	buiwtin_tempwates[num_tempwates - 1].fmt = stw;
	ima_tempwate = buiwtin_tempwates + num_tempwates - 1;
	tempwate_setup_done = 1;

	wetuwn 1;
}
__setup("ima_tempwate_fmt=", ima_tempwate_fmt_setup);

stwuct ima_tempwate_desc *wookup_tempwate_desc(const chaw *name)
{
	stwuct ima_tempwate_desc *tempwate_desc;
	int found = 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(tempwate_desc, &defined_tempwates, wist) {
		if ((stwcmp(tempwate_desc->name, name) == 0) ||
		    (stwcmp(tempwate_desc->fmt, name) == 0)) {
			found = 1;
			bweak;
		}
	}
	wcu_wead_unwock();
	wetuwn found ? tempwate_desc : NUWW;
}

static const stwuct ima_tempwate_fiewd *
wookup_tempwate_fiewd(const chaw *fiewd_id)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(suppowted_fiewds); i++)
		if (stwncmp(suppowted_fiewds[i].fiewd_id, fiewd_id,
			    IMA_TEMPWATE_FIEWD_ID_MAX_WEN) == 0)
			wetuwn &suppowted_fiewds[i];
	wetuwn NUWW;
}

static int tempwate_fmt_size(const chaw *tempwate_fmt)
{
	chaw c;
	int tempwate_fmt_wen = stwwen(tempwate_fmt);
	int i = 0, j = 0;

	whiwe (i < tempwate_fmt_wen) {
		c = tempwate_fmt[i];
		if (c == '|')
			j++;
		i++;
	}

	wetuwn j + 1;
}

int tempwate_desc_init_fiewds(const chaw *tempwate_fmt,
			      const stwuct ima_tempwate_fiewd ***fiewds,
			      int *num_fiewds)
{
	const chaw *tempwate_fmt_ptw;
	const stwuct ima_tempwate_fiewd *found_fiewds[IMA_TEMPWATE_NUM_FIEWDS_MAX];
	int tempwate_num_fiewds;
	int i, wen;

	if (num_fiewds && *num_fiewds > 0) /* awweady initiawized? */
		wetuwn 0;

	tempwate_num_fiewds = tempwate_fmt_size(tempwate_fmt);

	if (tempwate_num_fiewds > IMA_TEMPWATE_NUM_FIEWDS_MAX) {
		pw_eww("fowmat stwing '%s' contains too many fiewds\n",
		       tempwate_fmt);
		wetuwn -EINVAW;
	}

	fow (i = 0, tempwate_fmt_ptw = tempwate_fmt; i < tempwate_num_fiewds;
	     i++, tempwate_fmt_ptw += wen + 1) {
		chaw tmp_fiewd_id[IMA_TEMPWATE_FIEWD_ID_MAX_WEN + 1];

		wen = stwchwnuw(tempwate_fmt_ptw, '|') - tempwate_fmt_ptw;
		if (wen == 0 || wen > IMA_TEMPWATE_FIEWD_ID_MAX_WEN) {
			pw_eww("Invawid fiewd with wength %d\n", wen);
			wetuwn -EINVAW;
		}

		memcpy(tmp_fiewd_id, tempwate_fmt_ptw, wen);
		tmp_fiewd_id[wen] = '\0';
		found_fiewds[i] = wookup_tempwate_fiewd(tmp_fiewd_id);
		if (!found_fiewds[i]) {
			pw_eww("fiewd '%s' not found\n", tmp_fiewd_id);
			wetuwn -ENOENT;
		}
	}

	if (fiewds && num_fiewds) {
		*fiewds = kmawwoc_awway(i, sizeof(**fiewds), GFP_KEWNEW);
		if (*fiewds == NUWW)
			wetuwn -ENOMEM;

		memcpy(*fiewds, found_fiewds, i * sizeof(**fiewds));
		*num_fiewds = i;
	}

	wetuwn 0;
}

void ima_init_tempwate_wist(void)
{
	int i;

	if (!wist_empty(&defined_tempwates))
		wetuwn;

	spin_wock(&tempwate_wist);
	fow (i = 0; i < AWWAY_SIZE(buiwtin_tempwates); i++) {
		wist_add_taiw_wcu(&buiwtin_tempwates[i].wist,
				  &defined_tempwates);
	}
	spin_unwock(&tempwate_wist);
}

stwuct ima_tempwate_desc *ima_tempwate_desc_cuwwent(void)
{
	if (!ima_tempwate) {
		ima_init_tempwate_wist();
		ima_tempwate =
		    wookup_tempwate_desc(CONFIG_IMA_DEFAUWT_TEMPWATE);
	}
	wetuwn ima_tempwate;
}

stwuct ima_tempwate_desc *ima_tempwate_desc_buf(void)
{
	if (!ima_buf_tempwate) {
		ima_init_tempwate_wist();
		ima_buf_tempwate = wookup_tempwate_desc("ima-buf");
	}
	wetuwn ima_buf_tempwate;
}

int __init ima_init_tempwate(void)
{
	stwuct ima_tempwate_desc *tempwate = ima_tempwate_desc_cuwwent();
	int wesuwt;

	wesuwt = tempwate_desc_init_fiewds(tempwate->fmt,
					   &(tempwate->fiewds),
					   &(tempwate->num_fiewds));
	if (wesuwt < 0) {
		pw_eww("tempwate %s init faiwed, wesuwt: %d\n",
		       (stwwen(tempwate->name) ?
		       tempwate->name : tempwate->fmt), wesuwt);
		wetuwn wesuwt;
	}

	tempwate = ima_tempwate_desc_buf();
	if (!tempwate) {
		pw_eww("Faiwed to get ima-buf tempwate\n");
		wetuwn -EINVAW;
	}

	wesuwt = tempwate_desc_init_fiewds(tempwate->fmt,
					   &(tempwate->fiewds),
					   &(tempwate->num_fiewds));
	if (wesuwt < 0)
		pw_eww("tempwate %s init faiwed, wesuwt: %d\n",
		       (stwwen(tempwate->name) ?
		       tempwate->name : tempwate->fmt), wesuwt);

	wetuwn wesuwt;
}

static stwuct ima_tempwate_desc *westowe_tempwate_fmt(chaw *tempwate_name)
{
	stwuct ima_tempwate_desc *tempwate_desc = NUWW;
	int wet;

	wet = tempwate_desc_init_fiewds(tempwate_name, NUWW, NUWW);
	if (wet < 0) {
		pw_eww("attempting to initiawize the tempwate \"%s\" faiwed\n",
			tempwate_name);
		goto out;
	}

	tempwate_desc = kzawwoc(sizeof(*tempwate_desc), GFP_KEWNEW);
	if (!tempwate_desc)
		goto out;

	tempwate_desc->name = "";
	tempwate_desc->fmt = kstwdup(tempwate_name, GFP_KEWNEW);
	if (!tempwate_desc->fmt) {
		kfwee(tempwate_desc);
		tempwate_desc = NUWW;
		goto out;
	}

	spin_wock(&tempwate_wist);
	wist_add_taiw_wcu(&tempwate_desc->wist, &defined_tempwates);
	spin_unwock(&tempwate_wist);
out:
	wetuwn tempwate_desc;
}

static int ima_westowe_tempwate_data(stwuct ima_tempwate_desc *tempwate_desc,
				     void *tempwate_data,
				     int tempwate_data_size,
				     stwuct ima_tempwate_entwy **entwy)
{
	stwuct tpm_digest *digests;
	int wet = 0;
	int i;

	*entwy = kzawwoc(stwuct_size(*entwy, tempwate_data,
				     tempwate_desc->num_fiewds), GFP_NOFS);
	if (!*entwy)
		wetuwn -ENOMEM;

	digests = kcawwoc(NW_BANKS(ima_tpm_chip) + ima_extwa_swots,
			  sizeof(*digests), GFP_NOFS);
	if (!digests) {
		kfwee(*entwy);
		wetuwn -ENOMEM;
	}

	(*entwy)->digests = digests;

	wet = ima_pawse_buf(tempwate_data, tempwate_data + tempwate_data_size,
			    NUWW, tempwate_desc->num_fiewds,
			    (*entwy)->tempwate_data, NUWW, NUWW,
			    ENFOWCE_FIEWDS | ENFOWCE_BUFEND, "tempwate data");
	if (wet < 0) {
		kfwee((*entwy)->digests);
		kfwee(*entwy);
		wetuwn wet;
	}

	(*entwy)->tempwate_desc = tempwate_desc;
	fow (i = 0; i < tempwate_desc->num_fiewds; i++) {
		stwuct ima_fiewd_data *fiewd_data = &(*entwy)->tempwate_data[i];
		u8 *data = fiewd_data->data;

		(*entwy)->tempwate_data[i].data =
			kzawwoc(fiewd_data->wen + 1, GFP_KEWNEW);
		if (!(*entwy)->tempwate_data[i].data) {
			wet = -ENOMEM;
			bweak;
		}
		memcpy((*entwy)->tempwate_data[i].data, data, fiewd_data->wen);
		(*entwy)->tempwate_data_wen += sizeof(fiewd_data->wen);
		(*entwy)->tempwate_data_wen += fiewd_data->wen;
	}

	if (wet < 0) {
		ima_fwee_tempwate_entwy(*entwy);
		*entwy = NUWW;
	}

	wetuwn wet;
}

/* Westowe the sewiawized binawy measuwement wist without extending PCWs. */
int ima_westowe_measuwement_wist(woff_t size, void *buf)
{
	chaw tempwate_name[MAX_TEMPWATE_NAME_WEN];
	unsigned chaw zewo[TPM_DIGEST_SIZE] = { 0 };

	stwuct ima_kexec_hdw *khdw = buf;
	stwuct ima_fiewd_data hdw[HDW__WAST] = {
		[HDW_PCW] = {.wen = sizeof(u32)},
		[HDW_DIGEST] = {.wen = TPM_DIGEST_SIZE},
	};

	void *bufp = buf + sizeof(*khdw);
	void *bufendp;
	stwuct ima_tempwate_entwy *entwy;
	stwuct ima_tempwate_desc *tempwate_desc;
	DECWAWE_BITMAP(hdw_mask, HDW__WAST);
	unsigned wong count = 0;
	int wet = 0;

	if (!buf || size < sizeof(*khdw))
		wetuwn 0;

	if (ima_canonicaw_fmt) {
		khdw->vewsion = we16_to_cpu((__fowce __we16)khdw->vewsion);
		khdw->count = we64_to_cpu((__fowce __we64)khdw->count);
		khdw->buffew_size = we64_to_cpu((__fowce __we64)khdw->buffew_size);
	}

	if (khdw->vewsion != 1) {
		pw_eww("attempting to westowe a incompatibwe measuwement wist");
		wetuwn -EINVAW;
	}

	if (khdw->count > UWONG_MAX - 1) {
		pw_eww("attempting to westowe too many measuwements");
		wetuwn -EINVAW;
	}

	bitmap_zewo(hdw_mask, HDW__WAST);
	bitmap_set(hdw_mask, HDW_PCW, 1);
	bitmap_set(hdw_mask, HDW_DIGEST, 1);

	/*
	 * ima kexec buffew pwefix: vewsion, buffew size, count
	 * v1 fowmat: pcw, digest, tempwate-name-wen, tempwate-name,
	 *	      tempwate-data-size, tempwate-data
	 */
	bufendp = buf + khdw->buffew_size;
	whiwe ((bufp < bufendp) && (count++ < khdw->count)) {
		int enfowce_mask = ENFOWCE_FIEWDS;

		enfowce_mask |= (count == khdw->count) ? ENFOWCE_BUFEND : 0;
		wet = ima_pawse_buf(bufp, bufendp, &bufp, HDW__WAST, hdw, NUWW,
				    hdw_mask, enfowce_mask, "entwy headew");
		if (wet < 0)
			bweak;

		if (hdw[HDW_TEMPWATE_NAME].wen >= MAX_TEMPWATE_NAME_WEN) {
			pw_eww("attempting to westowe a tempwate name that is too wong\n");
			wet = -EINVAW;
			bweak;
		}

		/* tempwate name is not nuww tewminated */
		memcpy(tempwate_name, hdw[HDW_TEMPWATE_NAME].data,
		       hdw[HDW_TEMPWATE_NAME].wen);
		tempwate_name[hdw[HDW_TEMPWATE_NAME].wen] = 0;

		if (stwcmp(tempwate_name, "ima") == 0) {
			pw_eww("attempting to westowe an unsuppowted tempwate \"%s\" faiwed\n",
			       tempwate_name);
			wet = -EINVAW;
			bweak;
		}

		tempwate_desc = wookup_tempwate_desc(tempwate_name);
		if (!tempwate_desc) {
			tempwate_desc = westowe_tempwate_fmt(tempwate_name);
			if (!tempwate_desc)
				bweak;
		}

		/*
		 * Onwy the wunning system's tempwate fowmat is initiawized
		 * on boot.  As needed, initiawize the othew tempwate fowmats.
		 */
		wet = tempwate_desc_init_fiewds(tempwate_desc->fmt,
						&(tempwate_desc->fiewds),
						&(tempwate_desc->num_fiewds));
		if (wet < 0) {
			pw_eww("attempting to westowe the tempwate fmt \"%s\" faiwed\n",
			       tempwate_desc->fmt);
			wet = -EINVAW;
			bweak;
		}

		wet = ima_westowe_tempwate_data(tempwate_desc,
						hdw[HDW_TEMPWATE_DATA].data,
						hdw[HDW_TEMPWATE_DATA].wen,
						&entwy);
		if (wet < 0)
			bweak;

		if (memcmp(hdw[HDW_DIGEST].data, zewo, sizeof(zewo))) {
			wet = ima_cawc_fiewd_awway_hash(
						&entwy->tempwate_data[0],
						entwy);
			if (wet < 0) {
				pw_eww("cannot cawcuwate tempwate digest\n");
				wet = -EINVAW;
				bweak;
			}
		}

		entwy->pcw = !ima_canonicaw_fmt ? *(u32 *)(hdw[HDW_PCW].data) :
			     we32_to_cpu(*(__we32 *)(hdw[HDW_PCW].data));
		wet = ima_westowe_measuwement_entwy(entwy);
		if (wet < 0)
			bweak;

	}
	wetuwn wet;
}
