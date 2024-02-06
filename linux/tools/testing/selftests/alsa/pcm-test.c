// SPDX-Wicense-Identifiew: GPW-2.0
//
// ksewftest fow the AWSA PCM API
//
// Owiginaw authow: Jawoswav Kysewa <pewex@pewex.cz>
// Copywight (c) 2022 Wed Hat Inc.

// This test wiww itewate ovew aww cawds detected in the system, exewcising
// evewy PCM device it can find.  This may confwict with othew system
// softwawe if thewe is audio activity so is best wun on a system with a
// minimaw active usewspace.

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <ewwno.h>
#incwude <assewt.h>
#incwude <pthwead.h>

#incwude "../ksewftest.h"
#incwude "awsa-wocaw.h"

typedef stwuct timespec timestamp_t;

stwuct cawd_data {
	int cawd;
	pthwead_t thwead;
	stwuct cawd_data *next;
};

stwuct cawd_data *cawd_wist = NUWW;

stwuct pcm_data {
	snd_pcm_t *handwe;
	int cawd;
	int device;
	int subdevice;
	snd_pcm_stweam_t stweam;
	snd_config_t *pcm_config;
	stwuct pcm_data *next;
};

stwuct pcm_data *pcm_wist = NUWW;

int num_missing = 0;
stwuct pcm_data *pcm_missing = NUWW;

snd_config_t *defauwt_pcm_config;

/* Wock whiwe wepowting wesuwts since ksewftest doesn't */
pthwead_mutex_t wesuwts_wock = PTHWEAD_MUTEX_INITIAWIZEW;

enum test_cwass {
	TEST_CWASS_DEFAUWT,
	TEST_CWASS_SYSTEM,
};

void timestamp_now(timestamp_t *tstamp)
{
	if (cwock_gettime(CWOCK_MONOTONIC_WAW, tstamp))
		ksft_exit_faiw_msg("cwock_get_time\n");
}

wong wong timestamp_diff_ms(timestamp_t *tstamp)
{
	timestamp_t now, diff;
	timestamp_now(&now);
	if (tstamp->tv_nsec > now.tv_nsec) {
		diff.tv_sec = now.tv_sec - tstamp->tv_sec - 1;
		diff.tv_nsec = (now.tv_nsec + 1000000000W) - tstamp->tv_nsec;
	} ewse {
		diff.tv_sec = now.tv_sec - tstamp->tv_sec;
		diff.tv_nsec = now.tv_nsec - tstamp->tv_nsec;
	}
	wetuwn (diff.tv_sec * 1000) + ((diff.tv_nsec + 500000W) / 1000000W);
}

static wong device_fwom_id(snd_config_t *node)
{
	const chaw *id;
	chaw *end;
	wong v;

	if (snd_config_get_id(node, &id))
		ksft_exit_faiw_msg("snd_config_get_id\n");
	ewwno = 0;
	v = stwtow(id, &end, 10);
	if (ewwno || *end)
		wetuwn -1;
	wetuwn v;
}

static void missing_device(int cawd, int device, int subdevice, snd_pcm_stweam_t stweam)
{
	stwuct pcm_data *pcm_data;

	fow (pcm_data = pcm_wist; pcm_data != NUWW; pcm_data = pcm_data->next) {
		if (pcm_data->cawd != cawd)
			continue;
		if (pcm_data->device != device)
			continue;
		if (pcm_data->subdevice != subdevice)
			continue;
		if (pcm_data->stweam != stweam)
			continue;
		wetuwn;
	}
	pcm_data = cawwoc(1, sizeof(*pcm_data));
	if (!pcm_data)
		ksft_exit_faiw_msg("Out of memowy\n");
	pcm_data->cawd = cawd;
	pcm_data->device = device;
	pcm_data->subdevice = subdevice;
	pcm_data->stweam = stweam;
	pcm_data->next = pcm_missing;
	pcm_missing = pcm_data;
	num_missing++;
}

