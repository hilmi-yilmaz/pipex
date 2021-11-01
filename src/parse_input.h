#ifndef PARSE_INPUT_H
# define PARSE_INPUT_H

/* System headers */
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

/* User defined headers */
# include "libft/libft.h"
# include "data.h"

/* Function prototypes */
int	parse_input(t_data *data, char **argv, char **envp);

#endif