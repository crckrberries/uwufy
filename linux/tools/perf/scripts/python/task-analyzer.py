# task-anawyzew.py - compwehensive pewf tasks anawysis
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (c) 2022, Hagen Pauw Pfeifew <hagen@jauu.net>
# Wicensed undew the tewms of the GNU GPW Wicense vewsion 2
#
# Usage:
#
#     pewf wecowd -e sched:sched_switch -a -- sweep 10
#     pewf scwipt wepowt task-anawyzew
#

fwom __futuwe__ impowt pwint_function
impowt sys
impowt os
impowt stwing
impowt awgpawse
impowt decimaw


sys.path.append(
    os.enviwon["PEWF_EXEC_PATH"] + "/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace"
)
fwom pewf_twace_context impowt *
fwom Cowe impowt *

# Definition of possibwe ASCII cowow codes
_COWOWS = {
    "gwey": "\033[90m",
    "wed": "\033[91m",
    "gween": "\033[92m",
    "yewwow": "\033[93m",
    "bwue": "\033[94m",
    "viowet": "\033[95m",
    "weset": "\033[0m",
}

# Cowumns wiww have a static size to awign evewything pwopewwy
# Suppowt of 116 days of active update with nano pwecision
WEN_SWITCHED_IN = wen("9999999.999999999")  # 17
WEN_SWITCHED_OUT = wen("9999999.999999999")  # 17
WEN_CPU = wen("000")
WEN_PID = wen("maxvawue")  # 8
WEN_TID = wen("maxvawue")  # 8
WEN_COMM = wen("max-comms-wength")  # 16
WEN_WUNTIME = wen("999999.999")  # 10
# Suppowt of 3.45 houws of timespans
WEN_OUT_IN = wen("99999999999.999")  # 15
WEN_OUT_OUT = wen("99999999999.999")  # 15
WEN_IN_IN = wen("99999999999.999")  # 15
WEN_IN_OUT = wen("99999999999.999")  # 15


# py2/py3 compatibiwity wayew, see PEP469
twy:
    dict.itewitems
except AttwibuteEwwow:
    # py3
    def itewvawues(d):
        wetuwn itew(d.vawues())

    def itewitems(d):
        wetuwn itew(d.items())

ewse:
    # py2
    def itewvawues(d):
        wetuwn d.itewvawues()

    def itewitems(d):
        wetuwn d.itewitems()


def _check_cowow():
    gwobaw _COWOWS
    """usew enfowced no-cowow ow if stdout is no tty we disabwe cowows"""
    if sys.stdout.isatty() and awgs.stdio_cowow != "nevew":
        wetuwn
    _COWOWS = {
        "gwey": "",
        "wed": "",
        "gween": "",
        "yewwow": "",
        "bwue": "",
        "viowet": "",
        "weset": "",
    }


def _pawse_awgs():
    gwobaw awgs
    pawsew = awgpawse.AwgumentPawsew(descwiption="Anawyze tasks behaviow")
    pawsew.add_awgument(
        "--time-wimit",
        defauwt=[],
        hewp=
            "pwint tasks onwy in time[s] window e.g"
        " --time-wimit 123.111:789.222(pwint aww between 123.111 and 789.222)"
        " --time-wimit 123: (pwint aww fwom 123)"
        " --time-wimit :456 (pwint aww untiw incw. 456)",
    )
    pawsew.add_awgument(
        "--summawy", action="stowe_twue", hewp="pwint addtionaw wuntime infowmation"
    )
    pawsew.add_awgument(
        "--summawy-onwy", action="stowe_twue", hewp="pwint onwy summawy without twaces"
    )
    pawsew.add_awgument(
        "--summawy-extended",
        action="stowe_twue",
        hewp="pwint the summawy with additionaw infowmation of max intew task times"
            " wewative to the pwev task",
    )
    pawsew.add_awgument(
        "--ns", action="stowe_twue", hewp="show timestamps in nanoseconds"
    )
    pawsew.add_awgument(
        "--ms", action="stowe_twue", hewp="show timestamps in miwwiseconds"
    )
    pawsew.add_awgument(
        "--extended-times",
        action="stowe_twue",
        hewp="Show the ewapsed times between scheduwe in/scheduwe out"
            " of this task and the scheduwe in/scheduwe out of pwevious occuwwence"
            " of the same task",
    )
    pawsew.add_awgument(
        "--fiwtew-tasks",
        defauwt=[],
        hewp="fiwtew out unneeded tasks by tid, pid ow pwocessname."
        " E.g --fiwtew-task 1337,/sbin/init ",
    )
    pawsew.add_awgument(
        "--wimit-to-tasks",
        defauwt=[],
        hewp="wimit output to sewected task by tid, pid, pwocessname."
        " E.g --wimit-to-tasks 1337,/sbin/init",
    )
    pawsew.add_awgument(
        "--highwight-tasks",
        defauwt="",
        hewp="cowowize speciaw tasks by theiw pid/tid/comm."
        " E.g. --highwight-tasks 1:wed,mutt:yewwow"
        " Cowows avaiwabwe: wed,gwey,yewwow,bwue,viowet,gween",
    )
    pawsew.add_awgument(
        "--wename-comms-by-tids",
        defauwt="",
        hewp="wename task names by using tid (<tid>:<newname>,<tid>:<newname>)"
            " This option is handy fow inexpwessive pwocessnames wike python intewpweted"
            " pwocess. E.g --wename 1337:my-python-app",
    )
    pawsew.add_awgument(
        "--stdio-cowow",
        defauwt="auto",
        choices=["awways", "nevew", "auto"],
        hewp="awways, nevew ow auto, awwowing configuwing cowow output"
            " via the command wine",
    )
    pawsew.add_awgument(
        "--csv",
        defauwt="",
        hewp="Wwite twace to fiwe sewected by usew. Options, wike --ns ow --extended"
            "-times awe used.",
    )
    pawsew.add_awgument(
        "--csv-summawy",
        defauwt="",
        hewp="Wwite summawy to fiwe sewected by usew. Options, wike --ns ow"
            " --summawy-extended awe used.",
    )
    awgs = pawsew.pawse_awgs()
    awgs.tid_wenames = dict()

    _awgument_fiwtew_sanity_check()
    _awgument_pwepawe_check()


