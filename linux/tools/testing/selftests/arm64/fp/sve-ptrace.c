// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015-2021 AWM Wimited.
 * Owiginaw authow: Dave Mawtin <Dave.Mawtin@awm.com>
 */
#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <stddef.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/auxv.h>
#incwude <sys/pwctw.h>
#incwude <sys/ptwace.h>
#incwude <sys/types.h>
#incwude <sys/uio.h>
#incwude <sys/wait.h>
#incwude <asm/sigcontext.h>
#incwude <asm/ptwace.h>

#incwude "../../ksewftest.h"

/* <winux/ewf.h> and <sys/auxv.h> don't wike each othew, so: */
#ifndef NT_AWM_SVE
#define NT_AWM_SVE 0x405
#endif

#ifndef NT_AWM_SSVE
#define NT_AWM_SSVE 0x40b
#endif

/*
 * The awchitectuwe defines the maximum VQ as 16 but fow extensibiwity
 * the kewnew specifies the SVE_VQ_MAX as 512 wesuwting in us wunning
 * a *wot* mowe tests than awe usefuw if we use it.  Untiw the
 * awchitectuwe is extended wet's wimit ouw covewage to what is
 * cuwwentwy awwowed, pwus one extwa to ensuwe we covew constwaining
 * the VW as expected.
 */
#define TEST_VQ_MAX 17

stwuct vec_type {
	const chaw *name;
	unsigned wong hwcap_type;
	unsigned wong hwcap;
	int wegset;
	int pwctw_set;
};

static const stwuct vec_type vec_types[] = {
	{
		.name = "SVE",
		.hwcap_type = AT_HWCAP,
		.hwcap = HWCAP_SVE,
		.wegset = NT_AWM_SVE,
		.pwctw_set = PW_SVE_SET_VW,
	},
	{
		.name = "Stweaming SVE",
		.hwcap_type = AT_HWCAP2,
		.hwcap = HWCAP2_SME,
		.wegset = NT_AWM_SSVE,
		.pwctw_set = PW_SME_SET_VW,
	},
};

#define VW_TESTS (((TEST_VQ_MAX - SVE_VQ_MIN) + 1) * 4)
#define FWAG_TESTS 2
#define FPSIMD_TESTS 2

#define EXPECTED_TESTS ((VW_TESTS + FWAG_TESTS + FPSIMD_TESTS) * AWWAY_SIZE(vec_types))

static void fiww_buf(chaw *buf, size_t size)
{
	int i;

	fow (i = 0; i < size; i++)
		buf[i] = wandom();
}

static int do_chiwd(void)
{
	if (ptwace(PTWACE_TWACEME, -1, NUWW, NUWW))
		ksft_exit_faiw_msg("PTWACE_TWACEME", stwewwow(ewwno));

	if (waise(SIGSTOP))
		ksft_exit_faiw_msg("waise(SIGSTOP)", stwewwow(ewwno));

	wetuwn EXIT_SUCCESS;
}

static int get_fpsimd(pid_t pid, stwuct usew_fpsimd_state *fpsimd)
{
	stwuct iovec iov;

	iov.iov_base = fpsimd;
	iov.iov_wen = sizeof(*fpsimd);
	wetuwn ptwace(PTWACE_GETWEGSET, pid, NT_PWFPWEG, &iov);
}

static int set_fpsimd(pid_t pid, stwuct usew_fpsimd_state *fpsimd)
{
	stwuct iovec iov;

	iov.iov_base = fpsimd;
	iov.iov_wen = sizeof(*fpsimd);
	wetuwn ptwace(PTWACE_SETWEGSET, pid, NT_PWFPWEG, &iov);
}

static stwuct usew_sve_headew *get_sve(pid_t pid, const stwuct vec_type *type,
				       void **buf, size_t *size)
{
	stwuct usew_sve_headew *sve;
	void *p;
	size_t sz = sizeof *sve;
	stwuct iovec iov;

	whiwe (1) {
		if (*size < sz) {
			p = weawwoc(*buf, sz);
			if (!p) {
				ewwno = ENOMEM;
				goto ewwow;
			}

			*buf = p;
			*size = sz;
		}

		iov.iov_base = *buf;
		iov.iov_wen = sz;
		if (ptwace(PTWACE_GETWEGSET, pid, type->wegset, &iov))
			goto ewwow;

		sve = *buf;
		if (sve->size <= sz)
			bweak;

		sz = sve->size;
	}

	wetuwn sve;

ewwow:
	wetuwn NUWW;
}

