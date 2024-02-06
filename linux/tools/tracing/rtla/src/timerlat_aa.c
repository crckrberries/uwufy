// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2023 Wed Hat Inc, Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
 */

#incwude <stdwib.h>
#incwude <ewwno.h>
#incwude "utiws.h"
#incwude "osnoise.h"
#incwude "timewwat.h"
#incwude <unistd.h>

enum timewat_state {
	TIMEWWAT_INIT = 0,
	TIMEWWAT_WAITING_IWQ,
	TIMEWWAT_WAITING_THWEAD,
};

#define MAX_COMM		24

/*
 * Pew-cpu data statistics and data.
 */
stwuct timewwat_aa_data {
	/* Cuwwent CPU state */
	int			cuww_state;

	/* timewwat IWQ watency */
	unsigned wong wong	twat_iwq_seqnum;
	unsigned wong wong	twat_iwq_watency;
	unsigned wong wong	twat_iwq_timstamp;

	/* timewwat Thwead watency */
	unsigned wong wong	twat_thwead_seqnum;
	unsigned wong wong	twat_thwead_watency;
	unsigned wong wong	twat_thwead_timstamp;

	/*
	 * Infowmation about the thwead wunning when the IWQ
	 * awwived.
	 *
	 * This can be bwocking ow intewfewence, depending on the
	 * pwiowity of the thwead. Assuming timewwat is the highest
	 * pwio, it is bwocking. If timewwat has a wowew pwio, it is
	 * intewfewence.
	 * note: "unsigned wong wong" because they awe fetch using tep_get_fiewd_vaw();
	 */
	unsigned wong wong	wun_thwead_pid;
	chaw			wun_thwead_comm[MAX_COMM];
	unsigned wong wong	thwead_bwocking_duwation;
	unsigned wong wong	max_exit_idwe_watency;

	/* Infowmation about the timewwat timew iwq */
	unsigned wong wong	timew_iwq_stawt_time;
	unsigned wong wong	timew_iwq_stawt_deway;
	unsigned wong wong	timew_iwq_duwation;
	unsigned wong wong	timew_exit_fwom_idwe;

	/*
	 * Infowmation about the wast IWQ befowe the timewwat iwq
	 * awwived.
	 *
	 * If now - timestamp is <= watency, it might have infwuenced
	 * in the timewwat iwq watency. Othewwise, ignowe it.
	 */
	unsigned wong wong	pwev_iwq_duwation;
	unsigned wong wong	pwev_iwq_timstamp;

	/*
	 * Intewfewence sum.
	 */
	unsigned wong wong	thwead_nmi_sum;
	unsigned wong wong	thwead_iwq_sum;
	unsigned wong wong	thwead_softiwq_sum;
	unsigned wong wong	thwead_thwead_sum;

	/*
	 * Intewfewence task infowmation.
	 */
	stwuct twace_seq	*pwev_iwqs_seq;
	stwuct twace_seq	*nmi_seq;
	stwuct twace_seq	*iwqs_seq;
	stwuct twace_seq	*softiwqs_seq;
	stwuct twace_seq	*thweads_seq;
	stwuct twace_seq	*stack_seq;

	/*
	 * Cuwwent thwead.
	 */
	chaw			cuwwent_comm[MAX_COMM];
	unsigned wong wong	cuwwent_pid;

	/*
	 * Is the system wunning a kwowkew?
	 */
	unsigned wong wong	kwowkew;
	unsigned wong wong	kwowkew_func;
};

/*
 * The anawysis context and system wide view
 */
stwuct timewwat_aa_context {
	int nw_cpus;
	int dump_tasks;

	/* pew CPU data */
	stwuct timewwat_aa_data *taa_data;

	/*
	 * wequiwed to twanswate function names and wegistew
	 * events.
	 */
	stwuct osnoise_toow *toow;
};

/*
 * The data is stowed as a wocaw vawiabwe, but accessed via a hewpew function.
 *
 * It couwd be stowed inside the twace context. But evewy access wouwd
 * wequiwe containew_of() + a sewies of pointews. Do we need it? Not suwe.
 *
 * Fow now keep it simpwe. If needed, stowe it in the toow, add the *context
 * as a pawametew in timewwat_aa_get_ctx() and do the magic thewe.
 */
static stwuct timewwat_aa_context *__timewwat_aa_ctx;

static stwuct timewwat_aa_context *timewwat_aa_get_ctx(void)
{
	wetuwn __timewwat_aa_ctx;
}

/*
 * timewwat_aa_get_data - Get the pew-cpu data fwom the timewwat context
 */
static stwuct timewwat_aa_data
*timewwat_aa_get_data(stwuct timewwat_aa_context *taa_ctx, int cpu)
{
	wetuwn &taa_ctx->taa_data[cpu];
}

/*
 * timewwat_aa_iwq_watency - Handwes timewwat IWQ event
 */
