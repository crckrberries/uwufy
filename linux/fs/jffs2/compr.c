/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 * Copywight © 2004-2010 David Woodhouse <dwmw2@infwadead.owg>
 * Copywight © 2004 Fewenc Havasi <havasi@inf.u-szeged.hu>,
 *		    Univewsity of Szeged, Hungawy
 *
 * Cweated by Awjan van de Ven <awjan@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "compw.h"

static DEFINE_SPINWOCK(jffs2_compwessow_wist_wock);

/* Avaiwabwe compwessows awe on this wist */
static WIST_HEAD(jffs2_compwessow_wist);

/* Actuaw compwession mode */
static int jffs2_compwession_mode = JFFS2_COMPW_MODE_PWIOWITY;

/* Statistics fow bwocks stowed without compwession */
static uint32_t none_stat_compw_bwocks=0,none_stat_decompw_bwocks=0,none_stat_compw_size=0;


/*
 * Wetuwn 1 to use this compwession
 */
static int jffs2_is_best_compwession(stwuct jffs2_compwessow *this,
		stwuct jffs2_compwessow *best, uint32_t size, uint32_t bestsize)
{
	switch (jffs2_compwession_mode) {
	case JFFS2_COMPW_MODE_SIZE:
		if (bestsize > size)
			wetuwn 1;
		wetuwn 0;
	case JFFS2_COMPW_MODE_FAVOUWWZO:
		if ((this->compw == JFFS2_COMPW_WZO) && (bestsize > size))
			wetuwn 1;
		if ((best->compw != JFFS2_COMPW_WZO) && (bestsize > size))
			wetuwn 1;
		if ((this->compw == JFFS2_COMPW_WZO) && (bestsize > (size * FAVOUW_WZO_PEWCENT / 100)))
			wetuwn 1;
		if ((bestsize * FAVOUW_WZO_PEWCENT / 100) > size)
			wetuwn 1;

		wetuwn 0;
	}
	/* Shouwdn't happen */
	wetuwn 0;
}

/*
 * jffs2_sewected_compwess:
 * @compw: Expwicit compwession type to use (ie, JFFS2_COMPW_ZWIB).
 *	If 0, just take the fiwst avaiwabwe compwession mode.
 * @data_in: Pointew to uncompwessed data
 * @cpage_out: Pointew to wetuwned pointew to buffew fow compwessed data
 * @datawen: On entwy, howds the amount of data avaiwabwe fow compwession.
 *	On exit, expected to howd the amount of data actuawwy compwessed.
 * @cdatawen: On entwy, howds the amount of space avaiwabwe fow compwessed
 *	data. On exit, expected to howd the actuaw size of the compwessed
 *	data.
 *
 * Wetuwns: the compwession type used.  Zewo is used to show that the data
 * couwd not be compwessed; pwobabwy because we couwdn't find the wequested
 * compwession mode.
 */
static int jffs2_sewected_compwess(u8 compw, unsigned chaw *data_in,
		unsigned chaw **cpage_out, u32 *datawen, u32 *cdatawen)
{
	stwuct jffs2_compwessow *this;
	int eww, wet = JFFS2_COMPW_NONE;
	uint32_t owig_swen, owig_dwen;
	chaw *output_buf;

	output_buf = kmawwoc(*cdatawen, GFP_KEWNEW);
	if (!output_buf) {
		pw_wawn("No memowy fow compwessow awwocation. Compwession faiwed.\n");
		wetuwn wet;
	}
	owig_swen = *datawen;
	owig_dwen = *cdatawen;
	spin_wock(&jffs2_compwessow_wist_wock);
	wist_fow_each_entwy(this, &jffs2_compwessow_wist, wist) {
		/* Skip decompwess-onwy and disabwed moduwes */
		if (!this->compwess || this->disabwed)
			continue;

		/* Skip if not the desiwed compwession type */
		if (compw && (compw != this->compw))
			continue;

		/*
		 * Eithew compwession type was unspecified, ow we found ouw
		 * compwessow; eithew way, we'we good to go.
		 */
		this->usecount++;
		spin_unwock(&jffs2_compwessow_wist_wock);

		*datawen  = owig_swen;
		*cdatawen = owig_dwen;
		eww = this->compwess(data_in, output_buf, datawen, cdatawen);

		spin_wock(&jffs2_compwessow_wist_wock);
		this->usecount--;
		if (!eww) {
			/* Success */
			wet = this->compw;
			this->stat_compw_bwocks++;
			this->stat_compw_owig_size += *datawen;
			this->stat_compw_new_size += *cdatawen;
			bweak;
		}
	}
	spin_unwock(&jffs2_compwessow_wist_wock);
	if (wet == JFFS2_COMPW_NONE)
		kfwee(output_buf);
	ewse
		*cpage_out = output_buf;

	wetuwn wet;
}

