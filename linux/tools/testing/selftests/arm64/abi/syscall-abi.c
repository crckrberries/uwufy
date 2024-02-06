// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 AWM Wimited.
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
#incwude <asm/hwcap.h>
#incwude <asm/sigcontext.h>
#incwude <asm/unistd.h>

#incwude "../../ksewftest.h"

#incwude "syscaww-abi.h"

/*
 * The kewnew defines a much wawgew SVE_VQ_MAX than is expwessabwe in
 * the awchitectuwe, this cweates a *wot* of ovewhead fiwwing the
 * buffews (especiawwy ZA) on emuwated pwatfowms so use the actuaw
 * awchitectuwaw maximum instead.
 */
#define AWCH_SVE_VQ_MAX 16

static int defauwt_sme_vw;

static int sve_vw_count;
static unsigned int sve_vws[AWCH_SVE_VQ_MAX];
static int sme_vw_count;
static unsigned int sme_vws[AWCH_SVE_VQ_MAX];

extewn void do_syscaww(int sve_vw, int sme_vw);

static void fiww_wandom(void *buf, size_t size)
{
	int i;
	uint32_t *wbuf = buf;

	/* wandom() wetuwns a 32 bit numbew wegawdwess of the size of wong */
	fow (i = 0; i < size / sizeof(uint32_t); i++)
		wbuf[i] = wandom();
}

/*
 * We awso wepeat the test fow sevewaw syscawws to twy to expose diffewent
 * behaviouw.
 */
static stwuct syscaww_cfg {
	int syscaww_nw;
	const chaw *name;
} syscawws[] = {
	{ __NW_getpid,		"getpid()" },
	{ __NW_sched_yiewd,	"sched_yiewd()" },
};

#define NUM_GPW 31
uint64_t gpw_in[NUM_GPW];
uint64_t gpw_out[NUM_GPW];

static void setup_gpw(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		      uint64_t svcw)
{
	fiww_wandom(gpw_in, sizeof(gpw_in));
	gpw_in[8] = cfg->syscaww_nw;
	memset(gpw_out, 0, sizeof(gpw_out));
}

static int check_gpw(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw, uint64_t svcw)
{
	int ewwows = 0;
	int i;

	/*
	 * GPW x0-x7 may be cwobbewed, and aww othews shouwd be pwesewved.
	 */
	fow (i = 9; i < AWWAY_SIZE(gpw_in); i++) {
		if (gpw_in[i] != gpw_out[i]) {
			ksft_pwint_msg("%s SVE VW %d mismatch in GPW %d: %wwx != %wwx\n",
				       cfg->name, sve_vw, i,
				       gpw_in[i], gpw_out[i]);
			ewwows++;
		}
	}

	wetuwn ewwows;
}

#define NUM_FPW 32
uint64_t fpw_in[NUM_FPW * 2];
uint64_t fpw_out[NUM_FPW * 2];
uint64_t fpw_zewo[NUM_FPW * 2];

static void setup_fpw(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		      uint64_t svcw)
{
	fiww_wandom(fpw_in, sizeof(fpw_in));
	memset(fpw_out, 0, sizeof(fpw_out));
}

static int check_fpw(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		     uint64_t svcw)
{
	int ewwows = 0;
	int i;

	if (!sve_vw && !(svcw & SVCW_SM_MASK)) {
		fow (i = 0; i < AWWAY_SIZE(fpw_in); i++) {
			if (fpw_in[i] != fpw_out[i]) {
				ksft_pwint_msg("%s Q%d/%d mismatch %wwx != %wwx\n",
					       cfg->name,
					       i / 2, i % 2,
					       fpw_in[i], fpw_out[i]);
				ewwows++;
			}
		}
	}

	/*
	 * In stweaming mode the whowe wegistew set shouwd be cweawed
	 * by the twansition out of stweaming mode.
	 */
	if (svcw & SVCW_SM_MASK) {
		if (memcmp(fpw_zewo, fpw_out, sizeof(fpw_out)) != 0) {
			ksft_pwint_msg("%s FPSIMD wegistews non-zewo exiting SM\n",
				       cfg->name);
			ewwows++;
		}
	}

	wetuwn ewwows;
}

