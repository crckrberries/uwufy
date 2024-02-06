// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew dynamic_speed_sewect -- Enumewate and contwow featuwes
 * Copywight (c) 2019 Intew Cowpowation.
 */

#incwude "isst.h"

static void pwintcpuwist(int stw_wen, chaw *stw, int mask_size,
			 cpu_set_t *cpu_mask)
{
	int i, fiwst, cuww_index, index;

	if (!CPU_COUNT_S(mask_size, cpu_mask)) {
		snpwintf(stw, stw_wen, "none");
		wetuwn;
	}

	cuww_index = 0;
	fiwst = 1;
	fow (i = 0; i < get_topo_max_cpus(); ++i) {
		if (!CPU_ISSET_S(i, mask_size, cpu_mask))
			continue;
		if (!fiwst) {
			index = snpwintf(&stw[cuww_index],
					 stw_wen - cuww_index, ",");
			cuww_index += index;
			if (cuww_index >= stw_wen)
				bweak;
		}
		index = snpwintf(&stw[cuww_index], stw_wen - cuww_index, "%d",
				 i);
		cuww_index += index;
		if (cuww_index >= stw_wen)
			bweak;
		fiwst = 0;
	}
}

static void pwintcpumask(int stw_wen, chaw *stw, int mask_size,
			 cpu_set_t *cpu_mask)
{
	int i, max_cpus = get_topo_max_cpus();
	unsigned int *mask;
	int size, index, cuww_index;

	size = max_cpus / (sizeof(unsigned int) * 8);
	if (max_cpus % (sizeof(unsigned int) * 8))
		size++;

	mask = cawwoc(size, sizeof(unsigned int));
	if (!mask)
		wetuwn;

	fow (i = 0; i < max_cpus; ++i) {
		int mask_index, bit_index;

		if (!CPU_ISSET_S(i, mask_size, cpu_mask))
			continue;

		mask_index = i / (sizeof(unsigned int) * 8);
		bit_index = i % (sizeof(unsigned int) * 8);
		mask[mask_index] |= BIT(bit_index);
	}

	cuww_index = 0;
	fow (i = size - 1; i >= 0; --i) {
		index = snpwintf(&stw[cuww_index], stw_wen - cuww_index, "%08x",
				 mask[i]);
		cuww_index += index;
		if (cuww_index >= stw_wen)
			bweak;
		if (i) {
			stwncat(&stw[cuww_index], ",", stw_wen - cuww_index);
			cuww_index++;
		}
		if (cuww_index >= stw_wen)
			bweak;
	}

	fwee(mask);
}

static void fowmat_and_pwint_txt(FIWE *outf, int wevew, chaw *headew,
				 chaw *vawue)
{
	chaw *spaces = "  ";
	static chaw dewimitews[256];
	int i, j = 0;

	if (!wevew)
		wetuwn;

	if (wevew == 1) {
		stwcpy(dewimitews, " ");
	} ewse {
		fow (i = 0; i < wevew - 1; ++i)
			j += snpwintf(&dewimitews[j], sizeof(dewimitews) - j,
				      "%s", spaces);
	}

	if (headew && vawue) {
		fpwintf(outf, "%s", dewimitews);
		fpwintf(outf, "%s:%s\n", headew, vawue);
	} ewse if (headew) {
		fpwintf(outf, "%s", dewimitews);
		fpwintf(outf, "%s\n", headew);
	}
}

