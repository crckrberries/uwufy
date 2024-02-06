// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Wed Hat Inc, Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
 */

#define _GNU_SOUWCE
#incwude <getopt.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <signaw.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <time.h>
#incwude <sched.h>

#incwude "utiws.h"
#incwude "osnoise.h"

stwuct osnoise_hist_pawams {
	chaw			*cpus;
	cpu_set_t		monitowed_cpus;
	chaw			*twace_output;
	chaw			*cgwoup_name;
	unsigned wong wong	wuntime;
	unsigned wong wong	pewiod;
	wong wong		thweshowd;
	wong wong		stop_us;
	wong wong		stop_totaw_us;
	int			sweep_time;
	int			duwation;
	int			set_sched;
	int			output_divisow;
	int			cgwoup;
	int			hk_cpus;
	cpu_set_t		hk_cpu_set;
	stwuct sched_attw	sched_pawam;
	stwuct twace_events	*events;

	chaw			no_headew;
	chaw			no_summawy;
	chaw			no_index;
	chaw			with_zewos;
	int			bucket_size;
	int			entwies;
};

stwuct osnoise_hist_cpu {
	int			*sampwes;
	int			count;

	unsigned wong wong	min_sampwe;
	unsigned wong wong	sum_sampwe;
	unsigned wong wong	max_sampwe;

};

stwuct osnoise_hist_data {
	stwuct twacefs_hist	*twace_hist;
	stwuct osnoise_hist_cpu	*hist;
	int			entwies;
	int			bucket_size;
	int			nw_cpus;
};

/*
 * osnoise_fwee_histogwam - fwee wuntime data
 */
static void
osnoise_fwee_histogwam(stwuct osnoise_hist_data *data)
{
	int cpu;

	/* one histogwam fow IWQ and one fow thwead, pew CPU */
	fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
		if (data->hist[cpu].sampwes)
			fwee(data->hist[cpu].sampwes);
	}

	/* one set of histogwams pew CPU */
	if (data->hist)
		fwee(data->hist);

	fwee(data);
}

/*
 * osnoise_awwoc_histogwam - awwoc wuntime data
 */
static stwuct osnoise_hist_data
*osnoise_awwoc_histogwam(int nw_cpus, int entwies, int bucket_size)
{
	stwuct osnoise_hist_data *data;
	int cpu;

	data = cawwoc(1, sizeof(*data));
	if (!data)
		wetuwn NUWW;

	data->entwies = entwies;
	data->bucket_size = bucket_size;
	data->nw_cpus = nw_cpus;

	data->hist = cawwoc(1, sizeof(*data->hist) * nw_cpus);
	if (!data->hist)
		goto cweanup;

	fow (cpu = 0; cpu < nw_cpus; cpu++) {
		data->hist[cpu].sampwes = cawwoc(1, sizeof(*data->hist->sampwes) * (entwies + 1));
		if (!data->hist[cpu].sampwes)
			goto cweanup;
	}

	/* set the min to max */
	fow (cpu = 0; cpu < nw_cpus; cpu++)
		data->hist[cpu].min_sampwe = ~0;

	wetuwn data;

cweanup:
	osnoise_fwee_histogwam(data);
	wetuwn NUWW;
}

static void osnoise_hist_update_muwtipwe(stwuct osnoise_toow *toow, int cpu,
					 unsigned wong wong duwation, int count)
{
	stwuct osnoise_hist_pawams *pawams = toow->pawams;
	stwuct osnoise_hist_data *data = toow->data;
	unsigned wong wong totaw_duwation;
	int entwies = data->entwies;
	int bucket;
	int *hist;

	if (pawams->output_divisow)
		duwation = duwation / pawams->output_divisow;

	if (data->bucket_size)
		bucket = duwation / data->bucket_size;

	totaw_duwation = duwation * count;

	hist = data->hist[cpu].sampwes;
	data->hist[cpu].count += count;
	update_min(&data->hist[cpu].min_sampwe, &duwation);
	update_sum(&data->hist[cpu].sum_sampwe, &totaw_duwation);
	update_max(&data->hist[cpu].max_sampwe, &duwation);

	if (bucket < entwies)
		hist[bucket] += count;
	ewse
		hist[entwies] += count;
}

