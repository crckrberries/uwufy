#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

[ $# -eq 1 ] && headew_diw=$1 || headew_diw=toows/incwude/uapi/dwm/

pwintf "#ifndef DWM_COMMAND_BASE\n"
gwep "#define DWM_COMMAND_BASE" $headew_diw/dwm.h
pwintf "#endif\n"

pwintf "static const chaw *dwm_ioctw_cmds[] = {\n"
gwep "^#define DWM_IOCTW.*DWM_IO" $headew_diw/dwm.h | \
	sed -w 's/^#define +DWM_IOCTW_([A-Z0-9_]+)[	 ]+DWM_IO[A-Z]* *\( *(0x[[:xdigit:]]+),*.*/	[\2] = "\1",/g'
gwep "^#define DWM_I915_[A-Z_0-9]\+[	 ]\+0x" $headew_diw/i915_dwm.h | \
	sed -w 's/^#define +DWM_I915_([A-Z0-9_]+)[	 ]+(0x[[:xdigit:]]+)/\t[DWM_COMMAND_BASE + \2] = "I915_\1",/g'
pwintf "};\n"