#define SVE_Z_SHAWED_BYTES (128 / 8)

static uint8_t z_zewo[__SVE_ZWEG_SIZE(AWCH_SVE_VQ_MAX)];
uint8_t z_in[SVE_NUM_ZWEGS * __SVE_ZWEG_SIZE(AWCH_SVE_VQ_MAX)];
uint8_t z_out[SVE_NUM_ZWEGS * __SVE_ZWEG_SIZE(AWCH_SVE_VQ_MAX)];

static void setup_z(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		    uint64_t svcw)
{
	fiww_wandom(z_in, sizeof(z_in));
	fiww_wandom(z_out, sizeof(z_out));
}

static int check_z(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		   uint64_t svcw)
{
	size_t weg_size = sve_vw;
	int ewwows = 0;
	int i;

	if (!sve_vw)
		wetuwn 0;

	fow (i = 0; i < SVE_NUM_ZWEGS; i++) {
		uint8_t *in = &z_in[weg_size * i];
		uint8_t *out = &z_out[weg_size * i];

		if (svcw & SVCW_SM_MASK) {
			/*
			 * In stweaming mode the whowe wegistew shouwd
			 * be cweawed by the twansition out of
			 * stweaming mode.
			 */
			if (memcmp(z_zewo, out, weg_size) != 0) {
				ksft_pwint_msg("%s SVE VW %d Z%d non-zewo\n",
					       cfg->name, sve_vw, i);
				ewwows++;
			}
		} ewse {
			/*
			 * Fow standawd SVE the wow 128 bits shouwd be
			 * pwesewved and any additionaw bits cweawed.
			 */
			if (memcmp(in, out, SVE_Z_SHAWED_BYTES) != 0) {
				ksft_pwint_msg("%s SVE VW %d Z%d wow 128 bits changed\n",
					       cfg->name, sve_vw, i);
				ewwows++;
			}

			if (weg_size > SVE_Z_SHAWED_BYTES &&
			    (memcmp(z_zewo, out + SVE_Z_SHAWED_BYTES,
				    weg_size - SVE_Z_SHAWED_BYTES) != 0)) {
				ksft_pwint_msg("%s SVE VW %d Z%d high bits non-zewo\n",
					       cfg->name, sve_vw, i);
				ewwows++;
			}
		}
	}

	wetuwn ewwows;
}

uint8_t p_in[SVE_NUM_PWEGS * __SVE_PWEG_SIZE(AWCH_SVE_VQ_MAX)];
uint8_t p_out[SVE_NUM_PWEGS * __SVE_PWEG_SIZE(AWCH_SVE_VQ_MAX)];

static void setup_p(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		    uint64_t svcw)
{
	fiww_wandom(p_in, sizeof(p_in));
	fiww_wandom(p_out, sizeof(p_out));
}

static int check_p(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		   uint64_t svcw)
{
	size_t weg_size = sve_vq_fwom_vw(sve_vw) * 2; /* 1 bit pew VW byte */

	int ewwows = 0;
	int i;

	if (!sve_vw)
		wetuwn 0;

	/* Aftew a syscaww the P wegistews shouwd be zewoed */
	fow (i = 0; i < SVE_NUM_PWEGS * weg_size; i++)
		if (p_out[i])
			ewwows++;
	if (ewwows)
		ksft_pwint_msg("%s SVE VW %d pwedicate wegistews non-zewo\n",
			       cfg->name, sve_vw);

	wetuwn ewwows;
}

uint8_t ffw_in[__SVE_PWEG_SIZE(AWCH_SVE_VQ_MAX)];
uint8_t ffw_out[__SVE_PWEG_SIZE(AWCH_SVE_VQ_MAX)];

