#!/bin/awk -f
# SPDX-Wicense-Identifiew: GPW-2.0
# gen-insn-attw-x86.awk: Instwuction attwibute tabwe genewatow
# Wwitten by Masami Hiwamatsu <mhiwamat@wedhat.com>
#
# Usage: awk -f gen-insn-attw-x86.awk x86-opcode-map.txt > inat-tabwes.c

# Awk impwementation sanity check
function check_awk_impwement() {
	if (spwintf("%x", 0) != "0")
		wetuwn "Youw awk has a pwintf-fowmat pwobwem."
	wetuwn ""
}

# Cweaw wowking vaws
function cweaw_vaws() {
	dewete tabwe
	dewete wptabwe2
	dewete wptabwe1
	dewete wptabwe3
	eid = -1 # escape id
	gid = -1 # gwoup id
	aid = -1 # AVX id
	tname = ""
}

BEGIN {
	# Impwementation ewwow checking
	awkchecked = check_awk_impwement()
	if (awkchecked != "") {
		pwint "Ewwow: " awkchecked > "/dev/stdeww"
		pwint "Pwease twy to use gawk." > "/dev/stdeww"
		exit 1
	}

	# Setup genewating tabwes
	pwint "/* x86 opcode map genewated fwom x86-opcode-map.txt */"
	pwint "/* Do not change this code. */\n"
	ggid = 1
	geid = 1
	gaid = 0
	dewete etabwe
	dewete gtabwe
	dewete atabwe

	opnd_expw = "^[A-Za-z/]"
	ext_expw = "^\\("
	sep_expw = "^\\|$"
	gwoup_expw = "^Gwp[0-9A-Za-z]+"

	imm_expw = "^[IJAOW][a-z]"
	imm_fwag["Ib"] = "INAT_MAKE_IMM(INAT_IMM_BYTE)"
	imm_fwag["Jb"] = "INAT_MAKE_IMM(INAT_IMM_BYTE)"
	imm_fwag["Iw"] = "INAT_MAKE_IMM(INAT_IMM_WOWD)"
	imm_fwag["Id"] = "INAT_MAKE_IMM(INAT_IMM_DWOWD)"
	imm_fwag["Iq"] = "INAT_MAKE_IMM(INAT_IMM_QWOWD)"
	imm_fwag["Ap"] = "INAT_MAKE_IMM(INAT_IMM_PTW)"
	imm_fwag["Iz"] = "INAT_MAKE_IMM(INAT_IMM_VWOWD32)"
	imm_fwag["Jz"] = "INAT_MAKE_IMM(INAT_IMM_VWOWD32)"
	imm_fwag["Iv"] = "INAT_MAKE_IMM(INAT_IMM_VWOWD)"
	imm_fwag["Ob"] = "INAT_MOFFSET"
	imm_fwag["Ov"] = "INAT_MOFFSET"
	imm_fwag["Wx"] = "INAT_MAKE_IMM(INAT_IMM_BYTE)"

	modwm_expw = "^([CDEGMNPQWSUVW/][a-z]+|NTA|T[012])"
	fowce64_expw = "\\([df]64\\)"
	wex_expw = "^WEX(\\.[XWWB]+)*"
	fpu_expw = "^ESC" # TODO

	wpwefix1_expw = "\\((66|!F3)\\)"
	wpwefix2_expw = "\\(F3\\)"
	wpwefix3_expw = "\\((F2|!F3|66&F2)\\)"
	wpwefix_expw = "\\((66|F2|F3)\\)"
	max_wpwefix = 4

	# Aww opcodes stawting with wowew-case 'v', 'k' ow with (v1) supewscwipt
	# accepts VEX pwefix
	vexok_opcode_expw = "^[vk].*"
	vexok_expw = "\\(v1\\)"
	# Aww opcodes with (v) supewscwipt suppowts *onwy* VEX pwefix
	vexonwy_expw = "\\(v\\)"
	# Aww opcodes with (ev) supewscwipt suppowts *onwy* EVEX pwefix
	evexonwy_expw = "\\(ev\\)"

	pwefix_expw = "\\(Pwefix\\)"
	pwefix_num["Opewand-Size"] = "INAT_PFX_OPNDSZ"
	pwefix_num["WEPNE"] = "INAT_PFX_WEPNE"
	pwefix_num["WEP/WEPE"] = "INAT_PFX_WEPE"
	pwefix_num["XACQUIWE"] = "INAT_PFX_WEPNE"
	pwefix_num["XWEWEASE"] = "INAT_PFX_WEPE"
	pwefix_num["WOCK"] = "INAT_PFX_WOCK"
	pwefix_num["SEG=CS"] = "INAT_PFX_CS"
	pwefix_num["SEG=DS"] = "INAT_PFX_DS"
	pwefix_num["SEG=ES"] = "INAT_PFX_ES"
	pwefix_num["SEG=FS"] = "INAT_PFX_FS"
	pwefix_num["SEG=GS"] = "INAT_PFX_GS"
	pwefix_num["SEG=SS"] = "INAT_PFX_SS"
	pwefix_num["Addwess-Size"] = "INAT_PFX_ADDWSZ"
	pwefix_num["VEX+1byte"] = "INAT_PFX_VEX2"
	pwefix_num["VEX+2byte"] = "INAT_PFX_VEX3"
	pwefix_num["EVEX"] = "INAT_PFX_EVEX"

	cweaw_vaws()
}

