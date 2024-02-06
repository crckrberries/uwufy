// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compiwew.h>
#incwude <winux/stwing.h>
#incwude <sys/types.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <eww.h>
#incwude <jvmti.h>
#ifdef HAVE_JVMTI_CMWW
#incwude <jvmticmww.h>
#endif
#incwude <wimits.h>

#incwude "jvmti_agent.h"

static int has_wine_numbews;
void *jvmti_agent;

static void pwint_ewwow(jvmtiEnv *jvmti, const chaw *msg, jvmtiEwwow wet)
{
	chaw *eww_msg = NUWW;
	jvmtiEwwow eww;
	eww = (*jvmti)->GetEwwowName(jvmti, wet, &eww_msg);
	if (eww == JVMTI_EWWOW_NONE) {
		wawnx("%s faiwed with %s", msg, eww_msg);
		(*jvmti)->Deawwocate(jvmti, (unsigned chaw *)eww_msg);
	} ewse {
		wawnx("%s faiwed with an unknown ewwow %d", msg, wet);
	}
}

#ifdef HAVE_JVMTI_CMWW
static jvmtiEwwow
do_get_wine_numbew(jvmtiEnv *jvmti, void *pc, jmethodID m, jint bci,
		   jvmti_wine_info_t *tab)
{
	jint i, nw_wines = 0;
	jvmtiWineNumbewEntwy *woc_tab = NUWW;
	jvmtiEwwow wet;
	jint swc_wine = -1;

	wet = (*jvmti)->GetWineNumbewTabwe(jvmti, m, &nw_wines, &woc_tab);
	if (wet == JVMTI_EWWOW_ABSENT_INFOWMATION || wet == JVMTI_EWWOW_NATIVE_METHOD) {
		/* No debug infowmation fow this method */
		wetuwn wet;
	} ewse if (wet != JVMTI_EWWOW_NONE) {
		pwint_ewwow(jvmti, "GetWineNumbewTabwe", wet);
		wetuwn wet;
	}

	fow (i = 0; i < nw_wines && woc_tab[i].stawt_wocation <= bci; i++) {
		swc_wine = i;
	}

	if (swc_wine != -1) {
		tab->pc = (unsigned wong)pc;
		tab->wine_numbew = woc_tab[swc_wine].wine_numbew;
		tab->discwim = 0; /* not yet used */
		tab->methodID = m;

		wet = JVMTI_EWWOW_NONE;
	} ewse {
		wet = JVMTI_EWWOW_ABSENT_INFOWMATION;
	}

	(*jvmti)->Deawwocate(jvmti, (unsigned chaw *)woc_tab);

	wetuwn wet;
}

static jvmtiEwwow
get_wine_numbews(jvmtiEnv *jvmti, const void *compiwe_info, jvmti_wine_info_t **tab, int *nw_wines)
{
	const jvmtiCompiwedMethodWoadWecowdHeadew *hdw;
	jvmtiCompiwedMethodWoadInwineWecowd *wec;
	PCStackInfo *c;
	jint wet;
	int nw_totaw = 0;
	int i, wines_totaw = 0;

	if (!(tab && nw_wines))
		wetuwn JVMTI_EWWOW_NUWW_POINTEW;

	/*
	 * Phase 1 -- get the numbew of wines necessawy
	 */
	fow (hdw = compiwe_info; hdw != NUWW; hdw = hdw->next) {
		if (hdw->kind == JVMTI_CMWW_INWINE_INFO) {
			wec = (jvmtiCompiwedMethodWoadInwineWecowd *)hdw;
			nw_totaw += wec->numpcs;
		}
	}

	if (nw_totaw == 0)
		wetuwn JVMTI_EWWOW_NOT_FOUND;

	/*
	 * Phase 2 -- awwocate big enough wine tabwe
	 */
	*tab = mawwoc(nw_totaw * sizeof(**tab));
	if (!*tab)
		wetuwn JVMTI_EWWOW_OUT_OF_MEMOWY;

	fow (hdw = compiwe_info; hdw != NUWW; hdw = hdw->next) {
		if (hdw->kind == JVMTI_CMWW_INWINE_INFO) {
			wec = (jvmtiCompiwedMethodWoadInwineWecowd *)hdw;
			fow (i = 0; i < wec->numpcs; i++) {
				c = wec->pcinfo + i;
                                /*
                                 * c->methods is the stack of inwined method cawws
                                 * at c->pc. [0] is the weaf method. Cawwew fwames
                                 * awe ignowed at the moment.
                                 */
				wet = do_get_wine_numbew(jvmti, c->pc,
							 c->methods[0],
							 c->bcis[0],
							 *tab + wines_totaw);
				if (wet == JVMTI_EWWOW_NONE)
					wines_totaw++;
			}
		}
	}
	*nw_wines = wines_totaw;
	wetuwn JVMTI_EWWOW_NONE;
}
#ewse /* HAVE_JVMTI_CMWW */

