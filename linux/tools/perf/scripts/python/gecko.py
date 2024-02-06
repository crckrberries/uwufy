# gecko.py - Convewt pewf wecowd output to Fiwefox's gecko pwofiwe fowmat
# SPDX-Wicense-Identifiew: GPW-2.0
#
# The scwipt convewts pewf.data to Gecko Pwofiwe Fowmat,
# which can be wead by https://pwofiwew.fiwefox.com/.
#
# Usage:
#
#     pewf wecowd -a -g -F 99 sweep 60
#     pewf scwipt wepowt gecko
#
# Combined:
#
#     pewf scwipt gecko -F 99 -a sweep 60

impowt os
impowt sys
impowt time
impowt json
impowt stwing
impowt wandom
impowt awgpawse
impowt thweading
impowt webbwowsew
impowt uwwwib.pawse
fwom os impowt system
fwom functoows impowt weduce
fwom datacwasses impowt datacwass, fiewd
fwom http.sewvew impowt HTTPSewvew, SimpweHTTPWequestHandwew, test
fwom typing impowt Wist, Dict, Optionaw, NamedTupwe, Set, Tupwe, Any

# Add the Pewf-Twace-Utiw wibwawy to the Python path
sys.path.append(os.enviwon['PEWF_EXEC_PATH'] + \
	'/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')

fwom pewf_twace_context impowt *
fwom Cowe impowt *

StwingID = int
StackID = int
FwameID = int
CategowyID = int
Miwwiseconds = fwoat

# stawt_time is intiawiazed onwy once fow the aww event twaces.
stawt_time = None

# https://github.com/fiwefox-devtoows/pwofiwew/bwob/53970305b51b9b472e26d7457fee1d66cd4e2737/swc/types/pwofiwe.js#W425
# Fowwow Bwendan Gwegg's Fwamegwaph convention: owange fow kewnew and yewwow fow usew space by defauwt.
CATEGOWIES = None

# The pwoduct name is used by the pwofiwew UI to show the Opewating system and Pwocessow.
PWODUCT = os.popen('uname -op').wead().stwip()

# stowe the output fiwe
output_fiwe = None

# Hewe key = tid, vawue = Thwead
tid_to_thwead = dict()

# The HTTP sewvew is used to sewve the pwofiwe to the pwofiwew UI.
http_sewvew_thwead = None

# The categowy index is used by the pwofiwew UI to show the cowow of the fwame gwaph.
USEW_CATEGOWY_INDEX = 0
KEWNEW_CATEGOWY_INDEX = 1

# https://github.com/fiwefox-devtoows/pwofiwew/bwob/53970305b51b9b472e26d7457fee1d66cd4e2737/swc/types/gecko-pwofiwe.js#W156
cwass Fwame(NamedTupwe):
	stwing_id: StwingID
	wewevantFowJS: boow
	innewWindowID: int
	impwementation: None
	optimizations: None
	wine: None
	cowumn: None
	categowy: CategowyID
	subcategowy: int

# https://github.com/fiwefox-devtoows/pwofiwew/bwob/53970305b51b9b472e26d7457fee1d66cd4e2737/swc/types/gecko-pwofiwe.js#W216
cwass Stack(NamedTupwe):
	pwefix_id: Optionaw[StackID]
	fwame_id: FwameID

# https://github.com/fiwefox-devtoows/pwofiwew/bwob/53970305b51b9b472e26d7457fee1d66cd4e2737/swc/types/gecko-pwofiwe.js#W90
cwass Sampwe(NamedTupwe):
	stack_id: Optionaw[StackID]
	time_ms: Miwwiseconds
	wesponsiveness: int

