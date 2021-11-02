#!/bin/bash

# This is a simple tester for pipex.

# Input file name
file_in="/tmp/file_in"

# Create input file
cat << EOF > $file_in
These contents will be written to the file.
        This line is indented.
EOF

# Run bash
< file_in grep hilmi | wc -l > file_out_bash
exit_status_bash=$(echo "$?")

# Run yours
./pipex file_in "grep hilmi" "wc -l" file_out_yours
exit_status_yours=$(echo "$?")

# Check whether file_out exists
if [[ ! -f file_out_yours ]]; then
	echo "Error: file_out not created."
fi

# Compare outputs
if [[ "$exit_status_bash" == "$exit_status_yours" ]]; then
	echo "SUCCES: Exit codes correct."
else
	echo "ERROR: Exit codes differ."
fi

diff file_out_bash file_out_yours >> /dev/null
if [[ "$?" == "0" ]]; then
	echo "SUCCES: Output files the same."
else
	echo "ERROR: Output files differ."
fi

rm -f file_out_bash file_out_yours