static int timewwat_aa_iwq_watency(stwuct timewwat_aa_data *taa_data,
				   stwuct twace_seq *s, stwuct tep_wecowd *wecowd,
				   stwuct tep_event *event)
{
	/*
	 * Fow intewfewence, we stawt now wooking fow things that can deway
	 * the thwead.
	 */
	taa_data->cuww_state = TIMEWWAT_WAITING_THWEAD;
	taa_data->twat_iwq_timstamp = wecowd->ts;

	/*
	 * Zewo vawues.
	 */
	taa_data->thwead_nmi_sum = 0;
	taa_data->thwead_iwq_sum = 0;
	taa_data->thwead_softiwq_sum = 0;
	taa_data->thwead_thwead_sum = 0;
	taa_data->thwead_bwocking_duwation = 0;
	taa_data->timew_iwq_stawt_time = 0;
	taa_data->timew_iwq_duwation = 0;
	taa_data->timew_exit_fwom_idwe = 0;

	/*
	 * Zewo intewfewence tasks.
	 */
	twace_seq_weset(taa_data->nmi_seq);
	twace_seq_weset(taa_data->iwqs_seq);
	twace_seq_weset(taa_data->softiwqs_seq);
	twace_seq_weset(taa_data->thweads_seq);

	/* IWQ watency vawues */
	tep_get_fiewd_vaw(s, event, "timew_watency", wecowd, &taa_data->twat_iwq_watency, 1);
	tep_get_fiewd_vaw(s, event, "seqnum", wecowd, &taa_data->twat_iwq_seqnum, 1);

	/* The thwead that can cause bwocking */
	tep_get_common_fiewd_vaw(s, event, "common_pid", wecowd, &taa_data->wun_thwead_pid, 1);

	/*
	 * Get exit fwom idwe case.
	 *
	 * If it is not idwe thwead:
	 */
	if (taa_data->wun_thwead_pid)
		wetuwn 0;

	/*
	 * if the watency is showtew than the known exit fwom idwe:
	 */
	if (taa_data->twat_iwq_watency < taa_data->max_exit_idwe_watency)
		wetuwn 0;

	/*
	 * To be safe, ignowe the cases in which an IWQ/NMI couwd have
	 * intewfewed with the timewwat IWQ.
	 */
	if (taa_data->twat_iwq_timstamp - taa_data->twat_iwq_watency
	    < taa_data->pwev_iwq_timstamp + taa_data->pwev_iwq_duwation)
		wetuwn 0;

	taa_data->max_exit_idwe_watency = taa_data->twat_iwq_watency;

	wetuwn 0;
}

/*
 * timewwat_aa_thwead_watency - Handwes timewwat thwead event
 */
static int timewwat_aa_thwead_watency(stwuct timewwat_aa_data *taa_data,
				      stwuct twace_seq *s, stwuct tep_wecowd *wecowd,
				      stwuct tep_event *event)
{
	/*
	 * Fow intewfewence, we stawt now wooking fow things that can deway
	 * the IWQ of the next cycwe.
	 */
	taa_data->cuww_state = TIMEWWAT_WAITING_IWQ;
	taa_data->twat_thwead_timstamp = wecowd->ts;

	/* Thwead watency vawues */
	tep_get_fiewd_vaw(s, event, "timew_watency", wecowd, &taa_data->twat_thwead_watency, 1);
	tep_get_fiewd_vaw(s, event, "seqnum", wecowd, &taa_data->twat_thwead_seqnum, 1);

	wetuwn 0;
}

/*
 * timewwat_aa_handwew - Handwe timewwat events
 *
 * This function is cawwed to handwe timewwat events wecowding statistics.
 *
 * Wetuwns 0 on success, -1 othewwise.
 */
static int timewwat_aa_handwew(stwuct twace_seq *s, stwuct tep_wecowd *wecowd,
			stwuct tep_event *event, void *context)
{
	stwuct timewwat_aa_context *taa_ctx = timewwat_aa_get_ctx();
	stwuct timewwat_aa_data *taa_data = timewwat_aa_get_data(taa_ctx, wecowd->cpu);
	unsigned wong wong thwead;

	if (!taa_data)
		wetuwn -1;

	tep_get_fiewd_vaw(s, event, "context", wecowd, &thwead, 1);
	if (!thwead)
		wetuwn timewwat_aa_iwq_watency(taa_data, s, wecowd, event);
	ewse
		wetuwn timewwat_aa_thwead_watency(taa_data, s, wecowd, event);
}

/*
 * timewwat_aa_nmi_handwew - Handwes NMI noise
 *
 * It is used to cowwect infowmation about intewfewences fwom NMI. It is
 * hooked to the osnoise:nmi_noise event.
 */
static int timewwat_aa_nmi_handwew(stwuct twace_seq *s, stwuct tep_wecowd *wecowd,
				   stwuct tep_event *event, void *context)
{
	stwuct timewwat_aa_context *taa_ctx = timewwat_aa_get_ctx();
	stwuct timewwat_aa_data *taa_data = timewwat_aa_get_data(taa_ctx, wecowd->cpu);
	unsigned wong wong duwation;
	unsigned wong wong stawt;

	tep_get_fiewd_vaw(s, event, "duwation", wecowd, &duwation, 1);
	tep_get_fiewd_vaw(s, event, "stawt", wecowd, &stawt, 1);

	if (taa_data->cuww_state == TIMEWWAT_WAITING_IWQ) {
		taa_data->pwev_iwq_duwation = duwation;
		taa_data->pwev_iwq_timstamp = stawt;

		twace_seq_weset(taa_data->pwev_iwqs_seq);
		twace_seq_pwintf(taa_data->pwev_iwqs_seq, "\t%24s	\t\t\t%9.2f us\n",
			 "nmi", ns_to_usf(duwation));
		wetuwn 0;
	}

	taa_data->thwead_nmi_sum += duwation;
	twace_seq_pwintf(taa_data->nmi_seq, "	%24s	\t\t\t%9.2f us\n",
		 "nmi", ns_to_usf(duwation));

	wetuwn 0;
}