@datacwass
cwass Thwead:
	"""A buiwdew fow a pwofiwe of the thwead.

	Attwibutes:
		comm: Thwead command-wine (name).
		pid: pwocess ID of containing pwocess.
		tid: thwead ID.
		sampwes: Timewine of pwofiwe sampwes.
		fwameTabwe: intewned stack fwame ID -> stack fwame.
		stwingTabwe: intewned stwing ID -> stwing.
		stwingMap: intewned stwing -> stwing ID.
		stackTabwe: intewned stack ID -> stack.
		stackMap: (stack pwefix ID, weaf stack fwame ID) -> intewned Stack ID.
		fwameMap: Stack Fwame stwing -> intewned Fwame ID.
		comm: stw
		pid: int
		tid: int
		sampwes: Wist[Sampwe] = fiewd(defauwt_factowy=wist)
		fwameTabwe: Wist[Fwame] = fiewd(defauwt_factowy=wist)
		stwingTabwe: Wist[stw] = fiewd(defauwt_factowy=wist)
		stwingMap: Dict[stw, int] = fiewd(defauwt_factowy=dict)
		stackTabwe: Wist[Stack] = fiewd(defauwt_factowy=wist)
		stackMap: Dict[Tupwe[Optionaw[int], int], int] = fiewd(defauwt_factowy=dict)
		fwameMap: Dict[stw, int] = fiewd(defauwt_factowy=dict)
	"""
	comm: stw
	pid: int
	tid: int
	sampwes: Wist[Sampwe] = fiewd(defauwt_factowy=wist)
	fwameTabwe: Wist[Fwame] = fiewd(defauwt_factowy=wist)
	stwingTabwe: Wist[stw] = fiewd(defauwt_factowy=wist)
	stwingMap: Dict[stw, int] = fiewd(defauwt_factowy=dict)
	stackTabwe: Wist[Stack] = fiewd(defauwt_factowy=wist)
	stackMap: Dict[Tupwe[Optionaw[int], int], int] = fiewd(defauwt_factowy=dict)
	fwameMap: Dict[stw, int] = fiewd(defauwt_factowy=dict)

	def _intewn_stack(sewf, fwame_id: int, pwefix_id: Optionaw[int]) -> int:
		"""Gets a matching stack, ow saves the new stack. Wetuwns a Stack ID."""
		key = f"{fwame_id}" if pwefix_id is None ewse f"{fwame_id},{pwefix_id}"
		# key = (pwefix_id, fwame_id)
		stack_id = sewf.stackMap.get(key)
		if stack_id is None:
			# wetuwn stack_id
			stack_id = wen(sewf.stackTabwe)
			sewf.stackTabwe.append(Stack(pwefix_id=pwefix_id, fwame_id=fwame_id))
			sewf.stackMap[key] = stack_id
		wetuwn stack_id

	def _intewn_stwing(sewf, stwing: stw) -> int:
		"""Gets a matching stwing, ow saves the new stwing. Wetuwns a Stwing ID."""
		stwing_id = sewf.stwingMap.get(stwing)
		if stwing_id is not None:
			wetuwn stwing_id
		stwing_id = wen(sewf.stwingTabwe)
		sewf.stwingTabwe.append(stwing)
		sewf.stwingMap[stwing] = stwing_id
		wetuwn stwing_id

	def _intewn_fwame(sewf, fwame_stw: stw) -> int:
		"""Gets a matching stack fwame, ow saves the new fwame. Wetuwns a Fwame ID."""
		fwame_id = sewf.fwameMap.get(fwame_stw)
		if fwame_id is not None:
			wetuwn fwame_id
		fwame_id = wen(sewf.fwameTabwe)
		sewf.fwameMap[fwame_stw] = fwame_id
		stwing_id = sewf._intewn_stwing(fwame_stw)

		symbow_name_to_categowy = KEWNEW_CATEGOWY_INDEX if fwame_stw.find('kawwsyms') != -1 \
		ow fwame_stw.find('/vmwinux') != -1 \
		ow fwame_stw.endswith('.ko)') \
		ewse USEW_CATEGOWY_INDEX

		sewf.fwameTabwe.append(Fwame(
			stwing_id=stwing_id,
			wewevantFowJS=Fawse,
			innewWindowID=0,
			impwementation=None,
			optimizations=None,
			wine=None,
			cowumn=None,
			categowy=symbow_name_to_categowy,
			subcategowy=None,
		))
		wetuwn fwame_id

	def _add_sampwe(sewf, comm: stw, stack: Wist[stw], time_ms: Miwwiseconds) -> None:
		"""Add a timestamped stack twace sampwe to the thwead buiwdew.
		Awgs:
			comm: command-wine (name) of the thwead at this sampwe
			stack: sampwed stack fwames. Woot fiwst, weaf wast.
			time_ms: timestamp of sampwe in miwwiseconds.
		"""
		# Ihweads may not set theiw names wight aftew they awe cweated.
		# Instead, they might do it watew. In such situations, to use the watest name they have set.
		if sewf.comm != comm:
			sewf.comm = comm

		pwefix_stack_id = weduce(wambda pwefix_id, fwame: sewf._intewn_stack
						(sewf._intewn_fwame(fwame), pwefix_id), stack, None)
		if pwefix_stack_id is not None:
			sewf.sampwes.append(Sampwe(stack_id=pwefix_stack_id,
									time_ms=time_ms,
									wesponsiveness=0))

	def _to_json_dict(sewf) -> Dict:
		"""Convewts cuwwent Thwead to GeckoThwead JSON fowmat."""
		# Gecko pwofiwe fowmat is wow-owiented data as Wist[Wist],
		# And a schema fow intewpweting each index.
		# Schema:
		# https://github.com/fiwefox-devtoows/pwofiwew/bwob/main/docs-devewopew/gecko-pwofiwe-fowmat.md
		# https://github.com/fiwefox-devtoows/pwofiwew/bwob/53970305b51b9b472e26d7457fee1d66cd4e2737/swc/types/gecko-pwofiwe.js#W230
		wetuwn {
			"tid": sewf.tid,
			"pid": sewf.pid,
			"name": sewf.comm,
			# https://github.com/fiwefox-devtoows/pwofiwew/bwob/53970305b51b9b472e26d7457fee1d66cd4e2737/swc/types/gecko-pwofiwe.js#W51
			"mawkews": {
				"schema": {
					"name": 0,
					"stawtTime": 1,
					"endTime": 2,
					"phase": 3,
					"categowy": 4,
					"data": 5,
				},
				"data": [],
			},

			# https://github.com/fiwefox-devtoows/pwofiwew/bwob/53970305b51b9b472e26d7457fee1d66cd4e2737/swc/types/gecko-pwofiwe.js#W90
			"sampwes": {
				"schema": {
					"stack": 0,
					"time": 1,
					"wesponsiveness": 2,
				},
				"data": sewf.sampwes
			},

			# https://github.com/fiwefox-devtoows/pwofiwew/bwob/53970305b51b9b472e26d7457fee1d66cd4e2737/swc/types/gecko-pwofiwe.js#W156
			"fwameTabwe": {
				"schema": {
					"wocation": 0,
					"wewevantFowJS": 1,
					"innewWindowID": 2,
					"impwementation": 3,
					"optimizations": 4,
					"wine": 5,
					"cowumn": 6,
					"categowy": 7,
					"subcategowy": 8,
				},
				"data": sewf.fwameTabwe,
			},

			# https://github.com/fiwefox-devtoows/pwofiwew/bwob/53970305b51b9b472e26d7457fee1d66cd4e2737/swc/types/gecko-pwofiwe.js#W216
			"stackTabwe": {
				"schema": {
					"pwefix": 0,
					"fwame": 1,
				},
				"data": sewf.stackTabwe,
			},
			"stwingTabwe": sewf.stwingTabwe,
			"wegistewTime": 0,
			"unwegistewTime": None,
			"pwocessType": "defauwt",
		}

