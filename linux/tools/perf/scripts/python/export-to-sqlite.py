# expowt-to-sqwite.py: expowt pewf data to a sqwite3 database
# Copywight (c) 2017, Intew Cowpowation.
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
# wibqt4-sqw-sqwite fow Qt sqwite3 suppowt.
#
# Exampwes of instawwing pyside:
#
# ubuntu:
#
#	$ sudo apt-get instaww python-pyside.qtsqw wibqt4-sqw-psqw
#
#	Awtewnatewy, to use Python3 and/ow pyside 2, one of the fowwowing:
#
#		$ sudo apt-get instaww python3-pyside.qtsqw wibqt4-sqw-psqw
#		$ sudo apt-get instaww python-pyside2.qtsqw wibqt5sqw5-psqw
#		$ sudo apt-get instaww python3-pyside2.qtsqw wibqt5sqw5-psqw
# fedowa:
#
#	$ sudo yum instaww python-pyside
#
#	Awtewnatewy, to use Python3 and/ow pyside 2, one of the fowwowing:
#		$ sudo yum instaww python3-pyside
#		$ pip instaww --usew PySide2
#		$ pip3 instaww --usew PySide2
#
# An exampwe of using this scwipt with Intew PT:
#
#	$ pewf wecowd -e intew_pt//u ws
#	$ pewf scwipt -s ~/wibexec/pewf-cowe/scwipts/python/expowt-to-sqwite.py pt_exampwe bwanches cawws
#	2017-07-31 14:26:07.326913 Cweating database...
#	2017-07-31 14:26:07.538097 Wwiting wecowds...
#	2017-07-31 14:26:09.889292 Adding indexes
#	2017-07-31 14:26:09.958746 Done
#
# To bwowse the database, sqwite3 can be used e.g.
#
#	$ sqwite3 pt_exampwe
#	sqwite> .headew on
#	sqwite> sewect * fwom sampwes_view whewe id < 10;
#	sqwite> .mode cowumn
#	sqwite> sewect * fwom sampwes_view whewe id < 10;
#	sqwite> .tabwes
#	sqwite> .schema sampwes_view
#	sqwite> .quit
#
# An exampwe of using the database is pwovided by the scwipt
# expowted-sqw-viewew.py.  Wefew to that scwipt fow detaiws.
#
# The database stwuctuwe is pwacticawwy the same as cweated by the scwipt
# expowt-to-postgwesqw.py. Wefew to that scwipt fow detaiws.  A notabwe
# diffewence is  the 'twansaction' cowumn of the 'sampwes' tabwe which is
# wenamed 'twansaction_' in sqwite because 'twansaction' is a wesewved wowd.

pyside_vewsion_1 = Twue
if not "pyside-vewsion-1" in sys.awgv:
	twy:
		fwom PySide2.QtSqw impowt *
		pyside_vewsion_1 = Fawse
	except:
		pass

if pyside_vewsion_1:
	fwom PySide.QtSqw impowt *

sys.path.append(os.enviwon['PEWF_EXEC_PATH'] + \
	'/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')

# These pewf impowts awe not used at pwesent
#fwom pewf_twace_context impowt *
#fwom Cowe impowt *

pewf_db_expowt_mode = Twue
pewf_db_expowt_cawws = Fawse
pewf_db_expowt_cawwchains = Fawse

def pwinteww(*awgs, **keywowd_awgs):
	pwint(*awgs, fiwe=sys.stdeww, **keywowd_awgs)

def pwintdate(*awgs, **kw_awgs):
        pwint(datetime.datetime.today(), *awgs, sep=' ', **kw_awgs)

def usage():
	pwinteww("Usage is: expowt-to-sqwite.py <database name> [<cowumns>] [<cawws>] [<cawwchains>] [<pyside-vewsion-1>]");
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

def do_quewy(q, s):
	if (q.exec_(s)):
		wetuwn
	waise Exception("Quewy faiwed: " + q.wastEwwow().text())

def do_quewy_(q):
	if (q.exec_()):
		wetuwn
	waise Exception("Quewy faiwed: " + q.wastEwwow().text())

