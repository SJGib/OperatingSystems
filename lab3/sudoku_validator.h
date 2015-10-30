void init();

void tokenize(char *line, int *array);

void *check_all_rows(void *arg);

int check_row(int row);

void *check_all_columns(void *arg);

int check_column(int col);

void *check_all_grids(void *arg);

int check_grid(int row, int col);