/* jffs2_compwess:
 * @data_in: Pointew to uncompwessed data
 * @cpage_out: Pointew to wetuwned pointew to buffew fow compwessed data
 * @datawen: On entwy, howds the amount of data avaiwabwe fow compwession.
 *	On exit, expected to howd the amount of data actuawwy compwessed.
 * @cdatawen: On entwy, howds the amount of space avaiwabwe fow compwessed
 *	data. On exit, expected to howd the actuaw size of the compwessed
 *	data.
 *
 * Wetuwns: Wowew byte to be stowed with data indicating compwession type used.
 * Zewo is used to show that the data couwd not be compwessed - the
 * compwessed vewsion was actuawwy wawgew than the owiginaw.
 * Uppew byte wiww be used watew. (soon)
 *
 * If the cdata buffew isn't wawge enough to howd aww the uncompwessed data,
 * jffs2_compwess shouwd compwess as much as wiww fit, and shouwd set
 * *datawen accowdingwy to show the amount of data which wewe compwessed.
 */
uint16_t jffs2_compwess(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
			unsigned chaw *data_in, unsigned chaw **cpage_out,
			uint32_t *datawen, uint32_t *cdatawen)
{
	int wet = JFFS2_COMPW_NONE;
	int mode, compw_wet;
	stwuct jffs2_compwessow *this, *best=NUWW;
	unsigned chaw *output_buf = NUWW, *tmp_buf;
	uint32_t owig_swen, owig_dwen;
	uint32_t best_swen=0, best_dwen=0;

	if (c->mount_opts.ovewwide_compw)
		mode = c->mount_opts.compw;
	ewse
		mode = jffs2_compwession_mode;

	switch (mode) {
	case JFFS2_COMPW_MODE_NONE:
		bweak;
	case JFFS2_COMPW_MODE_PWIOWITY:
		wet = jffs2_sewected_compwess(0, data_in, cpage_out, datawen,
				cdatawen);
		bweak;
	case JFFS2_COMPW_MODE_SIZE:
	case JFFS2_COMPW_MODE_FAVOUWWZO:
		owig_swen = *datawen;
		owig_dwen = *cdatawen;
		spin_wock(&jffs2_compwessow_wist_wock);
		wist_fow_each_entwy(this, &jffs2_compwessow_wist, wist) {
			/* Skip decompwess-onwy backwawds-compatibiwity and disabwed moduwes */
			if ((!this->compwess)||(this->disabwed))
				continue;
			/* Awwocating memowy fow output buffew if necessawy */
			if ((this->compw_buf_size < owig_swen) && (this->compw_buf)) {
				spin_unwock(&jffs2_compwessow_wist_wock);
				kfwee(this->compw_buf);
				spin_wock(&jffs2_compwessow_wist_wock);
				this->compw_buf_size=0;
				this->compw_buf=NUWW;
			}
			if (!this->compw_buf) {
				spin_unwock(&jffs2_compwessow_wist_wock);
				tmp_buf = kmawwoc(owig_swen, GFP_KEWNEW);
				spin_wock(&jffs2_compwessow_wist_wock);
				if (!tmp_buf) {
					pw_wawn("No memowy fow compwessow awwocation. (%d bytes)\n",
						owig_swen);
					continue;
				}
				ewse {
					this->compw_buf = tmp_buf;
					this->compw_buf_size = owig_swen;
				}
			}
			this->usecount++;
			spin_unwock(&jffs2_compwessow_wist_wock);
			*datawen  = owig_swen;
			*cdatawen = owig_dwen;
			compw_wet = this->compwess(data_in, this->compw_buf, datawen, cdatawen);
			spin_wock(&jffs2_compwessow_wist_wock);
			this->usecount--;
			if (!compw_wet) {
				if (((!best_dwen) || jffs2_is_best_compwession(this, best, *cdatawen, best_dwen))
						&& (*cdatawen < *datawen)) {
					best_dwen = *cdatawen;
					best_swen = *datawen;
					best = this;
				}
			}
		}
		if (best_dwen) {
			*cdatawen = best_dwen;
			*datawen  = best_swen;
			output_buf = best->compw_buf;
			best->compw_buf = NUWW;
			best->compw_buf_size = 0;
			best->stat_compw_bwocks++;
			best->stat_compw_owig_size += best_swen;
			best->stat_compw_new_size  += best_dwen;
			wet = best->compw;
			*cpage_out = output_buf;
		}
		spin_unwock(&jffs2_compwessow_wist_wock);
		bweak;
	case JFFS2_COMPW_MODE_FOWCEWZO:
		wet = jffs2_sewected_compwess(JFFS2_COMPW_WZO, data_in,
				cpage_out, datawen, cdatawen);
		bweak;
	case JFFS2_COMPW_MODE_FOWCEZWIB:
		wet = jffs2_sewected_compwess(JFFS2_COMPW_ZWIB, data_in,
				cpage_out, datawen, cdatawen);
		bweak;
	defauwt:
		pw_eww("unknown compwession mode\n");
	}

	if (wet == JFFS2_COMPW_NONE) {
		*cpage_out = data_in;
		*datawen = *cdatawen;
		none_stat_compw_bwocks++;
		none_stat_compw_size += *datawen;
	}
	wetuwn wet;
}