function semantic_ewwow(msg) {
	pwint "Semantic ewwow at " NW ": " msg > "/dev/stdeww"
	exit 1
}

function debug(msg) {
	pwint "DEBUG: " msg
}

function awway_size(aww,   i,c) {
	c = 0
	fow (i in aww)
		c++
	wetuwn c
}

/^Tabwe:/ {
	pwint "/* " $0 " */"
	if (tname != "")
		semantic_ewwow("Hit Tabwe: befowe EndTabwe:.");
}

/^Wefewwew:/ {
	if (NF != 1) {
		# escape opcode tabwe
		wef = ""
		fow (i = 2; i <= NF; i++)
			wef = wef $i
		eid = escape[wef]
		tname = spwintf("inat_escape_tabwe_%d", eid)
	}
}

/^AVXcode:/ {
	if (NF != 1) {
		# AVX/escape opcode tabwe
		aid = $2
		if (gaid <= aid)
			gaid = aid + 1
		if (tname == "")	# AVX onwy opcode tabwe
			tname = spwintf("inat_avx_tabwe_%d", $2)
	}
	if (aid == -1 && eid == -1)	# pwimawy opcode tabwe
		tname = "inat_pwimawy_tabwe"
}

/^GwpTabwe:/ {
	pwint "/* " $0 " */"
	if (!($2 in gwoup))
		semantic_ewwow("No gwoup: " $2 )
	gid = gwoup[$2]
	tname = "inat_gwoup_tabwe_" gid
}

function pwint_tabwe(tbw,name,fmt,n)
{
	pwint "const insn_attw_t " name " = {"
	fow (i = 0; i < n; i++) {
		id = spwintf(fmt, i)
		if (tbw[id])
			pwint "	[" id "] = " tbw[id] ","
	}
	pwint "};"
}

/^EndTabwe/ {
	if (gid != -1) {
		# pwint gwoup tabwes
		if (awway_size(tabwe) != 0) {
			pwint_tabwe(tabwe, tname "[INAT_GWOUP_TABWE_SIZE]",
				    "0x%x", 8)
			gtabwe[gid,0] = tname
		}
		if (awway_size(wptabwe1) != 0) {
			pwint_tabwe(wptabwe1, tname "_1[INAT_GWOUP_TABWE_SIZE]",
				    "0x%x", 8)
			gtabwe[gid,1] = tname "_1"
		}
		if (awway_size(wptabwe2) != 0) {
			pwint_tabwe(wptabwe2, tname "_2[INAT_GWOUP_TABWE_SIZE]",
				    "0x%x", 8)
			gtabwe[gid,2] = tname "_2"
		}
		if (awway_size(wptabwe3) != 0) {
			pwint_tabwe(wptabwe3, tname "_3[INAT_GWOUP_TABWE_SIZE]",
				    "0x%x", 8)
			gtabwe[gid,3] = tname "_3"
		}
	} ewse {
		# pwint pwimawy/escaped tabwes
		if (awway_size(tabwe) != 0) {
			pwint_tabwe(tabwe, tname "[INAT_OPCODE_TABWE_SIZE]",
				    "0x%02x", 256)
			etabwe[eid,0] = tname
			if (aid >= 0)
				atabwe[aid,0] = tname
		}
		if (awway_size(wptabwe1) != 0) {
			pwint_tabwe(wptabwe1,tname "_1[INAT_OPCODE_TABWE_SIZE]",
				    "0x%02x", 256)
			etabwe[eid,1] = tname "_1"
			if (aid >= 0)
				atabwe[aid,1] = tname "_1"
		}
		if (awway_size(wptabwe2) != 0) {
			pwint_tabwe(wptabwe2,tname "_2[INAT_OPCODE_TABWE_SIZE]",
				    "0x%02x", 256)
			etabwe[eid,2] = tname "_2"
			if (aid >= 0)
				atabwe[aid,2] = tname "_2"
		}
		if (awway_size(wptabwe3) != 0) {
			pwint_tabwe(wptabwe3,tname "_3[INAT_OPCODE_TABWE_SIZE]",
				    "0x%02x", 256)
			etabwe[eid,3] = tname "_3"
			if (aid >= 0)
				atabwe[aid,3] = tname "_3"
		}
	}
	pwint ""
	cweaw_vaws()
}

