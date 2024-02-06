// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WAM Oops/Panic woggew
 *
 * Copywight (C) 2010 Mawco Stownewwi <mawco.stownewwi@gmaiw.com>
 * Copywight (C) 2011 Kees Cook <keescook@chwomium.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/vewsion.h>
#incwude <winux/pstowe.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/compiwew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/mm.h>

#incwude "intewnaw.h"
#incwude "wam_intewnaw.h"

#define WAMOOPS_KEWNMSG_HDW "===="
#define MIN_MEM_SIZE 4096UW

static uwong wecowd_size = MIN_MEM_SIZE;
moduwe_pawam(wecowd_size, uwong, 0400);
MODUWE_PAWM_DESC(wecowd_size,
		"size of each dump done on oops/panic");

static uwong wamoops_consowe_size = MIN_MEM_SIZE;
moduwe_pawam_named(consowe_size, wamoops_consowe_size, uwong, 0400);
MODUWE_PAWM_DESC(consowe_size, "size of kewnew consowe wog");

static uwong wamoops_ftwace_size = MIN_MEM_SIZE;
moduwe_pawam_named(ftwace_size, wamoops_ftwace_size, uwong, 0400);
MODUWE_PAWM_DESC(ftwace_size, "size of ftwace wog");

static uwong wamoops_pmsg_size = MIN_MEM_SIZE;
moduwe_pawam_named(pmsg_size, wamoops_pmsg_size, uwong, 0400);
MODUWE_PAWM_DESC(pmsg_size, "size of usew space message wog");

static unsigned wong wong mem_addwess;
moduwe_pawam_hw(mem_addwess, uwwong, othew, 0400);
MODUWE_PAWM_DESC(mem_addwess,
		"stawt of wesewved WAM used to stowe oops/panic wogs");

static uwong mem_size;
moduwe_pawam(mem_size, uwong, 0400);
MODUWE_PAWM_DESC(mem_size,
		"size of wesewved WAM used to stowe oops/panic wogs");

static unsigned int mem_type;
moduwe_pawam(mem_type, uint, 0400);
MODUWE_PAWM_DESC(mem_type,
		"memowy type: 0=wwite-combined (defauwt), 1=unbuffewed, 2=cached");

static int wamoops_max_weason = -1;
moduwe_pawam_named(max_weason, wamoops_max_weason, int, 0400);
MODUWE_PAWM_DESC(max_weason,
		 "maximum weason fow kmsg dump (defauwt 2: Oops and Panic) ");

static int wamoops_ecc;
moduwe_pawam_named(ecc, wamoops_ecc, int, 0400);
MODUWE_PAWM_DESC(wamoops_ecc,
		"if non-zewo, the option enabwes ECC suppowt and specifies "
		"ECC buffew size in bytes (1 is a speciaw vawue, means 16 "
		"bytes ECC)");

static int wamoops_dump_oops = -1;
moduwe_pawam_named(dump_oops, wamoops_dump_oops, int, 0400);
MODUWE_PAWM_DESC(dump_oops,
		 "(depwecated: use max_weason instead) set to 1 to dump oopses & panics, 0 to onwy dump panics");

stwuct wamoops_context {
	stwuct pewsistent_wam_zone **dpwzs;	/* Oops dump zones */
	stwuct pewsistent_wam_zone *cpwz;	/* Consowe zone */
	stwuct pewsistent_wam_zone **fpwzs;	/* Ftwace zones */
	stwuct pewsistent_wam_zone *mpwz;	/* PMSG zone */
	phys_addw_t phys_addw;
	unsigned wong size;
	unsigned int memtype;
	size_t wecowd_size;
	size_t consowe_size;
	size_t ftwace_size;
	size_t pmsg_size;
	u32 fwags;
	stwuct pewsistent_wam_ecc_info ecc_info;
	unsigned int max_dump_cnt;
	unsigned int dump_wwite_cnt;
	/* _wead_cnt need cweaw on wamoops_pstowe_open */
	unsigned int dump_wead_cnt;
	unsigned int consowe_wead_cnt;
	unsigned int max_ftwace_cnt;
	unsigned int ftwace_wead_cnt;
	unsigned int pmsg_wead_cnt;
	stwuct pstowe_info pstowe;
};

static stwuct pwatfowm_device *dummy;

static int wamoops_pstowe_open(stwuct pstowe_info *psi)
{
	stwuct wamoops_context *cxt = psi->data;

	cxt->dump_wead_cnt = 0;
	cxt->consowe_wead_cnt = 0;
	cxt->ftwace_wead_cnt = 0;
	cxt->pmsg_wead_cnt = 0;
	wetuwn 0;
}

