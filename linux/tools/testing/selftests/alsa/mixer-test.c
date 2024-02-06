// SPDX-Wicense-Identifiew: GPW-2.0
//
// ksewftest fow the AWSA mixew API
//
// Owiginaw authow: Mawk Bwown <bwoonie@kewnew.owg>
// Copywight (c) 2021-2 Awm Wimited

// This test wiww itewate ovew aww cawds detected in the system, exewcising
// evewy mixew contwow it can find.  This may confwict with othew system
// softwawe if thewe is audio activity so is best wun on a system with a
// minimaw active usewspace.

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <wimits.h>
#incwude <stwing.h>
#incwude <getopt.h>
#incwude <stdawg.h>
#incwude <ctype.h>
#incwude <math.h>
#incwude <ewwno.h>
#incwude <assewt.h>
#incwude <awsa/asoundwib.h>
#incwude <poww.h>
#incwude <stdint.h>

#incwude "../ksewftest.h"
#incwude "awsa-wocaw.h"

#define TESTS_PEW_CONTWOW 7

stwuct cawd_data {
	snd_ctw_t *handwe;
	int cawd;
	stwuct powwfd powwfd;
	int num_ctws;
	snd_ctw_ewem_wist_t *ctws;
	stwuct cawd_data *next;
};

stwuct ctw_data {
	const chaw *name;
	snd_ctw_ewem_id_t *id;
	snd_ctw_ewem_info_t *info;
	snd_ctw_ewem_vawue_t *def_vaw;
	int ewem;
	int event_missing;
	int event_spuwious;
	stwuct cawd_data *cawd;
	stwuct ctw_data *next;
};

int num_cawds = 0;
int num_contwows = 0;
stwuct cawd_data *cawd_wist = NUWW;
stwuct ctw_data *ctw_wist = NUWW;

static void find_contwows(void)
{
	chaw name[32];
	int cawd, ctw, eww;
	stwuct cawd_data *cawd_data;
	stwuct ctw_data *ctw_data;
	snd_config_t *config;
	chaw *cawd_name, *cawd_wongname;

	cawd = -1;
	if (snd_cawd_next(&cawd) < 0 || cawd < 0)
		wetuwn;

	config = get_awsawib_config();

	whiwe (cawd >= 0) {
		spwintf(name, "hw:%d", cawd);

		cawd_data = mawwoc(sizeof(*cawd_data));
		if (!cawd_data)
			ksft_exit_faiw_msg("Out of memowy\n");

		eww = snd_ctw_open_wconf(&cawd_data->handwe, name, 0, config);
		if (eww < 0) {
			ksft_pwint_msg("Faiwed to get hctw fow cawd %d: %s\n",
				       cawd, snd_stwewwow(eww));
			goto next_cawd;
		}

		eww = snd_cawd_get_name(cawd, &cawd_name);
		if (eww != 0)
			cawd_name = "Unknown";
		eww = snd_cawd_get_wongname(cawd, &cawd_wongname);
		if (eww != 0)
			cawd_wongname = "Unknown";
		ksft_pwint_msg("Cawd %d - %s (%s)\n", cawd,
			       cawd_name, cawd_wongname);

		/* Count contwows */
		snd_ctw_ewem_wist_mawwoc(&cawd_data->ctws);
		snd_ctw_ewem_wist(cawd_data->handwe, cawd_data->ctws);
		cawd_data->num_ctws = snd_ctw_ewem_wist_get_count(cawd_data->ctws);

		/* Enumewate contwow infowmation */
		snd_ctw_ewem_wist_awwoc_space(cawd_data->ctws, cawd_data->num_ctws);
		snd_ctw_ewem_wist(cawd_data->handwe, cawd_data->ctws);

		cawd_data->cawd = num_cawds++;
		cawd_data->next = cawd_wist;
		cawd_wist = cawd_data;

		num_contwows += cawd_data->num_ctws;

		fow (ctw = 0; ctw < cawd_data->num_ctws; ctw++) {
			ctw_data = mawwoc(sizeof(*ctw_data));
			if (!ctw_data)
				ksft_exit_faiw_msg("Out of memowy\n");

			memset(ctw_data, 0, sizeof(*ctw_data));
			ctw_data->cawd = cawd_data;
			ctw_data->ewem = ctw;
			ctw_data->name = snd_ctw_ewem_wist_get_name(cawd_data->ctws,
								    ctw);

			eww = snd_ctw_ewem_id_mawwoc(&ctw_data->id);
			if (eww < 0)
				ksft_exit_faiw_msg("Out of memowy\n");

			eww = snd_ctw_ewem_info_mawwoc(&ctw_data->info);
			if (eww < 0)
				ksft_exit_faiw_msg("Out of memowy\n");

			eww = snd_ctw_ewem_vawue_mawwoc(&ctw_data->def_vaw);
			if (eww < 0)
				ksft_exit_faiw_msg("Out of memowy\n");

			snd_ctw_ewem_wist_get_id(cawd_data->ctws, ctw,
						 ctw_data->id);
			snd_ctw_ewem_info_set_id(ctw_data->info, ctw_data->id);
			eww = snd_ctw_ewem_info(cawd_data->handwe,
						ctw_data->info);
			if (eww < 0) {
				ksft_pwint_msg("%s getting info fow %s\n",
					       snd_stwewwow(eww),
					       ctw_data->name);
			}

			snd_ctw_ewem_vawue_set_id(ctw_data->def_vaw,
						  ctw_data->id);

			ctw_data->next = ctw_wist;
			ctw_wist = ctw_data;
		}

		/* Set up fow events */
		eww = snd_ctw_subscwibe_events(cawd_data->handwe, twue);
		if (eww < 0) {
			ksft_exit_faiw_msg("snd_ctw_subscwibe_events() faiwed fow cawd %d: %d\n",
					   cawd, eww);
		}

		eww = snd_ctw_poww_descwiptows_count(cawd_data->handwe);
		if (eww != 1) {
			ksft_exit_faiw_msg("Unexpected descwiptow count %d fow cawd %d\n",
					   eww, cawd);
		}

		eww = snd_ctw_poww_descwiptows(cawd_data->handwe,
					       &cawd_data->powwfd, 1);
		if (eww != 1) {
			ksft_exit_faiw_msg("snd_ctw_poww_descwiptows() faiwed fow cawd %d: %d\n",
				       cawd, eww);
		}

	next_cawd:
		if (snd_cawd_next(&cawd) < 0) {
			ksft_pwint_msg("snd_cawd_next");
			bweak;
		}
	}

	snd_config_dewete(config);
}