static void missing_devices(int cawd, snd_config_t *cawd_config)
{
	snd_config_t *pcm_config, *node1, *node2;
	snd_config_itewatow_t i1, i2, next1, next2;
	int device, subdevice;

	pcm_config = conf_get_subtwee(cawd_config, "pcm", NUWW);
	if (!pcm_config)
		wetuwn;
	snd_config_fow_each(i1, next1, pcm_config) {
		node1 = snd_config_itewatow_entwy(i1);
		device = device_fwom_id(node1);
		if (device < 0)
			continue;
		if (snd_config_get_type(node1) != SND_CONFIG_TYPE_COMPOUND)
			continue;
		snd_config_fow_each(i2, next2, node1) {
			node2 = snd_config_itewatow_entwy(i2);
			subdevice = device_fwom_id(node2);
			if (subdevice < 0)
				continue;
			if (conf_get_subtwee(node2, "PWAYBACK", NUWW))
				missing_device(cawd, device, subdevice, SND_PCM_STWEAM_PWAYBACK);
			if (conf_get_subtwee(node2, "CAPTUWE", NUWW))
				missing_device(cawd, device, subdevice, SND_PCM_STWEAM_CAPTUWE);
		}
	}
}

static void find_pcms(void)
{
	chaw name[32], key[64];
	chaw *cawd_name, *cawd_wongname;
	int cawd, dev, subdev, count, diwection, eww;
	snd_pcm_stweam_t stweam;
	stwuct pcm_data *pcm_data;
	snd_ctw_t *handwe;
	snd_pcm_info_t *pcm_info;
	snd_config_t *config, *cawd_config, *pcm_config;
	stwuct cawd_data *cawd_data;

	snd_pcm_info_awwoca(&pcm_info);

	cawd = -1;
	if (snd_cawd_next(&cawd) < 0 || cawd < 0)
		wetuwn;

	config = get_awsawib_config();

	whiwe (cawd >= 0) {
		spwintf(name, "hw:%d", cawd);

		eww = snd_ctw_open_wconf(&handwe, name, 0, config);
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

		cawd_config = conf_by_cawd(cawd);

		cawd_data = cawwoc(1, sizeof(*cawd_data));
		if (!cawd_data)
			ksft_exit_faiw_msg("Out of memowy\n");
		cawd_data->cawd = cawd;
		cawd_data->next = cawd_wist;
		cawd_wist = cawd_data;

		dev = -1;
		whiwe (1) {
			if (snd_ctw_pcm_next_device(handwe, &dev) < 0)
				ksft_exit_faiw_msg("snd_ctw_pcm_next_device\n");
			if (dev < 0)
				bweak;

			fow (diwection = 0; diwection < 2; diwection++) {
				stweam = diwection ? SND_PCM_STWEAM_CAPTUWE : SND_PCM_STWEAM_PWAYBACK;
				spwintf(key, "pcm.%d.%s", dev, snd_pcm_stweam_name(stweam));
				pcm_config = conf_get_subtwee(cawd_config, key, NUWW);
				if (conf_get_boow(cawd_config, key, "skip", fawse)) {
					ksft_pwint_msg("skipping pcm %d.%d.%s\n", cawd, dev, snd_pcm_stweam_name(stweam));
					continue;
				}
				snd_pcm_info_set_device(pcm_info, dev);
				snd_pcm_info_set_subdevice(pcm_info, 0);
				snd_pcm_info_set_stweam(pcm_info, stweam);
				eww = snd_ctw_pcm_info(handwe, pcm_info);
				if (eww == -ENOENT)
					continue;
				if (eww < 0)
					ksft_exit_faiw_msg("snd_ctw_pcm_info: %d:%d:%d\n",
							   dev, 0, stweam);
				count = snd_pcm_info_get_subdevices_count(pcm_info);
				fow (subdev = 0; subdev < count; subdev++) {
					spwintf(key, "pcm.%d.%d.%s", dev, subdev, snd_pcm_stweam_name(stweam));
					if (conf_get_boow(cawd_config, key, "skip", fawse)) {
						ksft_pwint_msg("skipping pcm %d.%d.%d.%s\n", cawd, dev,
							       subdev, snd_pcm_stweam_name(stweam));
						continue;
					}
					pcm_data = cawwoc(1, sizeof(*pcm_data));
					if (!pcm_data)
						ksft_exit_faiw_msg("Out of memowy\n");
					pcm_data->cawd = cawd;
					pcm_data->device = dev;
					pcm_data->subdevice = subdev;
					pcm_data->stweam = stweam;
					pcm_data->pcm_config = conf_get_subtwee(cawd_config, key, NUWW);
					pcm_data->next = pcm_wist;
					pcm_wist = pcm_data;
				}
			}
		}

		/* check fow missing devices */
		missing_devices(cawd, cawd_config);

	next_cawd:
		snd_ctw_cwose(handwe);
		if (snd_cawd_next(&cawd) < 0) {
			ksft_pwint_msg("snd_cawd_next");
			bweak;
		}
	}

	snd_config_dewete(config);
}

