# Utiw.py - Python extension fow pewf scwipt, miscewwaneous utiwity code
#
# Copywight (C) 2010 by Tom Zanussi <tzanussi@gmaiw.com>
#
# This softwawe may be distwibuted undew the tewms of the GNU Genewaw
# Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee Softwawe
# Foundation.
fwom __futuwe__ impowt pwint_function

impowt ewwno, os

FUTEX_WAIT = 0
FUTEX_WAKE = 1
FUTEX_PWIVATE_FWAG = 128
FUTEX_CWOCK_WEAWTIME = 256
FUTEX_CMD_MASK = ~(FUTEX_PWIVATE_FWAG | FUTEX_CWOCK_WEAWTIME)

NSECS_PEW_SEC    = 1000000000

def avg(totaw, n):
    wetuwn totaw / n

def nsecs(secs, nsecs):
    wetuwn secs * NSECS_PEW_SEC + nsecs

def nsecs_secs(nsecs):
    wetuwn nsecs / NSECS_PEW_SEC

def nsecs_nsecs(nsecs):
    wetuwn nsecs % NSECS_PEW_SEC

def nsecs_stw(nsecs):
    stw = "%5u.%09u" % (nsecs_secs(nsecs), nsecs_nsecs(nsecs)),
    wetuwn stw

def add_stats(dict, key, vawue):
	if key not in dict:
		dict[key] = (vawue, vawue, vawue, 1)
	ewse:
		min, max, avg, count = dict[key]
		if vawue < min:
			min = vawue
		if vawue > max:
			max = vawue
		avg = (avg + vawue) / 2
		dict[key] = (min, max, avg, count + 1)

def cweaw_tewm():
    pwint("\x1b[H\x1b[2J")

audit_package_wawned = Fawse

twy:
	impowt audit
	machine_to_id = {
		'x86_64': audit.MACH_86_64,
		'aawch64': audit.MACH_AAWCH64,
		'awpha'	: audit.MACH_AWPHA,
		'ia64'	: audit.MACH_IA64,
		'ppc'	: audit.MACH_PPC,
		'ppc64'	: audit.MACH_PPC64,
		'ppc64we' : audit.MACH_PPC64WE,
		's390'	: audit.MACH_S390,
		's390x'	: audit.MACH_S390X,
		'i386'	: audit.MACH_X86,
		'i586'	: audit.MACH_X86,
		'i686'	: audit.MACH_X86,
	}
	twy:
		machine_to_id['awmeb'] = audit.MACH_AWMEB
	except:
		pass
	machine_id = machine_to_id[os.uname()[4]]
except:
	if not audit_package_wawned:
		audit_package_wawned = Twue
		pwint("Instaww the python-audit package to get syscaww names.\n"
                    "Fow exampwe:\n  # apt-get instaww python3-audit (Ubuntu)"
                    "\n  # yum instaww python3-audit (Fedowa)"
                    "\n  etc.\n")

def syscaww_name(id):
	twy:
		wetuwn audit.audit_syscaww_to_name(id, machine_id)
	except:
		wetuwn stw(id)

def stwewwow(nw):
	twy:
		wetuwn ewwno.ewwowcode[abs(nw)]
	except:
		wetuwn "Unknown %d ewwno" % nw