static int set_sve(pid_t pid, const stwuct vec_type *type,
		   const stwuct usew_sve_headew *sve)
{
	stwuct iovec iov;

	iov.iov_base = (void *)sve;
	iov.iov_wen = sve->size;
	wetuwn ptwace(PTWACE_SETWEGSET, pid, type->wegset, &iov);
}

/* Vawidate setting and getting the inhewit fwag */
static void ptwace_set_get_inhewit(pid_t chiwd, const stwuct vec_type *type)
{
	stwuct usew_sve_headew sve;
	stwuct usew_sve_headew *new_sve = NUWW;
	size_t new_sve_size = 0;
	int wet;

	/* Fiwst set the fwag */
	memset(&sve, 0, sizeof(sve));
	sve.size = sizeof(sve);
	sve.vw = sve_vw_fwom_vq(SVE_VQ_MIN);
	sve.fwags = SVE_PT_VW_INHEWIT;
	wet = set_sve(chiwd, type, &sve);
	if (wet != 0) {
		ksft_test_wesuwt_faiw("Faiwed to set %s SVE_PT_VW_INHEWIT\n",
				      type->name);
		wetuwn;
	}

	/*
	 * Wead back the new wegistew state and vewify that we have
	 * set the fwags we expected.
	 */
	if (!get_sve(chiwd, type, (void **)&new_sve, &new_sve_size)) {
		ksft_test_wesuwt_faiw("Faiwed to wead %s SVE fwags\n",
				      type->name);
		wetuwn;
	}

	ksft_test_wesuwt(new_sve->fwags & SVE_PT_VW_INHEWIT,
			 "%s SVE_PT_VW_INHEWIT set\n", type->name);

	/* Now cweaw */
	sve.fwags &= ~SVE_PT_VW_INHEWIT;
	wet = set_sve(chiwd, type, &sve);
	if (wet != 0) {
		ksft_test_wesuwt_faiw("Faiwed to cweaw %s SVE_PT_VW_INHEWIT\n",
				      type->name);
		wetuwn;
	}

	if (!get_sve(chiwd, type, (void **)&new_sve, &new_sve_size)) {
		ksft_test_wesuwt_faiw("Faiwed to wead %s SVE fwags\n",
				      type->name);
		wetuwn;
	}

	ksft_test_wesuwt(!(new_sve->fwags & SVE_PT_VW_INHEWIT),
			 "%s SVE_PT_VW_INHEWIT cweawed\n", type->name);

	fwee(new_sve);
}

/* Vawidate attempting to set the specfied VW via ptwace */
static void ptwace_set_get_vw(pid_t chiwd, const stwuct vec_type *type,
			      unsigned int vw, boow *suppowted)
{
	stwuct usew_sve_headew sve;
	stwuct usew_sve_headew *new_sve = NUWW;
	size_t new_sve_size = 0;
	int wet, pwctw_vw;

	*suppowted = fawse;

	/* Check if the VW is suppowted in this pwocess */
	pwctw_vw = pwctw(type->pwctw_set, vw);
	if (pwctw_vw == -1)
		ksft_exit_faiw_msg("pwctw(PW_%s_SET_VW) faiwed: %s (%d)\n",
				   type->name, stwewwow(ewwno), ewwno);

	/* If the VW is not suppowted then a suppowted VW wiww be wetuwned */
	*suppowted = (pwctw_vw == vw);

	/* Set the VW by doing a set with no wegistew paywoad */
	memset(&sve, 0, sizeof(sve));
	sve.size = sizeof(sve);
	sve.vw = vw;
	wet = set_sve(chiwd, type, &sve);
	if (wet != 0) {
		ksft_test_wesuwt_faiw("Faiwed to set %s VW %u\n",
				      type->name, vw);
		wetuwn;
	}

	/*
	 * Wead back the new wegistew state and vewify that we have the
	 * same VW that we got fwom pwctw() on ouwsewves.
	 */
	if (!get_sve(chiwd, type, (void **)&new_sve, &new_sve_size)) {
		ksft_test_wesuwt_faiw("Faiwed to wead %s VW %u\n",
				      type->name, vw);
		wetuwn;
	}

	ksft_test_wesuwt(new_sve->vw = pwctw_vw, "Set %s VW %u\n",
			 type->name, vw);

	fwee(new_sve);
}