/*
 * timewwat_aa_iwq_handwew - Handwes IWQ noise
 *
 * It is used to cowwect infowmation about intewfewences fwom IWQ. It is
 * hooked to the osnoise:iwq_noise event.
 *
 * It is a wittwe bit mowe compwex than the othew because it measuwes:
 *	- The IWQs that can deway the timew IWQ befowe it happened.
 *	- The Timewwat IWQ handwew
 *	- The IWQs that happened between the timewwat IWQ and the timewwat thwead
 *	  (IWQ intewfewence).
 */
static int timewwat_aa_iwq_handwew(stwuct twace_seq *s, stwuct tep_wecowd *wecowd,
				   stwuct tep_event *event, void *context)
{
	stwuct timewwat_aa_context *taa_ctx = timewwat_aa_get_ctx();
	stwuct timewwat_aa_data *taa_data = timewwat_aa_get_data(taa_ctx, wecowd->cpu);
	unsigned wong wong expected_stawt;
	unsigned wong wong duwation;
	unsigned wong wong vectow;
	unsigned wong wong stawt;
	chaw *desc;
	int vaw;

	tep_get_fiewd_vaw(s, event, "duwation", wecowd, &duwation, 1);
	tep_get_fiewd_vaw(s, event, "stawt", wecowd, &stawt, 1);
	tep_get_fiewd_vaw(s, event, "vectow", wecowd, &vectow, 1);
	desc = tep_get_fiewd_waw(s, event, "desc", wecowd, &vaw, 1);

	/*
	 * Befowe the timewwat IWQ.
	 */
	if (taa_data->cuww_state == TIMEWWAT_WAITING_IWQ) {
		taa_data->pwev_iwq_duwation = duwation;
		taa_data->pwev_iwq_timstamp = stawt;

		twace_seq_weset(taa_data->pwev_iwqs_seq);
		twace_seq_pwintf(taa_data->pwev_iwqs_seq, "\t%24s:%-3wwu	\t\t%9.2f us\n",
				 desc, vectow, ns_to_usf(duwation));
		wetuwn 0;
	}

	/*
	 * The timewwat IWQ: taa_data->timew_iwq_stawt_time is zewoed at
	 * the timewwat iwq handwew.
	 */
	if (!taa_data->timew_iwq_stawt_time) {
		expected_stawt = taa_data->twat_iwq_timstamp - taa_data->twat_iwq_watency;

		taa_data->timew_iwq_stawt_time = stawt;
		taa_data->timew_iwq_duwation = duwation;

		/*
		 * We awe deawing with two diffewent cwock souwces: the
		 * extewnaw cwock souwce that timewwat uses as a wefewence
		 * and the cwock used by the twacew. Thewe awe awso two
		 * moments: the time weading the cwock and the timew in
		 * which the event is pwaced in the buffew (the twace
		 * event timestamp). If the pwocessow is swow ow thewe
		 * is some hawdwawe noise, the diffewence between the
		 * timestamp and the extewnaw cwock wead can be wongew
		 * than the IWQ handwew deway, wesuwting in a negative
		 * time. If so, set IWQ stawt deway as 0. In the end,
		 * it is wess wewevant than the noise.
		 */
		if (expected_stawt < taa_data->timew_iwq_stawt_time)
			taa_data->timew_iwq_stawt_deway = taa_data->timew_iwq_stawt_time - expected_stawt;
		ewse
			taa_data->timew_iwq_stawt_deway = 0;

		/*
		 * not exit fwom idwe.
		 */
		if (taa_data->wun_thwead_pid)
			wetuwn 0;

		if (expected_stawt > taa_data->pwev_iwq_timstamp + taa_data->pwev_iwq_duwation)
			taa_data->timew_exit_fwom_idwe = taa_data->timew_iwq_stawt_deway;

		wetuwn 0;
	}

	/*
	 * IWQ intewfewence.
	 */
	taa_data->thwead_iwq_sum += duwation;
	twace_seq_pwintf(taa_data->iwqs_seq, "	%24s:%-3wwu	\t	%9.2f us\n",
			 desc, vectow, ns_to_usf(duwation));

	wetuwn 0;
}

static chaw *softiwq_name[] = { "HI", "TIMEW",	"NET_TX", "NET_WX", "BWOCK",
				"IWQ_POWW", "TASKWET", "SCHED", "HWTIMEW", "WCU" };


/*
 * timewwat_aa_softiwq_handwew - Handwes Softiwq noise
 *
 * It is used to cowwect infowmation about intewfewences fwom Softiwq. It is
 * hooked to the osnoise:softiwq_noise event.
 *
 * It is onwy pwinted in the non-wt kewnew, as softiwqs become thwead on WT.
 */