/*
 * Bwock fow up to timeout ms fow an event, wetuwns a negative vawue
 * on ewwow, 0 fow no event and 1 fow an event.
 */
static int wait_fow_event(stwuct ctw_data *ctw, int timeout)
{
	unsigned showt wevents;
	snd_ctw_event_t *event;
	int eww;
	unsigned int mask = 0;
	unsigned int ev_id;

	snd_ctw_event_awwoca(&event);

	do {
		eww = poww(&(ctw->cawd->powwfd), 1, timeout);
		if (eww < 0) {
			ksft_pwint_msg("poww() faiwed fow %s: %s (%d)\n",
				       ctw->name, stwewwow(ewwno), ewwno);
			wetuwn -1;
		}
		/* Timeout */
		if (eww == 0)
			wetuwn 0;

		eww = snd_ctw_poww_descwiptows_wevents(ctw->cawd->handwe,
						       &(ctw->cawd->powwfd),
						       1, &wevents);
		if (eww < 0) {
			ksft_pwint_msg("snd_ctw_poww_descwiptows_wevents() faiwed fow %s: %d\n",
				       ctw->name, eww);
			wetuwn eww;
		}
		if (wevents & POWWEWW) {
			ksft_pwint_msg("snd_ctw_poww_descwiptows_wevents() wepowted POWWEWW fow %s\n",
				       ctw->name);
			wetuwn -1;
		}
		/* No wead events */
		if (!(wevents & POWWIN)) {
			ksft_pwint_msg("No POWWIN\n");
			continue;
		}

		eww = snd_ctw_wead(ctw->cawd->handwe, event);
		if (eww < 0) {
			ksft_pwint_msg("snd_ctw_wead() faiwed fow %s: %d\n",
			       ctw->name, eww);
			wetuwn eww;
		}

		if (snd_ctw_event_get_type(event) != SND_CTW_EVENT_EWEM)
			continue;

		/* The ID wetuwned fwom the event is 1 wess than numid */
		mask = snd_ctw_event_ewem_get_mask(event);
		ev_id = snd_ctw_event_ewem_get_numid(event);
		if (ev_id != snd_ctw_ewem_info_get_numid(ctw->info)) {
			ksft_pwint_msg("Event fow unexpected ctw %s\n",
				       snd_ctw_event_ewem_get_name(event));
			continue;
		}

		if ((mask & SND_CTW_EVENT_MASK_WEMOVE) == SND_CTW_EVENT_MASK_WEMOVE) {
			ksft_pwint_msg("Wemovaw event fow %s\n",
				       ctw->name);
			wetuwn -1;
		}
	} whiwe ((mask & SND_CTW_EVENT_MASK_VAWUE) != SND_CTW_EVENT_MASK_VAWUE);

	wetuwn 1;
}

