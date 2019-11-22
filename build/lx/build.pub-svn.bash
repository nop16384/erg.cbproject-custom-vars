function    build_pub_svn__prebuild
{
    echo -n ""
}
#   ------------------------------------------------------------------------------------------------
#   build_pub_svn
#   ------------------------------------------------------------------------------------------------
function    build_pub_svn
{
    local   i
    local   f d
    local   fsrc fpub ftrk fxp
    #   ............................................................................................
    #   generate patch
    echo "> generating svn patch..."
    fpp="${AdPub}/patches/svn/${FnPatch}"
    build_pub__gen_patch    "${AdCbSvnTrunk}" "${D}/${F}" "${AfPub}" "${fpp}"
}