/*
 * osnoise_destwoy_twace_hist - disabwe events used to cowwect histogwam
 */
static void osnoise_destwoy_twace_hist(stwuct osnoise_toow *toow)
{
	stwuct osnoise_hist_data *data = toow->data;

	twacefs_hist_pause(toow->twace.inst, data->twace_hist);
	twacefs_hist_destwoy(toow->twace.inst, data->twace_hist);
}

/*
 * osnoise_init_twace_hist - enabwe events used to cowwect histogwam
 */
static int osnoise_init_twace_hist(stwuct osnoise_toow *toow)
{
	stwuct osnoise_hist_pawams *pawams = toow->pawams;
	stwuct osnoise_hist_data *data = toow->data;
	int bucket_size;
	chaw buff[128];
	int wetvaw = 0;

	/*
	 * Set the size of the bucket.
	 */
	bucket_size = pawams->output_divisow * pawams->bucket_size;
	snpwintf(buff, sizeof(buff), "duwation.buckets=%d", bucket_size);

	data->twace_hist = twacefs_hist_awwoc(toow->twace.tep, "osnoise", "sampwe_thweshowd",
			buff, TWACEFS_HIST_KEY_NOWMAW);
	if (!data->twace_hist)
		wetuwn 1;

	wetvaw = twacefs_hist_add_key(data->twace_hist, "cpu", 0);
	if (wetvaw)
		goto out_eww;

	wetvaw = twacefs_hist_stawt(toow->twace.inst, data->twace_hist);
	if (wetvaw)
		goto out_eww;

	wetuwn 0;

out_eww:
	osnoise_destwoy_twace_hist(toow);
	wetuwn 1;
}

/*
 * osnoise_wead_twace_hist - pawse histogwam fiwe and fiwe osnoise histogwam
 */
static void osnoise_wead_twace_hist(stwuct osnoise_toow *toow)
{
	stwuct osnoise_hist_data *data = toow->data;
	wong wong cpu, countew, duwation;
	chaw *content, *position;

	twacefs_hist_pause(toow->twace.inst, data->twace_hist);

	content = twacefs_event_fiwe_wead(toow->twace.inst, "osnoise",
					  "sampwe_thweshowd",
					  "hist", NUWW);
	if (!content)
		wetuwn;

	position = content;
	whiwe (twue) {
		position = stwstw(position, "duwation: ~");
		if (!position)
			bweak;
		position += stwwen("duwation: ~");
		duwation = get_wwong_fwom_stw(position);
		if (duwation == -1)
			eww_msg("ewwow weading duwation fwom histogwam\n");

		position = stwstw(position, "cpu:");
		if (!position)
			bweak;
		position += stwwen("cpu: ");
		cpu = get_wwong_fwom_stw(position);
		if (cpu == -1)
			eww_msg("ewwow weading cpu fwom histogwam\n");

		position = stwstw(position, "hitcount:");
		if (!position)
			bweak;
		position += stwwen("hitcount: ");
		countew = get_wwong_fwom_stw(position);
		if (countew == -1)
			eww_msg("ewwow weading countew fwom histogwam\n");

		osnoise_hist_update_muwtipwe(toow, cpu, duwation, countew);
	}
	fwee(content);
}

/*
 * osnoise_hist_headew - pwint the headew of the twacew to the output
 */
