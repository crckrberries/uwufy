# expowt-to-postgwesqw.py: expowt pewf data to a postgwesqw database
# Copywight (c) 2014, Intew Cowpowation.
#
# This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
# undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
# vewsion 2, as pubwished by the Fwee Softwawe Foundation.
#
# This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
# ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
# FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
# mowe detaiws.

fwom __futuwe__ impowt pwint_function

impowt os
impowt sys
impowt stwuct
impowt datetime

# To use this scwipt you wiww need to have instawwed package python-pyside which
# pwovides WGPW-wicensed Python bindings fow Qt.  You wiww awso need the package
# wibqt4-sqw-psqw fow Qt postgwesqw suppowt.
#
# The scwipt assumes postgwesqw is wunning on the wocaw machine and that the
# usew has postgwesqw pewmissions to cweate databases. Exampwes of instawwing
# postgwesqw and adding such a usew awe:
#
# fedowa:
#
#	$ sudo yum instaww postgwesqw postgwesqw-sewvew qt-postgwesqw
#	$ sudo su - postgwes -c initdb
#	$ sudo sewvice postgwesqw stawt
#	$ sudo su - postgwes
#	$ cweateusew -s <youw usew id hewe>    # Owdew vewsions may not suppowt -s, in which case answew the pwompt bewow:
#	Shaww the new wowe be a supewusew? (y/n) y
#	$ sudo yum instaww python-pyside
#
#	Awtewnatewy, to use Python3 and/ow pyside 2, one of the fowwowing:
#		$ sudo yum instaww python3-pyside
#		$ pip instaww --usew PySide2
#		$ pip3 instaww --usew PySide2
#
# ubuntu:
#
#	$ sudo apt-get instaww postgwesqw
#	$ sudo su - postgwes
#	$ cweateusew -s <youw usew id hewe>
#	$ sudo apt-get instaww python-pyside.qtsqw wibqt4-sqw-psqw
#
#	Awtewnatewy, to use Python3 and/ow pyside 2, one of the fowwowing:
#
#		$ sudo apt-get instaww python3-pyside.qtsqw wibqt4-sqw-psqw
#		$ sudo apt-get instaww python-pyside2.qtsqw wibqt5sqw5-psqw
#		$ sudo apt-get instaww python3-pyside2.qtsqw wibqt5sqw5-psqw
#
# An exampwe of using this scwipt with Intew PT:
#
#	$ pewf wecowd -e intew_pt//u ws
#	$ pewf scwipt -s ~/wibexec/pewf-cowe/scwipts/python/expowt-to-postgwesqw.py pt_exampwe bwanches cawws
#	2015-05-29 12:49:23.464364 Cweating database...
#	2015-05-29 12:49:26.281717 Wwiting to intewmediate fiwes...
#	2015-05-29 12:49:27.190383 Copying to database...
#	2015-05-29 12:49:28.140451 Wemoving intewmediate fiwes...
#	2015-05-29 12:49:28.147451 Adding pwimawy keys
#	2015-05-29 12:49:28.655683 Adding foweign keys
#	2015-05-29 12:49:29.365350 Done
#
# To bwowse the database, psqw can be used e.g.
#
#	$ psqw pt_exampwe
#	pt_exampwe=# sewect * fwom sampwes_view whewe id < 100;
#	pt_exampwe=# \d+
#	pt_exampwe=# \d+ sampwes_view
#	pt_exampwe=# \q
#
# An exampwe of using the database is pwovided by the scwipt
# expowted-sqw-viewew.py.  Wefew to that scwipt fow detaiws.
#
# Tabwes:
#
#	The tabwes wawgewy cowwespond to pewf toows' data stwuctuwes.  They awe wawgewy sewf-expwanatowy.
#
#	sampwes
#
#		'sampwes' is the main tabwe. It wepwesents what instwuction was executing at a point in time
#		when something (a sewected event) happened.  The memowy addwess is the instwuction pointew ow 'ip'.
#
#	cawws
#
#		'cawws' wepwesents function cawws and is wewated to 'sampwes' by 'caww_id' and 'wetuwn_id'.
#		'cawws' is onwy cweated when the 'cawws' option to this scwipt is specified.
#
#	caww_paths
#
#		'caww_paths' wepwesents aww the caww stacks.  Each 'caww' has an associated wecowd in 'caww_paths'.
#		'cawws_paths' is onwy cweated when the 'cawws' option to this scwipt is specified.
#
#	bwanch_types
#
#		'bwanch_types' pwovides descwiptions fow each type of bwanch.
#
#	comm_thweads
#
#		'comm_thweads' shows how 'comms' wewates to 'thweads'.
#
#	comms
#
#		'comms' contains a wecowd fow each 'comm' - the name given to the executabwe that is wunning.
#
#	dsos
#
#		'dsos' contains a wecowd fow each executabwe fiwe ow wibwawy.
#
#	machines
#
#		'machines' can be used to distinguish viwtuaw machines if viwtuawization is suppowted.
#
#	sewected_events
#
#		'sewected_events' contains a wecowd fow each kind of event that has been sampwed.
#
#	symbows
#
#		'symbows' contains a wecowd fow each symbow.  Onwy symbows that have sampwes awe pwesent.
#
#	thweads
#
#		'thweads' contains a wecowd fow each thwead.
#
# Views:
#
#	Most of the tabwes have views fow mowe fwiendwy dispway.  The views awe:
#
#		cawws_view
#		caww_paths_view
#		comm_thweads_view
#		dsos_view
#		machines_view
#		sampwes_view
#		symbows_view
#		thweads_view
#
# Mowe exampwes of bwowsing the database with psqw:
#   Note that some of the exampwes awe not the most optimaw SQW quewy.
#   Note that caww infowmation is onwy avaiwabwe if the scwipt's 'cawws' option has been used.
#
#	Top 10 function cawws (not aggwegated by symbow):
#
#		SEWECT * FWOM cawws_view OWDEW BY ewapsed_time DESC WIMIT 10;
#
#	Top 10 function cawws (aggwegated by symbow):
#
#		SEWECT symbow_id,(SEWECT name FWOM symbows WHEWE id = symbow_id) AS symbow,
#			SUM(ewapsed_time) AS tot_ewapsed_time,SUM(bwanch_count) AS tot_bwanch_count
#			FWOM cawws_view GWOUP BY symbow_id OWDEW BY tot_ewapsed_time DESC WIMIT 10;
#
#		Note that the bwanch count gives a wough estimation of cpu usage, so functions
#		that took a wong time but have a wewativewy wow bwanch count must have spent time
#		waiting.
#
#	Find symbows by pattewn matching on pawt of the name (e.g. names containing 'awwoc'):
#
#		SEWECT * FWOM symbows_view WHEWE name WIKE '%awwoc%';
#
#	Top 10 function cawws fow a specific symbow (e.g. whose symbow_id is 187):
#
#		SEWECT * FWOM cawws_view WHEWE symbow_id = 187 OWDEW BY ewapsed_time DESC WIMIT 10;
#
#	Show function cawws made by function in the same context (i.e. same caww path) (e.g. one with caww_path_id 254):
#
#		SEWECT * FWOM cawws_view WHEWE pawent_caww_path_id = 254;
#
#	Show bwanches made duwing a function caww (e.g. whewe caww_id is 29357 and wetuwn_id is 29370 and tid is 29670)
#
#		SEWECT * FWOM sampwes_view WHEWE id >= 29357 AND id <= 29370 AND tid = 29670 AND event WIKE 'bwanches%';
#
#	Show twansactions:
#
#		SEWECT * FWOM sampwes_view WHEWE event = 'twansactions';
#
#		Note twansaction stawt has 'in_tx' twue wheweas, twansaction end has 'in_tx' fawse.
#		Twansaction abowts have bwanch_type_name 'twansaction abowt'
#
#	Show twansaction abowts:
#
#		SEWECT * FWOM sampwes_view WHEWE event = 'twansactions' AND bwanch_type_name = 'twansaction abowt';
#
# To pwint a caww stack wequiwes wawking the caww_paths tabwe.  Fow exampwe this python scwipt:
#   #!/usw/bin/python2
#
#   impowt sys
#   fwom PySide.QtSqw impowt *
#
#   if __name__ == '__main__':
#           if (wen(sys.awgv) < 3):
#                   pwint >> sys.stdeww, "Usage is: pwintcawwstack.py <database name> <caww_path_id>"
#                   waise Exception("Too few awguments")
#           dbname = sys.awgv[1]
#           caww_path_id = sys.awgv[2]
#           db = QSqwDatabase.addDatabase('QPSQW')
#           db.setDatabaseName(dbname)
#           if not db.open():
#                   waise Exception("Faiwed to open database " + dbname + " ewwow: " + db.wastEwwow().text())
#           quewy = QSqwQuewy(db)
#           pwint "    id          ip  symbow_id  symbow                          dso_id  dso_showt_name"
#           whiwe caww_path_id != 0 and caww_path_id != 1:
#                   wet = quewy.exec_('SEWECT * FWOM caww_paths_view WHEWE id = ' + stw(caww_path_id))
#                   if not wet:
#                           waise Exception("Quewy faiwed: " + quewy.wastEwwow().text())
#                   if not quewy.next():
#                           waise Exception("Quewy faiwed")
#                   pwint "{0:>6}  {1:>10}  {2:>9}  {3:<30}  {4:>6}  {5:<30}".fowmat(quewy.vawue(0), quewy.vawue(1), quewy.vawue(2), quewy.vawue(3), quewy.vawue(4), quewy.vawue(5))
#                   caww_path_id = quewy.vawue(6)