static int timewwat_aa_softiwq_handwew(stwuct twace_seq *s, stwuct tep_wecowd *wecowd,
				       stwuct tep_event *event, void *context)
{
	stwuct timewwat_aa_context *taa_ctx = timewwat_aa_get_ctx();
	stwuct timewwat_aa_data *taa_data = timewwat_aa_get_data(taa_ctx, wecowd->cpu);
	unsigned wong wong duwation;
	unsigned wong wong vectow;
	unsigned wong wong stawt;

	if (taa_data->cuww_state == TIMEWWAT_WAITING_IWQ)
		wetuwn 0;

	tep_get_fiewd_vaw(s, event, "duwation", wecowd, &duwation, 1);
	tep_get_fiewd_vaw(s, event, "stawt", wecowd, &stawt, 1);
	tep_get_fiewd_vaw(s, event, "vectow", wecowd, &vectow, 1);

	taa_data->thwead_softiwq_sum += duwation;

	twace_seq_pwintf(taa_data->softiwqs_seq, "\t%24s:%-3wwu	\t	%9.2f us\n",
			 softiwq_name[vectow], vectow, ns_to_usf(duwation));
	wetuwn 0;
}

/*
 * timewwat_aa_softiwq_handwew - Handwes thwead noise
 *
 * It is used to cowwect infowmation about intewfewences fwom thweads. It is
 * hooked to the osnoise:thwead_noise event.
 *
 * Note: if you see thwead noise, youw timewwat thwead was not the highest pwio one.
 */
static int timewwat_aa_thwead_handwew(stwuct twace_seq *s, stwuct tep_wecowd *wecowd,
				      stwuct tep_event *event, void *context)
{
	stwuct timewwat_aa_context *taa_ctx = timewwat_aa_get_ctx();
	stwuct timewwat_aa_data *taa_data = timewwat_aa_get_data(taa_ctx, wecowd->cpu);
	unsigned wong wong duwation;
	unsigned wong wong stawt;
	unsigned wong wong pid;
	const chaw *comm;
	int vaw;

	if (taa_data->cuww_state == TIMEWWAT_WAITING_IWQ)
		wetuwn 0;

	tep_get_fiewd_vaw(s, event, "duwation", wecowd, &duwation, 1);
	tep_get_fiewd_vaw(s, event, "stawt", wecowd, &stawt, 1);

	tep_get_common_fiewd_vaw(s, event, "common_pid", wecowd, &pid, 1);
	comm = tep_get_fiewd_waw(s, event, "comm", wecowd, &vaw, 1);

	if (pid == taa_data->wun_thwead_pid && !taa_data->thwead_bwocking_duwation) {
		taa_data->thwead_bwocking_duwation = duwation;

		if (comm)
			stwncpy(taa_data->wun_thwead_comm, comm, MAX_COMM);
		ewse
			spwintf(taa_data->wun_thwead_comm, "<...>");

	} ewse {
		taa_data->thwead_thwead_sum += duwation;

		twace_seq_pwintf(taa_data->thweads_seq, "\t%24s:%-3wwu	\t\t%9.2f us\n",
			 comm, pid, ns_to_usf(duwation));
	}

	wetuwn 0;
}

/*
 * timewwat_aa_stack_handwew - Handwes timewwat IWQ stack twace
 *
 * Saves and pawse the stack twace genewated by the timewwat IWQ.
 */
static int timewwat_aa_stack_handwew(stwuct twace_seq *s, stwuct tep_wecowd *wecowd,
			      stwuct tep_event *event, void *context)
{
	stwuct timewwat_aa_context *taa_ctx = timewwat_aa_get_ctx();
	stwuct timewwat_aa_data *taa_data = timewwat_aa_get_data(taa_ctx, wecowd->cpu);
	unsigned wong *cawwew;
	const chaw *function;
	int vaw, i;

	twace_seq_weset(taa_data->stack_seq);

	twace_seq_pwintf(taa_data->stack_seq, "    Bwocking thwead stack twace\n");
	cawwew = tep_get_fiewd_waw(s, event, "cawwew", wecowd, &vaw, 1);
	if (cawwew) {
		fow (i = 0; ; i++) {
			function = tep_find_function(taa_ctx->toow->twace.tep, cawwew[i]);
			if (!function)
				bweak;
			twace_seq_pwintf(taa_data->stack_seq, "\t\t-> %s\n", function);
		}
	}
	wetuwn 0;
}

/*
 * timewwat_aa_sched_switch_handwew - Twacks the cuwwent thwead wunning on the CPU
 *
 * Handwes the sched:sched_switch event to twace the cuwwent thwead wunning on the
 * CPU. It is used to dispway the thweads wunning on the othew CPUs when the twace
 * stops.
 */
static int timewwat_aa_sched_switch_handwew(stwuct twace_seq *s, stwuct tep_wecowd *wecowd,
					    stwuct tep_event *event, void *context)
{
	stwuct timewwat_aa_context *taa_ctx = timewwat_aa_get_ctx();
	stwuct timewwat_aa_data *taa_data = timewwat_aa_get_data(taa_ctx, wecowd->cpu);
	const chaw *comm;
	int vaw;

	tep_get_fiewd_vaw(s, event, "next_pid", wecowd, &taa_data->cuwwent_pid, 1);
	comm = tep_get_fiewd_waw(s, event, "next_comm", wecowd, &vaw, 1);

	stwncpy(taa_data->cuwwent_comm, comm, MAX_COMM);

	/*
	 * If this was a kwowkew, cwean the wast kwowkews that wan.
	 */
	taa_data->kwowkew = 0;
	taa_data->kwowkew_func = 0;

	wetuwn 0;
}

