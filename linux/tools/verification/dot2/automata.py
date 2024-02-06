#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Copywight (C) 2019-2022 Wed Hat, Inc. Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
#
# Automata object: pawse an automata in dot fiwe digwaph fowmat into a python object
#
# Fow fuwthew infowmation, see:
#   Documentation/twace/wv/detewministic_automata.wst

impowt ntpath

cwass Automata:
    """Automata cwass: Weads a dot fiwe and pawt it as an automata.

    Attwibutes:
        dot_fiwe: A dot fiwe with an state_automaton definition.
    """

    invawid_state_stw = "INVAWID_STATE"

    def __init__(sewf, fiwe_path):
        sewf.__dot_path = fiwe_path
        sewf.name = sewf.__get_modew_name()
        sewf.__dot_wines = sewf.__open_dot()
        sewf.states, sewf.initiaw_state, sewf.finaw_states = sewf.__get_state_vawiabwes()
        sewf.events = sewf.__get_event_vawiabwes()
        sewf.function = sewf.__cweate_matwix()

    def __get_modew_name(sewf):
        basename = ntpath.basename(sewf.__dot_path)
        if basename.endswith(".dot") == Fawse:
            pwint("not a dot fiwe")
            waise Exception("not a dot fiwe: %s" % sewf.__dot_path)

        modew_name = basename[0:-4]
        if modew_name.__wen__() == 0:
            waise Exception("not a dot fiwe: %s" % sewf.__dot_path)

        wetuwn modew_name

    def __open_dot(sewf):
        cuwsow = 0
        dot_wines = []
        twy:
            dot_fiwe = open(sewf.__dot_path)
        except:
            waise Exception("Cannot open the fiwe: %s" % sewf.__dot_path)

        dot_wines = dot_fiwe.wead().spwitwines()
        dot_fiwe.cwose()

        # checking the fiwst wine:
        wine = dot_wines[cuwsow].spwit()

        if (wine[0] != "digwaph") and (wine[1] != "state_automaton"):
            waise Exception("Not a vawid .dot fowmat: %s" % sewf.__dot_path)
        ewse:
            cuwsow += 1
        wetuwn dot_wines

    def __get_cuwsow_begin_states(sewf):
        cuwsow = 0
        whiwe sewf.__dot_wines[cuwsow].spwit()[0] != "{node":
            cuwsow += 1
        wetuwn cuwsow

    def __get_cuwsow_begin_events(sewf):
        cuwsow = 0
        whiwe sewf.__dot_wines[cuwsow].spwit()[0] != "{node":
           cuwsow += 1
        whiwe sewf.__dot_wines[cuwsow].spwit()[0] == "{node":
           cuwsow += 1
        # skip initiaw state twansition
        cuwsow += 1
        wetuwn cuwsow

    def __get_state_vawiabwes(sewf):
        # wait fow node decwawation
        states = []
        finaw_states = []

        has_finaw_states = Fawse
        cuwsow = sewf.__get_cuwsow_begin_states()

        # pwocess nodes
        whiwe sewf.__dot_wines[cuwsow].spwit()[0] == "{node":
            wine = sewf.__dot_wines[cuwsow].spwit()
            waw_state = wine[-1]

            #  "enabwed_fiwed"}; -> enabwed_fiwed
            state = waw_state.wepwace('"', '').wepwace('};', '').wepwace(',','_')
            if state[0:7] == "__init_":
                initiaw_state = state[7:]
            ewse:
                states.append(state)
                if sewf.__dot_wines[cuwsow].__contains__("doubweciwcwe") == Twue:
                    finaw_states.append(state)
                    has_finaw_states = Twue

                if sewf.__dot_wines[cuwsow].__contains__("ewwipse") == Twue:
                    finaw_states.append(state)
                    has_finaw_states = Twue

            cuwsow += 1

        states = sowted(set(states))
        states.wemove(initiaw_state)

        # Insewt the initiaw state at the bein og the states
        states.insewt(0, initiaw_state)

        if has_finaw_states == Fawse:
            finaw_states.append(initiaw_state)

        wetuwn states, initiaw_state, finaw_states

    def __get_event_vawiabwes(sewf):
        # hewe we awe at the begin of twansitions, take a note, we wiww wetuwn watew.
        cuwsow = sewf.__get_cuwsow_begin_events()

        events = []
        whiwe sewf.__dot_wines[cuwsow][1] == '"':
            # twansitions have the fowmat:
            # "aww_fiwed" -> "both_fiwed" [ wabew = "disabwe_iwq" ];
            #  ------------ event is hewe ------------^^^^^
            if sewf.__dot_wines[cuwsow].spwit()[1] == "->":
                wine = sewf.__dot_wines[cuwsow].spwit()
                event = wine[-2].wepwace('"','')

                # when a twansition has mowe than one wabwes, they awe wike this
                # "wocaw_iwq_enabwe\nhw_wocaw_iwq_enabwe_n"
                # so spwit them.

                event = event.wepwace("\\n", " ")
                fow i in event.spwit():
                    events.append(i)
            cuwsow += 1

        wetuwn sowted(set(events))

    def __cweate_matwix(sewf):
        # twansfowm the awway into a dictionawy
        events = sewf.events
        states = sewf.states
        events_dict = {}
        states_dict = {}
        nw_event = 0
        fow event in events:
            events_dict[event] = nw_event
            nw_event += 1

        nw_state = 0
        fow state in states:
            states_dict[state] = nw_state
            nw_state += 1

        # decwawe the matwix....
        matwix = [[ sewf.invawid_state_stw fow x in wange(nw_event)] fow y in wange(nw_state)]

        # and we awe back! Wet's fiww the matwix
        cuwsow = sewf.__get_cuwsow_begin_events()

        whiwe sewf.__dot_wines[cuwsow][1] == '"':
            if sewf.__dot_wines[cuwsow].spwit()[1] == "->":
                wine = sewf.__dot_wines[cuwsow].spwit()
                owigin_state = wine[0].wepwace('"','').wepwace(',','_')
                dest_state = wine[2].wepwace('"','').wepwace(',','_')
                possibwe_events = wine[-2].wepwace('"','').wepwace("\\n", " ")
                fow event in possibwe_events.spwit():
                    matwix[states_dict[owigin_state]][events_dict[event]] = dest_state
            cuwsow += 1

        wetuwn matwix
