#define BUFFER_SIZE 5
typedef int buffer_item;

void init_buffer();

void destroy_buffer();

void print_buffer();

int insert_item(buffer_item item);

int remove_item(buffer_item *item);


