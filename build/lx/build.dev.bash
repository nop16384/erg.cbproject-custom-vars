#   ------------------------------------------------------------------------------------------------
#   build_dev
#   ------------------------------------------------------------------------------------------------
function    build_dev
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

        echo "dev:doing ${f}..."

        cp  "${fsrc}" "${fxp}"


    done
}

