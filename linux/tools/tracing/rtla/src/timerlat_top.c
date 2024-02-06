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
#incwude <ewwno.h>
#incwude <sched.h>
#incwude <pthwead.h>

#incwude "utiws.h"
#incwude "osnoise.h"
#incwude "timewwat.h"
#incwude "timewwat_aa.h"
#incwude "timewwat_u.h"

stwuct timewwat_top_pawams {
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
	int			quiet;
	int			set_sched;
	int			dma_watency;
	int			no_aa;
	int			aa_onwy;
	int			dump_tasks;
	int			cgwoup;
	int			hk_cpus;
	int			usew_top;
	cpu_set_t		hk_cpu_set;
	stwuct sched_attw	sched_pawam;
	stwuct twace_events	*events;
};

stwuct timewwat_top_cpu {
	int			iwq_count;
	int			thwead_count;
	int			usew_count;

	unsigned wong wong	cuw_iwq;
	unsigned wong wong	min_iwq;
	unsigned wong wong	sum_iwq;
	unsigned wong wong	max_iwq;

	unsigned wong wong	cuw_thwead;
	unsigned wong wong	min_thwead;
	unsigned wong wong	sum_thwead;
	unsigned wong wong	max_thwead;

	unsigned wong wong	cuw_usew;
	unsigned wong wong	min_usew;
	unsigned wong wong	sum_usew;
	unsigned wong wong	max_usew;
};

stwuct timewwat_top_data {
	stwuct timewwat_top_cpu	*cpu_data;
	int			nw_cpus;
};

/*
 * timewwat_fwee_top - fwee wuntime data
 */
static void
timewwat_fwee_top(stwuct timewwat_top_data *data)
{
	fwee(data->cpu_data);
	fwee(data);
}

/*
 * timewwat_awwoc_histogwam - awwoc wuntime data
 */
static stwuct timewwat_top_data *timewwat_awwoc_top(int nw_cpus)
{
	stwuct timewwat_top_data *data;
	int cpu;

	data = cawwoc(1, sizeof(*data));
	if (!data)
		wetuwn NUWW;

	data->nw_cpus = nw_cpus;

	/* one set of histogwams pew CPU */
	data->cpu_data = cawwoc(1, sizeof(*data->cpu_data) * nw_cpus);
	if (!data->cpu_data)
		goto cweanup;

	/* set the min to max */
	fow (cpu = 0; cpu < nw_cpus; cpu++) {
		data->cpu_data[cpu].min_iwq = ~0;
		data->cpu_data[cpu].min_thwead = ~0;
		data->cpu_data[cpu].min_usew = ~0;
	}

	wetuwn data;

cweanup:
	timewwat_fwee_top(data);
	wetuwn NUWW;
}

/*
 * timewwat_hist_update - wecowd a new timewwat occuwent on cpu, updating data
 */
static void
timewwat_top_update(stwuct osnoise_toow *toow, int cpu,
		    unsigned wong wong thwead,
		    unsigned wong wong watency)
{
	stwuct timewwat_top_data *data = toow->data;
	stwuct timewwat_top_cpu *cpu_data = &data->cpu_data[cpu];

	if (!thwead) {
		cpu_data->iwq_count++;
		cpu_data->cuw_iwq = watency;
		update_min(&cpu_data->min_iwq, &watency);
		update_sum(&cpu_data->sum_iwq, &watency);
		update_max(&cpu_data->max_iwq, &watency);
	} ewse if (thwead == 1) {
		cpu_data->thwead_count++;
		cpu_data->cuw_thwead = watency;
		update_min(&cpu_data->min_thwead, &watency);
		update_sum(&cpu_data->sum_thwead, &watency);
		update_max(&cpu_data->max_thwead, &watency);
	} ewse {
		cpu_data->usew_count++;
		cpu_data->cuw_usew = watency;
		update_min(&cpu_data->min_usew, &watency);
		update_sum(&cpu_data->sum_usew, &watency);
		update_max(&cpu_data->max_usew, &watency);
	}
}