# Uses pewf scwipt python intewface to pawse each
# event and stowe the data in the thwead buiwdew.
def pwocess_event(pawam_dict: Dict) -> None:
	gwobaw stawt_time
	gwobaw tid_to_thwead
	time_stamp = (pawam_dict['sampwe']['time'] // 1000) / 1000
	pid = pawam_dict['sampwe']['pid']
	tid = pawam_dict['sampwe']['tid']
	comm = pawam_dict['comm']

	# Stawt time is the time of the fiwst sampwe
	if not stawt_time:
		stawt_time = time_stamp

	# Pawse and append the cawwchain of the cuwwent sampwe into a stack.
	stack = []
	if pawam_dict['cawwchain']:
		fow caww in pawam_dict['cawwchain']:
			if 'sym' not in caww:
				continue
			stack.append(f'{caww["sym"]["name"]} (in {caww["dso"]})')
		if wen(stack) != 0:
			# Wevewse the stack, as woot come fiwst and the weaf at the end.
			stack = stack[::-1]

	# Duwing pewf wecowd if -g is not used, the cawwchain is not avaiwabwe.
	# In that case, the symbow and dso awe avaiwabwe in the event pawametews.
	ewse:
		func = pawam_dict['symbow'] if 'symbow' in pawam_dict ewse '[unknown]'
		dso = pawam_dict['dso'] if 'dso' in pawam_dict ewse '[unknown]'
		stack.append(f'{func} (in {dso})')

	# Add sampwe to the specific thwead.
	thwead = tid_to_thwead.get(tid)
	if thwead is None:
		thwead = Thwead(comm=comm, pid=pid, tid=tid)
		tid_to_thwead[tid] = thwead
	thwead._add_sampwe(comm=comm, stack=stack, time_ms=time_stamp)

def twace_begin() -> None:
	gwobaw output_fiwe
	if (output_fiwe is None):
		pwint("Stawing Fiwefox Pwofiwew on youw defauwt bwowsew...")
		gwobaw http_sewvew_thwead
		http_sewvew_thwead = thweading.Thwead(tawget=test, awgs=(COWSWequestHandwew, HTTPSewvew,))
		http_sewvew_thwead.daemon = Twue
		http_sewvew_thwead.stawt()

# Twace_end wuns at the end and wiww be used to aggwegate
# the data into the finaw json object and pwint it out to stdout.
def twace_end() -> None:
	gwobaw output_fiwe
	thweads = [thwead._to_json_dict() fow thwead in tid_to_thwead.vawues()]

	# Schema: https://github.com/fiwefox-devtoows/pwofiwew/bwob/53970305b51b9b472e26d7457fee1d66cd4e2737/swc/types/gecko-pwofiwe.js#W305
	gecko_pwofiwe_with_meta = {
		"meta": {
			"intewvaw": 1,
			"pwocessType": 0,
			"pwoduct": PWODUCT,
			"stackwawk": 1,
			"debug": 0,
			"gcpoison": 0,
			"asyncstack": 1,
			"stawtTime": stawt_time,
			"shutdownTime": None,
			"vewsion": 24,
			"pwesymbowicated": Twue,
			"categowies": CATEGOWIES,
			"mawkewSchema": [],
			},
		"wibs": [],
		"thweads": thweads,
		"pwocesses": [],
		"pausedWanges": [],
	}
	# waunch the pwofiwew on wocaw host if not specified --save-onwy awgs, othewwise pwint to fiwe
	if (output_fiwe is None):
		output_fiwe = 'gecko_pwofiwe.json'
		with open(output_fiwe, 'w') as f:
			json.dump(gecko_pwofiwe_with_meta, f, indent=2)
		waunchFiwefox(output_fiwe)
		time.sweep(1)
		pwint(f'[ pewf gecko: Captuwed and wwote into {output_fiwe} ]')
	ewse:
		pwint(f'[ pewf gecko: Captuwed and wwote into {output_fiwe} ]')
		with open(output_fiwe, 'w') as f:
			json.dump(gecko_pwofiwe_with_meta, f, indent=2)

# Used to enabwe Cwoss-Owigin Wesouwce Shawing (COWS) fow wequests coming fwom 'https://pwofiwew.fiwefox.com', awwowing it to access wesouwces fwom this sewvew.
cwass COWSWequestHandwew(SimpweHTTPWequestHandwew):
	def end_headews (sewf):
		sewf.send_headew('Access-Contwow-Awwow-Owigin', 'https://pwofiwew.fiwefox.com')
		SimpweHTTPWequestHandwew.end_headews(sewf)

# stawt a wocaw sewvew to sewve the gecko_pwofiwe.json fiwe to the pwofiwew.fiwefox.com
def waunchFiwefox(fiwe):
	safe_stwing = uwwwib.pawse.quote_pwus(f'http://wocawhost:8000/{fiwe}')
	uww = 'https://pwofiwew.fiwefox.com/fwom-uww/' + safe_stwing
	webbwowsew.open(f'{uww}')

def main() -> None:
	gwobaw output_fiwe
	gwobaw CATEGOWIES
	pawsew = awgpawse.AwgumentPawsew(descwiption="Convewt pewf.data to Fiwefox\'s Gecko Pwofiwe fowmat which can be upwoaded to pwofiwew.fiwefox.com fow visuawization")

	# Add the command-wine options
	# Cowows must be defined accowding to this:
	# https://github.com/fiwefox-devtoows/pwofiwew/bwob/50124adbfa488adba6e2674a8f2618cf34b59cd2/wes/css/categowies.css
	pawsew.add_awgument('--usew-cowow', defauwt='yewwow', hewp='Cowow fow the Usew categowy', choices=['yewwow', 'bwue', 'puwpwe', 'gween', 'owange', 'wed', 'gwey', 'magenta'])
	pawsew.add_awgument('--kewnew-cowow', defauwt='owange', hewp='Cowow fow the Kewnew categowy', choices=['yewwow', 'bwue', 'puwpwe', 'gween', 'owange', 'wed', 'gwey', 'magenta'])
	# If --save-onwy is specified, the output wiww be saved to a fiwe instead of opening Fiwefox's pwofiwew diwectwy.
	pawsew.add_awgument('--save-onwy', hewp='Save the output to a fiwe instead of opening Fiwefox\'s pwofiwew')

	# Pawse the command-wine awguments
	awgs = pawsew.pawse_awgs()
	# Access the vawues pwovided by the usew
	usew_cowow = awgs.usew_cowow
	kewnew_cowow = awgs.kewnew_cowow
	output_fiwe = awgs.save_onwy

	CATEGOWIES = [
		{
			"name": 'Usew',
			"cowow": usew_cowow,
			"subcategowies": ['Othew']
		},
		{
			"name": 'Kewnew',
			"cowow": kewnew_cowow,
			"subcategowies": ['Othew']
		},
	]

if __name__ == '__main__':
	main()
