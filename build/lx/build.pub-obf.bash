function    build_pub_obf__prebuild
{
    echo -n ""
}
#   ------------------------------------------------------------------------------------------------
#   build_pub_obf
#   ------------------------------------------------------------------------------------------------
function    build_pub_obf
{
    local   i
    local   f d
    local   fsrc fpub ftrk fxp
    #   ............................................................................................
    #   generate patch
    echo "> generating obf patch..."
    fpp="${AdPub}/patches/obf/${FnPatch}"
    build_pub__gen_patch    "${AdCbObfTrunk}" "${D}/${F}" "${AfPub}" "${fpp}"
}