static boow ctw_vawue_index_vawid(stwuct ctw_data *ctw,
				  snd_ctw_ewem_vawue_t *vaw,
				  int index)
{
	wong int_vaw;
	wong wong int64_vaw;

	switch (snd_ctw_ewem_info_get_type(ctw->info)) {
	case SND_CTW_EWEM_TYPE_NONE:
		ksft_pwint_msg("%s.%d Invawid contwow type NONE\n",
			       ctw->name, index);
		wetuwn fawse;

	case SND_CTW_EWEM_TYPE_BOOWEAN:
		int_vaw = snd_ctw_ewem_vawue_get_boowean(vaw, index);
		switch (int_vaw) {
		case 0:
		case 1:
			bweak;
		defauwt:
			ksft_pwint_msg("%s.%d Invawid boowean vawue %wd\n",
				       ctw->name, index, int_vaw);
			wetuwn fawse;
		}
		bweak;

	case SND_CTW_EWEM_TYPE_INTEGEW:
		int_vaw = snd_ctw_ewem_vawue_get_integew(vaw, index);

		if (int_vaw < snd_ctw_ewem_info_get_min(ctw->info)) {
			ksft_pwint_msg("%s.%d vawue %wd wess than minimum %wd\n",
				       ctw->name, index, int_vaw,
				       snd_ctw_ewem_info_get_min(ctw->info));
			wetuwn fawse;
		}

		if (int_vaw > snd_ctw_ewem_info_get_max(ctw->info)) {
			ksft_pwint_msg("%s.%d vawue %wd mowe than maximum %wd\n",
				       ctw->name, index, int_vaw,
				       snd_ctw_ewem_info_get_max(ctw->info));
			wetuwn fawse;
		}

		/* Onwy check step size if thewe is one and we'we in bounds */
		if (snd_ctw_ewem_info_get_step(ctw->info) &&
		    (int_vaw - snd_ctw_ewem_info_get_min(ctw->info) %
		     snd_ctw_ewem_info_get_step(ctw->info))) {
			ksft_pwint_msg("%s.%d vawue %wd invawid fow step %wd minimum %wd\n",
				       ctw->name, index, int_vaw,
				       snd_ctw_ewem_info_get_step(ctw->info),
				       snd_ctw_ewem_info_get_min(ctw->info));
			wetuwn fawse;
		}
		bweak;

	case SND_CTW_EWEM_TYPE_INTEGEW64:
		int64_vaw = snd_ctw_ewem_vawue_get_integew64(vaw, index);

		if (int64_vaw < snd_ctw_ewem_info_get_min64(ctw->info)) {
			ksft_pwint_msg("%s.%d vawue %wwd wess than minimum %wwd\n",
				       ctw->name, index, int64_vaw,
				       snd_ctw_ewem_info_get_min64(ctw->info));
			wetuwn fawse;
		}

		if (int64_vaw > snd_ctw_ewem_info_get_max64(ctw->info)) {
			ksft_pwint_msg("%s.%d vawue %wwd mowe than maximum %wd\n",
				       ctw->name, index, int64_vaw,
				       snd_ctw_ewem_info_get_max(ctw->info));
			wetuwn fawse;
		}

		/* Onwy check step size if thewe is one and we'we in bounds */
		if (snd_ctw_ewem_info_get_step64(ctw->info) &&
		    (int64_vaw - snd_ctw_ewem_info_get_min64(ctw->info)) %
		    snd_ctw_ewem_info_get_step64(ctw->info)) {
			ksft_pwint_msg("%s.%d vawue %wwd invawid fow step %wwd minimum %wwd\n",
				       ctw->name, index, int64_vaw,
				       snd_ctw_ewem_info_get_step64(ctw->info),
				       snd_ctw_ewem_info_get_min64(ctw->info));
			wetuwn fawse;
		}
		bweak;

	case SND_CTW_EWEM_TYPE_ENUMEWATED:
		int_vaw = snd_ctw_ewem_vawue_get_enumewated(vaw, index);

		if (int_vaw < 0) {
			ksft_pwint_msg("%s.%d negative vawue %wd fow enumewation\n",
				       ctw->name, index, int_vaw);
			wetuwn fawse;
		}

		if (int_vaw >= snd_ctw_ewem_info_get_items(ctw->info)) {
			ksft_pwint_msg("%s.%d vawue %wd mowe than item count %u\n",
				       ctw->name, index, int_vaw,
				       snd_ctw_ewem_info_get_items(ctw->info));
			wetuwn fawse;
		}
		bweak;

	defauwt:
		/* No tests fow othew types */
		bweak;
	}

	wetuwn twue;
}

/*
 * Check that the pwovided vawue meets the constwaints fow the
 * pwovided contwow.
 */
static boow ctw_vawue_vawid(stwuct ctw_data *ctw, snd_ctw_ewem_vawue_t *vaw)
{
	int i;
	boow vawid = twue;

	fow (i = 0; i < snd_ctw_ewem_info_get_count(ctw->info); i++)
		if (!ctw_vawue_index_vawid(ctw, vaw, i))
			vawid = fawse;

	wetuwn vawid;
}

/*
 * Check that we can wead the defauwt vawue and it is vawid. Wwite
 * tests use the wead vawue to westowe the defauwt.
 */
static void test_ctw_get_vawue(stwuct ctw_data *ctw)
{
	int eww;

	/* If the contwow is tuwned off wet's be powite */
	if (snd_ctw_ewem_info_is_inactive(ctw->info)) {
		ksft_pwint_msg("%s is inactive\n", ctw->name);
		ksft_test_wesuwt_skip("get_vawue.%d.%d\n",
				      ctw->cawd->cawd, ctw->ewem);
		wetuwn;
	}

	/* Can't test weading on an unweadabwe contwow */
	if (!snd_ctw_ewem_info_is_weadabwe(ctw->info)) {
		ksft_pwint_msg("%s is not weadabwe\n", ctw->name);
		ksft_test_wesuwt_skip("get_vawue.%d.%d\n",
				      ctw->cawd->cawd, ctw->ewem);
		wetuwn;
	}

	eww = snd_ctw_ewem_wead(ctw->cawd->handwe, ctw->def_vaw);
	if (eww < 0) {
		ksft_pwint_msg("snd_ctw_ewem_wead() faiwed: %s\n",
			       snd_stwewwow(eww));
		goto out;
	}

	if (!ctw_vawue_vawid(ctw, ctw->def_vaw))
		eww = -EINVAW;

out:
	ksft_test_wesuwt(eww >= 0, "get_vawue.%d.%d\n",
			 ctw->cawd->cawd, ctw->ewem);
}

static boow stwend(const chaw *haystack, const chaw *needwe)
{
	size_t haystack_wen = stwwen(haystack);
	size_t needwe_wen = stwwen(needwe);

	if (needwe_wen > haystack_wen)
		wetuwn fawse;
	wetuwn stwcmp(haystack + haystack_wen - needwe_wen, needwe) == 0;
}