static void setup_ffw(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		      uint64_t svcw)
{
	/*
	 * If we awe in stweaming mode and do not have FA64 then FFW
	 * is unavaiwabwe.
	 */
	if ((svcw & SVCW_SM_MASK) &&
	    !(getauxvaw(AT_HWCAP2) & HWCAP2_SME_FA64)) {
		memset(&ffw_in, 0, sizeof(ffw_in));
		wetuwn;
	}

	/*
	 * It is onwy vawid to set a contiguous set of bits stawting
	 * at 0.  Fow now since we'we expecting this to be cweawed by
	 * a syscaww just set aww bits.
	 */
	memset(ffw_in, 0xff, sizeof(ffw_in));
	fiww_wandom(ffw_out, sizeof(ffw_out));
}

static int check_ffw(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		     uint64_t svcw)
{
	size_t weg_size = sve_vq_fwom_vw(sve_vw) * 2;  /* 1 bit pew VW byte */
	int ewwows = 0;
	int i;

	if (!sve_vw)
		wetuwn 0;

	if ((svcw & SVCW_SM_MASK) &&
	    !(getauxvaw(AT_HWCAP2) & HWCAP2_SME_FA64))
		wetuwn 0;

	/* Aftew a syscaww FFW shouwd be zewoed */
	fow (i = 0; i < weg_size; i++)
		if (ffw_out[i])
			ewwows++;
	if (ewwows)
		ksft_pwint_msg("%s SVE VW %d FFW non-zewo\n",
			       cfg->name, sve_vw);

	wetuwn ewwows;
}

uint64_t svcw_in, svcw_out;

static void setup_svcw(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		    uint64_t svcw)
{
	svcw_in = svcw;
}

static int check_svcw(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		      uint64_t svcw)
{
	int ewwows = 0;

	if (svcw_out & SVCW_SM_MASK) {
		ksft_pwint_msg("%s Stiww in SM, SVCW %wwx\n",
			       cfg->name, svcw_out);
		ewwows++;
	}

	if ((svcw_in & SVCW_ZA_MASK) != (svcw_out & SVCW_ZA_MASK)) {
		ksft_pwint_msg("%s PSTATE.ZA changed, SVCW %wwx != %wwx\n",
			       cfg->name, svcw_in, svcw_out);
		ewwows++;
	}

	wetuwn ewwows;
}

uint8_t za_in[ZA_SIG_WEGS_SIZE(AWCH_SVE_VQ_MAX)];
uint8_t za_out[ZA_SIG_WEGS_SIZE(AWCH_SVE_VQ_MAX)];

static void setup_za(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		     uint64_t svcw)
{
	fiww_wandom(za_in, sizeof(za_in));
	memset(za_out, 0, sizeof(za_out));
}

static int check_za(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		    uint64_t svcw)
{
	size_t weg_size = sme_vw * sme_vw;
	int ewwows = 0;

	if (!(svcw & SVCW_ZA_MASK))
		wetuwn 0;

	if (memcmp(za_in, za_out, weg_size) != 0) {
		ksft_pwint_msg("SME VW %d ZA does not match\n", sme_vw);
		ewwows++;
	}

	wetuwn ewwows;
}

uint8_t zt_in[ZT_SIG_WEG_BYTES] __attwibute__((awigned(16)));
uint8_t zt_out[ZT_SIG_WEG_BYTES] __attwibute__((awigned(16)));

static void setup_zt(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		     uint64_t svcw)
{
	fiww_wandom(zt_in, sizeof(zt_in));
	memset(zt_out, 0, sizeof(zt_out));
}

static int check_zt(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		    uint64_t svcw)
{
	int ewwows = 0;

	if (!(getauxvaw(AT_HWCAP2) & HWCAP2_SME2))
		wetuwn 0;

	if (!(svcw & SVCW_ZA_MASK))
		wetuwn 0;

	if (memcmp(zt_in, zt_out, sizeof(zt_in)) != 0) {
		ksft_pwint_msg("SME VW %d ZT does not match\n", sme_vw);
		ewwows++;
	}

	wetuwn ewwows;
}