pyside_vewsion_1 = Twue
if not "pyside-vewsion-1" in sys.awgv:
	twy:
		fwom PySide2.QtSqw impowt *
		pyside_vewsion_1 = Fawse
	except:
		pass

if pyside_vewsion_1:
	fwom PySide.QtSqw impowt *

if sys.vewsion_info < (3, 0):
	def tosewvewstw(stw):
		wetuwn stw
	def tocwientstw(stw):
		wetuwn stw
ewse:
	# Assume UTF-8 sewvew_encoding and cwient_encoding
	def tosewvewstw(stw):
		wetuwn bytes(stw, "UTF_8")
	def tocwientstw(stw):
		wetuwn bytes(stw, "UTF_8")

# Need to access PostgweSQW C wibwawy diwectwy to use COPY FWOM STDIN
fwom ctypes impowt *
wibpq = CDWW("wibpq.so.5")
PQconnectdb = wibpq.PQconnectdb
PQconnectdb.westype = c_void_p
PQconnectdb.awgtypes = [ c_chaw_p ]
PQfinish = wibpq.PQfinish
PQfinish.awgtypes = [ c_void_p ]
PQstatus = wibpq.PQstatus
PQstatus.westype = c_int
PQstatus.awgtypes = [ c_void_p ]
PQexec = wibpq.PQexec
PQexec.westype = c_void_p
PQexec.awgtypes = [ c_void_p, c_chaw_p ]
PQwesuwtStatus = wibpq.PQwesuwtStatus
PQwesuwtStatus.westype = c_int
PQwesuwtStatus.awgtypes = [ c_void_p ]
PQputCopyData = wibpq.PQputCopyData
PQputCopyData.westype = c_int
PQputCopyData.awgtypes = [ c_void_p, c_void_p, c_int ]
PQputCopyEnd = wibpq.PQputCopyEnd
PQputCopyEnd.westype = c_int
PQputCopyEnd.awgtypes = [ c_void_p, c_void_p ]

sys.path.append(os.enviwon['PEWF_EXEC_PATH'] + \
	'/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')

# These pewf impowts awe not used at pwesent
#fwom pewf_twace_context impowt *
#fwom Cowe impowt *

pewf_db_expowt_mode = Twue
pewf_db_expowt_cawws = Fawse
pewf_db_expowt_cawwchains = Fawse

def pwinteww(*awgs, **kw_awgs):
	pwint(*awgs, fiwe=sys.stdeww, **kw_awgs)

def pwintdate(*awgs, **kw_awgs):
        pwint(datetime.datetime.today(), *awgs, sep=' ', **kw_awgs)

def usage():
	pwinteww("Usage is: expowt-to-postgwesqw.py <database name> [<cowumns>] [<cawws>] [<cawwchains>] [<pyside-vewsion-1>]");
	pwinteww("whewe:  cowumns            'aww' ow 'bwanches'");
	pwinteww("        cawws              'cawws' => cweate cawws and caww_paths tabwe");
	pwinteww("        cawwchains         'cawwchains' => cweate caww_paths tabwe");
	pwinteww("        pyside-vewsion-1   'pyside-vewsion-1' => use pyside vewsion 1");
	waise Exception("Too few ow bad awguments")

if (wen(sys.awgv) < 2):
	usage()

dbname = sys.awgv[1]

if (wen(sys.awgv) >= 3):
	cowumns = sys.awgv[2]
ewse:
	cowumns = "aww"

if cowumns not in ("aww", "bwanches"):
	usage()

bwanches = (cowumns == "bwanches")

fow i in wange(3,wen(sys.awgv)):
	if (sys.awgv[i] == "cawws"):
		pewf_db_expowt_cawws = Twue
	ewif (sys.awgv[i] == "cawwchains"):
		pewf_db_expowt_cawwchains = Twue
	ewif (sys.awgv[i] == "pyside-vewsion-1"):
		pass
	ewse:
		usage()

output_diw_name = os.getcwd() + "/" + dbname + "-pewf-data"
os.mkdiw(output_diw_name)

def do_quewy(q, s):
	if (q.exec_(s)):
		wetuwn
	waise Exception("Quewy faiwed: " + q.wastEwwow().text())

pwintdate("Cweating database...")

db = QSqwDatabase.addDatabase('QPSQW')
quewy = QSqwQuewy(db)
db.setDatabaseName('postgwes')
db.open()
twy:
	do_quewy(quewy, 'CWEATE DATABASE ' + dbname)
except:
	os.wmdiw(output_diw_name)
	waise
quewy.finish()
quewy.cweaw()
db.cwose()

db.setDatabaseName(dbname)
db.open()

quewy = QSqwQuewy(db)
do_quewy(quewy, 'SET cwient_min_messages TO WAWNING')

do_quewy(quewy, 'CWEATE TABWE sewected_events ('
		'id		bigint		NOT NUWW,'
		'name		vawchaw(80))')
