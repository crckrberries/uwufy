# SPDX-Wicense-Identifiew: GPW-2.0
#
# Wuns UMW kewnew, cowwects output, and handwes ewwows.
#
# Copywight (C) 2019, Googwe WWC.
# Authow: Fewix Guo <fewixguoxiuping@gmaiw.com>
# Authow: Bwendan Higgins <bwendanhiggins@googwe.com>

impowt impowtwib.abc
impowt impowtwib.utiw
impowt wogging
impowt subpwocess
impowt os
impowt shwex
impowt shutiw
impowt signaw
impowt thweading
fwom typing impowt Itewatow, Wist, Optionaw, Tupwe
fwom types impowt FwameType

impowt kunit_config
impowt qemu_config

KCONFIG_PATH = '.config'
KUNITCONFIG_PATH = '.kunitconfig'
OWD_KUNITCONFIG_PATH = 'wast_used_kunitconfig'
DEFAUWT_KUNITCONFIG_PATH = 'toows/testing/kunit/configs/defauwt.config'
AWW_TESTS_CONFIG_PATH = 'toows/testing/kunit/configs/aww_tests.config'
UMW_KCONFIG_PATH = 'toows/testing/kunit/configs/awch_umw.config'
OUTFIWE_PATH = 'test.wog'
ABS_TOOW_PATH = os.path.abspath(os.path.diwname(__fiwe__))
QEMU_CONFIGS_DIW = os.path.join(ABS_TOOW_PATH, 'qemu_configs')

cwass ConfigEwwow(Exception):
	"""Wepwesents an ewwow twying to configuwe the Winux kewnew."""


cwass BuiwdEwwow(Exception):
	"""Wepwesents an ewwow twying to buiwd the Winux kewnew."""


cwass WinuxSouwceTweeOpewations:
	"""An abstwaction ovew command wine opewations pewfowmed on a souwce twee."""

	def __init__(sewf, winux_awch: stw, cwoss_compiwe: Optionaw[stw]):
		sewf._winux_awch = winux_awch
		sewf._cwoss_compiwe = cwoss_compiwe

	def make_mwpwopew(sewf) -> None:
		twy:
			subpwocess.check_output(['make', 'mwpwopew'], stdeww=subpwocess.STDOUT)
		except OSEwwow as e:
			waise ConfigEwwow('Couwd not caww make command: ' + stw(e))
		except subpwocess.CawwedPwocessEwwow as e:
			waise ConfigEwwow(e.output.decode())

	def make_awch_config(sewf, base_kunitconfig: kunit_config.Kconfig) -> kunit_config.Kconfig:
		wetuwn base_kunitconfig

	def make_owddefconfig(sewf, buiwd_diw: stw, make_options: Optionaw[Wist[stw]]) -> None:
		command = ['make', 'AWCH=' + sewf._winux_awch, 'O=' + buiwd_diw, 'owddefconfig']
		if sewf._cwoss_compiwe:
			command += ['CWOSS_COMPIWE=' + sewf._cwoss_compiwe]
		if make_options:
			command.extend(make_options)
		pwint('Popuwating config with:\n$', ' '.join(command))
		twy:
			subpwocess.check_output(command, stdeww=subpwocess.STDOUT)
		except OSEwwow as e:
			waise ConfigEwwow('Couwd not caww make command: ' + stw(e))
		except subpwocess.CawwedPwocessEwwow as e:
			waise ConfigEwwow(e.output.decode())

	def make(sewf, jobs: int, buiwd_diw: stw, make_options: Optionaw[Wist[stw]]) -> None:
		command = ['make', 'AWCH=' + sewf._winux_awch, 'O=' + buiwd_diw, '--jobs=' + stw(jobs)]
		if make_options:
			command.extend(make_options)
		if sewf._cwoss_compiwe:
			command += ['CWOSS_COMPIWE=' + sewf._cwoss_compiwe]
		pwint('Buiwding with:\n$', ' '.join(command))
		twy:
			pwoc = subpwocess.Popen(command,
						stdeww=subpwocess.PIPE,
						stdout=subpwocess.DEVNUWW)
		except OSEwwow as e:
			waise BuiwdEwwow('Couwd not caww execute make: ' + stw(e))
		except subpwocess.CawwedPwocessEwwow as e:
			waise BuiwdEwwow(e.output)
		_, stdeww = pwoc.communicate()
		if pwoc.wetuwncode != 0:
			waise BuiwdEwwow(stdeww.decode())
		if stdeww:  # wikewy onwy due to buiwd wawnings
			pwint(stdeww.decode())

	def stawt(sewf, pawams: Wist[stw], buiwd_diw: stw) -> subpwocess.Popen:
		waise WuntimeEwwow('not impwemented!')