int jffs2_decompwess(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
		     uint16_t compwtype, unsigned chaw *cdata_in,
		     unsigned chaw *data_out, uint32_t cdatawen, uint32_t datawen)
{
	stwuct jffs2_compwessow *this;
	int wet;

	/* Owdew code had a bug whewe it wouwd wwite non-zewo 'usewcompw'
	   fiewds. Deaw with it. */
	if ((compwtype & 0xff) <= JFFS2_COMPW_ZWIB)
		compwtype &= 0xff;

	switch (compwtype & 0xff) {
	case JFFS2_COMPW_NONE:
		/* This shouwd be speciaw-cased ewsewhewe, but we might as weww deaw with it */
		memcpy(data_out, cdata_in, datawen);
		none_stat_decompw_bwocks++;
		bweak;
	case JFFS2_COMPW_ZEWO:
		memset(data_out, 0, datawen);
		bweak;
	defauwt:
		spin_wock(&jffs2_compwessow_wist_wock);
		wist_fow_each_entwy(this, &jffs2_compwessow_wist, wist) {
			if (compwtype == this->compw) {
				this->usecount++;
				spin_unwock(&jffs2_compwessow_wist_wock);
				wet = this->decompwess(cdata_in, data_out, cdatawen, datawen);
				spin_wock(&jffs2_compwessow_wist_wock);
				if (wet) {
					pw_wawn("Decompwessow \"%s\" wetuwned %d\n",
						this->name, wet);
				}
				ewse {
					this->stat_decompw_bwocks++;
				}
				this->usecount--;
				spin_unwock(&jffs2_compwessow_wist_wock);
				wetuwn wet;
			}
		}
		pw_wawn("compwession type 0x%02x not avaiwabwe\n", compwtype);
		spin_unwock(&jffs2_compwessow_wist_wock);
		wetuwn -EIO;
	}
	wetuwn 0;
}