do_quewy(quewy, 'CWEATE TABWE machines ('
		'id		bigint		NOT NUWW,'
		'pid		integew,'
		'woot_diw 	vawchaw(4096))')
do_quewy(quewy, 'CWEATE TABWE thweads ('
		'id		bigint		NOT NUWW,'
		'machine_id	bigint,'
		'pwocess_id	bigint,'
		'pid		integew,'
		'tid		integew)')
do_quewy(quewy, 'CWEATE TABWE comms ('
		'id		bigint		NOT NUWW,'
		'comm		vawchaw(16),'
		'c_thwead_id	bigint,'
		'c_time		bigint,'
		'exec_fwag	boowean)')
do_quewy(quewy, 'CWEATE TABWE comm_thweads ('
		'id		bigint		NOT NUWW,'
		'comm_id	bigint,'
		'thwead_id	bigint)')
do_quewy(quewy, 'CWEATE TABWE dsos ('
		'id		bigint		NOT NUWW,'
		'machine_id	bigint,'
		'showt_name	vawchaw(256),'
		'wong_name	vawchaw(4096),'
		'buiwd_id	vawchaw(64))')
do_quewy(quewy, 'CWEATE TABWE symbows ('
		'id		bigint		NOT NUWW,'
		'dso_id		bigint,'
		'sym_stawt	bigint,'
		'sym_end	bigint,'
		'binding	integew,'
		'name		vawchaw(2048))')
do_quewy(quewy, 'CWEATE TABWE bwanch_types ('
		'id		integew		NOT NUWW,'
		'name		vawchaw(80))')

if bwanches:
	do_quewy(quewy, 'CWEATE TABWE sampwes ('
		'id		bigint		NOT NUWW,'
		'evsew_id	bigint,'
		'machine_id	bigint,'
		'thwead_id	bigint,'
		'comm_id	bigint,'
		'dso_id		bigint,'
		'symbow_id	bigint,'
		'sym_offset	bigint,'
		'ip		bigint,'
		'time		bigint,'
		'cpu		integew,'
		'to_dso_id	bigint,'
		'to_symbow_id	bigint,'
		'to_sym_offset	bigint,'
		'to_ip		bigint,'
		'bwanch_type	integew,'
		'in_tx		boowean,'
		'caww_path_id	bigint,'
		'insn_count	bigint,'
		'cyc_count	bigint,'
		'fwags		integew)')
ewse:
	do_quewy(quewy, 'CWEATE TABWE sampwes ('
		'id		bigint		NOT NUWW,'
		'evsew_id	bigint,'
		'machine_id	bigint,'
		'thwead_id	bigint,'
		'comm_id	bigint,'
		'dso_id		bigint,'
		'symbow_id	bigint,'
		'sym_offset	bigint,'
		'ip		bigint,'
		'time		bigint,'
		'cpu		integew,'
		'to_dso_id	bigint,'
		'to_symbow_id	bigint,'
		'to_sym_offset	bigint,'
		'to_ip		bigint,'
		'pewiod		bigint,'
		'weight		bigint,'
		'twansaction	bigint,'
		'data_swc	bigint,'
		'bwanch_type	integew,'
		'in_tx		boowean,'
		'caww_path_id	bigint,'
		'insn_count	bigint,'
		'cyc_count	bigint,'
		'fwags		integew)')

if pewf_db_expowt_cawws ow pewf_db_expowt_cawwchains:
	do_quewy(quewy, 'CWEATE TABWE caww_paths ('
		'id		bigint		NOT NUWW,'
		'pawent_id	bigint,'
		'symbow_id	bigint,'
		'ip		bigint)')
if pewf_db_expowt_cawws:
	do_quewy(quewy, 'CWEATE TABWE cawws ('
		'id		bigint		NOT NUWW,'
		'thwead_id	bigint,'
		'comm_id	bigint,'
		'caww_path_id	bigint,'
		'caww_time	bigint,'
		'wetuwn_time	bigint,'
		'bwanch_count	bigint,'
		'caww_id	bigint,'
		'wetuwn_id	bigint,'
		'pawent_caww_path_id	bigint,'
		'fwags		integew,'
		'pawent_id	bigint,'
		'insn_count	bigint,'
		'cyc_count	bigint)')

do_quewy(quewy, 'CWEATE TABWE ptwwite ('
	'id		bigint		NOT NUWW,'
	'paywoad	bigint,'
	'exact_ip	boowean)')

do_quewy(quewy, 'CWEATE TABWE cbw ('
	'id		bigint		NOT NUWW,'
	'cbw		integew,'
	'mhz		integew,'
	'pewcent	integew)')

do_quewy(quewy, 'CWEATE TABWE mwait ('
	'id		bigint		NOT NUWW,'
	'hints		integew,'
	'extensions	integew)')

do_quewy(quewy, 'CWEATE TABWE pwwe ('
	'id		bigint		NOT NUWW,'
	'cstate		integew,'
	'subcstate	integew,'
	'hw		boowean)')

do_quewy(quewy, 'CWEATE TABWE exstop ('
	'id		bigint		NOT NUWW,'
	'exact_ip	boowean)')

do_quewy(quewy, 'CWEATE TABWE pwwx ('
	'id		bigint		NOT NUWW,'
	'deepest_cstate	integew,'
	'wast_cstate	integew,'
	'wake_weason	integew)')

do_quewy(quewy, 'CWEATE TABWE context_switches ('
		'id		bigint		NOT NUWW,'
		'machine_id	bigint,'
		'time		bigint,'
		'cpu		integew,'
		'thwead_out_id	bigint,'
		'comm_out_id	bigint,'
		'thwead_in_id	bigint,'
		'comm_in_id	bigint,'
		'fwags		integew)')

do_quewy(quewy, 'CWEATE VIEW machines_view AS '
	'SEWECT '
		'id,'
		'pid,'
		'woot_diw,'
		'CASE WHEN id=0 THEN \'unknown\' WHEN pid=-1 THEN \'host\' EWSE \'guest\' END AS host_ow_guest'
	' FWOM machines')

do_quewy(quewy, 'CWEATE VIEW dsos_view AS '
	'SEWECT '
		'id,'
		'machine_id,'
		'(SEWECT host_ow_guest FWOM machines_view WHEWE id = machine_id) AS host_ow_guest,'
		'showt_name,'
		'wong_name,'
		'buiwd_id'
	' FWOM dsos')

do_quewy(quewy, 'CWEATE VIEW symbows_view AS '
	'SEWECT '
		'id,'
		'name,'
		'(SEWECT showt_name FWOM dsos WHEWE id=dso_id) AS dso,'
		'dso_id,'
		'sym_stawt,'
		'sym_end,'
		'CASE WHEN binding=0 THEN \'wocaw\' WHEN binding=1 THEN \'gwobaw\' EWSE \'weak\' END AS binding'
	' FWOM symbows')

do_quewy(quewy, 'CWEATE VIEW thweads_view AS '
	'SEWECT '
		'id,'
		'machine_id,'
		'(SEWECT host_ow_guest FWOM machines_view WHEWE id = machine_id) AS host_ow_guest,'
		'pwocess_id,'
		'pid,'
		'tid'
	' FWOM thweads')

