#   ------------------------------------------------------------------------------------------------
#   build_pub__publish_file
#
#   $1  src-file path
#   $2  pub-file path
#   ------------------------------------------------------------------------------------------------
function    build_pub__publish_file
{
    local   fsrc fpub
    #   ............................................................................................
    fsrc="$1"
    fpub="$2"

    cat "${fsrc}" | sed                             \
        -e '/^[ \t]*\/\/[ \t]*ERG/d'                \
        -e '/ERG[+-]$/d'                            >   "${fpub}"
}
#   ------------------------------------------------------------------------------------------------
#   build_pub__gen_patch
#
#   $1  original file   rpath
#   $2  modified file   apath
#   $3  patch file      apath
#   ------------------------------------------------------------------------------------------------
function    build_pub__gen_patch
{
    local   fpo fpm fpp
    #   ............................................................................................
    fpo="$1"
    fpm="$2"
    fpp="$3"

    cd "${CbTrunkDir}"                                                                              #   get system-independant : diff from trunk dir

    diff -u "${fpo}" "${fpm}" > "${fpp}"
}
#   ------------------------------------------------------------------------------------------------
#   build_pub
#   ------------------------------------------------------------------------------------------------
function    build_pub
{
    local   i
    local   f d
    local   fsrc fpub ftrk fxp
    #   ............................................................................................
    for (( i=0 ; i < $((FilesCard)) ; i+=1 )) ; do

        f="${Files[$((i))]}"
        d="${Dirs[$((i))]}"

        fsrc="${ProjectDir}/src/${f}"
        fpub="${PubDir}/${f}"
        ftrk="${CbTrunkDir}/${d}/${f}"
        fxp="${XpDir}/${f}"

        #echo "src:${fsrc}"
        #echo "pub:${fpub}"
        #echo "trk:${ftrk}"
        #echo "xp :${fxp}"

        echo "pub:doing ${f}..."

        #   suppress ERG modification marks, publish and export
        build_pub__publish_file "${fsrc}" "${fpub}"
        cp "${fpub}" "${fxp}"

        #   generate patch
        fpn="erg.cb-cvars--patch--${f}"
        fpp="${PubDir}/patches/${fpn}"
        build_pub__gen_patch "${d}/${f}" "${fpub}" "${fpp}"

        #   update "erg.cb-cvars--apply-patches-vars.bash"
        echo "FPatch[${i}]=${fpn}"      >> "${PubDir}/lx/erg.cb-cvars--apply-patches-vars.bash"
        echo "  FDst[${i}]=${d}/${f}"   >> "${PubDir}/lx/erg.cb-cvars--apply-patches-vars.bash"

    done
}