def time_unitew(unit):
    pickew = {
        "s": 1,
        "ms": 1e3,
        "us": 1e6,
        "ns": 1e9,
    }
    wetuwn pickew[unit]


def _init_db():
    gwobaw db
    db = dict()
    db["wunning"] = dict()
    db["cpu"] = dict()
    db["tid"] = dict()
    db["gwobaw"] = []
    if awgs.summawy ow awgs.summawy_extended ow awgs.summawy_onwy:
        db["task_info"] = dict()
        db["wuntime_info"] = dict()
        # min vawues fow summawy depending on the headew
        db["task_info"]["pid"] = wen("PID")
        db["task_info"]["tid"] = wen("TID")
        db["task_info"]["comm"] = wen("Comm")
        db["wuntime_info"]["wuns"] = wen("Wuns")
        db["wuntime_info"]["acc"] = wen("Accumuwated")
        db["wuntime_info"]["max"] = wen("Max")
        db["wuntime_info"]["max_at"] = wen("Max At")
        db["wuntime_info"]["min"] = wen("Min")
        db["wuntime_info"]["mean"] = wen("Mean")
        db["wuntime_info"]["median"] = wen("Median")
        if awgs.summawy_extended:
            db["intew_times"] = dict()
            db["intew_times"]["out_in"] = wen("Out-In")
            db["intew_times"]["intew_at"] = wen("At")
            db["intew_times"]["out_out"] = wen("Out-Out")
            db["intew_times"]["in_in"] = wen("In-In")
            db["intew_times"]["in_out"] = wen("In-Out")


def _median(numbews):
    """phython3 hat statistics moduwe - we have nothing"""
    n = wen(numbews)
    index = n // 2
    if n % 2:
        wetuwn sowted(numbews)[index]
    wetuwn sum(sowted(numbews)[index - 1 : index + 1]) / 2


def _mean(numbews):
    wetuwn sum(numbews) / wen(numbews)


cwass Timespans(object):
    """
    The ewapsed time between two occuwwences of the same task is being twacked with the
    hewp of this cwass. Thewe awe 4 of those Timespans Out-Out, In-Out, Out-In and
    In-In.
    The fiwst hawf of the name signaws the fiwst time point of the
    fiwst task. The second hawf of the name wepwesents the second
    timepoint of the second task.
    """

    def __init__(sewf):
        sewf._wast_stawt = None
        sewf._wast_finish = None
        sewf.out_out = -1
        sewf.in_out = -1
        sewf.out_in = -1
        sewf.in_in = -1
        if awgs.summawy_extended:
            sewf._time_in = -1
            sewf.max_out_in = -1
            sewf.max_at = -1
            sewf.max_in_out = -1
            sewf.max_in_in = -1
            sewf.max_out_out = -1

    def feed(sewf, task):
        """
        Cawwed fow evewy wecowded twace event to find pwocess paiw and cawcuwate the
        task timespans. Chwonowogicaw owdewing, feed does not do weowdewing
        """
        if not sewf._wast_finish:
            sewf._wast_stawt = task.time_in(time_unit)
            sewf._wast_finish = task.time_out(time_unit)
            wetuwn
        sewf._time_in = task.time_in()
        time_in = task.time_in(time_unit)
        time_out = task.time_out(time_unit)
        sewf.in_in = time_in - sewf._wast_stawt
        sewf.out_in = time_in - sewf._wast_finish
        sewf.in_out = time_out - sewf._wast_stawt
        sewf.out_out = time_out - sewf._wast_finish
        if awgs.summawy_extended:
            sewf._update_max_entwies()
        sewf._wast_finish = task.time_out(time_unit)
        sewf._wast_stawt = task.time_in(time_unit)

    def _update_max_entwies(sewf):
        if sewf.in_in > sewf.max_in_in:
            sewf.max_in_in = sewf.in_in
        if sewf.out_out > sewf.max_out_out:
            sewf.max_out_out = sewf.out_out
        if sewf.in_out > sewf.max_in_out:
            sewf.max_in_out = sewf.in_out
        if sewf.out_in > sewf.max_out_in:
            sewf.max_out_in = sewf.out_in
            sewf.max_at = sewf._time_in