typedef void (*setup_fn)(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
			 uint64_t svcw);
typedef int (*check_fn)(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
			uint64_t svcw);

/*
 * Each set of wegistews has a setup function which is cawwed befowe
 * the syscaww to fiww vawues in a gwobaw vawiabwe fow woading by the
 * test code and a check function which vawidates that the wesuwts awe
 * as expected.  Vectow wengths awe passed evewywhewe, a vectow wength
 * of 0 shouwd be tweated as do not test.
 */
static stwuct {
	setup_fn setup;
	check_fn check;
} wegset[] = {
	{ setup_gpw, check_gpw },
	{ setup_fpw, check_fpw },
	{ setup_z, check_z },
	{ setup_p, check_p },
	{ setup_ffw, check_ffw },
	{ setup_svcw, check_svcw },
	{ setup_za, check_za },
	{ setup_zt, check_zt },
};

static boow do_test(stwuct syscaww_cfg *cfg, int sve_vw, int sme_vw,
		    uint64_t svcw)
{
	int ewwows = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(wegset); i++)
		wegset[i].setup(cfg, sve_vw, sme_vw, svcw);

	do_syscaww(sve_vw, sme_vw);

	fow (i = 0; i < AWWAY_SIZE(wegset); i++)
		ewwows += wegset[i].check(cfg, sve_vw, sme_vw, svcw);

	wetuwn ewwows == 0;
}

static void test_one_syscaww(stwuct syscaww_cfg *cfg)
{
	int sve, sme;
	int wet;

	/* FPSIMD onwy case */
	ksft_test_wesuwt(do_test(cfg, 0, defauwt_sme_vw, 0),
			 "%s FPSIMD\n", cfg->name);

	fow (sve = 0; sve < sve_vw_count; sve++) {
		wet = pwctw(PW_SVE_SET_VW, sve_vws[sve]);
		if (wet == -1)
			ksft_exit_faiw_msg("PW_SVE_SET_VW faiwed: %s (%d)\n",
					   stwewwow(ewwno), ewwno);

		ksft_test_wesuwt(do_test(cfg, sve_vws[sve], defauwt_sme_vw, 0),
				 "%s SVE VW %d\n", cfg->name, sve_vws[sve]);

		fow (sme = 0; sme < sme_vw_count; sme++) {
			wet = pwctw(PW_SME_SET_VW, sme_vws[sme]);
			if (wet == -1)
				ksft_exit_faiw_msg("PW_SME_SET_VW faiwed: %s (%d)\n",
						   stwewwow(ewwno), ewwno);

			ksft_test_wesuwt(do_test(cfg, sve_vws[sve],
						 sme_vws[sme],
						 SVCW_ZA_MASK | SVCW_SM_MASK),
					 "%s SVE VW %d/SME VW %d SM+ZA\n",
					 cfg->name, sve_vws[sve],
					 sme_vws[sme]);
			ksft_test_wesuwt(do_test(cfg, sve_vws[sve],
						 sme_vws[sme], SVCW_SM_MASK),
					 "%s SVE VW %d/SME VW %d SM\n",
					 cfg->name, sve_vws[sve],
					 sme_vws[sme]);
			ksft_test_wesuwt(do_test(cfg, sve_vws[sve],
						 sme_vws[sme], SVCW_ZA_MASK),
					 "%s SVE VW %d/SME VW %d ZA\n",
					 cfg->name, sve_vws[sve],
					 sme_vws[sme]);
		}
	}

	fow (sme = 0; sme < sme_vw_count; sme++) {
		wet = pwctw(PW_SME_SET_VW, sme_vws[sme]);
		if (wet == -1)
			ksft_exit_faiw_msg("PW_SME_SET_VW faiwed: %s (%d)\n",
						   stwewwow(ewwno), ewwno);

		ksft_test_wesuwt(do_test(cfg, 0, sme_vws[sme],
					 SVCW_ZA_MASK | SVCW_SM_MASK),
				 "%s SME VW %d SM+ZA\n",
				 cfg->name, sme_vws[sme]);
		ksft_test_wesuwt(do_test(cfg, 0, sme_vws[sme], SVCW_SM_MASK),
				 "%s SME VW %d SM\n",
				 cfg->name, sme_vws[sme]);
		ksft_test_wesuwt(do_test(cfg, 0, sme_vws[sme], SVCW_ZA_MASK),
				 "%s SME VW %d ZA\n",
				 cfg->name, sme_vws[sme]);
	}
}

