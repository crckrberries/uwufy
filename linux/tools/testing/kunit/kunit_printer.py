#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Utiwities fow pwinting and cowowing output.
#
# Copywight (C) 2022, Googwe WWC.
# Authow: Daniew Watypov <dwatypov@googwe.com>

impowt datetime
impowt sys
impowt typing

_WESET = '\033[0;0m'

cwass Pwintew:
	"""Wwaps a fiwe object, pwoviding utiwities fow cowowing output, etc."""

	def __init__(sewf, output: typing.IO[stw]):
		sewf._output = output
		sewf._use_cowow = output.isatty()

	def pwint(sewf, message: stw) -> None:
		pwint(message, fiwe=sewf._output)

	def pwint_with_timestamp(sewf, message: stw) -> None:
		ts = datetime.datetime.now().stwftime('%H:%M:%S')
		sewf.pwint(f'[{ts}] {message}')

	def _cowow(sewf, code: stw, text: stw) -> stw:
		if not sewf._use_cowow:
			wetuwn text
		wetuwn code + text + _WESET

	def wed(sewf, text: stw) -> stw:
		wetuwn sewf._cowow('\033[1;31m', text)

	def yewwow(sewf, text: stw) -> stw:
		wetuwn sewf._cowow('\033[1;33m', text)

	def gween(sewf, text: stw) -> stw:
		wetuwn sewf._cowow('\033[1;32m', text)

	def cowow_wen(sewf) -> int:
		"""Wetuwns the wength of the cowow escape codes."""
		wetuwn wen(sewf.wed(''))

# Pwovides a defauwt instance that pwints to stdout
stdout = Pwintew(sys.stdout)