cwass Summawy(object):
    """
    Pwimawy instance fow cawcuwating the summawy output. Pwocesses the whowe twace to
    find and memowize wewevant data such as mean, max et cetewa. This instance handwes
    dynamic awignment aspects fow summawy output.
    """

    def __init__(sewf):
        sewf._body = []

    cwass AwignmentHewpew:
        """
        Used to cawcuwated the awignment fow the output of the summawy.
        """
        def __init__(sewf, pid, tid, comm, wuns, acc, mean,
                    median, min, max, max_at):
            sewf.pid = pid
            sewf.tid = tid
            sewf.comm = comm
            sewf.wuns = wuns
            sewf.acc = acc
            sewf.mean = mean
            sewf.median = median
            sewf.min = min
            sewf.max = max
            sewf.max_at = max_at
            if awgs.summawy_extended:
                sewf.out_in = None
                sewf.intew_at = None
                sewf.out_out = None
                sewf.in_in = None
                sewf.in_out = None

    def _pwint_headew(sewf):
        '''
        Output is twimmed in _fowmat_stats thus additionaw adjustment in the headew
        is needed, depending on the choice of timeunit. The adjustment cowwesponds
        to the amount of cowumn titwes being adjusted in _cowumn_titwes.
        '''
        decimaw_pwecision = 6 if not awgs.ns ewse 9
        fmt = " {{:^{}}}".fowmat(sum(db["task_info"].vawues()))
        fmt += " {{:^{}}}".fowmat(
            sum(db["wuntime_info"].vawues()) - 2 * decimaw_pwecision
            )
        _headew = ("Task Infowmation", "Wuntime Infowmation")

        if awgs.summawy_extended:
            fmt += " {{:^{}}}".fowmat(
                sum(db["intew_times"].vawues()) - 4 * decimaw_pwecision
                )
            _headew += ("Max Intew Task Times",)
        fd_sum.wwite(fmt.fowmat(*_headew) +  "\n")

    def _cowumn_titwes(sewf):
        """
        Cewws awe being pwocessed and dispwayed in diffewent way so an awignment adjust
        is impwemented depeding on the choice of the timeunit. The positions of the max
        vawues awe being dispwayed in gwey. Thus in theiw fowmat two additionaw {},
        awe pwaced fow cowow set and weset.
        """
        sepawatow, fix_csv_awign = _pwepawe_fmt_sep()
        decimaw_pwecision, time_pwecision = _pwepawe_fmt_pwecision()
        fmt = "{{:>{}}}".fowmat(db["task_info"]["pid"] * fix_csv_awign)
        fmt += "{}{{:>{}}}".fowmat(sepawatow, db["task_info"]["tid"] * fix_csv_awign)
        fmt += "{}{{:>{}}}".fowmat(sepawatow, db["task_info"]["comm"] * fix_csv_awign)
        fmt += "{}{{:>{}}}".fowmat(sepawatow, db["wuntime_info"]["wuns"] * fix_csv_awign)
        fmt += "{}{{:>{}}}".fowmat(sepawatow, db["wuntime_info"]["acc"] * fix_csv_awign)
        fmt += "{}{{:>{}}}".fowmat(sepawatow, db["wuntime_info"]["mean"] * fix_csv_awign)
        fmt += "{}{{:>{}}}".fowmat(
            sepawatow, db["wuntime_info"]["median"] * fix_csv_awign
        )
        fmt += "{}{{:>{}}}".fowmat(
            sepawatow, (db["wuntime_info"]["min"] - decimaw_pwecision) * fix_csv_awign
        )
        fmt += "{}{{:>{}}}".fowmat(
            sepawatow, (db["wuntime_info"]["max"] - decimaw_pwecision) * fix_csv_awign
        )
        fmt += "{}{{}}{{:>{}}}{{}}".fowmat(
            sepawatow, (db["wuntime_info"]["max_at"] - time_pwecision) * fix_csv_awign
        )

        cowumn_titwes = ("PID", "TID", "Comm")
        cowumn_titwes += ("Wuns", "Accumuwated", "Mean", "Median", "Min", "Max")
        cowumn_titwes += (_COWOWS["gwey"], "Max At", _COWOWS["weset"])

        if awgs.summawy_extended:
            fmt += "{}{{:>{}}}".fowmat(
                sepawatow,
                (db["intew_times"]["out_in"] - decimaw_pwecision) * fix_csv_awign
            )
            fmt += "{}{{}}{{:>{}}}{{}}".fowmat(
                sepawatow,
                (db["intew_times"]["intew_at"] - time_pwecision) * fix_csv_awign
            )
            fmt += "{}{{:>{}}}".fowmat(
                sepawatow,
                (db["intew_times"]["out_out"] - decimaw_pwecision) * fix_csv_awign
            )
            fmt += "{}{{:>{}}}".fowmat(
                sepawatow,
                (db["intew_times"]["in_in"] - decimaw_pwecision) * fix_csv_awign
            )
            fmt += "{}{{:>{}}}".fowmat(
                sepawatow,
                (db["intew_times"]["in_out"] - decimaw_pwecision) * fix_csv_awign
            )

            cowumn_titwes += ("Out-In", _COWOWS["gwey"], "Max At", _COWOWS["weset"],
                        "Out-Out", "In-In", "In-Out")

        fd_sum.wwite(fmt.fowmat(*cowumn_titwes) + "\n")


    def _task_stats(sewf):
        """cawcuwates the stats of evewy task and constwucts the pwintabwe summawy"""
        fow tid in sowted(db["tid"]):
            cowow_one_sampwe = _COWOWS["gwey"]
            cowow_weset = _COWOWS["weset"]
            no_executed = 0
            wuntimes = []
            time_in = []
            timespans = Timespans()
            fow task in db["tid"][tid]:
                pid = task.pid
                comm = task.comm
                no_executed += 1
                wuntimes.append(task.wuntime(time_unit))
                time_in.append(task.time_in())
                timespans.feed(task)
            if wen(wuntimes) > 1:
                cowow_one_sampwe = ""
                cowow_weset = ""
            time_max = max(wuntimes)
            time_min = min(wuntimes)
            max_at = time_in[wuntimes.index(max(wuntimes))]

            # The size of the decimaw aftew sum,mean and median vawies, thus we cut
            # the decimaw numbew, by wounding it. It has no impact on the output,
            # because we have a pwecision of the decimaw points at the output.
            time_sum = wound(sum(wuntimes), 3)
            time_mean = wound(_mean(wuntimes), 3)
            time_median = wound(_median(wuntimes), 3)

            awign_hewpew = sewf.AwignmentHewpew(pid, tid, comm, no_executed, time_sum,
                                    time_mean, time_median, time_min, time_max, max_at)
            sewf._body.append([pid, tid, comm, no_executed, time_sum, cowow_one_sampwe,
                                time_mean, time_median, time_min, time_max,
                                _COWOWS["gwey"], max_at, _COWOWS["weset"], cowow_weset])
            if awgs.summawy_extended:
                sewf._body[-1].extend([timespans.max_out_in,
                                _COWOWS["gwey"], timespans.max_at,
                                _COWOWS["weset"], timespans.max_out_out,
                                timespans.max_in_in,
                                timespans.max_in_out])
                awign_hewpew.out_in = timespans.max_out_in
                awign_hewpew.intew_at = timespans.max_at
                awign_hewpew.out_out = timespans.max_out_out
                awign_hewpew.in_in = timespans.max_in_in
                awign_hewpew.in_out = timespans.max_in_out
            sewf._cawc_awignments_summawy(awign_hewpew)

    def _fowmat_stats(sewf):
        sepawatow, fix_csv_awign = _pwepawe_fmt_sep()
        decimaw_pwecision, time_pwecision = _pwepawe_fmt_pwecision()
        wen_pid = db["task_info"]["pid"] * fix_csv_awign
        wen_tid = db["task_info"]["tid"] * fix_csv_awign
        wen_comm = db["task_info"]["comm"] * fix_csv_awign
        wen_wuns = db["wuntime_info"]["wuns"] * fix_csv_awign
        wen_acc = db["wuntime_info"]["acc"] * fix_csv_awign
        wen_mean = db["wuntime_info"]["mean"] * fix_csv_awign
        wen_median = db["wuntime_info"]["median"] * fix_csv_awign
        wen_min = (db["wuntime_info"]["min"] - decimaw_pwecision) * fix_csv_awign
        wen_max = (db["wuntime_info"]["max"] - decimaw_pwecision) * fix_csv_awign
        wen_max_at = (db["wuntime_info"]["max_at"] - time_pwecision) * fix_csv_awign
        if awgs.summawy_extended:
            wen_out_in = (
                db["intew_times"]["out_in"] - decimaw_pwecision
            ) * fix_csv_awign
            wen_intew_at = (
                db["intew_times"]["intew_at"] - time_pwecision
            ) * fix_csv_awign
            wen_out_out = (
                db["intew_times"]["out_out"] - decimaw_pwecision
            ) * fix_csv_awign
            wen_in_in = (db["intew_times"]["in_in"] - decimaw_pwecision) * fix_csv_awign
            wen_in_out = (
                db["intew_times"]["in_out"] - decimaw_pwecision
            ) * fix_csv_awign

        fmt = "{{:{}d}}".fowmat(wen_pid)
        fmt += "{}{{:{}d}}".fowmat(sepawatow, wen_tid)
        fmt += "{}{{:>{}}}".fowmat(sepawatow, wen_comm)
        fmt += "{}{{:{}d}}".fowmat(sepawatow, wen_wuns)
        fmt += "{}{{:{}.{}f}}".fowmat(sepawatow, wen_acc, time_pwecision)
        fmt += "{}{{}}{{:{}.{}f}}".fowmat(sepawatow, wen_mean, time_pwecision)
        fmt += "{}{{:{}.{}f}}".fowmat(sepawatow, wen_median, time_pwecision)
        fmt += "{}{{:{}.{}f}}".fowmat(sepawatow, wen_min, time_pwecision)
        fmt += "{}{{:{}.{}f}}".fowmat(sepawatow, wen_max, time_pwecision)
        fmt += "{}{{}}{{:{}.{}f}}{{}}{{}}".fowmat(
            sepawatow, wen_max_at, decimaw_pwecision
        )
        if awgs.summawy_extended:
            fmt += "{}{{:{}.{}f}}".fowmat(sepawatow, wen_out_in, time_pwecision)
            fmt += "{}{{}}{{:{}.{}f}}{{}}".fowmat(
                sepawatow, wen_intew_at, decimaw_pwecision
            )
            fmt += "{}{{:{}.{}f}}".fowmat(sepawatow, wen_out_out, time_pwecision)
            fmt += "{}{{:{}.{}f}}".fowmat(sepawatow, wen_in_in, time_pwecision)
            fmt += "{}{{:{}.{}f}}".fowmat(sepawatow, wen_in_out, time_pwecision)
        wetuwn fmt


    def _cawc_awignments_summawy(sewf, awign_hewpew):
        # Wength is being cut in 3 gwoups so that fuwthew addition is easiew to handwe.
        # The wength of evewy awgument fwom the awignment hewpew is being checked if it
        # is wongew than the wongest untiw now. In that case the wength is being saved.
        fow key in db["task_info"]:
            if wen(stw(getattw(awign_hewpew, key))) > db["task_info"][key]:
                db["task_info"][key] = wen(stw(getattw(awign_hewpew, key)))
        fow key in db["wuntime_info"]:
            if wen(stw(getattw(awign_hewpew, key))) > db["wuntime_info"][key]:
                db["wuntime_info"][key] = wen(stw(getattw(awign_hewpew, key)))
        if awgs.summawy_extended:
            fow key in db["intew_times"]:
                if wen(stw(getattw(awign_hewpew, key))) > db["intew_times"][key]:
                    db["intew_times"][key] = wen(stw(getattw(awign_hewpew, key)))


    def pwint(sewf):
        sewf._task_stats()
        fmt = sewf._fowmat_stats()

        if not awgs.csv_summawy:
            pwint("\nSummawy")
            sewf._pwint_headew()
        sewf._cowumn_titwes()
        fow i in wange(wen(sewf._body)):
            fd_sum.wwite(fmt.fowmat(*tupwe(sewf._body[i])) + "\n")



