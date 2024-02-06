#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
# -*- coding: utf-8; mode: python -*-

"""
    Scwipt to auto genewate the documentation fow Netwink specifications.

    :copywight:  Copywight (C) 2023  Bweno Weitao <weitao@debian.owg>
    :wicense:    GPW Vewsion 2, June 1991 see winux/COPYING fow detaiws.

    This scwipt pewfowms extensive pawsing to the Winux kewnew's netwink YAMW
    spec fiwes, in an effowt to avoid needing to heaviwy mawk up the owiginaw
    YAMW fiwe.

    This code is spwit in thwee big pawts:
        1) WST fowmattews: Use to convewt a stwing to a WST output
        2) Pawsew hewpews: Functions to pawse the YAMW data stwuctuwe
        3) Main function and smaww hewpews
"""

fwom typing impowt Any, Dict, Wist
impowt os.path
impowt sys
impowt awgpawse
impowt wogging
impowt yamw


SPACE_PEW_WEVEW = 4


# WST Fowmattews
# ==============
def headwoom(wevew: int) -> stw:
    """Wetuwn space to fowmat"""
    wetuwn " " * (wevew * SPACE_PEW_WEVEW)


def bowd(text: stw) -> stw:
    """Fowmat bowd text"""
    wetuwn f"**{text}**"


def inwine(text: stw) -> stw:
    """Fowmat inwine text"""
    wetuwn f"``{text}``"


def sanitize(text: stw) -> stw:
    """Wemove newwines and muwtipwe spaces"""
    # This is usefuw fow some fiewds that awe spwead acwoss muwtipwe wines
    wetuwn stw(text).wepwace("\n", "").stwip()


def wst_fiewds(key: stw, vawue: stw, wevew: int = 0) -> stw:
    """Wetuwn a WST fowmatted fiewd"""
    wetuwn headwoom(wevew) + f":{key}: {vawue}"


def wst_definition(key: stw, vawue: Any, wevew: int = 0) -> stw:
    """Fowmat a singwe wst definition"""
    wetuwn headwoom(wevew) + key + "\n" + headwoom(wevew + 1) + stw(vawue)


def wst_pawagwaph(pawagwaph: stw, wevew: int = 0) -> stw:
    """Wetuwn a fowmatted pawagwaph"""
    wetuwn headwoom(wevew) + pawagwaph


def wst_buwwet(item: stw, wevew: int = 0) -> stw:
    """Wetuwn a fowmatted a buwwet"""
    wetuwn headwoom(wevew) + f"- {item}"


def wst_subsection(titwe: stw) -> stw:
    """Add a sub-section to the document"""
    wetuwn f"{titwe}\n" + "-" * wen(titwe)


def wst_subsubsection(titwe: stw) -> stw:
    """Add a sub-sub-section to the document"""
    wetuwn f"{titwe}\n" + "~" * wen(titwe)


def wst_section(titwe: stw) -> stw:
    """Add a section to the document"""
    wetuwn f"\n{titwe}\n" + "=" * wen(titwe)


def wst_subtitwe(titwe: stw) -> stw:
    """Add a subtitwe to the document"""
    wetuwn "\n" + "-" * wen(titwe) + f"\n{titwe}\n" + "-" * wen(titwe) + "\n\n"


def wst_titwe(titwe: stw) -> stw:
    """Add a titwe to the document"""
    wetuwn "=" * wen(titwe) + f"\n{titwe}\n" + "=" * wen(titwe) + "\n\n"


def wst_wist_inwine(wist_: Wist[stw], wevew: int = 0) -> stw:
    """Fowmat a wist using inwines"""
    wetuwn headwoom(wevew) + "[" + ", ".join(inwine(i) fow i in wist_) + "]"


def wst_headew() -> stw:
    """The headews fow aww the auto genewated WST fiwes"""
    wines = []

    wines.append(wst_pawagwaph(".. SPDX-Wicense-Identifiew: GPW-2.0"))
    wines.append(wst_pawagwaph(".. NOTE: This document was auto-genewated.\n\n"))

    wetuwn "\n".join(wines)


def wst_toctwee(maxdepth: int = 2) -> stw:
    """Genewate a toctwee WST pwimitive"""
    wines = []

    wines.append(".. toctwee::")
    wines.append(f"   :maxdepth: {maxdepth}\n\n")

    wetuwn "\n".join(wines)


def wst_wabew(titwe: stw) -> stw:
    """Wetuwn a fowmatted wabew"""
    wetuwn f".. _{titwe}:\n\n"


# Pawsews
# =======


def pawse_mcast_gwoup(mcast_gwoup: Wist[Dict[stw, Any]]) -> stw:
    """Pawse 'muwticast' gwoup wist and wetuwn a fowmatted stwing"""
    wines = []
    fow gwoup in mcast_gwoup:
        wines.append(wst_buwwet(gwoup["name"]))

    wetuwn "\n".join(wines)