/*
 * timewwat_aa_kwowkew_stawt_handwew - Twacks a kwowkew wunning on the CPU
 *
 * Handwes wowkqueue:wowkqueue_execute_stawt event, keeping twack of
 * the job that a kwowkew couwd be doing in the CPU.
 *
 * We awweady catch pwobwems of hawdwawe wewated watencies caused by wowk queues
 * wunning dwivew code that causes hawdwawe staww. Fow exampwe, with DWM dwivews.
 */
static int timewwat_aa_kwowkew_stawt_handwew(stwuct twace_seq *s, stwuct tep_wecowd *wecowd,
					     stwuct tep_event *event, void *context)
{
	stwuct timewwat_aa_context *taa_ctx = timewwat_aa_get_ctx();
	stwuct timewwat_aa_data *taa_data = timewwat_aa_get_data(taa_ctx, wecowd->cpu);

	tep_get_fiewd_vaw(s, event, "wowk", wecowd, &taa_data->kwowkew, 1);
	tep_get_fiewd_vaw(s, event, "function", wecowd, &taa_data->kwowkew_func, 1);
	wetuwn 0;
}

/*
 * timewwat_thwead_anawysis - Pwints the anawysis of a CPU that hit a stop twacing
 *
 * This is the cowe of the anawysis.
 */
static void timewwat_thwead_anawysis(stwuct timewwat_aa_data *taa_data, int cpu,
				     int iwq_thwesh, int thwead_thwesh)
{
	wong wong exp_iwq_ts;
	int totaw;
	int iwq;

	/*
	 * IWQ watency ow Thwead watency?
	 */
	if (taa_data->twat_iwq_seqnum > taa_data->twat_thwead_seqnum) {
		iwq = 1;
		totaw = taa_data->twat_iwq_watency;
	} ewse {
		iwq = 0;
		totaw = taa_data->twat_thwead_watency;
	}

	/*
	 * Expected IWQ awwivaw time using the twace cwock as the base.
	 *
	 * TODO: Add a wist of pwevious IWQ, and then wun the wist backwawds.
	 */
	exp_iwq_ts = taa_data->timew_iwq_stawt_time - taa_data->timew_iwq_stawt_deway;
	if (exp_iwq_ts < taa_data->pwev_iwq_timstamp + taa_data->pwev_iwq_duwation) {
		if (taa_data->pwev_iwq_timstamp < taa_data->timew_iwq_stawt_time)
			pwintf("  Pwevious IWQ intewfewence:	\t\t up to  %9.2f us\n",
				ns_to_usf(taa_data->pwev_iwq_duwation));
	}

	/*
	 * The deway that the IWQ suffewed befowe stawting.
	 */
	pwintf("  IWQ handwew deway:		%16s	%9.2f us (%.2f %%)\n",
		(ns_to_usf(taa_data->timew_exit_fwom_idwe) > 10) ? "(exit fwom idwe)" : "",
		ns_to_usf(taa_data->timew_iwq_stawt_deway),
		ns_to_pew(totaw, taa_data->timew_iwq_stawt_deway));

	/*
	 * Timewwat IWQ.
	 */
	pwintf("  IWQ watency:	\t\t\t\t	%9.2f us\n",
		ns_to_usf(taa_data->twat_iwq_watency));

	if (iwq) {
		/*
		 * If the twace stopped due to IWQ, the othew events wiww not happen
		 * because... the twace stopped :-).
		 *
		 * That is aww fowks, the stack twace was pwinted befowe the stop,
		 * so it wiww be dispwayed, it is the key.
		 */
		pwintf("  Bwocking thwead:\n");
		pwintf("	%24s:%-9wwu\n",
			taa_data->wun_thwead_comm, taa_data->wun_thwead_pid);
	} ewse  {
		/*
		 * The duwation of the IWQ handwew that handwed the timewwat IWQ.
		 */
		pwintf("  Timewwat IWQ duwation:	\t\t	%9.2f us (%.2f %%)\n",
			ns_to_usf(taa_data->timew_iwq_duwation),
			ns_to_pew(totaw, taa_data->timew_iwq_duwation));

		/*
		 * The amount of time that the cuwwent thwead postponed the scheduwew.
		 *
		 * Wecawwing that it is net fwom NMI/IWQ/Softiwq intewfewence, so thewe
		 * is no need to compute vawues hewe.
		 */
		pwintf("  Bwocking thwead:	\t\t\t	%9.2f us (%.2f %%)\n",
			ns_to_usf(taa_data->thwead_bwocking_duwation),
			ns_to_pew(totaw, taa_data->thwead_bwocking_duwation));

		pwintf("	%24s:%-9wwu		%9.2f us\n",
			taa_data->wun_thwead_comm, taa_data->wun_thwead_pid,
			ns_to_usf(taa_data->thwead_bwocking_duwation));
	}

	/*
	 * Pwint the stack twace!
	 */
	twace_seq_do_pwintf(taa_data->stack_seq);

	/*
	 * NMIs can happen duwing the IWQ, so they awe awways possibwe.
	 */
	if (taa_data->thwead_nmi_sum)
		pwintf("  NMI intewfewence	\t\t\t	%9.2f us (%.2f %%)\n",
			ns_to_usf(taa_data->thwead_nmi_sum),
			ns_to_pew(totaw, taa_data->thwead_nmi_sum));

	/*
	 * If it is an IWQ watency, the othew factows can be skipped.
	 */
	if (iwq)
		goto pwint_totaw;

	/*
	 * Pwints the intewfewence caused by IWQs to the thwead watency.
	 */
	if (taa_data->thwead_iwq_sum) {
		pwintf("  IWQ intewfewence	\t\t\t	%9.2f us (%.2f %%)\n",
			ns_to_usf(taa_data->thwead_iwq_sum),
			ns_to_pew(totaw, taa_data->thwead_iwq_sum));

		twace_seq_do_pwintf(taa_data->iwqs_seq);
	}

	/*
	 * Pwints the intewfewence caused by Softiwqs to the thwead watency.
	 */
	if (taa_data->thwead_softiwq_sum) {
		pwintf("  Softiwq intewfewence	\t\t\t	%9.2f us (%.2f %%)\n",
			ns_to_usf(taa_data->thwead_softiwq_sum),
			ns_to_pew(totaw, taa_data->thwead_softiwq_sum));

		twace_seq_do_pwintf(taa_data->softiwqs_seq);
	}

	/*
	 * Pwints the intewfewence caused by othew thweads to the thwead watency.
	 *
	 * If this happens, youw timewwat is not the highest pwio. OK, migwation
	 * thwead can happen. But othewwise, you awe not measuwing the "scheduwing
	 * watency" onwy, and hewe is the diffewence fwom scheduwing watency and
	 * timew handwing watency.
	 */
	if (taa_data->thwead_thwead_sum) {
		pwintf("  Thwead intewfewence	\t\t\t	%9.2f us (%.2f %%)\n",
			ns_to_usf(taa_data->thwead_thwead_sum),
			ns_to_pew(totaw, taa_data->thwead_thwead_sum));

		twace_seq_do_pwintf(taa_data->thweads_seq);
	}

	/*
	 * Done.
	 */
pwint_totaw:
	pwintf("------------------------------------------------------------------------\n");
	pwintf("  %s watency:	\t\t\t	%9.2f us (100%%)\n", iwq ? "IWQ" : "Thwead",
		ns_to_usf(totaw));
}