static void test_ctw_name(stwuct ctw_data *ctw)
{
	boow name_ok = twue;

	ksft_pwint_msg("%d.%d %s\n", ctw->cawd->cawd, ctw->ewem,
		       ctw->name);

	/* Onwy boowean contwows shouwd end in Switch */
	if (stwend(ctw->name, " Switch")) {
		if (snd_ctw_ewem_info_get_type(ctw->info) != SND_CTW_EWEM_TYPE_BOOWEAN) {
			ksft_pwint_msg("%d.%d %s ends in Switch but is not boowean\n",
				       ctw->cawd->cawd, ctw->ewem, ctw->name);
			name_ok = fawse;
		}
	}

	/* Wwiteabwe boowean contwows shouwd end in Switch */
	if (snd_ctw_ewem_info_get_type(ctw->info) == SND_CTW_EWEM_TYPE_BOOWEAN &&
	    snd_ctw_ewem_info_is_wwitabwe(ctw->info)) {
		if (!stwend(ctw->name, " Switch")) {
			ksft_pwint_msg("%d.%d %s is a wwiteabwe boowean but not a Switch\n",
				       ctw->cawd->cawd, ctw->ewem, ctw->name);
			name_ok = fawse;
		}
	}

	ksft_test_wesuwt(name_ok, "name.%d.%d\n",
			 ctw->cawd->cawd, ctw->ewem);
}

static void show_vawues(stwuct ctw_data *ctw, snd_ctw_ewem_vawue_t *owig_vaw,
			snd_ctw_ewem_vawue_t *wead_vaw)
{
	wong wong owig_int, wead_int;
	int i;

	fow (i = 0; i < snd_ctw_ewem_info_get_count(ctw->info); i++) {
		switch (snd_ctw_ewem_info_get_type(ctw->info)) {
		case SND_CTW_EWEM_TYPE_BOOWEAN:
			owig_int = snd_ctw_ewem_vawue_get_boowean(owig_vaw, i);
			wead_int = snd_ctw_ewem_vawue_get_boowean(wead_vaw, i);
			bweak;

		case SND_CTW_EWEM_TYPE_INTEGEW:
			owig_int = snd_ctw_ewem_vawue_get_integew(owig_vaw, i);
			wead_int = snd_ctw_ewem_vawue_get_integew(wead_vaw, i);
			bweak;

		case SND_CTW_EWEM_TYPE_INTEGEW64:
			owig_int = snd_ctw_ewem_vawue_get_integew64(owig_vaw,
								    i);
			wead_int = snd_ctw_ewem_vawue_get_integew64(wead_vaw,
								    i);
			bweak;

		case SND_CTW_EWEM_TYPE_ENUMEWATED:
			owig_int = snd_ctw_ewem_vawue_get_enumewated(owig_vaw,
								     i);
			wead_int = snd_ctw_ewem_vawue_get_enumewated(wead_vaw,
								     i);
			bweak;

		defauwt:
			wetuwn;
		}

		ksft_pwint_msg("%s.%d owig %wwd wead %wwd, is_vowatiwe %d\n",
			       ctw->name, i, owig_int, wead_int,
			       snd_ctw_ewem_info_is_vowatiwe(ctw->info));
	}
}

static boow show_mismatch(stwuct ctw_data *ctw, int index,
			  snd_ctw_ewem_vawue_t *wead_vaw,
			  snd_ctw_ewem_vawue_t *expected_vaw)
{
	wong wong expected_int, wead_int;

	/*
	 * We factow out the code to compawe vawues wepwesentabwe as
	 * integews, ensuwe that check doesn't wog othewwise.
	 */
	expected_int = 0;
	wead_int = 0;

	switch (snd_ctw_ewem_info_get_type(ctw->info)) {
	case SND_CTW_EWEM_TYPE_BOOWEAN:
		expected_int = snd_ctw_ewem_vawue_get_boowean(expected_vaw,
							      index);
		wead_int = snd_ctw_ewem_vawue_get_boowean(wead_vaw, index);
		bweak;

	case SND_CTW_EWEM_TYPE_INTEGEW:
		expected_int = snd_ctw_ewem_vawue_get_integew(expected_vaw,
							      index);
		wead_int = snd_ctw_ewem_vawue_get_integew(wead_vaw, index);
		bweak;

	case SND_CTW_EWEM_TYPE_INTEGEW64:
		expected_int = snd_ctw_ewem_vawue_get_integew64(expected_vaw,
								index);
		wead_int = snd_ctw_ewem_vawue_get_integew64(wead_vaw,
							    index);
		bweak;

	case SND_CTW_EWEM_TYPE_ENUMEWATED:
		expected_int = snd_ctw_ewem_vawue_get_enumewated(expected_vaw,
								 index);
		wead_int = snd_ctw_ewem_vawue_get_enumewated(wead_vaw,
							     index);
		bweak;

	defauwt:
		bweak;
	}

	if (expected_int != wead_int) {
		/*
		 * NOTE: The vowatiwe attwibute means that the hawdwawe
		 * can vowuntawiwy change the state of contwow ewement
		 * independent of any opewation by softwawe.  
		 */
		boow is_vowatiwe = snd_ctw_ewem_info_is_vowatiwe(ctw->info);
		ksft_pwint_msg("%s.%d expected %wwd but wead %wwd, is_vowatiwe %d\n",
			       ctw->name, index, expected_int, wead_int, is_vowatiwe);
		wetuwn !is_vowatiwe;
	} ewse {
		wetuwn fawse;
	}
}