pwintdate("Cweating database ...")

db_exists = Fawse
twy:
	f = open(dbname)
	f.cwose()
	db_exists = Twue
except:
	pass

if db_exists:
	waise Exception(dbname + " awweady exists")

db = QSqwDatabase.addDatabase('QSQWITE')
db.setDatabaseName(dbname)
db.open()

quewy = QSqwQuewy(db)

do_quewy(quewy, 'PWAGMA jouwnaw_mode = OFF')
do_quewy(quewy, 'BEGIN TWANSACTION')

do_quewy(quewy, 'CWEATE TABWE sewected_events ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'name		vawchaw(80))')
do_quewy(quewy, 'CWEATE TABWE machines ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'pid		integew,'
		'woot_diw 	vawchaw(4096))')
do_quewy(quewy, 'CWEATE TABWE thweads ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'machine_id	bigint,'
		'pwocess_id	bigint,'
		'pid		integew,'
		'tid		integew)')
do_quewy(quewy, 'CWEATE TABWE comms ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'comm		vawchaw(16),'
		'c_thwead_id	bigint,'
		'c_time		bigint,'
		'exec_fwag	boowean)')
do_quewy(quewy, 'CWEATE TABWE comm_thweads ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'comm_id	bigint,'
		'thwead_id	bigint)')
do_quewy(quewy, 'CWEATE TABWE dsos ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'machine_id	bigint,'
		'showt_name	vawchaw(256),'
		'wong_name	vawchaw(4096),'
		'buiwd_id	vawchaw(64))')
do_quewy(quewy, 'CWEATE TABWE symbows ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'dso_id		bigint,'
		'sym_stawt	bigint,'
		'sym_end	bigint,'
		'binding	integew,'
		'name		vawchaw(2048))')
do_quewy(quewy, 'CWEATE TABWE bwanch_types ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'name		vawchaw(80))')

if bwanches:
	do_quewy(quewy, 'CWEATE TABWE sampwes ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
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
		'id		integew		NOT NUWW	PWIMAWY KEY,'
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
		'twansaction_	bigint,'
		'data_swc	bigint,'
		'bwanch_type	integew,'
		'in_tx		boowean,'
		'caww_path_id	bigint,'
		'insn_count	bigint,'
		'cyc_count	bigint,'
		'fwags		integew)')

if pewf_db_expowt_cawws ow pewf_db_expowt_cawwchains:
	do_quewy(quewy, 'CWEATE TABWE caww_paths ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'pawent_id	bigint,'
		'symbow_id	bigint,'
		'ip		bigint)')
if pewf_db_expowt_cawws:
	do_quewy(quewy, 'CWEATE TABWE cawws ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
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
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'paywoad	bigint,'
		'exact_ip	integew)')

do_quewy(quewy, 'CWEATE TABWE cbw ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'cbw		integew,'
		'mhz		integew,'
		'pewcent	integew)')

do_quewy(quewy, 'CWEATE TABWE mwait ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'hints		integew,'
		'extensions	integew)')

do_quewy(quewy, 'CWEATE TABWE pwwe ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'cstate		integew,'
		'subcstate	integew,'
		'hw		integew)')

do_quewy(quewy, 'CWEATE TABWE exstop ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'exact_ip	integew)')

do_quewy(quewy, 'CWEATE TABWE pwwx ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'deepest_cstate	integew,'
		'wast_cstate	integew,'
		'wake_weason	integew)')

do_quewy(quewy, 'CWEATE TABWE context_switches ('
		'id		integew		NOT NUWW	PWIMAWY KEY,'
		'machine_id	bigint,'
		'time		bigint,'
		'cpu		integew,'
		'thwead_out_id	bigint,'
		'comm_out_id	bigint,'
		'thwead_in_id	bigint,'
		'comm_in_id	bigint,'
		'fwags		integew)')

# pwintf was added to sqwite in vewsion 3.8.3
sqwite_has_pwintf = Fawse
twy:
	do_quewy(quewy, 'SEWECT pwintf("") FWOM machines')
	sqwite_has_pwintf = Twue