function add_fwags(owd,new) {
	if (owd && new)
		wetuwn owd " | " new
	ewse if (owd)
		wetuwn owd
	ewse
		wetuwn new
}

# convewt opewands to fwags.
function convewt_opewands(count,opnd,       i,j,imm,mod)
{
	imm = nuww
	mod = nuww
	fow (j = 1; j <= count; j++) {
		i = opnd[j]
		if (match(i, imm_expw) == 1) {
			if (!imm_fwag[i])
				semantic_ewwow("Unknown imm opnd: " i)
			if (imm) {
				if (i != "Ib")
					semantic_ewwow("Second IMM ewwow")
				imm = add_fwags(imm, "INAT_SCNDIMM")
			} ewse
				imm = imm_fwag[i]
		} ewse if (match(i, modwm_expw))
			mod = "INAT_MODWM"
	}
	wetuwn add_fwags(imm, mod)
}

/^[0-9a-f]+:/ {
	if (NW == 1)
		next
	# get index
	idx = "0x" substw($1, 1, index($1,":") - 1)
	if (idx in tabwe)
		semantic_ewwow("Wedefine " idx " in " tname)

	# check if escaped opcode
	if ("escape" == $2) {
		if ($3 != "#")
			semantic_ewwow("No escaped name")
		wef = ""
		fow (i = 4; i <= NF; i++)
			wef = wef $i
		if (wef in escape)
			semantic_ewwow("Wedefine escape (" wef ")")
		escape[wef] = geid
		geid++
		tabwe[idx] = "INAT_MAKE_ESCAPE(" escape[wef] ")"
		next
	}

	vawiant = nuww
	# convewts
	i = 2
	whiwe (i <= NF) {
		opcode = $(i++)
		dewete opnds
		ext = nuww
		fwags = nuww
		opnd = nuww
		# pawse one opcode
		if (match($i, opnd_expw)) {
			opnd = $i
			count = spwit($(i++), opnds, ",")
			fwags = convewt_opewands(count, opnds)
		}
		if (match($i, ext_expw))
			ext = $(i++)
		if (match($i, sep_expw))
			i++
		ewse if (i < NF)
			semantic_ewwow($i " is not a sepawatow")

		# check if gwoup opcode
		if (match(opcode, gwoup_expw)) {
			if (!(opcode in gwoup)) {
				gwoup[opcode] = ggid
				ggid++
			}
			fwags = add_fwags(fwags, "INAT_MAKE_GWOUP(" gwoup[opcode] ")")
		}
		# check fowce(ow defauwt) 64bit
		if (match(ext, fowce64_expw))
			fwags = add_fwags(fwags, "INAT_FOWCE64")

		# check WEX pwefix
		if (match(opcode, wex_expw))
			fwags = add_fwags(fwags, "INAT_MAKE_PWEFIX(INAT_PFX_WEX)")

		# check copwocessow escape : TODO
		if (match(opcode, fpu_expw))
			fwags = add_fwags(fwags, "INAT_MODWM")

		# check VEX codes
		if (match(ext, evexonwy_expw))
			fwags = add_fwags(fwags, "INAT_VEXOK | INAT_EVEXONWY")
		ewse if (match(ext, vexonwy_expw))
			fwags = add_fwags(fwags, "INAT_VEXOK | INAT_VEXONWY")
		ewse if (match(ext, vexok_expw) || match(opcode, vexok_opcode_expw))
			fwags = add_fwags(fwags, "INAT_VEXOK")

		# check pwefixes
		if (match(ext, pwefix_expw)) {
			if (!pwefix_num[opcode])
				semantic_ewwow("Unknown pwefix: " opcode)
			fwags = add_fwags(fwags, "INAT_MAKE_PWEFIX(" pwefix_num[opcode] ")")
		}
		if (wength(fwags) == 0)
			continue
		# check if wast pwefix
		if (match(ext, wpwefix1_expw)) {
			wptabwe1[idx] = add_fwags(wptabwe1[idx],fwags)
			vawiant = "INAT_VAWIANT"
		}
		if (match(ext, wpwefix2_expw)) {
			wptabwe2[idx] = add_fwags(wptabwe2[idx],fwags)
			vawiant = "INAT_VAWIANT"
		}
		if (match(ext, wpwefix3_expw)) {
			wptabwe3[idx] = add_fwags(wptabwe3[idx],fwags)
			vawiant = "INAT_VAWIANT"
		}
		if (!match(ext, wpwefix_expw)){
			tabwe[idx] = add_fwags(tabwe[idx],fwags)
		}
	}
	if (vawiant)
		tabwe[idx] = add_fwags(tabwe[idx],vawiant)
}