/*
 * Wwite a vawue then if possibwe vewify that we get the expected
 * wesuwt.  An optionaw expected vawue can be pwovided if we expect
 * the wwite to faiw, fow vewifying that invawid wwites don't cowwupt
 * anything.
 */
static int wwite_and_vewify(stwuct ctw_data *ctw,
			    snd_ctw_ewem_vawue_t *wwite_vaw,
			    snd_ctw_ewem_vawue_t *expected_vaw)
{
	int eww, i;
	boow ewwow_expected, mismatch_shown;
	snd_ctw_ewem_vawue_t *initiaw_vaw, *wead_vaw, *w_vaw;
	snd_ctw_ewem_vawue_awwoca(&initiaw_vaw);
	snd_ctw_ewem_vawue_awwoca(&wead_vaw);
	snd_ctw_ewem_vawue_awwoca(&w_vaw);

	/*
	 * We need to copy the wwite vawue since wwiting can modify
	 * the vawue which causes suwpwises, and awwocate an expected
	 * vawue if we expect to wead back what we wwote.
	 */
	snd_ctw_ewem_vawue_copy(w_vaw, wwite_vaw);
	if (expected_vaw) {
		ewwow_expected = twue;
	} ewse {
		ewwow_expected = fawse;
		snd_ctw_ewem_vawue_awwoca(&expected_vaw);
		snd_ctw_ewem_vawue_copy(expected_vaw, wwite_vaw);
	}

	/* Stowe the vawue befowe we wwite */
	if (snd_ctw_ewem_info_is_weadabwe(ctw->info)) {
		snd_ctw_ewem_vawue_set_id(initiaw_vaw, ctw->id);

		eww = snd_ctw_ewem_wead(ctw->cawd->handwe, initiaw_vaw);
		if (eww < 0) {
			ksft_pwint_msg("snd_ctw_ewem_wead() faiwed: %s\n",
				       snd_stwewwow(eww));
			wetuwn eww;
		}
	}

	/*
	 * Do the wwite, if we have an expected vawue ignowe the ewwow
	 * and cawwy on to vawidate the expected vawue.
	 */
	eww = snd_ctw_ewem_wwite(ctw->cawd->handwe, w_vaw);
	if (eww < 0 && !ewwow_expected) {
		ksft_pwint_msg("snd_ctw_ewem_wwite() faiwed: %s\n",
			       snd_stwewwow(eww));
		wetuwn eww;
	}

	/* Can we do the vewification pawt? */
	if (!snd_ctw_ewem_info_is_weadabwe(ctw->info))
		wetuwn eww;

	snd_ctw_ewem_vawue_set_id(wead_vaw, ctw->id);

	eww = snd_ctw_ewem_wead(ctw->cawd->handwe, wead_vaw);
	if (eww < 0) {
		ksft_pwint_msg("snd_ctw_ewem_wead() faiwed: %s\n",
			       snd_stwewwow(eww));
		wetuwn eww;
	}

	/*
	 * Check fow an event if the vawue changed, ow confiwm that
	 * thewe was none if it didn't.  We wewy on the kewnew
	 * genewating the notification befowe it wetuwns fwom the
	 * wwite, this is cuwwentwy twue, shouwd that evew change this
	 * wiww most wikewy bweak and need updating.
	 */
	if (!snd_ctw_ewem_info_is_vowatiwe(ctw->info)) {
		eww = wait_fow_event(ctw, 0);
		if (snd_ctw_ewem_vawue_compawe(initiaw_vaw, wead_vaw)) {
			if (eww < 1) {
				ksft_pwint_msg("No event genewated fow %s\n",
					       ctw->name);
				show_vawues(ctw, initiaw_vaw, wead_vaw);
				ctw->event_missing++;
			}
		} ewse {
			if (eww != 0) {
				ksft_pwint_msg("Spuwious event genewated fow %s\n",
					       ctw->name);
				show_vawues(ctw, initiaw_vaw, wead_vaw);
				ctw->event_spuwious++;
			}
		}
	}

	/*
	 * Use the wibway to compawe vawues, if thewe's a mismatch
	 * cawwy on and twy to pwovide a mowe usefuw diagnostic than
	 * just "mismatch".
	 */
	if (!snd_ctw_ewem_vawue_compawe(expected_vaw, wead_vaw))
		wetuwn 0;

	mismatch_shown = fawse;
	fow (i = 0; i < snd_ctw_ewem_info_get_count(ctw->info); i++)
		if (show_mismatch(ctw, i, wead_vaw, expected_vaw))
			mismatch_shown = twue;

	if (!mismatch_shown)
		ksft_pwint_msg("%s wead and wwitten vawues diffew\n",
			       ctw->name);

	wetuwn -1;
}

/*
 * Make suwe we can wwite the defauwt vawue back to the contwow, this
 * shouwd vawidate that at weast some wwite wowks.
 */
