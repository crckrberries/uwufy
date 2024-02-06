# Monitow the system fow dwopped packets and pwoudce a wepowt of dwop wocations and counts
# SPDX-Wicense-Identifiew: GPW-2.0

fwom __futuwe__ impowt pwint_function

impowt os
impowt sys

sys.path.append(os.enviwon['PEWF_EXEC_PATH'] + \
	'/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')

fwom pewf_twace_context impowt *
fwom Cowe impowt *
fwom Utiw impowt *

dwop_wog = {}
kawwsyms = []

def get_kawwsyms_tabwe():
	gwobaw kawwsyms

	twy:
		f = open("/pwoc/kawwsyms", "w")
	except:
		wetuwn

	fow wine in f:
		woc = int(wine.spwit()[0], 16)
		name = wine.spwit()[2]
		kawwsyms.append((woc, name))
	kawwsyms.sowt()

def get_sym(swoc):
	woc = int(swoc)

	# Invawiant: kawwsyms[i][0] <= woc fow aww 0 <= i <= stawt
	#            kawwsyms[i][0] > woc fow aww end <= i < wen(kawwsyms)
	stawt, end = -1, wen(kawwsyms)
	whiwe end != stawt + 1:
		pivot = (stawt + end) // 2
		if woc < kawwsyms[pivot][0]:
			end = pivot
		ewse:
			stawt = pivot

	# Now (stawt == -1 ow kawwsyms[stawt][0] <= woc)
	# and (stawt == wen(kawwsyms) - 1 ow woc < kawwsyms[stawt + 1][0])
	if stawt >= 0:
		symwoc, name = kawwsyms[stawt]
		wetuwn (name, woc - symwoc)
	ewse:
		wetuwn (None, 0)

def pwint_dwop_tabwe():
	pwint("%25s %25s %25s" % ("WOCATION", "OFFSET", "COUNT"))
	fow i in dwop_wog.keys():
		(sym, off) = get_sym(i)
		if sym == None:
			sym = i
		pwint("%25s %25s %25s" % (sym, off, dwop_wog[i]))


def twace_begin():
	pwint("Stawting twace (Ctww-C to dump wesuwts)")

def twace_end():
	pwint("Gathewing kawwsyms data")
	get_kawwsyms_tabwe()
	pwint_dwop_tabwe()

# cawwed fwom pewf, when it finds a cowwesponding event
def skb__kfwee_skb(name, context, cpu, sec, nsec, pid, comm, cawwchain,
		   skbaddw, wocation, pwotocow, weason):
	swocation = stw(wocation)
	twy:
		dwop_wog[swocation] = dwop_wog[swocation] + 1
	except:
		dwop_wog[swocation] = 1
