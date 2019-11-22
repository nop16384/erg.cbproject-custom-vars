#!/bin/bash

#   ################################################################################################
#
#   build/lx/apply-patches.bash
#
#   $1  C::B trunk dir to apply patches to
#   $2  OptTarget : svn / obf
#   $3  OptWrite  : 'w' = really patch ; other = --dry-run
#
#   ################################################################################################

#   ################################################################################################
#   Globals
#   ################################################################################################
AdCbTrunk="$1"
OptTarget="$2"
OptWrite="$3"
#   ################################################################################################
#   Functions
#   ################################################################################################
#   ################################################################################################
#   Main
#   ################################################################################################

#   ................................................................................................
#   test if $1 parameter was given
if [[ -z "${AdCbTrunk}" ]] ; then

    echo "> you must specify the C::B trunk directory as parameter"
    echo "  ex : ./apply-patches \"/home/bob/codeblocks/svn11914/trunk\""
    exit 1
fi

#   test if $2 parameter was given
if [[ ( "${OptTarget}" != "erg" ) && ( "${OptTarget}" != "obf" ) ]] ; then

    echo "> you must specify the type of trunk to be patched ( 'svn' or 'obf' )"
    exit 1
fi

#   test if $3 parameter was given
if [[ "${OptWrite}" == "w" ]] ; then
    echo "> option 'w' given, will really patch"
    OptWrite=""
else
    echo "> option 'w' not given, will not patch ( --dry-run )"
    OptWrite="--dry-run"
fi
#   ................................................................................................
#   test if the script is run from the directory it reside in. The name of this script is
#   complicated enough to avoid confusion with hosts bash scripts
A=$( ls "erg.cb-cvars--apply-patches.bash" 2>&1 1>/dev/null )

if [[ -n "${A}" ]] ; then

    echo "> you must run this script from the directory it reside in."
    exit 1
fi
#   ................................................................................................
#   apply patches

#   get patches, we are in ..../pub/lx
source "erg.cb-cvars--apply-patches-vars.bash"

cd ..                                                                                               #   now we are in ..../pub
Pwd="$( pwd )"

for (( i=0 ; i != FilesCard ; i+=1 )) ; do

    AfPatch[$((i))]="${Pwd}/patches/${OptTarget}/${FPatch[$((i))]}"
    RfDst[$((i))]="${FDst[$((i))]}"

done

#   go in the trunk
cd "${AdCbTrunk}"

#   patch !
for (( i=0 ; i != FilesCard ; i+=1 )) ; do

    PCom="patch ${OptWrite} --verbose \"${RfDst[$((i))]}\" \"${AfPatch[$((i))]}\""

    echo "> Evaluating command [${PCom}]"

    eval "${PCom}"

done

exit 0