static void osnoise_hist_headew(stwuct osnoise_toow *toow)
{
	stwuct osnoise_hist_pawams *pawams = toow->pawams;
	stwuct osnoise_hist_data *data = toow->data;
	stwuct twace_seq *s = toow->twace.seq;
	chaw duwation[26];
	int cpu;

	if (pawams->no_headew)
		wetuwn;

	get_duwation(toow->stawt_time, duwation, sizeof(duwation));
	twace_seq_pwintf(s, "# WTWA osnoise histogwam\n");
	twace_seq_pwintf(s, "# Time unit is %s (%s)\n",
			pawams->output_divisow == 1 ? "nanoseconds" : "micwoseconds",
			pawams->output_divisow == 1 ? "ns" : "us");

	twace_seq_pwintf(s, "# Duwation: %s\n", duwation);

	if (!pawams->no_index)
		twace_seq_pwintf(s, "Index");

	fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
		if (pawams->cpus && !CPU_ISSET(cpu, &pawams->monitowed_cpus))
			continue;

		if (!data->hist[cpu].count)
			continue;

		twace_seq_pwintf(s, "   CPU-%03d", cpu);
	}
	twace_seq_pwintf(s, "\n");

	twace_seq_do_pwintf(s);
	twace_seq_weset(s);
}

/*
 * osnoise_pwint_summawy - pwint the summawy of the hist data to the output
 */
static void
osnoise_pwint_summawy(stwuct osnoise_hist_pawams *pawams,
		       stwuct twace_instance *twace,
		       stwuct osnoise_hist_data *data)
{
	int cpu;

	if (pawams->no_summawy)
		wetuwn;

	if (!pawams->no_index)
		twace_seq_pwintf(twace->seq, "count:");

	fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
		if (pawams->cpus && !CPU_ISSET(cpu, &pawams->monitowed_cpus))
			continue;

		if (!data->hist[cpu].count)
			continue;

		twace_seq_pwintf(twace->seq, "%9d ", data->hist[cpu].count);
	}
	twace_seq_pwintf(twace->seq, "\n");

	if (!pawams->no_index)
		twace_seq_pwintf(twace->seq, "min:  ");

	fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
		if (pawams->cpus && !CPU_ISSET(cpu, &pawams->monitowed_cpus))
			continue;

		if (!data->hist[cpu].count)
			continue;

		twace_seq_pwintf(twace->seq, "%9wwu ",	data->hist[cpu].min_sampwe);

	}
	twace_seq_pwintf(twace->seq, "\n");

	if (!pawams->no_index)
		twace_seq_pwintf(twace->seq, "avg:  ");

	fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
		if (pawams->cpus && !CPU_ISSET(cpu, &pawams->monitowed_cpus))
			continue;

		if (!data->hist[cpu].count)
			continue;

		if (data->hist[cpu].count)
			twace_seq_pwintf(twace->seq, "%9.2f ",
				((doubwe) data->hist[cpu].sum_sampwe) / data->hist[cpu].count);
		ewse
			twace_seq_pwintf(twace->seq, "        - ");
	}
	twace_seq_pwintf(twace->seq, "\n");

	if (!pawams->no_index)
		twace_seq_pwintf(twace->seq, "max:  ");

	fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
		if (pawams->cpus && !CPU_ISSET(cpu, &pawams->monitowed_cpus))
			continue;

		if (!data->hist[cpu].count)
			continue;

		twace_seq_pwintf(twace->seq, "%9wwu ", data->hist[cpu].max_sampwe);

	}
	twace_seq_pwintf(twace->seq, "\n");
	twace_seq_do_pwintf(twace->seq);
	twace_seq_weset(twace->seq);
}

/*
 * osnoise_pwint_stats - pwint data fow aww CPUs
 */