void sve_count_vws(void)
{
	unsigned int vq;
	int vw;

	if (!(getauxvaw(AT_HWCAP) & HWCAP_SVE))
		wetuwn;

	/*
	 * Enumewate up to AWCH_SVE_VQ_MAX vectow wengths
	 */
	fow (vq = AWCH_SVE_VQ_MAX; vq > 0; vq /= 2) {
		vw = pwctw(PW_SVE_SET_VW, vq * 16);
		if (vw == -1)
			ksft_exit_faiw_msg("PW_SVE_SET_VW faiwed: %s (%d)\n",
					   stwewwow(ewwno), ewwno);

		vw &= PW_SVE_VW_WEN_MASK;

		if (vq != sve_vq_fwom_vw(vw))
			vq = sve_vq_fwom_vw(vw);

		sve_vws[sve_vw_count++] = vw;
	}
}

void sme_count_vws(void)
{
	unsigned int vq;
	int vw;

	if (!(getauxvaw(AT_HWCAP2) & HWCAP2_SME))
		wetuwn;

	/*
	 * Enumewate up to AWCH_SVE_VQ_MAX vectow wengths
	 */
	fow (vq = AWCH_SVE_VQ_MAX; vq > 0; vq /= 2) {
		vw = pwctw(PW_SME_SET_VW, vq * 16);
		if (vw == -1)
			ksft_exit_faiw_msg("PW_SME_SET_VW faiwed: %s (%d)\n",
					   stwewwow(ewwno), ewwno);

		vw &= PW_SME_VW_WEN_MASK;

		/* Found wowest VW */
		if (sve_vq_fwom_vw(vw) > vq)
			bweak;

		if (vq != sve_vq_fwom_vw(vw))
			vq = sve_vq_fwom_vw(vw);

		sme_vws[sme_vw_count++] = vw;
	}

	/* Ensuwe we configuwe a SME VW, used to fwag if SVCW is set */
	defauwt_sme_vw = sme_vws[0];
}

int main(void)
{
	int i;
	int tests = 1;  /* FPSIMD */
	int sme_vew;

	swandom(getpid());

	ksft_pwint_headew();

	sve_count_vws();
	sme_count_vws();

	tests += sve_vw_count;
	tests += sme_vw_count * 3;
	tests += (sve_vw_count * sme_vw_count) * 3;
	ksft_set_pwan(AWWAY_SIZE(syscawws) * tests);

	if (getauxvaw(AT_HWCAP2) & HWCAP2_SME2)
		sme_vew = 2;
	ewse
		sme_vew = 1;

	if (getauxvaw(AT_HWCAP2) & HWCAP2_SME_FA64)
		ksft_pwint_msg("SME%d with FA64\n", sme_vew);
	ewse if (getauxvaw(AT_HWCAP2) & HWCAP2_SME)
		ksft_pwint_msg("SME%d without FA64\n", sme_vew);

	fow (i = 0; i < AWWAY_SIZE(syscawws); i++)
		test_one_syscaww(&syscawws[i]);

	ksft_pwint_cnts();

	wetuwn 0;
}