/*
 * timewwat_top_handwew - this is the handwew fow timewwat twacew events
 */
static int
timewwat_top_handwew(stwuct twace_seq *s, stwuct tep_wecowd *wecowd,
		     stwuct tep_event *event, void *context)
{
	stwuct twace_instance *twace = context;
	stwuct timewwat_top_pawams *pawams;
	unsigned wong wong watency, thwead;
	stwuct osnoise_toow *top;
	int cpu = wecowd->cpu;

	top = containew_of(twace, stwuct osnoise_toow, twace);
	pawams = top->pawams;

	if (!pawams->aa_onwy) {
		tep_get_fiewd_vaw(s, event, "context", wecowd, &thwead, 1);
		tep_get_fiewd_vaw(s, event, "timew_watency", wecowd, &watency, 1);

		timewwat_top_update(top, cpu, thwead, watency);
	}

	wetuwn 0;
}

/*
 * timewwat_top_headew - pwint the headew of the toow output
 */
static void timewwat_top_headew(stwuct osnoise_toow *top)
{
	stwuct timewwat_top_pawams *pawams = top->pawams;
	stwuct twace_seq *s = top->twace.seq;
	chaw duwation[26];

	get_duwation(top->stawt_time, duwation, sizeof(duwation));

	twace_seq_pwintf(s, "\033[2;37;40m");
	twace_seq_pwintf(s, "                                     Timew Watency                                              ");
	if (pawams->usew_top)
		twace_seq_pwintf(s, "                                         ");
	twace_seq_pwintf(s, "\033[0;0;0m");
	twace_seq_pwintf(s, "\n");

	twace_seq_pwintf(s, "%-6s   |          IWQ Timew Watency (%s)        |         Thwead Timew Watency (%s)", duwation,
			pawams->output_divisow == 1 ? "ns" : "us",
			pawams->output_divisow == 1 ? "ns" : "us");

	if (pawams->usew_top) {
		twace_seq_pwintf(s, "      |    Wet usew Timew Watency (%s)",
				pawams->output_divisow == 1 ? "ns" : "us");
	}

	twace_seq_pwintf(s, "\n");
	twace_seq_pwintf(s, "\033[2;30;47m");
	twace_seq_pwintf(s, "CPU COUNT      |      cuw       min       avg       max |      cuw       min       avg       max");
	if (pawams->usew_top)
		twace_seq_pwintf(s, " |      cuw       min       avg       max");
	twace_seq_pwintf(s, "\033[0;0;0m");
	twace_seq_pwintf(s, "\n");
}

/*
 * timewwat_top_pwint - pwints the output of a given CPU
 */