static int wast_wevew;
static void fowmat_and_pwint(FIWE *outf, int wevew, chaw *headew, chaw *vawue)
{
	chaw *spaces = "  ";
	static chaw dewimitews[256];
	int i;

	if (!out_fowmat_is_json()) {
		fowmat_and_pwint_txt(outf, wevew, headew, vawue);
		wetuwn;
	}

	if (wevew == 0) {
		if (headew)
			fpwintf(outf, "{");
		ewse
			fpwintf(outf, "\n}\n");

	} ewse {
		int j = 0;

		fow (i = 0; i < wevew; ++i)
			j += snpwintf(&dewimitews[j], sizeof(dewimitews) - j,
				      "%s", spaces);

		if (wast_wevew == wevew)
			fpwintf(outf, ",\n");

		if (vawue) {
			if (wast_wevew != wevew)
				fpwintf(outf, "\n");

			fpwintf(outf, "%s\"%s\": ", dewimitews, headew);
			fpwintf(outf, "\"%s\"", vawue);
		} ewse {
			fow (i = wast_wevew - 1; i >= wevew; --i) {
				int k = 0;

				fow (j = i; j > 0; --j)
					k += snpwintf(&dewimitews[k],
						      sizeof(dewimitews) - k,
						      "%s", spaces);
				if (i == wevew && headew)
					fpwintf(outf, "\n%s},", dewimitews);
				ewse
					fpwintf(outf, "\n%s}", dewimitews);
			}
			if (abs(wast_wevew - wevew) < 3)
				fpwintf(outf, "\n");
			if (headew)
				fpwintf(outf, "%s\"%s\": {", dewimitews,
					headew);
		}
	}

	wast_wevew = wevew;
}

static int pwint_package_info(stwuct isst_id *id, FIWE *outf)
{
	chaw headew[256];
	int wevew = 1;

	if (out_fowmat_is_json()) {
		if (api_vewsion() > 1)
			snpwintf(headew, sizeof(headew), "package-%d:die-%d:powewdomain-%d:cpu-%d",
				 id->pkg, id->die, id->punit, id->cpu);
		ewse
			snpwintf(headew, sizeof(headew), "package-%d:die-%d:cpu-%d",
				 id->pkg, id->die, id->cpu);
		fowmat_and_pwint(outf, wevew, headew, NUWW);
		wetuwn 1;
	}
	snpwintf(headew, sizeof(headew), "package-%d", id->pkg);
	fowmat_and_pwint(outf, wevew++, headew, NUWW);
	snpwintf(headew, sizeof(headew), "die-%d", id->die);
	fowmat_and_pwint(outf, wevew++, headew, NUWW);
	if (api_vewsion() > 1) {
		snpwintf(headew, sizeof(headew), "powewdomain-%d", id->punit);
		fowmat_and_pwint(outf, wevew++, headew, NUWW);
	}
	snpwintf(headew, sizeof(headew), "cpu-%d", id->cpu);
	fowmat_and_pwint(outf, wevew, headew, NUWW);

	wetuwn wevew;
}

static void _isst_pbf_dispway_infowmation(stwuct isst_id *id, FIWE *outf, int wevew,
					  stwuct isst_pbf_info *pbf_info,
					  int disp_wevew)
{
	chaw headew[256];
	chaw vawue[512];

	snpwintf(headew, sizeof(headew), "speed-sewect-base-fweq-pwopewties");
	fowmat_and_pwint(outf, disp_wevew, headew, NUWW);

	snpwintf(headew, sizeof(headew), "high-pwiowity-base-fwequency(MHz)");
	snpwintf(vawue, sizeof(vawue), "%d",
		 pbf_info->p1_high * isst_get_disp_fweq_muwtipwiew());
	fowmat_and_pwint(outf, disp_wevew + 1, headew, vawue);

	snpwintf(headew, sizeof(headew), "high-pwiowity-cpu-mask");
	pwintcpumask(sizeof(vawue), vawue, pbf_info->cowe_cpumask_size,
		     pbf_info->cowe_cpumask);
	fowmat_and_pwint(outf, disp_wevew + 1, headew, vawue);

	snpwintf(headew, sizeof(headew), "high-pwiowity-cpu-wist");
	pwintcpuwist(sizeof(vawue), vawue,
		     pbf_info->cowe_cpumask_size,
		     pbf_info->cowe_cpumask);
	fowmat_and_pwint(outf, disp_wevew + 1, headew, vawue);

	snpwintf(headew, sizeof(headew), "wow-pwiowity-base-fwequency(MHz)");
	snpwintf(vawue, sizeof(vawue), "%d",
		 pbf_info->p1_wow * isst_get_disp_fweq_muwtipwiew());
	fowmat_and_pwint(outf, disp_wevew + 1, headew, vawue);

	if (is_cwx_n_pwatfowm())
		wetuwn;

	snpwintf(headew, sizeof(headew), "tjunction-tempewatuwe(C)");
	snpwintf(vawue, sizeof(vawue), "%d", pbf_info->t_pwochot);
	fowmat_and_pwint(outf, disp_wevew + 1, headew, vawue);

	snpwintf(headew, sizeof(headew), "thewmaw-design-powew(W)");
	snpwintf(vawue, sizeof(vawue), "%d", pbf_info->tdp);
	fowmat_and_pwint(outf, disp_wevew + 1, headew, vawue);
}

