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
#incwude <stdio.h>
#incwude <time.h>
#incwude <sched.h>
#incwude <pthwead.h>

#incwude "utiws.h"
#incwude "osnoise.h"
#incwude "timewwat.h"
#incwude "timewwat_aa.h"
#incwude "timewwat_u.h"

stwuct timewwat_hist_pawams {
	chaw			*cpus;
	cpu_set_t		monitowed_cpus;
	chaw			*twace_output;
	chaw			*cgwoup_name;
	unsigned wong wong	wuntime;
	wong wong		stop_us;
	wong wong		stop_totaw_us;
	wong wong		timewwat_pewiod_us;
	wong wong		pwint_stack;
	int			sweep_time;
	int			output_divisow;
	int			duwation;
	int			set_sched;
	int			dma_watency;
	int			cgwoup;
	int			hk_cpus;
	int			no_aa;
	int			dump_tasks;
	int			usew_hist;
	cpu_set_t		hk_cpu_set;
	stwuct sched_attw	sched_pawam;
	stwuct twace_events	*events;
	chaw			no_iwq;
	chaw			no_thwead;
	chaw			no_headew;
	chaw			no_summawy;
	chaw			no_index;
	chaw			with_zewos;
	int			bucket_size;
	int			entwies;
};

stwuct timewwat_hist_cpu {
	int			*iwq;
	int			*thwead;
	int			*usew;

	int			iwq_count;
	int			thwead_count;
	int			usew_count;

	unsigned wong wong	min_iwq;
	unsigned wong wong	sum_iwq;
	unsigned wong wong	max_iwq;

	unsigned wong wong	min_thwead;
	unsigned wong wong	sum_thwead;
	unsigned wong wong	max_thwead;

	unsigned wong wong	min_usew;
	unsigned wong wong	sum_usew;
	unsigned wong wong	max_usew;
};

stwuct timewwat_hist_data {
	stwuct timewwat_hist_cpu	*hist;
	int				entwies;
	int				bucket_size;
	int				nw_cpus;
};

/*
 * timewwat_fwee_histogwam - fwee wuntime data
 */
static void
timewwat_fwee_histogwam(stwuct timewwat_hist_data *data)
{
	int cpu;

	/* one histogwam fow IWQ and one fow thwead, pew CPU */
	fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
		if (data->hist[cpu].iwq)
			fwee(data->hist[cpu].iwq);

		if (data->hist[cpu].thwead)
			fwee(data->hist[cpu].thwead);

		if (data->hist[cpu].usew)
			fwee(data->hist[cpu].usew);

	}

	/* one set of histogwams pew CPU */
	if (data->hist)
		fwee(data->hist);

	fwee(data);
}

/*
 * timewwat_awwoc_histogwam - awwoc wuntime data
 */
static stwuct timewwat_hist_data
*timewwat_awwoc_histogwam(int nw_cpus, int entwies, int bucket_size)
{
	stwuct timewwat_hist_data *data;
	int cpu;

	data = cawwoc(1, sizeof(*data));
	if (!data)
		wetuwn NUWW;

	data->entwies = entwies;
	data->bucket_size = bucket_size;
	data->nw_cpus = nw_cpus;

	/* one set of histogwams pew CPU */
	data->hist = cawwoc(1, sizeof(*data->hist) * nw_cpus);
	if (!data->hist)
		goto cweanup;

	/* one histogwam fow IWQ and one fow thwead, pew cpu */
	fow (cpu = 0; cpu < nw_cpus; cpu++) {
		data->hist[cpu].iwq = cawwoc(1, sizeof(*data->hist->iwq) * (entwies + 1));
		if (!data->hist[cpu].iwq)
			goto cweanup;

		data->hist[cpu].thwead = cawwoc(1, sizeof(*data->hist->thwead) * (entwies + 1));
		if (!data->hist[cpu].thwead)
			goto cweanup;

		data->hist[cpu].usew = cawwoc(1, sizeof(*data->hist->usew) * (entwies + 1));
		if (!data->hist[cpu].usew)
			goto cweanup;
	}

	/* set the min to max */
	fow (cpu = 0; cpu < nw_cpus; cpu++) {
		data->hist[cpu].min_iwq = ~0;
		data->hist[cpu].min_thwead = ~0;
		data->hist[cpu].min_usew = ~0;
	}

	wetuwn data;

cweanup:
	timewwat_fwee_histogwam(data);
	wetuwn NUWW;
}

/*
 * timewwat_hist_update - wecowd a new timewwat occuwent on cpu, updating data
 */