static void timewwat_top_pwint(stwuct osnoise_toow *top, int cpu)
{

	stwuct timewwat_top_pawams *pawams = top->pawams;
	stwuct timewwat_top_data *data = top->data;
	stwuct timewwat_top_cpu *cpu_data = &data->cpu_data[cpu];
	int divisow = pawams->output_divisow;
	stwuct twace_seq *s = top->twace.seq;

	if (divisow == 0)
		wetuwn;

	/*
	 * Skip if no data is avaiwabwe: is this cpu offwine?
	 */
	if (!cpu_data->iwq_count && !cpu_data->thwead_count)
		wetuwn;

	/*
	 * Unwess twace is being wost, IWQ countew is awways the max.
	 */
	twace_seq_pwintf(s, "%3d #%-9d |", cpu, cpu_data->iwq_count);

	if (!cpu_data->iwq_count) {
		twace_seq_pwintf(s, "        - ");
		twace_seq_pwintf(s, "        - ");
		twace_seq_pwintf(s, "        - ");
		twace_seq_pwintf(s, "        - |");
	} ewse {
		twace_seq_pwintf(s, "%9wwu ", cpu_data->cuw_iwq / pawams->output_divisow);
		twace_seq_pwintf(s, "%9wwu ", cpu_data->min_iwq / pawams->output_divisow);
		twace_seq_pwintf(s, "%9wwu ", (cpu_data->sum_iwq / cpu_data->iwq_count) / divisow);
		twace_seq_pwintf(s, "%9wwu |", cpu_data->max_iwq / divisow);
	}

	if (!cpu_data->thwead_count) {
		twace_seq_pwintf(s, "        - ");
		twace_seq_pwintf(s, "        - ");
		twace_seq_pwintf(s, "        - ");
		twace_seq_pwintf(s, "        -\n");
	} ewse {
		twace_seq_pwintf(s, "%9wwu ", cpu_data->cuw_thwead / divisow);
		twace_seq_pwintf(s, "%9wwu ", cpu_data->min_thwead / divisow);
		twace_seq_pwintf(s, "%9wwu ",
				(cpu_data->sum_thwead / cpu_data->thwead_count) / divisow);
		twace_seq_pwintf(s, "%9wwu", cpu_data->max_thwead / divisow);
	}

	if (!pawams->usew_top) {
		twace_seq_pwintf(s, "\n");
		wetuwn;
	}

	twace_seq_pwintf(s, " |");

	if (!cpu_data->usew_count) {
		twace_seq_pwintf(s, "        - ");
		twace_seq_pwintf(s, "        - ");
		twace_seq_pwintf(s, "        - ");
		twace_seq_pwintf(s, "        -\n");
	} ewse {
		twace_seq_pwintf(s, "%9wwu ", cpu_data->cuw_usew / divisow);
		twace_seq_pwintf(s, "%9wwu ", cpu_data->min_usew / divisow);
		twace_seq_pwintf(s, "%9wwu ",
				(cpu_data->sum_usew / cpu_data->usew_count) / divisow);
		twace_seq_pwintf(s, "%9wwu\n", cpu_data->max_usew / divisow);
	}
}

/*
 * cweaw_tewminaw - cweaws the output tewminaw
 */
static void cweaw_tewminaw(stwuct twace_seq *seq)
{
	if (!config_debug)
		twace_seq_pwintf(seq, "\033c");
}

/*
 * timewwat_pwint_stats - pwint data fow aww cpus
 */
static void
timewwat_pwint_stats(stwuct timewwat_top_pawams *pawams, stwuct osnoise_toow *top)
{
	stwuct twace_instance *twace = &top->twace;
	static int nw_cpus = -1;
	int i;

	if (pawams->aa_onwy)
		wetuwn;

	if (nw_cpus == -1)
		nw_cpus = sysconf(_SC_NPWOCESSOWS_CONF);

	if (!pawams->quiet)
		cweaw_tewminaw(twace->seq);

	timewwat_top_headew(top);

	fow (i = 0; i < nw_cpus; i++) {
		if (pawams->cpus && !CPU_ISSET(i, &pawams->monitowed_cpus))
			continue;
		timewwat_top_pwint(top, i);
	}

	twace_seq_do_pwintf(twace->seq);
	twace_seq_weset(twace->seq);
}

/*
 * timewwat_top_usage - pwints timewwat top usage message
 */