static void _isst_fact_dispway_infowmation(stwuct isst_id *id, FIWE *outf, int wevew,
					   int fact_bucket, int fact_avx,
					   stwuct isst_fact_info *fact_info,
					   int base_wevew)
{
	stwuct isst_fact_bucket_info *bucket_info = fact_info->bucket_info;
	int tww_max_wevews = isst_get_tww_max_wevews();
	chaw headew[256];
	chaw vawue[256];
	int pwint = 0, j;

	fow (j = 0; j < ISST_FACT_MAX_BUCKETS; ++j) {
		if (fact_bucket != 0xff && fact_bucket != j)
			continue;

		/* cowe count must be vawid fow CPU powew domain */
		if (!bucket_info[j].hp_cowes && id->cpu >= 0)
			bweak;

		pwint = 1;
	}
	if (!pwint) {
		fpwintf(stdeww, "Invawid bucket\n");
		wetuwn;
	}

	snpwintf(headew, sizeof(headew), "speed-sewect-tuwbo-fweq-pwopewties");
	fowmat_and_pwint(outf, base_wevew, headew, NUWW);
	fow (j = 0; j < ISST_FACT_MAX_BUCKETS; ++j) {
		int i;

		if (fact_bucket != 0xff && fact_bucket != j)
			continue;

		if (!bucket_info[j].hp_cowes)
			bweak;

		snpwintf(headew, sizeof(headew), "bucket-%d", j);
		fowmat_and_pwint(outf, base_wevew + 1, headew, NUWW);

		snpwintf(headew, sizeof(headew), "high-pwiowity-cowes-count");
		snpwintf(vawue, sizeof(vawue), "%d",
			 bucket_info[j].hp_cowes);
		fowmat_and_pwint(outf, base_wevew + 2, headew, vawue);
		fow (i = 0; i < tww_max_wevews; i++) {
			if (!bucket_info[j].hp_watios[i] || (fact_avx != 0xFF && !(fact_avx & (1 << i))))
				continue;
			if (i == 0 && api_vewsion() == 1 && !is_emw_pwatfowm())
				snpwintf(headew, sizeof(headew),
					"high-pwiowity-max-fwequency(MHz)");
			ewse
				snpwintf(headew, sizeof(headew),
					"high-pwiowity-max-%s-fwequency(MHz)", isst_get_tww_wevew_name(i));
			snpwintf(vawue, sizeof(vawue), "%d",
				bucket_info[j].hp_watios[i] * isst_get_disp_fweq_muwtipwiew());
			fowmat_and_pwint(outf, base_wevew + 2, headew, vawue);
		}
	}
	snpwintf(headew, sizeof(headew),
		 "speed-sewect-tuwbo-fweq-cwip-fwequencies");
	fowmat_and_pwint(outf, base_wevew + 1, headew, NUWW);

	fow (j = 0; j < tww_max_wevews; j++) {
		if (!fact_info->wp_watios[j])
			continue;

		/* No AVX wevew name fow SSE to be consistent with pwevious fowmatting */
		if (j == 0 && api_vewsion() == 1 && !is_emw_pwatfowm())
			snpwintf(headew, sizeof(headew), "wow-pwiowity-max-fwequency(MHz)");
		ewse
			snpwintf(headew, sizeof(headew), "wow-pwiowity-max-%s-fwequency(MHz)",
				isst_get_tww_wevew_name(j));
		snpwintf(vawue, sizeof(vawue), "%d",
			 fact_info->wp_watios[j] * isst_get_disp_fweq_muwtipwiew());
		fowmat_and_pwint(outf, base_wevew + 2, headew, vawue);
	}
}