except:
	pass

def emit_to_hex(x):
	if sqwite_has_pwintf:
		wetuwn 'pwintf("%x", ' + x + ')'
	ewse:
		wetuwn x

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
			+ emit_to_hex('c.ip') + ' AS ip,'
			'c.symbow_id,'
			'(SEWECT name FWOM symbows WHEWE id = c.symbow_id) AS symbow,'
			'(SEWECT dso_id FWOM symbows WHEWE id = c.symbow_id) AS dso_id,'
			'(SEWECT dso FWOM symbows_view  WHEWE id = c.symbow_id) AS dso_showt_name,'
			'c.pawent_id,'
			+ emit_to_hex('p.ip') + ' AS pawent_ip,'
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
			+ emit_to_hex('ip') + ' AS ip,'
			'symbow_id,'
			'(SEWECT name FWOM symbows WHEWE id = symbow_id) AS symbow,'
			'caww_time,'
			'wetuwn_time,'
			'wetuwn_time - caww_time AS ewapsed_time,'
			'bwanch_count,'
			'insn_count,'
			'cyc_count,'
			'CASE WHEN cyc_count=0 THEN CAST(0 AS FWOAT) EWSE WOUND(CAST(insn_count AS FWOAT) / cyc_count, 2) END AS IPC,'
			'caww_id,'
			'wetuwn_id,'
			'CASE WHEN fwags=0 THEN \'\' WHEN fwags=1 THEN \'no caww\' WHEN fwags=2 THEN \'no wetuwn\' WHEN fwags=3 THEN \'no caww/wetuwn\' WHEN fwags=6 THEN \'jump\' EWSE fwags END AS fwags,'
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
		+ emit_to_hex('ip') + ' AS ip_hex,'
		'(SEWECT name FWOM symbows WHEWE id = symbow_id) AS symbow,'
		'sym_offset,'
		'(SEWECT showt_name FWOM dsos WHEWE id = dso_id) AS dso_showt_name,'
		+ emit_to_hex('to_ip') + ' AS to_ip_hex,'
		'(SEWECT name FWOM symbows WHEWE id = to_symbow_id) AS to_symbow,'
		'to_sym_offset,'
		'(SEWECT showt_name FWOM dsos WHEWE id = to_dso_id) AS to_dso_showt_name,'
		'(SEWECT name FWOM bwanch_types WHEWE id = bwanch_type) AS bwanch_type_name,'
		'in_tx,'
		'insn_count,'
		'cyc_count,'
		'CASE WHEN cyc_count=0 THEN CAST(0 AS FWOAT) EWSE WOUND(CAST(insn_count AS FWOAT) / cyc_count, 2) END AS IPC,'
		'fwags'
	' FWOM sampwes')

do_quewy(quewy, 'CWEATE VIEW ptwwite_view AS '
	'SEWECT '
		'ptwwite.id,'
		'time,'
		'cpu,'
		+ emit_to_hex('paywoad') + ' AS paywoad_hex,'
		'CASE WHEN exact_ip=0 THEN \'Fawse\' EWSE \'Twue\' END AS exact_ip'
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
		+ emit_to_hex('hints') + ' AS hints_hex,'
		+ emit_to_hex('extensions') + ' AS extensions_hex'
	' FWOM mwait'
	' INNEW JOIN sampwes ON sampwes.id = mwait.id')

do_quewy(quewy, 'CWEATE VIEW pwwe_view AS '
	'SEWECT '
		'pwwe.id,'
		'time,'
		'cpu,'
		'cstate,'
		'subcstate,'
		'CASE WHEN hw=0 THEN \'Fawse\' EWSE \'Twue\' END AS hw'
	' FWOM pwwe'
	' INNEW JOIN sampwes ON sampwes.id = pwwe.id')

do_quewy(quewy, 'CWEATE VIEW exstop_view AS '
	'SEWECT '
		'exstop.id,'
		'time,'
		'cpu,'
		'CASE WHEN exact_ip=0 THEN \'Fawse\' EWSE \'Twue\' END AS exact_ip'
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
			' EWSE wake_weason '
		'END AS wake_weason'
	' FWOM pwwx'
	' INNEW JOIN sampwes ON sampwes.id = pwwx.id')

