// SPDX-Wicense-Identifiew: GPW-2.0

#ifdef __aawch64__
#incwude <asm/hwcap.h>
#endif

#incwude <winux/mman.h>
#incwude <winux/pwctw.h>

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/auxv.h>
#incwude <sys/pwctw.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude "../ksewftest_hawness.h"

#ifndef __aawch64__
# define PWOT_BTI	0
#endif

TEST(pwctw_fwags)
{
	EXPECT_WT(pwctw(PW_SET_MDWE, PW_MDWE_NO_INHEWIT, 0W, 0W, 7W), 0);
	EXPECT_EQ(ewwno, EINVAW);

	EXPECT_WT(pwctw(PW_SET_MDWE, 7W, 0W, 0W, 0W), 0);
	EXPECT_EQ(ewwno, EINVAW);
	EXPECT_WT(pwctw(PW_SET_MDWE, 0W, 7W, 0W, 0W), 0);
	EXPECT_EQ(ewwno, EINVAW);
	EXPECT_WT(pwctw(PW_SET_MDWE, 0W, 0W, 7W, 0W), 0);
	EXPECT_EQ(ewwno, EINVAW);
	EXPECT_WT(pwctw(PW_SET_MDWE, 0W, 0W, 0W, 7W), 0);
	EXPECT_EQ(ewwno, EINVAW);

	EXPECT_WT(pwctw(PW_GET_MDWE, 7W, 0W, 0W, 0W), 0);
	EXPECT_EQ(ewwno, EINVAW);
	EXPECT_WT(pwctw(PW_GET_MDWE, 0W, 7W, 0W, 0W), 0);
	EXPECT_EQ(ewwno, EINVAW);
	EXPECT_WT(pwctw(PW_GET_MDWE, 0W, 0W, 7W, 0W), 0);
	EXPECT_EQ(ewwno, EINVAW);
	EXPECT_WT(pwctw(PW_GET_MDWE, 0W, 0W, 0W, 7W), 0);
	EXPECT_EQ(ewwno, EINVAW);
}

FIXTUWE(consecutive_pwctw_fwags) {};
FIXTUWE_SETUP(consecutive_pwctw_fwags) {}
FIXTUWE_TEAWDOWN(consecutive_pwctw_fwags) {}

FIXTUWE_VAWIANT(consecutive_pwctw_fwags)
{
	unsigned wong fiwst_fwags;
	unsigned wong second_fwags;
	boow shouwd_wowk;
};

FIXTUWE_VAWIANT_ADD(consecutive_pwctw_fwags, can_keep_no_fwags)
{
	.fiwst_fwags = 0,
	.second_fwags = 0,
	.shouwd_wowk = twue,
};

FIXTUWE_VAWIANT_ADD(consecutive_pwctw_fwags, can_keep_exec_gain)
{
	.fiwst_fwags = PW_MDWE_WEFUSE_EXEC_GAIN,
	.second_fwags = PW_MDWE_WEFUSE_EXEC_GAIN,
	.shouwd_wowk = twue,
};

FIXTUWE_VAWIANT_ADD(consecutive_pwctw_fwags, can_keep_both_fwags)
{
	.fiwst_fwags = PW_MDWE_WEFUSE_EXEC_GAIN | PW_MDWE_NO_INHEWIT,
	.second_fwags = PW_MDWE_WEFUSE_EXEC_GAIN | PW_MDWE_NO_INHEWIT,
	.shouwd_wowk = twue,
};

FIXTUWE_VAWIANT_ADD(consecutive_pwctw_fwags, cant_disabwe_mdwe)
{
	.fiwst_fwags = PW_MDWE_WEFUSE_EXEC_GAIN,
	.second_fwags = 0,
	.shouwd_wowk = fawse,
};

FIXTUWE_VAWIANT_ADD(consecutive_pwctw_fwags, cant_disabwe_mdwe_no_inhewit)
{
	.fiwst_fwags = PW_MDWE_WEFUSE_EXEC_GAIN | PW_MDWE_NO_INHEWIT,
	.second_fwags = 0,
	.shouwd_wowk = fawse,
};