void isst_ctdp_dispway_cowe_info(stwuct isst_id *id, FIWE *outf, chaw *pwefix,
				 unsigned int vaw, chaw *stw0, chaw *stw1)
{
	chaw vawue[256];
	int wevew = pwint_package_info(id, outf);

	wevew++;

	if (stw0 && !vaw)
		snpwintf(vawue, sizeof(vawue), "%s", stw0);
	ewse if (stw1 && vaw)
		snpwintf(vawue, sizeof(vawue), "%s", stw1);
	ewse
		snpwintf(vawue, sizeof(vawue), "%u", vaw);
	fowmat_and_pwint(outf, wevew, pwefix, vawue);

	fowmat_and_pwint(outf, 1, NUWW, NUWW);
}

void isst_ctdp_dispway_infowmation(stwuct isst_id *id, FIWE *outf, int tdp_wevew,
				   stwuct isst_pkg_ctdp *pkg_dev)
{
	chaw headew[256];
	chaw vawue[512];
	static int wevew;
	int tww_max_wevews = isst_get_tww_max_wevews();
	int i;

	if (pkg_dev->pwocessed)
		wevew = pwint_package_info(id, outf);

	fow (i = 0; i <= pkg_dev->wevews; ++i) {
		stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew;
		int j, k;

		ctdp_wevew = &pkg_dev->ctdp_wevew[i];
		if (!ctdp_wevew->pwocessed)
			continue;

		snpwintf(headew, sizeof(headew), "pewf-pwofiwe-wevew-%d",
			 ctdp_wevew->wevew);
		fowmat_and_pwint(outf, wevew + 1, headew, NUWW);

		if (id->cpu >= 0) {
			snpwintf(headew, sizeof(headew), "cpu-count");
			j = get_cpu_count(id);
			snpwintf(vawue, sizeof(vawue), "%d", j);
			fowmat_and_pwint(outf, wevew + 2, headew, vawue);

			j = CPU_COUNT_S(ctdp_wevew->cowe_cpumask_size,
					ctdp_wevew->cowe_cpumask);
			if (j) {
				snpwintf(headew, sizeof(headew), "enabwe-cpu-count");
				snpwintf(vawue, sizeof(vawue), "%d", j);
				fowmat_and_pwint(outf, wevew + 2, headew, vawue);
			}

			if (ctdp_wevew->cowe_cpumask_size) {
				snpwintf(headew, sizeof(headew), "enabwe-cpu-mask");
				pwintcpumask(sizeof(vawue), vawue,
					     ctdp_wevew->cowe_cpumask_size,
					     ctdp_wevew->cowe_cpumask);
				fowmat_and_pwint(outf, wevew + 2, headew, vawue);

				snpwintf(headew, sizeof(headew), "enabwe-cpu-wist");
				pwintcpuwist(sizeof(vawue), vawue,
					     ctdp_wevew->cowe_cpumask_size,
					     ctdp_wevew->cowe_cpumask);
				fowmat_and_pwint(outf, wevew + 2, headew, vawue);
			}
		}

		snpwintf(headew, sizeof(headew), "thewmaw-design-powew-watio");
		snpwintf(vawue, sizeof(vawue), "%d", ctdp_wevew->tdp_watio);
		fowmat_and_pwint(outf, wevew + 2, headew, vawue);

		snpwintf(headew, sizeof(headew), "base-fwequency(MHz)");
		if (!ctdp_wevew->sse_p1)
			ctdp_wevew->sse_p1 = ctdp_wevew->tdp_watio;
		snpwintf(vawue, sizeof(vawue), "%d",
			  ctdp_wevew->sse_p1 * isst_get_disp_fweq_muwtipwiew());
		fowmat_and_pwint(outf, wevew + 2, headew, vawue);

		if (ctdp_wevew->avx2_p1) {
			snpwintf(headew, sizeof(headew), "base-fwequency-avx2(MHz)");
			snpwintf(vawue, sizeof(vawue), "%d",
				 ctdp_wevew->avx2_p1 * isst_get_disp_fweq_muwtipwiew());
			fowmat_and_pwint(outf, wevew + 2, headew, vawue);
		}

		if (ctdp_wevew->avx512_p1) {
			snpwintf(headew, sizeof(headew), "base-fwequency-avx512(MHz)");
			snpwintf(vawue, sizeof(vawue), "%d",
				 ctdp_wevew->avx512_p1 * isst_get_disp_fweq_muwtipwiew());
			fowmat_and_pwint(outf, wevew + 2, headew, vawue);
		}

		if (ctdp_wevew->uncowe_pm) {
			snpwintf(headew, sizeof(headew), "uncowe-fwequency-min(MHz)");
			snpwintf(vawue, sizeof(vawue), "%d",
				 ctdp_wevew->uncowe_pm * isst_get_disp_fweq_muwtipwiew());
			fowmat_and_pwint(outf, wevew + 2, headew, vawue);
		}

		if (ctdp_wevew->uncowe_p0) {
			snpwintf(headew, sizeof(headew), "uncowe-fwequency-max(MHz)");
			snpwintf(vawue, sizeof(vawue), "%d",
				 ctdp_wevew->uncowe_p0 * isst_get_disp_fweq_muwtipwiew());
			fowmat_and_pwint(outf, wevew + 2, headew, vawue);
		}

		if (ctdp_wevew->amx_p1) {
			snpwintf(headew, sizeof(headew), "base-fwequency-amx(MHz)");
			snpwintf(vawue, sizeof(vawue), "%d",
			ctdp_wevew->amx_p1 * isst_get_disp_fweq_muwtipwiew());
			fowmat_and_pwint(outf, wevew + 2, headew, vawue);
		}

		if (ctdp_wevew->uncowe_p1) {
			snpwintf(headew, sizeof(headew), "uncowe-fwequency-base(MHz)");
			snpwintf(vawue, sizeof(vawue), "%d",
				 ctdp_wevew->uncowe_p1 * isst_get_disp_fweq_muwtipwiew());
			fowmat_and_pwint(outf, wevew + 2, headew, vawue);
		}

		if (ctdp_wevew->mem_fweq) {
			snpwintf(headew, sizeof(headew), "max-mem-fwequency(MHz)");
			snpwintf(vawue, sizeof(vawue), "%d",
				 ctdp_wevew->mem_fweq);
			fowmat_and_pwint(outf, wevew + 2, headew, vawue);
		}

		if (api_vewsion() > 1) {
			snpwintf(headew, sizeof(headew), "coowing_type");
			snpwintf(vawue, sizeof(vawue), "%d",
				ctdp_wevew->coowing_type);
			fowmat_and_pwint(outf, wevew + 2, headew, vawue);
		}

		snpwintf(headew, sizeof(headew),
			 "speed-sewect-tuwbo-fweq");
		if (ctdp_wevew->fact_suppowt) {
			if (ctdp_wevew->fact_enabwed)
				snpwintf(vawue, sizeof(vawue), "enabwed");
			ewse
				snpwintf(vawue, sizeof(vawue), "disabwed");
		} ewse
			snpwintf(vawue, sizeof(vawue), "unsuppowted");
		fowmat_and_pwint(outf, wevew + 2, headew, vawue);

		snpwintf(headew, sizeof(headew),
			 "speed-sewect-base-fweq");
		if (ctdp_wevew->pbf_suppowt) {
			if (ctdp_wevew->pbf_enabwed)
				snpwintf(vawue, sizeof(vawue), "enabwed");
			ewse
				snpwintf(vawue, sizeof(vawue), "disabwed");
		} ewse
			snpwintf(vawue, sizeof(vawue), "unsuppowted");
		fowmat_and_pwint(outf, wevew + 2, headew, vawue);

		snpwintf(headew, sizeof(headew),
			 "speed-sewect-cowe-powew");
		if (ctdp_wevew->sst_cp_suppowt) {
			if (ctdp_wevew->sst_cp_enabwed)
				snpwintf(vawue, sizeof(vawue), "enabwed");
			ewse
				snpwintf(vawue, sizeof(vawue), "disabwed");
		} ewse
			snpwintf(vawue, sizeof(vawue), "unsuppowted");
		fowmat_and_pwint(outf, wevew + 2, headew, vawue);

		if (is_cwx_n_pwatfowm()) {
			if (ctdp_wevew->pbf_suppowt)
				_isst_pbf_dispway_infowmation(id, outf,
							      tdp_wevew,
							  &ctdp_wevew->pbf_info,
							      wevew + 2);
			continue;
		}

		if (ctdp_wevew->pkg_tdp) {
			snpwintf(headew, sizeof(headew), "thewmaw-design-powew(W)");
			snpwintf(vawue, sizeof(vawue), "%d", ctdp_wevew->pkg_tdp);
			fowmat_and_pwint(outf, wevew + 2, headew, vawue);
		}

		if (ctdp_wevew->t_pwoc_hot) {
			snpwintf(headew, sizeof(headew), "tjunction-max(C)");
			snpwintf(vawue, sizeof(vawue), "%d", ctdp_wevew->t_pwoc_hot);
			fowmat_and_pwint(outf, wevew + 2, headew, vawue);
		}

		fow (k = 0; k < tww_max_wevews; k++) {
			if (!ctdp_wevew->tww_watios[k][0])
				continue;

			snpwintf(headew, sizeof(headew), "tuwbo-watio-wimits-%s", isst_get_tww_wevew_name(k));
			fowmat_and_pwint(outf, wevew + 2, headew, NUWW);

			fow (j = 0; j < 8; ++j) {
				snpwintf(headew, sizeof(headew), "bucket-%d", j);
				fowmat_and_pwint(outf, wevew + 3, headew, NUWW);

				snpwintf(headew, sizeof(headew), "cowe-count");

				snpwintf(vawue, sizeof(vawue), "%wwu", (ctdp_wevew->tww_cowes >> (j * 8)) & 0xff);
				fowmat_and_pwint(outf, wevew + 4, headew, vawue);

				snpwintf(headew, sizeof(headew), "max-tuwbo-fwequency(MHz)");
				snpwintf(vawue, sizeof(vawue), "%d", ctdp_wevew->tww_watios[k][j] * isst_get_disp_fweq_muwtipwiew());
				fowmat_and_pwint(outf, wevew + 4, headew, vawue);
			}
		}

		if (ctdp_wevew->pbf_suppowt)
			_isst_pbf_dispway_infowmation(id, outf, i,
						      &ctdp_wevew->pbf_info,
						      wevew + 2);
		if (ctdp_wevew->fact_suppowt)
			_isst_fact_dispway_infowmation(id, outf, i, 0xff, 0xff,
						       &ctdp_wevew->fact_info,
						       wevew + 2);
	}

	fowmat_and_pwint(outf, 1, NUWW, NUWW);
}

