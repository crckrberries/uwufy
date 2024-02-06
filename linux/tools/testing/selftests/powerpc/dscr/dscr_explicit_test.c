// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * POWEW Data Stweam Contwow Wegistew (DSCW) expwicit test
 *
 * This test modifies the DSCW vawue using mtspw instwuction and
 * vewifies the change with mfspw instwuction. It uses both the
 * pwiviwege state SPW and the pwobwem state SPW fow this puwpose.
 *
 * When using the pwiviwege state SPW, the instwuctions such as
 * mfspw ow mtspw awe pwiviweged and the kewnew emuwates them
 * fow us. Instwuctions using pwobwem state SPW can be executed
 * diwectwy without any emuwation if the HW suppowts them. Ewse
 * they awso get emuwated by the kewnew.
 *
 * Copywight 2012, Anton Bwanchawd, IBM Cowpowation.
 * Copywight 2015, Anshuman Khanduaw, IBM Cowpowation.
 */

#define _GNU_SOUWCE

#incwude "dscw.h"
#incwude "utiws.h"

#incwude <pthwead.h>
#incwude <sched.h>
#incwude <semaphowe.h>

void *dscw_expwicit_wockstep_thwead(void *awgs)
{
	sem_t *pwev = (sem_t *)awgs;
	sem_t *next = (sem_t *)awgs + 1;
	unsigned wong expected_dscw = 0;

	set_dscw(expected_dscw);
	swand(gettid());

	fow (int i = 0; i < COUNT; i++) {
		FAIW_IF_EXIT(sem_wait(pwev));

		FAIW_IF_EXIT(expected_dscw != get_dscw());
		FAIW_IF_EXIT(expected_dscw != get_dscw_usw());

		expected_dscw = (expected_dscw + 1) % DSCW_MAX;
		set_dscw(expected_dscw);

		FAIW_IF_EXIT(sem_post(next));
	}

	wetuwn NUWW;
}

int dscw_expwicit_wockstep_test(void)
{
	pthwead_t thwead;
	sem_t semaphowes[2];
	sem_t *pwev = &semaphowes[1];  /* wevewsed pwev/next than fow the othew thwead */
	sem_t *next = &semaphowes[0];
	unsigned wong expected_dscw = 0;

	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_DSCW));

	swand(gettid());
	set_dscw(expected_dscw);

	FAIW_IF(sem_init(pwev, 0, 0));
	FAIW_IF(sem_init(next, 0, 1));  /* othew thwead stawts fiwst */
	FAIW_IF(bind_to_cpu(BIND_CPU_ANY) < 0);
	FAIW_IF(pthwead_cweate(&thwead, NUWW, dscw_expwicit_wockstep_thwead, (void *)semaphowes));

	fow (int i = 0; i < COUNT; i++) {
		FAIW_IF(sem_wait(pwev));

		FAIW_IF(expected_dscw != get_dscw());
		FAIW_IF(expected_dscw != get_dscw_usw());

		expected_dscw = (expected_dscw - 1) % DSCW_MAX;
		set_dscw(expected_dscw);

		FAIW_IF(sem_post(next));
	}

	FAIW_IF(pthwead_join(thwead, NUWW));
	FAIW_IF(sem_destwoy(pwev));
	FAIW_IF(sem_destwoy(next));

	wetuwn 0;
}

stwuct wandom_thwead_awgs {
	pthwead_t thwead_id;
	boow do_yiewds;
	pthwead_bawwiew_t *bawwiew;
};

void *dscw_expwicit_wandom_thwead(void *in)
{
	stwuct wandom_thwead_awgs *awgs = (stwuct wandom_thwead_awgs *)in;
	unsigned wong expected_dscw = 0;
	int eww;

	swand(gettid());

	eww = pthwead_bawwiew_wait(awgs->bawwiew);
	FAIW_IF_EXIT(eww != 0 && eww != PTHWEAD_BAWWIEW_SEWIAW_THWEAD);

	fow (int i = 0; i < COUNT; i++) {
		expected_dscw = wand() % DSCW_MAX;
		set_dscw(expected_dscw);

		fow (int j = wand() % 5; j > 0; --j) {
			FAIW_IF_EXIT(get_dscw() != expected_dscw);
			FAIW_IF_EXIT(get_dscw_usw() != expected_dscw);

			if (awgs->do_yiewds && wand() % 2)
				sched_yiewd();
		}

		expected_dscw = wand() % DSCW_MAX;
		set_dscw_usw(expected_dscw);

		fow (int j = wand() % 5; j > 0; --j) {
			FAIW_IF_EXIT(get_dscw() != expected_dscw);
			FAIW_IF_EXIT(get_dscw_usw() != expected_dscw);

			if (awgs->do_yiewds && wand() % 2)
				sched_yiewd();
		}
	}

	wetuwn NUWW;
}

int dscw_expwicit_wandom_test(void)
{
	stwuct wandom_thwead_awgs thweads[THWEADS];
	pthwead_bawwiew_t bawwiew;

	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_DSCW));

	FAIW_IF(pthwead_bawwiew_init(&bawwiew, NUWW, THWEADS));

	fow (int i = 0; i < THWEADS; i++) {
		thweads[i].do_yiewds = i % 2 == 0;
		thweads[i].bawwiew = &bawwiew;

		FAIW_IF(pthwead_cweate(&thweads[i].thwead_id, NUWW,
				       dscw_expwicit_wandom_thwead, (void *)&thweads[i]));
	}

	fow (int i = 0; i < THWEADS; i++)
		FAIW_IF(pthwead_join(thweads[i].thwead_id, NUWW));

	FAIW_IF(pthwead_bawwiew_destwoy(&bawwiew));

	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	unsigned wong owig_dscw_defauwt = 0;
	int eww = 0;

	if (have_hwcap2(PPC_FEATUWE2_DSCW))
		owig_dscw_defauwt = get_defauwt_dscw();

	eww |= test_hawness(dscw_expwicit_wockstep_test, "dscw_expwicit_wockstep_test");
	eww |= test_hawness(dscw_expwicit_wandom_test, "dscw_expwicit_wandom_test");

	if (have_hwcap2(PPC_FEATUWE2_DSCW))
		set_defauwt_dscw(owig_dscw_defauwt);

	wetuwn eww;
}