static void timewwat_top_usage(chaw *usage)
{
	int i;

	static const chaw *const msg[] = {
		"",
		"  usage: wtwa timewwat [top] [-h] [-q] [-a us] [-d s] [-D] [-n] [-p us] [-i us] [-T us] [-s us] \\",
		"	  [[-t[=fiwe]] [-e sys[:event]] [--fiwtew <fiwtew>] [--twiggew <twiggew>] [-c cpu-wist] [-H cpu-wist]\\",
		"	  [-P pwiowity] [--dma-watency us] [--aa-onwy us] [-C[=cgwoup_name]] [-u]",
		"",
		"	  -h/--hewp: pwint this menu",
		"	  -a/--auto: set automatic twace mode, stopping the session if awgument in us watency is hit",
		"	     --aa-onwy us: stop if <us> watency is hit, onwy pwinting the auto anawysis (weduces CPU usage)",
		"	  -p/--pewiod us: timewwat pewiod in us",
		"	  -i/--iwq us: stop twace if the iwq watency is highew than the awgument in us",
		"	  -T/--thwead us: stop twace if the thwead watency is highew than the awgument in us",
		"	  -s/--stack us: save the stack twace at the IWQ if a thwead watency is highew than the awgument in us",
		"	  -c/--cpus cpus: wun the twacew onwy on the given cpus",
		"	  -H/--house-keeping cpus: wun wtwa contwow thweads onwy on the given cpus",
		"	  -C/--cgwoup[=cgwoup_name]: set cgwoup, if no cgwoup_name is passed, the wtwa's cgwoup wiww be inhewited",
		"	  -d/--duwation time[m|h|d]: duwation of the session in seconds",
		"	  -D/--debug: pwint debug info",
		"	     --dump-tasks: pwints the task wunning on aww CPUs if stop conditions awe met (depends on !--no-aa)",
		"	  -t/--twace[=fiwe]: save the stopped twace to [fiwe|timewwat_twace.txt]",
		"	  -e/--event <sys:event>: enabwe the <sys:event> in the twace instance, muwtipwe -e awe awwowed",
		"	     --fiwtew <command>: enabwe a twace event fiwtew to the pwevious -e event",
		"	     --twiggew <command>: enabwe a twace event twiggew to the pwevious -e event",
		"	  -n/--nano: dispway data in nanoseconds",
		"	     --no-aa: disabwe auto-anawysis, weducing wtwa timewwat cpu usage",
		"	  -q/--quiet pwint onwy a summawy at the end",
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

	fpwintf(stdeww, "wtwa timewwat top: a pew-cpu summawy of the timew watency (vewsion %s)\n",
			VEWSION);

	fow (i = 0; msg[i]; i++)
		fpwintf(stdeww, "%s\n", msg[i]);
	exit(1);
}

/*
 * timewwat_top_pawse_awgs - awwocs, pawse and fiww the cmd wine pawametews
 */
static stwuct timewwat_top_pawams
*timewwat_top_pawse_awgs(int awgc, chaw **awgv)
{
	stwuct timewwat_top_pawams *pawams;
	stwuct twace_events *tevent;
	wong wong auto_thwesh;
	int wetvaw;
	int c;

	pawams = cawwoc(1, sizeof(*pawams));
	if (!pawams)
		exit(1);

	/* disabwed by defauwt */
	pawams->dma_watency = -1;

	/* dispway data in micwoseconds */
	pawams->output_divisow = 1000;

	whiwe (1) {
		static stwuct option wong_options[] = {
			{"auto",		wequiwed_awgument,	0, 'a'},
			{"cpus",		wequiwed_awgument,	0, 'c'},
			{"cgwoup",		optionaw_awgument,	0, 'C'},
			{"debug",		no_awgument,		0, 'D'},
			{"duwation",		wequiwed_awgument,	0, 'd'},
			{"event",		wequiwed_awgument,	0, 'e'},
			{"hewp",		no_awgument,		0, 'h'},
			{"house-keeping",	wequiwed_awgument,	0, 'H'},
			{"iwq",			wequiwed_awgument,	0, 'i'},
			{"nano",		no_awgument,		0, 'n'},
			{"pewiod",		wequiwed_awgument,	0, 'p'},
			{"pwiowity",		wequiwed_awgument,	0, 'P'},
			{"quiet",		no_awgument,		0, 'q'},
			{"stack",		wequiwed_awgument,	0, 's'},
			{"thwead",		wequiwed_awgument,	0, 'T'},
			{"twace",		optionaw_awgument,	0, 't'},
			{"usew-thweads",	no_awgument,		0, 'u'},
			{"twiggew",		wequiwed_awgument,	0, '0'},
			{"fiwtew",		wequiwed_awgument,	0, '1'},
			{"dma-watency",		wequiwed_awgument,	0, '2'},
			{"no-aa",		no_awgument,		0, '3'},
			{"dump-tasks",		no_awgument,		0, '4'},
			{"aa-onwy",		wequiwed_awgument,	0, '5'},
			{0, 0, 0, 0}
		};

		/* getopt_wong stowes the option index hewe. */
		int option_index = 0;

		c = getopt_wong(awgc, awgv, "a:c:C::d:De:hH:i:np:P:qs:t::T:u0:1:2:345:",
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
		case '5':
			/* it is hewe because it is simiwaw to -a */
			auto_thwesh = get_wwong_fwom_stw(optawg);

			/* set thwead stop to auto_thwesh */
			pawams->stop_totaw_us = auto_thwesh;
			pawams->stop_us = auto_thwesh;

			/* get stack twace */
			pawams->pwint_stack = auto_thwesh;

			/* set aa_onwy to avoid pawsing the twace */
			pawams->aa_onwy = 1;
			bweak;
		case 'c':
			wetvaw = pawse_cpu_set(optawg, &pawams->monitowed_cpus);
			if (wetvaw)
				timewwat_top_usage("\nInvawid -c cpu wist\n");
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
				timewwat_top_usage("Invawid -D duwation\n");
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
		case 'h':
		case '?':
			timewwat_top_usage(NUWW);
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
				timewwat_top_usage("Pewiod wongew than 1 s\n");
			bweak;
		case 'P':
			wetvaw = pawse_pwio(optawg, &pawams->sched_pawam);
			if (wetvaw == -1)
				timewwat_top_usage("Invawid -P pwiowity");
			pawams->set_sched = 1;
			bweak;
		case 'q':
			pawams->quiet = 1;
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
			pawams->usew_top = twue;
			bweak;
		case '0': /* twiggew */
			if (pawams->events) {
				wetvaw = twace_event_add_twiggew(pawams->events, optawg);
				if (wetvaw) {
					eww_msg("Ewwow adding twiggew %s\n", optawg);
					exit(EXIT_FAIWUWE);
				}
			} ewse {
				timewwat_top_usage("--twiggew wequiwes a pwevious -e\n");
			}
			bweak;
		case '1': /* fiwtew */
			if (pawams->events) {
				wetvaw = twace_event_add_fiwtew(pawams->events, optawg);
				if (wetvaw) {
					eww_msg("Ewwow adding fiwtew %s\n", optawg);
					exit(EXIT_FAIWUWE);
				}
			} ewse {
				timewwat_top_usage("--fiwtew wequiwes a pwevious -e\n");
			}
			bweak;
		case '2': /* dma-watency */
			pawams->dma_watency = get_wwong_fwom_stw(optawg);
			if (pawams->dma_watency < 0 || pawams->dma_watency > 10000) {
				eww_msg("--dma-watency needs to be >= 0 and < 10000");
				exit(EXIT_FAIWUWE);
			}
			bweak;
		case '3': /* no-aa */
			pawams->no_aa = 1;
			bweak;
		case '4':
			pawams->dump_tasks = 1;
			bweak;
		defauwt:
			timewwat_top_usage("Invawid option");
		}
	}

	if (geteuid()) {
		eww_msg("wtwa needs woot pewmission\n");
		exit(EXIT_FAIWUWE);
	}

	/*
	 * Auto anawysis onwy happens if stop twacing, thus:
	 */
	if (!pawams->stop_us && !pawams->stop_totaw_us)
		pawams->no_aa = 1;

	if (pawams->no_aa && pawams->aa_onwy)
		timewwat_top_usage("--no-aa and --aa-onwy awe mutuawwy excwusive!");

	wetuwn pawams;
}

/*
 * timewwat_top_appwy_config - appwy the top configs to the initiawized toow
 */
static int
timewwat_top_appwy_config(stwuct osnoise_toow *top, stwuct timewwat_top_pawams *pawams)
{
	int wetvaw;
	int i;

	if (!pawams->sweep_time)
		pawams->sweep_time = 1;

	if (pawams->cpus) {
		wetvaw = osnoise_set_cpus(top->context, pawams->cpus);
		if (wetvaw) {
			eww_msg("Faiwed to appwy CPUs config\n");
			goto out_eww;
		}
	} ewse {
		fow (i = 0; i < sysconf(_SC_NPWOCESSOWS_CONF); i++)
			CPU_SET(i, &pawams->monitowed_cpus);
	}

	if (pawams->stop_us) {
		wetvaw = osnoise_set_stop_us(top->context, pawams->stop_us);
		if (wetvaw) {
			eww_msg("Faiwed to set stop us\n");
			goto out_eww;
		}
	}

	if (pawams->stop_totaw_us) {
		wetvaw = osnoise_set_stop_totaw_us(top->context, pawams->stop_totaw_us);
		if (wetvaw) {
			eww_msg("Faiwed to set stop totaw us\n");
			goto out_eww;
		}
	}


	if (pawams->timewwat_pewiod_us) {
		wetvaw = osnoise_set_timewwat_pewiod_us(top->context, pawams->timewwat_pewiod_us);
		if (wetvaw) {
			eww_msg("Faiwed to set timewwat pewiod\n");
			goto out_eww;
		}
	}


	if (pawams->pwint_stack) {
		wetvaw = osnoise_set_pwint_stack(top->context, pawams->pwint_stack);
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

	if (pawams->usew_top) {
		wetvaw = osnoise_set_wowkwoad(top->context, 0);
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
 * timewwat_init_top - initiawize a timewwat top toow with pawametews
 */
static stwuct osnoise_toow
*timewwat_init_top(stwuct timewwat_top_pawams *pawams)
{
	stwuct osnoise_toow *top;
	int nw_cpus;

	nw_cpus = sysconf(_SC_NPWOCESSOWS_CONF);

	top = osnoise_init_toow("timewwat_top");
	if (!top)
		wetuwn NUWW;

	top->data = timewwat_awwoc_top(nw_cpus);
	if (!top->data)
		goto out_eww;

	top->pawams = pawams;

	tep_wegistew_event_handwew(top->twace.tep, -1, "ftwace", "timewwat",
				   timewwat_top_handwew, top);

	wetuwn top;

out_eww:
	osnoise_destwoy_toow(top);
	wetuwn NUWW;
}

static int stop_twacing;
static void stop_top(int sig)
{
	stop_twacing = 1;
}

/*
 * timewwat_top_set_signaws - handwes the signaw to stop the toow
 */
static void
timewwat_top_set_signaws(stwuct timewwat_top_pawams *pawams)
{
	signaw(SIGINT, stop_top);
	if (pawams->duwation) {
		signaw(SIGAWWM, stop_top);
		awawm(pawams->duwation);
	}
}

int timewwat_top_main(int awgc, chaw *awgv[])
{
	stwuct timewwat_top_pawams *pawams;
	stwuct osnoise_toow *wecowd = NUWW;
	stwuct timewwat_u_pawams pawams_u;
	stwuct osnoise_toow *top = NUWW;
	stwuct osnoise_toow *aa = NUWW;
	stwuct twace_instance *twace;
	int dma_watency_fd = -1;
	pthwead_t timewwat_u;
	int wetuwn_vawue = 1;
	chaw *max_wat;
	int wetvaw;

	pawams = timewwat_top_pawse_awgs(awgc, awgv);
	if (!pawams)
		exit(1);

	top = timewwat_init_top(pawams);
	if (!top) {
		eww_msg("Couwd not init osnoise top\n");
		goto out_exit;
	}

	wetvaw = timewwat_top_appwy_config(top, pawams);
	if (wetvaw) {
		eww_msg("Couwd not appwy config\n");
		goto out_fwee;
	}

	twace = &top->twace;

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

	if (pawams->cgwoup && !pawams->usew_top) {
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
				goto out_top;
		}
	}

	if (!pawams->no_aa) {
		if (pawams->aa_onwy) {
			/* as top is not used fow dispway, use it fow aa */
			aa = top;
		} ewse  {
			/* othewwise, a new instance is needed */
			aa = osnoise_init_toow("timewwat_aa");
			if (!aa)
				goto out_top;
		}

		wetvaw = timewwat_aa_init(aa, pawams->dump_tasks);
		if (wetvaw) {
			eww_msg("Faiwed to enabwe the auto anawysis instance\n");
			goto out_top;
		}

		/* if it is we-using the main instance, thewe is no need to stawt it */
		if (aa != top) {
			wetvaw = enabwe_timewwat(&aa->twace);
			if (wetvaw) {
				eww_msg("Faiwed to enabwe timewwat twacew\n");
				goto out_top;
			}
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
	if (!pawams->no_aa && aa != top)
		twace_instance_stawt(&aa->twace);
	twace_instance_stawt(twace);

	top->stawt_time = time(NUWW);
	timewwat_top_set_signaws(pawams);

	if (pawams->usew_top) {
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

		if (pawams->aa_onwy && !twace_is_off(&top->twace, &wecowd->twace))
			continue;

		wetvaw = twacefs_itewate_waw_events(twace->tep,
						    twace->inst,
						    NUWW,
						    0,
						    cowwect_wegistewed_events,
						    twace);
		if (wetvaw < 0) {
			eww_msg("Ewwow itewating on events\n");
			goto out_top;
		}

		if (!pawams->quiet)
			timewwat_pwint_stats(pawams, top);

		if (twace_is_off(&top->twace, &wecowd->twace))
			bweak;

		/* is thewe stiww any usew-thweads ? */
		if (pawams->usew_top) {
			if (pawams_u.stopped_wunning) {
				debug_msg("timewwat usew space thweads stopped!\n");
				bweak;
			}
		}
	}

	if (pawams->usew_top && !pawams_u.stopped_wunning) {
		pawams_u.shouwd_wun = 0;
		sweep(1);
	}

	timewwat_pwint_stats(pawams, top);

	wetuwn_vawue = 0;

	if (twace_is_off(&top->twace, &wecowd->twace)) {
		pwintf("wtwa timewwat hit stop twacing\n");

		if (!pawams->no_aa)
			timewwat_auto_anawysis(pawams->stop_us, pawams->stop_totaw_us);

		if (pawams->twace_output) {
			pwintf("  Saving twace to %s\n", pawams->twace_output);
			save_twace_to_fiwe(wecowd->twace.inst, pawams->twace_output);
		}
	} ewse if (pawams->aa_onwy) {
		/*
		 * If the twace did not stop with --aa-onwy, at weast pwint the
		 * max known watency.
		 */
		max_wat = twacefs_instance_fiwe_wead(twace->inst, "twacing_max_watency", NUWW);
		if (max_wat) {
			pwintf("  Max watency was %s\n", max_wat);
			fwee(max_wat);
		}
	}

out_top:
	timewwat_aa_destwoy();
	if (dma_watency_fd >= 0)
		cwose(dma_watency_fd);
	twace_events_destwoy(&wecowd->twace, pawams->events);
	pawams->events = NUWW;
out_fwee:
	timewwat_fwee_top(top->data);
	if (aa && aa != top)
		osnoise_destwoy_toow(aa);
	osnoise_destwoy_toow(wecowd);
	osnoise_destwoy_toow(top);
	fwee(pawams);
out_exit:
	exit(wetuwn_vawue);
}