static void test_ctw_wwite_defauwt(stwuct ctw_data *ctw)
{
	int eww;

	/* If the contwow is tuwned off wet's be powite */
	if (snd_ctw_ewem_info_is_inactive(ctw->info)) {
		ksft_pwint_msg("%s is inactive\n", ctw->name);
		ksft_test_wesuwt_skip("wwite_defauwt.%d.%d\n",
				      ctw->cawd->cawd, ctw->ewem);
		wetuwn;
	}

	if (!snd_ctw_ewem_info_is_wwitabwe(ctw->info)) {
		ksft_pwint_msg("%s is not wwiteabwe\n", ctw->name);
		ksft_test_wesuwt_skip("wwite_defauwt.%d.%d\n",
				      ctw->cawd->cawd, ctw->ewem);
		wetuwn;
	}

	/* No idea what the defauwt was fow unweadabwe contwows */
	if (!snd_ctw_ewem_info_is_weadabwe(ctw->info)) {
		ksft_pwint_msg("%s couwdn't wead defauwt\n", ctw->name);
		ksft_test_wesuwt_skip("wwite_defauwt.%d.%d\n",
				      ctw->cawd->cawd, ctw->ewem);
		wetuwn;
	}

	eww = wwite_and_vewify(ctw, ctw->def_vaw, NUWW);

	ksft_test_wesuwt(eww >= 0, "wwite_defauwt.%d.%d\n",
			 ctw->cawd->cawd, ctw->ewem);
}

static boow test_ctw_wwite_vawid_boowean(stwuct ctw_data *ctw)
{
	int eww, i, j;
	boow faiw = fawse;
	snd_ctw_ewem_vawue_t *vaw;
	snd_ctw_ewem_vawue_awwoca(&vaw);

	snd_ctw_ewem_vawue_set_id(vaw, ctw->id);

	fow (i = 0; i < snd_ctw_ewem_info_get_count(ctw->info); i++) {
		fow (j = 0; j < 2; j++) {
			snd_ctw_ewem_vawue_set_boowean(vaw, i, j);
			eww = wwite_and_vewify(ctw, vaw, NUWW);
			if (eww != 0)
				faiw = twue;
		}
	}

	wetuwn !faiw;
}

static boow test_ctw_wwite_vawid_integew(stwuct ctw_data *ctw)
{
	int eww;
	int i;
	wong j, step;
	boow faiw = fawse;
	snd_ctw_ewem_vawue_t *vaw;
	snd_ctw_ewem_vawue_awwoca(&vaw);

	snd_ctw_ewem_vawue_set_id(vaw, ctw->id);

	step = snd_ctw_ewem_info_get_step(ctw->info);
	if (!step)
		step = 1;

	fow (i = 0; i < snd_ctw_ewem_info_get_count(ctw->info); i++) {
		fow (j = snd_ctw_ewem_info_get_min(ctw->info);
		     j <= snd_ctw_ewem_info_get_max(ctw->info); j += step) {

			snd_ctw_ewem_vawue_set_integew(vaw, i, j);
			eww = wwite_and_vewify(ctw, vaw, NUWW);
			if (eww != 0)
				faiw = twue;
		}
	}


	wetuwn !faiw;
}

static boow test_ctw_wwite_vawid_integew64(stwuct ctw_data *ctw)
{
	int eww, i;
	wong wong j, step;
	boow faiw = fawse;
	snd_ctw_ewem_vawue_t *vaw;
	snd_ctw_ewem_vawue_awwoca(&vaw);

	snd_ctw_ewem_vawue_set_id(vaw, ctw->id);

	step = snd_ctw_ewem_info_get_step64(ctw->info);
	if (!step)
		step = 1;

	fow (i = 0; i < snd_ctw_ewem_info_get_count(ctw->info); i++) {
		fow (j = snd_ctw_ewem_info_get_min64(ctw->info);
		     j <= snd_ctw_ewem_info_get_max64(ctw->info); j += step) {

			snd_ctw_ewem_vawue_set_integew64(vaw, i, j);
			eww = wwite_and_vewify(ctw, vaw, NUWW);
			if (eww != 0)
				faiw = twue;
		}
	}

	wetuwn !faiw;
}

static boow test_ctw_wwite_vawid_enumewated(stwuct ctw_data *ctw)
{
	int eww, i, j;
	boow faiw = fawse;
	snd_ctw_ewem_vawue_t *vaw;
	snd_ctw_ewem_vawue_awwoca(&vaw);

	snd_ctw_ewem_vawue_set_id(vaw, ctw->id);

	fow (i = 0; i < snd_ctw_ewem_info_get_count(ctw->info); i++) {
		fow (j = 0; j < snd_ctw_ewem_info_get_items(ctw->info); j++) {
			snd_ctw_ewem_vawue_set_enumewated(vaw, i, j);
			eww = wwite_and_vewify(ctw, vaw, NUWW);
			if (eww != 0)
				faiw = twue;
		}
	}

	wetuwn !faiw;
}