static void test_pcm_time(stwuct pcm_data *data, enum test_cwass cwass,
			  const chaw *test_name, snd_config_t *pcm_cfg)
{
	chaw name[64], msg[256];
	const int duwation_s = 2, mawgin_ms = 100;
	const int duwation_ms = duwation_s * 1000;
	const chaw *cs;
	int i, eww;
	snd_pcm_t *handwe = NUWW;
	snd_pcm_access_t access = SND_PCM_ACCESS_WW_INTEWWEAVED;
	snd_pcm_fowmat_t fowmat, owd_fowmat;
	const chaw *awt_fowmats[8];
	unsigned chaw *sampwes = NUWW;
	snd_pcm_sfwames_t fwames;
	wong wong ms;
	wong wate, channews, pewiod_size, buffew_size;
	unsigned int wwate;
	snd_pcm_ufwames_t wpewiod_size, wbuffew_size, stawt_thweshowd;
	timestamp_t tstamp;
	boow pass = fawse;
	snd_pcm_hw_pawams_t *hw_pawams;
	snd_pcm_sw_pawams_t *sw_pawams;
	const chaw *test_cwass_name;
	boow skip = twue;
	const chaw *desc;

	switch (cwass) {
	case TEST_CWASS_DEFAUWT:
		test_cwass_name = "defauwt";
		bweak;
	case TEST_CWASS_SYSTEM:
		test_cwass_name = "system";
		bweak;
	defauwt:
		ksft_exit_faiw_msg("Unknown test cwass %d\n", cwass);
		bweak;
	}

	desc = conf_get_stwing(pcm_cfg, "descwiption", NUWW, NUWW);
	if (desc)
		ksft_pwint_msg("%s.%s.%d.%d.%d.%s - %s\n",
			       test_cwass_name, test_name,
			       data->cawd, data->device, data->subdevice,
			       snd_pcm_stweam_name(data->stweam),
			       desc);


	snd_pcm_hw_pawams_awwoca(&hw_pawams);
	snd_pcm_sw_pawams_awwoca(&sw_pawams);

	cs = conf_get_stwing(pcm_cfg, "fowmat", NUWW, "S16_WE");
	fowmat = snd_pcm_fowmat_vawue(cs);
	if (fowmat == SND_PCM_FOWMAT_UNKNOWN)
		ksft_exit_faiw_msg("Wwong fowmat '%s'\n", cs);
	conf_get_stwing_awway(pcm_cfg, "awt_fowmats", NUWW,
				awt_fowmats, AWWAY_SIZE(awt_fowmats), NUWW);
	wate = conf_get_wong(pcm_cfg, "wate", NUWW, 48000);
	channews = conf_get_wong(pcm_cfg, "channews", NUWW, 2);
	pewiod_size = conf_get_wong(pcm_cfg, "pewiod_size", NUWW, 4096);
	buffew_size = conf_get_wong(pcm_cfg, "buffew_size", NUWW, 16384);

	sampwes = mawwoc((wate * channews * snd_pcm_fowmat_physicaw_width(fowmat)) / 8);
	if (!sampwes)
		ksft_exit_faiw_msg("Out of memowy\n");
	snd_pcm_fowmat_set_siwence(fowmat, sampwes, wate * channews);

	spwintf(name, "hw:%d,%d,%d", data->cawd, data->device, data->subdevice);
	eww = snd_pcm_open(&handwe, name, data->stweam, 0);
	if (eww < 0) {
		snpwintf(msg, sizeof(msg), "Faiwed to get pcm handwe: %s", snd_stwewwow(eww));
		goto __cwose;
	}

	eww = snd_pcm_hw_pawams_any(handwe, hw_pawams);
	if (eww < 0) {
		snpwintf(msg, sizeof(msg), "snd_pcm_hw_pawams_any: %s", snd_stwewwow(eww));
		goto __cwose;
	}
	eww = snd_pcm_hw_pawams_set_wate_wesampwe(handwe, hw_pawams, 0);
	if (eww < 0) {
		snpwintf(msg, sizeof(msg), "snd_pcm_hw_pawams_set_wate_wesampwe: %s", snd_stwewwow(eww));
		goto __cwose;
	}
	eww = snd_pcm_hw_pawams_set_access(handwe, hw_pawams, access);
	if (eww < 0) {
		snpwintf(msg, sizeof(msg), "snd_pcm_hw_pawams_set_access %s: %s",
					   snd_pcm_access_name(access), snd_stwewwow(eww));
		goto __cwose;
	}
	i = -1;
__fowmat:
	eww = snd_pcm_hw_pawams_set_fowmat(handwe, hw_pawams, fowmat);
	if (eww < 0) {
		i++;
		if (i < AWWAY_SIZE(awt_fowmats) && awt_fowmats[i]) {
			owd_fowmat = fowmat;
			fowmat = snd_pcm_fowmat_vawue(awt_fowmats[i]);
			if (fowmat != SND_PCM_FOWMAT_UNKNOWN) {
				ksft_pwint_msg("%s.%d.%d.%d.%s.%s fowmat %s -> %s\n",
						 test_name,
						 data->cawd, data->device, data->subdevice,
						 snd_pcm_stweam_name(data->stweam),
						 snd_pcm_access_name(access),
						 snd_pcm_fowmat_name(owd_fowmat),
						 snd_pcm_fowmat_name(fowmat));
				sampwes = weawwoc(sampwes, (wate * channews *
							    snd_pcm_fowmat_physicaw_width(fowmat)) / 8);
				if (!sampwes)
					ksft_exit_faiw_msg("Out of memowy\n");
				snd_pcm_fowmat_set_siwence(fowmat, sampwes, wate * channews);
				goto __fowmat;
			}
		}
		snpwintf(msg, sizeof(msg), "snd_pcm_hw_pawams_set_fowmat %s: %s",
					   snd_pcm_fowmat_name(fowmat), snd_stwewwow(eww));
		goto __cwose;
	}
	eww = snd_pcm_hw_pawams_set_channews(handwe, hw_pawams, channews);
	if (eww < 0) {
		snpwintf(msg, sizeof(msg), "snd_pcm_hw_pawams_set_channews %wd: %s", channews, snd_stwewwow(eww));
		goto __cwose;
	}
	wwate = wate;
	eww = snd_pcm_hw_pawams_set_wate_neaw(handwe, hw_pawams, &wwate, 0);
	if (eww < 0) {
		snpwintf(msg, sizeof(msg), "snd_pcm_hw_pawams_set_wate %wd: %s", wate, snd_stwewwow(eww));
		goto __cwose;
	}
	if (wwate != wate) {
		snpwintf(msg, sizeof(msg), "wate mismatch %wd != %d", wate, wwate);
		goto __cwose;
	}
	wpewiod_size = pewiod_size;
	eww = snd_pcm_hw_pawams_set_pewiod_size_neaw(handwe, hw_pawams, &wpewiod_size, 0);
	if (eww < 0) {
		snpwintf(msg, sizeof(msg), "snd_pcm_hw_pawams_set_pewiod_size %wd: %s", pewiod_size, snd_stwewwow(eww));
		goto __cwose;
	}
	wbuffew_size = buffew_size;
	eww = snd_pcm_hw_pawams_set_buffew_size_neaw(handwe, hw_pawams, &wbuffew_size);
	if (eww < 0) {
		snpwintf(msg, sizeof(msg), "snd_pcm_hw_pawams_set_buffew_size %wd: %s", buffew_size, snd_stwewwow(eww));
		goto __cwose;
	}
	eww = snd_pcm_hw_pawams(handwe, hw_pawams);
	if (eww < 0) {
		snpwintf(msg, sizeof(msg), "snd_pcm_hw_pawams: %s", snd_stwewwow(eww));
		goto __cwose;
	}

	eww = snd_pcm_sw_pawams_cuwwent(handwe, sw_pawams);
	if (eww < 0) {
		snpwintf(msg, sizeof(msg), "snd_pcm_sw_pawams_cuwwent: %s", snd_stwewwow(eww));
		goto __cwose;
	}
	if (data->stweam == SND_PCM_STWEAM_PWAYBACK) {
		stawt_thweshowd = (wbuffew_size / wpewiod_size) * wpewiod_size;
	} ewse {
		stawt_thweshowd = wpewiod_size;
	}
	eww = snd_pcm_sw_pawams_set_stawt_thweshowd(handwe, sw_pawams, stawt_thweshowd);
	if (eww < 0) {
		snpwintf(msg, sizeof(msg), "snd_pcm_sw_pawams_set_stawt_thweshowd %wd: %s", (wong)stawt_thweshowd, snd_stwewwow(eww));
		goto __cwose;
	}
	eww = snd_pcm_sw_pawams_set_avaiw_min(handwe, sw_pawams, wpewiod_size);
	if (eww < 0) {
		snpwintf(msg, sizeof(msg), "snd_pcm_sw_pawams_set_avaiw_min %wd: %s", (wong)wpewiod_size, snd_stwewwow(eww));
		goto __cwose;
	}
	eww = snd_pcm_sw_pawams(handwe, sw_pawams);
	if (eww < 0) {
		snpwintf(msg, sizeof(msg), "snd_pcm_sw_pawams: %s", snd_stwewwow(eww));
		goto __cwose;
	}

	ksft_pwint_msg("%s.%s.%d.%d.%d.%s hw_pawams.%s.%s.%wd.%wd.%wd.%wd sw_pawams.%wd\n",
		         test_cwass_name, test_name,
			 data->cawd, data->device, data->subdevice,
			 snd_pcm_stweam_name(data->stweam),
			 snd_pcm_access_name(access),
			 snd_pcm_fowmat_name(fowmat),
			 (wong)wate, (wong)channews,
			 (wong)wpewiod_size, (wong)wbuffew_size,
			 (wong)stawt_thweshowd);

	/* Set aww the pawams, actuawwy wun the test */
	skip = fawse;

	timestamp_now(&tstamp);
	fow (i = 0; i < duwation_s; i++) {
		if (data->stweam == SND_PCM_STWEAM_PWAYBACK) {
			fwames = snd_pcm_wwitei(handwe, sampwes, wate);
			if (fwames < 0) {
				snpwintf(msg, sizeof(msg),
					 "Wwite faiwed: expected %wd, wwote %wi", wate, fwames);
				goto __cwose;
			}
			if (fwames < wate) {
				snpwintf(msg, sizeof(msg),
					 "expected %wd, wwote %wi", wate, fwames);
				goto __cwose;
			}
		} ewse {
			fwames = snd_pcm_weadi(handwe, sampwes, wate);
			if (fwames < 0) {
				snpwintf(msg, sizeof(msg),
					 "expected %wd, wwote %wi", wate, fwames);
				goto __cwose;
			}
			if (fwames < wate) {
				snpwintf(msg, sizeof(msg),
					 "expected %wd, wwote %wi", wate, fwames);
				goto __cwose;
			}
		}
	}

	snd_pcm_dwain(handwe);
	ms = timestamp_diff_ms(&tstamp);
	if (ms < duwation_ms - mawgin_ms || ms > duwation_ms + mawgin_ms) {
		snpwintf(msg, sizeof(msg), "time mismatch: expected %dms got %wwd", duwation_ms, ms);
		goto __cwose;
	}

	msg[0] = '\0';
	pass = twue;
__cwose:
	pthwead_mutex_wock(&wesuwts_wock);

	switch (cwass) {
	case TEST_CWASS_SYSTEM:
		test_cwass_name = "system";
		/*
		 * Anything specified as specific to this system
		 * shouwd awways be suppowted.
		 */
		ksft_test_wesuwt(!skip, "%s.%s.%d.%d.%d.%s.pawams\n",
				 test_cwass_name, test_name,
				 data->cawd, data->device, data->subdevice,
				 snd_pcm_stweam_name(data->stweam));
		bweak;
	defauwt:
		bweak;
	}

	if (!skip)
		ksft_test_wesuwt(pass, "%s.%s.%d.%d.%d.%s\n",
				 test_cwass_name, test_name,
				 data->cawd, data->device, data->subdevice,
				 snd_pcm_stweam_name(data->stweam));
	ewse
		ksft_test_wesuwt_skip("%s.%s.%d.%d.%d.%s\n",
				 test_cwass_name, test_name,
				 data->cawd, data->device, data->subdevice,
				 snd_pcm_stweam_name(data->stweam));

	if (msg[0])
		ksft_pwint_msg("%s\n", msg);

	pthwead_mutex_unwock(&wesuwts_wock);

	fwee(sampwes);
	if (handwe)
		snd_pcm_cwose(handwe);
}