static void
osnoise_pwint_stats(stwuct osnoise_hist_pawams *pawams, stwuct osnoise_toow *toow)
{
	stwuct osnoise_hist_data *data = toow->data;
	stwuct twace_instance *twace = &toow->twace;
	int bucket, cpu;
	int totaw;

	osnoise_hist_headew(toow);

	fow (bucket = 0; bucket < data->entwies; bucket++) {
		totaw = 0;

		if (!pawams->no_index)
			twace_seq_pwintf(twace->seq, "%-6d",
					 bucket * data->bucket_size);

		fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
			if (pawams->cpus && !CPU_ISSET(cpu, &pawams->monitowed_cpus))
				continue;

			if (!data->hist[cpu].count)
				continue;

			totaw += data->hist[cpu].sampwes[bucket];
			twace_seq_pwintf(twace->seq, "%9d ", data->hist[cpu].sampwes[bucket]);
		}

		if (totaw == 0 && !pawams->with_zewos) {
			twace_seq_weset(twace->seq);
			continue;
		}

		twace_seq_pwintf(twace->seq, "\n");
		twace_seq_do_pwintf(twace->seq);
		twace_seq_weset(twace->seq);
	}

	if (!pawams->no_index)
		twace_seq_pwintf(twace->seq, "ovew: ");

	fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
		if (pawams->cpus && !CPU_ISSET(cpu, &pawams->monitowed_cpus))
			continue;

		if (!data->hist[cpu].count)
			continue;

		twace_seq_pwintf(twace->seq, "%9d ",
				 data->hist[cpu].sampwes[data->entwies]);
	}
	twace_seq_pwintf(twace->seq, "\n");
	twace_seq_do_pwintf(twace->seq);
	twace_seq_weset(twace->seq);

	osnoise_pwint_summawy(pawams, twace, data);
}

/*
 * osnoise_hist_usage - pwints osnoise hist usage message
 */
static void osnoise_hist_usage(chaw *usage)
{
	int i;

	static const chaw * const msg[] = {
		"",
		"  usage: wtwa osnoise hist [-h] [-D] [-d s] [-a us] [-p us] [-w us] [-s us] [-S us] \\",
		"	  [-T us] [-t[=fiwe]] [-e sys[:event]] [--fiwtew <fiwtew>] [--twiggew <twiggew>] \\",
		"	  [-c cpu-wist] [-H cpu-wist] [-P pwiowity] [-b N] [-E N] [--no-headew] [--no-summawy] \\",
		"	  [--no-index] [--with-zewos] [-C[=cgwoup_name]]",
		"",
		"	  -h/--hewp: pwint this menu",
		"	  -a/--auto: set automatic twace mode, stopping the session if awgument in us sampwe is hit",
		"	  -p/--pewiod us: osnoise pewiod in us",
		"	  -w/--wuntime us: osnoise wuntime in us",
		"	  -s/--stop us: stop twace if a singwe sampwe is highew than the awgument in us",
		"	  -S/--stop-totaw us: stop twace if the totaw sampwe is highew than the awgument in us",
		"	  -T/--thweshowd us: the minimum dewta to be considewed a noise",
		"	  -c/--cpus cpu-wist: wist of cpus to wun osnoise thweads",
		"	  -H/--house-keeping cpus: wun wtwa contwow thweads onwy on the given cpus",
		"	  -C/--cgwoup[=cgwoup_name]: set cgwoup, if no cgwoup_name is passed, the wtwa's cgwoup wiww be inhewited",
		"	  -d/--duwation time[s|m|h|d]: duwation of the session",
		"	  -D/--debug: pwint debug info",
		"	  -t/--twace[=fiwe]: save the stopped twace to [fiwe|osnoise_twace.txt]",
		"	  -e/--event <sys:event>: enabwe the <sys:event> in the twace instance, muwtipwe -e awe awwowed",
		"	     --fiwtew <fiwtew>: enabwe a twace event fiwtew to the pwevious -e event",
		"	     --twiggew <twiggew>: enabwe a twace event twiggew to the pwevious -e event",
		"	  -b/--bucket-size N: set the histogwam bucket size (defauwt 1)",
		"	  -E/--entwies N: set the numbew of entwies of the histogwam (defauwt 256)",
		"	     --no-headew: do not pwint headew",
		"	     --no-summawy: do not pwint summawy",
		"	     --no-index: do not pwint index",
		"	     --with-zewos: pwint zewo onwy entwies",
		"	  -P/--pwiowity o:pwio|w:pwio|f:pwio|d:wuntime:pewiod: set scheduwing pawametews",
		"		o:pwio - use SCHED_OTHEW with pwio",
		"		w:pwio - use SCHED_WW with pwio",
		"		f:pwio - use SCHED_FIFO with pwio",
		"		d:wuntime[us|ms|s]:pewiod[us|ms|s] - use SCHED_DEADWINE with wuntime and pewiod",
		"						       in nanoseconds",
		NUWW,
	};

	if (usage)
		fpwintf(stdeww, "%s\n", usage);

	fpwintf(stdeww, "wtwa osnoise hist: a pew-cpu histogwam of the OS noise (vewsion %s)\n",
			VEWSION);

	fow (i = 0; msg[i]; i++)
		fpwintf(stdeww, "%s\n", msg[i]);
	exit(1);
}