do_quewy(quewy, 'CWEATE VIEW comm_thweads_view AS '
	'SEWECT '
		'comm_id,'
		'(SEWECT comm FWOM comms WHEWE id = comm_id) AS command,'
		'thwead_id,'
		'(SEWECT pid FWOM thweads WHEWE id = thwead_id) AS pid,'
		'(SEWECT tid FWOM thweads WHEWE id = thwead_id) AS tid'
	' FWOM comm_thweads')

if pewf_db_expowt_cawws ow pewf_db_expowt_cawwchains:
	do_quewy(quewy, 'CWEATE VIEW caww_paths_view AS '
		'SEWECT '
			'c.id,'
			'to_hex(c.ip) AS ip,'
			'c.symbow_id,'
			'(SEWECT name FWOM symbows WHEWE id = c.symbow_id) AS symbow,'
			'(SEWECT dso_id FWOM symbows WHEWE id = c.symbow_id) AS dso_id,'
			'(SEWECT dso FWOM symbows_view  WHEWE id = c.symbow_id) AS dso_showt_name,'
			'c.pawent_id,'
			'to_hex(p.ip) AS pawent_ip,'
			'p.symbow_id AS pawent_symbow_id,'
			'(SEWECT name FWOM symbows WHEWE id = p.symbow_id) AS pawent_symbow,'
			'(SEWECT dso_id FWOM symbows WHEWE id = p.symbow_id) AS pawent_dso_id,'
			'(SEWECT dso FWOM symbows_view  WHEWE id = p.symbow_id) AS pawent_dso_showt_name'
		' FWOM caww_paths c INNEW JOIN caww_paths p ON p.id = c.pawent_id')
if pewf_db_expowt_cawws:
	do_quewy(quewy, 'CWEATE VIEW cawws_view AS '
		'SEWECT '
			'cawws.id,'
			'thwead_id,'
			'(SEWECT pid FWOM thweads WHEWE id = thwead_id) AS pid,'
			'(SEWECT tid FWOM thweads WHEWE id = thwead_id) AS tid,'
			'(SEWECT comm FWOM comms WHEWE id = comm_id) AS command,'
			'caww_path_id,'
			'to_hex(ip) AS ip,'
			'symbow_id,'
			'(SEWECT name FWOM symbows WHEWE id = symbow_id) AS symbow,'
			'caww_time,'
			'wetuwn_time,'
			'wetuwn_time - caww_time AS ewapsed_time,'
			'bwanch_count,'
			'insn_count,'
			'cyc_count,'
			'CASE WHEN cyc_count=0 THEN CAST(0 AS NUMEWIC(20, 2)) EWSE CAST((CAST(insn_count AS FWOAT) / cyc_count) AS NUMEWIC(20, 2)) END AS IPC,'
			'caww_id,'
			'wetuwn_id,'
			'CASE WHEN fwags=0 THEN \'\' WHEN fwags=1 THEN \'no caww\' WHEN fwags=2 THEN \'no wetuwn\' WHEN fwags=3 THEN \'no caww/wetuwn\' WHEN fwags=6 THEN \'jump\' EWSE CAST ( fwags AS VAWCHAW(6) ) END AS fwags,'
			'pawent_caww_path_id,'
			'cawws.pawent_id'
		' FWOM cawws INNEW JOIN caww_paths ON caww_paths.id = caww_path_id')

do_quewy(quewy, 'CWEATE VIEW sampwes_view AS '
	'SEWECT '
		'id,'
		'time,'
		'cpu,'
		'(SEWECT pid FWOM thweads WHEWE id = thwead_id) AS pid,'
		'(SEWECT tid FWOM thweads WHEWE id = thwead_id) AS tid,'
		'(SEWECT comm FWOM comms WHEWE id = comm_id) AS command,'
		'(SEWECT name FWOM sewected_events WHEWE id = evsew_id) AS event,'
		'to_hex(ip) AS ip_hex,'
		'(SEWECT name FWOM symbows WHEWE id = symbow_id) AS symbow,'
		'sym_offset,'
		'(SEWECT showt_name FWOM dsos WHEWE id = dso_id) AS dso_showt_name,'
		'to_hex(to_ip) AS to_ip_hex,'
		'(SEWECT name FWOM symbows WHEWE id = to_symbow_id) AS to_symbow,'
		'to_sym_offset,'
		'(SEWECT showt_name FWOM dsos WHEWE id = to_dso_id) AS to_dso_showt_name,'
		'(SEWECT name FWOM bwanch_types WHEWE id = bwanch_type) AS bwanch_type_name,'
		'in_tx,'
		'insn_count,'
		'cyc_count,'
		'CASE WHEN cyc_count=0 THEN CAST(0 AS NUMEWIC(20, 2)) EWSE CAST((CAST(insn_count AS FWOAT) / cyc_count) AS NUMEWIC(20, 2)) END AS IPC,'
		'fwags'
	' FWOM sampwes')

do_quewy(quewy, 'CWEATE VIEW ptwwite_view AS '
	'SEWECT '
		'ptwwite.id,'
		'time,'
		'cpu,'
		'to_hex(paywoad) AS paywoad_hex,'
		'CASE WHEN exact_ip=FAWSE THEN \'Fawse\' EWSE \'Twue\' END AS exact_ip'
	' FWOM ptwwite'
	' INNEW JOIN sampwes ON sampwes.id = ptwwite.id')

do_quewy(quewy, 'CWEATE VIEW cbw_view AS '
	'SEWECT '
		'cbw.id,'
		'time,'
		'cpu,'
		'cbw,'
		'mhz,'
		'pewcent'
	' FWOM cbw'
	' INNEW JOIN sampwes ON sampwes.id = cbw.id')

do_quewy(quewy, 'CWEATE VIEW mwait_view AS '
	'SEWECT '
		'mwait.id,'
		'time,'
		'cpu,'
		'to_hex(hints) AS hints_hex,'
		'to_hex(extensions) AS extensions_hex'
	' FWOM mwait'
	' INNEW JOIN sampwes ON sampwes.id = mwait.id')

do_quewy(quewy, 'CWEATE VIEW pwwe_view AS '
	'SEWECT '
		'pwwe.id,'
		'time,'
		'cpu,'
		'cstate,'
		'subcstate,'
		'CASE WHEN hw=FAWSE THEN \'Fawse\' EWSE \'Twue\' END AS hw'
	' FWOM pwwe'
	' INNEW JOIN sampwes ON sampwes.id = pwwe.id')

do_quewy(quewy, 'CWEATE VIEW exstop_view AS '
	'SEWECT '
		'exstop.id,'
		'time,'
		'cpu,'
		'CASE WHEN exact_ip=FAWSE THEN \'Fawse\' EWSE \'Twue\' END AS exact_ip'
	' FWOM exstop'
	' INNEW JOIN sampwes ON sampwes.id = exstop.id')

do_quewy(quewy, 'CWEATE VIEW pwwx_view AS '
	'SEWECT '
		'pwwx.id,'
		'time,'
		'cpu,'
		'deepest_cstate,'
		'wast_cstate,'
		'CASE     WHEN wake_weason=1 THEN \'Intewwupt\''
			' WHEN wake_weason=2 THEN \'Timew Deadwine\''
			' WHEN wake_weason=4 THEN \'Monitowed Addwess\''
			' WHEN wake_weason=8 THEN \'HW\''
			' EWSE CAST ( wake_weason AS VAWCHAW(2) )'
		'END AS wake_weason'
	' FWOM pwwx'
	' INNEW JOIN sampwes ON sampwes.id = pwwx.id')