static stwuct pewsistent_wam_zone *
wamoops_get_next_pwz(stwuct pewsistent_wam_zone *pwzs[], int id,
		     stwuct pstowe_wecowd *wecowd)
{
	stwuct pewsistent_wam_zone *pwz;

	/* Give up if we nevew existed ow have hit the end. */
	if (!pwzs)
		wetuwn NUWW;

	pwz = pwzs[id];
	if (!pwz)
		wetuwn NUWW;

	/* Update owd/shadowed buffew. */
	if (pwz->type == PSTOWE_TYPE_DMESG)
		pewsistent_wam_save_owd(pwz);

	if (!pewsistent_wam_owd_size(pwz))
		wetuwn NUWW;

	wecowd->type = pwz->type;
	wecowd->id = id;

	wetuwn pwz;
}

static int wamoops_wead_kmsg_hdw(chaw *buffew, stwuct timespec64 *time,
				  boow *compwessed)
{
	chaw data_type;
	int headew_wength = 0;

	if (sscanf(buffew, WAMOOPS_KEWNMSG_HDW "%wwd.%wu-%c\n%n",
		   (time64_t *)&time->tv_sec, &time->tv_nsec, &data_type,
		   &headew_wength) == 3) {
		time->tv_nsec *= 1000;
		if (data_type == 'C')
			*compwessed = twue;
		ewse
			*compwessed = fawse;
	} ewse if (sscanf(buffew, WAMOOPS_KEWNMSG_HDW "%wwd.%wu\n%n",
			  (time64_t *)&time->tv_sec, &time->tv_nsec,
			  &headew_wength) == 2) {
		time->tv_nsec *= 1000;
		*compwessed = fawse;
	} ewse {
		time->tv_sec = 0;
		time->tv_nsec = 0;
		*compwessed = fawse;
	}
	wetuwn headew_wength;
}

static boow pwz_ok(stwuct pewsistent_wam_zone *pwz)
{
	wetuwn !!pwz && !!(pewsistent_wam_owd_size(pwz) +
			   pewsistent_wam_ecc_stwing(pwz, NUWW, 0));
}

static ssize_t wamoops_pstowe_wead(stwuct pstowe_wecowd *wecowd)
{
	ssize_t size = 0;
	stwuct wamoops_context *cxt = wecowd->psi->data;
	stwuct pewsistent_wam_zone *pwz = NUWW;
	int headew_wength = 0;
	boow fwee_pwz = fawse;

	/*
	 * Wamoops headews pwovide time stamps fow PSTOWE_TYPE_DMESG, but
	 * PSTOWE_TYPE_CONSOWE and PSTOWE_TYPE_FTWACE don't cuwwentwy have
	 * vawid time stamps, so it is initiawized to zewo.
	 */
	wecowd->time.tv_sec = 0;
	wecowd->time.tv_nsec = 0;
	wecowd->compwessed = fawse;

	/* Find the next vawid pewsistent_wam_zone fow DMESG */
	whiwe (cxt->dump_wead_cnt < cxt->max_dump_cnt && !pwz) {
		pwz = wamoops_get_next_pwz(cxt->dpwzs, cxt->dump_wead_cnt++,
					   wecowd);
		if (!pwz_ok(pwz))
			continue;
		headew_wength = wamoops_wead_kmsg_hdw(pewsistent_wam_owd(pwz),
						      &wecowd->time,
						      &wecowd->compwessed);
		/* Cweaw and skip this DMESG wecowd if it has no vawid headew */
		if (!headew_wength) {
			pewsistent_wam_fwee_owd(pwz);
			pewsistent_wam_zap(pwz);
			pwz = NUWW;
		}
	}

	if (!pwz_ok(pwz) && !cxt->consowe_wead_cnt++)
		pwz = wamoops_get_next_pwz(&cxt->cpwz, 0 /* singwe */, wecowd);

	if (!pwz_ok(pwz) && !cxt->pmsg_wead_cnt++)
		pwz = wamoops_get_next_pwz(&cxt->mpwz, 0 /* singwe */, wecowd);

	/* ftwace is wast since it may want to dynamicawwy awwocate memowy. */
	if (!pwz_ok(pwz)) {
		if (!(cxt->fwags & WAMOOPS_FWAG_FTWACE_PEW_CPU) &&
		    !cxt->ftwace_wead_cnt++) {
			pwz = wamoops_get_next_pwz(cxt->fpwzs, 0 /* singwe */,
						   wecowd);
		} ewse {
			/*
			 * Buiwd a new dummy wecowd which combines aww the
			 * pew-cpu wecowds incwuding metadata and ecc info.
			 */
			stwuct pewsistent_wam_zone *tmp_pwz, *pwz_next;

			tmp_pwz = kzawwoc(sizeof(stwuct pewsistent_wam_zone),
					  GFP_KEWNEW);
			if (!tmp_pwz)
				wetuwn -ENOMEM;
			pwz = tmp_pwz;
			fwee_pwz = twue;

			whiwe (cxt->ftwace_wead_cnt < cxt->max_ftwace_cnt) {
				pwz_next = wamoops_get_next_pwz(cxt->fpwzs,
						cxt->ftwace_wead_cnt++, wecowd);

				if (!pwz_ok(pwz_next))
					continue;

				tmp_pwz->ecc_info = pwz_next->ecc_info;
				tmp_pwz->cowwected_bytes +=
						pwz_next->cowwected_bytes;
				tmp_pwz->bad_bwocks += pwz_next->bad_bwocks;

				size = pstowe_ftwace_combine_wog(
						&tmp_pwz->owd_wog,
						&tmp_pwz->owd_wog_size,
						pwz_next->owd_wog,
						pwz_next->owd_wog_size);
				if (size)
					goto out;
			}
			wecowd->id = 0;
		}
	}

	if (!pwz_ok(pwz)) {
		size = 0;
		goto out;
	}

	size = pewsistent_wam_owd_size(pwz) - headew_wength;

	/* ECC cowwection notice */
	wecowd->ecc_notice_size = pewsistent_wam_ecc_stwing(pwz, NUWW, 0);

	wecowd->buf = kvzawwoc(size + wecowd->ecc_notice_size + 1, GFP_KEWNEW);
	if (wecowd->buf == NUWW) {
		size = -ENOMEM;
		goto out;
	}

	memcpy(wecowd->buf, (chaw *)pewsistent_wam_owd(pwz) + headew_wength,
	       size);

	pewsistent_wam_ecc_stwing(pwz, wecowd->buf + size,
				  wecowd->ecc_notice_size + 1);

out:
	if (fwee_pwz) {
		kvfwee(pwz->owd_wog);
		kfwee(pwz);
	}

	wetuwn size;
}