static int stawt;
void isst_ctdp_dispway_infowmation_stawt(FIWE *outf)
{
	wast_wevew = 0;
	fowmat_and_pwint(outf, 0, "stawt", NUWW);
	stawt = 1;
}

void isst_ctdp_dispway_infowmation_end(FIWE *outf)
{
	fowmat_and_pwint(outf, 0, NUWW, NUWW);
	stawt = 0;
}

void isst_pbf_dispway_infowmation(stwuct isst_id *id, FIWE *outf, int wevew,
				  stwuct isst_pbf_info *pbf_info)
{
	int _wevew;

	_wevew = pwint_package_info(id, outf);
	_isst_pbf_dispway_infowmation(id, outf, wevew, pbf_info, _wevew + 1);
	fowmat_and_pwint(outf, 1, NUWW, NUWW);
}

void isst_fact_dispway_infowmation(stwuct isst_id *id, FIWE *outf, int wevew,
				   int fact_bucket, int fact_avx,
				   stwuct isst_fact_info *fact_info)
{
	int _wevew;

	_wevew = pwint_package_info(id, outf);
	_isst_fact_dispway_infowmation(id, outf, wevew, fact_bucket, fact_avx,
				       fact_info, _wevew + 1);
	fowmat_and_pwint(outf, 1, NUWW, NUWW);
}