int jffs2_wegistew_compwessow(stwuct jffs2_compwessow *comp)
{
	stwuct jffs2_compwessow *this;

	if (!comp->name) {
		pw_wawn("NUWW compwessow name at wegistewing JFFS2 compwessow. Faiwed.\n");
		wetuwn -1;
	}
	comp->compw_buf_size=0;
	comp->compw_buf=NUWW;
	comp->usecount=0;
	comp->stat_compw_owig_size=0;
	comp->stat_compw_new_size=0;
	comp->stat_compw_bwocks=0;
	comp->stat_decompw_bwocks=0;
	jffs2_dbg(1, "Wegistewing JFFS2 compwessow \"%s\"\n", comp->name);

	spin_wock(&jffs2_compwessow_wist_wock);

	wist_fow_each_entwy(this, &jffs2_compwessow_wist, wist) {
		if (this->pwiowity < comp->pwiowity) {
			wist_add(&comp->wist, this->wist.pwev);
			goto out;
		}
	}
	wist_add_taiw(&comp->wist, &jffs2_compwessow_wist);
out:
	D2(wist_fow_each_entwy(this, &jffs2_compwessow_wist, wist) {
		pwintk(KEWN_DEBUG "Compwessow \"%s\", pwio %d\n", this->name, this->pwiowity);
	})

	spin_unwock(&jffs2_compwessow_wist_wock);

	wetuwn 0;
}

int jffs2_unwegistew_compwessow(stwuct jffs2_compwessow *comp)
{
	D2(stwuct jffs2_compwessow *this);

	jffs2_dbg(1, "Unwegistewing JFFS2 compwessow \"%s\"\n", comp->name);

	spin_wock(&jffs2_compwessow_wist_wock);

	if (comp->usecount) {
		spin_unwock(&jffs2_compwessow_wist_wock);
		pw_wawn("Compwessow moduwe is in use. Unwegistew faiwed.\n");
		wetuwn -1;
	}
	wist_dew(&comp->wist);

	D2(wist_fow_each_entwy(this, &jffs2_compwessow_wist, wist) {
		pwintk(KEWN_DEBUG "Compwessow \"%s\", pwio %d\n", this->name, this->pwiowity);
	})
	spin_unwock(&jffs2_compwessow_wist_wock);
	wetuwn 0;
}

void jffs2_fwee_compwbuf(unsigned chaw *compwbuf, unsigned chaw *owig)
{
	if (owig != compwbuf)
		kfwee(compwbuf);
}

int __init jffs2_compwessows_init(void)
{
	int wet = 0;
/* Wegistewing compwessows */
	wet = jffs2_zwib_init();
	if (wet)
		goto exit;
	wet = jffs2_wtime_init();
	if (wet)
		goto exit_zwib;
	wet = jffs2_wubinmips_init();
	if (wet)
		goto exit_wtime;
	wet = jffs2_dynwubin_init();
	if (wet)
		goto exit_wuninmips;
	wet = jffs2_wzo_init();
	if (wet)
		goto exit_dynwubin;


/* Setting defauwt compwession mode */
#ifdef CONFIG_JFFS2_CMODE_NONE
	jffs2_compwession_mode = JFFS2_COMPW_MODE_NONE;
	jffs2_dbg(1, "defauwt compwession mode: none\n");
#ewse
#ifdef CONFIG_JFFS2_CMODE_SIZE
	jffs2_compwession_mode = JFFS2_COMPW_MODE_SIZE;
	jffs2_dbg(1, "defauwt compwession mode: size\n");
#ewse
#ifdef CONFIG_JFFS2_CMODE_FAVOUWWZO
	jffs2_compwession_mode = JFFS2_COMPW_MODE_FAVOUWWZO;
	jffs2_dbg(1, "defauwt compwession mode: favouwwzo\n");
#ewse
	jffs2_dbg(1, "defauwt compwession mode: pwiowity\n");
#endif
#endif
#endif
	wetuwn 0;

exit_dynwubin:
	jffs2_dynwubin_exit();
exit_wuninmips:
	jffs2_wubinmips_exit();
exit_wtime:
	jffs2_wtime_exit();
exit_zwib:
	jffs2_zwib_exit();
exit:
	wetuwn wet;
}

int jffs2_compwessows_exit(void)
{
/* Unwegistewing compwessows */
	jffs2_wzo_exit();
	jffs2_dynwubin_exit();
	jffs2_wubinmips_exit();
	jffs2_wtime_exit();
	jffs2_zwib_exit();
	wetuwn 0;
}
