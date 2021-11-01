#ifndef CHILD_PROCESS_H
# define CHILD_PROCESS_H

/* System headers */
# include <stdio.h>
# include <unistd.h>

/* User defined headers */
# include "libft/libft.h"
# include "data.h"

/* Function prototypes */
int child_one(t_data data, int *fds, char **envp);

#endif