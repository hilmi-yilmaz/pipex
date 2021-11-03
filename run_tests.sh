#!/bin/bash

# This is a simple tester for pipex.

# Exit variables
exit_status_bash="0"
exit_status_yours="0"

# Check for pipex executable
if [[ ! -f pipex ]]; then
	echo "No pipex executable found."
	exit 1
fi

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
	exit_status_yours="$?"
}

# $1 whole command to execute
run_bash()
{
	bash -c "$1"
	exit_status_bash="$?"
	if [[ "$exit_status_bash" != "0" ]]; then
		echo "do some stuff"
	fi
}

# $1: exit_status_bash
# $2: exit_status_yours 
compare_outputs()
{
	# Check whether file_out exists
	# if [[ ! -f /tmp/file_out_yours ]]; then
	# 	echo "Error: file_out not created by pipex."
	# fi

	# # Compare exit status
	if [[ "$1" == "$2" ]]; then
		echo "SUCCES: Exit codes correct (yours="$2" | bash="$1")"
	else
		echo "ERROR: Exit codes differ (yours="$2" | bash="$1")"
	fi

	# Compare output files
	diff /tmp/file_out_bash /tmp/file_out_yours > /dev/null 2>&1
	if [[ "$?" == "0" ]]; then
		echo "SUCCES: Output files the same."
	else
		echo "ERROR: Output files differ."
	fi

	# Delete created files
	rm -f /tmp/file_out_bash /tmp/file_out_yours
	echo ""
}

# Test 1
run_bash "< $file_in grep contents | wc -l > /tmp/file_out_bash"
run_pipex "$file_in" "grep contents" "wc -l" "/tmp/file_out_yours"
compare_outputs "$exit_status_bash" "$exit_status_yours"

# Test 2
run_bash "< $file_in ls -la | wc -w > /tmp/file_out_bash"
run_pipex "$file_in" "ls -la" "wc -w" /tmp/file_out_yours
compare_outputs "$exit_status_bash" "$exit_status_yours"

# Test 3: Input file doesn't exists
run_bash "< ewa_broer grep contents | wc -l > /tmp/file_out_bash"
run_pipex ewa_broer "grep contents" "wc -l" /tmp/file_out_yours
compare_outputs "$exit_status_bash" "$exit_status_yours"

# Test 4: command 1 doesn't exist

# Test 5: test with outputfile without permission(chmod 444 output_file and then run pipex)