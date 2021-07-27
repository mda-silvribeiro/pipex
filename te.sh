#! /bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
HONEY="\e[38;5;214m"
BOLD="\033[1m"
RESET="\033[0m"

printf $HONEY$BOLD"\n╔═╗╦╔═╗╔═╗═╗ ╦\n"
printf              "╠═╝║╠═╝║╣ ╔╩╦╝\n"
printf              "╩  ╩╩  ╚═╝╩ ╚═\n"
printf "T E S T E R [mini]\n\n"$RESET

make -C ../
cp ../pipex .
touch forbidden
chmod 000 forbidden

f_test()
{
    ./pipex $1 "$2" "$3" $4
    PIPEX_EXIT_STATUS=$?
    OUTPUT_PIPEX=$(cat $4)
    # echo "$OUTPUT_PIPEX"
    : > outfile
    
    if [[ $PIPEX_EXIT_STATUS  = 139 ]]
    then
        printf $RED$BOLD"☠️ SEGFAULT ☠️\n"$RESET
        return
    fi

    < $1 $2 | $3 > $4
    BASH_EXIT_STATUS=$?
    OUTPUT_BASH=$(cat $4)
    # echo "$OUTPUT_BASH"
    : > outfile

    if [[ $OUTPUT_PIPEX = $OUTPUT_BASH ]]
    then
        printf $GREEN$BOLD"√\n"$RESET
    else
        printf $RED$BOLD"X\n"$RESET
    fi
}

# wrong number of args
printf $YELLOW"\nwrong number of args\n"$RESET
./pipex
./pipex infile
./pipex infile cat
./pipex infile cat outfile
./pipex infile cat cat cat outfile

# bad args
printf $YELLOW"\nbad args\n"$RESET
f_test bad cat cat outfile
f_test infile cat bad outfile
f_test infile bad cat outfile
f_test infile bad bad outfile
f_test infile cat "" outfile
f_test infile "" cat outfile
f_test infile "" "" outfile

# incorrect file permissions
printf $YELLOW"\nincorrect file permissions\n"$RESET
f_test infile cat cat forbidden
f_test forbidden cat cat outfile
f_test forbidden cat cat forbidden

# regular tests
printf $YELLOW"\nregular tests\n"$RESET
# from subject
f_test infile "ls -l" "wc -l" outfile
f_test infile "grep a1" "wc -w" outfile
# added
f_test infile "echo ." "wc -l" outfile
f_test infile "head -n 1" "wc -c" outfile
f_test infile "tail -n 1" "wc -c" outfile
f_test infile "cat -e" "cat -e" outfile
f_test infile "grep one" "wc -c" outfile
f_test infile "cat -e" "wc -w" outfile
f_test /dev/urandom "head -n 100" "wc -l" outfile

if [[ $1 = "-v" ]]
then
    printf $YELLOW"\nselection of tests with valgrind\n"$RESET
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind1.out ./pipex infile "" "" outfile > /dev/null 2>&1
    printf "valgrind1.out generated (ok)\n"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind2.out ./pipex infile cat bad outfile > /dev/null 2>&1
    printf "valgrind2.out generated (ok)\n"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind3.out ./pipex infile cat cat cat outfile > /dev/null 2>&1
    printf "valgrind3.out generated (ok)\n"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind4.out ./pipex infile cat cat forbidden > /dev/null 2>&1
    printf "valgrind3.out generated (ok)\n"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind5.out ./pipex infile "ls -l" "wc -l" outfile > /dev/null 2>&1
    printf "valgrind3.out generated (ok)\n"
else
    printf "\n(run with -v for a bit of valgrinding)\n"
fi