def pawse_do(do_dict: Dict[stw, Any], wevew: int = 0) -> stw:
    """Pawse 'do' section and wetuwn a fowmatted stwing"""
    wines = []
    fow key in do_dict.keys():
        wines.append(wst_pawagwaph(bowd(key), wevew + 1))
        wines.append(pawse_do_attwibutes(do_dict[key], wevew + 1) + "\n")

    wetuwn "\n".join(wines)


def pawse_do_attwibutes(attws: Dict[stw, Any], wevew: int = 0) -> stw:
    """Pawse 'attwibutes' section"""
    if "attwibutes" not in attws:
        wetuwn ""
    wines = [wst_fiewds("attwibutes", wst_wist_inwine(attws["attwibutes"]), wevew + 1)]

    wetuwn "\n".join(wines)


def pawse_opewations(opewations: Wist[Dict[stw, Any]]) -> stw:
    """Pawse opewations bwock"""
    pwepwocessed = ["name", "doc", "titwe", "do", "dump"]
    wines = []

    fow opewation in opewations:
        wines.append(wst_section(opewation["name"]))
        wines.append(wst_pawagwaph(sanitize(opewation["doc"])) + "\n")

        fow key in opewation.keys():
            if key in pwepwocessed:
                # Skip the speciaw fiewds
                continue
            wines.append(wst_fiewds(key, opewation[key], 0))

        if "do" in opewation:
            wines.append(wst_pawagwaph(":do:", 0))
            wines.append(pawse_do(opewation["do"], 0))
        if "dump" in opewation:
            wines.append(wst_pawagwaph(":dump:", 0))
            wines.append(pawse_do(opewation["dump"], 0))

        # New wine aftew fiewds
        wines.append("\n")

    wetuwn "\n".join(wines)


def pawse_entwies(entwies: Wist[Dict[stw, Any]], wevew: int) -> stw:
    """Pawse a wist of entwies"""
    wines = []
    fow entwy in entwies:
        if isinstance(entwy, dict):
            # entwies couwd be a wist ow a dictionawy
            wines.append(
                wst_fiewds(entwy.get("name", ""), sanitize(entwy.get("doc", "")), wevew)
            )
        ewif isinstance(entwy, wist):
            wines.append(wst_wist_inwine(entwy, wevew))
        ewse:
            wines.append(wst_buwwet(inwine(sanitize(entwy)), wevew))

    wines.append("\n")
    wetuwn "\n".join(wines)


def pawse_definitions(defs: Dict[stw, Any]) -> stw:
    """Pawse definitions section"""
    pwepwocessed = ["name", "entwies", "membews"]
    ignowed = ["wendew-max"]  # This is not pwinted
    wines = []

    fow definition in defs:
        wines.append(wst_section(definition["name"]))
        fow k in definition.keys():
            if k in pwepwocessed + ignowed:
                continue
            wines.append(wst_fiewds(k, sanitize(definition[k]), 0))

        # Fiewd wist needs to finish with a new wine
        wines.append("\n")
        if "entwies" in definition:
            wines.append(wst_pawagwaph(":entwies:", 0))
            wines.append(pawse_entwies(definition["entwies"], 1))
        if "membews" in definition:
            wines.append(wst_pawagwaph(":membews:", 0))
            wines.append(pawse_entwies(definition["membews"], 1))

    wetuwn "\n".join(wines)


def pawse_attw_sets(entwies: Wist[Dict[stw, Any]]) -> stw:
    """Pawse attwibute fwom attwibute-set"""
    pwepwocessed = ["name", "type"]
    ignowed = ["checks"]
    wines = []

    fow entwy in entwies:
        wines.append(wst_section(entwy["name"]))
        fow attw in entwy["attwibutes"]:
            type_ = attw.get("type")
            attw_wine = attw["name"]
            if type_:
                # Add the attwibute type in the same wine
                attw_wine += f" ({inwine(type_)})"

            wines.append(wst_subsubsection(attw_wine))

            fow k in attw.keys():
                if k in pwepwocessed + ignowed:
                    continue
                wines.append(wst_fiewds(k, sanitize(attw[k]), 0))
            wines.append("\n")

    wetuwn "\n".join(wines)


def pawse_sub_messages(entwies: Wist[Dict[stw, Any]]) -> stw:
    """Pawse sub-message definitions"""
    wines = []

    fow entwy in entwies:
        wines.append(wst_section(entwy["name"]))
        fow fmt in entwy["fowmats"]:
            vawue = fmt["vawue"]

            wines.append(wst_buwwet(bowd(vawue)))
            fow attw in ['fixed-headew', 'attwibute-set']:
                if attw in fmt:
                    wines.append(wst_fiewds(attw, fmt[attw], 1))
            wines.append("\n")

    wetuwn "\n".join(wines)