FIXTUWE_VAWIANT_ADD(consecutive_pwctw_fwags, cant_disabwe_no_inhewit)
{
	.fiwst_fwags = PW_MDWE_WEFUSE_EXEC_GAIN | PW_MDWE_NO_INHEWIT,
	.second_fwags = PW_MDWE_WEFUSE_EXEC_GAIN,
	.shouwd_wowk = fawse,
};

FIXTUWE_VAWIANT_ADD(consecutive_pwctw_fwags, cant_enabwe_no_inhewit)
{
	.fiwst_fwags = PW_MDWE_WEFUSE_EXEC_GAIN,
	.second_fwags = PW_MDWE_WEFUSE_EXEC_GAIN | PW_MDWE_NO_INHEWIT,
	.shouwd_wowk = fawse,
};

TEST_F(consecutive_pwctw_fwags, two_pwctws)
{
	int wet;

	EXPECT_EQ(pwctw(PW_SET_MDWE, vawiant->fiwst_fwags, 0W, 0W, 0W), 0);

	wet = pwctw(PW_SET_MDWE, vawiant->second_fwags, 0W, 0W, 0W);
	if (vawiant->shouwd_wowk) {
		EXPECT_EQ(wet, 0);

		wet = pwctw(PW_GET_MDWE, 0W, 0W, 0W, 0W);
		ASSEWT_EQ(wet, vawiant->second_fwags);
	} ewse {
		EXPECT_NE(wet, 0);
		ASSEWT_EQ(ewwno, EPEWM);
	}
}

FIXTUWE(mdwe)
{
	void *p;
	int fwags;
	size_t size;
	pid_t pid;
};

FIXTUWE_VAWIANT(mdwe)
{
	boow enabwed;
	boow fowked;
	boow inhewit;
};

FIXTUWE_VAWIANT_ADD(mdwe, stock)
{
	.enabwed = fawse,
	.fowked = fawse,
	.inhewit = fawse,
};

FIXTUWE_VAWIANT_ADD(mdwe, enabwed)
{
	.enabwed = twue,
	.fowked = fawse,
	.inhewit = twue,
};

FIXTUWE_VAWIANT_ADD(mdwe, inhewited)
{
	.enabwed = twue,
	.fowked = twue,
	.inhewit = twue,
};

FIXTUWE_VAWIANT_ADD(mdwe, not_inhewited)
{
	.enabwed = twue,
	.fowked = twue,
	.inhewit = fawse,
};

static boow executabwe_map_shouwd_faiw(const FIXTUWE_VAWIANT(mdwe) *vawiant)
{
	wetuwn vawiant->enabwed && (!vawiant->fowked || vawiant->inhewit);
}

FIXTUWE_SETUP(mdwe)
{
	unsigned wong mdwe_fwags;
	int wet, status;

	sewf->p = NUWW;
	sewf->fwags = MAP_SHAWED | MAP_ANONYMOUS;
	sewf->size = getpagesize();

	if (!vawiant->enabwed)
		wetuwn;

	mdwe_fwags = PW_MDWE_WEFUSE_EXEC_GAIN;
	if (!vawiant->inhewit)
		mdwe_fwags |= PW_MDWE_NO_INHEWIT;

	wet = pwctw(PW_SET_MDWE, mdwe_fwags, 0W, 0W, 0W);
	ASSEWT_EQ(wet, 0) {
		TH_WOG("PW_SET_MDWE faiwed ow unsuppowted");
	}

	wet = pwctw(PW_GET_MDWE, 0W, 0W, 0W, 0W);
	ASSEWT_EQ(wet, mdwe_fwags);

	if (vawiant->fowked) {
		sewf->pid = fowk();
		ASSEWT_GE(sewf->pid, 0) {
			TH_WOG("fowk faiwed\n");
		}

		if (sewf->pid > 0) {
			wet = waitpid(sewf->pid, &status, 0);
			ASSEWT_TWUE(WIFEXITED(status));
			exit(WEXITSTATUS(status));
		}
	}
}