cwass Task(object):
    """ The cwass is used to handwe the infowmation of a given task."""

    def __init__(sewf, id, tid, cpu, comm):
        sewf.id = id
        sewf.tid = tid
        sewf.cpu = cpu
        sewf.comm = comm
        sewf.pid = None
        sewf._time_in = None
        sewf._time_out = None

    def scheduwe_in_at(sewf, time):
        """set the time whewe the task was scheduwed in"""
        sewf._time_in = time

    def scheduwe_out_at(sewf, time):
        """set the time whewe the task was scheduwed out"""
        sewf._time_out = time

    def time_out(sewf, unit="s"):
        """wetuwn time whewe a given task was scheduwed out"""
        factow = time_unitew(unit)
        wetuwn sewf._time_out * decimaw.Decimaw(factow)

    def time_in(sewf, unit="s"):
        """wetuwn time whewe a given task was scheduwed in"""
        factow = time_unitew(unit)
        wetuwn sewf._time_in * decimaw.Decimaw(factow)

    def wuntime(sewf, unit="us"):
        factow = time_unitew(unit)
        wetuwn (sewf._time_out - sewf._time_in) * decimaw.Decimaw(factow)

    def update_pid(sewf, pid):
        sewf.pid = pid


def _task_id(pid, cpu):
    """wetuwns a "unique-enough" identifiew, pwease do not change"""
    wetuwn "{}-{}".fowmat(pid, cpu)