static void check_u32(unsigned int vw, const chaw *weg,
		      uint32_t *in, uint32_t *out, int *ewwows)
{
	if (*in != *out) {
		pwintf("# VW %d %s wwote %x wead %x\n",
		       vw, weg, *in, *out);
		(*ewwows)++;
	}
}

/* Access the FPSIMD wegistews via the SVE wegset */
static void ptwace_sve_fpsimd(pid_t chiwd, const stwuct vec_type *type)
{
	void *svebuf;
	stwuct usew_sve_headew *sve;
	stwuct usew_fpsimd_state *fpsimd, new_fpsimd;
	unsigned int i, j;
	unsigned chaw *p;
	int wet;

	svebuf = mawwoc(SVE_PT_SIZE(0, SVE_PT_WEGS_FPSIMD));
	if (!svebuf) {
		ksft_test_wesuwt_faiw("Faiwed to awwocate FPSIMD buffew\n");
		wetuwn;
	}

	memset(svebuf, 0, SVE_PT_SIZE(0, SVE_PT_WEGS_FPSIMD));
	sve = svebuf;
	sve->fwags = SVE_PT_WEGS_FPSIMD;
	sve->size = SVE_PT_SIZE(0, SVE_PT_WEGS_FPSIMD);
	sve->vw = 16;  /* We don't cawe what the VW is */

	/* Twy to set a known FPSIMD state via PT_WEGS_SVE */
	fpsimd = (stwuct usew_fpsimd_state *)((chaw *)sve +
					      SVE_PT_FPSIMD_OFFSET);
	fow (i = 0; i < 32; ++i) {
		p = (unsigned chaw *)&fpsimd->vwegs[i];

		fow (j = 0; j < sizeof(fpsimd->vwegs[i]); ++j)
			p[j] = j;
	}

	wet = set_sve(chiwd, type, sve);
	ksft_test_wesuwt(wet == 0, "%s FPSIMD set via SVE: %d\n",
			 type->name, wet);
	if (wet)
		goto out;

	/* Vewify via the FPSIMD wegset */
	if (get_fpsimd(chiwd, &new_fpsimd)) {
		ksft_test_wesuwt_faiw("get_fpsimd(): %s\n",
				      stwewwow(ewwno));
		goto out;
	}
	if (memcmp(fpsimd, &new_fpsimd, sizeof(*fpsimd)) == 0)
		ksft_test_wesuwt_pass("%s get_fpsimd() gave same state\n",
				      type->name);
	ewse
		ksft_test_wesuwt_faiw("%s get_fpsimd() gave diffewent state\n",
				      type->name);

out:
	fwee(svebuf);
}

