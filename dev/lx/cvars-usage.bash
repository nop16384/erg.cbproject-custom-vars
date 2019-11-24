#!/bin/bash

#   ################################################################################################
#
#   dev/lx/cvars-usage.bash
#
#   $1  Ad  C::B project dir
#   $2  Ad  C::B trunk
#
#   ################################################################################################

#   ------------------------------------------------------------------------------------------------
#   Vars / options
#   ------------------------------------------------------------------------------------------------
AdCbProject="$1"
AdCbTrunk="$2"

ListA="SetVar         UnsetVar         UnsetAllVars         HasVar GetVar GetAllVars"
ListI="SetInactiveVar UnsetInactiveVar UnsetAllInactiveVars               GetAllInactiveVars"
List="${ListA} ${ListI}"
List="SetDefinitionFileFilename"
#   ------------------------------------------------------------------------------------------------
if [[ -z "${AdCbProject}" ]] ; then
    echo "> Parameter #1 'AdCbProject' not defined."
    exit 1
fi
if [[ -z "${AdCbTrunk}" ]] ; then
    echo "> Parameter #2 'AdCbTrunk' not defined."
    exit 1
fi

AdCbProject="${AdCbProject%/}"                                                                      # C::B $(PROJECT_DIR) comes with a trailing '/'

#source "${AdCbProject}/build/lx/build.config.bash"                                                  # files modified & relative folders in C::B trunk

echo "Summary:"                                                                                     # message
echo "-------"
echo "AdCbProject :${AdCbProject}"
echo "AdCbTrunk   :${AdCbTrunk}"
echo " "
#   ------------------------------------------------------------------------------------------------
#   Go
#   ------------------------------------------------------------------------------------------------

#   main loop

export ListA
export ListI
export List

find "${AdCbTrunk}" -type f -name "*.h"   | xargs -I % awk -f "dev/lx/cvars-usage.awk" -v List="${List}" %

find "${AdCbTrunk}" -type f -name "*.cpp" | xargs -I % awk -f "dev/lx/cvars-usage.awk" -v List="${List}" %

exit 0

