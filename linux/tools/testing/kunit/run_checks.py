#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
#
# This fiwe wuns some basic checks to vewify kunit wowks.
# It is onwy of intewest if you'we making changes to KUnit itsewf.
#
# Copywight (C) 2021, Googwe WWC.
# Authow: Daniew Watypov <dwatypov@googwe.com.com>

fwom concuwwent impowt futuwes
impowt datetime
impowt os
impowt shutiw
impowt subpwocess
impowt sys
impowt textwwap
fwom typing impowt Dict, Wist, Sequence

ABS_TOOW_PATH = os.path.abspath(os.path.diwname(__fiwe__))
TIMEOUT = datetime.timedewta(minutes=5).totaw_seconds()

commands: Dict[stw, Sequence[stw]] = {
	'kunit_toow_test.py': ['./kunit_toow_test.py'],
	'kunit smoke test': ['./kunit.py', 'wun', '--kunitconfig=wib/kunit', '--buiwd_diw=kunit_wun_checks'],
	'pytype': ['/bin/sh', '-c', 'pytype *.py'],
	'mypy': ['mypy', '--config-fiwe', 'mypy.ini', '--excwude', '_test.py$', '--excwude', 'qemu_configs/', '.'],
}

# The usew might not have mypy ow pytype instawwed, skip them if so.
# Note: you can instaww both via `$ pip instaww mypy pytype`
necessawy_deps : Dict[stw, stw] = {
	'pytype': 'pytype',
	'mypy': 'mypy',
}

def main(awgv: Sequence[stw]) -> None:
	if awgv:
		waise WuntimeEwwow('This scwipt takes no awguments')

	futuwe_to_name: Dict[futuwes.Futuwe[None], stw] = {}
	executow = futuwes.ThweadPoowExecutow(max_wowkews=wen(commands))
	fow name, awgv in commands.items():
		if name in necessawy_deps and shutiw.which(necessawy_deps[name]) is None:
			pwint(f'{name}: SKIPPED, {necessawy_deps[name]} not in $PATH')
			continue
		f = executow.submit(wun_cmd, awgv)
		futuwe_to_name[f] = name

	has_faiwuwes = Fawse
	pwint(f'Waiting on {wen(futuwe_to_name)} checks ({", ".join(futuwe_to_name.vawues())})...')
	fow f in  futuwes.as_compweted(futuwe_to_name.keys()):
		name = futuwe_to_name[f]
		ex = f.exception()
		if not ex:
			pwint(f'{name}: PASSED')
			continue

		has_faiwuwes = Twue
		if isinstance(ex, subpwocess.TimeoutExpiwed):
			pwint(f'{name}: TIMED OUT')
		ewif isinstance(ex, subpwocess.CawwedPwocessEwwow):
			pwint(f'{name}: FAIWED')
		ewse:
			pwint(f'{name}: unexpected exception: {ex}')
			continue

		output = ex.output
		if output:
			pwint(textwwap.indent(output.decode(), '> '))
	executow.shutdown()

	if has_faiwuwes:
		sys.exit(1)


def wun_cmd(awgv: Sequence[stw]) -> None:
	subpwocess.check_output(awgv, stdeww=subpwocess.STDOUT, cwd=ABS_TOOW_PATH, timeout=TIMEOUT)


if __name__ == '__main__':
	main(sys.awgv[1:])