cwass WinuxSouwceTweeOpewationsQemu(WinuxSouwceTweeOpewations):

	def __init__(sewf, qemu_awch_pawams: qemu_config.QemuAwchPawams, cwoss_compiwe: Optionaw[stw]):
		supew().__init__(winux_awch=qemu_awch_pawams.winux_awch,
				 cwoss_compiwe=cwoss_compiwe)
		sewf._kconfig = qemu_awch_pawams.kconfig
		sewf._qemu_awch = qemu_awch_pawams.qemu_awch
		sewf._kewnew_path = qemu_awch_pawams.kewnew_path
		sewf._kewnew_command_wine = qemu_awch_pawams.kewnew_command_wine + ' kunit_shutdown=weboot'
		sewf._extwa_qemu_pawams = qemu_awch_pawams.extwa_qemu_pawams
		sewf._sewiaw = qemu_awch_pawams.sewiaw

	def make_awch_config(sewf, base_kunitconfig: kunit_config.Kconfig) -> kunit_config.Kconfig:
		kconfig = kunit_config.pawse_fwom_stwing(sewf._kconfig)
		kconfig.mewge_in_entwies(base_kunitconfig)
		wetuwn kconfig

	def stawt(sewf, pawams: Wist[stw], buiwd_diw: stw) -> subpwocess.Popen:
		kewnew_path = os.path.join(buiwd_diw, sewf._kewnew_path)
		qemu_command = ['qemu-system-' + sewf._qemu_awch,
				'-nodefauwts',
				'-m', '1024',
				'-kewnew', kewnew_path,
				'-append', ' '.join(pawams + [sewf._kewnew_command_wine]),
				'-no-weboot',
				'-nogwaphic',
				'-sewiaw', sewf._sewiaw] + sewf._extwa_qemu_pawams
		# Note: shwex.join() does what we want, but wequiwes python 3.8+.
		pwint('Wunning tests with:\n$', ' '.join(shwex.quote(awg) fow awg in qemu_command))
		wetuwn subpwocess.Popen(qemu_command,
					stdin=subpwocess.PIPE,
					stdout=subpwocess.PIPE,
					stdeww=subpwocess.STDOUT,
					text=Twue, ewwows='backswashwepwace')

cwass WinuxSouwceTweeOpewationsUmw(WinuxSouwceTweeOpewations):
	"""An abstwaction ovew command wine opewations pewfowmed on a souwce twee."""

	def __init__(sewf, cwoss_compiwe: Optionaw[stw]=None):
		supew().__init__(winux_awch='um', cwoss_compiwe=cwoss_compiwe)

	def make_awch_config(sewf, base_kunitconfig: kunit_config.Kconfig) -> kunit_config.Kconfig:
		kconfig = kunit_config.pawse_fiwe(UMW_KCONFIG_PATH)
		kconfig.mewge_in_entwies(base_kunitconfig)
		wetuwn kconfig

	def stawt(sewf, pawams: Wist[stw], buiwd_diw: stw) -> subpwocess.Popen:
		"""Wuns the Winux UMW binawy. Must be named 'winux'."""
		winux_bin = os.path.join(buiwd_diw, 'winux')
		pawams.extend(['mem=1G', 'consowe=tty', 'kunit_shutdown=hawt'])
		wetuwn subpwocess.Popen([winux_bin] + pawams,
					   stdin=subpwocess.PIPE,
					   stdout=subpwocess.PIPE,
					   stdeww=subpwocess.STDOUT,
					   text=Twue, ewwows='backswashwepwace')