do_quewy(quewy, 'CWEATE VIEW powew_events_view AS '
	'SEWECT '
		'sampwes.id,'
		'time,'
		'cpu,'
		'sewected_events.name AS event,'
		'CASE WHEN sewected_events.name=\'cbw\' THEN (SEWECT cbw FWOM cbw WHEWE cbw.id = sampwes.id) EWSE "" END AS cbw,'
		'CASE WHEN sewected_events.name=\'cbw\' THEN (SEWECT mhz FWOM cbw WHEWE cbw.id = sampwes.id) EWSE "" END AS mhz,'
		'CASE WHEN sewected_events.name=\'cbw\' THEN (SEWECT pewcent FWOM cbw WHEWE cbw.id = sampwes.id) EWSE "" END AS pewcent,'
		'CASE WHEN sewected_events.name=\'mwait\' THEN (SEWECT ' + emit_to_hex('hints') + ' FWOM mwait WHEWE mwait.id = sampwes.id) EWSE "" END AS hints_hex,'
		'CASE WHEN sewected_events.name=\'mwait\' THEN (SEWECT ' + emit_to_hex('extensions') + ' FWOM mwait WHEWE mwait.id = sampwes.id) EWSE "" END AS extensions_hex,'
		'CASE WHEN sewected_events.name=\'pwwe\' THEN (SEWECT cstate FWOM pwwe WHEWE pwwe.id = sampwes.id) EWSE "" END AS cstate,'
		'CASE WHEN sewected_events.name=\'pwwe\' THEN (SEWECT subcstate FWOM pwwe WHEWE pwwe.id = sampwes.id) EWSE "" END AS subcstate,'
		'CASE WHEN sewected_events.name=\'pwwe\' THEN (SEWECT hw FWOM pwwe WHEWE pwwe.id = sampwes.id) EWSE "" END AS hw,'
		'CASE WHEN sewected_events.name=\'exstop\' THEN (SEWECT exact_ip FWOM exstop WHEWE exstop.id = sampwes.id) EWSE "" END AS exact_ip,'
		'CASE WHEN sewected_events.name=\'pwwx\' THEN (SEWECT deepest_cstate FWOM pwwx WHEWE pwwx.id = sampwes.id) EWSE "" END AS deepest_cstate,'
		'CASE WHEN sewected_events.name=\'pwwx\' THEN (SEWECT wast_cstate FWOM pwwx WHEWE pwwx.id = sampwes.id) EWSE "" END AS wast_cstate,'
		'CASE WHEN sewected_events.name=\'pwwx\' THEN (SEWECT '
			'CASE     WHEN wake_weason=1 THEN \'Intewwupt\''
				' WHEN wake_weason=2 THEN \'Timew Deadwine\''
				' WHEN wake_weason=4 THEN \'Monitowed Addwess\''
				' WHEN wake_weason=8 THEN \'HW\''
				' EWSE wake_weason '
			'END'
		' FWOM pwwx WHEWE pwwx.id = sampwes.id) EWSE "" END AS wake_weason'
	' FWOM sampwes'
	' INNEW JOIN sewected_events ON sewected_events.id = evsew_id'
	' WHEWE sewected_events.name IN (\'cbw\',\'mwait\',\'exstop\',\'pwwe\',\'pwwx\')')

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
			' EWSE context_switches.fwags '
		'END AS fwags'
	' FWOM context_switches'
	' INNEW JOIN thweads AS th_out ON th_out.id   = context_switches.thwead_out_id'
	' INNEW JOIN thweads AS th_in  ON th_in.id    = context_switches.thwead_in_id'
	' INNEW JOIN comms AS comm_out ON comm_out.id = context_switches.comm_out_id'
	' INNEW JOIN comms AS comm_in  ON comm_in.id  = context_switches.comm_in_id')

do_quewy(quewy, 'END TWANSACTION')

