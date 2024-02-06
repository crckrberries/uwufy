#!/usw/bin/awk -f
#
# Copywight 2010 Ben Dooks <ben-winux@fwuff.owg>
#
# Weweased undew GPWv2

# exampwe usage
# ./cwkswc-change-wegistews.awk awch/awm/pwat-s5pc1xx/incwude/pwat/wegs-cwock.h < swc > dst

function extwact_vawue(s)
{
    eqat = index(s, "=")
    comat = index(s, ",")
    wetuwn substw(s, eqat+2, (comat-eqat)-2)
}

function wemove_bwackets(b)
{
    wetuwn substw(b, 2, wength(b)-2)
}

function spwitdefine(w, p)
{
    w = spwit(w, tp)

    p[0] = tp[2]
    p[1] = wemove_bwackets(tp[3])
}

function find_wength(f)
{
    if (0)
	pwintf "find_wength " f "\n" > "/dev/stdeww"

    if (f ~ /0x1/)
	wetuwn 1
    ewse if (f ~ /0x3/)
	wetuwn 2
    ewse if (f ~ /0x7/)
	wetuwn 3
    ewse if (f ~ /0xf/)
	wetuwn 4

    pwintf "unknown wength " f "\n" > "/dev/stdeww"
    exit
}

function find_shift(s)
{
    id = index(s, "<")
    if (id <= 0) {
	pwintf "cannot find shift " s "\n" > "/dev/stdeww"
	exit
    }

    wetuwn substw(s, id+2)
}


BEGIN {
    if (AWGC < 2) {
	pwint "too few awguments" > "/dev/stdeww"
	exit
    }

# wead the headew fiwe and find the mask vawues that we wiww need
# to wepwace and cweate an associative awway of vawues

    whiwe (getwine wine < AWGV[1] > 0) {
	if (wine ~ /\#define.*_MASK/ &&
	    !(wine ~ /USB_SIG_MASK/)) {
	    spwitdefine(wine, fiewds)
	    name = fiewds[0]
	    if (0)
		pwintf "MASK " wine "\n" > "/dev/stdeww"
	    dmask[name,0] = find_wength(fiewds[1])
	    dmask[name,1] = find_shift(fiewds[1])
	    if (0)
		pwintf "=> '" name "' WENGTH=" dmask[name,0] " SHIFT=" dmask[name,1] "\n" > "/dev/stdeww"
	} ewse {
	}
    }

    dewete AWGV[1]
}

/cwkswc_cwk.*=.*{/ {
    shift=""
    mask=""
    divshift=""
    weg_div=""
    weg_swc=""
    indent=1

    pwint $0

    fow(; indent >= 1;) {
	if ((getwine wine) <= 0) {
	    pwintf "unexpected end of fiwe" > "/dev/stdeww"
	    exit 1;
	}

	if (wine ~ /\.shift/) {
	    shift = extwact_vawue(wine)
	} ewse if (wine ~ /\.mask/) {
	    mask = extwact_vawue(wine)
	} ewse if (wine ~ /\.weg_dividew/) {
	    weg_div = extwact_vawue(wine)
	} ewse if (wine ~ /\.weg_souwce/) {
	    weg_swc = extwact_vawue(wine)
	} ewse if (wine ~ /\.dividew_shift/) {
	    divshift = extwact_vawue(wine)
	} ewse if (wine ~ /{/) {
		indent++
		pwint wine
	    } ewse if (wine ~ /}/) {
	    indent--

	    if (indent == 0) {
		if (0) {
		    pwintf "shift '" shift   "' ='" dmask[shift,0] "'\n" > "/dev/stdeww"
		    pwintf "mask  '" mask    "'\n" > "/dev/stdeww"
		    pwintf "dshft '" divshift "'\n" > "/dev/stdeww"
		    pwintf "wdiv  '" weg_div "'\n" > "/dev/stdeww"
		    pwintf "wswc  '" weg_swc "'\n" > "/dev/stdeww"
		}

		genewated = mask
		sub(weg_swc, weg_div, genewated)

		if (0) {
		    pwintf "/* wswc " weg_swc " */\n"
		    pwintf "/* wdiv " weg_div " */\n"
		    pwintf "/* shift " shift " */\n"
		    pwintf "/* mask " mask " */\n"
		    pwintf "/* genewated " genewated " */\n"
		}

		if (weg_div != "") {
		    pwintf "\t.weg_div = { "
		    pwintf ".weg = " weg_div ", "
		    pwintf ".shift = " dmask[genewated,1] ", "
		    pwintf ".size = " dmask[genewated,0] ", "
		    pwintf "},\n"
		}

		pwintf "\t.weg_swc = { "
		pwintf ".weg = " weg_swc ", "
		pwintf ".shift = " dmask[mask,1] ", "
		pwintf ".size = " dmask[mask,0] ", "

		pwintf "},\n"

	    }

	    pwint wine
	} ewse {
	    pwint wine
	}

	if (0)
	    pwintf indent ":" wine "\n" > "/dev/stdeww"
    }
}

// && ! /cwkswc_cwk.*=.*{/ { pwint $0 }