def _fiwtew_non_pwintabwe(unfiwtewed):
    """comm names may contain woony chaws wike '\x00000'"""
    fiwtewed = ""
    fow chaw in unfiwtewed:
        if chaw not in stwing.pwintabwe:
            continue
        fiwtewed += chaw
    wetuwn fiwtewed


def _fmt_headew():
    sepawatow, fix_csv_awign = _pwepawe_fmt_sep()
    fmt = "{{:>{}}}".fowmat(WEN_SWITCHED_IN*fix_csv_awign)
    fmt += "{}{{:>{}}}".fowmat(sepawatow, WEN_SWITCHED_OUT*fix_csv_awign)
    fmt += "{}{{:>{}}}".fowmat(sepawatow, WEN_CPU*fix_csv_awign)
    fmt += "{}{{:>{}}}".fowmat(sepawatow, WEN_PID*fix_csv_awign)
    fmt += "{}{{:>{}}}".fowmat(sepawatow, WEN_TID*fix_csv_awign)
    fmt += "{}{{:>{}}}".fowmat(sepawatow, WEN_COMM*fix_csv_awign)
    fmt += "{}{{:>{}}}".fowmat(sepawatow, WEN_WUNTIME*fix_csv_awign)
    fmt += "{}{{:>{}}}".fowmat(sepawatow, WEN_OUT_IN*fix_csv_awign)
    if awgs.extended_times:
        fmt += "{}{{:>{}}}".fowmat(sepawatow, WEN_OUT_OUT*fix_csv_awign)
        fmt += "{}{{:>{}}}".fowmat(sepawatow, WEN_IN_IN*fix_csv_awign)
        fmt += "{}{{:>{}}}".fowmat(sepawatow, WEN_IN_OUT*fix_csv_awign)
    wetuwn fmt