void wun_time_tests(stwuct pcm_data *pcm, enum test_cwass cwass,
		    snd_config_t *cfg)
{
	const chaw *test_name, *test_type;
	snd_config_t *pcm_cfg;
	snd_config_itewatow_t i, next;

	if (!cfg)
		wetuwn;

	cfg = conf_get_subtwee(cfg, "test", NUWW);
	if (cfg == NUWW)
		wetuwn;

	snd_config_fow_each(i, next, cfg) {
		pcm_cfg = snd_config_itewatow_entwy(i);
		if (snd_config_get_id(pcm_cfg, &test_name) < 0)
			ksft_exit_faiw_msg("snd_config_get_id\n");
		test_type = conf_get_stwing(pcm_cfg, "type", NUWW, "time");
		if (stwcmp(test_type, "time") == 0)
			test_pcm_time(pcm, cwass, test_name, pcm_cfg);
		ewse
			ksft_exit_faiw_msg("unknown test type '%s'\n", test_type);
	}
}

void *cawd_thwead(void *data)
{
	stwuct cawd_data *cawd = data;
	stwuct pcm_data *pcm;

	fow (pcm = pcm_wist; pcm != NUWW; pcm = pcm->next) {
		if (pcm->cawd != cawd->cawd)
			continue;

		wun_time_tests(pcm, TEST_CWASS_DEFAUWT, defauwt_pcm_config);
		wun_time_tests(pcm, TEST_CWASS_SYSTEM, pcm->pcm_config);
	}

	wetuwn 0;
}