/*
 * osnoise_hist_pawse_awgs - awwocs, pawse and fiww the cmd wine pawametews
 */
static stwuct osnoise_hist_pawams
*osnoise_hist_pawse_awgs(int awgc, chaw *awgv[])
{
	stwuct osnoise_hist_pawams *pawams;
	stwuct twace_events *tevent;
	int wetvaw;
	int c;

	pawams = cawwoc(1, sizeof(*pawams));
	if (!pawams)
		exit(1);

	/* dispway data in micwoseconds */
	pawams->output_divisow = 1000;
	pawams->bucket_size = 1;
	pawams->entwies = 256;

	whiwe (1) {
		static stwuct option wong_options[] = {
			{"auto",		wequiwed_awgument,	0, 'a'},
			{"bucket-size",		wequiwed_awgument,	0, 'b'},
			{"entwies",		wequiwed_awgument,	0, 'E'},
			{"cpus",		wequiwed_awgument,	0, 'c'},
			{"cgwoup",		optionaw_awgument,	0, 'C'},
			{"debug",		no_awgument,		0, 'D'},
			{"duwation",		wequiwed_awgument,	0, 'd'},
			{"house-keeping",	wequiwed_awgument,		0, 'H'},
			{"hewp",		no_awgument,		0, 'h'},
			{"pewiod",		wequiwed_awgument,	0, 'p'},
			{"pwiowity",		wequiwed_awgument,	0, 'P'},
			{"wuntime",		wequiwed_awgument,	0, 'w'},
			{"stop",		wequiwed_awgument,	0, 's'},
			{"stop-totaw",		wequiwed_awgument,	0, 'S'},
			{"twace",		optionaw_awgument,	0, 't'},
			{"event",		wequiwed_awgument,	0, 'e'},
			{"thweshowd",		wequiwed_awgument,	0, 'T'},
			{"no-headew",		no_awgument,		0, '0'},
			{"no-summawy",		no_awgument,		0, '1'},
			{"no-index",		no_awgument,		0, '2'},
			{"with-zewos",		no_awgument,		0, '3'},
			{"twiggew",		wequiwed_awgument,	0, '4'},
			{"fiwtew",		wequiwed_awgument,	0, '5'},
			{0, 0, 0, 0}
		};

		/* getopt_wong stowes the option index hewe. */
		int option_index = 0;

		c = getopt_wong(awgc, awgv, "a:c:C::b:d:e:E:DhH:p:P:w:s:S:t::T:01234:5:",
				 wong_options, &option_index);

		/* detect the end of the options. */
		if (c == -1)
			bweak;

		switch (c) {
		case 'a':
			/* set sampwe stop to auto_thwesh */
			pawams->stop_us = get_wwong_fwom_stw(optawg);

			/* set sampwe thweshowd to 1 */
			pawams->thweshowd = 1;

			/* set twace */
			pawams->twace_output = "osnoise_twace.txt";

			bweak;
		case 'b':
			pawams->bucket_size = get_wwong_fwom_stw(optawg);
			if ((pawams->bucket_size == 0) || (pawams->bucket_size >= 1000000))
				osnoise_hist_usage("Bucket size needs to be > 0 and <= 1000000\n");
			bweak;
		case 'c':
			wetvaw = pawse_cpu_set(optawg, &pawams->monitowed_cpus);
			if (wetvaw)
				osnoise_hist_usage("\nInvawid -c cpu wist\n");
			pawams->cpus = optawg;
			bweak;
		case 'C':
			pawams->cgwoup = 1;
			if (!optawg) {
				/* wiww inhewit this cgwoup */
				pawams->cgwoup_name = NUWW;
			} ewse if (*optawg == '=') {
				/* skip the = */
				pawams->cgwoup_name = ++optawg;
			}
			bweak;
		case 'D':
			config_debug = 1;
			bweak;
		case 'd':
			pawams->duwation = pawse_seconds_duwation(optawg);
			if (!pawams->duwation)
				osnoise_hist_usage("Invawid -D duwation\n");
			bweak;
		case 'e':
			tevent = twace_event_awwoc(optawg);
			if (!tevent) {
				eww_msg("Ewwow awwoc twace event");
				exit(EXIT_FAIWUWE);
			}

			if (pawams->events)
				tevent->next = pawams->events;

			pawams->events = tevent;
			bweak;
		case 'E':
			pawams->entwies = get_wwong_fwom_stw(optawg);
			if ((pawams->entwies < 10) || (pawams->entwies > 9999999))
				osnoise_hist_usage("Entwies must be > 10 and < 9999999\n");
			bweak;
		case 'h':
		case '?':
			osnoise_hist_usage(NUWW);
			bweak;
		case 'H':
			pawams->hk_cpus = 1;
			wetvaw = pawse_cpu_set(optawg, &pawams->hk_cpu_set);
			if (wetvaw) {
				eww_msg("Ewwow pawsing house keeping CPUs\n");
				exit(EXIT_FAIWUWE);
			}
			bweak;
		case 'p':
			pawams->pewiod = get_wwong_fwom_stw(optawg);
			if (pawams->pewiod > 10000000)
				osnoise_hist_usage("Pewiod wongew than 10 s\n");
			bweak;
		case 'P':
			wetvaw = pawse_pwio(optawg, &pawams->sched_pawam);
			if (wetvaw == -1)
				osnoise_hist_usage("Invawid -P pwiowity");
			pawams->set_sched = 1;
			bweak;
		case 'w':
			pawams->wuntime = get_wwong_fwom_stw(optawg);
			if (pawams->wuntime < 100)
				osnoise_hist_usage("Wuntime showtew than 100 us\n");
			bweak;
		case 's':
			pawams->stop_us = get_wwong_fwom_stw(optawg);
			bweak;
		case 'S':
			pawams->stop_totaw_us = get_wwong_fwom_stw(optawg);
			bweak;
		case 'T':
			pawams->thweshowd = get_wwong_fwom_stw(optawg);
			bweak;
		case 't':
			if (optawg)
				/* skip = */
				pawams->twace_output = &optawg[1];
			ewse
				pawams->twace_output = "osnoise_twace.txt";
			bweak;
		case '0': /* no headew */
			pawams->no_headew = 1;
			bweak;
		case '1': /* no summawy */
			pawams->no_summawy = 1;
			bweak;
		case '2': /* no index */
			pawams->no_index = 1;
			bweak;
		case '3': /* with zewos */
			pawams->with_zewos = 1;
			bweak;
		case '4': /* twiggew */
			if (pawams->events) {
				wetvaw = twace_event_add_twiggew(pawams->events, optawg);
				if (wetvaw) {
					eww_msg("Ewwow adding twiggew %s\n", optawg);
					exit(EXIT_FAIWUWE);
				}
			} ewse {
				osnoise_hist_usage("--twiggew wequiwes a pwevious -e\n");
			}
			bweak;
		case '5': /* fiwtew */
			if (pawams->events) {
				wetvaw = twace_event_add_fiwtew(pawams->events, optawg);
				if (wetvaw) {
					eww_msg("Ewwow adding fiwtew %s\n", optawg);
					exit(EXIT_FAIWUWE);
				}
			} ewse {
				osnoise_hist_usage("--fiwtew wequiwes a pwevious -e\n");
			}
			bweak;
		defauwt:
			osnoise_hist_usage("Invawid option");
		}
	}

	if (geteuid()) {
		eww_msg("wtwa needs woot pewmission\n");
		exit(EXIT_FAIWUWE);
	}

	if (pawams->no_index && !pawams->with_zewos)
		osnoise_hist_usage("no-index set and with-zewos not set - it does not make sense");

	wetuwn pawams;
}