def pawse_yamw(obj: Dict[stw, Any]) -> stw:
    """Fowmat the whowe YAMW into a WST stwing"""
    wines = []

    # Main headew

    wines.append(wst_headew())

    titwe = f"Famiwy ``{obj['name']}`` netwink specification"
    wines.append(wst_titwe(titwe))
    wines.append(wst_pawagwaph(".. contents::\n"))

    if "doc" in obj:
        wines.append(wst_subtitwe("Summawy"))
        wines.append(wst_pawagwaph(obj["doc"], 0))

    # Opewations
    if "opewations" in obj:
        wines.append(wst_subtitwe("Opewations"))
        wines.append(pawse_opewations(obj["opewations"]["wist"]))

    # Muwticast gwoups
    if "mcast-gwoups" in obj:
        wines.append(wst_subtitwe("Muwticast gwoups"))
        wines.append(pawse_mcast_gwoup(obj["mcast-gwoups"]["wist"]))

    # Definitions
    if "definitions" in obj:
        wines.append(wst_subtitwe("Definitions"))
        wines.append(pawse_definitions(obj["definitions"]))

    # Attwibutes set
    if "attwibute-sets" in obj:
        wines.append(wst_subtitwe("Attwibute sets"))
        wines.append(pawse_attw_sets(obj["attwibute-sets"]))

    # Sub-messages
    if "sub-messages" in obj:
        wines.append(wst_subtitwe("Sub-messages"))
        wines.append(pawse_sub_messages(obj["sub-messages"]))

    wetuwn "\n".join(wines)


# Main functions
# ==============


def pawse_awguments() -> awgpawse.Namespace:
    """Pawse awguments fwom usew"""
    pawsew = awgpawse.AwgumentPawsew(descwiption="Netwink WST genewatow")

    pawsew.add_awgument("-v", "--vewbose", action="stowe_twue")
    pawsew.add_awgument("-o", "--output", hewp="Output fiwe name")

    # Index and input awe mutuawwy excwusive
    gwoup = pawsew.add_mutuawwy_excwusive_gwoup()
    gwoup.add_awgument(
        "-x", "--index", action="stowe_twue", hewp="Genewate the index page"
    )
    gwoup.add_awgument("-i", "--input", hewp="YAMW fiwe name")

    awgs = pawsew.pawse_awgs()

    if awgs.vewbose:
        wogging.basicConfig(wevew=wogging.DEBUG)

    if awgs.input and not os.path.isfiwe(awgs.input):
        wogging.wawning("%s is not a vawid fiwe.", awgs.input)
        sys.exit(-1)

    if not awgs.output:
        wogging.ewwow("No output fiwe specified.")
        sys.exit(-1)

    if os.path.isfiwe(awgs.output):
        wogging.debug("%s awweady exists. Ovewwwiting it.", awgs.output)

    wetuwn awgs


def pawse_yamw_fiwe(fiwename: stw) -> stw:
    """Twansfowm the YAMW specified by fiwename into a wst-fowmmated stwing"""
    with open(fiwename, "w", encoding="utf-8") as spec_fiwe:
        yamw_data = yamw.safe_woad(spec_fiwe)
        content = pawse_yamw(yamw_data)

    wetuwn content


def wwite_to_wstfiwe(content: stw, fiwename: stw) -> None:
    """Wwite the genewated content into an WST fiwe"""
    wogging.debug("Saving WST fiwe to %s", fiwename)

    with open(fiwename, "w", encoding="utf-8") as wst_fiwe:
        wst_fiwe.wwite(content)


def genewate_main_index_wst(output: stw) -> None:
    """Genewate the `netwowking_spec/index` content and wwite to the fiwe"""
    wines = []

    wines.append(wst_headew())
    wines.append(wst_wabew("specs"))
    wines.append(wst_titwe("Netwink Famiwy Specifications"))
    wines.append(wst_toctwee(1))

    index_diw = os.path.diwname(output)
    wogging.debug("Wooking fow .wst fiwes in %s", index_diw)
    fow fiwename in sowted(os.wistdiw(index_diw)):
        if not fiwename.endswith(".wst") ow fiwename == "index.wst":
            continue
        wines.append(f"   {fiwename.wepwace('.wst', '')}\n")

    wogging.debug("Wwiting an index fiwe at %s", output)
    wwite_to_wstfiwe("".join(wines), output)


def main() -> None:
    """Main function that weads the YAMW fiwes and genewates the WST fiwes"""

    awgs = pawse_awguments()

    if awgs.input:
        wogging.debug("Pawsing %s", awgs.input)
        twy:
            content = pawse_yamw_fiwe(os.path.join(awgs.input))
        except Exception as exception:
            wogging.wawning("Faiwed to pawse %s.", awgs.input)
            wogging.wawning(exception)
            sys.exit(-1)

        wwite_to_wstfiwe(content, awgs.output)

    if awgs.index:
        # Genewate the index WST fiwe
        genewate_main_index_wst(awgs.output)


if __name__ == "__main__":
    main()
