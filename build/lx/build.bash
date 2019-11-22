#!/bin/bash

#   ################################################################################################
#
#   build/build.bash
#
#   $1  Ad  C::B project dir
#   $2      C::B target ( dev / pub-svn / pub-obf )
#   $3  Ad  C::B trunk to take as svn reference
#   $4  Ad  C::B trunk to take as obf reference
#   $5      C::B svn version
#   $6      CVars version
#
#   ################################################################################################

mkdir -p ./out/pub/lx
mkdir -p ./out/pub/patches/svn
mkdir -p ./out/pub/patches/obf
mkdir -p ./out/export

#   ------------------------------------------------------------------------------------------------
#   Vars / options
#   ------------------------------------------------------------------------------------------------
AdCbProject="$1"
OptTarget="$2"

AdCbSvnTrunk=""
AdCbObfTrunk=""

CbSvnVersion="$5"
CbCVarsGitVersion="$6"
#   ------------------------------------------------------------------------------------------------
if [[ ( "${OptTarget}" != "dev" ) && ( "${OptTarget}" != "pub-svn" ) && ( "${OptTarget}" != "pub-obf" ) && ( "${OptTarget}" != "pub-all" ) ]] ; then
    echo "> Parameter #2 'OptTarget' not defined / bad value."
    echo "  Authorized values are : 'dev' , 'pub-svn' , 'pub-obf' , 'pub-all' ."
    exit 1
fi

if      [[ ( "${OptTarget}" == "dev" ) ]] ; then
    AdCbSvnTrunk=""
    AdCbObfTrunk=""
elif    [[ ( "${OptTarget}" == "pub-svn" ) && ( -n "$3" ) ]] ; then
    AdCbSvnTrunk="$3"
elif    [[ ( "${OptTarget}" == "pub-obf" ) && ( -n "$4" ) ]] ; then
    AdCbObfTrunk="$4"
elif    [[ ( "${OptTarget}" == "pub-all" ) && ( -n "$3" ) && ( -n "$4" ) ]] ; then
    AdCbSvnTrunk="$3"
    AdCbObfTrunk="$4"
else
    echo "> Parameter #3 'cb svn trunk dir' and/or Parameter #3 'cb obf trunk dir' not defined.Please ensure"
    echo  " that the the corresponding CustomVars CB_CVARS__CB_SVN_TRUNK_DIR or CB_CVARS__CB_OBF_TRUNK_DIR"
    echo  " are defined in C::B:"
    exit 1
fi

if [[ -z "${CbSvnVersion}" ]] ; then
    echo "> Parameter #5 'CbSvnVersion' not defined. Please ensure that the CustomVar"
    echo "  CB_CVARS__CB_SVN_VERSION is defined in C::B:"
    exit 1
fi
if [[ -z "${CbCVarsGitVersion}" ]] ; then
    echo "> Parameter #6 'CbCVarsGitVersion' not defined. Please ensure that the CustomVar"
    echo "  CB_CVARS__GIT_VERSION is defined in C::B:"
    exit 1
fi

AdCbProject="${AdCbProject%/}"                                                                      # C::B $(PROJECT_DIR) comes with a trailing '/'

source "./build/lx/build.config.bash"                                                               # files modified & relative folders in C::B trunk

source "./build/lx/build.dev.bash"                                                                  # functions for dev and pub targets
source "./build/lx/build.pub.bash"
source "./build/lx/build.pub-svn.bash"
source "./build/lx/build.pub-obf.bash"

AdPub="${AdCbProject}/out/pub"                                                                      # for publication targets

AdXport="${AdCbProject}/out/export"                                                                 # for cb-custom project

AfXrcSrc="${AdCbProject}/src/compiler_options.xrc"
AfXrcPub="${AdPub}/compiler_options.xrc"

echo "Summary:"                                                                                     # message
echo "-------"
echo "Project Target:${OptTarget}"
echo "AdCbProject   :${AdCbProject}"
echo "AdPub         :${AdPub}"
echo "AdXport       :${AdXport}"
echo "AdCbSvnTrunk  :${AdCbSvnTrunk}"
echo "AdCbObfTrunk  :${AdCbObfTrunk}"
echo ""
#   ------------------------------------------------------------------------------------------------
#   Go
#   ------------------------------------------------------------------------------------------------

#   prebuild step : set version information
rm      ${AdPub}/0-GENERATED-FROM--* 2>/dev/null
echo    -n "" > "${AdPub}/0-GENERATED-FROM--CB-SVN-${CbSvnVersion}"
echo    -n "" > "${AdPub}/0-GENERATED-FROM--CB-CVARS-${CbCVarsGitVersion}"

#   prebuild step : init linux user script vars in pub directory
echo "FilesCard=${FilesCard}" > "${AdPub}/lx/erg.cb-cvars--apply-patches-vars.bash"

#   prebuild step : build target specific
if      [[ "${OptTarget}" == "dev" ]] ; then
    build_dev__prebuild
elif    [[ (( "${OptTarget}" == "pub-svn" )) || (( "${OptTarget}" == "pub-all" )) ]] ; then
    build_pub_svn__prebuild
elif    [[ (( "${OptTarget}" == "pub-obf" )) || (( "${OptTarget}" == "pub-all" )) ]] ; then
    build_pub_obf__prebuild
fi

echo ""

#   main loop
for (( i=0 ; i < $((FilesCard)) ; i+=1 )) ; do

    #   define vars
    F="${Files[$((i))]}"
    D="${Dirs[$((i))]}"

    AfSrc="${AdCbProject}/src/${F}"
    AfPub="${AdPub}/${F}"
    AfXport="${AdXport}/${F}"
    AfTrunk="${AdCbSvnTrunk}/${D}/${F}"
    FnPatch="erg.cb-cvars--patch--${F}"

    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "pub:doing ${F}..."
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

    case "${OptTarget}" in

    "dev")
    #echo "dev"
    build_dev
    ;;

    "pub-svn")
    #echo "pub-svn"
    build_pub__publish_file "${AfSrc}" "${AfPub}"
    build_pub_svn
    build_pub__apply_patch__add_var
    ;;

    "pub-obf")
    #echo "pub-obf"
    build_pub__publish_file "${AfSrc}" "${AfPub}"
    build_pub_obf
    build_pub__apply_patch__add_var
    ;;

    "pub-all")
    #echo "pub-all"
    build_pub__publish_file "${AfSrc}" "${AfPub}"
    build_pub_svn
    build_pub_obf
    build_pub__apply_patch__add_var
    ;;

    *)
    echo "> Main loop:bad target"
    exit 1
    ;;

    esac

done

#   postbuild step : publish linux user script
cp  "${AdCbProject}/build/lx/erg.cb-cvars--apply-patches.bash"  "${AdPub}/lx"
chmod u=rwx,g=rwx "${AdPub}/lx"

exit 0