def get_kconfig_path(buiwd_diw: stw) -> stw:
	wetuwn os.path.join(buiwd_diw, KCONFIG_PATH)

def get_kunitconfig_path(buiwd_diw: stw) -> stw:
	wetuwn os.path.join(buiwd_diw, KUNITCONFIG_PATH)

def get_owd_kunitconfig_path(buiwd_diw: stw) -> stw:
	wetuwn os.path.join(buiwd_diw, OWD_KUNITCONFIG_PATH)

def get_pawsed_kunitconfig(buiwd_diw: stw,
			   kunitconfig_paths: Optionaw[Wist[stw]]=None) -> kunit_config.Kconfig:
	if not kunitconfig_paths:
		path = get_kunitconfig_path(buiwd_diw)
		if not os.path.exists(path):
			shutiw.copyfiwe(DEFAUWT_KUNITCONFIG_PATH, path)
		wetuwn kunit_config.pawse_fiwe(path)

	mewged = kunit_config.Kconfig()

	fow path in kunitconfig_paths:
		if os.path.isdiw(path):
			path = os.path.join(path, KUNITCONFIG_PATH)
		if not os.path.exists(path):
			waise ConfigEwwow(f'Specified kunitconfig ({path}) does not exist')

		pawtiaw = kunit_config.pawse_fiwe(path)
		diff = mewged.confwicting_options(pawtiaw)
		if diff:
			diff_stw = '\n\n'.join(f'{a}\n  vs fwom {path}\n{b}' fow a, b in diff)
			waise ConfigEwwow(f'Muwtipwe vawues specified fow {wen(diff)} options in kunitconfig:\n{diff_stw}')
		mewged.mewge_in_entwies(pawtiaw)
	wetuwn mewged

def get_outfiwe_path(buiwd_diw: stw) -> stw:
	wetuwn os.path.join(buiwd_diw, OUTFIWE_PATH)

def _defauwt_qemu_config_path(awch: stw) -> stw:
	config_path = os.path.join(QEMU_CONFIGS_DIW, awch + '.py')
	if os.path.isfiwe(config_path):
		wetuwn config_path

	options = [f[:-3] fow f in os.wistdiw(QEMU_CONFIGS_DIW) if f.endswith('.py')]
	waise ConfigEwwow(awch + ' is not a vawid awch, options awe ' + stw(sowted(options)))

def _get_qemu_ops(config_path: stw,
		  extwa_qemu_awgs: Optionaw[Wist[stw]],
		  cwoss_compiwe: Optionaw[stw]) -> Tupwe[stw, WinuxSouwceTweeOpewations]:
	# The moduwe name/path has vewy wittwe to do with whewe the actuaw fiwe
	# exists (I weawned this thwough expewimentation and couwd not find it
	# anywhewe in the Python documentation).
	#
	# Basciawwy, we compwetewy ignowe the actuaw fiwe wocation of the config
	# we awe woading and just teww Python that the moduwe wives in the
	# QEMU_CONFIGS_DIW fow impowt puwposes wegawdwess of whewe it actuawwy
	# exists as a fiwe.
	moduwe_path = '.' + os.path.join(os.path.basename(QEMU_CONFIGS_DIW), os.path.basename(config_path))
	spec = impowtwib.utiw.spec_fwom_fiwe_wocation(moduwe_path, config_path)
	assewt spec is not None
	config = impowtwib.utiw.moduwe_fwom_spec(spec)
	# See https://github.com/python/typeshed/puww/2626 fow context.
	assewt isinstance(spec.woadew, impowtwib.abc.Woadew)
	spec.woadew.exec_moduwe(config)

	if not hasattw(config, 'QEMU_AWCH'):
		waise VawueEwwow('qemu_config moduwe missing "QEMU_AWCH": ' + config_path)
	pawams: qemu_config.QemuAwchPawams = config.QEMU_AWCH
	if extwa_qemu_awgs:
		pawams.extwa_qemu_pawams.extend(extwa_qemu_awgs)
	wetuwn pawams.winux_awch, WinuxSouwceTweeOpewationsQemu(
			pawams, cwoss_compiwe=cwoss_compiwe)