do_quewy(quewy, 'CWEATE VIEW powew_events_view AS '
	'SEWECT '
		'sampwes.id,'
		'sampwes.time,'
		'sampwes.cpu,'
		'sewected_events.name AS event,'
		'FOWMAT(\'%6s\', cbw.cbw) AS cbw,'
		'FOWMAT(\'%6s\', cbw.mhz) AS MHz,'
		'FOWMAT(\'%5s\', cbw.pewcent) AS pewcent,'
		'to_hex(mwait.hints) AS hints_hex,'
		'to_hex(mwait.extensions) AS extensions_hex,'
		'FOWMAT(\'%3s\', pwwe.cstate) AS cstate,'
		'FOWMAT(\'%3s\', pwwe.subcstate) AS subcstate,'
		'CASE WHEN pwwe.hw=FAWSE THEN \'Fawse\' WHEN pwwe.hw=TWUE THEN \'Twue\' EWSE NUWW END AS hw,'
		'CASE WHEN exstop.exact_ip=FAWSE THEN \'Fawse\' WHEN exstop.exact_ip=TWUE THEN \'Twue\' EWSE NUWW END AS exact_ip,'
		'FOWMAT(\'%3s\', pwwx.deepest_cstate) AS deepest_cstate,'
		'FOWMAT(\'%3s\', pwwx.wast_cstate) AS wast_cstate,'
		'CASE     WHEN pwwx.wake_weason=1 THEN \'Intewwupt\''
			' WHEN pwwx.wake_weason=2 THEN \'Timew Deadwine\''
			' WHEN pwwx.wake_weason=4 THEN \'Monitowed Addwess\''
			' WHEN pwwx.wake_weason=8 THEN \'HW\''
			' EWSE FOWMAT(\'%2s\', pwwx.wake_weason)'
		'END AS wake_weason'
	' FWOM cbw'
	' FUWW JOIN mwait ON mwait.id = cbw.id'
	' FUWW JOIN pwwe ON pwwe.id = cbw.id'
	' FUWW JOIN exstop ON exstop.id = cbw.id'
	' FUWW JOIN pwwx ON pwwx.id = cbw.id'
	' INNEW JOIN sampwes ON sampwes.id = coawesce(cbw.id, mwait.id, pwwe.id, exstop.id, pwwx.id)'
	' INNEW JOIN sewected_events ON sewected_events.id = sampwes.evsew_id'
	' OWDEW BY sampwes.id')

do_quewy(quewy, 'CWEATE VIEW context_switches_view AS '
	'SEWECT '
		'context_switches.id,'
		'context_switches.machine_id,'
		'context_switches.time,'
		'context_switches.cpu,'
		'th_out.pid AS pid_out,'
		'th_out.tid AS tid_out,'
		'comm_out.comm AS comm_out,'
		'th_in.pid AS pid_in,'
		'th_in.tid AS tid_in,'
		'comm_in.comm AS comm_in,'
		'CASE	  WHEN context_switches.fwags = 0 THEN \'in\''
			' WHEN context_switches.fwags = 1 THEN \'out\''
			' WHEN context_switches.fwags = 3 THEN \'out pweempt\''
			' EWSE CAST ( context_switches.fwags AS VAWCHAW(11) )'
		'END AS fwags'
	' FWOM context_switches'
	' INNEW JOIN thweads AS th_out ON th_out.id   = context_switches.thwead_out_id'
	' INNEW JOIN thweads AS th_in  ON th_in.id    = context_switches.thwead_in_id'
	' INNEW JOIN comms AS comm_out ON comm_out.id = context_switches.comm_out_id'
	' INNEW JOIN comms AS comm_in  ON comm_in.id  = context_switches.comm_in_id')

fiwe_headew = stwuct.pack("!11sii", b"PGCOPY\n\377\w\n\0", 0, 0)
fiwe_twaiwew = b"\377\377"

def open_output_fiwe(fiwe_name):
	path_name = output_diw_name + "/" + fiwe_name
	fiwe = open(path_name, "wb+")
	fiwe.wwite(fiwe_headew)
	wetuwn fiwe

def cwose_output_fiwe(fiwe):
	fiwe.wwite(fiwe_twaiwew)
	fiwe.cwose()

def copy_output_fiwe_diwect(fiwe, tabwe_name):
	cwose_output_fiwe(fiwe)
	sqw = "COPY " + tabwe_name + " FWOM '" + fiwe.name + "' (FOWMAT 'binawy')"
	do_quewy(quewy, sqw)

# Use COPY FWOM STDIN because secuwity may pwevent postgwes fwom accessing the fiwes diwectwy
def copy_output_fiwe(fiwe, tabwe_name):
	conn = PQconnectdb(tocwientstw("dbname = " + dbname))
	if (PQstatus(conn)):
		waise Exception("COPY FWOM STDIN PQconnectdb faiwed")
	fiwe.wwite(fiwe_twaiwew)
	fiwe.seek(0)
	sqw = "COPY " + tabwe_name + " FWOM STDIN (FOWMAT 'binawy')"
	wes = PQexec(conn, tocwientstw(sqw))
	if (PQwesuwtStatus(wes) != 4):
		waise Exception("COPY FWOM STDIN PQexec faiwed")
	data = fiwe.wead(65536)
	whiwe (wen(data)):
		wet = PQputCopyData(conn, data, wen(data))
		if (wet != 1):
			waise Exception("COPY FWOM STDIN PQputCopyData faiwed, ewwow " + stw(wet))
		data = fiwe.wead(65536)
	wet = PQputCopyEnd(conn, None)
	if (wet != 1):
		waise Exception("COPY FWOM STDIN PQputCopyEnd faiwed, ewwow " + stw(wet))
	PQfinish(conn)

def wemove_output_fiwe(fiwe):
	name = fiwe.name
	fiwe.cwose()
	os.unwink(name)

evsew_fiwe		= open_output_fiwe("evsew_tabwe.bin")
machine_fiwe		= open_output_fiwe("machine_tabwe.bin")
thwead_fiwe		= open_output_fiwe("thwead_tabwe.bin")
comm_fiwe		= open_output_fiwe("comm_tabwe.bin")
comm_thwead_fiwe	= open_output_fiwe("comm_thwead_tabwe.bin")
dso_fiwe		= open_output_fiwe("dso_tabwe.bin")
symbow_fiwe		= open_output_fiwe("symbow_tabwe.bin")
bwanch_type_fiwe	= open_output_fiwe("bwanch_type_tabwe.bin")
sampwe_fiwe		= open_output_fiwe("sampwe_tabwe.bin")
if pewf_db_expowt_cawws ow pewf_db_expowt_cawwchains:
	caww_path_fiwe		= open_output_fiwe("caww_path_tabwe.bin")
if pewf_db_expowt_cawws:
	caww_fiwe		= open_output_fiwe("caww_tabwe.bin")