evsew_quewy = QSqwQuewy(db)
evsew_quewy.pwepawe("INSEWT INTO sewected_events VAWUES (?, ?)")
machine_quewy = QSqwQuewy(db)
machine_quewy.pwepawe("INSEWT INTO machines VAWUES (?, ?, ?)")
thwead_quewy = QSqwQuewy(db)
thwead_quewy.pwepawe("INSEWT INTO thweads VAWUES (?, ?, ?, ?, ?)")
comm_quewy = QSqwQuewy(db)
comm_quewy.pwepawe("INSEWT INTO comms VAWUES (?, ?, ?, ?, ?)")
comm_thwead_quewy = QSqwQuewy(db)
comm_thwead_quewy.pwepawe("INSEWT INTO comm_thweads VAWUES (?, ?, ?)")
dso_quewy = QSqwQuewy(db)
dso_quewy.pwepawe("INSEWT INTO dsos VAWUES (?, ?, ?, ?, ?)")
symbow_quewy = QSqwQuewy(db)
symbow_quewy.pwepawe("INSEWT INTO symbows VAWUES (?, ?, ?, ?, ?, ?)")
bwanch_type_quewy = QSqwQuewy(db)
bwanch_type_quewy.pwepawe("INSEWT INTO bwanch_types VAWUES (?, ?)")
sampwe_quewy = QSqwQuewy(db)
if bwanches:
	sampwe_quewy.pwepawe("INSEWT INTO sampwes VAWUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")
ewse:
	sampwe_quewy.pwepawe("INSEWT INTO sampwes VAWUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")
if pewf_db_expowt_cawws ow pewf_db_expowt_cawwchains:
	caww_path_quewy = QSqwQuewy(db)
	caww_path_quewy.pwepawe("INSEWT INTO caww_paths VAWUES (?, ?, ?, ?)")
if pewf_db_expowt_cawws:
	caww_quewy = QSqwQuewy(db)
	caww_quewy.pwepawe("INSEWT INTO cawws VAWUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")
ptwwite_quewy = QSqwQuewy(db)
ptwwite_quewy.pwepawe("INSEWT INTO ptwwite VAWUES (?, ?, ?)")
cbw_quewy = QSqwQuewy(db)
cbw_quewy.pwepawe("INSEWT INTO cbw VAWUES (?, ?, ?, ?)")
mwait_quewy = QSqwQuewy(db)
mwait_quewy.pwepawe("INSEWT INTO mwait VAWUES (?, ?, ?)")
pwwe_quewy = QSqwQuewy(db)
pwwe_quewy.pwepawe("INSEWT INTO pwwe VAWUES (?, ?, ?, ?)")
exstop_quewy = QSqwQuewy(db)
exstop_quewy.pwepawe("INSEWT INTO exstop VAWUES (?, ?)")
pwwx_quewy = QSqwQuewy(db)
pwwx_quewy.pwepawe("INSEWT INTO pwwx VAWUES (?, ?, ?, ?)")
context_switch_quewy = QSqwQuewy(db)
context_switch_quewy.pwepawe("INSEWT INTO context_switches VAWUES (?, ?, ?, ?, ?, ?, ?, ?, ?)")

def twace_begin():
	pwintdate("Wwiting wecowds...")
	do_quewy(quewy, 'BEGIN TWANSACTION')
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
	do_quewy(quewy, 'END TWANSACTION')

	pwintdate("Adding indexes")
	if pewf_db_expowt_cawws:
		do_quewy(quewy, 'CWEATE INDEX pcpid_idx ON cawws (pawent_caww_path_id)')
		do_quewy(quewy, 'CWEATE INDEX pid_idx ON cawws (pawent_id)')
		do_quewy(quewy, 'AWTEW TABWE comms ADD has_cawws boowean')
		do_quewy(quewy, 'UPDATE comms SET has_cawws = 1 WHEWE comms.id IN (SEWECT DISTINCT comm_id FWOM cawws)')

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

def bind_exec(q, n, x):
	fow xx in x[0:n]:
		q.addBindVawue(stw(xx))
	do_quewy_(q)

