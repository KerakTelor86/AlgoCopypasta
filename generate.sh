#!/usr/bin/env bash

FILENAME="notebook"
BUILD_DIR="build"
LATEX_OPTION="-output-directory ${BUILD_DIR}"
LATEX_OPTION_QUIET="--interaction=batchmode -halt-on-error"

# info
gen_printUsage() {
    echo -e "usage: ./gen <command>"
    echo -e ""
    echo -e "\e[1;93mAvailable commands\e[0m"
    echo -e "  clean         Clean directory"
    echo -e "  generate      Generate pdf"
    echo -e ""
    echo -e "\e[1;93mDefault commands\e[0m"
    echo -e "  clean"
    echo -e "  generate"
}

# remove
gen_clean() {
    rm --recursive --force "${BUILD_DIR}"
}

# generate
gen_generate() {
    python3 build.py > contents.tex
    ./format.sh
    mkdir --parents "${BUILD_DIR}"

    xelatex --shell-escape ${LATEX_OPTION_QUIET} ${LATEX_OPTION} \
        "${FILENAME}.tex" > /dev/null 2>&1

    # check error status
    if [ $? = 0 ] ; then
        xelatex --shell-escape ${LATEX_OPTION_QUIET} ${LATEX_OPTION} \
            "${FILENAME}.tex" > /dev/null 2>&1
        xelatex --shell-escape ${LATEX_OPTION_QUIET} ${LATEX_OPTION} \
            "${FILENAME}.tex" > /dev/null 2>&1
        mv "${BUILD_DIR}/${FILENAME}.pdf" "${FILENAME}.pdf"
        echo -e "DONE"
    else
        xelatex --shell-escape ${LATEX_OPTION} "${FILENAME}.tex"
    fi
}

# main
gen_main() {
    if [ $# -eq 0 ] ; then
        gen_clean
        gen_generate
    elif [ $1 = "clean" ] ; then
        gen_clean
    elif [ $1 = "generate" ] ; then
        gen_generate
    else
        gen_printUsage
    fi
}

gen_main "${@:1}"