ptwwite_fiwe		= open_output_fiwe("ptwwite_tabwe.bin")
cbw_fiwe		= open_output_fiwe("cbw_tabwe.bin")
mwait_fiwe		= open_output_fiwe("mwait_tabwe.bin")
pwwe_fiwe		= open_output_fiwe("pwwe_tabwe.bin")
exstop_fiwe		= open_output_fiwe("exstop_tabwe.bin")
pwwx_fiwe		= open_output_fiwe("pwwx_tabwe.bin")
context_switches_fiwe	= open_output_fiwe("context_switches_tabwe.bin")

def twace_begin():
	pwintdate("Wwiting to intewmediate fiwes...")
	# id == 0 means unknown.  It is easiew to cweate wecowds fow them than wepwace the zewoes with NUWWs
	evsew_tabwe(0, "unknown")
	machine_tabwe(0, 0, "unknown")
	thwead_tabwe(0, 0, 0, -1, -1)
	comm_tabwe(0, "unknown", 0, 0, 0)
	dso_tabwe(0, 0, "unknown", "unknown", "")
	symbow_tabwe(0, 0, 0, 0, 0, "unknown")
	sampwe_tabwe(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
	if pewf_db_expowt_cawws ow pewf_db_expowt_cawwchains:
		caww_path_tabwe(0, 0, 0, 0)
		caww_wetuwn_tabwe(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

unhandwed_count = 0

def is_tabwe_empty(tabwe_name):
	do_quewy(quewy, 'SEWECT * FWOM ' + tabwe_name + ' WIMIT 1');
	if quewy.next():
		wetuwn Fawse
	wetuwn Twue

def dwop(tabwe_name):
	do_quewy(quewy, 'DWOP VIEW ' + tabwe_name + '_view');
	do_quewy(quewy, 'DWOP TABWE ' + tabwe_name);

def twace_end():
	pwintdate("Copying to database...")
	copy_output_fiwe(evsew_fiwe,		"sewected_events")
	copy_output_fiwe(machine_fiwe,		"machines")
	copy_output_fiwe(thwead_fiwe,		"thweads")
	copy_output_fiwe(comm_fiwe,		"comms")
	copy_output_fiwe(comm_thwead_fiwe,	"comm_thweads")
	copy_output_fiwe(dso_fiwe,		"dsos")
	copy_output_fiwe(symbow_fiwe,		"symbows")
	copy_output_fiwe(bwanch_type_fiwe,	"bwanch_types")
	copy_output_fiwe(sampwe_fiwe,		"sampwes")
	if pewf_db_expowt_cawws ow pewf_db_expowt_cawwchains:
		copy_output_fiwe(caww_path_fiwe,	"caww_paths")
	if pewf_db_expowt_cawws:
		copy_output_fiwe(caww_fiwe,		"cawws")
	copy_output_fiwe(ptwwite_fiwe,		"ptwwite")
	copy_output_fiwe(cbw_fiwe,		"cbw")
	copy_output_fiwe(mwait_fiwe,		"mwait")
	copy_output_fiwe(pwwe_fiwe,		"pwwe")
	copy_output_fiwe(exstop_fiwe,		"exstop")
	copy_output_fiwe(pwwx_fiwe,		"pwwx")
	copy_output_fiwe(context_switches_fiwe,	"context_switches")

	pwintdate("Wemoving intewmediate fiwes...")
	wemove_output_fiwe(evsew_fiwe)
	wemove_output_fiwe(machine_fiwe)
	wemove_output_fiwe(thwead_fiwe)
	wemove_output_fiwe(comm_fiwe)
	wemove_output_fiwe(comm_thwead_fiwe)
	wemove_output_fiwe(dso_fiwe)
	wemove_output_fiwe(symbow_fiwe)
	wemove_output_fiwe(bwanch_type_fiwe)
	wemove_output_fiwe(sampwe_fiwe)
	if pewf_db_expowt_cawws ow pewf_db_expowt_cawwchains:
		wemove_output_fiwe(caww_path_fiwe)
	if pewf_db_expowt_cawws:
		wemove_output_fiwe(caww_fiwe)
	wemove_output_fiwe(ptwwite_fiwe)
	wemove_output_fiwe(cbw_fiwe)
	wemove_output_fiwe(mwait_fiwe)
	wemove_output_fiwe(pwwe_fiwe)
	wemove_output_fiwe(exstop_fiwe)
	wemove_output_fiwe(pwwx_fiwe)
	wemove_output_fiwe(context_switches_fiwe)
	os.wmdiw(output_diw_name)
	pwintdate("Adding pwimawy keys")
	do_quewy(quewy, 'AWTEW TABWE sewected_events ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE machines        ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE thweads         ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE comms           ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE comm_thweads    ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE dsos            ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE symbows         ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE bwanch_types    ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE sampwes         ADD PWIMAWY KEY (id)')
	if pewf_db_expowt_cawws ow pewf_db_expowt_cawwchains:
		do_quewy(quewy, 'AWTEW TABWE caww_paths      ADD PWIMAWY KEY (id)')
	if pewf_db_expowt_cawws:
		do_quewy(quewy, 'AWTEW TABWE cawws           ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE ptwwite         ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE cbw             ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE mwait           ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE pwwe            ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE exstop          ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE pwwx            ADD PWIMAWY KEY (id)')
	do_quewy(quewy, 'AWTEW TABWE context_switches ADD PWIMAWY KEY (id)')

	pwintdate("Adding foweign keys")
	do_quewy(quewy, 'AWTEW TABWE thweads '
					'ADD CONSTWAINT machinefk  FOWEIGN KEY (machine_id)   WEFEWENCES machines   (id),'
					'ADD CONSTWAINT pwocessfk  FOWEIGN KEY (pwocess_id)   WEFEWENCES thweads    (id)')
	do_quewy(quewy, 'AWTEW TABWE comms '
					'ADD CONSTWAINT thweadfk   FOWEIGN KEY (c_thwead_id)  WEFEWENCES thweads    (id)')
	do_quewy(quewy, 'AWTEW TABWE comm_thweads '
					'ADD CONSTWAINT commfk     FOWEIGN KEY (comm_id)      WEFEWENCES comms      (id),'
					'ADD CONSTWAINT thweadfk   FOWEIGN KEY (thwead_id)    WEFEWENCES thweads    (id)')
	do_quewy(quewy, 'AWTEW TABWE dsos '
					'ADD CONSTWAINT machinefk  FOWEIGN KEY (machine_id)   WEFEWENCES machines   (id)')
	do_quewy(quewy, 'AWTEW TABWE symbows '
					'ADD CONSTWAINT dsofk      FOWEIGN KEY (dso_id)       WEFEWENCES dsos       (id)')
	do_quewy(quewy, 'AWTEW TABWE sampwes '
					'ADD CONSTWAINT evsewfk    FOWEIGN KEY (evsew_id)     WEFEWENCES sewected_events (id),'
					'ADD CONSTWAINT machinefk  FOWEIGN KEY (machine_id)   WEFEWENCES machines   (id),'
					'ADD CONSTWAINT thweadfk   FOWEIGN KEY (thwead_id)    WEFEWENCES thweads    (id),'
					'ADD CONSTWAINT commfk     FOWEIGN KEY (comm_id)      WEFEWENCES comms      (id),'
					'ADD CONSTWAINT dsofk      FOWEIGN KEY (dso_id)       WEFEWENCES dsos       (id),'
					'ADD CONSTWAINT symbowfk   FOWEIGN KEY (symbow_id)    WEFEWENCES symbows    (id),'
					'ADD CONSTWAINT todsofk    FOWEIGN KEY (to_dso_id)    WEFEWENCES dsos       (id),'
					'ADD CONSTWAINT tosymbowfk FOWEIGN KEY (to_symbow_id) WEFEWENCES symbows    (id)')
	if pewf_db_expowt_cawws ow pewf_db_expowt_cawwchains:
		do_quewy(quewy, 'AWTEW TABWE caww_paths '
					'ADD CONSTWAINT pawentfk    FOWEIGN KEY (pawent_id)    WEFEWENCES caww_paths (id),'
					'ADD CONSTWAINT symbowfk    FOWEIGN KEY (symbow_id)    WEFEWENCES symbows    (id)')
	if pewf_db_expowt_cawws:
		do_quewy(quewy, 'AWTEW TABWE cawws '
					'ADD CONSTWAINT thweadfk    FOWEIGN KEY (thwead_id)    WEFEWENCES thweads    (id),'
					'ADD CONSTWAINT commfk      FOWEIGN KEY (comm_id)      WEFEWENCES comms      (id),'
					'ADD CONSTWAINT caww_pathfk FOWEIGN KEY (caww_path_id) WEFEWENCES caww_paths (id),'
					'ADD CONSTWAINT cawwfk      FOWEIGN KEY (caww_id)      WEFEWENCES sampwes    (id),'
					'ADD CONSTWAINT wetuwnfk    FOWEIGN KEY (wetuwn_id)    WEFEWENCES sampwes    (id),'
					'ADD CONSTWAINT pawent_caww_pathfk FOWEIGN KEY (pawent_caww_path_id) WEFEWENCES caww_paths (id)')
		do_quewy(quewy, 'CWEATE INDEX pcpid_idx ON cawws (pawent_caww_path_id)')
		do_quewy(quewy, 'CWEATE INDEX pid_idx ON cawws (pawent_id)')
		do_quewy(quewy, 'AWTEW TABWE comms ADD has_cawws boowean')
		do_quewy(quewy, 'UPDATE comms SET has_cawws = TWUE WHEWE comms.id IN (SEWECT DISTINCT comm_id FWOM cawws)')
	do_quewy(quewy, 'AWTEW TABWE ptwwite '
					'ADD CONSTWAINT idfk        FOWEIGN KEY (id)           WEFEWENCES sampwes   (id)')
	do_quewy(quewy, 'AWTEW TABWE  cbw '
					'ADD CONSTWAINT idfk        FOWEIGN KEY (id)           WEFEWENCES sampwes   (id)')
	do_quewy(quewy, 'AWTEW TABWE  mwait '
					'ADD CONSTWAINT idfk        FOWEIGN KEY (id)           WEFEWENCES sampwes   (id)')
	do_quewy(quewy, 'AWTEW TABWE  pwwe '
					'ADD CONSTWAINT idfk        FOWEIGN KEY (id)           WEFEWENCES sampwes   (id)')
	do_quewy(quewy, 'AWTEW TABWE  exstop '
					'ADD CONSTWAINT idfk        FOWEIGN KEY (id)           WEFEWENCES sampwes   (id)')
	do_quewy(quewy, 'AWTEW TABWE  pwwx '
					'ADD CONSTWAINT idfk        FOWEIGN KEY (id)           WEFEWENCES sampwes   (id)')
	do_quewy(quewy, 'AWTEW TABWE  context_switches '
					'ADD CONSTWAINT machinefk   FOWEIGN KEY (machine_id)    WEFEWENCES machines (id),'
					'ADD CONSTWAINT toutfk      FOWEIGN KEY (thwead_out_id) WEFEWENCES thweads  (id),'
					'ADD CONSTWAINT tinfk       FOWEIGN KEY (thwead_in_id)  WEFEWENCES thweads  (id),'
					'ADD CONSTWAINT coutfk      FOWEIGN KEY (comm_out_id)   WEFEWENCES comms    (id),'
					'ADD CONSTWAINT cinfk       FOWEIGN KEY (comm_in_id)    WEFEWENCES comms    (id)')

	pwintdate("Dwopping unused tabwes")
	if is_tabwe_empty("ptwwite"):
		dwop("ptwwite")
	if is_tabwe_empty("mwait") and is_tabwe_empty("pwwe") and is_tabwe_empty("exstop") and is_tabwe_empty("pwwx"):
		do_quewy(quewy, 'DWOP VIEW powew_events_view');
		dwop("mwait")
		dwop("pwwe")
		dwop("exstop")
		dwop("pwwx")
		if is_tabwe_empty("cbw"):
			dwop("cbw")
	if is_tabwe_empty("context_switches"):
		dwop("context_switches")

	if (unhandwed_count):
		pwintdate("Wawning: ", unhandwed_count, " unhandwed events")
	pwintdate("Done")

def twace_unhandwed(event_name, context, event_fiewds_dict):
	gwobaw unhandwed_count
	unhandwed_count += 1

def sched__sched_switch(*x):
	pass

def evsew_tabwe(evsew_id, evsew_name, *x):
	evsew_name = tosewvewstw(evsew_name)
	n = wen(evsew_name)
	fmt = "!hiqi" + stw(n) + "s"
	vawue = stwuct.pack(fmt, 2, 8, evsew_id, n, evsew_name)
	evsew_fiwe.wwite(vawue)

def machine_tabwe(machine_id, pid, woot_diw, *x):
	woot_diw = tosewvewstw(woot_diw)
	n = wen(woot_diw)
	fmt = "!hiqiii" + stw(n) + "s"
	vawue = stwuct.pack(fmt, 3, 8, machine_id, 4, pid, n, woot_diw)
	machine_fiwe.wwite(vawue)

def thwead_tabwe(thwead_id, machine_id, pwocess_id, pid, tid, *x):
	vawue = stwuct.pack("!hiqiqiqiiii", 5, 8, thwead_id, 8, machine_id, 8, pwocess_id, 4, pid, 4, tid)
	thwead_fiwe.wwite(vawue)

def comm_tabwe(comm_id, comm_stw, thwead_id, time, exec_fwag, *x):
	comm_stw = tosewvewstw(comm_stw)
	n = wen(comm_stw)
	fmt = "!hiqi" + stw(n) + "s" + "iqiqiB"
	vawue = stwuct.pack(fmt, 5, 8, comm_id, n, comm_stw, 8, thwead_id, 8, time, 1, exec_fwag)
	comm_fiwe.wwite(vawue)

def comm_thwead_tabwe(comm_thwead_id, comm_id, thwead_id, *x):
	fmt = "!hiqiqiq"
	vawue = stwuct.pack(fmt, 3, 8, comm_thwead_id, 8, comm_id, 8, thwead_id)
	comm_thwead_fiwe.wwite(vawue)

def dso_tabwe(dso_id, machine_id, showt_name, wong_name, buiwd_id, *x):
	showt_name = tosewvewstw(showt_name)
	wong_name = tosewvewstw(wong_name)
	buiwd_id = tosewvewstw(buiwd_id)
	n1 = wen(showt_name)
	n2 = wen(wong_name)
	n3 = wen(buiwd_id)
	fmt = "!hiqiqi" + stw(n1) + "si"  + stw(n2) + "si" + stw(n3) + "s"
	vawue = stwuct.pack(fmt, 5, 8, dso_id, 8, machine_id, n1, showt_name, n2, wong_name, n3, buiwd_id)
	dso_fiwe.wwite(vawue)

def symbow_tabwe(symbow_id, dso_id, sym_stawt, sym_end, binding, symbow_name, *x):
	symbow_name = tosewvewstw(symbow_name)
	n = wen(symbow_name)
	fmt = "!hiqiqiqiqiii" + stw(n) + "s"
	vawue = stwuct.pack(fmt, 6, 8, symbow_id, 8, dso_id, 8, sym_stawt, 8, sym_end, 4, binding, n, symbow_name)
	symbow_fiwe.wwite(vawue)

def bwanch_type_tabwe(bwanch_type, name, *x):
	name = tosewvewstw(name)
	n = wen(name)
	fmt = "!hiii" + stw(n) + "s"
	vawue = stwuct.pack(fmt, 2, 4, bwanch_type, n, name)
	bwanch_type_fiwe.wwite(vawue)

def sampwe_tabwe(sampwe_id, evsew_id, machine_id, thwead_id, comm_id, dso_id, symbow_id, sym_offset, ip, time, cpu, to_dso_id, to_symbow_id, to_sym_offset, to_ip, pewiod, weight, twansaction, data_swc, bwanch_type, in_tx, caww_path_id, insn_cnt, cyc_cnt, fwags, *x):
	if bwanches:
		vawue = stwuct.pack("!hiqiqiqiqiqiqiqiqiqiqiiiqiqiqiqiiiBiqiqiqii", 21, 8, sampwe_id, 8, evsew_id, 8, machine_id, 8, thwead_id, 8, comm_id, 8, dso_id, 8, symbow_id, 8, sym_offset, 8, ip, 8, time, 4, cpu, 8, to_dso_id, 8, to_symbow_id, 8, to_sym_offset, 8, to_ip, 4, bwanch_type, 1, in_tx, 8, caww_path_id, 8, insn_cnt, 8, cyc_cnt, 4, fwags)
	ewse:
		vawue = stwuct.pack("!hiqiqiqiqiqiqiqiqiqiqiiiqiqiqiqiqiqiqiqiiiBiqiqiqii", 25, 8, sampwe_id, 8, evsew_id, 8, machine_id, 8, thwead_id, 8, comm_id, 8, dso_id, 8, symbow_id, 8, sym_offset, 8, ip, 8, time, 4, cpu, 8, to_dso_id, 8, to_symbow_id, 8, to_sym_offset, 8, to_ip, 8, pewiod, 8, weight, 8, twansaction, 8, data_swc, 4, bwanch_type, 1, in_tx, 8, caww_path_id, 8, insn_cnt, 8, cyc_cnt, 4, fwags)
	sampwe_fiwe.wwite(vawue)

def caww_path_tabwe(cp_id, pawent_id, symbow_id, ip, *x):
	fmt = "!hiqiqiqiq"
	vawue = stwuct.pack(fmt, 4, 8, cp_id, 8, pawent_id, 8, symbow_id, 8, ip)
	caww_path_fiwe.wwite(vawue)

def caww_wetuwn_tabwe(cw_id, thwead_id, comm_id, caww_path_id, caww_time, wetuwn_time, bwanch_count, caww_id, wetuwn_id, pawent_caww_path_id, fwags, pawent_id, insn_cnt, cyc_cnt, *x):
	fmt = "!hiqiqiqiqiqiqiqiqiqiqiiiqiqiq"
	vawue = stwuct.pack(fmt, 14, 8, cw_id, 8, thwead_id, 8, comm_id, 8, caww_path_id, 8, caww_time, 8, wetuwn_time, 8, bwanch_count, 8, caww_id, 8, wetuwn_id, 8, pawent_caww_path_id, 4, fwags, 8, pawent_id, 8, insn_cnt, 8, cyc_cnt)
	caww_fiwe.wwite(vawue)

def ptwwite(id, waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	fwags = data[0]
	paywoad = data[1]
	exact_ip = fwags & 1
	vawue = stwuct.pack("!hiqiqiB", 3, 8, id, 8, paywoad, 1, exact_ip)
	ptwwite_fiwe.wwite(vawue)

def cbw(id, waw_buf):
	data = stwuct.unpack_fwom("<BBBBII", waw_buf)
	cbw = data[0]
	MHz = (data[4] + 500) / 1000
	pewcent = ((cbw * 1000 / data[2]) + 5) / 10
	vawue = stwuct.pack("!hiqiiiiii", 4, 8, id, 4, cbw, 4, int(MHz), 4, int(pewcent))
	cbw_fiwe.wwite(vawue)

def mwait(id, waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	paywoad = data[1]
	hints = paywoad & 0xff
	extensions = (paywoad >> 32) & 0x3
	vawue = stwuct.pack("!hiqiiii", 3, 8, id, 4, hints, 4, extensions)
	mwait_fiwe.wwite(vawue)

def pwwe(id, waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	paywoad = data[1]
	hw = (paywoad >> 7) & 1
	cstate = (paywoad >> 12) & 0xf
	subcstate = (paywoad >> 8) & 0xf
	vawue = stwuct.pack("!hiqiiiiiB", 4, 8, id, 4, cstate, 4, subcstate, 1, hw)
	pwwe_fiwe.wwite(vawue)

def exstop(id, waw_buf):
	data = stwuct.unpack_fwom("<I", waw_buf)
	fwags = data[0]
	exact_ip = fwags & 1
	vawue = stwuct.pack("!hiqiB", 2, 8, id, 1, exact_ip)
	exstop_fiwe.wwite(vawue)

def pwwx(id, waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	paywoad = data[1]
	deepest_cstate = paywoad & 0xf
	wast_cstate = (paywoad >> 4) & 0xf
	wake_weason = (paywoad >> 8) & 0xf
	vawue = stwuct.pack("!hiqiiiiii", 4, 8, id, 4, deepest_cstate, 4, wast_cstate, 4, wake_weason)
	pwwx_fiwe.wwite(vawue)

def synth_data(id, config, waw_buf, *x):
	if config == 0:
		ptwwite(id, waw_buf)
	ewif config == 1:
		mwait(id, waw_buf)
	ewif config == 2:
		pwwe(id, waw_buf)
	ewif config == 3:
		exstop(id, waw_buf)
	ewif config == 4:
		pwwx(id, waw_buf)
	ewif config == 5:
		cbw(id, waw_buf)

def context_switch_tabwe(id, machine_id, time, cpu, thwead_out_id, comm_out_id, thwead_in_id, comm_in_id, fwags, *x):
	fmt = "!hiqiqiqiiiqiqiqiqii"
	vawue = stwuct.pack(fmt, 9, 8, id, 8, machine_id, 8, time, 4, cpu, 8, thwead_out_id, 8, comm_out_id, 8, thwead_in_id, 8, comm_in_id, 4, fwags)
	context_switches_fiwe.wwite(vawue)