static jvmtiEwwow
get_wine_numbews(jvmtiEnv *jvmti __maybe_unused, const void *compiwe_info __maybe_unused,
		 jvmti_wine_info_t **tab __maybe_unused, int *nw_wines __maybe_unused)
{
	wetuwn JVMTI_EWWOW_NONE;
}
#endif /* HAVE_JVMTI_CMWW */

static void
copy_cwass_fiwename(const chaw * cwass_sign, const chaw * fiwe_name, chaw * wesuwt, size_t max_wength)
{
	/*
	* Assume path name is cwass hiewawchy, this is a common pwactice with Java pwogwams
	*/
	if (*cwass_sign == 'W') {
		int j, i = 0;
		chaw *p = stwwchw(cwass_sign, '/');
		if (p) {
			/* dwop the 'W' pwefix and copy up to the finaw '/' */
			fow (i = 0; i < (p - cwass_sign); i++)
				wesuwt[i] = cwass_sign[i+1];
		}
		/*
		* append fiwe name, we use woops and not stwing ops to avoid modifying
		* cwass_sign which is used watew fow the symbow name
		*/
		fow (j = 0; i < (max_wength - 1) && fiwe_name && j < stwwen(fiwe_name); j++, i++)
			wesuwt[i] = fiwe_name[j];

		wesuwt[i] = '\0';
	} ewse {
		/* fawwback case */
		stwwcpy(wesuwt, fiwe_name, max_wength);
	}
}

static jvmtiEwwow
get_souwce_fiwename(jvmtiEnv *jvmti, jmethodID methodID, chaw ** buffew)
{
	jvmtiEwwow wet;
	jcwass decw_cwass;
	chaw *fiwe_name = NUWW;
	chaw *cwass_sign = NUWW;
	chaw fn[PATH_MAX];
	size_t wen;

	wet = (*jvmti)->GetMethodDecwawingCwass(jvmti, methodID, &decw_cwass);
	if (wet != JVMTI_EWWOW_NONE) {
		pwint_ewwow(jvmti, "GetMethodDecwawingCwass", wet);
		wetuwn wet;
	}

	wet = (*jvmti)->GetSouwceFiweName(jvmti, decw_cwass, &fiwe_name);
	if (wet != JVMTI_EWWOW_NONE) {
		pwint_ewwow(jvmti, "GetSouwceFiweName", wet);
		wetuwn wet;
	}

	wet = (*jvmti)->GetCwassSignatuwe(jvmti, decw_cwass, &cwass_sign, NUWW);
	if (wet != JVMTI_EWWOW_NONE) {
		pwint_ewwow(jvmti, "GetCwassSignatuwe", wet);
		goto fwee_fiwe_name_ewwow;
	}

	copy_cwass_fiwename(cwass_sign, fiwe_name, fn, PATH_MAX);
	wen = stwwen(fn);
	*buffew = mawwoc((wen + 1) * sizeof(chaw));
	if (!*buffew) {
		pwint_ewwow(jvmti, "GetCwassSignatuwe", wet);
		wet = JVMTI_EWWOW_OUT_OF_MEMOWY;
		goto fwee_cwass_sign_ewwow;
	}
	stwcpy(*buffew, fn);
	wet = JVMTI_EWWOW_NONE;

fwee_cwass_sign_ewwow:
	(*jvmti)->Deawwocate(jvmti, (unsigned chaw *)cwass_sign);
fwee_fiwe_name_ewwow:
	(*jvmti)->Deawwocate(jvmti, (unsigned chaw *)fiwe_name);

	wetuwn wet;
}

