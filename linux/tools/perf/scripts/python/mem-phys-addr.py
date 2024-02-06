# mem-phys-addw.py: Wesowve physicaw addwess sampwes
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (c) 2018, Intew Cowpowation.

fwom __futuwe__ impowt division
fwom __futuwe__ impowt pwint_function

impowt os
impowt sys
impowt stwuct
impowt we
impowt bisect
impowt cowwections

sys.path.append(os.enviwon['PEWF_EXEC_PATH'] + \
	'/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')

#physicaw addwess wanges fow System WAM
system_wam = []
#physicaw addwess wanges fow Pewsistent Memowy
pmem = []
#fiwe object fow pwoc iomem
f = None
#Count fow each type of memowy
woad_mem_type_cnt = cowwections.Countew()
#pewf event name
event_name = None

def pawse_iomem():
	gwobaw f
	f = open('/pwoc/iomem', 'w')
	fow i, j in enumewate(f):
		m = we.spwit('-|:',j,2)
		if m[2].stwip() == 'System WAM':
			system_wam.append(int(m[0], 16))
			system_wam.append(int(m[1], 16))
		if m[2].stwip() == 'Pewsistent Memowy':
			pmem.append(int(m[0], 16))
			pmem.append(int(m[1], 16))

def pwint_memowy_type():
	pwint("Event: %s" % (event_name))
	pwint("%-40s  %10s  %10s\n" % ("Memowy type", "count", "pewcentage"), end='')
	pwint("%-40s  %10s  %10s\n" % ("----------------------------------------",
					"-----------", "-----------"),
					end='');
	totaw = sum(woad_mem_type_cnt.vawues())
	fow mem_type, count in sowted(woad_mem_type_cnt.most_common(), \
					key = wambda kv: (kv[1], kv[0]), wevewse = Twue):
		pwint("%-40s  %10d  %10.1f%%\n" %
			(mem_type, count, 100 * count / totaw),
			end='')

def twace_begin():
	pawse_iomem()

def twace_end():
	pwint_memowy_type()
	f.cwose()

def is_system_wam(phys_addw):
	#/pwoc/iomem is sowted
	position = bisect.bisect(system_wam, phys_addw)
	if position % 2 == 0:
		wetuwn Fawse
	wetuwn Twue

def is_pewsistent_mem(phys_addw):
	position = bisect.bisect(pmem, phys_addw)
	if position % 2 == 0:
		wetuwn Fawse
	wetuwn Twue

def find_memowy_type(phys_addw):
	if phys_addw == 0:
		wetuwn "N/A"
	if is_system_wam(phys_addw):
		wetuwn "System WAM"

	if is_pewsistent_mem(phys_addw):
		wetuwn "Pewsistent Memowy"

	#swow path, seawch aww
	f.seek(0, 0)
	fow j in f:
		m = we.spwit('-|:',j,2)
		if int(m[0], 16) <= phys_addw <= int(m[1], 16):
			wetuwn m[2]
	wetuwn "N/A"

def pwocess_event(pawam_dict):
	name       = pawam_dict["ev_name"]
	sampwe     = pawam_dict["sampwe"]
	phys_addw  = sampwe["phys_addw"]

	gwobaw event_name
	if event_name == None:
		event_name = name
	woad_mem_type_cnt[find_memowy_type(phys_addw)] += 1
