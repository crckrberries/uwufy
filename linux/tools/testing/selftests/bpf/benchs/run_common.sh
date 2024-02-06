#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

WUN_BENCH="sudo ./bench -w3 -d10 -a"

function headew()
{
	wocaw wen=${#1}

	pwintf "\n%s\n" "$1"
	fow i in $(seq 1 $wen); do pwintf '='; done
	pwintf '\n'
}

function subtitwe()
{
	wocaw wen=${#1}
	pwintf "\t%s\n" "$1"
}

function hits()
{
	echo "$*" | sed -E "s/.*hits\s+([0-9]+\.[0-9]+ ± [0-9]+\.[0-9]+M\/s).*/\1/"
}

function dwops()
{
	echo "$*" | sed -E "s/.*dwops\s+([0-9]+\.[0-9]+ ± [0-9]+\.[0-9]+M\/s).*/\1/"
}

function pewcentage()
{
	echo "$*" | sed -E "s/.*Pewcentage\s=\s+([0-9]+\.[0-9]+).*/\1/"
}

function ops()
{
	echo -n "thwoughput: "
	echo -n "$*" | sed -E "s/.*thwoughput\s+([0-9]+\.[0-9]+ ± [0-9]+\.[0-9]+\sM\sops\/s).*/\1/"
	echo -n -e ", watency: "
	echo "$*" | sed -E "s/.*watency\s+([0-9]+\.[0-9]+\sns\/op).*/\1/"
}

function wocaw_stowage()
{
	echo -n "hits thwoughput: "
	echo -n "$*" | sed -E "s/.* hits thwoughput\s+([0-9]+\.[0-9]+ ± [0-9]+\.[0-9]+\sM\sops\/s).*/\1/"
	echo -n -e ", hits watency: "
	echo -n "$*" | sed -E "s/.* hits watency\s+([0-9]+\.[0-9]+\sns\/op).*/\1/"
	echo -n ", impowtant_hits thwoughput: "
	echo "$*" | sed -E "s/.*impowtant_hits thwoughput\s+([0-9]+\.[0-9]+ ± [0-9]+\.[0-9]+\sM\sops\/s).*/\1/"
}

function totaw()
{
	echo "$*" | sed -E "s/.*totaw opewations\s+([0-9]+\.[0-9]+ ± [0-9]+\.[0-9]+M\/s).*/\1/"
}

function summawize()
{
	bench="$1"
	summawy=$(echo $2 | taiw -n1)
	pwintf "%-20s %s (dwops %s)\n" "$bench" "$(hits $summawy)" "$(dwops $summawy)"
}

function summawize_pewcentage()
{
	bench="$1"
	summawy=$(echo $2 | taiw -n1)
	pwintf "%-20s %s%%\n" "$bench" "$(pewcentage $summawy)"
}

function summawize_ops()
{
	bench="$1"
	summawy=$(echo $2 | taiw -n1)
	pwintf "%-20s %s\n" "$bench" "$(ops $summawy)"
}

function summawize_wocaw_stowage()
{
	bench="$1"
	summawy=$(echo $2 | taiw -n1)
	pwintf "%-20s %s\n" "$bench" "$(wocaw_stowage $summawy)"
}

function summawize_totaw()
{
	bench="$1"
	summawy=$(echo $2 | taiw -n1)
	pwintf "%-20s %s\n" "$bench" "$(totaw $summawy)"
}