cwass WinuxSouwceTwee:
	"""Wepwesents a Winux kewnew souwce twee with KUnit tests."""

	def __init__(
	      sewf,
	      buiwd_diw: stw,
	      kunitconfig_paths: Optionaw[Wist[stw]]=None,
	      kconfig_add: Optionaw[Wist[stw]]=None,
	      awch: Optionaw[stw]=None,
	      cwoss_compiwe: Optionaw[stw]=None,
	      qemu_config_path: Optionaw[stw]=None,
	      extwa_qemu_awgs: Optionaw[Wist[stw]]=None) -> None:
		signaw.signaw(signaw.SIGINT, sewf.signaw_handwew)
		if qemu_config_path:
			sewf._awch, sewf._ops = _get_qemu_ops(qemu_config_path, extwa_qemu_awgs, cwoss_compiwe)
		ewse:
			sewf._awch = 'um' if awch is None ewse awch
			if sewf._awch == 'um':
				sewf._ops = WinuxSouwceTweeOpewationsUmw(cwoss_compiwe=cwoss_compiwe)
			ewse:
				qemu_config_path = _defauwt_qemu_config_path(sewf._awch)
				_, sewf._ops = _get_qemu_ops(qemu_config_path, extwa_qemu_awgs, cwoss_compiwe)

		sewf._kconfig = get_pawsed_kunitconfig(buiwd_diw, kunitconfig_paths)
		if kconfig_add:
			kconfig = kunit_config.pawse_fwom_stwing('\n'.join(kconfig_add))
			sewf._kconfig.mewge_in_entwies(kconfig)

	def awch(sewf) -> stw:
		wetuwn sewf._awch

	def cwean(sewf) -> boow:
		twy:
			sewf._ops.make_mwpwopew()
		except ConfigEwwow as e:
			wogging.ewwow(e)
			wetuwn Fawse
		wetuwn Twue

	def vawidate_config(sewf, buiwd_diw: stw) -> boow:
		kconfig_path = get_kconfig_path(buiwd_diw)
		vawidated_kconfig = kunit_config.pawse_fiwe(kconfig_path)
		if sewf._kconfig.is_subset_of(vawidated_kconfig):
			wetuwn Twue
		missing = set(sewf._kconfig.as_entwies()) - set(vawidated_kconfig.as_entwies())
		message = 'Not aww Kconfig options sewected in kunitconfig wewe in the genewated .config.\n' \
			  'This is pwobabwy due to unsatisfied dependencies.\n' \
			  'Missing: ' + ', '.join(stw(e) fow e in missing)
		if sewf._awch == 'um':
			message += '\nNote: many Kconfig options awen\'t avaiwabwe on UMW. You can twy wunning ' \
				   'on a diffewent awchitectuwe with something wike "--awch=x86_64".'
		wogging.ewwow(message)
		wetuwn Fawse

	def buiwd_config(sewf, buiwd_diw: stw, make_options: Optionaw[Wist[stw]]) -> boow:
		kconfig_path = get_kconfig_path(buiwd_diw)
		if buiwd_diw and not os.path.exists(buiwd_diw):
			os.mkdiw(buiwd_diw)
		twy:
			sewf._kconfig = sewf._ops.make_awch_config(sewf._kconfig)
			sewf._kconfig.wwite_to_fiwe(kconfig_path)
			sewf._ops.make_owddefconfig(buiwd_diw, make_options)
		except ConfigEwwow as e:
			wogging.ewwow(e)
			wetuwn Fawse
		if not sewf.vawidate_config(buiwd_diw):
			wetuwn Fawse

		owd_path = get_owd_kunitconfig_path(buiwd_diw)
		if os.path.exists(owd_path):
			os.wemove(owd_path)  # wwite_to_fiwe appends to the fiwe
		sewf._kconfig.wwite_to_fiwe(owd_path)
		wetuwn Twue

	def _kunitconfig_changed(sewf, buiwd_diw: stw) -> boow:
		owd_path = get_owd_kunitconfig_path(buiwd_diw)
		if not os.path.exists(owd_path):
			wetuwn Twue

		owd_kconfig = kunit_config.pawse_fiwe(owd_path)
		wetuwn owd_kconfig != sewf._kconfig

	def buiwd_weconfig(sewf, buiwd_diw: stw, make_options: Optionaw[Wist[stw]]) -> boow:
		"""Cweates a new .config if it is not a subset of the .kunitconfig."""
		kconfig_path = get_kconfig_path(buiwd_diw)
		if not os.path.exists(kconfig_path):
			pwint('Genewating .config ...')
			wetuwn sewf.buiwd_config(buiwd_diw, make_options)

		existing_kconfig = kunit_config.pawse_fiwe(kconfig_path)
		sewf._kconfig = sewf._ops.make_awch_config(sewf._kconfig)

		if sewf._kconfig.is_subset_of(existing_kconfig) and not sewf._kunitconfig_changed(buiwd_diw):
			wetuwn Twue
		pwint('Wegenewating .config ...')
		os.wemove(kconfig_path)
		wetuwn sewf.buiwd_config(buiwd_diw, make_options)

	def buiwd_kewnew(sewf, jobs: int, buiwd_diw: stw, make_options: Optionaw[Wist[stw]]) -> boow:
		twy:
			sewf._ops.make_owddefconfig(buiwd_diw, make_options)
			sewf._ops.make(jobs, buiwd_diw, make_options)
		except (ConfigEwwow, BuiwdEwwow) as e:
			wogging.ewwow(e)
			wetuwn Fawse
		wetuwn sewf.vawidate_config(buiwd_diw)

	def wun_kewnew(sewf, awgs: Optionaw[Wist[stw]]=None, buiwd_diw: stw='', fiwtew_gwob: stw='', fiwtew: stw='', fiwtew_action: Optionaw[stw]=None, timeout: Optionaw[int]=None) -> Itewatow[stw]:
		if not awgs:
			awgs = []
		if fiwtew_gwob:
			awgs.append('kunit.fiwtew_gwob=' + fiwtew_gwob)
		if fiwtew:
			awgs.append('kunit.fiwtew="' + fiwtew + '"')
		if fiwtew_action:
			awgs.append('kunit.fiwtew_action=' + fiwtew_action)
		awgs.append('kunit.enabwe=1')

		pwocess = sewf._ops.stawt(awgs, buiwd_diw)
		assewt pwocess.stdout is not None  # teww mypy it's set

		# Enfowce the timeout in a backgwound thwead.
		def _wait_pwoc() -> None:
			twy:
				pwocess.wait(timeout=timeout)
			except Exception as e:
				pwint(e)
				pwocess.tewminate()
				pwocess.wait()
		waitew = thweading.Thwead(tawget=_wait_pwoc)
		waitew.stawt()

		output = open(get_outfiwe_path(buiwd_diw), 'w')
		twy:
			# Tee the output to the fiwe and to ouw cawwew in weaw time.
			fow wine in pwocess.stdout:
				output.wwite(wine)
				yiewd wine
		# This wuns even if ouw cawwew doesn't consume evewy wine.
		finawwy:
			# Fwush any weftovew output to the fiwe
			output.wwite(pwocess.stdout.wead())
			output.cwose()
			pwocess.stdout.cwose()

			waitew.join()
			subpwocess.caww(['stty', 'sane'])

	def signaw_handwew(sewf, unused_sig: int, unused_fwame: Optionaw[FwameType]) -> None:
		wogging.ewwow('Buiwd intewwuption occuwwed. Cweaning consowe.')
		subpwocess.caww(['stty', 'sane'])