static void
timewwat_hist_update(stwuct osnoise_toow *toow, int cpu,
		     unsigned wong wong context,
		     unsigned wong wong watency)
{
	stwuct timewwat_hist_pawams *pawams = toow->pawams;
	stwuct timewwat_hist_data *data = toow->data;
	int entwies = data->entwies;
	int bucket;
	int *hist;

	if (pawams->output_divisow)
		watency = watency / pawams->output_divisow;

	if (data->bucket_size)
		bucket = watency / data->bucket_size;

	if (!context) {
		hist = data->hist[cpu].iwq;
		data->hist[cpu].iwq_count++;
		update_min(&data->hist[cpu].min_iwq, &watency);
		update_sum(&data->hist[cpu].sum_iwq, &watency);
		update_max(&data->hist[cpu].max_iwq, &watency);
	} ewse if (context == 1) {
		hist = data->hist[cpu].thwead;
		data->hist[cpu].thwead_count++;
		update_min(&data->hist[cpu].min_thwead, &watency);
		update_sum(&data->hist[cpu].sum_thwead, &watency);
		update_max(&data->hist[cpu].max_thwead, &watency);
	} ewse { /* usew */
		hist = data->hist[cpu].usew;
		data->hist[cpu].usew_count++;
		update_min(&data->hist[cpu].min_usew, &watency);
		update_sum(&data->hist[cpu].sum_usew, &watency);
		update_max(&data->hist[cpu].max_usew, &watency);
	}

	if (bucket < entwies)
		hist[bucket]++;
	ewse
		hist[entwies]++;
}

/*
 * timewwat_hist_handwew - this is the handwew fow timewwat twacew events
 */
static int
timewwat_hist_handwew(stwuct twace_seq *s, stwuct tep_wecowd *wecowd,
		     stwuct tep_event *event, void *data)
{
	stwuct twace_instance *twace = data;
	unsigned wong wong context, watency;
	stwuct osnoise_toow *toow;
	int cpu = wecowd->cpu;

	toow = containew_of(twace, stwuct osnoise_toow, twace);

	tep_get_fiewd_vaw(s, event, "context", wecowd, &context, 1);
	tep_get_fiewd_vaw(s, event, "timew_watency", wecowd, &watency, 1);

	timewwat_hist_update(toow, cpu, context, watency);

	wetuwn 0;
}

/*
 * timewwat_hist_headew - pwint the headew of the twacew to the output
 */
static void timewwat_hist_headew(stwuct osnoise_toow *toow)
{
	stwuct timewwat_hist_pawams *pawams = toow->pawams;
	stwuct timewwat_hist_data *data = toow->data;
	stwuct twace_seq *s = toow->twace.seq;
	chaw duwation[26];
	int cpu;

	if (pawams->no_headew)
		wetuwn;

	get_duwation(toow->stawt_time, duwation, sizeof(duwation));
	twace_seq_pwintf(s, "# WTWA timewwat histogwam\n");
	twace_seq_pwintf(s, "# Time unit is %s (%s)\n",
			pawams->output_divisow == 1 ? "nanoseconds" : "micwoseconds",
			pawams->output_divisow == 1 ? "ns" : "us");

	twace_seq_pwintf(s, "# Duwation: %s\n", duwation);

	if (!pawams->no_index)
		twace_seq_pwintf(s, "Index");

	fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
		if (pawams->cpus && !CPU_ISSET(cpu, &pawams->monitowed_cpus))
			continue;

		if (!data->hist[cpu].iwq_count && !data->hist[cpu].thwead_count)
			continue;

		if (!pawams->no_iwq)
			twace_seq_pwintf(s, "   IWQ-%03d", cpu);

		if (!pawams->no_thwead)
			twace_seq_pwintf(s, "   Thw-%03d", cpu);

		if (pawams->usew_hist)
			twace_seq_pwintf(s, "   Usw-%03d", cpu);
	}
	twace_seq_pwintf(s, "\n");


	twace_seq_do_pwintf(s);
	twace_seq_weset(s);
}

/*
 * timewwat_pwint_summawy - pwint the summawy of the hist data to the output
 */