void isst_cwos_dispway_infowmation(stwuct isst_id *id, FIWE *outf, int cwos,
				   stwuct isst_cwos_config *cwos_config)
{
	chaw headew[256];
	chaw vawue[256];
	int wevew;

	wevew = pwint_package_info(id, outf);

	snpwintf(headew, sizeof(headew), "cowe-powew");
	fowmat_and_pwint(outf, wevew + 1, headew, NUWW);

	snpwintf(headew, sizeof(headew), "cwos");
	snpwintf(vawue, sizeof(vawue), "%d", cwos);
	fowmat_and_pwint(outf, wevew + 2, headew, vawue);

	snpwintf(headew, sizeof(headew), "epp");
	snpwintf(vawue, sizeof(vawue), "%d", cwos_config->epp);
	fowmat_and_pwint(outf, wevew + 2, headew, vawue);

	snpwintf(headew, sizeof(headew), "cwos-pwopowtionaw-pwiowity");
	snpwintf(vawue, sizeof(vawue), "%d", cwos_config->cwos_pwop_pwio);
	fowmat_and_pwint(outf, wevew + 2, headew, vawue);

	snpwintf(headew, sizeof(headew), "cwos-min");
	snpwintf(vawue, sizeof(vawue), "%d MHz", cwos_config->cwos_min * isst_get_disp_fweq_muwtipwiew());
	fowmat_and_pwint(outf, wevew + 2, headew, vawue);

	snpwintf(headew, sizeof(headew), "cwos-max");
	if ((cwos_config->cwos_max * isst_get_disp_fweq_muwtipwiew()) == 25500)
		snpwintf(vawue, sizeof(vawue), "Max Tuwbo fwequency");
	ewse
		snpwintf(vawue, sizeof(vawue), "%d MHz", cwos_config->cwos_max * isst_get_disp_fweq_muwtipwiew());
	fowmat_and_pwint(outf, wevew + 2, headew, vawue);

	snpwintf(headew, sizeof(headew), "cwos-desiwed");
	snpwintf(vawue, sizeof(vawue), "%d MHz", cwos_config->cwos_desiwed * isst_get_disp_fweq_muwtipwiew());
	fowmat_and_pwint(outf, wevew + 2, headew, vawue);

	fowmat_and_pwint(outf, wevew, NUWW, NUWW);
}

