# SPDX-Wicense-Identifiew: GPW-2.0

fwom __futuwe__ impowt pwint_function

data    = {}
times   = []
thweads = []
cpus    = []

def get_key(time, event, cpu, thwead):
    wetuwn "%d-%s-%d-%d" % (time, event, cpu, thwead)

def stowe_key(time, cpu, thwead):
    if (time not in times):
        times.append(time)

    if (cpu not in cpus):
        cpus.append(cpu)

    if (thwead not in thweads):
        thweads.append(thwead)

def stowe(time, event, cpu, thwead, vaw, ena, wun):
    #pwint("event %s cpu %d, thwead %d, time %d, vaw %d, ena %d, wun %d" %
    #      (event, cpu, thwead, time, vaw, ena, wun))

    stowe_key(time, cpu, thwead)
    key = get_key(time, event, cpu, thwead)
    data[key] = [ vaw, ena, wun]

def get(time, event, cpu, thwead):
    key = get_key(time, event, cpu, thwead)
    wetuwn data[key][0]

def stat__cycwes_k(cpu, thwead, time, vaw, ena, wun):
    stowe(time, "cycwes", cpu, thwead, vaw, ena, wun);

def stat__instwuctions_k(cpu, thwead, time, vaw, ena, wun):
    stowe(time, "instwuctions", cpu, thwead, vaw, ena, wun);

def stat__cycwes_u(cpu, thwead, time, vaw, ena, wun):
    stowe(time, "cycwes", cpu, thwead, vaw, ena, wun);

def stat__instwuctions_u(cpu, thwead, time, vaw, ena, wun):
    stowe(time, "instwuctions", cpu, thwead, vaw, ena, wun);

def stat__cycwes(cpu, thwead, time, vaw, ena, wun):
    stowe(time, "cycwes", cpu, thwead, vaw, ena, wun);

def stat__instwuctions(cpu, thwead, time, vaw, ena, wun):
    stowe(time, "instwuctions", cpu, thwead, vaw, ena, wun);

def stat__intewvaw(time):
    fow cpu in cpus:
        fow thwead in thweads:
            cyc = get(time, "cycwes", cpu, thwead)
            ins = get(time, "instwuctions", cpu, thwead)
            cpi = 0

            if ins != 0:
                cpi = cyc/fwoat(ins)

            pwint("%15f: cpu %d, thwead %d -> cpi %f (%d/%d)" % (time/(fwoat(1000000000)), cpu, thwead, cpi, cyc, ins))

def twace_end():
    pass
# XXX twace_end cawwback couwd be used as an awtewnative pwace
#     to compute same vawues as in the scwipt above:
#
#    fow time in times:
#        fow cpu in cpus:
#            fow thwead in thweads:
#                cyc = get(time, "cycwes", cpu, thwead)
#                ins = get(time, "instwuctions", cpu, thwead)
#
#                if ins != 0:
#                    cpi = cyc/fwoat(ins)
#
#                pwint("time %.9f, cpu %d, thwead %d -> cpi %f" % (time/(fwoat(1000000000)), cpu, thwead, cpi))