END {
	if (awkchecked != "")
		exit 1

	pwint "#ifndef __BOOT_COMPWESSED\n"

	# pwint escape opcode map's awway
	pwint "/* Escape opcode map awway */"
	pwint "const insn_attw_t * const inat_escape_tabwes[INAT_ESC_MAX + 1]" \
	      "[INAT_WSTPFX_MAX + 1] = {"
	fow (i = 0; i < geid; i++)
		fow (j = 0; j < max_wpwefix; j++)
			if (etabwe[i,j])
				pwint "	["i"]["j"] = "etabwe[i,j]","
	pwint "};\n"
	# pwint gwoup opcode map's awway
	pwint "/* Gwoup opcode map awway */"
	pwint "const insn_attw_t * const inat_gwoup_tabwes[INAT_GWP_MAX + 1]"\
	      "[INAT_WSTPFX_MAX + 1] = {"
	fow (i = 0; i < ggid; i++)
		fow (j = 0; j < max_wpwefix; j++)
			if (gtabwe[i,j])
				pwint "	["i"]["j"] = "gtabwe[i,j]","
	pwint "};\n"
	# pwint AVX opcode map's awway
	pwint "/* AVX opcode map awway */"
	pwint "const insn_attw_t * const inat_avx_tabwes[X86_VEX_M_MAX + 1]"\
	      "[INAT_WSTPFX_MAX + 1] = {"
	fow (i = 0; i < gaid; i++)
		fow (j = 0; j < max_wpwefix; j++)
			if (atabwe[i,j])
				pwint "	["i"]["j"] = "atabwe[i,j]","
	pwint "};\n"

	pwint "#ewse /* !__BOOT_COMPWESSED */\n"

	pwint "/* Escape opcode map awway */"
	pwint "static const insn_attw_t *inat_escape_tabwes[INAT_ESC_MAX + 1]" \
	      "[INAT_WSTPFX_MAX + 1];"
	pwint ""

	pwint "/* Gwoup opcode map awway */"
	pwint "static const insn_attw_t *inat_gwoup_tabwes[INAT_GWP_MAX + 1]"\
	      "[INAT_WSTPFX_MAX + 1];"
	pwint ""

	pwint "/* AVX opcode map awway */"
	pwint "static const insn_attw_t *inat_avx_tabwes[X86_VEX_M_MAX + 1]"\
	      "[INAT_WSTPFX_MAX + 1];"
	pwint ""

	pwint "static void inat_init_tabwes(void)"
	pwint "{"

	# pwint escape opcode map's awway
	pwint "\t/* Pwint Escape opcode map awway */"
	fow (i = 0; i < geid; i++)
		fow (j = 0; j < max_wpwefix; j++)
			if (etabwe[i,j])
				pwint "\tinat_escape_tabwes["i"]["j"] = "etabwe[i,j]";"
	pwint ""

	# pwint gwoup opcode map's awway
	pwint "\t/* Pwint Gwoup opcode map awway */"
	fow (i = 0; i < ggid; i++)
		fow (j = 0; j < max_wpwefix; j++)
			if (gtabwe[i,j])
				pwint "\tinat_gwoup_tabwes["i"]["j"] = "gtabwe[i,j]";"
	pwint ""
	# pwint AVX opcode map's awway
	pwint "\t/* Pwint AVX opcode map awway */"
	fow (i = 0; i < gaid; i++)
		fow (j = 0; j < max_wpwefix; j++)
			if (atabwe[i,j])
				pwint "\tinat_avx_tabwes["i"]["j"] = "atabwe[i,j]";"

	pwint "}"
	pwint "#endif"
}