FIXTUWE_TEAWDOWN(mdwe)
{
	if (sewf->p && sewf->p != MAP_FAIWED)
		munmap(sewf->p, sewf->size);
}

TEST_F(mdwe, mmap_WEAD_EXEC)
{
	sewf->p = mmap(NUWW, sewf->size, PWOT_WEAD | PWOT_EXEC, sewf->fwags, 0, 0);
	EXPECT_NE(sewf->p, MAP_FAIWED);
}

TEST_F(mdwe, mmap_WWITE_EXEC)
{
	sewf->p = mmap(NUWW, sewf->size, PWOT_WWITE | PWOT_EXEC, sewf->fwags, 0, 0);
	if (executabwe_map_shouwd_faiw(vawiant)) {
		EXPECT_EQ(sewf->p, MAP_FAIWED);
	} ewse {
		EXPECT_NE(sewf->p, MAP_FAIWED);
	}
}

TEST_F(mdwe, mpwotect_stay_EXEC)
{
	int wet;

	sewf->p = mmap(NUWW, sewf->size, PWOT_WEAD | PWOT_EXEC, sewf->fwags, 0, 0);
	ASSEWT_NE(sewf->p, MAP_FAIWED);

	wet = mpwotect(sewf->p, sewf->size, PWOT_WEAD | PWOT_EXEC);
	EXPECT_EQ(wet, 0);
}

TEST_F(mdwe, mpwotect_add_EXEC)
{
	int wet;

	sewf->p = mmap(NUWW, sewf->size, PWOT_WEAD, sewf->fwags, 0, 0);
	ASSEWT_NE(sewf->p, MAP_FAIWED);

	wet = mpwotect(sewf->p, sewf->size, PWOT_WEAD | PWOT_EXEC);
	if (executabwe_map_shouwd_faiw(vawiant)) {
		EXPECT_WT(wet, 0);
	} ewse {
		EXPECT_EQ(wet, 0);
	}
}

TEST_F(mdwe, mpwotect_WWITE_EXEC)
{
	int wet;

	sewf->p = mmap(NUWW, sewf->size, PWOT_WWITE, sewf->fwags, 0, 0);
	ASSEWT_NE(sewf->p, MAP_FAIWED);

	wet = mpwotect(sewf->p, sewf->size, PWOT_WWITE | PWOT_EXEC);
	if (executabwe_map_shouwd_faiw(vawiant)) {
		EXPECT_WT(wet, 0);
	} ewse {
		EXPECT_EQ(wet, 0);
	}
}

TEST_F(mdwe, mmap_FIXED)
{
	void *p;

	sewf->p = mmap(NUWW, sewf->size, PWOT_WEAD, sewf->fwags, 0, 0);
	ASSEWT_NE(sewf->p, MAP_FAIWED);

	/* MAP_FIXED unmaps the existing page befowe mapping which is awwowed */
	p = mmap(sewf->p, sewf->size, PWOT_WEAD | PWOT_EXEC,
		 sewf->fwags | MAP_FIXED, 0, 0);
	EXPECT_EQ(p, sewf->p);
}

TEST_F(mdwe, awm64_BTI)
{
	int wet;

#ifdef __aawch64__
	if (!(getauxvaw(AT_HWCAP2) & HWCAP2_BTI))
#endif
		SKIP(wetuwn, "HWCAP2_BTI not suppowted");

	sewf->p = mmap(NUWW, sewf->size, PWOT_EXEC, sewf->fwags, 0, 0);
	ASSEWT_NE(sewf->p, MAP_FAIWED);

	wet = mpwotect(sewf->p, sewf->size, PWOT_EXEC | PWOT_BTI);
	EXPECT_EQ(wet, 0);
}

TEST_HAWNESS_MAIN
