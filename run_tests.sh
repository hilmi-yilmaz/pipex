#!/bin/bash

# This is a simple tester for pipex.

# Colours
RED="\033[0;31m"
GREEN="\033[0;32m"
NC="\033[0m"

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
}

# $1: exit_status_bash
# $2: exit_status_yours 
# $3: file_out_bash
# $4: file_out_yours
compare_outputs()
{
	# Check whether file_out exists
	# if [[ ! -f /tmp/file_out_yours ]]; then
	# 	echo "Error: file_out not created by pipex."
	# fi

	# # Compare exit status
	if [[ "$1" == "$2" ]]; then
		echo -e "${GREEN}SUCCES${NC}: Exit codes correct (yours="$2" | bash="$1")"
	else
		echo -e "${RED}ERROR${NC}: Exit codes differ (yours="$2" | bash="$1")"
	fi

	# Compare output files
	diff "$3" "$4" > /dev/null 2>&1
	if [[ "$?" == "0" ]]; then
		echo -e "${GREEN}SUCCES${NC}: Output files the same."
	else
		echo -e "${RED}ERROR${NC}: Output files differ."
	fi

	# Delete created files
	rm -f "$3" "$4"
	echo ""
}

# Test 1
run_bash "< $file_in grep contents | wc -l > /tmp/file_out_bash"
run_pipex "$file_in" "grep contents" "wc -l" "/tmp/file_out_yours"
compare_outputs "$exit_status_bash" "$exit_status_yours" "/tmp/file_out_bash" "/tmp/file_out_yours"

# Test 2
run_bash "< $file_in ls -la | wc -w > /tmp/file_out_bash"
run_pipex "$file_in" "ls -la" "wc -w" /tmp/file_out_yours
compare_outputs "$exit_status_bash" "$exit_status_yours" "/tmp/file_out_bash" "/tmp/file_out_yours"

# Test 3: Input file doesn't exists
run_bash "< ewa_broer grep contents | wc -l > /tmp/file_out_bash"
run_pipex ewa_broer "grep contents" "wc -l" /tmp/file_out_yours
compare_outputs "$exit_status_bash" "$exit_status_yours" "/tmp/file_out_bash" "/tmp/file_out_yours"

# Test 4: command 1 doesn't exist
run_bash "< $file_in grep12 contents | wc -l > /tmp/file_out_bash"
run_pipex "$file_in" "grep12 contents" "wc -l" "/tmp/file_out_yours"
compare_outputs "$exit_status_bash" "$exit_status_yours" "/tmp/file_out_bash" "/tmp/file_out_yours"

# Test 5: command 2 doesn't exist
run_bash "< $file_in grep contents | wc12 -l > /tmp/file_out_bash"
run_pipex "$file_in" "grep contents" "wc12 -l" "/tmp/file_out_yours"
compare_outputs "$exit_status_bash" "$exit_status_yours" "/tmp/file_out_bash" "/tmp/file_out_yours"

# Test 6: command 1 invalid option
run_bash "< $file_in grep -Q contents | wc -l > /tmp/file_out_bash"
run_pipex "$file_in" "grep -Q contents" "wc -l" "/tmp/file_out_yours"
compare_outputs "$exit_status_bash" "$exit_status_yours" "/tmp/file_out_bash" "/tmp/file_out_yours"

# Test 7: command 2 invalid option
run_bash "< $file_in grep contents | wc -x > /tmp/file_out_bash"
run_pipex "$file_in" "grep contents" "wc -x" "/tmp/file_out_yours"
compare_outputs "$exit_status_bash" "$exit_status_yours" "/tmp/file_out_bash" "/tmp/file_out_yours"

# Test : test with outputfile without permission(chmod 444 output_file and then run pipex)
touch /tmp/no_permissions
chmod 444 /tmp/no_permissions
run_bash "< $file_in grep contents | wc -l > /tmp/no_permissions"
run_pipex $file_in "grep contents" "wc -l" /tmp/no_permissions
compare_outputs "$exit_status_bash" "$exit_status_yours" "/tmp/no_permissions" "/tmp/no_permissions"