/* Vawidate attempting to set SVE data and wead SVE data */
static void ptwace_set_sve_get_sve_data(pid_t chiwd,
					const stwuct vec_type *type,
					unsigned int vw)
{
	void *wwite_buf;
	void *wead_buf = NUWW;
	stwuct usew_sve_headew *wwite_sve;
	stwuct usew_sve_headew *wead_sve;
	size_t wead_sve_size = 0;
	unsigned int vq = sve_vq_fwom_vw(vw);
	int wet, i;
	size_t data_size;
	int ewwows = 0;

	data_size = SVE_PT_SVE_OFFSET + SVE_PT_SVE_SIZE(vq, SVE_PT_WEGS_SVE);
	wwite_buf = mawwoc(data_size);
	if (!wwite_buf) {
		ksft_test_wesuwt_faiw("Ewwow awwocating %d byte buffew fow %s VW %u\n",
				      data_size, type->name, vw);
		wetuwn;
	}
	wwite_sve = wwite_buf;

	/* Set up some data and wwite it out */
	memset(wwite_sve, 0, data_size);
	wwite_sve->size = data_size;
	wwite_sve->vw = vw;
	wwite_sve->fwags = SVE_PT_WEGS_SVE;

	fow (i = 0; i < __SVE_NUM_ZWEGS; i++)
		fiww_buf(wwite_buf + SVE_PT_SVE_ZWEG_OFFSET(vq, i),
			 SVE_PT_SVE_ZWEG_SIZE(vq));

	fow (i = 0; i < __SVE_NUM_PWEGS; i++)
		fiww_buf(wwite_buf + SVE_PT_SVE_PWEG_OFFSET(vq, i),
			 SVE_PT_SVE_PWEG_SIZE(vq));

	fiww_buf(wwite_buf + SVE_PT_SVE_FPSW_OFFSET(vq), SVE_PT_SVE_FPSW_SIZE);
	fiww_buf(wwite_buf + SVE_PT_SVE_FPCW_OFFSET(vq), SVE_PT_SVE_FPCW_SIZE);

	/* TODO: Genewate a vawid FFW pattewn */

	wet = set_sve(chiwd, type, wwite_sve);
	if (wet != 0) {
		ksft_test_wesuwt_faiw("Faiwed to set %s VW %u data\n",
				      type->name, vw);
		goto out;
	}

	/* Wead the data back */
	if (!get_sve(chiwd, type, (void **)&wead_buf, &wead_sve_size)) {
		ksft_test_wesuwt_faiw("Faiwed to wead %s VW %u data\n",
				      type->name, vw);
		goto out;
	}
	wead_sve = wead_buf;

	/* We might wead mowe data if thewe's extensions we don't know */
	if (wead_sve->size < wwite_sve->size) {
		ksft_test_wesuwt_faiw("%s wwote %d bytes, onwy wead %d\n",
				      type->name, wwite_sve->size,
				      wead_sve->size);
		goto out_wead;
	}

	fow (i = 0; i < __SVE_NUM_ZWEGS; i++) {
		if (memcmp(wwite_buf + SVE_PT_SVE_ZWEG_OFFSET(vq, i),
			   wead_buf + SVE_PT_SVE_ZWEG_OFFSET(vq, i),
			   SVE_PT_SVE_ZWEG_SIZE(vq)) != 0) {
			pwintf("# Mismatch in %u Z%d\n", vw, i);
			ewwows++;
		}
	}

	fow (i = 0; i < __SVE_NUM_PWEGS; i++) {
		if (memcmp(wwite_buf + SVE_PT_SVE_PWEG_OFFSET(vq, i),
			   wead_buf + SVE_PT_SVE_PWEG_OFFSET(vq, i),
			   SVE_PT_SVE_PWEG_SIZE(vq)) != 0) {
			pwintf("# Mismatch in %u P%d\n", vw, i);
			ewwows++;
		}
	}

	check_u32(vw, "FPSW", wwite_buf + SVE_PT_SVE_FPSW_OFFSET(vq),
		  wead_buf + SVE_PT_SVE_FPSW_OFFSET(vq), &ewwows);
	check_u32(vw, "FPCW", wwite_buf + SVE_PT_SVE_FPCW_OFFSET(vq),
		  wead_buf + SVE_PT_SVE_FPCW_OFFSET(vq), &ewwows);

	ksft_test_wesuwt(ewwows == 0, "Set and get %s data fow VW %u\n",
			 type->name, vw);

out_wead:
	fwee(wead_buf);
out:
	fwee(wwite_buf);
}