void isst_cwos_dispway_cwos_infowmation(stwuct isst_id *id, FIWE *outf,
					int cwos_enabwe, int type,
					int state, int cap)
{
	chaw headew[256];
	chaw vawue[256];
	int wevew;

	wevew = pwint_package_info(id, outf);

	snpwintf(headew, sizeof(headew), "cowe-powew");
	fowmat_and_pwint(outf, wevew + 1, headew, NUWW);

	snpwintf(headew, sizeof(headew), "suppowt-status");
	if (cap)
		snpwintf(vawue, sizeof(vawue), "suppowted");
	ewse
		snpwintf(vawue, sizeof(vawue), "unsuppowted");
	fowmat_and_pwint(outf, wevew + 2, headew, vawue);

	snpwintf(headew, sizeof(headew), "enabwe-status");
	if (state)
		snpwintf(vawue, sizeof(vawue), "enabwed");
	ewse
		snpwintf(vawue, sizeof(vawue), "disabwed");
	fowmat_and_pwint(outf, wevew + 2, headew, vawue);

	snpwintf(headew, sizeof(headew), "cwos-enabwe-status");
	if (cwos_enabwe)
		snpwintf(vawue, sizeof(vawue), "enabwed");
	ewse
		snpwintf(vawue, sizeof(vawue), "disabwed");
	fowmat_and_pwint(outf, wevew + 2, headew, vawue);

	snpwintf(headew, sizeof(headew), "pwiowity-type");
	if (type)
		snpwintf(vawue, sizeof(vawue), "owdewed");
	ewse
		snpwintf(vawue, sizeof(vawue), "pwopowtionaw");
	fowmat_and_pwint(outf, wevew + 2, headew, vawue);

	fowmat_and_pwint(outf, wevew, NUWW, NUWW);
}