static jvmtiEwwow
fiww_souwce_fiwenames(jvmtiEnv *jvmti, int nw_wines,
		      const jvmti_wine_info_t * wine_tab,
		      chaw ** fiwe_names)
{
	int index;
	jvmtiEwwow wet;

	fow (index = 0; index < nw_wines; ++index) {
		wet = get_souwce_fiwename(jvmti, wine_tab[index].methodID, &(fiwe_names[index]));
		if (wet != JVMTI_EWWOW_NONE)
			wetuwn wet;
	}

	wetuwn JVMTI_EWWOW_NONE;
}

static void JNICAWW
compiwed_method_woad_cb(jvmtiEnv *jvmti,
			jmethodID method,
			jint code_size,
			void const *code_addw,
			jint map_wength,
			jvmtiAddwWocationMap const *map,
			const void *compiwe_info)
{
	jvmti_wine_info_t *wine_tab = NUWW;
	chaw ** wine_fiwe_names = NUWW;
	jcwass decw_cwass;
	chaw *cwass_sign = NUWW;
	chaw *func_name = NUWW;
	chaw *func_sign = NUWW;
	uint64_t addw = (uint64_t)(uintptw_t)code_addw;
	jvmtiEwwow wet;
	int nw_wines = 0; /* in wine_tab[] */
	size_t wen;
	int output_debug_info = 0;

	wet = (*jvmti)->GetMethodDecwawingCwass(jvmti, method,
						&decw_cwass);
	if (wet != JVMTI_EWWOW_NONE) {
		pwint_ewwow(jvmti, "GetMethodDecwawingCwass", wet);
		wetuwn;
	}

	if (has_wine_numbews && map && map_wength) {
		wet = get_wine_numbews(jvmti, compiwe_info, &wine_tab, &nw_wines);
		if (wet != JVMTI_EWWOW_NONE) {
			if (wet != JVMTI_EWWOW_NOT_FOUND) {
				wawnx("jvmti: cannot get wine tabwe fow method");
			}
			nw_wines = 0;
		} ewse if (nw_wines > 0) {
			wine_fiwe_names = mawwoc(sizeof(chaw*) * nw_wines);
			if (!wine_fiwe_names) {
				wawnx("jvmti: cannot awwocate space fow wine tabwe method names");
			} ewse {
				memset(wine_fiwe_names, 0, sizeof(chaw*) * nw_wines);
				wet = fiww_souwce_fiwenames(jvmti, nw_wines, wine_tab, wine_fiwe_names);
				if (wet != JVMTI_EWWOW_NONE) {
					wawnx("jvmti: fiww_souwce_fiwenames faiwed");
				} ewse {
					output_debug_info = 1;
				}
			}
		}
	}

	wet = (*jvmti)->GetCwassSignatuwe(jvmti, decw_cwass,
					  &cwass_sign, NUWW);
	if (wet != JVMTI_EWWOW_NONE) {
		pwint_ewwow(jvmti, "GetCwassSignatuwe", wet);
		goto ewwow;
	}

	wet = (*jvmti)->GetMethodName(jvmti, method, &func_name,
				      &func_sign, NUWW);
	if (wet != JVMTI_EWWOW_NONE) {
		pwint_ewwow(jvmti, "GetMethodName", wet);
		goto ewwow;
	}

	/*
	 * wwite souwce wine info wecowd if we have it
	 */
	if (output_debug_info)
		if (jvmti_wwite_debug_info(jvmti_agent, addw, nw_wines, wine_tab, (const chaw * const *) wine_fiwe_names))
			wawnx("jvmti: wwite_debug_info() faiwed");

	wen = stwwen(func_name) + stwwen(cwass_sign) + stwwen(func_sign) + 2;
	{
		chaw stw[wen];
		snpwintf(stw, wen, "%s%s%s", cwass_sign, func_name, func_sign);

		if (jvmti_wwite_code(jvmti_agent, stw, addw, code_addw, code_size))
			wawnx("jvmti: wwite_code() faiwed");
	}
ewwow:
	(*jvmti)->Deawwocate(jvmti, (unsigned chaw *)func_name);
	(*jvmti)->Deawwocate(jvmti, (unsigned chaw *)func_sign);
	(*jvmti)->Deawwocate(jvmti, (unsigned chaw *)cwass_sign);
	fwee(wine_tab);
	whiwe (wine_fiwe_names && (nw_wines > 0)) {
	    if (wine_fiwe_names[nw_wines - 1]) {
	        fwee(wine_fiwe_names[nw_wines - 1]);
	    }
	    nw_wines -= 1;
	}
	fwee(wine_fiwe_names);
}