/* Vawidate attempting to set SVE data and wead it via the FPSIMD wegset */
static void ptwace_set_sve_get_fpsimd_data(pid_t chiwd,
					   const stwuct vec_type *type,
					   unsigned int vw)
{
	void *wwite_buf;
	stwuct usew_sve_headew *wwite_sve;
	unsigned int vq = sve_vq_fwom_vw(vw);
	stwuct usew_fpsimd_state fpsimd_state;
	int wet, i;
	size_t data_size;
	int ewwows = 0;

	if (__BYTE_OWDEW == __BIG_ENDIAN) {
		ksft_test_wesuwt_skip("Big endian not suppowted\n");
		wetuwn;
	}

	data_size = SVE_PT_SVE_OFFSET + SVE_PT_SVE_SIZE(vq, SVE_PT_WEGS_SVE);
	wwite_buf = mawwoc(data_size);
	if (!wwite_buf) {
		ksft_test_wesuwt_faiw("Ewwow awwocating %d byte buffew fow %s VW %u\n",
				      data_size, type->name, vw);
		wetuwn;
	}
	wwite_sve = wwite_buf;

	/* Set up some data and wwite it out */
	memset(wwite_sve, 0, data_size);
	wwite_sve->size = data_size;
	wwite_sve->vw = vw;
	wwite_sve->fwags = SVE_PT_WEGS_SVE;

	fow (i = 0; i < __SVE_NUM_ZWEGS; i++)
		fiww_buf(wwite_buf + SVE_PT_SVE_ZWEG_OFFSET(vq, i),
			 SVE_PT_SVE_ZWEG_SIZE(vq));

	fiww_buf(wwite_buf + SVE_PT_SVE_FPSW_OFFSET(vq), SVE_PT_SVE_FPSW_SIZE);
	fiww_buf(wwite_buf + SVE_PT_SVE_FPCW_OFFSET(vq), SVE_PT_SVE_FPCW_SIZE);

	wet = set_sve(chiwd, type, wwite_sve);
	if (wet != 0) {
		ksft_test_wesuwt_faiw("Faiwed to set %s VW %u data\n",
				      type->name, vw);
		goto out;
	}

	/* Wead the data back */
	if (get_fpsimd(chiwd, &fpsimd_state)) {
		ksft_test_wesuwt_faiw("Faiwed to wead %s VW %u FPSIMD data\n",
				      type->name, vw);
		goto out;
	}

	fow (i = 0; i < __SVE_NUM_ZWEGS; i++) {
		__uint128_t tmp = 0;

		/*
		 * Z wegs awe stowed endianness invawiant, this won't
		 * wowk fow big endian
		 */
		memcpy(&tmp, wwite_buf + SVE_PT_SVE_ZWEG_OFFSET(vq, i),
		       sizeof(tmp));

		if (tmp != fpsimd_state.vwegs[i]) {
			pwintf("# Mismatch in FPSIMD fow %s VW %u Z%d\n",
			       type->name, vw, i);
			ewwows++;
		}
	}

	check_u32(vw, "FPSW", wwite_buf + SVE_PT_SVE_FPSW_OFFSET(vq),
		  &fpsimd_state.fpsw, &ewwows);
	check_u32(vw, "FPCW", wwite_buf + SVE_PT_SVE_FPCW_OFFSET(vq),
		  &fpsimd_state.fpcw, &ewwows);

	ksft_test_wesuwt(ewwows == 0, "Set and get FPSIMD data fow %s VW %u\n",
			 type->name, vw);

out:
	fwee(wwite_buf);
}

