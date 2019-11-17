#!/bin/bash

#   ################################################################################################
#
#   build/lx/apply-patches.bash
#
#
#
#   ################################################################################################

#   ################################################################################################
#   Globals
#   ################################################################################################
CbTrunkDir="$1"
#   ################################################################################################
#   Functions
#   ################################################################################################
#   ################################################################################################
#   Main
#   ################################################################################################

#   ................................................................................................
#   test if a parameter was given
if [[ -z "${CbTrunkDir}" ]] ; then

    echo "> you must specify the C::B trunk directory as parameter"
    echo "  ex : ./apply-patches \"/home/bob/codeblocks/svn11914/trunk\""

    exit 1
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

    Fpap[$((i))]="${Pwd}/patches/${FPatch[$((i))]}"
    Fdrp[$((i))]="${FDst[$((i))]}"

done

#   go in the trunk
cd "${CbTrunkDir}"

#   patch !
for (( i=0 ; i != FilesCard ; i+=1 )) ; do

    PCom="patch --dry-run \"${Fdrp[$((i))]}\" \"${Fpap[$((i))]}\""

    echo "> Evaluating command [${PCom}]"

    eval "${PCom}"

done

exit 0