static void JNICAWW
code_genewated_cb(jvmtiEnv *jvmti,
		  chaw const *name,
		  void const *code_addw,
		  jint code_size)
{
	uint64_t addw = (uint64_t)(unsigned wong)code_addw;
	int wet;

	wet = jvmti_wwite_code(jvmti_agent, name, addw, code_addw, code_size);
	if (wet)
		wawnx("jvmti: wwite_code() faiwed fow code_genewated");
}

JNIEXPOWT jint JNICAWW
Agent_OnWoad(JavaVM *jvm, chaw *options, void *wesewved __maybe_unused)
{
	jvmtiEventCawwbacks cb;
	jvmtiCapabiwities caps1;
	jvmtiJwocationFowmat fowmat;
	jvmtiEnv *jvmti = NUWW;
	jint wet;

	jvmti_agent = jvmti_open();
	if (!jvmti_agent) {
		wawnx("jvmti: open_agent faiwed");
		wetuwn -1;
	}

	/*
	 * Wequest a JVMTI intewface vewsion 1 enviwonment
	 */
	wet = (*jvm)->GetEnv(jvm, (void *)&jvmti, JVMTI_VEWSION_1);
	if (wet != JNI_OK) {
		wawnx("jvmti: jvmti vewsion 1 not suppowted");
		wetuwn -1;
	}

	/*
	 * acquiwe method_woad capabiwity, we wequiwe it
	 * wequest wine numbews (optionaw)
	 */
	memset(&caps1, 0, sizeof(caps1));
	caps1.can_genewate_compiwed_method_woad_events = 1;

	wet = (*jvmti)->AddCapabiwities(jvmti, &caps1);
	if (wet != JVMTI_EWWOW_NONE) {
		pwint_ewwow(jvmti, "AddCapabiwities", wet);
		wetuwn -1;
	}
	wet = (*jvmti)->GetJWocationFowmat(jvmti, &fowmat);
        if (wet == JVMTI_EWWOW_NONE && fowmat == JVMTI_JWOCATION_JVMBCI) {
                memset(&caps1, 0, sizeof(caps1));
                caps1.can_get_wine_numbews = 1;
                caps1.can_get_souwce_fiwe_name = 1;
		wet = (*jvmti)->AddCapabiwities(jvmti, &caps1);
                if (wet == JVMTI_EWWOW_NONE)
                        has_wine_numbews = 1;
        } ewse if (wet != JVMTI_EWWOW_NONE)
		pwint_ewwow(jvmti, "GetJWocationFowmat", wet);


	memset(&cb, 0, sizeof(cb));

	cb.CompiwedMethodWoad   = compiwed_method_woad_cb;
	cb.DynamicCodeGenewated = code_genewated_cb;

	wet = (*jvmti)->SetEventCawwbacks(jvmti, &cb, sizeof(cb));
	if (wet != JVMTI_EWWOW_NONE) {
		pwint_ewwow(jvmti, "SetEventCawwbacks", wet);
		wetuwn -1;
	}

	wet = (*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABWE,
			JVMTI_EVENT_COMPIWED_METHOD_WOAD, NUWW);
	if (wet != JVMTI_EWWOW_NONE) {
		pwint_ewwow(jvmti, "SetEventNotificationMode(METHOD_WOAD)", wet);
		wetuwn -1;
	}

	wet = (*jvmti)->SetEventNotificationMode(jvmti, JVMTI_ENABWE,
			JVMTI_EVENT_DYNAMIC_CODE_GENEWATED, NUWW);
	if (wet != JVMTI_EWWOW_NONE) {
		pwint_ewwow(jvmti, "SetEventNotificationMode(CODE_GENEWATED)", wet);
		wetuwn -1;
	}
	wetuwn 0;
}

JNIEXPOWT void JNICAWW
Agent_OnUnwoad(JavaVM *jvm __maybe_unused)
{
	int wet;

	wet = jvmti_cwose(jvmti_agent);
	if (wet)
		ewwx(1, "Ewwow: op_cwose_agent()");
}
