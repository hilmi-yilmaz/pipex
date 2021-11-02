#!/bin/bash

# This is a simple tester for pipex.

# Input file name
file_in="/tmp/file_in"

# Create input file
cat << EOF > $file_in
codamcodingcollege
codam
ahhaha
codamamsterdam
codanmgotcha
EOF

# $1: input file
# $2: cmd1
# $3: cmd2
# $4: output file
run_pipex()
{
	./pipex "$1" "$2" "$3" "$4"
	echo "$?"
}

# $1 whole command to execute
run_bash()
{
	bash -c "$1"
	echo "$?"
}

# $1: exit_status_bash
# $2: exit_status_yours 
compare_outputs()
{

	cat file_out_yours
	echo ""
	cat file_out_bash
	# Check whether file_out exists
	if [[ ! -f file_out_yours ]]; then
		echo "Error: file_out not created by pipex."
	fi

	# Compare exit status
	if [[ "$1" == "$2" ]]; then
		echo "SUCCES: Exit codes correct."
	else
		echo "ERROR: Exit codes differ."
	fi

	# Compare output files
	diff file_out_bash file_out_yours > /dev/null
	if [[ "$?" == "0" ]]; then
		echo "SUCCES: Output files the same."
	else
		echo "ERROR: Output files differ."
	fi

	# Delete created files
	rm -f file_out_bash file_out_yours
}

# Test 1
exit_status_bash=$(run_bash "< $file_in grep contents | wc -l > file_out_bash")
exit_status_yours=$(run_pipex "$file_in" "grep contents" "wc -l" "file_out_yours")
compare_outputs "$exit_status_bash" "$exit_status_yours"

# Test 2
exit_status_bash=$(run_bash "< $file_in ls -la | wc -w > file_out_bash")
exit_status_yours=$(run_pipex "$file_in" "ls -la" "wc -w" file_out_yours)
compare_outputs "$exit_status_bash" "$exit_status_yours"