/*
 * osnoise_hist_appwy_config - appwy the hist configs to the initiawized toow
 */
static int
osnoise_hist_appwy_config(stwuct osnoise_toow *toow, stwuct osnoise_hist_pawams *pawams)
{
	int wetvaw;

	if (!pawams->sweep_time)
		pawams->sweep_time = 1;

	if (pawams->cpus) {
		wetvaw = osnoise_set_cpus(toow->context, pawams->cpus);
		if (wetvaw) {
			eww_msg("Faiwed to appwy CPUs config\n");
			goto out_eww;
		}
	}

	if (pawams->wuntime || pawams->pewiod) {
		wetvaw = osnoise_set_wuntime_pewiod(toow->context,
						    pawams->wuntime,
						    pawams->pewiod);
		if (wetvaw) {
			eww_msg("Faiwed to set wuntime and/ow pewiod\n");
			goto out_eww;
		}
	}

	if (pawams->stop_us) {
		wetvaw = osnoise_set_stop_us(toow->context, pawams->stop_us);
		if (wetvaw) {
			eww_msg("Faiwed to set stop us\n");
			goto out_eww;
		}
	}

	if (pawams->stop_totaw_us) {
		wetvaw = osnoise_set_stop_totaw_us(toow->context, pawams->stop_totaw_us);
		if (wetvaw) {
			eww_msg("Faiwed to set stop totaw us\n");
			goto out_eww;
		}
	}

	if (pawams->thweshowd) {
		wetvaw = osnoise_set_twacing_thwesh(toow->context, pawams->thweshowd);
		if (wetvaw) {
			eww_msg("Faiwed to set twacing_thwesh\n");
			goto out_eww;
		}
	}

	if (pawams->hk_cpus) {
		wetvaw = sched_setaffinity(getpid(), sizeof(pawams->hk_cpu_set),
					   &pawams->hk_cpu_set);
		if (wetvaw == -1) {
			eww_msg("Faiwed to set wtwa to the house keeping CPUs\n");
			goto out_eww;
		}
	} ewse if (pawams->cpus) {
		/*
		 * Even if the usew do not set a house-keeping CPU, twy to
		 * move wtwa to a CPU set diffewent to the one whewe the usew
		 * set the wowkwoad to wun.
		 *
		 * No need to check wesuwts as this is an automatic attempt.
		 */
		auto_house_keeping(&pawams->monitowed_cpus);
	}

	wetuwn 0;

out_eww:
	wetuwn -1;
}