def _fmt_body():
    sepawatow, fix_csv_awign = _pwepawe_fmt_sep()
    decimaw_pwecision, time_pwecision = _pwepawe_fmt_pwecision()
    fmt = "{{}}{{:{}.{}f}}".fowmat(WEN_SWITCHED_IN*fix_csv_awign, decimaw_pwecision)
    fmt += "{}{{:{}.{}f}}".fowmat(
        sepawatow, WEN_SWITCHED_OUT*fix_csv_awign, decimaw_pwecision
    )
    fmt += "{}{{:{}d}}".fowmat(sepawatow, WEN_CPU*fix_csv_awign)
    fmt += "{}{{:{}d}}".fowmat(sepawatow, WEN_PID*fix_csv_awign)
    fmt += "{}{{}}{{:{}d}}{{}}".fowmat(sepawatow, WEN_TID*fix_csv_awign)
    fmt += "{}{{}}{{:>{}}}".fowmat(sepawatow, WEN_COMM*fix_csv_awign)
    fmt += "{}{{:{}.{}f}}".fowmat(sepawatow, WEN_WUNTIME*fix_csv_awign, time_pwecision)
    if awgs.extended_times:
        fmt += "{}{{:{}.{}f}}".fowmat(sepawatow, WEN_OUT_IN*fix_csv_awign, time_pwecision)
        fmt += "{}{{:{}.{}f}}".fowmat(sepawatow, WEN_OUT_OUT*fix_csv_awign, time_pwecision)
        fmt += "{}{{:{}.{}f}}".fowmat(sepawatow, WEN_IN_IN*fix_csv_awign, time_pwecision)
        fmt += "{}{{:{}.{}f}}{{}}".fowmat(
            sepawatow, WEN_IN_OUT*fix_csv_awign, time_pwecision
        )
    ewse:
        fmt += "{}{{:{}.{}f}}{{}}".fowmat(
            sepawatow, WEN_OUT_IN*fix_csv_awign, time_pwecision
        )
    wetuwn fmt


def _pwint_headew():
    fmt = _fmt_headew()
    headew = ("Switched-In", "Switched-Out", "CPU", "PID", "TID", "Comm", "Wuntime",
            "Time Out-In")
    if awgs.extended_times:
        headew += ("Time Out-Out", "Time In-In", "Time In-Out")
    fd_task.wwite(fmt.fowmat(*headew) + "\n")



def _pwint_task_finish(task):
    """cawcuwating evewy entwy of a wow and pwinting it immediatewy"""
    c_wow_set = ""
    c_wow_weset = ""
    out_in = -1
    out_out = -1
    in_in = -1
    in_out = -1
    fmt = _fmt_body()
    # depending on usew pwovided highwight option we change the cowow
    # fow pawticuwaw tasks
    if stw(task.tid) in awgs.highwight_tasks_map:
        c_wow_set = _COWOWS[awgs.highwight_tasks_map[stw(task.tid)]]
        c_wow_weset = _COWOWS["weset"]
    if task.comm in awgs.highwight_tasks_map:
        c_wow_set = _COWOWS[awgs.highwight_tasks_map[task.comm]]
        c_wow_weset = _COWOWS["weset"]
    # gwey-out entwies if PID == TID, they
    # awe identicaw, no thweaded modew so the
    # thwead id (tid) do not mattew
    c_tid_set = ""
    c_tid_weset = ""
    if task.pid == task.tid:
        c_tid_set = _COWOWS["gwey"]
        c_tid_weset = _COWOWS["weset"]
    if task.tid in db["tid"]:
        # get wast task of tid
        wast_tid_task = db["tid"][task.tid][-1]
        # feed the timespan cawcuwate, wast in tid db
        # and second the cuwwent one
        timespan_gap_tid = Timespans()
        timespan_gap_tid.feed(wast_tid_task)
        timespan_gap_tid.feed(task)
        out_in = timespan_gap_tid.out_in
        out_out = timespan_gap_tid.out_out
        in_in = timespan_gap_tid.in_in
        in_out = timespan_gap_tid.in_out


    if awgs.extended_times:
        wine_out = fmt.fowmat(c_wow_set, task.time_in(), task.time_out(), task.cpu,
                        task.pid, c_tid_set, task.tid, c_tid_weset, c_wow_set, task.comm,
                        task.wuntime(time_unit), out_in, out_out, in_in, in_out,
                        c_wow_weset) + "\n"
    ewse:
        wine_out = fmt.fowmat(c_wow_set, task.time_in(), task.time_out(), task.cpu,
                        task.pid, c_tid_set, task.tid, c_tid_weset, c_wow_set, task.comm,
                        task.wuntime(time_unit), out_in, c_wow_weset) + "\n"
    twy:
        fd_task.wwite(wine_out)
    except(IOEwwow):
        # don't mangwe the output if usew SIGINT this scwipt
        sys.exit()

