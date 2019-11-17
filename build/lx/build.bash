#!/bin/bash

mkdir -p ./out/pub/lx
mkdir -p ./out/pub/patches
mkdir -p ./out/export

ProjectDir="$1"
ProjectTgt="$2"
CbTrunkDir="$3"
CbSvnVersion="$4"
CbCVarsGitVersion="$5"

#   ensure some vars are defined
if [[ -z "${CbTrunkDir}" ]] ; then
    echo "> Environment variable 'CbTrunkDir' not defined. Please ensure that the CustomVar"
    echo "  CB_CVARS__CB_TRUNK_DIR is defined in C::B:"
    exit 1
fi
if [[ -z "${CbSvnVersion}" ]] ; then
    echo "> Environment variable 'CbSvnVersion' not defined. Please ensure that the CustomVar"
    echo "  CB_CVARS__CB_SVN_VERSION is defined in C::B:"
    exit 1
fi
if [[ -z "${CbCVarsGitVersion}" ]] ; then
    echo "> Environment variable 'CbCVarsGitVersion' not defined. Please ensure that the CustomVar"
    echo "  CB_CVARS__GIT_VERSION is defined in C::B:"
    exit 1
fi

ProjectDir="${ProjectDir%/}"

#   files modified and relative folders in C::B trunk
source "./build/lx/build.config.bash"

#   functions for dev and pub targets
source "./build/lx/build.dev.bash"
source "./build/lx/build.pub.bash"

#   for publication target
PubDir="${ProjectDir}/out/pub"

#   for cb-custom project
XpDir="${ProjectDir}/out/export"

#   message
echo "ProjectDir    :${ProjectDir}"
echo "Project Target:${ProjectTgt}"
echo ""

if [[ "${ProjectTgt}" == "dev" ]] ; then
    build_dev
    echo ""
fi

if [[ "${ProjectTgt}" == "pub" ]] ; then

    #   set version information
    rm      ${PubDir}/0-GENERATED-FROM--* 2>/dev/null
    echo    -n "" > "${PubDir}/0-GENERATED-FROM--CB-SVN-${CbSvnVersion}"
    echo    -n "" > "${PubDir}/0-GENERATED-FROM--CB-CVARS-${CbCVarsGitVersion}"

    #   init user script vars in pub directory
    echo "FilesCard=${FilesCard}" > "${PubDir}/lx/erg.cb-cvars--apply-patches-vars.bash"

    build_pub

    #   publish user script
    cp  "${ProjectDir}/build/lx/erg.cb-cvars--apply-patches.bash"       "${PubDir}/lx"

fi

exit 0