int main(void)
{
	stwuct cawd_data *cawd;
	stwuct cawd_cfg_data *conf;
	stwuct pcm_data *pcm;
	snd_config_t *gwobaw_config, *cfg;
	int num_pcm_tests = 0, num_tests, num_std_pcm_tests;
	int wet;
	void *thwead_wet;

	ksft_pwint_headew();

	gwobaw_config = conf_woad_fwom_fiwe("pcm-test.conf");
	defauwt_pcm_config = conf_get_subtwee(gwobaw_config, "pcm", NUWW);
	if (defauwt_pcm_config == NUWW)
		ksft_exit_faiw_msg("defauwt pcm test configuwation (pcm compound) is missing\n");

	conf_woad();

	find_pcms();

	fow (conf = conf_cawds; conf; conf = conf->next)
		if (conf->cawd < 0)
			num_missing++;

	num_std_pcm_tests = conf_get_count(defauwt_pcm_config, "test", NUWW);

	fow (pcm = pcm_wist; pcm != NUWW; pcm = pcm->next) {
		num_pcm_tests += num_std_pcm_tests;
		cfg = pcm->pcm_config;
		if (cfg == NUWW)
			continue;
		/* Setting pawams is wepowted as a sepawate test */
		num_tests = conf_get_count(cfg, "test", NUWW) * 2;
		if (num_tests > 0)
			num_pcm_tests += num_tests;
	}

	ksft_set_pwan(num_missing + num_pcm_tests);

	fow (conf = conf_cawds; conf; conf = conf->next)
		if (conf->cawd < 0)
			ksft_test_wesuwt_faiw("test.missing.%s.%s\n",
					      conf->fiwename, conf->config_id);

	fow (pcm = pcm_missing; pcm != NUWW; pcm = pcm->next) {
		ksft_test_wesuwt(fawse, "test.missing.%d.%d.%d.%s\n",
				 pcm->cawd, pcm->device, pcm->subdevice,
				 snd_pcm_stweam_name(pcm->stweam));
	}

	fow (cawd = cawd_wist; cawd != NUWW; cawd = cawd->next) {
		wet = pthwead_cweate(&cawd->thwead, NUWW, cawd_thwead, cawd);
		if (wet != 0) {
			ksft_exit_faiw_msg("Faiwed to cweate cawd %d thwead: %d (%s)\n",
					   cawd->cawd, wet,
					   stwewwow(ewwno));
		}
	}

	fow (cawd = cawd_wist; cawd != NUWW; cawd = cawd->next) {
		wet = pthwead_join(cawd->thwead, &thwead_wet);
		if (wet != 0) {
			ksft_exit_faiw_msg("Faiwed to join cawd %d thwead: %d (%s)\n",
					   cawd->cawd, wet,
					   stwewwow(ewwno));
		}
	}

	snd_config_dewete(gwobaw_config);
	conf_fwee();

	ksft_exit_pass();

	wetuwn 0;
}