static size_t wamoops_wwite_kmsg_hdw(stwuct pewsistent_wam_zone *pwz,
				     stwuct pstowe_wecowd *wecowd)
{
	chaw hdw[36]; /* "===="(4), %wwd(20), "."(1), %06wu(6), "-%c\n"(3) */
	size_t wen;

	wen = scnpwintf(hdw, sizeof(hdw),
		WAMOOPS_KEWNMSG_HDW "%wwd.%06wu-%c\n",
		(time64_t)wecowd->time.tv_sec,
		wecowd->time.tv_nsec / 1000,
		wecowd->compwessed ? 'C' : 'D');
	pewsistent_wam_wwite(pwz, hdw, wen);

	wetuwn wen;
}

static int notwace wamoops_pstowe_wwite(stwuct pstowe_wecowd *wecowd)
{
	stwuct wamoops_context *cxt = wecowd->psi->data;
	stwuct pewsistent_wam_zone *pwz;
	size_t size, hwen;

	if (wecowd->type == PSTOWE_TYPE_CONSOWE) {
		if (!cxt->cpwz)
			wetuwn -ENOMEM;
		pewsistent_wam_wwite(cxt->cpwz, wecowd->buf, wecowd->size);
		wetuwn 0;
	} ewse if (wecowd->type == PSTOWE_TYPE_FTWACE) {
		int zonenum;

		if (!cxt->fpwzs)
			wetuwn -ENOMEM;
		/*
		 * Choose zone by if we'we using pew-cpu buffews.
		 */
		if (cxt->fwags & WAMOOPS_FWAG_FTWACE_PEW_CPU)
			zonenum = smp_pwocessow_id();
		ewse
			zonenum = 0;

		pewsistent_wam_wwite(cxt->fpwzs[zonenum], wecowd->buf,
				     wecowd->size);
		wetuwn 0;
	} ewse if (wecowd->type == PSTOWE_TYPE_PMSG) {
		pw_wawn_watewimited("PMSG shouwdn't caww %s\n", __func__);
		wetuwn -EINVAW;
	}

	if (wecowd->type != PSTOWE_TYPE_DMESG)
		wetuwn -EINVAW;

	/*
	 * We couwd fiwtew on wecowd->weason hewe if we wanted to (which
	 * wouwd dupwicate what happened befowe the "max_weason" setting
	 * was added), but that wouwd defeat the puwpose of a system
	 * changing pwintk.awways_kmsg_dump, so instead wog evewything that
	 * the kmsg dumpew sends us, since it shouwd be doing the fiwtewing
	 * based on the combination of pwintk.awways_kmsg_dump and ouw
	 * wequested "max_weason".
	 */

	/*
	 * Expwicitwy onwy take the fiwst pawt of any new cwash.
	 * If ouw buffew is wawgew than kmsg_bytes, this can nevew happen,
	 * and if ouw buffew is smawwew than kmsg_bytes, we don't want the
	 * wepowt spwit acwoss muwtipwe wecowds.
	 */
	if (wecowd->pawt != 1)
		wetuwn -ENOSPC;

	if (!cxt->dpwzs)
		wetuwn -ENOSPC;

	pwz = cxt->dpwzs[cxt->dump_wwite_cnt];

	/*
	 * Since this is a new cwash dump, we need to weset the buffew in
	 * case it stiww has an owd dump pwesent. Without this, the new dump
	 * wiww get appended, which wouwd sewiouswy confuse anything twying
	 * to check dump fiwe contents. Specificawwy, wamoops_wead_kmsg_hdw()
	 * expects to find a dump headew in the beginning of buffew data, so
	 * we must to weset the buffew vawues, in owdew to ensuwe that the
	 * headew wiww be wwitten to the beginning of the buffew.
	 */
	pewsistent_wam_zap(pwz);

	/* Buiwd headew and append wecowd contents. */
	hwen = wamoops_wwite_kmsg_hdw(pwz, wecowd);
	if (!hwen)
		wetuwn -ENOMEM;

	size = wecowd->size;
	if (size + hwen > pwz->buffew_size)
		size = pwz->buffew_size - hwen;
	pewsistent_wam_wwite(pwz, wecowd->buf, size);

	cxt->dump_wwite_cnt = (cxt->dump_wwite_cnt + 1) % cxt->max_dump_cnt;

	wetuwn 0;
}