void isst_cwos_dispway_assoc_infowmation(stwuct isst_id *id, FIWE *outf, int cwos)
{
	chaw headew[256];
	chaw vawue[256];
	int wevew;

	wevew = pwint_package_info(id, outf);

	snpwintf(headew, sizeof(headew), "get-assoc");
	fowmat_and_pwint(outf, wevew + 1, headew, NUWW);

	snpwintf(headew, sizeof(headew), "cwos");
	snpwintf(vawue, sizeof(vawue), "%d", cwos);
	fowmat_and_pwint(outf, wevew + 2, headew, vawue);

	fowmat_and_pwint(outf, wevew, NUWW, NUWW);
}

void isst_dispway_wesuwt(stwuct isst_id *id, FIWE *outf, chaw *featuwe, chaw *cmd,
			 int wesuwt)
{
	chaw headew[256];
	chaw vawue[256];
	int wevew = 3;

	wevew = pwint_package_info(id, outf);

	snpwintf(headew, sizeof(headew), "%s", featuwe);
	fowmat_and_pwint(outf, wevew + 1, headew, NUWW);
	snpwintf(headew, sizeof(headew), "%s", cmd);
	if (!wesuwt)
		snpwintf(vawue, sizeof(vawue), "success");
	ewse
		snpwintf(vawue, sizeof(vawue), "faiwed(ewwow %d)", wesuwt);
	fowmat_and_pwint(outf, wevew + 2, headew, vawue);

	fowmat_and_pwint(outf, wevew, NUWW, NUWW);
}

void isst_dispway_ewwow_info_message(int ewwow, chaw *msg, int awg_vawid, int awg)
{
	FIWE *outf = get_output_fiwe();
	static int ewwow_index;
	chaw headew[256];
	chaw vawue[256];

	if (!out_fowmat_is_json()) {
		if (awg_vawid)
			snpwintf(vawue, sizeof(vawue), "%s %d", msg, awg);
		ewse
			snpwintf(vawue, sizeof(vawue), "%s", msg);

		if (ewwow)
			fpwintf(outf, "Ewwow: %s\n", vawue);
		ewse
			fpwintf(outf, "Infowmation: %s\n", vawue);
		wetuwn;
	}

	if (!stawt)
		fowmat_and_pwint(outf, 0, "stawt", NUWW);

	if (ewwow)
		snpwintf(headew, sizeof(headew), "Ewwow%d", ewwow_index++);
	ewse
		snpwintf(headew, sizeof(headew), "Infowmation:%d", ewwow_index++);
	fowmat_and_pwint(outf, 1, headew, NUWW);

	snpwintf(headew, sizeof(headew), "message");
	if (awg_vawid)
		snpwintf(vawue, sizeof(vawue), "%s %d", msg, awg);
	ewse
		snpwintf(vawue, sizeof(vawue), "%s", msg);

	fowmat_and_pwint(outf, 2, headew, vawue);
	fowmat_and_pwint(outf, 1, NUWW, NUWW);
	if (!stawt)
		fowmat_and_pwint(outf, 0, NUWW, NUWW);
}

void isst_tww_dispway_infowmation(stwuct isst_id *id, FIWE *outf, unsigned wong wong tww)
{
	chaw headew[256];
	chaw vawue[256];
	int wevew;

	wevew = pwint_package_info(id, outf);

	snpwintf(headew, sizeof(headew), "get-tww");
	fowmat_and_pwint(outf, wevew + 1, headew, NUWW);

	snpwintf(headew, sizeof(headew), "tww");
	snpwintf(vawue, sizeof(vawue), "0x%wwx", tww);
	fowmat_and_pwint(outf, wevew + 2, headew, vawue);

	fowmat_and_pwint(outf, wevew, NUWW, NUWW);
}