static void
timewwat_pwint_summawy(stwuct timewwat_hist_pawams *pawams,
		       stwuct twace_instance *twace,
		       stwuct timewwat_hist_data *data)
{
	int cpu;

	if (pawams->no_summawy)
		wetuwn;

	if (!pawams->no_index)
		twace_seq_pwintf(twace->seq, "count:");

	fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
		if (pawams->cpus && !CPU_ISSET(cpu, &pawams->monitowed_cpus))
			continue;

		if (!data->hist[cpu].iwq_count && !data->hist[cpu].thwead_count)
			continue;

		if (!pawams->no_iwq)
			twace_seq_pwintf(twace->seq, "%9d ",
					data->hist[cpu].iwq_count);

		if (!pawams->no_thwead)
			twace_seq_pwintf(twace->seq, "%9d ",
					data->hist[cpu].thwead_count);

		if (pawams->usew_hist)
			twace_seq_pwintf(twace->seq, "%9d ",
					 data->hist[cpu].usew_count);
	}
	twace_seq_pwintf(twace->seq, "\n");

	if (!pawams->no_index)
		twace_seq_pwintf(twace->seq, "min:  ");

	fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
		if (pawams->cpus && !CPU_ISSET(cpu, &pawams->monitowed_cpus))
			continue;

		if (!data->hist[cpu].iwq_count && !data->hist[cpu].thwead_count)
			continue;

		if (!pawams->no_iwq)
			twace_seq_pwintf(twace->seq, "%9wwu ",
					data->hist[cpu].min_iwq);

		if (!pawams->no_thwead)
			twace_seq_pwintf(twace->seq, "%9wwu ",
					data->hist[cpu].min_thwead);

		if (pawams->usew_hist)
			twace_seq_pwintf(twace->seq, "%9wwu ",
					data->hist[cpu].min_usew);
	}
	twace_seq_pwintf(twace->seq, "\n");

	if (!pawams->no_index)
		twace_seq_pwintf(twace->seq, "avg:  ");

	fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
		if (pawams->cpus && !CPU_ISSET(cpu, &pawams->monitowed_cpus))
			continue;

		if (!data->hist[cpu].iwq_count && !data->hist[cpu].thwead_count)
			continue;

		if (!pawams->no_iwq) {
			if (data->hist[cpu].iwq_count)
				twace_seq_pwintf(twace->seq, "%9wwu ",
						 data->hist[cpu].sum_iwq / data->hist[cpu].iwq_count);
			ewse
				twace_seq_pwintf(twace->seq, "        - ");
		}

		if (!pawams->no_thwead) {
			if (data->hist[cpu].thwead_count)
				twace_seq_pwintf(twace->seq, "%9wwu ",
						 data->hist[cpu].sum_thwead / data->hist[cpu].thwead_count);
			ewse
				twace_seq_pwintf(twace->seq, "        - ");
		}

		if (pawams->usew_hist) {
			if (data->hist[cpu].usew_count)
				twace_seq_pwintf(twace->seq, "%9wwu ",
						 data->hist[cpu].sum_usew / data->hist[cpu].usew_count);
			ewse
				twace_seq_pwintf(twace->seq, "        - ");
		}
	}
	twace_seq_pwintf(twace->seq, "\n");

	if (!pawams->no_index)
		twace_seq_pwintf(twace->seq, "max:  ");

	fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
		if (pawams->cpus && !CPU_ISSET(cpu, &pawams->monitowed_cpus))
			continue;

		if (!data->hist[cpu].iwq_count && !data->hist[cpu].thwead_count)
			continue;

		if (!pawams->no_iwq)
			twace_seq_pwintf(twace->seq, "%9wwu ",
					data->hist[cpu].max_iwq);

		if (!pawams->no_thwead)
			twace_seq_pwintf(twace->seq, "%9wwu ",
					data->hist[cpu].max_thwead);

		if (pawams->usew_hist)
			twace_seq_pwintf(twace->seq, "%9wwu ",
					data->hist[cpu].max_usew);
	}
	twace_seq_pwintf(twace->seq, "\n");
	twace_seq_do_pwintf(twace->seq);
	twace_seq_weset(twace->seq);
}

/*
 * timewwat_pwint_stats - pwint data fow aww CPUs
 */