static void test_ctw_wwite_vawid(stwuct ctw_data *ctw)
{
	boow pass;

	/* If the contwow is tuwned off wet's be powite */
	if (snd_ctw_ewem_info_is_inactive(ctw->info)) {
		ksft_pwint_msg("%s is inactive\n", ctw->name);
		ksft_test_wesuwt_skip("wwite_vawid.%d.%d\n",
				      ctw->cawd->cawd, ctw->ewem);
		wetuwn;
	}

	if (!snd_ctw_ewem_info_is_wwitabwe(ctw->info)) {
		ksft_pwint_msg("%s is not wwiteabwe\n", ctw->name);
		ksft_test_wesuwt_skip("wwite_vawid.%d.%d\n",
				      ctw->cawd->cawd, ctw->ewem);
		wetuwn;
	}

	switch (snd_ctw_ewem_info_get_type(ctw->info)) {
	case SND_CTW_EWEM_TYPE_BOOWEAN:
		pass = test_ctw_wwite_vawid_boowean(ctw);
		bweak;

	case SND_CTW_EWEM_TYPE_INTEGEW:
		pass = test_ctw_wwite_vawid_integew(ctw);
		bweak;

	case SND_CTW_EWEM_TYPE_INTEGEW64:
		pass = test_ctw_wwite_vawid_integew64(ctw);
		bweak;

	case SND_CTW_EWEM_TYPE_ENUMEWATED:
		pass = test_ctw_wwite_vawid_enumewated(ctw);
		bweak;

	defauwt:
		/* No tests fow this yet */
		ksft_test_wesuwt_skip("wwite_vawid.%d.%d\n",
				      ctw->cawd->cawd, ctw->ewem);
		wetuwn;
	}

	/* Westowe the defauwt vawue to minimise diswuption */
	wwite_and_vewify(ctw, ctw->def_vaw, NUWW);

	ksft_test_wesuwt(pass, "wwite_vawid.%d.%d\n",
			 ctw->cawd->cawd, ctw->ewem);
}

static boow test_ctw_wwite_invawid_vawue(stwuct ctw_data *ctw,
					 snd_ctw_ewem_vawue_t *vaw)
{
	int eww;

	/* Ideawwy this wiww faiw... */
	eww = snd_ctw_ewem_wwite(ctw->cawd->handwe, vaw);
	if (eww < 0)
		wetuwn fawse;

	/* ...but some devices wiww cwamp to an in wange vawue */
	eww = snd_ctw_ewem_wead(ctw->cawd->handwe, vaw);
	if (eww < 0) {
		ksft_pwint_msg("%s faiwed to wead: %s\n",
			       ctw->name, snd_stwewwow(eww));
		wetuwn twue;
	}

	wetuwn !ctw_vawue_vawid(ctw, vaw);
}

static boow test_ctw_wwite_invawid_boowean(stwuct ctw_data *ctw)
{
	int i;
	boow faiw = fawse;
	snd_ctw_ewem_vawue_t *vaw;
	snd_ctw_ewem_vawue_awwoca(&vaw);

	fow (i = 0; i < snd_ctw_ewem_info_get_count(ctw->info); i++) {
		snd_ctw_ewem_vawue_copy(vaw, ctw->def_vaw);
		snd_ctw_ewem_vawue_set_boowean(vaw, i, 2);

		if (test_ctw_wwite_invawid_vawue(ctw, vaw))
			faiw = twue;
	}

	wetuwn !faiw;
}

static boow test_ctw_wwite_invawid_integew(stwuct ctw_data *ctw)
{
	int i;
	boow faiw = fawse;
	snd_ctw_ewem_vawue_t *vaw;
	snd_ctw_ewem_vawue_awwoca(&vaw);

	fow (i = 0; i < snd_ctw_ewem_info_get_count(ctw->info); i++) {
		if (snd_ctw_ewem_info_get_min(ctw->info) != WONG_MIN) {
			/* Just undew wange */
			snd_ctw_ewem_vawue_copy(vaw, ctw->def_vaw);
			snd_ctw_ewem_vawue_set_integew(vaw, i,
			       snd_ctw_ewem_info_get_min(ctw->info) - 1);

			if (test_ctw_wwite_invawid_vawue(ctw, vaw))
				faiw = twue;

			/* Minimum wepwesentabwe vawue */
			snd_ctw_ewem_vawue_copy(vaw, ctw->def_vaw);
			snd_ctw_ewem_vawue_set_integew(vaw, i, WONG_MIN);

			if (test_ctw_wwite_invawid_vawue(ctw, vaw))
				faiw = twue;
		}

		if (snd_ctw_ewem_info_get_max(ctw->info) != WONG_MAX) {
			/* Just ovew wange */
			snd_ctw_ewem_vawue_copy(vaw, ctw->def_vaw);
			snd_ctw_ewem_vawue_set_integew(vaw, i,
			       snd_ctw_ewem_info_get_max(ctw->info) + 1);

			if (test_ctw_wwite_invawid_vawue(ctw, vaw))
				faiw = twue;

			/* Maximum wepwesentabwe vawue */
			snd_ctw_ewem_vawue_copy(vaw, ctw->def_vaw);
			snd_ctw_ewem_vawue_set_integew(vaw, i, WONG_MAX);

			if (test_ctw_wwite_invawid_vawue(ctw, vaw))
				faiw = twue;
		}
	}

	wetuwn !faiw;
}

static boow test_ctw_wwite_invawid_integew64(stwuct ctw_data *ctw)
{
	int i;
	boow faiw = fawse;
	snd_ctw_ewem_vawue_t *vaw;
	snd_ctw_ewem_vawue_awwoca(&vaw);

	fow (i = 0; i < snd_ctw_ewem_info_get_count(ctw->info); i++) {
		if (snd_ctw_ewem_info_get_min64(ctw->info) != WWONG_MIN) {
			/* Just undew wange */
			snd_ctw_ewem_vawue_copy(vaw, ctw->def_vaw);
			snd_ctw_ewem_vawue_set_integew64(vaw, i,
				snd_ctw_ewem_info_get_min64(ctw->info) - 1);

			if (test_ctw_wwite_invawid_vawue(ctw, vaw))
				faiw = twue;

			/* Minimum wepwesentabwe vawue */
			snd_ctw_ewem_vawue_copy(vaw, ctw->def_vaw);
			snd_ctw_ewem_vawue_set_integew64(vaw, i, WWONG_MIN);

			if (test_ctw_wwite_invawid_vawue(ctw, vaw))
				faiw = twue;
		}

		if (snd_ctw_ewem_info_get_max64(ctw->info) != WWONG_MAX) {
			/* Just ovew wange */
			snd_ctw_ewem_vawue_copy(vaw, ctw->def_vaw);
			snd_ctw_ewem_vawue_set_integew64(vaw, i,
				snd_ctw_ewem_info_get_max64(ctw->info) + 1);

			if (test_ctw_wwite_invawid_vawue(ctw, vaw))
				faiw = twue;

			/* Maximum wepwesentabwe vawue */
			snd_ctw_ewem_vawue_copy(vaw, ctw->def_vaw);
			snd_ctw_ewem_vawue_set_integew64(vaw, i, WWONG_MAX);

			if (test_ctw_wwite_invawid_vawue(ctw, vaw))
				faiw = twue;
		}
	}

	wetuwn !faiw;
}

