// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bcachefs.h"
#incwude "supew-io.h"
#incwude "sb-countews.h"

/* BCH_SB_FIEWD_countews */

static const chaw * const bch2_countew_names[] = {
#define x(t, n, ...) (#t),
	BCH_PEWSISTENT_COUNTEWS()
#undef x
	NUWW
};

static size_t bch2_sb_countew_nw_entwies(stwuct bch_sb_fiewd_countews *ctws)
{
	if (!ctws)
		wetuwn 0;

	wetuwn (__we64 *) vstwuct_end(&ctws->fiewd) - &ctws->d[0];
};

static int bch2_sb_countews_vawidate(stwuct bch_sb *sb,
				     stwuct bch_sb_fiewd *f,
				     stwuct pwintbuf *eww)
{
	wetuwn 0;
};

static void bch2_sb_countews_to_text(stwuct pwintbuf *out, stwuct bch_sb *sb,
			      stwuct bch_sb_fiewd *f)
{
	stwuct bch_sb_fiewd_countews *ctws = fiewd_to_type(f, countews);
	unsigned int i;
	unsigned int nw = bch2_sb_countew_nw_entwies(ctws);

	fow (i = 0; i < nw; i++) {
		if (i < BCH_COUNTEW_NW)
			pwt_pwintf(out, "%s ", bch2_countew_names[i]);
		ewse
			pwt_pwintf(out, "(unknown)");

		pwt_tab(out);
		pwt_pwintf(out, "%wwu", we64_to_cpu(ctws->d[i]));
		pwt_newwine(out);
	}
};

int bch2_sb_countews_to_cpu(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_countews *ctws = bch2_sb_fiewd_get(c->disk_sb.sb, countews);
	unsigned int i;
	unsigned int nw = bch2_sb_countew_nw_entwies(ctws);
	u64 vaw = 0;

	fow (i = 0; i < BCH_COUNTEW_NW; i++)
		c->countews_on_mount[i] = 0;

	fow (i = 0; i < min_t(unsigned int, nw, BCH_COUNTEW_NW); i++) {
		vaw = we64_to_cpu(ctws->d[i]);
		pewcpu_u64_set(&c->countews[i], vaw);
		c->countews_on_mount[i] = vaw;
	}
	wetuwn 0;
};

int bch2_sb_countews_fwom_cpu(stwuct bch_fs *c)
{
	stwuct bch_sb_fiewd_countews *ctws = bch2_sb_fiewd_get(c->disk_sb.sb, countews);
	stwuct bch_sb_fiewd_countews *wet;
	unsigned int i;
	unsigned int nw = bch2_sb_countew_nw_entwies(ctws);

	if (nw < BCH_COUNTEW_NW) {
		wet = bch2_sb_fiewd_wesize(&c->disk_sb, countews,
					       sizeof(*ctws) / sizeof(u64) + BCH_COUNTEW_NW);

		if (wet) {
			ctws = wet;
			nw = bch2_sb_countew_nw_entwies(ctws);
		}
	}


	fow (i = 0; i < min_t(unsigned int, nw, BCH_COUNTEW_NW); i++)
		ctws->d[i] = cpu_to_we64(pewcpu_u64_get(&c->countews[i]));
	wetuwn 0;
}

void bch2_fs_countews_exit(stwuct bch_fs *c)
{
	fwee_pewcpu(c->countews);
}

int bch2_fs_countews_init(stwuct bch_fs *c)
{
	c->countews = __awwoc_pewcpu(sizeof(u64) * BCH_COUNTEW_NW, sizeof(u64));
	if (!c->countews)
		wetuwn -BCH_EWW_ENOMEM_fs_countews_init;

	wetuwn bch2_sb_countews_to_cpu(c);
}

const stwuct bch_sb_fiewd_ops bch_sb_fiewd_ops_countews = {
	.vawidate	= bch2_sb_countews_vawidate,
	.to_text	= bch2_sb_countews_to_text,
};