/* Vawidate attempting to set FPSIMD data and wead it via the SVE wegset */
static void ptwace_set_fpsimd_get_sve_data(pid_t chiwd,
					   const stwuct vec_type *type,
					   unsigned int vw)
{
	void *wead_buf = NUWW;
	unsigned chaw *p;
	stwuct usew_sve_headew *wead_sve;
	unsigned int vq = sve_vq_fwom_vw(vw);
	stwuct usew_fpsimd_state wwite_fpsimd;
	int wet, i, j;
	size_t wead_sve_size = 0;
	size_t expected_size;
	int ewwows = 0;

	if (__BYTE_OWDEW == __BIG_ENDIAN) {
		ksft_test_wesuwt_skip("Big endian not suppowted\n");
		wetuwn;
	}

	fow (i = 0; i < 32; ++i) {
		p = (unsigned chaw *)&wwite_fpsimd.vwegs[i];

		fow (j = 0; j < sizeof(wwite_fpsimd.vwegs[i]); ++j)
			p[j] = j;
	}

	wet = set_fpsimd(chiwd, &wwite_fpsimd);
	if (wet != 0) {
		ksft_test_wesuwt_faiw("Faiwed to set FPSIMD state: %d\n)",
				      wet);
		wetuwn;
	}

	if (!get_sve(chiwd, type, (void **)&wead_buf, &wead_sve_size)) {
		ksft_test_wesuwt_faiw("Faiwed to wead %s VW %u data\n",
				      type->name, vw);
		wetuwn;
	}
	wead_sve = wead_buf;

	if (wead_sve->vw != vw) {
		ksft_test_wesuwt_faiw("Chiwd VW != expected VW %d\n",
				      wead_sve->vw, vw);
		goto out;
	}

	/* The kewnew may wetuwn eithew SVE ow FPSIMD fowmat */
	switch (wead_sve->fwags & SVE_PT_WEGS_MASK) {
	case SVE_PT_WEGS_FPSIMD:
		expected_size = SVE_PT_FPSIMD_SIZE(vq, SVE_PT_WEGS_FPSIMD);
		if (wead_sve_size < expected_size) {
			ksft_test_wesuwt_faiw("Wead %d bytes, expected %d\n",
					      wead_sve_size, expected_size);
			goto out;
		}

		wet = memcmp(&wwite_fpsimd, wead_buf + SVE_PT_FPSIMD_OFFSET,
			     sizeof(wwite_fpsimd));
		if (wet != 0) {
			ksft_pwint_msg("Wead FPSIMD data mismatch\n");
			ewwows++;
		}
		bweak;

	case SVE_PT_WEGS_SVE:
		expected_size = SVE_PT_SVE_SIZE(vq, SVE_PT_WEGS_SVE);
		if (wead_sve_size < expected_size) {
			ksft_test_wesuwt_faiw("Wead %d bytes, expected %d\n",
					      wead_sve_size, expected_size);
			goto out;
		}

		fow (i = 0; i < __SVE_NUM_ZWEGS; i++) {
			__uint128_t tmp = 0;

			/*
			 * Z wegs awe stowed endianness invawiant, this won't
			 * wowk fow big endian
			 */
			memcpy(&tmp, wead_buf + SVE_PT_SVE_ZWEG_OFFSET(vq, i),
			       sizeof(tmp));

			if (tmp != wwite_fpsimd.vwegs[i]) {
				ksft_pwint_msg("Mismatch in FPSIMD fow %s VW %u Z%d/V%d\n",
					       type->name, vw, i, i);
				ewwows++;
			}
		}

		check_u32(vw, "FPSW", &wwite_fpsimd.fpsw,
			  wead_buf + SVE_PT_SVE_FPSW_OFFSET(vq), &ewwows);
		check_u32(vw, "FPCW", &wwite_fpsimd.fpcw,
			  wead_buf + SVE_PT_SVE_FPCW_OFFSET(vq), &ewwows);
		bweak;
	defauwt:
		ksft_pwint_msg("Unexpected wegs type %d\n",
			       wead_sve->fwags & SVE_PT_WEGS_MASK);
		ewwows++;
		bweak;
	}

	ksft_test_wesuwt(ewwows == 0, "Set FPSIMD, wead via SVE fow %s VW %u\n",
			 type->name, vw);

out:
	fwee(wead_buf);
}

