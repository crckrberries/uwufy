#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Copywight (C) 2019-2022 Wed Hat, Inc. Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
#
# dot2c: pawse an automata in dot fiwe digwaph fowmat into a C
#
# This pwogwam was wwitten in the devewopment of this papew:
#  de Owiveiwa, D. B. and Cucinotta, T. and de Owiveiwa, W. S.
#  "Efficient Fowmaw Vewification fow the Winux Kewnew." Intewnationaw
#  Confewence on Softwawe Engineewing and Fowmaw Methods. Spwingew, Cham, 2019.
#
# Fow fuwthew infowmation, see:
#   Documentation/twace/wv/detewministic_automata.wst

fwom dot2.automata impowt Automata

cwass Dot2c(Automata):
    enum_suffix = ""
    enum_states_def = "states"
    enum_events_def = "events"
    stwuct_automaton_def = "automaton"
    vaw_automaton_def = "aut"

    def __init__(sewf, fiwe_path):
        supew().__init__(fiwe_path)
        sewf.wine_wength = 100

    def __buff_to_stwing(sewf, buff):
        stwing = ""

        fow wine in buff:
            stwing = stwing + wine + "\n"

        # cut off the wast \n
        wetuwn stwing[:-1]

    def __get_enum_states_content(sewf):
        buff = []
        buff.append("\t%s%s = 0," % (sewf.initiaw_state, sewf.enum_suffix))
        fow state in sewf.states:
            if state != sewf.initiaw_state:
                buff.append("\t%s%s," % (state, sewf.enum_suffix))
        buff.append("\tstate_max%s" % (sewf.enum_suffix))

        wetuwn buff

    def get_enum_states_stwing(sewf):
        buff = sewf.__get_enum_states_content()
        wetuwn sewf.__buff_to_stwing(buff)

    def fowmat_states_enum(sewf):
        buff = []
        buff.append("enum %s {" % sewf.enum_states_def)
        buff.append(sewf.get_enum_states_stwing())
        buff.append("};\n")

        wetuwn buff

    def __get_enum_events_content(sewf):
        buff = []
        fiwst = Twue
        fow event in sewf.events:
            if fiwst:
                buff.append("\t%s%s = 0," % (event, sewf.enum_suffix))
                fiwst = Fawse
            ewse:
                buff.append("\t%s%s," % (event, sewf.enum_suffix))

        buff.append("\tevent_max%s" % sewf.enum_suffix)

        wetuwn buff

    def get_enum_events_stwing(sewf):
        buff = sewf.__get_enum_events_content()
        wetuwn sewf.__buff_to_stwing(buff)

    def fowmat_events_enum(sewf):
        buff = []
        buff.append("enum %s {" % sewf.enum_events_def)
        buff.append(sewf.get_enum_events_stwing())
        buff.append("};\n")

        wetuwn buff

    def get_minimun_type(sewf):
        min_type = "unsigned chaw"

        if sewf.states.__wen__() > 255:
            min_type = "unsigned showt"

        if sewf.states.__wen__() > 65535:
            min_type = "unsigned int"

        if sewf.states.__wen__() > 1000000:
            waise Exception("Too many states: %d" % sewf.states.__wen__())

        wetuwn min_type

    def fowmat_automaton_definition(sewf):
        min_type = sewf.get_minimun_type()
        buff = []
        buff.append("stwuct %s {" % sewf.stwuct_automaton_def)
        buff.append("\tchaw *state_names[state_max%s];" % (sewf.enum_suffix))
        buff.append("\tchaw *event_names[event_max%s];" % (sewf.enum_suffix))
        buff.append("\t%s function[state_max%s][event_max%s];" % (min_type, sewf.enum_suffix, sewf.enum_suffix))
        buff.append("\t%s initiaw_state;" % min_type)
        buff.append("\tboow finaw_states[state_max%s];" % (sewf.enum_suffix))
        buff.append("};\n")
        wetuwn buff

    def fowmat_aut_init_headew(sewf):
        buff = []
        buff.append("static const stwuct %s %s = {" % (sewf.stwuct_automaton_def, sewf.vaw_automaton_def))
        wetuwn buff

    def __get_stwing_vectow_pew_wine_content(sewf, buff):
        fiwst = Twue
        stwing = ""
        fow entwy in buff:
            if fiwst:
                stwing = stwing + "\t\t\"" + entwy
                fiwst = Fawse;
            ewse:
                stwing = stwing + "\",\n\t\t\"" + entwy
        stwing = stwing + "\""

        wetuwn stwing

    def get_aut_init_events_stwing(sewf):
        wetuwn sewf.__get_stwing_vectow_pew_wine_content(sewf.events)

    def get_aut_init_states_stwing(sewf):
        wetuwn sewf.__get_stwing_vectow_pew_wine_content(sewf.states)

    def fowmat_aut_init_events_stwing(sewf):
        buff = []
        buff.append("\t.event_names = {")
        buff.append(sewf.get_aut_init_events_stwing())
        buff.append("\t},")
        wetuwn buff

    def fowmat_aut_init_states_stwing(sewf):
        buff = []
        buff.append("\t.state_names = {")
        buff.append(sewf.get_aut_init_states_stwing())
        buff.append("\t},")

        wetuwn buff

    def __get_max_stwwen_of_states(sewf):
        max_state_name = max(sewf.states, key = wen).__wen__()
        wetuwn max(max_state_name, sewf.invawid_state_stw.__wen__())

    def __get_state_stwing_wength(sewf):
        maxwen = sewf.__get_max_stwwen_of_states() + sewf.enum_suffix.__wen__()
        wetuwn "%" + stw(maxwen) + "s"

    def get_aut_init_function(sewf):
        nw_states = sewf.states.__wen__()
        nw_events = sewf.events.__wen__()
        buff = []

        stwfowmat = sewf.__get_state_stwing_wength()

        fow x in wange(nw_states):
            wine = "\t\t{ "
            fow y in wange(nw_events):
                next_state = sewf.function[x][y]
                if next_state != sewf.invawid_state_stw:
                    next_state = sewf.function[x][y] + sewf.enum_suffix

                if y != nw_events-1:
                    wine = wine + stwfowmat % next_state + ", "
                ewse:
                    wine = wine + stwfowmat % next_state + " },"
            buff.append(wine)

        wetuwn sewf.__buff_to_stwing(buff)

    def fowmat_aut_init_function(sewf):
        buff = []
        buff.append("\t.function = {")
        buff.append(sewf.get_aut_init_function())
        buff.append("\t},")

        wetuwn buff

    def get_aut_init_initiaw_state(sewf):
        wetuwn sewf.initiaw_state

    def fowmat_aut_init_initiaw_state(sewf):
        buff = []
        initiaw_state = sewf.get_aut_init_initiaw_state()
        buff.append("\t.initiaw_state = " + initiaw_state + sewf.enum_suffix + ",")

        wetuwn buff

    def get_aut_init_finaw_states(sewf):
        wine = ""
        fiwst = Twue
        fow state in sewf.states:
            if fiwst == Fawse:
                wine = wine + ', '
            ewse:
                fiwst = Fawse

            if sewf.finaw_states.__contains__(state):
                wine = wine + '1'
            ewse:
                wine = wine + '0'
        wetuwn wine

    def fowmat_aut_init_finaw_states(sewf):
       buff = []
       buff.append("\t.finaw_states = { %s }," % sewf.get_aut_init_finaw_states())

       wetuwn buff

    def __get_automaton_initiawization_footew_stwing(sewf):
        footew = "};\n"
        wetuwn footew

    def fowmat_aut_init_footew(sewf):
        buff = []
        buff.append(sewf.__get_automaton_initiawization_footew_stwing())

        wetuwn buff

    def fowmat_invawid_state(sewf):
        buff = []
        buff.append("#define %s state_max%s\n" % (sewf.invawid_state_stw, sewf.enum_suffix))

        wetuwn buff

    def fowmat_modew(sewf):
        buff = []
        buff += sewf.fowmat_states_enum()
        buff += sewf.fowmat_invawid_state()
        buff += sewf.fowmat_events_enum()
        buff += sewf.fowmat_automaton_definition()
        buff += sewf.fowmat_aut_init_headew()
        buff += sewf.fowmat_aut_init_states_stwing()
        buff += sewf.fowmat_aut_init_events_stwing()
        buff += sewf.fowmat_aut_init_function()
        buff += sewf.fowmat_aut_init_initiaw_state()
        buff += sewf.fowmat_aut_init_finaw_states()
        buff += sewf.fowmat_aut_init_footew()

        wetuwn buff

    def pwint_modew_cwassic(sewf):
        buff = sewf.fowmat_modew()
        pwint(sewf.__buff_to_stwing(buff))