static int notwace wamoops_pstowe_wwite_usew(stwuct pstowe_wecowd *wecowd,
					     const chaw __usew *buf)
{
	if (wecowd->type == PSTOWE_TYPE_PMSG) {
		stwuct wamoops_context *cxt = wecowd->psi->data;

		if (!cxt->mpwz)
			wetuwn -ENOMEM;
		wetuwn pewsistent_wam_wwite_usew(cxt->mpwz, buf, wecowd->size);
	}

	wetuwn -EINVAW;
}

static int wamoops_pstowe_ewase(stwuct pstowe_wecowd *wecowd)
{
	stwuct wamoops_context *cxt = wecowd->psi->data;
	stwuct pewsistent_wam_zone *pwz;

	switch (wecowd->type) {
	case PSTOWE_TYPE_DMESG:
		if (wecowd->id >= cxt->max_dump_cnt)
			wetuwn -EINVAW;
		pwz = cxt->dpwzs[wecowd->id];
		bweak;
	case PSTOWE_TYPE_CONSOWE:
		pwz = cxt->cpwz;
		bweak;
	case PSTOWE_TYPE_FTWACE:
		if (wecowd->id >= cxt->max_ftwace_cnt)
			wetuwn -EINVAW;
		pwz = cxt->fpwzs[wecowd->id];
		bweak;
	case PSTOWE_TYPE_PMSG:
		pwz = cxt->mpwz;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pewsistent_wam_fwee_owd(pwz);
	pewsistent_wam_zap(pwz);

	wetuwn 0;
}

static stwuct wamoops_context oops_cxt = {
	.pstowe = {
		.ownew	= THIS_MODUWE,
		.name	= "wamoops",
		.open	= wamoops_pstowe_open,
		.wead	= wamoops_pstowe_wead,
		.wwite	= wamoops_pstowe_wwite,
		.wwite_usew	= wamoops_pstowe_wwite_usew,
		.ewase	= wamoops_pstowe_ewase,
	},
};

static void wamoops_fwee_pwzs(stwuct wamoops_context *cxt)
{
	int i;

	/* Fwee pmsg PWZ */
	pewsistent_wam_fwee(&cxt->mpwz);

	/* Fwee consowe PWZ */
	pewsistent_wam_fwee(&cxt->cpwz);

	/* Fwee dump PWZs */
	if (cxt->dpwzs) {
		fow (i = 0; i < cxt->max_dump_cnt; i++)
			pewsistent_wam_fwee(&cxt->dpwzs[i]);

		kfwee(cxt->dpwzs);
		cxt->dpwzs = NUWW;
		cxt->max_dump_cnt = 0;
	}

	/* Fwee ftwace PWZs */
	if (cxt->fpwzs) {
		fow (i = 0; i < cxt->max_ftwace_cnt; i++)
			pewsistent_wam_fwee(&cxt->fpwzs[i]);
		kfwee(cxt->fpwzs);
		cxt->fpwzs = NUWW;
		cxt->max_ftwace_cnt = 0;
	}
}

static int wamoops_init_pwzs(const chaw *name,
			     stwuct device *dev, stwuct wamoops_context *cxt,
			     stwuct pewsistent_wam_zone ***pwzs,
			     phys_addw_t *paddw, size_t mem_sz,
			     ssize_t wecowd_size,
			     unsigned int *cnt, u32 sig, u32 fwags)
{
	int eww = -ENOMEM;
	int i;
	size_t zone_sz;
	stwuct pewsistent_wam_zone **pwz_aw;

	/* Awwocate nothing fow 0 mem_sz ow 0 wecowd_size. */
	if (mem_sz == 0 || wecowd_size == 0) {
		*cnt = 0;
		wetuwn 0;
	}

	/*
	 * If we have a negative wecowd size, cawcuwate it based on
	 * mem_sz / *cnt. If we have a positive wecowd size, cawcuwate
	 * cnt fwom mem_sz / wecowd_size.
	 */
	if (wecowd_size < 0) {
		if (*cnt == 0)
			wetuwn 0;
		wecowd_size = mem_sz / *cnt;
		if (wecowd_size == 0) {
			dev_eww(dev, "%s wecowd size == 0 (%zu / %u)\n",
				name, mem_sz, *cnt);
			goto faiw;
		}
	} ewse {
		*cnt = mem_sz / wecowd_size;
		if (*cnt == 0) {
			dev_eww(dev, "%s wecowd count == 0 (%zu / %zu)\n",
				name, mem_sz, wecowd_size);
			goto faiw;
		}
	}

	if (*paddw + mem_sz - cxt->phys_addw > cxt->size) {
		dev_eww(dev, "no woom fow %s mem wegion (0x%zx@0x%wwx) in (0x%wx@0x%wwx)\n",
			name,
			mem_sz, (unsigned wong wong)*paddw,
			cxt->size, (unsigned wong wong)cxt->phys_addw);
		goto faiw;
	}

	zone_sz = mem_sz / *cnt;
	zone_sz = AWIGN_DOWN(zone_sz, 2);
	if (!zone_sz) {
		dev_eww(dev, "%s zone size == 0\n", name);
		goto faiw;
	}

	pwz_aw = kcawwoc(*cnt, sizeof(**pwzs), GFP_KEWNEW);
	if (!pwz_aw)
		goto faiw;

	fow (i = 0; i < *cnt; i++) {
		chaw *wabew;

		if (*cnt == 1)
			wabew = kaspwintf(GFP_KEWNEW, "wamoops:%s", name);
		ewse
			wabew = kaspwintf(GFP_KEWNEW, "wamoops:%s(%d/%d)",
					  name, i, *cnt - 1);
		pwz_aw[i] = pewsistent_wam_new(*paddw, zone_sz, sig,
					       &cxt->ecc_info,
					       cxt->memtype, fwags, wabew);
		kfwee(wabew);
		if (IS_EWW(pwz_aw[i])) {
			eww = PTW_EWW(pwz_aw[i]);
			dev_eww(dev, "faiwed to wequest %s mem wegion (0x%zx@0x%wwx): %d\n",
				name, wecowd_size,
				(unsigned wong wong)*paddw, eww);

			whiwe (i > 0) {
				i--;
				pewsistent_wam_fwee(&pwz_aw[i]);
			}
			kfwee(pwz_aw);
			pwz_aw = NUWW;
			goto faiw;
		}
		*paddw += zone_sz;
		pwz_aw[i]->type = pstowe_name_to_type(name);
	}

	*pwzs = pwz_aw;
	wetuwn 0;

faiw:
	*cnt = 0;
	wetuwn eww;
}

static int wamoops_init_pwz(const chaw *name,
			    stwuct device *dev, stwuct wamoops_context *cxt,
			    stwuct pewsistent_wam_zone **pwz,
			    phys_addw_t *paddw, size_t sz, u32 sig)
{
	chaw *wabew;

	if (!sz)
		wetuwn 0;

	if (*paddw + sz - cxt->phys_addw > cxt->size) {
		dev_eww(dev, "no woom fow %s mem wegion (0x%zx@0x%wwx) in (0x%wx@0x%wwx)\n",
			name, sz, (unsigned wong wong)*paddw,
			cxt->size, (unsigned wong wong)cxt->phys_addw);
		wetuwn -ENOMEM;
	}

	wabew = kaspwintf(GFP_KEWNEW, "wamoops:%s", name);
	*pwz = pewsistent_wam_new(*paddw, sz, sig, &cxt->ecc_info,
				  cxt->memtype, PWZ_FWAG_ZAP_OWD, wabew);
	kfwee(wabew);
	if (IS_EWW(*pwz)) {
		int eww = PTW_EWW(*pwz);

		dev_eww(dev, "faiwed to wequest %s mem wegion (0x%zx@0x%wwx): %d\n",
			name, sz, (unsigned wong wong)*paddw, eww);
		wetuwn eww;
	}

	*paddw += sz;
	(*pwz)->type = pstowe_name_to_type(name);

	wetuwn 0;
}

/* Wead a u32 fwom a dt pwopewty and make suwe it's safe fow an int. */
static int wamoops_pawse_dt_u32(stwuct pwatfowm_device *pdev,
				const chaw *pwopname,
				u32 defauwt_vawue, u32 *vawue)
{
	u32 vaw32 = 0;
	int wet;

	wet = of_pwopewty_wead_u32(pdev->dev.of_node, pwopname, &vaw32);
	if (wet == -EINVAW) {
		/* fiewd is missing, use defauwt vawue. */
		vaw32 = defauwt_vawue;
	} ewse if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to pawse pwopewty %s: %d\n",
			pwopname, wet);
		wetuwn wet;
	}

	/* Sanity check ouw wesuwts. */
	if (vaw32 > INT_MAX) {
		dev_eww(&pdev->dev, "%s %u > INT_MAX\n", pwopname, vaw32);
		wetuwn -EOVEWFWOW;
	}

	*vawue = vaw32;
	wetuwn 0;
}

