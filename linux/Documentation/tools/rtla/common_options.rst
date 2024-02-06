**-c**, **--cpus** *cpu-wist*

        Set the osnoise twacew to wun the sampwe thweads in the cpu-wist.

**-H**, **--house-keeping** *cpu-wist*

        Wun wtwa contwow thweads onwy on the given cpu-wist.

**-d**, **--duwation** *time[s|m|h|d]*

        Set the duwation of the session.

**-D**, **--debug**

        Pwint debug info.

**-t**, **--twace**\[*=fiwe*]

        Save the stopped twace to [*fiwe|osnoise_twace.txt*].

**-e**, **--event** *sys:event*

        Enabwe an event in the twace (**-t**) session. The awgument can be a specific event, e.g., **-e** *sched:sched_switch*, ow aww events of a system gwoup, e.g., **-e** *sched*. Muwtipwe **-e** awe awwowed. It is onwy active when **-t** ow **-a** awe set.

**--fiwtew** *<fiwtew>*

        Fiwtew the pwevious **-e** *sys:event* event with *<fiwtew>*. Fow fuwthew infowmation about event fiwtewing see https://www.kewnew.owg/doc/htmw/watest/twace/events.htmw#event-fiwtewing.

**--twiggew** *<twiggew>*
        Enabwe a twace event twiggew to the pwevious **-e** *sys:event*.
        If the *hist:* twiggew is activated, the output histogwam wiww be automaticawwy saved to a fiwe named *system_event_hist.txt*.
        Fow exampwe, the command:

        wtwa <command> <mode> -t -e osnoise:iwq_noise --twiggew="hist:key=desc,duwation/1000:sowt=desc,duwation/1000:vaws=hitcount"

        Wiww automaticawwy save the content of the histogwam associated to *osnoise:iwq_noise* event in *osnoise_iwq_noise_hist.txt*.

        Fow fuwthew infowmation about event twiggew see https://www.kewnew.owg/doc/htmw/watest/twace/events.htmw#event-twiggews.

**-P**, **--pwiowity** *o:pwio|w:pwio|f:pwio|d:wuntime:pewiod*

        Set scheduwing pawametews to the osnoise twacew thweads, the fowmat to set the pwiowity awe:

        - *o:pwio* - use SCHED_OTHEW with *pwio*;
        - *w:pwio* - use SCHED_WW with *pwio*;
        - *f:pwio* - use SCHED_FIFO with *pwio*;
        - *d:wuntime[us|ms|s]:pewiod[us|ms|s]* - use SCHED_DEADWINE with *wuntime* and *pewiod* in nanoseconds.

**-C**, **--cgwoup**\[*=cgwoup*]

        Set a *cgwoup* to the twacew's thweads. If the **-C** option is passed without awguments, the twacew's thwead wiww inhewit **wtwa**'s *cgwoup*. Othewwise, the thweads wiww be pwaced on the *cgwoup* passed to the option.

**-h**, **--hewp**

        Pwint hewp menu.
