BEGIN {
    # print "-------------------------------- BEGIN -------------------------------- \n";
    # printf "File:[%s]\n", ARGV[1];
    # printf " \n"

    split(List, lst, " ");
    r_c=0;
}

{
    for ( t in lst )
    {
        #m=lst[t]"\\(";
        m=lst[t];
        if ( match($0, m ) )
        {
            r_ln[r_c]=NR;
            r_kw[r_c]=lst[t];
            r_tx[r_c]=$0;

            r_c++;
        }
    }
}

END {

    # print "-------------------------------- END -------------------------------- \n";

    if ( r_c != 0 )
    {
        printf "[%s]\n", FILENAME;
        for ( i = 0 ; i != r_c ; i++ )
        {
            printf "%-20s [%5d] %s\n", r_kw[i], r_ln[i], r_tx[i];
        }
        print " \n";
    }
}