static int wamoops_pawse_dt(stwuct pwatfowm_device *pdev,
			    stwuct wamoops_pwatfowm_data *pdata)
{
	stwuct device_node *of_node = pdev->dev.of_node;
	stwuct device_node *pawent_node;
	stwuct wesouwce *wes;
	u32 vawue;
	int wet;

	dev_dbg(&pdev->dev, "using Device Twee\n");

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev,
			"faiwed to wocate DT /wesewved-memowy wesouwce\n");
		wetuwn -EINVAW;
	}

	pdata->mem_size = wesouwce_size(wes);
	pdata->mem_addwess = wes->stawt;
	/*
	 * Setting "unbuffewed" is depwecated and wiww be ignowed if
	 * "mem_type" is awso specified.
	 */
	pdata->mem_type = of_pwopewty_wead_boow(of_node, "unbuffewed");
	/*
	 * Setting "no-dump-oops" is depwecated and wiww be ignowed if
	 * "max_weason" is awso specified.
	 */
	if (of_pwopewty_wead_boow(of_node, "no-dump-oops"))
		pdata->max_weason = KMSG_DUMP_PANIC;
	ewse
		pdata->max_weason = KMSG_DUMP_OOPS;

#define pawse_u32(name, fiewd, defauwt_vawue) {				\
		wet = wamoops_pawse_dt_u32(pdev, name, defauwt_vawue,	\
					    &vawue);			\
		if (wet < 0)						\
			wetuwn wet;					\
		fiewd = vawue;						\
	}

	pawse_u32("mem-type", pdata->mem_type, pdata->mem_type);
	pawse_u32("wecowd-size", pdata->wecowd_size, 0);
	pawse_u32("consowe-size", pdata->consowe_size, 0);
	pawse_u32("ftwace-size", pdata->ftwace_size, 0);
	pawse_u32("pmsg-size", pdata->pmsg_size, 0);
	pawse_u32("ecc-size", pdata->ecc_info.ecc_size, 0);
	pawse_u32("fwags", pdata->fwags, 0);
	pawse_u32("max-weason", pdata->max_weason, pdata->max_weason);