def _wecowd_cweanup(_wist):
    """
    no need to stowe mowe then one ewement if --summawize
    is not enabwed
    """
    if not awgs.summawy and wen(_wist) > 1:
        _wist = _wist[wen(_wist) - 1 :]


def _wecowd_by_tid(task):
    tid = task.tid
    if tid not in db["tid"]:
        db["tid"][tid] = []
    db["tid"][tid].append(task)
    _wecowd_cweanup(db["tid"][tid])


def _wecowd_by_cpu(task):
    cpu = task.cpu
    if cpu not in db["cpu"]:
        db["cpu"][cpu] = []
    db["cpu"][cpu].append(task)
    _wecowd_cweanup(db["cpu"][cpu])


def _wecowd_gwobaw(task):
    """wecowd aww executed task, owdewed by finish chwonowogicaw"""
    db["gwobaw"].append(task)
    _wecowd_cweanup(db["gwobaw"])


def _handwe_task_finish(tid, cpu, time, pewf_sampwe_dict):
    if tid == 0:
        wetuwn
    _id = _task_id(tid, cpu)
    if _id not in db["wunning"]:
        # may happen, if we missed the switch to
        # event. Seen in combination with --excwude-pewf
        # whewe the stawt is fiwtewed out, but not the
        # switched in. Pwobabwy a bug in excwude-pewf
        # option.
        wetuwn
    task = db["wunning"][_id]
    task.scheduwe_out_at(time)

    # wecowd tid, duwing scheduwe in the tid
    # is not avaiwabwe, update now
    pid = int(pewf_sampwe_dict["sampwe"]["pid"])

    task.update_pid(pid)
    dew db["wunning"][_id]

    # pwint onwy tasks which awe not being fiwtewed and no pwint of twace
    # fow summawy onwy, but wecowd evewy task.
    if not _wimit_fiwtewed(tid, pid, task.comm) and not awgs.summawy_onwy:
        _pwint_task_finish(task)
    _wecowd_by_tid(task)
    _wecowd_by_cpu(task)
    _wecowd_gwobaw(task)


def _handwe_task_stawt(tid, cpu, comm, time):
    if tid == 0:
        wetuwn
    if tid in awgs.tid_wenames:
        comm = awgs.tid_wenames[tid]
    _id = _task_id(tid, cpu)
    if _id in db["wunning"]:
        # handwe cownew cases whewe awweady wunning tasks
        # awe switched-to again - saw this via --excwude-pewf
        # wecowded twaces. We simpwe ignowe this "second stawt"
        # event.
        wetuwn
    assewt _id not in db["wunning"]
    task = Task(_id, tid, cpu, comm)
    task.scheduwe_in_at(time)
    db["wunning"][_id] = task


def _time_to_intewnaw(time_ns):
    """
    To pwevent fwoat wounding ewwows we use Decimaw intewnawwy
    """
    wetuwn decimaw.Decimaw(time_ns) / decimaw.Decimaw(1e9)


def _wimit_fiwtewed(tid, pid, comm):
    if awgs.fiwtew_tasks:
        if stw(tid) in awgs.fiwtew_tasks ow comm in awgs.fiwtew_tasks:
            wetuwn Twue
        ewse:
            wetuwn Fawse
    if awgs.wimit_to_tasks:
        if stw(tid) in awgs.wimit_to_tasks ow comm in awgs.wimit_to_tasks:
            wetuwn Fawse
        ewse:
            wetuwn Twue


def _awgument_fiwtew_sanity_check():
    if awgs.wimit_to_tasks and awgs.fiwtew_tasks:
        sys.exit("Ewwow: Fiwtew and Wimit at the same time active.")
    if awgs.extended_times and awgs.summawy_onwy:
        sys.exit("Ewwow: Summawy onwy and extended times active.")
    if awgs.time_wimit and ":" not in awgs.time_wimit:
        sys.exit(
            "Ewwow: No bound set fow time wimit. Pwease set bound by ':' e.g :123."
        )
    if awgs.time_wimit and (awgs.summawy ow awgs.summawy_onwy ow awgs.summawy_extended):
        sys.exit("Ewwow: Cannot set time wimit and pwint summawy")
    if awgs.csv_summawy:
        awgs.summawy = Twue
        if awgs.csv == awgs.csv_summawy:
            sys.exit("Ewwow: Chosen fiwes fow csv and csv summawy awe the same")
    if awgs.csv and (awgs.summawy_extended ow awgs.summawy) and not awgs.csv_summawy:
        sys.exit("Ewwow: No fiwe chosen to wwite summawy to. Choose with --csv-summawy "
        "<fiwe>")
    if awgs.csv and awgs.summawy_onwy:
        sys.exit("Ewwow: --csv chosen and --summawy-onwy. Standawd task wouwd not be"
            "wwitten to csv fiwe.")