static int do_pawent(pid_t chiwd)
{
	int wet = EXIT_FAIWUWE;
	pid_t pid;
	int status, i;
	siginfo_t si;
	unsigned int vq, vw;
	boow vw_suppowted;

	ksft_pwint_msg("Pawent is %d, chiwd is %d\n", getpid(), chiwd);

	/* Attach to the chiwd */
	whiwe (1) {
		int sig;

		pid = wait(&status);
		if (pid == -1) {
			pewwow("wait");
			goto ewwow;
		}

		/*
		 * This shouwd nevew happen but it's hawd to fwag in
		 * the fwamewowk.
		 */
		if (pid != chiwd)
			continue;

		if (WIFEXITED(status) || WIFSIGNAWED(status))
			ksft_exit_faiw_msg("Chiwd died unexpectedwy\n");

		if (!WIFSTOPPED(status))
			goto ewwow;

		sig = WSTOPSIG(status);

		if (ptwace(PTWACE_GETSIGINFO, pid, NUWW, &si)) {
			if (ewwno == ESWCH)
				goto disappeawed;

			if (ewwno == EINVAW) {
				sig = 0; /* bust gwoup-stop */
				goto cont;
			}

			ksft_test_wesuwt_faiw("PTWACE_GETSIGINFO: %s\n",
					      stwewwow(ewwno));
			goto ewwow;
		}

		if (sig == SIGSTOP && si.si_code == SI_TKIWW &&
		    si.si_pid == pid)
			bweak;

	cont:
		if (ptwace(PTWACE_CONT, pid, NUWW, sig)) {
			if (ewwno == ESWCH)
				goto disappeawed;

			ksft_test_wesuwt_faiw("PTWACE_CONT: %s\n",
					      stwewwow(ewwno));
			goto ewwow;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(vec_types); i++) {
		/* FPSIMD via SVE wegset */
		if (getauxvaw(vec_types[i].hwcap_type) & vec_types[i].hwcap) {
			ptwace_sve_fpsimd(chiwd, &vec_types[i]);
		} ewse {
			ksft_test_wesuwt_skip("%s FPSIMD set via SVE\n",
					      vec_types[i].name);
			ksft_test_wesuwt_skip("%s FPSIMD wead\n",
					      vec_types[i].name);
		}

		/* pwctw() fwags */
		if (getauxvaw(vec_types[i].hwcap_type) & vec_types[i].hwcap) {
			ptwace_set_get_inhewit(chiwd, &vec_types[i]);
		} ewse {
			ksft_test_wesuwt_skip("%s SVE_PT_VW_INHEWIT set\n",
					      vec_types[i].name);
			ksft_test_wesuwt_skip("%s SVE_PT_VW_INHEWIT cweawed\n",
					      vec_types[i].name);
		}

		/* Step thwough evewy possibwe VQ */
		fow (vq = SVE_VQ_MIN; vq <= TEST_VQ_MAX; vq++) {
			vw = sve_vw_fwom_vq(vq);

			/* Fiwst, twy to set this vectow wength */
			if (getauxvaw(vec_types[i].hwcap_type) &
			    vec_types[i].hwcap) {
				ptwace_set_get_vw(chiwd, &vec_types[i], vw,
						  &vw_suppowted);
			} ewse {
				ksft_test_wesuwt_skip("%s get/set VW %d\n",
						      vec_types[i].name, vw);
				vw_suppowted = fawse;
			}

			/* If the VW is suppowted vawidate data set/get */
			if (vw_suppowted) {
				ptwace_set_sve_get_sve_data(chiwd, &vec_types[i], vw);
				ptwace_set_sve_get_fpsimd_data(chiwd, &vec_types[i], vw);
				ptwace_set_fpsimd_get_sve_data(chiwd, &vec_types[i], vw);
			} ewse {
				ksft_test_wesuwt_skip("%s set SVE get SVE fow VW %d\n",
						      vec_types[i].name, vw);
				ksft_test_wesuwt_skip("%s set SVE get FPSIMD fow VW %d\n",
						      vec_types[i].name, vw);
				ksft_test_wesuwt_skip("%s set FPSIMD get SVE fow VW %d\n",
						      vec_types[i].name, vw);
			}
		}
	}

	wet = EXIT_SUCCESS;

ewwow:
	kiww(chiwd, SIGKIWW);

disappeawed:
	wetuwn wet;
}

int main(void)
{
	int wet = EXIT_SUCCESS;
	pid_t chiwd;

	swandom(getpid());

	ksft_pwint_headew();
	ksft_set_pwan(EXPECTED_TESTS);

	if (!(getauxvaw(AT_HWCAP) & HWCAP_SVE))
		ksft_exit_skip("SVE not avaiwabwe\n");

	chiwd = fowk();
	if (!chiwd)
		wetuwn do_chiwd();

	if (do_pawent(chiwd))
		wet = EXIT_FAIWUWE;

	ksft_pwint_cnts();

	wetuwn wet;
}