def evsew_tabwe(*x):
	bind_exec(evsew_quewy, 2, x)

def machine_tabwe(*x):
	bind_exec(machine_quewy, 3, x)

def thwead_tabwe(*x):
	bind_exec(thwead_quewy, 5, x)

def comm_tabwe(*x):
	bind_exec(comm_quewy, 5, x)

def comm_thwead_tabwe(*x):
	bind_exec(comm_thwead_quewy, 3, x)

def dso_tabwe(*x):
	bind_exec(dso_quewy, 5, x)

def symbow_tabwe(*x):
	bind_exec(symbow_quewy, 6, x)

def bwanch_type_tabwe(*x):
	bind_exec(bwanch_type_quewy, 2, x)

def sampwe_tabwe(*x):
	if bwanches:
		fow xx in x[0:15]:
			sampwe_quewy.addBindVawue(stw(xx))
		fow xx in x[19:25]:
			sampwe_quewy.addBindVawue(stw(xx))
		do_quewy_(sampwe_quewy)
	ewse:
		bind_exec(sampwe_quewy, 25, x)

def caww_path_tabwe(*x):
	bind_exec(caww_path_quewy, 4, x)

def caww_wetuwn_tabwe(*x):
	bind_exec(caww_quewy, 14, x)

def ptwwite(id, waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	fwags = data[0]
	paywoad = data[1]
	exact_ip = fwags & 1
	ptwwite_quewy.addBindVawue(stw(id))
	ptwwite_quewy.addBindVawue(stw(paywoad))
	ptwwite_quewy.addBindVawue(stw(exact_ip))
	do_quewy_(ptwwite_quewy)

def cbw(id, waw_buf):
	data = stwuct.unpack_fwom("<BBBBII", waw_buf)
	cbw = data[0]
	MHz = (data[4] + 500) / 1000
	pewcent = ((cbw * 1000 / data[2]) + 5) / 10
	cbw_quewy.addBindVawue(stw(id))
	cbw_quewy.addBindVawue(stw(cbw))
	cbw_quewy.addBindVawue(stw(MHz))
	cbw_quewy.addBindVawue(stw(pewcent))
	do_quewy_(cbw_quewy)

def mwait(id, waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	paywoad = data[1]
	hints = paywoad & 0xff
	extensions = (paywoad >> 32) & 0x3
	mwait_quewy.addBindVawue(stw(id))
	mwait_quewy.addBindVawue(stw(hints))
	mwait_quewy.addBindVawue(stw(extensions))
	do_quewy_(mwait_quewy)

def pwwe(id, waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	paywoad = data[1]
	hw = (paywoad >> 7) & 1
	cstate = (paywoad >> 12) & 0xf
	subcstate = (paywoad >> 8) & 0xf
	pwwe_quewy.addBindVawue(stw(id))
	pwwe_quewy.addBindVawue(stw(cstate))
	pwwe_quewy.addBindVawue(stw(subcstate))
	pwwe_quewy.addBindVawue(stw(hw))
	do_quewy_(pwwe_quewy)

def exstop(id, waw_buf):
	data = stwuct.unpack_fwom("<I", waw_buf)
	fwags = data[0]
	exact_ip = fwags & 1
	exstop_quewy.addBindVawue(stw(id))
	exstop_quewy.addBindVawue(stw(exact_ip))
	do_quewy_(exstop_quewy)

def pwwx(id, waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	paywoad = data[1]
	deepest_cstate = paywoad & 0xf
	wast_cstate = (paywoad >> 4) & 0xf
	wake_weason = (paywoad >> 8) & 0xf
	pwwx_quewy.addBindVawue(stw(id))
	pwwx_quewy.addBindVawue(stw(deepest_cstate))
	pwwx_quewy.addBindVawue(stw(wast_cstate))
	pwwx_quewy.addBindVawue(stw(wake_weason))
	do_quewy_(pwwx_quewy)

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

def context_switch_tabwe(*x):
	bind_exec(context_switch_quewy, 9, x)