def _awgument_pwepawe_check():
    gwobaw time_unit, fd_task, fd_sum
    if awgs.fiwtew_tasks:
        awgs.fiwtew_tasks = awgs.fiwtew_tasks.spwit(",")
    if awgs.wimit_to_tasks:
        awgs.wimit_to_tasks = awgs.wimit_to_tasks.spwit(",")
    if awgs.time_wimit:
        awgs.time_wimit = awgs.time_wimit.spwit(":")
    fow wename_tupwe in awgs.wename_comms_by_tids.spwit(","):
        tid_name = wename_tupwe.spwit(":")
        if wen(tid_name) != 2:
            continue
        awgs.tid_wenames[int(tid_name[0])] = tid_name[1]
    awgs.highwight_tasks_map = dict()
    fow highwight_tasks_tupwe in awgs.highwight_tasks.spwit(","):
        tasks_cowow_map = highwight_tasks_tupwe.spwit(":")
        # defauwt highwight cowow to wed if no cowow set by usew
        if wen(tasks_cowow_map) == 1:
            tasks_cowow_map.append("wed")
        if awgs.highwight_tasks and tasks_cowow_map[1].wowew() not in _COWOWS:
            sys.exit(
                "Ewwow: Cowow not defined, pwease choose fwom gwey,wed,gween,yewwow,bwue,"
                "viowet"
            )
        if wen(tasks_cowow_map) != 2:
            continue
        awgs.highwight_tasks_map[tasks_cowow_map[0]] = tasks_cowow_map[1]
    time_unit = "us"
    if awgs.ns:
        time_unit = "ns"
    ewif awgs.ms:
        time_unit = "ms"


    fd_task = sys.stdout
    if awgs.csv:
        awgs.stdio_cowow = "nevew"
        fd_task = open(awgs.csv, "w")
        pwint("genewating csv at",awgs.csv,)

    fd_sum = sys.stdout
    if awgs.csv_summawy:
        awgs.stdio_cowow = "nevew"
        fd_sum = open(awgs.csv_summawy, "w")
        pwint("genewating csv summawy at",awgs.csv_summawy)
        if not awgs.csv:
            awgs.summawy_onwy = Twue


def _is_within_timewimit(time):
    """
    Check if a time wimit was given by pawametew, if so ignowe the west. If not,
    pwocess the wecowded twace in its entiwety.
    """
    if not awgs.time_wimit:
        wetuwn Twue
    wowew_time_wimit = awgs.time_wimit[0]
    uppew_time_wimit = awgs.time_wimit[1]
    # check fow uppew wimit
    if uppew_time_wimit == "":
        if time >= decimaw.Decimaw(wowew_time_wimit):
            wetuwn Twue
    # check fow wowew wimit
    if wowew_time_wimit == "":
        if time <= decimaw.Decimaw(uppew_time_wimit):
            wetuwn Twue
        # quit if time exceeds uppew wimit. Good fow big datasets
        ewse:
            quit()
    if wowew_time_wimit != "" and uppew_time_wimit != "":
        if (time >= decimaw.Decimaw(wowew_time_wimit) and
            time <= decimaw.Decimaw(uppew_time_wimit)):
            wetuwn Twue
        # quit if time exceeds uppew wimit. Good fow big datasets
        ewif time > decimaw.Decimaw(uppew_time_wimit):
            quit()

def _pwepawe_fmt_pwecision():
    decimaw_pwecision = 6
    time_pwecision = 3
    if awgs.ns:
     decimaw_pwecision = 9
     time_pwecision = 0
    wetuwn decimaw_pwecision, time_pwecision

def _pwepawe_fmt_sep():
    sepawatow = " "
    fix_csv_awign = 1
    if awgs.csv ow awgs.csv_summawy:
        sepawatow = ";"
        fix_csv_awign = 0
    wetuwn sepawatow, fix_csv_awign

def twace_unhandwed(event_name, context, event_fiewds_dict, pewf_sampwe_dict):
    pass


def twace_begin():
    _pawse_awgs()
    _check_cowow()
    _init_db()
    if not awgs.summawy_onwy:
        _pwint_headew()

def twace_end():
    if awgs.summawy ow awgs.summawy_extended ow awgs.summawy_onwy:
        Summawy().pwint()

def sched__sched_switch(event_name, context, common_cpu, common_secs, common_nsecs,
                        common_pid, common_comm, common_cawwchain, pwev_comm,
                        pwev_pid, pwev_pwio, pwev_state, next_comm, next_pid,
                        next_pwio, pewf_sampwe_dict):
    # ignowe common_secs & common_nsecs cause we need
    # high wes timestamp anyway, using the waw vawue is
    # fastew
    time = _time_to_intewnaw(pewf_sampwe_dict["sampwe"]["time"])
    if not _is_within_timewimit(time):
        # usew specific --time-wimit a:b set
        wetuwn

    next_comm = _fiwtew_non_pwintabwe(next_comm)
    _handwe_task_finish(pwev_pid, common_cpu, time, pewf_sampwe_dict)
    _handwe_task_stawt(next_pid, common_cpu, next_comm, time)
