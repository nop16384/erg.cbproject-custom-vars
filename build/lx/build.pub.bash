#   ------------------------------------------------------------------------------------------------
#   build_pub__verify_file_changes
#
#   verify that the dst file is the same as the reference file
#
#   $1  ref-file apath
#   $2  dst-file apath
#   ------------------------------------------------------------------------------------------------
function    build_pub__verify_file_changes
{
    R=$( diff "$1" "$2" )

    if [[ $(($?)) -ne 0 ]] ; then
        echo "> Files ["$1"] ["$2"] are not identical, exiting"
        echo "${R}"
        exit 1
    fi
}
#   ------------------------------------------------------------------------------------------------
#   build_pub__publish_c_cpp
#
#   suppress ERG modification marks
#
#   $1  src-file apath
#   $2  pub-file apath
#   ------------------------------------------------------------------------------------------------
function    build_pub__publish_c_cpp
{
    cat "$1" | sed                              \
            -e '/^[ \t]*\/\/[ \t]*ERG/d'        \
            -e '/ERG[+-]$/d'                    >   "$2"
}
#   ------------------------------------------------------------------------------------------------
#   build_pub__publish_xrc
#
#   suppress HTML comments from file
#
#   $1  src-file apath
#   $2  pub-file apath
#   ------------------------------------------------------------------------------------------------
function    build_pub__publish_xrc
{
    cat "$1"  | sed '/<!--.*-->/d' | sed '/<!--/,/-->/d' > "$2"
}
#   ------------------------------------------------------------------------------------------------
#   build_pub__publish_file
#
#   suppress ERG modification marks ( or HTML comments for xrc files ), publish and export
#
#   $1  src-file path
#   $2  pub-file path
#   ------------------------------------------------------------------------------------------------
function    build_pub__publish_file
{
    local   fsrc fpub ext
    #   ............................................................................................
    fsrc="$1"
    fpub="$2"
    ext="${fsrc##*.}"

    if [[ "${ext}" != "xrc" ]] ; then

        build_pub__publish_c_cpp    "${fsrc}"   "${fpub}"

    else

        build_pub__publish_xrc      "${fsrc}"   "${fpub}"

    fi
}
#   ------------------------------------------------------------------------------------------------
#   build_pub__gen_patch
#
#   $1  Ad  Trunk to generate the path against
#   $2  Rf  file in trunk
#   $3  Af  modified file
#   $4  Af  patch file
#   ------------------------------------------------------------------------------------------------
function    build_pub__gen_patch
{
    local   fpo fpm fpp
    #   ............................................................................................
    fpo="$1"
    fpm="$2"
    fpp="$3"

    cd "$1"                                                                                         #   get system-independant : diff from trunk dir

    diff -u "$2" "$3" > "$4"
}
#   ------------------------------------------------------------------------------------------------
#   build_pub__apply_patch__add_var
#   ------------------------------------------------------------------------------------------------
function    build_pub__apply_patch__add_var
{
    #   update "erg.cb-cvars--apply-patches-vars.bash"
    #echo "> updating script vars..."
    echo "FPatch[${i}]=${FnPatch}"  >> "${AdPub}/lx/erg.cb-cvars--apply-patches-vars.bash"
    echo "  FDst[${i}]=${D}/${F}"   >> "${AdPub}/lx/erg.cb-cvars--apply-patches-vars.bash"
}