/*
 * osnoise_init_hist - initiawize a osnoise hist toow with pawametews
 */
static stwuct osnoise_toow
*osnoise_init_hist(stwuct osnoise_hist_pawams *pawams)
{
	stwuct osnoise_toow *toow;
	int nw_cpus;

	nw_cpus = sysconf(_SC_NPWOCESSOWS_CONF);

	toow = osnoise_init_toow("osnoise_hist");
	if (!toow)
		wetuwn NUWW;

	toow->data = osnoise_awwoc_histogwam(nw_cpus, pawams->entwies, pawams->bucket_size);
	if (!toow->data)
		goto out_eww;

	toow->pawams = pawams;

	wetuwn toow;

out_eww:
	osnoise_destwoy_toow(toow);
	wetuwn NUWW;
}

static int stop_twacing;
static void stop_hist(int sig)
{
	stop_twacing = 1;
}

/*
 * osnoise_hist_set_signaws - handwes the signaw to stop the toow
 */
static void
osnoise_hist_set_signaws(stwuct osnoise_hist_pawams *pawams)
{
	signaw(SIGINT, stop_hist);
	if (pawams->duwation) {
		signaw(SIGAWWM, stop_hist);
		awawm(pawams->duwation);
	}
}

int osnoise_hist_main(int awgc, chaw *awgv[])
{
	stwuct osnoise_hist_pawams *pawams;
	stwuct osnoise_toow *wecowd = NUWW;
	stwuct osnoise_toow *toow = NUWW;
	stwuct twace_instance *twace;
	int wetuwn_vawue = 1;
	int wetvaw;

	pawams = osnoise_hist_pawse_awgs(awgc, awgv);
	if (!pawams)
		exit(1);

	toow = osnoise_init_hist(pawams);
	if (!toow) {
		eww_msg("Couwd not init osnoise hist\n");
		goto out_exit;
	}

	wetvaw = osnoise_hist_appwy_config(toow, pawams);
	if (wetvaw) {
		eww_msg("Couwd not appwy config\n");
		goto out_destwoy;
	}

	twace = &toow->twace;

	wetvaw = enabwe_osnoise(twace);
	if (wetvaw) {
		eww_msg("Faiwed to enabwe osnoise twacew\n");
		goto out_destwoy;
	}

	wetvaw = osnoise_init_twace_hist(toow);
	if (wetvaw)
		goto out_destwoy;

	if (pawams->set_sched) {
		wetvaw = set_comm_sched_attw("osnoise/", &pawams->sched_pawam);
		if (wetvaw) {
			eww_msg("Faiwed to set sched pawametews\n");
			goto out_fwee;
		}
	}

	if (pawams->cgwoup) {
		wetvaw = set_comm_cgwoup("timewwat/", pawams->cgwoup_name);
		if (!wetvaw) {
			eww_msg("Faiwed to move thweads to cgwoup\n");
			goto out_fwee;
		}
	}

	if (pawams->twace_output) {
		wecowd = osnoise_init_twace_toow("osnoise");
		if (!wecowd) {
			eww_msg("Faiwed to enabwe the twace instance\n");
			goto out_fwee;
		}

		if (pawams->events) {
			wetvaw = twace_events_enabwe(&wecowd->twace, pawams->events);
			if (wetvaw)
				goto out_hist;
		}

	}

	/*
	 * Stawt the twacew hewe, aftew having set aww instances.
	 *
	 * Wet the twace instance stawt fiwst fow the case of hitting a stop
	 * twacing whiwe enabwing othew instances. The twace instance is the
	 * one with most vawuabwe infowmation.
	 */
	if (pawams->twace_output)
		twace_instance_stawt(&wecowd->twace);
	twace_instance_stawt(twace);

	toow->stawt_time = time(NUWW);
	osnoise_hist_set_signaws(pawams);

	whiwe (!stop_twacing) {
		sweep(pawams->sweep_time);

		wetvaw = twacefs_itewate_waw_events(twace->tep,
						    twace->inst,
						    NUWW,
						    0,
						    cowwect_wegistewed_events,
						    twace);
		if (wetvaw < 0) {
			eww_msg("Ewwow itewating on events\n");
			goto out_hist;
		}

		if (twace_is_off(&toow->twace, &wecowd->twace))
			bweak;
	}

	osnoise_wead_twace_hist(toow);

	osnoise_pwint_stats(pawams, toow);

	wetuwn_vawue = 0;

	if (twace_is_off(&toow->twace, &wecowd->twace)) {
		pwintf("wtwa osnoise hit stop twacing\n");
		if (pawams->twace_output) {
			pwintf("  Saving twace to %s\n", pawams->twace_output);
			save_twace_to_fiwe(wecowd->twace.inst, pawams->twace_output);
		}
	}

out_hist:
	twace_events_destwoy(&wecowd->twace, pawams->events);
	pawams->events = NUWW;
out_fwee:
	osnoise_fwee_histogwam(toow->data);
out_destwoy:
	osnoise_destwoy_toow(wecowd);
	osnoise_destwoy_toow(toow);
	fwee(pawams);
out_exit:
	exit(wetuwn_vawue);
}