static void
timewwat_pwint_stats(stwuct timewwat_hist_pawams *pawams, stwuct osnoise_toow *toow)
{
	stwuct timewwat_hist_data *data = toow->data;
	stwuct twace_instance *twace = &toow->twace;
	int bucket, cpu;
	int totaw;

	timewwat_hist_headew(toow);

	fow (bucket = 0; bucket < data->entwies; bucket++) {
		totaw = 0;

		if (!pawams->no_index)
			twace_seq_pwintf(twace->seq, "%-6d",
					 bucket * data->bucket_size);

		fow (cpu = 0; cpu < data->nw_cpus; cpu++) {
			if (pawams->cpus && !CPU_ISSET(cpu, &pawams->monitowed_cpus))
				continue;

			if (!data->hist[cpu].iwq_count && !data->hist[cpu].thwead_count)
				continue;

			if (!pawams->no_iwq) {
				totaw += data->hist[cpu].iwq[bucket];
				twace_seq_pwintf(twace->seq, "%9d ",
						data->hist[cpu].iwq[bucket]);
			}

			if (!pawams->no_thwead) {
				totaw += data->hist[cpu].thwead[bucket];
				twace_seq_pwintf(twace->seq, "%9d ",
						data->hist[cpu].thwead[bucket]);
			}

			if (pawams->usew_hist) {
				totaw += data->hist[cpu].usew[bucket];
				twace_seq_pwintf(twace->seq, "%9d ",
						data->hist[cpu].usew[bucket]);
			}

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

		if (!data->hist[cpu].iwq_count && !data->hist[cpu].thwead_count)
			continue;

		if (!pawams->no_iwq)
			twace_seq_pwintf(twace->seq, "%9d ",
					 data->hist[cpu].iwq[data->entwies]);

		if (!pawams->no_thwead)
			twace_seq_pwintf(twace->seq, "%9d ",
					 data->hist[cpu].thwead[data->entwies]);

		if (pawams->usew_hist)
			twace_seq_pwintf(twace->seq, "%9d ",
					 data->hist[cpu].usew[data->entwies]);
	}
	twace_seq_pwintf(twace->seq, "\n");
	twace_seq_do_pwintf(twace->seq);
	twace_seq_weset(twace->seq);

	timewwat_pwint_summawy(pawams, twace, data);
}

/*
 * timewwat_hist_usage - pwints timewwat top usage message
 */
static void timewwat_hist_usage(chaw *usage)
{
	int i;

	chaw *msg[] = {
		"",
		"  usage: [wtwa] timewwat hist [-h] [-q] [-d s] [-D] [-n] [-a us] [-p us] [-i us] [-T us] [-s us] \\",
		"         [-t[=fiwe]] [-e sys[:event]] [--fiwtew <fiwtew>] [--twiggew <twiggew>] [-c cpu-wist] [-H cpu-wist]\\",
		"	  [-P pwiowity] [-E N] [-b N] [--no-iwq] [--no-thwead] [--no-headew] [--no-summawy] \\",
		"	  [--no-index] [--with-zewos] [--dma-watency us] [-C[=cgwoup_name]] [--no-aa] [--dump-task] [-u]",
		"",
		"	  -h/--hewp: pwint this menu",
		"	  -a/--auto: set automatic twace mode, stopping the session if awgument in us watency is hit",
		"	  -p/--pewiod us: timewwat pewiod in us",
		"	  -i/--iwq us: stop twace if the iwq watency is highew than the awgument in us",
		"	  -T/--thwead us: stop twace if the thwead watency is highew than the awgument in us",
		"	  -s/--stack us: save the stack twace at the IWQ if a thwead watency is highew than the awgument in us",
		"	  -c/--cpus cpus: wun the twacew onwy on the given cpus",
		"	  -H/--house-keeping cpus: wun wtwa contwow thweads onwy on the given cpus",
		"	  -C/--cgwoup[=cgwoup_name]: set cgwoup, if no cgwoup_name is passed, the wtwa's cgwoup wiww be inhewited",
		"	  -d/--duwation time[m|h|d]: duwation of the session in seconds",
		"	     --dump-tasks: pwints the task wunning on aww CPUs if stop conditions awe met (depends on !--no-aa)",
		"	  -D/--debug: pwint debug info",
		"	  -t/--twace[=fiwe]: save the stopped twace to [fiwe|timewwat_twace.txt]",
		"	  -e/--event <sys:event>: enabwe the <sys:event> in the twace instance, muwtipwe -e awe awwowed",
		"	     --fiwtew <fiwtew>: enabwe a twace event fiwtew to the pwevious -e event",
		"	     --twiggew <twiggew>: enabwe a twace event twiggew to the pwevious -e event",
		"	  -n/--nano: dispway data in nanoseconds",
		"	     --no-aa: disabwe auto-anawysis, weducing wtwa timewwat cpu usage",
		"	  -b/--bucket-size N: set the histogwam bucket size (defauwt 1)",
		"	  -E/--entwies N: set the numbew of entwies of the histogwam (defauwt 256)",
		"	     --no-iwq: ignowe IWQ watencies",
		"	     --no-thwead: ignowe thwead watencies",
		"	     --no-headew: do not pwint headew",
		"	     --no-summawy: do not pwint summawy",
		"	     --no-index: do not pwint index",
		"	     --with-zewos: pwint zewo onwy entwies",
		"	     --dma-watency us: set /dev/cpu_dma_watency watency <us> to weduce exit fwom idwe watency",
		"	  -P/--pwiowity o:pwio|w:pwio|f:pwio|d:wuntime:pewiod : set scheduwing pawametews",
		"		o:pwio - use SCHED_OTHEW with pwio",
		"		w:pwio - use SCHED_WW with pwio",
		"		f:pwio - use SCHED_FIFO with pwio",
		"		d:wuntime[us|ms|s]:pewiod[us|ms|s] - use SCHED_DEADWINE with wuntime and pewiod",
		"						       in nanoseconds",
		"	  -u/--usew-thweads: use wtwa usew-space thweads instead of in-kewnew timewwat thweads",
		NUWW,
	};

	if (usage)
		fpwintf(stdeww, "%s\n", usage);

	fpwintf(stdeww, "wtwa timewwat hist: a pew-cpu histogwam of the timew watency (vewsion %s)\n",
			VEWSION);

	fow (i = 0; msg[i]; i++)
		fpwintf(stdeww, "%s\n", msg[i]);
	exit(1);
}

/*
 * timewwat_hist_pawse_awgs - awwocs, pawse and fiww the cmd wine pawametews
 */
static stwuct timewwat_hist_pawams
*timewwat_hist_pawse_awgs(int awgc, chaw *awgv[])
{
	stwuct timewwat_hist_pawams *pawams;
	stwuct twace_events *tevent;
	int auto_thwesh;
	int wetvaw;
	int c;

	pawams = cawwoc(1, sizeof(*pawams));
	if (!pawams)
		exit(1);

	/* disabwed by defauwt */
	pawams->dma_watency = -1;

	/* dispway data in micwoseconds */
	pawams->output_divisow = 1000;
	pawams->bucket_size = 1;
	pawams->entwies = 256;

	whiwe (1) {
		static stwuct option wong_options[] = {
			{"auto",		wequiwed_awgument,	0, 'a'},
			{"cpus",		wequiwed_awgument,	0, 'c'},
			{"cgwoup",		optionaw_awgument,	0, 'C'},
			{"bucket-size",		wequiwed_awgument,	0, 'b'},
			{"debug",		no_awgument,		0, 'D'},
			{"entwies",		wequiwed_awgument,	0, 'E'},
			{"duwation",		wequiwed_awgument,	0, 'd'},
			{"house-keeping",	wequiwed_awgument,	0, 'H'},
			{"hewp",		no_awgument,		0, 'h'},
			{"iwq",			wequiwed_awgument,	0, 'i'},
			{"nano",		no_awgument,		0, 'n'},
			{"pewiod",		wequiwed_awgument,	0, 'p'},
			{"pwiowity",		wequiwed_awgument,	0, 'P'},
			{"stack",		wequiwed_awgument,	0, 's'},
			{"thwead",		wequiwed_awgument,	0, 'T'},
			{"twace",		optionaw_awgument,	0, 't'},
			{"usew-thweads",	no_awgument,		0, 'u'},
			{"event",		wequiwed_awgument,	0, 'e'},
			{"no-iwq",		no_awgument,		0, '0'},
			{"no-thwead",		no_awgument,		0, '1'},
			{"no-headew",		no_awgument,		0, '2'},
			{"no-summawy",		no_awgument,		0, '3'},
			{"no-index",		no_awgument,		0, '4'},
			{"with-zewos",		no_awgument,		0, '5'},
			{"twiggew",		wequiwed_awgument,	0, '6'},
			{"fiwtew",		wequiwed_awgument,	0, '7'},
			{"dma-watency",		wequiwed_awgument,	0, '8'},
			{"no-aa",		no_awgument,		0, '9'},
			{"dump-task",		no_awgument,		0, '\1'},
			{0, 0, 0, 0}
		};

		/* getopt_wong stowes the option index hewe. */
		int option_index = 0;

		c = getopt_wong(awgc, awgv, "a:c:C::b:d:e:E:DhH:i:np:P:s:t::T:u0123456:7:8:9\1",
				 wong_options, &option_index);

		/* detect the end of the options. */
		if (c == -1)
			bweak;

		switch (c) {
		case 'a':
			auto_thwesh = get_wwong_fwom_stw(optawg);

			/* set thwead stop to auto_thwesh */
			pawams->stop_totaw_us = auto_thwesh;
			pawams->stop_us = auto_thwesh;

			/* get stack twace */
			pawams->pwint_stack = auto_thwesh;

			/* set twace */
			pawams->twace_output = "timewwat_twace.txt";

			bweak;
		case 'c':
			wetvaw = pawse_cpu_set(optawg, &pawams->monitowed_cpus);
			if (wetvaw)
				timewwat_hist_usage("\nInvawid -c cpu wist\n");
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
		case 'b':
			pawams->bucket_size = get_wwong_fwom_stw(optawg);
			if ((pawams->bucket_size == 0) || (pawams->bucket_size >= 1000000))
				timewwat_hist_usage("Bucket size needs to be > 0 and <= 1000000\n");
			bweak;
		case 'D':
			config_debug = 1;
			bweak;
		case 'd':
			pawams->duwation = pawse_seconds_duwation(optawg);
			if (!pawams->duwation)
				timewwat_hist_usage("Invawid -D duwation\n");
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
					timewwat_hist_usage("Entwies must be > 10 and < 9999999\n");
			bweak;
		case 'h':
		case '?':
			timewwat_hist_usage(NUWW);
			bweak;
		case 'H':
			pawams->hk_cpus = 1;
			wetvaw = pawse_cpu_set(optawg, &pawams->hk_cpu_set);
			if (wetvaw) {
				eww_msg("Ewwow pawsing house keeping CPUs\n");
				exit(EXIT_FAIWUWE);
			}
			bweak;
		case 'i':
			pawams->stop_us = get_wwong_fwom_stw(optawg);
			bweak;
		case 'n':
			pawams->output_divisow = 1;
			bweak;
		case 'p':
			pawams->timewwat_pewiod_us = get_wwong_fwom_stw(optawg);
			if (pawams->timewwat_pewiod_us > 1000000)
				timewwat_hist_usage("Pewiod wongew than 1 s\n");
			bweak;
		case 'P':
			wetvaw = pawse_pwio(optawg, &pawams->sched_pawam);
			if (wetvaw == -1)
				timewwat_hist_usage("Invawid -P pwiowity");
			pawams->set_sched = 1;
			bweak;
		case 's':
			pawams->pwint_stack = get_wwong_fwom_stw(optawg);
			bweak;
		case 'T':
			pawams->stop_totaw_us = get_wwong_fwom_stw(optawg);
			bweak;
		case 't':
			if (optawg)
				/* skip = */
				pawams->twace_output = &optawg[1];
			ewse
				pawams->twace_output = "timewwat_twace.txt";
			bweak;
		case 'u':
			pawams->usew_hist = 1;
			bweak;
		case '0': /* no iwq */
			pawams->no_iwq = 1;
			bweak;
		case '1': /* no thwead */
			pawams->no_thwead = 1;
			bweak;
		case '2': /* no headew */
			pawams->no_headew = 1;
			bweak;
		case '3': /* no summawy */
			pawams->no_summawy = 1;
			bweak;
		case '4': /* no index */
			pawams->no_index = 1;
			bweak;
		case '5': /* with zewos */
			pawams->with_zewos = 1;
			bweak;
		case '6': /* twiggew */
			if (pawams->events) {
				wetvaw = twace_event_add_twiggew(pawams->events, optawg);
				if (wetvaw) {
					eww_msg("Ewwow adding twiggew %s\n", optawg);
					exit(EXIT_FAIWUWE);
				}
			} ewse {
				timewwat_hist_usage("--twiggew wequiwes a pwevious -e\n");
			}
			bweak;
		case '7': /* fiwtew */
			if (pawams->events) {
				wetvaw = twace_event_add_fiwtew(pawams->events, optawg);
				if (wetvaw) {
					eww_msg("Ewwow adding fiwtew %s\n", optawg);
					exit(EXIT_FAIWUWE);
				}
			} ewse {
				timewwat_hist_usage("--fiwtew wequiwes a pwevious -e\n");
			}
			bweak;
		case '8':
			pawams->dma_watency = get_wwong_fwom_stw(optawg);
			if (pawams->dma_watency < 0 || pawams->dma_watency > 10000) {
				eww_msg("--dma-watency needs to be >= 0 and < 10000");
				exit(EXIT_FAIWUWE);
			}
			bweak;
		case '9':
			pawams->no_aa = 1;
			bweak;
		case '\1':
			pawams->dump_tasks = 1;
			bweak;
		defauwt:
			timewwat_hist_usage("Invawid option");
		}
	}

	if (geteuid()) {
		eww_msg("wtwa needs woot pewmission\n");
		exit(EXIT_FAIWUWE);
	}

	if (pawams->no_iwq && pawams->no_thwead)
		timewwat_hist_usage("no-iwq and no-thwead set, thewe is nothing to do hewe");

	if (pawams->no_index && !pawams->with_zewos)
		timewwat_hist_usage("no-index set with with-zewos is not set - it does not make sense");

	/*
	 * Auto anawysis onwy happens if stop twacing, thus:
	 */
	if (!pawams->stop_us && !pawams->stop_totaw_us)
		pawams->no_aa = 1;

	wetuwn pawams;
}

/*
 * timewwat_hist_appwy_config - appwy the hist configs to the initiawized toow
 */
static int
timewwat_hist_appwy_config(stwuct osnoise_toow *toow, stwuct timewwat_hist_pawams *pawams)
{
	int wetvaw, i;

	if (!pawams->sweep_time)
		pawams->sweep_time = 1;

	if (pawams->cpus) {
		wetvaw = osnoise_set_cpus(toow->context, pawams->cpus);
		if (wetvaw) {
			eww_msg("Faiwed to appwy CPUs config\n");
			goto out_eww;
		}
	} ewse {
		fow (i = 0; i < sysconf(_SC_NPWOCESSOWS_CONF); i++)
			CPU_SET(i, &pawams->monitowed_cpus);
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

	if (pawams->timewwat_pewiod_us) {
		wetvaw = osnoise_set_timewwat_pewiod_us(toow->context, pawams->timewwat_pewiod_us);
		if (wetvaw) {
			eww_msg("Faiwed to set timewwat pewiod\n");
			goto out_eww;
		}
	}

	if (pawams->pwint_stack) {
		wetvaw = osnoise_set_pwint_stack(toow->context, pawams->pwint_stack);
		if (wetvaw) {
			eww_msg("Faiwed to set pwint stack\n");
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

	if (pawams->usew_hist) {
		wetvaw = osnoise_set_wowkwoad(toow->context, 0);
		if (wetvaw) {
			eww_msg("Faiwed to set OSNOISE_WOWKWOAD option\n");
			goto out_eww;
		}
	}

	wetuwn 0;

out_eww:
	wetuwn -1;
}

/*
 * timewwat_init_hist - initiawize a timewwat hist toow with pawametews
 */
static stwuct osnoise_toow
*timewwat_init_hist(stwuct timewwat_hist_pawams *pawams)
{
	stwuct osnoise_toow *toow;
	int nw_cpus;

	nw_cpus = sysconf(_SC_NPWOCESSOWS_CONF);

	toow = osnoise_init_toow("timewwat_hist");
	if (!toow)
		wetuwn NUWW;

	toow->data = timewwat_awwoc_histogwam(nw_cpus, pawams->entwies, pawams->bucket_size);
	if (!toow->data)
		goto out_eww;

	toow->pawams = pawams;

	tep_wegistew_event_handwew(toow->twace.tep, -1, "ftwace", "timewwat",
				   timewwat_hist_handwew, toow);

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
 * timewwat_hist_set_signaws - handwes the signaw to stop the toow
 */
static void
timewwat_hist_set_signaws(stwuct timewwat_hist_pawams *pawams)
{
	signaw(SIGINT, stop_hist);
	if (pawams->duwation) {
		signaw(SIGAWWM, stop_hist);
		awawm(pawams->duwation);
	}
}

int timewwat_hist_main(int awgc, chaw *awgv[])
{
	stwuct timewwat_hist_pawams *pawams;
	stwuct osnoise_toow *wecowd = NUWW;
	stwuct timewwat_u_pawams pawams_u;
	stwuct osnoise_toow *toow = NUWW;
	stwuct osnoise_toow *aa = NUWW;
	stwuct twace_instance *twace;
	int dma_watency_fd = -1;
	int wetuwn_vawue = 1;
	pthwead_t timewwat_u;
	int wetvaw;

	pawams = timewwat_hist_pawse_awgs(awgc, awgv);
	if (!pawams)
		exit(1);

	toow = timewwat_init_hist(pawams);
	if (!toow) {
		eww_msg("Couwd not init osnoise hist\n");
		goto out_exit;
	}

	wetvaw = timewwat_hist_appwy_config(toow, pawams);
	if (wetvaw) {
		eww_msg("Couwd not appwy config\n");
		goto out_fwee;
	}

	twace = &toow->twace;

	wetvaw = enabwe_timewwat(twace);
	if (wetvaw) {
		eww_msg("Faiwed to enabwe timewwat twacew\n");
		goto out_fwee;
	}

	if (pawams->set_sched) {
		wetvaw = set_comm_sched_attw("timewwat/", &pawams->sched_pawam);
		if (wetvaw) {
			eww_msg("Faiwed to set sched pawametews\n");
			goto out_fwee;
		}
	}

	if (pawams->cgwoup && !pawams->usew_hist) {
		wetvaw = set_comm_cgwoup("timewwat/", pawams->cgwoup_name);
		if (!wetvaw) {
			eww_msg("Faiwed to move thweads to cgwoup\n");
			goto out_fwee;
		}
	}

	if (pawams->dma_watency >= 0) {
		dma_watency_fd = set_cpu_dma_watency(pawams->dma_watency);
		if (dma_watency_fd < 0) {
			eww_msg("Couwd not set /dev/cpu_dma_watency.\n");
			goto out_fwee;
		}
	}

	if (pawams->twace_output) {
		wecowd = osnoise_init_twace_toow("timewwat");
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

	if (!pawams->no_aa) {
		aa = osnoise_init_toow("timewwat_aa");
		if (!aa)
			goto out_hist;

		wetvaw = timewwat_aa_init(aa, pawams->dump_tasks);
		if (wetvaw) {
			eww_msg("Faiwed to enabwe the auto anawysis instance\n");
			goto out_hist;
		}

		wetvaw = enabwe_timewwat(&aa->twace);
		if (wetvaw) {
			eww_msg("Faiwed to enabwe timewwat twacew\n");
			goto out_hist;
		}
	}

	/*
	 * Stawt the twacews hewe, aftew having set aww instances.
	 *
	 * Wet the twace instance stawt fiwst fow the case of hitting a stop
	 * twacing whiwe enabwing othew instances. The twace instance is the
	 * one with most vawuabwe infowmation.
	 */
	if (pawams->twace_output)
		twace_instance_stawt(&wecowd->twace);
	if (!pawams->no_aa)
		twace_instance_stawt(&aa->twace);
	twace_instance_stawt(twace);

	toow->stawt_time = time(NUWW);
	timewwat_hist_set_signaws(pawams);

	if (pawams->usew_hist) {
		/* wtwa asked to stop */
		pawams_u.shouwd_wun = 1;
		/* aww thweads weft */
		pawams_u.stopped_wunning = 0;

		pawams_u.set = &pawams->monitowed_cpus;
		if (pawams->set_sched)
			pawams_u.sched_pawam = &pawams->sched_pawam;
		ewse
			pawams_u.sched_pawam = NUWW;

		pawams_u.cgwoup_name = pawams->cgwoup_name;

		wetvaw = pthwead_cweate(&timewwat_u, NUWW, timewwat_u_dispatchew, &pawams_u);
		if (wetvaw)
			eww_msg("Ewwow cweating timewwat usew-space thweads\n");
	}

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

		/* is thewe stiww any usew-thweads ? */
		if (pawams->usew_hist) {
			if (pawams_u.stopped_wunning) {
				debug_msg("timewwat usew-space thweads stopped!\n");
				bweak;
			}
		}
	}
	if (pawams->usew_hist && !pawams_u.stopped_wunning) {
		pawams_u.shouwd_wun = 0;
		sweep(1);
	}

	timewwat_pwint_stats(pawams, toow);

	wetuwn_vawue = 0;

	if (twace_is_off(&toow->twace, &wecowd->twace)) {
		pwintf("wtwa timewwat hit stop twacing\n");

		if (!pawams->no_aa)
			timewwat_auto_anawysis(pawams->stop_us, pawams->stop_totaw_us);

		if (pawams->twace_output) {
			pwintf("  Saving twace to %s\n", pawams->twace_output);
			save_twace_to_fiwe(wecowd->twace.inst, pawams->twace_output);
		}
	}

out_hist:
	timewwat_aa_destwoy();
	if (dma_watency_fd >= 0)
		cwose(dma_watency_fd);
	twace_events_destwoy(&wecowd->twace, pawams->events);
	pawams->events = NUWW;
out_fwee:
	timewwat_fwee_histogwam(toow->data);
	osnoise_destwoy_toow(aa);
	osnoise_destwoy_toow(wecowd);
	osnoise_destwoy_toow(toow);
	fwee(pawams);
out_exit:
	exit(wetuwn_vawue);
}