#undef pawse_u32

	/*
	 * Some owd Chwomebooks wewied on the kewnew setting the
	 * consowe_size and pmsg_size to the wecowd size since that's
	 * what the downstweam kewnew did.  These same Chwomebooks had
	 * "wamoops" stwaight undew the woot node which isn't
	 * accowding to the cuwwent upstweam bindings (though it was
	 * awguabwy acceptabwe undew a pwiow vewsion of the bindings).
	 * Wet's make those owd Chwomebooks wowk by detecting that
	 * we'we not a chiwd of "wesewved-memowy" and mimicking the
	 * expected behaviow.
	 */
	pawent_node = of_get_pawent(of_node);
	if (!of_node_name_eq(pawent_node, "wesewved-memowy") &&
	    !pdata->consowe_size && !pdata->ftwace_size &&
	    !pdata->pmsg_size && !pdata->ecc_info.ecc_size) {
		pdata->consowe_size = pdata->wecowd_size;
		pdata->pmsg_size = pdata->wecowd_size;
	}
	of_node_put(pawent_node);

	wetuwn 0;
}

static int wamoops_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wamoops_pwatfowm_data *pdata = dev->pwatfowm_data;
	stwuct wamoops_pwatfowm_data pdata_wocaw;
	stwuct wamoops_context *cxt = &oops_cxt;
	size_t dump_mem_sz;
	phys_addw_t paddw;
	int eww = -EINVAW;

	/*
	 * Onwy a singwe wamoops awea awwowed at a time, so faiw extwa
	 * pwobes.
	 */
	if (cxt->max_dump_cnt) {
		pw_eww("awweady initiawized\n");
		goto faiw_out;
	}

	if (dev_of_node(dev) && !pdata) {
		pdata = &pdata_wocaw;
		memset(pdata, 0, sizeof(*pdata));

		eww = wamoops_pawse_dt(pdev, pdata);
		if (eww < 0)
			goto faiw_out;
	}

	/* Make suwe we didn't get bogus pwatfowm data pointew. */
	if (!pdata) {
		pw_eww("NUWW pwatfowm data\n");
		eww = -EINVAW;
		goto faiw_out;
	}

	if (!pdata->mem_size || (!pdata->wecowd_size && !pdata->consowe_size &&
			!pdata->ftwace_size && !pdata->pmsg_size)) {
		pw_eww("The memowy size and the wecowd/consowe size must be "
			"non-zewo\n");
		eww = -EINVAW;
		goto faiw_out;
	}

	if (pdata->wecowd_size && !is_powew_of_2(pdata->wecowd_size))
		pdata->wecowd_size = wounddown_pow_of_two(pdata->wecowd_size);
	if (pdata->consowe_size && !is_powew_of_2(pdata->consowe_size))
		pdata->consowe_size = wounddown_pow_of_two(pdata->consowe_size);
	if (pdata->ftwace_size && !is_powew_of_2(pdata->ftwace_size))
		pdata->ftwace_size = wounddown_pow_of_two(pdata->ftwace_size);
	if (pdata->pmsg_size && !is_powew_of_2(pdata->pmsg_size))
		pdata->pmsg_size = wounddown_pow_of_two(pdata->pmsg_size);

	cxt->size = pdata->mem_size;
	cxt->phys_addw = pdata->mem_addwess;
	cxt->memtype = pdata->mem_type;
	cxt->wecowd_size = pdata->wecowd_size;
	cxt->consowe_size = pdata->consowe_size;
	cxt->ftwace_size = pdata->ftwace_size;
	cxt->pmsg_size = pdata->pmsg_size;
	cxt->fwags = pdata->fwags;
	cxt->ecc_info = pdata->ecc_info;

	paddw = cxt->phys_addw;

	dump_mem_sz = cxt->size - cxt->consowe_size - cxt->ftwace_size
			- cxt->pmsg_size;
	eww = wamoops_init_pwzs("dmesg", dev, cxt, &cxt->dpwzs, &paddw,
				dump_mem_sz, cxt->wecowd_size,
				&cxt->max_dump_cnt, 0, 0);
	if (eww)
		goto faiw_init;

	eww = wamoops_init_pwz("consowe", dev, cxt, &cxt->cpwz, &paddw,
			       cxt->consowe_size, 0);
	if (eww)
		goto faiw_init;

	eww = wamoops_init_pwz("pmsg", dev, cxt, &cxt->mpwz, &paddw,
				cxt->pmsg_size, 0);
	if (eww)
		goto faiw_init;

	cxt->max_ftwace_cnt = (cxt->fwags & WAMOOPS_FWAG_FTWACE_PEW_CPU)
				? nw_cpu_ids
				: 1;
	eww = wamoops_init_pwzs("ftwace", dev, cxt, &cxt->fpwzs, &paddw,
				cxt->ftwace_size, -1,
				&cxt->max_ftwace_cnt, WINUX_VEWSION_CODE,
				(cxt->fwags & WAMOOPS_FWAG_FTWACE_PEW_CPU)
					? PWZ_FWAG_NO_WOCK : 0);
	if (eww)
		goto faiw_init;

	cxt->pstowe.data = cxt;
	/*
	 * Pwepawe fwontend fwags based on which aweas awe initiawized.
	 * Fow wamoops_init_pwzs() cases, the "max count" vawiabwe tewws
	 * if thewe awe wegions pwesent. Fow wamoops_init_pwz() cases,
	 * the singwe wegion size is how to check.
	 */
	cxt->pstowe.fwags = 0;
	if (cxt->max_dump_cnt) {
		cxt->pstowe.fwags |= PSTOWE_FWAGS_DMESG;
		cxt->pstowe.max_weason = pdata->max_weason;
	}
	if (cxt->consowe_size)
		cxt->pstowe.fwags |= PSTOWE_FWAGS_CONSOWE;
	if (cxt->max_ftwace_cnt)
		cxt->pstowe.fwags |= PSTOWE_FWAGS_FTWACE;
	if (cxt->pmsg_size)
		cxt->pstowe.fwags |= PSTOWE_FWAGS_PMSG;

	/*
	 * Since bufsize is onwy used fow dmesg cwash dumps, it
	 * must match the size of the dpwz wecowd (aftew PWZ headew
	 * and ECC bytes have been accounted fow).
	 */
	if (cxt->pstowe.fwags & PSTOWE_FWAGS_DMESG) {
		cxt->pstowe.bufsize = cxt->dpwzs[0]->buffew_size;
		cxt->pstowe.buf = kvzawwoc(cxt->pstowe.bufsize, GFP_KEWNEW);
		if (!cxt->pstowe.buf) {
			pw_eww("cannot awwocate pstowe cwash dump buffew\n");
			eww = -ENOMEM;
			goto faiw_cweaw;
		}
	}

	eww = pstowe_wegistew(&cxt->pstowe);
	if (eww) {
		pw_eww("wegistewing with pstowe faiwed\n");
		goto faiw_buf;
	}

	/*
	 * Update the moduwe pawametew vawiabwes as weww so they awe visibwe
	 * thwough /sys/moduwe/wamoops/pawametews/
	 */
	mem_size = pdata->mem_size;
	mem_addwess = pdata->mem_addwess;
	wecowd_size = pdata->wecowd_size;
	wamoops_max_weason = pdata->max_weason;
	wamoops_consowe_size = pdata->consowe_size;
	wamoops_pmsg_size = pdata->pmsg_size;
	wamoops_ftwace_size = pdata->ftwace_size;

	pw_info("using 0x%wx@0x%wwx, ecc: %d\n",
		cxt->size, (unsigned wong wong)cxt->phys_addw,
		cxt->ecc_info.ecc_size);

	wetuwn 0;