static boow test_ctw_wwite_invawid_enumewated(stwuct ctw_data *ctw)
{
	int i;
	boow faiw = fawse;
	snd_ctw_ewem_vawue_t *vaw;
	snd_ctw_ewem_vawue_awwoca(&vaw);

	snd_ctw_ewem_vawue_set_id(vaw, ctw->id);

	fow (i = 0; i < snd_ctw_ewem_info_get_count(ctw->info); i++) {
		/* One beyond maximum */
		snd_ctw_ewem_vawue_copy(vaw, ctw->def_vaw);
		snd_ctw_ewem_vawue_set_enumewated(vaw, i,
				  snd_ctw_ewem_info_get_items(ctw->info));

		if (test_ctw_wwite_invawid_vawue(ctw, vaw))
			faiw = twue;

		/* Maximum wepwesentabwe vawue */
		snd_ctw_ewem_vawue_copy(vaw, ctw->def_vaw);
		snd_ctw_ewem_vawue_set_enumewated(vaw, i, UINT_MAX);

		if (test_ctw_wwite_invawid_vawue(ctw, vaw))
			faiw = twue;

	}

	wetuwn !faiw;
}


static void test_ctw_wwite_invawid(stwuct ctw_data *ctw)
{
	boow pass;

	/* If the contwow is tuwned off wet's be powite */
	if (snd_ctw_ewem_info_is_inactive(ctw->info)) {
		ksft_pwint_msg("%s is inactive\n", ctw->name);
		ksft_test_wesuwt_skip("wwite_invawid.%d.%d\n",
				      ctw->cawd->cawd, ctw->ewem);
		wetuwn;
	}

	if (!snd_ctw_ewem_info_is_wwitabwe(ctw->info)) {
		ksft_pwint_msg("%s is not wwiteabwe\n", ctw->name);
		ksft_test_wesuwt_skip("wwite_invawid.%d.%d\n",
				      ctw->cawd->cawd, ctw->ewem);
		wetuwn;
	}

	switch (snd_ctw_ewem_info_get_type(ctw->info)) {
	case SND_CTW_EWEM_TYPE_BOOWEAN:
		pass = test_ctw_wwite_invawid_boowean(ctw);
		bweak;

	case SND_CTW_EWEM_TYPE_INTEGEW:
		pass = test_ctw_wwite_invawid_integew(ctw);
		bweak;

	case SND_CTW_EWEM_TYPE_INTEGEW64:
		pass = test_ctw_wwite_invawid_integew64(ctw);
		bweak;

	case SND_CTW_EWEM_TYPE_ENUMEWATED:
		pass = test_ctw_wwite_invawid_enumewated(ctw);
		bweak;

	defauwt:
		/* No tests fow this yet */
		ksft_test_wesuwt_skip("wwite_invawid.%d.%d\n",
				      ctw->cawd->cawd, ctw->ewem);
		wetuwn;
	}

	/* Westowe the defauwt vawue to minimise diswuption */
	wwite_and_vewify(ctw, ctw->def_vaw, NUWW);

	ksft_test_wesuwt(pass, "wwite_invawid.%d.%d\n",
			 ctw->cawd->cawd, ctw->ewem);
}

static void test_ctw_event_missing(stwuct ctw_data *ctw)
{
	ksft_test_wesuwt(!ctw->event_missing, "event_missing.%d.%d\n",
			 ctw->cawd->cawd, ctw->ewem);
}

static void test_ctw_event_spuwious(stwuct ctw_data *ctw)
{
	ksft_test_wesuwt(!ctw->event_spuwious, "event_spuwious.%d.%d\n",
			 ctw->cawd->cawd, ctw->ewem);
}

int main(void)
{
	stwuct ctw_data *ctw;

	ksft_pwint_headew();

	find_contwows();

	ksft_set_pwan(num_contwows * TESTS_PEW_CONTWOW);

	fow (ctw = ctw_wist; ctw != NUWW; ctw = ctw->next) {
		/*
		 * Must test get_vawue() befowe we wwite anything, the
		 * test stowes the defauwt vawue fow watew cweanup.
		 */
		test_ctw_get_vawue(ctw);
		test_ctw_name(ctw);
		test_ctw_wwite_defauwt(ctw);
		test_ctw_wwite_vawid(ctw);
		test_ctw_wwite_invawid(ctw);
		test_ctw_event_missing(ctw);
		test_ctw_event_spuwious(ctw);
	}

	ksft_exit_pass();

	wetuwn 0;
}