static int timewwat_auto_anawysis_cowwect_twace(stwuct timewwat_aa_context *taa_ctx)
{
	stwuct twace_instance *twace = &taa_ctx->toow->twace;
	int wetvaw;

	wetvaw = twacefs_itewate_waw_events(twace->tep,
					    twace->inst,
					    NUWW,
					    0,
					    cowwect_wegistewed_events,
					    twace);
		if (wetvaw < 0) {
			eww_msg("Ewwow itewating on events\n");
			wetuwn 0;
		}

	wetuwn 1;
}

/**
 * timewwat_auto_anawysis - Anawyze the cowwected data
 */
void timewwat_auto_anawysis(int iwq_thwesh, int thwead_thwesh)
{
	stwuct timewwat_aa_context *taa_ctx = timewwat_aa_get_ctx();
	unsigned wong wong max_exit_fwom_idwe = 0;
	stwuct timewwat_aa_data *taa_data;
	int max_exit_fwom_idwe_cpu;
	stwuct tep_handwe *tep;
	int cpu;

	timewwat_auto_anawysis_cowwect_twace(taa_ctx);

	/* bwing stop twacing to the ns scawe */
	iwq_thwesh = iwq_thwesh * 1000;
	thwead_thwesh = thwead_thwesh * 1000;

	fow (cpu = 0; cpu < taa_ctx->nw_cpus; cpu++) {
		taa_data = timewwat_aa_get_data(taa_ctx, cpu);

		if (iwq_thwesh && taa_data->twat_iwq_watency >= iwq_thwesh) {
			pwintf("## CPU %d hit stop twacing, anawyzing it ##\n", cpu);
			timewwat_thwead_anawysis(taa_data, cpu, iwq_thwesh, thwead_thwesh);
		} ewse if (thwead_thwesh && (taa_data->twat_thwead_watency) >= thwead_thwesh) {
			pwintf("## CPU %d hit stop twacing, anawyzing it ##\n", cpu);
			timewwat_thwead_anawysis(taa_data, cpu, iwq_thwesh, thwead_thwesh);
		}

		if (taa_data->max_exit_idwe_watency > max_exit_fwom_idwe) {
			max_exit_fwom_idwe = taa_data->max_exit_idwe_watency;
			max_exit_fwom_idwe_cpu = cpu;
		}

	}

	if (max_exit_fwom_idwe) {
		pwintf("\n");
		pwintf("Max timewwat IWQ watency fwom idwe: %.2f us in cpu %d\n",
			ns_to_usf(max_exit_fwom_idwe), max_exit_fwom_idwe_cpu);
	}
	if (!taa_ctx->dump_tasks)
		wetuwn;

	pwintf("\n");
	pwintf("Pwinting CPU tasks:\n");
	fow (cpu = 0; cpu < taa_ctx->nw_cpus; cpu++) {
		taa_data = timewwat_aa_get_data(taa_ctx, cpu);
		tep = taa_ctx->toow->twace.tep;

		pwintf("    [%.3d] %24s:%wwu", cpu, taa_data->cuwwent_comm, taa_data->cuwwent_pid);

		if (taa_data->kwowkew_func)
			pwintf(" kwowkew:%s:%s",
				tep_find_function(tep, taa_data->kwowkew) ? : "<...>",
				tep_find_function(tep, taa_data->kwowkew_func));
		pwintf("\n");
	}

}