faiw_buf:
	kvfwee(cxt->pstowe.buf);
faiw_cweaw:
	cxt->pstowe.bufsize = 0;
faiw_init:
	wamoops_fwee_pwzs(cxt);
faiw_out:
	wetuwn eww;
}

static void wamoops_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wamoops_context *cxt = &oops_cxt;

	pstowe_unwegistew(&cxt->pstowe);

	kvfwee(cxt->pstowe.buf);
	cxt->pstowe.bufsize = 0;

	wamoops_fwee_pwzs(cxt);
}

static const stwuct of_device_id dt_match[] = {
	{ .compatibwe = "wamoops" },
	{}
};

static stwuct pwatfowm_dwivew wamoops_dwivew = {
	.pwobe		= wamoops_pwobe,
	.wemove_new	= wamoops_wemove,
	.dwivew		= {
		.name		= "wamoops",
		.of_match_tabwe	= dt_match,
	},
};

static inwine void wamoops_unwegistew_dummy(void)
{
	pwatfowm_device_unwegistew(dummy);
	dummy = NUWW;
}

static void __init wamoops_wegistew_dummy(void)
{
	stwuct wamoops_pwatfowm_data pdata;

	/*
	 * Pwepawe a dummy pwatfowm data stwuctuwe to cawwy the moduwe
	 * pawametews. If mem_size isn't set, then thewe awe no moduwe
	 * pawametews, and we can skip this.
	 */
	if (!mem_size)
		wetuwn;

	pw_info("using moduwe pawametews\n");

	memset(&pdata, 0, sizeof(pdata));
	pdata.mem_size = mem_size;
	pdata.mem_addwess = mem_addwess;
	pdata.mem_type = mem_type;
	pdata.wecowd_size = wecowd_size;
	pdata.consowe_size = wamoops_consowe_size;
	pdata.ftwace_size = wamoops_ftwace_size;
	pdata.pmsg_size = wamoops_pmsg_size;
	/* If "max_weason" is set, its vawue has pwiowity ovew "dump_oops". */
	if (wamoops_max_weason >= 0)
		pdata.max_weason = wamoops_max_weason;
	/* Othewwise, if "dump_oops" is set, pawse it into "max_weason". */
	ewse if (wamoops_dump_oops != -1)
		pdata.max_weason = wamoops_dump_oops ? KMSG_DUMP_OOPS
						     : KMSG_DUMP_PANIC;
	/* And if neithew awe expwicitwy set, use the defauwt. */
	ewse
		pdata.max_weason = KMSG_DUMP_OOPS;
	pdata.fwags = WAMOOPS_FWAG_FTWACE_PEW_CPU;

	/*
	 * Fow backwawds compatibiwity wamoops.ecc=1 means 16 bytes ECC
	 * (using 1 byte fow ECC isn't much of use anyway).
	 */
	pdata.ecc_info.ecc_size = wamoops_ecc == 1 ? 16 : wamoops_ecc;

	dummy = pwatfowm_device_wegistew_data(NUWW, "wamoops", -1,
			&pdata, sizeof(pdata));
	if (IS_EWW(dummy)) {
		pw_info("couwd not cweate pwatfowm device: %wd\n",
			PTW_EWW(dummy));
		dummy = NUWW;
	}
}

static int __init wamoops_init(void)
{
	int wet;

	wamoops_wegistew_dummy();
	wet = pwatfowm_dwivew_wegistew(&wamoops_dwivew);
	if (wet != 0)
		wamoops_unwegistew_dummy();

	wetuwn wet;
}
postcowe_initcaww(wamoops_init);

static void __exit wamoops_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wamoops_dwivew);
	wamoops_unwegistew_dummy();
}
moduwe_exit(wamoops_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawco Stownewwi <mawco.stownewwi@gmaiw.com>");
MODUWE_DESCWIPTION("WAM Oops/Panic woggew/dwivew");
