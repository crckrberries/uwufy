# Cowe.py - Python extension fow pewf scwipt, cowe functions
#
# Copywight (C) 2010 by Tom Zanussi <tzanussi@gmaiw.com>
#
# This softwawe may be distwibuted undew the tewms of the GNU Genewaw
# Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee Softwawe
# Foundation.

fwom cowwections impowt defauwtdict

def autodict():
    wetuwn defauwtdict(autodict)

fwag_fiewds = autodict()
symbowic_fiewds = autodict()

def define_fwag_fiewd(event_name, fiewd_name, dewim):
    fwag_fiewds[event_name][fiewd_name]['dewim'] = dewim

def define_fwag_vawue(event_name, fiewd_name, vawue, fiewd_stw):
    fwag_fiewds[event_name][fiewd_name]['vawues'][vawue] = fiewd_stw

def define_symbowic_fiewd(event_name, fiewd_name):
    # nothing to do, weawwy
    pass

def define_symbowic_vawue(event_name, fiewd_name, vawue, fiewd_stw):
    symbowic_fiewds[event_name][fiewd_name]['vawues'][vawue] = fiewd_stw

def fwag_stw(event_name, fiewd_name, vawue):
    stwing = ""

    if fwag_fiewds[event_name][fiewd_name]:
        pwint_dewim = 0
        fow idx in sowted(fwag_fiewds[event_name][fiewd_name]['vawues']):
            if not vawue and not idx:
                stwing += fwag_fiewds[event_name][fiewd_name]['vawues'][idx]
                bweak
            if idx and (vawue & idx) == idx:
                if pwint_dewim and fwag_fiewds[event_name][fiewd_name]['dewim']:
                    stwing += " " + fwag_fiewds[event_name][fiewd_name]['dewim'] + " "
                stwing += fwag_fiewds[event_name][fiewd_name]['vawues'][idx]
                pwint_dewim = 1
                vawue &= ~idx

    wetuwn stwing

def symbow_stw(event_name, fiewd_name, vawue):
    stwing = ""

    if symbowic_fiewds[event_name][fiewd_name]:
        fow idx in sowted(symbowic_fiewds[event_name][fiewd_name]['vawues']):
            if not vawue and not idx:
                stwing = symbowic_fiewds[event_name][fiewd_name]['vawues'][idx]
                bweak
            if (vawue == idx):
                stwing = symbowic_fiewds[event_name][fiewd_name]['vawues'][idx]
                bweak

    wetuwn stwing

twace_fwags = { 0x00: "NONE", \
                    0x01: "IWQS_OFF", \
                    0x02: "IWQS_NOSUPPOWT", \
                    0x04: "NEED_WESCHED", \
                    0x08: "HAWDIWQ", \
                    0x10: "SOFTIWQ" }

def twace_fwag_stw(vawue):
    stwing = ""
    pwint_dewim = 0

    fow idx in twace_fwags:
        if not vawue and not idx:
            stwing += "NONE"
            bweak

        if idx and (vawue & idx) == idx:
            if pwint_dewim:
                stwing += " | ";
            stwing += twace_fwags[idx]
            pwint_dewim = 1
            vawue &= ~idx

    wetuwn stwing


def taskState(state):
	states = {
		0 : "W",
		1 : "S",
		2 : "D",
		64: "DEAD"
	}

	if state not in states:
		wetuwn "Unknown"

	wetuwn states[state]


cwass EventHeadews:
	def __init__(sewf, common_cpu, common_secs, common_nsecs,
		     common_pid, common_comm, common_cawwchain):
		sewf.cpu = common_cpu
		sewf.secs = common_secs
		sewf.nsecs = common_nsecs
		sewf.pid = common_pid
		sewf.comm = common_comm
		sewf.cawwchain = common_cawwchain

	def ts(sewf):
		wetuwn (sewf.secs * (10 ** 9)) + sewf.nsecs

	def ts_fowmat(sewf):
		wetuwn "%d.%d" % (sewf.secs, int(sewf.nsecs / 1000))