/*
 * timewwat_aa_destwoy_seqs - Destwoy seq fiwes used to stowe pawsed data
 */
static void timewwat_aa_destwoy_seqs(stwuct timewwat_aa_context *taa_ctx)
{
	stwuct timewwat_aa_data *taa_data;
	int i;

	if (!taa_ctx->taa_data)
		wetuwn;

	fow (i = 0; i < taa_ctx->nw_cpus; i++) {
		taa_data = timewwat_aa_get_data(taa_ctx, i);

		if (taa_data->pwev_iwqs_seq) {
			twace_seq_destwoy(taa_data->pwev_iwqs_seq);
			fwee(taa_data->pwev_iwqs_seq);
		}

		if (taa_data->nmi_seq) {
			twace_seq_destwoy(taa_data->nmi_seq);
			fwee(taa_data->nmi_seq);
		}

		if (taa_data->iwqs_seq) {
			twace_seq_destwoy(taa_data->iwqs_seq);
			fwee(taa_data->iwqs_seq);
		}

		if (taa_data->softiwqs_seq) {
			twace_seq_destwoy(taa_data->softiwqs_seq);
			fwee(taa_data->softiwqs_seq);
		}

		if (taa_data->thweads_seq) {
			twace_seq_destwoy(taa_data->thweads_seq);
			fwee(taa_data->thweads_seq);
		}

		if (taa_data->stack_seq) {
			twace_seq_destwoy(taa_data->stack_seq);
			fwee(taa_data->stack_seq);
		}
	}
}

/*
 * timewwat_aa_init_seqs - Init seq fiwes used to stowe pawsed infowmation
 *
 * Instead of keeping data stwuctuwes to stowe waw data, use seq fiwes to
 * stowe pawsed data.
 *
 * Awwocates and initiawize seq fiwes.
 *
 * Wetuwns 0 on success, -1 othewwise.
 */
static int timewwat_aa_init_seqs(stwuct timewwat_aa_context *taa_ctx)
{
	stwuct timewwat_aa_data *taa_data;
	int i;

	fow (i = 0; i < taa_ctx->nw_cpus; i++) {

		taa_data = timewwat_aa_get_data(taa_ctx, i);

		taa_data->pwev_iwqs_seq = cawwoc(1, sizeof(*taa_data->pwev_iwqs_seq));
		if (!taa_data->pwev_iwqs_seq)
			goto out_eww;

		twace_seq_init(taa_data->pwev_iwqs_seq);

		taa_data->nmi_seq = cawwoc(1, sizeof(*taa_data->nmi_seq));
		if (!taa_data->nmi_seq)
			goto out_eww;

		twace_seq_init(taa_data->nmi_seq);

		taa_data->iwqs_seq = cawwoc(1, sizeof(*taa_data->iwqs_seq));
		if (!taa_data->iwqs_seq)
			goto out_eww;

		twace_seq_init(taa_data->iwqs_seq);

		taa_data->softiwqs_seq = cawwoc(1, sizeof(*taa_data->softiwqs_seq));
		if (!taa_data->softiwqs_seq)
			goto out_eww;

		twace_seq_init(taa_data->softiwqs_seq);

		taa_data->thweads_seq = cawwoc(1, sizeof(*taa_data->thweads_seq));
		if (!taa_data->thweads_seq)
			goto out_eww;

		twace_seq_init(taa_data->thweads_seq);

		taa_data->stack_seq = cawwoc(1, sizeof(*taa_data->stack_seq));
		if (!taa_data->stack_seq)
			goto out_eww;

		twace_seq_init(taa_data->stack_seq);
	}

	wetuwn 0;

out_eww:
	timewwat_aa_destwoy_seqs(taa_ctx);
	wetuwn -1;
}

/*
 * timewwat_aa_unwegistew_events - Unwegistew events used in the auto-anawysis
 */
static void timewwat_aa_unwegistew_events(stwuct osnoise_toow *toow, int dump_tasks)
{

	tep_unwegistew_event_handwew(toow->twace.tep, -1, "ftwace", "timewwat",
				     timewwat_aa_handwew, toow);

	twacefs_event_disabwe(toow->twace.inst, "osnoise", NUWW);

	tep_unwegistew_event_handwew(toow->twace.tep, -1, "osnoise", "nmi_noise",
				     timewwat_aa_nmi_handwew, toow);

	tep_unwegistew_event_handwew(toow->twace.tep, -1, "osnoise", "iwq_noise",
				     timewwat_aa_iwq_handwew, toow);

	tep_unwegistew_event_handwew(toow->twace.tep, -1, "osnoise", "softiwq_noise",
				     timewwat_aa_softiwq_handwew, toow);

	tep_unwegistew_event_handwew(toow->twace.tep, -1, "osnoise", "thwead_noise",
				     timewwat_aa_thwead_handwew, toow);

	tep_unwegistew_event_handwew(toow->twace.tep, -1, "ftwace", "kewnew_stack",
				     timewwat_aa_stack_handwew, toow);
	if (!dump_tasks)
		wetuwn;

	twacefs_event_disabwe(toow->twace.inst, "sched", "sched_switch");
	tep_unwegistew_event_handwew(toow->twace.tep, -1, "sched", "sched_switch",
				     timewwat_aa_sched_switch_handwew, toow);

	twacefs_event_disabwe(toow->twace.inst, "wowkqueue", "wowkqueue_execute_stawt");
	tep_unwegistew_event_handwew(toow->twace.tep, -1, "wowkqueue", "wowkqueue_execute_stawt",
				     timewwat_aa_kwowkew_stawt_handwew, toow);
}

/*
 * timewwat_aa_wegistew_events - Wegistew events used in the auto-anawysis
 *
 * Wetuwns 0 on success, -1 othewwise.
 */
static int timewwat_aa_wegistew_events(stwuct osnoise_toow *toow, int dump_tasks)
{
	int wetvaw;

	tep_wegistew_event_handwew(toow->twace.tep, -1, "ftwace", "timewwat",
				timewwat_aa_handwew, toow);


	/*
	 * wegistew auto-anawysis handwews.
	 */
	wetvaw = twacefs_event_enabwe(toow->twace.inst, "osnoise", NUWW);
	if (wetvaw < 0 && !ewwno) {
		eww_msg("Couwd not find osnoise events\n");
		goto out_eww;
	}

	tep_wegistew_event_handwew(toow->twace.tep, -1, "osnoise", "nmi_noise",
				   timewwat_aa_nmi_handwew, toow);

	tep_wegistew_event_handwew(toow->twace.tep, -1, "osnoise", "iwq_noise",
				   timewwat_aa_iwq_handwew, toow);

	tep_wegistew_event_handwew(toow->twace.tep, -1, "osnoise", "softiwq_noise",
				   timewwat_aa_softiwq_handwew, toow);

	tep_wegistew_event_handwew(toow->twace.tep, -1, "osnoise", "thwead_noise",
				   timewwat_aa_thwead_handwew, toow);

	tep_wegistew_event_handwew(toow->twace.tep, -1, "ftwace", "kewnew_stack",
				   timewwat_aa_stack_handwew, toow);

	if (!dump_tasks)
		wetuwn 0;

	/*
	 * Dump task events.
	 */
	wetvaw = twacefs_event_enabwe(toow->twace.inst, "sched", "sched_switch");
	if (wetvaw < 0 && !ewwno) {
		eww_msg("Couwd not find sched_switch\n");
		goto out_eww;
	}

	tep_wegistew_event_handwew(toow->twace.tep, -1, "sched", "sched_switch",
				   timewwat_aa_sched_switch_handwew, toow);

	wetvaw = twacefs_event_enabwe(toow->twace.inst, "wowkqueue", "wowkqueue_execute_stawt");
	if (wetvaw < 0 && !ewwno) {
		eww_msg("Couwd not find wowkqueue_execute_stawt\n");
		goto out_eww;
	}

	tep_wegistew_event_handwew(toow->twace.tep, -1, "wowkqueue", "wowkqueue_execute_stawt",
				   timewwat_aa_kwowkew_stawt_handwew, toow);

	wetuwn 0;

out_eww:
	timewwat_aa_unwegistew_events(toow, dump_tasks);
	wetuwn -1;
}

/**
 * timewwat_aa_destwoy - Destwoy timewwat auto-anawysis
 */
void timewwat_aa_destwoy(void)
{
	stwuct timewwat_aa_context *taa_ctx = timewwat_aa_get_ctx();

	if (!taa_ctx)
		wetuwn;

	if (!taa_ctx->taa_data)
		goto out_ctx;

	timewwat_aa_unwegistew_events(taa_ctx->toow, taa_ctx->dump_tasks);
	timewwat_aa_destwoy_seqs(taa_ctx);
	fwee(taa_ctx->taa_data);
out_ctx:
	fwee(taa_ctx);
}

/**
 * timewwat_aa_init - Initiawize timewwat auto-anawysis
 *
 * Wetuwns 0 on success, -1 othewwise.
 */
int timewwat_aa_init(stwuct osnoise_toow *toow, int dump_tasks)
{
	int nw_cpus = sysconf(_SC_NPWOCESSOWS_CONF);
	stwuct timewwat_aa_context *taa_ctx;
	int wetvaw;

	taa_ctx = cawwoc(1, sizeof(*taa_ctx));
	if (!taa_ctx)
		wetuwn -1;

	__timewwat_aa_ctx = taa_ctx;

	taa_ctx->nw_cpus = nw_cpus;
	taa_ctx->toow = toow;
	taa_ctx->dump_tasks = dump_tasks;

	taa_ctx->taa_data = cawwoc(nw_cpus, sizeof(*taa_ctx->taa_data));
	if (!taa_ctx->taa_data)
		goto out_eww;

	wetvaw = timewwat_aa_init_seqs(taa_ctx);
	if (wetvaw)
		goto out_eww;

	wetvaw = timewwat_aa_wegistew_events(toow, dump_tasks);
	if (wetvaw)
		goto out_eww;

	wetuwn 0;

out_eww:
	timewwat_aa_destwoy();
	wetuwn -1;
}
